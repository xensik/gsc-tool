// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"

auto overwrite_prompt(const std::string& file) -> bool
{
    auto overwrite = true;

    if (utils::file::exists(file))
    {
        do
        {
            printf("File \"%s\" already exists, overwrite? [Y/n]: ", file.data());
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

auto choose_resolver_file_name(uint16_t id, game& game) -> std::string
{
    switch (game)
    {
        case game::IW5:
            return IW5::resolver::file_name(id);
            break;
        case game::IW6:
            return IW6::resolver::file_name(id);
            break;
        case game::IW7:
            return IW7::resolver::file_name(id);
            break;
        case game::S1:
            return S1::resolver::file_name(id);
            break;
        case game::S2:
            return S2::resolver::file_name(id);
            break;
        case game::H1:
            return H1::resolver::file_name(id);
            break;
        case game::H2:
            return H2::resolver::file_name(id);
            break;
        default:
            printf("Not a valid game value \"%d\"", game);
            return "";
    }
}

void assemble_file(gsc::assembler& assembler, std::string file, bool zonetool)
{
    const auto ext = std::string(".gscasm");
    const auto extpos = file.find(ext);
    
    if (extpos != std::string::npos)
    {
        file.replace(extpos, ext.length(), "");
    }

    auto data = utils::file::read(file + ext);

    assembler.assemble(data);

    if (overwrite_prompt(file + (zonetool ? ".cgsc" : ".gscbin")))
    {
        if(zonetool)
        {
            utils::file::save(file + ".cgsc", assembler.output_script());
            utils::file::save(file + ".cgsc.stack", assembler.output_stack());
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
        }
    }
}

void disassemble_file(gsc::disassembler& disassembler, std::string file, game& game, bool zonetool)
{
    if(zonetool)
    {
        if (file.find(".stack") != std::string::npos)
        {
            printf("Cannot disassemble stack files\n");
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

        disassembler.disassemble(script, stack);
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

        disassembler.disassemble(script.bytecode, stack);
    }

    auto scriptid = std::filesystem::path(file).filename().string();

    if (!isdigit(scriptid.data()[0]))
    {
        utils::file::save(file + ".gscasm", disassembler.output_data());
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
    }
}

void compile_file(gsc::assembler& assembler, gsc::compiler& compiler, std::string file, bool zonetool)
{
    const auto ext = std::string(".gsc");
    const auto extpos = file.find(ext);
    
    if (extpos != std::string::npos)
    {
        file.replace(extpos, ext.length(), "");
    }

    auto data = utils::file::read(file + ext);

    compiler.compile(data);

    auto assembly = compiler.output();

    assembler.assemble(assembly);

    if (overwrite_prompt(file + (zonetool ? ".cgsc" : ".gscbin")))
    {
        if(zonetool)
        {
            utils::file::save(file + ".cgsc", assembler.output_script());
            utils::file::save(file + ".cgsc.stack", assembler.output_stack());
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
        }
    }
}

void decompile_file(gsc::disassembler& disassembler, gsc::decompiler& decompiler, std::string file, game& game, bool zonetool)
{
    if(zonetool)
    {
        if (file.find(".stack") != std::string::npos)
        {
            printf("Cannot disassemble stack files\n");
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

        disassembler.disassemble(script, stack);
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

        disassembler.disassemble(script.bytecode, stack);
    }

    auto output = disassembler.output();

    decompiler.decompile(output);

    auto scriptid = std::filesystem::path(file).filename().string();

    if (!isdigit(scriptid.data()[0]))
    {
        utils::file::save(file + ".gsc", decompiler.output());
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
    }

}

int parse_flags(int argc, char** argv, game& game, mode& mode, bool& zonetool)
{
    if (argc != 4) return 1;

    std::string arg = utils::string::to_lower(argv[1]);

    if (arg == "-iw5")
    {
        game = game::IW5;
    }
    else if (arg == "-iw6")
    {
        game = game::IW6;
    }
    else if (arg == "-iw7")
    {
        game = game::IW7;
    }
    else if (arg == "-s1")
    {
        game = game::S1;
    }
    else if (arg == "-s2")
    {
        game = game::S2;
    }
    else if (arg == "-h1")
    {
        game = game::H1;
    }
    else if (arg == "-h2")
    {
        game = game::H2;
    }
    else
    {
        printf("Unknown game \"%s\".\n", argv[1]);
        return 1;
    }

    arg = utils::string::to_lower(argv[2]);

    if(arg.at(1) == 'z')
    {
        arg.erase(arg.begin() + 1);
        zonetool = true;
    }

    if (arg == "-asm")
    {
        mode = mode::ASM;
    }
    else if (arg == "-disasm")
    {
        mode = mode::DISASM;
    }
    else if (arg == "-comp")
    {
        mode = mode::COMP;
    }
    else if (arg == "-decomp")
    {
        mode = mode::DECOMP;
    }
    else
    {
        printf("Unknown mode \"%s\".\n\n", argv[2]);
        return 1;
    }

    return 0;
}

int main(int argc, char** argv)
{
    std::string file = argv[argc - 1];
    mode mode = mode::__;
    game game = game::__;
    bool zonetool = false;

    if (parse_flags(argc, argv, game, mode, zonetool))
    {
        printf("usage: gsc-tool.exe <game> <mode> <file>\n");
        printf("	* games: -iw5, -iw6, -iw7, -s1, -s2, -h1, -h2\n");
        printf("	* modes: -asm, -disasm, -comp, -decomp\n");
        return 0;
    }

    if (mode == mode::ASM)
    {
        if( game == game::IW5)
        {
            IW5::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::IW6)
        {
            IW6::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::IW7)
        {
            IW7::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::S1)
        {
            S1::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::S2)
        {
            S2::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::H1)
        {
            H1::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
        else if (game == game::H2)
        {
            H2::assembler assembler;
            assemble_file(assembler, file, zonetool);
        }
    }
    else if (mode == mode::DISASM)
    {
        if (game == game::IW5)
        {
            IW5::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::IW6)
        {
            IW6::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::IW7)
        {
            IW7::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::S1)
        {
            S1::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::S2)
        {
            S2::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::H1)
        {
            H1::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
        else if (game == game::H2)
        {
            H2::disassembler disassembler;
            disassemble_file(disassembler, file, game, zonetool);
        }
    }
    else if (mode == mode::COMP)
    {
        if (game == game::IW5)
        {
            IW5::assembler assembler;
            IW5::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::IW6)
        {
            IW6::assembler assembler;
            IW6::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::IW7)
        {
            IW7::assembler assembler;
            IW7::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::S1)
        {
            S1::assembler assembler;
            S1::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::S2)
        {
            S2::assembler assembler;
            S2::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::H1)
        {
            H1::assembler assembler;
            H1::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
        else if (game == game::H2)
        {
            H2::assembler assembler;
            H2::compiler compiler;
            compile_file(assembler, compiler, file ,zonetool);
        }
    }
    else if (mode == mode::DECOMP)
    {
        if (game == game::IW5)
        {
            IW5::disassembler disassembler;
            IW5::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::IW6)
        {
            IW6::disassembler disassembler;
            IW6::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::IW7)
        {
            IW7::disassembler disassembler;
            IW7::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::S1)
        {
            S1::disassembler disassembler;
            S1::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::S2)
        {
            S2::disassembler disassembler;
            S2::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::H1)
        {
            H1::disassembler disassembler;
            H1::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
        else if (game == game::H2)
        {
            H2::disassembler disassembler;
            H2::decompiler decompiler;
            decompile_file(disassembler, decompiler, file, game, zonetool);
        }
    }

    return 0;
}
