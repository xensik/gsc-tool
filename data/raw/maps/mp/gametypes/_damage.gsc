#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

NUM_KILLS_GIVE_NUKE = 25;

isSwitchingTeams()
{
	if ( isDefined( self.switching_teams ) )
		return true;

	return false;
}


isTeamSwitchBalanced()
{
	playerCounts = self maps\mp\gametypes\_teams::CountPlayers();
	playerCounts[ self.leaving_team ] -- ;
	playerCounts[ self.joining_team ]++ ;

	return( ( playerCounts[ self.joining_team ] - playerCounts[ self.leaving_team ] ) < 2 );
}


isFriendlyFire( victim, attacker )
{
	if ( !level.teamBased )
		return false;
	
	if ( !isDefined( attacker ) )
		return false;
	
	if ( !isPlayer( attacker ) && !isDefined( attacker.team ) )
		return false;
	
	if ( victim.team != attacker.team )
		return false;
	
	if ( victim == attacker )
		return false;
	
	return true;
}


killedSelf( attacker )
{
	if ( !isPlayer( attacker ) )
		return false;

	if ( attacker != self )
		return false;

	return true;
}


isHeadShot( sWeapon, sHitLoc, sMeansOfDeath, attacker )
{	
	if ( isDefined( attacker ) )
	{
		if ( attacker.code_classname == "script_vehicle" && isDefined( attacker.owner ) )
			return false;
		if ( attacker.code_classname == "misc_turret" && isDefined( attacker.owner ) )
			return false;
		if ( attacker.code_classname == "script_model" && isDefined( attacker.owner ) )
			return false;
	}
	
	return( sHitLoc == "head" || sHitLoc == "helmet" ) && sMeansOfDeath != "MOD_MELEE" && sMeansOfDeath != "MOD_IMPACT" && !isEnvironmentWeapon( sWeapon );
}


handleTeamChangeDeath()
{
	if ( !level.teamBased )
		return;

	// this might be able to happen now, but we should remove instances where it can
	assert( self.leaving_team != self.joining_team );

	if ( self.joining_team == "spectator" || !isTeamSwitchBalanced() )
	{
		self thread [[ level.onXPEvent ]]( "suicide" );
		self incPersStat( "suicides", 1 );
		self.suicides = self getPersStat( "suicides" );
	}
}


handleWorldDeath( attacker, lifeId, sMeansOfDeath, sHitLoc )
{
	if ( !isDefined( attacker ) )
		return;

	if ( !isDefined( attacker.team ) )
	{	
		handleSuicideDeath( sMeansOfDeath, sHitLoc );
		return;
	}
	
	assert( attacker.team == "axis" || attacker.team == "allies" );

	if ( ( level.teamBased && attacker.team != self.team ) || !level.teamBased )
	{
		if ( isDefined( level.onNormalDeath ) && isPlayer( attacker ) && attacker.team != "spectator" )
			[[ level.onNormalDeath ]]( self, attacker, lifeId );
	}
}


handleSuicideDeath( sMeansOfDeath, sHitLoc )
{
	self SetCardDisplaySlot( self, 7 );
	self openMenu( "killedby_card_display" );

	self thread [[ level.onXPEvent ]]( "suicide" );
	self incPersStat( "suicides", 1 );
	self.suicides = self getPersStat( "suicides" );
	
	if ( !matchMakingGame() )
		self incPlayerStat( "suicides", 1 );

	scoreSub = maps\mp\gametypes\_tweakables::getTweakableValue( "game", "suicidepointloss" );
	maps\mp\gametypes\_gamescore::_setPlayerScore( self, maps\mp\gametypes\_gamescore::_getPlayerScore( self ) - scoreSub );

	if ( sMeansOfDeath == "MOD_SUICIDE" && sHitLoc == "none" && isDefined( self.throwingGrenade ) )
		self.lastGrenadeSuicideTime = gettime();

	// suicide was caused by too many team kills
	if ( isDefined( self.friendlydamage ) )
		self iPrintLnBold( &"MP_FRIENDLY_FIRE_WILL_NOT" );
}


handleFriendlyFireDeath( attacker )
{
	attacker SetCardDisplaySlot( self, 8 );
	attacker openMenu( "youkilled_card_display" );

	self SetCardDisplaySlot( attacker, 7 );
	self openMenu( "killedby_card_display" );

	attacker thread [[ level.onXPEvent ]]( "teamkill" );
	attacker.pers[ "teamkills" ] += 1.0;

	attacker.teamkillsThisRound++ ;

	if ( maps\mp\gametypes\_tweakables::getTweakableValue( "team", "teamkillpointloss" ) )
	{
		scoreSub = maps\mp\gametypes\_rank::getScoreInfoValue( "kill" );
		maps\mp\gametypes\_gamescore::_setPlayerScore( attacker, maps\mp\gametypes\_gamescore::_getPlayerScore( attacker ) - scoreSub );
	}

 	if ( level.maxAllowedTeamkills < 0 )
 		return;

	if ( level.inGracePeriod )
	{
		teamKillDelay = 1;
		attacker.pers["teamkills"] += level.maxAllowedTeamkills;
	}
	else if ( attacker.pers[ "teamkills" ] > 1 && getTimePassed() < ( (level.gracePeriod * 1000) + 8000 + ( attacker.pers[ "teamkills" ] * 1000 ) ) )
	{
		teamKillDelay = 1;
		attacker.pers["teamkills"] += level.maxAllowedTeamkills;
	}
	else
	{
		teamKillDelay = attacker maps\mp\gametypes\_playerlogic::TeamKillDelay();
	}

	if ( teamKillDelay > 0 )
	{
		attacker.pers["teamKillPunish"] = true;
		attacker _suicide();
	}
}


handleNormalDeath( lifeId, attacker, eInflictor, sWeapon, sMeansOfDeath )
{
	attacker thread maps\mp\_events::killedPlayer( lifeId, self, sWeapon, sMeansOfDeath );

	//if ( attacker.pers["teamkills"] <= level.maxAllowedTeamkills )
	//	attacker.pers["teamkills"] = max( attacker.pers["teamkills"] - 1, 0 );

	attacker SetCardDisplaySlot( self, 8 );
	attacker openMenu( "youkilled_card_display" );

	self SetCardDisplaySlot( attacker, 7 );
	self openMenu( "killedby_card_display" );

	if ( sMeansOfDeath == "MOD_HEAD_SHOT" )
	{
		attacker incPersStat( "headshots", 1 );
		attacker.headshots = attacker getPersStat( "headshots" );
		attacker incPlayerStat( "headshots", 1 );

		if ( isDefined( attacker.lastStand ) )
			value = maps\mp\gametypes\_rank::getScoreInfoValue( "kill" ) * 2;
		else
			value = undefined;

		attacker playLocalSound( "bullet_impact_headshot_2" );
	}
	else
	{
		if ( isDefined( attacker.lastStand ) )
			value = maps\mp\gametypes\_rank::getScoreInfoValue( "kill" ) * 2;
		else
			value = undefined;
	}

	attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", value, sWeapon, sMeansOfDeath );

	attacker incPersStat( "kills", 1 );
	attacker.kills = attacker getPersStat( "kills" );
	attacker updatePersRatio( "kdRatio", "kills", "deaths" );
	attacker maps\mp\gametypes\_persistence::statSetChild( "round", "kills", attacker.kills );
	attacker incPlayerStat( "kills", 1 );

	if ( isFlankKill( self, attacker ) )
	{
		attacker incPlayerStat( "flankkills", 1 );

		self incPlayerStat( "flankdeaths", 1 );
	}
	
	lastKillStreak = attacker.pers["cur_kill_streak"];

	self.pers["copyCatLoadout"] = undefined;

	if ( self _hasPerk( "specialty_copycat" ) )
		self.pers["copyCatLoadout"] = attacker maps\mp\gametypes\_class::cloneLoadout();
	
	if ( isAlive( attacker ) || attacker.streakType == "support" )
	{
		if ( attacker killShouldAddToKillstreak( sWeapon ) )
		{
			// NOTE: added threading to the giveAdrenaline() call because it could block the killcam from playing for a killed player
			//	this was happening if you earned a remote mortar and had one more kill to get something like the remote tank, and earned it while in the remote mortar
			//	there's a isChangingWeapon() loop that blocks since we're in the remote mortar not changing weapons when given the new killstreak
			attacker thread maps\mp\killstreaks\_killstreaks::giveAdrenaline( "kill" );
			attacker.pers["cur_kill_streak"]++;

			// at a certain number of kills we'll give you a nuke, but not from killstreak kills
			if( !isKillstreakWeapon( sWeapon ) )
				attacker.pers["cur_kill_streak_for_nuke"]++;

			numKills = NUM_KILLS_GIVE_NUKE;
			if( attacker _hasPerk( "specialty_hardline" ) )
				numKills--;

			if( !isKillstreakWeapon( sWeapon ) && attacker.pers["cur_kill_streak_for_nuke"] == numKills )
			{
				attacker thread maps\mp\killstreaks\_killstreaks::giveKillstreak( "nuke", false, true, attacker, true );
				attacker thread maps\mp\gametypes\_hud_message::killstreakSplashNotify( "nuke", numKills );
			}
		}

		attacker setPlayerStatIfGreater( "killstreak", attacker.pers["cur_kill_streak"] );

		if ( attacker.pers["cur_kill_streak"] > attacker getPersStat( "longestStreak" ) )
			attacker setPersStat( "longestStreak", attacker.pers["cur_kill_streak"] );
	}

	attacker.pers["cur_death_streak"] = 0;

	if ( attacker.pers["cur_kill_streak"] > attacker maps\mp\gametypes\_persistence::statGetChild( "round", "killStreak" ) )
	{
		attacker maps\mp\gametypes\_persistence::statSetChild( "round", "killStreak", attacker.pers["cur_kill_streak"] );
	}

	if ( attacker.pers["cur_kill_streak"] > attacker.kill_streak )
	{
		attacker maps\mp\gametypes\_persistence::statSet( "killStreak", attacker.pers["cur_kill_streak"] );
		attacker.kill_streak = attacker.pers["cur_kill_streak"];
	}

	maps\mp\gametypes\_gamescore::givePlayerScore( "kill", attacker, self );
	maps\mp\_skill::processKill( attacker, self );

	scoreSub = maps\mp\gametypes\_tweakables::getTweakableValue( "game", "deathpointloss" );
	maps\mp\gametypes\_gamescore::_setPlayerScore( self, maps\mp\gametypes\_gamescore::_getPlayerScore( self ) - scoreSub );

	if ( isDefined( level.ac130player ) && level.ac130player == attacker )
		level notify( "ai_killed", self );

	//if ( lastKillStreak != attacker.pers["cur_kill_streak"] )
	level notify ( "player_got_killstreak_" + attacker.pers["cur_kill_streak"], attacker );
	attacker notify( "got_killstreak" , attacker.pers["cur_kill_streak"] );

	attacker notify ( "killed_enemy" );
	
	//	assists for marking player with remote uav (allow in FFA)
	if ( isDefined( self.UAVRemoteMarkedBy ) )
	{
		if ( self.UAVRemoteMarkedBy != attacker )
			self.UAVRemoteMarkedBy thread maps\mp\killstreaks\_remoteuav::remoteUAV_processTaggedAssist( self );
		self.UAVRemoteMarkedBy = undefined;
	}	

	if ( isDefined( level.onNormalDeath ) && attacker.pers[ "team" ] != "spectator" )
		[[ level.onNormalDeath ]]( self, attacker, lifeId );

	if ( !level.teamBased )
	{
		self.attackers = [];
		return;
	}

	level thread maps\mp\gametypes\_battlechatter_mp::sayLocalSoundDelayed( attacker, "kill", 0.75 );	
	
	if ( isDefined( self.lastAttackedShieldPlayer ) && isDefined( self.lastAttackedShieldTime ) && self.lastAttackedShieldPlayer != attacker )
	{
		if ( getTime() - self.lastAttackedShieldTime < 2500 )
		{
			self.lastAttackedShieldPlayer thread maps\mp\gametypes\_gamescore::processShieldAssist( self );
			
			// if you are using the assists perk, then every assist is a kill towards a killstreak
			if( self.lastAttackedShieldPlayer _hasPerk( "specialty_assists" ) )
			{
				self.lastAttackedShieldPlayer.pers["assistsToKill"]++;

				if( !( self.lastAttackedShieldPlayer.pers["assistsToKill"] % 2 ) )
				{
					self.lastAttackedShieldPlayer maps\mp\gametypes\_missions::processChallenge( "ch_hardlineassists" );
					self.lastAttackedShieldPlayer maps\mp\killstreaks\_killstreaks::giveAdrenaline( "kill" );
					self.lastAttackedShieldPlayer.pers["cur_kill_streak"]++;
				}
			}
			else
			{
				self.lastAttackedShieldPlayer.pers["assistsToKill"] = 0;
			}
		}
		else if ( isAlive( self.lastAttackedShieldPlayer ) && getTime() - self.lastAttackedShieldTime < 5000 )
		{
			forwardVec = vectorNormalize( anglesToForward( self.angles ) );
			shieldVec = vectorNormalize( self.lastAttackedShieldPlayer.origin - self.origin );
		
			if ( vectorDot( shieldVec, forwardVec ) > 0.925 )
			{
				self.lastAttackedShieldPlayer thread maps\mp\gametypes\_gamescore::processShieldAssist( self );
				
				// if you are using the assists perk, then every assist is a kill towards a killstreak
				if( self.lastAttackedShieldPlayer _hasPerk( "specialty_assists" ) )
				{
					self.lastAttackedShieldPlayer.pers["assistsToKill"]++;

					if( !( self.lastAttackedShieldPlayer.pers["assistsToKill"] % 2 ) )
					{
						self.lastAttackedShieldPlayer maps\mp\gametypes\_missions::processChallenge( "ch_hardlineassists" );
						self.lastAttackedShieldPlayer maps\mp\killstreaks\_killstreaks::giveAdrenaline( "kill" );
						self.lastAttackedShieldPlayer.pers["cur_kill_streak"]++;
					}
				}
				else
				{
					self.lastAttackedShieldPlayer.pers["assistsToKill"] = 0;
				}
			}
		}
	}	

	//	regular assists
	if ( isDefined( self.attackers ) )
	{
		foreach ( player in self.attackers )
		{
			if ( !isDefined( player ) )
				continue;

			if ( player == attacker )
				continue;

			player thread maps\mp\gametypes\_gamescore::processAssist( self );

			// if you are using the assists perk, then every assist is a kill towards a killstreak
			if( player _hasPerk( "specialty_assists" ) )
			{
				player.pers["assistsToKill"]++;

				if( !( player.pers["assistsToKill"] % 2 ) )
				{
					player maps\mp\gametypes\_missions::processChallenge( "ch_hardlineassists" );
					player maps\mp\killstreaks\_killstreaks::giveAdrenaline( "kill" );
					player.pers["cur_kill_streak"]++;

					// at a certain number of kills in a streak we'll give you a nuke
					numKills = NUM_KILLS_GIVE_NUKE;
					if( player _hasPerk( "specialty_hardline" ) )
						numKills--;

					if( player.pers["cur_kill_streak"] == numKills )
					{
						player thread maps\mp\killstreaks\_killstreaks::giveKillstreak( "nuke", false, true, player, true );
						player thread maps\mp\gametypes\_hud_message::killstreakSplashNotify( "nuke", numKills );
					}
				}
			}
			else
			{
				player.pers["assistsToKill"] = 0;
			}
		}
		self.attackers = [];
	}
}

