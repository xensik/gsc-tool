#include maps\_utility;
#include common_scripts\utility;
#include maps\_hud_util;
#include maps\_remotemissile_utility;


init()
{
	//should make hellfires no do friendly fire
	level.no_friendly_fire_splash_damage = true;

	if ( !isdefined( level.min_time_between_uav_launches ) )
	{
		level.min_time_between_uav_launches = 12 * 1000;
	}

	if ( !isdefined( level.remote_missile_targets ) )
	{
		level.remote_missile_targets = [];
	}

	level.last_uav_launch_time = 0 - level.min_time_between_uav_launches;
//	level.last_uav_offline_time = 0;
	level.uav_radio_offline_called = false;

	PreCacheItem( "remote_missile_detonator" );
	if (isdefined(level.uav_missile_override))
		PreCacheItem( level.uav_missile_override );
	else
		PreCacheItem( "remote_missile" );
	PreCacheShader( "veh_hud_target" );
	PreCacheShader( "veh_hud_target_offscreen" );
	PreCacheShader( "veh_hud_missile_flash" );
	PreCacheShader( "ac130_overlay_grain" );
	PreCacheShader( "remotemissile_infantry_target" );
	PreCacheShader( "remotemissile_infantry_target_2plr" );
	PreCacheShader( "hud_fofbox_self_sp" );
	PreCacheShader( "dpad_killstreak_hellfire_missile_inactive" );
	// CAMERA: UAV_DRONE_011
	PreCacheString( &"HELLFIRE_DRONE_VIEW" );
	// CAMERA: MISSILE
	PreCacheString( &"HELLFIRE_MISSILE_VIEW" );
	// -MISSILE LAUNCHED-
	PreCacheString( &"HELLFIRE_FIRE" );

	level.uav_struct = SpawnStruct();
	level.uav_struct.view_cone = 4;

	flag_init( "predator_missile_launch_allowed" );
	flag_set( "predator_missile_launch_allowed" );


	// Predator Drone has been destroyed.
	add_hint_string( "hint_predator_drone_destroyed", &"HELLFIRE_DESTROYED", ::should_break_destroyed );
							// Press^3 [{+actionslot 4}] ^7to control the Predator Drone.
	add_hint_string( "hint_predator_drone_4", 			 &"HELLFIRE_USE_DRONE", 			::should_break_use_drone );
						// Press^3 [{+actionslot 2}] ^7to control the Predator Drone.
	add_hint_string( "hint_predator_drone_2", 			 &"HELLFIRE_USE_DRONE_2", 		::should_break_use_drone );
	// Predator Drone is unavailable.
	add_hint_string( "hint_predator_drone_not_available", &"HELLFIRE_DRONE_NOT_AVAILABLE", ::should_break_available );

	if (isdefined(level.remotemissile_usethermal) && level.remotemissile_usethermal)
		VisionSetMissilecam( "missilecam" );
	else if (!isdefined(level.VISION_UAV))
		VisionSetMissilecam( "missilecam" );
	else
		VisionSetMissilecam( level.VISION_UAV );

	SetSavedDvar( "missileRemoteSpeedUp", "1000" );
	SetSavedDvar( "missileRemoteSpeedTargetRange", "6000 12000" );

	mapname = GetDvar( "mapname" );
	if ( mapname == "zzz" )
	{
	}
	else if ( mapname == "raymetest" )
	{
		SetSavedDvar( "missileRemoteSpeedUp", "500" );
		SetSavedDvar( "missileRemoteSpeedTargetRange", "3000 6000" );
	}

	add_global_spawn_function( "axis", ::missile_kill_ai );

	flag_init( "uav_reloading" );
	flag_init( "uav_collecting_stats" );
	flag_init( "uav_enabled" );
	flag_set( "uav_enabled" );

	foreach ( player in level.players )
	{
		player ent_flag_init( "controlling_UAV" );
	}
}


should_break_use_drone()
{
	break_hint = false;
	if ( IsDefined( level.uav_is_destroyed ) )
	{
		break_hint = true;
	}

	uav = self get_uav();
	if ( !isalive( uav ) )
	{
		break_hint = true;
	}

	if ( IsDefined( self.is_flying_missile ) )
	{
		break_hint = true;
	}

	// Sniper Fi Support
	if ( flag_exist( "wave_wiped_out" ) && flag( "wave_wiped_out" ) )
	{
		break_hint = true;
	}

	if ( self ent_flag_exist( "laststand_downed" ) && self ent_flag( "laststand_downed" ) )
	{
		break_hint = true;
	}

	if ( self GetCurrentWeapon() == "remote_missile_detonator" )
	{
		break_hint = true;
	}
	
	if ( flag_exist ( "no_default_uav_hint" ) && flag ( "no_default_uav_hint" ) )
	{
		break_hint = true;
	}

	return break_hint;
}

init_radio_dialogue()
{
	if ( !IsDefined( level.scr_radio ) )
	{
		level.scr_radio = [];
	}

	level.uav_radio_initialized = true;

	// Offline / Online
	level.scr_radio[ "uav_reloading" ] 				 = "cont_cmt_rearmhellfires";
	level.scr_radio[ "uav_offline" ] 				 = "cont_cmt_hellfiresoffline";
	level.scr_radio[ "uav_online" ] 				 = "cont_cmt_hellfireonline";
	level.scr_radio[ "uav_online_repeat" ] 			 = "cont_cmt_repeatonline";

	level.scr_radio[ "uav_down" ] 					 = "cont_cmt_uavdown";

	// AI Kills
	level.scr_radio[ "uav_multi_kill" ] 			 = "cont_cmt_mutlipleconfirmed";
	level.scr_radio[ "uav_multi_kill2" ] 			 = "cont_cmt_fivepluskias";
	level.scr_radio[ "uav_few_kills" ] 				 = "cont_cmt_theyredown";
	level.scr_radio[ "uav_3_kills" ] 				 = "cont_cmt_3kills";
	level.scr_radio[ "uav_1_kill" ] 				 = "cont_cmt_hesdown";

	// vehicle kills
	level.scr_radio[ "uav_btr_kill" ] 				 = "cont_cmt_mutlipleconfirmed";
	level.scr_radio[ "uav_few_kills" ] 				 = "cont_cmt_theyredown";
	level.scr_radio[ "uav_3_kills" ] 				 = "cont_cmt_3kills";
	level.scr_radio[ "uav_1_kill" ] 				 = "cont_cmt_hesdown";

	level.scr_radio[ "uav_multi_vehicle_kill" ] 	 = "cont_cmt_goodhitvehicles";
	level.scr_radio[ "uav_multi_vehicle_kill2" ] 	 = "cont_cmt_goodeffectkia";

	level.scr_radio[ "uav_helo_kill" ] 				 = "cont_cmt_directhitshelo";
	level.scr_radio[ "uav_btr_kill" ] 				 = "cont_cmt_btrdestroyed";
	level.scr_radio[ "uav_truck_kill" ] 			 = "cont_cmt_goodkilltruck";
	level.scr_radio[ "uav_jeep_kill" ] 				 = "cont_cmt_directhitjeep";
	level.scr_radio[ "uav_direct_hit" ] 			 = "cont_cmt_directhit";
}

