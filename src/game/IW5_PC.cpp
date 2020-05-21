#include "stdinc.hpp"

std::unordered_map < std::uint8_t, std::string > opcode_map =
{
	{ OP_End, "end" },
	{ OP_Return, "retn" },
	{ OP_GetByte, "get_byte" },
	{ OP_GetNegByte, "get_neg_byte" },
	{ OP_GetUnsignedShort, "get_ushort" },
	{ OP_GetNegUnsignedShort, "get_neg_ushort" },
	{ OP_GetInteger, "get_int" },
	{ OP_GetBuiltinFunction, "get_builtin_func" },
	{ OP_GetBuiltinMethod, "get_builtin_method" },
	{ OP_GetFloat, "get_float" },
	{ OP_GetString, "get_string" },
	{ OP_GetUndefined, "get_undefined" },
	{ OP_GetZero, "get_zero" },
	{ OP_waittillFrameEnd, "waittillFrameEnd" },
	{ OP_CreateLocalVariable, "create_local_variable" },
	{ OP_RemoveLocalVariables, "remove_local_variables" },
	{ OP_EvalLocalVariableCached0, "eval_local_variable_cached0" },
	{ OP_EvalLocalVariableCached1, "eval_local_variable_cached1" },
	{ OP_EvalLocalVariableCached2, "eval_local_variable_cached2" },
	{ OP_EvalLocalVariableCached3, "eval_local_variable_cached3" },
	{ OP_EvalLocalVariableCached4, "eval_local_variable_cached4" },
	{ OP_EvalLocalVariableCached5, "eval_local_variable_cached5" },
	{ OP_EvalLocalVariableCached, "eval_local_variable_cached" },
	{ OP_EvalLocalArrayCached, "eval_local_array_cached" },
	{ OP_EvalArray, "eval_array" },
	{ OP_EvalNewLocalArrayRefCached0, "eval_new_local_array_ref_cached0" },
	{ OP_EvalLocalArrayRefCached0, "eval_local_array_ref_cached0" },
	{ OP_EvalLocalArrayRefCached, "eval_local_array_ref_cached" },
	{ OP_EvalArrayRef, "eval_array_ref" },
	{ OP_ClearArray, "clear_array" },
	{ OP_EmptyArray, "empty_array" },
	{ OP_AddArray, "add_array" },
	{ OP_PreScriptCall, "pre_script_call" },
	{ OP_ScriptLocalFunctionCall2, "script_local_func_call2" },
	{ OP_ScriptLocalFunctionCall, "script_local_func_call" },
	{ OP_ScriptLocalMethodCall, "script_local_method_call" },
	{ OP_ScriptLocalThreadCall, "script_local_thread_call" },
	{ OP_ScriptLocalChildThreadCall, "script_local_child_thread_call" },
	{ OP_ScriptLocalMethodThreadCall, "script_local_method_thread_call" },
	{ OP_ScriptLocalMethodChildThreadCall, "script_local_method_child_thread_call" },
	{ OP_ScriptFarFunctionCall2, "script_far_func_call2" },
	{ OP_ScriptFarFunctionCall, "script_far_func_call" },
	{ OP_ScriptFarMethodCall, "script_far_method_call" },
	{ OP_ScriptFarThreadCall, "script_far_thread_call" },
	{ OP_ScriptFarChildThreadCall, "script_far_child_thread_call" },
	{ OP_ScriptFarMethodThreadCall, "script_far_method_thread_call" },
	{ OP_ScriptFarMethodChildThreadCall, "script_far_method_child_thread_call" },
	{ OP_ScriptFunctionCallPointer, "script_func_call_pointer" },
	{ OP_ScriptMethodCallPointer, "script_method_call_pointer" },
	{ OP_ScriptThreadCallPointer, "script_thread_call_pointer" },
	{ OP_ScriptMethodChildThreadCallPointer, "script_method_child_thread_call_pointer" }, // its not exactly the same
	{ OP_ScriptMethodThreadCallPointer, "script_method_thread_call_pointer" },
	{ OP_ScriptMethodChildThreadCallPointer, "script_method_child_thread_call_pointer" },
	{ OP_CallBuiltinPointer, "call_builtin_pointer" },
	{ OP_CallBuiltinMethodPointer, "call_builtin_method_pointer" },
	{ OP_GetIString, "get_istring" },
	{ OP_GetVector, "get_vector" },
	{ OP_GetLevelObject, "get_level_obj" },
	{ OP_GetAnimObject, "get_anim_obj" },
	{ OP_GetSelf, "get_self" },
	{ OP_GetThisthread, "get_this_thread" },
	{ OP_GetLevel, "get_level" },
	{ OP_GetGame, "get_game" },
	{ OP_GetAnim, "get_anim" },
	{ OP_GetAnimation, "get_animation" },
	{ OP_GetGameRef, "get_game_ref" },
	{ OP_inc, "increment" },
	{ OP_dec, "decrement" },
	{ OP_bit_or, "bit_or" },
	{ OP_JumpOnFalseExpr, "jump_expr<false>" },
	{ OP_bit_ex_or, "bit_ex_or" },
	{ OP_bit_and, "bit_and" },
	{ OP_equality, "equality" },
	{ OP_inequality, "inequality" },
	{ OP_less, "less" },
	{ OP_greater, "greater" },
	{ OP_JumpOnTrueExpr, "jump_expr<true>" },
	{ OP_less_equal, "less_equal" },
	{ OP_jumpback, "jump_back" },
	{ OP_waittillmatch2, "waittillmatch2" },
	{ OP_waittill, "waittill" },
	{ OP_notify, "notify" },
	{ OP_endon, "endon" },
	{ OP_voidCodepos, "void_codepos" },
	{ OP_switch, "switch" },
	{ OP_endswitch, "endswitch" },
	{ OP_vector, "vector" },
	{ OP_JumpOnFalse, "jump<false>" },
	{ OP_greater_equal, "greater_equal" },
	{ OP_shift_left, "shift_left" },
	{ OP_shift_right, "shift_right" },
	{ OP_plus, "plus" },
	{ OP_jump, "jump" },
	{ OP_minus, "minus" },
	{ OP_multiply, "multiply" },
	{ OP_divide, "divide" },
	{ OP_mod, "mod" },
	{ OP_JumpOnTrue, "jump<true>" },
	{ OP_size, "size" },
	{ OP_waittillmatch, "waittillmatch" },
	{ OP_GetLocalFunction, "get_local_func" },
	{ OP_GetFarFunction, "get_far_func" },
	{ OP_GetSelfObject, "get_self_obj" },
	{ OP_EvalLevelFieldVariable, "eval_level_field_variable" },
	{ OP_EvalAnimFieldVariable, "eval_anim_field_variable" },
	{ OP_EvalSelfFieldVariable, "eval_self_field_variable" },
	{ OP_EvalFieldVariable, "eval_field_variable" },
	{ OP_EvalLevelFieldVariableRef, "eval_level_field_variable_ref" },
	{ OP_EvalAnimFieldVariableRef, "eval_anim_field_variable_ref" },
	{ OP_EvalSelfFieldVariableRef, "eval_self_field_variable_ref" },
	{ OP_EvalFieldVariableRef, "eval_field_variable_ref" },
	{ OP_ClearFieldVariable, "clear_field_variable" },
	{ OP_SafeCreateVariableFieldCached, "safe_create_variable_field_cached" },
	{ OP_SafeSetVariableFieldCached0, "safe_set_variable_field_cached0" },
	{ OP_SafeSetVariableFieldCached, "safe_set_variable_field_cached" },
	{ OP_SafeSetWaittillVariableFieldCached, "safe_set_waittill_variable_field_cached" },
	{ OP_GetAnimTree, "get_animtree" },
	{ OP_clearparams, "clearparams" },
	{ OP_checkclearparams, "checkclearparams" },
	{ OP_EvalLocalVariableRefCached0, "eval_local_variable_ref_cached0" },
	{ OP_EvalNewLocalVariableRefCached0, "eval_new_local_variable_ref_cached0" },
	{ OP_EvalLocalVariableRefCached, "eval_local_variable_ref_cached" },
	{ OP_SetLevelFieldVariableField, "set_level_field_variable_field" },
	{ OP_SetVariableField, "set_variable_field" },
	{ OP_ClearVariableField, "clear_variable_field" },
	{ OP_SetAnimFieldVariableField, "set_anim_field_vaiable_field" },
	{ OP_SetSelfFieldVariableField, "set_self_field_vaiable_field" },
	{ OP_SetLocalVariableFieldCached0, "set_local_variable_field_cached0" },
	{ OP_SetNewLocalVariableFieldCached0, "set_new_local_variable_field_cached0" },
	{ OP_SetLocalVariableFieldCached, "set_local_variable_field_cached" },
	{ OP_ClearLocalVariableFieldCached, "clear_local_variable_field_cached" },
	{ OP_ClearLocalVariableFieldCached0, "clear_local_variable_field_cached0" },
	{ OP_CallBuiltin0, "call<0>" },
	{ OP_CallBuiltin1, "call<1>" },
	{ OP_CallBuiltin2, "call<2>" },
	{ OP_CallBuiltin3, "call<3>" },
	{ OP_CallBuiltin4, "call<4>" },
	{ OP_CallBuiltin5, "call<5>" },
	{ OP_CallBuiltin, "call" },
	{ OP_CallBuiltinMethod0, "method<0>" },
	{ OP_CallBuiltinMethod1, "method<1>" },
	{ OP_CallBuiltinMethod2, "method<2>" },
	{ OP_CallBuiltinMethod3, "method<3>" },
	{ OP_CallBuiltinMethod4, "method<4>" },
	{ OP_CallBuiltinMethod5, "method<5>" },
	{ OP_CallBuiltinMethod, "method" },
	{ OP_wait, "wait" },
	{ OP_DecTop, "decrement_top" },
	{ OP_CastFieldObject, "cast_field_obj" },
	{ OP_EvalLocalVariableObjectCached, "eval_local_variable_obj_cached" },
	{ OP_CastBool, "cast_bool" },
	{ OP_BoolNot, "bool_not" },
	{ OP_BoolComplement, "bool_complement" },
};

