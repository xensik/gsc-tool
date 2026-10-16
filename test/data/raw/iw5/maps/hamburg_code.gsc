#include maps\_utility;
#include maps\_utility_code;
#include common_scripts\utility;
#include maps\_vehicle;
#include maps\hamburg_tank_ai;


WATER_TAG_COUNT = 12;
#using_animtree( "generic_human" );
fast_drones()
{
	if ( IsAI( self ) )
		return;
	self.runanim= random( [ %sprint_loop_distant_relative, %run_lowready_f_relative ] );
	self.movePlaybackRate = randomfloatrange( 0.95, 1.05 );
}

level_precache()
{
	//some extra cleanup, adding these level vars to modify global behevior
	level.destructible_cleans_up_more = true;
	level.spawn_pool_enabled = true;
	level.unstoppable_friendly_fire_shield = true;
	level.vehicles_ignore_mg_toggle = true;
	level.enable_struct_exploders = true;
	level.drone_death_handler = ::drone_death_handler;
	level.DisablemovementTracker = true;
	level.extra_vehicle_cleanup = true;
	level.disableStrangeOndeath = true;
	level.neverStopMonitoringFlash = true;
	level.bogMortarsGoOnce = true;
	level.spawn_pool_copy_function = ::spawn_pool_copy_function;
	level.maingun_FX_override = ::maingun_FX_hamburg;
	level.animate_drive_idle_on_dummies = true;
	
	
	// some of these are common
	maps\hamburg_fx::main();
	PreCacheItem( "mp5_drone" );
	PreCacheItem( "t90_turret_bold" );
	PreCacheModel( "generic_prop_raven" );
	level.cheap_vehicles_have_shields = true;
	
	create_lock( "sentry_drones" );

	vehicle_scripts\_m1a1_player_control::precache_tank();
	
	GetEnt( "garage_crash_light_flicker", "targetname" ) SetLightIntensity( 0 );
	
}

burn_name_tank_crew_spawners( spawner )
{
	spawner = self.spawner;
	spawner.script_friendname = self.name;
}

init_level()
{		
	if ( !IsDefined( level.FRIEND_MAX ) )
		level.FRIEND_MAX = 9;
//	thread show_me_the_drones();

	thread createfx_manager();

	tank_crew_1 = GetEnt( "tank_crew_1", "targetname" );
	tank_crew_2 = GetEnt( "tank_crew_2", "targetname" );
	tank_crew_1 add_spawn_function( ::burn_name_tank_crew_spawners );
	tank_crew_2 add_spawn_function( ::burn_name_tank_crew_spawners );
		
	add_global_spawn_function( "axis", ::fast_drones );	
	maps\hamburg_tank_ai::init_tank_ai_globals();

	add_global_spawn_function( "allies", ::brave_soul);
	
	maps\_drone_ai::init();
	
	level.custombadplacethread = ::hamburg_badplace;
 	
	PreCacheModel( "vehicle_m1a1_abrams_minigun_shiny_objective" );
	PreCacheModel( "vehicle_m1a1_abrams_minigun_shiny_part" );
	PreCacheString( &"PLATFORM_HOLD_TO_USE" );
	
	maps\_vehicle::build_deathfx_override( "script_vehicle_m1a1_abrams_minigun", undefined, "vehicle_m1a1_abrams_minigun", "explosions/vehicle_explosion_t90_cheap", "tag_deathfx", "exp_armor_vehicle" );
	
	if( !is_after_start( "hamburg_garage_ramp" ) )
	{
		level.player_tank = spawn_vehicle_from_targetname( "player_tank" );
		level.player_tank.shock_distance = 200;
		level.player_tank.black_distance = 500;
		level.player_tank.dummyspeed = 6;
		level.player_tank SetModel( "vehicle_m1a1_abrams_minigun" );
		level.player_tank vehicleusealtblendedaudio( true );
		level.player_tank godon();
		level.player_tank init_tank_ai();
		get_player_spot( level.player_tank );
		level.playervehicle = level.player_tank;
		level.player_tank.rumbleon = false;
		level.player_tank.dontunloadonend = true;
		level.player_tank.damageIsFromPlayer = true;
		level.player_tank thread shoot_explode();

		level.hero_tank = spawn_vehicle_from_targetname( "hero_tank" );
		
		level.hero_tank.shock_distance = 200;
		level.hero_tank.black_distance = 500;

		level.hero_tank.rumbleon = false;
		level.hero_tank godon();	
		level.hero_tank ent_flag_init( "sync_tanks" );
		level.hero_tank ent_flag_init( "stunned_tank" );
		level.hero_tank.dontunloadonend = true;
		level.hero_tank.damageIsFromPlayer = true;
		level.hero_tank thread shoot_explode();	
		level.hero_tank init_tank_ai();
	}
	
	 /#
	 	SetDvarIfUninitialized( "debug_vehicleturretaccuracy", "0" );
	 	SetDvarIfUninitialized( "debug_vehicleattackthreats", "0" );
	#/
	
	level.cleanup_ents = [];
	level.on_tank_protect_player_func = ::protect_player_for_a_bit;
	level.protect_player_on_fire =::FireWeapon_player_protect;	


	if( is_default_start() )
	{
		level.player_tank.teleported_to_path_section = true;
		level.hero_tank.teleported_to_path_section = true;
	}
	
	level.fast_destructible_explode = false;
	
	restart_smash_cars();
	
	PreCacheItem( "m1a1_turret_blank" );
	
	water_splashers_names = [ "script_vehicle_m1a1_abrams", "script_vehicle_m1a1_abrams_player_tm", "script_vehicle_m1a1_abrams_minigun" ];
	foreach( name in water_splashers_names )
	{
		script_vehicle_m1a1_abrams = GetEntArray( name, "classname" );	
		foreach ( spawner in script_vehicle_m1a1_abrams )
			spawner add_spawn_function_if_is_spawner( ::set_water_func );
	}
	
	setup_sandman = GetEnt( "sandman_spawner", "targetname" );
	setup_sandman add_spawn_function( ::setup_sandman);
		
	all_vehicles = GetEntArray( "script_vehicle", "code_classname" );	
	foreach ( spawner in all_vehicles )
	{
		if( isdefined( spawner.script_cheap ) && spawner.script_cheap != 0 )
			spawner add_spawn_function_if_is_spawner( ::stop_engine );
		if ( IsSubStr( spawner.classname, "m1a1" ) || IsSubStr( spawner.classname, "t90" ) )
			spawner add_spawn_function_if_is_spawner( ::shoot_explode );
	}
	
	
	maps\hamburg_garage_crash_anim::main();

	array_thread( GetEntArray( "vehicle_water", "targetname" ), ::add_trigger_function, ::water_splash_test );
	
	PreCacheShader( "black" );
	PreCacheModel( "vehicle_luxurysedan_2008_crush" );
	PreCacheModel( "vehicle_luxurysedan_2008_gray_crush" );
	PreCacheModel( "vehicle_luxurysedan_2008_white_crush" );
	PreCacheModel( "weapon_m4_iw5" );
	PreCacheModel( "viewlegs_generic" );
	
	PreCacheItem( "t90_turret_fast" );
	PreCacheItem( "flash_grenade" );
	PreCacheItem( "javelin" );
	PreCacheItem( "javelin_no_explode" );
	PreCacheItem( "javelin_cheap" );
	
	PreCacheItem( "m4m203_acog_payback" );
	
    maps\hamburg_amb::main();
    
 	init_level_flags();
 	
 	array_thread ( getstructarray( "cannon_target_aim", "targetname" ), ::cannon_target_aim );
	
	maps\hamburg_starts::start_thread();
	
	tank_types = [ "script_vehicle_t90_tank_woodland", "script_vehicle_t90_tank_woodland_hamburg", "script_vehicle_t90_tank_woodland_hamburg", "script_vehicle_m1a1_abrams_minigun", "script_vehicle_m1a1_abrams_minigun" ];
	foreach( tankname in tank_types )
		array_thread ( GetEntArray( tankname , "classname" ), ::add_spawn_function_if_is_spawner, ::init_tank_ai );

	array_thread( GetEntArray( "script_vehicle_m1a1_abrams_minigun", "classname" ), ::add_spawn_function_if_is_spawner, ::extra_m1a1_stuff );
	
	array_thread( GetEntArray( "script_vehicle_apache_mg", "classname" ), ::add_spawn_function_if_is_spawner, ::apaches_stuff );

	bad_place_till_deaths = GetVehicleNodeArray( "bad_place_till_death" , "script_noteworthy" );
	array_thread( bad_place_till_deaths, ::bad_place_till_deaththink );

	tank_gate_opens = GetEntArray( "tank_gate_open" , "targetname" );
	array_thread( tank_gate_opens, ::tank_gate_openthink );

	tank_gate_opens = GetVehicleNodeArray( "tank_gate_open", "script_noteworthy" );
	array_thread( tank_gate_opens, ::tank_gate_openthink );
	
	delaythread( 0.2, ::set_wind, 1001, 2.7, 0.7 );
	
	crawl_while_axis_alives = GetVehicleNodeArray( "crawl_while_axis_alive", "script_noteworthy" );
	array_thread( crawl_while_axis_alives, ::add_trigger_function, ::crawl_while_axis_alivethink );
	crawl_while_axis_alives = GetVehicleNodeArray( "stop_crawl_while_axis_alive", "script_noteworthy" );
	array_thread( crawl_while_axis_alives, ::add_trigger_function, ::crawl_while_axis_alivethink_no_crawl );
	
	kill_guys_in_volume = GetEntArray( "kill_guys_in_volume", "targetname" );
	array_thread( kill_guys_in_volume, ::add_trigger_function, ::kill_guys_in_volume );

	script_vehicle_t90_tank_woodlands = GetEntArray( "script_vehicle_t90_tank_woodland_hamburg" , "classname" );
	array_thread( script_vehicle_t90_tank_woodlands, ::add_spawn_function, ::script_vehicle_t90_tank_woodlandthink );
	
	missile_fires_at_helis = getstructarray_delete( "missile_fires_at_heli" , "targetname" );
	array_thread( missile_fires_at_helis, ::missile_fires_at_helithink );
	
	friend_replenishers = GetEntArray( "friend_replenisher" , "targetname" );
	array_thread( friend_replenishers, ::friend_replenisherthink );
	
	push_colors = GetVehicleNodeArray( "push_color" , "script_noteworthy" );
	array_thread( push_colors, ::push_colorthink );
	
	no_mans_lands = GetEntArray( "no_mans_land" , "targetname" );
	array_thread( no_mans_lands, ::no_mans_landthink );
	
	veh_node_tank_stop_for_enemiess = GetVehicleNodeArray( "veh_node_tank_stop_for_enemies" , "script_noteworthy" );
	array_thread( veh_node_tank_stop_for_enemiess, ::veh_node_tank_stop_for_enemiesthink );
	
	hard_reverses = GetVehicleNodeArray( "hard_reverse" , "script_noteworthy" );
	array_thread( hard_reverses, ::hard_reversethink );
	
	hard_reverses = GetVehicleNodeArray( "hard_forward" , "script_noteworthy" );
	array_thread( hard_reverses, ::hard_forwardthink );

	setup_new_fake_fires = GetEntArray( "setup_new_fake_fire" , "targetname" );
	array_thread( setup_new_fake_fires, ::setup_new_fake_firethink );
	
	trigger_when_ai_clears = GetEntArray( "trigger_when_ai_clear" , "targetname" );
	array_thread( trigger_when_ai_clears, ::trigger_when_ai_clearthink );
	
	delete_on_goals = GetEntArray( "delete_on_goal" , "script_noteworthy" );
	array_thread( delete_on_goals, ::add_spawn_function, ::delete_on_goalthink );
	
	thread free_structs();
	
	thread freetimescale_slomo_junk();
}

