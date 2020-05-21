#include maps\mp\_utility;
#include common_scripts\utility;
#include maps\mp\gametypes\_hud_util;

init()
{
	precacheModel( "vehicle_bradley" );	
	precacheModel( "vehicle_bradley_destroyed" );
		
	precacheShader( "compass_objpoint_tank_friendly" );
	precacheShader( "compass_objpoint_tank_enemy" );	
	precacheShader( "compass_objpoint_mortar_target" );
	
	precacheString( &"KILLSTREAKS_MOBILE_MORTAR" );
	precacheString( &"MP_GROUND_APPROACHES_TOO_CROWDED" );
	precacheString( &"MP_SELECT_MOBILE_MORTAR_LOCATION" );
	
	level.tankFire 		= loadfx( "props/barrelexp" );
	//level.tankDamage	= loadfx( "fire/tank_fire_turret_abrams" );
	level.tankExplode = loadfx( "explosions/large_vehicle_explosion" );
	level.tankFlash		= loadfx( "muzzleflashes/ac130_105mm" );
	level.tankDust1		= loadfx( "smoke/ground_smoke_launch_a" );	
	level.tankDust2		= loadfx( "smoke/ground_smoke_launch_a" );
	
	level.ground_support_locs = [];
	
	//
	//	ALPHA	
	level.ground_support_locs["mp_alpha"][0]["origin"] = ( -2748.91, 2921.33, 125.394 );
	level.ground_support_locs["mp_alpha"][0]["angles"] = ( 0, 16, 0 );
	
	level.ground_support_locs["mp_alpha"][1]["origin"] = ( 707.795, -499.191, -7.875 );
	level.ground_support_locs["mp_alpha"][1]["angles"] = ( 0, 90, 0 );
	
	level.ground_support_locs["mp_alpha"][2]["origin"] = ( 81.8557, 2343.87, -7.875 );
	level.ground_support_locs["mp_alpha"][2]["angles"] = ( 0, -90.1, 0 );
	
	//
	//	BRAVO
	level.ground_support_locs["mp_bravo"][0]["origin"] = ( -761.529, 1221.7, 1212.13 );
	level.ground_support_locs["mp_bravo"][0]["angles"] = ( 0, -92.373, 0 );
	
	level.ground_support_locs["mp_bravo"][1]["origin"] = ( 1474.99, 971.865, 1140.13 );
	level.ground_support_locs["mp_bravo"][1]["angles"] = ( 0, -178.401, 0 );
	
	level.ground_support_locs["mp_bravo"][2]["origin"] = ( -1366.57, -370.995, 975.807 );
	level.ground_support_locs["mp_bravo"][2]["angles"] = ( 0, 0.807495, 0 );
	
	//
	//	DOME
	level.ground_support_locs["mp_dome"][0]["origin"] = ( 960.279, -482.564, -388.872 );
	level.ground_support_locs["mp_dome"][0]["angles"] = ( 0, 100.536, 0 );
	
	level.ground_support_locs["mp_dome"][1]["origin"] = ( -921.941, 166.449, -418.131 );
	level.ground_support_locs["mp_dome"][1]["angles"] = ( 0, 25.4524, 0 );
	
	level.ground_support_locs["mp_dome"][2]["origin"] = ( 43.3564, 2102.85, -290.875 );
	level.ground_support_locs["mp_dome"][2]["angles"] = ( 0, -95.0347, 0 );
	
	//
	//	PLAZA 2
	level.ground_support_locs["mp_plaza2"][0]["origin"] = ( -1579.34, -2349.41, 556.125 );
	level.ground_support_locs["mp_plaza2"][0]["angles"] = ( 0, 5.32288, 0 );
	
	level.ground_support_locs["mp_plaza2"][1]["origin"] = ( -135.286, 1622.04, 607.13 );
	level.ground_support_locs["mp_plaza2"][1]["angles"] = ( 0, 173.639, 0 );
	
	level.ground_support_locs["mp_plaza2"][2]["origin"] = ( -1544.55, 1966.84, 632.024 );
	level.ground_support_locs["mp_plaza2"][2]["angles"] = ( 0, 0.796509, 0 );
	
	//
	//	RADAR
	level.ground_support_locs["mp_radar"][0]["origin"] = ( 896.685, 2692.74, 1208.13 );
	level.ground_support_locs["mp_radar"][0]["angles"] = ( 0, -178.313, 0 );
	
	level.ground_support_locs["mp_radar"][1]["origin"] = ( -2455.87, 1564.41, 1308.9 );
	level.ground_support_locs["mp_radar"][1]["angles"] = ( 0, 1.93471, 0 );
	
	level.ground_support_locs["mp_radar"][2]["origin"] = ( 1609, -1098.99, 1162.13 );
	level.ground_support_locs["mp_radar"][2]["angles"] = ( 0, 170.421, 0 );
	
	//
	//	INTERCHANGE
	level.ground_support_locs["mp_interchange"][0]["origin"] = ( -2067.08, 1218.17, -82.0487 );
	level.ground_support_locs["mp_interchange"][0]["angles"] = ( 0, -26.2946, 0 );
	
	level.ground_support_locs["mp_interchange"][1]["origin"] = ( -1198.2, -1782.62, 103.665 );
	level.ground_support_locs["mp_interchange"][1]["angles"] = ( 0, 23.3544, 0 );
	
	level.ground_support_locs["mp_interchange"][2]["origin"] = ( 2391.95, 899.034, 87.7839 );
	level.ground_support_locs["mp_interchange"][2]["angles"] = ( 0, -136.134, 0 );
	
	//
	//	LAMBETH
	level.ground_support_locs["mp_lambeth"][0]["origin"] = ( 1641.37, -1318.01, -260.173 );
	level.ground_support_locs["mp_lambeth"][0]["angles"] = ( 0, 133.329, 0 );
	
	level.ground_support_locs["mp_lambeth"][1]["origin"] = ( -1346.56, -880.226, -191.875 );
	level.ground_support_locs["mp_lambeth"][1]["angles"] = ( 0, 0.432892, 0 );
	
	level.ground_support_locs["mp_lambeth"][2]["origin"] = ( 1403.95, 3083.4, -287.354 );
	level.ground_support_locs["mp_lambeth"][2]["angles"] = ( 0, -106.321, 0 );
	
	//
	//	PARIS
	level.ground_support_locs["mp_paris"][0]["origin"] = ( -2427.42, 619.217, 188.826 );
	level.ground_support_locs["mp_paris"][0]["angles"] = ( 0, -2.90588, 0 );
	
	level.ground_support_locs["mp_paris"][1]["origin"] = ( 2066.95, 796.542, -88.322 );
	level.ground_support_locs["mp_paris"][1]["angles"] = ( 0, 177.292, 0 );
	
	level.ground_support_locs["mp_paris"][2]["origin"] = ( 506.406, -2165.36, -64.1201 );
	level.ground_support_locs["mp_paris"][2]["angles"] = ( 0, 89.5715, 0 );
	
	//
	//	HARDHAT
	level.ground_support_locs["mp_hardhat"][0]["origin"] = ( 2033.65, -1428.62, 299.86 );
	level.ground_support_locs["mp_hardhat"][0]["angles"] = ( 0, 177.979, 0 );
	
	level.ground_support_locs["mp_hardhat"][1]["origin"] = ( -1044.73, 82.9179, 181.022 );
	level.ground_support_locs["mp_hardhat"][1]["angles"] = ( 0, -2.68066, 0 );
	
	level.ground_support_locs["mp_hardhat"][2]["origin"] = ( 1248.95, 1322.56, 304.125 );
	level.ground_support_locs["mp_hardhat"][2]["angles"] = ( 0, -93.4772, 0 );	
	
	//
	//	CARBON
	level.ground_support_locs["mp_carbon"][0]["origin"] = ( -47.1408, -2841.26, 3940.01 );
	level.ground_support_locs["mp_carbon"][0]["angles"] = ( 0, -101.667, 0 );
	
	level.ground_support_locs["mp_carbon"][1]["origin"] = ( -1686.2, -4727.09, 3756.16 );
	level.ground_support_locs["mp_carbon"][1]["angles"] = ( 0, 87.6436, 0 );
	
	level.ground_support_locs["mp_carbon"][2]["origin"] = ( -3761.18, -3716.69, 3568.91 );
	level.ground_support_locs["mp_carbon"][2]["angles"] = ( 0, -4.20761, 0 );
	
	//
	//	SEATOWN
	level.ground_support_locs["mp_seatown"][0]["origin"] = ( 1339.87, 763.592, 175.114 );
	level.ground_support_locs["mp_seatown"][0]["angles"] = ( 0, 178.551, 0 );
	
	level.ground_support_locs["mp_seatown"][1]["origin"] = ( 1317.92, -725.589, 232.125 );
	level.ground_support_locs["mp_seatown"][1]["angles"] = ( 0, 177.738, 0 );
	
	level.ground_support_locs["mp_seatown"][2]["origin"] = ( -961.699, -1581.56, 144.125 );
	level.ground_support_locs["mp_seatown"][2]["angles"] = ( 0, 90.0176, 0 );
	
	//
	//	BOOTLEG
	level.ground_support_locs["mp_bootleg"][0]["origin"] = ( -988.964, 1833.74, -99.9509 );
	level.ground_support_locs["mp_bootleg"][0]["angles"] = ( 0, -78.8909, 0 );
	
	level.ground_support_locs["mp_bootleg"][1]["origin"] = ( 1105.84, -1116.13, -72.3048 );
	level.ground_support_locs["mp_bootleg"][1]["angles"] = ( 0, 176.558, 0 );
	
	level.ground_support_locs["mp_bootleg"][2]["origin"] = ( -2027.31, 84.2235, -51.875 );
	level.ground_support_locs["mp_bootleg"][2]["angles"] = ( 0, -5.12868, 0 );
	
	//
	//	METEORA
	level.ground_support_locs["mp_meteora"][0]["origin"] = ( -590.972, 1667.65, -99.6187 );
	level.ground_support_locs["mp_meteora"][0]["angles"] = ( 0, -89.7745, 0 );
	
	level.ground_support_locs["mp_meteora"][1]["origin"] = ( -1371.02, -1095.66, 4.125 );
	level.ground_support_locs["mp_meteora"][1]["angles"] = ( 0, 179.879, 0 );
	
	level.ground_support_locs["mp_meteora"][2]["origin"] = ( 938.851, -1376.99, -60.0877 );
	level.ground_support_locs["mp_meteora"][2]["angles"] = ( 0, 110.545, 0 );
	
	level.killStreakFuncs["mobile_mortar"] = ::tryUseMobileMortar;	
}


