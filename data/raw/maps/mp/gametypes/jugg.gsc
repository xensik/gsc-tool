#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;

//	jugg is allies
//	everyone else is axis

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
		registerTimeLimitDvar( level.gameType, 10 );
		registerRoundLimitDvar( level.gameType, 1 );
		registerScoreLimitDvar( level.gameType, 10 );
		registerWinLimitDvar( level.gameType, 1 );
		registerNumLivesDvar( level.gameType, 0 );
		registerHalfTimeDvar( level.gameType, 0 );
		
		level.matchRules_respawnNewJugg = false;
		level.matchRules_showJuggRadarIcon = true;
		level.matchRules_showJuggWorldIcon = false;			
		level.matchRules_damageMultiplier = 0;
		level.matchRules_vampirism = 0;		 
	}

	setSpecialLoadouts();
	
	level.teamBased = true;
	level.doPrematch = true;
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onSpawnPlayer = ::onSpawnPlayer;
	level.onPlayerKilled = ::onPlayerKilled; 
	level.onTimeLimit = ::onTimeLimit;
	
	if ( level.matchRules_damageMultiplier || level.matchRules_vampirism )
		level.modifyPlayerDamage = maps\mp\gametypes\_damage::gamemodeModifyPlayerDamage;
}


initializeMatchRules()
{
	//	set common values
	setCommonRulesFromMatchRulesData();
	
	//	set everything else (private match options, default .cfg file values, and what normally is registered in the 'else' below)
	level.matchRules_respawnNewJugg = GetMatchRulesData( "juggData", "respawnNewJugg" );
	level.matchRules_showJuggRadarIcon = GetMatchRulesData( "juggData", "showJuggRadarIcon" );
	level.matchRules_showJuggWorldIcon = GetMatchRulesData( "juggData", "showJuggWorldIcon" );
	
	SetDynamicDvar( "scr_jugg_roundswitch", 0 );
	registerRoundSwitchDvar( "jugg", 0, 0, 9 );
	SetDynamicDvar( "scr_jugg_roundlimit", 1 );
	registerRoundLimitDvar( "jugg", 1 );		
	SetDynamicDvar( "scr_jugg_winlimit", 1 );
	registerWinLimitDvar( "jugg", 1 );			
	SetDynamicDvar( "scr_jugg_halftime", 0 );
	registerHalfTimeDvar( "jugg", 0 );
		
	SetDynamicDvar( "scr_jugg_promode", 0 );	
}


onPrecacheGameType()
{
	precacheString( &"MP_JUGG_NEXT_JUGG_IN" );	
	
	precacheShader( "waypoint_kill" );
}


onStartGameType()
{
	setClientNameMode("auto_change");

	setObjectiveText( "allies", &"OBJECTIVES_JUGG" );
	setObjectiveText( "axis", &"OBJECTIVES_JUGG" );

	if ( level.splitscreen )
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_JUGG" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_JUGG" );
	}
	else
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_JUGG_SCORE" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_JUGG_SCORE" );
	}
	setObjectiveHintText( "allies", &"OBJECTIVES_JUGG_HINT" );
	setObjectiveHintText( "axis", &"OBJECTIVES_JUGG_HINT" );

	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );	
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_tdm_spawn" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_tdm_spawn" );
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "got_juggernaut", 250 );
	maps\mp\gametypes\_rank::registerScoreInfo( "kill_as_juggernaut", 50 );

	allowed = [];
	maps\mp\gametypes\_gameobjects::main(allowed);

	level.QuickMessageToAll = true;	
	level.blockWeaponDrops = true;
	
	level.jugg_juggernaut = undefined;
	level.jugg_choosingJugg = false;	
	
	level thread onPlayerConnect();	
	
	level.jugg_timerDisplay = createServerTimer( "objective", 1.4 );
	level.jugg_timerDisplay setPoint( "TOPLEFT", "TOPLEFT", 115, 5 );
	level.jugg_timerDisplay.label = &"MP_JUGG_NEXT_JUGG_IN";
	level.jugg_timerDisplay.alpha = 0;
	level.jugg_timerDisplay.archived = false;
	level.jugg_timerDisplay.hideWhenInMenu = true;	
	thread hideTimerDisplayOnGameEnd( level.jugg_timerDisplay );	

	level.killstreakRewards = false;
}


