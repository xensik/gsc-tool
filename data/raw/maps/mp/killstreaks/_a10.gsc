#include maps\mp\_utility;
#include common_scripts\utility;

/*
	A10 killstreak: the player uses the mini-map selector to select a place to strafe
*/

init()
{
	precacheString( &"MP_WAR_AIRSTRIKE_INBOUND" );
	precacheString( &"SPLASHES_DESTROYED_A10" );
	precacheString( &"KILLSTREAKS_A10_SUPPORT" );
	precacheModel( "vehicle_a10_warthog" );	
	precacheItem( "a10_30mm_mp" );
	precacheMpAnim( "MP_A10_strafing_run" );

	// TODO: remove either one of these depending on how we show this on the minimap
	PreCacheShader( "compass_objpoint_a10_friendly" );
	PreCacheShader( "compass_objpoint_a10_enemy" );
	PrecacheMiniMapIcon( "compass_objpoint_a10_friendly" );
	PrecacheMiniMapIcon( "compass_objpoint_a10_enemy" );
	
	level.a10_fx[ "bullet_rain" ] = LoadFX( "misc/warthog_volley_runner" );
	level.a10_fx[ "bullet_impacts" ] = LoadFX( "impacts/warthog_volley_runner" );
	level.a10_fx[ "bullet_dust" ] = LoadFX( "dust/wing_drop_dust" );
	level.a10_fx[ "afterburner" ] = LoadFX( "fire/jet_afterburner" );
	level.a10_fx[ "contrail" ] = LoadFX( "smoke/jet_contrail" );
	level.a10_fx[ "wingtip_light_green" ] = LoadFX( "misc/aircraft_light_wingtip_green" );
	level.a10_fx[ "wingtip_light_red" ] = LoadFX( "misc/aircraft_light_wingtip_red" );

	level.killStreakFuncs["a10_support"] = ::tryUseA10Strike;
	level.killstreakSetupFuncs["a10_support"] = ::a10SupportSetup;

	level.a10MaxHealth = 350;
	level.a10Speed = 100;
	level.a10SpeedReduction = 75;
	level.a10StartPointOffset = 5000;
	level.a10ImpactFXDelay = 0.5;
	level.a10Damage = 200;
	level.a10DamageRadius = 384;
	level.a10DamageDelay = 0.5;
	level.a10BulletRainDelay = 0.5;
	level.a10BulletImpactsDelay = 0.5;
	level.a10EarthquakeMagnitude = 0.1;
	level.a10EarthquakeDuration = 0.5;
	level.a10EarthquakeDelay = 0.5;
	level.a10DirtEffectRadius = 350;
	level.a10ShootingGroundSoundDelay = 0.1;
	level.a10StartPositionScalar = 2000;

/#
//	PLEASE DON'T DELETE, THESE ARE QUICK DVARS FOR QUICK CHANGES IN GAME
//	SetDvarIfUninitialized( "scr_a10MaxHealth", level.a10MaxHealth );
//	SetDvarIfUninitialized( "scr_a10Speed", level.a10Speed );
//	SetDvarIfUninitialized( "scr_a10SpeedReduction", level.a10SpeedReduction );
//	SetDvarIfUninitialized( "scr_a10StartPointOffset", level.a10StartPointOffset );
//	SetDvarIfUninitialized( "scr_a10ImpactFXDelay", level.a10ImpactFXDelay );
//	SetDvarIfUninitialized( "scr_a10Damage", level.a10Damage );
//	SetDvarIfUninitialized( "scr_a10DamageRadius", level.a10DamageRadius );
//	SetDvarIfUninitialized( "scr_a10DamageDelay", level.a10DamageDelay );
//	SetDvarIfUninitialized( "scr_a10BulletRainDelay", level.a10BulletRainDelay );
//	SetDvarIfUninitialized( "scr_a10BulletImpactsDelay", level.a10BulletImpactsDelay );
//	SetDvarIfUninitialized( "scr_a10EarthquakeMagnitude", level.a10EarthquakeMagnitude );
//	SetDvarIfUninitialized( "scr_a10EarthquakeDuration", level.a10EarthquakeDuration );
//	SetDvarIfUninitialized( "scr_a10EarthquakeDelay", level.a10EarthquakeDelay );
//	SetDvarIfUninitialized( "scr_a10DirtEffectRadius", level.a10DirtEffectRadius );
//	SetDvarIfUninitialized( "scr_a10ShootingGroundSoundDelay", level.a10ShootingGroundSoundDelay );
//	SetDvarIfUninitialized( "scr_a10StartPositionScalar", level.a10StartPositionScalar );

//	level thread checkDvars();
#/
}

