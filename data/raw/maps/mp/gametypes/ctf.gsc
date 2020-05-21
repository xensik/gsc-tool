#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
/*
	One Flag CTF
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

	if ( isUsingMatchRulesData() )
	{
		level.initializeMatchRules = ::initializeMatchRules;
		[[level.initializeMatchRules]]();
		level thread reInitializeMatchRulesOnMigration();
	}
	else
	{
		registerTimeLimitDvar( level.gameType, 5 );
		registerScoreLimitDvar( level.gameType, 3 );
		registerRoundLimitDvar( level.gameType, 1 );
		registerWinLimitDvar( level.gameType, 1 );
		registerNumLivesDvar( level.gameType, 0 );
		registerHalfTimeDvar( level.gameType, 0 );
		
		level.matchRules_damageMultiplier = 0;
		level.matchRules_vampirism = 0;	
	}

	setOverTimeLimitDvar( 4 );
		
	setSpecialLoadouts();
	
	level.teamBased = true;
	level.objectiveBased = true;
	level.overtimeScoreWinOverride = true;
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onPlayerKilled = ::onPlayerKilled;
	level.initGametypeAwards = ::initGametypeAwards;
	level.onTimeLimit = ::onTimeLimit;
	level.onSpawnPlayer = ::onSpawnPlayer;
	
	if ( level.matchRules_damageMultiplier || level.matchRules_vampirism )
		level.modifyPlayerDamage = maps\mp\gametypes\_damage::gamemodeModifyPlayerDamage;

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


initializeMatchRules()
{
	//	set common values
	setCommonRulesFromMatchRulesData();
	
	//	set everything else (private match options, default .cfg file values, and what normally is registered in the 'else' below)
	SetDynamicDvar( "scr_ctf_roundlimit", 1 );
	registerRoundLimitDvar( "ctf", 1 );					
	SetDynamicDvar( "scr_ctf_winlimit", 1 );
	registerWinLimitDvar( "ctf", 1 );			
	SetDynamicDvar( "scr_ctf_halftime", 0 );
	registerHalfTimeDvar( "ctf", 0 );
		
	SetDynamicDvar( "scr_ctf_returntime", 30 );
	SetDynamicDvar( "scr_ctf_promode", 0 );		
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
	//if( ( inOvertime() ) && !isDefined( self.otSpawned ) )
		//self thread printOTHint();
		
	//	flag carrier class? clear this regardless if they were carrier
	if ( isDefined( level.ctf_loadouts ) && isDefined( level.ctf_loadouts[self.team] ) )
		self.pers["gamemodeLoadout"] = undefined;		
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
		
	if ( inOvertime() )
		setDvar( "ui_override_halftime", 0 );
	else if ( game["switchedsides"] )
		setDvar( "ui_override_halftime", 2 );
	else
		setDvar( "ui_override_halftime", 1 );

	if ( !isdefined( game["original_defenders"] ) )
		game["original_defenders"] = game["defenders"];

	if ( game["switchedsides"] )
	{
		oldAttackers = game["attackers"];
		oldDefenders = game["defenders"];
		game["attackers"] = oldDefenders;
		game["defenders"] = oldAttackers;
	}
	
	//	set scores to zero at beginning of every round, round wins is what counts to game win
	game["teamScores"][game["attackers"]] = 0;		
	setTeamScore( game["attackers"], 0 );	
	game["teamScores"][game["defenders"]] = 0;		
	setTeamScore( game["defenders"], 0 );	

	setClientNameMode("auto_change");
	
	if ( level.splitscreen )
	{
		setObjectiveScoreText( game["attackers"], &"OBJECTIVES_ONE_FLAG_ATTACKER" );
		setObjectiveScoreText( game["defenders"], &"OBJECTIVES_ONE_FLAG_DEFENDER" );
	}
	else
	{
		setObjectiveScoreText( game["attackers"], &"OBJECTIVES_ONE_FLAG_ATTACKER_SCORE" );
		setObjectiveScoreText( game["defenders"], &"OBJECTIVES_ONE_FLAG_DEFENDER_SCORE" );
	}
	
	setObjectiveText( game["attackers"], &"OBJECTIVES_CTF" );
	setObjectiveText( game["defenders"], &"OBJECTIVES_CTF" );
	setObjectiveHintText( game["attackers"], &"OBJECTIVES_ONE_FLAG_ATTACKER_HINT" );
	setObjectiveHintText( game["defenders"], &"OBJECTIVES_ONE_FLAG_DEFENDER_HINT" );

	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_ctf_spawn_allies_start" );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_ctf_spawn_axis_start" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_ctf_spawn_allies" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_ctf_spawn_axis" );
	
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
	
	maps\mp\gametypes\_rank::registerScoreInfo( "assault", 200 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assault_assist", 40 );
	
	allowed[0] = "ctf";
	maps\mp\gametypes\_gameobjects::main(allowed);
		
	thread ctf();
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

//	if ( game["switchedsides"] )
//		spawnTeam = getOtherTeam( spawnteam );
	
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


ctf()
{
	level.flagModel["allies"] = maps\mp\gametypes\_teams::getTeamFlagModel( "allies" );
	level.icon2D["allies"] = maps\mp\gametypes\_teams::getTeamFlagIcon( "allies" );
	level.carryFlag["allies"] = maps\mp\gametypes\_teams::getTeamFlagCarryModel( "allies" );

	precacheModel( level.flagModel["allies"] );
	precacheModel( level.carryFlag["allies"] );

	level.flagModel["axis"] = maps\mp\gametypes\_teams::getTeamFlagModel( "axis" );
	level.icon2D["axis"] = maps\mp\gametypes\_teams::getTeamFlagIcon( "axis" );
	level.carryFlag["axis"] = maps\mp\gametypes\_teams::getTeamFlagCarryModel( "axis" );

	precacheModel( level.flagModel["axis"] );
	precacheModel( level.carryFlag["axis"] );
	
	level.iconEscort3D = "waypoint_escort";
	level.iconEscort2D = "waypoint_escort";
	precacheShader( level.iconEscort3D );
	precacheShader( level.iconEscort2D );
	//level.iconEscort2D = level.iconEscort3D; // flags with words on compass

	level.iconKill3D = "waypoint_kill";
	level.iconKill2D = "waypoint_kill";
	precacheShader( level.iconKill3D );
	precacheShader( level.iconKill2D );
	//level.iconKill2D = level.iconKill3D; // flags with words on compass

	level.iconCaptureFlag3D = "waypoint_capture_flag";
	level.iconCaptureFlag2D = "waypoint_capture_flag";
	precacheShader( level.iconCaptureFlag3D );
	precacheShader( level.iconCaptureFlag2D );
	//level.iconCaptureFlag2D = level.iconCaptureFlag3D; // flags with words on compass

	level.iconDefendFlag3D = "waypoint_defend_flag";
	level.iconDefendFlag2D = "waypoint_defend_flag";
	precacheShader( level.iconDefendFlag3D );
	precacheShader( level.iconDefendFlag2D );
	//level.iconDefendFlag2D = level.iconDefendFlag3D; // flags with words on compass

	level.iconReturnFlag3D = "waypoint_return_flag";
	level.iconReturnFlag2D = "waypoint_return_flag";
	precacheShader( level.iconReturnFlag3D );
	precacheShader( level.iconReturnFlag2D );
	//level.iconReturnFlag2D = level.iconReturnFlag3D; // flags with words on compass

	level.iconWaitForFlag3D = "waypoint_waitfor_flag";
	level.iconWaitForFlag2D = "waypoint_waitfor_flag";
	precacheShader( level.iconWaitForFlag3D );
	precacheShader( level.iconWaitForFlag2D );
	//level.iconWaitForFlag2D = level.iconWaitForFlag3D; // flags with words on compass
	
	precacheShader( level.icon2D["axis"] );
	precacheShader( level.icon2D["allies"] );
	
	precacheShader( "waypoint_flag_friendly" );
	precacheShader( "waypoint_flag_enemy" );

	precacheString( &"OBJECTIVES_FLAG_HOME" );
	precacheString( &"OBJECTIVES_FLAG_NAME" );
	precacheString( &"OBJECTIVES_FLAG_AWAY" );
	
	level.teamFlags[game["defenders"]] = createTeamFlag( game["defenders"], "allies" );
	level.teamFlags[game["attackers"]] = createTeamFlag( game["attackers"], level.otherTeam["allies"] );

	level.capZones[game["defenders"]] = createCapZone( game["defenders"], "allies" );
	level.capZones[game["attackers"]] = createCapZone( game["attackers"], level.otherTeam["allies"] );
	
	if ( level.splitScreen )
		hudElemAlpha = 0;
	else
		hudElemAlpha = 0.85;
	
	level.friendlyFlagStatusIcon["allies"] = createServerIcon( "waypoint_flag_friendly", 32, 32, "allies" );
	level.friendlyFlagStatusIcon["allies"] setPoint( "TOP LEFT", "TOP LEFT", 132, 0 );
	level.friendlyFlagStatusIcon["allies"].alpha = hudElemAlpha;
	level.friendlyFlagStatusIcon["allies"].hideWhenInMenu = true;
	level thread hideHudElementOnGameEnd( level.friendlyFlagStatusIcon["allies"] );

	level.friendlyFlagStatusText["allies"] = createServerFontString( "small", 1.6, "allies" );	
	level.friendlyFlagStatusText["allies"] setParent( level.friendlyFlagStatusIcon["allies"] );
	level.friendlyFlagStatusText["allies"] setPoint( "LEFT", "RIGHT", 4 );
	level.friendlyFlagStatusText["allies"] setText( &"OBJECTIVES_FLAG_HOME" );
	level.friendlyFlagStatusText["allies"].alpha = hudElemAlpha;
	level.friendlyFlagStatusText["allies"].color = (1,1,1);
	level.friendlyFlagStatusText["allies"].glowAlpha = 1;
	level.friendlyFlagStatusText["allies"].hideWhenInMenu = true;
	level thread hideHudElementOnGameEnd( level.friendlyFlagStatusText["allies"] );

	level.enemyFlagStatusIcon["allies"] = createServerIcon( "waypoint_flag_enemy", 24, 24, "allies" );
	level.enemyFlagStatusIcon["allies"] setPoint( "TOP LEFT", "TOP LEFT", 132, 26 );
	level.enemyFlagStatusIcon["allies"].alpha = hudElemAlpha;
	level.enemyFlagStatusIcon["allies"].hideWhenInMenu = true;
	level thread hideHudElementOnGameEnd( level.enemyFlagStatusIcon["allies"] );

	level.enemyFlagStatusText["allies"] = createServerFontString( "small", 1.6, "allies" );
	level.enemyFlagStatusText["allies"] setParent( level.enemyFlagStatusIcon["allies"] );
	level.enemyFlagStatusText["allies"] setPoint( "LEFT", "RIGHT", 4 );
	level.enemyFlagStatusText["allies"] setText( &"OBJECTIVES_FLAG_HOME" );	
	level.enemyFlagStatusText["allies"].alpha = hudElemAlpha;
	level.enemyFlagStatusText["allies"].color = (1,1,1);
	level.enemyFlagStatusText["allies"].glowAlpha = 1;
	level.enemyFlagStatusText["allies"].hideWhenInMenu = true;
	level thread hideHudElementOnGameEnd( level.enemyFlagStatusText["allies"] );


	level.friendlyFlagStatusIcon["axis"] = createServerIcon( "waypoint_flag_friendly", 32, 32, "axis" );
	level.friendlyFlagStatusIcon["axis"] setPoint( "TOP LEFT", "TOP LEFT", 132, 0 );
	level.friendlyFlagStatusIcon["axis"].alpha = hudElemAlpha;
	level.friendlyFlagStatusIcon["axis"].hideWhenInMenu = true;
	level thread hideHudElementOnGameEnd( level.friendlyFlagStatusIcon["axis"] );

	level.friendlyFlagStatusText["axis"] = createServerFontString( "small", 1.6, "axis" );	
	level.friendlyFlagStatusText["axis"] setParent( level.friendlyFlagStatusIcon["axis"] );
	level.friendlyFlagStatusText["axis"] setPoint( "LEFT", "RIGHT", 4 );
	level.friendlyFlagStatusText["axis"] setText( &"OBJECTIVES_FLAG_HOME" );
	level.friendlyFlagStatusText["axis"].alpha = hudElemAlpha;
	level.friendlyFlagStatusText["axis"].color = (1,1,1);
	level.friendlyFlagStatusText["axis"].glowAlpha = 1;
	level.friendlyFlagStatusText["axis"].hideWhenInMenu = true;
	level thread hideHudElementOnGameEnd( level.friendlyFlagStatusText["axis"] );

	level.enemyFlagStatusIcon["axis"] = createServerIcon( "waypoint_flag_enemy", 24, 24, "axis" );
	level.enemyFlagStatusIcon["axis"] setPoint( "TOP LEFT", "TOP LEFT", 132, 26 );
	level.enemyFlagStatusIcon["axis"].alpha = hudElemAlpha;
	level.enemyFlagStatusIcon["axis"].hideWhenInMenu = true;
	level thread hideHudElementOnGameEnd( level.enemyFlagStatusIcon["axis"] );

	level.enemyFlagStatusText["axis"] = createServerFontString( "small", 1.6, "axis" );
	level.enemyFlagStatusText["axis"] setParent( level.enemyFlagStatusIcon["axis"] );
	level.enemyFlagStatusText["axis"] setPoint( "LEFT", "RIGHT", 4 );
	level.enemyFlagStatusText["axis"] setText( &"OBJECTIVES_FLAG_HOME" );	
	level.enemyFlagStatusText["axis"].alpha = hudElemAlpha;
	level.enemyFlagStatusText["axis"].color = (1,1,1);
	level.enemyFlagStatusText["axis"].glowAlpha = 1;
	level.enemyFlagStatusText["axis"].hideWhenInMenu = true;
	level thread hideHudElementOnGameEnd( level.enemyFlagStatusText["axis"] );
}

hideHudElementOnGameEnd( hudElement )
{
	level waittill( "game_ended" );
	
	if ( isDefined( hudElement ) )
		hudElement.alpha = 0;
}

spawnFxDelay( fxid, pos, forward, right, delay )
{
	wait delay;
	effect = spawnFx( fxid, pos, forward, right );
	triggerFx( effect );
}

createTeamFlag( team, entityTeam )
{
	trigger = getEnt( "ctf_zone_" + entityTeam, "targetname" );
	if ( !isDefined( trigger ) ) 
	{
		error( "No ctf_zone_" + entityTeam + " trigger found in map." );
		return;
	}
	visuals[0] = getEnt( "ctf_flag_" + entityTeam, "targetname" );
	if ( !isDefined( visuals[0] ) ) 
	{
		error( "No ctf_flag_" + entityTeam + " script_model found in map." );
		return;
	}
	
	cloneTrigger = spawn( "trigger_radius", trigger.origin, 0, 96, trigger.height );
	trigger = cloneTrigger;
	
	visuals[0] setModel( level.flagModel[team] );
	
	teamFlag = maps\mp\gametypes\_gameobjects::createCarryObject( team, trigger, visuals, (0,0,85) );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseTime( "friendly", 0.5 );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseTime( "enemy", 0.5 );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseText( "enemy", &"MP_GRABBING_FLAG" );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseText( "friendly", &"MP_RETURNING_FLAG" );
	teamFlag maps\mp\gametypes\_gameobjects::allowCarry( "enemy" );
	
	teamFlag maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	teamFlag maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconKill2D );
	teamFlag maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconKill3D );
	teamFlag maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconEscort2D );
	teamFlag maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconEscort3D );

	teamFlag maps\mp\gametypes\_gameobjects::setCarryIcon( level.icon2D[team] );
	teamFlag.objIDPingFriendly = true;
	teamFlag.allowWeapons = true;
	teamFlag.onPickup = ::onPickup;
	teamFlag.onPickupFailed = ::onPickup;
	teamFlag.onDrop = ::onDrop;
	teamFlag.onReset = ::onReset;
	
	teamFlag.oldRadius = trigger.radius;
	//	too risky, too many situations where people can block the flag grab and cap
	//teamFlag.requiresLOS = true;

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

createCapZone( team, entityTeam )
{
	trigger = getEnt( "ctf_zone_" + entityTeam, "targetname" );
	if ( !isDefined( trigger ) ) 
	{
		error("No ctf_zone_" + entityTeam + " trigger found in map.");
		return;
	}
	
	visuals = [];
	capZone = maps\mp\gametypes\_gameobjects::createUseObject( team, trigger, visuals, (0,0,85) );
	capZone maps\mp\gametypes\_gameobjects::allowUse( "friendly" );

	capZone maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	capZone maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconDefendFlag2D );
	capZone maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconDefendFlag3D );
	capZone maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconCaptureFlag2D );
	capZone maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconCaptureFlag3D );

	capZone maps\mp\gametypes\_gameobjects::setUseTime( 0 );
	capZone maps\mp\gametypes\_gameobjects::setKeyObject( level.teamFlags[ getOtherTeam( team ) ] );
	
	capZone.onUse = ::onUse;
	capZone.onCantUse = ::onCantUse;
		
	traceStart = trigger.origin + (0,0,32);
	traceEnd = trigger.origin + (0,0,-32);
	trace = bulletTrace( traceStart, traceEnd, false, undefined );
	
	fx = maps\mp\gametypes\_teams::getTeamFlagFX( team );
	fxid = loadfx( fx );
	
	upangles = vectorToAngles( trace["normal"] );
	forward = anglesToForward( upangles );
	right = anglesToRight( upangles );
	
	thread spawnFxDelay( fxid, trace["position"], forward, right, 0.5 );
	
	return capZone;
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
		player thread maps\mp\gametypes\_hud_message::SplashNotify( "flagreturn", maps\mp\gametypes\_rank::getScoreInfoValue( "return" ) );
		player thread [[level.onXPEvent]]( "return" );
		self thread returnFlag();
		player incPlayerStat( "flagsreturned", 1 );
		player thread maps\mp\_matchdata::logGameEvent( "return", player.origin );

		printAndSoundOnEveryone( team, getOtherTeam( team ), &"MP_FLAG_RETURNED", &"MP_ENEMY_FLAG_RETURNED", "mp_obj_returned", "mp_obj_returned", "" );
		leaderDialog( "enemy_flag_returned", otherteam, "status" );
		leaderDialog( "flag_returned", team, "status" );
		
		player incPersStat( "returns", 1 );
		player maps\mp\gametypes\_persistence::statSetChild( "round", "returns", player.pers["returns"] );	

		level.friendlyFlagStatusText[team] setText( &"OBJECTIVES_FLAG_HOME" );
		level.friendlyFlagStatusText[team].glowColor = (1,1,1);
		level.friendlyFlagStatusText[team].glowAlpha = 0;			
		level.enemyFlagStatusText[otherTeam] setText( &"OBJECTIVES_FLAG_HOME" );
		level.enemyFlagStatusText[otherTeam].glowColor = (1,1,1);
		level.enemyFlagStatusText[otherTeam].glowAlpha = 0;
	}
	else
	{
		//	flag carrier class?  (do before attaching flag)
		if ( isDefined( level.ctf_loadouts ) && isDefined( level.ctf_loadouts[team] ) )
			player thread applyFlagCarrierClass();	// does flag attach
		else	
			player attachFlag();		

		level.friendlyFlagStatusText[otherTeam] setPlayerNameString( player );
		level.friendlyFlagStatusText[otherTeam].glowColor = (0.75,0.25,0.25);
		level.friendlyFlagStatusText[otherTeam].glowAlpha = 1;
		
		level.enemyFlagStatusText[team] setPlayerNameString( player );
		level.enemyFlagStatusText[team].glowColor = (0.25,0.75,0.25);
		level.enemyFlagStatusText[team].glowAlpha = 1;

		self maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
		self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconKill2D );
		self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconKill3D );
		self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconEscort2D );
		self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconEscort3D );

		level.capZones[otherTeam] maps\mp\gametypes\_gameobjects::allowUse( "none" );
		level.capZones[otherTeam] maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
		//level.capZones[otherTeam] maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconKill3D );
		//level.capZones[otherTeam] maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconKill3D );

		if ( !level.teamFlags[ team ] maps\mp\gametypes\_gameobjects::isHome() )
		{
			level.capZones[ team ].trigger maps\mp\_entityheadIcons::setHeadIcon( player, level.iconWaitForFlag2D, (0,0,85), undefined, undefined, undefined, undefined, undefined, undefined, undefined, false );	
			
			if ( isDefined( level.teamFlags[ team ].carrier ) )
				level.capZones[ otherTeam ].trigger maps\mp\_entityheadIcons::setHeadIcon( level.teamFlags[ team ].carrier, level.iconWaitForFlag2D, (0,0,85), undefined, undefined, undefined, undefined, undefined, undefined, undefined, false );				
		}
		
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
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconReturnFlag2D );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconReturnFlag3D );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconCaptureFlag2D );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconCaptureFlag3D );

	level.friendlyFlagStatusText[team] setText( &"OBJECTIVES_FLAG_AWAY" );
	level.friendlyFlagStatusText[team].glowColor = (1,1,1);
	level.friendlyFlagStatusText[team].glowAlpha = 0;	
	level.enemyFlagStatusText[otherTeam] setText( &"OBJECTIVES_FLAG_AWAY" );
	level.enemyFlagStatusText[otherTeam].glowColor = (1,1,1);
	level.enemyFlagStatusText[otherTeam].glowAlpha = 0;	

	level.capZones[otherTeam].trigger maps\mp\_entityheadIcons::setHeadIcon( "none", "", (0,0,0) );

	if ( isDefined( player ) )
	{
 		if ( isDefined( player.carryFlag ) )
			player detachFlag();
		
		printAndSoundOnEveryone( otherTeam, "none", &"MP_ENEMY_FLAG_DROPPED_BY", "", "mp_war_objective_lost", "", player );		
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
	
	team = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	otherTeam = level.otherTeam[team];	
	playSoundOnPlayers( "mp_war_objective_taken", team );
	playSoundOnPlayers( "mp_war_objective_lost", otherTeam );	
	
	self maps\mp\gametypes\_gameobjects::returnHome();
}


onReset()
{
	team = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	otherTeam = level.otherTeam[team];

	self maps\mp\gametypes\_gameobjects::allowCarry( "enemy" );
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconKill2D );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconKill3D );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconEscort2D );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconEscort3D );

	level.friendlyFlagStatusText[team] setText( &"OBJECTIVES_FLAG_HOME" );
	level.friendlyFlagStatusText[team].glowColor = (1,1,1);
	level.friendlyFlagStatusText[team].glowAlpha = 0;	

	level.enemyFlagStatusText[otherTeam] setText( &"OBJECTIVES_FLAG_HOME" );
	level.enemyFlagStatusText[otherTeam].glowColor = (1,1,1);
	level.enemyFlagStatusText[otherTeam].glowAlpha = 0;	
	
	level.capZones[team] maps\mp\gametypes\_gameobjects::allowUse( "friendly" );
	level.capZones[team] maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	level.capZones[team] maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconDefendFlag2D );
	level.capZones[team] maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconDefendFlag3D );
	level.capZones[team] maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconCaptureFlag2D );
	level.capZones[team] maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconCaptureFlag3D );

	level.capZones[team].trigger maps\mp\_entityheadIcons::setHeadIcon( "none", "", (0,0,0) );
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
	maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( team, 1 );	
	player thread maps\mp\gametypes\_hud_message::SplashNotify( "flag_capture", maps\mp\gametypes\_rank::getScoreInfoValue( "capture" ) );
	maps\mp\gametypes\_gamescore::givePlayerScore( "capture", player );
	player thread [[level.onXPEvent]]( "capture" );
	player incPlayerStat( "flagscaptured", 1 );
	player notify( "objective", "captured" );
	player thread maps\mp\_matchdata::logGameEvent( "capture", player.origin );

	player incPersStat( "captures", 1 );
	player maps\mp\gametypes\_persistence::statSetChild( "round", "captures", player.pers["captures"] );

	printAndSoundOnEveryone( team, otherteam, &"MP_ENEMY_FLAG_CAPTURED_BY", &"MP_FLAG_CAPTURED_BY", "mp_obj_captured", "mp_enemy_obj_captured", player );

	if ( isDefined( player.carryFlag ) )
		player detachFlag();
	
	//	flag carrier class?  (do after detach flag)
	if ( isDefined( level.ctf_loadouts ) && isDefined( level.ctf_loadouts[team] ) )
		player thread removeFlagCarrierClass();

	level.teamFlags[otherTeam]	returnFlag();
	
	level thread checkRoundWin( team );
}


checkRoundWin( team )
{
	if ( inOvertime() )
	{
		game["roundsWon"][team]++;
		level.finalKillCam_winner = team;
		game["teamScores"]["axis"] = game["roundsWon"]["axis"];
		game["teamScores"]["allies"] = game["roundsWon"]["allies"];	
		setTeamScore( "axis", game["teamScores"]["axis"] );
		setTeamScore( "allies", game["teamScores"]["allies"] );		
		thread maps\mp\gametypes\_gamelogic::endGame( team, game["strings"]["score_limit_reached"] );
	}	
	else if ( game["switchedsides"] )
	{
		if ( game["teamScores"][team] == getWatchedDvar( "scorelimit" ) )
		{
			game["roundsWon"][team]++;
			game["teamScores"]["axis"] = game["roundsWon"]["axis"];
			game["teamScores"]["allies"] = game["roundsWon"]["allies"];	
			setTeamScore( "axis", game["teamScores"]["axis"] );
			setTeamScore( "allies", game["teamScores"]["allies"] );				
			
			if ( game["roundsWon"][team] > game["roundsWon"][level.otherTeam[team]] )
			{				
				level.finalKillCam_winner = team;							
				thread maps\mp\gametypes\_gamelogic::endGame( team, game["strings"]["score_limit_reached"] );
			}
			else  
			{				
				//	tie, go into overtime	
				level.finalKillCam_winner = "none";				
				thread maps\mp\gametypes\_gamelogic::endGame( "overtime", game["strings"]["score_limit_reached"] );
			}
		}
	}
	else
	{
		if ( game["teamScores"][team] == getWatchedDvar( "scorelimit" ) )
		{
			game["roundsWon"][team]++;				
			level.finalKillCam_winner = team;
			game["teamScores"]["axis"] = game["roundsWon"]["axis"];
			game["teamScores"]["allies"] = game["roundsWon"]["allies"];
			setTeamScore( "axis", game["teamScores"]["axis"] );
			setTeamScore( "allies", game["teamScores"]["allies"] );								
			thread maps\mp\gametypes\_gamelogic::endGame( "halftime", game["strings"]["score_limit_reached"] );	
		}	
	}
}


onTimeLimit()
{
	if ( inOvertime() )
	{
		game["teamScores"]["axis"] = game["roundsWon"]["axis"];
		game["teamScores"]["allies"] = game["roundsWon"]["allies"];	
		setTeamScore( "axis", game["teamScores"]["axis"] );
		setTeamScore( "allies", game["teamScores"]["allies"] );				
		level.finalKillCam_winner = "none";
		thread maps\mp\gametypes\_gamelogic::endGame( "tie", game["strings"]["time_limit_reached"] );
	}	
	else if ( game["switchedsides"] )
	{
		//	whoever is winning wins the round
		if ( game["teamScores"]["axis"] > game["teamScores"]["allies"] )
			game["roundsWon"]["axis"]++;
		else if ( game["teamScores"]["allies"] > game["teamScores"]["axis"] )
			game["roundsWon"]["allies"]++;	
			
		game["teamScores"]["axis"] = game["roundsWon"]["axis"];
		game["teamScores"]["allies"] = game["roundsWon"]["allies"];		
		setTeamScore( "axis", game["teamScores"]["axis"] );
		setTeamScore( "allies", game["teamScores"]["allies"] );
		
		if ( game["roundsWon"]["axis"] > game["roundsWon"]["allies"] )
		{
			//	win game
			level.finalKillCam_winner = "axis";
			thread maps\mp\gametypes\_gamelogic::endGame( "axis", game["strings"]["time_limit_reached"] );
			return;
		}
		else if ( game["roundsWon"]["allies"] > game["roundsWon"]["axis"] )	
		{
			//	win game
			level.finalKillCam_winner = "allies";
			thread maps\mp\gametypes\_gamelogic::endGame( "allies", game["strings"]["time_limit_reached"] );
			return;
		}
		else
		{
			//	tie, go into overtime
			level.finalKillCam_winner = "none";
			thread maps\mp\gametypes\_gamelogic::endGame( "overtime", game["strings"]["time_limit_reached"] );			
		}					
	}
	else
	{
		//	whoever is winning wins the round, tie goes to neither, endgame( "overtime" ) doesn't touch rounds won so update them
		if ( game["teamScores"]["axis"] > game["teamScores"]["allies"] )
		{
			game["roundsWon"]["axis"]++;
			level.finalKillCam_winner = "axis";
		}
		else if ( game["teamScores"]["allies"] > game["teamScores"]["axis"] )
		{			
			game["roundsWon"]["allies"]++;
			level.finalKillCam_winner = "allies";
		}
		else
		{		
			level.finalKillCam_winner = "none";
		}		
		game["teamScores"]["axis"] = game["roundsWon"]["axis"];
		game["teamScores"]["allies"] = game["roundsWon"]["allies"];
		setTeamScore( "axis", game["teamScores"]["axis"] );
		setTeamScore( "allies", game["teamScores"]["allies"] );
		thread maps\mp\gametypes\_gamelogic::endGame( "halftime", game["strings"]["time_limit_reached"] );				
	}		
}


applyFlagCarrierClass()
{
	self endon( "death" );
	self endon( "disconnect" );
	level endon( "game_ended" );
	
	if ( self isJuggernaut() )
	{
		self notify( "lost_juggernaut" );
		wait( 0.05 );
	}	
	
	self.pers["gamemodeLoadout"] = level.ctf_loadouts[self.team];
	self maps\mp\gametypes\_class::giveLoadout( self.team, "gamemode", false, false );	
	
	self attachFlag();	
}


removeFlagCarrierClass()
{
	self endon( "death" );
	self endon( "disconnect" );
	level endon( "game_ended" );
	
	if ( self isJuggernaut() )
	{
		self notify( "lost_juggernaut" );
		wait( 0.05 );
	}	
	
	self.pers["gamemodeLoadout"] = undefined;
	self maps\mp\gametypes\_class::giveLoadout( self.team, self.class, undefined, false );	
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
			attacker thread [[level.onXPEvent]]( "kill_carrier" );
			maps\mp\gametypes\_gamescore::givePlayerScore( "kill_carrier", attacker );
			attacker incPlayerStat( "flagcarrierkills", 1 );
			
			attacker incPersStat( "defends", 1 );
			attacker maps\mp\gametypes\_persistence::statSetChild( "round", "defends", attacker.pers["defends"] );
			
			thread maps\mp\_matchdata::logKillEvent( killId, "carrying" );
			
			self detachFlag();
		}
	}
}


attachFlag()
{
	otherTeam = level.otherTeam[self.pers["team"]];
	
	self attach( level.carryFlag[otherTeam], "J_spine4", true );
	self.carryFlag = level.carryFlag[otherTeam];
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


setSpecialLoadouts()
{
	if ( isUsingMatchRulesData() && GetMatchRulesData( "defaultClasses", "axis", 5, "class", "inUse" ) )
	{
		level.ctf_loadouts["axis"] = getMatchRulesSpecialClass( "axis", 5 );	
	}
	if ( isUsingMatchRulesData() && GetMatchRulesData( "defaultClasses", "allies", 5, "class", "inUse" ) )
	{
		level.ctf_loadouts["allies"] = getMatchRulesSpecialClass( "allies", 5 );	
	}	
}