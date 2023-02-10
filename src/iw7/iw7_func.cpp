// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "iw7.hpp"

namespace xsk::gsc::iw7
{

extern std::array<std::pair<u16, char const*>, func_count> const func_list
{{
    { 0x001, "abs" },
    { 0x002, "acos" },
    { 0x003, "activateclientexploder" },
    { 0x004, "addagent" },
    { 0x005, "addbot" },
    { 0x006, "addtestclient" },
    { 0x007, "allclientsprint" },
    { 0x008, "ambientplay" },
    { 0x009, "ambientstop" },
    { 0x00A, "angleclamp" },
    { 0x00B, "angleclamp180" },
    { 0x00C, "anglesdelta" },
    { 0x00D, "anglestoaxis" },
    { 0x00E, "anglestoforward" },
    { 0x00F, "anglestoright" },
    { 0x010, "anglestoup" },
    { 0x011, "animhasnotetrack" },
    { 0x012, "asin" },
    { 0x013, "atan" },
    { 0x014, "_func_014" },
    { 0x015, "averagenormal" },
    { 0x016, "averagepoint" },
    { 0x017, "_func_017" },
    { 0x018, "_func_018" },
    { 0x019, "_func_019" },
    { 0x01A, "badplace_cylinder" },
    { 0x01B, "badplace_delete" },
    { 0x01C, "badplace_global" },
    { 0x01D, "bbprint" },
    { 0x01E, "blockteamradar" },
    { 0x01F, "botautoconnectenabled" },
    { 0x020, "_func_020" },
    { 0x021, "botflagmemoryevents" },
    { 0x022, "botgetclosestnavigablepoint" },
    { 0x023, "botgetmemoryevents" },
    { 0x024, "botgetteamdifficulty" },
    { 0x025, "botgetteamlimit" },
    { 0x026, "botmemoryflags" },
    { 0x027, "botsentientswap" },
    { 0x028, "botzonegetcount" },
    { 0x029, "botzonegetindoorpercent" },
    { 0x02A, "botzonenearestcount" },
    { 0x02B, "botzonesetteam" },
    { 0x02C, "bulletspread" },
    { 0x02D, "bullettrace" },
    { 0x02E, "bullettracepassed" },
    { 0x02F, "_func_02F" },
    { 0x030, "_func_030" },
    { 0x031, "_func_031" },
    { 0x032, "_func_032" },
    { 0x033, "_func_033" },
    { 0x034, "_func_034" },
    { 0x035, "canspawn" },
    { 0x036, "canspawnturret" },
    { 0x037, "capsuletracepassed" },
    { 0x038, "ceil" },
    { 0x039, "_func_039" },
    { 0x03A, "_func_03A" },
    { 0x03B, "_func_03B" },
    { 0x03C, "_func_03C" },
    { 0x03D, "_func_03D" },
    { 0x03E, "_func_03E" },
    { 0x03F, "_func_03F" },
    { 0x040, "_func_040" },
    { 0x041, "clamp" },
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
    { 0x04C, "cos" },
    { 0x04D, "createnavlink" },
    { 0x04E, "createthreatbiasgroup" },
    { 0x04F, "_func_04F" },
    { 0x050, "_func_050" },
    { 0x051, "_func_051" },
    { 0x052, "_func_052" },
    { 0x053, "_func_053" },
    { 0x054, "_func_054" },
    { 0x055, "_func_055" },
    { 0x056, "_func_056" },
    { 0x057, "_func_057" },
    { 0x058, "distance" },
    { 0x059, "distance2d" },
    { 0x05A, "distance2dsquared" },
    { 0x05B, "distancesquared" },
    { 0x05C, "drawcompassfriendlies" },
    { 0x05D, "earthquake" },
    { 0x05E, "_func_05E" },
    { 0x05F, "_func_05F" },
    { 0x060, "_func_060" },
    { 0x061, "_func_061" },
    { 0x062, "_func_062" },
    { 0x063, "endlobby" },
    { 0x064, "endparty" },
    { 0x065, "exitlevel" },
    { 0x066, "_func_066" },
    { 0x067, "findentrances" },
    { 0x068, "float" },
    { 0x069, "floor" },
    { 0x06A, "_func_06A" },
    { 0x06B, "_func_06B" },
    { 0x06C, "_func_06C" },
    { 0x06D, "_func_06D" },
    { 0x06E, "_func_06E" },
    { 0x06F, "_func_06F" },
    { 0x070, "_func_070" },
    { 0x071, "getactiveclientcount" },
    { 0x072, "_func_072" },
    { 0x073, "_func_073" },
    { 0x074, "_func_074" },
    { 0x075, "_func_075" },
    { 0x076, "getallnodes" },
    { 0x077, "_func_077" },
    { 0x078, "_func_078" },
    { 0x079, "_func_079" },
    { 0x07A, "getanimlength" },
    { 0x07B, "getarraykeys" },
    { 0x07C, "_func_07C" },
    { 0x07D, "_func_07D" },
    { 0x07E, "getbuildnumber" },
    { 0x07F, "getbuildversion" },
    { 0x080, "getclientmatchdata" },
    { 0x081, "getclosestnodeinsight" },
    { 0x082, "_func_082" },
    { 0x083, "_func_083" },
    { 0x084, "_func_084" },
    { 0x085, "getcsplinecount" },
    { 0x086, "_func_086" },
    { 0x087, "_func_087" },
    { 0x088, "_func_088" },
    { 0x089, "_func_089" },
    { 0x08A, "_func_08A" },
    { 0x08B, "_func_08B" },
    { 0x08C, "getcsplinepointposition" },
    { 0x08D, "getcsplinepointtangent" },
    { 0x08E, "_func_08E" },
    { 0x08F, "_func_08F" },
    { 0x090, "_func_090" },
    { 0x091, "getdvar" },
    { 0x092, "getdvarfloat" },
    { 0x093, "getdvarint" },
    { 0x094, "_func_094" },
    { 0x095, "_func_095" },
    { 0x096, "getenemysquaddata" },
    { 0x097, "_func_097" },
    { 0x098, "getent" },
    { 0x099, "getentarray" },
    { 0x09A, "_func_09A" },
    { 0x09B, "_func_09B" },
    { 0x09C, "getfirstarraykey" },
    { 0x09D, "_func_09D" },
    { 0x09E, "_func_09E" },
    { 0x09F, "_func_09F" },
    { 0x0A0, "getglass" },
    { 0x0A1, "_func_0A1" },
    { 0x0A2, "_func_0A2" },
    { 0x0A3, "getgroundposition" },
    { 0x0A4, "_func_0A4" },
    { 0x0A5, "_func_0A5" },
    { 0x0A6, "_func_0A6" },
    { 0x0A7, "getlinkednodes" },
    { 0x0A8, "_func_0A8" },
    { 0x0A9, "_func_0A9" },
    { 0x0AA, "_func_0AA" },
    { 0x0AB, "_func_0AB" },
    { 0x0AC, "_func_0AC" },
    { 0x0AD, "_func_0AD" },
    { 0x0AE, "getmatchrulesdata" },
    { 0x0AF, "getmaxagents" },
    { 0x0B0, "getmissileowner" },
    { 0x0B1, "getmovedelta" },
    { 0x0B2, "getnextarraykey" },
    { 0x0B3, "getnode" },
    { 0x0B4, "getnodearray" },
    { 0x0B5, "getnodesinradius" },
    { 0x0B6, "getnodesinradiussorted" },
    { 0x0B7, "getnodesintrigger" },
    { 0x0B8, "getnodesonpath" },
    { 0x0B9, "getnodezone" },
    { 0x0BA, "getnorthyaw" },
    { 0x0BB, "getnotetracktimes" },
    { 0x0BC, "_func_0BC" },
    { 0x0BD, "_func_0BD" },
    { 0x0BE, "getomnvar" },
    { 0x0BF, "_func_0BF" },
    { 0x0C0, "getpathdist" },
    { 0x0C1, "getplaylistid" },
    { 0x0C2, "getplaylistversion" },
    { 0x0C3, "getpredictedentityposition" },
    { 0x0C4, "_func_0C4" },
    { 0x0C5, "getentitylessscriptablearrayinradius" },
    { 0x0C6, "getspawnarray" },
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
    { 0x0D1, "getsubstr" },
    { 0x0D2, "getsystemtime" },
    { 0x0D3, "getteamplayersalive" },
    { 0x0D4, "getteamradar" },
    { 0x0D5, "getteamradarstrength" },
    { 0x0D6, "getteamscore" },
    { 0x0D7, "getthreatbias" },
    { 0x0D8, "gettime" },
    { 0x0D9, "gettimescale" },
    { 0x0DA, "gettimesincelastpaused" },
    { 0x0DB, "getuavstrengthlevelneutral" },
    { 0x0DC, "getuavstrengthlevelshowenemydirectional" },
    { 0x0DD, "getuavstrengthlevelshowenemyfastsweep" },
    { 0x0DE, "getuavstrengthmax" },
    { 0x0DF, "getuavstrengthmin" },
    { 0x0E0, "getvehiclenode" },
    { 0x0E1, "getvehiclenodearray" },
    { 0x0E2, "getweaponarray" },
    { 0x0E3, "getweaponattachments" },
    { 0x0E4, "getweaponbasename" },
    { 0x0E5, "getweaponcamoname" },
    { 0x0E6, "getweaponclipmodel" },
    { 0x0E7, "getweaponexplosionradius" },
    { 0x0E8, "getweaponflashtagname" },
    { 0x0E9, "getweaponhidetags" },
    { 0x0EA, "getweaponmodel" },
    { 0x0EB, "getweaponreticlename" },
    { 0x0EC, "getzonecount" },
    { 0x0ED, "getzonenearest" },
    { 0x0EE, "getzonenodeforindex" },
    { 0x0EF, "getzonenodes" },
    { 0x0F0, "getzonenodesbydist" },
    { 0x0F1, "getzoneorigin" },
    { 0x0F2, "getzonepath" },
    { 0x0F3, "glassradiusdamage" },
    { 0x0F4, "_func_0F4" },
    { 0x0F5, "incrementcounter" },
    { 0x0F6, "_func_0F6" },
    { 0x0F7, "int" },
    { 0x0F8, "invertangles" },
    { 0x0F9, "iprintln" },
    { 0x0FA, "iprintlnbold" },
    { 0x0FB, "isagent" },
    { 0x0FC, "isai" },
    { 0x0FD, "_func_0FD" },
    { 0x0FE, "isalive" },
    { 0x0FF, "isarray" },
    { 0x100, "isbot" },
    { 0x101, "iscinematicloaded" },
    { 0x102, "iscinematicplaying" },
    { 0x103, "isdedicatedserver" },
    { 0x104, "isdefined" },
    { 0x105, "isendstr" },
    { 0x106, "isenemyteam" },
    { 0x107, "isexplosivedamagemod" },
    { 0x108, "isglassdestroyed" },
    { 0x109, "_func_109" },
    { 0x10A, "_func_10A" },
    { 0x10B, "_func_10B" },
    { 0x10C, "_func_10C" },
    { 0x10D, "isplayer" },
    { 0x10E, "isplayernumber" },
    { 0x10F, "ispointinvolume" },
    { 0x110, "_func_110" },
    { 0x111, "_func_111" },
    { 0x112, "issentient" },
    { 0x113, "_func_113" },
    { 0x114, "_func_114" },
    { 0x115, "_func_115" },
    { 0x116, "isstring" },
    { 0x117, "issubstr" },
    { 0x118, "_func_118" },
    { 0x119, "_func_119" },
    { 0x11A, "_func_11A" },
    { 0x11B, "_func_11B" },
    { 0x11C, "isusingmatchrulesdata" },
    { 0x11D, "isvalidmissile" },
    { 0x11E, "_func_11E" },
    { 0x11F, "_func_11F" },
    { 0x120, "kick" },
    { 0x121, "_func_121" },
    { 0x122, "_func_122" },
    { 0x123, "length" },
    { 0x124, "length2d" },
    { 0x125, "length2dsquared" },
    { 0x126, "lengthsquared" },
    { 0x127, "_func_127" },
    { 0x128, "_func_128" },
    { 0x129, "_func_129" },
    { 0x12A, "_func_12A" },
    { 0x12B, "_func_12B" },
    { 0x12C, "loadfx" },
    { 0x12D, "_func_12D" },
    { 0x12E, "_func_12E" },
    { 0x12F, "_func_12F" },
    { 0x130, "log" },
    { 0x131, "logprint" },
    { 0x132, "logstring" },
    { 0x133, "lookupsoundlength" },
    { 0x134, "magicbullet" },
    { 0x135, "magicgrenade" },
    { 0x136, "magicgrenademanual" },
    { 0x137, "map_restart" },
    { 0x138, "_func_138" },
    { 0x139, "_func_139" },
    { 0x13A, "_func_13A" },
    { 0x13B, "_func_13B" },
    { 0x13C, "max" },
    { 0x13D, "min" },
    { 0x13E, "missile_createattractorent" },
    { 0x13F, "missile_createattractororigin" },
    { 0x140, "missile_createrepulsorent" },
    { 0x141, "missile_createrepulsororigin" },
    { 0x142, "missile_deleteattractor" },
    { 0x143, "_func_143" },
    { 0x144, "_func_144" },
    { 0x145, "_func_145" },
    { 0x146, "_func_146" },
    { 0x147, "newclienthudelem" },
    { 0x148, "newhudelem" },
    { 0x149, "newteamhudelem" },
    { 0x14A, "nodeexposedtosky" },
    { 0x14B, "nodesvisible" },
    { 0x14C, "notifyoncommand" },
    { 0x14D, "obituary" },
    { 0x14E, "_func_14E" },
    { 0x14F, "_func_14F" },
    { 0x150, "_func_150" },
    { 0x151, "_func_151" },
    { 0x152, "_func_152" },
    { 0x153, "_func_153" },
    { 0x154, "objective_delete" },
    { 0x155, "objective_icon" },
    { 0x156, "objective_onentity" },
    { 0x157, "objective_onentitywithrotation" },
    { 0x158, "objective_player" },
    { 0x159, "objective_playerenemyteam" },
    { 0x15A, "objective_playermask_hidefrom" },
    { 0x15B, "objective_playermask_hidefromall" },
    { 0x15C, "objective_playermask_showto" },
    { 0x15D, "objective_playermask_showtoall" },
    { 0x15E, "objective_playerteam" },
    { 0x15F, "objective_position" },
    { 0x160, "_func_160" },
    { 0x161, "_func_161" },
    { 0x162, "objective_state" },
    { 0x163, "_func_163" },
    { 0x164, "_func_164" },
    { 0x165, "_func_165" },
    { 0x166, "objective_team" },
    { 0x167, "_func_167" },
    { 0x168, "_func_168" },
    { 0x169, "_func_169" },
    { 0x16A, "physicsexplosionsphere" },
    { 0x16B, "_func_16B" },
    { 0x16C, "_func_16C" },
    { 0x16D, "_func_16D" },
    { 0x16E, "_func_16E" },
    { 0x16F, "playerphysicstrace" },
    { 0x170, "playfx" },
    { 0x171, "playfxontag" },
    { 0x172, "playfxontagforclients" },
    { 0x173, "playloopedfx" },
    { 0x174, "_func_174" },
    { 0x175, "_func_175" },
    { 0x176, "playrumbleonentity" },
    { 0x177, "playloopsound" },
    { 0x178, "_func_178" },
    { 0x179, "pointonsegmentnearesttopoint" },
    { 0x17A, "positionwouldtelefrag" },
    { 0x17B, "_func_17B" },
    { 0x17C, "_func_17C" },
    { 0x17D, "_func_17D" },
    { 0x17E, "precacheheadicon" },
    { 0x17F, "precacheitem" },
    { 0x180, "precacheleaderboards" },
    { 0x181, "precacheminimapicon" },
    { 0x182, "_func_182" },
    { 0x183, "precachemodel" },
    { 0x184, "precachempanim" },
    { 0x185, "precachestring" },
    { 0x186, "precacherumble" },
    { 0x187, "precacheshader" },
    { 0x188, "precacheshellshock" },
    { 0x189, "precachesound" },
    { 0x18A, "precachestatusicon" },
    { 0x18B, "precachestring" },
    { 0x18C, "precachetag" },
    { 0x18D, "precacheturret" },
    { 0x18E, "precachevehicle" },
    { 0x18F, "_func_18F" },
    { 0x190, "_func_190" },
    { 0x191, "radiusdamage" },
    { 0x192, "randomfloat" },
    { 0x193, "randomfloatrange" },
    { 0x194, "randomint" },
    { 0x195, "randomintrange" },
    { 0x196, "_func_196" },
    { 0x197, "_func_197" },
    { 0x198, "_func_198" },
    { 0x199, "_func_199" },
    { 0x19A, "_func_19A" },
    { 0x19B, "_func_19B" },
    { 0x19C, "_func_19C" },
    { 0x19D, "rotatepointaroundvector" },
    { 0x19E, "rotatevector" },
    { 0x19F, "rotatevectorinverted" },
    { 0x1A0, "_func_1A0" },
    { 0x1A1, "_func_1A1" },
    { 0x1A2, "_func_1A2" },
    { 0x1A3, "sendclientmatchdata" },
    { 0x1A4, "sendmatchdata" },
    { 0x1A5, "_func_1A5" },
    { 0x1A6, "_func_1A6" },
    { 0x1A7, "_func_1A7" },
    { 0x1A8, "setclientmatchdata" },
    { 0x1A9, "setclientmatchdatadef" },
    { 0x1AA, "setclientnamemode" },
    { 0x1AB, "_func_1AB" },
    { 0x1AC, "setdvar" },
    { 0x1AD, "setdvarifuninitialized" },
    { 0x1AE, "setdynamicdvar" },
    { 0x1AF, "setgameendtime" },
    { 0x1B0, "_func_1B0" },
    { 0x1B1, "_func_1B1" },
    { 0x1B2, "setignoremegroup" },
    { 0x1B3, "_func_1B3" },
    { 0x1B4, "setmapcenter" },
    { 0x1B5, "setmatchclientip" },
    { 0x1B6, "setmatchdata" },
    { 0x1B7, "setmatchdatadef" },
    { 0x1B8, "setmatchdataid" },
    { 0x1B9, "setminimap" },
    { 0x1BA, "_func_1BA" },
    { 0x1BB, "_func_1BB" },
    { 0x1BC, "setnojipscore" },
    { 0x1BD, "setnojiptime" },
    { 0x1BE, "_func_1BE" },
    { 0x1BF, "setomnvar" },
    { 0x1C0, "setomnvarforallclients" },
    { 0x1C1, "_func_1C1" },
    { 0x1C2, "_func_1C2" },
    { 0x1C3, "setplayerteamrank" },
    { 0x1C4, "_func_1C4" },
    { 0x1C5, "_func_1C5" },
    { 0x1C6, "setslowmotion" },
    { 0x1C7, "_func_1C7" },
    { 0x1C8, "_func_1C8" },
    { 0x1C9, "_func_1C9" },
    { 0x1CA, "_func_1CA" },
    { 0x1CB, "_func_1CB" },
    { 0x1CC, "setteammode" },
    { 0x1CD, "setteamradar" },
    { 0x1CE, "setteamradarstrength" },
    { 0x1CF, "setteamscore" },
    { 0x1D0, "_func_1D0" },
    { 0x1D1, "_func_1D1" },
    { 0x1D2, "_func_1D2" },
    { 0x1D3, "_func_1D3" },
    { 0x1D4, "_func_1D4" },
    { 0x1D5, "_func_1D5" },
    { 0x1D6, "setwinningteam" },
    { 0x1D7, "_func_1D7" },
    { 0x1D8, "sighttracepassed" },
    { 0x1D9, "sin" },
    { 0x1DA, "sortbydistance" },
    { 0x1DB, "soundexists" },
    { 0x1DC, "_func_1DC" },
    { 0x1DD, "_func_1DD" },
    { 0x1DE, "soundsettimescalefactor" },
    { 0x1DF, "spawn" },
    { 0x1E0, "spawnfx" },
    { 0x1E1, "spawnfxforclient" },
    { 0x1E2, "spawnhelicopter" },
    { 0x1E3, "spawnloopingsound" },
    { 0x1E4, "_func_1E4" },
    { 0x1E5, "spawnplane" },
    { 0x1E6, "spawnragdollconstraint" },
    { 0x1E7, "spawnsighttrace" },
    { 0x1E8, "spawnstruct" },
    { 0x1E9, "spawnturret" },
    { 0x1EA, "spawnvehicle" },
    { 0x1EB, "_func_1EB" },
    { 0x1EC, "_func_1EC" },
    { 0x1ED, "sqrt" },
    { 0x1EE, "squared" },
    { 0x1EF, "_func_1EF" },
    { 0x1F0, "_func_1F0" },
    { 0x1F1, "_func_1F1" },
    { 0x1F2, "stopfxontag" },
    { 0x1F3, "stricmp" },
    { 0x1F4, "strtok" },
    { 0x1F5, "_func_1F5" },
    { 0x1F6, "_func_1F6" },
    { 0x1F7, "tablelookup" },
    { 0x1F8, "tablelookupbyrow" },
    { 0x1F9, "tablelookupistring" },
    { 0x1FA, "_func_1FA" },
    { 0x1FB, "tablelookuprownum" },
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
    { 0x219, "tolower" },
    { 0x21A, "_func_21A" },
    { 0x21B, "_func_21B" },
    { 0x21C, "_func_21C" },
    { 0x21D, "_func_21D" },
    { 0x21E, "_func_21E" },
    { 0x21F, "_func_21F" },
    { 0x220, "transformmove" },
    { 0x221, "triggerfx" },
    { 0x222, "triggerportableradarping" },
    { 0x223, "triggeroneoffradarsweep" },
    { 0x224, "unblockteamradar" },
    { 0x225, "_func_225" },
    { 0x226, "_func_226" },
    { 0x227, "_func_227" },
    { 0x228, "_func_228" },
    { 0x229, "_func_229" },
    { 0x22A, "_func_22A" },
    { 0x22B, "vectorcross" },
    { 0x22C, "vectordot" },
    { 0x22D, "vectorfromlinetopoint" },
    { 0x22E, "vectorlerp" },
    { 0x22F, "vectornormalize" },
    { 0x230, "vectortoangles" },
    { 0x231, "vectortoyaw" },
    { 0x232, "vehicle_getarray" },
    { 0x233, "vehicle_getspawnerarray" },
    { 0x234, "visionsetalternate" },
    { 0x235, "visionsetfadetoblack" },
    { 0x236, "visionsetmissilecam" },
    { 0x237, "visionsetnaked" },
    { 0x238, "visionsetnight" },
    { 0x239, "visionsetpain" },
    { 0x23A, "visionsetthermal" },
    { 0x23B, "weaponaltweaponname" },
    { 0x23C, "weaponburstcount" },
    { 0x23D, "weaponclass" },
    { 0x23E, "weaponclipsize" },
    { 0x23F, "weaponfightdist" },
    { 0x240, "weaponfiretime" },
    { 0x241, "weaponhasthermalscope" },
    { 0x242, "weaponcandrop" },
    { 0x243, "weaponinheritsperks" },
    { 0x244, "weaponinventorytype" },
    { 0x245, "weaponisauto" },
    { 0x246, "weaponisboltaction" },
    { 0x247, "weaponisimpaling" },
    { 0x248, "weaponissemiauto" },
    { 0x249, "weaponmaxammo" },
    { 0x24A, "weaponmaxdist" },
    { 0x24B, "weaponstartammo" },
    { 0x24C, "weapontype" },
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
    { 0x26E, "physics_getbodylinvel" },
    { 0x26F, "_func_26F" },
    { 0x270, "_func_270" },
    { 0x271, "_func_271" },
    { 0x272, "_func_272" },
    { 0x273, "_func_273" },
    { 0x274, "_func_274" },
    { 0x275, "_func_275" },
    { 0x276, "getclosestpointonnavmesh" },
    { 0x277, "_func_277" },
    { 0x278, "_func_278" },
    { 0x279, "_func_279" },
    { 0x27A, "_func_27A" },
    { 0x27B, "_func_27B" },
    { 0x27C, "_func_27C" },
    { 0x27D, "isnumber" },
    { 0x27E, "_func_27E" },
    { 0x27F, "_func_27F" },
    { 0x280, "isbotmatchmakingenabled" },
    { 0x281, "addmpbottoteam" },
    { 0x282, "_func_282" },
    { 0x283, "_func_283" },
    { 0x284, "_func_284" },
    { 0x285, "physics_aabbbroadphasequery" },
    { 0x286, "physics_aabbquery" },
    { 0x287, "physics_raycast" },
    { 0x288, "physics_spherecast" },
    { 0x289, "physics_capsulecast" },
    { 0x28A, "physics_shapecast" },
    { 0x28B, "physics_querypoint" },
    { 0x28C, "physics_getclosestpointtosphere" },
    { 0x28D, "physics_getclosestpointtocapsule" },
    { 0x28E, "physics_getclosestpoint" },
    { 0x28F, "physics_createcontents" },
    { 0x290, "_func_290" },
    { 0x291, "_func_291" },
    { 0x292, "_func_292" },
    { 0x293, "_func_293" },
    { 0x294, "_func_294" },
    { 0x295, "_func_295" },
    { 0x296, "_func_296" },
    { 0x297, "_func_297" },
    { 0x298, "physics_charactercast" },
    { 0x299, "physics_getclosestpointtocharacter" },
    { 0x29A, "_func_29A" },
    { 0x29B, "_func_29B" },
    { 0x29C, "_func_29C" },
    { 0x29D, "_func_29D" },
    { 0x29E, "_func_29E" },
    { 0x29F, "cachespawnpathnodesincode" },
    { 0x2A0, "_func_2A0" },
    { 0x2A1, "triggerportableradarpingteam" },
    { 0x2A2, "isvfxfile" },
    { 0x2A3, "_func_2A3" },
    { 0x2A4, "_func_2A4" },
    { 0x2A5, "_func_2A5" },
    { 0x2A6, "_func_2A6" },
    { 0x2A7, "isnode" },
    { 0x2A8, "_func_2A8" },
    { 0x2A9, "setglobalsoundcontext" },
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
    { 0x2BF, "_func_2BF" },
    { 0x2C0, "_func_2C0" },
    { 0x2C1, "_func_2C1" },
    { 0x2C2, "_func_2C2" },
    { 0x2C3, "getweaponloottable" },
    { 0x2C4, "getweaponvariantindex" },
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
    { 0x2CF, "getmaxclients" },
    { 0x2D0, "_func_2D0" },
    { 0x2D1, "_func_2D1" },
    { 0x2D2, "getserverhostname" },
    { 0x2D3, "anglestoleft" },
    { 0x2D4, "_func_2D4" },
    { 0x2D5, "_func_2D5" },
    { 0x2D6, "_func_2D6" },
    { 0x2D7, "generateaxisanglesfromforwardvector" },
    { 0x2D8, "_func_2D8" },
    { 0x2D9, "isenumvaluevalid" },
    { 0x2DA, "_func_2DA" },
    { 0x2DB, "_func_2DB" },
    { 0x2DC, "_func_2DC" },
    { 0x2DD, "_func_2DD" },
    { 0x2DE, "_func_2DE" },
    { 0x2DF, "playfxontagsbetweenclients" },
    { 0x2E0, "playfxbetweenpoints" },
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
    { 0x2F9, "getangleindex" },
    { 0x2FA, "_func_2FA" },
    { 0x2FB, "_func_2FB" },
    { 0x2FC, "frontendscenecamerafade" },
    { 0x2FD, "frontendscenecamerafov" },
    { 0x2FE, "frontendscenegetactivesection" },
    { 0x2FF, "frontendscenecameracharacters" },
    { 0x300, "_func_300" },
    { 0x301, "_func_301" },
    { 0x302, "_func_302" },
    { 0x303, "isgamebattlematch" },
    { 0x304, "_func_304" },
    { 0x305, "_func_305" },
    { 0x306, "bbreportspawnfactors" },
    { 0x307, "bbreportspawntypes" },
    { 0x308, "bbreportspawnplayerdetails" },
    { 0x309, "_func_309" },
    { 0x30A, "_func_30A" },
    { 0x30B, "_func_30B" },
    { 0x30C, "_func_30C" },
    { 0x30D, "startpodium" },
    { 0x30E, "_func_30E" },
    { 0x30F, "frontendscenecameracinematic" },
    { 0x310, "setcodcasterclientmatchdata" },
    { 0x311, "getcodcasterclientmatchdata" },
    { 0x312, "sendcodcasterclientmatchdata" },
    { 0x313, "_func_313" },
    { 0x314, "_func_314" },
    { 0x315, "_func_315" },
    { 0x316, "_func_316" },
    { 0x317, "_func_317" },
    { 0x318, "_func_318" },
    { 0x319, "_func_319" },
    { 0x31A, "_func_31A" },
    { 0x31B, "_func_31B" },
    { 0x31C, "_func_31C" },
    { 0x31D, "setintrocameraactive" },
    { 0x31E, "removeallcorpses" },
    { 0x31F, "_func_31F" },
    { 0x320, "_func_320" },
    { 0x321, "stopspectateplayer" },
    { 0x322, "weaponispreferreddrop" },
    { 0x323, "_func_323" },
    { 0x324, "_func_324" },
    { 0x325, "_func_325" },
    { 0x326, "_func_326" },
    { 0x327, "_func_327" },
}};

} // namespace xsk::gsc::iw7
