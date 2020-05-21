#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
/*
	Arena
	Objective: 	Eliminate the enemy team
	Map ends:	When one team eliminates the enemy team, or the flag is reached
	Respawning:	Beginning of next round

	Level requirementss
	------------------
		Spawnpoints:
			classname		mp_tdm_spawn
			All players spawn from these. The spawnpoint chosen is dependent on the current locations of teammates and enemies
			at the time of spawn. Players generally spawn behind their teammates relative to the direction of enemies.

		Spectator Spawnpoints:
			classname		mp_global_intermission
			Spectators spawn from these and intermission is viewed from these positions.
			Atleast one is required, any more and they are randomly chosen between.
*/

/*QUAKED mp_tdm_spawn (0.0 0.0 1.0) (-16 -16 0) (16 16 72)
Players spawn away from enemies and near their team at one of these positions.*/

/*QUAKED mp_tdm_spawn_axis_start (0.5 0.0 1.0) (-16 -16 0) (16 16 72)
Axis players spawn away from enemies and near their team at one of these positions at the start of a round.*/

/*QUAKED mp_tdm_spawn_allies_start (0.0 0.5 1.0) (-16 -16 0) (16 16 72)
Allied players spawn away from enemies and near their team at one of these positions at the start of a round.*/

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
	registerNumLivesDvar( level.gameType, 0, 0, 10 );
	registerHalfTimeDvar( level.gameType, 0, 0, 1 );

	level.teamBased = true;
	level.objectiveBased = true;
	
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onSpawnPlayer = ::onSpawnPlayer;
	level.onNormalDeath = ::onNormalDeath;
	level.onPlayerKilled = ::onPlayerKilled;
	level.onDeadEvent = ::onDeadEvent;

	game["dialog"]["gametype"] = "arena";

	if ( getDvarInt( "g_hardcore" ) )
		game["dialog"]["gametype"] = "hc_" + game["dialog"]["gametype"];
	else if ( getDvarInt( "camera_thirdPerson" ) )
		game["dialog"]["gametype"] = "thirdp_" + game["dialog"]["gametype"];
	else if ( getDvarInt( "scr_diehard" ) )
		game["dialog"]["gametype"] = "dh_" + game["dialog"]["gametype"];
		
	game["strings"]["overtime_hint"] = &"MP_FIRST_BLOOD";
}

onPrecacheGameType()
{
	precacheShader( "compass_waypoint_captureneutral" );
	precacheShader( "compass_waypoint_capture" );
	precacheShader( "compass_waypoint_defend" );
	
	precacheShader( "waypoint_captureneutral" );
	precacheShader( "waypoint_capture" );
	precacheShader( "waypoint_defend" );

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

	setObjectiveText( "allies", &"OBJECTIVES_ARENA" );
	setObjectiveText( "axis", &"OBJECTIVES_ARENA" );
	
	if ( level.splitscreen )
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_ARENA" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_ARENA" );
	}
	else
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_ARENA_SCORE" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_ARENA_SCORE" );
	}
	setObjectiveHintText( "allies", &"OBJECTIVES_ARENA_HINT" );
	setObjectiveHintText( "axis", &"OBJECTIVES_ARENA_HINT" );
			
	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );	
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_tdm_spawn_allies_start" );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_tdm_spawn_axis_start" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_tdm_spawn" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_tdm_spawn" );
	
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );
	
	allowed[0] = "dom";
	allowed[1] = "airdrop_pallet";
	allowed[2] = "arena";
	maps\mp\gametypes\_rank::registerScoreInfo( "capture", 200 );
		
	maps\mp\gametypes\_gameobjects::main(allowed);	
	
	precacheFlag();
	thread arenaFlagWaiter();
	thread arenaTimeFlagWaiter();
}

precacheFlag()
{
	game["flagmodels"] = [];
	game["flagmodels"]["neutral"] = "prop_flag_neutral";

	game["flagmodels"]["allies"] = maps\mp\gametypes\_teams::getTeamFlagModel( "allies" );
	game["flagmodels"]["axis"] = maps\mp\gametypes\_teams::getTeamFlagModel( "axis" );
	
	precacheModel( game["flagmodels"]["neutral"] );
	precacheModel( game["flagmodels"]["allies"] );
	precacheModel( game["flagmodels"]["axis"] );
	
	precacheString( &"MP_CAPTURING_FLAG" );
	precacheString( &"MP_LOSING_FLAG" );
	precacheString( &"MP_DOM_YOUR_FLAG_WAS_CAPTURED" );
	precacheString( &"MP_DOM_ENEMY_FLAG_CAPTURED" );
	precacheString( &"MP_DOM_NEUTRAL_FLAG_CAPTURED" );
	precacheString( &"MP_ENEMY_FLAG_CAPTURED_BY" );
	precacheString( &"MP_NEUTRAL_FLAG_CAPTURED_BY" );
	precacheString( &"MP_FRIENDLY_FLAG_CAPTURED_BY" );
	
}