std::unordered_map < std::uint16_t, std::string > builtin_func_map =
{
	{ 1, "getweaponindexforname" },
	{ 2, "target_getarray" },
	{ 3, "ban" },
	{ 14, "setprintchannel" },
	{ 15, "print" },
	{ 16, "println" },
	{ 17, "print3d" },
	{ 18, "line" },
	{ 19, "spawnturret" },
	{ 20, "canspawnturret" },
	{ 21, "assert" },
	{ 38, "assertex" },
	{ 39, "assertmsg" },
	{ 40, "isdefined" },
	{ 41, "isstring" },
	{ 42, "setdvar" },
	{ 43, "setdynamicdvar" },
	{ 44, "setdvarifuninitialized" },
	{ 45, "setdevdvar" },
	{ 46, "setdevdvarifuninitialized" },
	{ 47, "getdvar" },
	{ 48, "getdvarint" },
	{ 49, "getdvarfloat" },
	{ 50, "getdvarvector" },
	{ 51, "gettime" },
	{ 52, "getentbynum" },
	{ 53, "getweaponmodel" },
	{ 57, "setsunlight" },
	{ 58, "resetsunlight" },
	{ 81, "getweaponhidetags" },
	{ 82, "getanimlength" },
	{ 83, "animhasnotetrack" },
	{ 84, "getnotetracktimes" },
	{ 85, "spawn" },
	{ 86, "spawnloopsound" },
	{ 87, "paramerror" },
	{ 88, "bullettrace" },
	{ 116, "sighttracepassed" },
	{ 117, "physicstrace" },
	{ 118, "physicstracenormal" },
	{ 119, "playerphysicstrace" },
	{ 120, "getgroundposition" },
	{ 121, "getmovedelta" },
	{ 122, "getangledelta" },
	{ 123, "getnorthyaw" },
	{ 150, "setnorthyaw" },
	{ 151, "setslowmotion" },
	{ 152, "randomint" },
	{ 153, "randomfloat" },
	{ 154, "randomintrange" },
	{ 155, "randomfloatrange" },
	{ 156, "sin" },
	{ 157, "cos" },
	{ 158, "tan" },
	{ 159, "asin" },
	{ 160, "acos" },
	{ 161, "atan" },
	{ 162, "castint" },
	{ 163, "castfloat" },
	{ 164, "abs" },
	{ 165, "min" },
	{ 198, "max" },
	{ 199, "floor" },
	{ 200, "ceil" },
	{ 201, "exp" },
	{ 202, "log" },
	{ 203, "sqrt" },
	{ 204, "squared" },
	{ 205, "clamp" },
	{ 206, "angleclamp" },
	{ 207, "angleclamp180" },
	{ 208, "vectorfromlinetopoint" },
	{ 209, "pointonsegmentnearesttopoint" },
	{ 210, "distance" },
	{ 211, "distance2d" },
	{ 212, "distancesquared" },
	{ 213, "length" },
	{ 214, "lengthsquared" },
	{ 215, "closer" },
	{ 216, "vectordot" },
	{ 217, "visionsetthermal" },
	{ 218, "visionsetpain" },
	{ 219, "endlobby" },
	{ 220, "setac130ambience" },
	{ 221, "getmapcustom" },
	{ 222, "updateskill" },
	{ 223, "spawnsighttrace" },
	{ 224, "incrementcounter" },
	{ 225, "getcountertotal" },
	{ 246, "vectornormalize" },
	{ 247, "vectortoangles" },
	{ 248, "vectortoyaw" },
	{ 249, "vectorlerp" },
	{ 250, "anglestoup" },
	{ 251, "anglestoright" },
	{ 252, "anglestoforward" },
	{ 253, "combineangles" },
	{ 254, "transformmove" },
	{ 255, "issubstr" },
	{ 256, "isendstr" },
	{ 257, "getsubstr" },
	{ 258, "tolower" },
	{ 259, "strtok" },
	{ 260, "stricmp" },
	{ 261, "ambientplay" },
	{ 262, "getuavstrengthmax" },
	{ 263, "getuavstrengthlevelneutral" },
	{ 264, "getuavstrengthlevelshowenemyfastsweep" },
	{ 265, "getuavstrengthlevelshowenemydirectional" },
	{ 266, "blockteamradar" },
	{ 267, "unblockteamradar" },
	{ 268, "isteamradarblocked" },
	{ 269, "getassignedteam" },
	{ 270, "setmatchdata" },
	{ 271, "getmatchdata" },
	{ 272, "sendmatchdata" },
	{ 273, "clearmatchdata" },
	{ 274, "setmatchdatadef" },
	{ 275, "setmatchclientip" },
	{ 276, "setmatchdataid" },
	{ 277, "setclientmatchdata" },
	{ 278, "getclientmatchdata" },
	{ 279, "setclientmatchdatadef" },
	{ 280, "sendclientmatchdata" },
	{ 281, "getbuildversion" },
	{ 282, "getbuildnumber" },
	{ 283, "getsystemtime" },
	{ 284, "getmatchrulesdata" },
	{ 285, "isusingmatchrulesdata" },
	{ 286, "kick" },
	{ 287, "issplitscreen" },
	{ 288, "setmapcenter" },
	{ 289, "setgameendtime" },
	{ 290, "visionsetnaked" },
	{ 291, "visionsetnight" },
	{ 292, "visionsetmissilecam" },
	{ 293, "ambientstop" },
	{ 294, "precachemodel" },
	{ 295, "precacheshellshock" },
	{ 296, "precacheitem" },
	{ 297, "precacheshader" },
	{ 298, "precachestring" },
	{ 299, "precachemenu" },
	{ 300, "precacherumble" },
	{ 301, "precachelocationselector" },
	{ 302, "precacheleaderboards" },
	{ 303, "loadfx" },
	{ 304, "playfx" },
	{ 305, "playfxontag" },
	{ 306, "stopfxontag" },
	{ 307, "playloopedfx" },
	{ 308, "spawnfx" },
	{ 309, "triggerfx" },
	{ 310, "playfxontagforclients" },
	{ 311, "setwinningteam" },
	{ 312, "announcement" },
	{ 313, "clientannouncement" },
	{ 314, "getteamscore" },
	{ 315, "setteamscore" },
	{ 316, "setclientnamemode" },
	{ 317, "updateclientnames" },
	{ 318, "getteamplayersalive" },
	{ 319, "logprint" },
	{ 320, "worldentnumber" },
	{ 321, "obituary" },
	{ 322, "positionwouldtelefrag" },
	{ 323, "canspawn" },
	{ 324, "getstarttime" },
	{ 325, "precachestatusicon" },
	{ 326, "precacheheadicon" },
	{ 327, "precacheminimapicon" },
	{ 328, "precachempanim" },
	{ 329, "map_restart" },
	{ 330, "exitlevel" },
	{ 331, "addtestclient" },
	{ 332, "makedvarserverinfo" },
	{ 333, "setarchive" },
	{ 334, "allclientsprint" },
	{ 335, "clientprint" },
	{ 336, "mapexists" },
	{ 337, "isvalidgametype" },
	{ 338, "matchend" },
	{ 339, "setplayerteamrank" },
	{ 340, "endparty" },
	{ 341, "setteamradar" },
	{ 342, "getteamradar" },
	{ 343, "setteamradarstrength" },
	{ 344, "getteamradarstrength" },
	{ 345, "getuavstrengthmin" },
	{ 346, "physicsexplosionsphere" },
	{ 347, "physicsexplosioncylinder" },
	{ 348, "physicsjolt" },
	{ 349, "physicsjitter" },
	{ 350, "setexpfog" },
	{ 351, "isexplosivedamagemod" },
	{ 352, "radiusdamage" },
	{ 353, "setplayerignoreradiusdamage" },
	{ 354, "glassradiusdamage" },
	{ 355, "earthquake" },
	{ 356, "getnumparts" },
	{ 357, "objective_onentity" },
	{ 358, "objective_team" },
	{ 359, "objective_player" },
	{ 360, "objective_playerteam" },
	{ 361, "objective_playerenemyteam" },
	{ 362, "iprintln" },
	{ 363, "iprintlnbold" },
	{ 364, "logstring_0" },
	{ 365, "getent" },
	{ 366, "getentarray" },
	{ 367, "spawnplane" },
	{ 368, "spawnstruct" },
	{ 369, "spawnhelicopter" },
	{ 370, "isalive" },
	{ 371, "isvehicle" },
	{ 372, "createattractorent" },
	{ 373, "createattractororigin" },
	{ 374, "createrepulsorent" },
	{ 375, "createrepulsororigin" },
	{ 376, "deleteattractor" },
	{ 377, "playsoundatpos" },
	{ 378, "newhudelem" },
	{ 379, "newclienthudelem" },
	{ 380, "newteamhudelem" },
	{ 381, "resettimeout" },
	{ 382, "precachefxteamthermal" },
	{ 383, "isplayer" },
	{ 384, "isplayernumber" },
	{ 385, "setwinningplayer" },
	{ 386, "getpartname" },
	{ 387, "weaponfiretime" },
	{ 388, "weaponclipsize" },
	{ 389, "weaponisauto" },
	{ 390, "weaponissemiauto" },
	{ 391, "weaponisboltaction" },
	{ 392, "weaponinheritsperks" },
	{ 393, "weaponburstcount" },
	{ 394, "weapontype" },
	{ 395, "weaponclass" },
	{ 396, "getnextarraykey" },
	{ 397, "sortbydistance" },
	{ 398, "tablelookup" },
	{ 399, "tablelookupbyrow" },
	{ 400, "tablelookupistring" },
	{ 401, "tablelookupistringbyrow" },
	{ 402, "tablelookuprownum" },
	{ 403, "getmissileowner" },
	{ 404, "magicbullet" },
	{ 405, "getweaponflashtagname" },
	{ 406, "averagepoint" },
	{ 407, "averagenormal" },
	{ 408, "vehicle_getspawnerarray" },
	{ 409, "playrumbleonposition" },
	{ 410, "playrumblelooponposition" },
	{ 411, "stopallrumbles" },
	{ 412, "soundexists" },
	{ 413, "openfile" },
	{ 414, "closefile" },
	{ 415, "fprintln" },
	{ 416, "fprintfields" },
	{ 417, "freadln" },
	{ 418, "fgetarg" },
	{ 419, "setminimap" },
	{ 420, "setthermalbodymaterial" },
	{ 421, "getarraykeys" },
	{ 422, "getfirstarraykey" },
	{ 423, "getglass" },
	{ 424, "getglassarray" },
	{ 425, "getglassorigin" },
	{ 426, "isglassdestroyed" },
	{ 427, "destroyglass" },
	{ 428, "deleteglass" },
	{ 429, "getentchannelscount" },
	{ 430, "getentchannelname" },
	{ 431, "objective_add" },
	{ 432, "objective_delete" },
	{ 433, "objective_state" },
	{ 434, "objective_icon" },
	{ 435, "objective_position" },
	{ 436, "objective_current" },
	{ 437, "weaponinventorytype" },
	{ 438, "weaponstartammo" },
	{ 439, "weaponmaxammo" },
	{ 440, "weaponaltweaponname" },
	{ 441, "isweaponcliponly" },
	{ 442, "isweapondetonationtimed" },
	{ 443, "weaponhasthermalscope" },
	{ 444, "getvehiclenode" },
	{ 445, "getvehiclenodearray" },
	{ 446, "getallvehiclenodes" },
	{ 447, "getnumvehicles" },
	{ 448, "precachevehicle" },
	{ 449, "spawnvehicle" },
	{ 450, "vehicle_getarray" },
};