isPlayerWeapon( weaponName )
{
	if ( weaponClass( weaponName ) == "non-player" )
		return false;
		
	if ( weaponClass( weaponName ) == "turret" )
		return false;

	if ( weaponInventoryType( weaponName ) == "primary" || weaponInventoryType( weaponName ) == "altmode" )
		return true;
		
	return false;
}

Callback_PlayerKilled( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration )
{
	PlayerKilled_internal( eInflictor, attacker, self, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, false );
}


QueueShieldForRemoval( shield )
{
	MY_MAX_SHIELDS_AT_A_TIME = 5;

	if ( !isDefined( level.shieldTrashArray ) )
		level.shieldTrashArray = [];

	if ( level.shieldTrashArray.size >= MY_MAX_SHIELDS_AT_A_TIME )
	{
		idxMax = (level.shieldTrashArray.size - 1);
		level.shieldTrashArray[0] delete();
		for ( idx = 0; idx < idxMax; idx++ )
			level.shieldTrashArray[idx] = level.shieldTrashArray[idx + 1];
		level.shieldTrashArray[idxMax] = undefined;
	}

	level.shieldTrashArray[level.shieldTrashArray.size] = shield;
}


LaunchShield( damage, meansOfDeath )
{
	shieldModel = "weapon_riot_shield_mp";

	self DetachShieldModel( shieldModel, "tag_weapon_left" );
	self.hasRiotShield = false;
	self.hasRiotShieldEquipped = false;
}


PlayerKilled_internal( eInflictor, attacker, victim, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, isFauxDeath )
{
	prof_begin( "PlayerKilled" );
	//prof_begin( " PlayerKilled_1" );

	victim endon( "spawned" );
	victim notify( "killed_player" );

	assert( victim.sessionteam != "spectator" );

	if ( isDefined( attacker ) )
		attacker.assistedSuicide = undefined;

	if ( !isDefined( victim.idFlags ) )
	{
		if ( sMeansOfDeath == "MOD_SUICIDE" )
			victim.idFlags = 0;
		else if ( sMeansOfDeath == "MOD_GRENADE" && isSubstr( sWeapon, "frag_grenade" ) && iDamage == 100000 )
			victim.idFlags = 0;
		else if ( sWeapon == "nuke_mp" )
			victim.idFlags = 0;
		else if ( level.friendlyfire >= 2)
			victim.idFlags = 0;
		else
			assertEx( 0, "Victims ID flags not set, but means of death was gr or nuke: " + sMeansOfDeath  );
	}

	if ( victim.hasRiotShieldEquipped )
		victim LaunchShield( iDamage, sMeansofDeath );

	//victim thread checkForceBleedOut();

	if ( !isFauxDeath )
	{
		if ( isDefined( victim.endGame ) )
		{
			if ( IsDefined( level.nukeDetonated ) )
				self VisionSetNakedForPlayer( level.nukeVisionSet, 2 );
			else
				self VisionSetNakedForPlayer( "", 2 ); // go to default visionset
		}
		else
		{
			if ( IsDefined( level.nukeDetonated ) )
				self VisionSetNakedForPlayer( level.nukeVisionSet, 0 );
			else
				self VisionSetNakedForPlayer( "", 0 ); // go to default visionset
			victim ThermalVisionOff();
		}
	}
	else
	{
		victim.fauxDead = true;
		self notify ( "death" );
	}

	if ( game[ "state" ] == "postgame" )
	{
		//prof_end( " PlayerKilled_1" );
		prof_end( "PlayerKilled" );
		return;
	}

	// replace params with last stand info
	deathTimeOffset = 0;

	if ( !isPlayer( eInflictor ) && isDefined( eInflictor.primaryWeapon ) )
	{
		sPrimaryWeapon = eInflictor.primaryWeapon;
	}
	else if ( isDefined( attacker ) && isPlayer( attacker ) && attacker getCurrentPrimaryWeapon() != "none" )
	{
		sPrimaryWeapon = attacker getCurrentPrimaryWeapon();
	}
	else//getCurrentPrimaryWeapon() will return none if the player is: ladder, grenade, killstreak placment, etc...
	{
		if ( isSubStr( sWeapon, "alt_" ) )
		{
			sPrimaryWeapon = GetSubStr( sWeapon, 4, sWeapon.size );
		}
		else//killstreak weapon or offhand
		{
			sPrimaryWeapon = undefined;
		}
	}
		
	if ( isdefined( victim.useLastStandParams ) || ( isDefined( victim.lastStandParams ) && sMeansOfDeath == "MOD_SUICIDE" ) )
	{
		victim ensureLastStandParamsValidity();
		victim.useLastStandParams = undefined;

		assert( isdefined( victim.lastStandParams ) );

		eInflictor = victim.lastStandParams.eInflictor;
		attacker = victim.lastStandParams.attacker;
		iDamage = victim.lastStandParams.iDamage;
		sMeansOfDeath = victim.lastStandParams.sMeansOfDeath;
		sWeapon = victim.lastStandParams.sWeapon;
		sPrimaryWeapon = victim.lastStandParams.sPrimaryWeapon;
		vDir = victim.lastStandParams.vDir;
		sHitLoc = victim.lastStandParams.sHitLoc;

		deathTimeOffset = ( gettime() - victim.lastStandParams.lastStandStartTime ) / 1000;
		victim.lastStandParams = undefined;
	}

	//prof_end( " PlayerKilled_1" );
	//prof_begin( " PlayerKilled_2" );

	//used for endgame perk and assisted suicide.
	if ( (!isDefined( attacker ) || attacker.classname == "trigger_hurt" || attacker.classname == "worldspawn" || attacker == victim ) && isDefined( self.attackers )  )
	{
		bestPlayer = undefined;

		foreach ( player in self.attackers )
		{
			if ( !isDefined( player ) )
				continue;

			if (! isDefined( victim.attackerData[ player.guid ].damage ) )
				continue;

			if ( player == victim || (level.teamBased && player.team == victim.team ) )
				continue;

			if ( victim.attackerData[ player.guid ].lasttimedamaged + 2500 < getTime() && ( attacker != victim && ( isDefined(victim.lastStand) && victim.lastStand ) ) )
				continue;			

			if ( victim.attackerData[ player.guid ].damage > 1 && ! isDefined( bestPlayer ) )
				bestPlayer = player;
			else if ( isDefined( bestPlayer ) && victim.attackerData[ player.guid ].damage > victim.attackerData[ bestPlayer.guid ].damage )
				bestPlayer = player;		
		}

		if ( isDefined( bestPlayer ) )
		{
			attacker = bestPlayer;
			attacker.assistedSuicide = true;
			sWeapon = victim.attackerData[ bestPlayer.guid ].weapon; 
			vDir = victim.attackerData[ bestPlayer.guid ].vDir;
			sHitLoc = victim.attackerData[ bestPlayer.guid ].sHitLoc;
			psOffsetTime = victim.attackerData[ bestPlayer.guid ].psOffsetTime;
			sMeansOfDeath = victim.attackerData[ bestPlayer.guid ].sMeansOfDeath;
			iDamage = victim.attackerData[ bestPlayer.guid ].damage;
			sPrimaryWeapon = victim.attackerData[ bestPlayer.guid ].sPrimaryWeapon;
			eInflictor = attacker;
		}
	}
	else
	{
		if ( isDefined( attacker ) )
			attacker.assistedSuicide = undefined;	
	}

	// override MOD
	if ( isHeadShot( sWeapon, sHitLoc, sMeansOfDeath, attacker ) )
		sMeansOfDeath = "MOD_HEAD_SHOT";
	else if ( sMeansOfDeath != "MOD_MELEE" && !isDefined( victim.nuked ) )
		victim playDeathSound();

	friendlyFire = isFriendlyFire( victim, attacker );

	if ( isDefined( attacker ) )
	{
		// override attacker if it's a vehicle	
		if ( attacker.code_classname == "script_vehicle" && isDefined( attacker.owner ) )
		{
			attacker = attacker.owner;
		}

		// override attacker if it's a sentry	
		if ( attacker.code_classname == "misc_turret" && isDefined( attacker.owner ) )
		{
			if ( isDefined( attacker.vehicle ) )
				attacker.vehicle notify( "killedPlayer", victim );

			attacker = attacker.owner;
		}

		// override attacker if it's a crate	
		if ( attacker.code_classname == "script_model" && isDefined( attacker.owner ) )
		{
			attacker = attacker.owner;

			if ( !isFriendlyFire( victim, attacker ) && attacker != victim )
				attacker notify( "crushed_enemy" );
		}
	}

	//prof_end( " PlayerKilled_2" );
	//prof_begin( " PlayerKilled_3" );

	//prof_begin( " PlayerKilled_3_drop" );
	// drop weapons from killed player
	victim maps\mp\gametypes\_weapons::dropScavengerForDeath( attacker );	// must be done before dropWeaponForDeath, since we use some weapon information
	victim maps\mp\gametypes\_weapons::dropWeaponForDeath( attacker );
	//prof_end( " PlayerKilled_3_drop" );

	if ( !isFauxDeath )
	{
		victim.sessionstate = "dead";
		victim.statusicon = "hud_status_dead";
	}

	// UTS update aliveCount
	victim maps\mp\gametypes\_playerlogic::removeFromAliveCount();

	if ( !isDefined( victim.switching_teams ) )
	{
		// update our various stats
		victim incPersStat( "deaths", 1 );
		victim.deaths = victim getPersStat( "deaths" );
		victim updatePersRatio( "kdRatio", "kills", "deaths" );
		victim maps\mp\gametypes\_persistence::statSetChild( "round", "deaths", victim.deaths );
		victim incPlayerStat( "deaths", 1 );
	}

	if ( isDefined( attacker ) && isPlayer(attacker) )
		attacker checkKillSteal( victim );

	// obituary
	obituary( victim, attacker, sWeapon, sMeansOfDeath );

	doKillcam = false;

	lifeId = getNextLifeId();

	victim logPrintPlayerDeath( lifeId, attacker, iDamage, sMeansOfDeath, sWeapon, sPrimaryWeapon, sHitLoc );
	victim maps\mp\_matchdata::logPlayerLife( lifeId );
	victim maps\mp\_matchdata::logPlayerDeath( lifeId, attacker, iDamage, sMeansOfDeath, sWeapon, sPrimaryWeapon, sHitLoc );

	if ( (sMeansOfDeath == "MOD_MELEE") )
	{
		if ( IsSubStr( sWeapon, "riotshield" ) )
		{
			attacker incPlayerStat( "shieldkills", 1 );

			if ( !matchMakingGame() )
				victim incPlayerStat( "shielddeaths", 1 );
		}
		else
			attacker incPlayerStat( "knifekills", 1 );
	}

	//prof_end( " PlayerKilled_3" );
	//prof_begin( " PlayerKilled_4" );

	if ( victim isSwitchingTeams() )
	{
		handleTeamChangeDeath();
	}
	else if ( !isPlayer( attacker ) || (isPlayer( attacker ) && sMeansOfDeath == "MOD_FALLING") )
	{
		handleWorldDeath( attacker, lifeId, sMeansOfDeath, sHitLoc );
	}
	else if ( attacker == victim )
	{
		handleSuicideDeath( sMeansOfDeath, sHitLoc );
	}
	else if ( friendlyFire )
	{
		if ( !isDefined( victim.nuked ) )
		{
			handleFriendlyFireDeath( attacker );
		}
	}
	else
	{
		if ( sMeansOfDeath == "MOD_GRENADE" && eInflictor == attacker )
			addAttacker( victim, attacker, eInflictor, sWeapon, iDamage, (0,0,0), vDir, sHitLoc, psOffsetTime, sMeansOfDeath );

		doKillcam = true;
		handleNormalDeath( lifeId, attacker, eInflictor, sWeapon, sMeansOfDeath );
		victim thread maps\mp\gametypes\_missions::playerKilled( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, sPrimaryWeapon, sHitLoc, attacker.modifiers );

		victim.pers["cur_death_streak"]++;

		if ( !getGametypeNumLives() && !matchMakingGame() )
			victim setPlayerStatIfGreater( "deathstreak", victim.pers["cur_death_streak"] );

		// team splash if juggernaut was killed
		if( IsPlayer( attacker ) && victim isJuggernaut() )
		{
			attacker thread teamPlayerCardSplash( "callout_killed_juggernaut", attacker );
		}
	}
	
	// Don't increment weapon stats for team kills or deaths
	wasInLastStand = false;
	lastWeaponBeforeDroppingIntoLastStand = undefined;
	if ( isDefined( self.previousPrimary ) )
	{
		wasInLastStand = true;
		lastWeaponBeforeDroppingIntoLastStand = self.previousPrimary;
	}
	
	if ( isPlayer( attacker ) && attacker != self && ( !level.teamBased || ( level.teamBased && self.team != attacker.team ) ) )
	{
		self thread  maps\mp\gametypes\_gamelogic::trackLeaderBoardDeathStats( sWeapon, sMeansOfDeath ); 

		if ( wasInLastStand && isDefined( lastWeaponBeforeDroppingIntoLastStand ) ) 
			weaponName = lastWeaponBeforeDroppingIntoLastStand;
		else
			weaponName = self.lastdroppableweapon;

		if ( isDefined( weaponName ) && ( isSubStr( weaponName, "gl_" ) || isSubStr( weaponName, "mk_" ) || isSubStr( weaponName, "ft_" ) ) )
			weaponName = self.currentWeapon;

		attacker thread  maps\mp\gametypes\_gamelogic::trackAttackerLeaderBoardDeathStats( sWeapon, sMeansOfDeath ); 
	}

	//prof_end( " PlayerKilled_4" );
	//prof_begin( " PlayerKilled_5" );

	// clear any per life variables
	victim resetPlayerVariables();
	victim.lastAttacker = attacker;
	victim.lastDeathPos = victim.origin;
	victim.deathTime = getTime();
	victim.wantSafeSpawn = false;
	victim.revived = false;
	victim.sameShotDamage = 0;

	if( maps\mp\killstreaks\_killstreaks::streakTypeResetsOnDeath( victim.streakType ) )
		victim maps\mp\killstreaks\_killstreaks::resetAdrenaline();

	if ( isFauxDeath )
	{
		doKillcam = false;
		deathAnimDuration = (victim PlayerForceDeathAnim( eInflictor, sMeansOfDeath, sWeapon, sHitLoc, vDir ));
	}

	victim.body = victim clonePlayer( deathAnimDuration );

	if ( isFauxDeath )
		victim PlayerHide();

	if ( victim isOnLadder() || victim isMantling() || !victim isOnGround() || isDefined( victim.nuked ) )
		victim.body startRagDoll();

	if ( !isDefined( victim.switching_teams ) )
		thread maps\mp\gametypes\_deathicons::addDeathicon( victim.body, victim, victim.team, 5.0 );

	thread delayStartRagdoll( victim.body, sHitLoc, vDir, sWeapon, eInflictor, sMeansOfDeath );

	// allow per gametype death handling	
	victim thread [[ level.onPlayerKilled ]]( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration, lifeId );

	if ( isPlayer( attacker ) )
		attackerNum = attacker getEntityNumber();
	else
		attackerNum = -1;
	killcamentity = victim getKillcamEntity( attacker, eInflictor, sWeapon );
	killcamentityindex = -1;
	killcamentitystarttime = 0;

	if ( isDefined( killcamentity ) )
	{
		killcamentityindex = killcamentity getEntityNumber();// must do this before any waiting lest the entity be deleted
		killcamentitystarttime = killcamentity.birthtime;
		if ( !isdefined( killcamentitystarttime ) )
			killcamentitystarttime = 0;
	}

/#
	if ( getDvarInt( "scr_forcekillcam" ) != 0 )
		doKillcam = true;
#/

	///////////////////////////////////////////////////////
	// KILL CAM STUFF
/*
	// record the kill cam values for the final kill cam
	if ( sMeansOfDeath != "MOD_SUICIDE" && !( !isDefined( attacker ) || attacker.classname == "trigger_hurt" || attacker.classname == "worldspawn" || attacker == victim ) )
	{
		recordFinalKillCam( 5.0, victim, attacker, attackerNum, killcamentityindex, killcamentitystarttime, sWeapon, deathTimeOffset, psOffsetTime );
	}

	// tell the ingame killcam ui what to say, this was tried but has an issue with new players not understanding, maybe just needs new text that is understood
	victim SetPlayerData( "killCamHowKilled", 0 );
	switch( sMeansOfDeath )
	{
	case "MOD_HEAD_SHOT":
		victim SetPlayerData( "killCamHowKilled", 1 );
		break;

	//case "MOD_MELEE":
	//	victim SetPlayerData( "killCamHowKilled", 2 );
	//	break;

	//case "MOD_RIFLE_BULLET":
	//case "MOD_PISTOL_BULLET":
	//	if( attacker PlayerAds() <= 0.5 )
	//		victim SetPlayerData( "killCamHowKilled", 3 );
	//	else
	//		victim SetPlayerData( "killCamHowKilled", 4 );
	//	break;

	//case "MOD_GRENADE_SPLASH":
	//case "MOD_GRENADE":
	//	weaponTokens = StrTok( sWeapon, "_" );
	//	if( "gl" == weaponTokens[0] )
	//		victim SetPlayerData( "killCamHowKilled", 5 );
	//	break;

	//case "MOD_IMPACT":
	//	weaponTokens = StrTok( sWeapon, "_" );
	//	if( "gl" == weaponTokens[0] )
	//		victim SetPlayerData( "killCamHowKilled", 6 );
	//	break;

	default:
		break;
	}

	//// check for camping last because it'll override the others
	//if( IsDefined( attacker.lastKillWasCamping ) && attacker.lastKillWasCamping )
	//	victim SetPlayerData( "killCamHowKilled", 7 );

	// END KILL CAM
	///////////////////////////////////////////////////////
*/
	if ( !isFauxDeath )
	{
		if ( !level.showingFinalKillcam && !level.killcam && doKillcam && !using_wii() )
		{
			if ( victim _hasPerk( "specialty_copycat" ) && isDefined( victim.pers["copyCatLoadout"] ) )
			{
				victim thread maps\mp\gametypes\_killcam::waitDeathCopyCatButton( attacker );
				wait ( 1.0 );
			}
		}

		// let the player watch themselves die
		wait( 0.25 );
		victim thread maps\mp\gametypes\_killcam::cancelKillCamOnUse();
		wait( 0.25 );

		self.respawnTimerStartTime = gettime() + 1000;
		timeUntilSpawn = maps\mp\gametypes\_playerlogic::TimeUntilSpawn( true );
		if ( timeUntilSpawn < 1 )
			timeUntilSpawn = 1;
		victim thread maps\mp\gametypes\_playerlogic::predictAboutToSpawnPlayerOverTime( timeUntilSpawn );

		wait( 1.0 );
		victim notify( "death_delay_finished" );
	}

	postDeathDelay = ( getTime() - victim.deathTime ) / 1000;
	self.respawnTimerStartTime = gettime();

	if ( !using_wii() && !(isDefined( victim.cancelKillcam) && victim.cancelKillcam) && doKillcam && level.killcam && game[ "state" ] == "playing" && !victim isUsingRemote() && !level.showingFinalKillcam )
	{
		livesLeft = !( getGametypeNumLives() && !victim.pers[ "lives" ] );
		timeUntilSpawn = maps\mp\gametypes\_playerlogic::TimeUntilSpawn( true );
		willRespawnImmediately = livesLeft && ( timeUntilSpawn <= 0 );

		if ( !livesLeft ) 
		{
			timeUntilSpawn = -1;
			level notify( "player_eliminated", victim );
		}

		victim maps\mp\gametypes\_killcam::killcam( attackerNum, killcamentityindex, killcamentitystarttime, sWeapon, postDeathDelay + deathTimeOffset, psOffsetTime, timeUntilSpawn, maps\mp\gametypes\_gamelogic::timeUntilRoundEnd(), attacker, victim );
	}

	//prof_end( " PlayerKilled_6" );
	//prof_begin( " PlayerKilled_7" );

	//self openMenu( "killedby_card_hide" );

	if ( game[ "state" ] != "playing" )
	{
		if ( !level.showingFinalKillcam )
		{
			victim.sessionstate = "dead";
			victim ClearKillcamState();
		}

		//prof_end( " PlayerKilled_7" );
		prof_end( "PlayerKilled" );
		return;
	}

	// class may be undefined if we have changed teams
	if ( isValidClass( victim.class ) )
	{
		victim thread maps\mp\gametypes\_playerlogic::spawnClient();
	}

	//prof_end( " PlayerKilled_7" );
	prof_end( "PlayerKilled" );
}

