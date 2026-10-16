#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;

#using_animtree( "generic_human" );

humvee_turret_init( turret, turretType )
{
	self endon( "killanimscript" );// code

 	Assert( IsDefined( turret ) );

    animscripts\utility::initialize( turretType );

	self.no_ai = true;
	self.noDrop = true;
	self.a.movement = "stop";
	self.a.special = turretType;
	self.a.usingTurret = turret;
	self.ignoreme = true;
	if( IsDefined( self.minigun_ignoreme ) )
		self.ignoreme = self.minigun_ignoreme;
	self.isCustomAnimating = false;
	self SetTurretAnim( self.primaryTurretAnim );
	self SetAnimKnobRestart( self.primaryTurretAnim, 1, 0.2, 1 );

	if ( IsDefined( self.weapon ) )
	{
		self animscripts\shared::placeWeaponOn( self.weapon, "none" );
	}

	self.onRotatingVehicleTurret = true;
	self.getOffVehicleFunc = ::turret_cleanup_on_unload;

	// end some _vehicle and _mgturret threads that we don't want
	self notify( "guy_man_turret_stop" );
	turret notify( "stop_burst_fire_unmanned" );

	// setup the turret
	turret.turretState = "start";
	turret.aiOwner = self;
	turret.fireTime = 0;
	turret SetMode( "sentry" );
	turret SetSentryOwner( self );
	turret SetDefaultDropPitch( 0 );
	turret SetTurretCanAIDetach( false );

	self gunner_pain_init();
	level thread handle_gunner_pain( self, turret );
	level thread handle_gunner_death( self, turret );

	// start tracking the turret rotation
	turret thread turret_track_rotatedirection( self );

	// start turret fire director
	turret.doFiring = false;
	self thread fireDirector( turret );

	wait( 0.05 );
	if ( IsAlive( self ) )
	{
		self thread gunner_turning_anims( turret );
	}
}

gunner_pain_init()
{
	self.allowPain = false; // we're going to handle it ourselves
	self setFlashbangImmunity( true );

	self.og_health = self.health;
	self.health = 200;
}

gunner_pain_reset()
{
	self.allowPain = true;
	self setFlashbangImmunity( false );
	self.health = self.og_health;
}

handle_gunner_pain( gunner, turret )
{
	gunner endon( "death" );
	turret endon( "death" );
	gunner endon( "dismount" );
	gunner endon( "jumping_out" );

	while ( 1 )
	{
		flashedNotify = "flashbang";

		//gunner waittill( "damage", damage, attacker, direction_vec, point, type, modelName, tagName, partName, dflags );
		msg = gunner waittill_any_return( "damage", flashedNotify );

		/* custom anim pre-empts pain or flash
		if( gunner.isCustomAnimating )
		{
			continue;
		}
		*/

		painAnim = random( gunner.turretPainAnims );
		if ( msg == flashedNotify )
		{
			painAnim = gunner.turretFlashbangedAnim;
			gunner animscripts\face::SayGenericDialogue( "flashbang" );
		}

		//turret thread turret_recenter();
		gunner DoCustomAnim( turret, painAnim, false );
		turret notify( "pain_done" );
	}
}

turret_recenter()
{
	self turret_aim_straight();
	self waittill( "pain_done" );
	self turret_aim_restore();
}

handle_gunner_death( gunner, turret )
{
	gunner endon( "dismount" );
	turret endon( "turret_cleanup" );

	gunner.deathanim = gunner.turretDeathAnim;
	gunner.noragdoll = true;

	gunner waittill( "death" );
	level thread turret_cleanup( gunner, turret );
}

// for when _vehicle_aianim wants to unload the gunner, it doesn't know as much as this script yet
turret_cleanup_on_unload()
{
	Assert( IsDefined( self.ridingVehicle ) );

	turret = self.ridingVehicle.mgturret[ 0 ];
	Assert( IsDefined( turret ) );

	// clean up AI - moved it here since it's only needed for unloading.
	if ( IsAlive( self ) )
	{
		self.no_ai = undefined;
		self.noDrop = undefined;
		self.ignoreme = false;
		self.a.special = "none";
		self.a.usingTurret = undefined;
		self.deathanim = undefined;
		self gunner_pain_reset();
		self.isCustomAnimating = undefined;

		self.turretSpecialAnims = undefined;
		self.turretPainAnims = undefined;

		self.onRotatingVehicleTurret = undefined;
		self.getOffVehicleFunc = undefined;

		self StopUseTurret();

		if ( IsDefined( self.weapon ) )
		{
			self animscripts\shared::placeWeaponOn( self.weapon, "right" );
		}
	}

	level thread turret_cleanup( self, turret );
}

