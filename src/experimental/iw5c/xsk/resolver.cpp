// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "iw5c.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4244)
#endif

namespace xsk::gsc::iw5c
{

std::unordered_map<std::uint8_t, std::string_view> opcode_map;
std::unordered_map<std::uint16_t, std::string_view> function_map;
std::unordered_map<std::uint16_t, std::string_view> method_map;
std::unordered_map<std::uint16_t, std::string_view> token_map;
std::unordered_map<std::string_view, std::uint8_t> opcode_map_rev;
std::unordered_map<std::string_view, std::uint16_t> function_map_rev;
std::unordered_map<std::string_view, std::uint16_t> method_map_rev;
std::unordered_map<std::string, std::uint16_t> token_map_rev;
std::unordered_map<std::string, std::vector<std::uint8_t>> files;
read_cb_type read_callback = nullptr;
std::set<std::string> string_map;

void resolver::init(read_cb_type callback)
{
    read_callback = callback;
}

void resolver::cleanup()
{
    files.clear();
}

auto resolver::opcode_id(const std::string& name) -> std::uint8_t
{
    const auto itr = opcode_map_rev.find(name);

    if (itr != opcode_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("couldn't resolve opcode id for name '%s'!", name.data()));
}

auto resolver::opcode_name(std::uint8_t id) -> std::string
{
    const auto itr = opcode_map.find(id);

    if (itr != opcode_map.end())
    {
        return std::string(itr->second);
    }

    throw error(utils::string::va("couldn't resolve opcode name for id '0x%hhX'!", id));
}

auto resolver::function_id(const std::string& name) -> std::uint16_t
{
    if (name.starts_with("_func_"))
    {
        return static_cast<std::uint16_t>(std::stoul(name.substr(6), nullptr, 16));
    }

    const auto itr = function_map_rev.find(name);

    if (itr != function_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("couldn't resolve builtin function id for name '%s'!", name.data()));
}

auto resolver::function_name(std::uint16_t id) -> std::string
{
    const auto itr = function_map.find(id);

    if (itr != function_map.end())
    {
        return std::string(itr->second);
    }

    return utils::string::va("_func_%04X", id);
}

auto resolver::method_id(const std::string& name) -> std::uint16_t
{
    if (name.starts_with("_meth_"))
    {
        return static_cast<std::uint16_t>(std::stoul(name.substr(6), nullptr, 16));
    }

    const auto itr = method_map_rev.find(name);

    if (itr != method_map_rev.end())
    {
        return itr->second;
    }

    throw error(utils::string::va("couldn't resolve builtin method id for name '%s'!", name.data()));
}

auto resolver::method_name(std::uint16_t id) -> std::string
{
    const auto itr = method_map.find(id);

    if (itr != method_map.end())
    {
        return std::string(itr->second);
    }

    return utils::string::va("_meth_%04X", id);
}

auto resolver::token_id(const std::string& name) -> std::uint16_t
{
    if (name.starts_with("_id_"))
    {
        return static_cast<std::uint16_t>(std::stoul(name.substr(4), nullptr, 16));
    }

    const auto itr = token_map_rev.find(name);

    if (itr != token_map_rev.end())
    {
        return itr->second;
    }

    return 0;
}

auto resolver::token_name(std::uint16_t id) -> std::string
{
    const auto itr = token_map.find(id);

    if (itr != token_map.end())
    {
        return std::string(itr->second);
    }

    return utils::string::va("_id_%04X", id);
}

auto resolver::find_function(const std::string& name) -> bool
{
    if (name.starts_with("_func_")) return true;

    const auto itr = function_map_rev.find(name);

    if (itr != function_map_rev.end())
    {
        return true;
    }

    return false;
}

auto resolver::find_method(const std::string& name) -> bool
{
    if (name.starts_with("_meth_")) return true;

    const auto itr = method_map_rev.find(name);

    if (itr != method_map_rev.end())
    {
        return true;
    }

    return false;
}

void resolver::add_function(const std::string& name, std::uint16_t id)
{
    const auto itr = function_map_rev.find(name);

    if (itr != function_map_rev.end())
    {
        throw error(utils::string::va("builtin function '%s' already defined.", name.data()));
    }

    const auto str = string_map.find(name);

    if (str != string_map.end())
    {
        function_map.insert({ id, *str });
        function_map_rev.insert({ *str, id });
    }
    else
    {
        auto ins = string_map.insert(name);

        if (ins.second)
        {
            function_map.insert({ id, *ins.first });
            function_map_rev.insert({ *ins.first, id });
        }
    }
}

void resolver::add_method(const std::string& name, std::uint16_t id)
{
    const auto itr = method_map_rev.find(name);

    if (itr != method_map_rev.end())
    {
        throw error(utils::string::va("builtin method '%s' already defined.", name.data()));
    }

    const auto str = string_map.find(name);

    if (str != string_map.end())
    {
        method_map.insert({ id, *str });
        method_map_rev.insert({ *str, id });
    }
    else
    {
        auto ins = string_map.insert(name);

        if (ins.second)
        {
            method_map.insert({ id, *ins.first });
            method_map_rev.insert({ *ins.first, id });
        }
    }
}

auto resolver::make_token(std::string_view str) -> std::string
{
    if (str.starts_with("_id_") || str.starts_with("_func_") || str.starts_with("_meth_"))
    {
        return std::string(str);
    }

    auto data = std::string(str.begin(), str.end());

    for (std::size_t i = 0; i < data.size(); i++)
    {
        data[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));
        if (data[i] == '\\') data[i] = '/';
    }

    return data;
}

auto resolver::file_data(const std::string& name) -> std::tuple<const std::string*, const char*, size_t>
{
    const auto itr = files.find(name);

    if (itr != files.end())
    {
        return { &itr->first ,reinterpret_cast<const char*>(itr->second.data()), itr->second.size() };
    }

    auto data = read_callback(name);

    const auto res = files.insert({ name, std::move(data)});

    if (res.second)
    {
        return { &res.first->first, reinterpret_cast<const char*>(res.first->second.data()), res.first->second.size() };
    }

    throw error("couldn't open gsc file '" + name + "'");
}

std::set<std::string_view> paths
{
    "aitype"sv,
    "animscripts"sv,
    "character"sv,
    "codescripts"sv,
    "common_scripts"sv,
    "maps"sv,
    "mptype"sv,
    "vehicle_scripts"sv,
    "xmodelalias"sv,
    "animscripts/civilian"sv,
    "animscripts/dog"sv,
    "animscripts/hummer_turret"sv,
    "animscripts/riotshield"sv,
    "animscripts/saw"sv,
    "animscripts/scripted"sv,
    "animscripts/technical"sv,
    "animscripts/traverse"sv,
    "maps/animated_models"sv,
    "maps/cinematic_setups"sv,
    "maps/createart"sv,
    "maps/createfx"sv,
    "maps/gametypes"sv,
    "maps/mp"sv,
    "maps/mp/gametypes"sv,
    "maps/mp/killstreaks"sv,
    "maps/mp/perks"sv,
};

auto resolver::fs_to_game_path(const std::filesystem::path& file) -> std::filesystem::path
{
    auto result = std::filesystem::path();
    auto root = false;

    for (auto& entry : file)
    {
        if (!root && paths.contains(entry.string()))
        {
            result = entry;
            root = true;
        }
        else if (paths.contains(result.string()))
        {
            result /= entry;
        }
    }

    return result.empty() ? file : result;
}

