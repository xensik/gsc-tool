#include "stdinc.hpp"

namespace iw5
{
	std::unordered_map<opcode, std::string> opcode_names =
	{
		{ opcode::OP_End, "end" },
		{ opcode::OP_Return, "retn" },
		{ opcode::OP_GetByte, "get_byte" },
		{ opcode::OP_GetNegByte, "get_neg_byte" },
		{ opcode::OP_GetUnsignedShort, "get_ushort" },
		{ opcode::OP_GetNegUnsignedShort, "get_neg_ushort" },
		{ opcode::OP_GetInteger, "get_int" },
		{ opcode::OP_GetBuiltinFunction, "get_builtin_func" },
		{ opcode::OP_GetBuiltinMethod, "get_builtin_method" },
		{ opcode::OP_GetFloat, "get_float" },
		{ opcode::OP_GetString, "get_string" },
		{ opcode::OP_GetUndefined, "get_undefined" },
		{ opcode::OP_GetZero, "get_zero" },
		{ opcode::OP_waittillFrameEnd, "waittill_frame_end" },
		{ opcode::OP_CreateLocalVariable, "create_local_variable" },
		{ opcode::OP_RemoveLocalVariables, "remove_local_variables" },
		{ opcode::OP_EvalLocalVariableCached0, "eval_local_variable_cached0" },
		{ opcode::OP_EvalLocalVariableCached1, "eval_local_variable_cached1" },
		{ opcode::OP_EvalLocalVariableCached2, "eval_local_variable_cached2" },
		{ opcode::OP_EvalLocalVariableCached3, "eval_local_variable_cached3" },
		{ opcode::OP_EvalLocalVariableCached4, "eval_local_variable_cached4" },
		{ opcode::OP_EvalLocalVariableCached5, "eval_local_variable_cached5" },
		{ opcode::OP_EvalLocalVariableCached, "eval_local_variable_cached" },
		{ opcode::OP_EvalLocalArrayCached, "eval_local_array_cached" },
		{ opcode::OP_EvalArray, "eval_array" },
		{ opcode::OP_EvalNewLocalArrayRefCached0, "eval_new_local_array_ref_cached0" },
		{ opcode::OP_EvalLocalArrayRefCached0, "eval_local_array_ref_cached0" },
		{ opcode::OP_EvalLocalArrayRefCached, "eval_local_array_ref_cached" },
		{ opcode::OP_EvalArrayRef, "eval_array_ref" },
		{ opcode::OP_ClearArray, "clear_array" },
		{ opcode::OP_EmptyArray, "empty_array" },
		{ opcode::OP_AddArray, "add_array" },
		{ opcode::OP_PreScriptCall, "pre_script_call" },
		{ opcode::OP_ScriptLocalFunctionCall2, "script_local_func_call2" },
		{ opcode::OP_ScriptLocalFunctionCall, "script_local_func_call" },
		{ opcode::OP_ScriptLocalMethodCall, "script_local_method_call" },
		{ opcode::OP_ScriptLocalThreadCall, "script_local_thread_call" },
		{ opcode::OP_ScriptLocalChildThreadCall, "script_local_child_thread_call" },
		{ opcode::OP_ScriptLocalMethodThreadCall, "script_local_method_thread_call" },
		{ opcode::OP_ScriptLocalMethodChildThreadCall, "script_local_method_child_thread_call" },
		{ opcode::OP_ScriptFarFunctionCall2, "script_far_func_call2" },
		{ opcode::OP_ScriptFarFunctionCall, "script_far_func_call" },
		{ opcode::OP_ScriptFarMethodCall, "script_far_method_call" },
		{ opcode::OP_ScriptFarThreadCall, "script_far_thread_call" },
		{ opcode::OP_ScriptFarChildThreadCall, "script_far_child_thread_call" },
		{ opcode::OP_ScriptFarMethodThreadCall, "script_far_method_thread_call" },
		{ opcode::OP_ScriptFarMethodChildThreadCall, "script_far_method_child_thread_call" },
		{ opcode::OP_ScriptFunctionCallPointer, "script_func_call_pointer" },
		{ opcode::OP_ScriptMethodCallPointer, "script_method_call_pointer" },
		{ opcode::OP_ScriptThreadCallPointer, "script_thread_call_pointer" },
		{ opcode::OP_ScriptMethodChildThreadCallPointer, "script_method_child_thread_call_pointer" }, // its not exactly the same
		{ opcode::OP_ScriptMethodThreadCallPointer, "script_method_thread_call_pointer" },
		{ opcode::OP_ScriptMethodChildThreadCallPointer, "script_method_child_thread_call_pointer" },
		{ opcode::OP_CallBuiltinPointer, "call_builtin_pointer" },
		{ opcode::OP_CallBuiltinMethodPointer, "call_builtin_method_pointer" },
		{ opcode::OP_GetIString, "get_istring" },
		{ opcode::OP_GetVector, "get_vector" },
		{ opcode::OP_GetLevelObject, "get_level_obj" },
		{ opcode::OP_GetAnimObject, "get_anim_obj" },
		{ opcode::OP_GetSelf, "get_self" },
		{ opcode::OP_GetThisthread, "get_this_thread" },
		{ opcode::OP_GetLevel, "get_level" },
		{ opcode::OP_GetGame, "get_game" },
		{ opcode::OP_GetAnim, "get_anim" },
		{ opcode::OP_GetAnimation, "get_animation" },
		{ opcode::OP_GetGameRef, "get_game_ref" },
		{ opcode::OP_inc, "increment" },
		{ opcode::OP_dec, "decrement" },
		{ opcode::OP_bit_or, "bit_or" },
		{ opcode::OP_JumpOnFalseExpr, "jump_expr<false>" },
		{ opcode::OP_bit_ex_or, "bit_ex_or" },
		{ opcode::OP_bit_and, "bit_and" },
		{ opcode::OP_equality, "equality" },
		{ opcode::OP_inequality, "inequality" },
		{ opcode::OP_less, "less" },
		{ opcode::OP_greater, "greater" },
		{ opcode::OP_JumpOnTrueExpr, "jump_expr<true>" },
		{ opcode::OP_less_equal, "less_equal" },
		{ opcode::OP_jumpback, "jump_back" },
		{ opcode::OP_waittillmatch2, "waittillmatch2" },
		{ opcode::OP_waittill, "waittill" },
		{ opcode::OP_notify, "notify" },
		{ opcode::OP_endon, "endon" },
		{ opcode::OP_voidCodepos, "void_codepos" },
		{ opcode::OP_switch, "switch" },
		{ opcode::OP_endswitch, "endswitch" },
		{ opcode::OP_vector, "vector" },
		{ opcode::OP_JumpOnFalse, "jump<false>" },
		{ opcode::OP_greater_equal, "greater_equal" },
		{ opcode::OP_shift_left, "shift_left" },
		{ opcode::OP_shift_right, "shift_right" },
		{ opcode::OP_plus, "plus" },
		{ opcode::OP_jump, "jump" },
		{ opcode::OP_minus, "minus" },
		{ opcode::OP_multiply, "multiply" },
		{ opcode::OP_divide, "divide" },
		{ opcode::OP_mod, "mod" },
		{ opcode::OP_JumpOnTrue, "jump<true>" },
		{ opcode::OP_size, "size" },
		{ opcode::OP_waittillmatch, "waittillmatch" },
		{ opcode::OP_GetLocalFunction, "get_local_func" },
		{ opcode::OP_GetFarFunction, "get_far_func" },
		{ opcode::OP_GetSelfObject, "get_self_obj" },
		{ opcode::OP_EvalLevelFieldVariable, "eval_level_field_variable" },
		{ opcode::OP_EvalAnimFieldVariable, "eval_anim_field_variable" },
		{ opcode::OP_EvalSelfFieldVariable, "eval_self_field_variable" },
		{ opcode::OP_EvalFieldVariable, "eval_field_variable" },
		{ opcode::OP_EvalLevelFieldVariableRef, "eval_level_field_variable_ref" },
		{ opcode::OP_EvalAnimFieldVariableRef, "eval_anim_field_variable_ref" },
		{ opcode::OP_EvalSelfFieldVariableRef, "eval_self_field_variable_ref" },
		{ opcode::OP_EvalFieldVariableRef, "eval_field_variable_ref" },
		{ opcode::OP_ClearFieldVariable, "clear_field_variable" },
		{ opcode::OP_SafeCreateVariableFieldCached, "safe_create_variable_field_cached" },
		{ opcode::OP_SafeSetVariableFieldCached0, "safe_set_variable_field_cached0" },
		{ opcode::OP_SafeSetVariableFieldCached, "safe_set_variable_field_cached" },
		{ opcode::OP_SafeSetWaittillVariableFieldCached, "safe_set_waittill_variable_field_cached" },
		{ opcode::OP_GetAnimTree, "get_animtree" },
		{ opcode::OP_clearparams, "clearparams" },
		{ opcode::OP_checkclearparams, "checkclearparams" },
		{ opcode::OP_EvalLocalVariableRefCached0, "eval_local_variable_ref_cached0" },
		{ opcode::OP_EvalNewLocalVariableRefCached0, "eval_new_local_variable_ref_cached0" },
		{ opcode::OP_EvalLocalVariableRefCached, "eval_local_variable_ref_cached" },
		{ opcode::OP_SetLevelFieldVariableField, "set_level_field_variable_field" },
		{ opcode::OP_SetVariableField, "set_variable_field" },
		{ opcode::OP_ClearVariableField, "clear_variable_field" },
		{ opcode::OP_SetAnimFieldVariableField, "set_anim_field_vaiable_field" },
		{ opcode::OP_SetSelfFieldVariableField, "set_self_field_vaiable_field" },
		{ opcode::OP_SetLocalVariableFieldCached0, "set_local_variable_field_cached0" },
		{ opcode::OP_SetNewLocalVariableFieldCached0, "set_new_local_variable_field_cached0" },
		{ opcode::OP_SetLocalVariableFieldCached, "set_local_variable_field_cached" },
		{ opcode::OP_ClearLocalVariableFieldCached, "clear_local_variable_field_cached" },
		{ opcode::OP_ClearLocalVariableFieldCached0, "clear_local_variable_field_cached0" },
		{ opcode::OP_CallBuiltin0, "call<0>" },
		{ opcode::OP_CallBuiltin1, "call<1>" },
		{ opcode::OP_CallBuiltin2, "call<2>" },
		{ opcode::OP_CallBuiltin3, "call<3>" },
		{ opcode::OP_CallBuiltin4, "call<4>" },
		{ opcode::OP_CallBuiltin5, "call<5>" },
		{ opcode::OP_CallBuiltin, "call" },
		{ opcode::OP_CallBuiltinMethod0, "method<0>" },
		{ opcode::OP_CallBuiltinMethod1, "method<1>" },
		{ opcode::OP_CallBuiltinMethod2, "method<2>" },
		{ opcode::OP_CallBuiltinMethod3, "method<3>" },
		{ opcode::OP_CallBuiltinMethod4, "method<4>" },
		{ opcode::OP_CallBuiltinMethod5, "method<5>" },
		{ opcode::OP_CallBuiltinMethod, "method" },
		{ opcode::OP_wait, "wait" },
		{ opcode::OP_DecTop, "decrement_top" },
		{ opcode::OP_CastFieldObject, "cast_field_obj" },
		{ opcode::OP_EvalLocalVariableObjectCached, "eval_local_variable_obj_cached" },
		{ opcode::OP_CastBool, "cast_bool" },
		{ opcode::OP_BoolNot, "bool_not" },
		{ opcode::OP_BoolComplement, "bool_complement" },
	};

