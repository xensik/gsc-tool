#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;
#include maps\_specialops;
#include maps\_hud_util;
#include maps\_audio_music;
#include maps\_audio;
#include maps\_shg_common;
#include maps\ss_util;
#include maps\_audio_zone_manager;

main()
{
	maps\so_ied_berlin_precache::main();
	maps\berlin_fx::main();
	maps\so_ied_berlin_fx::main();
	maps\createart\berlin_art::main();
	maps\_shg_common::so_mark_class( "trigger_multiple_audio" );
	so_delete_all_vehicles();
	PrecacheMinimapSentryCodeAssets();
	
	flag_init("reverse_breach_start");
	flag_init ( "ied_vo_line_good" );
	flag_init ( "all_ieds_defused" );
	flag_init ( "flag_conversation_in_progress" );
	flag_init ( "jugg_player_in_view" );
	flag_init ( "jugg_player_out_of_view" );
	flag_init ( "used_thumper" );
	flag_init ( "sniper_left_roof" );
	flag_init ( "dog_attack" );
	
	maps\_load::main();
	maps\berlin_aud::main();
	maps\so_aud::main();
	
	level.uav_missle_start_forward_distance = 100.0;
	level.uav_missle_start_right_distance = 0.0;
	
	
	thread predator_fog_setup();
	level.VISION_UAV = "ny_manhattan_predator";
	level.uav_missile_tag_for_camera = "tag_camera";
	maps\_remotemissile::init();
	//level.remote_missile_use_cluster_bomb = true;
	maps\_predator2::main();
	
	maps\_compass::setupMiniMap("compass_map_berlin"); 
	
	//precache stuff
	precacheitem ( "fraggrenade" );
	precacheitem ( "claymore" );
	precacheshader ( "waypoint_defuse" );
	precacheshader ( "juggernaut_overlay" );
	
	PreCacheString ( &"SO_IED_BERLIN_HINT_THUMPER" );
	PreCacheString ( &"SO_IED_BERLIN_HINT_SNIPER" );
	PreCacheString ( &"SO_IED_BERLIN_HINT_JUGG" );
	PreCacheString ( &"SO_IED_BERLIN_HINT_IEDS_MARKED" );
	PreCacheString ( &"SO_IED_BERLIN_EXPLO_KILL" );
	PreCacheString ( &"SO_IED_BERLIN_MELEE_KILL" );
	
	add_hint_string ( "hint_sniper", &"SO_IED_BERLIN_HINT_SNIPER" );
	add_hint_string ( "hint_jugg", &"SO_IED_BERLIN_HINT_JUGG" );
	add_hint_string ( "hint_ied_marked", &"SO_IED_BERLIN_HINT_IEDS_MARKED" );
	
	PreCacheModel ( "mp_fullbody_ally_juggernaut" );
	PreCacheModel ( "viewhands_juggernaut_ally" );
	PreCacheModel ( "viewhands_player_delta" );
	//precacheitem ( "fn2000_thermal" );
	
	//init flags
	flag_init( "uav_in_use" );
	flag_init( "uav_weapon_picked_up" );
	flag_init( "target_marked" );
	flag_init( "bridge_one_tank_destroyed" );
	flag_init ( "no_default_uav_hint" );
	

	
	setup();
	thread gameplay_logic();
}

setup()
{
	
	so_delete_all_by_type( ::type_spawn_trigger, ::type_flag_trigger, ::type_killspawner_trigger );
	
	crash_locs = getentarray ( "script_origin", "classname" );
	foreach ( loc in crash_locs )
	{
		if ( isdefined ( loc.targetname ) && loc.targetname == "helicopter_crash_location" && !isdefined ( loc.script_specialops ) )
			loc delete();
	}
	
	thread enable_escape_warning();
	thread enable_escape_failure();
	handle_sp_objects();
	
	add_hint_string( "hint_detect", &"SO_IED_BERLIN_HINT_DETECT", ::should_uavplayer_use_uav);
	add_hint_string ( "hint_thumper", &"SO_IED_BERLIN_HINT_THUMPER" );
	
	glass = getglass ( "building_throw_break_glass" );
	deleteglass ( glass );
	
	level.variable_scope_weapons = ["barrett", "fn2000_thermal"];
	thread maps\_shg_common::monitorScopeChange();
	
	aa_building_sniper_rifle = GetEnt( "aa_building_sniper_rifle", "targetname" );
	aa_building_sniper_rifle delete();
	
	thread vision_set_changes("berlin_parkway",0);
	
	//dog stuff
	animscripts\dog\dog_init::initDogAnimations();
	//maps\_load::set_player_viewhand_model( "viewhands_juggernaut_ally" );
	level.player_viewhand_model = "viewhands_player_delta";
	
	//block paths around ammo crates
	col = getentarray ( "so_ammo_col", "targetname" );
	foreach ( i in col )
	{
		BadPlace_Brush ( "ammo", 0, i, "axis" );
		i DisconnectPaths();
	}
	
	AZM_start_zone("berlin_street_bridge_tanks");
	
}
		
