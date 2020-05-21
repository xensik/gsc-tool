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

	registerTimeLimitDvar( level.gameType, 3, 0, 1440 );
	registerScoreLimitDvar( level.gameType, 1, 0, 10000 );
	registerRoundLimitDvar( level.gameType, 0, 0, 30 );
	registerWinLimitDvar( level.gameType, 4, 0, 10 );
	registerRoundSwitchDvar( level.gameType, 3, 0, 30 );
	registerNumLivesDvar( level.gameType, 0, 0, 10 );
	registerHalfTimeDvar( level.gameType, 0, 0, 1 );
	
	level.objectiveBased = true;
	level.teamBased = true;
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onSpawnPlayer = ::onSpawnPlayer;
	level.onPlayerKilled = ::onPlayerKilled;
	level.onTimeLimit = ::onTimeLimit;
	level.initGametypeAwards = ::initGametypeAwards;

	game["dialog"]["gametype"] = "oneflag";

	if ( getDvarInt( "g_hardcore" ) )
		game["dialog"]["gametype"] = "hc_" + game["dialog"]["gametype"];
	else if ( getDvarInt( "camera_thirdPerson" ) )
		game["dialog"]["gametype"] = "thirdp_" + game["dialog"]["gametype"];
	else if ( getDvarInt( "scr_diehard" ) )
		game["dialog"]["gametype"] = "dh_" + game["dialog"]["gametype"];
	else if (getDvarInt( "scr_" + level.gameType + "_promode" ) )
		game["dialog"]["gametype"] = game["dialog"]["gametype"] + "_pro";

	if ( getdvar("scr_oneflag_returntime") == "" )
		setdvar("scr_oneflag_returntime", "15");
	level.flagReturnTime = getdvarint( "scr_oneflag_returntime" );
}

onPrecacheGameType()
{
	precacheString(&"MP_FLAG_TAKEN_BY");
	precacheString(&"MP_ENEMY_FLAG_TAKEN_BY");
	precacheString(&"MP_FLAG_CAPTURED_BY");
	precacheString(&"MP_ENEMY_FLAG_CAPTURED_BY");
	//precacheString(&"MP_FLAG_RETURNED_BY");
	precacheString(&"MP_FLAG_RETURNED");
	precacheString(&"MP_ENEMY_FLAG_RETURNED");
	precacheString(&"MP_YOUR_FLAG_RETURNING_IN");
	precacheString(&"MP_ENEMY_FLAG_RETURNING_IN");
	precacheString(&"MP_ENEMY_FLAG_DROPPED_BY");
	precacheString( &"MP_DOM_NEUTRAL_FLAG_CAPTURED" );
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
	
	setObjectiveText( game["attackers"], &"OBJECTIVES_CTF" );
	setObjectiveText( game["defenders"], &"OBJECTIVES_CTF" );

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
	
	allowed[0] = "ctf";
	maps\mp\gametypes\_gameobjects::main(allowed);
	
	maps\mp\gametypes\_rank::registerScoreInfo( "kill", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "headshot", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assist", 20 );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "pickup", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "return", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "capture", 500 );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "kill_carrier", 100 );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "defend", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "defend_assist", 100 );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "assault", 200 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assault_assist", 40 );
	
	thread oneflag_ctf();
}


getSpawnPoint()
{
	spawnteam = self.pers["team"];
	if ( game["switchedsides"] )
		spawnteam = getOtherTeam( spawnteam );
	
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


onSpawnPlayer()
{
	self.usingObj = undefined;
}


oneflag_ctf()
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
	
	level.iconCapture3D = "waypoint_capture";
	level.iconCapture2D = "compass_waypoint_capture";
	level.iconDefend3D = "waypoint_defend";
	level.iconDefend2D = "compass_waypoint_defend";
	level.iconTarget3D = "waypoint_target";
	level.iconTarget2D = "compass_waypoint_target";
	
	precacheShader( level.icon2D["axis"] );
	precacheShader( level.icon2D["allies"] );

	precacheShader( level.iconCapture3D );
	precacheShader( level.iconDefend3D );

	precacheShader( level.iconCapture2D );
	precacheShader( level.iconDefend2D );

	precacheShader( level.iconTarget3D );
	precacheShader( level.iconTarget2D );

	precacheShader( "waypoint_kill" );
	
	level.teamFlags[game["defenders"]] = createTeamFlag( game["defenders"] );
	level.capZones[game["attackers"]] = createCapZone( game["attackers"] );
	level.flagCaptured = false;
}


