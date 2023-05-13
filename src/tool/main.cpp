// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/zlib.hpp"
#include "xsk/utils/file.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/gsc/engine/iw5_pc.hpp"
#include "xsk/gsc/engine/iw5_ps.hpp"
#include "xsk/gsc/engine/iw5_xb.hpp"
#include "xsk/gsc/engine/iw6_pc.hpp"
#include "xsk/gsc/engine/iw6_ps.hpp"
#include "xsk/gsc/engine/iw6_xb.hpp"
#include "xsk/gsc/engine/iw7.hpp"
#include "xsk/gsc/engine/iw8.hpp"
#include "xsk/gsc/engine/iw9.hpp"
#include "xsk/gsc/engine/s1_pc.hpp"
#include "xsk/gsc/engine/s1_ps.hpp"
#include "xsk/gsc/engine/s1_xb.hpp"
#include "xsk/gsc/engine/s2.hpp"
#include "xsk/gsc/engine/s4.hpp"
#include "xsk/gsc/engine/h1.hpp"
#include "xsk/gsc/engine/h2.hpp"
#include "xsk/arc/engine/t6_pc.hpp"
#include "xsk/arc/engine/t6_ps3.hpp"
#include "xsk/arc/engine/t6_xb2.hpp"
#include "xsk/arc/engine/t6_wiiu.hpp"
#include "xsk/arc/engine/t7.hpp"
#include "xsk/arc/engine/t8.hpp"
#include "xsk/arc/engine/t9.hpp"

namespace fs = std::filesystem;

