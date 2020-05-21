#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

init()
{
	precacheString( &"MP_WAR_RADAR_ACQUIRED" );
	precacheString( &"MP_WAR_RADAR_ACQUIRED_ENEMY" );
	precacheString( &"MP_WAR_RADAR_EXPIRED" );
	precacheString( &"MP_WAR_RADAR_EXPIRED_ENEMY" );
	
	precacheString( &"MP_WAR_COUNTER_RADAR_ACQUIRED" );	
	precacheString( &"MP_WAR_COUNTER_RADAR_ACQUIRED_ENEMY" );
	precacheString( &"MP_WAR_COUNTER_RADAR_EXPIRED" );
	precacheString( &"MP_WAR_COUNTER_RADAR_EXPIRED_ENEMY" );
	
	precacheString( &"MP_LASE_TARGET_FOR_PREDATOR_STRIKE" );
	
	precacheModel( "vehicle_uav_static_mp" );
	precacheModel( "vehicle_phantom_ray" );
	
	precacheItem( "uav_strike_marker_mp" );
	precacheItem( "uav_strike_projectile_mp" );
	
	level._effect[ "ac130_engineeffect" ]		= loadfx( "fire/jet_engine_ac130" );
	
	level.radarViewTime = 30; // time radar remains active
	level.uavBlockTime = 30; // this only seems to be used for the FFA version.
	
	assert( level.radarViewTime > 7 );
	assert( level.uavBlockTime > 7 );

	level.uav_fx[ "explode" ] = loadFx( "explosions/uav_advanced_death" );	
	level.uav_fx[ "trail" ] = loadFx( "smoke/advanced_uav_contrail" );

	level.killStreakFuncs["uav"] = ::tryUseUAV;
	level.killStreakFuncs["uav_support"] = ::tryUseUAVSupport;
	level.killStreakFuncs["uav_2"] = ::tryUseUAV;
	level.killStreakFuncs["double_uav"] = ::tryUseDoubleUAV;
	level.killStreakFuncs["triple_uav"] = ::tryUseTripleUAV;
	level.killStreakFuncs["counter_uav"] = ::tryUseCounterUAV;
	level.killstreakFuncs["uav_strike"] = ::tryUseUAVStrike;
	level.killstreakSetupFuncs["uav_strike"] = ::UAVStrikeSetup;
	level.killstreakFuncs["directional_uav"] = ::tryUseDirectionalUAV;

	
	level._effect[ "laserTarget" ] 	 = loadfx("misc/laser_glow");
		
	minimapOrigins = getEntArray( "minimap_corner", "targetname" );
	if ( miniMapOrigins.size )
		uavOrigin = maps\mp\gametypes\_spawnlogic::findBoxCenter( miniMapOrigins[0].origin, miniMapOrigins[1].origin );
	else
		uavOrigin = (0,0,0);
	
	level.UAVRig = spawn( "script_model", uavOrigin );
	level.UAVRig setModel( "c130_zoomrig" );
	level.UAVRig.angles = (0,115,0);
	level.UAVRig hide();

	// used for debug printing
	level.UAVRig.targetname = "uavrig_script_model";

	level.UAVRig thread rotateUAVRig();
	
	if ( level.teamBased )
	{
		level.radarMode["allies"] = "normal_radar";
		level.radarMode["axis"] = "normal_radar";
		level.activeUAVs["allies"] = 0;
		level.activeUAVs["axis"] = 0;
		level.activeCounterUAVs["allies"] = 0;
		level.activeCounterUAVs["axis"] = 0;
	
		level.uavModels["allies"] = [];
		level.uavModels["axis"] = [];
	}
	else
	{	
		level.radarMode = [];
		level.activeUAVs = [];
		level.activeCounterUAVs = [];
		
		level.uavModels = [];
		
		level thread onPlayerConnect();		
	}

	level thread UAVTracker();

/#
	SetDevDvarIfUninitialized( "scr_uav_timeout", level.radarViewTime  );
#/
}


