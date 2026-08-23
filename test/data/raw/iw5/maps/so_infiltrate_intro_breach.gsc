#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;

/*QUAKED trigger_use_breach (0.1 0.3 1.0) STARTOFF HAS_USER
Starts a slow mo breach sequence.
*/

/*QUAKED trigger_multiple_breachIcon (0.1 0.3 1.0) ? AI_AXIS AI_ALLIES AI_NEUTRAL NOTPLAYER VEHICLE TRIGGER_SPAWN TOUCH_ONCE
Targets a script origin. Makes the breach icon appear when you look at a breach door.
*/

/*QUAKED info_volume_breachdoor (0.1 0.3 1.0) ?
Include this volume in a breach prefab (with trigger, door posts, etc). Used to determine if there are any friendlies near the door to assist in muultiple-entry point breaches.
*/

/*QUAKED info_volume_breachroom (0.1 0.3 1.0) ?
Targeted by the breach icon script_origin on the breach door prefab. Can be targeted by multiple script_origins for multiple-entry point breaches. Used to set a flag when the room is cleared (add key "script_flag"). Also used to detect enemy and hostage status within the room.
*/

/*QUAKED info_volume_breachsafearea (0.1 0.3 1.0) ?
Optional. Add script_slomobreach number as a key/value to check to see if there are any enemies in this volume before allowing the breach to be performed.
*/

slowmo_breach_init()
{
	level.last_player_damage = 0;
	level.slomobreachduration = 3.5;	// duration of slomo breach
	level.breachEnemies_active = 0;
	level.breachignoreEnemy_count = false; 
	level.player_one_already_breached = undefined;
	level.breachEnemies_alive = 0;
	level.has_special_breach_anim = [];
	level.breach_passive_time = 0;
	level.single_breach_ok = false;
	if( !isdefined( level.override_reload ))
		level.override_reload = false;

	//set up dynamic sound channels that will only be partially affected by slomo (Values given by the audio dept)
	slomo_sound_scale_setup();

	//setDvarIfUninitialized( "breach_weapons", "0" );
	SetDvarIfUninitialized( "breach_debug", "0" );
	SetDvarIfUninitialized( "breach_requires_friendlies_in_position", "1" );

	//set dvar "hostage_missionfail" to "1" in your own script to have hostage deaths trigger a mission failure
	SetDvarIfUninitialized( "hostage_missionfail", "0" );

	PreCacheItem( "usp_scripted" );
	PreCacheShader( "breach_icon" );
	PreCacheModel( "weapon_parabolic_knife" );
	
	precacheString( &"SCRIPT_WAYPOINT_BREACH" );
	precacheString( &"SCRIPT_PLATFORM_BREACH_ACTIVATE" );
	precacheString( &"SCRIPT_BREACH_NEED_PLAYER" );
	precacheString( &"SCRIPT_BREACH_NEED_FRIENDLY" );
	precacheString( &"SCRIPT_BREACH_TOO_MANY_ENEMIES" );
	precacheString( &"SCRIPT_BREACH_ILLEGAL_WEAPON" );
	precacheString( &"SCRIPT_BREACH_PARTNER_NOT_READY" );
	precacheString( &"SCRIPT_BREACH_YOU_NOT_READY" );
	precacheString( &"SCRIPT_MISSIONFAIL_KILLEDHOSTAGE_THROUGH_ENEMY" );
	precacheString( &"SCRIPT_MISSIONFAIL_KILLEDHOSTAGE" );
	precacheString( &"SCRIPT_MISSIONFAIL_HOSTAGEEXECUTED" );
	precacheString( &"SCRIPT_MISSIONFAIL_HOSTAGEEXECUTED_USEMULTIDOOR" );
	precacheString( &"SCRIPT_BREACH_RELOADING" );
	
	level._slowmo_functions = [];
	level._effect[ "breach_door" ]					 = LoadFX( "explosions/breach_door" );
	level._effect[ "breach_room" ]					 = LoadFX( "explosions/breach_room" );
	level._effect[ "breach_room_residual" ]			 = LoadFX( "explosions/breach_room_residual" );
	level._effect[ "breach_knife_execution" ]		 = LoadFX( "impacts/flesh_hit_knife" );

	script_models();
	player_animations();
	generic_animations();
	friendly_animations();
	breach_anims();

	create_slowmo_breaches_from_entities();

	// this trigger will show the breach icon on the door when you look at it
	icon_triggers = GetEntArray( "trigger_multiple_breachIcon", "classname" );
	array_thread( icon_triggers, ::icon_trigger_setup );

	// entities that aren't meant to exist if a slowmo breach will happen
	breach_deletables = GetEntArray( "breach_solid_delete", "targetname" );
	array_call( breach_deletables, ::ConnectPaths );
	array_thread( breach_deletables, ::self_delete );

	// entities that aren't meant to exist if a slowmo breach will happen
	breach_deletables = GetEntArray( "breach_delete", "targetname" );
	array_thread( breach_deletables, ::self_delete );

	breach_fx = GetEntArray( "breach_fx", "targetname" );
	array_thread( breach_fx, ::breach_fx_setup );

	level.has_special_breach_anim[ "aa12" ] = true;
	level.has_special_breach_anim[ "aa12_reflex" ] = true;
	level.has_special_breach_anim[ "aa12_hb" ] = true;	
	level.has_special_breach_anim[ "aug_reflex" ] = true;
	level.has_special_breach_anim[ "aug_scope" ] = true;
	level.has_special_breach_anim[ "barrett" ] = true;
	level.has_special_breach_anim[ "beretta" ] = true;
	level.has_special_breach_anim[ "beretta393" ] = true;
	level.has_special_breach_anim[ "cheytac_silencer" ] = true;
	level.has_special_breach_anim[ "fal" ] = true;
	level.has_special_breach_anim[ "fal_acog" ] = true;
	level.has_special_breach_anim[ "fal_reflex" ] = true;
	level.has_special_breach_anim[ "fal_shotgun" ] = true;
	level.has_special_breach_anim[ "fal_shotgun_attach" ] = true;
	level.has_special_breach_anim[ "famas" ] = true;
	level.has_special_breach_anim[ "famas_arctic" ] = true;
	level.has_special_breach_anim[ "famas_arctic_eotech" ] = true;
	level.has_special_breach_anim[ "famas_arctic_reflex" ] = true;
	level.has_special_breach_anim[ "famas_mp2" ] = true;
	level.has_special_breach_anim[ "famas_shotgun" ] = true;
	level.has_special_breach_anim[ "famas_shotgun_attach" ] = true;
	level.has_special_breach_anim[ "famas_woodland" ] = true;
	level.has_special_breach_anim[ "famas_woodland_eotech" ] = true;
	level.has_special_breach_anim[ "famas_woodland_acog" ] = true;
	level.has_special_breach_anim[ "famas_woodland_reflex" ] = true;
	level.has_special_breach_anim[ "famas_woodland_shotgun" ] = true;
	level.has_special_breach_anim[ "famas_woodland_shotgun_attach" ] = true;
	level.has_special_breach_anim[ "fn2000" ] = true;
	level.has_special_breach_anim[ "fn2000_acog" ] = true;
	level.has_special_breach_anim[ "fn2000_eotech" ] = true;
	level.has_special_breach_anim[ "fn2000_reflex" ] = true;
	level.has_special_breach_anim[ "fn2000_scope" ] = true;
	level.has_special_breach_anim[ "fn2000_shotgun" ] = true;
	level.has_special_breach_anim[ "fn2000_shotgun_attach" ] = true;
	level.has_special_breach_anim[ "fn2000_silencer" ] = true;
	level.has_special_breach_anim[ "fn2000_thermal" ] = true;
	level.has_special_breach_anim[ "glock" ] = true;
	level.has_special_breach_anim[ "kriss" ] = true;
	level.has_special_breach_anim[ "kriss_reflex" ] = true;
	level.has_special_breach_anim[ "kriss_eotech" ] = true;
	level.has_special_breach_anim[ "kriss_acog_silencer" ] = true;
	level.has_special_breach_anim[ "m1014" ] = true;
	level.has_special_breach_anim[ "m14_scoped" ] = true;
	level.has_special_breach_anim[ "m14_scoped_arctic" ] = true;
	level.has_special_breach_anim[ "m14_scoped_ghil" ] = true;
	level.has_special_breach_anim[ "m14_scoped_silencer" ] = true;
	level.has_special_breach_anim[ "m14_scoped_silencer_woodland" ] = true;
	level.has_special_breach_anim[ "m14_scoped_woodland" ] = true;
	level.has_special_breach_anim[ "m14ebr" ] = true;
	level.has_special_breach_anim[ "m14ebr_thermal" ] = true;
	level.has_special_breach_anim[ "m203" ] = true;
	level.has_special_breach_anim[ "m16_acog" ] = true;
	level.has_special_breach_anim[ "m16_basic" ] = true;
	level.has_special_breach_anim[ "m16_grenadier" ] = true;
	level.has_special_breach_anim[ "m16_reflex" ] = true;
	level.has_special_breach_anim[ "m16_silencer" ] = true;
	level.has_special_breach_anim[ "m21_baseasset" ] = true;
	level.has_special_breach_anim[ "m21_scoped_arctic_silenced" ] = true;
	level.has_special_breach_anim[ "mp5" ] = true;
	level.has_special_breach_anim[ "mp5_arctic" ] = true;
	level.has_special_breach_anim[ "mp5_arctic_reflex" ] = true;
	level.has_special_breach_anim[ "mp5_eotech" ] = true;
	level.has_special_breach_anim[ "mp5_reflex" ] = true;
	level.has_special_breach_anim[ "mp5_silencer" ] = true;
	level.has_special_breach_anim[ "mp5_silencer_reflex" ] = true;
	level.has_special_breach_anim[ "ranger" ] = true;
	level.has_special_breach_anim[ "striker" ] = true;
	level.has_special_breach_anim[ "striker_reflex" ] = true;
	level.has_special_breach_anim[ "striker_woodland" ] = true;
	level.has_special_breach_anim[ "striker_woodland_reflex" ] = true;
	level.has_special_breach_anim[ "tavor_acog" ] = true;
	level.has_special_breach_anim[ "tavor_digital_acog" ] = true;
	level.has_special_breach_anim[ "tavor_digital_eotech" ] = true;
	level.has_special_breach_anim[ "tavor_digital_mars" ] = true;
	level.has_special_breach_anim[ "tavor_digital_reflex" ] = true;
	level.has_special_breach_anim[ "tavor_eotech" ] = true;
	level.has_special_breach_anim[ "tavor_mars" ] = true;
	level.has_special_breach_anim[ "tavor_reflex" ] = true;
	level.has_special_breach_anim[ "tavor_woodland_acog" ] = true;
	level.has_special_breach_anim[ "tavor_woodland_eotech" ] = true;
	level.has_special_breach_anim[ "tavor_woodland_mars" ] = true;
	level.has_special_breach_anim[ "tavor_woodland_reflex" ] = true;
	level.has_special_breach_anim[ "tmp" ] = true;
	level.has_special_breach_anim[ "tmp_reflex" ] = true;
	level.has_special_breach_anim[ "tmp_silencer" ] = true;
	level.has_special_breach_anim[ "ump45" ] = true;
	level.has_special_breach_anim[ "ump45_acog" ] = true;
	level.has_special_breach_anim[ "ump45_arctic" ] = true;
	level.has_special_breach_anim[ "ump45_arctic_acog" ] = true;
	level.has_special_breach_anim[ "ump45_arctic_reflex" ] = true;
	level.has_special_breach_anim[ "ump45_reflex" ] = true;
	level.has_special_breach_anim[ "ump45_silencer" ] = true;
	level.has_special_breach_anim[ "ump45_eotech" ] = true;
	level.has_special_breach_anim[ "wa2000" ] = true;
	level.has_special_breach_anim[ "wa2000_thermal" ] = true;
	level.has_special_breach_anim[ "g36c" ] = true;
	level.has_special_breach_anim[ "g36c_acog" ] = true;
	level.has_special_breach_anim[ "g36c_reflex" ] = true;
	level.has_special_breach_anim[ "g36c_grenadier" ] = true;
	level.has_special_breach_anim[ "pecheneg" ] = true;
	level.has_special_breach_anim[ "pecheneg_reflex" ] = true;
	level.has_special_breach_anim[ "gl_g36c" ] = true;
	level.has_special_breach_anim[ "m240" ] = true;
	level.has_special_breach_anim[ "m240_reflex" ] = true;
	level.has_special_breach_anim[ "m240_acog" ] = true;
	level.has_special_breach_anim[ "m4_grenadier" ] = true;
	level.has_special_breach_anim[ "m4_grunt" ] = true;
	level.has_special_breach_anim[ "m4_grunt_acog" ] = true;
	level.has_special_breach_anim[ "m4_grunt_reflex" ] = true;
	level.has_special_breach_anim[ "m4_shotgun" ] = true;
	level.has_special_breach_anim[ "m4_shotgun_attach" ] = true;
	level.has_special_breach_anim[ "m4_silencer" ] = true;
	level.has_special_breach_anim[ "m4_silencer_acog" ] = true;
	level.has_special_breach_anim[ "alt_m4m203_acog" ] = true;
	level.has_special_breach_anim[ "m4m203_acog" ] = true;
	level.has_special_breach_anim[ "alt_m4m203_acog_payback" ] = true;
	level.has_special_breach_anim[ "m4m203_acog_payback" ] = true;
	level.has_special_breach_anim[ "m4m203_reflex" ] = true;
	level.has_special_breach_anim[ "m4m203_reflex_arctic" ] = true;
	level.has_special_breach_anim[ "m4m203_silencer" ] = true;
	level.has_special_breach_anim[ "m4m203_silencer_reflex" ] = true;
	level.has_special_breach_anim[ "m4m203_eotech" ] = true;
	level.has_special_breach_anim[ "scar_h" ] = true;
	level.has_special_breach_anim[ "scar_h_fgrip" ] = true;
	level.has_special_breach_anim[ "scar_h_acog" ] = true;
	level.has_special_breach_anim[ "scar_h_grenadier" ] = true;
	level.has_special_breach_anim[ "scar_h_reflex" ] = true;
	level.has_special_breach_anim[ "scar_h_shotgun" ] = true;
	level.has_special_breach_anim[ "scar_h_shotgun_attach" ] = true;
	level.has_special_breach_anim[ "scar_h_silencer" ] = true;
	level.has_special_breach_anim[ "scar_h_thermal_silencer" ] = true;
	level.has_special_breach_anim[ "scar_h_thermal" ] = true;
	level.has_special_breach_anim[ "scar_h_m203" ] = true;
	level.has_special_breach_anim[ "m203_m4" ] = true;
	level.has_special_breach_anim[ "m203_m4_acog" ] = true;
	level.has_special_breach_anim[ "m203_m4_eotech" ] = true;
	level.has_special_breach_anim[ "m203_m4_reflex" ] = true;
	level.has_special_breach_anim[ "m203_m4_silencer" ] = true;
	level.has_special_breach_anim[ "m203_m4_silencer_reflex" ] = true;
	level.has_special_breach_anim[ "m203_m4_reflex_arctic" ] = true;
	level.has_special_breach_anim[ "coltanaconda" ] = true;
	level.has_special_breach_anim[ "deserteagle" ] = true;
	level.has_special_breach_anim[ "pp2000" ] = true;
	level.has_special_breach_anim[ "pp2000_reflex" ] = true;
	level.has_special_breach_anim[ "pp2000_silencer" ] = true;
	level.has_special_breach_anim[ "pp2000_thermal" ] = true;
	level.has_special_breach_anim[ "ak47" ] = true;
	level.has_special_breach_anim[ "ak47_acog" ] = true;
	level.has_special_breach_anim[ "ak47_arctic" ] = true;
	level.has_special_breach_anim[ "ak47_arctic_acog" ] = true;
	level.has_special_breach_anim[ "ak47_arctic_eotech" ] = true;
	level.has_special_breach_anim[ "ak47_arctic_grenadier" ] = true;
	level.has_special_breach_anim[ "ak47_arctic_reflex" ] = true;
	level.has_special_breach_anim[ "ak47_desert" ] = true;
	level.has_special_breach_anim[ "ak47_desert_acog" ] = true;
	level.has_special_breach_anim[ "ak47_desert_eotech" ] = true;
	level.has_special_breach_anim[ "ak47_desert_grenadier" ] = true;
	level.has_special_breach_anim[ "ak47_desert_reflex" ] = true;
	level.has_special_breach_anim[ "ak47_digital" ] = true;
	level.has_special_breach_anim[ "ak47_digital_acog" ] = true;
	level.has_special_breach_anim[ "ak47_digital_eotech" ] = true;
	level.has_special_breach_anim[ "ak47_digital_grenadier" ] = true;
	level.has_special_breach_anim[ "ak47_digital_reflex" ] = true;
	level.has_special_breach_anim[ "ak47_eotech" ] = true;
	level.has_special_breach_anim[ "ak47_fall" ] = true;
	level.has_special_breach_anim[ "ak47_fall_acog" ] = true;
	level.has_special_breach_anim[ "ak47_fall_eotech" ] = true;
	level.has_special_breach_anim[ "ak47_fall_grenadier" ] = true;
	level.has_special_breach_anim[ "ak47_fall_reflex" ] = true;
	level.has_special_breach_anim[ "ak47_grenadier" ] = true;
	level.has_special_breach_anim[ "ak47_reflex" ] = true;
	level.has_special_breach_anim[ "ak47_shotgun" ] = true;
	level.has_special_breach_anim[ "ak47_shotgun_attach" ] = true;
	level.has_special_breach_anim[ "ak47_silencer" ] = true;
	level.has_special_breach_anim[ "ak47_thermal" ] = true;
	level.has_special_breach_anim[ "ak47_woodland" ] = true;
	level.has_special_breach_anim[ "ak47_woodland_acog" ] = true;
	level.has_special_breach_anim[ "ak47_woodland_eotech" ] = true;
	level.has_special_breach_anim[ "ak47_woodland_grenadier" ] = true;
	level.has_special_breach_anim[ "ak47_woodland_reflex" ] = true;
	level.has_special_breach_anim[ "gl_ak47" ] = true;
	level.has_special_breach_anim[ "gl_ak47_arctic" ] = true;
	level.has_special_breach_anim[ "masada" ] = true;
	level.has_special_breach_anim[ "masada_acog" ] = true;
	level.has_special_breach_anim[ "masada_dcburn_mt_black_off" ] = true;
	level.has_special_breach_anim[ "masada_dcburn_mt_black_on" ] = true;
	level.has_special_breach_anim[ "masada_digital" ] = true;
	level.has_special_breach_anim[ "masada_digital_acog" ] = true;
	level.has_special_breach_anim[ "masada_digital_eotech" ] = true;
	level.has_special_breach_anim[ "masada_digital_grenadier_eotech" ] = true;
	level.has_special_breach_anim[ "gl_masada_digital_eotech" ] = true;
	level.has_special_breach_anim[ "masada_digital_reflex" ] = true;
	level.has_special_breach_anim[ "masada_eotech" ] = true;
	level.has_special_breach_anim[ "masada_grenadier_acog" ] = true;
	level.has_special_breach_anim[ "masada_reflex" ] = true;
	level.has_special_breach_anim[ "masada_silencer_motion_tracker_off" ] = true;
	level.has_special_breach_anim[ "masada_silencer_motion_tracker_on" ] = true;
	level.has_special_breach_anim[ "masada_silencer_mt_black_off" ] = true;
	level.has_special_breach_anim[ "masada_silencer_mt_black_on" ] = true;
	level.has_special_breach_anim[ "masada_silencer_mt_camo_off" ] = true;
	level.has_special_breach_anim[ "masada_silencer_mt_camo_on" ] = true;
	level.has_special_breach_anim[ "masada_silencer_mt_dust_off" ] = true;
	level.has_special_breach_anim[ "masada_silencer_mt_dust_on" ] = true;
	level.has_special_breach_anim[ "uzi" ] = true;
	level.has_special_breach_anim[ "uzi_sd" ] = true;
	level.has_special_breach_anim[ "uzi_silencer" ] = true;
	level.has_special_breach_anim[ "uzi_akimbo" ] = true;
	level.has_special_breach_anim[ "p90" ] = true;
	level.has_special_breach_anim[ "p90_acog" ] = true;
	level.has_special_breach_anim[ "p90_eotech" ] = true;
	level.has_special_breach_anim[ "p90_reflex" ] = true;
	level.has_special_breach_anim[ "p90_silencer" ] = true;
	level.has_special_breach_anim[ "p90_arctic" ] = true;
	level.has_special_breach_anim[ "p90_arctic_acog" ] = true;
	level.has_special_breach_anim[ "p90_arctic_eotech" ] = true;
	level.has_special_breach_anim[ "p90_arctic_reflex" ] = true;
	level.has_special_breach_anim[ "rpd" ] = true;
	level.has_special_breach_anim[ "rpd_acog" ] = true;
	level.has_special_breach_anim[ "rpd_grip" ] = true;
	level.has_special_breach_anim[ "rpd_reflex" ] = true;
	level.has_special_breach_anim[ "sa80" ] = true;
	level.has_special_breach_anim[ "sa80_scope" ] = true;
	level.has_special_breach_anim[ "sa80lmg" ] = true;
	level.has_special_breach_anim[ "sa80lmg_reflex" ] = true;
	level.has_special_breach_anim[ "sa80lmg_scope" ] = true;
	level.has_special_breach_anim[ "at4" ] = true;
	level.has_special_breach_anim[ "at4_straight" ] = true;
	level.has_special_breach_anim[ "model1887" ] = true;
	level.has_special_breach_anim[ "usp" ] = true;
	level.has_special_breach_anim[ "usp_airport" ] = true;
	level.has_special_breach_anim[ "usp_silencer" ] = true;
	level.has_special_breach_anim[ "dragunov" ] = true;
	level.has_special_breach_anim[ "dragunov_arctic" ] = true;
	level.has_special_breach_anim[ "dragunov_desert" ] = true;
	level.has_special_breach_anim[ "dragunov_fall" ] = true;
	level.has_special_breach_anim[ "dragunov_woodland" ] = true;
	level.has_special_breach_anim[ "mg4" ] = true;
	level.has_special_breach_anim[ "mg4_acog" ] = true;
	level.has_special_breach_anim[ "mg4_arctic" ] = true;
	level.has_special_breach_anim[ "mg4_arctic_reflex" ] = true;
	level.has_special_breach_anim[ "mg4_arctic_thermal" ] = true;
	level.has_special_breach_anim[ "mg4_reflex" ] = true;
	level.has_special_breach_anim[ "mg4_thermal" ] = true;
	level.has_special_breach_anim[ "spas12" ] = true;
	level.has_special_breach_anim[ "spas12_arctic" ] = true;
    level.has_special_breach_anim[ "spas12_arctic_eotech" ] = true;
    level.has_special_breach_anim[ "spas12_arctic_grip" ] = true;
    level.has_special_breach_anim[ "spas12_arctic_heartbeat" ] = true;
    level.has_special_breach_anim[ "spas12_arctic_heartbeat_attach" ] = true;
    level.has_special_breach_anim[ "spas12_arctic_reflex" ] = true;
    level.has_special_breach_anim[ "spas12_eotech" ] = true;
    level.has_special_breach_anim[ "spas12_grip" ] = true;
    level.has_special_breach_anim[ "spas12_heartbeat" ] = true;
    level.has_special_breach_anim[ "spas12_heartbeat_attach" ] = true;
    level.has_special_breach_anim[ "spas12_reflex" ] = true;
    level.has_special_breach_anim[ "spas12_silencer" ] = true;
	level.has_special_breach_anim[ "paw20_eotech" ] = true;
	level.has_special_breach_anim[ "acr_hybrid" ] = true;
	level.has_special_breach_anim[ "acr_hybrid_silenced" ] = true;
	level.has_special_breach_anim[ "alt_acr_hybrid" ] = true;
	level.has_special_breach_anim[ "alt_acr_hybrid_silenced" ] = true;
	level.has_special_breach_anim[ "p99" ] = true;
	level.has_special_breach_anim[ "rsass" ] = true;
	level.has_special_breach_anim[ "fnfiveseven" ] = true;
	level.has_special_breach_anim[ "pp90m1" ] = true;
	level.has_special_breach_anim[ "pp90m1_acog" ] = true;
	level.has_special_breach_anim[ "pp90m1_eotech" ] = true;
	level.has_special_breach_anim[ "pp90m1_reflex" ] = true;
	level.has_special_breach_anim[ "pp90m1_silencer" ] = true;

	flag_init( "breaching_on" );
	flag_init( "no_mercy" );
}

