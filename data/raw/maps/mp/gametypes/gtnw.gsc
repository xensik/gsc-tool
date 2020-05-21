#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
/*
	Di$oRdER was here :]
*/

/*QUAKED mp_ctf_spawn_axis (0.75 0.0 0.5) (-16 -16 0) (16 16 72)
Axis players spawn away from enemies and near their team at one of these positions.*/

/*QUAKED mp_ctf_spawn_allies (0.0 0.75 0.5) (-16 -16 0) (16 16 72)
Allied players spawn away from enemies and near their team at one of these positions.*/

/*QUAKED mp_ctf_spawn_axis_start (1.0 0.0 0.5) (-16 -16 0) (16 16 72)
Axis players spawn away from enemies and near their team at one of these positions at the start of a round.*/

/*QUAKED mp_ctf_spawn_allies_start (0.0 1.0 0.5) (-16 -16 0) (16 16 72)
Allied players spawn away from enemies and near their team at one of these positions at the start of a round.*/

main()
{
	maps\mp\gametypes\_globallogic::init();
	maps\mp\gametypes\_callbacksetup::SetupCallbacks();
	maps\mp\gametypes\_globallogic::SetupCallbacks();

	registerTimeLimitDvar( level.gameType, 3, 0, 1440 );
	registerScoreLimitDvar( level.gameType, 101, 0, 10000 );
	registerRoundLimitDvar( level.gameType, 1, 0, 30 );
	registerWinLimitDvar( level.gameType, 1, 0, 10 );
	registerRoundSwitchDvar( level.gameType, 0, 0, 30 );
	registerNumLivesDvar( level.gameType, 0, 0, 10 );
	registerHalfTimeDvar( level.gameType, 0, 0, 1 );
	
	level.teamBased = true;
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onDeadEvent = ::onDeadEvent;
	level.initGametypeAwards = ::initGametypeAwards;
	level.onTimeLimit = ::onTimeLimit;
	level.onNormalDeath = ::onNormalDeath;
	level.gtnw = true;
	
	game["dialog"]["gametype"] = "gtw";
	
	if ( getDvarInt( "g_hardcore" ) )
		game["dialog"]["gametype"] = "hc_" + game["dialog"]["gametype"];
	else if ( getDvarInt( "camera_thirdPerson" ) )
		game["dialog"]["gametype"] = "thirdp_" + game["dialog"]["gametype"];
	else if ( getDvarInt( "scr_diehard" ) )
		game["dialog"]["gametype"] = "dh_" + game["dialog"]["gametype"];
	else if (getDvarInt( "scr_" + level.gameType + "_promode" ) )
		game["dialog"]["gametype"] = game["dialog"]["gametype"] + "_pro";
	
	game["dialog"]["offense_obj"] = "obj_destroy";
	game["dialog"]["defense_obj"] = "obj_defend";
	level thread onPlayerConnect();
}

gtnw_endGame( winningTeam, endReasonText )
{
	thread maps\mp\gametypes\_gamelogic::endGame( winningTeam, endReasonText );
}


onPlayerConnect()
{
	for(;;)
	{
		level waittill( "connected", player );
		
		useBar = player createPrimaryProgressBar();
   		useBarText = player createPrimaryProgressBarText();
    	useBarText setText( &"MP_CAPTURING_NUKE" );
    	
    	useBar.useTime = 100;
    	player.useBar = useBar;
    	player.useBar hideElem();
    	player.useBarText = useBarText;
    	player.useBarText hideElem();
	}
}


onStartGameType()
{
	if ( !isdefined( game["switchedsides"] ) )
		game["switchedsides"] = false;

	if ( !isdefined( game["original_defenders"] ) )
		game["original_defenders"] = game["defenders"];

	if ( game["switchedsides"] )
	{
		oldAttackers = game["attackers"];
		oldDefenders = game["defenders"];
		game["attackers"] = oldDefenders;
		game["defenders"] = oldAttackers;
	}

	setClientNameMode("auto_change");
	
	
	if ( level.splitscreen )
	{
		setObjectiveScoreText( game["attackers"], &"OBJECTIVES_GTNW" );
		setObjectiveScoreText( game["defenders"], &"OBJECTIVES_GTNW" );
	}
	else
	{
		setObjectiveScoreText( game["attackers"], &"OBJECTIVES_GTNW_SCORE" );
		setObjectiveScoreText( game["defenders"], &"OBJECTIVES_GTNW_SCORE" );
	}
	
	setObjectiveText( game["attackers"], &"OBJECTIVES_GTNW" );
	setObjectiveText( game["defenders"], &"OBJECTIVES_GTNW" );
	
	setObjectiveHintText( game["attackers"], &"OBJECTIVES_GTNW_HINT" );
	setObjectiveHintText( game["defenders"], &"OBJECTIVES_GTNW_HINT" );
	
	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_ctf_spawn_allies_start" );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_ctf_spawn_axis_start" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_ctf_spawn_allies" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_ctf_spawn_axis" );
	
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "kill", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "headshot", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assist", 20 );
	maps\mp\gametypes\_rank::registerScoreInfo( "capture", 500 );

	allowed[0] = "airdrop_pallet";
	allowed[1] = "gtnw";
	allowed[2] = "gtnw_zone";
	maps\mp\gametypes\_gameobjects::main(allowed);
	
	thread setupNukeSite();
	
}

