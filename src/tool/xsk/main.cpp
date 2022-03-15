// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"

#include "utils/xsk/utils.hpp"
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

enum class encd { __, SOURCE, ASSEMBLY, BINARY };
enum class mode { __, ASM, DISASM, COMP, DECOMP };
enum class game { __, IW5, IW6, IW7, IW8, S1, S2, S4, H1, H2, T6 };

const std::map<std::string, encd> exts =
{
    { ".gsc", encd::SOURCE },
    { ".cgsc", encd::BINARY },
    { ".gscbin", encd::BINARY },
    { ".gscasm", encd::ASSEMBLY },
};

const std::map<std::string, mode> modes =
{
    { "asm", mode::ASM },
    { "disasm", mode::DISASM },
    { "comp", mode::COMP },
    { "decomp", mode::DECOMP },
};

const std::map<std::string, game> games =
{
    { "iw5", game::IW5 },
    { "iw6", game::IW6 },
    { "iw7", game::IW7 },
    { "iw8", game::IW8 },
    { "s1", game::S1 },
    { "s2", game::S2 },
    { "s4", game::S4 },
    { "h1", game::H1 },
    { "h2", game::H2 },
    { "t6", game::T6 },
};

const std::map<mode, encd> encds =
{
    { mode::ASM , encd::ASSEMBLY },
    { mode::DISASM, encd::BINARY },
    { mode::COMP, encd::SOURCE },
    { mode::DECOMP, encd::BINARY },
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
        case game::IW5:
            return iw5::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::IW6:
            return iw6::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::IW7:
            return iw7::resolver::file_name(id);
        case game::IW8:
            return iw8::resolver::file_name(id);
        case game::S1:
            return s1::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::S2:
            return s2::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::S4:
            return s4::resolver::file_name(id);
        case game::H1:
            return h1::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::H2:
            return h2::resolver::file_name(static_cast<std::uint16_t>(id));
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
                script.len = uncompressed.size();
                script.compressedLen = script.buffer.size();
                script.bytecodeLen = script.bytecode.size();

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
        std::cerr << e.what() << '\n';
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
                script.len = uncompressed.size();
                script.compressedLen = script.buffer.size();
                script.bytecodeLen = script.bytecode.size();

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
            auto filename = choose_resolver_file_name(std::atoi(scriptid.data()), game);
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
        std::cerr << e.what() << '\n';
    }
}

void init()
{
    contexts[game::IW5] = std::make_unique<iw5::context>();
    contexts[game::IW5]->init(build::prod, utils::file::read);
    contexts[game::IW6] = std::make_unique<iw6::context>();
    contexts[game::IW6]->init(build::prod, utils::file::read);
    contexts[game::IW7] = std::make_unique<iw7::context>();
    contexts[game::IW7]->init(build::prod, utils::file::read);
    contexts[game::IW8] = std::make_unique<iw8::context>();
    contexts[game::IW8]->init(build::prod, utils::file::read);
    contexts[game::S1] = std::make_unique<s1::context>();
    contexts[game::S1]->init(build::prod, utils::file::read);
    contexts[game::S2] = std::make_unique<s2::context>();
    contexts[game::S2]->init(build::prod, utils::file::read);
    contexts[game::S4] = std::make_unique<s4::context>();
    contexts[game::S4]->init(build::prod, utils::file::read);
    contexts[game::H1] = std::make_unique<h1::context>();
    contexts[game::H1]->init(build::prod, utils::file::read);
    contexts[game::H2] = std::make_unique<h2::context>();
    contexts[game::H2]->init(build::prod, utils::file::read);

    funcs[mode::ASM] = assemble_file;
    funcs[mode::DISASM] = disassemble_file;
    funcs[mode::COMP] = compile_file;
    funcs[mode::DECOMP] = decompile_file;
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

        utils::file::save((std::filesystem::path("assembled/t6") / next).string(), assembler.output());
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

        utils::file::save((std::filesystem::path("disassembled/t6") / next).string(), disassembler.output_data());
        std::cout << "disassembled " << path.replace_extension() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
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

        utils::file::save((std::filesystem::path("compiled/t6") / path).string(), assembler.output());
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

        utils::file::save((std::filesystem::path("decompiled/t6") / path).string(), decompiler.output());
        std::cout << "decompiled " << path.replace_extension() << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void init()
{
    contexts[game::T6] = std::make_unique<t6::context>();
    contexts[game::T6]->init(build::prod, utils::file::read);

    funcs[mode::ASM] = assemble_file;
    funcs[mode::DISASM] = disassemble_file;
    funcs[mode::COMP] = compile_file;
    funcs[mode::DECOMP] = decompile_file;
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
                if (game < game::T6)
                    gsc::funcs[mode](game, entry.path().string());
                else
                    arc::funcs[mode](game, std::filesystem::path(entry.path(), std::filesystem::path::format::generic_format));
            }
        }
    }
    else if (std::filesystem::is_regular_file(path))
    {
        if (game < game::T6)
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
    std::cout << "\t* games: iw5, iw6, iw7, iw8, s1, s2, s4, h1, h2, t6\n";
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
    mode mode = mode::__;
    game game = game::__;

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