check_missing_animation()
{
	if ( !isdefined( self.animation ) )
		return;

	if ( self will_be_manhandled() && self.script_noteworthy == "manhandled" )
	{
		AssertEx( IsDefined( self.target ), "Manhandled spawner with export " + self.export + " has no target." );
		spawner = GetEnt( self.target, "targetname" );
		AssertEx( IsDefined( spawner ) && IsSpawner( spawner ), "Manhandled spawner with export " + self.export + " has no spawner." );
		level.manhandled_spawners[ self.export ] = spawner;
	}

	parms = self.script_parameters;
	if ( IsDefined( parms ) )
	{
		level.missing_animation_parameters[ parms ] = true;
	}

	level.missing_animations[ self.animation ] = true;



}

is_breach_anim_loop_setup( anime, index, animation )
{
	if ( !isdefined( level.scr_anim[ "generic" ][ anime ] ) )
		return false;
	if ( !isdefined( level.scr_anim[ "generic" ][ anime ][ index ] ) )
		return false;

//	if ( level.scr_anim[ "generic" ][ anime ][ index ] != animation )
//		return false;

	PrintLn( "	level.scr_anim[ \"generic\" ][ \"" + anime + "\" ][ " + index + " ] = %" + animation + ";" );
	return true;
}

is_breach_anim_single_setup( anime, animation )
{
	if ( !isdefined( level.scr_anim[ "generic" ][ anime ] ) )
		return false;

//	if ( level.scr_anim[ "generic" ][ anime ] != animation )
//		return false;

	PrintLn( "	level.scr_anim[ \"generic\" ][ \"" + anime + "\" ] = %" + animation + ";" );
	return true;
}

dump_missing_anims()
{
	if ( !level.missing_animations.size )
		return;

	PrintLn( "^3Add these lines to the generic_human.atr section of " + level.script + "_anim.gsc:" );
	PrintLn( "	// _slowmo_breach anims" );
	adds = [];
	adds[ adds.size ] = "_survives";
	adds[ adds.size ] = "_death";
	adds[ adds.size ] = "_death2";
	adds[ adds.size ] = "_idle";
	adds[ adds.size ] = "_manhandled_guarded";
	adds[ adds.size ] = "_manhandled";
	adds[ adds.size ] = "_manhandled_guarded_idle";
	adds[ adds.size ] = "_manhandled_idle";
	adds[ adds.size ] = "_manhandled_guarded_prepare_idle";
	adds[ adds.size ] = "_manhandled_prepare_idle";
	adds[ adds.size ] = "_manhandled_guarded_prepare";
	adds[ adds.size ] = "_manhandled_prepare";

	// make new versions of the adds that h
	add_suffix = [];
	foreach ( parm, _ in level.missing_animation_parameters )
	{
		foreach ( add in adds )
		{
			add_suffix[ add_suffix.size ] = add + parm;
		}
	}
	adds = array_combine( adds, add_suffix );

	foreach ( anime, _ in level.missing_animations )
	{
		printed = false;

		if ( IsDefined( level.scr_stub[ "generic" ][ anime ] ) )
		{
			if ( IsArray( level.scr_stub[ "generic" ][ anime ] ) )
			{
				foreach ( index, animation in level.scr_stub[ "generic" ][ anime ] )
				{
					if ( !is_breach_anim_loop_setup( anime, index, animation ) )
						printed = true;
				}
			}
			else
			{
				if ( !is_breach_anim_single_setup( anime, level.scr_stub[ "generic" ][ anime ] ) )
					printed = true;
			}
		}

		foreach ( add in adds )
		{
			check_anime = anime + add;
			if ( !isdefined( level.scr_stub[ "generic" ][ check_anime ] ) )
				continue;

			if ( IsArray( level.scr_stub[ "generic" ][ check_anime ] ) )
			{
				foreach ( index, animation in level.scr_stub[ "generic" ][ check_anime ] )
				{
					if ( !is_breach_anim_loop_setup( check_anime, index, animation ) )
						printed = true;
				}
			}
			else
			{
				if ( !is_breach_anim_single_setup( check_anime, level.scr_stub[ "generic" ][ check_anime ] ) )
					printed = true;
			}
		}

		if ( printed )
			level.missing_animations[ anime ] = undefined;
	}

	PrintLn( " " );
	//assertEx( !level.missing_animations.size, "Important! See missing slow mo breach anim defines above!" );

	level.missing_animation_parameters = undefined;
	level.missing_animations = undefined;
}


#using_animtree( "generic_human" );
breach_anims()
{
	// these AI are killed by the breach so they have self.skipDeathAnim set.
	level.breach_death_anims = [];

	//knife props for executions, etc
	addNotetrack_attach( "generic", "attach knife right", "weapon_parabolic_knife", "TAG_INHAND" );
	addNotetrack_detach( "generic", "detach knife right", "weapon_parabolic_knife", "TAG_INHAND", "breach_react_knife_charge" );


	//Friendly hostage takedowns
	level.scr_stub[ "generic" ][ "takedown_room2B_soldier" ]			 = "takedown_room2B_soldier";
	level.scr_stub[ "generic" ][ "takedown_room2B_soldier_idle" ][ 0 ]			 = "takedown_room2B_soldier_idle";
	level.scr_stub[ "generic" ][ "takedown_room1Alt_soldier" ]			 = "takedown_room1Alt_soldier";
	level.scr_stub[ "generic" ][ "takedown_room1Alt_soldier_idle" ][ 0 ]			 = "takedown_room1Alt_soldier_idle";
	level.scr_stub[ "generic" ][ "takedown_room2A_soldier" ]			 = "takedown_room2A_soldier";
	level.scr_stub[ "generic" ][ "takedown_room2A_soldier_idle" ][ 0 ]			 = "takedown_room2A_soldier_end_idle";
	level.scr_stub[ "generic" ][ "takedown_room1B_soldier" ]			 = "takedown_room1B_soldier";
	level.scr_stub[ "generic" ][ "takedown_room1B_soldier_idle" ][ 0 ]			 = "takedown_room1B_soldier_idle";
	level.scr_stub[ "generic" ][ "takedown_room1A_soldier" ]			 = "takedown_room1A_soldier";
	level.scr_stub[ "generic" ][ "takedown_room1A_soldier_idle" ][ 0 ]			 = "takedown_room1A_soldier_idle";

	//C4 Rigged Chair
	level.scr_stub[ "generic" ][ "hostage_chair_twitch2" ]		 = "hostage_chair_twitch2";
	level.scr_stub[ "generic" ][ "hostage_chair_twitch2_idle" ]	[ 0 ]		 = "hostage_chair_idle";
	level.scr_stub[ "generic" ][ "hostage_chair_twitch" ]		 = "hostage_chair_twitch";
	level.scr_stub[ "generic" ][ "hostage_chair_twitch_idle" ]	[ 0 ]		 = "hostage_chair_idle";
	add_slowmo_breach_custom_function( "hostage_chair_twitch2", ::_slomo_breach_c4_hostage );
	add_slowmo_breach_custom_function( "hostage_chair_twitch", ::_slomo_breach_c4_hostage );

	//human shield execution
	level.scr_stub[ "generic" ][ "execution_shield_soldier" ]			 = "execution_shield_soldier";
	level.scr_stub[ "generic" ][ "execution_shield_hostage" ]			 = "execution_shield_hostage";
	level.scr_stub[ "generic" ][ "execution_shield_hostage_death" ]			 = "execution_shield_hostage_death";
	level.scr_stub[ "generic" ][ "execution_shield_hostage_survives" ]			 = "execution_shield_hostage_survives";
	level.scr_stub[ "generic" ][ "execution_shield_hostage_idle" ][ 0 ]	 = "hostage_knees_idle";

	add_slowmo_breach_custom_function( "execution_shield_soldier", ::_slomo_breach_executioner_pistol );
	add_slowmo_breach_custom_function( "execution_shield_hostage", ::_slomo_breach_executed_guy );

	//knife execution #1
	level.scr_stub[ "generic" ][ "execution_knife_soldier" ]			 = "execution_knife_soldier";
	level.scr_stub[ "generic" ][ "execution_knife_hostage" ]			 = "execution_knife_hostage";
	level.scr_stub[ "generic" ][ "execution_knife_hostage_death" ]		 = "execution_knife_hostage_death";
	level.scr_stub[ "generic" ][ "execution_knife_hostage_idle" ][ 0 ]	 = "hostage_knees_idle";
	level.scr_stub[ "generic" ][ "execution_knife_hostage_manhandled" ]	 = "takedown_room2B_hostageA";
	level.scr_stub[ "generic" ][ "execution_knife_hostage_manhandled_idle" ][ 0 ]	 = "takedown_room2B_hostageA_idle";

	add_slowmo_breach_custom_function( "execution_knife_hostage", ::_slomo_breach_executed_guy );
	add_slowmo_breach_custom_function( "execution_knife_soldier", ::_slomo_breach_executioner_knife );

	//knife execution #2
	level.scr_stub[ "generic" ][ "execution_knife2_soldier" ]			 = "execution_knife2_soldier";
	level.scr_stub[ "generic" ][ "execution_knife2_hostage" ]			 = "execution_knife2_hostage";
	level.scr_stub[ "generic" ][ "execution_knife2_hostage_death" ]			 = "execution_knife2_hostage_death";
	level.scr_stub[ "generic" ][ "execution_knife2_hostage_idle" ][ 0 ]	 = "hostage_stand_idle";
	add_slowmo_breach_custom_function( "execution_knife2_hostage", ::_slomo_breach_executed_guy );
	add_slowmo_breach_custom_function( "execution_knife2_soldier", ::_slomo_breach_executioner_knife );

	//enemy headshots hostage on his knees
	level.scr_stub[ "generic" ][ "execution_onknees_soldier" ]			 = "execution_onknees_soldier";
	level.scr_stub[ "generic" ][ "execution_onknees_hostage" ]			 = "execution_onknees_hostage";
	//level.scr_stub[ "generic" ][ "execution_onknees_hostage_idle" ][ 0 ] = "execution_onknees_hostage_survives";
	level.scr_stub[ "generic" ][ "execution_onknees_hostage_survives" ] = "execution_onknees_hostage_survives";
	level.scr_stub[ "generic" ][ "execution_onknees_hostage_death" ]	 = "execution_onknees_hostage_death";
	level.scr_stub[ "generic" ][ "execution_onknees_hostage_manhandled_guarded" ]	 = "takedown_room1A_hostageB";
	level.scr_stub[ "generic" ][ "execution_onknees_hostage_manhandled_guarded_idle" ][ 0 ]	 = "takedown_room1A_hostageB_idle";

	add_slowmo_breach_custom_function( "execution_onknees_soldier", ::_slomo_breach_executioner_pistol );
	add_slowmo_breach_custom_function( "execution_onknees_hostage", ::_slomo_breach_executed_guy );

	//enemy headshots hostage on his knees (V2)
	level.scr_stub[ "generic" ][ "execution_onknees2_soldier" ]			 = "execution_onknees2_soldier";
	level.scr_stub[ "generic" ][ "execution_onknees2_hostage" ]			 = "execution_onknees2_hostage";
	level.scr_stub[ "generic" ][ "execution_onknees2_hostage_survives" ] = "execution_onknees2_hostage_survives";
	level.scr_stub[ "generic" ][ "execution_onknees2_hostage_death" ]	 = "execution_onknees2_hostage_death";
	level.scr_stub[ "generic" ][ "execution_onknees2_hostage_manhandled_guarded" ]	 = "takedown_room2B_hostageB";
	level.scr_stub[ "generic" ][ "execution_onknees2_hostage_manhandled_guarded_idle" ][ 0 ]	 = "takedown_room2B_hostageB_idle";

	level.scr_stub[ "generic" ][ "execution_onknees2_hostage_manhandled_guarded_prepare_idleV2" ][ 0 ]	 = "takedown_room2A_hostageB_start_idle";
	level.scr_stub[ "generic" ][ "execution_onknees2_hostage_manhandled_guardedV2" ]	 = "takedown_room2A_hostageB";
	level.scr_stub[ "generic" ][ "execution_onknees2_hostage_manhandled_guarded_idleV2" ][ 0 ]	 = "takedown_room2A_hostageB_end_idle";

	add_slowmo_breach_custom_function( "execution_onknees2_soldier", ::_slomo_breach_executioner_pistol );
	add_slowmo_breach_custom_function( "execution_onknees2_hostage", ::_slomo_breach_executed_guy_pushed_to_floor );

	//enemy slams hostage against wall
	level.scr_stub[ "generic" ][ "execution_slamwall_soldier" ]			 = "execution_slamwall_soldier";
	level.scr_stub[ "generic" ][ "execution_slamwall_hostage" ]			 = "execution_slamwall_hostage";
	level.scr_stub[ "generic" ][ "execution_slamwall_hostage_idle" ][ 0 ]	 = "hostage_stand_idle";
	level.scr_stub[ "generic" ][ "execution_slamwall_hostage_death" ]			 = "execution_slamwall_hostage_death";
	level.scr_stub[ "generic" ][ "execution_slamwall_hostage_manhandled_prepare" ]			 = "takedown_room2A_hostageA_flee";
	level.scr_stub[ "generic" ][ "execution_slamwall_hostage_manhandled_prepare_idle" ][ 0 ] = "takedown_room2A_hostageA_hide_idle";
	level.scr_stub[ "generic" ][ "execution_slamwall_hostage_manhandled" ]	 			 = "takedown_room2A_hostageA";
	level.scr_stub[ "generic" ][ "execution_slamwall_hostage_manhandled_idle" ][ 0 ]	 = "takedown_room2A_hostageA_end_idle";

	add_slowmo_breach_custom_function( "execution_slamwall_soldier", ::_slomo_breach_executioner_pistol );
	add_slowmo_breach_custom_function( "execution_slamwall_hostage", ::_slomo_breach_executed_guy );

	//hostage shoulder-rams enemy but gets pushed to the floor and executed
	level.scr_stub[ "generic" ][ "execution_fightback_guy1_03" ]			 = "execution_fightback_guy1_03";
	level.scr_stub[ "generic" ][ "execution_fightback_guy2_03" ]			 	 = "execution_fightback_guy2_03";
	level.scr_stub[ "generic" ][ "execution_fightback_guy2_03_death" ]			 = "execution_fightback_guy2_03_death";
	level.scr_stub[ "generic" ][ "execution_fightback_guy2_03_survives" ]	 = "execution_fightback_guy2_03_survives";
	add_slowmo_breach_custom_function( "execution_fightback_guy1_03", ::_slomo_breach_executioner_pistol );
	add_slowmo_breach_custom_function( "execution_fightback_guy2_03", ::_slomo_breach_executed_guy_pushed_to_floor );

	//generic enemy surprised
	level.scr_stub[ "generic" ][ "patrol_bored_react" ]			 = "patrol_bored_react_walkstop";
	level.scr_stub[ "generic" ][ "exposed_idle_react" ]			 = "exposed_idle_reactA";
	level.scr_stub[ "generic" ][ "chess_surprise" ]				 = "parabolic_chessgame_surprise_b";
	level.scr_stub[ "generic" ][ "breach_chair_reaction_v1" ]			 = "breach_chair_reaction_v1";
	//level.scr_stub[ "generic" ][ "seated_guard_goforgun_1" ]			 = "seated_guard_goforgun_1";
	//level.scr_stub[ "generic" ][ "seated_guard_goforgun_2" ]			 = "seated_guard_goforgun_2";
	level.scr_stub[ "generic" ][ "patrol_bored_react_walkstop" ]		 = "patrol_bored_react_walkstop";
	level.scr_stub[ "generic" ][ "exposed_idle_reactA" ]				 = "exposed_idle_reactA";

	//generic hostage standalone
	level.scr_stub[ "generic" ][ "hostage_stand_react_front" ]	 = "hostage_stand_react_front";
	level.scr_stub[ "generic" ][ "hostage_stand_react_front_idle" ][ 0 ]	 = "hostage_stand_idle";
	level.scr_stub[ "generic" ][ "hostage_stand_react_front_manhandled" ]	 = "takedown_room1Alt_hostage";
	level.scr_stub[ "generic" ][ "hostage_stand_react_front_manhandled_idle" ][ 0 ]	 = "takedown_room1Alt_hostage_idle";


	// a few more anims useful for breaching
	level.scr_stub[ "generic" ][ "death_explosion_stand_B_v3" ]	 	 = "death_explosion_stand_B_v3";
	level.scr_stub[ "generic" ][ "breach_stackL_approach" ]	 		 = "breach_stackL_approach";
	level.scr_stub[ "generic" ][ "react_stand_2_run_R45" ]	 		 = "react_stand_2_run_R45";

	level.breach_death_anims[ "death_explosion_stand_B_v3" ] = true;

	add_slowmo_breach_custom_function( "hostage_stand_react_front", ::_slomo_breach_hostage_react );

	level.scr_stub[ "generic" ][ "hostage_stand_fall" ]	 		 = "hostage_stand_fall";
	level.scr_stub[ "generic" ][ "hostage_stand_fall_idle" ][ 0 ]	 		 = "hostage_knees_idle";
	level.scr_stub[ "generic" ][ "hostage_stand_fall_idle" ][ 1 ]	 		 = "hostage_knees_twitch";

	level.scr_stub[ "generic" ][ "hostage_stand_fall_manhandled" ]	 = "takedown_room1A_hostageA";
	level.scr_stub[ "generic" ][ "hostage_stand_fall_manhandled_idle" ][ 0 ]	 = "takedown_room1A_hostageA_idle";
	level.scr_stub[ "generic" ][ "hostage_stand_fall_manhandledV2" ]	 = "takedown_room1B_hostage";
	level.scr_stub[ "generic" ][ "hostage_stand_fall_manhandled_idleV2" ][ 0 ]	 = "takedown_room1B_hostage_idle";

	add_slowmo_breach_custom_function( "hostage_stand_fall", ::_slomo_breach_hostage_react );

	//enemy charges at door with a knife
	level.scr_stub[ "generic" ][ "breach_react_knife_idle" ]			   = "breach_react_knife_idle";
	level.scr_stub[ "generic" ][ "breach_react_knife_charge" ]			 = "breach_react_knife_charge";
	level.scr_stub[ "generic" ][ "breach_react_knife_charge_death" ]			 = "death_shotgun_back_v1";

	add_slowmo_breach_custom_function( "breach_react_knife_charge", ::_slomo_breach_knife_charger );

	//enemies blown back from the door explosive
	level.scr_stub[ "generic" ][ "breach_react_blowback_v1" ]			 = "breach_react_blowback_v1";
	level.scr_stub[ "generic" ][ "breach_react_blowback_v2" ]			 = "breach_react_blowback_v1";
	level.scr_stub[ "generic" ][ "breach_react_blowback_v3" ]			 = "breach_react_blowback_v1";
	level.scr_stub[ "generic" ][ "dying_crawl_back" ]			 = "dying_crawl_back";
	add_slowmo_breach_custom_function( "breach_react_blowback_v1", ::_slomo_breach_blowback_guy );
	add_slowmo_breach_custom_function( "breach_react_blowback_v2", ::_slomo_breach_blowback_guy );

	//enemies jumping behind/across desks
	level.scr_stub[ "generic" ][ "breach_react_desk_v1" ]			 = "breach_react_desk_v1";
	level.scr_stub[ "generic" ][ "breach_react_desk_v2" ]			 = "breach_react_desk_v2";
	level.scr_stub[ "generic" ][ "breach_react_desk_v3" ]			 = "breach_react_desk_v3";
	level.scr_stub[ "generic" ][ "breach_react_desk_v4" ]			 = "breach_react_desk_v4";
	level.scr_stub[ "generic" ][ "breach_react_desk_v5" ]			 = "breach_react_desk_v5";
	level.scr_stub[ "generic" ][ "breach_react_desk_v6" ]			 = "breach_react_desk_v6";

	//kicking down desk
	level.scr_stub[ "generic" ][ "breach_react_desk_v7" ]			 = "breach_react_desk_v7";
	add_slowmo_breach_custom_function( "breach_react_desk_v7", ::_slomo_breach_desk_guy );

	//guy pushing other guy out of the way
	level.scr_stub[ "generic" ][ "breach_react_push_guy1" ]			 = "breach_react_push_guy1";
	level.scr_stub[ "generic" ][ "breach_react_push_guy2" ]			 = "breach_react_push_guy2";

	//2 enemies tossing guns to one another
	level.scr_stub[ "generic" ][ "breach_react_guntoss_v1_guy1" ]			 = "breach_react_guntoss_v1_guy1";
	level.scr_stub[ "generic" ][ "breach_react_guntoss_v1_guy2" ]			 = "breach_react_guntoss_v1_guy2";
	level.scr_stub[ "generic" ][ "breach_react_guntoss_v2_guy1" ]			 = "breach_react_guntoss_v2_guy1";
	level.scr_stub[ "generic" ][ "breach_react_guntoss_v2_guy2" ]			 = "breach_react_guntoss_v2_guy2";

	//enemy hiding behind the chair
	level.scr_stub[ "generic" ][ "breach_chair_hide_reaction_v1" ]			 = "breach_chair_hide_reaction_v1";
	level.scr_stub[ "generic" ][ "breach_chair_hide_reaction_v1_death" ]	 = "covercrouch_death_1";
	level.scr_stub[ "generic" ][ "breach_chair_hide_reaction_v1_death2" ]	 = "covercrouch_death_2";

	level.scr_stub[ "generic" ][ "breach_chair_hide_reaction_v2" ]			 = "breach_chair_hide_reaction_v2";
	level.scr_stub[ "generic" ][ "breach_chair_hide_reaction_v2_death" ]	 = "breach_chair_hide_reaction_death_v2";
	add_slowmo_breach_custom_function( "breach_chair_hide_reaction_v1", ::_slomo_breach_chair_guy_normal );
	add_slowmo_breach_custom_function( "breach_chair_hide_reaction_v2", ::_slomo_breach_chair_guy_animated );

	//other hostage fighback animations (too slow and clunky...)
	//level.scr_stub[ "generic" ][ "execution_fightback_guy1_01" ]			 = "execution_fightback_guy1_01";
	//level.scr_stub[ "generic" ][ "execution_fightback_guy2_01" ]			 = "execution_fightback_guy2_01";
	level.scr_stub[ "generic" ][ "execution_fightback_guy1_02" ]			 = "execution_fightback_guy1_02";
	level.scr_stub[ "generic" ][ "execution_fightback_guy2_02" ]			 = "execution_fightback_guy2_02";

	//XXX TODO - Need to implement
	//level.scr_stub[ "generic" ][ "execution_fightback_7" ]			 = "execution_fightback_7";
	//level.scr_stub[ "generic" ][ "execution_slam_2" ]			 = "execution_slam_2";
	//level.scr_stub[ "generic" ][ "execution_shield_12" ]			 = "execution_shield_12";
	//level.scr_stub[ "generic" ][ "execution_knife_3" ]			 = "execution_knife_3";
	//level.scr_stub[ "generic" ][ "execution_knife_4" ]			 = "execution_knife_4";
	//level.scr_stub[ "generic" ][ "execution_hostage_idle_1" ]			 = "execution_hostage_idle_1";


	// fallback anims
	level.scr_anim[ "generic" ][ "hostage_knees_loop" ][ 0 ]	 = %hostage_knees_idle;
	level.scr_anim[ "generic" ][ "hostage_knees_loop" ][ 1 ]	 = %hostage_knees_twitch;

}