onPlayerConnect()
{
	for(;;)
	{
		level waittill( "connected", player );
		
		level.activeUAVs[ player.guid ] = 0;
		level.activeUAVs[ player.guid + "_radarStrength" ] = 0;
		level.activeCounterUAVs[ player.guid ] = 0;
		
		level.radarMode[ player.guid ] = "normal_radar";
	}
}

rotateUAVRig()
{
	for (;;)
	{
		self rotateyaw( -360, 60 );
		wait ( 60 );
	}
}

/#
debugLocation()
{
	self endon( "death" );

	while( true )
	{
		Print3d( self.origin, "UAV", ( 1, 0, 0 ) );
		Print3d( self.origin, "UAV origin: " + self.origin[0] + ", " + self.origin[1] + ", " + self.origin[2], ( 1, 0, 0 ) );
		
		Print3d( level.UAVRig.origin, "UAV Rig", ( 1, 0, 0 ) );
		Print3d( level.UAVRig.origin, "UAV Rig origin: " + level.UAVRig.origin[0] + ", " + level.UAVRig.origin[1] + ", " + level.UAVRig.origin[2], ( 1, 0, 0 ) );

		Print3d( level.UAVRig.origin - ( 0, 0, 50), "Distance: " + Distance( level.UAVRig.origin, self.origin ), ( 1, 0, 0 ) );

		Line( level.UAVRig.origin, self.origin, ( 0, 0, 1 ) );

		anglesForward = AnglesToForward( level.players[0].angles );
		scalar = (anglesForward[0] * 200, anglesForward[1] * 200, anglesForward[2] );
		Print3d( level.players[0].origin + scalar, "Distance: " + Distance( level.players[0].origin, self.origin ), ( 1, 0, 0 ) );
		wait( 0.05 );
	}
}

debugTrace()
{
	self endon( "death" );

	while( true )
	{
		result = BulletTrace( level.players[0].origin, self.origin, false, undefined );
		if( IsDefined( result ) && IsDefined( result[ "surfacetype" ] ) )
		{
			PrintLn( "UAV debugTrace: " + result[ "surfacetype" ] );
		}
		wait( 1.0 );
	}
}
#/

