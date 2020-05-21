#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;

/*
	Drop Zone
	Objective: 	Score points for your team over time by holding the drop zone.
				Periodic carepackage awarded to player who's been in drop zone the longest.
	Map ends:	When one team reaches the score limit, or time limit is reached
	Respawning:	No wait / Near teammates / Near drop zone

	Level requirementss
	------------------
		Start Spawnpoints:
			classname		mp_sab_spawn_allies_start, mp_sab_spawn_axis_start
			
		Spawnpoints:
			classname		mp_tdm_spawn	
			All players spawn from these. The spawnpoint chosen is dependent on the current locations of drop zone, teammates, and enemies
			at the time of spawn. Players generally spawn behind their teammates relative to the direction of enemies.

		Spectator Spawnpoints:
			classname		mp_global_intermission
			Spectators spawn from these and intermission is viewed from these positions.
			Atleast one is required, any more and they are randomly chosen between.
*/

GRND_ZONE_TOUCH_RADIUS = 300;
GRND_ZONE_DROP_RADIUS = 72;

main()
{
	if(getdvar("mapname") == "mp_background")
		return;
	
	maps\mp\gametypes\_globallogic::init();
	maps\mp\gametypes\_callbacksetup::SetupCallbacks();
	maps\mp\gametypes\_globallogic::SetupCallbacks();

	if ( isUsingMatchRulesData() )
	{
		level.initializeMatchRules = ::initializeMatchRules;
		[[level.initializeMatchRules]]();
		level thread reInitializeMatchRulesOnMigration();	
	}
	else
	{
		registerRoundSwitchDvar( level.gameType, 0, 0, 9 );
		registerTimeLimitDvar( level.gameType, 10 );
		registerScoreLimitDvar( level.gameType, 20000 );
		registerRoundLimitDvar( level.gameType, 1 );
		registerWinLimitDvar( level.gameType, 1 );
		registerNumLivesDvar( level.gameType, 0 );
		registerHalfTimeDvar( level.gameType, 0 );
		
		level.matchRules_dropTime = 30;
		level.matchRules_zoneSwitchTime = 120;		
		level.matchRules_damageMultiplier = 0;
		level.matchRules_vampirism = 0;			
	}

	level.teamBased = true;
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onSpawnPlayer = ::onSpawnPlayer;	
	
	if ( level.matchRules_damageMultiplier || level.matchRules_vampirism )
		level.modifyPlayerDamage = maps\mp\gametypes\_damage::gamemodeModifyPlayerDamage;
	
	level.grnd_fx["smoke"] = loadFx( "smoke/airdrop_flare_mp_effect_now" );
	level.grnd_fx["flare"] = loadFx( "smoke/signal_smoke_airdrop" );
	
	createZones();
}


initializeMatchRules()
{
	//	set common values
	setCommonRulesFromMatchRulesData();
	
	//	set everything else (private match options, default .cfg file values, and what normally is registered in the 'else' below)
	level.matchRules_dropTime = GetMatchRulesData( "grndData", "dropTime" );
	level.matchRules_zoneSwitchTime = 60 * GetMatchRulesData( "grndData", "zoneSwitchTime" );
	
	SetDynamicDvar( "scr_grnd_roundswitch", 0 );
	registerRoundSwitchDvar( "grnd", 0, 0, 9 );
	SetDynamicDvar( "scr_grnd_roundlimit", 1 );
	registerRoundLimitDvar( "grnd", 1 );		
	SetDynamicDvar( "scr_grnd_winlimit", 1 );
	registerWinLimitDvar( "grnd", 1 );			
	SetDynamicDvar( "scr_grnd_halftime", 0 );
	registerHalfTimeDvar( "grnd", 0 );
		
	SetDynamicDvar( "scr_grnd_promode", 0 );
}


onPrecacheGameType()
{
	precacheShader( "waypoint_captureneutral" );
	precacheShader( "waypoint_capture" );
	precacheShader( "waypoint_defend" );	
	
	precacheModel( "prop_flag_neutral" );
	
	precacheString( &"OBJECTIVES_GRND" );	
	precacheString( &"OBJECTIVES_GRND_SCORE" );	
	precacheString( &"OBJECTIVES_GRND_HINT" );	
	precacheString( &"OBJECTIVES_GRND_CONFIRM" );	
	precacheString( &"MP_CALLING_AIRDROP" );
	precacheString( &"MP_NEXT_DROP_ZONE_IN" );
	
	precacheModel( "weapon_us_smoke_grenade_burnt2" );
}


onStartGameType()
{
	setClientNameMode("auto_change");

	if ( !isdefined( game["switchedsides"] ) )
		game["switchedsides"] = false;

	setObjectiveText( "allies", &"OBJECTIVES_GRND" );
	setObjectiveText( "axis", &"OBJECTIVES_GRND" );
	
	if ( level.splitscreen )
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_GRND" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_GRND" );
	}
	else
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_GRND_SCORE" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_GRND_SCORE" );
	}
	setObjectiveHintText( "allies", &"OBJECTIVES_GRND_HINT" );
	setObjectiveHintText( "axis", &"OBJECTIVES_GRND_HINT" );
			
	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );		
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_sab_spawn_allies_start" );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_sab_spawn_axis_start" );		
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_tdm_spawn" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_tdm_spawn" );	
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );	
	
	//	get the central loction for first DZ using the SAB bomb, before it is removed
	centerLocObj = getEnt( "sab_bomb", "targetname" );	
	level.grnd_centerLoc = centerLocObj.origin;	
	
	maps\mp\gametypes\_rank::registerScoreInfo( "zone_kill", 100 );	
	maps\mp\gametypes\_rank::registerScoreInfo( "zone_tick",  20 );
	
	allowed[0] = level.gameType;
	allowed[1] = "tdm";	
	
	maps\mp\gametypes\_gameobjects::main(allowed);	
	
	level.grnd_timerDisplay = createServerTimer( "objective", 1.4 );
	level.grnd_timerDisplay setPoint( "TOPLEFT", "TOPLEFT", 115, 5 );
	level.grnd_timerDisplay.label = &"MP_NEXT_DROP_ZONE_IN";
	level.grnd_timerDisplay.alpha = 0;
	level.grnd_timerDisplay.archived = false;
	level.grnd_timerDisplay.hideWhenInMenu = true;	
	thread hideHudElementOnGameEnd( level.grnd_timerDisplay );
	
	initFirstZone();
}


