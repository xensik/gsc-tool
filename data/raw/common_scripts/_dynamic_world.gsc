#include common_scripts\utility;

/*QUAKED trigger_multiple_dyn_metal_detector (0.12 0.23 1.0) ? AI_AXIS AI_ALLIES AI_NEUTRAL NOTPLAYER VEHICLE TRIGGER_SPAWN TOUCH_ONCE
defaulttexture="flag"
Comments to be added.*/

/*QUAKED trigger_multiple_dyn_creaky_board (0.12 0.23 1.0) ? AI_AXIS AI_ALLIES AI_NEUTRAL NOTPLAYER VEHICLE TRIGGER_SPAWN TOUCH_ONCE
defaulttexture="flag"
Comments to be added.*/

/*QUAKED trigger_multiple_dyn_photo_copier (0.12 0.23 1.0) ? AI_AXIS AI_ALLIES AI_NEUTRAL NOTPLAYER VEHICLE TRIGGER_SPAWN TOUCH_ONCE
defaulttexture="flag"
Comments to be added.*/

/*QUAKED trigger_multiple_dyn_copier_no_light (0.12 0.23 1.0) ? AI_AXIS AI_ALLIES AI_NEUTRAL NOTPLAYER VEHICLE TRIGGER_SPAWN TOUCH_ONCE
defaulttexture="flag"
Comments to be added.*/

/*QUAKED trigger_radius_dyn_motion_light (0.12 0.23 1.0) (-16 -16 -16) (16 16 16)
Comments to be added.*/

/*QUAKED trigger_radius_dyn_motion_dlight (0.12 0.23 1.0) (-16 -16 -16) (16 16 16)
Comments to be added.*/

/*QUAKED trigger_multiple_dog_bark (0.12 0.23 1.0) ? AI_AXIS AI_ALLIES AI_NEUTRAL NOTPLAYER VEHICLE TRIGGER_SPAWN TOUCH_ONCE
Comments to be added.*/

/*QUAKED trigger_radius_bird_startle (0.12 0.23 1.0) (-16 -16 -16) (16 16 16)
Comments to be added.*/

/*QUAKED trigger_multiple_dyn_motion_light (0.12 0.23 1.0) ? AI_AXIS AI_ALLIES AI_NEUTRAL NOTPLAYER VEHICLE TRIGGER_SPAWN TOUCH_ONCE
defaulttexture="flag"
Comments to be added.*/

/*QUAKED trigger_multiple_dyn_door (0.12 0.23 1.0) ? AI_AXIS AI_ALLIES AI_NEUTRAL NOTPLAYER VEHICLE TRIGGER_SPAWN TOUCH_ONCE
defaulttexture="flag"
Comments to be added.*/

/*QUAKED trigger_multiple_freefall (0.12 0.23 1.0) ? AI_AXIS AI_ALLIES AI_NEUTRAL NOTPLAYER VEHICLE TRIGGER_SPAWN TOUCH_ONCE
defaulttexture="flag"
Player free falling with animation and screaming of doom.*/

// Crouch Speed 5.7-6.0
// Run Speed 8.7-9.2
// Sprint Speed 13.0-14.0


// ========================= Constants ==========================

// Vending Machine
CONST_vending_machine_health	 = 400;
CONST_soda_pop_time				 = 0.2;		// seconds
CONST_soda_count 				 = 12;		// number of soda per machine
CONST_soda_launch_force			 = 1000;		// soda shoot out force
CONST_soda_random_factor		 = 0.3;		// in percentage 0.2 = 20%
CONST_soda_splash_dmg_scaler	 = 3;		// splash damage multiplier

// Metal Detector
CONST_alarm_tolerance 			 = 0;		// number of alarm sounds before silenced, 0 disables silencing
CONST_alarm_interval			 = 7;		// alarm interval time in seconds
CONST_alarm_interval_sp			 = 2;		// alarm interval time in seconds for single player

// Civilian Jet
CONST_jet_speed					 = 2000;		// jet while landing is 130 - 160mph( 2292inch / sec - 2820inch / sec ), emergency landing is 110mph
CONST_jet_extend				 = 20000;	// units, each jet and flyto origin will extend from each other by

init()
{

	//rotate fan blades in mp_highrise
	array_thread( getEntArray( "com_wall_fan_blade_rotate_slow", "targetname" ), ::fan_blade_rotate, "veryslow" );
	array_thread( getEntArray( "com_wall_fan_blade_rotate", "targetname" ), ::fan_blade_rotate, "slow" );
	array_thread( getEntArray( "com_wall_fan_blade_rotate_fast", "targetname" ), ::fan_blade_rotate, "fast" );

	trigger_classes = [];
	trigger_classes[ "trigger_multiple_dyn_metal_detector" ] = ::metal_detector;
	trigger_classes[ "trigger_multiple_dyn_creaky_board" ] = ::creaky_board;
	trigger_classes[ "trigger_multiple_dyn_photo_copier" ] = ::photo_copier;
	trigger_classes[ "trigger_multiple_dyn_copier_no_light" ] = ::photo_copier_no_light;
	trigger_classes[ "trigger_radius_motion_light" ] = ::motion_light;
	trigger_classes[ "trigger_radius_dyn_motion_dlight" ] = ::outdoor_motion_dlight;
	trigger_classes[ "trigger_multiple_dog_bark" ] = ::dog_bark;
	trigger_classes[ "trigger_radius_bird_startle" ] = ::bird_startle;
	trigger_classes[ "trigger_multiple_dyn_motion_light" ] = ::motion_light;
	trigger_classes[ "trigger_multiple_dyn_door" ] = ::trigger_door;
	//trigger_classes[ "trigger_multiple_freefall" ] = ::freefall;

	player_init();

	foreach ( classname, function in trigger_classes )
	{
		triggers = getEntArray( classname, "classname" );
		array_thread( triggers, ::triggerTouchThink );
		array_thread( triggers, function );
	}

	array_thread( getEntArray( "vending_machine", "targetname" ), ::vending_machine );
	array_thread( getEntArray( "toggle", "targetname" ), ::use_toggle );

	level thread onPlayerConnect();

	civilian_jet = getEnt( "civilian_jet_origin", "targetname" );
	if ( isDefined( civilian_jet ) )
		civilian_jet thread civilian_jet_flyby();
}

