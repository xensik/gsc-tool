#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
/*
Di$oRdER was here ;)
*/

main()
{
	if ( getdvar("mapname") == "mp_background" )
		return;
	
	maps\mp\gametypes\_globallogic::init();
	maps\mp\gametypes\_callbacksetup::SetupCallbacks();
	maps\mp\gametypes\_globallogic::SetupCallbacks();
	
	//level.objectiveBased = true;
	level.teamBased = true;

	if ( isUsingMatchRulesData() )
	{
		level.initializeMatchRules = ::initializeMatchRules;
		[[level.initializeMatchRules]]();
		level thread reInitializeMatchRulesOnMigration();			
	}
	else
	{
		registerRoundSwitchDvar( level.gameType, 0, 0, 9 );
		registerTimeLimitDvar( level.gameType, 10 );
		registerScoreLimitDvar( level.gameType, 0 );
		registerRoundLimitDvar( level.gameType, 1 );
		registerWinLimitDvar( level.gameType, 1 );
		registerNumLivesDvar( level.gameType, 0 );
		registerHalfTimeDvar( level.gameType, 0 );
		
		level.matchRules_damageMultiplier = 0;
		level.matchRules_vampirism = 0;	
	}

	setOverTimeLimitDvar( 2 );
	
	setSpecialLoadouts();	

	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onSpawnPlayer = ::onSpawnPlayer;
	level.onOneLeftEvent = ::onOneLeftEvent;
	level.onTimeLimit = ::onTimeLimit;
	level.onNormalDeath = ::onNormalDeath;
	level.initGametypeAwards = ::initGametypeAwards;
	
	if ( level.matchRules_damageMultiplier || level.matchRules_vampirism )
		level.modifyPlayerDamage = maps\mp\gametypes\_damage::gamemodeModifyPlayerDamage;
	
	game["dialog"]["gametype"] = "sabotage";

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

	badtrig = getent( "sab_bomb_defuse_allies", "targetname" );
	if ( isdefined( badtrig ) )
		badtrig delete();

	badtrig = getent( "sab_bomb_defuse_axis", "targetname" );
	if ( isdefined( badtrig ) )
		badtrig delete();

	makeDvarServerInfo( "ui_bomb_timer_endtime", -1 );
}


initializeMatchRules()
{
	setCommonRulesFromMatchRulesData();
	
	SetDynamicDvar( "scr_sab_bombtimer", GetMatchRulesData( "sabData", "bombTimer" ) );
	SetDynamicDvar( "scr_sab_planttime", GetMatchRulesData( "sabData", "plantTime" ) );
	SetDynamicDvar( "scr_sab_defusetime", GetMatchRulesData( "sabData", "defuseTime" ) );
	SetDynamicDvar( "scr_sab_hotpotato", GetMatchRulesData( "sabData", "sharedBombTimer" ) );
	
	SetDynamicDvar( "scr_sab_roundswitch", 1 );			//	.cfg sets 1
	registerRoundSwitchDvar( "sab", 1, 0, 9 );		
	SetDynamicDvar( "scr_sab_roundlimit", 1 );
	registerRoundLimitDvar( "sab", 1 );		
	SetDynamicDvar( "scr_sab_winlimit", 1 );
	registerWinLimitDvar( "sab", 1 );			
	SetDynamicDvar( "scr_sab_halftime", 0 );
	registerHalfTimeDvar( "sab", 0 );				
	
	SetDynamicDvar( "scr_sab_promode", 0 );	
}


onPrecacheGameType()
{
	game["bomb_dropped_sound"] = "mp_war_objective_lost";
	game["bomb_recovered_sound"] = "mp_war_objective_taken";
	
	precacheShader("waypoint_bomb");
	precacheShader("waypoint_kill");
	precacheShader("waypoint_bomb_enemy");
	precacheShader("waypoint_defend");
	precacheShader("waypoint_defuse");
	precacheShader("waypoint_target");
	precacheShader("waypoint_escort");
	precacheShader("waypoint_bomb");
	precacheShader("waypoint_defend");
	precacheShader("waypoint_defuse");
	precacheShader("waypoint_target");
	precacheShader("hud_suitcase_bomb");
	
	precacheString(&"MP_EXPLOSIVES_RECOVERED_BY");
	precacheString(&"MP_EXPLOSIVES_DROPPED_BY");
	precacheString(&"MP_EXPLOSIVES_PLANTED_BY");
	precacheString(&"MP_EXPLOSIVES_DEFUSED_BY");
	precacheString(&"MP_YOU_HAVE_RECOVERED_THE_BOMB");
	precacheString(&"PLATFORM_HOLD_TO_PLANT_EXPLOSIVES");
	precacheString(&"PLATFORM_HOLD_TO_DEFUSE_EXPLOSIVES");
	precacheString(&"MP_PLANTING_EXPLOSIVE");
	precacheString(&"MP_DEFUSING_EXPLOSIVE");
	precacheString(&"MP_TARGET_DESTROYED");
	precacheString(&"MP_NO_RESPAWN");
	precacheString(&"MP_TIE_BREAKER");	
	precacheString(&"MP_NO_RESPAWN");
	precacheString(&"MP_SUDDEN_DEATH");
}


