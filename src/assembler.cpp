#include "stdinc.hpp"
#include "assembler.hpp"

_GSC_BEGIN

assembler::assembler()
{
	m_script = std::make_unique<byte_buffer>(0x100000);
	m_stack = std::make_unique<byte_buffer>(0x100000);
}

void assembler::assemble(std::string& buffer)
{
	std::vector<std::string> assembly = clean_buffer_lines(buffer);
	
	std::uint32_t count = 1;
	std::uint32_t index = 0;
	std::shared_ptr<function> func = nullptr;
	std::shared_ptr<instruction> inst = nullptr;
	bool in_switch = false;

	for (auto& line : assembly)
	{
		count++;

		if (line == "")
		{
			continue;
		}

		if (line.at(0) == '#')
		{
			continue;
		}
		else if (line.find("script_begin") != std::string::npos)
		{
			index += 1;
			continue;
		}
		else if (line.substr(0, 5) == "func_")
		{
			if (func != nullptr) // save last function size
			{
				func->m_size = index - func->m_index;
			}

			func = std::make_shared<function>();
			func->m_index = index;
			func->m_name = line;
			m_functions.push_back(func);
		}
		else if (line.substr(0, 4) == "loc_")
		{
			func->m_labels[index] = line;
		}
		else
		{
			// xensik: BUG! take care of string literals!
			std::vector<std::string> data;
			line.find(' ') != std::string::npos ? data = split(line, ' ') : data.push_back(line);

			if (in_switch) // group switch in one instruction
			{
				if (line.substr(0, 4) == "case")
				{
					for(auto& d: data)
						inst->m_data.push_back(d);
					inst->m_size += 7;
					index += 7;
				}
				else if (line.substr(0, 7) == "default")
				{
					for (auto& d : data)
						inst->m_data.push_back(d);
					inst->m_size += 7;
					index += 7;
					in_switch = false;
				}
				else
				{
					printf("ERROR parsing switch: invalid instruction '%s'", line.c_str());
				}
			}
			else
			{
				inst = std::make_shared<instruction>();
				inst->m_index = index;
				inst->m_opcode = GetOpCodeId(to_lower(data[0]));
				inst->m_size = GetInstructionSize(inst->m_opcode);

				inst->m_data = data;

				func->m_instructions.push_back(inst);
				index += inst->m_size;

				if (inst->m_opcode == OP_endswitch)
				{
					in_switch = true;
				}
			}
		}
		// save last function size
		if (count == assembly.size())
		{
			func->m_size = index - func->m_index;
		}
	}

	// script start opcode 00
	m_script->write<std::uint8_t>(0);

	for (auto f : m_functions)
	{
		this->assemble_function(f);
	}
}

void assembler::assemble_function(std::shared_ptr<function> func)
{
	// set label resolver for current function
	m_labels = func->m_labels;

	// write function size
	m_stack->write<std::uint32_t>(func->m_size);
	// write function id or name
	std::string func_name = func->m_name.substr(5);
	std::uint16_t func_id = is_hex_number(func_name) ? std::stoul(func_name, nullptr, 16) : 0;
	func->m_id = func_id;
	m_stack->write<std::uint16_t>(func_id);
	if (func_id == 0)
	{
		m_stack->write_string(func_name);
	}

	for (auto inst : func->m_instructions)
	{
		this->assemble_instruction(inst);
	}
}