std::unordered_map < std::uint16_t, std::string > builtin_method_map =
{
	{ 32768, "thermaldrawdisable" },
	{ 32770, "helicopter_setdamagestate" },
	{ 32771, "playsoundtoteam" },
	{ 32772, "playsoundtoplayer" },
	{ 32773, "playerhide" },
	{ 32774, "showtoplayer" },
	{ 32775, "enableplayeruse" },
	{ 32776, "disableplayeruse" },
	{ 32777, "makescrambler" },
	{ 32778, "makeportableradar" },
	{ 32779, "maketrophysystem" },
	{ 32780, "placespawnpoint" },
	{ 32781, "setteamfortrigger" },
	{ 32782, "clientclaimtrigger" },
	{ 32783, "clientreleasetrigger" },
	{ 32784, "releaseclaimedtrigger" },
	{ 32785, "isusingonlinedataoffline" },
	{ 32786, "getrestedtime" },
	{ 32787, "send73command_unk" },
	{ 32788, "isonladder" },
	{ 32789, "getcorpseanim" },
	{ 32790, "playerforcedeathanim" },
	{ 32791, "attach" },
	{ 32792, "attachshieldmodel" },
	{ 32798, "startragdoll" },
	{ 32800, "sendleaderboards" },
	{ 32803, "thermaldrawenable" },
	{ 32804, "detach" },
	{ 32805, "detachshieldmodel" },
	{ 32806, "moveshieldmodel" },
	{ 32807, "detachall" },
	{ 32808, "getattachsize" },
	{ 32809, "getattachmodelname" },
	{ 32810, "getattachtagname" },
	{ 32835, "getattachignorecollision" },
	{ 32836, "hidepart" },
	{ 32837, "hidepart_allinstances" },
	{ 32838, "hideallparts" },
	{ 32839, "showpart" },
	{ 32840, "showallparts" },
	{ 32841, "linkto" },
	{ 32842, "linktoblendtotag" },
	{ 32843, "unlink" },
	{ 32844, "setnormalhealth" },
	{ 32847, "show" },
	{ 32848, "hide" },
	{ 32864, "setmode" },
	{ 32865, "getmode" },
	{ 32867, "islinked" },
	{ 32868, "enablelinkto" },
	{ 32878, "playsoundasmaster" },
	{ 32879, "playloopsound" },
	{ 32884, "getnormalhealth" },
	{ 32885, "playerlinkto" },
	{ 32886, "playerlinktodelta" },
	{ 32887, "playerlinkweaponviewtodelta" },
	{ 32888, "playerlinktoabsolute" },
	{ 32889, "playerlinktoblend" },
	{ 32890, "playerlinkedoffsetenable" },
	{ 32891, "setwaypointedgestyle_secondaryarrow" },
	{ 32892, "setwaypointiconoffscreenonly" },
	{ 32893, "fadeovertime" },
	{ 32894, "scaleovertime" },
	{ 32895, "moveovertime" },
	{ 32896, "reset" },
	{ 32897, "destroy" },
	{ 32898, "setpulsefx" },
	{ 32899, "setplayernamestring" },
	{ 32900, "changefontscaleovertime" },
	{ 32910, "getorigin" },
	{ 32914, "useby" },
	{ 32915, "playsound" },
	{ 32916, "playerlinkedoffsetdisable" },
	{ 32917, "playerlinkedsetviewznear" },
	{ 32918, "playerlinkedsetusebaseangleforviewclamp" },
	{ 32919, "lerpviewangleclamp" },
	{ 32920, "setviewangleresistance" },
	{ 32921, "geteye" },
	{ 32922, "istouching" },
	{ 32923, "stoploopsound" },
	{ 32924, "stopsounds" },
	{ 32925, "playrumbleonentity" },
	{ 32926, "playrumblelooponentity" },
	{ 32927, "stoprumble" },
	{ 32928, "delete" },
	{ 32929, "setmodel" },
	{ 32930, "laseron" },
	{ 32931, "laseroff" },
	{ 32932, "laseraltviewon" },
	{ 32933, "laseraltviewoff" },
	{ 32934, "thermalvisionon" },
	{ 32935, "thermalvisionoff" },
	{ 32936, "thermalvisionfofoverlayon" },
	{ 32937, "thermalvisionfofoverlayoff" },
	{ 32938, "autospotoverlayon" },
	{ 32939, "autospotoverlayoff" },
	{ 32940, "setcontents" },
	{ 32941, "makeusable" },
	{ 32942, "makeunusable" },
	{ 32950, "settext" },
	{ 32951, "clearalltextafterhudelem" },
	{ 32952, "setshader" },
	{ 32953, "settargetent_hud" },
	{ 32954, "cleartargetent" },
	{ 32955, "settimer" },
	{ 32956, "settimerup" },
	{ 32957, "settimerstatic" },
	{ 32958, "settenthstimer" },
	{ 32959, "settenthstimerup" },
	{ 32960, "settenthstimerstatic" },
	{ 32961, "setclock" },
	{ 32962, "setclockup" },
	{ 32963, "setvalue" },
	{ 32964, "setwaypoint" },
	{ 32965, "setwaypointedgestyle_rotatingicon" },
	{ 32966, "setcursorhint" },
	{ 32967, "sethintstring" },
	{ 32968, "forceusehinton" },
	{ 32969, "forceusehintoff" },
	{ 32970, "makesoft" },
	{ 32971, "makehard" },
	{ 32972, "willneverchange" },
	{ 32973, "startfiring" },
	{ 32974, "stopfiring" },
	{ 32975, "isfiringturret" },
	{ 32976, "startbarrelspin" },
	{ 32977, "stopbarrelspin" },
	{ 32978, "getbarrelspinrate" },
	{ 32979, "remotecontrolturret" },
	{ 32980, "remotecontrolturretoff" },
	{ 32981, "shootturret" },
	{ 32982, "getturretowner" },
	{ 33006, "setsentryowner" },
	{ 33007, "setsentrycarrier" },
	{ 33008, "setturretminimapvisible" },
	{ 33009, "settargetentity" },
	{ 33010, "snaptotargetentity" },
	{ 33011, "cleartargetentity" },
	{ 33012, "getturrettarget" },
	{ 33013, "setplayerspread" },
	{ 33014, "setaispread" },
	{ 33015, "setsuppressiontime" },
	{ 33049, "setconvergencetime" },
	{ 33050, "setconvergenceheightpercent" },
	{ 33051, "setturretteam" },
	{ 33052, "maketurretsolid" },
	{ 33053, "maketurretoperable" },
	{ 33054, "maketurretinoperable" },
	{ 33082, "setturretaccuracy" },
	{ 33083, "setrightarc" },
	{ 33084, "setleftarc" },
	{ 33085, "settoparc" },
	{ 33086, "setbottomarc" },
	{ 33087, "setautorotationdelay" },
	{ 33088, "setdefaultdroppitch" },
	{ 33089, "restoredefaultdroppitch" },
	{ 33090, "turretfiredisable" },
	{ 33121, "turretfireenable" },
	{ 33122, "setturretmodechangewait" },
	{ 33123, "usetriggerrequirelookat" },
	{ 33124, "getstance" },
	{ 33125, "setstance" },
	{ 33126, "itemweaponsetammo" },
	{ 33127, "getammocount" },
	{ 33128, "gettagorigin" },
	{ 33129, "gettagangles" },
	{ 33130, "shellshock" },
	{ 33131, "stunplayer" },
	{ 33132, "stopshellshock" },
	{ 33133, "fadeoutshellshock" },
	{ 33134, "setdepthoffield" },
	{ 33135, "setviewmodeldepthoffield" },
	{ 33136, "setmotionblurmovescale" },
	{ 33168, "setmotionblurturnscale" },
	{ 33169, "setmotionblurzoomscale" },
	{ 33170, "viewkick" },
	{ 33171, "localtoworldcoords" },
	{ 33172, "getentitynumber" },
	{ 33173, "getentityvelocity" },
	{ 33174, "enablegrenadetouchdamage" },
	{ 33175, "disablegrenadetouchdamage" },
	{ 33176, "enableaimassist" },
	{ 33207, "disableaimassist" },
	{ 33208, "radiusdamage" },
	{ 33209, "detonate" },
	{ 33210, "damageconetrace" },
	{ 33211, "sightconetrace" },
	{ 33212, "settargetent" },
	{ 33213, "settargetpos" },
	{ 33214, "cleartarget" },
	{ 33215, "setflightmodedirect" },
	{ 33216, "setflightmodetop" },
	{ 33217, "getlightintensity" },
	{ 33218, "setlightintensity" },
	{ 33219, "isragdoll" },
	{ 33220, "setmovespeedscale" },
	{ 33221, "cameralinkto" },
	{ 33222, "cameraunlink" },
	{ 33251, "controlslinkto" },
	{ 33252, "controlsunlink" },
	{ 33253, "makevehiclesolidcapsule" },
	{ 33254, "makevehiclesolidsphere" },
	{ 33256, "remotecontrolvehicle" },
	{ 33257, "remotecontrolvehicleoff" },
	{ 33258, "isfiringvehicleturret" },
	{ 33259, "drivevehicleandcontrolturret" },
	{ 33260, "drivevehicleandcontrolturretoff" },
	{ 33261, "getplayersetting" },
	{ 33262, "getlocalplayerprofiledata" },
	{ 33263, "setlocalplayerprofiledata" },
	{ 33264, "remotecamerasoundscapeon" },
	{ 33265, "remotecamerasoundscapeoff" },
	{ 33266, "radarjamon" },
	{ 33267, "radarjamoff" },
	{ 33268, "setmotiontrackervisible" },
	{ 33269, "getmotiontrackervisible" },
	{ 33270, "worldpointinreticle_circle" },
	{ 33271, "getpointinbounds" },
	{ 33272, "transfermarkstonewscriptmodel" },
	{ 33273, "setwatersheeting" },
	{ 33274, "setweaponhudiconoverride" },
	{ 33275, "getweaponhudiconoverride" },
	{ 33276, "setempjammed" },
	{ 33277, "playersetexpfog" },
	{ 33278, "isitemunlocked" },
	{ 33279, "getplayerdata" },
	{ 33280, "vehicleturretcontroloff" },
	{ 33281, "isturretready" },
	{ 33282, "vehicledriveto" },
	{ 33283, "dospawn" },
	{ 33284, "isphysveh" },
	{ 33285, "phys_crash" },
	{ 33286, "phys_launch" },
	{ 33287, "phys_disablecrashing" },
	{ 33288, "phys_enablecrashing" },
	{ 33289, "phys_setspeed" },
	{ 33290, "phys_setconveyerbelt" },
	{ 33291, "freehelicopter" },
	{ 33306, "setplayerdata" },
	{ 33307, "trackerupdate" },
	{ 33308, "pingplayer" },
	{ 33309, "buttonpressed" },
	{ 33310, "sayall" },
	{ 33311, "sayteam" },
	{ 33312, "showscoreboard" },
	{ 33313, "setspawnweapon" },
	{ 33314, "dropitem" },
	{ 33315, "dropscavengerbag" },
	{ 33316, "setjitterparams" },
	{ 33317, "sethoverparams" },
	{ 33318, "joltbody" },
	{ 33319, "freevehicle" },
	{ 33320, "getwheelsurface" },
	{ 33321, "getvehicleowner" },
	{ 33322, "setvehiclelookattext" },
	{ 33323, "setvehicleteam" },
	{ 33324, "setneargoalnotifydist" },
	{ 33325, "setvehgoalpos" },
	{ 33326, "setgoalyaw" },
	{ 33327, "cleargoalyaw" },
	{ 33328, "settargetyaw" },
	{ 33329, "cleartargetyaw" },
	{ 33330, "helisetai" },
	{ 33331, "setturrettargetvec" },
	{ 33332, "setturrettargetent" },
	{ 33333, "clearturrettarget" },
	{ 33334, "canturretgettargetpoint" },
	{ 33335, "setlookatent" },
	{ 33336, "clearlookatent" },
	{ 33337, "setvehweapon" },
	{ 33338, "fireweapon" },
	{ 33339, "vehicleturretcontrolon" },
	{ 33340, "finishplayerdamage" },
	{ 33341, "suicide" },
	{ 33342, "closeingamemenu" },
	{ 33343, "iprintln" },
	{ 33344, "iprintlnbold" },
	{ 33345, "spawn" },
	{ 33346, "setentertime" },
	{ 33347, "cloneplayer" },
	{ 33348, "istalking" },
	{ 33349, "allowspectateteam" },
	{ 33350, "getguid" },
	{ 33351, "physicslaunchserver" },
	{ 33352, "physicslaunchserveritem" },
	{ 33353, "clonebrushmodeltoscriptmodel" },
	{ 33354, "scriptmodelplayanim" },
	{ 33355, "scriptmodelclearanim" },
	{ 33356, "vehicle_teleport" },
	{ 33357, "attachpath" },
	{ 33358, "getattachpos" },
	{ 33359, "startpath" },
	{ 33360, "setswitchnode" },
	{ 33361, "setwaitspeed" },
	{ 33362, "vehicle_finishdamage" },
	{ 33363, "setspeed" },
	{ 33364, "setspeedimmediate" },
	{ 33365, "vehicle_rotateyaw" },
	{ 33366, "getspeed" },
	{ 33367, "vehicle_getvelocity" },
	{ 33368, "getbodyvelocity" },
	{ 33369, "getsteering" },
	{ 33370, "getthrottle" },
	{ 33371, "turnengineoff" },
	{ 33372, "turnengineon" },
	{ 33373, "getgoalspeedmph" },
	{ 33374, "setacceleration" },
	{ 33375, "setdeceleration" },
	{ 33376, "resumespeed" },
	{ 33377, "setyawspeed" },
	{ 33378, "setyawspeedbyname" },
	{ 33379, "setmaxpitchroll" },
	{ 33380, "setairresistance" },
	{ 33381, "setturningability" },
	{ 33382, "getxuid" },
	{ 33383, "ishost" },
	{ 33384, "getspectatingplayer" },
	{ 33385, "predictstreampos" },
	{ 33386, "updatescores" },
	{ 33387, "updatedmscores" },
	{ 33388, "setrank" },
	{ 33389, "setcardtitle" },
	{ 33390, "weaponlocknoclearance" },
	{ 33391, "visionsyncwithplayer" },
	{ 33392, "showhudsplash" },
	{ 33393, "setperk" },
	{ 33394, "hasperk" },
	{ 33395, "clearperks" },
	{ 33396, "unsetperk" },
	{ 33397, "noclip" },
	{ 33398, "ufo" },
	{ 33399, "moveto" },
	{ 33400, "movex" },
	{ 33401, "movey" },
	{ 33402, "movez" },
	{ 33403, "movegravity" },
	{ 33404, "moveslide" },
	{ 33405, "stopmoveslide" },
	{ 33406, "rotateto" },
	{ 33407, "rotatepitch" },
	{ 33408, "rotateyaw" },
	{ 33409, "rotateroll" },
	{ 33410, "addpitch" },
	{ 33411, "addyaw" },
	{ 33412, "addroll" },
	{ 33413, "vibrate" },
	{ 33414, "rotatevelocity" },
	{ 33415, "solid" },
	{ 33416, "notsolid" },
	{ 33417, "setcandamage" },
	{ 33418, "setcanradiusdamage" },
	{ 33419, "physicslaunchclient" },
	{ 33420, "setcardicon" },
	{ 33421, "setcardnameplate" },
	{ 33422, "setcarddisplayslot" },
	{ 33423, "regweaponforfxremoval" },
	{ 33424, "laststandrevive" },
	{ 33425, "setspectatedefaults" },
	{ 33426, "getthirdpersoncrosshairoffset" },
	{ 33427, "disableweaponpickup" },
	{ 33428, "enableweaponpickup" },
	{ 33429, "issplitscreenplayer" },
	{ 33430, "getweaponslistoffhands" },
	{ 33431, "getweaponslistitems" },
	{ 33432, "getweaponslistexclusives" },
	{ 33433, "getweaponslist" },
	{ 33434, "canplayerplacesentry" },
	{ 33435, "canplayerplacetank" },
	{ 33436, "visionsetnakedforplayer" },
	{ 33437, "visionsetnightforplayer" },
	{ 33438, "visionsetmissilecamforplayer" },
	{ 33439, "visionsetthermalforplayer" },
	{ 33440, "visionsetpainforplayer" },
	{ 33441, "setblurforplayer" },
	{ 33442, "getplayerweaponmodel" },
	{ 33443, "getplayerknifemodel" },
	{ 33444, "updateplayermodelwithweapons" },
	{ 33445, "notifyonplayercommand" },
	{ 33446, "canmantle" },
	{ 33447, "forcemantle" },
	{ 33448, "ismantling" },
	{ 33449, "playfx" },
	{ 33450, "player_recoilscaleon" },
	{ 33451, "player_recoilscaleoff" },
	{ 33452, "weaponlockstart" },
	{ 33453, "weaponlockfinalize" },
	{ 33454, "weaponlockfree" },
	{ 33455, "weaponlocktargettooclose" },
	{ 33456, "issplitscreenplayerprimary" },
	{ 33457, "getviewmodel" },
	{ 33458, "fragbuttonpressed" },
	{ 33459, "secondaryoffhandbuttonpressed" },
	{ 33460, "getcurrentweaponclipammo" },
	{ 33461, "setvelocity" },
	{ 33462, "getplayerviewheight" },
	{ 33463, "getnormalizedmovement" },
	{ 33464, "setchannelvolumes" },
	{ 33465, "deactivatechannelvolumes" },
	{ 33466, "playlocalsound" },
	{ 33467, "stoplocalsound" },
	{ 33468, "setweaponammoclip" },
	{ 33469, "setweaponammostock" },
	{ 33470, "getweaponammoclip" },
	{ 33471, "getweaponammostock" },
	{ 33472, "anyammoforweaponmodes" },
	{ 33473, "setclientdvar" },
	{ 33474, "setclientdvars" },
	{ 33475, "allowads" },
	{ 33476, "allowjump" },
	{ 33477, "allowsprint" },
	{ 33478, "setspreadoverride" },
	{ 33479, "resetspreadoverride" },
	{ 33480, "setaimspreadmovementscale" },
	{ 33481, "setactionslot" },
	{ 33482, "setviewkickscale" },
	{ 33483, "getviewkickscale" },
	{ 33484, "getweaponslistall" },
	{ 33485, "getweaponslistprimaries" },
	{ 33486, "getnormalizedcameramovement" },
	{ 33487, "giveweapon" },
	{ 33488, "takeweapon" },
	{ 33489, "takeallweapons" },
	{ 33490, "getcurrentweapon" },
	{ 33491, "getcurrentprimaryweapon" },
	{ 33492, "getcurrentoffhand" },
	{ 33493, "hasweapon" },
	{ 33494, "switchtoweapon" },
	{ 33495, "switchtoweaponimmediate" },
	{ 33496, "switchtooffhand" },
	{ 33497, "setoffhandsecondaryclass" },
	{ 33498, "getoffhandsecondaryclass" },
	{ 33499, "beginlocationselection" },
	{ 33500, "endlocationselection" },
	{ 33501, "disableweapons" },
	{ 33502, "enableweapons" },
	{ 33503, "disableoffhandweapons" },
	{ 33504, "enableoffhandweapons" },
	{ 33505, "disableweaponswitch" },
	{ 33506, "enableweaponswitch" },
	{ 33507, "openpopupmenu" },
	{ 33508, "openpopupmenunomouse" },
	{ 33509, "closepopupmenu" },
	{ 33510, "openmenu" },
	{ 33511, "closemenu" },
	{ 33513, "freezecontrols" },
	{ 33514, "disableusability" },
	{ 33515, "enableusability" },
	{ 33516, "setwhizbyspreads" },
	{ 33517, "setwhizbyradii" },
	{ 33518, "setreverb" },
	{ 33519, "deactivatereverb" },
	{ 33520, "setvolmod" },
	{ 33521, "setchannelvolume" },
	{ 33522, "givestartammo" },
	{ 33523, "givemaxammo" },
	{ 33524, "getfractionstartammo" },
	{ 33525, "getfractionmaxammo" },
	{ 33526, "isdualwielding" },
	{ 33527, "isreloading" },
	{ 33528, "isswitchingweapon" },
	{ 33529, "setorigin" },
	{ 33530, "getvelocity" },
	{ 33531, "setplayerangles" },
	{ 33532, "getplayerangles" },
	{ 33533, "usebuttonpressed" },
	{ 33534, "attackbuttonpressed" },
	{ 33535, "adsbuttonpressed" },
	{ 33536, "meleebuttonpressed" },
	{ 33537, "playerads" },
	{ 33538, "isonground" },
	{ 33539, "isusingturret" },
	{ 33540, "setviewmodel" },
	{ 33541, "setoffhandprimaryclass" },
	{ 33542, "getoffhandprimaryclass" },
	{ 33543, "startac130" },
	{ 33544, "stopac130" },
	{ 33545, "error" },
	{ 33546, "setscriptmoverinkillcam" },
	{ 33547, "fadeovertime2" },
	{ 33548, "scaleovertime" },
};

