#include "stdinc.hpp"

namespace gsc
{
	assembler::assembler()
	{
		m_script = std::make_unique<byte_buffer>(0x100000);
		m_stack = std::make_unique<byte_buffer>(0x100000);
	}

	void assembler::assemble(std::string& buffer)
	{
		LOG_DEBUG("parsing assembly file...");

		std::vector<std::string> assembly = utils::string::clean_buffer_lines(buffer);

		std::vector<std::shared_ptr<function>> functions;
		std::shared_ptr<function> func = nullptr;
		std::shared_ptr<instruction> inst = nullptr;
		std::uint32_t index = 1;
		std::uint16_t switchnum = 0;

		for (auto& line : assembly)
		{
			if (line == "" || line.at(0) == '#' || line.find("script_asm") != std::string::npos)
			{
				continue;
			}
			else if (line.substr(0, 4) == "sub_")
			{
				if (func != nullptr)
				{
					func->m_size = index - func->m_index;
				}

				func = std::make_shared<function>();
				func->m_index = index;
				func->m_name = line.substr(4);
				functions.push_back(func);
			}
			else if (line.substr(0, 4) == "loc_")
			{
				func->m_labels[index] = line;
			}
			else
			{
				// xensik: BUG! take care of string literals!
				std::vector<std::string> data;
				line.find(' ') != std::string::npos ? data = utils::string::split(line, ' ') : data.push_back(line);

				if (switchnum)
				{
					if (line.substr(0, 4) == "case" || line.substr(0, 7) == "default")
					{
						for (auto& d : data)
						{
							inst->m_data.push_back(d);
						}
						switchnum--;
						continue;
					}

					LOG_ERROR("invalid instruction inside endswitch \"%s\"!", line.c_str());
					return;
				}
				else
				{
					inst = std::make_shared<instruction>();
					inst->m_index = index;
					inst->m_opcode = get_opcode_id(utils::string::to_lower(data[0]));
					inst->m_size = get_opcode_size(inst->m_opcode);
					inst->m_data = data;
					inst->m_parent = func;

					// group switch in one instruction
					if (inst->m_opcode == opcode::OP_endswitch)
					{
						if (utils::string::is_hex_number(data[1]))
						{
							switchnum = std::stoul(data[1], nullptr, 16);
							inst->m_size += 7 * switchnum;
						}
						else
						{
							LOG_ERROR("endswitch arg is not a number!", line.c_str());
							return;
						}
					}
					
					index += inst->m_size;
					func->m_instructions.push_back(inst);
				}
			}
		}
		if (func != nullptr)
		{
			func->m_size = index - func->m_index;
		}

		LOG_DEBUG("assembly file parse complete.");
		LOG_DEBUG("%d functions staged for assemble.", functions.size());

		this->assemble(functions);
	}

	auto assembler::output_script() -> std::vector<std::uint8_t>
	{
		std::vector<std::uint8_t> script;

		script.resize(m_script->get_pos());
		memcpy(script.data(), m_script->get_buffer().data(), script.size());

		return script;
	}

	auto assembler::output_stack() -> std::vector<std::uint8_t>
	{
		std::vector<std::uint8_t> stack;

		stack.resize(m_stack->get_pos());
		memcpy(stack.data(), m_stack->get_buffer().data(), stack.size());

		return stack;
	}

	void assembler::assemble(std::vector<std::shared_ptr<function>>& functions)
	{
		m_functions = functions;

		// script start opcode 00
		m_script->write<std::uint8_t>(0);

		for (auto func : m_functions)
		{
			this->assemble_function(func);
		}
	}

	void assembler::assemble_function(std::shared_ptr<function> func)
	{
		// function size
		m_stack->write<std::uint32_t>(func->m_size);

		// function id
		func->m_id = utils::string::is_number(func->m_name) ? std::stoul(func->m_name) : 0; // get_function_id(func->m_name);
		m_stack->write<std::uint16_t>(func->m_id);
		
		// function name
		if (func->m_id == 0)
		{
			m_stack->write_string(func->m_name);
		}

		for (auto inst : func->m_instructions)
		{
			this->assemble_instruction(inst);
		}
	}

