#include maps\_utility;
#include common_scripts\utility;
#include maps\_hud_util;
#include maps\_specialops_code;

specialops_init()
{
	// reset round stats from playerdata
	foreach ( player in level.players )
		player thread roundStat_init();
	
	if ( is_coop() )
	{
		// update difficulty:
		maps\_gameskill::setGlobalDifficulty();
	
		foreach ( idx, player in level.players )
			player maps\_gameskill::setDifficulty();
	}

	if ( !isdefined( level.so_override ) )
		level.so_override = [];

	// Be sure to enable the friendlyfire warnings for all SO maps, unless already specified not to.
	if ( !IsDefined( level.friendlyfire_warnings ) )
	{
		level.friendlyfire_warnings = true;
	}

	// SP Friendly Fire doesn't apply to SOs.
	level.no_friendly_fire_penalty = true;
	
	// precache minimap sentry icons
	PrecacheMinimapSentryCodeAssets();
	
	// End game summaries
	precachemenu( "sp_eog_summary" );
	precachemenu( "coop_eog_summary" );
	precachemenu( "coop_eog_summary2" );
	
	// helper menu to animate HUD done in menus
	precacheMenu( "surHUD_display" );
	
	// End game shellshock, just mutes the environment sounds
	PrecacheShellshock( "so_finished" );

	precacheShader( "hud_show_timer" );
//	PreCacheShader( "hud_star69icon" );

	PrecacheShader( "specops_ui_equipmentstore" );
	PrecacheShader( "specops_ui_weaponstore" );
	PrecacheShader( "specops_ui_airsupport" );
	
	so_precache_strings();

	foreach ( player in level.players )
	{
		player.so_hud_show_time = gettime() + ( so_standard_wait() * 1000 );
		player ent_flag_init( "so_hud_can_toggle" );
	}
		
	// Default timer settings
	level.challenge_time_nudge = 30;	// Yellow warning at 30 seconds
	level.challenge_time_hurry = 10;	// Red Hurry Up at 15 seconds
	
	// Function to handle crushing players when inside of a clip.
	level.func_destructible_crush_player = ::so_crush_player;
	
	// Default friendly fire scaler.
	setsaveddvar( "g_friendlyfireDamageScale", 2 );
	setsaveddvar( "turretSentryRestrictUsageToOwner", 0 );
	
	if ( isdefined( level.so_compass_zoom ) )
	{
		compass_dist = 0;
		switch ( level.so_compass_zoom )
		{
			case "close":	compass_dist = 1500; break;
			case "far":		compass_dist = 6000; break;
			default:		compass_dist = 3000; break;
		}
		if ( !issplitscreen() )
			compass_dist += ( compass_dist * 0.1 );	// Additional 10% in non-splitscreen.
		setsaveddvar( "compassmaxrange", compass_dist );
	}
	
	// Flag Inits
	flag_init( "challenge_timer_passed" );
	flag_init( "challenge_timer_expired" );
	flag_init( "special_op_succeeded" );
	flag_init( "special_op_failed" );
	flag_init( "special_op_terminated" );
	flag_init( "special_op_p1ready" );
	flag_init( "special_op_p2ready" );
	flag_init( "special_op_no_unlink" );
	flag_init( "special_op_final_xp_given" );

	// Savegames
	thread disable_saving();
	thread specialops_detect_death();

	// Dialog
	specialops_dialog_init();
	if ( is_coop() )
		maps\_specialops_battlechatter::init();
	
	if ( !isdefined( level.so_dialog_func_override ) )
		level.so_dialog_func_override = []; // allow for overriding mission specific dialogue

	// A little easier/different in solo play (mission and survival)
	// else just adjust melee damage scale in regular survival
	if ( !is_coop() )
		set_custom_gameskill_func( maps\_gameskill::solo_player_in_special_ops );
	else if ( is_survival() )
		set_custom_gameskill_func( maps\_gameskill::coop_player_in_special_ops_survival );

	// Setup the escape and failure triggers if any
	array_thread( getentarray( "trigger_multiple_SO_escapewarning", "classname" ), ::enable_escape_warning_auto );
	array_thread( getentarray( "trigger_multiple_SO_escapefailure", "classname" ), ::enable_escape_failure_auto );
	
	// Clear out the deadquote.
	level.so_deadquotes_chance = 0.5;	// 50/50 chance of using level specific deadquotes.
	setdvar( "ui_deadquote", "" );
	thread so_special_failure_hint();
	
	// For no longer opening level selection in spec ops after returning from a splitscreen game
	setdvar( "ui_skip_level_select", "1" );
	setDvar( "ui_opensummary", 0 );
	
	// clear dvar used to hide either the top or bottom minimap in splitscreen
	SetDvar( "ui_hide_minimap_splitscreen_playernum", 0 );
	
	// ---------------------- setup leaderboards ----------------------
	
	mainLeaderboard = "LB_" + level.script;
	hiddenLeaderboard = "";
	
	//if in chaos mode use chaos Leaderbaords
	if( GetDvarInt( "survival_chaos" ) == 1 )
	{
		mainLeaderboard += "_CHAOS";
	}
	
	if( is_coop() )
		mainLeaderboard += "_TEAM";	
		
	if( is_survival() )
	{
		hiddenLeaderboard = " LB_EXT_" + level.script;
		
		if( GetDvarInt( "survival_chaos" ) == 1 )
		{
			hiddenLeaderboard += "_CHAOS";
		}
		
		if( is_coop() )
			hiddenLeaderboard += "_TEAM";
	}
			
	precacheLeaderboards( mainLeaderboard + hiddenLeaderboard );
	
	// ----------------------------------------------------------------
	
	pick_starting_location_so();
	level thread setSoUniqueSavedDvars();
	
	// tell audio scripts we're in specops mode
	maps\_audio::aud_set_spec_ops(); 
	
	// register unlocks of specops levels
	register_level_unlock( "so_mw3_mission_2", "mission" );
	register_level_unlock( "so_mw3_mission_3", "mission" );
	register_level_unlock( "so_mw3_mission_4", "mission" );
	register_survival_unlock();
	
	// challenge and rank init
	maps\_rank::init();
	maps\_missions::init();
	
	// damage feedback
	enable_damagefeedback();
	
	// Adding damage feedback when AI are flashed. It's too late to
	// add this to the general damage feedback system so add it to
	// spec ops ai with a global spawn func. Update later -JC
	add_global_spawn_function( "axis", maps\_specialops_code::so_ai_flashed_damage_feedback );
	
	thread setup_XP();
	thread Unlock_hint();
	thread so_achievement_init();
}

roundStat_init()
{
	// wait a frame before player data can be touched
	wait 0.05;
	
	self setplayerdata( "round", "kills", 0 );
	self setplayerdata( "round", "killStreak", 0 );
	self setplayerdata( "round", "deaths", 0 );
	self setplayerdata( "round", "difficulty", 0 );
	self setplayerdata( "round", "score", 0 );
	self setplayerdata( "round", "timePlayed", 0 );
	self setplayerdata( "round", "wave", 0 );
	self setplayerdata( "round", "xuidTeammate", "0" );
	self setplayerdata( "round", "totalXp", 0 );
	self setplayerdata( "round", "scoreXp", 0 );
	self setplayerdata( "round", "challengeXp", 0 );
}

setSoUniqueSavedDvars()
{
	setsaveddvar( "hud_fade_ammodisplay", 	30 );
	setsaveddvar( "hud_fade_stance", 		30 );
	setsaveddvar( "hud_fade_offhand", 		30 );
	setsaveddvar( "hud_fade_compass", 		0 );
}

so_precache_strings()
{
	PrecacheString( &"SPECIAL_OPS_TIME_NULL" );
	PrecacheString( &"SPECIAL_OPS_TIME" );
	PrecacheString( &"SPECIAL_OPS_WAITING_P1" );
	PrecacheString( &"SPECIAL_OPS_WAITING_P2" );
	PrecacheString( &"SPECIAL_OPS_REVIVE_NAG_HINT" );
	PrecacheString( &"SPECIAL_OPS_CHALLENGE_SUCCESS" );
	PrecacheString( &"SPECIAL_OPS_CHALLENGE_FAILURE" );
	PrecacheString( &"SPECIAL_OPS_FAILURE_HINT_TIME" );
	PrecacheString( &"SPECIAL_OPS_ESCAPE_WARNING" );
	PrecacheString( &"SPECIAL_OPS_ESCAPE_SPLASH" );
	PrecacheString( &"SPECIAL_OPS_WAITING_OTHER_PLAYER" );
	PrecacheString( &"SPECIAL_OPS_STARTING_IN" );
	PrecacheString( &"SPECIAL_OPS_UI_TIME" );
	PrecacheString( &"SPECIAL_OPS_UI_KILLS" );
	PrecacheString( &"SPECIAL_OPS_UI_DIFFICULTY" );
	PrecacheString( &"SPECIAL_OPS_UI_PLAY_AGAIN" );
	PrecacheString( &"SPECIAL_OPS_DASHDASH" );
	PrecacheString( &"SPECIAL_OPS_HOSTILES" );
	PrecacheString( &"SPECIAL_OPS_INTERMISSION_WAVENUM" );
	PrecacheString( &"SPECIAL_OPS_INTERMISSION_WAVEFINAL" );
	PrecacheString( &"SPECIAL_OPS_WAVENUM" );
	PrecacheString( &"SPECIAL_OPS_WAVEFINAL" );
	PrecacheString( &"SPECIAL_OPS_PRESS_TO_CANCEL" );
	PrecacheString( &"SPECIAL_OPS_PLAYER_IS_READY" );
	PrecacheString( &"SPECIAL_OPS_PRESS_TO_START" );
	PrecacheString( &"SPECIAL_OPS_PLAYER_IS_NOT_READY" );
	PrecacheString( &"SPECIAL_OPS_EMPTY" );
}

// Call this to get whatever the standard time before we turn the hud on is.
so_standard_wait()
{
	return 4;
}

specialops_remove_unused()
{
	entarray = getentarray();
	if ( !isdefined( entarray ) )
		return;

	special_op_state = is_specialop();
	foreach ( ent in entarray )
	{
		if ( ent specialops_remove_entity_check( special_op_state ) )
			ent Delete();
	}
	
	// reset hint dvars so they don't cross over into SP
	so_special_failure_hint_reset_dvars();
}