std::unordered_map <std::uint16_t, std::string> filename_map =
{
	// missing files: aitype, animscripts, character, animated_models, mptype
	// _dev, _globalentities, _hostmigration (empty files?)
	{ 29, "maps/mp/gametypes/_tweakables" },
	{ 30, "common_scripts/utility" },
	{ 31, "common_scripts/_createfxmenu" },
	{ 32, "common_scripts/_fx" },
	// empty 33-69
	{ 70, "common_scripts/_destructible" },
	// empty 75-93
	{ 94, "common_scripts/_destructible_types" },
	// empty 95-224
	{ 225, "common_scripts/_artcommon" },
	// empty 226-272
	{ 273, "common_scripts/_elevator" },
	// empty 274-313
	{ 314, "common_scripts/_pipes" },
	{ 315, "common_scripts/_dynamic_world" },
	// empty 316-323
	{ 324, "codescripts/character" },
	// empty 325-365
	{ 366, "maps/mp/_utility" },
	{ 367, "maps/mp/gametypes/_rank" },
	{ 368, "maps/mp/gametypes/_persistence" },
	// empty 369-399
	{ 400, "maps/mp/gametypes/_gamelogic" },
	{ 401, "maps/mp/killstreaks/_killstreaks" },
	{ 402, "maps/mp/gametypes/_missions" },
	{ 403, "maps/mp/gametypes/_hud_message" },
	// characters
	{ 404, "mp_character_ally_ghillie_desert_sniper" },
	{ 405, "mp_character_opforce_ghillie_desert_sniper" },
	// 400s characters
	{ 491, "mp_character_sas_urban_assault" },
	{ 512, "unknown" },// 512 some utility shit
	// 532 characters
	// 533 characters
	// 600s, 700s 819-834 characters, animated_models, animscripts ...
	{ 835, "maps/mp/gametypes/_weapons" },
	{ 836, "maps/mp/_entityheadicons" },
	{ 837, "maps/mp/gametypes/_damagefeedback" },
	{ 838, "maps/mp/_stinger" },
	{ 839, "maps/mp/_flashgrenades" },
	{ 840, "maps/mp/_empgrenade" },
	{ 841, "maps/mp/gametypes/_class" },
	{ 842, "maps/mp/_equipment" },
	{ 843, "maps/mp/_javelin" },
	{ 844, "maps/mp/gametypes/_shellshock" },
	{ 845, "maps/mp/_matchdata" },
	{ 846, "maps/mp/killstreaks/_perkstreaks" },
	{ 847, "maps/mp/perks/_perkfunctions" },
	{ 848, "maps/mp/gametypes/_scrambler" },
	{ 849, "maps/mp/gametypes/_portable_radar" },
	{ 850, "maps/mp/gametypes/_objpoints" },
	{ 851, "maps/mp/gametypes/_hud_util" },
	{ 852, "maps/mp/gametypes/_gameobjects" },
	// empty 953-972
	{ 873, "maps/mp/gametypes/_quickmessages" },
	{ 874, "maps/mp/gametypes/_playerlogic" },
	{ 875, "maps/mp/gametypes/_spectating" },
	{ 876, "maps/mp/gametypes/_spawnlogic" },
	{ 877, "maps/mp/_events" },
	{ 878, "maps/mp/gametypes/_gamescore" },
	{ 879, "maps/mp/gametypes/_menus" },
	{ 880, "maps/mp/_minefields" },
	{ 881, "maps/mp/_radiation" },
	{ 882, "maps/mp/_shutter" },
	{ 883, "maps/mp/_destructables" },
	{ 884, "maps/mp/_audio" },
	{ 885, "maps/mp/_art" }, // 4 empty functions (iw4 have 4 empty funcs too)
	{ 886, "maps/mp/_createfx" },
	{ 887, "maps/mp/_global_fx" },
	{ 888, "maps/mp/_animatedmodels" },
	{ 889, "maps/mp/killstreaks/_helicopter" },
	{ 890, "maps/mp/_skill" },
	{ 891, "maps/mp/killstreaks/_remoteuav" },
	{ 892, "maps/mp/gametypes/_battlechatter_mp" },
	{ 893, "maps/mp/gametypes/_deathicons" },
	{ 894, "maps/mp/gametypes/_killcam" },
	{ 895, "maps/mp/perks/_perks" },
	{ 896, "maps/mp/gametypes/_damage" },
	{ 897, "maps/mp/_highlights" },
	{ 898, "maps/mp/killstreaks/_escortairdrop" },
	{ 899, "maps/mp/killstreaks/_juggernaut" },
	{ 900, "maps/mp/killstreaks/_autosentry" },
	{ 901, "maps/mp/killstreaks/_airdrop" },
	{ 902, "maps/mp/gametypes/_hud" },
	{ 903, "maps/mp/_load" },
	{ 904, "maps/mp/gametypes/_serversettings" },
	// empty 905-933
	{ 906, "unknown" }, // mp_plaza2.ff
	{ 907, "unknown" }, // mp_plaza2.ff
	{ 908, "unknown" }, // mp_carbon.ff
	{ 909, "unknown" }, // mp_carbon.ff

	{ 912, "unknown" }, // mp_village.ff
	{ 913, "unknown" }, // mp_village.ff
	{ 914, "unknown" }, // mp_seatown.ff
	{ 915, "unknown" }, // mp_seatown.ff
	{ 916, "unknown" }, // mp_lambeth.ff
	{ 917, "unknown" }, // mp_lambeth.ff
	{ 918, "unknown" }, // mp_hardhat.ff
	{ 919, "unknown" }, // mp_hardhat.ff
	{ 920, "unknown" }, // mp_bootleg.ff
	{ 921, "unknown" }, // mp_bootleg.ff
	{ 922, "unknown" }, // mp_exchange.ff
	{ 923, "unknown" }, // mp_exchange.ff
	{ 924, "unknown" }, // mp_mogadishu.ff
	{ 925, "unknown" }, // mp_mogadishu.ff
	{ 926, "unknown" }, // mp_underground.ff
	{ 927, "unknown" }, // mp_underground.ff
	{ 928, "unknown" }, // mp_interchange.ff
	{ 929, "unknown" }, // mp_interchange.ff

	{ 934, "maps/mp/gametypes/_healthoverlay" },
	{ 935, "maps/mp/gametypes/_music_and_dialog" },
	{ 936, "maps/mp/_awards" },
	{ 937, "maps/mp/_areas" },
	{ 938, "maps/mp/_defcon" },
	{ 939, "maps/mp/_matchevents" },
	{ 940, "maps/mp/gametypes/_friendicons" },
	{ 941, "maps/mp/gametypes/_scoreboard" },
	{ 942, "maps/mp/killstreaks/_harrier" },
	{ 943, "maps/mp/gametypes/_callbacksetup" },
	{ 944, "maps/mp/killstreaks/_airstrike" },
	{ 945, "maps/mp/killstreaks/_emp" },
	{ 946, "maps/mp/killstreaks/_uav" },
	{ 947, "maps/mp/killstreaks/_ac130" },
	{ 948, "maps/mp/killstreaks/_remotemissile" },
	{ 949, "maps/mp/killstreaks/_helicopter_flock" },
	// empty 950-978
	{ 967, "unknown" }, // mp_dome.ff
	{ 968, "unknown" }, // mp_dome.ff

	{ 971, "unknown" }, // mp_radar.ff
	{ 972, "unknown" }, // mp_radar.ff
	{ 973, "unknown" }, // mp_paris.ff
	{ 974, "unknown" }, // mp_paris.ff
	{ 975, "unknown" }, // mp_bravo.ff
	{ 976, "unknown" }, // mp_bravo.ff
	{ 977, "unknown" }, // mp_alpha.ff
	{ 978, "unknown" }, // mp_alpha.ff
	{ 979, "maps/mp/killstreaks/_helicopter_guard" },
	{ 980, "maps/mp/killstreaks/_nuke" },
	{ 981, "maps/mp/killstreaks/_remotemortar" },
	{ 982, "maps/mp/killstreaks/_deployablebox" },
	{ 983, "maps/mp/killstreaks/_ims" },
	{ 984, "maps/mp/killstreaks/_remoteturret" },
	{ 985, "maps/mp/killstreaks/_remotetank" },
	{ 986, "maps/mp/gametypes/_playercards" },
	{ 987, "maps/mp/gametypes/_globallogic" },
	// empty 988-997
	{ 998, "maps/mp/gametypes/_teams" },
	// empty 999-1215
	{ 1216, "maps/mp/killstreaks/_pavelow" },
	{ 1217, "maps/mp/_fx" },
	{ 1218, "maps/mp/_compass" },
	{ 1219, "unknown" }, // 1 empty function
	{ 1220, "maps/mp/_crib" },
	{ 1221, "maps/mp/killstreaks/_autoshotgun" },
	{ 1222, "maps/mp/killstreaks/_tank" },
	{ 1223, "maps/mp/killstreaks/_mobilemortar" },
	{ 1224, "maps/mp/killstreaks/_a10" },
	{ 1225, "maps/mp/killstreaks/_teamammorefill" },
	{ 1226, "unknown" }, // empty file
	{ 1227, "unknown" }, // 11 empty functions
	{ 1228, "unknown" }, // empty file
	{ 1229, "unknown" }, // empty file
	{ 1230, "maps/mp/killstreaks/_aamissile" },
	{ 1231, "maps/mp/killstreaks/_aastrike" },
	{ 1232, "maps/mp/killstreaks/_reaper" },
	// empty 1233-1342
	{ 1343, "mp_character_gign_head" }, // unk
	{ 1344, "codescripts/delete" },
	{ 1345, "codescripts/struct" },	

	{ 1443, "unknown" }, // mp_dome.ff mp_bootleg.ff mp_carbon.ff  mp_hardhat.ff mp_interchange.ff mp_seatown.ff  mp_underground.ff mp_boardwalk.ff
	{ 1444, "unknown" }, // mp_dome.ff anim ?
	{ 1445, "unknown" }, // mp_dome.ff anim ?
	{ 1446, "unknown" }, // mp_dome.ff anim ?
	{ 1447, "unknown" }, // mp_dome.ff anim ?
	{ 1448, "unknown" }, // mp_dome.ff anim ?
	{ 1449, "unknown" }, // mp_dome.ff anim ?
	{ 1450, "unknown" }, // mp_dome.ff anim ?
	{ 1451, "unknown" }, // mp_dome.ff anim ?
	{ 1452, "unknown" }, // mp_dome.ff anim ?
	{ 1453, "unknown" }, // mp_dome.ff anim ?
	{ 1454, "unknown" }, // mp_dome.ff anim ?
	{ 1455, "unknown" }, // mp_dome.ff anim ?
	{ 1456, "unknown" }, // mp_dome.ff anim ?
	{ 1457, "unknown" }, // mp_dome.ff anim ?
	{ 1458, "unknown" }, // mp_dome.ff anim ?
	{ 1459, "unknown" }, // mp_dome.ff fx, art
	{ 1460, "unknown" }, // mp_dome.ff fx, art mp_carbon.ff mp_hardhat.ff mp_interchange.ff mp_lambeth.ff  mp_radar.ff
	{ 1461, "unknown" }, // mp_dome.ff fx, art
	{ 1462, "unknown" }, // mp_dome.ff fx, art



	{ 1642, "unknown" }, // mp_carbon.ff

	{ 18649, "unknown" }, // mp_carbon.ff mp_hardhat.ff mp_radar.ff
	{ 18650, "unknown" }, // mp_carbon.ff mp_radar.ff  mp_underground.ff
	{ 18651, "unknown" }, // mp_radar.ff
	{ 18652, "unknown" }, // mp_radar.ff
	{ 18653, "unknown" }, // mp_radar.ff
	{ 18654, "unknown" }, // mp_radar.ff
	{ 18655, "unknown" }, // mp_radar.ff
	{ 18656, "unknown" }, // mp_radar.ff
	{ 18657, "unknown" }, // mp_radar.ff
	{ 18658, "unknown" }, // mp_radar.ff

	{ 18661, "unknown" }, // mp_bootleg.ff mp_seatown.ff mp_village.ff
	{ 18662, "unknown" }, // mp_bravo.ff mp_mogadishu.ff mp_seatown.ff mp_village.ff
	{ 18663, "unknown" }, // mp_village.ff
	{ 18664, "unknown" }, // mp_village.ff
	{ 18665, "unknown" }, // mp_village.ff
	{ 18666, "unknown" }, // mp_underground.ff
	{ 18667, "unknown" }, // mp_underground.ff

	{ 18670, "unknown" }, // mp_underground.ff
	{ 18671, "unknown" }, // mp_underground.ff
	{ 18672, "unknown" }, // mp_underground.ff
	{ 18673, "unknown" }, // mp_seatown.ff mp_boardwalk.ff
	{ 18674, "unknown" }, // mp_bravo.ff mp_seatown.ff
	{ 18675, "unknown" }, // mp_bravo.ff mp_seatown.ff
	{ 18676, "unknown" }, // mp_bravo.ff  mp_seatown.ff
	{ 18677, "unknown" }, // mp_seatown.ff
	{ 18678, "unknown" }, // mp_seatown.ff
	{ 18679, "unknown" }, // mp_seatown.ff
	{ 18680, "unknown" }, // mp_seatown.ff
	{ 18681, "unknown" }, // mp_seatown.ff
	{ 18682, "unknown" }, // mp_seatown.ff
	{ 18683, "unknown" }, // mp_seatown.ff
	{ 18684, "unknown" }, // mp_seatown.ff
	{ 18685, "unknown" }, // mp_seatown.ff


	{ 18686, "unknown" }, // mp_seatown.ff
	{ 18687, "unknown" }, // mp_seatown.ff
	{ 18688, "unknown" }, // mp_seatown.ff
	{ 18689, "unknown" }, // mp_bootleg.ff mp_bravo.ff mp_plaza2.ff mp_boardwalk.ff
	{ 18690, "unknown" }, // mp_plaza2.ff
	{ 18691, "unknown" }, // mp_plaza2.ff
	{ 18692, "unknown" }, // mp_plaza2.ff
	{ 18693, "unknown" }, // mp_plaza2.ff
	{ 18694, "unknown" }, // mp_paris.ff
	{ 18695, "unknown" }, // mp_paris.ff
	{ 18696, "unknown" }, // mp_paris.ff
	{ 18697, "unknown" }, // mp_paris.ff
	{ 18698, "unknown" }, // mp_mogadishu.ff
	{ 18699, "unknown" }, // mp_mogadishu.ff
	{ 18700, "unknown" }, // mp_mogadishu.ff
	{ 18701, "unknown" }, // mp_lambeth.ff
	{ 18702, "unknown" }, // mp_lambeth.ff
	{ 18703, "unknown" }, // mp_lambeth.ff
	{ 18704, "unknown" }, // mp_lambeth.ff
	{ 18705, "unknown" }, // mp_lambeth.ff
	{ 18706, "unknown" }, // mp_lambeth.ff
	{ 18707, "unknown" }, // mp_interchange.ff
	{ 18708, "unknown" }, // mp_interchange.ff
	{ 18709, "unknown" }, // mp_interchange.ff
	{ 18710, "unknown" }, // mp_hardhat.ff
	{ 18711, "unknown" }, // mp_hardhat.ff
	{ 18712, "unknown" }, // mp_hardhat.ff
	{ 18713, "unknown" }, // mp_hardhat.ff
	{ 18714, "unknown" }, // mp_hardhat.ff
	{ 18715, "unknown" }, // mp_hardhat.ff
	{ 18716, "unknown" }, // mp_hardhat.ff
	{ 18717, "unknown" }, // mp_hardhat.ff
	{ 18718, "unknown" }, // mp_hardhat.ff
	{ 18719, "unknown" }, // mp_hardhat.ff
	{ 18720, "unknown" }, // mp_hardhat.ff
	{ 18721, "unknown" }, // mp_hardhat.ff
	{ 18722, "unknown" }, // mp_hardhat.ff
	{ 18723, "unknown" }, // mp_hardhat.ff
	{ 18724, "unknown" }, // mp_hardhat.ff
	{ 18725, "unknown" }, // mp_hardhat.ff
	{ 18726, "unknown" }, // mp_hardhat.ff
	{ 18727, "unknown" }, // mp_hardhat.ff
	{ 18728, "unknown" }, // mp_hardhat.ff
	{ 18729, "unknown" }, // mp_hardhat.ff
	{ 18730, "unknown" }, // mp_hardhat.ff
	{ 18731, "unknown" }, // mp_hardhat.ff
	{ 18732, "unknown" }, // mp_hardhat.ff
	{ 18733, "unknown" }, // mp_exchange.ff
	{ 18734, "unknown" }, // mp_exchange.ff
	{ 18735, "unknown" }, // mp_exchange.ff
	{ 18736, "unknown" }, // mp_carbon.ff
	{ 18737, "unknown" }, // mp_carbon.ff
	{ 18738, "unknown" }, // mp_carbon.ff
	{ 18739, "unknown" }, // mp_carbon.ff
	{ 18740, "unknown" }, // mp_carbon.ff
	{ 18741, "unknown" }, // mp_carbon.ff
	{ 18742, "unknown" }, // mp_carbon.ff
	{ 18743, "unknown" }, // mp_carbon.ff
	{ 18744, "unknown" }, // mp_carbon.ff
	{ 18745, "unknown" }, // mp_carbon.ff
	{ 18746, "unknown" }, // mp_carbon.ff
	{ 18747, "unknown" }, // mp_carbon.ff
	{ 18748, "unknown" }, // mp_carbon.ff
	{ 18749, "unknown" }, // mp_carbon.ff
	{ 18750, "unknown" }, // mp_carbon.ff
	{ 18751, "unknown" }, // mp_carbon.ff
	{ 18752, "unknown" }, // mp_carbon.ff
	{ 18753, "unknown" }, // mp_carbon.ff
	{ 18754, "unknown" }, // mp_carbon.ff

	{ 18758, "unknown" }, // mp_carbon.ff
	{ 18759, "unknown" }, // mp_carbon.ff
	{ 18760, "unknown" }, // mp_bravo.ff
	{ 18761, "unknown" }, // mp_bravo.ff
	{ 18762, "unknown" }, // mp_bravo.ff
	{ 18763, "unknown" }, // mp_bravo.ff
	{ 18764, "unknown" }, // mp_bravo.ff
	{ 18765, "unknown" }, // mp_bravo.ff
	{ 18766, "unknown" }, // mp_bootleg.ff
	{ 18767, "unknown" }, // mp_bootleg.ff
	{ 18768, "unknown" }, // mp_bootleg.ff
	{ 18769, "unknown" }, // mp_bootleg.ff
	{ 18770, "unknown" }, // mp_alpha.ff
	{ 18771, "unknown" }, // mp_alpha.ff
	{ 18772, "unknown" }, // mp_alpha.ff
	{ 18773, "unknown" }, // mp_alpha.ff

	{ 33361, "maps/mp/mp_italy_precache" }, // mp_italy.ff
	{ 33362, "maps/createart/mp_italy_art" }, // mp_italy.ff
	{ 33363, "maps/mp/mp_italy_fx" }, // mp_italy.ff
	{ 33364, "maps/createfx/mp_italy_fx" }, // mp_italy.ff
	{ 33365, "maps/createart/mp_italy_fog" }, // mp_italy.ff

	{ 33366, "maps/mp/mp_park_precache" }, // mp_park.ff
	{ 33367, "maps/createart/mp_park_art" }, // mp_park.ff
	{ 33368, "maps/mp/mp_park_fx" }, // mp_park.ff
	{ 33369, "maps/createfx/mp_park_fx" }, // mp_park.ff
	{ 33370, "maps/createart/mp_park_fog" }, // mp_park.ff

	{ 33371, "maps/mp/mp_overwatch_precache" }, // mp_overwatch.ff
	{ 33372, "maps/createart/mp_overwatch_art" }, // mp_overwatch.ff
	{ 33373, "maps/mp/mp_overwatch_fx" }, // mp_overwatch.ff
	{ 33374, "maps/createfx/mp_overwatch_fx" }, // mp_overwatch.ff
	{ 33375, "maps/createart/mp_overwatch_fog" }, // mp_overwatch.ff

	{ 33376, "maps/mp/mp_morningwood_precache" }, // mp_morningwood.ff
	{ 33377, "maps/createart/mp_morningwood_art" }, // mp_morningwood.ff
	{ 33378, "maps/mp/mp_morningwood_fx" }, // mp_morningwood.ff
	{ 33379, "maps/createfx/mp_morningwood_fx" }, // mp_morningwood.ff
	{ 33380, "maps/createart/mp_morningwood_fog" }, // mp_morningwood.ff

		/*
	scriptfile,maps/mp/gametypes/faceoff
	scriptfile,maps/mp/mp_aground_ss
	scriptfile,maps/mp/mp_aground_ss_precache
	scriptfile,maps/mp/mp_aground_ss_fx
	scriptfile,maps/createfx/mp_aground_ss_fx
	scriptfile,maps/createart/mp_aground_ss_art
	scriptfile,maps/createart/mp_aground_ss_fog

	scriptfile,maps/mp/mp_boardwalk
	scriptfile,maps/mp/mp_boardwalk_precache
	scriptfile,maps/mp/mp_boardwalk_fx
	scriptfile,maps/createfx/mp_boardwalk_fx
	scriptfile,maps/createart/mp_boardwalk_art
	scriptfile,maps/createart/mp_boardwalk_fog
	scriptfile,maps/mp/mp_boardwalk_scriptlights
	scriptfile,maps/animated_models/bw_dd_carscript_01_full_anim

	scriptfile,maps/createart/mp_burn_ss_fog
	scriptfile,maps/mp/mp_burn_ss
	scriptfile,maps/mp/mp_burn_ss_precache
	scriptfile,maps/mp/mp_burn_ss_fx
	scriptfile,maps/createfx/mp_burn_ss_fx
	scriptfile,maps/createart/mp_burn_ss_art

	scriptfile,maps/animated_models/vehicle_industrial_truck_anims
	scriptfile,maps/animated_models/foliage_tree_river_birch_med_a
	scriptfile,maps/animated_models/mp_cement_tarp3
	scriptfile,maps/animated_models/mp_cement_tarp4_a
	scriptfile,maps/animated_models/mp_cement_tarp4_b
	scriptfile,maps/animated_models/mp_cement_tarp4_d
	scriptfile,maps/animated_models/mp_cement_tarp4_e
	scriptfile,maps/animated_models/mp_cement_tarp4_f
	scriptfile,maps/animated_models/mp_cement_tarp4_g
	scriptfile,maps/animated_models/vehicle_industrial_truck_spin
	scriptfile,maps/mp/mp_cement
	scriptfile,maps/mp/mp_cement_precache
	scriptfile,maps/mp/mp_cement_fx
	scriptfile,maps/createfx/mp_cement_fx
	scriptfile,maps/createart/mp_cement_fog
	scriptfile,maps/createart/mp_cement_art
	scriptfile,common_scripts/_interactive

	scriptfile,maps/mp/mp_courtyard_ss
	scriptfile,maps/mp/mp_courtyard_ss_precache
	scriptfile,maps/mp/mp_courtyard_ss_fx
	scriptfile,maps/createfx/mp_courtyard_ss_fx
	scriptfile,maps/createart/mp_courtyard_ss_art
	scriptfile,maps/createart/mp_courtyard_ss_fog

	scriptfile,maps/mp/mp_crosswalk_ss
	scriptfile,maps/mp/mp_crosswalk_ss_precache
	scriptfile,maps/mp/mp_crosswalk_ss_fx
	scriptfile,maps/createfx/mp_crosswalk_ss_fx
	scriptfile,maps/createart/mp_crosswalk_ss_art
	scriptfile,maps/createart/mp_crosswalk_ss_fog

	scriptfile,maps/mp/mp_hillside_ss
	scriptfile,maps/mp/mp_hillside_ss_precache
	scriptfile,maps/mp/mp_hillside_ss_fx
	scriptfile,maps/createfx/mp_hillside_ss_fx
	scriptfile,maps/createart/mp_hillside_ss_art
	scriptfile,maps/createart/mp_hillside_ss_fog
	scriptfile,maps/animated_models/com_boat_fishing_buoy2_scale5
	scriptfile,maps/animated_models/hillside_awnings_animated
	scriptfile,maps/animated_models/hillside_drapes_animated
	scriptfile,maps/animated_models/yacht_modern_periph

	scriptfile,maps/mp/mp_meteora
	scriptfile,maps/mp/mp_meteora_precache
	scriptfile,maps/mp/mp_meteora_fx
	scriptfile,maps/createfx/mp_meteora_fx
	scriptfile,maps/createart/mp_meteora_art
	scriptfile,maps/createart/mp_meteora_fog
	scriptfile,maps/animated_models/lantern_iron_off_animated
	scriptfile,maps/animated_models/foliage_afr_tree_umbrel_01a_sway
	scriptfile,maps/animated_models/foliage_tree_birch_yellow_light_sway

	scriptfile,maps/mp/mp_moab
	scriptfile,maps/mp/mp_moab_precache
	scriptfile,maps/mp/mp_moab_fx
	scriptfile,maps/createfx/mp_moab_fx
	scriptfile,maps/createart/mp_moab_art
	scriptfile,maps/createart/mp_moab_fog
	scriptfile,maps/animated_models/moab_curtains_lace
	scriptfile,maps/animated_models/moab_tailing_wheel_full_anim

	scriptfile,maps/mp/mp_nola
	scriptfile,maps/mp/mp_nola_precache
	scriptfile,maps/mp/mp_nola_fx
	scriptfile,maps/createfx/mp_nola_fx
	scriptfile,maps/mp/mp_nola_scriptlights
	scriptfile,maps/createart/mp_nola_art
	scriptfile,maps/createart/mp_nola_fog


	scriptfile,maps/animated_models/ow_chute_corner_hang_idle
	scriptfile,maps/animated_models/ow_chute_side_hang_idle
	scriptfile,maps/animated_models/ow_crane_hook
	scriptfile,maps/animated_models/foliage_prk_tree_beech_fall_anim
	scriptfile,maps/animated_models/foliage_prk_tree_birch_animated

	scriptfile,maps/mp/mp_qadeem
	scriptfile,maps/mp/mp_qadeem_precache
	scriptfile,maps/mp/mp_qadeem_fx
	scriptfile,maps/createfx/mp_qadeem_fx
	scriptfile,maps/createart/mp_qadeem_art
	scriptfile,maps/createart/mp_qadeem_fog

	scriptfile,maps/animated_models/foliage_pacific_palms06_animated
	scriptfile,maps/animated_models/foliage_pacific_palms08_animated
	scriptfile,maps/animated_models/foliage_tree_palm_bushy_3
	scriptfile,maps/animated_models/qad_foliage_tree_palm_bushy_3
	scriptfile,maps/animated_models/qad_lamp_windy_animated
	scriptfile,maps/animated_models/qad_palmtree_bushy_animated
	scriptfile,maps/animated_models/qad_palmtree_tall_animated

	scriptfile,maps/mp/mp_restrepo_ss
	scriptfile,maps/mp/mp_restrepo_ss_precache
	scriptfile,maps/mp/mp_restrepo_ss_fx
	scriptfile,maps/createfx/mp_restrepo_ss_fx
	scriptfile,maps/createart/mp_restrepo_ss_art
	scriptfile,maps/createart/mp_restrepo_ss_fog

	scriptfile,maps/mp/mp_roughneck
	scriptfile,maps/mp/mp_roughneck_precache
	scriptfile,maps/mp/mp_roughneck_fx
	scriptfile,maps/createfx/mp_roughneck_fx
	scriptfile,maps/createart/mp_roughneck_art
	scriptfile,maps/createart/mp_roughneck_fog

	scriptfile,maps/mp/mp_shipbreaker
	scriptfile,maps/mp/mp_shipbreaker_precache
	scriptfile,maps/mp/mp_shipbreaker_fx
	scriptfile,maps/createfx/mp_shipbreaker_fx
	scriptfile,maps/mp/mp_shipbreaker_scriptlights
	scriptfile,maps/createart/mp_shipbreaker_art
	scriptfile,maps/createart/mp_shipbreaker_fog

	scriptfile,maps/animated_models/sb_metal_chunk_animated
	scriptfile,common_scripts/_destructible_types_anim_chicken_dlc

	scriptfile,maps/mp/gametypes/faceoff
	scriptfile,maps/mp/mp_six_ss
	scriptfile,maps/mp/mp_six_ss_precache
	scriptfile,maps/mp/mp_six_ss_fx
	scriptfile,maps/createfx/mp_six_ss_fx
	scriptfile,maps/createart/mp_six_ss_art
	scriptfile,maps/createart/mp_six_ss_fog

	scriptfile,maps/animated_models/barn_door_l
	scriptfile,maps/animated_models/barn_door_r
	scriptfile,maps/animated_models/corn_field_01_anim
	scriptfile,maps/animated_models/farmhouse_distant
	scriptfile,maps/animated_models/fence_flimsy_animated
	scriptfile,maps/animated_models/fence_sturdy_animated
	scriptfile,maps/animated_models/lamp_iron_hanging_nochain_animated
	scriptfile,maps/animated_models/me_corrugated_metal_anim
	scriptfile,maps/animated_models/paris_shutter_anim_violent_01
	scriptfile,maps/animated_models/paris_shutter_anim_violent_02
	scriptfile,maps/animated_models/paris_shutter_anim_violent_03
	scriptfile,maps/animated_models/prop_chain_hanging_combined
	scriptfile,maps/animated_models/prop_chain_hanging_loop
	scriptfile,maps/animated_models/prop_chain_hanging_long
	scriptfile,maps/animated_models/prop_chain_hanging_short
	scriptfile,maps/animated_models/river_birch_lg_a_animated
	scriptfile,maps/animated_models/stable_doors_anim
	scriptfile,maps/animated_models/ug_oak_tree_windy_anim
	scriptfile,maps/animated_models/wire_hanging_192long
	scriptfile,maps/animated_models/wire_hanging_512long

	scriptfile,maps/mp/mp_terminal_cls
	scriptfile,maps/mp/mp_terminal_cls_precache
	scriptfile,maps/mp/mp_terminal_cls_fx
	scriptfile,maps/createfx/mp_terminal_cls_fx
	scriptfile,maps/createart/mp_terminal_cls_art
	scriptfile,maps/createart/mp_terminal_cls_fog

	scriptfile,animscripts/traverse/traverse_window_terminal
	scriptfile,maps/animated_models/accessories_windsock_wind_medium
	scriptfile,maps/animated_models/foliage_pacific_fern01
	*/
};