checkForceBleedout()
{
	if ( level.dieHardMode != 1 )
		return false;
	
	if ( !getGametypeNumLives() )
		return false;
	
	if ( level.livesCount[self.team] > 0 )
		return false;
	
	foreach ( player in level.players )
	{
		if ( !isAlive( player ) )
			continue;
			
		if ( player.team != self.team )
			continue;
			
		if ( player == self )
			continue;
		
		if ( !player.inLastStand )
			return false;
	}
	
	foreach ( player in level.players )
	{
		if ( !isAlive( player ) )
			continue;
		
		if ( player.team != self.team )
			continue;
		
		if ( player.inLastStand && player != self )
			player lastStandBleedOut(false);		
	}
	
	return true;					
}

checkKillSteal( vic )
{
	if ( matchMakingGame() )
		return;
	
	greatestDamage = 0;
	greatestAttacker = undefined;
	
	if ( isDefined( vic.attackerdata ) && vic.attackerdata.size > 1 )	
	{
		foreach ( attacker in vic.attackerdata )
		{
			if ( attacker.damage > greatestDamage )
			{
				greatestDamage = attacker.damage;
				greatestAttacker = attacker.attackerEnt;	
			}
		}
		
		if ( isDefined( greatestAttacker ) && greatestAttacker != self )
			self incPlayerStat( "killsteals", 1 );
	}
}

initFinalKillCam()
{
	level.finalKillCam_delay					= [];
	level.finalKillCam_victim					= [];
	level.finalKillCam_attacker					= [];
	level.finalKillCam_attackerNum				= [];
	level.finalKillCam_killCamEntityIndex		= [];
	level.finalKillCam_killCamEntityStartTime	= [];
	level.finalKillCam_sWeapon					= [];
	level.finalKillCam_deathTimeOffset			= [];
	level.finalKillCam_psOffsetTime				= [];
	level.finalKillCam_timeRecorded				= [];
	level.finalKillCam_timeGameEnded			= [];

	level.finalKillCam_delay[ "axis" ]					= undefined;
	level.finalKillCam_victim[ "axis" ]					= undefined;
	level.finalKillCam_attacker[ "axis" ]				= undefined;
	level.finalKillCam_attackerNum[ "axis" ]			= undefined;
	level.finalKillCam_killCamEntityIndex[ "axis" ]		= undefined;
	level.finalKillCam_killCamEntityStartTime[ "axis" ]	= undefined;
	level.finalKillCam_sWeapon[ "axis" ]				= undefined;
	level.finalKillCam_deathTimeOffset[ "axis" ]		= undefined;
	level.finalKillCam_psOffsetTime[ "axis" ]			= undefined;
	level.finalKillCam_timeRecorded[ "axis" ]			= undefined;
	level.finalKillCam_timeGameEnded[ "axis" ]			= undefined;

	level.finalKillCam_delay[ "allies" ]					= undefined;
	level.finalKillCam_victim[ "allies" ]					= undefined;
	level.finalKillCam_attacker[ "allies" ]					= undefined;
	level.finalKillCam_attackerNum[ "allies" ]				= undefined;
	level.finalKillCam_killCamEntityIndex[ "allies" ]		= undefined;
	level.finalKillCam_killCamEntityStartTime[ "allies" ]	= undefined;
	level.finalKillCam_sWeapon[ "allies" ]					= undefined;
	level.finalKillCam_deathTimeOffset[ "allies" ]			= undefined;
	level.finalKillCam_psOffsetTime[ "allies" ]				= undefined;
	level.finalKillCam_timeRecorded[ "allies" ]				= undefined;
	level.finalKillCam_timeGameEnded[ "allies" ]			= undefined;

	level.finalKillCam_delay[ "none" ]					= undefined;
	level.finalKillCam_victim[ "none" ]					= undefined;
	level.finalKillCam_attacker[ "none" ]				= undefined;
	level.finalKillCam_attackerNum[ "none" ]			= undefined;
	level.finalKillCam_killCamEntityIndex[ "none" ]		= undefined;
	level.finalKillCam_killCamEntityStartTime[ "none" ]	= undefined;
	level.finalKillCam_sWeapon[ "none" ]				= undefined;
	level.finalKillCam_deathTimeOffset[ "none" ]		= undefined;
	level.finalKillCam_psOffsetTime[ "none" ]			= undefined;
	level.finalKillCam_timeRecorded[ "none" ]			= undefined;
	level.finalKillCam_timeGameEnded[ "none" ]			= undefined;

	level.finalKillCam_winner = undefined;
}