const std::array<std::pair<std::uint8_t, const char*>, 153> opcode_list
{{
    { 0x00, "OP_End" },
    { 0x01, "OP_Return" },
    { 0x02, "OP_GetUndefined" },
    { 0x03, "OP_GetZero" },
    { 0x04, "OP_GetByte" },
    { 0x05, "OP_GetAnimTree" },
    { 0x06, "OP_GetNegByte" },
    { 0x07, "OP_GetUnsignedShort" },
    { 0x08, "OP_GetNegUnsignedShort" },
    { 0x09, "OP_GetInteger" },
    { 0x0A, "OP_GetBuiltinFunction" },
    { 0x0B, "OP_GetBuiltinMethod" },
    { 0x0C, "OP_GetFloat" },
    { 0x0D, "OP_GetString" },
    { 0x0E, "OP_GetIString" },
    { 0x0F, "OP_GetVector" },
    { 0x10, "OP_GetLevelObject" },
    { 0x11, "OP_GetAnimObject" },
    { 0x12, "OP_GetSelf" },
    { 0x13, "OP_GetThisthread" },
    { 0x14, "OP_GetLevel" },
    { 0x15, "OP_GetGame" },
    { 0x16, "OP_GetAnim" },
    { 0x17, "OP_GetAnimation" },
    { 0x18, "OP_GetGameRef" },
    { 0x1A, "OP_GetLocalFunction" },
    { 0x19, "OP_GetFarFunction" },
    { 0x1B, "OP_CreateLocalVariable" },
    { 0x1C, "OP_RemoveLocalVariables" },
    { 0x1D, "OP_EvalLocalVariableCached0" },
    { 0x1E, "OP_EvalLocalVariableCached1" },
    { 0x1F, "OP_EvalLocalVariableCached2" },
    { 0x20, "OP_EvalLocalVariableCached3" },
    { 0x21, "OP_EvalLocalVariableCached4" },
    { 0x22, "OP_EvalLocalVariableCached5" },
    { 0x23, "OP_EvalLocalVariableCached" },
    { 0x24, "OP_EvalLocalArrayCached" },
    { 0x25, "OP_EvalArray" },
    { 0x26, "OP_EvalLocalArrayRefCached0" },
    { 0x27, "OP_EvalNewLocalArrayRefCached0" },
    { 0x28, "OP_EvalLocalArrayRefCached" },
    { 0x29, "OP_EvalArrayRef" },
    { 0x2A, "OP_ClearArray" },
    { 0x2B, "OP_EmptyArray" },
    { 0x2C, "OP_AddArray" },
    { 0x2D, "OP_GetSelfObject" },
    { 0x2E, "OP_EvalLevelFieldVariable" },
    { 0x2F, "OP_EvalAnimFieldVariable" },
    { 0x30, "OP_EvalSelfFieldVariable" },
    { 0x31, "OP_EvalFieldVariable" },
    { 0x32, "OP_EvalLevelFieldVariableRef" },
    { 0x33, "OP_EvalAnimFieldVariableRef" },
    { 0x34, "OP_EvalSelfFieldVariableRef" },
    { 0x35, "OP_EvalFieldVariableRef" },
    { 0x36, "OP_ClearFieldVariable" },
    { 0x37, "OP_SafeCreateVariableFieldCached" },
    { 0x38, "OP_SafeSetVariableFieldCached0" },
    { 0x39, "OP_SafeSetVariableFieldCached" },
    { 0x3A, "OP_SafeSetWaittillVariableFieldCached" },
    { 0x3B, "OP_clearparams" },
    { 0x3C, "OP_checkclearparams" },
    { 0x3D, "OP_EvalLocalVariableRefCached0" },
    { 0x3E, "OP_EvalNewLocalVariableRefCached0" },
    { 0x3F, "OP_EvalLocalVariableRefCached" },
    { 0x40, "OP_SetLevelFieldVariableField" },
    { 0x41, "OP_SetVariableField" },
    { 0x42, "OP_ClearVariableField" },
    { 0x43, "OP_SetAnimFieldVariableField" },
    { 0x44, "OP_SetSelfFieldVariableField" },
    { 0x45, "OP_SetLocalVariableFieldCached0" },
    { 0x46, "OP_SetNewLocalVariableFieldCached0" },
    { 0x47, "OP_SetLocalVariableFieldCached" },
    { 0x48, "OP_ClearLocalVariableFieldCached" },
    { 0x49, "OP_ClearLocalVariableFieldCached0" },
    { 0x4A, "OP_CallBuiltin0" },
    { 0x4B, "OP_CallBuiltin1" },
    { 0x4C, "OP_CallBuiltin2" },
    { 0x4D, "OP_CallBuiltin3" },
    { 0x4E, "OP_CallBuiltin4" },
    { 0x4F, "OP_CallBuiltin5" },
    { 0x50, "OP_CallBuiltin" },
    { 0x51, "OP_CallBuiltinMethod0" },
    { 0x52, "OP_CallBuiltinMethod1" },
    { 0x53, "OP_CallBuiltinMethod2" },
    { 0x54, "OP_CallBuiltinMethod3" },
    { 0x55, "OP_CallBuiltinMethod4" },
    { 0x56, "OP_CallBuiltinMethod5" },
    { 0x57, "OP_CallBuiltinMethod" },
    { 0x58, "OP_wait" },
    { 0x59, "OP_waittillFrameEnd" },
    { 0x5A, "OP_PreScriptCall" },
    { 0x5B, "OP_ScriptLocalFunctionCall2" },
    { 0x5C, "OP_ScriptLocalFunctionCall" },
    { 0x5D, "OP_ScriptLocalMethodCall" },
    { 0x5E, "OP_ScriptLocalThreadCall" },
    { 0x5F, "OP_ScriptLocalChildThreadCall" },
    { 0x60, "OP_ScriptLocalMethodThreadCall" },
    { 0x61, "OP_ScriptLocalMethodChildThreadCall" },
    { 0x62, "OP_ScriptFarFunctionCall2" },
    { 0x63, "OP_ScriptFarFunctionCall" },
    { 0x64, "OP_ScriptFarMethodCall" },
    { 0x65, "OP_ScriptFarThreadCall" },
    { 0x66, "OP_ScriptFarChildThreadCall" },
    { 0x67, "OP_ScriptFarMethodThreadCall" },
    { 0x68, "OP_ScriptFarMethodChildThreadCall" },
    { 0x69, "OP_ScriptFunctionCallPointer" },
    { 0x6A, "OP_ScriptMethodCallPointer" },
    { 0x6B, "OP_ScriptThreadCallPointer" },
    { 0x6C, "OP_ScriptChildThreadCallPointer" },
    { 0x6D, "OP_ScriptMethodThreadCallPointer" },
    { 0x6E, "OP_ScriptMethodChildThreadCallPointer" },
    { 0x6F, "OP_CallBuiltinPointer" },
    { 0x70, "OP_CallBuiltinMethodPointer" },
    { 0x71, "OP_DecTop" },
    { 0x72, "OP_CastFieldObject" },
    { 0x73, "OP_EvalLocalVariableObjectCached" },
    { 0x74, "OP_CastBool" },
    { 0x75, "OP_BoolNot" },
    { 0x76, "OP_BoolComplement" },
    { 0x77, "OP_JumpOnFalse" },
    { 0x78, "OP_JumpOnTrue" },
    { 0x79, "OP_JumpOnFalseExpr" },
    { 0x7A, "OP_JumpOnTrueExpr" },
    { 0x7B, "OP_jump" },
    { 0x7C, "OP_jumpback" },
    { 0x7D, "OP_inc" },
    { 0x7E, "OP_dec" },
    { 0x7F, "OP_bit_or" },
    { 0x80, "OP_bit_ex_or" },
    { 0x81, "OP_bit_and" },
    { 0x82, "OP_equality" },
    { 0x83, "OP_inequality" },
    { 0x84, "OP_less" },
    { 0x85, "OP_greater" },
    { 0x86, "OP_less_equal" },
    { 0x87, "OP_greater_equal" },
    { 0x88, "OP_shift_left" },
    { 0x89, "OP_shift_right" },
    { 0x8A, "OP_plus" },
    { 0x8B, "OP_minus" },
    { 0x8C, "OP_multiply" },
    { 0x8D, "OP_divide" },
    { 0x8E, "OP_mod" },
    { 0x8F, "OP_size" },
    { 0x90, "OP_waittillmatch" },
    { 0x91, "OP_waittillmatch2" },
    { 0x92, "OP_waittill" },
    { 0x93, "OP_notify" },
    { 0x94, "OP_endon" },
    { 0x95, "OP_voidCodepos" },
    { 0x96, "OP_switch" },
    { 0x97, "OP_endswitch" },
    { 0x98, "OP_vector" },
}};