std::unordered_map <std::uint16_t, std::string> functions_map =
{
	{ 1650, "main" },
	{ 1651, "CodeCallback_StartGameType" },
	{ 1652, "CodeCallback_PlayerConnect" },
	{ 1653, "CodeCallback_PlayerDisconnect" },
	{ 1654, "CodeCallback_PlayerDamage" },
	{ 1655, "CodeCallback_PlayerKilled" },
	{ 1656, "CodeCallback_VehicleDamage" },
	{ 1657, "CodeCallback_CodeEndGame" },
	{ 1658, "CodeCallback_PlayerLastStand" },
	{ 1659, "CodeCallback_PlayerMigrated" },
	{ 1660, "CodeCallback_HostMigration" },
	{ 1661, "initstructs" },
	{ 1662, "createstruct" },
	{ 1663, "" }, // unk
	{ 1664, "init" },
	{ 1665, "precache" },

	// codescripts/character
	{ 7765, "setModelFromArray" },
	{ 7766, "precacheModelArray" },
	{ 7767, "attachHead" },
	{ 7771, "func_7771" },
	{ 7773, "new" },
	{ 7776, "save" },
	{ 7778, "load" },
	{ 7779, "get_random_character" },
	{ 7782, "get_least_used_index" },
	{ 7783, "initialize_character_group" },
	{ 7784, "get_random_weapon" },
	{ 2363, "random" },

	// common_scripts/_artcommon
	{ 6858, "artStartVisionFileExport" },
	{ 6859, "artEndVisionFileExport" },
	{ 6860, "artStartFogFileExport" },
	{ 6861, "artEndFogFileExport" },
	{ 6862, "artCommonfxprintln" },
	{ 6863, "setfogsliders" },
	{ 6864, "translateFogSlidersToScript" },
	{ 6875, "limit" },
	{ 6876, "updateFogFromScript" },
	{ 6877, "artfxprintlnFog" },

	// common_scripts/_createfx
	{ 0, "" },

	// common_scripts/_createfxmenu
	{ 0, "" },

	// common_scripts/_destructible
	{ 0, "" },

	// common_scripts/_destructible_types
	{ 0, "" },

	// common_scripts/_dynamic_world
	{ 0, "" },

	// common_scripts/_elevator
	{ 0, "" },

	// common_scripts/_fx
	{ 0, "" },

	// common_scripts/_pipes
	{ 0, "" },

	// common_scripts/utility
	{ 0, "" },

	// maps/mp/gametypes/_battlechatter_mp
	{ 7448, "onPlayerConnect" },
	{ 11281, "onPlayerSpawned" },
	{ 12633, "grenadeProximityTracking" },
	{ 12634, "suppressingFireTracking" },
	{ 12635, "suppressWaiter" },
	{ 12636, "claymoreTracking" },
	{ 12637, "reloadTracking" },
	{ 12638, "grenadeTracking" },
	{ 12639, "sayLocalSoundDelayed" },
	{ 12640, "sayLocalSound" },
	{ 12641, "doSound" },
	{ 12642, "timeHack" },
	{ 12643, "isSpeakerInRange" },
	{ 12644, "addSpeaker" },
	{ 12645, "removeSpeaker" },

	// maps/mp/gametypes/_callbacksetup
	{ 13320, "SetupDamageFlags" }, 
	{ 13325, "SetupCallbacks" },
	{ 13326, "SetDefaultCallbacks" },
	{ 13327, "AbortLevel" },
	{ 13328, "callbackVoid" },
	
	// maps/mp/gametypes/_class
	{ 12179, "getClassChoice" },
	{ 12180, "getWeaponChoice" },
	{ 14202, "logClassChoice" },
	{ 442, "cac_getCustomClassLoc" },
	{ 11477, "cac_getWeapon" },
	{ 11622, "cac_getWeaponAttachment" },
	{ 11623, "cac_getWeaponAttachmentTwo" },
	{ 11627, "cac_getWeaponBuff" },
	{ 14203, "cac_getWeaponCamo" },
	{ 14204, "cac_getWeaponReticle" },
	{ 11625, "cac_getPerk" },
	{ 11628, "cac_getKillstreak" },
	{ 11626, "cac_getDeathstreak" },
	{ 11624, "cac_getOffhand" },
	{ 14205, "recipe_getKillstreak" },
	{ 11630, "table_getWeapon" },
	{ 11631, "table_getWeaponAttachment" },
	{ 11636, "table_getWeaponBuff" },
	{ 14206, "table_getWeaponCamo" },
	{ 14207, "table_getWeaponReticle" },
	{ 11633, "table_getEquipment" },
	{ 11634, "table_getPerk" },
	{ 14208, "table_getTeamPerk" },
	{ 11632, "table_getOffhand" },
	{ 11637, "table_getKillstreak" },
	{ 11635, "table_getDeathstreak" },
	{ 11621, "getClassIndex" },
	{ 12660, "cloneLoadout" },
	{ 14209, "loadoutFakePerks" },
	{ 14210, "getLoadoutStreakTypeFromStreakType" },
	{ 12026, "giveLoadout" },
	{ 14218, "_detachAll" },
	{ 14023, "isPerkUpgraded" },
	{ 11681, "getPerkUpgrade" },
	{ 14219, "loadoutAllPerks" },
	{ 11461, "trackRiotShield" },
	{ 14224, "tryAttach" },
	{ 14225, "tryDetach" },
	{ 14226, "buildWeaponName" },
	{ 14229, "buildWeaponNameCamo" },
	{ 14230, "buildWeaponNameReticle" },
	{ 14231, "makeLettersToNumbers" },
	{ 14232, "setKillstreaks" },
	{ 14233, "replenishLoadout" },
	{ 14235, "onPlayerConnecting" },
	{ 14236, "fadeAway" },
	{ 12182, "setClass" },
	{ 14237, "getPerkForClass" },
	{ 14238, "classHasPerk" },
	{ 14198, "isValidPrimary" },
	{ 14199, "isValidSecondary" },
	{ 14239, "isValidAttachment" },
	{ 14146, "isAttachmentUnlocked" },
	{ 14240, "isValidWeaponBuff" },
	{ 14241, "isWeaponBuffUnlocked" },
	{ 14242, "isValidCamo" },
	{ 14243, "isValidReticle" },
	{ 14244, "isCamoUnlocked" },
	{ 14245, "isValidEquipment" },
	{ 14246, "isValidOffhand" },
	{ 14247, "isValidPerk1" },
	{ 14248, "isValidPerk2" },
	{ 14249, "isValidPerk3" },
	{ 14250, "isValidDeathStreak" },
	{ 14251, "isValidWeapon" },
	{ 14253, "isValidKillstreak" },
	
	// maps/mp/gametypes/_damage
	{ 0, "" },

	// maps/mp/gametypes/_damagefeedback
	{ 7448, "onPlayerConnect" },
	{ 6702, "updateDamageFeedback" },

	// maps/mp/gametypes/_deathicons
	{ 7448, "onPlayerConnect" },
	{ 12384, "updateDeathIconsEnabled" },
	{ 12385, "addDeathIcon" },
	{ 12387, "destroySlowly" },

	// maps/mp/gametypes/_dev
	{ 0, "" },

	// maps/mp/gametypes/_equipment
	{ 11312, "watchTrophyUsage" },
	{ 11321, "trophyUseListener" },
	{ 11325, "trophyPlayerSpawnWaiter" },
	{ 11326, "trophyDisconnectWaiter" },
	{ 11327, "trophyActive" },
	{ 11333, "projectileExplode" },
	{ 11336, "trophyDamage" },
	{ 11341, "trophyBreak" },

	// maps/mp/gametypes/_friendicons
	{ 0, "onPlayerConnect" },
	{ 0, "onPlayerSpawned" },
	{ 0, "onPlayerKilled" },
	{ 0, "showFriendIcon" },
	{ 0, "updateFriendIconSettings" },
	{ 0, "updateFriendIcons" },

	// maps/mp/gametypes/_gamelogic
	{ 0, "" },

	// maps/mp/gametypes/_gameobjects
	{ 0, "" },
};