tryUseMobileMortar( lifeId, kId )
{
	//	context fail cases
	if ( !isDefined( level.ground_support_locs[level.script] ) )
	{
		self iPrintLnBold( &"MP_UNAVAILABLE_IN_LEVEL" );
		return false;		
	}
	if ( isDefined( self.lastStand ) && !self _hasPerk( "specialty_finalstand" ) )
	{
		self iPrintLnBold( &"MP_UNAVILABLE_IN_LASTSTAND" );
		return false;
	}
	else if ( isDefined( level.mobileMortar ) )
	{
		self iPrintLnBold( &"MP_GROUND_APPROACHES_TOO_CROWDED" );
		return false;
	}
	else if ( self isUsingRemote() )
	{
		return false;
	}		
	
	//	select location
	locIndex = self selectEntranceLocation();	
	if ( !isDefined( locIndex ) )
	{
		return false;
	}
	else
		self thread stopLocationSelection( false );
	
	//	create it
	mobileMortar = createMobileMortar( self, locIndex );
	if ( !isDefined( mobileMortar ) )
		return false;	
		
	//	use it
	mobileMortar thread moveToPosition( "entrance" );
	return true;
}	
			
selectEntranceLocation()
{	
	locIndex = undefined;	
	
	for ( ;; )
	{
		self thread showIcons();
		self _beginLocationSelection( "mobile_mortar", "map_artillery_selector", false, 500 );	
		self endon( "stop_location_selection" );	
			
		self waittill( "confirm_location", location );	
		for ( i=0; i<3; i++ )
		{
			targetLoc = level.ground_support_locs[level.script][i]["origin"] * (1,1,0);
			distSquared = distanceSquared( location, targetLoc ); 
			if ( distSquared < 60000 )
			{
				locIndex = i;				
				break;
			}
		}
		if ( isDefined( locIndex ) )
		{
			for ( i=0; i<3; i++ )
			{
				if ( i == locIndex )
					Objective_Icon( self.locationObjectives[i], "compass_objpoint_mortar_target" );
				else
					Objective_state( self.locationObjectives[i], "invisible" );
			}							
		}
		else
		{
			for ( i=0; i<3; i++ )
			{
				Objective_Icon( self.locationObjectives[i], "compass_objpoint_tank_enemy" );			
			}			
		}		
		wait ( 0.5 );
		self notify( "picked_location" );
		wait( 0.05 );
		if ( isDefined( locIndex ) )
			break;
	}
	
	return locIndex;
}

