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
		registerScoreLimitDvar( level.gameType, 0 );
		registerRoundLimitDvar( level.gameType, 1 );
		registerWinLimitDvar( level.gameType, 1 );
		registerNumLivesDvar( level.gameType, 2 );
		registerHalfTimeDvar( level.gameType, 0 ); 
		
		level.matchRules_damageMultiplier = 0;
		level.matchRules_vampirism = 0;		
		level.matchRules_oneShotKill = false;
		
		level.matchRules_initialAmmo = 2;
		level.matchRules_rewardAmmo = 2;	
	}
	SetDynamicDvar( "scr_player_maxhealth", 100 );
	SetDynamicDvar( "scr_game_onlyheadshots", 0 );
	SetDynamicDvar( "scr_game_hardpoints", 0 );
	SetDynamicDvar( "scr_player_healthregentime", 5 );	
	
	setGun();
	setSpecialLoadouts();
	
	level.teamBased = false;
	level.doPrematch = true;
	level.killstreakRewards = false;
	level.onStartGameType = ::onStartGameType;
	level.onSpawnPlayer = ::onSpawnPlayer;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onPlayerKilled = ::onPlayerKilled;
	level.onOneLeftEvent = ::onOneLeftEvent;
	if ( level.matchRules_oneShotKill )
		level.modifyPlayerDamage = ::modifyPlayerDamage; 
}


initializeMatchRules()
{
	//	set common values
	setCommonRulesFromMatchRulesData( true );
	
	//	set everything else (private match options, default .cfg file values, and what normally is registered in the 'else' below)	
	level.matchRules_initialAmmo = GetMatchRulesData( "oicData", "initialAmmoCount" );
	level.matchRules_rewardAmmo = GetMatchRulesData( "oicData", "killRewardAmmoCount" );
	level.matchRules_oneShotKill = GetMatchRulesData( "oicData", "oneShotKill" );	
	
	//	neither are accessible in game options screen for this mode but reset in case there is junk data
	level.matchRules_damageMultiplier = 0;
	level.matchRules_vampirism = 0;					
	
	SetDynamicDvar( "scr_oic_winlimit", 1 );
	registerWinLimitDvar( "oic", 1 );
	SetDynamicDvar( "scr_oic_roundlimit", 1 );
	registerRoundLimitDvar( "oic", 1 );
	SetDynamicDvar( "scr_oic_halftime", 0 );
	registerHalfTimeDvar( "oic", 0 );
		
	SetDynamicDvar( "scr_oic_promode", 0 );	
	
	SetDynamicDvar( "scr_player_maxhealth", 100 );
	SetDynamicDvar( "scr_game_onlyheadshots", 0 );
	SetDynamicDvar( "scr_game_hardpoints", 0 );
	SetDynamicDvar( "scr_player_healthregentime", 5 );	
}


onStartGameType()
{
	setClientNameMode("auto_change");

	setObjectiveText( "allies", &"OBJECTIVES_OIC" );
	setObjectiveText( "axis", &"OBJECTIVES_OIC" );

	if ( level.splitscreen )
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_OIC" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_OIC" );
	}
	else
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_OIC_SCORE" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_OIC_SCORE" );
	}
	setObjectiveHintText( "allies", &"OBJECTIVES_OIC_HINT" );
	setObjectiveHintText( "axis", &"OBJECTIVES_OIC_HINT" );

	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );

	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_dm_spawn" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_dm_spawn" );

	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );

	allowed = [];
	maps\mp\gametypes\_gameobjects::main(allowed);
	
	maps\mp\gametypes\_rank::registerScoreInfo( "kill", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "headshot", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assist", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "suicide", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "teamkill", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "survivor", 25 );

	level.QuickMessageToAll = true;	
	level.blockWeaponDrops = true;
	
	level thread onPlayerConnect();

	level thread watchElimination();	
	
	level.killstreakRewards = false;
}


onPlayerConnect()
{
	for ( ;; )
	{
		level waittill( "connected", player );
		
		player.oic_firstSpawn = true;
	}
}


