// Copyright 2025 xensik. All rights reserved.
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
#include "xsk/arc/engine/jup.hpp"
#include "xsk/version.hpp"
#include "cxxopts.hpp"

namespace fs = std::filesystem;

namespace xsk
{

enum class result : i32 { success = 0, failure = 1 };
enum class fenc { _, source, assembly, binary, src_bin };
enum class mode { _, assemble, disassemble, compile, decompile, parse, rename };
enum class game { _, iw5, iw6, iw7, iw8, iw9, s1, s2, s4, h1, h2, t6, t7, t8, t9, jup };
enum class mach { _, pc, ps3, ps4, ps5, xb2, xb3, xb4, wiiu };
enum class inst { _, server, client };

auto dry_run = false;
auto workdir = fs::current_path();

std::unordered_map<std::string_view, fenc> const gsc_exts =
{
    { ".gsc", fenc::source },
    { ".csc", fenc::source },
    { ".cgsc", fenc::binary },
    { ".ccsc", fenc::binary },
    { ".gscbin", fenc::binary },
    { ".cscbin", fenc::binary },
    { ".gscasm", fenc::assembly },
    { ".cscasm", fenc::assembly },
};

std::unordered_map<std::string_view, fenc> const arc_exts =
{
    { ".gsc", fenc::src_bin },
    { ".csc", fenc::src_bin },
    { ".gscc", fenc::binary },
    { ".cscc", fenc::binary },
    { ".gscasm", fenc::assembly },
    { ".cscasm", fenc::assembly },
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
    { "jup", game::jup },
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
    { game::jup, "jup" },
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

std::unordered_map<std::string_view, inst> const insts =
{
    { "server", inst::server },
    { "client", inst::client },
};

auto operator |=(result& lhs, result rhs) -> void
{
    lhs = static_cast<result>(static_cast<i32>(lhs) | static_cast<i32>(rhs));
}

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
std::map<mode, std::function<result(game game, mach mach, fs::path file, fs::path rel)>> funcs;
bool zonetool = false;

auto assemble_file(game game, mach mach, fs::path file, fs::path rel) -> result
{
    try
    {
        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((zonetool ? ".cgsc" : ".gscbin"));

        auto data = utils::file::read(file);
        auto outasm = contexts[game][mach]->source().parse_assembly(data);
        auto outbin = contexts[game][mach]->assembler().assemble(*outasm);

        if (true/*overwrite_prompt(file + (zonetool ? ".cgsc" : ".gscbin"))*/)
        {
            if (zonetool)
            {
                auto path = fs::path{ "assembled" } / rel;

                if (!dry_run)
                {
                    utils::file::save(path, std::get<0>(outbin).data, std::get<0>(outbin).size);
                    utils::file::save(path.replace_extension(".cgsc.stack"), std::get<1>(outbin).data, std::get<1>(outbin).size);
                }

                std::cout << std::format("assembled {}\n", rel.generic_string());
            }
            else
            {
                asset script;
                script.name = "GSC"s;

                script.bytecode.resize(std::get<0>(outbin).size);
                std::memcpy(script.bytecode.data(), std::get<0>(outbin).data, script.bytecode.size());

                script.buffer.resize(std::get<1>(outbin).size);
                std::memcpy(script.buffer.data(), std::get<1>(outbin).data, script.buffer.size());
                script.buffer = utils::zlib::compress(script.buffer);

                script.len = static_cast<u32>(std::get<1>(outbin).size);
                script.compressedLen = static_cast<u32>(script.buffer.size());
                script.bytecodeLen = static_cast<u32>(script.bytecode.size());

                auto result = script.serialize();

                if (!dry_run)
                    utils::file::save(fs::path{ "assembled" } / rel, result);

                std::cout << std::format("assembled {}\n", rel.generic_string());
            }
        }

        return result::success;
    }
    catch (std::exception const& e)
    {
        std::cerr << std::format("{} at {}\n", e.what(), file.generic_string());
        return result::failure;
    }
}

auto disassemble_file(game game, mach mach, fs::path file, fs::path rel) -> result
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
            rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension(file.extension() == ".gscbin" ? ".gscasm" : ".cscasm");

            auto data = utils::file::read(file);

            asset asset;
            asset.deserialize(data);

            script = std::move(asset.bytecode);
            stack = utils::zlib::decompress(asset.buffer, asset.len);
        }