const std::array<std::pair<std::uint16_t, const char*>, 452> function_list
{{
    { 0x001, "createprintchannel" },
    { 0x002, "setprintchannel" },
    { 0x003, "print" },
    { 0x004, "println" },
    { 0x005, "print3d" },
    { 0x006, "line" },
    { 0x007, "precacheturret" },
    { 0x008, "getweaponarray" },
    { 0x009, "spawnturret" },
    { 0x00A, "canspawnturret" },
    { 0x00B, "assert" },
    { 0x00C, "assertex" },
    { 0x00D, "assertmsg" },
    { 0x00E, "isdefined" },
    { 0x00F, "isstring" },
    { 0x010, "setdvar" },
    { 0x011, "setdynamicdvar" },
    { 0x012, "setdvarifuninitialized" },
    { 0x013, "setdevdvar" },
    { 0x014, "setdevdvarifuninitialized" },
    { 0x015, "getdvar" },
    { 0x016, "getdvarint" },
    { 0x017, "getdvarfloat" },
    { 0x018, "getdvarvector" },
    { 0x019, "gettime" },
    { 0x01A, "getentbynum" },
    { 0x01B, "getweaponmodel" },
    { 0x01C, "getweaponhidetags" },
    { 0x01D, "getanimlength" },
    { 0x01E, "animhasnotetrack" },
    { 0x01F, "getnotetracktimes" },
    { 0x020, "spawn" },
    { 0x021, "spawnloopsound" },
    { 0x022, "spawnloopingsound" },
    { 0x023, "bullettrace" },
    { 0x024, "bullettracepassed" },
    { 0x025, "sighttracepassed" },
    { 0x026, "physicstrace" },
    { 0x027, "playerphysicstrace" },
    { 0x028, "getgroundposition" },
    { 0x029, "getmovedelta" },
    { 0x02A, "getangledelta" },
    { 0x02B, "getnorthyaw" },
    { 0x02C, "setnorthyaw" },
    { 0x02D, "setslowmotion" },
    { 0x02E, "randomint" },
    { 0x02F, "randomfloat" },
    { 0x030, "randomintrange" },
    { 0x031, "randomfloatrange" },
    { 0x032, "sin" },
    { 0x033, "cos" },
    { 0x034, "tan" },
    { 0x035, "asin" },
    { 0x036, "acos" },
    { 0x037, "atan" },
    { 0x038, "int" },
    { 0x039, "float" },
    { 0x03A, "abs" },
    { 0x03B, "min" },
    { 0x03C, "max" },
    { 0x03D, "floor" },
    { 0x03E, "ceil" },
    { 0x03F, "exp" },
    { 0x040, "log" },
    { 0x041, "sqrt" },
    { 0x042, "squared" },
    { 0x043, "clamp" },
    { 0x044, "angleclamp" },
    { 0x045, "angleclamp180" },
    { 0x046, "vectorfromlinetopoint" },
    { 0x047, "pointonsegmentnearesttopoint" },
    { 0x048, "distance" },
    { 0x049, "distance2d" },
    { 0x04A, "distancesquared" },
    { 0x04B, "length" },
    { 0x04C, "lengthsquared" },
    { 0x04D, "closer" },
    { 0x04E, "vectordot" },
    { 0x04F, "vectornormalize" },
    { 0x050, "vectortoangles" },
    { 0x051, "vectortoyaw" },
    { 0x052, "vectorlerp" },
    { 0x053, "anglestoup" },
    { 0x054, "anglestoright" },
    { 0x055, "anglestoforward" },
    { 0x056, "combineangles" },
    { 0x057, "transformmove" },
    { 0x058, "issubstr" },
    { 0x059, "isendstr" },
    { 0x05A, "getsubstr" },
    { 0x05B, "tolower" },
    { 0x05C, "strtok" },
    { 0x05D, "stricmp" },
    { 0x05E, "ambientplay" },
    { 0x05F, "ambientstop" },
    { 0x060, "precachemodel" },
    { 0x061, "precacheshellshock" },
    { 0x062, "precacheitem" },
    { 0x063, "precacheshader" },
    { 0x064, "precachestring" },
    { 0x065, "precachemenu" },
    { 0x066, "precacherumble" },
    { 0x067, "precachelocationselector" },
    { 0x068, "precacheleaderboards" },
    { 0x069, "loadfx" },
    { 0x06A, "playfx" },
    { 0x06B, "playfxontag" },
    { 0x06C, "stopfxontag" },
    { 0x06D, "playloopedfx" },
    { 0x06E, "spawnfx" },
    { 0x06F, "triggerfx" },
    { 0x070, "playfxontagforclients" },
    { 0x071, "physicsexplosionsphere" },
    { 0x072, "physicsexplosioncylinder" },
    { 0x073, "physicsjolt" },
    { 0x074, "physicsjitter" },
    { 0x075, "setexpfog" },
    { 0x076, "isexplosivedamagemod" },
    { 0x077, "radiusdamage" },
    { 0x078, "setplayerignoreradiusdamage" },
    { 0x079, "glassradiusdamage" },
    { 0x07A, "earthquake" },
    { 0x07B, "getnumparts" },
    { 0x07C, "getpartname" },
    { 0x07D, "weaponfiretime" },
    { 0x07E, "weaponclipsize" },
    { 0x07F, "weaponisauto" },
    { 0x080, "weaponissemiauto" },
    { 0x081, "weaponisboltaction" },
    { 0x082, "weaponinheritsperks" },
    { 0x083, "weaponburstcount" },
    { 0x084, "weapontype" },
    { 0x085, "weaponclass" },
    { 0x086, "weaponinventorytype" },
    { 0x087, "weaponstartammo" },
    { 0x088, "weaponmaxammo" },
    { 0x089, "weaponaltweaponname" },
    { 0x08A, "isweaponcliponly" },
    { 0x08B, "isweapondetonationtimed" },
    { 0x08C, "weaponhasthermalscope" },
    { 0x08D, "getvehiclenode" },
    { 0x08E, "getvehiclenodearray" },
    { 0x08F, "getallvehiclenodes" },
    { 0x090, "getnumvehicles" },
    { 0x091, "precachevehicle" },
    { 0x092, "spawnvehicle" },
    { 0x093, "vehicle_getarray" },
    { 0x094, "vehicle_getspawnerarray" },
    { 0x095, "playrumbleonposition" },
    { 0x096, "playrumblelooponposition" },
    { 0x097, "stopallrumbles" },
    { 0x098, "soundexists" },
    { 0x099, "openfile" },
    { 0x09A, "closefile" },
    { 0x09B, "fprintln" },
    { 0x09C, "fprintfields" },
    { 0x09D, "freadln" },
    { 0x09E, "fgetarg" },
    { 0x09F, "setminimap" },
    { 0x0A0, "setthermalbodymaterial" },
    { 0x0A1, "getarraykeys" },
    { 0x0A2, "getfirstarraykey" },
    { 0x0A3, "getnextarraykey" },
    { 0x0A4, "sortbydistance" },
    { 0x0A5, "tablelookup" },
    { 0x0A6, "tablelookupbyrow" },
    { 0x0A7, "tablelookupistring" },
    { 0x0A8, "tablelookupistringbyrow" },
    { 0x0A9, "tablelookuprownum" },
    { 0x0AA, "getmissileowner" },
    { 0x0AB, "magicbullet" },
    { 0x0AC, "getweaponflashtagname" },
    { 0x0AD, "averagepoint" },
    { 0x0AE, "averagenormal" },
    { 0x0AF, "getglass" },
    { 0x0B0, "getglassarray" },
    { 0x0B1, "getglassorigin" },
    { 0x0B2, "isglassdestroyed" },
    { 0x0B3, "destroyglass" },
    { 0x0B4, "deleteglass" },
    { 0x0B5, "getentchannelscount" },
    { 0x0B6, "getentchannelname" },
    { 0x0B7, "objective_add" },
    { 0x0B8, "objective_delete" },
    { 0x0B9, "objective_state" },
    { 0x0BA, "objective_icon" },
    { 0x0BB, "objective_position" },
    { 0x0BC, "objective_current" },
    { 0x0BD, "objective_onentity" },
    { 0x0BE, "objective_team" },
    { 0x0BF, "objective_player" },
    { 0x0C0, "objective_playerteam" },
    { 0x0C1, "objective_playerenemyteam" },
    { 0x0C2, "iprintln" },
    { 0x0C3, "iprintlnbold" },
    { 0x0C4, "logstring" },
    { 0x0C5, "getent" },
    { 0x0C6, "getentarray" },
    { 0x0C7, "spawnplane" },
    { 0x0C8, "spawnstruct" },
    { 0x0C9, "spawnhelicopter" },
    { 0x0CA, "isalive" },
    { 0x0CB, "isspawner" },
    { 0x0CC, "missile_createattractorent" },
    { 0x0CD, "missile_createattractororigin" },
    { 0x0CE, "missile_createrepulsorent" },
    { 0x0CF, "missile_createrepulsororigin" },
    { 0x0D0, "missile_deleteattractor" },
    { 0x0D1, "playsoundatpos" },
    { 0x0D2, "newhudelem" },
    { 0x0D3, "newclienthudelem" },
    { 0x0D4, "newteamhudelem" },
    { 0x0D5, "resettimeout" },
    { 0x0D6, "precachefxteamthermal" },
    { 0x0D7, "isplayer" },
    { 0x0D8, "isplayernumber" },
    { 0x0D9, "setwinningplayer" },
    { 0x0DA, "setwinningteam" },
    { 0x0DB, "announcement" },
    { 0x0DC, "clientannouncement" },
    { 0x0DD, "getteamscore" },
    { 0x0DE, "setteamscore" },
    { 0x0DF, "setclientnamemode" },
    { 0x0E0, "updateclientnames" },
    { 0x0E1, "getteamplayersalive" },
    { 0x0E2, "logprint" },
    { 0x0E3, "worldentnumber" },
    { 0x0E4, "obituary" },
    { 0x0E5, "positionwouldtelefrag" },
    { 0x0E6, "canspawn" },
    { 0x0E7, "getstarttime" },
    { 0x0E8, "precachestatusicon" },
    { 0x0E9, "precacheheadicon" },
    { 0x0EA, "precacheminimapicon" },
    { 0x0EB, "precachempanim" },
    { 0x0EC, "map_restart" },
    { 0x0ED, "exitlevel" },
    { 0x0EE, "addtestclient" },
    { 0x0EF, "makedvarserverinfo" },
    { 0x0F0, "setarchive" },
    { 0x0F1, "allclientsprint" },
    { 0x0F2, "clientprint" },
    { 0x0F3, "mapexists" },
    { 0x0F4, "isvalidgametype" },
    { 0x0F5, "matchend" },
    { 0x0F6, "setplayerteamrank" },
    { 0x0F7, "endparty" },
    { 0x0F8, "setteamradar" },
    { 0x0F9, "getteamradar" },
    { 0x0FA, "setteamradarstrength" },
    { 0x0FB, "getteamradarstrength" },
    { 0x0FC, "getuavstrengthmin" },
    { 0x0FD, "getuavstrengthmax" },
    { 0x0FE, "getuavstrengthlevelneutral" },
    { 0x0FF, "getuavstrengthlevelshowenemyfastsweep" },
    { 0x100, "getuavstrengthlevelshowenemydirectional" },
    { 0x101, "blockteamradar" },
    { 0x102, "unblockteamradar" },
    { 0x103, "isteamradarblocked" },
    { 0x104, "getassignedteam" },
    { 0x105, "setmatchdata" },
    { 0x106, "getmatchdata" },
    { 0x107, "sendmatchdata" },
    { 0x108, "clearmatchdata" },
    { 0x109, "setmatchdatadef" },
    { 0x10A, "setmatchclientip" },
    { 0x10B, "setmatchdataid" },
    { 0x10C, "setclientmatchdata" },
    { 0x10D, "getclientmatchdata" },
    { 0x10E, "setclientmatchdatadef" },
    { 0x10F, "sendclientmatchdata" },
    { 0x110, "getbuildversion" },
    { 0x111, "getbuildnumber" },
    { 0x112, "getsystemtime" },
    { 0x113, "getmatchrulesdata" },
    { 0x114, "isusingmatchrulesdata" },
    { 0x115, "kick" },
    { 0x116, "issplitscreen" },
    { 0x117, "setmapcenter" },
    { 0x118, "setgameendtime" },
    { 0x119, "visionsetnaked" },
    { 0x11A, "visionsetnight" },
    { 0x11B, "visionsetmissilecam" },
    { 0x11C, "visionsetthermal" },
    { 0x11D, "visionsetpain" },
    { 0x11E, "endlobby" },
    { 0x11F, "setac130ambience" },
    { 0x120, "getmapcustom" },
    { 0x121, "updateskill" },
    { 0x122, "spawnsighttrace" },
    { 0x123, "incrementcounter" },
    { 0x124, "getcountertotal" },
    { 0x125, "getlevelticks" },
    { 0x126, "perlinnoise2d" },
    { 0x127, "calcrockingangles" },
    { 0x128, "sethudlighting" },
    { 0x129, "reconevent" },
    { 0x12A, "reconspatialevent" },
    { 0x12B, "setsunflareposition" },
    { 0x12C, "createthreatbiasgroup" },
    { 0x12D, "threatbiasgroupexists" },
    { 0x12E, "getthreatbias" },
    { 0x12F, "setthreatbias" },
    { 0x130, "setthreatbiasagainstall" },
    { 0x131, "setignoremegroup" },
    { 0x132, "isenemyteam" },
    { 0x133, "objective_additionalentity" },
    { 0x134, "objective_state_nomessage" },
    { 0x135, "objective_string" },
    { 0x136, "objective_string_nomessage" },
    { 0x137, "objective_additionalposition" },
    { 0x138, "objective_current_nomessage" },
    { 0x139, "objective_additionalcurrent" },
    { 0x13A, "objective_ring" },
    { 0x13B, "objective_setpointertextoverride" },
    { 0x13C, "getnode" },
    { 0x13D, "getnodearray" },
    { 0x13E, "getallnodes" },
    { 0x13F, "getnodesinradius" },
    { 0x140, "getnodesinradiussorted" },
    { 0x141, "getclosestnodeinsight" },
    { 0x142, "getreflectionlocs" },
    { 0x143, "getreflectionreferencelocs" },
    { 0x144, "getvehicletracksegment" },
    { 0x145, "getvehicletracksegmentarray" },
    { 0x146, "getallvehicletracksegments" },
    { 0x147, "isarray" },
    { 0x148, "isai" },
    { 0x149, "issentient" },
    { 0x14A, "isgodmode" },
    { 0x14B, "getdebugdvar" },
    { 0x14C, "getdebugdvarint" },
    { 0x14D, "getdebugdvarfloat" },
    { 0x14E, "setsaveddvar" },
    { 0x14F, "getfreeaicount" },
    { 0x150, "getaicount" },
    { 0x151, "getaiarray" },
    { 0x152, "getaispeciesarray" },
    { 0x153, "getspawnerarray" },
    { 0x154, "getcorpsearray" },
    { 0x155, "getspawnerteamarray" },
    { 0x156, "getweaponclipmodel" },
    { 0x157, "getbrushmodelcenter" },
    { 0x158, "getkeybinding" },
    { 0x159, "getcommandfromkey" },
    { 0x15A, "getsticksconfig" },
    { 0x15B, "weaponfightdist" },
    { 0x15C, "weaponmaxdist" },
    { 0x15D, "isturretactive" },
    { 0x15E, "target_alloc" },
    { 0x15F, "target_flush" },
    { 0x160, "target_set" },
    { 0x161, "target_remove" },
    { 0x162, "target_setshader" },
    { 0x163, "target_setoffscreenshader" },
    { 0x164, "target_isinrect" },
    { 0x165, "target_isincircle" },
    { 0x166, "target_startreticlelockon" },
    { 0x167, "target_clearreticlelockon" },
    { 0x168, "target_getarray" },
    { 0x169, "target_istarget" },
    { 0x16A, "target_setattackmode" },
    { 0x16B, "target_setjavelinonly" },
    { 0x16C, "target_hidefromplayer" },
    { 0x16D, "target_showtoplayer" },
    { 0x16E, "target_setscaledrendermode" },
    { 0x16F, "target_drawcornersonly" },
    { 0x170, "target_drawsquare" },
    { 0x171, "target_drawsingle" },
    { 0x172, "target_setminsize" },
    { 0x173, "target_setmaxsize" },
    { 0x174, "target_setcolor" },
    { 0x175, "target_setdelay" },
    { 0x176, "getstartorigin" },
    { 0x177, "getstartangles" },
    { 0x178, "getcycleoriginoffset" },
    { 0x179, "magicgrenade" },
    { 0x17A, "magicgrenademanual" },
    { 0x17B, "setblur" },
    { 0x17C, "musicplay" },
    { 0x17D, "musicstop" },
    { 0x17E, "soundfade" },
    { 0x17F, "soundsettimescalefactor" },
    { 0x180, "soundresettimescale" },
    { 0x181, "setocclusionpreset" },
    { 0x182, "levelsoundfade" },
    { 0x183, "precachenightvisioncodeassets" },
    { 0x184, "precachedigitaldistortcodeassets" },
    { 0x185, "precacheminimapsentrycodeassets" },
    { 0x186, "savegame" },
    { 0x187, "issavesuccessful" },
    { 0x188, "issaverecentlyloaded" },
    { 0x189, "savegamenocommit" },
    { 0x18A, "commitsave" },
    { 0x18B, "commitwouldbevalid" },
    { 0x18C, "getfxvisibility" },
    { 0x18D, "setculldist" },
    { 0x18E, "getculldist" },
    { 0x18F, "sethalfresparticles" },
    { 0x190, "getmapsunlight" },
    { 0x191, "setsunlight" },
    { 0x192, "resetsunlight" },
    { 0x193, "getmapsundirection" },
    { 0x194, "getmapsunangles" },
    { 0x195, "setsundirection" },
    { 0x196, "lerpsundirection" },
    { 0x197, "lerpsunangles" },
    { 0x198, "resetsundirection" },
    { 0x199, "enableforcedsunshadows" },
    { 0x19A, "enableforcednosunshadows" },
    { 0x19B, "disableforcedsunshadows" },
    { 0x19C, "enableouterspacemodellighting" },
    { 0x19D, "disableouterspacemodellighting" },
    { 0x19E, "remapstage" },
    { 0x19F, "changelevel" },
    { 0x1A0, "missionsuccess" },
    { 0x1A1, "missionfailed" },
    { 0x1A2, "cinematic" },
    { 0x1A3, "cinematicingame" },
    { 0x1A4, "cinematicingamesync" },
    { 0x1A5, "cinematicingameloop" },
    { 0x1A6, "cinematicingameloopresident" },
    { 0x1A7, "iscinematicplaying" },
    { 0x1A8, "stopcinematicingame" },
    { 0x1A9, "pausecinematicingame" },
    { 0x1AA, "drawcompassfriendlies" },
    { 0x1AB, "bulletspread" },
    { 0x1AC, "bullettracer" },
    { 0x1AD, "badplace_delete" },
    { 0x1AE, "badplace_cylinder" },
    { 0x1AF, "badplace_arc" },
    { 0x1B0, "badplace_brush" },
    { 0x1B1, "clearallcorpses" },
    { 0x1B2, "setturretnode" },
    { 0x1B3, "unsetturretnode" },
    { 0x1B4, "setnodepriority" },
    { 0x1B5, "isnodeoccupied" },
    { 0x1B6, "setdebugorigin" },
    { 0x1B7, "setdebugangles" },
    { 0x1B8, "updategamerprofile" },
    { 0x1B9, "updategamerprofileall" },
    { 0x1BA, "clearlocalizedstrings" },
    { 0x1BB, "setphysicsgravitydir" },
    { 0x1BC, "gettimescale" },
    { 0x1BD, "settimescale" },
    { 0x1BE, "setslowmotionview" },
    { 0x1BF, "forcesharedammo" },
    { 0x1C0, "refreshhudcompass" },
    { 0x1C1, "refreshhudammocounter" },
    { 0x1C2, "notifyoncommand" },
    { 0x1C3, "gettimesincelastpaused" },
    { 0x1C4, "setlasermaterial" },
}};