freetimescale_slomo_junk()
{
	waittillframeend;
	SoundSetTimeScaleFactor( "Music", 1);
	SoundSetTimeScaleFactor( "Menu", 1 );
	SoundSetTimeScaleFactor( "local3", 1 );
	SoundSetTimeScaleFactor( "Mission", 1 );
	SoundSetTimeScaleFactor( "Announcer", 1 );
	SoundSetTimeScaleFactor( "Bulletimpact", 1);
	SoundSetTimeScaleFactor( "Voice", 1 );
	SoundSetTimeScaleFactor( "effects2", 1 );
	SoundSetTimeScaleFactor( "local", 1 );
	SoundSetTimeScaleFactor( "physics", 1 );
	SoundSetTimeScaleFactor( "ambient", 1 );
	SoundSetTimeScaleFactor( "auto", 1 );
}

restart_smash_cars()
{
	tank_crushable_cars = GetEntArray( "tank_crushable_car" , "script_noteworthy" );
	array_thread( tank_crushable_cars, ::tank_crushable_carthink );
}

delete_on_not_startthink()
{
	if( level.start_point != self.script_startname )
		self delete();
}

stop_engine()
{
	self Vehicle_TurnEngineOff();
}

free_structs()
{
	//wait a little bit
	waittillframeend;
	waittillframeend;
	level.struct = undefined;
	//remove all the structs for start positions
	get_on_foot_start_struct( true );
}

script_vehicle_t90_tank_woodlandthink()
{
	self SetVehWeapon( "t90_turret_bold" );
}

kill_guys_in_volume( triggerer )
{
	target = get_target_ent();
	ai = target get_ai_touching_volume( "axis");
	
	// fix massive amounts of guys screaming
	foreach( guy in ai )
		guy.diequietly = true;
		
	array_kill( ai );
	
	target delete();
	self delete();
}

extra_m1a1_stuff()
{
	self.BadPlaceModifier = 1.2;
	apply_hero_light();
}

apply_hero_light()
{
    self StartUsingHeroOnlyLighting();
}

glory_tank_spawn()
{
	level.glory_tank = spawn_vehicle_from_targetname( "glory_tank" );
	level.glory_tank.veh_pathtype = "constrained";
	level.glory_tank godon();	
	level.glory_tank ent_flag_init( "sync_tanks" );
	level.glory_tank.dontunloadonend = true;
	
	if( is_default_start() )
		level.glory_tank.teleported_to_path_section = true;
}

add_spawn_function_if_is_spawner( function )
{
	if ( ! IsSpawner( self ) )
		return;
	self add_spawn_function( function );
}
	
init_level_flags()
{
	flag_init( "start_beach_defense" );
	flag_init( "in_garage" );
	flag_init( "flash_bangers" );
	flag_init( "garage_jumpers" );
	flag_init( "intro_complete" );
	flag_init( "hot_buildings_destroyed" );
	flag_init( "hot_buildings_destroyed_2" );
	flag_init( "ospreys_go" );
	flag_init( "dropoff_osprey_go" );
	flag_init( "player_unloaded" );
	flag_init( "player_unloading" );
	flag_init( "helix_three_two_hit" );
	flag_init( "glory_tank_ready_for_death" );
	flag_init( "tank_path_bridge" );
	flag_init( "tank_path_before_garage" );
	flag_init( "tank_crash_exit" );
	flag_init( "player_ready_for_minigun_death" );	
	flag_init( "pause_sentry_turrets" );
	flag_init( "over_hovercrafts" );
	flag_init( "start_garage_section" );
	
	flag_init( "snipey_mc_sniperton_sniped" );
	flag_init( "tanks_entered_garage" );
	flag_init( "hind_hind" );
	flag_init( "player_in_tank" );
}

kill_flak_runners()
{
	if ( !IsDefined( level.flak_runners ) )
		return;
		
	array_delete( array_removeundefined( level.flak_runners ) );
}

manage_fake_fire_windows( targetname )
{
	if ( !IsDefined( level.player_in_nomans_land ) )
		level.player_in_nomans_land  = false;

	level endon ( "stop_doing_fake_fire_forever" );
	level endon ( "manage_fake_fire_windows_trigger" );
	
	flag_wait( "player_unloaded" );

	
	if ( !IsDefined( level.opening_fakefire_last_RPG ) )
		level.opening_fakefire_last_RPG = 0;
		
	spots = getstructarray_delete( targetname, "targetname" );
	spots_to_attack = [];
	current_time = GetTime();
	foreach( spot in spots )
	{
		spot.next_shoot_time = get_next_fake_fire_shoot_time( current_time );
		if ( !IsDefined( spot.target ) )
			continue;
		target_spots = getstructarray_delete( spot.target, "targetname" );
		
		if ( !IsDefined( target_spots ) )
			continue;
			
		spots_to_attack = array_merge( spots_to_attack, target_spots);
	}
	
	while( true )
	{
		lowest_next_time = 2000;
		currenttime = gettime();
		foreach( spot in spots )
		{
			next_shoot_time = spot.next_shoot_time;
			
			if( next_shoot_time < lowest_next_time ) 
				lowest_next_time = next_shoot_time;
				
			if ( currenttime > next_shoot_time  )
				spot thread opening_fakefire_think_burst( spots_to_attack );
			
		}
		wait_ms( lowest_next_time );
	}
}

opening_fakefire_machinegun()
{
	thread manage_fake_fire_windows( "event1_ambient_left_bullets" );
	thread manage_fake_fire_windows( "event1_ambient_right_bullets" );
	
}

SHOTWAITMIN = 100;
SHOTWAITMAX = 150;
BURSTWAITMIN = 1400;
BURSTWAITMAX = 2400;


wait_ms( milliseconds )
{
	if( milliseconds == 0 )
		return;
	wait milliseconds / 1000;
}

get_next_fake_fire_shoot_time( current_time )
{
	time = 0;
	if( level.player_in_nomans_land )
	{
		if ( level.player ent_flag( "player_has_red_flashing_overlay" ) )
			time = BURSTWAITMAX;
		else
			time = BURSTWAITMIN * 0.4;
	}
	else
		time = RandomIntRange( BURSTWAITMIN, BURSTWAITMAX );
	
	return current_time + time;
}