friendly_animations()
{
	level.scr_anim[ "generic" ][ "breach_friend_idle_01" ][ 0 ]		 = %breach_flash_R1_idle;
	level.scr_anim[ "generic" ][ "breach_friend_enter_01" ]			 = %breach_flash_R1_enter;
	level.scr_anim[ "generic" ][ "breach_friend_idle_02" ][ 0 ]		 = %breach_flash_R2_idle;
	level.scr_anim[ "generic" ][ "breach_friend_enter_02" ]			 = %breach_flash_R2_enter;
}


breach_fx_setup()
{
	AssertEx( IsDefined( self.script_fxid ), "Breach_fx at " + self.origin + " has no script_fxid" );
	AssertEx( IsDefined( self.script_slowmo_breach ), "Breach_fx at " + self.origin + " has no script_slowmo_breach" );
	fxid = self.script_fxid;
	index = self.script_slowmo_breach;
	ent = createExploder( fxid );
 	ent.v[ "origin" ] = self.origin;
 	ent.v[ "angles" ] = self.angles;
 	ent.v[ "fxid" ] = fxid;
 	ent.v[ "delay" ] = 0;
 	ent.v[ "exploder" ] = "breach_" + index;
 	ent.v[ "soundalias" ] = "nil";
}

create_slowmo_breaches_from_entities()
{
	// construct the slow mo breach scenes from breach entities in the level
	breaches = [];

	left_door_posts = GetEntArray( "breach_left_org", "targetname" );
	right_door_posts = GetEntArray( "breach_right_org", "targetname" );
	right_side_breach = GetEntArray("breach_right_active_org", "targetname");
	breach_enemy_spawners = GetEntArray( "breach_enemy_spawner", "targetname" );
	breach_hostage_spawners = GetEntArray( "breach_hostage_spawner", "targetname" );
	breach_friendlyenemy_spawners = GetEntArray( "breach_friendlyenemy_spawner", "targetname" );
	breach_friendlyhostage_spawners = GetEntArray( "breach_friendlyhostage_spawner", "targetname" );
	breach_coopenemy_spawners = GetEntArray( "breach_coopenemy_spawner", "targetname" );	// optional enemies for multi - door coop breaches for a door that neither player breaches
	breach_coophostage_spawners = GetEntArray( "breach_coophostage_spawner", "targetname" );	// optional hostages for multi - door coop breaches for a door that neither player breaches
	breach_path_solids = GetEntArray( "breach_solid", "targetname" );
	breach_door_volumes = GetEntArray( "breach_door_volume", "targetname" );
	breach_safe_volumes = GetEntArray( "breach_safe_volume", "targetname" );
	breach_triggers = GetEntArray( "trigger_use_breach", "classname" );
	breach_lookat_triggers = GetEntArray( "trigger_multiple_breachIcon", "classname" );
	breach_start_triggers = GetEntArray( "trigger_use_breach", "classname" );
	breach_damage_trigger = GetEntArray( "breach_damage_trigger", "targetname" );
	breach_leftpost_dest = GetentArray( "breach_left_org_dest", "targetname" );
	breach_rightpost_dest = GetentArray( "breach_right_org_dest", "targetname" );
	
	/#
	level.missing_animations = [];
	level.missing_animation_parameters = [];
	level.manhandled_spawners = [];
	array_thread( breach_enemy_spawners,          ::check_missing_animation );
	array_thread( breach_hostage_spawners,        ::check_missing_animation );
	array_thread( breach_friendlyenemy_spawners,  ::check_missing_animation );
	array_thread( breach_friendlyhostage_spawners,::check_missing_animation );
	array_thread( breach_coopenemy_spawners,      ::check_missing_animation );
	array_thread( breach_coophostage_spawners,    ::check_missing_animation );
	array_thread( level.manhandled_spawners,      ::check_missing_animation );

	dump_missing_anims();
	#/
	level.scr_stub = undefined;


	foreach ( post in left_door_posts )
	{
		index = post.script_slowmo_breach;
		AssertEx( IsDefined( index ), "Breach door post at " + post.origin + " had no script_slowmo_breach" );
		AssertEx( !isdefined( breaches[ index ] ), "Breach door post at " + post.origin + " used script_slowmo_breach " + index + " which is already in use elsewhere in the level. Each breach must have its own script_slowmo_breach." );

		// set up door type - default is "wood"
		doorType = "wood";
		if ( IsDefined( post.script_slowmo_breach_doortype ) )
		{
			switch( post.script_slowmo_breach_doortype )
			{
				case "wood":
				case "estate_wood":
				case "estate_wood_backwards":
				case "caves_wood":
				case "payback_wood":
				case "metal":
				case "none":
					doorType = post.script_slowmo_breach_doortype;
					break;
				default:
					AssertEx( "Illegal slowmo breach doortype " + post.script_slowmo_breach_doortype );
			}
		}

		ent = SpawnStruct();
		ent.left_post = post;
		ent.doorType = doorType;
		ent.spawners = [];
		ent.spawners[ "enemy" ] = [];
		ent.spawners[ "hostage" ] = [];
		ent.spawners[ "friendlyenemy" ] = [];
		ent.spawners[ "friendlyhostage" ] = [];
		ent.spawners[ "coopenemy" ] = [];		// optional enemies to set up at a door that is not breached by either coop player
		ent.spawners[ "coophostage" ] = [];		// optional hostages to set up at a door that is not breached by either coop player
		ent.lookat_triggers = [];
		ent.path_solids = [];
		ent.enabled = true;
		ent.door_volume = [];
		ent.room_volume = [];
		ent.safe_volume = undefined;	// Optional. Used to check if there are any live enemies in the area before allowing breach
		ent.friendly_anim_ent = [];	// used for positioning breaching friendlies on multiple - door rooms
		breaches[ index ] = ent;
	}
	
	/*
	//i can't add anymore vars to breaches (limit of 16, i guess) so I am adding this to a global
	foreach( dest in breach_leftpost_dest)
	{
		index = dest.script_slowmo_breach;
		AssertEx( IsDefined( index ), "Breach door post at " + dest.origin + " had no script_slowmo_breach" );
		AssertEx( !isdefined( breaches[ index ] ), "Breach door post at " + dest.origin + " used script_slowmo_breach " + index + " which is already in use elsewhere in the level. Each breach must have its own script_slowmo_breach." );
		
		if (!isdefined(level.intro_breaches))
			level.intro_breaches = [];
			
		level.intro_breaches[ index ].left_dest = dest;
	}
	
	//i can't add anymore vars to breaches (limit of 16, i guess) so I am adding this to a global
	foreach( dest in breach_rightpost_dest)
	{
		index = dest.script_slowmo_breach;
		AssertEx( IsDefined( index ), "Breach door post at " + dest.origin + " had no script_slowmo_breach" );
		AssertEx( !isdefined( breaches[ index ] ), "Breach door post at " + dest.origin + " used script_slowmo_breach " + index + " which is already in use elsewhere in the level. Each breach must have its own script_slowmo_breach." );
		
		if (!isdefined(level.intro_breaches))
			level.intro_breaches = [];
			
		level.intro_breaches[ index ].right_dest = dest;
	}
	*/
	

	foreach ( post in right_door_posts )
	{
		index = post.script_slowmo_breach;
		AssertEx( IsDefined( index ), "Breach door post at " + post.origin + " had no script_slowmo_breach" );
		AssertEx( IsDefined( breaches[ index ] ), "Breach door post at " + post.origin + " used script_slowmo_breach " + index + " but there is no corrosponding left_door_post with that script_slowmo_breach." );

		breaches[ index ].right_post = post;

		//create animation entity for friendly breaches from right door post
		anim_org = Spawn( "script_origin", post.origin );
		anim_org.angles = post.angles;

		// translate the anim_ent into the proper position for the animations
		ent = SpawnStruct();
		ent.entity = anim_org;
		ent.yaw = -90;
		ent translate_local();
		breaches[ index ].friendly_anim_ent = anim_org;
	}
	
	foreach ( post in right_side_breach )
	{
		index = post.script_slowmo_breach;
		AssertEx (IsDefined( post ), "post for right breach not found");
		AssertEx( IsDefined( index ), "Breach door post at " + post.origin + " had no script_slowmo_breach" );
		//AssertEx( IsDefined( breaches[ index ] ), "Breach door post at " + post.origin + " used script_slowmo_breach " + index + " but there is no corrosponding left_door_post with that script_slowmo_breach." );

		breaches[ index ].right_side_breach = post;

		//create animation entity for friendly breaches from right door post
		anim_org = Spawn( "script_origin", post.origin );
		anim_org.angles = post.angles;

		// translate the anim_ent into the proper position for the animations
		ent = SpawnStruct();
		ent.entity = anim_org;
		//ent.yaw = -90;
		ent translate_local();
		//breaches[ index ].friendly_anim_ent = anim_org;
	}

	foreach ( spawner in breach_enemy_spawners )
	{
		breaches = spawner breach_spawner_setup( breaches, "enemy" );
	}

	foreach ( spawner in breach_hostage_spawners )
	{
		breaches = spawner breach_spawner_setup( breaches, "hostage" );
	}

	foreach ( spawner in breach_friendlyenemy_spawners )
	{
		breaches = spawner breach_spawner_setup( breaches, "friendlyenemy" );
	}

	foreach ( spawner in breach_friendlyhostage_spawners )
	{
		breaches = spawner breach_spawner_setup( breaches, "friendlyhostage" );
	}
	foreach ( spawner in breach_coopenemy_spawners )
	{
		breaches = spawner breach_spawner_setup( breaches, "coopenemy" );
	}

	foreach ( spawner in breach_coophostage_spawners )
	{
		breaches = spawner breach_spawner_setup( breaches, "coophostage" );
	}

	AssertEx( breach_lookat_triggers.size, "No breach lookat trigger!" );
	foreach ( trigger in breach_lookat_triggers )
	{
		index = trigger.script_slowmo_breach;
		AssertEx( IsDefined( index ), "Breach lookat trigger at " + trigger.origin + " had no script_slowmo_breach" );
		breaches[ index ].lookat_triggers[ breaches[ index ].lookat_triggers.size ] = trigger;
		AssertEx( breaches[ index ].lookat_triggers.size < 2, "You have more than one trigger_multiple_breachIcon associated with script_slowmo_breach number " + index + ". Only one lookat trigger is allowed per breach door" );

		//get the script origin targeted by lookat trig 
		trigger_org = GetEnt( trigger.target, "targetname" );
		trigger.breach_origin = trigger_org.origin;
		AssertEx( IsDefined( trigger_org ), "Breach_lookat_trigger at " + trigger.origin + " needs to target a script_origin to be used for the breach icon." );

		//get the room volume targeted by the look_at trigger's script_origin
		room_volume = GetEnt( trigger_org.target, "targetname" );
		AssertEx( IsDefined( room_volume ), "The script origin targeted by the breach_lookat_trigger at " + trigger_org.origin + " needs to target an info_volume that encompasses the room being breached." );
		room_volume.breached = false;
		breaches[ index ].room_volume = room_volume;

		//Show icon on door origin 
		trigger_org thread breach_icon_think( trigger, index, room_volume );

		//initialize a flag for designer use (set when this room volume is breached and cleared)
		sFlagname = room_volume.script_flag;
		AssertEx( IsDefined( sFlagname ), "Breach room volume at " + room_volume.origin + " needs to have a unique script_flag key to set a flag once it has been breached and cleared." );
		flag_init( sFlagname );
	}

	foreach ( trigger in breach_start_triggers )
	{
		trigger UseTriggerRequireLookAt();
		index = trigger.script_slowmo_breach;
		AssertEx( IsDefined( index ), "Breach trigger at " + trigger.origin + " had no script_slowmo_breach" );
		breaches[ index ].trigger = trigger;
		if ( IsDefined( trigger.script_breachgroup ) )
			trigger thread breach_group_trigger_think();
	}

	foreach ( volume in breach_door_volumes )
	{
		index = volume.script_slowmo_breach;
		AssertEx( IsDefined( index ), "Breach volume at " + volume.origin + " had no script_slowmo_breach" );
		breaches[ index ].door_volume = volume;
	}

	foreach ( volume in breach_safe_volumes )
	{
		index = volume.script_slowmo_breach;
		AssertEx( IsDefined( index ), "Breach safe volume at " + volume.origin + " had no script_slowmo_breach" );
		breaches[ index ].safe_volume = volume;
	}

	foreach ( pathSolid in breach_path_solids )
	{
		index = pathSolid.script_slowmo_breach;
		AssertEx( IsDefined( index ), "Breach path solid at " + pathSolid.origin + " had no script_slowmo_breach" );
		breaches[ index ].path_solids[ breaches[ index ].path_solids.size ] = pathSolid;
	}

	foreach ( index, breach in breaches )
	{
		level thread slowmo_breach_think( breach, index );
	}

	foreach ( trigger in breach_damage_trigger )
	{
		index = trigger.script_slowmo_breach;
		Assert( IsDefined( index ) );
		trigger thread slowmo_breach_damage_trigger_think( index );
	}

	level.breach_groups = breaches;
}

