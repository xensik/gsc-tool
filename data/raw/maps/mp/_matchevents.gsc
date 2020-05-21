#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;


//////////////////////////////////////////////
//
//	Initialization



//	add this back to common_mp_weapons.csv
//	nodamage rocket for visual only
//weapon,mp/nodamage_rocket_mp


init()
{
	level.match_events_fx["smoke"] = loadFx( "smoke/smoke_grenade_11sec_mp" );
	level.match_events_fx["tracer"] = loadFx( "misc/tracer_incoming" );
	level.match_events_fx["explosion"] = loadFx( "explosions/building_explosion_huge_gulag" );	
	
	
	//precacheItem( "nodamage_rocket_mp" );
	
	level.matchEvents["mortar"] = ::doMortar;
	level.matchEvents["smoke"] = ::doSmoke;
	level.matchEvents["airstrike"] = ::doAirstrike;
	level.matchEvents["pavelow"] = ::doPavelow;
	level.matchEvents["heli_insertion"] = ::doHeliInsertion;
	level.matchEvents["osprey_insertion"] = ::doOspreyInsertion;
	
	level.matchEventStarted = false;
	//level thread onPlayerConnect();
}


onPlayerConnect()
{
	for ( ;; )
	{
		level waittill( "connected", player );
		player thread onPlayerSpawned();
	}
}


onPlayerSpawned()
{
	self endon( "disconnect" );
	level endon( "matchevent_started" );
	
	self waittill( "spawned_player" );	
	
	if ( level.matchEventStarted == false )
	{
		level.matchEventStarted = true;
		if ( cointoss() )
			self thread [[ random(level.matchEvents) ]]();
		level notify( "matchevent_started" );
	}			
}


//////////////////////////////////////////////
//
//	Utilities


getMapCenter()
{
	if ( isDefined( level.mapCenter ) )
		return level.mapCenter;
	
	alliesStart = GetEntArray( "mp_tdm_spawn_allies_start", "classname" );
	axisStart = GetEntArray( "mp_tdm_spawn_axis_start", "classname" );		
	if ( isDefined( alliesStart ) && isDefined( alliesStart[0] ) && isDefined( axisStart ) && isDefined( axisStart[0] ) )
	{
		halfDist = Distance( alliesStart[0].origin, axisStart[0].origin ) / 2;
		dir = vectorToAngles( alliesStart[0].origin - axisStart[0].origin );
		dir = vectorNormalize( dir );
		return alliesStart[0].origin + dir*halfDist;
	}
	return (0,0,0);	
}


getStartSpawns()
{
	alliesStart = GetEntArray( "mp_tdm_spawn_allies_start", "classname" );
	axisStart = GetEntArray( "mp_tdm_spawn_axis_start", "classname" );	
	
	if ( isDefined( alliesStart ) && isDefined( alliesStart[0] ) && isDefined( axisStart ) && isDefined( axisStart[0] ) )
	{
		startSpawns = [];
		startSpawns["axis"] = axisStart;
		startSpawns["allies"] = alliesStart;
		
		return startSpawns;
	}
	else
		return undefined;
}


//////////////////////////////////////////////
//
//	Event - Mortar


doMortar()
{
	mapCenter = getMapCenter();	
	offset = 1;
	for ( i=0; i<5; i++ )
	{
		mortarTarget = mapCenter + ( RandomIntRange(100, 600)*offset, RandomIntRange(100, 600)*offset, 0 );
		
		traceData = BulletTrace( mortarTarget+(0,0,500), mortarTarget-(0,0,500), false );
		if ( isDefined( traceData["position"] ) )
		{			
			PlayFx( level.match_events_fx["tracer"], mortarTarget );
			thread playSoundinSpace( "fast_artillery_round", mortarTarget );
			
			wait( RandomFloatRange( 0.5, 1.5 ) );
			
			PlayFx( level.match_events_fx["explosion"], mortarTarget );
			PlayRumbleOnPosition( "grenade_rumble", mortarTarget );
			Earthquake( 1.0, 0.6, mortarTarget, 2000 );	
			wii_play_grenade_rumble( mortarTarget );
			thread playSoundinSpace( "exp_suitcase_bomb_main", mortarTarget );
			physicsExplosionSphere( mortarTarget + (0,0,30), 250, 125, 2 );
			
			offset *= -1;			
		}		
	}
}


//////////////////////////////////////////////
//
//	Event - Smoke


doSmoke()
{
	mapCenter = getMapCenter();	
	offset = 1;
	for ( i=0; i<3; i++ )
	{
		smokeTarget = mapCenter + ( RandomIntRange(100, 600)*offset, RandomIntRange(100, 600)*offset, 0 );		
		
		PlayFx( level.match_events_fx["smoke"], smokeTarget );			
		offset *= -1;	
		wait( 2 );
	}	
}


