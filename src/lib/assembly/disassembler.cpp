// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "gsc_tool.hpp"

namespace gsc
{

disassembler::disassembler(bool ida_output)
{
	ida_output_ = ida_output;
	output_ = std::make_unique<xsk::byte_buffer>(0x100000);
}

void disassembler::disassemble(std::shared_ptr<xsk::byte_buffer> script, std::shared_ptr<xsk::byte_buffer> stack)
{
	script_ = script;
	stack_ = stack;
	output_->clear();
	functions_.clear();

	script_->seek(1); // skip opcode 00

	while (stack_->is_avail() && script_->is_avail())
	{
		auto func = std::make_shared<function>();
		func->index = script_->get_pos();
		func->size = stack_->read<std::uint32_t>();
		func->id = stack_->read<std::uint16_t>();
		func->name = func->id == 0 ? stack_->read_string() : get_token_name(func->id);
		functions_.push_back(func);

		this->dissasemble_function(func);
	}

	// fix local function calls here once we have all function names created
	this->resolve_local_functions();
}

auto disassembler::output() -> std::vector<std::shared_ptr<function>>
{
	return functions_;
}

auto disassembler::output_buffer() -> std::vector<std::uint8_t>
{
	this->print_script_name(""); // TODO: add file name conversor

	for (auto& func : functions_)
	{
		this->print_function(func);

		for (auto& inst : func->instructions)
		{
			if (func->labels.find(inst->index) != func->labels.end())
			{
				this->print_label(func->labels[inst->index]);
			}

			this->print_instruction(inst);
		}
	}

	std::vector<std::uint8_t> output;
	output.resize(output_->get_pos());
	memcpy(output.data(), output_->get_buffer().data(), output.size());

	return output;
}

void disassembler::dissasemble_function(std::shared_ptr<function> func)
{
	auto size = func->size;

	while (size > 0)
	{
		auto inst = std::make_shared<instruction>();
		inst->index = script_->get_pos();
		inst->opcode = static_cast<opcode>(script_->read<std::uint8_t>());
		inst->parent = func;
		func->instructions.push_back(inst);

		this->dissasemble_instruction(inst);

		size -= inst->size;
	}
}

void disassembler::dissasemble_instruction(std::shared_ptr<instruction> inst)
{
	switch (inst->opcode)
	{
	case opcode::OP_End:
		inst->size = 1;
		break;
	case opcode::OP_Return:
		inst->size = 1;
		break;
	case opcode::OP_GetByte:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_GetNegByte:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::int8_t>()));
		break;
	case opcode::OP_GetUnsignedShort:
		inst->size = 3;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint16_t>()));
		break;
	case opcode::OP_GetNegUnsignedShort:
		inst->size = 3;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::int16_t>()));
		break;
	case opcode::OP_GetInteger:
		inst->size = 5;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::int32_t>()));
		break;
	case opcode::OP_GetBuiltinFunction:
		this->disassemble_builtin_call(inst, false, false);
		break;
	case opcode::OP_GetBuiltinMethod:
		this->disassemble_builtin_call(inst, true, false);
		break;
	case opcode::OP_GetFloat:
		inst->size = 5;
		inst->data.push_back(xsk::string::va("%g", script_->read<float>()));
		break;
	case opcode::OP_GetString:
		inst->size = 3;
		inst->data.push_back(xsk::string::va("\"%s\"", stack_->read_string().data()));
		script_->seek(2);
		break;
	case opcode::OP_GetUndefined:
		inst->size = 1;
		break;
	case opcode::OP_GetZero:
		inst->size = 1;
		break;
	case opcode::OP_waittillFrameEnd:
		inst->size = 1;
		break;
	case opcode::OP_CreateLocalVariable:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_RemoveLocalVariables:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_EvalLocalVariableCached0:
	case opcode::OP_EvalLocalVariableCached1:
	case opcode::OP_EvalLocalVariableCached2:
	case opcode::OP_EvalLocalVariableCached3:
	case opcode::OP_EvalLocalVariableCached4:
	case opcode::OP_EvalLocalVariableCached5:
		inst->size = 1;
		break;
	case opcode::OP_EvalLocalVariableCached:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_EvalLocalArrayCached:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_EvalArray:
		inst->size = 1;
		break;
	case opcode::OP_EvalNewLocalArrayRefCached0:
		inst->size = 1;
		break;
	case opcode::OP_EvalLocalArrayRefCached0:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_EvalLocalArrayRefCached:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_EvalArrayRef:
		inst->size = 1;
		break;
	case opcode::OP_ClearArray:
		inst->size = 1;
		break;
	case opcode::OP_EmptyArray:
		inst->size = 1;
		break;
	case opcode::OP_AddArray:
		inst->size = 1;
		break;
	case opcode::OP_PreScriptCall:
		inst->size = 1;
		break;
	case opcode::OP_ScriptLocalFunctionCall2:
	case opcode::OP_ScriptLocalFunctionCall:
	case opcode::OP_ScriptLocalMethodCall:
		this->disassemble_local_call(inst, false);
		break;
	case opcode::OP_ScriptLocalThreadCall:
	case opcode::OP_ScriptLocalChildThreadCall:
	case opcode::OP_ScriptLocalMethodThreadCall:
	case opcode::OP_ScriptLocalMethodChildThreadCall:
		this->disassemble_local_call(inst, true);
		break;
	case opcode::OP_ScriptFarFunctionCall2:
	case opcode::OP_ScriptFarFunctionCall:
	case opcode::OP_ScriptFarMethodCall:
		this->disassemble_far_call(inst, false);
		break;
	case opcode::OP_ScriptFarThreadCall:
	case opcode::OP_ScriptFarChildThreadCall:
	case opcode::OP_ScriptFarMethodThreadCall:
	case opcode::OP_ScriptFarMethodChildThreadCall:
		this->disassemble_far_call(inst, true);
		break;
	case opcode::OP_ScriptFunctionCallPointer:
		inst->size = 1;
		break;
	case opcode::OP_ScriptMethodCallPointer:
		inst->size = 1;
		break;
	case opcode::OP_ScriptThreadCallPointer:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_ScriptMethodChildThreadCallPointer_0:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_ScriptMethodThreadCallPointer:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_ScriptMethodChildThreadCallPointer:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_CallBuiltinPointer:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_CallBuiltinMethodPointer:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_GetIString:
		inst->size = 3;
		script_->seek(2);
		inst->data.push_back(xsk::string::va("\"%s\"", stack_->read_string().data()));
		break;
	case opcode::OP_GetVector:
		inst->size = 13;
		inst->data.push_back(xsk::string::va("%g", script_->read<float>()));
		inst->data.push_back(xsk::string::va("%g", script_->read<float>()));
		inst->data.push_back(xsk::string::va("%g", script_->read<float>()));
		break;
	case opcode::OP_GetLevelObject:
		inst->size = 1;
		break;
	case opcode::OP_GetAnimObject:
		inst->size = 1;
		break;
	case opcode::OP_GetSelf:
		inst->size = 1;
		break;
	case opcode::OP_GetThisthread:
		inst->size = 1;
		break;
	case opcode::OP_GetLevel:
		inst->size = 1;
		break;
	case opcode::OP_GetGame:
		inst->size = 1;
		break;
	case opcode::OP_GetAnim:
		inst->size = 1;
	case opcode::OP_GetAnimation:
		inst->size = 5;
		script_->seek(4);
		inst->data.push_back(xsk::string::va("\"%s\"", stack_->read_string().data()));
		inst->data.push_back(xsk::string::va("\"%s\"", stack_->read_string().data()));
		break;
	case opcode::OP_GetGameRef:
		inst->size = 1;
		break;
	case opcode::OP_inc:
		inst->size = 1;
		break;
	case opcode::OP_dec:
		inst->size = 1;
		break;
	case opcode::OP_bit_or:
		inst->size = 1;
		break;
	case opcode::OP_JumpOnFalseExpr:
		this->disassemble_jump(inst, true, false);
		break;
	case opcode::OP_bit_ex_or:
		inst->size = 1;
		break;
	case opcode::OP_bit_and:
		inst->size = 1;
		break;
	case opcode::OP_equality:
		inst->size = 1;
		break;
	case opcode::OP_inequality:
		inst->size = 1;
		break;
	case opcode::OP_less:
		inst->size = 1;
		break;
	case opcode::OP_greater:
		inst->size = 1;
		break;
	case opcode::OP_JumpOnTrueExpr:
		this->disassemble_jump(inst, true, false);
		break;
	case opcode::OP_less_equal:
		inst->size = 1;
		break;
	case opcode::OP_jumpback:
		this->disassemble_jump(inst, false, true);
		break;
	case opcode::OP_waittillmatch2:
		// NOP
		break;
	case opcode::OP_waittill:
		inst->size = 1;
		break;
	case opcode::OP_notify:
		inst->size = 1;
		break;
	case opcode::OP_endon:
		inst->size = 1;
		break;
	case opcode::OP_voidCodepos:
		inst->size = 1;
		break;
	case opcode::OP_switch:
		this->disassemble_switch(inst);
		break;
	case opcode::OP_endswitch:
		this->disassemble_end_switch(inst);
		break;
	case opcode::OP_vector:
		inst->size = 1;
		break;
	case opcode::OP_JumpOnFalse:
		this->disassemble_jump(inst, true, false);
		break;
	case opcode::OP_greater_equal:
		inst->size = 1;
		break;
	case opcode::OP_shift_left:
		inst->size = 1;
		break;
	case opcode::OP_shift_right:
		inst->size = 1;
		break;
	case opcode::OP_plus:
		inst->size = 1;
		break;
	case opcode::OP_jump:
		this->disassemble_jump(inst, false, false);
		break;
	case opcode::OP_minus:
		inst->size = 1;
		break;
	case opcode::OP_multiply:
		inst->size = 1;
		break;
	case opcode::OP_divide:
		inst->size = 1;
		break;
	case opcode::OP_mod:
		inst->size = 1;
		break;
	case opcode::OP_JumpOnTrue:
		this->disassemble_jump(inst, true, false);
		break;
	case opcode::OP_size:
		inst->size = 1;
		break;
	case opcode::OP_waittillmatch:
		inst->size = 3;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint16_t>()));
		break;
	case opcode::OP_GetLocalFunction:
		this->disassemble_local_call(inst, false);
		break;
	case opcode::OP_GetFarFunction:
		this->disassemble_far_call(inst, false);
		break;
	case opcode::OP_GetSelfObject:
		inst->size = 1;
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
		this->disassemble_field_variable(inst);
		break;
	case opcode::OP_SafeCreateVariableFieldCached:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_SafeSetVariableFieldCached0:
		inst->size = 1;
		break;
	case opcode::OP_SafeSetVariableFieldCached:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_SafeSetWaittillVariableFieldCached:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_GetAnimTree:
		inst->size = 2;
		script_->seek(1);
		inst->data.push_back(xsk::string::va("\"%s\"", stack_->read_string().data()));
		break;
	case opcode::OP_clearparams:
		inst->size = 1;
		break;
	case opcode::OP_checkclearparams:
		inst->size = 1;
		break;
	case opcode::OP_EvalLocalVariableRefCached0:
		inst->size = 1;
		break;
	case opcode::OP_EvalNewLocalVariableRefCached0:
		inst->size = 1;
		break;
	case opcode::OP_EvalLocalVariableRefCached:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_SetVariableField:
		inst->size = 1;
		break;
	case opcode::OP_SetLocalVariableFieldCached0:
		inst->size = 1;
		break;
	case opcode::OP_SetNewLocalVariableFieldCached0:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_SetLocalVariableFieldCached:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_ClearLocalVariableFieldCached:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_ClearLocalVariableFieldCached0:
		inst->size = 1;
		break;
	case opcode::OP_CallBuiltin0:
	case opcode::OP_CallBuiltin1:
	case opcode::OP_CallBuiltin2:
	case opcode::OP_CallBuiltin3:
	case opcode::OP_CallBuiltin4:
	case opcode::OP_CallBuiltin5:
		this->disassemble_builtin_call(inst, false, false);
		break;
	case opcode::OP_CallBuiltin:
		this->disassemble_builtin_call(inst, false, true);
		break;
	case opcode::OP_CallBuiltinMethod0:
	case opcode::OP_CallBuiltinMethod1:
	case opcode::OP_CallBuiltinMethod2:
	case opcode::OP_CallBuiltinMethod3:
	case opcode::OP_CallBuiltinMethod4:
	case opcode::OP_CallBuiltinMethod5:
		this->disassemble_builtin_call(inst, true, false);
		break;
	case opcode::OP_CallBuiltinMethod:
		this->disassemble_builtin_call(inst, true, true);
		break;
	case opcode::OP_wait:
		inst->size = 1;
		break;
	case opcode::OP_DecTop:
		inst->size = 1;
		break;
	case opcode::OP_CastFieldObject:
		inst->size = 1;
		break;
	case opcode::OP_EvalLocalVariableObjectCached:
		inst->size = 2;
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
		break;
	case opcode::OP_CastBool:
		inst->size = 1;
		break;
	case opcode::OP_BoolNot:
		inst->size = 1;
		break;
	case opcode::OP_BoolComplement:
		inst->size = 1;
		break;
	default:
		XSK_ERROR("%04X UNHANDLED OPCODE (%X)!", inst->index, inst->opcode);
		break;
	}
}