launchUAV( owner, team, duration, uavType )
{
	if ( uavType == "counter_uav" )
		isCounter = true;
	else
		isCounter = false;
		
	UAVModel = spawn( "script_model", level.UAVRig getTagOrigin( "tag_origin" ) );
	
	
/#
	if( GetDvarInt( "scr_debuguav" ) )
	{
		UAVModel thread debugLocation();
		UAVModel thread debugTrace();
	}
#/
	
	UAVModel.value = 1;
	if ( uavType == "double_uav" )
		UAVModel.value = 2;
	else if ( uavType == "triple_uav" )
		UAVModel.value = 3;

	if ( UAVModel.value != 3 )
	{
		UAVModel setModel( "vehicle_uav_static_mp" );
		UAVModel thread damageTracker( isCounter, false );
	}
	else
	{
		UAVModel setModel( "vehicle_phantom_ray" );		
		UAVModel thread spawnFxDelay( level.uav_fx[ "trail" ], "tag_jet_trail" );
		UAVModel thread damageTracker( isCounter, true );
	}
	
	//UAVModel thread damageTracker( isCounter );
	UAVModel.team = team;
	UAVModel.owner = owner;
	UAVModel.timeToAdd = 0;

	UAVModel thread handleIncomingStinger();

	UAVModel addUAVModel();

	zOffset = randomIntRange( 3000, 5000 );

	// we need to make sure the uav doesn't go higher than 8100 units because bullets die at 8192
	if( IsDefined( level.spawnpoints ) )
		spawns = level.spawnPoints;
	else
		spawns = level.startSpawnPoints;

	lowestSpawn = spawns[0];
	foreach( spawn in spawns )
	{
		if ( spawn.origin[2] < lowestSpawn.origin[2] )
			lowestSpawn = spawn; 
	}
	lowestZ = lowestSpawn.origin[2];
	UAVRigZ = level.UAVRig.origin[2];
	if( lowestZ < 0 )
	{
		UAVRigZ += lowestZ * -1;
		lowestZ = 0;
	}
	diffZ = UAVRigZ - lowestZ;
	AssertEx( diffZ < 8100.0, "The lowest spawn and the UAV node are more than 8100 z units apart, please notify MP Design." );
	if( diffZ + zOffset > 8100.0 )
	{
		zOffset -= ( ( diffZ + zOffset ) - 8100.0 );
	}

	angle = randomInt( 360 );
	radiusOffset = randomInt( 2000 ) + 5000;

	xOffset = cos( angle ) * radiusOffset;
	yOffset = sin( angle ) * radiusOffset;

	angleVector = vectorNormalize( (xOffset,yOffset,zOffset) );
	angleVector = ( angleVector * RandomIntRange( 6000, 7000 ) );
	
	UAVModel LinkTo( level.UAVRig, "tag_origin", angleVector, (0,angle - 90,0) );

	UAVModel thread updateUAVModelVisibility();	
		
	if ( isCounter )
	{
		UAVModel.uavType = "counter";
		UAVModel addActiveCounterUAV();
	}	
	else 
	{
		UAVModel addActiveUAV();
		UAVModel.uavType = "standard";
	}
	
	//this adds 5 seconds of time to all active UAV's of the same type.
	if ( isDefined( level.activeUAVs[team] ) )
	{
		foreach ( uav in level.UAVModels[team] )
		{
			if (uav == UAVModel)
				continue;
			
			if ( uav.uavType == "counter" && isCounter )
				uav.timeToAdd += 5;
			else if ( uav.uavType == "standard" && !isCounter )
				uav.timeToAdd += 5;
		}
	}

	level notify ( "uav_update" );
	
	switch ( uavType )
	{
		case "uav_strike": 
			duration = 2;
			break;
		default:
			duration = duration -7;
			break;			
	}
	UAVModel waittill_notify_or_timeout_hostmigration_pause( "death", duration );

	if ( UAVModel.damageTaken < UAVModel.maxHealth )
	{
		UAVModel unlink();
	
		destPoint = UAVModel.origin + ( AnglesToForward( UAVModel.angles ) * 20000 );
		UAVModel moveTo( destPoint, 60 );
		PlayFXOnTag( level._effect[ "ac130_engineeffect" ] , UAVModel, "tag_origin" );

		UAVModel waittill_notify_or_timeout_hostmigration_pause( "death", 3 );

		if ( UAVModel.damageTaken < UAVModel.maxHealth )
		{
			UAVModel notify( "leaving" );
			UAVModel.isLeaving = true;
			UAVModel moveTo( destPoint, 4, 4, 0.0 );
		}
	
		UAVModel waittill_notify_or_timeout_hostmigration_pause( "death", 4 + UAVModel.timeToAdd );
	}

	if ( isCounter )
		UAVModel removeActiveCounterUAV();
	else
		UAVModel removeActiveUAV();

	UAVModel delete();
	UAVModel removeUAVModel();
	
	if( uavType == "directional_uav" )
	{
		owner.radarShowEnemyDirection = false;
		if( level.teambased )
		{
			foreach( player in level.players )
			{
				if( player.pers["team"] == team )
				{
					player.radarShowEnemyDirection = false;					
				}
			}
		}
	}
	
	level notify ( "uav_update" );
}

spawnFXDelay( fxID, tag )
{
	self endon( "death" );
	level endon( "game_ended" );
	
	wait( 0.5 );
	PlayFXOnTag( fxID, self, tag );
}

monitorUAVStrike()
{
	level endon( "game_ended" );
	for ( ;; )
	{
		msg = self waittill_any_return( "death", "uav_strike_cancel", "uav_strike_successful" );
		if ( msg == "uav_strike_successful" )
			return true;
		else
			return false;
	}
}

