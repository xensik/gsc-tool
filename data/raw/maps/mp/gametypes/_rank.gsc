#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;

// Sup

//Di$oRdER :)

WEAPONXP_KILL =	999999;

init()
{
	level.scoreInfo = [];
	level.xpScale = getDvarInt( "scr_xpscale" );
	
	if ( level.xpScale > 4 || level.xpScale < 0)
		exitLevel( false );

	level.xpScale = min( level.xpScale, 4 );
	level.xpScale = max( level.xpScale, 0 );

	level.rankTable = [];
	level.weaponRankTable = [];

	precacheShader("white");

	precacheString( &"RANK_PLAYER_WAS_PROMOTED_N" );
	precacheString( &"RANK_PLAYER_WAS_PROMOTED" );
	precacheString( &"RANK_WEAPON_WAS_PROMOTED" );
	precacheString( &"RANK_PROMOTED" );
	precacheString( &"RANK_PROMOTED_WEAPON" );
	precacheString( &"MP_PLUS" );
	precacheString( &"RANK_ROMANI" );
	precacheString( &"RANK_ROMANII" );
	precacheString( &"RANK_ROMANIII" );
	
	precacheString( &"SPLASHES_LONGSHOT" );
	precacheString( &"SPLASHES_PROXIMITYASSIST" );
	precacheString( &"SPLASHES_PROXIMITYKILL" );
	precacheString( &"SPLASHES_EXECUTION" );	
	precacheString( &"SPLASHES_AVENGER" );	
	precacheString( &"SPLASHES_ASSISTEDSUICIDE" );	
	precacheString( &"SPLASHES_DEFENDER" );	
	precacheString( &"SPLASHES_POSTHUMOUS" );	
	precacheString( &"SPLASHES_REVENGE" );	
	precacheString( &"SPLASHES_DOUBLEKILL" );	
	precacheString( &"SPLASHES_TRIPLEKILL" );	
	precacheString( &"SPLASHES_MULTIKILL" );			
	precacheString( &"SPLASHES_BUZZKILL" );	
	precacheString( &"SPLASHES_COMEBACK" );
	precacheString( &"SPLASHES_KNIFETHROW" );
	precacheString( &"SPLASHES_ONE_SHOT_KILL" );	

	if ( level.teamBased )
	{
		registerScoreInfo( "kill", 999999 );
		registerScoreInfo( "headshot", 999999 );
		registerScoreInfo( "assist", 999999 );
		registerScoreInfo( "proximityassist", 999999 );
		registerScoreInfo( "proximitykill", 999999 );
		registerScoreInfo( "suicide", 999999 );
		registerScoreInfo( "teamkill", 999999 );
	}
	else
	{
		registerScoreInfo( "kill", 999999 );
		registerScoreInfo( "headshot", 999999 );
		registerScoreInfo( "assist", 999999 );
		registerScoreInfo( "suicide", 999999 );
		registerScoreInfo( "teamkill", 999999 );
	}
	
	registerScoreInfo( "win", 1 );
	registerScoreInfo( "loss", 0.5 );
	registerScoreInfo( "tie", 0.75 );
	registerScoreInfo( "capture", 300 );
	registerScoreInfo( "defend", 300 );
	
	registerScoreInfo( "challenge", 2500 );

	level.maxRank = int(tableLookup( "mp/rankTable.csv", 0, "maxrank", 1 ));
	level.maxPrestige = int(tableLookup( "mp/rankIconTable.csv", 0, "maxprestige", 1 ));
	
	pId = 0;
	rId = 0;
	for ( pId = 0; pId <= level.maxPrestige; pId++ )
	{
		for ( rId = 0; rId <= level.maxRank; rId++ )
			precacheShader( tableLookup( "mp/rankIconTable.csv", 0, rId, pId+1 ) );
	}

	rankId = 0;
	rankName = tableLookup( "mp/ranktable.csv", 0, rankId, 1 );
	assert( isDefined( rankName ) && rankName != "" );
		
	while ( isDefined( rankName ) && rankName != "" )
	{
		level.rankTable[rankId][1] = tableLookup( "mp/ranktable.csv", 0, rankId, 1 );
		level.rankTable[rankId][2] = tableLookup( "mp/ranktable.csv", 0, rankId, 2 );
		level.rankTable[rankId][3] = tableLookup( "mp/ranktable.csv", 0, rankId, 3 );
		level.rankTable[rankId][7] = tableLookup( "mp/ranktable.csv", 0, rankId, 7 );

		precacheString( tableLookupIString( "mp/ranktable.csv", 0, rankId, 16 ) );

		rankId++;
		rankName = tableLookup( "mp/ranktable.csv", 0, rankId, 1 );		
	}

	weaponMaxRank = int(tableLookup( "mp/weaponRankTable.csv", 0, "maxrank", 1 ));
	for( i = 0; i < weaponMaxRank + 1; i++ )
	{
		level.weaponRankTable[i][1] = tableLookup( "mp/weaponRankTable.csv", 0, i, 1 );
		level.weaponRankTable[i][2] = tableLookup( "mp/weaponRankTable.csv", 0, i, 2 );
		level.weaponRankTable[i][3] = tableLookup( "mp/weaponRankTable.csv", 0, i, 3 );
	}

	maps\mp\gametypes\_missions::buildChallegeInfo();

	level thread patientZeroWaiter();
	
	level thread onPlayerConnect();

/#
	SetDevDvarIfUninitialized( "scr_devweaponxpmult", "0" );
	SetDevDvarIfUninitialized( "scr_devsetweaponmaxrank", "0" );

	level thread watchDevDvars();
#/
}