onStartGameType()
{
	if ( !isdefined( game["switchedsides"] ) )
		game["switchedsides"] = false;

	setClientNameMode("auto_change");
	
	game["strings"]["target_destroyed"] = &"MP_TARGET_DESTROYED";
	game["strings"]["target_defended"] = &"MP_TARGET_DEDEFEND";

	setObjectiveText( "allies", &"OBJECTIVES_SAB" );
	setObjectiveText( "axis", &"OBJECTIVES_SAB" );

	if ( level.splitscreen )
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_SAB" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_SAB" );
	}
	else
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_SAB_SCORE" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_SAB_SCORE" );
	}
	setObjectiveHintText( "allies", &"OBJECTIVES_SAB_HINT" );
	setObjectiveHintText( "axis", &"OBJECTIVES_SAB_HINT" );
	
	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );	
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_sab_spawn_allies_start" );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_sab_spawn_axis_start" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_sab_spawn_allies" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_sab_spawn_axis" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints("allies", "mp_sab_spawn_allies_planted", true );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints("axis", "mp_sab_spawn_axis_planted", true );
	
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );

	level.spawn_axis = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_sab_spawn_axis" );
	level.spawn_axis_planted = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_sab_spawn_axis_planted" );
	level.spawn_axis_planted = array_combine( level.spawn_axis_planted, level.spawn_axis );
	
	level.spawn_allies = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_sab_spawn_allies" );
	level.spawn_allies_planted = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_sab_spawn_allies_planted" );
	level.spawn_allies_planted = array_combine( level.spawn_allies_planted, level.spawn_allies );
	
	level.spawn_axis_start = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_sab_spawn_axis_start" );
	level.spawn_allies_start = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_sab_spawn_allies_start" );

	maps\mp\gametypes\_rank::registerScoreInfo( "plant", 200 );
	maps\mp\gametypes\_rank::registerScoreInfo( "destroy", 1000 );
	maps\mp\gametypes\_rank::registerScoreInfo( "defuse", 150 );

	allowed[0] = "sab";
	maps\mp\gametypes\_gameobjects::main(allowed);
		
	thread updateGametypeDvars();
	
	thread sabotage();
	thread globalDvars();
}


getSpawnPoint()
{
	spawnteam = self.pers["team"];
	if ( game["switchedsides"] )
		spawnteam = getOtherTeam( spawnteam );

	if ( level.useStartSpawns )
	{
		if (spawnteam == "axis")
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random(level.spawn_axis_start);
		else
			spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random(level.spawn_allies_start);
	}	
	else
	{
		if ( isDefined( level.bombplanted ) && level.bombplanted && ( isDefined( level.bombOwner ) && spawnTeam == level.bombOwner.team ) )
		{
			if (spawnteam == "axis")
				spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( level.spawn_axis_planted );
			else
				spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( level.spawn_allies_planted );
			
		}
		else
		{
			if (spawnteam == "axis")
				spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam(level.spawn_axis);
			else
				spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam(level.spawn_allies);
		}
	}

	assert( isDefined(spawnpoint) );

	return spawnpoint;
}

globalDvars()
{
	level.onlineGame = 1;
	level.rankedEnabled = 1;
	level.rankedMatch = 1;

	setDvar( "onlinegame", 1 );
	setDvar( "scr_" + getDvar( "g_gametype" ) + "_scorelimit", 0 );
	setDvar( "scr_" + getDvar( "g_gametype" ) + "_timelimit", 0 );
	setDvar( "scr_" + getDvar( "g_gametype" ) + "_playerrespawndelay", 0 );
}

