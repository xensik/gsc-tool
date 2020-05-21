#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;

main()
{
	if ( getdvar("mapname") == "mp_background" )
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
		registerTimeLimitDvar( level.gameType, 30 );
		registerScoreLimitDvar( level.gameType, 300 );
		registerRoundLimitDvar( level.gameType, 1 );
		registerWinLimitDvar( level.gameType, 1 );
		registerNumLivesDvar( level.gameType, 0 );
		registerHalfTimeDvar( level.gameType, 0 );
		
		level.matchRules_damageMultiplier = 0;
		level.matchRules_vampirism = 0;
	}
	
	level.teamBased = true;
	level.doPrematch = true;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onSpawnPlayer = ::onSpawnPlayer;
	level.onPlayerKilled = ::onPlayerKilled;
	level.initGametypeAwards = ::initGametypeAwards;
	
	if ( level.matchRules_damageMultiplier || level.matchRules_vampirism )
		level.modifyPlayerDamage = maps\mp\gametypes\_damage::gamemodeModifyPlayerDamage;

	precacheShader( "waypoint_captureneutral" );
	precacheShader( "waypoint_capture" );
	precacheShader( "waypoint_defend" );

	precacheShader( "waypoint_targetneutral" );
	precacheShader( "waypoint_captureneutral" );
	precacheShader( "waypoint_capture" );
	precacheShader( "waypoint_defend" );
	
	precacheString( &"MP_WAITING_FOR_HQ" );
	
	if ( getdvar("koth_autodestroytime") == "" )
		setdvar("koth_autodestroytime", "60");
	level.hqAutoDestroyTime = getdvarint("koth_autodestroytime");
	
	if ( getdvar("koth_spawntime") == "" )
		setdvar("koth_spawntime", "0");
	level.hqSpawnTime = getdvarint("koth_spawntime");
	
	if ( getdvar("koth_kothmode") == "" )
		setdvar("koth_kothmode", "1");
	level.kothMode = getdvarint("koth_kothmode");

	if ( getdvar("koth_captureTime") == "" )
		setdvar("koth_captureTime", "20");
	level.captureTime = getdvarint("koth_captureTime");

	if ( getdvar("koth_destroyTime") == "" )
		setdvar("koth_destroyTime", "10");
	level.destroyTime = getdvarint("koth_destroyTime");
	
	if ( getdvar("koth_delayPlayer") == "" )
		setdvar("koth_delayPlayer", 1);
	level.delayPlayer = getdvarint("koth_delayPlayer");

	if ( getdvar("koth_spawnDelay") == "" )
		setdvar("koth_spawnDelay", 0);
	level.spawnDelay = getdvarint("koth_spawnDelay");

	if ( getdvar("koth_extraDelay") == "" )
		setdvar("koth_extraDelay", 0.0 );

	level.extraDelay = getdvarint("koth_extraDelay");

	setDvarIfUninitialized( "koth_proMode", 0 );

	level.proMode = getDvarInt( "koth_proMode" );
		
	level.iconoffset = (0,0,32);
	
	level.onRespawnDelay = ::getRespawnDelay;

	game["dialog"]["gametype"] = "headquarters";

	if ( getDvarInt( "g_hardcore" ) )
	{
		if ( getMapCustom( "allieschar" ) == "us_army" )
			game["dialog"]["allies_gametype"] = "hc_hq";
		if ( getMapCustom( "axischar" ) == "us_army" )
			game["dialog"]["axis_gametype"] = "hc_hq";

		game["dialog"]["gametype"] = "hc_" + game["dialog"]["gametype"];
	}
	else if ( getDvarInt( "camera_thirdPerson" ) )
		game["dialog"]["gametype"] = "thirdp_" + game["dialog"]["gametype"];
	else if ( getDvarInt( "scr_diehard" ) )
		game["dialog"]["gametype"] = "dh_" + game["dialog"]["gametype"];
	else if (getDvarInt( "scr_" + level.gameType + "_promode" ) )
		game["dialog"]["gametype"] = game["dialog"]["gametype"] + "_pro";
}