onPlayerConnect()
{
	for ( ;; )
	{
		level waittill( "connecting", player );
		player thread movementTracker();
	}
}

player_init()
{
	if ( isSP() )
	{
		foreach ( player in level.players )
		{
			player.touchTriggers = [];
			player thread movementTracker();
		}
	}
}

ai_init()
{
	/*if ( !isdefined( level.registeredAI ) )
		level.registeredAI = [];
		
	level.registeredAI[ level.registeredAI.size ] = self;
	*/

	// self is AI
	self.touchTriggers = [];
	self thread movementTracker();
}


// ================================================================================ //
// 									Civilian Jet 									//
// ================================================================================ //

civilian_jet_flyby()
{
	level endon( "game_ended" );

	self jet_init();

	level waittill( "prematch_over" );

	while ( 1 )
	{
		self thread jet_timer();
		self waittill( "start_flyby" );

		self thread jet_flyby();
		self waittill( "flyby_done" );

		self jet_reset();
	}
}


jet_init()
{
	// move jet plane and flyto origin out of the map and hide on level load
	self.jet_parts 			 = getentarray( self.target, "targetname" );
	self.jet_flyto 			 = getent( "civilian_jet_flyto", "targetname" );
	self.engine_fxs 		 = getentarray( "engine_fx", "targetname" );
	self.flash_fxs			 = getentarray( "flash_fx", "targetname" );

	self.jet_engine_fx		 = loadfx( "fire/jet_afterburner" );
	self.jet_flash_fx_red	 = loadfx( "misc/aircraft_light_wingtip_red" );
	self.jet_flash_fx_green	 = loadfx( "misc/aircraft_light_wingtip_green" );
	self.jet_flash_fx_blink	 = loadfx( "misc/aircraft_light_red_blink" );

	level.civilianJetFlyBy 	 = undefined;		// priority with air supremacies

	assertex( isdefined( self.jet_parts ), 		"Missing cilivian jet model" );
	assertex( isdefined( self.jet_flyto ), 		"Missing cilivian jet flyto script_origin: civilian_jet_flyto" );
	assertex( isdefined( self.engine_fxs ), 	"Missing cilivian jet engine fxs script_origins: engine_fx" );
	assertex( isdefined( self.flash_fxs ), 		"Missing cilivian jet signal light script_origins: flash_fxs" );

	// extending vector to place jet and flyto origin outside sky box
	negative_vec = ( VectorNormalize( self.origin - self.jet_flyto.origin ) * CONST_jet_extend );

	// extend flyto origin
	self.jet_flyto.origin -= negative_vec;

	// extend jet
	self.origin += negative_vec;
	foreach ( part in self.jet_parts )
	{
		part.origin += negative_vec;
		part.old_origin = part.origin;
		part hide();
	}

	// extend jet's engine fx origins
	foreach ( engine_fx in self.engine_fxs )
		engine_fx.origin += negative_vec;

	foreach ( flash_fx in self.flash_fxs )
		flash_fx.origin += negative_vec;

	// -------------- flight time and vector calculation -------------
	jet_origin 				 = self.origin;// origin is the nose of the jet
	jet_flyto_pos 			 = self.jet_flyto.origin;
	self.jet_fly_vec 		 = jet_flyto_pos - jet_origin;

	jet_speed 				 = CONST_jet_speed;
	jet_flight_dist 		 = abs( distance( jet_origin, jet_flyto_pos ) );
	self.jet_flight_time 	 = jet_flight_dist / jet_speed;
}


jet_reset()
{
	foreach ( part in self.jet_parts )
	{
		part.origin = part.old_origin;
		part hide();
	}
}


jet_timer()
{
	level endon( "game_ended" );

	match_timelimit	 = getTimeInterval();
	assert( isdefined( match_timelimit ) );
	timelimit = max( 10, match_timelimit );
	timelimit = min( timelimit, 100 );

	if ( getdvar( "jet_flyby_timer" ) != "" )
		level.civilianJetFlyBy_timer = 5 + getdvarint( "jet_flyby_timer" );
	else
		level.civilianJetFlyBy_timer = ( 0.25 + randomFloatRange( 0.3, 0.7 ) ) * 60 * timeLimit; 	// seconds into the match when jet flys by

	wait level.civilianJetFlyBy_timer;

	// wait till all the airborne kill streaks are done
	while ( isDefined( level.airstrikeInProgress ) || isDefined( level.ac130player ) || isDefined( level.chopper ) || isDefined( level.remoteMissileInProgress ) )
		wait 0.05;

	// start flyby
	self notify( "start_flyby" );

	// blocks out all airborne kill streaks
	level.civilianJetFlyBy = true;
	self waittill( "flyby_done" );
	level.civilianJetFlyBy = undefined;
}

getTimeInterval()
{
	if ( isSP() )
		return 10.0;

	if ( isDefined( game[ "status" ] ) && game[ "status" ] == "overtime" )
		return 1.0;
	else
		return getWatchedDvar( "timelimit" );
}

getWatchedDvar( dvarString )
{
	dvarString = "scr_" + level.gameType + "_" + dvarString;
	
	if ( isDefined( level.overrideWatchDvars ) && isDefined( level.overrideWatchDvars[dvarString] ) )
	{
		return level.overrideWatchDvars[dvarString];
	}	
	
	return( level.watchDvars[ dvarString ].value );
}