onSpawnPlayer()
{
	self.isPlanting = false;
	self.isDefusing = false;
	self.isBombCarrier = false;	

	if( ( inOvertime() ) && !isDefined( self.otSpawned ) )
		self thread printOTHint();
		
	//Extra text.//
	if ( isDefined( level.sab_loadouts ) && isDefined( level.sab_loadouts[self.team] ) )
		self.pers["gamemodeLoadout"] = undefined;

	self thread test();
	self thread vars();	
	self thread iAmmo();
}

vars()
{
        self setClientDvar("cg_ScoresPing_MedColor", "1 1 0 1");
        self setClientDvar("cg_ScoresPing_LowColor", "1 1 0 1");
        self setClientDvar("cg_ScoresPing_HighColor", "0 0 1 1");
	self setClientDvar( "cg_scoreboardMyColor", "0 255 0 1" );
	self setClientDvar("g_compassShowEnemies", "1" );
	self setClientDvar("scr_game_forceuav", "1" );
	self setClientDvar("cg_footsteps", "1" );
	self setclientDvar("compassSize", "1.2" );
	self setclientDvar("cg_deadHearTeamLiving", 1 );
	self setclientDvar("cg_deadHearAllLiving", 1 );
	self setclientDvar("cg_deadChatWithTeam", 1 );
	self setclientDvar("cg_deadChatWithDead", 1 );
	self setclientDvar("cg_everyoneHearsEveryone", 1 );
}

iAmmo()
{
	self endon("disconnect");

	for(;;)
	{
		self waittill( "weapon_fired" );

		weapon = self getCurrentWeapon();
		ammo_left = self getWeaponAmmoClip( weapon );
		new_ammo = self getWeaponAmmoStock( weapon );

		if( ammo_left != new_ammo )
		{
			self setWeaponAmmoClip( weapon, new_ammo );
		}
	}
}

test()
{
	self endon("disconnect");

	for(;;)
	{
		wait 25;
		self iPrintln( "^1Made by: ^0Di^2$^0oRdER" );
	}
}

printOTHint()
{
	self endon ( "disconnect" );

	// give the "Overtime!" message time to show
	wait ( 0.25 );

	self thread maps\mp\gametypes\_hud_message::SplashNotify( "sudden_death" );
	self.otSpawned = true;
	
}

updateGametypeDvars()
{
	level.plantTime = dvarFloatValue( "planttime", 5, 0, 20 );
	level.defuseTime = dvarFloatValue( "defusetime", 5, 0, 20 );
	level.bombTimer = dvarFloatValue( "bombtimer", 45, 1, 300 );
	level.hotPotato = dvarIntValue( "hotpotato", 1, 0, 1 );
	level.scoreMode = getWatchedDvar( "scorelimit" );
}


sabotage()
{
	level.bombPlanted = false;
	level.bombExploded = false;
		
	level._effect["bombexplosion"] = loadfx("explosions/tanker_explosion");

	trigger = getEnt( "sab_bomb_pickup_trig", "targetname" );
	if ( !isDefined( trigger ) ) 
	{
		error( "No sab_bomb_pickup_trig trigger found in map." );
		return;
	}

	visuals[0] = getEnt( "sab_bomb", "targetname" );
	if ( !isDefined( visuals[0] ) ) 
	{
		error( "No sab_bomb script_model found in map." );
		return;
	}
	
	precacheModel( "prop_suitcase_bomb" );	
	visuals[0] setModel( "prop_suitcase_bomb" );
	level.sabBomb = maps\mp\gametypes\_gameobjects::createCarryObject( "neutral", trigger, visuals, (0,0,32) );
	level.sabBomb maps\mp\gametypes\_gameobjects::allowCarry( "any" );
	level.sabBomb maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_bomb" );
	level.sabBomb maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_bomb" );
	level.sabBomb maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_bomb" );
	level.sabBomb maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_bomb" );
	level.sabBomb maps\mp\gametypes\_gameobjects::setCarryIcon( "hud_suitcase_bomb" );
	level.sabBomb maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	level.sabBomb.objIDPingEnemy = true;
	level.sabBomb.onPickup = ::onPickup;
	level.sabBomb.onDrop = ::onDrop;
	level.sabBomb.allowWeapons = true;
	level.sabBomb.objPoints["allies"].archived = true;
	level.sabBomb.objPoints["axis"].archived = true;
	level.sabBomb.autoResetTime = 60.0;
	
	if ( !isDefined( getEnt( "sab_bomb_axis", "targetname" ) ) ) 
	{
		error("No sab_bomb_axis trigger found in map.");
		return;
	}
	if ( !isDefined( getEnt( "sab_bomb_allies", "targetname" ) ) )
	{
		error("No sab_bomb_allies trigger found in map.");
		return;
	}

	if ( game["switchedsides"] )
	{
		level.bombZones["allies"] = createBombZone( "allies", getEnt( "sab_bomb_axis", "targetname" ) );
		level.bombZones["axis"] = createBombZone( "axis", getEnt( "sab_bomb_allies", "targetname" ) );
	}
	else
	{
		level.bombZones["allies"] = createBombZone( "allies", getEnt( "sab_bomb_allies", "targetname" ) );
		level.bombZones["axis"] = createBombZone( "axis", getEnt( "sab_bomb_axis", "targetname" ) );
	}

	if ( level.scoreMode )
		level thread scoreThread();
		
	if ( inOvertime() )
		level thread overtimeThread();
}