const std::array<std::pair<std::uint16_t, const char*>, 781> method_list
{{
    { 0x8000, "attach" },
    { 0x8001, "attachshieldmodel" },
    { 0x8002, "detach" },
    { 0x8003, "detachshieldmodel" },
    { 0x8004, "moveshieldmodel" },
    { 0x8005, "detachall" },
    { 0x8006, "getattachsize" },
    { 0x8007, "getattachmodelname" },
    { 0x8008, "getattachtagname" },
    { 0x8009, "getattachignorecollision" },
    { 0x800A, "hidepart" },
    { 0x800B, "hidepart_allinstances" },
    { 0x800C, "hideallparts" },
    { 0x800D, "showpart" },
    { 0x800E, "showallparts" },
    { 0x800F, "linkto" },
    { 0x8010, "linktoblendtotag" },
    { 0x8011, "unlink" },
    { 0x8012, "islinked" },
    { 0x8013, "enablelinkto" },
    { 0x8014, "playerlinkto" },
    { 0x8015, "playerlinktodelta" },
    { 0x8016, "playerlinkweaponviewtodelta" },
    { 0x8017, "playerlinktoabsolute" },
    { 0x8018, "playerlinktoblend" },
    { 0x8019, "playerlinkedoffsetenable" },
    { 0x801A, "playerlinkedoffsetdisable" },
    { 0x801B, "playerlinkedsetviewznear" },
    { 0x801C, "playerlinkedsetusebaseangleforviewclamp" },
    { 0x801D, "lerpviewangleclamp" },
    { 0x801E, "setviewangleresistance" },
    { 0x801F, "geteye" },
    { 0x8020, "istouching" },
    { 0x8021, "stoploopsound" },
    { 0x8022, "stopsounds" },
    { 0x8023, "playrumbleonentity" },
    { 0x8024, "playrumblelooponentity" },
    { 0x8025, "stoprumble" },
    { 0x8026, "delete" },
    { 0x8027, "setmodel" },
    { 0x8028, "laseron" },
    { 0x8029, "laseroff" },
    { 0x802A, "laseraltviewon" },
    { 0x802B, "laseraltviewoff" },
    { 0x802C, "thermalvisionon" },
    { 0x802D, "thermalvisionoff" },
    { 0x802E, "thermalvisionfofoverlayon" },
    { 0x802F, "thermalvisionfofoverlayoff" },
    { 0x8030, "autospotoverlayon" },
    { 0x8031, "autospotoverlayoff" },
    { 0x8032, "setcontents" },
    { 0x8033, "makeusable" },
    { 0x8034, "makeunusable" },
    { 0x8035, "setcursorhint" },
    { 0x8036, "sethintstring" },
    { 0x8037, "forceusehinton" },
    { 0x8038, "forceusehintoff" },
    { 0x8039, "makesoft" },
    { 0x803A, "makehard" },
    { 0x803B, "willneverchange" },
    { 0x803C, "startfiring" },
    { 0x803D, "stopfiring" },
    { 0x803E, "isfiringturret" },
    { 0x803F, "startbarrelspin" },
    { 0x8040, "stopbarrelspin" },
    { 0x8041, "getbarrelspinrate" },
    { 0x8042, "remotecontrolturret" },
    { 0x8043, "remotecontrolturretoff" },
    { 0x8044, "shootturret" },
    { 0x8045, "getturretowner" },
    { 0x8046, "setsentryowner" },
    { 0x8047, "setsentrycarrier" },
    { 0x8048, "setturretminimapvisible" },
    { 0x8049, "settargetentity" },
    { 0x804A, "snaptotargetentity" },
    { 0x804B, "cleartargetentity" },
    { 0x804C, "getturrettarget" },
    { 0x804D, "setplayerspread" },
    { 0x804E, "setaispread" },
    { 0x804F, "setsuppressiontime" },
    { 0x8050, "setconvergencetime" },
    { 0x8051, "setconvergenceheightpercent" },
    { 0x8052, "setturretteam" },
    { 0x8053, "maketurretsolid" },
    { 0x8054, "maketurretoperable" },
    { 0x8055, "maketurretinoperable" },
    { 0x8056, "setturretaccuracy" },
    { 0x8057, "setrightarc" },
    { 0x8058, "setleftarc" },
    { 0x8059, "settoparc" },
    { 0x805A, "setbottomarc" },
    { 0x805B, "setautorotationdelay" },
    { 0x805C, "setdefaultdroppitch" },
    { 0x805D, "restoredefaultdroppitch" },
    { 0x805E, "turretfiredisable" },
    { 0x805F, "turretfireenable" },
    { 0x8060, "setturretmodechangewait" },
    { 0x8061, "usetriggerrequirelookat" },
    { 0x8062, "getstance" },
    { 0x8063, "setstance" },
    { 0x8064, "itemweaponsetammo" },
    { 0x8065, "getammocount" },
    { 0x8066, "gettagorigin" },
    { 0x8067, "gettagangles" },
    { 0x8068, "shellshock" },
    { 0x8069, "stunplayer" },
    { 0x806A, "stopshellshock" },
    { 0x806B, "fadeoutshellshock" },
    { 0x806C, "setdepthoffield" },
    { 0x806D, "setviewmodeldepthoffield" },
    { 0x806E, "setmotionblurmovescale" },
    { 0x806F, "setmotionblurturnscale" },
    { 0x8070, "setmotionblurzoomscale" },
    { 0x8071, "viewkick" },
    { 0x8072, "localtoworldcoords" },
    { 0x8073, "getentitynumber" },
    { 0x8074, "getentityvelocity" },
    { 0x8075, "enablegrenadetouchdamage" },
    { 0x8076, "disablegrenadetouchdamage" },
    { 0x8077, "enableaimassist" },
    { 0x8078, "disableaimassist" },
    { 0x8079, "radiusdamage" },
    { 0x807A, "detonate" },
    { 0x807B, "damageconetrace" },
    { 0x807C, "sightconetrace" },
    { 0x807D, "missile_settargetent" },
    { 0x807E, "missile_settargetpos" },
    { 0x807F, "missile_cleartarget" },
    { 0x8080, "missile_setflightmodedirect" },
    { 0x8081, "missile_setflightmodetop" },
    { 0x8082, "getlightintensity" },
    { 0x8083, "setlightintensity" },
    { 0x8084, "isragdoll" },
    { 0x8085, "setmovespeedscale" },
    { 0x8086, "cameralinkto" },
    { 0x8087, "cameraunlink" },
    { 0x8088, "controlslinkto" },
    { 0x8089, "controlsunlink" },
    { 0x808A, "makevehiclesolidcapsule" },
    { 0x808B, "makevehiclesolidsphere" },
    { 0x808C, "makevehiclesolid" },
    { 0x808D, "remotecontrolvehicle" },
    { 0x808E, "remotecontrolvehicleoff" },
    { 0x808F, "isfiringvehicleturret" },
    { 0x8090, "drivevehicleandcontrolturret" },
    { 0x8091, "drivevehicleandcontrolturretoff" },
    { 0x8092, "getplayersetting" },
    { 0x8093, "getlocalplayerprofiledata" },
    { 0x8094, "setlocalplayerprofiledata" },
    { 0x8095, "remotecamerasoundscapeon" },
    { 0x8096, "remotecamerasoundscapeoff" },
    { 0x8097, "radarjamon" },
    { 0x8098, "radarjamoff" },
    { 0x8099, "setmotiontrackervisible" },
    { 0x809A, "getmotiontrackervisible" },
    { 0x809B, "worldpointinreticle_circle" },
    { 0x809C, "getpointinbounds" },
    { 0x809D, "transfermarkstonewscriptmodel" },
    { 0x809E, "setwatersheeting" },
    { 0x809F, "setweaponhudiconoverride" },
    { 0x80A0, "getweaponhudiconoverride" },
    { 0x80A1, "setempjammed" },
    { 0x80A2, "playersetexpfog" },
    { 0x80A3, "isitemunlocked" },
    { 0x80A4, "getplayerdata" },
    { 0x80A5, "setplayerdata" },
    { 0x80A6, "trackerupdate" },
    { 0x80A7, "pingplayer" },
    { 0x80A8, "buttonpressed" },
    { 0x80A9, "sayall" },
    { 0x80AA, "sayteam" },
    { 0x80AB, "showscoreboard" },
    { 0x80AC, "setspawnweapon" },
    { 0x80AD, "dropitem" },
    { 0x80AE, "dropscavengerbag" },
    { 0x80AF, "finishplayerdamage" },
    { 0x80B0, "suicide" },
    { 0x80B1, "closeingamemenu" },
    { 0x80B2, "iprintln" },
    { 0x80B3, "iprintlnbold" },
    { 0x80B4, "spawn" },
    { 0x80B5, "setentertime" },
    { 0x80B6, "cloneplayer" },
    { 0x80B7, "istalking" },
    { 0x80B8, "allowspectateteam" },
    { 0x80B9, "getguid" },
    { 0x80BA, "getxuid" },
    { 0x80BB, "ishost" },
    { 0x80BC, "getspectatingplayer" },
    { 0x80BD, "predictstreampos" },
    { 0x80BE, "updatescores" },
    { 0x80BF, "updatedmscores" },
    { 0x80C0, "setrank" },
    { 0x80C1, "setcardtitle" },
    { 0x80C2, "setcardicon" },
    { 0x80C3, "setcardnameplate" },
    { 0x80C4, "setcarddisplayslot" },
    { 0x80C5, "kc_regweaponforfxremoval" },
    { 0x80C6, "laststandrevive" },
    { 0x80C7, "setspectatedefaults" },
    { 0x80C8, "getthirdpersoncrosshairoffset" },
    { 0x80C9, "disableweaponpickup" },
    { 0x80CA, "enableweaponpickup" },
    { 0x80CB, "issplitscreenplayer" },
    { 0x80CC, "issplitscreenplayerprimary" },
    { 0x80CD, "getviewmodel" },
    { 0x80CE, "fragbuttonpressed" },
    { 0x80CF, "secondaryoffhandbuttonpressed" },
    { 0x80D0, "getcurrentweaponclipammo" },
    { 0x80D1, "setvelocity" },
    { 0x80D2, "getplayerviewheight" },
    { 0x80D3, "getnormalizedmovement" },
    { 0x80D4, "getnormalizedcameramovement" },
    { 0x80D5, "giveweapon" },
    { 0x80D6, "takeweapon" },
    { 0x80D7, "takeallweapons" },
    { 0x80D8, "getcurrentweapon" },
    { 0x80D9, "getcurrentprimaryweapon" },
    { 0x80DA, "getcurrentoffhand" },
    { 0x80DB, "hasweapon" },
    { 0x80DC, "switchtoweapon" },
    { 0x80DD, "switchtoweaponimmediate" },
    { 0x80DE, "switchtooffhand" },
    { 0x80DF, "givestartammo" },
    { 0x80E0, "givemaxammo" },
    { 0x80E1, "getfractionstartammo" },
    { 0x80E2, "getfractionmaxammo" },
    { 0x80E3, "isdualwielding" },
    { 0x80E4, "isreloading" },
    { 0x80E5, "isswitchingweapon" },
    { 0x80E6, "setorigin" },
    { 0x80E7, "getvelocity" },
    { 0x80E8, "setplayerangles" },
    { 0x80E9, "getplayerangles" },
    { 0x80EA, "usebuttonpressed" },
    { 0x80EB, "attackbuttonpressed" },
    { 0x80EC, "adsbuttonpressed" },
    { 0x80ED, "meleebuttonpressed" },
    { 0x80EE, "playerads" },
    { 0x80EF, "isonground" },
    { 0x80F0, "isusingturret" },
    { 0x80F1, "setviewmodel" },
    { 0x80F2, "setoffhandprimaryclass" },
    { 0x80F3, "getoffhandprimaryclass" },
    { 0x80F4, "setoffhandsecondaryclass" },
    { 0x80F5, "getoffhandsecondaryclass" },
    { 0x80F6, "beginlocationselection" },
    { 0x80F7, "endlocationselection" },
    { 0x80F8, "disableweapons" },
    { 0x80F9, "enableweapons" },
    { 0x80FA, "disableoffhandweapons" },
    { 0x80FB, "enableoffhandweapons" },
    { 0x80FC, "disableweaponswitch" },
    { 0x80FD, "enableweaponswitch" },
    { 0x80FE, "openpopupmenu" },
    { 0x80FF, "openpopupmenunomouse" },
    { 0x8100, "closepopupmenu" },
    { 0x8101, "openmenu" },
    { 0x8102, "closemenu" },
    { 0x8103, "savematchrulestohistory" },
    { 0x8104, "freezecontrols" },
    { 0x8105, "disableusability" },
    { 0x8106, "enableusability" },
    { 0x8107, "setwhizbyspreads" },
    { 0x8108, "setwhizbyradii" },
    { 0x8109, "setreverb" },
    { 0x810A, "deactivatereverb" },
    { 0x810B, "setvolmod" },
    { 0x810C, "setchannelvolume" },
    { 0x810D, "setchannelvolumes" },
    { 0x810E, "deactivatechannelvolumes" },
    { 0x810F, "playlocalsound" },
    { 0x8110, "stoplocalsound" },
    { 0x8111, "setweaponammoclip" },
    { 0x8112, "setweaponammostock" },
    { 0x8113, "getweaponammoclip" },
    { 0x8114, "getweaponammostock" },
    { 0x8115, "anyammoforweaponmodes" },
    { 0x8116, "setclientdvar" },
    { 0x8117, "setclientdvars" },
    { 0x8118, "allowads" },
    { 0x8119, "allowjump" },
    { 0x811A, "allowsprint" },
    { 0x811B, "setspreadoverride" },
    { 0x811C, "resetspreadoverride" },
    { 0x811D, "setaimspreadmovementscale" },
    { 0x811E, "setactionslot" },
    { 0x811F, "setviewkickscale" },
    { 0x8120, "getviewkickscale" },
    { 0x8121, "getweaponslistall" },
    { 0x8122, "getweaponslistprimaries" },
    { 0x8123, "getweaponslistoffhands" },
    { 0x8124, "getweaponslistitems" },
    { 0x8125, "getweaponslistexclusives" },
    { 0x8126, "getweaponslist" },
    { 0x8127, "canplayerplacesentry" },
    { 0x8128, "canplayerplacetank" },
    { 0x8129, "visionsetnakedforplayer" },
    { 0x812A, "visionsetnightforplayer" },
    { 0x812B, "visionsetmissilecamforplayer" },
    { 0x812C, "visionsetthermalforplayer" },
    { 0x812D, "visionsetpainforplayer" },
    { 0x812E, "setblurforplayer" },
    { 0x812F, "getplayerweaponmodel" },
    { 0x8130, "getplayerknifemodel" },
    { 0x8131, "updateplayermodelwithweapons" },
    { 0x8132, "notifyonplayercommand" },
    { 0x8133, "canmantle" },
    { 0x8134, "forcemantle" },
    { 0x8135, "ismantling" },
    { 0x8136, "playfx" },
    { 0x8137, "player_recoilscaleon" },
    { 0x8138, "player_recoilscaleoff" },
    { 0x8139, "weaponlockstart" },
    { 0x813A, "weaponlockfinalize" },
    { 0x813B, "weaponlockfree" },
    { 0x813C, "weaponlocktargettooclose" },
    { 0x813D, "weaponlocknoclearance" },
    { 0x813E, "visionsyncwithplayer" },
    { 0x813F, "showhudsplash" },
    { 0x8140, "setperk" },
    { 0x8141, "hasperk" },
    { 0x8142, "clearperks" },
    { 0x8143, "unsetperk" },
    { 0x8144, "noclip" },
    { 0x8145, "ufo" },
    { 0x8146, "moveto" },
    { 0x8147, "movex" },
    { 0x8148, "movey" },
    { 0x8149, "movez" },
    { 0x814A, "movegravity" },
    { 0x814B, "moveslide" },
    { 0x814C, "stopmoveslide" },
    { 0x814D, "rotateto" },
    { 0x814E, "rotatepitch" },
    { 0x814F, "rotateyaw" },
    { 0x8150, "rotateroll" },
    { 0x8151, "addpitch" },
    { 0x8152, "addyaw" },
    { 0x8153, "addroll" },
    { 0x8154, "vibrate" },
    { 0x8155, "rotatevelocity" },
    { 0x8156, "solid" },
    { 0x8157, "notsolid" },
    { 0x8158, "setcandamage" },
    { 0x8159, "setcanradiusdamage" },
    { 0x815A, "physicslaunchclient" },
    { 0x815B, "physicslaunchserver" },
    { 0x815C, "physicslaunchserveritem" },
    { 0x815D, "clonebrushmodeltoscriptmodel" },
    { 0x815E, "scriptmodelplayanim" },
    { 0x815F, "scriptmodelclearanim" },
    { 0x8160, "vehicle_teleport" },
    { 0x8161, "attachpath" },
    { 0x8162, "getattachpos" },
    { 0x8163, "startpath" },
    { 0x8164, "setswitchnode" },
    { 0x8165, "setwaitspeed" },
    { 0x8166, "vehicle_finishdamage" },
    { 0x8167, "vehicle_setspeed" },
    { 0x8168, "vehicle_setspeedimmediate" },
    { 0x8169, "vehicle_rotateyaw" },
    { 0x816A, "vehicle_getspeed" },
    { 0x816B, "vehicle_getvelocity" },
    { 0x816C, "vehicle_getbodyvelocity" },
    { 0x816D, "vehicle_getsteering" },
    { 0x816E, "vehicle_getthrottle" },
    { 0x816F, "vehicle_turnengineoff" },
    { 0x8170, "vehicle_turnengineon" },
    { 0x8171, "getgoalspeedmph" },
    { 0x8172, "setacceleration" },
    { 0x8173, "setdeceleration" },
    { 0x8174, "resumespeed" },
    { 0x8175, "setyawspeed" },
    { 0x8176, "setyawspeedbyname" },
    { 0x8177, "setmaxpitchroll" },
    { 0x8178, "setairresistance" },
    { 0x8179, "setturningability" },
    { 0x817A, "setjitterparams" },
    { 0x817B, "sethoverparams" },
    { 0x817C, "joltbody" },
    { 0x817D, "freevehicle" },
    { 0x817E, "getwheelsurface" },
    { 0x817F, "getvehicleowner" },
    { 0x8180, "setvehiclelookattext" },
    { 0x8181, "setvehicleteam" },
    { 0x8182, "setneargoalnotifydist" },
    { 0x8183, "setvehgoalpos" },
    { 0x8184, "setgoalyaw" },
    { 0x8185, "cleargoalyaw" },
    { 0x8186, "settargetyaw" },
    { 0x8187, "cleartargetyaw" },
    { 0x8188, "vehicle_helisetai" },
    { 0x8189, "setturrettargetvec" },
    { 0x818A, "setturrettargetent" },
    { 0x818B, "clearturrettarget" },
    { 0x818C, "vehicle_canturrettargetpoint" },
    { 0x818D, "setlookatent" },
    { 0x818E, "clearlookatent" },
    { 0x818F, "setvehweapon" },
    { 0x8190, "fireweapon" },
    { 0x8191, "vehicleturretcontrolon" },
    { 0x8192, "vehicleturretcontroloff" },
    { 0x8193, "isturretready" },
    { 0x8194, "vehicledriveto" },
    { 0x8195, "vehicle_dospawn" },
    { 0x8196, "vehicle_isphysveh" },
    { 0x8197, "vehphys_crash" },
    { 0x8198, "vehphys_launch" },
    { 0x8199, "vehphys_disablecrashing" },
    { 0x819A, "vehphys_enablecrashing" },
    { 0x819B, "vehphys_setspeed" },
    { 0x819C, "vehphys_setconveyorbelt" },
    { 0x819D, "freehelicopter" },
    { 0x819E, "playerlinkedturretanglesenable" },
    { 0x819F, "playerlinkedturretanglesdisable" },
    { 0x81A0, "playersetstreamorigin" },
    { 0x81A1, "playerclearstreamorigin" },
    { 0x81A2, "nightvisionviewon" },
    { 0x81A3, "nightvisionviewoff" },
    { 0x81A4, "painvisionon" },
    { 0x81A5, "painvisionoff" },
    { 0x81A6, "getplayerintelisfound" },
    { 0x81A7, "setplayerintelfound" },
    { 0x81A8, "newpip" },
    { 0x81A9, "sethuddynlight" },
    { 0x81AA, "startscriptedanim" },
    { 0x81AB, "startcoverbehavior" },
    { 0x81AC, "startcoverarrival" },
    { 0x81AD, "starttraversearrival" },
    { 0x81AE, "checkcoverexitposwithpath" },
    { 0x81AF, "shoot" },
    { 0x81B0, "shootblank" },
    { 0x81B1, "melee" },
    { 0x81B2, "updateplayersightaccuracy" },
    { 0x81B3, "findshufflecovernode" },
    { 0x81B4, "findnearbycovernode" },
    { 0x81B5, "findcovernode" },
    { 0x81B6, "findbestcovernode" },
    { 0x81B7, "getcovernode" },
    { 0x81B8, "usecovernode" },
    { 0x81B9, "iscovervalidagainstenemy" },
    { 0x81BA, "reacquirestep" },
    { 0x81BB, "findreacquiredirectpath" },
    { 0x81BC, "trimpathtoattack" },
    { 0x81BD, "reacquiremove" },
    { 0x81BE, "findreacquireproximatepath" },
    { 0x81BF, "flagenemyunattackable" },
    { 0x81C0, "enterprone" },
    { 0x81C1, "exitprone" },
    { 0x81C2, "setproneanimnodes" },
    { 0x81C3, "updateprone" },
    { 0x81C4, "clearpitchorient" },
    { 0x81C5, "setlookatanimnodes" },
    { 0x81C6, "setlookat" },
    { 0x81C7, "setlookatentity" },
    { 0x81C8, "setlookatyawlimits" },
    { 0x81C9, "stoplookat" },
    { 0x81CA, "getmuzzlepos" },
    { 0x81CB, "getmuzzleangle" },
    { 0x81CC, "getmuzzlesideoffsetpos" },
    { 0x81CD, "getaimangle" },
    { 0x81CE, "canshoot" },
    { 0x81CF, "canshootenemy" },
    { 0x81D0, "cansee" },
    { 0x81D1, "seerecently" },
    { 0x81D2, "lastknowntime" },
    { 0x81D3, "lastknownpos" },
    { 0x81D4, "dropweapon" },
    { 0x81D5, "maymovetopoint" },
    { 0x81D6, "maymovefrompointtopoint" },
    { 0x81D7, "teleport" },
    { 0x81D8, "forceteleport" },
    { 0x81D9, "safeteleport" },
    { 0x81DA, "withinapproxpathdist" },
    { 0x81DB, "ispathdirect" },
    { 0x81DC, "allowedstances" },
    { 0x81DD, "isstanceallowed" },
    { 0x81DE, "issuppressionwaiting" },
    { 0x81DF, "issuppressed" },
    { 0x81E0, "ismovesuppressed" },
    { 0x81E1, "isgrenadepossafe" },
    { 0x81E2, "checkgrenadethrow" },
    { 0x81E3, "checkgrenadelaunch" },
    { 0x81E4, "checkgrenadelaunchpos" },
    { 0x81E5, "throwgrenade" },
    { 0x81E6, "pickupgrenade" },
    { 0x81E7, "useturret" },
    { 0x81E8, "stopuseturret" },
    { 0x81E9, "canuseturret" },
    { 0x81EA, "traversemode" },
    { 0x81EB, "animmode" },
    { 0x81EC, "orientmode" },
    { 0x81ED, "getmotionangle" },
    { 0x81EE, "shouldfacemotion" },
    { 0x81EF, "getanglestolikelyenemypath" },
    { 0x81F0, "setturretanim" },
    { 0x81F1, "getturret" },
    { 0x81F2, "getgroundenttype" },
    { 0x81F3, "animcustom" },
    { 0x81F4, "isinscriptedstate" },
    { 0x81F5, "canattackenemynode" },
    { 0x81F6, "getnegotiationstartnode" },
    { 0x81F7, "getnegotiationendnode" },
    { 0x81F8, "getdoorpathnode" },
    { 0x81F9, "comparenodedirtopathdir" },
    { 0x81FA, "checkprone" },
    { 0x81FB, "pushplayer" },
    { 0x81FC, "checkgrenadethrowpos" },
    { 0x81FD, "setgoalnode" },
    { 0x81FE, "setgoalpos" },
    { 0x81FF, "setgoalentity" },
    { 0x8200, "setgoalvolume" },
    { 0x8201, "setgoalvolumeauto" },
    { 0x8202, "getgoalvolume" },
    { 0x8203, "cleargoalvolume" },
    { 0x8204, "setfixednodesafevolume" },
    { 0x8205, "getfixednodesafevolume" },
    { 0x8206, "clearfixednodesafevolume" },
    { 0x8207, "isingoal" },
    { 0x8208, "setruntopos" },
    { 0x8209, "nearnode" },
    { 0x820A, "nearclaimnode" },
    { 0x820B, "nearclaimnodeandangle" },
    { 0x820C, "atdangerousnode" },
    { 0x820D, "getenemyinfo" },
    { 0x820E, "clearenemy" },
    { 0x820F, "setentitytarget" },
    { 0x8210, "clearentitytarget" },
    { 0x8211, "setpotentialthreat" },
    { 0x8212, "clearpotentialthreat" },
    { 0x8213, "setflashbanged" },
    { 0x8214, "setengagementmindist" },
    { 0x8215, "setengagementmaxdist" },
    { 0x8216, "isknownenemyinradius" },
    { 0x8217, "isknownenemyinvolume" },
    { 0x8218, "settalktospecies" },
    { 0x8219, "laseralton" },
    { 0x821A, "laseraltoff" },
    { 0x821B, "invisiblenotsolid" },
    { 0x821C, "visiblesolid" },
    { 0x821D, "setdefaultaimlimits" },
    { 0x821E, "initriotshieldhealth" },
    { 0x821F, "getenemysqdist" },
    { 0x8220, "getclosestenemysqdist" },
    { 0x8221, "setthreatbiasgroup" },
    { 0x8222, "getthreatbiasgroup" },
    { 0x8223, "makeentitysentient" },
    { 0x8224, "freeentitysentient" },
    { 0x8225, "isindoor" },
    { 0x8226, "getdroptofloorposition" },
    { 0x8227, "isbadguy" },
    { 0x8228, "animscripted" },
    { 0x8229, "animscriptedthirdperson" },
    { 0x822A, "animrelative" },
    { 0x822B, "stopanimscripted" },
    { 0x822C, "clearanim" },
    { 0x822D, "setanimknob" },
    { 0x822E, "setanimknoblimited" },
    { 0x822F, "setanimknobrestart" },
    { 0x8230, "setanimknoblimitedrestart" },
    { 0x8231, "setanimknoball" },
    { 0x8232, "setanimknoballlimited" },
    { 0x8233, "setanimknoballrestart" },
    { 0x8234, "setanimknoballlimitedrestart" },
    { 0x8235, "setanim" },
    { 0x8236, "setanimlimited" },
    { 0x8237, "setanimrestart" },
    { 0x8238, "setanimlimitedrestart" },
    { 0x8239, "getanimtime" },
    { 0x823A, "getanimweight" },
    { 0x823B, "getanimassettype" },
    { 0x823C, "setflaggedanimknob" },
    { 0x823D, "setflaggedanimknoblimited" },
    { 0x823E, "setflaggedanimknobrestart" },
    { 0x823F, "setflaggedanimknoblimitedrestart" },
    { 0x8240, "setflaggedanimknoball" },
    { 0x8241, "setflaggedanimknoballrestart" },
    { 0x8242, "setflaggedanim" },
    { 0x8243, "setflaggedanimlimited" },
    { 0x8244, "setflaggedanimrestart" },
    { 0x8245, "setflaggedanimlimitedrestart" },
    { 0x8246, "useanimtree" },
    { 0x8247, "stopuseanimtree" },
    { 0x8248, "setanimtime" },
    { 0x8249, "showviewmodel" },
    { 0x824A, "hideviewmodel" },
    { 0x824B, "allowstand" },
    { 0x824C, "allowcrouch" },
    { 0x824D, "allowprone" },
    { 0x824E, "allowlean" },
    { 0x824F, "setocclusion" },
    { 0x8250, "deactivateocclusion" },
    { 0x8251, "isocclusionenabled" },
    { 0x8252, "iseqenabled" },
    { 0x8253, "seteq" },
    { 0x8254, "seteqbands" },
    { 0x8255, "deactivateeq" },
    { 0x8256, "seteqlerp" },
    { 0x8257, "islookingat" },
    { 0x8258, "isthrowinggrenade" },
    { 0x8259, "isfiring" },
    { 0x825A, "ismeleeing" },
    { 0x825B, "setautopickup" },
    { 0x825C, "allowmelee" },
    { 0x825D, "allowfire" },
    { 0x825E, "enablehealthshield" },
    { 0x825F, "enabledeathshield" },
    { 0x8260, "nightvisiongogglesforceon" },
    { 0x8261, "nightvisiongogglesforceoff" },
    { 0x8262, "enableinvulnerability" },
    { 0x8263, "disableinvulnerability" },
    { 0x8264, "enablebreaching" },
    { 0x8265, "disablebreaching" },
    { 0x8266, "forceviewmodelanimation" },
    { 0x8267, "disableturretdismount" },
    { 0x8268, "enableturretdismount" },
    { 0x8269, "uploadscore" },
    { 0x826A, "uploadtime" },
    { 0x826B, "uploadleaderboards" },
    { 0x826C, "giveachievement" },
    { 0x826D, "hidehud" },
    { 0x826E, "showhud" },
    { 0x826F, "mountvehicle" },
    { 0x8270, "dismountvehicle" },
    { 0x8271, "enableslowaim" },
    { 0x8272, "disableslowaim" },
    { 0x8273, "usehintsinvehicle" },
    { 0x8274, "vehicleattackbuttonpressed" },
    { 0x8275, "setwhizbyoffset" },
    { 0x8276, "setwhizbyprobabilities" },
    { 0x8277, "visionsetnakedforplayer_lerp" },
    { 0x8278, "setwaitnode" },
    { 0x8279, "returnplayercontrol" },
    { 0x827A, "vehphys_starttrack" },
    { 0x827B, "vehphys_clearautodisable" },
    { 0x827C, "vehicleusealtblendedaudio" },
    { 0x827D, "settext" },
    { 0x827E, "clearalltextafterhudelem" },
    { 0x827F, "setshader" },
    { 0x8280, "settargetent" },
    { 0x8281, "cleartargetent" },
    { 0x8282, "settimer" },
    { 0x8283, "settimerup" },
    { 0x8284, "settimerstatic" },
    { 0x8285, "settenthstimer" },
    { 0x8286, "settenthstimerup" },
    { 0x8287, "settenthstimerstatic" },
    { 0x8288, "setclock" },
    { 0x8289, "setclockup" },
    { 0x828A, "setvalue" },
    { 0x828B, "setwaypoint" },
    { 0x828C, "setwaypointedgestyle_rotatingicon" },
    { 0x828D, "setwaypointedgestyle_secondaryarrow" },
    { 0x828E, "setwaypointiconoffscreenonly" },
    { 0x828F, "fadeovertime" },
    { 0x8290, "scaleovertime" },
    { 0x8291, "moveovertime" },
    { 0x8292, "reset" },
    { 0x8293, "destroy" },
    { 0x8294, "setpulsefx" },
    { 0x8295, "setplayernamestring" },
    { 0x8296, "changefontscaleovertime" },
    { 0x8297, "startignoringspotlight" },
    { 0x8298, "stopignoringspotlight" },
    { 0x8299, "dontcastshadows" },
    { 0x829A, "castshadows" },
    { 0x829B, "setstablemissile" },
    { 0x829C, "playersetgroundreferenceent" },
    { 0x829D, "dontinterpolate" },
    { 0x829E, "dospawn" },
    { 0x829F, "stalingradspawn" },
    { 0x82A0, "getorigin" },
    { 0x82A1, "getcentroid" },
    { 0x82A2, "getshootatpos" },
    { 0x82A3, "getdebugeye" },
    { 0x82A4, "useby" },
    { 0x82A5, "playsound" },
    { 0x82A6, "playsoundatviewheight" },
    { 0x82A7, "prefetchsound" },
    { 0x82A8, "setpitch" },
    { 0x82A9, "scalepitch" },
    { 0x82AA, "setvolume" },
    { 0x82AB, "scalevolume" },
    { 0x82AC, "setspeakermapmonotostereo" },
    { 0x82AD, "setspeakermapmonoto51" },
    { 0x82AE, "setdistributed2dsound" },
    { 0x82AF, "playsoundasmaster" },
    { 0x82B0, "playloopsound" },
    { 0x82B1, "eqon" },
    { 0x82B2, "eqoff" },
    { 0x82B3, "haseq" },
    { 0x82B4, "iswaitingonsound" },
    { 0x82B5, "getnormalhealth" },
    { 0x82B6, "setnormalhealth" },
    { 0x82B7, "dodamage" },
    { 0x82B8, "kill" },
    { 0x82B9, "show" },
    { 0x82BA, "hide" },
    { 0x82BB, "showonclient" },
    { 0x82BC, "hideonclient" },
    { 0x82BD, "laserforceon" },
    { 0x82BE, "laserforceoff" },
    { 0x82BF, "disconnectpaths" },
    { 0x82C0, "connectpaths" },
    { 0x82C1, "startusingheroonlylighting" },
    { 0x82C2, "stopusingheroonlylighting" },
    { 0x82C3, "startusinglessfrequentlighting" },
    { 0x82C4, "stopusinglessfrequentlighting" },
    { 0x82C5, "setthermalfog" },
    { 0x82C6, "setnightvisionfog" },
    { 0x82C7, "clearthermalfog" },
    { 0x82C8, "clearnightvisionfog" },
    { 0x82C9, "digitaldistortsetparams" },
    { 0x82CA, "setmode" },
    { 0x82CB, "getmode" },
    { 0x82CC, "setturretignoregoals" },
    { 0x82CD, "setturretcanaidetach" },
    { 0x82CE, "setturretfov" },
    { 0x82CF, "lerpfov" },
    { 0x82D0, "getvalidcoverpeekouts" },
    { 0x82D1, "gethighestnodestance" },
    { 0x82D2, "doesnodeallowstance" },
    { 0x82D3, "getgunangles" },
    { 0x82D4, "magicgrenade" },
    { 0x82D5, "magicgrenademanual" },
    { 0x82D6, "setfriendlychain" },
    { 0x82D7, "getentnum" },
    { 0x82D8, "launch" },
    { 0x82D9, "setsoundblend" },
    { 0x82DA, "makefakeai" },
    { 0x82DB, "spawndrone" },
    { 0x82DC, "setcorpseremovetimer" },
    { 0x82DD, "setlookattext" },
    { 0x82DE, "setspawnerteam" },
    { 0x82DF, "addaieventlistener" },
    { 0x82E0, "removeaieventlistener" },
    { 0x82E1, "getlightcolor" },
    { 0x82E2, "setlightcolor" },
    { 0x82E3, "getlightradius" },
    { 0x82E4, "setlightradius" },
    { 0x82E5, "getlightfovinner" },
    { 0x82E6, "getlightfovouter" },
    { 0x82E7, "setlightfovrange" },
    { 0x82E8, "getlightexponent" },
    { 0x82E9, "setlightexponent" },
    { 0x82EA, "startragdoll" },
    { 0x82EB, "startragdollfromimpact" },
    { 0x82EC, "logstring" },
    { 0x82ED, "laserhidefromclient" },
    { 0x82EE, "stopsoundchannel" },
    { 0x82EF, "thermaldrawenable" },
    { 0x82F0, "thermaldrawdisable" },
    { 0x82F1, "setturretdismountorg" },
    { 0x82F2, "setdamagestage" },
    { 0x82F3, "playsoundtoteam" },
    { 0x82F4, "playsoundtoplayer" },
    { 0x82F5, "playerhide" },
    { 0x82F6, "showtoplayer" },
    { 0x82F7, "enableplayeruse" },
    { 0x82F8, "disableplayeruse" },
    { 0x82F9, "makescrambler" },
    { 0x82FA, "makeportableradar" },
    { 0x82FB, "maketrophysystem" },
    { 0x82FC, "placespawnpoint" },
    { 0x82FD, "setteamfortrigger" },
    { 0x82FE, "clientclaimtrigger" },
    { 0x82FF, "clientreleasetrigger" },
    { 0x8300, "releaseclaimedtrigger" },
    { 0x8301, "isusingonlinedataoffline" },
    { 0x8302, "getrestedtime" },
    { 0x8303, "sendleaderboards" },
    { 0x8304, "isonladder" },
    { 0x8305, "getcorpseanim" },
    { 0x8306, "playerforcedeathanim" },
    { 0x8307, "startac130" },
    { 0x8308, "stopac130" },
    { 0x8309, "enablemousesteer" },
    { 0x830A, "setscriptmoverkillcam" },
    { 0x830B, "setmapnamestring" },
    { 0x830C, "setgametypestring" },
}};

