#include "stdinc.hpp"
#include "assembler.hpp"
#include "disassembler.hpp"

void AssembleFile(std::string file)
{
	std::string scriptfile = ReadFile(file);

	auto assembler_ = gsc::assembler();

	assembler_.assemble(scriptfile);

	SaveFile(file + ".out.cgsc", assembler_.output_script());
	SaveFile(file + ".out.cgsc.stack", assembler_.output_stack());
}

void DisassembleFile(std::string file)
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
	auto script = std::make_shared<byte_buffer>(file + ".cgsc");
	auto stack = std::make_shared<byte_buffer>(file + ".cgsc.stack");

	auto disasembler_ = gsc::disassembler(false);

	disasembler_.disassemble(script, stack);
	
	SaveFile(file + ".gscasm", disasembler_.output());
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

			if (arg == "-disasm" || arg == "-asm")
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
		printf("usage: ScriptfileDisasm.exe <options> <file>\n");
		return 0;
	}

	if (mode == "-asm")
	{
		AssembleFile(file);
	}
	else
	{
		DisassembleFile(file);
	}

	return 0;
}