recordFinalKillCam( delay, victim, attacker, attackerNum, killCamEntityIndex, killCamEntityStartTime, sWeapon, deathTimeOffset, psOffsetTime )
{
	// save this kill as the final kill cam so we can play it back when the match ends
	// we want to save each team seperately so we can show the winning team's kill when applicable
	if( level.teambased && IsDefined( attacker.team ) )
	{
		level.finalKillCam_delay[ attacker.team ]					= delay;
		level.finalKillCam_victim[ attacker.team ]					= victim;
		level.finalKillCam_attacker[ attacker.team ]				= attacker;
		level.finalKillCam_attackerNum[ attacker.team ]				= attackerNum;
		level.finalKillCam_killCamEntityIndex[ attacker.team ]		= killCamEntityIndex;
		level.finalKillCam_killCamEntityStartTime[ attacker.team ]	= killCamEntityStartTime;
		level.finalKillCam_sWeapon[ attacker.team ]					= sWeapon;
		level.finalKillCam_deathTimeOffset[ attacker.team ]			= deathTimeOffset;
		level.finalKillCam_psOffsetTime[ attacker.team ]			= psOffsetTime;
		level.finalKillCam_timeRecorded[ attacker.team ]			= getSecondsPassed();
		level.finalKillCam_timeGameEnded[ attacker.team ]			= getSecondsPassed(); // this gets set in endGame()
	}

	// none gets filled just in case we need something without a team or this is ffa
	level.finalKillCam_delay[ "none" ]					= delay;
	level.finalKillCam_victim[ "none" ]					= victim;
	level.finalKillCam_attacker[ "none" ]				= attacker;
	level.finalKillCam_attackerNum[ "none" ]			= attackerNum;
	level.finalKillCam_killCamEntityIndex[ "none" ]		= killCamEntityIndex;
	level.finalKillCam_killCamEntityStartTime[ "none" ]	= killCamEntityStartTime;
	level.finalKillCam_sWeapon[ "none" ]				= sWeapon;
	level.finalKillCam_deathTimeOffset[ "none" ]		= deathTimeOffset;
	level.finalKillCam_psOffsetTime[ "none" ]			= psOffsetTime;
	level.finalKillCam_timeRecorded[ "none" ]			= getSecondsPassed();
	level.finalKillCam_timeGameEnded[ "none" ]			= getSecondsPassed(); // this gets set in endGame()
}

eraseFinalKillCam()
{
	// erase this kill as the final kill cam so we don't play it back when the match ends
	level.finalKillCam_delay[ "axis" ]					= undefined;
	level.finalKillCam_victim[ "axis" ]					= undefined;
	level.finalKillCam_attacker[ "axis" ]				= undefined;
	level.finalKillCam_attackerNum[ "axis" ]			= undefined;
	level.finalKillCam_killCamEntityIndex[ "axis" ]		= undefined;
	level.finalKillCam_killCamEntityStartTime[ "axis" ]	= undefined;
	level.finalKillCam_sWeapon[ "axis" ]				= undefined;
	level.finalKillCam_deathTimeOffset[ "axis" ]		= undefined;
	level.finalKillCam_psOffsetTime[ "axis" ]			= undefined;
	level.finalKillCam_timeRecorded[ "axis" ]			= undefined;
	level.finalKillCam_timeGameEnded[ "axis" ]			= undefined;

	level.finalKillCam_delay[ "allies" ]					= undefined;
	level.finalKillCam_victim[ "allies" ]					= undefined;
	level.finalKillCam_attacker[ "allies" ]					= undefined;
	level.finalKillCam_attackerNum[ "allies" ]				= undefined;
	level.finalKillCam_killCamEntityIndex[ "allies" ]		= undefined;
	level.finalKillCam_killCamEntityStartTime[ "allies" ]	= undefined;
	level.finalKillCam_sWeapon[ "allies" ]					= undefined;
	level.finalKillCam_deathTimeOffset[ "allies" ]			= undefined;
	level.finalKillCam_psOffsetTime[ "allies" ]				= undefined;
	level.finalKillCam_timeRecorded[ "allies" ]				= undefined;
	level.finalKillCam_timeGameEnded[ "allies" ]			= undefined;

	level.finalKillCam_delay[ "none" ]					= undefined;
	level.finalKillCam_victim[ "none" ]					= undefined;
	level.finalKillCam_attacker[ "none" ]				= undefined;
	level.finalKillCam_attackerNum[ "none" ]			= undefined;
	level.finalKillCam_killCamEntityIndex[ "none" ]		= undefined;
	level.finalKillCam_killCamEntityStartTime[ "none" ]	= undefined;
	level.finalKillCam_sWeapon[ "none" ]				= undefined;
	level.finalKillCam_deathTimeOffset[ "none" ]		= undefined;
	level.finalKillCam_psOffsetTime[ "none" ]			= undefined;
	level.finalKillCam_timeRecorded[ "none" ]			= undefined;
	level.finalKillCam_timeGameEnded[ "none" ]			= undefined;

	level.finalKillCam_winner = undefined;
}

doFinalKillcam()
{
	level waittill ( "round_end_finished" );

	level.showingFinalKillcam = true;

	// we want to show the winner's final kill cam
	winner = "none";
	if( IsDefined( level.finalKillCam_winner ) )
	{
		winner = level.finalKillCam_winner;
		//switch( level.gametype )
		//{
		//case "war":		// tdm
		//case "dom":		// domination
		//case "sab":		// sabotage
		//case "sd":		// search and destroy
		//case "dd":		// demolition
		//case "ctf":		// capture the flag
		//case "koth":	// headquarters
		//case "tdef":	// team defender
		//	winner = level.finalKillCam_winner;
		//	break;

		//case "dm":		// ffa
		//default:
		//	break;
		//}
	}

	delay = level.finalKillCam_delay[ winner ];
	victim = level.finalKillCam_victim[ winner ];
	attacker = level.finalKillCam_attacker[ winner ];
	attackerNum = level.finalKillCam_attackerNum[ winner ];
	killCamEntityIndex = level.finalKillCam_killCamEntityIndex[ winner ];
	killCamEntityStartTime = level.finalKillCam_killCamEntityStartTime[ winner ];
	sWeapon = level.finalKillCam_sWeapon[ winner ];
	deathTimeOffset = level.finalKillCam_deathTimeOffset[ winner ];
	psOffsetTime = level.finalKillCam_psOffsetTime[ winner ];
	timeRecorded = level.finalKillCam_timeRecorded[ winner ];
	timeGameEnded = level.finalKillCam_timeGameEnded[ winner ];

	if( !isDefined( victim ) || 
		!isDefined( attacker ) )
	{
		level.showingFinalKillcam = false;
		level notify( "final_killcam_done" );
		return;
	}

	// if the killcam happened longer than 15 seconds ago, don't show it
	killCamBufferTime = 15;
	killCamOffsetTime = timeGameEnded - timeRecorded;
	if( killCamOffsetTime > killCamBufferTime )
	{
		level.showingFinalKillcam = false;
		level notify( "final_killcam_done" );
		return;
	}

	if ( isDefined( attacker ) )
	{
		//maps\mp\_awards::addAwardWinner( "finalkill", attacker.clientid );
		attacker.finalKill = true;
	}

	postDeathDelay = (( getTime() - victim.deathTime ) / 1000);
	
	foreach ( player in level.players )
	{
		player closePopupMenu();
		player closeInGameMenu();
		if( IsDefined( level.nukeDetonated ) )
			player VisionSetNakedForPlayer( level.nukeVisionSet, 0 );
		else
			player VisionSetNakedForPlayer( "", 0 ); // go to default visionset
		player.killcamentitylookat = victim getEntityNumber();
		
		if ( (player != victim || (!isRoundBased() || isLastRound())) && player _hasPerk( "specialty_copycat" ) )
			player _unsetPerk( "specialty_copycat" );
		
		player thread maps\mp\gametypes\_killcam::killcam( attackerNum, killcamentityindex, killcamentitystarttime, sWeapon, postDeathDelay + deathTimeOffset, psOffsetTime, 0, 10000, attacker, victim );
	}

	wait( 0.1 );

	while ( anyPlayersInKillcam() )
		wait( 0.05 );
	
	level notify( "final_killcam_done" );
	level.showingFinalKillcam = false;
}


anyPlayersInKillcam()
{
	if( using_wii() ) 
		return false;
		
	foreach ( player in level.players )
	{
		if ( isDefined( player.killcam ) )
			return true;
	}
	
	return false;
}


resetPlayerVariables()
{
	self.killedPlayersCurrent = [];
	self.switching_teams = undefined;
	self.joining_team = undefined;
	self.leaving_team = undefined;

	self.pers["cur_kill_streak"] = 0;
	self.pers["cur_kill_streak_for_nuke"] = 0;

	self maps\mp\gametypes\_gameobjects::detachUseModels();// want them detached before we create our corpse
}


getKillcamEntity( attacker, eInflictor, sWeapon ) // self == victim
{
	if( !isDefined( eInflictor ) || 
		eInflictor == attacker )
		return undefined;
	
	switch( sWeapon )
	{
	case "bouncingbetty_mp":			// bouncing betty
	case "artillery_mp":				// precision airstrike
	case "stealth_bomb_mp":				// stealth bomber
	case "pavelow_minigun_mp":			// pave low
	case "apache_minigun_mp":			// little bird flock
	case "littlebird_guard_minigun_mp":	// little bird guard
	case "osprey_minigun_mp":			// escort airdrop
	//case "remote_mortar_missile_mp":	// reaper
		return eInflictor.killCamEnt;

	case "sam_projectile_mp":			// sam turret
		if( IsDefined( eInflictor.samTurret ) && IsDefined( eInflictor.samTurret.killCamEnt ) )
			return eInflictor.samTurret.killCamEnt;
		break;

	case "ims_projectile_mp":			// ims
		if( IsDefined( attacker ) && IsDefined( attacker.imsKillCamEnt ) )
			return attacker.imsKillCamEnt;
		break;

	case "none":						// could be care package
		if( IsDefined( eInflictor.targetname ) && eInflictor.targetname == "care_package" )
			return eInflictor.killCamEnt;
		break;

	case "ac130_105mm_mp":				// ac130
	case "ac130_40mm_mp":				// ac130
	case "ac130_25mm_mp":				// ac130
	case "remotemissile_projectile_mp":	// predator missile
	case "osprey_player_minigun_mp":	// osprey gunner
	case "ugv_turret_mp":				// remote tank
	case "remote_turret_mp":			// remote turret
		return undefined;
	}
	
	// bomb sites
	if( isDefined( eInflictor.script_gameobjectname ) && 
		( eInflictor.script_gameobjectname == "bombzone" || eInflictor.script_gameobjectname == "sab" ) )
		return eInflictor.killCamEnt;
	
	// could be a destructible
	if( eInflictor.classname == "script_origin" || eInflictor.classname == "script_model" || eInflictor.classname == "script_brushmodel" )
	{
		// probably a barrel or a car or another destructible, the killcament gets set in _load.gsc when the level loads
		// if the attacker shot a destructible to kill the victim, then show from the ac130 or gunner and not the destructible because it causes a weird thermal bug
		if( isDefined( eInflictor.killCamEnt ) && !attacker attackerInRemoteKillstreak() )
			return eInflictor.killCamEnt;
		else
			return undefined; 
	}
	
	return eInflictor;
}

attackerInRemoteKillstreak() // self == attacker
{
	if( !IsDefined( self ) )
		return false;
	if( IsDefined( level.ac130player ) && self == level.ac130player )
		return true;
	if( IsDefined( level.chopper ) && IsDefined( level.chopper.gunner ) && self == level.chopper.gunner )
		return true;
	if( IsDefined( level.remote_mortar ) && IsDefined( level.remote_mortar.owner ) && self == level.remote_mortar.owner )
		return true;
	if( IsDefined( self.using_remote_turret ) && self.using_remote_turret )
		return true;
	if( IsDefined( self.using_remote_tank ) && self.using_remote_tank )
		return true;

	return false;
}

HitlocDebug( attacker, victim, damage, hitloc, dflags )
{
	colors = [];
	colors[ 0 ] = 2;
	colors[ 1 ] = 3;
	colors[ 2 ] = 5;
	colors[ 3 ] = 7;

	if ( !getdvarint( "scr_hitloc_debug" ) )
		return;

	if ( !isdefined( attacker.hitlocInited ) )
	{
		for ( i = 0; i < 6; i++ )
		{
			attacker setClientDvar( "ui_hitloc_" + i, "" );
		}
		attacker.hitlocInited = true;
	}

	if ( level.splitscreen || !isPLayer( attacker ) )
		return;

	elemcount = 6;
	if ( !isdefined( attacker.damageInfo ) )
	{
		attacker.damageInfo = [];
		for ( i = 0; i < elemcount; i++ )
		{
			attacker.damageInfo[ i ] = spawnstruct();
			attacker.damageInfo[ i ].damage = 0;
			attacker.damageInfo[ i ].hitloc = "";
			attacker.damageInfo[ i ].bp = false;
			attacker.damageInfo[ i ].jugg = false;
			attacker.damageInfo[ i ].colorIndex = 0;
		}
		attacker.damageInfoColorIndex = 0;
		attacker.damageInfoVictim = undefined;
	}

	for ( i = elemcount - 1; i > 0; i -- )
	{
		attacker.damageInfo[ i ].damage = attacker.damageInfo[ i - 1 ].damage;
		attacker.damageInfo[ i ].hitloc = attacker.damageInfo[ i - 1 ].hitloc;
		attacker.damageInfo[ i ].bp = attacker.damageInfo[ i - 1 ].bp;
		attacker.damageInfo[ i ].jugg = attacker.damageInfo[ i - 1 ].jugg;
		attacker.damageInfo[ i ].colorIndex = attacker.damageInfo[ i - 1 ].colorIndex;
	}
	attacker.damageInfo[ 0 ].damage = damage;
	attacker.damageInfo[ 0 ].hitloc = hitloc;
	attacker.damageInfo[ 0 ].bp = ( dflags & level.iDFLAGS_PENETRATION );
	attacker.damageInfo[ 0 ].jugg = victim isJuggernaut();
	if ( isdefined( attacker.damageInfoVictim ) && ( attacker.damageInfoVictim != victim ) )
	{
		attacker.damageInfoColorIndex++ ;
		if ( attacker.damageInfoColorIndex == colors.size )
			attacker.damageInfoColorIndex = 0;
	}
	attacker.damageInfoVictim = victim;
	attacker.damageInfo[ 0 ].colorIndex = attacker.damageInfoColorIndex;

	for ( i = 0; i < elemcount; i++ )
	{
		color = "^" + colors[ attacker.damageInfo[ i ].colorIndex ];
		if ( attacker.damageInfo[ i ].hitloc != "" )
		{
			val = color + attacker.damageInfo[ i ].hitloc;
			if ( attacker.damageInfo[ i ].bp )
				val += " (BP)";
			if ( attacker.damageInfo[ i ].jugg )
				val += " (Jugg)";
			attacker setClientDvar( "ui_hitloc_" + i, val );
		}
		attacker setClientDvar( "ui_hitloc_damage_" + i, color + attacker.damageInfo[ i ].damage );
	}
}

