#include maps\_utility;
#include common_scripts\utility;
#include animscripts\hummer_turret\common;

main( turret )
{
	turret.fireInterval = 0.1; // time between shots
	turret.closeEnoughAimDegrees = 45; // how many degrees away from aiming exactly at the target should we be before we start doing "on/near target" stuff
	turret.fireControllerFunc = ::fireController_minigun; // the function that tells the turret how exactly to shoot when the fireDirector tells it that it should be firing
	turret.specialCleanupFunc = ::minigun_cleanup_func; // gets called when the turret is no longer in use
	turret.default_drop_pitch = 20;

	humvee_turret_init( turret, "minigun" );
	wait( 0.05 );

	turret notify( "turret_ready" );
}

minigun_cleanup_func( gunner, turret )
{
	if ( turret GetBarrelSpinRate() > 0 )
	{
		turret StopBarrelSpin();
	}
}

// controls spinning & firing the minigun, responding to commands from fireDirector()
fireController_minigun( turret )
{
	self endon( "death" );
	self endon( "dismount" );
	
	assert( isdefined( turret ) );
	
	turret endon( "kill_fireController" );
	turret endon( "death" );

	// "extra" fire time makes the operator look like he has human reaction time
	turret.extraFireTime_min = 600; // ms
	turret.extraFireTime_max = 900;
	startFireTime = -1;
	ceaseFireTime = undefined;
	extraFireTime = undefined;

	// extra spin time makes it look like the operator is scanning for more targets
	turret.extraSpinTime_min = 250;
	turret.extraSpinTime_max = 2250;
	startExtraSpinningTime = -1;
	extraSpinTime = undefined;

	isFiring = false;
	isSpinning = false;

	// the weapon will need periodic operator "maintenance"
	turret.secsOfFiringBeforeReload = 15; // secs
	if( isdefined( turret.secsOfFiringBeforeReloadDefault ) )
		turret.secsOfFiringBeforeReload = turret.secsOfFiringBeforeReloadDefault;

	turret.fireTime = 0;
	
	self DoAim( turret );

	while ( 1 )
	{
		// if we're supposed to be firing but we're not, and if we're not doing a custom anim...
		if ( turret.doFiring && !isFiring && !self.isCustomAnimating )
		{
			isFiring = true;

			// spin the barrel if need be
			if ( !isSpinning )
			{
				//println( "start spin" );
				turret minigun_spinup();
				isSpinning = true;
			}

			// start firing
			//println( "start firing" );
			turret notify( "startfiring" );
			startFireTime = GetTime();
			self DoShoot( turret );
			wait( 0.05 ); // let the shooting thread start before potentially killing it on the same frame
		}
		// if we're currently not supposed to be firing but still actually are...
		else if ( !turret.doFiring && isFiring )
		{
			if ( !IsDefined( ceaseFireTime ) )
			{
				ceaseFireTime = GetTime(); // time when the turret stops firing
			}

			if ( !IsDefined( extraFireTime ) )
			{
				extraFireTime = RandomFloatRange( turret.extraFireTime_min, turret.extraFireTime_max );
			}

			// have we fired long enough after being told to stop?
			if ( GetTime() - ceaseFireTime >= extraFireTime )
			{
				isFiring = false;

				//println( "stop firing" );
				self DoAim( turret );
				startExtraSpinningTime = GetTime();

				// reset counters
				ceaseFireTime = undefined;
				extraFireTime = undefined;
			}
		}
		// if all we're still doing is spinning...
		else if ( !turret.doFiring && !isFiring && isSpinning )
		{
			if ( !IsDefined( extraSpinTime ) )
			{
				extraSpinTime = RandomFloatRange( turret.extraSpinTime_min, turret.extraSpinTime_max );
			}

			// stop spin immediately for custom anims, or wait for extra spin time
			if ( self.isCustomAnimating || ( GetTime() - startExtraSpinningTime >= extraSpinTime ) )
			{
				//println( "stop spin" );
				turret StopBarrelSpin();
				isSpinning = false;

				extraSpinTime = undefined; // reset
			}
		}

		if ( turret.turretstate == "fire" )
			turret.fireTime += 0.05;// ( GetTime() - startFireTime ) / 1000;

		if ( turret.fireTime > turret.secsOfFiringBeforeReload )
		{
			//println( "reload" );
			turret.doFiring = false;
			isFiring = false;
			self DoAim( turret );
			startExtraSpinningTime = -1;
			ceaseFireTime = undefined;
			extraFireTime = undefined;

			self thread DoReload( turret );
			turret.fireTime = 0; // reset counter
		}

		wait( 0.05 );
		
		if ( !isdefined( turret ) )
			break;
	}
}

// spins the minigun up to the full rate needed to fire
minigun_spinup()
{
	if ( self GetBarrelSpinRate() == 1 )
	{
		return;
	}

	self StartBarrelSpin();

	while ( self GetBarrelSpinRate() < 1 )
	{
		wait( 0.05 );
	}
}

//=====================================
// SRS TEMP - so I don't clutter generic_human with stuff I'm not using atm
/*
humveeGunner : complete nonloopsync
{
	//humvee_turret_2_passenger
	//humvee_turret_duck
	//humvee_turret_duck_left
	//humvee_turret_duck_right
	//humvee_turret_death
}
*/
