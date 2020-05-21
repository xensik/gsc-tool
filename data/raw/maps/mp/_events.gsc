#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

init()
{
	maps\mp\gametypes\_rank::registerScoreInfo( "headshot", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "execution", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "avenger", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "defender", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "posthumous", 25 );
	maps\mp\gametypes\_rank::registerScoreInfo( "revenge", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "double", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "triple", 75 );
	maps\mp\gametypes\_rank::registerScoreInfo( "multi", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "buzzkill", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "firstblood", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "comeback", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "longshot", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "assistedsuicide", 100 );
	maps\mp\gametypes\_rank::registerScoreInfo( "knifethrow", 100 );

	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "damage", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "heavy_damage", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "damaged", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "kill", 1 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "killed", 0 );
	
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "healed", 0);
	
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "headshot", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "melee", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "backstab", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "longshot", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "assistedsuicide", 0);
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "defender", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "avenger", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "execution", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "comeback", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "revenge", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "buzzkill", 0 );	
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "double", 0 );	
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "triple", 0 );	
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "multi", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "assist", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "firstBlood", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "capture", 1);
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "assistedCapture", 1 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "plant", 1);
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "defuse", 1);
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "vehicleDestroyed", 1 );

	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "3streak", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "4streak", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "5streak", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "6streak", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "7streak", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "8streak", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "9streak", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "10streak", 0 );
	maps\mp\killstreaks\_killstreaks::registerAdrenalineInfo( "regen", 0 );

	precacheShader( "crosshair_red" );

	level._effect["money"] = loadfx ("props/cash_player_drop");
	
	level.numKills = 0;

	level thread onPlayerConnect();	
}


onPlayerConnect()
{
	for(;;)
	{
		level waittill( "connected", player );
		
		player.killedPlayers = [];
		player.killedPlayersCurrent = [];
		player.killedBy = [];
		player.lastKilledBy = undefined;
		player.greatestUniquePlayerKills = 0;
		
		player.recentKillCount = 0;
		player.lastKillTime = 0;
		player.damagedPlayers = [];	
		
		player thread monitorCrateJacking();
		player thread monitorObjectives();
		player thread monitorHealed();
	}
}

damagedPlayer( victim, damage, weapon )
{
	if ( damage < 50  && damage > 10 )
		self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "damage" );
	else
		self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "heavy_damage" );
}