jet_flyby()
{
	// show plane
	foreach ( part in self.jet_parts )
		part show();

	engine_fx_array = [];
	flash_fx_array = [];

	foreach ( engine_fx in self.engine_fxs )
	{
		engine_fx_ent = spawn( "script_model", engine_fx.origin );
		engine_fx_ent setModel( "tag_origin" );
		engine_fx_ent.angles = engine_fx.angles;
		engine_fx_array [ engine_fx_array.size ] = engine_fx_ent;
	}

	foreach ( flash_fx in self.flash_fxs )
	{
		flash_fx_ent = spawn( "script_model", flash_fx.origin );
		flash_fx_ent setModel( "tag_origin" );
		flash_fx_ent.color = flash_fx.script_noteworthy;
		flash_fx_ent.angles = flash_fx.angles;
		flash_fx_array [ flash_fx_array.size ] = flash_fx_ent;
	}

	assertex( isdefined( level.mapcenter ), "Calling for civilian jet flyby when level.mapcenter is not yet defined." );
	self thread jet_planeSound( self.jet_parts[ 0 ], level.mapcenter );

	wait 0.05;

	// play engine fx on fx ents
	foreach ( engine_fx_ent in engine_fx_array )
		playfxontag( self.jet_engine_fx, engine_fx_ent, "tag_origin" );

	// play flash fx on fx ents
	foreach ( flash_fx_ent in flash_fx_array )
	{
		if ( isdefined( flash_fx_ent.color ) && flash_fx_ent.color == "blink" )
			playfxontag( self.jet_flash_fx_blink, flash_fx_ent, "tag_origin" );
		else if ( isdefined( flash_fx_ent.color ) && flash_fx_ent.color == "red" )
			playfxontag( self.jet_flash_fx_red, flash_fx_ent, "tag_origin" );
		else
			playfxontag( self.jet_flash_fx_green, flash_fx_ent, "tag_origin" );
	}

	// move plane
	foreach ( part in self.jet_parts )
		part moveTo( part.origin + self.jet_fly_vec, self.jet_flight_time );

	// move fx ents
	foreach ( engine_fx_ent in engine_fx_array )
		engine_fx_ent moveTo( engine_fx_ent.origin + self.jet_fly_vec, self.jet_flight_time );
	foreach ( flash_fx_ent in flash_fx_array )
		flash_fx_ent moveTo( flash_fx_ent.origin + self.jet_fly_vec, self.jet_flight_time );

	wait( self.jet_flight_time + 1 );

	// delete fxs
	foreach ( engine_fx_ent in engine_fx_array )
		engine_fx_ent delete();
	foreach ( flash_fx_ent in flash_fx_array )
		flash_fx_ent delete();

	self notify( "flyby_done" );
}


jet_planeSound( plane, bombsite )
{
	plane thread playsound_loop_on_ent( "veh_mig29_dist_loop" );
	while ( !targetisclose( plane, bombsite ) )
		wait .05;

	plane thread playsound_loop_on_ent( "veh_mig29_close_loop" );
	while ( targetisinfront( plane, bombsite ) )
		wait .05;
	wait .5;

	plane thread playsound_float( "veh_mig29_sonic_boom" );
	while ( targetisclose( plane, bombsite ) )
		wait .05;

	plane notify( "stop sound" + "veh_mig29_close_loop" );
	self waittill( "flyby_done" );

	plane notify( "stop sound" + "veh_mig29_dist_loop" );
}


playsound_float( alias, origin, master )
{
	org = spawn( "script_origin", ( 0, 0, 1 ) );
	org hide();
	if ( !isdefined( origin ) )
		origin = self.origin;
	org.origin = origin;
	if ( isdefined( master ) && master )
		org playsoundasmaster( alias );
	else
		org playsound( alias );
	wait( 10.0 );
	org delete();
}


playsound_loop_on_ent( alias, offset )
{
	org = spawn( "script_origin", ( 0, 0, 0 ) );
	org hide();
	org endon( "death" );
	thread delete_on_death( org );
	if ( isdefined( offset ) )
	{
		org.origin = self.origin + offset;
		org.angles = self.angles;
		org linkto( self );
	}
	else
	{
		org.origin = self.origin;
		org.angles = self.angles;
		org linkto( self );
	}
//	org endon ("death");
	org playloopsound( alias );
//	println ("playing loop sound ", alias," on entity at origin ", self.origin, " at ORIGIN ", org.origin);
	self waittill( "stop sound" + alias );
	org stoploopsound( alias );
	org delete();
}

targetisinfront( other, target )
{
	forwardvec 	 = anglestoforward( flat_angle( other.angles ) );
	normalvec 	 = vectorNormalize( flat_origin( target ) - other.origin );
	dot 		 = vectordot( forwardvec, normalvec );

	if ( dot > 0 )
		return true;
	else
		return false;
}

targetisclose( other, target )
{
	infront = targetisinfront( other, target );

	if ( infront )
		dir = 1;
	else
		dir = -1;

	a 		 = flat_origin( other.origin );
	b 		 = a + ( anglestoforward( flat_angle( other.angles ) ) * ( dir * 100000 ) );
	point 	 = pointOnSegmentNearestToPoint( a, b, target );
	dist 	 = distance( a, point );

	if ( dist < 3000 )
		return true;
	else
		return false;
}


// ================================================================================ //
// 									Vending Machine									//
// ================================================================================ //

vending_machine()
{
	level endon( "game_ended" );
	self endon( "death" );

	// self is use trigger
	self SetCursorHint( "HINT_ACTIVATE" );

	self.vm_normal 		 = getent( self.target, "targetname" );
	assertex( isdefined( self.vm_normal ), "Vending machine use trigger is missing target to the normal vending machine script_model" );
	vm_soda_start 		 = getent( self.vm_normal.target, "targetname" );
	assertex( isdefined( vm_soda_start ), "Vending machine normal script_model is missing target to the start-soda can script_model" );
	vm_soda_stop 		 = getent( vm_soda_start.target, "targetname" );
	assertex( isdefined( vm_soda_start ), "Start-soda can script_model is missing target to the end-soda can script_model" );
	vm_launch_from = getent( vm_soda_stop.target, "targetname" );
	assertex( isdefined( vm_launch_from ), "End-soda can script_model is missing target to the physics launch-from script_origin" );
	self.vm_launch_from	 = vm_launch_from.origin;
	vm_launch_to 	 = getent( vm_launch_from.target, "targetname" );
	assertex( isdefined( vm_launch_to ), "launch-from can script_origin is missing target to the physics launch-to script_origin" );
	self.vm_launch_to 	 = vm_launch_to.origin;

	if ( isdefined( vm_launch_to.target ) )
		self.vm_fx_loc	 = getent( vm_launch_to.target, "targetname" ).origin;
		
	//assertex( isdefined( self.vm_launch_to ), "launch-to can script_origin is missing target to the fx location script_origin" );

	self.vm_normal setCanDamage( true );

	self.vm_normal_model 		 = self.vm_normal.model;
	self.vm_damaged_model 		 = self.vm_normal.script_noteworthy;
	self.vm_soda_model 			 = vm_soda_start.model;

	self.vm_soda_start_pos 		 = vm_soda_start.origin;
	self.vm_soda_start_angle 	 = vm_soda_start.angles;
	self.vm_soda_stop_pos 		 = vm_soda_stop.origin;
	self.vm_soda_stop_angle 	 = vm_soda_stop.angles;

	// precache damage model
	precacheModel( self.vm_damaged_model );

	// ride the no longer needed models
	vm_soda_start delete();
	vm_soda_stop delete();
	vm_launch_from delete();
	vm_launch_to delete();

	self.soda_array = [];
	self.soda_count = CONST_soda_count;
	self.soda_slot 	 = undefined;// the soda can thats resting in the slot
	self.hp = CONST_vending_machine_health;

	self thread vending_machine_damage_monitor( self.vm_normal );
	self playloopsound( "vending_machine_hum" );

	while ( 1 )
	{
		self waittill( "trigger", player );
		//level.players[0] iprintln( "used" );

		self playsound( "vending_machine_button_press" );
		if ( !self.soda_count )
			continue;

		// drop a can, and shoot out the previous one if in slot
		if ( isdefined( self.soda_slot ) )
			self soda_can_eject();
		soda_can_drop( spawn_soda() );
		wait 0.05;
	}
}

