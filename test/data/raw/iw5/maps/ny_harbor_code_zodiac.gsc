#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;
#include maps\_audio;
#include maps\ny_harbor_code_sdv;
#include maps\ny_harbor_code_sub;
#include maps\ny_harbor_code_vo;
#include maps\ny_hind;
#include maps\ny_hind_ai;
#include maps\_gameevents;
#include maps\_helicopter_globals;
#include maps\_audio_music;
#include maps\_shg_common;
#include maps\_hud_util;


CONST_MPHTOIPS = 17.6;
CONST_ZODIAC_WHEEL_OFF = -6.0;

dump_entities()
{
	entities = getentarray();
	foreach (ent in entities)
	{
		id = ent GetEntityNumber();
		classname = "";
		if (isdefined(ent.classname))
			classname = ent.classname;
		origin = ent.origin;
		model = "";
		if (isdefined(ent.model))
			model = ent.model;
		targetname = "";
		if (isdefined(ent.targetname))
			targetname = ent.targetname;
		println(id + " : " + classname + ", " + model + ", " + targetname + ", (" + origin[0] + "," + origin[1] + ", " + origin[2] + ")" );
	}
}

////***********************************************************************
//  Zodiac stuff

displace_zodiac_collision( positions, angles )
{
	extra_displacement = 0;
	if (isdefined(self.displacement))
		extra_displacement = self.displacement;
	displacement_scale = 1.0;
	if (isdefined(self.displacement_scale))
		displacement_scale = self.displacement_scale;
	
	for (i=0; i<4; i++)
	{
		position = positions[i];
		displacement = 0;
		if (displacement_scale > 0)
		{
			current_patch = self.current_patch;
			if (!isdefined(current_patch))
				current_patch = level.escape_zodiac.current_patch;
			if (isdefined(current_patch))
				displacement = maps\_ocean::GetDisplacementForVertex( level.oceantextures[current_patch], position );
			displacement *= displacement_scale;
		}
		displacement += extra_displacement + self.zodiac_zoff;
		z = level.water_z + displacement;
		if (isdefined(self.zodiac_wheel_blend))
		{	// use the wheel of the zodiac as another reference to blend
			wheel_z = position[2];
			if (isdefined(self.zodiac_wheel_offset))
			{
				wheel_z += self.zodiac_wheel_offset;
			}
			blend = self.zodiac_wheel_blend;
			z = z*(1-blend) + wheel_z*blend;
		}
		origin = (position[0], position[1], z);
		self.zodiac_coll[i].origin = origin;
		self.zodiac_coll[i].angles = (0,angles[1]+60,0);
	}
}

displace_zodiac()
{
	CONST_WHEEL_TAGS = [ "tag_wheel_front_left", "tag_wheel_front_right", "tag_wheel_back_left", "tag_wheel_back_right" ];
	self endon("death");
	for (i=0; i<4; i++)
	{
		self.zodiac_coll[i] Hide();		// they start out visible for debugging
		if (isdefined(level.zodiac_colls))
			level.zodiac_colls[level.zodiac_colls.size] = self.zodiac_coll[i];
		else
			level.zodiac_colls[0] = self.zodiac_coll[i];
	}
	while (true)
	{
		if (!isdefined(self.manual_displace))
		{
			angles = self.angles;
			vel = 0.0 * (self Vehicle_GetVelocity());
			positions = [];
			for (i=0; i<4; i++)
			{
				positions[i] = (self GetTagOrigin( CONST_WHEEL_TAGS[i] )) + vel;
			}
			self displace_zodiac_collision( positions, angles );
		}
		wait 0.05;
	}
}

displace_zodiac_collision_at_position( position )
{
	CONST_WHEEL_TAGS = [ "tag_wheel_front_left", "tag_wheel_front_right", "tag_wheel_back_left", "tag_wheel_back_right" ];
	delta = position - self.origin;
	positions = [];
	angles = self.angles;
	for (i=0; i<4; i++)
	{
		positions[i] = delta + self GetTagOrigin( CONST_WHEEL_TAGS[i] );
	}
	self displace_zodiac_collision( positions, angles );
}

track_water_patch( targetnames, zoff )
{
	self endon("death");
	patches = [];
	foreach (targetname in targetnames)
	{
		patches[targetname] = getent( targetname, "targetname" );
		patches[targetname] Hide();	// start with all hidden
	}
	if (!isdefined(self.current_patch))
		self.current_patch = targetnames[0];
	/*
	current_patch = self.current_patch;
	patches[self.current_patch] Show();
	while (!flag("start_exit_path"))
	{
		if (current_patch != self.current_patch)
		{
			patches[current_patch] Hide();
			patches[self.current_patch] Show();
			current_patch = self.current_patch;
		}
		if (isdefined(current_patch))
		{
			origin = ( self.origin[0], self.origin[1], level.water_z + zoff );
			patches[current_patch].origin = origin;
		}
		wait 0.05;
	}
	foreach (patch in patches)
		patch Hide();
	*/
}

test_water_patch_switch()
{
	level.player endon("death");
	patchnames = [ "water_patch", "water_patch_med", "water_patch_calm" ];
	patchidx = 0;
	while (true)
	{
		while (!level.player usebuttonpressed())
			wait 0.05;
		while (level.player usebuttonpressed())
			wait 0.05;
		patchidx++;
		if (patchidx >= patchnames.size)
			patchidx = 0;
		self.current_patch = patchnames[patchidx];
		level.player SetWaterSheeting( 1, 0.5 );
	}
}

zodiac_setup( zoff, colltgt )
{
	self.zodiac_coll[0] = getent( colltgt+"a", "targetname");
	self.zodiac_coll[1] = getent( colltgt+"b", "targetname");
	self.zodiac_coll[2] = getent( colltgt+"c", "targetname");
	self.zodiac_coll[3] = getent( colltgt+"d", "targetname");
	self.zodiac_zoff = zoff;
	self vehphys_clearautodisable();	// don't turn off physics even if we aren't moving
	self thread zodiac_treadfx();
	self thread zodiac_physics();
	self thread vehicle_scripts\_zodiac_drive::drive_vehicle( true, true );	// noprice == true, noshoot == true
	self thread displace_zodiac( );
	wait 0.05;
	self Vehicle_teleport((self.origin[0], self.origin[1], self.zodiac_coll[0].origin[2] + 24), self.angles );
	/#
	//self thread test_water_patch_switch(); // commenting out for now, have ideas for tuning and reload is triggering this
	#/
}

hold_zodiac_in_place()
{
	start_origin = self.origin;
	start_yaw = self.angles[1];
	while (!flag( "get_on_zodiac" ))
	{
	    origin = (start_origin[0], start_origin[1], self.origin[2]);
	    angles = (self.angles[0], start_yaw, self.angles[2]);
	    self Vehicle_Teleport( origin, angles );
		wait 0.05;
	}
}

wait_to_get_on_zodiac()
{
	wait 0.5;	// this wait is for the debug start
	thread vo_zodiac_ride();
	thread sky_battle();
	thread setup_boat_destruction();
	thread sub_deck_fail();	//if player lingers we'll kill him with a hind
	
//	level.escape_zodiac2 hide();
	//thread show_carrier(); //carrier is hidden at start, show it here
	zoff = -36;
	set_water_sheating_time( "bump_small_start", "bump_big_start" );
	patchnames = [ "water_patch", "water_patch_med", "water_patch_calm" ];
	level.escape_zodiac thread zodiac_setup( zoff, "zodiac_collision_");
	level.ally_zodiac thread zodiac_setup( -60, "zodiac2_collision_" );	// we put it lower to look like it is in the water
	level.ally_zodiac.displacement = 10;	// raise it before we're on our zodiac so water doesn't clip
	level.escape_zodiac.current_patch = "water_patch_med"; // match the starting water
	
	setup_ally_zodiac();
	
	flag_wait("start_zodiac");
	
	lines = [];
//	lines[lines.size] = "nyharbor_lns_thisway";
	//lines[lines.size] = "nyharbor_lns_letsmove2";
	lines[lines.size] = "nyharbor_lns_gogo";
	
	//thread dialogue_reminder( level.sandman, "player_on_boat", lines, 3, 7 );
	
	//level.truck show();
	//level.grinch show();
	
	maps\ny_harbor::SetAbovewaterCharLighting();
	thread put_sandman_on_zodiac_waving();

	level.escape_zodiac thread hold_zodiac_in_place();

	flag_wait( "get_on_zodiac" );	// wait until player hits trigger to play get on zodiac anim
	aud_send_msg("aud_zodiac_slide_se");
	
	thread keep_dying_player_on_zodiac();
	//rumble ent
	level.zodiac_rumble = get_rumble_ent( "steady_rumble" );
	level.zodiac_rumble.intensity = 0;
	
	level.player delaycall ( 1.85, ::PlayRumbleOnEntity, "falling_land" );
	
	level.sandman notify("stop_waving");
	delaythread ( 1.0, ::sub_fire_missiles );
	//delaythread( 2.0, ::flag_set, "start_opening_missile_doors");
	level.sdv_player_legs hide();
	play_exit_to_zodiac();
	level.escape_zodiac thread track_water_patch( patchnames, zoff );
	
	flag_set( "obj_escape_given" );
	
	thread zodiac_slow_mo_setup();
	thread zodiac_gameplay();
	thread handle_rescue_seaknight();
	thread handle_allies_zodiac();
	level.escape_zodiac.current_patch = "water_patch_med";
	while (level.escape_zodiac.veh_speed <= 0)
		wait 0.05;
	aud_send_msg("begin_zodiac_ride");
	level.sandman.use_auto_pose = true;	// allow sandman to switch sides
}

setup_ally_zodiac()
{
	level.truck = maps\ny_harbor::create_ally("squad_reno", "truck", "Truck", "r");
	level.grinch = maps\ny_harbor::create_ally("squad_truck", "grinch", "Grinch", "r");
	thread 	load_ally_zodiac();
	level.ally_zodiac thread hold_zodiac_in_place();
}

sub_fire_missiles()
{
	flag_set ( "start_opening_missile_doors" );
	wait 4;
	//level.escape_zodiac anim_single_solo ( level.sandman, "launch_react", "tag_guy2" );
	
}

put_sandman_on_zodiac_waving()
{
	actor = level.sandman;
	actor endon("stop_waving");
	boat = level.escape_zodiac;
	boat Show();
	boat Vehicle_teleport ( level.escape_zodiac_start.origin, level.escape_zodiac.angles );
//	boat SetModel("vehicle_zodiac");	// show the npc version of the zodiac for now
	boat anim_first_frame_solo( actor, "wave_from_zodiac", "tag_guy2" );
	actor linkto( boat, "tag_guy2" );
	while (true)
		boat anim_single_solo( actor, "wave_from_zodiac", "tag_guy2" );
}

keep_dying_player_on_zodiac()
{
	level.player waittill("death");
	if (isdefined(level.player.driving) && level.player.driving)
	{
		while (true)
		{
			level.player PlayerLinkToDelta ( level.escape_zodiac, "tag_player", 0, 60, 90, 45, 45 );	// ensure player stays on boat
			wait 0.05;
		}
	}
}

catch_notetrack_switch_zodiac( boat1, boat2 )
{
	self waittillmatch( "single anim", "swap_zodiac" );
	boat1 SetModel("vehicle_zodiac_viewmodel_harbor");
	boat2 SetModel("vehicle_zodiac_viewmodel_harbor");
	boat1 DontCastShadows();
	boat2 DontCastShadows();
	level.ally_zodiac.displacement = 0;	// clear the displacement of the ally while we are looking away.
}

move_node_to_tgt_then_to_veh_tgt( snode, vnode )
{
	TIME_TO_S = 0.5;
	TIME_TO_V = 0.5;
	level.escape_zodiac.displacement_scale = 0.0;
	self unlink();
	self moveto( snode.origin, TIME_TO_S, 0, 0 );
	self rotateto( snode.angles, TIME_TO_S, 0, 0 );
	wait TIME_TO_S;
	// guarrantee we match
	self.origin = snode.origin;
	self.angles = snode.angles;
	snode linkto( self );		// now we want the snode to follow our znode
	// now move it back to the vehicle (which may be rocking
	self moveto( vnode.origin, TIME_TO_V, 0, 0 );
	self rotateto( vnode.angles, TIME_TO_V, 0, 0 );
	wait TIME_TO_V;
	// this should get us close, but the target may have moved slightly, so catchup in a frame
	self moveto( vnode.origin, 0.05, 0, 0 );
	self rotateto( vnode.angles, 0.05, 0, 0 );
	wait 0.05;
	self.origin = vnode.origin;
	self.angles = vnode.angles;
	self linkto( vnode );
}

ramp_displacement( target, time )
{
	while (time > 0)
	{
		self.displacement += (target - self.displacement)*0.05/time;
		time -= 0.05;
		wait 0.05;
	}
	if (target == 0)
		self.displacement = undefined;
	else
		self.displacement = target;
}

ramp_displacement_scale( target, time )
{
	while (time > 0)
	{
		self.displacement_scale += (target - self.displacement_scale)*0.05/time;
		time -= 0.05;
		wait 0.05;
	}
	if (target == 1)
		self.displacement_scale = undefined;
	else
		self.displacement_scale = target;
}

ramp_boatrocking_scale( target, time )
{
	while (time > 0)
	{
		current = getdvarfloat( "vehBoatRockingScale" );
		current += (target - current)*0.05/time;
		setsaveddvar( "vehBoatRockingScale", ""+current );
		time -= 0.05;
		wait 0.05;
	}
	setsaveddvar( "vehBoatRockingScale", ""+target );
}

clear_start_from_cinematic( actor )
{
	actor.start_from_cinematic = undefined;
}

draw_tag_axis( tag )
{
	/#
	axis = spawn("script_model", self GetTagOrigin( tag ));
	axis.angles = self GetTagAngles( tag );
	axis SetModel("axis");
	axis linkto(self, tag);
	self waittill("death");
	axis Delete();
	#/
}


