#include maps\mp\_utility;

InitStingerUsage()
{
	self.stingerStage = undefined;
	self.stingerTarget = undefined;
	self.stingerLockStartTime = undefined;
	self.stingerLostSightlineTime = undefined;
	
	self thread ResetStingerLockingOnDeath();
	level.stingerTargets = [];
}


ResetStingerLocking()
{
	if ( !IsDefined( self.stingerUseEntered ) )
		return;
	self.stingerUseEntered = undefined;

	self notify( "stop_javelin_locking_feedback" );
	self notify( "stop_javelin_locked_feedback" );

	self WeaponLockFree();
	InitStingerUsage();
}


ResetStingerLockingOnDeath()
{
	self endon( "disconnect" );

	self notify ( "ResetStingerLockingOnDeath" );
	self endon ( "ResetStingerLockingOnDeath" );

	for ( ;; )
	{
		self waittill( "death" );
		self ResetStingerLocking();
	}
}


StillValidStingerLock( ent )
{
	assert( IsDefined( self ) );

	if ( !IsDefined( ent ) )
		return false;
	if ( !(self WorldPointInReticle_Circle( ent.origin, 65, 85 )) )
		return false;

	//if ( self.stingerTarget == level.ac130.planeModel && !isDefined( level.ac130player ) )
	//	return false;

	return true;
}


LoopStingerLockingFeedback()
{
	self endon( "stop_javelin_locking_feedback" );

	for ( ;; )
	{
		if ( isDefined( level.chopper ) && isDefined( level.chopper.gunner ) && isDefined( self.stingerTarget ) && self.stingerTarget == level.chopper.gunner )
			level.chopper.gunner playLocalSound( "missile_locking" );

		if ( isDefined( level.ac130player ) && isDefined( self.stingerTarget ) && self.stingerTarget == level.ac130.planeModel )
			level.ac130player playLocalSound( "missile_locking" );
		
		self playLocalSound( "stinger_locking" );
		//*self PlayRumbleOnEntity( "ac130_25mm_fire" );

		wait 0.6;
	}
}


LoopStingerLockedFeedback()
{
	self endon( "stop_javelin_locked_feedback" );

	for ( ;; )
	{
		if ( isDefined( level.chopper ) && isDefined( level.chopper.gunner ) && isDefined( self.stingerTarget ) && self.stingerTarget == level.chopper.gunner )
			level.chopper.gunner playLocalSound( "missile_locking" );

		if ( isDefined( level.ac130player ) && isDefined( self.stingerTarget ) && self.stingerTarget == level.ac130.planeModel )
			level.ac130player playLocalSound( "missile_locking" );

		self playLocalSound( "stinger_locked" );
		//*self PlayRumbleOnEntity( "ac130_25mm_fire" );

		wait 0.25;
	}
}


/#
DrawStar( point )
{
	Line( point + (10,0,0), point - (10,0,0) );
	Line( point + (0,10,0), point - (0,10,0) );
	Line( point + (0,0,10), point - (0,0,10) );
}
#/


LockSightTest( target )
{
	eyePos = self GetEye();
	
	if ( !isDefined( target ) ) //targets can disapear during targeting.
		return false;
	
	passed = SightTracePassed( eyePos, target.origin, false, target );
	if ( passed )
		return true;

	front = target GetPointInBounds( 1, 0, 0 );
	passed = SightTracePassed( eyePos, front, false, target );
	if ( passed )
		return true;

	back = target GetPointInBounds( -1, 0, 0 );
	passed = SightTracePassed( eyePos, back, false, target );
	if ( passed )
		return true;

	return false;
}


StingerDebugDraw( target )
{
/#
	if ( GetDVar( "missileDebugDraw" ) != "1" )
		return;
	if ( !IsDefined( target ) )
		return;

	org = target.origin;
	DrawStar( org );
	org = target GetPointInBounds( 1, 0, 0 );
	DrawStar( org );
	org = target GetPointInBounds( -1, 0, 0 );
	DrawStar( org );
#/
}


SoftSightTest()
{
	LOST_SIGHT_LIMIT = 500;

	if ( self LockSightTest( self.stingerTarget ) )
	{
		self.stingerLostSightlineTime = 0;
		return true;
	}

	if ( self.stingerLostSightlineTime == 0 )
		self.stingerLostSightlineTime = getTime();

	timePassed = GetTime() - self.stingerLostSightlineTime;
	//PrintLn( "Losing sight of target [", timePassed, "]..." );

	if ( timePassed >= LOST_SIGHT_LIMIT )
	{
		//PrintLn( "Lost sight of target." );
		ResetStingerLocking();
		return false;
	}
	
	return true;
}