/*
=============
///ScriptDocBegin
"Name: enable_triggered_start( <challenge_id_start> )"
"Summary: Waits until the specified trigger is triggered, and then sets the flag which is used to kick off challenges."
"Module: Utility"
"MandatoryArg: <challenge_id_start>: Name of the flag *and* trigger that is used to start off the challenge."
"Example: enable_triggered_start( "challenge_start" );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
enable_triggeRed_start( challenge_id_start )
{
	level endon( "challenge_timer_expired" );

	trigger_ent = getent( challenge_id_start, "script_noteworthy" );
	AssertEx( isdefined( trigger_ent ), "challenge_id (" + challenge_id_start + ") was unable to match with a valid trigger." );
	
	trigger_ent waittill( "trigger" );
	flag_set( challenge_id_start );
}

/*
=============
///ScriptDocBegin
"Name: enable_triggered_complete( <challenge_id> , <challenge_id_complete> , <touch_style> )"
"Summary: Waits for all players in the game to be touching the trigger, then sets the challenge complete flag."
"MandatoryArg: <challenge_id>: Name of the trigger all players need to be touching. A matching flag will be set to true to enable any additional needed entities."
"MandatoryArg: <challenge_id_complete>: Flag to set once all players are touching the trigger."
"OptionalArg: <touch_style>: Method of touching to test. "all" = all players must be touching at the same time. "any" = all players must have touched it at some point, but don't need to currently. "freeze" = when a player touches the trigger freeze them and wait for the others."
"Module: Utility"
"Example: enable_triggered_complete( "challenge_trigger", "challenge_complete", "freeze" );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
enable_triggered_complete( challenge_id, challenge_id_complete, touch_style )
{
	level endon( "challenge_timer_expired" );

	flag_set( challenge_id );
	
	if ( !isdefined( touch_style ) )
		touch_style = "freeze";

	trigger_ent = getent( challenge_id, "script_noteworthy" );
	AssertEx( isdefined( trigger_ent ), "challenge_id (" + challenge_id + ") was unable to match with a valid trigger." );
	thread disable_mission_end_trigger( trigger_ent );
	
	switch ( touch_style )
	{
		case "all"		: wait_all_players_are_touching( trigger_ent ); break;
		case "any"		: wait_all_players_have_touched( trigger_ent, touch_style ); break;
		case "freeze"	: wait_all_players_have_touched( trigger_ent, touch_style ); break;
	}

	level.challenge_end_time = gettime();
	flag_set( challenge_id_complete );
}

/*
=============
///ScriptDocBegin
"Name: fade_challenge_in( <wait_time>, <doDialogue> )"
"Summary: Simple fade in for use at the start of challenges without anything special for their intro."
"Module: Utility"
"OptionalArg: <wait_time>: If defined will wait on black for specified time."
"OptionalArg: <doDialogue>: Sets whether the 'ready up' dialogue will play after fading the screen up."
"Example: fade_challenge_in();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
fade_challenge_in( wait_time, doDialogue )
{
	// default kill counter, replaceable
	if ( !is_survival() )
	{
		// currently only for mission bases SO levels
		foreach ( player in level.players )
			player thread enable_kill_counter();
	}
	
	if ( !isdefined( wait_time ) )
		wait_time = 0.5;
	
	alpha = 1;
	if ( isdefined( level.so_waiting_for_players_alpha ) )
		alpha = level.so_waiting_for_players_alpha;
	screen_fade = create_client_overlay( "black", alpha );

	wait( wait_time );
	level notify( "challenge_fading_in" );

	fadeUpTime = 1;
	screen_fade thread fade_over_time( 0, fadeUpTime );
	level thread notify_delay( "challenge_fadein_complete", fadeUpTime );
	
	if ( flag_exist( "slamzoom_finished" ) )
		flag_wait( "slamzoom_finished" );
	
	wait 0.75;
	
	if( !IsDefined( doDialogue ) || doDialogue )
	{
		thread so_dialog_ready_up();
	}
}

/*
=============
///ScriptDocBegin
"Name: fade_challenge_out( <challenge_id>, <skipDialog> )"
"Summary: Freezes players, fades out music, fades out the scene, and if requested posts an end of game summary."
"Module: Utility"
"OptionalArg: <challenge_id>: Flag to wait to be set before completing the challenge."
"OptionalArg: <skipDialog>: Set to true to skip outro dialog"
"Example: fade_challenge_out( "challenge_complete", true );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
fade_challenge_out( challenge_id, skipDialog )
{
	if ( !isdefined( skipDialog ) )
		skipDialog = false;
	
	if ( isdefined( challenge_id ) )
		flag_wait( challenge_id );
	
	do_sarcasm = undefined;
	
	// in survival, you can always do better, and we only do dialog after certain number of waves
	if ( is_survival() )
	{
		assert( isdefined( level.current_wave ) && isdefined( level.congrat_min_wave ) );
		
		do_sarcasm = true;
		
		if ( !skipDialog )
			skipDialog = ( level.current_wave < level.congrat_min_wave );
	}

	if ( !skipDialog )
		thread so_dialog_mission_success( do_sarcasm );	
	
	// setup end of game stat data player.so_eog_summary_data
	maps\_endmission::so_eog_summary_calculate( true );
	
	// wrap up end mission and leaderboard setup
	specialops_mission_over_setup( true );
	
	so_mission_complete_achivements();
	
	// survival force dead quotes since player die and mission can be success
	if ( is_survival() )
		level notify( "so_generate_deathquote" );
	
//	// remove all counters
//	foreach ( player in level.players )
//	{
//		player disable_challenge_counter_all();
//	}
	
	// opens end of game summary menus
	maps\_endmission::so_eog_summary_display();
}

/*
=============
///ScriptDocBegin
"Name: override_summary_time( <time_in_milliseconds> )"
"Summary: Overwrites play time for end of game summary and leaderboard. Called on a player."
"Module: Utility"
"OptionalArg: <time_in_milliseconds>: Time in milliseconds."
"Example: level.player override_summary_time( 349950 );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
override_summary_time( time_in_milliseconds )
{
	// Round the time to the tenths place and round up. This
	// is to keep all time recordings in spec ops consistent
	self.so_eog_summary_data[ "time" ] = maps\_utility::round_millisec_on_sec( time_in_milliseconds, 1, false );
}

/*
=============
///ScriptDocBegin
"Name: override_summary_kills( <kills> )"
"Summary: Overwrites play time for end of game summary and leaderboard. Called on a player."
"Module: Utility"
"OptionalArg: <kills>: Number of kills."
"Example: level.player override_summary_kills( 5 );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
override_summary_kills( kills )
{
	self.so_eog_summary_data[ "kills" ] = kills;
}

/*
=============
///ScriptDocBegin
"Name: override_summary_score( <score_int> )"
"Summary: Overwrites player score for end of game summary and leaderboard. Called on a player."
"Module: Utility"
"OptionalArg: <score_int>: Score integer."
"Example: level.player override_summary_score( 349950 );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
override_summary_score( score )
{
	self.so_eog_summary_data[ "score" ] = score;
}

/*
=============
///ScriptDocBegin
"Name: enable_countdown_timer( <time_wait>, <set_start_time>, <message>, <timer_draw_delay> )"
"Summary: Creates a timer on the screen that countsdown and marks the start of the challenge time when the timer has expired."
"Module: Utility"
"MandatoryArg: <time_wait>: The amount of time to count down from and wait."
"OptionalArg: <set_start_time>: If true, then will set level.challenge_start_time once the timer completes."
"OptionalArg: <message>: Optional message to display."
"OptionalArg: <timer_draw_delay>: When set, will pause for this long before drawing the timer after the message."
"Example: enable_start_countdown( 10 );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
enable_countdown_timer( time_wait, set_start_time, message, timer_draw_delay )
{
	level endon( "special_op_terminated" );
	
	if ( !isdefined( message ) )
		message = &"SPECIAL_OPS_STARTING_IN";
	
	hudelem = so_create_hud_item( 0, so_hud_ypos(), message );
	hudelem SetPulseFX( 50, time_wait * 1000, 500 );

	hudelem_timer = so_create_hud_item( 0, so_hud_ypos() );
	hudelem_timer thread show_countdown_timer_time( time_wait, timer_draw_delay );
	
	wait time_wait;
	level.player PlaySound( "arcademode_zerodeaths" );
	
	if ( isdefined( set_start_time ) && set_start_time )
		level.challenge_start_time = gettime();

	thread destroy_countdown_timer( hudelem, hudelem_timer );
}

destroy_countdown_timer( hudelem, hudelem_timer )
{
	wait 1;		
	hudelem Destroy();
	hudelem_timer Destroy();
}

show_countdown_timer_time( time_wait, delay )
{
	self.alignX = "left";
	self settenthstimer( time_wait );
	self.alpha = 0;

	if ( !isdefined( delay ) )
		delay = 0.625;
	wait delay;
	time_wait = int( ( time_wait - delay ) * 1000 );

	self SetPulseFX( 50, time_wait, 500 );
	self.alpha = 1;
}

/*
=============
///ScriptDocBegin
"Name: enable_challenge_timer( <start_flag> , <passed_flag> , <message> )"
"Summary: Will put up an on screen timer that counts down if level.challenge_time_limit is set, otherwise counts up from 0:00.0."
"Module: Utility"
"MandatoryArg: <start_flag>: Flag that the script will wait for before starting the timer."
"MandatoryArg: <passed_flag>: Flag that the script will wait for to determine challenge success and stop the timer."
"OptionalArg: <message>: Custom message you want displayed in front of the timer."
"OptionalArg: <no_display>: Makes it so the timer is never displayed. This also disables player toggling of the timer using actionslot1."
"Example: enable_challenge_timer( "player_reached_start", "player_reached_end", "Time remaining: " );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
enable_challenge_timer( start_flag, passed_flag, message, no_display )
{
	assertex( isdefined( passed_flag ), "display_challenge_timer_down() needs a valid passed_flag." );

	if ( isdefined( start_flag ) )
	{	
		if ( !flag_exist( start_flag ) )
			flag_init( start_flag );
		level.start_flag = start_flag;
	}
	
	if ( isdefined( passed_flag ) )
	{	
		if ( !flag_exist( passed_flag ) )
			flag_init( passed_flag );
		level.passed_flag = passed_flag;
	}
	
	if ( !isdefined( message ) )
		message = &"SPECIAL_OPS_TIME";

	if ( !isdefined( level.challenge_time_beep_start ) )
		level.challenge_time_beep_start = level.challenge_time_hurry;
	level.so_challenge_time_beep = level.challenge_time_beep_start + 1;

	foreach ( player in level.players )
	{
		player thread challenge_timer_player_setup( start_flag, passed_flag, message, no_display );
	}
}

/*
=============
///ScriptDocBegin
"Name: enable_challenge_counter( <line_index>, <label>, <message> )"
"Summary: Will put up an on screen counter."
"Module: Utility"
"MandatoryArg: <line_index>: Integer value that defines the 'Y' position in terms of lines."
"MandatoryArg: <label>: String, name for the counter."
"MandatoryArg: <message>: Notify message to update counter. It is required an integer value be passed with the notify message as a parameter."
"Example: level.player enable_challenge_counter( 2, "@UI_KILLS", "kill_count" );"
"SPMP: coop"
///ScriptDocEnd
=============
*/

enable_challenge_counter( line_index, label, message )
{
	AssertEx( IsDefined( self ) && IsPlayer( self ), "Self must be player." );
	
	if ( !IsDefined( self.hud_so_counter_messages ) )
	{
		self.hud_so_counter_messages = [];
	}
	
	if ( !IsDefined( self.hud_so_counter_values ) )
	{
		self.hud_so_counter_values = [];
	}
		
	self thread enable_challenge_counter_think( line_index, label, message );
}

enable_challenge_counter_think( line_index, label, message )
{
	level endon( "special_op_terminated" );
	
	Assert( IsDefined( self.hud_so_counter_messages ) && IsDefined( self.hud_so_counter_values ), "enable_challenge_counter_think() should not be called directly, use enable_challenge_counter()." );
	
	// instance replaced by newer counter display call
	disable_challenge_counter( line_index );
	self endon( challenge_counter_get_disable_notify( line_index ) );
	
	ypos = maps\_specialops::so_hud_ypos();
	self.hud_so_counter_messages[ line_index ] = maps\_specialops::so_create_hud_item( line_index, ypos, label, self );
	self.hud_so_counter_values[ line_index ] = maps\_specialops::so_create_hud_item( line_index, ypos, undefined, self );
	self.hud_so_counter_values[ line_index ] SetText( 0 );
	self.hud_so_counter_values[ line_index ].alignX = "left";
	
	// Child Thread these because at any time the counter could be removed by
	// the level scripter ending this thread and making the passed hud element invalid
	self childthread maps\_specialops::info_hud_handle_fade( self.hud_so_counter_messages[ line_index ] );
	self childthread maps\_specialops::info_hud_handle_fade( self.hud_so_counter_values[ line_index ] );
	
	if( !IsDefined( level.challenge_counter_start_immediately ) || !level.challenge_counter_start_immediately )
	{
		flag_wait( level.start_flag );
	}
	
	while( true )
	{
		self waittill( message, value );
		assertex( isdefined( value ), "Incorrect use of enable_challenge_counter(), an integer must be passed as a parameter of notify '"+ message +"'." );
		self.hud_so_counter_values[ line_index ] SetText( value );
	}
}

/*
=============
///ScriptDocBegin
"Name: disable_challenge_counter( <line_index> )"
"Summary: Will remove the current on screen counter with the specified line index."
"Module: Entity"
"CallOn: A player"
"MandatoryArg: <line_index>: Counter line to remove."
"Example: level.player disable_challenge_counter( 1 );"
"SPMP: coop"
///ScriptDocEnd
=============
*/

disable_challenge_counter( line_index )
{
	AssertEx( IsDefined( line_index ), "The line index must be defined." );
	AssertEx( IsDefined( self ) && IsPlayer( self ), "Self must be player." );
	
	line_index = Int( line_index );
	
	self notify( challenge_counter_get_disable_notify( line_index ) );
	
	if ( IsDefined( self.hud_so_counter_messages[ line_index ] ) )
	{
		self.hud_so_counter_messages[ line_index ] Destroy();
	}
		
	if ( IsDefined( self.hud_so_counter_values[ line_index ] ) )
	{
		self.hud_so_counter_values[ line_index ] Destroy();
	}
}

disable_challenge_counter_all()
{
	// Early out if there are now counters
	if ( IsDefined( self.hud_so_counter_messages ) )
	{
		foreach ( line_index, hud_msg in self.hud_so_counter_messages )
		{
			self disable_challenge_counter( line_index );
		}
		
		self.hud_so_counter_messages = [];
		self.hud_so_counter_values = [];
	}
}

challenge_counter_get_disable_notify( line_index )
{
	AssertEx( IsDefined( line_index ), "The line index must be defined." );
	line_index = int( line_index );
	
	return "challenge_counter_disable" + line_index;
}

/*
=============
///ScriptDocBegin
"Name: enable_kill_counter()"
"Summary: Creates an on screen kill counter on line index 2. A good example of how to use the counter hud item system."
"Module: Utility"
"CallOn: A player"
"Example: level.player enable_kill_counter();"
"SPMP: coop"
///ScriptDocEnd
=============
*/

enable_kill_counter()
{
	level.kill_counter_line_index = 2;
	
	level endon( "special_op_terminated" );
	
	// In case another kill counter was created before the 
	// below flag was set.
	self notify( "enabling_kill_counter" );
	self endon( "enabling_kill_counter" );
	
	//flag_wait( level.start_flag );
	
	self thread enable_challenge_counter( level.kill_counter_line_index, &"SPECIAL_OPS_KILL_COUNT", "ui_kill_count" );
	
	// Called after the generic think so that the notify used
	// to remove previous counters on the specified line does
	// not stomp this thread.
	self thread enable_kill_counter_think( level.kill_counter_line_index );
}

enable_kill_counter_think( line_index )
{
	level endon( "special_op_terminated" );
	self endon( challenge_counter_get_disable_notify( line_index ) );
	
	while( true )
	{
		level waittill( "specops_player_kill", attacker, victim );
		
		assert( isdefined( attacker.stats ) && isdefined( attacker.stats[ "kills" ] ) );
		
		if( self == attacker )
			self notify( "ui_kill_count", attacker.stats[ "kills" ] );
	}
}