is_radio_defined( alias )
{
	return IsDefined( level.scr_radio[ alias ] ) || IsDefined( level.scr_radio[ alias + "_variant" ] );
}

should_break_available()
{
	if ( IsDefined( level.uav_is_not_available ) )
		return false;
	else
		return true;
}

should_break_destroyed()
{
	if ( IsDefined( level.uav_is_destroyed ) )
		return false;
	else
		return true;
}

enable_uav( do_radio, restore )
{
	if ( !IsDefined( do_radio ) )
	{
		do_radio = true;
	}

	if ( !flag( "uav_enabled" ) )
	{
		flag_set( "uav_enabled" );

		if ( !flag( "uav_reloading" ) && do_radio )
		{
			thread remotemissile_radio( "uav_online" );
		}
	}

	if ( IsDefined( restore ) )
	{
		restore_uav_weapon( restore );
	}
}

disable_uav( do_radio, remove )
{
	if ( !IsDefined( do_radio ) )
	{
		do_radio = true;
	}

	if ( flag( "uav_enabled" ) )
	{
		flag_clear( "uav_enabled" );

		if ( !flag( "uav_reloading" ) && do_radio )
		{
			thread remotemissile_radio( "uav_offline" );
		}
	}

	if ( IsDefined( remove ) )
	{
		remove_uav_weapon();
	}
}

restore_uav_weapon( restore )
{
	if ( IsDefined( level.uav_is_destroyed ) )
	{
		return;
	}

	if ( IsString( restore ) )
	{
		weapon = restore;
	}
	else if ( IsDefined( self.uav_weaponname ) )
	{
		weapon = self.uav_weaponname;
	}
	else
	{
		return;
	}

	if ( !self HasWeapon( weapon ) )
	{
		return;
	}

	self SetWeaponHudIconOverride( "actionslot" + self get_remotemissile_actionslot(), "none" );
	self SetActionSlot( self get_remotemissile_actionslot(), "weapon", weapon );
}

remove_uav_weapon()
{
	self SetWeaponHudIconOverride( "actionslot" + self get_remotemissile_actionslot(), "dpad_killstreak_hellfire_missile_inactive" );
	self SetActionSlot( self get_remotemissile_actionslot(), "" );
}

is_remote_missile_weapon( weap )
{
	if ( !IsDefined( weap ) )
	{
		return false;
	}

	if ( weap == "remote_missile_detonator" )
	{
		return true;
	}

	if ( weap == "remote_missile_detonator_finite" )
	{
		return true;
	}

	return false;
}

give_remotemissile_weapon( weapon_name )
{
	self set_remotemissile_actionslot();
	self SetActionSlot( self get_remotemissile_actionslot(), "weapon", weapon_name );
	self GiveWeapon( weapon_name );

	self thread remotemissile_with_autoreloading();
}

// Sets the proper dpad depending if they have the claymore or not
set_remotemissile_actionslot()
{
	if ( !self HasWeapon( "claymore" ) )
	{
		// Move the claymore (since we do not have it yet) to the down dpad
		self.remotemissile_actionslot = 4;
	}
	else
	{
		self.remotemissile_actionslot = 2;
	}
}

get_remotemissile_actionslot()
{
	AssertEx( IsDefined( self.remotemissile_actionslot ), "self.remotemissile_actionslot is undefined, you need to use the give_remotemissile_weapon() function in here to give the player the weapon properly." );
	return self.remotemissile_actionslot;
}

has_uav_rigs()
{
	if ( !isdefined( self.uav_rigs ) )
		return false;
	
	return self.uav_rigs.size > 1;
}

remotemissile_weapon_change( optional_post_launch_func )
{
	self.using_uav = false;
	
	while ( 1 )
	{
		self waittill( "weapon_change", weap );
		
		if ( is_remote_missile_weapon( weap ) )
		{		
			self.using_uav = true;

			if ( IsDefined( level.uav_is_destroyed ) )
			{
				thread remotemissile_offline( false, "uav_down" );
				self SwitchToWeapon( self.last_weapon );
				self.using_uav = false;
				continue;
			}
			
			if ( self ent_flag_exist( "laststand_downed" ) && self ent_flag( "laststand_downed" ) )
			{
				self SwitchBackToMainWeapon();
				self.using_uav = false;
				continue;
			}
			
			// do not use predator if player is too hurt to do so
			if ( self ent_flag_exist( "player_has_red_flashing_overlay" ) && self ent_flag( "player_has_red_flashing_overlay" ) )
			{
				self SwitchBackToMainWeapon();
				self.using_uav = false;
				continue;
			}
			
			// UAV - remote missile can only be used one at a time in online/offline coop with SpecOps
			if ( is_survival() && isdefined( level.uav_user ) && level.uav_user != self )
			{
				// inform player why it cant be used
				self thread radio_dialogue(  "so_hq_uav_busy" );	// survival defined VO
				self SwitchBackToMainWeapon();
				self.using_uav = false;
				continue;
			}
			
			self.uav_weaponname = weap;

			self thread cancel_on_player_damage();
			if ( IsDefined( level.remote_missile_hide_stuff_func ) )
			{
				[[ level.remote_missile_hide_stuff_func ]]();
			}

			maps\_audio::aud_send_msg("player_UAV_use");

			level.uav_user = self;
			level.uav_killstats = [];

			UAVRemoteLauncherSequence( self, weap );

			level.uav_user = undefined;

			self.using_uav = false;

			if ( IsDefined( level.remoteMissile_global_post_launch_func ) )
			{
				[[ level.remoteMissile_global_post_launch_func ]]();
			}

			if ( isdefined( optional_post_launch_func ) )
			{
				thread [[ optional_post_launch_func ]]();
			}
		}
	}
}

remotemissile_track_current_weapon()
{
	self endon( "death" );

	self.last_weapon = self GetCurrentWeapon();
	while ( 1 )
	{
		self waittill( "weapon_change", newWeapon );
		if ( !is_remote_missile_weapon( newWeapon ) )
		{
			self.last_weapon = newWeapon;
		}
	}

}

// if isSpKillstreakReward, we won't do anything to the weapon once it's fired since the killstreak script handles that
remotemissile_player_input( optional_post_launch_func )
{
	assertex( isplayer( self ), "Can't give missiles to this entity." );

	self NotifyOnPlayerCommand( "switch_to_remotemissile", "+actionslot " + self get_remotemissile_actionslot() );

	self thread remotemissile_weapon_change( optional_post_launch_func );
	self thread remotemissile_track_current_weapon();

	for ( ;; )
	{
		self waittill( "switch_to_remotemissile" );

		if ( self.using_uav )
		{
			continue;
		}

		if ( !is_remote_missile_weapon( self GetCurrentWeapon() ) )
		{
			self.last_weapon = self GetCurrentWeapon();
		}

		if ( IsDefined( level.uav_is_destroyed ) )
		{
			thread remotemissile_offline( false, "uav_down" );
		}
		else 
		if ( flag( "uav_reloading" ) || !flag( "uav_enabled" ) )
		{
			thread remotemissile_offline( true );
		}
	}
}

