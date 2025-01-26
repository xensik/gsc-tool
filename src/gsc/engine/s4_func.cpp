// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/gsc/engine/s4.hpp"

namespace xsk::gsc::s4
{

extern std::array<std::pair<u16, char const*>, func_count> const func_list
{{
    { 0x001, "abs" },
    { 0x005, "addbot" },
    { 0x00E, "anglestoforward" },
    { 0x010, "anglestoup" },
    { 0x01B, "bbPrint" },
    { 0x040, "clamp" },
    { 0x058, "distance2d" },
    { 0x059, "distance2dsquared" },
    { 0x068, "floor" },
    { 0x08F, "getdvar" },
    { 0x090, "getdvarfloat" },
    { 0x091, "getdvarint" },
    { 0x097, "getentarray" },
    { 0x09B, "getfirstarraykey" },
    { 0x0AD, "getmatchrulesdata" },
    { 0x0B1, "getnextarraykey" },
    { 0x0C9, "getscriptablearray" },
    { 0x0DD, "gettime" },
    { 0x0FE, "int" },
    { 0x105, "isai" },
    { 0x108, "isbot" },
    { 0x118, "isplayer" },
    { 0x122, "issubstr" },
    { 0x126, "isusingmatchrulesdata" },
    { 0x13B, "loadfx" },
    { 0x146, "map_restart" },
    { 0x15A, "obituary" },
    { 0x191, "objective_setpingsforteam" },
    { 0x19C, "playfxontag" },
    { 0x1BB, "randomfloat" },
    { 0x1BD, "randomint" },
    { 0x1D3, "setclientnamemode" },
    { 0x1D5, "setdvar" },
    { 0x1D6, "setdvarifuninitialized" },
    { 0x1D7, "setdynamicdvar" },
    { 0x1D8, "setgameendtime" },
    { 0x1DD, "setmapcenter" },
    { 0x1E9, "setomnvar" },
    { 0x20A, "spawn" },
    { 0x214, "spawnstruct" },
    { 0x215, "spawnturret" },
    { 0x248, "tolower" },
    { 0x26D, "weaponburstcount" },
    { 0x26E, "weaponclass" },
    { 0x270, "weaponclipsize" },
    { 0x272, "weaponfiretime" },
    { 0x277, "weaponisauto" },
    { 0x27A, "weaponissemiauto" },
    { 0x2BA, "isbotmatchmakingenabled" },
    { 0x2BB, "addmpbottoteam" },
    { 0x2F1, "weaponisbeam" },
    { 0x351, "makeweapon" },
    { 0x374, "isnullweapon" },
    { 0x424, "brmatchstarted" },
}};

} // namespace xsk::gsc::s4