/#
//	PLEASE DON'T DELETE, THESE ARE QUICK DVARS FOR QUICK CHANGES IN GAME
//checkDvars()
//{
//	while( true )
//	{
//		level.a10MaxHealth = GetDvarInt( "scr_a10MaxHealth" );
//		level.a10Speed = GetDvarInt( "scr_a10Speed" );
//		level.a10SpeedReduction = GetDvarInt( "scr_a10SpeedReduction" );
//		level.a10StartPointOffset = GetDvarInt( "scr_a10StartPointOffset" );
//		level.a10ImpactFXDelay = GetDvarFloat( "scr_a10ImpactFXDelay" );
//		level.a10Damage = GetDvarInt( "scr_a10Damage" );
//		level.a10DamageRadius = GetDvarInt( "scr_a10DamageRadius" );
//		level.a10DamageDelay = GetDvarFloat( "scr_a10DamageDelay" );
//		level.a10BulletRainDelay = GetDvarFloat( "scr_a10BulletRainDelay" );
//		level.a10BulletImpactsDelay = GetDvarFloat( "scr_a10BulletImpactsDelay" );
//		level.a10EarthquakeMagnitude = GetDvarFloat( "scr_a10EarthquakeMagnitude" );
//		level.a10EarthquakeDuration = GetDvarFloat( "scr_a10EarthquakeDuration" );
//		level.a10EarthquakeDelay = GetDvarFloat( "scr_a10EarthquakeDelay" );
//		level.a10DirtEffectRadius = GetDvarFloat( "scr_a10DirtEffectRadius" );
//		level.a10ShootingGroundSoundDelay = GetDvarFloat( "scr_a10ShootingGroundSoundDelay" );
//		level.a10StartPositionScalar = GetDvarFloat( "scr_a10StartPositionScalar" );
//
//		wait( 1.0 );
//	}	
//}
#/

a10SupportSetup()
{
	self.usedUavA10 = false;
}

tryUseA10Strike( lifeID )
{
	result = undefined;
	
	if ( isDefined( level.civilianJetFlyBy ) )
	{
		self iPrintLnBold( &"MP_CIVILIAN_AIR_TRAFFIC" );
		return false;
	}

	if ( self isUsingRemote() )
	{
		return false;
	}
	
	if ( self isAirDenied() )
	{
		return false;
	}
	
	if ( self isEMPed() )
	{
		return false;
	}
	
	streakName = "a10_support";
	if( !self.usedUavA10 )
	{
		self.usedUavA10 = true;
		maps\mp\killstreaks\_uav::useUAV( streakName );		
	}

	result = self selectA10StrikeLocation( lifeId, streakName );

	if ( !isDefined( result ) || !result )
	{
		return false;
	}	

	return true;
}

selectA10StrikeLocation( lifeId, streakName )
{	
	self PlayLocalSound( "US_KS_hqr_a10" );
	self _beginLocationSelection( streakName, "map_artillery_selector", true, 500 );	
	self endon( "stop_location_selection" );

	// wait for the selection
	self waittill( "confirm_location", location, locationYaw);

	self PlayLocalSound( "US_KS_a10_inbound" );
	self thread finishA10StrikeUsage( lifeId, location, ::callA10Strike, locationYaw );

	self setblurforplayer( 0, 0.3 );

	return true;
}

