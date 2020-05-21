#include maps\mp\_utility;
#include common_scripts\utility;

InitJavelinUsage()
{
	self.javelinStage = undefined;
	self.javelinPoints = undefined;
	self.javelinNormals = undefined;
	self.javelinLockMisses = undefined;
	self.javelinTargetPoint = undefined;
	self.javelinTargetNormal = undefined;
	self.javelinLockStartTime = undefined;
}


ResetJavelinLocking()
{
	if ( !IsDefined( self.javelinUseEntered ) )
		return;
	self.javelinUseEntered = undefined;

	self notify( "stop_lockon_sound" );

	self WeaponLockFree();
	self WeaponLockTargetTooClose( false );
	self WeaponLockNoClearance( false );
	self.currentlyLocking = false;
	self.currentlyLocked = false;
	self.javelinTarget = undefined;

	self StopLocalSound( "javelin_clu_lock" );
	self StopLocalSound( "javelin_clu_aquiring_lock" );

	InitJavelinUsage();
}


/#
DrawStar( point, color )
{
	Line( point + (10,0,0), point - (10,0,0), color );
	Line( point + (0,10,0), point - (0,10,0), color );
	Line( point + (0,0,10), point - (0,0,10), color );
}
#/


EyeTraceForward()
{
	origin = self GetEye();
	angles = self GetPlayerAngles();
	forward = AnglesToForward( angles );
	endpoint = origin + forward * 15000;
	
	res = BulletTrace( origin, endpoint, false, undefined );

	if ( res["surfacetype"] == "none" )
		return undefined;
	if ( res["surfacetype"] == "default" )
		return undefined;

	ent = res["entity"];
	if ( IsDefined( ent ) )
	{
		if( isdefined(level.ac130))
		{
			if( isdefined(level.ac130.planemodel) )
			{
				if ( ent == level.ac130.planeModel )
					return undefined;				
			}
		}
	}

	results = [];
	results[0] = res["position"];
	results[1] = res["normal"];
	return results;
}


LockMissesReset()
{
	self.javelinLockMisses = undefined;
}


LockMissesIncr()
{
	if ( !IsDefined( self.javelinLockMisses ) )
		self.javelinLockMisses = 1;
	else
		self.javelinLockMisses++;
}


LockMissesPassedThreshold()
{
	MAX_MISSES = 4;
	
	if ( IsDefined( self.javelinLockMisses ) && (self.javelinLockMisses >= MAX_MISSES) )
		return true;
	return false;
}


TargetPointTooClose( targetPoint )
{
	MY_MIN_DIST = 1100;

	dist = Distance( self.origin, targetPoint );
	if ( dist < MY_MIN_DIST )
		return true;

	return false;
}


LoopLocalSeekSound( alias, interval )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( "stop_lockon_sound" );

	for ( ;; )
	{
		self PlayLocalSound( alias );
		wait interval;
	}
}


TopAttackPasses( targPoint, targNormal )
{
	origin = targPoint + (targNormal * 10.0);
	endpoint = origin + (0,0,2000);

	result = BulletTrace( origin, endpoint, false, undefined );

	if ( SightTracePassed( origin, endpoint, false, undefined ) )
		return true;
	return false;
}