killedPlayer( killId, victim, weapon, meansOfDeath )
{
	victimGuid = victim.guid;
	myGuid = self.guid;
	curTime = getTime();
	
	self thread updateRecentKills( killId );
	self.lastKillTime = getTime();
	self.lastKilledPlayer = victim;

	self.modifiers = [];

	level.numKills++;

	// a player is either damaged, or killed; never both
	self.damagedPlayers[victimGuid] = undefined;	
	
	if ( !isKillstreakWeapon( weapon ) && !self isJuggernaut() && !self _hasPerk( "specialty_explosivebullets" ) ) 
	{
		if ( weapon == "none" )
			return false;
		
		if ( isDefined( self.pers["copyCatLoadout"] ) && isDefined( self.pers["copyCatLoadout"]["owner"] ) )
		{
			if ( victim == self.pers["copyCatLoadout"]["owner"] )
				self.modifiers["clonekill"] = true;
		} 
		
		// added a failsafe here because this could be the victim killing themselves with something like the dead man's hand deathstreak
		if ( victim.attackers.size == 1 && !IsDefined( victim.attackers[victim.guid] ) )
		{
			/#
			if ( !isDefined( victim.attackers[self.guid] ) )
			{
				println("Weapon: "+ weapon );
				println("Attacker GUID:" + self.guid );
				
				foreach ( key,value in victim.attackers )
					println( "Victim Attacker list GUID: " + key );
			}
			#/
			assertEx( isDefined( victim.attackers[self.guid] ), "See console log for details" );
			
			weaponClass = getWeaponClass( weapon );
						
			if( weaponClass == "weapon_sniper" && 
				meansOfDeath != "MOD_MELEE" &&
				getTime() == victim.attackerData[self.guid].firstTimeDamaged )
			{
				self.modifiers["oneshotkill"] = true;
				self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_ONE_SHOT_KILL" );
			}
		}

		if ( isDefined( victim.throwingGrenade ) && victim.throwingGrenade == "frag_grenade_mp" )
			self.modifiers["cooking"] = true;
		
		if ( isDefined(self.assistedSuicide) && self.assistedSuicide )
			self assistedSuicide( killId, weapon, meansOfDeath );
		
		if ( level.numKills == 1 )
			self firstBlood( killId, weapon, meansOfDeath );
			
		if ( self.pers["cur_death_streak"] > 3 )
			self comeBack( killId, weapon, meansOfDeath );
			
		if ( meansOfDeath == "MOD_HEAD_SHOT" )
		{
			if ( isDefined( victim.lastStand ) )
				execution( killId, weapon, meansOfDeath );
			else
				headShot( killId, weapon, meansOfDeath );
		}
			
		if ( isDefined(self.wasti) && self.wasti && getTime() - self.spawnTime <= 5000 )
			self.modifiers["jackintheboxkill"] = true;
		
		if ( !isAlive( self ) && self.deathtime + 800 < getTime() )
			postDeathKill( killId );
		
		fakeAvenge = false;
		if ( level.teamBased && curTime - victim.lastKillTime < 500 )
		{
			if ( victim.lastkilledplayer != self )
				self avengedPlayer( killId, weapon, meansOfDeath );		
		}
	
		foreach ( guid, damageTime in victim.damagedPlayers )
		{
			if ( guid == self.guid )
				continue;
	
			if ( level.teamBased && curTime - damageTime < 500 )
				self defendedPlayer( killId, weapon, meansOfDeath );
		}
	
		if ( isDefined( victim.attackerPosition ) )
			attackerPosition = victim.attackerPosition;
		else
			attackerPosition = self.origin;
	
		if( isLongShot( self, weapon, meansOfDeath, attackerPosition, victim ) )
			self thread longshot( killId, weapon, meansOfDeath );
		
		/*get proximity assists and kills
		if ( isDefined(self.proximityActive) && self.proximityActive )
		{
			savedId = undefined;
			
			foreach( player in level.players )
			{
				if ( !isDefined( player ) )
					continue;
				
				if ( player.team != self.team )
					continue;
				
				if ( !isReallyAlive( player ) ) 
					continue;
				
				if ( !isReallyAlive( self ) )
					continue;
				
				if ( player == self )
					continue;
				
				//distance = DistanceSquared( player.origin, self.origin );
				
				if ( DistanceSquared( player.origin, self.origin ) < 262144 ) //512^2  (in proximity)
				{
					player proximityAssist( killId );
					
					if ( !isDefined( savedId ) || killID != savedId )
						self proximityKill( killId );
					
					savedId = killId;
				}
			}
		} */
		
		if ( victim.pers[ "cur_kill_streak" ] > 0 && isDefined( victim.killstreaks[ victim.pers["cur_kill_streak"] + 1 ] ) )
		{
			// playercard splash for the killstreak stopped
			self buzzKill( killId, victim, weapon, meansOfDeath );
		}
			
		self thread checkMatchDataKills( killId, victim, weapon, meansOfDeath);
		
	}

	if ( !isDefined( self.killedPlayers[victimGuid] ) )
		self.killedPlayers[victimGuid] = 0;

	if ( !isDefined( self.killedPlayersCurrent[victimGuid] ) )
		self.killedPlayersCurrent[victimGuid] = 0;
		
	if ( !isDefined( victim.killedBy[myGuid] ) )
		victim.killedBy[myGuid] = 0;

	self.killedPlayers[victimGuid]++;
	
	//this sets player stat for routine customer award
	if ( self.killedPlayers[victimGuid] > self.greatestUniquePlayerKills )
		self setPlayerStat( "killedsameplayer", self.killedPlayers[victimGuid] );
	
	self.killedPlayersCurrent[victimGuid]++;		
	victim.killedBy[myGuid]++;	

	victim.lastKilledBy = self;		
}