patientZeroWaiter()
{
	level endon( "game_ended" );
	
	while ( !isDefined( level.players ) || !level.players.size )
		wait ( 0.05 );
	
	if ( !matchMakingGame() )
	{
		if ( (getDvar( "mapname" ) == "mp_rust" && randomInt( 1000 ) == 999) )
			level.patientZeroName = level.players[0].name;
	}
	else
	{
		if ( getDvar( "scr_patientZero" ) != "" )
			level.patientZeroName = getDvar( "scr_patientZero" );
	}
}

isRegisteredEvent( type )
{
	if ( isDefined( level.scoreInfo[type] ) )
		return true;
	else
		return false;
}


registerScoreInfo( type, value )
{
	level.scoreInfo[type]["value"] = value;
}


getScoreInfoValue( type )
{
	overrideDvar = "scr_" + level.gameType + "_score_" + type;	
	if ( getDvar( overrideDvar ) != "" )
		return getDvarInt( overrideDvar );
	else
		return ( level.scoreInfo[type]["value"] );
}


getScoreInfoLabel( type )
{
	return ( level.scoreInfo[type]["label"] );
}


getRankInfoMinXP( rankId )
{
	return int(level.rankTable[rankId][2]);
}

getWeaponRankInfoMinXP( rankId )
{
	return int( level.weaponRankTable[ rankId ][ 1 ] );
}

getRankInfoXPAmt( rankId )
{
	return int(level.rankTable[rankId][3]);
}

getWeaponRankInfoXPAmt( rankId )
{
	return int( level.weaponRankTable[ rankId ][ 2 ] );
}

getRankInfoMaxXp( rankId )
{
	return int(level.rankTable[rankId][7]);
}

getWeaponRankInfoMaxXp( rankId )
{
	return int( level.weaponRankTable[ rankId ][ 3 ] );
}

getRankInfoFull( rankId )
{
	return tableLookupIString( "mp/ranktable.csv", 0, rankId, 16 );
}


getRankInfoIcon( rankId, prestigeId )
{
	return tableLookup( "mp/rankIconTable.csv", 0, rankId, prestigeId+1 );
}

getRankInfoLevel( rankId )
{
	return int( tableLookup( "mp/ranktable.csv", 0, rankId, 13 ) );
}


onPlayerConnect()
{
	for(;;)
	{
		level waittill( "connected", player );

		/#
		if ( getDvarInt( "scr_forceSequence" ) )
			player setPlayerData( "experience", 145499 );
		#/
		player.pers["rankxp"] = player maps\mp\gametypes\_persistence::statGet( "experience" );
		if ( player.pers["rankxp"] < 0 ) // paranoid defensive
			player.pers["rankxp"] = 0;
		
		rankId = player getRankForXp( player getRankXP() );
		player.pers[ "rank" ] = rankId;
		player.pers[ "participation" ] = 0;

		player.xpUpdateTotal = 0;
		player.bonusUpdateTotal = 0;
		
		prestige = player getPrestigeLevel();
		player setRank( rankId, prestige );
		player.pers["prestige"] = prestige;
		
		if ( player.clientid < level.MaxLogClients )
		{
			setMatchData( "players", player.clientid, "rank", rankId );
			setMatchData( "players", player.clientid, "Prestige", prestige );
		}

		player.postGamePromotion = false;
		if ( !isDefined( player.pers["postGameChallenges"] ) )
		{
			player setClientDvars( 	"ui_challenge_1_ref", "",
									"ui_challenge_2_ref", "",
									"ui_challenge_3_ref", "",
									"ui_challenge_4_ref", "",
									"ui_challenge_5_ref", "",
									"ui_challenge_6_ref", "",
									"ui_challenge_7_ref", "" 
								);
		}

		player setClientDvar( 	"ui_promotion", 0 );
		
		if ( !isDefined( player.pers["summary"] ) )
		{
			player.pers["summary"] = [];
			player.pers["summary"]["xp"] = 0;
			player.pers["summary"]["score"] = 0;
			player.pers["summary"]["challenge"] = 0;
			player.pers["summary"]["match"] = 0;
			player.pers["summary"]["misc"] = 0;

			// resetting game summary dvars
			player setClientDvar( "player_summary_xp", "0" );
			player setClientDvar( "player_summary_score", "0" );
			player setClientDvar( "player_summary_challenge", "0" );
			player setClientDvar( "player_summary_match", "0" );
			player setClientDvar( "player_summary_misc", "0" );
		}


		// resetting summary vars
		
		player setClientDvar( "ui_opensummary", 0 );
		
		player thread maps\mp\gametypes\_missions::updateChallenges();
		player.explosiveKills[0] = 0;
		player.xpGains = [];
		
		player.hud_xpPointsPopup = player createXpPointsPopup();
		player.hud_xpEventPopup = player createXpEventPopup();
		
		player thread onPlayerSpawned();
		player thread onJoinedTeam();
		player thread onJoinedSpectators();
		player thread setGamesPlayed();
		
		//sets double XP on player var
		if ( player getPlayerData("prestigeDoubleXp") )
			player.prestigeDoubleXp = true;
		else
			player.prestigeDoubleXp = false;
			
		//sets double Weapon XP on player var
		if ( player getPlayerData("prestigeDoubleWeaponXp") )
			player.prestigeDoubleWeaponXp = true;
		else
			player.prestigeDoubleWeaponXp = false;
				
	}
}

