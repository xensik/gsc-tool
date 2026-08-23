#include maps\_utility;
#include common_scripts\utility;

main( turret )
{
	self endon( "killanimscript" );// code

 	assert( isdefined( turret ) );

    animscripts\utility::initialize( "technical" );

	// when we ran our postscriptfunc we may have decided to stop using our turret,
	// in which case it's gone now
	if ( !IsDefined( turret ) )
	{
		return;
	}

	self.a.special = "technical";

	if ( isDefined( turret.script_delay_min ) )
		turret_delay = turret.script_delay_min;
	else
		turret_delay = maps\_mgturret::burst_fire_settings( "delay" );

	if ( isDefined( turret.script_delay_max ) )
		turret_delay_range = turret.script_delay_max - turret_delay;
	else
		turret_delay_range = maps\_mgturret::burst_fire_settings( "delay_range" );

	if ( isDefined( turret.script_burst_min ) )
		turret_burst = turret.script_burst_min;
	else
		turret_burst = maps\_mgturret::burst_fire_settings( "burst" );

	if ( isDefined( turret.script_burst_max ) )
		turret_burst_range = turret.script_burst_max - turret_burst;
	else
		turret_burst_range = maps\_mgturret::burst_fire_settings( "burst_range" );

	pauseUntilTime = getTime();
	turretState = "start";

	self animscripts\shared::placeWeaponOn( self.weapon, "none" );
	turret show();
	
	self.a.postScriptFunc = ::preplacedPostScriptFunc;
	
	turret notify( "stop_burst_fire_unmanned" );

	turret.doFiring = false;
	self thread fireController( turret );

	self setTurretAnim( self.primaryTurretAnim );
	self setAnimKnobRestart( self.primaryTurretAnim, 1, 0.2, 1 );

	self setAnimKnobLimitedRestart( self.additiveTurretIdle );
	self setAnimKnobLimitedRestart( self.additiveTurretFire );

	//turret setAnimKnobLimitedRestart( turret.additiveTurretIdle );
	//turret setAnimKnobLimitedRestart( turret.additiveTurretFire );

	turret endon( "death" );
	for ( ;; )
	{
		if ( turret.doFiring )
		{
			thread DoShoot( turret );

			self waitTimeOrUntilTurretStateChange( randomFloatRange( turret_burst, turret_burst + turret_burst_range ), turret );
			turret notify( "turretstatechange" );

			if ( turret.doFiring )
			{
				thread DoAim( turret );
				wait( randomFloatRange( turret_delay, turret_delay + turret_delay_range ) );
			}
		}
		else
		{
			thread DoAim( turret );
			turret waittill( "turretstatechange" );
		}
	}
}

waitTimeOrUntilTurretStateChange( time, turret )
{
	turret endon( "turretstatechange" );
	wait time;
}

fireController( turret )
{
	self endon( "killanimscript" );
	
	fovdot = cos( 15 );

	for ( ;; )
	{
		while ( IsDefined( self.enemy ) )
		{
			if ( self turret_should_shoot( turret, fovdot ) )
			{
				if ( !turret.doFiring )
				{
					turret.doFiring = true;
					turret notify( "turretstatechange" );
				}
			}
			else if ( turret.doFiring )
			{
				turret.doFiring = false;
				turret notify( "turretstatechange" );
			}

			wait( 0.05 );
		}

		if ( turret.doFiring )
		{
			turret.doFiring = false;
			turret notify( "turretstatechange" );
		}

		wait( 0.05 );
	}
}

turret_should_shoot( turret, fovdot )
{
	ASSERT( IsDefined( self.enemy ) );
	
	enemypos = self.enemy.origin;
	turretAimPos = turret getTagAngles( "tag_aim" );
	
	if( within_fov( turret.origin, turretAimPos, enemypos, fovdot ) || distanceSquared( turret.origin, enemyPos ) < 200 * 200 )
	{
		if( !self turret_would_hit_friend( turret ) )
		{
			return true;
		}
	}
	
	return false;
}

turret_would_hit_friend( turret, friendlyTeam )
{
	tag = "tag_flash";
	start = turret GetTagOrigin( tag );
	vec = AnglesToForward( turret GetTagAngles( tag ) );
	end = ( vec * 10000 );
	
	trace = BulletTrace( start, end, true, undefined );
	ent = trace[ "entity" ];
	
	if( IsDefined( ent ) )
	{
		if( ( IsDefined( ent.team ) && ent.team == self.team ) || ( IsDefined( ent.script_team ) && ent.script_team == self.team ) )
		{
			return true;
		}
	}
	
	return false;
}


turretTimer( duration, turret )
{
	if ( duration <= 0 )
		return;

	self endon( "killanimscript" );// code
	turret endon( "turretstatechange" );// code

	wait( duration );
	turret notify( "turretstatechange" );
}

