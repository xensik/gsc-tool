#include maps\_utility;
#include maps\_hud_util;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;
#include maps\_audio;
#include maps\ny_harbor_code_vo;
#include maps\ny_harbor_code_sub;
#include maps\ny_harbor_code_zodiac;
#include maps\_gameevents;
#include maps\_shg_common;


CONST_MPHTOIPS = 17.6;

//WE USE ORIGINAL
sub_ride_turn_settings_original()
{
	//yaw
	SetSavedDvar( "vehSubmarineYawDampening", "0.90" );				//was 0.86
	SetSavedDvar( "vehSubmarineMaxForwardYawAccel", "30" ); 	//was 45
	SetSavedDvar( "vehSubmarineMaxStoppedYawAccel", "45" ); 	//was 40

	//roll
	SetSavedDvar( "vehSubmarineMaxRollAccel", "30" );					//was 30
	SetSavedDvar( "vehSubmarineMaxRoll", "30" );						//was 45
	SetSavedDvar( "vehSubmarineRollDampening", "0.90" );				//was 0.86
	//pitch
	SetSavedDvar( "vehSubmarineMaxForwardPitchAccel", "20" ); //was 18
	SetSavedDvar( "vehSubmarineMaxStoppedPitchAccel", "20" ); //was 18
	SetSavedDvar( "vehSubmarineMaxUpPitch", "30" ); //was 60
	SetSavedDvar( "vehSubmarineMaxDownPitch", "30" ); //was 60
	SetSavedDvar( "vehSubmarinePitchDampening", "0.90" );				//was 0.86
	
	SetSavedDvar( "vehSubmarinePitchRestore", "0.98" );				//was 0.98
	SetSavedDvar( "vehSubmarineRollRestore", "0.96" );				//was 0.96
	SetSavedDvar( "vehSubmarineMinVelNorestore", "1" );				//was 0.96
	
	SetSavedDvar( "vehSubmarineLateralDampening", "0.99" );				//was 0.96
	
	
	SetSavedDvar( "vehSubmarineBodyRelRotation", "0" );
	SetSavedDvar( "vehSubmarineRollDrivenYaw", "0.0" );
}


sub_ride_turn_settings_standard()
{
	//yaw
	SetSavedDvar( "vehSubmarineYawDampening", "0.92" );				//was 0.96
	SetSavedDvar( "vehSubmarineMaxForwardYawAccel", "90" ); 	//was 40
	SetSavedDvar( "vehSubmarineMaxStoppedYawAccel", "40" ); 	//was 40

	//roll
	SetSavedDvar( "vehSubmarineMaxRollAccel", "80" );					//was 15
	SetSavedDvar( "vehSubmarineMaxRoll", "90" );
	SetSavedDvar( "vehSubmarineRollDampening", "0.95" );				//was 0.96
	//pitch
	SetSavedDvar( "vehSubmarineMaxForwardPitchAccel", "40" ); //was 15
	SetSavedDvar( "vehSubmarineMaxStoppedPitchAccel", "20" ); //was 15
	SetSavedDvar( "vehSubmarineMaxUpPitch", "60" );
	SetSavedDvar( "vehSubmarineMaxDownPitch", "60" );
	SetSavedDvar( "vehSubmarinePitchDampening", "0.92" );				//was 0.98
	
	SetSavedDvar( "vehSubmarinePitchRestore", "0.98" );				//was 0.98
	SetSavedDvar( "vehSubmarineRollRestore", "0.94" );				//was 0.96
	SetSavedDvar( "vehSubmarineMinVelNorestore", "1" );				//was 0.96
	
	SetSavedDvar( "vehSubmarineLateralDampening", "0.99" );				//was 0.96
	
	
	SetSavedDvar( "vehSubmarineBodyRelRotation", "1" );
	SetSavedDvar( "vehSubmarineRollDrivenYaw", "0.0" );
}

sub_ride_turn_settings_afterburner()
{
	//yaw
	SetSavedDvar( "vehSubmarineYawDampening", "0.92" );				//was 0.96
	SetSavedDvar( "vehSubmarineMaxForwardYawAccel", "90" ); 	//was 40
	SetSavedDvar( "vehSubmarineMaxStoppedYawAccel", "40" ); 	//was 40

	//roll
	SetSavedDvar( "vehSubmarineMaxRollAccel", "180" );					//was 15
	SetSavedDvar( "vehSubmarineMaxRoll", "90" );
	SetSavedDvar( "vehSubmarineRollDampening", "0.95" );				//was 0.96
	//pitch
	SetSavedDvar( "vehSubmarineMaxForwardPitchAccel", "40" ); //was 15
	SetSavedDvar( "vehSubmarineMaxStoppedPitchAccel", "20" ); //was 15
	SetSavedDvar( "vehSubmarineMaxUpPitch", "60" );
	SetSavedDvar( "vehSubmarineMaxDownPitch", "60" );
	SetSavedDvar( "vehSubmarinePitchDampening", "0.92" );				//was 0.98
	
	SetSavedDvar( "vehSubmarinePitchRestore", "0.98" );				//was 0.98
	SetSavedDvar( "vehSubmarineRollRestore", "0.94" );				//was 0.96
	SetSavedDvar( "vehSubmarineMinVelNorestore", "1" );				//was 0.96
	
	SetSavedDvar( "vehSubmarineLateralDampening", "0.99" );				//was 0.96
	SetSavedDvar( "vehSubmarineMaxLateralVel", "60" );					//was 20
	
	SetSavedDvar( "vehSubmarineBodyRelRotation", "5" );
	SetSavedDvar( "vehSubmarineRollDrivenYaw", "2.0" );
}

sub_ride_init()
{
	level.max_chase_speed = 285;
	SetSavedDvar( "vehSubmarineControls", "2" ); //was 1
	SetSavedDvar( "vehSubmarineMaxReverseAccel", "20" );			// was 0
	SetSavedDvar( "vehSubmarineMaxPositiveBuoyancy", "0" );		// don't allow buoyancy up
	SetSavedDvar( "vehSubmarineMaxNegativeBuoyancy", "0" );		// don't allow buoyancy down
	SetSavedDvar( "vehSubmarineMaxForwardAccel", "125" );		// was 350

	sub_ride_turn_settings_original();

	// these are only used in a dev block, but if I wrap them in a dev block, the call below doesn't see them as declared
	org_pitchclamp = getdvarfloat("vehCam_pitchClamp");
	org_yawclamp = getdvarfloat("vehCam_yawClamp");

	// we'll setup view clamping here, so a control mode change later may not setup the view clamping correctly
	if (getdvarint("vehSubmarineControls") == 2)
	{
		SetSavedDvar( "vehCam_pitchClamp", "0.1" );
		SetSavedDvar( "vehCam_yawClamp", "0.1" );
	}
	
	if( getdvarint( "vehSubmarineControls" ) == 1 )
	{
		thread monitor_inversion_change();
		SetSavedDvar( "vehCam_pitchClamp", "0.1" );
		SetSavedDvar( "vehCam_yawClamp", "0.1" );
	}
	
	thread post_tunnel_setup();
/#
	//thread wait_for_sdv_control_change(org_pitchclamp, org_yawclamp);
#/	
}

monitor_inversion_change()
{
	level endon( "submine_planted" );
	
	while( 1 )
	{
		if( isdefined( level.player GetLocalPlayerProfileData( "invertedPitch" ) ) && level.player GetLocalPlayerProfileData( "invertedPitch" ) )
		{
			SetSavedDvar( "vehSubmarineInvertUpDown", 0 );
		}
		else
		{
			SetSavedDvar( "vehSubmarineInvertUpDown", 1 );
		}
		wait( 0.5 );
	}
}

float2str( flt )
{
	return "" + flt;
}

AlterFloatSavedDvar( dvar, fraction )
{
	if (!isdefined(level._saved_dvars[dvar]))
	{
		level._saved_dvars[dvar] = GetDvarFloat( dvar );
	}
	val = fraction * level._saved_dvars[dvar];
	SetSavedDvar( dvar, float2str(val));
}

/#
wait_for_sdv_control_change(org_pitchclamp, org_yawclamp)
{
	curmode = getdvarint("vehSubmarineControls");
	while (true)
	{
		mode = getdvarint("vehSubmarineControls");
		if (mode != curmode)
		{
			curmode = mode;
			if (curmode <= 1)
			{
				SetSavedDvar( "vehCam_pitchClamp", org_pitchclamp );
				SetSavedDvar( "vehCam_yawClamp", org_yawclamp );
			}
			else
			{
				SetSavedDvar( "vehCam_pitchClamp", "0.1" );
				SetSavedDvar( "vehCam_yawClamp", "0.1" );
			}
		}
		wait 1.0;
	}
}
#/

rotate_tunnel_fans()
{
	top_fan = getent( "tunnel_fan_top", "targetname" );
	bottom_fan = getent( "tunnel_fan_bottom", "targetname" );
	
	top_fan thread rotate_fan();
	bottom_fan thread rotate_fan();
}

rotate_fan()
{
	level endon( "russian_sub_event" );
	while( 1 )
	{
		self RotateVelocity( ( 0, 10, 0 ), 60 );
		wait( 60 );
	}
}

TeleportAndRepath( name, bRepath)
{
	if (!isdefined(bRepath))
		bRepath = true;
	node = getvehiclenode( name+"_watch_spot", "script_noteworthy" );
	angles = node.angles;
	if (isdefined(self.target))
	{
		// get the angles from the previous node's origin to this node's origin
		start = self.target;
		curnode = undefined;
		prvnode = undefined;
		while (true)
		{
			prvnode = curnode;
			curnode = getvehiclenode( start, "targetname" );
			if (curnode == node)
				break;
			start = curnode.target;
		}
		dir = curnode.origin - prvnode.origin;
		angles = VectorToAngles(dir);
	}
	self Vehicle_Teleport( node.origin, angles );
	if (bRepath)
	{
		self attachpath( node );
		self thread vehicle_paths( node );
		self thread gopath();	// expect a wait at start
	}
}

player_entering_water( bStartAtWatch )
{
	if (!isdefined(bStartAtWatch))
		bStartAtWatch = false;
	sub_ride_init();
	flag_wait("entering_water");
	
	// sdvarray includes all sdvs
	level.sdvarray [0] = level.lead_sdv;
	level.sdvarray [1] = level.sdv02;
	level.sdvarray [2] = level.sdv03;
	//level.sdvarray [3] = level.sdv04;
	level.sdvarray [3] = level.grinch_sdv;
	level.sdvarray [4] = level.sdv06;
	//level.sdvarray [6] = level.other_sdv01;
	level.sdvarray [5] = level.other_sdv02;
	level.sdvarray [6] = level.player_sdv;
	
	// sdvarray_alt holds the sdvs that we need to spawn actors for (non-hero)
	level.sdvarray_alt [0] = level.sdv02;
	level.sdvarray_alt [1] = level.sdv03;
	//level.sdvarray_alt [2] = level.sdv04;
	level.sdvarray_alt [2] = level.sdv06;
	//level.sdvarray_alt [4] = level.other_sdv01;
	level.sdvarray_alt [3] = level.other_sdv02;
	
	if ( bStartAtWatch )
	{	// move all of the sdvs to where they need to be for this debug_start
		level.sdv02 thread TeleportAndRepath("sdv02");
		level.sdv03 thread TeleportAndRepath("sdv03");
	//	level.sdv04 thread TeleportAndRepath("sdv04");
		level.sdv06 thread TeleportAndRepath("sdv06");
		//level.other_sdv01 thread TeleportAndRepath("other_sdv01");
		level.other_sdv02 thread TeleportAndRepath("other_sdv02");
		level.grinch_sdv thread TeleportAndRepath("grinches");
		level.lead_sdv thread TeleportAndRepath("sandman");
		level.player_sdv thread TeleportAndRepath("players", false);
	}

	foreach (sdv in level.sdvarray_alt)
	{
			sdv ent_flag_clear( "lights" );	// lights are off for everyone for now
	}
	
	
	// kill the rumble on all but the player
	foreach (sdv in level.sdvarray)
	{
		sdv.dontunloadonend = true;
		if (sdv != level.player_sdv)
		{
			sdv notify("kill_rumble_forever");
		}
		thread setup_sdv_threads (sdv);
	}
	level.player_sdv thread maps\ny_harbor_sdv_drive::Sonar_Process();
//	level.player_sdv thread maps\ny_harbor_sdv_drive::UpdateSDVHUD();

//	ge_FlushEvents( "fx", "ambientsurface" );	// flush any fx events for ambient surface
	
	underwater_hud_enable(true);
	below_water_art_and_ambient_setup( undefined, bStartAtWatch );
	thread control_sdv_lights();
	thread wait_for_vd_fogvision();
	level.player_sdv thread wait_player_enter( bStartAtWatch );
	level.lead_sdv thread maps\ny_harbor_sdv_drive::update_sub_dyn_coll();
	level.grinch_sdv thread maps\ny_harbor_sdv_drive::update_sub_dyn_coll();
	
	//****Ambient Events****************************************************************
	thread submarine_spawn02();
	thread populate_floaters();
	
	if (!bStartAtWatch)
	{
		thread vision_set_fog_changes("ny_harbor_tunnel",0);
		//thread vo_wetsub_intro(4);
		thread sinking_ship();
	}
	
	thread monitor_player_and_russian_sub();
	level.ally_sdv_mode = 0;
	thread hide_surface_ships( true );
	thread hide_zodiac_ships();
}

cleanup_after_sdv_ride()
{
	level notify("sdv_ride_done");
	foreach (sdv in level.sdvarray)
	{
		if (isdefined(sdv.realtime_light_tag))
		{
			sdv.realtime_light_tag Delete();
		}
		if (isdefined(sdv.pilot))
		{
			sdv.pilot notify("sdv_done");
		}
		sdv notify("sdv_done");
	}
	level.sdvarray = undefined;
	level.player_sdv = undefined;
}

hide_zodiac_ships()
{
	ship1 = getent("ship_to_hide1", "targetname");
	ship1 hide();
}

populate_floaters()
{
	nodes = getentarray("harbor_floaters", "targetname");
	spawner = getent("spawner_harbor_floaters", "targetname");
	
	level.harbor_floaters = [];	
	foreach (node in nodes )
	{
		//println("**************************floaters=  " + nodes.size);
		//println("**************************animation=  " + node.animation);
		guy = spawner spawn_ai(true);
		guy gun_remove();
		guy SetModel( "body_city_civ_male_a" );
		anime = node.animation;
		guy forceTeleport( node.origin, node.angles );
		dummy = maps\_vehicle_aianim::convert_guy_to_drone( guy );
		dummy notsolid();
		level.harbor_floaters[ level.harbor_floaters.size ] = dummy;
		node thread anim_generic_loop (dummy, anime, "stop_loop");
		wait 0.5;
	}

	thread cleanup_floaters();
}

cleanup_floaters()
{
	flag_wait( "submine_planted" );
	foreach (dummy in level.harbor_floaters)
		dummy Delete();
	level.harbor_floaters = undefined;
}


sinking_ship()
{
	boat = getent("sinking_ship", "targetname");
	boat hide();
	flag_wait( "show_sinking_ship" );
	boat show();
	dest_org = getent("sinking_ship_destination", "targetname");
	
	level.fx_dummy = spawn_tag_origin();
	level.fx_dummy.origin = boat.origin;
	level.fx_dummy.angles = boat.angles;
	flag_wait ("start_sinking");
	
	//fall_time = 58.75;
	fall_time = 20;
	dest = dest_org getOrigin ();
	nx = randomfloatrange(-1.0,1.0);
	ny = randomfloatrange(-1.0,1.0);
	nz = randomfloatrange(-1.0,1.0);
	
	boat RotateTo ((dest_org.angles), fall_time);
	boat MoveTo (dest, fall_time);
	
	level.fx_dummy RotateTo ((dest_org.angles), fall_time);
	level.fx_dummy MoveTo (dest, fall_time);
	
	aud_data = [boat, fall_time, dest_org];
	aud_send_msg("underwater_battleship_sink", aud_data);
	
	// hide destroyer so it doesn't poke out of the water during sub breach
	flag_wait( "submine_planted" );
	level.fx_dummy Delete();
	boat hide();	// could just delete it at this point
}

water_depth_of_field( enable )
{
	if (!isdefined(level.water_dof_active))
	{
		level.water_dof_active = false;
		level.orgDofDefault = level.dofDefault;
	}
	
	if (level.water_dof_active == enable)
		return;
	level.water_dof_active = enable;
	
	dof_water = [];
	dof_water[ "nearStart" ] = .1;
	dof_water[ "nearEnd" ] = .2;
	dof_water[ "nearBlur" ] = 4.0;
	dof_water[ "farStart" ] = 150;
	dof_water[ "farEnd" ] = 1000;
	dof_water[ "farBlur" ] = 1.8;
	 
	if (enable)
		blend_dof( level.orgDofDefault, dof_water, 1.2 );
	else
		blend_dof( dof_water, level.orgDofDefault, 2.0 );
}



handle_sdv_ais()
{
	// spawn all of the ais, attach them to their sdvs and start a think on them
	pilotidx = 1;
	spawner = getent("spawner_for_sdvs", "targetname");
	
	foreach (sdv in level.sdvarray_alt)
	{
		pilot = spawner spawn_ai(true);
		level.sub_pilots[pilotidx] = pilot;
		level.sub[pilotidx] = sdv;
		pilot gun_remove();
		pilot thread sdv_ai_think(sdv);
		pilotidx += 1;
		wait 0.05;
	}
	//level.sandman hide();
	//level.truck hide();
	//level.grinch hide();
}

handle_hero_sdvs( bStartAtWatch )
{
	sandman = getent( "sdv_sandman", "targetname" );
	grinch = getent( "sdv_grinch", "targetname" );
	
	level.sdv_sandman = sandman spawn_ai( true );
	level.sdv_sandman.targetname = "sdv_sandman_ai";	// helps debugging
	level.sdv_grinch = grinch spawn_ai( true );
	level.sdv_grinch.targetname = "sdv_grinch_ai";	// helps debugging
	
	flag_set( "npcs_spawned" );
	
	level.sdv_sandman gun_remove();
	level.sdv_sandman.animname = "lonestar";
	level.sdv_grinch gun_remove();
	level.sdv_grinch.animname = "grinch";
	
	if (!bStartAtWatch)
	{
		play_tunnel_intro();
	}
}

