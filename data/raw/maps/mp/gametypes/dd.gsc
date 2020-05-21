#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;

/*
	Di$oRdER was here
	Attackers objective: Bomb both of 2 positions
	Defenders objective: Defend these 2 positions / Defuse planted bombs
	Round ends	When one team defends for duration of match, both sites are destroyed.
	Map ends	When one team reaches the score limit, or time limit or round limit is reached
	Respawning	Players respawn indefinetly, immediately

	Level requirements
	------------------
		Allied Spawnpoints:
			classname		mp_sd_spawn_attacker
			Allied players spawn from these. Place at least 16 of these relatively close together.

		Axis Spawnpoints:
			classname		mp_sd_spawn_defender
			Axis players spawn from these. Place at least 16 of these relatively close together.

		Spectator Spawnpoints:
			classname		mp_global_intermission
			Spectators spawn from these and intermission is viewed from these positions.
			Atleast one is required, any more and they are randomly chosen between.

		Bombzones:
			classname					trigger_multiple
			targetname					bombzone
			script_gameobjectname		bombzone
			script_bombmode_original	<if defined this bombzone will be used in the original bomb mode>
			script_bombmode_single		<if defined this bombzone will be used in the single bomb mode>
			script_bombmode_dual		<if defined this bombzone will be used in the dual bomb mode>
			script_team					Set to allies or axis. This is used to set which team a bombzone is used by in dual bomb mode.
			script_label				Set to A or B. This sets the letter shown on the compass in original mode.
			This is a volume of space in which the bomb can planted. Must contain an origin brush.

		Bomb:
			classname				trigger_lookat
			targetname				bombtrigger
			script_gameobjectname	bombzone
			This should be a 16x16 unit trigger with an origin brush placed so that it's center lies on the bottom plane of the trigger.
			Must be in the level somewhere. This is the trigger that is used when defusing a bomb.
			It gets moved to the position of the planted bomb model.

	Level script requirements
	-------------------------
		Team Definitions:
			game["attackers"] = "allies";
			game["defenders"] = "axis";
			This sets which team is attacking and which team is defending. Attackers plant the bombs. Defenders protect the targets.

		Exploder Effects:
			Setting script_noteworthy on a bombzone trigger to an exploder group can be used to trigger additional effects.
	
	multiple bombs
	multiple targets
	spawning
	round handling when both sites are destroyed

*/

/*QUAKED mp_dd_spawn_attacker_a (0.75 0.0 0.5) (-16 -16 0) (16 16 72)
Axis players spawn near bomb a.*/

/*QUAKED mp_dd_spawn_attacker_b (0.75 0.0 0.5) (-16 -16 0) (16 16 72)
Axis players spawn near bomb b.*/

/*QUAKED mp_dd_spawn_attacker (0.75 0.0 0.5) (-16 -16 0) (16 16 72)
Axis players spawn away from enemies and near their team at one of these positions.*/

/*QUAKED mp_dd_spawn_defender (0.0 0.75 0.5) (-16 -16 0) (16 16 72)
Allied players spawn away from enemies and near their team at one of these positions.*/

/*QUAKED mp_dd_spawn_defender_a (0.0 0.75 0.5) (-16 -16 0) (16 16 72)
Allied players spawn near bomb site a.*/

/*QUAKED mp_dd_spawn_defender_b (0.0 0.75 0.5) (-16 -16 0) (16 16 72)
Allied players spawn near bomb site b.*/

/*QUAKED mp_dd_spawn_attacker_start (0.0 1.0 0.0) (-16 -16 0) (16 16 72)
Attacking players spawn randomly at one of these positions at the beginning of a round.*/

/*QUAKED mp_dd_spawn_defender_start (1.0 0.0 0.0) (-16 -16 0) (16 16 72)
Defending players spawn randomly at one of these positions at the beginning of a round.*/

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
		registerRoundSwitchDvar( level.gameType, 1, 0, 9 );
		registerTimeLimitDvar( level.gameType, 3 );
		registerScoreLimitDvar( level.gameType, 0 );
		registerRoundLimitDvar( level.gameType, 3 );
		registerWinLimitDvar( level.gameType, 2 );
		registerNumLivesDvar( level.gameType, 0 );
		registerHalfTimeDvar( level.gameType, 0 );
		
		level.matchRules_damageMultiplier = 0;
		level.matchRules_vampirism = 0;	
	}
	
	setOverTimeLimitDvar( 3 );
	
	level.objectiveBased = true;
	level.teamBased = true;
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onSpawnPlayer = ::onSpawnPlayer;
	level.onDeadEvent = ::onDeadEvent;
	level.onTimeLimit = ::onTimeLimit;
	level.onNormalDeath = ::onNormalDeath;
	level.initGametypeAwards = ::initGametypeAwards;
	
	if ( level.matchRules_damageMultiplier || level.matchRules_vampirism )
		level.modifyPlayerDamage = maps\mp\gametypes\_damage::gamemodeModifyPlayerDamage;	
	
	level.dd = true;
	level.bombsPlanted = 0;
	level.ddBombModel = []
	
	setBombTimerDvar();
	
	makeDvarServerInfo( "ui_bombtimer_a", -1 );
	makeDvarServerInfo( "ui_bombtimer_b", -1 );
	
	game["dialog"]["gametype"] = "demolition";
	
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