/*
=============
///ScriptDocBegin
"Name: objective_breach( <obj> , <breach_index1> , <breach_index2> , <breach_index3> , <breach_index4> )"
"Summary: Adds objective positions at the correct location and name for breaching"
"Module: SlowMo Breach"
"MandatoryArg: <obj>: The index for the objective"
"OptionalArg: <breach_index1>: A breach to show the position for"
"OptionalArg: <breach_index2>: A breach to show the position for"
"OptionalArg: <breach_index3>: A breach to show the position for"
"OptionalArg: <breach_index4>: A breach to show the position for"
"Example: objective_breach( 2, breach_indices[ 0 ], breach_indices[ 1 ], breach_indices[ 2 ], breach_indices[ 3 ] );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
objective_breach( obj, breach_index1, breach_index2, breach_index3, breach_index4 )
{
	Objective_SetPointerTextOverride( obj, &"SCRIPT_WAYPOINT_BREACH" );
	objective_position( obj, ( 0, 0, 0 ) );
		
	breaches = [];
	if ( isdefined( breach_index1 ) )
	{
		breaches[ breaches.size ] = breach_index1;
	}
	if ( isdefined( breach_index2 ) )
	{
		breaches[ breaches.size ] = breach_index2;
	}
	if ( isdefined( breach_index3 ) )
	{
		breaches[ breaches.size ] = breach_index3;
	}
	if ( isdefined( breach_index4 ) )
	{
		breaches[ breaches.size ] = breach_index4;
	}
	
	count = 0;
	
	foreach ( breach_index in breaches )
	{
		assertex( isdefined( level.breach_groups[ breach_index ] ), "No breach group " + breach_index );
		
		ent = level.breach_groups[ breach_index ].left_post;
		if ( !isdefined( ent ) )
			return;
			
		right = anglestoright( ent.angles );
		origin = ent.origin + right * -22.5 + (0,0,56);
		objective_additionalposition( obj, count, origin );
		count++;
	}
}

assign_script_breachgroup_to_ents( breach_ents )
{
	foreach ( ent in breach_ents )
	{
		found_breach = false;
		foreach ( breach_index, breach_array in level.breach_groups )
		{
			foreach ( trigger in breach_array.lookat_triggers )
			{
				// close enough?
				if ( distance( ent.origin, trigger.breach_origin ) > 80 )
					continue;

				ent.script_slowmo_breach = breach_index;
				found_breach = true;
				break;
			}
			if ( found_breach )
				break;
		}
		assertex( found_breach, "Didnt find breach for " + ent.targetname + " at " + ent.origin );
	}
}

get_breach_indices_from_ents( interiorBreaches )
{
	breach_indices = [];
	foreach ( breach in interiorBreaches )
	{
		breach_indices[ breach_indices.size ] = breach.script_slowmo_breach;
	}
	return breach_indices;
}

slowmo_breach_damage_trigger_think( index )
{
	AssertEx( self.classname == "trigger_radius", "Breach damage trigger at " + self.origin + " needs to be a trigger_radius in order to work with slomo_breach script." );
	level waittill( "breaching_number_" + index );
	wait( 3 );
	ai = GetAIArray();
	ai = array_merge( ai, level.players );
	foreach ( guy in ai )
	{
		if ( guy IsTouching( self ) )
			return;
	}
	RadiusDamage( self.origin, self.radius, 500, 500 );
	self Delete();
}


icon_trigger_setup()
{
	// set the flag and then run the trigger_looking logic on it
	self.script_flag = "breach_door_icon_" + self.script_slowmo_breach;
	level thread maps\_load::trigger_looking( self );
}

breach_icon_think( trigger, index, room_volume )
{
	//self ==> the script_origin in the door targeted by the lookat trigger
	self thread breach_debug_display_animnames( room_volume );
	icon = NewHudElem();
	icon SetShader( "breach_icon", 1, 1 );
	icon.alpha = 0;
	icon.color = ( 1, 1, 1 );
	icon.x = self.origin[ 0 ];
	icon.y = self.origin[ 1 ];
	icon.z = self.origin[ 2 ];
	icon SetWayPoint( true, true );


	// spawn a hidden charge model so it gets streamed in early
	model = Spawn( "script_model", self.origin );
	model SetModel( "mil_frame_charge" );
	model HidePart( "j_frame_charge" );

	wait( 0.05 );
	sFlag = "breach_door_icon_" + index;
	flag_wait( sFlag );
	while ( !room_volume.breached )
	{
		/*
		// using objective marker for breaches now
		wait( 0.05 );
		icon FadeOverTime( 0.2 );
		while ( flag( sFlag ) )
		{
			icon.alpha = 0.3;
			wait( 0.05 );
		}
		icon FadeOverTime( 0.2 );
		icon.alpha = 0;
		*/
		wait( 0.05 );
	}
	icon Destroy();
	model Delete();
}

breach_spawner_setup( breaches, type )
{
	index = self.script_slowmo_breach;
	AssertEx( IsDefined( index ), "Breach spawner at " + self.origin + " had no script_slowmo_breach" );
	group = 0;
	if ( IsDefined( self.script_slowmo_breach_spawners ) )
	{
		if ( ( type == "enemy" ) || ( type == "hostage" ) )		// randomized decisions of which .script_slowmo_breach_spawners group only is supported for anemies / hostages in the door breached by the player...not by frienlies or other atrrangements
			group = self.script_slowmo_breach_spawners;
	}

	if ( !isdefined( breaches[ index ].spawners[ type ][ group ] ) )
		breaches[ index ].spawners[ type ][ group ] = [];

	array = breaches[ index ].spawners[ type ][ group ];
	array[ array.size ] = self;
	breaches[ index ].spawners[ type ][ group ] = array;

	if ( breaches.size )
		return breaches;
	else
		return undefined;


}



slowmo_breach_think( breach_array, breach_index )
{
	level endon ("missionfailed");
	
	// The left door post is the root of the animated elements (that aren't fx related).
	left_door_post  = breach_array.left_post;
	right_door_post = breach_array.right_post;
	//left_door_post_dest  = level.intro_breaches[ breach_index ].left_dest;
	//right_door_post_dest = level.intro_breaches[ breach_index ].right_dest;
	right_door_post_active = breach_array.right_side_breach;
	trigger = breach_array.trigger;
	solids = breach_array.path_solids;
	door_volume = breach_array.door_volume;
	room_volume = breach_array.room_volume;
	
	//there is no reason for this node to be present unless a right side breach is desired
	breach_on_right = false;
	if ( isdefined( right_door_post_active ) )
		breach_on_right = true;
	
	//setup friendly and enemy spawners add breach spawn funcs
	breach_enemies_and_hostages( breach_array, breach_index );
	
	//ensure the orientation of anim nodes are correct
	//ent = translate_post_positions( left_door_post, right_door_post, right_door_post_active, breach_on_right );

	//add "breach" text where applicable
	trigger setup_breach_hint_text();

	// pick door type
	chargeAnimModel = "breach_door_charge";
	door = decide_door_model( chargeAnimModel, breach_index, breach_array );
	
	//setup normal breach vars
	door_post = left_door_post;
	door_post.active = left_door_post;
	//door_post.active_dest  = left_door_post_dest;
	//door_post.passive_dest = right_door_post_dest;
	door_post.post = right_door_post;
	door_post.scene_models = [];
	door_post add_scene_model( "active_breacher_rig" );
	active_breacher_rig = door_post.scene_models[ "active_breacher_rig" ];
	door_post.passive_rig = "passive_breacher_rig";
	door_post.active_rig  = "active_breacher_rig";
	door_post.breach_anim = "breach_player_anim";
	door_post.active_animname = "active_breacher_3rd_person";
	door_post.passive_animname = "passive_breacher_3rd_person";

	if( breach_on_right )
	{
		door_post.active = right_door_post_active;
		door_post.isRightBreach = 1;
		door_post.post = left_door_post;
		door_post.passive_rig = "passive_breacher_rig_right";
		door_post.active_rig  = "active_breacher_rig_right";
		door_post.breach_anim = "breach_player_anim_right";
		door_post.active_animname = "active_breacher_3rd_person_right";
		door_post.passive_animname = "passive_breacher_3rd_person_right";
		door_post.scene_models[ "active_breacher_rig_right" ] = spawn_anim_model( "active_breacher_rig_right" );
		door_post.scene_models[ "active_breacher_rig_right" ] Hide();
		active_breacher_rig = door_post.scene_models[ "active_breacher_rig_right" ];
		
		//door_post.active_dest  = right_door_post_dest;
	//	door_post.passive_dest = left_door_post_dest;
		//chargeAnimModel = "breach_door_charge_right";
	}

	charge = spawn_anim_model( chargeAnimModel );
	Assert( IsDefined( charge ) );
	charge hide_notsolid();
		
	Assert( IsDefined( active_breacher_rig ) );
	AssertEx( IsSubStr( active_breacher_rig.model, "viewhands_player" ), "View hands must be player world hands, not some random model." );
 	active_breacher_rig Hide();

	passive_breacher_rig = undefined;
	if ( is_coop() )
	{
		door_post add_coop_scene_models();
		passive_breacher_rig = door_post.scene_models[ door_post.passive_rig ];// only exists in coop
		Assert( IsDefined( passive_breacher_rig ) );
		AssertEx( IsSubStr( passive_breacher_rig.model, "viewhands_player" ), "View hands must be player world hands, not some random model." );
		passive_breacher_rig Hide();
	}

	if (!isdefined(level.breach_charges))
	{
		level.breach_charges = [];
	}
	level.breach_charges[breach_index] = charge;
	
	door_post.door = door;
	door_post.charge = charge;
	door_post.breach_index = breach_index;
	
	door_post anim_first_frame_solo( door, "breach" );
	door_post.active anim_first_frame_solo( charge, "breach" );
	door_post.active anim_first_frame_solo( active_breacher_rig, door_post.breach_anim );
	if ( is_coop() )
		door_post.post anim_first_frame_solo( passive_breacher_rig, door_post.breach_anim );

//debug-------------------------------
//tag1 = spawn_tag_origin();
//tag1.origin = door_post.active.origin;
//tag2 = spawn_tag_origin();
//tag2.origin = door_post.post.origin;
//target_set (tag1);
//target_set (tag2);
//---------------------------------------

	door_post wait_for_breach_or_deletion( breach_array );

	foreach ( model in door_post.scene_models )
		model Delete();

	if ( IsDefined( trigger ) )
		trigger Delete();
	if ( IsDefined( door ) )
		door Delete();
	if ( IsDefined( charge ) )
		charge Delete();
	if ( IsDefined( left_door_post ) )
		left_door_post Delete();
	if ( IsDefined( right_door_post ) )
		right_door_post Delete();
}

breach_enemies_and_hostages( breach_array, breach_index  )
{
	breach_enemy_spawners = breach_array.spawners[ "enemy" ];
	breach_hostage_spawners = breach_array.spawners[ "hostage" ];
	
	breach_friendlyenemy_spawners = [];
	breach_friendlyhostage_spawners = [];
	breach_coopenemy_spawners = [];
	breach_coophostage_spawners = [];

	// I guess this was put in here to mitigate the error of LDs placing "script_slowmo_breach_spawners" numbers by mistake on groups of AI for friendlies (?) JK
	if ( IsDefined( breach_array.spawners[ "friendlyenemy" ][ 0 ] ) )
	{
		breach_friendlyenemy_spawners = breach_array.spawners[ "friendlyenemy" ][ 0 ];
		breach_array.spawners[ "friendlyenemy" ] = breach_friendlyenemy_spawners;
	}
	if ( IsDefined( breach_array.spawners[ "friendlyhostage" ][ 0 ] ) )
	{
		breach_friendlyhostage_spawners = breach_array.spawners[ "friendlyhostage" ][ 0 ];
		breach_array.spawners[ "friendlyhostage" ] = breach_friendlyhostage_spawners;
	}
	if ( IsDefined( breach_array.spawners[ "coopenemy" ][ 0 ] ) )
	{
		breach_coopenemy_spawners = breach_array.spawners[ "coopenemy" ][ 0 ];
		breach_array.spawners[ "coopenemy" ] = breach_coopenemy_spawners;
	}
	if ( IsDefined( breach_array.spawners[ "coophostage" ][ 0 ] ) )
	{
		breach_coophostage_spawners = breach_array.spawners[ "coophostage" ][ 0 ];
		breach_array.spawners[ "coophostage" ] = breach_coophostage_spawners;
	}

	// remove all but one random subset of the spawners
	keys = [];
	foreach ( index, spawner in breach_enemy_spawners )
	{
		keys[ index ] = index;
	}
	foreach ( index, spawner in breach_hostage_spawners )
	{
		keys[ index ] = index;
	}

	//AssertEx( keys.size, "Slowmo breach set up with no spawners!" );
	if ( keys.size )
	{
		random_key = random( keys );
		if ( IsDefined( breach_enemy_spawners[ random_key ] ) )
			breach_enemy_spawners = breach_enemy_spawners[ random_key ];
		else
			breach_enemy_spawners = [];

		if ( IsDefined( breach_hostage_spawners[ random_key ] ) )
			breach_hostage_spawners = breach_hostage_spawners[ random_key ];
		else
			breach_hostage_spawners = [];
	}

	breach_array.spawners[ "enemy" ] = breach_enemy_spawners;
	breach_array.spawners[ "hostage" ] = breach_hostage_spawners;

	//spawner callback functions for enemies and hostages
	array_thread( breach_enemy_spawners,          ::add_spawn_function, ::breach_enemy_spawner_think );
	array_thread( breach_hostage_spawners,        ::add_spawn_function, ::breach_hostage_spawner_think );
	array_thread( breach_friendlyenemy_spawners,  ::add_spawn_function, ::breach_enemy_spawner_think );
	array_thread( breach_friendlyhostage_spawners,::add_spawn_function, ::breach_hostage_spawner_think );
	array_thread( breach_coopenemy_spawners,      ::add_spawn_function, ::breach_enemy_spawner_think );
	array_thread( breach_coophostage_spawners,    ::add_spawn_function, ::breach_hostage_spawner_think );
}

translate_post_positions(left_door_post, right_door_post, right_door_post_active, breach_on_right)
{
	// translate the posts into the proper positions for the animations
	ent = SpawnStruct();
	ent.entity = left_door_post;
	ent.forward = 5;
	ent.right = 6;
	ent.yaw = -90;
	ent translate_local();
	
	ent = SpawnStruct();
	ent.entity = right_door_post;
	ent.right = -2;
	ent.yaw = 90;
	ent translate_local();
	
	//this is some bullshit. if it's coop, everything is basically fine, but single player, I need to swap the post locations not just the active breacher anims
	if (isdefined(right_door_post_active))
	{
		if(is_coop())
		{
			ent = SpawnStruct();
			ent.entity = right_door_post_active;
			ent.entity.origin = right_door_post.origin;
			ent.right = -1;
			ent.forward = 5;
			ent.yaw = 90;
			ent translate_local();
			
			ent = SpawnStruct();
			ent.entity = left_door_post;
			ent.right = -5;
			ent translate_local();
		}
		else
		{
			ent = SpawnStruct();
			ent.entity = right_door_post_active;
			ent.entity.origin = left_door_post.origin;
			ent.yaw = 90;
			ent.right = 15;
			ent translate_local();
			
			ent = SpawnStruct();
			ent.entity = left_door_post;
			ent.right = 0; //0
			ent translate_local();
		}

	}
		
	return ent;
}


decide_door_model( chargeAnimModel, breach_index, breach_array )
{
	doorAnimModel = undefined;
		
	switch( breach_array.doorType )
	{
		case "metal":
			doorAnimModel = "breach_door_model_metal";
			break;
		case "estate_wood":
			doorAnimModel = "breach_door_model_estate";
			break;
		case "estate_wood_backwards":
			doorAnimModel = "breach_door_model_estate";
			break;
		case "caves_wood":
			doorAnimModel = "breach_door_model_caves";
			break;
		case "payback_wood":
			doorAnimModel = "breach_door_model_payback";
			chargeAnimModel = "breach_door_charge_payback";
			break;
		case "wood":
		case "none":
			doorAnimModel = "breach_door_model";
			break;
		default:
			AssertEx( "Illegal slowmo breach doortype " + breach_array.doorType );
			break;
	}

	door = spawn_anim_model( doorAnimModel );
	Assert( IsDefined( door ) );
	if ( breach_array.doorType == "none" || breach_array.doorType == "estate_wood_backwards" )
		door Hide();

	level.breach_doors = [];
	level.breach_doors[ breach_index ] = door;
	
	return door;

}

setup_breach_hint_text()
{
	self SetHintString( &"SCRIPT_PLATFORM_BREACH_ACTIVATE" );
	if ( !isdefined( level.breach_use_triggers ) )
		level.breach_use_triggers = [];
	level.breach_use_triggers = array_add( level.breach_use_triggers, self );
}

breach_should_be_skipped( script_slowmo_breach )
{
	if ( !isdefined( level.skip_breach ) )
		return false;

	if ( !isdefined( level.skip_breach[ script_slowmo_breach ] ) )
		return false;

	return true;
}

coop_player_touching_valid_door_volume( door_volume, other_player )
{
	door_volumes = [];
	door_volumes[ 0 ] = door_volume;

	if ( IsDefined( door_volume.script_breachgroup ) )
	{
		door_volumes = get_door_volumes_from_breachgroup( door_volume.script_breachgroup );
	}

	foreach ( volume in door_volumes )
	{
		if ( other_player IsTouching( volume ) )
			return true;
	}
	return false;
}

get_door_volumes_from_breachgroup( breachgroup )
{
	aArray = [];
	aDoorVolumes = GetEntArray( "breach_door_volume", "targetname" );
	foreach ( volume in aDoorVolumes )
	{
		if ( ( IsDefined( volume.script_breachgroup ) ) && ( volume.script_breachgroup == breachgroup ) )
		{
			aArray[ aArray.size ] = volume;
		}
	}
	return aArray;
}

breach_participants_ready_to_proceed( player, breach_friendlies, door_volume )
{
	// Check for player proximity in co-op, no AI should be involved.
	if ( is_coop() )
	{
/*		This might need to be revisited. Currently the script doesn't support players at two
		breach points, thus being two active breachers. If we need it, we'll revisit the code
		but until then simply requiring everyone to be in the same breach volume in co-op.
		if ( !isdefined( breach_near_player( get_other_player( player ) ) ) )
			return false; */

		if ( level.single_breach_ok )
			return true;
		other_player = get_other_player( player );
		if ( other_player ent_flag_exist( "laststand_downed" ) && other_player ent_flag( "laststand_downed" ) )
			return false;
		if ( coop_player_touching_valid_door_volume( door_volume, other_player ) )
			return true;
		else
			return false;
	}

	// Do we need to care about AI friendlies at all?
	if ( breach_friendlies.size == 0 )
		return true;
	if ( !room_has_multiple_doors( door_volume ) )
		return true;

	// Check if friendlies are ready to breach...
	if ( !breach_friendlies_ready_at_other_door( door_volume, true ) )
	{
		if ( GetDvar( "breach_requires_friendlies_in_position" ) == "1" )
		{
			if ( !breachfriendlies_can_teleport( breach_friendlies, door_volume ) )
				return false;
		}
	}

	return true;
}

wait_for_breach_or_deletion( ent )
{
	level endon ("missionfailed");
	self endon ("dynamic_breach_modification");
	self endon ("death");
	trigger = ent.trigger;

	if ( !isdefined( trigger ) )
	{
		return;// the breach was deleted
	}

	door_volume = ent.door_volume;

	trigger endon( "death" );
	for ( ;; )
	{
		trigger waittill( "trigger", other, passive );

		if ( gettime() == level.breach_passive_time )
			passive = level.breach_passive_player;

		is_passive = isdefined( passive );

		if ( !ent.enabled )
			return;

		if ( isalive( other ) && !is_passive )
		{
			if ( breach_failed_to_start() )
				continue;
		}

		/*----------------------------------------------
		MAKE SURE THERE ARE NO ENEMIES, IF WE CARE
		------------------------------------------------*/	
		if ( ( IsDefined( ent.safe_volume ) ) && ( !is_specialop() ) )
		{
			if ( IsPlayer( other ) && IsAlive( other ) )
			{
				enemies = ent.safe_volume get_ai_touching_volume( "axis" );
				if ( enemies.size )
				{
					thread breach_too_many_enemies_hint();
					continue;
				}
			}
		}

		/*----------------------------------------------
		TRIGGER THE PLAYER BREACH, FRIENDLY BREACH, OR JUST OPEN THE DOOR
		------------------------------------------------*/	
		breach_friendlies = get_available_breachfriendlies( door_volume );

		if ( IsPlayer( other ) && IsAlive( other ) )
		{
			if ( breach_should_be_skipped( trigger.script_slowmo_breach ) )
				break;

			if ( breach_participants_ready_to_proceed( other, breach_friendlies, door_volume ) )
			{
				if ( player_breach( ent, other ) )
					break;
			}
			else
			{
				thread breach_friendly_hint();
			}
		}
		else
		if ( breach_friendlies.size )
		{
			friendlies_breach( ent, breach_friendlies );
			break;
		}
		else
		{
			breachless_door_opens( ent );
			break;
		}
	}
}

breachfriendlies_can_teleport( breachFriendlies, door_volume )
{
	numGuysReady = 0;

	player_volume = get_player_volume( door_volume );

	foreach ( guy in breachFriendlies )
	{
		if ( IsDefined( player_volume ) )
		{
			if ( guy goalpos_within_volume( player_volume ) )
			{
				continue;
			}
		}

		if ( !guy friendly_can_teleport() )
		{
			continue;
		}

		numGuysReady++;
	}

	if ( numGuysReady >= 2 )
	{
		return true;
	}

	return false;
}

friendly_can_teleport()
{
	if ( player_can_see_ai( self ) )
	{
		return false;
	}

	if ( Distance( level.player.origin, self.origin ) < 96 )
	{
		return false;
	}

	return true;
}

breach_friendly_hint()
{
	if ( is_coop() )
	{
		if ( breach_laststand_check () )
			thread breach_hint_create( &"SO_INFILTRATE_INTRO_REVIVE_HINT" );
		// Both players must be near a door to breach
		else
			thread breach_hint_create( &"SCRIPT_BREACH_NEED_PLAYER" );
	}
	else
	{
		// Waiting for friendlies to get in position...
		thread breach_hint_create( &"SCRIPT_BREACH_NEED_FRIENDLY" );
	}
}

breach_laststand_check()
{
	foreach ( player in level.players )
		if (isdefined ( player.laststand ) && player.laststand )
			return true;
	
	return false;
	
}

breach_too_many_enemies_hint()
{
	// Cannot breach. Clear the area of all enemies
	thread breach_hint_create( &"SCRIPT_BREACH_TOO_MANY_ENEMIES" );
}

breach_reloading_hint()
{
	// Cannot breach while reloading
	thread breach_hint_create( &"SCRIPT_BREACH_RELOADING" );
}