giveRecentShieldXP()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	
	self notify ( "giveRecentShieldXP" );
	self endon ( "giveRecentShieldXP" );
	
	self.recentShieldXP++;
	
	wait ( 20.0 );
	
	self.recentShieldXP = 0;
}


Callback_PlayerDamage_internal( eInflictor, eAttacker, victim, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime )
{	
	if ( !isReallyAlive( victim ) )
		return;
	
	if ( isDefined( eAttacker ) && eAttacker.classname == "script_origin" && isDefined( eAttacker.type ) && eAttacker.type == "soft_landing" )
		return;

	if ( sWeapon == "killstreak_emp_mp" )
		return;

	if ( sWeapon == "bouncingbetty_mp" && !maps\mp\gametypes\_weapons::mineDamageHeightPassed( eInflictor, victim ) )
		return;
	
	if ( sWeapon == "bouncingbetty_mp" && ( victim GetStance() == "crouch" || victim GetStance() == "prone" ) )
		iDamage = Int(iDamage/2);
		
	if ( sWeapon == "xm25_mp" && sMeansOfDeath == "MOD_IMPACT" )
		iDamage = 95;
	
	if ( sWeapon == "emp_grenade_mp" && sMeansOfDeath != "MOD_IMPACT" )
		victim notify( "emp_grenaded", eAttacker );
	
	if ( isDefined( level.hostMigrationTimer ) )
		return;
	
	if ( sMeansOfDeath == "MOD_FALLING" )
		victim thread emitFallDamage( iDamage );
		
	if ( sMeansOfDeath == "MOD_EXPLOSIVE_BULLET" && iDamage != 1 )
	{
		iDamage *= getDvarFloat( "scr_explBulletMod" );	
		iDamage = int( iDamage );
	}

	if ( isDefined( eAttacker ) && eAttacker.classname == "worldspawn" )
		eAttacker = undefined;
	
	if ( isDefined( eAttacker ) && isDefined( eAttacker.gunner ) )
		eAttacker = eAttacker.gunner;
	
	attackerIsNPC = isDefined( eAttacker ) && !isDefined( eAttacker.gunner ) && (eAttacker.classname == "script_vehicle" || eAttacker.classname == "misc_turret" || eAttacker.classname == "script_model");
	attackerIsHittingTeammate = level.teamBased && isDefined( eAttacker ) && ( victim != eAttacker ) && isDefined( eAttacker.team ) && ( victim.pers[ "team" ] == eAttacker.team );

	// fixes Bugzilla 136417 where player shoots inside a dropped ballistic vest, sentry or ims, but ends up damaging himself too
	attackerIsInflictorVictim = isDefined( eAttacker ) && isDefined( eInflictor ) && IsDefined( victim ) && isPlayer( eAttacker ) && (eAttacker == eInflictor) && (eAttacker == victim);

	if ( attackerIsInflictorVictim )
		return;

	stunFraction = 0.0;

	if ( iDFlags & level.iDFLAGS_STUN )
	{
		stunFraction = 0.0;
		//victim StunPlayer( 1.0 );
		iDamage = 0.0;
	}
	else if ( sHitLoc == "shield" )
	{
		if ( attackerIsHittingTeammate && level.friendlyfire == 0 )
			return;
		
		if ( sMeansOfDeath == "MOD_PISTOL_BULLET" || sMeansOfDeath == "MOD_RIFLE_BULLET" || sMeansOfDeath == "MOD_EXPLOSIVE_BULLET" && !attackerIsHittingTeammate )
		{
			if ( isPlayer( eAttacker ) )
			{
				eAttacker.lastAttackedShieldPlayer = victim;
				eAttacker.lastAttackedShieldTime = getTime();
			}
			victim notify ( "shield_blocked" );

			// fix turret + shield challenge exploits
			if ( isEnvironmentWeapon( sWeapon ) )
				shieldDamage = 25;
			else
				shieldDamage = maps\mp\perks\_perks::cac_modified_damage( victim, eAttacker, iDamage, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc );
						
			victim.shieldDamage += shieldDamage;

			// fix turret + shield challenge exploits
			if ( !isEnvironmentWeapon( sWeapon ) || cointoss() )
				victim.shieldBulletHits++;

			if ( victim.shieldBulletHits >= level.riotShieldXPBullets )
			{
				if ( self.recentShieldXP > 4 )
					xpVal = int( 50 / self.recentShieldXP );
				else
					xpVal = 50;
				
				printLn( xpVal );
				
				victim thread maps\mp\gametypes\_rank::giveRankXP( "shield_damage", xpVal );
				victim thread giveRecentShieldXP();
				
				victim thread maps\mp\gametypes\_missions::genericChallenge( "shield_damage", victim.shieldDamage );

				victim thread maps\mp\gametypes\_missions::genericChallenge( "shield_bullet_hits", victim.shieldBulletHits );
				
				victim.shieldDamage = 0;
				victim.shieldBulletHits = 0;
			}
		}

		if ( iDFlags & level.iDFLAGS_SHIELD_EXPLOSIVE_IMPACT )
		{
			if (  !attackerIsHittingTeammate )
				victim thread maps\mp\gametypes\_missions::genericChallenge( "shield_explosive_hits", 1 );

			sHitLoc = "none";	// code ignores any damage to a "shield" bodypart.
			if ( !(iDFlags & level.iDFLAGS_SHIELD_EXPLOSIVE_IMPACT_HUGE) )
				iDamage *= 0.0;
		}
		else if ( iDFlags & level.iDFLAGS_SHIELD_EXPLOSIVE_SPLASH )
		{
			if ( isDefined( eInflictor ) && isDefined( eInflictor.stuckEnemyEntity ) && eInflictor.stuckEnemyEntity == victim ) //does enough damage to shield carrier to ensure death
				iDamage = 101;
			
			victim thread maps\mp\gametypes\_missions::genericChallenge( "shield_explosive_hits", 1 );
			sHitLoc = "none";	// code ignores any damage to a "shield" bodypart.
		}
		else
		{
			return;
		}
	}
	else if ( (smeansofdeath == "MOD_MELEE") && IsSubStr( sweapon, "riotshield" ) )
	{
		if ( !(attackerIsHittingTeammate && (level.friendlyfire == 0)) )
		{
			stunFraction = 0.0;
			victim StunPlayer( 0.0 );
		}
	}

	if ( !attackerIsHittingTeammate )
		iDamage = maps\mp\perks\_perks::cac_modified_damage( victim, eAttacker, iDamage, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc );
	
	
	if ( isDefined( level.modifyPlayerDamage ) )	
		iDamage = [[level.modifyPlayerDamage]]( victim, eAttacker, iDamage, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc );
	
	if ( !iDamage )
		return false;
	//eInflictor, eAttacker, victim, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime
	
	//if ( !(attackerIsHittingTeammate && (level.friendlyfire == 0)) )
	//	checkVictimStutter( victim, eAttacker, vDir, sWeapon, sMeansofDeath );
	
	victim.iDFlags = iDFlags;
	victim.iDFlagsTime = getTime();

	if ( game[ "state" ] == "postgame" )
		return;
	if ( victim.sessionteam == "spectator" )
		return;
	if ( isDefined( victim.canDoCombat ) && !victim.canDoCombat )
		return;
	if ( isDefined( eAttacker ) && isPlayer( eAttacker ) && isDefined( eAttacker.canDoCombat ) && !eAttacker.canDoCombat )
		return;

	// handle vehicles/turrets and friendly fire
	if ( attackerIsNPC && attackerIsHittingTeammate )
	{
		if ( sMeansOfDeath == "MOD_CRUSH" )
		{
			victim _suicide();
			return;
		}
		
		if ( !level.friendlyfire )
			return;
	}

	prof_begin( "PlayerDamage flags/tweaks" );

	// Don't do knockback if the damage direction was not specified
	if ( !isDefined( vDir ) )
		iDFlags |= level.iDFLAGS_NO_KNOCKBACK;

	friendly = false;

	if ( ( victim.health == victim.maxhealth && ( !isDefined( victim.lastStand ) || !victim.lastStand )  ) || !isDefined( victim.attackers ) && !isDefined( victim.lastStand )  )
	{
		victim.attackers = [];
		victim.attackerData = [];
	}

	if ( isHeadShot( sWeapon, sHitLoc, sMeansOfDeath, eAttacker ) )
		sMeansOfDeath = "MOD_HEAD_SHOT";

	if ( maps\mp\gametypes\_tweakables::getTweakableValue( "game", "onlyheadshots" ) )
	{
		if ( sMeansOfDeath == "MOD_PISTOL_BULLET" || sMeansOfDeath == "MOD_RIFLE_BULLET" || sMeansOfDeath == "MOD_EXPLOSIVE_BULLET" )
			return;
		else if ( sMeansOfDeath == "MOD_HEAD_SHOT" )
			iDamage = 150;
	}

	// explosive barrel/car detection
	if ( sWeapon == "none" && isDefined( eInflictor ) )
	{
		if ( isDefined( eInflictor.destructible_type ) && isSubStr( eInflictor.destructible_type, "vehicle_" ) )
			sWeapon = "destructible_car";
	}

	if ( getTime() < (victim.spawnTime + level.killstreakSpawnShield) )
	{
		damageLimit = int( max( (victim.health / 4), 1 ) );
		if ( (iDamage >= damageLimit) && isKillstreakWeapon( sWeapon ) )
		{
			//println( "damage was: " + iDamage + "  is: " + damageLimit + " of health: " + victim.health);
			iDamage = damageLimit;
		}
	}

	prof_end( "PlayerDamage flags/tweaks" );

	// check for completely getting out of the damage
	if ( !(iDFlags & level.iDFLAGS_NO_PROTECTION) )
	{
		// items you own don't damage you in FFA
		if ( !level.teamBased && attackerIsNPC && isDefined( eAttacker.owner ) && eAttacker.owner == victim )
		{
			prof_end( "PlayerDamage player" );

			if ( sMeansOfDeath == "MOD_CRUSH" )
				victim _suicide();

			return;
		}

		if ( ( isSubStr( sMeansOfDeath, "MOD_GRENADE" ) || isSubStr( sMeansOfDeath, "MOD_EXPLOSIVE" ) || isSubStr( sMeansOfDeath, "MOD_PROJECTILE" ) ) && isDefined( eInflictor ) && isDefined( eAttacker ) )
		{
			// protect players from spawnkill grenades (IW5 ensure attacker is not player)
			if ( victim != eAttacker && eInflictor.classname == "grenade" && ( victim.lastSpawnTime + 3500 ) > getTime() && isDefined( victim.lastSpawnPoint ) && distance( eInflictor.origin, victim.lastSpawnPoint.origin ) < 250 )
			{
				prof_end( "PlayerDamage player" );
				return;
			}

			victim.explosiveInfo = [];
			victim.explosiveInfo[ "damageTime" ] = getTime();
			victim.explosiveInfo[ "damageId" ] = eInflictor getEntityNumber();
			victim.explosiveInfo[ "returnToSender" ] = false;
			victim.explosiveInfo[ "counterKill" ] = false;
			victim.explosiveInfo[ "chainKill" ] = false;
			victim.explosiveInfo[ "cookedKill" ] = false;
			victim.explosiveInfo[ "throwbackKill" ] = false;
			victim.explosiveInfo[ "suicideGrenadeKill" ] = false;
			victim.explosiveInfo[ "weapon" ] = sWeapon;

			isFrag = isSubStr( sWeapon, "frag_" );

			if ( eAttacker != victim )
			{
				if ( ( isSubStr( sWeapon, "c4_" ) || isSubStr( sWeapon, "claymore_" ) ) && isDefined( eAttacker ) && isDefined( eInflictor.owner ) )
				{
					victim.explosiveInfo[ "returnToSender" ] = ( eInflictor.owner == victim );
					victim.explosiveInfo[ "counterKill" ] = isDefined( eInflictor.wasDamaged );
					victim.explosiveInfo[ "chainKill" ] = isDefined( eInflictor.wasChained );
					victim.explosiveInfo[ "bulletPenetrationKill" ] = isDefined( eInflictor.wasDamagedFromBulletPenetration );
					victim.explosiveInfo[ "cookedKill" ] = false;
				}

				if ( isDefined( eAttacker.lastGrenadeSuicideTime ) && eAttacker.lastGrenadeSuicideTime >= gettime() - 66 && isFrag )
					victim.explosiveInfo[ "suicideGrenadeKill" ] = true;
			}

			if ( isFrag )
			{
				victim.explosiveInfo[ "cookedKill" ] = isDefined( eInflictor.isCooked );
				victim.explosiveInfo[ "throwbackKill" ] = isDefined( eInflictor.threwBack );
			}
			
			victim.explosiveInfo[ "stickKill" ] = isDefined( eInflictor.isStuck ) && eInflictor.isStuck == "enemy";
			victim.explosiveInfo[ "stickFriendlyKill" ] = isDefined( eInflictor.isStuck ) && eInflictor.isStuck == "friendly";
			
			if( isPlayer( eAttacker ) && eAttacker != self )
			{
				self maps\mp\gametypes\_gamelogic::setInflictorStat( eInflictor, eAttacker, sWeapon );
			}
		}
	
		if ( isPlayer( eAttacker ) && isDefined( eAttacker.pers[ "participation" ] ) )
			eAttacker.pers[ "participation" ]++ ;
		else if( isPlayer( eAttacker ) )
			eAttacker.pers[ "participation" ] = 1;

		prevHealthRatio = victim.health / victim.maxhealth;

		if ( attackerIsHittingTeammate )
		{
			if ( !matchMakingGame() && isPlayer(eAttacker) )
				eAttacker incPlayerStat( "mostff", 1 );
			
			prof_begin( "PlayerDamage player" );// profs automatically end when the function returns
			if ( level.friendlyfire == 0 || ( !isPlayer(eAttacker) && level.friendlyfire != 1 ) )// no one takes damage
			{
				if ( sWeapon == "artillery_mp" || sWeapon == "stealth_bomb_mp" )
					victim damageShellshockAndRumble( eInflictor, sWeapon, sMeansOfDeath, iDamage, iDFlags, eAttacker );
				return;
			}
			else if ( level.friendlyfire == 1 )// the friendly takes damage
			{
				if ( iDamage < 1 )
					iDamage = 1;

				// this fixes a bug where the friendly could kill the jugg in one or two shots
				if( victim isJuggernaut() )
					iDamage = maps\mp\perks\_perks::cac_modified_damage( victim, eAttacker, iDamage, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc );

				victim.lastDamageWasFromEnemy = false;

				victim finishPlayerDamageWrapper( eInflictor, eAttacker, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime, stunFraction );
			}
			else if ( ( level.friendlyfire == 2 ) && isReallyAlive( eAttacker ) )// only the attacker takes damage
			{
				iDamage = int( iDamage * .5 );
				if ( iDamage < 1 )
					iDamage = 1;

				eAttacker.lastDamageWasFromEnemy = false;

				eAttacker.friendlydamage = true;
				eAttacker finishPlayerDamageWrapper( eInflictor, eAttacker, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime, stunFraction );
				eAttacker.friendlydamage = undefined;
			}
			else if ( level.friendlyfire == 3 && isReallyAlive( eAttacker ) )// both friendly and attacker take damage
			{
				iDamage = int( iDamage * .5 );
				if ( iDamage < 1 )
					iDamage = 1;

				victim.lastDamageWasFromEnemy = false;
				eAttacker.lastDamageWasFromEnemy = false;

				victim finishPlayerDamageWrapper( eInflictor, eAttacker, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime, stunFraction );
				if ( isReallyAlive( eAttacker ) )// may have died due to friendly fire punishment
				{
					eAttacker.friendlydamage = true;
					eAttacker finishPlayerDamageWrapper( eInflictor, eAttacker, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime, stunFraction );
					eAttacker.friendlydamage = undefined;
				}
			}

			friendly = true;
			
		}
		else// not hitting teammate
		{
			prof_begin( "PlayerDamage world" );

			if ( iDamage < 1 )
				iDamage = 1;

			if ( isDefined( eAttacker ) && isPlayer( eAttacker ) )
				addAttacker( victim, eAttacker, eInflictor, sWeapon, iDamage, vPoint, vDir, sHitLoc, psOffsetTime, sMeansOfDeath );
			
			if ( sMeansOfDeath == "MOD_EXPLOSIVE" || sMeansOfDeath == "MOD_GRENADE_SPLASH" && iDamage < victim.health )
				victim notify( "survived_explosion", eAttacker );

			if ( isdefined( eAttacker ) )
				level.lastLegitimateAttacker = eAttacker;

			if ( isdefined( eAttacker ) && isPlayer( eAttacker ) && isDefined( sWeapon ) )
				eAttacker thread maps\mp\gametypes\_weapons::checkHit( sWeapon, victim );

			if ( isdefined( eAttacker ) && isPlayer( eAttacker ) && isDefined( sWeapon ) && eAttacker != victim )
			{
				eAttacker thread maps\mp\_events::damagedPlayer( self, iDamage, sWeapon );
				victim.attackerPosition = eAttacker.origin;
			}
			else
			{
				victim.attackerPosition = undefined;
			}

			if ( issubstr( sMeansOfDeath, "MOD_GRENADE" ) && isDefined( eInflictor.isCooked ) )
				victim.wasCooked = getTime();
			else
				victim.wasCooked = undefined;

			victim.lastDamageWasFromEnemy = ( isDefined( eAttacker ) && ( eAttacker != victim ) );

			if ( victim.lastDamageWasFromEnemy )
				eAttacker.damagedPlayers[ victim.guid ] = getTime();

			victim finishPlayerDamageWrapper( eInflictor, eAttacker, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime, stunFraction );

			if ( isDefined( level.ac130player ) && isDefined( eAttacker ) && ( level.ac130player == eAttacker ) )
				level notify( "ai_pain", victim );

			victim thread maps\mp\gametypes\_missions::playerDamaged( eInflictor, eAttacker, iDamage, sMeansOfDeath, sWeapon, sHitLoc );

			prof_end( "PlayerDamage world" );
			
		}

		if ( attackerIsNPC && isDefined( eAttacker.gunner ) )
			damager = eAttacker.gunner;
		else
			damager = eAttacker;

		if ( isDefined( damager) && damager != victim && iDamage > 0 )
		{
			if( iDFlags & level.iDFLAGS_STUN )
				typeHit = "stun";
			else if( ( IsExplosiveDamageMOD( sMeansOfDeath ) && victim _hasPerk( "_specialty_blastshield" ) ) )
				typeHit = "hitBodyArmor";
			else if( victim _hasPerk( "specialty_combathigh") )
				typeHit = "hitEndGame";
			else if( isDefined( victim.hasLightArmor ) )
				typeHit = "hitLightArmor";
			else if( victim isJuggernaut() )
				typeHit = "hitJuggernaut";
			else if( !shouldWeaponFeedback( sWeapon ) )
				typeHit = "none";
			else
				typeHit = "standard";
				
			damager thread maps\mp\gametypes\_damagefeedback::updateDamageFeedback( typeHit );
		}

		victim.hasDoneCombat = true;
	}

	if ( isdefined( eAttacker ) && ( eAttacker != victim ) && !friendly )
		level.useStartSpawns = false;

	// show directional blood if any damage taken
	// have it only be turned on when wanted for now
	//if( GetDvarInt( "scr_dir_blood" ) == 1 )
	//{
		if ( iDamage > 0 && IsDefined( eAttacker ) && !victim isUsingRemote() )
		{
			victim thread maps\mp\gametypes\_shellshock::bloodEffect( eAttacker.origin );
		}
	//}

	//=================
	// Damage Logging
	//=================

	prof_begin( "PlayerDamage log" );

/#
	if ( getDvarInt( "g_debugDamage" ) )
	{
		PrintLn( "client:" + victim GetEntityNumber() + " health:" + victim.health + " attacker:" + eAttacker GetEntityNumber() + " inflictor is player:" + isPlayer( eInflictor ) + " damage:" + iDamage + " hitLoc:" + sHitLoc + " range:" + Distance( eAttacker.origin, victim.origin ) );
	}
#/

	if ( victim.sessionstate != "dead" )
	{
		lpselfnum = victim getEntityNumber();
		lpselfname = victim.name;
		lpselfteam = victim.pers[ "team" ];
		lpselfGuid = victim.guid;
		lpattackerteam = "";

		if ( isPlayer( eAttacker ) )
		{
			lpattacknum = eAttacker getEntityNumber();
			lpattackGuid = eAttacker.guid;
			lpattackname = eAttacker.name;
			lpattackerteam = eAttacker.pers[ "team" ];
		}
		else
		{
			lpattacknum = -1;
			lpattackGuid = "";
			lpattackname = "";
			lpattackerteam = "world";
		}

		logPrint( "D;" + lpselfGuid + ";" + lpselfnum + ";" + lpselfteam + ";" + lpselfname + ";" + lpattackGuid + ";" + lpattacknum + ";" + lpattackerteam + ";" + lpattackname + ";" + sWeapon + ";" + iDamage + ";" + sMeansOfDeath + ";" + sHitLoc + "\n" );
	}

	HitlocDebug( eAttacker, victim, iDamage, sHitLoc, iDFlags );

	if( isDefined( eAttacker ) && eAttacker != victim )
	{
		if ( isPlayer( eAttacker ) )
			eAttacker incPlayerStat( "damagedone", iDamage );
		
		victim incPlayerStat( "damagetaken", iDamage );
	}

	prof_end( "PlayerDamage log" );
}