gameplay_logic()
{	
	
	thread enable_challenge_timer( "so_ied_berlin_start", "so_ied_berlin_complete" );
	thread fade_challenge_in(1, false);
	thread fade_challenge_out( "so_ied_berlin_complete", true );
	
	//damage reduction for juggernaut player - is multiplied for sniper player in damage_multiply()
	if ( level.gameskill == 1 )
		level.damage_reduction = 0.2;
	else if ( level.gameskill == 2 )
		level.damage_reduction = 0.2;
	else
		level.damage_reduction = 0.2;

	//defined sniper and juggernaut players.  Switched for the time being to get around UI bug (target boxes do not go away for uav player)
	if ( is_coop() )
	{
		// Role select text: 	"Select IED defuser." 
		// dvar coop_start: 	value "so_char_host" from menus sets host as the defuser
		// dvar coop_start: 	value "so_char_client" from menus sets client as defuser
		
		if ( GetDvar( "coop_start" ) == "so_char_host" )
		{
			level.jugg_player = level.players[0];
			level.sniper_player = level.players[1];
		}
		else
		{
			level.jugg_player = level.players[1];
			level.sniper_player = level.players[0];
		}
		
		player2_snipe_point = getent ( "snipe_player2", "targetname" );
		
		level.sniper_player setstance ( "prone" );
    	level.sniper_player playerlinktodelta ( player2_snipe_point, undefined, 1, 45, 45, 20, 70 );
    	wait 1;
    	level.sniper_player unlink();
    	level.sniper_player thread damage_multiply();
    	
		thread sniper_attractors();
		
		//end the game if a player is downed
		flag_clear ( "laststand_on" );
		
		delaythread ( 9, ::intro_hints );
		
		if( is_coop() )
			array_thread(level.players, ::kick_player_from_uav_on_death);
	}
	
	else
		level.jugg_player = level.players[0];	
	
	setsaveddvar("player_damageMultiplier", level.damage_reduction);  
	
	wait 0.1;
	//init variables	
	level.num_ied_groups = 8;
	level.ieds_remaining = level.num_ied_groups;
	level.clusterbomb = 1;
	level.uav_min_time = 30;
	level.ied_display_time = 0;
	level.num_obj_ieds = 3;
	level.ieds_marked = 0;
	level.cur_tank_target = level.jugg_player;

	flag_set ( "no_default_uav_hint" );	// so the default uav hint does not appear and conflict with our mission-specific hint
	
	level.jugg_player makeJuggernaut();
    level.jugg_player.bullet_armor = 500; //how much before we start taking damage.  does not regen
  	level.jugg_player.allowexplodedeath_health = 20; //what our health has to be to allow death by grenade / explosion
  	level.jugg_player.juggernaut_front_armor = .85;
   //level.jugg_player thread Handle_Juggernaut_Health();
   level.jugg_player thread Handle_Juggernaut_Health_Dog_bite();
   	level.jugg_player.grenadeTimers[ "air_support_strobe_ai" ] = 0;
   // level.jugg_player.attackeraccuracy = 0.5;
    
    wait 0.1;
    
	//spawn functions
	add_global_spawn_function( "axis", maps\_remotemissile_utility::setup_remote_missile_target );
	add_global_spawn_function( "axis", ::track_melee_kills );
	add_global_spawn_function( "axis", ::track_explosive_kills );
	array_spawn_function_noteworthy ( "dog", ::dog_think );
	
	array_thread ( level.players, maps\_remotemissile_utility::setup_remote_missile_target );
	
	thread setup_ieds();
	thread setup_uav();
	thread objectives();
	thread music();
	thread setup_vo();
	thread sniper_jump_kill();
	
	//co-op only stuff starts here
	if ( level.players.size > 1 )
	{
		
		
	}
	
	thread detect_hint();
	thread monitor_ieds();
	thread monitor_uav_usage();
	//thread monitor_weapon_switch();
	
	level.so_mission_worst_time = 600000;
	level.so_mission_min_time = 90000;
	maps\_shg_common::so_eog_summary( "@SO_IED_BERLIN_BONUS_EXPLO_KILL", 25, 50, "@SO_IED_BERLIN_BONUS_MELEE_KILL", 25, 50 );
	array_thread ( level.players, ::enable_challenge_counter, 3, &"SO_IED_BERLIN_EXPLO_KILL", "bonus1_count" );
	array_thread ( level.players, ::enable_challenge_counter, 4, &"SO_IED_BERLIN_MELEE_KILL", "bonus2_count" );
	
	flag_wait( "so_ied_berlin_start" );
	
	if ( is_coop() )
		thread littlebird();
	//thread combat();
	thread combat_waves();
	
	
}

handle_sp_objects()
{
	parkway_sign = getentarray("parkway_sign", "targetname");
	parkway_sign_collision = getentarray("parkway_sign_collision", "targetname");
	array_call (parkway_sign, ::delete);
	array_call (parkway_sign_collision, ::delete);
}

objectives()
{
	thread obj_ieds();
}

obj_ieds()
{
	
	level endon ( "all_ieds_defused" );
	
	objective_add( obj( 1 ), "active", &"SO_IED_BERLIN_OBJ_DEFUSE" );
	wait 1;
	objective_string_nomessage( obj( 1 ), &"SO_IED_BERLIN_OBJ_DEFUSE_REMAINING", level.ieds_remaining );
	wait 1;
	objective_current( obj( 1 ) );
	wait 1;
	
	thread update_objective_with_remaining_ieds();
		
	level.ieds_marked = 0;
	
	while ( true )
	{
		flag_wait ( "uav_in_use" );
		
		thread ieds_marked_hint();
		thread radio_dialogue_queue_single ( "so_berlin_hqr_iedsmarked" );
		
		level notify ( "clear_obj" );
		
		wait(0.25);//so we have time for the objecties to clear
		
		assert(level.ieds_marked == 0);
		
		level.closest_ieds_obj = get_array_of_closest ( level.jugg_player.origin, level.ieds_active );
		
		for ( i = 0; i < level.num_obj_ieds; i++ )
		{				
			level.closest_ieds_obj[i] thread make_position( i );
			level.closest_ieds_obj[i] thread ied_remove_obj_dot( i );
			level.ieds_marked++;
			
			wait( 0.25 );
		}
		flag_waitopen ( "uav_in_use" );
	}
		
}

update_objective_with_remaining_ieds()
{
	while(1)
	{
		level waittill ( "ied_defused" );
		wait 0.5;
		objective_string_nomessage( obj( 1 ), &"SO_IED_BERLIN_OBJ_DEFUSE_REMAINING", level.ieds_remaining );
	}
}

make_position(obj_index)
{
	objective_additionalposition ( obj( 1 ), obj_index, self.origin );
	
	self endon ( "stop_target" );
	level waittill ( "clear_obj" ); 
	
	objective_additionalposition ( obj( 1 ), obj_index, (0,0,0) );
	level.ieds_marked--;
}

ied_remove_obj_dot( obj_index )
{
	level endon ( "clear_obj" );
	self waittill ( "stop_target" );
	
	objective_additionalposition ( obj( 1 ), obj_index, (0,0,0) );
	level.ieds_marked--;
}

combat()
{
	flyby_helo = spawn_vehicle_from_targetname_and_drive ( "enemy_chopper_flyby" );
	
	flyby_helo waittill ( "reached_dynamic_path_end" );
	
	flyby_helo delete();
	
}