getSpawnPoint()
{
	//	first time here?
	if ( self.oic_firstSpawn )
	{
		self.oic_firstSpawn = false;
		
		//	everyone is a gamemode class in oic, no class selection
		self.pers["class"] = "gamemode";
		self.pers["lastClass"] = "";
		self.class = self.pers["class"];
		self.lastClass = self.pers["lastClass"];	
	}	
	
	spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( self.pers["team"] );
	spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_DM( spawnPoints );

	return spawnPoint;
}


onSpawnPlayer()
{
	//	award ammo that the player might have been waiting to receive on death
	if ( isDefined( self.oic_rewardAmmo ) && self.oic_rewardAmmo )
		self giveAmmo();
	else
		self.oic_rewardAmmo = 0;	
	
	//	level.onSpawnPlayer() gets called before giveLoadout()
	//	so wait until it is done then override weapons
	self.pers["gamemodeLoadout"] = level.oic_loadouts[self.pers["team"]];
	self thread waitLoadoutDone();
	
	level notify ( "spawned_player" );	
}

waitLoadoutDone()
{	
	level endon( "game_ended" );
	self endon( "disconnect" );
	
	level waittill( "player_spawned" );
	
	//	clear temp data
	self takeAllWeapons();
	
	//	give gun
	newWeapon = level.oic_gun + "_mp";
	_giveWeapon( newWeapon );		
	self switchToWeapon( newWeapon );
	self setSpawnWeapon( newWeapon );
	
	weaponTokens = StrTok( newWeapon, "_" );	
	if ( weaponTokens[0] == "iw5" )
		weaponName = weaponTokens[0] + "_" + weaponTokens[1];
	else if ( weaponTokens[0] == "alt" )
		weaponName = weaponTokens[1] + "_" + weaponTokens[2];
	else
		weaponName = weaponTokens[0];	
	self.pers["primaryWeapon"] = weaponName;	
		
	self.primaryWeapon = newWeapon;
	
	//	give ammo	
	clipAmmo = level.matchRules_initialAmmo;
	if( isDefined( self.pers["clip_ammo"] ) )
	{
		clipAmmo = self.pers["clip_ammo"];
		self.pers["clip_ammo"] = undefined;
	}
	self SetWeaponAmmoClip( self.primaryWeapon, clipAmmo );

	stockAmmo = 0;
	if( isDefined( self.pers["stock_ammo"] ) )
	{
		stockAmmo = self.pers["stock_ammo"];
		self.pers["stock_ammo"] = undefined;
	}
	self SetWeaponAmmoStock( self.primaryWeapon, stockAmmo );	
	
	//	give knife
	//self SetOffhandPrimaryClass( "throwingknife" );
	//_giveWeapon( "throwingknife_mp" );		
}


modifyPlayerDamage( victim, eAttacker, iDamage, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc )
{
	if ( ( sMeansOfDeath == "MOD_PISTOL_BULLET" ) || ( sMeansOfDeath == "MOD_RIFLE_BULLET" ) || ( sMeansOfDeath == "MOD_HEAD_SHOT" ) )	
		iDamage = 999;

	return iDamage;
}


onPlayerKilled( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, lifeId )
{
	if ( isDefined( attacker ) && isPlayer( attacker ) && self != attacker )
	{
		attacker.oic_rewardAmmo += level.matchRules_rewardAmmo;
		if ( self attackButtonPressed() )
			attacker thread waitGiveAmmo();
		else
			attacker giveAmmo();		
	}
}


onOneLeftEvent( team )
{
	lastPlayer = getLastLivingPlayer();
	
	logString( "last one alive, win: " + lastPlayer.name );
	level.finalKillCam_winner = "none";
	level thread maps\mp\gametypes\_gamelogic::endGame( lastPlayer, &"MP_ENEMIES_ELIMINATED" );	
}


waitGiveAmmo()
{
	self endon( "death" );
	self endon( "disconnect" );
	level endon( "game_ended" );
	
	self notify( "oic_waitGiveAmmo" );
	self  endon( "oic_waitGiveAmmo" );
	
	
	while( self attackButtonPressed() )
		wait( 0.05 );
	
	giveAmmo();
}