remotemissile_offline( extra_check, alias )
{
	if ( !IsDefined( alias ) )
	{
		alias = "uav_offline";
	}

	curr_time = GetTime();

	// Only use extra_check if you don't want the dialogue to happen just before the hellfire "online" is about to
	// play
	if ( extra_check && ( ( level.last_uav_launch_time + level.min_time_between_uav_launches ) - curr_time < 2000 ) || level.min_time_between_uav_launches < 5000 )
	{
		// These 2 checks are specific to levels. 
		// SO_ROOFTOP_CONTINGENCY needs dialogue if out of ammo.
		// All other levels need uav_is_destroyed
		if ( !IsDefined( level.uav_is_destroyed ) && ( IsDefined( self.uav_weaponname ) && self GetWeaponAmmoClip( self.uav_weaponname ) > 0 ) )
		{
			return;
		}
	}

	if ( flag( "uav_reloading" ) )
	{
		if ( IsDefined( level.scr_radio[ "uav_reloading" ] 	 ) )
		{
			alias = "uav_reloading";
		}
	}

//	if ( !flag( "uav_collecting_stats" ) && curr_time > level.last_uav_offline_time + 1000 )
	if ( !flag( "uav_collecting_stats" ) && !level.uav_radio_offline_called )
	{
		level.uav_radio_offline_called = true;
		remotemissile_radio( alias );
		level.uav_radio_offline_called = false;
	}
}



remotemissile_radio_reminder()
{
	level notify( "stop_remotemissile_radio_reminder" );

	level endon( "special_op_terminated" );
	level endon( "starting_predator_drone_control" );
	level endon( "stop_remotemissile_radio_reminder" );

	while ( 1 )
	{
		wait( 7 + RandomInt( 4 ) );

		if ( flag_exist( "special_op_terminated" ) && flag( "special_op_terminated" ) )
		{
			return;
		}

		if ( IsDefined( level.uav_is_destroyed ) )
		{
			return;
		}

		if ( flag( "uav_reloading" ) )
		{
			return;
		}

		if ( !flag( "uav_enabled" ) )
		{
			return;
		}

		remotemissile_radio( "uav_online_repeat" );

		wait( 15 + RandomInt( 10 ) );

		if ( flag_exist( "special_op_terminated" ) && flag( "special_op_terminated" ) )
		{
			return;
		}

		if ( IsDefined( level.uav_is_destroyed ) )
		{
			return;
		}

		if ( IsDefined( level.no_remote_missile_reminders ) )
		{
			return;
		}

		remotemissile_radio( "uav_online" );
		self thread display_hint_timeout( "hint_predator_drone_" + self get_remotemissile_actionslot(), 6 );

	}
}

play_kills_dialogue()
{
	if ( IsDefined( level.dont_use_global_uav_kill_dialog ) )
		return;

	if ( !IsDefined( level.uav_radio_initialized ) )
	{
		return;
	}

// "Good hit. Multiple vehicles destroyed."					level.scr_radio[ "multi_vehicle_kill" ] = "cont_cmt_goodhitvehicles";
// "Good effect on target. Multiple enemy vehicles KIA." 	level.scr_radio[ "multi_vehicle_kill2" ] = "cont_cmt_goodeffectkia";

// "Direct hit on the enemy helo. Nice shot Roach."			level.scr_radio[ "helo_kill" ] = "cont_cmt_directhitshelo";
// "Good effect on target. BTR destroyed."					level.scr_radio[ "btr_kill" ] = "cont_cmt_btrdestroyed";
// "Good kill. Truck destroyed."							level.scr_radio[ "truck_kill" ] = "cont_cmt_goodkilltruck";
// "Direct hit on that jeep."								level.scr_radio[ "jeep_kill" ] = "cont_cmt_directhitjeep";
// "Direct hit."											level.scr_radio[ "direct_hit" ] = "cont_cmt_directhit";

// "Five plus KIAs. Good hit. Good hit.						level.scr_radio[ "multi_kill2" ] = "cont_cmt_fivepluskias";
// "Multiple confirmed kills. Nice work."					level.scr_radio[ "multi_kill" ] = "cont_cmt_mutlipleconfirmed";
// "They're down."											level.scr_radio[ "few_kills" ] = "cont_cmt_theyredown";
// "Good hit. Looks like at least three kills."				level.scr_radio[ "3_kills" ] = "cont_cmt_3kills";
// "He's down."												level.scr_radio[ "1_kill" ] = "cont_cmt_hesdown";

	ai_alias = undefined;
	ai_kills = 0;

	if ( IsDefined( level.uav_killstats[ "ai" ] ) )
	{
		ai_kills = level.uav_killstats[ "ai" ];
	}

	if ( ai_kills > 5 )
	{
		ai_alias = "uav_multi_kill";

		if ( is_radio_defined( "uav_multi_kill2" ) && cointoss() )
		{
			ai_alias = "uav_multi_kill2";
		}
	}
	else if ( ai_kills >= 3 )
	{
		ai_alias = "uav_3_kills";
	}
	else if ( ai_kills > 1 )
	{
		ai_alias = "uav_few_kills";
	}
	else if ( ai_kills > 0 )
	{
		ai_alias = "uav_1_kill";
	}

	vehicle_alias = undefined;
	btr_kills = 0;

	vehicle_kills = 0;
	btr_kills = 0;
	helo_kills = 0;
	jeep_kills = 0;
	truck_kills = 0;

	foreach ( index, kills in level.uav_killstats )
	{
		if ( index == "ai" )
		{
			continue;
		}

		if ( kills  > 0 )
		{
			vehicle_kills = vehicle_kills + kills;

			if ( index == "btr" )
			{
				btr_kills = kills;
			}
			else if ( index == "helo" )
			{
				helo_kills = kills;
			}
			else if ( index == "jeep" )
			{
				jeep_kills = kills;
			}
			else if ( index == "truck" )
			{
				truck_kills = kills;
			}
		}
	}

	alias = ai_alias;

	if ( btr_kills > 0 )
	{
		alias = "uav_btr_kill";
	}
	else if ( helo_kills > 0 )
	{
		alias = "uav_helo_kill";
	}
	else if ( vehicle_kills > 1 )
	{
		alias = "uav_multi_vehicle_kill";

		if ( is_radio_defined( "uav_multi_vehicle_kill2" ) && cointoss() )
		{
			alias = "uav_multi_vehicle_kill2";
		}
	}
	else if ( jeep_kills > 0 )
	{
		alias = "uav_jeep_kill";

		if ( ai_kills > 2 && ai_kills <= 5 && is_radio_defined( "uav_direct_hit" ) && cointoss() )
		{
			alias = "uav_direct_hit";
		}
	}
	else if ( truck_kills > 0 )
	{
		alias = "uav_truck_kill";

		if ( ai_kills > 2 && ai_kills <= 5 && is_radio_defined( "uav_direct_hit" ) && cointoss() )
		{
			alias = "uav_direct_hit";
		}
	}

	if ( !IsDefined( alias ) )
	{
		return;
	}

	if ( flag_exist( "special_op_terminated" ) && flag( "special_op_terminated" ) )
	{
		return;
	}

	remotemissile_radio( alias );
	level notify( "remote_missile_kill_dialogue" );
}