/*
=============
///ScriptDocBegin
"Name: disable_kill_counter()"
"Summary: Removes the kill counter created with enable_kill_counter(). This is on line 2. If you replaced this counter with something else, this call will still delete that counter."
"Module: Utility"
"CallOn: A player"
"Example: level.player disable_kill_counter();"
"SPMP: coop"
///ScriptDocEnd
=============
*/

disable_kill_counter()
{
	if ( !IsDefined( level.kill_counter_line_index ) )
		return;
	
	disable_challenge_counter( level.kill_counter_line_index );
}

/*
=============
///ScriptDocBegin
"Name: disable_challenge_timer( <disable_challenge_timer> )"
"Summary: Will remove the timer from the screen, and prevent it from expiring and ending the mission."
"Module: Utility"
"Example: disable_challenge_timer();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
disable_challenge_timer()
{
	level notify( "stop_challenge_timer_thread" );
}

/*
=============
///ScriptDocBegin
"Name: so_get_difficulty_menu_string( <game_skill> )"
"Summary: Takes the passed game_skill int and returns the coresponding localized menu string for that game skill."
"Module: Utility"
"OptionalArg: <game_skill>: Specified gameskill otherwise the specops lowest game skill is used."
"Example: menu_string = so_get_difficulty_menu_string();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_get_difficulty_menu_string( game_skill )
{
	AssertEx( IsDefined( game_skill ) || IsDefined( level.specops_reward_gameskill ), "game_skill param and level.specops_reward_gameskill not defined." );
	game_skill = ter_op( IsDefined( game_skill ), game_skill, level.specops_reward_gameskill );
	AssertEx( Int( game_skill ) == game_skill, "game_skill param must be an integer" );
	
	difficulty_string = "";
	
	switch ( Int( game_skill ) )
	{
		case 0:
			difficulty_string = "@MENU_RECRUIT";
			break;
		case 1:
			difficulty_string = "@MENU_REGULAR";
			break;
		case 2:
			difficulty_string = "@MENU_HARDENED";
			break;
		case 3:
			difficulty_string = "@MENU_VETERAN";
			break;
		default:
			AssertMsg( "Invalid game_skill param: " + game_skill + ". Must be >= 0 and <= 3" );
			difficulty_string = "@MENU_REGULAR";
			break;
	}
	return difficulty_string;
}

/*
=============
///ScriptDocBegin
"Name: so_wait_for_players_ready( <so_wait_for_players_ready> )"
"Summary: Waits until both players have indicated they are ready to begin the mission. Only for online co-op matches since they can't pause."
"Module: Utility"
"Example: so_wait_for_players_ready();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_wait_for_players_ready()
{
	// Disabled entirely for now.
	if ( !isdefined( level.so_enable_wait_for_players ) )
		return;
		
	if ( !is_coop() || issplitscreen() )
		return;

	level.so_waiting_for_players = true;
	level.so_waiting_for_players_alpha = 0.85;

	level.player thread so_wait_for_player_ready( "special_op_p1ready", 2 );
	level.player2 thread so_wait_for_player_ready( "special_op_p2ready", 3.25 );

	screen_hold = create_client_overlay( "black", 1 );
	screen_hold fade_over_time( level.so_waiting_for_players_alpha, 1 );

	while ( !flag( "special_op_p1ready" ) || !flag( "special_op_p2ready" ) )
		wait 0.05;

	hold_time = 1;
	
	level.player thread so_wait_for_player_ready_cleanup( hold_time );
	level.player2 thread so_wait_for_player_ready_cleanup( hold_time );

	wait hold_time;
	
	screen_hold Destroy();
	level.so_waiting_for_players = undefined;
}

so_wait_for_player_ready( my_flag, y_line )
{
	self endon( "stop_waiting_start" );

	self freezecontrols( true );
	self disableweapons();
	
	self.waiting_to_start_hud = so_create_hud_item( 0, 0, &"SPECIAL_OPS_PRESS_TO_START", self, true );
	self.waiting_to_start_hud.alignx = "center";
	self.waiting_to_start_hud.horzAlign = "center";

	self.ready_indication_hud = so_create_hud_item( y_line, 0, &"SPECIAL_OPS_PLAYER_IS_NOT_READY", undefined, true );
	self.ready_indication_hud.alignx = "center";
	self.ready_indication_hud.horzAlign = "center";
	self.ready_indication_hud settext( self.playername );
	self.ready_indication_hud set_hud_yellow();

	// Need a tiny wait in order for the blur to stick.
	wait 0.05;
	self setBlurForPlayer( 6, 0 );

	NotifyOnCommand( self.unique_id + "_is_ready", "+gostand" );
	NotifyOnCommand( self.unique_id + "_is_not_ready", "+stance" );
	
	while ( 1 )
	{
		self waittill( self.unique_id + "_is_ready" );
		flag_set( my_flag );
		self PlaySound( "so_player_is_ready" );
		self.waiting_to_start_hud.label = &"SPECIAL_OPS_PRESS_TO_CANCEL";
		self.ready_indication_hud so_hud_pulse_success( &"SPECIAL_OPS_PLAYER_IS_READY" );
		
		self waittill( self.unique_id + "_is_not_ready" );
		flag_clear( my_flag );
		self PlaySound( "so_player_not_ready" );
		self.waiting_to_start_hud.label = &"SPECIAL_OPS_PRESS_TO_START";
		self.ready_indication_hud so_hud_pulse_warning( &"SPECIAL_OPS_PLAYER_IS_NOT_READY" );
	}
}

so_wait_for_player_ready_cleanup( hold_time )
{
	self notify( "stop_waiting_start" );
	self.waiting_to_start_hud thread so_remove_hud_item( true );
	
	wait hold_time;
	
	self.ready_indication_hud thread so_remove_hud_item( false, true );
	self freezecontrols( false );
	self enableweapons();
	self setBlurForPlayer( 0, 0.5 );
}

/*
=============
///ScriptDocBegin
"Name: attacker_is_p1( <attacker> )"
"Summary: Returns true if the attacker was player 1."
"Module: Utility"
"MandatoryArg: <attacker>: Entity to test against player 1."
"Example: credit_player_1 = attacker_is_p1( attacker );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
attacker_is_p1( attacker )
{
	if ( !isdefined( attacker ) )
		return false;
	
	return attacker == level.player;
}

/*
=============
///ScriptDocBegin
"Name: attacker_is_p2( <attacker> )"
"Summary: Returns true if the attacker was player 2 in a co-op game."
"Module: Utility"
"MandatoryArg: <attacker>: Entity to test against player 2."
"Example: credit_player_2 = attacker_is_p2( attacker );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
attacker_is_p2( attacker )
{
	if ( !is_coop() )
		return false;

	if ( !isdefined( attacker ) )
		return false;
		
	return attacker == level.player2;
}

/*
=============
///ScriptDocBegin
"Name: enable_escape_warning( <enable_escape_warning> )"
"Summary: Waits for the flag 'player_trying_to_escape' to be set, then displays a hint to any players touching a trigger with script_noteworthy matching 'player_trying_to_escape'. Removes the hint when no longer touching the trigger. Does not currently support more than one potential exit point"
"Module: Utility"
"Example: enable_escape_warning()"
"SPMP: coop"
///ScriptDocEnd
=============
*/
enable_escape_warning()
{
	level endon( "special_op_terminated" );

	level.escape_warning_triggers = getentarray( "player_trying_to_escape", "script_noteworthy" );
	assertex( level.escape_warning_triggers.size > 0, "enable_escape_warning() requires at least one trigger with script_noteworthy = player_trying_to_escape" );

	add_hint_string( "player_escape_warning", &"SPECIAL_OPS_EMPTY", ::disable_escape_warning );
	while( true )
	{
		wait 0.05;
		foreach ( trigger in level.escape_warning_triggers )
		{
			foreach ( player in level.players )
			{
				if ( !isdefined( player.escape_hint_active ) )
				{
					if ( player istouching( trigger ) )
					{
						player.escape_hint_active = true;
						player thread ping_escape_warning();
						player display_hint_timeout( "player_escape_warning" );
					}
				}
				else
				{
					if ( !isdefined( player.ping_escape_splash ) )
						player thread ping_escape_warning();
				}
			}
		}
	}
}

/*
=============
///ScriptDocBegin
"Name: enable_escape_failure( <enable_escape_failure> )"
"Summary: Waits for the flag 'player_has_escaped' to be set, and when hit displays the deadquote indicating mission failure and ends the mission."
"Example: enable_escape_failure()"
"Module: Utility"
"SPMP: coop"
///ScriptDocEnd
=============
*/
enable_escape_failure()
{
	level endon( "special_op_terminated" );

	flag_wait( "player_has_escaped" );

	level.challenge_end_time = gettime();

	so_force_deadquote( "@DEADQUOTE_SO_LEFT_PLAY_AREA" );
	maps\_utility::missionFailedWrapper();
}