        auto outasm = contexts[game][mach]->disassembler().disassemble(script, stack);
        auto outsrc = contexts[game][mach]->source().dump(*outasm);

        if (!dry_run)
            utils::file::save(fs::path{ "disassembled" } / rel, outsrc);

        std::cout << std::format("disassembled {}\n", rel.generic_string());
        return result::success;
    }
    catch (std::exception const& e)
    {
        std::cerr << std::format("{} at {}\n", e.what(), file.generic_string());
        return result::failure;
    }
}

auto compile_file(game game, mach mach, fs::path file, fs::path rel) -> result
{
    try
    {
        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((zonetool ? ".cgsc" : ".gscbin"));

        auto data = utils::file::read(file);
        auto outasm = contexts[game][mach]->compiler().compile(file.string(), data);
        auto outbin = contexts[game][mach]->assembler().assemble(*outasm);

        if (true/*overwrite_prompt(file + (zonetool ? ".cgsc" : ".gscbin"))*/)
        {
            if (zonetool)
            {
                auto path = fs::path{ "compiled" } / rel;

                if (!dry_run)
                {
                    utils::file::save(path, std::get<0>(outbin).data, std::get<0>(outbin).size);
                    utils::file::save(path.replace_extension(".cgsc.stack"), std::get<1>(outbin).data, std::get<1>(outbin).size);
                }

                std::cout << std::format("compiled {}\n", rel.generic_string());
            }
            else
            {
                asset script;
                script.name = "GSC"s;

                script.bytecode.resize(std::get<0>(outbin).size);
                std::memcpy(script.bytecode.data(), std::get<0>(outbin).data, script.bytecode.size());

                script.buffer.resize(std::get<1>(outbin).size);
                std::memcpy(script.buffer.data(), std::get<1>(outbin).data, script.buffer.size());
                script.buffer = utils::zlib::compress(script.buffer);

                script.len = static_cast<std::uint32_t>(std::get<1>(outbin).size);
                script.compressedLen = static_cast<std::uint32_t>(script.buffer.size());
                script.bytecodeLen = static_cast<std::uint32_t>(script.bytecode.size());

                auto result = script.serialize();

                if (!dry_run)
                    utils::file::save(fs::path{ "compiled" } / rel, result);

                std::cout << std::format("compiled {}\n", rel.generic_string());

                if ((contexts[game][mach]->build() & build::dev_maps) != build::prod)
                {
                    if (!dry_run)
                        utils::file::save(fs::path{ "compiled" } / fs::path{ "developer_maps" } / rel.replace_extension(".gscmap"), std::get<2>(outbin).data, std::get<2>(outbin).size);

                    std::cout << std::format("saved developer map {}\n", rel.generic_string());
                }
            }
        }

        return result::success;
    }
    catch (std::exception const& e)
    {
        std::cerr << std::format("{} at {}\n", e.what(), file.generic_string());
        return result::failure;
    }
}

auto decompile_file(game game, mach mach, fs::path file, fs::path rel) -> result
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
            rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((file.extension() == ".gscbin" ? ".gsc" : ".csc"));

            auto data = utils::file::read(file);

            asset asset;
            asset.deserialize(data);

            script = std::move(asset.bytecode);
            stack = utils::zlib::decompress(asset.buffer, asset.len);
        }

        auto outasm = contexts[game][mach]->disassembler().disassemble(script, stack);
        auto outast = contexts[game][mach]->decompiler().decompile(*outasm);
        auto outsrc = contexts[game][mach]->source().dump(*outast);

        if (!dry_run)
            utils::file::save(fs::path{ "decompiled" } / rel, outsrc);

        std::cout << std::format("decompiled {}\n", rel.generic_string());
        return result::success;
    }
    catch (std::exception const& e)
    {
        std::cerr << std::format("{} at {}\n", e.what(), file.generic_string());
        return result::failure;
    }
}