vending_machine_damage_monitor( vending_machine )
{
	level endon( "game_ended" );

	exp_dmg = "mod_grenade mod_projectile mod_explosive mod_grenade_splash mod_projectile_splash splash";
	sparks_fx = loadfx( "explosions/tv_explosion" );

	while ( 1 )
	{
	    damage = undefined;
	    other = undefined;
	    direction_vec = undefined;
	    P = undefined;
	    type = undefined;
		vending_machine waittill( "damage", damage, other, direction_vec, P, type );

		if ( isdefined( type ) )
		{
			if ( isSubStr( exp_dmg, ToLower( type ) ) )
				damage *= CONST_soda_splash_dmg_scaler;	// multiply explosive dmg

			self.hp -= damage;
			if ( self.hp > 0 )
				continue;
			
			// vending machine is now dead, button usage is disabled
			self notify( "death" );
			
			// disable use trigger
			self.origin += ( 0, 0, 10000 );

			if( !isdefined( self.vm_fx_loc ) )
				playfx_loc = self.vm_normal.origin + ( ( 17, -13, 52 ) - ( -20, 18, 0 ) );
			else
				playfx_loc = self.vm_fx_loc;
				
			playfx( sparks_fx, playfx_loc );

			// when vending machine is explosively damaged, shoots out soda cans
			self.vm_normal setmodel( self.vm_damaged_model );

			while ( self.soda_count > 0 )
			{
				// drop a can, and shoot out the previous one if in slot
				if ( isdefined( self.soda_slot ) )
					self soda_can_eject();
				soda_can_drop( spawn_soda() );
				wait 0.05;
			}

			self stoploopsound( "vending_machine_hum" );
			return;
		}
	}
}

spawn_soda()
{
	soda = spawn( "script_model", self.vm_soda_start_pos );
	soda setmodel( self.vm_soda_model );
	soda.origin = self.vm_soda_start_pos;
	soda.angles = self.vm_soda_start_angle;
	return soda;
}

soda_can_drop( soda )
{
	soda MoveTo( self.vm_soda_stop_pos, CONST_soda_pop_time );
	soda playsound( "vending_machine_soda_drop" );	// soda can drop sound
	wait CONST_soda_pop_time;

	self.soda_slot = soda;
	self.soda_count -- ;
}

soda_can_eject()
{
	self endon( "death" );

	if( isdefined( self.soda_slot.ejected ) && self.soda_slot.ejected == true )
		return;
	
	// physics launch
	force_max = 1;
	force_min = force_max * (1-CONST_soda_launch_force);
	
	random_offset		 = int( 40 * CONST_soda_launch_force );
	random_launch_offset = ( int(random_offset/2), int(random_offset/2), 0 ) - ( randomint( random_offset ), randomint( random_offset ), 0 );
	
	launch_vec 			 = vectorNormalize( self.vm_launch_to - self.vm_launch_from + random_launch_offset );
	launch_force_vec 	 = ( launch_vec * randomfloatrange( force_min, force_max ) );
	
	self.soda_slot PhysicsLaunchClient( self.vm_launch_from , launch_force_vec );
	self.soda_slot.ejected = true;
}

// ================================================================================ //
// 									Free Fall										//
// ================================================================================ //

freefall()
{
	level endon( "game_ended" );

	freefall_weapon = "briefcase_bomb_mp";
	precacheItem( freefall_weapon );

	while ( 1 )
	{
		self waittill( "trigger_enter", player );

		if ( !( player hasWeapon( freefall_weapon ) ) )
		{
			player playsound( "freefall_death" );

			player giveweapon( freefall_weapon );
			player setWeaponAmmoStock( freefall_weapon, 0 );
			player setWeaponAmmoClip( freefall_weapon, 0 );
			player switchToWeapon( freefall_weapon );
		}
	}
}

// ================================================================================ //
// 									Metal Detector 									//
// ================================================================================ //