play_exit_to_zodiac()
{
	// disable weapons early, to ensure weapons like the spas are put away before we see the arms
	level.player disableWeapons();
	level.player FreezeControls( true );
	
	//check players stance and if he is crouched, or prone, get him standing up to avoid viewmodel issues
	if ( level.player getstance() == "crouch" || level.player getstance() == "prone" )
	{
		//check to see if player is prone and if he is, wait longer to avoid viewmodel issues
		if ( level.player getstance() == "prone" )
			waittime = 0.5;
		else
			waittime = 0.2;
				
		level.player setstance ( "stand" );
		
		wait waittime;
	}

	thread ramp_boatrocking_scale( 0.0, 0.5 );
	// might need a 40 unit offset to get boat above water.
	actor = level.sandman;
	boat = level.escape_zodiac;
	boat makeUnusable();
	scriptednode = getent("sub_board_anim_node","targetname");
	offset = (0,0,18);						// we need an offset to ensure the water doesn't clip through
	snode = spawn_tag_origin();				// this node is used for the arms and legs
	snode.origin = scriptednode.origin + offset;
	snode.angles = scriptednode.angles;
	znode = spawn_tag_origin();				// this node is used for the zodiac model
	znode.origin = scriptednode.origin + offset;
	znode.angles = scriptednode.angles;
	vnode = spawn_tag_origin();				// this node is used for the zodiac vehicle
	vnode.origin = scriptednode.origin + offset;
	vnode.angles = scriptednode.angles;
	boat_model = spawn( "script_model", boat.origin );	// this is the visible zodiac matched with znode
	boat_model.animname = "zodiac";
	boat_model SetModel("vehicle_zodiac_boat");
	boat_model SetAnimTree();
	boat_model.targetname = "boat_model";	// debugging
	boat_model Hide();
//boat_model thread draw_tag_axis( "tag_player" );
//boat thread draw_tag_axis( "tag_player" );
//level.sdv_player_arms thread draw_tag_axis( "tag_player" );
	tgt_boat_model = spawn( "script_model", boat.origin );		// this is the zodiac matched with snode
	tgt_boat_model.animname = "zodiac";
	tgt_boat_model SetModel("vehicle_zodiac_boat");
	tgt_boat_model SetAnimTree();
	tgt_boat_model.targetname = "tgt_boat_model";	// debugging
	tgt_boat_model Hide();
	veh_boat_model = spawn( "script_model", boat.origin );		// this is the zodiac matched with vnode
	veh_boat_model.animname = "zodiac";
	veh_boat_model SetModel("vehicle_zodiac_boat");
	veh_boat_model SetAnimTree();
	veh_boat_model.targetname = "veh_boat_model";	// debugging
	veh_boat_model Hide();
//tgt_boat_model thread draw_tag_axis( "tag_player" );
	snode anim_first_frame_solo( tgt_boat_model, "exit_to_zodiac" );
	vnode anim_first_frame_solo( veh_boat_model, "exit_to_zodiac" );
	vnode linkto( veh_boat_model );		// so vnode will move when we move veh_boat_model
	tgt_boat_model linkto( snode );		// so tgt_boat_model will move when we move snode
	veh_boat_model match_origin_to_tag( boat, "tag_body", true );	// move the veh_boat_model and vnode to match boat (linking veh_boat_model)

	guys[0] = level.sdv_player_arms;
	guys[1] = level.sdv_player_legs;
	snode anim_first_frame( guys, "exit_to_zodiac" );
	guys[0] linkto( snode );
	guys[1] linkto( snode );
	level.sdv_player_arms hide();
	level.player playerlinktoblend ( level.sdv_player_arms, "tag_player", 0.2 );
	level.sdv_player_legs delaycall ( 0.2, ::show );
	
	wait 0.05;	// wait so the linked ent vnode moves as well
	znode.origin = vnode.origin;	// match znode with vnode at start
	znode.angles = vnode.angles;
	znode linkto( boat, "tag_body" );				// for now, znode will follow tag_body on the vehicle (so it gets the pitch/roll changes)
	znode anim_first_frame_solo( boat_model, "exit_to_zodiac" );	// boat_model should match boat/veh_boat_model at this point_in_fov
	boat_model linkto( znode );			// now we can move znode around while boat_model animates to get boat_model where we need to
	wait 0.05;	// not sure we need this
	boat Hide();
	boat_model Show();
	actor linkto( boat_model, "tag_guy2" );	// move sandman to the visible model
	
	wait 0.1;	// wait the remaining time for the blend
	// move the znode to the snode, linkto snode, then move back to vnode, while the animation is playing
	znode thread move_node_to_tgt_then_to_veh_tgt( snode, vnode );
	znode thread anim_single_solo( boat_model, "exit_to_zodiac" );				// animate the boat (we'll move it by moving znode)
	boat_model thread anim_single_solo( actor, "exit_to_zodiac", "tag_guy2" );	// animate sandman
	level.sdv_player_arms delaycall ( 0.1, ::show );
	level.sdv_player_arms thread catch_notetrack_switch_zodiac( boat_model, boat );
	snode anim_single( guys, "exit_to_zodiac" );
	level.sdv_player_legs unlink();
	level.sdv_player_arms linkto( boat_model, "tag_player" );	// link player arms so it stays in proper place until we've mounted
	// now move the boat_model back to the vehicle
	foreach( guy in guys ) //hide arms and legs since they were sticking around
	{
		guy hide();
	}
	boat_model unlink();
	actor unlink();	// so we can teleport as necessary
	actor.a.boat_pose = "left";	// prevent the transition between sides until we set use_auto_pose later
	actor.start_from_cinematic = true;	// this is to get us aiming forward
	delaythread( 2, ::clear_start_from_cinematic, actor );
	actor thread get_guy_on_zodiac( boat );
	// now we'll put everyone on the boat and the player will use it
	level.zodiac_playerZodiacModel = "vehicle_zodiac_viewmodel_harbor";	// ensure _zodiac_drive doesn't switch to wrong model
	array_call ( guys, ::unlink );
	array_call ( guys, ::linkto, boat, "tag_player" );
	boat Show();
	// get sandman back to playing the correct anim
	level.player FreezeControls( false );
	SetSavedDvar( "vehCam_pitchClamp", "0.1" );
	SetSavedDvar( "vehCam_yawClamp", "0.1" );
	boat makeUsable();
	boat useby(level.player);
	level.player.driving = true;
	boat makeUnusable();
	flag_clear ( "player_off_path" );
	flag_set("player_on_boat");
	
	autosave_by_name ( "on_zodiac" );
	
	delaythread ( 5, ::zodiac_fail );
	delaythread ( 5, ::zodiac_fail_progress_gates );
	level.zodiac_fail_speed = 30;
	boat thread ramp_displacement_scale( 1.0, 2.0 );	// ramp the effect of the waves back up
	thread ramp_boatrocking_scale( 1.0, 2.0 );	// ramp the rocking back up
	
	level.sandman disable_pain();
	thread display_hint_timeout ( "hint_zodiac", 10 );
	thread autosave_pre_carrier();
	
	// Removing this; adding e3-legal music, dv.  thread zodiac_music(); 
	
	// cleanup ents
	boat_model Delete();
	tgt_boat_model Delete();
	veh_boat_model Delete();
	snode Delete();
	znode Delete();
	vnode Delete();
}

autosave_pre_carrier()
{
	flag_wait ( "autosave_pre_carrier" );
	
	maps\_autosave::_autosave_game_now_notrestart();
	//thread autosave_by_name ( "pre_carrier_slide" );
	
}

show_carrier()
{
	carrier = getent( "carrier_model", "targetname" );
	carrier show();
}

zodiac_gameplay()
{
	level.zodiac_cg = false;
	ship = getent ("sinking_ship", "targetname");
	ship delete();	// to many polys and it's supposed to be underwater
	//thread setup_floating_bodies();
	thread make_swimmers();
	//thread make_fallers();
	thread ship_squeeze_event();
	thread destroyer_missile_fx();
	thread destroyer_zubr_driveby();
	thread make_zubrs();
	//thread make_fallers2();
	//thread make_falling_debris();
	thread show_hidden_ships();
	//thread spawn_enemies();
	thread zodiac_slow_mo_event();
	thread exit_path();
	thread missile_timing();
	thread start_boat_player_crash();
	thread zodiac_set_calm_waters();
	thread zodiac_smoke_field();
	thread hide_sub_missile_tubes();
	thread zodiac_fail_flip_player();
}

start_boat_player_crash()
{
	flag_wait("start_boat_crash");
	
}

zodiac_fail()
{
	flag_wait ( "player_on_boat" );
	
	thread zodiac_fail_monitor_speed();
	//thread zodiac_fail_monitor_distance();
	
	level endon ( "chinook_success" );
	level endon ( "pause_zodiac_fail" );
	
	while ( true )
	{
		flag_wait_any ( "player_too_slow", "player_off_path", "chinook_clean_entry" );
		
		if ( !flag ( "switch_chinook" ) )
			SetDvar( "ui_deadquote", "@NY_HARBOR_ZODIAC_FAIL_QUOTE" );
		else
			SetDvar( "ui_deadquote", "@NY_HARBOR_ZODIAC_FAIL_QUOTE_CHINOOK" );
		
		if ( flag ( "chinook_clean_entry" ) )
			SetDvar( "ui_deadquote", "@NY_HARBOR_ZODIAC_FAIL_QUOTE_CHINOOK_ENTRY" );			
		
		/*
		incoming_dur = randomfloatrange( 1.0, 1.5 );
		
		aud_send_msg("waterbarrage_inc_normal", incoming_dur);
		
		// Wait for incoming sound to play a bit.
		wait( incoming_dur );
		org = spawn ( "script_origin", ( 0, 0, 0 ) );
		forward = AnglesToForward( level.player.angles );
		right = anglestoright ( level.player.angles );
		x = randomfloatrange ( 0, 1 );
		org.origin = level.player.origin + forward * 128 + right * x;
		org.angles = level.player.angles;
		playfxontag ( level._effect[ "mortarExp_water" ], level.escape_zodiac, "tag_guy2" );
		wait 0.3;
		playfxontag ( level._effect["ny_harbor_explosionVerticalbarrage"], level.escape_zodiac, "tag_guy2" );
		aud_send_msg("zodiac_water_impacts", org.origin);
		//wait 0.25;
		level notify ( "flip" );
		*/
		
		missionFailedWrapper();
		break;
	}
	
}

zodiac_fail_monitor_speed()
{
	level endon ( "start_exit_path_align" );
	level endon ( "pause_zodiac_fail" );
	
	while ( true )
	{
		if ( flag ( "destroy_ally_zodiac" ) )
			level.zodiac_fail_speed = 50;
			
		if ( level.escape_zodiac vehicle_getspeed() <= level.zodiac_fail_speed )
		{
			flag_set ( "player_going_too_slow" );
			
			thread zodiac_fail_monitor_speed_clear();
			
			flag_wait_or_timeout ( "player_going_fast_enough", 5 );
			
			wait 0.1;
			
			if ( !flag ( "player_going_fast_enough" ) )
			{
				flag_set ( "player_too_slow" );
			}
			
			else
			{
				flag_clear ( "player_going_too_slow" );
				flag_clear ( "player_going_fast_enough" );
			}
			
		}
		
		wait 0.1;
		
	}
	
}

zodiac_fail_monitor_speed_clear()
{
	level endon ( "stop_monitor_speed_clear" );
	level endon ( "pause_zodiac_fail" );
	level endon ( "start_exit_path_align" );
	
	while ( true )
	{
		if ( level.escape_zodiac vehicle_getspeed() >= level.zodiac_fail_speed )
		{
			flag_set ( "player_going_fast_enough" );
			level notify ( "stop_monitor_speed_clear" );
		}
		
		wait 0.1;
		
	}
	
}

zodiac_fail_flip_player()
{

	level waittill ( "flip" );
	level.sdv_player_arms hide();
	level.sdv_player_legs hide();
	if (isdefined(level.escape_zodiac.firstPerson))
		level.escape_zodiac Detach( level.zodiac_playerHandModel, "tag_player" );
	level.player dismountvehicle();
	if ( isdefined ( level.player ) )
		level.player kill();
//	if ( !TEST_FLIP )
//		level.player waittill( "death" );
//
//	if ( TEST_FLIP )
//	{
//		while ( ! level.player ButtonPressed( "BUTTON_B" ) )
//			wait .05;
//	}

	linkobj = Spawn( "script_model", level.player.origin );
	linkobj.angles = level.player.angles;
	linkobj Hide();
	linkobj SetModel( "zodiac_head_roller" );
	linkobj LinkTo( level.escape_zodiac, "tag_player", ( 0, 0, 60 ), ( 0, 0, 0 ) );

	offset_obj = Spawn( "script_model", level.player.origin );
	offset_obj SetModel( "zodiac_head_roller" );
	offset_obj LinkTo( linkobj, "tag_player", ( 0, 0, -60 ), ( 0, 0, 0 ) );
	offset_obj.angles = level.player.angles;
	offset_obj Hide();

	blend_time = 1;

  // Attach the collision under the zodiac to try to help keep everything above (doesn't seem to work on ragdolls)
	base_origin = level.escape_zodiac.origin;
	coll = getent( "diver_death_collision", "targetname");
	coll Hide();
	coll.origin = base_origin;
	coll linkto( level.escape_zodiac, "tag_body");

//	if ( TEST_FLIP )
//	{
//		level.player DismountVehicle();
//		level.player.drivingVehicle = level.players_boat;
//
//	}

//	level.sandman stop_magic_bullet_shield();
//	level.sandman.ragdoll_immediate = true;  // sandman will go ragdoll immediately upon death
	
	wait .1;

	level.player PlayerLinkToDelta( offset_obj, "tag_player", 1.0, 0, 0, 0, 0 );
	level.player PlayerSetGroundReferenceEnt( offset_obj );

	boatvelocity = level.escape_zodiac Vehicle_GetVelocity();

	forward = AnglesToForward( level.escape_zodiac.angles );
	right = AnglesToRight( level.escape_zodiac.angles );
	sandman_hold = 0.15;
	offset = boatvelocity*0.15 - 12*forward + 48*right;
	if (VectorDot(forward,boatvelocity) < 0)
	{
		sandman_hold = 0.25;
	}
	exp_origin = level.player.origin + offset;
	physicsexplosionsphere ( exp_origin, 125, 120, 0.1 );
	
	wait sandman_hold;
//	level.sandman kill();
	wait 0.1;
	boatvelocity = level.escape_zodiac Vehicle_GetVelocity();
	exp_origin = level.sandman.origin + boatvelocity*0.10 + (0,0,24);
	physicsexplosionsphere ( exp_origin, 250, 200, 1.0 );
}

zodiac_death_call_flip()
{
	level.player waittill ( "death" );
	
	level notify ( "flip" );
}

chinook_extraction_fail()
{
	//this checks to see if the player hit the trigger to start the extraction 
	//and if so, wait a few seconds and fail the player as a fail safe for weird things happening if the player enters that trigger at a funky angle
	
	level endon ( "chinook_success" );
	
	flag_wait ( "start_exit_path_align" );
	
	wait 5;
	
	if ( !flag ( "chinook_success" ) )
		flag_set ( "player_off_path" );
		
}

//ensure the player keeps moving forward on the zodiac
zodiac_fail_progress_gates()
{
	num_gates = 7;
	
	level endon ( "flip" );
	level endon ( "chinook_success" );
	
	for ( i = 0; i <= num_gates; i++ )
	{
		flag_wait_or_timeout ( "zodiac_gate" + i, 8 );		//give the player 8 seconds to hit his next gate, or nuke him

		if ( i == 7 ) //give the player an extra couple seconds on the last gate before the carrier slide. 
				wait 3;
		
		if ( !flag ( "zodiac_gate" + i ) )
		{
			if ( !flag ( "start_boat_crash" ) )
				flag_set ( "player_off_path" );
		}
		else
			level notify ( "gate_passed" );
		
		
			
	}
	
	flag_wait ( "carrier_done" );
	num_gates = 14;
	
	for ( i = 8; i <= num_gates; i++ )
	{
		flag_wait_or_timeout ( "zodiac_gate" + i, 8 );		//give the player 8 seconds to hit his next gate, or nuke him
		if ( !flag ( "zodiac_gate" + i ) )
			flag_set ( "player_off_path" );
		else
			level notify ( "gate_passed" );
					
	}
	
	flag_wait_or_timeout ( "chinook_success", 10 );
	if ( !flag ( "start_exit_path" ) )
		flag_set ( "player_off_path" );
	

}

sub_deck_fail()
{
	wait 15; 
	count = 0;
	if( !flag( "get_on_zodiac" ) )
	{
		SetDvar( "ui_deadquote", "@NY_HARBOR_FAIL_SUB_DECK_ZODIAC" );
		missionFailedWrapper();
		
	}
	
}
	

//-----------------------------------------------------------
//                  MISSILES
//----------------------------------------------------------

missile_timing()
{
	flag_wait ("spawn_torpedo_1");
	ssn_12_0 = launch_s300( "big_missile0", "big_missile0_landed" );
	thread wait_for_missile_hit( "big_missile0_landed", ssn_12_0 );
	aud_send_msg("big_missile_launch_1", ssn_12_0);
	delaythread ( 4, ::zodiac_water_impacts, "spawn_missile_1", 0, 1 );
	thread kill_boat ( "big_missile0_landed", "ship2_squeeze", "ship2_squeeze_roll", "ship2_squeeze_roll_2" );
	
	flag_wait ("spawn_missile_1");

	wait 0.5;
	
	ssn_12_1 = launch_ssn12( "enemy_missile2", "enemy_missile2_landed" );
	thread wait_for_missile_hit( "enemy_missile2_landed", ssn_12_1 );
	aud_send_msg("big_missile_launch_2", ssn_12_1);
	
	s300_1 = launch_s300( "big_missile1", "big_missile1_landed" );
	thread wait_for_missile_hit( "big_missile1_landed", s300_1 );
	//thread kill_boat("big_missile1_landed", "ship_splode_1", "ship_splode_1a", "ship_splode_1b");
	thread kill_boat_anim ( "big_missile1_landed", "ship_splode_1", "burya", "front" );
	//disable ambient fx so ship explosions don't make us go over particle limit
	thread maps\ny_harbor_fx::disable_ambient_fx();
	aud_send_msg("incoming_missile_to_boat", s300_1);
	
	wait 0.6;
	
	s300_2 = launch_s300( "big_missile3", "big_missile3_landed" );
	thread wait_for_missile_hit( "big_missile3_landed", s300_2 );
	//thread kill_boat("big_missile3_landed", "ship_splode_3", "ship_splode_3a", "ship_splode_3b");
	thread kill_boat_anim ( "big_missile3_landed", "ship_splode_3", "burya", "front" );
	aud_send_msg("incoming_missile_to_boat", s300_2);
	
	flag_wait ("spawn_missile_2");
	wait 1;
	s300_3 = launch_s300( "big_missile2", "big_missile2_landed" );
	thread wait_for_missile_hit( "big_missile2_landed", s300_3 );
	//thread kill_boat("big_missile2_landed", "ship_splode_2", "ship_splode_2a", "ship_splode_2b");
	thread kill_boat_anim ( "big_missile2_landed", "ship_splode_2", "burya", "mid" );
	aud_send_msg("incoming_missile_to_boat", s300_3);
	
	flag_wait ("spawn_second_missiles");
	
	wait 0.5;
	s300_4 = launch_s300( "big_missile5", "big_missile5_landed" );
	thread wait_for_missile_hit( "big_missile5_landed", s300_4 );
	//thread kill_boat("big_missile5_landed", "ship_splode_5", "ship_splode_5a", "ship_splode_5b");
	thread kill_boat_anim ( "big_missile5_landed", "ship_splode_5", "burya", "mid" );
	aud_send_msg("incoming_missile_to_boat", s300_4);
	wait 0.5;
	
	s300_5 = launch_s300( "big_missile4", "big_missile4_landed" );
	thread wait_for_missile_hit( "big_missile4_landed", s300_5 );
	//thread kill_boat("big_missile4_landed", "ship_splode_4", "ship_splode_4a", "ship_splode_4b");
	thread kill_boat_anim ( "big_missile4_landed", "ship_splode_4", "burya", "rear" );
	aud_send_msg("incoming_missile_to_boat", s300_5);
	
	wait 5.4;
	s300_6 = launch_s300( "big_missile6", "big_missile6_landed" );
	thread wait_for_missile_hit( "big_missile6_landed", s300_6 );
	//thread kill_boat("big_missile6_landed", "ship_splode_6", "ship_splode_6a", "ship_splode_6b");
	thread kill_boat_anim ( "big_missile6_landed", "ship_splode_6", "burya", "front" );
	aud_send_msg("incoming_missile_to_boat", s300_6);
	
	flag_wait("exit_missile_trigger");
	wait 5;
	ssn_12_exit = launch_ssn12( "exit_missile_1", "big_missileE1_landed" );
	thread wait_for_missile_hit( "big_missileE1_landed", ssn_12_exit );
	
}