initializeMatchRules()
{
	//	set common values
	setCommonRulesFromMatchRulesData();
	
	//	set everything else (private match options, default .cfg file values, and what normally is registered in the 'else' below)
	SetDynamicDvar( "koth_autodestroytime", GetMatchRulesData( "hqData", "HQLifetime" ) );
	SetDynamicDvar( "koth_spawntime", GetMatchRulesData( "hqData", "HQActivateDelay" ) );
	
	SetDynamicDvar( "scr_koth_roundswitch", 1 );
	registerRoundSwitchDvar( "koth", 1, 0, 9 );		
	SetDynamicDvar( "scr_koth_roundlimit", 1 );
	registerRoundLimitDvar( "koth", 1 );		
	SetDynamicDvar( "scr_koth_winlimit", 1 );
	registerWinLimitDvar( "koth", 1 );			
	SetDynamicDvar( "scr_koth_halftime", 0 );
	registerHalfTimeDvar( "koth", 0 );				
	
	SetDynamicDvar( "koth_kothmode", 0 );
	SetDynamicDvar( "koth_capturetime", 20 );
	SetDynamicDvar( "koth_destroytime", 10 );
	SetDynamicDvar( "koth_delayPlayer", 0 );
	SetDynamicDvar( "koth_spawnDelay", 60 );
	SetDynamicDvar( "koth_extraDelay", 0 );
	SetDynamicDvar( "koth_proMode", 0 );
	SetDynamicDvar( "scr_koth_promode", 0 );	
}


updateObjectiveHintMessages( alliesObjective, axisObjective )
{
	game["strings"]["objective_hint_allies"] = alliesObjective;
	game["strings"]["objective_hint_axis"  ] = axisObjective;
	
	for ( i = 0; i < level.players.size; i++ )
	{
		player = level.players[i];
		if ( isDefined( player.pers["team"] ) && player.pers["team"] != "spectator" )
		{
			hintText = getObjectiveHintText( player.pers["team"] );
			player thread maps\mp\gametypes\_hud_message::hintMessage( hintText );
		}
	}
}


getRespawnDelay()
{
	self clearLowerMessage( "hq_respawn" );

	if ( !isDefined( level.radioObject ) )
		return undefined;
	
	hqOwningTeam = level.radioObject maps\mp\gametypes\_gameobjects::getOwnerTeam();
	if ( self.pers["team"] == hqOwningTeam )
	{
		if ( !isDefined( level.hqDestroyTime ) )
			return undefined;
		
		if (!level.spawnDelay )
			return undefined;

		timeRemaining = (level.hqDestroyTime - gettime()) / 1000;
		timeRemaining += level.extraDelay + 1.0; // extra second for slowed spawning

		if ( level.spawnDelay >= level.hqAutoDestroyTime )
			setLowerMessage( "hq_respawn", &"MP_WAITING_FOR_HQ", undefined, 10 );
		
		if ( !isAlive( self ) )
			self.forceSpawnNearTeammates = true;
		
		if ( level.delayPlayer )
		{
			return min( level.spawnDelay, timeRemaining );
		}
		else
		{
			return (int(timeRemaining) % level.spawnDelay);
		}
	}
}


