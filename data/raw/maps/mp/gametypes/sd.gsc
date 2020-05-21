#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
// Rallypoints should be destroyed on leaving your team/getting killed
// Compass icons need to be looked at
// Doesn't seem to be setting angle on spawn so that you are facing your rallypoint

/*
	Search and Destroy
	Attackers objective: Bomb one of 2 positions
	Defenders objective: Defend these 2 positions / Defuse planted bombs
	Round ends:	When one team is eliminated, bomb explodes, bomb is defused, or roundlength time is reached
	Map ends:	When one team reaches the score limit, or time limit or round limit is reached
	Respawning:	Players remain dead for the round and will respawn at the beginning of the next round

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
*/

/*QUAKED mp_sd_spawn_attacker (0.0 1.0 0.0) (-16 -16 0) (16 16 72)
Attacking players spawn randomly at one of these positions at the beginning of a round.*/

/*QUAKED mp_sd_spawn_defender (1.0 0.0 0.0) (-16 -16 0) (16 16 72)
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
		registerRoundSwitchDvar( level.gameType, 3, 0, 9 );
		registerTimeLimitDvar( level.gameType, 2.5 );
		registerScoreLimitDvar( level.gameType, 1 );
		registerRoundLimitDvar( level.gameType, 0 );
		registerWinLimitDvar( level.gameType, 4 );
		registerNumLivesDvar( level.gameType, 1 );
		registerHalfTimeDvar( level.gameType, 0 );
		
		level.matchRules_damageMultiplier = 0;
		level.matchRules_vampirism = 0;	
	}
	
	level.objectiveBased = true;
	level.teamBased = true;
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onSpawnPlayer = ::onSpawnPlayer;
	level.onPlayerKilled = ::onPlayerKilled;
	level.onDeadEvent = ::onDeadEvent;
	level.onOneLeftEvent = ::onOneLeftEvent;
	level.onTimeLimit = ::onTimeLimit;
	level.onNormalDeath = ::onNormalDeath;
	level.initGametypeAwards = ::initGametypeAwards;
	
	if ( level.matchRules_damageMultiplier || level.matchRules_vampirism )
		level.modifyPlayerDamage = maps\mp\gametypes\_damage::gamemodeModifyPlayerDamage;
	
	game["dialog"]["gametype"] = "searchdestroy";

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

	makeDvarServerInfo( "ui_bomb_timer_endtime", -1 );

/#
		SetDevDvarIfUninitialized( "scr_sd_debugBombKillCamEnt", 0 );
#/
}


initializeMatchRules()
{
	//	set common values
	setCommonRulesFromMatchRulesData();
	
	//	set everything else (private match options, default .cfg file values, and what normally is registered in the 'else' below)
	roundLength = GetMatchRulesData( "sdData", "roundLength" );
	SetDynamicDvar( "scr_sd_timelimit", roundLength );
	registerTimeLimitDvar( "sd", roundLength );	
			
	roundSwitch = GetMatchRulesData( "sdData", "roundSwitch" );
	SetDynamicDvar( "scr_sd_roundswitch", roundSwitch );
	registerRoundSwitchDvar( "sd", roundSwitch, 0, 9 );
	
	winLimit = GetMatchRulesData( "commonOption", "scoreLimit" );
	SetDynamicDvar( "scr_sd_winlimit", winLimit );
	registerWinLimitDvar( "sd", winLimit );		
		
	SetDynamicDvar( "scr_sd_bombtimer", GetMatchRulesData( "sdData", "bombTimer" ) );
	SetDynamicDvar( "scr_sd_planttime", GetMatchRulesData( "sdData", "plantTime" ) );
	SetDynamicDvar( "scr_sd_defusetime", GetMatchRulesData( "sdData", "defuseTime" ) );
	SetDynamicDvar( "scr_sd_multibomb", GetMatchRulesData( "sdData", "multiBomb" ) );
	
	SetDynamicDvar( "scr_sd_roundlimit", 0 );
	registerRoundLimitDvar( "sd", 0 );		
	SetDynamicDvar( "scr_sd_scorelimit", 1 );
	registerScoreLimitDvar( "sd", 1 );			
	SetDynamicDvar( "scr_sd_halftime", 0 );
	registerHalfTimeDvar( "sd", 0 );				
	
	SetDynamicDvar( "scr_sd_promode", 0 );	
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
	precacheShader("waypoint_defuse");
	precacheShader("waypoint_defuse_a");
	precacheShader("waypoint_defuse_b");
	precacheShader("waypoint_escort");
/*
	precacheShader("waypoint_target");
	precacheShader("waypoint_target_a");
	precacheShader("waypoint_target_b");
	precacheShader("waypoint_defend");
	precacheShader("waypoint_defend_a");
	precacheShader("waypoint_defend_b");
	precacheShader("waypoint_defuse");
	precacheShader("waypoint_defuse_a");
	precacheShader("waypoint_defuse_b");
*/	
	precacheString( &"MP_EXPLOSIVES_RECOVERED_BY" );
	precacheString( &"MP_EXPLOSIVES_DROPPED_BY" );
	precacheString( &"MP_EXPLOSIVES_PLANTED_BY" );
	precacheString( &"MP_EXPLOSIVES_DEFUSED_BY" );
	precacheString( &"PLATFORM_HOLD_TO_PLANT_EXPLOSIVES" );
	precacheString( &"PLATFORM_HOLD_TO_DEFUSE_EXPLOSIVES" );
	precacheString( &"MP_CANT_PLANT_WITHOUT_BOMB" );	
	precacheString( &"MP_PLANTING_EXPLOSIVE" );	
	precacheString( &"MP_DEFUSING_EXPLOSIVE" );	
}