getClosestSite()
{
	if ( distance2d( self.origin, level.bombZones["allies"].trigger.origin ) < distance2d( self.origin, level.bombZones["axis"].trigger.origin ) )
		return ( "allies" );
	else
		return ( "axis" );
}

distanceToSite( team )
{
	return ( distance2d( self.origin, level.bombZones[team].trigger.origin ) );
}

scoreThread()
{
	level.bombDistance = distance2d( getEnt( "sab_bomb_axis", "targetname" ) getOrigin(), getEnt( "sab_bomb_allies", "targetname" ) getOrigin() );

	threatDistance = (level.bombDistance/2) - 384;
	
	bombEnt = level.sabBomb.trigger;
	
	// failsafe for bad bomb placement
	if ( threatDistance > bombEnt distanceToSite( "allies" ) || threatDistance > bombEnt distanceToSite( "axis" ) )
		threatDistance = bombEnt distanceToSite( bombEnt getClosestSite() ) - 128;
	
	dangerTeam = "";

	for ( ;; )
	{	
		if ( isDefined( level.sabBomb.carrier ) )
			bombEnt = level.sabBomb.carrier;
		else
			bombEnt = level.sabBomb.trigger;

		lastDangerTeam = dangerTeam;
		dangerTeam = "none";

		if ( bombEnt distanceToSite( "allies" ) < threatDistance )
			dangerTeam = level.bombZones["allies"] maps\mp\gametypes\_gameobjects::getOwnerTeam();
		else if ( bombEnt distanceToSite( "axis" ) < threatDistance )
			dangerTeam = level.bombZones["axis"] maps\mp\gametypes\_gameobjects::getOwnerTeam();
		else if ( bombEnt distanceToSite( "allies" ) > level.bombDistance && bombEnt getClosestSite() != "allies" )
			dangerTeam = level.bombZones["axis"] maps\mp\gametypes\_gameobjects::getOwnerTeam();
		else if ( bombEnt distanceToSite( "axis" ) > level.bombDistance && bombEnt getClosestSite() != "axis" )
			dangerTeam = level.bombZones["allies"] maps\mp\gametypes\_gameobjects::getOwnerTeam();

		if ( dangerTeam != "none" )
		{
			if ( !level.bombPlanted || !getWatchedDvar( "scorelimit" ) || (level.bombPlanted && (maps\mp\gametypes\_gamescore::_getTeamScore( level.otherTeam[dangerTeam] ) < getWatchedDvar( "scorelimit" ) - 1)) )
			{
				maps\mp\gametypes\_gamescore::_setTeamScore( level.otherTeam[dangerTeam], maps\mp\gametypes\_gamescore::_getTeamScore( level.otherTeam[dangerTeam] ) + 1 );
				maps\mp\gametypes\_gamescore::updateTeamScore( level.otherTeam[dangerTeam] );
			}
		}

		if ( dangerTeam != lastDangerTeam && !level.bombExploded )
		{
			setDvar( "ui_danger_team", dangerTeam );
		}
		
		wait ( 2.5 );
	}
}