void disassembler::disassemble_builtin_call(std::shared_ptr<instruction> inst, bool method, bool arg_num)
{
	inst->size = arg_num ? 4 : 3;

	if (arg_num)
	{
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
	}

	if (method)
	{
		inst->data.push_back(get_builtin_method_name(script_->read<std::uint16_t>()));
	}
	else
	{
		inst->data.push_back(get_builtin_func_name(script_->read<std::uint16_t>()));
	}
}

void disassembler::disassemble_local_call(std::shared_ptr<instruction> inst, bool thread)
{
	inst->size = thread ? 5 : 4;

	std::int32_t offset = this->disassemble_offset();

	inst->data.push_back(xsk::string::va("%X", offset + inst->index + 1));

	if (thread)
	{
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
	}
}

void disassembler::disassemble_far_call(std::shared_ptr<instruction> inst, bool thread)
{
	inst->size = thread ? 5 : 4;

	script_->seek(3); // placeholder 24bit offset

	if (thread)
	{
		inst->data.push_back(xsk::string::va("%i", script_->read<std::uint8_t>()));
	}

	auto file_id = stack_->read<std::uint16_t>();
	auto file_name = file_id == 0 ? stack_->read_string() : get_file_name(file_id);
	auto func_id = stack_->read<std::uint16_t>();
	auto func_name = func_id == 0 ? stack_->read_string() : get_token_name(func_id);

	inst->data.push_back(file_name != "" ? file_name : xsk::string::va("%i", file_id));
	inst->data.push_back(func_name != "" ? func_name : xsk::string::va("%i", func_id));
}