auto parse_file(game game, mach mach, fs::path file, fs::path rel) -> result
{
    try
    {
        rel = fs::path{ games_rev.at(game) } / rel / file.filename();

        auto data = utils::file::read(file);

        auto prog = contexts[game][mach]->source().parse_program(file.string(), data);

        if (!dry_run)
            utils::file::save(fs::path{ "parsed" } / rel, contexts[game][mach]->source().dump(*prog));

        std::cout << std::format("parsed {}\n", rel.generic_string());
        return result::success;
    }
    catch (std::exception const& e)
    {
        std::cerr << std::format("{} at {}\n", e.what(), file.generic_string());
        return result::failure;
    }
}

auto rename_file(game game, mach mach, fs::path file, fs::path rel) -> result
{
    try
    {
        if (file.extension() != ".cgsc" && file.extension() != ".gsc" && file.extension() != ".csc" && file.extension() != ".gscbin" && file.extension() != ".cscbin")
            return result::success;

        auto ext = file.extension();
        auto zt = file.extension() == ".cgsc";

        if (game == game::iw9)
        {
            return result::success;
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

        if (!dry_run)
            utils::file::save(fs::path{ "renamed" } / rel, data);

        std::cout << std::format("renamed {} -> {}\n", file.filename().generic_string(), rel.generic_string());

        if (zt)
        {
            auto stack = utils::file::read(file.replace_extension(".cgsc.stack"));

            if (!dry_run)
                utils::file::save(fs::path{ "renamed" } / rel.replace_extension(".cgsc.stack"), stack);

            std::cout << std::format("renamed {} -> {}\n", file.filename().generic_string(), rel.generic_string());
        }

        return result::success;
    }
    catch (std::exception const& e)
    {
        std::cerr << std::format("{} at {}\n", e.what(), file.generic_string());
        return result::failure;
    }
}

std::unordered_map<std::string, std::vector<std::uint8_t>> files;

auto fs_read(context const* ctx, std::string const& name) -> std::pair<buffer, std::vector<u8>>
{
    auto path = workdir / fs::path{ name };

    auto bin_ext = ".gscbin";
    auto gsc_ext = ".gsc";
    auto gsh_ext = ".gsh";

    if (ctx->instance() == gsc::instance::client)
    {
        bin_ext = ".cscbin";
        gsc_ext = ".csc";
    }

    if (!utils::file::exists(path))
    {
        auto const name_noext = path.replace_extension("").string();

        auto id = ctx->token_id(name_noext);
        if (id > 0)
        {
            path = fs::path{ std::to_string(id) + bin_ext };
        }

        if (!utils::file::exists(path))
        {
            path = fs::path{ name_noext + bin_ext };
        }
    }

    auto data = utils::file::read(path);

    if (path.extension().string() == bin_ext || (path.extension().string() != gsh_ext && path.extension().string() != gsc_ext))
    {
        asset s;
        s.deserialize(data);
        auto stk = utils::zlib::decompress(s.buffer, s.len);
        auto res = files.insert({ path.filename().string(), std::move(s.bytecode)});

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

auto init_iw5(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::iw5].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::iw5][mach] = std::make_unique<iw5_pc::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::iw5][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        case mach::ps3:
        {
            contexts[game::iw5][mach] = std::make_unique<iw5_ps::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::iw5][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        case mach::xb2:
        {
            contexts[game::iw5][mach] = std::make_unique<iw5_xb::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::iw5][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_iw6(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::iw6].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::iw6][mach] = std::make_unique<iw6_pc::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::iw6][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        case mach::ps3:
        {
            contexts[game::iw6][mach] = std::make_unique<iw6_ps::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::iw6][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        case mach::xb2:
        {
            contexts[game::iw6][mach] = std::make_unique<iw6_xb::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::iw6][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_iw7(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::iw7].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::iw7][mach] = std::make_unique<iw7::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::iw7][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_iw8(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::iw8].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::iw8][mach] = std::make_unique<iw8::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::iw8][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_iw9(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::iw9].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::iw9][mach] = std::make_unique<iw9::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::iw9][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_s1(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::s1].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::s1][mach] = std::make_unique<s1_pc::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::s1][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        case mach::ps3:
        {
            contexts[game::s1][mach] = std::make_unique<s1_ps::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::s1][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        case mach::xb2:
        {
            contexts[game::s1][mach] = std::make_unique<s1_xb::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::s1][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_s2(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::s2].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::s2][mach] = std::make_unique<s2::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::s2][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_s4(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::s4].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::s4][mach] = std::make_unique<s4::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::s4][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_h1(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::h1].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::h1][mach] = std::make_unique<h1::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::h1][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_h2(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::h2].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::h2][mach] = std::make_unique<h2::context>(inst == inst::client ? gsc::instance::client : gsc::instance::server);
            contexts[game::h2][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init(game game, mach mach, inst inst, bool dev) -> void
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
        case game::iw5: init_iw5(mach, inst, dev); break;
        case game::iw6: init_iw6(mach, inst, dev); break;
        case game::iw7: init_iw7(mach, inst, dev); break;
        case game::iw8: init_iw8(mach, inst, dev); break;
        case game::iw9: init_iw9(mach, inst, dev); break;
        case game::s1:  init_s1(mach, inst, dev);  break;
        case game::s2:  init_s2(mach, inst, dev);  break;
        case game::s4:  init_s4(mach, inst, dev);  break;
        case game::h1:  init_h1(mach, inst, dev);  break;
        case game::h2:  init_h2(mach, inst, dev);  break;
        default: break;
    }
}

} // namespace xsk::gsc