/#
	SetDevDvarIfUninitialized( "scr_dd_debugBombKillCamEnt", 0 );
#/
}


initializeMatchRules()
{
	//	set common values
	setCommonRulesFromMatchRulesData();
	
	//	set everything else (private match options, default .cfg file values, and what normally is registered in the 'else' below)				
	roundSwitch = GetMatchRulesData( "demData", "roundSwitch" );
	SetDynamicDvar( "scr_dd_roundswitch", roundSwitch );
	registerRoundSwitchDvar( "dd", roundSwitch, 0, 9 );
		
	SetDynamicDvar( "scr_dd_bombtimer", GetMatchRulesData( "demData", "bombTimer" ) );
	SetDynamicDvar( "scr_dd_planttime", GetMatchRulesData( "demData", "plantTime" ) );
	SetDynamicDvar( "scr_dd_defusetime", GetMatchRulesData( "demData", "defuseTime" ) );
	SetDynamicDvar( "scr_dd_addtime", GetMatchRulesData( "demData", "extraTime" ) );
	
	SetDynamicDvar( "scr_dd_roundlimit", 3 );
	registerRoundLimitDvar( "dd", 3 );		
	SetDynamicDvar( "scr_dd_winlimit", 2 );
	registerWinLimitDvar( "dd", 2 );			
	SetDynamicDvar( "scr_dd_halftime", 0 );
	registerHalfTimeDvar( "dd", 0 );				
	
	SetDynamicDvar( "scr_dd_promode", 0 );	
}


onPrecacheGameType()
{
	game["bomb_dropped_sound"] = "mp_war_objective_lost";
	game["bomb_recovered_sound"] = "mp_war_objective_taken";

	precacheShader("waypoint_bomb");
	precacheShader("hud_suitcase_bomb");
	precacheShader("waypoint_target");
	precacheShader("waypoint_target_a");
	precacheShader("waypoint_target_b");
	precacheShader("waypoint_defend");
	precacheShader("waypoint_defend_a");
	precacheShader("waypoint_defend_b");
	precacheShader("waypoint_defuse_a");
	precacheShader("waypoint_defuse_b");
	precacheShader("waypoint_target");
	precacheShader("waypoint_target_a");
	precacheShader("waypoint_target_b");
	precacheShader("waypoint_defend");
	precacheShader("waypoint_defend_a");
	precacheShader("waypoint_defend_b");
	precacheShader("waypoint_defuse");
	precacheShader("waypoint_defuse_a");
	precacheShader("waypoint_defuse_b");
	
	precacheString( &"MP_EXPLOSIVES_RECOVERED_BY" );
	precacheString( &"MP_EXPLOSIVES_DROPPED_BY" );
	precacheString( &"MP_EXPLOSIVES_PLANTED_BY" );
	precacheString( &"MP_EXPLOSIVES_DEFUSED_BY" );
	precacheString( &"PLATFORM_HOLD_TO_PLANT_EXPLOSIVES" );
	precacheString( &"PLATFORM_HOLD_TO_DEFUSE_EXPLOSIVES" );
	precacheString( &"MP_CANT_PLANT_WITHOUT_BOMB" );	
	precacheString( &"MP_PLANTING_EXPLOSIVE" );	
	precacheString( &"MP_DEFUSING_EXPLOSIVE" );	
	precacheString( &"MP_BOMB_A_TIMER" );
	precacheString( &"MP_BOMB_B_TIMER" );	
	precacheString( &"MP_BOMBSITE_IN_USE" );
}

