// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"

#include "iw5/xsk/iw5.hpp"
#include "iw6/xsk/iw6.hpp"
#include "iw7/xsk/iw7.hpp"
#include "iw8/xsk/iw8.hpp"
#include "s1/xsk/s1.hpp"
#include "s2/xsk/s2.hpp"
#include "s4/xsk/s4.hpp"
#include "h1/xsk/h1.hpp"
#include "h2/xsk/h2.hpp"

namespace xsk::gsc
{

enum class encd { __, SOURCE, ASSEMBLY, BINARY };
enum class mode { __, ASM, DISASM, COMP, DECOMP };
enum class game { __, IW5, IW6, IW7, IW8, S1, S2, S4, H1, H2 };

const std::map<std::string, encd> exts = 
{ 
    { ".gsc", encd::SOURCE },
    { ".gscasm", encd::ASSEMBLY },
    { ".cgsc", encd::BINARY },
    { ".gscbin", encd::BINARY },
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
};

const std::map<mode, encd> encds = 
{ 
    { mode::ASM , encd::ASSEMBLY },
    { mode::DISASM, encd::BINARY },
    { mode::COMP, encd::SOURCE },
    { mode::DECOMP, encd::BINARY },
};

std::map<game, std::unique_ptr<gsc::assembler>> assemblers;
std::map<game, std::unique_ptr<gsc::disassembler>> disassemblers;
std::map<game, std::unique_ptr<gsc::compiler>> compilers;
std::map<game, std::unique_ptr<gsc::decompiler>> decompilers;
std::map<mode, std::function<void(game game, std::string file)>> funcs;

bool zonetool = false;

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

auto choose_resolver_file_name(uint32_t id, game& game) -> std::string
{
    switch (game)
    {
        case game::IW5: return iw5::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::IW6: return iw6::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::IW7: return iw7::resolver::file_name(id);
        case game::IW8: return iw8::resolver::file_name(id);
        case game::S1: return s1::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::S2: return s2::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::S4: return s4::resolver::file_name(id);
        case game::H1: return h1::resolver::file_name(static_cast<std::uint16_t>(id));
        case game::H2: return h2::resolver::file_name(static_cast<std::uint16_t>(id));
        default: return "";
    }
}

void assemble_file(game game, std::string file)
{
    try
    {
        const auto& assembler = assemblers[game];
        const auto ext = std::string(".gscasm");
        const auto extpos = file.find(ext);
        
        if (extpos != std::string::npos)
        {
            file.replace(extpos, ext.length(), "");
        }

        auto data = utils::file::read(file + ext);

        assembler->assemble(file, data);

        if (overwrite_prompt(file + (zonetool ? ".cgsc" : ".gscbin")))
        {
            if(zonetool)
            {
                utils::file::save(file + ".cgsc", assembler->output_script());
                utils::file::save(file + ".cgsc.stack", assembler->output_stack());
                std::cout << "assembled " << file << ".cgsc\n";
            }
            else
            {
                gsc::asset script;

                auto uncompressed = assembler->output_stack();
                auto compressed = utils::zlib::compress(uncompressed);

                script.name = file;
                script.bytecode = assembler->output_script();
                script.buffer = std::move(compressed);
                script.len = uncompressed.size();
                script.compressedLen = script.buffer.size();
                script.bytecodeLen = script.bytecode.size();

                auto output = script.serialize();
                utils::file::save(file + ".gscbin", output);
                std::cout << "assembled " << file << ".gscbin\n";
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void disassemble_file(game game, std::string file)
{
    try
    {
        const auto& disassembler = disassemblers[game];

        if(zonetool)
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

            disassembler->disassemble(file, script, stack);
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

            gsc::asset script;

            script.deserialize(data);

            auto stack = utils::zlib::decompress(script.buffer, script.len);

            disassembler->disassemble(file, script.bytecode, stack);
        }

        auto scriptid = std::filesystem::path(file).filename().string();

        if (!isdigit(scriptid.data()[0]))
        {
            utils::file::save(file + ".gscasm", disassembler->output_data());
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

            utils::file::save(file + filename + ".gscasm", disassembler->output_data());
            std::cout << "disassembled " << file << filename << ".gscasm\n";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    } 
}

void compile_file(game game, std::string file)
{
    try
    {
        const auto& assembler = assemblers[game];
        const auto& compiler = compilers[game];
        const auto ext = std::string(".gsc");
        const auto extpos = file.find(ext);
        
        if (extpos != std::string::npos)
        {
            file.replace(extpos, ext.length(), "");
        }

        auto data = utils::file::read(file + ext);
        compiler->set_readf_callback(utils::file::read);
        compiler->compile(file, data);

        auto assembly = compiler->output();

        assembler->assemble(file, assembly);

        if (overwrite_prompt(file + (zonetool ? ".cgsc" : ".gscbin")))
        {
            if(zonetool)
            {
                utils::file::save(file + ".cgsc", assembler->output_script());
                utils::file::save(file + ".cgsc.stack", assembler->output_stack());
                std::cout << "compiled " << file << ".cgsc\n";
            }
            else
            {
                gsc::asset script;

                auto uncompressed = assembler->output_stack();
                auto compressed = utils::zlib::compress(uncompressed);

                script.name = file;
                script.bytecode = assembler->output_script();
                script.buffer = std::move(compressed);
                script.len = uncompressed.size();
                script.compressedLen = script.buffer.size();
                script.bytecodeLen = script.bytecode.size();

                auto output = script.serialize();
                utils::file::save(file + ".gscbin", output);
                std::cout << "compiled " << file << ".gscbin\n";
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void decompile_file(game game, std::string file)
{
    try
    {
        const auto& disassembler = disassemblers[game];

        if(zonetool)
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

            disassembler->disassemble(file, script, stack);
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

            gsc::asset script;

            script.deserialize(data);

            auto stack = utils::zlib::decompress(script.buffer, script.len);

            disassembler->disassemble(file, script.bytecode, stack);
        }

        const auto& decompiler = decompilers[game];

        auto output = disassembler->output();

        decompiler->decompile(file, output);

        auto scriptid = std::filesystem::path(file).filename().string();

        if (!isdigit(scriptid.data()[0]))
        {
            utils::file::save(file + ".gsc", decompiler->output());
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

            utils::file::save(file + filename + ".gsc", decompiler->output());
            std::cout << "decompiled " << file << filename << ".gsc\n";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void execute(mode mode, game game, const std::string& path)
{
    if(std::filesystem::is_directory(path))
    {
        for(const auto& entry : std::filesystem::recursive_directory_iterator(path))
        {
            if(entry.is_regular_file())
            {
                auto it1 = encds.find(mode);
                auto it2 = exts.find(entry.path().extension().string());

                if(it1 != encds.end() && it2 != exts.end() && it1->second == it2->second)
                {
                    funcs[mode](game, entry.path().string());
                }
            }  
        }
    }
    else if(std::filesystem::is_regular_file(path))
    {
        funcs[mode](game, path);
    }
}

int parse_flags(int argc, char** argv, game& game, mode& mode, std::string& path)
{
    if (argc != 4) return 1;

    auto arg = utils::string::to_lower(argv[1]);

    if(arg.at(0) == 'z')
    {
        arg.erase(arg.begin());
        zonetool = true;
    }

    const auto it = modes.find(arg);

    if (it != modes.end())
    {
        mode = it->second;
    }
    else
    {
        std::cout << "Unknown mode '" << argv[1] << "'.\n\n";
        return 1;
    }

    arg = utils::string::to_lower(argv[2]);

    const auto itr = games.find(arg);

    if (itr != games.end())
    {
        game = itr->second;
    }
    else
    {
        std::cout << "Unknown game '" << argv[2] << "'.\n\n";
        return 1;
    }

    path = utils::string::fordslash(argv[3]);

    return 0;
}

void print_usage()
{
    std::cout << "usage: gsc-tool.exe <mode> <game> <path>\n";
    std::cout << "	* modes: asm, disasm, comp, decomp\n";
    std::cout << "	* games: iw5, iw6, iw7, iw8, s1, s2, s4, h1, h2\n";
    std::cout << "	* paths: file or directory (recursive)\n";
}

std::uint32_t main(std::uint32_t argc, char** argv)
{
    auto path = ""s;
    mode mode = mode::__;
    game game = game::__;

    assemblers[game::IW5] = std::make_unique<gsc::iw5::assembler>();
    assemblers[game::IW6] = std::make_unique<gsc::iw6::assembler>();
    assemblers[game::IW7] = std::make_unique<gsc::iw7::assembler>();
    assemblers[game::IW8] = std::make_unique<gsc::iw8::assembler>();
    assemblers[game::S1] = std::make_unique<gsc::s1::assembler>();
    assemblers[game::S2] = std::make_unique<gsc::s2::assembler>();
    assemblers[game::S4] = std::make_unique<gsc::s4::assembler>();
    assemblers[game::H1] = std::make_unique<gsc::h1::assembler>();
    assemblers[game::H2] = std::make_unique<gsc::h2::assembler>();

    disassemblers[game::IW5] = std::make_unique<gsc::iw5::disassembler>();
    disassemblers[game::IW6] = std::make_unique<gsc::iw6::disassembler>();
    disassemblers[game::IW7] = std::make_unique<gsc::iw7::disassembler>();
    disassemblers[game::IW8] = std::make_unique<gsc::iw8::disassembler>();
    disassemblers[game::S1] = std::make_unique<gsc::s1::disassembler>();
    disassemblers[game::S2] = std::make_unique<gsc::s2::disassembler>();
    disassemblers[game::S4] = std::make_unique<gsc::s4::disassembler>();
    disassemblers[game::H1] = std::make_unique<gsc::h1::disassembler>();
    disassemblers[game::H2] = std::make_unique<gsc::h2::disassembler>();

    compilers[game::IW5] = std::make_unique<gsc::iw5::compiler>(gsc::compilation_mode::release);
    compilers[game::IW6] = std::make_unique<gsc::iw6::compiler>();
    compilers[game::IW7] = std::make_unique<gsc::iw7::compiler>();
    compilers[game::IW8] = std::make_unique<gsc::iw8::compiler>();
    compilers[game::S1] = std::make_unique<gsc::s1::compiler>();
    compilers[game::S2] = std::make_unique<gsc::s2::compiler>();
    compilers[game::S4] = std::make_unique<gsc::s4::compiler>();
    compilers[game::H1] = std::make_unique<gsc::h1::compiler>();
    compilers[game::H2] = std::make_unique<gsc::h2::compiler>();

    decompilers[game::IW5] = std::make_unique<gsc::iw5::decompiler>();
    decompilers[game::IW6] = std::make_unique<gsc::iw6::decompiler>();
    decompilers[game::IW7] = std::make_unique<gsc::iw7::decompiler>();
    decompilers[game::IW8] = std::make_unique<gsc::iw8::decompiler>();
    decompilers[game::S1] = std::make_unique<gsc::s1::decompiler>();
    decompilers[game::S2] = std::make_unique<gsc::s2::decompiler>();
    decompilers[game::S4] = std::make_unique<gsc::s4::decompiler>();
    decompilers[game::H1] = std::make_unique<gsc::h1::decompiler>();
    decompilers[game::H2] = std::make_unique<gsc::h2::decompiler>();

    funcs[mode::ASM] = assemble_file;
    funcs[mode::DISASM] = disassemble_file;
    funcs[mode::COMP] = compile_file;
    funcs[mode::DECOMP] = decompile_file;

    if (parse_flags(argc, argv, game, mode, path))
    {
        print_usage();
        return 0;
    }

    execute(mode, game, path);

    return 0;
}

} // namespace xsk::gsc

int main(int argc, char** argv)
{
    xsk::gsc::main(argc, argv);
}