spawnFxDelay( fxid, pos, forward, right, delay )
{
	wait delay;
	effect = spawnFx( fxid, pos, forward, right );
	triggerFx( effect );
}

createTeamFlag( team )
{
	entityTeam = game["original_defenders"];

	trigger = getEnt( "ctf_trig_" + entityTeam, "targetname" );
	if ( !isDefined( trigger ) ) 
	{
		error( "No ctf_trig_" + entityTeam + " trigger found in map." );
		return;
	}
	visuals[0] = getEnt( "ctf_flag_" + entityTeam, "targetname" );
	if ( !isDefined( visuals[0] ) ) 
	{
		error( "No ctf_flag_" + entityTeam + " script_model found in map." );
		return;
	}
	
	cloneTrigger = spawn( "trigger_radius", trigger.origin, 0, 96, trigger.height );
	trigger delete();
	trigger = cloneTrigger;
	
	visuals[0] setModel( level.flagModel[team] );
	
	teamFlag = maps\mp\gametypes\_gameobjects::createCarryObject( team, trigger, visuals, (0,0,85) );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseTime( "friendly", 15.0 );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseTime( "enemy", 0 );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseText( "enemy", &"MP_CAPTURING_FLAG" );
	teamFlag maps\mp\gametypes\_gameobjects::setTeamUseText( "friendly", &"MP_RETURNING_FLAG" );

	teamFlag maps\mp\gametypes\_gameobjects::allowCarry( "enemy" );
	teamFlag maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	teamFlag maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconDefend2D );
	teamFlag maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconDefend3D );
	teamFlag maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", level.iconCapture2D );
	teamFlag maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", level.iconCapture3D );
	teamFlag maps\mp\gametypes\_gameobjects::setCarryIcon( level.icon2D[team] );
	teamFlag.allowWeapons = true;
	teamFlag.onPickup = ::onPickup;
	teamFlag.onPickupFailed = ::onPickup;
	teamFlag.onDrop = ::onDrop;
	teamFlag.onReset = ::onReset;
	//teamFlag.onBeginUse = ::onBeginUse;	
	//teamFlag.onEndUse = ::onEndUse;
	
	teamFlag.oldRadius = trigger.radius;

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

createCapZone( team )
{
	entityTeam = level.otherTeam[game["original_defenders"]];

	trigger = getEnt( "ctf_zone_" + entityTeam, "targetname" );
	if ( !isDefined( trigger ) ) 
	{
		error("No ctf_zone_" + entityTeam + " trigger found in map.");
		return;
	}

	visuals[0] = getEnt( "ctf_flag_" + entityTeam, "targetname" );
	if ( !isDefined( visuals[0] ) ) 
	{
		error( "No ctf_flag_" + entityTeam + " script_model found in map." );
		return;
	}

	visuals[0] hide();
	
	visuals = [];
	capZone = maps\mp\gametypes\_gameobjects::createUseObject( team, trigger, visuals, (0,0,85) );
	capZone maps\mp\gametypes\_gameobjects::allowUse( "friendly" );
	capZone maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	capZone maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconTarget2D );
	capZone maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconTarget3D );

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
	team = player.pers["team"];

	if ( team == "allies" )
		otherTeam = "axis";
	else
		otherTeam = "allies";


	if ( team == self maps\mp\gametypes\_gameobjects::getOwnerTeam() )
	{
		player thread maps\mp\gametypes\_hud_message::SplashNotify( "flagreturn", maps\mp\gametypes\_rank::getScoreInfoValue( "pickup" ) );
		player thread [[level.onXPEvent]]( "pickup" );
		self thread returnFlag();
		player incPlayerStat( "flagsreturned", 1 );
		player thread maps\mp\_matchdata::logGameEvent( "return", player.origin );
	}
	else
	{
		player attachFlag();

		level.capZones[team] maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );

		//self maps\mp\gametypes\_gameobjects::setVisibleTeam( "enemy" );
		self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_defend" );
		self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_kill" );
		self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconTarget2D );

		printAndSoundOnEveryone( team, otherteam, &"MP_ENEMY_FLAG_TAKEN_BY", &"MP_FLAG_TAKEN_BY", "mp_obj_taken", "mp_enemy_obj_taken", player );

		leaderDialog( "enemy_flag_taken", team, "status" );
		leaderDialog( "flag_taken", otherteam, "status" );

		player thread maps\mp\gametypes\_hud_message::SplashNotify( "flagpickup", maps\mp\gametypes\_rank::getScoreInfoValue( "pickup" ) );
		maps\mp\gametypes\_gamescore::givePlayerScore( "pickup", player );
		player thread [[level.onXPEvent]]( "pickup" );
		player incPlayerStat( "flagscarried", 1 );
		player thread maps\mp\_matchdata::logGameEvent( "pickup", player.origin );
	}
}