onStartGameType()
{	
	if ( game["roundsPlayed"] == 2 )
	{
		game["status"] = "overtime";
		setDvar( "ui_overtime", 1 );
	}
	
	if ( !isDefined( game["switchedsides"] ) )
		game["switchedsides"] = false;
	
	if ( game["switchedsides"] )
	{
		oldAttackers = game["attackers"];
		oldDefenders = game["defenders"];
		game["attackers"] = oldDefenders;
		game["defenders"] = oldAttackers;
	}
	
	level.useStartSpawns = true;
	
	setClientNameMode( "manual_change" );
	
	game["strings"]["target_destroyed"] = &"MP_TARGET_DESTROYED";
	game["strings"]["bomb_defused"] = &"MP_BOMB_DEFUSED";
	if ( inOvertime() )
	{
		game["dialog"]["defense_obj"] = "obj_destroy";
	}
	
	precacheString( game["strings"]["target_destroyed"] );
	precacheString( game["strings"]["bomb_defused"] );

	level._effect["bombexplosion"] = loadfx("explosions/tanker_explosion");
	
	setObjectiveText( game["attackers"], &"OBJECTIVES_DD_ATTACKER" );
	setObjectiveText( game["defenders"], &"OBJECTIVES_DD_DEFENDER" );

	if ( level.splitscreen )
	{
		setObjectiveScoreText( game["attackers"], &"OBJECTIVES_DD_ATTACKER" );
		setObjectiveScoreText( game["defenders"], &"OBJECTIVES_DD_DEFENDER" );
	}
	else
	{
		setObjectiveScoreText( game["attackers"], &"OBJECTIVES_DD_ATTACKER_SCORE" );
		setObjectiveScoreText( game["defenders"], &"OBJECTIVES_DD_DEFENDER_SCORE" );
	}
	
	if ( inOvertime() )
	{
		setObjectiveHintText( game["attackers"], &"OBJECTIVES_DD_OVERTIME_HINT" );
		setObjectiveHintText( game["defenders"], &"OBJECTIVES_DD_OVERTIME_HINT" );		
	}
	else
	{
		setObjectiveHintText( game["attackers"], &"OBJECTIVES_DD_ATTACKER_HINT" );
		setObjectiveHintText( game["defenders"], &"OBJECTIVES_DD_DEFENDER_HINT" );
	}

	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );		
	
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( game["defenders"], "mp_dd_spawn_defender" );	
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( game["defenders"], "mp_dd_spawn_defender_a", true );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( game["defenders"], "mp_dd_spawn_defender_b", true );
	
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_dd_spawn_defender_start" );
	
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( game["attackers"], "mp_dd_spawn_attacker" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( game["attackers"], "mp_dd_spawn_attacker_a", true );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( game["attackers"], "mp_dd_spawn_attacker_b", true );
	
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_dd_spawn_attacker_start" );
	
	level.spawn_defenders = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dd_spawn_defender" );
	level.spawn_defenders_a = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dd_spawn_defender_a" );
	level.spawn_defenders_a = array_combine( level.spawn_defenders, level.spawn_defenders_a );
	level.spawn_defenders_b = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dd_spawn_defender_b" );
	level.spawn_defenders_b = array_combine( level.spawn_defenders, level.spawn_defenders_b );
	
	level.spawn_attackers = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dd_spawn_attacker" );
	level.spawn_attackers_a = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dd_spawn_attacker_a" );
	level.spawn_attackers_a = array_combine( level.spawn_attackers, level.spawn_attackers_a );
	level.spawn_attackers_b = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dd_spawn_attacker_b" );
	level.spawn_attackers_b = array_combine( level.spawn_attackers, level.spawn_attackers_b );
	
	level.spawn_defenders_start = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dd_spawn_defender_start" );
	level.spawn_attackers_start = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_dd_spawn_attacker_start" );
	
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	level.aPlanted = false;
	level.bPlanted = false;
	
	setMapCenter( level.mapCenter );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "win", 2 );
	maps\mp\gametypes\_rank::registerScoreInfo( "loss", 1 );
	maps\mp\gametypes\_rank::registerScoreInfo( "tie", 1.5 );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "kill", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "headshot", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assist", 20 );
	maps\mp\gametypes\_rank::registerScoreInfo( "plant", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "defuse", 100 );
	
	thread updateGametypeDvars();
	thread waitToProcess();
	
	winlimit = getWatchedDvar("winlimit");
	
	allowed[0] = "dd";
	allowed[1] = "dd_bombzone";
	allowed[2] = "blocker";
	maps\mp\gametypes\_gameobjects::main(allowed);
	
	thread bombs();
}

waitToProcess()
{
	level endon( "game_end" );

	for ( ;; )
	{
		if ( level.inGracePeriod == 0 )
			break;
			
		wait ( 0.05 );	
	}
	
	level.useStartSpawns = false;
		
}

getSpawnPoint()
{
	spawnteam = self.pers["team"];

	if ( level.useStartSpawns )
	{
		if ( spawnteam == game["attackers"] )
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random(level.spawn_attackers_start);
		else
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random(level.spawn_defenders_start);
	}	
	else
	{
		if (spawnteam == game["attackers"] )
		{
			if ( inOvertime() )
				spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( spawnteam );
			else if ( (!level.aPlanted && !level.bPlanted) )
				spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( spawnteam );
			else if ( level.aPlanted && !level.bPlanted )
				spawnPoints = level.spawn_attackers_a;
			else if ( level.bPlanted && !level.aPlanted )
				spawnPoints = level.spawn_attackers_b;
			else
				spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( spawnteam );
			
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( spawnPoints );
		}
		else
		{
			if ( inOvertime() )
				spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( spawnteam );
			else if ( (!level.aPlanted && !level.bPlanted) )
				spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( spawnteam );
			else if ( level.aPlanted && !level.bPlanted )
				spawnPoints = level.spawn_defenders_a;
			else if ( level.bPlanted && !level.aPlanted )
				spawnPoints = level.spawn_defenders_b;
			else
				spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( spawnteam );
			
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( spawnPoints );
		}
	}
	
	assert( isDefined(spawnpoint) );

	return spawnpoint;
}