missile_timing2()
{
	wait 0.5;
	ssn_12_exit = launch_ssn12( "exit_missile_1", "big_missileE1_landed" );
	thread wait_for_missile_hit( "big_missileE1_landed", ssn_12_exit );
}

jet_timings1()
{
//	flag_wait("trigger_jets1");
//	jet1 = spawn_vehicles_from_targetname_and_drive( "f15_01");
//	jet2 = spawn_vehicles_from_targetname_and_drive( "f15_02");
	
	flag_wait("view_8");
	aud_send_msg("spawn_f15_fighters_finale");	
	wait 2.5;
	jet3 = spawn_vehicles_from_targetname_and_drive( "f15_03");
	jet4 = spawn_vehicles_from_targetname_and_drive( "f15_04");
	jet5 = spawn_vehicles_from_targetname_and_drive( "f15_05");
}

kill_boat(flg, boat, pos1, pos2)
{
	loc1 = getent(pos1, "targetname");
	loc2 = getent(pos2, "targetname");
	ship = getent(boat, "targetname");
	ship no_bobbing();
	flag_wait (flg);
	
	ship moveto(loc1.origin, 2.2, 0.2, 2);
	ship rotateto(loc1.angles, 2.2, 0.2, 2);
	wait 0.2;
	flag_set("flag_destroyer_fx");
	wait 0.3;
	//play wave fx
	wave = getent("destroyer_wave", "script_noteworthy");
	wave thread maps\ny_harbor_fx::play_explode_wave_anim();
	//play associated fx from createfx
	wait 1.0;
	ship moveto(loc2.origin, 3, 1.7, 0.3);
	ship rotateto(loc2.angles, 3, 1.7, 0.3);
	
}

kill_boat_anim ( wait_flag, boatname, animname, hit_loc  )
{
	boat = getent ( boatname, "targetname" );
	
	boat_anim = getent ( boat.target, "targetname" );
	boat_anim.animname = animname;
	boat_anim setanimtree();
	
	org = spawn ( "script_origin", boat.origin );
	org.angles = boat.angles;
	org linkto ( boat );
	boat_anim linkto ( org );
	
	flag_wait ( wait_flag );
	
	boat no_bobbing();
	
	org anim_first_frame_solo ( boat_anim, "destruct_" + hit_loc );
	
	//wait 0.1; 
	
	boat hide();
	boat_anim show();
	
	playfxontag(getfx("corvette_explosion_front"), boat_anim, "tag_deathfx_" + hit_loc );
	//play fire reflection
	explosionLoc = boat_anim getTagOrigin("tag_deathfx_" + hit_loc);
	maps\ny_harbor_fx::update_fire_reflections_manager("corvette_explosion_front", (explosionLoc[0], explosionLoc[1], -225) );
	//play wave fx
	wave = getent((boatname + "_wave"), "script_noteworthy");
	if(isdefined(wave))
		wave thread maps\ny_harbor_fx::play_explode_wave_anim("fire");
	//play associated fx from createfx
	flagname = "flag_" + boatname + "_fx";
	flag_set(flagname);
	org anim_single_solo ( boat_anim, "destruct_" + hit_loc );

	
	
}

setup_boat_destruction()
{
	boats = [];
	
	for ( i = 1; i < 7; i++ )
	{
		boat = getent ( "ship_splode_" + i, "targetname" );
		boat_destruct = getent ( boat.target, "targetname" );
		boat_destruct linkto ( boat );
		boat_destruct hide();
	}
	
}

launch_s300( name, flg )
{
	s300 = spawn_vehicles_from_targetname_and_drive( name );
	assert( s300.size > 0 );
	//
	s300[0].animname = "ss_n_12_missile";
	//s300[0] setanim( level.scr_anim["ss_n_12_missile"]["close_idle"], 1, 0 );

	s300[0] Vehicle_SetSpeed( 500, 100, 50 );

	s300[0] thread play_s300fx( name );//seperate thread to sequence fx off the missiles
	aud_send_msg("missile_launch", s300[0] );
	//thread wait_for_missile_hit( flg, ssn_12 );
	return s300[0];
}

launch_ssn12( name, flg )
{
	ssn_12 = spawn_vehicles_from_targetname_and_drive( name );
	assert( ssn_12.size > 0 );
	//
	ssn_12[0].animname = "ss_n_12_missile";
	ssn_12[0] setanim( level.scr_anim["ss_n_12_missile"]["close_idle"], 1, 0 );
	ssn_12[0] thread open_ssn12_wings();

	ssn_12[0] Vehicle_SetSpeed( 500, 100, 50 );

	ssn_12[0] thread play_ssn12fx_alt( name );//seperate thread to sequence fx off the missiles
	aud_send_msg("missile_launch", ssn_12[0] );
	//thread wait_for_missile_hit( flg, ssn_12 );
	return ssn_12[0];
}

wait_for_missile_hit( name, missile )
{
	missile endon("missile_hit");
	flag_wait( name );
	node = getvehiclenode( name, "targetname" );
	if (isdefined(node))
		missile thread missile_hit( node.origin, node.angles );
	else
		missile thread missile_hit( missile.origin, missile.angles );

	if ( isdefined( missile ) )
	{
		missile thread missile_cleanup();
	}
	missile notify("missile_hit");	// kill any other threads for this missile waiting for a hit
}


missile_hit( pos, angles )
{
	dummy = spawn_tag_origin();
	dummy.origin = pos;
	dummy.angles = angles;
	//PlayFXOnTag( getfx( "ship_explosion" ), dummy, "tag_origin" );
	aud_send_msg( "little_ship_missile_hit", dummy.origin);
	thread maps\ny_harbor_fx::play_missile_hit_screenfx(pos);
	if( isDefined( self ) )
	{
		self delete();
	}

	wait 2;
	dummy delete();
}

destroyer_missile_fx()
{
	flag_wait( "big_missile0_landed" );
	org = getstruct( "org_destroyer_fx", "targetname" );
	aud_send_msg("big_ship_missile_hit", org.origin);
	dummy = spawn_tag_origin();
	dummy.origin = org.origin;
	dummy.angles = org.angles;
	PlayFxOnTag( getfx( "destroyer_missile_impact" ), dummy, "tag_origin" );
	wait( 2 );
	StopFxOnTag( getfx( "destroyer_missile_impact" ), dummy, "tag_origin" );
	dummy delete();
}

destroyer_zubr_driveby()
{
	flag_wait( "zubrs_destroyers" );
	zubr = spawn_vehicle_from_targetname_and_drive( "destroyer_zubr" );
	zubr thread maps\ny_harbor_fx::surface_zbur_treadfx();
	
	flag_wait ( "start_boat_crash" );
	
	zubr delete();

	//zubr thread dvora_delete();
	
}

play_s300fx( name )
{
	self endon("death");

	if(name=="ssn12_1_r_i") exploder(690);
	else exploder(691);
	//Start the main ignition 
	wait(.5);
	if(name=="ssn12_1_r_i") exploder(692);
	else exploder(693);
	//start the white launch smoke & trail
	wait(.5);
	//PlayFXOnTag( getfx( "ssn12_launch_smoke" ), self, "tag_origin" );
	//start the black smoke
	wait(.5);
	//PlayFXOnTag( getfx( "ssn12_init" ), self, "tag_tail" );
}

play_ssn12fx_alt( name )
{
	self endon("death");

	if(name=="ssn12_1_r_i") exploder(690);
	else exploder(691);
	//Start the main ignition 
	wait(.5);
	if(name=="ssn12_1_r_i") exploder(692);
	else exploder(693);
	//start the white launch smoke & trail
	wait(.5);
	PlayFXOnTag( getfx( "ssn12_launch_smoke" ), self, "tag_tail" );
	//start the black smoke
	wait(.5);
	//PlayFXOnTag( getfx( "ssn12_init" ), self, "tag_tail" );
}

open_ssn12_wings()
{
	self endon("death");
	wait 0.5;
	self setanim( level.scr_anim["ss_n_12_missile"]["open"], 1, 0 );
}

missile_cleanup()
{
	if ( ent_flag_exist( "engineeffects" ) )
		ent_flag_clear( "engineeffects" );
	if ( ent_flag_exist( "afterburners" ) )
		ent_flag_clear( "afterburners" );
	if ( ent_flag_exist( "contrails" ) )
		ent_flag_clear( "contrails" );
	wait 0.05;
	self delete();
}

zodiac_set_calm_waters()
{
	trigger_wait_targetname( "calm_waters" );
	level.escape_zodiac.current_patch = "water_patch_calm";
}

hide_sub_missile_tubes()
{
	flag_wait( "spawn_missile_1" );
	thread maps\ny_harbor_code_sub::sub_missile_tubes_hide();
}

//-------------------------------------------------------------------------
////-------------------------------------------------------------------------------------
zodiac_smoke_field()
{
	flag_wait( "start_smoke_field" );
	orgs = getstructarray( "org_smoke", "targetname" );
	foreach( org in orgs )
	{
		dummy = spawn_tag_origin();
		dummy.origin = org.origin;
		dummy.angles = org.angles;
		//dummy thread smoke_fx();
	}
}

smoke_fx()
{
	PlayFXOnTag( getfx( "thin_black_smoke_L" ), self, "tag_origin" );
	level waittill( "kill_smoke_field" );
	StopFXOnTag( getfx( "thin_black_smoke_L" ), self, "tag_origin" );
}

determine_velocity_at_start( model, anm )
{
	self anim_first_frame_solo( model, anm );
	self thread anim_single_solo( model, anm );
	wait 0.05;
	start = model.origin;
	wait 0.05;
	end = model.origin;
	model StopAnimScripted();
	level.anim_start_vel[anm] = (end-start)*20;
}

zodiac_slow_mo_setup()
{
	org = getstruct( "org_carrier_crash", "targetname" );
	level.z_rail_1 = getent("carrier_slide_zodiac", "targetname");
	level.z_rail_1.animname = "zodiac";
	level.z_rail_1 SetAnimTree();
	level.z_rail_1 hide();
	level.z_rail_1 thread determine_velocity_at_start( level.z_rail_1, "carrier_start" );
	wait 0.5;
	level.z_rail_1.animname = "zodiac_player";
	level.z_rail_1 thread determine_velocity_at_start( level.z_rail_1, "finale_escape" );
	wait 0.5;
	level.z_rail_1.animname = "zodiac";
}

move_close_in_time( target, curvel, tgtvel, time2converge )
{
/*	/#
	createdebugtexthud("speed"+ target GetEntityNumber(), 20, 130, (1,1,1), "speed:");
	createdebugtexthud("tgtspd"+ target GetEntityNumber(), 20, 160, (1,1,1), "tgtspd:");
	#/	*/
	threshdist = 0.5 * length(curvel) * 0.05;
	prv_tgt_origin = target.origin;
	prv_origin = self.origin;
	firstframe = true;
	time = 0;
	rottime = time2converge;
	if (time2converge > 0.20)
		rottime = time2converge - 0.10;
	delta_angles = ShortestDeltaAngle(self.angles,target.angles, (360,360,360));
	self rotateto( self.angles + delta_angles, rottime, 0, 0 );	// assumes no rotation on target
	
	
	while (time < time2converge)
	{
		if (!firstframe)
		{
			curvel = 20 * (self.origin - prv_origin);
			tgtvel = 20 * (target.origin - prv_tgt_origin);
		}
		prv_tgt_origin = target.origin;
		prv_origin = self.origin;
		firstframe = false;
		ratio = time / time2converge;
		omratio = 1 - ratio;
		desired_vel = (omratio * curvel) + (ratio * tgtvel);
		desired_pos = (omratio * self.origin) + (ratio * target.origin);

		t = 1.0;
		pred_position = desired_pos + t*desired_vel;
		
		self moveto( pred_position, t, 0, 0 );
		
/*	/#
	MPHTOKPH = 1.609344;
	IPSTOKPH = MPHTOKPH/CONST_MPHTOIPS;
	tgtspd = length(tgtvel) * IPSTOKPH;
	speed = length(curvel) * IPSTOKPH;
	printdebugtexthud("speed"+ target GetEntityNumber(), speed);
	printdebugtexthud("tgtspd"+ target GetEntityNumber(), tgtspd);
	#/	*/
		time += 0.05;
		wait 0.05;
	}
	self.origin = target.origin;
	self.angles = target.angles;
}

match_fov( vehicle, transtime )
{
	level endon("stop_match_fov");
	vehdef = spawnstruct();
	vehcam_offset = (0,0,0);
	vehdef.vehcam_offset = vehcam_offset;
	vehdef.fovSpeed = CONST_MPHTOIPS*65.0;
	vehdef.fovIncrease = 20.0;
	vehdef.fovOffset = 0.0;
	vehdef.rollInfluence = 0.6;
	base_fov = GetDvarFloat("cg_fov");	// get base
	time = 0;
	prv_speed = 0.0;
	dSpeed = 2*CONST_MPHTOIPS;

	while (true)
	{	
		speed = 0.0;
		if (isdefined(vehicle.matching))
		{
			if (isdefined(vehicle.cur_speed))
				speed = CONST_MPHTOIPS*vehicle.cur_speed;
			else
				speed = Length(vehicle.vel);	// get speed in IPS
		}
		else
		{
			speed = CONST_MPHTOIPS* (vehicle Vehicle_GetSpeed());
		}
		diff = speed - prv_speed;
		if (diff < -1*dSpeed)
			diff = -1*dSpeed;
		if (diff > dSpeed)
			diff = dSpeed;
		speed = prv_speed + diff;
		prv_speed = speed;
		eyevalues = calc_vehicle_fov( vehicle, vehdef, speed );
		fovadd = eyevalues["fov"] - base_fov;
		if (time < transtime)
		{
			fovadd *= time/transtime;
			time += 0.05;
		}
		SetSavedDvar("cg_fovNonVehAdd", fovadd);
		wait 0.05;
	}
}

track_vel( ent )
{
	ent endon("stop_tracking_vel");
	prev_origin = ent.origin;
	while (true)
	{
		if (isdefined(ent.self_move))
		{
			prev_origin = ent.origin;
			if (ent.self_move > 0)
			{
				ent.vel = (ent.self_move/ent.base_self_move)*ent.base_vel;
				self.cur_speed = Length(ent.vel)/CONST_MPHTOIPS;
				ent.origin = ent.origin + 0.05*ent.vel;
			}
			else
			{
				ent.vel = (0,0,0);
			}
		}
		else
		{
			ent.vel = (ent.origin - prev_origin)*20;
			prev_origin = ent.origin;
		}
		self.vel = ent.vel;
		if (isdefined(self.matching))
		{
			self zodiac_match( ent, ent.vel );
		}
		wait 0.05;
	}
}
zodiac_teleport( origin, angles, vel )
{
	maxdspeed = 0.5;
	// move the collision before the zodiac
	self displace_zodiac_collision_at_position( origin+0.0*(vel[0],vel[1],0) );
	self vehicle_teleport( origin, angles );
	speed = Length(vel)/CONST_MPHTOIPS;
	if (isdefined(self.cur_speed))
	{	// after first frame, we limit the accel
		dSpeed = speed - self.cur_speed;
		if (abs(dSpeed) > maxdspeed)
		{
			if (dSpeed < 0)
				dSpeed = -1*maxdspeed;
			else
				dSpeed = maxdspeed;
		}
		speed = self.cur_speed + dSpeed;
		self.cur_speed = speed;	// first frame, we allow for instant change
	}
	else
	{
		self.cur_speed = speed;	// first frame, we allow for instant change
	}
	if (speed > 0)
		level.escape_zodiac Vehicle_SetSpeedImmediate(speed,speed, speed);
}