breach_bad_weapon_hint()
{
	// Cannot breach with this weapon
	thread breach_hint_create( &"SCRIPT_BREACH_ILLEGAL_WEAPON" );
}

breach_not_ready_hint()
{
	if ( is_coop() )
	{
		// Both players are not ready to breach
		thread breach_hint_create( &"SCRIPT_BREACH_PARTNER_NOT_READY" );
		return;
	}
	
	// You are not ready to breach
	thread breach_hint_create( &"SCRIPT_BREACH_YOU_NOT_READY" );
}

breach_hint_create( message )
{
	level notify( "breach_hint_cleanup" );
	level endon( "breach_hint_cleanup" );

	hint_offset = 20;
	if ( issplitscreen() )
		hint_offset = -23;

	thread hint( message, 3, hint_offset );
	thread breach_hint_cleanup();
}

breach_hint_cleanup()
{
	level notify( "breach_hint_cleanup" );
	level endon( "breach_hint_cleanup" );

	foreach ( trigger in level.breach_use_triggers )
	{
		if ( isdefined( trigger ) )
			trigger SetHintString( "" );
	}

	level waittill_notify_or_timeout( "breaching", 3 );
	hint_fade();

	foreach ( trigger in level.breach_use_triggers )
	{
		if ( isdefined( trigger ) )
			trigger SetHintString( &"SCRIPT_PLATFORM_BREACH_ACTIVATE" );
	}
}

room_has_multiple_doors( door_volume )
{
	if ( IsDefined( door_volume.script_breachgroup ) )
		return true;

	return false;
}

breach_friendlies_take_grenades()
{
	if ( !isdefined( level.breachfriendlies ) )
		return;

	// This ensures that the friendlies were actually a part of *this* breach action later.
	level.breachfriendlies_grenades_empty = true;

	foreach ( guy in level.breachfriendlies )
	{
		guy.grenadeammo_prebreach = guy.grenadeammo;
		guy.grenadeammo = 0;
	}
}

breach_friendlies_restore_grenades()
{
	if ( !isdefined( level.breachfriendlies ) )
		return;

	if ( !isdefined( level.breachfriendlies_grenades_empty ) )
		return;

	foreach ( guy in level.breachfriendlies )
	{
		guy.grenadeammo = guy.grenadeammo_prebreach;
		guy.grenadeammo_prebreach = undefined;
	}

	level.breachfriendlies_grenades_empty = undefined;
}

breach_friendlies_ready_at_other_door( door_volume, teleportOk )
{
	script_breachgroup = door_volume.script_breachgroup;
	AssertEx( IsDefined( script_breachgroup ), "Breach door volume at " + door_volume.origin + " has no script_breachgroup assigned even though it is a multiple entry room" );

	aDoorVolumes = get_door_volumes_from_breachgroup( door_volume.script_breachgroup );

	AssertEx( aDoorVolumes.size > 1, "There should be at least 2 volumes with a script_breachgroup value of " + script_breachgroup + " but there is only " + aDoorVolumes.size );
	aDoorVolumes = array_remove( aDoorVolumes, door_volume );
	AssertEx( aDoorVolumes.size == 1, "Slomo breach only currently supports 2 doors maximum. Script_breachgroup number " + script_breachgroup + " has " + aDoorVolumes.size + 1 );

	volume_to_check = aDoorVolumes[ 0 ];

	foreach ( guy in level.breachfriendlies )
	{
		// if teleporting this guy, as long as he's on the way to the volume, we don't care
		//  if he's not touching his volume if we can't see him
		if ( IsDefined( teleportOk ) && teleportOk )
		{
			if ( guy goalpos_within_volume( volume_to_check ) )
			{
				if ( guy friendly_can_teleport() )
				{
					return true;
				}
			}
		}

		if ( guy IsTouching( volume_to_check ) )
			return true;
	}

	return false;
}

add_coop_scene_models()
{
	add_scene_model( "passive_breacher_rig" );
	add_scene_model( "active_breacher_3rd_person" );
	add_scene_model( "passive_breacher_3rd_person" );
	add_scene_model( "passive_breacher_rig_right" );
}

add_scene_model( animname )
{
	self.scene_models[ animname ] = spawn_anim_model( animname );
	self.scene_models[ animname ] Hide();
}

set_room_to_breached( trigger, room_volume )
{
	room_volume.breached = true;

	breach_notify = get_breach_notify( trigger.script_breachgroup );
	if ( IsDefined( trigger.script_breachgroup ) )
		level notify( breach_notify );

	room_volume notify( "breached" );
	trigger trigger_off();
}

breachless_door_opens( breach_array )
{
	trigger = breach_array.trigger;
	room_volume = breach_array.room_volume;
	solids = breach_array.path_solids;
	door = self.door;
	charge = self.charge;

	set_room_to_breached( trigger, room_volume );

	// DOOR OPEN: Player used trigger of door in same breachgroup, and there are NO level.breachfriendlies defined
	// (door will just open while player isn't looking)

	array_call( solids, ::ConnectPaths );
	array_thread( solids, ::self_delete );
	ent = SpawnStruct();
	ent.entity = door;
	ent.forward = 4;
	ent.right = 10;
	ent.yaw = -170;
	ent translate_local();
	charge Delete();

	if ( !is_coop() )
		return;

	//If CO-OP, wait for the room to be breached so we can spawn AI
	while ( !room_volume.breached )
		wait( 0.05 );

	//spawn specific coop AI or the AI that would have spawned if the player had breached that door
	breach_enemy_spawners = undefined;
	breach_hostage_spawners = undefined;

	if ( breach_array.spawners[ "coopenemy" ].size )
	{
		breach_enemy_spawners = breach_array.spawners[ "coopenemy" ];
		breach_hostage_spawners = breach_array.spawners[ "coophostage" ];
	}
	else
	{
		breach_enemy_spawners = breach_array.spawners[ "enemy" ];
		breach_hostage_spawners = breach_array.spawners[ "hostage" ];
	}

	if ( breach_enemy_spawners.size )
		array_call( breach_enemy_spawners, ::StalingradSpawn );

	if ( breach_hostage_spawners.size )
		array_call( breach_hostage_spawners, ::StalingradSpawn );
}

friendlies_breach( breach_array, aBreachFriendlies )
{
	trigger = breach_array.trigger;
	door_volume = breach_array.door_volume;
	room_volume = breach_array.room_volume;
	breach_enemy_spawners = breach_array.spawners[ "enemy" ];
	breach_hostage_spawners = breach_array.spawners[ "hostage" ];
	breach_friendlyenemy_spawners = breach_array.spawners[ "friendlyenemy" ];
	breach_friendlyhostage_spawners = breach_array.spawners[ "friendlyhostage" ];
	solids = breach_array.path_solids;
	charge = self.charge;
	player_rig = self.scene_models[ self.active_rig ];

	set_room_to_breached( trigger, room_volume );
	// FRIENDLY BREACH: Player used trigger of door in same breachgroup, and there are level.breachfriendlies defined and available
	anim_ent = breach_array.friendly_anim_ent;

	player_volume = get_player_volume( door_volume );

	breachRequiresFriendlies = ( GetDvar( "breach_requires_friendlies_in_position" ) == "1" );
	if ( !breachRequiresFriendlies )
	{
		// override teleport if they're already there and we can rely on normal breaching logic
		if ( IsDefined( player_volume ) && breach_friendlies_ready_at_other_door( player_volume ) )
		{
			// now that we are switching from teleport logic to regular logic, pare down the breachfriendlies array:
			//  make sure that we restrict breaching only to guys who are in the door volume
			foreach ( guy in aBreachFriendlies )
			{
				if ( !guy IsTouching( door_volume ) )
				{
					aBreachFriendlies = array_remove( aBreachFriendlies, guy );
				}
			}
			AssertEx( aBreachFriendlies.size, "Couldn't find any breach friendlies!" );

			breachRequiresFriendlies = true;
		}
	}

	if ( breachRequiresFriendlies )
	{
		breaching_friendly1 = getClosest( anim_ent.origin, aBreachFriendlies );
	}
	else
	{
		breaching_friendly1 = get_teleport_optimized_breachfriendly( anim_ent.origin, door_volume, aBreachFriendlies, player_volume );
	}

	AssertEx( IsDefined( breaching_friendly1 ), "Can't get an AI to breach from position 1 (breaching_friendly1)." );

	aBreachFriendlies = array_remove( aBreachFriendlies, breaching_friendly1 );

	// spawn the guys in the room
	if ( breach_friendlyenemy_spawners.size )
	{
		level.breachenemies = array_spawn( breach_friendlyenemy_spawners, true );
	}

	if ( breach_friendlyhostage_spawners.size )
		array_call( breach_friendlyhostage_spawners, ::StalingradSpawn );

	array_call( solids, ::ConnectPaths );
	array_thread( solids, ::self_delete );

	breaching_friendly1 thread friendly_breach( 1, anim_ent, room_volume );

	if ( aBreachFriendlies.size )
	{
		if ( breachRequiresFriendlies )
		{
			// if they're required to be at the breach volume already, the next closest guy is our second breacher
			breaching_friendly2 = getClosest( anim_ent.origin, aBreachFriendlies );
		}
		else
		{
			// if teleporting, be more selective
			breaching_friendly2 = get_teleport_optimized_breachfriendly( anim_ent.origin, door_volume, aBreachFriendlies, player_volume );
		}

		// we don't HAVE to have a second breaching friendly
		if ( IsDefined( breaching_friendly2 ) )
		{
			breaching_friendly2 thread friendly_breach( 2, anim_ent, room_volume );
		}
		else
		{
			PrintLn( "Second friendly breaching position couldn't be filled because all possible breach friendlies to teleport are visible to the player." );
		}
	}

	wait( 1 );

	breach_friendlies_take_grenades();
	self anim_single_solo( player_rig, self.breach_anim );
}

get_player_volume( door_volume )
{
	player_volume = undefined;

	groupedDoorVolumes = get_grouped_doorvolumes( door_volume );
	foreach ( volume in groupedDoorVolumes )
	{
		if ( level.player IsTouching( volume ) )
		{
			player_volume = volume;
			break;
		}
	}

	return player_volume;
}

// finds a friendly who's the most optimal candidate for teleporting to the spot
get_teleport_optimized_breachfriendly( breachOrigin, door_volume, breachFriendlies, player_volume )
{
	// eliminate everyone the player can see and who's in the player breach volume
	sortedGuys = [];
	foreach ( guy in breachFriendlies )
	{
		if ( IsDefined( player_volume ) )
		{
			if ( guy goalpos_within_volume( player_volume ) )
			{
				continue;
			}
		}

		if ( !guy friendly_can_teleport() )
		{
			continue;
		}

		sortedGuys[ sortedGuys.size ] = guy;
	}

	if ( !sortedGuys.size )
	{
		//println( "All possible breach friendlies to teleport are visible to the player." );
		return undefined;
		//sortedGuys = breachFriendlies;
	}

	// before we consider goal positions, the closest guy is the best
	sortedGuys = get_array_of_closest( breachOrigin, sortedGuys );
	bestMatch = sortedGuys[ 0 ];

	// if anyone has their goalpos set to within the doorvolume, that's the best guy
	foreach ( guy in sortedGuys )
	{
		// see if his goalpos is inside the door volume
		if ( guy goalpos_within_volume( door_volume ) )
		{
			bestMatch = guy;
			break;
		}
	}

	return bestMatch;
}

goalpos_within_volume( volume )
{
	if ( IsDefined( self.goalpos ) )
	{
		// offset the goalpos vertically a bit to compensate for volume not touching ground
		if ( origin_within_volume( self.goalpos + ( 0, 0, 40 ), volume ) )
		{
			return true;
		}
	}

	return false;
}

origin_within_volume( origin, volume )
{
	testOrg = Spawn( "script_origin", origin );
	returnVal = false;

	if ( testOrg IsTouching( volume ) )
	{
		returnVal = true;;
	}

	testOrg Delete();
	return returnVal;
}

get_grouped_doorvolumes( doorVolume )
{
	grouped_volumes = [];
	grouped_volumes[ 0 ] = doorVolume;

	if ( IsDefined( doorVolume.script_breachgroup ) )
	{
		foreach ( breach in level.breach_groups )
		{
			if ( !IsDefined( breach.door_volume ) )
			{
				continue;
			}

			if ( breach.door_volume == doorVolume )
			{
				continue;
			}

			if ( !IsDefined( breach.door_volume.script_breachgroup ) )
			{
				continue;
			}

			if ( IsDefined( breach.door_volume.script_breachgroup ) && breach.door_volume.script_breachgroup == doorVolume.script_breachgroup )
			{
				grouped_volumes[ grouped_volumes.size ] = breach.door_volume;
			}
		}
	}

	return grouped_volumes;
}

sort_breachers( ent, breach_players )
{
	// if active player is to the right of the door switch active and passive.
	active = breach_players[ "active" ];

	vec1 = anglestoright( self.angles );
	vec2 = vectornormalize( active.origin -  ent.trigger.origin );
	dot = VectorDot( vec1, vec2 );
	if ( dot < 0 )
	{
		breach_players[ "active" ] = breach_players[ "passive" ];
		breach_players[ "passive" ] = active;
	}
	return breach_players;
}

player_breach( ent, player )
{
	AssertEx( IsDefined( player ), "player_breach() was called but player is undefined" );
	AssertEx( IsDefined( ent ), "player_breach() was called but ent is undefined" );

	breach_players = [];
	breach_players[ "active" ] = player;
	
	assert( isdefined ( self.scene_models ));
	assert( isdefined ( self.scene_models[ self.active_rig ]));
	
	active_breacher_rig = self.scene_models[ self.active_rig ];
	also_passive_breaching = false;
	passive_breacher_rig = undefined;
	if ( is_coop() && !level.single_breach_ok )
	{
		breach_players[ "passive" ] = get_other_player( breach_players[ "active" ] );
		passive_breacher_rig = self.scene_models[ self.passive_rig ];

		breach_array = breach_near_player( breach_players[ "passive" ] );
		AssertEx( IsDefined( breach_array ), "player_breach() was called in co-op but all players were not in position for breaching" );
		if ( breach_array == ent )
		{
			// Someone is breaching passively at this breach
			also_passive_breaching = true;
			breach_array.room_volume.has_passive_breacher = true;

			// Find out who...
			breach_players = self sort_breachers( ent, breach_players );
		}
		else
		{
			// other player breaches over there
			level.breach_passive_player = breach_players[ "passive" ];
			level.breach_passive_time = gettime();
			breach_array.trigger notify( "trigger", breach_players[ "passive" ], "passive" );
		}
	}

	breach_players[ "active" ] EnableBreaching();
	if ( also_passive_breaching )
		breach_players[ "passive" ] DisableWeapons();

	foreach ( player in breach_players )
	{
		if ( !isdefined( level.slowmo_breach_disable_stancemod ) )
		{
			player EnableInvulnerability();
			player DisableWeaponSwitch();
			player DisableOffhandWeapons();
			player AllowCrouch( false );
			player AllowProne( false );
			player AllowSprint( false );
			player AllowJump( false );
		}
		player _disableUsability();

		//don't get a .prebreachCurrentWeapon twice by mistake during multiple entry point breaches
		if ( !isdefined( player.prebreachCurrentWeapon ) )
			player.prebreachCurrentWeapon = player GetCurrentWeapon();
	}

	level notify( "breaching" );
	level notify( "breaching_number_" + self.script_slowmo_breach );
	
	setsaveddvar( "objectiveHide", true );
	
	room_volume = ent.room_volume;
	set_room_to_breached( ent.trigger, room_volume );

	// Time to set stuff based on whether or not primary breacher has a special breach anim	
	breach_sound_delay = undefined;
	is_special_breach = IsDefined( level.has_special_breach_anim[ breach_players[ "active" ].prebreachCurrentWeapon ] );
	if ( is_special_breach )
	{
		level.slowmo_breach_start_delay = 2.25;
		set_door_charge_anim_special();
		breach_sound_delay = 0.5;
	}
	else
	{
		level.slowmo_breach_start_delay = 2.15;
		set_door_charge_anim_normal();
		breach_sound_delay = 0.20;
	}

	//breach_players[ "active" ] delayCall( breach_sound_delay, ::playsound, "detpack_wall_plant" );// 0.4
	breach_players[ "active" ] thread play_detpack_plant_sound( breach_sound_delay );
	
	//need to reset these variables differently for coop, otherwise number of enemies is mis-calculated
	if ( is_coop() )
	{
		if ( !isdefined( level.player_one_already_breached ) ) 
		{
			level.breachEnemies_alive = 0;
			level.breachEnemies_active = 0;
			level.player_one_already_breached = true;
		}
	}
	//Always reset these variables to zero if we are not in co-op
	else
	{
		level.breachEnemies_alive = 0;
		level.breachEnemies_active = 0;
	}

	// Spawn the enemies in the room
	breach_enemy_spawners = ent.spawners[ "enemy" ];
	
	//ensure spawner list is valid
	breach_enemy_spawners array_removeUndefined( breach_enemy_spawners );
	array_call( breach_enemy_spawners, ::StalingradSpawn );

	// Spawn the hostages in the room
	breach_hostage_spawners = ent.spawners[ "hostage" ];
	array_call( breach_hostage_spawners, ::StalingradSpawn );

	// Smoothly hooks the player up to the animating tag
	assert (isdefined (breach_players[ "active" ]));
	assert (isdefined (active_breacher_rig));
	breach_players[ "active" ] PlayerLinkToBlend( active_breacher_rig, "tag_player", 0.2, 0.1, 0.1 );
	if ( IsDefined( breach_players[ "active" ].dont_unlink_after_breach ) )
		thread open_up_fov( 0.2, active_breacher_rig, "tag_player", 45, 45, 90, 45 );

	if ( also_passive_breaching )
	{
		breach_players[ "passive" ] PlayerLinkToBlend( passive_breacher_rig, "tag_player", 0.2, 0.1, 0.1 );
		if ( IsDefined( breach_players[ "passive" ].dont_unlink_after_breach ) )
			thread open_up_fov( 0.2, passive_breacher_rig, "tag_player", 45, 45, 90, 45 );
	}

	breach_players[ "active" ] thread take_prebreach_weapons();

	if ( !is_special_breach )
		wait( 0.05 );

	charge = self.charge;
	self.active thread anim_single_solo( charge, "breach" );
	charge show();

	breach_players[ "active" ] thread restore_prebreach_weapons();

	pause_breach_cleanup = false;
	if ( also_passive_breaching )
	{
		self.post thread anim_single_solo( passive_breacher_rig, self.breach_anim );
		
		breach_players[ "passive" ].animname = self.passive_animname;
		breach_players[ "passive" ] thread anim_single_solo( breach_players[ "passive" ], self.breach_anim );
		breach_players[ "passive" ] thread enable_passive_weapons();
		
		// eschmidt: fill the clip of the passive player and set prebreachCurrentWeapon to undefined to fix a bug with multiple breaches
		breach_players[ "passive" ] thread restore_prebreach_weapons();

		breach_players[ "active" ].animname = self.active_animname;
		breach_players[ "active" ] thread anim_single_solo( breach_players[ "active" ], self.breach_anim );
	}

	//this fires off the primary breach anim with the notetracks in it. it's a hack, but works fine
	if (!is_coop() && isdefined(self.isRightBreach ))
		thread play_primary_breachanim( self.breach_index );

	self.active anim_single_solo( active_breacher_rig, self.breach_anim );

	level notify( "sp_slowmo_breachanim_done" );
	
	//debug
	if ( isdefined( self.active_dest ) && isdefined( self.passive_dest ))
	{
		thing1 = spawn_tag_origin();
		thing1.origin = self.active_dest.origin;
		thing2 = spawn_tag_origin();
		thing2.origin = self.passive_dest.origin;
	}
	

	//check for dead enemies
	thread flag_set_when_room_cleared( room_volume );

	// This moved to after the animation to ensure the paths aren't cleared.
	// Otherwise the AI breacher is likely to stick his head into the explosion.
	solids = ent.path_solids;
	array_call( solids, ::ConnectPaths );
	array_thread( solids, ::self_delete );

	foreach ( player in breach_players )
	{
		if ( IsDefined( player.dont_unlink_after_breach ) )
		{
			pause_breach_cleanup = true;
			special_gulag_adjustment();
		}
		else
		{
			player Unlink();
		}

		player Show();
	}

	if ( pause_breach_cleanup )
	{
		// if script wants the player to stay stuck in the breach
		level waittill( "breach_concludes" );
	}

	// Don't stop breaching until we are ready to put player back in normal state.
	// Otherwise you get the charge animation playing because that's the "raise weapon" anim during breaches.
	breach_players[ "active" ] DisableBreaching();
	foreach ( player in breach_players )
	{
		if ( !isdefined( level.slowmo_breach_disable_stancemod ) )
		{
			player DisableInvulnerability();
			player EnableWeaponSwitch();
			player EnableOffhandWeapons();
			player AllowCrouch( true );
			player AllowProne( true );
			player AllowSprint( true );
			player AllowJump( true );
		}
		
		player _enableUsability();
	}
	
	return true;
}