isLongShot( attacker, weapon, meansOfDeath, attackerPosition, victim )
{
	if( isAlive( attacker ) && 
		!attacker isUsingRemote() && 
		( meansOfDeath == "MOD_RIFLE_BULLET" || meansOfDeath == "MOD_PISTOL_BULLET" || meansOfDeath == "MOD_HEAD_SHOT" ) && 
		!isKillstreakWeapon( weapon ) && !isDefined( attacker.assistedSuicide ) )
	{
		// check depending on the weapon being used to kill
		weaponClass = getWeaponClass( weapon );
		switch( WeaponClass )
		{
		case "weapon_pistol":
			weapDist = 800;
			break;
		case "weapon_machine_pistol":
		case "weapon_smg":
			weapDist = 1200;
			break;
		case "weapon_assault":
		case "weapon_lmg":
			weapDist = 1500;
			break;
		case "weapon_sniper":
			weapDist = 2000;
			break;
		case "weapon_shotgun":
			weapDist = 500;
			break;
		case "weapon_projectile":
		default:
			weapDist = 1536; // the old number
			break;
		}

		if( distance( attackerPosition, victim.origin ) > weapDist )
		{
			if( attacker IsItemUnlocked( "specialty_holdbreath" ) && attacker _hasPerk( "specialty_holdbreath" ) )
				attacker maps\mp\gametypes\_missions::processChallenge( "ch_longdistance" );
			
			return true;
		}
	}

	return false;
}

checkMatchDataKills( killId, victim, weapon, meansOfDeath )
{
	weaponClass = getWeaponClass( weapon );
	alreadyUsed = false;
	
	self thread camperCheck();
	
	if ( isDefined( self.lastKilledBy ) && self.lastKilledBy == victim )
	{
		self.lastKilledBy = undefined;
		self revenge( killId );

		playFx( level._effect["money"], victim getTagOrigin( "j_spine4" ) );
	}

	if ( victim.iDFlags & level.iDFLAGS_PENETRATION )
		self incPlayerStat( "bulletpenkills", 1 );
	
	if ( self.pers["rank"] < victim.pers["rank"] )
		self incPlayerStat( "higherrankkills", 1 );
	
	if ( self.pers["rank"] > victim.pers["rank"] )
		self incPlayerStat( "lowerrankkills", 1 );
	
	if ( isDefined( self.inFinalStand ) && self.inFinalStand )
		self incPlayerStat( "laststandkills", 1 );
	
	if ( isDefined( victim.inFinalStand ) && victim.inFinalStand )
		self incPlayerStat( "laststanderkills", 1 );
	
	if ( self getCurrentWeapon() != self.primaryWeapon && self getCurrentWeapon() != self.secondaryWeapon )
		self incPlayerStat( "otherweaponkills", 1 );

	timeAlive = getTime() - victim.spawnTime ;
	
	if( !matchMakingGame() )
		victim setPlayerStatIfLower( "shortestlife", timeAlive );
		
	victim setPlayerStatIfGreater( "longestlife", timeAlive );
	
	if( meansOfDeath != "MOD_MELEE" )
	{
		switch( weaponClass )
		{
		case "weapon_pistol":
		case "weapon_smg":
		case "weapon_assault":
		case "weapon_projectile":
		case "weapon_sniper":
		case "weapon_shotgun":
		case "weapon_lmg":
			self checkMatchDataWeaponKills( victim, weapon, meansOfDeath, weaponClass );
			break;
		case "weapon_grenade":
		case "weapon_explosive":
			self checkMatchDataEquipmentKills( victim, weapon, meansOfDeath );
			break;
		default:
			break;
		}
	}
}