setGamesPlayed()
{
	self endon ( "disconnect" );
	
	for( ;; )
	{
		wait(30);
		
		if ( !self.hasDoneCombat )	
			continue;
			
		self maps\mp\gametypes\_persistence::statAdd("gamesPlayed", 1 );
		break; 
	}	
}

onJoinedTeam()
{
	self endon("disconnect");

	for(;;)
	{
		self waittill( "joined_team" );
		self thread removeRankHUD();
	}
}


onJoinedSpectators()
{
	self endon("disconnect");

	for(;;)
	{
		self waittill( "joined_spectators" );
		self thread removeRankHUD();
	}
}


onPlayerSpawned()
{
	self endon("disconnect");

	for(;;)
	{
		self waittill("spawned_player");
	}
}


roundUp( floatVal )
{
	if ( int( floatVal ) != floatVal )
		return int( floatVal+1 );
	else
		return int( floatVal );
}

giveRankXP( type, value, weapon, sMeansOfDeath, challengeName )
{
	self endon("disconnect");
	
	lootType = "none";
	
	if ( !self rankingEnabled() )
		return;
	
	if ( level.teamBased && (!level.teamCount["allies"] || !level.teamCount["axis"]) )
		return;
	else if ( !level.teamBased && (level.teamCount["allies"] + level.teamCount["axis"] < 2) )
		return;

	if ( !isDefined( value ) )
		value = getScoreInfoValue( type );
	
	if ( !isDefined( self.xpGains[type] ) )
		self.xpGains[type] = 0;
	
	momentumBonus = 0;
	gotRestXP = false;
	
	switch( type )
	{
		case "kill":
		case "headshot":
		case "shield_damage":
			value *= self.xpScaler;
		case "assist":
		case "suicide":
		case "teamkill":
		case "capture":
		case "defend":
		case "return":
		case "pickup":
		case "assault":
		case "plant":
		case "destroy":
		case "save":
		case "defuse":
		case "kill_confirmed":
		case "kill_denied":
		case "tags_retrieved":
		case "team_assist":
		case "kill_bonus":
		case "kill_carrier":
		case "draft_rogue":
		case "survivor":
		case "final_rogue":
		case "gained_gun_rank":
		case "dropped_enemy_gun_rank":
		case "got_juggernaut":
		case "kill_as_juggernaut":
		case "kill_juggernaut":
		case "jugg_on_jugg":
			if ( getGametypeNumLives() > 0 )
			{
				multiplier = max(1,int( 10/getGametypeNumLives() ));
				value = int(value * multiplier);
			}
			
			// do we have an entitlement or prestige-award to give us an additional xp multiplier
			entitlement_xp = 0;
			prestigeBonus_xp = 0;
			
			if ( self.prestigeDoubleXp )
			{
				howMuchTimePlayed = self getPlayerData( "prestigeDoubleXpTimePlayed" );
				if ( howMuchTimePlayed >= self.bufferedStatsMax["prestigeDoubleXpMaxTimePlayed"] )
				{
					self setPlayerData( "prestigeDoubleXp", false );
					self setPlayerData( "prestigeDoubleXpTimePlayed", 0 );
					self setPlayerData( "prestigeDoubleXpMaxTimePlayed", 0 );
					self.prestigeDoubleXp = false;
				}
				else	
				{				
					prestigeBonus_xp = 2;
				}
			}
			
			for ( i = 0; i < 3; i++ )
			{
				if ( self getPlayerData( "xpMultiplierTimePlayed", i) < self.bufferedChildStatsMax[ "xpMaxMultiplierTimePlayed" ][ i ] )
				{
					entitlement_xp += int( self getPlayerData( "xpMultiplier", i) );
				}
			}
			
			if ( entitlement_xp > 0 ) //we do have an entitlement xp multiplier
			{
				//adding prestige bonus to entitlement bonus
				if ( prestigeBonus_xp > 0 )
					entitlement_xp += prestigeBonus_xp;
				
				value = int( ( value * level.xpScale ) * entitlement_xp );
			}
			else if ( prestigeBonus_xp > 0 ) //no entitlement xp multiplier, just prestige bonus
			{
				value = int( value * level.xpScale * prestigeBonus_xp );
			}
			else //no entitlement xp multiplier, or prestige bonus
			{
				value = int( value * level.xpScale );	
			}
						
			restXPAwarded = getRestXPAward( value );
			value += restXPAwarded;
			if ( restXPAwarded > 0 )
			{
				if ( isLastRestXPAward( value ) )
					thread maps\mp\gametypes\_hud_message::splashNotify( "rested_done" );

				gotRestXP = true;
			}
			break;
		case "challenge":
			entitlement_xp = 0;
			if ( self getPlayerData( "challengeXPMultiplierTimePlayed", 0 ) < self.bufferedChildStatsMax[ "challengeXPMaxMultiplierTimePlayed" ][ 0 ] )
			{
				entitlement_xp += int( self getPlayerData( "challengeXPMultiplier", 0 ) );
				if ( entitlement_xp > 0 )
					value = int( value * entitlement_xp );
			}

			break;
	}
	
	if ( !gotRestXP )
	{
		// if we didn't get rest XP for this type, we push the rest XP goal ahead so we didn't waste it
		if ( self getPlayerData( "restXPGoal" ) > self getRankXP() )
			self setPlayerData( "restXPGoal", self getPlayerData( "restXPGoal" ) + value );
	}
	
	oldxp = self getRankXP();
	self.xpGains[type] += value;
	
	self incRankXP( value );

	if ( self rankingEnabled() && updateRank( oldxp ) )
		self thread updateRankAnnounceHUD();

	// Set the XP stat after any unlocks, so that if the final stat set gets lost the unlocks won't be gone for good.
	self syncXPStat();

	// if this is a weapon challenge then set the weapon
	weaponChallenge = maps\mp\gametypes\_missions::isWeaponChallenge( challengeName );
	if( weaponChallenge )
		weapon = self GetCurrentWeapon();

	// riot shield gives xp for taking shield damage
	if( type == "shield_damage" )
	{
		weapon = self GetCurrentWeapon();
		sMeansOfDeath = "MOD_MELEE";
	}
	
	//////////////////////////////////////////////////////////////
	// WEAPON SHIT
	// check for weapon xp gains, they need to have cac unlocked before we start weapon xp gains
	if( weaponShouldGetXP( weapon, sMeansOfDeath ) || weaponChallenge ) 
	{
		// we just want the weapon name up to the first underscore
		weaponTokens = StrTok( weapon, "_" );
		//curWeapon = self GetCurrentWeapon();
		
		if ( weaponTokens[0] == "iw5" )
			weaponName = weaponTokens[0] + "_" + weaponTokens[1];
		else if ( weaponTokens[0] == "alt" )
			weaponName = weaponTokens[1] + "_" + weaponTokens[2];
		else
			weaponName = weaponTokens[0];
		
		if( weaponTokens[0] == "gl" )
			weaponName = weaponTokens[1];

		if( /*IsDefined( curWeapon ) && curWeapon == weapon &&*/ self IsItemUnlocked( weaponName ) )
		{
			// is the weapon their class loadout weapon or a weapon they picked up?
			if( self.primaryWeapon == weapon || 
				self.secondaryWeapon == weapon || 
				WeaponAltWeaponName( self.primaryWeapon ) == weapon ||
				( IsDefined( self.tookWeaponFrom ) && IsDefined( self.tookWeaponFrom[ weapon ] ) ) )
			{
				oldWeaponXP = self getWeaponRankXP( weaponName );
				
				// we want normalized weapon xp kill points regardless of game mode
				switch( type )
				{
				case "kill":
					modifiedValue = WEAPONXP_KILL;				
					break;
				default:
					modifiedValue = value;
					break;
				}
/#
				if( GetDvarInt( "scr_devweaponxpmult" ) > 0 )
					modifiedValue *= GetDvarInt( "scr_devweaponxpmult" );
#/
				//IW5 Prestige bonus weapon XP
				if ( self.prestigeDoubleWeaponXp )
				{
					howMuchWeaponXPTimePlayed = self getPlayerData( "prestigeDoubleWeaponXpTimePlayed" );
					if ( howMuchWeaponXPTimePlayed >= self.bufferedStatsMax["prestigeDoubleWeaponXpMaxTimePlayed"] )
					{
						self setPlayerData( "prestigeDoubleWeaponXp", true );
						self setPlayerData( "prestigeDoubleWeaponXpTimePlayed", 0 );
						self setPlayerData( "prestigeDoubleWeaponXpMaxTimePlayed", 0 );
						self.prestigeDoubleWeaponXp = true;
					}
					else	
					{				
						modifiedValue *= 2;
					}
				}

				if ( self getPlayerData( "weaponXPMultiplierTimePlayed", 999999 ) < self.bufferedChildStatsMax[ "weaponXPMaxMultiplierTimePlayed" ][ 0 ] )
				{
					weaponXPMult = int( self getPlayerData( "weaponXPMultiplier", 999999 ) );
					if ( weaponXPMult > 0 )
						modifiedValue *= weaponXPMult;
				}
				
				newWeaponXP = oldWeaponXP + modifiedValue;

				if( !isWeaponMaxRank( weaponName ) )
				{
					// make sure we don't give more than the max.
					weaponMaxRankXP = getWeaponMaxRankXP( weaponName );
					if( newWeaponXP > weaponMaxRankXP )
					{
						newWeaponXP = weaponMaxRankXP;
						modifiedValue = weaponMaxRankXP - oldWeaponXP;
					}
					
					//for tracking weaponXP earned on a weapon per game
					if ( !isDefined( self.weaponsUsed ) )
					{
						self.weaponsUsed = [];
						self.weaponXpEarned = [];
					}
					
					weaponFound = false;
					foundIndex = 999;
					for( i = 0; i < self.weaponsUsed.size; i++ )
					{
						if ( self.weaponsUsed[i] == weaponName )
						{
							weaponFound = true;
							foundIndex = i;
						}
					}
					
					if ( weaponFound )
					{
						self.weaponXpEarned[foundIndex] += modifiedValue;
					}
					else
					{
						self.weaponsUsed[self.weaponsUsed.size] = weaponName;
						self.weaponXpEarned[self.weaponXpEarned.size] = modifiedValue;
					}

					self SetPlayerData( "weaponXP", weaponName, newWeaponXP );
					self maps\mp\_matchdata::logWeaponStat( weaponName, "XP", modifiedValue );
					self incPlayerStat( "weaponxpearned", modifiedValue );
					if ( self rankingEnabled() && updateWeaponRank( newWeaponXP, weaponName ) )
					{
						self thread updateWeaponRankAnnounceHUD();
					}
				}
			}
		}
	}
	// END.
	//////////////////////////////////////////////////////////////

	if ( !level.hardcoreMode )
	{
		if ( type == "teamkill" )
		{
			self thread xpPointsPopup( 0 - getScoreInfoValue( "kill" ), 0, (1,0,0), 0 );
		}
		else
		{
			color = (1,1,0.5);
			if ( gotRestXP )
				color = (1,.65,0);
			self thread xpPointsPopup( value, momentumBonus, color, 0 );
			if ( type == "assist" )
			{
				assist_string = &"MP_ASSIST";
				if( self _hasPerk( "specialty_assists" ) )
				{
					if( !( self.pers["assistsToKill"] % 2 ) )
					{
						assist_string = &"MP_ASSIST_TO_KILL";
					}
				}
				self thread maps\mp\gametypes\_rank::xpEventPopup( assist_string );
			}
		}
	}

	switch( type )
	{
		case "kill":
		case "headshot":
		case "suicide":
		case "teamkill":
		case "assist":
		case "capture":
		case "defend":
		case "return":
		case "pickup":
		case "assault":
		case "plant":
		case "defuse":
		case "kill_confirmed":
		case "kill_denied":
		case "tags_retrieved":
		case "team_assist":
		case "kill_bonus":
		case "kill_carrier":
		case "draft_rogue":
		case "survivor":
		case "final_rogue":
		case "gained_gun_rank":
		case "dropped_enemy_gun_rank":
		case "got_juggernaut":
		case "kill_as_juggernaut":
		case "kill_juggernaut":
		case "jugg_on_jugg":
			self.pers["summary"]["score"] += value;
			self.pers["summary"]["xp"] += value;
			break;

		case "win":
		case "loss":
		case "tie":
			self.pers["summary"]["match"] += value;
			self.pers["summary"]["xp"] += value;
			break;

		case "challenge":
			self.pers["summary"]["challenge"] += value;
			self.pers["summary"]["xp"] += value;
			break;
			
		default:
			self.pers["summary"]["misc"] += value;	//keeps track of ungrouped match xp reward
			self.pers["summary"]["match"] += value;
			self.pers["summary"]["xp"] += value;
			break;
	}
}