allow_player_to_lookaround_during_tunnel_intro()
{
	level.player PlayerLinkToDelta( level.sdv_player_arms, "tag_player", 1.0, 0, 0, 0, 0, true );
	level.player LerpViewAngleClamp( 3, 0.5, 0.5, 15, 15, 15, 15 );
	level.player enableslowaim();
}

ssao_on_pc()
{
	if (!level.console) setsaveddvar("r_ssaostrength", 1.2);
}

ssao_off_pc()
{
	if (!level.console) setsaveddvar("r_ssaostrength", 0);
}




blur_on_pc()
{
	if (!level.console) setsaveddvar("r_floatzClearToThreshold", 1);
}

blur_off_pc()
{
	if (!level.console) setsaveddvar("r_floatzClearToThreshold", 0);
}

play_tunnel_intro()
{
	flag_init( "stop_torch_fx" );
//	flag_init( "player_tunnel_spline" );

	level.player thread fix_stances();
	
	org = getstruct( "org_tunnel_anim", "targetname" );
  // Since it looks like compression is causing a slight offset at the end, we manually compensate here
	angles = (0,151,0);
	right = AnglesToRight(angles);
	offset = 0.25;
	sdvorg = spawnstruct();
	sdvorg.origin = org.origin + offset*right;
	sdvorg.angles = org.angles;
	
	sdv = level.lead_sdv;
	sdv.animname = "blackshadow";
	
	grate = spawn_anim_model( "tunnel_grate" );
	grate.animname = "tunnel_grate";
	
	torch = spawn_anim_model( "torch" );
	torch.animname = "torch";
	
	level.sdv_player_arms.not_driving = true;
	level.player disableWeapons();
	player_sdv = level.player_sdv;
	player_sdv.animname = "player_sdv";
	
	thread blur_on_pc();
	thread ssao_off_pc();
	
	guys = [];
	guys[ 0 ] = level.sdv_sandman;
	guys[ 1 ] = sdv;
	guys[ 2 ] = grate;
	guys[ 3 ] = torch;
	player_array = [];
	player_array[ 0 ] = level.sdv_player_arms;
	player_array[ 1 ] = player_sdv;
//player_sdv thread draw_tag_axis( "tag_player" );
//level.sdv_player_arms thread draw_tag_axis( "tag_player" );
//level.sdv_player_arms thread draw_ent_axis( );

	flag_wait( "level_fade_done" );
	
	level.sdv_player_arms thread maps\ny_harbor_fx::intro_player_bubble_fx();
	level.sdv_sandman thread maps\ny_harbor_fx::intro_npc_bubble_fx();
	thread maps\ny_harbor_fx::torch_flare_fx();
	thread maps\ny_harbor_fx::torch_contrast();
	thread maps\ny_harbor_fx::intro_vision_reveal();
	thread maps\ny_harbor_fx::torch_grating_rays();
	thread maps\ny_harbor_fx::ny_harbor_intro_metal_glow();	
	thread maps\ny_harbor_fx::ny_harbor_intro_dof();
	thread maps\ny_harbor_fx::ny_harbor_intro_specular();
	grate thread maps\ny_harbor_fx::bubble_on_falling_grate();
	
	//blinky lights
	array_thread( GetEntArray( "ny_harbor_tunnel_sign_blinky", "targetname" ), maps\ny_harbor_fx::ny_harbor_tunnel_sign_blinky );
	
//removed cab toplight using model swap and trying via light flicker
//	array_thread( GetEntArray( "taxi_rooftop_ad_2_blinky", "targetname" ), maps\ny_harbor_fx::ny_harbor_tunnel_taxi_rooftop_ad_blinky );
//	array_thread( GetEntArray( "taxi_rooftop_ad_2_blinky_base", "targetname" ), maps\ny_harbor_fx::ny_harbor_tunnel_taxi_rooftop_ad_blinky_base );
	
	level.player PlayerLinkToBlend( level.sdv_player_arms, "tag_player", 0.4, 0.2, 0.2 );
	delaythread( 2, ::allow_player_to_lookaround_during_tunnel_intro);
	level.sdv_player_arms delayCall( 0.2, ::Show );
	
	torch delaythread( 13, ::delete_torch );
	level.sdv_grinch delaythread( 15, ::sdv_ai_think, level.grinch_sdv );
	level.grinch_sdv delaythread( 23, ::gopath, level.grinch_sdv );
	thread turn_torch_off();
	torch thread torch_fx();
	org thread anim_single_solo( player_array[0], "tunnel_intro" );
	sdvorg thread anim_single_solo( player_array[1], "tunnel_intro" );
	org anim_single( guys, "tunnel_intro" );
	flag_set( "tunnel_anim_finished" );
	sdv StopAnimScripted();
	level.sdv_sandman thread sdv_ai_think( level.lead_sdv );
	level.lead_sdv thread gopath( level.lead_sdv );
	thread sdv_tutorial();
	// freeze the anims on the player_array things
	for (i=0; i<2; i++)
	{
		anm = player_array[i] GetAnim("tunnel_intro");
		player_array[ i ] SetAnim( anm, 1.0, 0.0, 0.0 );
	}
	
	level.player LerpViewAngleClamp( 1.0, 0.2, 0.2, 0,0,0,0);	// get us centered smoothly
	//flag_wait( "player_tunnel_spline" );
	aud_send_msg("mus_intro");	
	// let the anims on the player_array things run
	for (i=0; i<2; i++)
	{
		anm = player_array[i] GetAnim("tunnel_intro");
		player_array[ i ] SetAnim( anm, 1.0, 0.0, 1.0 );
	}
	anm = player_array[0] GetAnim("tunnel_intro");
	
	while (player_array[0] GetAnimTime( anm ) != 1.0)
	{
//		if (player_array[0] GetAnimTime( anm ) < 0.85)
//			level notify ("bubble_wash_player_out_gate"); 
		wait 0.05;
	}
	flag_set( "player_out_of_vent" );
	autosave_by_name( "player_out_of_vent" );
	level.sdv_player_arms.not_driving = undefined;
	
	grate thread wait_to_delete_grate();

	level notify("msg_fx_intro_end");
}

wait_to_delete_grate()
{
	level.player endon( "death" );
	flag_wait( "submine_planted" );
	self Delete();
}

fix_stances()
{
	level.player AllowCrouch( false );
	level.player AllowProne( false );
	level.player AllowJump( false );
	level.player AllowSprint( false );
	
	flag_wait( "sub_breach_finished" );
	
	level.player AllowCrouch( true );
	level.player AllowProne( true );
	level.player AllowJump( true );
	level.player AllowSprint( true );
}

delete_torch()
{
	self delete();
}

draw_lstick_hint( offset, shader )
{
	MYFADEINTIME = 1.0;
	MYFLASHTIME = 0.75;
	MYALPHAHIGH = 0.95;
	MYALPHALOW = 0.4;
	Hint = NewHudElem();
	Hint.alpha = 0.9;
	Hint.x = offset;
	Hint.y = -68;
	Hint.alignx = "center";
	Hint.aligny = "middle";
	Hint.horzAlign = "center";
	Hint.vertAlign = "middle";
	Hint.foreground = false;
	Hint.hidewhendead = true;
	Hint.hidewheninmenu = true;

	Hint SetShader( shader, 40, 20 );
	level.stick_hint = Hint;

	Hint.alpha = 0;
	Hint FadeOverTime( MYFADEINTIME );
	Hint.alpha = MYALPHAHIGH;
	wait MYFADEINTIME;
	for ( i = 0; i < 1; i++ )
	{
		Hint FadeOverTime( MYFLASHTIME );
		Hint.alpha = MYALPHALOW;
		wait MYFLASHTIME;

		Hint FadeOverTime( MYFLASHTIME );
		Hint.alpha = MYALPHAHIGH;
		wait MYFLASHTIME;
	}
	hint notify( "destroying" );
	Hint Destroy();
	level.stick_hint = undefined;
}

monitor_stick_hint( offset )
{
	config = GetSticksConfig();
	cur_hint_shader = "lstick";
	if (issubstr(config,"southpaw"))
		cur_hint_shader = "rstick";
	
	thread draw_lstick_hint( offset, cur_hint_shader );
	while (isdefined(level.stick_hint))
	{
		newconfig = GetSticksConfig();
		if (newconfig != config)
		{
			config = newconfig;
			cur_hint_shader = "lstick";
			if (issubstr(config,"southpaw"))
				cur_hint_shader = "rstick";
			level.stick_hint SetShader(cur_hint_shader, 40, 20);
		}
		wait 0.05;
	}
}

draw_stick_hint( record, offset, shader )
{
	MYFADEINTIME = 1.0;
	MYFLASHTIME = 0.75;
	MYALPHAHIGH = 0.95;
	MYALPHALOW = 0.4;
	Hint = NewHudElem();
	Hint.alpha = 0.9;
	Hint.x = offset;
	Hint.y = -68;
	Hint.alignx = "center";
	Hint.aligny = "middle";
	Hint.horzAlign = "center";
	Hint.vertAlign = "middle";
	Hint.foreground = false;
	Hint.hidewhendead = true;
	Hint.hidewheninmenu = true;

	Hint SetShader( shader, 40, 20 );

	Hint.alpha = 0;
	Hint FadeOverTime( MYFADEINTIME );
	Hint.alpha = MYALPHAHIGH;
	record.hint = Hint;
	
	wait MYFADEINTIME;
	for ( i = 0; i < 1; i++ )
	{
		Hint FadeOverTime( MYFLASHTIME );
		Hint.alpha = MYALPHALOW;
		wait MYFLASHTIME;

		Hint FadeOverTime( MYFLASHTIME );
		Hint.alpha = MYALPHAHIGH;
		wait MYFLASHTIME;
	}
	hint notify( "destroying" );
	Hint Destroy();
	record.hint = undefined;
}


controller_stick_hint( hint_string, useIcons )
{
	config = GetSticksConfig();
	cur_flavor = "";
	if (issubstr(config,"southpaw"))
		cur_flavor = "_l";
	
	cur_hint_string = hint_string+cur_flavor;
	thread display_hint( cur_hint_string );
	if (!isdefined(useIcons))
	{
		while (isdefined(level.current_hint))
		{
			newconfig = GetSticksConfig();
			if (newconfig != config)
			{
				config = newconfig;
				cur_flavor = "";
				if (issubstr(config,"southpaw"))
					cur_flavor = "_l";
				cur_hint_string = hint_string+cur_flavor;
				locstrng = level.trigger_hint_string[ cur_hint_string ];
				level.current_hint SetText(locstrng);
			}
			wait 0.05;
		}
	}
	else
	{	// just use icons for the two sticks and swap them if needed
		accel_offset = -111;
		steer_offset = 78;
		accel_shader = "lstick";
		steer_shader = "rstick";
		config = GetSticksConfig();
		if (issubstr(config,"southpaw"))
		{
			accel_shader = "rstick";
			steer_shader = "lstick";
		}
		accel_icon = spawnstruct();
		thread draw_stick_hint( accel_icon, accel_offset, accel_shader );
		steer_icon = spawnstruct();
		thread draw_stick_hint( steer_icon, steer_offset, steer_shader );
		while (isdefined(level.current_hint))
		{
			newconfig = GetSticksConfig();
			if (newconfig != config)
			{
				config = newconfig;
				accel_shader = "lstick";
				steer_shader = "rstick";
				if (issubstr(config,"southpaw"))
				{
					accel_shader = "rstick";
					steer_shader = "lstick";
				}
				if (isdefined(accel_icon.hint))
					accel_icon.hint SetShader( accel_shader, 40, 20 );
				if (isdefined(steer_icon.hint))
					steer_icon.hint SetShader( steer_shader, 40, 20 );
			}
			wait 0.05;
		}
	}
}

controller_config_hint( hint_string, offset )
{
	cur_flavor = GetThrottleFlavor();
	cur_hint_string = hint_string+cur_flavor;
	thread display_hint( cur_hint_string );
	if (isdefined(offset) && level.console)
	{
		thread monitor_stick_hint( offset );
	}
	while (isdefined(level.current_hint))
	{
		new_flavor = GetThrottleFlavor();
		if (new_flavor != cur_flavor)
		{
			cur_flavor = new_flavor;
			cur_hint_string = hint_string+cur_flavor;
			locstrng = level.trigger_hint_string[ cur_hint_string ];
			level.current_hint SetText(locstrng);
		}
		wait 0.05;
	}
}

sdv_tutorial()
{
	flag_set( "aud_player_tunnel_spline" );
	
	if (level.console)
	{
		if (GetDvar("vehSubmarineControls") == "2")
		{
			//thread controller_stick_hint( "hint_sdv_drive_2_stick" );
			//thread move_player_out_of_vent();
			flag_wait( "player_out_of_vent" );
			if (level.ps3)
				thread controller_stick_hint( "hint_sdv_drive_3_stick" );
			else
				thread controller_stick_hint( "hint_sdv_drive_3_stick" );
		}
		else
		{
			hint_string = "hint_sdv_drive_2";
			//thread controller_config_hint( hint_string );
			//thread move_player_out_of_vent();
			flag_wait( "player_out_of_vent" );
			hint_string = "hint_sdv_drive_3";
			thread controller_config_hint( hint_string, 70 );
		}
	}
	else
	{
		//thread display_hint( "hint_sdv_drive_2" );
		//thread move_player_out_of_vent();
		flag_wait( "player_out_of_vent" );
		thread display_hint( "hint_sdv_drive_3" );
	}
}

ThrottleButtonPressedXenon_cb( veh )
{
	if (isdefined(veh) && (veh == "sdv") && (getdvar("vehSubmarineControls") == "2"))
	{
		input = level.player GetNormalizedMovement();
		if (input[0] > 0)
			return 1;
		return 0;
	}
	// ugly way to ensure we always get right trigger
	cmd = getCommandFromKey( "BUTTON_RTRIG" );
	if ((cmd == "+attack") || (cmd == "+attack_akimbo_accessible"))
		return self AttackButtonPressed();
	else
		return self AdsButtonPressed();
}

GetThrottleFlavorXenon_cb( veh )
{
	cmd = getCommandFromKey( "BUTTON_RTRIG" );
	if ((cmd == "+attack") || (cmd == "+attack_akimbo_accessible"))
		return "";
	else if (cmd == "+speed_throw")
		return "_1";
	else if (cmd == "+frag")
		return "_2";
	else if (cmd == "+smoke")
		return "_3";
}

ThrottleButtonPressedPS3_cb( veh )
{
	if (isdefined(veh) && (veh == "sdv") && (getdvar("vehSubmarineControls") == "2"))
	{
		input = level.player GetNormalizedMovement();
		if (input[0] > 0)
			return 1;
		return 0;
	}
	// ugly way to ensure we always get right trigger
	cmd = getCommandFromKey( "BUTTON_RSHLDR" );
	if ((cmd == "+attack") || (cmd == "+attack_akimbo_accessible"))
		return level.button_pressed[0];
	else if (cmd == "+speed_throw")
		return level.button_pressed[1];
	else if (cmd == "+frag")
		return level.button_pressed[2];
	else if (cmd == "+smoke")
		return level.button_pressed[3];
}

GetThrottleFlavorPS3_cb()
{
	cmd = getCommandFromKey( "BUTTON_RSHLDR" );
	if ((cmd == "+attack") || (cmd == "+attack_akimbo_accessible"))
		return "";
	else if (cmd == "+speed_throw")
		return "_1";
	else if (cmd == "+frag")
		return "_2";
	else if (cmd == "+smoke")
		return "_3";
}

ThrottleButtonPressedPC_cb( veh )
{
	return level.button_pressed[0];
}

GetThrottleFlavorPC_cb()
{
	return "";
}

ThrottleButtonPressed( veh )
{
	return self [[ level.throttle_pressed_fnc ]]( veh );
}

GetThrottleFlavor()
{
	return self [[ level.throttle_flavor_fnc ]]();
}

monitor_command( cmd, bp_index, bp_value)
{
	while (true)
	{
		self waittill( cmd );
		level.button_pressed[ bp_index ] = bp_value;
	}
}

setup_button_monitor( name, bp_index )
{
	level.button_pressed[bp_index] = 0;
	notifyOnCommand( name+"_pressed", "+"+name );
	level.player thread monitor_command(name+"_pressed",bp_index,1);
	notifyOnCommand( name+"_released", "-"+name );
	level.player thread monitor_command( name+"_released",bp_index,0);
}

setup_throttle_button()
{
	level.throttle_pressed_fnc = ::ThrottleButtonPressedXenon_cb;
	level.throttle_flavor_fnc = ::GetThrottleFlavorXenon_cb;
	if (!level.console)
	{	// PC
		setup_button_monitor( "forward", 0 );
		level.throttle_pressed_fnc = ::ThrottleButtonPressedPC_cb;
		level.throttle_flavor_fnc = ::GetThrottleFlavorPC_cb;
	}
	else if (level.ps3)
	{
		setup_button_monitor( "attack", 0 );
		setup_button_monitor( "speed_throw", 1 );
		setup_button_monitor( "frag", 2 );
		setup_button_monitor( "smoke", 3 );
		level.throttle_pressed_fnc = ::ThrottleButtonPressedPS3_cb;
		level.throttle_flavor_fnc = ::GetThrottleFlavorPS3_cb;
	}
}

move_player_out_of_vent()
{
	level.player FreezeControls( false );
	
	while( true )
	{
		if( level.player ThrottleButtonPressed( "sdv" ) )
		{
			level.player FreezeControls( true );
			break;
		}
		else
		{
			wait( 0.05 );
		}
	}
	
	flag_set( "player_tunnel_spline" );
}

torch_fx()
{
	PlayFxOnTag( getfx( "torch_fire_gun" ), self, "TAG_FX" );
	flag_wait( "stop_torch_fx" );
	StopFxOnTag( getfx( "torch_fire_gun" ), self, "TAG_FX" );
}

turn_torch_off()
{
	wait( 10 );//changed timing now that the torch is brigher it needs to end sooner.
	flag_set( "stop_torch_fx" );
}

play_alt_idle_on_pilot( anm, delay)
{
	if (delay > 0)
		wait delay;
	pilot = self.pilot;
	pilot.blackshadow_driving = false;
	self anim_generic( pilot, anm, "tag_player");
	if( isdefined( pilot ) )
		pilot.blackshadow_driving = true;
}