	void assembler::assemble_instruction(std::shared_ptr<instruction> inst)
	{
		switch (inst->m_opcode)
		{
		case opcode::OP_End:
		case opcode::OP_Return:
		case opcode::OP_GetUndefined:
		case opcode::OP_GetZero:
		case opcode::OP_waittillFrameEnd:
		case opcode::OP_EvalLocalVariableCached0:
		case opcode::OP_EvalLocalVariableCached1:
		case opcode::OP_EvalLocalVariableCached2:
		case opcode::OP_EvalLocalVariableCached3:
		case opcode::OP_EvalLocalVariableCached4:
		case opcode::OP_EvalLocalVariableCached5:
		case opcode::OP_EvalArray:
		case opcode::OP_EvalNewLocalArrayRefCached0:
		case opcode::OP_EvalArrayRef:
		case opcode::OP_ClearArray:
		case opcode::OP_EmptyArray:
		case opcode::OP_AddArray:
		case opcode::OP_PreScriptCall:
		case opcode::OP_ScriptFunctionCallPointer:
		case opcode::OP_ScriptMethodCallPointer:
		case opcode::OP_GetSelf:
		case opcode::OP_GetLevel:
		case opcode::OP_GetGame:
		case opcode::OP_GetGameRef:
		case opcode::OP_inc:
		case opcode::OP_dec:
		case opcode::OP_bit_or:
		case opcode::OP_bit_ex_or:
		case opcode::OP_bit_and:
		case opcode::OP_equality:
		case opcode::OP_inequality:
		case opcode::OP_less:
		case opcode::OP_greater:
		case opcode::OP_less_equal:
		case opcode::OP_waittill:
		case opcode::OP_notify:
		case opcode::OP_endon:
		case opcode::OP_voidCodepos:
		case opcode::OP_vector:
		case opcode::OP_greater_equal:
		case opcode::OP_plus:
		case opcode::OP_minus:
		case opcode::OP_multiply:
		case opcode::OP_divide:
		case opcode::OP_mod:
		case opcode::OP_size:
		case opcode::OP_GetSelfObject:
		case opcode::OP_SafeSetVariableFieldCached0:
		case opcode::OP_clearparams:
		case opcode::OP_checkclearparams:
		case opcode::OP_EvalLocalVariableRefCached0:
		case opcode::OP_EvalNewLocalVariableRefCached0:
		case opcode::OP_SetVariableField:
		case opcode::OP_SetLocalVariableFieldCached0:
		case opcode::OP_ClearLocalVariableFieldCached0:
		case opcode::OP_wait:
		case opcode::OP_DecTop:
		case opcode::OP_CastFieldObject:
		case opcode::OP_CastBool:
		case opcode::OP_BoolNot:
		case opcode::OP_BoolComplement:
			m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
			break;
		case opcode::OP_GetByte:
		case opcode::OP_CreateLocalVariable:
		case opcode::OP_RemoveLocalVariables:
		case opcode::OP_EvalLocalVariableCached:
		case opcode::OP_EvalLocalArrayCached:
		case opcode::OP_EvalLocalArrayRefCached0:
		case opcode::OP_EvalLocalArrayRefCached:
		case opcode::OP_ScriptThreadCallPointer:
		case opcode::OP_ScriptMethodThreadCallPointer:
		case opcode::OP_ScriptMethodChildThreadCallPointer:
		case opcode::OP_CallBuiltinPointer:
		case opcode::OP_CallBuiltinMethodPointer:
		case opcode::OP_GetAnimObject:
		case opcode::OP_SafeCreateVariableFieldCached:
		case opcode::OP_SafeSetVariableFieldCached:
		case opcode::OP_SafeSetWaittillVariableFieldCached:
		case opcode::OP_EvalLocalVariableRefCached:
		case opcode::OP_SetNewLocalVariableFieldCached0:
		case opcode::OP_SetLocalVariableFieldCached:
		case opcode::OP_ClearLocalVariableFieldCached:
		case opcode::OP_EvalLocalVariableObjectCached:
			m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
			m_script->write<std::uint8_t>(std::stol(inst->m_data[1]));
			break;
		case opcode::OP_GetNegByte:
			m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
			m_script->write<std::int8_t>(std::stol(inst->m_data[1]));
			break;
		case opcode::OP_GetUnsignedShort:
		case opcode::OP_waittillmatch:
			m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
			m_script->write<std::uint16_t>(std::stol(inst->m_data[1]));
			break;
		case opcode::OP_GetNegUnsignedShort:
			m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
			m_script->write<std::int16_t>(std::stol(inst->m_data[1]));
		case opcode::OP_JumpOnFalseExpr:
		case opcode::OP_JumpOnTrueExpr:
		case opcode::OP_JumpOnFalse:
		case opcode::OP_JumpOnTrue:
			this->assemble_jump(inst, true, false);
			break;
		case opcode::OP_jumpback:
			this->assemble_jump(inst, false, true);
			break;
		case opcode::OP_jump:
			this->assemble_jump(inst, false, false);
			break;
		case opcode::OP_switch:
			this->assemble_switch(inst);
			break;
		case opcode::OP_GetInteger:
			m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
			m_script->write<std::int32_t>(std::stol(inst->m_data[1]));
			break;
		case opcode::OP_GetFloat:
			m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
			m_script->write<float>(std::stof(inst->m_data[1]));
			break;
		case opcode::OP_GetVector:
			m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
			m_script->write<float>(std::stof(inst->m_data[1]));
			m_script->write<float>(std::stof(inst->m_data[2]));
			m_script->write<float>(std::stof(inst->m_data[3]));
			break;
		case opcode::OP_GetBuiltinFunction:
			this->assemble_builtin_call(inst, false, false);
			break;
		case opcode::OP_GetBuiltinMethod:
			this->assemble_builtin_call(inst, true, false);
			break;
		case opcode::OP_ScriptLocalFunctionCall2:
		case opcode::OP_ScriptLocalFunctionCall:
		case opcode::OP_ScriptLocalMethodCall:
		case opcode::OP_GetLocalFunction:
			this->assemble_local_call(inst, false);
			break;
		case opcode::OP_ScriptLocalThreadCall:
		case opcode::OP_ScriptLocalChildThreadCall:
		case opcode::OP_ScriptLocalMethodThreadCall:
		case opcode::OP_ScriptLocalMethodChildThreadCall:
			this->assemble_local_call(inst, true);
			break;
		case opcode::OP_ScriptFarFunctionCall2:
		case opcode::OP_ScriptFarFunctionCall:
		case opcode::OP_ScriptFarMethodCall:
		case opcode::OP_GetFarFunction:
			this->assemble_far_call(inst, false);
			break;
		case opcode::OP_ScriptFarThreadCall:
		case opcode::OP_ScriptFarChildThreadCall:
		case opcode::OP_ScriptFarMethodThreadCall:
		case opcode::OP_ScriptFarMethodChildThreadCall:
			this->assemble_far_call(inst, true);
			break;
		case opcode::OP_CallBuiltin0:
		case opcode::OP_CallBuiltin1:
		case opcode::OP_CallBuiltin2:
		case opcode::OP_CallBuiltin3:
		case opcode::OP_CallBuiltin4:
		case opcode::OP_CallBuiltin5:
			this->assemble_builtin_call(inst, false, false);
			break;
		case opcode::OP_CallBuiltin:
			this->assemble_builtin_call(inst, false, true);
			break;
		case opcode::OP_CallBuiltinMethod0:
		case opcode::OP_CallBuiltinMethod1:
		case opcode::OP_CallBuiltinMethod2:
		case opcode::OP_CallBuiltinMethod3:
		case opcode::OP_CallBuiltinMethod4:
		case opcode::OP_CallBuiltinMethod5:
			this->assemble_builtin_call(inst, true, false);
			break;
		case opcode::OP_CallBuiltinMethod:
			this->assemble_builtin_call(inst, true, true);
			break;
		case opcode::OP_GetString:
		case opcode::OP_GetIString:
			m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
			m_script->write<std::uint16_t>(0);
			m_stack->write_string(utils::string::get_string_literal(inst->m_data[1]));
			break;
		case opcode::OP_GetAnimation:
			m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
			m_script->write<std::uint32_t>(0); // placeholder 4 bytes?
			m_stack->write_string(utils::string::get_string_literal(inst->m_data[1]));
			m_stack->write_string(utils::string::get_string_literal(inst->m_data[2]));
			break;
		case opcode::OP_EvalLevelFieldVariable:
		case opcode::OP_EvalAnimFieldVariable:
		case opcode::OP_EvalSelfFieldVariable:
		case opcode::OP_EvalFieldVariable:
		case opcode::OP_EvalLevelFieldVariableRef:
		case opcode::OP_EvalAnimFieldVariableRef:
		case opcode::OP_EvalSelfFieldVariableRef:
		case opcode::OP_EvalFieldVariableRef:
		case opcode::OP_ClearFieldVariable:
		case opcode::OP_SetLevelFieldVariableField:
		case opcode::OP_SetAnimFieldVariableField:
		case opcode::OP_SetSelfFieldVariableField:
			this->assemble_field_variable(inst);
			break;
		case opcode::OP_GetAnimTree:
			m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
			m_script->write<std::uint8_t>(0);
			m_stack->write_string(utils::string::get_string_literal(inst->m_data[1]));
			break;
		case opcode::OP_endswitch:
			this->assemble_end_switch(inst);
			break;
		default:
			LOG_ERROR("%04X UNHANDLED OPCODE (%X)!", inst->m_index, inst->m_opcode);
			break;
		}
	}