onSpawnPlayer()
{
	
	if ( inOvertime() || self.pers["team"] == game["attackers"] )
	{
		self.isPlanting = false;
		self.isDefusing = false;
		self.isBombCarrier = true;
		
		if ( level.splitscreen )
		{
			self.carryIcon = createIcon( "hud_suitcase_bomb", 33, 33 );
			self.carryIcon setPoint( "BOTTOM RIGHT", "BOTTOM RIGHT", 0, -78 );
			self.carryIcon.alpha = 0.75;
		}
		else
		{
			self.carryIcon = createIcon( "hud_suitcase_bomb", 50, 50 );
			self.carryIcon setPoint( "BOTTOM RIGHT", "BOTTOM RIGHT", -90, -65 );
			self.carryIcon.alpha = 0.75;
		}		
		self.carryIcon.hidewheninmenu = true;
		self thread hideCarryIconOnGameEnd();
	}
	else
	{
		self.isPlanting = false;
		self.isDefusing = false;
		self.isBombCarrier = false;
		
		if ( isDefined( self.carryIcon ) )
		{
			self.carryIcon Destroy();
		}
	}

	level notify ( "spawned_player" );
}


hideCarryIconOnGameEnd()
{
	self endon( "disconnect" );
	
	level waittill( "game_ended" );
	
	if ( isDefined( self.carryIcon ) )
		self.carryIcon.alpha = 0;
}


dd_endGame( winningTeam, endReasonText )
{
	if ( winningTeam == "tie" )
		level.finalKillCam_winner = "none";
	else
		level.finalKillCam_winner = winningTeam;
	
	thread maps\mp\gametypes\_gamelogic::endGame( winningTeam, endReasonText );
}


onDeadEvent( team )
{
	if ( level.bombExploded || level.bombDefused )
		return;
	
	if ( team == "all" )
	{
		if ( level.bombPlanted )
			dd_endGame( game["attackers"], game["strings"][game["defenders"]+"_eliminated"] );
		else
			dd_endGame( game["defenders"], game["strings"][game["attackers"]+"_eliminated"] );
	}
	else if ( team == game["attackers"] )
	{
		if ( level.bombPlanted )
			return;

		level thread dd_endGame( game["defenders"], game["strings"][game["attackers"]+"_eliminated"] );
	}
	else if ( team == game["defenders"] )
	{
		level thread dd_endGame( game["attackers"], game["strings"][game["defenders"]+"_eliminated"] );
	}
}


onNormalDeath( victim, attacker, lifeId )
{
	score = maps\mp\gametypes\_rank::getScoreInfoValue( "kill" );
	assert( isDefined( score ) );

	team = victim.team;
	
	if ( game["state"] == "postgame" && (victim.team == game["defenders"] || !level.bombPlanted) )
		attacker.finalKill = true;
		
	if ( victim.isPlanting )
	{
		thread maps\mp\_matchdata::logKillEvent( lifeId, "planting" );
		
		attacker incPersStat( "defends", 1 );
		attacker maps\mp\gametypes\_persistence::statSetChild( "round", "defends", attacker.pers["defends"] );
		
	}
	else if ( victim.isDefusing )
	{
		thread maps\mp\_matchdata::logKillEvent( lifeId, "defusing" );
		
		attacker incPersStat( "defends", 1 );
		attacker maps\mp\gametypes\_persistence::statSetChild( "round", "defends", attacker.pers["defends"] );
	}
}


onTimeLimit()
{
	if ( inOvertime() )
	{
		dd_endGame( "tie", game["strings"]["time_limit_reached"] );
	}
	else
	{
		dd_endGame( game["defenders"], game["strings"]["time_limit_reached"] );
	}
}


updateGametypeDvars()
{
	level.plantTime = dvarFloatValue( "planttime", 5, 0, 20 );
	level.defuseTime = dvarFloatValue( "defusetime", 5, 0, 20 );
	level.bombTimer = dvarIntValue( "bombtimer", 45, 1, 300 );
	level.ddTimeToAdd = dvarFloatValue( "addtime", 2, 0, 5 );; //how much time is added to the match when a target is destroyed
}


verifyBombzones( bombZones )
{
	missing = "";
	if ( bombZones.size != 3 )
	{
		foundA = false;
		foundB = false;
		foundC = false;
		foreach ( bombZone in BombZones )
		{
			if ( isSubStr( toLower( bombZone.script_label ), "a" ) )
				foundA = true;
			else if ( isSubStr( toLower( bombZone.script_label ), "b" ) )
				foundB = true;
			else if ( isSubStr( toLower( bombZone.script_label ), "c" ) )
				foundC = true;		
		}
		if ( !foundA )
			missing += " A ";
		if ( !foundB )
			missing += " B ";
		if ( !foundC )
			missing += " C ";
	}		
	if ( missing != "" )
		assertMsg( "Bombzones:" + missing + "missing." );	
}