showLazeMessage()
{
	msg = self maps\mp\gametypes\_hud_util::createFontString( "bigfixed", 0.75 );
	msg maps\mp\gametypes\_hud_util::setPoint( "CENTER", "CENTER", 0 , 150 );
	msg setText( &"MP_LASE_TARGET_FOR_PREDATOR_STRIKE" );	
	
	self waittill_any_timeout( 4.0, "death", "uav_strike_cancel", "uav_strike_successful" );
	
	msg destroyElem();	
}

waitForLazeDiscard()
{
	level endon( "game_ended" );
	self endon( "death" );
	self endon( "uav_strike_used" );
	for ( ;; )
	{
		self waittill ( "weapon_change", newWeapon );
		
		if ( newWeapon != "uav_strike_marker_mp" )
		{		
			self notify( "uav_strike_cancel" );
			break;
		}
		else
			wait( 0.05 );
	}	
}

waitForLazedTarget()
{	
	level endon( "game_ended" );
	self endon( "death" );	
	
	self thread showLazeMessage();	
	self thread waitForLazeDiscard();
	
	weapon = self getLastWeapon();
	secondaryWeapon = undefined;	
	primaryWeapons = self GetWeaponsListPrimaries();
	foreach	( primaryWeapon in primaryWeapons )
	{
		if ( primaryWeapon != weapon )
		{
			secondaryWeapon = primaryWeapon;
			self takeWeapon( secondaryWeapon );
			break;
		}
	}	
	self _giveWeapon("uav_strike_marker_mp");
	self switchToWeapon( "uav_strike_marker_mp" );

	traceData = undefined;
	for(;;)
	{
		msg = self waittill_any_return( "weapon_fired", "uav_strike_cancel" );
		
		if ( msg == "uav_strike_cancel" )
			break;
		
	 	origin = self GetEye();
		forward = AnglesToForward( self GetPlayerAngles() );
		endpoint = origin + forward * 15000;
		
		traceData = BulletTrace( origin, endpoint, true, self );		
		if ( isDefined(traceData["position"]) )
			break;
	}
	
	if ( isDefined( traceData ) )
	{	
		self notify( "uav_strike_used" );
		
		targetPosition = traceData["position"];		
		
		fxEnt = SpawnFx( level._effect[ "laserTarget" ], targetPosition);
		TriggerFx( fxEnt );
		fxEnt thread waitFxEntDie();
	
		magicBullet( "uav_strike_projectile_mp", targetPosition + (0,0,4000) , targetPosition, self );		
	}
	
	self takeWeapon( "uav_strike_marker_mp" );
	if ( msg != "uav_strike_cancel" )
		self switchToWeapon( weapon );
	if ( isDefined( secondaryWeapon ) )
		self _giveWeapon( secondaryWeapon );		
	
	if ( isDefined( traceData ) )
		self notify( "uav_strike_successful" );
}

waitFxEntDie()
{
	wait( 2 );
	self delete();
}


waittill_notify_or_timeout_hostmigration_pause( msg, timer )
{
	self endon( msg );
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( timer );
}


updateUAVModelVisibility()
{
	self endon ( "death" );

	for ( ;; )
	{
		level waittill_either ( "joined_team", "uav_update" );
		
		self hide();
		foreach ( player in level.players )
		{
			if ( level.teamBased )
			{
				if ( player.team != self.team )
					self showToPlayer( player );
			}
			else
			{
				if ( isDefined( self.owner ) && player == self.owner )
					continue;
					
				self showToPlayer( player );
			}
		}
	}	
}