/*
=============
///ScriptDocBegin
"Name: so_delete_all_by_type( <function pointer 1>, <function pointer 2>, ... , <function pointer 5> )"
"Summary: Run this in first frame. Deletes level entities that do not have the key 'script_specialops 1', that are defined by function pointer passed in. This function can delete 5 types of entities at once."
"Module: Utility"
"MandatoryArg: <function pointer 1> These functions passed in must return a boolean. Example type_vehicle() will return isSubStr( self.code_classname, "script_vehicle" );"
"Example: so_delete_all_by_type( ::type_spawn_trigger, ::type_vehicle, ::type_spawners );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
// type definition function is called on the entity, it must return boolean without sleep
so_delete_all_by_type( type1_def_func, type2_def_func, type3_def_func, type4_def_func, type5_def_func, should_notify_before_delete )
{
	if(!isdefined(should_notify_before_delete))
		should_notify_before_delete = false;
		
	check_arr = [ type1_def_func, type2_def_func, type3_def_func, type4_def_func, type5_def_func ];
	check_arr = array_removeUndefined(check_arr);
		
	all_ents = getentarray();
	foreach( ent in all_ents )
	{
		if ( !isdefined( ent.code_classname ) )
			continue;

		isSpecialOpEnt = ( isdefined( ent.script_specialops ) && ent.script_specialops == 1 );
		if( isSpecialOpEnt )
			continue;
			
		//intel items are handled by the _intelligence script...they need to do more than just delete the trigger.
		isIntelItem = ( isdefined( ent.targetname ) && ent.targetname == "intelligence_item" );
		if( isIntelItem )
			continue;
		
		foreach( f in check_arr )
		{
			if( ent [[ f ]]() )
			{
				if(should_notify_before_delete)
					ent notify("delete");
				ent delete();
			}
		}
	}	
}

//============= some entity type function definitions ================
// ENTITY TYPE DEFINITION FUNCTIONS RETURN BOOLEAN TEST ON SELF
type_spawners()
{
	if ( !isdefined( self.code_classname ) )
		return false;
		
	return isSubStr( self.code_classname, "actor_" );	
}

type_vehicle()
{
	if ( !isdefined( self.code_classname ) )
		return false;
	
	//if you like collision on your so spawned vehicles you should not delete their coll maps
	if ( self.code_classname == "script_vehicle_collmap" )
		return false;		
		
	return isSubStr( self.code_classname, "script_vehicle" );
}

type_spawn_trigger()
{
	if ( !isdefined( self.classname ) )
		return false;

	if ( self.classname == "trigger_multiple_spawn" ) 
		return true;

	if ( self.classname == "trigger_multiple_spawn_reinforcement" )
		return true;

	if ( self.classname == "trigger_multiple_friendly_respawn" )
		return true;

	if ( isdefined( self.targetname ) && self.targetname == "flood_spawner" )
		return true;

	if ( isdefined( self.targetname ) && self.targetname == "friendly_respawn_trigger" )
		return true;

	if ( isdefined( self.spawnflags ) && self.spawnflags & 32 )
		return true;

	return false;
}

type_trigger()
{
	if ( !isdefined( self.code_classname ) )
		return false;
		
	array = [];
	array[ "trigger_multiple" ]	= 1;
	array[ "trigger_once" ]		= 1;
	array[ "trigger_use" ]		= 1;
	array[ "trigger_radius" ]	= 1;
	array[ "trigger_lookat" ]	= 1;
	array[ "trigger_disk" ]		= 1;
	array[ "trigger_damage" ]	= 1;
	
	return isdefined( array[ self.code_classname ] );
}

type_flag_trigger()
{
	if ( !IsDefined( self.classname ) )
	{
		return false;
	}
		
	array = [];
	array[ "trigger_multiple_flag_set" ]			= 1;
	array[ "trigger_multiple_flag_set_touching" ]	= 1;
	array[ "trigger_multiple_flag_clear" ]			= 1;
	array[ "trigger_multiple_flag_looking" ]		= 1;
	array[ "trigger_multiple_flag_lookat" ]			= 1;
	
	return IsDefined( array[ self.classname ] );
}

type_killspawner_trigger()
{
	if( !self type_trigger() )
	{
		return false;
	}
	
	if( IsDefined( self.script_killspawner ) )
	{
		return true;
	}
	
	return false;
}

type_goalvolume()
{
	if( !IsDefined( self.classname ) )
	{
		return false;
	}
	
	if( self.classname == "info_volume" && IsDefined( self.script_goalvolume ) )
	{
		return true;
	}
	
	return false;
}

type_infovolume()
{
	if( !IsDefined( self.classname ) )
	{
		return false;
	}
	
	return self.classname == "info_volume";
}

type_turret()
{
	if ( !IsDefined( self.classname ) )
	{
		return false;
	}
	
	return self.classname == "misc_turret";
}

type_weapon_placed()
{
	if( !IsDefined( self.classname ) || !IsDefined( self.model ) )
	{
		return false;
	}
	
	if( StrTok( self.classname, "_" )[ 0 ] == "weapon" )
	{
		return true;
	}
	
	return false;
}

/*
=============
///ScriptDocBegin
"Name: so_delete_all_spawntriggers()"
"Summary: Deletes all spawn triggers without the key 'script_specialops 1'."
"Example: so_delete_all_spawntriggers();"
"Module: Utility"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_delete_all_spawntriggers()
{
	so_delete_all_by_type( ::type_spawn_trigger );
}

/*
=============
///ScriptDocBegin
"Name: so_delete_all_triggers()"
"Summary: Deletes all triggers without the key 'script_specialops 1'."
"Example: so_delete_all_triggers();"
"Module: Utility"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_delete_all_triggers()
{
	so_delete_all_by_type( ::type_trigger, ::type_spawn_trigger, ::type_flag_trigger, ::type_killspawner_trigger );
	
	// Clean up bcs triggers which may now be undefined because
	// of the above trigger deletes
	animscripts\battlechatter::update_bcs_locations();
}

/*
=============
///ScriptDocBegin
"Name: so_delete_all_vehicles()"
"Summary: Deletes all script vehicles without the key 'script_specialops 1'."
"Example: so_delete_all_vehicles();"
"Module: Utility"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_delete_all_vehicles()
{
	so_delete_all_by_type( ::type_vehicle, undefined, undefined, undefined, undefined, true );
}

/*
=============
///ScriptDocBegin
"Name: so_delete_all_spawners()"
"Summary: Deletes all spawners without the key 'script_specialops 1'."
"Module: Utility"
"Example: so_delete_all_spawners();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_delete_all_spawners()
{
	so_delete_all_by_type( ::type_spawners );
}

/*
=============
///ScriptDocBegin
"Name: so_make_specialops_ent()"
"Summary: Gives the key 'script_specialops 1' to ents matching key/value."
"Module: Utility"
"Example: so_make_specialops_ent( "trigger_multiple_visionset", "classname" );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_make_specialops_ent( key, value, include_linked_ents )
{
	ents = getentarray( key, value );
	
	so_array_make_specialops( ents, include_linked_ents );
}

/*
=============
///ScriptDocBegin
"Name: so_make_bcslocations_specialops_ent()"
"Summary: Gives the key 'script_specialops 1' to bcs location triggers."
"Module: Utility"
"Example: so_make_bcslocations_specialops_ent();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_make_bcslocations_specialops_ent()
{
	so_array_make_specialops( anim.bcs_locations );
}

so_array_make_specialops( array, include_linked_ents )
{
	if ( !isdefined( include_linked_ents ) )
		include_linked_ents = false;
		
	level.so_traversed_list = []; // need to create this list to prevent infinite loops in so_make_specialops_ent_internal
	so_make_specialops_ent_internal( array, include_linked_ents );
	level.so_traversed_list = undefined;
}


// THIS IS FOR INTERNAL USE ONLY
so_make_specialops_ent_internal( ents, include_linked_ents )
{
	AssertEx( isdefined( level.so_traversed_list ), "level.so_traversed_list is undefined! You should not be using this function, use so_array_make_specialops instead!" );
	
	foreach ( ent in ents )
	{
		if ( array_contains( level.so_traversed_list, ent ) )
			continue;
			
		level.so_traversed_list[ level.so_traversed_list.size ] = ent;
		ent.script_specialops = 1;
		if ( include_linked_ents )
		{
			if ( isdefined( ent.target ) )
			{
				attached = getentarray( ent.target, "targetname" );
				so_make_specialops_ent_internal( attached, include_linked_ents );
			}
			
			if ( isdefined( ent.linkTo ) )
			{
				attached = ent get_linked_ents();
				so_make_specialops_ent_internal( attached, include_linked_ents );
			}
		}
	}
}

so_delete_breach_ents()
{
	breach_solids = getentarray( "breach_solid", "targetname" );
	foreach( ent in breach_solids )
	{
		ent connectPaths();
		ent delete();
	}
}

/*
=============
///ScriptDocBegin
"Name: so_force_deadquote( <quote> )"
"Summary: Utility function to easily force the game to use a specific Special Ops deadquote."
"Module: Utility"
"MandatoryArg: <quote>: Message you want displayed on the Mission Failed summary."
"Example: so_force_deadquote( &"SPECIAL_OPS_YOU_SUCK" );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_force_deadquote( quote, icon_dvar )
{
	assertex( isdefined( quote ), "so_force_deadquote() requires a valid quote to be passed in." );

	level.so_deadquotes = [];
	level.so_deadquotes[ 0 ] = quote;
	level.so_deadquotes_chance = 1.0;
	
	so_special_failure_hint_reset_dvars( icon_dvar );
}

/*
=============
///ScriptDocBegin
"Name: so_force_deadquote_array( <quotes> )"
"Summary: Utility function to easily force the game to use a specific list of Special Ops deadquotes."
"Module: Utility"
"MandatoryArg: <quotes>: Messages you want displayed on the Mission Failed summary."
"Example: so_include_deadquote_array( special_quotes );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_force_deadquote_array( quotes, icon_dvar )
{
	assertex( isdefined( quotes ), "so_force_deadquote_array() requires a valid quote array to be passed in." );

	level.so_deadquotes = quotes;
	level.so_deadquotes_chance = 1.0;

	so_special_failure_hint_reset_dvars( icon_dvar );
}

/*
=============
///ScriptDocBegin
"Name: so_include_deadquote_array( <quotes> )"
"Summary: Utility function to easily add new custom deadquotes to Special Ops deadquotes Merges with any existing ones."
"Module: Utility"
"MandatoryArg: <quotes>: Messages you want added to the list being displayed on the Mission Failed summary."
"Example: so_include_deadquote_array( special_quotes );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_include_deadquote_array( quotes )
{
	assertex( isdefined( quotes ), "so_include_deadquote_array() requires a valid quote array to be passed in." );

	if ( !isdefined( level.so_deadquotes ) )
		level.so_deadquotes = [];
	level.so_deadquotes = array_merge( level.so_deadquotes , quotes );
}

/*
=============
///ScriptDocBegin
"Name: so_create_hud_item( <yLine>, <xOffset> , <message>, <player>, <always_draw> )"
"Summary: Useful for creating the hud items that line up on the right side of the screen for typical Special Ops information."
"Module: Hud"
"OptionalArg: <yLine>: Line # to draw the element on. Start with 0 meaning top of the screen in split screen within the safe area."
"OptionalArg: <xOffset>: Offset for the X position."
"OptionalArg: <message>: Optional message to apply to the hudelem.label."
"OptionalArg: <player>: If a player is passed in, it will create a ClientHudElem for that player specifically."
"OptionalArg: <always_draw>: If true, then will not add itself to the list of hud elements to be toggled on and off with the dpad."
"Example: so_create_hud_item( 1, 0, &"SPECIAL_OPS_TIME_NULL", level.player2 );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_create_hud_item( yLine, xOffset, message, player, always_draw )
{
	if ( isdefined( player ) )
		assertex( isplayer( player ), "so_create_hud_item() received a value for player that did not pass the isplayer() check." );
		
	if ( !isdefined( yLine ) )
		yLine = 0;
	if ( !isdefined( xOffset ) )
		xOffset = 0;

	// This is to globally shift all the SOs down by two lines to help with overlap with the objective and help text.
	yLine += 2;

	hudelem = undefined;		
	if ( isdefined( player ) )
		hudelem = newClientHudElem( player );
	else
		hudelem = newHudElem();
	hudelem.alignX = "right";
	hudelem.alignY = "middle";
	hudelem.horzAlign = "right";
	hudelem.vertAlign = "middle";
	hudelem.x = xOffset;
	hudelem.y = -100 + ( 15 * yLine );
	hudelem.font = "hudsmall";
	hudelem.foreground = 1;
	hudelem.hidewheninmenu = true;
	hudelem.hidewhendead = true;
	hudelem.sort = 2;
	hudelem set_hud_white();

	if ( isdefined( message ) )
		hudelem.label = message;

	if ( !isdefined( always_draw ) || !always_draw )
	{
		if ( isdefined( player ) )
		{
			if ( !player so_hud_can_show() )
				player thread so_create_hud_item_delay_draw( hudelem );
			else
			{
				// If the hud can be shown turn toggling on
				// if it is not
				if ( !self ent_flag( "so_hud_can_toggle" ) )
					self ent_flag_set( "so_hud_can_toggle" );
			}
		}
	}
					
	return hudelem;
}

/*
=============
///ScriptDocBegin
"Name: so_create_hud_item_data( <yLine> , <xOffset> , <message> , <player> , <always_draw> )"
"Summary: Just like so_create_hud_item() but automatically sets it up to be in the 'data' position."
"Module: Hud"
"OptionalArg: <yLine>: Line # to draw the element on. Start with 0 meaning top of the screen in split screen within the safe area."
"OptionalArg: <xOffset>: Offset for the X position."
"OptionalArg: <message>: Optional message to apply to the hudelem.label."
"OptionalArg: <player>: If a player is passed in, it will create a ClientHudElem for that player specifically."
"OptionalArg: <always_draw>: If true, then will not add itself to the list of hud elements to be toggled on and off with the dpad."
"Example: so_create_hud_item_data( 1, 0, &"SPECIAL_OPS_TIME_NULL", level.player2 );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_create_hud_item_data( yLine, xOffset, message, player, always_draw )
{
	hudelem = so_create_hud_item( yLine, xOffset, message, player, always_draw );
	hudelem.alignX = "left";
	return hudelem;
}

/*
=============
///ScriptDocBegin
"Name: so_create_hud_item_debug( <yLine> , <xOffset> , <message> , <player> , <always_draw> )"
"Summary: Just like so_create_hud_item() but automatically sets it up to be useful for debug prints on the left side of the screen."
"Module: Hud"
"OptionalArg: <yLine>: Line # to draw the element on. Start with 0 meaning top of the screen in split screen within the safe area."
"OptionalArg: <xOffset>: Offset for the X position."
"OptionalArg: <message>: Optional message to apply to the hudelem.label."
"OptionalArg: <player>: If a player is passed in, it will create a ClientHudElem for that player specifically."
"OptionalArg: <always_draw>: If true, then will not add itself to the list of hud elements to be toggled on and off with the dpad."
"Example: so_create_hud_item_data( 1, 0, &"SPECIAL_OPS_TIME_NULL", level.player2 );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_create_hud_item_debug( yLine, xOffset, message, player, always_draw )
{
	hudelem = so_create_hud_item( yLine, xOffset, message, player, always_draw );
	hudelem.alignX = "left";
	hudelem.horzAlign = "left";
	return hudelem;
}

/*
=============
///ScriptDocBegin
"Name: so_hud_pulse_create( <new_value> )"
"Summary: Pulses the hud item and updates the label to the new value. Should always try to use the so_hud_pulse_<type> functions instead."
"Module: Hud"
"CallOn: A hud element"
"OptionalArg: <new_value>: When set to a value, will be set on the .label parameter of the hud element."
"Example: hudelem thread so_hud_pulse_create( 0 );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_hud_pulse_create( new_value )
{
	if ( !so_hud_pulse_init() )
		return;
	
	self notify( "update_hud_pulse" );
	self endon( "update_hud_pulse" );
	self endon( "destroying" );

	// Need to update this script to support SetValue AND SetText AND updating the label.
	if ( isdefined( new_value ) )
		self.label = new_value;

	if ( isdefined( self.pulse_sound ) )
		level.player PlaySound( self.pulse_sound );
		
	if ( isdefined( self.pulse_loop ) && self.pulse_loop )
		so_hud_pulse_loop();
	else
		so_hud_pulse_single( self.pulse_scale_big, self.pulse_scale_normal, self.pulse_time );
}

/*
=============
///ScriptDocBegin
"Name: so_hud_pulse_stop( <new_value> )"
"Summary: Call to take whatever current status a hud element pulse is in, and return it to normal."
"Module: Hud"
"CallOn: A hud element"
"OptionalArg: <new_value>: When start_immediately, will pass this through to be applied to the hud element's label."
"Example: hudelem thread so_hud_pulse_stop();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_hud_pulse_stop( new_value )
{
	if ( !so_hud_pulse_init() )
		return;
	
	self notify( "update_hud_pulse" );
	self endon( "update_hud_pulse" );
	self endon( "destroying" );
	
	if ( isdefined( new_value ) )
		self.label = new_value;
		
	self.pulse_loop = false;
	so_hud_pulse_single( self.fontscale, self.pulse_scale_normal, self.pulse_time );
}

/*
=============
///ScriptDocBegin
"Name: so_hud_pulse_default( <new_value> )"
"Summary: Pulses the hud element, and sets the default color for that type of pulse."
"Module: Hud"
"CallOn: A hud element"
"OptionalArg: <new_value>: When defined, will be set as the label of the new hud element."
"Example: hudelem so_hud_pulse_default( enemy_count );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_hud_pulse_default( new_value )
{
	set_hud_white();

	self.pulse_loop = false;
	so_hud_pulse_create( new_value );
}

/*
=============
///ScriptDocBegin
"Name: so_hud_pulse_close( <new_value> )"
"Summary: Pulse loops the hud element, and sets the default color for that type of pulse."
"Module: Hud"
"CallOn: A hud element"
"OptionalArg: <new_value>: When defined, will be set as the label of the new hud element."
"Example: hudelem so_hud_pulse_close( enemy_count );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_hud_pulse_close( new_value )
{
	set_hud_green();

	self.pulse_loop = true;
	so_hud_pulse_create( new_value );
}

/*
=============
///ScriptDocBegin
"Name: so_hud_pulse_success( <new_value> )"
"Summary: Pulses the hud element, and sets the default color for that type of pulse."
"Module: Hud"
"CallOn: A hud element"
"OptionalArg: <new_value>: When defined, will be set as the label of the new hud element."
"Example: hudelem so_hud_pulse_success( enemy_count );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_hud_pulse_success( new_value )
{
	set_hud_green();

	self.pulse_loop = false;
	so_hud_pulse_create( new_value );
}

/*
=============
///ScriptDocBegin
"Name: so_hud_pulse_warning( <new_value> )"
"Summary: Pulses the hud element, and sets the default color for that type of pulse."
"Module: Hud"
"CallOn: A hud element"
"OptionalArg: <new_value>: When defined, will be set as the label of the new hud element."
"Example: hudelem so_hud_pulse_warning( enemy_count );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_hud_pulse_warning( new_value )
{
	set_hud_yellow();
	
	self.pulse_loop = false;
	so_hud_pulse_create( new_value );
}

/*
=============
///ScriptDocBegin
"Name: so_hud_pulse_alarm( <new_value> )"
"Summary: Pulse loops the hud element, and sets the default color for that type of pulse."
"Module: Hud"
"CallOn: A hud element"
"OptionalArg: <new_value>: When defined, will be set as the label of the new hud element."
"Example: hudelem so_hud_pulse_alarm( enemy_count );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_hud_pulse_alarm( new_value )
{
	set_hud_red();
	
	self.pulse_loop = true;
	so_hud_pulse_create( new_value );
}

/*
=============
///ScriptDocBegin
"Name: so_hud_pulse_failure( <new_value> )"
"Summary: Pulses the hud element, and sets the default color for that type of pulse."
"Module: Hud"
"CallOn: A hud element"
"OptionalArg: <new_value>: When defined, will be set as the label of the new hud element."
"Example: hudelem so_hud_pulse_failure( enemy_count );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_hud_pulse_failure( new_value )
{
	set_hud_red();

	self.pulse_loop = false;
	so_hud_pulse_create( new_value );
}

/*
=============
///ScriptDocBegin
"Name: so_hud_pulse_disabled( <new_value> )"
"Summary: Pulses the hud element, and sets the default color for that type of pulse."
"Module: Hud"
"CallOn: A hud element"
"OptionalArg: <new_value>: When defined, will be set as the label of the new hud element."
"Example: hudelem so_hud_pulse_disabled( enemy_count );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_hud_pulse_disabled( new_value )
{
	set_hud_grey();

	self.pulse_loop = false;
	so_hud_pulse_create( new_value );
}

/*
=============
///ScriptDocBegin
"Name: so_hud_pulse_smart( <test_value>, <new_value> )"
"Summary: Pulses the hud element with the automatic style as specified with data on the hud element."
"Module: Hud"
"CallOn: A hud element"
"MandatoryArg: <test_value>: Value to check the pulse_bounds against. First thing it is less than in the bounds is the effect that will be acted upon."
"OptionalArg: <new_value>: When defined, will be set as the label of the new hud element."
"Example: hudelem so_hud_pulse_smart( enemy_count );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_hud_pulse_smart( test_value, new_value )
{
	if ( !isdefined( self.pulse_bounds ) )
	{
		self so_hud_pulse_default( new_value );
		return;
	}

	foreach ( i, bound in self.pulse_bounds )
	{
		if ( test_value <= bound )
		{
			switch ( i )
			{
				case "pulse_disabled" :	self so_hud_pulse_disabled( new_value );return;
				case "pulse_failure" :	self so_hud_pulse_failure( new_value );	return;
				case "pulse_alarm" :	self so_hud_pulse_alarm( new_value );	return;
				case "pulse_warning" :	self so_hud_pulse_warning( new_value );	return;
				case "pulse_default" :	self so_hud_pulse_default( new_value );	return;
				case "pulse_close" :	self so_hud_pulse_close( new_value );	return;
				case "pulse_success" :	self so_hud_pulse_success( new_value );	return;
			}
		}
	}

	self so_hud_pulse_default( new_value );
}

/*
=============
///ScriptDocBegin
"Name: so_hud_ypos( <so_hud_ypos> )"
"Summary: Returns the default value for SO HUD element Y positions. This is generally the split between the Text and the Value. When used allows simple adjustment of the hud to move it around in all SOs rather than hand updating each hud element."
"Module: Hud"
"CallOn: A hud element"
"Example: so_create_hud_item( 1, so_hud_ypos(), &"SPECIAL_OPS_TIME_NULL", level.player2 );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_hud_ypos()
{
	return -72;
}

/*
=============
///ScriptDocBegin
"Name: so_remove_hud_item( <destroy_immediately> )"
"Summary: Default behavior for removing an SO HUD item. Pulses out by default, but can be told to be removed immediately."
"Module: Hud"
"CallOn: A hud element"
"OptionalArg: <destroy_immediately>: When set to true, will just remove the item immediately."
"OptionalArg: <decay_immediately>: When set to true, will do the decay visuals immediately rather than holding for a moment."
"Example: hudelem so_remove_hud_item();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_remove_hud_item( destroy_immediately, decay_immediately )
{
	if ( isdefined( destroy_immediately ) && destroy_immediately )
	{
		self notify( "destroying" );
		self Destroy();
		return;
	}

	self thread so_hud_pulse_stop();

	if ( isdefined( decay_immediately ) && decay_immediately )
	{
		self SetPulseFX( 0, 0, 500 );
		wait( 0.5 );
	}
	else
	{
		self SetPulseFX( 0, 1500, 500 );
		wait( 2 );
	}
		
	self notify( "destroying" );
	self Destroy();
}

/*
=============
///ScriptDocBegin
"Name: set_hud_white( <new_alpha> )"
"Summary: Sets properties on a hud element to be a standard white color."
"Module: Hud"
"OptionalArg: <new_alpha>: Alpha to optionally set the hud element to."
"CallOn: A hud element"
"Example: hudelem set_hud_white();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
set_hud_white( new_alpha )
{
	if ( isdefined( new_alpha ) )
	{
		self.alpha = new_alpha;
		self.glowAlpha = new_alpha;
	}

	self.color = ( 1, 1, 1 );
	self.glowcolor = ( 0.6, 0.6, 0.6 );
}

/*
=============
///ScriptDocBegin
"Name: set_hud_blue( <new_alpha> )"
"Summary: Sets properties on a hud element to be a standard blue color."
"Module: Hud"
"OptionalArg: <new_alpha>: Alpha to optionally set the hud element to."
"CallOn: A hud element"
"Example: hudelem set_hud_blue();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
set_hud_blue( new_alpha )
{
	if ( isdefined( new_alpha ) )
	{
		self.alpha = new_alpha;
		self.glowAlpha = new_alpha;
	}

	self.color = ( 0.8, 0.8, 1 );
	self.glowcolor = ( 0.301961, 0.301961, 0.6 );
}

/*
=============
///ScriptDocBegin
"Name: set_hud_green( <new_alpha> )"
"Summary: Sets properties on a hud element to be a standard green color."
"Module: Hud"
"OptionalArg: <new_alpha>: Alpha to optionally set the hud element to."
"CallOn: A hud element"
"Example: hudelem set_hud_green();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
set_hud_green( new_alpha )
{
	if ( isdefined( new_alpha ) )
	{
		self.alpha = new_alpha;
		self.glowAlpha = new_alpha;
	}

	self.color = ( 0.8, 1, 0.8 );
	self.glowcolor = ( 0.301961, 0.6, 0.301961 );
}

/*
=============
///ScriptDocBegin
"Name: set_hud_yellow( <new_alpha> )"
"Summary: Sets properties on a hud element to be a standard yellow color."
"Module: Hud"
"OptionalArg: <new_alpha>: Alpha to optionally set the hud element to."
"CallOn: A hud element"
"Example: hudelem set_hud_yellow();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
set_hud_yellow( new_alpha )
{
	if ( isdefined( new_alpha ) )
	{
		self.alpha = new_alpha;
		self.glowAlpha = new_alpha;
	}

	self.color = ( 1, 1, 0.5 );
	self.glowcolor = ( 0.7, 0.7, 0.2 );
}

/*
=============
///ScriptDocBegin
"Name: set_hud_red( <new_alpha> )"
"Summary: Sets properties on a hud element to be a standard red color."
"Module: Hud"
"OptionalArg: <new_alpha>: Alpha to optionally set the hud element to."
"CallOn: A hud element"
"Example: hudelem set_hud_red();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
set_hud_red( new_alpha )
{
	if ( isdefined( new_alpha ) )
	{
		self.alpha = new_alpha;
		self.glowAlpha = new_alpha;
	}
	
	self.color = ( 1, 0.4, 0.4 );
	self.glowcolor = ( 0.7, 0.2, 0.2 );
}

/*
=============
///ScriptDocBegin
"Name: set_hud_grey( <new_alpha> )"
"Summary: Sets properties on a hud element to be a standard grey color."
"Module: Hud"
"OptionalArg: <new_alpha>: Alpha to optionally set the hud element to."
"CallOn: A hud element"
"Example: hudelem set_hud_grey();"
"SPMP: coop"
///ScriptDocEnd
=============
*/
set_hud_grey( new_alpha )
{
	if ( isdefined( new_alpha ) )
	{
		self.alpha = new_alpha;
		self.glowAlpha = new_alpha;
	}

	self.color = ( 0.4, 0.4, 0.4 );
	self.glowcolor = ( 0.2, 0.2, 0.2 );
}