turret_cleanup( gunner, turret )
{
	if ( !IsDefined( turret ) )
	{
		return;
	}

	turret notify( "kill_fireController" );
	turret notify( "turret_cleanup" );
	turret SetMode( "manual" );
	turret ClearTargetEntity();
	
	turret SetDefaultDropPitch( turret.default_drop_pitch );

	if ( IsDefined( gunner ) )
	{
		gunner ClearAnim( gunner.additiveUsegunRoot, 0 );
		gunner ClearAnim( gunner.additiveRotateRoot, 0 );
		gunner ClearAnim( gunner.turretSpecialAnimsRoot, 0 );
	}

	// clean up turret
	turret.fireInterval = undefined;
	turret.closeEnoughAimDegrees = undefined;
	turret.fireControllerFunc = undefined;

	turret.turretState = "free";
	turret.aiOwner = undefined;
	turret.fireTime = undefined;

	if ( IsDefined( turret.specialCleanupFunc ) )
	{
		level [[ turret.specialCleanupFunc ]]( gunner, turret );
	}
}

// tracks the rotational direction of the turret
turret_track_rotatedirection( gunner )
{
	self endon( "turret_cleanup" );
	self endon( "death" );
	gunner endon( "death" );
	gunner endon( "detach" );

	tag = "tag_aim";
	lastAngles = self GetTagAngles( tag );

	self turret_update_rotatedirection( "none" );

	while ( 1 )
	{
		currentAngles = self GetTagAngles( tag );

		// the vectordot of the old right angles and the current forward angles is going to tell us whether
		//  the turret is rotating left, right, or not at all
		oldRight = AnglesToRight( lastAngles );
		currentForward = AnglesToForward( currentAngles );

		dot = VectorDot( oldRight, currentForward );

		if ( dot == 0 )
		{
			self turret_update_rotatedirection( "none" );
		}
		else if ( dot > 0 )
		{
			self turret_update_rotatedirection( "right" );
		}
		else
		{
			self turret_update_rotatedirection( "left" );
		}

		lastAngles = self GetTagAngles( tag );

		wait( 0.05 );
	}
}

turret_update_rotatedirection( direction )
{
	if ( !IsDefined( self.rotateDirection ) || self.rotateDirection != direction )
	{
		self.rotateDirection = direction;

		//println( "spin direction change: " + self.rotateDirection );
	}
}

gunner_turning_anims( turret )
{
	self endon( "death" );
	turret endon( "death" );
	self endon( "dismount" );
	turret endon( "turret_cleanup" );

	blendInTime = 0.3;
	blendOutTime = 0.3;

	while ( 1 )
	{
		turret waittill( "new_fireTarget" );
		wait( 0.05 );// give him a chance to start rotating to the new target so the direction updates

		if ( !IsDefined( turret.fireTarget ) || self.isCustomAnimating )
		{
			continue;
		}

		anime = undefined;

		if ( !turret turret_aiming_near_target( turret.fireTarget, turret.closeEnoughAimDegrees ) )
		{
			if ( turret.rotateDirection == "right" )
			{
				anime = self.additiveTurretRotateRight;
				//println( "gunner anim RIGHT" );
			}
			else if ( turret.rotateDirection == "left" )
			{
				anime = self.additiveTurretRotateLeft;
				//println( "gunner anim LEFT" );
			}

			if ( IsDefined( anime ) )
			{
				// dial the parent branch up
				self SetAnimLimited( self.additiveRotateRoot, 1, blendInTime, 1 );
				// also tell it which leaf anim to use
				// (this is inheriting its parent's blend in time so we can set the time to 0)
				self SetAnimKnobLimited( anime, 1, 0, 1 );

				while ( IsDefined( turret.fireTarget ) && !turret turret_aiming_near_target( turret.fireTarget, turret.closeEnoughAimDegrees ) )
				{
					if ( self.isCustomAnimating )
					{
						break;
					}

					wait( 0.05 );
				}

				//println( "gunner anim CLEAR" );
				self ClearAnim( self.additiveRotateRoot, blendOutTime );
			}
		}
	}
}