GetTargetList()
{
	targets = [];

	if ( level.teamBased )
	{
		if ( IsDefined( level.chopper ) && ( level.chopper.team != self.team || level.chopper.owner == self ) )
			targets[targets.size] = level.chopper;

		if ( IsDefined( level.ac130player ) && level.ac130player.team != self.team )
			targets[targets.size] = level.ac130.planemodel;
		
		if ( IsDefined( level.harriers) )
		{
			foreach( harrier in level.harriers )
			{
				if ( IsDefined( harrier ) && ( harrier.team != self.team || ( IsDefined( harrier.owner ) && harrier.owner == self ) ) )
					targets[targets.size] = harrier;
			}
		}
	
		if ( level.UAVModels[level.otherTeam[self.team]].size )
		{
			foreach ( UAV in level.UAVModels[level.otherTeam[self.team]] )
				targets[targets.size] = UAV;
		}

		if ( IsDefined( level.littleBirds ) )
		{
			foreach ( lb in level.littleBirds )
			{
				if ( !IsDefined( lb ) )
					continue;
				
				if ( self.team != lb.owner.team || self == lb.owner )
					targets[targets.size] = lb;
			}
		}
		
		if ( IsDefined( level.ugvs ) )
		{
			foreach ( ugv in level.ugvs )
			{
				if ( !IsDefined( ugv ) )
					continue;

				if ( self.team != ugv.owner.team || self == ugv.owner )
					targets[targets.size] = ugv;
			}
		}

		//This exposes missile tracking issues - CUT IW5 Jordan
		/*
		foreach ( player in level.players )
		{
			if ( !isAlive( player ) )
				continue;

			if ( level.teamBased && player.team == self.team )
				continue;
				
			if ( player == self )
				continue;
	
			if ( player isJuggernaut() )
				targets[targets.size] = player;
		}
		*/

	}
	else
	{
		if ( IsDefined( level.chopper ) ) //check for teams IW5: ( level.chopper.owner != self )
			targets[targets.size] = level.chopper;

		if ( isDefined( level.ac130player ) )
			targets[targets.size] = level.ac130.planemodel;
		
		if ( isDefined( level.harriers) )
		{
			foreach( harrier in level.harriers )
			{
				if ( isDefined( harrier ) )
					targets[targets.size] = harrier;
			}
		}

		if ( level.UAVModels.size )
		{
			foreach ( ownerGuid, UAV in level.UAVModels )
			{
				if ( isDefined( UAV.owner ) && UAV.owner == self )
					continue;
					
				targets[targets.size] = UAV;
			}
		}
		
		if ( isDefined( level.littleBirds ) )
		{
			foreach ( lb in level.littleBirds )
			{
				if ( !isDefined( lb ) )
					continue;

				targets[targets.size] = lb;
			}
		}

		if ( IsDefined( level.ugvs ) )
		{
			foreach ( ugv in level.ugvs )
			{
				if ( !IsDefined( ugv ) )
					continue;

				targets[targets.size] = ugv;
			}
		}

		foreach ( player in level.players )
		{
			if ( !isAlive( player ) )
				continue;

			if ( level.teamBased && player.team == self.team )
				continue;
				
			if ( player == self )
				continue;
	
			if ( player isJuggernaut() )
				targets[targets.size] = player;
		}
		
	}
	
	return targets;
}


StingerUsageLoop()
{
	self endon("death");
	self endon("disconnect");

	LOCK_LENGTH = 1000;

	InitStingerUsage();

	for( ;; )
	{
		wait 0.05;

		weapon = self getCurrentWeapon();
		
		if ( weapon != "stinger_mp" && weapon != "at4_mp" && weapon != "iw5_smaw_mp" )
		{
			ResetStingerLocking();
			continue;
		}

		if ( self PlayerADS() < 0.95 )
		{
			ResetStingerLocking();
			continue;
		}

		self.stingerUseEntered = true;

		if ( !IsDefined( self.stingerStage ) )
			self.stingerStage = 0;

		StingerDebugDraw( self.stingerTarget );

		if ( self.stingerStage == 0 )  // searching for target
		{
			targets = GetTargetList();
			if ( targets.size == 0 )
				continue;

			targetsInReticle = [];
			foreach ( target in targets )
			{
				if ( !isDefined( target ) )
					continue;
				
				insideReticle = self WorldPointInReticle_Circle( target.origin, 65, 75 );
				
				if ( insideReticle )
					targetsInReticle[targetsInReticle.size] = target;
			}
			if ( targetsInReticle.size == 0 )
				continue;

			sortedTargets = SortByDistance( targetsInReticle, self.origin );
			if ( !( self LockSightTest( sortedTargets[0] ) ) )
				continue;

			//PrintLn( "Found a target to lock to..." );
			thread LoopStingerLockingFeedback();
			self.stingerTarget = sortedTargets[0];
			self.stingerLockStartTime = GetTime();
			self.stingerStage = 1;
			self.stingerLostSightlineTime = 0;
		}

		if ( self.stingerStage == 1 )  // locking on to a target
		{
			if ( !(self StillValidStingerLock( self.stingerTarget )) )
			{
				//PrintLn( "Failed to get lock." );
				ResetStingerLocking();
				continue;
			}

			passed = SoftSightTest();
			if ( !passed )
				continue;

			timePassed = getTime() - self.stingerLockStartTime;
			//PrintLn( "Locking [", timePassed, "]..." );
			if( self _hasPerk( "specialty_fasterlockon" ) )
			{
				if( timePassed < ( LOCK_LENGTH * 0.5 ) )
					continue;
			}
			else
			{
				if ( timePassed < LOCK_LENGTH )
					continue;
			}

			self notify( "stop_javelin_locking_feedback" );
			thread LoopStingerLockedFeedback();

			//PrintLn( "Locked!");
			if ( self.stingerTarget.model == "vehicle_av8b_harrier_jet_opfor_mp" || self.stingerTarget.model == "vehicle_av8b_harrier_jet_mp"  || self.stingerTarget.model == "vehicle_little_bird_armed_mp" )
				self WeaponLockFinalize( self.stingerTarget );
			else if ( isPlayer( self.stingerTarget ) )
				self WeaponLockFinalize( self.stingerTarget, ( 100,0, 64 ) );			
			else
				self WeaponLockFinalize( self.stingerTarget, ( 100,0,-32 ) );
			
			self.stingerStage = 2;		
		}

		if ( self.stingerStage == 2 )  // target locked
		{
			passed = SoftSightTest();
			if ( !passed )
				continue;

			if ( !(self StillValidStingerLock( self.stingerTarget )) )
			{
				//PrintLn( "Gave up lock." );
				ResetStingerLocking();
				continue;
			}
		}
	}
}