initFirstZone()
{
	level.zonesCycling = false;	
	
	//	find the closest zone to center	
	shortestDistance = 999999;
	shortestDistanceIndex = 0;
	for ( i=0; i<level.grnd_dropZones[level.script].size; i++ )
	{
		dropZone = level.grnd_dropZones[level.script][i];
		distToCenter = distance2d( level.grnd_centerLoc, dropZone );
		if ( distToCenter < shortestDistance )
		{
			shortestDistance = distToCenter;
			shortestDistanceIndex = i;
		}
	}		
	level.grnd_initialIndex = shortestDistanceIndex;
	initilPos = level.grnd_dropZones[level.script][shortestDistanceIndex];	
	
	//	create marker
	level.grnd_zone = spawn( "script_model", initilPos );
	level.grnd_zone.origin = initilPos;
	level.grnd_zone.angles = ( 90, 0, 0 );
	level.grnd_zone setModel( "weapon_us_smoke_grenade_burnt2" );
	
	//	spawning
	level.favorCloseSpawnEnt = level.grnd_zone;
	level.favorCloseSpawnScalar = 5;	
	
	//	make the rest
	level thread initZones();	
}


initZones()
{
	level.grnd_zones = [];
	for ( i=0; i<level.grnd_dropZones[level.script].size; i++ )
	{
		dropZone = level.grnd_dropZones[level.script][i];
		level.grnd_zones[i] = spawn( "script_origin", dropZone );
		level.grnd_zones[i].origin = dropZone;
		wait( 0.05 );
	}
	
	level.grnd_zones[level.grnd_initialIndex] delete();
	level.grnd_zones[level.grnd_initialIndex] = undefined;
	level.grnd_zones = array_removeUndefined( level.grnd_zones );	
}


getSpawnPoint()
{
	if ( level.inGracePeriod )
	{
		spawnPoints = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_sab_spawn_" + self.pers["team"] + "_start" );
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random( spawnPoints );
	}
	else
	{
		spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( self.pers["team"] );
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( spawnPoints );
	}
	
	return spawnPoint;
}


onSpawnPlayer()
{				
	//	in/out zone indicator
	if ( !isDefined( self.inGrindZone ) )
	{
		level thread setPlayerMessages( self );	
		
		//	let the first player in activate this
		if ( !level.zonesCycling )
		{
			level thread cycleZones();	
			level thread locationScoring();	
		}
	}		
		
	level notify ( "spawned_player" );	
}


setPlayerMessages( player )
{
	level endon( "game_ended" );	
	
	gameFlagWait( "prematch_done" );	
	
	//	points
	player.inGrindZonePoints = 0;
	
	//	hud indicator		
	player.grndHUDText = player createFontString( "small", 1.6 );	
	player.grndHUDText setPoint( "TOP LEFT", "TOP LEFT", 115, 22 );
	player.grndHUDText.alpha = 1;
	player.grndHUDText.hideWhenInMenu = true;	
	level thread hideHudElementOnGameEnd( player.grndHUDText );	
	
	//	hud icon
	player.grndHeadIcon = level.grnd_zone maps\mp\_entityheadIcons::setHeadIcon( player, "waypoint_captureneutral", (0,0,0), 14, 14, undefined, undefined, undefined, undefined, undefined, false );

	//	minimap waypoint
	player.grndObjId = maps\mp\gametypes\_gameobjects::getNextObjID();	
	objective_add( player.grndObjId, "invisible", (0,0,0) );
	objective_player( player.grndObjId, player getEntityNumber() );	
	Objective_OnEntity( player.grndObjId, level.grnd_zone );
	objective_icon( player.grndObjId, "waypoint_captureneutral" );
	objective_state( player.grndObjId, "active" );
	
	if ( distance2D( level.grnd_zone.origin, player.origin ) < GRND_ZONE_TOUCH_RADIUS )	
	{
		player.inGrindZone = true;
		player.grndHUDText setText( &"OBJECTIVES_GRND_CONFIRM" );	
		player.grndHUDText.color = (0.6,1,0.6);
		player.grndHeadIcon.alpha = 0;
	}
	else
	{
		player.inGrindZone = false;
		player.grndHUDText setText( &"OBJECTIVES_GRND_HINT" );	
		player.grndHUDText.color = (1,0.6,0.6);	
		player.grndHeadIcon.alpha = 0.85;
	}
	
	player.grnd_wasSpectator = false;
	if ( player.team == "spectator" )
	{
		player.inGrindZone = false;
		player.inGrindZonePoints = 0;
		player.grndHeadIcon.alpha = 0;
		player.grndHUDText.alpha = 0;	
		player.grnd_wasSpectator = true;		
	}	
	
	player thread grndTracking();		
}