showIcons()
{
	msg = self maps\mp\gametypes\_hud_util::createFontString( "bigfixed", 0.5 );
	msg maps\mp\gametypes\_hud_util::setPoint( "CENTER", "CENTER", 0 , -150 );
	msg setText( &"MP_SELECT_MOBILE_MORTAR_LOCATION" );	
	
	self.locationObjectives = [];
	
	for ( i=0; i<3; i++ )
	{
		self.locationObjectives[i] = maps\mp\gametypes\_gameobjects::getNextObjID();	
		objective_add( self.locationObjectives[i], "invisible", (0,0,0) );
		objective_position( self.locationObjectives[i], level.ground_support_locs[level.script][i]["origin"] );
		objective_state( self.locationObjectives[i], "active" );
		objective_team( self.locationObjectives[i], self.team );
		objective_icon( self.locationObjectives[i], "compass_objpoint_tank_friendly" );			
	}
	
	self waittill_any( "cancel_location", "picked_location", "stop_location_selection" );
	
	msg destroyElem();
	for ( i=0; i<3; i++ )
	{
		_objective_delete( self.locationObjectives[i] );
	}	
}

createMobileMortar( owner, locIndex )
{	
	//	position
	skyHeight = self maps\mp\killstreaks\_airdrop::getFlyHeightOffset( level.ground_support_locs[level.script][locIndex]["origin"] );
	primaryTrace = bulletTrace( level.ground_support_locs[level.script][locIndex]["origin"]+(0,0,skyHeight), level.ground_support_locs[level.script][locIndex]["origin"]-(0,0,skyHeight), false );
	spawnPos = primaryTrace["position"] + anglesToForward(level.ground_support_locs[level.script][locIndex]["angles"])*-1000;

	//	create it
	mobileMortar = Spawn( "script_model", spawnPos );
	if ( !isDefined( mobileMortar ) )	
		return undefined;

	//	set state vars		
	mobileMortar.angles = level.ground_support_locs[level.script][locIndex]["angles"];
	mobileMortar SetModel( "vehicle_bradley" );	
	mobileMortar setCanDamage( true );
	mobileMortar.maxhealth = level.heli_maxhealth*2;
	mobileMortar.health = mobileMortar.maxhealth;	
	mobileMortar.owner = owner;	
	mobileMortar.playersAttacked = [];
	mobileMortar.lastTarget = mobileMortar.origin; 
	if ( level.teamBased )
		mobileMortar.team = owner.team;	

	//	save some info about the level spawn bounds for fallback random targeting
	mobileMortar.lowX = level.spawnpoints[0].origin[0];
	mobileMortar.highX = level.spawnpoints[0].origin[0];
	mobileMortar.lowY = level.spawnpoints[0].origin[1];
	mobileMortar.highY = level.spawnpoints[0].origin[1];
	increment = 200;
	if ( level.spawnpoints.size > 1 )
	{
		for( i=1; i<level.spawnpoints.size; i++ )
		{
			if ( level.spawnpoints[i].origin[0] < mobileMortar.lowX )
				mobileMortar.lowX = level.spawnpoints[i].origin[0];
			else if ( level.spawnpoints[i].origin[0] > mobileMortar.highX )
				mobileMortar.highX = level.spawnpoints[i].origin[0];
				
			if ( level.spawnpoints[i].origin[1] < mobileMortar.lowY )
				mobileMortar.lowY = level.spawnpoints[i].origin[1];
			else if ( level.spawnpoints[i].origin[1] > mobileMortar.highY )
				mobileMortar.highY = level.spawnpoints[i].origin[1];			
		}	
	}
	else
		increment = -2000;
	mobileMortar.lowX += increment;
	mobileMortar.highX -= increment;	
	mobileMortar.lowY += increment;
	mobileMortar.highY -= increment;	

	//	minimap
	if ( level.teamBased )
	{
		curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
		objective_add( curObjID, "invisible", (0,0,0) );
		objective_position( curObjID, primaryTrace["position"] );
		objective_state( curObjID, "active" );
		objective_team( curObjID, mobileMortar.team );
		objective_icon( curObjID, "compass_objpoint_tank_friendly" );
		mobileMortar.objIdFriendly = curObjID;
	
		curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
		objective_add( curObjID, "invisible", (0,0,0) );
		objective_position( curObjID, primaryTrace["position"] );
		objective_state( curObjID, "active" );
		objective_team( curObjID, level.otherTeam[mobileMortar.team] );
		objective_icon( curObjID, "compass_objpoint_tank_enemy" );
		mobileMortar.objIdEnemy = curObjID;
	}		

	//	launch watch threads
	mobileMortar thread watchTimeOut();
	mobileMortar thread maps\mp\killstreaks\_helicopter::heli_damage_monitor();
	//mobileMortar thread watchDamage();
	mobileMortar thread watchDeath();
	mobileMortar thread watchProximity();	

	level.mobileMortar = mobileMortar;	

	return mobileMortar;	
}


