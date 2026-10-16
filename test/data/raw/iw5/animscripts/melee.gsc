#include animscripts\Utility;
#include animscripts\SetPoseMovement;
#include animscripts\Combat_Utility;
#include animscripts\notetracks;
#include common_scripts\Utility;
#include maps\_utility;
#using_animtree( "generic_human" );

// ===========================================================
//     AI vs Player melee
// ===========================================================

sqr8 = 8 * 8;
sqr16 = 16 * 16;
sqr32 = 32 * 32;
sqr36 = 36 * 36;
sqr64 = 64 * 64;

MELEE_RANGE		= 64;
MELEE_RANGE_SQ	= sqr64;
MELEE_ACTOR_BOUNDS_RADIUS = 32;	// a little bigger than twice the radius of an actor's bounding box
MELEE_ACTOR_BOUNDS_RADIUS_MINUS_EPSILON = (MELEE_ACTOR_BOUNDS_RADIUS-0.1);	// used for asserts

CHARGE_RANGE_SQ = 160 * 160;
CHARGE_RANGE_SQ_VS_PLAYER = 200 * 200;

FAILED_INIT_NEXT_MELEE_TIME			= 150;			// basic IsValid() falure
FAILED_CHARGE_NEXT_MELEE_TIME		= 1500;			// charge failures (both standard/aiVSai)
FAILED_STANDARD_NEXT_MELEE_TIME		= 2500;			// standard melee failure

NOTETRACK_SYNC			=	"sync";
NOTETRACK_UNSYNC		=	"unsync";
NOTETRACK_ATTACHKNIFE	=	"attach_knife";
NOTETRACK_DETACTKNIFE	=	"detach_knife";
NOTETRACK_STAB			=	"stab";
NOTETRACK_DEATH			=	"melee_death";
NOTETRACK_INTERACT		=	"melee_interact";

KNIFE_ATTACK_MODEL		=	"weapon_parabolic_knife";
KNIFE_ATTACK_TAG		=	"TAG_INHAND";
KNIFE_ATTACK_SOUND		=	"melee_knife_hit_body";
KNIFE_ATTACK_FX_NAME	=	"melee_knife_ai";
KNIFE_ATTACK_FX_PATH	=	"impacts/flesh_hit_knife";
KNIFE_ATTACK_FX_TAG		=	"TAG_KNIFE_FX";


Melee_Init()
{
	precacheModel( KNIFE_ATTACK_MODEL );
	level._effect[ KNIFE_ATTACK_FX_NAME ] = loadfx( KNIFE_ATTACK_FX_PATH );
}

Melee_StealthCheck()
{
	if ( !isdefined( self._stealth ) )
		return false;
		
	if ( isdefined( self.ent_flag ) && isdefined( self.ent_flag[ "_stealth_enabled" ] ) && self.ent_flag[ "_stealth_enabled" ] )
		if ( isdefined( self.ent_flag[ "_stealth_attack" ] ) && !self.ent_flag[ "_stealth_attack" ] )
			return true;
			
	return false;
}


Melee_TryExecuting()
{
	// Must have a valid enemy before we try anything
	if ( !isDefined( self.enemy ) )
		return false;
		
	if ( isdefined( self.dontmelee ) )
		return false;
		
	if ( Melee_StealthCheck() )
		return false;
		
	if ( !Melee_AcquireMutex( self.enemy ) )
		return false;
		
	Melee_ResetAction();
	if ( !Melee_ChooseAction() )
	{
		Melee_ReleaseMutex( self.enemy );
		return false;
	}

	self animcustom( ::Melee_MainLoop, ::Melee_EndScript );
}


// Setup internal melee structure for sanity/cache tracking
Melee_ResetAction()
{
	assert( isDefined( self.melee ) );
	assert( isDefined( self.enemy.melee ) );
	
	self.melee.target = self.enemy;
	self.melee.initiated = false;
	self.melee.inProgress = false;
}


// After succesfully checking for melee, initialize our move
Melee_ChooseAction()
{	
	if ( !Melee_IsValid() )
		return false;
		
	self.melee.initiated = true;
	
	if ( Melee_AIvsAI_ChooseAction() )
	{
		self.melee.func = ::Melee_AIvsAI_Main;
		return true;
	}
	
	if ( Melee_Standard_ChooseAction() )
	{	
		if ( isdefined( self.specialMelee_Standard ) )
			self.melee.func = self.specialMelee_Standard;
		else
			self.melee.func = ::Melee_Standard_Main;
		return true;
	}
	
	// Don't try again for a while since we can't start
	self.melee.func = undefined;
	self.nextMeleeCheckTime = gettime() + FAILED_INIT_NEXT_MELEE_TIME;
	self.nextMeleeCheckTarget = self.melee.target;
	return false;
}


Melee_UpdateAndValidateStartPos()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	assert( isDefined( self.melee.startPos ) );
	assert( isDefined( self.melee.target ) );
	
	ignoreActors = true;
	
	// If the target is too close from the start pos, move the start pos in a way that our traces will succeed.
	distFromTarget2d = distance2d( self.melee.startPos, self.melee.target.origin );
	if ( distFromTarget2d < MELEE_ACTOR_BOUNDS_RADIUS )
	{
		// Calculate the direction from the target to the start pos, and push that start pos a bit
		dirToStartPos2d = vectorNormalize( (self.melee.startPos[0] - self.melee.target.origin[0], self.melee.startPos[1] - self.melee.target.origin[1], 0) );
		self.melee.startPos += dirToStartPos2d * (MELEE_ACTOR_BOUNDS_RADIUS - distFromTarget2d);
		
		// ToDo: At this point an AI could be below the player and cause
		// this assert. Melee logic should early out before this point 
		// if the target is above or below this AI or this should be a
		// 3D distance check. Currently this assert happens when AI are
		// below or above the player and attempt to melee. Next game - JC/Julian
		assertex( distance2d( self.melee.startPos, self.melee.target.origin ) >= (MELEE_ACTOR_BOUNDS_RADIUS_MINUS_EPSILON), "Invalid distance to target: " + distance2d( self.melee.startPos, self.melee.target.origin ) + ", should be more than " + (MELEE_ACTOR_BOUNDS_RADIUS_MINUS_EPSILON) );
		ignoreActors = false;
	}

	// Height-based checks
	floorPos = self getDropToFloorPosition( self.melee.startPos );
	if ( !isDefined( floorPos ) )
		return false;

	// Point is so far from the ground that we can't reach it, fail
	if ( abs( self.melee.startPos[2] - floorPos[2] ) > (MELEE_RANGE * 0.80) )
		return false;

	// Point is on another floor / platform, can't get that high
	if ( abs( self.origin[2] - floorPos[2] ) > (MELEE_RANGE * 0.80) )
		return false;

	// If the point is fine, update its value
	self.melee.startPos = floorPos;
	assertex( distance2d( self.melee.startPos, self.melee.target.origin ) >= (MELEE_ACTOR_BOUNDS_RADIUS_MINUS_EPSILON), "Invalid distance to target: " + distance2d( self.melee.startPos, self.melee.target.origin ) + ", should be more than " + (MELEE_ACTOR_BOUNDS_RADIUS_MINUS_EPSILON) );

	// Now check whether movement is possible to that point	

	// First check to see if we can reach our start pos
	if ( !self mayMoveToPoint( self.melee.startPos, true, ignoreActors ) )
		return false;

	// Compute a point that's just outside of the target's bounds. Do a first trace to that point which doesn't
	// ignore actors, and then a second trace which does
	
	// if we're going around a corner, the two traces will pick a point to form a 90 angle.
	// otherwise we pick a point right outside of the target's box
	if ( isDefined( self.melee.startToTargetCornerAngles ) )
	{
		// first find the corner based on the angles
		targetToStartPos = self.melee.startPos - self.melee.target.origin;
		cornerDir = anglesToForward( self.melee.startToTargetCornerAngles );
		cornerDirLen = vectorDot( cornerDir, targetToStartPos );
		mayMoveTargetOrigin = self.melee.startPos - (cornerDir * cornerDirLen);

		// push it out a bit if it's too close to the target
		cornerToTarget = self.melee.target.origin - mayMoveTargetOrigin;
		cornerToTargetLen = distance2d( self.melee.target.origin, mayMoveTargetOrigin );
		if ( cornerToTargetLen < MELEE_ACTOR_BOUNDS_RADIUS )
			mayMoveTargetOrigin -= cornerToTarget * ((MELEE_ACTOR_BOUNDS_RADIUS-cornerToTargetLen)/MELEE_ACTOR_BOUNDS_RADIUS);
	}
	else
	{
		dirToStartPos2d = vectorNormalize( (self.melee.startPos[0] - self.melee.target.origin[0], self.melee.startPos[1] - self.melee.target.origin[1], 0) );
		mayMoveTargetOrigin = self.melee.target.origin + dirToStartPos2d * MELEE_ACTOR_BOUNDS_RADIUS;
	}

	assert( isDefined( mayMoveTargetOrigin ) );

	if ( !self mayMoveFromPointToPoint( self.melee.startPos, mayMoveTargetOrigin, true, false ) )
		return false;

	if ( !self mayMoveFromPointToPoint( mayMoveTargetOrigin, self.melee.target.origin, true, true ) )
		return false;

	return true;
}


