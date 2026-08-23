#include maps\_utility;
#include maps\_hud_util;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;
#include maps\hamburg_code;
#include maps\hamburg_garage_code;
#include maps\hamburg_tank_ai;
#include maps\hamburg_a_to_b;

//ORIGIN_ZERO = ( 0, 0, 0 );

//---------------------------------------------------------
// Garage Entrance Section
//---------------------------------------------------------

garage_entrance()
{
	init_garage();
	
	level thread new_garage_dialogue();

	set_ambient( "hamburg_tankgun_garage" );


	if( level.start_point == "hamburg_garage" )
	{
		level.hero_tank do_path_section( "tank_track_garage_entrance_hero" );
		level.player_tank do_path_section( "tank_track_garage_entrance_player" );
	}

	entrance_area();

	flag_set( "in_garage" );
	
	level.hero_tank stop_rumble_on_tank();
	
	both_tank_flag_wait( "start_garage_combat" );
}

new_garage_dialogue()
{
	thread radio_dialog_add_and_go( "tank_rh2_showontheroad" );
	thread radio_dialog_add_and_go( "tank_rh1_movefast" );
	level.player_tank ent_flag_wait( "pushback2" );
	wait( 1 );
	thread radio_dialog_add_and_go( "tank_rh2_holdon" );
	wait( 2.4 );
	thread radio_dialog_add_and_go( "tank_rh2_rightthere" );
	
	flag_wait( "rondevu_start" );
	
	thread radio_dialog_add_and_go( "tank_rh1_sawanother" );
	wait( 3 );
	thread radio_dialog_add_and_go( "tank_rh2_afteryou" );
	
	flag_wait( "start_garage_ramp" );
	wait( 12 );
	thread radio_dialog_add_and_go( "tank_rh1_woahwoahwait" );
	wait( 3 );
	thread radio_dialog_add_and_go( "tank_rh2_backitup" );
	wait( 4.6 );
	thread radio_dialog_add_and_go( "hamburg_rhg_ohshit" );
	
	
	
}

init_garage()
{
	if ( IsDefined( level.init_garage ) ) 
	{
		return;
	}

	level.init_garage = true;

	init_spawn_funcs();
	init_garage_flags();
	init_tanks();
	
	//Rhino 1: Let's move in.
	thread radio_dialog_add_and_go( "tank_rh1_letsmovein" );
	//Rhino 1: Take it slow…
	//thread radio_dialog_add_and_go( "tank_rh1_takeitslow" );
	//Rhino 1: They ran further down in to the garage.
	thread radio_dialog_add_and_go( "tank_rh1_fartherdownin" );


//	divider = GetEnt( "garage_divider", "targetname" );
//	divider ConnectPaths();

	thread ai_goalvolume_thread( "player_tank_goalvolume_start", level.player_tank );

	thread delayed_init_garage();
	thread tank_monster_clip();
}

delayed_init_garage()
{
	flag_wait( "start_garage_section" );
	thread trim_fires();
	wait 0.05;
	cleanup_ents_passive( "pre_garage_vehicles" );
	wait 0.05;
	thread cleanup_bridge_and_before_garage_area();
}

trim_fires()
{
	for ( i = 0; i < 10; i++ )
	{
		wait 5;
		putout_fires_stop_badplaces();
	}
	
}

init_spawn_funcs()
{
	array_spawn_function_noteworthy( "player_tank_garage_spawner", ::postspawn_player_tank_garage_ai );
	array_spawn_function_noteworthy( "rpg_vehicle", 			 	::postspawn_rpg_vehicle );
}

init_garage_flags()
{
}


init_tanks()
{
	tanks = [ level.hero_tank, level.player_tank ];

	level.hero_tank init_tank_path_flags( "tank_track_garage_entrance_hero" );
//	level.hero_tank init_tank_path_flags( "hero_reverse_garage_path" );
//	level.hero_tank init_tank_path_flags( "hero_forward_garage_path" );

	level.player_tank init_tank_path_flags( "tank_track_garage_entrance_player" );

	// Set tanks to no shoot close range
	level.player_tank.target_min_range = 1000;
	level.hero_tank.target_min_range = 700;

	foreach ( tank in tanks )
	{
		tank set_tank_damage( 300, 1200, 50 );
		tank thread tank_garage_thread();
		tank.script_badplace = false;
	}
}