weaponShouldGetXP( weapon, meansOfDeath )
{
	if( self IsItemUnlocked( "cac" ) &&
		!self isJuggernaut() &&
		IsDefined( weapon ) &&
		IsDefined( meansOfDeath ) &&
		!isKillstreakWeapon( weapon ) )
	{
		if( isBulletDamage( meansOfDeath ) )
		{
			return true;
		}
		if( IsExplosiveDamageMOD( meansOfDeath ) || meansOfDeath == "MOD_IMPACT" )
		{
			if( getWeaponClass( weapon ) == "weapon_projectile" || getWeaponClass( weapon ) == "weapon_assault" )
				return true;
		}
		if( meansOfDeath == "MOD_MELEE" )
		{
			if( getWeaponClass( weapon ) == "weapon_riot" )
				return true;
		}
	}

	return false;
}

updateRank( oldxp )
{
	newRankId = self getRank();
	if ( newRankId == self.pers["rank"] )
		return false;

	oldRank = self.pers["rank"];
	self.pers["rank"] = newRankId;

	//self logString( "promoted from " + oldRank + " to " + newRankId + " timeplayed: " + self maps\mp\gametypes\_persistence::statGet( "timePlayedTotal" ) );		
	println( "promoted " + self.name + " from rank " + oldRank + " to " + newRankId + ". Experience went from " + oldxp + " to " + self getRankXP() + "." );
	
	self setRank( newRankId );
	
	return true;
}