/*
=============
///ScriptDocBegin
"Name: info_hud_wait_for_player( <info_hud_wait_for_player> )"
"Summary: When run on a player, waits for them to press the appropriate key and sends a notify that will allow certain hud elements to become visible for a while before fading them back out."
"Module: Hud"
"CallOn: A player"
"OptionalArg: <endon_notify>: If a value is passed in, will create a level endon( endon_notify ) to terminate the function."
"Example: level.player info_hud_wait_for_player( "special_op_complete" );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
info_hud_wait_for_player( endon_notify )
{
	assertex( isplayer( self ), "info_hud_wait_for_player() must be called on a player." );

	// Prevent thread from being initiated multiple times.
	if ( isdefined( self.so_infohud_toggle_state ) )
		return;
			
	level endon( "challenge_timer_expired" );
	level endon( "challenge_timer_passed" );
	level endon( "special_op_terminated" );
	self endon( "death" );
	if ( isdefined( endon_notify ) )
		level endon( endon_notify );

	self setWeaponHudIconOverride( "actionslot1", "hud_show_timer" );
	notifyoncommand( "toggle_challenge_timer", "+actionslot 1" );
	self.so_infohud_toggle_state = info_hud_start_state();

	if ( !so_hud_can_show() )
	{
		thread info_hud_wait_force_on();
		self ent_flag_wait( "so_hud_can_toggle" );
	}

	self notify( "so_hud_toggle_available" );
	while ( 1 )
	{
		self waittill( "toggle_challenge_timer" );
		switch( self.so_infohud_toggle_state )
		{
			case "on":
				self.so_infohud_toggle_state = "off";
				setdvar( "so_ophud_" + self.unique_id, "0" );
				break;
			case "off":
				self.so_infohud_toggle_state = "on";
				setdvar( "so_ophud_" + self.unique_id, "1" );
				break;
		}
		self notify( "update_challenge_timer" );
	}
}

info_hud_wait_force_on()
{
	self endon( "so_hud_toggle_available" );
	
	notifyoncommand( "force_challenge_timer", "+actionslot 1" );
	self waittill( "force_challenge_timer" );
	self.so_hud_show_time = gettime();
	self.so_infohud_toggle_state = "on";
	setdvar( "so_ophud_" + self.unique_id, "1" );
}

info_hud_start_state()
{
	if ( getdvarint( "so_ophud_" + self.unique_id ) == 1 )
	{
		self.so_hud_show_time = gettime() + 1000;
		return "on";
	}

	if ( isdefined( level.challenge_time_limit ) )
		return "on";

	if ( isdefined( level.challenge_time_force_on ) && level.challenge_time_force_on )
		return "on";
		
	return "off";
}

/*
=============
///ScriptDocBegin
"Name: info_hud_handle_fade( <hudelem>, <endon_notify> )"
"Summary: When called on a player and a hudelement is passed in, it will wait for the notifies from info_hud_wait_for_player() and fade the item in or out as needed."
"Module: Hud"
"CallOn: A player"
"MandatoryArg: <hudelem>: Hud element to fade in and out."
"OptionalArg: <endon_notify>: If a value is passed in, will create a level endon( endon_notify ) to terminate the function."
"Example: level.player info_hud_handle_fad( timer_hud, "special_op_complete" );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
info_hud_handle_fade( hudelem, endon_notify )
{
	assertex( isplayer( self ), "info_hud_handle_fade() must be called on a player." );
	assertex( isdefined( hudelem ), "info_hud_handle_fade() requires a valid hudelem to be passed in." );
	
	level endon( "new_challenge_timer" );
	level endon( "challenge_timer_expired" );
	level endon( "challenge_timer_passed" );
	level endon( "special_op_terminated" );
	self endon( "death" );
	if ( isdefined( endon_notify ) )
		level endon( endon_notify );
	
	hudelem.so_can_toggle = true;

	self ent_flag_wait( "so_hud_can_toggle" );
	info_hud_update_alpha( hudelem );

	while( 1 )
	{
		self waittill( "update_challenge_timer" );
		hudelem FadeOverTime( 0.25 );
		info_hud_update_alpha( hudelem );
	}
}

info_hud_update_alpha( hudelem )
{
	switch( self.so_infohud_toggle_state )
	{
		case "on":	hudelem.alpha = 1;	break;
		case "off":	hudelem.alpha = 0;	break;
	}
}

/*
=============
///ScriptDocBegin
"Name: info_hud_decrement_timer( <time> )"
"Summary: Modifies the global challenge timer to subract the specified time from the current time."
"Module: Hud"
"MandatoryArg: <time>: The amount to subtract from the global time."
"Example: info_hud_decrement_timer( level.so_missed_target_deduction )"
"SPMP: coop"
///ScriptDocEnd
=============
*/
info_hud_decrement_timer( time )
{
	if ( !IsDefined( level.challenge_time_limit  ) )
	{
		return;
	}

	if ( flag( "challenge_timer_expired" ) || flag( "challenge_timer_passed" ) )
	{
		return;
	}

	level.so_challenge_time_left -= time;

	if ( level.so_challenge_time_left < 0 )
	{
		level.so_challenge_time_left = 0.01;
	}

	red = ( 0.6, 0.2, 0.2 );
	red_glow = ( 0.4, 0.1, 0.1 );
	foreach ( player in level.players )
	{
		player.hud_so_timer_time SetTenthsTimer( level.so_challenge_time_left );

// We need to support the hurry/nudge if we really want to change the color
// Probably store an extra variable on the hud time and msg to keep track.
//		old_color 		= player.hud_so_timer_time.color;
//		old_glow  		= player.hud_so_timer_time.glowcolor;
//		old_title_color = player.hud_so_timer_msg.color;
//		old_title_glow 	= player.hud_so_timer_msg.glowcolor;
//
//		player.hud_so_timer_time.color 		= red;
//		player.hud_so_timer_time.glowcolor 	= red_glow;
//		player.hud_so_timer_msg.color 		= red;
//		player.hud_so_timer_msg.glowcolor 	= red_glow;
//		
//		player.hud_so_timer_time FadeOverTime( 0.5 );
//		player.hud_so_timer_msg FadeOverTime( 0.5 );
//		
//		player.hud_so_timer_time.color 	= old_color;
//		player.hud_so_timer_time.glowcolor 	= old_glow;
//		player.hud_so_timer_msg.color 		= old_title_color;
//		player.hud_so_timer_msg.glowcolor 	= old_title_glow;
	}

	// Restart the challenge_timer_thread
	thread challenge_timer_thread();
}

