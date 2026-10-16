// split from shared.gsc 4/8/2010

#include maps\_utility;
#include animscripts\shared;
#include animscripts\utility;
#include animscripts\combat_utility;
#include common_scripts\utility;

#using_animtree( "generic_human" );

trackShootEntOrPos()
{
	self endon( "killanimscript" );
	self endon( "stop tracking" );
	self endon( "melee" );

/#
	assert( !isdefined( self.trackLoopThread ) );
	self.trackLoopThread = thisthread;
	self.trackLoopThreadType = "trackShootEntOrPos";
#/

	trackLoop( %aim_2, %aim_4, %aim_6, %aim_8 );
}

// max change in angle in 1 frame
normalDeltaChangePerFrame = 10;
largeDeltaChangePerFrame = 30;


trackLoop( aim2, aim4, aim6, aim8 )
{
	assert( isdefined( self.trackLoopThread ) );

	prevYawDelta = 0;
	prevPitchDelta = 0;
	angleDeltas = ( 0, 0, 0 );
	firstFrame = true;
	prevMotionRelativeDir = 0;
	quickTurnFrames = 0;
	deltaChangePerFrame = normalDeltaChangePerFrame;
	aimAddAngles = ( 0, 0, 0 );
	
	if ( self.type == "dog" )
	{
		doMaxAngleCheck = false;
		self.shootEnt = self.enemy;
	}
	else
	{
		doMaxAngleCheck = true;
		
		aimPitchAdd = 0;
		aimYawAdd = 0;
		
		if ( isdefined( self.coverCrouchLean_aimmode ) )
			aimPitchAdd = anim.coverCrouchLeanPitch;
		
		if ( ( self.script == "cover_left" || self.script == "cover_right" ) && isdefined( self.a.cornerMode ) && self.a.cornerMode == "lean" )
			aimYawAdd = self.coverNode.angles[ 1 ] - self.angles[ 1 ];
		
		aimAddAngles = ( aimPitchAdd, aimYawAdd, 0 );
	}
	
	for ( ;; )
	{
		prof_begin("trackLoop");

		incrAnimAimWeight();

		shootFromPos = getShootFromPos();
		
		shootPos = self.shootPos;
		if ( isdefined( self.shootEnt ) )
			shootPos = self.shootEnt getShootAtPos();

		if ( !isdefined( shootPos ) && self shouldCQB() )
			shootPos = trackLoop_CQBShootPos( shootFromPos );
	
		zeroIfNotInLimits = isdefined( self.onSnowmobile ) || isdefined( self.onATV );
		useShootAtPos = isdefined( shootPos );
		shootPosParam = ( 0, 0, 0 );
		if ( useShootAtPos )
			shootPosParam = shootPos;
			
		stepOutYaw = 0;
		useStepOutYaw = isdefined( self.stepOutYaw );
		if ( useStepOutYaw )
			stepOutYaw = self.stepOutYaw;
		
		angleDeltas = self GetAimAngle( shootFromPos, shootPosParam, useShootAtPos, aimAddAngles, stepOutYaw, useStepOutYaw, zeroIfNotInLimits );
		
		pitchDelta = angleDeltas[ 0 ];
		yawDelta = angleDeltas[ 1 ];
		angleDeltas = undefined;

		if ( quickTurnFrames > 0 )
		{
			quickTurnFrames = quickTurnFrames - 1;
			deltaChangePerFrame = max( normalDeltaChangePerFrame, deltaChangePerFrame - 5 );
		}
		else if ( self.relativeDir && self.relativeDir != prevMotionRelativeDir )
		{
			quickTurnFrames = 2;
			deltaChangePerFrame = largeDeltaChangePerFrame;
		}
		else
		{
			deltaChangePerFrame = normalDeltaChangePerFrame;
		}

		deltaChangePerFrameSq = squared( deltaChangePerFrame );

		prevMotionRelativeDir = self.relativeDir;
		
		checkDeltaChange = ( self.moveMode != "stop" ) || !firstFrame;
		

		if ( checkDeltaChange )
		{
			yawDeltaChange = yawDelta - prevYawDelta;
			if ( squared( yawDeltaChange ) > deltaChangePerFrameSq )
			{
				yawDelta = prevYawDelta + clamp( yawDeltaChange, -1 * deltaChangePerFrame, deltaChangePerFrame );
				yawDelta = clamp( yawDelta, self.leftAimLimit, self.rightAimLimit );		
			}

			pitchDeltaChange = pitchDelta - prevPitchDelta;
			if ( squared( pitchDeltaChange ) > deltaChangePerFrameSq )
			{
				pitchDelta = prevPitchDelta + clamp( pitchDeltaChange, -1 * deltaChangePerFrame, deltaChangePerFrame );
				pitchDelta = clamp( pitchDelta, self.downAimLimit, self.upAimLimit );
			}
		}

		firstFrame = false;
		prevYawDelta = yawDelta;
		prevPitchDelta = pitchDelta;
		
		trackLoop_setAnimWeights( aim2, aim4, aim6, aim8, pitchDelta, yawDelta );

		prof_end("trackLoop");
		wait( 0.05 );
	}
}


