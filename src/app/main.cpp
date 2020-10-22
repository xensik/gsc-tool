// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"
#include <filesystem>

void assemble_file(std::string file)
{
	auto scriptfile = utils::file::read(file + ".gscasm");
	gsc::assembler assembler;

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

void disassemble_file(std::string file)
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

	// open files
	auto script = std::make_shared<utils::byte_buffer>(file + ".cgsc");
	auto stack = std::make_shared<utils::byte_buffer>(file + ".cgsc.stack");

#ifdef DEV_DEBUG
	gsc::disassembler disassembler(true);
#else
	gsc::disassembler disassembler(false);
#endif

	disassembler.disassemble(script, stack);
	
#ifndef DEV_DEBUG
	utils::file::save(file + ".gscasm", disassembler.output_buffer());
#endif
}

void decompile_file(std::string file)
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

	// open files
	auto script = std::make_shared<utils::byte_buffer>(file + ".cgsc");
	auto stack = std::make_shared<utils::byte_buffer>(file + ".cgsc.stack");

	gsc::disassembler disassembler(false);

	disassembler.disassemble(script, stack);

	gsc::decompiler decompiler;

	decompiler.decompile(disassembler.output());

	utils::file::save(file + ".gsc", decompiler.output());
}

int main(int argc, char** argv)
{
	std::string file = argv[argc - 1];
	std::string mode;

	if (argc >= 3)
	{
		for (int i = 1; i < argc - 1; i++)
		{
			std::string arg = argv[i];

			if (arg == "-asm" || arg == "-disasm" || arg == "-decomp")
			{
				mode = arg;
			}
			else
			{
				printf("Unknown flag \"%s\".\n", argv[i]);
			}
		}
	}
	else
	{
		printf("usage: gsc-tool.exe <options> <file>\n");
		return 0;
	}

	if (mode == "-asm")
	{
		assemble_file(file);
	}
	else if (mode == "-disasm")
	{
		disassemble_file(file);
	}
	else if (mode == "-decomp")
	{
		decompile_file(file);
	}

	return 0;
}