opening_fakefire_think_burst( spots_to_attack )
{
	
	self.next_shoot_time = gettime() + 100000;
	burstShots = RandomIntRange( 5, 12 );
	for ( i = 0; i < burstShots; i++ )
	{
		pos = random( spots_to_attack ).origin  + randomvector( 50 );
		if( level.player_in_nomans_land )
		{
			if ( level.player ent_flag( "player_has_red_flashing_overlay" ) )
				wait BURSTWAITMAX / 1000;
			
			if( !level.player_in_nomans_land )
				continue;

			MagicBullet(  "m4m203_acog_payback", self.origin, level.player GetCentroid() );
			wait SHOTWAITMAX / 1000;
			continue;
		}
		else
			MagicBullet( "mp5_drone", self.origin, pos );
			
		wait( RandomFloatRange( SHOTWAITMIN, SHOTWAITMAX ) / 1000 );
	}
	self.next_shoot_time = get_next_fake_fire_shoot_time( gettime() );
}

clean_ai()
{
	ai = GetAIArray( "axis" );
	foreach( guy in ai )
		guy.diequietly = true;
	array_kill( ai );
}

enemies_getaway( targetname )
{
	goal = GetEnt( targetname, "targetname" );
	
	level.enemy_ai = array_removedead_or_dying( level.enemy_ai );
	guys = SortByDistance( level.enemy_ai, goal.origin );
	
	foreach( guy in guys )
	{
		if ( IsDefined ( guy ) && IsAlive( guy ) )
		{
			guy SetGoalPos( goal.origin );
			wait( RandomFloatRange( 1, 2 ) );
		}
	}
}

water_splash_reset_tank( info )
{
	info.water_tags = [];
	info.water_fx = getfx( "tank_water_splash_loop" );
	info.water_fx_ring = getfx( "tank_water_splash_ring" );
	info.splash_delay = 0.15;
	info.ring_interval = 6;
	info.water_tags =[	"tag_wheel_back_left",
						"tag_wheel_back_right",
						"tag_wheel_front_left",
						"tag_wheel_front_right",
						"tag_wheel_middle_left",
						"tag_wheel_middle_right"
						 ];
}

water_splash( trigger )
{
	if ( IsDefined( self.touching_water_trigger ) )
		return;
		
	self notify ( "water_splash" );
	self endon ( "water_splash" );
		
	self.touching_water_trigger = true;
	
	if ( !IsDefined( trigger.water_height ) )
	{
		Assert( IsDefined( trigger.target ) );
		target = getstruct( trigger.target, "targetname" );
		trigger.water_height = target.origin[ 2 ];
	}
	
	if ( !IsDefined( self.touching_trigger_ent ) )
	{
		self.touching_trigger_ent = spawn_tag_origin();
		self.touching_trigger_ent LinkTo( self, "tag_body", ( 0, 0, 0 ), ( 0, 0, 0 ) );
		thread water_splash_cleanup_touching_trigger( self.touching_trigger_ent );
	}
	self.touching_trigger_ent endon ( "death" );
	
	dummy = get_dummy();
	touching_ent = self.touching_trigger_ent;
	
	
	if ( !IsDefined( self.water_splash_info ) )
	{
		info = SpawnStruct();
		self.water_splash_info = info;
		[[ self.water_splash_reset_function ]]( info );
	}
	else
		info = self.water_splash_info;
	
	info.water_height = trigger.water_height;
	
	ring_interval = info.ring_interval;
	do_ring = true;
	
	while ( touching_ent IsTouching( trigger ) )
	{
		wait info.splash_delay;
		
		for ( i = 0; i < info.water_tags.size; i++ )
			water_splash_single( i, do_ring );
			
		dummy = get_dummy();
		if ( dummy != self )
			touching_ent = dummy;
		else
			touching_ent = self.touching_trigger_ent;

	}
	self.touching_water_trigger = undefined;
	[[ self.water_splash_reset_function ]]( info );
}

water_splash_cleanup_touching_trigger( ent )
{
	ent endon ( "death" );
	self waittill ( "death" );
	ent Delete();
}

water_splash_single( water_tag_index, do_ring )
{
	info = self.water_splash_info;
	dummy = get_dummy();
	
	tag = info.water_tags[ water_tag_index ];
	tag_origin = dummy GetTagOrigin( tag );
	start = tag_origin + ( 0, 0, 150 );
	end = tag_origin - ( 0, 0, 150 );
	trace = BulletTrace( start, end, false, self );
	
	if ( trace[ "surfacetype" ] != "water" )
		return;
		
	start = trace[ "position" ];

	if ( abs( start[ 2 ] -info.water_height ) > 100 && ! start[ 2 ]  < info.water_height )
		return;

	angles = flat_angle( dummy GetTagAngles( tag ) );
	forward = AnglesToForward( angles );
	up = AnglesToUp( angles );
	PlayFX( info.water_fx, start, up, forward );
	
	if ( do_ring )
	{
		PlayFX( info.water_fx_ring, start, up, forward );
	}
}

set_water_func()
{
	self.water_splash_function = ::water_splash;
	self.water_splash_reset_function = ::water_splash_reset_tank;
}

water_splash_test( triggerer )
{
	if ( IsDefined( triggerer.water_splash_function ) )
		triggerer thread [[ triggerer.water_splash_function ]]( self );
	thread add_trigger_function( ::water_splash_test );
}

put_player_on_tank( )
{
	maps\_compass::setupMiniMap("compass_map_hamburg", "city_minimap_corner");
	level.player_tank notify ( "stop_vehicle_shoot_shock" );
	level notify ( "stop_doing_fake_fire_forever" );
	level.player_tank vehicleusealtblendedaudio( false );
	level.player_tank SetModel( "vehicle_m1a1_abrams_viewmodel" );

	set_ambient( "hamburg_tankgun_city" );
	
	level.player_tank thread kill_the_minigun_guy();
	
	level.player_tank get_rid_of_tanks_mg();
	vehicle_scripts\_m1a1_player_control::init_tankcommander_code( level.player_tank );
	level.player_tank thread turret_attack_think_hamburg();

}

get_rid_of_tanks_mg()
{
	if ( IsDefined( level.player_tank.mgturret[ 1 ] ) )
		level.player_tank.mgturret[1] delete();
	level.player_tank.mgturret = array_removeundefined( level.player_tank.mgturret );	
}

kill_the_minigun_guy()
{
	self riders_godoff();
	foreach( rider in self.riders )
		if( IsAlive(rider) && rider.vehicle_position == 2 )
			rider delete();
}

do_path_teleport( node_name )
{
	node = GetVehicleNode( node_name, "targetname" );
	self Vehicle_Teleport( node.origin, node.angles );
	self.teleported_to_path_section = true;
	
//	if( self == level.player_tank )
//		level.player SetPlayerAngles( self.angles );
}

do_path_section( node_name, is_target )
{
	if ( !IsDefined( is_target ) || is_target == false )
		node = GetVehicleNode( node_name, "targetname" );
	else
		node = GetVehicleNode(  node_name, "target"  );

	if( node ent_flag_exist( "doing_path_section" ) )
		return;
	node ent_flag_init( "doing_path_section" );	
		
	if ( path_section_should_teleport() )
	{
		do_path_teleport( node_name );
	}
	
	self AttachPath( node );
	self StartPath( node );
	self thread vehicle_paths( node );
	self thread do_path_section_final( node );
}

do_path_section_without_the_hassle( node_name, is_target )
{
	if ( !IsDefined( is_target ) || is_target == false )
		node = GetVehicleNode( node_name, "targetname" );
	else
		node = GetVehicleNode(  node_name, "target"  );

	self StartPath( node );
	self thread vehicle_paths( node );
}


path_section_should_teleport()
{
	if (!IsDefined( self.teleported_to_path_section ) )
		return true;
	return false;
}

do_path_section_final( node )
{
	self waittill ( "reached_end_node" );
	node ent_flag_set( "doing_path_section" );	
}

cannon_target_aim()
{
	vehicle_node = GetVehicleNode( self.target, "targetname" );
	vehicle = vehicle_node waittill_triggered_current();
	set_cannon_target_origin( vehicle, self.origin );
}

set_cannon_target_origin( vehicle, origin )
{
	if ( !IsAlive( vehicle ) )
		return;
	vehicle.default_target_vec = origin;
	if ( !IsDefined( vehicle.tank_queue ) )
		vehicle.tank_queue = [];
	vehicle turret_idle();
}

shoot_explode()
{
	self notify ( "new_shoot_explode" );
	self endon ( "new_shoot_explode" );
	if ( !IsSubStr( self.classname, "m1a1" ) && !IsSubStr( self.classname, "t90" ) )
		return;
		
	thread test_hamburg_tank_anim();
	
	self SetVehWeapon( "m1a1_turret_blank" );		
	
	self endon ( "death" );
	while( true )
	{
		self waittill( "weapon_fired" ); 
		self vehicle_ai_event( "turret_fire" );
		shoot_anim();
		trace = tank_play_traced_effect();
		tank_do_fake_damage( trace );
	}
}