getNextZone()
{
	pos = undefined;
	index = undefined;
	
	if ( level.grnd_zones.size > 2 )
	{
		//	get the distance to the current zone from all the remaining zones
		//	set index and save furthest and closest along the way
		closestDistance = 999999;
		furthestDistance = 0;
		for ( i=0; i<level.grnd_zones.size; i++ )
		{
			level.grnd_zones[i].index = i;
			level.grnd_zones[i].distToZone = distance( level.grnd_zones[i].origin, level.grnd_zone.origin );
			if ( level.grnd_zones[i].distToZone > furthestDistance )
				furthestDistance = level.grnd_zones[i].distToZone;
			else if ( level.grnd_zones[i].distToZone < closestDistance )
				closestDistance = level.grnd_zones[i].distToZone;
		}
		
		//	try to get a grouping of far zones to randomly choose from
		farZones = [];
		closeZones = [];
		halfDistance = int( ( closestDistance + furthestDistance ) / 2 );
		for ( i=0; i<level.grnd_zones.size; i++ )
		{
			if ( level.grnd_zones[i].distToZone >= halfDistance )
				farZones[farZones.size] = level.grnd_zones[i];
			else
				closeZones[closeZones.size] = level.grnd_zones[i];
		}	
		zone = undefined;
		if ( farZones.size > 1 )
			zone = farZones[ randomIntRange( 0, farZones.size ) ];
		else
			zone = farZones[0];		
		index = zone.index;		
	}
	else if ( level.grnd_zones.size == 2 )
	{
		distanceA = distance( level.grnd_zones[0].origin, level.grnd_zone.origin );
		distanceB = distance( level.grnd_zones[1].origin, level.grnd_zone.origin );		
		if ( distanceA > distanceB )
			index = 0;
		else	
			index = 1;		
	}
	else if ( level.grnd_zones.size == 1 )
	{
		index = 0;
	}
	
	if ( isDefined( index ) )
	{
		pos = level.grnd_zones[index].origin;
		level.grnd_zones[index] delete();
		level.grnd_zones[index] = undefined;		
		level.grnd_zones = array_removeUndefined( level.grnd_zones );		
	}
	else
	{
		//	start all over
		pos = level.grnd_dropZones[level.script][level.grnd_initialIndex];
		level thread initZones();		
	}
	
	return pos;	
}


cycleZones()
{	
	level endon( "game_ended" );	
	
	gameFlagWait( "prematch_done" );	
		
	while( true )
	{	
		initialScores["axis"] = game["teamScores"]["axis"];
		initialScores["allies"] = game["teamScores"]["allies"];
		
		//	move zone
		pos = undefined;
		if ( !level.zonesCycling )
		{
			level.zonesCycling = true;
			pos = level.grnd_zone.origin;
		}
		else
		{
			pos = getNextZone();			
			StopFxOnTag( level.grnd_fx["smoke"], level.grnd_zone, "tag_fx" );
			wait( 0.05 );					
		}		
		traceStart = pos;
		traceEnd = pos + (0,0,-1000);
		trace = bulletTrace( traceStart, traceEnd, false, undefined );		
		level.grnd_zone.origin = trace["position"]+(0,0,1);
		
		//	smoke
		wait( 0.05 );
		PlayFxOnTag( level.grnd_fx["smoke"], level.grnd_zone, "tag_fx" );	
	
		//	reset drops
		if ( level.matchRules_dropTime )
			level thread randomDrops();
		
		//	wait
		level.grnd_timerDisplay.label = &"MP_NEXT_DROP_ZONE_IN";
		level.grnd_timerDisplay setTimer( level.matchRules_zoneSwitchTime );
		level.grnd_timerDisplay.alpha = 1;			
		maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( level.matchRules_zoneSwitchTime );				
		level.grnd_timerDisplay.alpha = 0;	
		
		//	audio cue for progress
		if ( game["teamScores"]["axis"] - initialScores["axis"] > game["teamScores"]["allies"] - initialScores["allies"] )
		{
			playSoundOnPlayers( "mp_obj_captured", "axis" );
			playSoundOnPlayers( "mp_enemy_obj_captured", "allies" );
		}		
		else if ( game["teamScores"]["allies"] - initialScores["allies"] > game["teamScores"]["axis"] - initialScores["axis"] )
		{
			playSoundOnPlayers( "mp_obj_captured", "allies" );
			playSoundOnPlayers( "mp_enemy_obj_captured", "axis" );
		}		
	}			
}


grndTracking()
{
	self endon( "disconnect" );
	level endon( "game_ended" );
	
	while( true )
	{
		if ( !self.grnd_wasSpectator && self.team == "spectator" )
		{
			self.inGrindZone = false;
			self.inGrindZonePoints = 0;
			self.grndHeadIcon.alpha = 0;
			self.grndHUDText.alpha = 0;	
			self.grnd_wasSpectator = true;		
		}
		else if ( self.team != "spectator" )
		{
			if ( ( self.grnd_wasSpectator || !self.inGrindZone ) && distance2D( level.grnd_zone.origin, self.origin ) < GRND_ZONE_TOUCH_RADIUS )	
			{
				self.inGrindZone = true;
				self.inGrindZonePoints = 0;
				self.grndHUDText setText( &"OBJECTIVES_GRND_CONFIRM" );	
				self.grndHUDText.color = (0.6,1,0.6);
				self.grndHUDText.alpha = 1;
				self.grndHeadIcon.alpha = 0;
			}
			else if ( ( self.grnd_wasSpectator || self.inGrindZone ) && distance2D( level.grnd_zone.origin, self.origin ) >= GRND_ZONE_TOUCH_RADIUS )
			{
				self.inGrindZone = false;
				self.inGrindZonePoints = 0;
				self.grndHUDText setText( &"OBJECTIVES_GRND_HINT" );	
				self.grndHUDText.color = (1,0.6,0.6);
				self.grndHUDText.alpha = 1;
				self.grndHeadIcon.alpha = 0.85;
			}
			self.grnd_wasSpectator = false;
		}
		
		wait( 0.05 );
	}	
}