finishA10StrikeUsage( lifeId, location, usedCallback, locationYaw )
{
	self notify( "used" );

	wait ( 0.05 );
	self thread stopLocationSelection( false );
	self thread [[usedCallback]]( lifeId, location, locationYaw );

	return true;
}

///////////////////////////////////////////////////
// STRIKE FUNCTIONS
//////////////////////////////////////////////////

callA10Strike( lifeId, attackPoint, yawDir )	
{
	if ( !isDefined( self ) ) 
		return;

	if ( level.teambased )
	{
		players = level.players;

		foreach( player in level.players )
		{
			playerteam = player.pers["team"];
			if ( isdefined( playerteam ) )
			{
				if ( playerteam == self.team )
					player iprintln( &"MP_WAR_AIRSTRIKE_INBOUND", self );
			}
		}
	}

	//// find underside of top of skybox
	//trace = bullettrace( level.mapCenter + (0,0,1000000), level.mapCenter, false, undefined );
	//attackPoint = (attackPoint[0], attackPoint[1], trace["position"][2] - 514);

	// Get starting and ending point for the a10
	direction = ( 0, yawDir, 0 );
	planeHalfDistance = 12000;

	startPoint = attackPoint + ( AnglesToForward( direction ) * ( -1 * planeHalfDistance ) );
	endPoint = attackPoint + ( AnglesToForward( direction ) * ( planeHalfDistance * 2 ) );

	startPoint = startPoint * (1,1,0);
	endPoint = endPoint * (1,1,0);

	trueHeight = getBestHeight( startPoint, endPoint );

	endPoint += ( 0, 0, trueHeight );
	startPoint += ( 0, 0, trueHeight );

	self endon("disconnect");

	requiredDeathCount = self.lifeId;

	level thread doA10Strike( lifeId, self, requiredDeathCount, attackPoint, startPoint, endPoint, direction, 0 );
}

getBestHeight( startPoint, endPoint )
{
	heightEnt = GetEnt( "airstrikeheight", "targetname" );
	
	spawns = level.spawnPoints;
	lowestSpawn = spawns[0];
	
	foreach( spawn in spawns )
	{
		if ( spawn.origin[2] < lowestSpawn.origin[2] )
			lowestSpawn = spawn; 
	}
	
	if ( isDefined( heightEnt ) )
		trueHeight = heightEnt.origin[2];
	else if( isDefined( level.airstrikeHeightScale ) )
		trueHeight = 850 * level.airstrikeHeightScale;
	else
		trueHeight = 850;
	
	//self thread drawLine(lowestSpawn.origin, heightEnt.origin, 120);
	
	failSafeHeight = trueHeight;
	
	highTempHeight = trueHeight;
	lowTempHeight = lowestSpawn.origin[2];
	bestHeight = undefined;
	failedTraces = 0;
	
	for ( ;; )
	{
		avgTempHeight = ( highTempHeight - lowTempHeight ) / 2 + lowTempHeight;
		primaryTrace = bulletTrace( startPoint + (0,0,avgTempHeight), endPoint + (0, 0, avgTempHeight), false, undefined );
		//self thread drawLine( startPoint + (0,0,avgTempHeight), endPoint + (0, 0, avgTempHeight), 120 );
		
		if ( primaryTrace["surfacetype"] != "none" )
		{
			lowTempHeight = avgTempHeight;
			failedTraces++;
			if ( failedTraces > 4 && isDefined( bestHeight ) )
			{
				trueHeight = bestHeight;
				break;
			}
			else if( failedTraces > 6 )
			{
				trueHeight = failSafeHeight;
				break;
			}
		}
		else
		{
			bestHeight = avgTempHeight;
			highTempHeight = avgTempHeight;	
			
			if ( avgTempHeight < lowestSpawn.origin[2] + 512 )
			{
				trueHeight = lowestSpawn.origin[2] + 512;
				break;
			}
		}
			
		wait 0.05;
	}
	
	failedTraces = 0;
	for ( ;; )
	{
		//println( "Advanced Trace" );
		
		wait 0.05;
		trace1 = bulletTrace( startPoint + (0,0,trueHeight), endPoint + (0, 0, trueHeight), false, undefined );
		trace2 = bulletTrace( startPoint + (50,50,trueHeight+50), endPoint + (50, 50, trueHeight+50), false, undefined );
		wait 0.05;
		trace3 = bulletTrace( startPoint + (-50,-50,trueHeight-50), endPoint + (-50, -50, trueHeight-50), false, undefined );
		trace4 = bulletTrace( startPoint + (50,50,trueHeight-50), endPoint + (50, 50, trueHeight-50), false, undefined );
		wait 0.05;
		trace5 = bulletTrace( startPoint + (-50,-50,trueHeight+50), endPoint + (-50, -50, trueHeight+50), false, undefined );
		
		if( trace1["surfacetype"] != "none" || trace2["surfacetype"] != "none" || trace3["surfacetype"] != "none" || trace4["surfacetype"] != "none" || trace5["surfacetype"] != "none"  )
		{
			failedTraces++;
			trueHeight += 200;
			
			if( failedTraces > 5 )
			{
				trueHeight = failSafeHeight;
				break;
			}
			continue;
		}
		break;
	}
		
	return trueHeight+175;
}