do_decal_square( position )
{
	vects = [ ( 1, 0, 0 ), ( 0, 1, 0 ), ( -1, 0, 0 ), ( 0, -1, 0 ), ( 0, 0, 1 ), ( 0, 0, -1 ) ];
	foreach ( vec in vects )
	{
		trace = BulletTrace( position, position + ( vec * 256 ), false, self );
		if ( trace[ "fraction" ] == 1.0 )
			continue;
		if ( !IsDefined( trace[ "surfacetype" ] ) )
			continue;
			
		surfacetype = trace[ "surfacetype" ];
		
		angle = VectorToAngles( trace[ "normal" ] );
		PlayFX( getfx( "tank_blast_decal_" + surfacetype ), trace[ "position" ]  , AnglesToForward( angle ), AnglesToUp( angle ) );
	}
}

tank_play_traced_effect()
{
	start = self GetTagOrigin( "tag_flash" );
	end = tag_project( "tag_flash", 99999 );
	trace = BulletTrace( start, end, true, self );
	surfacetype = trace[ "surfacetype" ];
	
	hit_entity = IsDefined( trace[ "entity" ] );
	
	if ( !IsDefined( surfacetype ) )
		return trace;
	
	if ( trace[ "fraction" ] == 1 )
		return trace;
	

//	between_angle = trace[ "normal" ] + ( -1 * AnglesToForward( self GetTagAngles( "tag_flash" ) ) );
	between_angle = ( -1 * AnglesToForward( self GetTagAngles( "tag_flash" ) ) );
	
	angle = VectorToAngles( trace[ "normal" ] );
	
	the_trace_to_decal = trace;
	if ( hit_entity )
	{
		down_trace = BulletTrace( trace[ "position" ], trace[ "position" ] + ( 0, 0, -10000 ), false, trace[ "entity" ] );
		the_trace_to_decal = trace;
		
		if ( trace[ "entity" ].origin[ 2 ] - down_trace[ "position" ][ 2 ]     < 54 )
		{
			angle = VectorToAngles( down_trace[ "normal" ] );
			the_trace_to_decal = down_trace;
		}
	}

	if ( IsDefined(  level.player_tank ) && self == level.player_tank )
	{	
		do_decal_square( the_trace_to_decal[ "position" ] + VectorNormalize( the_trace_to_decal[ "normal" ] ) * 77 );
		PlayFX( getfx( "tank_blast_decal_" + surfacetype ), the_trace_to_decal[ "position" ]  , AnglesToForward( angle ), AnglesToUp( angle ) );
	}
	
	
	range = 500;
	PhysicsExplosionSphere( trace[ "position" ], range + 300, range * 0.25, 1 );
	
	angle = VectorToAngles( between_angle );
	PlayFX( getfx( "tank_blast_" + surfacetype ), trace[ "position" ]  , AnglesToForward( angle ), AnglesToUp( angle ) );
	thread play_sound_in_space( "grenade_explode_default", trace[ "position" ] );
	return trace;
}

tank_do_fake_damage( trace )
{
	is_player_friend = ( self.script_team == "axis" );
	
	if( is_player_friend )
		level.player SetCanRadiusDamage( false );

	attacker = self;
	
	hit_entity = IsDefined( trace[ "entity" ] );
	
	RadiusDamage( trace[ "position" ], self.turret_damage_range, self.turret_damage_max, self.turret_damage_min, self );
	
	if( hit_entity )
	{
		if ( IsSubStr( trace[ "entity" ].classname, "t90" ) || IsSubStr( trace[ "entity" ].classname, "btr" ) )
		{
			if ( IsDefined( trace[ "entity" ].godmode ) && trace[ "entity" ].godmode )
			{
				//IPrintLn( "trying to kill godmode guy " );
			}
			else
			{
				trace[ "entity" ] Kill();
			} 
				
		}
	}

	if( is_player_friend )
		level.player SetCanRadiusDamage( true );
}

set_tank_damage( damage_range, damage_max, damage_min )
{	
	self.og_turret_damage_range = self.turret_damage_range;
	self.turret_damage_range = damage_range;

	self.og_turret_damage_max = self.turret_damage_max;
	self.turret_damage_max = damage_max;

	self.og_turret_damage_min = self.turret_damage_min;
	self.turret_damage_min = damage_min;
}

reset_tank_damage()
{
	Assert( IsDefined( self.og_turret_damage_range ) );
	Assert( IsDefined( self.og_turret_damage_max ) );
	Assert( IsDefined( self.og_turret_damage_min ) );

	self.turret_damage_range = self.og_turret_damage_range;
	self.turret_damage_max = self.og_turret_damage_max;
	self.turret_damage_min = self.og_turret_damage_min;

	self.og_turret_damage_range = undefined;
	self.og_turret_damage_max = undefined;
	self.og_turret_damage_min = undefined;
}

#using_animtree( "vehicles" );

shoot_anim()
{
	self ClearAnim( %abrams_shoot_kick, 0 );
	self SetAnimRestart( %abrams_shoot_kick );
}

garage_cleanup_beach_area()
{
	beach_areas = GetEntArray( "beach_area", "script_noteworthy" );
	wait 1;
	delete_destructibles_in_volumes( beach_areas, true );
	wait 1;
	delete_interactives_in_volumes( beach_areas, true );
	wait 1;
    delete_exploders_in_volumes( beach_areas, true );
	wait 1;
    delete_ai_in_volumes( beach_areas );
	wait 1;
    delete_vehicle_corpses_in_volumes( beach_areas );
	wait 1;
    delete_all_ents_in_volumes( beach_areas );
	wait 1;
	fx_volume_pause_noteworthy( "beach_area", true  );	
}

delete_all_ents_in_volumes( volumes )
{
	test_org = Spawn( "script_origin", ( 0, 0, 0 ) );
	test_org.dontdeleteme = true;
	delete_ents = [];
	incs = 0;
	classtypes = [ "script_model", "script_vehicle", "script_brushmodel", "trigger_multiple" ];
	foreach(class in classtypes )
	{
		ents = GetEntArray( class, "classname" );
		foreach( volume in volumes )
		{
			foreach ( ent in ents )
			{
				incs++;
				incs %= 3;
				if( incs == 1 )
					wait 0.05;
					
				if ( !IsDefined( ent ) )
					continue;
					
				if( IsSpawner( ent ) )
					continue;
					
				if ( IsDefined( ent.targetname ) )
				{
					if( ent.targetname == "helicopter_crash_location" )
						continue;
					if( ent.targetname == "tank_crew_2" )
						continue;
					if( ent.targetname == "tank_crew_1" )
						continue;	
					if( ent.targetname == "intelligence_item" )
						continue;
				}
				
				if ( IsDefined( ent.script_noteworthy ) )
				{
					if( ent.script_noteworthy == "special_place_in_my_heart" )
						continue;	
				}
				
				// deleting origins is just not worth the hassle, see play_sound stuff that spawns them.  I don't know what things are that don't have classname but GetEntArray() gets them so lets just ignore them.
				// SJP: ignore vehicle collmaps- deleting them leaves all vehicles on the b side with no collision :)
				if ( ent.classname == "script_vehicle_collmap" )
					continue;
		
				if ( IsDefined( ent.dontdeleteme ) )
					continue; // player tanks trace entity
					
				update_bcs = false;
				if( IsSubStr( ent.classname, "trigger_multiple_bcs" ) )
					update_bcs = true;	
		
		        test_org.origin = ent GetOrigin();
		        if ( !test_org IsTouching( volume ) )
		            continue;

				if( array_contains( volume.fx , ent ) )
					continue;
				if( array_contains( volumes , ent ) )
					continue;
		            
		       	ent Delete();
		       	
		       	if( update_bcs )
					anim.bcs_locations = array_removeundefined( anim.bcs_locations );
		       	
			}
		}
		
	} 
	test_org Delete();	
	
}

cleanup_bridge_and_before_garage_area()
{
	fx_volume_pause_noteworthy( "bridge_and_before_garage_area", true );	
	wait 1;
	bridge_and_before_garage_area = getentarray( "bridge_and_before_garage_area", "script_noteworthy" );
	delete_destructibles_in_volumes( bridge_and_before_garage_area, true );
	wait 1;
	delete_interactives_in_volumes( bridge_and_before_garage_area, true );
	wait 1;
    delete_exploders_in_volumes( bridge_and_before_garage_area, true );
	wait 1;
    delete_ai_in_volumes( bridge_and_before_garage_area );
	wait 1;
    delete_vehicle_corpses_in_volumes( bridge_and_before_garage_area );
	wait 1;
	delete_all_ents_in_volumes( bridge_and_before_garage_area );
	wait 1;
	delaythread( 1.1, ::garage_cleanup_beach_area ); // one more time for start poitns.

}