JavelinUsageLoop()
{
	self endon("death");
	self endon("disconnect");

	LOCK_LENGTH = 1150;
	GATHER_DELAY = 25;
	ADS_DELAY = 100;
	MAX_POINT_PEER_DIST = 400;
	POINTS_NEEDED_TO_START_LOCK = 12;

	lastGatherTime = 0;
	lastOutOfADS = 0;
	self.javelinTarget = undefined;
	
	InitJavelinUsage();

	for( ;; )
	{
		wait 0.05;

		debugDraw = false;
		if ( GetDVar( "missileDebugDraw" ) == "1" )
			debugDraw = true;

		debugText = false;
		if ( GetDVar( "missileDebugText" ) == "1" )
			debugText = true;

		weapon = self getCurrentWeapon();
		if ( !isSubStr( weapon, "javelin" ) || self isEMPed() )
		{
			ResetJavelinLocking();
			continue;
		}
		if ( self PlayerADS() < 0.95 )
		{
			lastOutOfADS = GetTime();

			ResetJavelinLocking();
			continue;
		}
		
		self.javelinUseEntered = true;
		if ( !IsDefined( self.javelinStage ) )
			self.javelinStage = 1;

		if ( self.javelinStage == 1 )	// SCANNING: try to find a good point to lock to
		{
			
			targets = maps\mp\_stinger::GetTargetList();
			if ( targets.size != 0 )
			{

				targetsInReticle = [];
				foreach ( target in targets )
				{
					insideReticle = self WorldPointInReticle_Circle( target.origin, 65, 40 );
					if ( insideReticle )
						targetsInReticle[targetsInReticle.size] = target;
				}
				
				if ( targetsInReticle.size != 0 )
				{
	
					sortedTargets = SortByDistance( targetsInReticle, self.origin );
					
					if ( !( self VehicleLockSightTest( sortedTargets[0] ) ) )
						continue;
		
					if ( debugText )
						PrintLn( "Javeling found a vehicle target to lock to." );
					
					self.javelinTarget = sortedTargets[0];
					
					if ( !isDefined( self.javelinLockStartTime ) )
						self.javelinLockStartTime = GetTime();
					
					self.javelinStage = 2;
					self.javelinLostSightlineTime = 0;
					
					self javelinLockVehicle( LOCK_LENGTH );
					self.javelinStage = 1;
					continue;
				}
			
			}
			
			if ( LockMissesPassedThreshold() )
			{
				ResetJavelinLocking();
				continue;
			}

			timePassed = GetTime() - lastOutOfADS;
			if ( timePassed < ADS_DELAY )
				continue;

			/#
			if ( debugDraw && IsDefined( self.javelinPoints ) )
			{
				foreach( javPoint in self.javelinPoints )
					DrawStar( javPoint, (0.8, 1.0, 0.8) );
				DrawStar( self.javelinPoints[self.javelinPoints.size - 1], (1, 1, 0.2) );
				DrawStar( AveragePoint( self.javelinPoints ), (0.2, 0.2, 1) );
			}
			#/

			timePassed = GetTime() - lastGatherTime;
			if ( timePassed < GATHER_DELAY )
				continue;
			lastGatherTime = GetTime();

			traceRes = (self EyeTraceForward());
			if ( !IsDefined( traceRes ) )
			{
				self LockMissesIncr();
				continue;
			}

			if ( self TargetPointTooClose( traceRes[0] ) )
			{
				self WeaponLockTargetTooClose( true );
				continue;
			}
			else
			{
				self WeaponLockTargetTooClose( false );
			}
			
			// make sure we haven't strayed too far
			if ( IsDefined( self.javelinPoints ) )
			{
				prevAvgPoint = AveragePoint( self.javelinPoints );
				dist = Distance( prevAvgPoint, traceRes[0] );
				//PrintLn( "[", self.javelinPoints.size, "] - Dist: ", dist );
				
				if ( dist > MAX_POINT_PEER_DIST )
				{
					LockMissesIncr();
					continue;
				}
			}
			else
			{
				self.javelinPoints = [];
				self.javelinNormals = [];
			}

			self.javelinPoints[self.javelinPoints.size] = traceRes[0];
			self.javelinNormals[self.javelinNormals.size] = traceRes[1];

			self LockMissesReset();
			if ( self.javelinPoints.size < POINTS_NEEDED_TO_START_LOCK )
				continue;

			// Go to stage 2:
			self.javelinTargetPoint = AveragePoint( self.javelinPoints );;
			self.javelinTargetNormal = AverageNormal( self.javelinNormals );;
			self.javelinLockMisses = undefined;
			self.javelinPoints = undefined;
			self.javelinNormals = undefined;
			self.javelinLockStartTime = GetTime();

			self WeaponLockStart( self.javelinTargetPoint );
			self thread LoopLocalSeekSound( "javelin_clu_aquiring_lock", 0.6 );

			self.javelinStage = 2;
		}

		if ( self.javelinStage == 2 )	// LOCKING: complete lockon to point
		{
			/#
			if ( debugDraw )
				DrawStar( self.javelinTargetPoint, (0.5, 1.0, 0.6) );
			#/

			insideReticle = self WorldPointInReticle_Circle( self.javelinTargetPoint, 65, 45 );
			if ( !insideReticle )
			{
				ResetJavelinLocking();
				continue;
			}

			if ( self TargetPointTooClose( self.javelinTargetPoint ) )
				self WeaponLockTargetTooClose( true );
			else
				self WeaponLockTargetTooClose( false );

			timePassed = getTime() - self.javelinLockStartTime;
			//PrintLn( "Locking [", timePassed, "]..." );
			if ( timePassed < LOCK_LENGTH )
				continue;

			self WeaponLockFinalize( self.javelinTargetPoint, (0,0,0), true );
			self notify( "stop_lockon_sound" );
			self PlayLocalSound( "javelin_clu_lock" );
			self.javelinStage = 3;
		}

		if ( self.javelinStage == 3 )	// LOCKED: try and hold it
		{
			/#
			if ( debugDraw )
				DrawStar( self.javelinTargetPoint, (0.1, 0.15, 1.0) );
			#/

			insideReticle = self WorldPointInReticle_Circle( self.javelinTargetPoint, 65, 45 );
			if ( !insideReticle )
			{
				ResetJavelinLocking();
				continue;
			}

			if ( self TargetPointTooClose( self.javelinTargetPoint ) )
				self WeaponLockTargetTooClose( true );
			else
				self WeaponLockTargetTooClose( false );

			continue;
		}	
	}
}