	std::unordered_map<std::string, opcode> opcode_ids
	{
		{ "end", opcode::OP_End },
		{ "retn", opcode::OP_Return },
		{ "get_byte", opcode::OP_GetByte },
		{ "get_neg_byte", opcode::OP_GetNegByte },
		{ "get_ushort", opcode::OP_GetUnsignedShort },
		{ "get_neg_ushort", opcode::OP_GetNegUnsignedShort },
		{ "get_int", opcode::OP_GetInteger },
		{ "get_builtin_func", opcode::OP_GetBuiltinFunction },
		{ "get_builtin_method", opcode::OP_GetBuiltinMethod },
		{ "get_float", opcode::OP_GetFloat },
		{ "get_string", opcode::OP_GetString },
		{ "get_undefined", opcode::OP_GetUndefined },
		{ "get_zero", opcode::OP_GetZero },
		{ "waittill_frame_end", opcode::OP_waittillFrameEnd },
		{ "create_local_variable", opcode::OP_CreateLocalVariable },
		{ "remove_local_variables", opcode::OP_RemoveLocalVariables },
		{ "eval_local_variable_cached0", opcode::OP_EvalLocalVariableCached0 },
		{ "eval_local_variable_cached1", opcode::OP_EvalLocalVariableCached1 },
		{ "eval_local_variable_cached2", opcode::OP_EvalLocalVariableCached2 },
		{ "eval_local_variable_cached3", opcode::OP_EvalLocalVariableCached3 },
		{ "eval_local_variable_cached4", opcode::OP_EvalLocalVariableCached4 },
		{ "eval_local_variable_cached5", opcode::OP_EvalLocalVariableCached5 },
		{ "eval_local_variable_cached", opcode::OP_EvalLocalVariableCached },
		{ "eval_local_array_cached", opcode::OP_EvalLocalArrayCached },
		{ "eval_array", opcode::OP_EvalArray },
		{ "eval_new_local_array_ref_cached0", opcode::OP_EvalNewLocalArrayRefCached0 },
		{ "eval_local_array_ref_cached0", opcode::OP_EvalLocalArrayRefCached0 },
		{ "eval_local_array_ref_cached", opcode::OP_EvalLocalArrayRefCached },
		{ "eval_array_ref", opcode::OP_EvalArrayRef },
		{ "clear_array", opcode::OP_ClearArray },
		{ "empty_array", opcode::OP_EmptyArray },
		{ "add_array", opcode::OP_AddArray },
		{ "pre_script_call", opcode::OP_PreScriptCall },
		{ "script_local_func_call2", opcode::OP_ScriptLocalFunctionCall2 },
		{ "script_local_func_call", opcode::OP_ScriptLocalFunctionCall },
		{ "script_local_method_call", opcode::OP_ScriptLocalMethodCall },
		{ "script_local_thread_call", opcode::OP_ScriptLocalThreadCall },
		{ "script_local_child_thread_call", opcode::OP_ScriptLocalChildThreadCall },
		{ "script_local_method_thread_call", opcode::OP_ScriptLocalMethodThreadCall },
		{ "script_local_method_child_thread_call", opcode::OP_ScriptLocalMethodChildThreadCall },
		{ "script_far_func_call2", opcode::OP_ScriptFarFunctionCall2 },
		{ "script_far_func_call", opcode::OP_ScriptFarFunctionCall },
		{ "script_far_method_call", opcode::OP_ScriptFarMethodCall },
		{ "script_far_thread_call", opcode::OP_ScriptFarThreadCall },
		{ "script_far_child_thread_call", opcode::OP_ScriptFarChildThreadCall },
		{ "script_far_method_thread_call", opcode::OP_ScriptFarMethodThreadCall },
		{ "script_far_method_child_thread_call", opcode::OP_ScriptFarMethodChildThreadCall },
		{ "script_func_call_pointer", opcode::OP_ScriptFunctionCallPointer },
		{ "script_method_call_pointer", opcode::OP_ScriptMethodCallPointer },
		{ "script_thread_call_pointer", opcode::OP_ScriptThreadCallPointer },
		{ "script_method_thread_call_pointer", opcode::OP_ScriptMethodThreadCallPointer },
		{ "script_method_child_thread_call_pointer", opcode::OP_ScriptMethodChildThreadCallPointer },
		{ "call_builtin_pointer", opcode::OP_CallBuiltinPointer },
		{ "call_builtin_method_pointer", opcode::OP_CallBuiltinMethodPointer },
		{ "get_istring", opcode::OP_GetIString },
		{ "get_vector", opcode::OP_GetVector },
		{ "get_level_obj", opcode::OP_GetLevelObject },
		{ "get_anim_obj", opcode::OP_GetAnimObject },
		{ "get_self", opcode::OP_GetSelf },
		{ "get_this_thread", opcode::OP_GetThisthread },
		{ "get_level", opcode::OP_GetLevel },
		{ "get_game", opcode::OP_GetGame },
		{ "get_anim", opcode::OP_GetAnim },
		{ "get_animation", opcode::OP_GetAnimation },
		{ "get_game_ref", opcode::OP_GetGameRef },
		{ "increment", opcode::OP_inc },
		{ "decrement", opcode::OP_dec },
		{ "bit_or", opcode::OP_bit_or },
		{ "jump_expr<false>", opcode::OP_JumpOnFalseExpr },
		{ "bit_ex_or", opcode::OP_bit_ex_or },
		{ "bit_and", opcode::OP_bit_and },
		{ "equality", opcode::OP_equality },
		{ "inequality", opcode::OP_inequality },
		{ "less", opcode::OP_less },
		{ "greater", opcode::OP_greater },
		{ "jump_expr<true>", opcode::OP_JumpOnTrueExpr },
		{ "less_equal", opcode::OP_less_equal },
		{ "jump_back", opcode::OP_jumpback },
		{ "waittillmatch2", opcode::OP_waittillmatch2 },
		{ "waittill", opcode::OP_waittill },
		{ "notify", opcode::OP_notify },
		{ "endon", opcode::OP_endon },
		{ "void_codepos", opcode::OP_voidCodepos },
		{ "switch", opcode::OP_switch },
		{ "endswitch", opcode::OP_endswitch },
		{ "vector", opcode::OP_vector },
		{ "jump<false>", opcode::OP_JumpOnFalse },
		{ "greater_equal", opcode::OP_greater_equal },
		{ "shift_left", opcode::OP_shift_left },
		{ "shift_right", opcode::OP_shift_right },
		{ "plus", opcode::OP_plus },
		{ "jump", opcode::OP_jump },
		{ "minus", opcode::OP_minus },
		{ "multiply", opcode::OP_multiply },
		{ "divide", opcode::OP_divide },
		{ "mod", opcode::OP_mod },
		{ "jump<true>", opcode::OP_JumpOnTrue },
		{ "size", opcode::OP_size },
		{ "waittillmatch", opcode::OP_waittillmatch },
		{ "get_local_func", opcode::OP_GetLocalFunction },
		{ "get_far_func", opcode::OP_GetFarFunction },
		{ "get_self_obj", opcode::OP_GetSelfObject },
		{ "eval_level_field_variable", opcode::OP_EvalLevelFieldVariable },
		{ "eval_anim_field_variable", opcode::OP_EvalAnimFieldVariable },
		{ "eval_self_field_variable", opcode::OP_EvalSelfFieldVariable },
		{ "eval_field_variable", opcode::OP_EvalFieldVariable },
		{ "eval_level_field_variable_ref", opcode::OP_EvalLevelFieldVariableRef },
		{ "eval_anim_field_variable_ref", opcode::OP_EvalAnimFieldVariableRef },
		{ "eval_self_field_variable_ref", opcode::OP_EvalSelfFieldVariableRef },
		{ "eval_field_variable_ref", opcode::OP_EvalFieldVariableRef },
		{ "clear_field_variable", opcode::OP_ClearFieldVariable },
		{ "safe_create_variable_field_cached", opcode::OP_SafeCreateVariableFieldCached },
		{ "safe_set_variable_field_cached0", opcode::OP_SafeSetVariableFieldCached0 },
		{ "safe_set_variable_field_cached", opcode::OP_SafeSetVariableFieldCached },
		{ "safe_set_waittill_variable_field_cached", opcode::OP_SafeSetWaittillVariableFieldCached },
		{ "get_animtree", opcode::OP_GetAnimTree },
		{ "clearparams", opcode::OP_clearparams },
		{ "checkclearparams", opcode::OP_checkclearparams },
		{ "eval_local_variable_ref_cached0", opcode::OP_EvalLocalVariableRefCached0 },
		{ "eval_new_local_variable_ref_cached0", opcode::OP_EvalNewLocalVariableRefCached0 },
		{ "eval_local_variable_ref_cached", opcode::OP_EvalLocalVariableRefCached},
		{ "set_level_field_variable_field", opcode::OP_SetLevelFieldVariableField },
		{ "set_variable_field", opcode::OP_SetVariableField },
		{ "clear_variable_field", opcode::OP_ClearVariableField },
		{ "set_anim_field_vaiable_field", opcode::OP_SetAnimFieldVariableField },
		{ "set_self_field_vaiable_field", opcode::OP_SetSelfFieldVariableField },
		{ "set_local_variable_field_cached0", opcode::OP_SetLocalVariableFieldCached0 },
		{ "set_new_local_variable_field_cached0", opcode::OP_SetNewLocalVariableFieldCached0 },
		{ "set_local_variable_field_cached", opcode::OP_SetLocalVariableFieldCached },
		{ "clear_local_variable_field_cached", opcode::OP_ClearLocalVariableFieldCached },
		{ "clear_local_variable_field_cached0", opcode::OP_ClearLocalVariableFieldCached0 },
		{ "call<0>", opcode::OP_CallBuiltin0 },
		{ "call<1>", opcode::OP_CallBuiltin1 },
		{ "call<2>", opcode::OP_CallBuiltin2 },
		{ "call<3>", opcode::OP_CallBuiltin3 },
		{ "call<4>", opcode::OP_CallBuiltin4 },
		{ "call<5>", opcode::OP_CallBuiltin5 },
		{ "call", opcode::OP_CallBuiltin },
		{ "method<0>", opcode::OP_CallBuiltinMethod0 },
		{ "method<1>", opcode::OP_CallBuiltinMethod1 },
		{ "method<2>", opcode::OP_CallBuiltinMethod2 },
		{ "method<3>", opcode::OP_CallBuiltinMethod3 },
		{ "method<4>", opcode::OP_CallBuiltinMethod4 },
		{ "method<5>", opcode::OP_CallBuiltinMethod5 },
		{ "method", opcode::OP_CallBuiltinMethod },
		{ "wait", opcode::OP_wait },
		{ "decrement_top", opcode::OP_DecTop },
		{ "cast_field_obj", opcode::OP_CastFieldObject },
		{ "eval_local_variable_obj_cached", opcode::OP_EvalLocalVariableObjectCached },
		{ "cast_bool", opcode::OP_CastBool },
		{ "bool_not", opcode::OP_BoolNot },
		{ "bool_complement", opcode::OP_BoolComplement },
	};

