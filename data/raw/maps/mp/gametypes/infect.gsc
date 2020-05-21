#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include maps\mp\gametypes\_class;

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
		setOverrideWatchDvar( "scorelimit", 0 );
		registerRoundLimitDvar( level.gameType, 1 );
		registerWinLimitDvar( level.gameType, 1 );
		registerNumLivesDvar( level.gameType, 0 );
		registerHalfTimeDvar( level.gameType, 0 ); 
		
		level.matchRules_numInitialInfected = 1;		
		level.matchRules_damageMultiplier = 0;
		level.matchRules_vampirism = 0;	
	}
	
	setSpecialLoadouts();
	
	level.teamBased = true;
	level.doPrematch = true;
	level.onPrecacheGameType = ::onPrecacheGameType;
	level.onStartGameType = ::onStartGameType;
	level.onSpawnPlayer = ::onSpawnPlayer;
	level.getSpawnPoint = ::getSpawnPoint;
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
	level.matchRules_numInitialInfected = GetMatchRulesData( "infectData", "numInitialInfected" );
	
	setOverrideWatchDvar( "scorelimit", 0 );
	SetDynamicDvar( "scr_infect_roundswitch", 0 );
	registerRoundSwitchDvar( "infect", 0, 0, 9 );
	SetDynamicDvar( "scr_infect_roundlimit", 1 );
	registerRoundLimitDvar( "infect", 1 );		
	SetDynamicDvar( "scr_infect_winlimit", 1 );
	registerWinLimitDvar( "infect", 1 );			
	SetDynamicDvar( "scr_infect_halftime", 0 );
	registerHalfTimeDvar( "infect", 0 );
		
	SetDynamicDvar( "scr_infect_promode", 0 );	
}


onPrecacheGameType()
{
	precacheString( &"MP_CONSCRIPTION_STARTS_IN" );
}


onStartGameType()
{
	setClientNameMode("auto_change");

	setObjectiveText( "allies", &"OBJECTIVES_INFECT" );
	setObjectiveText( "axis", &"OBJECTIVES_INFECT" );

	if ( level.splitscreen )
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_INFECT" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_INFECT" );
	}
	else
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_INFECT_SCORE" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_INFECT_SCORE" );
	}
	setObjectiveHintText( "allies", &"OBJECTIVES_INFECT_HINT" );
	setObjectiveHintText( "axis", &"OBJECTIVES_INFECT_HINT" );

	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );	
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_tdm_spawn" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_tdm_spawn" );
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );

	allowed = [];
	maps\mp\gametypes\_gameobjects::main(allowed);	

	maps\mp\gametypes\_rank::registerScoreInfo( "final_rogue", 200 );	
	maps\mp\gametypes\_rank::registerScoreInfo( "draft_rogue", 100 );	
	maps\mp\gametypes\_rank::registerScoreInfo( "survivor", 100 );

	level.QuickMessageToAll = true;	
	level.blockWeaponDrops = true;
	
	level.infect_timerDisplay = createServerTimer( "objective", 1.4 );
	level.infect_timerDisplay setPoint( "TOPLEFT", "TOPLEFT", 115, 5 );
	level.infect_timerDisplay.label = &"MP_DRAFT_STARTS_IN";
	level.infect_timerDisplay.alpha = 0;
	level.infect_timerDisplay.archived = false;
	level.infect_timerDisplay.hideWhenInMenu = true;	
	
	level.infect_choseFirstInfected = false;
	level.infect_choosingFirstInfected = false;
	
	level thread onPlayerConnect();	
	level thread onPlayerDisconnect();
}


onPlayerConnect()
{
	for ( ;; )
	{
		level waittill( "connected", player );
		
		player.infect_firstSpawn = true;
	}
}


onSpawnPlayer()
{
	updateTeamScores();	
	
	//	let the first spawned player kick this off
	if ( !level.infect_choosingFirstInfected )
	{
		level.infect_choosingFirstInfected = true;
		level thread chooseFirstInfected();
	}	
	
	//	onSpawnPlayer() is called before giveLoadout()
	//	set self.pers["gamemodeLoadout"] for giveLoadout() to use
	if ( isDefined( self.isInitialInfected ) )
		self.pers["gamemodeLoadout"] = level.infect_loadouts["axis_initial"];	
	else
		self.pers["gamemodeLoadout"] = level.infect_loadouts[self.pers["team"]];		
	
	level notify ( "spawned_player" );
}