bombs()
{
	level.bombPlanted = false;
	level.bombDefused = false;
	level.bombExploded = 0;

	level.bombZones = [];
	bombZones = getEntArray( "dd_bombzone", "targetname" );
	verifyBombzones( bombZones );
		
	//	loop and create interaction elements for bomb sites
	for ( index = 0; index < bombZones.size; index++ )
	{		
		//	get the trigger and visuals for the bombsite
		trigger = bombZones[index];
		visuals = getEntArray( bombZones[index].target, "targetname" );			
		label = bombZones[index].script_label;	
		collision = getEnt( "dd_bombzone_clip" + label, "targetname" );		
		if ( inOverTime() )
		{
			//	remove A and B in overtime
			if ( label == "_a" || label == "_b" )
			{
				trigger delete();
				visuals[0] delete();
				collision delete();
				continue;				
			}	
			
			//	create neutral bombsite
			bombZone = maps\mp\gametypes\_gameobjects::createUseObject( "neutral", trigger, visuals, (0,0,64) );
			bombZone maps\mp\gametypes\_gameobjects::allowUse( "any" );			
		}	
		else
		{
			//	remove C in rounds 1 and 2
			if ( label == "_c" )
			{
				trigger delete();
				visuals[0] delete();
				collision delete();
				continue;				
			}				
	
			//	create defender bombsites
			bombZone = maps\mp\gametypes\_gameobjects::createUseObject( game["defenders"], trigger, visuals, (0,0,64) );
			bombZone maps\mp\gametypes\_gameobjects::allowUse( "enemy" );					
		}			
		
		bombZone maps\mp\gametypes\_gameobjects::setUseTime( level.plantTime );
		bombZone maps\mp\gametypes\_gameobjects::setUseText( &"MP_PLANTING_EXPLOSIVE" );
		bombZone maps\mp\gametypes\_gameobjects::setUseHintText( &"PLATFORM_HOLD_TO_PLANT_EXPLOSIVES" );
		bombZone maps\mp\gametypes\_gameobjects::setKeyObject( level.ddBomb );
	
		//	from this point on, in overtime, the neutral bombsite C will be labeled _a 
		//	the label will only be used to utilize the existing dvars for hud timer display
		if ( inOverTime() )
			label = "_a";
			
		bombZone.label = label;
		bombZone.index = index;
		if ( inOvertime() )
		{
			bombZone maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_target" );
			bombZone maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_target" );
			bombZone maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_target" );
			bombZone maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_target" );
		}
		else
		{
			bombZone maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_defend" + label );
			bombZone maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_defend" + label );
			bombZone maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_target" + label );
			bombZone maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_target" + label );
		}
		bombZone maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
		bombZone.onBeginUse = ::onBeginUse;
		bombZone.onEndUse = ::onEndUse;
		bombZone.onUse = ::onUseObject;
		bombZone.onCantUse = ::onCantUse;
		bombZone.useWeapon = "briefcase_bomb_mp";
		bombZone.bombPlanted = false;
		
		bombZone.visuals[0] thread setupKillCamEnt();

		for ( i = 0; i < visuals.size; i++ )
		{
			if ( isDefined( visuals[i].script_exploder ) )
			{
				bombZone.exploderIndex = visuals[i].script_exploder;
				break;
			}
		}
		
		level.bombZones[level.bombZones.size] = bombZone;
		
		bombZone.bombDefuseTrig = getent( visuals[0].target, "targetname" );
		assert( isdefined( bombZone.bombDefuseTrig ) );
		bombZone.bombDefuseTrig.origin += (0,0,-10000);
		bombZone.bombDefuseTrig.label = label;
	}
	
	for ( index = 0; index < level.bombZones.size; index++ )
	{
		array = [];
		for ( otherindex = 0; otherindex < level.bombZones.size; otherindex++ )
		{
			if ( otherindex != index )
				array[ array.size ] = level.bombZones[otherindex];
		}
		level.bombZones[index].otherBombZones = array;
	}	
}

setupKillCamEnt() // self == bombZone.visuals[0]
{
	tempOrg = Spawn( "script_origin", self.origin );
	tempOrg.angles = self.angles;
	tempOrg RotateYaw( -45, 0.05 );
	wait( 0.05 );
	bulletStart = self.origin + ( 0, 0, 5 );
	bulletEnd = ( self.origin + ( AnglesToForward( tempOrg.angles ) * 100 ) ) + ( 0, 0, 128 );
	result = BulletTrace( bulletStart, bulletEnd, false, self );
	self.killCamEnt = Spawn( "script_model", result[ "position" ] );
	tempOrg delete();
/#
	self.killCamEnt thread debugKillCamEnt( self );
#/		
}

/#
debugKillCamEnt( visual ) // self == visuals[i].killCamEnt
{
	self endon( "death" );
	level endon( "game_ended" );
	visual endon( "death" );

	while( true )
	{
		if( GetDvarInt( "scr_dd_debugBombKillCamEnt" ) > 0 )
		{
			// show the kill cam ent
			Line( self.origin, self.origin + ( AnglesToForward( self.angles ) * 10 ), ( 1, 0, 0 ) );
			Line( self.origin, self.origin + ( AnglesToRight( self.angles ) * 10 ), ( 0, 1, 0 ) );
			Line( self.origin, self.origin + ( AnglesToUp( self.angles ) * 10 ), ( 0, 0, 1 ) );

			// line from bomb site to kill cam ent
			Line( visual.origin + ( 0, 0, 5 ), self.origin, ( 0, 0, 1 ) );

			// bomb site angles
			Line( visual.origin, visual.origin + ( AnglesToForward( visual.angles ) * 10 ), ( 1, 0, 0 ) );
			Line( visual.origin, visual.origin + ( AnglesToRight( visual.angles ) * 10 ), ( 0, 1, 0 ) );
			Line( visual.origin, visual.origin + ( AnglesToUp( visual.angles ) * 10 ), ( 0, 0, 1 ) );
		}
		wait( 0.05 );
	}
}
#/

