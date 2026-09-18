main( turret )
{
	self endon( "killanimscript" );// code

 	assert( isdefined( turret ) );

    animscripts\utility::initialize( "saw" );

	// when we ran our postscriptfunc we may have decided to stop using our turret,
	// in which case it's gone now
	if ( !isdefined( turret ) )
		return;

	self.a.special = "saw";

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

	if ( isDefined( turret.aiOwner ) )
	{
		assert( turret.aiOwner == self );
		self.a.postScriptFunc = ::postScriptFunc;
		self.a.usingTurret = turret;
		turret notify( "being_used" );
		self thread stopUsingTurretWhenNodeLost();
	}
	else
	{
		self.a.postScriptFunc = ::preplacedPostScriptFunc;
	}

	turret.doFiring = false;
	self thread fireController( turret );


	self setTurretAnim( self.primaryTurretAnim );
	self setAnimKnobRestart( self.primaryTurretAnim, 1, 0.2, 1 );

	self setAnimKnobLimitedRestart( self.additiveTurretIdle );
	self setAnimKnobLimitedRestart( self.additiveTurretFire );

	turret setAnimKnobLimitedRestart( turret.additiveTurretIdle );
	turret setAnimKnobLimitedRestart( turret.additiveTurretFire );

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
		while ( isDefined( self.enemy ) )
		{
			enemypos = self.enemy.origin;
			//if ( isSentient( enemypos ) )
			//	enemypos += (0,0,32);
			turretAimPos = turret getTagAngles( "tag_aim" );

			if ( within_fov( turret.origin, turretAimPos, enemypos, fovdot ) || distanceSquared( turret.origin, enemyPos ) < 200 * 200 )
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


turretTimer( duration, turret )
{
	if ( duration <= 0 )
		return;

	self endon( "killanimscript" );// code
	turret endon( "turretstatechange" );// code

	wait( duration );
	turret notify( "turretstatechange" );
}

stopUsingTurretWhenNodeLost()
{
	self endon( "killanimscript" );

	// sometimes someone else will come and steal our node. when that happens,
	// we should leave so we don't try to use the same MG at once.
	while ( 1 )
	{
		if ( !isdefined( self.node ) || distancesquared( self.origin, self.node.origin ) > 64 * 64 )
			self stopUseTurret();
		wait .25;
	}
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
			self stopUseTurret();
		}
	}

	assert( self.a.usingTurret.aiOwner == self );

	if ( animscript == "saw" )
	{
		turret = self getTurret();
		assert( isDefined( turret ) && turret == self.a.usingTurret );
		return;
	}

	self.a.usingTurret delete();
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


within_fov( start_origin, start_angles, end_origin, fov )
{
	normal = vectorNormalize( end_origin - start_origin );
	forward = anglestoforward( start_angles );
	dot = vectorDot( forward, normal );

	return dot >= fov;
}


// ==================================

#using_animtree( "generic_human" );

DoShoot( turret )
{
	self setAnim( %additive_saw_idle, 0, .1 );
	self setAnim( %additive_saw_fire, 1, .1 );

	turret turretDoShootAnims();

	TurretDoShoot( turret );
}

DoAim( turret )
{
	self setAnim( %additive_saw_idle, 1, .1 );
	self setAnim( %additive_saw_fire, 0, .1 );

	turret turretDoAimAnims();
}


//=====================================
#using_animtree( "mg42" );

TurretDoShoot( turret )
{
	self endon( "killanimscript" );
	turret endon( "turretstatechange" );// code or script

	for ( ;; )
	{
		turret ShootTurret();
		wait 0.1;
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