locationScoring()
{
	level endon( "game_ended" );
	
	gameFlagWait( "prematch_done" );
	
	score = maps\mp\gametypes\_rank::getScoreInfoValue( "zone_tick" );
	assert( isDefined( score ) );	
	
	while( true )
	{
		numPlayers["axis"] = 0;
		numPlayers["allies"] = 0;
		
		//	score
		foreach( player in level.players )
		{
			if ( isDefined( player.inGrindZone ) && isAlive( player ) && distance2D( level.grnd_zone.origin, player.origin ) < GRND_ZONE_TOUCH_RADIUS )
			{
				numPlayers[player.pers["team"]]++;
				player.inGrindZonePoints += score;				
			}
		}
		if ( numPlayers["axis"] )
			maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( "axis", score * numPlayers["axis"] );
		if ( numPlayers["allies"] )
			maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( "allies", score * numPlayers["allies"] );
		
		//	waypoints and compasspings
		if ( numPlayers["axis"] == numPlayers["allies"] )
		{
			foreach( player in level.players )
			{
				if ( isDefined( player.inGrindZone ) )
				{
					player.grndHeadIcon setShader( "waypoint_captureneutral", 14, 14 );
					player.grndHeadIcon setWaypoint( false, false, false, false );
					objective_icon( player.grndObjId, "waypoint_captureneutral" );
				}
			}			
		}
		else
		{
			foreach( player in level.players )
			{
				if ( isDefined( player.inGrindZone ) )
				{
					if ( numPlayers[player.pers["team"]] > numPlayers[level.otherTeam[player.pers["team"]]] )
					{
						player.grndHeadIcon setShader( "waypoint_defend", 14, 14 );
						player.grndHeadIcon setWaypoint( false, false, false, false );
						objective_icon( player.grndObjId, "waypoint_defend" );					
					}
					else
					{
						player.grndHeadIcon setShader( "waypoint_capture", 14, 14 );
						player.grndHeadIcon setWaypoint( false, false, false, false );
						objective_icon( player.grndObjId, "waypoint_capture" );					
					}
				}
			}			
		}		
		
		//	wait
		maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 1.0 );
	}
}

randomDrops()
{
	level endon( "game_ended" );
	level notify( "reset_grnd_drops" );
	level endon( "reset_grnd_drops" );
	
	//	try for no repeats per zone
	level.grnd_previousCrateTypes = [];
	
	while( true )
	{
		owner = getBestPlayer();			
		numIncomingVehicles = 1;
		if( isDefined( owner ) && 
			currentActiveVehicleCount() < maxVehiclesAllowed() && 
			level.fauxVehicleCount + numIncomingVehicles < maxVehiclesAllowed() && 
			level.numDropCrates < 8 )
		{
			owner thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_EARNED_CAREPACKAGE" );
			thread teamPlayerCardSplash( "callout_earned_carepackage", owner );			
			owner thread leaderDialog( level.otherTeam[ owner.team ] + "_enemy_airdrop_assault_inbound", level.otherTeam[ owner.team ] );
			owner thread leaderDialog( owner.team + "_friendly_airdrop_assault_inbound", owner.team );
			playSoundOnPlayers( "mp_war_objective_taken", owner.team );
			playSoundOnPlayers( "mp_war_objective_lost", level.otherTeam[owner.team] );			
			
			position = level.grnd_zone.origin + ( randomIntRange( (-1*GRND_ZONE_DROP_RADIUS), GRND_ZONE_DROP_RADIUS ), randomIntRange( (-1*GRND_ZONE_DROP_RADIUS), GRND_ZONE_DROP_RADIUS ), 0 );
						
			crateType = getDropZoneCrateType();
			if ( isSubStr( toLower( crateType ), "juggernaut" ) )
			{
				level thread maps\mp\killstreaks\_airdrop::doC130FlyBy( owner, position, randomFloat( 360 ), crateType );
			}
			else if ( crateType == "mega" )
			{
				level thread maps\mp\killstreaks\_airdrop::doMegaC130FlyBy( owner, position, randomFloat( 360 ), "airdrop_grnd", -360 );
			}
			else
			{
				level thread maps\mp\killstreaks\_airdrop::doFlyBy( owner, position, randomFloat( 360 ), "airdrop_grnd", 0, crateType );
			}
			
			waitTime = level.matchRules_dropTime;
		}		
		else
			waitTime = 0.5;		
		
		maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( waitTime );
	}
}


getBestPlayer()
{		
	bestPlayer = undefined;
	bestPlayerPoints = 0;
		
	//	find the player with the currently highest accumulated points in the zone
	foreach ( player in level.players )
	{
		if ( isAlive( player ) )
		{
			if ( distance2D( level.grnd_zone.origin, player.origin ) < GRND_ZONE_TOUCH_RADIUS && player.inGrindZonePoints > bestPlayerPoints )
			{
				bestPlayer = player;
				bestPlayerPoints = player.inGrindZonePoints;
			}
		}
	}	
	
	//	may return undefined
	return bestPlayer;
}


getDropZoneCrateType()
{
	crateType = undefined;
	if ( !isDefined( level.grnd_previousCrateTypes["mega"] ) && level.numDropCrates == 0 && randomIntRange( 0, 100 ) < 5 )
	{
		crateType = "mega";
	}
	else
	{
		if ( level.grnd_previousCrateTypes.size )
		{
			maxTries = 200;
			while( maxTries )
			{
				crateType = maps\mp\killstreaks\_airdrop::getRandomCrateType( "airdrop_grnd" );				
				if ( isDefined( level.grnd_previousCrateTypes[crateType] ) )
					crateType = undefined;
				else
					break;
				
				maxTries--;
			}
		}
		
		if ( !isDefined( crateType ) )
			crateType = maps\mp\killstreaks\_airdrop::getRandomCrateType( "airdrop_grnd" );
	}
	
	//	track it
	level.grnd_previousCrateTypes[crateType] = 1;	
	if ( level.grnd_previousCrateTypes.size == 15 )
		level.grnd_previousCrateTypes = [];
		
	return crateType;	
}


hideHudElementOnGameEnd( hudElement )
{
	level waittill("game_ended");
	hudElement.alpha = 0;
}