void assembler::assemble_instruction(std::shared_ptr<instruction> inst)
{
	switch(inst->m_opcode)
	{
	case OP_End:
	case OP_Return:
	case OP_GetUndefined:
	case OP_GetZero:
	case OP_EvalLocalVariableCached0:
	case OP_EvalLocalVariableCached1:
	case OP_EvalLocalVariableCached2:
	case OP_EvalLocalVariableCached3:
	case OP_EvalLocalVariableCached4:
	case OP_EvalLocalVariableCached5:
	case OP_EvalArray:
	case OP_EvalNewLocalArrayRefCached0:
	case OP_EvalArrayRef:
	case OP_ClearArray:
	case OP_EmptyArray:
	case OP_AddArray:
	case OP_PreScriptCall:
	case OP_ScriptFunctionCallPointer:
	case OP_ScriptMethodCallPointer:
	case OP_GetSelf:
	case OP_GetLevel:
	case OP_GetGame:
	case OP_GetGameRef:
	case OP_inc:
	case OP_dec:
	case OP_bit_or:
	case OP_bit_ex_or:
	case OP_bit_and:
	case OP_equality:
	case OP_inequality:
	case OP_less:
	case OP_greater:
	case OP_less_equal:
	case OP_waittill:
	case OP_notify:
	case OP_endon:
	case OP_voidCodepos:
	case OP_vector:
	case OP_greater_equal:
	case OP_plus:
	case OP_minus:
	case OP_multiply:
	case OP_divide:
	case OP_mod:
	case OP_size:
	case OP_GetSelfObject:
	case OP_SafeSetVariableFieldCached0:
	case OP_clearparams:
	case OP_checkclearparams:
	case OP_EvalLocalVariableRefCached0:
	case OP_EvalNewLocalVariableRefCached0:
	case OP_SetVariableField:
	case OP_SetLocalVariableFieldCached0:
	case OP_ClearLocalVariableFieldCached0:
	case OP_wait:
	case OP_DecTop:
	case OP_CastFieldObject:
	case OP_CastBool:
	case OP_BoolNot:
	case OP_BoolComplement:
		m_script->write<std::uint8_t>(inst->m_opcode);
		break;
	case OP_GetByte:
	case OP_CreateLocalVariable:
	case OP_RemoveLocalVariables:
	case OP_EvalLocalVariableCached:
	case OP_EvalLocalArrayCached:
	case OP_EvalLocalArrayRefCached0:
	case OP_EvalLocalArrayRefCached:
	case OP_ScriptThreadCallPointer:
	case OP_ScriptMethodThreadCallPointer:
	case OP_ScriptMethodChildThreadCallPointer:
	case OP_CallBuiltinPointer:
	case OP_CallBuiltinMethodPointer:
	case OP_GetAnimObject:
	case OP_SafeCreateVariableFieldCached:
	case OP_SafeSetVariableFieldCached:
	case OP_SafeSetWaittillVariableFieldCached:
	case OP_EvalLocalVariableRefCached:
	case OP_SetNewLocalVariableFieldCached0:
	case OP_SetLocalVariableFieldCached:
	case OP_ClearLocalVariableFieldCached:
	case OP_EvalLocalVariableObjectCached:
		m_script->write<std::uint8_t>(inst->m_opcode);
		m_script->write<std::uint8_t>(std::stol(inst->m_data[1], nullptr, 16));
		break;
	case OP_GetNegByte:
		m_script->write<std::uint8_t>(inst->m_opcode);
		m_script->write<std::int8_t>(std::stol(inst->m_data[1], nullptr, 16));
		break;
	case OP_GetUnsignedShort:
	case OP_waittillmatch:
		m_script->write<std::uint8_t>(inst->m_opcode);
		m_script->write<std::uint16_t>(std::stol(inst->m_data[1], nullptr, 16));
		break;
	case OP_GetNegUnsignedShort:
		m_script->write<std::uint8_t>(inst->m_opcode);
		m_script->write<std::int16_t>(std::stol(inst->m_data[1], nullptr, 16));
	case OP_JumpOnFalseExpr:
	case OP_JumpOnTrueExpr:
	case OP_JumpOnFalse:
	case OP_JumpOnTrue:
		this->assemble_jump(inst, true, false);
		break;
	case OP_jumpback:
		this->assemble_jump(inst, false, true);
		break;
	case OP_jump:
		this->assemble_jump(inst, false, false);
		break;
	case OP_GetInteger:
	case OP_switch:
		m_script->write<std::uint8_t>(inst->m_opcode);
		m_script->write<std::int32_t>(std::stol(inst->m_data[1], nullptr, 16));
		break;
	case OP_GetFloat:
		m_script->write<std::uint8_t>(inst->m_opcode);
		m_script->write<float>(std::stof(inst->m_data[1]));
		break;
	case OP_GetVector:
		m_script->write<std::uint8_t>(inst->m_opcode);
		m_script->write<float>(std::stof(inst->m_data[1]));
		m_script->write<float>(std::stof(inst->m_data[2]));
		m_script->write<float>(std::stof(inst->m_data[3]));
		break;
	case OP_GetBuiltinFunction:
		this->assemble_builtin_call(inst, false, false);
		break;
	case OP_GetBuiltinMethod:
		this->assemble_builtin_call(inst, true, false);
		break;
	case OP_ScriptLocalFunctionCall2:
	case OP_ScriptLocalFunctionCall:
	case OP_ScriptLocalMethodCall:
	case OP_GetLocalFunction:
		this->assemble_local_call(inst, false);
		break;
	case OP_ScriptLocalThreadCall:
	case OP_ScriptLocalChildThreadCall:
	case OP_ScriptLocalMethodThreadCall:
	case OP_ScriptLocalMethodChildThreadCall:
		this->assemble_local_call(inst, true);
		break;
	case OP_ScriptFarFunctionCall2:
	case OP_ScriptFarFunctionCall:
	case OP_ScriptFarMethodCall:
	case OP_GetFarFunction:
		this->assemble_far_call(inst, false);
		break;
	case OP_ScriptFarThreadCall:
	case OP_ScriptFarChildThreadCall:
	case OP_ScriptFarMethodThreadCall:
	case OP_ScriptFarMethodChildThreadCall:
		this->assemble_far_call(inst, true);
		break;
	case OP_CallBuiltin0:
	case OP_CallBuiltin1:
	case OP_CallBuiltin2:
	case OP_CallBuiltin3:
	case OP_CallBuiltin4:
	case OP_CallBuiltin5:
		this->assemble_builtin_call(inst, false, false);
		break;
	case OP_CallBuiltin:
		this->assemble_builtin_call(inst, false, true);
		break;
	case OP_CallBuiltinMethod0:
	case OP_CallBuiltinMethod1:
	case OP_CallBuiltinMethod2:
	case OP_CallBuiltinMethod3:
	case OP_CallBuiltinMethod4:
	case OP_CallBuiltinMethod5:
		this->assemble_builtin_call(inst, true, false);
		break;
	case OP_CallBuiltinMethod:
		this->assemble_builtin_call(inst, true, true);
		break;
	case OP_GetString:
	case OP_GetIString:
		m_script->write<std::uint8_t>(inst->m_opcode);
		m_script->write<std::uint16_t>(0);
		m_stack->write_string(get_string_literal(inst->m_data[1]));
		break;
	case OP_GetAnimation:
		m_script->write<std::uint8_t>(inst->m_opcode);
		m_stack->write_string(get_string_literal(inst->m_data[1]));
		m_stack->write_string(get_string_literal(inst->m_data[2]));
		break;
	case OP_EvalLevelFieldVariable:
	case OP_EvalAnimFieldVariable:
	case OP_EvalSelfFieldVariable:
	case OP_EvalFieldVariable:
	case OP_EvalLevelFieldVariableRef:
	case OP_EvalAnimFieldVariableRef:
	case OP_EvalSelfFieldVariableRef:
	case OP_EvalFieldVariableRef:
	case OP_ClearFieldVariable:
	case OP_SetLevelFieldVariableField:
	case OP_SetAnimFieldVariableField:
	case OP_SetSelfFieldVariableField:
		this->assemble_field_variable(inst);
		break;
	case OP_GetAnimTree:
		m_script->write<std::uint8_t>(inst->m_opcode);
		m_script->write<std::uint8_t>(0);
		m_stack->write_string(get_string_literal(inst->m_data[1]));
		break;
	case OP_endswitch:
		this->assemble_end_switch(inst);
		break;
	default:
		printf("[ERROR] %04X UNHANDLED OPCODE (%X)!\n", inst->m_index, inst->m_opcode);
		break;
	}
}