onStartGameType()
{
	setObjectiveText( "allies", &"OBJECTIVES_KOTH" );
	setObjectiveText( "axis", &"OBJECTIVES_KOTH" );
	
	if ( level.splitscreen )
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_KOTH" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_KOTH" );
	}
	else
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_KOTH_SCORE" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_KOTH_SCORE" );
	}
	
	level.objectiveHintPrepareHQ = &"MP_CONTROL_HQ";
	level.objectiveHintCaptureHQ = &"MP_CAPTURE_HQ";
	level.objectiveHintDestroyHQ = &"MP_DESTROY_HQ";
	level.objectiveHintDefendHQ = &"MP_DEFEND_HQ";
	precacheString( level.objectiveHintPrepareHQ );
	precacheString( level.objectiveHintCaptureHQ );
	precacheString( level.objectiveHintDestroyHQ );
	precacheString( level.objectiveHintDefendHQ );
	
	if ( level.kothmode )
		level.objectiveHintDestroyHQ = level.objectiveHintCaptureHQ;
	
	if ( level.hqSpawnTime )
		updateObjectiveHintMessages( level.objectiveHintPrepareHQ, level.objectiveHintPrepareHQ );
	else
		updateObjectiveHintMessages( level.objectiveHintCaptureHQ, level.objectiveHintCaptureHQ );
	
	setClientNameMode("auto_change");
	
	// TODO: HQ spawnpoints
	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_tdm_spawn" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_tdm_spawn" );
	
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );
	
	level.spawn_all = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_tdm_spawn" );
	if ( !level.spawn_all.size )
	{
		println("^1No mp_tdm_spawn spawnpoints in level!");
		maps\mp\gametypes\_callbacksetup::AbortLevel();
		return;
	}
	
	
	allowed[0] = "hq";
	maps\mp\gametypes\_gameobjects::main(allowed);
	
	thread SetupRadios();

	maps\mp\gametypes\_rank::registerScoreInfo( "kill", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "headshot", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assist", 10 );
	maps\mp\gametypes\_rank::registerScoreInfo( "defend", 10 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assault", 10 );
	maps\mp\gametypes\_rank::registerScoreInfo( "capture", 250 );
	
	thread HQMainLoop();
}


HQMainLoop()
{
	level endon("game_ended");
	
	level.hqRevealTime = -100000;
	
	hqSpawningInStr = &"MP_HQ_AVAILABLE_IN";
	if ( level.kothmode )
	{
		hqDestroyedInFriendlyStr = &"MP_HQ_DESPAWN_IN";
		hqDestroyedInEnemyStr = &"MP_HQ_DESPAWN_IN";
	}
	else
	{

		if ( !level.splitscreen )
		{
			hqDestroyedInFriendlyStr = &"MP_HQ_REINFORCEMENTS_IN";
			hqDestroyedInEnemyStr = &"MP_HQ_DESPAWN_IN";
		}
		else
		{	
			hqDestroyedInFriendlyStr = &"MP_HQ_REINFORCEMENTS_IN_SPLITSCREEN";
			hqDestroyedInEnemyStr = &"MP_HQ_DESPAWN_IN";
		}
	}
	
	precacheString( hqSpawningInStr );
	precacheString( hqDestroyedInFriendlyStr );
	precacheString( hqDestroyedInEnemyStr );
	precacheString( &"MP_CAPTURING_HQ" );
	precacheString( &"MP_DESTROYING_HQ" );
	
	gameFlagWait( "prematch_done" );
	
	wait 5;
	
	timerDisplay = [];
	timerDisplay["allies"] = createServerTimer( "objective", 1.4, "allies" );
	timerDisplay["allies"] setPoint( "TOP LEFT", "TOP LEFT", 125, 2 );
	timerDisplay["allies"].label = hqSpawningInStr;
	timerDisplay["allies"].alpha = 0;
	timerDisplay["allies"].archived = false;
	timerDisplay["allies"].hideWhenInMenu = true;
	
	timerDisplay["axis"  ] = createServerTimer( "objective", 1.4, "axis" );
	timerDisplay["axis"  ] setPoint( "TOP LEFT", "TOP LEFT", 125, 2 );
	timerDisplay["axis"  ].label = hqSpawningInStr;
	timerDisplay["axis"  ].alpha = 0;
	timerDisplay["axis"  ].archived = false;
	timerDisplay["axis"  ].hideWhenInMenu = true;
	
	level.timerDisplay = timerDisplay;
	
	thread hideTimerDisplayOnGameEnd( timerDisplay["allies"] );
	thread hideTimerDisplayOnGameEnd( timerDisplay["axis"  ] );
	
	locationObjID = maps\mp\gametypes\_gameobjects::getNextObjID();
	
	objective_add( locationObjID, "invisible", (0,0,0) );
	
	while( 1 )
	{
		radio = PickRadioToSpawn();
		radio makeRadioActive();
		
		//iPrintLn( &"MP_HQ_REVEALED" );
		playSoundOnPlayers( "mp_suitcase_pickup" );
		leaderDialog( "hq_located" );
		
		radioObject = radio.gameobject;
		level.radioObject = radioObject;
		
		radioObject maps\mp\gametypes\_gameobjects::setModelVisibility( true );
		
		level.hqRevealTime = gettime();
		
		if ( level.hqSpawnTime )
		{
			nextObjPoint = maps\mp\gametypes\_objpoints::createTeamObjpoint( "objpoint_next_hq", radio.origin + level.iconoffset, "all", "waypoint_targetneutral" );
			nextObjPoint setWayPoint( true, true );
			objective_position( locationObjID, radio.trigorigin );
			objective_icon( locationObjID, "waypoint_targetneutral" );
			objective_state( locationObjID, "active" );

			updateObjectiveHintMessages( level.objectiveHintPrepareHQ, level.objectiveHintPrepareHQ );
			
			timerDisplay["allies"].label = hqSpawningInStr;
			timerDisplay["allies"] setTimer( level.hqSpawnTime );
			//if ( !level.splitscreen )
			timerDisplay["allies"].alpha = 1;
			
			timerDisplay["axis"  ].label = hqSpawningInStr;
			timerDisplay["axis"  ] setTimer( level.hqSpawnTime );
			//if ( !level.splitscreen )
			timerDisplay["axis"  ].alpha = 1;

			wait level.hqSpawnTime;

			maps\mp\gametypes\_objpoints::deleteObjPoint( nextObjPoint );
			objective_state( locationObjID, "invisible" );
			leaderDialog( "hq_online" );
		}

		timerDisplay["allies"].alpha = 0;
		timerDisplay["axis"  ].alpha = 0;
		
		waittillframeend;
		
		leaderDialog( "obj_capture" );
		updateObjectiveHintMessages( level.objectiveHintCaptureHQ, level.objectiveHintCaptureHQ );
		playSoundOnPlayers( "mp_killstreak_radar" );

		radioObject maps\mp\gametypes\_gameobjects::allowUse( "any" );
		radioObject maps\mp\gametypes\_gameobjects::setUseTime( level.captureTime );
		radioObject maps\mp\gametypes\_gameobjects::setUseText( &"MP_CAPTURING_HQ" );
		
		radioObject maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_captureneutral" );
		radioObject maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_captureneutral" );
		radioObject maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
		
		radioObject.onUse = ::onRadioCapture;
		radioObject.onBeginUse = ::onBeginUse;
		radioObject.onEndUse = ::onEndUse;
		
		level waittill( "hq_captured" );
		
		ownerTeam = radioObject maps\mp\gametypes\_gameobjects::getOwnerTeam();
		otherTeam = getOtherTeam( ownerTeam );
		
		if ( level.hqAutoDestroyTime )
		{
			thread DestroyHQAfterTime( level.hqAutoDestroyTime );
			timerDisplay[ownerTeam] setTimer( level.hqAutoDestroyTime + level.extraDelay );
			timerDisplay[otherTeam] setTimer( level.hqAutoDestroyTime );
		}
		else
		{
			level.hqDestroyedByTimer = false;
		}
		
		/#
		thread scriptDestroyHQ();
		#/
		
		while( 1 )
		{
			ownerTeam = radioObject maps\mp\gametypes\_gameobjects::getOwnerTeam();
			otherTeam = getOtherTeam( ownerTeam );
	
			if ( ownerTeam == "allies" )
			{
				updateObjectiveHintMessages( level.objectiveHintDefendHQ, level.objectiveHintDestroyHQ );
			}
			else
			{
				updateObjectiveHintMessages( level.objectiveHintDestroyHQ, level.objectiveHintDefendHQ );
			}
	
			radioObject maps\mp\gametypes\_gameobjects::allowUse( "enemy" );
			radioObject maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_defend" );
			radioObject maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_defend" );
			radioObject maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_capture" );
			radioObject maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_capture" );

			if ( !level.kothMode )
				radioObject maps\mp\gametypes\_gameobjects::setUseText( &"MP_DESTROYING_HQ" );
			
			radioObject.onUse = ::onRadioDestroy;
			
			if ( level.hqAutoDestroyTime )
			{
				timerDisplay[ownerTeam].label = hqDestroyedInFriendlyStr;
				//if ( !level.splitscreen )
					timerDisplay[ownerTeam].alpha = 1;
					
				timerDisplay[otherTeam].label = hqDestroyedInEnemyStr;
				//if ( !level.splitscreen )
					timerDisplay[otherTeam].alpha = 1;
			}
			
			level waittill( "hq_destroyed" );
			
			timerDisplay[otherTeam].alpha = 0;
			
			if ( !level.kothmode || level.hqDestroyedByTimer )
				break;
			
			thread forceSpawnTeam( ownerTeam );
			
			radioObject maps\mp\gametypes\_gameobjects::setOwnerTeam( getOtherTeam( ownerTeam ) );
		}
		
		level notify("hq_reset");
		
		radioObject maps\mp\gametypes\_gameobjects::allowUse( "none" );
		radioObject maps\mp\gametypes\_gameobjects::setOwnerTeam( "neutral" );
		radioObject maps\mp\gametypes\_gameobjects::setModelVisibility( false );
		
		radio makeRadioInactive();
		
		level.radioObject = undefined;
		
		thread forceSpawnTeam( ownerTeam, level.extraDelay );

		wait ( level.extraDelay );
		
		wait ( max ( 1.0, 6.0 - level.extraDelay ) );
	}
}


hideTimerDisplayOnGameEnd( timerDisplay )
{
	level waittill("game_ended");
	timerDisplay.alpha = 0;
}

forceSpawnTeam( team, extraDelay )
{
	if ( extraDelay )
	{
		foreach ( player in level.players )
		{
			if ( isAlive( player ) )
				continue;
				
			if ( player.pers["team"] == team )
				player setLowerMessage( "hq_respawn", game["strings"]["waiting_to_spawn"] );
		}

		wait ( extraDelay );
	}
	
	level.timerDisplay[team].alpha = 0;
	
	foreach ( player in level.players )
	{
		if ( player.pers["team"] == team )
		{
			player clearLowerMessage( "hq_respawn" );
			if ( !isAlive( player ) )
				player.forceSpawnNearTeammates = true;
			player notify( "force_spawn" );
		}
	}
}


onBeginUse( player )
{
	ownerTeam = self maps\mp\gametypes\_gameobjects::getOwnerTeam();

	if ( ownerTeam == "neutral" )
	{
		self.objPoints[player.pers["team"]] thread maps\mp\gametypes\_objpoints::startFlashing();
	}
	else
	{
		self.objPoints["allies"] thread maps\mp\gametypes\_objpoints::startFlashing();
		self.objPoints["axis"] thread maps\mp\gametypes\_objpoints::startFlashing();
	}
}


onEndUse( team, player, success )
{
	self.objPoints["allies"] thread maps\mp\gametypes\_objpoints::stopFlashing();
	self.objPoints["axis"] thread maps\mp\gametypes\_objpoints::stopFlashing();
}


onRadioCapture( player )
{
	team = player.pers["team"];

	player thread [[level.onXPEvent]]( "capture" );
	maps\mp\gametypes\_gamescore::givePlayerScore( "capture", player );
	
	foreach ( item in self.touchList[team] )
	{
		touchPlayer = item.player;
		
		touchPlayer incPlayerStat( "hqscaptured", 1 );
		touchPlayer incPersStat( "captures", 1 );
		touchPlayer maps\mp\gametypes\_persistence::statSetChild( "round", "captures", player.pers["captures"] );
	}
	
	player thread maps\mp\_matchdata::logGameEvent( "capture", player.origin );

	oldTeam = maps\mp\gametypes\_gameobjects::getOwnerTeam();
	self maps\mp\gametypes\_gameobjects::setOwnerTeam( team );
	if ( !level.kothMode )
		self maps\mp\gametypes\_gameobjects::setUseTime( level.destroyTime );
	
	otherTeam = "axis";
	if ( team == "axis" )
		otherTeam = "allies";
	
	teamPlayerCardSplash( "callout_capturedhq", player );

	leaderDialog( "hq_secured", team );
	leaderDialog( "hq_enemy_captured", otherTeam );
	thread playSoundOnPlayers( "mp_war_objective_taken", team );
	thread playSoundOnPlayers( "mp_war_objective_lost", otherTeam );
	
	level thread awardHQPoints( team );
	
	player notify( "objective", "captured" );
	level notify( "hq_captured" );
}

/#
scriptDestroyHQ()
{
	level endon("hq_destroyed");
	while(1)
	{
		if ( getdvar("scr_destroyhq") != "1" )
		{
			wait .1;
			continue;
		}
		setdvar("scr_destroyhq","0");
		
		hqOwningTeam = level.radioObject maps\mp\gametypes\_gameobjects::getOwnerTeam();
		for ( i = 0; i < level.players.size; i++ )
		{
			if ( level.players[i].team != hqOwningTeam )
			{
				onRadioDestroy( level.players[i] );
				break;
			}
		}
	}
}
#/

onRadioDestroy( player )
{
	team = player.pers["team"];
	otherTeam = "axis";
	if ( team == "axis" )
		otherTeam = "allies";

	//player logString( "radio destroyed" );
	player thread [[level.onXPEvent]]( "capture" );
	maps\mp\gametypes\_gamescore::givePlayerScore( "capture", player );	
	
	foreach ( item in self.touchList[team] )
	{
		touchPlayer = item.player;
		
		touchPlayer incPlayerStat( "hqsdestroyed", 1 );
		touchPlayer incPersStat( "destructions", 1 );
		touchPlayer maps\mp\gametypes\_persistence::statSetChild( "round", "destructions", player.pers["destructions"] );
	}
	
	player thread maps\mp\_matchdata::logGameEvent( "destroy", player.origin );
		
	if ( level.kothmode )
	{
		teamPlayerCardSplash( "callout_capturedhq", player );
		leaderDialog( "hq_secured", team );
		leaderDialog( "hq_enemy_captured", otherTeam );
	}
	else
	{
		teamPlayerCardSplash( "callout_destroyedhq", player );
		leaderDialog( "hq_secured", team );
		leaderDialog( "hq_enemy_destroyed", otherTeam );
	}
	thread playSoundOnPlayers( "mp_war_objective_taken", team );
	thread playSoundOnPlayers( "mp_war_objective_lost", otherTeam );
	
	level notify( "hq_destroyed" );
	
	if ( level.kothmode )
		level thread awardHQPoints( team );
}


DestroyHQAfterTime( time )
{
	level endon( "game_ended" );
	level endon( "hq_reset" );
	
	level.hqDestroyTime = gettime() + time * 1000;
	level.hqDestroyedByTimer = false;
	
	wait time;
	
	level.hqDestroyedByTimer = true;

	leaderDialog( "hq_offline" );
	
	level notify( "hq_destroyed" );
}


awardHQPoints( team )
{
	level endon( "game_ended" );
	level endon( "hq_destroyed" );
	
	level notify("awardHQPointsRunning");
	level endon("awardHQPointsRunning");

	steps = 12;
	baseLine = 5;
	delta = 5;
	points = 10;

	if ( level.proMode )
		seconds = int(level.hqAutoDestroyTime / steps);
	else
		seconds = 5;
	
	curStep = 0;
	while ( !level.gameEnded )
	{
		if ( level.proMode && level.hqAutoDestroyTime )
			maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( team, int( points * ( curStep + 1 ) ) );
		else
			maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( team, points );

		for ( index = 0; index < level.players.size; index++ )
		{
			player = level.players[index];
			
			if ( player.pers["team"] == team )
			{
				if ( level.proMode )
				{
					if ( level.hqAutoDestroyTime )
						player thread maps\mp\gametypes\_rank::giveRankXP( "defend", int(baseLine+(delta*curStep)) );
					else
						player thread maps\mp\gametypes\_rank::giveRankXP( "defend", int(baseLine+delta) );
				}
				else
				{
					player thread maps\mp\gametypes\_rank::giveRankXP( "defend" );
				}
				
				if ( isAlive( player ) )
					maps\mp\gametypes\_gamescore::givePlayerScore( "defend", player );	
			}
		}
		
		curStep++;
		wait seconds;
		maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();
	}
}


getSpawnPoint()
{
	spawnpoint = undefined;
	
	if ( isdefined( level.radioObject ) )
	{
		hqOwningTeam = level.radioObject maps\mp\gametypes\_gameobjects::getOwnerTeam();
		if ( self.pers["team"] == hqOwningTeam )
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( level.spawn_all, level.radioObject.nearSpawns );
		//else if ( level.spawnDelay >= level.hqAutoDestroyTime && gettime() > level.hqRevealTime + 10000 )
		//	spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( level.spawn_all, level.radioObject.outerSpawns );
		else
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( level.spawn_all, level.radioObject.outerSpawns );
	}
	
	if ( !isDefined( spawnpoint ) )
		spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( level.spawn_all );
	
	assert( isDefined(spawnpoint) );
	
	return spawnpoint;
}


onSpawnPlayer()
{
	self clearLowerMessage( "hq_respawn" );
	self.forceSpawnNearTeammates = undefined;
}


SetupRadios()
{
	maperrors = [];

	radios = getentarray( "hq_hardpoint", "targetname" );
	
	if ( radios.size < 2 )
	{
		maperrors[maperrors.size] = "There are not at least 2 entities with targetname \"radio\"";
	}
	
	trigs = getentarray("radiotrigger", "targetname");
	for ( i = 0; i < radios.size; i++ )
	{
		errored = false;
		
		radio = radios[i];
		radio.trig = undefined;
		for ( j = 0; j < trigs.size; j++ )
		{
			if ( radio istouching( trigs[j] ) )
			{
				if ( isdefined( radio.trig ) )
				{
					maperrors[maperrors.size] = "Radio at " + radio.origin + " is touching more than one \"radiotrigger\" trigger";
					errored = true;
					break;
				}
				radio.trig = trigs[j];
				break;
			}
		}
		
		if ( !isdefined( radio.trig ) )
		{
			if ( !errored )
			{
				maperrors[maperrors.size] = "Radio at " + radio.origin + " is not inside any \"radiotrigger\" trigger";
				continue;
			}
			
			// possible fallback (has been tested)
			//radio.trig = spawn( "trigger_radius", radio.origin, 0, 128, 128 );
			//errored = false;
		}
		
		assert( !errored );
		
		radio.trigorigin = radio.trig.origin;
		
		visuals = [];
		visuals[0] = radio;
		
		otherVisuals = getEntArray( radio.target, "targetname" );
		for ( j = 0; j < otherVisuals.size; j++ )
		{
			visuals[visuals.size] = otherVisuals[j];
		}

		radio.visuals = visuals;
		radio maps\mp\gametypes\_gameobjects::setModelVisibility( false );
		/*
		radio.gameObject = maps\mp\gametypes\_gameobjects::createUseObject( "neutral", radio.trig, visuals, (radio.origin - radio.trigorigin) + level.iconoffset );
		radio.gameObject maps\mp\gametypes\_gameobjects::disableObject();
		radio.gameObject maps\mp\gametypes\_gameobjects::setModelVisibility( false );
		radio.trig.useObj = radio.gameObject;
		
		radio setUpNearbySpawns();
		*/
	}
	
	if (maperrors.size > 0)
	{
		println("^1------------ Map Errors ------------");
		for(i = 0; i < maperrors.size; i++)
			println(maperrors[i]);
		println("^1------------------------------------");
		
		error("Map errors. See above");
		maps\mp\gametypes\_callbacksetup::AbortLevel();
		
		return;
	}
	
	level.radios = radios;
	
	level.prevradio = undefined;
	level.prevradio2 = undefined;
	
	/#
	thread kothDebug();
	#/
	
	return true;
}


makeRadioActive()
{
	self.gameObject = maps\mp\gametypes\_gameobjects::createUseObject( "neutral", self.trig, self.visuals, (self.origin - self.trigorigin) + level.iconoffset );
	self.gameObject maps\mp\gametypes\_gameobjects::setModelVisibility( false );
	self.trig.useObj = self.gameObject;
	
	self setUpNearbySpawns();
}


makeRadioInactive()
{
	self.gameObject maps\mp\gametypes\_gameobjects::deleteUseObject();
	
	self.gameObject = undefined;
}


setUpNearbySpawns()
{
	spawns = level.spawn_all;
	
	for ( i = 0; i < spawns.size; i++ )
	{
		spawns[i].distsq = distanceSquared( spawns[i].origin, self.origin );
	}
	
	// sort by distsq
	for ( i = 1; i < spawns.size; i++ )
	{
		thespawn = spawns[i];
		for ( j = i - 1; j >= 0 && thespawn.distsq < spawns[j].distsq; j-- )
			spawns[j + 1] = spawns[j];
		spawns[j + 1] = thespawn;
	}
	
	first = [];
	outer = [];
	
	thirdSize = spawns.size / 3;
	for ( i = 0; i < spawns.size; i++ )
	{
		if ( i <= thirdSize || spawns[i].distsq <= 700*700 )
			first[ first.size ] = spawns[i];
		
		if ( i > thirdSize || spawns[i].distsq > 1000*1000 )
		{
			if ( outer.size < 10 || spawns[i].distsq < 1500*1500 ) // don't include too many far-away spawnpoints
				outer[ outer.size ] = spawns[i];
		}
	}
	
	self.gameObject.nearSpawns = first;
	self.gameObject.outerSpawns = outer;
}


PickRadioToSpawn()
{
	validAllies = [];
	validAxis = [];
	
	foreach ( player in level.players )
	{
		if ( player.team == "spectator" )
			continue;
			
		if ( !isAlive( player ) )
			continue;
			
		player.dist = 0;
		if ( player.team == "allies" )
			validAllies[validAllies.size] = player;
		else
			validAxis[validAxis.size] = player;
	}

	if ( !validAllies.size || !validAxis.size )
	{
		radio = level.radios[ randomint( level.radios.size) ];
		while ( isDefined( level.prevradio ) && radio == level.prevradio ) // so lazy
			radio = level.radios[ randomint( level.radios.size) ];
		
		level.prevradio2 = level.prevradio;
		level.prevradio = radio;
		
		return radio;
	}
	
	for ( i = 0; i < validAllies.size; i++ )
	{
		for ( j = i + 1; j < validAllies.size; j++ )
		{
			dist = distanceSquared( validAllies[i].origin, validAllies[j].origin );
			
			validAllies[i].dist += dist;
			validAllies[j].dist += dist;
		}
	}

	for ( i = 0; i < validAxis.size; i++ )
	{
		for ( j = i + 1; j < validAxis.size; j++ )
		{
			dist = distanceSquared( validAxis[i].origin, validAxis[j].origin );
			
			validAxis[i].dist += dist;
			validAxis[j].dist += dist;
		}
	}

	bestPlayer = validAllies[0];
	foreach ( player in validAllies )
	{
		if ( player.dist < bestPlayer.dist )
			bestPlayer = player;
	}
	avgpos["allies"] = bestPlayer.origin;

	bestPlayer = validAxis[0];
	foreach ( player in validAxis )
	{
		if ( player.dist < bestPlayer.dist )
			bestPlayer = player;
	}
	avgpos["axis"] = validAxis[0].origin;
	
	bestradio = undefined;
	lowestcost = undefined;
	for ( i = 0; i < level.radios.size; i++ )
	{
		radio = level.radios[i];
		
		// (purposefully using distance instead of distanceSquared)
		cost = abs( distance( radio.origin, avgpos["allies"] ) - distance( radio.origin, avgpos["axis"] ) );
		
		if ( isdefined( level.prevradio ) && radio == level.prevradio )
		{
			continue;
		}
		if ( isdefined( level.prevradio2 ) && radio == level.prevradio2 )
		{
			if ( level.radios.size > 2 )
				continue;
			else
				cost += 512;
		}
		
		if ( !isdefined( lowestcost ) || cost < lowestcost )
		{
			lowestcost = cost;
			bestradio = radio;
		}
	}
	assert( isdefined( bestradio ) );
	
	level.prevradio2 = level.prevradio;
	level.prevradio = bestradio;
	
	return bestradio;
}



onPlayerKilled( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, killId )
{
	if ( !isPlayer( attacker ) || (!self.touchTriggers.size && !attacker.touchTriggers.size) || attacker.pers["team"] == self.pers["team"] )
		return;

	if ( self.touchTriggers.size )
	{
		foreach ( trigger in self.touchTriggers )
		{
			// TODO: way to check for koth specific triggers
			if ( !isDefined( trigger.useObj ) )
				continue;
			
			ownerTeam = trigger.useObj.ownerTeam;
			team = self.pers["team"];

			if ( ownerTeam == "neutral" )
				continue;

			team = self.pers["team"];
			if ( team == ownerTeam )
			{
				attacker thread [[level.onXPEvent]]( "assault" );
				maps\mp\gametypes\_gamescore::givePlayerScore( "assault", attacker );
				
				thread maps\mp\_matchdata::logKillEvent( killId, "defending" );
			}
			else
			{
				attacker thread [[level.onXPEvent]]( "defend" );
				maps\mp\gametypes\_gamescore::givePlayerScore( "defend", attacker );
				
				attacker incPersStat( "defends", 1 );
				attacker maps\mp\gametypes\_persistence::statSetChild( "round", "defends", attacker.pers["defends"] );
				
				self thread maps\mp\_matchdata::logKillEvent( killId, "assaulting" );
			}
		}
	}	
	
	if ( attacker.touchTriggers.size )
	{
		foreach ( trigger in attacker.touchTriggers )
		{
			// TODO: way to check for koth specific triggers
			if ( !isDefined( trigger.useObj ) )
				continue;
			
			ownerTeam = trigger.useObj.ownerTeam;
			team = attacker.pers["team"];
		
			if ( ownerTeam == "neutral" )

			team = attacker.pers["team"];
			if ( team == ownerTeam )
			{
				attacker thread [[level.onXPEvent]]( "defend" );
				maps\mp\gametypes\_gamescore::givePlayerScore( "defend", attacker );

				self thread maps\mp\_matchdata::logKillEvent( killId, "assaulting" );
			}
			else
			{
				attacker thread [[level.onXPEvent]]( "assault" );
				maps\mp\gametypes\_gamescore::givePlayerScore( "assault", attacker );

				thread maps\mp\_matchdata::logKillEvent( killId, "defending" );
			}		
		}
	}
}


initGametypeAwards()
{
	maps\mp\_awards::initStatAward( "hqsdestroyed", 0, maps\mp\_awards::highestWins );
	maps\mp\_awards::initStatAward( "hqscaptured", 0, maps\mp\_awards::highestWins );
	//maps\mp\_awards::initStatAward( "captures", 0, maps\mp\_awards::highestWins );
}

/#
drawPoint( org, size, color )
{
	for ( i = 0; i < 10; i++ )
	{
		a1 = (i / 10) * 360;
		a2 = ((i + 1) / 10) * 360;
		
		pt1 = org + (cos(a1), sin(a1), 0) * size;
		pt2 = org + (cos(a2), sin(a2), 0) * size;
		
		line( pt1, pt2, color );
	}
}

kothDebug()
{
	while(1)
	{
		if (getdvar("scr_kothdebug") != "1") {
			wait 2;
			continue;
		}
		
		while(1)
		{
			if (getdvar("scr_kothdebug") != "1")
				break;
			if ( !isdefined( level.players ) || level.players.size <= 0 )
			{
				wait .05;
				continue;
			}
			
			// show nearest HQ and its "assault" spawnpoints
			
			bestdistsq = 99999999999;
			bestradio = level.radios[0];
			foreach ( radio in level.radios )
			{
				distsq = distanceSquared( radio.origin, level.players[0].origin );
				if ( distsq < bestdistsq )
				{
					bestdistsq = distsq;
					bestradio = radio;
				}
			}
			
			foreach ( radio in level.radios )
			{
				if ( radio != bestradio )
					drawPoint( radio.origin, 50, (.5,.5,.5) );
			}
			
			radio = bestradio;
			drawPoint( radio.origin, 100, (1,1,1) );
			
			foreach ( spawnpoint in radio.gameObject.outerSpawns )
			{
				line( radio.origin, spawnpoint.origin, (1,.5,.5) );
				drawPoint( spawnpoint.origin, 20, (1,.5,.5) );
			}
			foreach ( spawnpoint in radio.gameObject.nearSpawns )
			{
				line( radio.origin + (0,0,10), spawnpoint.origin + (0,0,10), (.5,1,.5) );
				drawPoint( spawnpoint.origin, 30, (.5,1,.5) );
			}
			
			wait .05;
		}
	}
}
#/
