#include maps\mp\_utility;
#include common_scripts\utility;

/******************************************************************* 
//						_harrier.gsc  
//	
//	Holds all the harrier specific functions
//	
//	Jordan Hirsh	Dec. 18th 	2008
********************************************************************/

beginHarrier( lifeId, startPoint, pos )
{
	heightEnt = GetEnt( "airstrikeheight", "targetname" );
	
	if ( isDefined( heightEnt ) )
		trueHeight = heightEnt.origin[2];
	else if( isDefined( level.airstrikeHeightScale ) )
		trueHeight = 850 * level.airstrikeHeightScale;
	else
		trueHeight = 850;
	
	pos *= (1,1,0);
	pathGoal = pos + (0,0, trueHeight );
	
	harrier = self spawnDefensiveHarrier( lifeId, self, startPoint, pathGoal );
	harrier.pathGoal = pathGoal;

	return harrier;
}

getCorrectHeight( x, y, rand )
{
	offGroundHeight = 1200;
	groundHeight = self traceGroundPoint(x,y);
	trueHeight = groundHeight + offGroundHeight;
	
	if( isDefined( level.airstrikeHeightScale ) && trueHeight < ( 850 * level.airstrikeHeightScale ) )
		trueHeight = ( 950 * level.airstrikeHeightScale );
	
	trueHeight += RandomInt( rand );
	
	return trueHeight;
}

spawnDefensiveHarrier( lifeId, owner, pathStart, pathGoal )
{
	forward = vectorToAngles( pathGoal - pathStart );

	if ( owner.team == "allies" )
		harrier = spawnHelicopter( owner, pathStart, forward, "harrier_mp" , "vehicle_av8b_harrier_jet_mp" );
	else
		harrier = spawnHelicopter( owner, pathStart, forward, "harrier_mp" , "vehicle_av8b_harrier_jet_opfor_mp" );
		
	if ( !isDefined( harrier ) )
		return;

	harrier addToHeliList();
	harrier thread removeFromHeliListOnDeath();

	harrier.speed = 250;
	harrier.accel = 175;
	harrier.health = 3000; 
	harrier.maxhealth = harrier.health;
	harrier.team = owner.team;
	harrier.owner = owner;
	harrier setCanDamage( true );
	harrier.owner = owner;
	harrier thread harrierDestroyed();
	harrier SetMaxPitchRoll( 0, 90 );		
	harrier Vehicle_SetSpeed( harrier.speed, harrier.accel );
	harrier thread playHarrierFx();
	harrier setdamagestage( 3 );
	harrier.missiles = 6;
	harrier.pers["team"] = harrier.team;
	harrier SetHoverParams( 50, 100, 50 );
	harrier setTurningAbility( 0.05 );
	harrier setYawSpeed(45,25,25,.5);
	harrier.defendLoc = pathGoal;
	harrier.lifeId = lifeId;
	
	harrier.damageCallback = ::Callback_VehicleDamage;
	
	level.harriers = array_removeUndefined( level.harriers );
	
	level.harriers[level.harriers.size] = harrier;
	
	return harrier;
}

defendLocation( harrier )
{
	harrier endon( "death" );
	assert ( isDefined( harrier ) );
	
	harrier thread harrierTimer();
	
	harrier setVehGoalPos( harrier.pathGoal, 1 );
	harrier thread closeToGoalCheck( harrier.pathGoal );
	
	harrier waittill ( "goal" );
	harrier stopHarrierWingFx();
	harrier engageGround();
}

closeToGoalCheck( pathGoal )
{
	self endon( "goal" );
	self endon( "death" );
	
	for( ;; )
	{
		if ( distance2d( self.origin, pathGoal  ) < 768 )
		{
			self SetMaxPitchRoll( 45, 25 );	
			break;
		}
		
		wait .05;
	}
}

engageGround()
{ 
	self notify( "engageGround" ); 
	self endon("engageGround");
	self endon("death");

	self thread harrierGetTargets();
	self thread randomHarrierMovement();
	
	pathGoal = self.defendLoc;

	self Vehicle_SetSpeed( 15, 5 );
	self setVehGoalPos( pathGoal, 1 );
	self waittill ( "goal" );
}

