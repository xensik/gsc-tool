// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"

void assemble_file(gsc::assembler& assembler, std::string file)
{
	auto scriptfile = utils::file::read(file + ".gscasm");

	assembler.assemble(scriptfile);

	auto overwrite = true;
	if (std::filesystem::exists(file + ".cgsc"))
	{
		do
		{
			printf("File \"%s.cgsc\" already exists, overwrite? [Y/n]: ", file.data());
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

	if (overwrite)
	{
		utils::file::save(file + ".cgsc", assembler.output_script());
		utils::file::save(file + ".cgsc.stack", assembler.output_stack());
	}
}

void disassemble_file(gsc::disassembler& disassembler, std::string file)
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

	// TODO: open files here instead inside byte_buffer
	auto script = file + ".cgsc";
	auto stack = file + ".cgsc.stack";

	disassembler.disassemble(script, stack);
	
	utils::file::save(file + ".gscasm", disassembler.output_asm());
}

void compile_file(gsc::assembler& assembler, gsc::compiler& compiler, std::string file)
{
	const auto ext = std::string(".gsc");
	const auto extpos = file.find(ext);
	if (extpos != std::string::npos)
	{
		file.replace(extpos, ext.length(), "");
	}

	auto scriptfile = utils::file::read(file + ".gsc");

	compiler.compile(scriptfile);

	// auto output = compiler.output();

	// assembler.assemble(output);

	// utils::file::save(file + ".cgsc", assembler.output_script());
	// utils::file::save(file + ".cgsc.stack", assembler.output_stack());
}

void decompile_file(gsc::disassembler& disassembler, gsc::decompiler& decompiler, std::string file)
{
	if (file.find(".stack") != std::string::npos)
	{
		printf("Cannot decompile stack files\n");
		return;
	}

	const auto ext = std::string(".cgsc");
	const auto extpos = file.find(ext);
	if (extpos != std::string::npos)
	{
		file.replace(extpos, ext.length(), "");
	}

	// TODO: open files here instead inside byte_buffer
	auto script = file + ".cgsc";
	auto stack = file + ".cgsc.stack";

	disassembler.disassemble(script, stack);

	auto output = disassembler.output();

	decompiler.decompile(output);

	utils::file::save(file + ".gsc", decompiler.output());
}

int parse_flags(int argc, char** argv, game& game, mode& mode)
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
	else if (arg == "-sh1")
	{
		game = game::SH1;
	}
	else
	{
		printf("Unknown game \"%s\".\n", argv[1]);
		return 1;
	}

	arg = utils::string::to_lower(argv[2]);

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
	bool idaout = IDAOUT;

	if (parse_flags(argc, argv, game, mode))
	{
		printf("usage: gsc-tool.exe <game> <mode> <file>\n");
		printf("	- games: -iw5, -iw6, -sh1\n");
		printf("	- modes: -asm, -disasm, -comp, -decomp\n");
		return 0;
	}

	if (mode == mode::ASM)
	{
		if( game == game::IW5)
		{
			IW5::assembler assembler;
			assemble_file(assembler, file);
		}
		else if (game == game::IW6)
		{
			IW6::assembler assembler;
			assemble_file(assembler, file);
		}
		else if (game == game::SH1)
		{
			SH1::assembler assembler;
			assemble_file(assembler, file);
		}
	}
	else if (mode == mode::DISASM)
	{
		if (game == game::IW5)
		{
			IW5::disassembler disassembler(idaout);
			disassemble_file(disassembler, file);
		}
		else if (game == game::IW6)
		{
			IW6::disassembler disassembler(idaout);
			disassemble_file(disassembler, file);
		}
		else if (game == game::SH1)
		{
			SH1::disassembler disassembler(idaout);
			disassemble_file(disassembler, file);
		}
	}
	else if (mode == mode::COMP)
	{
		if (game == game::IW5)
		{
			IW5::assembler assembler;
			IW5::compiler compiler;
			compile_file(assembler,compiler, file);
		}
		else if (game == game::IW6)
		{
			IW6::assembler assembler;
			IW6::compiler compiler;
			compile_file(assembler, compiler, file);
		}
		if (game == game::SH1)
		{
			SH1::assembler assembler;
			SH1::compiler compiler;
			compile_file(assembler, compiler, file);
		}
	}
	else if (mode == mode::DECOMP)
	{
		if (game == game::IW5)
		{
			IW5::disassembler disassembler(false);
			IW5::decompiler decompiler;
			decompile_file(disassembler, decompiler, file);
		}
		else if (game == game::IW6)
		{
			IW6::disassembler disassembler(false);
			IW6::decompiler decompiler;
			decompile_file(disassembler, decompiler, file);
		}
		if (game == game::SH1)
		{
			SH1::disassembler disassembler(false);
			SH1::decompiler decompiler;
			decompile_file(disassembler, decompiler, file);
		}
	}

	return 0;
}