// Checks for various self / target conditions. Does not check for pathing issues.
Melee_IsValid()
{
	// Must have a target still
	if ( !isDefined( self.melee.target ) )
		return false;
		
	target = self.melee.target;
		
	if ( isdefined( target.dontMelee ) )
		return false;

	// Distance check should usually fail
	enemyDistanceSq = distanceSquared( self.origin, target.origin );
	
	if ( isdefined( self.meleeChargeDistSq ) )
		chargeDistSq = self.meleeChargeDistSq;
	else if ( isplayer( target ) )
		chargeDistSq = CHARGE_RANGE_SQ_VS_PLAYER;
	else
		chargeDistSq = CHARGE_RANGE_SQ;
		
	// Enemy isn't even close enough to initiate
	if ( !self.melee.initiated && (enemyDistanceSq > chargeDistSq) )
		return false;

	//
	// Self Checks
	//
	
	// Don't charge if we're about to die
	if ( !isAlive( self ) )
		return false;

	// Don't melee on the first frame ...
	if ( isDefined( self.a.noFirstFrameMelee ) && (self.a.scriptStartTime >= gettime() + 50) )
		return false;		

	// Prevent doing checks too often on the same target
	if ( isDefined( self.nextMeleeCheckTime ) && isDefined( self.nextMeleeCheckTarget ) && (gettime() < self.nextMeleeCheckTime) && ( self.nextMeleeCheckTarget == target ) )
		return false;

	// Can't melee if we're not standing or crouching
	if ( isdefined( self.a.onback ) || (self.a.pose == "prone") )
		return false;

	// can't melee while sidearm is out. need animations for this.
	// we rely on main loop to put away sidearm if necessary.
	if ( usingSidearm() )
		return false;

	// don't melee charge with a grenade in range, unless you have a shield
	if ( isDefined( self.grenade ) && ( self.frontShieldAngleCos == 1 ) )
		return false;
		
	//
	// Enemy checks
	//

	if ( !isAlive( target ) )
		return false;

	// no melee on enemies that are flagged as such	
	
/*
=============
///ScriptFieldDocBegin
"Name: .dontattackme"
"Summary: stops other ai from attacking this entity but not ignore them"
"Module: ai"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
	if ( isDefined( target.dontAttackMe ) || (isDefined( target.ignoreMe ) && target.ignoreMe) )
		return false;

	// no meleeing virtual targets
	if ( !isAI( target ) && !isPlayer( target ) )
		return false;
	
	if ( isAI( target ) )
	{ 
		// special state, can't allow meleeing
		if ( target isInScriptedState() )
			return false;

		// crawling/dying
		if ( target doingLongDeath() || target.delayedDeath )
			return false;
	}

	// Check if our enemy is in a proper pose to get melee'd
	if ( isPlayer( target ) )
		enemyPose = target getStance();
	else
		enemyPose = target.a.pose;

	if ( (enemyPose != "stand") && (enemyPose != "crouch") )
		return false;
		
	// Disable melee completely when both targets are invulnerable
	if ( isDefined( self.magic_bullet_shield ) && isDefined( target.magic_bullet_shield ) )
		return false;
		
	// don't melee charge with a grenade in range of the enemy
	if ( isDefined( target.grenade ) )
		return false;		
		
	//
	//	Position Checks
	//

	// Have extra tolerance when already in progress, since some animations twist the origin quite a bit ( for example standard melee )
	if ( self.melee.inProgress )
		yawThreshold = 110;
	else
		yawThreshold = 60;
		
	yawToEnemy = AngleClamp180( self.angles[ 1 ] - GetYaw( target.origin ) );
	if ( abs( yawToEnemy ) > yawThreshold )
		return false;

	// Enemy is already close enough to melee.
	if ( enemyDistanceSq <= MELEE_RANGE_SQ )		
		return true;

	// if we already started, but no longer in melee range, fail/abort
	if ( self.melee.inProgress )
		return false;
		
	// we can't melee from our position and need to charge, but failed a charge recently on the same target ; fail
	if ( isDefined( self.nextMeleeChargeTime ) && isDefined( self.nextMeleeChargeTarget ) && (gettime() < self.nextMeleeChargeTime) && (self.nextMeleeChargeTarget == target) )
		return false;
		
	return true;
}

Melee_StartMovement()
{
	self.melee.playingMovementAnim = true;
	self.a.movement = "run";
}

Melee_StopMovement()
{
	self clearanim( %body, 0.2 );
	self.melee.playingMovementAnim = undefined;
	self.a.movement = "stop";
	self orientMode( "face default" );
}


Melee_MainLoop()
{
	self endon( "killanimscript" );
	self endon( "end_melee" );	
	
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	assert( isDefined( self.melee.func ) );
	
	while( true )
	{
		prevFunc = self.melee.func;
		
		[[ self.melee.func ]]();
		
		// No more melee actions available, or no new ones, finish
		if ( !isDefined( self.melee.func ) || (prevFunc == self.melee.func) )
			break;
	}	
}

Melee_Standard_DelayStandardCharge( target )
{
	if ( !isDefined ( target ) )
		return;
		
	self.nextMeleeStandardChargeTime = getTime() + FAILED_STANDARD_NEXT_MELEE_TIME;
	self.nextMeleeStandardChargeTarget = target;
}

Melee_Standard_CheckTimeConstraints()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	assert( isDefined( self.melee.target ) );

	// out of range and too early to do a standard melee
	targetDistSq = distanceSquared( self.melee.target.origin, self.origin );
	if ( (targetDistSq > MELEE_RANGE_SQ) && isDefined( self.nextMeleeStandardChargeTime ) && isDefined( self.nextMeleeStandardChargeTarget ) && (getTime() < self.nextMeleeStandardChargeTime) && (self.nextMeleeStandardChargeTarget == self.melee.target) )
		return false;
		
	return true;
}

Melee_Standard_ChooseAction()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	assert( isDefined( self.melee.target ) );

	if ( isDefined( self.melee.target.magic_bullet_shield ) )
		return false;
		
	if ( !Melee_Standard_CheckTimeConstraints() )
		return false;
		
	if ( isdefined( self.melee.target.specialMeleeChooseAction ) )
		return false;

	return Melee_Standard_UpdateAndValidateTarget();
}

Melee_Standard_ResetGiveUpTime()
{
	if ( isdefined( self.meleeChargeDistSq ) )
		chargeDistSq = self.meleeChargeDistSq;
	else if ( isplayer( self.melee.target ) )
		chargeDistSq = CHARGE_RANGE_SQ_VS_PLAYER;
	else
		chargeDistSq = CHARGE_RANGE_SQ;
		
	if ( distanceSquared( self.origin, self.melee.target.origin ) > chargeDistSq )
		self.melee.giveUpTime = gettime() + 3000;
	else
		self.melee.giveUpTime = gettime() + 1000;
}

Melee_Standard_Main()
{
	self animMode( "zonly_physics" );

	if( Isdefined( self.melee.target ) )
		Melee_Standard_ResetGiveUpTime();

  while ( Isdefined( self.melee.target ) )
	{
		// first, charge forward if we need to; get into place to play the melee animation
		if ( !Melee_Standard_GetInPosition() )
		{
			// if we couldn't get in place to melee, don't try to charge for a little while and abort
			self.nextMeleeChargeTime = getTime() + FAILED_CHARGE_NEXT_MELEE_TIME;
			self.nextMeleeChargeTarget = self.melee.target;
			break;
		}
		
		//an early out incase our target gets remvoed wile getting into position
		if ( !isdefined( self.melee.target ) )
			break;
		
		assert( (self.a.pose == "stand") || (self.a.pose == "crouch") );
		
		self animscripts\battleChatter_ai::evaluateMeleeEvent();
		
		self orientMode( "face point", self.melee.target.origin );
		self setflaggedanimknoballrestart( "meleeanim", %melee_1, %body, 1, .2, 1 );
		self.melee.inProgress = true;
		
		// If the attack loop returns false, we need to stop this melee
		if( !Melee_Standard_PlayAttackLoop() )
		{
			// Since getting here means that we've done a melee but our attack is no longer valid, delay before we can do a standard attack again. 
			Melee_Standard_DelayStandardCharge( self.melee.target );
			break;
		}
  }

	self animMode( "none" );
}


Melee_Standard_PlayAttackLoop()
{
	while ( true )
	{
		self waittill( "meleeanim", note );
		
		if ( note == "end" )
		{
			return true;
		}
		
		if ( note == "stop" )
		{
			// check if it's worth continuing with another melee.
			// and see if we could so something better , or continue with our attacks	
			if ( !Melee_ChooseAction() )
				return false;

			// Return whether the action we choose is the same as this one, in which case we'll simply continue.
			assert( isDefined( self.melee.func ) );
			if ( self.melee.func != ::Melee_Standard_Main )
				return true;
		}
		
		if ( note == "fire" )
		{
			if ( isdefined( self.melee.target ) )
			{
				oldhealth = self.melee.target.health;
				self melee();					
				if ( isDefined( self.melee.target ) && (self.melee.target.health < oldhealth) )
					Melee_Standard_ResetGiveUpTime();
			}
		}
	}
}

// this will update our target position based on our target
Melee_Standard_UpdateAndValidateTarget()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );

	if ( !isDefined( self.melee.target ) )	
		return false;
		
	if ( !Melee_IsValid() )
		return false;
	
	dirToTarget = vectorNormalize( self.melee.target.origin - self.origin );
	self.melee.startPos = self.melee.target.origin - 40.0 * dirToTarget;
	
	return Melee_UpdateAndValidateStartPos();
}

distance2dSquared( a, b ) // should be moved to code
{
	diff = (a[0] - b[0], a[1] - b[1], 0 );
	return lengthSquared( diff );
}

// this function makes the guy run towards his enemy, and start raising his gun if he's close enough to melee.
// it will return false if he gives up, or true if he's ready to start a melee animation.
Melee_Standard_GetInPosition()
{
	if ( !Melee_Standard_UpdateAndValidateTarget() )
		return false;
		
	enemyDistanceSq = distance2dSquared( self.origin, self.melee.target.origin );

	if ( enemyDistanceSq <= MELEE_RANGE_SQ )
	{
		// just play a melee-from-standing transition
		self SetFlaggedAnimKnobAll( "readyanim", %stand_2_melee_1, %body, 1, .3, 1 );
		self animscripts\shared::DoNoteTracks( "readyanim" );
		return true;
	}

	self Melee_PlayChargeSound();

	prevEnemyPos = self.melee.target.origin;

	sampleTime = 0.1;

	raiseGunAnimTravelDist = length( getmovedelta( %run_2_melee_charge, 0, 1 ) );
	meleeAnimTravelDist = 32;
	shouldRaiseGunDist = MELEE_RANGE * 0.75 + meleeAnimTravelDist + raiseGunAnimTravelDist;
	shouldRaiseGunDistSq = shouldRaiseGunDist * shouldRaiseGunDist;

	shouldMeleeDist = MELEE_RANGE + meleeAnimTravelDist;
	shouldMeleeDistSq = shouldMeleeDist * shouldMeleeDist;

	raiseGunFullDuration = getanimlength( %run_2_melee_charge ) * 1000;
	raiseGunFinishDuration = raiseGunFullDuration - 100;
	raiseGunPredictDuration = raiseGunFullDuration - 200;
	raiseGunStartTime = 0;

	predictedEnemyDistSqAfterRaiseGun = undefined;

	runAnim = %run_lowready_F;

	if ( isplayer( self.melee.target ) && self.melee.target == self.enemy )
		self orientMode( "face enemy" );
	else
		self orientMode( "face point", self.melee.target.origin );
		
	self SetFlaggedAnimKnobAll( "chargeanim", runAnim, %body, 1, .3, 1 );
	raisingGun = false;

	while ( 1 )
	{
		time = gettime();

		willBeWithinRangeWhenGunIsRaised = ( isdefined( predictedEnemyDistSqAfterRaiseGun ) && predictedEnemyDistSqAfterRaiseGun <= shouldRaiseGunDistSq );

		if ( !raisingGun )
		{
			if ( willBeWithinRangeWhenGunIsRaised )
			{
				Melee_StartMovement();
				self SetFlaggedAnimKnobAllRestart( "chargeanim", %run_2_melee_charge, %body, 1, .2, 1 );
				raiseGunStartTime = time;
				raisingGun = true;
			}
		}
		else
		{
			// if we *are* raising our gun, don't stop unless we're hopelessly out of range,
			// or if we hit the end of the raise gun animation and didn't melee yet
			withinRangeNow = enemyDistanceSq <= shouldRaiseGunDistSq;
			if ( time - raiseGunStartTime >= raiseGunFinishDuration || ( !willBeWithinRangeWhenGunIsRaised && !withinRangeNow ) )
			{
				Melee_StartMovement();
				self SetFlaggedAnimKnobAll( "chargeanim", runAnim, %body, 1, .3, 1 );
				raisingGun = false;
			}
		}
		self DoNoteTracksForTime( sampleTime, "chargeanim" );
		
		// now that we moved a bit, see if our target moved before we check for valid melee
		// it's possible something happened in the meantime that makes meleeing impossible.
		if ( !Melee_Standard_UpdateAndValidateTarget() )
		{
			Melee_StopMovement();
			return false;
		}
		
		enemyDistanceSq = distance2dSquared( self.origin, self.melee.target.origin );
		enemyVel = ( self.melee.target.origin - prevEnemyPos ) * ( 1 / ( gettime() - time ) );// units / msec
		prevEnemyPos = self.melee.target.origin;

		// figure out where the player will be when we hit them if we (a) start meleeing now, or (b) start raising our gun now
		predictedEnemyPosAfterRaiseGun = self.melee.target.origin + ( enemyVel * raiseGunPredictDuration );
		predictedEnemyDistSqAfterRaiseGun = distance2dSquared( self.origin, predictedEnemyPosAfterRaiseGun );

		// if we're done raising our gun, and starting a melee now will hit the guy, our preparation is finished
		// when fighting non-players, don't wait for the gun raise to finish, or we'll walk through them
		if ( raisingGun && (enemyDistanceSq <= shouldMeleeDistSq) && (gettime() - raiseGunStartTime >= raiseGunFinishDuration || !isPlayer( self.melee.target )) )
			break;

		// don't keep charging if we've been doing this for too long.
		if ( !raisingGun && (gettime() >= self.melee.giveUpTime) )
		{
			Melee_StopMovement();
			return false;
		}
	}
	
	Melee_StopMovement();
	return true;
}

Melee_PlayChargeSound()
{
	if ( !isdefined( self.a.nextMeleeChargeSound ) )
		 self.a.nextMeleeChargeSound = 0;
	
	if ( ( isdefined( self.enemy ) && isplayer( self.enemy ) ) || randomint( 3 ) == 0 )
	{
		if ( gettime() > self.a.nextMeleeChargeSound )
		{
			self animscripts\face::SayGenericDialogue( "meleecharge" );
			self.a.nextMeleeChargeSound = gettime() + 8000;
		}
	}
}

// ===========================================================
//     AI vs AI synced melee
// ===========================================================


Melee_AIvsAI_Exposed_ChooseAnimationAndPosition_Flip( angleDiff )
{
	flipAngleThreshold = 90;

	// Have extra tolerance when already in progress, since some animations twist the origin quite a bit ( for example standard melee )
	if ( self.melee.inProgress )
		flipAngleThreshold += 50;

	// facing each other
	if ( abs( angleDiff ) < flipAngleThreshold )
		return false;

	target = self.melee.target;
	Melee_Decide_Winner();
	if ( self.melee.winner )
	{
		self.melee.animName = %melee_F_awin_attack;
		target.melee.animName = %melee_F_awin_defend;
		target.melee.surviveAnimName = %melee_F_awin_defend_survive;
	}
	else
	{
		self.melee.animName = %melee_F_dwin_attack;
		target.melee.animName = %melee_F_dwin_defend;			
	}

	return true;
}


Melee_AIvsAI_Exposed_ChooseAnimationAndPosition_Wrestle( angleDiff )
{
	wrestleAngleThreshold = 100;
	
	// Have extra tolerance when already in progress, since some animations twist the origin quite a bit ( for example standard melee )
	if ( self.melee.inProgress )
		wrestleAngleThreshold += 50;
	
	// facing each other
	if ( abs( angleDiff ) < wrestleAngleThreshold )
		return false;

	target = self.melee.target;

	// Attacker must be able to win	
	if ( isDefined( target.magic_bullet_shield ) )
		return false;
		
	// Attacker must be able to win	
	if ( isDefined( target.meleeAlwaysWin ) )
	{
		assert( !isDefined( self.magic_bullet_shield ) );
		return false;
	}
	
	self.melee.winner = true;
	self.melee.animName = %bog_melee_R_attack;
	target.melee.animName = %bog_melee_R_defend;
	target.melee.surviveAnimName = %bog_melee_R_backdeath2;

	return true;
}


Melee_AIvsAI_Exposed_ChooseAnimationAndPosition_Behind( angleDiff )
{
	// from behind right
	if ( (-90 > angleDiff) || (angleDiff > 0) )
		return false;

	target = self.melee.target;

	// Attacker must be able to win
	if ( isDefined( target.magic_bullet_shield ) )
		return false;
	
	// Attacker must be able to win	
	if ( isDefined( target.meleeAlwaysWin ) )
	{
		assert( !isDefined( self.magic_bullet_shield ) );
		return false;
	}

	self.melee.winner = true;
	self.melee.animName = %melee_sync_attack;
	target.melee.animName = %melee_sync_defend;

	return true;
}


Melee_AIvsAI_Exposed_ChooseAnimationAndPosition_BuildExposedList()
{
	// If this AI is forced to play a specific melee, do so!
	if ( isDefined( self.meleeForcedExposedFlip ) )
	{
		assert( !isDefined( self.meleeForcedExposedWrestle ) );	//can't force both
		exposedMelees[0] = ::Melee_AIvsAI_Exposed_ChooseAnimationAndPosition_Flip;
	}	
	else if ( isDefined( self.meleeForcedExposedWrestle ) )
	{
		exposedMelees[0] = ::Melee_AIvsAI_Exposed_ChooseAnimationAndPosition_Wrestle;
	}
	else
	{	
		// Randomize whether flip or wrestle gets tested first. Behind always tested last.
		flipIndex = randomInt( 2 );
		wrestleIndex = 1 - flipIndex;
		behindIndex = 2;
		
		exposedMelees[flipIndex]	= ::Melee_AIvsAI_Exposed_ChooseAnimationAndPosition_Flip;
		exposedMelees[wrestleIndex]	= ::Melee_AIvsAI_Exposed_ChooseAnimationAndPosition_Wrestle;
		exposedMelees[behindIndex]	= ::Melee_AIvsAI_Exposed_ChooseAnimationAndPosition_Behind;
	}

	return exposedMelees;
}


Melee_AIvsAI_Exposed_ChooseAnimationAndPosition()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee.target ) );
	
	// Choose which sequence to play based on angles
	target = self.melee.target;
	angleToEnemy = vectortoangles( target.origin - self.origin );
	angleDiff = AngleClamp180( target.angles[ 1 ] - angleToEnemy[ 1 ] );

	exposedMelees = Melee_AIvsAI_Exposed_ChooseAnimationAndPosition_BuildExposedList();
	for( i = 0; i < exposedMelees.size; i++ )
	{
		// Test each melee move in order
		if ( [[ exposedMelees[i] ]]( angleDiff ) )
		{
			assert( isDefined ( self.melee.animName ) );
			assert( isDefined ( target.melee.animName ) );

			// Calculate the position based on the chosen animation. The angles are set so that the attacker faces the enemy before linking
			self.melee.startAngles = ( 0, angleToEnemy[1], 0 );
			self.melee.startPos = getStartOrigin( target.origin, target.angles, self.melee.animName );			
			
			// Succeed if it's on a proper floor/height, we can move in position and we we have a LOS to the target
			if ( Melee_UpdateAndValidateStartPos() )
				return true;
		}
	}
	
	// No moves possible
	return false;
}

Melee_Decide_Winner()
{
	assert( isDefined( self.melee ) );
	assert( isDefined( self.melee.target ) );
	
	target = self.melee.target;
	
	// Handle script requesting an AI always win in melee
	if( isDefined( self.meleeAlwaysWin ) )
	{
		assert( !isDefined( target.magic_bullet_shield ) );
		self.melee.winner = true;
		return;
	}
	else if ( isDefined( target.meleeAlwaysWin ) )
	{
		assert( !isDefined( self.magic_bullet_shield ) );
		self.melee.winner = false;
		return;
	}
	
	// Figure out who wins
	if ( isDefined( self.magic_bullet_shield ) )
	{
		assert( !isDefined( target.magic_bullet_shield ) );
		self.melee.winner = true;
	}
	else if ( isDefined( target.magic_bullet_shield ) )
	{
		self.melee.winner = false;
	}
	else
	{
		self.melee.winner = cointoss();
	}
}

Melee_AIvsAI_SpecialCover_ChooseAnimationAndPosition()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee.target ) );
	assert( isDefined( self.melee.target.covernode ) );
	
	target = self.melee.target;
	
	Melee_Decide_Winner();

	if ( target.covernode.type == "Cover Left" )
	{
		if ( self.melee.winner )
		{
			self.melee.animName = %cornerSdL_melee_winA_attacker;
			target.melee.animName = %cornerSdL_melee_winA_defender;
			target.melee.surviveAnimName = %cornerSdL_melee_winA_defender_survive;			
		}
		else
		{
			self.melee.animName = %cornerSdL_melee_winD_attacker;
			self.melee.surviveAnimName = %cornerSdL_melee_winD_attacker_survive;
			target.melee.animName = %cornerSdL_melee_winD_defender;				
		}
	}
	else	// Right
	{
		assert( target.covernode.type == "Cover Right" );
		if ( self.melee.winner )
		{
			self.melee.animName = %cornerSdR_melee_winA_attacker;
			target.melee.animName = %cornerSdR_melee_winA_defender;
		}
		else
		{
			self.melee.animName = %cornerSdR_melee_winD_attacker;
			target.melee.animName = %cornerSdR_melee_winD_defender;
		}
	}
	
	// The start position is based on the cover node of the target		
	self.melee.startPos = getStartOrigin( target.covernode.origin, target.covernode.angles, self.melee.animName );	
	self.melee.startAngles = ( target.covernode.angles[0], AngleClamp180( target.covernode.angles[1] + 180 ), target.covernode.angles[2] ); 
	
	target.melee.faceYaw = getNodeForwardYaw( target.covernode );
	
	// Make sure we can move to the selected point ( no re-try for now )
	self.melee.startToTargetCornerAngles = target.covernode.angles;
	if ( !Melee_UpdateAndValidateStartPos() )
	{
		self.melee.startToTargetCornerAngles = undefined;
		return false;
	}
	
	return true;
}


Melee_AIvsAI_SpecialCover_CanExecute()
{
	assert( isDefined ( self ) );
	assert( isDefined ( self.melee.target ) );
	
	cover = self.melee.target.covernode;
	if ( !isDefined( cover ) )
		return false;
		
	// Make sure the enemy is hiding or leaning out and not currently exposing
	if ( (distanceSquared( cover.origin, self.melee.target.origin ) > 16) && isdefined( self.melee.target.a.coverMode ) && ( (self.melee.target.a.coverMode != "hide") && (self.melee.target.a.coverMode != "lean") ) )
		return false;

	// Must be within a some arc in front of the cover
	coverToSelfAngles = vectortoangles( self.origin - cover.origin );
	angleDiff = AngleClamp180( cover.angles[ 1 ] - coverToSelfAngles[ 1 ] );
	
	// Only do it for left/right covers for now
	if ( cover.type == "Cover Left" )
	{
		if ( (angleDiff >= -50) && (angleDiff <= 0) )
			return true;
	}
	else if ( cover.type == "Cover Right" )
	{
		if ( (angleDiff >= 0) && (angleDiff <= 50) )
			return true;
	}	
	
	return false;
}


Melee_AIvsAI_ChooseAction()
{		
	assert( isDefined( self.melee ) );
	assert( isDefined( self.melee.target ) );

	target = self.melee.target;

	// We can only do AI vs AI between human AIs
	if ( !isAI( target ) || (target.type != "human") )
		return false;

	// Can't do AIvsAI in stairs
	assert( isDefined( self.stairsState ) );
	assert( isDefined( target.stairsState ) );
	if ( (self.stairsState != "none") || (target.stairsState != "none") )
		return false;

	// If neither AI can lose, no meleeing
	if ( isdefined( self.meleeAlwaysWin ) && isdefined( target.meleeAlwaysWin ) )
		return false;
		
	// At least one of the two needs not to have bullet shield to be in melee to begin with
	assert( !isDefined( self.magic_bullet_shield ) || !isdefined( self.melee.target.magic_bullet_shield ) );	
	if ( isdefined( self.magic_bullet_shield ) && isdefined( target.magic_bullet_shield ) )
		return false;
		
	// Don't let an AI flagged to always win at melee attempt to
	// melee another AI with a bullet shield
	if	(	
			( isdefined( self.meleeAlwaysWin ) && isdefined( target.magic_bullet_shield ) )
		||	( isdefined( target.meleeAlwaysWin ) && isdefined( self.magic_bullet_shield ) )
		)
	{
		return false;
	}

	if ( isdefined( self.specialMeleeChooseAction ) )
	{
		if ( ![[ self.specialMeleeChooseAction ]]() )
			return false;
		self.melee.precisePositioning = true;
	}
	else if ( isdefined( target.specialMeleeChooseAction ) )
	{
		return false;
	}
	// If we can execute a special cover sequence, do so, otherwise revert to standard	
	else if ( Melee_AIvsAI_SpecialCover_CanExecute() && Melee_AIvsAI_SpecialCover_ChooseAnimationAndPosition() )
	{
		self.melee.precisePositioning = true;
	}
	else
	{
		if ( !Melee_AIvsAI_Exposed_ChooseAnimationAndPosition() )
			return false;
		self.melee.precisePositioning = false;
	}	

	// Save the current facing yaw if none of the behaviors requested something specific.
	if ( !isDefined ( target.melee.faceYaw ) )
		target.melee.faceYaw = target.angles[1];

	// And the offset from the target to the start pos so that we can do validity checks
	self.melee.startPosOffset = ( self.melee.startPos - target.origin );

	// If we get here, we can get to our position and an action has been chosen
	return true;
}


Melee_AIvsAI_ScheduleNoteTrackLink( target )
{
	// Set us up to get sync'd when we get the note track ( not immediately as regular melees )		
	self.melee.syncNoteTrackEnt = target;		
	target.melee.syncNoteTrackEnt = undefined;
}


Melee_AIvsAI_TargetLink( target )
{
	assert( isDefined( self ) );
	assert( isDefined( target ) );

	// If the target is no longer meleeing, don't attach (should only be valid if surviving)
	if ( !isDefined( target.melee ) )
	{
		assert( isDefined( self.melee.survive ) );
		return;
	}

	self Melee_PlayChargeSound();

	// Only attach to our target if he's still alive
	if ( !isAlive( target ) )
		return;

	// Sync up - this var needs to stay outside the melee struct because code uses it!
	self.syncedMeleeTarget = target;
	target.syncedMeleeTarget = self;
	
	self.melee.linked = true;
	target.melee.linked = true;
	self linkToBlendToTag( target, "tag_sync", true, true );
}


Melee_AIvsAI_Main()
{
	// charge to correct position
	if ( !Melee_AIvsAI_GetInPosition() )
	{
		// if we couldn't get in place to melee, don't try to charge for a little while and abort		
		self.nextMeleeChargeTime = gettime() + FAILED_CHARGE_NEXT_MELEE_TIME;
		self.nextMeleeChargeTarget = self.melee.target;
		return;
	}
	
	target = self.melee.target;

	// make sure both are still alive - get in position should have aborted otherwise
	assert( isAlive( self ) && isAlive( target ) );

	// setup linking/syncing

	// catch any leftover sync issues
	assert( !isDefined( self.syncedMeleeTarget ) );
	assert( !isDefined( target.syncedMeleeTarget ) );

	assert( isDefined( self.melee.animName ) );	
	assert( animHasNotetrack( self.melee.animName, NOTETRACK_SYNC ) );
	self Melee_AIvsAI_ScheduleNoteTrackLink( target );
	
	// Setup who gets to live
	if ( self.melee.winner )
	{
		self.melee.death = undefined;
		target.melee.death = true;
	}
	else
	{
		target.melee.death = undefined;
		self.melee.death = true;
	}
	
	// link up the two in case someone ends the script early
	self.melee.partner = target;
	target.melee.partner = self;
	
	if ( self usingSideArm() )
	{
		self forceUseWeapon( self.primaryWeapon, "primary" );
		self.lastWeapon = self.primaryWeapon;
	}
	if ( target usingSideArm() )
	{
		target forceUseWeapon( target.primaryWeapon, "primary" );
		target.lastWeapon = target.primaryWeapon;
	}

	//save weapons
	self.melee.weapon = self.weapon;
	self.melee.weaponSlot = self getCurrentWeaponSlotName();
	target.melee.weapon = target.weapon;
	target.melee.weaponSlot = target getCurrentWeaponSlotName();

	// mark melee as in progress for the initiater
	self.melee.inProgress = true;

	// Run animation on our target
	target animcustom( ::Melee_AIvsAI_Execute, ::Melee_EndScript );
	target thread Melee_AIvsAI_AnimCustomInterruptionMonitor( self );

	// release the target now that it started, we're no longer allowed to mess with it
	self.melee.target = undefined;

	// We're already in a custom, call directly
	self Melee_AIvsAI_Execute();
}

Melee_AIvsAI_AnimCustomInterruptionMonitor( attacker )
{
	assert( isDefined( attacker ) );

	self endon( "end_melee" );
	self endon( "melee_aivsai_execute" );
	
	// Wait for a couple of frames. If the execution hasn't started then, fail.
	wait 0.1;

	if ( isDefined( attacker ) )
		attacker notify( "end_melee" );

	self notify( "end_melee" );
}


Melee_AIvsAI_GetInPosition_UpdateAndValidateTarget( initialTargetOrigin, giveUpTime )
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	assert( isDefined( initialTargetOrigin ) );

	// Took too long
	if ( isDefined( giveUpTime ) && (giveUpTime <= getTime()) )
		return false;

	// Check if we can still melee while charging
	if ( !Melee_IsValid() )
		return false;
	
	target = self.melee.target;

	// If target moves too much , fail
	positionDelta = distanceSquared( target.origin, initialTargetOrigin );

	// Less tolerant to movement when the target should be in cover
	assert( isDefined( self.melee.precisePositioning ) );
	if ( self.melee.precisePositioning )
		positionThreshold = sqr16;
	else
		positionThreshold = sqr36;

	if ( positionDelta > positionThreshold )
		return false;

	// Make sure the target hasn't moved in a way that would make us unable to do the melee		
	// Update our starting position
	// Make sure target is not out of reach
 	self.melee.startPos = target.origin + self.melee.startPosOffset;
 	if ( !Melee_UpdateAndValidateStartPos() )
 		return false;
 
	return true;
}


Melee_AIvsAI_GetInPosition_IsSuccessful( initialTargetOrigin )
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	assert( isDefined( self.melee.startPos ) );
	assert( isDefined( self.melee.target ) );
	assert( isDefined( initialTargetOrigin  ) );
	
	// at the start pos
	dist2dToStartPos = distanceSquared( (self.origin[0], self.origin[1], 0), (self.melee.startPos[0], self.melee.startPos[1], 0) );
	if ( (dist2dToStartPos < sqr8) && (abs( self.melee.startPos[2] - self.origin[2] ) < MELEE_RANGE) )
		return true;

	// in between enemy and start pos
	dist2dFromStartPosToTargetSq = distanceSquared( (initialTargetOrigin[0], initialTargetOrigin[1], 0), (self.melee.startPos[0], self.melee.startPos[1], 0) );
	dist2dToTargetSq = distanceSquared( (self.origin[0], self.origin[1], 0), (self.melee.target.origin[0], self.melee.target.origin[1], 0) );
	if ( (dist2dFromStartPosToTargetSq > dist2dToTargetSq) && (abs( self.melee.target.origin[2] - self.origin[2] ) < MELEE_RANGE) )
		return true;

	return false;
}


Melee_AIvsAI_GetInPosition_Finalize( initialTargetOrigin )
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	assert( isDefined( self.melee.precisePositioning ) );
	assert( isDefined( initialTargetOrigin ) );
	
	// stop the animation and such
	Melee_StopMovement();

	if ( self.melee.precisePositioning )
	{
		assert( isDefined( self.melee.startPos ) );
		assert( isDefined( self.melee.startAngles ) );	
		
		self forceTeleport( self.melee.startPos, self.melee.startAngles );
		wait 0.05;
	}
	else
	{
		self orientMode( "face angle", self.melee.startAngles[1] );
		wait 0.05;
	}

	// Teleport might have made the sequence invalid, make sure it's still right as we exit
	return Melee_AIvsAI_GetInPosition_UpdateAndValidateTarget( initialTargetOrigin );
}


Melee_AIvsAI_GetInPosition()
{	
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	
	// Check if we can still melee while charging
	if ( !Melee_IsValid() )
		return false;		

	Melee_StartMovement();
	self clearanim( %body, 0.2 );
	self setAnimKnobAll( animscripts\run::GetRunAnim(), %body, 1, 0.2 );
	self animMode( "zonly_physics" );
	self.keepClaimedNode = true;

	giveUpTime = getTime() + 1500;

	assert( isDefined( self.melee.target ) );
	assert( isDefined( self.melee.target.origin ) );
	initialTargetOrigin = self.melee.target.origin;

	/#
	self notify ( "MDBG_att_getInPosition", self.melee.target );
	self.melee.target notify ( "MDBG_def_getInPosition", self );
	#/

	while ( Melee_AIvsAI_GetInPosition_UpdateAndValidateTarget( initialTargetOrigin, giveUpTime ) )
	{
		if ( Melee_AIvsAI_GetInPosition_IsSuccessful( initialTargetOrigin ) )
			return Melee_AIvsAI_GetInPosition_Finalize( initialTargetOrigin );

		// play run forward anim
		self orientMode( "face point", self.melee.startPos );
		wait .05;
	}

	Melee_StopMovement();
	return false;
}


Melee_AIvsAI_Execute()
{
	self endon( "killanimscript" );
	self endon( "end_melee" );
	
	self notify( "melee_aivsai_execute" );
	
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );

	self animMode( "zonly_physics" );
	self.a.special = "none";
	self.specialDeathFunc = undefined;

	// Check whether something makes us drop our weapon. If we get revived we'll need to restore it
	self thread Melee_DroppedWeaponMonitorThread();
	
	// Check for our partner ending melee early, for getting saved etc
	self thread Melee_PartnerEndedMeleeMonitorThread();

	// If we have faceYaw specified, use them, otherwise stay oriented as we were
	if ( isDefined( self.melee.faceYaw ) )
		self orientMode( "face angle", self.melee.faceYaw );
	else
		self orientMode( "face current" );
	
	// only have standing melees for now, set these with notetracks
	self.a.pose = "stand";
	self clearanim( %body, 0.2 );
	
	// Disable some interruptions if we're going to die, we don't want to break out of melee
	if ( isDefined( self.melee.death ) )
		self Melee_DisableInterruptions();

	// Start the base animation, and loop over the note tracks until one of them tell us to stop	
	self setFlaggedAnimKnobAllRestart( "meleeAnim", self.melee.animName, %body, 1, 0.2 );
	endNote = self animscripts\shared::DoNoteTracks( "meleeAnim", ::Melee_HandleNoteTracks );

	// If the survival animation stopped us, play it now
	if ( (endNote == NOTETRACK_DEATH) && isDefined( self.melee.survive ) )
	{
		// If we dropped our weapon but we got saved, restore it immediately
		Melee_DroppedWeaponRestore();
		
		self setflaggedanimknoballrestart( "meleeAnim", self.melee.surviveAnimName, %body, 1, 0.2 );
		endNote = self animscripts\shared::DoNoteTracks( "meleeAnim", ::Melee_HandleNoteTracks );
	}

	// If we're marked for death, make sure we die before exiting
	if ( isDefined( self.melee ) && isDefined( self.melee.death ) )
		self kill();

	// note sure what this does:
	self.keepClaimedNode = false;
}


Melee_DisableInterruptions()
{
	//save the states so we can restore them
	self.melee.wasAllowingPain = self.allowPain;
	self.melee.wasFlashbangImmune = self.flashBangImmunity;
	
	//disable what makes sense
	self disable_pain();
	self setFlashbangImmunity( true );
}


Melee_NeedsWeaponSwap()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	return ( isDefined( self.melee.weapon ) && (self.melee.weapon != "none") && (self.weapon != self.melee.weapon) );
}


Melee_DroppedWeaponRestore()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );

	// Give back the weapon we had initially, if we had one, and we dropped it
	if ( self.weapon != "none" && self.lastWeapon != "none" )
		return;
		
	// If we did not have one to begin with, not much we can do
	if ( !isDefined( self.melee.weapon ) || (self.melee.weapon == "none") )
		return;		

	// Immediately swap the weapon. Can't animate when ending the script, and we don't want to when playing the revive
	self forceUseWeapon( self.melee.weapon, self.melee.weaponSlot );
	
	// if we dropped the item, destroy it
	if ( isDefined( self.melee.droppedWeaponEnt ) )
	{
		self.melee.droppedWeaponEnt delete();
		self.melee.droppedWeaponEnt = undefined;
	}
}


Melee_DroppedWeaponMonitorThread()
{
	self endon( "killanimscript" );
	self endon( "end_melee" );
	assert( isDefined( self.melee ) );

	self waittill( "weapon_dropped", droppedWeapon );

	// the weapon drop might fail if in solid and such. droppedWeapon would be 'removed entity' in that case.
	if ( isDefined( droppedWeapon ) )
	{
		assert( isDefined( self.melee ) );
		self.melee.droppedWeaponEnt = droppedWeapon;
	}
}


Melee_PartnerEndedMeleeMonitorThread_ShouldAnimSurvive()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );

	// Doesn't have a survival animation set
	if ( !isDefined( self.melee.surviveAnimName ) )
		return false;

	// Too early if before they interact
	if ( !isDefined( self.melee.surviveAnimAllowed ) )
		return false;

	return true;
}


Melee_PartnerEndedMeleeMonitorThread()
{
	self endon( "killanimscript" );
	self endon( "end_melee" );
	assert( isDefined( self.melee ) );
	
	self waittill( "partner_end_melee" );
	
	if ( isDefined( self.melee.death ) )
	{
		// partner ended the melee, and we're supposed to die. end the script
		if ( isDefined( self.melee.animatedDeath ) || isDefined( self.melee.interruptDeath ) )
		{
			self kill();
		}
		else
		{
			// don't die!
			self.melee.death = undefined;

			// partner ended before we decided we'd die, we should revive now
			if ( Melee_PartnerEndedMeleeMonitorThread_ShouldAnimSurvive() )
			{
				assert ( animHasNotetrack( self.melee.animName, NOTETRACK_DEATH ) );			
				self.melee.survive = true;				
			}
			else
			{
				self notify( "end_melee" );
			}
		}
	}
	else
	{
		// if we're not doing the last part of the animation, end immediately
		if ( !isDefined( self.melee.unsyncHappened ) )
			self notify( "end_melee" );
	}
}



Melee_Unlink()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );

	if ( !isDefined( self.melee.linked ) )
		return;
	
	// Unlink our sync'd target first, because our own unlink will clear this information
	if ( isDefined( self.syncedMeleeTarget ) )
		self.syncedMeleeTarget Melee_UnlinkInternal();

	self Melee_UnlinkInternal();
}


Melee_UnlinkInternal()
{
	assert( isDefined( self ) );

	self unlink();
	self.syncedMeleeTarget = undefined;

	if ( !isAlive( self ) )
		return;

	assert( isDefined( self.melee ) );
	assert( isDefined( self.melee.linked ) );
	self.melee.linked = undefined;

	self animMode( "zonly_physics" );
	self orientMode( "face angle", self.angles[1] );
}


Melee_HandleNoteTracks_Unsync()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	
	self Melee_Unlink();
	
	// let the AIs know that the unsync happened, which changes the interruption behavior
	self.melee.unsyncHappened = true;
	if ( isDefined( self.melee.partner ) && isDefined( self.melee.partner.melee ) )
		self.melee.partner.melee.unsyncHappened = true;
}


Melee_HandleNoteTracks_ShouldDieAfterUnsync()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );

	if ( animHasNotetrack( self.melee.animName, NOTETRACK_DEATH ) )
	{
		assert( isDefined( self.melee.surviveAnimName ) );
		return false;
	}

	return isdefined( self.melee.death );
}


Melee_HandleNoteTracks_Death( interruptAnimation )
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	assert( isdefined( self.melee.death ) );

	// set whether we should die immediately if melee were to end, or finish playing the animation
	if ( isDefined( interruptAnimation ) && interruptAnimation )
		self.melee.interruptDeath = true;
	else
		self.melee.animatedDeath = true;
}


Melee_HandleNoteTracks( note )
{
	if ( isSubStr( note, "ps_" ) )
	{
		alias = GetSubStr( note, 3 );
		self playSound( alias );
		return;
	}

	if ( note == NOTETRACK_SYNC )
	{	
		if ( isDefined( self.melee.syncNoteTrackEnt ) )
		{
			self Melee_AIvsAI_TargetLink( self.melee.syncNoteTrackEnt );
			self.melee.syncNoteTrackEnt = undefined;
		}
	}
	else if ( note == NOTETRACK_UNSYNC )
	{
		self Melee_HandleNoteTracks_Unsync();

		// After the targets unsync, the final 'death' sequence is usually played, and we want to handle the pre-corpse sequence ourself.
		// We could add a seperate note track too, if this turns out not to be precise enough.
		if ( Melee_HandleNoteTracks_ShouldDieAfterUnsync() )
			Melee_HandleNoteTracks_Death();
	}
	else if ( note == NOTETRACK_INTERACT )
	{
		// From this point on, it's okay to get revived by the animation
		self.melee.surviveAnimAllowed = true;
	}
	else if ( note == NOTETRACK_DEATH )
	{
		// Check if we got saved. If we did, play the alternate ending
		if ( isDefined( self.melee.survive ) )
		{
			assert( !isdefined( self.melee.death ) );
			assert( isDefined( self.melee.surviveAnimName ) );

			// Interrupt the waiting loop so that we may start a new one with the survival animation
			return note;
		}

		assert( isdefined( self.melee.death ) );
		Melee_HandleNoteTracks_Death();
		
		if ( isDefined( self.melee.animatedDeath ) )
			return note; // abort DoNoteTracks so we do our death immediately.
	}
	else if ( note == NOTETRACK_ATTACHKNIFE )
	{	
		self attach( KNIFE_ATTACK_MODEL, KNIFE_ATTACK_TAG, true );
		self.melee.hasKnife = true;
	}
	else if ( note == NOTETRACK_DETACTKNIFE )
	{
		self detach( KNIFE_ATTACK_MODEL, KNIFE_ATTACK_TAG, true );
		self.melee.hasKnife = undefined;
	}
	else if ( note == NOTETRACK_STAB )
	{
		assert( isDefined( self.melee.hasKnife ) );
		
		// Play the knife effect
		self playsound( KNIFE_ATTACK_SOUND );
		playfxontag( level._effect[ KNIFE_ATTACK_FX_NAME ], self, KNIFE_ATTACK_FX_TAG );
		
		// make sure the target dies after being stabbed if he's still doing the melee
		if ( isDefined( self.melee.partner ) && isDefined( self.melee.partner.melee ) )
			self.melee.partner Melee_HandleNoteTracks_Death( true );
	}
}


Melee_DeathHandler_Regular()
{
	self endon( "end_melee" );
	self animscripts\shared::DropAllAIWeapons();
	return false;	//play regular death
}


Melee_DeathHandler_Delayed()
{
	self endon( "end_melee" );
	self animscripts\notetracks::DoNoteTracksWithTimeout( "meleeAnim", 10.0 );
	self animscripts\shared::DropAllAIWeapons();
	self startRagdoll();
	
	return true;	//skip regular death
}


Melee_EndScript_CheckDeath()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );

	if ( !isAlive( self ) && isDefined( self.melee.death ) )
	{
		if ( isDefined( self.melee.animatedDeath ) )
			self.deathFunction = ::Melee_DeathHandler_Delayed;
		else
			self.deathFunction = ::Melee_DeathHandler_Regular;
	}
}


Melee_EndScript_CheckPositionAndMovement()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	
	if ( !isAlive( self ) )
		return;
	
	// make sure we're not marked as moving anymore
	if ( isDefined( self.melee.playingMovementAnim ) )
		Melee_StopMovement();

	// Adjust Ground Position
	newOrigin = self getDropToFloorPosition();
	if ( isDefined ( newOrigin ) )
		self forceTeleport( newOrigin, self.angles );
	else
		println( "Warning: Melee animation might have ended up in solid for entity #" + self getentnum() );
}


Melee_EndScript_CheckWeapon()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );
	
	// melee ended with the knife equipped, remove it
	if ( isDefined( self.melee.hasKnife ) )
		self detach( KNIFE_ATTACK_MODEL, KNIFE_ATTACK_TAG, true );

	// If we dropped our weapon but we didn't die, restore it
	if ( isAlive( self ) )
		Melee_DroppedWeaponRestore();
}


Melee_EndScript_CheckStateChanges()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );

	// Restore interruption-based state changes

	if ( isDefined( self.melee.wasAllowingPain ) )
	{
		if ( self.melee.wasAllowingPain )
			self enable_pain();
		else
			self disable_pain();
	}

	if ( isDefined( self.melee.wasFlashbangImmune ) )
		self setFlashbangImmunity( self.melee.wasFlashbangImmune );
}


Melee_EndScript()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee ) );

	self Melee_Unlink();
	self Melee_EndScript_CheckDeath();
	self Melee_EndScript_CheckPositionAndMovement();
	self Melee_EndScript_CheckWeapon();
	self Melee_EndScript_CheckStateChanges();

	// End the melee prematurely for the other sync'd ent when someone dies/script ends
	if ( isDefined( self.melee.partner ) )
		self.melee.partner notify( "partner_end_melee" );	

	self Melee_ReleaseMutex( self.melee.target );
}


Melee_AcquireMutex( target )
{
	assert( isDefined( self ) );
	assert( isDefined( target ) );
	
	// Can't acquire when soemone is targeting us for a melee
	if ( isDefined( self.melee ) )
		return false;
	
	// Can't acquire enemy mutex if he's already in a melee process
	if ( isDefined( target.melee ) )
		return false;

	self.melee = spawnStruct();
	target.melee = spawnStruct();
	
	return true;
}


Melee_ReleaseMutex( target )
{
	assert( isDefined( self ) );
	self.melee = undefined;

	if ( isDefined( target ) )
		target.melee = undefined;
}