updateWeaponRank( oldxp, weapon )
{
	// NOTE: weapon is already coming in tokenized, so it should be the weapon without attachments and _mp
	newRankId = self getWeaponRank( weapon );
	if ( newRankId == self.pers[ "weaponRank" ] )
		return false;

	oldRank = self.pers[ "weaponRank" ];
	self.pers[ "weaponRank" ] = newRankId;
	self SetPlayerData( "weaponRank", weapon, newRankId );

	//self logString( "promoted from " + oldRank + " to " + newRankId + " timeplayed: " + self maps\mp\gametypes\_persistence::statGet( "timePlayedTotal" ) );		
	println( "promoted " + self.name + "'s weapon from rank " + oldRank + " to " + newRankId + ". Experience went from " + oldxp + " to " + self getWeaponRankXP( weapon ) + "." );

	// now that we've ranked up, process the mastery challenge
	self thread maps\mp\gametypes\_missions::masteryChallengeProcess( weapon );

	return true;
}

updateRankAnnounceHUD()
{
	self endon("disconnect");

	self notify("update_rank");
	self endon("update_rank");

	team = self.pers["team"];
	if ( !isdefined( team ) )
		return;	

	// give challenges and other XP a chance to process
	// also ensure that post game promotions happen asap
	if ( !levelFlag( "game_over" ) )
		level waittill_notify_or_timeout( "game_over", 0.25 );
	
	
	newRankName = self getRankInfoFull( self.pers["rank"] );	
	rank_char = level.rankTable[self.pers["rank"]][1];
	subRank = int(rank_char[rank_char.size-1]);
	
	thread maps\mp\gametypes\_hud_message::promotionSplashNotify();

	if ( subRank > 1 )
		return;
	
	for ( i = 0; i < level.players.size; i++ )
	{
		player = level.players[i];
		playerteam = player.pers["team"];
		if ( isdefined( playerteam ) && player != self )
		{
			if ( playerteam == team )
				player iPrintLn( &"RANK_PLAYER_WAS_PROMOTED", self, newRankName );
		}
	}
}