namespace arc
{

std::map<game, std::map<mach, std::unique_ptr<context>>> contexts;
std::map<mode, std::function<result(game game, mach mach, fs::path const& file, fs::path rel)>> funcs;
bool t6fixup = false;

auto assemble_file(game game, mach mach, fs::path const& file, fs::path rel) -> result
{
    try
    {
        if (game != game::t6)
            throw std::runtime_error("not implemented");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((file.extension() == ".gscasm" ? ".gsc" : ".csc"));

        auto data = utils::file::read(file);

        if (data.size() >= 4 && !std::memcmp(&data[0], "\x80GSC", 4))
        {
            std::cerr << std::format("{} at {}\n", "already assembled", file.generic_string());
            return result::success;
        }

        auto outasm = contexts[game][mach]->source().parse_assembly(data);
        auto outbin = contexts[game][mach]->assembler().assemble(*outasm);

        if (!dry_run)
            utils::file::save(fs::path{ "assembled" } / rel, outbin.first.data, outbin.first.size);

        std::cout << std::format("assembled {}\n", rel.generic_string());
        return result::success;
    }
    catch (std::exception const& e)
    {
        std::cerr << std::format("{} at {}\n", e.what(), file.generic_string());
        return result::failure;
    }
}

auto disassemble_file(game game, mach mach, fs::path const& file, fs::path rel) -> result
{
    try
    {
        if (game > game::t7)
            throw std::runtime_error("not implemented");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((file.extension().string().starts_with(".gsc") ? ".gscasm" : ".cscasm"));

        auto data = utils::file::read(file.string());
        auto outasm = contexts[game][mach]->disassembler().disassemble(data);
        auto outsrc = contexts[game][mach]->source().dump(*outasm);

        if (!dry_run)
            utils::file::save(fs::path{ "disassembled" } / rel, outsrc);

        std::cout << std::format("disassembled {}\n", rel.generic_string());
        return result::success;
    }
    catch (std::exception const& e)
    {
        std::cerr << std::format("{} at {}\n", e.what(), file.generic_string());
        return result::failure;
    }
}

auto compile_file(game game, mach mach, fs::path const& file, fs::path rel) -> result
{
    try
    {
        if (game != game::t6)
            throw std::runtime_error("not implemented");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename();

        auto data = utils::file::read(file);

        if (data.size() >= 4 && !std::memcmp(&data[0], "\x80GSC", 4))
        {
            std::cerr << std::format("{} at {}\n", "already compiled", file.generic_string());
            return result::success;
        }

        auto outasm = contexts[game][mach]->compiler().compile(file.string(), data);
        auto outbin = contexts[game][mach]->assembler().assemble(*outasm);

        if (!dry_run)
            utils::file::save(fs::path{ "compiled" } / rel, outbin.first.data, outbin.first.size);

        std::cout << std::format("compiled {}\n", rel.generic_string());

        if ((contexts[game][mach]->build() & build::dev_maps) != build::prod)
        {
            if (!dry_run)
                utils::file::save(fs::path{ "compiled" } / fs::path{ "developer_maps" } / rel.replace_extension((rel.extension().string().starts_with(".gsc") ? ".gscmap" : ".cscmap")), outbin.second.data, outbin.second.size);

            std::cout << std::format("saved developer map {}\n", rel.generic_string());
        }

        return result::success;
    }
    catch (std::exception const& e)
    {
        std::cerr << std::format("{} at {}\n", e.what(), file.generic_string());
        return result::failure;
    }
}

auto decompile_file(game game, mach mach, fs::path const& file, fs::path rel) -> result
{
    try
    {
        if (game > game::t7)
            throw std::runtime_error("not implemented");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename();

        auto data = utils::file::read(file);

        auto outasm = contexts[game][mach]->disassembler().disassemble(data);
        auto outsrc = contexts[game][mach]->decompiler().decompile(*outasm);
        auto output = contexts[game][mach]->source().dump(*outsrc);

        if (!dry_run)
            utils::file::save(fs::path{ "decompiled" } / rel, output);

        std::cout << std::format("decompiled {}\n", rel.generic_string());
        return result::success;
    }
    catch (std::exception const& e)
    {
        std::cerr << std::format("{} at {}\n", e.what(), file.generic_string());
        return result::failure;
    }
}

auto parse_file(game game, mach mach, fs::path file, fs::path rel) -> result
{
    try
    {
        if (game != game::t6)
            throw std::runtime_error("not implemented");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename();

        auto data = utils::file::read(file);

        if (data.size() >= 4 && !std::memcmp(&data[0], "\x80GSC", 4))
        {
            std::cerr << std::format("{} at {}\n", "already compiled", file.generic_string());
            return result::success;
        }

        auto prog = contexts[game][mach]->source().parse_program(file.string(), data);

        if (!dry_run)
            utils::file::save(fs::path{ "parsed" } / rel, contexts[game][mach]->source().dump(*prog));

        std::cout << std::format("parsed {}\n", rel.generic_string());
        return result::success;
    }
    catch (std::exception const& e)
    {
        std::cerr << std::format("{} at {}\n", e.what(), file.generic_string());
        return result::failure;
    }
}

auto rename_file(game, mach, fs::path const&, fs::path) -> result
{
    std::cerr << std::format("not implemented for treyarch\n");
    return result::failure;
}

auto fs_read(std::string const& name) -> std::vector<u8>
{
    auto path = workdir / fs::path{ name };

    if (!utils::file::exists(path))
    {
        throw std::runtime_error("file not found: " + path.string());
    }

    return utils::file::read(path);
}

auto init_t6(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::t6].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::t6][mach] = std::make_unique<t6::pc::context>(inst == inst::client ? arc::instance::client : arc::instance::server);
            contexts[game::t6][mach]->init(dev ? build::dev : build::prod, fs_read);
            contexts[game::t6][mach]->fixup(t6fixup);
            break;
        }
        case mach::ps3:
        {
            contexts[game::t6][mach] = std::make_unique<t6::ps3::context>(inst == inst::client ? arc::instance::client : arc::instance::server);
            contexts[game::t6][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        case mach::xb2:
        {
            contexts[game::t6][mach] = std::make_unique<t6::xb2::context>(inst == inst::client ? arc::instance::client : arc::instance::server);
            contexts[game::t6][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        case mach::wiiu:
        {
            contexts[game::t6][mach] = std::make_unique<t6::wiiu::context>(inst == inst::client ? arc::instance::client : arc::instance::server);
            contexts[game::t6][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_t7(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::t7].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::t7][mach] = std::make_unique<t7::context>(inst == inst::client ? arc::instance::client : arc::instance::server);
            contexts[game::t7][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_t8(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::t8].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::t8][mach] = std::make_unique<t8::context>(inst == inst::client ? arc::instance::client : arc::instance::server);
            contexts[game::t8][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_t9(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::t9].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::t9][mach] = std::make_unique<t9::context>(inst == inst::client ? arc::instance::client : arc::instance::server);
            contexts[game::t9][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init_jup(mach mach, inst inst, bool dev) -> void
{
    if (contexts[game::jup].contains(mach)) return;

    switch (mach)
    {
        case mach::pc:
        {
            contexts[game::jup][mach] = std::make_unique<jup::context>(inst == inst::client ? arc::instance::client : arc::instance::server);
            contexts[game::jup][mach]->init(dev ? build::dev : build::prod, fs_read);
            break;
        }
        default:
            throw std::runtime_error("not implemented");
    }
}

auto init(game game, mach mach, inst inst, bool dev) -> void
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
        case game::t6: init_t6(mach, inst, dev); break;
        case game::t7: init_t7(mach, inst, dev); break;
        case game::t8: init_t8(mach, inst, dev); break;
        case game::t9: init_t9(mach, inst, dev); break;
        case game::jup: init_jup(mach, inst, dev); break;
        default: break;
    }
}

} // namespace xsk::arc

auto extension_match(fs::path const& ext, mode mode, game game) -> bool
{
    auto enc = fenc::_;

    if (game < game::t6 && gsc_exts.contains(ext.string()))
        enc = gsc_exts.at(ext.string());
    else if (arc_exts.contains(ext.string()))
        enc = arc_exts.at(ext.string());

    switch (mode)
    {
        case mode::assemble:    return enc == fenc::assembly;
        case mode::disassemble: return enc == fenc::binary || enc == fenc::src_bin;
        case mode::compile:     return enc == fenc::source || enc == fenc::src_bin;
        case mode::decompile:   return enc == fenc::binary || enc == fenc::src_bin;
        case mode::parse:       return enc == fenc::source || enc == fenc::src_bin;
        case mode::rename:      return enc != fenc::_;
        default:                return false;
    }
}

auto execute(mode mode, game game, mach mach, inst inst, fs::path const& path, bool dev) -> result
{
    gsc::init(game, mach, inst, dev);
    arc::init(game, mach, inst, dev);

    if (fs::is_directory(path))
    {
        auto exit_code = result::success;

        for (auto const& entry : fs::recursive_directory_iterator(path))
        {
            if (entry.is_regular_file() && extension_match(entry.path().extension(), mode, game))
            {
                auto rel = fs::relative(entry, path).remove_filename();

                if (game < game::t6)
                    exit_code |= gsc::funcs[mode](game, mach, entry.path().generic_string(), rel);
                else
                    exit_code |= arc::funcs[mode](game, mach, fs::path{ entry.path().generic_string(), fs::path::format::generic_format }, rel);
            }
        }

        return exit_code;
    }
    else if (fs::is_regular_file(path))
    {
        if (!extension_match(path.extension(), mode, game))
        {
            std::cerr << std::format("bad extension '{}'\n", path.extension().string());
            return result::failure;
        }

        if (game < game::t6)
            return gsc::funcs[mode](game, mach, path, fs::path{});
        else
            return arc::funcs[mode](game, mach, fs::path(path, fs::path::format::generic_format), fs::path{});
    }
    else
    {
        std::cerr << std::format("bad path '{}'\n", path.generic_string());
        return result::failure;
    }
}

auto parse_mode(std::string const& arg, mode& out) -> bool
{
    auto mode = utils::string::to_lower(arg);

    auto const it = modes.find(mode);

    if (it != modes.end())
    {
        out = it->second;
        return true;
    }

    return false;
}

auto parse_game(std::string const& arg, game& out) -> bool
{
    auto game = utils::string::to_lower(arg);

    auto const it = games.find(game);

    if (it != games.end())
    {
        out = it->second;
        return true;
    }

    return false;
}

auto parse_system(std::string const& arg, mach& out) -> bool
{
    auto mach = utils::string::to_lower(arg);

    auto const it = machs.find(mach);

    if (it != machs.end())
    {
        out = it->second;

        if (out == mach::ps4 || out == mach::ps5 || out == mach::xb3 || out == mach::xb4)
            out = mach::pc;

        return true;
    }

    return false;
}

auto parse_instance(std::string const& arg, inst& out) -> bool
{
    auto inst = utils::string::to_lower(arg);

    auto const it = insts.find(inst);

    if (it != insts.end())
    {
        out = it->second;
        return true;
    }

    return false;
}

auto branding() -> std::string
{
    return std::format("GSC Tool {} created by xensik\n", XSK_VERSION_STR);
}

auto main(u32 argc, char** argv) -> result
{
    cxxopts::Options options("gsc-tool", branding());
    options.custom_help("[OPTIONS...]");
    options.positional_help("<path>");
    options.set_width(120);

    options.add_options()
        ("m,mode","[REQUIRED] one of: asm, disasm, comp, decomp, parse, rename", cxxopts::value<std::string>(), "<mode>")
        ("g,game", "[REQUIRED] one of: iw5, iw6, iw7, iw8, iw9, s1, s2, s4, h1, h2, t6, t7, t8, t9, jup", cxxopts::value<std::string>(), "<game>")
        ("s,system", "[REQUIRED] one of: pc, ps3, ps4, ps5, xb2 (360), xb3 (One), xb4 (Series X|S), wiiu", cxxopts::value<std::string>(), "<system>")
        ("i,instance", "Instance to use (server, client).", cxxopts::value<std::string>()->default_value("server"), "<instance>")
        ("p,path", "File or directory to process.", cxxopts::value<std::string>())
        ("w,workdir", "Working directory for includes or headers.", cxxopts::value<std::string>()->default_value("."), "<path>")
        ("y,dry", "Dry run (do not write files).", cxxopts::value<bool>()->implicit_value("true"))
        ("d,dev", "Enable developer mode (dev blocks & generate bytecode map).", cxxopts::value<bool>()->implicit_value("true"))
        ("z,zonetool", "Enable zonetool mode (use .cgsc files).", cxxopts::value<bool>()->implicit_value("true"))
        ("t6fixup", "Decompile t6 files from broken compilers.", cxxopts::value<bool>()->implicit_value("true"))
        ("h,help", "Display help.")
        ("v,version", "Display version.");

    options.parse_positional({ "path" });

    try
    {
        auto result = options.parse(argc, argv);

        if (argc == 1 || result.count("help"))
        {
            std::cout << options.help() << std::endl;
            return result::success;
        }

        if (result.count("version"))
        {
            std::cout << branding();
            return result::success;
        }

        if(!result.count("mode"))
        {
            std::cerr << "[ERROR] missing required argument <mode>\n";
            return result::failure;
        }

        if (!result.count("game"))
        {
            std::cerr << "[ERROR] missing required argument <game>\n";
            return result::failure;
        }

        if (!result.count("system"))
        {
            std::cerr << "[ERROR] missing required argument <system>\n";
            return result::failure;
        }

        if (!result.count("path"))
        {
            std::cerr << "[ERROR] missing required argument <path>\n";
            return result::failure;
        }

        auto mode_arg = utils::string::to_lower(result["mode"].as<std::string>());
        auto game_arg = utils::string::to_lower(result["game"].as<std::string>());
        auto mach_arg = utils::string::to_lower(result["system"].as<std::string>());
        auto inst_arg = utils::string::to_lower(result["instance"].as<std::string>());
        auto path_arg = result["path"].as<std::string>();
        auto wdir_arg = result["workdir"].as<std::string>();
        auto path = fs::path{};
        auto mode = mode::_;
        auto game = game::_;
        auto mach = mach::_;
        auto inst = inst::_;
        auto dev = result["dev"].as<bool>();
        gsc::zonetool = result["zonetool"].as<bool>();
        arc::t6fixup = result["t6fixup"].as<bool>();
        dry_run = result["dry"].as<bool>();

        if(!parse_mode(mode_arg, mode))
        {
            std::cerr << "[ERROR] unknown mode '" << mode_arg << "'\n";
            return result::failure;
        }

        if (!parse_game(game_arg, game))
        {
            std::cerr << "[ERROR] unknown game '" << game_arg << "'\n";
            return result::failure;
        }

        if (!parse_system(mach_arg, mach))
        {
            std::cerr << "[ERROR] unknown system '" << mach_arg << "'\n";
            return result::failure;
        }

        if (!parse_instance(inst_arg, inst))
        {
            std::cerr << "[ERROR] unknown instance '" << inst_arg << "'\n";
            return result::failure;
        }

        path = fs::path{ utils::string::fordslash(path_arg), fs::path::format::generic_format };
        workdir = fs::path{ utils::string::fordslash(wdir_arg), fs::path::format::generic_format };

        if (!workdir.is_absolute())
        {
            workdir = fs::absolute(workdir);
        }

        std::cout << branding();
        return execute(mode, game, mach, inst, path, dev);
    }
    catch (std::exception const& e)
    {
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return result::failure;
    }
}

} // namespace xsk

int main(int argc, char** argv)
{
    return static_cast<int>(xsk::main(argc, argv));
}