combat_waves()
{
	level.jugg_player endon ("death");
	
	if ( !is_coop() )
	{
		enemy03_sp_delay = 3;
		enemy04_sp_delay = 5;
		addtowave02 = 0;
		addtowave03 = 0;
		addtowave04 = 0;
	}
	else
	{
		enemy03_sp_delay = 0;
		enemy04_sp_delay = 0;
		addtowave02 = 3;
		addtowave03 = 3;
		addtowave04 = 4;
	}
	array_spawn_function( getspawnerteamarray( "axis" ), ::enemy_ai_think );
	
	//iprintlnbold( "wave spawning" );
	array_spawn_targetname( "enemy_01", true );
	if ( is_coop() )
		array_spawn_targetname ( "enemy_01a", true );
	
	wait 1;
	
	thread combat_wave( "enemy_02", 12 + addtowave02 , 1, 5 );
	//thread dialogue_random_line ( undefined, "so_berlin_hqr_badguys", "so_berlin_hqr_anotherwave" );
	
	//while fewer than 33% have been defused
	wait_till_ieds_defused_percent( 0.33 );
	level notify( "end_current_combat_wave" );
	level.wave3_tank = spawn_vehicle_from_targetname_and_drive ( "tank_enemy_03" );
	level.wave3_tank thread track_explosive_kills();
	aud_send_msg("so_ied_wave3_tank", level.wave3_tank);
	level.wave3_tank thread tank_shoot_at_player();
	level.wave3_tank thread maps\_remotemissile_utility::setup_remote_missile_target();
	foreach ( mg in level.wave3_tank.mgturret )
		mg setconvergencetime ( 3, "yaw" );
	
	array_thread ( level.wave3_tank.riders, ::tank_gunner_monitor_death );
	delaythread ( 6, ::radio_dialogue_queue_single, "so_berlin_hqr_enemyarmor" );
	thread combat_wave( "enemy_03", 12 + addtowave03, 1, 5 + enemy03_sp_delay );
	delaythread ( 2, ::dialogue_random_line, "so_berlin_hqr_badguys", "so_berlin_hqr_anotherwave" );
	
	//while fewer than 66% have been defused
	wait_till_ieds_defused_percent( 0.66 ); 
	level notify( "end_current_combat_wave" );
	wave4_helo_name = "helo_enemy_04";
	wave4_helo_spawner = getent( wave4_helo_name, "targetname" );
	wave4_helo_spawner add_spawn_function( ::helo_enemy_04_ai_think );
	wave4_helo = spawn_vehicle_from_targetname_and_drive ( wave4_helo_name );
	wave4_helo thread track_explosive_kills();
	aud_send_msg("so_ied_wave4_littlebird", wave4_helo);
	delaythread ( 5, ::radio_dialogue_queue_single, "so_berlin_hqr_heloinbound" );
	wave4_helo thread maps\_remotemissile_utility::setup_remote_missile_target();
	foreach ( mg in wave4_helo.mgturret )
		mg setconvergencetime ( 3, "yaw" );
	thread combat_wave( "enemy_04", 12 + addtowave04, 1, 5 + enemy04_sp_delay );
	delaythread ( 1, ::dialogue_random_line, "so_berlin_hqr_badguys", "so_berlin_hqr_anotherwave" );
}

Littlebird()
{

	wait randomintrange ( 40, 80 );

	littlebird = spawn_vehicle_from_targetname_and_drive ( "enemy_littlebird" );
	littlebird thread track_explosive_kills();
	aud_send_msg("so_ied_littlebird", littlebird);
	littlebird thread maps\_remotemissile_utility::setup_remote_missile_target();
	littlebird delaycall ( 6, ::setlookatent, level.sniper_player );
	foreach ( mg in littlebird.mgturret )
		mg setconvergencetime ( 3, "yaw" );
	delaythread ( 5, ::radio_dialogue_queue_single, "so_berlin_hqr_heloinbound" );
	
	//littlebird thread set_speeds_when_dying();
		
}

set_speeds_when_dying()
{
	self waittill ( "deathspin" ); 
	speed = self vehicle_getspeed();
	self vehicle_setspeed(30, 90, 90 );
}
	
sniper_attractors()
{
	level endon ( "all_ieds_defused" );
	
	attractors = getentarray ( "rpg_attractor", "targetname" );
	
	while ( true )
	{
		current = random ( attractors );
		attractor = missile_createattractorent ( current, 9999, 512 );
		
		wait 10;
		missile_deleteattractor(attractor);
		
		wait 0.05;
		
	}
	
}

enemy_ai_think()
{
	self endon( "death" );
	self endon( "long_death" );
	self endon ( "stop_global_spawn_function" );
	level endon( "so_ied_berlin_complete" );
	
	if ( isdefined ( self.classname ) && !issubstr ( self.classname, "dog" ) )
	{
		if ( isdefined ( self.script_noteworthy) && self.script_noteworthy == "rooftop_snipers" )
			self notify ( "stop_global_spawn_function" );
		
		self.goalradius = 1024;
		self.pathrandompercent = 200;
		
		//find the closest few IEDs to the players and fight near them
		while( 1 )
		{
			targetpos = get_closest_ied_cluster_pos();
			
			self setgoalpos( targetpos );
			
			wait 5;
		}
	}
}

wait_till_ieds_defused_percent( percent )
{
	while( level.ieds_defused < ( level.num_ied_groups * percent ) )
	{
		level waittill( "ied_removed" );
	}
}

combat_wave( spawner_targetname, max_enemies, min_enemies, wave_delay )
{
	level endon( "end_current_combat_wave" );
	
	if( !isdefined( max_enemies ) )
	{
		max_enemies = 5;
	}
	
	if( !isdefined( min_enemies ) )
	{
		min_enemies = 1;
	}
	
	enemy_spawners = getentarray( spawner_targetname, "targetname" );
	
	//make sure we don't go out of bounds
	if( max_enemies > enemy_spawners.size )
	{
		max_enemies = enemy_spawners.size;
	}
	
	while( 1 )
	{
		enemies = getaicount( "axis" );
		if( enemies <= min_enemies )
		{
			wait wave_delay;
			//iprintlnbold( "wave spawning" );
			
			enemy_spawners = array_randomize( enemy_spawners );
			
			//array_spawn_targetname( "enemy_02" );
			for( i = 0; i < max_enemies; i++ )
			{
				enemy_spawners[i].count = 1;
				
				flag_waitopen ( "pause_spawn" );
				
				enemy_spawners[i] spawn_ai();
				wait(.25);
			}
		}
		
		wait 0.25;
	}
}

helo_enemy_04_ai_think()
{
	self endon( "death" );
	level endon( "so_ied_berlin_complete" );
	level endon ( "players_down" );
	
	self sethoverparams( 200, 5, 5 );
	
	//get loop nodes
	helo_enemy_04_paths = getstructarray( "helo_loop_node", "script_noteworthy" );
	current_path = helo_enemy_04_paths[0];
	
	//wait until we arrive at the loop start
	flag_wait( "helo_enemy_04_loop_arrive" );
	
	//patrol chopper around the area
	while( 1 )
	{
		//look at closest player
		player = get_closest_player_healthy( self.origin );
		self SetLookAtEnt( player );
		
		//make sure we don't choose the current path
		paths = array_remove( helo_enemy_04_paths, current_path );
		paths = array_randomize( paths );
		current_path = paths[0];
		
		//figure out how fast to move based on distance to travel
		dist = distance ( self.origin, current_path.origin );
		dist_in_miles = inches_to_miles( dist );
		time = seconds_to_hours( 5 );
		velocity = dist_in_miles / time;
		self vehicle_setspeed( velocity, velocity / 2 );
		
		//move to new path node
		self thread vehicle_paths( current_path );
		
		//wait until we arrive
		self waittill ( "vehicle_flag_arrived" );
		
		//wait a little more so player can shoot a stationary target
		wait randomfloatrange( 2, 4 );
	}
}