init_tank_path_flags( path )
{
	node = GetVehicleNode( path, "targetname" );
	while ( 1 )
	{
		if ( IsDefined( node.script_ent_flag_wait ) )
		{
			self init_ent_flag( node.script_ent_flag_wait );
		}

		if ( IsDefined( node.script_ent_flag_set ) )
		{
			self init_ent_flag( node.script_ent_flag_set );
		}

		if ( IsDefined( node.script_flag_wait ) )
		{
			init_level_flag( node.script_flag_wait );
		}

		if ( IsDefined( node.script_flag_set ) )
		{
			init_level_flag( node.script_flag_set );
		}

		// Look for color triggers then add a fake noteworthy
		// so we can get a notify when hit
		ent = GetEnt( node.targetname, "target" );
		if ( IsDefined( ent ) )
		{
			if ( ent.code_classname == "trigger_radius" )
			{
				if ( IsDefined( ent.script_color_allies ) )
				{
					node thread tank_color_thread( ent );
				}
			}
		}

		if ( !IsDefined( node.target ) )
		{
			break;
		}

		node = GetVehicleNode( node.target, "targetname" );
	}
}

init_ent_flag( f )
{
	if ( !self ent_flag_exist( f ) )
	{
		self ent_flag_init( f );
	}
}

init_level_flag( f )
{
	if ( !flag_exist( f ) )
	{
		flag_init( f );
	}
}

tank_color_thread( trigger )
{
	self waittill( "trigger" );
	trigger activate_trigger();
}

tank_garage_thread()
{
	self endon( "stop_tank_garage_thread" );

	while ( 1 )
	{
		self waittill( "noteworthy", note );
		node = self.currentnode;

		if ( note == "fire_rpg" )
		{
			rpg = GetEnt( node.target, "targetname" );
			rpg spawn_rpg_vehicle();
		}
		else if ( note == "turret_attack" )
		{
			self thread turret_attack_think_hamburg();
		}
		else if ( note == "stop_turret_attack" )
		{
			self thread stop_turret_attack_think_hamburg();
		}
		else if ( note == "turret_attack_rpgers" )
		{
//			self thread turret_attack_rpgers();
		}
		else if ( note == "spawn_gaz" )
		{
			self thread garage_ramp_spawn_gaz();
		}
		else if ( note == "enable_badplace" )
		{
			self.script_badplace = true;
		}
		else if ( note == "disable_badplace" )
		{
			self.script_badplace = false;
		}
	}
}

//turret_attack_rpgers()
//{
//	struct = getstruct( "rpgers_target", "targetname" );
//	self SetTurretTargetVec( struct.origin );
//
//	self waittill( "turret_on_target" );
//
//	self FireWeapon();
//	self update_turret_fire_timer();
//
//	self thread turret_attack_think_hamburg();	
//}

garage_ramp_spawn_gaz()
{
	spawn_vehicles_from_targetname_and_drive( "garage_ramp_gaz" );
	self thread turret_attack_think_hamburg();
}

entrance_area()
{
	activate_trigger_with_targetname( "start_garage_colors" );
	
// TESTING
///#
//	if ( GetDvarInt( "test_hero_path" ) > 0 )
//	{
//		wait( 0.5 );
//		spawners = GetSpawnerArray();
//		array_call( spawners, ::Delete );
//	}
//#/

	entrance_recon();
	autosave_by_name( "garage_entrance" );
}

entrance_recon()
{
	flag_wait( "garage_recon" );

//	time = 10;

//	if ( GetDvarInt( "test_hero_path" ) > 0 )
//	{
//		time = 2;
//	}

	activate_trigger_with_targetname( "garage_infantry_enter" );
	wait( 1 );
	flag_set( "start_garage_section" );
}

pre_load()
{
	maps\hamburg_garage_anim::main();

	PrecacheModel( "projectile_rpg7" );
}