doA10Strike( lifeId, owner, requiredDeathCount, attackPoint, startPoint, endPoint, direction, initialDelay )
{
	if ( !isDefined( owner ) ) 
		return;

	a10 = spawnA10( owner, startPoint, endPoint, attackPoint, initialDelay );
	a10.lifeId = lifeId;
	a10 PlayLoopSound( "veh_mig29_dist_loop" );

	spawns = level.spawnPoints;
	highestSpawn = spawns[0];

	foreach( spawn in spawns )
	{
		if ( spawn.origin[2] > highestSpawn.origin[2] )
			highestSpawn = spawn; 
	}

	a10.killCamEnt = Spawn( "script_model", ( a10.origin[0], a10.origin[1], highestSpawn.origin[2] + 5000 ) );
	a10.killCamEnt LinkTo( a10 );
	owner.a10 = a10;

	a10 thread watchTimeOut();	
	a10 thread watchDeath();	

	a10 endon( "death" );
	
	a10 thread a10StartMove();
}

watchTimeOut()
{
	level endon( "game_ended" );
	self endon( "gone" );
	self endon( "death" );
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 35.0 );
	
	self notify( "death" );
}

a10StartMove()
{
	self endon( "death" );

	// fly in, attack, leave
	
	assert ( isDefined( self ) );
	
	wait( self.initialDelay );
		
	startPoint = self.startPoint;
	attackPoint = self.attackPoint;
	endPoint = self.endPoint;

	// the attack point needs to remain around the same height so we don't clip through buildings
	attackPoint = ( attackPoint[0], attackPoint[1], startPoint[2] - level.a10StartPointOffset );

	// figure out how long it should take to fly to this point, considering we want a standard speed, rate * time = distance
	// we are also going halfway to the attack point and slowing down
	flyDist = Distance( startPoint, attackPoint ) * 0.5;
	flySpeed = float( level.a10Speed );
	flyTime = ( flyDist / flySpeed ) / 60.0;

	// the halfway point needs to remain around the same height so we don't clip through buildings
	halfwayPoint = startPoint + ( VectorNormalize( attackPoint - startPoint ) * flyDist );
	self thread a10PlayEngineFX();
	self MoveTo( halfwayPoint, flyTime );
	wait( flyTime );

	// now go the other half of the distance slowed down
	flyDist = Distance( startPoint, attackPoint ) * 0.5;
	flySpeed = float( level.a10Speed - level.a10SpeedReduction );
	flyTime = ( flyDist / flySpeed ) / 60.0;
	
	//self thread a10PlayEngineFX();
	self MoveTo( attackPoint, flyTime );
	self thread startA10Shooting( flyTime );
	self thread monitorKills();
	wait( flyTime );
		
	// leaving
	self notify( "stopShooting" );
	
	flyDist = Distance2D( attackPoint, endPoint );
	flySpeed =  level.a10Speed;
	flyTime = ( flyDist / flySpeed ) / 60;
	self MoveTo( endPoint, flyTime );

	pitch = VectorToAngles( endPoint - attackPoint );
	
	self waittill( "movedone" );
	
	self notify( "gone" );
	
	wait( 0.5 );
	
	self removeA10();
}