moveToPosition( position /*lifeId, airShip, pathStart, pathGoal, pathEnd, flyHeight*/ )
{
	level endon( "game_ended" );
	self endon( "death" );	
	
	if ( position == "entrance" )
		pos = self.origin + anglesToForward(self.angles)*1000;
	else
	{
		self notify( "leaving" );
		pos = self.origin + anglesToForward(self.angles)*-1000;
	}
	
	movetime = 3.0;
	self MoveTo( pos, movetime, movetime * 0.6, movetime * 0.4 );
	wait( movetime );		

	if ( position == "entrance" )
		self thread mortarAttack();
	else
	{
		StopFXOnTag( level.tankDust1, self.fxEnt, "tag_origin" );
		StopFXOnTag( level.tankDust2, self.fxEnt, "tag_origin" );
		//StopFXOnTag( level.tankDamage, self, "tag_origin" );	
		self.fxEnt delete();		
		
		_objective_delete( self.objIdFriendly );
		_objective_delete( self.objIdEnemy );
		level.mobileMortar = undefined;
		self delete();		
	}
}

findTarget()
{
	bestTarget = undefined;
	foreach ( player in level.players )	
	{
		if ( player == self.owner )
			continue;
		if ( player _hasPerk( "specialty_blindeye" ) )
			continue;
		if ( level.teamBased && player.team == self.owner.team )
			continue;			
		if ( distanceSquared( self.origin, player.origin ) < 1000000 )
			continue;		
		for ( i=0; i<self.playersAttacked.size; i++ )
		{
			if ( player == self.playersAttacked[i] )
				continue;
		}	
		if ( distanceSquared( player.origin, self.lastTarget ) < 500000 )
			continue;
		if ( level.teamBased )
		{
			friendlyClose = false;	
			for ( i=0; i<level.players.size; i++ )
			{
				if ( level.players[i].team != player.team && distanceSquared( player.origin, level.players[i].origin ) < 250000 ) 
				{
					friendlyClose = true;
					break;
				}
			}	
			if ( friendlyClose == true )
				continue;
		}
			
		wait( 0.05 );
		trace = bulletTrace( player.origin+(0,0,player maps\mp\killstreaks\_airdrop::getFlyHeightOffset( player.origin )), player.origin+(0,0,100), false );
		if ( trace["surfacetype"] != "none" )
			continue;
		
		bestTarget = player.origin;
		self.lastTarget = player.origin;
		self.playersAttacked[self.playersAttacked.size] = player;
		break;		
	}
	return bestTarget;
}

