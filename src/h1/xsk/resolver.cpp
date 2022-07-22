// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "h1.hpp"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4244)
#endif

namespace xsk::gsc::h1
{

std::unordered_map<std::uint8_t, std::string_view> opcode_map;
std::unordered_map<std::uint16_t, std::string_view> function_map;
std::unordered_map<std::uint16_t, std::string_view> method_map;
std::unordered_map<std::uint16_t, std::string_view> token_map;
std::unordered_map<std::string_view, std::uint8_t> opcode_map_rev;
std::unordered_map<std::string_view, std::uint16_t> function_map_rev;
std::unordered_map<std::string_view, std::uint16_t> method_map_rev;
std::unordered_map<std::string_view, std::uint16_t> token_map_rev;
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

auto resolver::file_data(const std::string& name) -> std::tuple<const std::string*, char*, size_t>
{
    const auto& itr = files.find(name);

    if (itr != files.end())
    {
        return { &itr->first ,reinterpret_cast<char*>(itr->second.data()), itr->second.size() };
    }

    auto data = read_callback(name);

    const auto& res = files.insert({ name, std::move(data)});

    if (res.second)
    {
        return { &res.first->first, reinterpret_cast<char*>(res.first->second.data()), res.first->second.size() };
    }

    throw error("couldn't open gsc file '" + name + "'");
}

std::set<std::string_view> paths
{
    "animscripts"sv,
    "animscripts/traverse"sv,
    "character"sv,
    "codescripts"sv,
    "common_scripts"sv,
    "destructible_scripts"sv,
    "maps"sv,
    "maps/animated_models"sv,
    "maps/createart"sv,
    "maps/createfx"sv,
    "maps/mp"sv,
    "maps/mp/gametypes"sv,
    "maps/mp/killstreaks"sv,
    "maps/mp/perks"sv,
    "mptype"sv,
    "soundscripts"sv,
    "vehicle_scripts"sv,
    "xmodelalias"sv,
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

const std::array<std::pair<std::uint8_t, const char*>, 154> opcode_list
{{
    { 0x17, "SET_NEW_LOCAL_VARIABLE_FIELD_CACHED0" },
    { 0x18, "EVAL_SELF_FIELD_VARIABLE" },
    { 0x19, "RETN" },
    { 0x1A, "CALL_BUILTIN_FUNC_0" },
    { 0x1B, "CALL_BUILTIN_FUNC_1" },
    { 0x1C, "CALL_BUILTIN_FUNC_2" },
    { 0x1D, "CALL_BUILTIN_FUNC_3" },
    { 0x1E, "CALL_BUILTIN_FUNC_4" },
    { 0x1F, "CALL_BUILTIN_FUNC_5" },
    { 0x20, "CALL_BUILTIN_FUNC" },
    { 0x21, "BOOL_NOT" },
    { 0x22, "CALL_FAR_METHOD_THEAD" },
    { 0x23, "JMP_EXPR_TRUE" },
    { 0x24, "SET_LEVEL_FIELD_VARIABLE_FIELD" },
    { 0x25, "CAST_BOOL" },
    { 0x26, "EVAL_NEW_LOCAL_ARRAY_REF_CACHED0" },
    { 0x27, "CALL_BUILTIN_FUNC_POINTER" },
    { 0x28, "INEQUALITY" },
    { 0x29, "GET_THISTHREAD" },
    { 0x2A, "CLEAR_FIELD_VARIABLE" },
    { 0x2B, "GET_FLOAT" },
    { 0x2C, "SAFE_CREATE_VARIABLE_FIELD_CACHED" },
    { 0x2D, "CALL_FAR_FUNC2" },
    { 0x2E, "CALL_FAR_FUNC" },
    { 0x2F, "CALL_FAR_FUNC_CHILD_THREAD" },
    { 0x30, "CLEAR_LOCAL_VARIABLE_FIELD_CACHED0" },
    { 0x31, "CLEAR_LOCAL_VARIABLE_FIELD_CACHED" },
    { 0x32, "CHECK_CLEAR_PARAMS" },
    { 0x33, "CAST_FIELD_OBJ" },
    { 0x34, "END" },
    { 0x35, "SIZE" },
    { 0x36, "EMPTY_ARRAY" },
    { 0x37, "BIT_AND" },
    { 0x38, "LESSEQUAL" },
    { 0x39, "VOIDCODEPOS" },
    { 0x3A, "CALL_METHOD_THREAD_POINTER" },
    { 0x3B, "ENDSWITCH" },
    { 0x3C, "CLEAR_VARIABLE_FIELD" },
    { 0x3D, "DIV" },
    { 0x3E, "CALL_FAR_METHOD_CHILD_THEAD" },
    { 0x3F, "GET_USHORT" },
    { 0x40, "JMP_TRUE" },
    { 0x41, "GET_SELF" },
    { 0x42, "CALL_FAR_FUNC_THREAD" },
    { 0x43, "CALL_LOCAL_FUNC_THREAD" },
    { 0x44, "SET_LOCAL_VARIABLE_FIELD_CACHED0" },
    { 0x45, "SET_LOCAL_VARIABLE_FIELD_CACHED" },
    { 0x46, "PLUS" },
    { 0x47, "BOOL_COMPLEMENT" },
    { 0x48, "CALL_METHOD_POINTER" },
    { 0x49, "INC" },
    { 0x4A, "REMOVE_LOCAL_VARIABLES" },
    { 0x4B, "JMP_EXPR_FALSE" },
    { 0x4C, "SWITCH" },
    { 0x4D, "CLEAR_PARAMS" },
    { 0x4E, "EVAL_LOCAL_VARIABLE_REF_CACHED0" },
    { 0x4F, "EVAL_LOCAL_VARIABLE_REF_CACHED" },
    { 0x50, "CALL_LOCAL_METHOD" },
    { 0x51, "EVAL_FIELD_VARIABLE" },
    { 0x52, "EVAL_FIELD_VARIABLE_REF" },
    { 0x53, "GET_STRING" },
    { 0x54, "CALL_FUNC_POINTER" },
    { 0x55, "EVAL_LEVEL_FIELD_VARIABLE" },
    { 0x56, "GET_VECTOR" },
    { 0x57, "ENDON" },
    { 0x58, "GREATEREQUAL" },
    { 0x59, "GET_SELF_OBJ" },
    { 0x5A, "SET_ANIM_FIELD_VARIABLE_FIELD" },
    { 0x5B, "SET_VARIABLE_FIELD" },
    { 0x5C, "CALL_LOCAL_FUNC2" },
    { 0x5D, "CALL_LOCAL_FUNC" },
    { 0x5E, "EVAL_LOCAL_ARRAY_REF_CACHED0" },
    { 0x5F, "EVAL_LOCAL_ARRAY_REF_CACHED" },
    { 0x60, "GET_FAR_FUNC" },
    { 0x61, "LESS" },
    { 0x62, "GET_GAME_REF" },
    { 0x63, "WAITFRAME" },
    { 0x64, "WAITTILLFRAMEEND" },
    { 0x65, "SAFE_SET_VARIABLE_FIELD_CACHED0" },
    { 0x66, "SAFE_SET_VARIABLE_FIELD_CACHED" },
    { 0x67, "CALL_METHOD_CHILD_THREAD_POINTER" },
    { 0x68, "GET_LEVEL" },
    { 0x69, "NOTIFY" },
    { 0x6A, "DEC_TOP" },
    { 0x6B, "SHIFT_LEFT" },
    { 0x6C, "CALL_LOCAL_METHOD_THREAD" },
    { 0x6D, "CALL_LOCAL_METHOD_CHILD_THREAD" },
    { 0x6E, "GREATER" },
    { 0x6F, "EVAL_LOCAL_VARIABLE_CACHED0" },
    { 0x70, "EVAL_LOCAL_VARIABLE_CACHED1" },
    { 0x71, "EVAL_LOCAL_VARIABLE_CACHED2" },
    { 0x72, "EVAL_LOCAL_VARIABLE_CACHED3" },
    { 0x73, "EVAL_LOCAL_VARIABLE_CACHED4" },
    { 0x74, "EVAL_LOCAL_VARIABLE_CACHED5" },
    { 0x75, "EVAL_LOCAL_VARIABLE_CACHED" },
    { 0x76, "SAFE_SET_WAITTILL_VARIABLE_FIELD_CACHED" },
    { 0x77, "JMP" },
    { 0x78, "CALL_FUNC_THREAD_POINTER" },
    { 0x79, "GET_ZERO" },
    { 0x7A, "WAIT" },
    { 0x7B, "MINUS" },
    { 0x7C, "SET_SELF_FIELD_VARIABLE_FIELD" },
    { 0x7D, "EVAL_NEW_LOCAL_VARIABLE_REF_CACHED0" },
    { 0x7E, "MULT" },
    { 0x7F, "CREATE_LOCAL_VARIABLE" },
    { 0x80, "CALL_LOCAL_FUNC_CHILD_THREAD" },
    { 0x81, "GET_INT" },
    { 0x82, "MOD" },
    { 0x83, "EVAL_ANIM_FIELD_VARIABLE_REF" },
    { 0x84, "GET_BUILTIN_FUNC" },
    { 0x85, "GET_GAME" },
    { 0x86, "WAITTILL" },
    { 0x87, "DEC" },
    { 0x88, "EVAL_LOCAL_VARIABLE_OBJECT_CACHED" },
    { 0x89, "PRE_CALL" },
    { 0x8A, "GET_ANIM" },
    { 0x8B, "GET_UNDEFINED" },
    { 0x8C, "EVAL_LEVEL_FIELD_VARIABLE_REF" },
    { 0x8D, "GET_ANIM_OBJ" },
    { 0x8E, "GET_LEVEL_OBJ" },
    { 0x8F, "BIT_EXOR" },
    { 0x90, "EQUALITY" },
    { 0x91, "CLEAR_ARRAY" },
    { 0x92, "JMP_BACK" },
    { 0x93, "GET_ANIMATION" },
    { 0x94, "EVAL_ANIM_FIELD_VARIABLE" },
    { 0x95, "GET_ANIMTREE" },
    { 0x96, "GET_ISTRING" },
    { 0x97, "EVAL_ARRAY_REF" },
    { 0x98, "EVAL_SELF_FIELD_VARIABLE_REF" },
    { 0x99, "GET_NBYTE" },
    { 0x9A, "GET_BUILTIN_METHOD" },
    { 0x9B, "CALL_BUILTIN_METHOD_POINTER" },
    { 0x9C, "EVAL_ARRAY" },
    { 0x9D, "VECTOR" },
    { 0x9E, "CALL_FAR_METHOD" },
    { 0x9F, "EVAL_LOCAL_ARRAY_CACHED" },
    { 0xA0, "GET_BYTE" },
    { 0xA1, "CALL_FUNC_CHILD_THREAD_POINTER" },
    { 0xA2, "BIT_OR" },
    { 0xA3, "ADD_ARRAY" },
    { 0xA4, "WAITTILLMATCH2" },
    { 0xA5, "WAITTILLMATCH" },
    { 0xA6, "GET_LOCAL_FUNC" },
    { 0xA7, "GET_NUSHORT" },
    { 0xA8, "SHIFT_RIGHT" },
    { 0xA9, "CALL_BUILTIN_METHOD_0" },
    { 0xAA, "CALL_BUILTIN_METHOD_1" },
    { 0xAB, "CALL_BUILTIN_METHOD_2" },
    { 0xAC, "CALL_BUILTIN_METHOD_3" },
    { 0xAD, "CALL_BUILTIN_METHOD_4" },
    { 0xAE, "CALL_BUILTIN_METHOD_5" },
    { 0xAF, "CALL_BUILTIN_METHOD" },
    { 0xB0, "JMP_FALSE" },
}};

const std::array<std::pair<std::uint16_t, const char*>, 778> function_list
{{
    { 0x001, "precacheturret" },
    { 0x002, "getweaponarray" },
    { 0x003, "createprintchannel" },
    { 0x004, "updategamerprofileall" },
    { 0x005, "clearlocalizedstrings" },
    { 0x006, "setphysicsgravitydir" },
    { 0x007, "gettimescale" },
    { 0x008, "settimescale" },
    { 0x009, "setslowmotionview" },
    { 0x00A, "teleportscene" },
    { 0x00B, "forcesharedammo" },
    { 0x00C, "refreshhudcompass" },
    { 0x00D, "refreshhudammocounter" },
    { 0x00E, "notifyoncommand" },
    { 0x00F, "setprintchannel" },
    { 0x010, "print" },
    { 0x011, "println" },
    { 0x012, "print3d" },
    { 0x013, "line" },
    { 0x014, "box" },
    { 0x015, "orientedbox" },
    { 0x016, "sphere" },
    { 0x017, "cylinder" },
    { 0x018, "spawnturret" },
    { 0x019, "canspawnturret" },
    { 0x01A, "assert" },
    { 0x01B, "pausecinematicingame" },
    { 0x01C, "drawcompassfriendlies" },
    { 0x01D, "bulletspread" },
    { 0x01E, "bullettracer" },
    { 0x01F, "badplace_delete" },
    { 0x020, "badplace_cylinder" },
    { 0x021, "badplace_arc" },
    { 0x022, "badplace_brush" },
    { 0x023, "clearallcorpses" },
    { 0x024, "setturretnode" },
    { 0x025, "unsetturretnode" },
    { 0x026, "setnodepriority" },
    { 0x027, "_func_027" },
    { 0x028, "_func_028" },
    { 0x029, "_func_029" },
    { 0x02A, "_func_02A" },
    { 0x02B, "_func_02B" },
    { 0x02C, "updategamerprofile" },
    { 0x02D, "assertex" },
    { 0x02E, "assertmsg" },
    { 0x02F, "isdefined" },
    { 0x030, "isvalidmissile" },
    { 0x031, "isstring" },
    { 0x032, "setomnvar" },
    { 0x033, "getomnvar" },
    { 0x034, "setdvar" },
    { 0x035, "setdynamicdvar" },
    { 0x036, "setdvarifuninitialized" },
    { 0x037, "setdevdvar" },
    { 0x038, "setdevdvarifuninitialized" },
    { 0x039, "getdvar" },
    { 0x03A, "getdvarint" },
    { 0x03B, "getdvarfloat" },
    { 0x03C, "getdvarvector" },
    { 0x03D, "gettime" },
    { 0x03E, "gettimeutc" },
    { 0x03F, "getradiometricunit" },
    { 0x040, "getentbynum" },
    { 0x041, "_func_041" },
    { 0x042, "_func_042" },
    { 0x043, "_func_043" },
    { 0x044, "_func_044" },
    { 0x045, "_func_045" },
    { 0x046, "_func_046" },
    { 0x047, "_func_047" },
    { 0x048, "_func_048" },
    { 0x049, "_func_049" },
    { 0x04A, "_func_04A" },
    { 0x04B, "_func_04B" },
    { 0x04C, "_func_04C" },
    { 0x04D, "_func_04D" },
    { 0x04E, "_func_04E" },
    { 0x04F, "_func_04F" },
    { 0x050, "_func_050" },
    { 0x051, "_func_051" },
    { 0x052, "_func_052" },
    { 0x053, "_func_053" },
    { 0x054, "_func_054" },
    { 0x055, "_func_055" },
    { 0x056, "_func_056" },
    { 0x057, "_func_057" },
    { 0x058, "_func_058" },
    { 0x059, "_func_059" },
    { 0x05A, "_func_05A" },
    { 0x05B, "_func_05B" },
    { 0x05C, "_func_05C" },
    { 0x05D, "_func_05D" },
    { 0x05E, "_func_05E" },
    { 0x05F, "_func_05F" },
    { 0x060, "_func_060" },
    { 0x061, "_func_061" },
    { 0x062, "_func_062" },
    { 0x063, "_func_063" },
    { 0x064, "_func_064" },
    { 0x065, "getanimlength" },
    { 0x066, "animhasnotetrack" },
    { 0x067, "getnotetracktimes" },
    { 0x068, "spawn" },
    { 0x069, "_func_069" },
    { 0x06A, "_func_06A" },
    { 0x06B, "_func_06B" },
    { 0x06C, "_func_06C" },
    { 0x06D, "_func_06D" },
    { 0x06E, "_func_06E" },
    { 0x06F, "_func_06F" },
    { 0x070, "_func_070" },
    { 0x071, "_func_071" },
    { 0x072, "_func_072" },
    { 0x073, "_func_073" },
    { 0x074, "_func_074" },
    { 0x075, "_func_075" },
    { 0x076, "_func_076" },
    { 0x077, "_func_077" },
    { 0x078, "_func_078" },
    { 0x079, "_func_079" },
    { 0x07A, "_func_07A" },
    { 0x07B, "_func_07B" },
    { 0x07C, "_func_07C" },
    { 0x07D, "_func_07D" },
    { 0x07E, "_func_07E" },
    { 0x07F, "_func_07F" },
    { 0x080, "_func_080" },
    { 0x081, "_func_081" },
    { 0x082, "_func_082" },
    { 0x083, "_func_083" },
    { 0x084, "_func_084" },
    { 0x085, "_func_085" },
    { 0x086, "_func_086" },
    { 0x087, "_func_087" },
    { 0x088, "_func_088" },
    { 0x089, "_func_089" },
    { 0x08A, "_func_08A" },
    { 0x08B, "_func_08B" },
    { 0x08C, "_func_08C" },
    { 0x08D, "_func_08D" },
    { 0x08E, "_func_08E" },
    { 0x08F, "_func_08F" },
    { 0x090, "_func_090" },
    { 0x091, "_func_091" },
    { 0x092, "_func_092" },
    { 0x093, "_func_093" },
    { 0x094, "_func_094" },
    { 0x095, "_func_095" },
    { 0x096, "_func_096" },
    { 0x097, "_func_097" },
    { 0x098, "_func_098" },
    { 0x099, "_func_099" },
    { 0x09A, "_func_09A" },
    { 0x09B, "_func_09B" },
    { 0x09C, "_func_09C" },
    { 0x09D, "_func_09D" },
    { 0x09E, "_func_09E" },
    { 0x09F, "_func_09F" },
    { 0x0A0, "_func_0A0" },
    { 0x0A1, "_func_0A1" },
    { 0x0A2, "_func_0A2" },
    { 0x0A3, "_func_0A3" },
    { 0x0A4, "_func_0A4" },
    { 0x0A5, "_func_0A5" },
    { 0x0A6, "_func_0A6" },
    { 0x0A7, "_func_0A7" },
    { 0x0A8, "_func_0A8" },
    { 0x0A9, "_func_0A9" },
    { 0x0AA, "_func_0AA" },
    { 0x0AB, "_func_0AB" },
    { 0x0AC, "_func_0AC" },
    { 0x0AD, "_func_0AD" },
    { 0x0AE, "_func_0AE" },
    { 0x0AF, "_func_0AF" },
    { 0x0B0, "_func_0B0" },
    { 0x0B1, "_func_0B1" },
    { 0x0B2, "_func_0B2" },
    { 0x0B3, "_func_0B3" },
    { 0x0B4, "_func_0B4" },
    { 0x0B5, "_func_0B5" },
    { 0x0B6, "_func_0B6" },
    { 0x0B7, "_func_0B7" },
    { 0x0B8, "_func_0B8" },
    { 0x0B9, "_func_0B9" },
    { 0x0BA, "_func_0BA" },
    { 0x0BB, "_func_0BB" },
    { 0x0BC, "_func_0BC" },
    { 0x0BD, "_func_0BD" },
    { 0x0BE, "_func_0BE" },
    { 0x0BF, "_func_0BF" },
    { 0x0C0, "_func_0C0" },
    { 0x0C1, "_func_0C1" },
    { 0x0C2, "_func_0C2" },
    { 0x0C3, "_func_0C3" },
    { 0x0C4, "_func_0C4" },
    { 0x0C5, "_func_0C5" },
    { 0x0C6, "_func_0C6" },
    { 0x0C7, "_func_0C7" },
    { 0x0C8, "_func_0C8" },
    { 0x0C9, "_func_0C9" },
    { 0x0CA, "_func_0CA" },
    { 0x0CB, "_func_0CB" },
    { 0x0CC, "_func_0CC" },
    { 0x0CD, "_func_0CD" },
    { 0x0CE, "_func_0CE" },
    { 0x0CF, "_func_0CF" },
    { 0x0D0, "_func_0D0" },
    { 0x0D1, "_func_0D1" },
    { 0x0D2, "_func_0D2" },
    { 0x0D3, "_func_0D3" },
    { 0x0D4, "_func_0D4" },
    { 0x0D5, "_func_0D5" },
    { 0x0D6, "_func_0D6" },
    { 0x0D7, "_func_0D7" },
    { 0x0D8, "_func_0D8" },
    { 0x0D9, "_func_0D9" },
    { 0x0DA, "_func_0DA" },
    { 0x0DB, "_func_0DB" },
    { 0x0DC, "_func_0DC" },
    { 0x0DD, "_func_0DD" },
    { 0x0DE, "_func_0DE" },
    { 0x0DF, "_func_0DF" },
    { 0x0E0, "_func_0E0" },
    { 0x0E1, "_func_0E1" },
    { 0x0E2, "_func_0E2" },
    { 0x0E3, "_func_0E3" },
    { 0x0E4, "_func_0E4" },
    { 0x0E5, "_func_0E5" },
    { 0x0E6, "_func_0E6" },
    { 0x0E7, "_func_0E7" },
    { 0x0E8, "_func_0E8" },
    { 0x0E9, "_func_0E9" },
    { 0x0EA, "_func_0EA" },
    { 0x0EB, "_func_0EB" },
    { 0x0EC, "_func_0EC" },
    { 0x0ED, "_func_0ED" },
    { 0x0EE, "_func_0EE" },
    { 0x0EF, "_func_0EF" },
    { 0x0F0, "_func_0F0" },
    { 0x0F1, "_func_0F1" },
    { 0x0F2, "_func_0F2" },
    { 0x0F3, "_func_0F3" },
    { 0x0F4, "_func_0F4" },
    { 0x0F5, "_func_0F5" },
    { 0x0F6, "_func_0F6" },
    { 0x0F7, "_func_0F7" },
    { 0x0F8, "_func_0F8" },
    { 0x0F9, "_func_0F9" },
    { 0x0FA, "_func_0FA" },
    { 0x0FB, "_func_0FB" },
    { 0x0FC, "_func_0FC" },
    { 0x0FD, "_func_0FD" },
    { 0x0FE, "_func_0FE" },
    { 0x0FF, "_func_0FF" },
    { 0x100, "_func_100" },
    { 0x101, "_func_101" },
    { 0x102, "_func_102" },
    { 0x103, "_func_103" },
    { 0x104, "_func_104" },
    { 0x105, "_func_105" },
    { 0x106, "_func_106" },
    { 0x107, "createthreatbiasgroup" },
    { 0x108, "threatbiasgroupexists" },
    { 0x109, "getthreatbias" },
    { 0x10A, "setthreatbias" },
    { 0x10B, "setthreatbiasagainstall" },
    { 0x10C, "setignoremegroup" },
    { 0x10D, "isenemyteam" },
    { 0x10E, "_func_10E" },
    { 0x10F, "_func_10F" },
    { 0x110, "_func_110" },
    { 0x111, "_func_111" },
    { 0x112, "_func_112" },
    { 0x113, "_func_113" },
    { 0x114, "_func_114" },
    { 0x115, "_func_115" },
    { 0x116, "_func_116" },
    { 0x117, "_func_117" },
    { 0x118, "anglestoup" },
    { 0x119, "anglestoright" },
    { 0x11A, "anglestoforward" },
    { 0x11B, "_func_11B" },
    { 0x11C, "_func_11C" },
    { 0x11D, "_func_11D" },
    { 0x11E, "_func_11E" },
    { 0x11F, "_func_11F" },
    { 0x120, "_func_120" },
    { 0x121, "_func_121" },
    { 0x122, "_func_122" },
    { 0x123, "_func_123" },
    { 0x124, "_func_124" },
    { 0x125, "_func_125" },
    { 0x126, "_func_126" },
    { 0x127, "_func_127" },
    { 0x128, "_func_128" },
    { 0x129, "_func_129" },
    { 0x12A, "_func_12A" },
    { 0x12B, "_func_12B" },
    { 0x12C, "_func_12C" },
    { 0x12D, "_func_12D" },
    { 0x12E, "_func_12E" },
    { 0x12F, "_func_12F" },
    { 0x130, "_func_130" },
    { 0x131, "_func_131" },
    { 0x132, "_func_132" },
    { 0x133, "_func_133" },
    { 0x134, "_func_134" },
    { 0x135, "_func_135" },
    { 0x136, "_func_136" },
    { 0x137, "_func_137" },
    { 0x138, "_func_138" },
    { 0x139, "_func_139" },
    { 0x13A, "_func_13A" },
    { 0x13B, "_func_13B" },
    { 0x13C, "_func_13C" },
    { 0x13D, "_func_13D" },
    { 0x13E, "_func_13E" },
    { 0x13F, "_func_13F" },
    { 0x140, "_func_140" },
    { 0x141, "_func_141" },
    { 0x142, "_func_142" },
    { 0x143, "_func_143" },
    { 0x144, "_func_144" },
    { 0x145, "_func_145" },
    { 0x146, "_func_146" },
    { 0x147, "precachemodel" },
    { 0x148, "precacheshellshock" },
    { 0x149, "precacheitem" },
    { 0x14A, "precacheshader" },
    { 0x14B, "precachestring" },
    { 0x14C, "precachemenu" },
    { 0x14D, "precacherumble" },
    { 0x14E, "precachelocationselector" },
    { 0x14F, "precacheleaderboards" },
    { 0x150, "loadfx" },
    { 0x151, "playfx" },
    { 0x152, "playfxontag" },
    { 0x153, "stopfxontag" },
    { 0x154, "killfxontag" },
    { 0x155, "playloopedfx" },
    { 0x156, "spawnfx" },
    { 0x157, "triggerfx" },
    { 0x158, "playfxontagforclients" },
    { 0x159, "setfxkillondelete" },
    { 0x15A, "_func_15A" },
    { 0x15B, "_func_15B" },
    { 0x15C, "_func_15C" },
    { 0x15D, "_func_15D" },
    { 0x15E, "_func_15E" },
    { 0x15F, "_func_15F" },
    { 0x160, "_func_160" },
    { 0x161, "_func_161" },
    { 0x162, "_func_162" },
    { 0x163, "_func_163" },
    { 0x164, "_func_164" },
    { 0x165, "_func_165" },
    { 0x166, "_func_166" },
    { 0x167, "_func_167" },
    { 0x168, "_func_168" },
    { 0x169, "_func_169" },
    { 0x16A, "_func_16A" },
    { 0x16B, "_func_16B" },
    { 0x16C, "_func_16C" },
    { 0x16D, "_func_16D" },
    { 0x16E, "_func_16E" },
    { 0x16F, "_func_16F" },
    { 0x170, "_func_170" },
    { 0x171, "_func_171" },
    { 0x172, "_func_172" },
    { 0x173, "_func_173" },
    { 0x174, "_func_174" },
    { 0x175, "_func_175" },
    { 0x176, "_func_176" },
    { 0x177, "_func_177" },
    { 0x178, "_func_178" },
    { 0x179, "_func_179" },
    { 0x17A, "_func_17A" },
    { 0x17B, "_func_17B" },
    { 0x17C, "_func_17C" },
    { 0x17D, "_func_17D" },
    { 0x17E, "_func_17E" },
    { 0x17F, "_func_17F" },
    { 0x180, "_func_180" },
    { 0x181, "_func_181" },
    { 0x182, "_func_182" },
    { 0x183, "_func_183" },
    { 0x184, "_func_184" },
    { 0x185, "_func_185" },
    { 0x186, "_func_186" },
    { 0x187, "_func_187" },
    { 0x188, "_func_188" },
    { 0x189, "_func_189" },
    { 0x18A, "_func_18A" },
    { 0x18B, "_func_18B" },
    { 0x18C, "_func_18C" },
    { 0x18D, "_func_18D" },
    { 0x18E, "objective_onentity" },
    { 0x18F, "objective_onentitywithrotation" },
    { 0x190, "objective_team" },
    { 0x191, "objective_player" },
    { 0x192, "objective_playerteam" },
    { 0x193, "objective_playerenemyteam" },
    { 0x194, "objective_playermask_hidefromall" },
    { 0x195, "objective_playermask_hidefrom" },
    { 0x196, "objective_playermask_showtoall" },
    { 0x197, "objective_playermask_showto" },
    { 0x198, "iprintln" },
    { 0x199, "iprintlnbold" },
    { 0x19A, "logstring" },
    { 0x19B, "getent" },
    { 0x19C, "getentarray" },
    { 0x19D, "getspawnarray" },
    { 0x19E, "spawnplane" },
    { 0x19F, "spawnstruct" },
    { 0x1A0, "spawnhelicopter" },
    { 0x1A1, "_func_1A1" },
    { 0x1A2, "_func_1A2" },
    { 0x1A3, "_func_1A3" },
    { 0x1A4, "_func_1A4" },
    { 0x1A5, "_func_1A5" },
    { 0x1A6, "_func_1A6" },
    { 0x1A7, "_func_1A7" },
    { 0x1A8, "_func_1A8" },
    { 0x1A9, "_func_1A9" },
    { 0x1AA, "_func_1AA" },
    { 0x1AB, "_func_1AB" },
    { 0x1AC, "_func_1AC" },
    { 0x1AD, "_func_1AD" },
    { 0x1AE, "_func_1AE" },
    { 0x1AF, "_func_1AF" },
    { 0x1B0, "_func_1B0" },
    { 0x1B1, "_func_1B1" },
    { 0x1B2, "_func_1B2" },
    { 0x1B3, "_func_1B3" },
    { 0x1B4, "_func_1B4" },
    { 0x1B5, "_func_1B5" },
    { 0x1B6, "_func_1B6" },
    { 0x1B7, "_func_1B7" },
    { 0x1B8, "_func_1B8" },
    { 0x1B9, "getnextarraykey" },
    { 0x1BA, "_func_1BA" },
    { 0x1BB, "_func_1BB" },
    { 0x1BC, "_func_1BC" },
    { 0x1BD, "_func_1BD" },
    { 0x1BE, "_func_1BE" },
    { 0x1BF, "_func_1BF" },
    { 0x1C0, "_func_1C0" },
    { 0x1C1, "_func_1C1" },
    { 0x1C2, "_func_1C2" },
    { 0x1C3, "_func_1C3" },
    { 0x1C4, "_func_1C4" },
    { 0x1C5, "_func_1C5" },
    { 0x1C6, "_func_1C6" },
    { 0x1C7, "_func_1C7" },
    { 0x1C8, "_func_1C8" },
    { 0x1C9, "_func_1C9" },
    { 0x1CA, "_func_1CA" },
    { 0x1CB, "_func_1CB" },
    { 0x1CC, "_func_1CC" },
    { 0x1CD, "_func_1CD" },
    { 0x1CE, "_func_1CE" },
    { 0x1CF, "_func_1CF" },
    { 0x1D0, "_func_1D0" },
    { 0x1D1, "_func_1D1" },
    { 0x1D2, "_func_1D2" },
    { 0x1D3, "_func_1D3" },
    { 0x1D4, "getfirstarraykey" },
    { 0x1D5, "_func_1D5" },
    { 0x1D6, "_func_1D6" },
    { 0x1D7, "_func_1D7" },
    { 0x1D8, "_func_1D8" },
    { 0x1D9, "_func_1D9" },
    { 0x1DA, "_func_1DA" },
    { 0x1DB, "_func_1DB" },
    { 0x1DC, "_func_1DC" },
    { 0x1DD, "objective_add" },
    { 0x1DE, "objective_delete" },
    { 0x1DF, "objective_state" },
    { 0x1E0, "objective_icon" },
    { 0x1E1, "_func_1E1" },
    { 0x1E2, "objective_position" },
    { 0x1E3, "objective_current" },
    { 0x1E4, "_func_1E4" },
    { 0x1E5, "_func_1E5" },
    { 0x1E6, "_func_1E6" },
    { 0x1E7, "_func_1E7" },
    { 0x1E8, "_func_1E8" },
    { 0x1E9, "_func_1E9" },
    { 0x1EA, "_func_1EA" },
    { 0x1EB, "_func_1EB" },
    { 0x1EC, "_func_1EC" },
    { 0x1ED, "_func_1ED" },
    { 0x1EE, "_func_1EE" },
    { 0x1EF, "_func_1EF" },
    { 0x1F0, "_func_1F0" },
    { 0x1F1, "_func_1F1" },
    { 0x1F2, "_func_1F2" },
    { 0x1F3, "_func_1F3" },
    { 0x1F4, "_func_1F4" },
    { 0x1F5, "_func_1F5" },
    { 0x1F6, "_func_1F6" },
    { 0x1F7, "_func_1F7" },
    { 0x1F8, "_func_1F8" },
    { 0x1F9, "_func_1F9" },
    { 0x1FA, "_func_1FA" },
    { 0x1FB, "_func_1FB" },
    { 0x1FC, "_func_1FC" },
    { 0x1FD, "_func_1FD" },
    { 0x1FE, "_func_1FE" },
    { 0x1FF, "_func_1FF" },
    { 0x200, "_func_200" },
    { 0x201, "_func_201" },
    { 0x202, "_func_202" },
    { 0x203, "_func_203" },
    { 0x204, "_func_204" },
    { 0x205, "_func_205" },
    { 0x206, "_func_206" },
    { 0x207, "_func_207" },
    { 0x208, "_func_208" },
    { 0x209, "_func_209" },
    { 0x20A, "_func_20A" },
    { 0x20B, "_func_20B" },
    { 0x20C, "_func_20C" },
    { 0x20D, "_func_20D" },
    { 0x20E, "_func_20E" },
    { 0x20F, "_func_20F" },
    { 0x210, "_func_210" },
    { 0x211, "_func_211" },
    { 0x212, "_func_212" },
    { 0x213, "_func_213" },
    { 0x214, "_func_214" },
    { 0x215, "_func_215" },
    { 0x216, "_func_216" },
    { 0x217, "_func_217" },
    { 0x218, "_func_218" },
    { 0x219, "_func_219" },
    { 0x21A, "_func_21A" },
    { 0x21B, "_func_21B" },
    { 0x21C, "_func_21C" },
    { 0x21D, "_func_21D" },
    { 0x21E, "_func_21E" },
    { 0x21F, "_func_21F" },
    { 0x220, "_func_220" },
    { 0x221, "_func_221" },
    { 0x222, "_func_222" },
    { 0x223, "_func_223" },
    { 0x224, "_func_224" },
    { 0x225, "_func_225" },
    { 0x226, "_func_226" },
    { 0x227, "_func_227" },
    { 0x228, "_func_228" },
    { 0x229, "_func_229" },
    { 0x22A, "_func_22A" },
    { 0x22B, "_func_22B" },
    { 0x22C, "_func_22C" },
    { 0x22D, "_func_22D" },
    { 0x22E, "_func_22E" },
    { 0x22F, "_func_22F" },
    { 0x230, "_func_230" },
    { 0x231, "_func_231" },
    { 0x232, "_func_232" },
    { 0x233, "_func_233" },
    { 0x234, "_func_234" },
    { 0x235, "_func_235" },
    { 0x236, "_func_236" },
    { 0x237, "_func_237" },
    { 0x238, "_func_238" },
    { 0x239, "_func_239" },
    { 0x23A, "_func_23A" },
    { 0x23B, "_func_23B" },
    { 0x23C, "_func_23C" },
    { 0x23D, "_func_23D" },
    { 0x23E, "_func_23E" },
    { 0x23F, "_func_23F" },
    { 0x240, "_func_240" },
    { 0x241, "_func_241" },
    { 0x242, "_func_242" },
    { 0x243, "_func_243" },
    { 0x244, "_func_244" },
    { 0x245, "_func_245" },
    { 0x246, "_func_246" },
    { 0x247, "_func_247" },
    { 0x248, "_func_248" },
    { 0x249, "_func_249" },
    { 0x24A, "_func_24A" },
    { 0x24B, "_func_24B" },
    { 0x24C, "_func_24C" },
    { 0x24D, "_func_24D" },
    { 0x24E, "_func_24E" },
    { 0x24F, "_func_24F" },
    { 0x250, "_func_250" },
    { 0x251, "_func_251" },
    { 0x252, "_func_252" },
    { 0x253, "_func_253" },
    { 0x254, "_func_254" },
    { 0x255, "_func_255" },
    { 0x256, "_func_256" },
    { 0x257, "_func_257" },
    { 0x258, "_func_258" },
    { 0x259, "_func_259" },
    { 0x25A, "_func_25A" },
    { 0x25B, "_func_25B" },
    { 0x25C, "_func_25C" },
    { 0x25D, "_func_25D" },
    { 0x25E, "_func_25E" },
    { 0x25F, "_func_25F" },
    { 0x260, "_func_260" },
    { 0x261, "_func_261" },
    { 0x262, "_func_262" },
    { 0x263, "_func_263" },
    { 0x264, "_func_264" },
    { 0x265, "_func_265" },
    { 0x266, "_func_266" },
    { 0x267, "_func_267" },
    { 0x268, "_func_268" },
    { 0x269, "_func_269" },
    { 0x26A, "_func_26A" },
    { 0x26B, "_func_26B" },
    { 0x26C, "_func_26C" },
    { 0x26D, "_func_26D" },
    { 0x26E, "_func_26E" },
    { 0x26F, "_func_26F" },
    { 0x270, "_func_270" },
    { 0x271, "_func_271" },
    { 0x272, "_func_272" },
    { 0x273, "_func_273" },
    { 0x274, "_func_274" },
    { 0x275, "_func_275" },
    { 0x276, "_func_276" },
    { 0x277, "_func_277" },
    { 0x278, "_func_278" },
    { 0x279, "_func_279" },
    { 0x27A, "_func_27A" },
    { 0x27B, "_func_27B" },
    { 0x27C, "_func_27C" },
    { 0x27D, "_func_27D" },
    { 0x27E, "_func_27E" },
    { 0x27F, "_func_27F" },
    { 0x280, "_func_280" },
    { 0x281, "_func_281" },
    { 0x282, "_func_282" },
    { 0x283, "_func_283" },
    { 0x284, "_func_284" },
    { 0x285, "_func_285" },
    { 0x286, "_func_286" },
    { 0x287, "_func_287" },
    { 0x288, "_func_288" },
    { 0x289, "_func_289" },
    { 0x28A, "_func_28A" },
    { 0x28B, "_func_28B" },
    { 0x28C, "_func_28C" },
    { 0x28D, "isalliedsentient" },
    { 0x28E, "_func_28E" },
    { 0x28F, "_func_28F" },
    { 0x290, "_func_290" },
    { 0x291, "_func_291" },
    { 0x292, "_func_292" },
    { 0x293, "_func_293" },
    { 0x294, "_func_294" },
    { 0x295, "_func_295" },
    { 0x296, "_func_296" },
    { 0x297, "_func_297" },
    { 0x298, "_func_298" },
    { 0x299, "_func_299" },
    { 0x29A, "_func_29A" },
    { 0x29B, "_func_29B" },
    { 0x29C, "_func_29C" },
    { 0x29D, "_func_29D" },
    { 0x29E, "_func_29E" },
    { 0x29F, "_func_29F" },
    { 0x2A0, "_func_2A0" },
    { 0x2A1, "_func_2A1" },
    { 0x2A2, "_func_2A2" },
    { 0x2A3, "_func_2A3" },
    { 0x2A4, "_func_2A4" },
    { 0x2A5, "_func_2A5" },
    { 0x2A6, "_func_2A6" },
    { 0x2A7, "_func_2A7" },
    { 0x2A8, "_func_2A8" },
    { 0x2A9, "_func_2A9" },
    { 0x2AA, "_func_2AA" },
    { 0x2AB, "_func_2AB" },
    { 0x2AC, "_func_2AC" },
    { 0x2AD, "_func_2AD" },
    { 0x2AE, "_func_2AE" },
    { 0x2AF, "_func_2AF" },
    { 0x2B0, "_func_2B0" },
    { 0x2B1, "_func_2B1" },
    { 0x2B2, "_func_2B2" },
    { 0x2B3, "_func_2B3" },
    { 0x2B4, "_func_2B4" },
    { 0x2B5, "_func_2B5" },
    { 0x2B6, "_func_2B6" },
    { 0x2B7, "_func_2B7" },
    { 0x2B8, "_func_2B8" },
    { 0x2B9, "_func_2B9" },
    { 0x2BA, "_func_2BA" },
    { 0x2BB, "_func_2BB" },
    { 0x2BC, "_func_2BC" },
    { 0x2BD, "_func_2BD" },
    { 0x2BE, "_func_2BE" },
    { 0x2BF, "objective_mlgspectator" },
    { 0x2C0, "_func_2C0" },
    { 0x2C1, "_func_2C1" },
    { 0x2C2, "_func_2C2" },
    { 0x2C3, "_func_2C3" },
    { 0x2C4, "_func_2C4" },
    { 0x2C5, "_func_2C5" },
    { 0x2C6, "_func_2C6" },
    { 0x2C7, "_func_2C7" },
    { 0x2C8, "_func_2C8" },
    { 0x2C9, "_func_2C9" },
    { 0x2CA, "_func_2CA" },
    { 0x2CB, "_func_2CB" },
    { 0x2CC, "_func_2CC" },
    { 0x2CD, "_func_2CD" },
    { 0x2CE, "_func_2CE" },
    { 0x2CF, "_func_2CF" },
    { 0x2D0, "_func_2D0" },
    { 0x2D1, "_func_2D1" },
    { 0x2D2, "_func_2D2" },
    { 0x2D3, "_func_2D3" },
    { 0x2D4, "_func_2D4" },
    { 0x2D5, "_func_2D5" },
    { 0x2D6, "_func_2D6" },
    { 0x2D7, "_func_2D7" },
    { 0x2D8, "_func_2D8" },
    { 0x2D9, "_func_2D9" },
    { 0x2DA, "_func_2DA" },
    { 0x2DB, "_func_2DB" },
    { 0x2DC, "_func_2DC" },
    { 0x2DD, "_func_2DD" },
    { 0x2DE, "_func_2DE" },
    { 0x2DF, "_func_2DF" },
    { 0x2E0, "_func_2E0" },
    { 0x2E1, "_func_2E1" },
    { 0x2E2, "_func_2E2" },
    { 0x2E3, "_func_2E3" },
    { 0x2E4, "_func_2E4" },
    { 0x2E5, "_func_2E5" },
    { 0x2E6, "_func_2E6" },
    { 0x2E7, "_func_2E7" },
    { 0x2E8, "_func_2E8" },
    { 0x2E9, "_func_2E9" },
    { 0x2EA, "_func_2EA" },
    { 0x2EB, "_func_2EB" },
    { 0x2EC, "_func_2EC" },
    { 0x2ED, "_func_2ED" },
    { 0x2EE, "_func_2EE" },
    { 0x2EF, "_func_2EF" },
    { 0x2F0, "_func_2F0" },
    { 0x2F1, "_func_2F1" },
    { 0x2F2, "_func_2F2" },
    { 0x2F3, "_func_2F3" },
    { 0x2F4, "_func_2F4" },
    { 0x2F5, "_func_2F5" },
    { 0x2F6, "_func_2F6" },
    { 0x2F7, "_func_2F7" },
    { 0x2F8, "_func_2F8" },
    { 0x2F9, "_func_2F9" },
    { 0x2FA, "_func_2FA" },
    { 0x2FB, "_func_2FB" },
    { 0x2FC, "_func_2FC" },
    { 0x2FD, "_func_2FD" },
    { 0x2FE, "_func_2FE" },
    { 0x2FF, "_func_2FF" },
    { 0x300, "_func_300" },
    { 0x301, "_func_301" },
    { 0x302, "_func_302" },
    { 0x303, "_func_303" },
    { 0x304, "_func_304" },
    { 0x305, "_func_305" },
    { 0x306, "_func_306" },
    { 0x307, "_func_307" },
    { 0x308, "_func_308" },
    { 0x309, "_func_309" },
    { 0x30A, "_func_30A" },
}};

const std::array<std::pair<std::uint16_t, const char*>, 1415> method_list
{{
    { 0x8000, "_meth_8000" },
    { 0x8001, "_meth_8001" },
    { 0x8002, "_meth_8002" },
    { 0x8003, "_meth_8003" },
    { 0x8004, "_meth_8004" },
    { 0x8005, "_meth_8005" },
    { 0x8006, "_meth_8006" },
    { 0x8007, "_meth_8007" },
    { 0x8008, "_meth_8008" },
    { 0x8009, "_meth_8009" },
    { 0x800A, "_meth_800A" },
    { 0x800B, "_meth_800B" },
    { 0x800C, "_meth_800C" },
    { 0x800D, "_meth_800D" },
    { 0x800E, "_meth_800E" },
    { 0x800F, "_meth_800F" },
    { 0x8010, "_meth_8010" },
    { 0x8011, "_meth_8011" },
    { 0x8012, "_meth_8012" },
    { 0x8013, "_meth_8013" },
    { 0x8014, "_meth_8014" },
    { 0x8015, "_meth_8015" },
    { 0x8016, "_meth_8016" },
    { 0x8017, "_meth_8017" },
    { 0x8018, "_meth_8018" },
    { 0x8019, "_meth_8019" },
    { 0x801A, "_meth_801A" },
    { 0x801B, "_meth_801B" },
    { 0x801C, "_meth_801C" },
    { 0x801D, "_meth_801D" },
    { 0x801E, "_meth_801E" },
    { 0x801F, "_meth_801F" },
    { 0x8020, "_meth_8020" },
    { 0x8021, "_meth_8021" },
    { 0x8022, "_meth_8022" },
    { 0x8023, "_meth_8023" },
    { 0x8024, "_meth_8024" },
    { 0x8025, "_meth_8025" },
    { 0x8026, "_meth_8026" },
    { 0x8027, "_meth_8027" },
    { 0x8028, "_meth_8028" },
    { 0x8029, "_meth_8029" },
    { 0x802A, "_meth_802A" },
    { 0x802B, "_meth_802B" },
    { 0x802C, "_meth_802C" },
    { 0x802D, "_meth_802D" },
    { 0x802E, "_meth_802E" },
    { 0x802F, "_meth_802F" },
    { 0x8030, "_meth_8030" },
    { 0x8031, "_meth_8031" },
    { 0x8032, "_meth_8032" },
    { 0x8033, "_meth_8033" },
    { 0x8034, "_meth_8034" },
    { 0x8035, "_meth_8035" },
    { 0x8036, "_meth_8036" },
    { 0x8037, "_meth_8037" },
    { 0x8038, "_meth_8038" },
    { 0x8039, "_meth_8039" },
    { 0x803A, "_meth_803A" },
    { 0x803B, "_meth_803B" },
    { 0x803C, "_meth_803C" },
    { 0x803D, "_meth_803D" },
    { 0x803E, "_meth_803E" },
    { 0x803F, "_meth_803F" },
    { 0x8040, "_meth_8040" },
    { 0x8041, "_meth_8041" },
    { 0x8042, "_meth_8042" },
    { 0x8043, "_meth_8043" },
    { 0x8044, "_meth_8044" },
    { 0x8045, "_meth_8045" },
    { 0x8046, "_meth_8046" },
    { 0x8047, "_meth_8047" },
    { 0x8048, "_meth_8048" },
    { 0x8049, "_meth_8049" },
    { 0x804A, "_meth_804A" },
    { 0x804B, "_meth_804B" },
    { 0x804C, "_meth_804C" },
    { 0x804D, "_meth_804D" },
    { 0x804E, "_meth_804E" },
    { 0x804F, "_meth_804F" },
    { 0x8050, "_meth_8050" },
    { 0x8051, "_meth_8051" },
    { 0x8052, "_meth_8052" },
    { 0x8053, "_meth_8053" },
    { 0x8054, "_meth_8054" },
    { 0x8055, "_meth_8055" },
    { 0x8056, "_meth_8056" },
    { 0x8057, "_meth_8057" },
    { 0x8058, "_meth_8058" },
    { 0x8059, "_meth_8059" },
    { 0x805A, "_meth_805A" },
    { 0x805B, "_meth_805B" },
    { 0x805C, "_meth_805C" },
    { 0x805D, "_meth_805D" },
    { 0x805E, "_meth_805E" },
    { 0x805F, "_meth_805F" },
    { 0x8060, "_meth_8060" },
    { 0x8061, "_meth_8061" },
    { 0x8062, "_meth_8062" },
    { 0x8063, "_meth_8063" },
    { 0x8064, "_meth_8064" },
    { 0x8065, "_meth_8065" },
    { 0x8066, "_meth_8066" },
    { 0x8067, "_meth_8067" },
    { 0x8068, "_meth_8068" },
    { 0x8069, "_meth_8069" },
    { 0x806A, "_meth_806A" },
    { 0x806B, "_meth_806B" },
    { 0x806C, "_meth_806C" },
    { 0x806D, "_meth_806D" },
    { 0x806E, "_meth_806E" },
    { 0x806F, "_meth_806F" },
    { 0x8070, "_meth_8070" },
    { 0x8071, "_meth_8071" },
    { 0x8072, "_meth_8072" },
    { 0x8073, "_meth_8073" },
    { 0x8074, "_meth_8074" },
    { 0x8075, "_meth_8075" },
    { 0x8076, "_meth_8076" },
    { 0x8077, "_meth_8077" },
    { 0x8078, "_meth_8078" },
    { 0x8079, "_meth_8079" },
    { 0x807A, "_meth_807A" },
    { 0x807B, "_meth_807B" },
    { 0x807C, "_meth_807C" },
    { 0x807D, "_meth_807D" },
    { 0x807E, "_meth_807E" },
    { 0x807F, "_meth_807F" },
    { 0x8080, "_meth_8080" },
    { 0x8081, "_meth_8081" },
    { 0x8082, "_meth_8082" },
    { 0x8083, "_meth_8083" },
    { 0x8084, "_meth_8084" },
    { 0x8085, "_meth_8085" },
    { 0x8086, "_meth_8086" },
    { 0x8087, "_meth_8087" },
    { 0x8088, "_meth_8088" },
    { 0x8089, "_meth_8089" },
    { 0x808A, "_meth_808A" },
    { 0x808B, "_meth_808B" },
    { 0x808C, "_meth_808C" },
    { 0x808D, "_meth_808D" },
    { 0x808E, "_meth_808E" },
    { 0x808F, "_meth_808F" },
    { 0x8090, "_meth_8090" },
    { 0x8091, "_meth_8091" },
    { 0x8092, "_meth_8092" },
    { 0x8093, "_meth_8093" },
    { 0x8094, "_meth_8094" },
    { 0x8095, "_meth_8095" },
    { 0x8096, "_meth_8096" },
    { 0x8097, "_meth_8097" },
    { 0x8098, "_meth_8098" },
    { 0x8099, "_meth_8099" },
    { 0x809A, "_meth_809A" },
    { 0x809B, "_meth_809B" },
    { 0x809C, "_meth_809C" },
    { 0x809D, "_meth_809D" },
    { 0x809E, "_meth_809E" },
    { 0x809F, "_meth_809F" },
    { 0x80A0, "_meth_80A0" },
    { 0x80A1, "_meth_80A1" },
    { 0x80A2, "_meth_80A2" },
    { 0x80A3, "_meth_80A3" },
    { 0x80A4, "_meth_80A4" },
    { 0x80A5, "_meth_80A5" },
    { 0x80A6, "_meth_80A6" },
    { 0x80A7, "_meth_80A7" },
    { 0x80A8, "_meth_80A8" },
    { 0x80A9, "_meth_80A9" },
    { 0x80AA, "_meth_80AA" },
    { 0x80AB, "_meth_80AB" },
    { 0x80AC, "_meth_80AC" },
    { 0x80AD, "_meth_80AD" },
    { 0x80AE, "_meth_80AE" },
    { 0x80AF, "_meth_80AF" },
    { 0x80B0, "_meth_80B0" },
    { 0x80B1, "_meth_80B1" },
    { 0x80B2, "delete" },
    { 0x80B3, "_meth_80B3" },
    { 0x80B4, "_meth_80B4" },
    { 0x80B5, "_meth_80B5" },
    { 0x80B6, "_meth_80B6" },
    { 0x80B7, "_meth_80B7" },
    { 0x80B8, "_meth_80B8" },
    { 0x80B9, "_meth_80B9" },
    { 0x80BA, "_meth_80BA" },
    { 0x80BB, "_meth_80BB" },
    { 0x80BC, "_meth_80BC" },
    { 0x80BD, "_meth_80BD" },
    { 0x80BE, "_meth_80BE" },
    { 0x80BF, "_meth_80BF" },
    { 0x80C0, "_meth_80C0" },
    { 0x80C1, "_meth_80C1" },
    { 0x80C2, "_meth_80C2" },
    { 0x80C3, "_meth_80C3" },
    { 0x80C4, "_meth_80C4" },
    { 0x80C5, "_meth_80C5" },
    { 0x80C6, "_meth_80C6" },
    { 0x80C7, "_meth_80C7" },
    { 0x80C8, "_meth_80C8" },
    { 0x80C9, "_meth_80C9" },
    { 0x80CA, "_meth_80CA" },
    { 0x80CB, "_meth_80CB" },
    { 0x80CC, "_meth_80CC" },
    { 0x80CD, "_meth_80CD" },
    { 0x80CE, "_meth_80CE" },
    { 0x80CF, "_meth_80CF" },
    { 0x80D0, "_meth_80D0" },
    { 0x80D1, "_meth_80D1" },
    { 0x80D2, "_meth_80D2" },
    { 0x80D3, "_meth_80D3" },
    { 0x80D4, "_meth_80D4" },
    { 0x80D5, "_meth_80D5" },
    { 0x80D6, "_meth_80D6" },
    { 0x80D7, "_meth_80D7" },
    { 0x80D8, "_meth_80D8" },
    { 0x80D9, "_meth_80D9" },
    { 0x80DA, "_meth_80DA" },
    { 0x80DB, "_meth_80DB" },
    { 0x80DC, "_meth_80DC" },
    { 0x80DD, "_meth_80DD" },
    { 0x80DE, "_meth_80DE" },
    { 0x80DF, "_meth_80DF" },
    { 0x80E0, "_meth_80E0" },
    { 0x80E1, "_meth_80E1" },
    { 0x80E2, "_meth_80E2" },
    { 0x80E3, "_meth_80E3" },
    { 0x80E4, "_meth_80E4" },
    { 0x80E5, "_meth_80E5" },
    { 0x80E6, "_meth_80E6" },
    { 0x80E7, "_meth_80E7" },
    { 0x80E8, "_meth_80E8" },
    { 0x80E9, "_meth_80E9" },
    { 0x80EA, "_meth_80EA" },
    { 0x80EB, "_meth_80EB" },
    { 0x80EC, "_meth_80EC" },
    { 0x80ED, "_meth_80ED" },
    { 0x80EE, "_meth_80EE" },
    { 0x80EF, "_meth_80EF" },
    { 0x80F0, "_meth_80F0" },
    { 0x80F1, "_meth_80F1" },
    { 0x80F2, "_meth_80F2" },
    { 0x80F3, "_meth_80F3" },
    { 0x80F4, "_meth_80F4" },
    { 0x80F5, "_meth_80F5" },
    { 0x80F6, "_meth_80F6" },
    { 0x80F7, "_meth_80F7" },
    { 0x80F8, "_meth_80F8" },
    { 0x80F9, "_meth_80F9" },
    { 0x80FA, "_meth_80FA" },
    { 0x80FB, "_meth_80FB" },
    { 0x80FC, "_meth_80FC" },
    { 0x80FD, "_meth_80FD" },
    { 0x80FE, "_meth_80FE" },
    { 0x80FF, "_meth_80FF" },
    { 0x8100, "_meth_8100" },
    { 0x8101, "_meth_8101" },
    { 0x8102, "_meth_8102" },
    { 0x8103, "_meth_8103" },
    { 0x8104, "_meth_8104" },
    { 0x8105, "_meth_8105" },
    { 0x8106, "_meth_8106" },
    { 0x8107, "_meth_8107" },
    { 0x8108, "_meth_8108" },
    { 0x8109, "_meth_8109" },
    { 0x810A, "_meth_810A" },
    { 0x810B, "_meth_810B" },
    { 0x810C, "_meth_810C" },
    { 0x810D, "_meth_810D" },
    { 0x810E, "_meth_810E" },
    { 0x810F, "_meth_810F" },
    { 0x8110, "_meth_8110" },
    { 0x8111, "_meth_8111" },
    { 0x8112, "_meth_8112" },
    { 0x8113, "_meth_8113" },
    { 0x8114, "_meth_8114" },
    { 0x8115, "_meth_8115" },
    { 0x8116, "_meth_8116" },
    { 0x8117, "_meth_8117" },
    { 0x8118, "_meth_8118" },
    { 0x8119, "_meth_8119" },
    { 0x811A, "_meth_811A" },
    { 0x811B, "_meth_811B" },
    { 0x811C, "_meth_811C" },
    { 0x811D, "_meth_811D" },
    { 0x811E, "_meth_811E" },
    { 0x811F, "_meth_811F" },
    { 0x8120, "_meth_8120" },
    { 0x8121, "_meth_8121" },
    { 0x8122, "_meth_8122" },
    { 0x8123, "_meth_8123" },
    { 0x8124, "_meth_8124" },
    { 0x8125, "_meth_8125" },
    { 0x8126, "_meth_8126" },
    { 0x8127, "_meth_8127" },
    { 0x8128, "_meth_8128" },
    { 0x8129, "_meth_8129" },
    { 0x812A, "_meth_812A" },
    { 0x812B, "_meth_812B" },
    { 0x812C, "_meth_812C" },
    { 0x812D, "_meth_812D" },
    { 0x812E, "_meth_812E" },
    { 0x812F, "_meth_812F" },
    { 0x8130, "_meth_8130" },
    { 0x8131, "_meth_8131" },
    { 0x8132, "_meth_8132" },
    { 0x8133, "_meth_8133" },
    { 0x8134, "_meth_8134" },
    { 0x8135, "_meth_8135" },
    { 0x8136, "_meth_8136" },
    { 0x8137, "_meth_8137" },
    { 0x8138, "_meth_8138" },
    { 0x8139, "_meth_8139" },
    { 0x813A, "_meth_813A" },
    { 0x813B, "_meth_813B" },
    { 0x813C, "_meth_813C" },
    { 0x813D, "_meth_813D" },
    { 0x813E, "_meth_813E" },
    { 0x813F, "_meth_813F" },
    { 0x8140, "_meth_8140" },
    { 0x8141, "_meth_8141" },
    { 0x8142, "_meth_8142" },
    { 0x8143, "_meth_8143" },
    { 0x8144, "_meth_8144" },
    { 0x8145, "_meth_8145" },
    { 0x8146, "_meth_8146" },
    { 0x8147, "_meth_8147" },
    { 0x8148, "_meth_8148" },
    { 0x8149, "_meth_8149" },
    { 0x814A, "_meth_814A" },
    { 0x814B, "_meth_814B" },
    { 0x814C, "_meth_814C" },
    { 0x814D, "_meth_814D" },
    { 0x814E, "_meth_814E" },
    { 0x814F, "_meth_814F" },
    { 0x8150, "_meth_8150" },
    { 0x8151, "_meth_8151" },
    { 0x8152, "_meth_8152" },
    { 0x8153, "_meth_8153" },
    { 0x8154, "_meth_8154" },
    { 0x8155, "_meth_8155" },
    { 0x8156, "_meth_8156" },
    { 0x8157, "_meth_8157" },
    { 0x8158, "_meth_8158" },
    { 0x8159, "_meth_8159" },
    { 0x815A, "_meth_815A" },
    { 0x815B, "_meth_815B" },
    { 0x815C, "_meth_815C" },
    { 0x815D, "_meth_815D" },
    { 0x815E, "_meth_815E" },
    { 0x815F, "_meth_815F" },
    { 0x8160, "_meth_8160" },
    { 0x8161, "_meth_8161" },
    { 0x8162, "_meth_8162" },
    { 0x8163, "_meth_8163" },
    { 0x8164, "_meth_8164" },
    { 0x8165, "_meth_8165" },
    { 0x8166, "_meth_8166" },
    { 0x8167, "_meth_8167" },
    { 0x8168, "_meth_8168" },
    { 0x8169, "_meth_8169" },
    { 0x816A, "_meth_816A" },
    { 0x816B, "_meth_816B" },
    { 0x816C, "_meth_816C" },
    { 0x816D, "_meth_816D" },
    { 0x816E, "_meth_816E" },
    { 0x816F, "_meth_816F" },
    { 0x8170, "_meth_8170" },
    { 0x8171, "_meth_8171" },
    { 0x8172, "_meth_8172" },
    { 0x8173, "_meth_8173" },
    { 0x8174, "_meth_8174" },
    { 0x8175, "_meth_8175" },
    { 0x8176, "_meth_8176" },
    { 0x8177, "_meth_8177" },
    { 0x8178, "_meth_8178" },
    { 0x8179, "_meth_8179" },
    { 0x817A, "_meth_817A" },
    { 0x817B, "_meth_817B" },
    { 0x817C, "_meth_817C" },
    { 0x817D, "_meth_817D" },
    { 0x817E, "_meth_817E" },
    { 0x817F, "_meth_817F" },
    { 0x8180, "_meth_8180" },
    { 0x8181, "_meth_8181" },
    { 0x8182, "_meth_8182" },
    { 0x8183, "_meth_8183" },
    { 0x8184, "_meth_8184" },
    { 0x8185, "_meth_8185" },
    { 0x8186, "_meth_8186" },
    { 0x8187, "_meth_8187" },
    { 0x8188, "_meth_8188" },
    { 0x8189, "_meth_8189" },
    { 0x818A, "_meth_818A" },
    { 0x818B, "_meth_818B" },
    { 0x818C, "_meth_818C" },
    { 0x818D, "_meth_818D" },
    { 0x818E, "_meth_818E" },
    { 0x818F, "_meth_818F" },
    { 0x8190, "_meth_8190" },
    { 0x8191, "_meth_8191" },
    { 0x8192, "_meth_8192" },
    { 0x8193, "_meth_8193" },
    { 0x8194, "_meth_8194" },
    { 0x8195, "_meth_8195" },
    { 0x8196, "_meth_8196" },
    { 0x8197, "_meth_8197" },
    { 0x8198, "_meth_8198" },
    { 0x8199, "_meth_8199" },
    { 0x819A, "_meth_819A" },
    { 0x819B, "_meth_819B" },
    { 0x819C, "_meth_819C" },
    { 0x819D, "_meth_819D" },
    { 0x819E, "_meth_819E" },
    { 0x819F, "_meth_819F" },
    { 0x81A0, "_meth_81A0" },
    { 0x81A1, "_meth_81A1" },
    { 0x81A2, "_meth_81A2" },
    { 0x81A3, "_meth_81A3" },
    { 0x81A4, "_meth_81A4" },
    { 0x81A5, "_meth_81A5" },
    { 0x81A6, "_meth_81A6" },
    { 0x81A7, "_meth_81A7" },
    { 0x81A8, "_meth_81A8" },
    { 0x81A9, "_meth_81A9" },
    { 0x81AA, "_meth_81AA" },
    { 0x81AB, "_meth_81AB" },
    { 0x81AC, "_meth_81AC" },
    { 0x81AD, "_meth_81AD" },
    { 0x81AE, "_meth_81AE" },
    { 0x81AF, "_meth_81AF" },
    { 0x81B0, "_meth_81B0" },
    { 0x81B1, "_meth_81B1" },
    { 0x81B2, "_meth_81B2" },
    { 0x81B3, "_meth_81B3" },
    { 0x81B4, "_meth_81B4" },
    { 0x81B5, "_meth_81B5" },
    { 0x81B6, "_meth_81B6" },
    { 0x81B7, "_meth_81B7" },
    { 0x81B8, "_meth_81B8" },
    { 0x81B9, "_meth_81B9" },
    { 0x81BA, "_meth_81BA" },
    { 0x81BB, "_meth_81BB" },
    { 0x81BC, "_meth_81BC" },
    { 0x81BD, "_meth_81BD" },
    { 0x81BE, "_meth_81BE" },
    { 0x81BF, "_meth_81BF" },
    { 0x81C0, "_meth_81C0" },
    { 0x81C1, "_meth_81C1" },
    { 0x81C2, "_meth_81C2" },
    { 0x81C3, "_meth_81C3" },
    { 0x81C4, "_meth_81C4" },
    { 0x81C5, "_meth_81C5" },
    { 0x81C6, "_meth_81C6" },
    { 0x81C7, "_meth_81C7" },
    { 0x81C8, "_meth_81C8" },
    { 0x81C9, "_meth_81C9" },
    { 0x81CA, "_meth_81CA" },
    { 0x81CB, "_meth_81CB" },
    { 0x81CC, "_meth_81CC" },
    { 0x81CD, "_meth_81CD" },
    { 0x81CE, "_meth_81CE" },
    { 0x81CF, "_meth_81CF" },
    { 0x81D0, "_meth_81D0" },
    { 0x81D1, "_meth_81D1" },
    { 0x81D2, "_meth_81D2" },
    { 0x81D3, "_meth_81D3" },
    { 0x81D4, "_meth_81D4" },
    { 0x81D5, "_meth_81D5" },
    { 0x81D6, "_meth_81D6" },
    { 0x81D7, "_meth_81D7" },
    { 0x81D8, "_meth_81D8" },
    { 0x81D9, "_meth_81D9" },
    { 0x81DA, "_meth_81DA" },
    { 0x81DB, "_meth_81DB" },
    { 0x81DC, "_meth_81DC" },
    { 0x81DD, "_meth_81DD" },
    { 0x81DE, "_meth_81DE" },
    { 0x81DF, "_meth_81DF" },
    { 0x81E0, "_meth_81E0" },
    { 0x81E1, "_meth_81E1" },
    { 0x81E2, "_meth_81E2" },
    { 0x81E3, "_meth_81E3" },
    { 0x81E4, "_meth_81E4" },
    { 0x81E5, "_meth_81E5" },
    { 0x81E6, "_meth_81E6" },
    { 0x81E7, "_meth_81E7" },
    { 0x81E8, "_meth_81E8" },
    { 0x81E9, "_meth_81E9" },
    { 0x81EA, "_meth_81EA" },
    { 0x81EB, "_meth_81EB" },
    { 0x81EC, "_meth_81EC" },
    { 0x81ED, "_meth_81ED" },
    { 0x81EE, "_meth_81EE" },
    { 0x81EF, "_meth_81EF" },
    { 0x81F0, "_meth_81F0" },
    { 0x81F1, "_meth_81F1" },
    { 0x81F2, "_meth_81F2" },
    { 0x81F3, "_meth_81F3" },
    { 0x81F4, "_meth_81F4" },
    { 0x81F5, "_meth_81F5" },
    { 0x81F6, "_meth_81F6" },
    { 0x81F7, "_meth_81F7" },
    { 0x81F8, "_meth_81F8" },
    { 0x81F9, "_meth_81F9" },
    { 0x81FA, "_meth_81FA" },
    { 0x81FB, "_meth_81FB" },
    { 0x81FC, "_meth_81FC" },
    { 0x81FD, "_meth_81FD" },
    { 0x81FE, "_meth_81FE" },
    { 0x81FF, "_meth_81FF" },
    { 0x8200, "_meth_8200" },
    { 0x8201, "_meth_8201" },
    { 0x8202, "_meth_8202" },
    { 0x8203, "_meth_8203" },
    { 0x8204, "_meth_8204" },
    { 0x8205, "_meth_8205" },
    { 0x8206, "_meth_8206" },
    { 0x8207, "_meth_8207" },
    { 0x8208, "_meth_8208" },
    { 0x8209, "_meth_8209" },
    { 0x820A, "_meth_820A" },
    { 0x820B, "_meth_820B" },
    { 0x820C, "_meth_820C" },
    { 0x820D, "_meth_820D" },
    { 0x820E, "_meth_820E" },
    { 0x820F, "_meth_820F" },
    { 0x8210, "_meth_8210" },
    { 0x8211, "_meth_8211" },
    { 0x8212, "_meth_8212" },
    { 0x8213, "_meth_8213" },
    { 0x8214, "_meth_8214" },
    { 0x8215, "_meth_8215" },
    { 0x8216, "_meth_8216" },
    { 0x8217, "_meth_8217" },
    { 0x8218, "_meth_8218" },
    { 0x8219, "_meth_8219" },
    { 0x821A, "_meth_821A" },
    { 0x821B, "_meth_821B" },
    { 0x821C, "_meth_821C" },
    { 0x821D, "_meth_821D" },
    { 0x821E, "_meth_821E" },
    { 0x821F, "_meth_821F" },
    { 0x8220, "_meth_8220" },
    { 0x8221, "_meth_8221" },
    { 0x8222, "_meth_8222" },
    { 0x8223, "_meth_8223" },
    { 0x8224, "_meth_8224" },
    { 0x8225, "_meth_8225" },
    { 0x8226, "_meth_8226" },
    { 0x8227, "_meth_8227" },
    { 0x8228, "_meth_8228" },
    { 0x8229, "_meth_8229" },
    { 0x822A, "_meth_822A" },
    { 0x822B, "_meth_822B" },
    { 0x822C, "_meth_822C" },
    { 0x822D, "_meth_822D" },
    { 0x822E, "_meth_822E" },
    { 0x822F, "_meth_822F" },
    { 0x8230, "_meth_8230" },
    { 0x8231, "_meth_8231" },
    { 0x8232, "_meth_8232" },
    { 0x8233, "_meth_8233" },
    { 0x8234, "_meth_8234" },
    { 0x8235, "_meth_8235" },
    { 0x8236, "_meth_8236" },
    { 0x8237, "_meth_8237" },
    { 0x8238, "_meth_8238" },
    { 0x8239, "_meth_8239" },
    { 0x823A, "_meth_823A" },
    { 0x823B, "_meth_823B" },
    { 0x823C, "_meth_823C" },
    { 0x823D, "_meth_823D" },
    { 0x823E, "_meth_823E" },
    { 0x823F, "_meth_823F" },
    { 0x8240, "_meth_8240" },
    { 0x8241, "_meth_8241" },
    { 0x8242, "_meth_8242" },
    { 0x8243, "_meth_8243" },
    { 0x8244, "_meth_8244" },
    { 0x8245, "_meth_8245" },
    { 0x8246, "_meth_8246" },
    { 0x8247, "_meth_8247" },
    { 0x8248, "_meth_8248" },
    { 0x8249, "_meth_8249" },
    { 0x824A, "_meth_824A" },
    { 0x824B, "_meth_824B" },
    { 0x824C, "_meth_824C" },
    { 0x824D, "_meth_824D" },
    { 0x824E, "_meth_824E" },
    { 0x824F, "_meth_824F" },
    { 0x8250, "_meth_8250" },
    { 0x8251, "_meth_8251" },
    { 0x8252, "_meth_8252" },
    { 0x8253, "_meth_8253" },
    { 0x8254, "_meth_8254" },
    { 0x8255, "_meth_8255" },
    { 0x8256, "_meth_8256" },
    { 0x8257, "_meth_8257" },
    { 0x8258, "_meth_8258" },
    { 0x8259, "_meth_8259" },
    { 0x825A, "_meth_825A" },
    { 0x825B, "_meth_825B" },
    { 0x825C, "_meth_825C" },
    { 0x825D, "_meth_825D" },
    { 0x825E, "_meth_825E" },
    { 0x825F, "_meth_825F" },
    { 0x8260, "_meth_8260" },
    { 0x8261, "_meth_8261" },
    { 0x8262, "_meth_8262" },
    { 0x8263, "_meth_8263" },
    { 0x8264, "_meth_8264" },
    { 0x8265, "_meth_8265" },
    { 0x8266, "_meth_8266" },
    { 0x8267, "_meth_8267" },
    { 0x8268, "_meth_8268" },
    { 0x8269, "_meth_8269" },
    { 0x826A, "_meth_826A" },
    { 0x826B, "_meth_826B" },
    { 0x826C, "_meth_826C" },
    { 0x826D, "_meth_826D" },
    { 0x826E, "_meth_826E" },
    { 0x826F, "_meth_826F" },
    { 0x8270, "_meth_8270" },
    { 0x8271, "_meth_8271" },
    { 0x8272, "_meth_8272" },
    { 0x8273, "_meth_8273" },
    { 0x8274, "_meth_8274" },
    { 0x8275, "_meth_8275" },
    { 0x8276, "_meth_8276" },
    { 0x8277, "_meth_8277" },
    { 0x8278, "_meth_8278" },
    { 0x8279, "_meth_8279" },
    { 0x827A, "_meth_827A" },
    { 0x827B, "_meth_827B" },
    { 0x827C, "_meth_827C" },
    { 0x827D, "_meth_827D" },
    { 0x827E, "_meth_827E" },
    { 0x827F, "_meth_827F" },
    { 0x8280, "_meth_8280" },
    { 0x8281, "_meth_8281" },
    { 0x8282, "_meth_8282" },
    { 0x8283, "_meth_8283" },
    { 0x8284, "_meth_8284" },
    { 0x8285, "_meth_8285" },
    { 0x8286, "_meth_8286" },
    { 0x8287, "_meth_8287" },
    { 0x8288, "_meth_8288" },
    { 0x8289, "_meth_8289" },
    { 0x828A, "_meth_828A" },
    { 0x828B, "_meth_828B" },
    { 0x828C, "_meth_828C" },
    { 0x828D, "_meth_828D" },
    { 0x828E, "_meth_828E" },
    { 0x828F, "_meth_828F" },
    { 0x8290, "_meth_8290" },
    { 0x8291, "_meth_8291" },
    { 0x8292, "_meth_8292" },
    { 0x8293, "_meth_8293" },
    { 0x8294, "_meth_8294" },
    { 0x8295, "_meth_8295" },
    { 0x8296, "_meth_8296" },
    { 0x8297, "_meth_8297" },
    { 0x8298, "_meth_8298" },
    { 0x8299, "_meth_8299" },
    { 0x829A, "_meth_829A" },
    { 0x829B, "_meth_829B" },
    { 0x829C, "_meth_829C" },
    { 0x829D, "_meth_829D" },
    { 0x829E, "_meth_829E" },
    { 0x829F, "_meth_829F" },
    { 0x82A0, "_meth_82A0" },
    { 0x82A1, "_meth_82A1" },
    { 0x82A2, "_meth_82A2" },
    { 0x82A3, "_meth_82A3" },
    { 0x82A4, "_meth_82A4" },
    { 0x82A5, "_meth_82A5" },
    { 0x82A6, "_meth_82A6" },
    { 0x82A7, "_meth_82A7" },
    { 0x82A8, "_meth_82A8" },
    { 0x82A9, "_meth_82A9" },
    { 0x82AA, "_meth_82AA" },
    { 0x82AB, "_meth_82AB" },
    { 0x82AC, "_meth_82AC" },
    { 0x82AD, "_meth_82AD" },
    { 0x82AE, "_meth_82AE" },
    { 0x82AF, "_meth_82AF" },
    { 0x82B0, "_meth_82B0" },
    { 0x82B1, "_meth_82B1" },
    { 0x82B2, "_meth_82B2" },
    { 0x82B3, "_meth_82B3" },
    { 0x82B4, "_meth_82B4" },
    { 0x82B5, "_meth_82B5" },
    { 0x82B6, "_meth_82B6" },
    { 0x82B7, "_meth_82B7" },
    { 0x82B8, "_meth_82B8" },
    { 0x82B9, "_meth_82B9" },
    { 0x82BA, "_meth_82BA" },
    { 0x82BB, "_meth_82BB" },
    { 0x82BC, "_meth_82BC" },
    { 0x82BD, "_meth_82BD" },
    { 0x82BE, "_meth_82BE" },
    { 0x82BF, "_meth_82BF" },
    { 0x82C0, "_meth_82C0" },
    { 0x82C1, "_meth_82C1" },
    { 0x82C2, "_meth_82C2" },
    { 0x82C3, "_meth_82C3" },
    { 0x82C4, "_meth_82C4" },
    { 0x82C5, "_meth_82C5" },
    { 0x82C6, "_meth_82C6" },
    { 0x82C7, "_meth_82C7" },
    { 0x82C8, "_meth_82C8" },
    { 0x82C9, "_meth_82C9" },
    { 0x82CA, "_meth_82CA" },
    { 0x82CB, "_meth_82CB" },
    { 0x82CC, "_meth_82CC" },
    { 0x82CD, "_meth_82CD" },
    { 0x82CE, "_meth_82CE" },
    { 0x82CF, "_meth_82CF" },
    { 0x82D0, "_meth_82D0" },
    { 0x82D1, "_meth_82D1" },
    { 0x82D2, "_meth_82D2" },
    { 0x82D3, "_meth_82D3" },
    { 0x82D4, "_meth_82D4" },
    { 0x82D5, "_meth_82D5" },
    { 0x82D6, "_meth_82D6" },
    { 0x82D7, "_meth_82D7" },
    { 0x82D8, "_meth_82D8" },
    { 0x82D9, "_meth_82D9" },
    { 0x82DA, "_meth_82DA" },
    { 0x82DB, "_meth_82DB" },
    { 0x82DC, "_meth_82DC" },
    { 0x82DD, "_meth_82DD" },
    { 0x82DE, "_meth_82DE" },
    { 0x82DF, "_meth_82DF" },
    { 0x82E0, "_meth_82E0" },
    { 0x82E1, "_meth_82E1" },
    { 0x82E2, "_meth_82E2" },
    { 0x82E3, "_meth_82E3" },
    { 0x82E4, "_meth_82E4" },
    { 0x82E5, "_meth_82E5" },
    { 0x82E6, "_meth_82E6" },
    { 0x82E7, "_meth_82E7" },
    { 0x82E8, "_meth_82E8" },
    { 0x82E9, "_meth_82E9" },
    { 0x82EA, "_meth_82EA" },
    { 0x82EB, "_meth_82EB" },
    { 0x82EC, "_meth_82EC" },
    { 0x82ED, "_meth_82ED" },
    { 0x82EE, "_meth_82EE" },
    { 0x82EF, "_meth_82EF" },
    { 0x82F0, "_meth_82F0" },
    { 0x82F1, "_meth_82F1" },
    { 0x82F2, "_meth_82F2" },
    { 0x82F3, "_meth_82F3" },
    { 0x82F4, "_meth_82F4" },
    { 0x82F5, "_meth_82F5" },
    { 0x82F6, "_meth_82F6" },
    { 0x82F7, "_meth_82F7" },
    { 0x82F8, "_meth_82F8" },
    { 0x82F9, "_meth_82F9" },
    { 0x82FA, "_meth_82FA" },
    { 0x82FB, "_meth_82FB" },
    { 0x82FC, "_meth_82FC" },
    { 0x82FD, "_meth_82FD" },
    { 0x82FE, "_meth_82FE" },
    { 0x82FF, "_meth_82FF" },
    { 0x8300, "_meth_8300" },
    { 0x8301, "_meth_8301" },
    { 0x8302, "_meth_8302" },
    { 0x8303, "_meth_8303" },
    { 0x8304, "_meth_8304" },
    { 0x8305, "_meth_8305" },
    { 0x8306, "_meth_8306" },
    { 0x8307, "_meth_8307" },
    { 0x8308, "_meth_8308" },
    { 0x8309, "_meth_8309" },
    { 0x830A, "_meth_830A" },
    { 0x830B, "_meth_830B" },
    { 0x830C, "_meth_830C" },
    { 0x830D, "_meth_830D" },
    { 0x830E, "_meth_830E" },
    { 0x830F, "_meth_830F" },
    { 0x8310, "_meth_8310" },
    { 0x8311, "_meth_8311" },
    { 0x8312, "_meth_8312" },
    { 0x8313, "_meth_8313" },
    { 0x8314, "_meth_8314" },
    { 0x8315, "_meth_8315" },
    { 0x8316, "_meth_8316" },
    { 0x8317, "_meth_8317" },
    { 0x8318, "_meth_8318" },
    { 0x8319, "_meth_8319" },
    { 0x831A, "_meth_831A" },
    { 0x831B, "_meth_831B" },
    { 0x831C, "_meth_831C" },
    { 0x831D, "_meth_831D" },
    { 0x831E, "_meth_831E" },
    { 0x831F, "_meth_831F" },
    { 0x8320, "_meth_8320" },
    { 0x8321, "_meth_8321" },
    { 0x8322, "_meth_8322" },
    { 0x8323, "_meth_8323" },
    { 0x8324, "_meth_8324" },
    { 0x8325, "_meth_8325" },
    { 0x8326, "_meth_8326" },
    { 0x8327, "_meth_8327" },
    { 0x8328, "_meth_8328" },
    { 0x8329, "_meth_8329" },
    { 0x832A, "_meth_832A" },
    { 0x832B, "_meth_832B" },
    { 0x832C, "_meth_832C" },
    { 0x832D, "_meth_832D" },
    { 0x832E, "_meth_832E" },
    { 0x832F, "_meth_832F" },
    { 0x8330, "_meth_8330" },
    { 0x8331, "_meth_8331" },
    { 0x8332, "_meth_8332" },
    { 0x8333, "_meth_8333" },
    { 0x8334, "_meth_8334" },
    { 0x8335, "_meth_8335" },
    { 0x8336, "_meth_8336" },
    { 0x8337, "_meth_8337" },
    { 0x8338, "_meth_8338" },
    { 0x8339, "_meth_8339" },
    { 0x833A, "_meth_833A" },
    { 0x833B, "_meth_833B" },
    { 0x833C, "_meth_833C" },
    { 0x833D, "_meth_833D" },
    { 0x833E, "_meth_833E" },
    { 0x833F, "_meth_833F" },
    { 0x8340, "_meth_8340" },
    { 0x8341, "_meth_8341" },
    { 0x8342, "_meth_8342" },
    { 0x8343, "_meth_8343" },
    { 0x8344, "_meth_8344" },
    { 0x8345, "_meth_8345" },
    { 0x8346, "_meth_8346" },
    { 0x8347, "_meth_8347" },
    { 0x8348, "_meth_8348" },
    { 0x8349, "_meth_8349" },
    { 0x834A, "_meth_834A" },
    { 0x834B, "_meth_834B" },
    { 0x834C, "_meth_834C" },
    { 0x834D, "_meth_834D" },
    { 0x834E, "_meth_834E" },
    { 0x834F, "_meth_834F" },
    { 0x8350, "_meth_8350" },
    { 0x8351, "_meth_8351" },
    { 0x8352, "_meth_8352" },
    { 0x8353, "_meth_8353" },
    { 0x8354, "_meth_8354" },
    { 0x8355, "_meth_8355" },
    { 0x8356, "_meth_8356" },
    { 0x8357, "_meth_8357" },
    { 0x8358, "_meth_8358" },
    { 0x8359, "_meth_8359" },
    { 0x835A, "_meth_835A" },
    { 0x835B, "_meth_835B" },
    { 0x835C, "_meth_835C" },
    { 0x835D, "_meth_835D" },
    { 0x835E, "_meth_835E" },
    { 0x835F, "_meth_835F" },
    { 0x8360, "_meth_8360" },
    { 0x8361, "_meth_8361" },
    { 0x8362, "_meth_8362" },
    { 0x8363, "_meth_8363" },
    { 0x8364, "_meth_8364" },
    { 0x8365, "_meth_8365" },
    { 0x8366, "_meth_8366" },
    { 0x8367, "_meth_8367" },
    { 0x8368, "_meth_8368" },
    { 0x8369, "_meth_8369" },
    { 0x836A, "_meth_836A" },
    { 0x836B, "_meth_836B" },
    { 0x836C, "_meth_836C" },
    { 0x836D, "_meth_836D" },
    { 0x836E, "_meth_836E" },
    { 0x836F, "_meth_836F" },
    { 0x8370, "_meth_8370" },
    { 0x8371, "_meth_8371" },
    { 0x8372, "_meth_8372" },
    { 0x8373, "_meth_8373" },
    { 0x8374, "_meth_8374" },
    { 0x8375, "_meth_8375" },
    { 0x8376, "_meth_8376" },
    { 0x8377, "_meth_8377" },
    { 0x8378, "_meth_8378" },
    { 0x8379, "_meth_8379" },
    { 0x837A, "_meth_837A" },
    { 0x837B, "_meth_837B" },
    { 0x837C, "_meth_837C" },
    { 0x837D, "_meth_837D" },
    { 0x837E, "_meth_837E" },
    { 0x837F, "_meth_837F" },
    { 0x8380, "_meth_8380" },
    { 0x8381, "_meth_8381" },
    { 0x8382, "_meth_8382" },
    { 0x8383, "_meth_8383" },
    { 0x8384, "_meth_8384" },
    { 0x8385, "_meth_8385" },
    { 0x8386, "_meth_8386" },
    { 0x8387, "_meth_8387" },
    { 0x8388, "_meth_8388" },
    { 0x8389, "_meth_8389" },
    { 0x838A, "_meth_838A" },
    { 0x838B, "_meth_838B" },
    { 0x838C, "_meth_838C" },
    { 0x838D, "_meth_838D" },
    { 0x838E, "_meth_838E" },
    { 0x838F, "_meth_838F" },
    { 0x8390, "_meth_8390" },
    { 0x8391, "_meth_8391" },
    { 0x8392, "_meth_8392" },
    { 0x8393, "_meth_8393" },
    { 0x8394, "_meth_8394" },
    { 0x8395, "_meth_8395" },
    { 0x8396, "_meth_8396" },
    { 0x8397, "_meth_8397" },
    { 0x8398, "_meth_8398" },
    { 0x8399, "_meth_8399" },
    { 0x839A, "_meth_839A" },
    { 0x839B, "_meth_839B" },
    { 0x839C, "_meth_839C" },
    { 0x839D, "_meth_839D" },
    { 0x839E, "_meth_839E" },
    { 0x839F, "_meth_839F" },
    { 0x83A0, "_meth_83A0" },
    { 0x83A1, "_meth_83A1" },
    { 0x83A2, "_meth_83A2" },
    { 0x83A3, "_meth_83A3" },
    { 0x83A4, "_meth_83A4" },
    { 0x83A5, "_meth_83A5" },
    { 0x83A6, "_meth_83A6" },
    { 0x83A7, "_meth_83A7" },
    { 0x83A8, "_meth_83A8" },
    { 0x83A9, "_meth_83A9" },
    { 0x83AA, "_meth_83AA" },
    { 0x83AB, "_meth_83AB" },
    { 0x83AC, "_meth_83AC" },
    { 0x83AD, "_meth_83AD" },
    { 0x83AE, "_meth_83AE" },
    { 0x83AF, "_meth_83AF" },
    { 0x83B0, "_meth_83B0" },
    { 0x83B1, "_meth_83B1" },
    { 0x83B2, "_meth_83B2" },
    { 0x83B3, "_meth_83B3" },
    { 0x83B4, "_meth_83B4" },
    { 0x83B5, "_meth_83B5" },
    { 0x83B6, "_meth_83B6" },
    { 0x83B7, "_meth_83B7" },
    { 0x83B8, "_meth_83B8" },
    { 0x83B9, "_meth_83B9" },
    { 0x83BA, "_meth_83BA" },
    { 0x83BB, "_meth_83BB" },
    { 0x83BC, "_meth_83BC" },
    { 0x83BD, "_meth_83BD" },
    { 0x83BE, "_meth_83BE" },
    { 0x83BF, "_meth_83BF" },
    { 0x83C0, "_meth_83C0" },
    { 0x83C1, "_meth_83C1" },
    { 0x83C2, "_meth_83C2" },
    { 0x83C3, "_meth_83C3" },
    { 0x83C4, "_meth_83C4" },
    { 0x83C5, "_meth_83C5" },
    { 0x83C6, "_meth_83C6" },
    { 0x83C7, "_meth_83C7" },
    { 0x83C8, "_meth_83C8" },
    { 0x83C9, "_meth_83C9" },
    { 0x83CA, "_meth_83CA" },
    { 0x83CB, "_meth_83CB" },
    { 0x83CC, "_meth_83CC" },
    { 0x83CD, "_meth_83CD" },
    { 0x83CE, "_meth_83CE" },
    { 0x83CF, "_meth_83CF" },
    { 0x83D0, "_meth_83D0" },
    { 0x83D1, "_meth_83D1" },
    { 0x83D2, "_meth_83D2" },
    { 0x83D3, "_meth_83D3" },
    { 0x83D4, "_meth_83D4" },
    { 0x83D5, "_meth_83D5" },
    { 0x83D6, "_meth_83D6" },
    { 0x83D7, "_meth_83D7" },
    { 0x83D8, "_meth_83D8" },
    { 0x83D9, "_meth_83D9" },
    { 0x83DA, "_meth_83DA" },
    { 0x83DB, "_meth_83DB" },
    { 0x83DC, "_meth_83DC" },
    { 0x83DD, "_meth_83DD" },
    { 0x83DE, "_meth_83DE" },
    { 0x83DF, "_meth_83DF" },
    { 0x83E0, "_meth_83E0" },
    { 0x83E1, "_meth_83E1" },
    { 0x83E2, "_meth_83E2" },
    { 0x83E3, "_meth_83E3" },
    { 0x83E4, "_meth_83E4" },
    { 0x83E5, "_meth_83E5" },
    { 0x83E6, "_meth_83E6" },
    { 0x83E7, "_meth_83E7" },
    { 0x83E8, "_meth_83E8" },
    { 0x83E9, "_meth_83E9" },
    { 0x83EA, "_meth_83EA" },
    { 0x83EB, "_meth_83EB" },
    { 0x83EC, "_meth_83EC" },
    { 0x83ED, "_meth_83ED" },
    { 0x83EE, "_meth_83EE" },
    { 0x83EF, "_meth_83EF" },
    { 0x83F0, "_meth_83F0" },
    { 0x83F1, "_meth_83F1" },
    { 0x83F2, "_meth_83F2" },
    { 0x83F3, "_meth_83F3" },
    { 0x83F4, "_meth_83F4" },
    { 0x83F5, "_meth_83F5" },
    { 0x83F6, "_meth_83F6" },
    { 0x83F7, "_meth_83F7" },
    { 0x83F8, "_meth_83F8" },
    { 0x83F9, "_meth_83F9" },
    { 0x83FA, "_meth_83FA" },
    { 0x83FB, "_meth_83FB" },
    { 0x83FC, "_meth_83FC" },
    { 0x83FD, "_meth_83FD" },
    { 0x83FE, "_meth_83FE" },
    { 0x83FF, "_meth_83FF" },
    { 0x8400, "_meth_8400" },
    { 0x8401, "_meth_8401" },
    { 0x8402, "_meth_8402" },
    { 0x8403, "_meth_8403" },
    { 0x8404, "_meth_8404" },
    { 0x8405, "_meth_8405" },
    { 0x8406, "_meth_8406" },
    { 0x8407, "_meth_8407" },
    { 0x8408, "_meth_8408" },
    { 0x8409, "_meth_8409" },
    { 0x840A, "_meth_840A" },
    { 0x840B, "_meth_840B" },
    { 0x840C, "_meth_840C" },
    { 0x840D, "_meth_840D" },
    { 0x840E, "_meth_840E" },
    { 0x840F, "_meth_840F" },
    { 0x8410, "_meth_8410" },
    { 0x8411, "_meth_8411" },
    { 0x8412, "_meth_8412" },
    { 0x8413, "_meth_8413" },
    { 0x8414, "_meth_8414" },
    { 0x8415, "_meth_8415" },
    { 0x8416, "_meth_8416" },
    { 0x8417, "_meth_8417" },
    { 0x8418, "_meth_8418" },
    { 0x8419, "_meth_8419" },
    { 0x841A, "_meth_841A" },
    { 0x841B, "_meth_841B" },
    { 0x841C, "_meth_841C" },
    { 0x841D, "_meth_841D" },
    { 0x841E, "_meth_841E" },
    { 0x841F, "_meth_841F" },
    { 0x8420, "_meth_8420" },
    { 0x8421, "_meth_8421" },
    { 0x8422, "_meth_8422" },
    { 0x8423, "_meth_8423" },
    { 0x8424, "_meth_8424" },
    { 0x8425, "_meth_8425" },
    { 0x8426, "_meth_8426" },
    { 0x8427, "_meth_8427" },
    { 0x8428, "_meth_8428" },
    { 0x8429, "_meth_8429" },
    { 0x842A, "_meth_842A" },
    { 0x842B, "_meth_842B" },
    { 0x842C, "_meth_842C" },
    { 0x842D, "_meth_842D" },
    { 0x842E, "_meth_842E" },
    { 0x842F, "_meth_842F" },
    { 0x8430, "_meth_8430" },
    { 0x8431, "_meth_8431" },
    { 0x8432, "_meth_8432" },
    { 0x8433, "_meth_8433" },
    { 0x8434, "_meth_8434" },
    { 0x8435, "_meth_8435" },
    { 0x8436, "_meth_8436" },
    { 0x8437, "_meth_8437" },
    { 0x8438, "_meth_8438" },
    { 0x8439, "_meth_8439" },
    { 0x843A, "_meth_843A" },
    { 0x843B, "_meth_843B" },
    { 0x843C, "_meth_843C" },
    { 0x843D, "_meth_843D" },
    { 0x843E, "_meth_843E" },
    { 0x843F, "_meth_843F" },
    { 0x8440, "_meth_8440" },
    { 0x8441, "_meth_8441" },
    { 0x8442, "_meth_8442" },
    { 0x8443, "_meth_8443" },
    { 0x8444, "_meth_8444" },
    { 0x8445, "_meth_8445" },
    { 0x8446, "_meth_8446" },
    { 0x8447, "_meth_8447" },
    { 0x8448, "_meth_8448" },
    { 0x8449, "_meth_8449" },
    { 0x844A, "_meth_844A" },
    { 0x844B, "_meth_844B" },
    { 0x844C, "_meth_844C" },
    { 0x844D, "_meth_844D" },
    { 0x844E, "_meth_844E" },
    { 0x844F, "_meth_844F" },
    { 0x8450, "_meth_8450" },
    { 0x8451, "_meth_8451" },
    { 0x8452, "_meth_8452" },
    { 0x8453, "_meth_8453" },
    { 0x8454, "_meth_8454" },
    { 0x8455, "_meth_8455" },
    { 0x8456, "_meth_8456" },
    { 0x8457, "_meth_8457" },
    { 0x8458, "_meth_8458" },
    { 0x8459, "_meth_8459" },
    { 0x845A, "_meth_845A" },
    { 0x845B, "_meth_845B" },
    { 0x845C, "_meth_845C" },
    { 0x845D, "_meth_845D" },
    { 0x845E, "_meth_845E" },
    { 0x845F, "_meth_845F" },
    { 0x8460, "_meth_8460" },
    { 0x8461, "_meth_8461" },
    { 0x8462, "_meth_8462" },
    { 0x8463, "_meth_8463" },
    { 0x8464, "_meth_8464" },
    { 0x8465, "_meth_8465" },
    { 0x8466, "_meth_8466" },
    { 0x8467, "_meth_8467" },
    { 0x8468, "_meth_8468" },
    { 0x8469, "_meth_8469" },
    { 0x846A, "_meth_846A" },
    { 0x846B, "_meth_846B" },
    { 0x846C, "_meth_846C" },
    { 0x846D, "_meth_846D" },
    { 0x846E, "_meth_846E" },
    { 0x846F, "_meth_846F" },
    { 0x8470, "_meth_8470" },
    { 0x8471, "_meth_8471" },
    { 0x8472, "_meth_8472" },
    { 0x8473, "_meth_8473" },
    { 0x8474, "_meth_8474" },
    { 0x8475, "_meth_8475" },
    { 0x8476, "_meth_8476" },
    { 0x8477, "_meth_8477" },
    { 0x8478, "_meth_8478" },
    { 0x8479, "_meth_8479" },
    { 0x847A, "_meth_847A" },
    { 0x847B, "_meth_847B" },
    { 0x847C, "_meth_847C" },
    { 0x847D, "_meth_847D" },
    { 0x847E, "_meth_847E" },
    { 0x847F, "_meth_847F" },
    { 0x8480, "_meth_8480" },
    { 0x8481, "_meth_8481" },
    { 0x8482, "_meth_8482" },
    { 0x8483, "_meth_8483" },
    { 0x8484, "_meth_8484" },
    { 0x8485, "_meth_8485" },
    { 0x8486, "_meth_8486" },
    { 0x8487, "_meth_8487" },
    { 0x8488, "_meth_8488" },
    { 0x8489, "_meth_8489" },
    { 0x848A, "_meth_848A" },
    { 0x848B, "_meth_848B" },
    { 0x848C, "_meth_848C" },
    { 0x848D, "_meth_848D" },
    { 0x848E, "_meth_848E" },
    { 0x848F, "_meth_848F" },
    { 0x8490, "_meth_8490" },
    { 0x8491, "_meth_8491" },
    { 0x8492, "_meth_8492" },
    { 0x8493, "_meth_8493" },
    { 0x8494, "_meth_8494" },
    { 0x8495, "_meth_8495" },
    { 0x8496, "_meth_8496" },
    { 0x8497, "_meth_8497" },
    { 0x8498, "_meth_8498" },
    { 0x8499, "_meth_8499" },
    { 0x849A, "_meth_849A" },
    { 0x849B, "_meth_849B" },
    { 0x849C, "_meth_849C" },
    { 0x849D, "_meth_849D" },
    { 0x849E, "_meth_849E" },
    { 0x849F, "_meth_849F" },
    { 0x84A0, "_meth_84A0" },
    { 0x84A1, "_meth_84A1" },
    { 0x84A2, "_meth_84A2" },
    { 0x84A3, "_meth_84A3" },
    { 0x84A4, "_meth_84A4" },
    { 0x84A5, "_meth_84A5" },
    { 0x84A6, "_meth_84A6" },
    { 0x84A7, "_meth_84A7" },
    { 0x84A8, "_meth_84A8" },
    { 0x84A9, "_meth_84A9" },
    { 0x84AA, "_meth_84AA" },
    { 0x84AB, "_meth_84AB" },
    { 0x84AC, "_meth_84AC" },
    { 0x84AD, "_meth_84AD" },
    { 0x84AE, "_meth_84AE" },
    { 0x84AF, "_meth_84AF" },
    { 0x84B0, "_meth_84B0" },
    { 0x84B1, "_meth_84B1" },
    { 0x84B2, "_meth_84B2" },
    { 0x84B3, "_meth_84B3" },
    { 0x84B4, "_meth_84B4" },
    { 0x84B5, "_meth_84B5" },
    { 0x84B6, "_meth_84B6" },
    { 0x84B7, "_meth_84B7" },
    { 0x84B8, "_meth_84B8" },
    { 0x84B9, "_meth_84B9" },
    { 0x84BA, "_meth_84BA" },
    { 0x84BB, "_meth_84BB" },
    { 0x84BC, "_meth_84BC" },
    { 0x84BD, "_meth_84BD" },
    { 0x84BE, "_meth_84BE" },
    { 0x84BF, "_meth_84BF" },
    { 0x84C0, "_meth_84C0" },
    { 0x84C1, "_meth_84C1" },
    { 0x84C2, "_meth_84C2" },
    { 0x84C3, "_meth_84C3" },
    { 0x84C4, "_meth_84C4" },
    { 0x84C5, "_meth_84C5" },
    { 0x84C6, "_meth_84C6" },
    { 0x84C7, "_meth_84C7" },
    { 0x84C8, "_meth_84C8" },
    { 0x84C9, "_meth_84C9" },
    { 0x84CA, "_meth_84CA" },
    { 0x84CB, "_meth_84CB" },
    { 0x84CC, "_meth_84CC" },
    { 0x84CD, "_meth_84CD" },
    { 0x84CE, "_meth_84CE" },
    { 0x84CF, "_meth_84CF" },
    { 0x84D0, "_meth_84D0" },
    { 0x84D1, "_meth_84D1" },
    { 0x84D2, "_meth_84D2" },
    { 0x84D3, "_meth_84D3" },
    { 0x84D4, "_meth_84D4" },
    { 0x84D5, "_meth_84D5" },
    { 0x84D6, "_meth_84D6" },
    { 0x84D7, "_meth_84D7" },
    { 0x84D8, "_meth_84D8" },
    { 0x84D9, "_meth_84D9" },
    { 0x84DA, "_meth_84DA" },
    { 0x84DB, "_meth_84DB" },
    { 0x84DC, "_meth_84DC" },
    { 0x84DD, "_meth_84DD" },
    { 0x84DE, "_meth_84DE" },
    { 0x84DF, "_meth_84DF" },
    { 0x84E0, "_meth_84E0" },
    { 0x84E1, "_meth_84E1" },
    { 0x84E2, "_meth_84E2" },
    { 0x84E3, "_meth_84E3" },
    { 0x84E4, "_meth_84E4" },
    { 0x84E5, "_meth_84E5" },
    { 0x84E6, "_meth_84E6" },
    { 0x84E7, "_meth_84E7" },
    { 0x84E8, "_meth_84E8" },
    { 0x84E9, "_meth_84E9" },
    { 0x84EA, "_meth_84EA" },
    { 0x84EB, "_meth_84EB" },
    { 0x84EC, "_meth_84EC" },
    { 0x84ED, "_meth_84ED" },
    { 0x84EE, "_meth_84EE" },
    { 0x84EF, "_meth_84EF" },
    { 0x84F0, "_meth_84F0" },
    { 0x84F1, "_meth_84F1" },
    { 0x84F2, "_meth_84F2" },
    { 0x84F3, "_meth_84F3" },
    { 0x84F4, "_meth_84F4" },
    { 0x84F5, "_meth_84F5" },
    { 0x84F6, "_meth_84F6" },
    { 0x84F7, "_meth_84F7" },
    { 0x84F8, "_meth_84F8" },
    { 0x84F9, "_meth_84F9" },
    { 0x84FA, "_meth_84FA" },
    { 0x84FB, "_meth_84FB" },
    { 0x84FC, "_meth_84FC" },
    { 0x84FD, "_meth_84FD" },
    { 0x84FE, "_meth_84FE" },
    { 0x84FF, "_meth_84FF" },
    { 0x8500, "_meth_8500" },
    { 0x8501, "_meth_8501" },
    { 0x8502, "_meth_8502" },
    { 0x8503, "_meth_8503" },
    { 0x8504, "_meth_8504" },
    { 0x8505, "_meth_8505" },
    { 0x8506, "_meth_8506" },
    { 0x8507, "_meth_8507" },
    { 0x8508, "_meth_8508" },
    { 0x8509, "_meth_8509" },
    { 0x850A, "_meth_850A" },
    { 0x850B, "_meth_850B" },
    { 0x850C, "_meth_850C" },
    { 0x850D, "_meth_850D" },
    { 0x850E, "_meth_850E" },
    { 0x850F, "_meth_850F" },
    { 0x8510, "_meth_8510" },
    { 0x8511, "_meth_8511" },
    { 0x8512, "_meth_8512" },
    { 0x8513, "_meth_8513" },
    { 0x8514, "_meth_8514" },
    { 0x8515, "_meth_8515" },
    { 0x8516, "_meth_8516" },
    { 0x8517, "_meth_8517" },
    { 0x8518, "_meth_8518" },
    { 0x8519, "_meth_8519" },
    { 0x851A, "_meth_851A" },
    { 0x851B, "_meth_851B" },
    { 0x851C, "_meth_851C" },
    { 0x851D, "_meth_851D" },
    { 0x851E, "_meth_851E" },
    { 0x851F, "_meth_851F" },
    { 0x8520, "_meth_8520" },
    { 0x8521, "_meth_8521" },
    { 0x8522, "_meth_8522" },
    { 0x8523, "_meth_8523" },
    { 0x8524, "_meth_8524" },
    { 0x8525, "_meth_8525" },
    { 0x8526, "_meth_8526" },
    { 0x8527, "_meth_8527" },
    { 0x8528, "_meth_8528" },
    { 0x8529, "_meth_8529" },
    { 0x852A, "_meth_852A" },
    { 0x852B, "_meth_852B" },
    { 0x852C, "_meth_852C" },
    { 0x852D, "_meth_852D" },
    { 0x852E, "_meth_852E" },
    { 0x852F, "_meth_852F" },
    { 0x8530, "_meth_8530" },
    { 0x8531, "_meth_8531" },
    { 0x8532, "_meth_8532" },
    { 0x8533, "_meth_8533" },
    { 0x8534, "_meth_8534" },
    { 0x8535, "_meth_8535" },
    { 0x8536, "_meth_8536" },
    { 0x8537, "_meth_8537" },
    { 0x8538, "_meth_8538" },
    { 0x8539, "_meth_8539" },
    { 0x853A, "_meth_853A" },
    { 0x853B, "_meth_853B" },
    { 0x853C, "_meth_853C" },
    { 0x853D, "_meth_853D" },
    { 0x853E, "_meth_853E" },
    { 0x853F, "_meth_853F" },
    { 0x8540, "_meth_8540" },
    { 0x8541, "_meth_8541" },
    { 0x8542, "_meth_8542" },
    { 0x8543, "_meth_8543" },
    { 0x8544, "_meth_8544" },
    { 0x8545, "_meth_8545" },
    { 0x8546, "_meth_8546" },
    { 0x8547, "_meth_8547" },
    { 0x8548, "_meth_8548" },
    { 0x8549, "_meth_8549" },
    { 0x854A, "_meth_854A" },
    { 0x854B, "_meth_854B" },
    { 0x854C, "_meth_854C" },
    { 0x854D, "_meth_854D" },
    { 0x854E, "_meth_854E" },
    { 0x854F, "_meth_854F" },
    { 0x8550, "_meth_8550" },
    { 0x8551, "_meth_8551" },
    { 0x8552, "_meth_8552" },
    { 0x8553, "_meth_8553" },
    { 0x8554, "_meth_8554" },
    { 0x8555, "_meth_8555" },
    { 0x8556, "_meth_8556" },
    { 0x8557, "_meth_8557" },
    { 0x8558, "_meth_8558" },
    { 0x8559, "_meth_8559" },
    { 0x855A, "_meth_855A" },
    { 0x855B, "_meth_855B" },
    { 0x855C, "_meth_855C" },
    { 0x855D, "_meth_855D" },
    { 0x855E, "_meth_855E" },
    { 0x855F, "_meth_855F" },
    { 0x8560, "_meth_8560" },
    { 0x8561, "_meth_8561" },
    { 0x8562, "_meth_8562" },
    { 0x8563, "_meth_8563" },
    { 0x8564, "_meth_8564" },
    { 0x8565, "_meth_8565" },
    { 0x8566, "_meth_8566" },
    { 0x8567, "_meth_8567" },
    { 0x8568, "_meth_8568" },
    { 0x8569, "_meth_8569" },
    { 0x856A, "_meth_856A" },
    { 0x856B, "_meth_856B" },
    { 0x856C, "_meth_856C" },
    { 0x856D, "_meth_856D" },
    { 0x856E, "_meth_856E" },
    { 0x856F, "_meth_856F" },
    { 0x8570, "_meth_8570" },
    { 0x8571, "_meth_8571" },
    { 0x8572, "_meth_8572" },
    { 0x8573, "_meth_8573" },
    { 0x8574, "_meth_8574" },
    { 0x8575, "_meth_8575" },
    { 0x8576, "_meth_8576" },
    { 0x8577, "_meth_8577" },
    { 0x8578, "_meth_8578" },
    { 0x8579, "_meth_8579" },
    { 0x857A, "_meth_857A" },
    { 0x857B, "_meth_857B" },
    { 0x857C, "_meth_857C" },
    { 0x857D, "_meth_857D" },
    { 0x857E, "_meth_857E" },
    { 0x857F, "_meth_857F" },
    { 0x8580, "_meth_8580" },
    { 0x8581, "_meth_8581" },
    { 0x8582, "_meth_8582" },
    { 0x8583, "_meth_8583" },
    { 0x8584, "_meth_8584" },
    { 0x8585, "_meth_8585" },
    { 0x8586, "_meth_8586" },
}};

const std::array<std::pair<std::uint16_t, const char*>, 804> token_list
{{
    { 0x0000, "" },
    { 0x0001, "pl#" },
    { 0x0002, "-" },
    { 0x0003, "radius`" },
    { 0x0004, "note:" },
    { 0x0005, "_" },
    { 0x0006, "_custom" },
    { 0x0007, "a" },
    { 0x0008, "ability" },
    { 0x0009, "accumulate" },
    { 0x000A, "accuracy" },
    { 0x000B, "actionslot1" },
    { 0x000C, "actionslot2" },
    { 0x000D, "actionslot3" },
    { 0x000E, "actionslot4" },
    { 0x000F, "actionslot5" },
    { 0x0010, "actionslot6" },
    { 0x0011, "actionslot7" },
    { 0x0012, "actionslot8" },
    { 0x0013, "activator" },
    { 0x0014, "active" },
    { 0x0015, "activecostume" },
    { 0x0016, "activeemblemslot" },
    { 0x0017, "activesquadmember" },
    { 0x0018, "activevisionset" },
    { 0x0019, "activevisionsetduration" },
    { 0x001A, "agent" },
    { 0x001B, "agenthealth" },
    { 0x001C, "agentname" },
    { 0x001D, "agentteam" },
    { 0x001E, "ai_event" },
    { 0x001F, "ai_sight_line_cycle_group" },
    { 0x0020, "ai_sight_line_group" },
    { 0x0021, "aim_highest_bone" },
    { 0x0022, "aim_vis_bone" },
    { 0x0023, "aiSpread" },
    { 0x0024, "aisquadmembers" },
    { 0x0025, "alert" },
    { 0x0026, "alertlevel" },
    { 0x0027, "alertlevelint" },
    { 0x0028, "alien" },
    { 0x0029, "alienplayerloadout" },
    { 0x002A, "alienplayerstats" },
    { 0x002B, "aliensession" },
    { 0x002C, "alignx" },
    { 0x002D, "aligny" },
    { 0x002E, "all" },
    { 0x002F, "allies" },
    { 0x0030, "allowcrouch" },
    { 0x0031, "allowdeath" },
    { 0x0032, "allowjump" },
    { 0x0033, "allowladders" },
    { 0x0034, "allowpain" },
    { 0x0035, "allowprone" },
    { 0x0036, "allstreaksrestricted" },
    { 0x0037, "alpha" },
    { 0x0038, "altmode" },
    { 0x0039, "always" },
    { 0x003A, "ambient" },
    { 0x003B, "ambienttrack" },
    { 0x003C, "ambienttrack_ac130" },
    { 0x003D, "ambush" },
    { 0x003E, "ambush_nodes_only" },
    { 0x003F, "angle_deltas" },
    { 0x0040, "anglelerprate" },
    { 0x0041, "angles" },
    { 0x0042, "anim_angle_delta" },
    { 0x0043, "anim_deltas" },
    { 0x0044, "anim_pose" },
    { 0x0045, "anim_will_finish" },
    { 0x0046, "animation" },
    { 0x0047, "animscript" },
    { 0x0048, "archived" },
    { 0x0049, "archivetime" },
    { 0x004A, "armor" },
    { 0x004B, "asleep" },
    { 0x004C, "aspectratio" },
    { 0x004D, "assaultstreaks" },
    { 0x004E, "assignedbucket" },
    { 0x004F, "assists" },
    { 0x0050, "attachment" },
    { 0x0051, "attachmentclassrestricted" },
    { 0x0052, "attachmentrestricted" },
    { 0x0053, "attachments" },
    { 0x0054, "attachtag" },
    { 0x0055, "attacker" },
    { 0x0056, "attackeraccuracy" },
    { 0x0057, "attackercount" },
    { 0x0058, "attackerisjuggernaut" },
    { 0x0059, "attackerpos" },
    { 0x005A, "author" },
    { 0x005B, "auto_ai" },
    { 0x005C, "auto_change" },
    { 0x005D, "auto_nonai" },
    { 0x005E, "avoidanceboundshalfsize" },
    { 0x005F, "awards" },
    { 0x0060, "axis" },
    { 0x0061, "b" },
    { 0x0062, "back" },
    { 0x0063, "back_left" },
    { 0x0064, "back_low" },
    { 0x0065, "back_mid" },
    { 0x0066, "back_right" },
    { 0x0067, "back_up" },
    { 0x0068, "background" },
    { 0x0069, "bad_guys" },
    { 0x006A, "bad_path" },
    { 0x006B, "badplaceawareness" },
    { 0x006C, "ball_off" },
    { 0x006D, "ball_on" },
    { 0x006E, "ball_pass" },
    { 0x006F, "bandwidthdown" },
    { 0x0070, "bandwidthtestcount" },
    { 0x0071, "bandwidthup" },
    { 0x0072, "baselineoverflow_max" },
    { 0x0073, "baselineoverflow_worst" },
    { 0x0074, "battery_discharge_begin" },
    { 0x0075, "battery_discharge_end" },
    { 0x0076, "begin" },
    { 0x0077, "begin_custom_anim" },
    { 0x0078, "begin_firing" },
    { 0x0079, "begin_firing_left" },
    { 0x007A, "bestweapon" },
    { 0x007B, "bestweaponindex" },
    { 0x007C, "bipods" },
    { 0x007D, "birthtime" },
    { 0x007E, "bl_rotor1" },
    { 0x007F, "bl_rotor2" },
    { 0x0080, "bl_rotor3" },
    { 0x0081, "blackops2prestige" },
    { 0x0082, "blackops2rank" },
    { 0x0083, "blade_hide" },
    { 0x0084, "blade_show" },
    { 0x0085, "blockfriendlies" },
    { 0x0086, "blurradius" },
    { 0x0087, "body" },
    { 0x0088, "body_animate_jnt" },
    { 0x0089, "bottomarc" },
    { 0x008A, "br_rotor1" },
    { 0x008B, "br_rotor2" },
    { 0x008C, "br_rotor3" },
    { 0x008D, "breadcrumbheader" },
    { 0x008E, "buff" },
    { 0x008F, "bullet_hitshield" },
    { 0x0090, "bullethit" },
    { 0x0091, "bulletwhizby" },
    { 0x0092, "c" },
    { 0x0093, "callingcardindex" },
    { 0x0094, "camo" },
    { 0x0095, "cancel_location" },
    { 0x0096, "canclimbladders" },
    { 0x0097, "canjumppath" },
    { 0x0098, "cardicon" },
    { 0x0099, "cardnameplate" },
    { 0x009A, "cardtitle" },
    { 0x009B, "cgmchecksum" },
    { 0x009C, "ch_prestige" },
    { 0x009D, "ch_prestige_max" },
    { 0x009E, "chainfallback" },
    { 0x009F, "chainnode" },
    { 0x00A0, "challengeprogress" },
    { 0x00A1, "challengestate" },
    { 0x00A2, "chest" },
    { 0x00A3, "churnscores" },
    { 0x00A4, "chyron_message1" },
    { 0x00A5, "chyron_message2" },
    { 0x00A6, "chyron_message3" },
    { 0x00A7, "civilian" },
    { 0x00A8, "clanidhigh" },
    { 0x00A9, "clanidlow" },
    { 0x00AA, "classname" },
    { 0x00AB, "clipdistance" },
    { 0x00AC, "code_classname" },
    { 0x00AD, "code_damageradius" },
    { 0x00AE, "code_move" },
    { 0x00AF, "code_move_slide" },
    { 0x00B0, "codecallback_agentadded" },
    { 0x00B1, "codecallback_agentdamaged" },
    { 0x00B2, "codecallback_agentkilled" },
    { 0x00B3, "codecallback_bullethitentity" },
    { 0x00B4, "codecallback_codeendgame" },
    { 0x00B5, "codecallback_entitydamage" },
    { 0x00B6, "codecallback_entityoutofworld" },
    { 0x00B7, "codecallback_handleinstantmessage" },
    { 0x00B8, "codecallback_hostmigration" },
    { 0x00B9, "codecallback_leaderdialog" },
    { 0x00BA, "codecallback_partymembers" },
    { 0x00BB, "codecallback_playerconnect" },
    { 0x00BC, "codecallback_playerdamage" },
    { 0x00BD, "codecallback_playerdisconnect" },
    { 0x00BE, "codecallback_playergrenadesuicide" },
    { 0x00BF, "codecallback_playerkilled" },
    { 0x00C0, "codecallback_playerlaststand" },
    { 0x00C1, "codecallback_playermigrated" },
    { 0x00C2, "codecallback_startgametype" },
    { 0x00C3, "codecallback_vehicledamage" }, // 195
//
    { 0x00C4, "color" },
    { 0x00C5, "color_blind_toggled" },
    { 0x00C6, "combat" },
    { 0x00C7, "combatmode" },
    { 0x00C8, "combatrecord" },
    { 0x00C9, "commonoption" },
    { 0x00CA, "confirm_location" },
    { 0x00CB, "connection_id" },
    { 0x00CC, "connectionidchunkhigh" },
    { 0x00CD, "connectionidchunklow" },
    { 0x00CE, "consolegame" },
    { 0x00CF, "consoleidchunkhigh" },
    { 0x00D0, "consoleidchunklow" },
    { 0x00D1, "constrained" },
    { 0x00D2, "contact" },
    { 0x00D3, "contextleanenabled" },
    { 0x00D4, "convergencetime" },
    { 0x00D5, "coopactivesquadmember" },
    { 0x00D6, "coopsquadmembers" },
    { 0x00D7, "costumes" },
    { 0x00D8, "count" },
    { 0x00D9, "cover" },
    { 0x00DA, "cover_approach" },
    { 0x00DB, "coversearchinterval" },
    { 0x00DC, "createstruct" },

    { 0x0208, "init" },
    { 0x0209, "initstructs" },

    { 0x0267, "main" },

    { 0x53D, "codescripts/delete" },
    { 0x53E, "codescripts/struct" },
    { 0x53F, "codescripts/message" },
    { 0x540, "maps/mp/gametypes/_callbacksetup" },

// S1 stuff
    { 0xA4D6, "character/character_sp_usmc_at4" },
    { 0xA4D7, "character/character_sp_usmc_james" },
    { 0xA4D8, "character/character_sp_usmc_ryan" },
    { 0xA4D9, "character/character_sp_usmc_sami" },
    { 0xA4DA, "character/character_sp_usmc_sami_goggles" },
    { 0xA4DB, "character/character_sp_usmc_zach" },
    { 0xA4DC, "character/character_sp_usmc_zach_goggles" },
    { 0xA4DD, "character/character_us_marine_ar" },
    { 0xA4DE, "character/character_us_marine_ar_lowlod" },
    { 0xA4DF, "character/character_us_marine_dress" },
    { 0xA4E0, "character/character_us_marine_dress_a" },
    { 0xA4E1, "character/character_us_marine_dress_b" },
    { 0xA4E2, "character/character_us_marine_dress_c" },
    { 0xA4E3, "character/character_us_marine_dress_d" },
    { 0xA4E4, "character/character_us_marine_dress_e" },
    { 0xA4E5, "character/character_us_marine_dress_f" },
    { 0xA4E6, "character/character_us_marine_dress_lowlod" },
    { 0xA4E7, "character/character_us_marine_seofob_ar" },
    { 0xA4E8, "character/character_us_marine_shotgun_lowlod" },
    { 0xA4E9, "character/character_us_marine_smg" },
    { 0xA4EA, "character/character_us_marine_smg_lowlod" },
    { 0xA4EB, "character/character_us_marine_smg_seo" },
    { 0xA4EC, "character/character_us_marine_smg_seointro" },
    { 0xA4ED, "character/mp_character_cloak_test" },
    { 0xA4EE, "character/mp_character_sentinel" },
    { 0xA4EF, "codescripts/character" },
    { 0xA4F0, "common_scripts/_artcommon" },
    { 0xA4F1, "common_scripts/_bcs_location_trigs" },
    { 0xA4F2, "common_scripts/_createfx" },
    { 0xA4F3, "common_scripts/_createfxmenu" },
    { 0xA4F4, "common_scripts/_destructible" },
    { 0xA4F5, "common_scripts/_dynamic_world" },
    { 0xA4F6, "common_scripts/_elevator" },
    { 0xA4F7, "common_scripts/_exploder" },
    { 0xA4F8, "common_scripts/_fx" },
    { 0xA4F9, "common_scripts/_pipes" },
    { 0xA4FA, "common_scripts/utility" },
    { 0xA4FB, "destructible_scripts/computer_01_destp" },
    { 0xA4FC, "destructible_scripts/container_plastic_72x56x48_01_destp" },
    { 0xA4FD, "destructible_scripts/container_plastic_beige_med_01_destp" },
    { 0xA4FE, "destructible_scripts/greece_spinning_displays" },
    { 0xA4FF, "destructible_scripts/powerbox_112x64_01_green_destp" },
    { 0xA500, "destructible_scripts/security_camera_scanner_destp" },
    { 0xA501, "destructible_scripts/toy_chicken" },
    { 0xA502, "destructible_scripts/toy_chicken_common" },
    { 0xA503, "destructible_scripts/toy_electricbox4" },
    { 0xA504, "destructible_scripts/toy_generator" },
    { 0xA505, "destructible_scripts/toy_generator_on" },
    { 0xA506, "destructible_scripts/toy_locker_double" },
    { 0xA507, "destructible_scripts/vehicle_civ_domestic_sedan_01_glass" },
    { 0xA508, "destructible_scripts/vehicle_civ_domestic_sedan_police_destpv" },
    { 0xA509, "destructible_scripts/vehicle_civ_domestic_sedan_taxi_glass" },
    { 0xA50A, "destructible_scripts/vehicle_civ_smartcar_destpv" },
    { 0xA50B, "destructible_scripts/vehicle_luxurysedan" },
    { 0xA50C, "destructible_scripts/vehicle_luxurysedan_2008" },
    { 0xA50D, "destructible_scripts/vehicle_pickup" },
    { 0xA50E, "destructible_scripts/vehicle_suv_atlas_destpv" },
    { 0xA50F, "destructible_scripts/wall_firebox_destp" },
    { 0xA510, "maps/_anim" },
    { 0xA511, "maps/_animatedmodels" },
    { 0xA512, "maps/_ar_view" },
    { 0xA513, "maps/_art" },
    { 0xA514, "maps/_autosave" },
    { 0xA515, "maps/_bobbing_boats" },
    { 0xA516, "maps/_breach" },
    { 0xA517, "maps/_car_door_shield" },
    { 0xA518, "maps/_cg_encounter_perf_monitor" },
    { 0xA519, "maps/_chargeable_weapon" },
    { 0xA51A, "maps/_cloak" },
    { 0xA51B, "maps/_cloak_enemy_behavior" },
    { 0xA51C, "maps/_colors" },
    { 0xA51D, "maps/_compass" },
    { 0xA51E, "maps/_controlled_orbiting_drone" },
    { 0xA51F, "maps/_controlled_sniperdrone" },
    { 0xA520, "maps/_coop" },
    { 0xA521, "maps/_createfx" },
    { 0xA522, "maps/_credits" },
    { 0xA523, "maps/_credits_autogen" },
    { 0xA524, "maps/_damagefeedback" },
    { 0xA525, "maps/_dds" },
    { 0xA526, "maps/_debug" },
    { 0xA527, "maps/_deployablecoverai" },
    { 0xA528, "maps/_detonategrenades" },
    { 0xA529, "maps/_dog_control" },
    { 0xA52A, "maps/_dog_kinect" },
    { 0xA52B, "maps/_drone" },
    { 0xA52C, "maps/_drone_ai" },
    { 0xA52D, "maps/_drone_base" },
    { 0xA52E, "maps/_drone_civilian" },
    { 0xA52F, "maps/_dshk_player" },
    { 0xA530, "maps/_endmission" },
    { 0xA531, "maps/_exo_climb" },
    { 0xA532, "maps/_exo_punch_door" },
    { 0xA533, "maps/_exo_shield_sp" },
    { 0xA534, "maps/_flashlight_cheap" },
    { 0xA535, "maps/_foam_bomb" },
    { 0xA536, "maps/_friendlyfire" },
    { 0xA537, "maps/_gameskill" },
    { 0xA538, "maps/_global_fx" },
    { 0xA539, "maps/_global_fx_code" },
    { 0xA53A, "maps/_grapple" },
    { 0xA53B, "maps/_grapple_anim" },
    { 0xA53C, "maps/_grapple_traverse" },
    { 0xA53D, "maps/_hand_signals" },
    { 0xA53E, "maps/_helicopter_ai" },
    { 0xA53F, "maps/_helicopter_globals" },
    { 0xA540, "maps/_high_speed_clouds" },
    { 0xA541, "maps/_hms_ai_utility" },
    { 0xA542, "maps/_hms_door_interact" },
    { 0xA543, "maps/_hms_greece_civilian" },
    { 0xA544, "maps/_hms_utility" },
    { 0xA545, "maps/_hud" },
    { 0xA546, "maps/_hud_util" },
    { 0xA547, "maps/_idle" },
    { 0xA548, "maps/_idle_phone" },
    { 0xA549, "maps/_idle_smoke" },
    { 0xA54A, "maps/_intelligence" },
    { 0xA54B, "maps/_introscreen" },
    { 0xA54C, "maps/_inventory" },
    { 0xA54D, "maps/_juggernaut" },
    { 0xA54E, "maps/_lighting" },
    { 0xA54F, "maps/_lights" },
    { 0xA550, "maps/_load" },
    { 0xA551, "maps/_loadout" },
    { 0xA552, "maps/_loadout_code" },
    { 0xA553, "maps/_mark_and_execute" },
    { 0xA554, "maps/_mech" },
    { 0xA555, "maps/_mech_aud" },
    { 0xA556, "maps/_mech_grapple" },
    { 0xA557, "maps/_mg_penetration" },
    { 0xA558, "maps/_mgturret" },
    { 0xA559, "maps/_mgturret_auto_nonai" },
    { 0xA55A, "maps/_microdronelauncher" },
    { 0xA55B, "maps/_microwave_grenade" },
    { 0xA55C, "maps/_mocap_ar" },
    { 0xA55D, "maps/_names" },
    { 0xA55E, "maps/_nightvision" },
    { 0xA55F, "maps/_patrol" },
    { 0xA560, "maps/_patrol_anims" },
    { 0xA561, "maps/_patrol_anims_active" },
    { 0xA562, "maps/_patrol_anims_casualkiller" },
    { 0xA563, "maps/_patrol_anims_creepwalk" },
    { 0xA564, "maps/_patrol_anims_patroljog" },
    { 0xA565, "maps/_patrol_cold_anims" },
    { 0xA566, "maps/_patrol_extended" },
    { 0xA567, "maps/_player_boost_dash" },
    { 0xA568, "maps/_player_boost_jump_anims" },
    { 0xA569, "maps/_player_boost_jump_aud" },
    { 0xA56A, "maps/_player_death" },
    { 0xA56B, "maps/_player_exo" },
    { 0xA56C, "maps/_player_fastzip" },
    { 0xA56D, "maps/_player_high_jump" },
    { 0xA56E, "maps/_player_land_assist" },
    { 0xA56F, "maps/_player_stats" },
    { 0xA570, "maps/_playermech_code" },
    { 0xA571, "maps/_pmove" },
    { 0xA572, "maps/_president" },
    { 0xA573, "maps/_props" },
    { 0xA574, "maps/_rambo" },
    { 0xA575, "maps/_riotshield" },
    { 0xA576, "maps/_sarray" },
    { 0xA577, "maps/_shg_anim" },
    { 0xA578, "maps/_shg_debug" },
    { 0xA579, "maps/_shg_design_tools" },
    { 0xA57A, "maps/_shg_fx" },
    { 0xA57B, "maps/_shg_utility" },
    { 0xA57C, "maps/_slowmo_breach" },
    { 0xA57D, "maps/_sniper_glint" },
    { 0xA57E, "maps/_sniper_setup_ai" },
    { 0xA57F, "maps/_sonicaoe" },
    { 0xA580, "maps/_sp_matchdata" },
    { 0xA581, "maps/_spawner" },
    { 0xA582, "maps/_stealth" },
    { 0xA583, "maps/_stealth_accuracy_friendly" },
    { 0xA584, "maps/_stealth_animation_funcs" },
    { 0xA585, "maps/_stealth_anims" },
    { 0xA586, "maps/_stealth_behavior_enemy" },
    { 0xA587, "maps/_stealth_behavior_friendly" },
    { 0xA588, "maps/_stealth_behavior_system" },
    { 0xA589, "maps/_stealth_color_friendly" },
    { 0xA58A, "maps/_stealth_corpse_enemy" },
    { 0xA58B, "maps/_stealth_corpse_system" },
    { 0xA58C, "maps/_stealth_debug" },
    { 0xA58D, "maps/_stealth_display" },
    { 0xA58E, "maps/_stealth_event_enemy" },
    { 0xA58F, "maps/_stealth_shared_utilities" },
    { 0xA590, "maps/_stealth_smartstance_friendly" },
    { 0xA591, "maps/_stealth_threat_enemy" },
    { 0xA592, "maps/_stealth_utility" },
    { 0xA593, "maps/_stealth_visibility_enemy" },
    { 0xA594, "maps/_stealth_visibility_friendly" },
    { 0xA595, "maps/_stealth_visibility_system" },
    { 0xA596, "maps/_stingerm7" },
    { 0xA597, "maps/_stingerm7_greece" },
    { 0xA598, "maps/_swim_ai" },
    { 0xA599, "maps/_swim_ai_common" },
    { 0xA59A, "maps/_swim_player" },
    { 0xA59B, "maps/_tagging" },
    { 0xA59C, "maps/_target_lock" },
    { 0xA59D, "maps/_treadfx" },
    { 0xA59E, "maps/_trigger" },
    { 0xA59F, "maps/_underwater" },
    { 0xA5A0, "maps/_upgrade_challenge" },
    { 0xA5A1, "maps/_upgrade_perks" },
    { 0xA5A2, "maps/_upgrade_system" },
    { 0xA5A3, "maps/_urgent_walk" },
    { 0xA5A4, "maps/_utility" },
    { 0xA5A5, "maps/_utility_code" },
    { 0xA5A6, "maps/_utility_dogs" },
    { 0xA5A7, "maps/_variable_grenade" },
    { 0xA5A8, "maps/_vehicle" },
    { 0xA5A9, "maps/_vehicle_aianim" },
    { 0xA5AA, "maps/_vehicle_code" },
    { 0xA5AB, "maps/_vehicle_free_drive" },
    { 0xA5AC, "maps/_vehicle_missile" },
    { 0xA5AD, "maps/_vehicle_shg" },
    { 0xA5AE, "maps/_vehicle_traffic" },
    { 0xA5AF, "maps/_vignette_util" },
    { 0xA5B0, "maps/_warzone_tactics" },
    { 0xA5B1, "maps/_water" },
    { 0xA5B2, "maps/_weapon_pdrone" },
    { 0xA5B3, "maps/_weather" },
    { 0xA5B4, "maps/betrayal_fx" },
    { 0xA5B5, "maps/betrayal_precache" },
    { 0xA5B6, "maps/captured_fx" },
    { 0xA5B7, "maps/captured_precache" },
    { 0xA5B8, "maps/crash_fx" },
    { 0xA5B9, "maps/crash_precache" },
    { 0xA5BA, "maps/credits_s1_fx" },
    { 0xA5BB, "maps/credits_s1_precache" },
    { 0xA5BC, "maps/detroit_fx" },
    { 0xA5BD, "maps/detroit_precache" },
    { 0xA5BE, "maps/df_baghdad_fx" },
    { 0xA5BF, "maps/df_baghdad_precache" },
    { 0xA5C0, "maps/df_fly_fx" },
    { 0xA5C1, "maps/df_fly_precache" },
    { 0xA5C2, "maps/finale_fx" },
    { 0xA5C3, "maps/finale_precache" },
    { 0xA5C4, "maps/fusion_fx" },
    { 0xA5C5, "maps/fusion_precache" },
    { 0xA5C6, "maps/greece_conf_center_fx" },
    { 0xA5C7, "maps/greece_ending_fx" },
    { 0xA5C8, "maps/greece_fx" },
    { 0xA5C9, "maps/greece_precache" },
    { 0xA5CA, "maps/greece_safehouse_fx" },
    { 0xA5CB, "maps/greece_sniper_scramble_fx" },
    { 0xA5CC, "maps/irons_estate_fx" },
    { 0xA5CD, "maps/irons_estate_precache" },
    { 0xA5CE, "maps/lab_fx" },
    { 0xA5CF, "maps/lab_precache" },
    { 0xA5D0, "maps/lagos_fx" },
    { 0xA5D1, "maps/lagos_precache" },
    { 0xA5D2, "maps/recovery_fx" },
    { 0xA5D3, "maps/recovery_precache" },
    { 0xA5D4, "maps/sanfran_b_fx" },
    { 0xA5D5, "maps/sanfran_b_precache" },
    { 0xA5D6, "maps/sanfran_fx" },
    { 0xA5D7, "maps/sanfran_precache" },
    { 0xA5D8, "maps/seoul_fx" },
    { 0xA5D9, "maps/seoul_precache" },
    { 0xA5DA, "mptype/mptype_cloak_test" },
    { 0xA5DB, "soundscripts/_ambient" },
    { 0xA5DC, "soundscripts/_audio" },
    { 0xA5DD, "soundscripts/_audio_dynamic_ambi" },
    { 0xA5DE, "soundscripts/_audio_mix_manager" },
    { 0xA5DF, "soundscripts/_audio_music" },
    { 0xA5E0, "soundscripts/_audio_presets_music" },
    { 0xA5E1, "soundscripts/_audio_presets_vehicles" },
    { 0xA5E2, "soundscripts/_audio_reverb" },
    { 0xA5E3, "soundscripts/_audio_stream_manager" },
    { 0xA5E4, "soundscripts/_audio_vehicle_manager" },
    { 0xA5E5, "soundscripts/_audio_vehicles" },
    { 0xA5E6, "soundscripts/_audio_whizby" },
    { 0xA5E7, "soundscripts/_audio_zone_manager" },
    { 0xA5E8, "soundscripts/_snd" },
    { 0xA5E9, "soundscripts/_snd_common" },
    { 0xA5EA, "soundscripts/_snd_debug_bayless" },
    { 0xA5EB, "soundscripts/_snd_debug_bina" },
    { 0xA5EC, "soundscripts/_snd_debug_blondin" },
    { 0xA5ED, "soundscripts/_snd_debug_caisley" },
    { 0xA5EE, "soundscripts/_snd_debug_gavazza" },
    { 0xA5EF, "soundscripts/_snd_debug_kilborn" },
    { 0xA5F0, "soundscripts/_snd_debug_loperfido" },
    { 0xA5F1, "soundscripts/_snd_debug_mcsweeney" },
    { 0xA5F2, "soundscripts/_snd_debug_mika" },
    { 0xA5F3, "soundscripts/_snd_debug_naas" },
    { 0xA5F4, "soundscripts/_snd_debug_nuniyants" },
    { 0xA5F5, "soundscripts/_snd_debug_swenson" },
    { 0xA5F6, "soundscripts/_snd_debug_veca" },
    { 0xA5F7, "soundscripts/_snd_filters" },
    { 0xA5F8, "soundscripts/_snd_foley" },
    { 0xA5F9, "soundscripts/_snd_hud" },
    { 0xA5FA, "soundscripts/_snd_pcap" },
    { 0xA5FB, "soundscripts/_snd_playsound" },
    { 0xA5FC, "soundscripts/_snd_timescale" },
    { 0xA5FD, "soundscripts/so_aud" },
    { 0xA5FE, "vehicle_scripts/_atlas_jet" },
    { 0xA5FF, "vehicle_scripts/_atlas_piranha" },
    { 0xA600, "vehicle_scripts/_atlas_suv" },
    { 0xA601, "vehicle_scripts/_atlas_van" },
    { 0xA602, "vehicle_scripts/_attack_drone" },
    { 0xA603, "vehicle_scripts/_attack_drone_aud" },
    { 0xA604, "vehicle_scripts/_attack_drone_common" },
    { 0xA605, "vehicle_scripts/_attack_drone_controllable" },
    { 0xA606, "vehicle_scripts/_attack_drone_individual" },
    { 0xA607, "vehicle_scripts/_attack_drone_kamikaze" },
    { 0xA608, "vehicle_scripts/_attack_drone_queen" },
    { 0xA609, "vehicle_scripts/_attack_heli" },
    { 0xA60A, "vehicle_scripts/_chinese_brave_warrior" },
    { 0xA60B, "vehicle_scripts/_civ_boat" },
    { 0xA60C, "vehicle_scripts/_civ_boxtruck_ai" },
    { 0xA60D, "vehicle_scripts/_civ_domestic_bus" },
    { 0xA60E, "vehicle_scripts/_civ_domestic_economy_ai" },
    { 0xA60F, "vehicle_scripts/_civ_domestic_minivan" },
    { 0xA610, "vehicle_scripts/_civ_domestic_sedan_01" },
    { 0xA611, "vehicle_scripts/_civ_domestic_sedan_police" },
    { 0xA612, "vehicle_scripts/_civ_domestic_sedan_taxi_01" },
    { 0xA613, "vehicle_scripts/_civ_domestic_sportscar_01" },
    { 0xA614, "vehicle_scripts/_civ_domestic_suv" },
    { 0xA615, "vehicle_scripts/_civ_domestic_truck" },
    { 0xA616, "vehicle_scripts/_civ_full_size_pickup_01_ai" },
    { 0xA617, "vehicle_scripts/_civ_full_size_technical" },
    { 0xA618, "vehicle_scripts/_civ_pickup_truck_01" },
    { 0xA619, "vehicle_scripts/_civ_smartcar" },
    { 0xA61A, "vehicle_scripts/_civ_workvan" },
    { 0xA61B, "vehicle_scripts/_cover_drone" },
    { 0xA61C, "vehicle_scripts/_cover_drone_aud" },
    { 0xA61D, "vehicle_scripts/_diveboat" },
    { 0xA61E, "vehicle_scripts/_diveboat_aud" },
    { 0xA61F, "vehicle_scripts/_empty" },
    { 0xA620, "vehicle_scripts/_ft101_tank" },
    { 0xA621, "vehicle_scripts/_gaz" },
    { 0xA622, "vehicle_scripts/_gaz_dshk" },
    { 0xA623, "vehicle_scripts/_gaz_dshk_aud" },
    { 0xA624, "vehicle_scripts/_generic_script_model_lagos" },
    { 0xA625, "vehicle_scripts/_havoc_missile_scripted" },
    { 0xA626, "vehicle_scripts/_hovertank" },
    { 0xA627, "vehicle_scripts/_hovertank_aud" },
    { 0xA628, "vehicle_scripts/_ind_semi_truck_fuel_tanker" },
    { 0xA629, "vehicle_scripts/_jetbike" },
    { 0xA62A, "vehicle_scripts/_jetbike_aud" },
    { 0xA62B, "vehicle_scripts/_littlebird" },
    { 0xA62C, "vehicle_scripts/_littlebird_aud" },
    { 0xA62D, "vehicle_scripts/_littlebird_landing" },
    { 0xA62E, "vehicle_scripts/_littlebird_player" },
    { 0xA62F, "vehicle_scripts/_mi17" },
    { 0xA630, "vehicle_scripts/_mi17_aud" },
    { 0xA631, "vehicle_scripts/_mi17_noai" },
    { 0xA632, "vehicle_scripts/_mig29" },
    { 0xA633, "vehicle_scripts/_mig29_controllable" },
    { 0xA634, "vehicle_scripts/_mil_cargo_truck" },
    { 0xA635, "vehicle_scripts/_pdrone" },
    { 0xA636, "vehicle_scripts/_pdrone_aud" },
    { 0xA637, "vehicle_scripts/_pdrone_player" },
    { 0xA638, "vehicle_scripts/_pdrone_player_aud" },
    { 0xA639, "vehicle_scripts/_pdrone_security" },
    { 0xA63A, "vehicle_scripts/_pdrone_security_aud" },
    { 0xA63B, "vehicle_scripts/_pdrone_tactical_picker" },
    { 0xA63C, "vehicle_scripts/_pdrone_threat_sensor" },
    { 0xA63D, "vehicle_scripts/_pitbull" },
    { 0xA63E, "vehicle_scripts/_pitbull_aud" },
    { 0xA63F, "vehicle_scripts/_razorback" },
    { 0xA640, "vehicle_scripts/_razorback_fx" },
    { 0xA641, "vehicle_scripts/_s19" },
    { 0xA642, "vehicle_scripts/_sentinel_survey_drone_hud" },
    { 0xA643, "vehicle_scripts/_shrike" },
    { 0xA644, "vehicle_scripts/_sidewinder_scripted" },
    { 0xA645, "vehicle_scripts/_slamraam" },
    { 0xA646, "vehicle_scripts/_sniper_drone" },
    { 0xA647, "vehicle_scripts/_sniper_drone_aud" },
    { 0xA648, "vehicle_scripts/_uk_delivery_truck" },
    { 0xA649, "vehicle_scripts/_vehicle_missile_launcher_ai" },
    { 0xA64A, "vehicle_scripts/_vehicle_multiweapon_util" },
    { 0xA64B, "vehicle_scripts/_vehicle_turret_ai" },
    { 0xA64C, "vehicle_scripts/_vrap" },
    { 0xA64D, "vehicle_scripts/_walker_tank" },
    { 0xA64E, "vehicle_scripts/_x4walker_wheels" },
    { 0xA64F, "vehicle_scripts/_x4walker_wheels_aud" },
    { 0xA650, "vehicle_scripts/_x4walker_wheels_turret" },
    { 0xA651, "vehicle_scripts/_x4walker_wheels_turret_aud" },
    { 0xA652, "vehicle_scripts/_x4walker_wheels_turret_closed" },
    { 0xA653, "vehicle_scripts/_x4walker_wheels_turret_closed_aud" },
    { 0xA654, "vehicle_scripts/_xh9_warbird" },
/*
    { 0x0000, "xmodelalias/alias_africa_civilian_male_heads" },
    { 0x0000, "xmodelalias/alias_atlas_bodyguard_heads" },
    { 0x0000, "xmodelalias/alias_civ_afr_dark_male_bodies_casual" },
    { 0x0000, "xmodelalias/alias_civ_afr_dark_male_bodies_dress" },
    { 0x0000, "xmodelalias/alias_civ_afr_dark_male_heads" },
    { 0x0000, "xmodelalias/alias_civ_afr_drk_female_bodies_cas" },
    { 0x0000, "xmodelalias/alias_civ_afr_drk_female_bodies_drs" },
    { 0x0000, "xmodelalias/alias_civ_afr_drk_female_heads" },
    { 0x0000, "xmodelalias/alias_civ_afr_lgt_fem_bod_drs_sml" },
    { 0x0000, "xmodelalias/alias_civ_afr_lgt_female_bodies_cas" },
    { 0x0000, "xmodelalias/alias_civ_afr_lgt_female_bodies_drs" },
    { 0x0000, "xmodelalias/alias_civ_afr_lgt_female_heads" },
    { 0x0000, "xmodelalias/alias_civ_afr_light_male_bodies_casual" },
    { 0x0000, "xmodelalias/alias_civ_afr_light_male_bodies_dress" },
    { 0x0000, "xmodelalias/alias_civ_afr_light_male_heads" },
    { 0x0000, "xmodelalias/alias_civ_asi_male_bodies_casual" },
    { 0x0000, "xmodelalias/alias_civ_asi_male_bodies_dress" },
    { 0x0000, "xmodelalias/alias_civ_asi_male_heads" },
    { 0x0000, "xmodelalias/alias_civ_asi_male_heads_cpt" },
    { 0x0000, "xmodelalias/alias_civ_cau_fem_bod_drs_sml" },
    { 0x0000, "xmodelalias/alias_civ_cau_fem_heads_sml" },
    { 0x0000, "xmodelalias/alias_civ_cau_female_bodies_cas" },
    { 0x0000, "xmodelalias/alias_civ_cau_female_bodies_drs" },
    { 0x0000, "xmodelalias/alias_civ_cau_female_heads" },
    { 0x0000, "xmodelalias/alias_civ_cau_male_bodies_casual" },
    { 0x0000, "xmodelalias/alias_civ_cau_male_bodies_dress" },
    { 0x0000, "xmodelalias/alias_civ_cau_male_heads" },
    { 0x0000, "xmodelalias/alias_civ_cau_male_heads_hazmat_nohat" },
    { 0x0000, "xmodelalias/alias_civ_mde_female_bodies_cas" },
    { 0x0000, "xmodelalias/alias_civ_mde_female_bodies_drs" },
    { 0x0000, "xmodelalias/alias_civ_mde_female_heads" },
    { 0x0000, "xmodelalias/alias_civ_mde_male_bodies_casual" },
    { 0x0000, "xmodelalias/alias_civ_mde_male_bodies_dress" },
    { 0x0000, "xmodelalias/alias_civ_mde_male_heads" },
    { 0x0000, "xmodelalias/alias_civ_pris_afr_dark_male_bodies" },
    { 0x0000, "xmodelalias/alias_civ_pris_cau_male_bodies" },
    { 0x0000, "xmodelalias/alias_civ_pris_mde_male_bodies" },
    { 0x0000, "xmodelalias/alias_civ_rec_funeral_male_body" },
    { 0x0000, "xmodelalias/alias_civ_rec_funeral_male_body_afr" },
    { 0x0000, "xmodelalias/alias_civ_rec_funeral_male_heads" },
    { 0x0000, "xmodelalias/alias_civ_rec_funeral_male_heads_afr" },
    { 0x0000, "xmodelalias/alias_civ_urban_dead_body_a" },
    { 0x0000, "xmodelalias/alias_civ_urban_dead_body_b" },
    { 0x0000, "xmodelalias/alias_civ_urban_dead_body_c" },
    { 0x0000, "xmodelalias/alias_civ_urban_male_heads_afr_light" },
    { 0x0000, "xmodelalias/alias_civ_worker_hardhat_s1_heads" },
    { 0x0000, "xmodelalias/alias_civilian_heads_prisoner_female" },
    { 0x0000, "xmodelalias/alias_civilian_slum_heads" },
    { 0x0000, "xmodelalias/alias_civilian_slum_heads_wht" },
    { 0x0000, "xmodelalias/alias_civilian_worker_heads" },
    { 0x0000, "xmodelalias/alias_cloak_test" },
    { 0x0000, "xmodelalias/alias_coop_cloaked_static_heads" },
    { 0x0000, "xmodelalias/alias_enemy_atlas_arctic_heads" },
    { 0x0000, "xmodelalias/alias_enemy_atlas_elite_heads" },
    { 0x0000, "xmodelalias/alias_enemy_atlas_heads" },
    { 0x0000, "xmodelalias/alias_greece_civilian_heads_males_a" },
    { 0x0000, "xmodelalias/alias_greece_civilian_heads_males_b" },
    { 0x0000, "xmodelalias/alias_kva_heads" },
    { 0x0000, "xmodelalias/alias_mp_sentinel_heads" },
    { 0x0000, "xmodelalias/alias_nigerian_army_bodies" },
    { 0x0000, "xmodelalias/alias_nigerian_army_heads" },
    { 0x0000, "xmodelalias/alias_pmc_casual_heads" },
    { 0x0000, "xmodelalias/alias_pmc_casual_heads_asi" },
    { 0x0000, "xmodelalias/alias_pmc_helmet_heads" },
    { 0x0000, "xmodelalias/alias_sentinel_arctic_bodies" },
    { 0x0000, "xmodelalias/alias_sentinel_arctic_heads" },
    { 0x0000, "xmodelalias/alias_sentinel_bodies" },
    { 0x0000, "xmodelalias/alias_sentinel_heads" },
    { 0x0000, "xmodelalias/alias_sentinel_udt_heads" },
    { 0x0000, "xmodelalias/alias_seoul_civilian_body_females" },
    { 0x0000, "xmodelalias/alias_seoul_civilian_body_males_a" },
    { 0x0000, "xmodelalias/alias_seoul_civilian_body_males_b" },
    { 0x0000, "xmodelalias/alias_seoul_civilian_body_males_d" },
    { 0x0000, "xmodelalias/alias_seoul_civilian_body_males_f" },
    { 0x0000, "xmodelalias/alias_seoul_civilian_head_females" },
    { 0x0000, "xmodelalias/alias_seoul_civilian_head_males_a" },
    { 0x0000, "xmodelalias/alias_seoul_civilian_head_males_b" },
    { 0x0000, "xmodelalias/alias_seoul_civilian_head_males_c" },
    { 0x0000, "xmodelalias/alias_seoul_civilian_head_males_d" },
    { 0x0000, "xmodelalias/alias_us_marine_dress_bodies" },
    { 0x0000, "xmodelalias/alias_us_marine_dress_heads" },
    { 0x0000, "xmodelalias/alias_us_marine_heads" },
    { 0x0000, "maps/animated_models/foliage_tree_grey_oak_lg_a" },
    { 0x0000, "maps/createart/betrayal_art" },
    { 0x0000, "maps/createart/betrayal_fog" },
    { 0x0000, "maps/createart/betrayal_fog_hdr" },
    { 0x0000, "maps/createart/captured_art" },
    { 0x0000, "maps/createart/captured_fog" },
    { 0x0000, "maps/createart/captured_fog_hdr" },
    { 0x0000, "maps/createart/crash_art" },
    { 0x0000, "maps/createart/crash_fog" },
    { 0x0000, "maps/createart/crash_fog_hdr" },
    { 0x0000, "maps/createart/credits_s1_art" },
    { 0x0000, "maps/createart/credits_s1_fog" },
    { 0x0000, "maps/createart/credits_s1_fog_hdr" },
    { 0x0000, "maps/createart/detroit_art" },
    { 0x0000, "maps/createart/detroit_fog" },
    { 0x0000, "maps/createart/detroit_fog_hdr" },
    { 0x0000, "maps/createart/df_baghdad_art" },
    { 0x0000, "maps/createart/df_baghdad_fog" },
    { 0x0000, "maps/createart/df_baghdad_fog_hdr" },
    { 0x0000, "maps/createart/df_fly_art" },
    { 0x0000, "maps/createart/df_fly_fog" },
    { 0x0000, "maps/createart/df_fly_fog_hdr" },
    { 0x0000, "maps/createart/finale_art" },
    { 0x0000, "maps/createart/finale_fog" },
    { 0x0000, "maps/createart/finale_fog_hdr" },
    { 0x0000, "maps/createart/fusion_art" },
    { 0x0000, "maps/createart/fusion_fog" },
    { 0x0000, "maps/createart/fusion_fog_hdr" },
    { 0x0000, "maps/createart/greece_art" },
    { 0x0000, "maps/createart/greece_fog" },
    { 0x0000, "maps/createart/greece_fog_hdr" },
    { 0x0000, "maps/createart/irons_estate_art" },
    { 0x0000, "maps/createart/irons_estate_fog" },
    { 0x0000, "maps/createart/irons_estate_fog_hdr" },
    { 0x0000, "maps/createart/lab_art" },
    { 0x0000, "maps/createart/lab_fog" },
    { 0x0000, "maps/createart/lab_fog_hdr" },
    { 0x0000, "maps/createart/lagos_art" },
    { 0x0000, "maps/createart/lagos_fog" },
    { 0x0000, "maps/createart/lagos_fog_hdr" },
    { 0x0000, "maps/createart/mp_comeback_art" },
    { 0x0000, "maps/createart/mp_comeback_fog" },
    { 0x0000, "maps/createart/mp_comeback_fog_hdr" },
    { 0x0000, "maps/createart/mp_detroit_art" },
    { 0x0000, "maps/createart/mp_detroit_fog" },
    { 0x0000, "maps/createart/mp_detroit_fog_hdr" },
    { 0x0000, "maps/createart/mp_greenband_art" },
    { 0x0000, "maps/createart/mp_greenband_fog" },
    { 0x0000, "maps/createart/mp_greenband_fog_hdr" },
    { 0x0000, "maps/createart/mp_instinct_art" },
    { 0x0000, "maps/createart/mp_instinct_fog" },
    { 0x0000, "maps/createart/mp_instinct_fog_hdr" },
    { 0x0000, "maps/createart/mp_lab2_art" },
    { 0x0000, "maps/createart/mp_lab2_fog" },
    { 0x0000, "maps/createart/mp_lab2_fog_hdr" },
    { 0x0000, "maps/createart/mp_laser2_art" },
    { 0x0000, "maps/createart/mp_laser2_fog" },
    { 0x0000, "maps/createart/mp_laser2_fog_hdr" },
    { 0x0000, "maps/createart/mp_levity_art" },
    { 0x0000, "maps/createart/mp_levity_fog" },
    { 0x0000, "maps/createart/mp_levity_fog_hdr" },
    { 0x0000, "maps/createart/mp_prison_art" },
    { 0x0000, "maps/createart/mp_prison_fog" },
    { 0x0000, "maps/createart/mp_prison_fog_hdr" },
    { 0x0000, "maps/createart/mp_prison_z_art" },
    { 0x0000, "maps/createart/mp_prison_z_fog" },
    { 0x0000, "maps/createart/mp_prison_z_fog_hdr" },
    { 0x0000, "maps/createart/mp_recovery_art" },
    { 0x0000, "maps/createart/mp_recovery_fog" },
    { 0x0000, "maps/createart/mp_recovery_fog_hdr" },
    { 0x0000, "maps/createart/mp_refraction_art" },
    { 0x0000, "maps/createart/mp_refraction_fog" },
    { 0x0000, "maps/createart/mp_refraction_fog_hdr" },
    { 0x0000, "maps/createart/mp_solar_art" },
    { 0x0000, "maps/createart/mp_solar_fog" },
    { 0x0000, "maps/createart/mp_solar_fog_hdr" },
    { 0x0000, "maps/createart/mp_terrace_art" },
    { 0x0000, "maps/createart/mp_terrace_fog" },
    { 0x0000, "maps/createart/mp_terrace_fog_hdr" },
    { 0x0000, "maps/createart/mp_venus_art" },
    { 0x0000, "maps/createart/mp_venus_fog" },
    { 0x0000, "maps/createart/mp_venus_fog_hdr" },
*/
    { 0xA6F9, "maps/createart/mp_vlobby_room_art" },
    { 0xA6FA, "maps/createart/mp_vlobby_room_fog" },
    { 0xA6FB, "maps/createart/mp_vlobby_room_fog_hdr" },
//  { 0xA6FX-0xA71F } S1 stuff
    { 0xA720, "maps/mp/_adrenaline" },
    { 0xA72A, "maps/mp/_aerial_pathnodes" },
    { 0xA72B, "maps/mp/_animatedmodels" },
    { 0xA72C, "maps/mp/_areas" },
    { 0xA72D, "maps/mp/_art" },
    { 0xA72E, "maps/mp/_audio" },
    { 0xA72F, "maps/mp/_awards" },
    { 0xA730, "maps/mp/_braggingrights" },
    { 0xA731, "maps/mp/_compass" },
    { 0xA732, "maps/mp/_createfx" },
    { 0xA733, "maps/mp/_crib" },
    { 0xA734, "maps/mp/_destructables" },
    { 0xA735, "maps/mp/_dynamic_events" },
    { 0xA736, "maps/mp/_empgrenade" },
    { 0xA737, "maps/mp/_entityheadicons" },
    { 0xA738, "maps/mp/_events" },
    { 0xA739, "maps/mp/_exo_battery" },
    { 0xA73A, "maps/mp/_exo_cloak" },
    { 0xA73B, "maps/mp/_exo_hover" },
    { 0xA73C, "maps/mp/_exo_mute" },
    { 0xA73D, "maps/mp/_exo_ping" },
    { 0xA73E, "maps/mp/_exo_repulsor" },
    { 0xA73F, "maps/mp/_exo_shield" },
    { 0xA740, "maps/mp/_exo_suit" },
    { 0xA741, "maps/mp/_exocrossbow" },
    { 0xA742, "maps/mp/_exoknife" },
    { 0xA743, "maps/mp/_explosive_drone" },
    { 0xA744, "maps/mp/_explosive_gel" },
    { 0xA745, "maps/mp/_extrahealth" },
    { 0xA746, "maps/mp/_fastheal" },
    { 0xA747, "maps/mp/_flashgrenades" },
    { 0xA748, "maps/mp/_fx" },
    { 0xA749, "maps/mp/_global_fx" },
    { 0xA74A, "maps/mp/_global_fx_code" },
    { 0xA74B, "maps/mp/_lasersight" },
    { 0xA74C, "maps/mp/_load" },
    { 0xA74D, "maps/mp/_lsrmissileguidance" },
    { 0xA74E, "maps/mp/_matchdata" },
    { 0xA74F, "maps/mp/_menus" },
    { 0xA750, "maps/mp/_microdronelauncher" },
    { 0xA751, "maps/mp/_movers" },
    { 0xA752, "maps/mp/_mp_lights" },
    { 0xA753, "maps/mp/_mutebomb" },
    { 0xA754, "maps/mp/_na45" },
    { 0xA755, "maps/mp/_opticsthermal" },
    { 0xA756, "maps/mp/_reinforcements" },
    { 0xA757, "maps/mp/_riotshield" },
    { 0xA758, "maps/mp/_scoreboard" },
    { 0xA759, "maps/mp/_shutter" },
    { 0xA75A, "maps/mp/_snd_common_mp" },
    { 0xA75B, "maps/mp/_stinger" },
    { 0xA75C, "maps/mp/_stingerm7" },
    { 0xA75D, "maps/mp/_stock" },
    { 0xA75E, "maps/mp/_target_enhancer" },
    { 0xA75F, "maps/mp/_teleport" },
    { 0xA760, "maps/mp/_threatdetection" },
    { 0xA761, "maps/mp/_tracking_drone" },
    { 0xA762, "maps/mp/_trackrounds" },
    { 0xA763, "maps/mp/_tridrone" },
    { 0xA764, "maps/mp/_utility" },
    { 0xA765, "maps/mp/_vl_base" },
    { 0xA766, "maps/mp/_vl_camera" },
    { 0xA767, "maps/mp/_vl_firingrange" },
    { 0xA768, "maps/mp/_vl_selfiebooth" },
    { 0xA769, "maps/mp/_water" },
    { 0xA76A, "maps/mp/_zipline" },
    { 0xA76B, "maps/mp/mp_comeback_fx" },
    { 0xA76C, "maps/mp/mp_comeback_precache" },
    { 0xA76D, "maps/mp/mp_detroit_fx" },
    { 0xA76E, "maps/mp/mp_detroit_precache" },
    { 0xA76D, "maps/mp/mp_greenband_fx" },
    { 0xA770, "maps/mp/mp_greenband_precache" },
    { 0xA771, "maps/mp/mp_instinct_fx" },
    { 0xA772, "maps/mp/mp_instinct_precache" },
    { 0xA773, "maps/mp/mp_lab2_fx" },
    { 0xA774, "maps/mp/mp_lab2_precache" },
    { 0xA775, "maps/mp/mp_laser2_fx" },
    { 0xA776, "maps/mp/mp_laser2_precache" },
    { 0xA777, "maps/mp/mp_levity_fx" },
    { 0xA778, "maps/mp/mp_levity_precache" },
    { 0xA779, "maps/mp/mp_prison_fx" },
    { 0xA77A, "maps/mp/mp_prison_precache" },
    { 0xA77B, "maps/mp/mp_prison_z_fx" },
    { 0xA77C, "maps/mp/mp_prison_z_precache" },
    { 0xA77D, "maps/mp/mp_recovery_fx" },
    { 0xA77E, "maps/mp/mp_recovery_precache" },
    { 0xA77F, "maps/mp/mp_refraction_fx" },
    { 0xA780, "maps/mp/mp_refraction_precache" },
    { 0xA781, "maps/mp/mp_solar_fx" },
    { 0xA782, "maps/mp/mp_solar_precache" },
    { 0xA783, "maps/mp/mp_terrace_fx" },
    { 0xA784, "maps/mp/mp_terrace_precache" },
    { 0xA785, "maps/mp/mp_venus_fx" },
    { 0xA786, "maps/mp/mp_venus_precache" },
    { 0xA787, "maps/mp/mp_vlobby_room_fx" },
    { 0xA788, "maps/mp/mp_vlobby_room_precache" },
    { 0xA789, "maps/mp/gametypes/_battlebuddy" },
    { 0xA78A, "maps/mp/gametypes/_battlechatter_mp" },
    { 0xA78B, "maps/mp/gametypes/_class" },
    { 0xA78C, "maps/mp/gametypes/_clientids" },
    { 0xA78D, "maps/mp/gametypes/_damage" },
    { 0xA78E, "maps/mp/gametypes/_damagefeedback" },
    { 0xA78F, "maps/mp/gametypes/_deathicons" },
    { 0xA790, "maps/mp/gametypes/_dev" },
    { 0xA791, "maps/mp/gametypes/_equipment" },
    { 0xA792, "maps/mp/gametypes/_friendicons" },
    { 0xA793, "maps/mp/gametypes/_gamelogic" },
    { 0xA794, "maps/mp/gametypes/_gameobjects" },
    { 0xA795, "maps/mp/gametypes/_gamescores" },
    { 0xA796, "maps/mp/gametypes/_globalentities" },
    { 0xA797, "maps/mp/gametypes/_globallogic" },
    { 0xA798, "maps/mp/gametypes/_hardpoints" },
    { 0xA799, "maps/mp/gametypes/_healthoverlay" },
    { 0xA79A, "maps/mp/gametypes/_high_jump_mp" },
    { 0xA79B, "maps/mp/gametypes/_horde_armory" },
    { 0xA79C, "maps/mp/gametypes/_horde_crates" },
    { 0xA79D, "maps/mp/gametypes/_horde_dialog" },
    { 0xA79E, "maps/mp/gametypes/_horde_drones" },
    { 0xA79F, "maps/mp/gametypes/_horde_laststand" },
    { 0xA7A0, "maps/mp/gametypes/_horde_sentry" },
    { 0xA7A1, "maps/mp/gametypes/_horde_smart_grenade" },
    { 0xA7A2, "maps/mp/gametypes/_horde_util" },
    { 0xA7A3, "maps/mp/gametypes/_horde_zombies" },
    { 0xA7A4, "maps/mp/gametypes/_hostmigration" },
    { 0xA7A5, "maps/mp/gametypes/_hud" },
    { 0xA7A6, "maps/mp/gametypes/_hud_message" },
    { 0xA7A7, "maps/mp/gametypes/_hud_util" },
    { 0xA7A8, "maps/mp/gametypes/_killcam" },
    { 0xA7A9, "maps/mp/gametypes/_menus" },
    { 0xA7AA, "maps/mp/gametypes/_misions" },
    { 0xA7AB, "maps/mp/gametypes/_music_and_dialog" },
    { 0xA7AC, "maps/mp/gametypes/_objpoints" },
    { 0xA7AD, "maps/mp/gametypes/_orbital" },
    { 0xA7AE, "maps/mp/gametypes/_persistence" },
    { 0xA7AF, "maps/mp/gametypes/_player_boost_jump_mp" },
    { 0xA7B0, "maps/mp/gametypes/_playercards" },
    { 0xA7B1, "maps/mp/gametypes/_playerlogic" },
    { 0xA7B2, "maps/mp/gametypes/_portable_radar" },
    { 0xA7B3, "maps/mp/gametypes/_quickmessages" },
    { 0xA7B4, "maps/mp/gametypes/_rank" },
    { 0xA7B5, "maps/mp/gametypes/_scrambler" },
    { 0xA7B6, "maps/mp/gametypes/_serversettings" },
    { 0xA7B7, "maps/mp/gametypes/_shellshock" },
    { 0xA7B8, "maps/mp/gametypes/_spawnfactor" },
    { 0xA7B9, "maps/mp/gametypes/_spawnlogic" },
    { 0xA7BA, "maps/mp/gametypes/_spawnscoring" },
    { 0xA7BB, "maps/mp/gametypes/_spectating" },
    { 0xA7BC, "maps/mp/gametypes/_teams" },
    { 0xA7BD, "maps/mp/gametypes/_tweakables" },
    { 0xA7BE, "maps/mp/gametypes/_weapons" },
    { 0xA7BF, "maps/mp/killstreaks/_aerial_utility" },
    { 0xA7C0, "maps/mp/killstreaks/_agent_killstreak" },
    { 0xA7C1, "maps/mp/killstreaks/_airdrop" },
    { 0xA7C2, "maps/mp/killstreaks/_airstrike" },
    { 0xA7C3, "maps/mp/killstreaks/_assaultdrone_ai" },
    { 0xA7C4, "maps/mp/killstreaks/_autosentry" },
    { 0xA7C5, "maps/mp/killstreaks/_coop_util" },
    { 0xA7C6, "maps/mp/killstreaks/_dog_killstreak" },
    { 0xA7C7, "maps/mp/killstreaks/_drone_assault" },
    { 0xA7C8, "maps/mp/killstreaks/_drone_carepackage" },
    { 0xA7C9, "maps/mp/killstreaks/_drone_common" },
    { 0xA7CA, "maps/mp/killstreaks/_drone_recon" },
    { 0xA7CB, "maps/mp/killstreaks/_emp" },
    { 0xA7CC, "maps/mp/killstreaks/_juggernaut" },
    { 0xA7CD, "maps/mp/killstreaks/_killstreaks" },
    { 0xA7CE, "maps/mp/killstreaks/_killstreaks_init" },
    { 0xA7CF, "maps/mp/killstreaks/_marking_util" },
    { 0xA7D0, "maps/mp/killstreaks/_missile_strike" },
    { 0xA7D1, "maps/mp/killstreaks/_nuke" },
    { 0xA7D2, "maps/mp/killstreaks/_orbital_carepackage" },
    { 0xA7D3, "maps/mp/killstreaks/_orbital_strike" },
    { 0xA7D4, "maps/mp/killstreaks/_orbital_util" },
    { 0xA7D5, "maps/mp/killstreaks/_orbitalsupport" },
    { 0xA7D6, "maps/mp/killstreaks/_placeable" },
    { 0xA7D7, "maps/mp/killstreaks/_remoteturret" },
    { 0xA7D8, "maps/mp/killstreaks/_rippedturret" },
    { 0xA7D9, "maps/mp/killstreaks/_teamammorefill" },
    { 0xA7DA, "maps/mp/killstreaks/_uav" },
    { 0xA7DB, "maps/mp/killstreaks/_warbird" },
    { 0xA7DC, "maps/mp/killstreaks/streak_mp_comeback" },
    { 0xA7DD, "maps/mp/killstreaks/streak_mp_detroit" },
    { 0xA7DE, "maps/mp/killstreaks/streak_mp_instinct" },
    { 0xA7DF, "maps/mp/killstreaks/streak_mp_laser2" },
    { 0xA7E0, "maps/mp/killstreaks/streak_mp_prison" },
    { 0xA7E1, "maps/mp/killstreaks/streak_mp_recovery" },
    { 0xA7E2, "maps/mp/killstreaks/streak_mp_refraction" },
    { 0xA7E3, "maps/mp/killstreaks/streak_mp_solar" },
    { 0xA7E4, "maps/mp/killstreaks/streak_mp_terrace" },
    { 0xA7E5, "maps/mp/perks/_perkfunctions" },
    { 0xA7E6, "maps/mp/perks/_perks" },

/*
    { 0x0DD, "createtime" },
    { 0x0DE, "criticalbulletdamagedist" },
    { 0x0DF, "crouch" },
    { 0x0E0, "currency" },
    { 0x0E1, "current" },
    { 0x0E2, "currentanimtime" },
    { 0x0E3, "currentgen" },
    { 0x0E4, "currentwinstreak" },
    { 0x0E5, "cursorhint" },
    { 0x0E6, "custom_attach_00" },
    { 0x0E7, "custom_attach_01" },
    { 0x0E8, "custom_attach_02" },
    { 0x0E9, "custom_attach_03" },
    { 0x0EA, "custom_attach_04" },
    { 0x0EB, "custom_attach_05" },
    { 0x0EC, "custom_attach_06" },
    { 0x0ED, "custom_attach_07" },
    { 0x0EE, "custom_attach_08" },
    { 0x0EF, "custom_attach_09" },
    { 0x0F0, "custom_attach_10" },
    { 0x0F1, "custom_attach_11" },
    { 0x0F2, "custom_attach_12" },
    { 0x0F3, "custom_attach_13" },
    { 0x0F4, "custom_attach_14" },
    { 0x0F5, "custom_attach_15" },
    { 0x0F6, "customclasses" },
    { 0x0F7, "customization_loaded" },
    { 0x0F8, "d" },
    { 0x0F9, "dailychallengeid" },
    { 0x0FA, "damage" },
    { 0x0FB, "damage_notdone" },
    { 0x0FC, "damagedir" },
    { 0x0FD, "damagelocation" },
    { 0x0FE, "damagemod" },
    { 0x0FF, "damagemultiplier" },
    { 0x100, "damageshield" },
    { 0x101, "damagetaken" },
    { 0x102, "damageweapon" },
    { 0x103, "damageyaw" },
    { 0x104, "dangerreactduration" },
    { 0x105, "datalength" },
    { 0x106, "dcid" },
    { 0x107, "dead" },
    { 0x108, "death" },
    { 0x109, "deathangles" },
    { 0x10A, "deathinvulnerabletime" },
    { 0x10B, "deathplant" },
    { 0x10C, "deathpos" },
    { 0x10D, "deaths" },
    { 0x10E, "deathshield" },
    { 0x10F, "defaultclasses" },
    { 0x110, "defense" },
    { 0x111, "defense_level" },
    { 0x112, "delayeddeath" },
    { 0x113, "deploy_riotshield" },
    { 0x114, "desc" },
    { 0x115, "descmodified" },
    { 0x116, "desiredangle" },
    { 0x117, "destructible_type" },
    { 0x118, "detectable" },
    { 0x119, "detected" },
    { 0x11A, "detonate" },
    { 0x11B, "device_id_high" },
    { 0x11C, "device_id_low" },
    { 0x11D, "deviceconnectionhistory" },
    { 0x11E, "deviceusefrequency" },
    { 0x11F, "diequietly" },
    { 0x120, "diffusefraction" },
    { 0x121, "direct" },
    { 0x122, "disable" },
    { 0x123, "disableplayeradsloscheck" },
    { 0x124, "dlight" },
    { 0x125, "dmg" },
    { 0x126, "dodamagetoall" },
    { 0x127, "dodangerreact" },
    { 0x128, "doffar" },
    { 0x129, "dofnear" },
    { 0x12A, "dofphysicalfocusdistance" },
    { 0x12B, "dofphysicalfstop" },
    { 0x12C, "dog" },
    { 0x12D, "doghandler" },
    { 0x12E, "doingambush" },
    { 0x12F, "done" },
    { 0x130, "dontavoidplayer" },
    { 0x131, "dotofdeath" },
    { 0x132, "down" },
    { 0x133, "downaimlimit" },
    { 0x134, "drawoncompass" },
    { 0x135, "dropweapon" },
    { 0x136, "duration" },
    { 0x137, "eftarc" },
    { 0x138, "empty" },
    { 0x139, "empty_offhand" },
    { 0x13A, "enable" },
    { 0x13B, "enablehudlighting" },
    { 0x13C, "enableshadows" },
    { 0x13D, "end_firing" },
    { 0x13E, "end_firing_left" },
    { 0x13F, "end_script" },
    { 0x140, "enddeaths" },
    { 0x141, "endkills" },
    { 0x142, "enemy" },
    { 0x143, "enemy_sighted" },
    { 0x144, "enemy_sighted_lost" },
    { 0x145, "enemy_visible" },
    { 0x146, "enemyname" },
    { 0x147, "enemyplatform" },
    { 0x148, "enemyradarmode" },
    { 0x149, "enemyxuidhigh" },
    { 0x14A, "enemyxuidlow" },
    { 0x14B, "energy_fire" },
    { 0x14C, "engagemaxdist" },
    { 0x14D, "engagemaxfalloffdist" },
    { 0x14E, "engagemindist" },
    { 0x14F, "engageminfalloffdist" },
    { 0x150, "enhanceable" },
    { 0x151, "entity" },
    { 0x152, "entitydeleted" },
    { 0x153, "entityoverflow_max" },
    { 0x154, "entityoverflow_worst" },
    { 0x155, "equipment" },
    { 0x156, "equipmentsetups" },
    { 0x157, "escaped" },
    { 0x158, "exclusive" },
    { 0x159, "exo_ability_activate" },
    { 0x15A, "exo_adrenaline_fire" },
    { 0x15B, "exo_boost" },
    { 0x15C, "exo_dodge" },
    { 0x15D, "exo_power" },
    { 0x15E, "exo_slide" },
    { 0x15F, "exo_slide_hit_player" },
    { 0x160, "exoattachment1" },
    { 0x161, "exoattachment2" },
    { 0x162, "experience" },
    { 0x163, "explode" },
    { 0x164, "exposedduration" },
    { 0x165, "extracustomclassesentitlement" },
    { 0x166, "extracustomclassesprestige" },
    { 0x167, "extrascore0" },
    { 0x168, "extrascore1" },
    { 0x169, "face_angle" },
    { 0x16A, "face_angle_3d" },
    { 0x16B, "face_angle_abs" },
    { 0x16C, "face_angle_rel" },
    { 0x16D, "face_current" },
    { 0x16E, "face_default" },
    { 0x16F, "face_direction" },
    { 0x170, "face_enemy" },
    { 0x171, "face_enemy_or_motion" },
    { 0x172, "face_goal" },
    { 0x173, "face_motion" },
    { 0x174, "face_point" },
    { 0x175, "facemotion" },
    { 0x176, "failed" },
    { 0x177, "falling" },
    { 0x178, "fast_radar" },
    { 0x179, "favoriteenemy" },
    { 0x17A, "finalaccuracy" },
    { 0x17B, "first_person" },
    { 0x17C, "firstplayedsptime" },
    { 0x17D, "fixednode" },
    { 0x17E, "fixednodesaferadius" },
    { 0x17F, "fl_rotor1" },
    { 0x180, "fl_rotor2" },
    { 0x181, "fl_rotor3" },
    { 0x182, "flash" },
    { 0x183, "flashbang" },
    { 0x184, "foley" },
    { 0x185, "follow" },
    { 0x186, "followmax" },
    { 0x187, "followmin" },
    { 0x188, "font" },
    { 0x189, "fontscale" },
    { 0x18A, "foot_ik_active" },
    { 0x18B, "foot_ik_blend_in" },
    { 0x18C, "foot_ik_blend_out" },
    { 0x18D, "foot_ik_inactive" },
    { 0x18E, "footstepdetectdist" },
    { 0x18F, "footstepdetectdistsprint" },
    { 0x190, "footstepdetectdistwalk" },
    { 0x191, "force_off" },
    { 0x192, "force_on" },
    { 0x193, "force_fully_on" },
    { 0x194, "forcepartyskillignore" },
    { 0x195, "forceragdollimmediate" },
    { 0x196, "forcespectatorclient" },
    { 0x197, "foregrip_off" },
    { 0x198, "foreground" },
    { 0x199, "forward" },
    { 0x19A, "fov" },
    { 0x19B, "fovcosine" },
    { 0x19C, "fovcosinebusy" },
    { 0x19D, "fovcosinez" },
    { 0x19E, "fr_rotor1" },
    { 0x19F, "fr_rotor2" },
    { 0x1A0, "fr_rotor3" },
    { 0x1A1, "fraction" },
    { 0x1A2, "frag" },
    { 0x1A3, "free" },
    { 0x1A4, "freecamera" },
    { 0x1A5, "freelook" },
    { 0x1A6, "frequency" },
    { 0x1A7, "friendlyfire" },
    { 0x1A8, "front_left" },
    { 0x1A9, "front_right" },
    { 0x1AA, "frontshieldanglecos" },
    { 0x1AB, "fs_concrete" },
    { 0x1AC, "fs_dirt" },
    { 0x1AD, "fs_metal" },
    { 0x1AE, "fs_wood" },
    { 0x1AF, "game_extrainfo" },
    { 0x1B0, "gamecount" },
    { 0x1B1, "gamertag" },
    { 0x1B2, "gamesplayed" },
    { 0x1B3, "gametype" },
    { 0x1B4, "gender" },
    { 0x1B5, "ghostsprestige" },
    { 0x1B6, "ghostsrank" },
    { 0x1B7, "glass" },
    { 0x1B8, "glass_damaged" },
    { 0x1B9, "glass_destroyed" },
    { 0x1BA, "globalcostume" },
    { 0x1BB, "gloves" },
    { 0x1BC, "glowalpha" },
    { 0x1BD, "glowcolor" },
    { 0x1BE, "goal" },
    { 0x1BF, "goal_changed" },
    { 0x1C0, "goal_reached" },
    { 0x1C1, "goal_yaw" },
    { 0x1C2, "goalheight" },
    { 0x1C3, "goalpos" },
    { 0x1C4, "goalradius" },
    { 0x1C5, "goaltime" },
    { 0x1C6, "goalweight" },
    { 0x1C7, "goingtoruntopos" },
    { 0x1C8, "gravity" },
    { 0x1C9, "gravity_noclip" },
    { 0x1CA, "grenade" },
    { 0x1CB, "grenade_fire" },
    { 0x1CC, "grenade_off" },
    { 0x1CD, "grenade_on" },
    { 0x1CE, "grenade_pullback" },
    { 0x1CF, "grenade_return_hand_tag" },
    { 0x1D0, "grenadeammo" },
    { 0x1D1, "grenadeawareness" },
    { 0x1D2, "grenadedanger" },
    { 0x1D3, "grenadeweapon" },
    { 0x1D4, "ground_slam" },
    { 0x1D5, "ground_slam_hit_player" },
    { 0x1D6, "groundentchanged" },
    { 0x1D7, "groundtype" },
    { 0x1D8, "gunblockedbywall" },
    { 0x1D9, "gunshot" },
    { 0x1DA, "gunshot_teammate" },
    { 0x1DB, "hardcoremodeon" },
    { 0x1DC, "hasdoublexpitem" },
    { 0x1DD, "hasradar" },
    { 0x1DE, "hasvalidcostumeselfieimage" },
    { 0x1DF, "head" },
    { 0x1E0, "headicon" },
    { 0x1E1, "headiconteam" },
    { 0x1E2, "headshots" },
    { 0x1E3, "health" },
    { 0x1E4, "healthregen" },
    { 0x1E5, "height" },
    { 0x1E6, "helmet" },
    { 0x1E7, "hidein3rdperson" },
    { 0x1E8, "hidewhendead" },
    { 0x1E9, "hidewhenindemo" },
    { 0x1EA, "hidewheninmenu" },
    { 0x1EB, "high_priority" },
    { 0x1EC, "highlyawareradius" },
    { 0x1ED, "hindlegstraceoffset" },
    { 0x1EE, "hintstring" },
    { 0x1EF, "hit_by_missile" },
    { 0x1F0, "horzalign" },
    { 0x1F1, "host_sucks_end_game" },
    { 0x1F2, "hostfailures" },
    { 0x1F3, "hostquits" },
    { 0x1F4, "hostsuccesses" },
    { 0x1F5, "human" },
    { 0x1F6, "iconnew" },
    { 0x1F7, "iconunlocked" },
    { 0x1F8, "ignoreall" },
    { 0x1F9, "ignoreclosefoliage" },
    { 0x1FA, "ignoreexplosionevents" },
    { 0x1FB, "ignoreforfixednodesafecheck" },
    { 0x1FC, "ignoreme" },
    { 0x1FD, "ignorerandombulletdamage" },
    { 0x1FE, "ignoresuppression" },
    { 0x1FF, "ignoretriggers" },
    { 0x200, "ikweight" },
    { 0x201, "index" },
    { 0x202, "infinite_energy" },
    { 0x203, "info_notnull" },
    { 0x204, "info_player_start" },
    { 0x205, "init" },
    { 0x206, "initstructs" },
    { 0x207, "insolid" },
    { 0x208, "intermission" },
    { 0x209, "interval" },
    { 0x20A, "inuse" },
    { 0x20B, "invalid_parent" },
    { 0x20C, "invisible" },
    { 0x20D, "isradarblocked" },
    { 0x20E, "item" },
    { 0x20F, "j_exo_rcket_arm02" },
    { 0x210, "j_exoclav04_l" },
    { 0x211, "j_exoclav04_r" },
    { 0x212, "j_exohip04_l" },
    { 0x213, "j_exohip04_r" },
    { 0x214, "j_eyeball_le" },
    { 0x215, "j_eyeball_ri" },
    { 0x216, "j_gun" },
    { 0x217, "j_head" },
    { 0x218, "j_hip_l" },
    { 0x219, "j_hip_r" },
    { 0x21A, "j_knee_le" },
    { 0x21B, "j_knee_ri" },
    { 0x21C, "j_left_elbow" },
    { 0x21D, "j_left_hand" },
    { 0x21E, "j_left_shoulder" },
    { 0x21F, "j_mainroot" },
    { 0x220, "j_neck" },
    { 0x221, "j_right_elbow" },
    { 0x222, "j_right_hand" },
    { 0x223, "j_right_hand_placement" },
    { 0x224, "j_right_shoulder" },
    { 0x225, "j_rocket" },
    { 0x226, "j_spine4" },
    { 0x227, "j_spinelower" },
    { 0x228, "j_spineupper" },
    { 0x229, "jumpcost" },
    { 0x22A, "jumping" },
    { 0x22B, "justclass" },
    { 0x22C, "kdratio" },
    { 0x22D, "keepclaimednode" },
    { 0x22E, "keepclaimednodeifvalid" },
    { 0x22F, "keepnodeduringscriptedanim" },
    { 0x230, "key1" },
    { 0x231, "key2" },
    { 0x232, "kill_timestamp" },
    { 0x233, "killanimscript" },
    { 0x234, "killcamentity" },
    { 0x235, "killcamentitylookat" },
    { 0x236, "kills" },
    { 0x237, "killstreak" },
    { 0x238, "killstreakcount" },
    { 0x239, "killstreakrestricted" },
    { 0x23A, "killstreakunlocked" },
    { 0x23B, "knife_off" },
    { 0x23C, "knife_on" },
    { 0x23D, "known_event" },
    { 0x23E, "label" },
    { 0x23F, "ladder_down" },
    { 0x240, "ladder_up" },
    { 0x241, "land" },
    { 0x242, "last_stand_count" },
    { 0x243, "lastattacker" },
    { 0x244, "lastenemysightpos" },
    { 0x245, "lastplayedtime" },
    { 0x246, "laststand" },
    { 0x247, "leanamount" },
    { 0x248, "ledge" },
    { 0x249, "left" },
    { 0x24A, "leftaimlimit" },
    { 0x24B, "leftarc" },
    { 0x24C, "lethal" },
    { 0x24D, "lifecount" },
    { 0x24E, "light" },
    { 0x24F, "lives" },
    { 0x250, "loadouts" },
    { 0x251, "lockorientation" },
    { 0x252, "lod" },
    { 0x253, "look" },
    { 0x254, "lookahead" },
    { 0x255, "lookaheaddir" },
    { 0x256, "lookaheaddist" },
    { 0x257, "lookaheadhitsstairs" },
    { 0x258, "lookforward" },
    { 0x259, "lookright" },
    { 0x25A, "looktarget" },
    { 0x25B, "lookup" },
    { 0x25C, "loot" },
    { 0x25D, "lootnew" },
    { 0x25E, "loses" },
    { 0x25F, "low_priority" },
    { 0x260, "lowresbackground" },
    { 0x261, "luinotifyserver" },
    { 0x262, "mag_eject" },
    { 0x263, "mag_eject_left" },
    { 0x264, "main" },
    { 0x265, "manual" },
    { 0x266, "manual_ai" },
    { 0x267, "manual_change" },
    { 0x268, "map" },
    { 0x269, "matchid" },
    { 0x26A, "matchmakingsettingsversion" },
    { 0x26B, "matchmakingtesttype" },
    { 0x26C, "max_time" },
    { 0x26D, "maxfaceenemydist" },
    { 0x26E, "maxhealth" },
    { 0x26F, "maxrange" },
    { 0x270, "maxsightdistsqrd" },
    { 0x271, "maxturnspeed" },
    { 0x272, "maxvisibledist" },
    { 0x273, "melee_fired" },
    { 0x274, "melee_hit_react" },
    { 0x275, "meleeattackdist" },
    { 0x276, "menuresponse" },
    { 0x277, "micro_dlc_bits_last_gen" },
    { 0x278, "micro_dlc_bits_next_gen" },
    { 0x279, "middle_left" },
    { 0x27A, "middle_right" },
    { 0x27B, "migrateablequits" },
    { 0x27C, "min_energy" },
    { 0x27D, "min_time" },
    { 0x27E, "minpaindamage" },
    { 0x27F, "minusedistsq" },
    { 0x280, "missile_fire" },
    { 0x281, "missile_passed_target" },
    { 0x282, "missile_stuck" },
    { 0x283, "mlgversion" },
    { 0x284, "mod" },
    { 0x285, "mod_crush" },
    { 0x286, "mod_energy" },
    { 0x287, "mod_explosive" },
    { 0x288, "mod_explosive_bullet" },
    { 0x289, "mod_falling" },
    { 0x28A, "mod_grenade" },
    { 0x28B, "mod_grenade_splash" },
    { 0x28C, "mod_head_shot" },
    { 0x28D, "mod_impact" },
    { 0x28E, "mod_melee" },
    { 0x28F, "mod_melee_alien" },
    { 0x290, "mod_melee_alt" },
    { 0x291, "mod_melee_dog" },
    { 0x292, "mod_pistol_bullet" },
    { 0x293, "mod_projectile" },
    { 0x294, "mod_projectile_splash" },
    { 0x295, "mod_rifle_bullet" },
    { 0x296, "mod_suicide" },
    { 0x297, "mod_trigger_hurt" },
    { 0x298, "mod_unknown" },
    { 0x299, "model" },
    { 0x29A, "modeprefix" },
    { 0x29B, "modifiers" },
    { 0x29C, "motiontrackerenabled" },
    { 0x29D, "mounted_dlc_bits" },
    { 0x29E, "movedone" },
    { 0x29F, "movemode" },
    { 0x2A0, "munition" },
    { 0x2A1, "munition_level" },
    { 0x2A2, "mw3prestige" },
    { 0x2A3, "mw3rank" },
    { 0x2A4, "name" },
    { 0x2A5, "namemodified" },
    { 0x2A6, "near_goal" },
    { 0x2A7, "nearz" },
    { 0x2A8, "neutral" },
    { 0x2A9, "never" },
    { 0x2AA, "newenemyreactiondistsq" },
    { 0x2AB, "newentitlement" },
    { 0x2AC, "nextgen" },
    { 0x2AD, "nextreadblackops2" },
    { 0x2AE, "nextreadghosts0" },
    { 0x2AF, "nextreadghosts1" },
    { 0x2B0, "nextreadmw3" },
    { 0x2B1, "night_vision_off" },
    { 0x2B2, "night_vision_on" },
    { 0x2B3, "no_bot_random_path" },
    { 0x2B4, "no_cover" },
    { 0x2B5, "no_gravity" },
    { 0x2B6, "noattackeraccuracymod" },
    { 0x2B7, "noclip" },
    { 0x2B8, "node" },
    { 0x2B9, "node_not_safe" },
    { 0x2BA, "node_out_of_range" },
    { 0x2BB, "node_relinquished" },
    { 0x2BC, "node_taken" },
    { 0x2BD, "nodeoffsetpos" },
    { 0x2BE, "nododgemove" },
    { 0x2BF, "nogravity" },
    { 0x2C0, "nogrenadereturnthrow" },
    { 0x2C1, "noncombat" },
    { 0x2C2, "none" },
    { 0x2C3, "nonmigrateablequits" },
    { 0x2C4, "nophysics" },
    { 0x2C5, "normal" },
    { 0x2C6, "normal_radar" },
    { 0x2C7, "northyaw" },
    { 0x2C8, "notifyname" },
    { 0x2C9, "notinsolid" },
    { 0x2CA, "num0" },
    { 0x2CB, "num1" },
    { 0x2CC, "num2" },
    { 0x2CD, "num3" },
    { 0x2CE, "num4" },
    { 0x2CF, "objective" },
    { 0x2D0, "obstacle" },
    { 0x2D1, "offense" },
    { 0x2D2, "offense_level" },
    { 0x2D3, "offhand" },
    { 0x2D4, "offhand_end" },
    { 0x2D5, "offhandweapon" },
    { 0x2D6, "oldtime" },
    { 0x2D7, "ondeactivate" },
    { 0x2D8, "onenterstate" },
    { 0x2D9, "only_sky" },
    { 0x2DA, "onlygoodnearestnodes" },
    { 0x2DB, "onwifi" },
    { 0x2DC, "operationsdeadline" },
    { 0x2DD, "oriented" },
    { 0x2DE, "orientto_complete" },
    { 0x2DF, "origin" },
    { 0x2E0, "other" },
    { 0x2E1, "over" },
    { 0x2E2, "owner" },
    { 0x2E3, "pacifist" },
    { 0x2E4, "pacifistwait" },
    { 0x2E5, "pain" },
    { 0x2E6, "pantssize" },
    { 0x2E7, "parentindex" },
    { 0x2E8, "parentname" },
    { 0x2E9, "partyid" },
    { 0x2EA, "pasttitledata" },
    { 0x2EB, "patch" },
    { 0x2EC, "patchbacking" },
    { 0x2ED, "path_blocked" },
    { 0x2EE, "path_changed" },
    { 0x2EF, "path_dir_change" },
    { 0x2F0, "path_enemy" },
    { 0x2F1, "path_need_dodge" },
    { 0x2F2, "path_set" },
    { 0x2F3, "pathenemyfightdist" },
    { 0x2F4, "pathenemylookahead" },
    { 0x2F5, "pathgoalpos" },
    { 0x2F6, "pathlookaheaddist" },
    { 0x2F7, "pathrandompercent" },
    { 0x2F8, "pc" },
    { 0x2F9, "pccg" },
    { 0x2FA, "pelvis" },
    { 0x2FB, "perk1" },
    { 0x2FC, "perk2" },
    { 0x2FD, "perk3" },
    { 0x2FE, "perk4" },
    { 0x2FF, "perk5" },
    { 0x300, "perk6" },
    { 0x301, "perkclassrestricted" },
    { 0x302, "perkrestricted" },
    { 0x303, "perks" },
    { 0x304, "perkslots" },
    { 0x305, "pers" },
    { 0x306, "persistentperksunlocked" },
    { 0x307, "persistentweaponsunlocked" },
    { 0x308, "phone_off" },
    { 0x309, "phone_on" },
    { 0x30A, "physics_finished" },
    { 0x30B, "physics_impact" },
    { 0x30C, "pickup" },
    { 0x30D, "pickup_riotshield" },
    { 0x30E, "pistol" },
    { 0x30F, "pitchamount" },
    { 0x310, "pitchconvergencetime" },
    { 0x311, "plane_waypoint" },
    { 0x312, "playedblackops2" },
    { 0x313, "playedghosts" },
    { 0x314, "playedmw3" },
    { 0x315, "player" },
    { 0x316, "player_controller" },
    { 0x317, "player_pushed" },
    { 0x318, "playercardbackground" },
    { 0x319, "playercardpatch" },
    { 0x31A, "playercardpatchbacking" },
    { 0x31B, "playerconnectionhistory" },
    { 0x31C, "playerid" },
    { 0x31D, "playerip" },
    { 0x31E, "playername" },
    { 0x31F, "playerpositions" },
    { 0x320, "players" },
    { 0x321, "playerSpread" },
    { 0x322, "playerxuidhigh" },
    { 0x323, "playerxuidlow" },
    { 0x324, "playing" },
    { 0x325, "points" },
    { 0x326, "position" },
    { 0x327, "positioninworld" },
    { 0x328, "postsharpturnlookaheaddist" },
    { 0x329, "precache" },
    { 0x32A, "predicted_projectile_impact" },
    { 0x32B, "prestige" },
    { 0x32C, "prestigedoublexp" },
    { 0x32D, "prestigedoublexpmaxtimeplayed" },
    { 0x32E, "prestigeshoptokens" },
    { 0x32F, "prestigeshoptokensentitlement" },
    { 0x330, "prevanimdelta" },
    { 0x331, "prevnode" },
    { 0x332, "prevscript" },
    { 0x333, "primary" },
    { 0x334, "primaryattachment1" },
    { 0x335, "primaryattachment2" },
    { 0x336, "primaryattachment3" },
    { 0x337, "primaryattachments" },
    { 0x338, "primaryattachkit" },
    { 0x339, "primarycamo" },
    { 0x33A, "primaryfurniturekit" },
    { 0x33B, "primaryoffhand" },
    { 0x33C, "primaryreticle" },
    { 0x33D, "primaryweapon" },
    { 0x33E, "privatematchactivesquadmember" },
    { 0x33F, "privatematchcustomclasses" },
    { 0x340, "privatematchsquadmembers" },
    { 0x341, "projectile_impact" },
    { 0x342, "projectile_impact_player" },
    { 0x343, "prone" },
    { 0x344, "proneok" },
    { 0x345, "providecoveringfire" },
    { 0x346, "ps3" },
    { 0x347, "ps4" },
    { 0x348, "psoffsettime" },
    { 0x349, "pushable" },
    { 0x34A, "radaralwayson" },
    { 0x34B, "radarmode" },
    { 0x34C, "radarshowenemydirection" },
    { 0x34D, "radarstrength" },
    { 0x34E, "radius" },
    { 0x34F, "ragdoll_early_result" },
    { 0x350, "raise_riotshield" },
    { 0x351, "rank" },
    { 0x352, "rate" },
    { 0x353, "reached_end_node" },
    { 0x354, "reached_wait_node" },
    { 0x355, "reached_wait_speed" },
    { 0x356, "reactiontargetpos" },
    { 0x357, "realtimedelta" },
    { 0x358, "receiver" },
    { 0x359, "recipename" },
    { 0x35A, "reciprocality" },
    { 0x35B, "reflection_clear_color" },
    { 0x35C, "reinforcement" },
    { 0x35D, "relativedir" },
    { 0x35E, "relativeoffset" },
    { 0x35F, "reload" },
    { 0x360, "reload_start" },
    { 0x361, "remotemissilespawn" },
    { 0x362, "rendertotexture" },
    { 0x363, "reportindex" },
    { 0x364, "reports" },
    { 0x365, "reputation" },
    { 0x366, "requestarrivalnotify" },
    { 0x367, "requirement_beat100waves" },
    { 0x368, "requirement_beat200waves" },
    { 0x369, "requirement_beat50waves" },
    { 0x36A, "requirement_beatenzombies" },
    { 0x36B, "requirement_maxarmorproficiency" },
    { 0x36C, "requirement_maxweaponproficiency" },
    { 0x36D, "requirement_playedallmaps" },
    { 0x36E, "requirement_unlockedprison" },
    { 0x36F, "requirement_unlockedtier2" },
    { 0x370, "requirement_unlockedtier3" },
    { 0x371, "reserved" },
    { 0x372, "respawndelay" },
    { 0x373, "result" },
    { 0x374, "reticle" },
    { 0x375, "return_pitch" },
    { 0x376, "reverse" },
    { 0x377, "revives" },
    { 0x378, "right" },
    { 0x379, "rightaimlimit" },
    { 0x37A, "rightarc" },
    { 0x37B, "riotshield_damaged" },
    { 0x37C, "riotshield_hit" },
    { 0x37D, "rocket" },
    { 0x37E, "rocket_off" },
    { 0x37F, "rocket_on" },
    { 0x380, "rotatedone" },
    { 0x381, "rotation" },
    { 0x382, "run" },
    { 0x383, "runcost" },
    { 0x384, "runto_arrived" },
    { 0x385, "safetochangescript" },
    { 0x386, "scavenger" },
    { 0x387, "scope_cap" },
    { 0x388, "scope_center" },
    { 0x389, "scope_top" },
    { 0x38A, "score" },
    { 0x38B, "script" },
    { 0x38C, "script_brushmodel" },
    { 0x38D, "script_clut" },
    { 0x38E, "script_context" },
    { 0x38F, "script_delay" },
    { 0x390, "script_goal_changed" },
    { 0x391, "script_label" },
    { 0x392, "script_lightset" },
    { 0x393, "script_linkname" },
    { 0x394, "script_model" },
    { 0x395, "script_noteworthy" },
    { 0x396, "script_origin" },
    { 0x397, "script_parent" },
    { 0x398, "script_parentname" },
    { 0x399, "script_pushable" },
    { 0x39A, "script_vehicle" },
    { 0x39B, "script_vehicle_collision" },
    { 0x39C, "script_vehicle_collmap" },
    { 0x39D, "script_vehicle_corpse" },
    { 0x39E, "script_visionset" },
    { 0x39F, "script_water" },
    { 0x3A0, "script_reverb" },
    { 0x3A1, "script_zone" },
    { 0x3A2, "scriptable" },
    { 0x3A3, "scriptableactor" },
    { 0x3A4, "scripted_viewmodel_anim" },
    { 0x3A5, "scriptedarrivalent" },
    { 0x3A6, "search_end" },
    { 0x3A7, "secondary" },
    { 0x3A8, "secondaryattachment1" },
    { 0x3A9, "secondaryattachment2" },
    { 0x3AA, "secondaryattachments" },
    { 0x3AB, "secondaryattachkit" },
    { 0x3AC, "secondarycamo" },
    { 0x3AD, "secondaryfurniturekit" },
    { 0x3AE, "secondaryoffhand" },
    { 0x3AF, "secondaryreticle" },
    { 0x3B0, "secondaryweapon" },
    { 0x3B1, "sentry" },
    { 0x3B2, "sentry_manual" },
    { 0x3B3, "sentry_offline" },
    { 0x3B4, "servertimecount" },
    { 0x3B5, "servertimeexceedcount" },
    { 0x3B6, "servertimemax" },
    { 0x3B7, "servertimetotal" },
    { 0x3B8, "servertimetotalexceed" },
    { 0x3B9, "sessionstate" },
    { 0x3BA, "sessionteam" },
    { 0x3BB, "sharpturn" },
    { 0x3BC, "sharpturnlookaheaddist" },
    { 0x3BD, "sharpturnnotifydist" },
    { 0x3BE, "sharpturntooclosetodestdist" },
    { 0x3BF, "shirt" },
    { 0x3C0, "showinkillcam" },
    { 0x3C1, "showkillcam" },
    { 0x3C2, "sightlatency" },
    { 0x3C3, "silenced_shot" },
    { 0x3C4, "skill_points" },
    { 0x3C5, "skillbucket" },
    { 0x3C6, "skillrating" },
    { 0x3C7, "skillratingtype" },
    { 0x3C8, "slidevelocity" },
    { 0x3C9, "slowmo_active" },
    { 0x3CA, "slowmo_passive" },
    { 0x3CB, "smoke" },
    { 0x3CC, "snd_channelvolprio_holdbreath" },
    { 0x3CD, "snd_channelvolprio_pain" },
    { 0x3CE, "snd_channelvolprio_shellshock" },
    { 0x3CF, "snd_enveffectsprio_level" },
    { 0x3D0, "snd_enveffectsprio_shellshock" },
    { 0x3D1, "sort" },
    { 0x3D2, "sound_blend" },
    { 0x3D3, "soundeventdone" },
    { 0x3D4, "space" },
    { 0x3D5, "spawned" },
    { 0x3D6, "spawner" },
    { 0x3D7, "spawnflags" },
    { 0x3D8, "spawnpos" },
    { 0x3D9, "spawntime" },
    { 0x3DA, "specialgrenade" },
    { 0x3DB, "spectatekillcam" },
    { 0x3DC, "spectating_cycle" },
    { 0x3DD, "spectator" },
    { 0x3DE, "speechcommand" },
    { 0x3DF, "speed" },
    { 0x3E0, "splatter" },
    { 0x3E1, "splineplanereachednode" },
    { 0x3E2, "sprint_begin" },
    { 0x3E3, "sprint_end" },
    { 0x3E4, "sprint_slide_begin" },
    { 0x3E5, "sprint_slide_end" },
    { 0x3E6, "squad_base" },
    { 0x3E7, "squad_mode" },
    { 0x3E8, "squad_name" },
    { 0x3E9, "squadhq" },
    { 0x3EA, "squadmembers" },
    { 0x3EB, "squadmemxp" },
    { 0x3EC, "squadname" },
    { 0x3ED, "stairs" },
    { 0x3EE, "stairsstate" },
    { 0x3EF, "stand" },
    { 0x3F0, "start_blend" },
    { 0x3F1, "start_move" },
    { 0x3F2, "start_ragdoll" },
    { 0x3F3, "startdeaths" },
    { 0x3F4, "startdeploy_riotshield" },
    { 0x3F5, "startingoffsetforlife" },
    { 0x3F6, "startkills" },
    { 0x3F7, "state_changed" },
    { 0x3F8, "statelocked" },
    { 0x3F9, "stencil_disable" },
    { 0x3FA, "stencil_onesided" },
    { 0x3FB, "stencil_twosided" },
    { 0x3FC, "stencilfunc_always" },
    { 0x3FD, "stencilfunc_equal" },
    { 0x3FE, "stencilfunc_greater" },
    { 0x3FF, "stencilfunc_greaterequal" },
    { 0x400, "stencilfunc_less" },
    { 0x401, "stencilfunc_lessequal" },
    { 0x402, "stencilfunc_never" },
    { 0x403, "stencilfunc_notequal" },
    { 0x404, "stencilop_decr" },
    { 0x405, "stencilop_decrsat" },
    { 0x406, "stencilop_incr" },
    { 0x407, "stencilop_incrsat" },
    { 0x408, "stencilop_invert" },
    { 0x409, "stencilop_keep" },
    { 0x40A, "stencilop_replace" },
    { 0x40B, "stencilop_zero" },
    { 0x40C, "stop" },
    { 0x40D, "stop_soon" },
    { 0x40E, "stopanimdistsq" },
    { 0x40F, "stopsoonnotifydist" },
    { 0x410, "streak" },
    { 0x411, "streaktype" },
    { 0x412, "suckedashost" },
    { 0x413, "suncolor" },
    { 0x414, "sundirection" },
    { 0x415, "sunlight" },
    { 0x416, "support" },
    { 0x417, "support_level" },
    { 0x418, "suppression" },
    { 0x419, "suppression_end" },
    { 0x41A, "suppressionduration" },
    { 0x41B, "suppressionmeter" },
    { 0x41C, "suppressionstarttime" },
    { 0x41D, "suppressionTime" },
    { 0x41E, "suppressionwait" },
    { 0x41F, "surfacetype" },
    { 0x420, "surprisedbymedistsq" },
    { 0x421, "swimmer" },
    { 0x422, "switched_var_grenade" },
    { 0x423, "syncedmeleetarget" },
    { 0x424, "tactical" },
    { 0x425, "tag" },
    { 0x426, "tag_ai_aim_target" },
    { 0x427, "tag_aim" },
    { 0x428, "tag_aim_animated" },
    { 0x429, "tag_aim_pivot" },
    { 0x42A, "tag_barrel" },
    { 0x42B, "tag_blade_off" },
    { 0x42C, "tag_body" },
    { 0x42D, "tag_brass" },
    { 0x42E, "tag_brass_2" },
    { 0x42F, "tag_butt" },
    { 0x430, "tag_camera" },
    { 0x431, "tag_clip" },
    { 0x432, "tag_clip_dual" },
    { 0x433, "tag_clip_dual2" },
    { 0x434, "tag_detach" },
    { 0x435, "tag_engine_left" },
    { 0x436, "tag_engine_right" },
    { 0x437, "tag_eotech_reticle" },
    { 0x438, "tag_eye" },
    { 0x439, "tag_flash" },
    { 0x43A, "tag_flash_11" },
    { 0x43B, "tag_flash_2" },
    { 0x43C, "tag_flash_22" },
    { 0x43D, "tag_flash_3" },
    { 0x43E, "tag_flash_launcher" },
    { 0x43F, "tag_flash_silenced" },
    { 0x440, "tag_fx" },
    { 0x441, "tag_gasmask" },
    { 0x442, "tag_gasmask2" },
    { 0x443, "tag_ik_ankle_fl" },
    { 0x444, "tag_ik_ankle_fr" },
    { 0x445, "tag_ik_ankle_kl" },
    { 0x446, "tag_ik_ankle_kr" },
    { 0x447, "tag_ik_ankle_ml" },
    { 0x448, "tag_ik_ankle_mr" },
    { 0x449, "tag_ik_footflat_fl" },
    { 0x44A, "tag_ik_footflat_fr" },
    { 0x44B, "tag_ik_footflat_kl" },
    { 0x44C, "tag_ik_footflat_kr" },
    { 0x44D, "tag_ik_footflat_ml" },
    { 0x44E, "tag_ik_footflat_mr" },
    { 0x44F, "tag_ik_hip_fl" },
    { 0x450, "tag_ik_hip_fr" },
    { 0x451, "tag_ik_hip_kl" },
    { 0x452, "tag_ik_hip_kr" },
    { 0x453, "tag_ik_hip_ml" },
    { 0x454, "tag_ik_hip_mr" },
    { 0x455, "tag_ik_knee_fl" },
    { 0x456, "tag_ik_knee_fr" },
    { 0x457, "tag_ik_knee_kl" },
    { 0x458, "tag_ik_knee_kr" },
    { 0x459, "tag_ik_knee_ml" },
    { 0x45A, "tag_ik_knee_mr" },
    { 0x45B, "tag_ik_loc_le" },
    { 0x45C, "tag_ik_loc_le_foregrip" },
    { 0x45D, "tag_ik_loc_le_launcher" },
    { 0x45E, "tag_ik_loc_le_shotgun" },
    { 0x45F, "tag_ik_target" },
    { 0x460, "tag_inhand" },
    { 0x461, "tag_jetblast_fx" },
    { 0x462, "tag_jetpack" },
    { 0x463, "tag_knife_attach" },
    { 0x464, "tag_knife_fx" },
    { 0x465, "tag_laser" },
    { 0x466, "tag_launcher" },
    { 0x467, "tag_magnifier_eotech_reticle" },
    { 0x468, "tag_mobile_cover_upright" },
    { 0x469, "tag_motion_tracker_bl" },
    { 0x46A, "tag_motion_tracker_br" },
    { 0x46B, "tag_motion_tracker_fx" },
    { 0x46C, "tag_motion_tracker_tl" },
    { 0x46D, "tag_origin" },
    { 0x46E, "tag_player" },
    { 0x46F, "tag_popout" },
    { 0x470, "tag_rail_master_off" },
    { 0x471, "tag_rail_master_on" },
    { 0x472, "tag_rail_side_off" },
    { 0x473, "tag_rail_side_on" },
    { 0x474, "tag_reticle_acog" },
    { 0x475, "tag_reticle_default" },
    { 0x476, "tag_reticle_default2" },
    { 0x477, "tag_reticle_hamr" },
    { 0x478, "tag_reticle_on" },
    { 0x479, "tag_reticle_red_dot" },
    { 0x47A, "tag_reticle_reflex" },
    { 0x47B, "tag_reticle_tavor_scope" },
    { 0x47C, "tag_reticle_thermal_scope" },
    { 0x47D, "tag_rider" },
    { 0x47E, "tag_riot_shield" },
    { 0x47F, "tag_rocket" },
    { 0x480, "tag_scope_ads_off" },
    { 0x481, "tag_scope_ads_on" },
    { 0x482, "tag_shield_back" },
    { 0x483, "tag_shotgun" },
    { 0x484, "tag_show_alt" },
    { 0x485, "tag_sight_off" },
    { 0x486, "tag_sight_on" },
    { 0x487, "tag_stow_back_mid_attach" },
    { 0x488, "tag_stowed_back" },
    { 0x489, "tag_stowed_hip_rear" },
    { 0x48A, "tag_sync" },
    { 0x48B, "tag_tip" },
    { 0x48C, "tag_turret" },
    { 0x48D, "tag_turret_base" },
    { 0x48E, "tag_turret_pitch" },
    { 0x48F, "tag_turret_yaw" },
    { 0x490, "tag_weapon" },
    { 0x491, "tag_weapon_chest" },
    { 0x492, "tag_weapon_left" },
    { 0x493, "tag_weapon_right" },
    { 0x494, "tag_wheel_back_left" },
    { 0x495, "tag_wheel_back_right" },
    { 0x496, "tag_wheel_front_left" },
    { 0x497, "tag_wheel_front_right" },
    { 0x498, "tag_wheel_middle_left" },
    { 0x499, "tag_wheel_middle_right" },
    { 0x49A, "tag_wheel_spin_left01" },
    { 0x49B, "tag_wheel_spin_left02" },
    { 0x49C, "tag_wheel_spin_left03" },
    { 0x49D, "tag_wheel_spin_right01" },
    { 0x49E, "tag_wheel_spin_right02" },
    { 0x49F, "tag_wheel_spin_right03" },
    { 0x4A0, "takedamage" },
    { 0x4A1, "target" },
    { 0x4A2, "target_script_trigger" },
    { 0x4A3, "targetname" },
    { 0x4A4, "team" },
    { 0x4A5, "team3" },
    { 0x4A6, "teambalanced" },
    { 0x4A7, "teammode_axisallies" },
    { 0x4A8, "teammode_ffa" },
    { 0x4A9, "teammovewaittime" },
    { 0x4AA, "their_score" },
    { 0x4AB, "thermal" },
    { 0x4AC, "thermalbodymaterial" },
    { 0x4AD, "third_person" },
    { 0x4AE, "threatbias" },
    { 0x4AF, "threatbiasgroup" },
    { 0x4B0, "threatsightdelayenabled" },
    { 0x4B1, "threatsightdelayfalloff" },
    { 0x4B2, "threshold" },
    { 0x4B3, "throwingknife" },
    { 0x4B4, "time" },
    { 0x4B5, "timeplayedtotal" },
    { 0x4B6, "titlenew" },
    { 0x4B7, "titleunlocked" },
    { 0x4B8, "top" },
    { 0x4B9, "toparc" },
    { 0x4BA, "totalxp" },
    { 0x4BB, "touch" },
    { 0x4BC, "touching_platform" },
    { 0x4BD, "traverse_complete" },
    { 0x4BE, "traverse_soon" },
    { 0x4BF, "traversecost" },
    { 0x4C0, "traversesoonnotifydist" },
    { 0x4C1, "trend" },
    { 0x4C2, "trigger" },
    { 0x4C3, "trigger_damage" },
    { 0x4C4, "trigger_use" },
    { 0x4C5, "trigger_use_touch" },
    { 0x4C6, "truck_cam" },
    { 0x4C7, "turnrate" },
    { 0x4C8, "turret_deactivate" },
    { 0x4C9, "turret_fire" },
    { 0x4CA, "turret_no_vis" },
    { 0x4CB, "turret_not_on_target" },
    { 0x4CC, "turret_on_target" },
    { 0x4CD, "turret_on_vistarget" },
    { 0x4CE, "turret_pitch_clamped" },
    { 0x4CF, "turret_rotate_stopped" },
    { 0x4D0, "turret_yaw_clamped" },
    { 0x4D1, "turretinvulnerability" },
    { 0x4D2, "turretownerchange" },
    { 0x4D3, "turretstatechange" },
    { 0x4D4, "type" },
    { 0x4D5, "ucdidhigh" },
    { 0x4D6, "ucdidlow" },
    { 0x4D7, "unlockedcamo" },
    { 0x4D8, "unlockedreticles" },
    { 0x4D9, "unlockpoints" },
    { 0x4DA, "unresolved_collision" },
    { 0x4DB, "up" },
    { 0x4DC, "upaimlimit" },
    { 0x4DD, "upgradechallengeprogress" },
    { 0x4DE, "upgradechallengestage" },
    { 0x4DF, "upgradepoints" },
    { 0x4E0, "upgradepurchased" },
    { 0x4E1, "useable" },
    { 0x4E2, "usechokepoints" },
    { 0x4E3, "usecombatscriptatcover" },
    { 0x4E4, "usedemblemslots" },
    { 0x4E5, "useorcaavoidance" },
    { 0x4E6, "usepathsmoothingvalues" },
    { 0x4E7, "veh_boatbounce" },
    { 0x4E8, "veh_boost_activated" },
    { 0x4E9, "veh_boost_deactivated" },
    { 0x4EA, "veh_brake" },
    { 0x4EB, "veh_collision" },
    { 0x4EC, "veh_contact" },
    { 0x4ED, "veh_jolt" },
    { 0x4EE, "veh_landed" },
    { 0x4EF, "veh_leftground" },
    { 0x4F0, "veh_pathdir" },
    { 0x4F1, "veh_pathspeed" },
    { 0x4F2, "veh_pathtype" },
    { 0x4F3, "veh_predictedcollision" },
    { 0x4F4, "veh_speed" },
    { 0x4F5, "veh_throttle" },
    { 0x4F6, "veh_topspeed" },
    { 0x4F7, "veh_transmission" },
    { 0x4F8, "vehicle_dismount" },
    { 0x4F9, "vehicle_mount" },
    { 0x4FA, "vehicletype" },
    { 0x4FB, "velocity" },
    { 0x4FC, "vertalign" },
    { 0x4FD, "visionsetmissilecam" },
    { 0x4FE, "visionsetmissilecamduration" },
    { 0x4FF, "visionsetnaked" },
    { 0x500, "visionsetnakedduration" },
    { 0x501, "visionsetnight" },
    { 0x502, "visionsetnightduration" },
    { 0x503, "visionsetpain" },
    { 0x504, "visionsetpainduration" },
    { 0x505, "visionsetthermal" },
    { 0x506, "visionsetthermalduration" },
    { 0x507, "vote" },
    { 0x508, "wait" },
    { 0x509, "walk" },
    { 0x50A, "walkdist" },
    { 0x50B, "walkdistfacingmotion" },
    { 0x50C, "wastacticalinsertion" },
    { 0x50D, "waypoint_reached" },
    { 0x50E, "weapon" },
    { 0x50F, "weapon_change" },
    { 0x510, "weapon_dropped" },
    { 0x511, "weapon_fired" },
    { 0x512, "weapon_model_change" },
    { 0x513, "weapon_switch_invalid" },
    { 0x514, "weapon_switch_started" },
    { 0x515, "weapon_taken" },
    { 0x516, "weaponchange" },
    { 0x517, "weaponclassrestricted" },
    { 0x518, "weaponinfo" },
    { 0x519, "weaponrank" },
    { 0x51A, "weaponrestricted" },
    { 0x51B, "weaponsetups" },
    { 0x51C, "weaponstats" },
    { 0x51D, "weeklychallengeid" },
    { 0x51E, "weight" },
    { 0x51F, "width" },
    { 0x520, "wildcard1" },
    { 0x521, "wildcard2" },
    { 0x522, "wildcard3" },
    { 0x523, "wildcardslots" },
    { 0x524, "win_streak" },
    { 0x525, "winlossratio" },
    { 0x526, "wins" },
    { 0x527, "won_match" },
    { 0x528, "world" },
    { 0x529, "worldmodel" },
    { 0x52A, "worldspawn" },
    { 0x52B, "x" },
    { 0x52C, "xb3" },
    { 0x52D, "xenon" },
    { 0x52E, "xp" },
    { 0x52F, "xp_multiplier" },
    { 0x530, "xpmaxmultipliertimeplayed" },
    { 0x531, "xpmultiplier" },
    { 0x532, "xuid" },
    { 0x533, "y" },
    { 0x534, "yawconvergencetime" },
    { 0x535, "your_score" },
    { 0x536, "z" },
    { 0x537, "zonly_physics" },
*/
//
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
            token_map_rev.insert({ entry.second, entry.first });
        }
    }
};

__init__ _;

} // namespace xsk::gsc::h1

#ifdef _MSC_VER
#pragma warning(pop)
#endif

// ps4 function_list

/*
"createprintchannel"
"setprintchannel"
"print"
"println"
"print3d"
"line"
"box"
"orientedbox"
"sphere"
"cylinder"
"precacheturret"
"getweaponarray"
"spawnturret"
"canspawnturret"
"assert"
"assertex"
"assertmsg"
"isdefined"
"isvalidmissile"
"isstring"
"setomnvar"
"getomnvar"
"setdvar"
"setdynamicdvar"
"setdvarifuninitialized"
"setdevdvar"
"setdevdvarifuninitialized"
"getdvar"
"getdvarint"
"getdvarfloat"
"getdvarvector"
"gettime"
"gettimeutc"
"getradiometricunit"
"getentbynum"
"getweaponmodel"
"getweapondisplayname"
"getweaponbasename"
"getweaponattachments"
"getweaponattachmentdisplaynames"
"getweaponcamoname"
"getweaponreticlename"
"getanimlength"
"animhasnotetrack"
"getnotetracktimes"
"spawn"
"spawnloopsound"
"spawnloopingsound"
"bullettrace"
"bullettracepassed"
"sighttracepassed"
"physicstrace"
"playerphysicstrace"
"getgroundposition"
"getmovedelta"
"getangledelta"
"getnorthyaw"
"setnorthyaw"
"setslowmotion"
"randomint"
"randomfloat"
"randomintrange"
"randomfloatrange"
"sin"
"cos"
"tan"
"asin"
"acos"
"atan"
"int"
"float"
"abs"
"min"
"max"
"floor"
"ceil"
"exp"
"log"
"sqrt"
"squared"
"clamp"
"angleclamp"
"angleclamp180"
"vectorfromlinetopoint"
"pointonsegmentnearesttopoint"
"distance"
"distance2d"
"distancesquared"
"length"
"length2d"
"lengthsquared"
"length2dsquared"
"closer"
"vectordot"
"vectorcross"
"vectornormalize"
"vectortoangles"
"vectortoyaw"
"vectorlerp"
"axistoangles"
"anglestoup"
"anglestoright"
"anglestoforward"
"anglesdelta"
"combineangles"
"transformmove"
"rotatevector"
"rotatepointaroundvector"
"issubstr"
"isendstr"
"getsubstr"
"tolower"
"strtok"
"stricmp"
"ambientplay"
"ambientstop"
"precachemodel"
"precacheshellshock"
"precacheitem"
"precacheshader"
"precachestring"
"precachemenu"
"precacherumble"
"precachelocationselector"
"precacheleaderboards"
"loadfx"
"playfx"
"playfxontag"
"stopfxontag"
"killfxontag"
"playloopedfx"
"spawnfx"
"triggerfx"
"playfxontagforclients"
"setfxkillondelete"
"playimpactheadfatalfx"
"physicsexplosionsphere"
"physicsexplosioncylinder"
"physicsjolt"
"physicsjitter"
"setexpfog"
"setexpfogext"
"setexpfogdvarsonly"
"setexpfogextdvarsonly"
"setatmosfog"
"setatmosfogdvarsonly"
"isexplosivedamagemod"
"radiusdamage"
"setplayerignoreradiusdamage"
"glassradiusdamage"
"earthquake"
"getnumparts"
"getpartname"
"weaponfiretime"
"weaponclipsize"
"weaponisauto"
"weaponissemiauto"
"weaponisboltaction"
"weaponinheritsperks"
"weaponburstcount"
"weapontype"
"weaponclass"
"weaponinventorytype"
"weaponstartammo"
"weaponmaxammo"
"weaponaltweaponname"
"isweaponcliponly"
"isweapondetonationtimed"
"isweaponmanuallydetonatedbyemptythrow"
"weaponhasthermalscope"
"getvehiclenode"
"getvehiclenodearray"
"getallvehiclenodes"
"getnumvehicles"
"precachevehicle"
"spawnvehicle"
"vehicle_getarray"
"vehicle_getspawnerarray"
"playrumbleonposition"
"playrumblelooponposition"
"stopallrumbles"
"soundexists"
"openfile"
"closefile"
"fprintln"
"fprintfields"
"freadln"
"fgetarg"
"setminimap"
"setthermalbodymaterial"
"getarraykeys"
"getfirstarraykey"
"getnextarraykey"
"sortbydistance"
"tablelookup"
"tablelookupbyrow"
"tablelookupistring"
"tablelookupistringbyrow"
"tablelookuprownum"
"tableexists"
"getmissileowner"
"magicbullet"
"getweaponflashtagname"
"averagepoint"
"averagenormal"
"getglass"
"getglassarray"
"getglassorigin"
"isglassdestroyed"
"destroyglass"
"deleteglass"
"getdspbuscount"
"getdspbusname"
"objective_add"
"objective_delete"
"objective_state"
"objective_icon"
"objective_indentlevel"
"objective_position"
"objective_current"
"objective_onentity"
"objective_onentitywithrotation"
"objective_team"
"objective_player"
"objective_playerteam"
"objective_playerenemyteam"
"objective_playermask_hidefromall"
"objective_playermask_hidefrom"
"objective_playermask_showtoall"
"objective_playermask_showto"
"iprintln"
"iprintlnbold"
"logstring"
"getent"
"getentarray"
"getspawnarray"
"spawnplane"
"spawnstruct"
"spawnhelicopter"
"isalive"
"isspawner"
"missile_createattractorent"
"missile_createattractororigin"
"missile_createrepulsorent"
"missile_createrepulsororigin"
"missile_deleteattractor"
"playsoundatpos"
"newhudelem"
"newclienthudelem"
"newteamhudelem"
"resettimeout"
"isplayer"
"isplayernumber"
"setwinningteam"
"announcement"
"clientannouncement"
"setteammode"
"getteamscore"
"setteamscore"
"setclientnamemode"
"updateclientnames"
"getteamplayersalive"
"logprint"
"worldentnumber"
"obituary"
"positionwouldtelefrag"
"canspawn"
"getstarttime"
"precacheheadicon"
"precacheminimapicon"
"precachempanim"
"map_restart"
"exitlevel"
"addtestclient"
"addagent"
"setarchive"
"allclientsprint"
"clientprint"
"mapexists"
"isvalidgametype"
"matchend"
"setplayerteamrank"
"endparty"
"setteamradar"
"getteamradar"
"setteamradarstrength"
"getteamradarstrength"
"getuavstrengthmin"
"getuavstrengthmax"
"getuavstrengthlevelneutral"
"getuavstrengthlevelshowenemyfastsweep"
"getuavstrengthlevelshowenemydirectional"
"blockteamradar"
"unblockteamradar"
"isteamradarblocked"
"getassignedteam"
"setmatchdata"
"getmatchdata"
"sendmatchdata"
"clearmatchdata"
"setmatchdatadef"
"setmatchclientip"
"setmatchdataid"
"setclientmatchdata"
"getclientmatchdata"
"setclientmatchdatadef"
"sendclientmatchdata"
"getbuildversion"
"getbuildnumber"
"getsystemtime"
"getmatchrulesdata"
"isusingmatchrulesdata"
"kick"
"issplitscreen"
"setmapcenter"
"setgameendtime"
"visionsetnaked"
"visionsetnight"
"visionsetmissilecam"
"visionsetthermal"
"visionsetpain"
"endlobby"
"setac130ambience"
"getmapcustom"
"spawnsighttrace"
"incrementcounter"
"getcountertotal"
"getlevelticks"
"perlinnoise2d"
"calcrockingangles"
"reconevent"
"reconspatialevent"
"setsunflareposition"
"createthreatbiasgroup"
"threatbiasgroupexists"
"getthreatbias"
"setthreatbias"
"setthreatbiasagainstall"
"setignoremegroup"
"isenemyteam"
"objective_additionalentity"
"objective_state_nomessage"
"objective_string"
"objective_string_nomessage"
"objective_additionalposition"
"objective_current_nomessage"
"objective_additionalcurrent"
"objective_ring"
"objective_setpointertextoverride"
"getnode"
"getnodearray"
"getallnodes"
"getnodesinradius"
"getnodesinradiussorted"
"getclosestnodeinsight"
"getreflectionlocs"
"getreflectionreferencelocs"
"getvehicletracksegment"
"getvehicletracksegmentarray"
"getallvehicletracksegments"
"isarray"
"isai"
"getindexforluincstring"
"issentient"
"isgodmode"
"getdebugdvar"
"getdebugdvarint"
"getdebugdvarfloat"
"setsaveddvar"
"getfreeaicount"
"getaicount"
"getaiarray"
"getaispeciesarray"
"getspawnerarray"
"getcorpsearray"
"getspawnerteamarray"
"getweaponclipmodel"
"getbrushmodelcenter"
"getkeybinding"
"getcommandfromkey"
"getsticksconfig"
"weaponfightdist"
"weaponmaxdist"
"isturretactive"
"getturretfov"
"target_alloc"
"target_flush"
"target_set"
"target_remove"
"target_setshader"
"target_setoffscreenshader"
"target_isinrect"
"target_isincircle"
"target_startreticlelockon"
"target_clearreticlelockon"
"target_getarray"
"target_istarget"
"target_setattackmode"
"target_setjavelinonly"
"target_hidefromplayer"
"target_showtoplayer"
"target_setscaledrendermode"
"target_drawcornersonly"
"target_drawsquare"
"target_drawsingle"
"target_setminsize"
"target_setmaxsize"
"target_setcolor"
"target_setdelay"
"getstartorigin"
"getstartangles"
"getcycleoriginoffset"
"magicgrenade"
"magicgrenademanual"
"setblur"
"musicplay"
"musicstop"
"soundfade"
"addsoundsubmix"
"clearsoundsubmix"
"clearallsubmixes"
"blendsoundsubmix"
"makesoundsubmixsticky"
"makesoundsubmixunsticky"
"soundsettimescalefactor"
"soundresettimescale"
"levelsoundfade"
"precachenightvisioncodeassets"
"precachedigitaldistortcodeassets"
"precachesonarvisioncodeassets"
"precacheminimapsentrycodeassets"
"savegame"
"issavesuccessful"
"issaverecentlyloaded"
"savegamenocommit"
"commitsave"
"commitwouldbevalid"
"getfxvisibility"
"setculldist"
"getculldist"
"sethalfresparticles"
"getmapsunlight"
"setsunlight"
"resetsunlight"
"getmapsundirection"
"getmapsunangles"
"setsundirection"
"lerpsundirection"
"lerpsunangles"
"resetsundirection"
"enableforcedsunshadows"
"enableforcednosunshadows"
"disableforcedsunshadows"
"enableouterspacemodellighting"
"disableouterspacemodellighting"
"remapstage"
"changelevel"
"missionsuccess"
"missionfailed"
"cinematic"
"cinematicingame"
"cinematicingamesync"
"cinematicingameloop"
"cinematicingameloopresident"
"iscinematicplaying"
"stopcinematicingame"
"pausecinematicingame"
"drawcompassfriendlies"
"bulletspread"
"bullettracer"
"badplace_delete"
"badplace_cylinder"
"badplace_arc"
"badplace_brush"
"clearallcorpses"
"setturretnode"
"unsetturretnode"
"setnodepriority"
"isnodeoccupied"
"setdebugorigin"
"setdebugangles"
"updategamerprofile"
"updategamerprofileall"
"clearlocalizedstrings"
"setphysicsgravitydir"
"gettimescale"
"settimescale"
"setslowmotionview"
"teleportscene"
"forcesharedammo"
"refreshhudcompass"
"refreshhudammocounter"
"notifyoncommand"
"pow"
"atan2"
"botgetmemoryevents"
"botautoconnectenabled"
"botzonegetcount"
"botzonesetteam"
"botzonenearestcount"
"botmemoryflags"
"botflagmemoryevents"
"botzonegetindoorpercent"
"botsentientswap"
"isbot"
"isagent"
"getmaxagents"
"botdebugdrawtrigger"
"botgetclosestnavigablepoint"
"getnodesintrigger"
"nodesvisible"
"getnodesonpath"
"getzonecount"
"getzonenearest"
"getzonenodes"
"getzonepath"
"getzoneorigin"
"getnodezone"
"getzonenodesbydist"
"getzonenodeforindex"
"getweaponexplosionradius"
"markdangerousnodes"
"markdangerousnodesintrigger"
"nodeexposedtosky"
"findentrances"
"badplace_global"
"getpathdist"
"getlinkednodes"
"disconnectnodepair"
"connectnodepair"
"gettimesincelastpaused"
"precachefxontag"
"precachetag"
"precachesound"
"devsetminimapdvarsettings"
"loadtransient"
"unloadtransient"
"unloadalltransients"
"synctransients"
"aretransientsbusy"
"istransientqueued"
"istransientloaded"
"loadstartpointtransient"
"distance2dsquared"
"getangledelta3d"
"activateclientexploder"
"trajectorycalculateinitialvelocity"
"trajectorycalculateminimumvelocity"
"trajectorycalculateexitangle"
"trajectoryestimatedesiredinairtime"
"trajectorycomputedeltaheightattime"
"trajectorycanattemptaccuratejump"
"adddebugcommand"
"ispointinvolume"
"cinematicgettimeinmsec"
"cinematicgetframe"
"iscinematicloaded"
"bbprint"
"getenemysquaddata"
"lookupsoundlength"
"getscriptablearray"
"clearfog"
"setleveldopplerpreset"
"screenshake"
"isusinghdr"
"isusingssao"
"grantloot"
"playerphysicstraceinfo"
"getminchargetime"
"getchargetimepershot"
"getmaxchargeshots"
"weaponischargeable"
"weaponusesheat"
"lootserviceonendgame"
"luinotifyevent"
"lootserviceonstartgame"
"tournamentreportplayerspm"
"tournamentreportwinningteam"
"tournamentreportendofgame"
"wakeupphysicssphere"
"wakeupragdollsphere"
"dopplerpitch"
"piecewiselinearlookup"
"anglestoaxis"
"visionsetwater"
"sendscriptusageanalysisdata"
"resetscriptusageanalysisdata"
"instantlylogusageanalysisdata"
"invertangles"
"rotatevectorinverted"
"calculatestartorientation"
"droptoground"
"setdemigodmode"
"precachelaser"
"getcsplinecount"
"getcsplinepointcount"
"getcsplinelength"
"getcsplinepointid"
"getcsplinepointlabel"
"getcsplinepointtension"
"getcsplinepointposition"
"getcsplinepointcorridordims"
"getcsplinepointtangent"
"getcsplinepointdisttonextpoint"
"calccsplineposition"
"calccsplinetangent"
"calccsplinecorridor"
"setnojipscore"
"setnojiptime"
"getpredictedentityposition"
"gamedvrprohibitrecording"
"gamedvrstartrecording"
"gamedvrstoprecording"
"gamedvrsetvideometadata"
"gamedvrprohibitscreenshots"
"gamedvrsetscreenshotmetadata"
"queuedialog"
"speechenablegrammar"
"speechenable"
"livestreamingenable"
"livestreamingsetbitrate"
"livestreamingsetmetadata"
"livestreamingenablearchiving"
"triggerportableradarping"
"setglaregrimematerial"
"botgetteamlimit"
"spawnfxforclient"
"botgetteamdifficulty"
"debugstar"
"newdebughudelem"
"printlightsetsettings"
"lightsetdumpstate"
"getsquadassaultelo"
"loadluifile"
"isdedicatedserver"
"getplaylistversion"
"getplaylistid"
"getactiveclientcount"
"issquadsmode"
"getsquadassaultsquadindex"
"visionsetpostapply"
"addbot"
"ishairrunning"
"getnearbyarrayelements"
"vectorclamp"
"isalliedsentient"
"istestclient"
"getrandomnodedestination"
"debuglocalizestring"
"enablesoundcontextoverride"
"disablesoundcontextoverride"
"notifyoncommandremove"
"getsndaliasvalue"
"setsndaliasvalue"
"packedtablelookup"
"packedtablesectionlookup"
"packedtablelookupwithrange"
"grappletrace"
"stopclientexploder"
"closestpointstwosegs"
"isremovedentity"
"tablegetrowcount"
"tablegetcolumncount"
"batteryusepershot"
"batteryreqtouse"
"isweaponmanuallydetonatedbydoubletap"
"grapplegetmagnets"
"getweaponname"
"activatepersistentclientexploder"
"deployriotshield"
"validatecostume"
"randomcostume"
"shootblank"
"boidflockupdate"
"debuggetanimname"
"setspmatchdata"
"getspmatchdata"
"sendspmatchdata"
"clearspmatchdata"
"setspmatchdatadef"
"playcinematicforall"
"preloadcinematicforall"
"stopcinematicforall"
"capsuletracepassed"
"stopfxontagforclient"
"killfxontagforclient"
"isvector"
"notifychallengecomplete"
"lootservicestarttrackingplaytime"
"lootservicestoptrackingplaytime"
"lootservicevalidateplaytime"
"recordbreadcrumbdataforplayer"
"getweaponandattachmentmodels"
"changewhizbyautosimparams"
"sysprint"
"objective_mlgspectator"
"setspcheckpointdata"
"getspcheckpointdata"
"isnumber"
"isonlinegame"
"issystemlink"
"setsoundmasteringfadetime"
"getstanceandmotionstateforplayer"
"nodeisnotusable"
"nodesetnotusable"
"spawnlinkedfx"
"spawnlinkedfxforclient"
"getplaylistname"
"getlocaltimestring"
"isonwifi"
"getbuttonsconfig"
"getchallengeid"
"nodehasremotemissileset"
"nodegetremotemissilename"
"remotemissileenttracetooriginpassed"
"bombingruntracepassed"
"soundsettraceflags"
"handlepickupdeployedriotshield"
"getcodanywherecurrentplatform"
"getcostumefromtable"
"visionsetoverdrive"
"nodegetsplitgroup"
"recordbreadcrumbdataforplayersp"
"getchallengerewarditem"
"setentplayerxuidforemblem"
"resetentplayerxuidforemblems"
"nodesetremotemissilename"
"isshipbuild"
"strinsertnumericdelimiters"
"isscriptedagent"
"playfxonweapon"
"stopfxonweapon"
"killfxonweapon"
"getdefaultmaxfaceenemydistance"
"applyaccelerationonentity"
"applyimpulseonentity"
"setshaderconstant"
"getinventoryitemtype"
"getweaponmodelbounds"
"weaponitemplayidleanim"
"getstaticmodelcount"
"getstaticmodelname"
"getstaticmodelbounds"
"findstaticmodelindex"
"getdynentcount"
"getdynentmodelname"
"getdynentmodelbounds"
"finddynentwithmodelindex"
"getentitymodelname"
"getentitymodelbounds"
"findentitywithmodelindex"
*/

// ps4 method_list

/*
"attach"
"detach"
"detachall"
"getattachsize"
"getattachmodelname"
"getattachtagname"
"getattachignorecollision"
"hidepart"
"hidepart_allinstances"
"hideallparts"
"showpart"
"showallparts"
"linkto"
"linktoblendtotag"
"unlink"
"islinked"
"enablelinkto"
"playerlinkto"
"playerlinktodelta"
"playerlinkweaponviewtodelta"
"playerlinktoabsolute"
"playerlinktoblend"
"playerlinkedoffsetenable"
"playerlinkedoffsetdisable"
"playerlinkedsetviewznear"
"playerlinkedsetusebaseangleforviewclamp"
"lerpviewangleclamp"
"setviewangleresistance"
"springcamenabled"
"springcamdisabled"
"linktoplayerview"
"unlinkfromplayerview"
"geteye"
"istouching"
"getistouchingentities"
"stoploopsound"
"stopsounds"
"playrumbleonentity"
"playrumblelooponentity"
"stoprumble"
"delete"
"setmodel"
"laseron"
"laseroff"
"laseraltviewon"
"laseraltviewoff"
"thermalvisionon"
"thermalvisionoff"
"thermalvisionfofoverlayon"
"thermalvisionfofoverlayoff"
"autospotoverlayon"
"autospotoverlayoff"
"seteyesonuplinkenabled"
"setdamagefeedback"
"setcontents"
"makeusable"
"makeunusable"
"makeglobalusable"
"makeglobalunusable"
"setcursorhint"
"sethintstring"
"setsecondaryhintstring"
"forceusehinton"
"forceusehintoff"
"makesoft"
"makehard"
"willneverchange"
"startfiring"
"stopfiring"
"isfiringturret"
"startbarrelspin"
"stopbarrelspin"
"getbarrelspinrate"
"remotecontrolturret"
"remotecontrolturretoff"
"shootturret"
"getturretowner"
"setsentryowner"
"setsentrycarrier"
"setturretminimapvisible"
"settargetentity"
"snaptotargetentity"
"cleartargetentity"
"getturrettarget"
"setplayerspread"
"setaispread"
"setsuppressiontime"
"setconvergencetime"
"setconvergenceheightpercent"
"setturretteam"
"maketurretsolid"
"maketurretoperable"
"maketurretinoperable"
"setturretaccuracy"
"setrightarc"
"setleftarc"
"settoparc"
"setbottomarc"
"setautorotationdelay"
"setdefaultdroppitch"
"restoredefaultdroppitch"
"turretfiredisable"
"turretfireenable"
"setturretmodechangewait"
"usetriggerrequirelookat"
"getstance"
"setstance"
"itemweaponsetammo"
"getammocount"
"gettagorigin"
"gettagangles"
"shellshock"
"stunplayer"
"stopshellshock"
"fadeoutshellshock"
"setdepthoffield"
"setviewmodeldepthoffield"
"setmotionblurmovescale"
"setmotionblurturnscale"
"setmotionblurzoomscale"
"viewkick"
"localtoworldcoords"
"getentitynumber"
"getentityvelocity"
"enablegrenadetouchdamage"
"disablegrenadetouchdamage"
"enableaimassist"
"disableaimassist"
"radiusdamage"
"detonate"
"damageconetrace"
"sightconetrace"
"missile_settargetent"
"missile_settargetpos"
"missile_cleartarget"
"missile_setflightmodedirect"
"missile_setflightmodetop"
"getlightintensity"
"setlightintensity"
"isragdoll"
"setmovespeedscale"
"cameralinkto"
"cameraunlink"
"controlslinkto"
"controlsunlink"
"makevehiclesolidcapsule"
"teleportentityrelative"
"makevehiclesolidsphere"
"makevehiclesolid"
"remotecontrolvehicle"
"remotecontrolvehicleoff"
"isfiringvehicleturret"
"remotecontrolvehicletarget"
"remotecontrolvehicletargetoff"
"drivevehicleandcontrolturret"
"drivevehicleandcontrolturretoff"
"getplayersetting"
"getlocalplayerprofiledata"
"setlocalplayerprofiledata"
"remotecamerasoundscapeon"
"remotecamerasoundscapeoff"
"setmotiontrackervisible"
"getmotiontrackervisible"
"worldpointinreticle_circle"
"worldpointinreticle_rect"
"getpointinbounds"
"transfermarkstonewscriptmodel"
"setwatersheeting"
"addontoviewmodel"
"clearviewmodeladdons"
"setweaponhudiconoverride"
"getweaponhudiconoverride"
"setempjammed"
"playersetexpfog"
"playersetexpfogext"
"playersetatmosfog"
"isitemunlocked"
"getplayerdata"
"setplayerdata"
"getcacplayerdata"
"setcacplayerdata"
"trackerupdate"
"pingplayer"
"buttonpressed"
"sayall"
"sayteam"
"setspawnweapon"
"dropitem"
"dropscavengerbag"
"finishplayerdamage"
"suicide"
"closeingamemenu"
"iprintln"
"iprintlnbold"
"spawn"
"setentertime"
"cloneplayer"
"istalking"
"allowspectateteam"
"forcespectatepov"
"getguid"
"getxuid"
"getucdidhigh"
"getucdidlow"
"getclanidhigh"
"getclanidlow"
"ishost"
"getspectatingplayer"
"predictstreampos"
"updatescores"
"updatedmscores"
"setrank"
"setcardtitle"
"setcardicon"
"setcardnameplate"
"setcarddisplayslot"
"kc_regweaponforfxremoval"
"laststandrevive"
"startlaststand"
"setspectatedefaults"
"getthirdpersoncrosshairoffset"
"disableweaponpickup"
"enableweaponpickup"
"issplitscreenplayer"
"issplitscreenplayerprimary"
"markforeyeson"
"issighted"
"getsightedplayers"
"getplayerssightingme"
"getviewmodel"
"fragbuttonpressed"
"secondaryoffhandbuttonpressed"
"getcurrentweaponclipammo"
"setvelocity"
"getplayerviewheight"
"getnormalizedmovement"
"getnormalizedcameramovement"
"giveweapon"
"takeweapon"
"takeallweapons"
"getcurrentweapon"
"getcurrentprimaryweapon"
"getcurrentoffhand"
"hasweapon"
"switchtoweapon"
"switchtoweaponimmediate"
"gethybridsightenabled"
"switchtooffhand"
"givestartammo"
"givemaxammo"
"getfractionstartammo"
"getfractionmaxammo"
"isdualwielding"
"isreloading"
"isswitchingweapon"
"setorigin"
"getvelocity"
"setplayerangles"
"getplayerangles"
"usebuttonpressed"
"attackbuttonpressed"
"adsbuttonpressed"
"meleebuttonpressed"
"playerads"
"isonground"
"isusingturret"
"setviewmodel"
"setlethalweapon"
"getlethalweapon"
"settacticalweapon"
"gettacticalweapon"
"beginlocationselection"
"endlocationselection"
"disableweapons"
"enableweapons"
"disableoffhandweapons"
"enableoffhandweapons"
"disableweaponswitch"
"enableweaponswitch"
"openpopupmenu"
"openpopupmenunomouse"
"closepopupmenu"
"openmenu"
"closemenu"
"savematchrulestohistory"
"freezecontrols"
"disableusability"
"enableusability"
"setwhizbyspreads"
"setwhizbyradii"
"setreverb"
"deactivatereverb"
"setvolmod"
"playlocalsound"
"stoplocalsound"
"setweaponammoclip"
"setweaponammostock"
"getweaponammoclip"
"getweaponammostock"
"anyammoforweaponmodes"
"setclientomnvar"
"setclientdvar"
"setclientdvars"
"setclientspawnsighttraces"
"clientspawnsighttracepassed"
"allowads"
"allowjump"
"allowladder"
"allowmantle"
"allowsprint"
"setspreadoverride"
"resetspreadoverride"
"setaimspreadmovementscale"
"setactionslot"
"setviewkickscale"
"getviewkickscale"
"getweaponslistall"
"getweaponslistprimaries"
"getweaponslistoffhands"
"getweaponslistitems"
"getweaponslistexclusives"
"getweaponslist"
"canplayerplacesentry"
"canplayerplacetank"
"visionsetnakedforplayer"
"visionsetnightforplayer"
"visionsetmissilecamforplayer"
"visionsetthermalforplayer"
"visionsetpainforplayer"
"setblurforplayer"
"getplayerweaponmodel"
"getplayerknifemodel"
"updateentitywithweapons"
"notifyonplayercommand"
"canmantle"
"forcemantle"
"ismantling"
"playfx"
"player_recoilscaleon"
"player_recoilscaleoff"
"weaponlockstart"
"weaponlockfinalize"
"weaponlockfree"
"weaponlocktargettooclose"
"weaponlocknoclearance"
"visionsyncwithplayer"
"showhudsplash"
"setperk"
"hasperk"
"clearperks"
"unsetperk"
"registerparty"
"getfireteammembers"
"noclip"
"ufo"
"moveto"
"movex"
"movey"
"movez"
"movegravity"
"moveslide"
"stopmoveslide"
"rotateto"
"rotatepitch"
"rotateyaw"
"rotateroll"
"addpitch"
"addyaw"
"addroll"
"vibrate"
"rotatevelocity"
"solid"
"notsolid"
"setcandamage"
"setcanradiusdamage"
"physicslaunchclient"
"physicslaunchserver"
"physicslaunchserveritem"
"clonebrushmodeltoscriptmodel"
"scriptmodelplayanim"
"scriptmodelclearanim"
"scriptmodelplayanimdeltamotion"
"vehicle_teleport"
"attachpath"
"getattachpos"
"startpath"
"setswitchnode"
"setwaitspeed"
"vehicle_finishdamage"
"vehicle_setspeed"
"vehicle_setspeedimmediate"
"vehicle_rotateyaw"
"vehicle_getspeed"
"vehicle_getvelocity"
"vehicle_getbodyvelocity"
"vehicle_getsteering"
"vehicle_getthrottle"
"vehicle_turnengineoff"
"vehicle_turnengineon"
"vehicle_orientto"
"getgoalspeedmph"
"setacceleration"
"setdeceleration"
"resumespeed"
"setyawspeed"
"setyawspeedbyname"
"setmaxpitchroll"
"setairresistance"
"setturningability"
"setjitterparams"
"sethoverparams"
"joltbody"
"freevehicle"
"getwheelsurface"
"getvehicleowner"
"setvehiclelookattext"
"setvehicleteam"
"setneargoalnotifydist"
"setvehgoalpos"
"setgoalyaw"
"cleargoalyaw"
"settargetyaw"
"cleartargetyaw"
"vehicle_helisetai"
"setturrettargetvec"
"setturrettargetent"
"clearturrettarget"
"vehicle_canturrettargetpoint"
"setlookatent"
"clearlookatent"
"setvehweapon"
"fireweapon"
"vehicleturretcontrolon"
"vehicleturretcontroloff"
"isturretready"
"vehicledriveto"
"vehicle_dospawn"
"vehicle_isphysveh"
"vehphys_crash"
"vehphys_launch"
"vehphys_disablecrashing"
"vehphys_enablecrashing"
"vehphys_setspeed"
"vehphys_setconveyorbelt"
"freehelicopter"
"playerlinkedturretanglesenable"
"playerlinkedturretanglesdisable"
"playerlinkedvehicleanglesenable"
"playerlinkedvehicleanglesdisable"
"playersetstreamorigin"
"playerclearstreamorigin"
"nightvisionviewon"
"nightvisionviewoff"
"painvisionon"
"painvisionoff"
"getplayerintelisfound"
"setplayerintelfound"
"newpip"
"sethuddynlight"
"startscriptedanim"
"startcoverbehavior"
"startcoverarrival"
"starttraversearrival"
"checkcoverexitposwithpath"
"shoot"
"shootblank"
"melee"
"updateplayersightaccuracy"
"findshufflecovernode"
"findnearbycovernode"
"findcovernode"
"findbestcovernode"
"getcovernode"
"usecovernode"
"iscovervalidagainstenemy"
"reacquirestep"
"findreacquiredirectpath"
"trimpathtoattack"
"reacquiremove"
"findreacquireproximatepath"
"flagenemyunattackable"
"enterprone"
"exitprone"
"setproneanimnodes"
"updateprone"
"clearpitchorient"
"setlookatanimnodes"
"setlookat"
"setlookatentity"
"setlookatyawlimits"
"stoplookat"
"getmuzzlepos"
"getmuzzleangle"
"getmuzzlesideoffsetpos"
"getaimangle"
"canshoot"
"canshootenemy"
"cansee"
"seerecently"
"lastknowntime"
"lastknownpos"
"dropweapon"
"maymovetopoint"
"maymovefrompointtopoint"
"teleport"
"forceteleport"
"safeteleport"
"withinapproxpathdist"
"ispathdirect"
"allowedstances"
"isstanceallowed"
"issuppressionwaiting"
"issuppressed"
"ismovesuppressed"
"checkgrenadethrow"
"checkgrenadelaunch"
"checkgrenadelaunchpos"
"throwgrenade"
"pickupgrenade"
"useturret"
"stopuseturret"
"canuseturret"
"traversemode"
"animmode"
"orientmode"
"getmotionangle"
"shouldfacemotion"
"getanglestolikelyenemypath"
"setturretanim"
"getturret"
"getgroundenttype"
"forcestartnegotiation"
"setalienjumpcostscale"
"setalienruncostscale"
"setalientraversecostscale"
"animcustom"
"isinscriptedstate"
"canattackenemynode"
"getnegotiationstartnode"
"getnegotiationendnode"
"getnegotiationnextnode"
"getdoorpathnode"
"comparenodedirtopathdir"
"checkprone"
"pushplayer"
"checkgrenadethrowpos"
"setgoalnode"
"setgoalpos"
"setgoalentity"
"setgoalvolume"
"setgoalvolumeauto"
"getgoalvolume"
"cleargoalvolume"
"setfixednodesafevolume"
"getfixednodesafevolume"
"clearfixednodesafevolume"
"isingoal"
"setruntopos"
"nearnode"
"nearclaimnode"
"nearclaimnodeandangle"
"atdangerousnode"
"getisforcedincombat"
"setisforcedincombat"
"getenemyinfo"
"clearenemy"
"setentitytarget"
"clearentitytarget"
"setpotentialthreat"
"clearpotentialthreat"
"setflashbanged"
"setengagementmindist"
"setengagementmaxdist"
"isknownenemyinradius"
"isknownenemyinvolume"
"settalktospecies"
"invisiblenotsolid"
"visiblesolid"
"setdefaultaimlimits"
"initriotshieldhealth"
"getenemysqdist"
"getclosestenemysqdist"
"setthreatbiasgroup"
"getthreatbiasgroup"
"makeentitysentient"
"freeentitysentient"
"isindoor"
"getdroptofloorposition"
"isbadguy"
"animscripted"
"animscriptedthirdperson"
"animrelative"
"stopanimscripted"
"clearanim"
"setanimknob"
"setanimknoblimited"
"setanimknobrestart"
"setanimknoblimitedrestart"
"setanimknoball"
"setanimknoballlimited"
"setanimknoballrestart"
"setanimknoballlimitedrestart"
"setanim"
"setanimlimited"
"setanimrestart"
"setanimlimitedrestart"
"getanimtime"
"getanimweight"
"getanimassettype"
"setflaggedanimknob"
"setflaggedanimknoblimited"
"setflaggedanimknobrestart"
"setflaggedanimknoblimitedrestart"
"setflaggedanimknoball"
"setflaggedanimknoballrestart"
"setflaggedanim"
"setflaggedanimlimited"
"setflaggedanimrestart"
"setflaggedanimlimitedrestart"
"useanimtree"
"stopuseanimtree"
"setanimtime"
"allowstand"
"allowcrouch"
"allowprone"
"allowlean"
"allowswim"
"setocclusion"
"deactivateocclusion"
"deactivateallocclusion"
"isocclusionenabled"
"iseqenabled"
"seteq"
"seteqbands"
"deactivateeq"
"seteqlerp"
"islookingat"
"isthrowinggrenade"
"isfiring"
"ismeleeing"
"setautopickup"
"allowmelee"
"allowfire"
"enablehealthshield"
"enabledeathshield"
"nightvisiongogglesforceon"
"nightvisiongogglesforceoff"
"enableinvulnerability"
"disableinvulnerability"
"enablebreaching"
"disablebreaching"
"forceviewmodelanimation"
"disableturretdismount"
"enableturretdismount"
"uploadscore"
"uploadtime"
"uploadleaderboards"
"giveachievement"
"hidehud"
"showhud"
"mountvehicle"
"dismountvehicle"
"enableslowaim"
"disableslowaim"
"usehintsinvehicle"
"vehicleattackbuttonpressed"
"setwhizbyoffset"
"setwhizbyprobabilities"
"visionsetnakedforplayer_lerp"
"setwaitnode"
"returnplayercontrol"
"vehphys_starttrack"
"vehphys_clearautodisable"
"vehicleusealtblendedaudio"
"settext"
"clearalltextafterhudelem"
"setshader"
"settargetent"
"cleartargetent"
"settimer"
"settimerup"
"settimerstatic"
"settenthstimer"
"settenthstimerup"
"settenthstimerstatic"
"setclock"
"setclockup"
"setvalue"
"setwaypoint"
"setwaypointedgestyle_rotatingicon"
"setwaypointedgestyle_secondaryarrow"
"setwaypointiconoffscreenonly"
"fadeovertime"
"scaleovertime"
"moveovertime"
"reset"
"destroy"
"setpulsefx"
"setplayernamestring"
"changefontscaleovertime"
"startignoringspotlight"
"stopignoringspotlight"
"dontcastshadows"
"castshadows"
"setstablemissile"
"playersetgroundreferenceent"
"dontinterpolate"
"dospawn"
"stalingradspawn"
"getorigin"
"getcentroid"
"getshootatpos"
"getdebugeye"
"useby"
"playsound"
"playsoundevent"
"getsoundeventplayingonentity"
"setsoundeventparameter"
"stopsoundevent"
"playsoundatviewheight"
"prefetchsound"
"setpitch"
"scalepitch"
"setvolume"
"scalevolume"
"enableportalgroup"
"setspeakermapmonotostereo"
"setspeakermapmonoto51"
"setdistributed2dsound"
"playsoundasmaster"
"playloopsound"
"eqon"
"eqoff"
"haseq"
"iswaitingonsound"
"playfoley"
"getnormalhealth"
"setnormalhealth"
"dodamage"
"kill"
"show"
"hide"
"showonclient"
"hideonclient"
"disconnectpaths"
"connectpaths"
"disconnectnode"
"connectnode"
"startusingheroonlylighting"
"stopusingheroonlylighting"
"startusinglessfrequentlighting"
"stopusinglessfrequentlighting"
"setmovingplatformplayerturnrate"
"setthermalfog"
"setnightvisionfog"
"clearthermalfog"
"clearnightvisionfog"
"digitaldistortsetparams"
"setmode"
"getmode"
"setturretignoregoals"
"setturretcanaidetach"
"setturretfov"
"setplayerturretfov"
"lerpfov"
"lerpfovscale"
"getvalidcoverpeekouts"
"gethighestnodestance"
"doesnodeallowstance"
"doesnodeforcecombat"
"getgunangles"
"magicgrenade"
"magicgrenademanual"
"getentnum"
"launch"
"setsoundblend"
"makefakeai"
"spawndrone"
"setcorpseremovetimer"
"setlookattext"
"setspawnerteam"
"addaieventlistener"
"removeaieventlistener"
"getlightcolor"
"setlightcolor"
"getlightradius"
"setlightradius"
"getlightfovinner"
"getlightfovouter"
"setlightfovrange"
"getlightexponent"
"setlightexponent"
"startragdoll"
"startragdollfromimpact"
"queryshouldearlyragdoll"
"shouldearlyragdoll"
"logstring"
"laserhidefromclient"
"stopsounddspbus"
"thermaldrawenable"
"thermaldrawdisable"
"setturretdismountorg"
"setdamagestage"
"playsoundtoteam"
"playsoundtoplayer"
"playerhide"
"playershow"
"showtoplayer"
"threatdetectedtoplayer"
"clearthreatdetected"
"enableplayeruse"
"disableplayeruse"
"enableammogeneration"
"disableammogeneration"
"makescrambler"
"makeportableradar"
"clearscrambler"
"clearportableradar"
"placespawnpoint"
"setteamfortrigger"
"clientclaimtrigger"
"clientreleasetrigger"
"releaseclaimedtrigger"
"isusingonlinedataoffline"
"getrestedtime"
"sendleaderboards"
"isonladder"
"getcorpseanim"
"playerforcedeathanim"
"enablefocus"
"disablefocus"
"enableaudiozoom"
"disableaudiozoom"
"startac130"
"stopac130"
"enablemousesteer"
"setscriptmoverkillcam"
"usinggamepad"
"forcethirdpersonwhenfollowing"
"disableforcethirdpersonwhenfollowing"
"botsetflag"
"botsetstance"
"botsetscriptmove"
"botsetscriptgoal"
"botsetscriptgoalnode"
"botclearscriptgoal"
"botsetscriptenemy"
"botclearscriptenemy"
"botsetattacker"
"botgetscriptgoal"
"botgetscriptgoalradius"
"botgetscriptgoalyaw"
"botgetscriptgoaltype"
"botgetentrancepoint"
"botgetworldsize"
"botnodeavailable"
"botfindnoderandom"
"botmemoryevent"
"botmemoryselectpos"
"botnodepick"
"bothasscriptgoal"
"botgetpersonality"
"botthrowgrenade"
"botgetmemoryevents"
"botsetpersonality"
"botsetdifficulty"
"botgetdifficulty"
"botgetworldclosestedge"
"botlookatpoint"
"botpredictseepoint"
"botcanseeentity"
"botgetnodesonpath"
"botnodepickmultiple"
"botgetnearestnode"
"botgetfovdot"
"botsetawareness"
"botpursuingscriptgoal"
"botgetscriptgoalnode"
"botgetimperfectenemyinfo"
"botflagmemoryevents"
"botsetpathingstyle"
"botsetdifficultysetting"
"botgetdifficultysetting"
"botgetpathdist"
"botisrandomized"
"botpressbutton"
"botclearbutton"
"botnodescoremultiple"
"getnodenumber"
"setclientowner"
"setotherent"
"setaisightlinevisible"
"setentityowner"
"nodeisdisconnected"
"getnearestnode"
"makeentitynomeleetarget"
"isagent"
"spawnagent"
"finishagentdamage"
"setagentattacker"
"cloneagent"
"agentcanseesentient"
"scragentsetwaypoint"
"scragentsetgoalpos"
"scragentgetgoalpos"
"scragentsetgoalnode"
"scragentsetgoalentity"
"scragentsetgoalradius"
"scragentsetanimscale"
"scragentsetorientmode"
"scragentsetanimmode"
"scragentsetphysicsmode"
"scragentsetclipmode"
"scragentsetmaxturnspeed"
"scragentgetmaxturnspeed"
"scragentbeginmelee"
"scragentsetscripted"
"scragentdotrajectory"
"scragentdoanimlerp"
"scragentsetviewheight"
"scragentclaimnode"
"scragentrelinquishclaimednode"
"setradarping"
"setradarhighlight"
"setsonarvision"
"setharmonicbreach"
"setmaterialscriptparam"
"getaimassistdeltas"
"getaimassisttargetangles"
"getchargetime"
"overridereflectionprobe"
"defaultreflectionprobe"
"isholdinggrenade"
"isswitchinggrenade"
"ispreparinggrenade"
"setstencilstateoverride"
"clearstencilstateoverride"
"allowhighjump"
"isjumping"
"ishighjumping"
"vehicle_setvelocity"
"vehicle_addvelocity"
"getbraggingright"
"getmodelfromentity"
"getweaponheatlevel"
"isweaponoverheated"
"sprintbuttonpressed"
"vehicle_planethrottleoverride"
"vehicle_planethrottlereturncontrol"
"vehicle_planecrash"
"copyanimtreestate"
"lightsetforplayer"
"lightsetoverrideenableforplayer"
"lightsetoverridedisableforplayer"
"physicslaunchclientwithimpulse"
"setorcaavoidance"
"iswheelslipping"
"killnotification"
"setanimrate"
"setdoghandler"
"setdogcommand"
"setdogattackradius"
"isdogfollowinghandler"
"setdogmaxdrivespeed"
"isdogbeingdriven"
"setdogautoattackwhendriven"
"getdogattackbeginnode"
"setanimclass"
"enableanimstate"
"setanimstate"
"getanimentry"
"getanimentryname"
"getanimentryalias"
"getanimentrycount"
"pushplayervector"
"issprinting"
"playerlinkeduselinkedvelocity"
"shootstopsound"
"setclothtype"
"getclothmovesound"
"getequipmovesound"
"jumpbuttonpressed"
"rotateby"
"getlookaheaddir"
"getpathgoalpos"
"setrocketcorpse"
"setcorpsefalling"
"setsurfacetype"
"aiphysicstrace"
"aiphysicstracepassed"
"setdevtext"
"forcemovingplatformentity"
"setmovingplatformtrigger"
"visionsetstage"
"linkwaypointtotargetwithoffset"
"getlinkedparent"
"getmovingplatformparent"
"setnameplatematerial"
"retargetscriptmodellighting"
"setmantlesoundflavor"
"clearclienttriggeraudiozone"
"setclienttriggeraudiozone"
"makevehiclenotcollidewithplayers"
"getbobrate"
"setbobrate"
"setscriptablepartstate"
"stopsliding"
"cancelrocketcorpse"
"setdronegoalpos"
"hudoutlineenable"
"hudoutlinedisable"
"motionblurhqenable"
"motionblurhqdisable"
"screenshakeonentity"
"setpitchorient"
"worldpointtoscreenpos"
"linktoplayerviewignoreparentrot"
"shouldplaymeleedeathanim"
"botfirstavailablegrenade"
"visionsetwaterforplayer"
"setwatersurfacetransitionfx"
"linktoplayerviewfollowwatersurface"
"linktoplayerviewattachwatersurfacetransitioneffects"
"playersetwaterfog"
"emissiveblend"
"enableforceviewmodeldof"
"disableforceviewmodeldof"
"getcustomizationbody"
"getcustomizationhead"
"getcustomizationviewmodel"
"setviewmodeldepth"
"isenemyaware"
"hasenemybeenseen"
"physicssetmaxlinvel"
"physicssetmaxangvel"
"physicsgetlinvel"
"physicsgetlinspeed"
"physicsgetangvel"
"physicsgetangspeed"
"disablemissileboosting"
"enablemissileboosting"
"canspawntestclient"
"spawntestclient"
"loadcustomizationplayerview"
"setgrenadethrowscale"
"setgrenadecookscale"
"setplanesplineid"
"hudoutlineenableforclient"
"hudoutlinedisableforclient"
"hudoutlineenableforclients"
"hudoutlinedisableforclients"
"turretsetbarrelspinenabled"
"hasloadedcustomizationplayerview"
"setclienttriggeraudiozonelerp"
"setclienttriggeraudiozonepartial"
"scragentdoanimrelative"
"rotatetolinked"
"rotatebylinked"
"setlinkedangles"
"getcorpseentity"
"removefrommovingplatformsystem"
"logmatchdatalife"
"logmatchdatadeath"
"queuedialogforplayer"
"setmlgcameradefaults"
"ismlgspectator"
"disableautoreload"
"enableautoreload"
"issprintsliding"
"getlinkedchildren"
"botpredictenemycampspots"
"playsoundonmovingent"
"cancelmantle"
"hasfemalecustomizationmodel"
"loadviewweapons"
"setscriptabledamageowner"
"getscriptabletypeforentity"
"setfxkilldefondelete"
"getdogavoident"
"enabledogavoidance"
"enablehybridsight"
"lastknownreason"
"gettagindex"
"challengenotification"
"cancelaimove"
"vehicle_jetbikesethoverforcescale"
"linktosynchronizedparent"
"getclientomnvar"
"drawpostresolve"
"drawpostresolveoff"
"getcacplayerdataforgroup"
"cloakingenable"
"cloakingdisable"
"getunnormalizedcameramovement"
"getturretheat"
"isturretoverheated"
"vehicle_jetbikegetthrustfraction"
"vehicle_jetbikegetdragfraction"
"vehicle_jetbikegetantislipfraction"
"vehicle_jetbikegettotalrepulsorfraction"
"vehicle_assignbrushmodelcollision"
"vehicle_removebrushmodelcollision"
"vehicle_hovertanksethoverforcescale"
"forcesprint"
"forceads"
"forcedeathfall"
"gethybridscopestate"
"sethybridscopestate"
"getvieworigin"
"setweaponmodelvariant"
"ridevehicle"
"stopridingvehicle"
"getmantlesound"
"autoboltmissileeffects"
"disablemissilestick"
"enablemissilestick"
"setmissileminimapvisible"
"isoffhandweaponreadytothrow"
"isleaning"
"makecollidewithitemclip"
"ismovementfromgamepad"
"visionsetpostapplyforplayer"
"setlookattarget"
"clearlookattarget"
"overridematerial"
"overridematerialreset"
"overridetexture"
"overrideviewmodelmaterial"
"overrideviewmodelmaterialreset"
"enemyincrosshairs"
"setviewmodelmaterialscriptparam"
"vehicle_hovertankgetthrottleforce"
"vehicle_hovertankgetrepulsorforces"
"vehicle_hovertankgetantislipforce"
"vehicle_hovertankgetuprightingforce"
"vehicle_hovertankgetautoyawforce"
"getturretyawrate"
"getturretpitchrate"
"setclienttriggervisionset"
"overridelightingorigin"
"defaultlightingorigin"
"playdynamicambience"
"stopdynamicambience"
"isusinghandbrake"
"isusingboost"
"showviewmodel"
"hideviewmodel"
"setpickupweapon"
"playerlinkedmantleenable"
"allowpowerslide"
"allowhighjumpdrop"
"despawnagent"
"vehicle_setfakespeed"
"vehicle_jetbikesetthrustscale"
"agentclearscriptvars"
"scriptmodelplayanimdeltamotionfrompos"
"drawfacingentity"
"allowdodge"
"setcanspawnvehicleson"
"vehicle_setminimapvisible"
"setclutforplayer"
"setclutoverrideenableforplayer"
"setclutoverridedisableforplayer"
"setpainvisioneq"
"setplayermech"
"setdamagecallbackon"
"finishentitydamage"
"getlightshadowstate"
"setlightshadowstate"
"forceviewmodelanimationclear"
"designatefoftarget"
"sethintstringvisibleonlytoowner"
"notifyonplayercommandremove"
"canmantleex"
"allowboostjump"
"batterydischargebegin"
"batterydischargeend"
"batterydischargeonce"
"batterygetcharge"
"batterysetcharge"
"batteryfullrecharge"
"batterygetsize"
"batterysetdischargescale"
"batterygetdischargerate"
"batteryisinuse"
"enablephysicaldepthoffieldscripting"
"disablephysicaldepthoffieldscripting"
"setphysicaldepthoffield"
"setadsphysicaldepthoffield"
"vehicle_gettopspeed"
"gettoparc"
"getbottomarc"
"forcejump"
"vehicle_helicoptersetmaxangularvelocity"
"vehicle_helicoptersetmaxangularacceleration"
"setdemigod"
"attachnobuilddobj"
"setviewmodelanim"
"setviewmodelanimtime"
"pauseviewmodelanim"
"setadditiveviewmodelanim"
"activityfeedwriteingamepost"
"setcostumemodels"
"vehicle_getcurrentnode"
"setphysicalviewmodeldepthoffield"
"scriptmodelpauseanim"
"digitaldistortsetmaterial"
"disableoffhandsecondaryweapons"
"enableoffhandsecondaryweapons"
"canplaceriotshield"
"setriotshieldfailhint"
"enabledetonate"
"getdetonateenabled"
"playergetuseent"
"refreshshieldmodels"
"vehicle_diveboatissubmerged"
"scragentusemodelcollisionbounds"
"scragentsetwallruncost"
"getgravity"
"setgravityoverride"
"resetgravityoverride"
"vehphys_getvelocity"
"vehphys_isoffground"
"getjointype"
"vehicle_diveboatdive"
"addsoundmutedevice"
"removesoundmutedevice"
"clientaddsoundsubmix"
"clientclearsoundsubmix"
"clientclearallsubmixes"
"clientblendsoundsubmix"
"clientmakesoundsubmixsticky"
"clientmakesoundsubmixunsticky"
"clientenablesoundcontextoverride"
"clientdisablesoundcontextoverride"
"getthreatsightdelay"
"isusingoffhand"
"physicsstop"
"setremotehelicopterthrottlescale"
"actorusemodelcollisionbounds"
"setaxialmove"
"pathabilityadd"
"pathabilityremove"
"evaluatetrajectorydelta"
"rotateovertime"
"vehicle_diveboatenabledive"
"initwaterclienttrigger"
"getplayerweaponviewmodel"
"setturretheatwhenoverheating"
"setthreatdetection"
"setignorefoliagesightingme"
"loadcostumemodels"
"crouchbuttonpressed"
"disablealternatemelee"
"enablealternatemelee"
"hasblendshapes"
"getactiveanimations"
"hidepartviewmodel"
"luiopenmenu"
"screenpostoworldpoint"
"iscloaked"
"vehicleget3pcameraoffset"
"vehicleget3ppitchclamp"
"setstompbreakthrough"
"getstompbreakthrough"
"selfieaccessselfievalidflaginplayerdef"
"selfieaccessselfiecustomassetsarestreamed"
"selfieupdateselfieviewparameters"
"selfieinitializeselfieupdate"
"selfiescreenshottaken"
"selfieuploadcompleted"
"selfierestorebufferswaps"
"getsystemtimesp"
"setmissilecoasting"
"setmlgspectator"
"gettotalmpxp"
"turretsetgroundaimentity"
"hideweapontags"
"getweapondamagelocationmultiplier"
"setorbiterents"
"enablereload"
"isgroundentoverwater"
"setballpassallowed"
"consumereinforcement"
"ghost"
"loadweapons"
"playscheduledcinematicsound"
"setopaqueunlitforplayer"
"setwaypointiconfadeatcenter"
"setreinforcementhintstrings"
"enablecustomweaponcontext"
"disablecustomweaponcontext"
"setshadowrendering"
"playlocalannouncersound"
"setmissilespecialclipmask"
"vehicle_diveboatgetthrottleforce"
"vehicle_diveboatgetdragforce"
"isdodging"
"ispowersliding"
"getusableentity"
"getcurrentping"
"sethidetrigger"
"detonatebydoubletap"
"getnormalizedflick"
"getdwid"
"setplayerinfospmatchdata"
"physicsisactive"
"hasanimtree"
"isgod"
"setagentcostumeindex"
"visionsetoverdriveforplayer"
"issplitscreenotherplayerenemy"
"setowneroriginal"
"getlinkedtagname"
"forcefirstpersonwhenfollowed"
"disableforcefirstpersonwhenfollowed"
"setwaypointaerialtargeting"
"worldweaponsloaded"
"enablegrenadethrowback"
"usetriggertouchcheckstance"
"onlystreamactiveweapon"
"precachekillcamiconforweapon"
"selfierequestupdate"
"getclanwarsbonus"
"scragentsetspecies"
"scragentallowboost"
"scragentsetnopenetrate"
"finishplayerdamage_impactfx"
"finishagentdamage_impactfx"
"scragentsetorienttoground"
"scragentsetallowragdoll"
"scragentsetobstacleavoid"
"scragentsetlateralcodemove"
"scragentsetpathteamspread"
"isnotarget"
"setmovingplatformjitter"
"agentusescragentclipmask"
"setmeleechargevalid"
"ishighjumpallowed"
"setprestigemastery"
"agentsetfavoriteenemy"
"getpointinmodelbounds"
"setexomeleechargevalid"
"setdivision"
"setgrapplinghooktarget"
"scragentgetnodesonpath"
"addzmexploderbloodfx"
"sethighjumpresetallowed"
"scragentsetzombietype"
"getgroundentity"
"isnoclip"
"deleteonhostmigration"
"scragentgetphysicsmode"
"deathdropgrenade"
"stopsound"
"scragentsettraversenoderadius"
"scragentgettraversenoderadius"
"allowriotshieldplant"
"setstatic"
"scragentsynchronizeanims"
"settertiaryhintstring"
"scragentclearpath"
"scragenttrimpath"
"getsnapshotindexforclient"
"getsnapshotacknowledgedindexforclient"
"hasanimstate"
"movecomparison_enable"
"movecomparison_setbuttonpressed"
"movecomparison_setstickvalue"
"cloneclientasscriptmodel"
"disablerootmotion"
"playerlinktodeltablendviewangle"
"startweaponinspection"
"isinspectingweapon"
"luinotifyevent"
"luinotifyeventtospectators"
"enablequatinterpolationrotation"
"doesnodeforceidle"
"setisignoringgrenades"
*/


/*
{ 0x0000, "character/character_atlas_ar" },
{ 0x0000, "character/character_atlas_arctic_ar" },
{ 0x0000, "character/character_atlas_arctic_smg" },
{ 0x0000, "character/character_atlas_bodyguard_smg" },
{ 0x0000, "character/character_atlas_elete" },
{ 0x0000, "character/character_atlas_mech_pilot" },
{ 0x0000, "character/character_atlas_noexo" },
{ 0x0000, "character/character_atlas_pmc_estate_smg" },
{ 0x0000, "character/character_atlas_security_ar" },
{ 0x0000, "character/character_atlas_smg" },
{ 0x0000, "character/character_atlas_smg_lowlod" },
{ 0x0000, "character/character_casual_irons" },
{ 0x0000, "character/character_casual_irons_bet_holo" },
{ 0x0000, "character/character_civ_afr_dark_female_casual" },
{ 0x0000, "character/character_civ_afr_dark_female_dress" },
{ 0x0000, "character/character_civ_afr_dark_male_casual" },
{ 0x0000, "character/character_civ_afr_dark_male_dress" },
{ 0x0000, "character/character_civ_afr_drk_female_cas" },
{ 0x0000, "character/character_civ_afr_lgt_female_cas" },
{ 0x0000, "character/character_civ_afr_light_fem_drs_sml" },
{ 0x0000, "character/character_civ_afr_light_female_casual" },
{ 0x0000, "character/character_civ_afr_light_female_dress" },
{ 0x0000, "character/character_civ_afr_light_male_casual" },
{ 0x0000, "character/character_civ_afr_light_male_dress" },
{ 0x0000, "character/character_civ_afr_male_cas_grk" },
{ 0x0000, "character/character_civ_afr_male_drs_grk" },
{ 0x0000, "character/character_civ_african_male_b" },
{ 0x0000, "character/character_civ_african_male_c" },
{ 0x0000, "character/character_civ_african_male_d" },
{ 0x0000, "character/character_civ_asi_male_casual" },
{ 0x0000, "character/character_civ_asi_male_dress" },
{ 0x0000, "character/character_civ_cau_fem_drs_sml" },
{ 0x0000, "character/character_civ_cau_female_casual" },
{ 0x0000, "character/character_civ_cau_female_dress" },
{ 0x0000, "character/character_civ_cau_male_casual" },
{ 0x0000, "character/character_civ_cau_male_casual_ball1" },
{ 0x0000, "character/character_civ_cau_male_casual_ball2" },
{ 0x0000, "character/character_civ_cau_male_casual_grk" },
{ 0x0000, "character/character_civ_cau_male_dress" },
{ 0x0000, "character/character_civ_cau_male_dress_grk" },
{ 0x0000, "character/character_civ_mde_female_casual" },
{ 0x0000, "character/character_civ_mde_female_dress" },
{ 0x0000, "character/character_civ_mde_male_casual" },
{ 0x0000, "character/character_civ_mde_male_dress" },
{ 0x0000, "character/character_civ_pris_afr_dark_male_lite" },
{ 0x0000, "character/character_civ_pris_cau_male_lite" },
{ 0x0000, "character/character_civ_pris_mde_male_lite" },
{ 0x0000, "character/character_civ_rec_funeral_female_a" },
{ 0x0000, "character/character_civ_rec_funeral_female_b" },
{ 0x0000, "character/character_civ_rec_funeral_female_c" },
{ 0x0000, "character/character_civ_rec_funeral_female_d" },
{ 0x0000, "character/character_civ_rec_funeral_female_wife" },
{ 0x0000, "character/character_civ_rec_funeral_male" },
{ 0x0000, "character/character_civ_rec_funeral_male_afr" },
{ 0x0000, "character/character_civ_rec_funeral_male_afr_a" },
{ 0x0000, "character/character_civ_rec_funeral_male_afr_b" },
{ 0x0000, "character/character_civ_rec_funeral_male_afr_c" },
{ 0x0000, "character/character_civ_rec_funeral_male_afr_d" },
{ 0x0000, "character/character_civ_rec_funeral_male_asi_a" },
{ 0x0000, "character/character_civ_rec_funeral_male_cau_a" },
{ 0x0000, "character/character_civ_rec_funeral_male_cau_b" },
{ 0x0000, "character/character_civ_rec_funeral_male_cau_c" },
{ 0x0000, "character/character_civ_rec_funeral_male_cau_d" },
{ 0x0000, "character/character_civ_rec_funeral_male_cau_e" },
{ 0x0000, "character/character_civ_rec_funeral_male_cau_f" },
{ 0x0000, "character/character_civ_s1_female_a" },
{ 0x0000, "character/character_civ_s1_female_b" },
{ 0x0000, "character/character_civ_s1_female_c" },
{ 0x0000, "character/character_civ_s1_female_d" },
{ 0x0000, "character/character_civ_s1_female_dead_a" },
{ 0x0000, "character/character_civ_s1_female_dead_b" },
{ 0x0000, "character/character_civ_s1_female_e" },
{ 0x0000, "character/character_civ_s1_female_f" },
{ 0x0000, "character/character_civ_s1_female_g" },
{ 0x0000, "character/character_civ_s1_male_a" },
{ 0x0000, "character/character_civ_s1_male_b" },
{ 0x0000, "character/character_civ_s1_male_c" },
{ 0x0000, "character/character_civ_s1_male_d" },
{ 0x0000, "character/character_civ_s1_male_dead_a" },
{ 0x0000, "character/character_civ_s1_male_dead_b" },
{ 0x0000, "character/character_civ_s1_male_dead_c" },
{ 0x0000, "character/character_civ_s1_male_e" },
{ 0x0000, "character/character_civ_s1_male_hostage_lag" },
{ 0x0000, "character/character_civ_s1_worker_a" },
{ 0x0000, "character/character_civ_s1_worker_b" },
{ 0x0000, "character/character_civ_s1_worker_hardhat" },
{ 0x0000, "character/character_civ_scientist_s1_a" },
{ 0x0000, "character/character_civ_scientist_s1_b" },
{ 0x0000, "character/character_civ_scientist_s1_c" },
{ 0x0000, "character/character_civ_scientist_s1_d" },
{ 0x0000, "character/character_civ_scientist_s1_e" },
{ 0x0000, "character/character_civ_scientist_s1_f" },
{ 0x0000, "character/character_civ_seoul_female" },
{ 0x0000, "character/character_civ_seoul_male_a" },
{ 0x0000, "character/character_civ_seoul_male_b" },
{ 0x0000, "character/character_civ_seoul_male_d" },
{ 0x0000, "character/character_civ_seoul_male_e" },
{ 0x0000, "character/character_civ_seoul_male_f" },
{ 0x0000, "character/character_civ_seoul_male_principle" },
{ 0x0000, "character/character_civilian_africa_male_a" },
{ 0x0000, "character/character_civilian_africa_male_b" },
{ 0x0000, "character/character_civilian_africa_male_c" },
{ 0x0000, "character/character_civilian_india_female_a" },
{ 0x0000, "character/character_civilian_india_female_b" },
{ 0x0000, "character/character_civilian_india_male_a" },
{ 0x0000, "character/character_civilian_india_male_b" },
{ 0x0000, "character/character_civilian_india_male_c" },
{ 0x0000, "character/character_civilian_india_male_d" },
{ 0x0000, "character/character_civilian_prisoner_female_a" },
{ 0x0000, "character/character_civilian_prisoner_female_b" },
{ 0x0000, "character/character_civilian_slum_male_aa" },
{ 0x0000, "character/character_civilian_slum_male_aa_wht" },
{ 0x0000, "character/character_civilian_slum_male_ab" },
{ 0x0000, "character/character_civilian_slum_male_ab_wht" },
{ 0x0000, "character/character_civilian_slum_male_ba" },
{ 0x0000, "character/character_civilian_slum_male_ba_wht" },
{ 0x0000, "character/character_civilian_slum_male_bb" },
{ 0x0000, "character/character_civilian_slum_male_bb_wht" },
{ 0x0000, "character/character_civilian_worker_a" },
{ 0x0000, "character/character_civilian_worker_b" },
{ 0x0000, "character/character_civilian_worker_c" },
{ 0x0000, "character/character_coop_cloaked_static" },
{ 0x0000, "character/character_doctor" },
{ 0x0000, "character/character_doctor_cpt" },
{ 0x0000, "character/character_doctor_mwi" },
{ 0x0000, "character/character_doctor_mwi_holo" },
{ 0x0000, "character/character_doctor_pas" },
{ 0x0000, "character/character_dprk_ar" },
{ 0x0000, "character/character_dprk_shotgun" },
{ 0x0000, "character/character_dprk_smg" },
{ 0x0000, "character/character_hero_burke_b_atlas" },
{ 0x0000, "character/character_hero_burke_b_pmc" },
{ 0x0000, "character/character_hero_burke_sentinel" },
{ 0x0000, "character/character_hero_burke_sentinel_cloak" },
{ 0x0000, "character/character_hero_carter_pmc" },
{ 0x0000, "character/character_hero_cormack_captured" },
{ 0x0000, "character/character_hero_cormack_cloak" },
{ 0x0000, "character/character_hero_cormack_marine" },
{ 0x0000, "character/character_hero_cormack_marine_damaged" },
{ 0x0000, "character/character_hero_cormack_marine_dress" },
{ 0x0000, "character/character_hero_cormack_marine_seointro" },
{ 0x0000, "character/character_hero_cormack_sentinel" },
{ 0x0000, "character/character_hero_cormack_sentinel_arctic" },
{ 0x0000, "character/character_hero_cormack_sentinel_udt_b" },
{ 0x0000, "character/character_hero_cormack_sentinel_udtgr" },
{ 0x0000, "character/character_hero_gideon_atlas" },
{ 0x0000, "character/character_hero_gideon_atlas_arctic" },
{ 0x0000, "character/character_hero_gideon_atlas_pmc" },
{ 0x0000, "character/character_hero_gideon_atlas_pmc_mask" },
{ 0x0000, "character/character_hero_gideon_captured" },
{ 0x0000, "character/character_hero_gideon_pmc" },
{ 0x0000, "character/character_hero_gideon_sentinel_cloak" },
{ 0x0000, "character/character_hero_gideon_sentinel_finale" },
{ 0x0000, "character/character_hero_gideon_sentinel_jetpack" },
{ 0x0000, "character/character_hero_gideon_sentinel_pilot" },
{ 0x0000, "character/character_hero_ilana_atlas_pmc" },
{ 0x0000, "character/character_hero_ilana_captured" },
{ 0x0000, "character/character_hero_ilana_sentinel_arctic" },
{ 0x0000, "character/character_hero_ilana_sentinel_pilot" },
{ 0x0000, "character/character_hero_ilana_sentinel_udt_b" },
{ 0x0000, "character/character_hero_ilana_sentinel_udtgr" },
{ 0x0000, "character/character_hero_ilana_tourist" },
{ 0x0000, "character/character_hero_irons" },
{ 0x0000, "character/character_hero_joker_atlas" },
{ 0x0000, "character/character_hero_joker_atlas_pmc" },
{ 0x0000, "character/character_hero_knox_sentinel" },
{ 0x0000, "character/character_hero_knox_sentinel_cloak" },
{ 0x0000, "character/character_hero_knox_sentinel_det_cloak" },
{ 0x0000, "character/character_hero_knox_sentinel_jetpack" },
{ 0x0000, "character/character_hero_knox_sentinel_pilot" },
{ 0x0000, "character/character_hero_knox_sentinel_udt" },
{ 0x0000, "character/character_hero_knox_sentinel_udtgr" },
{ 0x0000, "character/character_hero_parker_atlas" },
{ 0x0000, "character/character_hero_will_marine" },
{ 0x0000, "character/character_hero_will_marine_seointro" },
{ 0x0000, "character/character_ie_doctor" },
{ 0x0000, "character/character_kva_ar" },
{ 0x0000, "character/character_kva_civ_a" },
{ 0x0000, "character/character_kva_civ_b" },
{ 0x0000, "character/character_kva_civ_c" },
{ 0x0000, "character/character_kva_hazmat" },
{ 0x0000, "character/character_kva_hazmat_nohat" },
{ 0x0000, "character/character_kva_leader_hades" },
{ 0x0000, "character/character_kva_lmg" },
{ 0x0000, "character/character_kva_shotgun" },
{ 0x0000, "character/character_kva_smg" },
{ 0x0000, "character/character_mech" },
{ 0x0000, "character/character_mech_long_lod" },
{ 0x0000, "character/character_mech_long_lod_baghdad" },
{ 0x0000, "character/character_mech_scaled" },
{ 0x0000, "character/character_navy_sf_assault_a" },
{ 0x0000, "character/character_navy_sf_assault_b" },
{ 0x0000, "character/character_navy_sf_assault_c" },
{ 0x0000, "character/character_nigerian_army" },
{ 0x0000, "character/character_nigerian_general" },
{ 0x0000, "character/character_nigerian_prime_minister" },
{ 0x0000, "character/character_pmc_ar" },
{ 0x0000, "character/character_pmc_ar_lowlod" },
{ 0x0000, "character/character_pmc_cap_ar" },
{ 0x0000, "character/character_pmc_noexo" },
{ 0x0000, "character/character_pmc_noexo_rec_driver" },
{ 0x0000, "character/character_pmc_smg" },
{ 0x0000, "character/character_pmc_smg_asi" },
{ 0x0000, "character/character_potus" },
{ 0x0000, "character/character_sentinel" },
{ 0x0000, "character/character_sentinel_arctic_ar" },
{ 0x0000, "character/character_sentinel_cloak" },
{ 0x0000, "character/character_sentinel_ie" },
{ 0x0000, "character/character_sentinel_ie_land" },
{ 0x0000, "character/character_sentinel_soldier_cloaked" },
{ 0x0000, "character/character_sf_police_a" },
{ 0x0000, "character/character_sf_police_b" },
{ 0x0000, "character/character_sf_police_c" },
{ 0x0000, "character/character_sp_doberman_dog" },
{ 0x0000, "character/character_sp_usmc_at4" },
{ 0x0000, "character/character_sp_usmc_james" },
{ 0x0000, "character/character_sp_usmc_ryan" },
{ 0x0000, "character/character_sp_usmc_sami" },
{ 0x0000, "character/character_sp_usmc_sami_goggles" },
{ 0x0000, "character/character_sp_usmc_zach" },
{ 0x0000, "character/character_sp_usmc_zach_goggles" },
{ 0x0000, "character/character_us_marine_ar" },
{ 0x0000, "character/character_us_marine_ar_lowlod" },
{ 0x0000, "character/character_us_marine_dress" },
{ 0x0000, "character/character_us_marine_dress_a" },
{ 0x0000, "character/character_us_marine_dress_b" },
{ 0x0000, "character/character_us_marine_dress_c" },
{ 0x0000, "character/character_us_marine_dress_d" },
{ 0x0000, "character/character_us_marine_dress_e" },
{ 0x0000, "character/character_us_marine_dress_f" },
{ 0x0000, "character/character_us_marine_dress_lowlod" },
{ 0x0000, "character/character_us_marine_seofob_ar" },
{ 0x0000, "character/character_us_marine_shotgun_lowlod" },
{ 0x0000, "character/character_us_marine_smg" },
{ 0x0000, "character/character_us_marine_smg_lowlod" },
{ 0x0000, "character/character_us_marine_smg_seo" },
{ 0x0000, "character/character_us_marine_smg_seointro" },
{ 0x0000, "character/mp_character_cloak_test" },
{ 0x0000, "character/mp_character_sentinel" },

{ 0xA4EF, "codescripts/character" },
{ 0xA4F0, "common_scripts/_artcommon" },
{ 0xA4F1, "common_scripts/_bcs_location_trigs" },
{ 0xA4F2, "common_scripts/_createfx" },
{ 0xA4F3, "common_scripts/_createfxmenu" },
{ 0xA4F4, "common_scripts/_destructible" },
{ 0xA4F5, "common_scripts/_dynamic_world" },
{ 0xA4F6, "common_scripts/_elevator" },
{ 0xA4F7, "common_scripts/_exploder" },
{ 0xA4F8, "common_scripts/_fx" },
{ 0xA4F9, "common_scripts/_pipes" },
{ 0xA4FA, "common_scripts/utility" },

{ 0x0000, "destructible_scripts/computer_01_destp" },
{ 0x0000, "destructible_scripts/container_plastic_72x56x48_01_destp" },
{ 0x0000, "destructible_scripts/container_plastic_beige_med_01_destp" },
{ 0x0000, "destructible_scripts/greece_spinning_displays" },
{ 0x0000, "destructible_scripts/powerbox_112x64_01_green_destp" },
{ 0x0000, "destructible_scripts/security_camera_scanner_destp" },
{ 0x0000, "destructible_scripts/toy_chicken" },
{ 0x0000, "destructible_scripts/toy_chicken_common" },
{ 0x0000, "destructible_scripts/toy_electricbox4" },
{ 0x0000, "destructible_scripts/toy_generator" },
{ 0x0000, "destructible_scripts/toy_generator_on" },
{ 0x0000, "destructible_scripts/toy_locker_double" },
{ 0x0000, "destructible_scripts/vehicle_civ_domestic_sedan_01_glass" },
{ 0x0000, "destructible_scripts/vehicle_civ_domestic_sedan_police_destpv" },
{ 0x0000, "destructible_scripts/vehicle_civ_domestic_sedan_taxi_glass" },
{ 0x0000, "destructible_scripts/vehicle_civ_smartcar_destpv" },
{ 0x0000, "destructible_scripts/vehicle_luxurysedan" },
{ 0x0000, "destructible_scripts/vehicle_luxurysedan_2008" },
{ 0x0000, "destructible_scripts/vehicle_pickup" },
{ 0x0000, "destructible_scripts/vehicle_suv_atlas_destpv" },
{ 0x0000, "destructible_scripts/wall_firebox_destp" },
{ 0x0000, "maps/_anim" },
{ 0x0000, "maps/_animatedmodels" },
{ 0x0000, "maps/_ar_view" },
{ 0x0000, "maps/_art" },
{ 0x0000, "maps/_autosave" },
{ 0x0000, "maps/_bobbing_boats" },
{ 0x0000, "maps/_breach" },
{ 0x0000, "maps/_car_door_shield" },
{ 0x0000, "maps/_cg_encounter_perf_monitor" },
{ 0x0000, "maps/_chargeable_weapon" },
{ 0x0000, "maps/_cloak" },
{ 0x0000, "maps/_cloak_enemy_behavior" },
{ 0x0000, "maps/_colors" },
{ 0x0000, "maps/_compass" },
{ 0x0000, "maps/_controlled_orbiting_drone" },
{ 0x0000, "maps/_controlled_sniperdrone" },
{ 0x0000, "maps/_coop" },
{ 0x0000, "maps/_createfx" },
{ 0x0000, "maps/_credits" },
{ 0x0000, "maps/_credits_autogen" },
{ 0x0000, "maps/_damagefeedback" },
{ 0x0000, "maps/_dds" },
{ 0x0000, "maps/_debug" },
{ 0x0000, "maps/_deployablecoverai" },
{ 0x0000, "maps/_detonategrenades" },
{ 0x0000, "maps/_dog_control" },
{ 0x0000, "maps/_dog_kinect" },
{ 0x0000, "maps/_drone" },
{ 0x0000, "maps/_drone_ai" },
{ 0x0000, "maps/_drone_base" },
{ 0x0000, "maps/_drone_civilian" },
{ 0x0000, "maps/_dshk_player" },
{ 0x0000, "maps/_endmission" },
{ 0x0000, "maps/_exo_climb" },
{ 0x0000, "maps/_exo_punch_door" },
{ 0x0000, "maps/_exo_shield_sp" },
{ 0x0000, "maps/_flashlight_cheap" },
{ 0x0000, "maps/_foam_bomb" },
{ 0x0000, "maps/_friendlyfire" },
{ 0x0000, "maps/_gameskill" },
{ 0x0000, "maps/_global_fx" },
{ 0x0000, "maps/_global_fx_code" },
{ 0x0000, "maps/_grapple" },
{ 0x0000, "maps/_grapple_anim" },
{ 0x0000, "maps/_grapple_traverse" },
{ 0x0000, "maps/_hand_signals" },
{ 0x0000, "maps/_helicopter_ai" },
{ 0x0000, "maps/_helicopter_globals" },
{ 0x0000, "maps/_high_speed_clouds" },
{ 0x0000, "maps/_hms_ai_utility" },
{ 0x0000, "maps/_hms_door_interact" },
{ 0x0000, "maps/_hms_greece_civilian" },
{ 0x0000, "maps/_hms_utility" },
{ 0x0000, "maps/_hud" },
{ 0x0000, "maps/_hud_util" },
{ 0x0000, "maps/_idle" },
{ 0x0000, "maps/_idle_phone" },
{ 0x0000, "maps/_idle_smoke" },
{ 0x0000, "maps/_intelligence" },
{ 0x0000, "maps/_introscreen" },
{ 0x0000, "maps/_inventory" },
{ 0x0000, "maps/_juggernaut" },
{ 0x0000, "maps/_lighting" },
{ 0x0000, "maps/_lights" },
{ 0x0000, "maps/_load" },
{ 0x0000, "maps/_loadout" },
{ 0x0000, "maps/_loadout_code" },
{ 0x0000, "maps/_mark_and_execute" },
{ 0x0000, "maps/_mech" },
{ 0x0000, "maps/_mech_aud" },
{ 0x0000, "maps/_mech_grapple" },
{ 0x0000, "maps/_mg_penetration" },
{ 0x0000, "maps/_mgturret" },
{ 0x0000, "maps/_mgturret_auto_nonai" },
{ 0x0000, "maps/_microdronelauncher" },
{ 0x0000, "maps/_microwave_grenade" },
{ 0x0000, "maps/_mocap_ar" },
{ 0x0000, "maps/_names" },
{ 0x0000, "maps/_nightvision" },
{ 0x0000, "maps/_patrol" },
{ 0x0000, "maps/_patrol_anims" },
{ 0x0000, "maps/_patrol_anims_active" },
{ 0x0000, "maps/_patrol_anims_casualkiller" },
{ 0x0000, "maps/_patrol_anims_creepwalk" },
{ 0x0000, "maps/_patrol_anims_patroljog" },
{ 0x0000, "maps/_patrol_cold_anims" },
{ 0x0000, "maps/_patrol_extended" },
{ 0x0000, "maps/_player_boost_dash" },
{ 0x0000, "maps/_player_boost_jump_anims" },
{ 0x0000, "maps/_player_boost_jump_aud" },
{ 0x0000, "maps/_player_death" },
{ 0x0000, "maps/_player_exo" },
{ 0x0000, "maps/_player_fastzip" },
{ 0x0000, "maps/_player_high_jump" },
{ 0x0000, "maps/_player_land_assist" },
{ 0x0000, "maps/_player_stats" },
{ 0x0000, "maps/_playermech_code" },
{ 0x0000, "maps/_pmove" },
{ 0x0000, "maps/_president" },
{ 0x0000, "maps/_props" },
{ 0x0000, "maps/_rambo" },
{ 0x0000, "maps/_riotshield" },
{ 0x0000, "maps/_sarray" },
{ 0x0000, "maps/_shg_anim" },
{ 0x0000, "maps/_shg_debug" },
{ 0x0000, "maps/_shg_design_tools" },
{ 0x0000, "maps/_shg_fx" },
{ 0x0000, "maps/_shg_utility" },
{ 0x0000, "maps/_slowmo_breach" },
{ 0x0000, "maps/_sniper_glint" },
{ 0x0000, "maps/_sniper_setup_ai" },
{ 0x0000, "maps/_sonicaoe" },
{ 0x0000, "maps/_sp_matchdata" },
{ 0x0000, "maps/_spawner" },
{ 0x0000, "maps/_stealth" },
{ 0x0000, "maps/_stealth_accuracy_friendly" },
{ 0x0000, "maps/_stealth_animation_funcs" },
{ 0x0000, "maps/_stealth_anims" },
{ 0x0000, "maps/_stealth_behavior_enemy" },
{ 0x0000, "maps/_stealth_behavior_friendly" },
{ 0x0000, "maps/_stealth_behavior_system" },
{ 0x0000, "maps/_stealth_color_friendly" },
{ 0x0000, "maps/_stealth_corpse_enemy" },
{ 0x0000, "maps/_stealth_corpse_system" },
{ 0x0000, "maps/_stealth_debug" },
{ 0x0000, "maps/_stealth_display" },
{ 0x0000, "maps/_stealth_event_enemy" },
{ 0x0000, "maps/_stealth_shared_utilities" },
{ 0x0000, "maps/_stealth_smartstance_friendly" },
{ 0x0000, "maps/_stealth_threat_enemy" },
{ 0x0000, "maps/_stealth_utility" },
{ 0x0000, "maps/_stealth_visibility_enemy" },
{ 0x0000, "maps/_stealth_visibility_friendly" },
{ 0x0000, "maps/_stealth_visibility_system" },
{ 0x0000, "maps/_stingerm7" },
{ 0x0000, "maps/_stingerm7_greece" },
{ 0x0000, "maps/_swim_ai" },
{ 0x0000, "maps/_swim_ai_common" },
{ 0x0000, "maps/_swim_player" },
{ 0x0000, "maps/_tagging" },
{ 0x0000, "maps/_target_lock" },
{ 0x0000, "maps/_treadfx" },
{ 0x0000, "maps/_trigger" },
{ 0x0000, "maps/_underwater" },
{ 0x0000, "maps/_upgrade_challenge" },
{ 0x0000, "maps/_upgrade_perks" },
{ 0x0000, "maps/_upgrade_system" },
{ 0x0000, "maps/_urgent_walk" },
{ 0x0000, "maps/_utility" },
{ 0x0000, "maps/_utility_code" },
{ 0x0000, "maps/_utility_dogs" },
{ 0x0000, "maps/_variable_grenade" },
{ 0x0000, "maps/_vehicle" },
{ 0x0000, "maps/_vehicle_aianim" },
{ 0x0000, "maps/_vehicle_code" },
{ 0x0000, "maps/_vehicle_free_drive" },
{ 0x0000, "maps/_vehicle_missile" },
{ 0x0000, "maps/_vehicle_shg" },
{ 0x0000, "maps/_vehicle_traffic" },
{ 0x0000, "maps/_vignette_util" },
{ 0x0000, "maps/_warzone_tactics" },
{ 0x0000, "maps/_water" },
{ 0x0000, "maps/_weapon_pdrone" },
{ 0x0000, "maps/_weather" },
{ 0x0000, "maps/betrayal_fx" },
{ 0x0000, "maps/betrayal_precache" },
{ 0x0000, "maps/captured_fx" },
{ 0x0000, "maps/captured_precache" },
{ 0x0000, "maps/crash_fx" },
{ 0x0000, "maps/crash_precache" },
{ 0x0000, "maps/credits_s1_fx" },
{ 0x0000, "maps/credits_s1_precache" },
{ 0x0000, "maps/detroit_fx" },
{ 0x0000, "maps/detroit_precache" },
{ 0x0000, "maps/df_baghdad_fx" },
{ 0x0000, "maps/df_baghdad_precache" },
{ 0x0000, "maps/df_fly_fx" },
{ 0x0000, "maps/df_fly_precache" },
{ 0x0000, "maps/finale_fx" },
{ 0x0000, "maps/finale_precache" },
{ 0x0000, "maps/fusion_fx" },
{ 0x0000, "maps/fusion_precache" },
{ 0x0000, "maps/greece_conf_center_fx" },
{ 0x0000, "maps/greece_ending_fx" },
{ 0x0000, "maps/greece_fx" },
{ 0x0000, "maps/greece_precache" },
{ 0x0000, "maps/greece_safehouse_fx" },
{ 0x0000, "maps/greece_sniper_scramble_fx" },
{ 0x0000, "maps/irons_estate_fx" },
{ 0x0000, "maps/irons_estate_precache" },
{ 0x0000, "maps/lab_fx" },
{ 0x0000, "maps/lab_precache" },
{ 0x0000, "maps/lagos_fx" },
{ 0x0000, "maps/lagos_precache" },
{ 0x0000, "maps/recovery_fx" },
{ 0x0000, "maps/recovery_precache" },
{ 0x0000, "maps/sanfran_b_fx" },
{ 0x0000, "maps/sanfran_b_precache" },
{ 0x0000, "maps/sanfran_fx" },
{ 0x0000, "maps/sanfran_precache" },
{ 0x0000, "maps/seoul_fx" },
{ 0x0000, "maps/seoul_precache" },
{ 0x0000, "mptype/mptype_cloak_test" },
{ 0x0000, "soundscripts/_ambient" },
{ 0x0000, "soundscripts/_audio" },
{ 0x0000, "soundscripts/_audio_dynamic_ambi" },
{ 0x0000, "soundscripts/_audio_mix_manager" },
{ 0x0000, "soundscripts/_audio_music" },
{ 0x0000, "soundscripts/_audio_presets_music" },
{ 0x0000, "soundscripts/_audio_presets_vehicles" },
{ 0x0000, "soundscripts/_audio_reverb" },
{ 0x0000, "soundscripts/_audio_stream_manager" },
{ 0x0000, "soundscripts/_audio_vehicle_manager" },
{ 0x0000, "soundscripts/_audio_vehicles" },
{ 0x0000, "soundscripts/_audio_whizby" },
{ 0x0000, "soundscripts/_audio_zone_manager" },
{ 0x0000, "soundscripts/_snd" },
{ 0x0000, "soundscripts/_snd_common" },
{ 0x0000, "soundscripts/_snd_debug_bayless" },
{ 0x0000, "soundscripts/_snd_debug_bina" },
{ 0x0000, "soundscripts/_snd_debug_blondin" },
{ 0x0000, "soundscripts/_snd_debug_caisley" },
{ 0x0000, "soundscripts/_snd_debug_gavazza" },
{ 0x0000, "soundscripts/_snd_debug_kilborn" },
{ 0x0000, "soundscripts/_snd_debug_loperfido" },
{ 0x0000, "soundscripts/_snd_debug_mcsweeney" },
{ 0x0000, "soundscripts/_snd_debug_mika" },
{ 0x0000, "soundscripts/_snd_debug_naas" },
{ 0x0000, "soundscripts/_snd_debug_nuniyants" },
{ 0x0000, "soundscripts/_snd_debug_swenson" },
{ 0x0000, "soundscripts/_snd_debug_veca" },
{ 0x0000, "soundscripts/_snd_filters" },
{ 0x0000, "soundscripts/_snd_foley" },
{ 0x0000, "soundscripts/_snd_hud" },
{ 0x0000, "soundscripts/_snd_pcap" },
{ 0x0000, "soundscripts/_snd_playsound" },
{ 0x0000, "soundscripts/_snd_timescale" },
{ 0x0000, "soundscripts/so_aud" },
{ 0x0000, "vehicle_scripts/_atlas_jet" },
{ 0x0000, "vehicle_scripts/_atlas_piranha" },
{ 0x0000, "vehicle_scripts/_atlas_suv" },
{ 0x0000, "vehicle_scripts/_atlas_van" },
{ 0x0000, "vehicle_scripts/_attack_drone" },
{ 0x0000, "vehicle_scripts/_attack_drone_aud" },
{ 0x0000, "vehicle_scripts/_attack_drone_common" },
{ 0x0000, "vehicle_scripts/_attack_drone_controllable" },
{ 0x0000, "vehicle_scripts/_attack_drone_individual" },
{ 0x0000, "vehicle_scripts/_attack_drone_kamikaze" },
{ 0x0000, "vehicle_scripts/_attack_drone_queen" },
{ 0x0000, "vehicle_scripts/_attack_heli" },
{ 0x0000, "vehicle_scripts/_chinese_brave_warrior" },
{ 0x0000, "vehicle_scripts/_civ_boat" },
{ 0x0000, "vehicle_scripts/_civ_boxtruck_ai" },
{ 0x0000, "vehicle_scripts/_civ_domestic_bus" },
{ 0x0000, "vehicle_scripts/_civ_domestic_economy_ai" },
{ 0x0000, "vehicle_scripts/_civ_domestic_minivan" },
{ 0x0000, "vehicle_scripts/_civ_domestic_sedan_01" },
{ 0x0000, "vehicle_scripts/_civ_domestic_sedan_police" },
{ 0x0000, "vehicle_scripts/_civ_domestic_sedan_taxi_01" },
{ 0x0000, "vehicle_scripts/_civ_domestic_sportscar_01" },
{ 0x0000, "vehicle_scripts/_civ_domestic_suv" },
{ 0x0000, "vehicle_scripts/_civ_domestic_truck" },
{ 0x0000, "vehicle_scripts/_civ_full_size_pickup_01_ai" },
{ 0x0000, "vehicle_scripts/_civ_full_size_technical" },
{ 0x0000, "vehicle_scripts/_civ_pickup_truck_01" },
{ 0x0000, "vehicle_scripts/_civ_smartcar" },
{ 0x0000, "vehicle_scripts/_civ_workvan" },
{ 0x0000, "vehicle_scripts/_cover_drone" },
{ 0x0000, "vehicle_scripts/_cover_drone_aud" },
{ 0x0000, "vehicle_scripts/_diveboat" },
{ 0x0000, "vehicle_scripts/_diveboat_aud" },
{ 0x0000, "vehicle_scripts/_empty" },
{ 0x0000, "vehicle_scripts/_ft101_tank" },
{ 0x0000, "vehicle_scripts/_gaz" },
{ 0x0000, "vehicle_scripts/_gaz_dshk" },
{ 0x0000, "vehicle_scripts/_gaz_dshk_aud" },
{ 0x0000, "vehicle_scripts/_generic_script_model_lagos" },
{ 0x0000, "vehicle_scripts/_havoc_missile_scripted" },
{ 0x0000, "vehicle_scripts/_hovertank" },
{ 0x0000, "vehicle_scripts/_hovertank_aud" },
{ 0x0000, "vehicle_scripts/_ind_semi_truck_fuel_tanker" },
{ 0x0000, "vehicle_scripts/_jetbike" },
{ 0x0000, "vehicle_scripts/_jetbike_aud" },
{ 0x0000, "vehicle_scripts/_littlebird" },
{ 0x0000, "vehicle_scripts/_littlebird_aud" },
{ 0x0000, "vehicle_scripts/_littlebird_landing" },
{ 0x0000, "vehicle_scripts/_littlebird_player" },
{ 0x0000, "vehicle_scripts/_mi17" },
{ 0x0000, "vehicle_scripts/_mi17_aud" },
{ 0x0000, "vehicle_scripts/_mi17_noai" },
{ 0x0000, "vehicle_scripts/_mig29" },
{ 0x0000, "vehicle_scripts/_mig29_controllable" },
{ 0x0000, "vehicle_scripts/_mil_cargo_truck" },
{ 0x0000, "vehicle_scripts/_pdrone" },
{ 0x0000, "vehicle_scripts/_pdrone_aud" },
{ 0x0000, "vehicle_scripts/_pdrone_player" },
{ 0x0000, "vehicle_scripts/_pdrone_player_aud" },
{ 0x0000, "vehicle_scripts/_pdrone_security" },
{ 0x0000, "vehicle_scripts/_pdrone_security_aud" },
{ 0x0000, "vehicle_scripts/_pdrone_tactical_picker" },
{ 0x0000, "vehicle_scripts/_pdrone_threat_sensor" },
{ 0x0000, "vehicle_scripts/_pitbull" },
{ 0x0000, "vehicle_scripts/_pitbull_aud" },
{ 0x0000, "vehicle_scripts/_razorback" },
{ 0x0000, "vehicle_scripts/_razorback_fx" },
{ 0x0000, "vehicle_scripts/_s19" },
{ 0x0000, "vehicle_scripts/_sentinel_survey_drone_hud" },
{ 0x0000, "vehicle_scripts/_shrike" },
{ 0x0000, "vehicle_scripts/_sidewinder_scripted" },
{ 0x0000, "vehicle_scripts/_slamraam" },
{ 0x0000, "vehicle_scripts/_sniper_drone" },
{ 0x0000, "vehicle_scripts/_sniper_drone_aud" },
{ 0x0000, "vehicle_scripts/_uk_delivery_truck" },
{ 0x0000, "vehicle_scripts/_vehicle_missile_launcher_ai" },
{ 0x0000, "vehicle_scripts/_vehicle_multiweapon_util" },
{ 0x0000, "vehicle_scripts/_vehicle_turret_ai" },
{ 0x0000, "vehicle_scripts/_vrap" },
{ 0x0000, "vehicle_scripts/_walker_tank" },
{ 0x0000, "vehicle_scripts/_x4walker_wheels" },
{ 0x0000, "vehicle_scripts/_x4walker_wheels_aud" },
{ 0x0000, "vehicle_scripts/_x4walker_wheels_turret" },
{ 0x0000, "vehicle_scripts/_x4walker_wheels_turret_aud" },
{ 0x0000, "vehicle_scripts/_x4walker_wheels_turret_closed" },
{ 0x0000, "vehicle_scripts/_x4walker_wheels_turret_closed_aud" },
{ 0x0000, "vehicle_scripts/_xh9_warbird" },
{ 0x0000, "xmodelalias/alias_africa_civilian_male_heads" },
{ 0x0000, "xmodelalias/alias_atlas_bodyguard_heads" },
{ 0x0000, "xmodelalias/alias_civ_afr_dark_male_bodies_casual" },
{ 0x0000, "xmodelalias/alias_civ_afr_dark_male_bodies_dress" },
{ 0x0000, "xmodelalias/alias_civ_afr_dark_male_heads" },
{ 0x0000, "xmodelalias/alias_civ_afr_drk_female_bodies_cas" },
{ 0x0000, "xmodelalias/alias_civ_afr_drk_female_bodies_drs" },
{ 0x0000, "xmodelalias/alias_civ_afr_drk_female_heads" },
{ 0x0000, "xmodelalias/alias_civ_afr_lgt_fem_bod_drs_sml" },
{ 0x0000, "xmodelalias/alias_civ_afr_lgt_female_bodies_cas" },
{ 0x0000, "xmodelalias/alias_civ_afr_lgt_female_bodies_drs" },
{ 0x0000, "xmodelalias/alias_civ_afr_lgt_female_heads" },
{ 0x0000, "xmodelalias/alias_civ_afr_light_male_bodies_casual" },
{ 0x0000, "xmodelalias/alias_civ_afr_light_male_bodies_dress" },
{ 0x0000, "xmodelalias/alias_civ_afr_light_male_heads" },
{ 0x0000, "xmodelalias/alias_civ_asi_male_bodies_casual" },
{ 0x0000, "xmodelalias/alias_civ_asi_male_bodies_dress" },
{ 0x0000, "xmodelalias/alias_civ_asi_male_heads" },
{ 0x0000, "xmodelalias/alias_civ_asi_male_heads_cpt" },
{ 0x0000, "xmodelalias/alias_civ_cau_fem_bod_drs_sml" },
{ 0x0000, "xmodelalias/alias_civ_cau_fem_heads_sml" },
{ 0x0000, "xmodelalias/alias_civ_cau_female_bodies_cas" },
{ 0x0000, "xmodelalias/alias_civ_cau_female_bodies_drs" },
{ 0x0000, "xmodelalias/alias_civ_cau_female_heads" },
{ 0x0000, "xmodelalias/alias_civ_cau_male_bodies_casual" },
{ 0x0000, "xmodelalias/alias_civ_cau_male_bodies_dress" },
{ 0x0000, "xmodelalias/alias_civ_cau_male_heads" },
{ 0x0000, "xmodelalias/alias_civ_cau_male_heads_hazmat_nohat" },
{ 0x0000, "xmodelalias/alias_civ_mde_female_bodies_cas" },
{ 0x0000, "xmodelalias/alias_civ_mde_female_bodies_drs" },
{ 0x0000, "xmodelalias/alias_civ_mde_female_heads" },
{ 0x0000, "xmodelalias/alias_civ_mde_male_bodies_casual" },
{ 0x0000, "xmodelalias/alias_civ_mde_male_bodies_dress" },
{ 0x0000, "xmodelalias/alias_civ_mde_male_heads" },
{ 0x0000, "xmodelalias/alias_civ_pris_afr_dark_male_bodies" },
{ 0x0000, "xmodelalias/alias_civ_pris_cau_male_bodies" },
{ 0x0000, "xmodelalias/alias_civ_pris_mde_male_bodies" },
{ 0x0000, "xmodelalias/alias_civ_rec_funeral_male_body" },
{ 0x0000, "xmodelalias/alias_civ_rec_funeral_male_body_afr" },
{ 0x0000, "xmodelalias/alias_civ_rec_funeral_male_heads" },
{ 0x0000, "xmodelalias/alias_civ_rec_funeral_male_heads_afr" },
{ 0x0000, "xmodelalias/alias_civ_urban_dead_body_a" },
{ 0x0000, "xmodelalias/alias_civ_urban_dead_body_b" },
{ 0x0000, "xmodelalias/alias_civ_urban_dead_body_c" },
{ 0x0000, "xmodelalias/alias_civ_urban_male_heads_afr_light" },
{ 0x0000, "xmodelalias/alias_civ_worker_hardhat_s1_heads" },
{ 0x0000, "xmodelalias/alias_civilian_heads_prisoner_female" },
{ 0x0000, "xmodelalias/alias_civilian_slum_heads" },
{ 0x0000, "xmodelalias/alias_civilian_slum_heads_wht" },
{ 0x0000, "xmodelalias/alias_civilian_worker_heads" },
{ 0x0000, "xmodelalias/alias_cloak_test" },
{ 0x0000, "xmodelalias/alias_coop_cloaked_static_heads" },
{ 0x0000, "xmodelalias/alias_enemy_atlas_arctic_heads" },
{ 0x0000, "xmodelalias/alias_enemy_atlas_elite_heads" },
{ 0x0000, "xmodelalias/alias_enemy_atlas_heads" },
{ 0x0000, "xmodelalias/alias_greece_civilian_heads_males_a" },
{ 0x0000, "xmodelalias/alias_greece_civilian_heads_males_b" },
{ 0x0000, "xmodelalias/alias_kva_heads" },
{ 0x0000, "xmodelalias/alias_mp_sentinel_heads" },
{ 0x0000, "xmodelalias/alias_nigerian_army_bodies" },
{ 0x0000, "xmodelalias/alias_nigerian_army_heads" },
{ 0x0000, "xmodelalias/alias_pmc_casual_heads" },
{ 0x0000, "xmodelalias/alias_pmc_casual_heads_asi" },
{ 0x0000, "xmodelalias/alias_pmc_helmet_heads" },
{ 0x0000, "xmodelalias/alias_sentinel_arctic_bodies" },
{ 0x0000, "xmodelalias/alias_sentinel_arctic_heads" },
{ 0x0000, "xmodelalias/alias_sentinel_bodies" },
{ 0x0000, "xmodelalias/alias_sentinel_heads" },
{ 0x0000, "xmodelalias/alias_sentinel_udt_heads" },
{ 0x0000, "xmodelalias/alias_seoul_civilian_body_females" },
{ 0x0000, "xmodelalias/alias_seoul_civilian_body_males_a" },
{ 0x0000, "xmodelalias/alias_seoul_civilian_body_males_b" },
{ 0x0000, "xmodelalias/alias_seoul_civilian_body_males_d" },
{ 0x0000, "xmodelalias/alias_seoul_civilian_body_males_f" },
{ 0x0000, "xmodelalias/alias_seoul_civilian_head_females" },
{ 0x0000, "xmodelalias/alias_seoul_civilian_head_males_a" },
{ 0x0000, "xmodelalias/alias_seoul_civilian_head_males_b" },
{ 0x0000, "xmodelalias/alias_seoul_civilian_head_males_c" },
{ 0x0000, "xmodelalias/alias_seoul_civilian_head_males_d" },
{ 0x0000, "xmodelalias/alias_us_marine_dress_bodies" },
{ 0x0000, "xmodelalias/alias_us_marine_dress_heads" },
{ 0x0000, "xmodelalias/alias_us_marine_heads" },
{ 0x0000, "maps/animated_models/foliage_tree_grey_oak_lg_a" },
{ 0x0000, "maps/createart/betrayal_art" },
{ 0x0000, "maps/createart/betrayal_fog" },
{ 0x0000, "maps/createart/betrayal_fog_hdr" },
{ 0x0000, "maps/createart/captured_art" },
{ 0x0000, "maps/createart/captured_fog" },
{ 0x0000, "maps/createart/captured_fog_hdr" },
{ 0x0000, "maps/createart/crash_art" },
{ 0x0000, "maps/createart/crash_fog" },
{ 0x0000, "maps/createart/crash_fog_hdr" },
{ 0x0000, "maps/createart/credits_s1_art" },
{ 0x0000, "maps/createart/credits_s1_fog" },
{ 0x0000, "maps/createart/credits_s1_fog_hdr" },
{ 0x0000, "maps/createart/detroit_art" },
{ 0x0000, "maps/createart/detroit_fog" },
{ 0x0000, "maps/createart/detroit_fog_hdr" },
{ 0x0000, "maps/createart/df_baghdad_art" },
{ 0x0000, "maps/createart/df_baghdad_fog" },
{ 0x0000, "maps/createart/df_baghdad_fog_hdr" },
{ 0x0000, "maps/createart/df_fly_art" },
{ 0x0000, "maps/createart/df_fly_fog" },
{ 0x0000, "maps/createart/df_fly_fog_hdr" },
{ 0x0000, "maps/createart/finale_art" },
{ 0x0000, "maps/createart/finale_fog" },
{ 0x0000, "maps/createart/finale_fog_hdr" },
{ 0x0000, "maps/createart/fusion_art" },
{ 0x0000, "maps/createart/fusion_fog" },
{ 0x0000, "maps/createart/fusion_fog_hdr" },
{ 0x0000, "maps/createart/greece_art" },
{ 0x0000, "maps/createart/greece_fog" },
{ 0x0000, "maps/createart/greece_fog_hdr" },
{ 0x0000, "maps/createart/irons_estate_art" },
{ 0x0000, "maps/createart/irons_estate_fog" },
{ 0x0000, "maps/createart/irons_estate_fog_hdr" },
{ 0x0000, "maps/createart/lab_art" },
{ 0x0000, "maps/createart/lab_fog" },
{ 0x0000, "maps/createart/lab_fog_hdr" },
{ 0x0000, "maps/createart/lagos_art" },
{ 0x0000, "maps/createart/lagos_fog" },
{ 0x0000, "maps/createart/lagos_fog_hdr" },
{ 0x0000, "maps/createart/mp_comeback_art" },
{ 0x0000, "maps/createart/mp_comeback_fog" },
{ 0x0000, "maps/createart/mp_comeback_fog_hdr" },
{ 0x0000, "maps/createart/mp_detroit_art" },
{ 0x0000, "maps/createart/mp_detroit_fog" },
{ 0x0000, "maps/createart/mp_detroit_fog_hdr" },
{ 0x0000, "maps/createart/mp_greenband_art" },
{ 0x0000, "maps/createart/mp_greenband_fog" },
{ 0x0000, "maps/createart/mp_greenband_fog_hdr" },
{ 0x0000, "maps/createart/mp_instinct_art" },
{ 0x0000, "maps/createart/mp_instinct_fog" },
{ 0x0000, "maps/createart/mp_instinct_fog_hdr" },
{ 0x0000, "maps/createart/mp_lab2_art" },
{ 0x0000, "maps/createart/mp_lab2_fog" },
{ 0x0000, "maps/createart/mp_lab2_fog_hdr" },
{ 0x0000, "maps/createart/mp_laser2_art" },
{ 0x0000, "maps/createart/mp_laser2_fog" },
{ 0x0000, "maps/createart/mp_laser2_fog_hdr" },
{ 0x0000, "maps/createart/mp_levity_art" },
{ 0x0000, "maps/createart/mp_levity_fog" },
{ 0x0000, "maps/createart/mp_levity_fog_hdr" },
{ 0x0000, "maps/createart/mp_prison_art" },
{ 0x0000, "maps/createart/mp_prison_fog" },
{ 0x0000, "maps/createart/mp_prison_fog_hdr" },
{ 0x0000, "maps/createart/mp_prison_z_art" },
{ 0x0000, "maps/createart/mp_prison_z_fog" },
{ 0x0000, "maps/createart/mp_prison_z_fog_hdr" },
{ 0x0000, "maps/createart/mp_recovery_art" },
{ 0x0000, "maps/createart/mp_recovery_fog" },
{ 0x0000, "maps/createart/mp_recovery_fog_hdr" },
{ 0x0000, "maps/createart/mp_refraction_art" },
{ 0x0000, "maps/createart/mp_refraction_fog" },
{ 0x0000, "maps/createart/mp_refraction_fog_hdr" },
{ 0x0000, "maps/createart/mp_solar_art" },
{ 0x0000, "maps/createart/mp_solar_fog" },
{ 0x0000, "maps/createart/mp_solar_fog_hdr" },
{ 0x0000, "maps/createart/mp_terrace_art" },
{ 0x0000, "maps/createart/mp_terrace_fog" },
{ 0x0000, "maps/createart/mp_terrace_fog_hdr" },
{ 0x0000, "maps/createart/mp_venus_art" },
{ 0x0000, "maps/createart/mp_venus_fog" },
{ 0x0000, "maps/createart/mp_venus_fog_hdr" },
{ 0x0000, "maps/createart/mp_vlobby_room_art" },
{ 0x0000, "maps/createart/mp_vlobby_room_fog" },
{ 0x0000, "maps/createart/mp_vlobby_room_fog_hdr" },
{ 0x0000, "maps/createart/recovery_art" },
{ 0x0000, "maps/createart/recovery_fog" },
{ 0x0000, "maps/createart/recovery_fog_hdr" },
{ 0x0000, "maps/createart/sanfran_art" },
{ 0x0000, "maps/createart/sanfran_b_art" },
{ 0x0000, "maps/createart/sanfran_b_fog" },
{ 0x0000, "maps/createart/sanfran_b_fog_hdr" },
{ 0x0000, "maps/createart/sanfran_fog" },
{ 0x0000, "maps/createart/sanfran_fog_hdr" },
{ 0x0000, "maps/createart/seoul_art" },
{ 0x0000, "maps/createart/seoul_fog" },
{ 0x0000, "maps/createart/seoul_fog_hdr" },
{ 0x0000, "maps/createfx/betrayal_fx" },
{ 0x0000, "maps/createfx/captured_fx" },
{ 0x0000, "maps/createfx/captured_sound" },
{ 0x0000, "maps/createfx/crash_fx" },
{ 0x0000, "maps/createfx/credits_s1_fx" },
{ 0x0000, "maps/createfx/detroit_fx" },
{ 0x0000, "maps/createfx/df_baghdad_fx" },
{ 0x0000, "maps/createfx/df_fly_fx" },
{ 0x0000, "maps/createfx/finale_fx" },
{ 0x0000, "maps/createfx/fusion_fx" },
{ 0x0000, "maps/createfx/greece_fx" },
{ 0x0000, "maps/createfx/irons_estate_fx" },
{ 0x0000, "maps/createfx/lab_fx" },
{ 0x0000, "maps/createfx/lagos_fx" },
{ 0x0000, "maps/createfx/mp_comeback_fx" },
{ 0x0000, "maps/createfx/mp_detroit_fx" },
{ 0x0000, "maps/createfx/mp_greenband_fx" },
{ 0x0000, "maps/createfx/mp_instinct_fx" },
{ 0x0000, "maps/createfx/mp_lab2_fx" },
{ 0x0000, "maps/createfx/mp_laser2_fx" },
{ 0x0000, "maps/createfx/mp_levity_fx" },
{ 0x0000, "maps/createfx/mp_prison_fx" },
{ 0x0000, "maps/createfx/mp_prison_z_fx" },
{ 0x0000, "maps/createfx/mp_recovery_fx" },
{ 0x0000, "maps/createfx/mp_refraction_fx" },
{ 0x0000, "maps/createfx/mp_solar_fx" },
{ 0x0000, "maps/createfx/mp_terrace_fx" },
{ 0x0000, "maps/createfx/mp_venus_fx" },
{ 0x0000, "maps/createfx/mp_vlobby_room_fx" },
{ 0x0000, "maps/createfx/recovery_fx" },
{ 0x0000, "maps/createfx/sanfran_b_fx" },
{ 0x0000, "maps/createfx/sanfran_fx" },
{ 0x0000, "maps/createfx/seoul_fx" },
{ 0x0000, "maps/mp/_adrenaline" },
{ 0x0000, "maps/mp/_aerial_pathnodes" },
{ 0x0000, "maps/mp/_animatedmodels" },
{ 0x0000, "maps/mp/_areas" },
{ 0x0000, "maps/mp/_art" },
{ 0x0000, "maps/mp/_audio" },
{ 0x0000, "maps/mp/_awards" },
{ 0x0000, "maps/mp/_braggingrights" },
{ 0x0000, "maps/mp/_compass" },
{ 0x0000, "maps/mp/_createfx" },
{ 0x0000, "maps/mp/_crib" },
{ 0x0000, "maps/mp/_destructables" },
{ 0x0000, "maps/mp/_dynamic_events" },
{ 0x0000, "maps/mp/_empgrenade" },
{ 0x0000, "maps/mp/_entityheadicons" },
{ 0x0000, "maps/mp/_events" },
{ 0x0000, "maps/mp/_exo_battery" },
{ 0x0000, "maps/mp/_exo_cloak" },
{ 0x0000, "maps/mp/_exo_hover" },
{ 0x0000, "maps/mp/_exo_mute" },
{ 0x0000, "maps/mp/_exo_ping" },
{ 0x0000, "maps/mp/_exo_repulsor" },
{ 0x0000, "maps/mp/_exo_shield" },
{ 0x0000, "maps/mp/_exo_suit" },
{ 0x0000, "maps/mp/_exocrossbow" },
{ 0x0000, "maps/mp/_exoknife" },
{ 0x0000, "maps/mp/_explosive_drone" },
{ 0x0000, "maps/mp/_explosive_gel" },
{ 0x0000, "maps/mp/_extrahealth" },
{ 0x0000, "maps/mp/_fastheal" },
{ 0x0000, "maps/mp/_flashgrenades" },
{ 0x0000, "maps/mp/_fx" },
{ 0x0000, "maps/mp/_global_fx" },
{ 0x0000, "maps/mp/_global_fx_code" },
{ 0x0000, "maps/mp/_lasersight" },
{ 0x0000, "maps/mp/_load" },
{ 0x0000, "maps/mp/_lsrmissileguidance" },
{ 0x0000, "maps/mp/_matchdata" },
{ 0x0000, "maps/mp/_menus" },
{ 0x0000, "maps/mp/_microdronelauncher" },
{ 0x0000, "maps/mp/_movers" },
{ 0x0000, "maps/mp/_mp_lights" },
{ 0x0000, "maps/mp/_mutebomb" },
{ 0x0000, "maps/mp/_na45" },
{ 0x0000, "maps/mp/_opticsthermal" },
{ 0x0000, "maps/mp/_reinforcements" },
{ 0x0000, "maps/mp/_riotshield" },
{ 0x0000, "maps/mp/_scoreboard" },
{ 0x0000, "maps/mp/_shutter" },
{ 0x0000, "maps/mp/_snd_common_mp" },
{ 0x0000, "maps/mp/_stinger" },
{ 0x0000, "maps/mp/_stingerm7" },
{ 0x0000, "maps/mp/_stock" },
{ 0x0000, "maps/mp/_target_enhancer" },
{ 0x0000, "maps/mp/_teleport" },
{ 0x0000, "maps/mp/_threatdetection" },
{ 0x0000, "maps/mp/_tracking_drone" },
{ 0x0000, "maps/mp/_trackrounds" },
{ 0x0000, "maps/mp/_tridrone" },
{ 0x0000, "maps/mp/_utility" },
{ 0x0000, "maps/mp/_vl_base" },
{ 0x0000, "maps/mp/_vl_camera" },
{ 0x0000, "maps/mp/_vl_firingrange" },
{ 0x0000, "maps/mp/_vl_selfiebooth" },
{ 0x0000, "maps/mp/_water" },
{ 0x0000, "maps/mp/_zipline" },
{ 0x0000, "maps/mp/mp_comeback_fx" },
{ 0x0000, "maps/mp/mp_comeback_precache" },
{ 0x0000, "maps/mp/mp_detroit_fx" },
{ 0x0000, "maps/mp/mp_detroit_precache" },
{ 0x0000, "maps/mp/mp_greenband_fx" },
{ 0x0000, "maps/mp/mp_greenband_precache" },
{ 0x0000, "maps/mp/mp_instinct_fx" },
{ 0x0000, "maps/mp/mp_instinct_precache" },
{ 0x0000, "maps/mp/mp_lab2_fx" },
{ 0x0000, "maps/mp/mp_lab2_precache" },
{ 0x0000, "maps/mp/mp_laser2_fx" },
{ 0x0000, "maps/mp/mp_laser2_precache" },
{ 0x0000, "maps/mp/mp_levity_fx" },
{ 0x0000, "maps/mp/mp_levity_precache" },
{ 0x0000, "maps/mp/mp_prison_fx" },
{ 0x0000, "maps/mp/mp_prison_precache" },
{ 0x0000, "maps/mp/mp_prison_z_fx" },
{ 0x0000, "maps/mp/mp_prison_z_precache" },
{ 0x0000, "maps/mp/mp_recovery_fx" },
{ 0x0000, "maps/mp/mp_recovery_precache" },
{ 0x0000, "maps/mp/mp_refraction_fx" },
{ 0x0000, "maps/mp/mp_refraction_precache" },
{ 0x0000, "maps/mp/mp_solar_fx" },
{ 0x0000, "maps/mp/mp_solar_precache" },
{ 0x0000, "maps/mp/mp_terrace_fx" },
{ 0x0000, "maps/mp/mp_terrace_precache" },
{ 0x0000, "maps/mp/mp_venus_fx" },
{ 0x0000, "maps/mp/mp_venus_precache" },
{ 0x0000, "maps/mp/mp_vlobby_room_fx" },
{ 0x0000, "maps/mp/mp_vlobby_room_precache" },
{ 0x0000, "maps/mp/gametypes/_battlebuddy" },
{ 0x0000, "maps/mp/gametypes/_battlechatter_mp" },
{ 0x0000, "maps/mp/gametypes/_class" },
{ 0x0000, "maps/mp/gametypes/_clientids" },
{ 0x0000, "maps/mp/gametypes/_damage" },
{ 0x0000, "maps/mp/gametypes/_damagefeedback" },
{ 0x0000, "maps/mp/gametypes/_deathicons" },
{ 0x0000, "maps/mp/gametypes/_dev" },
{ 0x0000, "maps/mp/gametypes/_equipment" },
{ 0x0000, "maps/mp/gametypes/_friendicons" },
{ 0x0000, "maps/mp/gametypes/_gamelogic" },
{ 0x0000, "maps/mp/gametypes/_gameobjects" },
{ 0x0000, "maps/mp/gametypes/_gamescore" },
{ 0x0000, "maps/mp/gametypes/_globalentities" },
{ 0x0000, "maps/mp/gametypes/_globallogic" },
{ 0x0000, "maps/mp/gametypes/_hardpoints" },
{ 0x0000, "maps/mp/gametypes/_healthoverlay" },
{ 0x0000, "maps/mp/gametypes/_high_jump_mp" },
{ 0x0000, "maps/mp/gametypes/_horde_armory" },
{ 0x0000, "maps/mp/gametypes/_horde_crates" },
{ 0x0000, "maps/mp/gametypes/_horde_dialog" },
{ 0x0000, "maps/mp/gametypes/_horde_drones" },
{ 0x0000, "maps/mp/gametypes/_horde_laststand" },
{ 0x0000, "maps/mp/gametypes/_horde_sentry" },
{ 0x0000, "maps/mp/gametypes/_horde_smart_grenade" },
{ 0x0000, "maps/mp/gametypes/_horde_util" },
{ 0x0000, "maps/mp/gametypes/_horde_zombies" },
{ 0x0000, "maps/mp/gametypes/_hostmigration" },
{ 0x0000, "maps/mp/gametypes/_hud" },
{ 0x0000, "maps/mp/gametypes/_hud_message" },
{ 0x0000, "maps/mp/gametypes/_hud_util" },
{ 0x0000, "maps/mp/gametypes/_killcam" },
{ 0x0000, "maps/mp/gametypes/_menus" },
{ 0x0000, "maps/mp/gametypes/_missions" },
{ 0x0000, "maps/mp/gametypes/_music_and_dialog" },
{ 0x0000, "maps/mp/gametypes/_objpoints" },
{ 0x0000, "maps/mp/gametypes/_orbital" },
{ 0x0000, "maps/mp/gametypes/_persistence" },
{ 0x0000, "maps/mp/gametypes/_player_boost_jump_mp" },
{ 0x0000, "maps/mp/gametypes/_playercards" },
{ 0x0000, "maps/mp/gametypes/_playerlogic" },
{ 0x0000, "maps/mp/gametypes/_portable_radar" },
{ 0x0000, "maps/mp/gametypes/_quickmessages" },
{ 0x0000, "maps/mp/gametypes/_rank" },
{ 0x0000, "maps/mp/gametypes/_scrambler" },
{ 0x0000, "maps/mp/gametypes/_serversettings" },
{ 0x0000, "maps/mp/gametypes/_shellshock" },
{ 0x0000, "maps/mp/gametypes/_spawnfactor" },
{ 0x0000, "maps/mp/gametypes/_spawnlogic" },
{ 0x0000, "maps/mp/gametypes/_spawnscoring" },
{ 0x0000, "maps/mp/gametypes/_spectating" },
{ 0x0000, "maps/mp/gametypes/_teams" },
{ 0x0000, "maps/mp/gametypes/_tweakables" },
{ 0x0000, "maps/mp/gametypes/_weapons" },
{ 0x0000, "maps/mp/killstreaks/_aerial_utility" },
{ 0x0000, "maps/mp/killstreaks/_agent_killstreak" },
{ 0x0000, "maps/mp/killstreaks/_airdrop" },
{ 0x0000, "maps/mp/killstreaks/_airstrike" },
{ 0x0000, "maps/mp/killstreaks/_assaultdrone_ai" },
{ 0x0000, "maps/mp/killstreaks/_autosentry" },
{ 0x0000, "maps/mp/killstreaks/_coop_util" },
{ 0x0000, "maps/mp/killstreaks/_dog_killstreak" },
{ 0x0000, "maps/mp/killstreaks/_drone_assault" },
{ 0x0000, "maps/mp/killstreaks/_drone_carepackage" },
{ 0x0000, "maps/mp/killstreaks/_drone_common" },
{ 0x0000, "maps/mp/killstreaks/_drone_recon" },
{ 0x0000, "maps/mp/killstreaks/_emp" },
{ 0x0000, "maps/mp/killstreaks/_juggernaut" },
{ 0x0000, "maps/mp/killstreaks/_killstreaks" },
{ 0x0000, "maps/mp/killstreaks/_killstreaks_init" },
{ 0x0000, "maps/mp/killstreaks/_marking_util" },
{ 0x0000, "maps/mp/killstreaks/_missile_strike" },
{ 0x0000, "maps/mp/killstreaks/_nuke" },
{ 0x0000, "maps/mp/killstreaks/_orbital_carepackage" },
{ 0x0000, "maps/mp/killstreaks/_orbital_strike" },
{ 0x0000, "maps/mp/killstreaks/_orbital_util" },
{ 0x0000, "maps/mp/killstreaks/_orbitalsupport" },
{ 0x0000, "maps/mp/killstreaks/_placeable" },
{ 0x0000, "maps/mp/killstreaks/_remoteturret" },
{ 0x0000, "maps/mp/killstreaks/_rippedturret" },
{ 0x0000, "maps/mp/killstreaks/_teamammorefill" },
{ 0x0000, "maps/mp/killstreaks/_uav" },
{ 0x0000, "maps/mp/killstreaks/_warbird" },
{ 0x0000, "maps/mp/killstreaks/streak_mp_comeback" },
{ 0x0000, "maps/mp/killstreaks/streak_mp_detroit" },
{ 0x0000, "maps/mp/killstreaks/streak_mp_instinct" },
{ 0x0000, "maps/mp/killstreaks/streak_mp_laser2" },
{ 0x0000, "maps/mp/killstreaks/streak_mp_prison" },
{ 0x0000, "maps/mp/killstreaks/streak_mp_recovery" },
{ 0x0000, "maps/mp/killstreaks/streak_mp_refraction" },
{ 0x0000, "maps/mp/killstreaks/streak_mp_solar" },
{ 0x0000, "maps/mp/killstreaks/streak_mp_terrace" },
{ 0x0000, "maps/mp/perks/_perkfunctions" },
{ 0x0000, "maps/mp/perks/_perks" },
*/

/*
// after first files codescript

{ 0x0000, "__smangles" },
{ 0x0000, "__smid" },
{ 0x0000, "__smname" },
{ 0x0000, "__smorigin" },
{ 0x0000, "_abortdefendlocation" },
{ 0x0000, "_adddropmarkerinternal" },
{ 0x0000, "_adjustcamerayawpitchrate" },
{ 0x0000, "_advancetogoal" },
{ 0x0000, "_ai_delete" },
{ 0x0000, "_ai_group" },
{ 0x0000, "_ai_health" },
{ 0x0000, "_aliveplayers" },
{ 0x0000, "_allowalternatemelee" },
{ 0x0000, "_allowweaponpickup" },
{ 0x0000, "_ams" },
{ 0x0000, "_animactive" },
{ 0x0000, "_anime" },
{ 0x0000, "_animmode" },
{ 0x0000, "_animname" },
{ 0x0000, "_anims" },
{ 0x0000, "_anims_drone" },
{ 0x0000, "_anims_player" },
{ 0x0000, "_anims_proxy" },
{ 0x0000, "_array_wait" },
{ 0x0000, "_assignnewvehicleturretuser" },
{ 0x0000, "_attachfanclip" },
{ 0x0000, "_audio" },
{ 0x0000, "_autosave_game_now" },
{ 0x0000, "_autosave_game_now_nochecks" },
{ 0x0000, "_autosave_game_now_notrestart" },
{ 0x0000, "_autosave_stealthcheck" },
{ 0x0000, "_beginlocationselection" },
{ 0x0000, "_bootup_static" },
{ 0x0000, "_cangiveability" },
{ 0x0000, "_caralarmfx" },
{ 0x0000, "_caralarmstop" },
{ 0x0000, "_cleanupshootinglocationondeath" },
{ 0x0000, "_clearabilities" },
{ 0x0000, "_clearalltextafterhudelem" },
{ 0x0000, "_clearcharacterdialogondeath" },
{ 0x0000, "_clearcharacterdialogonnotify" },
{ 0x0000, "_clearentitytarget" },
{ 0x0000, "_clearperks" },
{ 0x0000, "_clearradiodialogondeath" },
{ 0x0000, "_clearworlddialogonnotify" },
{ 0x0000, "_cloak_enemy_array" },
{ 0x0000, "_cloak_enemy_state" },
{ 0x0000, "_cloak_toggle_internal" },
{ 0x0000, "_cloaked_stealth_settings" },
{ 0x0000, "_closingdistancecheck" },
{ 0x0000, "_color" },
{ 0x0000, "_colors_go_line" },
{ 0x0000, "_createfx" },
{ 0x0000, "_createhudline" },
{ 0x0000, "_custom_anim" },
{ 0x0000, "_custom_anim_loop" },
{ 0x0000, "_custom_anim_thread" },
{ 0x0000, "_debug_vector_to_string" },
{ 0x0000, "_defendlocation" },
{ 0x0000, "_delaygrenadethrow" },
{ 0x0000, "_delete" },
{ 0x0000, "_destroyprojectileafterdelay" },
{ 0x0000, "_destructible_preanims" },
{ 0x0000, "_destructible_preanimtree" },
{ 0x0000, "_detachall" },
{ 0x0000, "_determineallynodescore" },
{ 0x0000, "_determineshotgunnodescore" },
{ 0x0000, "_dialogtablelookup" },
{ 0x0000, "_disableoffhandweapons" },
{ 0x0000, "_disableusability" },
{ 0x0000, "_disableweapon" },
{ 0x0000, "_disableweaponswitch" },
{ 0x0000, "_displayhelpertext" },
{ 0x0000, "_displayrechargehelpertext" },
{ 0x0000, "_dmg" },
{ 0x0000, "_do_a_lil_damage_and_heal" },
{ 0x0000, "_drawdebug" },
{ 0x0000, "_earthquake" },
{ 0x0000, "_effect" },
{ 0x0000, "_effect_keys" },
{ 0x0000, "_enabledetonate" },
{ 0x0000, "_enableexplosivedeath" },
{ 0x0000, "_enableoffhandweapons" },
{ 0x0000, "_enableusability" },
{ 0x0000, "_enableweapon" },
{ 0x0000, "_enableweaponswitch" },
{ 0x0000, "_ensure_player_is_decloaked" },
{ 0x0000, "_evaluatebuddycovernodes" },
{ 0x0000, "_evaluatenodeattackradius" },
{ 0x0000, "_evaluatenodeinplayerfov" },
{ 0x0000, "_evaluatenodeiscover" },
{ 0x0000, "_evaluatenodeisexposed" },
{ 0x0000, "_evaluatenodeknownenemyinradius" },
{ 0x0000, "_evaluatenodelostoplayer" },
{ 0x0000, "_evaluatenodeothershotgunnersbest" },
{ 0x0000, "_evaluatenodeplayerinradius" },
{ 0x0000, "_evaluatenodeplayervisibility" },
{ 0x0000, "_evaluatenoderangetoplayer" },
{ 0x0000, "_evaluateshotgunnercovernodes" },
{ 0x0000, "_exit" },
{ 0x0000, "_exit_menu" },
{ 0x0000, "_extended_patrol_idle_animation_list_fu"... },
{ 0x0000, "_extra_autosave_checks" },
{ 0x0000, "_facility" },
{ 0x0000, "_fastopen" },
{ 0x0000, "_findfleelocation" },
{ 0x0000, "_findnewvehicleturretuser" },
{ 0x0000, "_fire" },
{ 0x0000, "_first_frame_anim" },
{ 0x0000, "_flag_wait_trigger" },
{ 0x0000, "_force_kill" },
{ 0x0000, "_freevehicle" },
{ 0x0000, "_frozen_controls" },
{ 0x0000, "_fx" },
{ 0x0000, "_get_dummy" },
{ 0x0000, "_get_if_defined_or_default" },
{ 0x0000, "_getindex" },
{ 0x0000, "_getmodulekillstreakweapon" },
{ 0x0000, "_getpaintoutline" },
{ 0x0000, "_getplayerscore" },
{ 0x0000, "_getradarstrength" },
{ 0x0000, "_getrandomorginfrontofplayer" },
{ 0x0000, "_getscrambletypeidforstring" },
{ 0x0000, "_getteampaintoutline" },
{ 0x0000, "_getteamscore" },
{ 0x0000, "_getvehiclespawnerarray" },
{ 0x0000, "_getvehiclespawnerarray_by_spawngroup" },
{ 0x0000, "_giveweapon" },
{ 0x0000, "_glass_physics_wakeup" },
{ 0x0000, "_glass_physics_wakeup_update" },
{ 0x0000, "_global_fx_ents" },
{ 0x0000, "_goalblockedbyai" },
{ 0x0000, "_goalblockedbyplayer" },
{ 0x0000, "_gopath" },
{ 0x0000, "_group" },
{ 0x0000, "_handle_triggers_on" },
{ 0x0000, "_handlebreachgrenade" },
{ 0x0000, "_hasability" },
{ 0x0000, "_hasperk" },
{ 0x0000, "_hint_stick_get_config_suffix" },
{ 0x0000, "_hint_stick_update_breakfunc" },
{ 0x0000, "_hint_stick_update_string" },
{ 0x0000, "_ignore_settings_old" },
{ 0x0000, "_initalliedaialleycombatbehavior" },
{ 0x0000, "_initsafehouseexitkvabehavior" },
{ 0x0000, "_insertintoglobalusablelist" },
{ 0x0000, "_interactive" },
{ 0x0000, "_investigate_last_known_position_with_e"... },
{ 0x0000, "_investigate_last_known_position_wrappe"... },
{ 0x0000, "_is_godmode" },
{ 0x0000, "_isairplane" },
{ 0x0000, "_ishelicopter" },
{ 0x0000, "_kill" },
{ 0x0000, "_kill_fx" },
{ 0x0000, "_lastanimtime" },
{ 0x0000, "_lastwave" },
{ 0x0000, "_lc" },
{ 0x0000, "_lc_persists" },
{ 0x0000, "_leaderdialogwait" },
{ 0x0000, "_light" },
{ 0x0000, "_linkto" },
{ 0x0000, "_listen_drone_input" },
{ 0x0000, "_listen_for_hold_to_exit" },
{ 0x0000, "_listen_for_hold_to_exit_set_flags" },
{ 0x0000, "_loadstarted" },
{ 0x0000, "_make_overlay" },
{ 0x0000, "_manage_timer" },
{ 0x0000, "_mark_newlyspawned" },
{ 0x0000, "_max_script_health" },
{ 0x0000, "_mb" },
{ 0x0000, "_mech_globals" },
{ 0x0000, "_mech_hunt_baghdad" },
{ 0x0000, "_mech_node" },
{ 0x0000, "_mech_occupied" },
{ 0x0000, "_mgoff" },
{ 0x0000, "_mgon" },
{ 0x0000, "_missile_strike_setting" },
{ 0x0000, "_missilemissedtargetcheck" },
{ 0x0000, "_missing_fx" },
{ 0x0000, "_monitor_controls" },
{ 0x0000, "_monitor_damage" },
{ 0x0000, "_monitor_health" },
{ 0x0000, "_monitor_regen" },
{ 0x0000, "_monitor_static" },
{ 0x0000, "_monitor_threat_count" },
{ 0x0000, "_monitor_touch" },
{ 0x0000, "_monitor_volume_array" },
{ 0x0000, "_mount_snowmobile" },
{ 0x0000, "_newhudelem" },
{ 0x0000, "_nextcoverprint" },
{ 0x0000, "_nextmission" },
{ 0x0000, "_normalbehavior" },
{ 0x0000, "_notetrackfx" },
{ 0x0000, "_obituary" },
{ 0x0000, "_objective_delete" },
{ 0x0000, "_offset_position_from_tag" },
{ 0x0000, "_old_visionset" },
{ 0x0000, "_orbital_care_pod" },
{ 0x0000, "_orbital_strike_setting" },
{ 0x0000, "_patrol_endon_spotted_flag" },
{ 0x0000, "_pdrone_player_exit_return_control" },
{ 0x0000, "_pdrone_player_proxy" },
{ 0x0000, "_pdrone_player_proxy_clear" },
{ 0x0000, "_pdrone_player_proxy_delicate_flower" },
{ 0x0000, "_pdrone_stop_use_anim" },
{ 0x0000, "_pipe_fx_time" },
{ 0x0000, "_pipe_methods" },
{ 0x0000, "_pipes" },
{ 0x0000, "_play_view_model_cloak_toggle_anim" },
{ 0x0000, "_playerallow" },
{ 0x0000, "_playercleanupscrambleevents" },
{ 0x0000, "_playergetnextevent" },
{ 0x0000, "_playergetscrambleevent" },
{ 0x0000, "_playergetuniquescrambleid" },
{ 0x0000, "_playermonitorscrambleevents" },
{ 0x0000, "_playlocalsound" },
{ 0x0000, "_popopen" },
{ 0x0000, "_precache" },
{ 0x0000, "_pursueenemy" },
{ 0x0000, "_radio_queue" },
{ 0x0000, "_radiusdamage" },
{ 0x0000, "_randommissilemovement" },
{ 0x0000, "_reactionanimation" },
{ 0x0000, "_reduce_hud_target_count_on_death" },
{ 0x0000, "_remove_drone_control" },
{ 0x0000, "_remove_hud" },
{ 0x0000, "_remove_hud_on_death" },
{ 0x0000, "_remove_hudoutline_on_enemies" },
{ 0x0000, "_remove_overlay_static" },
{ 0x0000, "_remove_shield" },
{ 0x0000, "_reset_dvars" },
{ 0x0000, "_restorepreviousnameplatematerial" },
{ 0x0000, "_returnanimorigin" },
{ 0x0000, "_rotateprop" },
{ 0x0000, "_rotateyaw" },
{ 0x0000, "_s2walk" },
{ 0x0000, "_save_dvars" },
{ 0x0000, "_script_exploders" },
{ 0x0000, "_scripted_spawn" },
{ 0x0000, "_set_dvars" },
{ 0x0000, "_set_hudoutline_on_enemies" },
{ 0x0000, "_set_overlay_static_alpha" },
{ 0x0000, "_setability" },
{ 0x0000, "_setactionslot" },
{ 0x0000, "_setentitytarget" },
{ 0x0000, "_sethighestmissionifnotcheating" },
{ 0x0000, "_sethudoutline" },
{ 0x0000, "_sethudoutline_on_spawn" },
{ 0x0000, "_setlightintensity" },
{ 0x0000, "_setmissiondiffstringifnotcheating" },
{ 0x0000, "_setnameplatematerial" },
{ 0x0000, "_setperk" },
{ 0x0000, "_setplayerscore" },
{ 0x0000, "_setsaveddvar" },
{ 0x0000, "_setswitchnode" },
{ 0x0000, "_setteamscore" },
{ 0x0000, "_settext" },
{ 0x0000, "_setup_hud" },
{ 0x0000, "_setup_overlay_static" },
{ 0x0000, "_setupdooranimstyle" },
{ 0x0000, "_setvehgoalpos" },
{ 0x0000, "_setvehgoalpos_wrap" },
{ 0x0000, "_shotgunneradvance" },
{ 0x0000, "_shotgunnerambience" },
{ 0x0000, "_shotgunnerdamagefunction" },
{ 0x0000, "_shotgunnerdeath" },
{ 0x0000, "_show_contols" },
{ 0x0000, "_slomo_breach_blowback_guy" },
{ 0x0000, "_slomo_breach_c4_hostage" },
{ 0x0000, "_slomo_breach_chair_guy_animated" },
{ 0x0000, "_slomo_breach_chair_guy_normal" },
{ 0x0000, "_slomo_breach_desk_guy" },
{ 0x0000, "_slomo_breach_executed_guy" },
{ 0x0000, "_slomo_breach_executed_guy_pushed_to_fl"... },
{ 0x0000, "_slomo_breach_executioner_knife" },
{ 0x0000, "_slomo_breach_executioner_pistol" },
{ 0x0000, "_slomo_breach_fightback_guy" },
{ 0x0000, "_slomo_breach_hostage_react" },
{ 0x0000, "_slomo_breach_knife_charger" },
{ 0x0000, "_slomo_breach_knife_hostage_death" },
{ 0x0000, "_slomo_breach_pistol_guy" },
{ 0x0000, "_slowmo_breach_funcs" },
{ 0x0000, "_slowmo_functions" },
{ 0x0000, "_slowopen" },
{ 0x0000, "_snd" },
{ 0x0000, "_snd_update_soundcontextoverride" },
{ 0x0000, "_sonicaoeanim" },
{ 0x0000, "_sonicaoenotready" },
{ 0x0000, "_sortbyscore" },
{ 0x0000, "_sound" },
{ 0x0000, "_spawner_mg42_think" },
{ 0x0000, "_spawner_stealth_default" },
{ 0x0000, "_spawntargetnamegotogoal" },
{ 0x0000, "_squaddoorbreach" },
{ 0x0000, "_startdooropen" },
{ 0x0000, "_state_init" },
{ 0x0000, "_stealth" },
{ 0x0000, "_stealth_move_detection_cap" },
{ 0x0000, "_stop_mech_hunt_baghdad" },
{ 0x0000, "_stunassaultdrones" },
{ 0x0000, "_stuncivilians" },
{ 0x0000, "_stunenemies" },
{ 0x0000, "_suicide" },
{ 0x0000, "_tag_entity" },
{ 0x0000, "_takeweaponsexcept" },
{ 0x0000, "_teleportleashbehavior" },
{ 0x0000, "_tff_sync_trigger_think" },
{ 0x0000, "_tff_sync_triggers" },
{ 0x0000, "_threatdetection" },
{ 0x0000, "_timeout" },
{ 0x0000, "_timeout_pause_on_death_and_prematch" },
{ 0x0000, "_trigger_handle_triggering" },
{ 0x0000, "_unlink" },
{ 0x0000, "_unsetability" },
{ 0x0000, "_unsetperk" },
{ 0x0000, "_updatebuddycovernodes" },
{ 0x0000, "_updateenemygroupdirection" },
{ 0x0000, "_updateenemyusable" },
{ 0x0000, "_updatepainamount" },
{ 0x0000, "_updateshotgunnercovernodes" },
{ 0x0000, "_updateteamusable" },
{ 0x0000, "_useperkenabled" },
{ 0x0000, "_validateattacker" },
{ 0x0000, "_vehicle_badplace" },
{ 0x0000, "_vehicle_effect" },
{ 0x0000, "_vehicle_effect_custom_param" },
{ 0x0000, "_vehicle_is_crashing" },
{ 0x0000, "_vehicle_landvehicle" },
{ 0x0000, "_vehicle_paths" },
{ 0x0000, "_vehicle_resume_named" },
{ 0x0000, "_vehicle_spawn" },
{ 0x0000, "_vehicle_stop_named" },
{ 0x0000, "_vehicle_unload" },
{ 0x0000, "_vehicleturretreenable" },
{ 0x0000, "_vmodel_anims" },
{ 0x0000, "_vmodel_enter" },
{ 0x0000, "_vmodel_exit" },
{ 0x0000, "_vmodel_sway" },
{ 0x0000, "_vol" },
{ 0x0000, "_wait" },
{ 0x0000, "_waittillgoalornewgoal" },
{ 0x0000, "_waittillmatch" },
{ 0x0000, "_waittillmatch_notify" },
{ 0x0000, "_walk" },
{ 0x0000, "_wavedelay" },
{ 0x0000, "_waveplayerspawnindex" },
{ 0x0000, "a10_30mm_fire" },
{ 0x0000, "a10_fire_missiles" },
{ 0x0000, "a10_gun_dives" },
{ 0x0000, "a10_missile_dives" },
{ 0x0000, "a10_missile_set_target" },
{ 0x0000, "a10_precache" },
{ 0x0000, "a10_spawn_funcs" },
{ 0x0000, "a10_wait_fire_missile" },
{ 0x0000, "a10_wait_start_firing" },
{ 0x0000, "a10_wait_stop_firing" },
{ 0x0000, "aa_add_event" },
{ 0x0000, "aa_add_event_float" },
{ 0x0000, "aa_ai_functions" },
{ 0x0000, "aa_door_functions" },
{ 0x0000, "aa_explosion" },
{ 0x0000, "aa_init_stats" },
{ 0x0000, "aa_player_ads_tracking" },
{ 0x0000, "aa_player_attacks_enemy_with_ads" },
{ 0x0000, "aa_player_health_tracking" },
{ 0x0000, "aa_print_vals" },
{ 0x0000, "aa_should_start_fresh" },
{ 0x0000, "aa_spawning_functions" },
{ 0x0000, "aa_time_tracking" },
{ 0x0000, "aa_update_flags" },
{ 0x0000, "abandon_mission_warning_hint" },
{ 0x0000, "abanglecutoff" },
{ 0x0000, "abilities" },
{ 0x0000, "abilitycansetfuncs" },
{ 0x0000, "abilitychosen" },
{ 0x0000, "abilitysetfuncs" },
{ 0x0000, "abilityunsetfuncs" },
{ 0x0000, "abort" },
{ 0x0000, "abort_count" },
{ 0x0000, "abort_drones" },
{ 0x0000, "abort_wait_any_func_array" },
{ 0x0000, "abortapproachifthreatened" },
{ 0x0000, "abortlevel" },
{ 0x0000, "abortreloadwhencanshoot" },
{ 0x0000, "about_to_stop" },
{ 0x0000, "about_to_unload" },
{ 0x0000, "abouttobebreached" },
{ 0x0000, "absangleclamp180" },
{ 0x0000, "absyawtoangles" },
{ 0x0000, "absyawtoenemy" },
{ 0x0000, "absyawtoenemy2d" },
{ 0x0000, "absyawtoorigin" },
{ 0x0000, "absz" },
{ 0x0000, "abyss_player_kill" },
{ 0x0000, "ac_duct" },
{ 0x0000, "ac_duct_01" },
{ 0x0000, "ac_duct_02" },
{ 0x0000, "ac130" },
{ 0x0000, "ac130_flood_respawn" },
{ 0x0000, "ac130gunner" },
{ 0x0000, "ac130player" },
{ 0x0000, "accaracy_mod" },
{ 0x0000, "accel" },
{ 0x0000, "accel_watcher" },
{ 0x0000, "accelerating" },
{ 0x0000, "acceltime" },
{ 0x0000, "accessallmarkers" },
{ 0x0000, "accumulated_restore" },
{ 0x0000, "accumulateplayerpingdata" },
{ 0x0000, "accuracy_fake_function" },
{ 0x0000, "accuracygrowthmultiplier" },
{ 0x0000, "accuracystationarymod" },
{ 0x0000, "achieve_downed_kills" },
{ 0x0000, "achieve_slowmo_breach_kills" },
{ 0x0000, "achievement" },
{ 0x0000, "achievement_attacker" },
{ 0x0000, "achievementsniperdronetriplekill" },
{ 0x0000, "acquire_target" },
{ 0x0000, "acquired_animation" },
{ 0x0000, "acquiring_dogfight_target" },
{ 0x0000, "acquiring_lock_target" },
{ 0x0000, "action_back" },
{ 0x0000, "action_func" },
{ 0x0000, "action_gears" },
{ 0x0000, "action_killstreak" },
{ 0x0000, "action_leaderboards" },
{ 0x0000, "action_slot_num" },
{ 0x0000, "action_slot_whistle" },
{ 0x0000, "action_thread" },
{ 0x0000, "action_weapons_primary" },
{ 0x0000, "action_weapons_secondary" },
{ 0x0000, "actionnotify" },
{ 0x0000, "actionnotifymessage" },
{ 0x0000, "actionslotenabled" },
{ 0x0000, "actionslots" },
{ 0x0000, "activate_betrayal_exo_abilities" },
{ 0x0000, "activate_clientside_exploder" },
{ 0x0000, "activate_color_code_internal" },
{ 0x0000, "activate_destructibles_in_volume" },
{ 0x0000, "activate_exo_ping" },
{ 0x0000, "activate_exploder" },
{ 0x0000, "activate_exploders_in_volume" },
{ 0x0000, "activate_guy" },
{ 0x0000, "activate_heater" },
{ 0x0000, "activate_individual_exploder" },
{ 0x0000, "activate_individual_exploder_proc" },
{ 0x0000, "activate_interactives_in_volume" },
{ 0x0000, "activate_mute_volume" },
{ 0x0000, "activate_security_drone" },
{ 0x0000, "activate_splashes" },
{ 0x0000, "activate_takedown_world_prompt_on_enemy" },
{ 0x0000, "activate_takedown_world_prompt_on_truck"... },
{ 0x0000, "activate_targets" },
{ 0x0000, "activate_trigger" },
{ 0x0000, "activate_trigger_process" },
{ 0x0000, "activate_trigger_when_player_jumps" },
{ 0x0000, "activate_trigger_with_noteworthy" },
{ 0x0000, "activate_trigger_with_targetname" },
{ 0x0000, "activateagent" },
{ 0x0000, "activategroupedtridrones" },
{ 0x0000, "activateplayerhud" },
{ 0x0000, "activateratio" },
{ 0x0000, "activatethermal" },
{ 0x0000, "activation_cost" },
{ 0x0000, "active_boats" },
{ 0x0000, "active_button" },
{ 0x0000, "active_civilians" },
{ 0x0000, "active_cloaking_disable" },
{ 0x0000, "active_cloaking_enable" },
{ 0x0000, "active_drones" },
{ 0x0000, "active_events" },
{ 0x0000, "active_events_axis" },
{ 0x0000, "active_ffa_players" },
{ 0x0000, "active_objective" },
{ 0x0000, "active_vo_lockouts" },
{ 0x0000, "active_wait_spread" },
{ 0x0000, "activecounteruavs" },
{ 0x0000, "activefriendlyspawn" },
{ 0x0000, "activegrenadetimer" },
{ 0x0000, "activehordedefendlocs" },
{ 0x0000, "activenodes" },
{ 0x0000, "activeplayers" },
{ 0x0000, "activestyle" },
{ 0x0000, "activetarget" },
{ 0x0000, "activeuavs" },
{ 0x0000, "activeweapon" },
{ 0x0000, "actor_alarm_guard" },
{ 0x0000, "actor_anims" },
{ 0x0000, "actor_playscene_walker_stepover_cormack" },
{ 0x0000, "actor_playscene_walker_stepover_jackson" },
{ 0x0000, "actor_playscene_walker_stepover_will" },
{ 0x0000, "actual_spawn" },
{ 0x0000, "ad_offset_position_from_tag" },
{ 0x0000, "add_abort" },
{ 0x0000, "add_agents_to_game" },
{ 0x0000, "add_ai_to_colors" },
{ 0x0000, "add_and_select_entity" },
{ 0x0000, "add_animation" },
{ 0x0000, "add_animsound" },
{ 0x0000, "add_array_to_destructible" },
{ 0x0000, "add_avatar" },
{ 0x0000, "add_basement_enemy_flashlight" },
{ 0x0000, "add_bcs_location_mapping" },
{ 0x0000, "add_breach_func" },
{ 0x0000, "add_burke_flashlight" },
{ 0x0000, "add_button" },
{ 0x0000, "add_c4_glow" },
{ 0x0000, "add_call" },
{ 0x0000, "add_capture_enemy_momentum" },
{ 0x0000, "add_capture_friendly_momentum" },
{ 0x0000, "add_cellphone_notetracks" },
{ 0x0000, "add_cheap_flashlight" },
{ 0x0000, "add_cleanup_ent" },
{ 0x0000, "add_collision_offsets_to_path_ent" },
{ 0x0000, "add_collision_to_path" },
{ 0x0000, "add_collision_to_path_node" },
{ 0x0000, "add_contrail" },
{ 0x0000, "add_control_based_hint_strings" },
{ 0x0000, "add_coop_scene_models" },
{ 0x0000, "add_cover_node" },
{ 0x0000, "add_damage_function" },
{ 0x0000, "add_damage_fx" },
{ 0x0000, "add_damage_owner_recorder" },
{ 0x0000, "add_damagefeedback" },
{ 0x0000, "add_dds_category" },
{ 0x0000, "add_dds_category_axis" },
{ 0x0000, "add_dds_category_group" },
{ 0x0000, "add_dds_category_group_axis" },
{ 0x0000, "add_dds_countryid" },
{ 0x0000, "add_debug_element" },
{ 0x0000, "add_destructible_fx" },
{ 0x0000, "add_destructible_to_frame_queue" },
{ 0x0000, "add_destructible_type_function" },
{ 0x0000, "add_destructible_type_transient" },
{ 0x0000, "add_dialogue_line" },
{ 0x0000, "add_doc_civ_walla" },
{ 0x0000, "add_drone_to_squad" },
{ 0x0000, "add_earthquake" },
{ 0x0000, "add_endon" },
{ 0x0000, "add_enemy_flashlight" },
{ 0x0000, "add_extra_autosave_check" },
{ 0x0000, "add_fractional_data_point" },
{ 0x0000, "add_func" },
{ 0x0000, "add_fx" },
{ 0x0000, "add_global_spawn_function" },
{ 0x0000, "add_greece_starts" },
{ 0x0000, "add_hint_background" },
{ 0x0000, "add_hint_string" },
{ 0x0000, "add_hovertank_turret" },
{ 0x0000, "add_hud_line" },
{ 0x0000, "add_hudelm_position_internal" },
{ 0x0000, "add_humanoid_agent" },
{ 0x0000, "add_idle_control" },
{ 0x0000, "add_jav_glow" },
{ 0x0000, "add_kb_button" },
{ 0x0000, "add_key" },
{ 0x0000, "add_key_to_destructible" },
{ 0x0000, "add_keypairs_to_destructible" },
{ 0x0000, "add_kill_enemy_minion_momentum" },
{ 0x0000, "add_kill_enemy_momentum" },
{ 0x0000, "add_kill_friendly_minion_momentum" },
{ 0x0000, "add_kill_friendly_momentum" },
{ 0x0000, "add_lock_target" },
{ 0x0000, "add_mag_move_notetracks" },
{ 0x0000, "add_momentum" },
{ 0x0000, "add_moving_obstacle" },
{ 0x0000, "add_moving_vol_to_node" },
{ 0x0000, "add_name" },
{ 0x0000, "add_no_game_starts" },
{ 0x0000, "add_node_to_global_arrays" },
{ 0x0000, "add_noself_call" },
{ 0x0000, "add_note_track_data" },
{ 0x0000, "add_notetrack_and_get_index" },
{ 0x0000, "add_notetrack_array" },
{ 0x0000, "add_object_to_tactics_system" },
{ 0x0000, "add_objective" },
{ 0x0000, "add_option_to_selected_entities" },
{ 0x0000, "add_party_member_class_change" },
{ 0x0000, "add_passenger_to_player_pitbull" },
{ 0x0000, "add_path_node" },
{ 0x0000, "add_path_weights" },
{ 0x0000, "add_phrase_to_history" },
{ 0x0000, "add_player_flashlight" },
{ 0x0000, "add_proccess_trigger" },
{ 0x0000, "add_random_killspawner_to_spawngroup" },
{ 0x0000, "add_reactive_fx" },
{ 0x0000, "add_replace_after_load_done" },
{ 0x0000, "add_reverb" },
{ 0x0000, "add_rpg_to_tactics_system" },
{ 0x0000, "add_scene_model" },
{ 0x0000, "add_script_car" },
{ 0x0000, "add_shake_and_rumble_notetracks" },
{ 0x0000, "add_shake_and_rumble_notetracks_for_gra"... },
{ 0x0000, "add_shake_and_rumble_notetracks_for_jum"... },
{ 0x0000, "add_sit_load_ak_notetracks" },
{ 0x0000, "add_slowmo_breach_custom_function" },
{ 0x0000, "add_slowmo_breacher" },
{ 0x0000, "add_smoking_notetracks" },
{ 0x0000, "add_spawn_behavior" },
{ 0x0000, "add_spawn_function" },
{ 0x0000, "add_spawn_function_to_noteworthy" },
{ 0x0000, "add_spawn_function_to_targetname" },
{ 0x0000, "add_spawner_to_global_arrays" },
{ 0x0000, "add_start" },
{ 0x0000, "add_start_assert" },
{ 0x0000, "add_start_construct" },
{ 0x0000, "add_struct_to_global_array" },
{ 0x0000, "add_swarm_repulsor_for_ally" },
{ 0x0000, "add_target_on_dot" },
{ 0x0000, "add_target_on_los" },
{ 0x0000, "add_target_pivot" },
{ 0x0000, "add_to_animsound" },
{ 0x0000, "add_to_array" },
{ 0x0000, "add_to_bot_damage_targets" },
{ 0x0000, "add_to_bot_use_targets" },
{ 0x0000, "add_to_destroyed_count" },
{ 0x0000, "add_to_dialogue" },
{ 0x0000, "add_to_dialogue_generic" },
{ 0x0000, "add_to_flock" },
{ 0x0000, "add_to_group_civilian" },
{ 0x0000, "add_to_group_enemy" },
{ 0x0000, "add_to_javelin_targeting" },
{ 0x0000, "add_to_radio" },
{ 0x0000, "add_to_spawngroup" },
{ 0x0000, "add_to_threat_bias" },
{ 0x0000, "add_tokens_to_trigger_flags" },
{ 0x0000, "add_trace_fx" },
{ 0x0000, "add_trace_fx_proc" },
{ 0x0000, "add_trigger_func_thread" },
{ 0x0000, "add_trigger_function" },
{ 0x0000, "add_turret_on_dismount" },
{ 0x0000, "add_vehicle_anim" },
{ 0x0000, "add_vehicle_player_anim" },
{ 0x0000, "add_vision_set" },
{ 0x0000, "add_vision_sets_from_triggers" },
{ 0x0000, "add_vol_to_node" },
{ 0x0000, "add_volume_to_global_arrays" },
{ 0x0000, "add_wait" },
{ 0x0000, "add_wait_asserter" },
{ 0x0000, "add_warbird_cargo" },
{ 0x0000, "add_weapon" },
{ 0x0000, "add_z" },
{ 0x0000, "addactioncovermealiasex" },
{ 0x0000, "addactivecounteruav" },
{ 0x0000, "addactiveuav" },
{ 0x0000, "addaieventlistener_func" },
{ 0x0000, "addairexplosion" },
{ 0x0000, "addallowedthreatcallout" },
{ 0x0000, "addalternatespawnpoint" },
{ 0x0000, "addarmorypoints" },
{ 0x0000, "addattachments" },
{ 0x0000, "addattacker" },
{ 0x0000, "addautomaticattachments" },
{ 0x0000, "addcalloutresponseevent" },
{ 0x0000, "addcastname" },
{ 0x0000, "addcenterdual" },
{ 0x0000, "addcenterheading" },
{ 0x0000, "addcenterimage" },
{ 0x0000, "addcentername" },
{ 0x0000, "addcenternamedouble" },
{ 0x0000, "addcentersubtitle" },
{ 0x0000, "addcentertriple" },
{ 0x0000, "addcheckfirealias" },
{ 0x0000, "addchild" },
{ 0x0000, "addcollisiontopool" },
{ 0x0000, "addconcatdirectionalias" },
{ 0x0000, "addconcattargetalias" },
{ 0x0000, "addcratetype" },
{ 0x0000, "addcratetypes_standard" },
{ 0x0000, "adddeathicon" },
{ 0x0000, "adddropmarker" },
{ 0x0000, "added_aerial_links" },
{ 0x0000, "addedtowave" },
{ 0x0000, "addgap" },
{ 0x0000, "addgrenadethrowanimoffset" },
{ 0x0000, "addhinttrigger" },
{ 0x0000, "addhostileburstalias" },
{ 0x0000, "addinformalias" },
{ 0x0000, "addinformevent" },
{ 0x0000, "addinformreloadingaliasex" },
{ 0x0000, "additional_delete_cars" },
{ 0x0000, "additional_geo" },
{ 0x0000, "additional_tactical_logic_func" },
{ 0x0000, "additional_unlink_nodes" },
{ 0x0000, "additionalassets" },
{ 0x0000, "additionalsighttraceentities" },
{ 0x0000, "additionalvo" },
{ 0x0000, "additive_pain" },
{ 0x0000, "additive_pull_weight" },
{ 0x0000, "additiverotateroot" },
{ 0x0000, "additiveturretdriveidle" },
{ 0x0000, "additiveturretfire" },
{ 0x0000, "additiveturretidle" },
{ 0x0000, "additiveturretrotateleft" },
{ 0x0000, "additiveturretrotateright" },
{ 0x0000, "additiveusegunroot" },
{ 0x0000, "addlastperks" },
{ 0x0000, "addlaunchers" },
{ 0x0000, "addleftname" },
{ 0x0000, "addlefttitle" },
{ 0x0000, "addlevel" },
{ 0x0000, "addlightningexploder" },
{ 0x0000, "addlowermessage" },
{ 0x0000, "addmovecombataliasex" },
{ 0x0000, "addmovenoncombataliasex" },
{ 0x0000, "addnamealias" },
{ 0x0000, "addnamealiasex" },
{ 0x0000, "addnodestobechecked" },
{ 0x0000, "addnotetrack_animsound" },
{ 0x0000, "addnotetrack_attach" },
{ 0x0000, "addnotetrack_customfunction" },
{ 0x0000, "addnotetrack_detach" },
{ 0x0000, "addnotetrack_detach_gun" },
{ 0x0000, "addnotetrack_df" },
{ 0x0000, "addnotetrack_dialogue" },
{ 0x0000, "addnotetrack_flag" },
{ 0x0000, "addnotetrack_flag_clear" },
{ 0x0000, "addnotetrack_lui_notify" },
{ 0x0000, "addnotetrack_notify" },
{ 0x0000, "addnotetrack_playersound" },
{ 0x0000, "addnotetrack_set_omnvar" },
{ 0x0000, "addnotetrack_sound" },
{ 0x0000, "addnotetrack_startfxontag" },
{ 0x0000, "addnotetrack_stopfxontag" },
{ 0x0000, "addnotetrack_swapparttoefx" },
{ 0x0000, "addnotetrack_tracepartforefx" },
{ 0x0000, "addofficertosquad" },
{ 0x0000, "addonstart_animsound" },
{ 0x0000, "addoption" },
{ 0x0000, "addorderalias" },
{ 0x0000, "addorderevent" },
{ 0x0000, "addplanetolist" },
{ 0x0000, "addplayernamealias" },
{ 0x0000, "addplayertosquad" },
{ 0x0000, "addpossiblethreatcallout" },
{ 0x0000, "addposteventgeotocratebadplacearray" },
{ 0x0000, "addprereq" },
{ 0x0000, "addrankalias" },
{ 0x0000, "addreactionalias" },
{ 0x0000, "addreactionevent" },
{ 0x0000, "addresponsealias" },
{ 0x0000, "addresponseevent" },
{ 0x0000, "addresponseevent_internal" },
{ 0x0000, "addrightname" },
{ 0x0000, "addrighttitle" },
{ 0x0000, "addsafetyhealth" },
{ 0x0000, "addsituationalcombatorder" },
{ 0x0000, "addsituationalorder" },
{ 0x0000, "addspace" },
{ 0x0000, "addspacesmall" },
{ 0x0000, "addspawnpoints" },
{ 0x0000, "addspeaker" },
{ 0x0000, "addstartspawnpoints" },
{ 0x0000, "addstreaksupportprompt" },
{ 0x0000, "addsubleftname" },
{ 0x0000, "addsublefttitle" },
{ 0x0000, "addtakingfirealias" },
{ 0x0000, "addtauntalias" },
{ 0x0000, "addthreatalias" },
{ 0x0000, "addthreatcalloutalias" },
{ 0x0000, "addthreatcalloutecho" },
{ 0x0000, "addthreatcalloutlandmarkalias" },
{ 0x0000, "addthreatcalloutlocationalias" },
{ 0x0000, "addthreatcalloutqa_nextline" },
{ 0x0000, "addthreatcalloutresponsealias" },
{ 0x0000, "addthreatdistancealias" },
{ 0x0000, "addthreatelevationalias" },
{ 0x0000, "addthreatevent" },
{ 0x0000, "addthreatexposedalias" },
{ 0x0000, "addthreatobviousalias" },
{ 0x0000, "addtime" },
{ 0x0000, "addtoalivecount" },
{ 0x0000, "addtobaseangle" },
{ 0x0000, "addtobattlebuddywaitlist" },
{ 0x0000, "addtocarepackagedronelist" },
{ 0x0000, "addtocharactersarray" },
{ 0x0000, "addtodeletespike" },
{ 0x0000, "addtoexplosivedronelist" },
{ 0x0000, "addtohelilist" },
{ 0x0000, "addtolittlebirdlist" },
{ 0x0000, "addtolivescount" },
{ 0x0000, "addtoparticipantsarray" },
{ 0x0000, "addtosquad" },
{ 0x0000, "addtosystem" },
{ 0x0000, "addtoteam" },
{ 0x0000, "addtoteamcount" },
{ 0x0000, "addtototalspawned" },
{ 0x0000, "addtotrackingdronelist" },
{ 0x0000, "addtoturretlist" },
{ 0x0000, "addtowavespawner" },
{ 0x0000, "addturret" },
{ 0x0000, "adduavmodel" },
{ 0x0000, "aden_key_fr" },
{ 0x0000, "adjust_angles_to_player" },
{ 0x0000, "adjust_bounce_lookahead" },
{ 0x0000, "adjust_gravity" },
{ 0x0000, "adjust_model_speed_to_node" },
{ 0x0000, "adjust_pitbull_add_idle" },
{ 0x0000, "adjustallyaccuracyovertime" },
{ 0x0000, "adjustfov" },
{ 0x0000, "adjustlink" },
{ 0x0000, "adjustmissileoverlay" },
{ 0x0000, "adjustshadowcenter" },
{ 0x0000, "adjuststaticoverlay" },
{ 0x0000, "adrenaline" },
{ 0x0000, "adrenaline_col" },
{ 0x0000, "adrenaline_speed_scalar" },
{ 0x0000, "adrenalineinit" },
{ 0x0000, "adrenalinesettings" },
{ 0x0000, "adrenalinesupport" },
{ 0x0000, "adrone_condition_callback_to_state_deat"... },
{ 0x0000, "adrone_condition_callback_to_state_dest"... },
{ 0x0000, "adrone_condition_callback_to_state_dist"... },
{ 0x0000, "adrone_condition_callback_to_state_flyb"... },
{ 0x0000, "adrone_condition_callback_to_state_flyi"... },
{ 0x0000, "adrone_condition_callback_to_state_flyo"... },
{ 0x0000, "adrone_condition_callback_to_state_hove"... },
{ 0x0000, "adrone_condition_callback_to_state_off" },
{ 0x0000, "ads" },
{ 0x0000, "ads_hint" },
{ 0x0000, "ads_hint_breakout" },
{ 0x0000, "ads_hint_breakout_think" },
{ 0x0000, "ads_hint_clear" },
{ 0x0000, "ads_hint_display" },
{ 0x0000, "ads_on" },
{ 0x0000, "adsmonitor" },
{ 0x0000, "adstime" },
{ 0x0000, "advance_bones_and_joker_intro" },
{ 0x0000, "advance_gideon_if_player_ahead" },
{ 0x0000, "advance_regardless_of_numbers" },
{ 0x0000, "advancedtraverse" },
{ 0x0000, "advancedtraverse2" },
{ 0x0000, "advancedwindowtraverse" },
{ 0x0000, "advanceonhidingenemy" },
{ 0x0000, "advancetoenemygroup" },
{ 0x0000, "advancetoenemygroupmax" },
{ 0x0000, "advancetoenemyinterval" },
{ 0x0000, "aerial_danger_exists_for" },
{ 0x0000, "aerial_dangers_monitoring" },
{ 0x0000, "aerial_group" },
{ 0x0000, "aerial_neighbors" },
{ 0x0000, "aerial_pathnode_group_connect_dist" },
{ 0x0000, "aerial_pathnode_offset" },
{ 0x0000, "aerial_pathnodes" },
{ 0x0000, "aerial_pathnodes_force_connect" },
{ 0x0000, "aerialdrone" },
{ 0x0000, "aerialkillstreakmarker" },
{ 0x0000, "affected" },
{ 0x0000, "afk" },
{ 0x0000, "after_collpase_ents" },
{ 0x0000, "afterlandanim" },
{ 0x0000, "afterlandanimconnected" },
{ 0x0000, "aftermath_anims" },
{ 0x0000, "agent_damage_finished" },
{ 0x0000, "agent_funcs" },
{ 0x0000, "agent_gameparticipant" },
{ 0x0000, "agent_override_difficulty" },
{ 0x0000, "agent_player_conf_think" },
{ 0x0000, "agent_player_dom_think" },
{ 0x0000, "agent_player_sd_think" },
{ 0x0000, "agent_squadmember_conf_think" },
{ 0x0000, "agent_squadmember_dom_think" },
{ 0x0000, "agent_teamparticipant" },
{ 0x0000, "agent_type" },
{ 0x0000, "agentarray" },
{ 0x0000, "agentbody" },
{ 0x0000, "agentcostumetablename" },
{ 0x0000, "agentdogbark" },
{ 0x0000, "agentdogthink" },
{ 0x0000, "agentfunc" },
{ 0x0000, "aggresivelookat" },
{ 0x0000, "aggressivemode" },
{ 0x0000, "aggro_target" },
{ 0x0000, "ah_delay_playerseek" },
{ 0x0000, "ah_fast_body_cleanup" },
{ 0x0000, "ah_init_track_block" },
{ 0x0000, "ah_init_track_doors" },
{ 0x0000, "ah_morgue_doors" },
{ 0x0000, "ah_morgue_threat_proc" },
{ 0x0000, "ah_move_track_block" },
{ 0x0000, "ah_player_bodybag_slowdown" },
{ 0x0000, "ah_track_door_open" },
{ 0x0000, "ah_tranistion_doors" },
{ 0x0000, "ai" },
{ 0x0000, "ai_3d_sighting_model" },
{ 0x0000, "ai_add_player_only_damage" },
{ 0x0000, "ai_add_twenty_percent_damage" },
{ 0x0000, "ai_ally_mb_intro_anim" },
{ 0x0000, "ai_animate_props_on_death" },
{ 0x0000, "ai_array" },
{ 0x0000, "ai_array_killcount_flag_set" },
{ 0x0000, "ai_boat_bow_splash_fx" },
{ 0x0000, "ai_boat_water_foamfx" },
{ 0x0000, "ai_canal_combat_01_accuracy_think" },
{ 0x0000, "ai_canal_combat_02_accuracy_think" },
{ 0x0000, "ai_canal_combat_03_accuracy_think" },
{ 0x0000, "ai_canal_combat_04_accuracy_think" },
{ 0x0000, "ai_canal_combat_05_accuracy_think" },
{ 0x0000, "ai_charged_shot_wait_for_death" },
{ 0x0000, "ai_classname_in_level" },
{ 0x0000, "ai_classname_in_level_keys" },
{ 0x0000, "ai_clear_custom_animation_reaction" },
{ 0x0000, "ai_clear_custom_animation_reaction_and_"... },
{ 0x0000, "ai_cond_player_at_ambient_battle" },
{ 0x0000, "ai_cond_player_at_escape_battle" },
{ 0x0000, "ai_cond_player_at_pitbull_battle" },
{ 0x0000, "ai_cond_player_at_police_battle" },
{ 0x0000, "ai_cond_player_at_standoff_battle" },
{ 0x0000, "ai_cond_player_at_standoff_battle_or_da"... },
{ 0x0000, "ai_cond_player_at_tanker_battle" },
{ 0x0000, "ai_cond_player_at_van" },
{ 0x0000, "ai_cond_reached_goal" },
{ 0x0000, "ai_cond_reached_path_end" },
{ 0x0000, "ai_create_behavior_function" },
{ 0x0000, "ai_damage_think" },
{ 0x0000, "ai_deathflag" },
{ 0x0000, "ai_delete_self" },
{ 0x0000, "ai_delete_when_out_of_sight" },
{ 0x0000, "ai_detect_charged_damage" },
{ 0x0000, "ai_detection" },
{ 0x0000, "ai_detection_timeout" },
{ 0x0000, "ai_disable_swim_or_underwater_walk" },
{ 0x0000, "ai_diveboat_foam_trail" },
{ 0x0000, "ai_diveboats_chase_trail" },
{ 0x0000, "ai_dont_glow_in_thermal" },
{ 0x0000, "ai_empty" },
{ 0x0000, "ai_enable_swim_or_underwater_walk" },
{ 0x0000, "ai_end_fixed_node" },
{ 0x0000, "ai_end_ignore_all" },
{ 0x0000, "ai_end_ignore_me" },
{ 0x0000, "ai_end_magic_bullet_shield" },
{ 0x0000, "ai_flee_from_microwave" },
{ 0x0000, "ai_func_override" },
{ 0x0000, "ai_functions" },
{ 0x0000, "ai_game_mode" },
{ 0x0000, "ai_gd" },
{ 0x0000, "ai_get_behavior_function" },
{ 0x0000, "ai_go_to_goal_before_colors" },
{ 0x0000, "ai_ignore_everything" },
{ 0x0000, "ai_ignore_foliage_for_time" },
{ 0x0000, "ai_init" },
{ 0x0000, "ai_jump_over_40_down_88" },
{ 0x0000, "ai_kill" },
{ 0x0000, "ai_kill_no_ragdoll" },
{ 0x0000, "ai_kill_when_out_of_sight" },
{ 0x0000, "ai_lasers" },
{ 0x0000, "ai_lobby_think" },
{ 0x0000, "ai_mantle_over_low_cover_40" },
{ 0x0000, "ai_mb1" },
{ 0x0000, "ai_mb1_allywarp" },
{ 0x0000, "ai_mb1_drones" },
{ 0x0000, "ai_mb1_first_guard_fallback" },
{ 0x0000, "ai_mb1_jumpdown_guards" },
{ 0x0000, "ai_mb1_script_end" },
{ 0x0000, "ai_mb2" },
{ 0x0000, "ai_mb2_drones" },
{ 0x0000, "ai_mb2_enemies_run" },
{ 0x0000, "ai_mb2_enemyrun" },
{ 0x0000, "ai_mb2_gate" },
{ 0x0000, "ai_mb2_mech_watcher" },
{ 0x0000, "ai_mb2_remove_stencils" },
{ 0x0000, "ai_mb2_script_end" },
{ 0x0000, "ai_message_handler_hidden" },
{ 0x0000, "ai_message_handler_spotted" },
{ 0x0000, "ai_mode" },
{ 0x0000, "ai_motorpool_animation" },
{ 0x0000, "ai_notify" },
{ 0x0000, "ai_number" },
{ 0x0000, "ai_player_only_damage_func" },
{ 0x0000, "ai_remove_outline_waiter" },
{ 0x0000, "ai_remove_player_only_damage" },
{ 0x0000, "ai_remove_twenty_percent_damage" },
{ 0x0000, "ai_restore_ignore_setting" },
{ 0x0000, "ai_run_behavior_until_condition" },
{ 0x0000, "ai_save_ignore_setting" },
{ 0x0000, "ai_set_custom_animation_reaction" },
{ 0x0000, "ai_set_goback_override_function" },
{ 0x0000, "ai_sets_goal" },
{ 0x0000, "ai_shoot_missile" },
{ 0x0000, "ai_shoot_missile_salvo" },
{ 0x0000, "ai_shot_by_player_team_notify" },
{ 0x0000, "ai_should_be_added" },
{ 0x0000, "ai_silo_floor_01_balcony" },
{ 0x0000, "ai_silo_floor_01_wave_2_think" },
{ 0x0000, "ai_silo_floor_01_wave_3_think" },
{ 0x0000, "ai_silo_think" },
{ 0x0000, "ai_slide_across_car" },
{ 0x0000, "ai_special_retreat_watcher" },
{ 0x0000, "ai_start_balcony_death" },
{ 0x0000, "ai_start_ignore_all" },
{ 0x0000, "ai_start_ignore_me" },
{ 0x0000, "ai_start_magic_bullet_shield" },
{ 0x0000, "ai_start_pacifist" },
{ 0x0000, "ai_start_respawn_death" },
{ 0x0000, "ai_stealth_pause_handler" },
{ 0x0000, "ai_step_up_32" },
{ 0x0000, "ai_stop_death_function" },
{ 0x0000, "ai_stun" },
{ 0x0000, "ai_swim_death" },
{ 0x0000, "ai_swim_pain" },
{ 0x0000, "ai_target" },
{ 0x0000, "ai_target_force" },
{ 0x0000, "ai_target_force_damaged" },
{ 0x0000, "ai_target_force_scripted" },
{ 0x0000, "ai_thermal" },
{ 0x0000, "ai_toggle_cloak" },
{ 0x0000, "ai_toggle_cloak_animate" },
{ 0x0000, "ai_toggle_cloak_complete_vo" },
{ 0x0000, "ai_toggle_cloak_start_vo" },
{ 0x0000, "ai_twenty_percent_damage_func" },
{ 0x0000, "ai_unignore_everything" },
{ 0x0000, "ai_wading_footsteps" },
{ 0x0000, "ai_wait_go" },
{ 0x0000, "ai_water_footstep" },
{ 0x0000, "ai_water_set_depth" },
{ 0x0000, "ai_wave_monitor_retreat" },
{ 0x0000, "ai_wave_monitor_threshold" },
{ 0x0000, "ai_wave_setgoalvolume" },
{ 0x0000, "ai_wave_spawn" },
{ 0x0000, "ai_wave_spawn_volume" },
{ 0x0000, "ai_wave_spawn_volume_threshold" },
{ 0x0000, "ai_wave_spawn_volume_threshold_retreat" },
{ 0x0000, "aianim_simple" },
{ 0x0000, "aianim_simple_vehicle" },
{ 0x0000, "aiareintheroom" },
{ 0x0000, "aiarraydeleteonflag" },
{ 0x0000, "aiarrayfallbackonflag" },
{ 0x0000, "aiarrayidleloop" },
{ 0x0000, "aiarraymovetonewidlepos" },
{ 0x0000, "aiarrayoverridemodelrandom" },
{ 0x0000, "aiattack" },
{ 0x0000, "aibattlechatterloop" },
{ 0x0000, "aicount" },
{ 0x0000, "aideathenemy" },
{ 0x0000, "aideatheventthread" },
{ 0x0000, "aideathfriendly" },
{ 0x0000, "aideleteonflag" },
{ 0x0000, "aidisablestealthcombat" },
{ 0x0000, "aidisplacewaiter" },
{ 0x0000, "aienablestealthcombat" },
{ 0x0000, "aienabletotalcombat" },
{ 0x0000, "aifallbackonflag" },
{ 0x0000, "aifollow" },
{ 0x0000, "aifolloworderwaiter" },
{ 0x0000, "aigrenadedangerwaiter" },
{ 0x0000, "aigroup_create" },
{ 0x0000, "aigroup_soldierthink" },
{ 0x0000, "aigroup_spawnerdeath" },
{ 0x0000, "aigroup_spawnerempty" },
{ 0x0000, "aigroup_spawnerthink" },
{ 0x0000, "aihasweapon" },
{ 0x0000, "aihostileburstloop" },
{ 0x0000, "aiidleloop" },
{ 0x0000, "aiidleloopdisable" },
{ 0x0000, "aiinwater" },
{ 0x0000, "aikilleventthread" },
{ 0x0000, "aikills" },
{ 0x0000, "aim_accel_turnrate_lerp" },
{ 0x0000, "aim_additives_think" },
{ 0x0000, "aim_assist_bmodel" },
{ 0x0000, "aim_assist_using_bmodels_init" },
{ 0x0000, "aim_assist_with_bmodels" },
{ 0x0000, "aim_at_my_attacker" },
{ 0x0000, "aim_axis_of_selected_ents" },
{ 0x0000, "aim_burke_at_angles" },
{ 0x0000, "aim_hud" },
{ 0x0000, "aim_hud_on" },
{ 0x0000, "aim_test" },
{ 0x0000, "aim_turnrate_pitch" },
{ 0x0000, "aim_turnrate_pitch_ads" },
{ 0x0000, "aim_turnrate_yaw" },
{ 0x0000, "aim_turnrate_yaw_ads" },
{ 0x0000, "aim_turret_at_ambush_point_or_visible_e"... },
{ 0x0000, "aim_while_moving_thread" },
{ 0x0000, "aimassist_target" },
{ 0x0000, "aimblendtime" },
{ 0x0000, "aimbutdontshoot" },
{ 0x0000, "aimedatshootentorpos" },
{ 0x0000, "aimedsomewhatatenemy" },
{ 0x0000, "aimfaryawtolerance" },
{ 0x0000, "aimidlethread" },
{ 0x0000, "aimovetonewidlepos" },
{ 0x0000, "aimpitchdifftolerance" },
{ 0x0000, "aimsetupblendtime" },
{ 0x0000, "aimtarget" },
{ 0x0000, "aimweight" },
{ 0x0000, "aimweight_end" },
{ 0x0000, "aimweight_start" },
{ 0x0000, "aimweight_t" },
{ 0x0000, "aimweight_transframes" },
{ 0x0000, "aimyawdiffclosedistsq" },
{ 0x0000, "aimyawdiffclosetolerance" },
{ 0x0000, "aimyawdifffartolerance" },
{ 0x0000, "ainame" },
{ 0x0000, "ainameandrankwaiter" },
{ 0x0000, "aiofficerorders" },
{ 0x0000, "aioverridemodel" },
{ 0x0000, "aioverridemodelrandom" },
{ 0x0000, "aiowner" },
{ 0x0000, "air_strip_ambient_a10_gun_dive_1" },
{ 0x0000, "air_strip_ambient_a10_gun_dive_2" },
{ 0x0000, "air_strip_ambient_a10_gun_dive_3" },
{ 0x0000, "air_strip_ambient_dogfight_1" },
{ 0x0000, "air_strip_ambient_dogfight_2" },
{ 0x0000, "air_strip_ambient_dogfight_3" },
{ 0x0000, "airank" },
{ 0x0000, "airbrake_hint" },
{ 0x0000, "aircraft_wash" },
{ 0x0000, "aircraft_wash_thread" },
{ 0x0000, "airdropcratecollision" },
{ 0x0000, "airplane_list" },
{ 0x0000, "airstrike_drones" },
{ 0x0000, "airstrike_earthquake" },
{ 0x0000, "airstrike_flares_monitor" },
{ 0x0000, "airstrikefx" },
{ 0x0000, "airstrikeinprogress" },
{ 0x0000, "airstrikeoverrides" },
{ 0x0000, "airstriketype" },
{ 0x0000, "airtoairevent" },
{ 0x0000, "airtogroundevent" },
{ 0x0000, "aistartusingassaultvehicle" },
{ 0x0000, "aispread" },
{ 0x0000, "aistate" },
{ 0x0000, "aistealthcombatenemygotocover" },
{ 0x0000, "aisuppressai" },
{ 0x0000, "aithreadthreader" },
{ 0x0000, "aiturnnotifies" },
{ 0x0000, "aitype_check" },
{ 0x0000, "aiupdateanimstate" },
{ 0x0000, "aiupdatecombat" },
{ 0x0000, "aiupdatesuppressed" },
{ 0x0000, "aiweapon" },
{ 0x0000, "ajani" },
{ 0x0000, "akimboweaponent" },
{ 0x0000, "alarm_annoyance" },
{ 0x0000, "alarm_create_loops" },
{ 0x0000, "alarm_enable" },
{ 0x0000, "alarm_guid" },
{ 0x0000, "alarm_interval" },
{ 0x0000, "alarm_is_playing" },
{ 0x0000, "alarm_monitor_cleanup" },
{ 0x0000, "alarm_on" },
{ 0x0000, "alarm_playing" },
{ 0x0000, "alarm_reverb_distance_mix" },
{ 0x0000, "alarm_start" },
{ 0x0000, "alarm_start_loops" },
{ 0x0000, "alarm_stop_loops" },
{ 0x0000, "alarm_update_loops" },
{ 0x0000, "alarm_validate_damage" },
{ 0x0000, "alarmfx" },
{ 0x0000, "alarmfx01" },
{ 0x0000, "alarmsoundent" },
{ 0x0000, "alarmsystem" },
{ 0x0000, "alcove_clips" },
{ 0x0000, "alert_check_function" },
{ 0x0000, "alert_level" },
{ 0x0000, "alert_level_table" },
{ 0x0000, "alert_sound" },
{ 0x0000, "alert_stop_animating" },
{ 0x0000, "alert_when_another_is_hurt" },
{ 0x0000, "alertai" },
{ 0x0000, "alertaigroup" },
{ 0x0000, "alertallpoolguards" },
{ 0x0000, "alerted" },
{ 0x0000, "alerted_amount" },
{ 0x0000, "alerted_by_corpse" },
{ 0x0000, "alertedenemies" },
{ 0x0000, "alertedentity" },
{ 0x0000, "alertedinfo" },
{ 0x0000, "alertface" },
{ 0x0000, "alertgroup" },
{ 0x0000, "alerthighlighthudeffect" },
{ 0x0000, "alerttimedelay" },
{ 0x0000, "alias" },
{ 0x0000, "alias_data" },
{ 0x0000, "alias_name" },
{ 0x0000, "aliens_make_entity_sentient_func" },
{ 0x0000, "align_hint_think" },
{ 0x0000, "alignment_factor" },
{ 0x0000, "alive" },
{ 0x0000, "alivecount" },
{ 0x0000, "aliveplayers" },
{ 0x0000, "all_avatars_scheduled_for_delete" },
{ 0x0000, "all_dom_flags" },
{ 0x0000, "all_exopush_enemies_dead" },
{ 0x0000, "all_hp_zones" },
{ 0x0000, "all_players_istouching" },
{ 0x0000, "all_team_streak_col" },
{ 0x0000, "all3duiscreens" },
{ 0x0000, "allboothdisplays" },
{ 0x0000, "allenemyambushers" },
{ 0x0000, "allenemypatrollers" },
{ 0x0000, "allenemyvehicles" },
{ 0x0000, "allenvarray" },
{ 0x0000, "alley_1_big_metal_gate" },
{ 0x0000, "alley_1_complete_dialogue" },
{ 0x0000, "alley_a_dialogue" },
{ 0x0000, "alley_b_dialogue" },
{ 0x0000, "alley_beckon" },
{ 0x0000, "alley_combat_dialogue" },
{ 0x0000, "alley_dialogue" },
{ 0x0000, "alley_ending_point_trigger" },
{ 0x0000, "alley_fail_dialogue" },
{ 0x0000, "alley_flank_dialogue" },
{ 0x0000, "alley_flank_dialogue_nag" },
{ 0x0000, "alley_gideon_slide" },
{ 0x0000, "alley_meetup_dialogue" },
{ 0x0000, "alley_oncoming_dialogue" },
{ 0x0000, "alley_setup" },
{ 0x0000, "alley_veh_god_on" },
{ 0x0000, "alley1_combat" },
{ 0x0000, "alley1_force_deaths" },
{ 0x0000, "alley1_kva" },
{ 0x0000, "alley1_oncoming" },
{ 0x0000, "alley1_oncoming_burke_alley_enter" },
{ 0x0000, "alley1_oncoming_goto" },
{ 0x0000, "alley1_oncoming_grenade_awareness" },
{ 0x0000, "alley1_oncoming_truck_anims" },
{ 0x0000, "alley1_oncoming_truck_seq" },
{ 0x0000, "alley1_oncoming_truck_sweeper_monitor" },
{ 0x0000, "alley1_oncoming_turret_fire" },
{ 0x0000, "alley1_oncoming_turret_think" },
{ 0x0000, "alley1_stage1_combat" },
{ 0x0000, "alley1_stage1_rooftop_movedown" },
{ 0x0000, "alley1_stage2_combat" },
{ 0x0000, "alley1_stage2_combat_flag" },
{ 0x0000, "alley1_stage3_combat" },
{ 0x0000, "alley1_stage3_combat_flag" },
{ 0x0000, "alley1_stage3_refill_think" },
{ 0x0000, "alley1_veh_destro" },
{ 0x0000, "alley2_combat" },
{ 0x0000, "alley2_combat_enemy_vol_assign" },
{ 0x0000, "alley2_combat_player_monitor" },
{ 0x0000, "alley2_combat_vol_assign" },
{ 0x0000, "alley2_jumpers" },
{ 0x0000, "alley2_jumpers_setup" },
{ 0x0000, "alley2_kva" },
{ 0x0000, "alley2_spawner_locator" },
{ 0x0000, "alley2_stage1_combat" },
{ 0x0000, "alley2_stage2_combat" },
{ 0x0000, "alley2_stage3_combat" },
{ 0x0000, "alleys_distant_emergency_siren_blasts" },
{ 0x0000, "alleys_distant_euro_siren_loop" },
{ 0x0000, "alleys_distant_standard_siren_loop" },
{ 0x0000, "alleys_end_music" },
{ 0x0000, "alleys_music_end" },
{ 0x0000, "alleys_rpg_fight_music" },
{ 0x0000, "alleys_rpg_music" },
{ 0x0000, "alleys_rpg_music_backup_trigger" },
{ 0x0000, "alleysallymovement" },
{ 0x0000, "alleysbegin" },
{ 0x0000, "alleysbegincombatdialog" },
{ 0x0000, "alleyscafeanims" },
{ 0x0000, "alleyscheckifplayerretreated" },
{ 0x0000, "alleyscombat" },
{ 0x0000, "alleyscombatbacklinefloodspawns" },
{ 0x0000, "alleyscombatbacklineleftinteriorfloor1" },
{ 0x0000, "alleyscombatbacklineleftside" },
{ 0x0000, "alleyscombatbacklinerightinteriorfloor1" },
{ 0x0000, "alleyscombatbacklinerightinteriorfloor2" },
{ 0x0000, "alleyscombatbacklinerightside" },
{ 0x0000, "alleyscombatenemycountmonitor" },
{ 0x0000, "alleyscombatenemyorders" },
{ 0x0000, "alleyscombatenemyretreat" },
{ 0x0000, "alleyscombatenemysetup" },
{ 0x0000, "alleyscombatenterbuilding" },
{ 0x0000, "alleyscombatfinalbldgfloodspawns" },
{ 0x0000, "alleyscombatfinalbuilding" },
{ 0x0000, "alleyscombatfinalbuildinginterior" },
{ 0x0000, "alleyscombatfinalbuildingshotgunners" },
{ 0x0000, "alleyscombatfrontlinefloodspawns" },
{ 0x0000, "alleyscombatfrontlineleftbackstairs" },
{ 0x0000, "alleyscombatfrontlineleftside" },
{ 0x0000, "alleyscombatfrontlineleftsideinteriorfl"... },
{ 0x0000, "alleyscombatfrontlinerightbackatm" },
{ 0x0000, "alleyscombatfrontlinerightside" },
{ 0x0000, "alleyscombatinteriorfakebulletsactivate" },
{ 0x0000, "alleyscombatinteriorfakebulletssetup" },
{ 0x0000, "alleyscombatmidlineleftside" },
{ 0x0000, "alleyscombatmidlinerightside" },
{ 0x0000, "alleyscombatmidlinerightsideinterior" },
{ 0x0000, "alleyscombattriggertoggles" },
{ 0x0000, "alleysdialogtimer" },
{ 0x0000, "alleysdronecivilians" },
{ 0x0000, "alleysdronegawker" },
{ 0x0000, "alleysenemyretreat" },
{ 0x0000, "alleysenemyrpg" },
{ 0x0000, "alleysenemyspawns" },
{ 0x0000, "alleysflaginit" },
{ 0x0000, "alleysgatebash" },
{ 0x0000, "alleysgatebashrumblelight" },
{ 0x0000, "alleysgateriprumbleheavy" },
{ 0x0000, "alleysgateripunblockpath" },
{ 0x0000, "alleysglobalsetup" },
{ 0x0000, "alleysglobalvars" },
{ 0x0000, "alleysilanaleadstheway" },
{ 0x0000, "alleysintroanims" },
{ 0x0000, "alleysintrotransitiondialogue" },
{ 0x0000, "alleyskvaintrodialogue" },
{ 0x0000, "alleysmidpointreminder" },
{ 0x0000, "alleysmonitorgateriphint" },
{ 0x0000, "alleysobjectivesetup" },
{ 0x0000, "alleysprecache" },
{ 0x0000, "alleysremainingenemies" },
{ 0x0000, "alleysrpgguyshootfirst" },
{ 0x0000, "alleyssetcompletedobjflags" },
{ 0x0000, "alleyssniperpip" },
{ 0x0000, "alleysspawnrpgenemies" },
{ 0x0000, "alleysstartpoints" },
{ 0x0000, "alleysstreettransitiondialogue" },
{ 0x0000, "alleysvehicleexplodeondeath" },
{ 0x0000, "alleysvehiclemonitor" },
{ 0x0000, "alleysvideolog" },
{ 0x0000, "alleysvisitorcentergate" },
{ 0x0000, "alleysvisitorcentergatereminder" },
{ 0x0000, "alleyway_fight_enemies" },
{ 0x0000, "allfloorpannels" },
{ 0x0000, "allies_bunker" },
{ 0x0000, "allies_careful" },
{ 0x0000, "allies_check_cloak_state" },
{ 0x0000, "allies_cover_michell" },
{ 0x0000, "allies_dialog_col" },
{ 0x0000, "allies_inert" },
{ 0x0000, "allies_plane" },
{ 0x0000, "allies_rally_init" },
{ 0x0000, "allies_s1" },
{ 0x0000, "allies_s2" },
{ 0x0000, "allies_start_spawn_name" },
{ 0x0000, "allies_to_building_exit" },
{ 0x0000, "allies_to_drone_swarm" },
{ 0x0000, "allies_to_first_land_assist" },
{ 0x0000, "allies_to_first_land_assist_debug" },
{ 0x0000, "allies_to_fob" },
{ 0x0000, "allies_to_fob_think" },
{ 0x0000, "allies_to_hill" },
{ 0x0000, "allies_to_truck_jump" },
{ 0x0000, "allies_to_weapons_platform_video_log" },
{ 0x0000, "alliesbreachatrium" },
{ 0x0000, "alliesbreachatriumonalarm" },
{ 0x0000, "alliesbreachconfroom" },
{ 0x0000, "alliescapturing" },
{ 0x0000, "allieschopper" },
{ 0x0000, "alliesdrivein" },
{ 0x0000, "alliesexitatrium" },
{ 0x0000, "alliesexitconfroom" },
{ 0x0000, "alliesexittruck" },
{ 0x0000, "alliesflagcarrierclientnum" },
{ 0x0000, "alliesflagstatus" },
{ 0x0000, "alliesparkingdefend" },
{ 0x0000, "alliesparkingkill" },
{ 0x0000, "alliesparkingkillalt" },
{ 0x0000, "alliesparkingkillvictim" },
{ 0x0000, "alliesparkingsetup" },
{ 0x0000, "alliesredirect" },
{ 0x0000, "alliesshootpooltargets" },
{ 0x0000, "alliesvulnerabletime" },
{ 0x0000, "allieswarningtime" },
{ 0x0000, "allow_backstabbers" },
{ 0x0000, "allow_boost_jump" },
{ 0x0000, "allow_death_delay" },
{ 0x0000, "allow_death_during_zipline" },
{ 0x0000, "allow_death_timer" },
{ 0x0000, "allow_dog_paired_melee_vs_ai" },
{ 0x0000, "allow_early_back_out" },
{ 0x0000, "allow_exo_climb" },
{ 0x0000, "allow_fake_shooting" },
{ 0x0000, "allow_pipe_damage" },
{ 0x0000, "allow_player_hovertank_mount" },
{ 0x0000, "allow_player_input_1" },
{ 0x0000, "allow_player_input_2" },
{ 0x0000, "allow_player_zip" },
{ 0x0000, "allow_random_killers" },
{ 0x0000, "allow_swimming" },
{ 0x0000, "allow_threat_paint" },
{ 0x0000, "allowable_double_attachments" },
{ 0x0000, "allowboostingabovetriggerradius" },
{ 0x0000, "allowcarry" },
{ 0x0000, "allowclasschoice" },
{ 0x0000, "allowdronedelivery" },
{ 0x0000, "allowedcallouts" },
{ 0x0000, "allowedpartialreloadontheruntime" },
{ 0x0000, "allowempdamage" },
{ 0x0000, "allowenemyspectate" },
{ 0x0000, "allowfauxdeath" },
{ 0x0000, "allowfreespectate" },
{ 0x0000, "allowlaststandai" },
{ 0x0000, "allowlatecomers" },
{ 0x0000, "allowmeleedamage" },
{ 0x0000, "allowneutral" },
{ 0x0000, "allowplayerscore" },
{ 0x0000, "allowshoot" },
{ 0x0000, "allowteamchoice" },
{ 0x0000, "allowtelefrag" },
{ 0x0000, "allowuse" },
{ 0x0000, "allowvehicledamage" },
{ 0x0000, "allowvote" },
{ 0x0000, "allowweapons" },
{ 0x0000, "alltargetlogicarray" },
{ 0x0000, "alltargetmax" },
{ 0x0000, "alltargetmin" },
{ 0x0000, "alltargetsarray" },
{ 0x0000, "alltriggerarray" },
{ 0x0000, "allvfx_struct" },
{ 0x0000, "ally" },
{ 0x0000, "ally_advance_ahead_upon_killing_group" },
{ 0x0000, "ally_ai_active" },
{ 0x0000, "ally_alert_vol" },
{ 0x0000, "ally_anims" },
{ 0x0000, "ally_determine_move_speed" },
{ 0x0000, "ally_dynamic_run_set" },
{ 0x0000, "ally_enable_boost_traversals" },
{ 0x0000, "ally_fire_on_dam" },
{ 0x0000, "ally_grapple" },
{ 0x0000, "ally_jet_shoot_think" },
{ 0x0000, "ally_move_dynamic_speed" },
{ 0x0000, "ally_mover" },
{ 0x0000, "ally_one_handed_grenade_proc" },
{ 0x0000, "ally_redirect_goto_node" },
{ 0x0000, "ally_reset_dynamic_speed" },
{ 0x0000, "ally_s2_squad_member_1" },
{ 0x0000, "ally_s2_squad_member_2" },
{ 0x0000, "ally_s2_squad_member_3" },
{ 0x0000, "ally_s2_squad_member_4" },
{ 0x0000, "ally_shoot_rpg_at_drones" },
{ 0x0000, "ally_squad_member_1" },
{ 0x0000, "ally_squad_member_2" },
{ 0x0000, "ally_squad_member_3" },
{ 0x0000, "ally_squad_member_4" },
{ 0x0000, "ally_stop_dynamic_speed" },
{ 0x0000, "ally_vo_controller" },
{ 0x0000, "ally_vo_org" },
{ 0x0000, "allyagentthink" },
{ 0x0000, "allybreachconfroomanddie" },
{ 0x0000, "allyburkeparkingsetup" },
{ 0x0000, "allyclaimedtarget" },
{ 0x0000, "allyclearforcegoalonend" },
{ 0x0000, "allyconfroomdeath" },
{ 0x0000, "allyexithandlevictim" },
{ 0x0000, "allyexitpool" },
{ 0x0000, "allyexittruck" },
{ 0x0000, "allyinfiltrators" },
{ 0x0000, "allypoolclimb" },
{ 0x0000, "allypoolkill" },
{ 0x0000, "allypoolsetup" },
{ 0x0000, "allyredirect" },
{ 0x0000, "allyredirectgotonode" },
{ 0x0000, "allyredirectnoteworthy" },
{ 0x0000, "allyscrambleanimations" },
{ 0x0000, "allysetupconfroom" },
{ 0x0000, "allysetupstruggle" },
{ 0x0000, "allyshootpooltarget" },
{ 0x0000, "allyshootwalkwaytarget" },
{ 0x0000, "allysquad" },
{ 0x0000, "allystealthanimations" },
{ 0x0000, "allystruggleslomo" },
{ 0x0000, "allystrugglesuccess" },
{ 0x0000, "allytanks" },
{ 0x0000, "allywalkwaykill" },
{ 0x0000, "allywalkwaykillvictim" },
{ 0x0000, "almost_dead" },
{ 0x0000, "alpha_leader" },
{ 0x0000, "alpha_leader_think" },
{ 0x0000, "alpha_squad" },
{ 0x0000, "alpha_squad_and_player" },
{ 0x0000, "alphabetize" },
{ 0x0000, "alphabetize_localized_string" },
{ 0x0000, "already_dumpped" },
{ 0x0000, "already_got_end_level_notetrack" },
{ 0x0000, "already_ran_function" },
{ 0x0000, "already_set" },
{ 0x0000, "already_used" },
{ 0x0000, "alreadyaddedtoalivecount" },
{ 0x0000, "alt_rspns_random_test" },
{ 0x0000, "alt_rspns_test_func" },
{ 0x0000, "alternates" },
{ 0x0000, "altmeleedeath" },
{ 0x0000, "altmeleevictimorientation" },
{ 0x0000, "always_loop_ents" },
{ 0x0000, "always_pain" },
{ 0x0000, "always_sprint" },
{ 0x0000, "always_wake_drones" },
{ 0x0000, "alwaysdrawfriendlynames" },
{ 0x0000, "alwayslookatfirsttarget" },
{ 0x0000, "alwaysrocketdeath" },
{ 0x0000, "alwaysrunforward" },
{ 0x0000, "alwaysstaticout" },
{ 0x0000, "alwaysusepistol" },
{ 0x0000, "am_i_hit" },
{ 0x0000, "am_i_moving" },
{ 0x0000, "amb_push_oneshots" },
{ 0x0000, "amb_pushing" },
{ 0x0000, "amb_sky_combat" },
{ 0x0000, "amb_sky_combat_setup" },
{ 0x0000, "ambience" },
{ 0x0000, "ambience_inner" },
{ 0x0000, "ambience_outer" },
{ 0x0000, "ambient_animate" },
{ 0x0000, "ambient_battle_deployable_cover" },
{ 0x0000, "ambient_building_fires_fob_drone_swarm" },
{ 0x0000, "ambient_combat" },
{ 0x0000, "ambient_combat_allies" },
{ 0x0000, "ambient_combat_axis" },
{ 0x0000, "ambient_combat_vo" },
{ 0x0000, "ambient_deck" },
{ 0x0000, "ambient_dialogue_manager" },
{ 0x0000, "ambient_drones" },
{ 0x0000, "ambient_eq" },
{ 0x0000, "ambient_explosion_before_landing" },
{ 0x0000, "ambient_explosion_courtyard" },
{ 0x0000, "ambient_explosion_dirt_cooling_towers" },
{ 0x0000, "ambient_explosion_fireball_cooling_towe"... },
{ 0x0000, "ambient_explosion_play" },
{ 0x0000, "ambient_explosions" },
{ 0x0000, "ambient_fan_rotate" },
{ 0x0000, "ambient_fires_inside_building" },
{ 0x0000, "ambient_flare_fx" },
{ 0x0000, "ambient_gas_explosion_loading_zone" },
{ 0x0000, "ambient_hangar" },
{ 0x0000, "ambient_hangar_fan_blade_rotate" },
{ 0x0000, "ambient_hangar_fan_blades_setup" },
{ 0x0000, "ambient_hangar_workers" },
{ 0x0000, "ambient_hangar_workers_spawn_settings" },
{ 0x0000, "ambient_large_pipe_effects_courtyard" },
{ 0x0000, "ambient_mb1_crane" },
{ 0x0000, "ambient_mb2_claw_platform" },
{ 0x0000, "ambient_mb2_crane" },
{ 0x0000, "ambient_mb2_cranes" },
{ 0x0000, "ambient_mb2_tanks" },
{ 0x0000, "ambient_model_fix" },
{ 0x0000, "ambient_modifier" },
{ 0x0000, "ambient_police_drone_vo" },
{ 0x0000, "ambient_police_drones" },
{ 0x0000, "ambient_reverb" },
{ 0x0000, "ambient_shrike_flyby" },
{ 0x0000, "ambient_smk_walkway" },
{ 0x0000, "ambient_sniper_rockets" },
{ 0x0000, "ambient_soldier_vo_01" },
{ 0x0000, "ambient_soldier_vo_02" },
{ 0x0000, "ambient_soldier_vo_03" },
{ 0x0000, "ambient_soldier_vo_04" },
{ 0x0000, "ambient_soldier_vo_05" },
{ 0x0000, "ambient_soldier_vo_06" },
{ 0x0000, "ambient_track" },
{ 0x0000, "ambient_underwater_effects_rescue" },
{ 0x0000, "ambient_warbird_fire" },
{ 0x0000, "ambient_warbird_shooting_think" },
{ 0x0000, "ambient_warbird_wait_to_fire" },
{ 0x0000, "ambientanimation" },
{ 0x0000, "ambientcloudskill" },
{ 0x0000, "ambientcloudsloadin" },
{ 0x0000, "ambientdelay" },
{ 0x0000, "ambientevent" },
{ 0x0000, "ambienteventstart" },
{ 0x0000, "ambientexp" },
{ 0x0000, "ambienthdr" },
{ 0x0000, "ambulance_damage_part" },
{ 0x0000, "ambulance_firstframe_function" },
{ 0x0000, "ambulance_max_health" },
{ 0x0000, "ambulance_objective_update" },
{ 0x0000, "ambulance_part_monitor" },
{ 0x0000, "ambulance_push_active" },
{ 0x0000, "ambulance_push_attach" },
{ 0x0000, "ambulance_push_idle" },
{ 0x0000, "ambulance_push_sequence_end" },
{ 0x0000, "ambulance_push_step_away" },
{ 0x0000, "ambush_ambushed_vo" },
{ 0x0000, "ambush_breakout" },
{ 0x0000, "ambush_duration" },
{ 0x0000, "ambush_end" },
{ 0x0000, "ambush_entrances" },
{ 0x0000, "ambush_events" },
{ 0x0000, "ambush_heli_explosion" },
{ 0x0000, "ambush_player_if_alive_exopush" },
{ 0x0000, "ambush_trap_ent" },
{ 0x0000, "ambush_wait" },
{ 0x0000, "ambush_yaw" },
{ 0x0000, "ambushendtime" },
{ 0x0000, "ambushnode" },
{ 0x0000, "ambushtimer" },
{ 0x0000, "americans" },
{ 0x0000, "americans_setup" },
{ 0x0000, "ammo" },
{ 0x0000, "ammo_cache_think_global" },
{ 0x0000, "ammo_icon" },
{ 0x0000, "ammo_icon_fade_in" },
{ 0x0000, "ammo_icon_fade_out" },
{ 0x0000, "ammo_icon_think" },
{ 0x0000, "ammo_icon_trig" },
{ 0x0000, "ammo_max" },
{ 0x0000, "ammo_pickup" },
{ 0x0000, "ammocheatinterval" },
{ 0x0000, "ammocheattime" },
{ 0x0000, "ammofeeder" },
{ 0x0000, "ammopickup" },
{ 0x0000, "ammopickup_scalar" },
{ 0x0000, "ammopickupfunc" },
{ 0x0000, "ammopickupmodel" },
{ 0x0000, "ammorefillprimary" },
{ 0x0000, "ammorefillsecondary" },
{ 0x0000, "amount" },
{ 0x0000, "amount_in_sights" },
{ 0x0000, "amplify_vfx" },
{ 0x0000, "ams_enabled" },
{ 0x0000, "ams_get_state" },
{ 0x0000, "ams_init" },
{ 0x0000, "ams_intensity" },
{ 0x0000, "ams_player_health" },
{ 0x0000, "ams_proxy_vehicle_speed" },
{ 0x0000, "ams_set_intensity" },
{ 0x0000, "ams_set_proxy_vehicle" },
{ 0x0000, "ams_set_state" },
{ 0x0000, "ams_start" },
{ 0x0000, "ams_stop" },
{ 0x0000, "amsx_get" },
{ 0x0000, "amsx_get_proxy" },
{ 0x0000, "amsx_get_proxy_vehicle_ent" },
{ 0x0000, "amv_jetbike_height_time" },
{ 0x0000, "amv_jetbike_height_val" },
{ 0x0000, "angle" },
{ 0x0000, "angle_interpolate" },
{ 0x0000, "angle_lerp" },
{ 0x0000, "angle_offset" },
{ 0x0000, "angleaccel" },
{ 0x0000, "anglelimit" },
{ 0x0000, "anglerangethread" },
{ 0x0000, "angles_and_origin" },
{ 0x0000, "angles_clamp_180" },
{ 0x0000, "angles_lerp" },
{ 0x0000, "angles_origin" },
{ 0x0000, "anglescheck" },
{ 0x0000, "anglesclamp180" },
{ 0x0000, "anglesondeath" },
{ 0x0000, "anglesonkill" },
{ 0x0000, "anglessubtract" },
{ 0x0000, "anglevalid" },
{ 0x0000, "angspeed" },
{ 0x0000, "anim_1" },
{ 0x0000, "anim_2" },
{ 0x0000, "anim_3" },
{ 0x0000, "anim_addmodel" },
{ 0x0000, "anim_animationendnotify" },
{ 0x0000, "anim_array" },
{ 0x0000, "anim_at_entity" },
{ 0x0000, "anim_at_self" },
{ 0x0000, "anim_blend_time_override" },
{ 0x0000, "anim_burke_boost_lets_go" },
{ 0x0000, "anim_burke_crawl" },
{ 0x0000, "anim_changes_pushplayer" },
{ 0x0000, "anim_custom_animmode" },
{ 0x0000, "anim_custom_animmode_loop" },
{ 0x0000, "anim_custom_animmode_loop_solo" },
{ 0x0000, "anim_custom_animmode_on_guy" },
{ 0x0000, "anim_custom_animmode_solo" },
{ 0x0000, "anim_deathnotify" },
{ 0x0000, "anim_debug" },
{ 0x0000, "anim_dialogueendnotify" },
{ 0x0000, "anim_disablepain" },
{ 0x0000, "anim_dontpushplayer" },
{ 0x0000, "anim_down" },
{ 0x0000, "anim_end_early" },
{ 0x0000, "anim_end_early_animationendnotify" },
{ 0x0000, "anim_end_early_deathnotify" },
{ 0x0000, "anim_end_early_dialogueendnotify" },
{ 0x0000, "anim_end_early_facialendnotify" },
{ 0x0000, "anim_exists" },
{ 0x0000, "anim_facialanim" },
{ 0x0000, "anim_facialendnotify" },
{ 0x0000, "anim_facialfiller" },
{ 0x0000, "anim_first_frame" },
{ 0x0000, "anim_first_frame_on_guy" },
{ 0x0000, "anim_first_frame_solo" },
{ 0x0000, "anim_first_frame_with_finale_gameplay" },
{ 0x0000, "anim_generic" },
{ 0x0000, "anim_generic_custom_animmode" },
{ 0x0000, "anim_generic_custom_animmode_loop" },
{ 0x0000, "anim_generic_first_frame" },
{ 0x0000, "anim_generic_gravity" },
{ 0x0000, "anim_generic_loop" },
{ 0x0000, "anim_generic_queue" },
{ 0x0000, "anim_generic_reach" },
{ 0x0000, "anim_generic_reach_and_arrive" },
{ 0x0000, "anim_generic_run" },
{ 0x0000, "anim_generic_teleport" },
{ 0x0000, "anim_gunhand" },
{ 0x0000, "anim_guninhand" },
{ 0x0000, "anim_handle_notetrack" },
{ 0x0000, "anim_idle_down" },
{ 0x0000, "anim_idle_up" },
{ 0x0000, "anim_is_death" },
{ 0x0000, "anim_laserbuoy" },
{ 0x0000, "anim_last_frame_solo" },
{ 0x0000, "anim_link_tag_model" },
{ 0x0000, "anim_loop" },
{ 0x0000, "anim_loop_hatch_anims_solo" },
{ 0x0000, "anim_loop_packet" },
{ 0x0000, "anim_loop_packet_solo" },
{ 0x0000, "anim_loop_solo" },
{ 0x0000, "anim_loop_solo_vm" },
{ 0x0000, "anim_loop_vm" },
{ 0x0000, "anim_moveto" },
{ 0x0000, "anim_node" },
{ 0x0000, "anim_org" },
{ 0x0000, "anim_org_ajani_post_breach" },
{ 0x0000, "anim_playsound_func" },
{ 0x0000, "anim_pos" },
{ 0x0000, "anim_prep" },
{ 0x0000, "anim_prop_init_threads" },
{ 0x0000, "anim_prop_models" },
{ 0x0000, "anim_prop_models_animtree" },
{ 0x0000, "anim_props" },
{ 0x0000, "anim_props_animated" },
{ 0x0000, "anim_pushplayer" },
{ 0x0000, "anim_rate_to_speed" },
{ 0x0000, "anim_reach" },
{ 0x0000, "anim_reach_and_approach" },
{ 0x0000, "anim_reach_and_approach_node_solo" },
{ 0x0000, "anim_reach_and_approach_solo" },
{ 0x0000, "anim_reach_and_idle" },
{ 0x0000, "anim_reach_and_idle_solo" },
{ 0x0000, "anim_reach_and_plant" },
{ 0x0000, "anim_reach_and_plant_and_arrive" },
{ 0x0000, "anim_reach_cleanup" },
{ 0x0000, "anim_reach_cleanup_solo" },
{ 0x0000, "anim_reach_failsafe" },
{ 0x0000, "anim_reach_fix" },
{ 0x0000, "anim_reach_idle" },
{ 0x0000, "anim_reach_solo" },
{ 0x0000, "anim_reach_success" },
{ 0x0000, "anim_reach_together" },
{ 0x0000, "anim_reach_together_with_overrides" },
{ 0x0000, "anim_reach_with_funcs" },
{ 0x0000, "anim_relative" },
{ 0x0000, "anim_removemodel" },
{ 0x0000, "anim_roundabout_rappel_1" },
{ 0x0000, "anim_roundabout_rappel_2" },
{ 0x0000, "anim_scene_building_exit_cormack" },
{ 0x0000, "anim_scene_building_exit_will" },
{ 0x0000, "anim_scene_building_jump" },
{ 0x0000, "anim_scene_walker_stepover" },
{ 0x0000, "anim_scene_will_grabs_car_door" },
{ 0x0000, "anim_scene_will_grabs_car_door_post_che"... },
{ 0x0000, "anim_self_set_real_time" },
{ 0x0000, "anim_self_set_time" },
{ 0x0000, "anim_sequence" },
{ 0x0000, "anim_set_rate" },
{ 0x0000, "anim_set_rate_internal" },
{ 0x0000, "anim_set_rate_single" },
{ 0x0000, "anim_set_real_time" },
{ 0x0000, "anim_set_time" },
{ 0x0000, "anim_simple" },
{ 0x0000, "anim_simple_notify" },
{ 0x0000, "anim_single" },
{ 0x0000, "anim_single_droppod_custom" },
{ 0x0000, "anim_single_end_early" },
{ 0x0000, "anim_single_failsafe" },
{ 0x0000, "anim_single_failsafeonguy" },
{ 0x0000, "anim_single_internal" },
{ 0x0000, "anim_single_mech" },
{ 0x0000, "anim_single_qte_middle" },
{ 0x0000, "anim_single_qte_middle_fail" },
{ 0x0000, "anim_single_queue" },
{ 0x0000, "anim_single_run" },
{ 0x0000, "anim_single_run_solo" },
{ 0x0000, "anim_single_solo" },
{ 0x0000, "anim_single_solo_custom" },
{ 0x0000, "anim_single_solo_d" },
{ 0x0000, "anim_single_solo_in_place" },
{ 0x0000, "anim_single_solo_internal_vm" },
{ 0x0000, "anim_single_solo_run" },
{ 0x0000, "anim_single_solo_vm" },
{ 0x0000, "anim_single_solo_with_lerp" },
{ 0x0000, "anim_single_solo_with_special_walk" },
{ 0x0000, "anim_single_solo_with_wait_flag" },
{ 0x0000, "anim_single_to_delete" },
{ 0x0000, "anim_single_to_delete_solo" },
{ 0x0000, "anim_single_to_loop" },
{ 0x0000, "anim_single_to_loop_solo" },
{ 0x0000, "anim_single_with_gameplay" },
{ 0x0000, "anim_spawn_generic_model" },
{ 0x0000, "anim_spawn_model" },
{ 0x0000, "anim_spawn_tag_model" },
{ 0x0000, "anim_spawner_teleport" },
{ 0x0000, "anim_speed" },
{ 0x0000, "anim_start_at_groundpos" },
{ 0x0000, "anim_start_pos" },
{ 0x0000, "anim_start_pos_solo" },
{ 0x0000, "anim_state" },
{ 0x0000, "anim_stop" },
{ 0x0000, "anim_stopanimscripted" },
{ 0x0000, "anim_struct" },
{ 0x0000, "anim_struct_exfil" },
{ 0x0000, "anim_struct2" },
{ 0x0000, "anim_tag" },
{ 0x0000, "anim_teleport" },
{ 0x0000, "anim_teleport_solo" },
{ 0x0000, "anim_time" },
{ 0x0000, "anim_up" },
{ 0x0000, "anim_van_intro" },
{ 0x0000, "anim_wait_func" },
{ 0x0000, "anim_weight" },
{ 0x0000, "anim_with_teleport" },
{ 0x0000, "animal_anims" },
{ 0x0000, "animalanimations" },
{ 0x0000, "animalias" },
{ 0x0000, "animarchetype" },
{ 0x0000, "animarray" },
{ 0x0000, "animarrayanyexist" },
{ 0x0000, "animarrayfuncs" },
{ 0x0000, "animarraypickrandom" },
{ 0x0000, "animate_collapse_ent" },
{ 0x0000, "animate_dead_body" },
{ 0x0000, "animate_drills" },
{ 0x0000, "animate_drive_idle" },
{ 0x0000, "animate_drive_idle_on_dummies" },
{ 0x0000, "animate_guys" },
{ 0x0000, "animate_on_goal" },
{ 0x0000, "animate_player_on_rig_simple" },
{ 0x0000, "animate_props_on_death" },
{ 0x0000, "animate_script_origin" },
{ 0x0000, "animate_the_other_guys" },
{ 0x0000, "animate_turret_with_viewmodel" },
{ 0x0000, "animated_gun" },
{ 0x0000, "animated_lights" },
{ 0x0000, "animated_pod_function" },
{ 0x0000, "animated_prop_anims" },
{ 0x0000, "animateddeath" },
{ 0x0000, "animatedpalmtrees" },
{ 0x0000, "animatemodel" },
{ 0x0000, "animatemoveintoplace" },
{ 0x0000, "animatetreewind" },
{ 0x0000, "animation_process" },
{ 0x0000, "animation_think" },
{ 0x0000, "animcbs" },
{ 0x0000, "animdodgeobstaclelistener" },
{ 0x0000, "animdown" },
{ 0x0000, "anime" },
{ 0x0000, "animent" },
{ 0x0000, "animflagnameindex" },
{ 0x0000, "animhasfacialoverride" },
{ 0x0000, "animidledown" },
{ 0x0000, "animidleup" },
{ 0x0000, "animname" },
{ 0x0000, "animnode" },
{ 0x0000, "animontag" },
{ 0x0000, "animontag_ragdoll_death" },
{ 0x0000, "animontag_ragdoll_death_fall" },
{ 0x0000, "animontag_unloading_vehicle_explosion" },
{ 0x0000, "animplaybackrate" },
{ 0x0000, "animref" },
{ 0x0000, "anims" },
{ 0x0000, "animsapplied" },
{ 0x0000, "animscript_sittag" },
{ 0x0000, "animscript_target" },
{ 0x0000, "animscriptdonotetracksthread" },
{ 0x0000, "animsequence" },
{ 0x0000, "animset" },
{ 0x0000, "animsets" },
{ 0x0000, "animsound_aliases" },
{ 0x0000, "animsound_exists" },
{ 0x0000, "animsound_hud_extralines" },
{ 0x0000, "animsound_hudlimit" },
{ 0x0000, "animsound_start_tracker" },
{ 0x0000, "animsound_start_tracker_loop" },
{ 0x0000, "animsound_tagged" },
{ 0x0000, "animsound_tracker" },
{ 0x0000, "animsounds" },
{ 0x0000, "animsounds_thisframe" },
{ 0x0000, "animstate" },
{ 0x0000, "animsubstate" },
{ 0x0000, "animtree" },
{ 0x0000, "animup" },
{ 0x0000, "anml_doberman" },
{ 0x0000, "announcerdisabled" },
{ 0x0000, "annoyance_tracker" },
{ 0x0000, "antiintrusion" },
{ 0x0000, "any_enemy_is_able_to_attack" },
{ 0x0000, "any_players_istouching" },
{ 0x0000, "any_wheel_on_ground" },
{ 0x0000, "anyattachmentisscope" },
{ 0x0000, "anyplayersinkillcam" },
{ 0x0000, "anystingermissilelockedon" },
{ 0x0000, "anythingistouching" },
{ 0x0000, "anythingtouchingtrigger" },
{ 0x0000, "apex" },
{ 0x0000, "apm_mine_deletekillcament" },
{ 0x0000, "applied_reverb" },
{ 0x0000, "apply_difficulty_frac_with_func" },
{ 0x0000, "apply_difficulty_step_with_func" },
{ 0x0000, "apply_end_fog" },
{ 0x0000, "apply_fog" },
{ 0x0000, "apply_friendly_fire_damage_modifier" },
{ 0x0000, "apply_jump_fx" },
{ 0x0000, "apply_option_to_selected_fx" },
{ 0x0000, "apply_reinforcement_perk" },
{ 0x0000, "apply_reverb" },
{ 0x0000, "apply_truckjunk" },
{ 0x0000, "apply_whizby" },
{ 0x0000, "applybombcarrierclass" },
{ 0x0000, "applyemp" },
{ 0x0000, "applyflagcarrierclass" },
{ 0x0000, "applyflash" },
{ 0x0000, "applyloadout" },
{ 0x0000, "applyperks" },
{ 0x0000, "applyprisonturretradararrow" },
{ 0x0000, "approach_barracks_combat_setup" },
{ 0x0000, "approach_handle_murica_movement_left" },
{ 0x0000, "approach_idle_ents" },
{ 0x0000, "approach_scene_ents" },
{ 0x0000, "approach_spawn_functions" },
{ 0x0000, "approach_types" },
{ 0x0000, "approachconditioncheckfunc" },
{ 0x0000, "approaching" },
{ 0x0000, "approaching_roundabout_dialogue" },
{ 0x0000, "approaching_standoff" },
{ 0x0000, "approachnumber" },
{ 0x0000, "approachtype" },
{ 0x0000, "approachtypefunc" },
{ 0x0000, "approachwaittillclose" },
{ 0x0000, "aquiring_targets_think" },
{ 0x0000, "ar_moment" },
{ 0x0000, "arc_point" },
{ 0x0000, "arcade_plane_controls" },
{ 0x0000, "arcademode" },
{ 0x0000, "arcademode_hud_timer" },
{ 0x0000, "arcademode_stop_timer" },
{ 0x0000, "arcademode_stoptime" },
{ 0x0000, "archetype_exists" },
{ 0x0000, "archetypechanged" },
{ 0x0000, "archetypeexists" },
{ 0x0000, "archetypes" },
{ 0x0000, "archive" },
{ 0x0000, "are_we_close" },
{ 0x0000, "aredifferent" },
{ 0x0000, "arm_repair_attempt" },
{ 0x0000, "armada_intro_screen" },
{ 0x0000, "armed" },
{ 0x0000, "armordamagehints" },
{ 0x0000, "armorpiercingmod" },
{ 0x0000, "armorvestmod" },
{ 0x0000, "armorygiveexoability" },
{ 0x0000, "armorypoints" },
{ 0x0000, "armorypurchasefail" },
{ 0x0000, "armorythink" },
{ 0x0000, "array" },
{ 0x0000, "array_2dadd" },
{ 0x0000, "array_add" },
{ 0x0000, "array_call" },
{ 0x0000, "array_checkaddattachment" },
{ 0x0000, "array_combine" },
{ 0x0000, "array_combine_all" },
{ 0x0000, "array_combine_keys" },
{ 0x0000, "array_combine_multiple" },
{ 0x0000, "array_combine_non_integer_indices" },
{ 0x0000, "array_combine_unique" },
{ 0x0000, "array_compare" },
{ 0x0000, "array_contains" },
{ 0x0000, "array_delete" },
{ 0x0000, "array_delete_evenly" },
{ 0x0000, "array_exclude" },
{ 0x0000, "array_find" },
{ 0x0000, "array_first" },
{ 0x0000, "array_index_by_classname" },
{ 0x0000, "array_index_by_parameters" },
{ 0x0000, "array_index_by_script_index" },
{ 0x0000, "array_insert" },
{ 0x0000, "array_kill" },
{ 0x0000, "array_levelcall" },
{ 0x0000, "array_levelthread" },
{ 0x0000, "array_levelthread_safe" },
{ 0x0000, "array_merge" },
{ 0x0000, "array_merge_links" },
{ 0x0000, "array_notify" },
{ 0x0000, "array_randomize" },
{ 0x0000, "array_remove" },
{ 0x0000, "array_remove_array" },
{ 0x0000, "array_remove_dead" },
{ 0x0000, "array_remove_duplicates" },
{ 0x0000, "array_remove_index" },
{ 0x0000, "array_remove_nokeys" },
{ 0x0000, "array_removeclaimedtargets" },
{ 0x0000, "array_removedead" },
{ 0x0000, "array_removedead_keepkeys" },
{ 0x0000, "array_removedead_or_dying" },
{ 0x0000, "array_removefirstinqueue" },
{ 0x0000, "array_removeundefined" },
{ 0x0000, "array_reverse" },
{ 0x0000, "array_safe_delete" },
{ 0x0000, "array_setgoalvolume" },
{ 0x0000, "array_sort_by_handler" },
{ 0x0000, "array_sort_with_func" },
{ 0x0000, "array_sound_start" },
{ 0x0000, "array_spawn" },
{ 0x0000, "array_spawn_allow_fail" },
{ 0x0000, "array_spawn_cg" },
{ 0x0000, "array_spawn_function" },
{ 0x0000, "array_spawn_function_noteworthy" },
{ 0x0000, "array_spawn_function_targetname" },
{ 0x0000, "array_spawn_noteworthy" },
{ 0x0000, "array_spawn_targetname" },
{ 0x0000, "array_spawn_targetname_allow_fail" },
{ 0x0000, "array_spawn_targetname_cg" },
{ 0x0000, "array_spawn_targetname_stagger" },
{ 0x0000, "array_thread" },
{ 0x0000, "array_thread_mod_delayed" },
{ 0x0000, "array_thread_safe" },
{ 0x0000, "array_thread4" },
{ 0x0000, "array_thread5" },
{ 0x0000, "array_wait" },
{ 0x0000, "array_waitlogic1" },
{ 0x0000, "array_waitlogic2" },
{ 0x0000, "array_waittill_player_lookat" },
{ 0x0000, "array_waittill_player_lookat_proc" },
{ 0x0000, "arrayinsertion" },
{ 0x0000, "arrayremovevalue" },
{ 0x0000, "arrays_color_spawners" },
{ 0x0000, "arrays_of_colorcoded_nodes" },
{ 0x0000, "arrays_of_colorcoded_volumes" },
{ 0x0000, "arrays_of_colorforced_ai" },
{ 0x0000, "arrivalanim" },
{ 0x0000, "arrivalendstance" },
{ 0x0000, "arrivalnodetype" },
{ 0x0000, "arrivalpathgoalpos" },
{ 0x0000, "arrivalstance" },
{ 0x0000, "arrivalstartdist" },
{ 0x0000, "arrivaltype" },
{ 0x0000, "arrive" },
{ 0x0000, "art_print_fog" },
{ 0x0000, "artendfogfileexport" },
{ 0x0000, "artendvisionfileexport" },
{ 0x0000, "artfxprintlnfog" },
{ 0x0000, "artifact_pulse" },
{ 0x0000, "artifacts" },
{ 0x0000, "artifacts_fade" },
{ 0x0000, "artillery_earthquake" },
{ 0x0000, "artillerydangercenters" },
{ 0x0000, "artilleryshellshock" },
{ 0x0000, "artstartfogfileexport" },
{ 0x0000, "artstartvisionfileexport" },
{ 0x0000, "assault_drone_stinger_target_pos" },
{ 0x0000, "assault_vehicle_ai_aerial_follow_path_o"... },
{ 0x0000, "assault_vehicle_ai_aerial_movement" },
{ 0x0000, "assault_vehicle_ai_aerial_pathing_c4" },
{ 0x0000, "assault_vehicle_ai_aerial_pathing_turre"... },
{ 0x0000, "assault_vehicle_ai_air_movement_func" },
{ 0x0000, "assault_vehicle_ai_can_see_living_enemy" },
{ 0x0000, "assault_vehicle_ai_end_on_owner_disconn"... },
{ 0x0000, "assault_vehicle_ai_enemy_exists_and_is_"... },
{ 0x0000, "assault_vehicle_ai_enemy_moved_air" },
{ 0x0000, "assault_vehicle_ai_enemy_moved_ground" },
{ 0x0000, "assault_vehicle_ai_follow_path" },
{ 0x0000, "assault_vehicle_ai_get_camera_position" },
{ 0x0000, "assault_vehicle_ai_get_nearest_node" },
{ 0x0000, "assault_vehicle_ai_ground_movement" },
{ 0x0000, "assault_vehicle_ai_ground_movement_loop" },
{ 0x0000, "assault_vehicle_ai_init" },
{ 0x0000, "assault_vehicle_ai_move_to_aerial_node" },
{ 0x0000, "assault_vehicle_ai_path_timeout_time" },
{ 0x0000, "assault_vehicle_ai_pick_aerial_node" },
{ 0x0000, "assault_vehicle_ai_threat" },
{ 0x0000, "assault_vehicle_ai_weapons" },
{ 0x0000, "assaultfullstaticondeath" },
{ 0x0000, "assaulthandledeath" },
{ 0x0000, "assaulthandletimeoutwarning" },
{ 0x0000, "assaulthudremove" },
{ 0x0000, "assaulthudsetup" },
{ 0x0000, "assaultobjectiveevent" },
{ 0x0000, "assaultplayerexit" },
{ 0x0000, "assaultsetinactivity" },
{ 0x0000, "assaultvehiclemonitorweapons" },
{ 0x0000, "assert_existance_of_anim" },
{ 0x0000, "assert_existance_of_anim_vm" },
{ 0x0000, "assert_existance_of_looping_anim" },
{ 0x0000, "assert_if_anim_not_defined" },
{ 0x0000, "assert_if_identical_origins" },
{ 0x0000, "assertdisplayed" },
{ 0x0000, "assertdisplayed_b" },
{ 0x0000, "asset_name" },
{ 0x0000, "asset_names" },
{ 0x0000, "asset_type" },
{ 0x0000, "assign_animals_tree" },
{ 0x0000, "assign_animtree" },
{ 0x0000, "assign_cloak_model" },
{ 0x0000, "assign_drone_tree" },
{ 0x0000, "assign_fx_to_trigger" },
{ 0x0000, "assign_generic_human_tree" },
{ 0x0000, "assign_goal_node" },
{ 0x0000, "assign_goal_vol" },
{ 0x0000, "assign_model" },
{ 0x0000, "assign_nodes_to_zipline_guys" },
{ 0x0000, "assign_npcid" },
{ 0x0000, "assign_script_breachgroup_to_ents" },
{ 0x0000, "assign_spawns" },
{ 0x0000, "assign_spawns_version_2" },
{ 0x0000, "assign_spawns_version_3" },
{ 0x0000, "assign_unique_id" },
{ 0x0000, "assignawards" },
{ 0x0000, "assigned_brush" },
{ 0x0000, "assigned_model" },
{ 0x0000, "assigned_model_b" },
{ 0x0000, "assigned_parent" },
{ 0x0000, "assignpracticeroundclasses" },
{ 0x0000, "assignteamspawns" },
{ 0x0000, "assistedsuicide" },
{ 0x0000, "assistedsuicideevent" },
{ 0x0000, "assistplayer" },
{ 0x0000, "assistpoints" },
{ 0x0000, "assists_disabled" },
{ 0x0000, "ast_mus_on" },
{ 0x0000, "at_goal" },
{ 0x0000, "at_path_end" },
{ 0x0000, "at_rest" },
{ 0x0000, "at_start" },
{ 0x0000, "at_van_enemy_cleanup" },
{ 0x0000, "atbrinkofdeath" },
{ 0x0000, "atconcealmentnode" },
{ 0x0000, "atk_bomber" },
{ 0x0000, "atk_bomber_no_path_to_bomb_count" },
{ 0x0000, "atk_bomber_update" },
{ 0x0000, "atlas_base_weapon_manager" },
{ 0x0000, "atlas_base_weapon_manager_elevator" },
{ 0x0000, "atlas_building_roof_walla" },
{ 0x0000, "atlas_drone_damage_function" },
{ 0x0000, "atlas_guard" },
{ 0x0000, "atlas_guard_dialogue_line1" },
{ 0x0000, "atlas_guard1" },
{ 0x0000, "atlas_guard2" },
{ 0x0000, "atlas_guard3" },
{ 0x0000, "atlas_guard4" },
{ 0x0000, "atlas_guard5" },
{ 0x0000, "atlas_guard6" },
{ 0x0000, "atlas_guard7" },
{ 0x0000, "atlas_intercepts" },
{ 0x0000, "atlas_sign_flicker" },
{ 0x0000, "atlas_suv_impact_fx" },
{ 0x0000, "atlas_suv_rider_no_react" },
{ 0x0000, "atlas_suv_rider_react" },
{ 0x0000, "atlas_suv_rider_think" },
{ 0x0000, "atlas_van_explode" },
{ 0x0000, "atlas1" },
{ 0x0000, "atlas2" },
{ 0x0000, "atlascard_cormack_walk" },
{ 0x0000, "atlascard_irons_grab_card" },
{ 0x0000, "atlascard_irons_handshake" },
{ 0x0000, "atlascard_irons_leave" },
{ 0x0000, "atlascard_irons_place_hand" },
{ 0x0000, "atlascard_irons_tap" },
{ 0x0000, "atlascard_irons_turn" },
{ 0x0000, "atlascard_irons_walk" },
{ 0x0000, "atlasdrn_condition_callback_to_state_de"... },
{ 0x0000, "atlasdrn_condition_callback_to_state_de"... },
{ 0x0000, "atlasdrn_condition_callback_to_state_di"... },
{ 0x0000, "atlasdrn_condition_callback_to_state_fl"... },
{ 0x0000, "atlasdrn_condition_callback_to_state_fl"... },
{ 0x0000, "atlasdrn_condition_callback_to_state_fl"... },
{ 0x0000, "atlasdrn_condition_callback_to_state_ho"... },
{ 0x0000, "atlasdrn_condition_callback_to_state_of"... },
{ 0x0000, "atlasdrn_lens_focus" },
{ 0x0000, "atm_is_muted" },
{ 0x0000, "atm_max_off_time" },
{ 0x0000, "atm_max_on_time" },
{ 0x0000, "atm_mute_time" },
{ 0x0000, "atm_off_time" },
{ 0x0000, "atmosfogdistancescale" },
{ 0x0000, "atmosfogenabled" },
{ 0x0000, "atmosfogextinctionstrength" },
{ 0x0000, "atmosfoghalfplanedistance" },
{ 0x0000, "atmosfoghazecolor" },
{ 0x0000, "atmosfoghazespread" },
{ 0x0000, "atmosfoghazestrength" },
{ 0x0000, "atmosfogheightfogbaseheight" },
{ 0x0000, "atmosfogheightfogenabled" },
{ 0x0000, "atmosfogheightfoghalfplanedistance" },
{ 0x0000, "atmosfoginscatterstrength" },
{ 0x0000, "atmosfogskyangularfalloffenabled" },
{ 0x0000, "atmosfogskydistance" },
{ 0x0000, "atmosfogskyfalloffanglerange" },
{ 0x0000, "atmosfogskyfalloffstartangle" },
{ 0x0000, "atmosfogstartdistance" },
{ 0x0000, "atmosfogsundirection" },
{ 0x0000, "atmosfogsunfogcolor" },
{ 0x0000, "atrium_breach_signal_start" },
{ 0x0000, "atrium_timer_expire" },
{ 0x0000, "atriumanimations" },
{ 0x0000, "atriumboostjump" },
{ 0x0000, "atriumboostjumpguy" },
{ 0x0000, "atriumbreachexplosionnotetrack" },
{ 0x0000, "atriumbreachidle" },
{ 0x0000, "atriumbreachidleburke" },
{ 0x0000, "atriumbreachidleinfiltrators" },
{ 0x0000, "atriumbreachmonitoralliesinposition" },
{ 0x0000, "atriumdoorbreachdamage" },
{ 0x0000, "atriumdoorsopen" },
{ 0x0000, "atriumdoorsopenonalarm" },
{ 0x0000, "atriumlookatdialogue" },
{ 0x0000, "atriumreminderdialogue" },
{ 0x0000, "atriumsetupdialogue" },
{ 0x0000, "atriumshootfirstdialogue" },
{ 0x0000, "atriumtimer" },
{ 0x0000, "atriumtimewindow" },
{ 0x0000, "atrrestoremech" },
{ 0x0000, "attach_assault_drone_lights" },
{ 0x0000, "attach_bone" },
{ 0x0000, "attach_cig" },
{ 0x0000, "attach_cig_self" },
{ 0x0000, "attach_clip" },
{ 0x0000, "attach_ent" },
{ 0x0000, "attach_fixed_scanner" },
{ 0x0000, "attach_flashlight_in_hand" },
{ 0x0000, "attach_flashlight_on_gun" },
{ 0x0000, "attach_flashlight_on_vehicle_unload" },
{ 0x0000, "attach_fx_to_mechanism" },
{ 0x0000, "attach_housing" },
{ 0x0000, "attach_light_to_face" },
{ 0x0000, "attach_light_to_police_car" },
{ 0x0000, "attach_littlebird_parts" },
{ 0x0000, "attach_model_override" },
{ 0x0000, "attach_or_link" },
{ 0x0000, "attach_phone" },
{ 0x0000, "attach_player_current_weapon_to_anim_ta"... },
{ 0x0000, "attach_player_current_weapon_to_rig" },
{ 0x0000, "attach_pointlight_to_beam" },
{ 0x0000, "attach_scanner" },
{ 0x0000, "attach_scanner_turret" },
{ 0x0000, "attach_tag" },
{ 0x0000, "attach_wakefx" },
{ 0x0000, "attach_weapon_to_tag_sync" },
{ 0x0000, "attachdistortionfx" },
{ 0x0000, "attachedguys" },
{ 0x0000, "attachedmodels" },
{ 0x0000, "attachedpath" },
{ 0x0000, "attachedpropmodel" },
{ 0x0000, "attachedproptag" },
{ 0x0000, "attachedusemodel" },
{ 0x0000, "attachflag" },
{ 0x0000, "attachgrenademodel" },
{ 0x0000, "attachhat" },
{ 0x0000, "attachhead" },
{ 0x0000, "attachmentdeath" },
{ 0x0000, "attachmentexplode" },
{ 0x0000, "attachmentmap_attachtoperk" },
{ 0x0000, "attachmentmap_basetounique" },
{ 0x0000, "attachmentmap_tobase" },
{ 0x0000, "attachmentmap_tounique" },
{ 0x0000, "attachmentmap_uniquetobase" },
{ 0x0000, "attachmentperkmap" },
{ 0x0000, "attachmenttype" },
{ 0x0000, "attachmissiles" },
{ 0x0000, "attachmodelti" },
{ 0x0000, "attachprops" },
{ 0x0000, "attachpropsfunction" },
{ 0x0000, "attachusemodel" },
{ 0x0000, "attachweapon" },
{ 0x0000, "attack_accuracy" },
{ 0x0000, "attack_available" },
{ 0x0000, "attack_behavior" },
{ 0x0000, "attack_damage_trigger" },
{ 0x0000, "attack_delay" },
{ 0x0000, "attack_drone_audio_handler" },
{ 0x0000, "attack_drone_flybys_audio" },
{ 0x0000, "attack_drone_formation_init" },
{ 0x0000, "attack_drone_init" },
{ 0x0000, "attack_drone_kamikaze_audio" },
{ 0x0000, "attack_drone_kamikaze_flying_fx" },
{ 0x0000, "attack_drone_queen_1shot_handler" },
{ 0x0000, "attack_drone_queen_audio" },
{ 0x0000, "attack_drone_queen_flybys_audio" },
{ 0x0000, "attack_drone_queen_flying_fx" },
{ 0x0000, "attack_drones_nofly_zone_radius" },
{ 0x0000, "attack_drones_num_drones_per_queen" },
{ 0x0000, "attack_drones_num_queens" },
{ 0x0000, "attack_heli_cleanup" },
{ 0x0000, "attack_heli_fx" },
{ 0x0000, "attack_heli_safe_volumes" },
{ 0x0000, "attack_hint_display" },
{ 0x0000, "attack_if_buddy_killed" },
{ 0x0000, "attack_origin_condition_threadd" },
{ 0x0000, "attack_player_for_time" },
{ 0x0000, "attack_sight_required" },
{ 0x0000, "attackback" },
{ 0x0000, "attacked_by_dog" },
{ 0x0000, "attacker_isonmyteam" },
{ 0x0000, "attacker_troop_isonmyteam" },
{ 0x0000, "attackercandamageitem" },
{ 0x0000, "attackerdata" },
{ 0x0000, "attackerent" },
{ 0x0000, "attackerinlaststand" },
{ 0x0000, "attackerinremotekillstreak" },
{ 0x0000, "attackerishittingteam" },
{ 0x0000, "attackerlist" },
{ 0x0000, "attackeronground" },
{ 0x0000, "attackerposition" },
{ 0x0000, "attackers" },
{ 0x0000, "attackerstance" },
{ 0x0000, "attackertable" },
{ 0x0000, "attackheliaiburstsize" },
{ 0x0000, "attackheliexcluders" },
{ 0x0000, "attackhelifov" },
{ 0x0000, "attackheligraceperiod" },
{ 0x0000, "attackhelikillsai" },
{ 0x0000, "attackhelimemory" },
{ 0x0000, "attackhelimovetime" },
{ 0x0000, "attackheliplayerbreak" },
{ 0x0000, "attackhelirange" },
{ 0x0000, "attackhelitargetreaquire" },
{ 0x0000, "attackhelitimeout" },
{ 0x0000, "attacking_player" },
{ 0x0000, "attackmiss" },
{ 0x0000, "attackmisstracktargetthread" },
{ 0x0000, "attacknode" },
{ 0x0000, "attacknothingtodo" },
{ 0x0000, "attackoffset" },
{ 0x0000, "attackradius" },
{ 0x0000, "attackradiussq" },
{ 0x0000, "attackstate" },
{ 0x0000, "attacksuppressableenemy" },
{ 0x0000, "attackteleportthread" },
{ 0x0000, "attackvisibleenemy" },
{ 0x0000, "attackzheight" },
{ 0x0000, "attackzheightdown" },
{ 0x0000, "attempt_execute" },
{ 0x0000, "attempt_mark_enemy" },
{ 0x0000, "attract_range" },
{ 0x0000, "attract_strength" },
{ 0x0000, "attractor" },
{ 0x0000, "attractor2" },
{ 0x0000, "attractornumber" },
{ 0x0000, "aud" },
{ 0x0000, "aud_2b_missile_final" },
{ 0x0000, "aud_2b_missile1" },
{ 0x0000, "aud_2b_missile2" },
{ 0x0000, "aud_2b_missile3" },
{ 0x0000, "aud_ac_units" },
{ 0x0000, "aud_add_progress_map" },
{ 0x0000, "aud_alarm_submix" },
{ 0x0000, "aud_ally_card_accept" },
{ 0x0000, "aud_ally_card_error" },
{ 0x0000, "aud_ally_card_swipe" },
{ 0x0000, "aud_ambient_animations" },
{ 0x0000, "aud_ambient_helicopter" },
{ 0x0000, "aud_approaching_poolhouse" },
{ 0x0000, "aud_ascent_final_warbird" },
{ 0x0000, "aud_atlas_suv_explo" },
{ 0x0000, "aud_autopsy_entrance" },
{ 0x0000, "aud_autopsy_entrance_vo" },
{ 0x0000, "aud_autopsy_knife_pry_door" },
{ 0x0000, "aud_avs_enemy_warbird" },
{ 0x0000, "aud_avs_enemy_warbird_2" },
{ 0x0000, "aud_avs_enemy_warbird_grapple" },
{ 0x0000, "aud_avs_intro_allies_1" },
{ 0x0000, "aud_avs_intro_allies_2" },
{ 0x0000, "aud_background_chatter" },
{ 0x0000, "aud_background_chatter_gate" },
{ 0x0000, "aud_balcony_aircraft_wait" },
{ 0x0000, "aud_ball_fountain" },
{ 0x0000, "aud_bet_exo_climb_gear_lt" },
{ 0x0000, "aud_bet_exo_climb_gear_rt" },
{ 0x0000, "aud_bet_exo_climb_hit_lt" },
{ 0x0000, "aud_bet_exo_climb_hit_rt" },
{ 0x0000, "aud_bet_exo_climb_settle_lt" },
{ 0x0000, "aud_bet_exo_climb_settle_rt" },
{ 0x0000, "aud_bet_exo_climb_windup_lt" },
{ 0x0000, "aud_bet_exo_climb_windup_rt" },
{ 0x0000, "aud_big_gate_open_stage_1" },
{ 0x0000, "aud_big_gate_open_stage_2" },
{ 0x0000, "aud_big_gate_pre_open" },
{ 0x0000, "aud_big_gate_stop_stage_1" },
{ 0x0000, "aud_big_gate_stop_stage_2" },
{ 0x0000, "aud_briefing" },
{ 0x0000, "aud_building_drop" },
{ 0x0000, "aud_building_pre_drop" },
{ 0x0000, "aud_burke_bus1_land" },
{ 0x0000, "aud_burke_hill_slide_stump" },
{ 0x0000, "aud_burke_intro_anim" },
{ 0x0000, "aud_burke_ledge_jump" },
{ 0x0000, "aud_burke_nearing_cliff" },
{ 0x0000, "aud_burke_open_door" },
{ 0x0000, "aud_burke_river_over_log" },
{ 0x0000, "aud_burke_riverbank_footstep_left" },
{ 0x0000, "aud_burke_riverbank_footstep_right" },
{ 0x0000, "aud_burke_riverbank_slide" },
{ 0x0000, "aud_burke_step_over_log" },
{ 0x0000, "aud_burke_stumble_knee" },
{ 0x0000, "aud_burke_stumble_run" },
{ 0x0000, "aud_burke_takedown" },
{ 0x0000, "aud_burke_tree_cover_01" },
{ 0x0000, "aud_burke_wall_climb" },
{ 0x0000, "aud_burke_water_deep_step" },
{ 0x0000, "aud_burke_water_enter" },
{ 0x0000, "aud_burke_water_exit" },
{ 0x0000, "aud_burke_water_fall_forward" },
{ 0x0000, "aud_burke_water_footstep_left" },
{ 0x0000, "aud_burke_water_footstep_right" },
{ 0x0000, "aud_burke_water_jump" },
{ 0x0000, "aud_burke_water_shallow_step" },
{ 0x0000, "aud_burke_water_slip" },
{ 0x0000, "aud_cap_45_onearm_toss" },
{ 0x0000, "aud_cap_escape_to_heli_truck_1" },
{ 0x0000, "aud_cap_escape_to_heli_truck_2" },
{ 0x0000, "aud_cap_heli_sfx_01" },
{ 0x0000, "aud_cap_heli_sfx_02" },
{ 0x0000, "aud_cap_heli_sfx_03" },
{ 0x0000, "aud_cap_heli_sfx_04" },
{ 0x0000, "aud_cap_heli_sfx_05" },
{ 0x0000, "aud_cap_heli_sfx_06" },
{ 0x0000, "aud_cap_interrogation_transition_vo" },
{ 0x0000, "aud_cap_s2_trolley_sfx_01" },
{ 0x0000, "aud_cap_s2_trolley_sfx_02" },
{ 0x0000, "aud_cap_s2_trolley_sfx_03" },
{ 0x0000, "aud_cap_s2_trolley_sfx_03_crk" },
{ 0x0000, "aud_cap_s2_trolley_sfx_04" },
{ 0x0000, "aud_cap_s2_trolley_sfx_05" },
{ 0x0000, "aud_cap_s2_trolley_sfx_06" },
{ 0x0000, "aud_cap_s2_trolley_sfx_07" },
{ 0x0000, "aud_cap_s2_trolley_sfx_08" },
{ 0x0000, "aud_cap_s2_trolley_sfx_09" },
{ 0x0000, "aud_cap_s2_trolley_sfx_10" },
{ 0x0000, "aud_cap_sml_onearm_toss" },
{ 0x0000, "aud_captured_foley_override_handler" },
{ 0x0000, "aud_captured_setup_anims" },
{ 0x0000, "aud_cave_ambience" },
{ 0x0000, "aud_cave_cascade" },
{ 0x0000, "aud_check_sound_done" },
{ 0x0000, "aud_chopper_sniper_bullet" },
{ 0x0000, "aud_chopper_sniper_whizby" },
{ 0x0000, "aud_clamp" },
{ 0x0000, "aud_clear_sticky_threat" },
{ 0x0000, "aud_close_sounds" },
{ 0x0000, "aud_combat_clearing_1_warbird" },
{ 0x0000, "aud_combat_clearing_2_littlebird_1" },
{ 0x0000, "aud_combat_clearing_2_littlebird_2" },
{ 0x0000, "aud_combat_clearing_3_littlebird_1" },
{ 0x0000, "aud_combat_clearing_3_littlebird_2" },
{ 0x0000, "aud_conduit_smash" },
{ 0x0000, "aud_copy_vector" },
{ 0x0000, "aud_cormack_approach" },
{ 0x0000, "aud_cormack_final_monitor_smash" },
{ 0x0000, "aud_cormack_final_smash_promo" },
{ 0x0000, "aud_cormack_grapple_kill" },
{ 0x0000, "aud_cormack_monitor_smash_promo" },
{ 0x0000, "aud_cormack_rappel_cable" },
{ 0x0000, "aud_courtyard_hangar_door_close" },
{ 0x0000, "aud_courtyard_hangar_door_hack" },
{ 0x0000, "aud_courtyard_hangar_door_hack_idle" },
{ 0x0000, "aud_courtyard_hangar_door_open" },
{ 0x0000, "aud_crane_mount_crouch_jump" },
{ 0x0000, "aud_crane_mount_lt_hand_hit" },
{ 0x0000, "aud_crane_mount_lt_hand_rest" },
{ 0x0000, "aud_crane_mount_rt_hand_hit" },
{ 0x0000, "aud_crane_mount_rt_hand_rest" },
{ 0x0000, "aud_crash_wakeup_sfx" },
{ 0x0000, "aud_create_drive_envs" },
{ 0x0000, "aud_create_entity" },
{ 0x0000, "aud_create_linked_entity" },
{ 0x0000, "aud_ctyard_vrap01" },
{ 0x0000, "aud_ctyard_vrap02" },
{ 0x0000, "aud_ctyard_vrap04" },
{ 0x0000, "aud_ctyard_vrap05" },
{ 0x0000, "aud_delete_on_sounddone" },
{ 0x0000, "aud_destroy_deployed_pod" },
{ 0x0000, "aud_det_foley_override_handler" },
{ 0x0000, "aud_detach_from_vtol" },
{ 0x0000, "aud_disable_deathsdoor_audio" },
{ 0x0000, "aud_dna_bomb_01" },
{ 0x0000, "aud_dna_bomb_02" },
{ 0x0000, "aud_door" },
{ 0x0000, "aud_door_takedown_mix_handler" },
{ 0x0000, "aud_door_takedown_scream" },
{ 0x0000, "aud_drone_attack" },
{ 0x0000, "aud_drone_investigating" },
{ 0x0000, "aud_drone_start_jets" },
{ 0x0000, "aud_drone_view_intro_start" },
{ 0x0000, "aud_drone_view_intro_target" },
{ 0x0000, "aud_drop_pod_fire" },
{ 0x0000, "aud_drop_pod_land_fail" },
{ 0x0000, "aud_drop_pod_land_success" },
{ 0x0000, "aud_drop_pod_trophy_kill" },
{ 0x0000, "aud_duck" },
{ 0x0000, "aud_dyanmic_event" },
{ 0x0000, "aud_dynamic_event_startup" },
{ 0x0000, "aud_enable_deathsdoor_audio" },
{ 0x0000, "aud_engine_disable" },
{ 0x0000, "aud_engine_throttle_amount" },
{ 0x0000, "aud_engine_wait" },
{ 0x0000, "aud_enter_vtol" },
{ 0x0000, "aud_escape_doctor_bodybag" },
{ 0x0000, "aud_escape_give_gun_exo" },
{ 0x0000, "aud_escape_guard_takedown_door" },
{ 0x0000, "aud_escape_keycard" },
{ 0x0000, "aud_estate_grounds_ambience" },
{ 0x0000, "aud_estate_grounds_emitters" },
{ 0x0000, "aud_estate_living_ambience" },
{ 0x0000, "aud_estate_security_ambience" },
{ 0x0000, "aud_exfil_door_1" },
{ 0x0000, "aud_exfil_door_2a" },
{ 0x0000, "aud_exfil_door_2b" },
{ 0x0000, "aud_exfil_vtol_ascend" },
{ 0x0000, "aud_exfil_vtol_grapple" },
{ 0x0000, "aud_exfil_vtol_start" },
{ 0x0000, "aud_exfil_vtol_wind" },
{ 0x0000, "aud_exit_vtol" },
{ 0x0000, "aud_exo_climb_burke" },
{ 0x0000, "aud_exo_climb_flank_land" },
{ 0x0000, "aud_exo_climb_flank_over" },
{ 0x0000, "aud_exo_climb_gear_lt" },
{ 0x0000, "aud_exo_climb_gear_rt" },
{ 0x0000, "aud_exo_climb_gideon_land" },
{ 0x0000, "aud_exo_climb_hit_lt" },
{ 0x0000, "aud_exo_climb_hit_rt" },
{ 0x0000, "aud_exo_climb_mount_jump" },
{ 0x0000, "aud_exo_climb_mount_land" },
{ 0x0000, "aud_exo_climb_rest_lt" },
{ 0x0000, "aud_exo_climb_rest_rt" },
{ 0x0000, "aud_exo_climb_slide_push" },
{ 0x0000, "aud_exo_climb_slide_start" },
{ 0x0000, "aud_exo_climb_slide_stop" },
{ 0x0000, "aud_exo_climb_windup_lt" },
{ 0x0000, "aud_exo_climb_windup_rt" },
{ 0x0000, "aud_facility_breach_start" },
{ 0x0000, "aud_fade_in" },
{ 0x0000, "aud_fade_in_music" },
{ 0x0000, "aud_fade_loop_out_and_delete" },
{ 0x0000, "aud_fade_loop_out_and_delete_temp" },
{ 0x0000, "aud_fade_out" },
{ 0x0000, "aud_fade_out_and_delete" },
{ 0x0000, "aud_fadeup_intro_loop" },
{ 0x0000, "aud_fall_scream" },
{ 0x0000, "aud_falls_climbing" },
{ 0x0000, "aud_fin_rocket_damage_vfx" },
{ 0x0000, "aud_find_exploder" },
{ 0x0000, "aud_flag_handler" },
{ 0x0000, "aud_foam_room_emitters" },
{ 0x0000, "aud_foliage_insects" },
{ 0x0000, "aud_foliage_mix" },
{ 0x0000, "aud_foliage_movement" },
{ 0x0000, "aud_forest_ambience" },
{ 0x0000, "aud_forest_ambient_loops" },
{ 0x0000, "aud_fountains" },
{ 0x0000, "aud_garage_hyd_wrench" },
{ 0x0000, "aud_garage_lift" },
{ 0x0000, "aud_gas_sfx" },
{ 0x0000, "aud_get_ambi_submix" },
{ 0x0000, "aud_get_envelope_domain" },
{ 0x0000, "aud_get_music_submix" },
{ 0x0000, "aud_get_optional_param" },
{ 0x0000, "aud_get_player_locamote_state" },
{ 0x0000, "aud_get_progress_map" },
{ 0x0000, "aud_get_sticky_threat" },
{ 0x0000, "aud_get_threat_level" },
{ 0x0000, "aud_gideon_autopsy_halls_start" },
{ 0x0000, "aud_gideon_heli_runout_kick" },
{ 0x0000, "aud_gideon_heli_runout_start" },
{ 0x0000, "aud_gideon_test_chamber_ascend_start" },
{ 0x0000, "aud_gideon_test_chamber_bodybag_1" },
{ 0x0000, "aud_gideon_test_chamber_bodybag_2" },
{ 0x0000, "aud_gideon_test_chamber_climb_stairs_1" },
{ 0x0000, "aud_gideon_test_chamber_climb_stairs_2" },
{ 0x0000, "aud_gideon_test_chamber_descend_stairs" },
{ 0x0000, "aud_gideon_test_chamber_descend_stairs_"... },
{ 0x0000, "aud_gideon_test_chamber_door_kick" },
{ 0x0000, "aud_gideon_test_chamber_security" },
{ 0x0000, "aud_gideon_test_chamber_stair_door" },
{ 0x0000, "aud_grapple_from_foliage" },
{ 0x0000, "aud_grapple_infil" },
{ 0x0000, "aud_grapple_kill_foliage" },
{ 0x0000, "aud_grapple_land_debris" },
{ 0x0000, "aud_grapple_launch" },
{ 0x0000, "aud_grapple_monitor" },
{ 0x0000, "aud_grates" },
{ 0x0000, "aud_ground_veh_deathwatch" },
{ 0x0000, "aud_ground_veh_loops" },
{ 0x0000, "aud_ground_veh_speed_mapping" },
{ 0x0000, "aud_guard_station_ambience" },
{ 0x0000, "aud_guard_station_main_door" },
{ 0x0000, "aud_guardhouse_foley_cormack" },
{ 0x0000, "aud_gun_throw_logic" },
{ 0x0000, "aud_handle_alarms" },
{ 0x0000, "aud_handle_buoy_sfx" },
{ 0x0000, "aud_handle_clearing_dambs" },
{ 0x0000, "aud_handle_earthquake" },
{ 0x0000, "aud_handle_gangam_jets" },
{ 0x0000, "aud_handle_incoming" },
{ 0x0000, "aud_handle_map_setups" },
{ 0x0000, "aud_handle_river_progress_flags" },
{ 0x0000, "aud_handle_river_sfx" },
{ 0x0000, "aud_handle_river_shallow_flag" },
{ 0x0000, "aud_handle_so_missile" },
{ 0x0000, "aud_handle_vista_jets" },
{ 0x0000, "aud_handle_warning_vo" },
{ 0x0000, "aud_handle_wave_incoming" },
{ 0x0000, "aud_handle_waves_crash" },
{ 0x0000, "aud_hangar_ambience" },
{ 0x0000, "aud_hangar_car_door_exit" },
{ 0x0000, "aud_hangar_door_exit" },
{ 0x0000, "aud_hangar_door_open" },
{ 0x0000, "aud_hangar_walla" },
{ 0x0000, "aud_hatch_gideon" },
{ 0x0000, "aud_hatch_plr" },
{ 0x0000, "aud_hazmat_guy_foley" },
{ 0x0000, "aud_hazmat_guy_pushes_alarm" },
{ 0x0000, "aud_heli_battle_flyover" },
{ 0x0000, "aud_heli_crash_pos" },
{ 0x0000, "aud_heli_escape_idle_sfx" },
{ 0x0000, "aud_heli_manticore_flyover" },
{ 0x0000, "aud_helicopter_deathwatch" },
{ 0x0000, "aud_helo_spotlight_spawn" },
{ 0x0000, "aud_hostage_truck_hits_water" },
{ 0x0000, "aud_hostage_truck_over_curb" },
{ 0x0000, "aud_hostage_truck_over_edge" },
{ 0x0000, "aud_hostage_truck_tbone" },
{ 0x0000, "aud_human_activity_streams" },
{ 0x0000, "aud_ilana_carmack_escape_controlroom" },
{ 0x0000, "aud_ilana_carmack_escape_controlroom_at"... },
{ 0x0000, "aud_ilana_carmack_escape_hallway" },
{ 0x0000, "aud_ilana_carmack_escape_hallway_end" },
{ 0x0000, "aud_ilana_carmack_escape_takedown" },
{ 0x0000, "aud_ilana_carmack_rescue_01" },
{ 0x0000, "aud_impact_monitor" },
{ 0x0000, "aud_impact_system_diveboat" },
{ 0x0000, "aud_impact_system_hovertank" },
{ 0x0000, "aud_impact_system_jetbike" },
{ 0x0000, "aud_in_zone" },
{ 0x0000, "aud_incin_after" },
{ 0x0000, "aud_incin_after_loop1" },
{ 0x0000, "aud_incin_amb_kill" },
{ 0x0000, "aud_incin_blackout" },
{ 0x0000, "aud_incin_cart_done" },
{ 0x0000, "aud_incin_cart_push" },
{ 0x0000, "aud_incin_cart_push_stop" },
{ 0x0000, "aud_incin_cart_start" },
{ 0x0000, "aud_incin_flame_logic_first_burst" },
{ 0x0000, "aud_incin_flame_loop" },
{ 0x0000, "aud_incin_flame_loop_2" },
{ 0x0000, "aud_incin_pilot_light" },
{ 0x0000, "aud_incin_pilot_light1" },
{ 0x0000, "aud_incin_pilot_light2" },
{ 0x0000, "aud_incin_pilot_light3" },
{ 0x0000, "aud_incin_pilot_light4" },
{ 0x0000, "aud_incin_pilot_light5" },
{ 0x0000, "aud_incin_pipe_burst" },
{ 0x0000, "aud_incin_pipe_grab" },
{ 0x0000, "aud_init" },
{ 0x0000, "aud_insect_sound" },
{ 0x0000, "aud_intel" },
{ 0x0000, "aud_interrogation_music_pt1" },
{ 0x0000, "aud_interrogation_music_pt2" },
{ 0x0000, "aud_interrogation_scene" },
{ 0x0000, "aud_into_mech_missle" },
{ 0x0000, "aud_intro_caravan_mute" },
{ 0x0000, "aud_intro_caravan_passby" },
{ 0x0000, "aud_intro_caravan_unmute" },
{ 0x0000, "aud_intro_drone" },
{ 0x0000, "aud_intro_foley" },
{ 0x0000, "aud_intro_heli_flyover" },
{ 0x0000, "aud_intro_to_elev_walla" },
{ 0x0000, "aud_intro_truck_gate" },
{ 0x0000, "aud_intro_truck_passby_01" },
{ 0x0000, "aud_intro_truck_passby_02" },
{ 0x0000, "aud_intro_truck_stop" },
{ 0x0000, "aud_introblack_bullet" },
{ 0x0000, "aud_irons_reveal_bomb_shake" },
{ 0x0000, "aud_irons_reveal_bomb_shake_02" },
{ 0x0000, "aud_irons_reveal_star_trek_door" },
{ 0x0000, "aud_irons_says_hello" },
{ 0x0000, "aud_ironsstealth" },
{ 0x0000, "aud_is_even" },
{ 0x0000, "aud_is_specops" },
{ 0x0000, "aud_jeep_death_listener" },
{ 0x0000, "aud_knox_keypad" },
{ 0x0000, "aud_knox_thermite" },
{ 0x0000, "aud_knox_thermite_promo" },
{ 0x0000, "aud_lab_ambient_emitters" },
{ 0x0000, "aud_lab_foley_override_handler" },
{ 0x0000, "aud_lab_intro_screen" },
{ 0x0000, "aud_lab_phone_wait" },
{ 0x0000, "aud_lab_tech_chair_startle_1" },
{ 0x0000, "aud_lab_tech_chair_startle_2" },
{ 0x0000, "aud_lab_tech_desk_bump" },
{ 0x0000, "aud_laser_energy_beam_start" },
{ 0x0000, "aud_laser_pre_move_down" },
{ 0x0000, "aud_last_time" },
{ 0x0000, "aud_level_fadein" },
{ 0x0000, "aud_limp_exo" },
{ 0x0000, "aud_limp_off" },
{ 0x0000, "aud_limp_on" },
{ 0x0000, "aud_little_bird_hit" },
{ 0x0000, "aud_lockdown_alarm" },
{ 0x0000, "aud_lowstealth" },
{ 0x0000, "aud_manticore_crane" },
{ 0x0000, "aud_max" },
{ 0x0000, "aud_mech_crush_guy" },
{ 0x0000, "aud_mech_grapple_pitch_up" },
{ 0x0000, "aud_mech_idle_sfx" },
{ 0x0000, "aud_mech_jump" },
{ 0x0000, "aud_mech_missile_fire" },
{ 0x0000, "aud_mech_obj_move" },
{ 0x0000, "aud_mech_obj_move_end" },
{ 0x0000, "aud_mech_obj_move_wait" },
{ 0x0000, "aud_mech_panic_walla_watcher" },
{ 0x0000, "aud_mech_scanner" },
{ 0x0000, "aud_mech_trucks_enter" },
{ 0x0000, "aud_mech1_bg_truck" },
{ 0x0000, "aud_mechkill_catchdude" },
{ 0x0000, "aud_median_impact" },
{ 0x0000, "aud_meet_atlast_roof_explode" },
{ 0x0000, "aud_microwave_grenade" },
{ 0x0000, "aud_microwave_grenade_sparks_dude" },
{ 0x0000, "aud_microwave_grenade_sparks_env" },
{ 0x0000, "aud_min" },
{ 0x0000, "aud_monitor_irons" },
{ 0x0000, "aud_morgue_bodybag_doors" },
{ 0x0000, "aud_morgue_bodybag_line_emt" },
{ 0x0000, "aud_morgue_computer_door_entry_sfx" },
{ 0x0000, "aud_mus_boost" },
{ 0x0000, "aud_music_state" },
{ 0x0000, "aud_num_alive_enemies" },
{ 0x0000, "aud_observation_guard_radio" },
{ 0x0000, "aud_old_music_state" },
{ 0x0000, "aud_onearm_weapon_swap" },
{ 0x0000, "aud_overrides" },
{ 0x0000, "aud_pa_announc_01" },
{ 0x0000, "aud_pa_announc_02" },
{ 0x0000, "aud_pa_announc_03" },
{ 0x0000, "aud_pa_announc_04" },
{ 0x0000, "aud_painting_fall" },
{ 0x0000, "aud_panic_walla" },
{ 0x0000, "aud_patching_in_foley" },
{ 0x0000, "aud_patrol_helo_debris_sfx" },
{ 0x0000, "aud_penthouse_front_door" },
{ 0x0000, "aud_percent_chance" },
{ 0x0000, "aud_piston_ent" },
{ 0x0000, "aud_pitbull_crash_concussion" },
{ 0x0000, "aud_play" },
{ 0x0000, "aud_play_announcer_warning" },
{ 0x0000, "aud_play_distance_attenuated_2d" },
{ 0x0000, "aud_play_dust" },
{ 0x0000, "aud_play_dynamic_explosion" },
{ 0x0000, "aud_play_horror_ambience" },
{ 0x0000, "aud_play_laser_move_down" },
{ 0x0000, "aud_play_laser_move_up" },
{ 0x0000, "aud_play_line_emitter" },
{ 0x0000, "aud_play_pcap_vo" },
{ 0x0000, "aud_play_pod_impact" },
{ 0x0000, "aud_play_point_source_loop" },
{ 0x0000, "aud_play_rocket_travel_loops" },
{ 0x0000, "aud_play_tank_explosion" },
{ 0x0000, "aud_play_trophy_fire" },
{ 0x0000, "aud_player_bus_exo_jump" },
{ 0x0000, "aud_player_bus_exo_land" },
{ 0x0000, "aud_player_bus_jump_handplant" },
{ 0x0000, "aud_player_bus_land" },
{ 0x0000, "aud_player_bus1_exo_land" },
{ 0x0000, "aud_player_bus1_land" },
{ 0x0000, "aud_player_climb_foley" },
{ 0x0000, "aud_player_climb_to_ledge" },
{ 0x0000, "aud_player_computer" },
{ 0x0000, "aud_player_computer_gl_timing_fix" },
{ 0x0000, "aud_player_computer_promo" },
{ 0x0000, "aud_player_exo_punch_driver" },
{ 0x0000, "aud_player_exo_punch_metal_plate" },
{ 0x0000, "aud_player_gets_in_tank" },
{ 0x0000, "aud_player_grab_mirror" },
{ 0x0000, "aud_player_hill_slide" },
{ 0x0000, "aud_player_jump_back_to_bus" },
{ 0x0000, "aud_player_jump_to_truck" },
{ 0x0000, "aud_player_land_back_on_bus" },
{ 0x0000, "aud_player_land_on_truck" },
{ 0x0000, "aud_player_rappel_complete" },
{ 0x0000, "aud_player_throw_driver" },
{ 0x0000, "aud_player_throw_metal_plate" },
{ 0x0000, "aud_player_wall_climb_01" },
{ 0x0000, "aud_player_wall_climb_02" },
{ 0x0000, "aud_player_wall_climb_03" },
{ 0x0000, "aud_player_wall_climb_04" },
{ 0x0000, "aud_player_wall_climb_05" },
{ 0x0000, "aud_playermech_end" },
{ 0x0000, "aud_playermech_foley_override_handler" },
{ 0x0000, "aud_playermech_start" },
{ 0x0000, "aud_plr_hit" },
{ 0x0000, "aud_plr_hit_vo_line" },
{ 0x0000, "aud_plr_hit_vo_look" },
{ 0x0000, "aud_plr_hit_vo_move_back" },
{ 0x0000, "aud_plr_hit_vo_move_forward" },
{ 0x0000, "aud_plr_inside_mech" },
{ 0x0000, "aud_pod_arm_reach" },
{ 0x0000, "aud_pod_hits_ground" },
{ 0x0000, "aud_pod_hits_ground_corrected" },
{ 0x0000, "aud_pod_scene_begin" },
{ 0x0000, "aud_pod_turbulence_01" },
{ 0x0000, "aud_pod_turbulence_02" },
{ 0x0000, "aud_poolhouse_ambience" },
{ 0x0000, "aud_post_courtyard_emitters" },
{ 0x0000, "aud_print" },
{ 0x0000, "aud_print_3d_on_ent" },
{ 0x0000, "aud_print_debug" },
{ 0x0000, "aud_print_error" },
{ 0x0000, "aud_print_synch" },
{ 0x0000, "aud_print_warning" },
{ 0x0000, "aud_print_zone" },
{ 0x0000, "aud_print_zone_small" },
{ 0x0000, "aud_rappel_player_hookup" },
{ 0x0000, "aud_rappel_player_movement_start" },
{ 0x0000, "aud_rappel_player_movement_stop" },
{ 0x0000, "aud_reached_penthouse" },
{ 0x0000, "aud_ready_hooks" },
{ 0x0000, "aud_recon_foley" },
{ 0x0000, "aud_red_light" },
{ 0x0000, "aud_reinforcements_door1" },
{ 0x0000, "aud_reinforcements_door2" },
{ 0x0000, "aud_rescue_drone" },
{ 0x0000, "aud_rescue_sfx_a" },
{ 0x0000, "aud_rescue_sfx_b" },
{ 0x0000, "aud_rescue_sfx_c" },
{ 0x0000, "aud_rescue_sfx_d" },
{ 0x0000, "aud_rescue_sfx_e" },
{ 0x0000, "aud_rescue_sfx_f" },
{ 0x0000, "aud_rescue_sfx_g" },
{ 0x0000, "aud_rocket_launch_start" },
{ 0x0000, "aud_rocket_stage_01_start" },
{ 0x0000, "aud_rooftop_warbird_departing" },
{ 0x0000, "aud_rooftop_wind_volume" },
{ 0x0000, "aud_rooftops_ambience" },
{ 0x0000, "aud_rotate_vector_yaw" },
{ 0x0000, "aud_run_tank_system" },
{ 0x0000, "aud_s1_elevator_boss_foley" },
{ 0x0000, "aud_s1_elevator_cormack_foley" },
{ 0x0000, "aud_s1_elevator_guard_foley" },
{ 0x0000, "aud_s1_elevator_kick_1" },
{ 0x0000, "aud_s1_elevator_kick_2" },
{ 0x0000, "aud_s2walk_alarm_tone_lp" },
{ 0x0000, "aud_s2walk_cell_prisoners" },
{ 0x0000, "aud_s2walk_cells_foley_mix" },
{ 0x0000, "aud_s2walk_clear_foley_mix" },
{ 0x0000, "aud_s2walk_cormack_punched" },
{ 0x0000, "aud_s2walk_door_close" },
{ 0x0000, "aud_s2walk_door_open" },
{ 0x0000, "aud_s2walk_emitters" },
{ 0x0000, "aud_s2walk_execution_fire" },
{ 0x0000, "aud_s2walk_execution_kneeling_prisoners" },
{ 0x0000, "aud_s2walk_flyby_1" },
{ 0x0000, "aud_s2walk_guard_3_foley_01" },
{ 0x0000, "aud_s2walk_guard_3_foley_02" },
{ 0x0000, "aud_s2walk_guard_hip_radio" },
{ 0x0000, "aud_s2walk_guard_radios" },
{ 0x0000, "aud_s2walk_ilona_push" },
{ 0x0000, "aud_s2walk_loudspeaker2_line1" },
{ 0x0000, "aud_s2walk_loudspeaker2_line2" },
{ 0x0000, "aud_s2walk_prisoner_2_beating" },
{ 0x0000, "aud_s2walk_start_cormack_foley" },
{ 0x0000, "aud_s2walk_start_gideon_bodyfall" },
{ 0x0000, "aud_s2walk_start_gideon_foley" },
{ 0x0000, "aud_s2walk_start_guard_1_foley" },
{ 0x0000, "aud_s2walk_start_guard_1_grabpush" },
{ 0x0000, "aud_s2walk_start_guard_2_foley" },
{ 0x0000, "aud_s2walk_start_guard_2_grab" },
{ 0x0000, "aud_s2walk_start_guard_2_grabpush" },
{ 0x0000, "aud_s2walk_start_guard_2_push" },
{ 0x0000, "aud_s2walk_start_guard_3_foley" },
{ 0x0000, "aud_s2walk_start_guard_3_walkup_foley" },
{ 0x0000, "aud_s2walk_start_ilona_foley" },
{ 0x0000, "aud_s2walk_start_player_foley" },
{ 0x0000, "aud_s2walk_temp_guard_vo" },
{ 0x0000, "aud_s2walk_trigger_start" },
{ 0x0000, "aud_s2walk_yard_prisoners_whimpering" },
{ 0x0000, "aud_s3escape_doctor_radio" },
{ 0x0000, "aud_scale_envelope" },
{ 0x0000, "aud_scale_vector" },
{ 0x0000, "aud_scale_vector_2d" },
{ 0x0000, "aud_scanner_door_open" },
{ 0x0000, "aud_security_alarm" },
{ 0x0000, "aud_security_center_drones_on" },
{ 0x0000, "aud_security_countdown" },
{ 0x0000, "aud_security_hatch_exit" },
{ 0x0000, "aud_security_main_screen" },
{ 0x0000, "aud_security_plant_emp" },
{ 0x0000, "aud_security_prints" },
{ 0x0000, "aud_security_reboot" },
{ 0x0000, "aud_security_vent" },
{ 0x0000, "aud_security_welcome" },
{ 0x0000, "aud_separation_door" },
{ 0x0000, "aud_separation_elevator" },
{ 0x0000, "aud_separation_logic" },
{ 0x0000, "aud_server_room_door_crack" },
{ 0x0000, "aud_server_room_door_enter" },
{ 0x0000, "aud_server_room_door_kick" },
{ 0x0000, "aud_server_room_thermite" },
{ 0x0000, "aud_server_thermite_burn_loop" },
{ 0x0000, "aud_server_thermite_burn_start" },
{ 0x0000, "aud_server_thermite_out" },
{ 0x0000, "aud_set_ambi_submix" },
{ 0x0000, "aud_set_level_fade_time" },
{ 0x0000, "aud_set_mission_failed_music" },
{ 0x0000, "aud_set_music_submix" },
{ 0x0000, "aud_set_point_source_loop_volume" },
{ 0x0000, "aud_set_spec_ops" },
{ 0x0000, "aud_set_sticky_threat" },
{ 0x0000, "aud_set_timescale" },
{ 0x0000, "aud_setup_drop_pod_loop" },
{ 0x0000, "aud_shack_explode" },
{ 0x0000, "aud_shack_explode_whizby" },
{ 0x0000, "aud_slomo_wait" },
{ 0x0000, "aud_smooth" },
{ 0x0000, "aud_sonar_vision_off" },
{ 0x0000, "aud_sonar_vision_on" },
{ 0x0000, "aud_spark_1" },
{ 0x0000, "aud_spark_2" },
{ 0x0000, "aud_spark_3" },
{ 0x0000, "aud_spark_4" },
{ 0x0000, "aud_spark_5" },
{ 0x0000, "aud_sprinklers" },
{ 0x0000, "aud_start_dna_events" },
{ 0x0000, "aud_start_dna_events_cg" },
{ 0x0000, "aud_start_exfil_foley" },
{ 0x0000, "aud_start_nyse_fire" },
{ 0x0000, "aud_start_slow_mo_gunshot_callback" },
{ 0x0000, "aud_stealth_broken_timer" },
{ 0x0000, "aud_stealth_melee" },
{ 0x0000, "aud_stop_and_delete_ent" },
{ 0x0000, "aud_stop_cormack_foley" },
{ 0x0000, "aud_stop_headspace_ambience" },
{ 0x0000, "aud_stop_horror_ambience" },
{ 0x0000, "aud_stop_line_emitter" },
{ 0x0000, "aud_stop_mech_panic_walla_watcher" },
{ 0x0000, "aud_stop_mute_device_for_vo" },
{ 0x0000, "aud_stop_point_source_loop" },
{ 0x0000, "aud_stop_slow_mo_gunshot_callback" },
{ 0x0000, "aud_stop_sound_logic" },
{ 0x0000, "aud_stop_training_mute_device" },
{ 0x0000, "aud_stop_vrap_mute_device" },
{ 0x0000, "aud_table_pulldown" },
{ 0x0000, "aud_tank_death_listener" },
{ 0x0000, "aud_tank_field_littlebird" },
{ 0x0000, "aud_tank_field_warbird" },
{ 0x0000, "aud_tank_fire_watch" },
{ 0x0000, "aud_tank_road_littlebird_1" },
{ 0x0000, "aud_tank_road_littlebird_2" },
{ 0x0000, "aud_tank_section_vehicles_handler" },
{ 0x0000, "aud_tank_section_vehicles_spawned" },
{ 0x0000, "aud_tanker_crash" },
{ 0x0000, "aud_tanker_fall_down" },
{ 0x0000, "aud_tennis_court_wakeup" },
{ 0x0000, "aud_tire_splash" },
{ 0x0000, "aud_titan_siege_mode_adj_left_side" },
{ 0x0000, "aud_titan_siege_mode_adj_left_side_back" },
{ 0x0000, "aud_titan_siege_mode_adj_right_side" },
{ 0x0000, "aud_titan_siege_mode_adj_right_side_bac"... },
{ 0x0000, "aud_training_s2_potus_ziptie_release" },
{ 0x0000, "aud_transport_chopper" },
{ 0x0000, "aud_trolley_music" },
{ 0x0000, "aud_truck_dodge_slowmo_start" },
{ 0x0000, "aud_truck_dodge_slowmo_whoosh" },
{ 0x0000, "aud_truck_hits_divider" },
{ 0x0000, "aud_truck_hits_ground" },
{ 0x0000, "aud_truck_jump_slowmo" },
{ 0x0000, "aud_truck_punch_slowmo" },
{ 0x0000, "aud_truck1_engine_pullup" },
{ 0x0000, "aud_truck2_engine_drive" },
{ 0x0000, "aud_truck2_engine_idle" },
{ 0x0000, "aud_truck2_engine_pullup" },
{ 0x0000, "aud_trucks_arrive" },
{ 0x0000, "aud_turret_entry" },
{ 0x0000, "aud_turrets_activate" },
{ 0x0000, "aud_use_string_tables" },
{ 0x0000, "aud_var_nade_type" },
{ 0x0000, "aud_vector_magnitude_2d" },
{ 0x0000, "aud_vehicle_ride_data" },
{ 0x0000, "aud_vrap_mute_start" },
{ 0x0000, "aud_vtol_excellerate_end" },
{ 0x0000, "aud_vtol_excellerate_start" },
{ 0x0000, "aud_vtol_exterior_idle" },
{ 0x0000, "aud_vtol_land" },
{ 0x0000, "aud_vtol_passed" },
{ 0x0000, "aud_wait_delay" },
{ 0x0000, "aud_wait_for_mission_fail_music" },
{ 0x0000, "aud_wakeup_amb" },
{ 0x0000, "aud_wakeup_mech_cooldown_pings" },
{ 0x0000, "aud_wakeup_mix" },
{ 0x0000, "aud_warehouse_mech_lift" },
{ 0x0000, "aud_warehouse_mech_lift_alarm" },
{ 0x0000, "aud_warehouse_mech_lift_vo" },
{ 0x0000, "aud_warehouse_roof_machines" },
{ 0x0000, "aud_warehouse_roof_machines_line" },
{ 0x0000, "aud_warning_vo" },
{ 0x0000, "aud_watch_for_anim_end" },
{ 0x0000, "aud_water_footsteps_foley" },
{ 0x0000, "aud_water_footsteps_override" },
{ 0x0000, "aud_water_sound" },
{ 0x0000, "aud_waterfall_ambience" },
{ 0x0000, "aud_windmill_sniper_whizby" },
{ 0x0000, "aud_zap_logic_change" },
{ 0x0000, "aud_zap_scene" },
{ 0x0000, "audiblesightplaying" },
{ 0x0000, "audio" },
{ 0x0000, "audio_buzzer_struct" },
{ 0x0000, "audio_jet_counter" },
{ 0x0000, "audio_monitor_chopper01_death" },
{ 0x0000, "audio_monitor_chopper02_death" },
{ 0x0000, "audio_org" },
{ 0x0000, "audio_presets_music_cue_groups" },
{ 0x0000, "audio_presets_music_cues" },
{ 0x0000, "audio_presets_music_moods" },
{ 0x0000, "audio_presets_vehicle_maps" },
{ 0x0000, "audio_presets_vehicles" },
{ 0x0000, "audio_push_1_box_drop" },
{ 0x0000, "audio_push_1_box_pickup" },
{ 0x0000, "audio_push_1_box_push" },
{ 0x0000, "audio_push_1_crane_move_1" },
{ 0x0000, "audio_push_1_crane_move_2" },
{ 0x0000, "audio_push_1_crane_move_3" },
{ 0x0000, "audio_push_2_box_drop" },
{ 0x0000, "audio_push_2_box_pickup" },
{ 0x0000, "audio_push_2_box_push" },
{ 0x0000, "audio_push_2_crane_move_1" },
{ 0x0000, "audio_push_2_crane_move_2" },
{ 0x0000, "audio_push_2_crane_move_3" },
{ 0x0000, "audio_start_wrestling_exo_guy" },
{ 0x0000, "audio_start_wrestling_guy2" },
{ 0x0000, "audio_start_wrestling_guy3" },
{ 0x0000, "audio_start_wrestling_guy4" },
{ 0x0000, "audio_start_wrestling_guy5" },
{ 0x0000, "audio_stingers_school_bodies_room" },
{ 0x0000, "audio_stringtable_mapname" },
{ 0x0000, "audio_zones" },
{ 0x0000, "audx_attenuate" },
{ 0x0000, "audx_delete_on_sounddone_internal" },
{ 0x0000, "audx_do_dynamic_explosion_math" },
{ 0x0000, "audx_duck" },
{ 0x0000, "audx_fade_in_internal" },
{ 0x0000, "audx_fade_out_internal" },
{ 0x0000, "audx_play_distance_attenuated_2d_intern"... },
{ 0x0000, "audx_play_line_emitter_internal" },
{ 0x0000, "audx_print_3d_timer" },
{ 0x0000, "audx_set_spec_ops" },
{ 0x0000, "audx_slomo_wait" },
{ 0x0000, "auto_adjust_difficulty_player_movement_"... },
{ 0x0000, "auto_adjust_difficulty_player_positione"... },
{ 0x0000, "auto_adjust_difficulty_track_player_dea"... },
{ 0x0000, "auto_adjust_difficulty_track_player_sho"... },
{ 0x0000, "auto_adjust_enemy_death_detection" },
{ 0x0000, "auto_adjust_enemy_died" },
{ 0x0000, "auto_adjust_flags" },
{ 0x0000, "auto_adjust_new_zone" },
{ 0x0000, "auto_adjust_results" },
{ 0x0000, "auto_adust_zone_complete" },
{ 0x0000, "auto_combat_music" },
{ 0x0000, "auto_mg42_target" },
{ 0x0000, "auto_mgturretlink" },
{ 0x0000, "auto_occumulator_base" },
{ 0x0000, "auto_recloak" },
{ 0x0000, "autoadjust_playerspots" },
{ 0x0000, "autoassign" },
{ 0x0000, "autoclose" },
{ 0x0000, "autofocus_hipenable" },
{ 0x0000, "autofocus_hipenable_bike" },
{ 0x0000, "autofocus_loop" },
{ 0x0000, "autopsy_cleanup" },
{ 0x0000, "autopsy_create_fodder_techs" },
{ 0x0000, "autopsy_doctor_door_doctor" },
{ 0x0000, "autopsy_doctor_door_enemies" },
{ 0x0000, "autopsy_doctor_door_enemy_ammo" },
{ 0x0000, "autopsy_doctor_door_enemy_think" },
{ 0x0000, "autopsy_doctor_door_fail" },
{ 0x0000, "autopsy_doctor_door_gideon" },
{ 0x0000, "autopsy_doctor_door_no_hint" },
{ 0x0000, "autopsy_doctor_door_player" },
{ 0x0000, "autopsy_door_action" },
{ 0x0000, "autopsy_door_tech" },
{ 0x0000, "autopsy_first_frame_entry_doors" },
{ 0x0000, "autopsy_fodder_tech_animate" },
{ 0x0000, "autopsy_fodder_tech_think" },
{ 0x0000, "autopsy_guard" },
{ 0x0000, "autopsy_guard_player_hit" },
{ 0x0000, "autopsy_main_doctor" },
{ 0x0000, "autopsy_start" },
{ 0x0000, "autoresettime" },
{ 0x0000, "autosave_by_name" },
{ 0x0000, "autosave_by_name_silent" },
{ 0x0000, "autosave_by_name_thread" },
{ 0x0000, "autosave_check_override" },
{ 0x0000, "autosave_check_pitbull_moving" },
{ 0x0000, "autosave_check_pitbull_no_recent_accel" },
{ 0x0000, "autosave_check_pitbull_upright" },
{ 0x0000, "autosave_fly_check" },
{ 0x0000, "autosave_hostile_drone_check" },
{ 0x0000, "autosave_jetbike_check_too_slow" },
{ 0x0000, "autosave_jetbike_check_trailing" },
{ 0x0000, "autosave_now" },
{ 0x0000, "autosave_now_silent" },
{ 0x0000, "autosave_now_trigger" },
{ 0x0000, "autosave_or_timeout" },
{ 0x0000, "autosave_proximity_threat_func" },
{ 0x0000, "autosave_recon" },
{ 0x0000, "autosave_stealth" },
{ 0x0000, "autosave_stealth_meter_check" },
{ 0x0000, "autosave_stealth_silent" },
{ 0x0000, "autosave_stealth_spotted_check" },
{ 0x0000, "autosave_tactical" },
{ 0x0000, "autosave_tactical_grenade_check" },
{ 0x0000, "autosave_tactical_grenade_check_dieout" },
{ 0x0000, "autosave_tactical_player_nades" },
{ 0x0000, "autosave_tactical_proc" },
{ 0x0000, "autosave_tactical_setup" },
{ 0x0000, "autosave_threat_check_enabled" },
{ 0x0000, "autosave_timeout" },
{ 0x0000, "autosaveammocheck" },
{ 0x0000, "autosavecheck" },
{ 0x0000, "autosavecheck_not_picky" },
{ 0x0000, "autosaveconfcentercombatcheck" },
{ 0x0000, "autosaveconfcenterstealthcheck" },
{ 0x0000, "autosavehealthcheck" },
{ 0x0000, "autosavenamethink" },
{ 0x0000, "autosaveplayercheck" },
{ 0x0000, "autosaveprint" },
{ 0x0000, "autosaves_think" },
{ 0x0000, "autosavesniperdronestealth" },
{ 0x0000, "autosavethreatcheck" },
{ 0x0000, "autoshootanimrate" },
{ 0x0000, "autospot_is_close_to_player" },
{ 0x0000, "autospotadswatcher" },
{ 0x0000, "autospotdeathwatcher" },
{ 0x0000, "autotarget" },
{ 0x0000, "auxillary_hud" },
{ 0x0000, "available" },
{ 0x0000, "available_crash_paths" },
{ 0x0000, "availablepositions" },
{ 0x0000, "avalanche_environment" },
{ 0x0000, "avalanche_falling_death" },
{ 0x0000, "avatar" },
{ 0x0000, "avatar_after_spawn" },
{ 0x0000, "avatar_scheduled_for_removal" },
{ 0x0000, "avatar_spawnpoint" },
{ 0x0000, "avatarinfo" },
{ 0x0000, "avengedplayerevent" },
{ 0x0000, "avm_add_envelope" },
{ 0x0000, "avm_add_in_state_callback" },
{ 0x0000, "avm_add_init_state_callback" },
{ 0x0000, "avm_add_loops" },
{ 0x0000, "avm_add_oneshot" },
{ 0x0000, "avm_add_oneshots" },
{ 0x0000, "avm_add_param_map_env" },
{ 0x0000, "avm_add_state_transition" },
{ 0x0000, "avm_begin_behavior_data" },
{ 0x0000, "avm_begin_behavior_def" },
{ 0x0000, "avm_begin_loop_data" },
{ 0x0000, "avm_begin_loop_def" },
{ 0x0000, "avm_begin_oneshot_data" },
{ 0x0000, "avm_begin_oneshot_def" },
{ 0x0000, "avm_begin_param_map" },
{ 0x0000, "avm_begin_preset_def" },
{ 0x0000, "avm_begin_state_data" },
{ 0x0000, "avm_begin_state_def" },
{ 0x0000, "avm_begin_state_group" },
{ 0x0000, "avm_change_smoothing_rate" },
{ 0x0000, "avm_compute_alpha_from_rc" },
{ 0x0000, "avm_compute_doppler_pitch" },
{ 0x0000, "avm_compute_smoothing_rc_from_alpha" },
{ 0x0000, "avm_create_vehicle_proxy" },
{ 0x0000, "avm_end_behavior_data" },
{ 0x0000, "avm_end_behavior_def" },
{ 0x0000, "avm_end_loop_data" },
{ 0x0000, "avm_end_loop_def" },
{ 0x0000, "avm_end_oneshot_data" },
{ 0x0000, "avm_end_oneshot_def" },
{ 0x0000, "avm_end_param_map" },
{ 0x0000, "avm_end_preset_def" },
{ 0x0000, "avm_end_state_data" },
{ 0x0000, "avm_end_state_def" },
{ 0x0000, "avm_end_state_group" },
{ 0x0000, "avm_get_running_instance_count" },
{ 0x0000, "avm_get_update_rate" },
{ 0x0000, "avm_init" },
{ 0x0000, "avm_register_callback" },
{ 0x0000, "avm_set_instance_master_volume" },
{ 0x0000, "avm_set_loop_mute_state" },
{ 0x0000, "avmx_add_behavior_shortcut_param_maps" },
{ 0x0000, "avmx_add_instance" },
{ 0x0000, "avmx_add_oneshot_ducking_scalar" },
{ 0x0000, "avmx_add_preset" },
{ 0x0000, "avmx_are_all_defined" },
{ 0x0000, "avmx_continuously_update_snd_ent" },
{ 0x0000, "avmx_create_instance_struct" },
{ 0x0000, "avmx_create_param_io_struct" },
{ 0x0000, "avmx_create_preset" },
{ 0x0000, "avmx_fade_stop_and_delete_sound_obj" },
{ 0x0000, "avmx_generate_instance_name" },
{ 0x0000, "avmx_get" },
{ 0x0000, "avmx_get_behavior_instance_struct" },
{ 0x0000, "avmx_get_behavior_preset_struct" },
{ 0x0000, "avmx_get_behavior_restricted_oneshots" },
{ 0x0000, "avmx_get_callback" },
{ 0x0000, "avmx_get_current_instance_sound_item_in"... },
{ 0x0000, "avmx_get_envelope" },
{ 0x0000, "avmx_get_fadein_time" },
{ 0x0000, "avmx_get_fadeout_time" },
{ 0x0000, "avmx_get_instance" },
{ 0x0000, "avmx_get_instance_name" },
{ 0x0000, "avmx_get_instance_preset" },
{ 0x0000, "avmx_get_instance_preset_name" },
{ 0x0000, "avmx_get_instance_sound_item_output" },
{ 0x0000, "avmx_get_instance_sound_item_volume" },
{ 0x0000, "avmx_get_instance_state_struct" },
{ 0x0000, "avmx_get_master_volume" },
{ 0x0000, "avmx_get_oneshot_poly_mode" },
{ 0x0000, "avmx_get_oneshot_update_mode" },
{ 0x0000, "avmx_get_preset" },
{ 0x0000, "avmx_get_preset_name" },
{ 0x0000, "avmx_get_sound_alias" },
{ 0x0000, "avmx_get_sound_alias_count" },
{ 0x0000, "avmx_get_sound_instance" },
{ 0x0000, "avmx_get_state_preset_struct" },
{ 0x0000, "avmx_get_vehicle_entity" },
{ 0x0000, "avmx_handle_oneshot_ducking" },
{ 0x0000, "avmx_is_player_mode" },
{ 0x0000, "avmx_is_vehicle_proxy" },
{ 0x0000, "avmx_launch_state_machines" },
{ 0x0000, "avmx_map_input" },
{ 0x0000, "avmx_map_io" },
{ 0x0000, "avmx_monitor_death" },
{ 0x0000, "avmx_monitor_oneshot_done" },
{ 0x0000, "avmx_normalize_ranged_value" },
{ 0x0000, "avmx_preset_determine_param_map_env_own"... },
{ 0x0000, "avmx_preset_determine_param_map_owner" },
{ 0x0000, "avmx_preset_set_param_map_defaults" },
{ 0x0000, "avmx_remove_instance" },
{ 0x0000, "avmx_remove_oneshot_ducking_scalar" },
{ 0x0000, "avmx_set_behavior_oneshot_overrides" },
{ 0x0000, "avmx_set_instance_init_callback" },
{ 0x0000, "avmx_set_instance_master_volume" },
{ 0x0000, "avmx_set_loop_play_state" },
{ 0x0000, "avmx_set_loop_volume" },
{ 0x0000, "avmx_set_oneshot_ducking_scalar" },
{ 0x0000, "avmx_set_oneshot_update_mode" },
{ 0x0000, "avmx_set_preset_name" },
{ 0x0000, "avmx_start_instance" },
{ 0x0000, "avmx_start_loop" },
{ 0x0000, "avmx_start_oneshot_alias" },
{ 0x0000, "avmx_state_condition_function" },
{ 0x0000, "avmx_state_enter_action_function" },
{ 0x0000, "avmx_state_enter_action_init_data" },
{ 0x0000, "avmx_state_enter_action_play_loops" },
{ 0x0000, "avmx_state_enter_action_play_oneshots" },
{ 0x0000, "avmx_state_exit_action_function" },
{ 0x0000, "avmx_stop_instance" },
{ 0x0000, "avmx_stop_loop" },
{ 0x0000, "avmx_stop_snd_ent" },
{ 0x0000, "avmx_update_instance_loop_assets" },
{ 0x0000, "avmx_update_loop_ducking_scalar" },
{ 0x0000, "avmx_update_loops" },
{ 0x0000, "avmx_update_oneshot_duck_scalar" },
{ 0x0000, "avmx_update_sound_ent_output_param" },
{ 0x0000, "avmx_vehicle_getspeed" },
{ 0x0000, "avoid_players" },
{ 0x0000, "avoidairstrikelocations" },
{ 0x0000, "avoidcarepackages" },
{ 0x0000, "avoidcornervisibleenemies" },
{ 0x0000, "avoidenemiesbydistance" },
{ 0x0000, "avoidenemyspawn" },
{ 0x0000, "avoidfullvisibleenemies" },
{ 0x0000, "avoidgasclouds" },
{ 0x0000, "avoidgrenades" },
{ 0x0000, "avoidkillstreakonspawntimer" },
{ 0x0000, "avoidlastattackerlocation" },
{ 0x0000, "avoidlastdeathlocation" },
{ 0x0000, "avoidmines" },
{ 0x0000, "avoidrecentlyused" },
{ 0x0000, "avoidsamespawn" },
{ 0x0000, "avoidspawninhp" },
{ 0x0000, "avoidtelefrag" },
{ 0x0000, "award_intel" },
{ 0x0000, "award_player_exo_challenge_kill_for_sce"... },
{ 0x0000, "awardcapturepoints" },
{ 0x0000, "awardedfinalsurvivor" },
{ 0x0000, "awardgameevent" },
{ 0x0000, "awardhordeheadshots" },
{ 0x0000, "awardhordekill" },
{ 0x0000, "awardhorderevive" },
{ 0x0000, "awardhorderoundnumber" },
{ 0x0000, "awardhordweaponlevel" },
{ 0x0000, "awardpoints" },
{ 0x0000, "awardxp" },
{ 0x0000, "aware_aievents" },
{ 0x0000, "awareness_meter_fail" },
{ 0x0000, "awareness_param" },
{ 0x0000, "axis_check_cloak_state" },
{ 0x0000, "axis_global_accuracy_mod" },
{ 0x0000, "axis_start_spawn_name" },
{ 0x0000, "axiscapturing" },
{ 0x0000, "axischopper" },
{ 0x0000, "axisflagcarrierclientnum" },
{ 0x0000, "axisflagstatus" },
{ 0x0000, "axismode" },
{ 0x0000, "azm_get_current_zone" },
{ 0x0000, "azm_get_damb_enable" },
{ 0x0000, "azm_get_filter_bypass" },
{ 0x0000, "azm_get_filter_enable" },
{ 0x0000, "azm_get_mix_bypass" },
{ 0x0000, "azm_get_mix_enable" },
{ 0x0000, "azm_get_occlusion_bypass" },
{ 0x0000, "azm_get_occlusion_enable" },
{ 0x0000, "azm_get_quad_enable" },
{ 0x0000, "azm_get_reverb_bypass" },
{ 0x0000, "azm_get_reverb_enable" },
{ 0x0000, "azm_init" },
{ 0x0000, "azm_print_enter_blend" },
{ 0x0000, "azm_print_exit_blend" },
{ 0x0000, "azm_print_progress" },
{ 0x0000, "azm_set_current_zone" },
{ 0x0000, "azm_set_damb_enable" },
{ 0x0000, "azm_set_filter_bypass" },
{ 0x0000, "azm_set_filter_enable" },
{ 0x0000, "azm_set_mix_bypass" },
{ 0x0000, "azm_set_mix_enable" },
{ 0x0000, "azm_set_occlusion_bypass" },
{ 0x0000, "azm_set_occlusion_enable" },
{ 0x0000, "azm_set_quad_enable" },
{ 0x0000, "azm_set_reverb_bypass" },
{ 0x0000, "azm_set_reverb_enable" },
{ 0x0000, "azm_set_zone_dynamic_ambience" },
{ 0x0000, "azm_set_zone_mix" },
{ 0x0000, "azm_set_zone_occlusion" },
{ 0x0000, "azm_set_zone_reverb" },
{ 0x0000, "azm_set_zone_streamed_ambience" },
{ 0x0000, "azm_start_zone" },
{ 0x0000, "azm_stop_zone" },
{ 0x0000, "azm_stop_zones" },
{ 0x0000, "azm_use_string_table" },
{ 0x0000, "azmx_blend_zones" },
{ 0x0000, "azmx_get_blend_args" },
{ 0x0000, "azmx_get_preset_from_string_table" },
{ 0x0000, "azmx_get_zone_preset_from_stringtable_i"... },
{ 0x0000, "azmx_is_valid_damb_blend_request" },
{ 0x0000, "azmx_is_valid_mix_blend_request" },
{ 0x0000, "azmx_is_valid_samb_blend_request" },
{ 0x0000, "azmx_load_zone" },
{ 0x0000, "azmx_restart_damb" },
{ 0x0000, "azmx_restart_mix" },
{ 0x0000, "azmx_restart_occlusion" },
{ 0x0000, "azmx_restart_reverb" },
{ 0x0000, "azmx_restart_stream" },
{ 0x0000, "azmx_set_param_internal" },
{ 0x0000, "azmx_wait_till_fade_done_and_remove_zon"... },
//

*/