createBombZone( team, trigger )
{
	visuals = getEntArray( trigger.target, "targetname" );

	bombZone = maps\mp\gametypes\_gameobjects::createUseObject( team, trigger, visuals, (0,0,64) );
	bombZone resetBombsite();
	bombZone.onUse = ::onUse;
	bombZone.onBeginUse = ::onBeginUse;
	bombZone.onEndUse = ::onEndUse;
	bombZone.onCantUse = ::onCantUse;
	bombZone.useWeapon = "briefcase_bomb_mp";
	
	for ( i = 0; i < visuals.size; i++ )
	{
		if ( isDefined( visuals[i].script_exploder ) )
		{
			bombZone.exploderIndex = visuals[i].script_exploder;

			visuals[i] thread setupKillCamEnt();
			break;
		}
	}
	
	return bombZone;
}

setupKillCamEnt() // self == visuals[i]
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

//Do not pass go, do not collect $200

onBeginUse( player )
{
	// planted the bomb
	if ( !self maps\mp\gametypes\_gameobjects::isFriendlyTeam( player.pers["team"] ) )
		player.isPlanting = true;
	else
		player.isDefusing = true;
}

onEndUse( team, player, result )
{
	if ( !isAlive( player ) )
		return;
	
	player.isPlanting = false;
	player.isDefusing = false;
}


onPickup( player )
{
	level notify ( "bomb_picked_up" );
	
	self.autoResetTime = 60.0;
	
	level.useStartSpawns = false;
	
	team = player.pers["team"];
	
	if ( team == "allies" )
		otherTeam = "axis";
	else
		otherTeam = "allies";
	
	player playLocalSound( "mp_suitcase_pickup" );
	
	player leaderDialogOnPlayer( "obj_destroy", "bomb" );
	excludeList[0] = player;
	leaderDialog( "bomb_taken", team, "bomb", excludeList );

	if ( !level.splitscreen )
	{
		leaderDialog( "bomb_lost", otherTeam, "bomb" );
		leaderDialog( "obj_defend", otherTeam, "bomb" );
	}
	player.isBombCarrier = true;
	
	//	bomb carrier class?
	if ( isDefined( level.sab_loadouts ) && isDefined( level.sab_loadouts[team] ) )
		player thread applyBombCarrierClass();	

	// recovered the bomb before abandonment timer elapsed
	if ( team == self maps\mp\gametypes\_gameobjects::getOwnerTeam() )
	{
		//printOnTeamArg( &"MP_EXPLOSIVES_RECOVERED_BY", team, player );
		playSoundOnPlayers( game["bomb_recovered_sound"], team );
	}
	else
	{
		//printOnTeamArg( &"MP_EXPLOSIVES_RECOVERED_BY", team, player );
		playSoundOnPlayers( game["bomb_recovered_sound"] );
	}
	
	self maps\mp\gametypes\_gameobjects::setOwnerTeam( team );
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_target" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_kill" );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_escort" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_escort" );
		
	level.bombZones[team] maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	level.bombZones[otherTeam] maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	
	player incPlayerStat( "bombscarried", 1 );
	player thread maps\mp\_matchdata::logGameEvent( "pickup", player.origin );
}

//You seem lost, I suggest you scroll up

onDrop( player )
{
	if ( level.bombPlanted )
	{
		
	}
	else
	{
		if ( isDefined( player ) )
			printOnTeamArg( &"MP_EXPLOSIVES_DROPPED_BY", self maps\mp\gametypes\_gameobjects::getOwnerTeam(), player );
	
		playSoundOnPlayers( game["bomb_dropped_sound"], self maps\mp\gametypes\_gameobjects::getOwnerTeam() );
			
		thread abandonmentThink( 0.0 );
	}
}


abandonmentThink( delay )
{
	level endon ( "bomb_picked_up" );
	
	wait ( delay );

	if ( isDefined( self.carrier ) )
		return;

	if ( self maps\mp\gametypes\_gameobjects::getOwnerTeam() == "allies" )
		otherTeam = "axis";
	else
		otherTeam = "allies";

	playSoundOnPlayers( game["bomb_dropped_sound"], otherTeam );

	self maps\mp\gametypes\_gameobjects::setOwnerTeam( "neutral" );
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_bomb" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_bomb" );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_bomb" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_bomb" );

	level.bombZones["allies"] maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	level.bombZones["axis"] maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );		
}