shouldWeaponFeedback( sWeapon )
{
	// should this weapon give feedback
	switch( sWeapon )
	{
	case "stealth_bomb_mp":
	case "artillery_mp":
		return false;
	}

	return true;
}

checkVictimStutter( victim, eAttacker, vDir, sWeapon, sMeansOfDeath )
{
	if ( sMeansOfDeath == "MOD_PISTOL_BULLET" || sMeansOfDeath == "MOD_RIFLE_BULLET" || sMeansOfDeath == "MOD_HEAD_SHOT" )
	{
		if ( Distance( victim.origin, eAttacker.origin ) > 256 )
			return;
		
		vicVelocity = victim getVelocity();
		
		if (  LengthSquared( vicVelocity ) < 10 )
			return;
		
		facing = findIsFacing( victim, eAttacker, 25 );
	
		if ( facing )
		{	
			victim thread stutterStep();
		}	
	}
}

		
stutterStep( enterScale )
{	
	self endon( "disconnect" );
	self endon( "death" );
	level endon( "game_ended" );
	
	
	self.inStutter = true;
	
	self.moveSpeedScaler = 0.05;
	self maps\mp\gametypes\_weapons::updateMoveSpeedScale();
	wait( .5 );
	
	self.moveSpeedScaler = 1;
	if( self _hasPerk( "specialty_lightweight" ) )
		self.moveSpeedScaler = lightWeightScalar();
	
	self maps\mp\gametypes\_weapons::updateMoveSpeedScale();
	
	self.inStutter = false;
}


addAttacker( victim, eAttacker, eInflictor, sWeapon, iDamage, vPoint, vDir, sHitLoc, psOffsetTime, sMeansOfDeath )
{
	if ( !isDefined( victim.attackerData ) )
		victim.attackerData = [];
	
	if ( !isDefined( victim.attackerData[ eAttacker.guid ] ) )
	{
		victim.attackers[ eAttacker.guid ] = eAttacker;
		// we keep an array of attackers by their client ID so we can easily tell
		// if they're already one of the existing attackers in the above if().
		// we store in this array data that is useful for other things, like challenges
		victim.attackerData[ eAttacker.guid ] = SpawnStruct();
		victim.attackerData[ eAttacker.guid ].damage = 0;	
		victim.attackerData[ eAttacker.guid ].attackerEnt = eAttacker;
		victim.attackerData[ eAttacker.guid ].firstTimeDamaged = getTime();				
	}
	if ( maps\mp\gametypes\_weapons::isPrimaryWeapon( sWeapon ) && ! maps\mp\gametypes\_weapons::isSideArm( sWeapon ) )
		victim.attackerData[ eAttacker.guid ].isPrimary = true;
	
	victim.attackerData[ eAttacker.guid ].damage += iDamage;
	victim.attackerData[ eAttacker.guid ].weapon = sWeapon;
	victim.attackerData[ eAttacker.guid ].vPoint = vPoint;
	victim.attackerData[ eAttacker.guid ].vDir = vDir;
	victim.attackerData[ eAttacker.guid ].sHitLoc = sHitLoc;
	victim.attackerData[ eAttacker.guid ].psOffsetTime = psOffsetTime;
	victim.attackerData[ eAttacker.guid ].sMeansOfDeath = sMeansOfDeath;
	victim.attackerData[ eAttacker.guid ].attackerEnt = eAttacker;
	victim.attackerData[ eAttacker.guid ].lasttimeDamaged = getTime();
	
	if ( isDefined( eInflictor ) && !isPlayer( eInflictor ) && isDefined( eInflictor.primaryWeapon ) )
		victim.attackerData[ eAttacker.guid ].sPrimaryWeapon = eInflictor.primaryWeapon;
	else if ( isDefined( eAttacker ) && isPlayer( eAttacker ) && eAttacker getCurrentPrimaryWeapon() != "none" )
		victim.attackerData[ eAttacker.guid ].sPrimaryWeapon = eAttacker getCurrentPrimaryWeapon();
	else
		victim.attackerData[ eAttacker.guid ].sPrimaryWeapon = undefined;
}

resetAttackerList()
{
	self endon( "disconnect" );
	self endon( "death" );
	level endon( "game_ended" );
	
	//wait is to offset premature calling in _healthOverlay
	wait( 1.75 ); 
	self.attackers = [];
	self.attackerData = [];
}


Callback_PlayerDamage( eInflictor, eAttacker, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime )
{
	Callback_PlayerDamage_internal( eInflictor, eAttacker, self, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime );
}