// TODO: get the animation working so we don't have to do the moveto's above
//#using_animtree( "multiplayer" );
//a10StartMove()
//{
//	self endon( "death" );
//
//	// fly in, attack, leave
//
//	assert ( isDefined( self ) );
//
//	wait( self.initialDelay );
//
//	strafeAnim = %MP_A10_strafing_run;
//	animTime = GetAnimLength( strafeAnim );
//	startFrac = 1;
//	if( AnimHasNotetrack( strafeAnim, "fire_start" ) )
//	{
//		times = GetNotetrackTimes( strafeAnim, "fire_start" );
//		if( isDefined( times ) )
//			startFrac = times[ 0 ];
//	}
//	fireStartWaitTime = animTime * startFrac;
//
//	endFrac = 1;
//	if( AnimHasNotetrack( strafeAnim, "fire_end" ) )
//	{
//		times = GetNotetrackTimes( strafeAnim, "fire_end" );
//		if( isDefined( times ) )
//			endFrac = times[ 0 ];
//	}
//	fireEndWaitTime = ( animTime * endFrac ) - fireStartWaitTime;
//	lastWaitTime = animTime - ( animTime * endFrac );
//
//	//self MoveTo( self.endPoint, animTime );
//	self ScriptModelPlayAnim( "MP_A10_strafing_run" );
//
//	self thread a10PlayEngineFX();
//
//	wait( fireStartWaitTime );	
//	//self thread startA10Shooting( fireEndWaitTime );
//	//self thread monitorKills();
//
//	wait( fireEndWaitTime );	
//	self notify( "stopShooting" );
//	wait( lastWaitTime );
//
//	self removeA10();
//}

a10PlayEngineFX() // self == a10
{
	self endon ( "death" );

	wait( 0.5);
	PlayFXOnTag( level.a10_fx[ "afterburner" ], self, "tag_engine_right" );
	wait( 0.5);
	PlayFXOnTag( level.a10_fx[ "afterburner" ], self, "tag_engine_left" );
	wait( 0.5);
	PlayFXOnTag( level.a10_fx[ "contrail" ], self, "tag_right_wingtip" );
	wait( 0.5);
	PlayFXOnTag( level.a10_fx[ "contrail" ], self, "tag_left_wingtip" );
	wait( 0.5);
	PlayFXOnTag( level.a10_fx[ "wingtip_light_red" ], self, "tag_right_wingtip" );
	wait( 0.5);
	PlayFXOnTag( level.a10_fx[ "wingtip_light_green" ], self, "tag_left_wingtip" );
}

monitorKills()
{
	level endon( "game_ended" );
	self endon( "gone" );
	self endon( "death" );
	self endon( "stopShooting" );
	
	for(;;)
	{
		self waittill( "killedPlayer" );
		self.killCount++;
	}
}