// Need to make sure these only apply to kills of an enemy, not friendlies or yourself
checkMatchDataWeaponKills( victim, weapon, meansOfDeath, weaponType )
{
	attacker = self;
	kill_ref = undefined;
	headshot_ref = undefined;
	death_ref = undefined;
	
	switch( weaponType )
	{
		case "weapon_pistol":
			kill_ref = "pistolkills";
			headshot_ref = "pistolheadshots";
			break;	
		case "weapon_smg":
			kill_ref = "smgkills";
			headshot_ref = "smgheadshots";
			break;
		case "weapon_assault":
			kill_ref = "arkills";
			headshot_ref = "arheadshots";
			break;
		case "weapon_projectile":
			if ( weaponClass( weapon ) == "rocketlauncher" )
				kill_ref = "rocketkills";
			break;
		case "weapon_sniper":
			kill_ref = "sniperkills";
			headshot_ref = "sniperheadshots";
			break;
		case "weapon_shotgun":
			kill_ref = "shotgunkills";
			headshot_ref = "shotgunheadshots";
			death_ref = "shotgundeaths";
			break;
		case "weapon_lmg":
			kill_ref = "lmgkills";
			headshot_ref = "lmgheadshots";
			break;
		default:
			break;
	}

	if ( isDefined ( kill_ref ) )
		attacker incPlayerStat( kill_ref, 1 );

	if ( isDefined ( headshot_ref ) && meansOfDeath == "MOD_HEAD_SHOT" )
		attacker incPlayerStat( headshot_ref, 1 );

	if ( isDefined ( death_ref ) && !matchMakingGame() )
		victim incPlayerStat( death_ref, 1 );
		
	if ( attacker PlayerAds() > 0.5 ) 
	{
		attacker incPlayerStat( "adskills", 1 );

		if ( weaponType == "weapon_sniper" || isSubStr( weapon, "acog" ) )
			attacker incPlayerStat( "scopedkills", 1 );
		
		if ( isSubStr( weapon, "thermal" ) )
			attacker incPlayerStat( "thermalkills", 1 );
	}
	else
	{
		attacker incPlayerStat( "hipfirekills", 1 );
	}
}

// Need to make sure these only apply to kills of an enemy, not friendlies or yourself
checkMatchDataEquipmentKills( victim, weapon, meansOfDeath )
{	
	attacker = self;
	
	// equipment kills
	switch( weapon )
	{
		case "frag_grenade_mp":
			attacker incPlayerStat( "fragkills", 1 );
			attacker incPlayerStat( "grenadekills", 1 );
			isEquipment = true;
			break;	
		case "c4_mp":
			attacker incPlayerStat( "c4kills", 1 );
			isEquipment = true;
			break;
		case "semtex_mp":
			attacker incPlayerStat( "semtexkills", 1 );
			attacker incPlayerStat( "grenadekills", 1 );
			isEquipment = true;
			break;
		case "claymore_mp":
			attacker incPlayerStat( "claymorekills", 1 );
			isEquipment = true;
			break;
		case "throwingknife_mp":
			attacker incPlayerStat( "throwingknifekills", 1 );			
			self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_KNIFETHROW" );			
			isEquipment = true;
			break;
		default:
			isEquipment = false;
			break;
	}
	
	if ( isEquipment )
		attacker incPlayerStat( "equipmentkills", 1 );
}

camperCheck()
{
	self.lastKillWasCamping = false;
	if ( !isDefined ( self.lastKillLocation ) )
	{
		self.lastKillLocation = self.origin;	
		self.lastCampKillTime = getTime();
		return;
	}
	
	if ( Distance( self.lastKillLocation, self.origin ) < 512 && getTime() - self.lastCampKillTime > 5000 )
	{
		self incPlayerStat( "mostcamperkills", 1 );
		self.lastKillWasCamping = true;
	}
	
	self.lastKillLocation = self.origin;
	self.lastCampKillTime = getTime();
}

consolation( killId )
{
	/*
	value = int( maps\mp\gametypes\_rank::getScoreInfoValue( "kill" ) * 0.25 );

	self thread maps\mp\gametypes\_hud_message::SplashNotifyDelayed( "consolation", value );
	self thread maps\mp\gametypes\_rank::giveRankXP( "consolation", value );
	*/
}