finishPlayerDamageWrapper( eInflictor, eAttacker, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime, stunFraction )
{
	if ( (self isUsingRemote() ) && (iDamage >= self.health) && !(iDFlags & level.iDFLAGS_STUN) )
	{
		if ( !isDefined( vDir ) )
			vDir = ( 0,0,0 );

		if ( !isDefined( eAttacker ) && !isDefined( eInflictor ) )
		{
			eAttacker = self;
			eInflictor = eAttacker;
		}
		
		assert( isDefined( eAttacker ) );
		assert( isDefined( eInflictor ) );

		PlayerKilled_internal( eInflictor, eAttacker, self, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, 0, true );
	}
	else
	{
		if ( !self Callback_KillingBlow( eInflictor, eAttacker, iDamage - (iDamage * stunFraction), iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime ) )
			return;
			
		if ( !isAlive(self) )
			return;

		self finishPlayerDamage( eInflictor, eAttacker, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime, stunFraction );
	}

	if ( sMeansOfDeath == "MOD_EXPLOSIVE_BULLET" )
		self shellShock( "damage_mp", getDvarFloat( "scr_csmode" ) );

	self damageShellshockAndRumble( eInflictor, sWeapon, sMeansOfDeath, iDamage, iDFlags, eAttacker );
}


Callback_PlayerLastStand( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, psOffsetTime, deathAnimDuration )
{	
		
	lastStandParams = spawnStruct();
	lastStandParams.eInflictor = eInflictor;
	lastStandParams.attacker = attacker;
	lastStandParams.iDamage = iDamage;
	lastStandParams.attackerPosition = attacker.origin;
	if ( attacker == self )
		lastStandParams.sMeansOfDeath = "MOD_SUICIDE";
	else
		lastStandParams.sMeansOfDeath = sMeansOfDeath;
	
	lastStandParams.sWeapon = sWeapon;
	if ( isDefined( attacker ) && isPlayer( attacker ) && attacker getCurrentPrimaryWeapon() != "none" )
		lastStandParams.sPrimaryWeapon = attacker getCurrentPrimaryWeapon();
	else
		lastStandParams.sPrimaryWeapon = undefined;
	lastStandParams.vDir = vDir;
	lastStandParams.sHitLoc = sHitLoc;
	lastStandParams.lastStandStartTime = getTime();

	mayDoLastStand = mayDoLastStand( sWeapon, sMeansOfDeath, sHitLoc );
	
	//if ( mayDoLastStand )
	//	mayDoLastStand = !self checkForceBleedOut();
	
	if ( isDefined( self.endGame ) )
		mayDoLastStand = false;
	
	if ( level.teamBased && isDefined( attacker.team ) && attacker.team == self.team )
		mayDoLastStand = false;

	 /#
	if ( getdvar( "scr_forcelaststand" ) == "1" )
		mayDoLastStand = true;
	#/
	
	if ( !mayDoLastStand )
	{
		self.lastStandParams = lastStandParams;
		self.useLastStandParams = true;
		self _suicide();
		return;
	}
	
	self.inLastStand = true;

	notifyData = spawnStruct();
	if ( self _hasPerk( "specialty_finalstand" ) )
	{
		notifyData.titleText = game[ "strings" ][ "final_stand" ];
		notifyData.iconName = "specialty_finalstand";
	}
	else if ( self _hasPerk( "specialty_c4death" ) )
	{
		notifyData.titleText = game[ "strings" ][ "c4_death" ];
		notifyData.iconName = "specialty_c4death";
	}
	else
	{
		notifyData.titleText = game[ "strings" ][ "last_stand" ];
		notifyData.iconName = "specialty_pistoldeath";
	}
	notifyData.glowColor = ( 1, 0, 0 );
	notifyData.sound = "mp_last_stand";
	notifyData.duration = 2.0;

	self.health = 1;

	self thread maps\mp\gametypes\_hud_message::notifyMessage( notifyData );

	grenadeTypePrimary = "frag_grenade_mp";

	if ( isDefined( level.ac130player ) && isDefined( attacker ) && level.ac130player == attacker )
		level notify( "ai_crawling", self );
	
	if ( self _hasPerk( "specialty_finalstand" ) )
	{
		self.lastStandParams = lastStandParams;
		self.inFinalStand = true;
		
		weaponList = self GetWeaponsListExclusives();
		foreach ( weapon in weaponList )
			self takeWeapon( weapon );
		
		self _disableUsability();

		self thread enableLastStandWeapons();
		self thread lastStandTimer( 20, true );		
	}
	else if ( self _hasPerk( "specialty_c4death" ) )
	{
		self.lastStandParams = lastStandParams;

		self takeAllWeapons();
		self giveWeapon( "c4death_mp", 0, false );
		self switchToWeapon( "c4death_mp" );
		self _disableUsability();
		self.inC4Death = true;
		
		//self thread dieAfterTime( 7 );
		self thread lastStandTimer( 20, false );	
		self thread detonateOnUse();
		self thread detonateOnDeath();	
	}
	else if ( level.dieHardMode )
	{	
		self.lastStandParams = lastStandParams;
		self thread enableLastStandWeapons();
		self thread lastStandTimer( 20, false );
		self _disableUsability();
	}
	else // normal last stand
	{
		self.lastStandParams = lastStandParams;
		
		pistolWeapon = undefined;
		
		weaponsList = self GetWeaponsListPrimaries();
		foreach ( weapon in weaponsList )
		{
			if ( maps\mp\gametypes\_weapons::isSideArm( weapon ) )
				pistolWeapon = weapon;			
		}
			
		if ( !isDefined( pistolWeapon ) )
		{
			pistolWeapon = "iw5_usp45_mp";
			self _giveWeapon( pistolWeapon );
		}
	
		self giveMaxAmmo( pistolWeapon );
		self DisableWeaponSwitch();
		self _disableUsability();
		
		if ( !self _hasPerk("specialty_laststandoffhand") )
			self DisableOffhandWeapons();
				
		self switchToWeapon( pistolWeapon );
		
		self thread lastStandTimer( 10, false );
	}
}

dieAfterTime( time )
{
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "joined_team" );
	level endon( "game_ended" );
	
	wait ( time );
	self.useLastStandParams = true;
	self _suicide();
}

detonateOnUse()
{
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "joined_team" );
	level endon( "game_ended" );
	
	self waittill( "detonate" );
	self.useLastStandParams = true;
	self c4DeathDetonate();
}

detonateOnDeath()
{
	self endon( "detonate" );
	self endon( "disconnect" );
	self endon( "joined_team" );
	level endon( "game_ended" );
	
	self waittill( "death" );
	self c4DeathDetonate();
}

c4DeathDetonate()
{
	self playSound( "detpack_explo_default" );
	self.c4DeathEffect = playFX( level.c4Death, self.origin );
	RadiusDamage( self.origin, 400, 100, 100, self );
	
	if ( isAlive( self ) )
		self _suicide();
}

enableLastStandWeapons()
{
	self endon( "death" );
	self endon( "disconnect" );
	level endon( "game_ended" );

	self freezeControlsWrapper( true );
	wait .30;
	
	self freezeControlsWrapper( false );
}

lastStandTimer( delay, isFinalStand )
{
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "revive");
	level endon( "game_ended" );
	
	level notify ( "player_last_stand" );
	
	self thread lastStandWaittillDeath();
	
	self.lastStand = true;
	
	if ( !isFinalStand && !level.dieHardMode && ( !isDefined( self.inC4Death ) || !self.inC4Death ) )
	{
		self thread lastStandAllowSuicide();
		self setLowerMessage( "last_stand", &"PLATFORM_COWARDS_WAY_OUT", undefined, undefined, undefined, undefined, undefined, undefined, true );
		self thread lastStandKeepOverlay();
	}
	
	if ( level.dieHardMode == 1 && level.dieHardMode != 2 )
	{
		reviveEnt = spawn( "script_model", self.origin );
		reviveEnt setModel( "tag_origin" );
		reviveEnt setCursorHint( "HINT_NOICON" );
		reviveEnt setHintString( &"PLATFORM_REVIVE" );

		reviveEnt reviveSetup( self );
		reviveEnt endon ( "death" );

		reviveIcon = newTeamHudElem( self.team );
		reviveIcon setShader( "waypoint_revive", 8, 8 );
		reviveIcon setWaypoint( true, true );
		reviveIcon SetTargetEnt( self );
		reviveIcon thread destroyOnReviveEntDeath( reviveEnt );

		reviveIcon.color = (0.33, 0.75, 0.24);
		self playDeathSound();
		
		if ( isFinalStand )
		{
			wait( delay );
			
			if ( self.inFinalStand )
				self thread lastStandBleedOut( isFinalStand, reviveEnt );
		}
		
		return;
	}
	else if( level.dieHardMode == 2 )
	{
		self thread lastStandKeepOverlay();
		reviveEnt = spawn( "script_model", self.origin );
		reviveEnt setModel( "tag_origin" );
		reviveEnt setCursorHint( "HINT_NOICON" );
		reviveEnt setHintString( &"PLATFORM_REVIVE" );

		reviveEnt reviveSetup( self );
		reviveEnt endon ( "death" );

		reviveIcon = newTeamHudElem( self.team );
		reviveIcon setShader( "waypoint_revive", 8, 8 );
		reviveIcon setWaypoint( true, true );
		reviveIcon SetTargetEnt( self );
		reviveIcon thread destroyOnReviveEntDeath( reviveEnt );

		reviveIcon.color = (0.33, 0.75, 0.24);
		self playDeathSound();
		
		if ( isFinalStand )
		{
			wait( delay );
			
			if ( self.inFinalStand )
				self thread lastStandBleedOut( isFinalStand, reviveEnt );
		}
		
		wait delay / 3;
		reviveIcon.color = (1.0, 0.64, 0.0);
		
		while ( reviveEnt.inUse )
			wait ( 0.05 );
		
		self playDeathSound();	
		wait delay / 3;
		reviveIcon.color = (1.0, 0.0, 0.0);

		while ( reviveEnt.inUse )
			wait ( 0.05 );

		self playDeathSound();
		wait delay / 3;	

		while ( reviveEnt.inUse )
			wait ( 0.05 );
		
		wait( 0.05 ); 
		self thread lastStandBleedOut( isFinalStand );
		return;
	}
	
	self thread lastStandKeepOverlay();
	wait( delay );
	self thread lastStandBleedout( isFinalStand );

}

maxHealthOverlay( maxHealth, refresh )
{
	self endon( "stop_maxHealthOverlay" );
	self endon( "revive" );
	self endon( "death" );
	
	for( ;; )
	{
		self.health -= 1;
		self.maxHealth = maxHealth;
		wait( .05 );
		self.maxHealth = 50;
		self.health += 1;
	
		wait ( .50 );
	}	
}

lastStandBleedOut( reviveOnBleedOut, reviveEnt )
{
	if ( reviveOnBleedOut )
	{
		self.lastStand = undefined;
		self.inFinalStand = false;
		self notify( "revive" );
		self clearLowerMessage( "last_stand" );
		maps\mp\gametypes\_playerlogic::lastStandRespawnPlayer();
		
		if( isDefined( reviveEnt ) )
			reviveEnt Delete();
	}
	else
	{
		self.useLastStandParams = true;
		self.beingRevived = false;
		self _suicide();
	}
}


lastStandAllowSuicide()
{
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "game_ended" );
	self endon( "revive");

	while ( 1 )
	{
		if ( self useButtonPressed() )
		{
			pressStartTime = gettime();
			while ( self useButtonPressed() )
			{
				wait .05;
				if ( gettime() - pressStartTime > 700 )
					break;
			}
			if ( gettime() - pressStartTime > 700 )
				break;
		}
		wait .05;
	}

	self thread lastStandBleedOut( false );
}

lastStandKeepOverlay()
{
	level endon( "game_ended" );
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "revive" );

	// keep the health overlay going by making code think the player is getting damaged
	while ( !level.gameEnded )
	{
		self.health = 2;
		wait .05;
		self.health = 1;
		wait .5;
	}
	
	self.health = self.maxhealth;
}


lastStandWaittillDeath()
{
	self endon( "disconnect" );
	self endon( "revive" );
	level endon( "game_ended" );
	self waittill( "death" );

	self clearLowerMessage( "last_stand" );
	self.lastStand = undefined;
}


mayDoLastStand( sWeapon, sMeansOfDeath, sHitLoc )
{
	if ( sMeansOfDeath == "MOD_TRIGGER_HURT" )
		return false;
	
	if ( sMeansOfDeath != "MOD_PISTOL_BULLET" && sMeansOfDeath != "MOD_RIFLE_BULLET" && sMeansOfDeath != "MOD_FALLING" && sMeansOfDeath != "MOD_EXPLOSIVE_BULLET" )
		return false;

	if ( sMeansOfDeath == "MOD_IMPACT" && sWeapon == "throwingknife_mp" )
		return false;
		
	if ( sMeansOfDeath == "MOD_IMPACT" && ( sWeapon == "m79_mp" || isSubStr(sWeapon, "gl_") ) )
		return false;

	if ( isHeadShot( sWeapon, sHitLoc, sMeansOfDeath ) )
		return false;
	
	if ( self isUsingRemote() )
		return false;

	return true;
}


ensureLastStandParamsValidity()
{
	// attacker may have become undefined if the player that killed me has disconnected
	if ( !isDefined( self.lastStandParams.attacker ) )
		self.lastStandParams.attacker = self;
}