inches_to_miles( inches )
{
	return inches * 0.000015782;
}

seconds_to_hours( seconds )
{
	return seconds * 0.000277777778;
}

setup_uav()
{
	if( !is_coop_online() )
	{
		cur_vision_set = GetDvar( "vision_set_current" );
		assert( cur_vision_set != "" );
		set_vision_set( cur_vision_set, 0 );	// we need to do this to ensure the level.lvl_visionset is set for the uav code
	}
	//  we may need to do some work on this for specops since it is using the level setting rather than a player setting
	
	level.uav = spawn_vehicle_from_targetname_and_drive( "uav" );
	level.uavRig = spawn( "script_model", level.uav.origin );
	level.uavRig setmodel( "tag_origin" );
	
	level.min_time_between_uav_launches = level.uav_min_time * 1000;
	level.uav_struct.view_cone = 10;
	
	level.uav vehicle_setspeed ( 3, 15, 5 );
	
	thread UAVRigAiming();
	
	thread give_player_predator_drone();
	
	//level.uav hide();
	
	pickup_trigger = getent ( "trigger_uav_control", "targetname" );
	//pickup_trigger usetriggerrequirelookat();
	pickup_trigger thread monitor_uav_pickup();
}
	
give_player_predator_drone()
{
	trigger_wait_targetname ( "trigger_uav_control" );
	
	level.uav show();	
}

UAV_move_lookat()
{
	lookat_2 = getent ( "uav_lookat_2", "targetname" );
	
	level.uav_lookat_point moveto ( lookat_2.origin, 10, 2, 1 );
}
	
		

UAVRigAiming()
{
	level.uav_lookat_point = getent ( "uav_lookat", "targetname" );
	level.lookat = level.uav_lookat_point;
	level.uav endon ( "death" );
	for ( ;; )
	{
		if ( IsDefined( level.uavTargetEnt ) )
			targetPos = level.uavTargetEnt.origin;
		else if ( IsDefined( level.uavTargetPos ) )
			targetPos = level.uavTargetPos;
		else
		{
			/*targetpos = get_closest_ied_cluster_pos();
				
			//set target center to always be in center of the street
			targetpos = ( 192, targetpos[1], targetpos[2] );*/
			
			targetpos = level.uav_lookat_point.origin;
		}
			

		angles = VectorToAngles( targetPos - level.uav.origin );

		level.uavRig MoveTo( level.uav.origin, 0.10, 0, 0 );
		level.uavRig RotateTo( ANGLES, 0.10, 0, 0 );
		wait 0.05;
	}
}

monitor_uav_pickup()
{
	uav_control = getent ( "uav_control", "targetname" );
	
	flag_set( "uav_weapon_picked_up" );
	
	if ( level.players.size == 1 )
	{
		level.so_uav_player = level.jugg_player;
	}
	
	else
	{
		level.so_uav_player = level.sniper_player;	
	}
	uav_control delete();
	self trigger_off();
	
	//wait until level starts before launching is allowed
	//flag_wait( "so_ied_berlin_start" );
	
	level.so_uav_player thread maps\_remotemissile::give_remotemissile_weapon( "remote_missile_detonator" );	
	level.so_uav_player thread predator_keep_safe_view();
	if ( level.so_uav_player == level.jugg_player )
		level.so_uav_player thread predator_hide_jugg_overlay();
	
	if ( level.players.size > 1 )
		level.sniper_player thread disable_if_falling();
	
}

disable_if_falling()
{
	no_weapon_switch = GetEnt( "no_weapon_switch", "targetname" );
	while (1)
	{
		if( no_weapon_switch istouching( self ))
		{
			self SetActionSlot( self.remotemissile_actionslot, "");
		}
		wait 0.05;
	}
}

setup_ieds()
{
	
	thread kick_player_if_dog_attack();
	ieds = [];
	
	for ( i = 0; i < level.num_ied_groups; i++ )
	{
		ied_group = getentarray ( "org_ied_" + i, "targetname" );
	
		ieds [ i ] = random ( ied_group );
		ieds [ i ].trigger = getent ( "ied_trigger_" + i, "targetname" );
		ieds [ i ].trigger enablelinkto();
		ieds [ i ].trigger sethintstring ( &"SO_IED_BERLIN_HINT_IED" );
		ieds [ i ].trigger UseTriggerRequireLookAt ();
		ieds [ i ].trigger.origin = ieds [ i ].origin + ( 0, 0, 8 );
		
		target_set ( ieds[i], (0, 0, 16 ) );
		target_setshader ( ieds[i], "waypoint_defuse" );
		
		foreach ( player in level.players )
		{
			target_hidefromplayer ( ieds[i], player );
		}
		
		ieds[i] thread ied_draw_logic();
		ieds[i] thread ied_defuse_logic();
		//ieds[i] thread ied_detonate_logic();
		ieds[i] thread ied_badplace_and_cleanup_logic();
		
		wait(.1);
	}
	
	level.ieds_active = ieds;
		
}



ied_draw_logic()
{
	self endon ( "stop_target" );
	
	while ( true )
	{
		flag_wait( "uav_in_use" );
		
		target_showtoplayer ( self, level.so_uav_player );
		
		flag_waitopen( "uav_in_use" );
		
		flag_wait_or_timeout( "uav_in_use", level.ied_display_time );
		
		target_hidefromplayer ( self, level.so_uav_player );
	}
	
	wait 0.05;
}

ied_defuse_logic()
{
	self endon ( "blow_up" );
	defused = false;
	self.trigger_off = undefined;
	
	while ( !defused )
	{		
		if ( isdefined ( self.trigger_off ) && ( self.trigger_off ) )
			self.trigger trigger_on();
				
		self.trigger waittill ( "trigger", triggerer );
		
		if ( !flag ( "dog_attack" ) )
		{
			self.trigger trigger_off();
			self.trigger_off = true;
	
			defused = self maps\_shg_common::progress_bar( triggerer, ::defused_success, 3, &"SO_IED_BERLIN_DEFUSING", &"SO_IED_BERLIN_IED_DEFUSED", undefined, &"SO_IED_BERLIN_IED_NOT_DEFUSED", "dog_attack" );
		}
	}
	
	self Delete();	
}

defused_success()
{
	level notify ( "ied_defused" );	
	self notify ( "stop_target" );
}