// makes a passenger into the turret gunner - call instead of UseTurret()
vehicle_passenger_2_turret( vehicle, pos, turret, animation )
{
	vehicle.usedPositions[ self.vehicle_position ] = false;
	//vehicle.riders = array_remove( vehicle.riders, self );
	self maps\_vehicle_aianim::guy_cleanup_vehiclevars();
	guy_gets_on_turret( vehicle, pos, turret, animation );
}

// makes a passenger into the turret gunner - call instead of UseTurret()
guy_goes_directly_to_turret( vehicle, pos, turret, animation )
{
	guy_gets_on_turret( vehicle, pos, turret, animation );
}

guy_gets_on_turret( vehicle, pos, turret, animation )
{
	self endon( "death" );
	turret endon( "death" );

	// forget about being a regular vehicle rider
	self StopAnimScripted();
	self notify( "newanim" );

	self.drivingVehicle = undefined;

	self.no_ai = true;
	animation = %humvee_passenger_2_turret;
	if ( !isdefined( animation ) )
		animation = self.passenger_2_turret_anim;

	// get the origin/angles of the vehicle tag where this guy is riding
	animpos = maps\_vehicle_aianim::anim_pos( vehicle, pos );
	org = vehicle GetTagOrigin( animpos.sittag );
	angles = vehicle GetTagAngles( animpos.sittag );

	turret SetDefaultDropPitch( 0 );
	turret thread turret_animate( turret.passenger2turret_anime );

	// animate into position
	self AnimScripted( "passenger2turret", org, angles, animation );
	wait( GetAnimLength( animation ) );
	self StopAnimScripted();

	turret turret_aim_restore();

	// now start running the regular turret scripts - GDT points to minigun_hummer\stand::main()
	self UseTurret( turret );
}

turret_animate( anime )
{
	if ( IsDefined( self.idleAnim ) )
	{
		self ClearAnim( self.idleAnim, 0 );
		self.idleAnim = undefined;
	}

	self SetFlaggedAnimKnobRestart( "minigun_turret", anime, 1, 0, 1 );
	self waittillmatch( "minigun_turret", "end" );
	self ClearAnim( anime, 0 );
}

turret_animfirstframe( anime )
{
	self SetAnimKnobRestart( anime, 1, 0, 0 );
	self.idleAnim = anime;
}

// "directs" the turret about whether it should be firing or not
//  note: works with either code-controlled sentry targets or manually setting turret target
//  - to make an AI aim without firing, set his .ignoreall to true
fireDirector( turret )
{
	self endon( "death" );
	turret endon( "death" );
	self endon( "dismount" );
	turret endon( "kill_fireController" );

	turret thread turret_target_updater( self );
	wait( 0.05 );// let the target updater kick off

	self thread [[ turret.fireControllerFunc ]]( turret );

	target = undefined;

	while ( 1 )
	{
		// get a target
		target = turret.fireTarget;

		// wait for the right time to start shooting
		while ( turret target_confirm( target ) )
		{
			// tried a CanSee check here too, didn't seem necessary after testing
			if ( turret turret_aiming_near_target( target, turret.closeEnoughAimDegrees ) )
			{
				break;
			}
			wait( 0.05 );
		}

		if ( turret target_confirm( target ) && !self.ignoreall )
		{
			// shoot at him
			turret.doFiring = true;
		}

		// wait for his death, or for the code/script to pick/designate a new target
		while ( turret target_confirm( target ) && !self.ignoreall && !self.isCustomAnimating )
		{
			wait( 0.05 );
		}

		// stop shooting
		if ( turret.Dofiring || self.ignoreall )
		{
			turret.doFiring = false;
		}

		wait( 0.05 );
	}
}

// makes sure the target that the fireDirector is thinking about is still synced with turret_target_updater
target_confirm( target )
{
	if ( IsDefined( self.dontshoot ) )
	{
		AssertEx( self.dontshoot, ".dontshoot must be true or undefined." );
		return false;
	}

	// maybe the turret can't see the target anymore
	if ( !IsDefined( self.fireTarget ) )
	{
		return false;
	}

	if ( !turret_target_validate( target ) )
	{
		return false;
	}

	if ( target != self.fireTarget )
	{
		return false;
	}

	return true;
}