harrierLeave()
{
	self endon( "death" );
	
	self SetMaxPitchRoll( 0, 0 );
	self notify( "leaving" );
	self breakTarget( true );
	self notify("stopRand");
	
	for ( ;; )
	{
		self Vehicle_SetSpeed( 35, 25 );
		pathGoal = self.origin + ( ( AnglesToForward( ( 0, RandomInt( 360 ), 0 ) ) * 500 ) );
		pathGoal += ( 0,0,900);
		
		leaveTrace = BulletTrace(self.origin, self.origin+(0,0,900), false, self );
		if( leaveTrace["surfacetype"] == "none" )
			break;
		
		wait( 0.10 );
	}
	
	self setVehGoalPos( pathGoal, 1 );
	self thread startHarrierWingFx();
	self waittill ( "goal" );
	self playSound( "harrier_fly_away" );
	pathEnd = self getPathEnd(); 
	self Vehicle_SetSpeed( 250, 75 );
	self setVehGoalPos( pathEnd, 1 );
	self waittill ( "goal" );
	
	level.airPlane[level.airPlane.size - 1] = undefined; 

	self notify ( "harrier_gone" );
	self thread harrierDelete();
}


harrierDelete()
{
	self delete();
}

harrierTimer()
{
	self endon( "death" );
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 45 );
	self harrierLeave();
}

randomHarrierMovement()
{
	self notify( "randomHarrierMovement" ); 
	self endon("randomHarrierMovement");
	
	self endon("stopRand");
	self endon("death");
	self endon( "acquiringTarget" );
	self endon( "leaving" );
	
	pos = self.defendloc;
	
	for ( ;; )
	{
		newpos =  self GetNewPoint(self.origin); //crazy blocking call
		self setVehGoalPos( newpos, 1 );
		self waittill ("goal");	
		wait( randomIntRange( 3, 6) );
		self notify( "randMove" );
	}
}

getNewPoint( pos, targ )
{
	self endon("stopRand");
	self endon("death");
	self endon( "acquiringTarget" );
	self endon( "leaving" );
	
	if ( !isDefined( targ ) )
	{
		enemyPoints = [];
		
		foreach( player in level.players )
		{
			if ( player == self )
				continue;
			
			if ( !level.teambased || player.team != self.team )
				enemyPoints[enemyPoints.size] = player.origin;
		}
		
		if ( enemyPoints.size > 0 )
		{
			gotoPoint = AveragePoint( enemyPoints );
			
			pointX = gotoPoint[0];
			pointY = gotoPoint[1];
		}	
		else
		{
			center = level.mapCenter;
			movementDist = ( level.mapSize / 6 ) - 200; 
		
			pointX = RandomFloatRange( center[0]-movementDist, center[0]+movementDist );
			pointY = RandomFloatRange( center[1]-movementDist, center[1]+movementDist );
		}
		
		newHeight = self getCorrectHeight( pointX, PointY, 20 );
	}
	else
	{
		if( coinToss() )
		{
			directVector = self.origin - self.bestTarget.origin;
			pointX = directVector[0];
			pointY = directVector[1] * -1;
			newHeight = self getCorrectHeight( pointX, PointY, 20 );
			perpendicularVector = ( pointY,pointX,newHeight );
		
			if ( distance2D( self.origin, perpendicularVector ) > 1200 )
			{
				pointY *= .5;
				pointX *= .5;	
				perpendicularVector = ( pointY,pointX,newHeight );
			}
		}
		else
		{	
			if ( distance2D( self.origin, self.bestTarget.origin ) < 200 )
				return;
			
			yaw = self.angles[1];	
			direction = (0,yaw,0);
			moveToPoint = self.origin + ( AnglesToForward( direction ) * RandomIntRange( 200, 400 ) );
			newHeight = self getCorrectHeight( moveToPoint[0], moveToPoint[1], 20 );
			
			pointX = moveToPoint[0];
			pointY = moveToPoint[1];
		}
	}
	for ( ;; )
	{
		point =  traceNewPoint( pointX, PointY, newHeight );
		
		if ( point != 0 )
			return point;
			
		pointX = RandomFloatRange( pos[0]-1200, pos[0]+1200 );
		pointY = RandomFloatRange( pos[1]-1200, pos[1]+1200 );
		newHeight = self getCorrectHeight( pointX, PointY, 20 );
	}
}	