set_variant_remotemissile_radio( alias )
{
	if ( IsDefined( level.scr_radio[ alias + "_variant" ] ) && IsArray( level.scr_radio[ alias + "_variant" ] ) )
	{
		level.scr_radio[ alias ] = level.scr_radio[ alias + "_variant" ][ RandomInt( level.scr_radio[ alias + "_variant" ].size ) ];
	}
}

remotemissile_radio( alias )
{
	if ( !IsDefined( level.uav_radio_initialized ) )
	{
		return;
	}

	if ( IsDefined( level.uav_radio_disabled ) && level.uav_radio_disabled )
	{
		return;
	}

	if ( !is_radio_defined( alias ) )
	{
		return;
	}

	if ( flag_exist( "special_op_terminated" ) && flag( "special_op_terminated" ) )
	{
		return;
	}

	set_variant_remotemissile_radio( alias );
	radio_dialogue( alias );
}

cancel_on_player_damage()
{
	self endon( "exiting_uav_control" );
	self.took_damage = false;
	//self waittill( "damage" );
	if ( is_Survival() )
		self waittill_any( "player_has_red_flashing_overlay", "player_downed", "dtest", "force_out_of_uav" );
	else
		self waittill_any( "damage", "dtest", "force_out_of_uav" );
	
	self.took_damage = true;
	maps\_audio::aud_send_msg("abort_UAV_control");
}


text_TitleCreate()
{
	level.text1 = self createClientFontString( "objective", 2.0 );
	
	y_offset = -175;
	// survival has other hud elements that would overlap this string
	if ( is_survival() )
	{
		y_offset = -150;
		// splitscreen has further overlapping issues for top/bottom screen, thus requires another adjustment
		if ( issplitscreen() )
			y_offset = -110;
	}
	
	level.text1 setPoint( "CENTER", undefined, 0, y_offset );
}


text_TitleSetText( text )
{
	level.text1 SetText( text );
}


text_TitleFadeout()
{
	level.text1 FadeOverTime( 0.25 );
	level.text1.alpha = 0;
}


text_TitleDestroy()
{
	if ( !IsDefined( level.text1 ) )
		return;
	level.text1 Destroy();
	level.text1 = undefined;
}


display_wait_to_fire( time_till_reload )
{
	text_NoticeDestroy();
	// MISSILE RELOADED IN: 
	self text_LabelCreate( &"HELLFIRE_RELOADING_WITH_TIME", time_till_reload );
	wait( 1 );
	text_NoticeDestroy();
}

text_LabelCreate( text, time )
{
	level.text2 = self createClientFontString( "objective", 1.85 );
	level.text2 SetPoint( "CENTER", undefined, 0, -120 );
	level.text2.label = text;
	level.text2 SetValue( time );
	level.text2.color = ( 0.85, 0.85, 0.85 );
	level.text2.alpha = 0.75;
}


text_NoticeCreate( text )
{
	level.text2 = self createClientFontString( "objective", 1.85 );
	level.text2 SetPoint( "CENTER", undefined, 0, -120 );
	level.text2 SetText( text );
	level.text2.color = ( 0.85, 0.85, 0.85 );
	level.text2.alpha = 0.75;
}


text_NoticeFadeout()
{
	if ( !IsDefined( level.text2 ) )
		return;
	level.text2 FadeOverTime( 0.25 );
	level.text2.alpha = 0;
}


text_NoticeDestroy()
{
	if ( !IsDefined( level.text2 ) )
		return;
	level.text2 Destroy();
	level.text2 = undefined;
}

WaitWithAbortOnDamage( time )
{
	finishTime = GetTime() + ( time * 1000 );
	while ( GetTime() < finishTime )
	{
		if ( self.took_damage )
		{
			return false;
		}
		
		if ( IsDefined( level.uav_is_destroyed ) )
		{
			return false;
		}
		
		if (self UseButtonPressed())
		{
			return false;
		}

		if ( !flag( "uav_enabled" ) )
		{
			return false;
		}

		wait 0.05;
	}
	return true;
}


NotifyOnMissileDeath( missile, player )
{
	timeWeFired = GetTime();
	level.remoteMissileFireTime = timeWeFired;

	if ( IsDefined( missile ) )
	{
		level.remoteMissile = missile;
		missile waittill( "death" );
	}
	
	player delaythread(0.1, ::HoldStanceChange, true );
	
	player.active_uav_missile = undefined;

	//defensive check; make sure we're this is still the latest remote missile
	if ( IsDefined( level.remoteMissileFireTime ) && ( level.remoteMissileFireTime == timeWeFired ) )
	{
		level notify( "remote_missile_exploded" );
		player notify( "remote_missile_exploded" );	// player specific notify
		level.remoteMissile = undefined;
	}

	level delayThread( 0.2, ::send_notify, "delayed_remote_missile_exploded" );
}

AbortLaptopSwitch( player )
{
	player ent_flag_clear( "controlling_UAV" );
	player notify("exiting_uav_control");

	maps\_audio::aud_send_msg("abort_UAV_control");
	
	player VisionSetNakedForPlayer( level.lvl_visionset, 0.5 );
		
	if (isdefined(level.remotemissile_usethermal) && level.remotemissile_usethermal)
	{
		player VisionSetThermalForPlayer( level.visionThermalDefault, 0.5 );
	}
	else
	{
		if (isdefined(get_vision_set_fog(level.lvl_visionset)))
			player fog_set_changes(level.lvl_visionset, 0.5);
	}

	player SwitchBackToMainWeapon();
	player FreezeControls( false );
	if ( !is_player_down( player ) )
		player EnableOffhandWeapons();
		
	player delaythread(0.1, ::HoldStanceChange, true );

	level.uavTargetEnt = undefined;

	wait 0.1;
	HudItemsShow();
}

HoldStanceChange( allowed )
{
	if (!allowed)
	{
		stance = self getstance();
		if (stance != "prone")
			self AllowProne(allowed);
		if (stance != "crouch")
			self AllowCrouch(allowed);
		if (stance != "stand")
			self AllowStand(allowed);
	}
	else
	{
		self AllowProne(allowed);
		self AllowCrouch(allowed);
		self AllowStand(allowed);
	}
}


