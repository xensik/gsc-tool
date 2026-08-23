#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;
#include maps\_audio;
#include maps\ny_harbor_code_vo;
#include maps\_gameevents;
#include maps\_hud_util;
#include maps\_shg_common;


sub_setup()
{
	//flag_init( "hatch_enemies_dead" );
	flag_init( "barracks_sandman_opening_door" );
	if( !flag_exist( "barracks_guys_dead" ) )
	{
		flag_init( "barracks_guys_dead" );
	}

	level.sub_doors = [];
	array_spawn_function_noteworthy( "sub_enemy", ::sub_setup_enemy );
	
	thread setup_music();
	thread setup_sandman();
	thread sub_exterior_ambient();
	thread sub_entrance();
	thread sub_barracks();
	thread sub_reactor_room();
	thread sub_missile_room();
	thread sub_missile_tubes_show();
	thread sub_exit();
	thread remove_sub_pilots();
	thread setup_the_dead();
	thread sub_set_player_speed();
	thread VO_audio();
	thread open_hatch_rear();
	thread watch_water_on();
	thread watch_water_off();
	thread cleanup_after_sub();
	thread manage_external_water_in_sub();
	thread disable_prone_on_back_of_sub();
	
	
	silo_interior_visibility( false );	// hide the interior silos at start

	player_speed_percent( 75 );
	level.player AllowSprint( true );

	autosave_by_name( "sub_exterior" );
}

disable_prone_on_back_of_sub()
{
	level endon( "ladder_done" );
	
	while( 1 )
	{
		if( flag( "sub_disable_prone" ) )
		{
			level.player AllowProne( false );
			level.player AllowCrouch( false );
		}
		else
		{
			level.player AllowProne( true );
			level.player AllowCrouch( true );
		}
		wait( 0.05 );
	}
}

cleanup_after_sub()
{
	flag_wait("player_on_boat");
	foreach (door in level.sub_doors)
		door Delete();
}