// make sure the script knows about the most recent turret target
// (this is necessary because code sets the turret target silently and behind the scenes)
turret_target_updater( gunner )
{
	gunner endon( "death" );
	self endon( "death" );
	gunner endon( "dismount" );
	self endon( "kill_fireController" );


	// initialize this, other threads are looking for it
	self.fireTarget = undefined;

	target = undefined;
	lastTarget = undefined;

	while ( 1 )
	{
		target = self GetTurretTarget( false );

		doUpdate = false;

		// target can come back undefined if the turret loses sight of its target
		if ( turret_target_validate( target ) || !IsDefined( target ) )
		{
			// if the old target was defined and the new target is undefined
			//  (e.g., the turret lost its target) we want to update
			if ( !IsDefined( target ) && IsDefined( lastTarget ) )
			{
				doUpdate = true;
			}
			// or, if the new target is defined and the old one isn't, do the update
			else if ( IsDefined( target ) && !IsDefined( lastTarget ) )
			{
				doUpdate = true;
			}
			// or, if the new target is defined and different from before, do the update
			else if ( IsDefined( target ) && target != lastTarget )
			{
				doUpdate = true;
			}

			if ( doUpdate )
			{
				self.fireTarget = target;
				lastTarget = target;
				self notify( "new_fireTarget" );
			}
		}

		wait( 0.05 );
	}
}

turret_target_validate( target )
{
	if ( !IsDefined( target ) )
	{
		return false;
	}

	if ( IsDefined( target.ignoreme ) && target.ignoreme )
	{
		return false;
	}

	// can't use IsSentient because the sentient AIs will turn into non-sentient corpses
	if ( IsSubStr( target.code_classname, "actor" ) && !IsAlive( target ) )
	{
		return false;
	}

	return true;
}

// manually designate a target for the turret
// - fireTime_min: minimum amount of time to fire once the turret has centered on the target
// - fireTime_max (optional): if set, function will pick a random time between min and max
// - fireTime_message (optional): will fire until the turret is notified the message. will ignore min and max time.
set_manual_target( target, fireTime_min, fireTime_max, fireTime_message )
{
	AssertEx( IsDefined( target ), "undefined target passed to set_manual_target()." );

	self endon( "turret_cleanup" );

	oldMode = self GetMode();
	if ( oldMode != "manual" )
	{
		self SetMode( "manual" );
	}

	if ( !IsDefined( fireTime_min ) && !IsDefined( fireTime_max ) )
	{
		fireTime_min = 1.5;
		fireTime_max = 3;
	}

	self animscripts\hummer_turret\common::custom_anim_wait();
	self SetTargetEntity( target );
	//println( "target set" );

	self waittill( "turret_on_target" );
	//println( "turret on target" );

	if ( IsDefined( fireTime_message ) )
	{
		self waittill( fireTime_message );
	}
	else if ( IsDefined( fireTime_max ) )
	{
		wait( RandomFloatRange( fireTime_min, fireTime_max ) );
	}
	else
	{
		wait( fireTime_min );
	}

	self custom_anim_wait();
	self ClearTargetEntity( target );

	if ( IsDefined( oldMode ) )
	{
		self SetMode( oldMode );
	}
}

DoShoot( turret )
{
	self notify( "doshoot_starting" );

	self SetAnimLimited( self.additiveUsegunRoot, 1, .1 );
	self SetAnimKnobLimited( self.additiveTurretFire, 1, .1 );

	turret.turretState = "fire";
	turret thread fire( self );
}

fire( gunner )
{
	gunner endon( "death" );
	self endon( "death" );
	gunner endon( "dismount" );
	self endon( "kill_fireController" );
	self endon( "stopfiring" );
	self endon( "custom_anim" );

	while ( 1 )
	{
		self ShootTurret();
		wait( self.fireInterval );
	}
}

DoAim( turret )
{
	turret.turretState = "aim";
	turret notify( "stopfiring" );

	self thread DoAim_idle_think( turret );
}