//////////////////////////////////////////////
//
//	Event - Airstrike


doAirstrike()
{
	level endon( "game_ended" );
	
	offset = 1;
	mapCenter = getMapCenter();
	for( i = 0; i < 3; i++ )
	{	
		strikeTarget = mapCenter + ( RandomIntRange(100, 600)*offset, RandomIntRange(100, 600)*offset, 0 );
		traceData = BulletTrace( strikeTarget+(0,0,500), strikeTarget-(0,0,500), false );
		if ( isDefined( traceData["position"] ) )
		{		
			thread doAirstrikeFlyBy( traceData["position"] );	
			offset *= -1;	
			wait ( randomIntRange( 2,4 ) );
		}
	}
}

doAirstrikeFlyBy( strikeTarget )
{
	randSpawn = randomInt( level.spawnPoints.size - 1 );
	targetPos = level.spawnPoints[randSpawn].origin * (1,1,0);
	
	backDist = 8000;
	forwardDist = 8000;
	heightEnt = GetEnt( "airstrikeheight", "targetname" );
	
	upVector = (0, 0, heightEnt.origin[2] + randomIntRange(-100, 600) );
	
	forward = AnglesToForward( (0,randomInt(45),0) );
	
	startpos = targetPos + upVector + forward * backDist * -1;
	endPos = targetPos + upVector + forward * forwardDist;
	
	plane2StartPos = startpos + ( randomIntRange(400,500), randomIntRange(400,500), randomIntRange(200,300) );
	plane2EndPos = endPos + ( randomIntRange(400,500), randomIntRange(400,500), randomIntRange(200,300) );
	
	plane = spawnplane( self, "script_model", startpos );
	plane2 = spawnplane( self, "script_model", plane2StartPos );
	
	if ( cointoss() )
	{
		plane setModel( "vehicle_av8b_harrier_jet_mp" );
		plane2 setModel( "vehicle_av8b_harrier_jet_mp" );
	}
	else
	{
		plane setModel( "vehicle_av8b_harrier_jet_opfor_mp" );
		plane2 setModel( "vehicle_av8b_harrier_jet_opfor_mp" );
	}
	
	plane.angles = vectorToAngles( endPos-startPos );
	plane playloopsound( "veh_mig29_dist_loop" );
	plane thread playPlaneFx();
	
	plane2.angles = vectorToAngles( endPos-plane2StartPos );
	plane2 playloopsound( "veh_mig29_dist_loop" );
	plane2 thread playPlaneFx();
	
	length = distance(startPos, endPos);
	plane moveTo( endPos * 2, length/2000, 0, 0 );
	wait( randomFloatRange( .25, .5 ) );
	plane2 moveTo( plane2EndPos * 2, length/2000, 0, 0 );
	
	//MagicBullet( "nodamage_rocket_mp", plane.origin, strikeTarget );
	
	wait( length/2000 );
	plane delete();
	plane2 delete();	
}

playPlaneFx()
{
	self endon ( "death" );

	wait( 0.5);
	playfxontag( level.fx_airstrike_afterburner, self, "tag_engine_right" );
	wait( 0.5);
	playfxontag( level.fx_airstrike_afterburner, self, "tag_engine_left" );
	wait( 0.5);
	playfxontag( level.fx_airstrike_contrail, self, "tag_right_wingtip" );
	wait( 0.5);
	playfxontag( level.fx_airstrike_contrail, self, "tag_left_wingtip" );
}


//////////////////////////////////////////////
//
//	Event - Pavelow


doPavelow()
{
	mapCenter = getMapCenter();
	traceData = BulletTrace( mapCenter+(0,0,500), mapCenter-(0,0,500), false );
	if ( isDefined( traceData["position"] ) )
	{
		if ( cointoss() )
			vehicleModel = "vehicle_pavelow";
		else
			vehicleModel = "vehicle_pavelow_opfor";		
		chopper = spawnHelicopter( self, traceData["position"]+(0,0,1000), (0,0,0), "pavelow_mp", vehicleModel );		
		if ( !isDefined( chopper ) )
			return;
		
		chopper.team = self.pers["team"];
		chopper.heli_type = level.heli_types[ vehicleModel ];
		chopper thread [[ level.lightFxFunc[ level.heli_types[ vehicleModel ] ] ]]();
		chopper.zOffset = (0,0,chopper getTagOrigin( "tag_origin" )[2] - chopper getTagOrigin( "tag_ground" )[2]);	
		
		wait( 1 );
		
		playFxOnTag( level.chopper_fx["damage"]["on_fire"], chopper, "tag_engine_left" );
		chopper thread maps\mp\killstreaks\_helicopter::heli_crash();		
	}
}