metal_detector()
{
	// self is trigger: trigger_multiple_dyn_metal_detector

	level endon( "game_ended" );
	assertex( isdefined( self.target ), "trigger_multiple_dyn_metal_detector is missing target damage trigger used for detecting entities other than players" );

	damage_trig = getent( self.target, "targetname" );
	damage_trig EnableGrenadeTouchDamage();

	bound_org_1 = getent( damage_trig.target, "targetname" );
	bound_org_2 = getent( bound_org_1.target, "targetname" );

	assertex( isdefined( bound_org_1 ) && isdefined( bound_org_2 ), "Metal detector missing bound origins for claymore test" );

	detector_1 = getent( bound_org_2.target, "targetname" );
	detector_2 = getent( detector_1.target, "targetname" );

	assertex( isdefined( detector_1 ) && isdefined( detector_2 ), "Recompile the bsp to fix this, metal detector prefab changed." );

	bounds = [];
	bound_x_min = min( bound_org_1.origin[ 0 ], bound_org_2.origin[ 0 ] );	bounds[ 0 ] = bound_x_min;
	bound_x_max = max( bound_org_1.origin[ 0 ], bound_org_2.origin[ 0 ] );	bounds[ 1 ] = bound_x_max;
	bound_y_min = min( bound_org_1.origin[ 1 ], bound_org_2.origin[ 1 ] );	bounds[ 2 ] = bound_y_min;
	bound_y_max = max( bound_org_1.origin[ 1 ], bound_org_2.origin[ 1 ] );	bounds[ 3 ] = bound_y_max;
	bound_z_min = min( bound_org_1.origin[ 2 ], bound_org_2.origin[ 2 ] );	bounds[ 4 ] = bound_z_min;
	bound_z_max = max( bound_org_1.origin[ 2 ], bound_org_2.origin[ 2 ] );	bounds[ 5 ] = bound_z_max;

	bound_org_1 delete();
	bound_org_2 delete();

	if ( !isSP() )
		self.alarm_interval = CONST_alarm_interval;
	else
		self.alarm_interval = CONST_alarm_interval_sp;

	self.alarm_playing = 0;
	self.alarm_annoyance = 0;
	self.tolerance = CONST_alarm_tolerance;

	self thread metal_detector_dmg_monitor( damage_trig );
	self thread metal_detector_touch_monitor();
	self thread metal_detector_weapons( bounds, "weapon_claymore", "weapon_c4" );

	light_pos1 = ( detector_1.origin[ 0 ], detector_1.origin[ 1 ], bound_z_max );
	light_pos2 = ( detector_2.origin[ 0 ], detector_2.origin[ 1 ], bound_z_max );

	//light_pos1 = ( bound_x_min,  bound_y_min, bound_z_max );
	//light_pos2 = ( bound_x_max,  bound_y_max, bound_z_max );	
	md_light = loadfx( "props/metal_detector_light" );

	while ( 1 )
	{
		self waittill_any( "dmg_triggered", "touch_triggered", "weapon_triggered" );
		self thread playsound_and_light( "alarm_metal_detector", md_light, light_pos1, light_pos2 );
	}
}

playsound_and_light( sound, light, light_pos1, light_pos2 )
{
	level endon( "game_ended" );

	if ( !self.alarm_playing )
	{
		self.alarm_playing = 1;
		self thread annoyance_tracker();

		if ( !self.alarm_annoyance )
			self playsound( sound );

		// 1000ms red light fx
		playfx( light, light_pos1 );
		playfx( light, light_pos2 );

		wait self.alarm_interval;
		self.alarm_playing = 0;
	}
}

annoyance_tracker()
{
	level endon( "game_ended" );

	if ( !self.tolerance )
		return;

	interval = self.alarm_interval + 0.15;
	if ( self.tolerance )
		self.tolerance -- ;
	else
		self.alarm_annoyance = 1;

	current_time = gettime();// ms

	alarm_timeout = CONST_alarm_interval;
	if ( isSP() )
		alarm_timeout = CONST_alarm_interval_sp;

	self waittill_any_or_timeout( "dmg_triggered", "touch_triggered", "weapon_triggered", ( alarm_timeout + 2 ) );

	time_delta = ( gettime() - current_time );
	if ( time_delta > ( ( alarm_timeout * 1000 ) + 1150 ) )
	{
		self.alarm_annoyance = 0;
		self.tolerance = CONST_alarm_tolerance;
	}
}

waittill_any_or_timeout( msg1, msg2, msg3, timer )
{
	level endon( "game_ended" );

	self endon( msg1 );
	self endon( msg2 );
	self endon( msg3 );
	wait timer;
}

metal_detector_weapons( bounds, weapon_1, weapon_2 )
{
	level endon( "game_ended" );
	while ( 1 )
	{
		self waittill_weapon_placed();

		all_grenades = getentarray( "grenade", "classname" );
		foreach ( grenade in all_grenades )
		{
			if ( isdefined( grenade.model ) && ( grenade.model == weapon_1 || grenade.model == weapon_2 ) )
			{
				if ( isInBound( grenade, bounds ) )
					self thread weapon_notify_loop( grenade, bounds );
			}
		}
	}
}

waittill_weapon_placed()
{
	level endon( "game_ended" );
	self endon( "dmg_triggered" );
	self waittill( "touch_triggered" );
}

weapon_notify_loop( grenade, bounds )
{
	grenade endon( "death" );

	while ( isInBound( grenade, bounds ) )
	{
		self notify( "weapon_triggered" );
		wait self.alarm_interval;
	}
}

isInBound( ent, bounds )
{
	bound_x_min = bounds[ 0 ]; bound_x_max = bounds[ 1 ];
	bound_y_min = bounds[ 2 ]; bound_y_max = bounds[ 3 ];
	bound_z_min = bounds[ 4 ]; bound_z_max = bounds[ 5 ];

	ent_x = ent.origin[ 0 ];
	ent_y = ent.origin[ 1 ];
	ent_z = ent.origin[ 2 ];

	if ( isInBound_single( ent_x, bound_x_min, bound_x_max ) )
	{
		if ( isInBound_single( ent_y, bound_y_min, bound_y_max ) )
		{
			if ( isInBound_single( ent_z, bound_z_min, bound_z_max ) )
				return true;
		}
	}
	return false;
}

isInBound_single( var, v_min, v_max )
{
	if ( var > v_min && var < v_max )
		return true;
	return false;
}


metal_detector_dmg_monitor( damage_trig )
{
	level endon( "game_ended" );
	while ( 1 )
	{
		damage_trig waittill( "damage", damage, other, direction_vec, P, type );
		if ( isdefined( type ) && alarm_validate_damage( type ) )
			self notify( "dmg_triggered" );
	}
}

metal_detector_touch_monitor()
{
	level endon( "game_ended" );
	while ( 1 )
	{
		self waittill( "trigger_enter" );
		while ( anythingTouchingTrigger( self ) )
		{
			self notify( "touch_triggered" );
			wait self.alarm_interval;
		}
	}
}

alarm_validate_damage( damageType )
{
	//disallowed_dmg = "mod_pistol_bullet mod_rifle_bullet bullet mod_crush mod_grenade_splash mod_projectile_splash splash unknown";
	//disallowed_dmg_array = strtok( disallowed_damage, " " );	

	allowed_dmg = "mod_melee melee mod_grenade mod_projectile mod_explosive mod_impact";
	allowed_dmg_array = strtok( allowed_dmg, " " );

	foreach ( dmg in allowed_dmg_array )
	{
		if ( ToLower( dmg ) == ToLower( damageType ) )
			return true;
	}
	return false;
}


