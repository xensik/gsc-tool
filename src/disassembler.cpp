#include "stdinc.hpp"
#include "disassembler.hpp"

_GSC_BEGIN

disassembler::disassembler(bool ida_output)
{
	m_ida_output = ida_output;
	m_output = std::make_unique<byte_buffer>(0x100000);
}

void disassembler::disassemble(std::shared_ptr<byte_buffer> script, std::shared_ptr<byte_buffer> stack)
{
	m_script = script;
	m_stack = stack;
	m_output->clear();
	m_functions.clear();
	m_labels.clear();
	
	m_script->seek(1); // skip opcode 00

	while (m_stack->is_avail() && m_script->is_avail())
	{
		auto func = std::make_shared<function>();
		func->m_index = m_script->get_pos();
		func->m_size = m_stack->read<std::uint32_t>();
		func->m_id = m_stack->read<std::uint16_t>();
		func->m_name = func->m_id == 0 ? m_stack->read_string() : ""; /*GetFunctionName(func_id)*/
		m_functions.push_back(func);

		this->dissasemble_function(func);

		func->m_labels = m_labels;
		m_labels.clear();
	}

	this->print_script_name(""); // xensik: need to add file name conversor

	for (auto& function : m_functions)
	{
		this->print_function(function);

		for (auto& instruction : function->m_instructions)
		{
			if (function->m_labels.find(instruction->m_index) != function->m_labels.end())
			{
				this->print_label(function->m_labels[instruction->m_index]);
			}

			this->print_instruction(instruction);
		}

		m_output->write_cpp_string("\n");
	}
}

void disassembler::dissasemble_function(std::shared_ptr<function> func)
{
	std::uint32_t size = func->m_size;

	while (size > 0)
	{
		auto inst = std::make_shared<instruction>();
		inst->m_index = m_script->get_pos();
		inst->m_opcode = m_script->read<std::uint8_t>();
		func->m_instructions.push_back(inst);
		
		this->dissasemble_instruction(inst);

		size -= inst->m_size;
	}
}