zodiac_match( target, vel )
{
	// cinematics don't honor the tag_origin->tag_body contract, so determine the position relative to tag_body
	offset = self.origin - self GetTagOrigin("tag_body");
	body_origin = target GetTagOrigin("tag_body");
	origin = body_origin + offset + 0.10*(vel[0],vel[1],0);
	angles = target GetTagAngles("tag_body");
	if (self.matching_teleport > 0)
	{
		zodiac_teleport( origin, (0,angles[1],0), vel);
		self.matching_teleport--;
	}
	else
	{
		maxdspeed = 0.5;
		//forward = VectorNormalize((vel[0], vel[1], 0));
		forward = AnglesToForward(angles);
		forward = VectorNormalize((forward[0],forward[1],0));
		speed = Length(vel)/CONST_MPHTOIPS;
		if (isdefined(self.cur_speed))
		{	// after first frame, we limit the accel
			dSpeed = speed - self.cur_speed;
			if (abs(dSpeed) > maxdspeed)
			{
				if (dSpeed < 0)
					dSpeed = -1*maxdspeed;
				else
					dSpeed = maxdspeed;
			}
			speed = self.cur_speed + dSpeed;
			self.cur_speed = speed;	// save the cur speed
		}
		else
		{
			self.cur_speed = speed;	// first frame, we allow for instant change
		}
		if ((speed > 0) && !level.player.driving)
		{
			level.escape_zodiac Vehicle_SetSpeedImmediate(speed,speed, speed);
			level.escape_zodiac VehicleDriveTo( self.origin + 2400*forward, speed );
		}
		
	}
}

wait_to_start_matching()
{
	wait 1.5;	// wait until the animated boat is more level, so the physics vehicle is whacked
	level.escape_zodiac.matching = true;
	level.escape_zodiac.matching_teleport = 55;
	thread match_fov( level.escape_zodiac, 2.0 );
}

prep_escape_zodiac_for_slide_end()
{
	level.escape_zodiac hide();
	// move the escape_zodiac to a position where it's physics can settle down
	origin = level.ally_zodiac.origin - ( 120, 0, 0);
	angles = level.escape_zodiac.angles;
	vel = level.ally_zodiac Vehicle_GetVelocity();
	level.escape_zodiac zodiac_teleport( origin, (0,angles[1],0), vel);
}

zodiac_slow_mo_event()
{
	level.player endon("death");
	flag_wait ( "spawn_dvora" );
	
	org = getstruct( "org_carrier_crash", "targetname" );
	org.origin = org.origin + (0,0,12);
	
	level.dvora = spawn_vehicle_from_targetname( "dvora_crasher" );
	level.dvora.animname = "dvora";
	level.dvora godon();
	level.dvora thread setup_dvora(org);
	
	dmg_triggers = getentarray ( "dvora_mine_trigger", "targetname" );
	array_thread ( dmg_triggers, ::dvora_mine_trigger_monitor );
	foreach ( trigger in dmg_triggers )
	{
		trigger EnableLinkTo();
		trigger linkto ( level.dvora );
	}

	level.dvora thread maps\ny_harbor_fx::surface_dvora_carrier_fx();
	
	flag_wait ("start_boat_crash");

	level.zodiac_rumble delaythread ( 0, ::rumble_ramp_to,  0.4, 0.4 );	
	level.zodiac_rumble delaythread ( 1, ::rumble_ramp_to, 0, 1 );
	
	level.player enableinvulnerability();
	level.player SetWaterSheeting( 0 );

	zodiac_ref_tgt = spawn("script_model", level.z_rail_1.origin);
	zodiac_ref_tgt SetModel("vehicle_zodiac_viewmodel_harbor");
	zodiac_ref_tgt.animname = "zodiac";
	zodiac_ref_tgt SetAnimTree();
	zodiac_ref_tgt hide();
	org anim_first_frame_solo( zodiac_ref_tgt, "carrier_start" );
	zodiac_ref_start = zodiac_ref_tgt.origin;
	
	patch = getent( level.escape_zodiac.current_patch, "targetname" ); 
	patch hide();
	level.player thread player_reload_silently();
	
	aud_send_msg("pre_slo_mo_splash");
	
	// switch to model and transition to the zodiac_ref_tgt position/angles
	level.escape_zodiac thread maps\ny_harbor_fx::surface_escape_zodiac_bumbfx();
	
	wait 0.25;
	
	thread vehicle_scripts\_zodiac_drive::stop_1st_person( level.escape_zodiac );
	level.escape_zodiac useby(level.player);
	level.player.driving = false;
	level.sandman.forceidle = true;
		
	level.player unlink();
	zodiac_model = spawn("script_model", level.escape_zodiac.origin);
	level.escape_zodiac_fx = zodiac_model;
	zodiac_model.angles = level.escape_zodiac.angles;
	zodiac_model SetModel("vehicle_zodiac_viewmodel_harbor");
	zodiac_model.animname = "zodiac";
	zodiac_model SetAnimTree();
	level.player PlayerLinkToDelta(zodiac_model, "tag_player", 0, 0, 0, 0, 0, false );
	level.player allowmelee ( false );
	level.sandman thread get_guy_on_zodiac( zodiac_model, true );
	thread prep_escape_zodiac_for_slide_end();
	level.zodiac_cg = true;
	level.ally_zodiac vehicle_setspeed( 45, 12, 5 );
	
	// get the model to the target
	vel = level.escape_zodiac Vehicle_GetVelocity();
	tgtvel = level.anim_start_vel[ "carrier_start" ];
	distance = Distance(zodiac_model.origin, zodiac_ref_tgt.origin);
	speed = 0.75*Length(vel) + 0.25*Length(tgtvel);	// weighted speed favoring our initial speed
	time2converge = distance/speed;
	anim_start_origin = zodiac_ref_tgt.origin;
	zodiac_ref_tgt.origin = anim_start_origin - time2converge*tgtvel;	// time to get to matching point
	
	//do splash delay here
	zodiac_ref_tgt moveto( anim_start_origin, 0.25, 0, 0 );
	zodiac_model move_close_in_time( zodiac_ref_tgt, vel, tgtvel, 0.25 );
	// move_close_in_time blocks until completed
	
	level.z_rail_1 = zodiac_model;
	level.escape_zodiac thread track_vel( zodiac_model );
//	level.player SetWaterSheeting( 1, 2.0 );

	boats = [];
	boats[ 0 ] = level.z_rail_1;
	//boats[ 1 ] = level.dvora;
	
	level.dvora show();
	level notify( "kill_smoke_field" );
	level.dvora animscripted( "dvora_carrier_anim_started", org.origin, org.angles, level.scr_anim[ "dvora" ][ "carrier_start" ] );
	level notify("msg_fx_playSecondSplash");
	dvora_3 = spawn_vehicle_from_targetname_and_drive ( "dvora_3" );
	aud_send_msg("slow_mo_dvora", dvora_3);
	//dvora_3 thread dvora_delete();
	//dvora_3 thread maps\ny_harbor_fx::surface_dvora_treadfx();
	level notify ( "pause_zodiac_fail" );  //stop the zodiac fail state while the slide is happening
	flag_clear ( "player_off_path" );
	org anim_single( boats, "carrier_start" );
//	weapons = level.player GetWeaponsListPrimaries();
//	foreach( weapon in weapons )
//	{
//		level.player TakeWeapon( weapon );
//	}
	
	thread carrier_slowmo_enable_player_weapon();
	thread zodiac_slomo_open_view();
	thread carrier_slow_mo_on();
//thread dump_entities();
	level.dvora animscripted( "dvora_carrier_anim_started", org.origin, org.angles, level.scr_anim[ "dvora" ][ "carrier_breach" ] );
	org anim_single( boats, "carrier_breach" );
	level.player DisableWeapons();
	level.player playerlinktoblend ( level.z_rail_1, "tag_player", .05, 0, 0 );
	if( !flag( "dvora_destroyed" ) )
	{
		//setSlowMotion( .25, 1.0, .5 );
		//level.player disableslowaim();
	}
	level.escape_zodiac.displacement = -12;
	level.escape_zodiac.displacement_scale = 0.0;
	thread wait_to_start_matching();
	
	level.player disableinvulnerability();
	thread dvora_kill_player();

	level notify("msg_fx_play_lastsplash");

	aud_send_msg("boat_slowmo_outro");
	org anim_single( boats, "carrier_end" );

	//********************************************
	zodiac_model notify("stop_tracking_vel");
	level.escape_zodiac.matching = undefined;	// turn off matching
	level.player SetWaterSheeting( 1, 5.0 );
	level.escape_zodiac useby(level.player);
	level.escape_zodiac makeUnusable();
	zodiac_model LinkToBlendToTag( level.escape_zodiac, "tag_body_origin", false );
	level.sandman thread get_guy_on_zodiac( level.escape_zodiac, true );
	zodiac_model Hide();
	level.escape_zodiac Show();
	wait 0.05;
	//********************************************
	
	thread zodiac_fail();  //start up the zodiac fail state again once the slide is over
	thread chinook_extraction_fail();
	
	time2stop = 1.0;
	zodiac_model.self_move = time2stop;
	zodiac_model.base_self_move = time2stop;
	zodiac_model.base_vel = (zodiac_model.vel[0], zodiac_model.vel[1], 0);
	while ( time2stop > 0 )
	{
		if (level.player ThrottleButtonPressed())
			break;
		time2stop -= 0.05;
		zodiac_model.self_move = time2stop;
		wait 0.05;
	}

	level.escape_zodiac.matching = undefined;	// turn off matching
	//level.escape_zodiac thread vehicle_scripts\_zodiac_drive::drive_vehicle( true, true );	// noprice == true, noshoot == true
	level.player FreezeControls( false );
	level.escape_zodiac ReturnPlayerControl();
	level.player.driving = true;
	level.escape_zodiac.veh_topspeed = 55;
	flag_set( "carrier_done" );
	thread autosave_by_name ( "carrier_slide_done" );
	level.escape_zodiac.current_patch = "water_patch_med";
	level.zodiac_cg = false;
	level.ally_zodiac thread keep_zodiac_ahead( level.escape_zodiac );
	wait 0.1;
	zodiac_model notify("stop_tracking_vel");
//	level.escape_zodiac.manual_displace = undefined;
	// restore our displacement and displacement_scale over time
	dDispl = -0.25;
	if (level.escape_zodiac.displacement < 0)
		dDispl = 0.25;
	while ((level.escape_zodiac.displacement != 0) ||
			(level.escape_zodiac.displacement_scale<1.0) ||
			(isdefined(level.escape_zodiac.zodiac_wheel_blend) && (level.escape_zodiac.zodiac_wheel_blend > 0.0)) )
	{
		if (level.escape_zodiac.displacement != 0)
			level.escape_zodiac.displacement += dDispl;
		else
			level.escape_zodiac.displacement = 0;
		if (level.escape_zodiac.displacement_scale<1.0)
			level.escape_zodiac.displacement_scale += 0.01;
		else
			level.escape_zodiac.displacement_scale = 1.0;
		if (isdefined(level.escape_zodiac.zodiac_wheel_blend))
		{
			if (level.escape_zodiac.zodiac_wheel_blend > 0.0)
				level.escape_zodiac.zodiac_wheel_blend -= 0.01;		// go to zero
			else
				level.escape_zodiac.zodiac_wheel_blend = 0.0;
		}
		wait 0.05;
	}
	level notify("stop_match_fov");	// stop the thread
	level.escape_zodiac.zodiac_wheel_blend = undefined;		// turn off
	wait 2.0;
	level.sandman.forceidle = undefined;
	zodiac_model Delete();
}

hide_player_vm_at_death()
{
	level endon( "dvora_destroyed" );
	level.player waittill("death");
	level.sdv_player_arms Hide();
	thread vehicle_scripts\_zodiac_drive::stop_1st_person( level.escape_zodiac );
	level.player FreezeControls(true);
}

dvora_kill_player()
{
	shots = 0;
	
	if ( !flag ( "dvora_destroyed" ) )
	{
		thread hide_player_vm_at_death();

		while ( !flag ( "dvora_destroyed" ) )
		{
			foreach ( mg in level.dvora.mgturret )
			{
				mg shootturret();
				level.player dodamage ( 10, level.player.origin );
				shots++;
			}
			
			wait 0.1;
			
			if ( shots >= 30 )
			{
				SetDvar( "ui_deadquote", "@NY_HARBOR_CARRIER_FAIL" );
				thread missionFailedWrapper();
				//level.player kill();
				//wait 0.1;
				while (true)
				{
					level.player PlayerLinkToDelta ( level.z_rail_1, "tag_player", 0, 60, 90, 45, 45 );	// ensure player stays on boat
					wait 0.05;
				}
			}
		}
	}
}

carrier_slowmo_enable_player_weapon()
{
	
	wait 0.2;
//	level.player GiveWeapon( "aa12_harbor" );
//	level.player SwitchToWeapon( "aa12_harbor" );
	level.player EnableWeapons();
	level.player lerpviewangleclamp ( 0.25, 0.1, 0, 60, 60, 45, 45 );
	//level.player PlayerLinkToDelta(level.z_rail_1, "tag_player", 0, 60, 40, 45, 45 );
	
}

zodiac_slomo_open_view()
{
	flag_wait ( "dvora_guy3_dead" );
	//iprintlnbold ( "3rd_guy_dead" );
	if ( !flag ( "carrier_done" ) )
		level.player PlayerLinkToDelta ( level.z_rail_1, "tag_player", 0, 60, 90, 45, 45 );
}
	
carrier_slow_mo_on()
{
	wait( 0.3 );
	setSlowMotion( 1.0, .3, .1 );
	aud_send_msg("start_carrier_slowmotion");
	level.player enableslowaim();
	wait 0.4;
	setslowmotion ( 0.3, 1.0, 0.2 );
	wait 0.2;
	level.player disableslowaim();
}

dvora_rider_death( vehicle, explosion_offset, force, delay )
{
	self.ragdoll_immediate = true;
	self waittill("death");
	// get direction to player
	forward = VectorNormalize(level.player.origin - self.origin);
	up = (0,0,1);
	right = vectorcross(forward,up);
	if (false && isdefined(vehicle))
	{
		scl = 0.2;
		vel_offset = 0.05*vehicle.vel;
		origin = self.origin + scl*((explosion_offset[0]*forward) + (explosion_offset[1]*right) + (0,0,explosion_offset[2]));
		origin = origin - vel_offset;
		radius = Distance(origin,self.origin);
		force *= 1.5;
	}
	else
	{
		radius = Length(explosion_offset);
		origin = self.origin + (explosion_offset[0]*forward) + (explosion_offset[1]*right) + (0,0,explosion_offset[2]);
	}
	if (delay>0)
		wait delay;
	if (isdefined(self))
	{
		radius = Length(explosion_offset);
		origin = self.origin + (explosion_offset[0]*forward) + (explosion_offset[1]*right) + (0,0,explosion_offset[2]);
	}
	/#
	//thread draw_point_a_while( origin, 24, (1,0,0), 10 );
	#/
	PhysicsExplosionSphere( origin, 1.5*radius, radius, force );
}

track_velocity()
{
	self endon("death");
	self.vel = (0,0,0);
	prv_origin = self.origin;
	while (true)
	{
		self.vel = 20*(self.origin - prv_origin);
		prv_origin = self.origin;
		foreach (rider in self.riders)
		{
			if ( isdefined ( rider ) && isalive ( rider ) )
				rider.ragdoll_start_vel = self.vel;
		}
		wait 0.05;
	}
}

setup_dvora(org)
{	
	self thread track_velocity();
	foreach( turret in self.mgturret )
	{
		turret setTurretCanAiDetach( false );
		//turret settargetentity ( level.player, (0, 0, 0) );
		turret setconvergencetime ( 0, "yaw" );
		//turret.ignoreall = true;
		//turret unlink();
	 
	}
	
	level.dvora.mgturret [ 0 ] settargetentity ( level.ally_zodiac, (0, 0, 0) );
	level.dvora.mgturret [ 1 ] settargetentity ( level.escape_zodiac, (0, 0, 0) );
	
	ragdoll_exp_offsets = [ (100,0,0), (100,0,0), (-100,0,0), (-100,0,0) ];
	ragdoll_exp_force = [ 1000, 1000, 1000, 1000 ];
	ragdoll_exp_delay = [ 0.05, 0.05, 0.05, 0.05 ];
	foreach( i,rider in self.riders )
	{
		rider.ignoreme = true;
		rider.accuracy = 0.06;
		if ( rider.vehicle_position == 0 )
		{
			rider.ignoreall = true;
			rider thread dvora_setdeathanim ( "ny_harbor_davora_front_turret_death", "tag_guy" );
			rider kill();
		}
		
		else if ( rider.vehicle_position == 2 )
		{
			rider thread shoot_blanks();
			rider thread dvora_setdeathanim ( "ny_harbor_davora_side_fall_death", "tag_guy3" );
		}
		
		else if ( rider.vehicle_position == 3 )
		{
			rider thread shoot_blanks();
			rider thread dvora_setdeathanim ( "stand_death_shoulderback", "tag_guy4" );
		}
			
		
	}
	self thread maps\ny_harbor_fx::surface_dvora_destroy_fx(org);
	self maps\ny_harbor_fx::surface_dvora_npc_hit_thread();

	//self thread maps\ny_harbor_fx::surface_dvora_treadfx();
 	
 	// since the player can be right were we are spawning the dvora and actors, hide them for a frame
 	self Hide();
	foreach( rider in self.riders )
	{
		rider Hide();
	}
	wait 0.10;
 	self Show();
	foreach( rider in self.riders )
	{
		rider Show();
	}
	
	self.riders[ 2 ] waittill( "death" );
	
	//rumble
	level.zodiac_rumble delaythread ( 0, ::rumble_ramp_to,  0.7, 0.1 );
	level.zodiac_rumble delaythread ( 0.75, ::rumble_ramp_to, 0, 0.5 );		//and stop
	
	flag_set( "dvora_hit" );
	
	riders = [];
	riders [ riders.size ] = self.riders [ 0 ];
	riders [ riders.size ] = self.riders [ 1 ];
	riders [ riders.size ] = self.riders [ 2 ];
	riders [ riders.size ] = self.riders [ 3 ];
	
	foreach ( mg in self.mgturret )
	{
		mg delaycall ( 0.25, ::hide );
	}
	
	array_thread ( riders, ::dvora_delete_riders );
	
	//make sure the front guy's corpse isn't hanging around anymore.
	corpses = getcorpsearray();
    foreach( corpse in corpses )
    	corpse delete();
	
	level.dvora setanim( level.scr_anim[ "dvora" ][ "destorychunk" ] );

	self notify( "dvora_destroyed" );
	//self StopAnimScripted();
	
	
	//dummy = spawn_tag_origin();
	//dummy linkto( self, "tag_player", (0, 0, 0), (0, 0, 0) );
	//PlayFxOnTag( getfx( "generic_explosions" ), dummy, "tag_origin" );
	wait( 0.2 );
	
	//setSlowMotion( .25, 1.0, .5 );
	aud_send_msg("stop_carrier_slowmotion");
	//level.player disableslowaim();
	//dummy delete();
	flag_set( "dvora_destroyed" );
}

