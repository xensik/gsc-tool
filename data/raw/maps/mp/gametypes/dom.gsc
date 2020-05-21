#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
/*
	Domination
	Objective: 	Capture all the flags by touching them
	Map ends:	When one team captures all the flags, or time limit is reached
	Respawning:	No wait / Near teammates

	Level requirements
	------------------
		Spawnpoints:
			classname		mp_tdm_spawn
			All players spawn from these. The spawnpoint chosen is dependent on the current locations of owned flags, teammates and 
			enemies at the time of spawn. Players generally spawn behind their teammates relative to the direction of enemies.
			Optionally, give a spawnpoint a script_linkto to specify which flag it "belongs" to (see Flag Descriptors).

		Spectator Spawnpoints:
			classname		mp_global_intermission
			Spectators spawn from these and intermission is viewed from these positions.
			Atleast one is required, any more and they are randomly chosen between.

		Flags:
			classname       trigger_radius
			targetname      flag_primary or flag_secondary
			Flags that need to be captured to win. Primary flags take time to capture; secondary flags are instant.
		
		Flag Descriptors:
			classname       script_origin
			targetname      flag_descriptor
			Place one flag descriptor close to each flag. Use the script_linkname and script_linkto properties to say which flags
			it can be considered "adjacent" to in the level. For instance, if players have a primary path from flag1 to flag2, and 
			from flag2 to flag3, flag2 would have a flag_descriptor with these properties:
			script_linkname flag2
			script_linkto flag1 flag3
			
			Set scr_domdebug to 1 to see flag connections and what spawnpoints are considered connected to each flag.
*/

/*QUAKED mp_dom_spawn (0.5 0.5 1.0) (-16 -16 0) (16 16 72)
Players spawn near their flags at one of these positions.*/

/*QUAKED mp_dom_spawn_axis_start (1.0 0.0 1.0) (-16 -16 0) (16 16 72)
Axis players spawn away from enemies and near their team at one of these positions at the start of a round.*/

/*QUAKED mp_dom_spawn_allies_start (0.0 1.0 1.0) (-16 -16 0) (16 16 72)
Allied players spawn away from enemies and near their team at one of these positions at the start of a round.*/


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
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onPlayerKilled = ::onPlayerKilled;
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.initGametypeAwards = ::initGametypeAwards;
	level.onSpawnPlayer = ::onSpawnPlayer;
	
	if ( level.matchRules_damageMultiplier || level.matchRules_vampirism )
		level.modifyPlayerDamage = maps\mp\gametypes\_damage::gamemodeModifyPlayerDamage;
	
	game["dialog"]["gametype"] = "domination";

	if ( getDvarInt( "g_hardcore" ) )
		game["dialog"]["gametype"] = "hc_" + game["dialog"]["gametype"];
	else if ( getDvarInt( "camera_thirdPerson" ) )
		game["dialog"]["gametype"] = "thirdp_" + game["dialog"]["gametype"];
	else if ( getDvarInt( "scr_diehard" ) )
		game["dialog"]["gametype"] = "dh_" + game["dialog"]["gametype"];
	else if (getDvarInt( "scr_" + level.gameType + "_promode" ) )
		game["dialog"]["gametype"] = game["dialog"]["gametype"] + "_pro";

	game["dialog"]["offense_obj"] = "capture_objs";
	game["dialog"]["defense_obj"] = "capture_objs";
}


initializeMatchRules()
{
	assert( isUsingMatchRulesData() );

	//	set common values
	setCommonRulesFromMatchRulesData();

	//	set everything else (private match options, default .cfg file values, and what normally is registered in the 'else' below)
	SetDynamicDvar( "scr_dom_roundlimit", 1 );
	registerRoundLimitDvar( "dom", 1 );		
	SetDynamicDvar( "scr_dom_winlimit", 1 );
	registerWinLimitDvar( "dom", 1 );			
	SetDynamicDvar( "scr_dom_halftime", 0 );
	registerHalfTimeDvar( "dom", 0 );				

	SetDynamicDvar( "scr_dom_promode", 0 );
}