UAVRemoteLauncherSequence( player, weap )
{
	if ( weap == "remote_missile_detonator" )
	{
		player GiveMaxAmmo( weap );
	}

	level notify( "starting_predator_drone_control" );
	player notify( "starting_predator_drone_control" );
	delay_switch_into_missile = false;
	return_to_uav_after_impact = false;

	level.VISION_BLACK = "black_bw";
	if ( !isdefined( level.VISION_UAV ) )
	{
		level.VISION_UAV = "ac130";
	}

	level.VISION_MISSILE = "missilecam";

//	level.uavPlayerOrigin = player GetOrigin();
//	level.uavPlayerAngles = player GetPlayerAngles();

	player DisableOffhandWeapons();
	player FreezeControls( true );
	player HoldStanceChange(false);
	
	player ent_flag_set( "controlling_UAV" );

	noDamage = player WaitWithAbortOnDamage( 1.0 );
	if ( !noDamage )
	{
		AbortLaptopSwitch( player );
		return;
	}

	trans_time = 0.25;
	player VisionSetNakedForPlayer( level.VISION_BLACK, trans_time );
	if (isdefined(level.remotemissile_usethermal) && level.remotemissile_usethermal)
		player VisionSetThermalForPlayer( level.VISION_BLACK, trans_time );
	HudItemsHide();

	noDamage = WaitWithAbortOnDamage( trans_time );
	if ( !noDamage )
	{
		AbortLaptopSwitch( player );
		return;
	}

	player.is_controlling_UAV = true;
	level notify( "player_is_controlling_UAV" );
	player notify( "player_is_controlling_UAV" );

	Assert( self == player );
	uav = player get_uav();

	if ( IsDefined( uav ) )
	{
		if ( is_specialop() )
		{
			uav HideOnClient( self );
		}
		else
		{
			uav Hide();
		}
	}

	rig = player_uav_rig();
	if ( !remotemissile_move_player() )
	{
		player PlayerLinkWeaponViewToDelta( rig, "tag_player", 1.0, level.uav_struct.view_cone, level.uav_struct.view_cone, level.uav_struct.view_cone, level.uav_struct.view_cone );
		angles = rig GetTagAngles( "tag_origin" );
		player SetPlayerAngles( angles );
	
	}
	else
	{
		player.old_origin = player.origin;
		player.old_angles = player GetPlayerAngles();
		player PlayerLinkToDelta( player_uav_rig(), "tag_player", 1.0, level.uav_struct.view_cone, level.uav_struct.view_cone, level.uav_struct.view_cone, level.uav_struct.view_cone );
		player PlayerLinkToDelta( player_uav_rig(), "tag_player", 1.0, 0, 0, 0, 0 );

		// expand the view clamp
		player delayThread( 0.1, ::open_view_cone );
	}

	player FreezeControls( false );

	player HideViewModel();
	wait 0.05;
	

	if (isdefined(level.activate_uav_hud_cb))
	{
		player [[level.activate_uav_hud_cb]] ();
	}
	else
	{
		player text_TitleCreate();
		// CAMERA: UAV_DRONE_011
		text_TitleSetText( &"HELLFIRE_DRONE_VIEW" );
	}

	if (isdefined(level.remotemissile_usethermal) && level.remotemissile_usethermal)
	{
		maps\_load::thermal_EffectsOn();
		player ThermalVisionOn();
		player VisionSetThermalForPlayer( level.VISION_UAV, 0.25 );
		assert( isdefined( level.lvl_visionset != "" ) );
		player VisionSetNakedForPlayer( level.lvl_visionset, 0.25 );
	}
	else
	{
		if (isdefined(get_vision_set_fog(level.VISION_UAV)))
			player fog_set_changes(level.VISION_UAV, 0.25);
		player VisionSetNakedForPlayer( level.VISION_UAV, 0.25 );
	}
	thread DrawTargetsStart();
	wait 0.2;

	
	doAttack = WaitForAttackCommand( player );
	if ( !doAttack )
	{
		ExitFromCamera_UAV( player, player.took_damage );
		return;
	}

	level.last_uav_launch_time = GetTime();
	thread uav_reload();

	level notify( "player_fired_remote_missile" );
	player notify( "player_fired_remote_missile" );
	missile = FireMissileFromUAVPlayer( player );
	missile thread do_physics_impact_on_explosion( player ); 
	missile thread flash_for_explosion_early( player ); 
	

	if ( delay_switch_into_missile )
	{
		// -MISSILE LAUNCHED-
		player text_NoticeCreate( &"HELLFIRE_FIRE" );
		noDamage = WaitWithAbortOnDamage( 1.2 );
		if ( !noDamage )
		{
			ExitFromCamera_UAV( player, true );
			return;
		}

		text_NoticeFadeout();
		DrawTargetsEnd();
		//player VisionSetThermalForPlayer( level.VISION_BLACK, 0.25 );
		wait 0.25;
	}

	player.is_flying_missile = true;// used to break the hint
	if (isdefined(level.firemissile_uav_hud_cb))
	{
		player [[ level.firemissile_uav_hud_cb ]]( 0 );
	}
	else
	{
		// CAMERA: MISSILE
		text_TitleSetText( &"HELLFIRE_MISSILE_VIEW" );
		text_NoticeDestroy();
	}
	SwitchBackToMainWeaponFast();
	player RemoteCameraSoundscapeOn();
	player Unlink(); // <- unlinking here cuases the screen to go brighter
	//player VisionSetThermalForPlayer( level.VISION_MISSILE, 0.5 );
	player DisableWeapons();
	if (isdefined(level.uav_missile_tag_for_camera))
		player CameraLinkTo( missile, level.uav_missile_tag_for_camera );
	else
		player CameraLinkTo( missile, "tag_origin" );
	player ControlsLinkTo( missile );

	noDamage = WaitWithAbortOnDamage( 0.2 );
	if ( !noDamage )
	{
		ExitFromCamera_Missile( player, true );
		return;
	}
	
	if ( isdefined ( level.remote_missile_steering_cb ) )
	{
		player [[ level.remote_missile_steering_cb ]] (missile);
	}	

	thread DrawTargetsStart();
	while ( IsDefined( level.remoteMissile ) )
	{
		wait 0.05;
		if ( IsDefined( level.uav_is_destroyed ) )
		{
			ExitFromCamera_Missile( player, true );
			return;
		}

		if ( player.took_damage )
		{
			ExitFromCamera_Missile( player, true );
			return;
		}

		if ( !flag( "uav_enabled" ) )
		{
			ExitFromCamera_Missile( player, true );
			return;
		}
	}

	if ( !isdefined( uav ) )
	{
		ExitFromCamera_Missile( player, false );
		return;
	}

	if ( return_to_uav_after_impact )
	{
		//new - go back to uav to see explosion
		//level.uav Hide(); // should be hide on client?
		SetSavedDvar( "cg_fov", 26 );
		player.fov_is_altered = true;
		player.is_flying_missile = undefined;
		player ControlsUnlink();
		player CameraUnlink();
		player RemoteCameraSoundscapeOff();
		player PlayerLinkWeaponViewToDelta( player_uav_rig(), "tag_player", 1.0, level.uav_struct.view_cone, level.uav_struct.view_cone, level.uav_struct.view_cone, level.uav_struct.view_cone );
		player SetPlayerAngles( player_uav_rig() GetTagAngles( "tag_origin" ) );

		noDamage = WaitWithAbortOnDamage( 2 );
		if ( !noDamage )
		{
			ExitFromCamera_UAV( player, player.took_damage );
			return;
		}

		ExitFromCamera_UAV( player, false );
	}
	else
	{
		ExitFromCamera_Missile( player, false );
	}
}

uav_reload()
{
	level endon( "stop_uav_reload" );

	flag_set( "uav_reloading" );

	wait( level.min_time_between_uav_launches * 0.001 );

	flag_clear( "uav_reloading" );
}

flash_for_explosion_early( player )
{
	player waittill( "predicted_projectile_impact", weaponName, position );
	// hide geometry we could see due to the camera clipping through by flashing the screen a frame early
	player VisionSetNakedForPlayer( "coup_sunblind", 0 );
}