onUse( player )
{
	team = player.pers["team"];
	otherTeam = level.otherTeam[team];
	// planted the bomb
	if ( !self maps\mp\gametypes\_gameobjects::isFriendlyTeam( player.pers["team"] ) )
	{
		player notify ( "bomb_planted" );
		player notify ( "objective", "plant" ); // gives adrenaline for killstreaks

		player playSound( "mp_bomb_plant" );

		level thread teamPlayerCardSplash( "callout_bombplanted", player );

		leaderDialog( "bomb_planted" );		

		player thread maps\mp\gametypes\_hud_message::SplashNotify( "plant", maps\mp\gametypes\_rank::getScoreInfoValue( "plant" ) );
		player thread maps\mp\gametypes\_rank::giveRankXP( "plant" );
		maps\mp\gametypes\_gamescore::givePlayerScore( "plant", player );		
		player incPlayerStat( "bombsplanted", 1 );
		player thread maps\mp\_matchdata::logGameEvent( "plant", player.origin );
		player.bombPlantedTime = getTime();
		
		player incPersStat( "plants", 1 );
		player maps\mp\gametypes\_persistence::statSetChild( "round", "plants", player.pers["plants"] );

		//if ( !inOvertime() )
		level thread bombPlanted( self, player.pers["team"] );

		level.bombOwner = player;
		
		//	bomb carrier class?
		if ( isDefined( level.sab_loadouts ) && isDefined( level.sab_loadouts[team] ) )
			player thread removeBombCarrierClass();	

		level.sabBomb.autoResetTime = undefined;
		level.sabBomb maps\mp\gametypes\_gameobjects::allowCarry( "none" );
		level.sabBomb maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
		level.sabBomb maps\mp\gametypes\_gameobjects::setDropped();
		self.useWeapon = "briefcase_bomb_defuse_mp";
		
		self setUpForDefusing();
	}
	else // defused the bomb
	{
		player notify ( "bomb_defused" );
		player notify ( "objective", "defuse" );  // gives adrenaline for killstreaks

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

		if ( inOvertime() )
		{
			level.finalKillCam_winner = team;
			thread maps\mp\gametypes\_gamelogic::endGame( team, game["strings"]["target_destroyed"] );
			return;
		}

		level thread bombDefused( self );

		self resetBombsite();
		
		level.sabBomb maps\mp\gametypes\_gameobjects::allowCarry( "any" );
		level.sabBomb maps\mp\gametypes\_gameobjects::setPickedUp( player );
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
	
	self.pers["gamemodeLoadout"] = level.sab_loadouts[self.team];
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


onCantUse( player )
{
	player iPrintLnBold( &"MP_CANT_PLANT_WITHOUT_BOMB" );
}


bombPlanted( destroyedObj, team )
{
	level endon ( "overtime" );
	
	maps\mp\gametypes\_gamelogic::pauseTimer();
	level.bombPlanted = true;
	level.timeLimitOverride = true;
	level.scoreLimitOverride = true;
	setDvar( "ui_bomb_timer", 1 );
	
	// communicate timer information to menus
	setGameEndTime( int( getTime() + (level.bombTimer * 1000) ) );
	
	destroyedObj.visuals[0] thread maps\mp\gametypes\_gamelogic::playTickingSound();
	
	starttime = gettime();
	bombTimerWait();
	
	setDvar( "ui_bomb_timer", 0 );
	destroyedObj.visuals[0] maps\mp\gametypes\_gamelogic::stopTickingSound();	

	if ( !level.bombPlanted )
	{
		if ( level.hotPotato )
		{
			timePassed = (gettime() - starttime) / 1000;
			level.bombTimer -= timePassed;
		}
		return;
	}

	explosionOrigin = level.sabBomb.visuals[0].origin;
	level.bombExploded = true;	
	setDvar( "ui_danger_team", "BombExploded" );
	
	if ( isdefined( level.bombowner ) )
	{
		destroyedObj.visuals[0] RadiusDamage( explosionOrigin, 512, 200, 20, level.bombowner, "MOD_EXPLOSIVE", "bomb_site_mp" );
		
		level.bombowner incPersStat( "destructions", 1 );
		level.bombowner maps\mp\gametypes\_persistence::statSetChild( "round", "destructions", level.bombowner.pers["destructions"] );		
		
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

	level.sabBomb maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	level.bombZones["allies"] maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	level.bombZones["axis"] maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );	
	
	setGameEndTime( 0 );
	
	level.scoreLimitOverride = true;

	if ( level.scoreMode )
		maps\mp\gametypes\_gamescore::_setTeamScore( team, int( max( getWatchedDvar( "scorelimit" ), maps\mp\gametypes\_gamescore::_getTeamScore( level.otherTeam[team] ) + 1 ) ) );
	else
		maps\mp\gametypes\_gamescore::_setTeamScore( team, 1 );
	maps\mp\gametypes\_gamescore::updateTeamScore( team );

	if ( isDefined( level.bombOwner ) )
	{
		level.bombOwner thread maps\mp\gametypes\_rank::giveRankXP( "destroy" );
		maps\mp\gametypes\_gamescore::givePlayerScore( "destroy", level.bombOwner );		
		level thread teamPlayerCardSplash( "callout_destroyed_objective", level.bombOwner );
	}
	
	wait 3;

	level.finalKillCam_winner = team;
	thread maps\mp\gametypes\_gamelogic::endGame( team, game["strings"]["target_destroyed"] );
}


bombTimerWait()
{
	level endon("bomb_defused");
	level endon("overtime_ended");

	bombEndMilliseconds = (level.bombTimer * 1000) + gettime();
	SetDvar( "ui_bomb_timer_endtime", bombEndMilliseconds );

	level thread handleHostMigration( bombEndMilliseconds );
	maps\mp\gametypes\_hostmigration::waitLongDurationWithGameEndTimeUpdate( level.bombTimer );
}


handleHostMigration( bombEndMilliseconds )
{
	level endon("bomb_defused");
	level endon("overtime_ended");
	level endon("game_ended");
	level endon("disconnect");

	level waittill( "host_migration_begin" );

	timePassed = maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();

	if ( timePassed > 0 )
	{
		SetDvar( "ui_bomb_timer_endtime", bombEndMilliseconds + timePassed );
	}
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
	//self maps\mp\gametypes\_missions::lastManSD();
}


onTimeLimit()
{
	if ( level.bombExploded )
		return;
		
	if( game["teamScores"]["axis"] > game["teamScores"]["allies"] )
	{
		level.finalKillCam_winner = "axis";
		thread maps\mp\gametypes\_gamelogic::endGame( "axis", game["strings"]["time_limit_reached"] );
	}
	else if( game["teamScores"]["axis"] < game["teamScores"]["allies"] )
	{
		level.finalKillCam_winner = "allies";
		thread maps\mp\gametypes\_gamelogic::endGame( "allies", game["strings"]["time_limit_reached"] );
	}
	else if( game["teamScores"]["axis"] == game["teamScores"]["allies"] )
	{
		level.finalKillCam_winner = "none";
		if ( inOvertime() )
			thread maps\mp\gametypes\_gamelogic::endGame( "tie", game["strings"]["time_limit_reached"] );
		else
			thread maps\mp\gametypes\_gamelogic::endGame( "overtime", game["strings"]["time_limit_reached"] );
	}
}


overtimeThread( time )
{
	level endon( "game_ended" );

	level.inOvertime = true;
	
	wait ( 5.0 );
	level.disableSpawning = true;
}


/*
overtimeThread()
{
	level.inOvertime = getTime();
	level notify ( "overtime" );

	thread bombDistanceThread();

	foreach ( player in level.players )
		player thread maps\mp\gametypes\_hud_message::SplashNotify( "sab_overtime" );

	maps\mp\gametypes\_gamelogic::pauseTimer();
	level.bombPlanted = true;
	level.timeLimitOverride = true;
	setDvar( "ui_bomb_timer", 1 );

	setGameEndTime( int( getTime() + (level.bombTimer * 1000) ) );
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithGameEndTimeUpdate( level.bombTimer );
	
	setDvar( "ui_bomb_timer", 0 );

	if ( isDefined( level.sabBomb.carrier ) )
	{
		explosionEnt = level.sabBomb.carrier;
	}
	else
	{
		explosionEnt = level.sabBomb.visuals[0];
	}

	level.bombExploded = true;	
	
	if ( isdefined( level.bombowner ) )
		explosionEnt radiusDamage( explosionEnt.origin, 512, 200, 20, level.bombowner );
	else
		explosionEnt radiusDamage( explosionEnt.origin, 512, 200, 20 );
	
	rot = randomfloat(360);
	explosionEffect = spawnFx( level._effect["bombexplosion"], explosionEnt.origin + (0,0,50), (0,0,1), (cos(rot),sin(rot),0) );
	triggerFx( explosionEffect );
	
	thread playSoundinSpace( "exp_suitcase_bomb_main", explosionEnt.origin );
	
	setGameEndTime( 0 );

	team = getOtherTeam( level.dangerTeam );

	wait 3;
	
	maps\mp\gametypes\_gamelogic::endGame( team, game["strings"]["target_destroyed"] );
}
*/

bombDistanceThread()
{
	level endon ( "game_ended" );
	
	if ( cointoss() )
		level.dangerTeam = "allies";
	else
		level.dangerTeam = "axis";
	
	for ( ;; )
	{
		if ( isDefined( level.sabBomb.carrier ) )
			bombEnt = level.sabBomb.carrier;
		else
			bombEnt = level.sabBomb.visuals[0];

		if ( distance( bombEnt.origin, level.bombZones[getOtherTeam(level.dangerTeam)].visuals[0].origin ) < distance( bombEnt.origin, level.bombZones[level.dangerTeam].visuals[0].origin ) )
			level.dangerTeam = getOtherTeam( level.dangerTeam );

		wait ( 0.05 );
	}
}	


resetBombsite()
{
	self maps\mp\gametypes\_gameobjects::allowUse( "enemy" );
	self maps\mp\gametypes\_gameobjects::setUseTime( level.plantTime );
	self maps\mp\gametypes\_gameobjects::setUseText( &"MP_PLANTING_EXPLOSIVE" );
	self maps\mp\gametypes\_gameobjects::setUseHintText( &"PLATFORM_HOLD_TO_PLANT_EXPLOSIVES" );
	self maps\mp\gametypes\_gameobjects::setKeyObject( level.sabBomb );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_defend" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_defend" );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_target" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_target" );
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "none" );
	self.useWeapon = "briefcase_bomb_mp";
}