traceNewPoint(x,y,z)
{
	self endon("stopRand");
	self endon("death");
	self endon( "acquiringTarget" );
	self endon( "leaving" );
	self endon( "randMove" );
	
	for( i = 1 ; i <= 10 ; i++ )
	{
		
		switch( i )
		{
			case 1:
				trc = BulletTrace( self.origin, (x,y,z), false, self );
				break;
			case 2:
				trc = BulletTrace( (self getTagOrigin( "tag_left_wingtip" )), (x,y,z), false, self );
				//self thread drawLine( (self getTagOrigin( "tag_left_wingtip" )), (x,y,z), 4 );
				break;
			case 3:
				trc = BulletTrace( (self getTagOrigin( "tag_right_wingtip" )), (x,y,z), false, self );
				//self thread drawLine( (self getTagOrigin( "tag_right_wingtip" )), (x,y,z), 4 );
				break;
			case 4:
				trc = BulletTrace( (self getTagOrigin( "tag_engine_left2" )), (x,y,z), false, self );
				//self thread drawLine( (self getTagOrigin( "tag_engine_left2" )), (x,y,z), 4 );
				break;
			case 5:
				trc = BulletTrace( (self getTagOrigin( "tag_engine_right2" )), (x,y,z), false, self );
				//self thread drawLine( (self getTagOrigin( "tag_engine_right2" )), (x,y,z), 4 );
				break;
			case 6:
				trc = BulletTrace( (self getTagOrigin( "tag_right_alamo_missile" )), (x,y,z), false, self );
				//self thread drawLine( (self getTagOrigin( "tag_right_alamo_missile" )), (x,y,z), 4 );
				break;
			case 7:
				trc = BulletTrace( (self getTagOrigin( "tag_left_alamo_missile" )), (x,y,z), false, self );
				//self thread drawLine( (self getTagOrigin( "tag_left_alamo_missile" )), (x,y,z), 4 );
				break;
			case 8:
				trc = BulletTrace( (self getTagOrigin( "tag_right_archer_missile" )), (x,y,z), false, self );
				//self thread drawLine( (self getTagOrigin( "tag_right_archer_missile" )), (x,y,z), 4 );
				break;
			case 9:
				trc = BulletTrace( (self getTagOrigin( "tag_left_archer_missile" )), (x,y,z), false, self );
				//self thread drawLine( (self getTagOrigin( "tag_left_archer_missile" )), (x,y,z), 4 );
				break;
			case 10:
				trc = BulletTrace( (self getTagOrigin( "tag_light_tail" )), (x,y,z), false, self );
				//self thread drawLine( (self getTagOrigin( "tag_light_tail" )), (x,y,z), 4 );
				break;
			default:
				trc = BulletTrace( self.origin, (x,y,z), false, self );
		}
		
		if ( trc["surfacetype"] != "none" )
		{	
			return 0;
		}
		
		wait(0.05);		
	}
	
	pathGoal = ( x, y, z );
	return pathGoal;
}


traceGroundPoint(x,y)
{
	self endon("death");
	self endon( "acquiringTarget" );
	self endon( "leaving" );
	
	highTrace = -9999999;
	lowTrace = 9999999;
	z = -9999999;
	highz = self.origin[2];
	trace = undefined;
	lTrace = undefined;
	
	for( i = 1 ; i <= 5 ; i++ )
	{
		
		switch( i )
		{
			case 1:
				trc = BulletTrace( (x,y,highz), (x,y,z), false, self );
				//self thread drawLine( ( x,y,highz ), (x,y,z), 4 );
				break;
			case 2:
				trc = BulletTrace( (x+20,y+20,highz), (x+20,y+20,z), false, self );
				//self thread drawLine( ( x+20,y+20,highz ), (x+20,y+20,z), 4 );
				break;
			case 3:
				trc = BulletTrace( (x-20,y-20,highz), (x-20,y-20,z), false, self );
				//self thread drawLine( ( x-20,y-20,highz ), (x-20,y-20,z), 4 );
				break;
			case 4:
				trc = BulletTrace( (x+20,y-20,highz), (x+20,y-20,z), false, self );
				//self thread drawLine( ( x+20,y-20,highz ), (x+20,y-20,z), 4 );
				break;
			case 5:
				trc = BulletTrace( (x-20,y+20,highz), (x-20,y+20,z), false, self );
				//self thread drawLine( ( x-20,y+20,highz ), (x-20,y+20,z), 4 );
				break;	
			default:
				trc = BulletTrace( self.origin, (x,y,z), false, self );
		}
		
		if ( trc["position"][2] > highTrace )
		{
			highTrace = trc["position"][2];
			trace = trc;
		}
		else if ( trc["position"][2] < lowTrace )
		{
			lowTrace = trc["position"][2];
			lTrace = trc;
		}
		
		wait(0.05);		
	}
	
	//thread drawLine( self.origin, lTrace["position"], 5, (0,1,0) );
	//thread drawLine( self.origin, trace["position"], 5, (1,0,0) );
	
	return highTrace;
}