do_physics_impact_on_explosion( player )
{
	player.fired_hellfire_missile = true;

	player waittill( "projectile_impact", weaponName, position, radius );

	level thread missile_kills( player );

	level.uavTargetPos = position;

	physicsSphereRadius = 1000;
	physicsSphereForce = 6.0;
	Earthquake( 0.3, 1.4, position, 8000 );

	maps\_audio::aud_send_msg( "remote_missle_impact", position );

	wait 0.1;
	PhysicsExplosionSphere( position, physicsSphereRadius, physicsSphereRadius / 2, physicsSphereForce );

	wait 2;
	level.uavTargetPos = undefined;
	player.fired_hellfire_missile = undefined;
	//level notify ( "player_missile_finished_impact" );
}		

missile_kills( player )
{
	flag_set( "uav_collecting_stats" );

//	ai_array = GetAIArray( "axis" );
//	foreach ( ai in ai_array )
//	{
//		ai thread missile_kill_ai( player );
//	}

	vehicles = getVehicleArray();
	foreach ( vehicle in vehicles )
	{
		vehicle thread missile_kill_vehicle( player );
	}

	wait( 1 );
	flag_clear( "uav_collecting_stats" );
}

missile_kill_ai( attacker )
{
	if ( !IsDefined( level.uav_radio_initialized ) )
	{
		return;
	}

	self waittill( "death", attacker, cause );

	if ( !IsDefined( level.uav_user ) )
	{
		return;
	}

	if ( !IsDefined( level.uav_killstats[ "ai" ] ) )
	{
		level.uav_killstats[ "ai" ] = 0;
	}

	if ( IsDefined( attacker ) && IsDefined( level.uav_user ) )
	{
		if ( attacker == level.uav_user || ( IsDefined( attacker.attacker ) && attacker.attacker == level.uav_user ) )
		{
			level.uav_killstats[ "ai" ]++;
			//if ( IsPlayer( level.uav_user ) && level.uav_killstats[ "ai" ] == 10 )
			//	level.uav_user player_giveachievement_wrapper( "TEN_PLUS_FOOT_MOBILES" );
		}
	}
}

missile_kill_vehicle( player )
{
	if ( !IsDefined( level.uav_radio_initialized ) )
	{
		return;
	}

	level endon( "delayed_remote_missile_exploded" );

	type = undefined;

	switch( self.vehicletype )
	{
		case "btr80":
		case "btr80_physics":
			type = "btr";
			break;

		case "ucav":
		case "hind":
		case "mi17":
		case "mi17_noai":
		case "mi17_bulletdamage":
			type = "helo";
			break;

		case "uaz":
		case "uaz_physics":
			type = "jeep";
			break;

		case "bm21":
		case "bm21_drivable":
		case "bm21_troops":
			type = "truck";
			break;

		default:
			type = "vehicle";
			break;
	}

	if ( !IsDefined( level.uav_killstats[ type ] ) )
	{
		level.uav_killstats[ type ] = 0;
	}

	self waittill( "death", attacker, cause );

	if ( ( type == "helo" || type == "btr" ) || IsDefined( self.riders ) && self.riders.size > 0 )
	{
		if ( IsDefined( attacker ) && attacker == player )
		{
			level.uav_killstats[ type ]++;
		}
	}
}

get_current_uav_rig()
{
	assert( self.current_uav_index < self.uav_rigs.size );
	rig = self.uav_rigs[ self.current_uav_index ];
	return rig;
}


get_uav()
{
	AssertEx( IsPlayer( self ), "Only player entities can be Self" );

	if ( !isdefined( self.uav_rigs ) )
	{
		// level.uav may or may not exist
		return level.uav;
	}
	
	if ( !isdefined( self.current_uav_index ) )
	{
		self.current_uav_index = 0;
	}

	rig = get_current_uav_rig();
	
	return rig.uav;
}

ExitFromCamera_Missile( player, reasonIsPain )
{
	player.is_flying_missile = undefined;
	if (isdefined(level.firemissile_uav_hud_cb))
	{
		player [[ level.firemissile_uav_hud_cb ]]( 1 );
	}
	else
	{
		text_TitleDestroy();
	}
	DrawTargetsEnd();

	if ( IsDefined( level.uav_is_destroyed ) )
		thread staticEffect( 0.5 );

	player ControlsUnlink();
	player CameraUnlink();
	if (isdefined(level.remotemissile_usethermal) && level.remotemissile_usethermal)
	{
		maps\_load::thermal_EffectsOff();
		player ThermalVisionOff();
		player VisionSetThermalForPlayer( level.visionThermalDefault, 0 );
	}
	player RemoteCameraSoundscapeOff();

	uav = player get_uav();
	
	if ( IsDefined( uav ) )
	{
		if ( is_specialop() )
		{
			uav ShowOnClient( self );
		}
		else
		{
			uav Show();
		}
	}

	if ( reasonIsPain )
	{
		//fast switch back - go right to weapon, no flash
		player VisionSetNakedForPlayer( level.VISION_BLACK, 0 );
		wait 0.05;
		player VisionSetNakedForPlayer( level.lvl_visionset, 0.4 );
		if (!(isdefined(level.remotemissile_usethermal) && level.remotemissile_usethermal))
		{
			if (isdefined(get_vision_set_fog(level.lvl_visionset)))
				player fog_set_changes(level.lvl_visionset, 0.4);
		}
		
		if ( !is_player_down( player ) )
			player EnableWeapons();
		
		player FreezeControls( false );
		player ShowViewModel();
		wait 0.2;

		HudItemsShow();
		
		if ( !is_player_down( player ) )
			player EnableOffhandWeapons();
	}
	else
	{
		//slow switch back - flash from missile explosion
		player VisionSetNakedForPlayer( "coup_sunblind", 0 );
		player FreezeControls( true );
		wait 0.05;

		player VisionSetNakedForPlayer( level.lvl_visionset, 1.0 );
		if (!(isdefined(level.remotemissile_usethermal) && level.remotemissile_usethermal))
		{
			if (isdefined(get_vision_set_fog(level.lvl_visionset)))
				player fog_set_changes(level.lvl_visionset, 1.0);
		}
		
		if ( !is_player_down( player ) )
			player EnableWeapons();
			
		player ShowViewModel();
		wait 0.5;

		HudItemsShow();
		
		if ( !is_player_down( player ) )
			player EnableOffhandWeapons();
		
		player FreezeControls( false );
	}

	player notify("exiting_uav_control");
	player.is_controlling_UAV = undefined;

	level.uavTargetEnt = undefined;
}