trackLoop_CQBShootPos( shootFromPos )
{
	shootPos = undefined;
	selfForward = anglesToForward( self.angles );

	if ( isdefined( self.cqb_target ) )
	{
		shootPos = self.cqb_target getShootAtPos();
		
		if ( IsDefined( self.cqb_wide_target_track ) )
		{
			AssertEx( self.cqb_wide_target_track != false , "self.cqb_wide_target_track should be either true or undefined" );
			if ( vectorDot( vectorNormalize( shootPos - shootFromPos ), selfForward ) < 0.177 )// 0.177 = cos80
				shootPos = undefined;
		}
		else if ( vectorDot( vectorNormalize( shootPos - shootFromPos ), selfForward ) < 0.643 )// 0.643 = cos50
			shootPos = undefined;
	}
	if ( !isdefined( shootPos ) && isdefined( self.cqb_point_of_interest ) )
	{
		shootPos = self.cqb_point_of_interest;
		if ( IsDefined( self.cqb_wide_poi_track ) )
		{
			AssertEx( self.cqb_wide_poi_track != false , "self.cqb_wide_poi_track should be either true or undefined" );
			if ( vectorDot( vectorNormalize( shootPos - shootFromPos ), selfForward ) < 0.177 )// 0.177 = cos80
				shootPos = undefined;
		}
		else if ( vectorDot( vectorNormalize( shootPos - shootFromPos ), selfForward ) < 0.643 )// 0.643 = cos50
			shootPos = undefined;
	}

	return shootPos;
}


trackLoop_anglesForNoShootPos( shootFromPos, aimAddAngles )
{
	assert( !isdefined( self.shootEnt ) );

	if ( recentlySawEnemy() )
	{
		shootAtOffset = ( self.enemy getShootAtPos() - self.enemy.origin );
		shootAtPos = ( self lastKnownPos( self.enemy ) + shootAtOffset );
		return trackLoop_getDesiredAngles( (shootAtPos - shootFromPos), aimAddAngles );
	}

	pitchDelta = 0;
	yawDelta = 0;

	if ( isdefined( self.node ) && isdefined( anim.isCombatScriptNode[ self.node.type ] ) && distanceSquared( self.origin, self.node.origin ) < 16 )
	{
		yawDelta = AngleClamp180( self.angles[ 1 ] - self.node.angles[ 1 ] );
	}
	else
	{
		likelyEnemyDir = self getAnglesToLikelyEnemyPath();
		if ( isdefined( likelyEnemyDir ) )
		{
			yawDelta = AngleClamp180( self.angles[ 1 ] - likelyEnemyDir[ 1 ] );
			pitchDelta = AngleClamp180( 360 - likelyEnemyDir[ 0 ] );
		}
	}

	return( pitchDelta, yawDelta, 0 );
}


trackLoop_getDesiredAngles( vectorToShootPos, aimAddAngles )
{
	anglesToShootPos = vectorToAngles( vectorToShootPos );

	stairPitchAdd = 0;
	stairYawAdd = 0;

	if ( self.stairsState == "up" )
	{
		stairPitchAdd = -40;
	}
	else if ( self.stairsState == "down" )
	{
		stairPitchAdd = 40;
		stairYawAdd = 12;
	}

	pitchDelta = 360 - anglesToShootPos[ 0 ];
	pitchDelta = AngleClamp180( pitchDelta + aimAddAngles [ 0 ] + stairPitchAdd );

	if ( isDefined( self.stepOutYaw ) )
	{
		yawDelta = self.stepOutYaw - anglesToShootPos[ 1 ];
	}
	else
	{
		yawOffset = AngleClamp180( self.desiredAngle - self.angles[ 1 ] ) * 0.5;
		yawDelta = yawOffset + self.angles[ 1 ] - anglesToShootPos[ 1 ];
	}
	yawDelta = AngleClamp180( yawDelta + aimAddAngles [ 1 ] + stairYawAdd );

	return( pitchDelta, yawDelta, 0 );
}


