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

enum class mode { __, ASM, DISASM, COMP, DECOMP };
enum class game { __, IW5, IW6, IW7, IW8, S1, S2, S4, H1, H2 };

std::map<std::string, mode> modes = 
{ 
    { "-asm", mode::ASM },
    { "-disasm", mode::DISASM },
    { "-comp", mode::COMP },
    { "-decomp", mode::DECOMP },
};

std::map<std::string, game> games = 
{ 
    { "-iw5", game::IW5 },
    { "-iw6", game::IW6 },
    { "-iw7", game::IW7 },
    { "-iw8", game::IW8 },
    { "-s1", game::S1 },
    { "-s2", game::S2 },
    { "-s4", game::S4 },
    { "-h1", game::H1 },
    { "-h2", game::H2 },
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

void assemble_file(gsc::assembler& assembler, std::string file, bool zonetool)
{
    try
    {
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
            if(zonetool)
            {
                utils::file::save(file + ".cgsc", assembler.output_script());
                utils::file::save(file + ".cgsc.stack", assembler.output_stack());
                std::cout << "assembled " << file << ".cgsc\n";
            }
            else
            {
                gsc::asset script;

                auto uncompressed = assembler.output_stack();
                auto compressed = utils::zlib::compress(uncompressed);

                script.name = file;
                script.bytecode = assembler.output_script();
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

void disassemble_file(gsc::disassembler& disassembler, std::string file, game& game, bool zonetool)
{
    try
    {
        if(zonetool)
        {
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

            disassembler.disassemble(file, script.bytecode, stack);
        }

        auto scriptid = std::filesystem::path(file).filename().string();

        if (!isdigit(scriptid.data()[0]))
        {
            utils::file::save(file + ".gscasm", disassembler.output_data());
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

            utils::file::save(file + filename + ".gscasm", disassembler.output_data());
            std::cout << "disassembled " << file << filename << ".gscasm\n";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    } 
}

void compile_file(gsc::assembler& assembler, gsc::compiler& compiler, std::string file, bool zonetool)
{
    try
    {
        const auto ext = std::string(".gsc");
        const auto extpos = file.find(ext);
        
        if (extpos != std::string::npos)
        {
            file.replace(extpos, ext.length(), "");
        }

        auto data = utils::file::read(file + ext);
        compiler.set_readf_callback(utils::file::read);
        compiler.compile(file, data);

        auto assembly = compiler.output();

        assembler.assemble(file, assembly);

        if (overwrite_prompt(file + (zonetool ? ".cgsc" : ".gscbin")))
        {
            if(zonetool)
            {
                utils::file::save(file + ".cgsc", assembler.output_script());
                utils::file::save(file + ".cgsc.stack", assembler.output_stack());
                std::cout << "compiled " << file << ".cgsc\n";
            }
            else
            {
                gsc::asset script;

                auto uncompressed = assembler.output_stack();
                auto compressed = utils::zlib::compress(uncompressed);

                script.name = file;
                script.bytecode = assembler.output_script();
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

void decompile_file(gsc::disassembler& disassembler, gsc::decompiler& decompiler, std::string file, game& game, bool zonetool)
{
    try
    {
        if(zonetool)
        {
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

            disassembler.disassemble(file, script.bytecode, stack);
        }

        auto output = disassembler.output();

        decompiler.decompile(file, output);

        auto scriptid = std::filesystem::path(file).filename().string();

        if (!isdigit(scriptid.data()[0]))
        {
            utils::file::save(file + ".gsc", decompiler.output());
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

            utils::file::save(file + filename + ".gsc", decompiler.output());
            std::cout << "decompiled " << file << filename << ".gsc\n";
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int parse_flags(int argc, char** argv, game& game, mode& mode, bool& zonetool)
{
    if (argc != 4) return 1;

    std::string arg = utils::string::to_lower(argv[1]);

    const auto it1 = games.find(arg);

    if (it1 != games.end())
    {
        game = it1->second;
    }
    else
    {
        std::cout << "Unknown game '" << argv[1] << "'.\n\n";
        return 1;
    }

    arg = utils::string::to_lower(argv[2]);

    if(arg.at(1) == 'z')
    {
        arg.erase(arg.begin() + 1);
        zonetool = true;
    }

    const auto it2 = modes.find(arg);

    if (it2 != modes.end())
    {
        mode = it2->second;
    }
    else
    {
        std::cout << "Unknown mode '" << argv[2] << "'.\n\n";
        return 1;
    }

    return 0;
}

void print_usage()
{
    std::cout << "usage: gsc-tool.exe <game> <mode> <file>\n";
    std::cout << "	* games: -iw5, -iw6, -iw7, -iw8, -s1, -s2, -s4, -h1, -h2\n";
    std::cout << "	* modes: -asm, -disasm, -comp, -decomp\n";
}

std::uint32_t main(std::uint32_t argc, char** argv)
{
    std::string file = utils::string::fordslash(argv[argc - 1]);
    mode mode = mode::__;
    game game = game::__;
    bool zonetool = false;

    if (parse_flags(argc, argv, game, mode, zonetool))
    {
        print_usage();
        return 0;
    }

    if (mode == mode::ASM)
    {
        if( game == game::IW5)
        {
            gsc::iw5::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::IW6)
        {
            iw6::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::IW7)
        {
            iw7::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::IW8)
        {
            iw8::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::S1)
        {
            s1::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::S2)
        {
            s2::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::S4)
        {
            s4::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::H1)
        {
            h1::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::H2)
        {
            h2::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
    }
    else if (mode == mode::DISASM)
    {
        if (game == game::IW5)
        {
            gsc::iw5::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::IW6)
        {
            iw6::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::IW7)
        {
            iw7::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::IW8)
        {
            iw8::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::S1)
        {
            s1::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::S2)
        {
            s2::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::S4)
        {
            s4::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::H1)
        {
            h1::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::H2)
        {
            h2::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
    }
    else if (mode == mode::COMP)
    {
        if (game == game::IW5)
        {
            gsc::iw5::assembler assembler;
            gsc::iw5::compiler compiler(gsc::compilation_mode::release);
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::IW6)
        {
            iw6::assembler assembler;
            iw6::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::IW7)
        {
            iw7::assembler assembler;
            iw7::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::IW8)
        {
            iw8::assembler assembler;
            iw8::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::S1)
        {
            s1::assembler assembler;
            s1::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::S2)
        {
            s2::assembler assembler;
            s2::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::S4)
        {
            s4::assembler assembler;
            s4::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::H1)
        {
            h1::assembler assembler;
            h1::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::H2)
        {
            h2::assembler assembler;
            h2::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
    }
    else if (mode == mode::DECOMP)
    {
        if (game == game::IW5)
        {
            iw5::disassembler disassembler;
            iw5::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::IW6)
        {
            iw6::disassembler disassembler;
            iw6::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::IW7)
        {
            iw7::disassembler disassembler;
            iw7::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::IW8)
        {
            iw8::disassembler disassembler;
            iw8::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::S1)
        {
            s1::disassembler disassembler;
            s1::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::S2)
        {
            s2::disassembler disassembler;
            s2::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::S4)
        {
            s4::disassembler disassembler;
            s4::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::H1)
        {
            h1::disassembler disassembler;
            h1::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::H2)
        {
            h2::disassembler disassembler;
            h2::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
    }

    return 0;
}

} // namespace xsk::gsc

int main(int argc, char** argv)
{
    xsk::gsc::main(argc, argv);
}