onPrecacheGameType()
{
	precacheShader("waypoint_defend");
	precacheShader("waypoint_target");
	precacheShader("waypoint_capture");
	precacheShader("compass_waypoint_target");
	precacheShader("compass_waypoint_defend");
	precacheShader("compass_waypoint_capture");
	
	precacheString( &"MP_CAPTURING_NUKE" );
	return;
}

setupNukeSite()
{
	level.lastStatus["allies"] = 0;
	level.lastStatus["axis"] = 0;
	
	nukeZone = getEnt( "gtnw_zone", "targetname" );
	assertEx( isDefined( nukeZone ), "GTNW Zone prefab doesn't exist in this map" );
	visuals = [];
	
	nukeSite  = maps\mp\gametypes\_gameobjects::createUseObject( "neutral", nukeZone, visuals, (0,0,100) );
	
	nukeSite maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "compass_waypoint_defend");
	nukeSite maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_defend" );

	nukeSite maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "compass_waypoint_captureneutral" );
	nukeSite maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_captureneutral" );
	
	nukeSite maps\mp\gametypes\_gameobjects::allowUse( "enemy" );
	nukeSite.noUseBar = true;
	nukeSite maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	
	nukeSite.onBeginUse = ::onBeginUse;
    nukeSite.onEndUse = ::onEndUse;
                                
	level.nukeSite = nukeSite;
	nukeSite thread scoreCounter();
}


getSpawnPoint()
{
	if ( self.team == "axis" )
	{
		spawnTeam = game["attackers"];
	}
	else
	{
		spawnTeam = game["defenders"];
	}

	if ( level.inGracePeriod )
	{
		spawnPoints = getentarray("mp_ctf_spawn_" + spawnteam + "_start", "classname");		
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random( spawnPoints );
	}
	else
	{
		spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( spawnteam );
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( spawnPoints );
	}
	
	return spawnPoint;
}


spawnFxDelay( fxid, pos, forward, right, delay )
{
	wait delay;
	effect = spawnFx( fxid, pos, forward, right );
	triggerFx( effect );
}


onDeadEvent( team )
{
	if ( ( isDefined( level.nukeIncoming ) && level.nukeIncoming ) || ( isDefined( level.nukeDetonated ) && level.nukeDetonated ) )
		return;
	
	if ( team == game["attackers"] )
	{
		maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( team, 1 );	
		level thread gtnw_endGame( game["defenders"], game["strings"][game["attackers"]+"_eliminated"] );
	}
	else if ( team == game["defenders"] )
	{
		maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( team, 1 );	
		level thread gtnw_endGame( game["attackers"], game["strings"][game["defenders"]+"_eliminated"] );
	}
}

initGametypeAwards()
{
	return;
}

onTimeLimit()
{
	if ( game["teamScores"]["allies"] == game["teamScores"]["axis"] )
	{
		level thread overtimeThread();
	}
	else if( game["teamScores"]["axis"] > game["teamScores"]["allies"] )
	{
		thread maps\mp\gametypes\_gamelogic::endGame( "axis", game["strings"]["time_limit_reached"] );
	}
	else if( game["teamScores"]["axis"] < game["teamScores"]["allies"] )
	{
		thread maps\mp\gametypes\_gamelogic::endGame( "allies", game["strings"]["time_limit_reached"] );
	}
}

overtimeThread( time )
{
	level endon( "game_ended" );

	level.inOvertime = true;
	level thread disableSpawning( 5 );
	
	level.endGameTime = 120;
	
	time = level.endGameTime;

	foreach ( player in level.players )
		player thread maps\mp\gametypes\_hud_message::SplashNotify( "gtnw_overtime" );
	
	maps\mp\gametypes\_gamelogic::pauseTimer();
	level.timeLimitOverride = true;
	setGameEndTime( int( getTime() + ( level.endGameTime * 1000 ) ) );
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithGameEndTimeUpdate( time );
	
	if ( game["teamScores"]["axis"] > game["teamScores"]["allies"] )
	{
		thread maps\mp\gametypes\_gamelogic::endGame( "axis", game["strings"]["time_limit_reached"] );
	}
	else if ( game["teamScores"]["axis"] < game["teamScores"]["allies"]  )
	{
		thread maps\mp\gametypes\_gamelogic::endGame( "allies", game["strings"]["time_limit_reached"] );
	}
	else
	{
		thread maps\mp\gametypes\_gamelogic::endGame( "tie", game["strings"]["time_limit_reached"] );
	}

}

disableSpawning( waitTime )
{
	level endon( "game_ended" );
	
	wait ( 5 );
	level.disableSpawning = true;
}