/*
=============
///ScriptDocBegin
"Name: is_dvar_character_switcher( <dvar> )"
"Summary: Tests the specified dvar to see whether the player positions have switched (for vehicle SOs)."
"Module: Utility"
"MandatoryArg: <dvar>: The dvar to test."
"Example: is_dvar_character_switcher( "specops_character_switched" )"
"SPMP: coop"
///ScriptDocEnd
=============
*/
is_dvar_character_switcher( dvar )
{
	val = getdvar( dvar );
	return val == "so_char_client" || val == "so_char_host";
}

// ---------------------------------------------------------------------------------
//	Special Ops common dialog.
// ---------------------------------------------------------------------------------
has_been_played()
{
	best_time_name = tablelookup( "sp/specOpsTable.csv", 1, level.script, 9 );
	if ( best_time_name == "" )
		return false;

	foreach( player in level.players )
	{
		current_best_time = player GetLocalPlayerProfileData( best_time_name );

		if ( !isdefined( current_best_time ) )
			continue;	// non local player

		if ( current_best_time != 0 )
			return true;			
	}
	
	return false;
}

is_best_wave( wave )
{
	/*
	foreach( player in level.players )
	{
		current_best_wave = player getplayerdata( "round", "wave" );

		if ( !isdefined( current_best_wave ) )
			continue;	// non local player
			
		never_played = ( current_best_wave == 0 );
		if ( never_played )
			continue;
		
		if ( wave > current_best_wave )
			return true;
	}
	*/
	return false;
}

is_best_time( time_start, time_current, time_frac )
{
	if ( !isdefined( time_start ) )
	{
		if ( isdefined( level.challenge_start_time ) )
			time_start = level.challenge_start_time;
		else
			time_start = 300;	// Frame time that script actually starts on.
	}
		
	if ( !isdefined( time_current ) )
		time_current = gettime();
		
	if ( !isdefined( time_frac ) )
		time_frac = 0.0;

	// Check for best time.
	m_seconds = ( time_current - time_start );
	m_seconds = int( min( m_seconds, 86400000 ) );
	best_time_name = tablelookup( "sp/specOpsTable.csv", 1, level.script, 9 );
	if ( best_time_name == "" )
		return false;
		
	foreach( player in level.players )
	{
		current_best_time = player GetLocalPlayerProfileData( best_time_name );

		if ( !isdefined( current_best_time ) )
			continue;	// non local player
			
		never_played = ( current_best_time == 0 );
		if ( never_played )
			continue;
			
		current_best_time -= ( current_best_time * time_frac );
		if ( m_seconds < current_best_time )
			return true;
	}
	
	return false;
}

is_poor_time( time_start, time_current, time_frac )
{
	if ( !isdefined( time_start ) )
	{
		if ( isdefined( level.challenge_start_time ) )
			time_start = level.challenge_start_time;
		else
			time_start = 300;	// Frame time that script actually starts on.
	}
		
	if ( !isdefined( time_current ) )
		time_current = gettime();
		
	if ( !isdefined( time_frac ) )
		time_frac = 0.0;

	m_seconds = ( time_current - time_start );
	m_time_limit = ( level.challenge_time_limit * 1000 );
	m_time_limit -= ( m_time_limit * time_frac );

	return ( m_seconds > m_time_limit );
}

so_dialog_ready_up()
{
	if ( isdefined( level.so_dialog_func_override[ "ready_up" ] ) )
	{
		[[ level.so_dialog_func_override[ "ready_up" ] ]]();
		return;
	}

	so_dialog_play( "so_tf_1_plyr_prep", 0, true );
}

so_dialog_mission_success( do_sarcasm )
{
	// Check for best time.
	if ( !is_survival() && is_best_time( level.challenge_start_time, level.challenge_end_time ) )
	{
		if ( isdefined( level.so_dialog_func_override[ "success_best" ] ) )
		{
			thread [[ level.so_dialog_func_override[ "success_best" ] ]]();
			return;
		}
		
		thread so_dialog_play( "so_tf_1_success_best", 0.5, true );
		return;
	}
	
	/*
	// Check for most waves survived
	if ( is_survival() && is_best_wave( level.current_wave ) )
	{
		thread so_dialog_play( "so_tf_1_success_best", 0.5, true );
		return;
	}
	*/
	
	// Normal time.
	// Hardened and lower only get supportive success messages. Veteran has 50/50 chance to get a sarcastic.
	if ( !isdefined( do_sarcasm ) )
	{
		do_sarcasm = false;
		if ( level.gameSkill >= 3 )
		{
			if ( has_been_played() )
				do_sarcasm = cointoss();
		}
	}
	
	if ( isdefined( level.so_dialog_func_override[ "success_generic" ] ) )
	{
		[[ level.so_dialog_func_override[ "success_generic" ] ]](do_sarcasm);
		return;
	}
	
	if ( do_sarcasm )
		so_dialog_play( "so_tf_1_success_jerk", 0.5, true );
	else
		so_dialog_play( "so_tf_1_success_generic", 0.5, true );
}

/*
=============
///ScriptDocBegin
"Name: so_dialog_mission_failed( <sound_alias> )"
"Summary: Used to safely play a piece of dialog on mission failure without worry of getting duplicates. Whichever one is called first wins."
"Module: Utility"
"MandatoryArg: <sound_alias>: The sound alias in level.scr_radio"
"Example: so_dialog_mission_failed( "what_are_you_stupid" );"
"SPMP: coop"
///ScriptDocEnd
=============
*/
so_dialog_mission_failed( sound_alias )
{
	// This is designed to prevent multiple failed messages from playing. Only the first one gets played.
	assertex( isdefined( sound_alias ), "so_dialog_mission_failed() requires a valid sound_alias." );
	if ( isdefined( level.failed_dialog_played ) && level.failed_dialog_played )
		return;

	level.failed_dialog_played = true;
	so_dialog_play( sound_alias, 0.5, true );
}

so_dialog_mission_failed_generic()
{
	if ( isdefined( level.so_dialog_func_override[ "failed_generic" ] ) )
	{
		[[ level.so_dialog_func_override[ "failed_generic" ] ]]();
		return;
	}
	
	if ( ( level.gameskill <= 2 ) || cointoss() )
		so_dialog_mission_failed( "so_tf_1_fail_generic" );
	else
		so_dialog_mission_failed( "so_tf_1_fail_generic_jerk" );
}

so_dialog_mission_failed_time()
{
	if ( isdefined( level.so_dialog_func_override[ "failed_time" ] ) )
	{
		[[ level.so_dialog_func_override[ "failed_time" ] ]]();
		return;
	}
	
	so_dialog_mission_failed( "so_tf_1_fail_time" );
}

so_dialog_mission_failed_bleedout()
{
	if ( isdefined( level.so_dialog_func_override[ "failed_bleedout" ] ) )
	{
		[[ level.so_dialog_func_override[ "failed_bleedout" ] ]]();
		return;
	}
	
	so_dialog_mission_failed( "so_tf_1_fail_bleedout" );
}

so_dialog_time_low_normal()
{
	if ( isdefined( level.so_dialog_func_override[ "time_low_normal" ] ) )
	{
		[[ level.so_dialog_func_override[ "time_low_normal" ] ]]();
		return;
	}
	
	so_dialog_play( "so_tf_1_time_generic" );
}

so_dialog_time_low_hurry()
{
	if ( isdefined( level.so_dialog_func_override[ "time_low_hurry" ] ) )
	{
		[[ level.so_dialog_func_override[ "time_low_hurry" ] ]]();
		return;
	}
	
	so_dialog_play( "so_tf_1_time_hurry" );
}

so_dialog_killing_civilians()
{
	if ( !isdefined( level.civilian_warning_time ) )
	{
		level.civilian_warning_time = gettime();
		if ( !isdefined( level.civilian_warning_throttle ) )
			level.civilian_warning_throttle = 5000;
	}
	else
	{
		if ( ( gettime() - level.civilian_warning_time ) < level.civilian_warning_throttle )
			return;
	}
	
	wait_time = 0.5;
	level.civilian_warning_time = gettime() + ( wait_time * 1000 );
	
	if ( isdefined( level.so_dialog_func_override[ "killing_civilians" ] ) )
	{
		[[ level.so_dialog_func_override[ "killing_civilians" ] ]]();
		return;
	}
	
	so_dialog_play( "so_tf_1_civ_kill_warning", 0.5 );
}

// Note this doesn't account for any mission which might go "backwards" in regards to current_value.
so_dialog_progress_update( current_value, current_goal )
{
	if ( !isdefined( current_value ) )
		return;

	if ( !isdefined( current_goal ) )
		return;
		
	if ( !isdefined( level.so_progress_goal_status ) )
		level.so_progress_goal_status = "none";
	
	time_frac = undefined;
	switch ( level.so_progress_goal_status )
	{
		case "none":		time_frac = 0.75;	break;
		case "3quarter":	time_frac = 0.5;	break;
		case "half":		time_frac = 0.25;	break;
		default:			return;				// No behavior for other states.
	}
	
	test_goal = current_goal * time_frac;
	if ( current_value > test_goal )
		return;

	time_dialog = undefined;
	switch ( level.so_progress_goal_status )
	{
		case "none":
			level.so_progress_goal_status = "3quarter";		
			time_dialog = "so_tf_1_progress_3quarter";
			break;
		case "3quarter":
			level.so_progress_goal_status = "half";		
			time_dialog = "so_tf_1_progress_half";
			break;
		case "half":
			level.so_progress_goal_status = "quarter";	
			time_dialog = "so_tf_1_progress_quarter";
			break;
	}

	if ( isdefined( level.so_dialog_func_override[ "progress_goal_status" ] ) )
	{
		[[ level.so_dialog_func_override[ "progress_goal_status" ] ]]();
		return;
	}

	so_dialog_play( time_dialog, 0.5 );
//	so_dialog_progress_update_time_quality( time_frac );
}