onUseObject( player )
{
	team = player.pers["team"];
	otherTeam = level.otherTeam[team];

	if ( ( inOverTime() && self.bombPlanted == false ) || ( !inOvertime() && !self maps\mp\gametypes\_gameobjects::isFriendlyTeam( player.pers["team"] ) ) )
	{
		self.bombPlanted = true;
		player notify ( "bomb_planted" );
		player playSound( "mp_bomb_plant" );

		thread teamPlayerCardSplash( "callout_bombplanted", player );
		
		player notify ( "objective", "plant" );
		
		//iPrintLn( &"MP_EXPLOSIVES_PLANTED_BY", player );
		leaderDialog( "bomb_planted" );

		player thread maps\mp\gametypes\_hud_message::SplashNotify( "plant", maps\mp\gametypes\_rank::getScoreInfoValue( "plant" ) );
		player thread maps\mp\gametypes\_rank::giveRankXP( "plant" );
		maps\mp\gametypes\_gamescore::givePlayerScore( "plant", player );		
		player incPlayerStat( "bombsplanted", 1 );
		player thread maps\mp\_matchdata::logGameEvent( "plant", player.origin );
		player.bombPlantedTime = getTime();
		
		player incPersStat( "plants", 1 );
		player maps\mp\gametypes\_persistence::statSetChild( "round", "plants", player.pers["plants"] );

		level thread bombPlanted( self, player );

		level.bombOwner = player;
		self.useWeapon = "briefcase_bomb_defuse_mp";
	}
	else // defused the bomb
	{
		self.bombPlanted = false;		
		self thread bombHandler( player, "defused" );
		player notify ( "objective", "defuse" );
	}
}


resetBombZone()
{
	if ( inOvertime() )
	{
		self maps\mp\gametypes\_gameobjects::setOwnerTeam( "neutral" );
		self maps\mp\gametypes\_gameobjects::allowUse( "any" );		
		friendlyIcon = "waypoint_target";
		enemyIcon = "waypoint_target";
	}
	else
	{	
		self maps\mp\gametypes\_gameobjects::allowUse( "enemy" );
		friendlyIcon = "waypoint_defend" + self.label;
		enemyIcon = "waypoint_target" + self.label;
	}
	self maps\mp\gametypes\_gameobjects::setUseTime( level.plantTime );
	self maps\mp\gametypes\_gameobjects::setUseText( &"MP_PLANTING_EXPLOSIVE" );
	self maps\mp\gametypes\_gameobjects::setUseHintText( &"PLATFORM_HOLD_TO_PLANT_EXPLOSIVES" );
	self maps\mp\gametypes\_gameobjects::setKeyObject( level.ddBomb );			
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", friendlyIcon );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", friendlyIcon  );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", enemyIcon );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", enemyIcon );		
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	self.useWeapon = "briefcase_bomb_mp";
}

setUpForDefusing()
{	
	if ( inOvertime() )
	{
		friendlyIcon = "waypoint_defuse";
		enemyIcon = "waypoint_defend";
	}
	else
	{	
		friendlyIcon = "waypoint_defuse" + self.label;
		enemyIcon = "waypoint_defend" + self.label;
	}	
	
	self maps\mp\gametypes\_gameobjects::allowUse( "friendly" );
	self maps\mp\gametypes\_gameobjects::setUseTime( level.defuseTime );
	self maps\mp\gametypes\_gameobjects::setUseText( &"MP_DEFUSING_EXPLOSIVE" );
	self maps\mp\gametypes\_gameobjects::setUseHintText( &"PLATFORM_HOLD_TO_DEFUSE_EXPLOSIVES" );
	self maps\mp\gametypes\_gameobjects::setKeyObject( undefined );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", friendlyIcon );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", friendlyIcon );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", enemyIcon );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", enemyIcon );
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
}

onBeginUse( player )
{
	if ( ( inOverTime() && self.bombPlanted == true ) || ( !inOvertime() && self maps\mp\gametypes\_gameobjects::isFriendlyTeam( player.pers["team"] ) ) )
	{
		player playSound( "mp_bomb_defuse" );
		player.isDefusing = true;
		
		bestDistance = 9000000;
		closestBomb = undefined;
		
		if ( isDefined( level.ddBombModel ) )
		{
			foreach ( bomb in level.ddBombModel )
			{
				if ( !isDefined( bomb ) )
					continue;
				
				dist = distanceSquared( player.origin, bomb.origin );
				
				if (  dist < bestDistance )
				{
					bestDistance = dist;			
					closestBomb = bomb;
				}
			}
			
			assert( isDefined(closestBomb) );
			player.defusing = closestBomb;
			closestBomb hide();
		}
	}
	else
	{
		player.isPlanting = true;
	}
}