void assembler::assemble_builtin_call(std::shared_ptr<instruction> inst, bool method, bool arg_num)
{
	m_script->write<std::uint8_t>(inst->m_opcode);

	if (arg_num)
	{
		m_script->write<std::uint8_t>(std::stol(inst->m_data[1], nullptr, 16));
	}

	if (method)
	{
		m_script->write<std::uint16_t>(GetBuiltinMethodId(arg_num ? inst->m_data[2] : inst->m_data[1]));
	}
	else
	{
		m_script->write<std::uint16_t>(GetBuiltinFuncId(arg_num ? inst->m_data[2] : inst->m_data[1]));
	}
}

void assembler::assemble_local_call(std::shared_ptr<instruction> inst, bool thread)
{
	m_script->write<std::uint8_t>(inst->m_opcode);

	std::int32_t addr = this->resolve_function(inst->m_data[1]);

	std::int32_t offset = addr - inst->m_index - 1;

	this->assemble_offset(offset);
	
	if (thread)
	{
		m_script->write<std::uint8_t>(std::stol(inst->m_data[2], nullptr, 16));
	}
}

void assembler::assemble_far_call(std::shared_ptr<instruction> inst, bool thread)
{
	m_script->write<std::uint8_t>(inst->m_opcode);
	m_script->write<std::uint8_t>(0); // 3 bytes placeholder
	m_script->write<std::uint16_t>(0);

	if (thread)
	{
		m_script->write<std::uint8_t>(std::stol(inst->m_data[1], nullptr, 16));
	}

	auto file_id = std::stol(thread ? inst->m_data[2] : inst->m_data[1], nullptr, 16); //GetFileId(data[1]);
	auto func_id = std::stol(thread ? inst->m_data[3] : inst->m_data[2], nullptr, 16); //GetFunctionId(data[2]);
	m_stack->write<std::uint16_t>(file_id);
	if (file_id == 0) m_stack->write_string(thread ? inst->m_data[2] : inst->m_data[1]);
	m_stack->write<std::uint16_t>(func_id);
	if (func_id == 0) m_stack->write_string(thread ? inst->m_data[3] : inst->m_data[2]);
}