dvora_mine_trigger_monitor()
{
	level endon ( "dvora_destroyed" );
	
	while ( true )
	{
		self waittill ( "trigger", player );
		
		if ( player == level.player )
			if (isdefined ( level.dvora.riders[2] ) && isalive ( level.dvora.riders[2] ) )
				level.dvora.riders[2] kill();
		
		wait 0.05;
	}
	
}


shoot_blanks()
{
	self endon ( "death" );
	
	for ( i = 0; i < 10; i++ )
	{
		self ShootBlank();
		wait randomfloatrange ( 0.1, 0.4 );
	}
	
}

dvora_delete_riders()
{
	wait 0.25;
	if ( isdefined ( self ) )
		self delete();
}

dvora_setdeathanim( deathanim, guy_tag )
{
	self endon("death");	// they are deleted when the dvora is destroyed
	wait 0.5;
	self.noragdoll = true;
	if ( self.vehicle_position == 0 )
	{
		if ( isdefined ( deathanim ) )
			self.deathanim = GetGenericAnim( deathanim );			
	}
	
	else
	{
		self.health = 9999;
		self.animname = "generic";
		
		self waittill ( "damage" );
		
		if ( self.vehicle_position == 3 )
			flag_set ( "dvora_guy3_dead" );
		
		level.dvora anim_single_solo ( self, deathanim, guy_tag );
		
		if ( isdefined ( self ) )
		
		{
			if ( self.vehicle_position == 3 )	
				level.dvora anim_loop_solo ( self, "ny_harbor_stand_death_shoulderback_pose", "stop_loop", guy_tag );
		}
		
		if ( isdefined ( self ) )
			self delete();
	}
	
}

move_dvora()
{
	self endon( "dvora_destroyed" );
	println ("go dvora 1");
	wait 1;
	self thread move_boat("dvora_crash_event1", 2.2);
	wait 2.2;
	self thread move_boat("dvora_crash_event2", 2.5);
	wait 2.5;
	self thread move_boat("dvora_crash_event3", 2);
	wait 2;
	println ("go dvora 4");
	self thread move_boat("dvora_crash_event4", 2);
	println ("done dvora 4");
	wait 1.5;	
}

monitor_dvora_count_shots()
{
	level endon ( "dvora_destroyed" );
	level.player endon ( "death" );
	
	while ( true )
	{
		level.player waittill( "weapon_fired" );		
		level.player.dvora_shots++;
	}
}

zubr_crash()
{
	level.zubr thread move_boat("zubr_slow_mo3", 2);
	wait 2;
	level.zubr thread move_boat("zubr_slow_mo4", 1);
	wait 1;
	level.zubr thread move_boat("zubr_slow_mo5", 1);
	wait 1;
	level.zubr thread move_boat("zubr_slow_mo6", 1);

}

move_boat(pos, time)
{
	loc = getent(pos, "targetname");
	self moveto(loc.origin, time);
	self rotateto(loc.angles, time);
	
}

ch46e_animated_rotors()
{
	self endon( "death" );
	xanim = self getanim( "rotors" );
	length = getanimlength( xanim );

	while ( true )
	{
		if ( !isdefined( self ) )
			break;
		self setanim( xanim );
		wait length;
	}
}


wait_to_start_exit_quake()
{
	flag_wait ( "start_exit_path_earthquake" );
	
	earthquake ( 0.2, 2, level.player.origin, 1024 );
}

zodiac_driveto( ref, speed, tgt_speed, threshdist, offset, time )
{
	target = ref.origin + (offset* AnglesToForward(ref.angles));
	self vehicledriveto(target, speed );
	while (true)
	{	// wait until the driveto gets us close enough
		newtarget = ref.origin + (offset* AnglesToForward(ref.angles));
		if (distance(newtarget,target) > 12 )
		{	// our target moved enough to retrigger a driveto
			target = newtarget;
			self vehicledriveto(target, speed );
		}
		z2t = target - self.origin;
		dist = Length(z2t);
		if (dist < threshdist)
			break;
		forward = AnglesToForward(self.angles);
		distfwd = VectorDot(forward, z2t);
		if (distfwd < 0)
			break;
		if (time > 0)
		{
			offset *= 1 - (0.05/time);
			speed += (tgt_speed - speed)*(0.05/time);
			time -= 0.05;
		}
		else
		{
			offset = 0;
			speed = tgt_speed;
		}
		wait 0.05;
	}
}

move_displace_to_target( time, target )
{
	self endon("death");
	if (!isdefined(self.displacement))
		return;
	delta = (target - self.displacement) * 0.05/time;
	while (time > 0)
	{
		self.displacement += delta;
		time -= 0.05;
		wait 0.05;
	}
	self.displacement = target;
}

switch_to_flyout_water()
{
	wait 2;
	ShowWater( 3 );
}

adjust_fov_to_default( fov)
{
	blendTime = 1.0;
	blendCount = blendTime/0.05;
	blendFrac = 0.05/blendTime;
	base_fov = GetDvarFloat("cg_fov");
	fovadd = fov - base_fov;
	dFov = blendFrac*fovadd;
	blend = 0;
	while (blendCount > 0)
	{
		wait 0.05;
		fovadd = fovadd - dFov;
		SetSavedDvar("cg_fovNonVehAdd",fovadd);
		blend += blendFrac;
		blendCount -= 1;
	}
	SetSavedDvar("cg_fovNonVehAdd",0);
}


exit_path()
{
	level endon ( "player_off_path" );
	
	// these need to match the parameters in the Blackshadow's vehicle
	finale_collision = getent("zodiac_finale_collision","targetname");
	finale_collision.origin = finale_collision.origin + (0,0,12);	// adjust to the correct height
	vehdef = spawnstruct();
	vehcam_offset = (0,0,0);
	vehdef.vehcam_offset = vehcam_offset;
	vehdef.fovSpeed = CONST_MPHTOIPS*65.0;
	vehdef.fovIncrease = 20.0;
	vehdef.fovOffset = 0.0;
	vehdef.rollInfluence = 0.6;
	
	level.exit_chinook = spawn_vehicle_from_targetname ( "exit_vehicle" );
	level.exit_chinook.animname = "ch46e";
	level.exit_chinook SetAnimTree();
	level.exit_chinook thread ch46e_animated_rotors();	

//	level.exit_chinook2 = spawn_vehicle_from_targetname ( "exit_vehicle2" );
//	level.exit_chinook2.animname = "ch46e2";
//	level.exit_chinook2 SetAnimTree();
	
	level.chinook_model = getent( "chinook_model", "targetname" );
	level.chinook_model.animname = "ch46e";
	level.chinook_model SetAnimTree();
	level.chinook_model hide();
	
	level.exit_chinook hide();
	//level.exit_chinook2 hide();
	
	thread wait_to_start_exit_quake();

	zodiac_ref_tgt = spawn ( "script_model", ( 0, 0, 0 ) );//level.escape_zodiac maps\_vehicle::vehicle_to_dummy();
	zodiac_ref_tgt setmodel ( "vehicle_zodiac_viewmodel_harbor" );
	zodiac_ref_tgt.animname = "zodiac_player";
	zodiac_ref_tgt setanimtree();
	zodiac_ref_tgt Hide();
	zodiac_tmp = spawn ( "script_model", ( 0, 0, 0 ) );//level.escape_zodiac maps\_vehicle::vehicle_to_dummy();
	zodiac_tmp setmodel ( "vehicle_zodiac_viewmodel_harbor" );
	zodiac_tmp.animname = "zodiac_player";
	zodiac_tmp setanimtree();
	zodiac_tmp Hide();
	level.exit_chinook anim_first_frame_solo( zodiac_tmp, "finale_escape", "tag_guy9" );
	zodiac_tmp linkto( level.exit_chinook, "tag_guy9" );
	wait 0.05;	// ensure the animation affects tag_body
	zodiac_ref_tgt match_origin_to_tag( zodiac_tmp, "tag_body", true );
	forward = AnglesToForward( zodiac_ref_tgt.angles );
	if (!isdefined(level.debug_exit_flight))
	{
		while (true)
		{
			flag_wait("start_exit_path_align");
			// determine if the zodiac is pointed in a direction that will allow us to dock
			zodiac_forward = AnglesToForward( level.escape_zodiac.angles );
			dp = VectorDot( forward, zodiac_forward);	// testing direction
			delta = zodiac_ref_tgt.origin - level.escape_zodiac.origin;
			delta = VectorNormalize( delta );
			dpo = VectorDot( forward, delta );
			if ((dp > 0.8) && (dpo > 0.8))
				break;
			flag_clear("start_exit_path_align");	// let the trigger set it again.
			wait 0.05;
		}
	}
	else
		flag_wait("start_exit_path_align");
		
		
	flag_set ( "chinook_success" );	
	level.exit_chinook notify ( "stop_loop" );
	
	level.player allowcrouch ( false );
	level.player allowprone ( false );
	
	aud_send_msg("start_zodiac_into_chinook");
	level.zodiac_cg = true;
	// turn off displacement, since it can cause havok with matching	
	level.escape_zodiac.displacement_scale = 0;
	level.escape_zodiac thread move_displace_to_target( 0.8, -36 );
	
	//turn off all hud elements, no need for them anymore
	SetSavedDvar( "compass", 0 );
    SetSavedDvar( "ammoCounterHide", 1 );
    SetSavedDvar( "hud_showstance", 0 );
    SetSavedDvar( "actionSlotsHide", 1 );

	zodiac_model = spawn ( "script_model", level.escape_zodiac.origin );//level.escape_zodiac maps\_vehicle::vehicle_to_dummy();
	zodiac_model setmodel ( "vehicle_zodiac_viewmodel_harbor" );
	zodiac_model.animname = "zodiac_player";
	zodiac_model setanimtree();
	zodiac_model match_origin_to_tag( level.escape_zodiac, "tag_body", true );  // we link to the tag on the vehicle
	level.escape_zodiac Hide();
	level.sdv_player_arms unlink();
	level.sdv_player_arms.origin = zodiac_model GetTagOrigin("tag_player");
	level.sdv_player_arms.angles = zodiac_model GetTagAngles("tag_player");
	level.sdv_player_arms dontinterpolate();
	level.sdv_player_arms linkto( zodiac_model, "tag_player");
	level.sandman dontinterpolate();
	level.sandman linkto( zodiac_model, "tag_guy2");

//	level notify( "msg_fx_play_chinook_board_coverpop" );

	fov = GetDvarFloat("cg_fov");
	if (!isdefined(level.debug_exit_flight))
	{
		eyevalues = calc_vehicle_fov( level.escape_zodiac, vehdef );
		fovadd = eyevalues["fov"] - fov;
		fov = eyevalues["fov"];
		if (isdefined(level.player.driving) && level.player.driving)
		{
			SetSavedDvar("cg_fovNonVehAdd",fovadd);	// match the vehicle
			level.escape_zodiac useby( level.player );	// get us off the vehicle
			level.escape_zodiac.veh_brake = 0;	// ensure we didn't carry over braking from when we released the player
			level.player.driving = false;
		}
		level.player playerlinktoBlend( level.sdv_player_arms, "tag_player", 0, 0, 0 );
		// get the model to the target
		vel = level.escape_zodiac Vehicle_GetVelocity();
		zspeed = level.escape_zodiac Vehicle_GetSpeed();
		tgtvel = level.anim_start_vel[ "finale_escape" ];
		// we will pick a point before the actual desired point so we can get a straight shot
		speed = Length(tgtvel)/CONST_MPHTOIPS;
		level.escape_zodiac zodiac_driveto( zodiac_ref_tgt, zspeed, speed, 120, -240, 1.0 );	// use a point 20 feet before the reference
	}
	delaythread ( 9, ::flag_set, "send_off_second_chinook" );
	flag_set( "no_more_physics_effects" );
	org = getstruct( "org_finale_escape", "targetname" );
	zodiac_model unlink();	// no longer linked to vehicle
	
	thread adjust_fov_to_default( fov);

	// interpolate between current zodiac position and reference target position
	zodiac_velocity = level.escape_zodiac Vehicle_GetVelocity();
	zodiac_speed = max( Length( zodiac_velocity ), 0.01 );
	distance_to_go = Length( zodiac_ref_tgt.origin - zodiac_model.origin );
	time_to_go = distance_to_go / zodiac_speed;
	server_steps = int ( time_to_go / 0.05 ) - 1;
	interp_start = zodiac_model.origin;
	interp_end = zodiac_ref_tgt.origin;
	zodiac_model rotateto(zodiac_ref_tgt.angles, ( server_steps + 1 ) * 0.05, 0.0, 0.0);
	for ( step = 0; step < server_steps; step++ )
	{
		interp = ( step + 1.0 ) / ( server_steps + 2 );
		interp_pos = interp_start * ( 1.0 - interp ) + interp_end * interp;
		zodiac_model.origin = interp_pos;
		wait 0.05;
	}
	if (!isdefined(level.debug_exit_flight))
	{
		level.sdv_player_arms unlink();		// the arms were linked to the model, we move them to the chinook (for rel anim)
	}

	guys = [];
	guys[ 0 ] = zodiac_model;
	guys[ 1 ] = level.sdv_player_arms;
	guys[ 2 ] = level.ch_guy1;
	guys[ 3 ] = level.ch_guy2;
	guys[ 4 ] = level.sandman;
	
	// for debug start
	zodiac_model Show();
	level.ch_guy1 Show();
	level.ch_guy2 Show();
	level.sandman Show();
	if (isdefined(level.debug_exit_flight))
	{
		level.exit_chinook anim_first_frame( guys, "finale_escape", "tag_guy9" );
	}
	
	level.sdv_player_arms linkto ( level.exit_chinook, "tag_guy9" );
	level.sandman linkto ( level.exit_chinook, "tag_guy9" );
	thread vehicle_scripts\_zodiac_drive::stop_1st_person( level.escape_zodiac );
	thread ally_zodiac_hide();
	level.sdv_player_arms delayCall( 0.2, ::Show );
	thread switch_to_flyout_water();
	level.ch_guy1 delaycall ( 4, ::delete );
	level.escape_zodiac delaycall( 2, ::Delete );  // delete zodiac so it doesn't leave anymore trails (wait to ensure other threads are finished)
	
	//rumble for exit
	level.zodiac_rumble delaythread ( 0.25, ::rumble_ramp_to,  0.3, 0.1 );	
	level.zodiac_rumble delaythread ( 0.65, ::rumble_ramp_to, 0, 0.5 );
	
	aud_send_msg( "mus_finale" );	// if this needs to come earlier, we should add a notetrack
	aud_send_msg( "chinook_finale_escape" );
	org thread anim_single_solo ( level.exit_chinook, "finale_escape" );
	level.exit_chinook anim_single( guys, "finale_escape", "tag_guy9" );
	chinook_exit_node = getstruct ( "chinook_exit", "targetname" );
	wait 0.05;
	level.exit_chinook thread maps\_vehicle::vehicle_paths_helicopter ( chinook_exit_node );
	level.exit_chinook setmaxpitchroll ( 10, 80 );
	level.player PlayerLinkToDelta ( level.sdv_player_arms, "tag_player", 1, 10, 10, 20, 5, true );
	thread escape_flight();
	
	//flag_wait ( "exit_chinook_speedup" );
	//level.exit_chinook Vehicle_SetSpeed ( 80, 20, 20 );
	
	flag_wait ( "exit_chinook_reduce_roll" );
	level.exit_chinook setmaxpitchroll ( 10, 30 );
	
}