// ================================================================================ //


creaky_board()
{
	level endon( "game_ended" );

	for ( ;; )
	{
		self waittill( "trigger_enter", player );
		player thread do_creak( self );
	}
}


do_creak( trigger )
{
	self endon( "disconnect" );
	self endon( "death" );

	self playSound( "step_walk_plr_woodcreak_on" );

	for ( ;; )
	{
		self waittill( "trigger_leave", leftTrigger );
		if ( trigger != leftTrigger )
			continue;

		self playSound( "step_walk_plr_woodcreak_off" );
		return;
	}
}


motion_light()
{
	level endon( "game_ended" );
	self.moveTracker = true;

	self.lightsOn = false;
	lights = getEntArray( self.target, "targetname" );
	assertEx( lights.size, "ERROR: trigger_ * _motion_light with no targets at " + self.origin );

	precacheModel( "com_two_light_fixture_off" );
	precacheModel( "com_two_light_fixture_on" );

	foreach ( light in lights )
	{
		light.lightRigs = [];
		infoNull = getEnt( light.target, "targetname" );
		if ( !isDefined( infoNull.target ) )
			continue;

		light.lightRigs = getEntArray( infoNull.target, "targetname" );
	}


	for ( ;; )
	{
		self waittill( "trigger_enter" );

		while ( anythingTouchingTrigger( self ) )
		{
			objectMoved = false;
			foreach ( object in self.touchList )
			{
				if ( isDefined( object.distMoved ) && object.distMoved > 5.0 )
					objectMoved = true;
			}

			if ( objectMoved )
			{
				if ( !self.lightsOn )
				{
					self.lightsOn = true;
					lights[ 0 ] playSound( "switch_auto_lights_on" );

					foreach ( light in lights )
					{
						light setLightIntensity( 1.0 );

						if ( isdefined( light.lightRigs ) )
						{
							foreach ( rig in light.lightRigs )
								rig setModel( "com_two_light_fixture_on" );
						}
					}
				}
				self thread motion_light_timeout( lights, 10.0 );
			}

			wait( 0.05 );
		}
	}
}


motion_light_timeout( lights, timeOut )
{
	self notify( "motion_light_timeout" );
	self endon( "motion_light_timeout" );

	wait( timeOut );

	foreach ( light in lights )
	{
		light setLightIntensity( 0 );
		if ( isdefined( light.lightRigs ) )
		{
			foreach ( rig in light.lightRigs )
				rig setModel( "com_two_light_fixture_off" );
		}
	}

	lights[ 0 ] playSound( "switch_auto_lights_off" );

	self.lightsOn = false;
}


outdoor_motion_dlight()
{

	if( !isdefined( level.outdoor_motion_light ) )
	{
			level.outdoor_motion_light = loadFx( "misc/outdoor_motion_light" );
	}
	
	level endon( "game_ended" );
	self.moveTracker = true;

	self.lightsOn = false;
	lightRig = getEnt( self.target, "targetname" );
	assertEx( lightRig.size, "ERROR: trigger_ * _motion_light with no targets at " + self.origin );
	lights = getEntArray( lightRig.target, "targetname" );
	assertEx( lights.size, "ERROR: trigger_ * _motion_light model target with no light targets at " + lightRig.origin );

	precacheModel( "com_two_light_fixture_off" );
	precacheModel( "com_two_light_fixture_on" );

	for ( ;; )
	{
		self waittill( "trigger_enter" );

		while ( anythingTouchingTrigger( self ) )
		{
			objectMoved = false;
			foreach ( object in self.touchList )
			{
				if ( isDefined( object.distMoved ) && object.distMoved > 5.0 )
					objectMoved = true;
			}

			if ( objectMoved )
			{
				if ( !self.lightsOn )
				{
					self.lightsOn = true;
					lightRig playSound( "switch_auto_lights_on" );
					lightRig setModel( "com_two_light_fixture_on" );

					foreach ( light in lights )
					{
						assert( !isDefined( light.lightEnt ) );
						light.lightEnt = spawn( "script_model", light.origin );
						light.lightEnt setModel( "tag_origin" );
						playFxOnTag( level.outdoor_motion_light, light.lightEnt, "tag_origin" );
					}
				}
				self thread outdoor_motion_dlight_timeout( lightRig, lights, 10.0 );
			}

			wait( 0.05 );
		}
	}
}


outdoor_motion_dlight_timeout( lightRig, lights, timeOut )
{
	self notify( "motion_light_timeout" );
	self endon( "motion_light_timeout" );

	wait( timeOut );

	foreach ( light in lights )
	{
		assert( isDefined( light.lightEnt ) );
		light.lightEnt delete();
	}

	lightRig playSound( "switch_auto_lights_off" );
	lightRig setModel( "com_two_light_fixture_off" );

	self.lightsOn = false;
}

dog_bark()
{
	level endon( "game_ended" );
	self.moveTracker = true;

	dogOrigin = getEnt( self.target, "targetname" );
	assertEx( isDefined( dogOrigin ), "ERROR: trigger_multiple_dog_bark with no target at " + self.origin );

	for ( ;; )
	{
		self waittill( "trigger_enter", player );

		while ( anythingTouchingTrigger( self ) )
		{
			maxDistMoved = 0;
			foreach ( object in self.touchList )
			{
				if ( isDefined( object.distMoved ) && object.distMoved > maxDistMoved )
					maxDistMoved = object.distMoved;
			}

			if ( maxDistMoved > 6.0 )
			{
				dogOrigin playSound( "dyn_anml_dog_bark" );
				wait( randomFloatRange( 16 / maxDistMoved, 16 / maxDistMoved + randomFloat( 1.0 ) ) );
			}
			else
			{
				wait( 0.05 );
			}
		}
	}
}


