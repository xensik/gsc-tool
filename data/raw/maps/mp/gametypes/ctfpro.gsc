#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;

/*QUAKED mp_ctf_pro_spawn_attackers_start (1.0 0.5 0.5) (-16 -16 0) (16 16 72)
Attackers spawn away from enemies and near their team at one of these positions at the start of a round.*/

/*QUAKED mp_ctf_pro_spawn_attackers (0.75 0.5 0.5) (-16 -16 0) (16 16 72)
Attackers spawn away from enemies and near their team at one of these positions.*/

/*QUAKED mp_ctf_pro_spawn_defenders_start (0.5 1.0 0.5) (-16 -16 0) (16 16 72)
Defenders spawn away from enemies and near their team at one of these positions at the start of a round.*/

/*QUAKED mp_ctf_pro_spawn_defenders (0.5 0.75 0.5) (-16 -16 0) (16 16 72)
Defenders spawn away from enemies and near their team at one of these positions.*/

main()
{
	maps\mp\gametypes\_globallogic::init();
	maps\mp\gametypes\_callbacksetup::SetupCallbacks();
	maps\mp\gametypes\_globallogic::SetupCallbacks();

	registerScoreLimitDvar( level.gameType, 1000 );
	registerTimeLimitDvar( level.gameType, 6, 0, 0 );
	registerRoundLimitDvar( level.gameType, 2, 0, 0 );
	setOverrideWatchDvar( "winlimit", 2 );
	registerRoundSwitchDvar( level.gameType, 1, 0, 0 );
	registerNumLivesDvar( level.gameType, 0, 0, 0 );
	registerHalfTimeDvar( level.gameType, 1, 0, 0 );

	//setOverTimeLimitDvar( 3 );
	
	level.teamBased = true;
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onPlayerKilled = ::onPlayerKilled;
	level.initGametypeAwards = ::initGametypeAwards;
	level.onHalfTime = ::onTimeLimit;
	level.onTimeLimit = ::onTimeLimit;
	level.onSpawnPlayer = ::onSpawnPlayer;
	
	level.scoreLimitOverride = true;
	level.overtimeScoreWinOverride = true;	

	level.flagReturnTime = getIntProperty( "scr_ctf_returntime", 30 );

	game["dialog"]["gametype"] = "captureflag";

	if ( getDvarInt( "g_hardcore" ) )
		game["dialog"]["gametype"] = "hc_" + game["dialog"]["gametype"];
	else if ( getDvarInt( "camera_thirdPerson" ) )
		game["dialog"]["gametype"] = "thirdp_" + game["dialog"]["gametype"];
	else if ( getDvarInt( "scr_diehard" ) )
		game["dialog"]["gametype"] = "dh_" + game["dialog"]["gametype"];
	else if (getDvarInt( "scr_" + level.gameType + "_promode" ) )
		game["dialog"]["gametype"] = game["dialog"]["gametype"] + "_pro";

	game["dialog"]["offense_obj"] = "capture_obj";
	game["dialog"]["defense_obj"] = "capture_obj";
}

onPrecacheGameType()
{
	precacheString(&"MP_FLAG_TAKEN_BY");
	precacheString(&"MP_ENEMY_FLAG_TAKEN_BY");
	precacheString(&"MP_FLAG_CAPTURED_BY");
	precacheString(&"MP_ENEMY_FLAG_CAPTURED_BY");
	precacheString(&"MP_FLAG_RETURNED");
	precacheString(&"MP_ENEMY_FLAG_RETURNED");
	precacheString(&"MP_YOUR_FLAG_RETURNING_IN");
	precacheString(&"MP_ENEMY_FLAG_RETURNING_IN");
	precacheString(&"MP_ENEMY_FLAG_DROPPED_BY");
	precacheString(&"MP_DOM_NEUTRAL_FLAG_CAPTURED");
	precacheString(&"MP_GRABBING_FLAG");
	precacheString(&"MP_RETURNING_FLAG");
}


onSpawnPlayer()
{
	if( ( inOvertime() ) && !isDefined( self.otSpawned ) )
		self thread printOTHint();
}