onEndUse( team, player, result )
{
	if ( !isDefined( player ) )
		return;
	
	if ( player.isDefusing )
	{
		if ( isDefined( player.defusing ) && !result )
		{
			player.defusing show();
		}
	}
	
	if ( isAlive( player ) )
	{
		player.isDefusing = false;
		player.isPlanting = false;
	}
}

onCantUse( player )
{
	player iPrintLnBold( &"MP_BOMBSITE_IN_USE" );
}

onReset()
{
}

bombPlanted( destroyedObj, player )
{
	destroyedObj endon( "defused" );
	
	playerTeam = player.team;
	
	level.bombsPlanted += 1;
	self setBombTimerDvar();
	maps\mp\gametypes\_gamelogic::pauseTimer();
	level.timePauseStart = getTime();
	level.timeLimitOverride = true;
	
	level.bombPlanted = true;
	level.destroyedObject = destroyedObj;
	
	//	not used in overtime, just for spawns in rounds 1 and 2
	if ( level.destroyedObject.label == "_a" )
		level.aPlanted = true;
	else
		level.bPlanted = true; 
	
	level.destroyedObject.bombPlanted = true;
	
	destroyedObj.visuals[0] thread playDemolitionTickingSound(destroyedObj);
	level.tickingObject = destroyedObj.visuals[0];
	
	self dropBombModel( player, destroyedObj.label );
	destroyedObj.bombDefused = false;	
	destroyedObj maps\mp\gametypes\_gameobjects::allowUse( "none" );
	destroyedObj maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	if ( inOvertime() )
		destroyedObj Maps\mp\gametypes\_gameobjects::setOwnerTeam( level.otherTeam[player.team] );	
	destroyedObj setUpForDefusing();
	
	destroyedObj BombTimerWait(destroyedObj); //waits for bomb to explode!
	
	destroyedObj thread bombHandler( player ,"explode", playerTeam );
	
}

bombHandler( player, destType, playerTeam )	// playerTeam needed because bombHandler is called after a wait so the player could be gone
{	
	self.visuals[0] notify( "stopTicking" );
	level.bombsPlanted -= 1;
	
	//	not used in overtime, just for spawns in rounds 1 and 2
	if ( self.label == "_a" )
		level.aPlanted = false;
	else
		level.bPlanted = false; 
	
	self restartTimer();
	self setBombTimerDvar();

	setDvar( "ui_bombtimer" + self.label, -1 );
	//self maps\mp\gametypes\_gameobjects::updateTimer( 0, false );
	
	if ( level.gameEnded )
		return;
	
	if ( destType == "explode" )
	{
		level notify("bomb_exploded" + self.label);
		level.bombExploded += 1;
		
		explosionOrigin = self.curorigin;
		level.ddBombModel[ self.label ] Delete();
		
		if ( isdefined( player ) )
		{
			self.visuals[0] RadiusDamage( explosionOrigin, 512, 200, 20, player, "MOD_EXPLOSIVE", "bomb_site_mp" );
			
			//targets destroyed used for award
			player incPlayerStat( "targetsdestroyed", 1 );			
			player incPersStat( "destructions", 1 );
			player maps\mp\gametypes\_persistence::statSetChild( "round", "destructions", player.pers["destructions"] );
		}
		else
		{
			self.visuals[0] RadiusDamage( explosionOrigin, 512, 200, 20, undefined, "MOD_EXPLOSIVE", "bomb_site_mp" );
		}
		
		rot = randomfloat(360);
		explosionEffect = spawnFx( level._effect["bombexplosion"], explosionOrigin + (0,0,50), (0,0,1), (cos(rot),sin(rot),0) );
		triggerFx( explosionEffect );
		
		PlayRumbleOnPosition( "grenade_rumble", explosionOrigin );
		earthquake( 0.75, 2.0, explosionOrigin, 2000 );
		wii_play_grenade_rumble( explosionOrigin );
		
		thread playSoundinSpace( "exp_suitcase_bomb_main", explosionOrigin );
		
		if ( isDefined( self.exploderIndex ) )
			exploder( self.exploderIndex );
		
		self maps\mp\gametypes\_gameobjects::disableObject();

		if ( !inOvertime() && level.bombExploded < 2 )
		{
			foreach ( splashPlayer in level.players )
				splashPlayer thread maps\mp\gametypes\_hud_message::SplashNotify( "time_added" );
		}
	
		wait 2;
		
		if ( inOvertime() || level.bombExploded > 1 )
			dd_endGame( playerTeam, game["strings"]["target_destroyed"] );
		else
			level thread teamPlayerCardSplash( "callout_time_added", player );
	}
	else //defused
	{
		player notify ( "bomb_defused" );
		self notify( "defused" );

//		if ( !level.hardcoreMode )
//			iPrintLn( &"MP_EXPLOSIVES_DEFUSED_BY", player );

		leaderDialog( "bomb_defused" );

		level thread teamPlayerCardSplash( "callout_bombdefused", player );

		level thread bombDefused( self );
		self resetBombzone();

		if ( isDefined( level.bombOwner ) && ( level.bombOwner.bombPlantedTime + 4000 + (level.defuseTime*1000) ) > getTime() && isReallyAlive( level.bombOwner ) )
			player thread maps\mp\gametypes\_hud_message::SplashNotify( "ninja_defuse", ( maps\mp\gametypes\_rank::getScoreInfoValue( "defuse" ) ) );
		else
			player thread maps\mp\gametypes\_hud_message::SplashNotify( "defuse", maps\mp\gametypes\_rank::getScoreInfoValue( "defuse" ) );
					
		player thread maps\mp\gametypes\_rank::giveRankXP( "defuse" );
		maps\mp\gametypes\_gamescore::givePlayerScore( "defuse", player );
		
		player incPlayerStat( "bombsdefused", 1 );
		player incPersStat( "defuses", 1 );
		player maps\mp\gametypes\_persistence::statSetChild( "round", "defuses", player.pers["defuses"] );
		
		player thread maps\mp\_matchdata::logGameEvent( "defuse", player.origIn );
	}
	
}