getSpawnPoint()
{	
	//	first time here?
	if ( self.infect_firstSpawn )
	{
		self.infect_firstSpawn = false;
		
		//	everyone is a gamemode class in infect, no class selection
		self.pers["class"] = "gamemode";
		self.pers["lastClass"] = "";
		self.class = self.pers["class"];
		self.lastClass = self.pers["lastClass"];	
			
		//	everyone starts as survivors	
		self maps\mp\gametypes\_menus::addToTeam( "allies", true );
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


chooseFirstInfected()
{
	level endon( "game_ended" );
	
	gameFlagWait( "prematch_done" );
	
	level.infect_timerDisplay.label = &"MP_DRAFT_STARTS_IN";
	level.infect_timerDisplay setTimer( 8 );
	level.infect_timerDisplay.alpha = 1;	
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 8.0 );
	
	level.infect_timerDisplay.alpha = 0;		
	
	first = level.players[ randomInt( level.players.size ) ];
	first.infect_isBeingChosen = true;
	
	first endon( "disconnect" );
	while( !isAlive( first ) )
		wait( 0.05 );
		
	first maps\mp\gametypes\_menus::addToTeam( "axis" );
	updateTeamScores();
	level.infect_choseFirstInfected = true;
	first.infect_isBeingChosen = undefined;
	first.isInitialInfected = true;
	
	//	remove jugg if needed before changing loadout
	if ( first isJuggernaut() )
	{
		first notify( "lost_juggernaut" );
		wait( 0.05 );
	}	
	//	set the gamemodeloadout to initial infected for giveLoadout() to use
	first.pers["gamemodeLoadout"] = level.infect_loadouts["axis_initial"];
	first maps\mp\gametypes\_class::giveLoadout( "axis", "gamemode", false, false );
	
	//	tell the world!
	thread teamPlayerCardSplash( "callout_first_mercenary", first );
	playSoundOnPlayers( "mp_enemy_obj_captured" );	
}


setInitialToNormalInfected()
{
	self.isInitialInfected = undefined;
	//	remove jugg if needed before changing loadout
	if ( self isJuggernaut() )
	{
		self notify( "lost_juggernaut" );
		wait( 0.05 );
	}	
	self.pers["gamemodeLoadout"] = level.infect_loadouts["axis"];
	self maps\mp\gametypes\_class::giveLoadout( "axis", "gamemode", false, false  );	
}


onPlayerKilled( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, lifeId )
{
	if ( isDefined( attacker ) && isPlayer( attacker ) && attacker != self && self.team == "allies" )
	{				
		//	move victim to infected
		self maps\mp\gametypes\_menus::addToTeam( "axis" );	
		updateTeamScores();
		
		//	set attacker to regular infected if they were the first and this is their first kill
		if ( isDefined( attacker.isInitialInfected ) )
			attacker thread setInitialToNormalInfected();
		
		//	reward attacker
		attacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DRAFTED" );
		maps\mp\gametypes\_gamescore::givePlayerScore( "draft_rogue", attacker, self, true );
		attacker thread maps\mp\gametypes\_rank::giveRankXP( "draft_rogue" );
		
		//	how many left?
		numSurvivors = getNumSurvivors();
		
		//	generic messages/sounds, and reward survivors
		if ( numSurvivors > 1 )
		{
			playSoundOnPlayers( "mp_enemy_obj_captured", "allies" );
			playSoundOnPlayers( "mp_war_objective_taken", "axis" );
			thread teamPlayerCardSplash( "callout_got_drafted", self, "allies" );	
			thread teamPlayerCardSplash( "callout_drafted_rogue", attacker, "axis" );			
				
			foreach ( player in level.players )
			{
				if ( player.team == "allies" )
				{
					player thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_SURVIVOR" );
					maps\mp\gametypes\_gamescore::givePlayerScore( "survivor", player, undefined, true );
					player thread maps\mp\gametypes\_rank::giveRankXP( "survivor" );	
				}
			}			
		}		
		//	inform/reward last
		if ( numSurvivors == 1 )
		{
			playSoundOnPlayers( "mp_obj_captured" );
			foreach ( player in level.players )
			{
				if ( player.team == "allies" )
				{
					player thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_FINAL_ROGUE" );
					maps\mp\gametypes\_gamescore::givePlayerScore( "final_rogue", player, undefined, true );	
					player thread maps\mp\gametypes\_rank::giveRankXP( "final_rogue" );					
					thread teamPlayerCardSplash( "callout_final_rogue", player );
					break;
				}
			}
		}
		//	infected win
		else if ( numSurvivors == 0 )
		{
			level.finalKillCam_winner = "axis";
			level thread maps\mp\gametypes\_gamelogic::endGame( "axis", game["strings"]["allies_eliminated"] );			
		}	
	}		
}


onPlayerDisconnect()
{
	for(;;)
	{
		level waittill( "disconnected", player );
		
		updateTeamScores();
	
		if ( isDefined( player.infect_isBeingChosen ) || level.infect_choseFirstInfected )
		{				
			if ( getNumSurvivors() == 0 )
			{
				level.finalKillCam_winner = "axis";
				level thread maps\mp\gametypes\_gamelogic::endGame( "axis", game["strings"]["allies_eliminated"] );	
			}
			else if ( getNumInfected() == 0 )
			{
				//	infected quit, shame them
				thread teamPlayerCardSplash( "callout_deserted", player );
				
				//	pick a new one and keep the game going
				level.infect_choseFirstInfected = false;
				level thread chooseFirstInfected();				
			}
		}		
	}
}


onTimeLimit()
{
	level.finalKillCam_winner = "allies";
	level thread maps\mp\gametypes\_gamelogic::endGame( "allies", game["strings"]["time_limit_reached"] );	
}


updateTeamScores()
{
	game["teamScores"]["axis"] = getNumInfected();
	setTeamScore( "axis", getNumInfected() );
	game["teamScores"]["allies"] = getNumSurvivors();
	setTeamScore( "allies", getNumSurvivors() );
}


getNumInfected()
{
	numInfected = 0;
	foreach ( player in level.players )
	{
		if ( player.team == "axis" )
			numInfected++;
	}
	return numInfected;	
}


getNumSurvivors()
{
	numSurvivors = 0;
	foreach ( player in level.players )
	{
		if ( player.team == "allies" )
			numSurvivors++;
	}
	return numSurvivors;	
}


setSpecialLoadouts()
{	
	//	Rogues in the game mode infected, are the only special class that has killstreaks.
	//	When rogues become the initial mercenary or are drafted to mercenaries, the initial mercenary and mercenary
	//	special classes have no killstreaks defined (because they aren't accessible for their class edit menu).
	//	We need to assign default null data so something exists in this loadout to override whatever they had before as rogues.	
	
	//	mercenaries
	if ( isUsingMatchRulesData() && GetMatchRulesData( "defaultClasses", "axis", 0, "class", "inUse" ) )
	{
		level.infect_loadouts["axis"] = getMatchRulesSpecialClass( "axis", 0 );	
		level.infect_loadouts["axis"]["loadoutStreakType"] = "assault";
		level.infect_loadouts["axis"]["loadoutKillstreak1"] = "none";
		level.infect_loadouts["axis"]["loadoutKillstreak2"] = "none";
		level.infect_loadouts["axis"]["loadoutKillstreak3"] = "none";		
	}
	else
	{
		level.infect_loadouts["axis"]["loadoutPrimary"] = "iw5_fmg9";
		level.infect_loadouts["axis"]["loadoutPrimaryAttachment"] = "reflex";
		level.infect_loadouts["axis"]["loadoutPrimaryAttachment2"] = "none";
		level.infect_loadouts["axis"]["loadoutPrimaryBuff"] = "specialty_null";
		level.infect_loadouts["axis"]["loadoutPrimaryCamo"] = "none";
		level.infect_loadouts["axis"]["loadoutPrimaryReticle"] = "none";
		
		level.infect_loadouts["axis"]["loadoutSecondary"] = "none";
		level.infect_loadouts["axis"]["loadoutSecondaryAttachment"] = "none";
		level.infect_loadouts["axis"]["loadoutSecondaryAttachment2"] = "none";
		level.infect_loadouts["axis"]["loadoutSecondaryBuff"] = "specialty_null";
		level.infect_loadouts["axis"]["loadoutSecondaryCamo"] = "none";
		level.infect_loadouts["axis"]["loadoutSecondaryReticle"] = "none";
		
		level.infect_loadouts["axis"]["loadoutEquipment"] = "throwingknife_mp";
		level.infect_loadouts["axis"]["loadoutOffhand"] = "none";
		
		level.infect_loadouts["axis"]["loadoutPerk1"] = "specialty_longersprint";
		level.infect_loadouts["axis"]["loadoutPerk2"] = "specialty_quickdraw";
		level.infect_loadouts["axis"]["loadoutPerk3"] = "specialty_quieter";
		
		level.infect_loadouts["axis"]["loadoutStreakType"] = "assault";
		level.infect_loadouts["axis"]["loadoutKillstreak1"] = "none";
		level.infect_loadouts["axis"]["loadoutKillstreak2"] = "none";
		level.infect_loadouts["axis"]["loadoutKillstreak3"] = "none";	
		
		level.infect_loadouts["axis"]["loadoutDeathstreak"] = "specialty_grenadepulldeath";		
	
		level.infect_loadouts["axis"]["loadoutJuggernaut"] = false;	
	}
	
	//	initial mercenaries
	if ( isUsingMatchRulesData() && GetMatchRulesData( "defaultClasses", "axis", 5, "class", "inUse" ) )
	{
		level.infect_loadouts["axis_initial"] = getMatchRulesSpecialClass( "axis", 5 );	
		level.infect_loadouts["axis_initial"]["loadoutStreakType"] = "assault";
		level.infect_loadouts["axis_initial"]["loadoutKillstreak1"] = "none";
		level.infect_loadouts["axis_initial"]["loadoutKillstreak2"] = "none";
		level.infect_loadouts["axis_initial"]["loadoutKillstreak3"] = "none";	
	}
	else
	{
		level.infect_loadouts["axis_initial"]["loadoutPrimary"] = "iw5_scar";
		level.infect_loadouts["axis_initial"]["loadoutPrimaryAttachment"] = "reflex";
		level.infect_loadouts["axis_initial"]["loadoutPrimaryAttachment2"] = "xmags";
		level.infect_loadouts["axis_initial"]["loadoutPrimaryBuff"] = "specialty_bling";
		level.infect_loadouts["axis_initial"]["loadoutPrimaryCamo"] = "none";
		level.infect_loadouts["axis_initial"]["loadoutPrimaryReticle"] = "none";
		
		level.infect_loadouts["axis_initial"]["loadoutSecondary"] = "none";
		level.infect_loadouts["axis_initial"]["loadoutSecondaryAttachment"] = "none";
		level.infect_loadouts["axis_initial"]["loadoutSecondaryAttachment2"] = "none";
		level.infect_loadouts["axis_initial"]["loadoutSecondaryBuff"] = "specialty_null";
		level.infect_loadouts["axis_initial"]["loadoutSecondaryCamo"] = "none";
		level.infect_loadouts["axis_initial"]["loadoutSecondaryReticle"] = "none";
		
		level.infect_loadouts["axis_initial"]["loadoutEquipment"] = "specialty_null";
		level.infect_loadouts["axis_initial"]["loadoutOffhand"] = "none";
		
		level.infect_loadouts["axis_initial"]["loadoutPerk1"] = "specialty_longersprint";
		level.infect_loadouts["axis_initial"]["loadoutPerk2"] = "specialty_quickdraw";
		level.infect_loadouts["axis_initial"]["loadoutPerk3"] = "specialty_bulletaccuracy";
		
		level.infect_loadouts["axis_initial"]["loadoutStreakType"] = "assault";
		level.infect_loadouts["axis_initial"]["loadoutKillstreak1"] = "none";
		level.infect_loadouts["axis_initial"]["loadoutKillstreak2"] = "none";
		level.infect_loadouts["axis_initial"]["loadoutKillstreak3"] = "none";	
		
		level.infect_loadouts["axis_initial"]["loadoutDeathstreak"] = "specialty_grenadepulldeath";	
	
		level.infect_loadouts["axis_initial"]["loadoutJuggernaut"] = false;
	}
	
	//	rogues
	if ( isUsingMatchRulesData() && GetMatchRulesData( "defaultClasses", "allies", 0, "class", "inUse" ) )
	{
		level.infect_loadouts["allies"] = getMatchRulesSpecialClass( "allies", 0 );			
	}
	else
	{
		level.infect_loadouts["allies"]["loadoutPrimary"] = "iw5_spas12";
		level.infect_loadouts["allies"]["loadoutPrimaryAttachment"] = "silencer03";
		level.infect_loadouts["allies"]["loadoutPrimaryAttachment2"] = "none";
		level.infect_loadouts["allies"]["loadoutPrimaryBuff"] = "specialty_longerrange";
		level.infect_loadouts["allies"]["loadoutPrimaryCamo"] = "none";
		level.infect_loadouts["allies"]["loadoutPrimaryReticle"] = "none";
		
		level.infect_loadouts["allies"]["loadoutSecondary"] = "none";
		level.infect_loadouts["allies"]["loadoutSecondaryAttachment"] = "none";
		level.infect_loadouts["allies"]["loadoutSecondaryAttachment2"] = "none";
		level.infect_loadouts["allies"]["loadoutSecondaryBuff"] = "specialty_null";
		level.infect_loadouts["allies"]["loadoutSecondaryCamo"] = "none";
		level.infect_loadouts["allies"]["loadoutSecondaryReticle"] = "none";
		
		level.infect_loadouts["allies"]["loadoutEquipment"] = "claymore_mp";
		level.infect_loadouts["allies"]["loadoutOffhand"] = "flash_grenade_mp";
		
		level.infect_loadouts["allies"]["loadoutPerk1"] = "specialty_scavenger";
		level.infect_loadouts["allies"]["loadoutPerk2"] = "specialty_quickdraw";
		level.infect_loadouts["allies"]["loadoutPerk3"] = "specialty_quieter";		
		
		level.infect_loadouts["allies"]["loadoutDeathstreak"] = "specialty_null";		
	
		level.infect_loadouts["allies"]["loadoutJuggernaut"] = false;			
	}	
}