printOTHint()
{
	self endon ( "disconnect" );
	// give the "Overtime!" message time to show
	wait ( 0.25 );

	self.otSpawned = true;
	hintMessage = getObjectiveHintText( self.team );
	self thread maps\mp\gametypes\_hud_message::hintMessage( hintMessage );
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
		
		if ( game["roundsWon"][game["defenders"]] > 0 )
		{
			game["teamScores"][game["defenders"]] = 500;		
			setTeamScore( game["defenders"], 500 );			
		}
		else
		{
			game["teamScores"][game["defenders"]] = 0;		
			setTeamScore( game["defenders"], 0 );			
		}
	}	
	
	setClientNameMode("auto_change");
	
	if ( level.splitscreen )
	{
		if ( inOvertime() )
		{
			setObjectiveScoreText( game["attackers"], &"OBJECTIVES_GRAB_FLAG" );
			setObjectiveScoreText( game["defenders"], &"OBJECTIVES_GRAB_FLAG" );
		}
		else
		{
			setObjectiveScoreText( game["attackers"], &"OBJECTIVES_ONE_FLAG_ATTACKER" );
			setObjectiveScoreText( game["defenders"], &"OBJECTIVES_ONE_FLAG_DEFENDER" );
		}
	}
	else
	{
		if ( inOvertime() )
		{
			setObjectiveScoreText( game["attackers"], &"OBJECTIVES_GRAB_FLAG_SCORE" );
			setObjectiveScoreText( game["defenders"], &"OBJECTIVES_GRAB_FLAG_SCORE" );
		}
		else
		{
			setObjectiveScoreText( game["attackers"], &"OBJECTIVES_ONE_FLAG_ATTACKER_SCORE" );
			setObjectiveScoreText( game["defenders"], &"OBJECTIVES_ONE_FLAG_DEFENDER_SCORE" );
		}
	}
	
	if ( inOvertime() )
	{
		setObjectiveText( game["attackers"], &"OBJECTIVES_OVERTIME_CTF" );
		setObjectiveText( game["defenders"], &"OBJECTIVES_OVERTIME_CTF" );
		setObjectiveHintText( game["attackers"], &"OBJECTIVES_GRAB_FLAG_HINT" );
		setObjectiveHintText( game["defenders"], &"OBJECTIVES_GRAB_FLAG_HINT" );
	}
	else
	{
		setObjectiveText( game["attackers"], &"OBJECTIVES_CTF" );
		setObjectiveText( game["defenders"], &"OBJECTIVES_CTF" );
		setObjectiveHintText( game["attackers"], &"OBJECTIVES_ONE_FLAG_ATTACKER_HINT" );
		setObjectiveHintText( game["defenders"], &"OBJECTIVES_ONE_FLAG_DEFENDER_HINT" );
	}

	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_ctf_pro_spawn_attackers_start" );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_ctf_pro_spawn_defenders_start" );	
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( game["attackers"], "mp_ctf_pro_spawn_attackers" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( game["defenders"], "mp_ctf_pro_spawn_defenders" );
	
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "kill", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "headshot", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assist", 20 );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "pickup", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "return", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "capture", 250 );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "kill_carrier", 50 );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "defend", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "defend_assist", 100 );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "assault", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assault_assist", 100 );
	
	//	extra killstreak points for hard flags
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "capture", 1);
	
	allowed[0] = "ctf_pro";
	maps\mp\gametypes\_gameobjects::main(allowed);
		
	thread ctfPro();
}


getSpawnPoint()
{
	if ( level.inGracePeriod )
	{
		if ( self.team == game["attackers"] )
			label = "attackers";
		else
			label = "defenders";
		
		spawnPoints = getentarray("mp_ctf_pro_spawn_" + label + "_start", "classname");		
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random( spawnPoints );
	}
	else
	{
		spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( self.team );
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( spawnPoints );
	}
	
	return spawnPoint;
}