void disassembler::dissasemble_instruction(std::shared_ptr<instruction> inst)
{
	switch (inst->m_opcode)
	{
	case OP_End:
		inst->m_size = 1;
		break;
	case OP_Return:
		inst->m_size = 1;
		break;
	case OP_GetByte:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_GetNegByte:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::int8_t>()));
		break;
	case OP_GetUnsignedShort:
		inst->m_size = 3;
		inst->m_data.push_back(va("%X", m_script->read<std::uint16_t>()));
		break;
	case OP_GetNegUnsignedShort:
		inst->m_size = 3;
		inst->m_data.push_back(va("%X", m_script->read<std::int16_t>()));
		break;
	case OP_GetInteger:
		inst->m_size = 5;
		inst->m_data.push_back(va("%X", m_script->read<std::int32_t>()));
		break;
	case OP_GetBuiltinFunction:
		this->disassemble_builtin_call(inst, false, false);
		break;
	case OP_GetBuiltinMethod:
		this->disassemble_builtin_call(inst, true, false);
		break;
	case OP_GetFloat:
		inst->m_size = 5;
		inst->m_data.push_back(va("%f", m_script->read<float>()));
		break;
	case OP_GetString:
		inst->m_size = 3;
		inst->m_data.push_back(va("\"%s\"", m_stack->read_string().data()));
		m_script->seek(2);
		break;
	case OP_GetUndefined:
		inst->m_size = 1;
		break;
	case OP_GetZero:
		inst->m_size = 1;
		break;
	case OP_CreateLocalVariable:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_RemoveLocalVariables:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_EvalLocalVariableCached0:
	case OP_EvalLocalVariableCached1:
	case OP_EvalLocalVariableCached2:
	case OP_EvalLocalVariableCached3:
	case OP_EvalLocalVariableCached4:
	case OP_EvalLocalVariableCached5:
		inst->m_size = 1;
		break;
	case OP_EvalLocalVariableCached:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_EvalLocalArrayCached:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_EvalArray:
		inst->m_size = 1;
		break;
	case OP_EvalNewLocalArrayRefCached0:
		inst->m_size = 1;
		break;
	case OP_EvalLocalArrayRefCached0:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_EvalLocalArrayRefCached:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_EvalArrayRef:
		inst->m_size = 1;
		break;
	case OP_ClearArray:
		inst->m_size = 1;
		break;
	case OP_EmptyArray:
		inst->m_size = 1;
		break;
	case OP_AddArray:
		inst->m_size = 1;
		break;
	case OP_PreScriptCall:
		inst->m_size = 1;
		break;
	case OP_ScriptLocalFunctionCall2:
	case OP_ScriptLocalFunctionCall:
	case OP_ScriptLocalMethodCall:
		this->disassemble_local_call(inst, false);
		break;
	case OP_ScriptLocalThreadCall:
	case OP_ScriptLocalChildThreadCall:
	case OP_ScriptLocalMethodThreadCall:
	case OP_ScriptLocalMethodChildThreadCall:
		this->disassemble_local_call(inst, true);
		break;
	case OP_ScriptFarFunctionCall2:
	case OP_ScriptFarFunctionCall:
	case OP_ScriptFarMethodCall:
		this->disassemble_far_call(inst, false);
		break;
	case OP_ScriptFarThreadCall:
	case OP_ScriptFarChildThreadCall:
	case OP_ScriptFarMethodThreadCall:
	case OP_ScriptFarMethodChildThreadCall:
		this->disassemble_far_call(inst, true);
		break;
	case OP_ScriptFunctionCallPointer:
		inst->m_size = 1;
		break;
	case OP_ScriptMethodCallPointer:
		inst->m_size = 1;
		break;
	case OP_ScriptThreadCallPointer:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case 0x32:
		printf("opcode 0x32 trigger!!\n");
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_ScriptMethodThreadCallPointer:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_ScriptMethodChildThreadCallPointer:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_CallBuiltinPointer:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_CallBuiltinMethodPointer:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_GetIString:
		inst->m_size = 3;
		m_script->seek(2);
		inst->m_data.push_back(va("\"%s\"", m_stack->read_string().data()));
		break;
	case OP_GetVector:
		inst->m_size = 13;
		inst->m_data.push_back(va("%f", m_script->read<float>()));
		inst->m_data.push_back(va("%f", m_script->read<float>()));
		inst->m_data.push_back(va("%f", m_script->read<float>()));
		break;
	case OP_GetLevelObject:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_GetAnimObject:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_GetSelf:
		inst->m_size = 1;
		break;
	case OP_GetThisthread:
		inst->m_size = 1;
		break;
	case OP_GetLevel:
		inst->m_size = 1;
		break;
	case OP_GetGame:
		inst->m_size = 1;
		break;
	case OP_GetAnim:
		inst->m_size = 1;
	case OP_GetAnimation:
		inst->m_size = 1;
		inst->m_data.push_back(va("\"%s\"", m_stack->read_string().data()));
		inst->m_data.push_back(va("\"%s\"", m_stack->read_string().data()));
		break;
	case OP_GetGameRef:
		inst->m_size = 1;
		break;
	case OP_inc:
		inst->m_size = 1;
		break;
	case OP_dec:
		inst->m_size = 1;
		break;
	case OP_bit_or:
		inst->m_size = 1;
		break;
	case OP_JumpOnFalseExpr:
		this->disassemble_jump(inst, true, false);
		break;
	case OP_bit_ex_or:
		inst->m_size = 1;
		break;
	case OP_bit_and:
		inst->m_size = 1;
		break;
	case OP_equality:
		inst->m_size = 1;
		break;
	case OP_inequality:
		inst->m_size = 1;
		break;
	case OP_less:
		inst->m_size = 1;
		break;
	case OP_greater:
		inst->m_size = 1;
		break;
	case OP_JumpOnTrueExpr:
		this->disassemble_jump(inst, true, false);
		break;
	case OP_less_equal:
		inst->m_size = 1;
		break;
	case OP_jumpback:
		this->disassemble_jump(inst, false, true);
		break;
	case OP_waittillmatch2: // NOP
		break;
	case OP_waittill:
		inst->m_size = 1;
		break;
	case OP_notify:
		inst->m_size = 1;
		break;
	case OP_endon:
		inst->m_size = 1;
		break;
	case OP_voidCodepos:
		inst->m_size = 1;
		break;
	case OP_switch:
		this->disassemble_jump(inst, false, false);
		break;
	case OP_endswitch:
		this->disassemble_end_switch(inst);
		break;
	case OP_vector:
		inst->m_size = 1;
		break;
	case OP_JumpOnFalse:
		this->disassemble_jump(inst, true, false);
		break;
	case OP_greater_equal:
		inst->m_size = 1;
		break;
	case OP_shift_left:
		inst->m_size = 1;
		break;
	case OP_shift_right:
		inst->m_size = 1;
		break;
	case OP_plus:
		inst->m_size = 1;
		break;
	case OP_jump:
		this->disassemble_jump(inst, false, false);
		break;
	case OP_minus:
		inst->m_size = 1;
		break;
	case OP_multiply:
		inst->m_size = 1;
		break;
	case OP_divide:
		inst->m_size = 1;
		break;
	case OP_mod:
		inst->m_size = 1;
		break;
	case OP_JumpOnTrue:
		this->disassemble_jump(inst, true, false);
		break;
	case OP_size:
		inst->m_size = 1;
		break;
	case OP_waittillmatch:
		inst->m_size = 3;
		inst->m_data.push_back(va("%X", m_script->read<std::uint16_t>()));
		break;
	case OP_GetLocalFunction:
		this->disassemble_local_call(inst, false);
		break;
	case OP_GetFarFunction:
		this->disassemble_far_call(inst, false);
		break;
	case OP_GetSelfObject:
		inst->m_size = 1;
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
		this->disassemble_field_variable(inst);
		break;
	case OP_SafeCreateVariableFieldCached:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_SafeSetVariableFieldCached0:
		inst->m_size = 1;
		break;
	case OP_SafeSetVariableFieldCached:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_SafeSetWaittillVariableFieldCached:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_GetAnimTree:
		inst->m_size = 2;
		m_script->seek(1);
		inst->m_data.push_back(va("\"%s\"", m_stack->read_string().data()));
		break;
	case OP_clearparams:
		inst->m_size = 1;
		break;
	case OP_checkclearparams:
		inst->m_size = 1;
		break;
	case OP_EvalLocalVariableRefCached0:
		inst->m_size = 1;
		break;
	case OP_EvalNewLocalVariableRefCached0:
		inst->m_size = 1;
		break;
	case OP_EvalLocalVariableRefCached:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_SetVariableField:
		inst->m_size = 1;
		break;
	case OP_SetLocalVariableFieldCached0:
		inst->m_size = 1;
		break;
	case OP_SetNewLocalVariableFieldCached0:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_SetLocalVariableFieldCached:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_ClearLocalVariableFieldCached:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_ClearLocalVariableFieldCached0:
		inst->m_size = 1;
		break;
	case OP_CallBuiltin0:
	case OP_CallBuiltin1:
	case OP_CallBuiltin2:
	case OP_CallBuiltin3:
	case OP_CallBuiltin4:
	case OP_CallBuiltin5:
		this->disassemble_builtin_call(inst, false, false);
		break;
	case OP_CallBuiltin:
		this->disassemble_builtin_call(inst, false, true);
		break;
	case OP_CallBuiltinMethod0:
	case OP_CallBuiltinMethod1:
	case OP_CallBuiltinMethod2:
	case OP_CallBuiltinMethod3:
	case OP_CallBuiltinMethod4:
	case OP_CallBuiltinMethod5:
		this->disassemble_builtin_call(inst, true, false);
		break;
	case OP_CallBuiltinMethod:
		this->disassemble_builtin_call(inst, true, true);
		break;
	case OP_wait:
		inst->m_size = 1;
		break;
	case OP_DecTop:
		inst->m_size = 1;
		break;
	case OP_CastFieldObject:
		inst->m_size = 1;
		break;
	case OP_EvalLocalVariableObjectCached:
		inst->m_size = 2;
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
		break;
	case OP_CastBool:
		inst->m_size = 1;
		break;
	case OP_BoolNot:
		inst->m_size = 1;
		break;
	case OP_BoolComplement:
		inst->m_size = 1;
		break;
	default:
		printf("[ERROR] %04X UNHANDLED OPCODE (%X)!\n", inst->m_index, inst->m_opcode);
		break;
	}
}

