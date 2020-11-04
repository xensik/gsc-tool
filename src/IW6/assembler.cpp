// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW6.hpp"

namespace IW6
{

assembler::assembler()
{
	script_ = std::make_unique<utils::byte_buffer>(0x100000);
	stack_ = std::make_unique<utils::byte_buffer>(0x100000);
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
		if (line == "" || line.substr(0, 2) == "//" /*|| line.find("script_asm") != std::string::npos*/)
		{
			continue;
		}
		else if (line.substr(0, 4) == "sub_")
		{
			if (func != nullptr)
			{
				func->size = index - func->index;
			}

			func = std::make_shared<function>();
			func->index = index;
			func->name = line.substr(4);
			functions.push_back(func);
		}
		else if (line.substr(0, 4) == "loc_")
		{
			func->labels[index] = line;
		}
		else
		{
			// TODO: BUG! take care of string literals!
			std::vector<std::string> data;
			line.find(' ') != std::string::npos ? (void)(data = utils::string::split(line, ' ')) : data.push_back(line);

			if (switchnum)
			{
				if (line.substr(0, 4) == "case" || line.substr(0, 7) == "default")
				{
					for (auto& d : data)
					{
						inst->data.push_back(d);
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
				inst->index = index;
				inst->opcode = static_cast<std::uint8_t>(resolver::opcode_id(utils::string::to_lower(data[0])));
				inst->size = opcode_size(opcode(inst->opcode));
				inst->data = data;
				inst->parent = func;

				// group switch in one instruction
				if (opcode(inst->opcode) == opcode::OP_endswitch)
				{
					if (utils::string::is_number(data[1]))
					{
						switchnum = std::stoul(data[1]);
						inst->size += 7 * switchnum;
					}
					else
					{
						LOG_ERROR("endswitch arg is not a number!", line.c_str());
						return;
					}
				}
					
				index += inst->size;
				func->instructions.push_back(inst);
			}
		}
	}
	if (func != nullptr)
	{
		func->size = index - func->index;
	}

	LOG_DEBUG("assembly file parse complete.");
	LOG_DEBUG("%d functions staged for assemble.", functions.size());

	this->assemble(functions);
}

auto assembler::output_script() -> std::string
{
	std::string script;

	script.resize(script_->pos());
	memcpy(script.data(), script_->buffer().data(), script.size());

	return script;
}

auto assembler::output_stack() -> std::string
{
	std::string stack;

	stack.resize(stack_->pos());
	memcpy(stack.data(), stack_->buffer().data(), stack.size());

	return stack;
}

void assembler::assemble(std::vector<std::shared_ptr<function>>& functions)
{
	functions_ = functions;

	script_->write<std::uint8_t>(0x34); // magic opcode

	for (auto func : functions_)
	{
		this->assemble_function(func);
	}
}

void assembler::assemble_function(std::shared_ptr<function> func)
{
	stack_->write<std::uint32_t>(func->size);

	func->id = func->name.substr(0, 3) == "id#" ? std::stoul(func->name.substr(3)) : resolver::token_id(func->name);
	stack_->write<std::uint16_t>(func->id);

	if (func->id == 0)
	{
		stack_->write_c_string(func->name);
	}

	for (auto inst : func->instructions)
	{
		this->assemble_instruction(inst);
	}
}

void assembler::assemble_instruction(std::shared_ptr<instruction> inst)
{
	LOG_INFO("%s\n", resolver::opcode_name(opcode(inst->opcode)).c_str());
	switch (opcode(inst->opcode))
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
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		break;
	case opcode::OP_GetByte:
	case opcode::OP_ScriptThreadCallPointer:
	case opcode::OP_ScriptMethodThreadCallPointer:
	case opcode::OP_ScriptMethodChildThreadCallPointer:
	case opcode::OP_CallBuiltinPointer:
	case opcode::OP_CallBuiltinMethodPointer:
	case opcode::OP_GetAnimObject:
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		script_->write<std::uint8_t>(std::stol(inst->data[1]));
		break;
	case opcode::OP_CreateLocalVariable:
	case opcode::OP_RemoveLocalVariables:
	case opcode::OP_EvalLocalVariableCached:
	case opcode::OP_EvalLocalArrayCached:
	case opcode::OP_EvalLocalArrayRefCached0:
	case opcode::OP_EvalLocalArrayRefCached:
	case opcode::OP_SafeCreateVariableFieldCached:
	case opcode::OP_SafeSetVariableFieldCached:
	case opcode::OP_SafeSetWaittillVariableFieldCached:
	case opcode::OP_EvalLocalVariableRefCached:
	case opcode::OP_SetNewLocalVariableFieldCached0:
	case opcode::OP_SetLocalVariableFieldCached:
	case opcode::OP_ClearLocalVariableFieldCached:
	case opcode::OP_EvalLocalVariableObjectCached:
	case opcode::OP_EvalNewLocalArrayRefCached0:
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		script_->write<std::uint8_t>(std::stol(inst->data[1]));
		break;
	case opcode::OP_GetNegByte:
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		script_->write<std::int8_t>(std::stol(inst->data[1]));
		break;
	case opcode::OP_GetUnsignedShort:
	case opcode::OP_waittillmatch:// IW6 placeholder is 2 or 4????
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		script_->write<std::uint16_t>(std::stol(inst->data[1]));
		break;
	case opcode::OP_GetNegUnsignedShort:
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		script_->write<std::int16_t>(std::stol(inst->data[1]));
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
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		script_->write<std::int32_t>(std::stol(inst->data[1]));
		break;
	case opcode::OP_GetFloat:
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		script_->write<float>(std::stof(inst->data[1]));
		break;
	case opcode::OP_GetVector:
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		script_->write<float>(std::stof(inst->data[1]));
		script_->write<float>(std::stof(inst->data[2]));
		script_->write<float>(std::stof(inst->data[3]));
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
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		script_->write<std::uint32_t>(0); // IW6: 4 bytes placeholder
		stack_->write_c_string(utils::string::get_string_literal(inst->data[1]));
		break;
	case opcode::OP_GetAnimation:
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		script_->write<std::uint32_t>(0);
		script_->write<std::uint32_t>(0); // IW6: 8 bytes placeholder
		stack_->write_c_string(utils::string::get_string_literal(inst->data[1]));
		stack_->write_c_string(utils::string::get_string_literal(inst->data[2]));
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
		script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
		script_->write<std::uint8_t>(0);
		stack_->write_c_string(utils::string::get_string_literal(inst->data[1]));
		break;
	case opcode::OP_endswitch:
		this->assemble_end_switch(inst);
		break;
	default:
		LOG_ERROR("Unhandled opcode (0x%X) at index '%04X'!", inst->opcode, inst->index);
		break;
	}
}

void assembler::assemble_builtin_call(std::shared_ptr<instruction> inst, bool method, bool arg_num)
{
	script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

	std::uint16_t id = 0;

	if (arg_num)
	{
		script_->write<std::uint8_t>(std::stol(inst->data[1]));

		if (method)
			id = inst->data[2].substr(0, 3) == "id#" ? std::stol(inst->data[2].substr(3)) : resolver::builtin_method_id(inst->data[2]);
		else
			id = inst->data[2].substr(0, 3) == "id#" ? std::stol(inst->data[2].substr(3)) : resolver::builtin_func_id(inst->data[2]);

	}
	else
	{
		if (method)
			id = inst->data[1].substr(0, 3) == "id#" ? std::stol(inst->data[1].substr(3)) : resolver::builtin_method_id(inst->data[1]);
		else
			id = inst->data[1].substr(0, 3) == "id#" ? std::stol(inst->data[1].substr(3)) : resolver::builtin_func_id(inst->data[1]);
	}

	script_->write<std::uint16_t>(id);
}

void assembler::assemble_local_call(std::shared_ptr<instruction> inst, bool thread)
{
	script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

	std::int32_t addr = this->resolve_function(inst->data[1]);

	std::int32_t offset = addr - inst->index - 1;

	this->assemble_offset(offset);

	if (thread)
	{
		script_->write<std::uint8_t>(std::stol(inst->data[2]));
	}
}

void assembler::assemble_far_call(std::shared_ptr<instruction> inst, bool thread)
{
	script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));
	script_->write<std::uint8_t>(0); // 3 bytes placeholder
	script_->write<std::uint16_t>(0);

	std::uint16_t file_id = 0;
	std::uint16_t func_id = 0;

	if (thread)
	{
		script_->write<std::uint8_t>(std::stol(inst->data[1]));

		file_id = inst->data[2].substr(0, 3) == "id#" ? std::stol(inst->data[2].substr(3)) : resolver::file_id(inst->data[2]);
		func_id = inst->data[3].substr(0, 3) == "id#" ? std::stol(inst->data[3].substr(3)) : resolver::token_id(inst->data[3]);
	}
	else
	{
		file_id = inst->data[1].substr(0, 3) == "id#" ? std::stol(inst->data[1].substr(3)) : resolver::file_id(inst->data[1]);
		func_id = inst->data[2].substr(0, 3) == "id#" ? std::stol(inst->data[2].substr(3)) : resolver::token_id(inst->data[2]);
	}

	stack_->write<std::uint16_t>(file_id);
	if (file_id == 0) stack_->write_c_string(thread ? inst->data[2] : inst->data[1]);
	stack_->write<std::uint16_t>(func_id);
	if (func_id == 0) stack_->write_c_string(thread ? inst->data[3] : inst->data[2]);
}