ctfPro()
{
	level.flagModel[game["defenders"]] = maps\mp\gametypes\_teams::getTeamFlagModel( game["defenders"] );
	level.icon2D[game["defenders"]] = maps\mp\gametypes\_teams::getTeamFlagIcon( game["defenders"] );
	level.carryFlag[game["defenders"]] = maps\mp\gametypes\_teams::getTeamFlagCarryModel( game["defenders"] );

	precacheModel( level.flagModel[game["defenders"]] );
	precacheModel( level.carryFlag[game["defenders"]] );
	
	level.iconEscort2D["a"] = "waypoint_escort_a";
	level.iconEscort2D["b"] = "waypoint_escort_b";
	level.iconEscort3D["a"] = level.iconEscort2D["a"];
	level.iconEscort3D["b"] = level.iconEscort2D["b"];
	precacheShader( level.iconEscort2D["a"] );
	precacheShader( level.iconEscort2D["b"] );

	level.iconKill2D["a"] = "waypoint_kill_a";
	level.iconKill2D["b"] = "waypoint_kill_b";
	level.iconKill3D["a"] = level.iconKill2D["a"];
	level.iconKill3D["b"] = level.iconKill2D["b"];
	precacheShader( level.iconKill2D["a"] );
	precacheShader( level.iconKill2D["b"] );

	level.iconCaptureFlag2D["a"] = "waypoint_capture_flag_a";
	level.iconCaptureFlag2D["b"] = "waypoint_capture_flag_b";
	level.iconCaptureFlag3D["a"] = level.iconCaptureFlag2D["a"];
	level.iconCaptureFlag3D["b"] = level.iconCaptureFlag2D["b"];
	precacheShader( level.iconCaptureFlag2D["a"] );
	precacheShader( level.iconCaptureFlag2D["b"] );

	level.iconDefendFlag2D["a"] = "waypoint_defend_flag_a";
	level.iconDefendFlag2D["b"] = "waypoint_defend_flag_b";
	level.iconDefendFlag3D["a"] = level.iconDefendFlag2D["a"];
	level.iconDefendFlag3D["b"] = level.iconDefendFlag2D["b"];
	precacheShader( level.iconDefendFlag2D["a"] );
	precacheShader( level.iconDefendFlag2D["b"] );

	level.iconReturnFlag2D["a"] = "waypoint_return_flag_a";
	level.iconReturnFlag2D["b"] = "waypoint_return_flag_b";
	level.iconReturnFlag3D["a"] = level.iconReturnFlag2D["a"];
	level.iconReturnFlag3D["b"] = level.iconReturnFlag2D["b"];
	precacheShader( level.iconReturnFlag2D["a"] );
	precacheShader( level.iconReturnFlag2D["b"] );
	
	level.iconFlagBase2D = "waypoint_flag_base";
	level.iconFlagBase3D = level.iconFlagBase2D;
	precacheShader( level.iconFlagBase2D );
	
	precacheShader( level.icon2D[game["defenders"]] );
	
	precacheShader( "waypoint_flag_friendly" );
	precacheShader( "waypoint_flag_enemy" );

	precacheString( &"OBJECTIVES_FLAG_HOME" );
	precacheString( &"OBJECTIVES_FLAG_NAME" );
	precacheString( &"OBJECTIVES_FLAG_AWAY" );
	
	level.teamFlags[game["defenders"]] = createTeamFlags( game["defenders"] ); 
	level.capZones[game["attackers"]] = createCapZones( game["attackers"] );
}

//sets overtime and associated variables
onTimeLimit()
{
	if ( game["switchedsides"] == true )
	{
		if ( game["roundsWon"][game["defenders"]] > 0 )
		{			
			game["teamScores"][game["defenders"]] = 1;		
			setTeamScore( game["defenders"], 1 );	
			game["teamScores"][game["attackers"]] = 0;		
			setTeamScore( game["attackers"], 0 );					
			
			setOverrideWatchDvar( "winlimit", 1 );
			level.onlyRoundOverride = true;
			thread maps\mp\gametypes\_gamelogic::endGame( game["defenders"], game["strings"]["time_limit_reached"] );
		}
		else
		{
			game["teamScores"][game["defenders"]] = 0;		
			setTeamScore( game["defenders"], 0 );	
			game["teamScores"][game["attackers"]] = 0;		
			setTeamScore( game["attackers"], 0 );			
			thread maps\mp\gametypes\_gamelogic::endGame( "tie", game["strings"]["time_limit_reached"] );
		}		
	}
	else
	{
		game["roundsPlayed"]++;
		game["teamScores"][game["attackers"]] = 0;			
		setTeamScore( game["attackers"], 0 );	
		thread maps\mp\gametypes\_gamelogic::endGame( "halftime", game["strings"]["time_limit_reached"] );		
	}
}