DoAim_idle_think( turret )
{
	self notify( "doaim_idle_think" );
	self endon( "doaim_idle_think" );

	self endon( "custom_anim" );
	self endon( "doshoot_starting" );
	self endon( "death" );
	
	turret endon( "death" );
	assertex( isdefined( turret ), "The turret is gone!" );
	assertex( isalive( self ), "No, I can't die!" );

	Assert( IsDefined( turret.ownervehicle ) );
	vehicle = turret.ownervehicle;
	assertex( isdefined( vehicle ), "There is no vehicle!" );

	idle = -1;

	for ( ;; )
	{
		if ( vehicle Vehicle_GetSpeed() < 1 && idle )
		{
			self SetAnimLimited( self.additiveUsegunRoot, 1, 0.1 );
			self SetAnimKnobLimited( self.additiveTurretIdle, 1, 0.1 );
			idle = 0;
		}
		else 
		if ( vehicle Vehicle_GetSpeed() >= 1 && !idle )
		{
			self SetAnimLimited( self.additiveUsegunRoot, 1, 0.1 );
			self SetAnimKnobLimited( self.additiveTurretDriveIdle, 1, 0.1 );
			idle = 1;
		}

		wait( 0.05 );
	}
}

/*
=============
///ScriptDocBegin
"Name: turret_gunner_custom_anim( <turret> , <animStr> , <centerTurretFirst> )"
"Summary: Call on a turret gunner do one of his predefined custom animations.  All the custom anims for a turret gunner get set up in the array self.turretSpecialAnims, in the main script for the turret type - for example, animscripts\hummer_turret\minigun_stand.gsc."
"Module: Entity"
"CallOn: An AI using a vehicle turret. (Note: this only works for 360 degree vehicle turrets, for example those on the hummer or the suburban.)"
"MandatoryArg: <turret> The turret the AI is using."
"MandatoryArg: <animStr> The name of the animation, as a string. used as the lookup index for self.turretSpecialAnims."
"OptionalArg: <centerTurretFirst>: Whether the turret should re-center to its "home" location before the animation plays. Defaults to false."
"Example: gunner animscripts\hummer_turret\common::turret_gunner_custom_anim( turret, anime, true );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
turret_gunner_custom_anim( turret, animStr, centerTurretFirst )
{
	// this section of endons should be identical to the ones in the function below
	self endon( "death" );
	turret endon( "death" );
	self endon( "dismount" );
	self endon( "jumping_out" );

	anime = self.turretSpecialAnims[ animStr ];
	Assert( IsDefined( anime ) );

	self custom_anim_wait();

	disabledReload = turret reload_disable_safe();

	self DoCustomAnim( turret, anime, centerTurretFirst );

	if ( disabledReload )
	{
		turret reload_enable();
	}
}

reload_disable_safe()
{
	disabledReload = false;
	if ( !IsDefined( self.disableReload ) || !self.disableReload )
	{
		disabledReload = true;
		self.disableReload = true;
	}

	return disabledReload;
}

reload_enable()
{
	self.disableReload = false;
}

DoReload( turret )
{
	if ( IsDefined( turret.disableReload ) )
	{
		return;
	}

	// this section of endons should be identical to the ones in the function above
	self endon( "death" );
	turret endon( "death" );
	self endon( "dismount" );
	self endon( "jumping_out" );

	self thread custom_battlechatter( "inform_reloading" );

	self DoCustomAnim( turret, self.turretReloadAnim, true );
}

DoCustomAnim( turret, anime, centerTurretFirst )
{
	// NOTE! To stop behavior, don't notify do_custom_anim, do self notify( "special_anim", "end" );
	self notify( "do_custom_anim" );
	self endon( "do_custom_anim" );

	/*
	// these endons are dupes
	
	self endon( "death" );
	turret endon( "death" );
	self endon( "dismount" );
	self endon( "jumping_out" );
	*/

	Assert( IsDefined( anime ) );

	self.isCustomAnimating = true;
	self.customAnim = anime;
	turret.turretState = "customanim";
	turret TurretFireDisable();

	if ( turret GetBarrelSpinRate() > 0 )
	{
		turret StopBarrelSpin();
	}

	// turn off threads that can mess up the animtree
	turret notify( "kill_fireController" );
	self notify( "custom_anim" );

	if ( IsDefined( centerTurretFirst ) && centerTurretFirst )
	{
		turret turret_aim_straight();
	}

	// "knob" dials down all the siblings of the specialanimsroot, so we don't need to manually
	//  dial down self.primaryTurretAnim or self.additiveUsegunRoot right here
	self SetAnimKnobLimitedRestart( self.turretSpecialAnimsRoot, 1, 0.2 );
	self SetFlaggedAnimKnobRestart( "special_anim", anime, 1, 0, 1 );

	for ( ;; )
	{
		// broke into a loop so I can debug the notetracks
		self waittill( "special_anim", notetrack );
		if ( notetrack == "end" )
			break;
	}

	// turn the ROOT down, not the anim under the root
	self ClearAnim( self.turretSpecialAnimsRoot, 0.2 );
	// dial these up individually - can't use "knob" cause we want them both to be active
	self SetAnimLimited( self.primaryTurretAnim, 1 ); // 0.2 blend time is the default
	self SetAnimLimited( self.additiveUsegunRoot, 1 );

	if ( IsDefined( centerTurretFirst ) && centerTurretFirst )
	{
		turret turret_aim_restore();
	}

	self.customAnim = undefined;
	self.isCustomAnimating = false;
	turret TurretFireEnable();

	// turn those animtree-messing-up threads back on
	self thread fireDirector( turret );
}