void assembler::assemble_switch(std::shared_ptr<instruction> inst)
{
	script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

	std::int32_t addr = this->resolve_label(inst, inst->data[1]);

	script_->write<std::int32_t>(addr - inst->index - 4);
}

void assembler::assemble_end_switch(std::shared_ptr<instruction> inst)
{
	script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

	std::uint16_t casenum = 0;

	if (utils::string::is_number(inst->data[1]))
	{
		casenum = std::stol(inst->data[1]);
	}
	else
	{
		LOG_ERROR("invalid endswitch number!");
	}

	script_->write<std::uint16_t>(casenum);

	std::uint32_t internal_index = inst->index + 3;

	for (std::uint16_t i = 0; i < casenum; i++)
	{
		if (inst->data[2 + (3 * i)] == "case")
		{
			script_->write<uint32_t>(i + 1);
			stack_->write_c_string(utils::string::get_string_literal(inst->data[2 + (3 * i) + 1]));

			internal_index += 4;

			std::int32_t addr = this->resolve_label(inst, inst->data[2 + (3 * i) + 2]);

			this->assemble_offset(addr - internal_index);

			internal_index += 3;
		}
		else if (inst->data[2 + (3 * i)] == "default")
		{
			script_->write<uint32_t>(0);
			stack_->write_c_string("\x01");

			internal_index += 4;
			std::int32_t addr = this->resolve_label(inst, inst->data[2 + (3 * i) + 1]);

			this->assemble_offset(addr - internal_index);

			internal_index += 3;
		}
	}
}