spawnFxDelay( fxid, pos, forward, right, delay )
{
	wait delay;
	effect = spawnFx( fxid, pos, forward, right );
	triggerFx( effect );
}

createTeamFlags( team )
{
	teamFlags = [];
	teamFlags[0] = createTeamFlag( team, "a" );
	teamFlags[0].points = 200;
	teamFlags[1] = createTeamFlag( team, "b" );
	teamFlags[1].points = 200;
	
	return teamFlags;
}

createTeamFlag( team, label )
{
	trigger = getEnt( "ctf_pro_trig_" + label, "targetname" );
	if ( !isDefined( trigger ) ) 
	{
		error( "No ctf_pro_trig_" + label + " trigger found in map." );
		return;
	}
	visual = getEnt( "ctf_pro_flag_" + label, "targetname" );
	if ( !isDefined( visual ) ) 
	{
		error( "No ctf_pro_flag_" + label + " script_model found in map." );
		return;
	}	
	marker = getEnt( "ctf_pro_flag_spawn_" + label, "targetname" );
	if ( !isDefined( marker ) )
	{
		error( "No ctf_pro_flag_spawn_" + label + " script_origin found in map." );
		return;
	}		
		
	visual setModel( level.flagModel[team] );	
	carryVisuals[0] = visual;
	
	teamFlag = maps\mp\gametypes\_gameobjects::createCarryObject( team, trigger, carryVisuals, (0,0,85) );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseTime( "friendly", 0.5 );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseTime( "enemy", 0.5 );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseText( "enemy", &"MP_GRABBING_FLAG" );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseText( "friendly", &"MP_RETURNING_FLAG" );
	teamFlag maps\mp\gametypes\_gameobjects::allowCarry( "enemy" );
	
	teamFlag maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	teamFlag maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconKill2D[label] );
	teamFlag maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconKill3D[label] );
	teamFlag maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconEscort2D[label] );
	teamFlag maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconEscort3D[label] );

	teamFlag maps\mp\gametypes\_gameobjects::setCarryIcon( level.icon2D[team] );
	teamFlag.objIDPingFriendly = true;
	teamFlag.allowWeapons = true;
	teamFlag.onPickup = ::onPickup;
	teamFlag.onPickupFailed = ::onPickup;
	teamFlag.onDrop = ::onDrop;
	teamFlag.onReset = ::onReset;
	
	teamFlag.oldRadius = trigger.radius;
	teamFlag.atHome = true;
	teamFlag.label = label;
	
	carryVisuals = [];
	flagMarker = maps\mp\gametypes\_gameobjects::createUseObject( team, marker, carryVisuals, (0,0,85) );
	flagMarker maps\mp\gametypes\_gameobjects::allowUse( "none" );		
	flagMarker maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	flagMarker maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconDefendFlag2D[label] );
	flagMarker maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconDefendFlag3D[label] );
	flagMarker maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconCaptureFlag2D[label] );
	flagMarker maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconCaptureFlag3D[label] );
	teamFlag.marker = flagMarker;	

	traceStart = trigger.origin + (0,0,32);
	traceEnd = trigger.origin + (0,0,-32);
	trace = bulletTrace( traceStart, traceEnd, false, undefined );
	
	fx = maps\mp\gametypes\_teams::getTeamFlagFX( team );
	fxid = loadfx( fx );
	
	upangles = vectorToAngles( trace["normal"] );
	forward = anglesToForward( upangles );
	right = anglesToRight( upangles );
	
	thread spawnFxDelay( fxid, trace["position"], forward, right, 0.5 );

	return teamFlag;	
}