playHarrierFx()
{
	self endon ( "death" );

	wait( 0.2 );
	playfxontag( level.fx_airstrike_contrail, self, "tag_right_wingtip" );	
	playfxontag( level.fx_airstrike_contrail, self, "tag_left_wingtip" );
	wait( 0.2 );
	playfxontag( level.harrier_afterburnerfx, self, "tag_engine_right" );
	playfxontag( level.harrier_afterburnerfx, self, "tag_engine_left" );
	wait( 0.2 );
	playfxontag( level.harrier_afterburnerfx, self, "tag_engine_right2" );
	playfxontag( level.harrier_afterburnerfx, self, "tag_engine_left2" );
	wait( 0.2 );
	playFXOnTag( level.chopper_fx["light"]["left"], self, "tag_light_L_wing" );
	wait ( 0.2 );
	playFXOnTag( level.chopper_fx["light"]["right"], self, "tag_light_R_wing" );
	wait ( 0.2 );
	playFXOnTag( level.chopper_fx["light"]["belly"], self, "tag_light_belly" );
	wait ( 0.2 );
	playFXOnTag( level.chopper_fx["light"]["tail"], self, "tag_light_tail" );
	
}

stopHarrierWingFx()
{
	stopfxontag( level.fx_airstrike_contrail, self, "tag_right_wingtip" );
	stopfxontag( level.fx_airstrike_contrail, self, "tag_left_wingtip" );
}

startHarrierWingFx()
{
	wait ( 3.0);
	
	if ( !isDefined( self ) )
		return;
		
	playfxontag( level.fx_airstrike_contrail, self, "tag_right_wingtip" );
	playfxontag( level.fx_airstrike_contrail, self, "tag_left_wingtip" );
}

getPathStart( coord )
{
	pathRandomness = 100;
	harrierHalfDistance = 15000;
	harrierFlyHeight = 850;

	yaw = randomFloat( 360 );	
	direction = (0,yaw,0);

	startPoint = coord + ( AnglesToForward( direction ) * ( -1 * harrierHalfDistance ) );
	startPoint += ( (randomfloat(2) - 1)*pathRandomness, (randomfloat(2) - 1)*pathRandomness, 0 );
	
	return startPoint;
}

getPathEnd()
{
	pathRandomness = 150;
	harrierHalfDistance = 15000;
	harrierFlyHeight = 850;

	yaw = self.angles[1];	
	direction = (0,yaw,0);

	endPoint = self.origin + ( AnglesToForward( direction ) * harrierHalfDistance );
	return endPoint;
}

fireOnTarget( facingTolerance, zOffset )
{
	self endon("leaving");
	self endon("stopfiring");
	self endon("explode");
	self endon("death");
	self.bestTarget endon( "death" );
	self.bestTarget endon( "disconnect" );
	
	acquiredTime = getTime();
	missileTime = getTime();
	missileReady = false;
	
	self setVehWeapon( "harrier_20mm_mp" );
	
	if ( !isDefined( zOffset ) )
		zOffset = 50;

	for ( ;; )
	{
		if ( self isReadyToFire( facingTolerance ) )
			break;
		else
			wait ( .25 );
	} 
	self SetTurretTargetEnt( self.bestTarget, ( 0,0,50 ) );
	
	numShots = 25;
	
	for ( ;; )
	{
		if ( numShots == 25 )
			self playLoopSound( "weap_cobra_20mm_fire_npc" );
				
		numShots--;
		self FireWeapon( "tag_flash", self.bestTarget, (0,0,0), .05 );
		wait ( .10);
		
		if ( numShots <= 0 )
		{
			self stopLoopSound();
			wait (1);
			numShots = 25;
		}
	}
}