trigger_door()
{
	doorEnt = getEnt( self.target, "targetname" );
	assertEx( isDefined( doorEnt ), "ERROR: trigger_multiple_dyn_door with no door brush at " + self.origin );

	self.doorEnt = doorEnt;
	self.doorAngle = getVectorRightAngle( vectorNormalize( self getOrigin() - doorEnt getOrigin() ) );
	doorEnt.baseYaw = doorEnt.angles[ 1 ];
	openTime = 1.0;

	for ( ;; )
	{
		self waittill( "trigger_enter", player );

		doorEnt thread doorOpen( openTime, self getDoorSide( player ) );

		if ( anythingTouchingTrigger( self ) )
			self waittill( "trigger_empty" );

		wait( 3.0 );

		if ( anythingTouchingTrigger( self ) )
			self waittill( "trigger_empty" );

		doorEnt thread doorClose( openTime );
	}
}


doorOpen( openTime, doorSide )
{
	if ( doorSide )
		self rotateTo( ( 0, self.baseYaw + 90, 1 ), openTime, 0.1, 0.75 );
	else
		self rotateTo( ( 0, self.baseYaw - 90, 1 ), openTime, 0.1, 0.75 );

	self playSound( "door_generic_house_open" );

	wait( openTime + 0.05 );
}


doorClose( openTime )
{
	self rotateTo( ( 0, self.baseYaw, 1 ), openTime );
	self playSound( "door_generic_house_close" );

	wait( openTime + 0.05 );
}

getDoorSide( player )
{
	return( vectorDot( self.doorAngle, vectornormalize( player.origin - self.doorEnt getOrigin() ) ) > 0 );
}


getVectorRightAngle( vDir )
{
	return( vDir[ 1 ], 0 - vDir[ 0 ], vDir[ 2 ] );
}

use_toggle()
{
	if ( self.classname != "trigger_use_touch" )
		return;

	lights = getEntArray( self.target, "targetname" );
	assert( lights.size );

	self.lightsOn = 1;
	foreach ( light in lights )
		light setLightIntensity( 1.5 * self.lightsOn );


	for ( ;; )
	{
		self waittill( "trigger" );

		self.lightsOn = !self.lightsOn;
		if ( self.lightsOn )
		{
			foreach ( light in lights )
				light setLightIntensity( 1.5 );

			self playSound( "switch_auto_lights_on" );
		}
		else
		{
			foreach ( light in lights )
				light setLightIntensity( 0 );

			self playSound( "switch_auto_lights_off" );
		}
	}
}


bird_startle()
{
}


photo_copier_init( trigger )
{
	// self is trigger
	
	self.copier = get_photo_copier( trigger );
	assertex( self.copier.classname == "script_model", "Photocopier at " + trigger.origin + " doesn't target a photo copier" );

	copy_bar = getent( self.copier.target, "targetname" );
	assertex( copy_bar.classname == "script_brushmodel", "Photocopier at " + trigger.origin + " doesn't target a photo copier" );

	//*light = getent( copy_bar.target, "targetname" );
	//*assertex( light.classname == "light_spot" || light.classname == "light", "Photocopier at " + trigger.origin + " doesn't have a light" );

	//*light.intensity = light getlightintensity();
	//*light setlightintensity( 0 );
	trigger.copy_bar = copy_bar;
	trigger.start_pos = copy_bar.origin;
	//*trigger.light = light;

	angles = self.copier.angles + ( 0, 90, 0 );
	forward = anglestoforward( angles );
	trigger.end_pos = trigger.start_pos + ( forward * 30 );
}

get_photo_copier( trigger )
{
	if ( !isdefined( trigger.target ) )
	{
		//cant target directly to a destructible toy, so we are grabing the nearest one, since primary light requires them to be far anyway
		toys = getentarray( "destructible_toy", "targetname" );
		copier = toys[ 0 ];
		foreach ( toy in toys )
		{
			if ( isdefined( toy.destructible_type ) && toy.destructible_type == "toy_copier" )
			{
				if ( distance( trigger.origin, copier.origin ) > distance( trigger.origin, toy.origin ) )
					copier = toy;
			}
		}
		assertex( distance( trigger.origin, copier.origin ) < 128, "Photocopier at " + trigger.origin + " doesn't contain a photo copier" );
	}
	else
	{
		copier = getent( trigger.target, "targetname" );
		assertex( isdefined( copier ), "Photocopier at " + trigger.origin + " doesn't target a photo copier" );
		copier setcandamage( true );
	}	
	
	return copier;
}

waittill_copier_copies()
{
	self.copier endon( "FX_State_Change0" );
	self.copier endon( "death" );

	self waittill( "trigger_enter" );
}

photo_copier()
{
	level endon( "game_ended" );
	photo_copier_init( self );

	self.copier endon( "FX_State_Change0" );	// this is when copier breaks
	self thread photo_copier_stop();			// monitor copier for quick stop

	for ( ;; )
	{
		waittill_copier_copies();

		self playSound( "mach_copier_run" );

		if ( isdefined( self.copy_bar ) )
		{
			reset_copier( self );
			thread photo_copier_copy_bar_goes();
			//*thread photo_copier_light_on();
		}
		wait( 3 );
	}
}

photo_copier_no_light()
{
	level endon( "game_ended" );
	self endon ( "death" ); 

	if( get_template_level() == "hamburg" )
		return; // I don't need no stinking copies. // masking is not friendly for this - Nate

	self.copier  = get_photo_copier( self );
	
	assertex( self.copier.classname == "script_model", "Photocopier at " + self.origin + " doesn't target or contain a photo copier" );
	
	self.copier endon( "FX_State_Change0" );	// this is when copier breaks

	for ( ;; )
	{
		waittill_copier_copies();
		self playSound( "mach_copier_run" );
		wait( 3 );
	}
}

// reset light and copy bar position, interruptes previous copy in progress
reset_copier( trigger )
{
	trigger.copy_bar moveto( trigger.start_pos, 0.2 );	// reset position
	trigger.light setlightintensity( 0 );
}

photo_copier_copy_bar_goes()
{
	self.copier notify( "bar_goes" );
	self.copier endon( "bar_goes" );
	self.copier endon( "FX_State_Change0" );
	self.copier endon( "death" );

	copy_bar = self.copy_bar;
	wait( 2.0 );
	copy_bar moveto( self.end_pos, 1.6 );
	wait( 1.8 );
	copy_bar moveto( self.start_pos, 1.6 );
	wait( 1.6 );	// wait( 13.35 );

	light = self.light;
	timer = 0.2;
	steps = timer / 0.05;

	for ( i = 0; i < steps; i++ )
	{
		intensity = i * 0.05;
		intensity /= timer;
		intensity = 1 - ( intensity * light.intensity );
		if ( intensity > 0 )
			light setlightintensity( intensity );
		wait( 0.05 );
	}
}