createCapZones( team )
{
	triggers = [];
	triggers = getEntArray( "ctf_pro_zone", "targetname" );
	if ( !isDefined( triggers[0] ) ) 
	{
		error("No ctf_pro_zone" + " triggers found in map.");
		return;
	}
	
	capZones = [];
	for( i=0; i<triggers.size; i++ )
	{	
		//	temp until I get rid of the 3rd flag
		if ( isDefined( level.teamFlags[ getOtherTeam( team ) ][i] ) )
		{
			visuals = [];
			capZones[i] = maps\mp\gametypes\_gameobjects::createUseObject( team, triggers[i], visuals, (0,0,0) );
			capZones[i] maps\mp\gametypes\_gameobjects::allowUse( "friendly" );
			capZones[i] maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
			capZones[i] maps\mp\gametypes\_gameobjects::setUseTime( 0 );
			capZones[i] maps\mp\gametypes\_gameobjects::setKeyObject( level.teamFlags[ getOtherTeam( team ) ][i] );
			
			capZones[i].onUse = ::onUse;
			capZones[i].onCantUse = ::onCantUse;
		}
	}
	
	//	Only need visuals for one cap zone (the three exist in the same place, each keyed to a different flag)
	//	save origin on one of the cap zones for cap zone headicon creation for flag carrier
	capZones[0].origin = triggers[0].origin;	
		
	traceStart = triggers[0].origin + (0,0,32);
	traceEnd = triggers[0].origin + (0,0,-32);
	trace = bulletTrace( traceStart, traceEnd, false, undefined );
	
	fx = maps\mp\gametypes\_teams::getTeamFlagFX( team );
	fxid = loadfx( fx );
	
	upangles = vectorToAngles( trace["normal"] );
	forward = anglesToForward( upangles );
	right = anglesToRight( upangles );
	
	thread spawnFxDelay( fxid, trace["position"], forward, right, 0.5 );
	
	return capZones;
}


onBeginUse( player )
{
	team = player.pers["team"];

	if ( team == self maps\mp\gametypes\_gameobjects::getOwnerTeam() )
		self.trigger.radius = 1024;
	else
		self.trigger.radius = self.oldRadius;
}


onEndUse( player, team, success )
{
	self.trigger.radius = self.oldRadius;
}


onPickup( player )
{	
	self notify ( "picked_up" );

	team = player.pers["team"];

	if ( team == "allies" )
		otherTeam = "axis";
	else
		otherTeam = "allies";
		
	if ( team == self maps\mp\gametypes\_gameobjects::getOwnerTeam() )
	{
		thread teamPlayerCardSplash( "callout_flagreturn", player );
		player thread maps\mp\gametypes\_hud_message::SplashNotify( "flagreturn", maps\mp\gametypes\_rank::getScoreInfoValue( "return" ) );
		maps\mp\gametypes\_gamescore::givePlayerScore( "return", player );
		player thread [[level.onXPEvent]]( "return" );
		self thread returnFlag();
		player incPlayerStat( "flagsreturned", 1 );
		
		player incPersStat( "returns", 1 );
		//player maps\mp\gametypes\_persistence::statSetChild( "round", "returns", player.flagsreturned );
		
		player thread maps\mp\_matchdata::logGameEvent( "return", player.origin );

		printAndSoundOnEveryone( team, getOtherTeam( team ), &"MP_FLAG_RETURNED", &"MP_ENEMY_FLAG_RETURNED", "mp_obj_returned", "mp_obj_returned", "" );
		leaderDialog( "enemy_flag_returned", otherteam, "status" );
		leaderDialog( "flag_returned", team, "status" );	
	}
	else
	{
		player attachFlag( self );

		self maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
		self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconKill2D[self.label] );
		self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconKill3D[self.label] );
		self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconEscort2D[self.label] );
		self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconEscort3D[self.label] );
		
		self.marker maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
		
		player.zoneHeadIcon = level.capZones[game["attackers"]][0] maps\mp\_entityheadIcons::setHeadIcon( player, level.iconFlagBase2D, (0,0,0), 24, 24, undefined, undefined, undefined, undefined, undefined, false );		
		
		player.zoneMapIcon = maps\mp\gametypes\_gameobjects::getNextObjID();	
		objective_add( player.zoneMapIcon, "invisible", (0,0,0) );
		objective_position( player.zoneMapIcon, level.capZones[game["attackers"]][0].origin );
		objective_state( player.zoneMapIcon, "active" );
		objective_player( player.zoneMapIcon, player getEntityNumber() );
		objective_icon( player.zoneMapIcon, level.iconFlagBase2D );				

		printAndSoundOnEveryone( team, otherteam, &"MP_ENEMY_FLAG_TAKEN_BY", &"MP_FLAG_TAKEN_BY", "mp_obj_taken", "mp_enemy_obj_taken", player );

		leaderDialog( "enemy_flag_taken", team, "status" );
		leaderDialog( "flag_taken", otherteam, "status" );

		thread teamPlayerCardSplash( "callout_flagpickup", player );
		player thread maps\mp\gametypes\_hud_message::SplashNotify( "flagpickup", maps\mp\gametypes\_rank::getScoreInfoValue( "pickup" ) );
		maps\mp\gametypes\_gamescore::givePlayerScore( "pickup", player );
		player thread [[level.onXPEvent]]( "pickup" );
		player incPlayerStat( "flagscarried", 1 );
		player thread maps\mp\_matchdata::logGameEvent( "pickup", player.origin );
	}
}