isReadyToFire( tolerance )
{
	self endon( "death" );
	self endon( "leaving" );
	
	if (! isdefined(tolerance) )
		tolerance = 10;
	
	harrierForwardVector = anglesToForward( self.angles );
	harrierToTarget = self.bestTarget.origin - self.origin;
	harrierForwardVector *= (1,1,0);
	harrierToTarget *= (1,1,0 );
	
	harrierToTarget = VectorNormalize( harrierToTarget );
	harrierForwardVector = VectorNormalize( harrierForwardVector );
	
	targetCosine = VectorDot( harrierToTarget, harrierForwardVector );
	facingCosine = Cos( tolerance );

	if ( targetCosine >= facingCosine )
		return true;
	else
		return false;
}

acquireGroundTarget( targets )
{
	self endon( "death" );
	self endon( "leaving" );

	if ( targets.size == 1 )
		self.bestTarget = targets[0];
	else
		self.bestTarget = self getBestTarget( targets );
	
	self backToDefendLocation( false );
	
	self notify( "acquiringTarget" );
	
	self SetTurretTargetEnt( self.bestTarget );
	self SetLookAtEnt( self.bestTarget );
	
	newpos =  self GetNewPoint(self.origin, true);
	self setVehGoalPos( newpos, 1 );
		
	self thread watchTargetDeath();
	self thread watchTargetLOS();
	
	self setVehWeapon( "harrier_20mm_mp" );
	self thread fireOnTarget(); // fires on current target.
}

backToDefendLocation( forced )
{
	self setVehGoalPos( self.defendloc, 1 );
	
	if ( isDefined( forced ) && forced )
		self waittill ( "goal" );
}


wouldCollide( destination )
{
	trace = BulletTrace( self.origin, destination, true, self );
	
	if ( trace["position"] == destination )
		return false;
	else
		return true;
}

watchTargetDeath()
{
	self notify( "watchTargetDeath" );
	self endon( "watchTargetDeath" );
	self endon( "newTarget" );
	
	self endon( "death" );
	self endon( "leaving" );

	self.bestTarget waittill( "death" );
	self thread breakTarget();
}

watchTargetLOS( tolerance )
{	
	self endon( "death" );
	self.bestTarget endon( "death" );
	self.bestTarget endon( "disconnect" );
	self endon( "leaving" );
	self endon( "newTarget" );
	lostTime = undefined;
	
	if ( !isDefined( tolerance ) )
		tolerance = 1000;
	
	for ( ;; )
	{
		if ( !isTarget( self.bestTarget ) )
		{
			self thread breakTarget();
			return;	
		}	
		
		if ( !isDefined( self.bestTarget ) )//hack to cover host migration vehicle targets
		{
			self thread breakTarget();
			return;	
		}
		
		if ( self.bestTarget sightConeTrace( self.origin, self ) < 1 )
		{		
			if ( !isDefined(lostTime) )
				lostTime = getTime();
			
			if ( getTime() - lostTime > tolerance )
			{
				self thread breakTarget();
				return;
			}
		}	
		else
		{
			lostTime = undefined;
		}
		
		wait( .25 );
	}
}

breakTarget( noNewTarget )
{
	self endon( "death" );
	
	self ClearLookAtEnt();
	self stopLoopSound();
	self notify("stopfiring");
	
	if ( isDefined(noNewTarget) && noNewTarget )
 		return;
 	
 	self thread randomHarrierMovement();
 	self notify( "newTarget" );
 	self thread harrierGetTargets();
	
}