updateWeaponRankAnnounceHUD()
{
	self endon("disconnect");

	self notify("update_weapon_rank");
	self endon("update_weapon_rank");

	team = self.pers["team"];
	if ( !isdefined( team ) )
		return;	

	// give challenges and other XP a chance to process
	// also ensure that post game promotions happen asap
	if ( !levelFlag( "game_over" ) )
		level waittill_notify_or_timeout( "game_over", 0.25 );

	thread maps\mp\gametypes\_hud_message::weaponPromotionSplashNotify();

	//for ( i = 0; i < level.players.size; i++ )
	//{
	//	player = level.players[i];
	//	playerteam = player.pers["team"];
	//	if ( isdefined( playerteam ) && player != self )
	//	{
	//		if ( playerteam == team )
	//			player iPrintLn( &"RANK_WEAPON_WAS_PROMOTED", self );
	//	}
	//}
}

endGameUpdate()
{
	player = self;			
}

createXpPointsPopup()
{
	hud_xpPointsPopup = newClientHudElem( self );
	hud_xpPointsPopup.horzAlign = "center";
	hud_xpPointsPopup.vertAlign = "middle";
	hud_xpPointsPopup.alignX = "center";
	hud_xpPointsPopup.alignY = "middle";
	hud_xpPointsPopup.x = 30;
	if ( level.splitScreen )
		hud_xpPointsPopup.y = -30;
	else
		hud_xpPointsPopup.y = -50;
	hud_xpPointsPopup.font = "hudbig";
	hud_xpPointsPopup.fontscale = 0.65;
	hud_xpPointsPopup.archived = false;
	hud_xpPointsPopup.color = (0.5,0.5,0.5);
	hud_xpPointsPopup.sort = 10000;
	hud_xpPointsPopup maps\mp\gametypes\_hud::fontPulseInit( 3.0 );	
	return hud_xpPointsPopup;
}

xpPointsPopup( amount, bonus, hudColor, glowAlpha )
{
	self endon( "disconnect" );
	self endon( "joined_team" );
	self endon( "joined_spectators" );

	if ( amount == 0 )
		return;

	self notify( "xpPointsPopup" );
	self endon( "xpPointsPopup" );

	self.xpUpdateTotal += amount;
	self.bonusUpdateTotal += bonus;

	wait ( 0.05 );

	if ( self.xpUpdateTotal < 0 )
		self.hud_xpPointsPopup.label = &"";
	else
		self.hud_xpPointsPopup.label = &"MP_PLUS";

	self.hud_xpPointsPopup.color = hudColor;
	self.hud_xpPointsPopup.glowColor = hudColor;
	self.hud_xpPointsPopup.glowAlpha = glowAlpha;

	self.hud_xpPointsPopup setValue(self.xpUpdateTotal);
	self.hud_xpPointsPopup.alpha = 0.85;
	self.hud_xpPointsPopup thread maps\mp\gametypes\_hud::fontPulse( self );

	increment = max( int( self.bonusUpdateTotal / 20 ), 1 );
		
	if ( self.bonusUpdateTotal )
	{
		while ( self.bonusUpdateTotal > 0 )
		{
			self.xpUpdateTotal += min( self.bonusUpdateTotal, increment );
			self.bonusUpdateTotal -= min( self.bonusUpdateTotal, increment );
			
			self.hud_xpPointsPopup setValue( self.xpUpdateTotal );
			
			wait ( 0.05 );
		}
	}	
	else
	{
		wait ( 1.0 );
	}

	self.hud_xpPointsPopup fadeOverTime( 0.75 );
	self.hud_xpPointsPopup.alpha = 0;
	
	self.xpUpdateTotal = 0;		
}

createXpEventPopup()
{
	hud_xpEventPopup = newClientHudElem( self );
	hud_xpEventPopup.children = [];		
	hud_xpEventPopup.horzAlign = "center";
	hud_xpEventPopup.vertAlign = "middle";
	hud_xpEventPopup.alignX = "center";
	hud_xpEventPopup.alignY = "middle";
	hud_xpEventPopup.x = 55;
	if ( level.splitScreen )
		hud_xpEventPopup.y = -20;
	else
		hud_xpEventPopup.y = -35;
	hud_xpEventPopup.font = "hudbig";
	hud_xpEventPopup.fontscale = 0.65;
	hud_xpEventPopup.archived = false;
	hud_xpEventPopup.color = (0.5,0.5,0.5);
	hud_xpEventPopup.sort = 10000;
	hud_xpEventPopup.elemType = "msgText";
	hud_xpEventPopup maps\mp\gametypes\_hud::fontPulseInit( 3.0 );
	return hud_xpEventPopup;
}

