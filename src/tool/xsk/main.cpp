// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "utils/xsk/utils.hpp"
#include "experimental/iw5c/xsk/iw5c.hpp"
#include "iw5/xsk/iw5.hpp"
#include "iw6/xsk/iw6.hpp"
#include "iw7/xsk/iw7.hpp"
#include "iw8/xsk/iw8.hpp"
#include "s1/xsk/s1.hpp"
#include "s2/xsk/s2.hpp"
#include "s4/xsk/s4.hpp"
#include "h1/xsk/h1.hpp"
#include "h2/xsk/h2.hpp"
#include "t6/xsk/t6.hpp"

namespace xsk
{

enum class encd { _, source, assembly, binary };
enum class mode { _, assemble, disassemble, compile, decompile };
enum class game { _, iw5c, iw5, iw6, iw7, iw8, s1, s2, s4, h1, h2, t6 };

const std::map<std::string, encd> exts =
{
    { ".gsc", encd::source },
    { ".cgsc", encd::binary },
    { ".gscbin", encd::binary },
    { ".gscasm", encd::assembly },
};

const std::map<std::string, mode> modes =
{
    { "asm", mode::assemble },
    { "disasm", mode::disassemble },
    { "comp", mode::compile },
    { "decomp", mode::decompile },
};

const std::map<std::string, game> games =
{
    { "iw5c", game::iw5c },
    { "iw5", game::iw5 },
    { "iw6", game::iw6 },
    { "iw7", game::iw7 },
    { "iw8", game::iw8 },
    { "s1", game::s1 },
    { "s2", game::s2 },
    { "s4", game::s4 },
    { "h1", game::h1 },
    { "h2", game::h2 },
    { "t6", game::t6 },
};

const std::map<mode, encd> encds =
{
    { mode::assemble , encd::assembly },
    { mode::disassemble, encd::binary },
    { mode::compile, encd::source },
    { mode::decompile, encd::binary },
};

auto overwrite_prompt(const std::string& file) -> bool
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

std::map<game, context::ptr> contexts;
std::map<mode, std::function<void(game game, std::string file)>> funcs;
bool zonetool = false;

auto choose_resolver_file_name(uint32_t id, game& game) -> std::string
{
    switch (game)
    {
        case game::iw5c:
            return iw5c::resolver::token_name(static_cast<std::uint16_t>(id));
        case game::iw5:
            return iw5::resolver::token_name(static_cast<std::uint16_t>(id));
        case game::iw6:
            return iw6::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::iw7:
            return iw7::resolver::file_name(id);
        case game::iw8:
            return iw8::resolver::file_name(id);
        case game::s1:
            return s1::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::s2:
            return s2::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::s4:
            return s4::resolver::file_name(id);
        case game::h1:
            return h1::resolver::token_name(static_cast<std::uint16_t>(id));
        case game::h2:
            return h2::resolver::token_name(static_cast<std::uint16_t>(id));
        default:
            return "";
    }
}

void assemble_file(game game, std::string file)
{
    try
    {
        auto& assembler = contexts[game]->assembler();
        const auto ext = std::string(".gscasm");
        const auto extpos = file.find(ext);

        if (extpos != std::string::npos)
        {
            file.replace(extpos, ext.length(), "");
        }

        auto data = utils::file::read(file + ext);

        assembler.assemble(file, data);

        if (overwrite_prompt(file + (zonetool ? ".cgsc" : ".gscbin")))
        {
            if (zonetool)
            {
                utils::file::save("assembled/" + file + ".cgsc", assembler.output_script());
                utils::file::save("assembled/" + file + ".cgsc.stack", assembler.output_stack());
                std::cout << "assembled " << file << ".cgsc\n";
            }
            else
            {
                asset script;

                auto uncompressed = assembler.output_stack();
                auto compressed = utils::zlib::compress(uncompressed);

                script.name = file;
                script.bytecode = assembler.output_script();
                script.buffer = std::move(compressed);
                script.len = static_cast<std::uint32_t>(uncompressed.size());
                script.compressedLen = static_cast<std::uint32_t>(script.buffer.size());
                script.bytecodeLen = static_cast<std::uint32_t>(script.bytecode.size());

                auto output = script.serialize();
                utils::file::save("assembled/" + file + ".gscbin", output);
                std::cout << "assembled " << file << ".gscbin\n";
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void disassemble_file(game game, std::string file)
{
    try
    {
        auto& disassembler = contexts[game]->disassembler();

        if (zonetool)
        {
            if (file.find(".gscbin") != std::string::npos) return;

            if (file.find(".stack") != std::string::npos)
            {
                std::cerr << "Cannot disassemble stack files\n";
                return;
            }

            const auto ext = std::string(".cgsc");
            const auto extpos = file.find(ext);

            if (extpos != std::string::npos)
            {
                file.replace(extpos, ext.length(), "");
            }

            auto script = utils::file::read(file + ".cgsc");
            auto stack = utils::file::read(file + ".cgsc.stack");

            disassembler.disassemble(file, script, stack);
        }
        else
        {
            if (file.find(".cgsc") != std::string::npos) return;

            const auto ext = std::string(".gscbin");
            const auto extpos = file.find(ext);

            if (extpos != std::string::npos)
            {
                file.replace(extpos, ext.length(), "");
            }

            auto data = utils::file::read(file + ext);

            asset script;

            script.deserialize(data);

            auto stack = utils::zlib::decompress(script.buffer, script.len);

            disassembler.disassemble(file, script.bytecode, stack);
        }

        auto scriptid = std::filesystem::path(file).filename().string();

        if (!isdigit(scriptid.data()[0]))
        {
            utils::file::save("disassembled/" + file + ".gscasm", disassembler.output_data());
            std::cout << "disassembled " << file << ".gscasm\n";
        }
        else
        {
            auto filename = choose_resolver_file_name(std::atoi(scriptid.data()), game);
            auto count = file.find(scriptid);

            if (count != std::string::npos)
            {
                if (!filename.empty())
                {
                    file.erase(count, scriptid.length());
                }
            }

            utils::file::save("disassembled/" + file + filename + ".gscasm", disassembler.output_data());
            std::cout << "disassembled " << file << filename << ".gscasm\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << " at " << file << '\n';
    }
}

void compile_file(game game, std::string file)
{
    try
    {
        auto& assembler = contexts[game]->assembler();
        auto& compiler = contexts[game]->compiler();
        const auto ext = std::string(".gsc");
        const auto extpos = file.find(ext);

        if (extpos != std::string::npos)
        {
            file.replace(extpos, ext.length(), "");
        }

        auto data = utils::file::read(file + ext);

        compiler.compile(file, data);

        auto assembly = compiler.output();

        assembler.assemble(file, assembly);

        if (overwrite_prompt(file + (zonetool ? ".cgsc" : ".gscbin")))
        {
            if (zonetool)
            {
                utils::file::save("compiled/" + file + ".cgsc", assembler.output_script());
                utils::file::save("compiled/" + file + ".cgsc.stack", assembler.output_stack());
                std::cout << "compiled " << file << ".cgsc\n";
            }
            else
            {
                asset script;

                auto uncompressed = assembler.output_stack();
                auto compressed = utils::zlib::compress(uncompressed);

                script.name = file;
                script.bytecode = assembler.output_script();
                script.buffer = std::move(compressed);
                script.len = static_cast<std::uint32_t>(uncompressed.size());
                script.compressedLen = static_cast<std::uint32_t>(script.buffer.size());
                script.bytecodeLen = static_cast<std::uint32_t>(script.bytecode.size());

                auto output = script.serialize();
                utils::file::save("compiled/" + file + ".gscbin", output);
                std::cout << "compiled " << file << ".gscbin\n";
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void decompile_file(game game, std::string file)
{
    try
    {
        auto& disassembler = contexts[game]->disassembler();

        if (zonetool)
        {
            if (file.find(".gscbin") != std::string::npos) return;

            if (file.find(".stack") != std::string::npos)
            {
                std::cerr << "Cannot disassemble stack files\n";
                return;
            }

            const auto ext = std::string(".cgsc");
            const auto extpos = file.find(ext);

            if (extpos != std::string::npos)
            {
                file.replace(extpos, ext.length(), "");
            }

            auto script = utils::file::read(file + ".cgsc");
            auto stack = utils::file::read(file + ".cgsc.stack");

            disassembler.disassemble(file, script, stack);
        }
        else
        {
            if (file.find(".cgsc") != std::string::npos) return;

            const auto ext = std::string(".gscbin");
            const auto extpos = file.find(ext);

            if (extpos != std::string::npos)
            {
                file.replace(extpos, ext.length(), "");
            }

            auto data = utils::file::read(file + ext);

            asset script;

            script.deserialize(data);

            auto stack = utils::zlib::decompress(script.buffer, script.len);

            disassembler.disassemble(file, script.bytecode, stack);
        }

        auto& decompiler = contexts[game]->decompiler();

        auto output = disassembler.output();

        decompiler.decompile(file, output);

        auto scriptid = std::filesystem::path(file).filename().string();

        if (!isdigit(scriptid.data()[0]))
        {
            utils::file::save("decompiled/" + file + ".gsc", decompiler.output());
            std::cout << "decompiled " << file << ".gsc\n";
        }
        else
        {
            auto filename = choose_resolver_file_name(std::atoi(scriptid.data()), game);/*xsk::utils::string::va("%s_%04X", scriptid.data(),  std::atoi(scriptid.data()));*/
            auto count = file.find(scriptid);

            if (count != std::string::npos)
            {
                if (!filename.empty())
                {
                    file.erase(count, scriptid.length());
                }
            }

            utils::file::save("decompiled/" + file + filename + ".gsc", decompiler.output());
            std::cout << "decompiled " << file << filename << ".gsc\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << " at " << file << '\n';
    }
}

void init()
{
    contexts[game::iw5c] = std::make_unique<iw5c::context>();
    contexts[game::iw5c]->init(build::prod, utils::file::read);
    contexts[game::iw5] = std::make_unique<iw5::context>();
    contexts[game::iw5]->init(build::prod, utils::file::read);
    contexts[game::iw6] = std::make_unique<iw6::context>();
    contexts[game::iw6]->init(build::prod, utils::file::read);
    contexts[game::iw7] = std::make_unique<iw7::context>();
    contexts[game::iw7]->init(build::prod, utils::file::read);
    contexts[game::iw8] = std::make_unique<iw8::context>();
    contexts[game::iw8]->init(build::prod, utils::file::read);
    contexts[game::s1] = std::make_unique<s1::context>();
    contexts[game::s1]->init(build::prod, utils::file::read);
    contexts[game::s2] = std::make_unique<s2::context>();
    contexts[game::s2]->init(build::prod, utils::file::read);
    contexts[game::s4] = std::make_unique<s4::context>();
    contexts[game::s4]->init(build::prod, utils::file::read);
    contexts[game::h1] = std::make_unique<h1::context>();
    contexts[game::h1]->init(build::prod, utils::file::read);
    contexts[game::h2] = std::make_unique<h2::context>();
    contexts[game::h2]->init(build::prod, utils::file::read);

    funcs[mode::assemble] = assemble_file;
    funcs[mode::disassemble] = disassemble_file;
    funcs[mode::compile] = compile_file;
    funcs[mode::decompile] = decompile_file;
}

} // namespace xsk::gsc

namespace arc
{

std::map<game, context::ptr> contexts;
std::map<mode, std::function<void(game game, const std::filesystem::path& file)>> funcs;

void assemble_file(game game, const std::filesystem::path& file)
{
    try
    {
        auto& assembler = contexts[game]->assembler();

        auto data = utils::file::read(file.string());
        auto path = t6::resolver::fs_to_game_path(file);
        auto next = path.extension() == ".gscasm" ? path.replace_extension(".gsc") : path.replace_extension(".csc");

        assembler.assemble(next.string(), data);

        utils::file::save((std::filesystem::path("assembled/t6") / next).generic_string(), assembler.output());
        std::cout << "assembled " << path.replace_extension() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void disassemble_file(game game, const std::filesystem::path& file)
{
    try
    {
        auto& disassembler = contexts[game]->disassembler();

        auto data = utils::file::read(file.string());
        auto path = t6::resolver::fs_to_game_path(file);
        auto next = path.extension() == ".gsc" ? path.replace_extension(".gscasm") : path.replace_extension(".cscasm");

        disassembler.disassemble(file.string(), data);

        utils::file::save((std::filesystem::path("disassembled/t6") / next).generic_string(), disassembler.output_raw());
        std::cout << "disassembled " << path.replace_extension() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << " at " << file.string() << '\n';
    }
}

void compile_file(game game, const std::filesystem::path& file)
{
    try
    {
        auto& assembler = contexts[game]->assembler();
        auto& compiler = contexts[game]->compiler();

        auto data = utils::file::read(file.string());
        auto path = t6::resolver::fs_to_game_path(file);

        compiler.compile(file.string(), data);

        auto assembly = compiler.output();

        assembler.assemble(path.string(), assembly);

        utils::file::save((std::filesystem::path("compiled/t6") / path).generic_string(), assembler.output());
        std::cout << "compiled " << path.replace_extension() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void decompile_file(game game, const std::filesystem::path& file)
{
    try
    {
        auto& disassembler = contexts[game]->disassembler();
        auto& decompiler = contexts[game]->decompiler();

        auto data = utils::file::read(file.string());
        auto path = t6::resolver::fs_to_game_path(file);

        disassembler.disassemble(file.string(), data);

        auto output = disassembler.output();

        decompiler.decompile(file.string(), output);

        utils::file::save((std::filesystem::path("decompiled/t6") / path).generic_string(), decompiler.output());
        std::cout << "decompiled " << path.replace_extension() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << " at " << file.string() << '\n';
    }
}

void init()
{
    contexts[game::t6] = std::make_unique<t6::context>();
    contexts[game::t6]->init(build::prod, utils::file::read);

    funcs[mode::assemble] = assemble_file;
    funcs[mode::disassemble] = disassemble_file;
    funcs[mode::compile] = compile_file;
    funcs[mode::decompile] = decompile_file;
}

} // namespace xsk::arc

void execute(mode mode, game game, const std::string& path)
{
    if (std::filesystem::is_directory(path))
    {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
        {
            if (entry.is_regular_file())
            {
                if (game < game::t6)
                    gsc::funcs[mode](game, entry.path().generic_string());
                else
                    arc::funcs[mode](game, std::filesystem::path(entry.path().generic_string(), std::filesystem::path::format::generic_format));
            }
        }
    }
    else if (std::filesystem::is_regular_file(path))
    {
        if (game < game::t6)
            gsc::funcs[mode](game, path);
        else
            arc::funcs[mode](game, std::filesystem::path(path, std::filesystem::path::format::generic_format));
    }
}

auto parse_flags(int argc, char** argv, game& game, mode& mode, std::string& path) -> bool
{
    if (argc != 4) return false;

    auto arg = utils::string::to_lower(argv[1]);

    if (arg.at(0) == 'z')
    {
        arg.erase(arg.begin());
        gsc::zonetool = true;
    }

    const auto& it = modes.find(arg);

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

    const auto& itr = games.find(arg);

    if (itr != games.end())
    {
        game = itr->second;
    }
    else
    {
        std::cout << "[ERROR] unknown game '" << argv[2] << "'.\n\n";
        return false;
    }

    path = utils::string::fordslash(argv[3]);

    return true;
}

void print_usage()
{
    std::cout << "usage: gsc-tool.exe <mode> <game> <path>\n";
    std::cout << "\t* modes: asm, disasm, comp, decomp\n";
    std::cout << "\t* games: iw5c, iw5, iw6, iw7, iw8, s1, s2, s4, h1, h2, t6\n";
    std::cout << "\t* paths: file or directory (recursive)\n";
}
/*
auto shell_parse(const std::vector<std::string>& data, game& game, mode& mode, std::string& path) -> bool
{
    if (data.size() != 3) return false;

    auto arg = utils::string::to_lower(data[0]);

    if (arg.at(0) == 'z')
    {
        arg.erase(arg.begin());
        gsc::zonetool = true;
    }

    const auto& it = modes.find(arg);

    if (it != modes.end())
    {
        mode = it->second;
    }
    else
    {
        std::cout << "[ERROR] unknown mode '" << data[0] << "'.\n";
        return false;
    }

    arg = utils::string::to_lower(data[1]);

    const auto& itr = games.find(arg);

    if (itr != games.end())
    {
        game = itr->second;
    }
    else
    {
        std::cout << "[ERROR] unknown game '" << data[1] << "'.\n";
        return false;
    }

    path = utils::string::fordslash(data[2]);

    return true;
}

void shell_usage()
{
    std::cout << "\nusage: <mode> <game> <path>\n";
    std::cout << "\t* modes: asm, disasm, comp, decomp\n";
    std::cout << "\t* games: iw5, iw6, iw7, iw8, s1, s2, s4, h1, h2, t6\n";
    std::cout << "\t* paths: file or directory (recursive)\n";
    std::cout << "type 'exit' to close\n";
    std::cout << "------------------------------------------------------\n";
}

void shell()
{
    std::string cmd;
    cmd.resize(1024);
    std::vector<std::string> data;
    std::regex exp(R"(([A-Za-z0-9.\/\\]+|\"(?:\\.|[^\"])*?\"|\'(?:\\.|[^\'])*?\'))");

    std::cout << "GSC Tool - https://github.com/xensik/gsc-tool\n";
    shell_usage();

    while (true)
    {
        std::cout << "> ";
        std::memset(cmd.data(), 0, 1024);
        std::cin.getline(cmd.data(), 1024, '\n');
        data.clear();

        for (auto i = std::sregex_iterator(cmd.begin(), cmd.end(), exp); i != std::sregex_iterator(); ++i)
        {
            data.push_back(i->str());
        }

        if (data.size() == 0)
            continue;

        if (data.size() == 1 && data[0] == "exit")
            break;

        auto path = ""s;
        mode mode = mode::__;
        game game = game::__;

        if (shell_parse(data, game, mode, path))
            execute(mode, game, path);
        else
            shell_usage();
    }
}
*/
void main(std::uint32_t argc, char** argv)
{
    auto path = ""s;
    mode mode = mode::_;
    game game = game::_;

    gsc::init();
    arc::init();
/*
    if (argc <= 1)
    {
        return shell();
    }
*/
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