namespace xsk
{

enum class encd { _, source, assembly, binary };
enum class mode { _, assemble, disassemble, compile, decompile, parse, rename };
enum class game { _, iw5, iw6, iw7, iw8, iw9, s1, s2, s4, h1, h2, t6, t7, t8, t9 };
enum class mach { _, pc, ps3, ps4, ps5, xb2, xb3, xb4, wiiu };

std::unordered_map<std::string_view, encd> const exts =
{
    { ".gsc", encd::source },
    { ".cgsc", encd::binary },
    { ".gscbin", encd::binary },
    { ".gscasm", encd::assembly },
};

std::unordered_map<std::string_view, mode> const modes =
{
    { "asm", mode::assemble },
    { "disasm", mode::disassemble },
    { "comp", mode::compile },
    { "decomp", mode::decompile },
    { "parse", mode::parse },
    { "rename", mode::rename },
};

std::unordered_map<std::string_view, game> const games =
{
    { "iw5", game::iw5 },
    { "iw6", game::iw6 },
    { "iw7", game::iw7 },
    { "iw8", game::iw8 },
    { "iw9", game::iw9 },
    { "s1", game::s1 },
    { "s2", game::s2 },
    { "s4", game::s4 },
    { "h1", game::h1 },
    { "h2", game::h2 },
    { "t6", game::t6 },
    { "t7", game::t7 },
    { "t8", game::t8 },
    { "t9", game::t9 },
};

std::map<game, std::string_view> const games_rev =
{
    { game::iw5, "iw5" },
    { game::iw6, "iw6" },
    { game::iw7, "iw7" },
    { game::iw8, "iw8" },
    { game::iw9, "iw9" },
    { game::s1, "s1" },
    { game::s2, "s2" },
    { game::s4, "s4" },
    { game::h1, "h1" },
    { game::h2, "h2" },
    { game::t6, "t6" },
    { game::t7, "t7" },
    { game::t8, "t8" },
    { game::t9, "t9" },
};

std::unordered_map<std::string_view, mach> const machs =
{
    { "pc",   mach::pc   },
    { "ps3",  mach::ps3  },
    { "ps4",  mach::ps4  },
    { "ps5",  mach::ps5  },
    { "xb2",  mach::xb2  },
    { "xb3",  mach::xb3  },
    { "xb4",  mach::xb4  },
    { "wiiu", mach::wiiu },
};

std::map<mode, encd> const encds =
{
    { mode::assemble, encd::assembly },
    { mode::disassemble, encd::binary },
    { mode::compile, encd::source },
    { mode::decompile, encd::binary },
};

auto overwrite_prompt(std::string const& file) -> bool
{
    auto overwrite = true;

    if (utils::file::exists(file))
    {
        do
        {
            std::cout << "File \"" << file << "\" already exists, overwrite? [Y/n]: ";
            auto result = std::getchar();

            if (result == '\n' || result == 'Y' || result == 'y')
            {
                break;
            }
            else if (result == 'N' || result == 'n')
            {
                overwrite = false;
                break;
            }
        } while (true);
    }

    return overwrite;
}

namespace gsc
{

std::map<game, std::map<mach, std::unique_ptr<context>>> contexts;
std::map<mode, std::function<void(game game, mach mach, fs::path file, fs::path rel)>> funcs;
bool zonetool = false;

auto assemble_file(game game, mach mach, fs::path file, fs::path rel) -> void
{
    try
    {
        if (file.extension() != ".gscasm")
            throw std::runtime_error("expected .gscasm file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((zonetool ? ".cgsc" : ".gscbin"));

        auto data = utils::file::read(file);
        auto outasm = contexts[game][mach]->source().parse_assembly(data);
        auto outbin = contexts[game][mach]->assembler().assemble(*outasm);

        if (true/*overwrite_prompt(file + (zonetool ? ".cgsc" : ".gscbin"))*/)
        {
            if (zonetool)
            {
                auto path = fs::path{ "assembled" } / rel;
                utils::file::save(path, outbin.first.data, outbin.first.size);
                utils::file::save(path.replace_extension(".cgsc.stack"), outbin.second.data, outbin.second.size);
                std::cout << fmt::format("assembled {}\n", rel.generic_string());
            }
            else
            {
                asset script;
                script.name = "GSC"s;
                
                script.bytecode.resize(outbin.first.size);
                std::memcpy(script.bytecode.data(), outbin.first.data, script.bytecode.size());

                script.buffer.resize(outbin.second.size);
                std::memcpy(script.buffer.data(), outbin.second.data, script.buffer.size());
                script.buffer = utils::zlib::compress(script.buffer);

                script.len = static_cast<std::uint32_t>(outbin.second.size);
                script.compressedLen = static_cast<std::uint32_t>(script.buffer.size());
                script.bytecodeLen = static_cast<std::uint32_t>(script.bytecode.size());

                auto result = script.serialize();
                utils::file::save(fs::path{ "assembled" } / rel, result);
                std::cout << fmt::format("assembled {}\n", rel.generic_string());
            }
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

auto disassemble_file(game game, mach mach, fs::path file, fs::path rel) -> void
{
    try
    {
        auto script = std::vector<std::uint8_t>{};
        auto stack = std::vector<std::uint8_t>{};

        if (zonetool)
        {
            if (file.extension() != ".cgsc")
                throw std::runtime_error("expected .cgsc file");
            
            auto fbuf = file;
            rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension(".gsc");

            script = utils::file::read(file);
            stack = utils::file::read(fbuf.replace_extension(".cgsc.stack"));
        }
        else
        {
            if (file.extension() != ".gscbin")
                throw std::runtime_error("expected .gscbin file");

            rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension(".gscasm");

            auto data = utils::file::read(file);

            asset asset;
            asset.deserialize(data);

            script = std::move(asset.bytecode);
            stack = utils::zlib::decompress(asset.buffer, asset.len);
        }

        auto outasm = contexts[game][mach]->disassembler().disassemble(script, stack);
        auto outsrc = contexts[game][mach]->source().dump(*outasm);

        utils::file::save(fs::path{ "disassembled" } / rel, outsrc);
        std::cout << fmt::format("disassembled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

auto compile_file(game game, mach mach, fs::path file, fs::path rel) -> void
{
    try
    {
        if (file.extension() != ".gsc")
            throw std::runtime_error("expected .gsc file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((zonetool ? ".cgsc" : ".gscbin"));

        auto data = utils::file::read(file);
        auto outasm = contexts[game][mach]->compiler().compile(file.string(), data);
        auto outbin = contexts[game][mach]->assembler().assemble(*outasm);

        if (true/*overwrite_prompt(file + (zonetool ? ".cgsc" : ".gscbin"))*/)
        {
            if (zonetool)
            {
                auto path = fs::path{ "compiled" } / rel;
                utils::file::save(path, outbin.first.data, outbin.first.size);
                utils::file::save(path.replace_extension(".cgsc.stack"), outbin.second.data, outbin.second.size);
                std::cout << fmt::format("compiled {}\n", rel.generic_string());
            }
            else
            {
                asset script;
                script.name = "GSC"s;
                
                script.bytecode.resize(outbin.first.size);
                std::memcpy(script.bytecode.data(), outbin.first.data, script.bytecode.size());

                script.buffer.resize(outbin.second.size);
                std::memcpy(script.buffer.data(), outbin.second.data, script.buffer.size());
                script.buffer = utils::zlib::compress(script.buffer);

                script.len = static_cast<std::uint32_t>(outbin.second.size);
                script.compressedLen = static_cast<std::uint32_t>(script.buffer.size());
                script.bytecodeLen = static_cast<std::uint32_t>(script.bytecode.size());

                auto result = script.serialize();
                utils::file::save(fs::path{ "compiled" } / rel, result);
                std::cout << fmt::format("compiled {}\n", rel.generic_string());
            }
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

auto decompile_file(game game, mach mach, fs::path file, fs::path rel) -> void
{
    try
    {
        auto script = std::vector<std::uint8_t>{};
        auto stack = std::vector<std::uint8_t>{};
    
        if (zonetool)
        {
            if (file.extension() != ".cgsc")
                throw std::runtime_error("expected .cgsc file");
            
            auto fbuf = file;
            rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension(".gsc");

            script = utils::file::read(file);
            stack = utils::file::read(fbuf.replace_extension(".cgsc.stack"));
        }
        else
        {
            if (file.extension() != ".gscbin")
                throw std::runtime_error("expected .gscbin file");

            rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension(".gsc");

            auto data = utils::file::read(file);

            asset asset;
            asset.deserialize(data);

            script = std::move(asset.bytecode);
            stack = utils::zlib::decompress(asset.buffer, asset.len);
        }

        auto outasm = contexts[game][mach]->disassembler().disassemble(script, stack);
        auto outast = contexts[game][mach]->decompiler().decompile(*outasm);
        auto outsrc = contexts[game][mach]->source().dump(*outast);

        utils::file::save(fs::path{ "decompiled" } / rel, outsrc);
        std::cout << fmt::format("decompiled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

auto parse_file(game game, mach mach, fs::path file, fs::path rel) -> void
{
    try
    {
        if (file.extension() != ".gsc")
            throw std::runtime_error("expected .gsc file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename();

        auto data = utils::file::read(file);

        auto prog = contexts[game][mach]->source().parse_program(file.string(), data);
        utils::file::save(fs::path{ "parsed" } / rel, contexts[game][mach]->source().dump(*prog));
        std::cout << fmt::format("parsed {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

auto rename_file(game game, mach mach, fs::path file, fs::path rel) -> void
{
    try
    {
        if (file.extension() != ".cgsc" && file.extension() != ".gsc" && file.extension() != ".csc" && file.extension() != ".gscbin" && file.extension() != ".cscbin")
            return;

        auto ext = file.extension();
        auto zt = file.extension() == ".cgsc";

        if (game == game::iw9)
        {
            return;
        }
        else
        {
            auto name = file.filename().replace_extension().string();

            if (utils::string::is_number(name))
            {
                name = contexts[game][mach]->token_name(std::stoul(name));
            }
            else if (utils::string::is_hex_number(name))
            {
                name = contexts[game][mach]->token_name(std::stoul(name, nullptr, 16));
            }
            
            if (!name.starts_with("_id_"))
            {
                rel = fs::path{ games_rev.at(game) } / rel / name;
                rel.replace_extension(ext);
            }
            else
            {
                rel = fs::path{ games_rev.at(game) } / rel / file.filename();
            }
        }

        auto data = utils::file::read(file);
        utils::file::save(fs::path{ "renamed" } / rel, data);
        std::cout << fmt::format("renamed {} -> {}\n", file.filename().generic_string(), rel.generic_string());

        if (zt)
        {
            auto stack = utils::file::read(file.replace_extension(".cgsc.stack"));
            utils::file::save(fs::path{ "renamed" } / rel.replace_extension(".cgsc.stack"), stack);
            std::cout << fmt::format("renamed {} -> {}\n", file.filename().generic_string(), rel.generic_string());
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

std::unordered_map<std::string, std::vector<std::uint8_t>> files;

auto fs_read(std::string const& name) -> std::pair<buffer, std::vector<u8>>
{
    auto data = utils::file::read(fs::path{ name });
    
    if(name.ends_with(".gscbin") || (!name.ends_with(".gsh") && !name.ends_with(".gsc")))
    {
        asset s;
        s.deserialize(data);
        auto stk = utils::zlib::decompress(s.buffer, s.len);
        auto res = files.insert({ name, std::move(s.bytecode) });

        if (res.second)
        {
            return { {res.first->second.data(), res.first->second.size() }, std::move(stk) };
        }
    }
    else
    {
        return { {}, std::move(data) };
    }

    throw std::runtime_error("file read error");
}

auto init_iw5(mach mach) -> void
{
    if (contexts[game::iw5].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::iw5][mach] = std::make_unique<iw5_pc::context>();
            contexts[game::iw5][mach]->init(build::prod, fs_read);
            break;
        }
        case mach::ps3:
        {
            contexts[game::iw5][mach] = std::make_unique<iw5_ps::context>();
            contexts[game::iw5][mach]->init(build::prod, fs_read);
            break;
        }
        case mach::xb2:
        {
            contexts[game::iw5][mach] = std::make_unique<iw5_xb::context>();
            contexts[game::iw5][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_iw6(mach mach) -> void
{
    if (contexts[game::iw6].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::iw6][mach] = std::make_unique<iw6_pc::context>();
            contexts[game::iw6][mach]->init(build::prod, fs_read);
            break;
        }
        case mach::ps3:
        {
            contexts[game::iw6][mach] = std::make_unique<iw6_ps::context>();
            contexts[game::iw6][mach]->init(build::prod, fs_read);
            break;
        }
        case mach::xb2:
        {
            contexts[game::iw6][mach] = std::make_unique<iw6_xb::context>();
            contexts[game::iw6][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_iw7(mach mach) -> void
{
    if (contexts[game::iw7].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::iw7][mach] = std::make_unique<iw7::context>();
            contexts[game::iw7][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_iw8(mach mach) -> void
{
    if (contexts[game::iw8].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::iw8][mach] = std::make_unique<iw8::context>();
            contexts[game::iw8][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_iw9(mach mach) -> void
{
    if (contexts[game::iw9].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::iw9][mach] = std::make_unique<iw9::context>();
            contexts[game::iw9][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_s1(mach mach) -> void
{
    if (contexts[game::s1].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::s1][mach] = std::make_unique<s1_pc::context>();
            contexts[game::s1][mach]->init(build::prod, fs_read);
            break;
        }
        case mach::ps3:
        {
            contexts[game::s1][mach] = std::make_unique<s1_ps::context>();
            contexts[game::s1][mach]->init(build::prod, fs_read);
            break;
        }
        case mach::xb2:
        {
            contexts[game::s1][mach] = std::make_unique<s1_xb::context>();
            contexts[game::s1][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_s2(mach mach) -> void
{
    if (contexts[game::s2].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::s2][mach] = std::make_unique<s2::context>();
            contexts[game::s2][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_s4(mach mach) -> void
{
    if (contexts[game::s4].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::s4][mach] = std::make_unique<s4::context>();
            contexts[game::s4][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_h1(mach mach) -> void
{
    if (contexts[game::h1].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::h1][mach] = std::make_unique<h1::context>();
            contexts[game::h1][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_h2(mach mach) -> void
{
    if (contexts[game::h2].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::h2][mach] = std::make_unique<h2::context>();
            contexts[game::h2][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init(game game, mach mach) -> void
{
    funcs[mode::assemble] = assemble_file;
    funcs[mode::disassemble] = disassemble_file;
    funcs[mode::compile] = compile_file;
    funcs[mode::decompile] = decompile_file;
    funcs[mode::parse] = parse_file;
    funcs[mode::rename] = rename_file;

    if (!contexts.contains(game))
    {
        contexts.insert({ game, std::map<xsk::mach, std::unique_ptr<context>>() });
    }

    switch (game)
    {
        case game::iw5: init_iw5(mach); break;
        case game::iw6: init_iw6(mach); break;
        case game::iw7: init_iw7(mach); break;
        case game::iw8: init_iw8(mach); break;
        case game::iw9: init_iw9(mach); break;
        case game::s1:  init_s1(mach);  break;
        case game::s2:  init_s2(mach);  break;
        case game::s4:  init_s4(mach);  break;
        case game::h1:  init_h1(mach);  break;
        case game::h2:  init_h2(mach);  break;
        default: break;
    }
}

} // namespace xsk::gsc

namespace arc
{

std::map<game, std::map<mach, std::unique_ptr<context>>> contexts;
std::map<mode, std::function<void(game game, mach mach, fs::path const& file, fs::path rel)>> funcs;

void assemble_file(game game, mach mach, fs::path const& file, fs::path rel)
{
    try
    {
        if (game != game::t6)
            throw std::runtime_error("not implemented");

        if (file.extension() != ".gscasm" && file.extension() != ".cscasm")
            throw std::runtime_error("expected .gscasm or .cscasm file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((file.extension() == ".gscasm" ? ".gsc" : ".csc"));

        auto data = utils::file::read(file);
        auto outasm = contexts[game][mach]->source().parse_assembly(data);
        auto outbin = contexts[game][mach]->assembler().assemble(*outasm);

        utils::file::save(fs::path{ "assembled" } / rel, outbin.data, outbin.size);
        std::cout << fmt::format("assembled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

void disassemble_file(game game, mach mach, fs::path const& file, fs::path rel)
{
    try
    {
        if (file.extension() != ".gsc" && file.extension() != ".csc" && file.extension() != ".gscc" && file.extension() != ".cscc")
            throw std::runtime_error("expected .gsc or .csc file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((file.extension() == ".gsc" ? ".gscasm" : ".cscasm"));

        auto data = utils::file::read(file.string());
        auto outasm = contexts[game][mach]->disassembler().disassemble(data);
        auto outsrc = contexts[game][mach]->source().dump(*outasm);

        utils::file::save(fs::path{ "disassembled" } / rel, outsrc);
        std::cout << fmt::format("disassembled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

void compile_file(game game, mach mach, fs::path const& file, fs::path rel)
{
    try
    {
        if (game != game::t6)
            throw std::runtime_error("not implemented");

        if (file.extension() != ".gsc" && file.extension() != ".csc")
            throw std::runtime_error("expected .gsc or .csc file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename();

        auto data = utils::file::read(file);
        auto outasm = contexts[game][mach]->compiler().compile(file.string(), data);
        auto outbin = contexts[game][mach]->assembler().assemble(*outasm);

        utils::file::save(fs::path{ "compiled" } / rel, outbin.data, outbin.size);
        std::cout << fmt::format("compiled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

void decompile_file(game game, mach mach, fs::path const& file, fs::path rel)
{
    try
    {
        if (file.extension() != ".gsc" && file.extension() != ".csc" && file.extension() != ".gscc" && file.extension() != ".cscc")
            throw std::runtime_error("expected .gsc or .csc file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename();

        auto data = utils::file::read(file);

        auto outasm = contexts[game][mach]->disassembler().disassemble(data);
        auto outsrc = contexts[game][mach]->decompiler().decompile(*outasm);
        auto output = contexts[game][mach]->source().dump(*outsrc);

        utils::file::save(fs::path{ "decompiled" } / rel, output);
        std::cout << fmt::format("decompiled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

void parse_file(game, mach, fs::path const&, fs::path)
{
    std::cerr << fmt::format("not implemented for treyarch\n");
}

void rename_file(game, mach, fs::path const&, fs::path)
{
    std::cerr << fmt::format("not implemented for treyarch\n");
}

auto fs_read(std::string const& name) -> std::vector<u8>
{
    return utils::file::read(fs::path{ name });
}

auto init_t6(mach mach) -> void
{
    if (contexts[game::t6].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::t6][mach] = std::make_unique<t6::pc::context>();
            contexts[game::t6][mach]->init(build::prod, fs_read);
            break;
        }
        case mach::ps3:
        {
            contexts[game::t6][mach] = std::make_unique<t6::ps3::context>();
            contexts[game::t6][mach]->init(build::prod, fs_read);
            break;
        }
        case mach::xb2:
        {
            contexts[game::t6][mach] = std::make_unique<t6::xb2::context>();
            contexts[game::t6][mach]->init(build::prod, fs_read);
            break;
        }
        case mach::wiiu:
        {
            contexts[game::t6][mach] = std::make_unique<t6::wiiu::context>();
            contexts[game::t6][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_t7(mach mach) -> void
{
    if (contexts[game::t7].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::t7][mach] = std::make_unique<t7::context>();
            contexts[game::t7][mach]->init(build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_t8(mach /*mach*/) -> void
{
    throw std::runtime_error("not implemented");

    // if (contexts[game::t8].contains(mach)) return;

    // switch (mach)
    // {
    //     case mach::pc:
    //     {
    //         contexts[game::t8][mach] = std::make_unique<t8::context>();
    //         contexts[game::t8][mach]->init(build::prod, fs_read);
    //         break;
    //     }
    //     default:
    //         throw std::runtime_error("not implemented");
    // }
}

auto init_t9(mach /*mach*/) -> void
{
    throw std::runtime_error("not implemented");

    // if (contexts[game::t9].contains(mach)) return;

    // switch (mach)
    // {
    //     case mach::pc:
    //     {
    //         contexts[game::t9][mach] = std::make_unique<t9::context>();
    //         contexts[game::t9][mach]->init(build::prod, fs_read);
    //         break;
    //     }
    //     default:
    //         throw std::runtime_error("not implemented");
    // }
}

auto init(game game, mach mach) -> void
{
    funcs[mode::assemble] = assemble_file;
    funcs[mode::disassemble] = disassemble_file;
    funcs[mode::compile] = compile_file;
    funcs[mode::decompile] = decompile_file;
    funcs[mode::parse] = parse_file;
    funcs[mode::rename] = rename_file;

    if (!contexts.contains(game))
    {
        contexts.insert({ game, std::map<xsk::mach, std::unique_ptr<context>>() });
    }

    switch (game)
    {
        case game::t6: init_t6(mach); break;
        case game::t7: init_t7(mach); break;
        case game::t8: init_t8(mach); break;
        case game::t9: init_t9(mach); break;
        default: break;
    }
}

} // namespace xsk::arc

auto execute(mode mode, game game, mach mach, fs::path const& path) -> void
{
    gsc::init(game, mach);
    arc::init(game, mach);

    if (fs::is_directory(path))
    {
        for (auto const& entry : fs::recursive_directory_iterator(path))
        {
            if (entry.is_regular_file() && entry.path().extension() != ".stack")
            {
                auto rel = fs::relative(entry, path).remove_filename();

                if (game < game::t6)
                    gsc::funcs[mode](game, mach, entry.path().generic_string(), rel);
                else
                    arc::funcs[mode](game, mach, fs::path{ entry.path().generic_string(), fs::path::format::generic_format }, rel);
            }
        }
    }
    else if (fs::is_regular_file(path))
    {
        if (game < game::t6)
            gsc::funcs[mode](game, mach, path, fs::path{});
        else
            arc::funcs[mode](game, mach, fs::path(path, fs::path::format::generic_format), fs::path{});
    }
    else
    {
        std::cerr << fmt::format("bad path '{}'\n", path.generic_string());
    }
}

auto parse_flags(u32 argc, char** argv, mode& mode, game& game, mach& mach, fs::path& path) -> bool
{
    if (argc != 5) return false;

    auto arg = utils::string::to_lower(argv[1]);

    if (arg.at(0) == 'z')
    {
        arg.erase(arg.begin());
        gsc::zonetool = true;
    }

    auto const it1 = modes.find(arg);

    if (it1 != modes.end())
    {
        mode = it1->second;
    }
    else
    {
        std::cout << "[ERROR] unknown mode '" << argv[1] << "'.\n\n";
        return false;
    }

    arg = utils::string::to_lower(argv[2]);

    auto const it2 = games.find(arg);

    if (it2 != games.end())
    {
        game = it2->second;
    }
    else
    {
        std::cout << "[ERROR] unknown game '" << argv[2] << "'.\n\n";
        return false;
    }

    arg = utils::string::to_lower(argv[3]);

    auto const it3 = machs.find(arg);

    if (it3 != machs.end())
    {
        mach = it3->second;

        if (mach == mach::ps4 || mach == mach::ps5 || mach == mach::xb3 || mach == mach::xb4)
            mach = mach::pc;
    }
    else
    {
        std::cout << "[ERROR] unknown system '" << argv[3] << "'.\n\n";
        return false;
    }

    path = fs::path{ utils::string::fordslash(argv[4]), fs::path::format::generic_format };

    return true;
}

auto print_usage() -> void
{
    std::cout << "usage: gsc-tool <mode> <game> <system> <path>\n";
    std::cout << "\t* mode: asm, disasm, comp, decomp, parse, rename\n";
    std::cout << "\t* game: iw5, iw6, iw7, iw8, iw9, s1, s2, s4, h1, h2, t6, t7, t8, t9\n";
    std::cout << "\t* system: pc, ps3, ps4, ps5, xb2 (360), xb3 (One), xb4 (Series X|S), wiiu\n";
    std::cout << "\t* path: file or directory (recursive)\n";
    std::cin.get();
}

auto main(u32 argc, char** argv) -> void
{
    auto path = fs::path{};
    auto mode = mode::_;
    auto game = game::_;
    auto mach = mach::_;

    if (!parse_flags(argc, argv, mode, game, mach, path))
    {
        return print_usage();
    }

    execute(mode, game, mach, path);
}

} // namespace xsk

int main(int argc, char** argv)
{
    xsk::main(argc, argv);
    return 0;
}