//---------------------------------------------------------
// Garage Combat Section
//---------------------------------------------------------
garage_combat_area()
{
	init_garage();

	if ( level.start_point == "hamburg_garage_post_entrance" )
	{
		level.player_tank do_path_section( "tank_track_garage_two_player", true );
		level.hero_tank do_path_section( "tank_track_garage_two_hero", true );

		wait( 1 );

		level.player_tank stop_turret_attack_think_hamburg();
		level.hero_tank stop_turret_attack_think_hamburg();

//		both_tank_flag_wait( "start_garage_combat" );
	}

//	flag_wait( "garage_rpg_attack" );

//	rpg_attack();

//	level.hero_tank ent_flag_set( "garage_smoke" );
//	wait( 3 );

//	flag_set( "ram_office" );
	thread ram_office();
	
//	stage_friendly_for_ambush = getvehiclenode( "stage_friendly_for_ambush", "script_noteworthy" );
//	stage_friendly_for_ambush waittill ( "trigger" );
	
//	level.hero_tank stop_turret_attack_think_hamburg();
//	cannon_target_aim_sequence = getstruct( "cannon_target_aim_sequence", "script_noteworthy" );
//	level.hero_tank SetTurretTargetVec( cannon_target_aim_sequence.origin );

//	hero_wait();

	flag_wait( "garage_send_infantry" );
	thread garage_rondevu_infantry();

	flag_wait( "garage_rpgers_flanked" );
	goal_volume = GetEnt( "garage_last_volume", "script_noteworthy" );
	ai = goal_volume get_ai_touching_volume( "axis" );

	if ( IsDefined( ai ) )
	{
		array_thread( ai, ::ai_set_goalvolume, goal_volume );
	}
}

garage_rondevu_infantry()
{
//	divider = GetEnt( "garage_divider", "targetname" );
//	divider DisconnectPaths();

//	level.hero_tank.script_badplace = false;
//	red = get_force_color_guys( "allies", "r" );
//	red = array_remove( red, level.sandman );

//	structs = getstructarray( "rondevu_red_start", "targetname" );
//	foreach ( idx, guy in red )
//	{
//		guy thread garage_rondevu_thread( structs[ idx ] );
//	}

//	orange = get_force_color_guys( "allies", "o" );

//	structs = getstructarray( "rondevu_orange_start", "targetname" );
//	foreach ( idx, guy in orange )
//	{
//		guy thread garage_rondevu_thread( structs[ idx ] );
//	}
}

garage_rondevu_thread( struct )
{
	self ForceTeleport( struct.origin, struct.angles );
	self thread maps\_spawner::go_to_struct( struct );
}

ram_office()
{
	level.player_tank.script_badplace = false;
	level.player_tank stop_turret_attack_think_hamburg();
	level.player_tank thread turret_reset();
//	thread print_tank_pos_thread();

	thread tank_move_car();

	triggers = GetEntArray( "garage_office_exploder_trigger", "targetname" );
	array_thread( triggers, ::office_exploders );
//
//	trigger = GetEnt( "garage_office_trigger", "targetname" );
//	trigger waittill( "trigger" );
//	thread office_debris( 1 );
//
//	trigger = GetEnt( "garage_office_trigger2", "targetname" );
//	trigger waittill( "trigger" );
//	thread office_debris( 2 );
}

office_exploders( num )
{
	self waittill( "trigger" );
	
	putout_fires_stop_badplaces();
	
	num = self.script_index;

	exploder_name = "garage_office_exploder" + num;
	exploder( exploder_name );

	debris = GetEntArray( exploder_name, "targetname" );
	array_delete( debris );

	glass_array = GetGlassArray( "garage_office_glass" + num );
	force = AnglesToForward( ( 0, 90, 0 ) ) * 20;
	foreach ( glass in glass_array )
	{
		DestroyGlass( glass, force );
	}

	barriers = GetEntArray( "garage_office_barrier" + num, "targetname" );
	foreach ( barrier in barriers )
	{
		barrier.origin = barrier.origin + ( 0, 0, 5 );
		yaw = RandomFloatRange( 80, 100 );
		power = AnglesToForward( ( -30, yaw, 0 ) ) * RandomFloatRange( 2500, 5000 );

		x = RandomFloatRange( -5, 5 );
		y = RandomFloatRange( -5, 5 );
		z = RandomFloatRange( -5, 5 );
		origin = barrier.origin + ( x, y, z );
		barrier PhysicsLaunchClient( origin, power );
	}

	self Delete();
}