monitor_ieds()
{	
	level.jugg_player endon ("death");
	
	level.ieds_defused = 0;
	
	level.ieds_title = so_create_hud_item( -3, so_hud_ypos(), &"SO_IED_BERLIN_IEDS_REMAINING" );
	level.ieds_count = so_create_hud_item( -3, so_hud_ypos(), undefined );
	level.ieds_count.alignx = "left";
	level.ieds_count SetValue( level.num_ied_groups );
	level.vehicles_max = level.laptops_left;
	while ( true )
	{
		level waittill ( "ied_defused" );
		level.ieds_defused ++;
		
		level.ieds_title thread so_hud_pulse_success();
		level.ieds_count thread so_hud_pulse_success();
		
		level.ieds_remaining = level.num_ied_groups - level.ieds_defused;
		
		if ( level.ieds_remaining < 3 )
			level.num_obj_ieds --;
		
		level.ieds_count SetValue( level.ieds_remaining );
		//thread so_dialog_counter_update( level.ieds_remaining, level.num_ied_groups );
		objective_String_NoMessage( obj( 1 ), &"SO_IED_BERLIN_OBJ_DEFUSE", level.ieds_remaining );
		
		if ( level.ieds_defused >= level.num_ied_groups )
		{
			// wait a bit in case a player dies from an ied, then check that at least one player is alive
			wait 0.1;
			if( (isdefined( level.jugg_player ) && isalive( level.jugg_player )) || (isdefined( level.sniper_player ) && isalive( level.sniper_player )) )
			{
					flag_set ( "all_ieds_defused" );
					foreach ( player in level.players )
						player EnableInvulnerability();
					triggers = getentarray ( "escape_triggers", "targetname" );
					foreach ( trigger in triggers )
						trigger trigger_off();
					objective_complete ( obj( 1 ) );
					
			}
		}
	}
}

//returns the average location of IEDs closest to the players
get_closest_ied_cluster_pos()
{
	//the following is a catch for the rare (but still possible) chance that the player will start moving before the level.ieds_active array is created
	while( !isdefined( level.ieds_active ))
		wait 0.5;

	if( level.ieds_active.size > 0 )
	{
		averageOrigin = getAveragePlayerOrigin();
		closest_ieds = get_array_of_closest( averageOrigin, level.ieds_active, undefined, 3 );
		targetpos = get_average_origin( closest_ieds );
	}
	else
	{
		targetpos = (0, 0, 0);
	}
	
	return targetpos;
}

kick_player_if_dog_attack()
{
	level endon ( "so_ied_berlin_complete" );
	level endon ( "missionfailed" );
	
	while (1)
	{
		level.jugg_player waittill ( "damage", amount, attacker, direction_vec, point, type );
		
		if(isdefined(attacker) && isdefined(attacker.type) && attacker.type == "dog")
		{
			flag_set ( "dog_attack" );
			wait 1;
			flag_clear ("dog_attack");
		}
	}
}

get_player_speed()
{
	vel = self GetVelocity();
	// figure out the length of the vector to get the speed (distance from world center = length)
	speed = Distance( ( vel[ 0 ], vel[ 1 ], 0 ), ( 0, 0, 0 ) );  // don't care about Z velocity
	
	return speed;
}

check_deflection()
{
	deflection = self getnormalizedmovement();
	deflection_x = deflection[0];
	deflection_y = deflection[1];
	
	if ( ( deflection_x >= 0.8 || deflection_x <= -0.8 ) || ( deflection_y >= 0.8 || deflection_y <= -0.8 ) )
		return true;
	else
		return false;
		
}

ied_detonate_logic ()
{
	self endon ( "blow_up" );
	self endon ( "stop_target" );
	
	deflection_time = 0;
	
	running_time = 0;
	
	while ( true )
	{
		foreach ( player in level.players )
		{
			if ( ( distance ( player.origin, self.origin ) <= 64 ) && ( player getstance() != "prone" ) )
			{
				player_speed = player get_player_speed();
				
				while( player_speed > 100 )
				{
					running_time++;
					player playsound ( "cobra_missile_locked" );
					
					if( running_time >= 15 || player_speed > 200 )
					{
						self ied_detonate();
						self notify ( "blow_up" );
					}
					
					player_speed = player get_player_speed();					
					wait 0.05;
				}
				
				running_time = 0;
			}
		}
		
		wait 0.05;
	}
}	

ied_detonate()
{
	so_force_deadquote( "@SO_IED_BERLIN_IED_DETONATED" );
	
	self Playsound ( "arcademode_2x" );
	
	wait 0.16;
	
	self playsound( "detpack_explo_main", "sound_done" );
	self makeunusable();
	self radiusdamage( self.origin, 256, 100000, 99999 );
	earthquake( 0.4, 1, self.origin, 1000 );
	playfx( level._effect[ "c4_explosion" ], self.origin );
	target_remove ( self );
	
	//don't notify until after the explosion
	level notify ( "ied_defused" );
	self notify ( "stop_target" );
	
	self delete(); 
	
}

ied_badplace_and_cleanup_logic()
{
	badplace_name = self.targetname;
	badplace_cylinder( badplace_name, -1, self.origin, 64, 64, "axis" );
	
	self waittill( "stop_target" );
	
	//remove ied from active list
	level.ieds_active = array_remove( level.ieds_active, self );
	
	badplace_delete( badplace_name );
	
	level notify( "ied_removed" );
}

music()
{
	MUS_play("so_bln_player_unloaded_from_intro_flight");
}

detect_hint()
{
	flag_wait( "so_ied_berlin_start" );
	
	while ( 1 )
	{
		if( !flag( "uav_in_use" ) )
		{
			if ( level.ieds_marked == 0 )
				level.so_uav_player display_hint( "hint_detect" );
		}
		
		//when it is used, hint will be removed
		flag_wait( "uav_in_use" );
		
		//wait until player stops using it to start timer
		flag_waitopen( "uav_in_use" );

		//if uav isn't used within the next 45 seconds, show the hint.  
		flag_wait_or_timeout( "uav_in_use", level.uav_min_time + 15 );
	}
}

should_uavplayer_use_uav()
{
	return flag( "uav_in_use");
}

monitor_uav_usage()
{
	while( 1 )
	{
		level waittill ( "player_is_controlling_UAV" );
		{
			flag_set( "uav_in_use" );
			level.uav playloopsound("amb_blin_uav"); // using same sound as used in nymn uav moment
		}
	
		level waittill ( "draw_target_end" );
		flag_clear( "uav_in_use" );
		level.uav stoploopsound();
	}
}