delete_ai_in_volumes( volumes )
{
	ents = GetAIArray();

	test_org = Spawn( "script_origin", ( 0, 0, 0 ) );
	delete_ents = [];
	
	incs = 0;
	foreach( volume in volumes )
		foreach ( ent in ents )
		{
			incs++;
			incs %= 5;
			if( incs == 1 )
				wait 0.05;
			if ( !IsDefined( ent ) )
				continue;
	        test_org.origin = ent GetOrigin();
	        if ( !test_org IsTouching( volume ) )
	            continue;
			if ( IsDefined( ent.dontdeleteme ) )
				continue;	            
			ent Delete();
		}

	test_org Delete();	
}

delete_vehicle_corpses_in_volumes( volumes )
{
	ents = GetEntArray( "script_vehicle_corpse", "classname" );
	test_org = Spawn( "script_origin", ( 0, 0, 0 ) );
	delete_ents = [];
	foreach( volume in volumes )
		foreach ( ent in ents )
		{
	        test_org.origin = ent GetOrigin();
	        if ( !test_org IsTouching( volume ) )
	            continue;
			if ( IsDefined( ent.deathfx_ent ) )
				ent.deathfx_ent Delete();
			ent Delete();
		}
	test_org Delete();	
}

concrete_cracks( flag_msg )
{
	level endon ( "stop_concrete_cracks" );
	self endon ( "death" );

	if ( IsDefined( flag_msg ) )
	{
		flag_wait( flag_msg );
	}
	
	crack_interval = 5;
	inc = 0;
	cracktags = [ "tag_wheel_front_left" , "tag_wheel_front_right" ];
	spewtags = [ "tag_wheel_back_left" , "tag_wheel_back_right","tag_wheel_middle_left" , "tag_wheel_middle_right","tag_wheel_front_left" , "tag_wheel_front_right" ];
	
	while( true )
	{
		wait 0.15;
		foreach( tag in spewtags )
		{
			bodyorg = self GetTagOrigin( tag );
			down_trace = BulletTrace(bodyorg  , bodyorg + ( 0, 0, -10000 ), true, self);
			angle = VectorToAngles( down_trace[ "normal" ] );
			PlayFX( getfx( "tank_concrete_cracks_spitup"  ), down_trace[ "position" ]  , AnglesToForward( angle ), AnglesToUp( angle ) );
		}
		
		inc++;
		inc %= crack_interval;
		if ( inc )
			continue;
			
		foreach ( tag in cracktags )
		{
			bodyorg = self GetTagOrigin( tag );
			down_trace = BulletTrace( bodyorg, bodyorg + ( 0, 0, -10000 ), true, self );
			angle = VectorToAngles( down_trace[ "normal" ] );
			PlayFX( getfx( "tank_concrete_cracks" ), down_trace[ "position" ]  , AnglesToForward( angle ), AnglesToUp( angle ) );
		}	
			
	}
}

// disables grenades for one NPC, saving his grenade ammo count
disable_grenades()
{
	if ( !IsAI( self ) )
		return;
	self.grenadeammo = 0;
}

#using_animtree( "destructibles" );

get_linked_ent_undefined_return()
{
	targets = get_linked_ents();
	if( !targets.size )
		return undefined;

	assert( targets.size == 1 );
	
	return targets[0];
}

tank_crushable_carthink()
{
	target = get_linked_ent_undefined_return();
	
	if( !isdefined( target ) )
		return; // it's allready been done and cleaned up.
	
	self endon ("masking_destructible" );

	self notify ( "tank_crushable_carthink" );
	self endon ( "tank_crushable_carthink" );

	last_tank = undefined;
	
	while( true )
	{
		target waittill ( "trigger", other );

		if ( !isdefined( last_tank ) || last_tank != other )
		{
			if ( isdefined( target.script_soundalias ) ) 
			{
				if ( !isSubStr( target.script_soundalias, "_player_" ) || Distance( level.player.origin, self.origin ) < 800 ) // need this because the sound is 2d apparently.
				{

					thread play_sound_in_space( target.script_soundalias, self.origin );
				}
			}
			last_tank = other;
		}
		
		wait( 2 );
		
		if ( Distance( other.origin, self.origin ) > 240 )
			continue;
//		self DoDamage( 3333, self.origin, level.player, level.player );
		
		thread protect_player_for_a_bit();
//		self destructible_force_explosion();
		PlayFX( getfx( "tank_crush" ), self.origin );	

		self hide();
		
		model = spawn_tag_origin();
		if( IsSubStr( self.model, "vehicle_luxurysedan_2008" ) )
			model SetModel( "vehicle_luxurysedan_2008_crush" );

		if( IsSubStr( self.model, "vehicle_luxurysedan_2008_gray" ) )
			model SetModel( "vehicle_luxurysedan_2008_gray_crush" );

		if( IsSubStr( self.model, "vehicle_luxurysedan_2008_white" ) )
			model SetModel( "vehicle_luxurysedan_2008_white_crush" );
		
		model thread play_sound_on_entity( "hamburg_crush_tank" );
		model show();
		target delete();
		return;	
	}
}


// passive due to ents not existing on start points.
cleanup_ents_passive( groupname )
{
	if ( ! IsDefined( level.cleanup_ents ) )
		return;
    if ( !IsDefined( level.cleanup_ents[ groupname ] ) )
		return;
		
	cleanup_ents( groupname );
}

crawl_while_axis_alivethink_no_crawl( player_vehicle )
{
	wait RandomFloatRange( 1 ,2 );
	player_vehicle vehicle_resume_if_not_named_stop( 3 );	
	level.hero_tank vehicle_resume_if_not_named_stop( 3 );	
	player_vehicle notify ( "stop_crawl_while_axis_alivethink" );	
}


vehicle_resume_if_not_named_stop( resume_speed )
{
	if ( IsDefined( self.vehicle_stop_named ) )
	{
		if( self.vehicle_stop_named.size ) 
			return;
	}
	self ResumeSpeed( resume_speed );
}

vehicle_setspeed_if_not_named_stop( speed, accel, decel )
{
	if ( IsDefined( self.vehicle_stop_named ) )
	{
		if( self.vehicle_stop_named.size ) 
			return;
	}
	self Vehicle_SetSpeed( speed, accel, decel );
}

crawl_while_axis_alivethink( player_vehicle )
{
	axis = GetAIArray( "axis" );
	if( ! axis.size )
		return;
		
	player_vehicle notify ( "stop_crawl_while_axis_alivethink" );	
	player_vehicle endon ( "stop_crawl_while_axis_alivethink" );	
	
	player_vehicle vehicle_setspeed_if_not_named_stop( 3, 15, 15 );
	level.hero_tank vehicle_setspeed_if_not_named_stop( 3, 15, 15 );
	
	while( GetAIArray( "axis" ).size )
	{
		ais = GetAIArray( "axis" );
		speedtogo = 5;
		if( ais.size < 6 )
			speedtogo = 6;
		if( ais.size < 4 )
			speedtogo = 8;
		if( ais.size < 3 ) 
			speedtogo = 10;
		if( ais.size < 2 )
			speedtogo = 14;
			
		player_vehicle vehicle_setspeed_if_not_named_stop( speedtogo, 15, 15 );
		level.hero_tank vehicle_setspeed_if_not_named_stop( speedtogo, 15, 15 );
			
		wait 0.15;
		
	}
	crawl_while_axis_alivethink_no_crawl( player_vehicle );
}

FireWeapon_player_protect()
{
	if( self == level.playervehicle || self.script_team == "allies"  )
		thread protect_player_for_a_bit();
	self FireWeapon();
}

protect_player_for_a_bit()
{
	if( ( !IsDefined(level.player_tank) ) )
		return; // player is already protected or not in a tank.
		
	level.player endon ( "going_inside" );
	level.player notify ( "stop_protect_player_for_a_bit" );
	level.player endon ( "stop_protect_player_for_a_bit" );
	
	level.player EnableInvulnerability();
	
	waittillframeend;

	if ( IsDefined( level.player.stayinvulnerable ) && level.player.stayinvulnerable  )
		return;
		
	level.player DisableInvulnerability();
}

get_player_spot( player_truck )
{
	
    foreach ( junk in player_truck.truckjunk )
        if ( IsDefined( junk.script_noteworthy ) && junk.script_noteworthy == "player_spot" )
        {
            junk NotSolid();
            player_truck.body_referenced_junk = junk;
            junk hide();
            return junk;
        }
            
    AssertMsg( "no player spot!" );
}


riders_godoff()
{
	foreach( rider in self.riders )
		if ( IsDefined( rider.magic_bullet_shield ) )
			rider stop_magic_bullet_shield();
}

get_linked_ent_or_vehiclenode()
{
	array = get_linked_ents();
	if( array.size > 0 )
	{
		assert( array.size == 1 );
		assert( isdefined( array[ 0 ] ) );
		return array[ 0 ];
	}
	
	array = get_linked_vehicle_nodes();
	if( array.size > 0 )
	{
		assert( array.size == 1 );
		assert( isdefined( array[ 0 ] ) );
		return array[ 0 ];
	}
	AssertMsg( "no_linked ent_or_vehiclenode" );
}