ally_zodiac_hide()
{
	wait 5;
	
	level.ally_zodiac hide();
	if (isdefined(level.grinch))	// debugstart support
		level.grinch hide();
	if (isdefined(level.truck))	// debugstart support
		level.truck hide();
	
}
	
escape_flight( )
{
	dvora = spawn_vehicle_from_targetname_and_drive( "last_dvora" );
	//vehicle = spawn_vehicle_from_targetname_and_drive("exit_vehicle");
	wait 0.05;
	
	//vehicle.animname = "ch46e";
//	vehicle thread anim_single_solo( vehicle, "open_rear" );
	//vehicle thread anim_loop_solo( vehicle, "wide_open_rear_loop" );
	
	flag_set("exit_missile_trigger");
	thread missile_timing2();
	thread jet_timings1();
	
	//org = spawn_tag_origin();
	//org linkto(vehicle, "door_rear", (-40,20,10), (-20, 180, 0));  //position: x up/down; y left/right; 
	//level.player PlayerLinkToBlend( org, "tag_origin", 0.2, 0.1, 0.1 );
	//level.player playerlinktodelta(org, "tag_origin", 0.5, 45.0, 45.0 );
	//level.player thread player_reload_silently();
	//level.player EnableWeapons();
	flag_set( "obj_escape_complete" );
	if (isdefined(level.rescue_seaknight2))
		level.rescue_seaknight2 Hide();	// probably should have a path to have it fly out as well
	//if( isDefined( level.rescue_seaknight ) )
		//level.rescue_seaknight hide();
	if (isdefined(level.chinook_model))
		level.chinook_model hide();
	flag_set( "finale_dialogue" );
	flag_wait("view_8");
	//org rotateto((115,0,0), 3, 1, .5);
	
	wait 6;
	ending_fadeout_nextmission();
}

ending_fadeout_nextmission( )
{
	video_fade_time		= 2.0;
	audio_delay_time	= 2.0;
	audio_fade_time		= 6.0;
	level_fade_time		= audio_delay_time + audio_delay_time;
	
	black_overlay = create_client_overlay("black", 0, level.player);
	black_overlay FadeOverTime(video_fade_time);
	black_overlay.alpha = 1;
	
	aud_send_msg("level_fade_to_black", [audio_delay_time, audio_fade_time]);
	
	wait(level_fade_time);
	
	nextmission();
}

spawn_enemies()
{
	spawner = getent( "zodiac_enemy", "targetname" );
	level.zodiac_enemy = spawner spawn_ai(true);
}

show_hidden_ships()
{
	ship1 = getent("ship_to_hide1", "targetname");
	
	ship1 show();
}

ship_squeeze_event()
{
	flag_wait("spawn_hind01");
	heli = spawn_vehicle_from_targetname_and_drive("hind_squeeze");
	aud_send_msg("spawn_ship_squeeze_hind", heli);
	//heli setyawspeed ( 720, 180 );
//	heli2 = spawn_vehicle_from_targetname_and_drive("hind_squeeze2");
	targets = ["hind_targets1", "hind_targets2", "hind_targets3", "hind_targets4", "hind_targets5", "hind_targets6", "hind_targets7", "hind_targets8", "hind_targets9", "hind_targets10", "hind_targets11"];
//	targets2 = ["hind2_targets1", "hind2_targets2", "hind2_targets3", "hind2_targets4", "hind2_targets5", "hind2_targets6", "hind2_targets7", "hind2_targets8", "hind2_targets9", "hind2_targets10", "hind2_targets11"];
//	heli thread fire_missiles(targets);
//	heli delayThread( 2, ::fire_missiles, targets);
//	heli2 delayThread( 1, ::fire_missiles, targets2);
	
/*	flag_wait("swimmers2");
	//self thread fire_missile( "hind_rpg", numRockets, level.player );
	ship = getent("ship_squeeze_ship", "targetname");
	ship2 = getent("ship2_squeeze", "targetname");
	org = getent("ship_squeeze_dest", "targetname");
	org2 = getent("ship2_squeeze_dest", "targetname");
	
	ship moveto (org.origin, 8.75);
	ship rotateto (org.angles, 8.75);
	
	ship2 moveto (org2.origin, 8.75);
	ship2 rotateto (org2.angles, 8.75);
*/

	flag_wait ( "destroy_squeeze_heli" );
	
	wait 2; 
	
	forward = AnglesToForward ( heli.angles );
	org = spawn ( "script_origin", ( 0, 0, 0 ) );
	org.origin = heli.origin - forward * 3000;
	missile = magicbullet ( "tomahawk_missile", org.origin, heli.origin  );
	aud_send_msg("tomahawk_the_hind", missile);
	attractor = missile_createattractorent ( heli, 999999, 999999 );
	
	//heli waittill ( "death" );
	
	//attractor delete();
	
//	while ( true ) 
//	{
//		attractor.origin = heli.origin;
//		wait 0.05;
//	}
	
}

create_attractor()
{
	thing2 = undefined;
	level.generic_attractor = spawn ( "script_origin", (0, 0, 0));
	thing2 = Missile_CreateAttractorEnt( level.generic_attractor, 10000, 999999 );
	
	level.player_head_attractor moveto ((0,0,0), 0.05, 0, 0);
	
}

fire_missiles(targets)
{
	thing = undefined;
	level.generic_attractor = spawn ( "script_origin", (0, 0, 0));
	thing = Missile_CreateAttractorEnt( level.generic_attractor, 10000, 999999 );
	
	foreach (t in targets)
	{
		target = getent(t, "targetname");
		if (isdefined(target))
		{
			level.generic_attractor moveto(target.origin, 1);
			self thread fire_missile( "hind_rpg", 1, target );
		}
		wait .25;
	}
}

make_falling_debris()
{
	flag_wait("debris1");
	thread falling_debris("f15_01", "f15_01_pos1", "f15_01_pos2", 5, 1.5 );
	
}

falling_debris(item, org1, org2, time1, time2)
{
	thing = getent (item, "targetname");
	pos1 = getent(org1, "targetname");
	pos2 = getent(org2, "targetname");
	
	
	thing moveto(pos1.origin, time1, time1/2);
	thing rotateto (pos1.angles, time1, time1/2);
	wait time1;
	thing moveto(pos2.origin, time2, time2/4);
	thing rotateto (pos2.angles, time2, time2/4);
	wait time2;
	thing delete();
}

make_zubrs()
{
	flag_wait( "zubrs" );

	dvora_1 = spawn_vehicle_from_targetname_and_drive( "dvora_1" );
	aud_send_msg("dvora_1", dvora_1);
	dvora_1 thread maps\ny_harbor_fx::surface_dvora_treadfx();
	dvora_2 = spawn_vehicle_from_targetname_and_drive( "dvora_2" );
	aud_send_msg("dvora_2", dvora_2);
	dvora_2 thread maps\ny_harbor_fx::surface_dvora_treadfx();

	flag_wait ( "start_boat_crash" );
	
	dvora_1 delete();
	dvora_2 delete();
	//dvora_1 thread dvora_delete();
	//dvora_2 thread dvora_delete();

}

make_swimmers()
{
	//flag_wait ("swimmers");
	//thread setup_swimmers("harbor_swimmers1", "harbor_surface_floater_dest1");
	flag_wait ("swimmers2");
	//thread setup_swimmers("harbor_swimmers2", "harbor_surface_floater_dest2");
}

make_fallers()
{
	flag_wait ("fallers");
	loc = getent("faller1_dest", "targetname");
	fall_orgs = getentarray ("fallers", "targetname");					//origins for falling guys
	spawner = getent ("bodies_for_falling", "targetname");			//spawner for all fallers
	water_level = loc getorigin();															//this is just an origin slightly beneath the water's surface
	
	while (!flag("swimmers2"))
	{
		foreach (guy in fall_orgs)
		{
			thread setup_fallers(guy, loc, spawner);
			wait 1;
		}
	}
}

make_fallers2()
{
	flag_wait ("fallers2");
	loc = getent("fallers2_water", "targetname");
	fall_orgs = getentarray ("fallers2", "targetname");					//origins for falling guys
	spawner = getent ("bodies_for_falling2", "targetname");			//spawner for all fallers
	water_level = loc getorigin();															//this is just an origin slightly beneath the water's surface
	
	while (!flag("fallers2_end"))
	{
		foreach (guy in fall_orgs)
		{
			thread setup_fallers(guy, loc, spawner);
			wait 1;
		}
	}
}

setup_fallers(org, dest, spawner)
{
	guy = spawner spawn_ai(true);
		guy gun_remove();
		anime = org.animation;
		guy forceTeleport( org.origin, org.angles );
		dummy = maps\_vehicle_aianim::convert_guy_to_drone( guy );
		tagO = spawn_tag_origin();
		tagO.origin = org.origin;
	
		dummy thread anim_generic_loop (dummy, anime, "stop_loop");
		dummy LinkTo(tagO);

	vect = dest getorigin();
	loc = org getorigin();

	falling = true;
	time = 0;

	tagO moveto ((loc[0], loc[1], vect[2]) , 2, 1);

	wait 2;
	dummy delete();
	tagO delete();
}

setup_swimmers(guys, raft)
{
	swimmers = getentarray(guys, "script_noteworthy");
	boat = getent (raft, "targetname");
	
	foreach (swimmer in swimmers)
	{
		org = swimmer getorigin ();
		dest = boat getorigin ();
		dist = distance(swimmer.origin, boat.origin);
		time = dist/52;																					 //i want my guys to swim about 3mph which is about 52 units per second
		swimmer MoveTo (dest, time);
		wait 0.05;
		//forward = AnglesToForward( swimmer.angles );
	}
}

move_the_swimmer(forward)
{
	println(forward);
	dest = self.origin + (forward * 1000);
	time = randomfloatrange(10.0, 15.0);
	self MoveTo (dest, time);
}


setup_floating_bodies()
{
	spawners = getentarray ("bodies_for_harbor", "targetname");
	origns = getentarray ("harbor_surface_floater", "targetname");
	n = 0;
	
	foreach (org in origns)
	{
		guy = spawners[n] spawn_ai(true);
		guy gun_remove();
		anime = org.animation;
		guy forceTeleport( org.origin, org.angles );
		dummy = maps\_vehicle_aianim::convert_guy_to_drone( guy );
		org thread anim_generic_loop (dummy, anime, "stop_loop");
		
		if (n < (spawners.size - 1))
			n++;
		else
		 n = 0;
		wait 0.1;
	}
}

open_seaknight_doors( flg )
{
	flag_wait( flg );
	self.animname = "ch46e";
	self anim_single_solo( self, "open_rear" );
	self anim_loop_solo( self, "open_rear_loop" );
}

start_extraction()
{
	flag_wait( "switch_chinook" );
	chinooks = [];
	chinooks [ 1 ] = level.exit_chinook;
	//chinooks [ 2 ] = level.exit_chinook2;
	
	//level.rescue_seaknight hide();
	
	level.exit_chinook show();
	level.rescue_seaknight2 delete();
	//level.exit_chinook2 show();

	aud_send_msg("show_exit_chinook", level.exit_chinook);
	org = getstruct( "org_finale_escape", "targetname" );
//	level.zodiac_start_ghost = spawn ( "script_model", ( 0, 0, 0 ) );
//	level.zodiac_start_ghost setmodel ( "vehicle_zodiac_boat" );
//	level.zodiac_start_ghost.animname = "player_zodiac";
//	level.zodiac_start_ghost setanimtree();
//	level.zodiac_start_ghost hide();
	
	//set up the chinook crew
	level.ch_guy1 = getent ( "ch_guy1", "targetname" );
	level.ch_guy1.animname = "ch_guy1";
	level.ch_guy1 assign_animtree();
	level.ch_guy1 attach ( "head_tank_a_pilot", "" );
	
	level.ch_guy2 = getent ( "ch_guy2", "targetname" );
	level.ch_guy2.animname = "ch_guy2";
	level.ch_guy2 assign_animtree();
	level.ch_guy2 attach ( "head_tank_b_pilot", "" );
	
	level.ch_guy1 linktoblendtotag (level.exit_chinook, "tag_guy9" );
	level.ch_guy2 linktoblendtotag (level.exit_chinook, "tag_guy9" );
	level.exit_chinook thread anim_loop_solo ( level.ch_guy2, "chinook_idle", "stop_loop", "tag_guy9" );	
	level.exit_chinook thread anim_loop_solo ( level.ch_guy1, "chinook_idle", "stop_loop", "tag_guy9" );
	
	org anim_single( chinooks, "chinook_landing" );
	
	wait 0.05;
	
	org thread anim_loop( chinooks, "chinook_idle" );
	//level.zodiac_start_ghost linkto ( level.chinook_model, "tag_guy9" );
	//level.chinook_model anim_first_frame_solo ( level.zodiac_start_ghost, "finale_escape", "tag_guy9" );
	//level.zodiac_start_point = spawn_tag_origin();
	//level.zodiac_start_point.origin = level.zodiac_start_ghost.origin;
	//level.zodiac_start_point.angles = level.zodiac_start_ghost.angles;
	
}

handle_rescue_seaknight()
{
	println("---------------------------------start helicopter");
	flag_wait( "get_on_zodiac" );
	
	flag_wait ("spawn_chinook");
	
	//spawn water impacts around zodiac
	thread zodiac_water_impacts( "zodiac_stop_mortar2", 0, 1 );
	
	println("---------------------------------spawn helicopter");
	level.treadfx_immediate = true;	// start kicking off dust immediately
	level.rescue_seaknight = spawn_vehicle_from_targetname_and_drive( "rescue_seaknight" );
	level.treadfx_immediate = undefined;
	level.rescue_seaknight.animname = "ch46e2";
	level.rescue_seaknight setanimtree();
	level.rescue_seaknight thread ch46e_animated_rotors();
	
	level.rescue_seaknight2 = spawn_vehicle_from_targetname_and_drive( "rescue_seaknight2" );
	level.rescue_seaknight2.animname = "ch46e2";
	level.rescue_seaknight2 setanimtree();
	level.rescue_seaknight2 thread ch46e_animated_rotors();
	
	aud_send_msg("spawn_flyby_chinook_left", level.rescue_seaknight2);
	aud_send_msg("spawn_flyby_chinook_right", level.rescue_seaknight);	
	
	flag_wait ("spawn_last_zubr");
	//level.last_zubr = spawn_vehicle_from_targetname_and_drive( "last_chaser" );
	

	//level.rescue_seaknight2 thread open_seaknight_doors( "seaknight2_open_doors" );
	//level.rescue_seaknight thread open_seaknight_doors_escape( "switch_chinook" );
	thread start_extraction();

	aud_send_msg( "mus_theres_our_bird" );
	
	// force sandman to be on the left side
	level.sandman.use_auto_pose = undefined;	// no more autoswitch
	level.sandman.scripted_boat_pose = "left";	// force to the left
}

ally_zodiac_wake_control()
{
	flag_wait("ally_zodiac_jumping");
	self ent_flag_clear("tread_active");	// stop the wake before the jump
	self notify("zodiac_treadfx_stop");
	flag_wait("ally_zodiac_landing");
	self ent_flag_set("tread_active");	// turn it back on after we land
	self notify("zodiac_treadfx_go");
}

keep_zodiac_ahead( chaser )
{
	self endon("death");
	chaser endon("death");
	while (level.zodiac_cg == false)
	{
		dist = Distance( self.origin, chaser.origin );
		speed = chaser.veh_speed;
		accel = 10;
		if (flag("ally_zodiac_point_of_no_return") && !flag("ally_zodiac_landing"))
		{	// be sure we get over the jump at speed
			speed = 40;
			accel = 30;
		}
		else if (dist < 1080)
		{	// speedup
			speed = chaser.veh_speed + 5;
			accel = 30;
		}
		else if (dist > 1560)
		{	// slow down
			speed = chaser.veh_speed - 5;
			if (speed < 0)
				speed = 0;
			accel = 20;
		}
		
		else
		{
			if (speed < 10)
				speed = 10;
		}
		self vehicle_setspeed( speed, accel, accel );
		wait 0.05;
	}
}

handle_allies_zodiac()
{
	flag_wait( "get_on_zodiac" );
	
	wait 2.0;
	thread gopath( level.ally_zodiac );
	level.ally_zodiac thread keep_zodiac_ahead( level.escape_zodiac );
	level.ally_zodiac thread ally_zodiac_wake_control();
}

ZODIAC_TREADFX_MOVETIME = .2;
ZODIAC_TREADFX_MOVETIMEFRACTION = 1 / ( ZODIAC_TREADFX_MOVETIME + .05 );
ZODIAC_TREADFX_HEIGHTOFFSET = ( 0, 0, 16 );