harrierGetTargets()
{
	self notify( "harrierGetTargets" ); 
	self endon("harrierGetTargets");
	
	self endon( "death" );
	self endon( "leaving" );
	targets = [];
	
	for ( ;; )
	{
		targets = [];
		players = level.players;
		
		if ( isDefined( level.chopper ) && level.chopper.team != self.team && isAlive( level.chopper ) )
		{	
			if ( !isDefined( level.chopper.nonTarget ) || ( isDefined( level.chopper.nonTarget ) && !level.chopper.nonTarget )  )
			{
					self thread engageVehicle( level.chopper );
					return;
			}
			else
			{
				backToDefendLocation( true );		
			}
		}
			
		for (i = 0; i < players.size; i++)
		{
			potentialTarget = players[i];
			if ( isTarget( potentialTarget ) )
			{
				if( isdefined( players[i] ) )
					targets[targets.size] = players[i];
			}
			else
				continue;
			
			wait( .05 );
		}
		if ( targets.size > 0 )
		{
			self acquireGroundTarget( targets );
			return;
		}
		wait( 1 );
	}
}

isTarget( potentialTarget )
{
	self endon( "death" );
	
	if ( !isalive( potentialTarget ) || potentialTarget.sessionstate != "playing" )
		return false;
		
	if ( isDefined( self.owner ) && potentialTarget == self.owner )
		return false;
	
	if ( distance( potentialTarget.origin, self.origin ) > 8192 )
		return false;
	
	if ( Distance2D( potentialTarget.origin , self.origin ) < 768 )
		return false;
	
	if ( !isdefined( potentialTarget.pers["team"] ) )
		return false;
	
	if ( level.teamBased && potentialTarget.pers["team"] == self.team )
		return false;
	
	if ( potentialTarget.pers["team"] == "spectator" )
		return false;
	
	if ( isdefined( potentialTarget.spawntime ) && ( gettime() - potentialTarget.spawntime )/1000 <= 5 )
		return false;

	if ( potentialTarget _hasPerk( "specialty_blindeye" ) )
		return false;
	
	harrier_centroid = self.origin + ( 0, 0, -160 );
	harrier_forward_norm = anglestoforward( self.angles );
	harrier_turret_point = harrier_centroid + 144 * harrier_forward_norm;
	harrier_canSeeTarget = potentialTarget sightConeTrace( self.origin, self );
	
	if ( harrier_canSeeTarget < 1 )
		return false;	
	
	return true;
}

getBestTarget( targets )
{
	self endon( "death" );
	mainGunPointOrigin = self getTagOrigin( "tag_flash" );
	harrierOrigin = self.origin;
	harrier_forward_norm = anglestoforward( self.angles );
	
	bestYaw = undefined;
	bestTarget = undefined;
	targetHasRocket = false;
	
	foreach ( targ in targets )
	{
		angle = abs ( vectorToAngles ( ( targ.origin - self.origin ) )[1] );
		noseAngle = abs( self getTagAngles( "tag_flash" )[1] );
		angle = abs ( angle - noseAngle );			
		
		// in this calculation having a rocket removes 40d of rotation cost from best target calculation
		// to prioritize targeting dangerous targets.
		weaponsArray = targ GetWeaponsListItems();
		foreach ( weapon in weaponsArray )
		{
			if ( isSubStr( weapon, "at4" ) || isSubStr( weapon, "stinger" ) || isSubStr( weapon, "jav" ) )
				angle -= 40;
		}
		
		if ( Distance( self.origin, targ.origin ) > 2000 )
			angle += 40;
				
		if ( !isDefined( bestYaw ) )
		{				
			bestYaw = angle;
			bestTarget = targ;
		} 
		else if ( bestYaw > angle )
		{
			bestYaw = angle;
			bestTarget = targ;			
		}
	}
	
	return ( bestTarget );
}

fireMissile( missileTarget )
{
	self endon( "death" );
	self endon( "leaving" );
	
	assert( self.health > 0 );
	
	if ( self.missiles <= 0 )
		return;
	
	friendlyInRadius = self checkForFriendlies( missileTarget, 256 );
	
	if ( !isdefined( missileTarget ) )
		return;
		
	if ( Distance2D(self.origin, missileTarget.origin ) < 512 )
		return;
	
	if ( isDefined ( friendlyInRadius ) && friendlyInRadius )
		return;

	self.missiles--;
	self setVehWeapon( "harrier_FFAR_mp" );
	
	if ( isDefined( missileTarget.targetEnt ) )
		missile = self fireWeapon( "tag_flash", missileTarget.targetEnt, (0,0,-250) );
	else
		missile = self fireWeapon( "tag_flash", missileTarget, (0,0,-250) );
		
	missile Missile_SetFlightmodeDirect();
	missile Missile_SetTargetEnt( missileTarget );
}