missile_fires_at_helithink()
{
	trigger = get_linked_ent_or_vehiclenode();
	trigger waittill ( "trigger" );
	vehicle = get_vehicle( self.target, "targetname" );
	
	if( !isdefined( vehicle ) )
	{
		/#
			IPrintLn( "no vehicle for missile_fires_at_helithink()" );
		#/
		return;
	}	
	
	vehicle riders_godoff();
	
	if( self.target != "extra_osprey" )
		vehicle godoff();
		
	vehicle.enableRocketDeath = true;
	
	newMissile = MagicBullet( "javelin_no_explode", self.origin, vehicle GetCentroid() );
	newmissile Missile_SetFlightmodeDirect();
	newMissile Missile_SetTargetEnt( vehicle );
}

apaches_stuff()
{
	self.dontunloadonend = true;
	self SetHoverParams( 233, 222, 55 );
	thread tank_mgs_target_drones();
}


#using_animtree( "vehicles" );
test_hamburg_tank_anim()
{
	self notify ( "test_hamburg_tank_anim" );
	self endon ( "test_hamburg_tank_anim" );
	self waittill ( "death" );
	if ( !IsDefined( self ) )
		return;
	self SetAnim( %hamburg_tank_explosion );
}

tank_delay_thoughts( time_ms )
{
	level.tank_thought_next = gettime() + time_ms;
}

tank_gate_openthink()
{
	vehicle_nodes = get_linked_vehicle_nodes();
	assert( vehicle_nodes.size );
	array_thread( vehicle_nodes, ::tank_gate_openthink_node , self);
	self.tank_gate_open_triggered = false;
	self add_trigger_function( ::tank_gate_openthink_trigger_func );
}

tank_gate_openthink_trigger_func( other )
{
	self.tank_gate_open_triggered = true;
	if ( IsDefined( self.classname ) )
		self Delete();
}

trigger_or_node_waittill_trigger()
{
	if ( !IsDefined( self.classname ) )
		other = waittill_triggered_current();
	else
		self waittill ( "trigger", other );
	return other;
}

tank_gate_openthink_node( trigger )
{
	self endon ( "forced_open" );
	self.tank_gate_open = false;
	self.tank_gate_open_trigger = trigger;
	other = trigger_or_node_waittill_trigger();
	if ( !IsDefined( trigger ) || trigger.tank_gate_open_triggered )
		return;
	other endon ( "death" );	
	
	identifier = self.script_linkname;
	Assert( IsDefined( identifier ) );
	other vehicle_stop_named( "tank_gate_open" + identifier, 15, 15 );
	trigger trigger_or_node_waittill_trigger();
	other vehicle_resume_named( "tank_gate_open" + identifier );
}

CONST_bp_height = 300;
CONST_BP_DURATION = 0.5;
hamburg_badplace()
{
	if ( !IsDefined( self.script_badplace ) )
		return;
	self endon( "kill_badplace_forever" );
	if ( !self Vehicle_IsPhysVeh() )
		self endon( "death" );
	self endon( "delete" );
	hasturret = IsDefined( level.vehicle_hasMainTurret[ self.model ] ) && level.vehicle_hasMainTurret[ self.model ];
	bp_angle_left = 17;
	bp_angle_right = 17;
	for ( ;; )
	{
		if ( !IsDefined( self ) )
			return;
		if ( !IsDefined( self.script_badplace ) || !self.script_badplace )
		{
// 			BadPlace_Delete( "tankbadplace" );
			while ( IsDefined( self ) && ( !IsDefined( self.script_badplace ) || !self.script_badplace ) )
				wait 0.5;
			if ( !IsDefined( self ) )
				return;
		}
		speed = self Vehicle_GetSpeed();
		if ( speed <= 0 )
		{
			wait CONST_BP_DURATION;
			continue;
		}
		if ( speed < 5 )
			bp_radius = 180;
		else if ( ( speed > 5 ) && ( speed < 8 ) )
			bp_radius = 230;
		else
			bp_radius = 280;

		if ( IsDefined( self.BadPlaceModifier ) )
			bp_radius = ( bp_radius * self.BadPlaceModifier );

// 			bp_direction = AnglesToForward( self.angles );
		if ( hasturret )
			bp_direction = AnglesToForward( self GetTagAngles( "tag_turret" ) );
		else
			bp_direction = AnglesToForward( self.angles );
			
		cylinder_org = tag_project( "tag_origin", 148 );

		// have to use unique names for each bad place. if not they will be shared for all vehicles and thats not good. - R
		BadPlace_Arc( self.unique_id + "arc", CONST_BP_DURATION, self.origin, bp_radius * 1.9, CONST_bp_height, bp_direction, bp_angle_left, bp_angle_right, "axis", "team3", "allies" );
		BadPlace_Cylinder( self.unique_id + "cyl", CONST_BP_DURATION, cylinder_org, bp_radius, CONST_bp_height, "axis", "team3", "allies" );

		wait CONST_BP_DURATION + 0.05;
	}
}

no_mans_landthink()
{
	flag_wait( "player_unloaded" );
	self endon ( "death" );
	while( true )
	{
		self waittill ( "trigger", other );
		if( IsAI( other ) )
			childthread no_mans_land_AI( other );
		else if ( IsPlayer( other ) )
			childthread no_mans_land_player( other );
	}
}

PLAYER_PARTICIPATING_RADIUS_SQRD = 202500;

no_mans_land_player( player )
{
	if ( IsDefined( player.no_mans_land_AI ) && player.no_mans_land_AI )
		return;
		
	player.no_mans_land_AI = true;
	
	wait RandomFloatRange( 0.7, 1.5 );

	excluders = [];
	
	while ( player IsTouching( self ) )
	{
		if ( excluders.size )
			friendly_ai = get_closest_ai( player.origin, "allies", excluders);
		else
			friendly_ai = get_closest_ai( player.origin, "allies" );

		//friendly vehicles ai don't count.
		if( IsDefined( friendly_ai ) && IsDefined( friendly_ai.ridingvehicle ) )
		{
			excluders[excluders.size] = friendly_ai;	
			continue;
		}
		
		if ( !IsDefined( friendly_ai ) || DistanceSquared( friendly_ai.origin, player.origin ) > PLAYER_PARTICIPATING_RADIUS_SQRD )
		{
			level.player_in_nomans_land = true;
			level.player.attackeraccuracy = 20000;
			level.player.threatbias = 20000;
		}
		else
		{
			no_mans_land_player_reset();
		}
		wait 0.15;
	}
	
	no_mans_land_player_reset();
	player.no_mans_land_AI = false;

	
}

no_mans_land_player_reset()
{
	level.player maps\_gameskill::setDifficulty();
	level.player_in_nomans_land = false;
}

no_mans_land_AI( guy )
{
	if ( IsDefined( guy.no_mans_land_AI ) && guy.no_mans_land_AI )
		return;
		
	if( guy.team == "axis" )
		return;
		
	guy.no_mans_land_AI = true;
	guy notify ( "no_mans_land_AI" );
	guy endon ( "no_mans_land_AI" );
	guy endon ( "death" );
	guy enable_sprint();
	while ( guy IsTouching( self ) )
		wait 0.2;
	guy disable_sprint();
	guy.no_mans_land_AI = false;
}

push_colorthink()
{
	waittill_triggered_current();
	linked_trigger = get_linked_ents();
	if( linked_trigger.size == 0 )
		return;
	Assert( linked_trigger.size == 1 );
	linked_trigger[ 0 ] notify ( "trigger", level.player );
	if ( IsDefined( self.classname ) )
		self Delete();
}

friend_replenisherthink()
{
	Assert( IsDefined( self.target ) );
	Assert( IsDefined( self.script_forceColor ) );
	
	while( true )
	{
		self waittill ( "trigger" );
		
		while( level.player IsTouching( self ) )
		{
			do_replenish_once();
			wait RandomFloatRange( 5,10 );
		}
		
	}
	
}

do_replenish_once()
{
	colors = StrTok( self.script_forceColor, " " );
	
	totalguy_tally = 0;
	buckets = [];
	foreach( color in colors )
	{
		guys = get_force_color_guys( "allies", color );
		totalguy_tally += guys.size;
		struct = SpawnStruct();
		struct.numguys = guys.size;
		struct.guys_to_spawn = 0;
		buckets[color] = struct;
	}
	
	friends_to_spawn = level.FRIEND_MAX - totalguy_tally;
	
	if( friends_to_spawn <= 0 )
		return;
	
	for ( i = 0; i < friends_to_spawn; i++ )
	{
		lesser = 80;
		destcolor = "";
		foreach( color in colors )
			if( buckets[color].numguys < lesser ) 
			{
				destcolor = color;
				lesser = buckets[color].numguys;
			}
		Assert( destcolor != "" );
		buckets[ destcolor ].guys_to_spawn++;
		buckets[ destcolor ].numguys++;
	}
	
	foreach( color in colors )
	{
		if( buckets[ color ].guys_to_spawn == 0 )
			continue;
		replenish_friends( color, self.target, buckets[ color ].guys_to_spawn );
	}
	
}