void assembler::assemble_end_switch(std::shared_ptr<instruction> inst)
{
	m_script->write<std::uint8_t>(inst->m_opcode);
	
	auto casenum = std::stol(inst->m_data[1], nullptr, 16);
	m_script->write<std::uint16_t>(casenum);

	std::uint32_t internal_index = inst->m_index + 3;

	for (std::uint32_t i = 0; i < casenum; i++)
	{
		if (inst->m_data[3 + (2*i)] == "case")
		{
			m_script->write<uint32_t>(i + 1);
			m_stack->write_string(get_string_literal(inst->m_data[3 + (2 * i) + 1]));

			internal_index += 4;

			std::int32_t addr = std::stol(inst->m_data[3 + (2 * i) + 2], nullptr, 16);

			this->assemble_offset(addr - internal_index);

			internal_index += 3;
		}
		else if (inst->m_data[3 + (2 * i)] == "default")
		{
			m_script->write<uint32_t>(0);
			m_stack->write_string("\x01");

			internal_index += 4;
			std::int32_t addr = this->resolve_label(inst->m_data[3 + (2 * i) + 1]);

			this->assemble_offset(addr - internal_index);

			internal_index += 3;
		}
	}
}

void assembler::assemble_field_variable(std::shared_ptr<instruction> inst)
{
	m_script->write<std::uint8_t>(inst->m_opcode);

	std::string field_name;
	std::uint16_t field_id = 0;

	if (inst->m_data[1].find("field_") != std::string::npos)
	{
		field_name = inst->m_data[1].substr(6);
		field_id = (std::uint16_t)std::stol(field_name, nullptr, 16);
	}
	else
	{
		field_name = inst->m_data[1];
		std::uint16_t field_id = 0; // resolve id
		if (field_id == 0)
			field_id = 0xFFFF;
	}

	m_script->write<std::uint16_t>(field_id);
	
	if (field_id > 33386)
	{
		m_stack->write<std::uint16_t>(0);
		m_stack->write_string(field_name);
	}
}

void assembler::assemble_jump(std::shared_ptr<instruction> inst, bool expr, bool back)
{
	m_script->write<std::uint8_t>(inst->m_opcode);
	
	std::int32_t addr = this->resolve_label(inst->m_data[1]);

	if (expr)
	{
		m_script->write<std::int16_t>(addr - inst->m_index - 3);
	}
	else if (back)
	{
		m_script->write<std::int16_t>((inst->m_index + 3) - addr);
	}
	else
	{
		m_script->write<std::int32_t>(addr - inst->m_index - 5);
	}
}

void assembler::assemble_offset(std::int32_t offset)
{
	offset = (offset << 10) >> 8;

	std::vector<std::uint8_t> bytes;
	bytes.resize(4);
	
	std::fill(bytes.begin(), bytes.end(), 0);
	*reinterpret_cast<std::int32_t*>(bytes.data()) = offset;

	m_script->write<std::uint8_t>(bytes[0]);
	m_script->write<std::uint8_t>(bytes[1]);
	m_script->write<std::uint8_t>(bytes[2]);
}

std::uint32_t assembler::resolve_function(const std::string& name)
{
	if (name.find("func_") == std::string::npos)
		return std::stol(name, nullptr, 16);

	for (auto func : m_functions)
	{
		if (func->m_name == name)
		{
			return func->m_index;
		}
	}
	printf("[ERROR] Couldn't resolve function address of \"%s\"!\n", name.c_str());
	return 0;
}

std::uint32_t assembler::resolve_label(const std::string& name)
{
	for (auto& func : m_labels)
	{
		if (func.second == name)
		{
			return func.first;
		}
	}

	if (is_hex_number(name))
		return std::stol(name, nullptr, 16);

	printf("[ERROR] Couldn't resolve label address of \"%s\"!\n", name.c_str());
	return 0;
}

std::vector<std::uint8_t> assembler::output_script()
{
	std::vector<std::uint8_t> script;
	script.resize(m_script->get_pos());
	memcpy(script.data(), m_script->get_buffer().data(), script.size());

	return script;
}

std::vector<std::uint8_t> assembler::output_stack()
{
	std::vector<std::uint8_t> stack;
	stack.resize(m_stack->get_pos());
	memcpy(stack.data(), m_stack->get_buffer().data(), stack.size());

	return stack;
}

_GSC_END
