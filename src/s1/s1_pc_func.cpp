// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "s1_pc.hpp"

namespace xsk::gsc::s1_pc
{

extern std::array<std::pair<u16, char const*>, func_count> const func_list
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
    { 0x023, "clearallcorpses" }, // SP 0x140261020
    { 0x024, "setturretnode" }, // SP 0x14027EA80
    { 0x025, "unsetturretnode" }, // SP 0x14027EB20
    { 0x026, "setnodepriority" }, // SP 0x14027E9B0
    { 0x027, "_func_027" }, // SP 0x14027E870
    { 0x028, "_func_028" }, // empty
    { 0x029, "_func_029" }, // empty
    { 0x02A, "_func_02A" }, // empty
    { 0x02B, "_func_02B" }, // empty
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
    { 0x041, "getweaponmodel" },
    { 0x042, "getculldist" },
    { 0x043, "sethalfresparticles" },
    { 0x044, "getmapsunlight" },
    { 0x045, "setsunlight" },
    { 0x046, "resetsunlight" },
    { 0x047, "getmapsundirection" },
    { 0x048, "getmapsunangles" },
    { 0x049, "setsundirection" },
    { 0x04A, "lerpsundirection" },
    { 0x04B, "lerpsunangles" },
    { 0x04C, "resetsundirection" },
    { 0x04D, "enableforcedsunshadows" },
    { 0x04E, "enableforcednosunshadows" },
    { 0x04F, "disableforcedsunshadows" },
    { 0x050, "enableouterspacemodellighting" },
    { 0x051, "disableouterspacemodellighting" },
    { 0x052, "remapstage" },
    { 0x053, "_func_053" }, // SP 0x14025F6B0
    { 0x054, "_func_054" }, // SP 0x14025F800
    { 0x055, "_func_055" }, // SP 0x14025F830
    { 0x056, "_func_056" }, // SP 0x14025F850
    { 0x057, "_func_057" }, // SP 0x14025F920
    { 0x058, "_func_058" }, // SP 0x14025FA20
    { 0x059, "_func_059" }, // SP 0x14025FB80
    { 0x05A, "_func_05A" }, // SP 0x14025FC00
    { 0x05B, "_func_05B" }, // SP 0x14025FC80
    { 0x05C, "_func_05C" }, // SP 0x14025FE00
    { 0x05D, "getweapondisplayname" },
    { 0x05E, "getweaponbasename" },
    { 0x05F, "getweaponattachments" },
    { 0x060, "getweaponattachmentdisplaynames" },
    { 0x061, "getweaponcamoname" },
    { 0x062, "getweaponreticlename" },
    { 0x063, "getanimlength" },
    { 0x064, "animhasnotetrack" },
    { 0x065, "getnotetracktimes" },
    { 0x066, "spawn" },
    { 0x067, "spawnloopsound" },
    { 0x068, "spawnloopingsound" },
    { 0x069, "bullettrace" },
    { 0x06A, "target_setmaxsize" },
    { 0x06B, "target_setcolor" },
    { 0x06C, "target_setdelay" },
    { 0x06D, "getstartorigin" },
    { 0x06E, "getstartangles" },
    { 0x06F, "_func_06F" }, // SP 0x14020DCB0
    { 0x070, "_func_070" }, // SP 0x14025FCB0
    { 0x071, "_func_071" }, // SP 0x140243B90, MP 0x1403104D0
    { 0x072, "_func_072" }, // SP 0x14025BCC0
    { 0x073, "_func_073" }, // SP 0x14025BD60
    { 0x074, "_func_074" }, // SP 0x14025BFA0
    { 0x075, "_func_075" }, // SP 0x14025C150
    { 0x076, "_func_076" }, // SP 0x140246C90, MP 0x140311AD0
    { 0x077, "_func_077" }, // SP 0x140246D70, MP 0x140311D80
    { 0x078, "_func_078" }, // SP 0x140246DA0, MP 0x140311D90
    { 0x079, "_func_079" }, // SP 0x140246F10, MP 0x140311DF0
    { 0x07A, "_func_07A" }, // SP 0x140247010, MP 0x140311EF0
    { 0x07B, "_func_07B" }, // SP 0x140247060, MP 0x140311F50
    { 0x07C, "_func_07C" }, // SP 0x14025C320
    { 0x07D, "_func_07D" }, // SP 0x14025D3E0
    { 0x07E, "_func_07E" }, // SP 0x14025C220
    { 0x07F, "_func_07F" }, // SP 0x14025F620
    { 0x080, "_func_080" }, // SP 0x140241480, MP 0x14031FB60
    { 0x081, "_func_081" }, // SP 0x14025F640
    { 0x082, "_func_082" }, // SP 0x14025F690
    { 0x083, "_func_083" }, // SP 0x14025D480
    { 0x084, "_func_084" }, // SP 0x14025E160
    { 0x085, "_func_085" }, // SP 0x14025E180
    { 0x086, "_func_086" }, // SP 0x14025D8D0
    { 0x087, "_func_087" }, // SP 0x14025E1A0
    { 0x088, "_func_088" }, // SP 0x14025E270
    { 0x089, "_func_089" }, // SP 0x14025FE70
    { 0x08A, "_func_08A" }, // SP 0x140260370
    { 0x08B, "bullettracepassed" },
    { 0x08C, "sighttracepassed" },
    { 0x08D, "physicstrace" },
    { 0x08E, "playerphysicstrace" },
    { 0x08F, "getgroundposition" },
    { 0x090, "getmovedelta" },
    { 0x091, "getangledelta" },
    { 0x092, "getnorthyaw" },
    { 0x093, "_func_093" }, // SP 0x14025C1F0
    { 0x094, "_func_094" }, // SP 0x14025C2F0
    { 0x095, "_func_095" }, // SP 0x14025E330
    { 0x096, "_func_096" }, // SP 0x14025E380
    { 0x097, "_func_097" }, // SP 0x14025E2F0
    { 0x098, "_func_098" }, // SP 0x14026C770
    { 0x099, "_func_099" }, // SP 0x14026CB40
    { 0x09A, "_func_09A" }, // SP 0x14026CE30
    { 0x09B, "_func_09B" }, // SP 0x14026CDF0
    { 0x09C, "_func_09C" }, // SP 0x14026D9F0
    { 0x09D, "_func_09D" }, // SP 0x14026D670
    { 0x09E, "_func_09E" }, // SP 0x14026CCC0
    { 0x09F, "_func_09F" }, // SP 0x14026CC50
    { 0x0A0, "_func_0A0" }, // SP 0x14026DB20
    { 0x0A1, "_func_0A1" }, // SP 0x14026C790
    { 0x0A2, "_func_0A2" }, // SP 0x14026CBD0
    { 0x0A3, "_func_0A3" }, // SP 0x14026CD60
    { 0x0A4, "_func_0A4" }, // SP 0x14026CE50
    { 0x0A5, "_func_0A5" }, // SP 0x14026D2E0
    { 0x0A6, "_func_0A6" }, // SP 0x14026CC40
    { 0x0A7, "_func_0A7" }, // SP 0x14026DB10
    { 0x0A8, "_func_0A8" }, // SP 0x14026D8C0
    { 0x0A9, "_func_0A9" }, // SP 0x14026C7C0
    { 0x0AA, "_func_0AA" }, // SP 0x14026C9F0
    { 0x0AB, "_func_0AB" }, // SP 0x14026C8F0
    { 0x0AC, "_func_0AC" }, // SP 0x14026D520
    { 0x0AD, "setnorthyaw" },
    { 0x0AE, "setslowmotion" },
    { 0x0AF, "randomint" },
    { 0x0B0, "randomfloat" },
    { 0x0B1, "randomintrange" },
    { 0x0B2, "randomfloatrange" },
    { 0x0B3, "sin" },
    { 0x0B4, "cos" },
    { 0x0B5, "tan" },
    { 0x0B6, "asin" },
    { 0x0B7, "acos" },
    { 0x0B8, "atan" },
    { 0x0B9, "int" },
    { 0x0BA, "float" },
    { 0x0BB, "abs" },
    { 0x0BC, "min" },
    { 0x0BD, "objective_additionalcurrent" },
    { 0x0BE, "objective_ring" },
    { 0x0BF, "objective_setpointertextoverride" },
    { 0x0C0, "getnode" },
    { 0x0C1, "getnodearray" },
    { 0x0C2, "getallnodes" },
    { 0x0C3, "getnodesinradius" },
    { 0x0C4, "getnodesinradiussorted" },
    { 0x0C5, "getclosestnodeinsight" },
    { 0x0C6, "getreflectionlocs" },
    { 0x0C7, "getreflectionreferencelocs" },
    { 0x0C8, "getvehicletracksegment" },
    { 0x0C9, "getvehicletracksegmentarray" },
    { 0x0CA, "getallvehicletracksegments" },
    { 0x0CB, "isarray" },
    { 0x0CC, "isai" },
    { 0x0CD, "getindexforluincstring" },
    { 0x0CE, "issentient" },
    { 0x0CF, "_func_0CF" }, // SP 0x140259F30
    { 0x0D0, "_func_0D0" }, // SP 0x14025A0E0
    { 0x0D1, "_func_0D1" }, // SP 0x14025A170
    { 0x0D2, "_func_0D2" }, // SP 0x14025A1F0
    { 0x0D3, "_func_0D3" }, // SP 0x14025A220
    { 0x0D4, "_func_0D4" }, // SP 0x14025A620
    { 0x0D5, "_func_0D5" }, // SP 0x14025B700
    { 0x0D6, "_func_0D6" }, // SP 0x14025B8F0
    { 0x0D7, "_func_0D7" }, // SP 0x14025BA10
    { 0x0D8, "_func_0D8" }, // SP 0x14025BC40
    { 0x0D9, "_func_0D9" }, // SP 0x14025BB90
    { 0x0DA, "_func_0DA" }, // SP 0x14025BE80
    { 0x0DB, "_func_0DB" }, // SP 0x14025BF20
    { 0x0DC, "_func_0DC" }, // empty
    { 0x0DD, "_func_0DD" }, // SP 0x14025C0E0
    { 0x0DE, "max" },
    { 0x0DF, "floor" },
    { 0x0E0, "ceil" },
    { 0x0E1, "exp" },
    { 0x0E2, "log" },
    { 0x0E3, "sqrt" },
    { 0x0E4, "squared" },
    { 0x0E5, "clamp" },
    { 0x0E6, "angleclamp" },
    { 0x0E7, "angleclamp180" },
    { 0x0E8, "vectorfromlinetopoint" },
    { 0x0E9, "pointonsegmentnearesttopoint" },
    { 0x0EA, "distance" },
    { 0x0EB, "distance2d" },
    { 0x0EC, "distancesquared" },
    { 0x0ED, "length" },
    { 0x0EE, "length2d" },
    { 0x0EF, "lengthsquared" },
    { 0x0F0, "length2dsquared" },
    { 0x0F1, "closer" },
    { 0x0F2, "vectordot" },
    { 0x0F3, "vectorcross" },
    { 0x0F4, "axistoangles" },
    { 0x0F5, "visionsetthermal" },
    { 0x0F6, "visionsetpain" },
    { 0x0F7, "endlobby" },
    { 0x0F8, "setac130ambience" },
    { 0x0F9, "getmapcustom" },
    { 0x0FA, "spawnsighttrace" },
    { 0x0FB, "incrementcounter" },
    { 0x0FC, "getcountertotal" },
    { 0x0FD, "getlevelticks" },
    { 0x0FE, "perlinnoise2d" },
    { 0x0FF, "calcrockingangles" },
    { 0x100, "reconevent" },
    { 0x101, "reconspatialevent" },
    { 0x102, "setsunflareposition" },
    { 0x103, "createthreatbiasgroup" },
    { 0x104, "threatbiasgroupexists" },
    { 0x105, "getthreatbias" },
    { 0x106, "setthreatbias" },
    { 0x107, "setthreatbiasagainstall" },
    { 0x108, "setignoremegroup" },
    { 0x109, "isenemyteam" },
    { 0x10A, "objective_additionalentity" },
    { 0x10B, "objective_state_nomessage" },
    { 0x10C, "objective_string" },
    { 0x10D, "objective_string_nomessage" },
    { 0x10E, "objective_additionalposition" },
    { 0x10F, "objective_current_nomessage" },
    { 0x110, "vectornormalize" },
    { 0x111, "vectortoangles" },
    { 0x112, "vectortoyaw" },
    { 0x113, "vectorlerp" },
    { 0x114, "anglestoup" },
    { 0x115, "anglestoright" },
    { 0x116, "anglestoforward" },
    { 0x117, "anglesdelta" },
    { 0x118, "combineangles" },
    { 0x119, "transformmove" },
    { 0x11A, "rotatevector" },
    { 0x11B, "rotatepointaroundvector" },
    { 0x11C, "issubstr" },
    { 0x11D, "isendstr" },
    { 0x11E, "getsubstr" },
    { 0x11F, "tolower" },
    { 0x120, "strtok" },
    { 0x121, "stricmp" },
    { 0x122, "ambientplay" },
    { 0x123, "getuavstrengthmax" },
    { 0x124, "getuavstrengthlevelneutral" },
    { 0x125, "getuavstrengthlevelshowenemyfastsweep" },
    { 0x126, "getuavstrengthlevelshowenemydirectional" },
    { 0x127, "blockteamradar" },
    { 0x128, "unblockteamradar" },
    { 0x129, "isteamradarblocked" },
    { 0x12A, "getassignedteam" },
    { 0x12B, "setmatchdata" },
    { 0x12C, "getmatchdata" },
    { 0x12D, "sendmatchdata" },
    { 0x12E, "clearmatchdata" },
    { 0x12F, "setmatchdatadef" },
    { 0x130, "setmatchclientip" },
    { 0x131, "setmatchdataid" },
    { 0x132, "setclientmatchdata" },
    { 0x133, "getclientmatchdata" },
    { 0x134, "setclientmatchdatadef" },
    { 0x135, "sendclientmatchdata" },
    { 0x136, "getbuildversion" },
    { 0x137, "getbuildnumber" },
    { 0x138, "getsystemtime" },
    { 0x139, "getmatchrulesdata" },
    { 0x13A, "isusingmatchrulesdata" },
    { 0x13B, "kick" },
    { 0x13C, "issplitscreen" },
    { 0x13D, "setmapcenter" },
    { 0x13E, "setgameendtime" },
    { 0x13F, "visionsetnaked" },
    { 0x140, "visionsetnight" },
    { 0x141, "visionsetmissilecam" },
    { 0x142, "ambientstop" },
    { 0x143, "precachemodel" },
    { 0x144, "precacheshellshock" },
    { 0x145, "precacheitem" },
    { 0x146, "precacheshader" },
    { 0x147, "precachestring" },
    { 0x148, "precachemenu" },
    { 0x149, "precacherumble" },
    { 0x14A, "precachelocationselector" },
    { 0x14B, "precacheleaderboards" },
    { 0x14C, "loadfx" },
    { 0x14D, "playfx" },
    { 0x14E, "playfxontag" },
    { 0x14F, "stopfxontag" },
    { 0x150, "killfxontag" },
    { 0x151, "playloopedfx" },
    { 0x152, "spawnfx" },
    { 0x153, "triggerfx" },
    { 0x154, "playfxontagforclients" },
    { 0x155, "setwinningteam" },
    { 0x156, "announcement" },
    { 0x157, "clientannouncement" },
    { 0x158, "setteammode" },
    { 0x159, "getteamscore" },
    { 0x15A, "setteamscore" },
    { 0x15B, "setclientnamemode" },
    { 0x15C, "updateclientnames" },
    { 0x15D, "getteamplayersalive" },
    { 0x15E, "logprint" },
    { 0x15F, "worldentnumber" },
    { 0x160, "obituary" },
    { 0x161, "positionwouldtelefrag" },
    { 0x162, "canspawn" },
    { 0x163, "getstarttime" },
    { 0x164, "precachestatusicon" },
    { 0x165, "precacheheadicon" },
    { 0x166, "precacheminimapicon" },
    { 0x167, "precachempanim" },
    { 0x168, "map_restart" },
    { 0x169, "_func_169" }, // MP 0x14032E320
    { 0x16A, "exitlevel" },
    { 0x16B, "_func_16B" }, // MP 0x14032E4E0
    { 0x16C, "_func_16C" }, // MP 0x14032EA90
    { 0x16D, "_func_16D" }, // MP 0x140328560
    { 0x16E, "_func_16E" }, // MP 0x14032EB80
    { 0x16F, "_func_16F" }, // MP 0x14032EEF0
    { 0x170, "_func_170" }, // MP 0x14032EBC0
    { 0x171, "_func_171" }, // MP 0x14032EC00
    { 0x172, "_func_172" }, // MP 0x140328580
    { 0x173, "_func_173" }, // MP 0x140328590
    { 0x174, "_func_174" }, // MP 0x140328700
    { 0x175, "_func_175" }, // MP 0x14032CBB0
    { 0x176, "_func_176" }, // MP 0x14032CC20
    { 0x177, "_func_177" }, // MP 0x14032CCE0
    { 0x178, "_func_178" }, // MP 0x14032CDC0
    { 0x179, "_func_179" }, // MP 0x14032CE20
    { 0x17A, "physicsexplosionsphere" },
    { 0x17B, "physicsexplosioncylinder" },
    { 0x17C, "physicsjolt" },
    { 0x17D, "physicsjitter" },
    { 0x17E, "setexpfog" },
    { 0x17F, "setexpfogext" },
    { 0x180, "setexpfogdvarsonly" },
    { 0x181, "setexpfogextdvarsonly" },
    { 0x182, "setatmosfog" },
    { 0x183, "setatmosfogdvarsonly" },
    { 0x184, "isexplosivedamagemod" },
    { 0x185, "radiusdamage" },
    { 0x186, "setplayerignoreradiusdamage" },
    { 0x187, "glassradiusdamage" },
    { 0x188, "earthquake" },
    { 0x189, "getnumparts" },
    { 0x18A, "objective_onentity" },
    { 0x18B, "objective_onentitywithrotation" },
    { 0x18C, "objective_team" },
    { 0x18D, "objective_player" },
    { 0x18E, "objective_playerteam" },
    { 0x18F, "objective_playerenemyteam" },
    { 0x190, "objective_playermask_hidefromall" },
    { 0x191, "objective_playermask_hidefrom" },
    { 0x192, "objective_playermask_showtoall" },
    { 0x193, "objective_playermask_showto" },
    { 0x194, "iprintln" },
    { 0x195, "iprintlnbold" },
    { 0x196, "logstring" },
    { 0x197, "getent" },
    { 0x198, "getentarray" },
    { 0x199, "getspawnarray" },
    { 0x19A, "spawnplane" },
    { 0x19B, "spawnstruct" },
    { 0x19C, "spawnhelicopter" },
    { 0x19D, "isalive" },
    { 0x19E, "isspawner" },
    { 0x19F, "missile_createattractorent" },
    { 0x1A0, "missile_createattractororigin" },
    { 0x1A1, "missile_createrepulsorent" },
    { 0x1A2, "missile_createrepulsororigin" },
    { 0x1A3, "missile_deleteattractor" },
    { 0x1A4, "playsoundatpos" },
    { 0x1A5, "newhudelem" },
    { 0x1A6, "newclienthudelem" },
    { 0x1A7, "newteamhudelem" },
    { 0x1A8, "resettimeout" },
    { 0x1A9, "isplayer" },
    { 0x1AA, "isplayernumber" },
    { 0x1AB, "getpartname" },
    { 0x1AC, "weaponfiretime" },
    { 0x1AD, "weaponclipsize" },
    { 0x1AE, "weaponisauto" },
    { 0x1AF, "weaponissemiauto" },
    { 0x1B0, "weaponisboltaction" },
    { 0x1B1, "weaponinheritsperks" },
    { 0x1B2, "weaponburstcount" },
    { 0x1B3, "weapontype" },
    { 0x1B4, "weaponclass" },
    { 0x1B5, "getnextarraykey" },
    { 0x1B6, "sortbydistance" },
    { 0x1B7, "tablelookup" },
    { 0x1B8, "tablelookupbyrow" },
    { 0x1B9, "tablelookupistring" },
    { 0x1BA, "tablelookupistringbyrow" },
    { 0x1BB, "tablelookuprownum" },
    { 0x1BC, "tableexists" },
    { 0x1BD, "getmissileowner" },
    { 0x1BE, "magicbullet" },
    { 0x1BF, "getweaponflashtagname" },
    { 0x1C0, "averagepoint" },
    { 0x1C1, "averagenormal" },
    { 0x1C2, "vehicle_getspawnerarray" },
    { 0x1C3, "playrumbleonposition" },
    { 0x1C4, "playrumblelooponposition" },
    { 0x1C5, "stopallrumbles" },
    { 0x1C6, "soundexists" },
    { 0x1C7, "openfile" },
    { 0x1C8, "closefile" },
    { 0x1C9, "fprintln" },
    { 0x1CA, "fprintfields" },
    { 0x1CB, "freadln" },
    { 0x1CC, "fgetarg" },
    { 0x1CD, "setminimap" },
    { 0x1CE, "setthermalbodymaterial" },
    { 0x1CF, "getarraykeys" },
    { 0x1D0, "getfirstarraykey" },
    { 0x1D1, "getglass" },
    { 0x1D2, "getglassarray" },
    { 0x1D3, "getglassorigin" },
    { 0x1D4, "isglassdestroyed" },
    { 0x1D5, "destroyglass" },
    { 0x1D6, "deleteglass" },
    { 0x1D7, "getentchannelscount" },
    { 0x1D8, "getentchannelname" },
    { 0x1D9, "objective_add" },
    { 0x1DA, "objective_delete" },
    { 0x1DB, "objective_state" },
    { 0x1DC, "objective_icon" },
    { 0x1DD, "objective_position" },
    { 0x1DE, "objective_current" },
    { 0x1DF, "_func_1DF" }, // SP 0x140245580, MP 0x14030C5F0 // weap
    { 0x1E0, "_func_1E0" }, // SP 0x140245870, MP 0x14030C960
    { 0x1E1, "_func_1E1" }, // SP 0x140245A90, MP 0x14030CAD0
    { 0x1E2, "_func_1E2" }, // SP 0x140245D00, MP 0x14030D110
    { 0x1E3, "_func_1E3" }, // SP 0x140246230, MP 0x14030D980
    { 0x1E4, "_func_1E4" }, // SP 0x1402464C0, MP 0x14030DFC0
    { 0x1E5, "_func_1E5" }, // SP 0x1402468A0, MP 0x14030E400
    { 0x1E6, "_func_1E6" }, // SP 0x140246E40, MP 0x14030E970
    { 0x1E7, "getvehiclenode" },
    { 0x1E8, "getvehiclenodearray" },
    { 0x1E9, "getallvehiclenodes" },
    { 0x1EA, "getnumvehicles" },
    { 0x1EB, "precachevehicle" },
    { 0x1EC, "spawnvehicle" },
    { 0x1ED, "vehicle_getarray" },
    { 0x1EE, "pow" },
    { 0x1EF, "angleclamp360" },
    { 0x1F0, "botgetmemoryevents" },
    { 0x1F1, "botautoconnectenabled" },
    { 0x1F2, "botzonegetcount" },
    { 0x1F3, "botzonesetteam" },
    { 0x1F4, "botzonenearestcount" },
    { 0x1F5, "botmemoryflags" },
    { 0x1F6, "botflagmemoryevents" },
    { 0x1F7, "botzonegetindoorpercent" },
    { 0x1F8, "botsentientswap" },
    { 0x1F9, "isbot" },
    { 0x1FA, "isagent" },
    { 0x1FB, "_func_1FB" }, // MP 0x140406E40
    { 0x1FC, "_func_1FC" }, // MP 0x140432CD0
    { 0x1FD, "_func_1FD" }, // MP 0x140432EE0
    { 0x1FE, "_func_1FE" }, // MP 0x1402D2430
    { 0x1FF, "_func_1FF" }, // SP 0x14027E8E0, MP 0x1402D3710
    { 0x200, "_func_200" }, // SP 0x14027E550, MP 0x1402D2530
    { 0x201, "_func_201" }, // MP 0x1402D28C0
    { 0x202, "_func_202" }, // MP 0x1402D28D0
    { 0x203, "_func_203" }, // MP 0x1402D2A40
    { 0x204, "_func_204" }, // MP 0x1402D30E0
    { 0x205, "_func_205" }, // MP 0x1402D3060
    { 0x206, "_func_206" }, // MP 0x1402D2370
    { 0x207, "_func_207" }, // MP 0x1402D2D20
    { 0x208, "_func_208" }, // MP 0x1402D29D0
    { 0x209, "_func_209" }, // SP 0x14025C070, MP 0x14032AF60
    { 0x20A, "_func_20A" }, // empty
    { 0x20B, "_func_20B" }, // empty
    { 0x20C, "_func_20C" }, // MP 0x1402D3310
    { 0x20D, "_func_20D" }, // MP 0x1402D1E20
    { 0x20E, "badplace_global" },
    { 0x20F, "getpathdist" },
    { 0x210, "getlinkednodes" },
    { 0x211, "disconnectnodepair" },
    { 0x212, "connectnodepair" },
    { 0x213, "_func_213" }, // SP 0x140259F80
    { 0x214, "_func_214" }, // empty
    { 0x215, "_func_215" }, // empty
    { 0x216, "_func_216" }, // MP 0x140330030
    { 0x217, "_func_217" }, // MP 0x14032E430
    { 0x218, "_func_218" }, // SP 0x140321E90
    { 0x219, "_func_219" }, // SP 0x1403220D0
    { 0x21A, "_func_21A" }, // SP 0x140322010
    { 0x21B, "_func_21B" }, // SP 0x140321FB0
    { 0x21C, "_func_21C" }, // SP 0x140321B90
    { 0x21D, "_func_21D" }, // SP 0x140321C10
    { 0x21E, "_func_21E" }, // SP 0x140321BC0
    { 0x21F, "_func_21F" }, // SP 0x140321C50
    { 0x220, "_func_220" }, // SP 0x1402509E0, MP 0x1403176D0
    { 0x221, "_func_221" }, // SP 0x14024FD80, MP 0x1403175D0
    { 0x222, "_func_222" }, // SP 0x140253430, MP 0x14031FB30
    { 0x223, "_func_223" }, // SP 0x1402538E0, MP 0x140320C40
    { 0x224, "_func_224" }, // SP 0x140253AE0, MP 0x140320E00
    { 0x225, "_func_225" }, // SP 0x140254010, MP 0x1403210C0
    { 0x226, "_func_226" }, // SP 0x140254670, MP 0x140321250
    { 0x227, "_func_227" }, // SP 0x14023DF60, MP 0x140321520
    { 0x228, "_func_228" }, // SP 0x14023E450, MP 0x1403217F0
    { 0x229, "_func_229" }, // MP 0x14030FA10
    { 0x22A, "_func_22A" }, // SP 0x140250490, MP 0x1403172F0
    { 0x22B, "_func_22B" }, // SP 0x14025FDE0
    { 0x22C, "_func_22C" }, // SP 0x14025FDC0
    { 0x22D, "_func_22D" }, // SP 0x14025FDA0
    { 0x22E, "_func_22E" }, // empty
    { 0x22F, "_func_22F" }, // MP 0x14030B9E0
    { 0x230, "_func_230" }, // empty
    { 0x231, "_func_231" }, // SP 0x1402403A0, MP 0x14030BB90
    { 0x232, "_func_232" }, // SP 0x140240810, MP 0x140320F60
    { 0x233, "_func_233" }, // SP 0x14025CF00, MP 0x14032BE10
    { 0x234, "_func_234" }, // SP 0x14025EA90
    { 0x235, "_func_235" }, // SP 0x14024CB60, MP 0x140321C30
    { 0x236, "_func_236" }, // MP 0x140321C40
    { 0x237, "_func_237" }, // empty
    { 0x238, "_func_238" }, // SP 0x14024A020, MP 0x140311A40
    { 0x239, "_func_239" }, // SP 0x140247090, MP 0x14030EC50
    { 0x23A, "_func_23A" }, // SP 0x140247300, MP 0x14030F050
    { 0x23B, "_func_23B" }, // SP 0x1402474E0, MP 0x14030F340
    { 0x23C, "_func_23C" }, // SP 0x1402477E0, MP 0x14030F550
    { 0x23D, "_func_23D" }, // SP 0x140247A40, MP 0x14030F710
    { 0x23E, "_func_23E" }, // MP 0x1403295E0
    { 0x23F, "_func_23F" }, // SP 0x14023FCB0, MP 0x140322690
    { 0x240, "_func_240" }, // MP 0x140329600
    { 0x241, "_func_241" }, // MP 0x140329950
    { 0x242, "_func_242" }, // MP 0x1403299C0
    { 0x243, "_func_243" }, // MP 0x1403299D0
    { 0x244, "_func_244" }, // SP 0x14025D7C0
    { 0x245, "_func_245" }, // SP 0x140253C30, MP 0x14031A690
    { 0x246, "_func_246" }, // SP 0x14024F1E0, MP 0x1403163C0
    { 0x247, "_func_247" }, // SP 0x140252280, MP 0x140319020
    { 0x248, "_func_248" }, // SP 0x140260360
    { 0x249, "_func_249" }, // MP 0x14030B680
    { 0x24A, "_func_24A" }, // MP 0x14030B870
    { 0x24B, "_func_24B" }, // MP 0x14030B9D0
    { 0x24C, "_func_24C" }, // SP 0x1402531C0, MP 0x140319F60
    { 0x24D, "_func_24D" }, // SP 0x140253500, MP 0x140319FC0
    { 0x24E, "_func_24E" }, // SP 0x1402539F0, MP 0x14031A250
    { 0x24F, "_func_24F" }, // MP 0x140338900
    { 0x250, "_func_250" }, // SP 0x140259FA0
    { 0x251, "_func_251" }, // SP 0x140249700, MP 0x140310B20
    { 0x252, "_func_252" }, // SP 0x140240DE0, MP 0x14030CBF0
    { 0x253, "_func_253" }, // SP 0x140240E00, MP 0x14030CE90
    { 0x254, "_func_254" }, // SP 0x140241180, MP 0x14030D000
    { 0x255, "_func_255" }, // SP 0x140241330, MP 0x14030D2A0
    { 0x256, "_func_256" }, // SP 0x140241560, MP 0x14030D650
    { 0x257, "_func_257" }, // SP 0x140241970, MP 0x14030D8E0
    { 0x258, "_func_258" }, // SP 0x140241A70, MP 0x14030E070
    { 0x259, "_func_259" }, // SP 0x140241E30, MP 0x14030E4C0
    { 0x25A, "_func_25A" }, // SP 0x140241F40, MP 0x14030E7B0
    { 0x25B, "_func_25B" }, // SP 0x140242270, MP 0x14030EAC0
    { 0x25C, "_func_25C" }, // SP 0x1402425F0, MP 0x14030EED0
    { 0x25D, "_func_25D" }, // SP 0x140242960, MP 0x14030F280
    { 0x25E, "_func_25E" }, // SP 0x140242C80, MP 0x14030F640
    { 0x25F, "_func_25F" }, // SP 0x1402430E0, MP 0x14030F990
    { 0x260, "_func_260" }, // MP 0x14030FA20
    { 0x261, "_func_261" }, // MP 0x14032BC00
    { 0x262, "_func_262" }, // MP 0x14030FD60
    { 0x263, "_func_263" }, // MP 0x14030FDB0
    { 0x264, "_func_264" }, // MP 0x14030FF50
    { 0x265, "_func_265" }, // MP 0x140310030
    { 0x266, "_func_266" }, // MP 0x140310040
    { 0x267, "_func_267" }, // MP 0x1403101C0
    { 0x268, "_func_268" }, // MP 0x140328750
    { 0x269, "_func_269" }, // empty
    { 0x26A, "_func_26A" }, // empty
    { 0x26B, "_func_26B" }, // MP 0x140310250
    { 0x26C, "_func_26C" }, // MP 0x140310260
    { 0x26D, "_func_26D" }, // MP 0x140310360
    { 0x26E, "_func_26E" }, // MP 0x140310480
    { 0x26F, "_func_26F" }, // MP 0x14032C3B0
    { 0x270, "_func_270" }, // empty
    { 0x271, "_func_271" }, // MP 0x140433260
    { 0x272, "_func_272" }, // MP 0x1403328E0
    { 0x273, "_func_273" }, // MP 0x140433220
    { 0x274, "_func_274" }, // MP 0x14030F630
    { 0x275, "_func_275" }, // MP 0x1402F05B0
    { 0x276, "_func_276" }, // MP 0x14030C470
    { 0x277, "_func_277" }, // MP 0x14030C480
    { 0x278, "_func_278" }, // MP 0x14030BA90
    { 0x279, "_func_279" }, // SP 0x1402476E0, MP 0x140310920
    { 0x27A, "_func_27A" }, // MP 0x14032C4A0
    { 0x27B, "_func_27B" }, // MP 0x14032C4B0
    { 0x27C, "_func_27C" }, // MP 0x14032C4D0
    { 0x27D, "_func_27D" }, // MP 0x14032C840
    { 0x27E, "_func_27E" }, // MP 0x14032CAB0
    { 0x27F, "_func_27F" }, // MP 0x14030BB00
    { 0x280, "_func_280" }, // MP 0x14032F7E0
    { 0x281, "_func_281" }, // MP 0x14032E600
    { 0x282, "_func_282" }, // MP 0x140310EC0
    { 0x283, "_func_283" }, // SP 0x14023EC00, MP 0x14031BAE0
    { 0x284, "_func_284" }, // SP 0x14023F300, MP 0x14031C2B0
    { 0x285, "_func_285" }, // MP 0x140043610
    { 0x286, "istestclient" },
    { 0x287, "_func_287" }, // MP 0x1402D2850
    { 0x288, "_func_288" }, // MP 0x14032F0C0
    { 0x289, "_func_289" }, // SP 0x1402471A0, MP 0x140311FF0
    { 0x28A, "_func_28A" }, // SP 0x1402471E0, MP 0x140312040
    { 0x28B, "_func_28B" }, // SP 0x140259CC0
    { 0x28C, "_func_28C" }, // SP 0x140244780, MP 0x140311100
    { 0x28D, "_func_28D" }, // SP 0x140247F80, MP 0x140314C70
    { 0x28E, "_func_28E" }, // SP 0x140244530, MP 0x14030D340
    { 0x28F, "_func_28F" }, // SP 0x1402453C0, MP 0x14030DA60
    { 0x290, "_func_290" }, // SP 0x140245780, MP 0x14030E5C0
    { 0x291, "_func_291" }, // SP 0x1402601E0
    { 0x292, "_func_292" }, // MP 0x14031FDA0
    { 0x293, "_func_293" }, // SP 0x1402503F0, MP 0x140317140
    { 0x294, "_func_294" }, // SP 0x140246AD0, MP 0x14030FD70
    { 0x295, "_func_295" }, // SP 0x140246F20, MP 0x140310210
    { 0x296, "_func_296" }, // SP 0x140247200, MP 0x140310370
    { 0x297, "_func_297" }, // MP 0x14032FBA0
    { 0x298, "_func_298" }, // MP 0x14032FCA0
    { 0x299, "_func_299" }, // SP 0x140246B10, MP 0x14030E700
    { 0x29A, "_func_29A" }, // SP 0x1402603C0
    { 0x29B, "_func_29B" }, // SP 0x14024CE40, MP 0x140316070
    { 0x29C, "_func_29C" }, // MP 0x14031FC20
    { 0x29D, "_func_29D" }, // SP 0x14024A520, MP 0x140318030
    { 0x29E, "_func_29E" }, // MP 0x140318A90
    { 0x29F, "_func_29F" }, // MP 0x140318560
    { 0x2A0, "_func_2A0" }, // MP 0x140328F10
    { 0x2A1, "_func_2A1" }, // SP 0x14025A630
    { 0x2A2, "_func_2A2" }, // SP 0x140243B50, MP 0x14030CA90
    { 0x2A3, "_func_2A3" }, // SP 0x14024B760, MP 0x1403199C0
    { 0x2A4, "_func_2A4" }, // SP 0x14024AB20, MP 0x140319680
    { 0x2A5, "_func_2A5" }, // SP 0x14024B670, MP 0x1403199A0
    { 0x2A6, "_func_2A6" }, // SP 0x14024B710, MP 0x1403199B0
    { 0x2A7, "_func_2A7" }, // SP 0x14024B850, MP 0x140319A20
    { 0x2A8, "_func_2A8" }, // MP 0x14032D2A0
    { 0x2A9, "_func_2A9" }, // MP 0x14032D300
    { 0x2AA, "_func_2AA" }, // MP 0x14032D340
    { 0x2AB, "_func_2AB" }, // MP 0x14032D780
    { 0x2AC, "_func_2AC" }, // MP 0x14031CA40
    { 0x2AD, "_func_2AD" }, // MP 0x14031E1F0
    { 0x2AE, "_func_2AE" }, // SP 0x14023E7F0, MP 0x140321880
    { 0x2AF, "_func_2AF" }, // SP 0x14025CCA0
    { 0x2B0, "_func_2B0" }, // MP 0x140329610
    { 0x2B1, "_func_2B1" }, // MP 0x1403297B0
    { 0x2B2, "_func_2B2" }, // MP 0x1403298D0
    { 0x2B3, "_func_2B3" }, // MP 0x14032ACF0
    { 0x2B4, "_func_2B4" }, // SP 0x14024EAD0, MP 0x140317DF0
    { 0x2B5, "_func_2B5" }, // SP 0x14025CCF0
    { 0x2B6, "_func_2B6" }, // SP 0x140245730, MP 0x14030E570
    { 0x2B7, "_func_2B7" }, // MP 0x140337920
    { 0x2B8, "_func_2B8" }, // SP 0x14024BB40, MP 0x140319B40
    { 0x2B9, "_func_2B9" }, // SP 0x14024BC90, MP 0x140319B50
    { 0x2BA, "_func_2BA" }, // SP 0x14023ED90, MP 0x140321AE0
    { 0x2BB, "_func_2BB" }, // SP 0x14024B7C0, MP 0x140314A40
    { 0x2BC, "_func_2BC" }, // MP 0x140314C30
    { 0x2BD, "_func_2BD" }, // SP 0x14025CF50
    { 0x2BE, "_func_2BE" }, // MP 0x14032AEA0
    { 0x2BF, "_func_2BF" }, // MP 0x1402D3540
    { 0x2C0, "_func_2C0" }, // MP 0x1402D35B0
    { 0x2C1, "_func_2C1" }, // MP 0x140332A70
    { 0x2C2, "_func_2C2" }, // MP 0x140332AE0
    { 0x2C3, "_func_2C3" }, // MP 0x14032C580
    { 0x2C4, "_func_2C4" }, // MP 0x14032C650
    { 0x2C5, "_func_2C5" }, // MP 0x14032C820
    { 0x2C6, "_func_2C6" }, // SP 0x14025C2C0
    { 0x2C7, "_func_2C7" }, // MP 0x14032C2A0
    { 0x2C8, "_func_2C8" }, // MP 0x1402D34D0
    { 0x2C9, "_func_2C9" }, // MP 0x1402D33F0
    { 0x2CA, "_func_2CA" }, // MP 0x14032DAD0
    { 0x2CB, "_func_2CB" }, // MP 0x14032DC40
    { 0x2CC, "_func_2CC" }, // SP 0x14025C4B0
    { 0x2CD, "_func_2CD" }, // SP 0x14024A6B0, MP 0x140318270
    { 0x2CE, "_func_2CE" }, // MP 0x14032C6B0
    { 0x2CF, "_func_2CF" }, // MP 0x140318AD0
    { 0x2D0, "_func_2D0" }, // SP 0x140260350
    { 0x2D1, "_func_2D1" }, // MP 0x1402D3460
    { 0x2D2, "_func_2D2" }, // SP 0x14025CFA0
    { 0x2D3, "_func_2D3" }, // MP 0x14032C2D0
    { 0x2D4, "_func_2D4" }, // MP 0x140332620
    { 0x2D5, "_func_2D5" }, // MP 0x140332610
    { 0x2D6, "_func_2D6" }, // MP 0x1402D3630
    { 0x2D7, "_func_2D7" }, // MP 0x14031AA80
    { 0x2D8, "_func_2D8" }, // SP 0x140240AD0, MP 0x14031EAD0
    { 0x2D9, "_func_2D9" }, // MP 0x140328010
    { 0x2DA, "_func_2DA" }, // MP 0x14031B670
    { 0x2DB, "_func_2DB" }, // MP 0x14031D3F0
    { 0x2DC, "_func_2DC" }, // MP 0x14031E670
    { 0x2DD, "_func_2DD" }, // MP 0x140339100
    { 0x2DE, "_func_2DE" }, // MP 0x140319200
    { 0x2DF, "_func_2DF" }, // MP 0x140331E00
}};

} // namespace xsk::gsc::s1_pc