returnFlag()
{
	self maps\mp\gametypes\_gameobjects::returnHome();	
}


onDrop( player )
{
	team = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	otherTeam = level.otherTeam[team];

	self maps\mp\gametypes\_gameobjects::allowCarry( "any" );
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconReturnFlag2D[self.label] );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconReturnFlag3D[self.label] );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconCaptureFlag2D[self.label] );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconCaptureFlag3D[self.label] );

	if ( isDefined( player ) )
	{
 		if ( isDefined( player.carryFlag ) )
			player detachFlag();
		
		printAndSoundOnEveryone( otherTeam, "none", &"MP_ENEMY_FLAG_DROPPED_BY", "", "mp_war_objective_lost", "", player );	
		
		if ( isDefined( player.zoneHeadIcon ) )
			player.zoneHeadIcon destroy();
		if ( isDefined( player.zoneMapIcon ) )
		{
			_objective_delete( player.zoneMapIcon );
			player.zoneMapIcon = undefined;
		}	
	}
	else
	{
		playSoundOnPlayers( "mp_war_objective_lost", otherTeam );
	}

	leaderDialog( "enemy_flag_dropped", otherTeam, "status" );
	leaderDialog( "flag_dropped", team, "status" );
	
	self thread returnAfterTime();
}

returnAfterTime()
{
	self endon ( "picked_up" );
	
	wait ( level.flagReturnTime );
	
	self maps\mp\gametypes\_gameobjects::returnHome();
}


onReset()
{
	team = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	otherTeam = level.otherTeam[team];

	self maps\mp\gametypes\_gameobjects::allowCarry( "enemy" );
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconKill2D[self.label] );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconKill3D[self.label] );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconEscort2D[self.label] );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconEscort3D[self.label] );
	
	self.marker maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );	
}


onUse( player )
{
	team = player.pers["team"];
	if ( team == "allies" )
		otherTeam = "axis";
	else
		otherTeam = "allies";

	leaderDialog( "enemy_flag_captured", team, "status" );
	leaderDialog( "flag_captured", otherteam, "status" );	

	thread teamPlayerCardSplash( "callout_flagcapture", player );
	giveScore( team, player.cappedFlag.points );	
	player thread maps\mp\gametypes\_hud_message::SplashNotify( "flag_capture", maps\mp\gametypes\_rank::getScoreInfoValue( "capture" ) );
	maps\mp\gametypes\_gamescore::givePlayerScore( "capture", player );
	player thread [[level.onXPEvent]]( "capture" );
	
	player incPlayerStat( "flagscaptured", 1 );
	
	player incPersStat( "captures", 1 );
	//player maps\mp\gametypes\_persistence::statSetChild( "round", "captures", player.flagscaptured );
	
	player notify( "objective", "captured" );
	player thread maps\mp\_matchdata::logGameEvent( "capture", player.origin );
	
	//	extra killstreak points for hard flags
	if ( isDefined( level.adrenalineInfo[ "capture" ] ) )
		player maps\mp\killstreaks\_killstreaks::giveAdrenaline( "capture" );
		

	printAndSoundOnEveryone( team, otherteam, &"MP_ENEMY_FLAG_CAPTURED_BY", &"MP_FLAG_CAPTURED_BY", "mp_obj_captured", "mp_enemy_obj_captured", player );

	if ( isDefined( player.carryFlag ) )
		player detachFlag();
		
	if ( isDefined( player.zoneHeadIcon ) )
		player.zoneHeadIcon destroy();	
	if ( isDefined( player.zoneMapIcon ) )
	{
		_objective_delete( player.zoneMapIcon );
		player.zoneMapIcon = undefined;
	}			

	player.cappedFlag returnFlag();
}