onBeginUse( player )
{
	player.useBar showElem();
	player.useBarText showElem();
	return;
}

onEndUse( team, player, success )
{
	player.useBar hideElem();
	player.useBarText hideElem();	
	return;
}

scoreCounter()
{
	level endon( "game_ended" );
	self endon( "stop_counting" );
	
	for ( ;; )
	{
		
		if ( !self.touchList["axis"].size && !self.touchlist["allies"].size )
		{
			setDvar( "ui_danger_team", "none" );
			
			self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "compass_waypoint_captureneutral" );
			self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_captureneutral" );
			
			self maps\mp\gametypes\_gameobjects::setOwnerTeam( "none" );
			self updateHudElems();
			wait 1;
			continue;	
		}
		
		self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "compass_waypoint_defend");
		self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_defend" );
		self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "compass_waypoint_capture" );
		self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_capture" );
		
		if ( self.touchList["axis"].size > self.touchList["allies"].size )
		{
			if ( maps\mp\gametypes\_gamescore::_getTeamScore( "axis" ) < 100 )
				maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( "axis", 1 );	
			
			self thread setUseBarScore( "axis" );
			setDvar( "ui_danger_team", "allies" );
			self maps\mp\gametypes\_gameobjects::setOwnerTeam( "axis" );
			
			if ( maps\mp\gametypes\_gamescore::_getTeamScore( "axis" ) >= 100 )
			{
				self maps\mp\gametypes\_gameobjects::allowUse( "none" );
				activateNuke( "axis" );
				self notify( "stop_counting" );
			}
		}
		else if ( self.touchList["axis"].size < self.touchList["allies"].size )
		{
			if ( maps\mp\gametypes\_gamescore::_getTeamScore( "allies" ) < 100 )
				maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( "allies", 1 );
			
			self thread setUseBarScore( "allies" );
			setDvar( "ui_danger_team", "axis" );
			self maps\mp\gametypes\_gameobjects::setOwnerTeam( "allies" );
			
			if ( maps\mp\gametypes\_gamescore::_getTeamScore( "allies" ) >= 100 )
			{
				self maps\mp\gametypes\_gameobjects::allowUse( "none" );
				activateNuke( "allies" );
				self notify( "stop_counting" );
			}
		}
		else
		{
			self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "compass_waypoint_captureneutral" );
			self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_captureneutral" );
			
			self maps\mp\gametypes\_gameobjects::setOwnerTeam( "none" );
			setDvar( "ui_danger_team", "contested" );
		}
		updateHudElems();
		
		wait( 1 );
	}
}


activateNuke( team )
{
	self giveFlagCaptureXP( self.touchList[team] );
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	self maps\mp\gametypes\_gameobjects::allowUse( "none" );
	
	
	bestTime = 99999999;
	nukeOwner = undefined;
	
	foreach( player in level.players )
	{
		if ( !isDefined( player ) )
			continue;
			
		player.useBar hideElem();
		player.useBarText hideElem();	
		
		if ( player.team != team )
			continue;
		
		if ( !isDefined( self.touchlist[team][player.guid] ) )
			continue;
		
		timeStarted = self.touchlist[team][player.guid].startTime;
		
		if ( timeStarted < bestTime )
		{
			nukeOwner = player;
			bestTime = timeStarted;
		}
	}
	assert( isDefined( nukeOwner ) );
	
	nukeOwner maps\mp\killstreaks\_nuke::tryUseNuke( 1 );	
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
		player thread maps\mp\gametypes\_hud_message::SplashNotify( "captured_nuke", maps\mp\gametypes\_rank::getScoreInfoValue( "capture" ) );
		player thread [[level.onXPEvent]]( "capture" );
		maps\mp\gametypes\_gamescore::givePlayerScore( "capture", player );
	}
}

setUseBarScore( team )
{
	teamScore = getTeamScore( team );

	foreach( player in level.players )
	{
		if ( !isDefined( player ) )
			continue;
		
		if ( player.team != team )
			continue;
		
		if ( !isDefined( self.touchlist[team][player.guid] ) )
			continue;
		
		//player thread maps\mp\gametypes\_rank::giveRankXP( "challenge",50 );
		
		player.useBar updateBar( teamScore/100, 0 );
	}
}

updateHudElems()
{
	foreach( player in level.players )
	{
		if ( !isDefined( player ) )
			continue;
		
		if ( !isDefined( self.touchlist["axis"][player.guid] ) && !isDefined( self.touchlist["allies"][player.guid] ) )
		{
			player.useBar hideElem();
			player.useBarText hideElem();	
		}	
		
		if ( isDefined( self.touchlist["axis"][player.guid] ) || isDefined( self.touchlist["allies"][player.guid] ) )
		{
			player.useBar showElem();
			player.useBarText showElem();
		}
	}
}


onNormalDeath( victim, attacker, lifeId )
{
	if ( !isDefined( level.inOvertime ) || !level.inOvertime )
		return;
		
	team = victim.team;
	
	if ( game["state"] == "postgame" )
		attacker.finalKill = true;
}