chooseInitialJugg()
{
	level endon( "game_ended" );
	
	gameFlagWait( "prematch_done" );
	
	level.jugg_timerDisplay.label = &"MP_JUGG_NEXT_JUGG_IN";
	level.jugg_timerDisplay setTimer( 8 );
	level.jugg_timerDisplay.alpha = 1;	
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 8.0 );
	
	level.jugg_timerDisplay.alpha = 0;
	
	resetJugg( level.players[ randomInt( level.players.size ) ] );
}


onPlayerConnect()
{
	for ( ;; )
	{
		level waittill( "connected", player );
		
		player.jugg_juggScore = 0;
		player.jugg_firstSpawn = true;
		player thread onDisconnect();
	}
}


onSpawnPlayer()
{
	if ( !level.jugg_choosingJugg )
	{
		level.jugg_choosingJugg = true;
		level thread chooseInitialJugg();
	}
	
	self.pers["gamemodeLoadout"] = level.jugg_loadouts[self.pers["team"]];		
	
	level notify ( "spawned_player" );	
}


getSpawnPoint()
{
	if ( self.jugg_firstSpawn )
	{
		self.jugg_firstSpawn = false;
		
		//	everyone is a gamemode class in jugg, no class selection
		self.pers["class"] = "gamemode";
		self.pers["lastClass"] = "";
		self.class = self.pers["class"];
		self.lastClass = self.pers["lastClass"];		
		
		//	everyone starts non jugg
		self maps\mp\gametypes\_menus::addToTeam( "axis", true );
	}
		
	if ( level.inGracePeriod )
	{
		spawnPoints = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_tdm_spawn" );
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random( spawnPoints );
	}
	else
	{
		spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( self.pers["team"] );
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( spawnPoints );
	}
	
	return spawnPoint;	
}	


onPlayerKilled( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, lifeId )
{	
	if ( isDefined( attacker ) && isPlayer( attacker ) && attacker != self )
	{
		//	victim is juggernaut
		if ( isDefined( level.jugg_juggernaut ) && level.jugg_juggernaut == self )
		{		
			if ( level.matchRules_showJuggWorldIcon )
				self.jugg_headIcon destroy();
			
			resetJugg( attacker, self );			
		}
		//	attacker is juggernaut
		else if ( isDefined( level.jugg_juggernaut ) && level.jugg_juggernaut == attacker )
		{
			attacker.jugg_juggScore ++;
			attacker maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( attacker.pers["team"], 1 );				
			attacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_JUGGERNAUT_KILL" );
			maps\mp\gametypes\_gamescore::givePlayerScore( "kill_as_juggernaut", attacker, self, true );
			attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill_as_juggernaut" );				
		}
	}
	else if ( isDefined( level.jugg_juggernaut ) && level.jugg_juggernaut == self )
	{		
		self maps\mp\gametypes\_menus::addToTeam( "axis" );
		level thread chooseInitialJugg();			
	}						
}


resetJugg( newJugg, oldJugg )
{
	//	clear old jugg
	if ( isDefined( oldJugg ) )
	{		
		oldJugg maps\mp\gametypes\_menus::addToTeam( "axis" );
	}
	
	if ( isDefined( level.jugg_juggernaut ) )
		playSoundOnPlayers( "mp_enemy_obj_captured" );
	else
		playSoundOnPlayers( "mp_obj_captured" );		
	
	//	set the new jugg	
	level.jugg_juggernaut = newJugg;
	newJugg maps\mp\gametypes\_menus::addToTeam( "allies" );	
	updateJuggScores( newJugg );
	
	//	give them a point for becoming jugg
	newJugg.jugg_juggScore ++;
	newJugg maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( "allies", 1 );	
		
	//	give the loadout
	newJugg thread giveJuggLoadout();
}