giveScore( team, score )
{
	maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( team, score );
	
	if ( game["state"] != "playing" )
		return;
	
	if ( game["switchedsides"] )
	{
		if( game["teamScores"][game["attackers"]] >= getWatchedDvar( "scorelimit" ) )
		{
			setOverrideWatchDvar( "winlimit", 1 );
			level.onlyRoundOverride = true;		
			
			if ( game["roundsWon"][game["defenders"]] == 0 )
			{
				game["teamScores"][game["attackers"]] = 1;		
				setTeamScore( game["attackers"], 1 );
				game["teamScores"][game["defenders"]] = 0;		
				setTeamScore( game["defenders"], 0 );				
				
				thread maps\mp\gametypes\_gamelogic::endGame( game["attackers"], game["strings"]["score_limit_reached"] );
			}
			else
			{
				game["teamScores"][game["attackers"]] = 1;		
				setTeamScore( game["attackers"], 1 );
				game["teamScores"][game["defenders"]] = 1;		
				setTeamScore( game["defenders"], 1 );				
				
				thread maps\mp\gametypes\_gamelogic::endGame( "tie", game["strings"]["score_limit_reached"] );
			}
		}		
	}
	else 
	{		
		if( game["teamScores"][game["attackers"]] >= getWatchedDvar( "scorelimit" ) )
		{
			game["roundsPlayed"]++;			
				
			game["teamScores"][game["attackers"]] = 1;		
			setTeamScore( game["attackers"], 1 );
			game["teamScores"][game["defenders"]] = 0;		
			setTeamScore( game["defenders"], 0 );				
			
			game["roundsWon"][game["attackers"]]++;
			maps\mp\gametypes\_gamescore::updateTeamScore( game["attackers"] );
			thread maps\mp\gametypes\_gamelogic::endGame( "halftime", game["strings"]["score_limit_reached"] );
		}	
	}
}


onCantUse( player )
{
//	player iPrintLnBold( &"MP_CANT_PLANT_WITHOUT_BOMB" );
}


onPlayerKilled( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, killId )
{
	if ( isDefined( attacker ) && isPlayer( attacker ) && attacker.pers["team"] != self.pers["team"] )
	{
		if ( isDefined( attacker.carryFlag ) )
			attacker incPlayerStat( "killsasflagcarrier", 1 );

		if ( isDefined( self.carryFlag ) )
		{
			thread teamPlayerCardSplash( "callout_killflagcarrier", attacker );
			attacker thread maps\mp\gametypes\_hud_message::SplashNotify( "killflagcarrier", maps\mp\gametypes\_rank::getScoreInfoValue( "kill_carrier" ) );
			maps\mp\gametypes\_gamescore::givePlayerScore( "kill_carrier", attacker );
			attacker thread [[level.onXPEvent]]( "kill_carrier" );
			
			attacker incPersStat( "defends", 1 );
			//attacker maps\mp\gametypes\_persistence::statSetChild( "round", "defends", attacker.defends );
			
			thread maps\mp\_matchdata::logKillEvent( killId, "carrying" );
			
			self detachFlag();
		}
	}
}


attachFlag( cappedFlag )
{
	otherTeam = level.otherTeam[self.pers["team"]];
	
	self attach( level.carryFlag[otherTeam], "J_spine4", true );
	self.carryFlag = level.carryFlag[otherTeam];
	self.cappedFlag = cappedFlag;
}

detachFlag()
{
	self detach( self.carryFlag, "J_spine4" );
	self.carryFlag = undefined;
}

initGametypeAwards()
{
	maps\mp\_awards::initStatAward( "flagscaptured",		0, maps\mp\_awards::highestWins );
	maps\mp\_awards::initStatAward( "flagsreturned", 		0, maps\mp\_awards::highestWins );
	maps\mp\_awards::initStatAward( "flagcarrierkills", 	0, maps\mp\_awards::highestWins );
	maps\mp\_awards::initStatAward( "flagscarried",			0, maps\mp\_awards::highestWins );
	maps\mp\_awards::initStatAward( "killsasflagcarrier", 	0, maps\mp\_awards::highestWins );
}