checkForFriendlies( missileTarget, radiusSize )
{
	self endon( "death" );
	self endon( "leaving" );
	
	targets = [];
	players = level.players;
	strikePosition = missileTarget.origin;
	
	for (i = 0; i < players.size; i++)
	{
		potentialCollateral = players[i];
	
		if ( potentialCollateral.team != self.team )
			continue;
		
		potentialPosition = potentialCollateral.origin;
		
		if ( distance2D( potentialPosition, strikePosition ) < 512 )
			return true;
	}
	return false;
}

///-------------------------------------------------------
//
//		Health Functions
//
///------------------------------------------------------


Callback_VehicleDamage( inflictor, attacker, damage, dFlags, meansOfDeath, weapon, point, dir, hitLoc, timeOffset, modelIndex, partName )
{
	if ( ( attacker == self || ( isDefined( attacker.pers ) && attacker.pers["team"] == self.team ) && level.teamBased ) && ( attacker != self.owner ) )
		return;
	
	if ( self.health <= 0 )
		return;
	
	switch ( weapon )
	{
		case "ac130_105mm_mp":
		case "ac130_40mm_mp":
		case "stinger_mp":
		case "javelin_mp":
		case "remotemissile_projectile_mp":
			self.largeProjectileDamage = true;
			damage = self.maxhealth + 1;
			break;
		case "rpg_mp":
		case "at4_mp":
			self.largeProjectileDamage = true;
			damage = self.maxhealth - 900;
			break;
		default:
			if ( weapon != "none" )
				damage = Int(damage/2);
			self.largeProjectileDamage = false;
			break;
	}
	
	attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "" );
	
	if ( isPlayer( attacker ) && attacker _hasPerk( "specialty_armorpiercing" ) )
	{
		damageAdd = int( damage*level.armorPiercingMod );
		damage += damageAdd;
	}
	
	if ( self.health <= damage )
	{
		if ( isPlayer( attacker ) && (!isDefined(self.owner) || attacker != self.owner) )
		{
			thread teamPlayerCardSplash( "callout_destroyed_harrier", attacker );
			attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 300, weapon, meansOfDeath );
			thread maps\mp\gametypes\_missions::vehicleKilled( self.owner, self, undefined, attacker, damage, meansOfDeath, weapon );
			attacker notify( "destroyed_killstreak" );
		}
	
		self notify("death"); 
	}
	
	if ( self.health - damage <= 900 && ( !isDefined( self.smoking ) || !self.smoking ) )
	{
		self thread playDamageEfx();
		self.smoking = true;		
	}
	
	self Vehicle_FinishDamage( inflictor, attacker, damage, dFlags, meansOfDeath, weapon, point, dir, hitLoc, timeOffset, modelIndex, partName );
}

playDamageEfx()
{
	self endon( "death" );
	
	stopFxOnTag( level.harrier_afterburnerfx, self, "tag_engine_left" );
	playFxOnTag( level.harrier_smoke, self, "tag_engine_left" );
	
	stopFxOnTag( level.harrier_afterburnerfx, self, "tag_engine_right" );
	playFxOnTag( level.harrier_smoke, self, "tag_engine_right" );
	wait( 0.15 );
	
	stopFxOnTag( level.harrier_afterburnerfx, self, "tag_engine_left2" );
	playFxontag( level.harrier_smoke, self, "tag_engine_left2" );
		
	stopFxOnTag( level.harrier_afterburnerfx, self, "tag_engine_right2" );
	playFxontag( level.harrier_smoke, self, "tag_engine_right2" );
	playFxOnTag( level.chopper_fx["damage"]["heavy_smoke"], self, "tag_engine_left" );
}

harrierDestroyed()
{
	self endon( "harrier_gone" );
	
	self waittill( "death" );
	
	if (! isDefined(self) )
		return;

	if ( !isDefined( self.largeProjectileDamage ) )
	{
		self Vehicle_SetSpeed( 25, 5 );
		self thread harrierSpin( RandomIntRange(180, 220) );
		
		wait( RandomFloatRange( .5, 1.5 ) );
	}

	harrierExplode();
}

