// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW6.hpp"

namespace IW6
{

auto resolver::opcode_id(const std::string& name) -> opcode
{
	const auto itr = opcode_map.find(name);

	if (itr != opcode_map.end())
	{
		return itr->second;
	}

	LOG_ERROR("Couldn't resolve opcode id for name '%s'!", name.data());
	return opcode::OP_Count;
}

auto resolver::opcode_name(opcode id) -> std::string
{
	for (auto& opcode : opcode_map)
	{
		if (opcode.second == id)
		{
			return opcode.first;
		}
	}

	LOG_ERROR("Couldn't resolve opcode name for id '0x%hhX'!", id);
	return "";
}

auto resolver::builtin_func_id(const std::string& name) -> std::uint16_t
{
	const auto itr = builtin_function_map.find(name);

	if (itr != builtin_function_map.end())
	{
		return itr->second;
	}

	LOG_DEBUG("Couldn't resolve builtin function id for name '%s'!", name.data());
	return 0xFFFF;
}

auto resolver::builtin_func_name(std::uint16_t id) -> std::string
{
	for (auto& field : builtin_function_map)
	{
		if (field.second == id)
		{
			return field.first;
		}
	}

	LOG_DEBUG("Couldn't resolve builtin function name for id '%i'!", id);
	return utils::string::va("id#%i", id);
}

auto resolver::builtin_method_id(const std::string& name) -> std::uint16_t
{
	const auto itr = builtin_method_map.find(name);

	if (itr != builtin_method_map.end())
	{
		return itr->second;
	}

	LOG_DEBUG("Couldn't resolve builtin method id for name '%s'!", name.data());
	return 0xFFFF;
}

auto resolver::builtin_method_name(std::uint16_t id) -> std::string
{
	for (auto& field : builtin_method_map)
	{
		if (field.second == id)
		{
			return field.first;
		}
	}
	LOG_DEBUG("Couldn't resolve builtin method name for id '%i'!", id);
	return utils::string::va("id#%i", id);
}

auto resolver::file_id(const std::string& name) -> std::uint16_t
{
	const auto itr = file_map.find(name);

	if (itr != file_map.end())
	{
		return itr->second;
	}

	LOG_DEBUG("Couldn't resolve file id for name '%s'!", name.data());
	return 0;
}

auto resolver::file_name(std::uint16_t id) -> std::string
{
	for (auto& file : file_map)
	{
		if (file.second == id)
		{
			return file.first;
		}
	}

	LOG_DEBUG("Couldn't resolve file name for id '%i'!", id);
	return utils::string::va("id#%i", id);
}

auto resolver::token_id(const std::string& name) -> std::uint16_t
{
	const auto itr = token_map.find(name);

	if (itr != token_map.end())
	{
		return itr->second;
	}

	LOG_DEBUG("Couldn't resolve token id for name '%s'!", name.data());
	return 0;
}

auto resolver::token_name(std::uint16_t id) -> std::string
{
	for (auto& func : token_map)
	{
		if (func.second == id)
		{
			return func.first;
		}
	}

	LOG_DEBUG("Couldn't resolve token name for id '%i'!", id);
	return utils::string::va("id#%i", id);
}

std::unordered_map<std::string, opcode> resolver::opcode_map
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
	{ "set_anim_field_variable_field", opcode::OP_SetAnimFieldVariableField },
	{ "set_self_field_variable_field", opcode::OP_SetSelfFieldVariableField },
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

std::unordered_map<std::string, std::uint16_t> resolver::builtin_function_map
{
	{ "isDefined", 45 },
	{ "setDvar", 50 },
	{ "setDynamicDvar", 51 },
	{ "setDvarIfUninitialized", 52 },
	{ "setDvar", 53 },
	{ "setDvarIfUninitialized", 54 },
	{ "getDvar", 55 },

	{ "isSubStr", 275 },
	{ "isEndStr", 276 },
	{ "getSubStr", 277 },
	{ "toLower", 278 },
	{ "strTok", 279 },
	{ "strICmp", 280 },

	{ "loadfx", 323 },
	{ "exitLevel", 352 },

	{ "getEntArray", 393 },

	{ "spawnstruct", 396 },

	
	{ "getnextarraykey", 422 },
	{ "getfirstarraykey", 449 },
};

std::unordered_map<std::string, std::uint16_t> resolver::builtin_method_map
{
	{ "delete", 32937 },
};

std::unordered_map<std::string, std::uint16_t> resolver::file_map
{
	{ "codescripts\\character", 911 },
	{ "codescripts\\delete", 912 },
	{ "codescripts\\struct", 913 },
	
	{ "common_scripts\\_createfx", 916 },
	{ "common_scripts\\_createfxmenu", 917 },

	{ "common_scripts\\_destructible", 919 },
	{ "common_scripts\\_dynamic_world", 920 },
	{ "common_scripts\\_elevator", 921 },

	{ "common_scripts\\_fx", 923 },

	{ "common_scripts\\utility", 927 },


	{ "maps\\createart\\mp_zebra_art", 1265 },
	{ "maps\\mp\\_compass", 1357 },
	{ "maps\\mp\\_load", 1373 },

	{ "maps\\mp\\mp_zebra_fx", 1416 },
	{ "maps\\mp\\mp_zebra_precache", 1417 },

	{ "maps\\mp\\gametypes\\_callbacksetup", 1467 },
	{ "maps\\mp\\gametypes\\_damage", 1470 },
	{ "maps\\mp\\gametypes\\_gamelogic", 1476 },
	{ "maps\\mp\\gametypes\\_hostmigration", 1486 },

	{ "maps\\mp\\gametypes\\_playerlogic", 1500 },
	{ "maps\\mp\\gametypes\\_rank", 1501 },
	{ "maps\\mp\\gametypes\\_serversettings", 1502 },

	{ "maps\\mp\\gametypes\\_teams", 1508 },
};

std::unordered_map <std::string, std::uint16_t> resolver::token_map
{
	{ "_effect", 1644 },
	{ "CreateStruct", 8482 },
	{ "init", 17631 },
	{ "main", 20445 },
	{ "InitStructs", 18005 },

	{ "setupMiniMap", 29184 },

	{ "struct", 31988 },

	{ "CodeCallback_StartGameType", 7654 },
	{ "CodeCallback_PlayerConnect", 7648 },
	{ "CodeCallback_PlayerDisconnect", 7650 },
	{ "CodeCallback_PlayerDamage", 7649 },
	{ "CodeCallback_PlayerKilled", 7651 },
	{ "CodeCallback_VehicleDamage", 7655 },
	{ "CodeCallback_CodeEndGame", 7645 },
	{ "CodeCallback_PlayerLastStand", 7652 },
	{ "CodeCallback_PlayerMigrated", 7653 },
	{ "CodeCallback_HostMigration", 7646 },
	{ "SetupDamageFlags", 29170 },
	{ "SetupCallbacks", 29168 },
	{ "SetDefaultCallbacks", 28693 },
	{ "AbortLevel", 1983 },
	{ "callbackVoid", 6492 },
	{ "gametypestarted", 14087 },
	{ "callbackStartGameType", 6491 },
	{ "callbackPlayerConnect", 6484 },
	{ "callbackPlayerDisconnect", 6486 },
	{ "callbackPlayerDamage", 6485 },
	{ "callbackPlayerKilled", 6487 },
	{ "damageCallback", 8960 },
	{ "callbackCodeEndGame", 6482 },
	{ "callbackPlayerLastStand", 6488 },
	{ "callbackPlayerMigrated", 6489 },
	{ "callbackHostMigration", 6483 },
	{ "Callback_StartGameType", 6480 },
	{ "Callback_PlayerConnect", 6471 },
	{ "Callback_PlayerDisconnect", 6474 },
	{ "Callback_PlayerDamage", 6472 },
	{ "Callback_PlayerKilled", 6475 },
	{ "Callback_CodeEndGame", 6468 },
	{ "Callback_PlayerLastStand", 6476 },
	{ "Callback_PlayerMigrated", 6479 },
	{ "Callback_HostMigration", 6469 },
	{ "iDFLAGS_RADIUS", 17344 },
	{ "iDFLAGS_NO_ARMOR", 17338 },
	{ "iDFLAGS_NO_KNOCKBACK", 17339 },
	{ "iDFLAGS_PENETRATION", 17343 },
	{ "iDFLAGS_STUN", 17348 },
	{ "iDFLAGS_SHIELD_EXPLOSIVE_IMPACT", 17345 },
	{ "iDFLAGS_SHIELD_EXPLOSIVE_IMPACT_HUGE", 17346 },
	{ "iDFLAGS_SHIELD_EXPLOSIVE_SPLASH", 17347 },
	{ "iDFLAGS_NO_TEAM_PROTECTION", 17341 },
	{ "iDFLAGS_NO_PROTECTION", 17340 },
	{ "iDFLAGS_PASSTHRU", 17342 },
	
};

} // namespace IW6