zodiac_treadfx_chaser( chaseobj )
{
	// self here is the invisible boat for playing leveled wake fx.
	PlayFXOnTag( getfx( "zodiac_wake_geotrail" ), self, "tag_origin" );
	self NotSolid();
	self Hide();
	self endon( "death" );
	chaseobj endon( "death" );

	// needs to be it's own thread so can cleanup after the thing dies.
	thread zodiac_treadfx_chaser_death( chaseobj );

	chaseobj ent_flag_init( "in_air" );
	chaseobj ent_flag_init( "tread_active" );
	chaseobj ent_flag_set( "tread_active" );

	childthread zodiac_treadfx_stop_notify( chaseobj );
	childthread zodiac_treadfx_toggle( chaseobj );

	while ( IsAlive( chaseobj ) )
	{
//		self DontInterpolate();
		self MoveTo( chaseobj GetTagOrigin( "tag_origin" ) + ZODIAC_TREADFX_HEIGHTOFFSET + ( chaseobj Vehicle_GetVelocity() / ZODIAC_TREADFX_MOVETIMEFRACTION ), ZODIAC_TREADFX_MOVETIME );
		self RotateTo( ( 0, chaseobj.angles[ 1 ], 0 ), ZODIAC_TREADFX_MOVETIME ) ;
		wait ZODIAC_TREADFX_MOVETIME + .05;// + .05 to get rid of silly jiggle at the end when issueing back to back moveto's. Code bug I believe.
		waittillframeend;
	}
	self Delete();
}

zodiac_treadfx_toggle( chaseobj )
{
	chaseobj endon("death");
	active = true;
	prv_active = true;
	prv_in_air = chaseobj ent_flag( "in_air" );
	while ( 1 )
	{
		msg = chaseobj waittill_any_return( "zodiac_treadfx_stop", "zodiac_treadfx_go", "veh_leftground", "veh_landed" );
		
		if ( msg == "veh_leftground" )
			chaseobj ent_flag_set( "in_air" );
		if ( msg == "veh_landed" )
			chaseobj ent_flag_clear( "in_air" );
		if ( msg == "zodiac_treadfx_go" )
			active = true;
		if ( msg == "zodiac_treadfx_stop" )
			active = false;
		in_air = chaseobj ent_flag( "in_air" );
		
		// see if we were previously playing an fx and now we shouldn't be
		if ((prv_active && !prv_in_air) && // we should have been playing an fx
			(!active || in_air) )			// we now shouldn't be playing an fx
			StopFXOnTag( getfx( "zodiac_wake_geotrail" ), self, "tag_origin" );
		else if ((!prv_active || prv_in_air) &&	// we weren't playing an fx
				 (active && !in_air))			// and we should be playing it now
			PlayFXOnTag( getfx( "zodiac_wake_geotrail" ), self, "tag_origin" );
		prv_active = active;
		prv_in_air = in_air;
	}
}

zodiac_treadfx_stop_notify( chaseobj )
{
	chaseobj endon("death");
	while ( 1 )
	{
		vel = chaseobj Vehicle_GetVelocity();
		forward = AnglesToForward( chaseobj.angles );
		dp = VectorDot( vel, forward );
		if ( dp < -10 )
		{	// no treadfx if going in reverse
			if (chaseobj ent_flag( "tread_active" ))
				chaseobj notify( "zodiac_treadfx_stop" );
		}
		else if ( chaseobj Vehicle_GetSpeed() < 4 )
		{
			if (chaseobj ent_flag( "tread_active" ))
				chaseobj notify( "zodiac_treadfx_stop" );
		}
		else if ( ! chaseobj ent_flag( "in_air" ) )
		{
			if (chaseobj ent_flag( "tread_active" ))
				chaseobj notify( "zodiac_treadfx_go" );
		}
		wait .1;
	}
}

zodiac_treadfx_chaser_death( chaseobj )
{
	chaseobj waittill_any( "stop_bike", "death", "kill_treadfx" );
	self Delete();
}

zodiac_treadfx()
{
	chaser = Spawn( "script_model", self.origin );
	chaser SetModel( self.model );
	chaser.angles = ( 0, self.angles[ 1 ], 0 );
	chaser thread zodiac_treadfx_chaser( self );
}

enemy_chase_boat_breadcrumb()
{
	struct = SpawnStruct();
	struct.origin = self.origin;
	struct.angles = flat_angle( self.angles );
	struct.spawn_time = GetTime();
	level.breadcrumb[ level.breadcrumb.size ] = struct;
}

vehicle_dump()
{
	predumpvehicles = GetEntArray( "script_vehicle", "code_classname" );
	vehicles = [];

	// dumping can jump a frame in which the information could be altered, this stores the necessary info real quick
	foreach ( vehicle in predumpvehicles )
	{
		if ( IsSpawner( vehicle ) )
			continue;
		struct = SpawnStruct();
		struct.classname = vehicle.classname;
		struct.origin = vehicle.origin;
		struct.angles = vehicle.angles;
//		struct.spawner_id = vehicle.spawner_id;
		struct.speedbeforepause = vehicle Vehicle_GetSpeed();
		struct.script_VehicleSpawngroup = vehicle.script_vehiclespawngroup;
		struct.script_VehicleStartMove = vehicle.script_vehiclestartmove;
		struct.model = vehicle.model;
		struct.angles = vehicle.angles;
		if ( IsDefined( level.playersride ) && vehicle == level.playersride )
			struct.playersride = true;
		vehicles[ vehicles.size ] = struct;
	}

	fileprint_launcher_start_file();
	fileprint_map_start();

	foreach ( i, vehicle in vehicles )
	{
		origin = fileprint_radiant_vec( vehicle.origin );// convert these vectors to mapfile keypair format
		angles = fileprint_radiant_vec( vehicle.angles );

		fileprint_map_entity_start();
			fileprint_map_keypairprint( "classname", "script_struct" );
			fileprint_map_keypairprint( "model", vehicle.model );
			fileprint_map_keypairprint( "origin", origin );
			fileprint_map_keypairprint( "angles", angles );
			if ( IsDefined( vehicle.speedbeforepause ) )
				fileprint_map_keypairprint( "current_speed", vehicle.speedbeforepause );
			if ( IsDefined( vehicle.script_VehicleSpawngroup ) )
				fileprint_map_keypairprint( "script_vehiclespawngroup", vehicle.script_VehicleSpawngroup );
			if ( IsDefined( vehicle.script_VehicleStartMove ) )
				fileprint_map_keypairprint( "script_vehiclestartmove", vehicle.script_VehicleStartMove );
		fileprint_map_entity_end();
	}
	map_name = level.script + "_veh_ref.map";
	fileprint_launcher_end_file( "/map_source/" + map_name );
	launcher_write_clipboard( map_name );
}

draw_crumb( crumb, lastcrumb, fraction )
{
	if ( !flag( "debug_crumbs" ) )
		return;
	left_spot = crumb.origin + AnglesToRight( crumb.angles ) * -1000 ;
	right_spot = crumb.origin + AnglesToRight( crumb.angles ) * 1000 ;
	color = ( fraction, 1 - fraction, 0 );

	Line( left_spot, right_spot, color );

	if ( !isdefined( lastcrumb ) )
		return;

	left_spot_last = lastcrumb.origin + AnglesToRight( lastcrumb.angles ) * -1000 ;
	right_spot_last = lastcrumb.origin + AnglesToRight( lastcrumb.angles ) * 1000 ;
	Line( left_spot, left_spot_last, color );
	Line( right_spot, right_spot_last, color );
}

zodiac_physics()
{
	self.bigjump_timedelta = 500;
	self.jump_timedelta = 250;
	self.event_time = -1;
	self.event = [];
	self.event[ "jump" ] = [];
	self.event[ "jump" ][ "driver" ] = false;
	self.event[ "jump" ][ "passenger" ] = false;
	self.event[ "bump" ] = [];
	self.event[ "bump" ][ "driver" ] = false;
	self.event[ "bump" ][ "passenger" ] = false;
	self.event[ "bump_big" ] = [];
	self.event[ "bump_big" ][ "driver" ] = false;
	self.event[ "bump_big" ][ "passenger" ] = false;
	self.event[ "sway_left" ] = [];
	self.event[ "sway_left" ][ "driver" ] = false;
	self.event[ "sway_left" ][ "passenger" ] = false;
	self.event[ "sway_right" ] = [];
	self.event[ "sway_right" ][ "driver" ] = false;
	self.event[ "sway_right" ][ "passenger" ] = false;
	self childthread watchVelocity();
	self childthread listen_leftground();
	self childthread listen_landed();
	self childthread listen_jolt();
	self childthread listen_bounce();
	self childthread listen_turn_spray();
//	self thread listen_collision();
}

zodiac_fx( fxName )
{
	tag = "tag_origin";

	if ( IsDefined( level._effect_tag[ fxName ] ) )
		tag = level._effect_tag[ fxName ];

	if ( IsDefined( level._effect[ fxName ] ) )
		PlayFXOnTag( level._effect[ fxName ], self, tag );
		//iprintlnbold( fxName );
//	if ( IsDefined( level.zodiac_fx_sound[ fxname ] ) )
//		thread play_sound_on_entity( level.zodiac_fx_sound[ fxname ] );
		//println( fxName );
}

listen_leftground()
{
	nofx = true;
	self endon( "death" );
	flag_wait( "player_on_boat" );
	for ( ;; )
	{
		self waittill( "veh_leftground" );
		self.event_time = GetTime();
		self.event[ "jump" ][ "driver" ] = true;
		self.event[ "jump" ][ "passenger" ] = true;

		if (!nofx)
			zodiac_fx( "zodiac_leftground" );
	}
}

listen_landed()
{
	self endon( "death" );
	wait 2; // no ignore the land that happens when they spawn above the water.
	flag_wait( "player_on_boat" );
	for ( ;; )
	{
		self waittill( "veh_landed" );
		self.event[ "jump" ][ "driver" ] = false;
		self.event[ "jump" ][ "passenger" ] = false;
		if ( self.event_time + self.bigjump_timedelta < GetTime() )
		{
			self.event[ "bump_big" ][ "driver" ] = true;
			self.event[ "bump_big" ][ "passenger" ] = true;
			if ( ! flag( "player_in_sight_of_boarding" ) )
				thread water_bump( "bump_big" );
			if ( self == level.players_boat )
			{
				zodiac_fx( "player_zodiac_bumpbig" );
				aud_send_msg("zodiac_landed_big");
			}

			else
				zodiac_fx( "zodiac_bumpbig" );
		}
		else if ( self.event_time + self.jump_timedelta < GetTime() )
		{
			self.event[ "bump" ][ "driver" ] = true;
			self.event[ "bump" ][ "passenger" ] = true;
			if ( ! flag( "player_in_sight_of_boarding" ) )
				thread water_bump( "bump" );
			if ( self == level.players_boat )
			{
				zodiac_fx( "player_zodiac_bump" );
				aud_send_msg("zodiac_landed");
			}

			else
				zodiac_fx( "zodiac_bump" );
		}
	}
}

trigger_set_water_sheating_time( bump_small, bump_big )
{
	self waittill( "trigger" );
	set_water_sheating_time( bump_small, bump_big );
}

set_water_sheating_time( bump_small, bump_big )
{
	// duplicated in af_chase_knife_fight_code
	level.water_sheating_time[ "bump" ] = level.water_sheating_time[ bump_small ];
	level.water_sheating_time[ "bump_big" ] = level.water_sheating_time[ bump_big ];
}

water_bump( bumptype )
{
	if ( !isdefined( level.players_boat ) ||  self != level.players_boat )
		return;
	level endon( "missionfailed" );
	if ( flag( "missionfailed" ) )
		return;

	if ( bumptype == "bump_big" )
		level.player PlayRumbleOnEntity( "damage_heavy" );
	else
		level.player PlayRumbleOnEntity( "damage_light" );

	if ( !flag( "no_more_physics_effects" ) )
		level.player SetWaterSheeting( 1, level.water_sheating_time[ bumptype ] );
}

listen_jolt()
{
	self endon( "death" );
	flag_wait( "player_on_boat" );
	for ( ;; )
	{
		self waittill( "veh_jolt", jolt );
		if ( jolt[ 1 ] >= 0 )
		{
			self.event[ "sway_left" ][ "driver" ] = true;
			self.event[ "sway_left" ][ "passenger" ] = true;

			zodiac_fx( "zodiac_sway_left" );
		}
		else
		{
			self.event[ "sway_right" ][ "driver" ] = true;
			self.event[ "sway_right" ][ "passenger" ] = true;

			zodiac_fx( "zodiac_sway_right" );
		}
	}
}

listen_bounce()
{
	nofx = true;
	self endon( "death" );
	flag_wait( "player_on_boat" );

	for ( ;; )
	{
		self waittill( "veh_boatbounce", force );

//		if ( self == level.players_boat )
//			IPrintLnBold( force );

		if ( force < 75.0 )
		{
		}
		else if ( force < 100.0 )
		{
			//PlayFXOnTag( getfx( "zodiac_bounce_small_left" ), self, "TAG_FX_LF" );
			//PlayFXOnTag( getfx( "zodiac_bounce_small_left" ), self, "TAG_FX_RF" );
			zodiac_fx( "zodiac_bounce_small_left" );
			zodiac_fx( "zodiac_bounce_small_right" );
		}
		else
		{
			//PlayFXOnTag( getfx( "zodiac_bounce_large_left" ), self, "TAG_FX_LF" );
			//PlayFXOnTag( getfx( "zodiac_bounce_large_left" ), self, "TAG_FX_RF" );
			zodiac_fx( "zodiac_bounce_large_left" );
			zodiac_fx( "zodiac_bounce_large_right" );
		}
	}
}

listen_turn_spray()
{
    self endon( "death" );
    while ( 1 )
    {
        velocity = self Vehicle_GetBodyVelocity();

        if ( self Vehicle_GetSpeed() > 40 )
        {
            if ( velocity[ 1 ] < -150.0 )
            {
              zodiac_fx( "zodiac_sway_right" );
              aud_send_msg("zodiac_sway_right");            	
            }
            else if ( velocity[ 1 ] > 150.0 )
            {
            	zodiac_fx( "zodiac_sway_left" );
              aud_send_msg("zodiac_sway_left");
            }
        }
        else if ( self Vehicle_GetSpeed() > 10 )
        {
            if ( velocity[ 1 ] < -30.0 )
            {
              zodiac_fx( "zodiac_sway_right_light" );
              aud_send_msg("zodiac_sway_right_light");            	
            }
            else if ( velocity[ 1 ] > 30.0 )
            {
            	zodiac_fx( "zodiac_sway_left_light" );
              aud_send_msg("zodiac_sway_left_light");
            }

        }
        wait .05;
    }
}

listen_collision()
{
	self endon( "death" );

	for ( ;; )
	{
		self waittill( "veh_collision", collision, start_vel );

		foreach ( rider in self.riders )
		{
			if ( IsAlive( rider ) && !isdefined( rider.magic_bullet_shield ) )
			{
//				rider.specialDeathFunc = animscripts\snowmobile::snowmobile_collide_death;
				rider Kill();
			}
		}
		zodiac_fx( "zodiac_collision" );
	}
}

watchVelocity()
{
	self endon( "death" );
	vel = self Vehicle_GetVelocity();
	for ( ;; )
	{
		self.prevFrameVelocity = vel;
		vel = self Vehicle_GetVelocity();
		wait .05;
	}
}

rumble_with_throttle()
{
	rumble_ent = get_rumble_ent();

	throttle_leveling_time = 3.4;

	level_throttle = .01;

	full_throttled_time = 0;

	rumble_fraction = .13;

	while ( 1 )
	{
		throttle = self Vehicle_GetThrottle();

		full_throttled_time += .05;

		if ( throttle < .5 )
		{
			full_throttled_time = 0;
			throttle_level_fraction = 1;
		}
		else
		{
			throttle_level_fraction = 1 - ( full_throttled_time / throttle_leveling_time );
		}

		rumble_ent.intensity = ( throttle * rumble_fraction * throttle_level_fraction );

		if ( full_throttled_time > throttle_leveling_time || self Vehicle_GetSpeed() > 43 )
		{
			full_throttled_time = throttle_leveling_time;// probably not necessary. just keeping the number from going really high.
			rumble_ent.intensity = 0;
		}

		wait .05;
		if ( flag( "player_in_sight_of_boarding" ) )
			break;
	}
	rumble_ent Delete();
}

boatrider_link( vehicle, noblend )
{
	if (isdefined(noblend) && noblend)
	{
		self dontinterpolate();
		self LinkTo( vehicle, "tag_guy2" );
	}
	else
		self LinkToBlendToTag( vehicle, "tag_guy2", false );

}


boatrider_think( vehicle )
{
	boatrider_link( vehicle );

	self AllowedStances( "crouch" );
	self.ignoreAll = false;
	self.vehicle = vehicle;
	self.force_canAttackEnemyNode = true;

	//self thread boatrider_targets();
	self.fullAutoRangeSq = 2000 * 2000;

	// make Price know about all enemies (helps enemy selection when moving fast)
	self.highlyAwareRadius = 2048;

	self AnimCustom( maps\_zodiac_harbor_ai::think );
}

get_guy_on_zodiac( vehicle, bAlreadyOnBoat, noblend )
{
	tag = "tag_guy2";
	self teleport( vehicle getTagOrigin( tag ), vehicle getTagAngles( tag ) );
	if (isdefined(bAlreadyOnBoat) && bAlreadyOnBoat)
	{
		self thread boatrider_link( vehicle, noblend );
		self.vehicle = vehicle;
	}
	else
		self thread boatrider_think(vehicle);

}