onStartGameType()
{
	if ( !isDefined( game["switchedsides"] ) )
		game["switchedsides"] = false;
	
	if ( game["switchedsides"] )
	{
		oldAttackers = game["attackers"];
		oldDefenders = game["defenders"];
		game["attackers"] = oldDefenders;
		game["defenders"] = oldAttackers;
	}
	
	setClientNameMode( "manual_change" );
	
	game["strings"]["target_destroyed"] = &"MP_TARGET_DESTROYED";
	game["strings"]["bomb_defused"] = &"MP_BOMB_DEFUSED";
	
	precacheString( game["strings"]["target_destroyed"] );
	precacheString( game["strings"]["bomb_defused"] );

	level._effect["bombexplosion"] = loadfx("explosions/tanker_explosion");
	
	setObjectiveText( game["attackers"], &"OBJECTIVES_SD_ATTACKER" );
	setObjectiveText( game["defenders"], &"OBJECTIVES_SD_DEFENDER" );

	if ( level.splitscreen )
	{
		setObjectiveScoreText( game["attackers"], &"OBJECTIVES_SD_ATTACKER" );
		setObjectiveScoreText( game["defenders"], &"OBJECTIVES_SD_DEFENDER" );
	}
	else
	{
		setObjectiveScoreText( game["attackers"], &"OBJECTIVES_SD_ATTACKER_SCORE" );
		setObjectiveScoreText( game["defenders"], &"OBJECTIVES_SD_DEFENDER_SCORE" );
	}
	setObjectiveHintText( game["attackers"], &"OBJECTIVES_SD_ATTACKER_HINT" );
	setObjectiveHintText( game["defenders"], &"OBJECTIVES_SD_DEFENDER_HINT" );

	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );	
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_sd_spawn_attacker" );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_sd_spawn_defender" );
	
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );
	
	allowed[0] = "sd";
	allowed[1] = "bombzone";
	allowed[2] = "blocker";
	maps\mp\gametypes\_gameobjects::main(allowed);
	
	maps\mp\gametypes\_rank::registerScoreInfo( "win", 2 );
	maps\mp\gametypes\_rank::registerScoreInfo( "loss", 1 );
	maps\mp\gametypes\_rank::registerScoreInfo( "tie", 1.5 );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "kill", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "headshot", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assist", 20 );
	maps\mp\gametypes\_rank::registerScoreInfo( "plant", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "defuse", 100 );
	
	thread updateGametypeDvars();
	
	//	because axis or allies may be attackers, special loadout has to be created on game start for this mode
	setSpecialLoadout();
	
	thread bombs();
}


