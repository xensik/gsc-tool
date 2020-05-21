#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include maps\mp\gametypes\_class;
#include common_scripts\utility;

main()
{
	maps\mp\gametypes\_globallogic::init();
	maps\mp\gametypes\_callbacksetup::SetupCallbacks();
	maps\mp\gametypes\_globallogic::SetupCallbacks();
	
	//	must be done before scorelimit is set
	setGuns();

	if ( isUsingMatchRulesData() )
	{
		level.initializeMatchRules = ::initializeMatchRules;
		[[level.initializeMatchRules]]();
		level thread reInitializeMatchRulesOnMigration();	
	}
	else
	{
		registerTimeLimitDvar( level.gameType, 10 );
		SetDynamicDvar( "scr_gun_scorelimit", level.gun_guns.size );
		registerScoreLimitDvar( level.gameType, level.gun_guns.size );
		level thread reInitializeScoreLimitOnMigration();
		registerRoundLimitDvar( level.gameType, 1 );
		registerWinLimitDvar( level.gameType, 0 );
		registerNumLivesDvar( level.gameType, 0 );
		registerHalfTimeDvar( level.gameType, 0 ); 
		
		level.matchRules_randomize = 0;
		level.matchRules_damageMultiplier = 0;
		level.matchRules_vampirism = 0;
	}
	setSpecialLoadout();	
	
	level.teamBased = false;
	level.doPrematch = true;
	level.killstreakRewards = false;
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
	setCommonRulesFromMatchRulesData( true );
	
	//	set everything else (private match options, default .cfg file values, and what normally is registered in the 'else' below)			
	level.matchRules_randomize = GetMatchRulesData( "gunData", "randomize" );
	
	SetDynamicDvar( "scr_gun_scorelimit", level.gun_guns.size );
	registerScoreLimitDvar( level.gameType, level.gun_guns.size );	
	SetDynamicDvar( "scr_gun_winlimit", 1 );
	registerWinLimitDvar( "gun", 1 );
	SetDynamicDvar( "scr_gun_roundlimit", 1 );
	registerRoundLimitDvar( "gun", 1 );
	SetDynamicDvar( "scr_gun_halftime", 0 );
	registerHalfTimeDvar( "gun", 0 );
		
	SetDynamicDvar( "scr_gun_promode", 0 );
}


reInitializeScoreLimitOnMigration()
{
	SetDynamicDvar( "scr_gun_scorelimit", level.gun_guns.size );
	registerScoreLimitDvar( level.gameType, level.gun_guns.size );	
}


onPrecacheGameType()
{
	precacheString( &"MP_GUN" );
}