findRandomTarget()
{
	randomTarget = undefined;
  for( i=0; i<20; i++ )
  {
  	testTarget = ( RandomFloatRange( self.lowX, self.highX ), RandomFloatRange( self.lowY, self.highY ), 0 );
		if ( distanceSquared( self.origin*(1,1,0), testTarget ) < 1000000 )
			continue;
		if ( distanceSquared( self.owner.origin*(1,1,0), testTarget ) < 250000 )
			continue;
		if ( distanceSquared( self.origin*(1,1,0), self.lastTarget ) < 500000 )
			continue;			  	
  	
  	friendlyClose = false;
		if ( level.teamBased )
		{
	  	foreach ( player in level.players )
	  	{
	  		if ( player.team == self.owner.team && distanceSquared( player.origin*(1,1,0), testTarget ) < 250000 )
	  		{
	  			friendlyClose = true;
	  			break;
	  		}
	  	} 
	  }
	  
  	if ( friendlyClose == false )
  	{
  		randomTarget = testTarget;
  		self.lastTarget = testTarget;
  		break;
  	}	  
  }

	//	we tried
	if ( !isDefined( randomTarget ) )
		randomTarget = ( RandomFloatRange( self.lowX, self.highX ), RandomFloatRange( self.lowY, self.highY ), 0 );

	return randomTarget;  		
}