getSpawnPoint()
{
	if(self.pers["team"] == game["attackers"])
		spawnPointName = "mp_sd_spawn_attacker";
	else
		spawnPointName = "mp_sd_spawn_defender";

	spawnPoints = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( spawnPointName );
	assert( spawnPoints.size );
	spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random( spawnPoints );

	return spawnpoint;
}

onSpawnPlayer()
{
	self.isPlanting = false;
	self.isDefusing = false;
	self.isBombCarrier = false;
	
	if ( level.multiBomb && !isDefined( self.carryIcon ) && self.pers["team"] == game["attackers"] && !level.bombPlanted )
	{
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
	
	//	bomb carrier class? clear this regardless if they were carrier
	if ( isDefined( level.sd_loadout ) && isDefined( level.sd_loadout[self.team] ) )
		self.pers["gamemodeLoadout"] = undefined;	
	
	level notify ( "spawned_player" );
}


hideCarryIconOnGameEnd()
{
	self endon( "disconnect" );
	
	level waittill( "game_ended" );
	
	if ( isDefined( self.carryIcon ) )
		self.carryIcon.alpha = 0;
}


onPlayerKilled(eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, killId)
{
	thread checkAllowSpectating();
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


sd_endGame( winningTeam, endReasonText )
{
	level.finalKillCam_winner = winningTeam;
	// don't show the final killcam if the game ends with the bomb blowing up or bomb being defused, unless the bomb kills someone
	if( endReasonText == game["strings"]["target_destroyed"] || endReasonText == game["strings"]["bomb_defused"] )
	{
		eraseKillCam = true;
		foreach( bombZone in level.bombZones )
		{
			if(	IsDefined( level.finalKillCam_killCamEntityIndex[ winningTeam ] ) && level.finalKillCam_killCamEntityIndex[ winningTeam ] == bombZone.killCamEntNum )
			{
				eraseKillCam = false;
				break;
			}
		}

		if( eraseKillCam )
			maps\mp\gametypes\_damage::eraseFinalKillCam();
	}

	thread maps\mp\gametypes\_gamelogic::endGame( winningTeam, endReasonText );
}


onDeadEvent( team )
{
	if ( level.bombExploded || level.bombDefused )
		return;
	
	if ( team == "all" )
	{
		if ( level.bombPlanted )
			sd_endGame( game["attackers"], game["strings"][game["defenders"]+"_eliminated"] );
		else
			sd_endGame( game["defenders"], game["strings"][game["attackers"]+"_eliminated"] );
	}
	else if ( team == game["attackers"] )
	{
		if ( level.bombPlanted )
			return;

		level thread sd_endGame( game["defenders"], game["strings"][game["attackers"]+"_eliminated"] );
	}
	else if ( team == game["defenders"] )
	{
		level thread sd_endGame( game["attackers"], game["strings"][game["defenders"]+"_eliminated"] );
	}
}


onOneLeftEvent( team )
{
	if ( level.bombExploded || level.bombDefused )
		return;

	lastPlayer = getLastLivingPlayer( team );

	lastPlayer thread giveLastOnTeamWarning();
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
		
		//playerstats used for accolades
		//attacker incPlayerStat( "defends", 1 );
		
		attacker incPersStat( "defends", 1 );
		attacker maps\mp\gametypes\_persistence::statSetChild( "round", "defends", attacker.pers["defends"] );
		
	}
	else if ( victim.isBombCarrier )
	{
		attacker incPlayerStat( "bombcarrierkills", 1 );
		thread maps\mp\_matchdata::logKillEvent( lifeId, "carrying" );			
	}
	else if ( victim.isDefusing )
	{
		thread maps\mp\_matchdata::logKillEvent( lifeId, "defusing" );
		
		//playerstats used for accolades
		//attacker incPlayerStat( "defends", 1 );
		
		attacker incPersStat( "defends", 1 );
		attacker maps\mp\gametypes\_persistence::statSetChild( "round", "defends", attacker.pers["defends"] );
	}
		
	if ( attacker.isBombCarrier )
		attacker incPlayerStat( "killsasbombcarrier", 1 );
}


giveLastOnTeamWarning()
{
	self endon("death");
	self endon("disconnect");
	level endon( "game_ended" );
		
	self waitTillRecoveredHealth( 3 );
	
	otherTeam = getOtherTeam( self.pers["team"] );
	level thread teamPlayerCardSplash( "callout_lastteammemberalive", self, self.pers["team"] );
	level thread teamPlayerCardSplash( "callout_lastenemyalive", self, otherTeam );
	level notify ( "last_alive", self );	
	self maps\mp\gametypes\_missions::lastManSD();
}


onTimeLimit()
{
	sd_endGame( game["defenders"], game["strings"]["time_limit_reached"] );
}


updateGametypeDvars()
{
	level.plantTime = dvarFloatValue( "planttime", 5, 0, 20 );
	level.defuseTime = dvarFloatValue( "defusetime", 5, 0, 20 );
	level.bombTimer = dvarFloatValue( "bombtimer", 45, 1, 300 );
	level.multiBomb = dvarIntValue( "multibomb", 0, 0, 1 );
}


//	to remove Dem overtime bombzone
removeBombZoneC( bombZones )
{
	cZones = [];
	brushModels = getEntArray( "script_brushmodel", "classname" );
	foreach ( brushModel in BrushModels )
	{
		if ( isDefined( brushModel.script_gameobjectname ) && brushModel.script_gameobjectname == "bombzone" )
		{			
			foreach ( bombZone in bombZones )
			{
				if ( distance( brushModel.origin, bombZone.origin ) < 100 && isSubStr( toLower( bombZone.script_label ), "c" ) )
				{
					//	track which bombzones need to be removed (2 in mogadishu?)
					bombZone.relatedBrushModel = brushModel;
					cZones[cZones.size] = bombZone;
					break;
				}					
			}
		}
	}	
	
	foreach ( cZone in cZones )
	{
		cZone.relatedBrushModel delete();
		visuals = getEntArray( cZone.target, "targetname" );
		foreach ( visual in visuals )
			visual delete();
		cZone delete();
	}
	
	return array_removeUndefined( bombZones );	
}


bombs()
{
	level.bombPlanted = false;
	level.bombDefused = false;
	level.bombExploded = false;

	trigger = getEnt( "sd_bomb_pickup_trig", "targetname" );
	if ( !isDefined( trigger ) )
	{
		error("No sd_bomb_pickup_trig trigger found in map.");
		return;
	}
	
	visuals[0] = getEnt( "sd_bomb", "targetname" );
	if ( !isDefined( visuals[0] ) )
	{
		error("No sd_bomb script_model found in map.");
		return;
	}

	precacheModel( "prop_suitcase_bomb" );	
	visuals[0] setModel( "prop_suitcase_bomb" );
	
	if ( !level.multiBomb )
	{
		level.sdBomb = maps\mp\gametypes\_gameobjects::createCarryObject( game["attackers"], trigger, visuals, (0,0,32) );
		level.sdBomb maps\mp\gametypes\_gameobjects::allowCarry( "friendly" );
		level.sdBomb maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_bomb" );
		level.sdBomb maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_bomb" );
		level.sdBomb maps\mp\gametypes\_gameobjects::setVisibleTeam( "friendly" );
		level.sdBomb maps\mp\gametypes\_gameobjects::setCarryIcon( "hud_suitcase_bomb" );
		level.sdBomb.allowWeapons = true;
		level.sdBomb.onPickup = ::onPickup;
		level.sdBomb.onDrop = ::onDrop;
	}
	else
	{
		trigger delete();
		visuals[0] delete();
	}
	
	
	level.bombZones = [];
	
	bombZones = getEntArray( "bombzone", "targetname" );	
	bombZones = removeBombZoneC( bombZones );
	
	for ( index = 0; index < bombZones.size; index++ )
	{
		trigger = bombZones[index];
		visuals = getEntArray( bombZones[index].target, "targetname" );
		
		bombZone = maps\mp\gametypes\_gameobjects::createUseObject( game["defenders"], trigger, visuals, (0,0,64) );
		bombZone maps\mp\gametypes\_gameobjects::allowUse( "enemy" );
		bombZone maps\mp\gametypes\_gameobjects::setUseTime( level.plantTime );
		bombZone maps\mp\gametypes\_gameobjects::setUseText( &"MP_PLANTING_EXPLOSIVE" );
		bombZone maps\mp\gametypes\_gameobjects::setUseHintText( &"PLATFORM_HOLD_TO_PLANT_EXPLOSIVES" );
		if ( !level.multiBomb )
			bombZone maps\mp\gametypes\_gameobjects::setKeyObject( level.sdBomb );
		label = bombZone maps\mp\gametypes\_gameobjects::getLabel();
		bombZone.label = label;
		bombZone maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_defend" + label );
		bombZone maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_defend" + label );
		bombZone maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_target" + label );
		bombZone maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_target" + label );
		bombZone maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
		bombZone.onBeginUse = ::onBeginUse;
		bombZone.onEndUse = ::onEndUse;
		bombZone.onUse = ::onUsePlantObject;
		bombZone.onCantUse = ::onCantUse;
		bombZone.useWeapon = "briefcase_bomb_mp";
		
		for ( i = 0; i < visuals.size; i++ )
		{
			if ( isDefined( visuals[i].script_exploder ) )
			{
				bombZone.exploderIndex = visuals[i].script_exploder;

				visuals[i] thread setupKillCamEnt( bombZone );
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

setupKillCamEnt( bombZone ) // self == visuals[i]
{
	tempOrg = Spawn( "script_origin", self.origin );
	tempOrg.angles = self.angles;
	tempOrg RotateYaw( -45, 0.05 );
	wait( 0.05 );
	bulletStart = self.origin + ( 0, 0, 5 );
	bulletEnd = ( self.origin + ( AnglesToForward( tempOrg.angles ) * 100 ) ) + ( 0, 0, 128 );
	result = BulletTrace( bulletStart, bulletEnd, false, self );
	self.killCamEnt = Spawn( "script_model", result[ "position" ] );
	bombZone.killCamEntNum = self.killCamEnt GetEntityNumber();
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
		if( GetDvarInt( "scr_sd_debugBombKillCamEnt" ) > 0 )
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

onBeginUse( player )
{
	if ( self maps\mp\gametypes\_gameobjects::isFriendlyTeam( player.pers["team"] ) )
	{
		player playSound( "mp_bomb_defuse" );
		player.isDefusing = true;
		
		if ( isDefined( level.sdBombModel ) )
			level.sdBombModel hide();
	}
	else
	{
		player.isPlanting = true;

		if ( level.multibomb )
		{
			for ( i = 0; i < self.otherBombZones.size; i++ )
			{
				//self.otherBombZones[i] maps\mp\gametypes\_gameobjects::disableObject();
				self.otherBombZones[i] maps\mp\gametypes\_gameobjects::allowUse( "none" );
				self.otherBombZones[i] maps\mp\gametypes\_gameobjects::setVisibleTeam( "friendly" );
			}
		}
	}
}

onEndUse( team, player, result )
{
	if ( !isDefined( player ) )
		return;
	
	if ( isAlive( player ) )
	{
		player.isDefusing = false;
		player.isPlanting = false;
	}
	
	if ( self maps\mp\gametypes\_gameobjects::isFriendlyTeam( player.pers["team"] ) )
	{
		if ( isDefined( level.sdBombModel ) && !result )
		{
			level.sdBombModel show();
		}
	}
	else
	{
		if ( level.multibomb && !result )
		{
			for ( i = 0; i < self.otherBombZones.size; i++ )
			{
				//self.otherBombZones[i] maps\mp\gametypes\_gameobjects::enableObject();
				self.otherBombZones[i] maps\mp\gametypes\_gameobjects::allowUse( "enemy" );
				self.otherBombZones[i] maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
			}
		}
	}
}

onCantUse( player )
{
	player iPrintLnBold( &"MP_CANT_PLANT_WITHOUT_BOMB" );
}

onUsePlantObject( player )
{
	// planted the bomb
	if ( !self maps\mp\gametypes\_gameobjects::isFriendlyTeam( player.pers["team"] ) )
	{
		level thread bombPlanted( self, player );
		//player logString( "bomb planted: " + self.label );
		
		// disable all bomb zones except this one
		for ( index = 0; index < level.bombZones.size; index++ )
		{
			if ( level.bombZones[index] == self )
				continue;
				
			level.bombZones[index] maps\mp\gametypes\_gameobjects::disableObject();
		}
		
		player playSound( "mp_bomb_plant" );
		player notify ( "bomb_planted" );
		player notify ( "objective", "plant" ); // gives adrenaline for killstreaks
		
		player incPersStat( "plants", 1 );
		player maps\mp\gametypes\_persistence::statSetChild( "round", "plants", player.pers["plants"] );

		//if ( !level.hardcoreMode )
		//	iPrintLn( &"MP_EXPLOSIVES_PLANTED_BY", player );
		
		//	bomb carrier class?
		if ( isDefined( level.sd_loadout ) && isDefined( level.sd_loadout[player.team] ) )
			player thread removeBombCarrierClass();	

		leaderDialog( "bomb_planted" );

		level thread teamPlayerCardSplash( "callout_bombplanted", player );

		level.bombOwner = player;
		player thread maps\mp\gametypes\_hud_message::SplashNotify( "plant", maps\mp\gametypes\_rank::getScoreInfoValue( "plant" ) );
		player thread maps\mp\gametypes\_rank::giveRankXP( "plant" );
		player.bombPlantedTime = getTime();
		maps\mp\gametypes\_gamescore::givePlayerScore( "plant", player );
		
		player thread maps\mp\_matchdata::logGameEvent( "plant", player.origin );
	}
}


applyBombCarrierClass()
{
	self endon( "death" );
	self endon( "disconnect" );
	level endon( "game_ended" );
	
	if ( self isJuggernaut() )
	{
		self notify( "lost_juggernaut" );
		wait( 0.05 );
	}	
	
	self.pers["gamemodeLoadout"] = level.sd_loadout[self.team];
	self maps\mp\gametypes\_class::giveLoadout( self.team, "gamemode", false, false );		
}


removeBombCarrierClass()
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


onUseDefuseObject( player )
{
	player notify ( "bomb_defused" );
	player notify ( "objective", "defuse" );  // gives adrenaline for killstreaks
	//player logString( "bomb defused: " + self.label );
	level thread bombDefused();
	
	// disable this bomb zone
	self maps\mp\gametypes\_gameobjects::disableObject();
	
	//if ( !level.hardcoreMode )
	//	iPrintLn( &"MP_EXPLOSIVES_DEFUSED_BY", player );
	leaderDialog( "bomb_defused" );

	level thread teamPlayerCardSplash( "callout_bombdefused", player );

	if ( isDefined( level.bombOwner ) && ( level.bombOwner.bombPlantedTime + 3000 + (level.defuseTime*1000) ) > getTime() && isReallyAlive( level.bombOwner ) )
		player thread maps\mp\gametypes\_hud_message::SplashNotify( "ninja_defuse", ( maps\mp\gametypes\_rank::getScoreInfoValue( "defuse" ) ) );
	else
		player thread maps\mp\gametypes\_hud_message::SplashNotify( "defuse", maps\mp\gametypes\_rank::getScoreInfoValue( "defuse" ) );
	
	player thread maps\mp\gametypes\_rank::giveRankXP( "defuse" );
	maps\mp\gametypes\_gamescore::givePlayerScore( "defuse", player );		
	
	player incPersStat( "defuses", 1 );
	player maps\mp\gametypes\_persistence::statSetChild( "round", "defuses", player.pers["defuses"] );
	
	player thread maps\mp\_matchdata::logGameEvent( "defuse", player.origin );
}


onDrop( player )
{
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_bomb" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_bomb" );
	
	maps\mp\_utility::playSoundOnPlayers( game["bomb_dropped_sound"], game["attackers"] );
}


onPickup( player )
{
	player.isBombCarrier = true;
	player incPlayerStat( "bombscarried", 1 );
	player thread maps\mp\_matchdata::logGameEvent( "pickup", player.origin );
	
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_escort" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_escort" );
	
	//	bomb carrier class?
	if ( isDefined( level.sd_loadout ) && isDefined( level.sd_loadout[player.team] ) )
		player thread applyBombCarrierClass();

	if ( !level.bombDefused )
	{
		teamPlayerCardSplash( "callout_bombtaken", player, player.team );		
		leaderDialog( "bomb_taken", player.pers["team"] );
	}
	maps\mp\_utility::playSoundOnPlayers( game["bomb_recovered_sound"], game["attackers"] );
}


onReset()
{
}


bombPlanted( destroyedObj, player )
{
	maps\mp\gametypes\_gamelogic::pauseTimer();
	level.bombPlanted = true;
	
	destroyedObj.visuals[0] thread maps\mp\gametypes\_gamelogic::playTickingSound();
	level.tickingObject = destroyedObj.visuals[0];

	level.timeLimitOverride = true;
	setGameEndTime( int( gettime() + (level.bombTimer * 1000) ) );
	setDvar( "ui_bomb_timer", 1 );
	
	if ( !level.multiBomb )
	{
		level.sdBomb maps\mp\gametypes\_gameobjects::allowCarry( "none" );
		level.sdBomb maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
		level.sdBomb maps\mp\gametypes\_gameobjects::setDropped();
		level.sdBombModel = level.sdBomb.visuals[0];
	}
	else
	{
		
		for ( index = 0; index < level.players.size; index++ )
		{
			if ( isDefined( level.players[index].carryIcon ) )
				level.players[index].carryIcon destroyElem();
		}

		trace = bulletTrace( player.origin + (0,0,20), player.origin - (0,0,2000), false, player );
		
		tempAngle = randomfloat( 360 );
		forward = (cos( tempAngle ), sin( tempAngle ), 0);
		forward = vectornormalize( forward - ( trace["normal"] * vectordot( forward, trace["normal"] ) ) );
		dropAngles = vectortoangles( forward );
		
		level.sdBombModel = spawn( "script_model", trace["position"] );
		level.sdBombModel.angles = dropAngles;
		level.sdBombModel setModel( "prop_suitcase_bomb" );
	}
	destroyedObj maps\mp\gametypes\_gameobjects::allowUse( "none" );
	destroyedObj maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	/*
	destroyedObj maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", undefined );
	destroyedObj maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", undefined );
	destroyedObj maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", undefined );
	destroyedObj maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", undefined );
	*/
	label = destroyedObj maps\mp\gametypes\_gameobjects::getLabel();
	
	// create a new object to defuse with.
	trigger = destroyedObj.bombDefuseTrig;
	trigger.origin = level.sdBombModel.origin;
	visuals = [];
	defuseObject = maps\mp\gametypes\_gameobjects::createUseObject( game["defenders"], trigger, visuals, (0,0,32) );
	defuseObject maps\mp\gametypes\_gameobjects::allowUse( "friendly" );
	defuseObject maps\mp\gametypes\_gameobjects::setUseTime( level.defuseTime );
	defuseObject maps\mp\gametypes\_gameobjects::setUseText( &"MP_DEFUSING_EXPLOSIVE" );
	defuseObject maps\mp\gametypes\_gameobjects::setUseHintText( &"PLATFORM_HOLD_TO_DEFUSE_EXPLOSIVES" );
	defuseObject maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	defuseObject maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_defuse" + label );
	defuseObject maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_defend" + label );
	defuseObject maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_defuse" + label );
	defuseObject maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_defend" + label );
	defuseObject.label = label;
	defuseObject.onBeginUse = ::onBeginUse;
	defuseObject.onEndUse = ::onEndUse;
	defuseObject.onUse = ::onUseDefuseObject;
	defuseObject.useWeapon = "briefcase_bomb_defuse_mp";
	
	BombTimerWait();
	setDvar( "ui_bomb_timer", 0 );
	
	destroyedObj.visuals[0] maps\mp\gametypes\_gamelogic::stopTickingSound();
	
	if ( level.gameEnded || level.bombDefused )
		return;
	
	level.bombExploded = true;
	
	explosionOrigin = level.sdBombModel.origin;
	level.sdBombModel hide();
	
	if ( isdefined( player ) )
	{
		destroyedObj.visuals[0] RadiusDamage( explosionOrigin, 512, 200, 20, player, "MOD_EXPLOSIVE", "bomb_site_mp" );
		player incPersStat( "destructions", 1 );
		player maps\mp\gametypes\_persistence::statSetChild( "round", "destructions", player.pers["destructions"] );
	}
	else
		destroyedObj.visuals[0] RadiusDamage( explosionOrigin, 512, 200, 20, undefined, "MOD_EXPLOSIVE", "bomb_site_mp" );
	
	rot = randomfloat(360);
	explosionEffect = spawnFx( level._effect["bombexplosion"], explosionOrigin + (0,0,50), (0,0,1), (cos(rot),sin(rot),0) );
	triggerFx( explosionEffect );

	PlayRumbleOnPosition( "grenade_rumble", explosionOrigin );
	earthquake( 0.75, 2.0, explosionOrigin, 2000 );
	wii_play_grenade_rumble( explosionOrigin );
	
	thread playSoundinSpace( "exp_suitcase_bomb_main", explosionOrigin );
	
	if ( isDefined( destroyedObj.exploderIndex ) )
		exploder( destroyedObj.exploderIndex );
	
	for ( index = 0; index < level.bombZones.size; index++ )
		level.bombZones[index] maps\mp\gametypes\_gameobjects::disableObject();
	defuseObject maps\mp\gametypes\_gameobjects::disableObject();
	
	setGameEndTime( 0 );
	
	wait 3;
	
	sd_endGame( game["attackers"], game["strings"]["target_destroyed"] );
}


BombTimerWait()
{
	level endon( "game_ended" );
	level endon( "bomb_defused" );

	bombEndMilliseconds = (level.bombTimer * 1000) + gettime();
	SetDvar( "ui_bomb_timer_endtime", bombEndMilliseconds );

	level thread handleHostMigration( bombEndMilliseconds );
	maps\mp\gametypes\_hostmigration::waitLongDurationWithGameEndTimeUpdate( level.bombTimer );
}


handleHostMigration( bombEndMilliseconds )
{
	level endon( "game_ended" );
	level endon( "bomb_defused" );
	level endon( "game_ended" );
	level endon( "disconnect" );

	level waittill( "host_migration_begin" );

	timePassed = maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();

	if ( timePassed > 0 )
	{
		SetDvar( "ui_bomb_timer_endtime", bombEndMilliseconds + timePassed );
	}
}


bombDefused()
{
	level.tickingObject maps\mp\gametypes\_gamelogic::stopTickingSound();
	level.bombDefused = true;
	setDvar( "ui_bomb_timer", 0 );
	
	level notify("bomb_defused");
	
	wait 1.5;
	
	setGameEndTime( 0 );
	
	sd_endGame( game["defenders"], game["strings"]["bomb_defused"] );
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


setSpecialLoadout()
{
	//	attacker bomb carrier
	if ( isUsingMatchRulesData() && GetMatchRulesData( "defaultClasses", "axis", 5, "class", "inUse" ) )
	{
		level.sd_loadout[game["attackers"]] = getMatchRulesSpecialClass( "axis", 5 );	
	}		
}