onPrecacheGameType()
{
	precacheShader( "waypoint_captureneutral" );
	precacheShader( "waypoint_capture" );
	precacheShader( "waypoint_defend" );
	precacheShader( "waypoint_captureneutral_a" );
	precacheShader( "waypoint_capture_a" );
	precacheShader( "waypoint_defend_a" );
	precacheShader( "waypoint_captureneutral_b" );
	precacheShader( "waypoint_capture_b" );
	precacheShader( "waypoint_defend_b" );
	precacheShader( "waypoint_captureneutral_c" );
	precacheShader( "waypoint_capture_c" );
	precacheShader( "waypoint_defend_c" );

	precacheShader( "waypoint_captureneutral" );
	precacheShader( "waypoint_capture" );
	precacheShader( "waypoint_defend" );
	precacheShader( "waypoint_captureneutral_a" );
	precacheShader( "waypoint_capture_a" );
	precacheShader( "waypoint_defend_a" );
	precacheShader( "waypoint_captureneutral_b" );
	precacheShader( "waypoint_capture_b" );
	precacheShader( "waypoint_defend_b" );
	precacheShader( "waypoint_captureneutral_c" );
	precacheShader( "waypoint_capture_c" );
	precacheShader( "waypoint_defend_c" );
}


onStartGameType()
{	
	setObjectiveText( "allies", &"OBJECTIVES_DOM" );
	setObjectiveText( "axis", &"OBJECTIVES_DOM" );

	if ( level.splitscreen )
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_DOM" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_DOM" );
	}
	else
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_DOM_SCORE" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_DOM_SCORE" );
	}
	setObjectiveHintText( "allies", &"OBJECTIVES_DOM_HINT" );
	setObjectiveHintText( "axis", &"OBJECTIVES_DOM_HINT" );

	setClientNameMode("auto_change");

	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_dom_spawn_allies_start" );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_dom_spawn_axis_start" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_dom_spawn" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_dom_spawn" );
	
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );
	
	level.spawn_all = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dom_spawn" );
	level.spawn_axis_start = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dom_spawn_axis_start" );
	level.spawn_allies_start = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dom_spawn_allies_start" );
	
	level.startPos["allies"] = level.spawn_allies_start[0].origin;
	level.startPos["axis"] = level.spawn_axis_start[0].origin;
	
	level.flagBaseFXid[ "allies" ] = loadfx( maps\mp\gametypes\_teams::getTeamFlagFX( "allies" ) );
	level.flagBaseFXid[ "axis"   ] = loadfx( maps\mp\gametypes\_teams::getTeamFlagFX( "axis" ) );
	
	allowed[0] = "dom";