damageTracker( isCounterUAV, isAdvanced )
{
	level endon ( "game_ended" );
	
	self setCanDamage( true );
	
	self.health = 999999; // keep it from dying anywhere in code
	if (isAdvanced)
		self.maxhealth = 2000; // this is the health we'll check
	else
		self.maxhealth = 1000; // this is the health we'll check
	self.damageTaken = 0; // how much damage has it taken

	
	for ( ;; )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );

		if ( !isPlayer( attacker ) )
		{
			if ( !isDefined( self ) )
				return;
				
			continue;
		}
			
		if ( isDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
			self.wasDamagedFromBulletPenetration = true;

		self.wasDamaged = true;

		modifiedDamage = damage;

		if( IsPlayer( attacker ) )
		{					
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "" );

			if( meansOfDeath == "MOD_RIFLE_BULLET" || meansOfDeath == "MOD_PISTOL_BULLET" )
			{
				if ( attacker _hasPerk( "specialty_armorpiercing" ) )
					modifiedDamage += damage * level.armorPiercingMod;
			}
		}

		if( IsDefined( weapon ) )
		{
			switch( weapon )
			{
			case "stinger_mp":
			case "javelin_mp":
				self.largeProjectileDamage = true;
				modifiedDamage = self.maxHealth + 1;
				break;

			case "sam_projectile_mp":
				self.largeProjectileDamage = true;		
				mult = 0.25;
				if( isAdvanced )
					mult = 0.15;
				modifiedDamage = self.maxHealth * mult; // takes about 2 burst of sam rockets
				break;
			}
		}
		
		self.damageTaken += modifiedDamage;
/#
		if ( IsDefined( self ) && GetDvarInt( "g_debugDamage" ) )
			PrintLn( "uav:" + self getEntityNumber() + " health:" + ( self.health - self.damageTaken ) + " attacker:" + attacker.clientid + " inflictor is player:" + isPlayer( attacker ) + " damage:" + modifiedDamage + " range:" + Distance( attacker.origin, self.origin ) );
#/

		if ( self.damageTaken >= self.maxHealth )
		{
			if ( isPlayer( attacker ) && ( !isDefined( self.owner ) || attacker != self.owner ) )
			{
				self Hide();
				forward = ( AnglesToRight( self.angles ) * 200 );
				playFx ( level.uav_fx[ "explode" ], self.origin, forward );

				//	TODO: pass in streakname and build the callout name from the streakname
				if ( isDefined( self.uavType ) && self.uavType == "remote_mortar" )
					thread teamPlayerCardSplash( "callout_destroyed_remote_mortar", attacker );
				else if ( isCounterUAV )
					thread teamPlayerCardSplash( "callout_destroyed_counter_uav", attacker );
				else
					thread teamPlayerCardSplash( "callout_destroyed_uav", attacker );

				thread maps\mp\gametypes\_missions::vehicleKilled( self.owner, self, undefined, attacker, damage, meansOfDeath, weapon );
				attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 50, weapon, meansOfDeath );
				attacker notify( "destroyed_killstreak" );
				
				if ( isDefined( self.UAVRemoteMarkedBy ) && self.UAVRemoteMarkedBy != attacker )
					self.UAVRemoteMarkedBy thread maps\mp\killstreaks\_remoteuav::remoteUAV_processTaggedAssist();				
			}
			
			self notify( "death" );
			return;
		}
	}
}


tryUseUAV( lifeId )
{
	return useUAV( "uav" );
}

tryUseUAVSupport( lifeId )
{
	return useUAV( "uav_support" );
}

tryUseDoubleUAV( lifeId )
{
	return useUAV( "double_uav" );
}

tryUseTripleUAV( lifeId )
{
	return useUAV( "triple_uav" );
}

tryUseCounterUAV( lifeId )
{
	return useUAV( "counter_uav" );
}

UAVStrikeSetup()
{
	self.usedStrikeUAV = 0;
}

tryUseUAVStrike( lifeId )
{
	if ( self.usedStrikeUAV == 0 )
	{
		self.usedStrikeUAV = 1;
		useUAV( "uav_strike" );
	}
	self thread waitForLazedTarget();
	return monitorUAVStrike();
}

tryUseDirectionalUAV( lifeId )
{
	return useUAV( "directional_uav" );
}