proximityAssist( killId )
{
	self.modifiers["proximityAssist"] = true;
	
	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_PROXIMITYASSIST" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "proximityassist" );
	//self thread maps\mp\_matchdata::logKillEvent( killId, "proximityAssist" );
}


proximityKill( killId )
{
	self.modifiers["proximityKill"] = true;
	
	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_PROXIMITYKILL" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "proximitykill" );
	//self thread maps\mp\_matchdata::logKillEvent( killId, "proximityKill" );
}


longshot( killId, weapon, meansOfDeath )
{
	self.modifiers["longshot"] = true;
	
	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_LONGSHOT" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "longshot", undefined, weapon, meansOfDeath );
	self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "longshot" );
	self incPlayerStat( "longshots", 1 );
	self thread maps\mp\_matchdata::logKillEvent( killId, "longshot" );
}

	
execution( killId, weapon, meansOfDeath )
{
	self.modifiers["execution"] = true;

	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_EXECUTION" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "execution", undefined, weapon, meansOfDeath );
	self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "execution" );
	self thread maps\mp\_matchdata::logKillEvent( killId, "execution" );
}


headShot( killId, weapon, meansOfDeath )
{
	self.modifiers["headshot"] = true;

	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_HEADSHOT" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "headshot", undefined, weapon, meansOfDeath );
	self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "headshot" );
	self thread maps\mp\_matchdata::logKillEvent( killId, "headshot" );
}


avengedPlayer( killId, weapon, meansOfDeath )
{
	self.modifiers["avenger"] = true;

	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_AVENGER" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "avenger", undefined, weapon, meansOfDeath );
	self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "avenger" );
	self thread maps\mp\_matchdata::logKillEvent( killId, "avenger" );
	
	self incPlayerStat( "avengekills", 1 );
}

assistedSuicide( killId, weapon, meansOfDeath )
{
	self.modifiers["assistedsuicide"] = true;

	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_ASSISTEDSUICIDE" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "assistedsuicide", undefined, weapon, meansOfDeath );
	self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "assistedsuicide" );
	self thread maps\mp\_matchdata::logKillEvent( killId, "assistedsuicide" );
}

defendedPlayer( killId, weapon, meansOfDeath )
{
	self.modifiers["defender"] = true;

	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DEFENDER" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "defender", undefined, weapon, meansOfDeath );
	self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "defender" );
	self thread maps\mp\_matchdata::logKillEvent( killId, "defender" );
	
	self incPlayerStat( "rescues", 1 );
}


postDeathKill( killId )
{
	self.modifiers["posthumous"] = true;

	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_POSTHUMOUS" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "posthumous" );
	self thread maps\mp\_matchdata::logKillEvent( killId, "posthumous" );
}


backStab( killId )
{
	self iPrintLnBold( "backstab" );
}


revenge( killId )
{
	self.modifiers["revenge"] = true;

	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_REVENGE" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "revenge" );
	self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "revenge" );
	self thread maps\mp\_matchdata::logKillEvent( killId, "revenge" );
	
	self incPlayerStat( "revengekills", 1 );
}


multiKill( killId, killCount )
{
	assert( killCount > 1 );
	
	if ( killCount == 2 )
	{
		self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DOUBLEKILL" );
		
		self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "double" );
	}
	else if ( killCount == 3 )
	{
		self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_TRIPLEKILL" );
		
		self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "triple" );
		thread teamPlayerCardSplash( "callout_3xkill", self );
	}
	else
	{
		self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_MULTIKILL" );
		
		self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "multi" );
		thread teamPlayerCardSplash( "callout_3xpluskill", self );
	}
	
	self thread maps\mp\_matchdata::logMultiKill( killId, killCount );
	
	// update player multikill record
	self setPlayerStatIfGreater( "multikill", killCount );
	
	// update player multikill count
	self incPlayerStat( "mostmultikills", 1 );
}