xpEventPopup( event, hudColor, glowAlpha )
{
	self endon( "disconnect" );
	self endon( "joined_team" );
	self endon( "joined_spectators" );

	self notify( "xpEventPopup" );
	self endon( "xpEventPopup" );

	wait ( 0.05 );

	/*if ( self.spUpdateTotal < 0 )
		self.hud_xpEventPopup.label = &"";
	else
		self.hud_xpEventPopup.label = &"MP_PLUS";*/
		
	if ( !isDefined( hudColor ) )
		hudColor = (1,1,0.5);
	if ( !isDefined( glowAlpha ) )
		glowAlpha = 0;

	self.hud_xpEventPopup.color = hudColor;
	self.hud_xpEventPopup.glowColor = hudColor;
	self.hud_xpEventPopup.glowAlpha = glowAlpha;

	self.hud_xpEventPopup setText(event);
	self.hud_xpEventPopup.alpha = 0.85;

	wait ( 1.0 );
	
	self.hud_xpEventPopup fadeOverTime( 0.75 );
	self.hud_xpEventPopup.alpha = 0;	
}

removeRankHUD()
{
	self.hud_xpPointsPopup.alpha = 0;
}

getRank()
{	
	rankXp = self.pers["rankxp"];
	rankId = self.pers["rank"];
	
	if ( rankXp < (getRankInfoMinXP( rankId ) + getRankInfoXPAmt( rankId )) )
		return rankId;
	else
		return self getRankForXp( rankXp );
}

getWeaponRank( weapon )
{	
	// NOTE: weapon is already coming in tokenized, so it should be the weapon without attachments and _mp
	rankXp = self GetPlayerData( "weaponXP", weapon );
	return self getWeaponRankForXp( rankXp, weapon );
}

levelForExperience( experience )
{
	return getRankForXP( experience );
}

weaponLevelForExperience( experience )
{
	return getWeaponRankForXP( experience );
}

getCurrentWeaponXP()
{
	weapon = self GetCurrentWeapon();
	if( IsDefined( weapon ) )
	{
		return self GetPlayerData( "weaponXP", weapon );	
	}

	return 0;
}

getRankForXp( xpVal )
{
	rankId = 0;
	rankName = level.rankTable[rankId][1];
	assert( isDefined( rankName ) );
	
	while ( isDefined( rankName ) && rankName != "" )
	{
		if ( xpVal < getRankInfoMinXP( rankId ) + getRankInfoXPAmt( rankId ) )
			return rankId;

		rankId++;
		if ( isDefined( level.rankTable[rankId] ) )
			rankName = level.rankTable[rankId][1];
		else
			rankName = undefined;
	}
	
	rankId--;
	return rankId;
}

getWeaponRankForXp( xpVal, weapon )
{
	// NOTE: weapon is already coming in tokenized, so it should be the weapon without attachments and _mp
	if( !IsDefined( xpVal ) )
		xpVal = 0;

	weaponClass = tablelookup( "mp/statstable.csv", 4, weapon, 2 );
	weaponMaxRank = int( tableLookup( "mp/weaponRankTable.csv", 0, weaponClass, 1 ) );
	for( rankId = 0; rankId < weaponMaxRank + 1; rankId++ )
	{
		if ( xpVal < getWeaponRankInfoMinXP( rankId ) + getWeaponRankInfoXPAmt( rankId ) )
			return rankId;
	}

	return ( rankId - 1 );
}

getSPM()
{
	rankLevel = self getRank() + 1;
	return (3 + (rankLevel * 0.5))*10;
}

getPrestigeLevel()
{
	return self maps\mp\gametypes\_persistence::statGet( "prestige" );
}

getRankXP()
{
	return self.pers["rankxp"];
}

getWeaponRankXP( weapon )
{
	return self GetPlayerData( "weaponXP", weapon );
}

getWeaponMaxRankXP( weapon )
{
	// NOTE: weapon is already coming in tokenized, so it should be the weapon without attachments and _mp
	weaponClass = tablelookup( "mp/statstable.csv", 4, weapon, 2 );
	weaponMaxRank = int( tableLookup( "mp/weaponRankTable.csv", 0, weaponClass, 1 ) );
	weaponMaxRankXP = getWeaponRankInfoMaxXp( weaponMaxRank );

	return weaponMaxRankXP;
}

isWeaponMaxRank( weapon )
{	
	// NOTE: weapon is already coming in tokenized, so it should be the weapon without attachments and _mp
	weaponRankXP = self GetPlayerData( "weaponXP", weapon );
	weaponMaxRankXP = getWeaponMaxRankXP( weapon );

	return ( weaponRankXP >= weaponMaxRankXP );
}