std::unordered_map <std::uint16_t, std::string> fields_map =
{
// level
	// codescripts/struct
	{ 2291, "struct" },

	{7781, "character_index_cache" },

	// maps/mp/gametypes/_callbacksetup
	{ 7207, "callbackPlayerDamage" },
	{ 11338, "iDFLAGS_PENETRATION" },
	{ 13323, "iDFLAGS_NO_TEAM_PROTECTION" },
	{ 13324, "iDFLAGS_PASSTHRU" },
	{ 12327, "callbackStartGameType" },
	{ 12328, "callbackPlayerConnect" },
	{ 12329, "callbackPlayerDisconnect" },
	{ 12330, "callbackPlayerKilled" },
	{ 12331, "callbackCodeEndGame" },
	{ 12332, "callbackPlayerLastStand" },
	{ 12333, "callbackPlayerMigrated" },
	{ 12735, "iDFLAGS_STUN" },
	{ 12736, "iDFLAGS_SHIELD_EXPLOSIVE_IMPACT" },
	{ 12737, "iDFLAGS_SHIELD_EXPLOSIVE_IMPACT_HUGE" },
	{ 12738, "iDFLAGS_SHIELD_EXPLOSIVE_SPLASH" },
	{ 12742, "iDFLAGS_NO_KNOCKBACK" },
	{ 12744, "iDFLAGS_NO_PROTECTION" },
	{ 13317, "gametypestarted" },
	{ 13318, "damageCallback" },
	{ 13319, "callbackHostMigration" },
	{ 13321, "iDFLAGS_RADIUS" },
	
	{ 11629, "classTableName" },
	{ 14200, "classMap" },
	{ 14200, "defaultClass" },

// self
	{ 3791, "headModel" },
	{ 11620, "curClass" },
	{ 12181, "lastClass" },
	
};