firstBlood( killId, weapon, meansOfDeath )
{
	self.modifiers["firstblood"] = true;

	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_FIRSTBLOOD" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "firstblood", undefined, weapon, meansOfDeath );
	self thread maps\mp\_matchdata::logKillEvent( killId, "firstblood" );
	self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "firstBlood" );

	thread teamPlayerCardSplash( "callout_firstblood", self );
}


winningShot( killId )
{
}


buzzKill( killId, victim, weapon, meansOfDeath )
{
	self.modifiers["buzzkill"] =  victim.pers["cur_kill_streak"];

	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_BUZZKILL" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "buzzkill", undefined, weapon, meansOfDeath );
	self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "buzzkill" );
	self thread maps\mp\_matchdata::logKillEvent( killId, "buzzkill" );
}


comeBack( killId, weapon, meansOfDeath )
{
	self.modifiers["comeback"] = true;

	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_COMEBACK" );
	
	self thread maps\mp\gametypes\_rank::giveRankXP( "comeback", undefined, weapon, meansOfDeath );
	self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "comeback" );
	self thread maps\mp\_matchdata::logKillEvent( killId, "comeback" );

	self incPlayerStat( "comebacks", 1 );
}


disconnected()
{
	myGuid = self.guid;
	
	for ( entry = 0; entry < level.players.size; entry++ )
	{
		if ( isDefined( level.players[entry].killedPlayers[myGuid] ) )
			level.players[entry].killedPlayers[myGuid] = undefined;
	
		if ( isDefined( level.players[entry].killedPlayersCurrent[myGuid] ) )
			level.players[entry].killedPlayersCurrent[myGuid] = undefined;
	
		if ( isDefined( level.players[entry].killedBy[myGuid] ) )
			level.players[entry].killedBy[myGuid] = undefined;
	}
}

monitorHealed()
{
	level endon( "end_game" );
	self endon( "disconnect" );
	
	for (;;)
	{
		self waittill( "healed");
		self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "healed" );
	}	
}


updateRecentKills( killId )
{
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	self notify ( "updateRecentKills" );
	self endon ( "updateRecentKills" );
	
	self.recentKillCount++;
	
	wait ( 1.0 );
	
	if ( self.recentKillCount > 1 )
		self multiKill( killId, self.recentKillCount );
	
	self.recentKillCount = 0;
}

monitorCrateJacking()
{
	level endon( "end_game" );
	self endon( "disconnect" );
	
	for( ;; )
	{
		self waittill( "hijacker", crateType, owner );
		
		self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_HIJACKER" );			
		self thread maps\mp\gametypes\_rank::giveRankXP( "hijacker", 100 );
		
		splashName = "hijacked_airdrop";
		challengeName = "ch_hijacker";

		switch( crateType )
		{
		case "sentry":
			splashName = "hijacked_sentry";
			break;
		case "juggernaut":
			splashName = "hijacked_juggernaut";
			break;
		case "remote_tank":
			splashName = "hijacked_remote_tank";
			break;
		case "mega":
		case "emergency_airdrop":
			splashName = "hijacked_emergency_airdrop";
			challengeName = "ch_newjack";
			break;

		default:
			break;
		}
		
		if( IsDefined( owner ) )
			owner maps\mp\gametypes\_hud_message::playerCardSplashNotify( splashName, self );
		self notify( "process", challengeName );
	}
}

monitorObjectives()
{
	level endon( "end_game" );
	self endon( "disconnect" );
	
	for (;;)
	{
		self waittill( "objective", objType );
		
		if ( objType == "captured" )
		{
			self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "capture" );
			
			if ( isDefined( self.lastStand ) && self.lastStand )
			{
				self thread maps\mp\gametypes\_hud_message::SplashNotifyDelayed( "heroic", 100 );
				self thread maps\mp\gametypes\_rank::giveRankXP( "reviver", 100 );
			}
		}
		
		if ( objType == "assistedCapture" )
			self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "assistedCapture" );
		
		if ( objType == "plant" )
			self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "plant" );
			
		if ( objType == "defuse" )
			self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "defuse" );
		
	}	
}

