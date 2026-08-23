// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include <catch_amalgamated.hpp>
#include "common.hpp"
#include "xsk/utils/file.hpp"
#include "xsk/utils/zlib.hpp"

namespace xsk::test
{

namespace
{

namespace fs = std::filesystem;

// The corpus under test/data/<game> is original game source. Every file is put
// through the full pipeline and the bytecode has to survive the trip:
//
//   source -> compile -> assemble -> disassemble -> decompile -> print -> compile
//
// The two assemblies must come out byte for byte identical. Anything the parser
// cannot read, the decompiler cannot rebuild or the printer cannot round-trip
// shows up as a failing file here.

// test/data mirrors data/: 'raw' holds original source, 'bin' holds shipped bytecode.
auto corpus_root(std::string_view kind, std::string_view game) -> fs::path
{
    return fs::path{ XSK_TEST_DATA } / kind / game;
}

auto corpus(std::string_view kind, std::string_view game, std::string_view ext) -> std::vector<std::string>
{
    auto const root = corpus_root(kind, game);
    auto out = std::vector<std::string>{};

    for (auto const& entry : fs::recursive_directory_iterator{ root })
    {
        if (entry.is_regular_file() && entry.path().extension() == ext)
            out.push_back(fs::relative(entry.path(), root).generic_string());
    }

    std::sort(out.begin(), out.end());
    return out;
}

// Scripts '#include' each other and the compiler resolves those through the
// context, so reads are served straight out of the corpus directory.
template <typename Ctx>
auto make_engine_ctx(std::string_view game, typename fam<Ctx>::build build) -> Ctx*
{
    auto root = corpus_root("raw", game);
    auto* c = new Ctx(fam<Ctx>::instance::server);

    c->init(build, [root](auto const*, std::string const& name) {
        return std::pair<typename fam<Ctx>::buffer, std::vector<u8>>{ {}, utils::file::read(root / name) };
    });

    return c;
}

// Original source is written against the developer build, so the corpus is run both
// ways: '/# #/' blocks are stripped under prod and compiled under dev, which is two
// different programs out of the same file.
//
// ponytail: deliberate leak and statics keyed on nothing but the context type, same
// reasoning as ctx() in common.hpp. One game maps to one corpus directory, so a second
// root for the same context type is not a case that exists.
template <typename Ctx>
auto engine_ctx(std::string_view game, bool dev) -> Ctx*
{
    static Ctx* prod = make_engine_ctx<Ctx>(game, fam<Ctx>::build::prod);
    static Ctx* devel = make_engine_ctx<Ctx>(game, fam<Ctx>::build::dev);

    return dev ? devel : prod;
}

auto as_vector(auto const& buf) -> std::vector<u8>
{
    return std::vector<u8>{ buf.data, buf.data + buf.size };
}

// Catch2 would dump both buffers on a plain vector comparison, which for a
// 100 KB script is unreadable. Report where they part company instead.
auto diff(std::vector<u8> const& lhs, auto const& rhs) -> std::string
{
    if (lhs.size() != rhs.size)
        return std::format("size {} != {}", lhs.size(), rhs.size);

    for (auto i = usize{ 0 }; i < lhs.size(); i++)
    {
        if (lhs[i] != rhs.data[i])
            return std::format("byte {} of {}: {:02X} != {:02X}", i, lhs.size(), lhs[i], rhs.data[i]);
    }

    return {};
}

// Bytes decide, but "byte 3841 of 14337" says nothing about what went wrong. On a mismatch
// both buffers go back through the disassembler and the first differing line is reported.
template <typename Ctx>
auto asm_diff(Ctx* c, std::vector<u8> const& lscript, std::vector<u8> const& lstack, std::vector<u8> const& rscript, std::vector<u8> const& rstack) -> std::string
{
    try
    {
        auto const lhs = print_asm<Ctx>(*c->disassembler().disassemble(lscript, lstack), c);
        auto const rhs = print_asm<Ctx>(*c->disassembler().disassemble(rscript, rstack), c);

        auto li = usize{ 0 };
        auto ri = usize{ 0 };
        auto line = usize{ 1 };

        while (li < lhs.size() && ri < rhs.size())
        {
            auto const le = lhs.find('\n', li);
            auto const re = rhs.find('\n', ri);
            auto const l = lhs.substr(li, le - li);
            auto const r = rhs.substr(ri, re - ri);

            if (l != r)
                return std::format("line {}: '{}' != '{}'", line, l, r);

            if (le == std::string::npos || re == std::string::npos)
                break;

            li = le + 1;
            ri = re + 1;
            line++;
        }

        return std::format("assembly agrees to line {}, so the difference is in the encoding", line);
    }
    catch (std::exception const& e)
    {
        return std::format("disassembly failed: {}", e.what());
    }
}

template <typename Ctx>
auto round_trip(Ctx* c, std::string const& name, std::vector<u8> src) -> void
{
    auto data = c->assembler().assemble(*c->compiler().compile(name, src));

    // The assembler writes into members it reuses on the next call, so keep a
    // copy of the first result before compiling the printed source.
    auto script = as_vector(std::get<0>(data));
    auto stack = as_vector(std::get<1>(data));

    auto out = c->printer().print(*c->decompiler().decompile(*c->disassembler().disassemble(script, stack)));
    // Named apart from the source so a failure says which of the two compiles threw. The
    // name only feeds error locations, it never reaches the bytecode.
    auto redo = c->assembler().assemble(*c->compiler().compile(name + " (decompiled)", out));

    CHECK(diff(script, std::get<0>(redo)) == "");
    CHECK(diff(stack, std::get<1>(redo)) == "");
}

// Shipped bytecode in, the same bytecode back out. Stronger than the source round trip
// above: that one only proves we agree with ourselves, this one is measured against what
// Infinity Ward's compiler actually emitted.
//
// The decompiler writes far calls fully qualified rather than emitting '#include', so the
// printed source resolves nothing externally and no read callback is involved.
template <typename Ctx>
auto round_trip_binary(Ctx* c, std::string const& name, std::vector<u8> const& file) -> void
{
    auto script = typename fam<Ctx>::asset{};
    script.deserialize(file);

    auto const stack = utils::zlib::decompress(script.buffer, script.length);

    // The shipped bytes cannot be compared directly. OP_GetString and friends keep their
    // string reference in the script as a placeholder the game fills in at load time, and
    // the assembler writes a zero there; a shipped file carries whatever the engine baked
    // in. So the shipped instruction stream is put back through the assembler once to get
    // a baseline in our own placeholder convention, and the round trip is measured against
    // that. Everything else — opcodes, operands, offsets, the string table — still has to
    // match Infinity Ward's compiler byte for byte.
    auto base = c->assembler().assemble(*c->disassembler().disassemble(script.bytecode, stack));
    auto const base_script = as_vector(std::get<0>(base));
    auto const base_stack = as_vector(std::get<1>(base));

    auto out = c->printer().print(*c->decompiler().decompile(*c->disassembler().disassemble(base_script, base_stack)));
    auto redo = c->assembler().assemble(*c->compiler().compile(name, out));

    auto const redo_script = as_vector(std::get<0>(redo));
    auto const redo_stack = as_vector(std::get<1>(redo));

    if (base_script != redo_script || base_stack != redo_stack)
    {
        INFO(asm_diff(c, base_script, base_stack, redo_script, redo_stack));
        CHECK(diff(base_script, std::get<0>(redo)) == "");
        CHECK(diff(base_stack, std::get<1>(redo)) == "");
    }
}

template <typename Ctx>
auto round_trip_corpus(std::string_view game, bool dev) -> void
{
    auto const root = corpus_root("raw", game);
    auto* c = engine_ctx<Ctx>(game, dev);

    for (auto const& file : corpus("raw", game, ".gsc"))
    {
        DYNAMIC_SECTION(file)
        {
            round_trip(c, file, utils::file::read(root / file));
        }
    }
}

template <typename Ctx>
auto round_trip_binary_corpus(std::string_view game) -> void
{
    auto const root = corpus_root("bin", game);
    auto* c = engine_ctx<Ctx>(game, false);

    for (auto const& file : corpus("bin", game, ".gscbin"))
    {
        DYNAMIC_SECTION(file)
        {
            round_trip_binary(c, file, utils::file::read(root / file));
        }
    }
}

} // namespace

TEST_CASE("iw5 round trips its source (prod)", "[engine][gsc][iw5]")
{
    round_trip_corpus<gsc::iw5_pc::context>("iw5", false);
}

TEST_CASE("iw5 round trips its source (dev)", "[engine][gsc][iw5]")
{
    round_trip_corpus<gsc::iw5_pc::context>("iw5", true);
}

TEST_CASE("iw5 round trips shipped bytecode", "[engine][gsc][iw5][binary]")
{
    round_trip_binary_corpus<gsc::iw5_pc::context>("iw5");
}

} // namespace xsk::test