void assembler::assemble_field_variable(std::shared_ptr<instruction> inst)
{
	script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

	std::uint16_t field_id = 0;

	if (inst->data[1].substr(0, 3) == "id#")
	{
		field_id = (std::uint16_t)std::stol(inst->data[1].substr(3));
	}
	else
	{
		field_id = resolver::token_id(inst->data[1]);

		if (field_id == 0)
		{
			field_id = 0xFFFF;
		}
	}

	script_->write<std::uint16_t>(field_id);

	if (field_id > 38305)
	{
		stack_->write<std::uint16_t>(0);
		stack_->write_c_string(inst->data[1]);
	}
}

void assembler::assemble_jump(std::shared_ptr<instruction> inst, bool expr, bool back)
{
	script_->write<std::uint8_t>(static_cast<std::uint8_t>(inst->opcode));

	std::int32_t addr = this->resolve_label(inst, inst->data[1]);

	if (expr)
	{
		script_->write<std::int16_t>(addr - inst->index - 3);
	}
	else if (back)
	{
		script_->write<std::int16_t>((inst->index + 3) - addr);
	}
	else
	{
		script_->write<std::int32_t>(addr - inst->index - 5);
	}
}

void assembler::assemble_offset(std::int32_t offset)
{
	offset = (offset << 10) >> 8;

	std::vector<std::uint8_t> bytes;
	bytes.resize(4);

	std::fill(bytes.begin(), bytes.end(), 0);
	*reinterpret_cast<std::int32_t*>(bytes.data()) = offset;

	script_->write<std::uint8_t>(bytes[0]);
	script_->write<std::uint8_t>(bytes[1]);
	script_->write<std::uint8_t>(bytes[2]);
}

auto assembler::resolve_function(const std::string& name) -> std::uint32_t
{
	std::string temp = name.substr(4);

	for (auto func : functions_)
	{
		if (func->name == temp)
		{
			return func->index;
		}
	}

	LOG_ERROR("Couldn't resolve local function address of '%s'!", temp.c_str());
	return 0;
}

auto assembler::resolve_label(std::shared_ptr<instruction> inst, const std::string& name) -> std::uint32_t
{
	for (auto& func : inst->parent->labels)
	{
		if (func.second == name)
		{
			return func.first;
		}
	}

	LOG_ERROR("Couldn't resolve label address of '%s'!", name.c_str());
	return 0;
}

}  // namespace IW6