//////////////////////////////////////////////
//
//	Event - Heli Insertion


doHeliInsertion()
{
	startSpawns = getStartSpawns();	
	if ( isDefined( startSpawns ) )
	{	
		spawnHeight = 200;
		hoverOffset = 200;
		leaveOffset = 1000;
		
		//	allies choppers		
		
		forward1 = AnglesToForward( startSpawns["allies"][0].angles ) * 300;
		up1 = AnglesToUp( startSpawns["allies"][0].angles ) * spawnHeight;
		right1 = AnglesToRight( startSpawns["allies"][0].angles ) * 200;
		left1 = AnglesToRight( startSpawns["allies"][0].angles ) * -200;		
		rightPos1 = startSpawns["allies"][0].origin+forward1+up1+right1;
		leftPos1 = startSpawns["allies"][0].origin+forward1+up1+left1;
		
		chopper1 = spawnHelicopter( self, rightPos1, startSpawns["allies"][0].angles, "attack_littlebird_mp", "vehicle_little_bird_armed_mp" );	
		chopper2 = spawnHelicopter( self, leftPos1, startSpawns["allies"][0].angles, "attack_littlebird_mp", "vehicle_little_bird_armed_mp" );		
		
		//	axis choppers
		
		forward2 = AnglesToForward( startSpawns["axis"][0].angles ) * 300;
		up2 = AnglesToUp( startSpawns["axis"][0].angles ) * spawnHeight;
		right2 = AnglesToRight( startSpawns["axis"][0].angles ) * 200;
		left2 = AnglesToRight( startSpawns["axis"][0].angles ) * -200;	
		rightPos2 = startSpawns["axis"][0].origin+forward2+up2+right2;
		leftPos2 = startSpawns["axis"][0].origin+forward2+up2+left2;			
		
		chopper3 = spawnHelicopter( self, rightPos2, startSpawns["axis"][0].angles, "attack_littlebird_mp", "vehicle_little_bird_armed_mp" );		
		chopper4 = spawnHelicopter( self, leftPos2, startSpawns["axis"][0].angles, "attack_littlebird_mp", "vehicle_little_bird_armed_mp" );
		
		//	rise to hover
		
		chopper1 Vehicle_SetSpeed( 20, 10 );
		chopper1 SetYawSpeed( 3, 3, 3, 0.3 );
		chopper1 setVehGoalPos( rightPos1+(0,0,hoverOffset), 1 );				
			
		chopper2 Vehicle_SetSpeed( 20, 10 );
		chopper2 SetYawSpeed( 3, 3, 3, 0.3 );
		chopper2 setVehGoalPos( leftPos1+(0,0,hoverOffset), 1 );		
		
		chopper3 Vehicle_SetSpeed( 20, 10 );
		chopper3 SetYawSpeed( 3, 3, 3, 0.3 );
		chopper3 setVehGoalPos( rightPos2+(0,0,hoverOffset), 1 );			
			
		chopper4 Vehicle_SetSpeed( 20, 10 );
		chopper4 SetYawSpeed( 3, 3, 3, 0.3 );
		chopper4 setVehGoalPos( leftPos2+(0,0,hoverOffset), 1 );	
			
		chopper1 waittill ( "goal" );
		wait( 2 );
		
		//	rise to leave
		
		chopper1 Vehicle_SetSpeed( 80, 60 );
		chopper1 SetYawSpeed( 30, 15, 15, 0.3 );
		chopper1 setVehGoalPos( rightPos1+(0,0,leaveOffset)+right1*2, 1 );		
		
		chopper2 Vehicle_SetSpeed( 80, 60 );
		chopper2 SetYawSpeed( 30, 15, 15, 0.3 );
		chopper2 setVehGoalPos( leftPos1+(0,0,leaveOffset)+left1*2, 1 );		

		chopper3 Vehicle_SetSpeed( 80, 60 );
		chopper3 SetYawSpeed( 30, 15, 15, 0.3 );
		chopper3 setVehGoalPos( rightPos2+(0,0,leaveOffset)+right2*2, 1 );		
		
		chopper4 Vehicle_SetSpeed( 80, 60 );
		chopper4 SetYawSpeed( 30, 15, 15, 0.3 );
		chopper4 setVehGoalPos( leftPos2+(0,0,leaveOffset)+left2*2, 1 );
		
		chopper1 waittill ( "goal" );
		
		//	leave
		
		chopper1 Vehicle_SetSpeed( 120, 120 );
		chopper1 SetYawSpeed( 60, 40, 40, 0.3 );
		chopper1 setVehGoalPos( rightPos1+(0,0,leaveOffset)+right1*2+forward1*-20, 1 );		
		
		chopper2 Vehicle_SetSpeed( 120, 120 );
		chopper2 SetYawSpeed( 60, 40, 40, 0.3 );
		chopper2 setVehGoalPos( leftPos1+(0,0,leaveOffset)+left1*2+forward1*-20, 1 );		

		chopper3 Vehicle_SetSpeed( 120, 120 );
		chopper3 SetYawSpeed( 60, 40, 40, 0.3 );
		chopper3 setVehGoalPos( rightPos2+(0,0,leaveOffset)+right2*2+forward2*-20, 1 );		
		
		chopper4 Vehicle_SetSpeed( 120, 120 );
		chopper4 SetYawSpeed( 60, 40, 40, 0.3 );
		chopper4 setVehGoalPos( leftPos2+(0,0,leaveOffset)+left2*2+forward2*-20, 1 );	
		
		chopper1 waittill ( "goal" );
		
		chopper1 delete();
		chopper2 delete();
		chopper3 delete();
		chopper4 delete();	
	}
}