	auto GetOpCodeName(opcode op) -> std::string
	{
		if (opcode_names.find(op) != opcode_names.end())
			return opcode_names[op];

		LOG_ERROR("Couldn't resolve opcode 0x%X!", op);
		return "";
	}

	auto GetOpCodeId(const std::string& name) -> opcode
	{
		if (opcode_ids.find(name) != opcode_ids.end())
			return opcode_ids[name];

		LOG_ERROR("Couldn't resolve opcode \"%s\"!", name.data());
		return opcode::OP_Count;
	}

	auto GetOpCodeSize(opcode opcode) -> std::size_t
	{
		switch (opcode)
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
			return 1;
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
		case opcode::OP_GetNegByte:
			return 2;
			break;
		case opcode::OP_GetUnsignedShort:
		case opcode::OP_jumpback:
		case opcode::OP_waittillmatch:
		case opcode::OP_GetNegUnsignedShort:
		case opcode::OP_JumpOnFalseExpr:
		case opcode::OP_JumpOnTrueExpr:
		case opcode::OP_JumpOnFalse:
		case opcode::OP_JumpOnTrue:
		case opcode::OP_GetBuiltinFunction:
		case opcode::OP_GetBuiltinMethod:
		case opcode::OP_CallBuiltin0:
		case opcode::OP_CallBuiltin1:
		case opcode::OP_CallBuiltin2:
		case opcode::OP_CallBuiltin3:
		case opcode::OP_CallBuiltin4:
		case opcode::OP_CallBuiltin5:
		case opcode::OP_CallBuiltinMethod0:
		case opcode::OP_CallBuiltinMethod1:
		case opcode::OP_CallBuiltinMethod2:
		case opcode::OP_CallBuiltinMethod3:
		case opcode::OP_CallBuiltinMethod4:
		case opcode::OP_CallBuiltinMethod5:
		case opcode::OP_GetString:
		case opcode::OP_GetIString:
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
		case opcode::OP_GetAnimTree:
		case opcode::OP_endswitch:
			return 3;
			break;
		case opcode::OP_ScriptLocalFunctionCall2:
		case opcode::OP_ScriptLocalFunctionCall:
		case opcode::OP_ScriptLocalMethodCall:
		case opcode::OP_GetLocalFunction:
		case opcode::OP_ScriptFarFunctionCall2:
		case opcode::OP_ScriptFarFunctionCall:
		case opcode::OP_ScriptFarMethodCall:
		case opcode::OP_GetFarFunction:
		case opcode::OP_CallBuiltin:
		case opcode::OP_CallBuiltinMethod:
			return 4;
			break;
		case opcode::OP_GetInteger:
		case opcode::OP_switch:
		case opcode::OP_jump:
		case opcode::OP_GetFloat:
		case opcode::OP_ScriptLocalThreadCall:
		case opcode::OP_ScriptLocalChildThreadCall:
		case opcode::OP_ScriptLocalMethodThreadCall:
		case opcode::OP_ScriptLocalMethodChildThreadCall:
		case opcode::OP_ScriptFarThreadCall:
		case opcode::OP_ScriptFarChildThreadCall:
		case opcode::OP_ScriptFarMethodThreadCall:
		case opcode::OP_ScriptFarMethodChildThreadCall:
		case opcode::OP_GetAnimation:
			return 5;
			break;
		case opcode::OP_GetVector:
			return 13;
			break;
		default:
			LOG_ERROR("Couldn't resolve instruction size 0x%X!", opcode);
			return 0;
		}
	}
}