onStartGameType()
{
	setClientNameMode("auto_change");

	setObjectiveText( "allies", &"OBJECTIVES_DM" );
	setObjectiveText( "axis", &"OBJECTIVES_DM" );

	if ( level.splitscreen )
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_DM" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_DM" );
	}
	else
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_DM_SCORE" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_DM_SCORE" );
	}
	setObjectiveHintText( "allies", &"OBJECTIVES_DM_HINT" );
	setObjectiveHintText( "axis", &"OBJECTIVES_DM_HINT" );

	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );

	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_dm_spawn" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_dm_spawn" );

	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );		
	
	maps\mp\gametypes\_rank::registerScoreInfo( "kill", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assist", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "suicide", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "teamkill", 0 );	
	maps\mp\gametypes\_rank::registerScoreInfo( "headshot", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "execution", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "avenger", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "defender", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "posthumous", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "revenge", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "double", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "triple", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "multi", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "buzzkill", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "firstblood", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "comeback", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "longshot", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assistedsuicide", 0 );
	maps\mp\gametypes\_rank::registerScoreInfo( "knifethrow", 0 );			
	
	maps\mp\gametypes\_rank::registerScoreInfo( "gained_gun_score", 1 );
	maps\mp\gametypes\_rank::registerScoreInfo( "dropped_gun_score", -1 );
	
	maps\mp\gametypes\_rank::registerScoreInfo( "gained_gun_rank", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "dropped_enemy_gun_rank", 100 );

	allowed = [];
	maps\mp\gametypes\_gameobjects::main(allowed);

	level.QuickMessageToAll = true;
	level.blockWeaponDrops = true;
	
	//	set index on enter	
	level thread onPlayerConnect();	
	
	level.killstreakRewards = false;
}


onPlayerConnect()
{
	for ( ;; )
	{
		level waittill( "connected", player );
		
		player.gun_firstSpawn = true;
		
		player.gunGameGunIndex = 0;
		player.gunGamePrevGunIndex = 0;
		player initGunHUD();
		
		if ( level.matchRules_randomize )
		{
			player.gun_nextGuns = level.gun_guns;
			player.gun_prevGuns = [];
		}
		
		player thread refillAmmo();
		player thread refillSingleCountAmmo();
	}
}


getSpawnPoint()
{
	//	first time here?
	if ( self.gun_firstSpawn )
	{
		self.gun_firstSpawn = false;
		
		//	everyone is a gamemode class in gun, no class selection
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
	//	level.onSpawnPlayer() gets called before giveLoadout()
	//	so wait until it is done then override weapons
	self.pers["gamemodeLoadout"] = level.gun_loadouts[self.pers["team"]];
	self thread waitLoadoutDone();
	
	level notify ( "spawned_player" );	
}


waitLoadoutDone()
{	
	level endon( "game_ended" );
	self endon( "disconnect" );
	
	level waittill( "player_spawned" );
	
	self givePerk( "specialty_bling", false );
	self giveNextGun( true );
}


onPlayerKilled( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, lifeId )
{
	if ( sMeansOfDeath == "MOD_FALLING" || ( isDefined( attacker ) && isPlayer( attacker ) ) )
	{
		if ( sMeansOfDeath == "MOD_FALLING" || attacker == self || ( sMeansOfDeath == "MOD_MELEE" && sWeapon != "riotshield_mp" ) )
		{			
			self playLocalSound( "mp_war_objective_lost" );
			
			//	drop level for suicide and getting knifed
			self.gunGamePrevGunIndex = self.gunGameGunIndex;
			self.gunGameGunIndex = int( max( 0, self.gunGameGunIndex-1 ) );	
			if ( self.gunGamePrevGunIndex > self.gunGameGunIndex )	
				maps\mp\gametypes\_gamescore::givePlayerScore( "dropped_gun_score", self, undefined, true, true );
			
			if ( sMeansOfDeath == "MOD_MELEE" )
			{
				if ( self.gunGamePrevGunIndex )
				{
					attacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DROPPED_ENEMY_GUN_RANK" );
					attacker thread maps\mp\gametypes\_rank::giveRankXP( "dropped_enemy_gun_rank" );	
				}			
			}	
		}
		else if ( ( sMeansOfDeath == "MOD_PISTOL_BULLET" ) || ( sMeansOfDeath == "MOD_RIFLE_BULLET" ) || ( sMeansOfDeath == "MOD_HEAD_SHOT" ) || 
		          ( sMeansOfDeath == "MOD_PROJECTILE" ) || ( sMeansOfDeath == "MOD_PROJECTILE_SPLASH" ) || 
		          ( sMeansOfDeath == "MOD_IMPACT" ) || ( sMeansOfDeath == "MOD_GRENADE" ) || ( sMeansOfDeath == "MOD_GRENADE_SPLASH" ) ||
		          ( sMeansOfDeath == "MOD_MELEE" && sWeapon == "riotshield_mp" ) )
		{
			//	no double kills
			if ( sWeapon != attacker.primaryWeapon )
				return;		
			
			attacker.gunGamePrevGunIndex = attacker.gunGameGunIndex;
			attacker.gunGameGunIndex++;
			
			attacker thread maps\mp\gametypes\_rank::giveRankXP( "gained_gun_rank" );
			maps\mp\gametypes\_gamescore::givePlayerScore( "gained_gun_score", attacker, self, true, true );		
			
			if ( attacker.gunGameGunIndex == level.gun_guns.size-1 )
			{
				playSoundOnPlayers( "mp_enemy_obj_captured" );
				level thread teamPlayerCardSplash( "callout_top_gun_rank", attacker );
			}		
				
			if ( attacker.gunGameGunIndex < level.gun_guns.size )
			{
				attacker playLocalSound( "mp_war_objective_taken" );
				attacker giveNextGun();		
			}	
		}
	}
}


giveNextGun( doSetSpawnWeapon )
{	
	//	get the next one
	newWeapon = getNextGun();		
	self.gun_curGun = newWeapon;	//	save the base version so it's easier to compare when dropping with randomize on
	
	//	add attachments
	newWeapon = addAttachments( newWeapon );
	
	//	give gun
	self takeAllWeapons();
	_giveWeapon( newWeapon );		
	
	//	set vars
	if ( isDefined( doSetSpawnWeapon ) )
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
	
	//	use it!
	self GiveStartAmmo( newWeapon );
	self switchToWeapon( newWeapon );		
	
	//	gain/drop scoring/messaging
	if ( self.gunGamePrevGunIndex > self.gunGameGunIndex )
	{
		//	we dropped :(
		self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DROPPED_GUN_RANK" );		
	}
	else if ( self.gunGamePrevGunIndex < self.gunGameGunIndex )
	{
		//	we gained :)
		self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_GAINED_GUN_RANK" );		
	}
	self.gunGamePrevGunIndex = self.gunGameGunIndex;
	
	//	update the personal gun progress hud
	self updateGunHUD();
}


getNextGun()
{
	if ( level.matchRules_randomize )
	{
		//	gained
		if ( self.gunGamePrevGunIndex < self.gunGameGunIndex )
		{
			//	add one from new to prev
			index = randomInt( self.gun_nextGuns.size );
			newWeapon = self.gun_nextGuns[index];
			self.gun_prevGuns[self.gun_prevGuns.size] = self.gun_nextGuns[index];			
			
			//	remove it from new
			self.gun_nextGuns[index] = undefined;
			self.gun_nextGuns = array_removeUndefined( self.gun_nextGuns );
		}
		//	dropped
		else if ( self.gunGamePrevGunIndex > self.gunGameGunIndex )
		{
			//	add one from prev to new
			if ( self.gun_prevGuns.size > 1 )
			{
				for ( i=0; i<self.gun_prevGuns.size; i++ )
				{
					if ( self.gun_prevGuns[i] == self.gun_curGun )
						break;
				}
				self.gun_nextGuns[self.gun_nextGuns.size] = self.gun_prevGuns[i];
				self.gun_prevGuns[i] = undefined;
				self.gun_prevGuns = array_removeUndefined( self.gun_prevGuns );
			}
			
			//	pick a new one from prev
			index = randomInt( self.gun_prevGuns.size );
			newWeapon = self.gun_prevGuns[index];			
		}
		//	died
		else if ( self.gun_prevGuns.size )
		{
			index = randomInt( self.gun_prevGuns.size );
			newWeapon = self.gun_prevGuns[index];			
		}
		//	starting
		else
		{
			//	put a new one in the used
			index = randomInt( self.gun_nextGuns.size );
			newWeapon = self.gun_nextGuns[index];
			self.gun_prevGuns[self.gun_prevGuns.size] = self.gun_nextGuns[index];			
			
			//	remove it from new
			self.gun_nextGuns[index] = undefined;
			self.gun_nextGuns = array_removeUndefined( self.gun_nextGuns );			
		}
	}
	else
		newWeapon = level.gun_guns[self.gunGameGunIndex];
		
	return newWeapon;	
}


addAttachments( weaponName )
{
	if ( isDefined( level.gun_attachments[weaponName] ) && isDefined( level.gun_attachments[weaponName]["attach1"] ) )
		attach1 = level.gun_attachments[weaponName]["attach1"];
	else
		attach1 = "none";
	
	if ( isDefined( level.gun_attachments[weaponName] ) && isDefined( level.gun_attachments[weaponName]["attach2"] ) )
		attach2 = level.gun_attachments[weaponName]["attach2"];
	else
		attach2 = "none";	
	
	fullWeaponName = buildWeaponName( weaponName, attach1, attach2, 0, 0 );
	return fullWeaponName;	
}


onTimeLimit()
{
	level.finalKillCam_winner = "none";
	winners = getHighestProgressedPlayers();
	
	if ( !isDefined( winners ) || !winners.size )
		thread maps\mp\gametypes\_gamelogic::endGame( "tie", game["strings"]["time_limit_reached"] );	
	else if ( winners.size == 1 )
		thread maps\mp\gametypes\_gamelogic::endGame( winners[0], game["strings"]["time_limit_reached"] );
	else
	{
		if ( winners[winners.size-1].gunGameGunIndex > winners[winners.size-2].gunGameGunIndex )
			thread maps\mp\gametypes\_gamelogic::endGame( winners[winners.size-1], game["strings"]["time_limit_reached"] );
		else
			thread maps\mp\gametypes\_gamelogic::endGame( "tie", game["strings"]["time_limit_reached"] );
	}
}


getHighestProgressedPlayers()
{
	highestProgress = -1;
	highestProgressedPlayers = [];
	foreach( player in level.players )
	{
		if ( isDefined( player.gunGameGunIndex ) && player.gunGameGunIndex >= highestProgress )
		{
			highestProgress = player.gunGameGunIndex;
			highestProgressedPlayers[highestProgressedPlayers.size] = player;
		}
	}
	return highestProgressedPlayers;
}


refillAmmo()
{
	level endon( "game_ended" );
	self  endon( "disconnect" );
	
	while ( true )
	{
		self waittill( "reload" );
		self playLocalSound( "scavenger_pack_pickup" );
		self GiveStartAmmo( (level.gun_guns[self.gunGameGunIndex]+"_mp") );
	}	
}


refillSingleCountAmmo()
{
	level endon( "game_ended" );
	self  endon( "disconnect" );
	
	while ( true )
	{
		if ( isDefined( self.primaryWeapon ) && self getAmmoCount( self.primaryWeapon ) == 0 )
		{
			//	fake a reload time
			wait( 2 );
			self notify( "reload" );
			wait( 1 );
		}
		else
			wait( 0.05 );
	}	
}


initGunHUD()
{
	self.gun_progressDisplay[0] = self createFontString( "small", 1.6 );	
	self.gun_progressDisplay[0] setPoint( "TOP LEFT", "TOP LEFT", 115, 5 );
	self.gun_progressDisplay[0] setText( &"MP_WEAPON" );
	self.gun_progressDisplay[0].alpha = 1;
	self.gun_progressDisplay[0].archived = false;
	self.gun_progressDisplay[0].hideWhenInMenu = true;	
	
	self.gun_progressDisplay[1] = self createFontString( "small", 1.6 );		
	self.gun_progressDisplay[1] setPoint( "TOP LEFT", "TOP LEFT", 115, 23 );
	self.gun_progressDisplay[1] setText( "1 / " + level.gun_guns.size );
	self.gun_progressDisplay[1].alpha = 1;
	self.gun_progressDisplay[1].archived = false;
	self.gun_progressDisplay[1].hideWhenInMenu = true;	
	
	self thread hideOnGameEnd( self.gun_progressDisplay );	
}


updateGunHUD()
{
	self.gun_progressDisplay[1] setText( (self.gunGameGunIndex+1) + " / " + level.gun_guns.size );
}


hideOnGameEnd( hudElems )
{
	self endon( "disconnect" );
	level waittill("game_ended");
	
	foreach ( hudElem in hudElems )
		hudElem.alpha = 0;
}


setGuns()
{	
	level.gun_guns = [];
	
	numGuns = 0;
	if ( isUsingMatchRulesData() )
		numGuns = GetMatchRulesData( "gunData", "numGuns" );
		
	if ( numGuns )
	{
		for ( i=0; i<numGuns; i++ )
			level.gun_guns[i] = GetMatchRulesData( "gunData", "guns", i );	
	}
	else
	{	
		//	hand guns
		level.gun_guns[0]  = "iw5_deserteagle";	
		//	machine pistols
		level.gun_guns[1]  = "iw5_g18";
		level.gun_guns[2]  = "iw5_mp9";
		//	sub
		level.gun_guns[3]  = "iw5_mp5";
		level.gun_guns[4]  = "iw5_p90";
		level.gun_guns[5]  = "iw5_mp7";			
		//	assault - auto
		level.gun_guns[6]  = "iw5_ak47";
		level.gun_guns[7]  = "iw5_g36c";
		level.gun_guns[8]  = "iw5_scar";		
		//	lmg
		level.gun_guns[9]  = "iw5_pecheneg";
		level.gun_guns[10] = "iw5_mg36";
		//	shotgun
		level.gun_guns[11] = "iw5_spas12";
		level.gun_guns[12] = "iw5_aa12";
		level.gun_guns[13] = "iw5_1887";
		//	assault - burst
		level.gun_guns[14] = "iw5_type95";
		level.gun_guns[15] = "iw5_mk14";	
		//	sniper
		level.gun_guns[16] = "iw5_barrett";
		level.gun_guns[17] = "iw5_msr";	
		//	launcher
		level.gun_guns[18] = "xm25";
		level.gun_guns[19] = "javelin";
	}	
	
	//	default attachments for all guns that take them
	level.gun_attachments = [];
	//	pistol
	level.gun_attachments["iw5_44magnum"]["attach1"] = "tactical";
	level.gun_attachments["iw5_usp45"]["attach1"] = "xmags";
	level.gun_attachments["iw5_deserteagle"]["attach1"] = "tactical";
	level.gun_attachments["iw5_mp412"]["attach1"] = "tactical";
	level.gun_attachments["iw5_p99"]["attach1"] = "xmags";
	level.gun_attachments["iw5_fnfiveseven"]["attach1"] = "xmags";
	//	machine pistol
	level.gun_attachments["iw5_fmg9"]["attach1"] = "reflex";
	level.gun_attachments["iw5_skorpion"]["attach1"] = "reflex";
	level.gun_attachments["iw5_mp9"]["attach1"] = "reflex";
	level.gun_attachments["iw5_g18"]["attach1"] = "reflex";
	//	smg
	level.gun_attachments["iw5_mp5"]["attach1"] = "reflex";
	level.gun_attachments["iw5_mp5"]["attach2"] = "xmags";
	level.gun_attachments["iw5_m9"]["attach1"] = "reflex";
	level.gun_attachments["iw5_m9"]["attach2"] = "xmags";
	level.gun_attachments["iw5_p90"]["attach1"] = "reflex";
	level.gun_attachments["iw5_p90"]["attach2"] = "xmags";
	level.gun_attachments["iw5_pp90m1"]["attach1"] = "reflex";
	level.gun_attachments["iw5_pp90m1"]["attach2"] = "xmags";
	level.gun_attachments["iw5_ump45"]["attach1"] = "reflex";
	level.gun_attachments["iw5_ump45"]["attach2"] = "xmags";
	level.gun_attachments["iw5_mp7"]["attach1"] = "reflex";
	level.gun_attachments["iw5_mp7"]["attach2"] = "xmags";
	//	assault
	level.gun_attachments["iw5_ak47"]["attach1"] = "reflex";
	level.gun_attachments["iw5_ak47"]["attach2"] = "xmags";
	level.gun_attachments["iw5_m16"]["attach1"] = "reflex";
	level.gun_attachments["iw5_m16"]["attach2"] = "xmags";
	level.gun_attachments["iw5_m4"]["attach1"] = "reflex";
	level.gun_attachments["iw5_m4"]["attach2"] = "xmags";
	level.gun_attachments["iw5_fad"]["attach1"] = "reflex";
	level.gun_attachments["iw5_fad"]["attach2"] = "xmags";
	level.gun_attachments["iw5_acr"]["attach1"] = "reflex";
	level.gun_attachments["iw5_acr"]["attach2"] = "xmags";
	level.gun_attachments["iw5_type95"]["attach1"] = "reflex";
	level.gun_attachments["iw5_type95"]["attach2"] = "xmags";
	level.gun_attachments["iw5_mk14"]["attach1"] = "reflex";
	level.gun_attachments["iw5_mk14"]["attach2"] = "xmags";
	level.gun_attachments["iw5_scar"]["attach1"] = "reflex";
	level.gun_attachments["iw5_scar"]["attach2"] = "xmags";
	level.gun_attachments["iw5_g36c"]["attach1"] = "reflex";
	level.gun_attachments["iw5_g36c"]["attach2"] = "xmags";
	level.gun_attachments["iw5_cm901"]["attach1"] = "reflex";
	level.gun_attachments["iw5_cm901"]["attach2"] = "xmags";
	//	sniper
	level.gun_attachments["iw5_dragunov"]["attach1"] = "xmags";
	level.gun_attachments["iw5_msr"]["attach1"] = "xmags";
	level.gun_attachments["iw5_barrett"]["attach1"] = "xmags";
	level.gun_attachments["iw5_rsass"]["attach1"] = "xmags";
	level.gun_attachments["iw5_as50"]["attach1"] = "xmags";
	level.gun_attachments["iw5_l96a1"]["attach1"] = "xmags";
	//	shotgun
	level.gun_attachments["iw5_ksg"]["attach1"] = "grip";
	level.gun_attachments["iw5_ksg"]["attach2"] = "xmags";
	level.gun_attachments["iw5_striker"]["attach1"] = "grip";
	level.gun_attachments["iw5_striker"]["attach2"] = "xmags";
	level.gun_attachments["iw5_aa12"]["attach1"] = "grip";
	level.gun_attachments["iw5_aa12"]["attach2"] = "xmags";
	level.gun_attachments["iw5_usas12"]["attach1"] = "grip";
	level.gun_attachments["iw5_usas12"]["attach2"] = "xmags";
	level.gun_attachments["iw5_spas12"]["attach1"] = "grip";
	level.gun_attachments["iw5_spas12"]["attach2"] = "xmags";
	//	lmg
	level.gun_attachments["iw5_m60"]["attach1"] = "grip";
	level.gun_attachments["iw5_m60"]["attach2"] = "reflex";
	level.gun_attachments["iw5_mk46"]["attach1"] = "grip";
	level.gun_attachments["iw5_mk46"]["attach2"] = "reflex";
	level.gun_attachments["iw5_pecheneg"]["attach1"] = "grip";
	level.gun_attachments["iw5_pecheneg"]["attach2"] = "reflex";
	level.gun_attachments["iw5_sa80"]["attach1"] = "grip";
	level.gun_attachments["iw5_sa80"]["attach2"] = "reflex";
	level.gun_attachments["iw5_mg36"]["attach1"] = "grip";
	level.gun_attachments["iw5_mg36"]["attach2"] = "reflex";
}


setSpecialLoadout()
{	
	//	no killstreaks defined for special classes		
	level.gun_loadouts["axis"]["loadoutPrimary"] = "iw5_acr";	//  can't use "none" for primary, this is replaced on spawn anyway
	level.gun_loadouts["axis"]["loadoutPrimaryAttachment"] = "none";
	level.gun_loadouts["axis"]["loadoutPrimaryAttachment2"] = "none";
	level.gun_loadouts["axis"]["loadoutPrimaryBuff"] = "specialty_null";
	level.gun_loadouts["axis"]["loadoutPrimaryCamo"] = "none";
	level.gun_loadouts["axis"]["loadoutPrimaryReticle"] = "none";
	
	level.gun_loadouts["axis"]["loadoutSecondary"] = "none";
	level.gun_loadouts["axis"]["loadoutSecondaryAttachment"] = "none";
	level.gun_loadouts["axis"]["loadoutSecondaryAttachment2"] = "none";
	level.gun_loadouts["axis"]["loadoutSecondaryBuff"] = "specialty_null";
	level.gun_loadouts["axis"]["loadoutSecondaryCamo"] = "none";
	level.gun_loadouts["axis"]["loadoutSecondaryReticle"] = "none";
	
	level.gun_loadouts["axis"]["loadoutEquipment"] = "specialty_null";
	level.gun_loadouts["axis"]["loadoutOffhand"] = "none";
	
	level.gun_loadouts["axis"]["loadoutPerk1"] = "specialty_null";
	level.gun_loadouts["axis"]["loadoutPerk2"] = "specialty_null";
	level.gun_loadouts["axis"]["loadoutPerk3"] = "specialty_null";
	
	level.gun_loadouts["axis"]["loadoutDeathstreak"] = "specialty_null";
	
	level.gun_loadouts["axis"]["loadoutJuggernaut"]	= false;
	
	//	FFA games don't have teams, but players are allowed to choose team on the way in
	//	just for character model and announcer voice variety.  Same loadout for both.	
	level.gun_loadouts["allies"] = level.gun_loadouts["axis"];
}