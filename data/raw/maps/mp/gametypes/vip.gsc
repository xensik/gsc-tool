#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
/*
	VIP
	Objective: 	Escort the VIP to safety, or eliminate the VIP beofore he reaches extraction
	Map ends:	When one team eliminates the enemy team, or the flag is reached
	Respawning:	Beginning of next round

	Level requirementss
	------------------
		Spawnpoints:
			classname		mp_tdm_spawn
		

		Spectator Spawnpoints:
			classname		mp_global_intermission
*/

main()
{
	if(getdvar("mapname") == "mp_background")
		return;
	
	maps\mp\gametypes\_globallogic::init();
	maps\mp\gametypes\_callbacksetup::SetupCallbacks();
	maps\mp\gametypes\_globallogic::SetupCallbacks();

	registerRoundSwitchDvar( level.gameType, 0, 0, 9 );
	registerTimeLimitDvar( level.gameType, 10, 0, 1440 );
	registerScoreLimitDvar( level.gameType, 500, 0, 5000 );
	registerRoundLimitDvar( level.gameType, 1, 0, 10 );
	registerWinLimitDvar( level.gameType, 1, 0, 10 );
	registerRoundSwitchDvar( level.gameType, 3, 0, 30 );
	registerNumLivesDvar( level.gameType, 1, 0, 10 );
	registerWatchDvarInt( "halftime", 0 );

	level.teamBased = true;
	level.objectiveBased = true;
	
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onSpawnPlayer = ::onSpawnPlayer;
	level.onNormalDeath = ::onNormalDeath;
	level.onPlayerKilled = ::onPlayerKilled;
	level.onDeadEvent = ::onDeadEvent;

	game["dialog"]["gametype"] = "VIP";
}

onPrecacheGameType()
{
	precacheShader( "compass_waypoint_captureneutral" );
	precacheShader( "compass_waypoint_capture" );
	precacheShader( "compass_waypoint_defend" );
	
	precacheShader( "waypoint_captureneutral" );
	precacheShader( "waypoint_capture" );
	precacheShader( "waypoint_defend" );
	
	precacheString( &"MP_ELIMINATED_VIP" );	
	precacheString( &"MP_DEFENDED_VIP" );
	precacheString( &"SPLASHES_VIP" );
	
	game["flagmodels"] = [];
	game["flagmodels"]["neutral"] = "prop_flag_neutral";

	game["flagmodels"]["allies"] = maps\mp\gametypes\_teams::getTeamFlagModel( "allies" );
	game["flagmodels"]["axis"] = maps\mp\gametypes\_teams::getTeamFlagModel( "axis" );
	
	precacheModel( game["flagmodels"]["neutral"] );
	precacheModel( game["flagmodels"]["allies"] );
	precacheModel( game["flagmodels"]["axis"] );
	
}

onStartGameType()
{
	setClientNameMode("auto_change");

	if ( !isdefined( game["switchedsides"] ) )
		game["switchedsides"] = false;

	if ( game["switchedsides"] )
	{
		oldAttackers = game["attackers"];
		oldDefenders = game["defenders"];
		game["attackers"] = oldDefenders;
		game["defenders"] = oldAttackers;
	}

	setObjectiveText( "allies", &"OBJECTIVES_VIP" );
	setObjectiveText( "axis", &"OBJECTIVES_VIP" );
	
	if ( level.splitscreen )
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_VIP" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_VIP" );
	}
	else
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_VIP_SCORE" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_VIP_SCORE" );
	}
	setObjectiveHintText( "allies", &"OBJECTIVES_VIP_HINT" );
	setObjectiveHintText( "axis", &"OBJECTIVES_VIP_HINT" );
			
	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );	
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_tdm_spawn_allies_start" );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_tdm_spawn_axis_start" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_tdm_spawn" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_tdm_spawn" );
	
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );
	
	allowed[0] = "vip";
	allowed[1] = "sd";
	//maps\mp\gametypes\_rank::registerScoreInfo( "capture", 200 );
		
	maps\mp\gametypes\_gameobjects::main(allowed);	
	
	self thread waitToProcess();
}

waitToProcess()
{
	level endon( "game_end" );
	level endon( "waitSkipped" );

	self thread extractionZone();
	self thread skipWait();

	gameFlagWait( "prematch_done" );
	gameFlagWait( "graceperiod_done" );
	self notify( "graceComplete" );
	
	self thread vipSelection();
}