getHitLocHeight( sHitLoc )
{
	switch( sHitLoc )
	{
		case "helmet":
		case "head":
		case "neck":
			return 60;
		case "torso_upper":
		case "right_arm_upper":
		case "left_arm_upper":
		case "right_arm_lower":
		case "left_arm_lower":
		case "right_hand":
		case "left_hand":
		case "gun":
			return 48;
		case "torso_lower":
			return 40;
		case "right_leg_upper":
		case "left_leg_upper":
			return 32;
		case "right_leg_lower":
		case "left_leg_lower":
			return 10;
		case "right_foot":
		case "left_foot":
			return 5;
	}
	return 48;
}

delayStartRagdoll( ent, sHitLoc, vDir, sWeapon, eInflictor, sMeansOfDeath )
{
	if ( isDefined( ent ) )
	{
		deathAnim = ent getCorpseAnim();
		if ( animhasnotetrack( deathAnim, "ignore_ragdoll" ) )
			return;
	}
	
	if ( isDefined( level.noRagdollEnts ) && level.noRagdollEnts.size )
	{
		foreach( noRag in level.noRagdollEnts )
		{
			if ( distanceSquared( ent.origin, noRag.origin ) <	65536 ) //256^2
				return;
		}
	}

	wait( 0.2 );

	if ( !isDefined( ent ) )
		return;

	if ( ent isRagDoll() )
		return;

	deathAnim = ent getcorpseanim();

	startFrac = 0.35;

	if ( animhasnotetrack( deathAnim, "start_ragdoll" ) )
	{
		times = getnotetracktimes( deathAnim, "start_ragdoll" );
		if ( isDefined( times ) )
			startFrac = times[ 0 ];
	}

	waitTime = startFrac * getanimlength( deathAnim );
	wait( waitTime );

	if ( isDefined( ent ) )
	{
		ent startragdoll( 1 );
	}
}


getMostKilledBy()
{
	mostKilledBy = "";
	killCount = 0;

	killedByNames = getArrayKeys( self.killedBy );

	for ( index = 0; index < killedByNames.size; index++ )
	{
		killedByName = killedByNames[ index ];
		if ( self.killedBy[ killedByName ] <= killCount )
			continue;

		killCount = self.killedBy[ killedByName ];
		mostKilleBy = killedByName;
	}

	return mostKilledBy;
}


getMostKilled()
{
	mostKilled = "";
	killCount = 0;

	killedNames = getArrayKeys( self.killedPlayers );

	for ( index = 0; index < killedNames.size; index++ )
	{
		killedName = killedNames[ index ];
		if ( self.killedPlayers[ killedName ] <= killCount )
			continue;

		killCount = self.killedPlayers[ killedName ];
		mostKilled = killedName;
	}

	return mostKilled;
}


damageShellshockAndRumble( eInflictor, sWeapon, sMeansOfDeath, iDamage, iDFlags, eAttacker )
{
	self thread maps\mp\gametypes\_weapons::onWeaponDamage( eInflictor, sWeapon, sMeansOfDeath, iDamage, eAttacker );
	self PlayRumbleOnEntity( "damage_heavy" );
}


reviveSetup( owner )
{
	team = owner.team;
	
	self linkTo( owner, "tag_origin" );

	self.owner = owner;
	self.inUse = false;
	self makeUsable();
	self updateUsableByTeam( team );
	self thread trackTeamChanges( team );
	
	self thread reviveTriggerThink( team );
	
	self thread deleteOnReviveOrDeathOrDisconnect();
}


deleteOnReviveOrDeathOrDisconnect()
{
	self endon ( "death" );
	
	self.owner waittill_any ( "death", "disconnect" );
	
	self delete();
}


updateUsableByTeam( team )
{
	foreach (player in level.players)
	{
		if ( team == player.team && player != self.owner )
			self enablePlayerUse( player );	
		else
			self disablePlayerUse( player );	
	}	
}


trackTeamChanges( team )
{
	self endon ( "death" );
	
	while ( true )
	{
		level waittill ( "joined_team" );
		
		self updateUsableByTeam( team );
	}
}


trackLastStandChanges( team )
{
	self endon ( "death" );
	
	while ( true )
	{
		level waittill ( "player_last_stand" );
		
		self updateUsableByTeam( team );
	}
}


reviveTriggerThink( team )
{
	self endon ( "death" );
	level endon ( "game_ended" );
	
	for ( ;; )
	{
		self waittill ( "trigger", player );
		self.owner.beingRevived = true;

		if ( isDefined(player.beingRevived) && player.beingRevived )
		{
			self.owner.beingRevived = false;
			continue;
		}
			
		self makeUnUsable();
		self.owner freezeControlsWrapper( true );

		revived = self useHoldThink( player );
		self.owner.beingRevived = false;
		
		if ( !isAlive( self.owner ) )
		{	
			self delete();
			return;
		}

		self.owner freezeControlsWrapper( false );
			
		if ( revived )
		{
			player thread maps\mp\gametypes\_hud_message::SplashNotifyDelayed( "reviver", 200 );
			player thread maps\mp\gametypes\_rank::giveRankXP( "reviver", 200 );

			self.owner.lastStand = undefined;
			self.owner clearLowerMessage( "last_stand" );
			
			self.owner.moveSpeedScaler = 1;
			if( self.owner _hasPerk( "specialty_lightweight" ) )
				self.owner.moveSpeedScaler = lightWeightScalar();
			
			self.owner.maxHealth = 100;
			
			self.owner maps\mp\gametypes\_weapons::updateMoveSpeedScale();
			self.owner maps\mp\gametypes\_playerlogic::lastStandRespawnPlayer();

			self.owner givePerk( "specialty_pistoldeath", false );
			self.owner.beingRevived = false;
			
			self delete();
			return;
		}
			
		self makeUsable();
		self updateUsableByTeam( team );
	}
}



/*
=============
useHoldThink

Claims the use trigger for player and displays a use bar
Returns true if the player sucessfully fills the use bar
=============
*/
useHoldThink( player )
{
	reviveSpot = spawn( "script_origin", self.origin );
	reviveSpot hide();	
	player playerLinkTo( reviveSpot );		
	player PlayerLinkedOffsetEnable();
	
	player _disableWeapon();
	
	self.curProgress = 0;
	self.inUse = true;
	self.useRate = 0;
	self.useTime = 3000;
	
	player thread personalUseBar( self );
	
	result = useHoldThinkLoop( player );
	
	if ( isDefined( player ) && isReallyAlive( player ) )
	{
		player Unlink();
		player _enableWeapon();
	}

	if ( isDefined( result ) && result )
	{
		self.owner thread maps\mp\gametypes\_hud_message::playerCardSplashNotify( "revived", player );
		self.owner.inlaststand = false;
		return true;
	}
	
	self.inUse = false;
	reviveSpot Delete();	
	return false;
}


personalUseBar( object )
{
	useBar = self createPrimaryProgressBar();
	useBarText = self createPrimaryProgressBarText();
	useBarText setText( &"MPUI_REVIVING" );

	objUseBar = object.owner createPrimaryProgressBar();
	objUseBarText = object.owner createPrimaryProgressBarText();
	objUseBarText setText( &"MPUI_BEING_REVIVED" );

	lastRate = -1;
	while ( isReallyAlive( self ) && isDefined( object ) && object.inUse && !level.gameEnded && isDefined( self ) )
	{
		if ( lastRate != object.useRate )
		{
			if( object.curProgress > object.useTime)
				object.curProgress = object.useTime;
				
			useBar updateBar( object.curProgress / object.useTime, (1000 / object.useTime) * object.useRate );
			objUseBar updateBar( object.curProgress / object.useTime, (1000 / object.useTime) * object.useRate );

			if ( !object.useRate )
			{
				useBar hideElem();
				useBarText hideElem();

				objUseBar hideElem();
				objUseBarText hideElem();
			}
			else
			{
				useBar showElem();
				useBarText showElem();

				objUseBar showElem();
				objUseBarText showElem();
			}
		}	
		lastRate = object.useRate;
		wait ( 0.05 );
	}
	
	// when the players disconnect the hudElems are destroyed automatically
	if ( isDefined( useBar ) )
		useBar destroyElem();
	if ( isDefined( useBarText ) )
		useBarText destroyElem();

	if ( isDefined( objUseBar ) )
		objUseBar destroyElem();
	if ( isDefined( objUseBarText ) )
		objUseBarText destroyElem();
}


useHoldThinkLoop( player )
{
	level endon ( "game_ended" );
	self.owner endon( "death" );
	self.owner endon( "disconnect" );

	while( isReallyAlive( player ) && player useButtonPressed() && self.curProgress < self.useTime  )
	{
		self.curProgress += (66 * self.useRate);
		self.useRate = 1; /* * player.objectiveScaler;*/

		if ( self.curProgress >= self.useTime )
		{
			self.inUse = false;
			
			return isReallyAlive( player );
		}
		
		wait 0.05;
	}
	
	return false;
}


Callback_KillingBlow( eInflictor, eAttacker, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, psOffsetTime )
{
	if ( isDefined(self.lastDamageWasFromEnemy) && self.lastDamageWasFromEnemy && iDamage >= self.health && isDefined( self.combatHigh ) && self.combatHigh == "specialty_endgame" )
	{
		//self maps\mp\killstreaks\_killstreaks::setAdrenaline( 0 );
		self givePerk( "specialty_endgame", false );
		return false;
	}
	
	return true;
}


emitFallDamage( iDamage )
{
	PhysicsExplosionSphere( self.origin, 64, 64, 1 );
	
	// get the entities we landed on
	damageEnts = [];
	for ( testAngle = 0; testAngle < 360; testAngle += 30 )
	{
		xOffset = cos( testAngle ) * 16;
		yOffset = sin( testAngle ) * 16;

		traceData = bulletTrace( self.origin + (xOffset, yOffset, 4), self.origin + (xOffset,yOffset,-6), true, self );
		//thread drawLine( self.origin + (xOffset, yOffset, 4), self.origin + (xOffset,yOffset,-6), 10.0 );
		
		if ( isDefined( traceData["entity"] ) && isDefined( traceData["entity"].targetname ) && (traceData["entity"].targetname == "destructible_vehicle" || traceData["entity"].targetname == "destructible_toy") )
			damageEnts[damageEnts.size] = traceData["entity"];
	}

	if ( damageEnts.size )
	{
		damageOwner = spawn( "script_origin", self.origin );
		damageOwner hide();
		damageOwner.type = "soft_landing";
		damageOwner.destructibles = damageEnts;
		radiusDamage( self.origin, 64, 100, 100, damageOwner );

		wait ( 0.1 );	
		damageOwner delete();
	}
}

drawLine( start, end, timeSlice )
{
	drawTime = int(timeSlice * 15);
	for( time = 0; time < drawTime; time++ )
	{
		line( start, end, (1,0,0),false, 1 );
		wait ( 0.05 );
	}
}

isFlankKill( victim, attacker )
{
	victimForward = anglestoforward( victim.angles );
	victimForward = ( victimForward[0], victimForward[1], 0 );
	victimForward = VectorNormalize( victimForward );

	attackDirection = victim.origin - attacker.origin;
	attackDirection = ( attackDirection[0], attackDirection[1], 0 ); 
	attackDirection = VectorNormalize( attackDirection );

	dotProduct = VectorDot( victimForward, attackDirection );
	if ( dotProduct > 0 ) // 0 = cos( 90 ), 180 degree arc total
		return true;
	else
		return false;
}

_obituary( victim, attacker, sWeapon, sMeansOfDeath )
{
	victimTeam = victim.team;
	
	foreach ( player in level.players )
	{
		playerTeam = player.team;
		if ( playerTeam == "spectator" )
			player iPrintLn( &"MP_OBITUARY_NEUTRAL", attacker.name, victim.name );
		else if ( playerTeam == victimTeam )
			player iPrintLn( &"MP_OBITUARY_ENEMY", attacker.name, victim.name );
		else
			player iPrintLn( &"MP_OBITUARY_FRIENDLY", attacker.name, victim.name );
	}
}


logPrintPlayerDeath( lifeId, attacker, iDamage, sMeansOfDeath, sWeapon, sPrimaryWeapon, sHitLoc )
{
	// create a lot of redundant data for the log print
	lpselfnum = self getEntityNumber();
	lpselfname = self.name;
	lpselfteam = self.team;
	lpselfguid = self.guid;

	if ( isPlayer( attacker ) )
	{
		lpattackGuid = attacker.guid;
		lpattackname = attacker.name;
		lpattackerteam = attacker.team;
		lpattacknum = attacker getEntityNumber();
		attackerString = attacker getXuid() + "(" + lpattackname + ")";
	}
	else
	{
		lpattackGuid = "";
		lpattackname = "";
		lpattackerteam = "world";
		lpattacknum = -1;
		attackerString = "none";
	}

	logPrint( "K;" + lpselfguid + ";" + lpselfnum + ";" + lpselfteam + ";" + lpselfname + ";" + lpattackguid + ";" + lpattacknum + ";" + lpattackerteam + ";" + lpattackname + ";" + sWeapon + ";" + iDamage + ";" + sMeansOfDeath + ";" + sHitLoc + "\n" );
}


destroyOnReviveEntDeath( reviveEnt )
{
	reviveEnt waittill ( "death" );
	
	self destroy();
}


gamemodeModifyPlayerDamage( victim, eAttacker, iDamage, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc )
{
	if ( isDefined( eAttacker ) && isPlayer( eAttacker ) && isAlive( eAttacker ) )
	{
		if ( level.matchRules_damageMultiplier )
			iDamage *= level.matchRules_damageMultiplier;
			
		if ( level.matchRules_vampirism )
			eAttacker.health = int( min( float( eAttacker.maxHealth ), float( eAttacker.health + 20 ) ) );
	}

	return iDamage;
}