play_primary_breachanim( num )
{
	anime = "breach_player_anim" ;
	temp  = spawn_anim_model( "passive_breacher_rig", (level.players[0].origin) );
	temp.breach_index = num;
	temp hide();
	temp  anim_single_solo( temp, anime);
	temp  delete();
}

play_detpack_plant_sound( breach_sound_delay )
{
	self endon( "death" );
	wait( breach_sound_delay );
	self playsound( "detpack_wall_plant" );
}

flag_set_when_room_cleared( room_volume )
{
	sFlagName = room_volume.script_flag;
	level endon( sFlagName );
	aEnemies = room_volume get_ai_touching_volume( "bad_guys" );
	waittill_dead( aEnemies );
	level notify( "breach_room_has_been_cleared" );
	level.breachenemies = undefined;
	flag_set( sFlagName );
}

take_prebreach_weapons()
{
	// give the usp_scripted weapon, which plays the charge setting and breaching viewmodel & camera animation
	self GiveWeapon( "usp_scripted" );
	self SwitchToWeaponImmediate( "usp_scripted" );

	// must quick switch back to the weapon if it has a special breach anim
	if ( IsDefined( level.has_special_breach_anim[ self.prebreachCurrentWeapon ] ) )
		self SwitchToWeaponImmediate( self.prebreachCurrentWeapon );
}

restore_prebreach_weapons()
{
	wait( 0.5 );

	self TakeWeapon( "usp_scripted" );

	if ( IsDefined( self.prebreachCurrentWeapon ) )
	{
		weapon = self.prebreachCurrentWeapon;
		self SwitchToWeapon( weapon );

		// if we're on easy/normal, make sure we have at least one magazine's worth of ammo for the active weapon
		if ( self should_topoff_breach_weapon( weapon ) )
		{
			clipSize = WeaponClipSize( weapon );
			if ( self GetWeaponAmmoClip( weapon ) < clipSize )
				self SetWeaponAmmoClip( weapon, clipSize );
		}

		self.prebreachCurrentWeapon = undefined;
	}
}

enable_passive_weapons()
{
	wait 2.2;
	self EnableWeapons();
}

should_topoff_breach_weapon( weapon )
{
	if ( level.gameskill > 1 )
	{
		return false;
	}
	
	if ( IsDefined( level.breach_no_auto_reload ) )
	{
		return !level.breach_no_auto_reload;
	}

	if ( !IsDefined( self.prebreachCurrentWeapon ) )
	{
		return false;
	}

	if ( weapon != self.prebreachCurrentWeapon )
	{
		return false;
	}

	return true;
}

friendly_breach( stackPosition, anim_ent, room_volume )
{
	sFlagName = room_volume.script_flag;

	if ( stackPosition == 2 )
	{
		sAnimIdle = "breach_friend_idle_02";
		sAnimEnter = "breach_friend_enter_02";
	}
	else
	{
		sAnimIdle = "breach_friend_idle_01";
		sAnimEnter = "breach_friend_enter_01";
	}

	self.breaching = true;
	invulnerableBeforeBreach = true;
	if ( !isdefined( self.magic_bullet_shield ) )
	{
		invulnerableBeforeBreach = false;
		self thread magic_bullet_shield();
	}

	wait( 0.5 );
	self ForceTeleport( anim_ent.origin, anim_ent.angles );
	anim_ent thread anim_generic_loop( self, sAnimIdle, "stop_idle" );
	self SetGoalPos( self.origin );
	wait( 3 );

	self thread friendlies_shoot_while_breaching( stackPosition );
	anim_ent notify( "stop_idle" );

	anim_ent anim_generic( self, sAnimEnter );
	self SetGoalPos( self.origin );
	level notify( "friendlies_finished_breach" );

	//wait until all enemies dead before stopping magic_bullet_sheild
	flag_wait( sFlagName );

	//restore vulnerability (if they were vulnerable in the first place)
	if ( !invulnerableBeforeBreach )
		self stop_magic_bullet_shield();

	self.breaching = undefined;
}

friendlies_shoot_while_breaching( stackPosition )
{
	//friendlies fire scripted bullets when weapons are lined up with breach enemies
	if ( stackPosition == 1 )
		wait( 1 );
	else
		wait( 2 );

	level endon( "friendlies_finished_breach" );
	level endon( "breach_room_has_been_cleared" );

	while ( !isdefined( level.breachenemies ) )
		wait( 0.05 );
	while ( ( IsDefined( level.breachenemies ) ) && ( level.breachenemies.size ) )
	{
		wait( 0.05 );
		if ( !isdefined( level.breachenemies ) )
			break;
		level.breachenemies = remove_dead_from_array( level.breachenemies );
		foreach ( enemy in level.breachenemies )
		{
			if ( ( !isalive( enemy ) ) || ( !isdefined( enemy ) ) )
				continue;

			enemy_head_org = enemy GetTagOrigin( "tag_eye" );
			myGunPos = self GetMuzzlePos();
			myEyeOffset = ( self GetShootAtPos() - myGunPos );
			if ( self CanShoot( enemy_head_org, myEyeOffset ) )
			{
				MagicBullet( self.weapon, self GetMuzzlePos(), enemy_head_org );
				BulletTracer( self GetMuzzlePos(), enemy_head_org, true );
				wait( 0.5 );
			}
		}
	}
}

get_available_breachfriendlies( volume )
{
	available_friendlies = [];

	if ( !isdefined( level.breachfriendlies ) )
	{
		return available_friendlies;
	}

	// don't want dead/removed guys to be considered
	available_friendlies = array_removeDead( level.breachfriendlies );

	breachRequiresFriendlies = ( GetDvar( "breach_requires_friendlies_in_position" ) == "1" );

	foreach ( guy in available_friendlies )
	{
		// remove him if he's already breaching
		if ( ( IsDefined( guy.breaching ) ) && ( guy.breaching == true ) )
		{
			available_friendlies = array_remove( available_friendlies, guy );
			continue;
		}

		// if the breach requires that friendlies walk there, and the guy hasn't walked there yet, remove him
		if ( breachRequiresFriendlies && !guy IsTouching( volume ) )
		{
			available_friendlies = array_remove( available_friendlies, guy );
			continue;
		}
	}

	return available_friendlies;
}

get_breach_notify( script_breachgroup )
{
	if ( !isdefined( script_breachgroup ) )
		script_breachgroup = "none";
	return "A door in breach group " + script_breachgroup + " has been activated.";
}

breach_group_trigger_think()
{
	//self ==> the breach trigger calling the function
	// Waits for any other trigger in the breachGroup to be activated, then cancels its breach functionality (creaks opens the door)
	sBreachGroup = self.script_breachgroup;
	breach_notify = get_breach_notify( sBreachGroup );
	level waittill( breach_notify );
	waittillframeend;// give other players a chance to breach here before fake breaching it
	self notify( "trigger" );
}

slowmo_player_cleanup()
{
	AssertEx( IsPlayer( self ), "slowmo_player_cleanup() called on a non-player." );

	if ( IsDefined( level.playerSpeed ) )
		self SetMoveSpeedScale( level.playerSpeed );
	else
		self SetMoveSpeedScale( 1 );
}

slowmo_begins( rig )
{
	if ( ( IsDefined( level.breaching ) ) && ( level.breaching == true ) )
	{
		return;
	}
	level.breaching = true;
	flag_set( "breaching_on" );

	level notify( "slowmo_go" );
	level endon( "slowmo_go" );

	slomoLerpTime_in = 0.5;
	slomoLerpTime_out = 0.75;

	slomobreachplayerspeed = 0.2;
	if ( IsDefined( level.slomobreachplayerspeed ) )
	{
		slomobreachplayerspeed = level.slomobreachplayerspeed;
	}

	player = level.player;
	other_player = undefined;
	if ( is_coop() )
		other_player = get_other_player( player );

	player thread play_sound_on_entity( "slomo_whoosh" );
	player thread player_heartbeat();

	thread slomo_breach_vision_change( ( slomoLerpTime_in * 2 ), ( slomoLerpTime_out / 2 ) );

	thread slomo_difficulty_dvars();
	flag_clear( "can_save" );
	slowmo_start();
	
	player thread set_breaching_variable();
	if ( IsDefined( other_player ) )
		other_player thread set_breaching_variable();
	
	player AllowMelee( false ); ///melee is useless and causes bugs during slomo
	if ( IsDefined( other_player ) )
		other_player AllowMelee( false ); ///melee is useless and causes bugs during slomo
	
	slowmo_setspeed_slow( 0.25 );
	slowmo_setlerptime_in( slomoLerpTime_in );
	slowmo_lerp_in();
	
	player SetMoveSpeedScale( slomobreachplayerspeed );
	if ( IsDefined( other_player ) )
		other_player SetMoveSpeedScale( slomobreachplayerspeed );

	startTime = GetTime();
	endTime = startTime + ( level.slomobreachduration * 1000 );

	// Only worry about weapon status changes in single player.
	if ( !is_coop() )
		player thread catch_weapon_switch();// called after the player weapons are force - changed, so this is cool to put here

	player thread catch_mission_failed();
	if ( IsDefined( other_player ) )
		other_player thread catch_mission_failed();

	// be lenient about some slowmo-ending activities at the start of the slowmo period
	reloadIgnoreTime = 500;// ms
	switchWeaponIgnoreTime = 1000;

	// wait for slowmo timeout, or wait for conditions to be met that will interrupt the slowmo
	for ( ;; )
	{
		if ( IsDefined( level.forced_slowmo_breach_slowdown ) )
		{
			if ( !level.forced_slowmo_breach_slowdown )
			{
				if ( IsDefined( level.forced_slowmo_breach_lerpout ) )
					slomoLerpTime_out = level.forced_slowmo_breach_lerpout;
				break;
			}

			wait( 0.05 );
			continue;
		}

		if ( GetTime() >= endTime )
			break;

		// is everyone dead?
		if ( (level.breachEnemies_active <= 0) && (level.breachignoreEnemy_count == false) )
		{
			// lerp out a little slower so we see more of the last guy's death in slowmo
			slomoLerpTime_out = 1.15;
			break;
		}

		// Only worry about weapon status changes in single player.
		if ( !is_coop() )
		{
			// did the player start reloading after the reload ignore time window has expired?
			if ( player.lastReloadStartTime >= ( startTime + reloadIgnoreTime ) )
			{
				break;
			}

			// did player switch weapons?
			if ( player.switchedWeapons && ( ( GetTime() - startTime ) > switchWeaponIgnoreTime ) )
			{
				break;
			}
		}

		// did we fail the mission during slowmo?
		if ( is_specialop() && flag( "special_op_terminated" ) )
		{
			break;
		}
		
		// did we fail the mission during slowmo?
		if ( player.breach_missionfailed || ( is_coop() && other_player.breach_missionfailed ) )
		{
			// lerp out fast so we can restart faster
			slomoLerpTime_out = 0.5;
			break;
		}

		wait( 0.05 );
	}

	level notify( "slowmo_breach_ending", slomoLerpTime_out );
	level notify( "stop_player_heartbeat" );

	player thread play_sound_on_entity( "slomo_whoosh" );
	slowmo_setlerptime_out( slomoLerpTime_out );
	slowmo_lerp_out();
	
	player AllowMelee( true ); ///melee is useless and causes bugs during slomo
	if ( IsDefined( other_player ) )
		other_player AllowMelee( true ); ///melee is useless and causes bugs during slomo
		
	player delaythread( slomoLerpTime_out, ::clear_breaching_variable );
	if ( IsDefined( other_player ) )
		other_player delaythread( slomoLerpTime_out, ::clear_breaching_variable );
	
	slowmo_end();
	flag_set( "can_save" );
	
	level.player_one_already_breached = undefined;
	
	player slowmo_player_cleanup();
	if ( IsDefined( other_player ) )
		other_player slowmo_player_cleanup();

	level notify( "slomo_breach_over" );
	level.breaching = false;
	flag_clear( "breaching_on" );
	
	setsaveddvar( "objectiveHide", false );
}

set_breaching_variable()
{
	self endon( "clear_breaching_variable" );
	
	self.isbreaching = 1;
	self.breaching_shots_fired = 0;
	self.achieve_slowmo_breach_kills = undefined;
	ammo = self getcurrentweaponclipammo();
	
	self notifyonPlayercommand( "player_shot_fired", "+attack" );
	self notifyonPlayercommand( "player_shot_fired", "+attack_akimbo_accessible" );	// support accessibility control scheme
			
	while( isdefined( self.isbreaching ) )
	{
		self waittill( "player_shot_fired" );		
		
		self.breaching_shots_fired = ammo - self getcurrentweaponclipammo();
		
		wait .05;
				
		while( self isFiring() )
		{
			self.breaching_shots_fired = ammo - self getcurrentweaponclipammo();	
			wait .05;
		}
	}
}

clear_breaching_variable()
{
	self.isbreaching = undefined;
	self thread notify_delay( "clear_breaching_variable", .25 );
}

slomo_difficulty_dvars()
{
	//Get current viewKick values
	old_bg_viewKickScale = GetDvar( "bg_viewKickScale" ); 	// 0.8
	old_bg_viewKickMax = GetDvar( "bg_viewKickMax" );		// 90
	SetSavedDvar( "bg_viewKickScale", 0.3 );		// make the view kick a little easier
	SetSavedDvar( "bg_viewKickMax", "15" );			// make the view kick a little easier

	SetSavedDvar( "bullet_penetration_damage", 0 ); // Disable bullet penetration damage so that hostages are less likely to be shot through enemies


	level waittill( "slowmo_breach_ending" );
	
	//Restore all values when slomo is over
	
	SetSavedDvar( "bg_viewKickScale", old_bg_viewKickScale );	// set view kick back to whatever it was
	SetSavedDvar( "bg_viewKickMax", old_bg_viewKickMax );		// set view kick back to whatever it was
	
	wait( 2 );	//wait a few seconds before resetting bullet dvar
	SetSavedDvar( "bullet_penetration_damage", 1 ); 			// Re - enable bullet penetration

}


slomo_breach_vision_change( lerpTime_in, lerpTime_out )
{
	if ( !IsDefined( level.slomoBasevision ) )
	{
		return;
	}

	VisionSetNaked( "slomo_breach", lerpTime_in );

	level waittill( "slowmo_breach_ending", newLerpTime );

	// maybe update the lerp time in case things changed in the main thread
	if ( IsDefined( newLerpTime ) )
	{
		lerpTime_out = newLerpTime;
	}

	wait( 1 );
	VisionSetNaked( level.slomoBasevision, lerpTime_out );
}

player_heartbeat()
{
	level endon( "stop_player_heartbeat" );
	while ( true )
	{
		self PlayLocalSound( "breathing_heartbeat" );
		wait .5;
	}
}

catch_weapon_switch()
{
	level endon( "slowmo_breach_ending" );

	self.switchedWeapons = false;

	self waittill_any( "weapon_switch_started", "night_vision_on", "night_vision_off" );

	self.switchedWeapons = true;
}

catch_mission_failed()
{
	level endon( "slowmo_breach_ending" );

	self.breach_missionfailed = false;

	level waittill( "mission failed" );

	self.breach_missionfailed = true;
}

breach_enemy_spawner_think()
{
	reference = self.spawner;
	self endon( "death" );
	self add_damage_function( ::record_last_player_damage );
	self thread breach_enemy_ignored_by_friendlies();
	self thread breach_enemy_ragdoll_on_death();
	level thread breach_enemy_track_status( self );

	// I set this up so that you can specify a custom reference node since it just assumes that they should always be using self as the reference node
	if ( IsDefined( self.script_parameters ) && string_starts_with( self.script_parameters , "reference" ) )
	{
		reference = GetEnt( self.script_parameters , "targetname" );
	}
	
	self.reference = reference;
	reference anim_generic_first_frame( self, self.animation );
	AssertEx( IsDefined( level.scr_anim[ "generic" ][ self.animation ] ), "Have not defined level.scr_anim[ generic ] for anim " + self.animation );

	if ( IsDefined( level._slowmo_functions[ self.animation ] ) )
	{
		// run a custom function for this animation set
		custom_function = level._slowmo_functions[ self.animation ];
		self thread [[ custom_function ]]();
	}

	self.grenadeammo = 0;
	self.allowdeath = true;
	self.health = 10;
	self.baseaccuracy = 5000;

	if ( IsDefined( self.script_threatbias ) )
	{
		self.threatbias = self.script_threatbias;
	}

	if ( IsDefined( level.breach_death_anims[ self.animation ] ) )
		self.skipDeathAnim = true;

	wait( level.slowmo_breach_start_delay );

	self script_delay();

	self notify( "starting_breach_reaction" );
	level notify( "breach_enemy_anims" );
	reference anim_generic( self, self.animation );
	self notify( "finished_breach_start_anim" );
}

record_last_player_damage( damage, attacker, direction_vec, point, type, modelName, tagName )
{
	if ( !isalive( attacker ) )
		return;
	if ( !IsPlayer( attacker ) )
		return;
	if ( !self IsBadGuy() )
		return;

	level.last_player_damage = GetTime();
}

breach_enemy_ignored_by_friendlies()
{
	//all enemies in a breached room should be ignored by friendlies
	//until slowmo is over. Any friendlies that are actually breaching
	//will fire their weapons anyway through anim notetracks
	self endon( "death" );
	if ( !flag( "no_mercy" ) )
		self.ignoreme = true;
	level waittill_either( "slomo_breach_over", "friendlies_finished_breach" );
	if ( IsDefined( self ) )
		self.ignoreme = false;
}

// immediately sends guys without custom death anims into ragdoll when they die
//  in a breach situation.  helps eliminate animation popping
//
// NOTE: kill this with breach_enemy_cancel_ragdoll() if you have a scripted death animation
//  that matches the breach start animation
breach_enemy_ragdoll_on_death()
{
	self endon( "breach_enemy_cancel_ragdoll_death" );

	// cause death.gsc to do StartRagdollFromImpact() for us
	self.ragdoll_immediate = true;

	msg = self waittill_any_return( "death", "finished_breach_start_anim" );

	if ( msg == "finished_breach_start_anim" )
	{
		self.ragdoll_immediate = undefined;
	}
}

breach_enemy_cancel_ragdoll()
{
	self notify( "breach_enemy_cancel_ragdoll_death" );
	self.ragdoll_immediate = undefined;
}

breach_enemy_track_status( enemy )
{
	level.breachEnemies_active++;

	ent = SpawnStruct();
	ent.enemy = enemy;

	ent thread breach_enemy_waitfor_death( enemy );
	ent thread breach_enemy_waitfor_death_counter( enemy );
	ent thread breach_enemy_catch_exceptions( enemy );
	ent thread breach_enemy_waitfor_breach_ending();

	ent waittill( "breach_status_change", status );

	level.breachEnemies_active--;

	ent = undefined;
}

breach_enemy_waitfor_death( enemy )
{
	self endon( "breach_status_change" );

	enemy waittill( "death" );
	self notify( "breach_status_change", "death" );
}

// Special version of the death wait that allows us to know when all enemies are dead.
breach_enemy_waitfor_death_counter( enemy )
{
	level.breachEnemies_alive++;

	enemy waittill( "death" );

	level.breachEnemies_alive--;
	if ( level.breachEnemies_alive <= 0 )
		breach_friendlies_restore_grenades();

	level notify( "breach_all_enemies_dead" );
}

breach_enemy_catch_exceptions( enemy )
{
	self endon( "breach_status_change" );

	while ( IsAlive( enemy ) )
	{
		wait( 0.05 );
	}

	self notify( "breach_status_change", "exception" );
}

breach_enemy_waitfor_breach_ending()
{
	self endon( "breach_status_change" );

	level waittill( "slowmo_breach_ending" );
	self notify( "breach_status_change", "breach_ending" );
}

breach_hostage_spawner_think()
{
	self endon( "death" );
	self.breachfinished = false;
	reference = self.spawner;
	self.reference = reference;

	self endon( "cancel_breach_behavior" );
	
	if (!isdefined( level.no_hostage_fail ) || !level.no_hostage_fail)
	{
		self thread hostage_mission_fail();
		self.no_friendly_fire_penalty = true;	//mission fail is done separately for hostages
	}

	//find out if anim is a loop. assuming you want the hostage to play the looping anim
	//TODO-- allow for animations other than "GENERIC" anims
	if ( isAnimLoop() )
	{
		self anim_generic_loop( self, self.animation, "stop_idle" );
	}
	else
	{
		self anim_generic_first_frame( self, self.animation );
	}

	self.health = 10;	// needs to be low to allow enemies and player to kill with one bullet
	self.IgnoreRandomBulletDamage = true;	// don't get killed by stray bullets from friendlies or enemies
	wait( level.slowmo_breach_start_delay );
	
	if ( IsDefined(self.special_breach_exit ))
		return;

	
	if ( IsDefined( level._slowmo_functions[ self.animation ] ) )
	{
		// run a custom function for this animation set
		custom_function = level._slowmo_functions[ self.animation ];
		self thread [[ custom_function ]]();
	}

	self.allowdeath = true;
	reference anim_generic( self, self.animation );

	self notify( "finished_breach_start_anim" );

	//self.IgnoreRandomBulletDamage = false;	//allow to be killed by stray bullets now that sequence is over

	if ( IsDefined( self.skipEndingIdle ) )
		return;

	if ( anim_exists( self.animation + "_idle" ) )
		thread anim_generic_loop( self, self.animation + "_idle", "stop_idle" );
	else
	{
		loop = "hostage_knees_loop";
		self thread anim_generic_loop( self, loop, "stop_idle" );
	}
	self.breachfinished = true;
}