arenaTimeFlagWaiter()
{
	level endon( "down_to_one" );
	level endon( "game_end" );
	
	for( ;; )
	{
		timeLeft = maps\mp\gametypes\_gamelogic::getTimeRemaining();
		
		if ( timeLeft < 61000 )
			break;
	
		wait ( 1 );	
	}
	
	level notify( "arena_flag_time" );
	thread arenaFlag();
}

arenaFlagWaiter()
{
	level endon( "game_end" );
	level endon( "arena_flag_time" );
	
	for ( ;; )
	{
		if ( level.inGracePeriod == 0 )
			break;
			
		wait ( 0.05 );	
	}
	
	for ( ;; )
	{
		if ( getTeamPlayersAlive ( "axis" ) == 1 )
		{
			thread arenaFlag();
			level notify( "down_to_one" );
			break;
		}
		if ( getTeamPlayersAlive ( "allies" ) == 1 )
		{
			thread arenaFlag();
			level notify( "down_to_one" );
			break;
		}
		wait( 1 );
	}
	
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
	self.usingObj = undefined;
	level notify ( "spawned_player" );
}

onNormalDeath( victim, attacker, lifeId )
{
	score = maps\mp\gametypes\_rank::getScoreInfoValue( "kill" );
	assert( isDefined( score ) );

	attacker maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( attacker.pers["team"], score );
	
	team = victim.team;
	
	if ( game["state"] == "postgame" )
		attacker.finalKill = true;
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

arenaFlag()
{
	level.lastStatus["allies"] = 0;
	level.lastStatus["axis"] = 0;
		
	arenaFlag = getEntArray("flag_arena", "targetname");
	primaryFlags = getEntArray( "flag_primary", "targetname" );
	secondaryFlags = getEntArray( "flag_secondary", "targetname" );
	
	// check to see if arena flag is present otherwise throw a warning and use the dom Flag.
	if ( !isDefined( arenaFlag[0] ) )
	{	
		println("WARNING: no arena flags specified attempting to use Dom flag_b" );
	
		if ( (primaryFlags.size + secondaryFlags.size) < 1 )
		{
			printLn( "^1Not enough domination flags found in level!" );
			maps\mp\gametypes\_callbacksetup::AbortLevel();
			return;
		}
		
		self setupDomFlag(primaryFlags, secondaryFlags);
	}
	else
		level.arenaFlag = arenaFlag[0];
	
	trigger = level.arenaFlag;
	if ( isDefined( trigger.target ) )
	{
		visuals[0] = getEnt( trigger.target, "targetname" );
	}
	else
	{
		visuals[0] = spawn( "script_model", trigger.origin );
		visuals[0].angles = trigger.angles;
	}

	visuals[0] setModel( game["flagmodels"]["neutral"] );
	
	arenaFlag = maps\mp\gametypes\_gameobjects::createUseObject( "neutral", trigger, visuals, (0,0,100) );
	arenaFlag maps\mp\gametypes\_gameobjects::allowUse( "enemy" );
	arenaFlag maps\mp\gametypes\_gameobjects::setUseTime( 20.0 );
	arenaFlag maps\mp\gametypes\_gameobjects::setUseText( &"MP_CAPTURING_FLAG" );
	label = arenaFlag maps\mp\gametypes\_gameobjects::getLabel();
	arenaFlag.label = label;
	arenaFlag maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "compass_waypoint_defend");
	arenaFlag maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_defend");
	arenaFlag maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "compass_waypoint_captureneutral");
	arenaFlag maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_captureneutral");
	arenaFlag maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	arenaFlag.onUse = ::onUse;
	arenaFlag.onBeginUse = ::onBeginUse;
	arenaFlag.onUseUpdate = ::onUseUpdate;
	arenaFlag.onEndUse = ::onEndUse;
	arenaFlag.isArena = true;
	
	//play sound to show flag is now available for capture
	iPrintLnBold( "Arena flag spawned" );
	
	level.arenaFlag playSound( "flag_spawned" );	
	
	traceStart = visuals[0].origin + (0,0,32);
	traceEnd = visuals[0].origin + (0,0,-32);
	trace = bulletTrace( traceStart, traceEnd, false, undefined );

	upangles = vectorToAngles( trace["normal"] );
	arenaFlag.baseeffectforward = anglesToForward( upangles );
	arenaFlag.baseeffectright = anglesToRight( upangles );
	arenaFlag.baseeffectpos = trace["position"];
	
	arenaFlag.levelFlag = level.arenaFlag;
	
	level.arenaFlag = arenaFlag;
}