std::size_t GetInstructionSize(std::uint8_t opcode)
{
	switch (opcode)
	{
	case OP_End:
	case OP_Return:
	case OP_GetUndefined:
	case OP_GetZero:
	case OP_EvalLocalVariableCached0:
	case OP_EvalLocalVariableCached1:
	case OP_EvalLocalVariableCached2:
	case OP_EvalLocalVariableCached3:
	case OP_EvalLocalVariableCached4:
	case OP_EvalLocalVariableCached5:
	case OP_EvalArray:
	case OP_EvalNewLocalArrayRefCached0:
	case OP_EvalArrayRef:
	case OP_ClearArray:
	case OP_EmptyArray:
	case OP_AddArray:
	case OP_PreScriptCall:
	case OP_ScriptFunctionCallPointer:
	case OP_ScriptMethodCallPointer:
	case OP_GetSelf:
	case OP_GetLevel:
	case OP_GetGame:
	case OP_GetGameRef:
	case OP_inc:
	case OP_dec:
	case OP_bit_or:
	case OP_bit_ex_or:
	case OP_bit_and:
	case OP_equality:
	case OP_inequality:
	case OP_less:
	case OP_greater:
	case OP_less_equal:
	case OP_waittill:
	case OP_notify:
	case OP_endon:
	case OP_voidCodepos:
	case OP_vector:
	case OP_greater_equal:
	case OP_plus:
	case OP_minus:
	case OP_multiply:
	case OP_divide:
	case OP_mod:
	case OP_size:
	case OP_GetSelfObject:
	case OP_SafeSetVariableFieldCached0:
	case OP_clearparams:
	case OP_checkclearparams:
	case OP_EvalLocalVariableRefCached0:
	case OP_EvalNewLocalVariableRefCached0:
	case OP_SetVariableField:
	case OP_SetLocalVariableFieldCached0:
	case OP_ClearLocalVariableFieldCached0:
	case OP_wait:
	case OP_DecTop:
	case OP_CastFieldObject:
	case OP_CastBool:
	case OP_BoolNot:
	case OP_BoolComplement:
	case OP_GetAnimation:
		return 1;
		break;
	case OP_GetByte:
	case OP_CreateLocalVariable:
	case OP_RemoveLocalVariables:
	case OP_EvalLocalVariableCached:
	case OP_EvalLocalArrayCached:
	case OP_EvalLocalArrayRefCached0:
	case OP_EvalLocalArrayRefCached:
	case OP_ScriptThreadCallPointer:
	case OP_ScriptMethodThreadCallPointer:
	case OP_ScriptMethodChildThreadCallPointer:
	case OP_CallBuiltinPointer:
	case OP_CallBuiltinMethodPointer:
	case OP_GetAnimObject:
	case OP_SafeCreateVariableFieldCached:
	case OP_SafeSetVariableFieldCached:
	case OP_SafeSetWaittillVariableFieldCached:
	case OP_EvalLocalVariableRefCached:
	case OP_SetNewLocalVariableFieldCached0:
	case OP_SetLocalVariableFieldCached:
	case OP_ClearLocalVariableFieldCached:
	case OP_EvalLocalVariableObjectCached:
	case OP_GetNegByte:
		return 2;
		break;
	case OP_GetUnsignedShort:
	case OP_jumpback:
	case OP_waittillmatch:
	case OP_GetNegUnsignedShort:
	case OP_JumpOnFalseExpr:
	case OP_JumpOnTrueExpr:
	case OP_JumpOnFalse:
	case OP_JumpOnTrue:
	case OP_GetBuiltinFunction:
	case OP_GetBuiltinMethod:
	case OP_CallBuiltin0:
	case OP_CallBuiltin1:
	case OP_CallBuiltin2:
	case OP_CallBuiltin3:
	case OP_CallBuiltin4:
	case OP_CallBuiltin5:
	case OP_CallBuiltinMethod0:
	case OP_CallBuiltinMethod1:
	case OP_CallBuiltinMethod2:
	case OP_CallBuiltinMethod3:
	case OP_CallBuiltinMethod4:
	case OP_CallBuiltinMethod5:
	case OP_GetString:
	case OP_GetIString:
	case OP_EvalLevelFieldVariable:
	case OP_EvalAnimFieldVariable:
	case OP_EvalSelfFieldVariable:
	case OP_EvalFieldVariable:
	case OP_EvalLevelFieldVariableRef:
	case OP_EvalAnimFieldVariableRef:
	case OP_EvalSelfFieldVariableRef:
	case OP_EvalFieldVariableRef:
	case OP_ClearFieldVariable:
	case OP_SetLevelFieldVariableField:
	case OP_SetAnimFieldVariableField:
	case OP_SetSelfFieldVariableField:
	case OP_GetAnimTree:
	case OP_endswitch:
		return 3;
		break;
	case OP_ScriptLocalFunctionCall2:
	case OP_ScriptLocalFunctionCall:
	case OP_ScriptLocalMethodCall:
	case OP_GetLocalFunction:
	case OP_ScriptFarFunctionCall2:
	case OP_ScriptFarFunctionCall:
	case OP_ScriptFarMethodCall:
	case OP_GetFarFunction:
	case OP_CallBuiltin:
	case OP_CallBuiltinMethod:
		return 4;
		break;
	case OP_GetInteger:
	case OP_switch:
	case OP_jump:
	case OP_GetFloat:
	case OP_ScriptLocalThreadCall:
	case OP_ScriptLocalChildThreadCall:
	case OP_ScriptLocalMethodThreadCall:
	case OP_ScriptLocalMethodChildThreadCall:
	case OP_ScriptFarThreadCall:
	case OP_ScriptFarChildThreadCall:
	case OP_ScriptFarMethodThreadCall:
	case OP_ScriptFarMethodChildThreadCall:
		return 5;
		break;
	case OP_GetVector:
		return 13;
		break;
	default:
		printf("[ERROR] Couldn't resolve instruction size 0x%X!\n", opcode);
		return 0;
	}
}