stop_script_anim(node, flg)
{

	while ( isdefined(self) && self.health >= 30)
	{
		wait 0.05;
		if (isdefined(flg) && flag(flg))
		{
			self anim_stopanimscripted();
			flag_clear(flg);
		}
	}
	
	if( isdefined( self ) )
		self anim_stopanimscripted();
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//                              BRIDGE
//-------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------------------------
//                              END BRIDGE
//-------------------------------------------------------------------------------------------------------------------------------------------

generic_surprise_death(anime_node_targetname, spawner_targetname)
{
}

			
			

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------------------

remove_sub_pilots()
{
	flag_wait("player_surfaces");
	if (isdefined(level.sub_pilots) && level.sub_pilots.size > 0)
	{
		foreach (guy in level.sub_pilots)
		{
				guy delete();
		}
	}
	
	if( isdefined( level.sdv_grinch ) )
		level.sdv_grinch delete();
	if( isdefined( level.sdv_sandman ) )
		level.sdv_sandman delete();
	
}

debug_playerview()
{
	/#
	while (true)
	{
		angles = level.player GetPlayerAngles();
		origin = level.player GetEye();
		forward = anglestoforward(angles);
		
		draw_axis( origin + 24*forward, angles );
		wait 0.05;
	}
	#/
}

npc_through_water( scriptnode )
{
	scriptnode.origin = scriptnode.origin + (0,0,96);
	self thread bobbing_actor( scriptnode, 0.0 );
	level.russian_cine_sub SetModel("vehicle_russian_oscar2_sub_breached");
}

catch_notetrack_subswap( scriptnode, refnode )
{
	self waittillmatch( "single anim", "subswap" );
	scriptnode.origin = refnode.origin;
	scriptnode.angles = refnode.angles;
	level.breach_sub_scriptnode Delete();
	level.breach_sub_scriptnode = undefined;
	level.russian_cine_sub Hide();
	//burya1 = getent("burya1", "targetname" );
	burya2 = getent("burya2", "targetname" );
	//burya1 Show();
	burya2 Show();
}

catch_notetrack_stopbob()
{
	wait 0.05;
	level notify("stop_bob");
}

rockoutside()
{
	thread RockingSub();
	thread OnOutsideOfSub();
}

anim_single_solo_trans( ent, anime, tag, trans )
{
	self thread anim_single_solo( ent, anime, tag );
	anm = ent getanim( anime );
	animtime = GetAnimLength(anm);
	ent SetFlaggedAnim( "single_anim", anm, 1.0, trans, 1.0 );
	ent waittill_match_or_timeout( "single anim", "end", animtime );
}

sub_breach_move_allies( start_ent, end_ent )
{
	wait 0.05;
	start_angles = start_ent GetTagAngles("body");
	end_angles =  end_ent GetTagAngles("body");
	delta_origin = (end_ent GetTagOrigin("body")) - (start_ent GetTagOrigin("body"));
	delta_angles = end_angles - start_angles;
	foreach (sdv in level.sdvarray)
	{
		if (sdv == level.player_sdv)
			continue;
		origin = sdv.origin + delta_origin;
		angles = sdv.angles + delta_angles;
		forward = AnglesToForward(angles);
		// get sdv off path and move relative
		sdv dontinterpolate();
		sdv vehicle_teleport( origin, angles );
		sdv vehicleDriveTo( origin + (100*12*forward), 1.0 );
		sdv Vehicle_SetSpeed( level.russian_sub_02 Vehicle_GetSpeed(), 10, 10 );
	}
}

sub_breach_open_view()
{
	//level.player PlayerLinkToDelta( level.sdv_player_arms, "tag_player", 1.0, 15, 15, 15, 15, true );
	level.player lerpviewangleclamp( 1.0, 0.3, 0.3, 15, 0, 15, 0 );
	level.player enableslowaim();
}

bobbing_jitter_cleanup( bob )
{
	level waittill( "cleanup_bob" );
	bob.bob_ref delete();
	bob delete();
}

delete_on_msg( ent, msg )
{
	level waittill( msg );
	if (isdefined(ent))
		ent delete();
}

bobbing_jitter( bob, bobscale )
{
	bob_ref = bob.bob_ref;
	if (!isdefined(bob_ref))
		bob_ref = spawn_tag_origin();
	bob_ref.origin = bob.origin;
	bob_ref.angles = bob.angles;
	bob.bob_ref = bob_ref;
	bob.start_origin = bob.origin;
	
	level endon("stop_bob");
	bob endon("death");
	thread bobbing_jitter_cleanup( bob );
	maxrange = 12.0;
	minZrange = 0;
	maxZrange = 12.0;
	minTime = 0.5;
	maxTime = 1.5;
	while (true)
	{
		angle = RandomFloatRange(0.0, 1.0);
		angle *= 360;
		radius = bobscale*RandomFloatRange(0.0, maxrange);
		x = radius*cos(angle);
		y = radius*cos(angle);
		z = bobscale*RandomFloatRange( minZrange, maxZrange );
		time = RandomFloatRange( minTime, maxTime );
		bob.bob_ref moveto( bob.start_origin + (x, y, z), time, time/4.0, time/4.0 );
		wait time;
	}
}

bobbing_updown( bob )
{
	bob_ref = bob.bob_ref;
	if (!isdefined(bob_ref))
		bob_ref = spawn_tag_origin();
	bob_ref.origin = bob.origin;
	bob_ref.angles = bob.angles;
	bob.bob_ref = bob_ref;
	bob.start_origin = bob.origin;
	
	level endon("stop_bob");
	thread bobbing_jitter_cleanup( bob );
return;	// cinematic is taking care of this
/*
	minZrange = -4.0;
	maxZrange = 4.0;
	minTime = 0.5;
	maxTime = 2.5;
	while (true)
	{
		x = 0;
		y = 0;
		z = RandomFloatRange( minZrange, maxZrange );
		time = RandomFloatRange( minTime, maxTime );
		bob.bob_ref moveto( bob.start_origin + (x, y, z), time, time/4.0, time/4.0 );
		wait time;
	}
*/
}

bobbing_ripple( bobbing_obj )
{
	level endon("stop_bob");
	bobbing_obj endon("death");
	zoff = -430;
	ripple_obj = spawn_tag_origin();
	ripple_obj.origin = self.origin;
	ripple_obj.angles = ( -90, 0, 0 );
	thread delete_on_msg( ripple_obj, "stop_bob" );
	curtime = 0;
	time = 0;
	while (true)
	{
		// the ripple will be centered on the actor's x,y and not be displaced with z jitter, so use ref_origin[2] for it
		ripple_obj.origin = (self.origin[0], self.origin[1], bobbing_obj.ref_origin[2] + zoff);
	/#
//	draw_point( ripple_obj.origin, 24, (1,1,1) );
	#/
		if (curtime >= time)
		{
			playfxontag( getfx("ocean_ripple"), ripple_obj, "tag_origin" );
			time = RandomFloatRange( 0.25,0.5 );
			curtime = 0;
		}
		else
			curtime += 0.05;
		wait 0.05;
	}
}

bobbing_actor( bobbing_obj, bobscale )
{
	// self is the actor that is being bobbed
	// bobbing_obj is the reference node for the animation, so it's Z is relative to it's original Z
	// bobbing_obj will be tracking the surface z where self is in x,y (though it isn't necessarily at x,y)
	// bobbing_obj.bob_ref is jittered (up/down or all around) using movetos and is used to offset bobbing_obj
	// bobbing_obj.ref_origin is the origin displaced in z without any jittered
	// bobbing_obj.start_origin is the initial origin
	level endon("stop_bob");
	bobbing_obj endon("death");
	bobbing_obj.start_origin = bobbing_obj.origin;
	bobbing_obj.ref_origin = bobbing_obj.origin;
	if (bobscale > 0)
		thread bobbing_jitter( bobbing_obj, bobscale );
	else
	{
		thread bobbing_updown( bobbing_obj );
		thread bobbing_ripple( bobbing_obj );
	}
	while (true)
	{
		origin = self.origin;	// use the actor's x,y to determine displacement
		displacement = maps\_ocean::GetDisplacementForVertex( level.oceantextures["water_patch"], origin );
		// get the non-jittered origin
		bobbing_obj.ref_origin = bobbing_obj.start_origin + ( 0, 0, displacement );
		// add the jitter to the ref_origin
		bobbing_obj.origin = bobbing_obj.ref_origin + (bobbing_obj.bob_ref.origin - bobbing_obj.start_origin );
		wait 0.05;
	}
}

bobbing_ally( ally, targetname )
{
	tgt = getent(targetname,"targetname");
	bobbing_obj = spawn_tag_origin();
	tgt.origin = tgt.origin - (0,0,48);
	bobbing_obj.origin = tgt.origin;
	bobbing_obj.angles = tgt.angles;
	ally show();
	ally ForceTeleport( bobbing_obj.origin, bobbing_obj.angles );
	ally linkto( bobbing_obj, "tag_origin" );
	ally thread bobbing_actor( tgt, bobbing_obj, -6, 0.0 );
}

player_surfaces()
{
	flag_wait("player_surfaces");
	
	thread watch_explosions();
	flag_wait( "done_watching_explosion" );
	wait( 1 );
	flag_wait("sub_breach_finished");
	level.player unlink();
	level notify( "stop_bob" );
	level.russian_sub_02 Hide();
	level.player EnableWeapons();
	level.player FreezeControls( false );
	level.player.ignoreme = false;
	flag_set("get_onto_sub");
}

watch_explosions()
{
	flag_wait( "submine_detonated" );
	wait( 1 );
	flag_set( "done_watching_explosion" );
}

  fade_in( fade_time )
  {
  	if ( level.MissionFailed )
  		return;
  	level notify( "now_fade_in" );
  		
  	black_overlay = get_black_overlay();
  	if ( fade_time )
  		black_overlay FadeOverTime( fade_time );
  
  	black_overlay.alpha = 0;
  
  	wait( fade_time );
  }

fade_out( fade_out_time )
{
  	black_overlay = get_black_overlay();
  	if ( fade_out_time )
  		black_overlay FadeOverTime( fade_out_time );
  
  	black_overlay.alpha = 1;
  
  	wait( fade_out_time );
}

get_black_overlay()
 {
  	if ( !IsDefined( level.black_overlay ) )
  		level.black_overlay = create_client_overlay( "black", 0, level.player );
  	level.black_overlay.sort = -1;
  	level.black_overlay.foreground = false;
  	return level.black_overlay;
 }

HideShowEnts(ents, hide_them)
{
	if (!isdefined(ents))
		return;
	foreach (ent in ents)
	{
		if (hide_them)
		{
			ent Hide();
			ent.hidden = true;
		}
		else
		{
			ent Show();
			ent.hidden = false;
		}
	}
}

ship2_squeeze_bob()
{
	ship = GetEnt("ship2_squeeze", "targetname" );
	refship = GetEnt("ship_squeeze_ship", "targetname" );
	prep_bobbing( [ship], refship.bobbing_fnc, refship.bobbing_settings, refship.bobbing_underwater );
	ship thread start_bobbing_single(0);
	flag_wait( "ladder_done" );	// turn it off after the ladder slide
	ship no_bobbing();
}

// Here are the modes
// 0 is the starting mode, which happens during the breach cinematic
// 1 is after the cinematic, boarding the Sub
// 2 is the start of the zodiac ride (which starts with all static except around the sub)
// 3 is the chinook fly out.
ShowWater( mode )
{
	dyn_water = getentarray( "dyn_water", "script_noteworthy");
	static_water = getentarray( "stat_water", "script_noteworthy");
	dyn_water_sub = getentarray( "dyn_water_sub", "script_noteworthy");
	static_water_sub = getentarray( "stat_water_sub", "script_noteworthy");
	dyn_water_breachpatch_high = getentarray( "dyn_water_breachpatch_high", "script_noteworthy");
	dyn_water_breachpatch_low = getentarray( "dyn_water_breachpatch_low", "script_noteworthy");
	fly_out_water = getentarray( "water_flyout", "script_noteworthy" );
	fly_out_water_off = getentarray( "water_flyout_off", "script_noteworthy" );
	switch(mode)
	{
		case 0:	// 0 is the starting mode, which happens during the breach cinematic
			HideShowEnts(dyn_water_sub, false);
			HideShowEnts(static_water_sub, true);
			HideShowEnts(dyn_water_breachpatch_high, true);
			HideShowEnts(dyn_water_breachpatch_low, false);	// for now, don't use the highest for now
			HideShowEnts(dyn_water, true);
			HideShowEnts(static_water, false);	// all static water
			HideShowEnts(fly_out_water, true);	// hide flyout water
			HideShowEnts(fly_out_water_off, false);	// show flyout water off
			break;
		case 1:	// 1 is after the cinematic, boarding the Sub
			HideShowEnts(dyn_water_sub, false);
			HideShowEnts(static_water_sub, true);
			HideShowEnts(dyn_water_breachpatch_high, true);
			HideShowEnts(dyn_water_breachpatch_low, false);	// after teleport, we'll use the low
			HideShowEnts(dyn_water, true);
			HideShowEnts(static_water, false);	// all static water
			HideShowEnts(fly_out_water, true);	// hide flyout water
			HideShowEnts(fly_out_water_off, false);	// show flyout water off
			break;
		case 2:	// 2 is the start of the zodiac ride (which starts with all static except around the sub)
			HideShowEnts(dyn_water_sub, false);
			HideShowEnts(static_water_sub, true);
			HideShowEnts(dyn_water_breachpatch_high, true);
			HideShowEnts(dyn_water_breachpatch_low, false);	// after teleport, we'll use the low
			HideShowEnts(dyn_water, true);
			HideShowEnts(static_water, false);	// all static water
			HideShowEnts(fly_out_water, true);	// hide flyout water
			HideShowEnts(fly_out_water_off, false);	// show flyout water off
			break;
		case 3:	// 3 is the chinook fly out.
			HideShowEnts(dyn_water_sub, true);
			HideShowEnts(static_water_sub, true);
			HideShowEnts(dyn_water_breachpatch_high, true);
			HideShowEnts(dyn_water_breachpatch_low, true);
			HideShowEnts(dyn_water, true);
			HideShowEnts(static_water, true);	// all static water
			HideShowEnts(fly_out_water, false);	// show flyout water
			HideShowEnts(fly_out_water_off, true);	// hide flyout water off
			break;
	}
}

BobObjectTo( isBuoy )
{
	self endon("stop_bobbing");
	while (true)
	{
		if (flag("outside_above_water") || self.bobbing_underwater)
		{
			origin = (self.tgt_values[3],self.tgt_values[4],self.tgt_values[5]);
			angles = (self.tgt_values[0],self.tgt_values[1],self.tgt_values[2]);
			self moveto(origin, 0.1, 0.0, 0.0 );
			if (!isBuoy)
				self rotateto(angles, 0.1, 0.0, 0.0 );
			wait 0.05;
		}
		else
			wait 0.2;
	}
}


BobObjectParam( which, org_value, min_value, max_value, min_period, max_period, oldstyle )
{
	self endon("stop_bobbing");
	state = randomint(2);
	self.tgt_values[which] = org_value;
	while (true)
	{
		if (flag("outside_above_water") || self.bobbing_underwater)
		{
			new_value = org_value;
			newperiod = min_period;
			switch(state)
			{
				case 0:
					new_value = org_value + randomfloat(max_value);
					break;
				case 1:
					if (min_value < 0)
						new_value = org_value - randomfloat(-1*min_value);
					else
						new_value = org_value + randomfloat(min_value);
					break;
			}	
			newperiod = randomfloatrange(min_period, max_period);
			accel_t = newperiod/3.0;
			decel_t = newperiod/3.0;
			if (oldstyle)
			{
				delta = 0;
				if (which < 3)
				{	// ensure that we never do a full rotation due to self.angles wrapping at 180/-180
					delta = new_value -  self.angles[which];
					delta = AngleClamp180(delta);
				}
				switch(which)
				{
					case 0:
						self RotatePitch( delta, newperiod, accel_t, decel_t );
						break;
					case 1:
						self RotateYaw( delta, newperiod, accel_t, decel_t );
						break;
					case 2:
						self RotateRoll( delta, newperiod, accel_t, decel_t );
						break;
					case 3:
						self MoveX( new_value-self.origin[0], newperiod, accel_t, decel_t );
						break;
					case 4:
						self MoveY( new_value-self.origin[1], newperiod, accel_t, decel_t );
						break;
					case 5:
						self MoveZ( new_value-self.origin[2], newperiod, accel_t, decel_t );
						break;
				}
				wait newperiod;
			}
			else
			{
				while (0 < newperiod)
				{
					curval = self.tgt_values[which];
					delta = new_value - curval;
					self.tgt_values[which] += (0.05/newperiod)*delta;
					wait 0.05;
					newperiod -= 0.05;
				}
			}
			state = 1-state;
		}
		else
			wait 0.2;
	}
}

BobbingBuoyAngles()
{
	self endon("stop_bobbing");
	// taken from Veh_BoatGetRockingAngles in vehicle.cpp
	SECONDARY_SCALE = 0.3;
	ROLL_SCALE = 1.5;

	rockingRotationPeriod = 60.0;
	rockingPeriod = 3.0;
	rockingAmplitude = 4.0;
	secRockingAmplitude = SECONDARY_SCALE*rockingAmplitude;
	
	rockingDirYaw = 0;
	self.org_angles = self.angles;
	if ((self.org_angles[0] == 0) && (self.org_angles[2] == 0))
		not_oriented = true;
	else
		not_oriented = false;
	zero = (0,0,0);	// we just want angles from transformMove
	deltaDirYaw = ((0.05*360)/rockingRotationPeriod);
	angleTimeFactor = (0.001 * 360.0)/rockingPeriod;
	while (true)
	{
		if (flag("outside_above_water") || self.bobbing_underwater )
		{
/*
			rockingDirYaw = rockingDirYaw + deltaDirYaw;
			if (rockingDirYaw > 180)
				rockingDirYaw -= 360;
			yawSin = -1*sin(rockingDirYaw);
			yawCos = cos(rockingDirYaw);
			angle = gettime()*angleTimeFactor;
			oscSin = sin(angle);
			oscCos = cos(angle);
			
			displacement = rockingAmplitude * oscCos;
			displacementSecondary = secRockingAmplitude * oscSin;
			
			pitch = yawCos*displacement - yawSin*displacementSecondary;
			roll = yawSin*displacement + yawCos*displacementSecondary;
			roll *= ROLL_SCALE;
			
		//	targetangles = (AngleClamp180(pitch),AngleClamp180(self.angles[1]),AngleClamp180(roll));
			targetangles = (pitch,self.angles[1],roll);
			if (!not_oriented)
			{
				startangles = (0,self.angles[1],0);
				// use transformMove to get the target orientation from our original orientation
				transform = transformMove( zero, targetangles, zero, startangles, zero, self.org_angles );
				targetangles = transform["angles"];
		//		targetangles = (AngleClamp180(targetangles[0]),AngleClamp180(targetangles[1]),AngleClamp180(targetangles[2]));
			}
*/
/**/
			result = CalcRockingAngles( self.org_angles, rockingDirYaw, 4.0, 3.0, 60.0 );
			targetangles = result["angles"];
			rockingDirYaw = result["result"];
/**/
			self rotateto(targetangles, 0.4, 0, 0);
		}
		wait 0.2;
	}
}

BobbingObject( settings )
{
	start_origin = self.origin;
	start_angles = self.angles;
	max_pitch = 5;
	min_pitch_period = 3;
	max_pitch_period = 6;
	max_yaw = 0;
	min_yaw_period = 3;
	max_yaw_period = 6;
	max_roll = 0;
	min_roll_period = 3;
	max_roll_period = 6;
	max_sink = 36;
	max_float = 24;
	min_bob_period = 3;
	max_bob_period = 6;
	max_dx = 0;
	min_dx_period = 3;
	max_dx_period = 6;
	max_dy = 0;
	min_dy_period = 3;
	max_dy_period = 6;
	oldstyle = true;
	if (isdefined(settings))
	{
		if (isdefined(settings.max_pitch))
			max_pitch = settings.max_pitch;
		if (isdefined(settings.min_pitch_period))
			min_pitch_period = settings.min_pitch_period;
		if (isdefined(settings.max_pitch_period))
			max_pitch_period = settings.max_pitch_period;
		if (isdefined(settings.max_yaw))
			max_yaw = settings.max_yaw;
		if (isdefined(settings.min_yaw_period))
			min_yaw_period = settings.min_yaw_period;
		if (isdefined(settings.max_yaw_period))
			max_yaw_period = settings.max_yaw_period;
		if (isdefined(settings.max_roll))
			max_roll = settings.max_roll;
		if (isdefined(settings.min_roll_period))
			min_roll_period = settings.min_roll_period;
		if (isdefined(settings.max_roll_period))
			max_roll_period = settings.max_roll_period;
		if (isdefined(settings.max_sink))
			max_sink = settings.max_sink;
		if (isdefined(settings.max_float))
			max_float = settings.max_float;
		if (isdefined(settings.min_bob_period))
			min_bob_period = settings.min_bob_period;
		if (isdefined(settings.max_bob_period))
			max_bob_period = settings.max_bob_period;
		if (isdefined(settings.max_dx))
			max_dx = settings.max_dx;
		if (isdefined(settings.min_dx_period))
			min_dx_period = settings.min_dx_period;
		if (isdefined(settings.max_dx_period))
			max_dx_period = settings.max_dx_period;
		if (isdefined(settings.max_dy))
			max_dy = settings.max_dy;
		if (isdefined(settings.min_dy_period))
			min_dy_period = settings.min_dy_period;
		if (isdefined(settings.max_dy_period))
			max_dy_period = settings.max_dy_period;
		if (isdefined(settings.oldstyle))
			oldstyle = settings.oldstyle;
	}
	
	self.tgt_values[0] = start_angles[0];
	self.tgt_values[1] = start_angles[1];
	self.tgt_values[2] = start_angles[2];
	self.tgt_values[3] = start_origin[0];
	self.tgt_values[4] = start_origin[1];
	self.tgt_values[5] = start_origin[2];
	if (!oldstyle)
		self thread BobObjectTo( isdefined(settings.isbuoy) );
	if (isdefined(settings.isbuoy))
	{
		thread BobbingBuoyAngles();
	}
	else
	{
		if (max_pitch > 0)
			thread BobObjectParam( 0, start_angles[0], 0-max_pitch, max_pitch, min_pitch_period, max_pitch_period, oldstyle );
		if (max_yaw > 0)
			thread BobObjectParam( 1, start_angles[1], 0-max_yaw, max_yaw, min_yaw_period, max_yaw_period, oldstyle );
		if (max_roll > 0)
			thread BobObjectParam( 2, start_angles[2], 0-max_roll, max_roll, min_roll_period, max_roll_period, oldstyle );
	}
	if (max_dx > 0)
		thread BobObjectParam( 3, start_origin[0], 0-max_dx, max_dx, min_dx_period, max_dx_period, oldstyle );
	if (max_dy > 0)
		thread BobObjectParam( 4, start_origin[1], 0-max_dy, max_dy, min_dy_period, max_dy_period, oldstyle );
	if (max_float > 0)
		thread BobObjectParam( 5, start_origin[2], 0-max_sink, max_float, min_bob_period, max_bob_period, oldstyle );
}

SmoothValue(ratio)
{
	if (ratio == 1)
		blend = 1;
	else
	{
		r2 = ratio*ratio;
		blend = 3*r2 - 2*r2*ratio;
//		blend = ratio - (sin(360*ratio)/6.28);
	}
	return blend;
}

ExpensiveBobbingObj( settings )
{
	self endon("stop_bobbing");
	
	base_origin = self.origin;
	base_angles = self.angles;
	pitch_target = RandomFloatRange(3, 10);
	prv_pitch_target = 0;
	pitch_time = RandomIntRange( 20, 60);
	time = 0;
	while (true)
	{
		displacement = maps\_ocean::GetDisplacementForVertex( level.oceantextures["water_patch"], base_origin );
		self.origin = (base_origin[0], base_origin[1], base_origin[2] + displacement);
		dpitch = ((pitch_target - prv_pitch_target)*SmoothValue(time/pitch_time)) + prv_pitch_target;
		self.angles = (base_angles[0] + dpitch, base_angles[1], base_angles[2]);
		time++;
		if (time > pitch_time)
		{
			prv_pitch_target = pitch_target;
			if (pitch_target > 0)
				pitch_target = -1*RandomFloatRange(3, 10);
			else
				pitch_target = RandomFloatRange(3, 10);
			pitch_time = RandomIntRange( 20, 60);
			time = 1;
		}
		wait 0.05;
	}
}

CreateDefaultBobSettings()
{
	settings = spawnstruct();
	settings.max_pitch = 5;
	settings.min_pitch_period = 3;
	settings.max_pitch_period = 6;
	settings.max_yaw = 0;
	settings.min_yaw_period = 3;
	settings.max_yaw_period = 6;
	settings.max_roll = 0;
	settings.min_roll_period = 3;
	settings.max_roll_period = 6;
	settings.max_sink = 36;
	settings.max_float = 24;
	settings.min_bob_period = 3;
	settings.max_bob_period = 6;
	return settings;
}

CreateDefaultSmallBobSettings()
{
	settings = spawnstruct();
	settings.max_pitch = 10;
	settings.min_pitch_period = 1;
	settings.max_pitch_period = 3;
	settings.max_yaw = 0;
	settings.min_yaw_period = 3;
	settings.max_yaw_period = 6;
	settings.max_roll = 10;
	settings.min_roll_period = 1;
	settings.max_roll_period = 3;
	settings.max_sink = 12;
	settings.max_float = 12;
	settings.min_bob_period = 1;
	settings.max_bob_period = 3;
	settings.isbuoy = true;
	return settings;
}

no_bobbing()
{
	self.nobob = true;
	self notify("stop_bobbing");
}

cleanup_bobbing()
{
	self.org_angles = self.angles;
	self.org_origin = self.origin;
	self waittill("stop_bobbing");
	waittillframeend;
	// ensure we don't keep moving and are back at our original values
	self rotateto(self.org_angles, 1, 0, 0);
	self moveto(self.org_origin, 1, 0, 0);
}

start_bobbing_single( time )
{
	self notify("stop_bobbing");	// ensure we don't have multiple threads running
	self endon("stop_bobbing");
	self thread cleanup_bobbing();
	wait time;
	if (isdefined(self.nobob) && self.nobob)
		return;
	self [[ self.bobbing_fnc ]]( self.bobbing_settings );
}

start_bobbing( objs )
{
	maxtime = 1.0;
	time = 0.0;
	foreach (obj in objs)
	{
		// spread out starting the objects in time
		obj thread start_bobbing_single( time );
		time += 0.05;
		if (time > maxtime)
			time -= maxtime;
	}
}

stop_bobbing( objs )
{
	foreach (obj in objs)
	{
		obj notify("stop_bobbing");
	}
}

prep_bobbing( objs, fnc, settings, underwater )
{
	foreach (obj in objs)
	{
		obj.bobbing_fnc = fnc;
		obj.bobbing_settings = settings;
		obj.bobbing_underwater = underwater;
	}
}

SetupBobbingShips()
{
	level.bobbing_objects = [];
	bobbing_ships_settings = CreateDefaultBobSettings();
	bobbing_ships = getentarray( "bobbing_ship", "script_noteworthy" );
	prep_bobbing( bobbing_ships, ::BobbingObject, bobbing_ships_settings, false );
	level.bobbing_objects = array_combine_unique( level.bobbing_objects, bobbing_ships );

	bobbing_ship_big_settings = CreateDefaultBobSettings();
	bobbing_ship_big_settings.max_pitch = 1.0;
	big_bobbing_ships = getentarray ( "bobbing_ship_big", "script_noteworthy" );
	prep_bobbing( big_bobbing_ships, ::BobbingObject, bobbing_ship_big_settings, false );
	level.bobbing_objects = array_combine_unique( level.bobbing_objects, big_bobbing_ships );
	
	sinking_ships_settings = CreateDefaultBobSettings();
	sinking_ships_settings.max_pitch = 2;
	sinking_ships = getentarray( "sinking_ship", "script_noteworthy" );
	prep_bobbing( sinking_ships, ::BobbingObject, sinking_ships_settings, false );
	level.bobbing_objects = array_combine_unique( level.bobbing_objects, sinking_ships );

	bobbing_objs_settings = CreateDefaultSmallBobSettings();
	bobbing_objs = getentarray( "bobbing_object", "script_noteworthy" );
	prep_bobbing( bobbing_objs, ::BobbingObject, bobbing_objs_settings, false );
	level.bobbing_objects = array_combine_unique( level.bobbing_objects, bobbing_objs );

	bobbing_buoys_settings = CreateDefaultSmallBobSettings();
	bobbing_buoys = getentarray( "bobbing_buoy", "script_noteworthy" );
	prep_bobbing( bobbing_buoys, ::BobbingObject, bobbing_buoys_settings, false );
	level.bobbing_objects = array_combine_unique( level.bobbing_objects, bobbing_buoys );
	
	expensive_bobbers = getentarray( "bobbing_expensive", "script_noteworthy" );
	prep_bobbing( expensive_bobbers, ::ExpensiveBobbingObj, undefined, false );
	level.bobbing_objects = array_combine_unique( level.bobbing_objects, expensive_bobbers );
	
	bobbing_mines_settings = CreateDefaultBobSettings();
	bobbing_mines_settings.max_pitch = 5;
	bobbing_mines_settings.min_pitch_period = 3;
	bobbing_mines_settings.max_pitch_period = 8;
	bobbing_mines_settings.max_yaw = 10;
	bobbing_mines_settings.min_yaw_period = 3;
	bobbing_mines_settings.max_yaw_period = 8;
	bobbing_mines_settings.max_roll = 5;
	bobbing_mines_settings.min_roll_period = 3;
	bobbing_mines_settings.max_roll_period = 8;
	bobbing_mines_settings.max_sink = 12;
	bobbing_mines_settings.max_float = 12;
	bobbing_mines_settings.min_bob_period = 3;
	bobbing_mines_settings.max_bob_period = 8;
	bobbing_mines_settings.max_dx = 12;
	bobbing_mines_settings.min_dx_period = 3;
	bobbing_mines_settings.max_dx_period = 8;
	bobbing_mines_settings.max_dy = 12;
	bobbing_mines_settings.min_dy_period = 3;
	bobbing_mines_settings.max_dy_period = 8;
	bobbing_mines_settings.oldstyle = false;
	bobbing_mines = getentarray( "underwater_mines", "script_noteworthy" );
	prep_bobbing( bobbing_mines, ::BobbingObject, bobbing_mines_settings, true );
	thread start_bobbing( bobbing_mines );	// let the underwater mines always be going
}

InitBobbingVolumes()
{
	vols = getentarray("bobbing_volume","script_noteworthy");
	foreach (vol in vols)
	{	// find all bobbing objects in this volume and place them in bobbers
		vol.bobbers = [];
		foreach (ent in level.bobbing_objects)
		{
			if (!isdefined(ent.bobbing_volume))
			{
				if (vol istouching( ent ))
				{
					ent.bobbing_volume = vol;
					vol.bobbers[vol.bobbers.size] = ent;
				}
			}
		}
	}
	// just for fun, track how many are outside our volumes
	// these should be converted to misc_models
	level.always_bobbing_objects = [];
	foreach (ent in level.bobbing_objects)
	{
		if (!isdefined(ent.bobbing_volume))
		{	// this ent wasn't added to any volume, so add to always_bobbing_objects
			level.always_bobbing_objects[level.always_bobbing_objects.size] = ent;
			println("unsued bobber: (" + ent.origin[0] + "," + ent.origin[1] + "," + ent.origin[2] + ") + " + ent.model );
		}
	}
//	DebugBobbingObjects();
}

ActivateBobbingObjects()
{	// self is the volume to activate
	if (isdefined(self.bobbers))
	{
		println("starting " + self.bobbers.size + " bobbing objects");
		thread start_bobbing(self.bobbers);
	}
}

DeactivateBobbingObjects()
{	// self is the volume to deactivate
	if (isdefined(self.bobbers))
	{
		println("stopping " + self.bobbers.size + " bobbing objects");
		thread stop_bobbing(self.bobbers);
	}
}

DebugBobbingObjects()
{
	foreach (obj in level.bobbing_objects)
	{
		obj.origin = obj.origin + (0,0,480);
	}
}

ControlBobbingVolume( id, start )
{
	vols = getentarray("bobbing_volume","script_noteworthy");
	foreach (vol in vols)
	{
		if (isdefined(vol.script_parameters) && (vol.script_parameters == id))
		{
			if (start)
				vol thread ActivateBobbingObjects();
			else
				vol thread DeactivateBobbingObjects();
		}
	}
}

StopRocking( ref2 )
{
	flag_wait( "obj_capturesub_complete" );
	level notify("stop_rocking");
//	level waittill("stop_rocking");
	level.player playerSetGroundReferenceEnt( undefined );
	self Delete();
	if (isdefined(ref2))
		ref2 Delete();
}

OnOutsideOfSub()
{
	level.rocking_mag[0] = 0.5;
	level.rocking_mag[1] = 1.5;
	flag_set("outside_above_water");
}

OnInsideOfSub()
{
	level.rocking_mag[0] = 1.0;
	level.rocking_mag[1] = 2.5;
	flag_clear("outside_above_water");
}

hide_sub_water()
{
	water = getentarray( "rocking_water", "targetname" );
	foreach( patch in water )
	{
		patch hide();	
	}
}

show_sub_water()
{
	water = getentarray( "rocking_water", "targetname" );
	foreach( patch in water )
	{
		patch show();
	}
}

watch_water_on()
{
	level endon( "player_on_boat" );
	while( 1 )
	{
		trigger_wait_targetname( "trig_water_on" );
		thread show_sub_water();
		wait( 0.05 );
	}
}

watch_water_off()
{
	level endon( "player_on_boat" );
	while( 1 )
	{
		trigger_wait_targetname( "trig_water_off" );
		thread hide_sub_water();
		wait( 0.05 );
	}
}

RockingSub()
{
	level endon("stop_rocking");
	refposent = getent("rocking_reference", "targetname");
	refent = spawn_tag_origin();
	refent2 = undefined;
	if (!isdefined(refposent))
	{
		refent.angles = (0, 0, 0);
	}
	else
	{
		refent.origin = refposent.origin;
		refent.angles = refposent.angles;
		/*
		refent2 = spawn_tag_origin();
		refent2.origin = refposent.origin;
		refent2.angles = refposent.angles;
		*/
	}
	refent thread StopRocking( refent2 );
	sgn = 1;
	level.rocking_mag[0] = 1.0;
	level.rocking_mag[1] = 2.5;
	rocking_waters = getentarray( "rocking_water", "targetname" );
	debris = getentarray( "bobbing_small", "script_noteworthy" );
	foreach (ent in debris)
	{
		ent.start_origin = ent.origin;
		ent.start_angles = ent.angles;
		
		x = cos(ent.angles[1]);
		y = sin(ent.angles[1]);
		ent.rock_ang = (x, 0, y);
	}
	if (isdefined(refent2))
	{
		foreach (ent in rocking_waters)
		{
			ent linkto( refent2, "tag_origin" );
		}
	}
	thread setup_ent_rockers();
	level.player playerSetGroundReferenceEnt( refent );
	thread set_grav( refent );
	while (true)
	{
		t = RandomFloatRange( 2.0, 3.0 );
		angle = sgn * RandomFloatRange( level.rocking_mag[0], level.rocking_mag[1] );
		sgn = -1 * sgn;
		angles = ( 0, 0, angle );
		refent.targetangles = angles;
		refent.targettime = gettime() + 1000*t;
		aud_send_msg("if_the_sub_is_a_rocking_dont_come_a_knocking");
		refent rotateto( angles, t, t/3, t/3 );
		thread rock_ents( sgn, t, t/3, t/3 );
		thread rock_debris( debris, angles, t, t/3, t/3 );
		if (isdefined(refent2))
		{
			angles = (0, 0, 0.5*angle );
			refent2 rotateto( angles, t, t/3, t/3 );
		}
		wait t;
	}
}


set_grav( view_angle_controller_entity )
{
	level endon( "stop_rocking" );
	thread reset_grav();
	count = 0;
	jolt_org = getstruct( "jolter", "targetname" );
	flag_wait( "hatch_player_using_ladder" );
	while( 1 )
	{ 
		toup = anglestoup( view_angle_controller_entity.angles );
		grav_dir = -1 * toup ;
		grav_ampped = grav_dir * ( 1, 10, .75 ); //changing the amplitude so we get more movement
		grav = vectorNormalize( grav_ampped );

		SetPhysicsGravityDir( grav );
		
		count++;
		if( count > 10 )
		{
			//jittering to get phy obj to move a bit
			PhysicsJitter(jolt_org.origin, 1000, 800, .01, .1 );
			count = 0;
		}
		wait( .05 );
	}
}

reset_grav()
{
	level waittill( "stop_rocking" );
	wait( .05 );
	SetPhysicsGravityDir( ( 0, 0, -1 ) );
}

setup_ent_rockers()
{
	level.rockers = [];
	level.rockers_opp = [];
	level.rocker_hangers = [];
	
	doors = getentarray( "sub_pressuredoor_rocker", "targetname" );
	foreach( door in doors )
	{
		org = getent( door.target, "targetname" );
		door linkto( org );
		level.rockers[level.rockers.size] = org;
	}
	
	doors = getentarray( "sub_pressuredoor_rocker_opposite", "targetname" );
	foreach( door in doors )
	{
		org = getent( door.target, "targetname" );
		door linkto( org );
		level.rockers_opp[level.rockers_opp.size] = org;
	}
	
	hangers01 = getentarray( "dyn_hanger", "targetname" );
	foreach( ent in hangers01 )
	{
		org = getent( ent.target, "targetname" );
		ent linkto( org );
		level.rocker_hangers[level.rocker_hangers.size] = org;
	}
}


rock_ents( sig, time, accel, decel )
{
	angle = 3 * ( level.rocking_mag[1] * sig );
	
	foreach( org in level.rockers ) 
	{
		org rotateto( ( org.angles[0], org.angles[1] + ( angle ) , org.angles[0] ), time, accel, decel );
	}
	
	foreach( org in level.rockers_opp ) 
	{
		org rotateto( ( org.angles[0], org.angles[1] + ( -1 * angle ) , org.angles[0] ), time, accel, decel );
	}
	
	foreach( org in level.rocker_hangers ) 
	{
		switch( org.script_noteworthy )
		{
			case "x":
				org rotateto( ( org.angles[0] + ( angle ), org.angles[1]  , org.angles[0] ), time, accel, decel );
			break;	
			case "x_neg":
				org rotateto( ( org.angles[0] + ( -1 * angle ), org.angles[1]  , org.angles[0] ), time, accel, decel );
			break;	
			case "y":
				org rotateto( ( org.angles[0] , org.angles[1] + ( angle )  , org.angles[0] ), time, accel, decel );
			break;	
			case "y_neg":
				org rotateto( ( org.angles[0] , org.angles[1] + ( -1 * angle )  , org.angles[0] ), time, accel, decel );
			break;
			case "z":
				org rotateto( ( org.angles[0] , org.angles[1], org.angles[0] + ( angle ) ), time, accel, decel );
			break;
			case "z_neg":
				org rotateto( ( org.angles[0] , org.angles[1], org.angles[0] + ( -1 * angle ) ), time, accel, decel );
			break;
			default:
			break;
		}
	}
	/*
	foreach( org in level.rocker_hangers03 ) 
	{
		//org rotateto( ( org.angles[0] + ( angle ), org.angles[1]  , org.angles[0] ), time, accel, decel );
		rot = combineangles( (0, angle, 0), org.angles );
		org rotateto( rot, time, accel, decel );
	}
	*/
}

rock_debris( debris, angles, t, accel, deccel )
{
	movedir = (0,1,0);
	roll = angles[2];
	offset = roll/2.5;	// we normalize the offset to the biggest amount of roll for tuning ease
	
	foreach (ent in debris)
	{
		mag = RandomFloatRange(4, 12);
		target = ent.start_origin + mag*offset*movedir;
	//	displacement = randomFloatRange( -4, 4 );
	//	target = (target[0], target[1], target[2] +  displacement);
		ent moveto( target, t, accel, deccel );
		angmag = randomFloatRange(3*level.rocking_mag[0], 3*level.rocking_mag[1]);
		ang = angmag*offset;
		dAngles = ( ent.rock_ang[0] * ang, ent.rock_ang[1] * ang, ent.rock_ang[2] * ang );
		angles = ent.start_angles + dAngles;
		ent rotateto( angles, t, accel, deccel );
	}
}


silo_interior_visibility( bVisible )
{
	ents = getentarray( "missle_silo_pocket", "target" );
	foreach (ent in ents)
	{
		if (bVisible)
			ent Show();
		else
			ent Hide();
	}
}

open_missile_hatch( side, index )
{
	sn_name = "missile_hatch_"+side+"_"+index;
	ents = getentarray( sn_name,"script_noteworthy" );
	animated = undefined;
	foreach(ent in ents)
	{
		if (!isdefined(ent.targetname))
			continue;
		if (ent.targetname == "missile_hatch")
		{
			animated = ent;
			break;
		}
	}
	assert(isdefined(animated));
	animated.animname = "missile_hatch";
	animated SetAnimTree();
	dummy = spawn_tag_origin();
	dummy.origin = animated.origin;
	dummy.angles = (270,0,0);// animated.angles;
	playfxontag(getfx("steam_missile_tube"), dummy, "tag_origin");
	animated anim_single_solo( animated, "open");
	life = randomfloat(3) + 2;
	wait (life);
	stopfxontag(getfx("steam_missile_tube"), dummy, "tag_origin");
	dummy delete();
}

open_missile_silo( side, index )
{
	sn_name = "missle_silo_"+side+"_"+index;
	ents = getentarray( sn_name,"script_noteworthy" );
	// out of the ents, find the one with the correct targetname
	animated = undefined;
	foreach(ent in ents)
	{
		if (!isdefined(ent.targetname))
			continue;
		if (ent.targetname == "missile_silo_door")
		{
			animated = ent;
			break;
		}
	}
	assert(isdefined(animated));
	assert(isdefined(animated.target));
	target = undefined;
	foreach(ent in ents)
	{
		if (!isdefined(ent.targetname))
			continue;
		if (ent.targetname == animated.target)
		{
			target = ent;
			break;
		}
	}
	assert(isdefined(target));
	animated.animname = "missile_door";
	animated SetAnimTree();
	target linkto(animated,"door");
	aud_send_msg("sub_missile_door_open", target);
	//play water streaming out fx
	if (side == "l")
			exploder(500 + index);
	animated anim_single_solo( animated, "open");
}

wait_to_sequence_missiles()
{
	flag_wait("start_opening_missile_doors");
	silo_interior_visibility( true );
	for (i=0; i<6; i++)
	{
		delay = (5-i)*0.5 + randomfloatrange(0.0,0.4);
		delaythread( 0.1 + delay, ::open_missile_silo,"l", i);
		delaythread( 0.3 + delay, ::open_missile_silo,"r", i);
	}
	for (i=0; i<9; i++)
	{
		delay = (8-i)*0.5 + randomfloatrange(0.0,0.4);
		delaythread( 0.7 + delay, ::open_missile_hatch,"l", i);
		delaythread( 1.0 + delay, ::open_missile_hatch,"r", i);
	}
	delaythread( 2.5, ::launch_ssn19,"l", 9);
	delaythread( 3.5, ::launch_ssn19,"l", 7);
	
	//rumble
	level.zodiac_rumble delaythread ( 2.8, ::rumble_ramp_to,  0.2, 0.1 );	
	level.zodiac_rumble delaythread ( 4.2, ::rumble_ramp_to, 0, 1 );		//and stop
}

play_ssn19fx( name )
{
	//Start the screen fx thread
	/*
	thread launch_ssn12_screenfx();
	//Start the initial ingnition flames
	if(name=="ssn12_1_r_i") exploder(690);
	else exploder(691);
	//Start the main ignition 
	wait(.5);
	if(name=="ssn12_1_r_i") exploder(692);
	else exploder(693);
	*/
	//start the white launch smoke & trail
	wait(0.95);
	PlayFXOnTag( getfx( "ssn12_launch_smoke12" ), self, "tag_tail" );
	//play reflection effect
	//explosionLoc = self.origin;
	//maps\ny_harbor_fx::update_fire_reflections_manager("sub_missile_launch", (explosionLoc[0], explosionLoc[1], -225) );
	//start the black smoke
	wait(.5);
	//PlayFXOnTag( getfx( "ssn12_init" ), self, "tag_tail" );
	ent_flag_waitopen( "contrails" );
	//stopfxontag(getfx( "ssn12_init" ), self, "tag_tail");
	stopfxontag(getfx( "ssn12_launch_smoke12" ), self, "tag_tail");
}

play_ssn19fx_alt( name )
{
	//Start the screen fx thread
	//thread launch_ssn12_screenfx();
	//Start the initial ingnition flames
	/*
	if(name=="ssn12_1_r_i") exploder(690);
	else exploder(691);
	//Start the main ignition 
	wait(.5);
	if(name=="ssn12_1_r_i") exploder(692);
	else exploder(693);
	*/
	//start the white launch smoke & trail
	wait(.5);
	PlayFXOnTag( getfx( "ssn12_launch_smoke" ), self, "tag_tail" );
	//start the black smoke
	wait(.5);
	PlayFXOnTag( getfx( "ssn12_init" ), self, "tag_tail" );
}

open_ssn19_wings()
{
	self endon("death");
	wait 0.5;
	self setanim( level.scr_anim["ss_n_12_missile"]["open"], 1, 0 );
}


launch_ssn19( side, index )
{
	// get the hatch
	sn_name = "ssn19_"+side+"_"+index;
	// use the hatch to determine the starting point for the missile
	missile = spawn_vehicle_from_targetname( sn_name );
	missile.animname = "ss_n_12_missile";
	missile SetAnimTree();
	missile setanim( missile getanim("close_idle"), 1, 0 );
	missile.script_vehicle_selfremove = true;
	missile thread play_ssn19fx( sn_name );//seperate thread to sequence fx off the missiles
	aud_send_msg("sub_missile_launch", missile);

	wait 0.75;
	missile thread open_ssn19_wings();
	thread gopath( missile );
}





///////////////////////////////////
//////////---- SETUP ----//////////
///////////////////////////////////

sub_give_player_weapon()
{
	level.player enableweapons();
}

setup_sandman()
{
	assert(level.sandman.animname == "lonestar");
	level.sandman.ignoreall = false;
	level.sandman.awareness = 1;
	//level.sandman enable_cqbwalk();
	level.sandman enable_ai_color();
	level.sandman disable_surprise();
	//level.sandman walkdist_zero();
}



setup_music()
{
	
	/*
	"mus_board_sub" - When the player first gets on the outside of the sub (after being in the water).
	 
	"mus_enter_sub" - When the player lands in the sub (after sliding down the ladder).
	 
	"mus_sub_combat_begin" - When interior combat begins (right when sandman opens the first sub door).
	 
	"mus_sub_scuttle_announcement" - Halfway up the stairs after the flooded room. (Note this is where Glen 
	                wants a Russian PA announcement saying that they are scuttling the ship, then sirens go off, etc.
	 
	"mus_sub_door_breach" - When sub door explodes.
	 
	"mus_sub_combat_end" - When the last enemy dies in the final control room.
	 
	"mus_program_launch" - After final combat, when Sandman says "Frost... on me."
	 
	"mus_sandman_copies_all" - When Sandman says to Overlord, "Sandman copies all" after programming the missile.
	*/
	
	//aud_send_msg( "mus_board_sub" );
	
	
	thread setup_music_before_door_breach(); // For door breach checkpoint to work with music cues.
	
	flag_wait( "ladder_done" );
	aud_send_msg( "mus_enter_sub" );
	
	flag_wait( "barracks_sandman_opening_door" );
	aud_send_msg( "mus_sub_combat_begin" );
	
	flag_wait( "reactor_room_announcement" );
	aud_send_msg( "mus_sub_scuttle_announcement" );
	wait(3);
	aud_send_msg("aud_scuttle_alarms_start");
}

// For door breach checkpoint to work with music cues.
setup_music_before_door_breach()
{
	flag_wait( "door_blown" );
	aud_send_msg( "mus_sub_door_breach" );
	
	flag_wait( "breach_done" );
	aud_send_msg( "mus_sub_combat_end" );
	
	//flag_wait( "vo_sub_interior_6" );
	flag_wait( "vo_sandman_checkpointneptune" );
	aud_send_msg( "mus_program_launch" );
}

// trying to retain vo timing...
VO_audio()
{
	//wait 3;
	thread vo_sub_exterior();
	thread vo_sub_exterior_allies();
	thread vo_sub_interior_engine_room();
	thread sandman_exit_nag_vo();
	//thread vo_sub_interior_barracks();
	thread vo_sub_interior_reactor();
	thread vo_sub_interior_missile_room_1( );
	thread vo_sub_interior_missile_room_2( );
}

	
sub_missile_tubes_hide()
{
	//flag_wait( "ladder_done" );
	//hide the missile tubes so they don't appear while in the sub
	ents = getentarray( "missile_hatch", "targetname" );
	foreach( ent in ents )
	{
		ent hide();
	}
	
	ents = getentarray( "missile_silo", "targetname" );
	foreach( ent in ents )
	{
		ent hide();
	}
	
	ents = getentarray( "missle_silo_pocket_middle", "targetname" );
	foreach( ent in ents )
	{
		ent hide();
	}
	
	ents = getentarray( "missile_silo_door", "targetname" );
	foreach( ent in ents )
	{
		ent hide();
	}
	
	ents = getentarray( "missle_silo_pocket", "targetname" );
	foreach( ent in ents )
	{
		ent hide();
	}
	
	ents = getentarray( "missle_silo_pocket_rear", "targetname" );
	foreach( ent in ents )
	{
		ent hide();
	}
	
}


sub_missile_tubes_show()
{
	flag_wait( "vo_bridge_is_done" );
	ents = getentarray( "missile_hatch", "targetname" );
	foreach( ent in ents )
	{
		ent show();
	}
	ents = getentarray( "missile_silo", "targetname" );
	foreach( ent in ents )
	{
		ent show();
	}
	
	ents = getentarray( "missle_silo_pocket_middle", "targetname" );
	foreach( ent in ents )
	{
		ent show();
	}
	
	ents = getentarray( "missile_silo_door", "targetname" );
	foreach( ent in ents )
	{
		ent show();
	}
	
	ents = getentarray( "missle_silo_pocket", "targetname" );
	foreach( ent in ents )
	{
		ent show();
	}
	
	ents = getentarray( "missle_silo_pocket_rear", "targetname" );
	foreach( ent in ents )
	{
		ent show();
	}
}

setup_the_dead()
{
	flag_wait("sub_entering");
	spawner = getent("sub_spawner_for_dead1", "targetname");
	Lnodes = getentarray("sub_dead_and_dying_loops", "targetname");

	foreach (node in Lnodes)
	{
		guy = spawner spawn_ai( true );
		wait( .05 );
		guy gun_remove();
		guy dummy_keep_pose( node, node.animation );
		//wait 0.05;
	}
}

sub_setup_enemy()
{
	self disable_long_death();
	self disable_surprise();
	self.grenadeammo = 0;
	
	if( isDefined( self.script_parameters ) )
	{
		self thread sub_enemy_vo();
	}
}

sub_enemy_vo()
{
	s_line = "";
	s_flag = "";
	switch( self.script_parameters )
	{
		case "extinguisher":
			self.animname = "extinguisher";
			s_line = "nyharbor_ru1_extinguisher";
			s_flag = "vo_extinguisher";
			break;
		case "reactor":
			self.animname = "reactor";
			s_line = "nyharbor_ru2_reactorroom";
			s_flag = "vo_reactor";
			break;
		case "stairs":
			self.animname = "stairs";
			s_line = "nyharbor_ru3_rushthem";
			s_flag = "vo_stairs";
			break;
		case "missile_1":
			self.animname = "missile_1";
			s_line = "nyharbor_ru3_intruders";
			s_flag = "missile_room_1_vo";
			break;
		case "missile_2":
			self.animname = "missile_2";
			s_line = "nyharbor_ru3_fireyourweapon";
			s_flag = "vo_missile_room_2";
			break;
		case "missile_3":
			self.animname = "missile_3";
			s_line = "nyharbor_ru3_outofammo";
			s_flag = "vo_missile_room_3";
			break;
	}
	
	self thread sub_enemy_play_vo( s_flag, s_line );
}

sub_enemy_play_vo( in_flag, in_line )
{
	self endon( "death" );
	flag_wait( in_flag );
	self dialogue_queue( in_line );
}

//////////////////////////////////////
//////////---- EXTERIOR ----//////////
//////////////////////////////////////
sub_exterior_ambient()
{
	thread sub_exterior_helicopters();
}

sub_exterior_helicopters()
{
	level.sub_exterior_hinds = [];
	
	//array_spawn_function_targetname( "sub_exterior_hind" , ::sub_exterior_helicopter_add_as_target );
	//thread sub_exterior_fire_at_hinds();
	flag_wait( "ready_for_player_slide" );
	wait( 15 );
	count = 0;
	if( !flag( "hatch_player_using_ladder" ) )
	{
		hind_player_killer_spawn = getent( "sub_exterior_hind_kill_player", "targetname" );
		hind_player_killer = hind_player_killer_spawn spawn_vehicle_and_gopath();
		aud_send_msg("hind_player_killer", hind_player_killer);
		hind_player_killer SetMaxPitchRoll( 10, 50 );
		level notify( "sub_exterior_chopper_spawned", hind_player_killer );
		flag_wait( "sub_exterior_hind_kill_player_fire" );
		while( !flag( "hatch_player_using_ladder" ) )
		{
			if( count > 2 ){
				level.player kill();
			}
			hind_player_killer sub_exterior_heli_fire_turret( level.player, 50, .05 );
			count++;
			wait( 5 );
		}
		hind_player_killer delete();
	}
}

sub_exterior_fire_at_hinds()
{
	flag_wait( "sub_exterior_hind_1_fire" ); 

	orgs = getStructarray( "sub_exterior_fire_at_hind", "targetname" );

	timer = gettime() + 10000;

	while( timer > gettime()  )
	{
		if(  level.sub_exterior_hinds.size < 1 )
			break;
			
		//foreach( org in orgs )
		//{
			org = random( orgs );
			target = random( level.sub_exterior_hinds );
			//for( i=0; i < 3; i++ )
			//{
				magicbullet( "rpg", org.origin, target.origin );
			//}
			//wait( randomfloatrange( 0, .05 ) ); 
		//}
		wait( randomfloatrange( 1, 2 ) );
	}
}

sub_exterior_chinook()
{
	self endon( "death" );
	aud_send_msg( "chinook_spawned", self );
	self.animname = "ch46e";
	self SetAnimTree();
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

sub_exterior_helicopter_add_as_target()
{
	level.sub_exterior_hinds[level.sub_exterior_hinds.size] = self;
	
	self waittill( "death" );
	level.sub_exterior_hinds = array_remove( level.sub_exterior_hinds, self );
}

sub_exterior_helicopter_fire_turret( )
{
	aud_send_msg( "hind_spawned", self );
	name = self.script_noteworthy;
	self endon( "death" );
	flag_wait( name + "_fire" );
	target = GetStruct( name + "_target", "targetname" );
	self sub_exterior_heli_fire_turret( target, 75, 0.1 );
}

sub_exterior_heli_fire_turret( eTarget, iShots, delay )
{
	self endon( "death" );
	if ( IsDefined( self.defaultWeapon ) )
		defaultWeapon = self.defaultWeapon;
	else
		defaultWeapon = "hind_turret";
	weaponName = "hind_turret";

	loseTargetDelay  = undefined;
	tags = [];
	self SetVehWeapon( defaultWeapon );
	if ( !isdefined( iShots ) )
		iShots = 1;
	if ( !isdefined( delay ) )
		delay = 1;
	
	entTarget = etarget;
	dist_increment = undefined;
	forward = undefined;
	
	//if the target is a struct, need to spawn a dummy ent to fire at
	if ( !isdefined( eTarget.classname ) )
	{
		dummyTarget = Spawn( "script_origin", eTarget.origin );
		self thread delete_on_death( dummyTarget );
		dummyTarget.targetname = eTarget.targetname;
		dummyTarget.origin = eTarget.origin;
		entTarget = dummyTarget;
	}
	
	if( isdefined( etarget.target ) )
	{
		if( !IsDefined( eTarget.classname ) )
		{
			etarget2 = GetStruct( etarget.target, "targetname" );
			dist = distance( etarget.origin, etarget2.origin );
			angles = vectortoangles( etarget2.origin - etarget.origin );
			forward = anglestoforward( angles );
			dist_increment = dist/ishots;
		}
	}
	
	self setturrettargetent( entTarget );
	
	for( i = 0; i < iShots; i++ )
	{ 
		self FireWeapon( "tag_flash", entTarget );//tag_barrel  // tag_turret
		wait( delay );
		if( isdefined( dist_increment ) && isdefined( forward ) )
		{
			enttarget.origin = entTarget.origin + forward * dist_increment;
		}
	}	
	
	self SetVehWeapon( defaultWeapon );
}

sub_entrance()
{
	thread hatch_sandman_drop_frag();
	thread hatch_player_slide();
	
	flag_wait("sub_entrance_gameplay");
	thread open_hatch();
	thread hatch_enemies();
	thread maps\ny_harbor_fx::surface_sub_hatch_moment();
}

hatch_enemies()
{
	level.hatch_enemies_dead = 0;
	
	spawners = getentarray( "hatch_enemy", "targetname" );
	array_thread( spawners, ::add_spawn_function, ::setup_hatch_enemy );
	array_spawn( spawners, true );
}

setup_hatch_enemy()
{
	self endon( "death" );
	self thread hatch_enemy_monitor_death();
	self.goalradius = 8;
	self.noragdoll = true;
	self.ignoreall = true;
	self.ignoreme = true;
	self waittill( "goal" );
	wait( 1 );
	self.ignoreme = false;
	self.ignoreall = false;
}

sandman_kill( guy )
{
	PlayFxOnTag( getfx( "flesh_hit" ), guy, "j_head" );
}


hatch_enemy( anim_ent, targetname, animation, ignore )
{	
	spawner = getent( targetname, "targetname" );
	guy = spawner spawn_ai( true );
	spawn_failed();
	if( isDefined( ignore ) && ignore )
	{
		guy magic_bullet_shield();
		guy thread ignore_until_done( anim_ent, animation );
		guy thread hatch_enemy_monitor_death();
		guy.allowdeath = true;
		guy.noragdoll = true;
		anim_ent anim_generic( guy, animation );
		if( isDefined( guy ) && isAlive( guy ) )
		{
			guy stop_magic_bullet_shield();
			guy kill_no_react();
		}
	}
	else
	{
		guy.goalradius = 8;
		guy magic_bullet_shield();
		guy thread hatch_enemy_monitor_death();
		guy.allowdeath = true;
		guy.noragdoll = true;
		guy delaythread( 3.5, ::stop_magic_bullet_shield );
		anim_ent anim_generic( guy, animation );
	}
}

ignore_until_done( anim_ent, animation )
{
	self.ignoreme = true;
	self endon( "death" );
	anim_ent waittill( animation );
	wait( 1 );
	self.ignoreme = false;
}

hatch_enemy_monitor_death()
{
	self waittill( "death" );
	level.hatch_enemies_dead++;
	
	if( level.hatch_enemies_dead > 1 )
	{
		flag_set( "hatch_enemies_dead" );
	}
}

open_hatch()
{
	hatchA = getent("hatch_component1", "targetname");
	hatchB = getent("hatch_component2", "targetname");
	org = spawn_tag_origin();
	//org2 = getent("hatch_org2", "targetname");
	org3 = getent("hatch_org", "targetname");
	org.origin = org3.origin;
	org.angles = org3.angles;
	if (isdefined(hatchA))
	{
		hatchA Hide();
		hatchA linkto (org, "tag_origin");
	}
	hatchB linkto (org, "tag_origin");
	flag_set( "vo_hatch_open" );
	org rotateto((154,0,180), 0.05);
}

open_hatch_rear()
{
	col = getent( "rear_hatch_col", "targetname" );
	col notsolid();
	
	flag_wait( "sub_control_room_sandman_exit" );

	hatchA = getent("rear_hatch_component1", "targetname");
	hatchB = getent("rear_hatch_component2", "targetname");
	org = spawn_tag_origin();
	org3 = getent("rear_hatch_org", "targetname");
	org.origin = org3.origin;
	org.angles = org3.angles;
	if (isdefined(hatchA))
	{
		hatchA Hide();
		hatchA linkto (org, "tag_origin");
	}
	hatchB linkto (org, "tag_origin");
	
	org rotateto((150, org.angles[1], org.angles[2]) , 0.05);
	col solid();
	
	hatch_col = getent( "rear_hatch_col_interior", "targetname" );
	hatch_col notsolid();
	
	hatch_col_top = getent( "rear_hatch_col_top", "targetname" );
	hatch_col_top notsolid();
	
}

hatch_sandman_drop_frag()
{
	thread setup_frag();
	
	addnotetrack_customfunction( level.sandman.animname, "show", ::show_frag, "ny_harbor_sandman_drops_frag_inhatch" );
	
	if(!flag_exist("hatch_enemies_dead"))
		flag_init("hatch_enemies_dead"); //for debug load
		
	flag_wait( "hatch_enemies_dead" );
	//level.sandman.moveplaybackrate = 1;
	aud_send_msg("aud_prime_sandman_grenade_anim");
	level.sandman enable_surprise();
	anim_ent1 = getstruct( "hatch_sandman_drop_frag_anim_ent", "targetname" );
	
	level.sandman disable_ai_color();
	
	anim_ent1 anim_reach_solo( level.sandman, "ny_harbor_sandman_drops_frag_inhatch" );
	aud_send_msg("aud_start_sandman_grenade_anim");
	thread entrance_vo_timing();
	
	delaythread( 11, ::flag_set_wrapper, "ready_for_player_slide" );
	delaythread( 3, ::hide_grenade );
	anim_ent1 anim_single_solo( level.sandman, "ny_harbor_sandman_drops_frag_inhatch" );

	level.sandman enable_ai_color_dontmove();
//	level.sandman thread SmartLaserSystem();
}

SmartLaserSystem()
{
	self endon("disable_smart_laser");
	
	while(1)
	{
		if(self.isreloading || (self.a.state == "cover" && (self.a.special == "cover_left" || self.a.special == "cover_right")))
		{
			self laserforceoff();
		}
		else
		{
			self laserforceon();		
		}
		wait(0.05);
	}
}

hide_grenade()
{
	level.frag delete();
}

flag_set_wrapper(param)
{
	flag_set(param);
}

setup_frag()
{
	level.frag = getent( "frag_grenade", "targetname" );
	level.frag hide();
	org = level.sandman getTagOrigin("tag_inhand");
	ang = level.sandman getTagAngles("tag_inhand");
	level.frag.origin = org;
	level.frag.angles = ang;
	level.frag linkto( level.sandman, "tag_inhand" );
}

show_frag( guy )
{
	level.frag show();
}

hatch_player_slide()
{
	//trigger waits for flag ("ready_for_player_slide");
	aud_send_msg("aud_prime_player_downladder");
	use_trigger = getent( "hatch_player_slide", "targetname" );
	use_trigger SetHintString( &"NY_HARBOR_HINT_USE_TO_ENTER" );
	use_trigger UseTriggerRequireLookAt();
	use_trigger waittill( "trigger" );
	use_trigger trigger_off();
	
	level.player disableWeapons();
	level.player FreezeControls( true );
	
	maps\_shg_common::SetUpPlayerForAnimations();
	
	level.sdv_player_arms hide();//make sure the arms are hidden
	flag_set( "hatch_player_using_ladder" );
	aud_send_msg("aud_player_downladder");
	
	
	node = getstruct("hatch_player_slide_anim_pos", "targetname");
	snode = spawn_tag_origin();
	snode.origin = node.origin; //+ (0,0,30);
	snode.angles = node.angles;

	level.player playerlinktoblend( level.sdv_player_arms, "tag_player", 0.2 );

	level.sdv_player_arms dontcastshadows();
	level.sdv_player_arms  delaycall( .3, ::show );
	level delaythread( 3.6, ::remove_hatch_corpses );
	snode anim_single_solo( level.sdv_player_arms, "player_ladder_slide" );
	
	level.sdv_player_arms hide();
	level.player FreezeControls( false );
	level.player unlink();
	level.player enableWeapons();
	
	maps\_shg_common::SetUpPlayerForGamePlay();
	
	flag_set( "ladder_done" );
	
	thread OnInsideOfSub();
}

remove_hatch_corpses()
{
	ClearAllCorpses();
}

entrance_vo_timing()
{
	wait ( 2 );
	flag_set("vo_frag_out");
	wait ( 5 );
	flag_set("vo_frag_out_clear");
}

sub_extra_spawn( skip_flag_wait )
{
//	flag_wait( "sub_entrance_gameplay" );
	if ( !IsDefined( skip_flag_wait ) )
	{
		flag_wait( "sub_breach_finished" );
	}

	array_spawn_function_targetname( "submarine_extra_friends", ::sub_extra_friendly );
	array_spawn_function_targetname( "submarine_extra_enemy", ::sub_extra_enemy );
	array_spawn_targetname( "submarine_extra_friends" );
	array_spawn_targetname( "submarine_extra_enemy" );
}

sub_extra_friendly()
{
	self endon( "death" );

	self.noreload = true;
	self.noragdoll = true;
	self.grenadeammo = 0;
	self magic_bullet_shield();
	self disable_surprise();
	self disable_bulletwhizbyreaction();
	self.disableFriendlyFireReaction = true;
	self.baseaccuracy = 10;
	self.accuracy = 1;
	if( isDefined( self.script_friendname ) && self.script_friendname == "Grinch" )
	{
		level.sub_grinch = self;
		level.sub_grinch.animname = "sub_grinch";
	}
	if( isDefined( self.script_friendname ) && self.script_friendname == "Truck" )
	{
		level.sub_truck = self;
		level.sub_truck.animname = "sub_truck";
	}

	self thread sub_friendly_shoot_chopper();

	if ( IsDefined( self.script_godmode ) )
	{
		self SetCanDamage( false );
	}

	if(!flag_exist("hatch_enemies_dead"))
		flag_init("hatch_enemies_dead"); //for debug load
		
	flag_wait( "hatch_enemies_dead" );
	self.ignoresuppression = true;

	//disable friendlies dying so the ragdolls don't go flying through the air
	//if ( IsDefined( self.script_godmode ) )
	//{
	//	self waittill( "goal" );
	//	self SetCanDamage( true );
	//}

	// Let's kill the enemies quicker
	while( self.baseaccuracy < 50 )
	{
		if ( flag( "ladder_done" ) )
		{
			break;
		}

		self.baseaccuracy += 1;
		wait( 0.5 );
	}

	flag_wait( "ladder_done" );

	if ( IsDefined( self.magic_bullet_shield ) )
	{
		self stop_magic_bullet_shield();
	}

	self Delete();
}

sub_friendly_shoot_chopper()
{
	self endon( "death" );
	level waittill( "sub_exterior_chopper_spawned", chopper );

	// Would be best if this was a ent flag from the chopper when it 
	// gets to a specific vehicle node.
	wait( 8 );

	self stop_magic_bullet_shield();
	self SetEntityTarget( chopper );
}

sub_extra_enemy()
{
	self endon( "death" );
	self.script_noteworthy = undefined;
	self.health = 3;

	self disable_bulletwhizbyreaction();

	// Changing body models
	array = [ "body_russian_naval_assault_g", "body_russian_naval_assault_gg", "body_russian_naval_assault_h" ];
	self setModel( array[ RandomInt( array.size ) ] );

	self.noragdoll = true;
	/*if ( IsDefined( self.script_parameters ) )
	{
		self.deathanim = getgenericanim( self.script_parameters );
		self.deathfunction = ::sub_extra_death;
	}*/

	flag_wait( "ladder_done" );
	self Delete();
}

sub_extra_death()
{
	self thread sub_extra_death_thread();
	return false;
}

sub_extra_death_thread()
{
	power = 10;
	dir_offset = ( 0, -90, 0 );
	mult = 0.25;

	if ( self.script_parameters == "exposed_crouch_death_twist" )
	{
		self OrientMode( "face angle", self.angles[ 1 ] - 90 );
		dir_offset = ( 0, 90, 0 );
		power = 30;
		mult = 0.15;
	}

	time = GetAnimLength( self.deathanim );
	wait( time * mult );
	dir = AnglesToForward( self.angles + dir_offset );
	dir = dir * power;
	self Startragdollfromimpact( self GetTagOrigin( "j_spine4" ), dir );
	wait( 0.05 );
}

//////////////////////////////////////
//////////---- BARRACKS ----//////////
//////////////////////////////////////

sub_barracks()
{
	thread barracks_open_door();
	thread barracks_enemies();
	thread barracks_sandman_exit();
	
	flag_wait("trigger_barracks_entrance");
	
	thread bulkhead_door_vo();
}


barracks_open_door()
{
	anim_ent = getent( "barracks_door_open_anim_ent", "targetname" );
	door = spawn_anim_model( "door", anim_ent.origin );
	level.sub_doors[ level.sub_doors.size ] = door;
	
	anime = "open_with_wheel" ;

	anim_ent anim_first_frame_solo( door, anime );	
	
	flag_wait( "trigger_barracks_entrance" );
	
	level.sandman disable_ai_color();
	
	level.sandman disable_awareness();
	
	level.sandman notify("disable_smart_laser");
	level.sandman laserforceoff();

	anim_ent anim_reach_solo( level.sandman, anime );
	
	actors = make_array( level.sandman, door );
	
	aud_send_msg("aud_open_bulkhead_door");
	
	flag_set( "barracks_sandman_opening_door" );
	
	delaythread( 5, ::barracks_open_door_collision );
	anim_ent anim_single( actors, anime );
	
	//get sandman to next color node
	level.sandman enable_ai_color();
//	level.sandman thread SmartLaserSystem();
	trigger = getent( "barracks_sandman_after_door_open", "targetname" );
	trigger notify( "trigger" );
	level.sandman thread shoot_magic_bullets();

	battlechatter_on( "allies" );
	battlechatter_on( "axis" );
	
	wait( 2 );
	level.sandman enable_awareness();
}

shoot_magic_bullets()
{
	counter = 0;
	org = getstruct( "org_sandman_target", "targetname" );
	
	while( counter < 6 )
	{
		MagicBullet( "mp5_silencer_reflex_harbor", self GetMuzzlePos(), org.origin );
		wait( 0.05 );
		counter++;
	}
}

barracks_open_door_collision()
{
	col = getent( "barracks_open_door_col", "targetname" );
	col ConnectPaths();
	col delete();
}

bulkhead_door_vo()
{
	flag_set("vo_sub_interior_1");
	wait ( 5 );
	flag_set("vo_go_downstairs");
	
}

barracks_enemies()
{
	
	//slam door
	thread barracks_slam_door();
	//guy waving
	thread barracks_waver();
	
	//fire extinguisher
	
	//guys running
	//guy running hits wall
	thread barracks_run_and_stumble();
	//guy running coughing
	//thread barracks_runner();
}

barracks_runner()
{
	flag_wait( "trigger_barracks_entrance" );
	wait( 12 ); //waiting for sandmand to get the door open
	spawner = getent( "barracks_spawn1", "targetname" );
	guy = spawner spawn_ai( true );
	
	guy runners();
}

barracks_slam_door()
{
	thread barracks_slam_door_collision();
	
	flag_wait( "trigger_barracks_entrance" );
	spawner = getent( "barracks_slam_door", "targetname" );
	guy = spawner spawn_ai( true );
	spawn_failed();
	guy.animname = "barracks_2";
	guy thread magic_bullet_shield();
	guy.awareness = 1;
	guy disable_awareness();
	anim_ent = getstruct( "barracks_slam_door_anim_pos", "targetname" );
	door = spawn_anim_model( "door", anim_ent.origin );
	level.sub_doors[ level.sub_doors.size ] = door;
	anime = "slam_door" ;
	actors = make_array( guy, door );
	anim_ent anim_first_frame( actors, anime );	

	flag_wait_or_timeout( "barracks_slam_door", 20 );
	flag_set( "barracks_slam_door" );//incase of timeout
	guy thread dialogue_queue( "nyharbor_ru2_behinddoor" );
	delaythread( .05, ::anim_set_rate, actors, anime, 1.5 );
	anim_ent anim_single( actors, anime );
	guy stop_magic_bullet_shield();
	guy delete();

}	

barracks_slam_door_collision()
{
	col = getent( "barracks_slam_door_col", "targetname" );
	col ConnectPaths();
	col notsolid();
	
	flag_wait( "barracks_slam_door" );
	col disconnectpaths();
	col solid();
}

barracks_waver()
{
	flag_wait( "trigger_barracks_entrance" );
	//wait( 7.5 );
	spawner = getent( "barracks_waver", "targetname" );
	guy = spawner spawn_ai( true );
	guy.ignoreall = true;
	guy thread magic_bullet_shield();
		
	anim_pos = getstruct( "barracks_waver_anim_pos", "targetname" );
	anim_pos anim_generic_first_frame( guy, "launchfacility_b_blast_door_seq_waveidle" );
	flag_wait( "barracks_sandman_opening_door" );
	wait( 4 );
	//guy disable_death_anims();
	guy.allowdeath = true;
	guy stop_magic_bullet_shield();
	guy.ignoreall = false;
	anim_pos anim_generic( guy, "launchfacility_b_blast_door_seq_waveidle" );
	
	//wait( 8.5 );
	//anim_pos notify( "end_loop" );
	guy enable_death_anims();
	guy thread move_to_target_node();
}

barracks_run_and_stumble()
{
	flag_wait( "barracks_sandman_opening_door" );
	thread maps\ny_harbor_fx::door_open_smokeout_vfx();
	wait( 7.5 );
	
	spawner = getent( "barracks_run_and_stumble", "targetname" );
	guy = spawner spawn_ai( true );
	spawn_failed();
	guy.animname = "barracks_1";
	guy thread dialogue_queue( "nyharbor_ru1_americans" );
	guy thread ignore_until_goal();
	//guy disable_death_anims();
		
	//anim_pos = getstruct( "barracks_run_and_stumble_anim_pos", "targetname" );
	//anim_pos anim_generic( guy, "ny_harbor_affected_russian_guy1" );
	
	//guy enable_death_anims();
	guy thread move_to_target_node();
}

ignore_until_goal()
{
	self endon( "death" );
	self.ignoreall = true;
	self waittill( "goal" );
	self.ignoreall = false;
}

barracks_sandman_exit()
{
	level endon("sandman_paired_kill");
	
	anim_ent = getstruct( "barracks_sandman_exit_anim_pos", "targetname" );
	org = getstruct( "barracks_sandman_exit_anim_pos_guy", "targetname" );
	door = spawn_anim_model( "door", anim_ent.origin );
	level.sub_doors[ level.sub_doors.size ] = door;
	
	anime = "barracks_sandman_exit" ;

	anim_ent anim_first_frame_solo( door, anime );	
	
	flag_wait( "barracks_sandman_opening_door" );
	wait( 20 );
	
	level.sandman disable_ai_color();
	
	anim_ent anim_reach_solo( level.sandman, anime );
	actors = make_array( level.sandman, door );
	
//	anim_ent anim_single( actors, anime );
	anim_ent thread anim_single_solo( door, "barracks_sandman_exit" );
	org anim_single_solo( level.sandman, "barracks_sandman_exit" );
	thread barracks_sandman_exit_loop( org );
}

barracks_sandman_exit_loop( anim_ent )
{
	//special so we can stop sandmans loop so we don't get two later
	anim_ent thread anim_loop_solo( level.sandman, "barracks_sandman_exit_idle", "end_loop" );
	flag_set( "barracks_exit_nag_vo" );
	flag_wait_either( "sandman_paired_kill", "barracks_move_sandman" );
	anim_ent notify( "end_loop" );
	
	if( flag( "barracks_move_sandman" ) ) //if player backs through lookat trigger
	{
		level.sandman anim_stopanimscripted();
		loc = getent( "sandman_barracks_teleport", "targetname" );
		level.sandman teleport_ent( loc );
		level.sandman set_goal_pos( level.sandman.origin );
	}
}

move_to_target_node()
{
	self endon( "death" );
	
	if( !isalive( self ) )
	{
		return;
	}
	
	if( isdefined( self.target ) )
	{
		goal = GetNode( self.target, "targetname" );
		self setGoalPos( goal.origin );
		waittillframeend;
		self.goalradius = 64;
	}
	
}

//////////////////////////////////////////
//////////---- REACTOR ROOM ----//////////
//////////////////////////////////////////

sub_reactor_room()
{
	array_spawn_function_noteworthy( "reactor_room_runner", ::runners );
	thread reactor_room_sandman_paired_kill();
	thread reactor_room_vfx_steam();
	thread water_sheeting();
	thread reactor_room_pipe_burst();
}

reactor_room_vfx_steam()
{
	flag_wait( "reactor_room_vfx_steam_start" );
	//ents = getStructarray( "reactor_room_vfx_steam", "targetname" );
	//foreach( ent in ents )
	//{
		exploder(258);
		earthquake ( 0.3, 1.7, level.player.origin, 1024 );
	//}
}

water_sheeting()
{
	flag_wait( "ladder_done" );
	water_vols = getentarray( "sub_water_sheeting_vol", "targetname" );
	water_sheeting_on = false;
	while( !flag( "start_zodiac" ) )
	{
		if( check_volumes( water_vols ) )
		{
			if( water_sheeting_on == false )
			{
				level.player setwatersheeting( 1 );
				water_sheeting_on = true;
			}
			wait( .05 );
		}else if( water_sheeting_on == true )
		{
			level.player setwatersheeting( 1, 0.5 );
			water_sheeting_on = false;
			wait( .05 );
		}
		else{
			wait( .05 );
		}
	}
}

reactor_room_sandman_paired_kill()
{
	level endon( "sandman_paired_kill_interrupted" );
	addnotetrack_customfunction( level.sandman.animname, "HEADSMASH", ::reactor_room_head_smash, "ny_harbor_doorway_headsmash" );
	
	flag_wait( "sandman_paired_kill" );
	
	thread show_sub_water();
	
	anim_pos = getstruct( "reactor_room_sandman_paired_kill_anim_pos", "targetname" );
	
	//spawn guy to die
	spawner = getent( "reactor_room_sandman_paired_killed_enemy", "targetname" );
	enemy = spawner spawn_ai( true );
	spawn_failed();
	enemy.animname = "generic";
	enemy.ignoreall = true;
	enemy.ignoreme = true;
	enemy.allowdeath = true;
	enemy.health = 999999;
	//enemy thread monitor_paired_interrupt_enemy();
	enemy thread play_blood_fx();
	
	//handle anim
	actors = make_array( enemy, level.sandman );
	level.sandman notify("disable_smart_laser");
	level.sandman laserforceoff();
	//level.sandman thread monitor_paired_interrupt_sandman();
	
	aud_send_msg("aud_sub_sandman_pairedkill_headsmash");
	
	anim_pos thread anim_single(actors, "ny_harbor_doorway_headsmash");
	
	wait 165/30; //wait the number of frames (anim ends around 136 frames at 30fps) in the enemy's anim, then make him a drone

	enemy thread dummy_keep_pose( anim_pos, "ny_harbor_doorway_headsmash_enemy_deadpose" );
	
	//wait ((205-165) / 30); //sandman's animation is longer than the enemy's animation. waiting the remainder of that time

	level.sandman enable_ai_color();
//	level.sandman thread SmartLaserSystem();
	trigger = getent( "reactor_room_sandman_color_after_paired", "targetname" );
	trigger notify( "trigger" );
	flag_set( "sandman_paired_kill_complete" );
	level notify( "sandman_paired_kill_finished" );
	thread extinguisher_guy( 5 );

	// play a 1 frame duplicate animation of sandman's final frame to remove the gun rotation
	level.sandman waittillmatch( "single anim", "end" );
	// ny_harbor_doorway_headsmash_no_gun_flip is a 1 frame end of the end frame - but without the gun rotation
	anim_pos anim_single_solo(level.sandman, "ny_harbor_doorway_headsmash_no_gun_flip");
	// the next 2 lines set the transition out/in times to zero. this prevents a 360 degree quaternion spin.
	level.sandman SetAnim( level.scr_anim[ level.sandman.animname ][ "ny_harbor_doorway_headsmash" ], 0, 0 );
	level.sandman SetAnim( level.scr_anim[ level.sandman.animname ][ "ny_harbor_doorway_headsmash_no_gun_flip" ], 1, 0 );
	
	if( GetDvarInt( "demo_itiot" ) == 1 )
	{
		thread demo_fade();
	}
}

play_blood_fx()
{
	while( !flag( "sandman_paired_kill_complete" ) )
	{
		self waittill( "damage", amount, attacker, direction, position, damage_type );
	
		if ( IsDefined( position ) && IsDefined( damage_type ) )
		{
			if ( damage_type == "MOD_PISTOL_BULLET" ||
				 damage_type == "MOD_RIFLE_BULLET" || 
			 	damage_type == "MOD_EXPLOSIVE_BULLET" )
			{
				PlayFx( getfx( "flesh_hit" ), position );
			}
		}
		
		wait( 0.5 );
	}
}

monitor_paired_interrupt_enemy()
{
	level endon( "sandman_paired_kill_finished" );
	self waittill( "damage" );
	self anim_stopanimscripted();
	self kill();
	level notify( "sandman_paired_kill_interrupted" );
}

monitor_paired_interrupt_sandman()
{
	level endon( "sandman_paired_kill_finished" );
	level waittill( "sandman_paired_kill_interrupted" );
	self anim_stopanimscripted();
	
	level.sandman enable_ai_color();
	trigger = getent( "reactor_room_sandman_color_after_paired", "targetname" );
	trigger notify( "trigger" );
	flag_set( "sandman_paired_kill_complete" );
	level thread extinguisher_guy( 7 );
	
	if( GetDvarInt( "demo_itiot" ) == 1 )
	{
		thread demo_fade();
	}
}


demo_fade()
{
	flag_wait( "e3_guy_killed" );
	wait( 1 );
	level.player FreezeControls( true );
	thread battlechatter_off( "allies" );
	thread battlechatter_off( "axis" );
	aud_send_msg( "e3_demo_fade_out", 1 );
    thread introscreen_generic_fade_out("black", 5, 1, 1 );
	lines = [];
	lines[0] = &"NY_HARBOR_DEMO_1";
	thread demo_feed_lines(lines, 1);
	delaythread( 1, ::delete_badguys );
	wait( 3 );
	itiot_bridge_breach();
}

itiot_bridge_breach()
{
	//let player move
	level.player FreezeControls( false );
	//force player to stand if he wasn't when he hit the fade
	level.player SetStance( "stand" );
	//hide reactor room water behind player for fps
	thread maps\ny_harbor_code_sub::hide_sub_water();
	//send audio message
	aud_send_msg( "e3_demo_fade_in", 1 );
	aud_send_msg("start_bridge_breach");
	thread sub_missile_tubes_hide();
	thread sub_missile_tubes_show();
	thread open_hatch_rear();
	player_start = getstruct("start_breach_player_loc","targetname");
	level.player teleport_player( player_start );
	thread sub_exit();
	//flag sets for objectives
	flag_set( "obj_plantmine_given" );
	flag_set( "obj_plantmine_complete" );
	flag_set( "obj_capturesub_given");
	flag_set( "player_surfaces");
	flag_set( "ready_for_player_slide");
	flag_set( "hatch_player_using_ladder");
	flag_set( "sub_objective_breach");
	
	player_speed_percent( 75 );
	//run his setup code then override
	setup_sandman();
	sandman_start = getstruct("start_breach_sandman_loc","targetname");
	level.sandman forceTeleport( sandman_start.origin, sandman_start.angles );	
	thread RockingSub();
	vision_set_fog_changes("ny_harbor_sub_4", 0);
	setsaveddvar("sm_sunenable",0);
	setsaveddvar("sm_spotlimit",2);
	
	thread setup_music_before_door_breach();
}

extinguisher_guy( time )
{
	flag_init( "vo_extinguisher" );
	spawner = getent( "extinguisher_guy", "targetname" );
	org = getstruct( "org_fire_extinguisher", "targetname" );
	guy = spawner spawn_ai();
	if (isdefined(guy))
	{	// player can be quick enough to see the spawn point here, so we just skip the extinguisher_guy in that case
		guy.animname = "guy";
		guy.allowdeath = true;
		guy gun_remove();
		guy thread ignore_extinguisher( time );
		extinguisher = spawn_anim_model( "extinguisher" );
		extinguisher.animname = "extinguisher";
		
		guys = [];
		guys[0] = guy;
		guys[1] = extinguisher;
		
		guy thread monitor_end_loop( org, extinguisher );
		guy thread maps\ny_harbor_fx::sub_interior_extinguisherfx( extinguisher );
		flag_set( "vo_extinguisher" );
		org anim_loop( guys, "extinguisher_loop", "stop_loop" );
	}
}

monitor_end_loop( org, extinguisher )
{
	self waittill( "death" );
	org notify( "stop_loop" );
	extinguisher anim_stopanimscripted();
	extinguisher PhysicsLaunchClient( extinguisher.origin, (0,0,0) );
}

ignore_extinguisher( time )
{
	self endon( "death" );
	self.ignoreme = true;
	wait( time );
	self.ignoreme = false;
	level.sandman.favoriteenemy = self;
}

delete_badguys()
{
	//delete badguys we were just fighting
	badguys = GetAiArray( "axis" );
	foreach( guy in badguys )
	{
		guy delete();
	}
}

reactor_room_head_smash( guy )
{
	thread maps\ny_harbor_fx::head_smash_vfx();//should be a notetrack and played on a bone...
}

runners()
{
	self endon( "death" );
	self disable_long_death();
	
	self.awareness = 1; 
	self disable_awareness();
	self disable_cqbwalk();
	self.grenadeammo = 0;
	self notify( "retreat" );
	
	if( isDefined( self.script_parameters ) )
	{
		self thread sub_enemy_vo();
	}
	
	self waittill_either( "goal", "damage" );
	self enable_awareness();
	self enable_cqbwalk();
}



reactor_room_pipe_burst()
{
		flag_wait( "reactor_room_announcement" );
		wait( 1.0 );
		//earthquake ( 0.3, 1.7, level.player.origin, 1024 ); removed per Don Veca's/Bretts request
		wait( 0.3 );
		exploder(259);
		aud_send_msg("aud_premissileroom_pipeburst");
		//wait( 0.3 );
		//exploder(260);
		pipe_valve = getent("pipe_valve", "script_noteworthy");
    pipe_valve hide();

}

//////////////////////////////////////////
//////////---- MISSILE ROOM ----//////////
//////////////////////////////////////////

sub_missile_room()
{
	
	array_spawn_function_noteworthy( "missile_room_runner", ::runners );
	
}

//////////////////////////////////////////
//////////---- CONTROL ROOM ----//////////
//////////////////////////////////////////


breach_vo()
{
	thread vo_sub_interior_bridge();
}

bridge_breach()
{
	flag_init( "breaching_on" );
	
	thread backtrack_fail(); //fail player if he goes back into the sub
	thread breach_vo();
	level.bridge_dudes = [];
	level.breachEnemies_active = 0;
	level.breachEnemies_alive = 0;
	
	charge = getent("mil_frame_charge", "targetname");
	charge hide();
	
	snode = getent("bridge_breach_loc","targetname");	
	
	//set up door
	level.breach_door = spawn_anim_model( "breach_door", snode.origin );
	level.breach_door.animname = "breach_door";
	level.breach_door setanimtree();		
	snode anim_first_frame_solo( level.breach_door, "ny_harbor_door_breach" );	

	clicker1 = getent("detonator_1", "targetname");
	clicker1 hide();
	
	clicker2 = getent("detonator_2", "targetname");
	clicker2 hide();
	
	
	rshirt_spawner = getent("spawner_ambient_mis2_group2", "targetname");
	
	flag_wait( "sub_breach_sandman_to_postion" );
	guys = GetAiArray( "axis" );
	fov_var = GetDVarInt( "cg_fov" );
	angle = cos( fov_var );
	array_thread( guys, ::breach_retreat_and_delete, angle );
	aud_send_msg("bridge_breach_setup");
	flag_set( "vo_wait_at_door" );
	level.sandman disable_cqbwalk();
	level.sandman notify("disable_smart_laser");
	level.sandman laserforceoff();
	
	level.sandman disable_ai_color();
	sandman_wait_node = getstruct( "bridge_breach_sandman_idle", "targetname" );

	snode anim_reach_solo( level.sandman, "ny_harbor_door_breach_idle_trans" );
	snode anim_single_solo( level.sandman, "ny_harbor_door_breach_idle_trans" );
	snode thread anim_loop_solo( level.sandman, "ny_harbor_door_breach_idle", "end_idle" );
	level.sandman SetLookAtEntity( level.player );
	
	//set when sandman gets in position for the breach
	flag_wait("ready_for_breach");
	
	flag_set( "vo_breach" );
		
	bridge_breach_trigger = GetEnt( "bridge_breach_trigger", "targetname" );
	bridge_breach_trigger UseTriggerRequireLookAt();
	bridge_breach_trigger SetHintString(&"NY_HARBOR_HINT_USE_TO_BREACH");
	
	bridge_breach_trigger waittill("trigger");
	aud_send_msg("player_trigger_sub_door_breach");
	bridge_breach_trigger delete();
	level.sdv_player_arms hide();//make sure hands are hidden
	
	flag_set("breach_started");
	
	breach_door_col = GetEnt( "breach_door_col", "targetname" );
	
	
	level.breach_charge1 = spawn_anim_model( "breach_charge1", snode.origin );
	level.breach_charge1.animname = "breach_charge1";
	level.breach_charge1 hide();
	
	level.breach_charge2 = spawn_anim_model( "breach_charge2", snode.origin );
	level.breach_charge2.animname = "breach_charge2";
	level.breach_charge2 hide();
	
	level.player DisableOffhandWeapons();
	level.player FreezeControls( true );
	maps\_shg_common::SetUpPlayerForAnimations();

	//player is in position!!!
	thread battlechatter_off( "allies" );
	thread battlechatter_off( "axis" );
	level.player disableWeapons();
	level.player waittill( "weapon_change" );
	thread breach_setup_player();
	breach_door_col ConnectPaths();
	breach_door_col Delete();
	snode anim_first_frame_solo( level.sdv_player_arms, "ny_harbor_door_breach" );
	level.player playerlinktoblend( level.sdv_player_arms, "tag_player", 0.2 );
	wait( .2 );	
	//make sure everything needed is visible
	
	charge show();	
	clicker1 show();	
	clicker2 show();	
	
	//get all things in the scene set up with their animnames
	charge.animname = "door_charge";
	charge setanimtree();
	
	clicker1.animname = "breach_detonator1";
	clicker1 setanimtree();	
	
	clicker2.animname = "breach_detonator2";
	clicker2 setanimtree ();	
			
	spawner = getent("bridge_breach_guy1", "targetname"); 
	
	hit_by_door_guy = spawner spawn_ai(true);
	hit_by_door_guy gun_remove();
	hit_by_door_guy = maps\_vehicle_aianim::convert_guy_to_drone( hit_by_door_guy );
	hit_by_door_guy notsolid();
	hit_by_door_guy.animname = "generic";
	
	flag_set("start_bridge_breach");
	
	snode notify( "end_idle" );
	guys = [ level.sandman, charge, level.breach_door, clicker1, clicker2, level.sdv_player_arms, hit_by_door_guy, level.breach_charge1, level.breach_charge2 ];
	level.sdv_player_arms delaycall(.1, ::show);
	snode anim_single( guys, "ny_harbor_door_breach" );
	level.player thread breach_top_off_weapon();	
	flag_wait("door_blown");
	aud_send_msg("bridge_breach");
	//thread breach_sandman_enter_room();
	level.sdv_player_arms hide();
	//wait( .4 );
	level.player enableWeapons();
	level.player FreezeControls( false );
	
	wait(1);

	level.player unlink();
	
	thread breach_sandman_enter_room();

	flag_wait( "breach_done" );
	thread breach_cleanup_player();
	
}

breach_retreat_and_delete( angle )
{
	self endon( "death" );
	volume = getent( "vol_breach_enemies_retreat", "targetname" );
	self.awareness = 1;
	//self disable_awareness();
	self disable_cqbwalk();
	self SetGoalVolumeAuto( volume );
	while( within_fov_of_players( self.origin, angle ) )
	{
		wait( RandomFloatRange( 0.05, .3) );
	}
	self delete();
}

breach_sandman_enter_room()
{
	level.sandman enable_ai_color();
	sandman_color_trigger = getent( "breach_sandman_enter_room", "targetname" );
	sandman_color_trigger notify( "trigger" );
}

breach_setup_player()
{
	level.player EnableInvulnerability();
	level.player DisableWeaponSwitch();
	level.player DisableOffhandWeapons();
	level.player AllowCrouch( false );
	level.player AllowProne( false );
	level.player AllowSprint( false );
	level.player AllowJump( false );
	maps\ny_harbor_fx::door_breach_vision_change();
	maps\ny_harbor_fx::door_breach_flash_vfx();
	maps\ny_harbor_fx::door_breach_blur();
}

breach_cleanup_player()
{
	level.player DisableInvulnerability();
	level.player EnableWeaponSwitch();
	level.player EnableOffhandWeapons();
	level.player AllowCrouch( true );
	level.player AllowProne( true );
	level.player AllowSprint( true );
	level.player AllowJump( true );
}

blow_door(guy)
{
	flag_set("door_blown");
	
	level.breach_door SetModel( "ny_harbor_sub_pressuredoor_bridge_destroyed" );
	origin = level.breach_door GetTagOrigin("hinge");
	angles = level.breach_door GetTagAngles("hinge");
	f = AnglesToForward( angles );
	r = AnglesToRight( angles );
	u = AnglesToUp( angles );
	offset = (-28,-8,-12);
	origin = origin + f*offset[0] + r*offset[1] + u*offset[2];
	level.breach_destroyed_door = spawn("script_model", origin);
	level.breach_destroyed_door SetModel( "ny_harbor_sub_pressuredoor_bridge_destroyed_door" );
	level.breach_destroyed_door.angles = angles;
	level.breach_destroyed_door linkto( level.breach_door, "hinge" );
	level.breach_door HidePart("hinge");
	level.breach_door HidePart("handle");
	
	clicker1 = getent("detonator_1", "targetname");
	clicker1 delete();
	
	clicker2 = getent("detonator_2", "targetname");
	clicker2 delete();
	
	charge = getent("mil_frame_charge", "targetname");
	charge delete();
	
	level.breach_charge1 delete();
	level.breach_charge2 delete();
	
	thread maps\ny_harbor_fx::door_breach_vfx();
	
		
	thread captain_animation();
	thread breach_enemy_1();
	thread breach_enemy_2();
	thread breach_enemy_3();
}

breach_slow_down(guy)
{
	//wait .65;//.5
	thread slowmo_begins();

}

breach_top_off_weapon( weapon )
{
	weapon = self GetCurrentWeapon();
	// if we're on easy/normal, make sure we have at least one magazine's worth of ammo for the active weapon
	if ( self should_topoff_breach_weapon() )
	{
		clipSize = WeaponClipSize( weapon );
		if ( self GetWeaponAmmoClip( weapon ) < clipSize )
			self SetWeaponAmmoClip( weapon, clipSize );
	}	
}

should_topoff_breach_weapon()
{
	if ( level.gameskill > 1 )
	{
		return false;
	}

	return true;
}

show_charge_1( guy )
{
	level.breach_charge1 show();
}

detach_charge_1( guy )
{
	//nothing for now
}

show_charge_2( guy )
{
	level.breach_charge2 show();
}

detach_charge_2( guy )
{
	//nothing for now
}

slowmo_begins( rig )
{
	aud_send_msg("door_breach_slowmo_start");
	level.slomobreachduration = 3.5;
	slomoLerpTime_in = 0.5;
	slomoLerpTime_out = 0.75;
	slomobreachplayerspeed = 0.2;
	
	if ( ( IsDefined( level.breaching ) ) && ( level.breaching == true ) )
	{
		return;
	}
	level.breaching = true;
	flag_set( "breaching_on" );

	level notify( "slowmo_go" );
	level endon( "slowmo_go" );

	
	if ( IsDefined( level.slomobreachplayerspeed ) )
	{
		slomobreachplayerspeed = level.slomobreachplayerspeed;
	}

	player = level.player;
	/*
	other_player = undefined;
	if ( is_coop() )
		other_player = get_other_player( player );
*/
	player thread play_sound_on_entity( "slomo_whoosh" );
	player thread player_heartbeat();

	//thread slomo_breach_vision_change( ( slomoLerpTime_in * 2 ), ( slomoLerpTime_out / 2 ) );

	//thread slomo_difficulty_dvars();
	flag_clear( "can_save" );
	//slowmo_start();
	
	//player thread set_breaching_variable();

	player AllowMelee( false ); ///melee is useless and causes bugs during slomo
	
	
	slowmo_setspeed_slow( 0.25 );
	slowmo_setlerptime_in( slomoLerpTime_in );
	slowmo_lerp_in();
	
	player SetMoveSpeedScale( slomobreachplayerspeed );


	startTime = GetTime();
	endTime = startTime + ( level.slomobreachduration * 1000 );

	player thread catch_weapon_switch();
	player thread catch_mission_failed();


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
		
		if ( level.breachEnemies_active <= 0 )
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
		if ( player.breach_missionfailed )
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

	slowmo_end();
	aud_send_msg("door_breach_slowmo_end");
	flag_set( "can_save" );
	
	level.player_one_already_breached = undefined;
	
	player slowmo_player_cleanup();
	/*if ( IsDefined( other_player ) )
		other_player slowmo_player_cleanup();*/

	level notify( "slomo_breach_over" );
	level.breaching = false;
	flag_clear( "breaching_on" );
	flag_set( "breach_done" );
	setsaveddvar( "objectiveHide", false );
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

slowmo_player_cleanup()
{
	AssertEx( IsPlayer( self ), "slowmo_player_cleanup() called on a non-player." );

	if ( IsDefined( level.playerSpeed ) )
		self SetMoveSpeedScale( level.playerSpeed );
	else
		self SetMoveSpeedScale( 1 );
}


breach_enemy_track_status( enemy, wait_for_damage )
{
	level.breachEnemies_active++;

	ent = SpawnStruct();
	ent.enemy = enemy;

	ent thread breach_enemy_waitfor_death( enemy );
	ent thread breach_enemy_waitfor_death_counter( enemy );
	ent thread breach_enemy_catch_exceptions( enemy );
	ent thread breach_enemy_waitfor_breach_ending();
	if( isdefined( wait_for_damage ) )
	{
		ent thread breach_enemy_waitfor_damage( enemy );
	}

	ent waittill( "breach_status_change", status );

	level.breachEnemies_active--;

	ent = undefined;
}


breach_enemy_waitfor_damage( enemy )
{
	self endon( "breach_status_change" );

	enemy waittill( "damage" );

	self notify( "breach_status_change", "death" );
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
			flag_set( "bridge_breach_all_enemies_dead" );

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

breach_enemy_monitor_dead()
{
	while( !flag( "bridge_breach_all_enemies_dead" )  )
	{
		
		
		wait( .05 );
	}
}

breach_sandman_take_keys()
{
	flag_wait( "bridge_breach_all_enemies_dead" );
	flag_wait("start_end_scene");
	snode = getent("bridge_breach_loc","targetname");	
	//get into position for the event
	snode anim_generic_reach(level.sandman, "ny_harbor_paried_takedown_sandman_start");
	flag_set("vo_sub_interior_6");
	
	snode anim_generic(level.sandman, "ny_harbor_paried_takedown_sandman_start");
	aud_send_msg("aud_start_sandman_takes_key");
	level.sub_captain.animname = "generic";
	guys = [level.sandman, level.sub_captain];
	snode thread anim_single_solo( level.sub_captain, "ny_harbor_captain_search_flip_over" );
	snode anim_single_solo( level.sandman, "ny_harbor_captain_search_flip_over" );
	snode anim_single_solo( level.sandman, "ny_harbor_captain_search_flip_over_b" );
	level notify("start_missilekey");
	snode anim_single_solo( level.sandman, "ny_harbor_captain_search_flip_over_c" );
	level.sub_captain = undefined;
	
	flag_set( "sub_control_room_key_scene_ready" );
	//missile turn key sequence
	
}

controls_scene()
{
	level.player endon ( "death" );
	
	org = getent("bridge_breach_loc", "targetname");
	
	missile_key_panel = spawn_anim_model( "missile_key_panel" );
	level.missile_key_panel = missile_key_panel;
	org anim_first_frame_solo( level.missile_key_panel, "sub_turn_key" );
	level.missile_key_panel showpart( "tag_lighton" );
	
	missile_key_panel_box = spawn_anim_model( "missile_key_panel_box" );
	level.missile_key_panel_box = missile_key_panel_box;
	org anim_first_frame_solo( level.missile_key_panel_box, "sub_turn_key" );
	level.missile_key_panel_box hidepart( "tag_lighton" );
	
	flag_wait( "sub_control_room_key_scene_ready" );
	
	org thread anim_generic_loop(level.sandman, "sub_turn_key_idle", "stop_loop");
	aud_send_msg("aud_prime_missilekeytoss");

	flag_wait( "sub_control_room_player_to_controls" );
	control_panel = getent( "sub_control_key_panel_main", "targetname" );
	control_panel glow();
	missile_key_panel glow();
	missile_key_panel_box harbor_glow();

	control_panel_trigger = GetEnt( "sub_control_room_player_use", "targetname" );
	control_panel_trigger UseTriggerRequireLookAt();
	control_panel_trigger SetHintString(&"NY_HARBOR_HINT_USE");
	
	control_panel_trigger waittill("trigger");
	control_panel_trigger delete();

	thread return_player_body_if_death();

	control_panel stopglow();
	missile_key_panel stopglow();
	missile_key_panel_box harbor_stop_glow();

	flag_set( "player_at_controls" );
	
	flag_set( "vo_overlord_dialogue" );
	
	level.player DisableOffhandWeapons();
	level.player FreezeControls( true );
	maps\_shg_common::SetUpPlayerForAnimations();
	
	//turn key scene
	level.player disableWeapons();
	
	org anim_first_frame_solo( level.sdv_player_arms, "sub_turn_key" );
	
	link_time = 0.3;
	level.player playerlinktoblend( level.sdv_player_arms, "tag_player", link_time );
	
	wait( link_time );
	level.sdv_player_arms Show();
	
	player_key = spawn_anim_model( "missile_key_player", org.origin );
	sandman_key = spawn_anim_model( "missile_key_sandman", org.origin );
	
	org notify( "stop_loop" );
	guys = [ level.sdv_player_arms, level.sandman, sandman_key, player_key, missile_key_panel_box, missile_key_panel ];
	thread vo_sandman_count_down( level.sandman );
	org anim_single( guys, "sub_turn_key" );
	org thread anim_single_solo( level.sandman, "sub_turn_key2" );
	wait( 115/30 );
	level.sdv_player_arms Hide();
	
	maps\_shg_common::SetUpPlayerForGamePlay();
	level.player enableWeapons();
	level.player FreezeControls( false );
	level.player unlink();
	
	sandman_key Delete();
	player_key Delete();
	
	wait( 52/30 );
	flag_set( "sub_control_room_sandman_exit" );
	
	//temp = getstruct( "temp_move_player_out_of_geo", "targetname" );
	//level.player lerp_player_view_to_position( temp.origin, level.player.angles, .5 );
	
	flag_wait("vo_bridge_is_done");
	
	autosave_by_name( "control_room" );
	
	flag_wait("start_zodiac");
	
	level.missile_key_panel Delete();
	level.missile_key_panel_box Delete();

}

return_player_body_if_death()
{
	level.player waittill ( "death" );
	level.sdv_player_arms hide();
	maps\_shg_common::SetUpPlayerForGamePlay();
	level.player enableWeapons();
	level.player FreezeControls( false );
	level.player unlink();
}

harbor_glow( model )
{
	if ( IsDefined( self.non_glow_model ) )
		return;

	self.non_glow_model = self.model;

	if ( !isdefined( model ) )
		model = self.model + "_obj";
	self SetModel( model );
	self hidepart( "tag_lighton" );
}

harbor_stop_glow( model )
{
	if ( !isdefined( self.non_glow_model ) )
		return;

	self SetModel( self.non_glow_model );
	self hidepart( "tag_lighton" );
	self.non_glow_model = undefined;
}

handle_death_anim_complete()
{
	self notify("death_anim_complete");
}

captain_animation()
{
	cSpawn = getent( "spawn_sub_captain", "targetname" );
	level.sub_captain = cSpawn spawn_ai( true );
	level.sub_captain gun_remove();
	
	thread breach_enemy_track_status( level.sub_captain, true );
	level.sub_captain.ignoreall = true;
	level.sub_captain thread magic_bullet_shield();
	level.sub_captain thread sub_captain_force_kill();
	//get into position
	anim_ent = getent("bridge_breach_loc","targetname");
	anim_ent thread anim_generic( level.sub_captain, "ny_harbor_paried_takedown_captain_start" );
	
	level.sub_captain waittill( "damage", amount, attacker, direction, position, damage_type );
	
	if ( IsDefined( position ) && IsDefined( damage_type ) )
	{
		if ( damage_type == "MOD_PISTOL_BULLET" ||
			 damage_type == "MOD_RIFLE_BULLET" || 
			 damage_type == "MOD_EXPLOSIVE_BULLET" )
		{
			PlayFx( getfx( "headshot" ), position );
		}
	}
	anim_ent anim_generic( level.sub_captain, "ny_harbor_paried_takedown_captain_die" );
	level.sub_captain stop_magic_bullet_shield();
	level.sub_captain = level.sub_captain dummy_keep_pose( anim_ent, "ny_harbor_paried_takedown_captain_dead_1" );
	aud_send_msg("aud_prime_sandman_takes_key");
	flag_set("start_end_scene");
}

sub_captain_force_kill(){
	self endon( "damage" );
	wait( 3 );
	org = level.sandman getTagOrigin( "tag_inhand" );
	magicbullet( "mp5_silencer_reflex_harbor", org, self.origin + ( 0, 0, 32 ), level.player );
	wait( .05 );
	self dodamage( 10, level.sandman.origin, level.sandman );
}

breach_enemy_1()
{
	spawner = getent( "breach_enemy_1", "targetname" );
	guy = spawner spawn_ai( true );
	guy thread breach_enemy_setup_no_ragdoll();
	anim_pos = getstruct( "breach_enemy_loc1", "targetname" );
	anim_pos anim_generic( guy, "breach_enemy_1" );
	
}

control_mbs( time )
{
	self thread magic_bullet_shield();
	wait time;
	self thread stop_magic_bullet_shield();
}

breach_enemy_2()
{
	spawner = getent( "breach_enemy_2_1", "targetname" );
	guy1 = spawner spawn_ai( true );
	guy1 thread breach_enemy_setup_no_ragdoll();
	//guy1 thread control_mbs(1.5);
	guy1.animname = "breacher1";
	
	spawner = getent( "breach_enemy_2_2", "targetname" );
	guy2 = spawner spawn_ai( true );
	guy2 thread breach_enemy_setup_no_ragdoll();
	//guy2 thread control_mbs(2.25);
	guy2.animname = "breacher2";

	guys = make_array( guy1, guy2 );
	
	anim_pos = getstruct( "breach_enemy_loc2", "targetname" );
	anim_pos anim_single( guys, "breach_enemy_2" );
}

breach_enemy_3()
{
	spawner = getent( "breach_enemy_3", "targetname" );
	guy = spawner spawn_ai( true );
	guy thread setup_knife();
	
	guy.animname = "knife_guy";
	guy breach_enemy_setup();
	guy thread slomo_breach_knife_charger();
	guys = [];
	guys[0] = guy;
	
	anim_pos = getstruct( "breach_enemy_loc3", "targetname" );
	delaythread( 0.05, ::anim_set_time, guys, "breach_react_knife_charge", 0.12 );
	anim_pos anim_single_solo( guy, "breach_react_knife_charge" );
}

setup_knife()
{
	level.player endon( "death" );
	level.knife = getent( "weapon_knife", "targetname" );
	org = self getTagOrigin("tag_inhand");
	ang = self getTagAngles("tag_inhand");
	level.knife.origin = org;
	level.knife.angles = ang;
	level.knife linkto( self, "tag_inhand" );
	self waittill( "death" );
	level.knife unlink();
	level.knife PhysicsLaunchClient( level.knife.origin, (0,0,0) );
}

breach_enemy_setup()
{
	level thread breach_enemy_track_status( self, false );
	self thread breach_enemy_ragdoll_on_death();
	
	self.grenadeammo = 0;
	self.allowdeath = true;
	self.health = 10;
	self.baseaccuracy = 5000;
}

breach_enemy_setup_no_ragdoll()
{
	level thread breach_enemy_track_status( self, false );
	
	self.grenadeammo = 0;
	self.allowdeath = true;
	self.health = 10;
	self.baseaccuracy = 5000;
}

slomo_breach_knife_charger()
{
	self endon( "death" );
	self breach_enemy_cancel_ragdoll();
	self thread breach_knife_charger_monitor_death();
	self set_deathanim( "breach_react_knife_charge_death" );
	self waittillmatch( "single anim", "stab" );
	wait( .1 );
	self thread knife_guy_stabs_player();
	self waittill( "finished_breach_start_anim" );
	//self gun_recall();
}

breach_knife_charger_monitor_death()
{
	self waittill( "death" );
	num_attachments = self GetAttachSize();
	for( i = 0; i < num_attachments; i++ )
	{
		if( self GetAttachModelName( i ) == "weapon_parabolic_knife" )
		{
			self detach( "weapon_parabolic_knife", "TAG_INHAND" );
			break;
		}
	}
}

knife_guy_stabs_player()
{
	player = level.player;
	dist = Distance( player.origin, self.origin );
	if ( dist <= 50 )
	{
		player PlayRumbleOnEntity( "grenade_rumble" );
		player thread play_sound_on_entity( "melee_knife_hit_body" );
		player DisableInvulnerability();
		//player EnableDeathShield( false );
		waittillframeend;
		player DoDamage( player.health + 50000, self GetTagOrigin( "tag_weapon_right" ), self );
		player.breach_missionfailed = true;// tells slowmo to stop
	}
}

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

///////////////////////////////////
//////////---- EXIT ----///////////
///////////////////////////////////

sub_exit()
{
	flag_wait( "sub_control_room_sandman_exit" );
	anim_pos = getstruct( "sub_sandman_exit_jump", "targetname" );
	anim_pos anim_first_frame_solo( level.sandman, "sub_exit_jump" );
	
	level.player disableoffhandweapons ();
	
	flag_wait( "sub_exit_player_going_out_hatch" );
	anim_pos anim_single_solo( level.sandman, "sub_exit_jump" );
	flag_set( "start_zodiac" );

	// cleanup all of the corpses	
	 ClearAllCorpses();
}





///////////////////////////////////
//////////---- UTILS ----//////////
///////////////////////////////////

sub_set_player_speed()
{
	flag_wait( "ladder_done" );
	vols = getentarray( "sub_player_slow_vol", "targetname" );
	player_slow_on = false;
	while( !flag( "start_zodiac" ) )
	{
		if( check_volumes( vols ) )
		{
			if( player_slow_on == false )
			{
				player_speed_percent( 50 );
				level.player AllowSprint( false );
				player_slow_on = true;
			}
			wait( .05 );
		}else if( player_slow_on == true )
		{
			player_speed_percent( 75 );
			level.player AllowSprint( true );
			player_slow_on = false;
			wait( .05 );
		}
		else{
			wait( .05 );
		}
	}
}


check_volumes( volume_array )
{
	foreach( volume in volume_array )
	{
		if(level.player isTouching( volume ))
			return true;
		wait(0.05);
	}
	return false;
}


dummy_keep_pose( anim_ent, anim_pose )
{
 dummy = maps\_vehicle_aianim::convert_guy_to_drone( self );
 dummy startUsingHeroOnlyLighting();
 if (isarray(getGenericAnim(anim_pose)))
 	anim_pose = anim_pose + "_nl";	// expects there to be an _nl flavor for looping flavors
 anim_ent anim_generic_first_frame( dummy, anim_pose );
 dummy notsolid();
 return dummy;
}

disable_death_anims()
{
	self.allowdeath = true;
	self.ragdoll_immediate = true;
	//self.skipdeathanim = true;
	//self.noragdoll = true;
	//self.a.nodeath = true;
	
}

enable_death_anims()
{
	if( isalive( self ) )
	{
		self.allowdeath = false;
		self.ragdoll_immediate = undefined;
		//self.a.nodeath = false;
	}
}

kill_no_react()
{
 if ( !isalive( self ) )
  return;
 self.allowDeath = true;
 self.a.nodeath = true;
 self set_battlechatter( false );

 self kill();
}


disable_awareness()
{
	assert(self.awareness);
	self.awareness = 0;
	self.ignoreall = true;
	self.dontmelee = true;
	self.ignoreSuppression = true;
	assert(!isdefined(self.suppressionwait_old));
	self.suppressionwait_old = self.suppressionwait;
	self.suppressionwait = 0;
	self disable_surprise();
	self.IgnoreRandomBulletDamage = true;
  	self disable_bulletwhizbyreaction();
  	self disable_pain();
  	self disable_danger_react();
  	self.grenadeawareness = 0;
  	self.ignoreme = 1;
  	self enable_dontevershoot();
  	self.disableFriendlyFireReaction = true;
}

has_awareness()
{
	return self.awareness;
}

enable_awareness()
{
	assert(!self.awareness);
	self.awareness = 1;
	self.ignoreall = false;
	self.dontmelee = undefined;
	self.ignoreSuppression = false;
	assert(isdefined(self.suppressionwait_old));
	self.suppressionwait = self.suppressionwait_old;
	self.suppressionwait_old = undefined;
	self enable_surprise();
	self.IgnoreRandomBulletDamage = false;
	self enable_bulletwhizbyreaction();
 	self enable_pain();
 	self enable_danger_react(3);
	self.grenadeawareness = 1;
	self.ignoreme = 0;
	self disable_dontevershoot();
	self.disableFriendlyFireReaction = undefined;
}

manage_external_water_in_sub()
{
	dyn_water_sub = getentarray( "dyn_water_sub", "script_noteworthy" );
	dyn_water_breachpatch_low = getentarray( "dyn_water_breachpatch_low", "script_noteworthy" );
	water_flyout_off = getentarray( "water_flyout_off", "script_noteworthy" );
	
	flag_wait( "ladder_done" );
	HideShowEnts( dyn_water_sub, true );
	HideShowEnts( dyn_water_breachpatch_low, true );
	HideShowEnts( water_flyout_off, true );
	
	flag_wait( "sub_exit_player_going_out_hatch" );
	HideShowEnts( dyn_water_sub, false );
	HideShowEnts( dyn_water_breachpatch_low, false );
	HideShowEnts( water_flyout_off, false );
}

backtrack_fail()
{
	level endon( "get_on_zodiac" );
	flag_wait( "player_sub_backtrack" );
	
	SetDvar( "ui_deadquote", "@NY_HARBOR_FAIL_SUB_DECK_ZODIAC" );
	missionFailedWrapper();
}

introscreen_generic_fade_out( shader, pause_time, fade_in_time, fade_out_time )
{
	if ( !isdefined( fade_in_time ) )
		fade_in_time = 1.5;

	introblack = NewHudElem();
	introblack.x = 0;
	introblack.y = 0;
	introblack.horzAlign = "fullscreen";
	introblack.vertAlign = "fullscreen";
	introblack.foreground = true;
	introblack SetShader( shader, 640, 480 );

	if ( IsDefined( fade_out_time ) && fade_out_time > 0 )
	{
		introblack.alpha = 0;
		introblack FadeOverTime( fade_out_time );
		introblack.alpha = 1;
		wait( fade_out_time );
	}
	
	wait pause_time;

	if( isDefined( fade_in_time ) && fade_in_time > 0 )
	{
		introblack.alpha = 1;
		introblack FadeOverTime( fade_in_time );
		introblack.alpha = 0;
		wait( fade_in_time );
	}
	introblack destroy();
}

demo_feed_lines( lines, interval )
{
	keys = GetArrayKeys( lines );
	
	for ( i = 0; i < keys.size; i++ )
	{
		key = keys[ i ];
		time = ( i * interval ) + 1;
		delayThread( time, ::CenterLineThread, lines[ key ], ( lines.size - i - 1 ), interval, key );
	}
}

CenterLineThread( string, size, interval, index_key )
{
	level notify( "new_introscreen_element" );
	
	hudelem = NewHudElem();
	hudelem.x = 0;
	hudelem.y = 0;
	hudelem.alignX = "center";
	hudelem.alignY = "middle";
	hudelem.horzAlign = "center";
	hudelem.vertAlign = "middle_adjustable";
	hudelem.sort = 1;// force to draw after the background
	hudelem.foreground = true;
	hudelem SetText( string );
	hudelem.alpha = 0;
	hudelem FadeOverTime( 0.2 );
	hudelem.alpha = 1;
	
	hudelem.hidewheninmenu = true;
	hudelem.fontScale = 2.4;// was 1.6 and 2.4, larger font change
	hudelem.color = ( 0.8, 1.0, 0.8 );
	hudelem.font = "objective";
	hudelem.glowColor = ( 0.3, 0.6, 0.3 );
	hudelem.glowAlpha = 1;
	duration = Int( ( interval * 1000 ) + 4000 );
	hudelem SetPulseFX( 30, duration, 700 );// something, decay start, decay duration
	
	thread maps\_introscreen::hudelem_destroy( hudelem );
	
	if ( !isdefined( index_key ) )
		return;
	if ( !isstring( index_key ) )
		return;
	if ( index_key != "date" )
		return;
}