useUAV( uavType )
{
	if ( ! self validateUseStreak() )
		return false;
	
	self maps\mp\_matchdata::logKillstreakEvent( uavType, self.origin );

	team = self.pers["team"];		
	useTime = level.radarViewTime;

/#
	useTime = GetDvarInt( "scr_uav_timeout", level.radarViewTime );
#/

	level thread launchUAV( self, team, useTime, uavType );	

	switch( uavType )
	{
	case "counter_uav":
		self notify( "used_counter_uav" );
		break;
	case "double_uav":
		self notify( "used_double_uav" );
		break;
	case "triple_uav":
		level thread teamPlayerCardSplash( "used_triple_uav", self, team );
		self notify( "used_triple_uav" );
		break;
	case "directional_uav":
		self.radarShowEnemyDirection = true;
		if( level.teambased )
		{
			foreach( player in level.players )
			{
				if( player.pers["team"] == team )
				{
					player.radarShowEnemyDirection = true;					
				}
			}
		}
		level thread teamPlayerCardSplash( "used_directional_uav", self, team );
		self notify( "used_directional_uav" );
		break;
	default:
		self notify( "used_uav" );
		break;
	}
	
	return true;
}


UAVTracker()
{
	level endon ( "game_ended" );
	
	for ( ;; )
	{
		level waittill ( "uav_update" );
		
		if ( level.teamBased )
		{
			updateTeamUAVStatus( "allies" );
			updateTeamUAVStatus( "axis" );		
		}
		else
		{
			updatePlayersUAVStatus();
		}
	}
}

_getRadarStrength( team )
{
	activeUAVs = 0;
	activeCounterUAVs = 0;
	

	foreach ( uav in level.UAVModels[team] )
	{
		if ( uav.uavType == "counter" )
			continue;
		
		if ( uav.uavType == "remote_mortar" )
			continue;
	
		activeUAVs += uav.value;
	}	

	
	foreach ( uav in level.UAVModels[level.otherTeam[team] ] )
	{
		if ( uav.uavType != "counter" )
			continue;
		
		activeCounterUAVs += uav.value;
	}	

	
	if( activeCounterUAVs > 0 )
		radarStrength = -3;
	else
		radarStrength = activeUAVs;
	
	strengthMin = GetUAVStrengthMin();
	strengthMax = GetUAVStrengthMax();	
	
	//clamp between min/max
	if( radarStrength <= strengthMin )
	{
		radarStrength = strengthMin;
	}
	else if( radarStrength >= strengthMax ) 
	{
		radarStrength = strengthMax;	
	}
	
	return radarStrength;
}


updateTeamUAVStatus( team )
{
	radarStrength = _getRadarStrength( team );

	setTeamRadarStrength( team, radarStrength );

	if ( radarStrength >= GetUAVStrengthLevelNeutral() )
		unblockTeamRadar( team );
	else
		blockTeamRadar( team );
	
	if ( radarStrength <= GetUAVStrengthLevelNeutral() )
	{
		setTeamRadarWrapper( team, 0 );
		updateTeamUAVType( team );
		return;
	}
	
	if ( radarStrength >= GetUAVStrengthLevelShowEnemyFastSweep() )
		level.radarMode[team] = "fast_radar";
	else
		level.radarMode[team] = "normal_radar";

	updateTeamUAVType( team );
	setTeamRadarWrapper( team, 1 );	
}

//for FFA
updatePlayersUAVStatus()
{
	strengthMin = GetUAVStrengthMin();
	strengthMax = GetUAVStrengthMax();
	strengthDirectional = GetUAVStrengthLevelShowEnemyDirectional();
	
	//allPlayersCounterUAVTotal = 0;
	////calculate total counter uavs that currently exists across all players
	//foreach ( player in level.players )
	//{
	//	allPlayersCounterUAVTotal += level.activeCounterUAVs[ player.guid ];		
	//}
	
	foreach ( player in level.players )
	{
		radarStrength = level.activeUAVs[ player.guid + "_radarStrength" ];

		// if there are any counters up that aren't this player's then they are blocked
		foreach( enemyPlayer in level.players )
		{
			if( enemyPlayer == player )
				continue;

			activeCounterUAVs = level.activeCounterUAVs[ enemyPlayer.guid ];
			if( activeCounterUAVs > 0 )
			{
				radarStrength = -3;
				break;
			}
		}

		//clamp between min/max
		if( radarStrength <= strengthMin )
		{
			radarStrength = strengthMin;
		}
		else if( radarStrength >= strengthMax ) 
		{
			radarStrength = strengthMax;	
		}
			
		player.radarstrength = radarStrength;
				
		if ( radarStrength >= GetUAVStrengthLevelNeutral() )
			player.isRadarBlocked = false;
		else
			player.isRadarBlocked = true;
				
				
		if ( radarStrength <= GetUAVStrengthLevelNeutral()  )
		{
			player.hasRadar = false;
			player.radarShowEnemyDirection = false;
			continue;
		}
		
		if ( radarStrength >= GetUAVStrengthLevelShowEnemyFastSweep() )
			player.radarMode = "fast_radar";
		else
			player.radarMode = "normal_radar";
			
		//set directional status
		player.radarShowEnemyDirection = radarStrength >= strengthDirectional;
		
		player.hasRadar = true;
	}
}