skipWait()
{
	self endon( "graceComplete" );
	
	for(;;)
	{
		if( level.players.size > 2 )
			break;
			
		wait( .5 );
	}
	
	self notify( "waitSkipped" );
	self thread vipSelection();
	
}

getSpawnPoint()
{
	spawnteam = self.pers["team"];
	if ( game["switchedsides"] )
		spawnteam = getOtherTeam( spawnteam );

	if ( level.inGracePeriod )
	{
		spawnPoints = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_tdm_spawn_" + spawnteam + "_start" );
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random( spawnPoints );
	}
	else
	{
		spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( spawnteam );
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( spawnPoints );
	}
	
	return spawnPoint;
}

onSpawnPlayer()
{
	self.isVip = false;
	self.usingObj = undefined;
	level notify ( "spawned_player" );
}

onNormalDeath( victim, attacker, lifeId )
{
	score = maps\mp\gametypes\_rank::getScoreInfoValue( "kill" );
	assert( isDefined( score ) );

	attacker maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( attacker.pers["team"], score );
	
	team = victim.team;
	
	if ( isDefined( victim.isVip ) && victim.isVip )
	{
		level thread vip_endGame( game["attackers"], &"MP_ELIMINATED_VIP" );
		attacker.finalKill = true;
	}	
}

onPlayerKilled(eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, killId)
{
	thread checkAllowSpectating();
}

onTimeLimit()
{
	if ( game["status"] == "overtime" )
	{
		winner = "forfeit";
	}
	else if ( game["teamScores"]["allies"] == game["teamScores"]["axis"] )
	{
		winner = "overtime";
	}
	else if ( game["teamScores"]["axis"] > game["teamScores"]["allies"] )
	{
		winner = "axis";
	}
	else
	{
		winner = "allies";
	}
	
	thread maps\mp\gametypes\_gamelogic::endGame( winner, game["strings"]["time_limit_reached"] );
}

checkAllowSpectating()
{
	wait ( 0.05 );
	
	update = false;
	if ( !level.aliveCount[ game["attackers"] ] )
	{
		level.spectateOverride[game["attackers"]].allowEnemySpectate = 1;
		update = true;
	}
	if ( !level.aliveCount[ game["defenders"] ] )
	{
		level.spectateOverride[game["defenders"]].allowEnemySpectate = 1;
		update = true;
	}
	if ( update )
		maps\mp\gametypes\_spectating::updateSpectateSettings();
}

onDeadEvent( team )
{
	if ( team == game["attackers"] )
	{
		level thread vip_endGame( game["defenders"], game["strings"][game["attackers"]+"_eliminated"] );
	}
	else if ( team == game["defenders"] )
	{
		level thread vip_endGame( game["attackers"], game["strings"][game["defenders"]+"_eliminated"] );
	}
}

vip_endGame( winningTeam, endReasonText )
{
	thread maps\mp\gametypes\_gamelogic::endGame( winningTeam, endReasonText );
}

vipSelection()
{
	println( "SELECTION" );
	potentialVIPs = [];
	abortTime = 0;
	
	for( ;; )
	{
		if ( level.players.size >= 2 )
			break;
			
		if ( abortTime >= 100 )
		{
			iPrintlnBold( "Game mode only playable with 2 or more players" );
			wait( 2 );
			maps\mp\gametypes\_callbacksetup::AbortLevel();
		}
		
		abortTime++;		
		wait( .1 );
	}	 
	
	foreach ( player in level.players )
	{			
		if ( player.team == game["defenders"] )	
			potentialVIPs[ potentialVIPs.size ] = player;
	}
	
	selectedVIPNum = RandomIntRange( 0, potentialVIPs.size );
	selectedPlayer = potentialVIPs[ selectedVIPNum ];
	
	if ( !isAlive(selectedPlayer ) && !isSubStr( selectedPlayer.guid, "bot" ) )
		selectedPlayer forceVIPSpawn();
			
	setupVip( selectedPlayer );
}