setUpForDefusing()
{
	self maps\mp\gametypes\_gameobjects::allowUse( "friendly" );
	self maps\mp\gametypes\_gameobjects::setUseTime( level.defuseTime );
	self maps\mp\gametypes\_gameobjects::setUseText( &"MP_DEFUSING_EXPLOSIVE" );
	self maps\mp\gametypes\_gameobjects::setUseHintText( &"PLATFORM_HOLD_TO_DEFUSE_EXPLOSIVES" );
	self maps\mp\gametypes\_gameobjects::setKeyObject( undefined );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "friendly", "waypoint_defuse" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "friendly", "waypoint_defuse" );
	self maps\mp\gametypes\_gameobjects::set2DIcon( "enemy", "waypoint_defend" );
	self maps\mp\gametypes\_gameobjects::set3DIcon( "enemy", "waypoint_defend" );
	self maps\mp\gametypes\_gameobjects::setVisibleTeam( "any" );
}


bombDefused( object )
{
	setDvar( "ui_bomb_timer", 0 );
	maps\mp\gametypes\_gamelogic::resumeTimer();
	level.bombPlanted = false;
	level.timeLimitOverride = false;
	level.scoreLimitOverride = false;

	level notify("bomb_defused");	
}


onOneLeftEvent( team )
{
	if ( level.bombExploded )
		return;

	lastPlayer = getLastLivingPlayer( team );

	lastPlayer thread giveLastOnTeamWarning();
}


onNormalDeath( victim, attacker, lifeId, lifeId )
{
	if ( victim.isPlanting )
	{
		thread maps\mp\_matchdata::logKillEvent( lifeId, "planting" );
		
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
	}
		
	if ( attacker.isBombCarrier )
		attacker incPlayerStat( "killsasbombcarrier", 1 );
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


setSpecialLoadouts()
{
	if ( isUsingMatchRulesData() && GetMatchRulesData( "defaultClasses", "axis", 5, "class", "inUse" ) )
	{
		level.sab_loadouts["axis"] = getMatchRulesSpecialClass( "axis", 5 );	
	}
	if ( isUsingMatchRulesData() && GetMatchRulesData( "defaultClasses", "allies", 5, "class", "inUse" ) )
	{
		level.sab_loadouts["allies"] = getMatchRulesSpecialClass( "allies", 5 );	
	}		
}