createZones()
{
	level.grnd_dropZones = [];
	
	//	future way
	dropZones = getEntArray( "grnd_dropZone", "targetname" );
	if ( isDefined( dropZones ) && dropZones.size )
	{
		i=0;
		foreach ( dropZone in dropZones )
		{
			level.grnd_dropZones[level.script][i] = dropZone.origin;
			i++;
		}
	}
	else
	{	
		//	current way
		level.grnd_dropZones["mp_seatown"][0] 		= (-1226, -1399, 204);
		level.grnd_dropZones["mp_seatown"][1] 		= (1048, 886, 228);
		level.grnd_dropZones["mp_seatown"][2] 		= (-1982, 1494, 229);
		level.grnd_dropZones["mp_seatown"][3] 		= (-2297, -855, 210);
		level.grnd_dropZones["mp_seatown"][4] 		= (-2261, -334, 248);
		level.grnd_dropZones["mp_seatown"][5] 		= (-2048, 512, 248);
		level.grnd_dropZones["mp_seatown"][6] 		= (-1439, 1065, 72);
		level.grnd_dropZones["mp_seatown"][7] 		= (-410, 982, 127);
		level.grnd_dropZones["mp_seatown"][8] 		= (-666, -217, 226);
		level.grnd_dropZones["mp_seatown"][9] 		= (-523, -875, 260);
		level.grnd_dropZones["mp_seatown"][10] 		= (-345, -1449, 254);
		level.grnd_dropZones["mp_seatown"][11] 		= (1167, -533, 294);
		level.grnd_dropZones["mp_seatown"][12] 		= (367, 991, 179);
		level.grnd_dropZones["mp_seatown"][13] 		= (1106, 219, 292);
		
		level.grnd_dropZones["mp_dome"][0] 			= (97, 898, -240);
		level.grnd_dropZones["mp_dome"][1] 			= (-226, 1464, -231);
		level.grnd_dropZones["mp_dome"][2] 			= (-603, 194, -358);
		level.grnd_dropZones["mp_dome"][3] 			= (814, -406, -335);
		level.grnd_dropZones["mp_dome"][4] 			= (5, 1975, -231);
		level.grnd_dropZones["mp_dome"][5] 			= (-673, 1100, -284);
		level.grnd_dropZones["mp_dome"][6] 			= (669, 1028, -255);
		level.grnd_dropZones["mp_dome"][7] 			= (1231, 807, -267);
		level.grnd_dropZones["mp_dome"][8] 			= (709, 210, -342);
		level.grnd_dropZones["mp_dome"][9] 			= (1223, 10, -336);
		level.grnd_dropZones["mp_dome"][10]			= (-222, 418, -333);
		level.grnd_dropZones["mp_dome"][11]			= (501, -183, -330);
		
		level.grnd_dropZones["mp_plaza2"][0] 		= (221, 440, 754);
		level.grnd_dropZones["mp_plaza2"][1] 		= (155, 1763, 668);
		level.grnd_dropZones["mp_plaza2"][2] 		= (-430, 1871, 691);
		level.grnd_dropZones["mp_plaza2"][3] 		= (-1190, 1759, 668);
		level.grnd_dropZones["mp_plaza2"][4] 		= (-1273, 1279, 829);
		level.grnd_dropZones["mp_plaza2"][5] 		= (-593, 1274, 676);
		level.grnd_dropZones["mp_plaza2"][6] 		= (-251, 1006, 722);
		level.grnd_dropZones["mp_plaza2"][7] 		= (80, 1343, 676);
		level.grnd_dropZones["mp_plaza2"][8] 		= (397, -99, 708);
		level.grnd_dropZones["mp_plaza2"][9] 		= (-1109, 92, 741);
		level.grnd_dropZones["mp_plaza2"][10] 		= (-280, -195, 700);
		level.grnd_dropZones["mp_plaza2"][11] 		= (28, -1600, 668);
		level.grnd_dropZones["mp_plaza2"][12] 		= (764, -1752, 669);
		
		level.grnd_dropZones["mp_mogadishu"][0] 	= (1448, 1945, 39);
		level.grnd_dropZones["mp_mogadishu"][1] 	= (1499, -1193, 15);
		level.grnd_dropZones["mp_mogadishu"][2] 	= (791, -880, 16);
		level.grnd_dropZones["mp_mogadishu"][3] 	= (38, -1007, 16);
		level.grnd_dropZones["mp_mogadishu"][4] 	= (-691, -260, 22);
		level.grnd_dropZones["mp_mogadishu"][5] 	= (2, 52, 2);
		level.grnd_dropZones["mp_mogadishu"][6] 	= (664, 69, 12);
		level.grnd_dropZones["mp_mogadishu"][7] 	= (1676, 251, -1);
		level.grnd_dropZones["mp_mogadishu"][8] 	= (2314, 1860, 63);
		level.grnd_dropZones["mp_mogadishu"][9] 	= (73, 858, 3);
		level.grnd_dropZones["mp_mogadishu"][10] 	= (710, 837, 16);
		level.grnd_dropZones["mp_mogadishu"][11] 	= (-549, 829, 2);
		level.grnd_dropZones["mp_mogadishu"][12] 	= (34, 1850, 84);
		level.grnd_dropZones["mp_mogadishu"][13] 	= (-778, 2614, 157);
		level.grnd_dropZones["mp_mogadishu"][14] 	= (-204, 3206, 152);
		level.grnd_dropZones["mp_mogadishu"][15] 	= (752, 3189, 148);
		level.grnd_dropZones["mp_mogadishu"][16] 	= (692, 2354, 95);
		
		level.grnd_dropZones["mp_paris"][0] 		= (-931, -921, 110);
		level.grnd_dropZones["mp_paris"][1] 		= (1597, 1768, 47);
		level.grnd_dropZones["mp_paris"][2] 		= (716, 1809, 33);
		level.grnd_dropZones["mp_paris"][3] 		= (258, 2074, 36);
		level.grnd_dropZones["mp_paris"][4] 		= (459, 1067, 37);
		level.grnd_dropZones["mp_paris"][5] 		= (852, 1350, 118);
		level.grnd_dropZones["mp_paris"][6] 		= (1601, 897, 45);
		level.grnd_dropZones["mp_paris"][7] 		= (1286, 420, 41);
		level.grnd_dropZones["mp_paris"][8] 		= (1613, 181, 172);
		level.grnd_dropZones["mp_paris"][9] 		= (466, -752, 67);
		level.grnd_dropZones["mp_paris"][10] 		= (994, -625, 50);
		level.grnd_dropZones["mp_paris"][11] 		= (-211, -60, 63);
		level.grnd_dropZones["mp_paris"][12] 		= (-742, 177, 133);	
		level.grnd_dropZones["mp_paris"][13] 		= (-1532, 100, 250);
		level.grnd_dropZones["mp_paris"][14] 		= (-343, 1922, 121);
		level.grnd_dropZones["mp_paris"][15] 		= (-1127, 1555, 284);
		level.grnd_dropZones["mp_paris"][16] 		= (-2025, 1327, 316);
		level.grnd_dropZones["mp_paris"][17] 		= (-1039, 841, 187);			
		
		level.grnd_dropZones["mp_exchange"][0] 		= (-614, 1286, 113);
		level.grnd_dropZones["mp_exchange"][1] 		= (182, 1155, 148);
		level.grnd_dropZones["mp_exchange"][2] 		= (1018, 1254, 120);
		level.grnd_dropZones["mp_exchange"][3] 		= (2182, 1322, 145);
		level.grnd_dropZones["mp_exchange"][4] 		= (655, 815, 13);
		level.grnd_dropZones["mp_exchange"][5] 		= (761, -312, -18);
		level.grnd_dropZones["mp_exchange"][6] 		= (761, -771, 112);
		level.grnd_dropZones["mp_exchange"][7] 		= (635, -1450, 110);
		level.grnd_dropZones["mp_exchange"][8] 		= (152, -1538, 96);
		level.grnd_dropZones["mp_exchange"][9]		= (303, -824, 88);
		level.grnd_dropZones["mp_exchange"][10]		= (-953, -768, 45);
		level.grnd_dropZones["mp_exchange"][11]		= (2392, 1305, 144);
		level.grnd_dropZones["mp_exchange"][12]		= (1634, 1329, 151);
		level.grnd_dropZones["mp_exchange"][13]		= (1315, 743, 159);
		
		level.grnd_dropZones["mp_bootleg"][0] 		= (-1432, 1404, 8);
		level.grnd_dropZones["mp_bootleg"][1] 		= (-1017, 1787, -39);
		level.grnd_dropZones["mp_bootleg"][2] 		= (-590, 1514, -43);
		level.grnd_dropZones["mp_bootleg"][3] 		= (-588, 614, -12);
		level.grnd_dropZones["mp_bootleg"][4] 		= (-1732, 84, 11);
		level.grnd_dropZones["mp_bootleg"][5] 		= (-1809, -302, 140);
		level.grnd_dropZones["mp_bootleg"][6] 		= (-1649, -1147, 92);
		level.grnd_dropZones["mp_bootleg"][7] 		= (-884, -1035, -4);
		level.grnd_dropZones["mp_bootleg"][8] 		= (-719, -1673, 60);
		level.grnd_dropZones["mp_bootleg"][9] 		= (-335, -2111, 60);
		level.grnd_dropZones["mp_bootleg"][10] 		= (208, -1955, 68);
		level.grnd_dropZones["mp_bootleg"][11] 		= (-198, -1726, 60);
		level.grnd_dropZones["mp_bootleg"][12] 		= (100, -1101, -9);
		level.grnd_dropZones["mp_bootleg"][13] 		= (-427, -100, -8);
		level.grnd_dropZones["mp_bootleg"][14] 		= (949, -1132, -10);
		level.grnd_dropZones["mp_bootleg"][15] 		= (884, 1182, -28);
		level.grnd_dropZones["mp_bootleg"][16] 		= (242, 1194, -45);		
		
		level.grnd_dropZones["mp_carbon"][0] 		= (-3330, -3392, 3630);
		level.grnd_dropZones["mp_carbon"][1] 		= (-3635, -3735, 3630);
		level.grnd_dropZones["mp_carbon"][2] 		= (-3625, -4189, 3633);
		level.grnd_dropZones["mp_carbon"][3] 		= (-2992, -4339, 3627);
		level.grnd_dropZones["mp_carbon"][4] 		= (-2925, -4999, 3673);
		level.grnd_dropZones["mp_carbon"][5] 		= (-2573, -4771, 3784);
		level.grnd_dropZones["mp_carbon"][6] 		= (-1705, -4643, 3813);
		level.grnd_dropZones["mp_carbon"][7] 		= (-1799, -3957, 3813);
		level.grnd_dropZones["mp_carbon"][8] 		= (-2141, -3647, 3815);
		level.grnd_dropZones["mp_carbon"][9] 		= (-3212, -2879, 3807);
		level.grnd_dropZones["mp_carbon"][10] 		= (-1623, -3339, 3808);
		level.grnd_dropZones["mp_carbon"][11] 		= (-1223, -4234, 3834);
		level.grnd_dropZones["mp_carbon"][12] 		= (-896, -4888, 3944);
		level.grnd_dropZones["mp_carbon"][13] 		= (-228, -4535, 3975);
		level.grnd_dropZones["mp_carbon"][14] 		= (-257, -3865, 3956);
		level.grnd_dropZones["mp_carbon"][15] 		= (-215, -3260, 3967);
		level.grnd_dropZones["mp_carbon"][16] 		= (-535, -3798, 3966);
		
		level.grnd_dropZones["mp_hardhat"][0] 		= (2035, -229, 246);
		level.grnd_dropZones["mp_hardhat"][1] 		= (1959, -772, 352);
		level.grnd_dropZones["mp_hardhat"][2] 		= (1883, -1384, 351);
		level.grnd_dropZones["mp_hardhat"][3] 		= (848, -1520, 334);
		level.grnd_dropZones["mp_hardhat"][4] 		= (1326, -1380, 342);
		level.grnd_dropZones["mp_hardhat"][5] 		= (-338, -1273, 348);
		level.grnd_dropZones["mp_hardhat"][6] 		= (-821, -884, 348);
		level.grnd_dropZones["mp_hardhat"][7] 		= (-920, -290, 230);
		level.grnd_dropZones["mp_hardhat"][8] 		= (-463, -250, 333);
		level.grnd_dropZones["mp_hardhat"][9] 		= (-741, 208, 245);
		level.grnd_dropZones["mp_hardhat"][10] 		= (-201, 806, 437);
		level.grnd_dropZones["mp_hardhat"][11] 		= (224, 980, 436);
		level.grnd_dropZones["mp_hardhat"][12] 		= (1125, 656, 255);
		level.grnd_dropZones["mp_hardhat"][13] 		= (1531, 1241, 364);
		level.grnd_dropZones["mp_hardhat"][14] 		= (1522, 542, 244);	
		
		level.grnd_dropZones["mp_alpha"][0] 		= (-1979, 1653, 148);
		level.grnd_dropZones["mp_alpha"][1] 		= (-1392, 1623, 60);
		level.grnd_dropZones["mp_alpha"][2] 		= (-1697, 1205, 52);
		level.grnd_dropZones["mp_alpha"][3] 		= (-1671, 692, 54);
		level.grnd_dropZones["mp_alpha"][4] 		= (-572, -272, 55);
		level.grnd_dropZones["mp_alpha"][5] 		= (634, -345, 52);
		level.grnd_dropZones["mp_alpha"][6] 		= (391, 121, 60);
		level.grnd_dropZones["mp_alpha"][7] 		= (291, 1271, 60);
		level.grnd_dropZones["mp_alpha"][8] 		= (-459, 868, 52);
		level.grnd_dropZones["mp_alpha"][9] 		= (-353, 1334, 52);
		level.grnd_dropZones["mp_alpha"][10] 		= (-37, 1637, 52);
		level.grnd_dropZones["mp_alpha"][11] 		= (-5, 2226, 52);
		level.grnd_dropZones["mp_alpha"][12] 		= (-407, 2198, 196);
		
		level.grnd_dropZones["mp_village"][0] 		= (647, 1891, 332);
		level.grnd_dropZones["mp_village"][1] 		= (-26, 1749, 334);
		level.grnd_dropZones["mp_village"][2] 		= (104, 1292, 323);
		level.grnd_dropZones["mp_village"][3] 		= (-1064, 1552, 322);
		level.grnd_dropZones["mp_village"][4] 		= (-599, 886, 378);
		level.grnd_dropZones["mp_village"][5] 		= (-1038, 569, 317);
		level.grnd_dropZones["mp_village"][6] 		= (-1899, 1217, 336);
		level.grnd_dropZones["mp_village"][7] 		= (-1540, 289, 304);
		level.grnd_dropZones["mp_village"][8] 		= (-454, -277, 270);
		level.grnd_dropZones["mp_village"][9] 		= (-1734, -790, 365);
		level.grnd_dropZones["mp_village"][10] 		= (-1418, -1371, 431);
		level.grnd_dropZones["mp_village"][11] 		= (-928, -749, 417);
		level.grnd_dropZones["mp_village"][12] 		= (-861, -2105, 408);
		level.grnd_dropZones["mp_village"][13] 		= (-191, -1550, 400);
		level.grnd_dropZones["mp_village"][14] 		= (357, -678, 245);
		level.grnd_dropZones["mp_village"][15] 		= (-216, 295, 223);
		level.grnd_dropZones["mp_village"][16] 		= (162, -199, 229);
		level.grnd_dropZones["mp_village"][17] 		= (179, -3052, 447);
		level.grnd_dropZones["mp_village"][18] 		= (510, -1790, 375);
		level.grnd_dropZones["mp_village"][19] 		= (1089, -615, 398);
		level.grnd_dropZones["mp_village"][20] 		= (1631, 394, 297);
		level.grnd_dropZones["mp_village"][21] 		= (1007, 1385, 337);
		level.grnd_dropZones["mp_village"][22] 		= (992, 248, 330);
		level.grnd_dropZones["mp_village"][23] 		= (551, 732, 386);		
		
		level.grnd_dropZones["mp_lambeth"][0] 		= (-293, -1286, -180);
		level.grnd_dropZones["mp_lambeth"][1] 		= (-938, -785, -130);
		level.grnd_dropZones["mp_lambeth"][2] 		= (-375, -250, -187);
		level.grnd_dropZones["mp_lambeth"][3] 		= (-355, 409, -196);
		level.grnd_dropZones["mp_lambeth"][4] 		= (161, -5, -181);
		level.grnd_dropZones["mp_lambeth"][5] 		= (682, -407, -197);
		level.grnd_dropZones["mp_lambeth"][6] 		= (694, 263, -196);
		level.grnd_dropZones["mp_lambeth"][7] 		= (690, 1158, -243);
		level.grnd_dropZones["mp_lambeth"][8] 		= (1181, 801, -67);
		level.grnd_dropZones["mp_lambeth"][9] 		= (1281, 1248, -257);
		level.grnd_dropZones["mp_lambeth"][10] 		= (2057, 757, -249);
		level.grnd_dropZones["mp_lambeth"][11] 		= (1470, -1040, -109);
		level.grnd_dropZones["mp_lambeth"][12] 		= (1761, -258, -210);
		level.grnd_dropZones["mp_lambeth"][13] 		= (2800, -652, -186);
		level.grnd_dropZones["mp_lambeth"][14] 		= (2785, 445, -244);
		level.grnd_dropZones["mp_lambeth"][15] 		= (2751, 1090, -263);
		level.grnd_dropZones["mp_lambeth"][16] 		= (1535, 1980, -214);
		level.grnd_dropZones["mp_lambeth"][17] 		= (1262, 2602, -213);
		level.grnd_dropZones["mp_lambeth"][18] 		= (419, 2218, -183);
		level.grnd_dropZones["mp_lambeth"][19] 		= (170, 1631, -182);
		level.grnd_dropZones["mp_lambeth"][20] 		= (-606, 1549, -201);
		level.grnd_dropZones["mp_lambeth"][21] 		= (-1199, 1030, -196);
		
		level.grnd_dropZones["mp_radar"][0] 		= (-3482, -498, 1222);
		level.grnd_dropZones["mp_radar"][1] 		= (-4263, -124, 1229);
		level.grnd_dropZones["mp_radar"][2] 		= (-4006, 827, 1238);
		level.grnd_dropZones["mp_radar"][3] 		= (-3375, 342, 1222);
		level.grnd_dropZones["mp_radar"][4] 		= (-4623, 531, 1298);
		level.grnd_dropZones["mp_radar"][5] 		= (-5157, 877, 1200);
		level.grnd_dropZones["mp_radar"][6] 		= (-5950, 1071, 1305);
		level.grnd_dropZones["mp_radar"][7] 		= (-6509, 1660, 1299);
		level.grnd_dropZones["mp_radar"][8] 		= (-7013, 2955, 1359);
		level.grnd_dropZones["mp_radar"][9] 		= (-6333, 3473, 1421);
		level.grnd_dropZones["mp_radar"][10] 		= (-5675, 2923, 1388);
		level.grnd_dropZones["mp_radar"][11] 		= (-7119, 4357, 1380);
		level.grnd_dropZones["mp_radar"][12] 		= (-5487, 4077, 1356);
		level.grnd_dropZones["mp_radar"][13] 		= (-5736, 2960, 1407);
		level.grnd_dropZones["mp_radar"][14] 		= (-4908, 3281, 1225);
		level.grnd_dropZones["mp_radar"][15] 		= (-4421, 4071, 1268);
		level.grnd_dropZones["mp_radar"][16] 		= (-4979, 1816, 1205);
		level.grnd_dropZones["mp_radar"][17] 		= (-4874, 2306, 1223);		
		
		level.grnd_dropZones["mp_interchange"][0] 	= (2465, -402, 149);
		level.grnd_dropZones["mp_interchange"][1] 	= (2128, 199, 68);
		level.grnd_dropZones["mp_interchange"][2] 	= (1280, 1263, 126);
		level.grnd_dropZones["mp_interchange"][3] 	= (762, 1747, 114);
		level.grnd_dropZones["mp_interchange"][4] 	= (-9, 1836, 38);
		level.grnd_dropZones["mp_interchange"][5] 	= (-284, 1171, 159);
		level.grnd_dropZones["mp_interchange"][6] 	= (-1028, 944, 31);
		level.grnd_dropZones["mp_interchange"][7] 	= (-256, 264, 126);
		level.grnd_dropZones["mp_interchange"][8] 	= (462, -463, 158);
		level.grnd_dropZones["mp_interchange"][9] 	= (1029, -1045, 179);
		level.grnd_dropZones["mp_interchange"][10] 	= (1760, -1434, 142);
		level.grnd_dropZones["mp_interchange"][11] 	= (1538, -361, 142);
		level.grnd_dropZones["mp_interchange"][12] 	= (1150, -2977, 171);
		level.grnd_dropZones["mp_interchange"][13] 	= (371, -2883, 209);
		level.grnd_dropZones["mp_interchange"][14] 	= (399, -2149, 220);		
		
		level.grnd_dropZones["mp_underground"][0] 	= (-602, 3072, -68);
		level.grnd_dropZones["mp_underground"][1] 	= (-285, 2551, -215);
		level.grnd_dropZones["mp_underground"][2] 	= (574, 2656, -40);
		level.grnd_dropZones["mp_underground"][3] 	= (-627, 1579, -196);
		level.grnd_dropZones["mp_underground"][4] 	= (28, 1556, -196);
		level.grnd_dropZones["mp_underground"][5] 	= (727, 1615, -196);
		level.grnd_dropZones["mp_underground"][6] 	= (-1491, 1268, -196);
		level.grnd_dropZones["mp_underground"][7] 	= (-1370, 1757, -196);
		level.grnd_dropZones["mp_underground"][8] 	= (-1259, 599, -156);
		level.grnd_dropZones["mp_underground"][9] 	= (-959, -26, 60);
		level.grnd_dropZones["mp_underground"][10] 	= (-303, -562, 60);
		level.grnd_dropZones["mp_underground"][11] 	= (193, -922, 60);
		level.grnd_dropZones["mp_underground"][12] 	= (305, 817, -68);
		level.grnd_dropZones["mp_underground"][13] 	= (-276, 370, -68);
		
		level.grnd_dropZones["mp_bravo"][0] 		= (-1359, 608, 975);
		level.grnd_dropZones["mp_bravo"][1] 		= (-1686, 313, 991);
		level.grnd_dropZones["mp_bravo"][2] 		= (-1228, 41, 976);
		level.grnd_dropZones["mp_bravo"][3] 		= (-732, -715, 1032);
		level.grnd_dropZones["mp_bravo"][4] 		= (31, -771, 1038);
		level.grnd_dropZones["mp_bravo"][5] 		= (986, -833, 1116);
		level.grnd_dropZones["mp_bravo"][6] 		= (1800, -577, 1229);
		level.grnd_dropZones["mp_bravo"][7] 		= (1588, -55, 1181);
		level.grnd_dropZones["mp_bravo"][8] 		= (619, 916, 1175);
		level.grnd_dropZones["mp_bravo"][9] 		= (-129, 1310, 1228);
		level.grnd_dropZones["mp_bravo"][10] 		= (-726, 1272, 1268);
		level.grnd_dropZones["mp_bravo"][11] 		= (-741, 752, 1053);
		level.grnd_dropZones["mp_bravo"][12] 		= (6, -136, 1282);		
	}
}