tank_shoot_at_player()
{
	self endon("death");
	self endon("stop_tank_fire_at_player");
	if ( level.players.size > 1 )
		self thread tank_monitor_jugg_sight(); //target switching, only in coop
	

	
	while(isdefined(self) && isalive(self))
	{
		if (!isdefined(level.cur_tank_target) && isdefined(level.jugg_player) && level.jugg_player.health > 0)
			level.cur_tank_target = level.jugg_player;

		if(isdefined(level.cur_tank_target)&& level.cur_tank_target.health > 0)
		{
			self setturrettargetent( level.cur_tank_target , (randomintrange(-64, 64),randomintrange(-64, 64),randomintrange(-16, 100)));
			if(SightTracePassed(self.origin + (0,0,100), level.cur_tank_target.origin + (0,0,40), false, self ))
			{
				self fireweapon();
				wait(randomintrange(6,10));
			}
			else
			{
				wait 1;
			}	
		}
		else
		{
			wait 1;
		}
	}
}

tank_monitor_jugg_sight()
{
	self endon ( "death" );
	
	while ( true )
	{
		if ( isdefined ( level.cur_tank_target ) )
		{
			if(!SightTracePassed(self.origin + (0,0,100), level.cur_tank_target.origin + (0,0,40), false, self ))
			{
				flag_set ( "jugg_player_out_of_view" );
				
				thread tank_monitor_jugg_sight_clear();
				
				flag_wait_or_timeout ( "jugg_player_in_view", 5 );
				
				wait 0.1;
				
				if ( !flag ( "jugg_player_in_view" ) )
				{
					level.cur_tank_target = level.sniper_player;
				}
				
				else
				{
					level.cur_tank_target = level.jugg_player;
					flag_clear ( "jugg_player_in_view" );
				}
				
			}
			
		}
		
		wait 0.1;
		
	}
	
}

tank_monitor_jugg_sight_clear()
{
	level endon ( "stop_monitor_jugg_sight_clear" );
	
	while ( true )
	{
		if ( isdefined ( level.cur_tank_target ) )
		{
			if(SightTracePassed(self.origin + (0,0,100), level.cur_tank_target.origin + (0,0,40), false, self ))
			{
				flag_set ( "jugg_player_in_view" );
				level notify ( "stop_monitor_jugg_sight_clear" );
			}
			
		}
		
		wait 0.1;
		
	}
	
}

tank_gunner_monitor_death()
{
	self waittill ( "death", attacker, cause, weaponname );
	
	
	if (isdefined (weaponname) && IsSubStr ( weaponname, "remote" ) )
		level.wave3_tank dodamage ( level.wave3_tank.health + 1000, ( 0, 0, 0 ) );
		
	
}

makeJuggernaut()
{
	assert(isplayer(self));
	
	//health regen
	//self.gs.playerHealth_RegularRegenDelay = ( 50 );
	//self.gs.longregentime = ( 50 );
	self blend_MoveSpeedscale_Percent( 70 );
	self setviewkickscale ( .5 );
	
	self.radius_multi = 0.2;
	self.melee_multi = 0.2;
	
	setsaveddvar( "player_radiusDamageMultiplier", self.radius_multi);
	setsaveddvar( "player_meleeDamageMultiplier", self.melee_multi);

	//movement restrictions
	self AllowJump( false );
	//self AllowSprint( false );
	self AllowProne ( false );
	self thread force_no_prone();
	//self AllowCrouch ( false );

	//visuals
	SetHUDLighting( true );
	self.juggernautOverlay = newClientHudElem( self );
	self.juggernautOverlay.x = 0;
	self.juggernautOverlay.y = 0;
	self.juggernautOverlay.alignX = "left";
	self.juggernautOverlay.alignY = "top";
	self.juggernautOverlay.horzAlign = "fullscreen";
	self.juggernautOverlay.vertAlign = "fullscreen";
	self.juggernautOverlay setshader ( "juggernaut_overlay", 640, 480 );
	self.juggernautOverlay.sort = -10;
	self.juggernautOverlay.archived = true;
	self.juggernautOverlay.hidein3rdperson = true;
	
	//juggernaut_overlay = maps\_hud_util::create_client_overlay( "juggernaut_overlay", 1, self );
	self setViewmodel( "viewhands_juggernaut_ally" );
	self setmodelfunc( ::make_jug_model );
}

predator_hide_jugg_overlay()
{
	level endon ( "so_ied_berlin_complete" );
	
	while ( true )
	{
		flag_wait ( "uav_in_use" );
		self.juggernautOverlay.alpha = 0;
		
		flag_waitopen ( "uav_in_use" );
		
		self.juggernautOverlay fadeovertime ( 1 );
		self.juggernautOverlay.alpha = 1;
	
		wait 0.05;		
	}
	
}

force_no_prone()
{
	while(1)
	{
		self AllowProne ( false );
		wait 0.05;
	}
}

make_jug_model()
{
	self setModel("mp_fullbody_ally_juggernaut");
}

playerBreathingSound( maxhealth, hurthealth )
{
	level.healthOverlayCutoff = .55;
	assert(isdefined(level.healthOverlayCutoff));

	wait( 2 );

	for ( ;; )
	{
		wait( 0.2 );
		if ( self.health <= 0 )
			return;

		// Player still has a lot of health so no breathing sound
		ratio = self.health / self.maxHealth;
		if ( ratio > level.healthOverlayCutoff )
			continue;

		level.player play_sound_on_entity( "breathing_hurt" );
		wait( 0.1 + randomfloat( 0.8 ) );
	}
}

Handle_Juggernaut_Health_Dog_bite()
{
	while(1)
	{
		self waittill( "damage", amount, attacker, direction_vec, point, type, modelName, tagName );
		
		if (isdefined(attacker) 
				&& isdefined(attacker.type) 
				&& attacker.type == "dog"
				&& isdefined(attacker.meleeingPlayer) 
				&& isdefined(attacker.meleeingPlayer.player_view)
				)
		{
			attacker.meleeingPlayer.player_view thread await_animation_complete( self, attacker);
		}
	}
}

await_animation_complete( player, attacker )
{
	player endon ("death");
	attacker endon ("death");
	attacker endon( "pvd_melee_interrupted" );

	player thread give_back_weapons( attacker);
	
	attacker.meleeingPlayer.player_view waittill( "pvd_melee_done" );
	
	player kill();
}

give_back_weapons(attacker)
{
	self endon ("death");

	attacker waittill( "pvd_melee_interrupted" );
	
	wait 2.5; //this wait is the same as in the dog code. it waits for the player to go from this prone position to stand
	
	self showViewModel();
	self enableweapons();

}