// use this if you're manually setting the turret target entity - call this first (non-threaded)
//  to make sure that the DoCustomAnim function doesn't clear out your custom target
custom_anim_wait()
{
	self endon( "death" );

	if ( !IsDefined( self.isCustomAnimating ) )
	{
		return;
	}

	while ( self.isCustomAnimating )
	{
		wait( 0.05 );
	}
}

turret_aim_straight( straightAngles )
{
	if( self getmode() == "sentry" ) 
		return;
		
	if ( !IsDefined( straightAngles ) )
	{
		currentAngles = self GetTagAngles( "tag_flash" );
		straightAngles = ( 0, currentAngles[ 1 ], currentAngles[ 2 ] );// just keep the yaw
	}

	self.oldMode = self GetMode();
	
		self SetMode( "manual" );

	// use a temp target to make the gun point straight forward
	forward = AnglesToForward( straightAngles );
	scalevec = ( forward * 96 );
	targetOrigin = self GetTagOrigin( "tag_aim" ) + scalevec;
	
	self.tempTarget = Spawn( "script_origin", targetOrigin );
	self.tempTarget.ignoreme = true;
	self.tempTarget LinkTo( self.ownerVehicle );// if the vehicle is moving we have to link the target to the gun so the gun doesn't rotate around as the vehicle angles change

	self ClearTargetEntity();
	self SetTargetEntity( self.tempTarget );
	self waittill( "turret_on_target" );
}

turret_aim_restore()
{
	self ClearTargetEntity();

	if ( IsDefined( self.tempTarget ) )
	{
		self.tempTarget Unlink();
		self.tempTarget Delete();
	}

	if ( IsDefined( self.oldMode ) )
	{
		self SetMode( self.oldMode );
		self.oldMode = undefined;
	}
}

// - closeEnoughAngle: we want to be pointing within [+/- of this value in degrees]
//    to the target to return true
turret_aiming_near_target( target, closeEnoughAngle )
{
	delta = self turret_get_angle_to_target( target );

	if ( delta <= closeEnoughAngle )
	{
		return true;
	}

	return false;
}

turret_get_angle_to_target( target )
{
	// get the yaw angle of the vector between the target origin and the turret origin
	yawAngleToTarget = VectorToYaw( target.origin - self.origin );

	// normalize the difference between the yaw angle and the angles of the end of the barrel:
	//  this tells us how far away we are from being perfectly centered on the target
	turretYawAngle = self GetTagAngles( "tag_flash" )[ 1 ];
	delta = animscripts\utility::AbsAngleClamp180( turretYawAngle - yawAngleToTarget );

	return delta;
}

lerp_out_drop_pitch( time )
{
	blend = self create_blend( ::blend_dropPitch, 20, 0 );
	blend.time = time;
}

blend_dropPitch( progress, start, end )
{
	val = start * ( 1 - progress ) + end * progress;
	self SetDefaultDropPitch( val );
}