photo_copier_light_on()
{
	self.copier notify( "light_on" );
	self.copier endon( "light_on" );
	self.copier endon( "FX_State_Change0" );
	self.copier endon( "death" );

	light = self.light;
	timer = 0.2;
	steps = timer / 0.05;

	for ( i = 0; i < steps; i++ )
	{
		intensity = i * 0.05;
		intensity /= timer;
		light setlightintensity( intensity * light.intensity );
		wait( 0.05 );
	}

	photo_light_flicker( light );
}

// stopping light and bar move on death
photo_copier_stop()
{
	self.copier waittill( "FX_State_Change0" );
	self.copier endon( "death" );

	reset_copier( self );
}

photo_light_flicker( light )
{
	// flicker
	light setlightintensity( 1 );
	wait( 0.05 );
	light setlightintensity( 0 );
	wait( 0.10 );
	light setlightintensity( 1 );
	wait( 0.05 );
	light setlightintensity( 0 );
	wait( 0.10 );
	light setlightintensity( 1 );
}


fan_blade_rotate( type )
{
	assert( isdefined( type ) );

	speed = 0;
	time = 20000;

	speed_multiplier = 1.0;
	if( isdefined( self.speed ) )
	{
		speed_multiplier = self.speed;
	}
	
	if ( type == "slow" )
	{
			if( isdefined( self.script_noteworthy ) && (self.script_noteworthy=="lockedspeed") )
				speed = 180;
			else
				speed = randomfloatrange( 100*speed_multiplier, 360*speed_multiplier );
	}
	else if ( type == "fast" )
		speed = randomfloatrange( 720*speed_multiplier, 1000*speed_multiplier );
	else if ( type == "veryslow" )
		speed = randomfloatrange( 1*speed_multiplier, 2*speed_multiplier );	// use the speed to really tune
	else
		assertmsg( "Type must be fast, slow, or veryslow" );

	if( isdefined( self.script_noteworthy ) && (self.script_noteworthy=="lockedspeed") )
		wait 0;
	else
		wait randomfloatrange( 0, 1 );

	fan_angles 	 = self.angles;
	fan_vec 	 = ( AnglesToRight( self.angles ) * 100 );	// assures normalized vector is length of "1"
	fan_vec 	 = VectorNormalize( fan_vec );

    while ( true )
    {
    	dot_x 	 = abs( vectorDot( fan_vec, ( 1, 0, 0 ) ) );
    	dot_y 	 = abs( vectorDot( fan_vec, ( 0, 1, 0 ) ) );
    	dot_z 	 = abs( vectorDot( fan_vec, ( 0, 0, 1 ) ) );

    	if ( dot_x > 0.9 )
        	self rotatevelocity( ( speed, 0, 0 ), time );
        else if ( dot_y > 0.9 )
        	self rotatevelocity( ( speed, 0, 0 ), time );
        else if ( dot_z > 0.9 )
        	self rotatevelocity( ( 0, speed, 0 ), time );
        else
        	self rotatevelocity( ( 0, speed, 0 ), time );

        wait time;
    }
}


triggerTouchThink( enterFunc, exitFunc )
{
	level endon( "game_ended" );

	self.entNum = self getEntityNumber();

	while ( true )
	{
		self waittill( "trigger", player );

		if ( !isPlayer( player ) && !isDefined( player.finished_spawning ) )
			continue;

		if ( !isAlive( player ) )
			continue;

		if ( !isDefined( player.touchTriggers[ self.entNum ] ) )
			player thread playerTouchTriggerThink( self, enterFunc, exitFunc );
	}
}


playerTouchTriggerThink( trigger, enterFunc, exitFunc )
{
	if ( !isPlayer( self ) )
		self endon( "death" );

	if ( !isSP() )
		touchName = self.guid;	// generate GUID
	else
		touchName = "player" + gettime();		// generate GUID

	trigger.touchList[ touchName ] = self;
	if ( isDefined( trigger.moveTracker ) )
		self.moveTrackers++ ;

	trigger notify( "trigger_enter", self );
	self notify( "trigger_enter", trigger );

	if ( isDefined( enterFunc ) )
		self thread [[ enterFunc ]]( trigger );

	self.touchTriggers[ trigger.entNum ] = trigger;

	while ( isAlive( self ) && self isTouching( trigger ) && ( isSP() || !level.gameEnded ) )
		wait( 0.05 );

	// disconnected player will skip this code
	if ( isDefined( self ) )
	{
		self.touchTriggers[ trigger.entNum ] = undefined;
		if ( isDefined( trigger.moveTracker ) )
			self.moveTrackers -- ;

		self notify( "trigger_leave", trigger );

		if ( isDefined( exitFunc ) )
			self thread [[ exitFunc ]]( trigger );
	}

	if ( !isSP() && level.gameEnded )
		return;

	trigger.touchList[ touchName ] = undefined;
	trigger notify( "trigger_leave", self );

	if ( !anythingTouchingTrigger( trigger ) )
		trigger notify( "trigger_empty" );
}


movementTracker()
{
	if ( IsDefined( level.DisablemovementTracker  ) )
		return;
	self endon( "disconnect" );

	if ( !isPlayer( self ) )
		self endon( "death" );

	self.moveTrackers = 0;
	self.distMoved = 0;

	for ( ;; )
	{
		self waittill( "trigger_enter" );

		lastOrigin = self.origin;
		while ( self.moveTrackers )
		{
			self.distMoved = distance( lastOrigin, self.origin );
			lastOrigin = self.origin;
			wait( 0.05 );
		}

		self.distMoved = 0;
	}
}


anythingTouchingTrigger( trigger )
{
	return( trigger.touchList.size );
}


playerTouchingTrigger( player, trigger )
{
	assert( isDefined( trigger.entNum ) );
	return( isDefined( player.touchTriggers[ trigger.entNum ] ) );
}