void disassembler::disassemble_jump(std::shared_ptr<instruction> inst, bool expr, bool back)
{
	inst->size = (expr || back) ? 3 : 5;

	std::int32_t addr;
	std::string label;

	if (expr)
	{
		addr = inst->index + 3 + script_->read<std::int16_t>();
		label = xsk::string::va("loc_%X", addr);
		inst->data.push_back(label);
	}
	else if (back)
	{
		addr = inst->index + 3 - script_->read<std::uint16_t>();
		label = xsk::string::va("loc_%X", addr);
		inst->data.push_back(label);
	}
	else
	{
		addr = inst->index + 5 + script_->read<std::int32_t>();
		label = xsk::string::va("loc_%X", addr);
		inst->data.push_back(label);
	}

	inst->parent->labels[addr] = label;
}

void disassembler::disassemble_field_variable(std::shared_ptr<instruction> inst)
{
	inst->size = 3;

	std::uint16_t field_id = script_->read<std::uint16_t>();
	std::string field_name = field_id > 33386 ? stack_->read_opaque_string() : get_token_name(field_id);

	inst->data.push_back(field_name != "" ? field_name : xsk::string::va("%i", field_id));
}

void disassembler::disassemble_switch(std::shared_ptr<instruction> inst)
{
	inst->size = 5;

	std::int32_t addr = inst->index + 4 + script_->read<std::int32_t>();
	std::string label = xsk::string::va("loc_%X", addr);

	inst->data.push_back(label);
	inst->parent->labels[addr] = label;
}