get_truck_on_zodiac()
{
	level.truck.forced_startingposition = 0;
	level.truck gun_remove();
	level.ally_zodiac maps\_vehicle_aianim::guy_enter( level.truck );
	level.ally_zodiac thread anim_generic_loop( level.truck, "zodiac_driver_idle", undefined, "tag_driver");
}

load_ally_zodiac()
{
	level.grinch thread get_guy_on_zodiac( level.ally_zodiac );
	get_truck_on_zodiac();
}

get_guys_on_zodiacs()
{
	level.sandman thread get_guy_on_zodiac( level.escape_zodiac );
	load_ally_zodiac();
}

player_reload_silently()
{
	Assert(IsPlayer(self));
	
	weapon = self GetCurrentWeapon();
	if(IsDefined(weapon) && ( weapon != "none" ) )
	{
		class = WeaponClass(weapon);
		if(class != "rocketlauncher" && class != "grenade")
		{			
			current = self GetWeaponAmmoClip(weapon);
			clip = WeaponClipSize(weapon);
			
			if ( level.player GetWeaponAmmoStock ( weapon ) <= clip * 2 )
				level.player SetWeaponAmmoStock ( weapon, clip * 2 );
			
			needed = clip - current;
			stock = self GetWeaponAmmoStock(weapon);
			given = Int(min(needed, stock));
			
			self SetWeaponAmmoClip(weapon, current + given);			
			self SetWeaponAmmoStock(weapon, stock - given);
		}
	}
}

	
zodiac_water_impacts( while_flag, barrage, physics )
{
	org = spawn ( "script_origin", ( 0, 0, 0 ) );
	
	if ( barrage )
	{
		thread zodiac_water_impacts_lateral( "right", while_flag );
		thread zodiac_water_impacts_lateral( "left", while_flag );
	}
	
	while ( !flag ( while_flag ) )
	{
		wait randomintrange ( 3, 6 );
				
		if ( !flag ( while_flag ) )
		{
			//This stuff handles the incoming sound for audio guys to finish later on
			incoming_dur = randomfloatrange( 1.0, 1.5 );
			aud_send_msg("waterbarrage_inc_normal", incoming_dur);
		
			// Wait for incoming sound to play a bit.
			wait( incoming_dur );
		
			forward = AnglesToForward( level.player.angles );
			right = anglestoright ( level.player.angles );
			x = randomfloatrange ( 0, 1 );
			org.origin = level.player.origin + forward * 600 + right * x;
			org.angles = level.player.angles;
			playfx ( level._effect[ "mortarExp_water" ], org.origin );
			thread maps\ny_harbor_fx::surface_waterexp_res(org.origin);
			aud_send_msg("zodiac_water_impacts", org.origin);
			wait 0.90;
//			forward = anglestoforward ( org.angles );
//			org.origin = org.origin - forward * 128;
			
			if ( physics )
				physicsexplosionsphere ( org.origin + ( 0, 0, -42 ), 50, 45, 1.00 );
		}
	}
	
	org delete();
	
}

zodiac_water_impacts_lateral( side, while_flag )
{
	org = spawn ( "script_origin", ( 0, 0, 0 ) );
	
	while ( !flag ( while_flag ) )
	{
		wait randomfloatrange ( 3, 6 );
		
		if ( !flag ( while_flag ) )
		{
			//This stuff handles the incoming sound for audio guys to finish later on
			incoming_dur = randomfloatrange( 1.0, 1.5 );
			aud_send_msg("waterbarrage_inc_lateral", incoming_dur);
		
			// Wait for incoming sound to play a bit.
			wait( incoming_dur );
			
			forward = AnglesToForward( level.player.angles );
			right = anglestoright ( level.player.angles );
			
			if ( side == "left" )
				x = randomfloatrange ( -500, -300 );
			else
				x = randomfloatrange ( 300, 500 );
				
			forward_range = randomfloatrange ( 800, 1500 );
			org.origin = level.player.origin + forward * forward_range + right * x;
			org.angles = level.player.angles;
			playfx ( level._effect[ "mortarExp_water" ], org.origin );
			thread maps\ny_harbor_fx::surface_waterexp_res(org.origin);
			//Play Water explosion sound.
			aud_send_msg("zodiac_water_impacts_lateral", org.origin);
		}
	}
	
	org delete();
	
}

dvora_delete()
{
	self waittill ( "reached_end_node" );
//	foreach ( rider in self.riders )
//	{
//		if ( isdefined ( rider ) && isdefined ( self ) )
//			rider delete();
//	}
	
	self notify ( "stop_fx" );
	
	wait 0.05;
	
	self delete();
	
}
	
//zodiac_music()
//{
//	//temp music call, take this out eventually
//	mus_play ( "nyh_mhtn_blding_cmbt1", 1 );
//	wait 6;
//	mus_play ( "nyh_mhtn_blding_cmbt1_lp", 0.5 );
//	flag_wait ( "finale_dialogue" );
//	mus_play ( "nyh_slava_enter_chopper", 1 );
//	
//}

change_debug_wp_color( name, orgcolor, newcolor, t )
{
	ChangeDebugTextHudColor( name, newcolor );
	while (t > 0)
	{
		dc = orgcolor - newcolor;
		newcolor = newcolor + (0.05/t)*dc;
		ChangeDebugTextHudColor( name, newcolor );
		t -= 0.05;
		wait 0.05;
	}
	ChangeDebugTextHudColor( name, orgcolor );
}

debug_water_patches()
{
	huds = [];
	x = 20;
	y = 20;
	foreach (patch in level.water_patches)
	{
		if (!isdefined(patch.hidden))
			patch.hidden = 0;
		patch.prv_hidden = patch.hidden;
		entnum = patch GetEntityNumber();
		name = "patch"+entnum;
		CreateDebugTextHud(name,x,y);
		y += 18;
	}
	volumes = getentarray( "bobbing_volume", "script_noteworthy");
	foreach (volume in volumes)
	{
		if (!isdefined(volume.hidden))
			volume.hidden = 0;
		volume.prv_hidden = volume.hidden;
	}
	while (true)
	{
		foreach (patch in level.water_patches)
		{
			patch_shown = "+";
			if (isdefined(patch.hidden) && patch.hidden)
				patch_shown = "-";
			entnum = patch GetEntityNumber();
			name = "patch"+entnum;

			text = patch_shown;
			if (isdefined(patch.script_noteworthy))
				text = text + patch.script_noteworthy;
			if (isdefined(patch.targetname))
				text = text + ":" + patch.targetname;
			if (isdefined(patch.target))
			{
				sibling = getent(patch.target, "targetname");
				if (isdefined(sibling))
				{
					sibling_shown = "+";
					if (isdefined(sibling.hidden) && sibling.hidden)
						sibling_shown = "-";
					text = text + " " + sibling_shown;
					if (isdefined(sibling.script_noteworthy))
						text = text + sibling.script_noteworthy;
					if (isdefined(sibling.targetname))
						text = text + ":" + sibling.targetname;
				}
			}
			PrintDebugTextStringHud(name,text);
			if ( patch.prv_hidden != patch.hidden )
				thread change_debug_wp_color( name, (1,1,1), (1,0,0), 2.0 );
			patch.prv_hidden = patch.hidden;
		}
		
		wait 0.05;
	}
}

setup_wp_trigger()
{
	if (!isdefined(self.patches_show))
		self.patches_show = [];
	if (!isdefined(self.patches_hide))
		self.patches_hide = [];
}

setup_water_patch_triggers()
{
	InitBobbingVolumes();
	active_triggers = [];
	level.water_patches = [];
	triggers = getentarray("water_patch_trigger", "script_noteworthy");
	if (isdefined(triggers))
		active_triggers = triggers;
	foreach (trigger in triggers)
	{
		trigger setup_wp_trigger();
	}
	foreach (trigger in triggers)
	{
		if (isdefined(trigger.target))
		{	// the targets are the patches to show
			targets = getentarray( trigger.target, "targetname" );
			assertex(isdefined(targets), "trigger target " + trigger.target + " not referencing anything");
			trigger.patches_show = array_combine_unique( trigger.patches_show, targets );
			level.water_patches = array_combine_unique( level.water_patches, targets );
			
			foreach (target in targets)
			{
				if (isdefined(target.target))
				{	// should point at the patches to hide
					if (target.classname != "info_volume")
					{
						targets2 = getentarray( target.target, "targetname" );
						assertex(isdefined(targets2), "dyn_patch target " + target.target + " not referencing anything");
						trigger.patches_hide = array_combine_unique( trigger.patches_hide, targets2 );
						foreach (target2 in targets2)
						{
							// point it back at the target
							if (!isdefined(target2.parent_targets))
								target2.parent_targets = [];
							target2.parent_targets[target2.parent_targets.size] = target;
							
							if (isdefined(target2.target))
							{ // this should be the triggers to hide the target and show the target2
								triggers2 = getentarray( target2.target, "targetname");
								assertex(isdefined(triggers2), "dyn_patch target " + target2.target + " not referencing anything");
								foreach (trigger2 in triggers2)
								{
									trigger2 setup_wp_trigger();
									trigger2.patches_show = array_combine_unique( trigger2.patches_show, [ target2 ] );
									trigger2.patches_hide = array_combine_unique( trigger2.patches_hide, [ target ] );
									active_triggers = array_combine_unique( active_triggers, [trigger2] );
								}
							}
						}
					}
					else
					{	// info_volumes should point at a trigger 
						{ // this should be the triggers to hide the target and show the target2
							triggers2 = getentarray( target.target, "targetname");
							assertex(isdefined(triggers2), "dyn_patch target " + target.target + " not referencing anything");
							foreach (trigger2 in triggers2)
							{
								trigger2 setup_wp_trigger();
								trigger2.patches_hide = array_combine_unique( trigger2.patches_hide, [ target ] );
								active_triggers = array_combine_unique( active_triggers, [trigger2] );
							}
						}
					}
				}
			}
		}
	}
	// since some volumes might point at a trigger (deactivated by a trigger) without any triggers pointing at it
	// scan the volumes to find any we need to add
	volumes = getentarray("bobbing_volume", "script_noteworthy");
	foreach (volume in volumes)
	{
		if (isdefined(volume.target) && !isdefined(volume.targetname))
		{	// this volume was probably not added
			// info_volumes should point at a trigger 
			// this should be the triggers to hide the target and show the target2
			triggers2 = getentarray( volume.target, "targetname");
			assertex(isdefined(triggers2), "dyn_patch target " + volume.target + " not referencing anything");
			foreach (trigger2 in triggers2)
			{
				trigger2 setup_wp_trigger();
				trigger2.patches_hide = array_combine_unique( trigger2.patches_hide, [ volume ] );
				active_triggers = array_combine_unique( active_triggers, [trigger2] );
			}
		}
	}
	array_thread( active_triggers, ::water_patch_trigger_thread );
//	thread debug_water_patches();
}

water_patch_trigger_thread()
{
	last_trigger = 0;
	trigger_off_time = 100;
	while (true)
	{
		self waittill("trigger");
		if (last_trigger < gettime())
		{
			foreach (ent in self.patches_show)
			{
				if (ent.classname != "info_volume")
				{
					ent Show();
				}
				else
				{
					ent thread ActivateBobbingObjects();
				}
				ent.hidden = false;
			}
			foreach (ent in self.patches_hide)
			{
				if (ent.classname != "info_volume")
				{
					ent Hide();
				}
				else
				{
					ent thread DeactivateBobbingObjects();
				}
				ent.hidden = true;
			}
		}
		last_trigger = gettime() + trigger_off_time;
		wait 0.05;
	}
}

sky_battle()
{
    //sub_flyover jets
    flag_wait ("sub_exit_player_going_out_hatch");
    wait 0.1;
	f15_cb07 = spawn_vehicle_from_targetname_and_drive ("f15_cb07");
	f15_cb07 thread craig_delete_jet();
	aud_send_msg("spawn_f15_fighters_7_8", f15_cb07);
	
	wait 0.2;
	f15_cb08 = spawn_vehicle_from_targetname_and_drive ("f15_cb08");
	f15_cb08 thread craig_delete_jet();
    
    //zodiac_flyover jets
    flag_wait ("fallers");
    wait 0.4;
	f15_cb01 = spawn_vehicle_from_targetname_and_drive ("f15_cb01");
	f15_cb01 thread craig_delete_jet();
	aud_send_msg("spawn_f15_fighters_1_2", f15_cb01);
	
    wait 0.6;
	f15_cb02 = spawn_vehicle_from_targetname_and_drive ("f15_cb02");
	f15_cb02 thread craig_delete_jet();
	
    wait 0.0;
	f15_cb03 = spawn_vehicle_from_targetname_and_drive ("f15_cb03");
	f15_cb03 thread craig_delete_jet();
	
    wait 0.0;
	f15_cb04 = spawn_vehicle_from_targetname_and_drive ("f15_cb04");
	f15_cb04 thread craig_delete_jet();
	aud_send_msg("spawn_f15_fighters_3_4", f15_cb04);

	flag_wait ("spawn_hind01");
    wait 2.5;
	f15_cb05 = spawn_vehicle_from_targetname_and_drive ("f15_cb05");
	f15_cb05 thread craig_delete_jet();
	aud_send_msg("spawn_f15_fighter_5", f15_cb05);
	
	wait 2.5;
	f15_cb06 = spawn_vehicle_from_targetname_and_drive ("f15_cb06");
	f15_cb06 thread craig_delete_jet();
	aud_send_msg("spawn_f15_fighter_6", f15_cb06);
	
	flag_wait ("fallers");
    wait 0.1;
	rescue_seaknight2_cb01 = spawn_vehicle_from_targetname_and_drive ("rescue_seaknight2_cb01");
	rescue_seaknight2_cb01 thread craig_delete_helo();
	
    wait 0.1;
	rescue_seaknight2_cb02 = spawn_vehicle_from_targetname_and_drive ("rescue_seaknight2_cb02");
	rescue_seaknight2_cb02 thread craig_delete_helo();
	
    wait 0.1;
	rescue_seaknight2_cb03 = spawn_vehicle_from_targetname_and_drive ("rescue_seaknight2_cb03");
	rescue_seaknight2_cb03 thread craig_delete_helo();
	
    wait 0.1;
	rescue_seaknight2_cb04 = spawn_vehicle_from_targetname_and_drive ("rescue_seaknight2_cb04");
	rescue_seaknight2_cb04 thread craig_delete_helo();
	
	flag_wait ("start_boat_crash");
    wait 0.5;
	hind_mi24_cb01 = spawn_vehicle_from_targetname_and_drive ("hind_mi24_cb01");
	hind_mi24_cb01 thread craig_delete_helo();
	hind_mi24_cb01 setmaxpitchroll(30,60);
	
	wait 2.6;
	hind_mi24_cb02 = spawn_vehicle_from_targetname_and_drive ("hind_mi24_cb02");
	hind_mi24_cb02 thread craig_delete_helo();
	hind_mi24_cb02 setmaxpitchroll(30,60);
	
	wait 3.7;
	hind_mi24_cb03 = spawn_vehicle_from_targetname_and_drive ("hind_mi24_cb03");
	hind_mi24_cb03 thread craig_delete_helo();
	
	wait 0.2;
	hind_mi24_cb04 = spawn_vehicle_from_targetname_and_drive ("hind_mi24_cb04");
	hind_mi24_cb04 thread craig_delete_helo();
	
	wait 0.5;
	hind_mi24_cb05 = spawn_vehicle_from_targetname_and_drive ("hind_mi24_cb05");
	hind_mi24_cb05 thread craig_delete_helo();
	hind_mi24_cb05 setmaxpitchroll(30,80);
	aud_send_msg("spawn_hind_flyby_5", hind_mi24_cb05);
	
	wait 0.7;
	hind_mi24_cb06 = spawn_vehicle_from_targetname_and_drive ("hind_mi24_cb06");
	hind_mi24_cb06 thread craig_delete_helo();
	hind_mi24_cb06 setmaxpitchroll(30,80);
	aud_send_msg("spawn_hind_flyby_6", hind_mi24_cb06);	
}

craig_delete_helo()
{
    self waittill ( "reached_dynamic_path_end" );
    self delete();
    
}

craig_delete_jet()
{
    self waittill ( "reached_end_node" );
    self delete();
    
}

rotating_radar()
{
	speed = 0;
	time = 20000;

	speed_multiplier = 1.0;
	if( isdefined( self.speed ) )
	{
		speed_multiplier = self.speed;
	}
	
	speed = randomfloatrange( 1*speed_multiplier, 2*speed_multiplier );	// use the speed to really tune

	if( isdefined( self.script_noteworthy ) && (self.script_noteworthy=="lockedspeed") )
		wait 0;
	else
		wait randomfloatrange( 0, 1 );


    while ( true )
    {
       	self rotatevelocity( ( 0, speed, 0 ), time );

        wait time;
    }
}