post_tunnel_setup()
{
	level endon( "russian_sub_event" );
	
	flag_wait( "leaving_tunnel" );
	
	//level.other_sdv01 thread play_alt_idle_on_pilot( "wetsub_idle_alt01", RandomFloatRange(1.0,1.4));
	//level.sdv02 thread play_alt_idle_on_pilot( "wetsub_idle_alt02", RandomFloatRange(1.0,1.4));
	
	level.lead_sdv thread lead_sdv_beacon();
	wait( 2 );
	thread adjust_accel_over_time();
	SetSavedDvar( "vehSubmarineMaxForwardVel", "300" );
	
	flag_wait( "mine_dialogue" );
	
	if( !isDefined( level.start_at_watching_sub ) )
	{
		thread vo_mines();
	}
}

adjust_accel_over_time()
{
	wait( 1 );
	SetSavedDvar( "vehSubmarineMaxForwardAccel", "125" );
	wait( 1 );
	SetSavedDvar( "vehSubmarineMaxForwardAccel", "225" );
	wait( 1 );
	SetSavedDvar( "vehSubmarineMaxForwardAccel", "325" );
}

wait_for_end_of_ride()
{
	level waittill("sdv_ride_done");
    self.custom_animscript_table[ "combat" ] = undefined;
    self.custom_animscript_table[ "move" ] = undefined;
    self.custom_animscript_table[ "stop" ] = undefined;
    self notify("killanimscript");
}

scubamask_on_player(bFade)
{
	Assert(IsPlayer(self));	
	if(!IsDefined(bFade)) bFade = true;
	
	if(bFade)
	{
		fade_out( 0.25 );
	}
	
	SetHUDLighting( true );

	self.scubamask_hud_elem = NewHudElem();
	self.scubamask_hud_elem.x = 0;
	self.scubamask_hud_elem.y = 0;
	self.scubamask_hud_elem.horzAlign = "fullscreen";
	self.scubamask_hud_elem.vertAlign = "fullscreen";
	//self.scubamask_hud_elem.foreground = true;
	self.scubamask_hud_elem.sort = -1; // trying to be behind introscreen_generic_black_fade_in	
	self.scubamask_hud_elem SetShader("scubamask_overlay_delta", 640, 480);
	self.scubamask_hud_elem.alpha = 1.0;
	
	//level.player delaythread( 1.0, ::scubamask_breathing );
		
	if(bFade)
	{
		wait( 0.25 );
		fade_in( 1.0 );
	}
}

scubamask_off_player()
{
	Assert(IsPlayer(self));	
	
	//aud_send_msg("mus_board_sub");
	
	fade_out( 0.6 );	// this blocks, but apparently not enough
	wait 0.25;			// wait before we kill the mask
	level.mask show();

	if(IsDefined(self.scubamask_hud_elem))
	{
		self.scubamask_hud_elem Destroy();	
		self.scubamask_hud_elem = undefined;
	}

	SetHUDLighting( false );

	level.player notify( "stop_breathing" ); 
	flag_set( "player_mask_off" );
	aud_send_msg("scubamask_off_player");
	wait( 0.25 );
	fade_in( 0.1 );
}	

/*
gasmask_off_moment()
{
	flag_wait( "flag_gasmasks_off" );
	wait 3;
	
	level.player gasmask_off_player();
	level.hero_lone_star gasmask_off_npc();
	level.hero_reno gasmask_off_npc();
	
}

*/

scubamask_breathing()
{
	delay = 1.0;
	self endon( "stop_breathing" );
	
	while ( 1 )
	{
		self play_sound_on_entity( "breathing_gasmask" );
		wait( delay );
	}
}

/*

gasmask_on_npc()
{
	self.gasmask = Spawn("script_model", (0, 0, 0));
	self.gasmask SetModel("prop_sas_gasmask");
	self.gasmask LinkTo(self, "tag_eye", (-4, 0, 2), (120, 0, 0));
}

gasmask_off_npc()
{
	if(IsDefined(self.gasmask))
		self.gasmask Delete();
}

*/

sdv_ai_think(sdv)
{
	level endon("sdv_ride_done");
	thread wait_for_end_of_ride();
	sdv.pilot = self;
	sdv thread anim_generic_first_frame(self,"wetsub_idle", "tag_player");
	self ForceTeleport(sdv gettagorigin("tag_player"), sdv gettagangles("tag_player"));
	self LinkToBlendToTag(sdv, "tag_npc_origin", false);
	
    self.custom_animscript_table[ "combat" ] = animscripts\blackshadow::main;
    self.custom_animscript_table[ "move" ] = animscripts\blackshadow::main;
    self.custom_animscript_table[ "stop" ] = animscripts\blackshadow::main;
    self.blackshadow = sdv;
    
    sdv thread anim_generic( self, "wetsub_idle", "tag_player" );
    // the end of the above animation will cause a transition to the blackshadow animscript
    wait 0.05;
    self anim_StopAnimScripted();
    self thread maps\ny_harbor_sdv_drive::npc_bubbles();
}


submine_waitfor_trigger()
{
	flag_wait( "submine_planted" );
	level.player notify("stop_dpfog");
	thread vision_set_fog_changes("ny_harbor_underwater_sub_explode", 3);
	aud_send_msg("submine_planted");
	
	flag_wait( "detonate_sub" );
	aud_send_msg("submine_detonated", level.mine_sub_model);
	//moved the vfx call to ny_harbor_fx.gsc file under cine_sub_surfacing_explosions();	
	
	flag_set ( "submine_detonated" );
}

ShortestDeltaAngle(angles,tgt_angles, maxangvel )
{
	dangles = tgt_angles - angles;
	da = [];
	for (i=0; i<3; i++)
	{
		a = dangles[i];
		av = maxangvel[i];
		while (a < -180)
			a += 360;
		while (a > 180)
			a -= 360;
		if (a < -1*av)
			a = -1*av;
		if (a > av)
			a = av;
		da[i] = a;
	}
	dangles = ( da[0], da[1], da[2] );
	return dangles;
}

SmoothDeltaAngle(angles,tgt_angles, ratio )
{
	dangles = tgt_angles - angles;
	da = [];
	if (ratio == 1)
		blend = 1;
	else
	{
		r2 = ratio*ratio;
		blend = 3*r2 - 2*r2*ratio;
//		blend = ratio - (sin(360*ratio)/6.28);
	}
	for (i=0; i<3; i++)
	{
		a = dangles[i];
		while (a < -180)
			a += 360;
		while (a > 180)
			a -= 360;
		a *= blend;
		da[i] = a;
	}
	dangles = ( da[0], da[1], da[2] );
	return dangles;
}

LimitAngle( wsAngles, refAngles, limitAngle )
{
	refForward = AnglesToForward(refAngles);
	wsForward = AnglesToForward(wsAngles);
	dp = VectorDot(refForward, wsForward);
	limDP = cos( limitAngle );
	if (dp < limDP)
	{	// need to find the vector with a dp of limDP in the plane of wsForward and refForward
		perp = wsForward - dp*refForward;	// we want the direction for perp (it will be in same plane)
		perp = VectorNormalize(perp);
		sinLim = sin(limitAngle);
		wsForward = limDP*refForward + sinLim*perp;
		angles = VectorToAngles( wsForward );
		wsAngles = (angles[0],angles[1],wsAngles[2]);	// maintain the roll
	}
	return wsAngles;
}

MCL_MAX_ANG_VEL = (20,40,20);

move_cal_cleanup( model, msg )
{
	level endon( "stop_mcl" );
	self waittill( msg );
	model Delete();
	level notify( "stop_mcl" );
}