hostage_health_regen()
{
	baseHealth = self.health;
	self endon( "death" );
	self endon( "saved" );
	while ( IsDefined( self ) )
	{
		self waittill( "damage", amount, attacker );
		if ( IsDefined( attacker ) )
		{
			if ( IsPlayer( attacker ) )
			{
				//self DoDamage( self.health + 100, self.origin, level.player );
				self Kill( self.origin, level.player );
				break;
			}
			else if ( ( IsDefined( attacker.team ) ) && ( attacker.team == "allies" ) )
				self.health = baseHealth;

		}
	}
}

get_room_volume_from_slomo_breach_number( script_slomo_breach )
{
	return level.breach_groups[ script_slomo_breach ].room_volume;
}

hostage_mission_fail()
{
	if ( is_specialop() )
		level endon( "special_op_terminated" );
		
	level endon( "mission failed" );
	baseHealth = self.health;
	missionFailedHostage = false;
	self thread hostage_health_regen();
	room_volume = get_room_volume_from_slomo_breach_number( self.script_slowmo_breach );
	if ( GetDvar( "hostage_missionfail" ) == "0" )
		return;

	while ( IsDefined( self ) )
	{
		self waittill( "death", attacker );
		// Mission failed. A hostage was executed.

		if ( IsDefined( attacker ) )
		{
			if ( IsPlayer( attacker ) )
			{
				level notify( "player_shot_a_hostage" );
				// Mission failed. You killed a hostage.
				waittillframeend;// give level.last_player_damage a chance to get set
				//if ( ( level.last_player_damage + 50 < GetTime() ) || ( level.last_player_damage == GetTime() ) )
				if ( level.last_player_damage == GetTime() )
				{
					// Mission failed. You shot a hostage through an enemy.\nSome weapons have deep bullet penetration.
					//breach_set_deadquote( &"SCRIPT_MISSIONFAIL_KILLEDHOSTAGE_THROUGH_ENEMY", "@SCRIPT_MISSIONFAIL_KILLEDHOSTAGE_THROUGH_ENEMY" );
					
					// Mission failed. You killed a hostage. 
					//(not doing bullet penetration anymore on any skill level, but will leave check here in case 
					//we want a message about shotguns, etc)
					breach_set_deadquote( &"SCRIPT_MISSIONFAIL_KILLEDHOSTAGE", "@SCRIPT_MISSIONFAIL_KILLEDHOSTAGE" );
				}
				else
				{
					// Mission failed. You killed a hostage.
					breach_set_deadquote( &"SCRIPT_MISSIONFAIL_KILLEDHOSTAGE", "@SCRIPT_MISSIONFAIL_KILLEDHOSTAGE" );
				}

				missionFailedHostage = true;
			}
			else if ( ( IsDefined( attacker.team ) ) && ( attacker.team == "allies" ) && ( !IsPlayer( attacker ) ) )
			{
				AssertMsg( "hostage was accidentally killed by a friendly...need a script fix for this" );
				// Mission failed. A hostage was executed.
				breach_set_deadquote( &"SCRIPT_MISSIONFAIL_HOSTAGEEXECUTED", "@SCRIPT_MISSIONFAIL_HOSTAGEEXECUTED" );
				missionFailedHostage = true;
			}
			else
			{
				if ( self coop_breached_from_same_door_in_a_muliti_door_room( room_volume ) )
				{
					// Mission failed. A hostage was executed.\nTry breaching from opposite doors.
					breach_set_deadquote( &"SCRIPT_MISSIONFAIL_HOSTAGEEXECUTED_USEMULTIDOOR", "@SCRIPT_MISSIONFAIL_HOSTAGEEXECUTED_USEMULTIDOOR" );
				}
				else
				{
					// Mission failed. A hostage was executed.
					breach_set_deadquote( &"SCRIPT_MISSIONFAIL_HOSTAGEEXECUTED", "@SCRIPT_MISSIONFAIL_HOSTAGEEXECUTED" );
				}

				missionFailedHostage = true;
			}
		}

		if ( missionFailedHostage == true )
		{
			thread maps\_utility::missionFailedWrapper();
			level notify( "mission failed" );
		}
	}
}

// This is lame and ugly, but the cleanest for now.
breach_set_deadquote( deadquote, so_deadquote )
{
	assert( isdefined( deadquote ) && isdefined( so_deadquote ) );
	
	if ( is_specialop() )
		maps\_specialops::so_force_deadquote( so_deadquote );
	else
		setDvar( "ui_deadquote", deadquote );
}

coop_breached_from_same_door_in_a_muliti_door_room( room_volume )
{
	if ( !is_specialop() )
		return false;
	if ( !is_coop() )
		return false;
	if ( IsDefined( room_volume.has_passive_breacher ) )
		return true;
	else
		return false;
}

isAnimLoop()
{
	if( isarray( level.scr_anim[ "generic" ]))
	{
		if( isarray( level.scr_anim[ "generic" ][ self.animation ]))
		{
			if( isdefined( level.scr_anim[ "generic" ][ self.animation ][0]))
			{
				return true;
			}
		}
	}
	return false;
}

#using_animtree( "script_model" );
script_models()
{
	// wooden door
	level.scr_anim[ "breach_door_model" ][ "breach" ]	 = %breach_player_door_v2;
	level.scr_animtree[ "breach_door_model" ]					 = #animtree;
	level.scr_model[ "breach_door_model" ]						 = "com_door_01_handleright";

	level.scr_anim[ "breach_door_hinge" ][ "breach" ]	 = %breach_player_door_hinge_v1;
	level.scr_animtree[ "breach_door_hinge" ] 				 = #animtree;
	level.scr_model[ "breach_door_hinge" ] 						 = "com_door_piece_hinge";
	
	// metal door
	level.scr_anim[ "breach_door_model_metal" ][ "breach" ] = %breach_player_door_v2;
	level.scr_animtree[ "breach_door_model_metal" ] 			  = #animtree;
	level.scr_model[ "breach_door_model_metal" ]				    = "breach_door_metal_right";

	level.scr_anim[ "breach_door_hinge_metal" ][ "breach" ]	= %breach_player_door_metal;
	level.scr_animtree[ "breach_door_hinge_metal" ]				  = #animtree;
	level.scr_model[ "breach_door_hinge_metal" ] 				    = "breach_door_metal_right_dst";

	// explosive charge
	// this gets overwritten at time of breach
	level.scr_anim[ "breach_door_charge" ][ "breach" ]		    = %breach_player_frame_charge_v3;
	level.scr_animtree[ "breach_door_charge" ] 					      = #animtree;
	level.scr_model[ "breach_door_charge" ] 					        = "mil_frame_charge";
	
//	level.scr_anim[ "breach_door_charge_right" ][ "breach" ]	= %breach_player_frame_charge_v3;
//	level.scr_animtree[ "breach_door_charge_right" ] 					= #animtree;
//	level.scr_model[ "breach_door_charge_right" ] 					  = "mil_frame_charge";
	
	//level.scr_animtree[ "desk" ]			 = #animtree;
	//level.scr_anim[ "desk" ][ "breach_react_desk_v7_desk" ] 	 = %breach_react_desk_v7_desk;

	//level.scr_animtree[ "chair" ]			 = #animtree;
	//level.scr_anim[ "chair" ][ "breach_chair_hide_reaction_v2_chair" ] 	 = %breach_chair_hide_reaction_v2_chair;
	//level.scr_anim[ "chair" ][ "breach_chair_hide_reaction_death_v2_chair" ]			 = %breach_chair_hide_reaction_death_v2_chair;
}

set_door_charge_anim_normal()
{
	level.scr_anim[ "breach_door_charge" ][ "breach" ]			 = %breach_player_frame_charge_v3;
}

set_door_charge_anim_special()
{
	level.scr_anim[ "breach_door_charge" ][ "breach" ]			 = %breach_player_frame_charge;
}


#using_animtree( "generic_human" );
generic_animations()
{

}


//#using_animtree( "player" );
#using_animtree( "multiplayer" );
player_animations()
{
	if ( !isdefined( level.slowmo_viewhands ) )
		level.slowmo_viewhands = "viewhands_player_sas_woodland";

	level.scr_animtree[ "active_breacher_rig" ]								 = #animtree;
	level.scr_model[ "active_breacher_rig" ]							  	 = level.slowmo_viewhands;
	level.scr_anim[ "active_breacher_rig" ][ "breach_player_anim" ]			 = %breach_coop_player_1;
	
	level.scr_animtree[ "active_breacher_rig_right" ]								 = #animtree;
	level.scr_model[ "active_breacher_rig_right" ]							  	 = level.slowmo_viewhands;
	//level.scr_anim[ "active_breacher_rig_right" ][ "breach_player_anim_right" ]			 = %ny_harbor_door_breach_player;
	level.scr_anim[ "active_breacher_rig_right" ][ "breach_player_anim_right" ]			 = %breach_coop_player_2;
	
	level.scr_animtree[ "passive_breacher_rig" ] 							               = #animtree;
	level.scr_model[ "passive_breacher_rig" ] 								               = level.slowmo_viewhands;
	level.scr_anim[ "passive_breacher_rig" ][ "breach_player_anim" ]		     = %breach_coop_player_1;
	
	level.scr_animtree[ "passive_breacher_rig_right" ] 							               = #animtree;
	level.scr_model[ "passive_breacher_rig_right" ] 								               = level.slowmo_viewhands;
	level.scr_anim[ "passive_breacher_rig_right" ][ "breach_player_anim_right" ]	 = %breach_coop_player_1;
	
	if ( is_coop() )
	{
		level.scr_anim[ "active_breacher_rig" ][ "breach_player_anim" ]			     = %breach_coop_player_1;

		level.scr_animtree[ "active_breacher_3rd_person" ] 					           	 = #animtree;
		level.scr_model[ "active_breacher_3rd_person" ] 						             = level.slowmo_viewhands;
		level.scr_anim[ "active_breacher_3rd_person" ][ "breach_player_anim" ]	 = %breach_coop_player_1_3rdPerson; 
		level.scr_anim[ "active_breacher_3rd_person" ][ "root" ]			         	 = %code;

		level.scr_animtree[ "passive_breacher_rig" ] 							               = #animtree;
		level.scr_model[ "passive_breacher_rig" ] 								               = level.slowmo_viewhands;
		level.scr_anim[ "passive_breacher_rig" ][ "breach_player_anim" ]		     = %breach_coop_player_2;

		level.scr_animtree[ "passive_breacher_3rd_person" ] 					           = #animtree;
		level.scr_model[ "passive_breacher_3rd_person" ] 						             = level.slowmo_viewhands;
		level.scr_anim[ "passive_breacher_3rd_person" ][ "breach_player_anim" ]	 = %breach_coop_player_2_3rdPerson; 
		level.scr_anim[ "passive_breacher_3rd_person" ][ "root" ]				         = %code;
		
		//for right side breach
		level.scr_anim[ "active_breacher_rig_right" ][ "breach_player_anim_right" ] = %breach_coop_player_2;

		level.scr_animtree[ "active_breacher_3rd_person_right" ] 					           	 = #animtree;
		level.scr_model[ "active_breacher_3rd_person_right" ] 						             = level.slowmo_viewhands;
		level.scr_anim[ "active_breacher_3rd_person_right" ][ "breach_player_anim_right" ]	 = %breach_coop_player_2_3rdPerson; //changes from player 2
		level.scr_anim[ "active_breacher_3rd_person_right" ][ "root" ]			         	 = %code;



		level.scr_animtree[ "passive_breacher_3rd_person_right" ] 					           = #animtree;
		level.scr_model[ "passive_breacher_3rd_person_right" ] 						             = level.slowmo_viewhands;
		level.scr_anim[ "passive_breacher_3rd_person_right" ][ "breach_player_anim_right" ]	 = %breach_coop_player_2_3rdPerson; //changes from player 1
		level.scr_anim[ "passive_breacher_3rd_person_right" ][ "root" ]				         = %code;
	}

	// can add custom functions to occur when the breach happens
	level._slowmo_breach_funcs = [];
	add_breach_func( ::breach_explosion );

	addNotetrack_customFunction( "active_breacher_rig", "explode", ::breach_functions );
	addNotetrack_customFunction( "active_breacher_rig", "slowmo", ::slowmo_begins );
	addNotetrack_customFunction( "passive_breacher_rig", "explode", ::breach_functions );
	addNotetrack_customFunction( "passive_breacher_rig", "slowmo", ::slowmo_begins );

	if(is_coop())
	{
		addNotetrack_customFunction( "passive_breacher_rig_right", "explode", ::breach_functions );
		addNotetrack_customFunction( "passive_breacher_rig_right", "slowmo", ::slowmo_begins );
	}
}

add_breach_func( func )
{
	/#
	foreach ( existing_func in level._slowmo_breach_funcs )
	{
		AssertEx( func != existing_func, "Breach func was added twice" );
	}
	#/

	level._slowmo_breach_funcs[ level._slowmo_breach_funcs.size ] = func;
}

breach_functions( breach_rig )
{
	foreach ( func in level._slowmo_breach_funcs )
	{
		thread [[ func ]]( breach_rig );
	}
}

breach_explosion( breach_rig )
{
	if ( !isdefined( self.reverse_breach ))
	{
		breach_array = level.breach_groups[ self.breach_index ];
		self.reverse_breach = false;
	}
	else
		breach_array = self;
		

	expSound = undefined;
	destroyedModelAlias = undefined;
	switch( breach_array.doorType )
	{
		case "wood":
			expSound = "detpack_explo_wood";
			destroyedModelAlias = "breach_door_hinge";
			break;
		case "estate_wood":
			expSound = "detpack_explo_wood";
			destroyedModelAlias = "breach_door_hinge_estate";
			break;
		case "estate_wood_backwards":
			expSound = "detpack_explo_wood";
			destroyedModelAlias = undefined;
			break;
		case "caves_wood":
			expSound = "detpack_explo_wood";
			destroyedModelAlias = "breach_door_hinge_caves";
			break;
		case "payback_wood":
			expSound = "pybk_breach_blast";
			destroyedModelAlias = "breach_door_hinge_payback";
			break;
		case "metal":
			expSound = "detpack_explo_metal";
			destroyedModelAlias = "breach_door_hinge_metal";
			break;
		case "none":
			expSound = "detpack_explo_concrete";
			break;
		default:
			AssertEx( "Illegal slowmo breach doortype " + breach_array.doorType );
			break;
	}
	
	if( !isdefined( self.charge ))
		self.charge = level.breach_charges[self.breach_index ];
	
	if( isdefined( self.charge ))
	{
		if ( IsDefined( expSound ) )
			thread play_sound_in_space( expSound, self.charge.origin );
		exploder( "breach_" + self.breach_index );
		thread breach_rumble( self.charge.origin );
		
		self.charge Delete();
	}

	level notify( "breach_explosion" );

	if ( IsDefined( destroyedModelAlias ) && !self.reverse_breach )
	{
		destroyedModel = spawn_anim_model( destroyedModelAlias );
		self.post thread anim_single_solo( destroyedModel, "breach" );
	}

	wait( 0.05 );

	if ( IsDefined( self.door ) )
	{
		self.door Delete();
	}
}

breach_rumble( org )
{
	dummy = Spawn( "script_origin", org );
	dummy.origin = org;
	dummy PlayRumbleOnEntity( "grenade_rumble" );
	wait( 4 );
	dummy Delete();

}

// CUSTOM FUNCTIONS FOR SLOWMO BREACH GUYS


_slomo_breach_executioner_knife()
{
	self endon( "death" );
	self.doDamageToAll = true;
	self thread knife_guy_cleanup();
}

_slomo_breach_executioner_pistol()
{
	self endon( "death" );
	self.doDamageToAll = true;
	self thread _slomo_breach_pistol_guy();
}


_slomo_breach_pistol_guy()
{
	self animscripts\notetracks::noteTrackPistolPickup();
}

_slomo_breach_blowback_guy()
{
	self endon( "death" );
	//self breach_enemy_cancel_ragdoll();
	if ( !flag( "no_mercy" ) )
		self.ignoreme = true;
	self.forceLongDeath = true;
	self waittill_notetrack_or_damage( "bodyfall large" );
	self waittill( "finished_breach_start_anim" );
	self DoDamage( self.health - 1, self.origin );
}

_slomo_breach_executed_guy()
{
	if ( ( self.animation == "execution_knife_hostage" ) || ( self.animation == "execution_knife2_hostage" ) )
		self thread _slomo_breach_knife_hostage_death();

	//Additional check to see if this hostage will be manhandled
	if ( self will_be_manhandled() )
		self thread get_manhandled();

	self.skipEndingIdle = true;	// will skip the generic knees loop that most hostages go into
	self endon( "death" );
	self set_generic_deathanim( self.animation + "_death" );
	self waittill( "finished_breach_start_anim" );
	
	//don't play end looping anim if we want to manhandle this hostage
	if ( IsDefined( self.manhandled ) )
		return;
	
	if ( anim_exists( self.animation + "_survives" ) )
	{
		self.reference anim_generic( self, self.animation + "_survives" );
	}
	thread anim_generic_loop( self, self.animation + "_idle", "stop_idle" );
	self.breachfinished = true;
}

_slomo_breach_hostage_react()
{
	//Additional check to see if this hostage will be manhandled
	if ( self will_be_manhandled() )
		self thread get_manhandled();

	self.skipEndingIdle = true;	// will skip the generic knees loop that most hostages go into

	self waittill( "finished_breach_start_anim" );

	//don't play end looping anim if we want to manhandle this hostage
	if ( IsDefined( self.manhandled ) )
		return;

	if ( anim_exists( self.animation + "_idle" ) )
		thread anim_generic_loop( self, self.animation + "_idle", "stop_idle" );
	self.breachfinished = true;
}

_slomo_breach_c4_hostage()
{
	eChair = Spawn( "script_model", self.reference.origin );
	eChair SetModel( "com_restaurantchair_2" );
	eChair.angles = self.reference.angles + ( 0, 90, 0 );
	eChair.origin = self.reference.origin;
}

_slomo_breach_knife_hostage_death()
{
	eKiller = get_closest_ai( self.origin, "bad_guys" );
	self waittill( "finished_breach_start_anim" );
	if ( ( IsDefined( eKiller ) ) && ( IsAlive( eKiller ) ) )
	{
		PlayFXOnTag( getfx( "breach_knife_execution" ), self, "J_neck" );
		self thread play_sound_on_entity( "melee_knife_hit_body" );
		self Kill();
	}
}

_slomo_breach_executed_guy_pushed_to_floor()
{
	self.skipEndingIdle = true;	// will skip the generic knees loop that most hostages go into
	self endon( "death" );

	//Additional check to see if this hostage will be manhandled
	if ( self will_be_manhandled() )
		self thread get_manhandled();

	self waittillmatch( "single anim", "bodyfall large" );
	self set_generic_deathanim( self.animation + "_death" );
	self waittill( "finished_breach_start_anim" );
	self anim_generic( self, self.animation + "_survives" );

	//don't play end looping anim if we want to manhandle this hostage
	if ( IsDefined( self.manhandled ) )
		return;
	self thread anim_generic_loop( self, "hostage_knees_loop", "stop_idle" );
	self.breachfinished = true;
}

_slomo_breach_fightback_guy()
{
	self.skipEndingIdle = true;	// will skip the generic knees loop that most hostages go into
	self endon( "death" );
	self waittill( "finished_breach_start_anim" );
	self set_generic_deathanim( self.animation + "_death" );
	self anim_generic( self, self.animation + "_survives" );
	self thread anim_generic_loop( self, "hostage_knees_loop", "stop_idle" );
	self.breachfinished = true;
}

_slomo_breach_knife_charger()
{
	self endon( "death" );
	//self breach_enemy_cancel_ragdoll();
	//self set_generic_deathanim( self.animation + "_death" );
	self waittillmatch( "single anim", "stab" );
	wait( .1 );
	self thread knife_guy_stabs_player();
	self waittill( "finished_breach_start_anim" );
	//self gun_recall();
}

knife_guy_stabs_player()
{
	player = get_closest_player( self.origin );
	dist = Distance( player.origin, self.origin );
	if ( dist <= 50 )
	{
		player PlayRumbleOnEntity( "grenade_rumble" );
		player thread play_sound_on_entity( "melee_knife_hit_body" );
		player EnableHealthShield( false );
		player EnableDeathShield( false );
		waittillframeend;
		player DoDamage( player.health + 50000, self GetTagOrigin( "tag_weapon_right" ), self );
		player.breach_missionfailed = true;// tells slowmo to stop
	}
}