ExitFromCamera_UAV( player, reasonIsPain )
{
	maps\_audio::aud_send_msg("abort_UAV_control");
	DrawTargetsEnd();
	if (isdefined(level.deactivate_uav_hud_cb))
	{
		player [[level.deactivate_uav_hud_cb]]( 0 );
	}
	else
	{
		text_TitleFadeout();
		text_NoticeFadeout();
	}
	player VisionSetNakedForPlayer( level.VISION_BLACK, 0.25 );
	if (isdefined(level.remotemissile_usethermal) && level.remotemissile_usethermal)
		player VisionSetThermalForPlayer( level.VISION_BLACK, 0.25 );
	if ( IsDefined( level.uav_is_destroyed ) )
		player thread staticEffect( 0.5 );
	wait 0.15;

	wait 0.35;

	if (isdefined(level.deactivate_uav_hud_cb))
	{
		player [[level.deactivate_uav_hud_cb]]( 1 );
	}
	else
	{
		text_TitleDestroy();
		text_NoticeDestroy();
	}
	player Unlink();
	if (isdefined(level.remotemissile_usethermal) && level.remotemissile_usethermal)
	{
		player VisionSetThermalForPlayer( level.visionThermalDefault, 0 );
		maps\_load::thermal_EffectsOff();
		player ThermalVisionOff();
	}

	if ( IsDefined( player.fov_is_altered ) )
		SetSavedDvar( "cg_fov", 65 );

	uav = player get_uav();
	
	if ( IsDefined( uav ) )
	{
		if ( is_specialop() )
		{
			uav ShowOnClient( self );
		}
		else
		{
			uav Show();
		}
	}

	if ( reasonIsPain )
	{
		//fast switch back - go right to weapon
		player SwitchBackToMainWeaponFast();
		player FreezeControls( true );
		wait 0.15;
		player VisionSetNakedForPlayer( level.lvl_visionset, 0.4 );
		if (!(isdefined(level.remotemissile_usethermal) && level.remotemissile_usethermal))
		{
			if (isdefined(get_vision_set_fog(level.lvl_visionset)))
				player fog_set_changes(level.lvl_visionset, 0.4);
		}
		
		if ( !is_player_down( player ) )
			player EnableWeapons();
			
		player ShowViewModel();
		wait 0.10;

		HudItemsShow();
		
		if ( !is_player_down( player ) )
			player EnableOffhandWeapons();
		
		player FreezeControls( false );
	}
	else
	{
		//slow switch back - show laptop, etc
		player FreezeControls( true );
		wait 0.05;
		player VisionSetNakedForPlayer( level.lvl_visionset, 0.75 );
		if (!(isdefined(level.remotemissile_usethermal) && level.remotemissile_usethermal))
		{
			if (isdefined(get_vision_set_fog(level.lvl_visionset)))
				player fog_set_changes(level.lvl_visionset, 0.75);
		}
		
		if ( !is_player_down( player ) )
			player EnableWeapons();
		
		player ShowViewModel();
		wait 0.5;

		HudItemsShow();
		player SwitchBackToMainWeapon();
		
		if ( !is_player_down( player ) )
			player EnableOffhandWeapons();
		
		player FreezeControls( false );
	}
	player delaythread(0.1, ::HoldStanceChange, true );
	player notify("exiting_uav_control");

	player.is_controlling_UAV = undefined;

	level.uavTargetEnt = undefined;
	return;
}

WaitForAttackCommand( player )
{
	// I'd like to use GetCommandFromKey to make this "proper" incase of different keybindings
	// but it's not mp friendly...
//	dpad_left = GetCommandFromKey( "DPAD_LEFT" );
//	dpad_left = GetCommandFromKey( "BUTTON_Y" );
//	dpad_left = GetCommandFromKey( "BUTTON_B" );

//	player NotifyOnPlayerCommand( "abort_remote_missile", "+actionslot 3" ); 		// DPad Left
	player NotifyOnPlayerCommand( "abort_remote_missile", "weapnext" );				// BUTTON_Y
	player NotifyOnPlayerCommand( "abort_remote_missile", "+stance" );				// BUTTON_B
	if (!level.console)
	{	// pc specific
		player NotifyOnPlayerCommand( "abort_remote_missile", "+gostand" );				// jump
		player NotifyOnPlayerCommand( "abort_remote_missile", "togglecrouch" );			// crouch
		player NotifyOnPlayerCommand( "abort_remote_missile", "toggleprone" );			// prone
	}

	player NotifyOnPlayerCommand( "launch_remote_missile", "+attack" );				// BUTTON_RTRIG
	player NotifyOnPlayerCommand( "launch_remote_missile", "+attack_akimbo_accessible" );	// support accessibility control scheme

	player thread wait_for_other();
	player thread wait_for_command_thread( "abort_remote_missile", "abort" );

	if ( flag( "predator_missile_launch_allowed" ) )
		player thread wait_for_command_thread( "launch_remote_missile", "launch" );

	player waittill( "remote_missile_attack", val );
	player ent_flag_clear( "controlling_UAV" );

	if ( val == "launch" )
	{
		return true;
	}
	else
	{
		return false;
	}
}

wait_for_command_thread( msg, val )
{
	self endon( "remote_missile_attack" );
	self waittill( msg );

	self notify( "remote_missile_attack", val );
}

wait_for_other()
{
	self endon( "remote_missile_attack" );

	for ( ;; )
	{
		wait( 0.05 );
		if ( self.took_damage )
		{
			break;
		}

		if ( !flag( "uav_enabled" ) )
		{
			break;
		}

		if ( IsDefined( level.uav_is_destroyed ) )
		{
			break;
		}
	}

	self notify( "remote_missile_attack", "abort" );
}


HudItemsHide()
{
	if ( level.players.size > 0 )
	{
		for ( i = 0; i < level.players.size; i++ )
		{
			if ( IsDefined( level.players[ i ].using_uav ) && level.players[ i ].using_uav )
				SetDvar( "ui_remotemissile_playernum", ( i + 1 ) );// 0 = no uav, 1 = player1, 2 = player2
		}
	}
	else
	{
		SetSavedDvar( "compass", "0" );
		SetSavedDvar( "ammoCounterHide", "1" );
		SetSavedDvar( "actionSlotsHide", "1" );
	}
}


HudItemsShow()
{
	if ( level.players.size > 0 )
	{
		SetDvar( "ui_remotemissile_playernum", 0 );// 0 = no uav, 1 = player1, 2 = player2
	}
	else
	{
		SetSavedDvar( "compass", "1" );
		SetSavedDvar( "ammoCounterHide", "0" );
		SetSavedDvar( "actionSlotsHide", "0" );
	}
}


FireMissileFromUAVPlayer( player )
{
	Earthquake( 0.25, 0.5, player_uav_rig().origin, 5000 );
	

	org = player_uav_rig().origin;
	playerAngles = player GetPlayerAngles();
	forward = AnglesToForward( playerAngles );
	right = AnglesToRight( playerAngles );
	
	if(!isdefined( level.uav_missle_start_forward_distance ))
		level.uav_missle_start_forward_distance = -300.0;
	
	if(!isdefined( level.uav_missle_start_right_distance ))
		level.uav_missle_start_right_distance = 700.0;
	
	start = org + ( right * level.uav_missle_start_right_distance ) + ( forward * level.uav_missle_start_forward_distance );
	end = start + forward * 10.0;

	if ( IsDefined( level.uav_missile_override ) )
	{
		missile = MagicBullet( level.uav_missile_override, start, end, player );
	}
	else if ( IsDefined( level.remote_missile_snow ) )
	{
		missile = MagicBullet( "remote_missile_snow", start, end, player );
	}
	else
	{
		if ( IsDefined( level.remote_missile_invasion ) )
			missile = MagicBullet( "remote_missile_invasion", start, end, player );
		else
			missile = MagicBullet( "remote_missile", start, end, player );
	}

	player.active_uav_missile = missile;
	thread NotifyOnMissileDeath( missile, player );
	return missile;
}