blockPlayerUAV()
{
	self endon ( "disconnect" );
	
	self notify ( "blockPlayerUAV" );
	self endon ( "blockPlayerUAV" );

	self.isRadarBlocked = true;
	
	wait ( level.uavBlockTime );

	self.isRadarBlocked = false;

	//self iPrintLn( &"MP_WAR_COUNTER_RADAR_EXPIRED" );
}


updateTeamUAVType( team )
{
	shouldBeDirectional = _getRadarStrength( team ) >= GetUAVStrengthLevelShowEnemyDirectional();

	foreach ( player in level.players )
	{
		if ( player.team == "spectator" )
			continue;
		
		player.radarMode = level.radarMode[player.team];
				
		//use direction based on uav signal strength
		if( player.team == team )
		{
			player.radarShowEnemyDirection = shouldBeDirectional;			
		}		
	}
}

usePlayerUAV( doubleUAV, useTime )
{
	level endon("game_ended");
	self endon("disconnect");

	self notify ( "usePlayerUAV" );
	self endon ( "usePlayerUAV" );
	
	if ( doubleUAV )
		self.radarMode = "fast_radar";
	else
		self.radarMode = "normal_radar";

	self.hasRadar = true;
	
	wait ( useTime );
	
	self.hasRadar = false;
	
	//self iPrintLn( &"MP_WAR_RADAR_EXPIRED" );
}


setTeamRadarWrapper( team, value )
{
	setTeamRadar( team, value );
	level notify( "radar_status_change", team );
}



handleIncomingStinger()
{
	level endon ( "game_ended" );
	self endon ( "death" );
	
	for ( ;; )
	{
		level waittill ( "stinger_fired", player, missile, lockTarget );
		
		if ( !IsDefined( lockTarget ) || (lockTarget != self) )
			continue;
			
		missile thread stingerProximityDetonate( lockTarget, player );
	}
}


stingerProximityDetonate( targetEnt, player )
{
	self endon ( "death" );

	minDist = distance( self.origin, targetEnt GetPointInBounds( 0, 0, 0 ) );
	lastCenter = targetEnt GetPointInBounds( 0, 0, 0 );

	for ( ;; )
	{
		// UAV already destroyed
		if ( !isDefined( targetEnt ) )
			center = lastCenter;
		else
			center = targetEnt GetPointInBounds( 0, 0, 0 );
			
		lastCenter = center;		
		
		curDist = distance( self.origin, center );
		
		if ( curDist < minDist )
			minDist = curDist;
		
		if ( curDist > minDist )
		{
			if ( curDist > 1536 )
				return;
				
			RadiusDamage( self.origin, 1536, 600, 600, player, "MOD_EXPLOSIVE", "stinger_mp" );
			playFx( level.stingerFXid, self.origin );

			//self playSound( "remotemissile_explode" );
			self hide();
			
			self notify("deleted");
			wait ( 0.05 );
			self delete();
			player notify( "killstreak_destroyed" );
		}
		
		wait ( 0.05 );
	}	
}


addUAVModel() // self == uavmodel
{
	if ( level.teamBased )
		level.UAVModels[ self.team ][level.UAVModels[ self.team ].size] = self;
	else
		level.UAVModels[ self.owner.guid + "_" + getTime() ] = self;	
}	