postScriptFunc( animscript )
{
	if ( animscript == "pain" )
	{
		if ( isdefined( self.node ) && distancesquared( self.origin, self.node.origin ) < 64 * 64 )
		{
			self.a.usingTurret hide();
			self animscripts\shared::placeWeaponOn( self.weapon, "right" );
			self.a.postScriptFunc = ::postPainFunc;
			return;
		}
		else
		{
			self StopUseTurret();
		}
	}

	assert( self.a.usingTurret.aiOwner == self );

	if ( animscript == "saw" )
	{
		turret = self GetTurret();
		assert( IsDefined( turret ) && turret == self.a.usingTurret );
		return;
	}

	self.a.usingTurret Delete();
	self.a.usingTurret = undefined;

	self animscripts\shared::placeWeaponOn( self.weapon, "right" );
}

postPainFunc( animscript )
{
	assert( isDefined( self.a.usingTurret ) );
	assert( self.a.usingTurret.aiOwner == self );

	if ( !isdefined( self.node ) || distancesquared( self.origin, self.node.origin ) > 64 * 64 )
	{
		self stopUseTurret();

		self.a.usingTurret delete();
		self.a.usingTurret = undefined;

		// we may have gone into long death, in which case our weapon is gone
		if ( isdefined( self.weapon ) && self.weapon != "none" )
		{
			self animscripts\shared::placeWeaponOn( self.weapon, "right" );
		}
	}
	else if ( animscript != "saw" )
	{
		self.a.usingTurret delete();
	}
}


preplacedPostScriptFunc( animscript )
{
	self animscripts\shared::placeWeaponOn( self.weapon, "right" );
}


// ==================================

#using_animtree( "generic_human" );

DoShoot( turret )
{
	self setAnim( %additive_saw_idle, 0, .1 );
	self setAnim( %additive_saw_fire, 1, .1 );

	//turret turretDoShootAnims();

	TurretDoShoot( turret );
}

DoAim( turret )
{
	self setAnim( %additive_saw_idle, 1, .1 );
	self setAnim( %additive_saw_fire, 0, .1 );

	//turret turretDoAimAnims();
}


//=====================================
#using_animtree( "mg42" );

TurretDoShoot( turret )
{
	self endon( "killanimscript" );
	turret endon( "turretstatechange" );// code or script
	turret endon( "death" );// code or script

	for ( ;; )
	{
		turret ShootTurret();
		wait( 0.15 );
	}
}

turretDoShootAnims()
{
	self setAnim( %additive_saw_idle, 0, .1 );
	self setAnim( %additive_saw_fire, 1, .1 );
}

turretDoAimAnims()
{
	self setAnim( %additive_saw_idle, 1, .1 );
	self setAnim( %additive_saw_fire, 0, .1 );
}


//==================
/* OLD STUFF
//==================
main( shoot, recover, aim, turret )
{
	self endon( "killanimscript" );// code

    animscripts\utility::initialize( "technical" );

	self.a.special = "technical";

	if ( isDefined( turret.script_delay_min ) )
		turret_delay = turret.script_delay_min;
	else
		turret_delay = maps\_mgturret::burst_fire_settings( "delay" );

	if ( isDefined( turret.script_delay_max ) )
		turret_delay_range = turret.script_delay_max - turret_delay;
	else
		turret_delay_range = maps\_mgturret::burst_fire_settings( "delay_range" );

	if ( isDefined( turret.script_burst_min ) )
		turret_burst = turret.script_burst_min;
	else
		turret_burst = maps\_mgturret::burst_fire_settings( "burst" );

	if ( isDefined( turret.script_burst_max ) )
		turret_burst_range = turret.script_burst_max - turret_burst;
	else
		turret_burst_range = maps\_mgturret::burst_fire_settings( "burst_range" );

	pauseUntilTime = getTime();
	turretState = "start";

	self animscripts\shared::placeWeaponOn( self.weapon, "none" );
	self.a.postScriptFunc = ::preplacedPostScriptFunc;

	for ( ;; )
	{
		duration = ( pauseUntilTime - getTime() ) * 0.001;
		if ( turret isFiringTurret() && ( duration <= 0 ) )
		{
			if ( turretState != "fire" )
			{
				turretState = "fire";
				thread [[ shoot ]]( turret );// non blocking
			}

			duration = turret_burst + randomFloat( turret_burst_range );

			thread turretTimer( duration, turret );



			turret waittill( "turretstatechange" );// code or script

			duration = turret_delay + randomFloat( turret_delay_range );

			pauseUntilTime = getTime() + int( duration * 1000 );

			if ( isDefined( recover ) )
			{
				turretState = "recover";
				[[ recover ]]( turret );// blocking
			}
		}
		else
		{
			if ( turretState != "aim" )
			{
				turretState = "aim";
				thread [[ aim ]]( turret );// non blocking
			}

			thread turretTimer( duration, turret );

			turret waittill( "turretstatechange" );// code or script
		}
	}
}


turretTimer( duration, turret )
{
	if ( duration <= 0 )
		return;

	self endon( "killanimscript" );// code
	turret endon( "turretstatechange" );// code

	wait( duration );
	turret notify( "turretstatechange" );
}


preplacedPostScriptFunc( animscript )
{
	self animscripts\shared::placeWeaponOn( self.weapon, "right" );
}
*/