DebugSightLine( start, end, passed )
{
	/#
	if ( GetDVar( "missileDebugDraw" ) != "1" )
		return;

	if ( passed )
		color = ( 0.3, 1.0, 0.3 );
	else
		color = ( 1.0, 0.2, 0.2 );

	MY_OFFSET = ( 0, 0, 5 );

	Line( start + MY_OFFSET, end, color );
	#/
}

VehicleLockSightTest( target )
{
	eyePos = self GetEye();

	center = target GetPointInBounds( 0, 0, 0 );
	passed = SightTracePassed( eyePos, center, false, target );
	DebugSightLine( eyePos, center, passed );
	if ( passed )
		return true;

	front = target GetPointInBounds( 1, 0, 0 );
	passed = SightTracePassed( eyePos, front, false, target );
	DebugSightLine( eyePos, front, passed );
	if ( passed )
		return true;

	back = target GetPointInBounds( -1, 0, 0 );
	passed = SightTracePassed( eyePos, back, false, target );
	DebugSightLine( eyePos, back, passed );
	if ( passed )
		return true;

	return false;
}

javelinLockVehicle( lockLength )
{	
	if ( self.javelinStage == 2 )  // locking on to a target
	{
		self WeaponLockStart( self.javelinTarget );
		
		if ( !(self StillValidJavelinLock( self.javelinTarget ) ) )
		{
			ResetJavelinLocking();
			self.javelinLockStartTime = undefined;
			return;
		}

		passed = SoftSightTest();
		if ( !passed )
		{
			self.javelinLockStartTime = undefined;
			return;
		}
		
		if ( !isDefined( self.currentlyLocking ) || !self.currentlyLocking )
		{
			self thread LoopLocalSeekSound( "javelin_clu_aquiring_lock", 0.6 );
			self.currentlyLocking = true;
		}

		timePassed = getTime() - self.javelinLockStartTime;

		if( self _hasPerk( "specialty_fasterlockon" ) )
		{
			if( timePassed < ( lockLength * 0.5 ) )
				return;
		}
		else
		{
			if ( timePassed < lockLength )
				return;
		}
		
		//strangely buggy with the moving target...
		//javTarg = eyeTraceForward();
		//if ( !isDefined( javTarg ) )
		//	return;
		
		//topAttack = TopAttackPasses( javTarg[0], javTarg[1] );
		
		if ( isPlayer( self.javelinTarget ) )
			self WeaponLockFinalize( self.javelinTarget, (0,0,64), false );
		else
			self WeaponLockFinalize( self.javelinTarget, (0,0,0), false );
		
		
		self notify( "stop_lockon_sound" );
		
		if ( !isDefined( self.currentlyLocked ) || !self.currentlyLocked )
		{
			self PlayLocalSound( "javelin_clu_lock" );
			self.currentlyLocked = true;
		}
		
		self.javelinStage = 3;		
	}

	if ( self.javelinStage == 3 )  // target locked
	{
		passed = SoftSightTest();
		if ( !passed )
			return;

		if ( !(self StillValidJavelinLock( self.javelinTarget ) ) )
		{
			ResetJavelinLocking();
			return;
		}
	}
}	


StillValidJavelinLock( ent )
{
	assert( IsDefined( self ) );

	if ( !IsDefined( ent ) )
		return false;
	if ( !(self WorldPointInReticle_Circle( ent.origin, 65, 85 )) )
		return false;

	return true;
}


SoftSightTest()
{
	LOST_SIGHT_LIMIT = 500;

	if ( self VehicleLockSightTest( self.javelinTarget ) )
	{
		self.javelinLostSightlineTime = 0;
		return true;
	}

	if ( self.javelinLostSightlineTime == 0 )
		self.javelinLostSightlineTime = getTime();

	timePassed = GetTime() - self.javelinLostSightlineTime;

	if ( timePassed >= LOST_SIGHT_LIMIT )
	{
		ResetJavelinLocking();
		return false;
	}
	
	return true;
}