returnFlag()
{
	team = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	otherTeam = level.otherTeam[team];
	
	self maps\mp\gametypes\_gameobjects::returnHome();
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	self maps\mp\gametypes\_gameobjects::allowCarry( "enemy" );

	level.capZones[otherTeam] maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	
	printAndSoundOnEveryone( team, getOtherTeam( team ), &"MP_FLAG_RETURNED", &"MP_ENEMY_FLAG_RETURNED", "mp_obj_returned", "mp_obj_returned", "" );
	leaderDialog( "enemy_flag_returned", otherteam, "status" );
	leaderDialog( "flag_returned", team, "status" );	
}


onDrop( player )
{
	team = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	otherTeam = level.otherTeam[team];
	
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconDefend3D );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconDefend2D );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy",    level.iconCapture3D );
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	self maps\mp\gametypes\_gameobjects::allowCarry( "any" );

	level.capZones[otherTeam] maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	
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
}


onReset()
{
	self notify ( "flag_reset" );

	team = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	otherTeam = level.otherTeam[team];
	
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", level.iconDefend3D );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", level.iconDefend2D );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy",    level.iconCapture3D );

	level.capZones[otherTeam] maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
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

	maps\mp\gametypes\_gamescore::givePlayerScore( "capture", player );
	player thread [[level.onXPEvent]]( "capture" );
	player incPlayerStat( "flagscaptured", 1 );
	player notify( "objective", "captured" );
	player thread maps\mp\_matchdata::logGameEvent( "capture", player.origin );

	// round win here, no reset necessary

	printAndSoundOnEveryone( team, otherteam, &"MP_ENEMY_FLAG_CAPTURED_BY", &"MP_FLAG_CAPTURED_BY", "mp_obj_captured", "mp_enemy_obj_captured", player );

	thread flagCaptured( team, &"MP_DOM_NEUTRAL_FLAG_CAPTURED" );

	level.teamFlags[otherTeam] maps\mp\gametypes\_gameobjects::allowCarry( "none" );
	level.teamFlags[otherTeam] maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	level.teamFlags[otherTeam] maps\mp\gametypes\_gameobjects::disableObject();
	level.capZones[team] maps\mp\gametypes\_gameobjects::allowUse( "none" );

	if ( isDefined( player.carryFlag ) )
		player detachFlag();
}


flagCaptured( winningTeam, endReasonText )
{
	maps\mp\gametypes\_gamelogic::endGame( winningTeam, endReasonText );
	level.flagCaptured = true;
}


onTimeLimit()
{
	if ( level.flagCaptured )
		return; 

	// TODO: change to "Flag Defended" or some such
	maps\mp\gametypes\_gamelogic::endGame( game["defenders"], game["strings"]["time_limit_reached"] );
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