removeUAVModel() // self == uavmodel
{
	UAVModels = [];

	if ( level.teamBased )
	{
		team = self.team;
		
		foreach ( uavModel in level.UAVModels[team] )
		{
			if ( !isDefined( uavModel ) )
				continue;
				
			UAVModels[UAVModels.size] = uavModel;
		}

		level.UAVModels[team] = UAVModels;
	}
	else
	{
		foreach ( uavModel in level.UAVModels )
		{
			if ( !isDefined( uavModel ) )
				continue;
				
			UAVModels[UAVModels.size] = uavModel;
		}

		level.UAVModels = UAVModels;
	}	
}


addActiveUAV() // self == uav model
{
	if ( level.teamBased )
	{
		level.activeUAVs[self.team]++;	
	}
	else
	{
		level.activeUAVs[ self.owner.guid ]++;
		level.activeUAVs[ self.owner.guid + "_radarStrength" ] += self.value;
	}

/*
	if ( level.teamBased )
	{
		foreach ( player in level.players )
		{
			if ( player.team == self.team )
				player iPrintLn( &"MP_WAR_RADAR_ACQUIRED", self.owner, level.radarViewTime );
			else if ( player.team == level.otherTeam[self.team] )
				player iPrintLn( &"MP_WAR_RADAR_ACQUIRED_ENEMY", level.radarViewTime  );
		}
	}	
	else
	{
		foreach ( player in level.players )
		{
			if ( player == self.owner )
				player iPrintLn( &"MP_WAR_RADAR_ACQUIRED", self.owner, level.radarViewTime );
			else
				player iPrintLn( &"MP_WAR_RADAR_ACQUIRED_ENEMY", level.radarViewTime );
		}
	}
*/
}


addActiveCounterUAV()
{
	if ( level.teamBased )
		level.activeCounterUAVs[self.team]++;	
	else
		level.activeCounterUAVs[self.owner.guid]++;	
/*
	if ( level.teamBased )
	{
		foreach ( player in level.players )
		{
			if ( player.team == self.team )
				player iPrintLn( &"MP_WAR_COUNTER_RADAR_ACQUIRED", self.owner, level.uavBlockTime );
			else if ( player.team == level.otherTeam[self.team] )
				player iPrintLn( &"MP_WAR_COUNTER_RADAR_ACQUIRED_ENEMY", level.uavBlockTime );
		}
	}	
	else
	{
		foreach ( player in level.players )
		{
			if ( player == self.owner )
				player iPrintLn( &"MP_WAR_COUNTER_RADAR_ACQUIRED", self.owner, level.uavBlockTime );
			else
				player iPrintLn( &"MP_WAR_COUNTER_RADAR_ACQUIRED_ENEMY", level.uavBlockTime );
		}
	}
*/
}


removeActiveUAV() // self == uav model
{
	if ( level.teamBased )
	{
		level.activeUAVs[self.team]--;
		
		if ( !level.activeUAVs[self.team] )
		{
			//printOnTeam( &"MP_WAR_RADAR_EXPIRED", self.team );
			//printOnTeam( &"MP_WAR_RADAR_EXPIRED_ENEMY", level.otherTeam[self.team] );
		}
	}
	else if ( isDefined( self.owner ) )
	{
		level.activeUAVs[ self.owner.guid ]--;
		level.activeUAVs[ self.owner.guid + "_radarStrength" ] -= self.value;
	}
}


removeActiveCounterUAV()
{
	if ( level.teamBased )
	{
		level.activeCounterUAVs[self.team]--;

		if ( !level.activeCounterUAVs[self.team] )
		{
			//printOnTeam( &"MP_WAR_COUNTER_RADAR_EXPIRED", self.team );
			//printOnTeam( &"MP_WAR_COUNTER_RADAR_EXPIRED_ENEMY", level.otherTeam[self.team] );
		}
	}
	else if ( isDefined( self.owner ) )
	{
		level.activeCounterUAVs[self.owner.guid]--;
	}
}