// spawn at a start node and monitors it
spawnA10( owner, startPoint, endPoint, attackPoint, initialDelay )
{
	// need to move the start point up so we get a dive bombing look
	startPoint += (0, 0, level.a10StartPointOffset);
	forward = VectorToAngles( endPoint - startPoint );
	a10 = Spawn( "script_model", startPoint );
	// TODO: figure out a better way to do this
	// spawning in a plane so the minimap icon is right
	fakeA10 = spawnPlane( owner, "script_model", startPoint, "compass_objpoint_a10_friendly" , "compass_objpoint_a10_enemy" );
	
	if ( !isDefined( a10 ) )
		return;

	fakeA10 LinkTo( a10 );
	a10.fakeA10 = fakeA10;

	a10 SetModel( "vehicle_a10_warthog" );
	a10.health = 999999; 
	a10.maxhealth = level.a10MaxHealth;
	a10.damageTaken = 0;
	a10.owner = owner;
	a10.team = owner.team;
	a10.killCount = 0;
	a10.startPoint = startPoint;
	a10.endPoint = endPoint;
	a10.attackPoint = attackPoint;
	a10.initialDelay = initialDelay;
	a10.angles = forward;	

	//if ( level.teamBased )
	//{
	//	curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
	//	Objective_Add( curObjID, "active", startPoint, "compass_objpoint_a10_friendly" );
	//	Objective_Team( curObjID, a10.team );
	//	Objective_OnEntity( curObjID, a10 );
	//	a10.objIdFriendly = curObjID;

	//	curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
	//	Objective_Add( curObjID, "active", startPoint, "compass_objpoint_a10_enemy" );
	//	Objective_Team( curObjID, level.otherTeam[a10.team] );
	//	Objective_OnEntity( curObjID, a10 );
	//	a10.objIdEnemy = curObjID;
	//}

	//if ( !level.teamBased )
	//{
	//	curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
	//	Objective_Add( curObjID, "active", startPoint, "compass_objpoint_a10_friendly" );
	//	Objective_OnEntity( curObjID, a10 );
	//	a10.objIdFriendly = curObjID;
	//}

	//a10.damageCallback = ::Callback_VehicleDamage;

	return a10;
}

startA10Shooting( moveTime ) // self == a10
{
	self endon( "gone" );
	self endon( "death" );
	self endon( "stopShooting" );
	
	spawns = level.spawnPoints;
	lowestSpawn = spawns[0];

	// we have the attack point, we need to move it and damage players within the radius as we do
	start = VectorNormalize( self.origin - self.attackPoint ) * level.a10StartPositionScalar;
	start = self.attackPoint + ( start[0], start[1], 0 );
	end = VectorNormalize( self.origin - self.attackPoint ) * ( -1 * level.a10StartPositionScalar );
	end = self.attackPoint + ( end[0], end[1], 0 );
	forward = VectorNormalize( end - start );

	velocity = Distance2D( start, end ) / ( moveTime / 0.066 );

	self.a10ShootingPos = ( start[0], start[1], lowestSpawn.origin[2] - 128 );
	move = forward * velocity;

	// shoot tracer fx and start fx on the ground to look like this is destroying the area
	self thread playBulletRain();
	self thread manageShootingLoopSound();
	//wait( level.a10ImpactFXDelay );
	//self thread a10KillCam();
	self thread manageShootingGroundSound();
	//self thread playBulletImpacts();
	self thread a10Earthquake();

	while( moveTime > 0 )
	{
		foreach( player in level.players )
		{
			if( level.teambased )
			{
				if( player.team != self.owner.team )
				{
					pt = PointOnSegmentNearestToPoint( self.origin, self.a10ShootingPos, player.origin );
					if( DistanceSquared( pt, player.origin ) < ( level.a10DamageRadius * level.a10DamageRadius ) )
					{
						RadiusDamage( pt, level.a10DamageRadius, level.a10Damage, level.a10Damage, self, "MOD_RIFLE_BULLET", "a10_30mm_mp" );
					}
				}
			}
			else
			{
				pt = PointOnSegmentNearestToPoint( self.origin, self.a10ShootingPos, player.origin );
				if( DistanceSquared( pt, player.origin ) < ( level.a10DamageRadius * level.a10DamageRadius ) )
				{
					RadiusDamage( pt, level.a10DamageRadius, level.a10Damage, level.a10Damage, self, "MOD_RIFLE_BULLET", "a10_30mm_mp" );
				}
			}
		}

		// shoot a magic bullet to get destruction from destructibles
		fakeGunOrigin = self GetTagOrigin( "tag_gun" );
		for( i = 0; i < 1; i++ )
		{
			MagicBullet( "a10_30mm_mp", fakeGunOrigin, self.a10ShootingPos + ( RandomIntRange( -100, 100 ), RandomIntRange( -100, 100 ), 0 ), self.owner );
		}

		self.a10ShootingPos += ( move[0], move[1], 0 );
/#
		//level thread drawLine( self.origin, self.a10ShootingPos, 10 );
#/
		moveTime -= 0.066;
		wait( 0.05 );
	}

	//trigger_origin = self.a10ShootingPos;
	//trigger = Spawn( "trigger_radius", trigger_origin, 0, level.a10DamageRadius, Distance2D( self.origin, trigger_origin ) );
	//self.trigger = trigger;
	//self thread a10DamageInRadius( trigger );
	//while( moveTime > 0 )
	//{
	//	self.a10ShootingPos += ( move[0], move[1], 0 );
	//	trigger.origin += ( move[0], move[1], 0 );
	//	//level thread drawLine( self.origin, self.a10ShootingPos, 10 );
	//	moveTime -= 0.05;
	//	wait( 0.05 );
	//}
	//trigger delete();
	//self.trigger = undefined;
}