setupVip ( vipPlayer )
{
	vipPlayer TakeAllWeapons();
	vipPlayer _clearPerks();
	
	vipPlayer.isVip = true;
	
	vipPlayer giveWeapon( "deserteagle_fmj_mp" );
	vipPlayer giveStartAmmo( "deserteagle_fmj_mp" );
	
	vipPlayer giveWeapon( "riotshield_mp" );
	vipPlayer switchToWeapon( "riotshield_mp" );
	
	vipPlayer givePerk( "specialty_armorvest", false );
	vipPlayer givePerk( "specialty_finalstand", false );
	
	vipPlayer iPrintlnBold( "You Are the VIP" );
	//TO DO: add defend icon on the VIP
}

extractionZone()
{
	extractionZone = getEntArray("extraction_vip", "targetname");
	
	// check to see if zone is available.
	if ( !isDefined( extractionZone ) )
	{	
		println("WARNING: no extraction zone specified" );
	
		printLn( "^1Not enough extraction zones found in level!" );
		maps\mp\gametypes\_callbacksetup::AbortLevel();
		return;
	}
	else
		level.extractionZone = extractionZone;
		
	trigger = level.extractionZone[0];
	if ( isDefined( trigger.target ) )
	{
		visuals[0] = getEnt( trigger.target, "targetname" );
	}
	else
	{
		visuals[0] = spawn( "script_model", trigger.origin );
		visuals[0].angles = trigger.angles;
	}
	
	extractionZone = maps\mp\gametypes\_gameobjects::createUseObject( game["defenders"], trigger, visuals, (0,0,100) );
	extractionZone maps\mp\gametypes\_gameobjects::allowUse( "friendly" );
	extractionZone maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	extractionZone maps\mp\gametypes\_gameobjects::setUseText( &"MP_CALLING_EXTRACTION" );
	extractionZone maps\mp\gametypes\_gameobjects::setUseTime( 0 );
	
	extractionZone.onUse = ::onUse;
	extractionZone.onCantUse = ::onCantUse;
		
	traceStart = trigger.origin + (0,0,32);
	traceEnd = trigger.origin + (0,0,-32);
	trace = bulletTrace( traceStart, traceEnd, false, undefined );
	
	fx = maps\mp\gametypes\_teams::getTeamFlagFX( game["defenders"] );
	fxid = loadfx( fx );
	
	upangles = vectorToAngles( trace["normal"] );
	forward = anglesToForward( upangles );
	right = anglesToRight( upangles );
	thread spawnFxDelay( fxid, trace["position"], forward, right, 0.5 );
	
	extractionZone maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "compass_waypoint_defend");
	extractionZone maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_defend");
	extractionZone maps\mp\gametypes\_gameobjects::setVisibleTeam( "friendly" );
	
	level.extractionZone = extractionZone;
}

setVIPUse()
{
	foreach (player in level.players)
	{
		if ( ! player.isVip )
			self.trigger disablePlayerUse(player);
	}
}

onUse( player )
{
	if ( !isDefined( player.isVip ) || ! player.isVip )
	{
		return;		
	}
	
	iPrintlnBold( "Extraction on its way" );
	self handleTimer( player );
}

handleTimer( player )
{
	player endon( "death" );
	level endon( "game_end" );
	
	level.extractionTime = 45;
	maps\mp\gametypes\_gamelogic::pauseTimer();
	level.timeLimitOverride = true;
	setGameEndTime( int( getTime() + (level.extractionTime * 1000) ) );
	wait level.extractionTime;
	
	//call the sentry airdrops
	level thread vip_endGame( game["defenders"], &"MP_DEFENDED_VIP" );
}

onEndUse( team, player, success )
{
	println( "End Use" );
}

onCantUse( player )
{
//	player iPrintLnBold( &"MP_CANT_PLANT_WITHOUT_BOMB" );
}

spawnFxDelay( fxid, pos, forward, right, delay )
{
	wait delay;
	effect = spawnFx( fxid, pos, forward, right );
	triggerFx( effect );
}

forceVIPSpawn()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( "spawned" );

	if ( self.hasSpawned )
		return;
	
	if ( !isValidClass( self.pers["class"] ) )
	{
		self.pers["class"] = "CLASS_CUSTOM1";
		
		self.class = self.pers["class"];
	}
	
	self closeMenus();
	self thread maps\mp\gametypes\_playerlogic::spawnClient();
}