std::string GetOpCodeName(std::uint8_t id)
{
	if (opcode_map.find(id) != opcode_map.end())
		return opcode_map[id];

	printf("[ERROR]: Couldn't resolve opcode 0x%X!\n", id);
	return "";
}

std::uint8_t GetOpCodeId(const std::string& name)
{
	for (auto& opcode : opcode_map)
	{
		if (opcode.second == name)
		{
			return opcode.first;
		}
	}

	printf("[ERROR]: Couldn't resolve opcode \"%s\"!\n", name.data());
	return 0xFF;
}

std::string GetBuiltinFuncName(std::uint16_t id)
{
	if (builtin_func_map.find(id) != builtin_func_map.end())
		return builtin_func_map[id];

	printf("[ERROR]: Couldn't resolve builtin function 0x%X!\n", id);
	return "";
}

std::uint16_t GetBuiltinFuncId(const std::string& name)
{
	for (auto& func : builtin_func_map)
	{
		if (func.second == name)
		{
			return func.first;
		}
	}

	printf("[ERROR]: Couldn't resolve builtin function \"%s\"!\n", name.data());
	return 0xFFFF;
}

std::string GetBuiltinMethodName(std::uint16_t id)
{
	if (builtin_method_map.find(id) != builtin_method_map.end())
		return builtin_method_map[id];

	printf("[ERROR]: Couldn't resolve builtin method 0x%X!\n", id);
	return "";
}

std::uint16_t GetBuiltinMethodId(const std::string& name)
{
	for (auto& func : builtin_method_map)
	{
		if (func.second == name)
		{
			return func.first;
		}
	}

	printf("[ERROR]: Couldn't resolve builtin method \"%s\"!\n", name.data());
	return 0xFFFF;
}

std::string GetFileName(std::uint16_t id)
{
	if (filename_map.find(id) != filename_map.end())
		return filename_map[id];

	printf("[ERROR]: Couldn't resolve file 0x%X!\n", id);
	return "";
}

std::string GetFunctionName(std::uint16_t id)
{
	if (functions_map.find(id) != functions_map.end())
		return functions_map[id];

	printf("[ERROR]: Couldn't resolve function 0x%X!\n", id);
	return "";
}

std::string GetFieldName(std::uint16_t id)
{
	if (fields_map.find(id) != fields_map.end())
		return fields_map[id];

	printf("[ERROR]: Couldn't resolve field 0x%X!\n", id);
	return "";
}