void disassembler::disassemble_builtin_call(std::shared_ptr<instruction> inst, bool method, bool arg_num)
{
	inst->m_size = arg_num ? 4 : 3;

	if (arg_num)
	{
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
	}

	if (method)
	{
		inst->m_data.push_back(GetBuiltinMethodName(m_script->read<std::uint16_t>()));
	}
	else
	{
		inst->m_data.push_back(GetBuiltinFuncName(m_script->read<std::uint16_t>()));
	}
}

void disassembler::disassemble_local_call(std::shared_ptr<instruction> inst, bool thread)
{
	inst->m_size = thread ? 5 : 4;

	std::int32_t offset = this->disassemble_offset();

	inst->m_data.push_back(va("%X", offset + inst->m_index + 1));

	if (thread)
	{
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
	}
}

void disassembler::disassemble_far_call(std::shared_ptr<instruction> inst, bool thread)
{
	inst->m_size = thread ? 5 : 4;

	m_script->seek(3); // placeholder 24bit offset

	if (thread)
	{
		inst->m_data.push_back(va("%X", m_script->read<std::uint8_t>()));
	}

	auto file_id = m_stack->read<std::uint16_t>();
	auto file_name = file_id == 0 ? m_stack->read_string() : ""; /*GetFileName(file_id)*/
	auto func_id = m_stack->read<std::uint16_t>();
	auto func_name = func_id == 0 ? m_stack->read_string() : ""; /*GetFunctionName(func_id)*/

	inst->m_data.push_back(file_name != "" ? file_name : va("%X", file_id));
	inst->m_data.push_back(func_name != "" ? func_name : va("%X", func_id));
}