so_dialog_progress_update_time_quality( time_frac )
{
	// Even if this is their best time so far, always warn about running late first.
	if ( isdefined( level.challenge_time_limit ) )
	{
		if ( is_poor_time( level.challenge_start_time, gettime(), time_frac ) )
		{
			if ( isdefined( level.so_dialog_func_override[ "time_status_late" ] ) )
			{
				[[ level.so_dialog_func_override[ "time_status_late" ] ]]();
				return;
			}
			so_dialog_play( "so_tf_1_time_status_late", 0.2 );
			return;
		}
	}

	if ( is_best_time( level.challenge_start_time, gettime(), time_frac ) )
	{
		if ( isdefined( level.so_dialog_func_override[ "time_status_good" ] ) )
		{
			[[ level.so_dialog_func_override[ "time_status_good" ] ]]();
			return;
		}
		so_dialog_play( "so_tf_1_time_status_good", 0.2 );
	}
}

so_dialog_counter_update( current_count, current_goal, countdown_divide )
{
	// Prevent overlaps happening quickly.
	if ( !isdefined( level.so_counter_dialog_time ) )
		level.so_counter_dialog_time = 0;
	if ( gettime() < level.so_counter_dialog_time )
		return;

	if ( !isdefined( current_count ) )
		return;

	if ( !isdefined( countdown_divide ) )
		countdown_divide = 1;
	adjusted_count = int( current_count / countdown_divide );

	// No callouts for anything over 5.
	if ( adjusted_count > 5 )
	{
		if ( !isdefined( level.challenge_progress_manual_update ) || !level.challenge_progress_manual_update )
		{
			thread so_dialog_progress_update( current_count, current_goal );
			level.so_counter_dialog_time = gettime() + 800;
		}
		return;
	}
		
	if ( isdefined( level.so_dialog_func_override[ "progress" ] ) )
	{
		thread [[ level.so_dialog_func_override[ "progress" ] ]](adjusted_count);
	}
	else
	{
	// Call 'em out!
	switch( adjusted_count )
	{
		case 5: thread so_dialog_play( "so_tf_1_progress_5more", 0.5 );	break;
		case 4: thread so_dialog_play( "so_tf_1_progress_4more", 0.5 );	break;
		case 3: thread so_dialog_play( "so_tf_1_progress_3more", 0.5 );	break;
		case 2: thread so_dialog_play( "so_tf_1_progress_2more", 0.5 );	break;
		case 1: thread so_dialog_play( "so_tf_1_progress_1more", 0.5 );	break;
	}
	}
	
	level.so_counter_dialog_time = gettime() + 800;
}

// ---------------------------------------------------------------------------------

so_crush_player( player, mod )
{
	assert( isdefined( self ) );
	assert( isdefined( player ) );
	
	if ( !IsDefined( player.coop_death_reason ) )
	{
		player.coop_death_reason = [];
	}

	if ( !IsDefined( mod ) )
	{
		mod = "MOD_EXPLOSIVE";
	}

	player.coop_death_reason[ "attacker" ] = self;
	player.coop_death_reason[ "cause" ] = mod;
	player.coop_death_reason[ "weapon_name" ] = "none";
	
	player kill_wrapper();
}

// Returns the previously completed difficulty. This will not
// take into account the current play through as that difficulty
// completion is sent to player data after end of game call
get_previously_completed_difficulty()
{
	AssertEx( IsDefined( self ) && IsPlayer( self ), "Self must be player to get completed difficulty." );
	
	// run on player
	levelIndex = level.specOpsSettings maps\_endmission::getLevelIndex( level.script );

	difficulty = Int( ( self GetLocalPlayerProfileData( "missionSOHighestDifficulty" ))[ levelIndex ] );
	difficulty = Int( max( 0, difficulty ) );

	return difficulty;
}

// ---------------------------------------------------------------------------------
// Special Ops 3 Star Display System 
//		-for Time Trial Based Maps like delta camp (pit 2.0) and so_timetrial_london
// ---------------------------------------------------------------------------------


/*
=============
///ScriptDocBegin
"Name: so_hud_stars_precache()"
"Summary: Call to precache difficulty star hud items. Add the following to your csv: include,specialops_hud_stars."
"Module: Utility"
"CallOn: "
"Example: so_hud_stars_precache()"
"SPMP: coop"
///ScriptDocEnd
=============
*/

so_hud_stars_precache()
{	
	PreCacheShader( "difficulty_star" );
}

/*
=============
///ScriptDocBegin
"Name: so_hud_stars_init( <time_regular> , <time_hard> , <time_veteran> )"
"Summary: Initialize the star hud system for timetrial based maps. This creates 3 star hud items. so_hud_stars_precache() should be called first. Add the following to your csv: include,specialops_hud_stars"
"Module: Utility"
"CallOn: A player"
"MandatoryArg: <time_regular>: Time in seconds before regular star is deleted"
"MandatoryArg: <time_hard>: Time in seconds before hardened star is deleted"
"MandatoryArg: <time_veteran>: Time in seconds before veteran star is deleted"
"OptionalArg: <line_index>: Optional line index to put the stars on. Defaults to 4."
"Example: level.player so_hud_stars_single_think( 120.0, 90.0, 60.0 );"
"SPMP: coop"
///ScriptDocEnd
=============
*/

so_hud_stars_init( flag_start, flag_end, time_regular, time_hard, time_veteran, line_index )
{
	AssertEx( IsDefined( self ) && IsPlayer( self ), "Self must be a player." );
	AssertEx( IsDefined( time_regular ) && IsDefined( time_hard ) && IsDefined( time_veteran ), "All difficulty times must be defined." );
	
	level.race_times = [];
	level.race_times[ "regular" ]	= time_regular;
	level.race_times[ "hardened" ]	= time_hard;
	level.race_times[ "veteran" ]	= time_veteran;
	
	line_index = ter_op( IsDefined( line_index ), line_index, 4 );
	
	self.stars_removed = [];
	
	self thread so_hud_stars_single_think( flag_start, flag_end, 0, level.race_times[ "regular" ], 	"regular", line_index );
	self thread so_hud_stars_single_think( flag_start, flag_end, 1, level.race_times[ "hardened" ], 	"hardened", line_index );
	self thread so_hud_stars_single_think( flag_start, flag_end, 2, level.race_times[ "veteran" ], 	"veteran", line_index );
}

// Each star hud item is created by a call to this function
so_hud_stars_single_think( flag_start, flag_end, x_pos_offset, time_remove, difficulty, line_index )
{
	AssertEx( IsDefined( flag_start ) && flag_exist( flag_start ), "Challenge start flag doesn't exist: " + flag_start );
	AssertEx( IsDefined( flag_end ) && flag_exist( flag_end  ), "Challenge end flag doesn't exist: " + flag_end );
	AssertEx( IsDefined( x_pos_offset ), "X offset undefined." );
	AssertEx( IsDefined( time_remove ), "Time before star item expires undefined." );
	/#
	so_hud_stars_validate_difficulty( difficulty );
	#/
	
	level endon( "special_op_terminated" );
	level endon( flag_end );
	
	if ( !IsDefined( self.so_hud_star_count ) )
	{
		self.so_hud_star_count = 0;
	}
	self.so_hud_star_count++;
	
	star_width = 25;
	ypos = so_hud_ypos();
	
	star = so_create_hud_item( line_index, ypos, undefined, self );
	star.x -= ( x_pos_offset * star_width ) - 30;
	star.y += 5;
	star SetShader( "difficulty_star", 25, 25 );
	
	flag_wait( flag_start );
	
	self thread so_hud_stars_single_force_alpha_end( star, flag_end );

	// don't remove a star if timelimit is less then 0
	if ( time_remove < 0 )
	{
		return;
	}

	self thread so_hud_stars_sound_and_flash( star, time_remove, flag_end );
	level waittill_any_timeout( time_remove, "star_hud_remove_" + difficulty );

	// In case the player finished this frame
	waittillframeend;
	
	if ( flag( flag_end ) )
	{
		return;
	}
	
	self.so_hud_star_count--;
	
	star Destroy();
}


/*
=============
///ScriptDocBegin
"Name: so_hud_stars_remove( <difficulty> )"
"Summary: Removes a specified difficulty star from both players in case the mission wants this star gone even if the time hasn't expired."
"Module: Utility"
"CallOn: Nothing, handles coop."
"OptionalArg: <difficulty>: The valid difficulty parameters are regular, hardened and veteran. If no difficulty is passed the next star is removed."
"Example: so_hud_stars_remove( "hardened" )"
"SPMP: coop"
///ScriptDocEnd
=============
*/

so_hud_stars_remove( difficulty )
{
	foreach ( player in level.players )
	{
		AssertEx( IsDefined( player.stars_removed ), "Stars removed array should have been initialized in so_hud_stars_init()." );
	
		if ( !IsDefined( difficulty ) )	
		{
			if ( !IsDefined( player.stars_removed[ "veteran" ] ) )
			{
				difficulty = "veteran";
			}
			else if ( !IsDefined( player.stars_removed[ "hardened" ] ) )
			{
				difficulty = "hardened";
			}
			else if ( !IsDefined( player.stars_removed[ "regular" ] ) )
			{
				difficulty = "regular";
			}
		}
		
		// Early out if this star has already been removed.
		if ( IsDefined( player.stars_removed[ difficulty ] ) )
		{
			return;
		}
	
		/#
		so_hud_stars_validate_difficulty( difficulty );
		#/
		
		// Make sure a star is not being removed
		// out of order.
		if	(
				difficulty == "hardened"
			&&	!IsDefined( player.stars_removed[ "veteran" ] )
			)
		{
			Assert( "Star for difficulty " + difficulty + " should not be removed before veteran" );
			return;
		}
		else if
			(
				difficulty == "regular"
			&&	( !IsDefined( player.stars_removed[ "veteran" ] ) || !IsDefined( player.stars_removed[ "hardened" ] ) )
			)
		{
			Assert( "Star for difficulty " + difficulty + " should not be removed before veteran or hardened" );
			return;
		}
		
		// Record star removed
		player.stars_removed[ difficulty ] = 1;
		
		level notify( "star_hud_remove_" + difficulty );
	}
}

so_hud_stars_validate_difficulty( difficulty )
{
	AssertEx( IsDefined( difficulty ), "Difficulty must be defined." );
	
	switch( difficulty )
	{
		case "regular":
		case "hardened":
		case "veteran":
			break;
		default:
			Assert( "Invalid difficulty parameter: " + difficulty + ". Must be regular, hardened or veteran." );
			break;
	}
}

so_hud_stars_sound_and_flash( star, time_remove, flag_end )
{
	star endon( "death" );
	level endon( flag_end );
	level endon( "special_op_terminated" );
	
	seconds_to_tick = 5;
	seconds_before_tick = time_remove - seconds_to_tick;
	Assert( seconds_before_tick > 0 );
	
	wait( seconds_before_tick );
	
	for ( i = 0; i < seconds_to_tick; i++ )
	{
		self PlayLocalSound( "star_tick" );

		star.alpha = 1;
		wait( 0.5 );

		star.alpha = 0.3;
		wait( 0.5 );
	}

	self PlayLocalSound( "star_lost" );
}

so_hud_stars_single_force_alpha_end( star, flag_end )
{
	star endon( "death" );

	flag_wait( flag_end );
	waittillframeend;
	star.alpha = 1;
}


// ======================================================================
// Unlock hint 
// ======================================================================

Unlock_hint()
{
	// wait due to access to playerdata block needs to happen in second frame
	wait 0.05;
	
	foreach( player in level.players )
		player thread Unlock_hint_think();
}

Unlock_hint_think()
{
	//level endon( "special_op_terminated" );
	//self endon( "death" );
	
	// hide unlock display
	self surHUD_disable( "unlock" );
	
	for( index=0; index<3; index++ )
		self unlock_hint_reset( index );
	
	// per player unlock listener
	while ( 1 )
	{
		// wait till level up
		self waittill( "update_rank" );
		
		// wait for playerdata finish setting
		waittillframeend;
		
		// player is no longer defined, so we cant record player data
		if ( !isdefined( self ) )
			return;
		
		// check if player new rank has unlocks		
		player_rank = self maps\_rank::getRank();
		
		assertex( isdefined( level.unlock_array ), "unlockable array setup failed" );
		assertex( level.unlock_array.size > 0, "no unlockables registered, call: maps\_so_survival::unlock_register( ref, lvl, name, icon )" );
		
		unlockable_array = level.unlock_array[ player_rank ];
		
		if ( isdefined( unlockable_array ) )
		{
			// reset
			for( index=0; index<3; index++ )
			{
				unlockable = unlockable_array[ index ];
				if ( isdefined( unlockable ) )
				{
					// record recent unlock
					self register_recent_unlock( unlockable );
			
					self _setplayerdata_array( "surHUD_unlock_hint_" + index, "name", unlockable.name );
					self _setplayerdata_array( "surHUD_unlock_hint_" + index, "icon", unlockable.icon );
					self _setplayerdata_array( "surHUD_unlock_hint_" + index, "mode", unlockable.mode );
				}
				else
				{
					self unlock_hint_reset( index );
				}
			}

			// tell menu script to animate unlock hint UI with provided data
			self surHUD_animate( "unlock" );
		}
	}
}