replenish_friends( colorgroup, targetname, spawn_count )
{
	do_spawn_max = false;
	if( !IsDefined( spawn_count ) )
	{
		spawn_count = level.FRIEND_MAX;
		do_spawn_max = true;
	}
		
	Assert( spawn_count > 0 );
	
	guys = get_force_color_guys( "allies", colorgroup );
	spawner_positions = getstructarray( targetname, "targetname" );
	spawner_positions = array_randomize( spawner_positions );
	
	if( do_spawn_max )
		friends_to_spawn = spawn_count - guys.size;
	else
		friends_to_spawn = spawn_count;
	
	Assert( friends_to_spawn <= spawner_positions.size );
	
	main_spawner = GetEnt( "master_replenish_spawner", "targetname" );
	for ( i = 0; i < friends_to_spawn; i++ )
	{
		
		main_spawner.count = 1;
		main_spawner.origin = spawner_positions[ i ].origin;
		
		if( IsDefined( spawner_positions[ i ].angles ) )
			main_spawner.angles = spawner_positions[ i ].angles;
			
		guy = main_spawner spawn_ai( true );
		if( !IsDefined( guy ) )
			continue;
		guy thread set_force_color( colorgroup );
		guy thread replenish_guy_helper();
		
		// doesn't like multiple guys spawned on the same frame from one spawner
		wait 0.05;
		if( get_all_force_color_friendlies().size > level.FRIEND_MAX )
			return;
	}
}

replenish_guy_helper()
{
	self endon ( "death" );
	self.ignoreme = true;
	self enable_sprint();
	wait 3;
	self.ignoreme = false;
	self disable_sprint();
	
}

call_on_thread_end( threadname, code_function )
{
	while ( IsDefined( threadname ) )
		wait 0.05;
	self call [[code_function]]();
}


veh_node_tank_stop_for_enemiesthink()
{
	tank = waittill_triggered_current();
	tank vehicle_stop_named( "tank_stop_for_enemies", 15, 15 );	
	
	while( true )
	{
		linked_spawners = get_linked_ents();
		Assert( linked_spawners.size );
		alive_or_spawner_not_spawned = false;
		
		foreach( a in linked_spawners )
		{
			if( !IsSpawner( a ) && IsAlive( a ) )
			{
				alive_or_spawner_not_spawned = true;
				break;
			}
			
			if ( IsSpawner( a ) && !IsDefined( a.spawned_count ) )
			{
				alive_or_spawner_not_spawned = true;
				break;
			}
		}
			
		if( !alive_or_spawner_not_spawned )
			break;
			
		wait RandomFloatRange( 0.5, 2);
		
	}
		
	tank vehicle_resume_named( "tank_stop_for_enemies" );
	
}

setup_new_fake_firethink()
{
	self waittill ( "trigger" );
	level notify ( "manage_fake_fire_windows_trigger" );
	thread manage_fake_fire_windows( self.target );
	self delete();
}

trigger_when_ai_clearthink()
{
	self waittill ( "trigger" );
	volume = GetEnt( self.target, "targetname" );
	trigger = volume get_linked_ent();
	trigger endon ( "trigger" );
	while( volume get_ai_touching_volume( "allies" ).size )
		wait 0.1;
	trigger notify ( "trigger" );
	self delete();
}

hard_reversethink()
{
	do_hard_direction_change( "reverse" );
}


hard_forwardthink()
{
	do_hard_direction_change( "forward" );
}

do_hard_direction_change( direction )
{
	destination_path = get_linked_ent_or_vehiclenode();
	Assert( !IsDefined( destination_path.classname ) );
	vehicle = waittill_triggered_current();
	wait 0.5;
	vehicle.veh_transmission = direction;
	vehicle.script_transmission = direction;
	vehicle Vehicle_SetSpeed( 10, 10, 10 );
	vehicle delayCall( 2, ::ResumeSpeed, 10 );
	vehicle StartPath( destination_path );
	vehicle thread vehicle_paths( destination_path );
}

get_on_foot_start_struct( post_load_cleanup )
{
	if( !isdefined( post_load_cleanup ) )
		post_load_cleanup = false;
	array = getstructarray_delete( "on_foot_start", "targetname" );
	the_struct = undefined;
	foreach( struct in array )
	{
		if( struct.script_startname == level.start_point )
		{
			the_struct = struct;
			continue;
		}
		getstructarray_delete( struct.target, "targetname" );
	}
			
	if ( IsDefined( the_struct ) )
		return the_struct;
	
	if( post_load_cleanup ) 
		return;

	AssertMsg( "no on foot start point! " );
}

mask_destructibles_in_volumes_noteworthy( noteworthy )
{
	volumes = GetEntArray( noteworthy, "script_noteworthy" );
	mask_destructibles_in_volumes( volumes );
	mask_exploders_in_volume( volumes );
}

activate_destructibles_in_volumes_noteworthy( noteworthy )
{
	volumes = GetEntArray( noteworthy, "script_noteworthy" );
	foreach( volume in volumes )
		volume activate_destructibles_in_volume();
		
	restart_smash_cars();
}

get_sandman()
{
	if( IsAlive( level.sandman ) )
		return level.sandman;
	spawner = GetEnt( "sandman_spawner", "targetname" );
	level.sandman = spawner spawn_ai( true );
	return level.sandman;
}

setup_sandman()
{
	self.animname = "sandman";
	level.red1 = self;
	level.sandman = self;
	self make_hero();
	self set_force_color( "red" );
	self magic_bullet_shield();
	self.dontdeleteme = true;
}

bad_place_till_deaththink()
{
	other = waittill_triggered_current();
	other endon ( "death" );
	while ( IsAlive( other ) )
	{
		BadPlace_Cylinder( other.unique_id + "bad_place_till_deaththink", 1, other.origin, 600, 600, "allies" );
		wait 1;		
	}
}

delete_on_goalthink()
{
	struct_spawner  = self.spawner.struct_spawner;
	
	if ( !IsDefined( struct_spawner ) )
		return;

	if( struct_spawner goal_think_triggered_new() )
		level notify ( "goal_think_triggered_new" );
	waittillframeend; // for array_spawn_target() let all the subsequent delete_on_goalthinks return;
	
	if ( !IsDefined( self ) )
		return;
		
	level endon ( "goal_think_triggered_new" );

	if ( !IsDefined( struct_spawner.script_drone_repeat_count ) )
		return;
	
	delete_on_goal_respawn = 0;
	if ( !IsDefined( struct_spawner.delete_on_goal_respawn ) )
	{
		struct_spawner.delete_on_goal_respawn = struct_spawner.script_drone_repeat_count;
	}
	
	if( struct_spawner.delete_on_goal_respawn == 0 )
	{
		
		struct_spawner.delete_on_goal_respawn = undefined;
		return;
	}
	struct_spawner.delete_on_goal_respawn--;
	self waittill ( "death" );
	spawner = maps\_spawner::get_spawner_from_pool( struct_spawner, 1 );
	spawner thread spawn_ai( false );
}

goal_think_triggered_new()
{
	targetingtriggers = GetEntArray( self.targetname, "target" );
	if ( targetingtriggers.size )
	{
		foreach( targettingtrigger in targetingtriggers )
			if( targettingtrigger ent_flag_exist( "new_goal_trigger") )
				return false;
			else
				targettingtrigger ent_flag_init( "new_goal_trigger" );
		return true;
	}
	
	
	
	if( ent_flag_exist( "new_goal_trigger") )
		return false;
	ent_flag_init( "new_goal_trigger" );
	return true;
}

DEATH_DELETE_FOV = 0.5; // cos(60)

drone_death_handler( deathanim )
{
	if ( !IsDefined( level.drone_bodies ) )
		level.drone_bodies = 0;
		
	level.drone_bodies++;
	
	self maps\_drone::drone_play_scripted_anim( deathanim, "deathplant" );
	
	self notsolid();
	
	self thread maps\_drone::drone_thermal_draw_disable( 2 );
	
	if( isdefined( self ) && isdefined( self.nocorpsedelete ) )
		return;

	wait 1;
	while( isdefined( self ) )
	{
		wait( 2 );
		if ( drone_should_delete() )
			self delete();
	}
	
	level.drone_bodies--;
}

drone_should_delete()
{
	if( DistanceSquared( level.player.origin, self.origin ) > 1000000 )
		return true;
	if ( !within_fov( level.player.origin, level.player.angles, self.origin, DEATH_DELETE_FOV ) )
		return true;
	if( level.drone_bodies > 5 )
		return true;
	return false;
}

brave_soul()
{
	self.suppressionwait = 0;
	self.ignoresuppression = true;
	self.disableBulletWhizbyReaction = true;
	self.disableReactionAnims = true;
	self.disableFriendlyFireReaction = true;
}

turret_attacks_target( target )
{
	if( isHelicopter() )
		return;

	self SetTurretTargetEnt( target );
	target endon ( "death" );
	while ( true )
	{
		self waittill ( "turret_on_target" );
		self FireWeapon();
		self.turretfiretimer = RandomFloatRange( 3, 4 );
		wait self.turretfiretimer;
	}
}