tank_move_car()
{
	ents = GetEntArray( "tank_move_car", "script_noteworthy" );
	clip = undefined;
	car = undefined;
	foreach ( ent in ents )
	{
		if ( ent.classname == "script_brushmodel" )
		{
			clip = ent;
		}
		else
		{
			car = ent;
		}
	}

	clip LinkTo( car );
	struct = getstruct( "tank_move_car_resting_position", "targetname" );

	trigger_wait_targetname( "tank_move_car" );

	car.animname = "tank_move_car";
	car assign_animtree();

	rock_anim = car getanim( "rock" );
	flat_tire_anim = car getanim( "flat_tire" );
	root_anim = car getanim( "root" );

	car SetAnimRestart( rock_anim, 1 );
	car delaycall( 0.5, ::ClearAnim, root_anim, 0.5 );

	car DoDamage( 5000, car.origin );
	clip DisconnectPaths();

	time = 1;
	car MoveTo( struct.origin, time, 0, 0.2 );
	car RotateTo( struct.angles, time * 0.25 );

	wait( time );
	clip ConnectPaths();
}

print_tank_pos_thread()
{
/#
	write_map_header();

	origin = level.player_tank.origin;
	angles = level.player_tank.angles;
	write_tank_struct( origin, angles );

	dist = 300 * 300;
	while ( !flag( "garage_rpgers_flanked" ) )
	{
		wait( 0.05 );
		if ( DistanceSquared( origin, level.player_tank.origin ) < dist )
		{
			continue;
		}

		origin = level.player_tank.origin;
		angles = level.player_tank.angles;
		write_tank_struct( origin, angles );
	}

	saved = CloseFile( level.tank_pos_file );
	println( "FILE IS SAVED!" );
#/
}

write_map_header()
{
/#
	level.tank_pos_file = OpenFile( "scriptgen/hamburg_tank_pos.map", "write" );
	level.tank_struct_num = 1;

	write_map_line( "iwmap 9" );
	write_map_line( "layers" );
	write_map_line( "{" );
	write_map_line( "    \"The Map\"" );
	write_map_line( "    \"000_Global\" flags active" );
	write_map_line( "}" );
	write_map_line( "cameraPresets" );
	write_map_line( "{" );
	write_map_line( "    origin 0 20 46 angles 0 0 0" );
	write_map_line( "    origin 0 20 46 angles 0 0 0" );
	write_map_line( "    origin 0 20 46 angles 0 0 0" );
	write_map_line( "    origin 0 20 46 angles 0 0 0" );
	write_map_line( "    origin 0 20 46 angles 0 0 0" );
	write_map_line( "}" );
	write_map_line( "entity 0 intruder 1" );
	write_map_line( "{" );
	write_map_line( "    \"classname\" \"worldspawn\"" );
	write_map_line( "}" );
#/
}

write_tank_struct( origin, angles )
{
/#
	target = "tank_print" + level.tank_struct_num;
	targetname = "tank_print" + ( level.tank_struct_num - 1 );
	write_map_line( "entity " + level.tank_struct_num + " intruder 2" );
	write_map_line( "{" );
	write_map_line( "    \"origin\" \"" + origin[ 0 ] + " " + origin[ 1 ] + " " + origin[ 2 ] + "\"" );
	write_map_line( "    \"angles\" \"" + angles[ 0 ] + " " + angles[ 1 ] + " " + angles[ 2 ] + "\"" );
	write_map_line( "    \"model\" \"vehicle_m1a1_abrams_minigun\"" );
	write_map_line( "    \"classname\" \"script_struct\"" );
	write_map_line( "    \"target\" \"" + target + "\"" );
	write_map_line( "    \"targetname\" \"" + targetname + "\"" );
	write_map_line( "}" );

	level.tank_struct_num++;
#/
}

write_map_line( str )
{
/#
	fprintln( level.tank_pos_file, str );
#/
}

rpg_attack()
{
	level thread hero_tank_rpg_attack();

	rpgs = GetEntArray( "garage_rpg", "targetname" );
	rpgs = array_randomize( rpgs );

	foreach ( rpg in rpgs )
	{
		rpg spawn_vehicle_and_gopath();
		wait( RandomFloatRange( 0.7, 1.2 ) );
	}
}