void disassembler::disassemble_end_switch(std::shared_ptr<instruction> inst)
{
	inst->size = 3;

	std::uint16_t case_num = script_->read<std::uint16_t>();
	inst->data.push_back(xsk::string::va("%i", case_num));

	std::uint32_t internal_index = inst->index + 3;

	if (case_num)
	{
		for (auto i = case_num; i > 0; i--)
		{
			std::uint32_t case_label = script_->read<std::uint32_t>();

			if (case_label < 0x10000 && case_label > 0)
			{
				inst->data.push_back("case");
				inst->data.push_back(xsk::string::va("\"%s\"", stack_->read_string().data()));
			}
			else if (case_label < 0x10000)
			{
				inst->data.push_back("default");
				stack_->read<std::uint16_t>(); // should be 01 00 (opaque string id)
			}
			else
			{
				inst->data.push_back("case");
				inst->data.push_back(xsk::string::va("%i", case_label & 0xFFFF));
			}

			inst->size += 4;
			internal_index += 4;

			auto addr = this->disassemble_offset() + internal_index;
			std::string label = xsk::string::va("loc_%X", addr);
			inst->data.push_back(label);

			inst->parent->labels[addr] = label;

			inst->size += 3;
			internal_index += 3;
		}
	}
}

auto disassembler::disassemble_offset() -> std::int32_t
{
	std::vector<std::uint8_t> bytes;

	bytes.resize(4);
	std::fill(bytes.begin(), bytes.end(), 0);

	for (int i = 0; i < 3; i++)
	{
		bytes[i] = script_->read<std::uint8_t>();
	}

	std::int32_t offset = *reinterpret_cast<std::int32_t*>(bytes.data());

	offset = (offset << 8) >> 10;

	return offset;
}