//a10KillCam() // self == a10
//{
//	forward = AnglesToForward( self.angles );
//
//	killCamEnt = Spawn( "script_model", self.attackPoint );
//	self.killCamEnt = killCamEnt;
//	self.owner.a10 = self;
//	killCamEnt.startTime = gettime();
//	killCamEnt.angles = forward;
//}

playBulletRain() // self == a10
{
	self endon( "gone" );
	self endon( "death" );
	self endon( "stopShooting" );

	while( true )
	{
		fakeGunOrigin = self GetTagOrigin( "tag_gun" );
		fakeGunAngles = self.a10ShootingPos - fakeGunOrigin;
		fakeGunAnglesUp = AnglesToUp( fakeGunAngles );
		PlayFX( level.a10_fx[ "bullet_rain" ], fakeGunOrigin, fakeGunAngles, fakeGunAnglesUp );
		wait( level.a10BulletRainDelay );
	}
}

manageShootingLoopSound() // self == a10
{
	ent = Spawn( "script_origin", self GetTagOrigin( "tag_gun" ) );
	if( !IsDefined( ent ) )
		return;
	ent LinkTo( self, "tag_gun" );

	ent PlayLoopSound( "pavelow_mg_loop" );
	self waittill_any( "stopShooting", "gone", "death" );
	ent StopLoopSound( "pavelow_mg_loop" );
	wait( 0.5 );
	ent delete();
}

manageShootingGroundSound() // self == a10
{
	self endon( "death" );
	self endon( "gone" );
	self endon( "stopShooting" );

	while( true )
	{
		level thread play_sound_in_space( "bullet_a10warthog_default", self.a10ShootingPos );
		wait( level.a10ShootingGroundSoundDelay );
	}
}

a10Earthquake() // self == a10
{
	self endon( "death" );
	self endon( "gone" );
	self endon( "stopShooting" );

	while( true )
	{
		PlayRumbleOnPosition( "grenade_rumble", self.a10ShootingPos );
		Earthquake( level.a10EarthquakeMagnitude, level.a10EarthquakeDuration, self.a10ShootingPos, level.a10DamageRadius );
		wii_play_grenade_rumble( self.a10ShootingPos );

		foreach ( player in level.players )
		{
			if ( player isUsingRemote() )
				continue;

			if ( distance( self.a10ShootingPos, player.origin ) > level.a10DirtEffectRadius )
				continue;

			if ( player DamageConeTrace( self.a10ShootingPos ) )
				player thread maps\mp\gametypes\_shellshock::dirtEffect( self.a10ShootingPos );
		}

		wait( level.a10EarthquakeDelay );
	}
}