setupDomFlag( primaryFlags, secondaryFlags )
{
	for ( index = 0; index < primaryFlags.size; index++ )
	{
		label = primaryFlags[index].script_label;
		
		if ( label != "_b" )
		{
				primaryFlags[index] delete();	
		}
		else	
		{
				level.arenaFlag = primaryFlags[index];
				return;
		}
	}
}

onDeadEvent( team )
{
	if ( team == game["attackers"] )
	{
		level thread arena_endGame( game["defenders"], game["strings"][game["attackers"]+"_eliminated"] );
	}
	else if ( team == game["defenders"] )
	{
		level thread arena_endGame( game["attackers"], game["strings"][game["defenders"]+"_eliminated"] );
	}
}

arena_endGame( winningTeam, endReasonText )
{
	thread maps\mp\gametypes\_gamelogic::endGame( winningTeam, endReasonText );
}

giveFlagCaptureXP( touchList )
{
	level endon ( "game_ended" );
	wait .05;
	WaitTillSlowProcessAllowed();
	
	players = getArrayKeys( touchList );
	for ( index = 0; index < players.size; index++ )
	{
		player = touchList[players[index]].player;
		player thread [[level.onXPEvent]]( "capture" );
		maps\mp\gametypes\_gamescore::givePlayerScore( "capture", player );
		player thread maps\mp\_matchdata::logGameEvent( "capture", player.origin );
	}
}

onUse( player )
{
	team = player.pers["team"];
	oldTeam = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	label = self maps\mp\gametypes\_gameobjects::getLabel();

	//player logString( "flag captured: " + self.label );
	
	self.captureTime = getTime();
	
	self maps\mp\gametypes\_gameobjects::setOwnerTeam( team );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "compass_waypoint_capture" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_capture" );
	self.visuals[0] setModel( game["flagmodels"][team] );
	
	assert( team != "neutral" );
	
	if ( oldTeam == "neutral" )
	{
		otherTeam = getOtherTeam( team );
		thread printAndSoundOnEveryone( team, otherTeam, &"MP_NEUTRAL_FLAG_CAPTURED_BY", &"MP_NEUTRAL_FLAG_CAPTURED_BY", "mp_war_objective_taken", undefined, player );
		
		statusDialog( "captured_a", team );
		statusDialog( "enemy_has_a", otherTeam );
	}
	else
		thread printAndSoundOnEveryone( team, oldTeam, &"MP_ENEMY_FLAG_CAPTURED_BY", &"MP_FRIENDLY_FLAG_CAPTURED_BY", "mp_war_objective_taken", "mp_war_objective_lost", player );
		
	thread giveFlagCaptureXP( self.touchList[team] );
	player notify( "objective", "captured" );
	
	thread flagCaptured( team, &"MP_DOM_NEUTRAL_FLAG_CAPTURED" );
}

onBeginUse( player )
{
	ownerTeam = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	self.didStatusNotify = false;
	
	if ( ownerTeam == "neutral" )
	{
		otherTeam = getOtherTeam( player.pers["team"] );
		
		statusDialog( "securing", player.pers["team"] );
		self.objPoints[player.pers["team"]] thread maps\mp\gametypes\_objpoints::startFlashing();
		
		statusDialog( "enemy_taking", otherTeam );
		
		return;
	}
		
	if ( ownerTeam == "allies" )
		otherTeam = "axis";
	else
		otherTeam = "allies";

	self.objPoints["allies"] thread maps\mp\gametypes\_objpoints::startFlashing();
	self.objPoints["axis"] thread maps\mp\gametypes\_objpoints::startFlashing();
}

onUseUpdate( team, progress, change )
{
	if ( progress > 0.066 && change && !self.didStatusNotify )
	{
		otherTeam = getOtherTeam( team );
		
		statusDialog( "losing_a", otherTeam );
		statusDialog( "securing_a", team );

		self.didStatusNotify = true;
	}
}

onEndUse( team, player, success )
{
	self.objPoints["allies"] thread maps\mp\gametypes\_objpoints::stopFlashing();
	self.objPoints["axis"] thread maps\mp\gametypes\_objpoints::stopFlashing();
}

statusDialog( dialog, team )
{
	time = getTime();
	if ( getTime() < level.lastStatus[team] + 6000 )
		return;
		
	thread delayedLeaderDialog( dialog, team );
	level.lastStatus[team] = getTime();	
}

delayedLeaderDialog( sound, team )
{
	level endon ( "game_ended" );
	wait .1;
	WaitTillSlowProcessAllowed();
	
	leaderDialog( sound, team );
}

delayedLeaderDialogBothTeams( sound1, team1, sound2, team2 )
{
	level endon ( "game_ended" );
	wait .1;
	WaitTillSlowProcessAllowed();
	
	leaderDialogBothTeams( sound1, team1, sound2, team2 );
}

flagCaptured( winningTeam, endReasonText )
{
	maps\mp\gametypes\_gamelogic::endGame( winningTeam, endReasonText );
}
