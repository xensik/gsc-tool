// Copyright 2020 xensik. All Rights Reserved.

#ifndef XSK_GSC_ASM_DATA_H_
#define XSK_GSC_ASM_DATA_H_

namespace gsc
{

struct instruction;

struct function
{
	std::uint32_t index;
	std::uint32_t size;
	std::uint16_t id;
	std::string name;
	std::vector<std::shared_ptr<instruction>> instructions;
	std::unordered_map<std::uint32_t, std::string> labels;

	function::function() : index(0), name(""), size(0), id(0) { }
};

struct instruction
{
	std::uint32_t index;
	std::uint32_t size;
	opcode opcode;
	std::vector<std::string> data;
	std::shared_ptr<function> parent;

	instruction::instruction() : index(0), opcode(opcode::OP_Count), size(0) { }
};

} // namespace gsc

#endif // XSK_GSC_ASM_DATA_H_