void disassembler::disassemble_jump(std::shared_ptr<instruction> inst, bool expr, bool back)
{
	inst->m_size = (expr || back) ? 3 : 5;

	std::int32_t addr;
	std::string label;

	if (expr)
	{
		addr = inst->m_index + 3 + m_script->read<std::int16_t>();
		label = va("loc_%X", addr);
		inst->m_data.push_back(label);
	}
	else if (back)
	{
		addr = inst->m_index + 3 - m_script->read<std::uint16_t>();
		label = va("loc_%X", addr);
		inst->m_data.push_back(label);
	}
	else
	{
		addr = inst->m_index + 5 + m_script->read<std::int32_t>();
		label = va("loc_%X", addr);
		inst->m_data.push_back(label);
	}

	m_labels[addr] = label;
}

void disassembler::disassemble_field_variable(std::shared_ptr<instruction> inst)
{
	inst->m_size = 3;

	std::uint16_t field_id = m_script->read<std::uint16_t>();
	std::string field_name = "";

	inst->m_data.push_back(va("field_%X", field_id));

	if (field_id > 33386)
	{
		inst->m_data.push_back(va("\"%s\"", m_stack->read_opaque_string().data()));
	}
}

void disassembler::disassemble_end_switch(std::shared_ptr<instruction> inst)
{
	inst->m_size = 3;

	std::uint16_t case_num = m_script->read<std::uint16_t>();
	inst->m_data.push_back(va("%X", case_num));

	std::uint32_t internal_index = inst->m_index + 3;

	if (case_num)
	{
		for (auto i = case_num; i > 0; i--)
		{
			std::uint32_t case_label = m_script->read<std::uint32_t>();
			
			if (case_label < 0x10000 && case_label > 0)
			{
				inst->m_data.push_back("case");
				inst->m_data.push_back(va("\"%s\"", m_stack->read_string().data()));
			}
			else if (case_label < 0x10000)
			{
				inst->m_data.push_back("default");
				m_stack->read<std::uint16_t>(); // should be 01 00 (opaque string id)
			}
			else
			{
				inst->m_data.push_back("case");
				inst->m_data.push_back(va("%X", case_label & 0xFFFF));
			}

			inst->m_size += 4;
			internal_index += 4;

			auto addr = this->disassemble_offset() + internal_index;
			std::string label = va("loc_%X", addr);
			inst->m_data.push_back(label);
			
			m_labels[addr] = label;

			inst->m_size += 3;
			internal_index += 3;
		}
	}
}

std::int32_t disassembler::disassemble_offset()
{
	std::vector<std::uint8_t> bytes;

	bytes.resize(4);
	std::fill(bytes.begin(), bytes.end(), 0);

	for (int i = 0; i < 3; i++)
	{
		bytes[i] = m_script->read<std::uint8_t>();
	}

	std::int32_t offset = *reinterpret_cast<std::int32_t*>(bytes.data());
	
	offset = (offset << 8) >> 10;

	return offset;
}