void disassembler::resolve_local_functions()
{
	for (auto& func : functions_)
	{
		for (auto& inst : func->instructions)
		{
			switch (inst->opcode)
			{
			case opcode::OP_GetLocalFunction:
			case opcode::OP_ScriptLocalFunctionCall:
			case opcode::OP_ScriptLocalFunctionCall2:
			case opcode::OP_ScriptLocalMethodCall:
			case opcode::OP_ScriptLocalThreadCall:
			case opcode::OP_ScriptLocalChildThreadCall:
			case opcode::OP_ScriptLocalMethodThreadCall:
			case opcode::OP_ScriptLocalMethodChildThreadCall:
				inst->data.at(0) = this->resolve_function(inst->data[0]);
				break;
			default:
				break;
			}
		}
	}
}

auto disassembler::resolve_function(const std::string& index) -> std::string
{
	if (xsk::string::is_hex_number(index))
	{
		std::uint32_t idx = std::stoul(index, nullptr, 16);

		for (auto& func : functions_)
		{
			if (func->index == idx)
			{
				if (func->name != "")
					return xsk::string::va("sub_%s", func->name.data());
				else
					return xsk::string::va("sub_%i", func->id);
			}
		}

		XSK_ERROR("Couldn't resolve function name at index '0x%04X'!", idx);
		return index;
	}
	else
	{
		XSK_ERROR("\"%s\" is not valid function address!", index.c_str());
		return index;
	}
}

void disassembler::print_script_name(const std::string& name)
{
	output_->write_cpp_string(xsk::string::va("script_asm %s\n", name.data()));
}

void disassembler::print_opcodes(std::uint32_t index, std::uint32_t size)
{
	if (ida_output_)
	{
		output_->write_cpp_string(xsk::string::va("%04X\t", index));
		output_->write_cpp_string(xsk::string::va("%-20s \t\t", script_->get_bytes_print(index, size).data()));
	}
	else
	{
		output_->write_cpp_string("\t\t");
	}
}

void disassembler::print_function(std::shared_ptr<function> func)
{
	output_->write_cpp_string("\n");

	if (ida_output_)
	{
		output_->write_cpp_string(xsk::string::va("\t%-20s", ""));
	}

	if (func->name != "")
	{
		output_->write_cpp_string(xsk::string::va("sub_%s\n", func->name.data()));
	}
	else
	{
		output_->write_cpp_string(xsk::string::va("sub_%i\n", func->id));
	}
}

void disassembler::print_instruction(std::shared_ptr<instruction> inst)
{
	switch (inst->opcode)
	{
	case opcode::OP_endswitch:
		this->print_opcodes(inst->index, 3);
		output_->write_cpp_string(xsk::string::va("%s", get_opcode_name(inst->opcode).data()));
		output_->write_cpp_string(xsk::string::va(" %s\n", inst->data[0].data()));
		{
			std::uint32_t totalcase = std::stoul(inst->data[0]);
			auto index = 0;
			for (auto casenum = 0; casenum < totalcase; casenum++)
			{
				this->print_opcodes(inst->index, 7);
				if (inst->data[1 + index] == "case")
				{
					output_->write_cpp_string(xsk::string::va("%s %s %s", inst->data[1 + index].data(), inst->data[1 + index + 1].data(), inst->data[1 + index + 2].data()));
					index += 3;
				}
				else if (inst->data[1 + index] == "default")
				{
					output_->write_cpp_string(xsk::string::va("%s %s", inst->data[1 + index].data(), inst->data[1 + index + 1].data()));
					index += 2;
				}
				if (casenum != totalcase - 1)
					output_->write_cpp_string("\n");
			}
		}
		break;
	default:
		this->print_opcodes(inst->index, inst->size);
		output_->write_cpp_string(xsk::string::va("%s", get_opcode_name(inst->opcode).data()));
		for (auto& d : inst->data)
		{
			output_->write_cpp_string(xsk::string::va(" %s", d.data()));
		}
		break;
	}

	output_->write_cpp_string("\n");
}

void disassembler::print_label(const std::string& label)
{
	if (ida_output_)
	{
		output_->write_cpp_string("\n\t");
		output_->write_cpp_string(xsk::string::va("%-20s ", ""));
	}

	output_->write_cpp_string(xsk::string::va("\t%s\n", label.data()));
}

} // namespace gsc