//	allowed[1] = "hardpoint";
	maps\mp\gametypes\_gameobjects::main(allowed);

	maps\mp\gametypes\_rank::registerScoreInfo( "kill", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "headshot", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assist", 10 );

	maps\mp\gametypes\_rank::registerScoreInfo( "capture", 150 );

	maps\mp\gametypes\_rank::registerScoreInfo( "defend", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "defend_assist", 10 );

	maps\mp\gametypes\_rank::registerScoreInfo( "assault", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assault_assist", 10 );
		
	thread domFlags();
	thread updateDomScores();	
}


getSpawnPoint()
{
	spawnpoint = undefined;
	
	if ( !level.useStartSpawns )
	{
		flagsOwned = 0;
		enemyFlagsOwned = 0;
		myTeam = self.pers["team"];
		enemyTeam = getOtherTeam( myTeam );
		for ( i = 0; i < level.flags.size; i++ )
		{
			team = level.flags[i] getFlagTeam();
			if ( team == myTeam )
				flagsOwned++;
			else if ( team == enemyTeam )
				enemyFlagsOwned++;
		}
		
		if ( flagsOwned == level.flags.size )
		{
			// own all flags! pretend we don't own the last one we got, so enemies can spawn there
			enemyBestSpawnFlag = level.bestSpawnFlag[ getOtherTeam( self.pers["team"] ) ];
			
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( level.spawn_all, getSpawnsBoundingFlag( enemyBestSpawnFlag ) );
		}
		else if ( flagsOwned > 0 )
		{
			// spawn near any flag we own that's nearish something we can capture
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( level.spawn_all, getBoundaryFlagSpawns( myTeam ) );
		}
		else
		{
			// own no flags!
			bestFlag = undefined;
			if ( enemyFlagsOwned > 0 && enemyFlagsOwned < level.flags.size )
			{
				// there should be an unowned one to use
				bestFlag = getUnownedFlagNearestStart( myTeam );
			}
			if ( !isdefined( bestFlag ) )
			{
				// pretend we still own the last one we lost
				bestFlag = level.bestSpawnFlag[ self.pers["team"] ];
			}
			level.bestSpawnFlag[ self.pers["team"] ] = bestFlag;
			
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( level.spawn_all, bestFlag.nearbyspawns );
		}
	}
	
	if ( !isdefined( spawnpoint ) )
	{
		if (self.pers["team"] == "axis")
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random(level.spawn_axis_start);
		else
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random(level.spawn_allies_start);
	}
	
	//spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( level.spawn_all );
	
	assert( isDefined(spawnpoint) );
	
	return spawnpoint;
}


domFlags()
{
	level.lastStatus["allies"] = 0;
	level.lastStatus["axis"] = 0;
	
	game["flagmodels"] = [];
	game["flagmodels"]["neutral"] = "prop_flag_neutral";

	game["flagmodels"]["allies"] = maps\mp\gametypes\_teams::getTeamFlagModel( "allies" );
	game["flagmodels"]["axis"] = maps\mp\gametypes\_teams::getTeamFlagModel( "axis" );
	
	precacheModel( game["flagmodels"]["neutral"] );
	precacheModel( game["flagmodels"]["allies"] );
	precacheModel( game["flagmodels"]["axis"] );
	
	precacheString( &"MP_SECURING_POSITION" );	
	
	primaryFlags = getEntArray( "flag_primary", "targetname" );
	secondaryFlags = getEntArray( "flag_secondary", "targetname" );
	
	if ( (primaryFlags.size + secondaryFlags.size) < 2 )
	{
		printLn( "^1Not enough domination flags found in level!" );
		maps\mp\gametypes\_callbacksetup::AbortLevel();
		return;
	}
	
	level.flags = [];
	for ( index = 0; index < primaryFlags.size; index++ )
		level.flags[level.flags.size] = primaryFlags[index];
	
	for ( index = 0; index < secondaryFlags.size; index++ )
		level.flags[level.flags.size] = secondaryFlags[index];
	
	level.domFlags = [];
	for ( index = 0; index < level.flags.size; index++ )
	{
		trigger = level.flags[index];
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

		domFlag = maps\mp\gametypes\_gameobjects::createUseObject( "neutral", trigger, visuals, (0,0,100) );
		domFlag maps\mp\gametypes\_gameobjects::allowUse( "enemy" );
		domFlag maps\mp\gametypes\_gameobjects::setUseTime( 10.0 );
		domFlag maps\mp\gametypes\_gameobjects::setUseText( &"MP_SECURING_POSITION" );
		label = domFlag maps\mp\gametypes\_gameobjects::getLabel();
		domFlag.label = label;
		domFlag maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_defend" + label );
		domFlag maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_defend" + label );
		domFlag maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_captureneutral" + label );
		domFlag maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_captureneutral" + label );
		domFlag maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
		domFlag.onUse = ::onUse;
		domFlag.onBeginUse = ::onBeginUse;
		domFlag.onUseUpdate = ::onUseUpdate;
		domFlag.onEndUse = ::onEndUse;
		
		
		traceStart = visuals[0].origin + (0,0,32);
		traceEnd = visuals[0].origin + (0,0,-32);
		trace = bulletTrace( traceStart, traceEnd, false, undefined );
	
		upangles = vectorToAngles( trace["normal"] );
		domFlag.baseeffectforward = anglesToForward( upangles );
		domFlag.baseeffectright = anglesToRight( upangles );
		
		domFlag.baseeffectpos = trace["position"];
		
		// legacy spawn code support
		level.flags[index].useObj = domFlag;
		level.flags[index].adjflags = [];
		level.flags[index].nearbyspawns = [];
		
		domFlag.levelFlag = level.flags[index];
		
		level.domFlags[level.domFlags.size] = domFlag;
	}
	
	// level.bestSpawnFlag is used as a last resort when the enemy holds all flags.
	level.bestSpawnFlag = [];
	level.bestSpawnFlag[ "allies" ] = getUnownedFlagNearestStart( "allies", undefined );
	level.bestSpawnFlag[ "axis" ] = getUnownedFlagNearestStart( "axis", level.bestSpawnFlag[ "allies" ] );
	
	flagSetup();
	
	/#
	thread domDebug();
	#/
}

getUnownedFlagNearestStart( team, excludeFlag )
{
	best = undefined;
	bestdistsq = undefined;
	for ( i = 0; i < level.flags.size; i++ )
	{
		flag = level.flags[i];
		
		if ( flag getFlagTeam() != "neutral" )
			continue;
		
		distsq = distanceSquared( flag.origin, level.startPos[team] );
		if ( (!isDefined( excludeFlag ) || flag != excludeFlag) && (!isdefined( best ) || distsq < bestdistsq) )
		{
			bestdistsq = distsq;
			best = flag;
		}
	}
	return best;
}

/#
domDebug()
{
	while(1)
	{
		if (getdvar("scr_domdebug") != "1") {
			wait 2;
			continue;
		}
		
		while(1)
		{
			if (getdvar("scr_domdebug") != "1")
				break;
			// show flag connections and each flag's spawnpoints
			for (i = 0; i < level.flags.size; i++) {
				for (j = 0; j < level.flags[i].adjflags.size; j++) {
					line(level.flags[i].origin, level.flags[i].adjflags[j].origin, (1,1,1));
				}
				
				for (j = 0; j < level.flags[i].nearbyspawns.size; j++) {
					line(level.flags[i].origin, level.flags[i].nearbyspawns[j].origin, (.2,.2,.6));
				}
				
				if ( level.flags[i] == level.bestSpawnFlag["allies"] )
					print3d( level.flags[i].origin, "allies best spawn flag" );
				if ( level.flags[i] == level.bestSpawnFlag["axis"] )
					print3d( level.flags[i].origin, "axis best spawn flag" );
			}
			wait .05;
		}
	}
}
#/

onBeginUse( player )
{
	ownerTeam = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	self.didStatusNotify = false;

	if ( ownerTeam == "neutral" )
	{
		statusDialog( "securing"+self.label, player.pers["team"] );
		self.objPoints[player.pers["team"]] thread maps\mp\gametypes\_objpoints::startFlashing();
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
		ownerTeam = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
		if ( ownerTeam == "neutral" )
		{
			statusDialog( "securing"+self.label, team );
		}
		else
		{
			statusDialog( "losing"+self.label, ownerTeam );
			statusDialog( "securing"+self.label, team );
		}

		self.didStatusNotify = true;
	}
}


statusDialog( dialog, team, forceDialog )
{
	time = getTime();
	
	if ( getTime() < level.lastStatus[team] + 5000 && (!isDefined( forceDialog ) || !forceDialog) )
		return;
		
	thread delayedLeaderDialog( dialog, team );
	level.lastStatus[team] = getTime();	
}


onEndUse( team, player, success )
{
	self.objPoints["allies"] thread maps\mp\gametypes\_objpoints::stopFlashing();
	self.objPoints["axis"] thread maps\mp\gametypes\_objpoints::stopFlashing();
}


resetFlagBaseEffect()
{
	if ( isdefined( self.baseeffect ) )
		self.baseeffect delete();
	
	team = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	
	if ( team != "axis" && team != "allies" )
		return;
	
	fxid = level.flagBaseFXid[ team ];

	self.baseeffect = spawnFx( fxid, self.baseeffectpos, self.baseeffectforward, self.baseeffectright );
	triggerFx( self.baseeffect );
}

onUse( player )
{
	team = player.pers["team"];
	oldTeam = self maps\mp\gametypes\_gameobjects::getOwnerTeam();
	label = self maps\mp\gametypes\_gameobjects::getLabel();
	
	//player logString( "flag captured: " + self.label );
	
	self.captureTime = getTime();
	
	self maps\mp\gametypes\_gameobjects::setOwnerTeam( team );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_capture" + label );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_capture" + label );
	self.visuals[0] setModel( game["flagmodels"][team] );
	
	self resetFlagBaseEffect();
	
	level.useStartSpawns = false;
	
	assert( team != "neutral" );
	
	if ( oldTeam == "neutral" )
	{
		otherTeam = getOtherTeam( team );
		thread printAndSoundOnEveryone( team, otherTeam, undefined, undefined, "mp_war_objective_taken", undefined, player );
		
		statusDialog( "secured"+self.label, team, true );
		statusDialog( "enemy_has"+self.label, otherTeam, true );
	}
	else
	{
		thread printAndSoundOnEveryone( team, oldTeam, undefined, undefined, "mp_war_objective_taken", "mp_war_objective_lost", player );
		
//		thread delayedLeaderDialogBothTeams( "obj_lost", oldTeam, "obj_taken", team );

		if ( getTeamFlagCount( team ) == level.flags.size )
		{
			statusDialog( "secure_all", team );
			statusDialog( "lost_all", oldTeam );
		}
		else
		{	
			statusDialog( "secured"+self.label, team, true );
			statusDialog( "lost"+self.label, oldTeam, true );
		}
		
		level.bestSpawnFlag[ oldTeam ] = self.levelFlag;
	}
	
	player notify( "objective", "captured" );
	self thread giveFlagCaptureXP( self.touchList[team] );
}