Handle_Juggernaut_Health()
{
	self endon("death");
	self.currenthealth = self.health;
	self thread jugg_explosion_deathshield();
	self.gs.playerHealth_RegularRegenDelay = 500;
	self.gs.longregentime = 500;
	
	while ( 1 )
	{
		self waittill( "damage", amount, attacker, direction_vec, point, type, modelName, tagName );
		
		
		mod_amount = 0;
		if ( self jugg_hit_bullet_armor( type ) )
		{
			self.health = self.currenthealth;
			self.bullet_armor -= amount;
			mod_amount = amount;
		}
		// regen health for tanks with armor in the front
		else if ( self jugg_has_frontarmor() ) 
		{
			mod_amount = self.health;
			self jugg_mod_front_armor( attacker, amount );
			self.currenthealth = self.health;
			
			mod_amount -= self.health; //to see how it was effected
		}
		
		if(self == level.player)
		{
			iprintln ( "health:" + self.health + " armor:" + self.bullet_armor + " dmg change: " + mod_amount);
		}		
		
		amount = undefined;
		attacker = undefined;
		direction_vec = undefined;
		point = undefined;
		modelName = undefined;
		tagName = undefined;
		type = undefined;
	}
}

edit_damage_multipliers(num1, num2, num3)
{
	setsaveddvar( "player_radiusDamageMultiplier", num1);
	setsaveddvar( "player_meleeDamageMultiplier", num2);
	setsaveddvar( "player_DamageMultiplier", num3);
}

jugg_explosion_deathshield()
{
	self EnableDeathShield( true );
	
	while ( 1 )
	{
		self waittill( "deathshield", damage, attacker, direction, point, type, modelName, tagName, partName, dflags, weaponName );
		
		shouldReallyDie = true;
		if ( IsSubStr( type, "GRENADE" ) || IsSubStr( type, "EXPLOSIVE" ))
		{
			//if we would die from an explosion / grenade 
			assert(isdefined(self.allowexplodedeath_health));
			if(self.currenthealth > self.allowexplodedeath_health)
			{	
				shouldReallyDie = false;			
				self.health = self.allowexplodedeath_health - 1; 
			}
		}
		
		if(shouldReallyDie)
		{
			self EnableDeathShield( false );
			self kill();			
		}
		
	}
}

//self.juggernaut_front_armor (0-1) what percentage of damage to take if we are hit from the front
//so if level.juggernaut_front_armor = .75 and we are hit from the front for 10 points of damage 
//it will be reduced to 10 * .75 = 7.5
jugg_has_frontarmor()
{
	return( IsDefined( self.juggernaut_front_armor ) );
}

jugg_mod_front_armor( attacker, amount )
{
	forwardvec = AnglesToForward( self.angles );
	othervec = VectorNormalize( attacker.origin - self.origin );
//	if ( VectorDot( forwardvec, othervec ) > 0.86 )
		self.health += Int( amount * self.juggernaut_front_armor );
}

jugg_hit_bullet_armor( type )
{
	if ( self.bullet_armor <= 0 )
		return false;
	if ( !( IsDefined( type ) ) )
		return false;
	if ( ! IsSubStr( type, "BULLET" ) )
		return false;
	else
		return true;
}

aud_monitor_player_impacts()
{
	level endon("aud_stop_player_impacts");
	
	while(true)
	{
		level.player waittill( "damage", amount, attacker, direction, point, damage_type );
		level.player playsound("armor_impact");
		// play armor impact sound that is *not* on impact_plr volmod
	}
}

damage_multiply()
{
	self endon ( "death" );
    
    damage_scale = ( 1 - level.damage_reduction ) /  level.damage_reduction;  
    
    while ( true )
    {
        self waittill ( "damage", amount, attacker, direction_vec, point, type );
        if ( isdefined ( attacker ) && issubstr ( attacker.model, "minigun" ) )
        	damage_scale = damage_scale / 2;
        self dodamage ( damage_scale * amount, direction_vec, attacker );
    }
}

sniper_jump_kill()
{
	level endon( "all_ieds_defused" );
	level endon ( "special_op_terminated" );
	flag_wait ( "sniper_off_roof" );
	if ( is_coop() )
		level.sniper_player kill();

}

kick_player_from_uav_on_death()
{
	wait 1;							//wait for player to equip weapon
	weapon = level.sniper_player getcurrentprimaryweapon();
	while (1)
	{
		if (level.jugg_player.health <= 0 )
			flag_clear( "uav_enabled" );
		wait 0.05;
	}
}

intro_hints()
{
	thread intro_hint( level.sniper_player, &"SO_IED_BERLIN_HINT_SNIPER" );
	thread intro_hint( level.jugg_player, &"SO_IED_BERLIN_HINT_JUGG" );
}

intro_hint( player, string )
{
	text = newClientHudElem( player );
	
	text.alignX = "center";
	text.alignY = "middle";
	text.horzAlign = "center";
	text.vertAlign = "middle";
	text.font = "hudsmall";
	text.foreground = 1;
	text.hidewheninmenu = true;
	text.hidewhendead = true;
	text.sort = 2;
	text.label = string;
	
	text set_hud_green();
	text thread hud_blink();
	
	flag_wait_or_timeout ( "uav_in_use", 6 );
	
	text notify ( "stop_blink" );
	wait 0.05;
	text destroy();	
}

ieds_marked_hint()
{
	text = newClientHudElem( level.so_uav_player );
	
	text.alignX = "center";
	text.alignY = "bottom";
	text.horzAlign = "center";
	text.vertAlign = "bottom";
	text.font = "hudsmall";
	text.foreground = 1;
	text.hidewheninmenu = true;
	text.hidewhendead = true;
	text.sort = 2;
	text.label = &"SO_IED_BERLIN_HINT_IEDS_MARKED";
	
	text set_hud_red();
	text thread hud_blink();
	
	flag_waitopen_or_timeout ( "uav_in_use", 6 );
	
	text notify ( "stop_blink" );
	wait 0.05;
	text destroy();	
	
}

predator_keep_safe_view()
{
	self endon("death");
	start_forward = (0.0, 0.0, -1.0);	// hard coding so we can limit the dp as much as possible
	
	min_dp = Cos(55);
	
	while( !flag ( "so_ied_berlin_complete" ) )
	{
		self waittill("player_fired_remote_missile");
		while (isdefined(self.active_uav_missile))
		{	// monitor to ensure our missile is in a valid area
			forward = AnglesToForward(self.active_uav_missile.angles);
			dp = VectorDot(forward,start_forward);
			if (dp < min_dp)
			{	// cause 1 point of damage to take player out of remotemissile view.
				self notify("force_out_of_uav");	// ensure we exit even if in god mode
				pos = self.active_uav_missile.origin;	// for lack of a better pos
				self DoDamage(1,pos);
				break;
			}
			wait 0.05;
		}
	}
}