mortarAttack()
{
	level endon( "game_ended" );
	self endon( "death" );
	self endon( "leaving" );	
	
	//	testing fx stuff
	dustCount = 0;
	self.fxEnt = Spawn( "script_model", self.origin );	
	self.fxEnt setModel( "tag_origin" );
	self.fxEnt.angles = self.angles;
	self.fxEnt AddPitch( -90 );	
	
	for(;;)
	{
		//	target
		flatPos = self findTarget();
		if ( !isDefined( flatPos ) )
			flatPos = self findRandomTarget();				
		flyHeight = self.origin[2] + 3500;		
		primaryTrace = bulletTrace( flatPos+(0,0,flyHeight), flatPos-(0,0,flyHeight), false );
		assert( primaryTrace["surfacetype"] != "none" );
		startPos = flatPos + (0,0,flyHeight);
		targetPos = flatPos + (0,0,primaryTrace["position"][2]);
		
		//	fx
		self playSound( "bmp_fire" );
		playFX( level.tankFlash, self.origin+anglesToForward(self.angles)*50 );	
		if ( dustCount < 3 )
		{
			PlayFXOnTag( level.tankDust1, self.fxEnt, "tag_origin" );
			PlayFXOnTag( level.tankDust2, self.fxEnt, "tag_origin" );
			dustCount++;
		}	
		self thread mortarRecoil();
		
		//	fire
		level thread fireMortar( self, startPos, targetPos );
		
		//	wait
		self waittill( "mortar_fire_done" );
		wait( 2.5 );
	}	
}

fireMortar( mobileMortar, startPos, targetPos )
{
	level endon( "game_ended" );
	
	owner = mobileMortar.owner;
	
	projectile = magicBullet( "javelin_mp", mobileMortar.origin+(0,0,150), startPos, owner );	
	
	curObjID1 = maps\mp\gametypes\_gameobjects::getNextObjID();	
	objective_add( curObjID1, "invisible", (0,0,0) );
	objective_position( curObjID1, targetPos );
	objective_state( curObjID1, "active" );
	objective_team( curObjID1, mobileMortar.team );
	objective_icon( curObjID1, "compass_objpoint_mortar_target" );
	projectile.objIdFriendly = curObjID1;

	curObjID2 = maps\mp\gametypes\_gameobjects::getNextObjID();	
	objective_add( curObjID2, "invisible", (0,0,0) );
	objective_position( curObjID2, targetPos );
	objective_state( curObjID2, "active" );
	objective_team( curObjID2, level.otherTeam[mobileMortar.team] );
	objective_icon( curObjID2, "compass_objpoint_mortar_target" );
	projectile.objIdEnemy = curObjID2;	
	
	flyCount = 0;
	for( ;; )
	{
		if ( !isDefined( projectile ) || flyCount > 115 || distanceSquared( projectile.origin, startPos ) < 500 )
			break;
		else
			wait( 0.05 );
		flyCount++;
	}			
	
	if ( isDefined( projectile ) )
		projectile delete();	
		
	if ( isDefined( owner ) )
		projectile2 = magicBullet( "javelin_mp", startPos+(0,0,200), targetPos, owner );
	else
		projectile2 = magicBullet( "javelin_mp", startPos+(0,0,200), targetPos );
	projectile2.objIdFriendly = curObjID1;
	projectile2.objIdEnemy = curObjID2;
	projectile2 thread watchProjectileOnMiniMap( mobileMortar );
}