hero_tank_rpg_attack()
{
	while ( level.hero_tank.veh_speed > 0 )
	{
		wait( 0.05 );
	}

	wait( 0.5 );

	// FALL BACK!!!
	level.hero_tank ent_flag_set( "garage_smoke" );

//	println( "hero tank origin = ", level.hero_tank.origin );
	level.hero_tank.veh_transmission = "reverse";
	level.hero_tank vehicle_wheels_backward();

	node = GetVehicleNode( "hero_reverse_garage_path", "targetname" );
	level.hero_tank AttachPath( node );
	level.hero_tank StartPath();
	level.hero_tank thread vehicle_paths( node );
	level.hero_tank ResumeSpeed( 10 );

	level.hero_tank waittill( "reached_end_node" );

	level.hero_tank.veh_transmission = "forward";
	level.hero_tank vehicle_wheels_forward();

	node = GetVehicleNode( "hero_forward_garage_path", "targetname" );
	level.hero_tank AttachPath( node );
	level.hero_tank StartPath();
	level.hero_tank thread vehicle_paths( node );
	level.hero_tank ResumeSpeed( 10 );
}

garage_pre_ramp()
{
	init_garage();

	if ( level.start_point == "hamburg_garage_pre_ramp" )
	{
		level.player_tank do_path_section( "tank_track_garage_three_player", true );
		level.hero_tank do_path_section( "friendly_tank_ambush", true );
	}

	flag_wait( "rondevu_start" );
	wait( 5 );
	
	clear_hallway_volume = GetEnt( "clear_hallway_volume", "targetname" );
	while( clear_hallway_volume get_ai_touching_volume( "allies" ).size )
		wait 0.1;

	flag_set( "rondevu_done" );
}

garage_ramp()
{
	init_garage();
	if ( level.start_point == "hamburg_garage_ramp" )
	{
		level.player_tank do_path_section( "tank_track_garage_ramp_player", true );
		level.hero_tank do_path_section( "tank_track_garage_ramp_hero", true );
		wait( 1 ); // Let stuff initialize
	}
	
	

	level.player delayThread( 5, ::play_sound_on_entity, "bridge_creaking" );
	scene_org = getstruct( "tank_crash_org", "targetname" );
	spawn_garage_rig();
	
	level.hero_tank thread concrete_cracks( "start_garage_ramp" );
	
	flag_wait( "prep_garage_ramp" );

	level.player_tank stop_turret_attack_think_hamburg();
	level.hero_tank stop_turret_attack_think_hamburg();
	ramp_aim_struct = getstruct( "ramp_aim_struct", "targetname" );
	level.player_tank SetTurretTargetVec( ramp_aim_struct.origin );
	level.hero_tank SetTurretTargetVec( ramp_aim_struct.origin );
	
	thread battlechatter_off( "allies" );

	flag_wait( "ramp_crash" );
	//level.player_tank notify ( "suspend_drive_anims" );
		
	dummy = level.player_tank vehicle_to_dummy();
	level.player_tank thread vehicle_scripts\_m1a1_player_control::set_dummy_to_my_angles();
	level notify ( "stop_concrete_cracks" );

	explode_the_ramps();
	
	dummy Unlink();
	dummy.origin = level.player_tank.body_referenced_junk.origin;
	dummy.angles = level.player_tank.body_referenced_junk.angles;
	//dummy SetModel( "vehicle_m1a1_abrams_viewmodel_tread_stop" );

	level.player_tank vehicle_scripts\_m1a1_player_control::tank_unmount_player();
	
	// bump up player a little to mask arms poping in, Earthquake to hide pop
	Earthquake( 0.7, 1.8,  level.player.origin, 2000 );
	level.player SetOrigin( level.player.origin + ( 0, 0, 44 ) );
	player_angles = set_x( level.player GetPlayerAngles(), -14 );
	level.player SetPlayerAngles( player_angles );
	
	minigun = level.player_tank.turret_mini;
	minigun Hide();
	//minigun delete();
	level.player takeallweapons();
	
	set_stance_for_crash_anims();
	
	//thread earthquake_for_a_bit();
	
	rig = level.garage_rig;	
	rig thread gather_linkables();
	
	tag = "tag_turret_mg_r";
	anim_model = spawn_anim_model( "m1a1_player_hands", level.player_tank GetTagOrigin( tag ) );
	gun_model = spawn_anim_model( "m1a1_player_minigun" );

	guys = [ gun_model, anim_model ];
	
	dummy anim_teleport( guys, "crash_bump", tag );
	dummy anim_first_frame( guys, "crash_bump", tag );
	anim_model LinkTo( dummy, tag);
	gun_model LinkTo( dummy, tag);

	movetime = 0.2; // I'm pretty close;
	dummy.animname = "post_crash_tank";

	//scene_org anim_moveto( [ dummy ], "hamburg_tank_crash", undefined, movetime, 0, 0 );
	
	level.player thread play_sound_on_entity( "hamburg_garage_collapse" );
	
	//level.player playerlinktodelta( anim_model, "tag_player", 1, 180, 180, 180, 180, false );
	
	//wait movetime;

	dummy thread anim_single( [ gun_model, anim_model ], "crash_bump", tag );
	rig SetAnim( rig getanim( "collapse" ) , 1  );
	thread do_tank_crash_for_garage( scene_org, dummy );	
	thread tank_crash_sounds( rig, rig getanim( "collapse" ) );
	level.post_crash_tank = level.player_tank.modeldummy;
	level.player_tank.modeldummyon = false;
	level.player_tank.modeldummy = undefined;
	level.post_crash_tank notify ( "stop_model_dummy_death" ); 
	
	level.player PlayerLinkToDeltaBlend( 0.7, 0, 0, anim_model, "tag_player", 1, 5, 5, 5, 5, true );
 	
	level waittill ( "do_tank_crash_for_garage" );
	
	thread cleanup_pre_gun_anim_model_thing( anim_model, gun_model, scene_org );
	level.hero_tank delete();
	level.player_tank delete();
	
	maps\hamburg_a_to_b::tank_crash_exit();
}