giveFlagCaptureXP( touchList )
{
	level endon ( "game_ended" );
	
	players = getArrayKeys( touchList );
	for ( index = 0; index < players.size; index++ )
	{
		player = touchList[players[index]].player;
		player thread maps\mp\gametypes\_hud_message::SplashNotify( "capture", maps\mp\gametypes\_rank::getScoreInfoValue( "capture" ) );
		player thread updateCPM();
		player thread maps\mp\gametypes\_rank::giveRankXP( "capture", maps\mp\gametypes\_rank::getScoreInfoValue( "capture" ) * player getCapXPScale() );
		printLn( maps\mp\gametypes\_rank::getScoreInfoValue( "capture" ) * player getCapXPScale() );
		maps\mp\gametypes\_gamescore::givePlayerScore( "capture", player );
		
		player incPlayerStat( "pointscaptured", 1 );
		player incPersStat( "captures", 1 );
		player maps\mp\gametypes\_persistence::statSetChild( "round", "captures", player.pers["captures"] );
		
		if ( player != self )
			player notify( "objective", "assistedCapture" );
	}
	
	player = self maps\mp\gametypes\_gameobjects::getEarliestClaimPlayer();

	level thread teamPlayerCardSplash( "callout_securedposition" + self.label, player );

	player thread maps\mp\_matchdata::logGameEvent( "capture", player.origin );	
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


updateDomScores()
{
	level endon ( "game_ended" );
	
	while ( !level.gameEnded )
	{
		domFlags = getOwnedDomFlags();
		
		if ( domFlags.size )
		{
			for ( i = 1; i < domFlags.size; i++ )
			{
				domFlag = domFlags[i];
				flagScore = getTime() - domFlag.captureTime;
				for ( j = i - 1; j >= 0 && flagScore > (getTime() - domFlags[j].captureTime); j-- )
					domFlags[j + 1] = domFlags[j];
				domFlags[j + 1] = domFlag;
			}
			
			foreach( domFlag in domFlags )
			{
				team = domFlag maps\mp\gametypes\_gameobjects::getOwnerTeam();
				assert( team == "allies" || team == "axis" );
				maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( team, 1 );	
			}
		}
		
		// end the game if people aren't playing
		if ( (((getTimePassed() / 1000) > 120 && domFlags.size < 2) || ((getTimePassed() / 1000) > 300 && domFlags.size < 3)) && matchMakingGame() )
		{
			thread maps\mp\gametypes\_gamelogic::endGame( "none", game["strings"]["time_limit_reached"] );
			return;			
		}
		
		wait ( 5.0 );
		maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();
	}
}


onPlayerKilled( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, killId )
{
	if( !isPlayer( attacker ) || 
		attacker.pers["team"] == self.pers["team"] )
		return;

	awardedAssault = false;
	awardedDefend = false;

	victim = self;

	foreach( trigger in victim.touchTriggers )
	{
		if( trigger != level.flags[0] &&
			trigger != level.flags[1] &&
			trigger != level.flags[2] )
			continue;
		
		ownerTeam = trigger.useObj.ownerTeam;
		victimTeam = victim.pers["team"];

		if ( ownerTeam == "neutral" )
			continue;
		
		// if the victim owns the flag and is touching the flag when killed, then the attacker gets the assault medal
		if ( victimTeam == ownerTeam )
		{
			awardedAssault = true;
			attacker thread maps\mp\gametypes\_hud_message::SplashNotify( "assault", maps\mp\gametypes\_rank::getScoreInfoValue( "assault" ) );
			attacker thread maps\mp\gametypes\_rank::giveRankXP( "assault" );
			maps\mp\gametypes\_gamescore::givePlayerScore( "assault", attacker );

			thread maps\mp\_matchdata::logKillEvent( killId, "defending" );
		}
		// if the victim doesn't own the flag and is touching the flag when killed, then the attacker gets the defend medal
		else
		{
			awardedDefend = true;
			attacker thread maps\mp\gametypes\_hud_message::SplashNotify( "defend", maps\mp\gametypes\_rank::getScoreInfoValue( "defend" ) );
			attacker thread maps\mp\gametypes\_rank::giveRankXP( "defend" );
			maps\mp\gametypes\_gamescore::givePlayerScore( "defend", attacker );

			attacker incPersStat( "defends", 1 );
			attacker maps\mp\gametypes\_persistence::statSetChild( "round", "defends", attacker.pers["defends"] );

			thread maps\mp\_matchdata::logKillEvent( killId, "assaulting" );
		}
	}

	foreach( trigger in attacker.touchTriggers )
	{
		if( trigger != level.flags[0] &&
			trigger != level.flags[1] &&
			trigger != level.flags[2] )
			continue;
		
		ownerTeam = trigger.useObj.ownerTeam;
		attackerTeam = attacker.pers["team"];
		
		if ( ownerTeam == "neutral" )
			continue;
		
		// if the attacker doesn't own the flag and is touching the flag when killing the victim, then the attacker gets an assault medal
		if ( attackerTeam != ownerTeam )
		{
			if ( !awardedAssault )
				attacker thread maps\mp\gametypes\_hud_message::SplashNotify( "assault", maps\mp\gametypes\_rank::getScoreInfoValue( "assault" ) );
			attacker thread maps\mp\gametypes\_rank::giveRankXP( "assault" );
			maps\mp\gametypes\_gamescore::givePlayerScore( "assault", attacker );		

			thread maps\mp\_matchdata::logKillEvent( killId, "defending" );
		}
	}

	// now if the attacker kills the victim within a radius of a flag that the attacker owns, the attacker gets a defend medal
	foreach( trigger in level.flags )
	{
		ownerTeam = trigger.useObj.ownerTeam;
		attackerTeam = attacker.pers["team"];
		
		victimDistanceToFlag = DistanceSquared( trigger.origin, victim.origin );
		defendDistance = 300 * 300;

		if( attackerTeam == ownerTeam && victimDistanceToFlag < defendDistance )
		{
			if ( !awardedDefend )
				attacker thread maps\mp\gametypes\_hud_message::SplashNotify( "defend", maps\mp\gametypes\_rank::getScoreInfoValue( "defend" ) );
			attacker thread maps\mp\gametypes\_rank::giveRankXP( "defend" );
			maps\mp\gametypes\_gamescore::givePlayerScore( "defend", attacker );

			thread maps\mp\_matchdata::logKillEvent( killId, "assaulting" );
		}
	}
}


getOwnedDomFlags()
{
	domFlags = [];
	foreach ( domFlag in level.domFlags )
	{
		if ( domFlag maps\mp\gametypes\_gameobjects::getOwnerTeam() != "neutral" && isDefined( domFlag.captureTime ) )
			domFlags[domFlags.size] = domFlag;
	}
	
	return domFlags;
}


getTeamFlagCount( team )
{
	score = 0;
	for (i = 0; i < level.flags.size; i++) 
	{
		if ( level.domFlags[i] maps\mp\gametypes\_gameobjects::getOwnerTeam() == team )
			score++;
	}	
	return score;
}

getFlagTeam()
{
	return self.useObj maps\mp\gametypes\_gameobjects::getOwnerTeam();
}

getBoundaryFlags()
{
	// get all flags which are adjacent to flags that aren't owned by the same team
	bflags = [];
	for (i = 0; i < level.flags.size; i++)
	{
		for (j = 0; j < level.flags[i].adjflags.size; j++)
		{
			if (level.flags[i].useObj maps\mp\gametypes\_gameobjects::getOwnerTeam() != level.flags[i].adjflags[j].useObj maps\mp\gametypes\_gameobjects::getOwnerTeam() )
			{
				bflags[bflags.size] = level.flags[i];
				break;
			}
		}
	}
	
	return bflags;
}

getBoundaryFlagSpawns(team)
{
	spawns = [];
	
	bflags = getBoundaryFlags();
	for (i = 0; i < bflags.size; i++)
	{
		if (isdefined(team) && bflags[i] getFlagTeam() != team)
			continue;
		
		for (j = 0; j < bflags[i].nearbyspawns.size; j++)
			spawns[spawns.size] = bflags[i].nearbyspawns[j];
	}
	
	return spawns;
}

getSpawnsBoundingFlag( avoidflag )
{
	spawns = [];

	for (i = 0; i < level.flags.size; i++)
	{
		flag = level.flags[i];
		if ( flag == avoidflag )
			continue;
		
		isbounding = false;
		for (j = 0; j < flag.adjflags.size; j++)
		{
			if ( flag.adjflags[j] == avoidflag )
			{
				isbounding = true;
				break;
			}
		}
		
		if ( !isbounding )
			continue;
		
		for (j = 0; j < flag.nearbyspawns.size; j++)
			spawns[spawns.size] = flag.nearbyspawns[j];
	}
	
	return spawns;
}

// gets an array of all spawnpoints which are near flags that are
// owned by the given team, or that are adjacent to flags owned by the given team.
getOwnedAndBoundingFlagSpawns(team)
{
	spawns = [];

	for (i = 0; i < level.flags.size; i++)
	{
		if ( level.flags[i] getFlagTeam() == team )
		{
			// add spawns near this flag
			for (s = 0; s < level.flags[i].nearbyspawns.size; s++)
				spawns[spawns.size] = level.flags[i].nearbyspawns[s];
		}
		else
		{
			for (j = 0; j < level.flags[i].adjflags.size; j++)
			{
				if ( level.flags[i].adjflags[j] getFlagTeam() == team )
				{
					// add spawns near this flag
					for (s = 0; s < level.flags[i].nearbyspawns.size; s++)
						spawns[spawns.size] = level.flags[i].nearbyspawns[s];
					break;
				}
			}
		}
	}
	
	return spawns;
}

// gets an array of all spawnpoints which are near flags that are
// owned by the given team
getOwnedFlagSpawns(team)
{
	spawns = [];

	for (i = 0; i < level.flags.size; i++)
	{
		if ( level.flags[i] getFlagTeam() == team )
		{
			// add spawns near this flag
			for (s = 0; s < level.flags[i].nearbyspawns.size; s++)
				spawns[spawns.size] = level.flags[i].nearbyspawns[s];
		}
	}
	
	return spawns;
}

flagSetup()
{
	maperrors = [];
	descriptorsByLinkname = [];

	// (find each flag_descriptor object)
	descriptors = getentarray("flag_descriptor", "targetname");
	
	flags = level.flags;
	
	for (i = 0; i < level.domFlags.size; i++)
	{
		closestdist = undefined;
		closestdesc = undefined;
		for (j = 0; j < descriptors.size; j++)
		{
			dist = distance(flags[i].origin, descriptors[j].origin);
			if (!isdefined(closestdist) || dist < closestdist) {
				closestdist = dist;
				closestdesc = descriptors[j];
			}
		}
		
		if (!isdefined(closestdesc)) {
			maperrors[maperrors.size] = "there is no flag_descriptor in the map! see explanation in dom.gsc";
			break;
		}
		if (isdefined(closestdesc.flag)) {
			maperrors[maperrors.size] = "flag_descriptor with script_linkname \"" + closestdesc.script_linkname + "\" is nearby more than one flag; is there a unique descriptor near each flag?";
			continue;
		}
		flags[i].descriptor = closestdesc;
		closestdesc.flag = flags[i];
		descriptorsByLinkname[closestdesc.script_linkname] = closestdesc;
	}
	
	if (maperrors.size == 0)
	{
		// find adjacent flags
		for (i = 0; i < flags.size; i++)
		{
			if (isdefined(flags[i].descriptor.script_linkto))
				adjdescs = strtok(flags[i].descriptor.script_linkto, " ");
			else
				adjdescs = [];
			for (j = 0; j < adjdescs.size; j++)
			{
				otherdesc = descriptorsByLinkname[adjdescs[j]];
				if (!isdefined(otherdesc) || otherdesc.targetname != "flag_descriptor") {
					maperrors[maperrors.size] = "flag_descriptor with script_linkname \"" + flags[i].descriptor.script_linkname + "\" linked to \"" + adjdescs[j] + "\" which does not exist as a script_linkname of any other entity with a targetname of flag_descriptor (or, if it does, that flag_descriptor has not been assigned to a flag)";
					continue;
				}
				adjflag = otherdesc.flag;
				if (adjflag == flags[i]) {
					maperrors[maperrors.size] = "flag_descriptor with script_linkname \"" + flags[i].descriptor.script_linkname + "\" linked to itself";
					continue;
				}
				flags[i].adjflags[flags[i].adjflags.size] = adjflag;
			}
		}
	}
	
	// assign each spawnpoint to nearest flag
	spawnpoints = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dom_spawn" );
	for (i = 0; i < spawnpoints.size; i++)
	{
		if (isdefined(spawnpoints[i].script_linkto)) {
			desc = descriptorsByLinkname[spawnpoints[i].script_linkto];
			if (!isdefined(desc) || desc.targetname != "flag_descriptor") {
				maperrors[maperrors.size] = "Spawnpoint at " + spawnpoints[i].origin + "\" linked to \"" + spawnpoints[i].script_linkto + "\" which does not exist as a script_linkname of any entity with a targetname of flag_descriptor (or, if it does, that flag_descriptor has not been assigned to a flag)";
				continue;
			}
			nearestflag = desc.flag;
		}
		else {
			nearestflag = undefined;
			nearestdist = undefined;
			for (j = 0; j < flags.size; j++)
			{
				dist = distancesquared(flags[j].origin, spawnpoints[i].origin);
				if (!isdefined(nearestflag) || dist < nearestdist)
				{
					nearestflag = flags[j];
					nearestdist = dist;
				}
			}
		}
		nearestflag.nearbyspawns[nearestflag.nearbyspawns.size] = spawnpoints[i];
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
}

initGametypeAwards()
{
	maps\mp\_awards::initStatAward( "pointscaptured", 0, maps\mp\_awards::highestWins );
}

onSpawnPlayer()
{
}

updateCPM()
{
	if ( !isDefined( self.CPM ) )
	{
		self.numCaps = 0;
		self.CPM = 0;
	}
	
	self.numCaps++;
	
	if ( getMinutesPassed() < 1 )
		return;
		
	self.CPM = self.numCaps / getMinutesPassed();
}

getCapXPScale()
{
	if ( self.CPM < 4 )
		return 1;
	else
		return 0.25;
}