move_close_and_link( target, vel, maxconvergence, tgtvel, msg, threshdist, angletime, waitForFlag, angledtime, tag )
{
	self endon("stop_mcl");
	self endon("death");
	target endon("death");
/*	/#
	createdebugtexthud("speed"+ target GetEntityNumber(), 20, 130, (1,1,1), "speed:");
	createdebugtexthud("tgtspd"+ target GetEntityNumber(), 20, 160, (1,1,1), "tgtspd:");
	#/	*/
	if (!isdefined(angledtime))
		angledtime = 0.5;
	if (!isdefined(threshdist))
	{
		threshdist = 0.25 * length(vel) * 0.05;
		if (threshdist < 2)
			threshdist = 2;
	}
	if (!isdefined(angletime))
	{	// pick an angletime based on the angular distances at start (could have separate time for each axis)
		angles = target.angles;
		if (isdefined(tag))
			angles = target GetTagAngles( tag );
		delta_angles = ShortestDeltaAngle(self.angles,angles, (360,360,360));
		angletime = abs(delta_angles[0])/MCL_MAX_ANG_VEL[0];
		temp = abs(delta_angles[1])/MCL_MAX_ANG_VEL[1];
		if (temp > angletime)
			angletime = temp;
		temp = abs(delta_angles[2])/MCL_MAX_ANG_VEL[2];
		if (temp > angletime)
			angletime = temp;
	}
	time = 0;
	prv_tgt_origin = target.origin;
	prv_origin = self.origin;
	firstframe = true;
	// we'll get a relative speed in the same direction as the tgtvel
	tgtdir = VectorNormalize(tgtvel);
	speed = VectorDot(tgtdir,vel);
	maxrelspeed = speed - length(tgtvel);
	if (maxrelspeed < maxconvergence)
		maxrelspeed = maxconvergence;
	relspeed = maxrelspeed;
	desiredrelspeed = maxconvergence;
	deccel = (relspeed - desiredrelspeed)/(4*20);
	accel = 10*deccel;
	curvel = (0,0,0);
	prv_distance = Distance(target.origin, self.origin);
	holdcount=0;
	if (isdefined(msg))
	{
		holdcount=2;
	}
	refmodel = undefined;
	if (isdefined(tag))
	{
		refmodel = spawn("script_model",(0,0,0));
		refmodel SetModel(self.model);
		self thread move_cal_cleanup( refmodel, "stop_mcl" );
		self thread move_cal_cleanup( refmodel, "death" );
		target thread move_cal_cleanup( refmodel, "death" );
	}
	
	while (true)
	{
		angles = target.angles;
		origin = target.origin;
		if (isdefined(tag))
		{
			transform = get_origin_to_tag( target, tag, refmodel );
			angles = transform["angles"];
			origin = transform["origin"];
		}
		delta = origin - self.origin;
		distance = Length( delta );
		if ( (!isdefined( waitForFlag ) || flag(waitForFlag)) && (distance < threshdist) )
		{
			if (holdcount > 0)
			{
				if (isdefined(msg))
				{
					level notify(msg);
					msg = undefined;
				}
				holdcount--;
			}
			else
			{
				if (isdefined(tag))
				{
					transform = get_origin_to_tag( target, tag, refmodel );

					self.angles = transform["angles"];
					self.origin = transform["origin"];
				}
				else
				{
					self.origin = target.origin;
					self.angles = target.angles;
				}
				self linkto( target );
				return;
			}
		}
		if (!firstframe && (prv_distance <= distance) )
		{	// losing ground, so accel
			desiredrelspeed = relspeed + accel;
			relspeed = desiredrelspeed;
		}
		else
		{
			if (relspeed > desiredrelspeed)
			{
				relspeed -= deccel;
			}
			else
				relspeed = desiredrelspeed;
		}
		prv_distance = distance;
		ratio = time/angletime;
		if (ratio > 1)
			ratio = 1;
		delta_angles = SmoothDeltaAngle(self.angles,angles, ratio);
		pred_position = (0,0,0);
		t = 0;
		if (firstframe)
		{
			tgtdir = vectornormalize(tgtvel);
			curvel = vel;
		}
		else
		{
			curvel = 20 * (self.origin - prv_origin);
			tgtvel = 20 * (origin - prv_tgt_origin);
		}
		prv_tgt_origin = origin;
		prv_origin = self.origin;
		//relvel = curvel - tgtvel;
		t = distance/relspeed;
	//	if (firstframe)
	//		self.origin = self.origin; // + 0.025*vel;	// ensure we keep moving some until moveto is up to speed
		firstframe = false;
		tgt_angles = self.angles + delta_angles;

		if (t < 0.5)		
			t = 0.5;
		pred_position = origin + t*tgtvel;
		
		self moveto( pred_position, t, 0, 0 );
		if (angledtime < 0.5)
		{
			self.angles = self.angles + delta_angles*(0.05/angledtime);
		}
		else
			self rotateto( tgt_angles, angledtime, 0, 0 );
	//print("ang=("+self.angles[0]+","+self.angles[1]+","+self.angles[2]+") tgt=("+tgt_angles[0]+","+tgt_angles[1]+","+tgt_angles[2]+")");
		
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
}


draw_ent_axis( )
{
	/#
	axis = spawn("script_model", self.origin);
	axis.angles = self.angles;
	axis SetModel("axis");
	axis linkto(self);
	self waittill("death");
	axis Delete();
	#/
}

debug_eye( ent, tag, offset )
{
	eyeang = ent GetTagAngles(tag);	// our current eyeang
	eyefor = AnglesToForward( eyeang );
	eyergt = AnglesToRight( eyeang );
	eyeup = AnglesToUp( eyeang );
	ctlorg = ent GetTagOrigin(tag);
	plr_eye_origin = ctlorg + (offset[0]*eyefor) + (offset[1]*eyergt) + (offset[2]*eyeup);	// this is where the eye is
	axis = spawn("script_model", plr_eye_origin);
	axis.angles = eyeang;
	axis SetModel("axis");
	axis linkto(ent,tag);
	ent waittill("death");
	axis Delete();
}

get_origin_to_tag( target, tag, refmodel )
{	// self is the ent that we will match to tag
	org_origin = self.origin;
	org_angles = self.angles;
	
	tgt_tag_origin = target GetTagOrigin( tag );
	tgt_tag_angles = target GetTagAngles( tag );
	tgt_tag_up = AnglesToUp( tgt_tag_angles );
	tgt_tag_right = AnglesToRight( tgt_tag_angles );
	tgt_tag_forward = AnglesToForward( tgt_tag_angles );
	
	// get our bindpose
	our_tag_origin = undefined;
	our_tag_angles = undefined;
	if (!isdefined(refmodel))
	{
		self.origin = (0,0,0);
		self.angles = (0,0,0);
		
		// assume bindpose follows the standards
		our_tag_origin = self GetTagOrigin( tag );
		our_tag_angles = self GetTagAngles( tag );
		self.origin = org_origin;
		self.angles = org_angles;
	}
	else
	{
		refmodel.origin = (0,0,0);
		refmodel.angles = (0,0,0);
		
		// assume bindpose follows the standards
		our_tag_origin = refmodel GetTagOrigin( tag );
		our_tag_angles = refmodel GetTagAngles( tag );
	}
	
	// now determine where our origin should be to get our tag to match the target's tag
	our_origin = tgt_tag_origin - our_tag_origin[0]*tgt_tag_forward - our_tag_origin[1]*tgt_tag_right - our_tag_origin[2]*tgt_tag_up;
	our_angles = tgt_tag_angles;

	transform["origin"] = our_origin;
	transform["angles"] = our_angles;
	return transform;
}

match_origin_to_tag( target, tag, bLink, refmodel )
{	// self is the ent that we will match to tag
	transform = get_origin_to_tag( target, tag, refmodel );

	self.origin = transform["origin"];
	self.angles = transform["angles"];
	
	// and link
	if (bLink)
		self linkto( target, tag );
}

PLR_HEIGHT = 60;
watch_object( player, controller, arms, tag, tgt_arms, plroffset, fov, blendTime, doneFlag )
{
	controller endon("stop_watching");
	maxangvel = ( 0.3, 0.6, 0.3 );
	//blendTime = 1.0;
	blendCount = int(blendTime/0.05);
	blendFrac = 1.0/blendCount;
	base_fov = GetDvarFloat("cg_fov");
	fovadd = fov - base_fov;
	dFov = blendFrac*fovadd;
	blend = 0;
	wait 0.2;	// to ensure this isn't causing a pop.
	reftag = "tag_origin";
/*
//	thread debug_eye( arms, tag, plroffset );
	thread debug_eye( tgt_arms, tag, plroffset );
	thread debug_eye( controller, "tag_origin", plroffset );
	thread debug_eye( arms.sdv, reftag, (0,0,0) );
	thread debug_eye( tgt_arms.sdv, reftag, (0,0,0) );
*/
	while (true)
	{
		wait 0.05;
		eyeang = controller GetTagAngles("tag_origin");	// our current eyeang
		eyefor = AnglesToForward( eyeang );
		eyergt = AnglesToRight( eyeang );
		eyeup = AnglesToUp( eyeang );
		ctlorg = controller GetTagOrigin("tag_origin");
		plr_eye_origin = ctlorg + (plroffset[0]*eyefor) + (plroffset[1]*eyergt) + (plroffset[2]*eyeup);	// this is where the eye is
		
		// rather than point at the target, we're going to match the start of animation position
		ideal_eyeang = tgt_arms GetTagAngles( tag );
		tgt_pos = tgt_arms GetTagOrigin( tag );
		tgtfor = AnglesToForward( ideal_eyeang );
		tgtrgt = AnglesToRight( ideal_eyeang );
		tgtup = AnglesToUp( ideal_eyeang );
		tgt_ref_eyepos = tgt_pos + (plroffset[0]*tgtfor) + (plroffset[1]*tgtrgt) + (plroffset[2]*tgtup);	// this is where the eye is
		
		// get the ideal eyepos relative to the moving sdv
		tgt_ref_pos = tgt_arms.sdv GetTagOrigin(reftag);
		tgt_ref_angles = tgt_arms.sdv GetTagAngles(reftag);
		ref_pos = arms.sdv GetTagOrigin(reftag);
		ref_angles = arms.sdv GetTagAngles(reftag);
		
		f = AnglesToForward(tgt_ref_angles);
		r = AnglesToRight(tgt_ref_angles);
		u = AnglesToUp(tgt_ref_angles);
		deltaIEP = tgt_ref_eyepos - tgt_ref_pos;
		// transform it to local space
		deltaIEP = (VectorDot(f,deltaIEP), VectorDot(r,deltaIEP), VectorDot(u,deltaIEP));
		f = AnglesToForward(ref_angles);
		r = AnglesToRight(ref_angles);
		u = AnglesToUp(ref_angles);
		// transform it into world space for the arms
		deltaIEP = deltaIEP[0]*f + deltaIEP[1]*r + deltaIEP[2]*u;
		
		ideal_eyepos = ref_pos + deltaIEP;	// relative to the SDV we're on
		
		// get the current delta in world space for the arms
		deltaEP = plr_eye_origin - ref_pos;
		// blend from the current eye to the ideal eye
		sblend = SmoothValue(blend);
		plr_eye_origin = ref_pos + (1-sblend)*deltaEP + sblend*deltaIEP;
		
		if (blend < 1.0)
			deltaAng = SmoothDeltaAngle(eyeang,ideal_eyeang, blend );
		else
			deltaAng = ShortestDeltaAngle(eyeang,ideal_eyeang, maxangvel );
		angles = controller.angles + deltaAng;
		angles = LimitAngle( angles, level.player_sdv GetTagAngles("tag_body"), 45 );

		controller_for = AnglesToForward( angles );
		controller_rgt = AnglesToRight( angles );
		controller_up = AnglesToUp( angles );
		origin = plr_eye_origin - (plroffset[0]*controller_for + plroffset[1]*controller_rgt + plroffset[2]*controller_up);
		controller unlink();
		controller.angles = angles;
		// get the position of the controller so the eye matches our blended eye
		controller.origin = origin;
		controller linkto( arms, tag );
		if ((blend == 1.0) && isdefined(doneFlag))
		{
			flag_set( doneFlag );
		}

		if (blendCount > 0)
		{
			fovadd = fovadd - dFov;
			SetSavedDvar("cg_fovNonVehAdd",fovadd);
			blend += blendFrac;
			blendCount -= 1;
		}
		if (blend > 1.0)
			blend = 1.0;
	}
}

player_linkto_match( eyepos, eyeang, controller, arms, tag, offset )
{
	controller unlink();
	up = AnglesToUp( eyeang );
	right = AnglesToRight( eyeang );
	forward = AnglesToForward( eyeang );
	controller.origin = eyepos - ((offset[0]*forward) + (offset[1]*right) + (offset[2]*up));
	controller.angles = eyeang;
	controller linkto( arms, tag );
}

switch_sdv_realtime_lights( src, dst )
{
	src notify("stop_light_control");	// kill the thread running on the src
	dst ent_flag_init( "realtime_lights" );
	src ent_flag_clear("realtime_lights");
	src.use_realtime_lights = false;
	dst ent_flag_set("realtime_lights");
	dst.use_realtime_lights = true;
	dst.realtime_light_tag = src.realtime_light_tag;
	src.realtime_light_tag = undefined;
	dst.realtime_light_tag unlink();
	dst.realtime_light_tag.origin = dst GetTagOrigin("tag_light_l");
	dst.realtime_light_tag.angles = dst GetTagAngles("tag_light_l");
	dst.realtime_light_tag linkto( dst, "tag_light_l" );
}

turn_on_light_on_mine()
{
//	wait( 2.95 ); Use this timing to hide teleport.
	wait 3.4;
	playFXOnTag( getfx( "c4_light_blink" ), self, "tag_fx" );
}

GetBodySpacePosition( offset )
{
	forward = AnglesToForward(self.angles);
	right = AnglesToRight(self.angles);
	up = AnglesToUp(self.angles);
	return offset[0]*forward + offset[1]*right + offset[2]*up;
}

notetrack_hides_objective_mine( ent )
{
	// ent waittillmatch("anim single", "hideobj" );
	wait 1.5;
	level.mine_sub_model hide();		// hide the objective mine
}

calc_vehicle_fov( vehicle, vehdef, speed )
{
	base_fov = GetDvarFloat("cg_fov");	// cg_fov
	fovSpeed = vehdef.fovSpeed;
	// SDV parameters
	fovIncrease = vehdef.fovIncrease;
	fovOffset = vehdef.fovOffset;
	rollInfluence = vehdef.rollInfluence;
	
	if (!isdefined(speed))
		speed = Length(vehicle Vehicle_GetVelocity());
	speedScale = speed/fovSpeed;
	if (speedScale > 1.0)
		speedScale = 1.0;
	fovIncrease = speedScale*fovIncrease;
	fovOffset = speedScale*fovOffset;
	
	values["fov"] = base_fov + fovIncrease;
	values["fovOffset"] = fovOffset;
	return values;
}

calc_vehicle_view( vehicle, vehdef, speed )
{
	angles = vehicle GetTagAngles( "tag_player" );
	origin = vehicle GetTagOrigin( "tag_player" );
	forward = AnglesToForward(angles);
	up = AnglesToUp(angles);
	right = AnglesToUp(angles);
	offset = (0, 0, PLR_HEIGHT);
	base_fov = GetDvarFloat("cg_fov");	// cg_fov
	fovSpeed = vehdef.fovSpeed;
	// SDV parameters
	fovIncrease = vehdef.fovIncrease;
	fovOffset = vehdef.fovOffset;
	rollInfluence = vehdef.rollInfluence;
	vehcam_offset = vehdef.vehcam_offset;
	
	if (!isdefined(speed))
		speed = Length(vehicle Vehicle_GetVelocity());
	speedScale = speed/fovSpeed;
	if (speedScale > 1.0)
		speedScale = 1.0;
	fovIncrease = speedScale*fovIncrease;
	fovOffset = speedScale*fovOffset;
	offset = offset + vehcam_offset + (fovOffset,0,0);
	
	values["eyepos"] = origin + offset[0]*forward + offset[1]*right + offset[2]*up;
	values["eyeang"] = ( angles[0], angles[1], AngleClamp180(rollInfluence*angles[2]) );
	values["fov"] = base_fov + fovIncrease;
	values["fovOffset"] = fovOffset;
	values["offset"] = offset;
	return values;
}

calc_player_pos( parent, tag )
{
	angles = parent GetTagAngles( tag );
	origin = parent GetTagOrigin( tag );
	offset = (0,0,PLR_HEIGHT);
	forward = AnglesToForward(angles);
	right = AnglesToRight(angles);
	up = AnglesToUp(angles);
	eyepos = origin + offset[0]*forward + offset[1]*right + offset[2]*up;
	plrpos = eyepos - offset;
	plrang = angles;
}

submine_waitfor_plant()
{
	// Since sdvs aren't physics vehicles, we'll have to switch to a script model of it
	sdv_model = spawn( "script_model", level.player_sdv.origin );
	sdv_model.angles = level.player_sdv.angles;
	sdv_model SetModel("vehicle_blackshadow_730_viewmodel");
	sdv_model.animname = "blackshadow";
	sdv_model SetAnimTree();
	sdv_model match_origin_to_tag( level.player_sdv, "tag_body", false );	// ensure we match orientation
	sdv_model linkto( level.player_sdv, "tag_body");
	sdv_model Hide();
	level.player_sdv.sdv_model = sdv_model;	// so fx can be hooked to it
	player_control = spawn_tag_origin();	// this entity lets us control the camera

	scriptednode = spawn_tag_origin();
	scriptednode.origin = level.mine_sub_model.origin;
	scriptednode.angles = level.russian_sub_02.angles + ( 0, 90, 0 );	// temp since until we place the limpit mine
	//scriptednode thread draw_ent_axis();
	scriptednode linkto( level.mine_sub_model );	// for first part, we follow the mine

	// the tgt_model is the reference position we need to get our scripted model to smoothly before starting the anim
	tgt_model = spawn( "script_model", level.player_sdv.origin );
	tgt_model SetModel("vehicle_blackshadow_730_viewmodel");
	tgt_model.animname = "blackshadow";
	tgt_model SetAnimTree();
	tgt_model Hide();
	tgt_model.origin = level.player_sdv.origin;
	tgt_model.angles = level.player_sdv.angles;
	// move the sdv_model to the desired position relative to the russian sub
	scriptednode anim_first_frame_solo( tgt_model, "mine_plant", "tag_origin");
	tgt_model linkto(scriptednode, "tag_origin" );

	// create a target to use to determine our final camera orientation
	tgt_arms = spawn_anim_model( "player_sdv_rig" );
	tgt_arms.animname = "player_sdv_rig";
	scriptednode anim_first_frame_solo( tgt_arms, "surfacing", "tag_origin" );
	tgt_arms linkto( scriptednode, "tag_origin");
	tgt_arms Hide();

	plrcam_offset = (0,0,PLR_HEIGHT);

	vehcam_offset = (-4,0,0);

	// these need to match the parameters in the Blackshadow's vehicle
	vehdef = spawnstruct();
	vehdef.vehcam_offset = vehcam_offset;
	vehdef.fovSpeed = CONST_MPHTOIPS*65.0;
	vehdef.fovIncrease = 20.0;
	vehdef.fovOffset = 4.0;
	vehdef.rollInfluence = 0.6;
	
	level.sdv_player_arms.sdv = sdv_model;
	tgt_arms.sdv = tgt_model;

	level notify("entering_mine_plant");	// start any fx to hide the pop entering the mine plant
	wait 0.25;	// give fx time to cover any pops

	eyepos = level.player GetEye();
	eyeang = level.player GetPlayerAngles();
	
	level.mine_plant_started = true;
	
	// get the sub close before it links
	tgtvel = level.russian_sub_02 Vehicle_GetVelocity();
	vel = level.player_sdv Vehicle_GetVelocity();	// get it before useby changes the sdv's orientation
	level.player_sdv Hide();
	
	// to get a stable model and smooth transition below, we'll switch to a model here
	//scriptednode = level.mine_sub_model;
	flag_set( "aud_planting_submine" );
	flag_set( "vo_stop_mine_nag" );
	// get our reference node, which will start out on the mine and later be moved to the world position for the breach
	sdv_model unlink();
	sdv_model match_origin_to_tag( level.player_sdv, "tag_body", false );	// ensure we match orientation
	sdv_model Show();
	thread switch_sdv_realtime_lights( level.player_sdv, sdv_model );
	maps\ny_harbor_sdv_drive::ChangeSonarEntity( sdv_model );
//	maps\ny_harbor_sdv_drive::TransferSDVHUD( sdv_model, false );

	// calculate the eyeang/eyepos using the standard algorithm
	eyevalues = calc_vehicle_view( level.player_sdv, vehdef );
	eyepos = eyevalues["eyepos"];
//	eyeang = eyevalues["eyeang"];

	// since we want to have the player lookat the mine as we approach, we add an entity between the player and arms
	vehcam_offset = (vehcam_offset[0] + eyevalues["fovOffset"], vehcam_offset[1], vehcam_offset[2]);
	fov = eyevalues["fov"];
	
	level.sdv_player_arms unlink();		// the arms were linked to the vehicle sdv, we move them to the sdv_model

	origin = sdv_model GetTagOrigin( "tag_player" );
	angles = sdv_model GetTagAngles( "tag_player" );
	level.sdv_player_arms.origin = origin;
	level.sdv_player_arms.angles = angles;
	level.sdv_player_arms linkto( sdv_model, "tag_player" );
	origin = level.sdv_player_arms.origin;
	angles = level.sdv_player_arms.angles;
	player_control.origin = origin;
	player_control.angles = (eyeang[0], eyeang[1], 0);	// no roll for the player controller
	angles = player_control.angles;
	
	aud_send_msg( "aud_link_engine_entities_to_scripted_node", sdv_model);
		
	level.player_sdv useby( level.player );	// this toggles the use, so this releases the vehicle and unlinks the player
	// note the useby getting off also sets the dontinterpolate bit for the player
	level.player_sdv.playercontrolled = false;
	level.player.in_sdv = false;
	level.player disableweapons();
	// ensure the player matches the control entity before linking (note that our roll should be 0 here)
	level.player SetOrigin( origin );
	level.player SetPlayerAngles( player_control.angles );
	level.player PlayerLinkToDelta( player_control, "tag_origin", 1.0, 10, 2, 10, 10, true );
 	level.player dontinterpolate(); // since the SetOrigin and useby both toggled the flag
	// now we will "fix" the position of the control so our eye is in the correct place, and link it to the arms
	player_linkto_match( eyepos, eyeang, player_control, level.sdv_player_arms, "tag_player", plrcam_offset );
	SetSavedDvar("cg_fovNonVehAdd", fov-GetDvarFloat("cg_fov") );	// since the fov is likely different from the base (note that we do this late, trying to ensure it is set correctly the first frame we are off sub)
	
	// setup the thread that will keep us looking at the mine
	avgspeed = 0.5*(Length(vel) + Length(tgtvel));
	distance = Distance(tgt_model.origin, sdv_model.origin);
	t = distance/avgspeed;
	t = 2.0;
	thread watch_object( level.player, player_control, level.sdv_player_arms, "tag_player", tgt_arms, plrcam_offset, fov, t, "finished_head_turn_to_mine");
	sdv_model move_close_and_link( tgt_model, vel, 3*CONST_MPHTOIPS, tgtvel, "starting_mine_plant", 0.5, undefined, "finished_head_turn_to_mine" );
	// move_close_and_link will block until it's close enough
	SetSavedDvar("vehcam_offset","0 0 0");	// turn off offset for any later vehicles (wait to ensure it doesn't cause a camera pop earlier)
	
	// play the animation to place the mine on the sub
	mine = spawn( "script_model",level.sdv_player_arms.origin );
	mine setmodel( "weapon_underwater_limpet_mine" );
	mine.animname = "mine";
	aud_send_msg("aud_limpet_mine_anim");
	mine SetAnimTree();
	// get the player attached to the arms with no roll, before applying the anim
	level.sdv_player_arms unlink();
	level.sdv_player_arms.angles = (level.sdv_player_arms.angles[0], level.sdv_player_arms.angles[1], 0);
	level.player SetOrigin(level.sdv_player_arms.origin);
	level.player SetPlayerAngles(level.sdv_player_arms.angles);
	level.player dontinterpolate();
	level.player PlayerLinktoDelta( level.sdv_player_arms, "tag_player", 1.0, 2, 2, 2, 2, true );
	
	scriptednode anim_first_frame_solo( level.sdv_player_arms, "surfacing", "tag_origin" );
	scriptednode anim_first_frame_solo( mine, "mine_plant", "tag_origin" );
	sdv_model unlink();
	scriptednode anim_first_frame_solo( sdv_model, "mine_plant", "tag_origin" );
	sdv_model linkto( scriptednode );
	level.sdv_player_arms linkto( scriptednode, "tag_origin" );	// arms will stay with scriptednode
	mine linkto( level.mine_sub_model, "tag_weapon" );
	//thread notetrack_hides_objective_mine( level.sdv_player_arms );
	player_control notify("stop_watching");		// kill the watch thread
	// turn off the player sdv rig blackshadow anims
	level.sdv_player_arms.not_driving = true;
	
	mine thread turn_on_light_on_mine();
	mine thread maps\ny_harbor_fx::submine_bubbles_vfx();//add tiny bubbles to mine after planted
	// we had to delay the arm animation a frame to get it to match the mine plant
	scriptednode delaythread( 0.05, ::anim_single_solo, level.sdv_player_arms, "surfacing", "tag_origin" );
	scriptednode anim_single_solo( mine, "mine_plant", "tag_origin" );
	
	// after the mine's mine_plant animation, we are going to move everything and start using the russian_cine_sub (since the sub vehicle is on a path) 
	sub = spawn("script_model", level.russian_sub_02.origin);
	sub.angles = level.russian_sub_02.angles;
	sub SetModel( level.russian_sub_02.model );
	sub.animname = "russian_sub";
	sub SetAnimTree();
	thread switch_oscar2_lights( level.russian_sub_02, sub );
	level.russian_sub_02 Hide();
	level.russian_cine_sub = sub;
	sub.animname = "russian_sub";
	// move the mine to the cine sub
	mine StopAnimScripted();
	mine dontinterpolate();
	mine linkto( level.russian_cine_sub, "body" );	// had to be body since the anim rotated body 180
	level.mine_sub_model Delete();
	level.mine_sub_model = mine;

	// arms are still playing the animaiton and linked to the scriptednode	
	// in the middle of the mineplant, at the end of the anim, we teleport everything to play the sub surface
	sdv_model unlink();			// move_close_and_link linked us to the tgt_model, so unlink
	tgt_model Delete();			// cleanup
	tgt_arms Delete();			// cleanup
	player_control Delete();	// cleanup
	flag_set ( "submine_planted" );
	flag_set( "obj_plantmine_complete" );
	flag_set( "obj_capturesub_given" );
	scriptednode unlink();		// we were linked to the mine, now we will be moved to the breach org
	handle_sub_breach( sdv_model, scriptednode );
}

sub_breach_sub( refnode )
{
	scriptnode = spawn_tag_origin();
	scriptnode.origin = refnode.origin + (0,0,-96);
	scriptnode.angles = refnode.angles;
	level.breach_sub_scriptnode = scriptnode;
	level.russian_cine_sub dontinterpolate();
	scriptnode anim_first_frame_solo( level.russian_cine_sub, "surfacing" );
	thread sub_breach_move_allies( level.russian_sub_02, level.russian_cine_sub );
	level.russian_cine_sub linkto(scriptnode);
	maps\ny_harbor_sdv_drive::ChangeSonarSubTarget(level.russian_cine_sub, level.russian_sub_02);
	scriptnode anim_single_solo( level.russian_cine_sub, "surfacing" );
	flag_wait("sub_breach_finished");
	level.russian_cine_sub Delete();
	level.russian_cine_sub = undefined;
}


handle_sub_breach( sdv_model, scriptednode )
{
	flag_set( "player_surfaces" );
	node = getent("sub_breach_anim_node", "targetname" );
	scriptednode.origin = node.origin;
	scriptednode.angles = node.angles;
	level thread sub_breach_player( scriptednode );
	level thread sub_breach_sub( node );
	level thread sub_breach_sdv( node, sdv_model );
	level thread sub_breach_ally( node );
	level thread sub_breach_rumble();
	
	flag_set("sub_breach_started");
	aud_send_msg("sub_breach_started", node);
	flag_wait("sub_breach_finished");
	level.mine_sub_model Delete();
	level.mine_sub_model = undefined;
	cleanup_after_sdv_ride();
}

sub_breach_rumble()
{
	flag_wait( "sub_surface_rumble" );
	
	counter = 0;
	time_small = 2.5;
	time_large = 5.5;
	time_small_2 = 9.0;
	
	while( counter < time_small )
	{
		level.player PlayRumbleOnEntity( "viewmodel_small" );
		wait( 0.05 );
		counter += 0.05;
	}
	
	while( counter < time_large )
	{
		level.player PlayRumbleOnEntity( "viewmodel_large" );
		wait( 0.05 );
		counter += 0.05;
	}
	
	while( counter < time_small_2 )
	{
		level.player PlayRumbleOnEntity( "viewmodel_small" );
		wait( 0.05 );
		counter += 0.05;
	}
}

sub_breach_player( scriptnode )
{
	level notify("sdv_ride_done");
	//level.sdv_player_arms.not_driving = true;
	//thread debug_playerview();

//	level.player disableweapons();
	//burya1 = getent("burya1", "targetname" );
	burya2 = getent("burya2", "targetname" );
	//burya1 Hide();
	burya2 Hide();
	
	scriptnode.base_origin = scriptnode.origin;
	scriptnode.origin = scriptnode.origin + (0,0,-96);	// shift it down below the caulk at start
	level.sdv_player_arms dontinterpolate();
	// should already be linked
//	level.sdv_player_arms linkto( scriptnode, "tag_origin" );
	// re-link with blend, which seems to eliminate camera error?
	level.player.origin = level.sdv_player_arms.origin;
	level.player dontinterpolate();
//	level.player PlayerLinkToBlend( level.sdv_player_arms, "tag_player", 0.0, 0,0,0,0 );
//	level.player PlayerLinkToDelta( level.sdv_player_arms, "tag_player", 1.0, 0,0,0,0, true );
	delaythread( 3, ::sub_breach_open_view );
	level.sdv_player_arms thread catch_notetrack_player_through_water( scriptnode );	// wait until the player has reached surface to start bobbing and do water change (should be a notetrack)
	level.sdv_player_arms thread catch_notetrack_mine_explosion();
	
	// wait for anim to finish
	//scriptnode waittill("surfacing");
	wait (600+580)/30.0;	// wait time of the animation after first teleport
	underwater_hud_enable( false );
	level.sdv_player_arms unlink();
	level notify("cleanup_bob");
	// coming up through the water, we will "teleport" to the Radiant Sub
	refnode = getent( "sub_board_anim_node", "targetname" );
	scriptnode2 = spawn_tag_origin();
	scriptnode2.origin = scriptnode.origin; // + (0,0,-96);	// shift it down below the caulk at start
	scriptnode2.angles = scriptnode.angles;
	scriptnode2 anim_first_frame_solo( level.sdv_player_arms, "boarding" );
	level.sdv_player_arms linkto(scriptnode2);
	level.sdv_player_arms thread catch_notetrack_subswap( scriptnode2, refnode );
	level.sdv_player_arms thread catch_notetrack_take_mask_off();
	level.sdv_player_arms thread catch_notetrack_stopbob();
	
	level.mask = spawn_anim_model( "mask" );
	level.mask.animname = "mask";
	level.mask hide();
	level.mask linkto( scriptnode2 );
	guys = [];
	guys[0] = level.sdv_player_arms;
	guys[1] = level.mask;
	scriptnode2 anim_single( guys, "boarding" );
	level.sdv_player_arms StopAnimScripted();
	level.sdv_player_arms unlink();
	level.player unlink();
	level.sdv_player_arms Hide();
	level.mask Delete();
	level.player disableslowaim();
	flag_set( "sub_breach_finished" );
	aud_send_msg("sub_breach_finished");
}

sub_breach_ally( refnode )
{
	scriptnode = spawn_tag_origin();
	scriptnode.origin = refnode.origin + (0,0,-96);
	scriptnode.angles = refnode.angles;
	guy = level.sdv_sandman;
	org_model = guy.model;
	guy SetModel(level.sdv_sandman.model);
	guy Show();
	scriptnode anim_first_frame_solo( guy, "surfacing" );
	guy linkto( scriptnode, "tag_origin" );
	guy delaythread( (-65 + 580)/30.0, ::npc_through_water, scriptnode );	// wait until the ally has reached surface to start bobbing (should be a notetrack)
	scriptnode anim_single_solo( guy, "surfacing" );
	guy unlink();
	guy SetModel(org_model);
	//guy delete();
	
	//setup sandman for sub... doing it here because he needs to be there before the teleport... sub_setup is after
	thread sub_extra_spawn();
	level.sandman = maps\ny_harbor::create_ally("sandman_sub", "lonestar", "Sandman", "o", true);
}

catch_notetrack_player_through_water( scriptnode )
{
	self waittillmatch( "single anim", "waterout" );

	aud_send_msg("player_surfaces");
		
	//ship[0] = getent("burya1", "targetname" );
	ship[0] = getent("burya2", "targetname" );
	hide_surface_ships( false, ship );
	scriptnode.origin = scriptnode.origin + (0,0,96);
	level.breach_sub_scriptnode.origin = level.breach_sub_scriptnode.origin + (0,0,96);
	self thread bobbing_actor( scriptnode, 0.3 );

	thread above_water_art_and_ambient_setup();
	//thread player_surface_blur();
	setsaveddvar("phys_gravity","-800.");
	maps\ny_harbor::SetAbovewaterCharLighting();
	flag_set("player_through_water");
}

sub_breach_sdv( refnode, sdv_model )
{
	thread maps\ny_harbor_sdv_drive::ClearSonar();
	scriptnode = spawn_tag_origin();
	scriptnode.origin = refnode.origin + (0,0,-96);	// shift it down below the caulk at start
	scriptnode.angles = refnode.angles;
	sdv_model dontinterpolate();
	scriptnode anim_first_frame_solo( sdv_model, "surfacing" );
//	maps\ny_harbor_sdv_drive::TransferSDVHUD( sdv_model, false );	// we do it again to ensure things are good
	wait 0.05;
	scriptnode anim_single_solo( sdv_model, "surfacing", undefined );
	flag_wait("sub_breach_finished");
	wait 0.05;	// ensure everyone else has a chance before we cleanup
	StopFxOnTag( GetFx("flashlight_spotlight"), sdv_model.realtime_light_tag, "tag_origin" );
	sdv_model.realtime_light_tag Delete();
	sdv_model Delete();
}



fail_sub_mine_plant()
{
	level notify( "new_quote_string" );
	SetSavedDvar( "vehSubmarineMaxForwardVel", "0" );
	SetSavedDvar( "vehSubmarineMaxForwardAccel", "0" );
	SetDvar( "ui_deadquote", &"NY_HARBOR_SUB_FAIL" );
	missionFailedWrapper();
	wait 1000;	// don't return
}

grinch_submine_plant()
{
	ally_submine_plant(level.grinch_sdv, level.sdv_grinch, level.ally_mine_sub_target["grinch"], "mine_plant", "npc_plant_side" );
}

sdv03_submine_plant()
{
	wait 4.0;	// give the player a better chance to see it
	ally_submine_plant(level.sdv03, level.sdv03.pilot, level.ally_mine_sub_target["sdv03"], "npc_plant_up", "npc_plant_up" );
}

ally_submine_plant( sdv, sdv_actor, target, sdv_anm, anm )
{
	level endon( "player_surfaces" );
	// wait for the grinch to get close enough to plant a mine
	sdv notify("end_speed_control");
	threshdist = 120;
	while (true)
	{
		sdv2tgt = target.origin - sdv.origin;
		vel = level.russian_sub_02 Vehicle_GetVelocity();
		speed = level.russian_sub_02 Vehicle_GetSpeed();
		vel = VectorNormalize(vel);
		dp = VectorDot( vel, sdv2tgt );
		adp = abs(dp);
		if (adp < threshdist)
			break;	// close enough to lock on
		if (dp > 0)
		{	// need to catch up with point
			adjust = 7 * adp/(2*threshdist);
			speed = speed + adjust;
		}
		else
		{	// slow down
			if (adp < threshdist)
				speed *= 0.9;
			else
				speed *= 0.9 * threshdist/adp;
		}
		accel = speed;
		if (accel <= 0)
			accel = 0.1;
		sdv Vehicle_SetSpeed( speed, accel, accel );
		wait 0.05;
	}
	sdv Vehicle_SetSpeed( level.russian_sub_02 Vehicle_GetSpeed() );
	while (!(sdv ent_flag("lights")))
		wait 0.05;	// wait until the lights come on before we continue
		
	// to get a stable model and smooth transition below, we'll switch to a model here
	scriptednode = spawn_tag_origin();
	scriptednode.origin = target.origin;
	scriptednode.angles = level.russian_sub_02.angles + ( 0, 90, 0 );	// temp since until we place the limpit mine
//scriptednode thread draw_ent_axis();
	scriptednode linkto( target );
	sdv_model = spawn( "script_model", sdv.origin );
	sdv_model.angles = sdv.angles;
	sdv_model SetModel("vehicle_blackshadow_730");
	sdv_model.animname = "blackshadow";
	sdv_model SetAnimTree();
	sdv_model match_origin_to_tag( sdv, "tag_body", false );
	sdv_model ent_flag_init("lights");
	sdv_model thread vehicle_scripts\_submarine_sdv::handle_lights();
	if (sdv ent_flag("lights"))
	{
		sdv ent_flag_clear("lights");
		sdv_model ent_flag_set("lights");
	}
		
	sdv_model Show();
	tgt_model = spawn( "script_model", sdv.origin );
	tgt_model.angles = sdv.angles;
	tgt_model SetModel("vehicle_blackshadow_730");
	tgt_model.animname = "blackshadow";
	tgt_model SetAnimTree();
	tgt_model Hide();
	sdv Hide();
	sdv_actor unlink();
	sdv_actor ForceTeleport(sdv_model gettagorigin("tag_npc_origin"), sdv_model gettagangles("tag_npc_origin"));
	sdv_actor LinkToBlendToTag( sdv_model, "tag_npc_origin", false );
	// move the sdv_model to the desired position relative to the russian sub
	scriptednode anim_first_frame_solo( tgt_model,sdv_anm, "tag_origin");
	tgt_model linkto(scriptednode, "tag_origin" );
	// get the sub close before it links
	sdv_model thread move_close_and_link_end_early();
	sdv_model move_close_and_link( tgt_model, 1.0*(sdv Vehicle_GetVelocity()), 6*CONST_MPHTOIPS, (level.russian_sub_02 Vehicle_GetVelocity()) );
	// move_close_and_link will block until it's close enough
	wait 0.25;	// wait a short period for good measure

	// play the animation to place the mine on the sub
	sdv_actor.blackshadow_driving = false;	// turn off the driving anims
	guys[0] = sdv_actor;
	org_animname = sdv_actor.animname;
	sdv_actor.animname = "generic";	// strange case, we probably shouldn't tie a multi-actor to generic
	mine = spawn( "script_model", guys[0].origin );
	mine setmodel( "weapon_underwater_limpet_mine" );
	mine.animname = "mine";
	mine SetAnimTree();
	guys[1] = mine;
	scriptednode anim_first_frame( guys, anm, "tag_origin" );
	guys[0] linkto( target );
	guys[1] linkto( target );
//	sdv vehicle_teleport(sdv_model.origin, sdv_model.angles);	// for good measure
	// turn off the player sdv rig blackshadow anims
	//level.sdv_player_arms.not_driving = true;
	mine thread turn_on_light_on_mine();
	scriptednode anim_single( guys, anm, "tag_origin" );
	// after the animation, we need to transition the sdv_model to the vehicle, then switch back
	// turn on the player sdv rig blackshadow anims
	sdv_actor.animname = org_animname;
	sdv_actor StopAnimScripted();
	
	//level.sdv_player_arms.not_driving = undefined;	// turn the driving anims back on
	guys[0] linkto( sdv_model, "tag_npc_origin" );	// was linked to mine target, now to sdv_model
	sdv_model unlink();	// no longer linked to our mine target

	// move the sub back to the vehicle before mounting it
	vel = (sdv Vehicle_GetVelocity());
	sdv_model move_close_and_link( sdv, 1.0*vel, 6*CONST_MPHTOIPS, vel );

	if (sdv_model ent_flag("lights"))
	{
		sdv_model ent_flag_clear("lights");
		sdv ent_flag_set("lights");
	}
	// now link our actor back to the vehicle, unhide it and cleanup
	sdv thread anim_generic_first_frame(sdv_actor,"wetsub_idle", "tag_player");
	origin = sdv GetTagOrigin( "tag_npc_origin" );
	angles = sdv GetTagAngles(  "tag_npc_origin" );
	sdv_actor forceTeleport( origin, angles );
	sdv_actor LinkToBlendToTag( sdv, "tag_npc_origin" );
	sdv_actor.blackshadow_driving = true;	// turn on the driving anims
    sdv thread anim_generic( sdv_actor, "wetsub_idle", "tag_player" );
    // the end of the above animation will cause a transition to the blackshadow animscript
    wait 0.05;
    sdv_actor anim_StopAnimScripted();
	sdv Show();
		
	sdv_model Delete();
	tgt_model Delete();
	scriptednode Delete();
}

move_close_and_link_end_early()
{
	flag_wait( "player_surfaces" );
	self notify( "stop_mcl" );
}


get_vehicle_match_speed( vehicle, target_origin )
{
	distspeedup= 1.0/30;
	forward = anglestoforward(vehicle.angles);
	right = anglestoright(vehicle.angles);
	up = anglestoup(vehicle.angles);
	
	forward = anglestoforward(self.angles);
	to_target = target_origin - self.origin;
	dist = VectorDot(forward,to_target);
	desiredspeed = vehicle Vehicle_GetSpeed();
	deltaspeed = dist*distspeedup;
	if (deltaspeed < -20)
		deltaspeed = -20;
	if (deltaspeed > 20)
		deltaspeed = 20;
	speed = desiredspeed + deltaspeed;
	if (speed < 0)
		speed = 0;
	return speed;
}

MAX_SUBMINE_AUTOPLANT_DIST = 360;
monitor_submine_plant()
{
	hint_display = false;
	hint_displayed = false;
	time = 0;
	holdtime = 0.0;
	finished = false;
	min_x = -360;
	max_x = 120;
	min_y = 0;
	max_y = 360;
	min_z = -72;
	max_z = 72;
	while (!finished)
	{
		sdv_origin = level.player_sdv gettagorigin("tag_light_l");
		mine2sdv = sdv_origin - level.mine_sub_target.origin;
		forward = AnglesToForward(level.mine_sub_target.angles);
		right = AnglesToRight(level.mine_sub_target.angles);
		up = AnglesToUp(level.mine_sub_target.angles);
		
		distance = Length(mine2sdv);
		x = VectorDot(forward,mine2sdv);
		y = VectorDot(right,mine2sdv);
		z = VectorDot(up,mine2sdv);
		
		// since aligning the sdv with the sub to start the animation can have issues if we are too far
		// off from the start orientation, don't allow triggering
		// we also require the sdv to be within 45 degrees of horizontal
		angles = level.russian_sub_02 GetTagAngles( "body" );
		forward = AnglesToForward( angles );
		angles = level.player_sdv GetTagAngles( "tag_body" );
		sdv_forward = AnglesToForward( angles );
		dp = VectorDot( forward, sdv_forward );

		hint_display = false;		
		if ((min_x <= x) && (x <= max_x) &&
			(min_y <= y) && (y <= max_y) &&
			(min_z <= z) && (z <= max_z) &&
			(dp > 0.707) && (abs(sdv_forward[2]) < 0.5) )
		{
			// see if the use button is pushed
			if ( level.player UseButtonPressed() )
				time += 0.05;
			else
				time = 0;
			hint_display = true;
			level.speed_above_sub = 0;	// hold the relative positions of the subs
			level.ally_sdv_mode = 2;
		}
		if (time > holdtime)
		{
			finished = true;
			if (hint_displayed)
			{
				level.player delaycall(0.05,::ForceUseHintOff);
				level.player delaycall(0.1,::UseHintsInVehicle, false );	// restore a frame later
			}
			thread submine_waitfor_trigger();
			thread submine_waitfor_plant();
			level.mine_sub_model hide();
		}
		else
		{
			if (hint_display != hint_displayed)
			{
				hint_displayed = hint_display;
				if (hint_display)
				{
					level.player UseHintsInVehicle(true);	// normally, UseHints aren't shown when on a vehicle
					level.player ForceUseHintOn( &"SCRIPT_PLATFORM_HINT_PLANTEXPLOSIVES" );
				}
				else
				{
					level.player ForceUseHintOff();
					level.player delaycall(0.05,::UseHintsInVehicle, false );	// restore a frame later
				}
			}
		}
		wait 0.05;
	}
}

monitor_player_and_russian_sub()
{
	flag_wait( "sub_done" );
	wait( 5 );
	lockon = false;
	maxspeed = level.max_chase_speed;
	distaheadforstop = -240.0;
	distbehindforslow = 240.0;
	reference_fwd_offset = 0;
	sub_speed_adjust = 2;
	level.mine_plant_started = false;
	thread monitor_submine_plant();
	while (!level.mine_plant_started)
	{
		if (isdefined(level.mine_sub_target))
		{
			sdv_origin = level.player_sdv gettagorigin("tag_light_l");
			// We're going to try to keep the player's sdv behind the mine
			rs_forward = AnglesToForward( level.russian_sub_02.angles );
			bs_forward = AnglesToForward( level.player_sdv.angles );
			dp = VectorDot( rs_forward, bs_forward );
			subspeed = (CONST_MPHTOIPS*level.russian_sub_02.veh_speed) + sub_speed_adjust;
			speed = maxspeed;
			if (dp > 0.9)
			{	// only manipulate the speed of the sdv if it is moving in the same direction as the sub
				mine_reference = level.mine_sub_target.origin + reference_fwd_offset * rs_forward;
				tomine = mine_reference - sdv_origin;
				fwddist2mine = VectorDot( tomine, rs_forward );
				if ( fwddist2mine < distaheadforstop )
					speed = 0;
				else if ( fwddist2mine > distbehindforslow )
					speed = maxspeed;
				else if ( fwddist2mine > 0 )
				{	// slowing to sub's speed
					ratio = fwddist2mine / distbehindforslow;
					speed = (maxspeed - subspeed)*ratio + subspeed;
				}
				else
				{	// slowing to 0
					ratio = fwddist2mine / distaheadforstop;
					speed = subspeed*ratio;
				}
			}
			SetSavedDvar( "vehSubmarineMaxForwardVel", "" + speed );
		}
		wait 0.05;
	}
	SetSavedDvar( "vehSubmarineMaxForwardVel", "320" );	// restore our max speed
}


toggle_lights(bool, bImmediate)
{
	if (bool  == "on")
	{
		foreach (sdv in level.sdvarray)
		{
			if (!isdefined(bImmediate) || !bImmediate)
			{
				stagger = randomfloatrange (0.0, 0.25);
				wait stagger;
			}
			if (isdefined(sdv.use_realtime_lights) && sdv.use_realtime_lights)
			{
				sdv ent_flag_set("realtime_lights");	// turn on the  realtime lights
				sdv ent_flag_clear( "lights" );			// turn off lights
			}
			else
			{
				sdv ent_flag_set( "lights" );	// lights are on
				sdv ent_flag_clear("realtime_lights");	// turn off the  realtime lights
			}
		}
	}
	else
	{
		level.player_sdv ent_flag_clear("realtime_lights");	// turn off the player's realtime lights
		foreach (sdv in level.sdvarray)
		{
			if (sdv == level.player_sdv)
				continue;
			if (!isdefined(bImmediate) || !bImmediate)
			{
				stagger = randomfloatrange (0.0, .25);
				wait stagger;
			}
			sdv ent_flag_clear( "lights" );	// lights are off 
			sdv ent_flag_clear("realtime_lights");	// turn off the  realtime lights
		}
		//level.overridelights = false;
	}
}

force_light_on_via_volume()
{
	flag_wait ("sdv_force_lights_on");
	//thread toggle_lights("on");
}



//*************Sub ride events
monitor_mineplant_fail()
{
	flag_wait_either("sub_finished", "reach_end_of_sub_path" );
	if ( !flag( "aud_planting_submine" ) )
		thread fail_sub_mine_plant();
}

attach_mine_target_to_sub( sub )
{
	// use the mine_ref animation to put it in the correct place
	level.mine_sub_model = spawn( "script_model", sub.origin );
	level.mine_sub_model setmodel( "weapon_underwater_limpet_mine_obj" );
	level.mine_sub_model.animname = "mine";
	level.mine_sub_model SetAnimTree();
	sub anim_first_frame_solo( level.mine_sub_model, "mine_ref", "body" );
	level.mine_sub_model linkto( sub, "body" );
	level.mine_sub_target = spawn_tag_origin();
	level.mine_sub_target.origin = level.mine_sub_model.origin + ( 0, 12, 0 );
	level.mine_sub_target.angles = sub.angles;
	level.mine_sub_target linkto( sub );
}

attach_ally_mine_target( name, sub, offset )
{
	origin = sub.origin;
	forward = anglestoforward(sub.angles);
	right = anglestoright(sub.angles);
	up = anglestoup(sub.angles);
	origin = origin + offset[0]*forward + offset[1]*right + offset[2]*up;
	level.ally_mine_sub_target[name] = spawn_tag_origin();
	level.ally_mine_sub_target[name].origin = origin;
	level.ally_mine_sub_target[name].angles = sub.angles;
	level.ally_mine_sub_target[name] linkto( sub, "body" );
}

russian_sub_intro()
{
	flag_wait( "start_submarine02" );
	thread vo_wetsub_russian_sub();
}

switch_oscar2_lights( src, dst )
{
	dst.light_fx = src.light_fx;
	src.light_fx = undefined;
	foreach (fx_ent in dst.light_fx)
	{
		stopfxontag(fx_ent.fx, fx_ent, "tag_origin"); 
		fx_ent unlink();
		fx_ent.origin = dst GetTagOrigin( fx_ent.tag );
		fx_ent.angles = dst GetTagAngles( fx_ent.tag );
		fx_ent linkto( dst, fx_ent.tag );
		wait 0.05;
		playfxontag(fx_ent.fx, fx_ent, "tag_origin"); 
	}
}

setup_oscar2_light( fx, tag )
{
	fx_ent = spawn_tag_origin();
	fx_ent.origin = self GetTagOrigin( tag );
	fx_ent.angles = self GetTagAngles( tag );
	fx_ent.tag = tag;
	fx_ent.fx = fx;
	fx_ent linkto( self, tag );
	self.light_fx[self.light_fx.size] = fx_ent;
	playfxontag(fx,fx_ent,"tag_origin"); 
}

setup_oscar2_lights()
{
	fx = getfx("submarine_red_light");
	self.light_fx = [];
}

bob_player_sdv()
{
	sdv = level.player_sdv;
	coll = getent( "blackshadow_tube", "targetname" );
	base_origin = sdv.origin;
	coll.angles = (sdv.angles[0],sdv.angles[1],0);
	up = AnglesToUp(coll.angles);
	right = AnglesToRight(coll.angles);
	z_off = 12;
	coll.origin = sdv.origin + z_off*up;
	preferred_z = -2184.0;
	speed = 12.0;	// ips
	max_dist_per_frm = speed*0.05;
	save_maxLatVel = getdvarfloat("vehSubmarineMaxLateralVel");
	save_maxLatDamp = getdvarfloat("vehSubmarineLateralDampening");
	setsaveddvar( "vehSubmarineMaxLateralVel", "200" );
	setsaveddvar( "vehSubmarineLateralDampening", "0.99" );
	setsaveddvar( "vehSubmarineAllowInSolid", "1" );
	// first, move the player's sdv to the preferred location
	while (!flag("sdvs_chase_sub"))
	{
		coll.angles = (sdv.angles[0],sdv.angles[1],0);
		forward = AnglesToForward(coll.angles);
		up = AnglesToUp(coll.angles);
		ref_origin = sdv.origin + z_off*up;
		dist = preferred_z - coll.origin[2];
		vel = sdv Vehicle_GetVelocity();
		dp = VectorDot(vel,forward);	// forward velocity
		if ((abs(dist) < 4.0) && (dp < 0.5))
			break;
		if (dist > max_dist_per_frm)
			dist = max_dist_per_frm;
		else if (dist < -1*max_dist_per_frm)
			dist = -1*max_dist_per_frm;
		delta = ref_origin - coll.origin;
		forward = AnglesToForward(coll.angles);
		dp = VectorDot(delta,forward);
		coll.origin = coll.origin + (0,0,dist) + dp*forward;
		wait 0.05;
	}	
	setsaveddvar( "vehSubmarineMaxLateralVel", ""+save_maxLatVel );
	setsaveddvar( "vehSubmarineLateralDampening", ""+save_maxLatDamp );
	base_origin = sdv.origin;
	coll.origin = base_origin;
	coll.angles = sdv.angles;
	mag = 18;
	mn = 6;
	time = 0;
	movetime = 0;
	tgt_origin = base_origin;
	start_origin = base_origin;
	offset = (0,0,0);
	// now start the bobbing
	while (!flag("sdvs_chase_sub"))
	{
		if (time >= movetime)
		{
			/*
			up_value = RandomFloatRange( mn, mag );
			if (randomfloat(1.0) > 0.5)
				up_value *= -1;
			*/
			up_value = 0;
			right_value = RandomFloatRange( mn, mag );
			if (randomfloat(1.0) > 0.5)
				right_value *= -1;
			offset = up_value*up + right_value*right;
			tgt_origin = base_origin + offset;
			start_origin = coll.origin;
			offset = tgt_origin - start_origin;
			movetime = RandomFloatRange(5,8);
			time = 0;
		}
		
		f = SmoothValue(time/movetime);
		coll.origin =  start_origin + f*offset;
		time += 0.05;
		wait 0.05;
	}
	setsaveddvar( "vehSubmarineAllowInSolid", "0" );
	coll Delete();
}

russian_sub_setup()	// sets up the russian sub (waits until start_submarine02 is set
{
	flag_wait( "start_submarine02" );
	thread stop_player_sdv();
	thread torpedo_fire();
	thread bob_player_sdv();
	wait( 2 );
	level.russian_sub_02 = maps\_vehicle::spawn_vehicle_from_targetname( "submarine02" );
	level.russian_sub_02.animname = "russian_sub";
	level.russian_sub_02 thread monitor_mineplant_fail();
	level.russian_sub_02 thread monitor_propeller_vibration();
	level.russian_sub_02 thread monitor_propeller_death();
	level.russian_sub_02 SetAnim( level.scr_anim[level.russian_sub_02.animname]["propellers"][0], 1.0, 0.2, 2.0 );
	maps\ny_harbor_sdv_drive::AddSonarSubTarget( level.russian_sub_02 );
	flag_set( "russian_sub_spawned" );
	level.player notify( "stop_friendly_bubbles" );
	thread toggle_lights( "off", true );
	level.russian_sub_02 setup_oscar2_lights();
}

monitor_propeller_vibration()
{
	level endon( "entering_mine_plant" );
	level.player endon( "death" );
	
	//thread anim_rumble();
	rumble_dist = 2000;
	// start controller rumble when player is within distance threshold to propeller
	while( 1 )
	{
		prop_left = self GetTagOrigin( "tag_left_porpeller" );
		prop_right = self GetTagOrigin( "tag_right_propeller" );
		dist_left = distance( level.player.origin, prop_left );
		dist_right = distance( level.player.origin, prop_right );
		
		if( ( dist_left <= rumble_dist ) || ( dist_right <= rumble_dist ) )
		{
			level.player PlayRumbleOnEntity( "viewmodel_small" );
		}
		
		wait( 0.05 );
	}
}

anim_rumble()
{
	flag_wait( "submine_planted" );
	
	counter = 0;
	time = 6.5;
	
	while( counter < time )
	{
		level.player PlayRumbleOnEntity( "viewmodel_small" );
		wait( 0.05 );
		counter += 0.05;
	}
}

monitor_propeller_death()
{
	level endon( "submine_planted" );
	level.player endon( "death" );
	
	prop_length = 132;
	while( 1 )
	{
		prop_left = self GetTagOrigin( "tag_left_porpeller" );
		prop_right = self GetTagOrigin( "tag_right_propeller" );
		dist_left = distance( level.player.origin, prop_left );
		dist_right = distance( level.player.origin, prop_right );
		
		if( ( dist_left <= prop_length ) || ( dist_right <= prop_length ) )
		{
			//player is within the distance from center + length or propeller blade so he gets chopped up
			level notify( "new_quote_string" );
			SetDvar( "ui_deadquote", &"NY_HARBOR_PROP_DEATH" );
			level.player kill();
		}
		
		wait( 0.05 );
	}
}

torpedo_fire()
{
	wait( 1 );
	torpedo_1 = spawn_vehicle_from_targetname_and_drive( "oscar_torpedo_1" );
	aud_send_msg("torpedo_1", torpedo_1);
	maps\ny_harbor_sdv_drive::AddSonarTarget( torpedo_1, 1 );
	wait( 0.5 );
	torpedo_2 = spawn_vehicle_from_targetname_and_drive( "oscar_torpedo_2" );
	aud_send_msg("torpedo_2", torpedo_2);
	maps\ny_harbor_sdv_drive::AddSonarTarget( torpedo_2, 1 );
	flag_wait( "detonate_torpedo" );
	
	if( isDefined( torpedo_2 ) )
	{
		torpedo_2 delete();
	}
	
	wait( 5 );
	if( isDefined( torpedo_1 ) )
	{
		torpedo_1 delete();
	}
}

submarine_spawn02()
{
	flag_wait ("russian_sub_spawned");
	thread submarine_sdv_shut_down();
	
	flag_set ("russian_sub_event");
	thread toggle_lights("off");
	
	thread gopath( level.russian_sub_02 );
	
	aud_send_msg("sub_approach", level.russian_sub_02);
	
	level.russian_sub_02 thread monitor_mineplant_fail();
	thread attach_mine_target_to_sub( level.russian_sub_02 );
	
	grinch_offset = (-2060, 275, -130 );
	//thread test_offset( level.russian_sub_02, ally_offset );
	thread attach_ally_mine_target( "grinch", level.russian_sub_02, grinch_offset );
	
	sdv03_offset = (-2060, 190, -240 );
	//thread test_offset( level.russian_sub_02, sdv03_offset );
	thread attach_ally_mine_target( "sdv03", level.russian_sub_02, sdv03_offset );
	
	//thread vo_wetsub_russian_sub(1);
	//wait 2;
	thread sdv_pause_1();
}

stop_player_sdv()
{
	//level.player_sdv Vehicle_SetSpeed( 0, 15, 45 );
	thread set_dvar_overtime( "vehSubmarineMaxForwardVel", "0", 3 );
	level.player FreezeControls( true );
	if( !isDefined( level.start_at_watching_sub ) )
		wait( 3 );
	
	level.player_sdv hidepart( "tag_glowpanel" );
	SetSavedDvar( "vehSubmarineMaxForwardVel", "0" );
	SetSavedDvar( "vehSubmarineMaxForwardAccel", "0" );
	SetSavedDvar( "vehSubmarineForwardDampening", "0.95" );	// slow down the sdv quickly
	SetSavedDvar( "vehSubmarineMaxStoppedYawAccel", "0" );
	SetSavedDvar( "vehCam_yawTurnRate", "130" );
	SetSavedDvar( "vehCam_yawClamp", "20" );
	SetSavedDvar( "vehSubmarineControls", "1" );
	SetSavedDvar( "vehCam_pitchClamp", "8" );
	SetSavedDvar( "vehSubmarineMaxStoppedPitchAccel", "0" );
	level.player FreezeControls( false );
	wait 3;
	SetSavedDvar( "vehSubmarineForwardDampening", "0.99" );
}

test_offset( sub, offset )
{
	/#
	while (true)
	{
		origin = sub.origin;
		forward = anglestoforward(sub.angles);
		right = anglestoright(sub.angles);
		up = anglestoup(sub.angles);
		origin = origin + offset[0]*forward + offset[1]*right + offset[2]*up;
		maps\_shg_common::draw_point( origin, 24, (1,1,1) );
		wait 0.05;
	}
	#/		
}

sdv_pause_1()
{
	time = 0.0;
	duration = 31.0;
	anm = level.scr_anim["generic"]["wetsub_acknowledge"];
	acktime = GetAnimLength(anm);

	level notify("sdv_done_leading");	// stop a bunch of the leading logic, so we can wait at the wait nodes
	// sdvs should stop when they hit the wait node, so wait the time we need to for the Sub
	wait duration-acktime;
	
//	level.lead_sdv thread play_alt_idle_on_pilot( "wetsub_acknowledge", 0.0 );
	wait acktime;

	level.lead_sdv.pilot StopAnimScripted();
	
	level.russian_sub_02 Vehicle_SetSpeed( 8, 2, 2 ); //slow oscar down so you can actually catch up to it
	level.grinch_sdv notify("stop_lead_sdv_think");	// stop having him adjust speed based on player
	level.ally_sdv_mode = 1;
	
	thread grinch_submine_plant();
	thread sdv03_submine_plant();

	thread toggle_lights("on");
	level.player_sdv thread maps\ny_harbor_sdv_drive::friendly_bubbles();

	lerp_time = 0.25;
	thread set_dvar_overtime( "vehCam_yawClamp", "0.1", lerp_time );
	thread set_dvar_overtime( "vehCam_pitchClamp", "0.1", lerp_time );
	wait( lerp_time );
	level.player_sdv showpart( "tag_glowpanel" );
	SetSavedDvar( "vehSubmarineMaxStoppedYawAccel", "40" );
	SetSavedDvar( "vehCam_yawTurnRate", "260" );
	SetSavedDvar( "vehSubmarineMaxForwardVel", ""+level.max_chase_speed );
	SetSavedDvar( "vehSubmarineMaxForwardAccel", "85" );
	SetSavedDvar( "vehSubmarineForwardDampening", "0.99" );
	SetSavedDvar( "vehSubmarineMaxUpPitch", "60" );
	SetSavedDvar( "vehSubmarineMaxDownPitch", "60" );
//	SetSavedDvar( "vehCam_yawClamp", "0.1" );
	SetSavedDvar( "vehSubmarineMaxStoppedPitchAccel", "20" );
//	SetSavedDvar( "vehCam_pitchClamp", "0.1" );
	SetSavedDvar( "vehSubmarineControls", "2" );
	
	delaythread( 5, maps\ny_harbor_sdv_drive::setup_contact_mines ); //turn mines back on
	
	flag_set("sdvs_chase_sub");
	autosave_by_name( "russian_sub_event" );
	flag_wait( "submine_planted" );
	
	autosave_by_name( "submine_planted" );
	
	SetSavedDvar( "vehSubmarineMaxForwardVel", "320" );
	SetSavedDvar( "vehSubmarineMaxForwardAccel", "85" );
	SetSavedDvar( "vehSubmarineForwardDampening", "0.99" );
	level.speed_above_sub = 20;
}

set_dvar_overtime( dvar, value, time )
{
	counter = 0;
	current = GetDvarFloat( dvar );
	value = float(time);
	deltaValue = value - current;
	value_frac = 0.05 * ( deltaValue / time );
	numsteps = int(time/0.05);
	while( numsteps > 0 )
	{
		current += value_frac;
		SetSavedDvar( dvar, ""+current );
		numsteps--;
		wait( 0.05 );
	}
	SetSavedDvar( dvar, ""+value );
}

submarine_sdv_shut_down()
{
	flag_wait("russian_sub_event");
	thread toggle_lights("off");
}

monitor_sdv_control_invert()
{
	level endon("sdv_ride_done");
	SetSavedDvar( "vehSubmarineInvertUpDown", 1 );	// start with inverted
	
	/*
	for ( ;; )
	{
		while (!level.player AdsButtonPressed())
			wait 0.05;
		SetSavedDvar("vehSubmarineInvertUpDown",1-getdvarint("vehSubmarineInvertUpDown"));
		while (level.player AdsButtonPressed())
			wait 0.05;
	}
	*/
}

wait_to_turn_on_players_light()
{
	level waittill("msg_torch_flare_fx_end");
	wait 0.5;
	level.player_sdv.use_realtime_lights = true;	// player is using realtime lights
	level.player_sdv ent_flag_set("realtime_lights");	// turn on the player's realtime lights
}

wait_player_enter( bStartAtWatch )
{
	for ( ;; )
	{
		pilot = flag_wait("entering_sdv_from_anim");
		assert(isdefined(pilot));
		if ( pilot.classname == "player" )
			break;
		wait 0.05;
	}
	//thread monitor_sdv_control_invert();
	if (bStartAtWatch)
	{
		level.player_sdv ent_flag_set("realtime_lights");
	}
	else
	{
		thread wait_to_turn_on_players_light();
	}
	level.player thread scubamask_on_player(false);
	level.lead_sdv ent_flag_set( "lights" );	// lights are on for sandman
	level.grinch_sdv ent_flag_set( "lights" );	// lights are on for grinch

	handle_hero_sdvs( bStartAtWatch );
	level maps\ny_harbor_sdv_drive::player_enter_submarine( self, pilot, true );
	level.sdv_player_arms thread manage_sdv_drive();
	
	// give instructions
	flag_set( "obj_plantmine_given" );
	hint_string = "";
/*	if( GetDvarInt( "vehsubmarinecontrols" ) == 1 )
	{
		hint_string = "hint_sdv_drive";
	}
	if( GetDvarInt( "vehsubmarinecontrols" ) == 2 )
	{
		hint_string = "hint_sdv_drive_2";
	}

	thread display_hint( hint_string );
*/	

	// start the lead sdv
	if (isdefined(level.lead_sdv) && isDefined( level.grinch_sdv ) )
	{
		level.lead_sdv thread lead_sdv_think(level.lead_sdv);
		level.grinch_sdv thread lead_sdv_think( level.grinch_sdv );
		thread monitor_player_keeping_close( [level.lead_sdv, level.grinch_sdv] );
		thread initiate_friendly_sdvs(bStartAtWatch);
	}
}

lead_sdv_beacon()
{
	while( !flag( "russian_sub_event" ) )
	{
		PlayFxOnTag( getfx( "lead_sdv_beacon" ), self, "TAG_ORIGIN" );
		StopFxOnTag( getfx( "lead_sdv_beacon" ), self, "TAG_ORIGIN" );
		wait( 2 );
	}
	
	StopFxOnTag( getfx( "lead_sdv_beacon" ), self, "TAG_ORIGIN" );
}

set_sdv_drive_anim_params(anms, wgts)
{
	// first, we normalize the weights
	accum = 0;
	for (axis = 0; axis<2; axis++)
	{
		for (dir = 0; dir<2; dir++)
		{
			accum += wgts[axis][dir];
		}
	}
	if (accum < 1)
	{
		wgts[2] = 1-accum;
		accum = 1;
	}
	else
		wgts[2] = 0;
	for (axis = 0; axis<2; axis++)
	{
		for (dir = 0; dir<2; dir++)
		{
			wgts[axis][dir] = wgts[axis][dir]/accum;
		}
	}
	
	for (axis = 0; axis<2; axis++)
	{
		for (dir = 0; dir<2; dir++)
		{
			self setanim(anms[axis][dir], wgts[axis][dir], 0.2, 1);
		}
	}
	self setanim(anms[2], wgts[2], 0.2, 1);
}

set_sdv_nodrive_anim_params( anms )
{
	for (axis = 0; axis<2; axis++)
	{
		for (dir = 0; dir<2; dir++)
		{
			self setanim(anms[axis][dir], 0.0, 0.2, 1);
		}
	}
	self setanim(anms[2], 0.0, 0.2, 1);
}

// expects self to be the viewmodel
manage_sdv_drive()
{
	level endon("sdv_ride_done");
	anms = [];
	anms[0] = [];	// x axis
	anms[0][0] = level.scr_anim[ "player_sdv_rig" ][ "sdv" ][ "turn_left" ];
	anms[0][1] = level.scr_anim[ "player_sdv_rig" ][ "sdv" ][ "turn_right" ];
	anms[1] = [];	// y axis
	anms[1][0] = level.scr_anim[ "player_sdv_rig" ][ "sdv" ][ "turn_down" ];
	anms[1][1] = level.scr_anim[ "player_sdv_rig" ][ "sdv" ][ "turn_up" ];
	anms[2] = level.scr_anim[ "player_sdv_rig" ][ "sdv" ][ "idle" ];
	
	wgts = [];	// current weights for the anims
	wgts[0] = [];	// x axis
	wgts[1] = [];	// y axis
	wgts[3] = 1;	// idle
	
	while (true)
	{
		// each frame, we get the control input and convert that to a weight and frame for the four anims
		input_ = level.player GetNormalizedMovement();
		input[0] = input_[1];
		input[1] = -1*input_[0];
		for (axis = 0; axis<2; axis++)
		{
			if (input[axis] < 0)
			{
				wgts[axis][0] = -1*input[axis];
				wgts[axis][1] = 0;
			}
			else if (input[axis] > 0)
			{
				wgts[axis][1] = input[axis];
				wgts[axis][0] = 0;
			}
			else
			{
				wgts[axis][0] = 0;
				wgts[axis][1] = 0;
			}
		}
		if (isdefined(self.not_driving))
			self set_sdv_nodrive_anim_params( anms );
		else
		self set_sdv_drive_anim_params(anms, wgts);
		wait 0.05;
	}
}

initiate_friendly_sdvs (bStartAtWatch)
{
	level endon("sdv_ride_done");
	while (level.player_sdv.veh_speed <= 0)
		wait 0.5;
		
	flag_set( "player_sdv_moving" );
	foreach (sdv in level.sdvarray)
	{
		if (sdv != level.player_sdv)
			sdv thread ally_sdv_speed_control(bStartAtWatch);
	}
}

gradual_speed_change(sdv,speed)
{
	if (!flag("sdvs_chase_sub") && isdefined(sdv.vehicle_flags) && isdefined(sdv.vehicle_flags["sdvs_chase_sub"]) && sdv.vehicle_flags["sdvs_chase_sub"] )
		return;	// don't set it if we're slowing down for a flag_wait and haven't set the flag yet
	cSpeed = sdv.veh_speed;
	// set accel/deccel to reach target in around 2 seconds
	dSpeed = abs(cSpeed - speed);
	accel = dSpeed/2.0;
	if (accel < 2)
		accel = 2;
	deccel = accel;
	if (deccel < 25)
		deccel = 25;
	sdv Vehicle_SetSpeed(speed, accel, deccel);
}

ally_sdv_speed_monitor_wait_nodes()
{
	level endon("sdv_ride_done");
	self endon("reached_end_node");
	self endon("death");
	self endon("end_speed_control");
	while (true)
	{
		self waittill("reached_wait_node");
		level.ally_sdv_mode = 3;
	}	
}

MAX_DECCEL=20;
ally_sdv_speed_control(bStartAtWatch)
{
	if (!isdefined(level.ally_sdv_mode))
		level.ally_sdv_mode = 0;
	level endon("sdv_ride_done");
	self endon("reached_end_node");
	self endon("death");
	self endon("end_speed_control");
	level.speed_above_sub = 10;
	flag_wait( "tunnel_exit" );
	autosave_by_name( "tunnel_exit" );
	self thread ally_sdv_speed_monitor_wait_nodes();
	self gopath( self );

	// for now, we're assuming they never stop, so just turn on the motor stuff
	self ent_flag_set( "moving" );
	if (!bStartAtWatch)
		self ent_flag_clear( "lights" );	// lights are off for everyone for now
	prv_mode = -1;
	defaultwaittime = 1.0;
	waittime = defaultwaittime;
	base_dist = RandomFloatRange( 0, 480 );
	
	while (true)
	{
		wait waittime;
		waittime = defaultwaittime;
		if (flag("sdvs_chase_sub") && isdefined(level.russian_sub_02) && (level.russian_sub_02 Vehicle_GetSpeed() <= 0.1))
		{	// trying to ensure we catch the end of the sub path
			flag_set("sub_finished","targetname");
			break;	// russian sub done with it's path, so stop matching it (we've failed mission)
		}
		if (!flag("sdvs_chase_sub") && isdefined(self.vehicle_flags) && isdefined(self.vehicle_flags["sdvs_chase_sub"]) && self.vehicle_flags["sdvs_chase_sub"] )
			continue;
		player_sdv_on_spline = level.player_sdv_pos_on_spline; // this will be different for each sdv
		new_speed_seed = RandomFloatRange( -4, 2 );
		rand_ideal_dist = RandomFloatRange( 400, 500 );
		switch(level.ally_sdv_mode)
		{
			case 0:	// at the beginning, getting too the wait for sub spot
				if (isdefined(self.leader))
					break;	// the lead subs are adjusted separately during mode 0
				// we want to ensure we are in front of the player by more than closestdist and no more than maxdist
				closestdist = base_dist + 200;
				maxdist = base_dist + rand_ideal_dist;
				dir = AnglesToForward(self.angles);
				p2s = self.origin - level.player_sdv.origin;
				dp = VectorDot(dir,p2s);	// this is the distance from the player's sdv to this sdv in the direction sdv is facing
				dist = Length(p2s);			// this is the world space distance
				pSpeed = level.player_sdv Vehicle_GetSpeed();
				nSpeed = self Vehicle_GetSpeed();
				if (dp < closestdist)
				{	// speed up
					nSpeed = pSpeed + 2;
					waittime = 0.1;
				} 
				else if (dp > maxdist)
				{	// slow down
					nSpeed = pSpeed - 2;
					waittime = 0.1;
				}
				else
				{	// maintain distance with some small variation in speed
					dSpeed = pSpeed - nSpeed;
					if ((dSpeed < -5) || (dSpeed > 5))
						waittime = 0.1;
					nSpeed += 0.5*dSpeed + RandomFloatRange(-0.5,0.5);
				}
				if (nSpeed <= 0)
					nSpeed = 0.0;
				accel = 0.5*nSpeed;
				if (nSpeed > 1)
					accel = 0.5*nSpeed;
				else
					accel = 0.5;
				if (nSpeed > 5)
					deccel = nSpeed;
				else
					deccel = MAX_DECCEL;	// ensure we can come to a stop quickly
				self Vehicle_SetSpeed( nSpeed, accel, deccel );
				break;
			case 1: // catch up with the russian sub, but stay close to player
				dist = distance(level.russian_sub_02.origin, self.origin);
				nSpeed = level.russian_sub_02.veh_speed;
				newSpeed = nSpeed + new_speed_seed;
				if (newSpeed < 1)
					continue;
				
				in_fov = within_fov_of_players( self.origin, Cos( 45 ) );
	
				if (  dist >= 600 && !in_fov) 
				{	// try to catchup faster when we're not in fov
					thread gradual_speed_change( self, newSpeed + 30 );
				}
				else if ( ( level.player_sdv.veh_speed > 0 ) && dist < 600 && dist > 200 )
					thread gradual_speed_change( self, newSpeed );	// maintain our varying speed
				else if ( dist > rand_ideal_dist )
				{	// allow player to catch up some
					if ( newSpeed > 1 )
						thread gradual_speed_change( self, newSpeed -1 );
				}
				else if ( dist <= 300 )
				{	// player is getting too close
					newSpeed = nSpeed + level.russian_sub_02.veh_speed;	// double player's speed
					if (in_fov)
						newSpeed += 1;	// faster when in view than when not?
					else
						newSpeed -= 1;
					if (newSpeed > 0)
						thread gradual_speed_change( self, newSpeed );
				}
				break;
			case 2:	// hold position with russian sub, then zoom ahead after planting mine
				if (prv_mode != level.ally_sdv_mode)
					level.russian_sub_02 endon("death");
				speed = level.russian_sub_02 Vehicle_GetSpeed();
				variance = RandomFloatRange(-1.0, 1.0);
				speed += level.speed_above_sub + variance;
				self Vehicle_SetSpeed( speed, 10, 25 );
				break;
			case 3:	// allow someone else to handle SetSpeed
				break;
		}
		prv_mode = level.ally_sdv_mode;
	}	
}

sdv_dist_logic()
{
	//set initial distance tollerances for lead SDV
	//old numbers: 960/720/360
	level.sdv_wait_for_player_dist = 620;
	level.sdv_ideal_dist_from_player = 420;
	level.sdv_too_close_to_player = 260;
}

sdv_speed_monitor()
{
	level endon("sdv_ride_done");
	self endon("sdv_done");
	while (true)
	{
		if (self.veh_speed >= 5)
		{
			if (!self ent_flag("moving"))
				self ent_flag_set("moving");
		}
		else
		{
			if (self ent_flag("moving"))
				self ent_flag_clear("moving");
		}
		wait 0.1;
	}
}

cleanup_sdv_realtime_lights()
{
	self waittill_any("death","sdv_done","stop_light_control");
	if (isdefined(self.realtime_light_tag))
	{
		if (self ent_flag( "realtime_lights" ))
			stopfxontag( getfx( "flashlight_spotlight" ), self.realtime_light_tag, "tag_origin" );
		self.realtime_light_tag Delete();
		self.realtime_light_tag = undefined;
	}
}

control_sdv_realtime_lights()
{
	self endon("death");
	self endon("sdv_done");
	self endon("stop_light_control");
	self ent_flag_init( "realtime_lights" );
	self.realtime_light_tag = spawn_tag_origin();
	self.realtime_light_tag.origin = self GetTagOrigin("tag_light_l");
	self.realtime_light_tag.angles = self GetTagAngles("tag_light_l");
	self.realtime_light_tag linkto(self,"tag_light_l");
	self thread cleanup_sdv_realtime_lights();
	while (true)
	{
		self ent_flag_wait( "realtime_lights" );
		PlayFxOnTag(getfx("flashlight_spotlight"), self.realtime_light_tag, "tag_origin");
		self.light_on_start = gettime();	// used when moving lights to another entity
		self ent_flag_waitopen( "realtime_lights" );
		stopfxontag( getfx( "flashlight_spotlight" ), self.realtime_light_tag, "tag_origin" );
	}
}

monitor_player_keeping_close(sdvs)
{
	//level.autosave_check_override = ::XXXX;
	thread maps\ny_harbor_code_vo::sdv_follow_nag_lines();
	CONST_WARNING_TO = 3.0;
	CONST_FAIL_TO = 12.0;
	warning_to = CONST_WARNING_TO;
	fail_to = CONST_FAIL_TO;

	flag_wait("wait_for_player");
	wait 0.1;	// allow other threads to initialize the stopped var

	for ( ;; )
	{
		if ( flag("lead_sdv_reached_end") )
			break;
		stopped = true;
		foreach (sdv in sdvs)
		{
			if (!sdv.stopped)
				stopped = false;	// if either is moving, we call it good
		}
		if (stopped)
		{
			if (warning_to <= 0.0)
			{	// time to give a warning for frost to keep up
				flag_set("vo_sdv_follow_nag");
			}
			warning_to -= 0.05;
			fail_to -= 0.05;
			if (fail_to <= 0.0)
			{
				level notify( "new_quote_string" );
				SetSavedDvar( "vehSubmarineMaxForwardVel", "0" );
				SetSavedDvar( "vehSubmarineMaxForwardAccel", "0" );
				SetDvar( "ui_deadquote", &"NY_HARBOR_SDV_FAIL_QUOTE" );	// TODO: need another wrapper
				maps\_utility::missionFailedWrapper();
				wait 1000;	// shouldn't come back
			}
		}
		else
		{	// reset our timeouts every frame we're moving
			flag_clear("vo_sdv_follow_nag");
			warning_to = CONST_WARNING_TO;
			fail_to = CONST_FAIL_TO;
		}
		wait 0.05;
	}
	flag_clear("vo_sdv_follow_nag");	// ensure we stop the vo
	level notify("stop_sdv_follow_nag");
	//level.autosave_check_override = undefined;
}

lead_sdv_think( lead_sdv )
{
	level endon("sdv_ride_done");
	level endon("sdv_done_leading");
	lead_sdv endon("stop_lead_sdv_think");
	lead_sdv endon("reached_wait_node");
	
	lead_sdv.leader = true;	// flag as leader so speed isn't adjusted in two places during mode 0
	//start the thread that determines the distances for the lead sdv
	thread sdv_dist_logic();
	wait 0.05;
	
	// wait until the player's sub starts moving
	if (!isdefined(level.player_sdv))
		return;
	
	for ( ;; )
	{
		if (level.player_sdv.veh_speed > 1.5)
			break;
		wait 0.05;
	}
	
	// start on the path at our desired speed
	//lead_sdv gopath( lead_sdv );
	flag_set("wait_for_player");
	lead_sdv ent_flag_set( "lights" );	// lights are on for everyone for now
	//level.player_sdv ent_flag_set( "lights" );	// we might want to only turn on the lights at specific times

	lead_sdv Vehicle_SetSpeed(5, 15, 25);
	lead_sdv thread wait_for_lead_sdv_to_reach_end( lead_sdv );
	
	// check our distance from the player's sub and slow down if we get too far
	lead_sdv.stopped = false;
	player_stopped = true;
	for ( ;; )
	{
		if ( flag("lead_sdv_reached_end") )
			break;
			
		if ( !IsDefined( level.player_sdv_pos_on_spline ) )
        {
			flag_clear("vo_sdv_follow_nag");
        	wait 0.05;
        	continue;
        }
        if ( level.ally_sdv_mode == 3 )
        {
			flag_clear("vo_sdv_follow_nag");
        	wait 0.05;
        	continue;
        }
		if (!flag("sdvs_chase_sub") && isdefined(self.vehicle_flags) && isdefined(self.vehicle_flags["sdvs_chase_sub"]) && self.vehicle_flags["sdvs_chase_sub"] )
		{
			flag_clear("vo_sdv_follow_nag");
			wait 0.05;
			continue;
		}

		forward = anglestoforward(level.lead_sdv.angles);
		// if we reach the end of the path, break out of this 
		player_sdv_on_spline = level.player_sdv_pos_on_spline;
		dist = distance(player_sdv_on_spline, lead_sdv.origin);
		lead_to_player = player_sdv_on_spline - lead_sdv.origin;
		dot = vectordot(forward,lead_to_player);	// use this to determine if the player has gotten ahead of the player 
		
		if ((dist > level.sdv_wait_for_player_dist) && !lead_sdv.stopped && (dot < 0))	// 80 ft and the player is behind
		{	// come to a stop if too far away
			lead_sdv Vehicle_SetSpeed(0, 15, 25);
			lead_sdv.stopped = true;
		}
		else if ((dist < level.sdv_too_close_to_player) || (dot >= 0))	// 30 ft or the player is ahead
		{
			lead_sdv Vehicle_SetSpeed(level.player_sdv.veh_speed+1, 15, 25);
			lead_sdv.stopped = false;
		}
		else if (dist < level.sdv_ideal_dist_from_player)	// 60 ft
		{	// we were stopped and the player is within 60 ft, so start moving again
			if (level.player_sdv.veh_speed > 5)
				lead_sdv Vehicle_SetSpeed(level.player_sdv.veh_speed, 10, 25);
			else
				lead_sdv Vehicle_SetSpeed(5, 15, 25);
			lead_sdv.stopped = false;
		}
		if (level.player_sdv.veh_speed > 5)
		{
			if (player_stopped)
			{
				player_stopped = false;
			}
		}
		else
		{
			if (!player_stopped)
			{
				player_stopped = true;
			}
		}
		wait 0.05;
	}
	
	// at this point, the lead sub is at the end of the path
	lead_sdv.leader = undefined;	// clear flag as leader so speed can be adjusted by other monitor
}

wait_for_lead_sdv_to_reach_end(lead_sdv)
{
	lead_sdv endon("death");
	lead_sdv endon("sdv_done");
	level waittill("sdv_done_leading");	// stop a bunch of the leading logic, so we can wait at the wait nodes
	flag_set("lead_sdv_reached_end");
}

setup_sdv_threads(sdv, player)
{
	sdv thread control_sdv_realtime_lights();
	sdv thread sdv_speed_monitor();
	if (isdefined(player))
	{
		sdv thread maps\ny_harbor_fx::player_sdv_fx();
	}
	else
	{
		sdv thread maps\ny_harbor_fx::npc_sdv_fx();
	}
}

control_sdv_lights()
{
	level endon("sdv_ride_done");
	flag_wait("light_toggle_on_1");
	thread toggle_lights( "on" );
}

/**************************scene setup*************************************************/

wait_for_set_uw_charlighting()
{
	flag_wait("leaving_tunnel");
	maps\ny_harbor::SetUnderwaterCharLighting();
}

wait_for_vd_fogvision()
{
	thread wait_for_set_uw_charlighting();
	flag_wait("leaving_tunnel_visionchange");
	level.player thread viewdependent_fog_vision_update( 5.0 );
}

/**************************************************************************************/
below_water_art_and_ambient_setup( bUseRigApproachFog, bViewDependentFV )
{		
	if ( isdefined(  bUseRigApproachFog ) )
	{
		vision_set_fog_changes( "ny_harbor_underwater", 0 );
		thread underwater_fog_approaching_rig( 0 );
	}

	else
	{
		thread vision_set_fog_changes( "ny_harbor_underwater", 0 );
	}
	if (isdefined(bViewDependentFV) && bViewDependentFV)
		level.player thread viewdependent_fog_vision_update();
//	SetCullDist( 8000 );
		
	delaythread( 2.0, ::water_depth_of_field, true );

/* DOF disabled because of fx issues	
	level.dofDefault[ "nearStart" ] = 0;
	level.dofDefault[ "nearEnd" ] = 31;
	level.dofDefault[ "farStart" ] = 154;
	level.dofDefault[ "farEnd" ] = 2100;
	level.dofDefault[ "nearBlur" ] = 5;
	level.dofDefault[ "farBlur" ] = 5;

	level.player maps\_art::setDefaultDepthOfField();
*/
}

above_water_art_and_ambient_setup()
{
	SetCullDist(level.cull_dist);
	level.player notify("stop_dpfog");

  thread blur_off_pc();
  thread ssao_on_pc();

	thread vision_set_fog_changes( "ny_harbor_surfacing", .1 );
	delaythread( 1.0, ::water_depth_of_field, false );
}

underwater_fog_approaching_rig( transitionTime )
{
	setExpFog( 0, 482, 0.0461649, 0.25026, 0.221809, 1, transitionTime, 0.0501764, 0.0501764, 0.0501764, (-0.0563281, 0.0228246, -1), 58.2299, 87.711, 1.48781 );
}

///////////////////////////////////////////////////////////////////////////////////////
setup_viewdependent_fog_vision()
{
	level.dp_pitches = [-90,-30, 0, 30];
	level.dp_depths = [-1200, -600, -200, 0];
	// level.dp_fogs[pitchidx][depthidx]
	//                             -1200                           -600                        -200                    0
	level.dp_fogs[0 /* -90 */] = [ "ny_harbor_underwater_bottom", "ny_harbor_underwater_mid", "ny_harbor_underwater_mid", "ny_harbor_underwater_mid"];
	level.dp_fogs[1 /* -30 */] = [ "ny_harbor_underwater_bottom", "ny_harbor_underwater_mid", "ny_harbor_underwater_mid", "ny_harbor_underwater_mid"];
	level.dp_fogs[2 /*   0 */] = [ "ny_harbor_underwater_bottom", "ny_harbor_underwater_mid", "ny_harbor_underwater_mid", "ny_harbor_underwater_mid"];
	level.dp_fogs[3 /*  30 */] = [ "ny_harbor_underwater_bottom", "ny_harbor_underwater_mid", "ny_harbor_underwater_mid", "ny_harbor_underwater_mid"];
	
	level.dp_vision[0 /* -90 */] = "ny_harbor_underwater_top";
	level.dp_vision[1 /* -30 */] = "ny_harbor_underwater_top";
	level.dp_vision[2 /*   0 */] = "ny_harbor_underwater";
	level.dp_vision[3 /*  30 */] = "ny_harbor_underwater_bottom";
}

blend_fog( f0, f1, v, f )
{
	omv = 1.0 - v;
	f.startDist = v*f0.startDist + omv*f1.startDist;
	f.halfwayDist = v*f0.halfwayDist + omv*f1.halfwayDist;
	f.maxOpacity = v*f0.maxOpacity + omv*f1.maxOpacity;
	f.red = v*f0.red + omv*f1.red;
	f.green = v*f0.green + omv*f1.green;
	f.blue = v*f0.blue + omv*f1.blue;
	f.sunRed = v*f0.sunRed + omv*f1.sunRed;
	f.sunGreen = v*f0.sunGreen + omv*f1.sunGreen;
	f.sunBlue = v*f0.sunBlue + omv*f1.sunBlue;
	f.sunBeginFadeAngle = v*f0.sunBeginFadeAngle + omv*f1.sunBeginFadeAngle;
	f.sunEndFadeAngle = v*f0.sunEndFadeAngle + omv*f1.sunEndFadeAngle;
	f.normalFogScale = v*f0.normalFogScale + omv*f1.normalFogScale;
	f.sunDir = VectorLerp( f0.sunDir, f1.sunDir, v );
	f.sunFogEnabled = f0.sunFogEnabled || f1.sunFogEnabled;
}

debug_fdfv()
{
	/#
	CreateDebugTextHud( "depth", 20, 100, ( 1, 1, 1), "depth:" );
	CreateDebugTextHud( "pitch", 20, 130, ( 1, 1, 1), "pitch:" );
	#/
}

viewdependent_fog_vision_update( blend_in_time )
{
	self endon("stop_dpfog");
	self endon("death");
	if (!isdefined(self.viewdependent_vision_enabled))
		self.viewdependent_vision_enabled = true;
	if (!isdefined(self.viewdependent_fog_enabled))
		self.viewdependent_fog_enabled = true;
	fogent = SpawnStruct();
	fogent.name = "depth_pitch_fog";
	lfog[0] = SpawnStruct();
	lfog[1] = SpawnStruct();
	if (!isdefined( blend_in_time ) )
		blend_in_time = 0;
	//thread debug_fdfv();
	
	while (true)
	{
		/#
		if (GetDvarInt( "scr_art_tweak" ) != 0)
		{	// don't drive things while in art tweak mode
			wait 0.05;
			continue;
		}
		#/
		depthblend = 0;
		pitchblend = 0;
		// get the current pitch/depth
		angles = self GetPlayerAngles();
		pitch = angles[0];
		depth = self.origin[2] - level.water_z;
		/#
		//PrintDebugTextHud( "depth", depth);
		//PrintDebugTextHud( "pitch", pitch);
		#/
		// find the indices
		pitchidx = [0, 0];
		pitchblend = 0;
		foreach (idx, p in level.dp_pitches)
		{
			pitchidx[1] = idx;
			if (pitch < p)
			{
				p0 = level.dp_pitches[ pitchidx[0] ];
				rng = p - p0;
				if (rng > 0)
					pitchblend = (pitch - p0)/rng;
				break;
			}
			pitchidx[0] = idx;
		}
		depthidx = [0, 0];
		depthblend = 0;
		foreach (idx, d in level.dp_depths)
		{
			depthidx[1] = idx;
			if (depth < d)
			{
				d0 = level.dp_depths[ depthidx[0] ];
				rng = d - d0;
				if (rng > 0)
					depthblend = (depth - d0)/rng;
				break;
			}
			depthidx[0] = idx;
		}
		
		if (self.viewdependent_fog_enabled)
		{
			for (i=0; i<2; i++)
			{	// get the depth variations
				fog0 = get_vision_set_fog( level.dp_fogs[ pitchidx[i] ][ depthidx[0] ] );
				fog1 = get_vision_set_fog( level.dp_fogs[ pitchidx[i] ][ depthidx[1] ] );
				blend_fog( fog0, fog1, depthblend, lfog[i] );
			}
			// now blend based on the pitch
			blend_fog( lfog[0], lfog[1], pitchblend, fogent );
			self set_fog_to_ent_values( fogent, blend_in_time  );
		}
		
		// now determine the vision set blend
		if (self.viewdependent_vision_enabled)
		{
			if ( blend_in_time > 0.05 )
			{
				pi = pitchidx[0];
				if (pitchblend > 0.5)
					pi = pitchidx[1];
				vision = level.dp_vision[ pi ];
				vision_set_changes( vision, blend_in_time );
				blend_in_time -= 0.05;
				if (blend_in_time < 0.05)
					blend_in_time = 0.05;
			}
			else
			{
			if ( pitchidx[0] == pitchidx[1] )
				self VisionSetNakedForPlayer( level.dp_vision[ pitchidx[0] ] );
			else
				self VisionSetNakedForPlayer_Lerp( level.dp_vision[ pitchidx[0] ], level.dp_vision[ pitchidx[1] ], pitchblend );
			}
		}
		
		wait 0.05;
	}
}



init_sdv_path()
{
	//wait 1;
	aChain = [];
	ePathpoint = level.lead_sdv;
	i = 0;
	while ( isdefined( ePathpoint.target ) )
	{
		if ( isdefined( ePathpoint.target ) )
		{
			ePathpoint = getvehiclenode( ePathpoint.target, "targetname" );
			
			if (isdefined(ePathpoint))			
				aChain[ aChain.size ] = ePathpoint;
		}
		else
			break;
	}
	level.sdv_path = aChain;
}

underwater_hud_enable( bool )
{
	wait 0.05;
	if ( bool == true )
	{
		//setsaveddvar( "ui_hidemap", 1 );
		SetSavedDvar( "hud_showStance", "0" );
		//SetSavedDvar( "compass", "0" );					// Hide the compass
		SetSavedDvar( "compassHideSansObjectivePointer", "1" );		// Keep the follow icon
		//SetDvar( "old_compass", "0" );
		SetSavedDvar( "ammoCounterHide", "1" );
		setsaveddvar( "g_friendlyNameDist", 0 );
		//SetSavedDvar( "hud_showTextNoAmmo", "0" ); 
	}
	else
	{
		//setsaveddvar( "ui_hidemap", 0 );
		setSavedDvar( "hud_drawhud", "1" );
		SetSavedDvar( "hud_showStance", "1" );
		//SetSavedDvar( "compass", "1" );					// Show the compass
		SetSavedDvar( "compassHideSansObjectivePointer", "0" );		// Show the compass
		//SetDvar( "old_compass", "1" );
		SetSavedDvar( "ammoCounterHide", "0" );
		setsaveddvar( "g_friendlyNameDist", 15000 );
		//SetSavedDvar( "hud_showTextNoAmmo", "1" ); 
	}
}

player_surface_blur()
{
	//level.player thread play_sound_in_space( "splash_player_water_exit" );
	thread water_streaks();
//	SetBlur( 3, .1 ); SetBlur can't be used in conjuction with setwatersheeting.
//	wait 0.25;
//	SetBlur( 0, .5 );
}

water_streaks()
{
	level.player SetWaterSheeting( 1, 3.0 );
}


//-------------------------------------------------------------------------------------------------------------
//  Floating Body Handling
//-------------------------------------------------------------------------------------------------------------
init_floating_bodies()
{
	run_thread_on_noteworthy( "ai_floating_body", ::floating_body_think_init );
}

hide_floating_bodies()
{
}

floating_body_think_init()
{
	self assign_animtree("floating_body");
	// create a tag that we can link the body too and have float around
	tag_origin = spawn_tag_origin();
	tag_origin.origin = self.origin;
	tag_origin.angles = self.angles;
	self.tag_origin = tag_origin;
	self linkto(tag_origin,"tag_origin");
	
	self thread floating_body_think();
}

floating_body_think()
{
	sAnim = self.animation;
	eGoal = undefined;
	sAnimLoop = undefined;
	looping = false;
	/*-----------------------
	DOES AI HAVE A GOAL ENTITY?
	-------------------------*/	
	if ( isdefined( self.target ) )
		eGoal = getent( self.target, "targetname" );
	
	/*-----------------------
	GO AHEAD AND PLAY LOOPING IDLE (IF ANIM IS LOOPING)
	-------------------------*/	
	if (isdefined(sAnim))
	{
		if ( isarray( level.scr_anim[ "generic" ][ sAnim ] ) )
		{
			looping = true;
			self thread anim_generic_loop( self, sAnim, "stop_idle" );
		}
		else
		{
			//FREEZE FRAME AT START OF ANIM (IF IT'S NOT A LOOP)
			//if the given anim is not a loop, it will transition to a loop
			self anim_generic_first_frame( self, sAnim );
			sAnimLoop = sAnim + "_idle";
			if ( !anim_exists( sAnimLoop ) )
				sAnimLoop = undefined;
		}
	}
	
	/*-----------------------
	WAIT FOR A FLAG (IF DEFINED IN THE SPAWNER) THEN PLAY ANIM
	-------------------------*/	
	if ( isdefined( self.script_flag ) )
	{
		flag_wait( self.script_flag );
	}
	
	// The sim here is very simple, loop among any path nodes moving at a default velocity, which can be overridden
	// deal with the path
	if ( isdefined( eGoal ) )
	{
		self thread floating_body_moving(eGoal);
	}
	if (isdefined(sAnim))
	{
		// deal with the non-loop
		if ( !looping ) 
		{
			self anim_generic( self, sAnim );	// this will block until the anim is finished
			if ( isdefined( sAnimLoop ) )
			{
				self thread anim_generic_loop( self, sAnimLoop, "stop_idle" );
			}
		}
	}	
}


// self is the entity for the body
// eGoal is the first goal, which will be looped back to
floating_body_moving(eStartGoal)
{
	assert( isdefined(self.tag_origin) );
	// since we've already placed the actor at the first goal, us the next	
	eGoal = undefined;
		
	// start moving towards each goal
	for ( ;; )
	{
		if (!isDefined(eGoal))
			eGoal = eStartGoal;
		
		// See if there is a time on the node, if not, use the default velocity to calculate the time
		if (isDefined(eGoal.speed))
			speed = eGoal.speed;
		else
		{
			speed = 1.0;	// inches/sec
		}
		assert(speed > 0);
		dist = distance( eGoal.origin, self.tag_origin.origin );
		time = dist/speed;
		// Move the tag to the new goal in the time specified
		self.tag_origin moveto( eGoal.origin, time, .05, .05 );
		self.tag_origin rotateto( eGoal.angles, time, .05, .05 );
		
		wait time;	// wait till we're done with the move
			
		if (isDefined(eGoal.target))
			eGoal = getent( eGoal.target, "targetname" );
		else
			eGoal = undefined;
	}
}

anim_exists( sAnim, animname )
{
	if ( !isdefined( animname ) )
		animname = "generic";
	if ( isDefined( level.scr_anim[ animname ][ sAnim ] ) )
		return true;
	else
		return false;
}

move_ent_along_entpath(ent, defaultSpeed, firsttarget )
{
	if (ent islinked())
	{
		// do we need to set the origin/angles or will it already not pop??
		ent unlink();
	}
	tag_origin = ent spawn_tag_origin();
	if (isplayer(ent))
		ent playerlinkto(tag_origin,"tag_origin",0.5);
	else
		ent linkto(tag_origin,"tag_origin");
	if (!isdefined(defaultSpeed))
		defaultSpeed = 128;
	if (!isdefined(firsttarget))
		firsttarget = ent.target;
	
	// get the first ent in the path
	assert(isdefined(firsttarget));
	for (eGoal = getent( firsttarget, "targetname") ; isdefined(eGoal) ; eGoal = getent(eGoal.target, "targetname"))
	{
		if (isdefined(eGoal.speed))
			speed = eGoal.speed;
		else
			speed = defaultSpeed;
		dist = distance(tag_origin.origin, eGoal.origin);
		time = dist / speed;
		tag_origin moveto(eGoal.origin, time);
		tag_origin rotateto(eGoal.angles, time);
		wait time;
		if (isdefined(eGoal.script_flag_set))
			flag_set(eGoal.script_flag_set);
		if (!isdefined(eGoal.target))
			break;
	}
	if (isdefined(eGoal) && isdefined(eGoal.script_noteworthy))
	{
		if (eGoal.script_noteworthy == "gravity")
		{	// hold the current XY, and let gravity affect the Z (use a different gravity for beneath the water
			water_z = -1200;	// -100ft
			if (isdefined(level.water_z))
				water_z = level.water_z;
			if (tag_origin.origin[2] > water_z)
			{	// move with gravity to the water
				dist = tag_origin.origin[2] - water_z;
				time = dist/128;	// 128 inches/sec
				target = (tag_origin.origin[0], tag_origin.origin[0], water_z);
				acceltime = 3;
				if (acceltime > (time - 0.05))
					acceltime = time - 0.05;
				tag_origin moveto(target, time, acceltime);
				if (isdefined(eGoal.script_parameters))
				{	// use the script_parameters to determine a rotational velocity
					rot = eGoal.script_parameters;
					tag_origin rotatevelocity(rot, time, acceltime);
				}
				wait time;
			}
			// at this point, we should be at or below the water
			dist = water_z - tag_origin.origin[2] + 1200;	// go down a 100 ft
			time = dist/32;	// 32 inches/sec
			target = (tag_origin.origin[0], tag_origin.origin[0], water_z);
			acceltime = 1;
			if (acceltime > (time - 0.05))
				acceltime = time - 0.05;
			tag_origin moveto(target, time, acceltime);
			if (isdefined(eGoal.script_parameters))
			{	// use the script_parameters to determine a rotational velocity
				rot = eGoal.script_parameters;
				rot = 0.05 * rot;	// use a slower rotation
				tag_origin rotatevelocity(rot, time, acceltime);
			}
			wait time;
		}
	}
	ent unlink();
	tag_origin delete();
}

hide_surface_ships( bHide, exclude_ships )
{
	ships = getentarray("above_water_only", "script_noteworthy" );
	ships = array_combine_unique( ships, getentarray("bobbing_ship", "script_noteworthy" ));
	ships = array_combine_unique( ships, getentarray( "bobbing_ship_big", "script_noteworthy" ) );
	if (isdefined(exclude_ships))
		ships = array_remove_array( ships, exclude_ships);
	foreach (ship in ships)
	{
		if (bHide)
			ship Hide();
		else
			ship Show();
	}
}

catch_notetrack_take_mask_off()
{
	wait ((661-601)/30.0 - 0.25);
//	self waittillmatch( "single anim", "maskoff" );
	level.player thread scubamask_off_player();
	delaythread( 0.65, ::rockoutside);
}

catch_notetrack_mine_explosion()
{
	self waittillmatch( "single anim", "explosion" );
	//wait (-230+580)/30.0;
	flag_set( "detonate_sub" );
}