knife_guy_cleanup()
{
	wait 0.5;
	self waittill_either( "damage", "finished_breach_start_anim" );
	if ( IsDefined( self ) )
		self Detach( "weapon_parabolic_knife", "TAG_INHAND" );
}

_slomo_breach_chair_guy_normal()
{
	self endon( "death" );
	self breach_enemy_cancel_ragdoll();
	iRand = RandomIntRange( 1, 3 );
	if ( cointoss() )
		self set_generic_deathanim( self.animation + "_death" );
	else
		self set_generic_deathanim( self.animation + "_death2" );
}

_slomo_breach_chair_guy_animated()
{
	self endon( "death" );
	self breach_enemy_cancel_ragdoll();
	self set_generic_deathanim( self.animation + "_death" );
	self thread chair_animate();
	self waittill( "finished_breach_start_anim" );
	self thread _slomo_breach_chair_guy_normal();
}

chair_animate()
{
	eChair = Spawn( "script_model", self.reference.origin );
	eChair SetModel( "furniture_chair_metal01" );
	eChair.animname = "chair";
	eChair assign_animtree();
	eChair.reference = Spawn( "script_origin", self.reference.origin );
	eChair.reference.angles = self.reference.angles;
	//ent = SpawnStruct();
	//ent.entity = eChair;
	//ent.forward = 40;
	//ent translate_local();

	self waittill( "starting_breach_reaction" );
	eChair.reference thread anim_single_solo( eChair, "breach_chair_hide_reaction_v2_chair" );

	//if guy finishes breach reaction, don't play the chair tipping over when he dies
	self endon( "finished_breach_start_anim" );

	//if the guy is still alive and hasn't finished breach reaction, play the chair tipping over when he dies
	if ( IsAlive( self ) )
	{
		self waittill( "death" );
		eChair.reference thread anim_single_solo( eChair, "breach_chair_hide_reaction_death_v2_chair" );
	}
}

_slomo_breach_desk_guy()
{
	self endon( "death" );
	self thread desk_animate();
	self waittill( "finished_breach_start_anim" );
}

desk_animate()
{
	eDesk = Spawn( "script_model", self.reference.origin );
	eDesk SetModel( "furniture_long_desk_animate" );
	eDesk.animname = "desk";
	eDesk assign_animtree();
	eDesk.reference = Spawn( "script_origin", self.reference.origin );
	eDesk.reference.angles = self.reference.angles;
	//ent = SpawnStruct();
	//ent.entity = eDesk;
	//ent.forward = 40;
	//ent translate_local();
	self waittill( "starting_breach_reaction" );
	eDesk.reference thread anim_single_solo( eDesk, "breach_react_desk_v7_desk" );
}



// CUSTOM FUNCTIONS FOR SLOWMO BREACH GUYS

breach_near_player( player )
{
	foreach ( ent in level.breach_groups )
	{
		if ( player IsTouching( ent.door_volume ) )
			return ent;
	}
}

get_breach_groups()
{
	// Returns all breach groups in the level

	keys = GetArrayKeys( level.breach_groups );
	return keys;
}

make_empty_breach( group_num )
{
	// Make no AI or hostages spawn for the specified group number. The breach remains functional.

	AssertEx( IsDefined( group_num ), "You must specify a breach group number to make empty" );
	AssertEx( IsDefined( level.breach_groups[ group_num ] ), group_num + " is not a valid breach group number" );
	level.breach_groups[ group_num ].enabled = false;
}

delete_breach( group_num )
{
	// Removes the breach group and all associated entities.

	AssertEx( IsDefined( group_num ), "You must specify a breach group number to delete" );
	AssertEx( IsDefined( level.breach_groups[ group_num ] ), group_num + " is not a valid breach group number" );
	AssertEx( IsDefined( level.breach_groups[ group_num ].trigger ), "Tried to delete breach that was already deleted" );
	level.breach_groups[ group_num ].trigger Delete();
	solids = level.breach_groups[ group_num ].path_solids;
	array_call( solids, ::ConnectPaths );
	array_thread( solids, ::self_delete );
	foreach ( trigger in level.breach_groups[ group_num ].lookat_triggers )
		trigger Delete();
}

breach_debug_display_animnames( room_volume )
{

	if ( !isdefined( self ) )
		return;
	org = self.origin;
	wait( 0.05 );
	if ( GetDvar( "breach_debug" ) == "0" )
		return;
	//self ==> the script_origin in the door targeted by the lookat trigger
	aBreachAI = [];
	aAI1 = GetEntArray( "breach_enemy_spawner", "targetname" );
	aAI2 = GetEntArray( "breach_hostage_spawner", "targetname" );
	aBreachAI = array_merge( aAI1, aAI2 );
	foreach ( spawner in aBreachAI )
	{
		if ( !spawner IsTouching( room_volume ) )
			aBreachAI = array_remove( aBreachAI, spawner );
	}

	while ( !room_volume.breached )
	{
		neworg = org;
		foreach ( spawner in aBreachAI )
		{
			if ( IsDefined( spawner.animation ) )
			{
				thread debug_message( spawner.animation, neworg, 1 );
				neworg = neworg - ( 0, 0, 10 );
			}

		}

		wait( 1 );
	}

	//room_volume waittill( "breached" );
}

will_be_manhandled()
{
	if ( is_coop() )
		return false;

	if ( ( IsDefined( level.hostagemanhandle ) ) && ( level.hostagemanhandle == false ) )
		return false;

	if ( IsDefined( self.script_noteworthy ) )
	{
		return self.script_noteworthy == "manhandled" || self.script_noteworthy == "manhandled_guarded";
	}

	return false;
}

manhandler_hold()
{
	// First need all enemies dead...
	if ( level.breachEnemies_alive > 0 )
		return true;

	if ( !self.startManhandling )
		return true;

	return false;
}

get_manhandled()
{
	self endon( "death" );
	self.manhandled = true;		// will make hostage skip default ending behavior / idle
	self.readyToBeManhandled = false;
	self.startManhandling = false;
	manhandlerSpawner = undefined;
	/*-----------------------
	FIND THE MANHANDLER ASSOCIATED WITH THIS HOSTAGE
	-------------------------*/	
	if ( self.script_noteworthy == "manhandled" )
	{
		manhandlerSpawner = GetEnt( self.target, "targetname" );
		AssertEx( IsDefined( manhandlerSpawner ), "Hostage with export " + self.export + " is tagged with a script_noteworthy of 'manhandled', but is not targeting a friendly spawner that will do the manhandling." );
	}

	friendly_manhandler = undefined;	// may not spawn a manhandler if this hostage will just be guarded....the hostage getting manhandled will take care of spawning him

	/*-----------------------
	BUILD LIST OF ANIMS FOR THIS HOSTAGE
	-------------------------*/	
	sAnimManhandledPrepare = undefined;
	sAnimManhandledPrepareIdle = undefined;
	sAnimManhandled = undefined;
	sAnimManhandledIdle = undefined;
	sAnimVariationSuffix = "";

	//Is there a suffix to add to the anims? Hostages with the same breach anim
	//may have different takedowns for different rooms
	if ( IsDefined( self.script_parameters ) )
		sAnimVariationSuffix = self.script_parameters;

	//script_noteworthy defines whether hostage is taken down by a friendly or just guarded
	switch( self.script_noteworthy )
	{
		case "manhandled":
			sAnimManhandled = self.animation + "_manhandled";
			break;
		case "manhandled_guarded":
			sAnimManhandled = self.animation + "_manhandled_guarded";
			break;
	}
	sAnimManhandledIdle = sAnimManhandled + "_idle" + sAnimVariationSuffix;
	sAnimManhandledPrepare = sAnimManhandled + "_prepare" + sAnimVariationSuffix;
	sAnimManhandledPrepareIdle = sAnimManhandled + "_prepare_idle" + sAnimVariationSuffix;
	sAnimManhandled = sAnimManhandled + sAnimVariationSuffix;
	/*-----------------------
	MAKE SURE THERE ARE AT LEAST THE MANHANDLED ANIM AND THE IDLE
	-------------------------*/	
	self assert_if_anim_not_defined( sAnimManhandled );
	self assert_if_anim_not_defined( sAnimManhandledIdle );

	/*-----------------------
	SPAWN MANHANDLER OUTSIDE DOOR, ONLY FOR THE ONE GETTING TAKEN DOWN
	-------------------------*/	
	if ( self.script_noteworthy == "manhandled" )
	{
		friendly_manhandler = manhandlerSpawner spawn_ai( true );
		friendly_manhandler Hide();
		AssertEx( IsDefined( level.scr_anim[ "generic" ][ friendly_manhandler.animation ] ), "Manhandling friendly with export " + self.export + " does not have animation " + friendly_manhandler.animation + " defined in a level.scr_anim" );
		self.reference anim_generic_first_frame( friendly_manhandler, friendly_manhandler.animation );
		friendly_manhandler PushPlayer( true );
		level.manhandler = friendly_manhandler;
		friendly_manhandler.readyToManhandle = false;
		friendly_manhandler thread manhandler_think();
	}

	/*-----------------------
	WAIT UNTIL PLAYER PLANTS CHARGE
	-------------------------*/	
	wait( 1 );

	/*-----------------------
	SHOW MANHANDLER, IF THERE IS ONE TO SHOW
	-------------------------*/	
	if ( self.script_noteworthy == "manhandled" )
		friendly_manhandler Show();

	/*-----------------------
	WAIT TO FINISH REGULAR BREACH ANIM
	-------------------------*/	
	self waittill( "finished_breach_start_anim" );

	/*-----------------------
	PLAY MANHANDLE PREPARE ANIMS
	-------------------------*/	
	if ( anim_exists( sAnimManhandledPrepare ) )
	{
		self.reference anim_generic( self, sAnimManhandledPrepare );
	}

	/*-----------------------
	PLAY MANHANDLE PREPARE IDLE UNTIL MANHANDLER READY TO COME IN
	-------------------------*/	
	if ( anim_exists( sAnimManhandledPrepareIdle ) )
		self.reference thread anim_generic_loop( self, sAnimManhandledPrepareIdle, "stop_idle" );
	else
		sAnimManhandledPrepareIdle = undefined;

	self.readyToBeManhandled = true;

	/*-----------------------
	ONLY WAIT IF THE HOSTAGE HAS AN APPROPRIATE LOOP
	-------------------------*/	
	if ( IsDefined( sAnimManhandledPrepareIdle ) )
	{
		while ( self manhandler_hold() )
			wait( 0.05 );
	}
	/*-----------------------
	PLAY MANHANDLE ANIMS
	-------------------------*/	
	self.reference notify( "stop_idle" );
	self notify( "stop_idle" );

	//Play friendly manhandler anim if there
	if ( self.script_noteworthy == "manhandled" )
	{
		self.reference thread anim_generic( friendly_manhandler, friendly_manhandler.animation );
	}

	//play hostage manhandle
	self.reference anim_generic( self, sAnimManhandled );

	/*-----------------------
	PLAY MANHANDLE IDLES
	-------------------------*/	
	//Play friendly manhandler idle if there
	if ( ( IsDefined( friendly_manhandler ) ) && ( IsDefined( level.scr_anim[ "generic" ][ friendly_manhandler.animation + "_idle" ] ) ) )
	{
		self.reference thread anim_generic_loop( friendly_manhandler, friendly_manhandler.animation + "_idle", "stop_idle" );
	}

	//play hostage manhandle idle if there
	if ( IsDefined( level.scr_anim[ "generic" ][ sAnimManhandledIdle ] ) )
	{
		self.reference thread anim_generic_loop( self, sAnimManhandledIdle, "stop_idle" );
	}
}

special_gulag_adjustment()
{
	angles = level.player GetPlayerAngles();
	angles = ( 0, angles[ 1 ], 0 );
	forward = AnglesToForward( angles );
	up = AnglesToUp( angles );

	tag_origin = spawn_tag_origin();
	tag_origin.origin = level.player.origin;
	tag_origin.angles = angles;
	level.player PlayerLinkToDelta( tag_origin, "tag_origin", 1, 45, 45, 90, 45, true );

	time = 0.45;
	//tag_origin MoveTo( tag_origin.origin + forward * 32 + up * -16, time, time * 0.4, time * 0.4 );
	tag_origin MoveTo( tag_origin.origin + forward * 32 + up * -14, time, time * 0.4, time * 0.4 );
//	tag_origin thread maps\_debug::drawtagforever( "tag_origin" );
	wait( time );
	level.player SetMoveSpeedScale( 0.5 );

	thread player_slows_down();
	
	level.player unlink();
	level.price_breach_ent thread price_breach_ent_rotatesto_player(); 
	level.price_breach_ent thread price_breach_ent_movesto_player(); 
}

player_slows_down()
{
	wait( 0.25 );
	blend = level create_blend( ::player_loses_speedscale, 0.5, 0 );
	blend.time = 1.5;
}

price_breach_ent_movesto_player()
{
	self endon( "stop_following_player" );
	wait( 1.5 );
	for ( ;; )
	{
		self moveto( level.player.origin, 2, 0, 0 );
		wait( 0.05 );
	}
}

price_breach_ent_rotatesto_player()
{
	self endon( "stop_following_player" );
	ent = spawn( "script_origin", (0,0,0) );
	for ( ;; )
	{
		start = level.player.origin;
		start = set_z( start, 0 );
		end = self.origin;
		end = set_z( end, 0 );
		
		angles = vectortoangles( start - end );
		
		forward = anglestoforward( angles );
		my_forward = anglestoforward( self.angles );
		my_right = anglestoright( self.angles );

		dot = vectordot( forward, my_right );		
		ent.angles = self.angles;

		yaw_dif = abs( acos( dot ) );
		
		rotate = 2;
		if ( rotate > yaw_dif )
			rotate = yaw_dif;
			
		if ( dot < 0 )
		{
			ent addyaw( rotate );
		}
		else
		{
			ent addyaw( rotate * -1 );
		}
			
		//self rotateto( angles, 0.1, 0, 0 );	
		self rotateto( ent.angles, 0.15 );
		
		
		//println( "dot " + dot * 100 );
		//angles += (0,-90,0);
		//self rotateto( angles, 0.1, 0, 0 );
		//self moveto( level.player.origin, 0.1, 0, 0 );
		wait( 0.15 );
	}
}

player_loses_speedscale( progress, start, end )
{
	level.player setmovespeedscale( start * ( 1 - progress ) + end * progress );
}

manhandler_think()
{
	level endon( "mission failed" );
	if ( GetDvar( "hostage_missionfail" ) == "1" )
	{
		level endon( "player_shot_a_hostage" );
	}
	self thread magic_bullet_shield();
	self setFlashbangImmunity( true );
	if ( !flag( "no_mercy" ) )
		self.ignoreme = true;
	self.grenadeawareness = 0;
	wait( 1 );
	/*-----------------------
	GET POINTERS TO THE HOSTAGES I WILL MANHANDLE
	-------------------------*/	
	aHostages = [];
	aAI = GetAISpeciesArray( "neutral", "civilian" );
	foreach ( guy in aAI )
	{
		if ( !isdefined( guy.readyToBeManhandled ) )
			continue;
		if ( ( IsDefined( guy.script_slowmo_breach ) ) && ( guy.script_slowmo_breach == self.script_slowmo_breach ) )
		{
			if ( ( IsDefined( guy.script_noteworthy ) ) && ( IsSubStr( guy.script_noteworthy, "manhandled" ) ) )
				aHostages = array_add( aHostages, guy );
		}
	}
	AssertEx( aHostages.size > 0, "Manhandler with export " + self.export + " can not find any hostages with script_noteworthy containing 'manhandled*' in its script_slomo_breach number" );

	/*-----------------------
	WAIT FOR ALL ASSOCIATED HOSTAGES TO BE READY TO BE MANHANDLED
	-------------------------*/	
	iCounter = aHostages.size;
	tempArray = aHostages;
	while ( iCounter > 0 )
	{
		wait( 0.05 );
		foreach ( guy in tempArray )
		{
			// This shouldn't be necessary?
			if ( !isdefined( guy ) || guy.readyToBeManhandled == true )
			{
				tempArray = array_remove( tempArray, guy );
				iCounter--;
			}

		}
	}
	/*-----------------------
	TELL MANHANDLER TO START MANHANDLE SEQUENCE
	-------------------------*/	
	foreach ( guy in aHostages )
	{
		// This shouldn't be necessary?
		if ( IsDefined( guy ) )
			guy.startManhandling = true;
	}

}


assert_if_anim_not_defined( sAnim )
{
	AssertEx( anim_exists( sAnim ), "Hostage with export " + self.export + " does not have animation " + sAnim + " defined in level.scr_anim" );
}

anim_exists( sAnim )
{
	if ( IsDefined( level.scr_anim[ "generic" ][ sAnim ] ) )
		return true;
	else
		return false;
}

/*
=============
///ScriptDocBegin
"Name: add_slowmo_breach_custom_function( <animation> , <function> )"
"Summary: Adds a custom slowmo breach function for guys using a specific animation"
"Module: SlowMo Breach"
"MandatoryArg: <animation>: The animation the guy plays "
"OptionalArg: <function>: The function to call on this guy"
"Example: add_slowmo_breach_custom_function( "execution_onknees_soldier", ::_slomo_breach_pistol_guy );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_slowmo_breach_custom_function( animation, function )
{
	AssertEx( !isdefined( level._slowmo_functions[ animation ] ), "Tried to redefined function for slow mo breach guys with animation " + animation );
	level._slowmo_functions[ animation ] = function;
}

/*
=============
///ScriptDocBegin
"Name: add_slowmo_breacher()"
"Summary: Adds an AI to level.breachfriendlies so they will be considered as candidates to breach into rooms with multiple breach points"
"Module: SlowMo Breach"
"CallOn: Any friendly AI"
"Example: level.price add_slowmo_breacher();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_slowmo_breacher()
{
	if ( !isdefined( self ) )
		return;
	AssertEx( IsAI( self ), "add_slomo_breacher() can only be called on a friendly AI" );
	if ( !isdefined( level.breachfriendlies ) )
	{
		level.breachfriendlies = [];
		level.breachfriendlies[ 0 ] = self;
	}
	else if ( is_in_array( level.breachfriendlies, self ) )
	{
		return;
	}
	else
		level.breachfriendlies = array_add( level.breachfriendlies, self );
}

/*
=============
///ScriptDocBegin
"Name: remove_slowmo_breacher()"
"Summary: Removes an AI from level.breachfriendlies so they will not be considered as a candidate to breach into rooms with multiple breach points"
"Module: SlowMo Breach"
"CallOn: Any friendly AI"
"Example: level.price remove_slowmo_breacher();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
remove_slowmo_breacher()
{
	if ( !isdefined( self ) )
		return;
	AssertEx( IsAI( self ), "remove_slomo_breacher() can only be called on a friendly AI" );
	if ( !isdefined( level.breachfriendlies ) )
		return;
	if ( is_in_array( level.breachfriendlies, self ) )
	{
		level.breachfriendlies = array_remove( level.breachfriendlies, self );
	}
}

breach_failed_to_start()
{
	fail_funcs = [];
	fail_funcs[ fail_funcs.size ] = ::isMeleeing;
	fail_funcs[ fail_funcs.size ] = ::isSwitchingWeapon;
	fail_funcs[ fail_funcs.size ] = ::IsThrowingGrenade;

	foreach ( player in level.players )
	{
		if ( player IsReloading() && !level.override_reload)
		{
			thread breach_reloading_hint();
			return true;
		}
		
		if ( player using_illegal_breach_weapon() )
		{
			thread breach_bad_weapon_hint();
			return true;
		}
		
		foreach ( func in fail_funcs )
		{
			if ( player call [[ func ]]() )
			{
				thread breach_not_ready_hint();
				return true;
			}
		}			
	}
		
	return false;
}

using_illegal_breach_weapon()
{
	illegal_weapons = [];
	illegal_weapons[ "riotshield" ] = true;
	illegal_weapons[ "claymore" ] = true;
	illegal_weapons[ "c4" ] = true;
	if ( !level.single_breach_ok )
		illegal_weapons[ "none" ] = true;
	
	weapon = self getCurrentWeapon();
	
	return isdefined( illegal_weapons[ weapon ] );
}

slomo_sound_scale_setup()
{
	SoundSetTimeScaleFactor( "Music", 0 );
	SoundSetTimeScaleFactor( "Menu", 0 );
	SoundSetTimeScaleFactor( "local3", 0.0 );
	SoundSetTimeScaleFactor( "Mission", 0.0 );
	SoundSetTimeScaleFactor( "Announcer", 0.0 );
	SoundSetTimeScaleFactor( "Bulletimpact", .60 );
	SoundSetTimeScaleFactor( "Voice", 0.40 );
	SoundSetTimeScaleFactor( "effects2", 0.20 );
	SoundSetTimeScaleFactor( "local", 0.40 );
	SoundSetTimeScaleFactor( "physics", 0.20 );
	SoundSetTimeScaleFactor( "ambient", 0.50 );
	SoundSetTimeScaleFactor( "auto", 0.50 );
	
}