giveAmmo()
{
	currentWeapon = self getCurrentWeapon();
	clipAmmo = self GetWeaponAmmoClip( currentWeapon );
	self SetWeaponAmmoClip( currentWeapon, clipAmmo + self.oic_rewardAmmo );
	self playLocalSound( "scavenger_pack_pickup" );
	
	self.oic_rewardAmmo = 0;
}


watchElimination()
{
	level endon( "game_ended" );
	
	for ( ;; )
	{
		level waittill( "player_eliminated", player );
		
		thread teamPlayerCardSplash( "callout_eliminated", player );
		
		remainingPlayers = [];
		foreach ( player in level.players )
		{
			if ( IsDefined( player ) && ( IsAlive( player ) || player.pers["lives"] > 0 ) )
			{
				remainingPlayers[remainingPlayers.size] = player;				
				player thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_SURVIVOR" );
				maps\mp\gametypes\_gamescore::givePlayerScore( "survivor", player, undefined, true );
				player thread maps\mp\gametypes\_rank::giveRankXP( "survivor" );
			}
		}
		
		if ( remainingPlayers.size > 2 )
		{
			playSoundOnPlayers( "mp_enemy_obj_captured" );
		}
		else if ( remainingPlayers.size == 2 )
		{
			playSoundOnPlayers( "mp_obj_captured" );
			
			remainingPlayers[0] thread maps\mp\gametypes\_hud_message::playerCardSplashNotify( "callout_lastenemyalive", remainingPlayers[1] );
			remainingPlayers[1] thread maps\mp\gametypes\_hud_message::playerCardSplashNotify( "callout_lastenemyalive", remainingPlayers[0] );
		}
	}
}


setGun()
{	
	level.oic_gun = undefined;
	
	gun = "none";
	if ( isUsingMatchRulesData() )
		gun = GetMatchRulesData( "oicData", "weapon" );
		
	if ( isDefined( gun ) && gun != "none" )
	{
		level.oic_gun = gun;	
	}
	else
	{	
		level.oic_gun = "iw5_g18_mp";	
	}
}


setSpecialLoadouts()
{	
	//	no killstreaks defined for special classes		
	level.oic_loadouts["axis"]["loadoutPrimary"] = "iw5_acr";	//  can't use "none" for primary, this is replaced on spawn anyway
	level.oic_loadouts["axis"]["loadoutPrimaryAttachment"] = "none";
	level.oic_loadouts["axis"]["loadoutPrimaryAttachment2"] = "none";
	level.oic_loadouts["axis"]["loadoutPrimaryBuff"] = "specialty_null";
	level.oic_loadouts["axis"]["loadoutPrimaryCamo"] = "none";
	level.oic_loadouts["axis"]["loadoutPrimaryReticle"] = "none";
	
	level.oic_loadouts["axis"]["loadoutSecondary"] = "none";
	level.oic_loadouts["axis"]["loadoutSecondaryAttachment"] = "none";
	level.oic_loadouts["axis"]["loadoutSecondaryAttachment2"] = "none";
	level.oic_loadouts["axis"]["loadoutSecondaryBuff"] = "specialty_null";
	level.oic_loadouts["axis"]["loadoutSecondaryCamo"] = "none";
	level.oic_loadouts["axis"]["loadoutSecondaryReticle"] = "none";
	
	level.oic_loadouts["axis"]["loadoutEquipment"] = "specialty_null";
	level.oic_loadouts["axis"]["loadoutOffhand"] = "none";
	
	level.oic_loadouts["axis"]["loadoutPerk1"] = "specialty_null";
	level.oic_loadouts["axis"]["loadoutPerk2"] = "specialty_null";
	level.oic_loadouts["axis"]["loadoutPerk3"] = "specialty_null";
	
	level.oic_loadouts["axis"]["loadoutDeathstreak"] = "specialty_null";
	
	level.oic_loadouts["axis"]["loadoutJuggernaut"]	= false;	
	
	//	FFA games don't have teams, but players are allowed to choose team on the way in
	//	just for character model and announcer voice variety.  Same loadout for both.	
	level.oic_loadouts["allies"] = level.oic_loadouts["axis"];
}