giveJuggLoadout()
{	
	//	wait till they've spawned if they're dead
	while( !isAlive( self ) )
		wait( 0.05 ); 	
	
	//	suit up
	self.pers["gamemodeLoadout"] = level.jugg_loadouts[self.pers["team"]];
	
	//	respawn?
	if ( level.matchRules_respawnNewJugg )
	{
		//	store chosen and set current class to the 
		self.jugg_chosenClass = self.class;
		self maps\mp\gametypes\_class::setClass( "gamemode" );		
		self thread maps\mp\gametypes\_playerlogic::spawnClient();
	}		
	else
		self thread maps\mp\killstreaks\_juggernaut::giveJuggernaut( "jugg_juggernaut" );
	
	//	world icon?
	if ( level.matchRules_showJuggWorldIcon )
		self.jugg_headIcon = self maps\mp\_entityheadIcons::setHeadIcon( level.otherTeam[self.team], "waypoint_kill", (0,0,85), 24, 24, undefined, undefined, undefined, undefined, undefined, false );	
	
	//	bonus and messaging
	gotJuggBonus = maps\mp\gametypes\_rank::getScoreInfoValue( "got_juggernaut" );				
	self thread maps\mp\gametypes\_hud_message::SplashNotify( "got_juggernaut", gotJuggBonus );
	maps\mp\gametypes\_gamescore::givePlayerScore( "got_juggernaut", self, undefined, true );	
	self thread maps\mp\gametypes\_rank::giveRankXP( "got_juggernaut" );
	level thread teamPlayerCardSplash( "callout_new_juggernaut", self, level.otherTeam[self.team] );
}


updateJuggScores( newJugg )
{
	highestScore = 0;
	foreach ( player in level.players )
	{
		if ( player != newJugg && isDefined( player.jugg_juggScore ) && player.jugg_juggScore > highestScore )
			highestScore = player.jugg_juggScore;
	}

	game["teamScores"]["allies"] = newJugg.jugg_juggScore;
	setTeamScore( "axis", newJugg.jugg_juggScore );	
	
	game["teamScores"]["axis"] = highestScore;
	setTeamScore( "allies", highestScore );	
}


onDisconnect()
{
	level endon( "game_ended" );
	
	for(;;)
	{
		self waittill( "disconnected" );

		if ( isDefined( level.jugg_juggernaut ) && level.jugg_juggernaut == self )
		{
			//	if jugg disconnects, give jugg to lowest scoring player
			newJugg = undefined;
			lowestScore = 999999;
			foreach( player in level.players )
			{
				if ( player != self )
				{
					if ( isDefined( player.score ) && player.score < lowestScore )
					{
						lowestScore = player.score;
						newJugg = player;
					}
				}
			}
			//	give away the new loadout
			if ( isDefined( newJugg ) )
			{
				resetJugg( newJugg );
			}
		}		
	}
}


onTimeLimit()
{
	//	peasants win if they last the time limit
	level.finalKillCam_winner = "axis";
	level thread maps\mp\gametypes\_gamelogic::endGame( "axis", game["strings"]["time_limit_reached"] );	
}


hideTimerDisplayOnGameEnd( timerDisplay )
{
	level waittill("game_ended");
	timerDisplay.alpha = 0;
}