DrawTargetsStart()
{
	level.uav_struct.draw_red_boxes = true;
	level endon( "uav_destroyed" );
	level endon( "draw_target_end" );
	level notify( "stop_prv_draw_targets" );	// ensure only one of these threads is running at any given time
	level endon( "stop_prv_draw_targets" );
	wait 0.05;		// ensure we don't have this routine ever running at the same time on the same server frame
	//level.player ThermalVisionFOFOverlayOn();
	targets_per_frame = 4;
	targets_drawn = 0;
	time_between_updates = 0.05;

	foreach ( tgt in level.remote_missile_targets )
	{
		if ( !IsAlive( tgt ) )
			continue;
		
		tgt draw_target();
		targets_drawn++;
		if ( targets_drawn >= targets_per_frame )
		{
			targets_drawn = 0;
			wait time_between_updates;
		}
	}
}


draw_target()
{
	self.has_target_shader = true;

	if ( IsDefined( self.helicopter_predator_target_shader ) )
	{
		Target_Set( self, ( 0, 0, -96 ) );
	}
	else
	{
		Target_Set( self, ( 0, 0, 64 ) );
	}

	if ( IsAI( self ) )
	{
		if ( IsSplitScreen() )
		{
			Target_SetShader( self, "remotemissile_infantry_target_2plr" );
		}
		else
		{
			Target_SetShader( self, "remotemissile_infantry_target" );
		}
	}
	else 
	if ( IsPlayer( self ) )// Make sure you add the player to the level.remote_missile_targets before use
	{
		if ( IsDefined( self.is_controlling_UAV ) && self.is_controlling_UAV )
		{
			Target_SetShader( self, "hud_fofbox_self_sp" );
		}
		else
		{
			// what shader should the other player use??? None for now... -Carlos
		}
	}	
	else
	{
		Target_SetShader( self, "veh_hud_target" );
	}

	// There is an order of execution issue, which is why this is commented out.
	// If player 2 ( level.players[ 1 ] ) runs the Target_ShowToPlayer() last, then player 1 will be able
	// to see the targets.
	// So, the work around is to figure out who is controlling the UAV, then call to Target_ShowToPlayer() 
	// before Target_HideFromPlayer()
//	foreach( player in level.players )
//	{
//		if( IsDefined( player.is_controlling_UAV ) && player.is_controlling_UAV )
//			Target_ShowToPlayer( self, player );
//		else
//			Target_HideFromPlayer( self, player );
//	}

	uav_controller = undefined;
	non_uav_controller = undefined;

	foreach ( player in level.players )
	{
		if ( IsDefined( player.is_controlling_UAV ) && player.is_controlling_UAV )
		{
			Target_ShowToPlayer( self, player );
			continue;
		}
		
		Target_HideFromPlayer( self, player );
	}
}


DrawTargetsEnd()
{
	level notify( "draw_target_end" );
	level.uav_struct.draw_red_boxes = undefined;
	//level.player ThermalVisionFOFOverlayOff();
	waittillframeend;// was colliding with self waittill death which also removes the target
	
	foreach ( tgt in level.remote_missile_targets )
	{
		if ( !isdefined( tgt ) )
			continue;
		
		if ( IsDefined( tgt.has_target_shader ) )
		{
			tgt.has_target_shader = undefined;
			Target_Remove( tgt );
		}
	}
}


SwitchBackToMainWeapon()
{
	return SwitchBackToMainWeapon_internal( ::_switcher );
}

SwitchBackToMainWeaponFast()
{
	return SwitchBackToMainWeapon_internal( ::_switcherNow );
}

_switcher( weapName )
{
	self SwitchToWeapon( weapName );
}

_switcherNow( weapName )
{
	self SwitchToWeaponImmediate( weapName );
}

SwitchBackToMainWeapon_internal( func )
{
	if ( self ent_flag_exist( "laststand_downed" ) && self ent_flag( "laststand_downed" ) )
	{
		return;
	}

	//"primary", "offhand", "item", "altmode", and "exclusive".
	weapons = self GetWeaponsList( "primary", "altmode" );
	foreach ( weapon in weapons )
	{
		if ( self.last_weapon == weapon )
		{
			self [[ func ]]( self.last_weapon );
			return;
		}
	}

	if ( weapons.size > 0 )
		self [[ func ]]( weapons[ 0 ] );
}


staticEffect( duration )
{
	org = Spawn( "script_origin", ( 0, 0, 1 ) );
	org.origin = self.origin;
	org PlaySound( "predator_drone_static", "sounddone" );

	static = NewClientHudElem( self );
	static.horzAlign = "fullscreen";
	static.vertAlign = "fullscreen";
	static SetShader( "ac130_overlay_grain", 640, 480 );

	wait( duration );

	static Destroy();

	wait( 3 );

	org StopSounds();
	wait( 1 );
	org Delete();
}

player_can_cycle_uav_rigs()
{
	self endon( "controlling_UAV" );
	was_pressed = self AttackButtonPressed();
	for ( ;; )
	{
			
		pressed = self AttackButtonPressed();
		
		if ( !was_pressed && pressed )
		{
			self.current_uav_index++;
			self.current_uav_index %= self.uav_rigs.size;
			
			rig = player_uav_rig();
			self Unlink();

			val = level.uav_struct.view_cone;
			self PlayerLinkWeaponViewToDelta( rig, "tag_player", 1, val, val, val, val, 1 );
			angles = rig GetTagAngles( "tag_origin" );
			self SetPlayerAngles( angles );
		}
		
		was_pressed = pressed;
		wait 0.05;
	}

}

cycle_uav_rigs()
{
	if ( self.uav_rigs.size <= 1 )
		return;

	if ( isdefined( self.cycling_rigs ) )
		return;
	self.cycling_rigs = true;
	
	
	for ( ;; )
	{
		self ent_flag_wait( "controlling_UAV" );
		
		player_can_cycle_uav_rigs();
	}
}

run_rig_function_when_player_uses_UAV( rig_function, player )
{
	dvars = [];
	dvars[ "player0" ] = "cg_playerFovScale0";
	dvars[ "player1" ] = "cg_playerFovScale1";
	dvar = dvars[ player.unique_id ];

	for ( ;; )
	{
		player ent_flag_wait( "controlling_UAV" );

		thread [[ rig_function ]]( player );

		AssertEx( !flag( "predator_missile_launch_allowed" ), "Not compatible with firing mode currently" );
	
/*		
		if ( remotemissile_move_player() )
		{
			player PlayerSetGroundReferenceEnt( self );
			player.ignoreme = true;// temporarily needed
		}
*/
		player ent_flag_waitopen( "controlling_UAV" );
		SetSavedDvar( dvar, 1 );

/*
		if ( remotemissile_move_player() )
		{
			player PlayerSetGroundReferenceEnt( undefined );
			
			AssertEx( IsDefined( player.old_origin ), "Somehow old_origin wasn't set." );
			player.ignoreme = false;
			player Unlink();
			player SetOrigin( player.old_origin );
			player SetPlayerAngles( player.old_angles );
		}
*/		
	}
}

open_view_cone()
{
	self LerpViewAngleClamp( 0, 0, 0, level.uav_struct.view_cone, level.uav_struct.view_cone, level.uav_struct.view_cone * 0.25, level.uav_struct.view_cone );
}