trackLoop_clampAngles( pitchDelta, yawDelta, doMaxAngleCheck )
{
	if ( isdefined( self.onSnowMobile ) || isdefined( self.onATV ) )
	{
		if ( yawDelta > self.rightAimLimit || yawDelta < self.leftAimLimit )
			yawDelta = 0;
		if ( pitchDelta > self.upAimLimit || pitchDelta < self.downAimLimit )
			pitchDelta = 0;
	}
	else if ( doMaxAngleCheck && ( abs( yawDelta ) > anim.maxAngleCheckYawDelta || abs( pitchDelta ) > anim.maxAngleCheckPitchDelta ) )
	{
		yawDelta = 0;
		pitchDelta = 0;
	}
	else
	{
		if ( self.gunBlockedByWall )
			yawDelta = clamp( yawDelta, -10, 10 );
		else
			yawDelta = clamp( yawDelta, self.leftAimLimit, self.rightAimLimit );
			
		pitchDelta = clamp( pitchDelta, self.downAimLimit, self.upAimLimit );
	}
	
	return( pitchDelta, yawDelta, 0 );
}

aimBlendTime = .1;

trackLoop_setAnimWeights( aim2, aim4, aim6, aim8, pitchDelta, yawDelta )
{
	if ( yawDelta > 0 )
	{
		assert( yawDelta <= self.rightAimLimit );
		weight = yawDelta / self.rightAimLimit * self.a.aimweight;
		self setAnimLimited( aim4, 0, aimBlendTime, 1, true );
		self setAnimLimited( aim6, weight, aimBlendTime, 1, true );
	}
	else if ( yawDelta < 0 )
	{
		assert( yawDelta >= self.leftAimLimit );
		weight = yawDelta / self.leftAimLimit * self.a.aimweight;
		self setAnimLimited( aim6, 0, aimBlendTime, 1, true );
		self setAnimLimited( aim4, weight, aimBlendTime, 1, true );
	}

	if ( pitchDelta > 0 )
	{
		assert( pitchDelta <= self.upAimLimit );
		weight = pitchDelta / self.upAimLimit * self.a.aimweight;
		self setAnimLimited( aim2, 0, aimBlendTime, 1, true );
		self setAnimLimited( aim8, weight, aimBlendTime, 1, true );
	}
	else if ( pitchDelta < 0 )
	{
		assert( pitchDelta >= self.downAimLimit );
		weight = pitchDelta / self.downAimLimit * self.a.aimweight;
		self setAnimLimited( aim8, 0, aimBlendTime, 1, true );
		self setAnimLimited( aim2, weight, aimBlendTime, 1, true );
	}
}


//setAnimAimWeight works just like setanimlimited on an imaginary anim node that affects the four aiming directions.
setAnimAimWeight( goalweight, goaltime )
{
	if ( !isdefined( goaltime ) || goaltime <= 0 )
	{
		self.a.aimweight = goalweight;
		self.a.aimweight_start = goalweight;
		self.a.aimweight_end = goalweight;
		self.a.aimweight_transframes = 0;
	}
	else
	{
		if ( !isdefined( self.a.aimweight ) )
			self.a.aimweight = 0;
		self.a.aimweight_start = self.a.aimweight;
		self.a.aimweight_end = goalweight;
		self.a.aimweight_transframes = int( goaltime * 20 );
	}
	self.a.aimweight_t = 0;
}


incrAnimAimWeight()
{
	if ( self.a.aimweight_t < self.a.aimweight_transframes )
	{
		self.a.aimweight_t++ ;
		t = 1.0 * self.a.aimweight_t / self.a.aimweight_transframes;
		self.a.aimweight = self.a.aimweight_start * ( 1 - t ) + self.a.aimweight_end * t;
	}
}