cleanup_pre_gun_anim_model_thing( anim_model, gun_model, scene_org )
{
	scene_org waittill ( "hamburg_tank_crash" );
	anim_model Delete();
	gun_model delete();
}

do_tank_crash_for_garage( scene_org, dummy )
{
	// kill the fires on destructibles
	putout_fires_stop_badplaces();
	
	scene_org thread anim_single_solo( dummy, "hamburg_tank_crash" );
	anim_time = getanimlength( dummy getanim( "hamburg_tank_crash" ) );
	foreach( rider in level.player_tank.riders )
		rider Delete();
	
	delaythread( 4, maps\hamburg_a_to_b::turn_on_exterior_light );
	wait 8.7;
	
	level.player ShellShock( "hamburg_garage_crash", 4 );
	level.player LerpFOV( 65, 1 );
	Earthquake( 0.6, 2.3, level.player GetEye() + ( 0, 0, -64 ), 200 );
	dummy Hide();
	thread maps\hamburg_a_to_b::do_idle_guys_in_tank( dummy );
	dummy thread  turn_on_interior_light();
	thread vision_set_fog_changes( "hamburg_garage_inside_tank", 0.1 );
	level notify ("do_tank_crash_for_garage");
}

tank_crash_sounds( rig, anime )
{
	while ( rig getAnimTime( anime ) < 0.46 )
		wait( 0.05 );
	
	org = rig GetTagOrigin( "j_vehicle_4" );
	thread play_sound_in_space( "scn_hamburg_tank_crash_car1", org );

	while ( rig getAnimTime( anime ) < 0.57 )
		wait( 0.05 );
	
	org = rig GetTagOrigin( "j_vehicle_2" );
	thread play_sound_in_space( "scn_hamburg_tank_crash_car2", org );
	
	while ( rig getAnimTime( anime ) < 0.84 )
		wait( 0.05 );
	
	org = rig GetTagOrigin( "j_vehicle_5" );
	thread play_sound_in_space( "scn_hamburg_tank_crash_car3", org );
}

common_garage_player_on_tank()
{
	maps\_compass::setupMiniMap( "compass_map_hamburg", "city_minimap_corner" );
	struct = getstruct( "hamburg_garage_start_point", "script_noteworthy" );
	maps\hamburg_landing_zone::do_on_foot_start( struct );
	thread put_player_on_tank();
}