const std::array<std::pair<std::uint16_t, const char*>, 5> token_list
{{
    { 0x0000, "" },
    { 0x0001, "pl#" },
    { 0x0002, "-" },
    { 0x0003, "radius`" },
    { 0x0004, "note:" },
}};

struct __init__
{
    __init__()
    {
        static bool init = false;
        if (init) return;
        init = true;

        opcode_map.reserve(opcode_list.size());
        opcode_map_rev.reserve(opcode_list.size());
        function_map.reserve(function_list.size());
        function_map_rev.reserve(function_list.size());
        method_map.reserve(method_list.size());
        method_map_rev.reserve(method_list.size());
        token_map.reserve(token_list.size());
        token_map_rev.reserve(token_list.size());

        for (const auto& entry : opcode_list)
        {
            opcode_map.insert({ entry.first, entry.second });
            opcode_map_rev.insert({ entry.second, entry.first });
        }

        for (const auto& entry : function_list)
        {
            function_map.insert({ entry.first, entry.second });
            function_map_rev.insert({ entry.second, entry.first });
        }

        for (const auto& entry : method_list)
        {
            method_map.insert({ entry.first, entry.second });
            method_map_rev.insert({ entry.second, entry.first });
        }

        for (const auto& entry : token_list)
        {
            token_map.insert({ entry.first, entry.second });
            token_map_rev.insert({ utils::string::to_lower(entry.second), entry.first });
        }
    }
};

__init__ _;

} // namespace xsk::gsc::iw5c

#ifdef _MSC_VER
#pragma warning(pop)
#endif