setSpecialLoadouts()
{
	//	everyone else
	if ( isUsingMatchRulesData() && GetMatchRulesData( "defaultClasses", "axis", 0, "class", "inUse" ) )
	{
		level.jugg_loadouts["axis"] = getMatchRulesSpecialClass( "axis", 0 );
		level.jugg_loadouts["axis"]["loadoutJuggernaut"] = 0;	
	}
	else
	{
		//	no killstreaks defined for special classes		
		level.jugg_loadouts["axis"]["loadoutPrimary"] = "iw5_usas12";
		level.jugg_loadouts["axis"]["loadoutPrimaryAttachment"] = "none";
		level.jugg_loadouts["axis"]["loadoutPrimaryAttachment2"] = "none";
		level.jugg_loadouts["axis"]["loadoutPrimaryBuff"] = "specialty_longerrange";
		level.jugg_loadouts["axis"]["loadoutPrimaryCamo"] = "none";
		level.jugg_loadouts["axis"]["loadoutPrimaryReticle"] = "none";
		level.jugg_loadouts["axis"]["loadoutSecondary"] = "iw5_44magnum";
		
		level.jugg_loadouts["axis"]["loadoutSecondaryAttachment"] = "none";
		level.jugg_loadouts["axis"]["loadoutSecondaryAttachment2"] = "none";
		level.jugg_loadouts["axis"]["loadoutSecondaryBuff"] = "specialty_null";
		level.jugg_loadouts["axis"]["loadoutSecondaryCamo"] = "none";
		level.jugg_loadouts["axis"]["loadoutSecondaryReticle"] = "none";
		
		level.jugg_loadouts["axis"]["loadoutEquipment"] = "claymore_mp";
		level.jugg_loadouts["axis"]["loadoutOffhand"] = "flash_grenade_mp";
		
		level.jugg_loadouts["axis"]["loadoutPerk1"] = "specialty_longersprint";
		level.jugg_loadouts["axis"]["loadoutPerk2"] = "specialty_quickdraw";
		level.jugg_loadouts["axis"]["loadoutPerk3"] = "specialty_bulletaccuracy";
		
		level.jugg_loadouts["axis"]["loadoutDeathstreak"] = "specialty_grenadepulldeath";
		level.jugg_loadouts["axis"]["loadoutJuggernaut"] = 0;		
	}
	
	//	the jugg
	if ( isUsingMatchRulesData() && GetMatchRulesData( "defaultClasses", "allies", 5, "class", "inUse" ) )
	{
		level.jugg_loadouts["allies"] = getMatchRulesSpecialClass( "allies", 5 );
		level.jugg_loadouts["allies"]["loadoutJuggernaut"] = 1;	// needed because we might spawn jugg instead of calling giveJugg()			
	}
	else
	{
		//	no killstreaks defined for special classes	
		level.jugg_loadouts["allies"]["loadoutPrimary"] = "iw5_scar";
		level.jugg_loadouts["allies"]["loadoutPrimaryAttachment"] = "none";
		level.jugg_loadouts["allies"]["loadoutPrimaryAttachment2"] = "none";
		level.jugg_loadouts["allies"]["loadoutPrimaryBuff"] = "specialty_bulletpenetration";
		level.jugg_loadouts["allies"]["loadoutPrimaryCamo"] = "none";
		level.jugg_loadouts["allies"]["loadoutPrimaryReticle"] = "none";
		
		level.jugg_loadouts["allies"]["loadoutSecondary"] = "rpg";
		level.jugg_loadouts["allies"]["loadoutSecondaryAttachment"] = "none";
		level.jugg_loadouts["allies"]["loadoutSecondaryAttachment2"] = "none";
		level.jugg_loadouts["allies"]["loadoutSecondaryBuff"] = "specialty_null";
		level.jugg_loadouts["allies"]["loadoutSecondaryCamo"] = "none";
		level.jugg_loadouts["allies"]["loadoutSecondaryReticle"] = "none";
		
		level.jugg_loadouts["allies"]["loadoutEquipment"] = "frag_grenade_mp";
		level.jugg_loadouts["allies"]["loadoutOffhand"] = "smoke_grenade_mp";
		
		level.jugg_loadouts["allies"]["loadoutPerk1"] = "specialty_scavenger";
		level.jugg_loadouts["allies"]["loadoutPerk2"] = "_specialty_blastshield";
		level.jugg_loadouts["allies"]["loadoutPerk3"] = "specialty_bulletaccuracy";
		
		level.jugg_loadouts["allies"]["loadoutDeathstreak"] = "specialty_null";	
		level.jugg_loadouts["allies"]["loadoutJuggernaut"] = 1;	// needed because we might spawn jugg instead of calling giveJugg()						
	}		
}