	void assembler::assemble_builtin_call(std::shared_ptr<instruction> inst, bool method, bool arg_num)
	{
		m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));

		if (arg_num)
		{
			m_script->write<std::uint8_t>(std::stol(inst->m_data[1]));
		}

		if (method)
		{
			m_script->write<std::uint16_t>(get_builtin_method_id(arg_num ? inst->m_data[2] : inst->m_data[1]));
		}
		else
		{
			m_script->write<std::uint16_t>(get_builtin_func_id(arg_num ? inst->m_data[2] : inst->m_data[1]));
		}
	}

	void assembler::assemble_local_call(std::shared_ptr<instruction> inst, bool thread)
	{
		m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));

		std::int32_t addr = this->resolve_function(inst->m_data[1]);

		std::int32_t offset = addr - inst->m_index - 1;

		this->assemble_offset(offset);

		if (thread)
		{
			m_script->write<std::uint8_t>(std::stol(inst->m_data[2]));
		}
	}

	void assembler::assemble_far_call(std::shared_ptr<instruction> inst, bool thread)
	{
		m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));
		m_script->write<std::uint8_t>(0); // 3 bytes placeholder
		m_script->write<std::uint16_t>(0);

		if (thread)
		{
			m_script->write<std::uint8_t>(std::stol(inst->m_data[1]));
		}

		auto file_id = std::stol(thread ? inst->m_data[2] : inst->m_data[1]); // get_file_id(data[1]);
		auto func_id = std::stol(thread ? inst->m_data[3] : inst->m_data[2]); // get_function_id(data[2]);
		m_stack->write<std::uint16_t>(file_id);
		if (file_id == 0) m_stack->write_string(thread ? inst->m_data[2] : inst->m_data[1]);
		m_stack->write<std::uint16_t>(func_id);
		if (func_id == 0) m_stack->write_string(thread ? inst->m_data[3] : inst->m_data[2]);
	}

	void assembler::assemble_switch(std::shared_ptr<instruction> inst)
	{
		m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));

		std::int32_t addr = this->resolve_label(inst, inst->m_data[1]);

		m_script->write<std::int32_t>(addr - inst->m_index - 4);
	}

	void assembler::assemble_end_switch(std::shared_ptr<instruction> inst)
	{
		m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));

		std::uint16_t casenum = 0;

		if (utils::string::is_hex_number(inst->m_data[1]))
		{
			casenum = std::stol(inst->m_data[1]);
		}
		else
		{
			LOG_ERROR("invalid endswitch number!");
		}

		m_script->write<std::uint16_t>(casenum);

		std::uint32_t internal_index = inst->m_index + 3;

		for (std::uint16_t i = 0; i < casenum; i++)
		{
			if (inst->m_data[2 + (3 * i)] == "case")
			{
				m_script->write<uint32_t>(i + 1);
				m_stack->write_string(utils::string::get_string_literal(inst->m_data[2 + (3 * i) + 1]));

				internal_index += 4;

				std::int32_t addr = this->resolve_label(inst, inst->m_data[2 + (3 * i) + 2]);

				this->assemble_offset(addr - internal_index);

				internal_index += 3;
			}
			else if (inst->m_data[2 + (3 * i)] == "default")
			{
				m_script->write<uint32_t>(0);
				m_stack->write_string("\x01");

				internal_index += 4;
				std::int32_t addr = this->resolve_label(inst, inst->m_data[2 + (3 * i) + 1]);

				this->assemble_offset(addr - internal_index);

				internal_index += 3;
			}
		}
	}

	void assembler::assemble_field_variable(std::shared_ptr<instruction> inst)
	{
		m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));

		std::string field_name;
		std::uint16_t field_id = 0;

		if (inst->m_data[1].find("field_") != std::string::npos)
		{
			field_name = inst->m_data[1].substr(6);
			field_id = (std::uint16_t)std::stol(field_name);
		}
		else
		{
			field_name = inst->m_data[1];
			std::uint16_t field_id = 0; // get_field_id(field_name);
			if (field_id == 0)
			{
				field_id = 0xFFFF;
			}
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
		m_script->write<std::uint8_t>(static_cast<std::uint8_t>(inst->m_opcode));

		std::int32_t addr = this->resolve_label(inst, inst->m_data[1]);

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

	auto assembler::resolve_function(const std::string& name) -> std::uint32_t
	{
		std::string temp = name.substr(4);

		for (auto func : m_functions)
		{
			if (func->m_name == temp)
			{
				return func->m_index;
			}
		}

		LOG_ERROR("Couldn't resolve local function address of '%s'!", name.c_str());
		return 0;
	}

	auto assembler::resolve_label(std::shared_ptr<instruction> inst, const std::string& name) -> std::uint32_t
	{
		for (auto& func : inst->m_parent->m_labels)
		{
			if (func.second == name)
			{
				return func.first;
			}
		}

		LOG_ERROR("Couldn't resolve label address of '%s'!", name.c_str());
		return 0;
	}
}