playDemolitionTickingSound( site )
{
	self endon("death");
	self endon("stopTicking");
	level endon("game_ended");
	
	while(1)
	{
		self playSound( "ui_mp_suitcasebomb_timer" );
		
		if ( !isDefined( site.waitTime ) || site.waitTime > 10 )
			wait 1.0;
		else if ( isDefined( site.waitTime ) && site.waitTime > 5  )
			wait 0.5;
		else 
			wait 0.25;
		maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();
	}
}

setBombTimerDvar()
{
	println( "BOMBS PLANTED: " + level.bombsPlanted );
	
	if ( level.bombsPlanted == 1 )
		setDvar( "ui_bomb_timer", 2 );
	else if ( level.bombsPlanted == 2 )
		setDvar( "ui_bomb_timer", 3 );
	else
		setDvar( "ui_bomb_timer", 0 );
}


dropBombModel( player, site )
{
	trace = bulletTrace( player.origin + (0,0,20), player.origin - (0,0,2000), false, player );

	tempAngle = randomfloat( 360 );
	forward = (cos( tempAngle ), sin( tempAngle ), 0);
	forward = VectorNormalize( forward - ( trace[ "normal" ] * VectorDot( forward, trace[ "normal" ] ) ) );
	dropAngles = vectortoangles( forward );
	
	level.ddBombModel[ site ] = spawn( "script_model", trace["position"] );
	level.ddBombModel[ site ].angles = dropAngles;
	level.ddBombModel[ site ] setModel( "prop_suitcase_bomb" );
}


restartTimer()
{
	if ( level.bombsPlanted <= 0 )
	{
		maps\mp\gametypes\_gamelogic::resumeTimer();
		level.timePaused = ( getTime() - level.timePauseStart ) ;
		level.timeLimitOverride = false;
	}
}


BombTimerWait(siteLoc)
{
	level endon("game_ended");
	level endon("bomb_defused" + siteLoc.label );

	if ( inOverTime() )
		siteLoc.waitTime = level.bombTimer; //	might add player option for overtime bomb timer, use bomb timer for now
	else
		siteLoc.waitTime = level.bombTimer;

	level thread update_ui_timers( siteLoc );
	
	while ( siteLoc.waitTime >= 0 )
	{
		siteLoc.waitTime--;

		//self maps\mp\gametypes\_gameobjects::updateTimer( waitTime, true );
		
		if ( siteLoc.waitTime >= 0 )
			wait( 1 );
		
		maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();
	}
}

update_ui_timers( siteLoc )
{
	level endon ( "game_ended" );
	level endon ( "disconnect" );
	level endon ( "bomb_defused" + siteLoc.label );
	level endon ( "bomb_exploded" + siteLoc.label );

	bombEndMilliseconds = (siteLoc.waitTime * 1000) + gettime();
	SetDvar( "ui_bombtimer" + siteLoc.label, bombEndMilliseconds );

	level waittill( "host_migration_begin" );

	timePassed = maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();

	if ( timePassed > 0 )
	{
		SetDvar( "ui_bombtimer" + siteLoc.label, bombEndMilliseconds + timePassed );
	}
}

bombDefused( siteDefused )
{
	level.tickingObject maps\mp\gametypes\_gamelogic::stopTickingSound();
	siteDefused.bombDefused = true;
	self setBombTimerDvar();
	
	setDvar( "ui_bombtimer" + siteDefused.label, -1 );
	
	level notify("bomb_defused" + siteDefused.label);	
}

initGametypeAwards()
{
	maps\mp\_awards::initStatAward( "targetsdestroyed", 	0, maps\mp\_awards::highestWins );
	maps\mp\_awards::initStatAward( "bombsplanted", 		0, maps\mp\_awards::highestWins );
	maps\mp\_awards::initStatAward( "bombsdefused", 		0, maps\mp\_awards::highestWins );
	maps\mp\_awards::initStatAward( "bombcarrierkills", 	0, maps\mp\_awards::highestWins );
	maps\mp\_awards::initStatAward( "bombscarried", 		0, maps\mp\_awards::highestWins );
	maps\mp\_awards::initStatAward( "killsasbombcarrier", 	0, maps\mp\_awards::highestWins );
}