//playBulletImpacts() // self == a10
//{
//	self endon( "gone" );
//	self endon( "death" );
//	self endon( "stopShooting" );
//
//	//PlayFX( level.a10_fx[ "bullet_dust" ], self.trigger.origin );
//	while( true )
//	{
//		PlayFX( level.a10_fx[ "bullet_impacts" ], self.trigger.origin );
//		wait( level.a10BulletImpactsDelay );
//	}
//}

//a10DamageInRadius( trigger ) // self == a10
//{
//	level endon( "game_ended" );
//	self endon( "death" );
//	self endon( "stopShooting" );
//
//	while( true )
//	{
//		foreach( player in level.players )
//		{
//			if( player IsTouching( trigger ) )
//			{
//				RadiusDamage( self.a10ShootingPos, level.a10DamageRadius, level.a10Damage, level.a10Damage, self, "MOD_RIFLE_BULLET", "a10_30mm_mp" );
//				RadiusDamage( self.a10ShootingPos + ( 0, 0, level.a10DamageRadius ), level.a10DamageRadius, level.a10Damage, level.a10Damage, self, "MOD_RIFLE_BULLET", "a10_30mm_mp" );
//				RadiusDamage( self.a10ShootingPos + ( 0, 0, level.a10DamageRadius * 2 ), level.a10DamageRadius, level.a10Damage, level.a10Damage, self, "MOD_RIFLE_BULLET", "a10_30mm_mp" );
//				RadiusDamage( self.a10ShootingPos + ( 0, 0, level.a10DamageRadius * 3 ), level.a10DamageRadius, level.a10Damage, level.a10Damage, self, "MOD_RIFLE_BULLET", "a10_30mm_mp" );
//			}
//		}
//
//		wait( level.a10DamageDelay );
//	}
//}

/#
drawLine( start, end, seconds )
{
	increment = seconds / 0.066;
	for( time = 0; time < increment; time++ )
	{
		Line( start, end, (1,0,0), false, 1 );
		Print3d( start, "START", (1, 0, 0) );
		Print3d( end, "END", (1, 0, 0) );
		wait ( 0.05 );
	}
}
#/

watchDeath()
{
	self endon( "gone" );	
	self waittill( "death" );
	
	self thread a10Destroyed();
}

a10Destroyed()
{
	self endon( "gone" );
	
	if (! isDefined(self) )
		return;
		
	wait( RandomFloatRange( .5, 1.5 ) );
	
	a10Explode();
}

a10Explode()
{
	//forward = ( self.origin + ( 0, 0, 1 ) ) - self.origin;

	//deathAngles = self getTagAngles( "tag_deathfx" );
	//playFx( level.chopper_fx["explode"]["air_death"]["littlebird"], self getTagOrigin( "tag_engine_left" ), anglesToForward( deathAngles ), anglesToUp( deathAngles ) );
	//
	//self playSound( "cobra_helicopter_crash" );
	self notify ( "explode" );
	
	self removeA10();
}

removeA10()
{	
	if( IsDefined( self.killCamEnt ) )
		self.killCamEnt delete();
	//if( IsDefined( self.trigger ) )
	//	self.trigger delete();
	if( IsDefined( self.fakeA10 ) )
		self.fakeA10 delete();
	//if ( isDefined( self.objIdFriendly ) )
	//	_objective_delete( self.objIdFriendly );
	//if ( isDefined( self.objIdEnemy ) )
	//	_objective_delete( self.objIdEnemy );

	self delete();	
}