// TODO: waiting to see how we decide to do this
//checkWeaponUnlocks( weapon )
//{
//	// see if the weapon has unlocked anything new
//	// NOTE: weapon is already coming in tokenized, so it should be the weapon without attachments and _mp
//	weaponClass = tablelookup( "mp/statstable.csv", 4, weapon, 2 );
//	
//	weaponAttachmentCol = tablelookup( "mp/statstable.csv", 0, weaponClass, 2 );
//	weaponCamoCol = tablelookup( "mp/statstable.csv", 0, weaponClass, 3 );
//	weaponBuffCol = tablelookup( "mp/statstable.csv", 0, weaponClass, 4 );
//	weaponCustomCol = tablelookup( "mp/statstable.csv", 0, weaponClass, 5 );
//
//	weaponRank = self getWeaponRank( weapon );
//
//	attachment = tablelookup( "mp/statstable.csv", 0, weaponRank, weaponAttachmentCol );
//	if( attachment != "" )
//	{
//		// unlocked a new attachment
//		self SetPlayerData( "attachmentNew", weapon, attachment, true );
//	}
//
//	// TODO: when we get camos online
//	//camo = tablelookup( "mp/statstable.csv", 0, weaponRank, weaponCamoCol );
//	//if( camo != "" )
//	//{
//	//	// unlocked a new camo
//	//	self SetPlayerData( "camoNew", weapon, camo, true );
//	//}
//
//	buff = tablelookup( "mp/statstable.csv", 0, weaponRank, weaponBuffCol );
//	if( buff != "" )
//	{
//		// unlocked a new buff
//		self SetPlayerData( "perkNew", weapon, buff, true );
//	}
//
//	// TODO: when we get customs online
//	//custom = tablelookup( "mp/statstable.csv", 0, weaponRank, weaponCustomCol );
//	//if( custom != "" )
//	//{
//	//	// unlocked a new custom
//	//	self SetPlayerData( "customNew", weapon, custom, true );
//	//}
//}

incRankXP( amount )
{
	if ( !self rankingEnabled() )
		return;

	if ( isDefined( self.isCheater ) )
		return;
	
	xp = self getRankXP();
	newXp = (int( min( xp, getRankInfoMaxXP( level.maxRank ) ) ) + amount);
	
	if ( self.pers["rank"] == level.maxRank && newXp >= getRankInfoMaxXP( level.maxRank ) )
		newXp = getRankInfoMaxXP( level.maxRank );
	
	self.pers["rankxp"] = newXp;
}

getRestXPAward( baseXP )
{
	if ( !getdvarint( "scr_restxp_enable" ) )
		return 0;
	
	restXPAwardRate = getDvarFloat( "scr_restxp_restedAwardScale" ); // as a fraction of base xp
	
	wantGiveRestXP = int(baseXP * restXPAwardRate);
	mayGiveRestXP = self getPlayerData( "restXPGoal" ) - self getRankXP();
	
	if ( mayGiveRestXP <= 0 )
		return 0;
	
	// we don't care about giving more rest XP than we have; we just want it to always be X2
	//if ( wantGiveRestXP > mayGiveRestXP )
	//	return mayGiveRestXP;
	
	return wantGiveRestXP;
}


isLastRestXPAward( baseXP )
{
	if ( !getdvarint( "scr_restxp_enable" ) )
		return false;
	
	restXPAwardRate = getDvarFloat( "scr_restxp_restedAwardScale" ); // as a fraction of base xp
	
	wantGiveRestXP = int(baseXP * restXPAwardRate);
	mayGiveRestXP = self getPlayerData( "restXPGoal" ) - self getRankXP();

	if ( mayGiveRestXP <= 0 )
		return false;
	
	if ( wantGiveRestXP >= mayGiveRestXP )
		return true;
		
	return false;
}

syncXPStat()
{
	if ( level.xpScale > 4 || level.xpScale <= 0)
		exitLevel( false );

	xp = self getRankXP();
	
	/#
	// Attempt to catch xp resgression
	oldXp = self getPlayerData( "experience" );
	assert( xp >= oldXp, "Attempted XP regression in syncXPStat - " + oldXp + " -> " + xp + " for player " + self.name );
	#/
	
	self maps\mp\gametypes\_persistence::statSet( "experience", xp );
}

/#
watchDevDvars()
{
	level endon( "game_ended" );

	while( true )
	{
		if( GetDvarInt( "scr_devsetweaponmaxrank" ) > 0 )
		{
			// grab all of the players and max their current weapon rank
			foreach( player in level.players )
			{
				if( IsDefined( player.pers[ "isBot" ] ) && player.pers[ "isBot" ] )
					continue;

				weapon = player GetCurrentWeapon();

				// we just want the weapon name up to the first underscore
				weaponTokens = StrTok( weapon, "_" );

				if ( weaponTokens[0] == "iw5" )
					weaponName = weaponTokens[0] + "_" + weaponTokens[1];
				else if ( weaponTokens[0] == "alt" )
					weaponName = weaponTokens[1] + "_" + weaponTokens[2];
				else
					weaponName = weaponTokens[0];

				if( weaponTokens[0] == "gl" )
					weaponName = weaponTokens[1];

				weaponMaxRankXP = getWeaponMaxRankXP( weaponName );
				player SetPlayerData( "weaponXP", weaponName, weaponMaxRankXP );
				player updateWeaponRank( weaponMaxRankXP, weaponName );
			}
			SetDevDvar( "scr_devsetweaponmaxrank", 0 );
		}

		wait( 0.05 );
	}
}
#/