//////////////////////////////////////////////
//
//	Event - Osprey Insertion


doOspreyInsertion()
{
	startSpawns = getStartSpawns();	
	if ( isDefined( startSpawns ) )
	{	
		spawnHeight = 200;
		hoverOffset = 200;
		leaveOffset = 1000;
		
		//	allies osprey
		
		forward1 = AnglesToForward( startSpawns["allies"][0].angles ) * 300;
		up1 = AnglesToUp( startSpawns["allies"][0].angles ) * spawnHeight;
		pos1 = startSpawns["allies"][0].origin+forward1+up1;		
		airShip1 = spawnHelicopter( self, pos1, startSpawns["allies"][0].angles, "osprey_minigun_mp", "vehicle_v22_osprey_body_mp" );					
		
		//	axis osprey
		
		forward2 = AnglesToForward( startSpawns["axis"][0].angles ) * 300;
		up2 = AnglesToUp( startSpawns["axis"][0].angles ) * spawnHeight;
		pos2 = startSpawns["axis"][0].origin+forward2+up2;		
		airShip2 = spawnHelicopter( self, pos2, startSpawns["axis"][0].angles, "osprey_minigun_mp", "vehicle_v22_osprey_body_mp" );				
		
		//	rise to hover
		
		airship1 thread maps\mp\killstreaks\_escortairdrop::airShipPitchPropsUp();
		airship2 thread maps\mp\killstreaks\_escortairdrop::airShipPitchPropsUp();		
		airShip1 thread maps\mp\killstreaks\_escortairdrop::airShipPitchHatchDown();
		airShip2 thread maps\mp\killstreaks\_escortairdrop::airShipPitchHatchDown();		
		
		airShip1 Vehicle_SetSpeed( 20, 10 );
		airShip1 SetYawSpeed( 3, 3, 3, 0.3 );
		airShip1 setVehGoalPos( pos1+(0,0,hoverOffset), 1 );	
		
		airShip2 Vehicle_SetSpeed( 20, 10 );
		airShip2 SetYawSpeed( 3, 3, 3, 0.3 );
		airShip2 setVehGoalPos( pos2+(0,0,hoverOffset), 1 );				
		
		airShip1 waittill ( "goal" );
		
		airShip1 thread maps\mp\killstreaks\_escortairdrop::airShipPitchHatchUp();
		airShip2 thread maps\mp\killstreaks\_escortairdrop::airShipPitchHatchUp();
		
		wait( 2 );
		
		//	rise to leave
		
		airShip1 Vehicle_SetSpeed( 80, 60 );
		airShip1 SetYawSpeed( 30, 15, 15, 0.3 );
		airShip1 setVehGoalPos( pos1+(0,0,leaveOffset), 1 );	
		
		airShip2 Vehicle_SetSpeed( 80, 60 );
		airShip2 SetYawSpeed( 30, 15, 15, 0.3 );
		airShip2 setVehGoalPos( pos2+(0,0,leaveOffset), 1 );	
		
		airShip1 waittill ( "goal" );
		
		//	leave		
		
		airship1 thread maps\mp\killstreaks\_escortairdrop::airShipPitchPropsDown();
		airship2 thread maps\mp\killstreaks\_escortairdrop::airShipPitchPropsDown();
		
		airShip1 Vehicle_SetSpeed( 120, 120 );
		airShip1 SetYawSpeed( 100, 100, 40, 0.3 );
		airShip1 setVehGoalPos( pos1+(0,0,leaveOffset)+forward1*-20, 1 );	
		
		airShip2 Vehicle_SetSpeed( 120, 120 );
		airShip2 SetYawSpeed( 100, 100, 40, 0.3 );
		airShip2 setVehGoalPos( pos2+(0,0,leaveOffset)+forward2*-20, 1 );		
		
		airShip1 waittill ( "goal" );
		
		airShip1 delete();	
		airShip2 delete();				
	}	
}