teleport_ai_toarray( guys, array_of_structs )
{
	Assert( array_of_structs.size > guys.size );
	
	for ( i = 0; i < guys.size; i++ )
	{
		guys[ i ] ForceTeleport( array_of_structs[ i ].origin, ( 0, 0, 0 ) );
	}
	
}

vehicle_turret_restore_old_mode()
{
	foreach( turret in self.mgturret )
		if ( IsDefined( turret.OldMode ) )
		{
			turret SetMode( turret.OldMode );
			turret.OldMode = undefined;
		}

}

spawn_pool_copy_function( struct_spawner )
{
	self.script_drone_repeat_count = struct_spawner.script_drone_repeat_count;
	//if ( IsDefined( self.script_drone_repeat_count ) )
		self.struct_spawner = struct_spawner;
}


show_me_the_drones()
{
	while( !isdefined( level.drones ) )
		wait 0.05;
	while(true)
	{
		foreach( drone in level.drones["axis"].array )
			Line( level.player.origin, drone.origin, (1,1,0) );
		wait 0.05;
	}
	
}

//---------------------------------------------------------
// Global FX Section
//---------------------------------------------------------
createfx_manager()
{
	wait( 0.1 );

	y = 12000;
	foreach ( fx in level.createFXent )
	{
		origin = fx.v[ "origin" ];
		if ( origin[ 1 ] > y )
		{
			fx pauseeffect();
		}
	}

	flag_wait( "tank_crash_exit" );

	foreach ( fx in level.createFXent )
	{
		origin = fx.v[ "origin" ];
		if ( origin[ 1 ] > y )
		{
			fx restarteffect();
		}
		else if ( origin[ 1 ] < y - 1000 )
		{
			fx pauseeffect();
		}
	}
}

// if you just putout_fires you run the risk of leaving a badplace living for 128 seconds..
putout_fires_stop_badplaces()
{
	level notify ( "putout_fires" );
	destructible_toy = array_combine( GetEntArray( "destructible_toy", "targetname" ), GetEntArray( "destructible_vehicle", "targetname" ) );
	foreach( toy in destructible_toy)
		toy notify ( "remove_badplace" );
}

PlayerLinkToDeltaBlend( blendtime, accel_time, decel_time, linkto_entity, tag, viewpercentag_fraction, right_arc, left_arc, top_arc, bottom_arc, use_tag_angles_ )
{
	if ( !IsDefined( viewpercentag_fraction ) )
		viewpercentag_fraction = 1;
	if ( !IsDefined( right_arc ) )
		right_arc = 0;
	if ( !IsDefined( left_arc ) )
		left_arc = 0;
	if ( !IsDefined( top_arc ) )
		top_arc = 0;
	if ( !IsDefined( bottom_arc ) )
		bottom_arc = 0;
	if ( !IsDefined( use_tag_angles_ ) )
		use_tag_angles_ = true;
	
	self PlayerLinkToBlend( linkto_entity, tag, blendtime, accel_time, decel_time );
	self delaycall( blendtime, ::PlaYerLinkToDelta, linkto_entity, tag, viewpercentag_fraction, right_arc, left_arc, top_arc, bottom_arc, use_tag_angles_);

}

// SPOTLIGHT STUFF BORROWED FROM LONDON

spot_light( fxname, cheapfx, tag_name, death_ent )
{
    if ( IsDefined( level.last_spot_light ) )
    {
        struct = level.last_spot_light;
        // stop the spotlight shadowmap version
        if ( IsDefined( struct.entity ) )
        {
	        StopFXOnTag( struct.effect_id, struct.entity, struct.tag_name );
	        // start the low budget version
	        if ( IsDefined( struct.cheap_effect_id ) )
	          PlayFXOnTag( struct.cheap_effect_id, struct.entity, struct.tag_name );
        }
        wait 0.2;
    }

	level notify( "spotlight_changed_owner" );
	waitframe();
    struct = SpawnStruct();
    struct.effect_id = getfx( fxname );
    if ( isdefined( cheapfx ) )
    	struct.cheap_effect_id = getfx( cheapfx );
    struct.entity = self;
    struct.tag_name = tag_name;
    
    PlayFXOnTag( struct.effect_id, struct.entity, struct.tag_name );
    
    if ( IsDefined( death_ent ) )
    {
        thread spot_light_death( death_ent );
        
    }
    level.last_spot_light = struct;
}

stop_last_spot_light()
{
	if ( IsDefined( level.last_spot_light ) )
	{
		struct = level.last_spot_light;
		// stop the spotlight shadowmap version
		StopFXOnTag( struct.effect_id, struct.entity, struct.tag_name );
		level.last_spot_light = undefined;
	}
}

spot_light_death( death_ent )
{
    self notify ( "new_spot_light_death" );
    self endon ( "new_spot_light_death" );
    self endon ( "death" );
    death_ent waittill ( "death" );
    self Delete();
}

pauseeffectsByID( id )
{
	fx = getfxarraybyid( id );
	array_thread( fx, ::pauseEffect );
	
}

radio_dialog_add_and_go( alias,timeout )
{
	radio_add( alias );
	radio_dialogue( alias,timeout );
}



maingun_FX_hamburg()
{
	model = self.model;
	if ( !IsDefined( level.vehicle_deckdust[ model ] ) )
		return;
	self endon( "death" );
	
	while ( true )
	{
		self waittill( "weapon_fired" ); // waits for Code notify when FireWeapon() is called.
		if ( DistanceSquared( level.player.origin, self.origin ) > 1690000 )
			continue;
		PlayFXOnTag( level.vehicle_deckdust[ model ], self, "tag_engine_exhaust" );
		barrel_origin = self GetTagOrigin( "tag_flash" );
		ground = PhysicsTrace( barrel_origin, barrel_origin + ( 0, 0, -128 ) );
		PhysicsExplosionSphere( ground, 192, 100, 1 );
	}
}

turn_on_the_tanks_lights()
{
	effect_id = getfx( "hamburg_tank_red_light" );
	
	if( !ent_flag_exist( "lights_in_tank" ) )
	{
		ent_flag_init( "lights_in_tank" );
		ent_flag_set( "lights_in_tank" );
	}
	else
	{
		if( ent_flag( "lights_in_tank" ) )
			return;
	}
	
	PlayFXOnTag( effect_id, self, "tag_interior_light_1" );
	wait 0.05;
	PlayFXOnTag( effect_id, self, "tag_interior_light_2" );
//	wait 0.05;
//	PlayFXOnTag( effect_id, self, "tag_interior_light_3" );

	wait 0.05;
	effect_id = getfx( "hamburg_garage_godray_small" );
	PlayFXOnTag( effect_id, self, "tag_interior_light_godray" );
}


turn_off_the_tanks_lights( onlygodray )
{
	effect_id = getfx( "hamburg_tank_red_light" );
	
	if( !ent_flag_exist( "lights_in_tank" ) || !ent_flag( "lights_in_tank" ) )
		return;
		
	ent_flag_clear( "lights_in_tank" );
	
	if ( !IsDefined( onlygodray ) )
	{
		StopFXOnTag( effect_id, self, "tag_interior_light_1" );
		StopFXOnTag( effect_id, self, "tag_interior_light_2" );
	}
//	StopFXOnTag( effect_id, self, "tag_interior_light_3" );

	effect_id = getfx( "hamburg_garage_godray_small" );
	StopFXOnTag( effect_id, self, "tag_interior_light_godray" );
	
}

turn_on_interior_light()
{
	if( isdefined( level.garage_crash_light_exit ) )
		level.garage_crash_light_exit notify ( "stop_handler" );

	thread turn_on_the_tanks_lights();	
	wait 0.1;
	//exploder( "inside_the_tank_fire" );
	
	garage_crash_light_in_tank = getstruct( "garage_crash_light_in_tank", "targetname" );
	garage_crash_light_in_tank_target = getstruct( garage_crash_light_in_tank.target, "targetname" );
	garage_crash_light_in_tank.angles = vectortoangles( garage_crash_light_in_tank_target.origin - garage_crash_light_in_tank.origin );
	angles = garage_crash_light_in_tank.angles;

	
	
	emitter = garage_crash_light_in_tank spawn_tag_origin();
	emitter.angles = angles;
	
	//this is just the bits around it
	//PlayFX( getfx( "hamburg_garage_godray_small" ), emitter.origin, anglestoforward(angles), anglestoup( angles ));

	//this is the real light that is abreviated
	emitter thread spot_light( "hamburg_garage_godray_small_light", undefined , "tag_origin", emitter );
	
	//PlayFXOnTag( getfx( "hamburg_garage_godray_small" ), emitter, "tag_origin" );
	level.garage_crash_light_in_tank = emitter;

	
}

stop_rumble_on_tank()
{
	self notify ( "kill_rumble_forever" );
	self StopRumble( "tank_rumble" );
}