track_explosive_kills()
{
	level endon ( "so_ied_berlin_complete" );
	level endon ( "missionfailed" );
	
	self waittill ( "death", attacker, cause, weapon );
	if ( isdefined ( attacker ) && isplayer ( attacker ) && isdefined ( cause ) )
		if ( cause == "MOD_EXPLOSIVE" || cause == "MOD_EXPLOSIVE_SPLASH" || cause == "MOD_GRENADE_SPLASH" || cause == "MOD_PROJECTILE_SPLASH" || cause == "MOD_GRENADE" || cause == "MOD_PROJECTILE" )
		{
			attacker.bonus_1++;
			attacker notify ( "bonus1_count", attacker.bonus_1 );
		}
	
}

track_melee_kills()
{
	level endon ( "so_ied_berlin_complete" );
	level endon ( "missionfailed" );
	
	self waittill ( "death", attacker, cause, weapon );
	if ( isdefined ( attacker ) && isplayer ( attacker ) && isdefined ( cause ) && cause == "MOD_MELEE" )
	{
		attacker.bonus_2++;
		attacker notify ( "bonus2_count", attacker.bonus_2 );
	}
	
}

//track_explosive_kills()
//{
//	level endon ( "so_ied_berlin_complete" );
//	while ( true )
//	{
//		self.bonus_1 = self.stats [ "kills_explosives" ];
//		wait 0.05;
//	}
//	
//}

//track_melee_kills()
//{
//	level endon ( "so_ied_berlin_complete" );
//	while ( true )
//	{
//		self.bonus_2 = self.stats [ "kills_melee" ];
//		wait 0.05;
//	}
//	
//}

//===========================================
// 			spawn_so_warlord_dog
//===========================================
dog_think()
{
	
	self SetGoalEntity( level.jugg_player );
	self set_favoriteenemy( level.jugg_player );
	
	exit_point = GetEnt( "dog_backup", "targetname" );
	self thread dog_monitor_goal_ent( level.jugg_player, exit_point );
}		

setup_vo()
{
	//overlord
	add_radio([
		"so_berlin_hqr_iedsscattered",		//IEDs are scattered across the parkwy Metal 0-1.  Jump into your bomb disposal suit and clear them out so our armor can roll through safely.  
		"so_berlin_hqr_ieddefused",				//IED defused.
		"so_berlin_hqr_iedneutralized",		//IED neutralized.
		"so_berlin_hqr_neutralized",			//Neutralized.
		"so_berlin_hqr_threatneutralized",			//Threat neutralized.
		"so_berlin_hqr_fivemore",		//5 more. 
		"so_berlin_hqr_threemore",		//3 more to go metal 0-4
		"so_berlin_hqr_twoleft",	//2 left.
		"so_berlin_hqr_onetogo",		//One to go.
		"so_berlin_hqr_enemyarmor",	//Enemy armor headed into your area Metal 0-4, watch your six.
		"so_berlin_hqr_rotorwing",		//Enemy rotor wing spotted, get eyes on that bird Metal 0-4.
		"so_berlin_hqr_badguys",			//More bad guys headed your way Metal 0-4.  Move on those IED locations.
		"so_berlin_hqr_onstation",			//Metal Zero Four, a Predator is on station, ready to send intel on IED locations.
		"so_berlin_hqr_onpredator",			//Metal Zero Four, get on the Predator to spot those IEDs.
		"so_berlin_hqr_heloinbound",			//Enemy helo inbound, take down that chopper.
		"so_berlin_hqr_anotherwave",			//Another wave of enemy troops headed to your sector Metal 0-4. 
		"so_berlin_hqr_comeonhome",			//All IEDs neutralized.  Nice work Metal 0-4.  Come on home.  Overlord, out.
		"so_berlin_hqr_iedsmarked"			//IEDs marked.
	]);
	thread vo();
	thread vo_defuse();
	delaythread ( 20, ::vo_reaper_hint );
}

vo()
{
	level.jugg_player endon ("death");
	
	wait 1;
	
	thread radio_dialogue_queue_single ( "so_berlin_hqr_iedsscattered" );
	
	flag_wait ( "all_ieds_defused" );
	
	radio_dialogue_queue_single ( "so_berlin_hqr_comeonhome" );
	flag_set ( "so_ied_berlin_complete" );
	
}

vo_defuse()
{
	level endon ( "so_ied_berlin_complete" );
	level.jugg_player endon ("death");
	
	lines = [];
	lines [ lines.size ] = "so_berlin_hqr_ieddefused";
	lines [ lines.size ] = "so_berlin_hqr_iedneutralized";
	lines [ lines.size ] = "so_berlin_hqr_neutralized";
	lines [ lines.size ] = "so_berlin_hqr_threatneutralized";
	last_line = undefined;
	
	while ( true )
	{
		level waittill ( "ied_defused" );
		while ( !flag ( "ied_vo_line_good" ) )
		{
			line = random ( lines );
			
			if ( isdefined ( last_line) && last_line == line )
				continue;
			else
			{
				radio_dialogue_queue_single ( line );
				last_line = line;
				if ( level.ieds_remaining == 5 )
					radio_dialogue_queue_single ( "so_berlin_hqr_fivemore" );
				if ( level.ieds_remaining == 3 )
					radio_dialogue_queue_single ( "so_berlin_hqr_threemore" );
				if ( level.ieds_remaining == 2 )
					radio_dialogue_queue_single ( "so_berlin_hqr_twoleft" );
				if ( level.ieds_remaining == 1 )
					radio_dialogue_queue_single ( "so_berlin_hqr_onetogo" );
										
				flag_set ( "ied_vo_line_good" );
			}
			
			wait 0.05;
		}
		
		flag_clear ( "ied_vo_line_good" );
		
	}
}

vo_reaper_hint()
{
	level endon ( "all_ieds_defused" );
	level.jugg_player endon ("death");
	lines = [];
	lines [ lines.size ] = "so_berlin_hqr_onpredator";
	lines [ lines.size ] = "so_berlin_hqr_onstation";
	vo_line_good = false;
	
	while ( true )
	{
		if ( level.ieds_marked == 0 )
		{	
			while ( !vo_line_good )
			{
				line = random ( lines );
				
				if ( isdefined ( level.dialogue_random_last_line ) && level.dialogue_random_last_line == line )
					continue;
				else
				{
					radio_dialogue ( line );
					level.dialogue_random_last_line = line;
					vo_line_good = true;
				}
				
				wait 0.05;
			}
	
			vo_line_good = false;
			
			wait 10;
		}
		
		wait 0.5;
	}
			
}
	

add_radio(lines)
{
	foreach(line in lines)
	{
		level.scr_radio[line] = line;	
	}	
}


predator_fog_setup()
{
	ent = maps\_utility::create_vision_set_fog( "ny_manhattan_predator" );
	ent.startDist = 8000.17;
	ent.halfwayDist = 19391;
	ent.red = 1;
	ent.green = 1;
	ent.blue = 1;
	ent.maxOpacity = 0.1;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 0;
}