// crash explosion
harrierExplode()
{
	self playSound( "harrier_jet_crash" );
	level.airPlane[level.airPlane.size - 1] = undefined; 

	deathAngles = self getTagAngles( "tag_deathfx" );		
	playFx( level.harrier_deathfx, self getTagOrigin( "tag_deathfx" ), anglesToForward( deathAngles ), anglesToUp( deathAngles ) );

	self notify ( "explode" );

	wait ( 0.05 );

	self thread harrierDelete();
}


harrierSpin( speed )
{
	self endon( "explode" );
	
	playfxontag( level.chopper_fx["explode"]["medium"], self, "tag_origin" );
	
	self setyawspeed( speed, speed, speed );
	while ( isdefined( self ) )
	{
		self settargetyaw( self.angles[1]+(speed*0.9) );
		wait ( 1 );
	}
}

engageVehicle( vehTarget )
{
	vehTarget endon("death");
	vehTarget endon("leaving");
	vehTarget endon("crashing");
	self endon("death");
	
		self acquireVehicleTarget( vehTarget );

		self thread fireOnVehicleTarget();
}

fireOnVehicleTarget()
{
	self endon("leaving");
	self endon("stopfiring");
	self endon("explode");
	self.bestTarget endon ("crashing");
	self.bestTarget endon ("leaving");
	self.bestTarget endon ("death");
	
	acquiredTime = getTime();
	
	if ( isDefined( self.bestTarget ) && self.bestTarget.classname == "script_vehicle" )
	{
		self SetTurretTargetEnt( self.bestTarget );
	
		for ( ;; )
		{
			curDist = distance2D( self.origin, self.bestTarget.origin );
			
			if ( getTime() - acquiredTime >  2500 && curDist > 1000 )
			{
				self fireMissile( self.bestTarget );
				acquiredTime = getTime();
			}
			
			wait ( .10);
		}
	}
}

acquireVehicleTarget( vehTarget )
{
	self endon( "death" );
	self endon( "leaving" );
		
	self notify( "newTarget" );
	self.bestTarget = vehTarget;
	self notify( "acquiringVehTarget" );
	self SetLookAtEnt( self.bestTarget );
	self thread watchVehTargetDeath();
	self thread watchVehTargetCrash();
	
	self SetTurretTargetEnt( self.bestTarget );
}

watchVehTargetCrash()
{
	self endon( "death" );
	self endon( "leaving" );
	self.bestTarget endon ( "death" );
	self.bestTarget endon ( "drop_crate" );
	
	self.bestTarget waittill( "crashing" );
		self breakVehTarget();
}

watchVehTargetDeath()
{
	self endon( "death" );
	self endon( "leaving" );
	self.bestTarget endon ( "crashing" );
	self.bestTarget endon ( "drop_crate" );
	
	self.bestTarget waittill( "death" );
		breakVehTarget();
}

breakVehTarget()
{
	self ClearLookAtEnt();
	
	if ( isDefined( self.bestTarget ) && !isDefined( self.bestTarget.nonTarget ) )
		self.bestTarget.nonTarget = true;
	
	self notify("stopfiring");
 	self notify( "newTarget" );
 	self thread stopHarrierWingFx();
 	self thread engageGround();
}

evasiveManuverOne()
{
	self SetMaxPitchRoll( 15, 80);		
	self Vehicle_SetSpeed( 50, 100 );
	self setYawSpeed(90,30,30,.5);
	
	curOrg = self.origin;
		
	yaw = self.angles[1];	
	if( cointoss() )
		direction = (0,yaw+90,0);
	else
		direction = (0,yaw-90,0);
		
	moveToPoint = self.origin + ( AnglesToForward( direction ) * 500 );
	
	self setVehGoalPos( moveToPoint, 1 );
	//println( "evasive manuver one" );
	self waittill ("goal");
}

drawLine( start, end, timeSlice, color )
{
	if( !isdefined( color ) )
		color = ( 1,1,1 );
	
	drawTime = int(timeSlice * 15);
	for( time = 0; time < drawTime; time++ )
	{
		line( start, end, color,false, 1 );
		wait ( 0.05 );
	}
}

addToHeliList()
{
	level.helis[self getEntityNumber()] = self;	
}

removeFromHeliListOnDeath()
{
	entityNumber = self getEntityNumber();

	self waittill ( "death" );

	level.helis[entityNumber] = undefined;
}