std::string disassembler::resolve_function(const std::string& index)
{
	if (is_hex_number(index))
	{
		std::uint32_t idx = std::stoul(index, nullptr, 16);

		for (auto& func : m_functions)
		{
			if (func->m_index == idx)
			{
				if(func->m_id == 0)
					return va("func_%s", func->m_name.data());
				else
					return va("func_%X", func->m_id);
			}
		}

		printf("[ERROR] Couldn't resolve function name of 0x%X!\n", idx);
		return index;
	}
	else
	{
		printf("[ERROR] \"%s\" is not valid function address!\n", index.data());
		return index;
	}
}

void disassembler::print_script_name(const std::string& name)
{
	m_output->write_cpp_string(va("script_begin %s\n", name.data()));
}

void disassembler::print_opcodes(std::uint32_t index, std::uint32_t size)
{
	if (m_ida_output)
	{
		m_output->write_cpp_string(va("%04X\t", index));
		m_output->write_cpp_string(va("%-20s \t\t", m_script->get_bytes_print(index, size).data()));
	}
	else
	{
		m_output->write_cpp_string("\t\t");
	}
}

void disassembler::print_function(std::shared_ptr<function> func)
{
	if (m_ida_output)
	{
		m_output->write_cpp_string("\n\t");
		m_output->write_cpp_string(va("%-20s", ""));
	}

	if (func->m_id == 0)
	{
		m_output->write_cpp_string(va("func_%s\n", func->m_name.data()));
	}
	else
	{
		m_output->write_cpp_string(va("func_%X\n", func->m_id));
	}
}

void disassembler::print_instruction(std::shared_ptr<instruction> inst)
{
	switch (inst->m_opcode)
	{
	case OP_endswitch:
		this->print_opcodes(inst->m_index, 3);
		m_output->write_cpp_string(va("%s", GetOpCodeName(inst->m_opcode).data()));
		m_output->write_cpp_string(va(" %s\n", inst->m_data[0].data()));
		{
			std::uint32_t totalcase = std::stoul(inst->m_data[0], nullptr, 16);
			auto index = 0;
			for (auto casenum = 0; casenum < totalcase; casenum++)
			{
				this->print_opcodes(inst->m_index, 7);
				if (inst->m_data[1 + index] == "case")
				{
					m_output->write_cpp_string(va("%s %s %s", inst->m_data[1 + index].data(), inst->m_data[1 + index + 1].data(), inst->m_data[1 + index + 2].data()));
					index += 3;
				}
				else if (inst->m_data[1 + index] == "default")
				{
					m_output->write_cpp_string(va("%s %s", inst->m_data[1 + index].data(), inst->m_data[1 + index + 1].data()));
					index += 2;
				}
				if (casenum != totalcase - 1)
					m_output->write_cpp_string("\n");
			}
		}
		break;
	case OP_GetLocalFunction:
	case OP_ScriptLocalFunctionCall: // fix local function calls here once we have all function names created
	case OP_ScriptLocalFunctionCall2:
	case OP_ScriptLocalMethodCall:
	case OP_ScriptLocalThreadCall:
	case OP_ScriptLocalChildThreadCall:
	case OP_ScriptLocalMethodThreadCall:
	case OP_ScriptLocalMethodChildThreadCall:
		this->print_opcodes(inst->m_index, inst->m_size);
		m_output->write_cpp_string(va("%s", GetOpCodeName(inst->m_opcode).data()));
		m_output->write_cpp_string(va(" %s", this->resolve_function(inst->m_data[0]).data()));
		if (inst->m_data.size() > 1)
		{
			m_output->write_cpp_string(va(" %s", inst->m_data[1].data()));
		}
		break;
	default:
		this->print_opcodes(inst->m_index, inst->m_size);
		m_output->write_cpp_string(va("%s", GetOpCodeName(inst->m_opcode).data()));
		for (auto& d : inst->m_data)
		{
			m_output->write_cpp_string(va(" %s", d.data()));
		}
		break;
	}

	m_output->write_cpp_string("\n");
}

void disassembler::print_label(const std::string& label)
{
	if (m_ida_output)
	{
		m_output->write_cpp_string("\n\t");
		m_output->write_cpp_string(va("%-20s ", ""));
	}

	m_output->write_cpp_string(va("\t%s\n", label.data()));
}

std::vector<std::uint8_t> disassembler::output()
{
	std::vector<std::uint8_t> output;
	output.resize(m_output->get_pos());
	memcpy(output.data(), m_output->get_buffer().data(), output.size());

	return output;
}

_GSC_END
