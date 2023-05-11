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
#include "xsk/arc/engine/t6.hpp"
#include "xsk/arc/engine/t7.hpp"
#include "xsk/arc/engine/t8.hpp"
#include "xsk/arc/engine/t9.hpp"

namespace fs = std::filesystem;

namespace xsk
{

enum class encd { _, source, assembly, binary };
enum class mode { _, assemble, disassemble, compile, decompile, parse, rename };
enum class game { _, iw5ps, iw5xb, iw6ps, iw6xb, s1ps, s1xb, iw5, iw6, iw7, iw8, iw9, s1, s2, s4, h1, h2, t6, t7, t8, t9 };

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
    { "iw5ps", game::iw5ps },
    { "iw5xb", game::iw5xb },
    { "iw6ps", game::iw6ps },
    { "iw6xb", game::iw6xb },
    { "s1ps", game::s1ps },
    { "s1xb", game::s1xb },
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
    { game::iw5ps, "iw5ps", },
    { game::iw5xb, "iw5xb" },
    { game::iw6ps, "iw6ps" },
    { game::iw6xb, "iw6xb" },
    { game::s1ps, "s1ps" },
    { game::s1xb, "s1xb" },
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

std::map<mode, encd> const encds =
{
    { mode::assemble , encd::assembly },
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

std::map<game, std::unique_ptr<context>> contexts;
std::map<mode, std::function<void(game game, fs::path file, fs::path rel)>> funcs;
bool zonetool = false;

auto assemble_file(game game, fs::path file, fs::path rel) -> void
{
    try
    {
        if (file.extension() != ".gscasm")
            throw std::runtime_error("expected .gscasm file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((zonetool ? ".cgsc" : ".gscbin"));

        auto data = utils::file::read(file);
        auto outasm = contexts[game]->source().parse_assembly(data);
        auto outbin = contexts[game]->assembler().assemble(*outasm);

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

auto disassemble_file(game game, fs::path file, fs::path rel) -> void
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

        auto outasm = contexts[game]->disassembler().disassemble(script, stack);
        auto outsrc = contexts[game]->source().dump(*outasm);

        utils::file::save(fs::path{ "disassembled" } / rel, outsrc);
        std::cout << fmt::format("disassembled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

auto compile_file(game game, fs::path file, fs::path rel) -> void
{
    try
    {
        if (file.extension() != ".gsc")
            throw std::runtime_error("expected .gsc file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((zonetool ? ".cgsc" : ".gscbin"));

        auto data = utils::file::read(file);
        auto outasm = contexts[game]->compiler().compile(file.string(), data);
        auto outbin = contexts[game]->assembler().assemble(*outasm);

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

auto decompile_file(game game, fs::path file, fs::path rel) -> void
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

        auto outasm = contexts[game]->disassembler().disassemble(script, stack);
        auto outast = contexts[game]->decompiler().decompile(*outasm);
        auto outsrc = contexts[game]->source().dump(*outast);

        utils::file::save(fs::path{ "decompiled" } / rel, outsrc);
        std::cout << fmt::format("decompiled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

auto parse_file(game game, fs::path file, fs::path rel) -> void
{
    try
    {
        if (file.extension() != ".gsc")
            throw std::runtime_error("expected .gsc file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename();

        auto data = utils::file::read(file);

        auto prog = contexts[game]->source().parse_program(file.string(), data);
        utils::file::save(fs::path{ "parsed" } / rel, contexts[game]->source().dump(*prog));
        std::cout << fmt::format("parsed {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

auto rename_file(game game, fs::path file, fs::path rel) -> void
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
                name = contexts[game]->token_name(std::stoul(name));
            }
            else if (utils::string::is_hex_number(name))
            {
                name = contexts[game]->token_name(std::stoul(name, nullptr, 16));
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

auto fs_callback(std::string const& name) -> std::pair<buffer, std::vector<u8>>
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

auto init_iw5() -> void
{
    if (!contexts.contains(game::iw5))
    {
        contexts[game::iw5] = std::make_unique<iw5_pc::context>();
        contexts[game::iw5]->init(build::prod, fs_callback);
    }
}

auto init_iw5_ps() -> void
{
    if (!contexts.contains(game::iw5ps))
    {
        contexts[game::iw5ps] = std::make_unique<iw5_ps::context>();
        contexts[game::iw5ps]->init(build::prod, fs_callback);
    }
}

auto init_iw5_xb() -> void
{
    if (!contexts.contains(game::iw5xb))
    {
        contexts[game::iw5xb] = std::make_unique<iw5_xb::context>();
        contexts[game::iw5xb]->init(build::prod, fs_callback);
    }
}

auto init_iw6() -> void
{
    if (!contexts.contains(game::iw6))
    {
        contexts[game::iw6] = std::make_unique<iw6_pc::context>();
        contexts[game::iw6]->init(build::prod, fs_callback);
    }
}

auto init_iw6_ps() -> void
{
    if (!contexts.contains(game::iw6ps))
    {
        contexts[game::iw6ps] = std::make_unique<iw6_ps::context>();
        contexts[game::iw6ps]->init(build::prod, fs_callback);
    }
}

auto init_iw6_xb() -> void
{
    if (!contexts.contains(game::iw6xb))
    {
        contexts[game::iw6xb] = std::make_unique<iw6_xb::context>();
        contexts[game::iw6xb]->init(build::prod, fs_callback);
    }
}

auto init_iw7() -> void
{
    if (!contexts.contains(game::iw7))
    {
        contexts[game::iw7] = std::make_unique<iw7::context>();
        contexts[game::iw7]->init(build::prod, fs_callback);
    }
}

auto init_iw8() -> void
{
    if (!contexts.contains(game::iw8))
    {
        contexts[game::iw8] = std::make_unique<iw8::context>();
        contexts[game::iw8]->init(build::prod, fs_callback);
    }
}

auto init_iw9() -> void
{
    if (!contexts.contains(game::iw9))
    {
        contexts[game::iw9] = std::make_unique<iw9::context>();
        contexts[game::iw9]->init(build::prod, fs_callback);
    }
}

auto init_s1() -> void
{
    if (!contexts.contains(game::s1))
    {
        contexts[game::s1] = std::make_unique<s1_pc::context>();
        contexts[game::s1]->init(build::prod, fs_callback);
    }
}

auto init_s1_ps() -> void
{
    if (!contexts.contains(game::s1ps))
    {
        contexts[game::s1ps] = std::make_unique<s1_ps::context>();
        contexts[game::s1ps]->init(build::prod, fs_callback);
    }
}

auto init_s1_xb() -> void
{
    if (!contexts.contains(game::s1xb))
    {
        contexts[game::s1xb] = std::make_unique<s1_xb::context>();
        contexts[game::s1xb]->init(build::prod, fs_callback);
    }
}

auto init_s2() -> void
{
    if (!contexts.contains(game::s2))
    {
        contexts[game::s2] = std::make_unique<s2::context>();
        contexts[game::s2]->init(build::prod, fs_callback);
    }
}

auto init_s4() -> void
{
    if (!contexts.contains(game::s4))
    {
        contexts[game::s4] = std::make_unique<s4::context>();
        contexts[game::s4]->init(build::prod, fs_callback);
    }
}

auto init_h1() -> void
{
    if (!contexts.contains(game::h1))
    {
        contexts[game::h1] = std::make_unique<h1::context>();
        contexts[game::h1]->init(build::prod, fs_callback);
    }
}

auto init_h2() -> void
{
    if (!contexts.contains(game::h2))
    {
        contexts[game::h2] = std::make_unique<h2::context>();
        contexts[game::h2]->init(build::prod, fs_callback);
    }
}

auto init(game game) -> void
{
    funcs[mode::assemble] = assemble_file;
    funcs[mode::disassemble] = disassemble_file;
    funcs[mode::compile] = compile_file;
    funcs[mode::decompile] = decompile_file;
    funcs[mode::parse] = parse_file;
    funcs[mode::rename] = rename_file;

    switch (game)
    {
        case game::iw5:   init_iw5();    break;
        case game::iw5ps: init_iw5_ps(); break;
        case game::iw5xb: init_iw5_xb(); break;
        case game::iw6:   init_iw6();    break;
        case game::iw6ps: init_iw6_ps(); break;
        case game::iw6xb: init_iw6_xb(); break;
        case game::iw7:   init_iw7();    break;
        case game::iw8:   init_iw8();    break;
        case game::iw9:   init_iw9();    break;
        case game::s1:    init_s1();     break;
        case game::s1ps:  init_s1_ps();  break;
        case game::s1xb:  init_s1_xb();  break;
        case game::s2:    init_s2();     break;
        case game::s4:    init_s4();     break;
        case game::h1:    init_h1();     break;
        case game::h2:    init_h2();     break;
        default: break;
    }
}

} // namespace xsk::gsc

namespace arc
{

std::map<game, std::unique_ptr<context>> contexts;
std::map<mode, std::function<void(game game, fs::path const& file, fs::path rel)>> funcs;

void assemble_file(game game, fs::path const& file, fs::path rel)
{
    try
    {
        if (game != game::t6)
            throw std::runtime_error("not implemented");

        if (file.extension() != ".gscasm" && file.extension() != ".cscasm")
            throw std::runtime_error("expected .gscasm or .cscasm file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((file.extension() == ".gscasm" ? ".gsc" : ".csc"));

        auto data = utils::file::read(file);
        auto outasm = contexts[game]->source().parse_assembly(data);
        auto outbin = contexts[game]->assembler().assemble(*outasm);

        utils::file::save(fs::path{ "assembled" } / rel, outbin.data, outbin.size);
        std::cout << fmt::format("assembled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

void disassemble_file(game game, fs::path const& file, fs::path rel)
{
    try
    {
        if (file.extension() != ".gsc" && file.extension() != ".csc" && file.extension() != ".gscc" && file.extension() != ".cscc")
            throw std::runtime_error("expected .gsc or .csc file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename().replace_extension((file.extension() == ".gsc" ? ".gscasm" : ".cscasm"));

        auto data = utils::file::read(file.string());
        auto outasm = contexts[game]->disassembler().disassemble(data);
        auto outsrc = contexts[game]->source().dump(*outasm);

        utils::file::save(fs::path{ "disassembled" } / rel, outsrc);
        std::cout << fmt::format("disassembled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

void compile_file(game game, fs::path const& file, fs::path rel)
{
    try
    {
        if (game != game::t6)
            throw std::runtime_error("not implemented");

        if (file.extension() != ".gsc" && file.extension() != ".csc")
            throw std::runtime_error("expected .gsc or .csc file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename();

        auto data = utils::file::read(file);
        auto outasm = contexts[game]->compiler().compile(file.string(), data);
        auto outbin = contexts[game]->assembler().assemble(*outasm);

        utils::file::save(fs::path{ "compiled" } / rel, outbin.data, outbin.size);
        std::cout << fmt::format("compiled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

void decompile_file(game game, fs::path const& file, fs::path rel)
{
    try
    {
        if (file.extension() != ".gsc" && file.extension() != ".csc" && file.extension() != ".gscc" && file.extension() != ".cscc")
            throw std::runtime_error("expected .gsc or .csc file");

        rel = fs::path{ games_rev.at(game) } / rel / file.filename();

        auto data = utils::file::read(file);

        auto outasm = contexts[game]->disassembler().disassemble(data);
        auto outsrc = contexts[game]->decompiler().decompile(*outasm);
        auto output = contexts[game]->source().dump(*outsrc);

        utils::file::save(fs::path{ "decompiled" } / rel, output);
        std::cout << fmt::format("decompiled {}\n", rel.generic_string());
    }
    catch (std::exception const& e)
    {
        std::cerr << fmt::format("{} at {}\n", e.what(), file.generic_string());
    }
}

void parse_file(game, fs::path const&, fs::path)
{
    std::cerr << fmt::format("not implemented for t6\n");
}

void rename_file(game, fs::path const&, fs::path)
{
    std::cerr << fmt::format("not implemented for t6\n");
}

auto fs_read(std::string const& name) -> std::vector<u8>
{
    return utils::file::read(fs::path{ name });
}

auto init_t6() -> void
{
    if (!contexts.contains(game::t6))
    {
        contexts[game::t6] = std::make_unique<t6::context>();
        contexts[game::t6]->init(build::prod, fs_read);
    }
}

auto init_t7() -> void
{
    if (!contexts.contains(game::t7))
    {
        contexts[game::t7] = std::make_unique<t7::context>();
        contexts[game::t7]->init(build::prod, fs_read);
    }
}

auto init_t8() -> void
{
    throw std::runtime_error("not implemented");

    if (!contexts.contains(game::t8))
    {
        contexts[game::t8] = std::make_unique<t8::context>();
        contexts[game::t8]->init(build::prod, fs_read);
    }
}

auto init_t9() -> void
{
    throw std::runtime_error("not implemented");

    if (!contexts.contains(game::t9))
    {
        contexts[game::t9] = std::make_unique<t9::context>();
        contexts[game::t9]->init(build::prod, fs_read);
    }
}

auto init(game game) -> void
{
    funcs[mode::assemble] = assemble_file;
    funcs[mode::disassemble] = disassemble_file;
    funcs[mode::compile] = compile_file;
    funcs[mode::decompile] = decompile_file;
    funcs[mode::parse] = parse_file;
    funcs[mode::rename] = rename_file;

    switch (game)
    {
        case game::t6: init_t6(); break;
        case game::t7: init_t7(); break;
        case game::t8: init_t8(); break;
        case game::t9: init_t9(); break;
        default: break;
    }
}

} // namespace xsk::arc

auto execute(mode mode, game game, fs::path const& path) -> void
{
    gsc::init(game);
    arc::init(game);

    if (fs::is_directory(path))
    {
        for (auto const& entry : fs::recursive_directory_iterator(path))
        {
            if (entry.is_regular_file() && entry.path().extension() != ".stack")
            {
                auto rel = fs::relative(entry, path).remove_filename();

                if (game < game::t6)
                    gsc::funcs[mode](game, entry.path().generic_string(), rel);
                else
                    arc::funcs[mode](game, fs::path{ entry.path().generic_string(), fs::path::format::generic_format }, rel);
            }
        }
    }
    else if (fs::is_regular_file(path))
    {
        if (game < game::t6)
            gsc::funcs[mode](game, path, fs::path{});
        else
            arc::funcs[mode](game, fs::path(path, fs::path::format::generic_format), fs::path{});
    }
    else
    {
        std::cerr << fmt::format("bad path '{}'\n", path.generic_string());
    }
}

auto parse_flags(u32 argc, char** argv, game& game, mode& mode, fs::path& path) -> bool
{
    if (argc != 4) return false;

    auto arg = utils::string::to_lower(argv[1]);

    if (arg.at(0) == 'z')
    {
        arg.erase(arg.begin());
        gsc::zonetool = true;
    }

    auto const it = modes.find(arg);

    if (it != modes.end())
    {
        mode = it->second;
    }
    else
    {
        std::cout << "[ERROR] unknown mode '" << argv[1] << "'.\n\n";
        return false;
    }

    arg = utils::string::to_lower(argv[2]);

    auto const itr = games.find(arg);

    if (itr != games.end())
    {
        game = itr->second;
    }
    else
    {
        std::cout << "[ERROR] unknown game '" << argv[2] << "'.\n\n";
        return false;
    }

    path = fs::path{ utils::string::fordslash(argv[3]), fs::path::format::generic_format };

    return true;
}

auto print_usage() -> void
{
    std::cout << "usage: gsc-tool <mode> <game> <path>\n";
    std::cout << "\t* modes: asm, disasm, comp, decomp, parse\n";
    std::cout << "\t* games: iw5ps, iw5xb, iw6ps, iw6xb, s1ps, s1xb, iw5, iw6, iw7, iw8, iw9, s1, s2, s4, h1, h2, t6\n";
    std::cout << "\t* paths: file or directory (recursive)\n";
    std::cin.get();
}

auto main(u32 argc, char** argv) -> void
{
    auto path = fs::path{};
    auto mode = mode::_;
    auto game = game::_;

    if (!parse_flags(argc, argv, game, mode, path))
    {
        return print_usage();
    }

    execute(mode, game, path);
}

} // namespace xsk

int main(int argc, char** argv)
{
    xsk::main(argc, argv);
    return 0;
}