register_recent_unlock( unlock_struct )
{
	assertex( isdefined( unlock_struct.name ), "Unlocked item is missing name." );
	assertex( isdefined( unlock_struct.ref ), "Unlocked item is missing reference string." );
	
	if ( !unlock_struct.feature )
	{	
		// unlock is an item
		item_type			= tablelookup( "sp/survival_armories.csv", 1, unlock_struct.ref, 2 );
		item_width_ratio 	= int( 1 + ( item_type == "weapon" ) );
		item_icon 			= tablelookup( "sp/survival_armories.csv", 1, unlock_struct.ref, 6 );
		item_desc 			= unlock_struct.desc;
		
		// pass 2 to 3
		self pass_recent_item_unlock( "recent_item_2", "recent_item_3" );
		// pass 1 to 2
		self pass_recent_item_unlock( "recent_item_1", "recent_item_2" );
		// record 1
		self _setplayerdata_array( "recent_item_1", "name", 			unlock_struct.name );
		self _setplayerdata_array( "recent_item_1", "icon", 			item_icon );
		self _setplayerdata_array( "recent_item_1", "desc", 			item_desc );
		self _setplayerdata_array( "recent_item_1", "icon_width_ratio", item_width_ratio );
	}
	else
	{	// unlock is a feature
		// pass 1 to 2
		feature_name = self getplayerdata( "recent_feature_1", "name" );
		self _setplayerdata_array( "recent_feature_2", "name", feature_name );
		// record 1
		self _setplayerdata_array( "recent_feature_1", "name", unlock_struct.name );
	}
}

pass_recent_item_unlock( from, to )
{
	item_name 				= self getplayerdata( from, "name" );
	item_desc 				= self getplayerdata( from, "desc" );
	item_icon 				= self getplayerdata( from, "icon" );
	item_icon_width_ratio 	= self getplayerdata( from, "icon_width_ratio" );
	
	self _setplayerdata_array( to, "name", 				item_name );
	self _setplayerdata_array( to, "desc", 				item_desc );
	self _setplayerdata_array( to, "icon", 				item_icon );
	self _setplayerdata_array( to, "icon_width_ratio", 	item_icon_width_ratio );
}

unlock_hint_reset( index )
{
	self _setplayerdata_array( "surHUD_unlock_hint_" + index, "name", "" );
	self _setplayerdata_array( "surHUD_unlock_hint_" + index, "icon", "" );
	self _setplayerdata_array( "surHUD_unlock_hint_" + index, "mode", "" );
}

// this opens a menu to set milliseconds() in menu script to get menu element to animate
surHUD_animate( ref )
{
	level endon( "special_op_terminated" );
	self endon( "stop_animate_" + ref );
	self thread surHUD_animate_endon_clear( "stop_animate_" + ref );
	
	if ( !isdefined( self.surHUD_busy ) )
		self.surHUD_busy = false;

	while ( self.surHUD_busy )
		wait 0.05;
	
	// only one animate to be done in a frame
	self.surHUD_busy = true;
	
	// if hidden, we show since animate implies visbility
	if ( !surHUD_is_enabled( ref ) )
		self surHUD_enable( ref );
	
	// sets the element to be animated
	self _setplayerdata_single( "surHUD_set_animate", ref );
	wait 0.05;

	// opens menu to set timer to animate for item
	self openmenu( "surHUD_display" );
	
	wait 0.05;
	self.surHUD_busy = false;
	self notify( "surHUD_free" );
}

surHUD_animate_endon_clear( msg )
{
	self endon( "surHUD_free" );
	
	self waittill( msg );
	self.surHUD_busy = false;
}

// sets mini challenge text label per slot
surHUD_challenge_label( slot, value )
{
	if ( isdefined( self ) )
		self _setplayerdata_array( "surHUD_challenge_label", "slot_" + slot, value );
}

// set mini challenge progress per slot
surHUD_challenge_progress( slot, value )
{
	if ( isdefined( self ) )
		self _setplayerdata_array( "surHUD_challenge_progress", "slot_" + slot, value );
}

// set mini challenge reward amount per slot
surHUD_challenge_reward( slot, value )
{
	if ( isdefined( self ) )
		self _setplayerdata_array( "surHUD_challenge_reward", "slot_" + slot, value );
}

// show menu hud element
surHUD_is_enabled( ref )
{
	if ( isdefined( self ) && self getplayerdata( "surHUD", ref ) )
		return true;
		
	return false;
}

// show menu hud element
surHUD_enable( ref )
{
	if ( isdefined( self ) )
		self _setplayerdata_array( "surHUD", ref, 1 );
}

// hide menu hud element
surHUD_disable( ref )
{
	if ( isdefined( self ) )
		self _setplayerdata_array( "surHUD", ref, 0 );
}

_setplayerdata_single( data_name, value )
{
//	name = "player";
//	if ( isdefined( self.unique_id ) )
//		name = self.unique_id;
		
//	println( name + "> setplayerdata("+data_name+","+value+") START: " + gettime() );
	self setplayerdata( data_name, value );
//	println( name + "> setplayerdata("+data_name+","+value+") END: " + gettime() );
}

_setplayerdata_array( data_name, data_index, value )
{
//	name = "player";
//	if ( isdefined( self.unique_id ) )
//		name = self.unique_id;
		
//	println( name + "> setplayerdata("+data_name+","+data_index+","+value+") START: " + gettime() );
	self setplayerdata( data_name, data_index, value );
//	fprintln( name + "> setplayerdata("+data_name+","+data_index+","+value+") END: " + gettime() );
}


// ======================================================================
// SpecOps Achievements 
// ======================================================================

// init achievements tracking per session
so_achievement_init()
{
	wait 0.05;	// due to player data acess
	
	foreach( player in level.players )
		player thread so_achievement_reset();
}

// tracking completed achievements this session to early out
so_achievement_reset()
{
	// self is player
	if ( !isdefined( self.achievement_completed ) )
		self.achievement_completed = [];

	// achievement completion reset this session
	self.achievement_completed[ "ARMS_DEALER" ] 			= 0;
	self.achievement_completed[ "DANGER_ZONE" ] 			= 0;
	self.achievement_completed[ "DEFENSE_SPENDING" ] 		= 0;
	//self.achievement_completed[ "GET_RICH_OR_DIE_TRYING" ]= 0;
	//self.achievement_completed[ "I_LIVE" ] 				= 0;
	self.achievement_completed[ "SURVIVOR" ] 				= 0;
	self.achievement_completed[ "UNSTOPPABLE" ] 			= 0;
	//self.achievement_completed[ "BRAG_RAGS" ] 			= 0;
	//self.achievement_completed[ "TACTICIAN" ] 			= 0;
}

// function called from external to update progress of an achievement
so_achievement_update( achievement_string, extra_arg )
{
	// self is player
	if ( is_survival() )
	{
		// survival
		switch ( achievement_string )
		{
			// counting items
			case "ARMS_DEALER": 		// Buy all items from the Survival Weapon Armory.
			case "DEFENSE_SPENDING": 	// Buy all items from the Survival Equipment Armory.
			case "DANGER_ZONE":			// Buy all items from the Survival Air Support Armory. 
				// extra_arg here is item_ref of an armory item
				self thread so_achievement_item_collection( achievement_string, extra_arg ); 
				return;
			
			// counting waves
			case "SURVIVOR":			// Survive 10 waves in each mission of Special Ops Survival mode.
				self thread so_achievement_wave_count( achievement_string, 9 );
				return;
				
			case "UNSTOPPABLE":			// Survive 15 waves in each mission of Special Ops Survival mode. 
				self thread so_achievement_wave_count( achievement_string, 14 ); 
				return;
				
			// singular
			case "I_LIVE":					// Survive 1 wave in a Special Ops Survival Game.	
			case "GET_RICH_OR_DIE_TRYING": 	//Have $50,000 current balance in a Special Ops Survival game. 
				self thread player_giveachievement_wrapper( achievement_string );
				return;
		}
	}
	else
	{
		// missions
		switch ( achievement_string )
		{
			case "BRAG_RAGS":		// Earn 1 star in Special Ops Mission Mode. 
				self thread player_giveachievement_wrapper( achievement_string );
				return;
				
			case "TACTICIAN":  		// Earn 1 star in each mission of Special Ops Mission Mode.
				self thread so_achievement_star_count( achievement_string, 1 ); 
				return;

			case "OVERACHIEVER":  	// Earn 3 stars in each mission of Special Ops Mission Mode.
				self thread so_achievement_star_count( achievement_string, 3 ); 
				return;
		}
	}
}


// ================ Tracking of Survival Armory Purchases ================
// ***using variables that only exist in survival
// generic function for counting items bought from all 3 armories
so_achievement_item_collection( achievement_string, item_ref )
{
	// self is player
	assertex( is_survival(), "SO ACHIEVEMENT: survival achievement function called in non-survival mode." );

	if ( self.achievement_completed[ achievement_string ] )
		return;
	
	// survival mode means we have access to level.armory array
	assertex( isdefined( level.armory_all_items ), "SO ACHIEVEMENT: survival mode started without armory items array built" );
	assertex( isdefined( level.armory_all_items[ item_ref ] ), "SO ACHIEVEMENT: item does not exist in armory items array" );
	
	item_type = level.armory_all_items[ item_ref ].type;
	
	// record item purchase if not already purchased
	if ( self getplayerdata( item_type + "_purchased", item_ref ) == 0 )
		self setplayerdata( item_type + "_purchased", item_ref, 1 );
	else
		return; // early out as nothing as changed
	
	completed = false;
	
	// special case for weapons as upgrades are also part of weapon armory
	if ( item_type == "weapon" || item_type == "weaponupgrade" )
		completed = self is_purchase_collection_complete( "weapon", "weapon_purchased" ) && self is_purchase_collection_complete( "weaponupgrade", "weaponupgrade_purchased" );
	else
		completed = self is_purchase_collection_complete( item_type, item_type + "_purchased" );
	
	// give achievement YEY!
	if ( completed )
	{
		self player_giveachievement_wrapper( achievement_string );
		self.achievement_completed[ achievement_string ] = 1;	// no more accessing playerdata this session
	}
}

is_purchase_collection_complete( item_type, playerdata_array_string )
{
	// self is player
	assertex( isdefined( item_type ) && isdefineD( level.armory[ item_type ] ), "SO ACHIEVEMENT: Armory type or armory does not exist..." );
	
	foreach( item_struct in level.armory[ item_type ] )
	{
		if ( self getplayerdata( playerdata_array_string, item_struct.ref ) == 0 )
			return false;
	}
	return true;
}

// ================ Tracking of Survival Waves ================

so_achievement_wave_count( achievement_string, count )
{
	// self is player
	assertex( is_survival(), "SO ACHIEVEMENT: survival achievement function called in non-survival mode." );
	assertex( isdefined( level.specOpsSettings ), "Survival level array not setup." );
	
	if ( self.achievement_completed[ achievement_string ] )
		return;

	// tracking only survival levels indexed 0-15 for MW3
	for( i=0; i<16; i++ )
	{
		assertex( isdefined( level.specOpsSettings.levels[i] ), "Survival level index: " + i +" is out of bound." );
		
		bspname = level.specOpsSettings.levels[i].name;
		assertex( isdefined( bspname ), "The map name is not defined inside levels array for spec ops!" );
		
		best_score_var 	= tablelookup( "sp/specOpsTable.csv", 1, bspname, 9 );
		assertex( IsDefined( best_score_var ) && best_score_var != "", "best wave var for this level does not exist!" );
		
		best_wave = int( self GetLocalPlayerProfileData( best_score_var ) / 1000 );
		assertex( isdefined( best_wave ), "Best wave is not defined for this player" );

		// current level's wave number has not yet been recorded into profile data
		if ( bspname == level.script )
			best_wave = level.current_wave;

		// failed to satisify
		if ( best_wave < count )
			return;
	}
	
	// achievement earned as count was reached for all levels
	self player_giveachievement_wrapper( achievement_string );
	self.achievement_completed[ achievement_string ] = 1;	// no more accessing playerdata this session
	
	if ( achievement_string == "UNSTOPPABLE" )
	{
		//self thread maps\_missions::processChallenge( "ch_unstoppable" );
		
		self setPlayerData( "challengeState", "ch_unstoppable", 2 );
	}
}

// ================ Tracking of Mission Stars ================

so_achievement_star_count( achievement_string, count )
{
	// self is player
	assertex( !is_survival(), "SO ACHIEVEMENT: SO Mission achievement function called in survival mode." );
	assertex( isdefined( level.specOpsSettings ), "Survival level array not setup." );
	
	// tracking only mission levels indexed 16-31 for MW3
	for( i=16; i<32; i++ )
	{
		assertex( isdefined( level.specOpsSettings.levels[i] ), "Survival level index: " + i +" is out of bound." );
		
		bspname = level.specOpsSettings.levels[i].name;
		assertex( isdefined( bspname ), "The map name is not defined inside levels array for spec ops!" );

		stars = Int( ( self GetLocalPlayerProfileData( "missionSOHighestDifficulty" ))[ i ] );
		stars = Int( max( 0, stars ) ) - 1;

		if ( stars < count )
			return;
	}
	
	// achievement earned as count was reached for all levels
	self player_giveachievement_wrapper( achievement_string );
	
	if ( achievement_string == "OVERACHIEVER" )
	{
		//self thread maps\_missions::processChallenge( "ch_overachiever" );
		
		self setPlayerData( "challengeState", "ch_overachiever", 2 );
	}
}