watchProjectileOnMiniMap( mobileMortar )
{
	level endon( "game_ended" );	
	
	self waittill( "death" );
	
	_objective_delete( self.objIdFriendly );
	_objective_delete( self.objIdEnemy );	
		
	if ( isDefined( mobileMortar ) )
		mobileMortar notify( "mortar_fire_done" );
}


mortarRecoil()
{
	level endon( "game_ended" );
	self endon( "death" );
	self endon( "leaving" );
	
	backPos = self.origin + anglesToForward(self.angles)*-20;
	restorePos = self.origin;
	restoreAngles = self.angles;
		
	self MoveTo( backPos, 0.10 );
	self RotatePitch( -3, 0.10 );
	wait( 0.10 );	
	
	self MoveTo( restorePos, 0.15 );
	self RotateTo( restoreAngles, 0.15 );
	wait( 0.15 );	
}

watchTimeOut()
{
	level endon( "game_ended" );
	self endon( "death" );
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 90.0 );
	
	self setCanDamage( false );
	self thread moveToPosition( "exit" );
}

watchProximity()
{
	level endon( "game_ended" );
	self endon( "death" );
	self endon( "leaving" );
	
	for ( ;; )
	{
		RadiusDamage( self.origin, 200, 20, 20 );
		wait( 1 );
	}
}

watchDeath()
{
	level endon( "game_ended" );
	self endon( "leaving" );	
	
	self waittill( "death" );
	
	playFX( level.tankFire, self.origin);	
	playFX( level.tankExplode, self.origin);
 	destroyedTank = Spawn( "script_model", self.origin );
  destroyedTank setModel( "vehicle_bradley_destroyed" );
  destroyedTank.angles = self.angles;		
	
	StopFXOnTag( level.tankDust1, self.fxEnt, "tag_origin" );
	StopFXOnTag( level.tankDust2, self.fxEnt, "tag_origin" );
	//StopFXOnTag( level.tankDamage, self, "tag_origin" );	
	_objective_delete( self.objIdFriendly );
	_objective_delete( self.objIdEnemy );
	self.fxEnt delete();
	self delete();
		
	wait( 3.5 );
	
	destroyedTank delete();	
	level.mobileMortar = undefined;
}

watchDamage()
{
	/*
	if ( !isDefined( attacker ) || attacker == self )
		return;
		
	if ( !maps\mp\gameTypes\_weapons::attackerCanDamageItem( attacker, self.owner ) )
		return;			
		
	self.damageTaken+=damage;		
	if ( self.damageTaken >= self.maxhealth  && ( (level.teamBased && self.team != attacker.team) || !level.teamBased) )
	{
		validAttacker = undefined;
		if ( isDefined( attacker.owner ) && (!isDefined(self.owner) || attacker.owner != self.owner) )
			validAttacker = attacker.owner;				
		else if ( !isDefined(self.owner) || attacker != self.owner )
			validAttacker = attacker;
			
		//	sanity checks	
		if ( !isDefined(attacker.owner) && attacker.classname == "script_vehicle" )
				validAttacker = undefined;
		if ( isDefined( attacker.class ) && attacker.class == "worldspawn" )
				validAttacker = undefined;			

		if ( isDefined( validAttacker ) )
		{
			validAttacker notify( "destroyed_helicopter" );
			validAttacker notify( "destroyed_killstreak", weapon );
			thread teamPlayerCardSplash( "callout_destroyed_helicopter", validAttacker );			
			validAttacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 300 );			
			validAttacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DESTROYED_HELICOPTER" );
			thread maps\mp\gametypes\_missions::vehicleKilled( self.owner, self, undefined, validAttacker, damage, meansOfDeath );		
		}
	}			
	*/

	level endon( "game_ended" );
	self endon( "death" );
	for ( ;; )
	{
		self waittill( "damage", amount, attacker, dir, point, type );
		//if ( attacker == self )
			//self.health += amount;
		/*if ( self.health < 500 && !isDefined( self.playingDamageFX ) )
		{
			self.playingDamageFX = true;
			PlayFXOnTag( level.tankDamage, self, "tag_origin" );
		}*/
		if ( self.health < 0 )
			break;		
	}

}
