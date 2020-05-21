#include maps\mp\gametypes\_hud_util;
#include maps\mp\_utility;
#include common_scripts\utility;
#include maps\mp\_wii_utility;

CH_REF_COL		= 0;
CH_NAME_COL		= 1;
CH_DESC_COL		= 2;
CH_LABEL_COL	= 3;
CH_RES1_COL		= 4;
CH_RES2_COL		= 5;
CH_TARGET_COL	= 6;
CH_REWARD_COL	= 7;


TIER_FILE_COL	= 4;

CH_REGULAR		= 0;
CH_DAILY			= 1;
CH_WEEKLY			= 2;

UNLOCK_TABLE_REF = "mp/unlockTable.csv";
CHALLENGE_TABLE_REF = "mp/challengeTable.csv";
ALL_CHALLENGES_TABLE_REF = "mp/allChallengesTable.csv";
DAILY_CHALLENGES_TABLE_REF = "mp/dailychallengesTable.csv";
WEEKLY_CHALLENGES_TABLE_REF = "mp/weeklychallengesTable.csv";

init()
{
	precacheString(&"MP_CHALLENGE_COMPLETED");

	if ( !mayProcessChallenges() )
		return;
	
	level.missionCallbacks = [];

	registerMissionCallback( "playerKilled", ::ch_kills );	
	registerMissionCallback( "playerKilled", ::ch_vehicle_kills );
	registerMissionCallback( "playerHardpoint", ::ch_hardpoints );
	registerMissionCallback( "playerAssist", ::ch_assists );	
	registerMissionCallback( "roundEnd", ::ch_roundwin );
	registerMissionCallback( "roundEnd", ::ch_roundplayed );
	registerMissionCallback( "vehicleKilled", ::ch_vehicle_killed );
	
	level thread createPerkMap();
		
	level thread onPlayerConnect();
}

createPerkMap()
{
	level.perkMap = [];
	
	level.perkMap["specialty_bulletdamage"] = "specialty_stoppingpower";
	level.perkMap["specialty_quieter"] = "specialty_deadsilence";
	level.perkMap["specialty_localjammer"] = "specialty_scrambler";
	level.perkMap["specialty_fastreload"] = "specialty_sleightofhand";
	level.perkMap["specialty_pistoldeath"] = "specialty_laststand";
}


mayProcessChallenges()
{
	/#
	if ( getDvarInt( "debug_challenges" ) )
		return true;
	#/
	
	return ( level.rankedMatch );
}

onPlayerConnect()
{
	for(;;)
	{
		level waittill( "connected", player );

		if ( !isDefined( player.pers["postGameChallenges"] ) )
			player.pers["postGameChallenges"] = 0;

		player thread onPlayerSpawned();
		player thread initMissionData();
		player thread monitorBombUse();
		player thread monitorFallDistance();
		player thread monitorLiveTime();	
		player thread monitorStreaks();
		player thread monitorStreakReward();
		player thread monitorScavengerPickup();
		player thread monitorBlastShieldSurvival();
		player thread monitorTacInsertionsDestroyed();
		player thread monitorProcessChallenge();
		player thread monitorKillstreakProgress();
		player thread monitorFinalStandSurvival();
		//player thread monitorCombatHighSurvival();
		//player thread monitorKilledKillstreak();
		player thread monitorADSTime();
		player thread monitorWeaponSwap();
		player thread monitorFlashbang();
		player thread monitorConcussion();
		player thread monitorMineTriggering();
		
		if ( using_wii() )
		{
			player wii_NotifyOnPlayerCommand_persistent( "hold_breath", "+smoke", "+sprint_and_cameralock", "+activate" );
			player wii_NotifyOnPlayerCommand_persistent( "release_breath", "-smoke", "-sprint_and_cameralock", "-activate" );
		}
		else
		{
			player NotifyOnPlayerCommand( "hold_breath", "+breath_sprint" );
			player NotifyOnPlayerCommand( "release_breath", "-breath_sprint" );
		}
		player thread monitorHoldBreath();
		
		if( using_wii() )
		{
			player wii_NotifyOnPlayerCommand_persistent( "jumped", "+sprint_or_jump", "+sprint_and_cameralock", "+zappermenu" );
		}
				
		player NotifyOnPlayerCommand( "jumped", "+goStand" );
		player thread monitorMantle();

		/*if ( isDefined( level.patientZeroName ) && isSubStr( player.name, level.patientZeroName ) )
		{
			player setPlayerData( "challengeState", "ch_infected", 2 );
			player setPlayerData( "challengeProgress", "ch_infected", 1 );
			player setPlayerData( "challengeState", "ch_plague", 2 );
			player setPlayerData( "challengeProgress", "ch_plague", 1 );
		}*/	
		
		player setPlayerData( "round", "weaponsUsed", 0, "none" );
		player setPlayerData( "round", "weaponsUsed", 1, "none" );
		player setPlayerData( "round", "weaponsUsed", 2, "none" );
		player setPlayerData( "round", "weaponXpEarned", 0, 0 );
		player setPlayerData( "round", "weaponXpEarned", 1, 0 );
		player setPlayerData( "round", "weaponXpEarned", 2, 0 );

		cardTitleIndex = player getPlayerData( "cardTitle" );
		cardTitle = tableLookupByRow( "mp/cardTitleTable_strm.csv", cardTitleIndex, 0 );

		if ( cardTitle == "cardtitle_infected" )
			player.infected = true;
		else if ( cardTitle == "cardtitle_plague" )
			player.plague = true;
	}
}

// TODO: When possible move above onPlayerConnect threads here
onPlayerSpawned()
{
	self endon( "disconnect" );
	for(;;)
	{
		self waittill( "spawned_player" );

		self thread monitorSprintDistance();
	}
}

monitorScavengerPickup()
{
	self endon ( "disconnect" );

	for( ;; )
	{
		self waittill( "scavenger_pickup" ); 
		
		if ( self IsItemUnlocked( "specialty_scavenger" ) && self _hasPerk( "specialty_scavenger" ) )
			self processChallenge( "ch_scavenger_pro" );
		
		wait( 0.05 );
	}	
}


monitorStreakReward()
{
	self endon ( "disconnect" );

	for( ;; )
	{
		self waittill( "received_earned_killstreak" ); 
		
		if ( self IsItemUnlocked( "specialty_hardline" ) && self _hasPerk( "specialty_hardline" ) )
			self processChallenge( "ch_hardline_pro" );
		
		wait( 0.05 );
	}	
}

monitorBlastShieldSurvival()
{
	self endon ( "disconnect" );

	for( ;; )
	{
		self waittill( "survived_explosion", attacker ); 
		
		// don't let the player boost themselves
		if( IsDefined( attacker ) && IsPlayer( attacker ) && self == attacker )
			continue;

		if ( self IsItemUnlocked( "_specialty_blastshield" ) && self _hasPerk( "_specialty_blastshield" ) )
			self processChallenge( "ch_blastshield_pro" );
		
		waitframe();
	}	
}

monitorTacInsertionsDestroyed()
{
	self endon ( "disconnect" );
	
	for(;;)
	{
		self waittill( "destroyed_insertion", owner );
		
		if ( self == owner )
			return;
		
		self processChallenge( "ch_darkbringer" );
		self incPlayerStat( "mosttacprevented", 1 );
	
		self thread maps\mp\gametypes\_hud_message::SplashNotify( "denied", 20 );
		owner maps\mp\gametypes\_hud_message::playerCardSplashNotify( "destroyed_insertion", self );

		waitframe();
	}
}

monitorFinalStandSurvival()
{
	self endon ( "disconnect" );
	
	for(;;)
	{
		self waittill( "revive" );
		
		self processChallenge( "ch_livingdead" );

		waitframe();
	}
}

//monitorCombatHighSurvival()
//{
//	self endon ( "disconnect" );
//
//	for(;;)
//	{
//		self waittill( "combathigh_survived" );
//		
//		self processChallenge( "ch_thenumb" );
//
//		waitframe();
//	}
//}

// round based tracking
initMissionData()
{
	keys = getArrayKeys( level.killstreakFuncs );	
	foreach ( key in keys )
		self.pers[key] = 0;
	
	self.pers["lastBulletKillTime"] = 0;
	self.pers["bulletStreak"] = 0;
	self.explosiveInfo = [];
}

registerMissionCallback(callback, func)
{
	if (!isdefined(level.missionCallbacks[callback]))
		level.missionCallbacks[callback] = [];
	level.missionCallbacks[callback][level.missionCallbacks[callback].size] = func;
}


getChallengeStatus( name )
{
	assertEx( isDefined(self.challengeData), "Player: " + self.name + " doesnt have challenge data." );
	
	if ( isDefined( self.challengeData[name] ) )
		return self.challengeData[name];
	else
		return 0;
}


ch_assists( data )
{
	player = data.player;
	player processChallenge( "ch_assists" );
}


ch_hardpoints( data )
{
	player = data.player;
	player.pers[data.hardpointType]++;

	switch ( data.hardpointType )
	{
	// Assault Killstreaks
	case "uav":
		player processChallenge( "ch_uav" );
		player processChallenge( "ch_assault_streaks" );
		if ( player.pers["uav"] >= 3 )
			player processChallenge( "ch_nosecrets" );
		break;
	case "airdrop_assault":
		player processChallenge( "ch_airdrop_assault" );
		player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["airdrop_assault"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	//*case "predator_missile":
	//*	player processChallenge( "ch_predator_missile" );
	//*	player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["predator_missile"] >= 2 )
		//	player processChallenge( "ch_???" );
	//*	break;
	case "ims":
		player processChallenge( "ch_ims" );
		player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["ims"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	case "airdrop_sentry_minigun":
		player processChallenge( "ch_airdrop_sentry_minigun" );
		player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["airdrop_sentry_minigun"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	case "precision_airstrike":
		player processChallenge( "ch_precision_airstrike" );
		player processChallenge( "ch_assault_streaks" );
		if ( player.pers["precision_airstrike"] >= 2 )
			player processChallenge( "ch_afterburner" );
		break;
	case "helicopter":
		player processChallenge( "ch_helicopter" );
		player processChallenge( "ch_assault_streaks" );
		if ( player.pers["helicopter"] >= 2 )
			player processChallenge( "ch_airsuperiority" );
		break;
	case "littlebird_flock":
		player processChallenge( "ch_littlebird_flock" );
		player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["littlebird_flock"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	case "littlebird_support":
		player processChallenge( "ch_littlebird_support" );
		player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["littlebird_support"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	//*case "remote_mortar":
	//*	player processChallenge( "ch_remote_mortar" );
	//*	player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["remote_mortar"] >= 2 )
		//	player processChallenge( "ch_???" );
	//*	break;
	case "airdrop_remote_tank":
		player processChallenge( "ch_airdrop_remote_tank" );
		player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["airdrop_remote_tank"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	case "helicopter_flares":
		player processChallenge( "ch_helicopter_flares" );
		player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["helicopter_flares"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	//*case "ac130":
	//*	player processChallenge( "ch_ac130" );
	//*	player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["ac130"] >= 2 )
		//	player processChallenge( "ch_???" );
	//*	break;
	case "airdrop_juggernaut":
		player processChallenge( "ch_airdrop_juggernaut" );
		player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["airdrop_juggernaut"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	//*case "osprey_gunner":
	//*	player processChallenge( "ch_osprey_gunner" );
	//*	player processChallenge( "ch_assault_streaks" );
		//if ( player.pers["osprey_gunner"] >= 2 )
		//	player processChallenge( "ch_???" );
	//*	break;
	// End Assault Killstreaks



	// Support Killstreaks
	case "uav_support":
		player processChallenge( "ch_uav_support" );
		player processChallenge( "ch_support_streaks" );
		if ( player.pers["uav"] >= 3 )
			player processChallenge( "ch_nosecrets" );
		break;
	case "counter_uav":
		player processChallenge( "ch_counter_uav" );
		player processChallenge( "ch_support_streaks" );
		if ( player.pers["counter_uav"] >= 3 )
			player processChallenge( "ch_sunblock" );
		break;
	case "deployable_vest":
		player processChallenge( "ch_deployable_vest" );
		player processChallenge( "ch_support_streaks" );
		//if ( player.pers["deployable_vest"] >= 3 )
		//	player processChallenge( "ch_???" );
		break;
	case "airdrop_trap":
		player processChallenge( "ch_airdrop_trap" );
		player processChallenge( "ch_support_streaks" );
		//if ( player.pers["airdrop_trap"] >= 3 )
		//	player processChallenge( "ch_???" );
		break;
	case "sam_turret":
		player processChallenge( "ch_sam_turret" );
		player processChallenge( "ch_support_streaks" );
		//if ( player.pers["sam_turret"] >= 3 )
		//	player processChallenge( "ch_???" );
		break;
	//*case "remote_uav":
		//*player processChallenge( "ch_remote_uav" );
		//*player processChallenge( "ch_support_streaks" );
		//if ( player.pers["remote_uav"] >= 3 )
		//	player processChallenge( "ch_???" );
	//*	break;
	case "triple_uav":
		player processChallenge( "ch_triple_uav" );
		player processChallenge( "ch_support_streaks" );
		//if ( player.pers["triple_uav"] >= 3 )
		//	player processChallenge( "ch_???" );
		break;
	case "remote_mg_turret":
		player processChallenge( "ch_remote_mg_turret" );
		player processChallenge( "ch_support_streaks" );
		//if ( player.pers["remote_mg_turret"] >= 3 )
		//	player processChallenge( "ch_???" );
		break;
	case "stealth_airstrike":
		player processChallenge( "ch_stealth_airstrike" );
		player processChallenge( "ch_support_streaks" );
		//if ( player.pers["stealth_airstrike"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	case "emp":
		player processChallenge( "ch_emp" );
		player processChallenge( "ch_support_streaks" );
		//if ( player.pers["emp"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	case "airdrop_juggernaut_recon":
		player processChallenge( "ch_airdrop_juggernaut_recon" );
		player processChallenge( "ch_support_streaks" );
		//if ( player.pers["airdrop_juggernaut_recon"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	case "escort_airdrop":
		player processChallenge( "ch_escort_airdrop" );
		player processChallenge( "ch_support_streaks" );
		//if ( player.pers["escort_airdrop"] >= 2 )
		//	player processChallenge( "ch_???" );
		break;
	// End Support Killstreaks



	// Specialist Killstreaks
	case "specialty_longersprint_ks":
	case "specialty_longersprint_ks_pro":
		player processChallenge( "ch_longersprint_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_fastreload_ks":
	case "specialty_fastreload_ks_pro":
		player processChallenge( "ch_fastreload_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_scavenger_ks":
	case "specialty_scavenger_ks_pro":
		player processChallenge( "ch_scavenger_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_blindeye_ks":
	case "specialty_blindeye_ks_pro":
		player processChallenge( "ch_blindeye_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_paint_ks":
	case "specialty_paint_ks_pro":
		player processChallenge( "ch_paint_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_hardline_ks":
	case "specialty_hardline_ks_pro":
		player processChallenge( "ch_hardline_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_coldblooded_ks":
	case "specialty_coldblooded_ks_pro":
		player processChallenge( "ch_coldblooded_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_quickdraw_ks":
	case "specialty_quickdraw_ks_pro":
		player processChallenge( "ch_quickdraw_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "_specialty_blastshield_ks":
	case "_specialty_blastshield_ks_pro":
		player processChallenge( "ch_blastshield_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_detectexplosive_ks":
	case "specialty_detectexplosive_ks_pro":
		player processChallenge( "ch_detectexplosive_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_autospot_ks":
	case "specialty_autospot_ks_pro":
		player processChallenge( "ch_autospot_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_bulletaccuracy_ks":
	case "specialty_bulletaccuracy_ks_pro":
		player processChallenge( "ch_bulletaccuracy_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_quieter_ks":
	case "specialty_quieter_ks_pro":
		player processChallenge( "ch_quieter_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "specialty_stalker_ks":
	case "specialty_stalker_ks_pro":
		player processChallenge( "ch_stalker_ks" );
		player processChallenge( "ch_specialist_streaks" );
		break;
	case "all_perks_bonus":
		player processChallenge( "ch_all_perks_bonus" );
		break;
	// End Specialist Killstreaks



	// Secret Killstreaks
	case "nuke":
		player processChallenge( "ch_nuke" );
		break;
	}
}


ch_vehicle_kills( data )
{
	if ( !isDefined( data.attacker ) || !isPlayer( data.attacker ) )
		return;

	if ( !isKillstreakWeapon( data.sWeapon ) )
		return;
		
	player = data.attacker;

	if ( !isDefined( player.pers[data.sWeapon + "_streak"] ) )
		player.pers[data.sWeapon + "_streak"] = 0;

	player.pers[data.sWeapon + "_streak"]++;

	switch ( data.sWeapon )
	{
		case "artillery_mp":			// Precision Airstrike
			player processChallenge( "ch_carpetbomber" );

			if ( player.pers[data.sWeapon + "_streak"] >= 5 )
				player processChallenge( "ch_carpetbomb" );

			if ( isDefined( player.finalKill ) )
				player processChallenge( "ch_finishingtouch" );
			break;

		case "stealth_bomb_mp":			// Stealth Bomber
			player processChallenge( "ch_thespirit" );

			if ( player.pers[data.sWeapon + "_streak"] >= 5 )
				player processChallenge( "ch_redcarpet" );

			if ( isDefined( player.finalKill ) )
				player processChallenge( "ch_technokiller" );
			break;

		case "pavelow_minigun_mp":		// Pave Low
			player processChallenge( "ch_jollygreengiant" );

			if ( isDefined( player.finalKill ) )
				player processChallenge( "ch_transformer" );
			break;

		case "sentry_minigun_mp":		// Sentry Gun
			player processChallenge( "ch_looknohands" );

			if ( isDefined( player.finalKill ) )
				player processChallenge( "ch_absentee" );
			break;

		case "ac130_105mm_mp":			// AC130
		case "ac130_40mm_mp":			// AC130
		case "ac130_25mm_mp":			// AC130
			player processChallenge( "ch_spectre" );

			if ( isDefined( player.finalKill ) )
				player processChallenge( "ch_deathfromabove" );
			break;

		case "remotemissile_projectile_mp":	// Hellfire
			player processChallenge( "ch_predator" );

			if ( player.pers[data.sWeapon + "_streak"] >= 4 )
				player processChallenge( "ch_reaper" );

			if ( isDefined( player.finalKill ) )
				player processChallenge( "ch_dronekiller" );
			break;

		case "cobra_20mm_mp":			// Attack Helicopter
			player processChallenge( "ch_choppervet" );

			if ( isDefined( player.finalKill ) )
				player processChallenge( "ch_og" );
			break;

		case "nuke_mp":					// Nuke
			data.victim processChallenge( "ch_radiationsickness" );
			break;

		default:
			break;		
	}
}	


ch_vehicle_killed( data )
{
	if ( !isDefined( data.attacker ) || !isPlayer( data.attacker ) )
		return;

	player = data.attacker;
}


clearIDShortly( expId )
{
	self endon ( "disconnect" );
	
	self notify( "clearing_expID_" + expID );
	self endon ( "clearing_expID_" + expID );
	
	wait ( 3.0 );
	self.explosiveKills[expId] = undefined;
}

MGKill()
{
	player = self;
	if ( !isDefined( player.pers["MGStreak"] ) )
	{
		player.pers["MGStreak"] = 0;
		player thread endMGStreakWhenLeaveMG();
		if ( !isDefined( player.pers["MGStreak"] ) )
			return;
	}
	player.pers["MGStreak"]++;
	//iprintln( player.pers["MGStreak"] );
	if ( player.pers["MGStreak"] >= 5 )
		player processChallenge( "ch_mgmaster" );
}

endMGStreakWhenLeaveMG()
{
	self endon("disconnect");
	while(1)
	{
		if ( !isAlive( self ) || self useButtonPressed() )
		{
			self.pers["MGStreak"] = undefined;
			//iprintln("0");
			break;
		}
		wait .05;
	}
}

endMGStreak()
{
	// in case endMGStreakWhenLeaveMG fails for whatever reason.
	self.pers["MGStreak"] = undefined;
	//iprintln("0");
}

killedBestEnemyPlayer( wasBest )
{
	if ( !isdefined( self.pers["countermvp_streak"] ) || !wasBest )
		self.pers["countermvp_streak"] = 0;
	
	self.pers["countermvp_streak"]++;
	
	if ( self.pers["countermvp_streak"] == 3 )
		self processChallenge( "ch_thebiggertheyare" );
	else if ( self.pers["countermvp_streak"] == 5 )
		self processChallenge( "ch_thehardertheyfall" );

	if ( self.pers["countermvp_streak"] >= 10 )
		self processChallenge( "ch_countermvp" );
}


isHighestScoringPlayer( player )
{
	if ( !isDefined( player.score ) || player.score < 1 )
		return false;

	players = level.players;
	if ( level.teamBased )
		team = player.pers["team"];
	else
		team = "all";

	highScore = player.score;

	for( i = 0; i < players.size; i++ )
	{
		if ( !isDefined( players[i].score ) )
			continue;
			
		if ( players[i].score < 1 )
			continue;

		if ( team != "all" && players[i].pers["team"] != team )
			continue;
		
		if ( players[i].score > highScore )
			return false;
	}
	
	return true;
}


ch_kills( data, time )
{
	data.victim playerDied();
	
	if ( !isDefined( data.attacker ) || !isPlayer( data.attacker ) )
		return;
	
	player = data.attacker;
	
	time = data.time;
	
	if ( player.pers["cur_kill_streak"] == 10 )
		player processChallenge( "ch_fearless" );

	if ( level.teamBased )
	{
		if ( level.teamCount[data.victim.pers["team"]] > 3 && player.killedPlayers.size >= level.teamCount[data.victim.pers["team"]] )
		{
			player processChallenge( "ch_tangodown" );
			
			//maps\mp\_awards::addAwardWinner( "killedotherteam", player.clientid );
		}
	
		if ( level.teamCount[data.victim.pers["team"]] > 3 && player.killedPlayersCurrent.size >= level.teamCount[data.victim.pers["team"]] )
		{
			player processChallenge( "ch_extremecruelty" );
		
			//maps\mp\_awards::addAwardWinner( "killedotherteamonelife", player.clientid );
		}
	}

	// if the victim is within the attackers smoke when they are killed
	if( IsDefined( data.victim.inPlayerSmokeScreen ) && data.victim.inPlayerSmokeScreen == player )
		player processChallenge( "ch_smokeemifyougotem" );

	// if the victim is within the attackers scrambler proximity when they are killed
	if( IsDefined( data.victim.inPlayerScrambler ) && data.victim.inPlayerScrambler == player )
		player processChallenge( "ch_scram" );

	// if the victim is within the attackers portable radar proximity when they are killed
	if( IsDefined( data.victim.inPlayerPortableRadar ) && data.victim.inPlayerPortableRadar == player )
		player processChallenge( "ch_zerolatency" );

	if ( isDefined( player.killedPlayers[data.victim.guid] ) && player.killedPlayers[data.victim.guid] == 5 )
		player processChallenge( "ch_rival" );

	if ( isdefined( player.tookWeaponFrom[ data.sWeapon ] ) )
	{
		if ( player.tookWeaponFrom[ data.sWeapon ] == data.victim && data.sMeansOfDeath != "MOD_MELEE" )
			player processChallenge( "ch_cruelty" );
	}

	oneLeftCount = 0;

	secondaryCount = 0;
	longshotCount = 0;
	killsLast10s = 1;
	
	killedPlayers[data.victim.name] = data.victim.name;
	usedWeapons[data.sWeapon] = data.sWeapon;
	uniqueKills = 1;
	killstreakKills = [];
	
	foreach ( killData in player.killsThisLife )
	{
		if ( isCACSecondaryWeapon( killData.sWeapon ) && killData.sMeansOfDeath != "MOD_MELEE" )
			secondaryCount++;
		
		if ( isDefined( killData.modifiers["longshot"] ) )
			longshotCount++;

		if ( time - killData.time < 10000 )
			killsLast10s++;		

		if ( isKillstreakWeapon( killData.sWeapon ) )
		{
			if ( !isDefined( killstreakKills[ killData.sWeapon ] ) )
				killstreakKills[ killData.sWeapon ] = 0;

			killstreakKills[ killData.sWeapon ]++;
		}
		else
		{
			if ( isDefined( level.oneLeftTime[player.team] ) && killData.time > level.oneLeftTime[player.team] )
				oneLeftCount++;

			if ( isDefined( killData.victim ) )
			{
				if ( !isDefined( killedPlayers[killData.victim.name] ) && !isDefined( usedWeapons[killData.sWeapon] ) && !isKillStreakWeapon( killData.sWeapon ) )
					uniqueKills++;
		
				killedPlayers[killData.victim.name] = killData.victim.name;
			}
			
			usedWeapons[killData.sWeapon] = killData.sWeapon;
		}
	}

	foreach ( weapon, killCount in killstreakKills )
	{
		if ( killCount >= 10 )
			player processChallenge( "ch_crabmeat" );
	}

	if ( uniqueKills == 3 )
		player processChallenge( "ch_renaissance" );

	if ( killsLast10s > 3 && level.teamCount[data.victim.team] <= killsLast10s )
		player processChallenge( "ch_omnicide" );

	if ( isCACSecondaryWeapon( data.sWeapon ) && secondaryCount == 2 )
		player processChallenge( "ch_sidekick" );

	if ( isDefined( data.modifiers["longshot"] ) && longshotCount == 2 )
		player processChallenge( "ch_nbk" );
	
	if ( isDefined( level.oneLeftTime[player.team] ) && oneLeftCount == 2 )
		player processChallenge( "ch_enemyofthestate" );

	if ( player IsItemUnlocked( "specialty_twoprimaries" ) && player _hasPerk( "specialty_twoprimaries" ) && player.secondaryWeapon == data.sWeapon )
		player processChallenge( "ch_twoprimaries_pro" );

	if ( data.victim.score > 0 )
	{
		if ( level.teambased )
		{
			victimteam = data.victim.pers["team"];
			if ( isdefined( victimteam ) && victimteam != player.pers["team"] )
			{
				if ( isHighestScoringPlayer( data.victim ) && level.players.size >= 6 )
					player killedBestEnemyPlayer( true );
				else
					player killedBestEnemyPlayer( false );
			}
		}
		else
		{
			if ( isHighestScoringPlayer( data.victim ) && level.players.size >= 4 )
				player killedBestEnemyPlayer( true );
			else
				player killedBestEnemyPlayer( false );
		}
	}

	if ( isDefined( data.modifiers["avenger"] ) )
		player processChallenge( "ch_avenger" );
	
	if ( isDefined( data.modifiers["buzzkill"] ) && data.modifiers["buzzkill"] >= 9 )
		player processChallenge( "ch_thedenier" );

	// Filter out killstreak weapons	
	if ( isKillstreakWeapon( data.sWeapon ) )
		return;

	if ( isDefined( data.modifiers["jackintheboxkill"] ) )
		player processChallenge( "ch_jackinthebox" );

	if ( isDefined( data.modifiers["cooking"] ) )
		player processChallenge( "ch_no" );

	if ( isDefined( player.finalKill ) )
	{
		player processChallenge( "ch_theedge" );

		//*if ( isDefined( data.modifiers["revenge"] ) )
		//*	player processChallenge( "ch_moneyshot" );
	}

	if ( player isAtBrinkOfDeath() )
	{
		player.brinkOfDeathKillStreak++;
		if ( player.brinkOfDeathKillStreak >= 3 )
		{
			player processChallenge( "ch_thebrink" );
		}
	}
	
	if( IsDefined( player.inFinalStand ) && player.inFinalStand )
	{
		if( IsDefined( data.modifiers["revenge"] ) )
			player processChallenge( "ch_robinhood" );

		if( IsDefined( player.finalKill ) )
			player processChallenge( "ch_lastresort" );			

		if( isStrStart( data.sWeapon, "c4_" ) )
			player processChallenge( "ch_clickclickboom" );		

		player processChallenge( "ch_laststandvet" );
	}		

	if ( data.sMeansOfDeath == "MOD_PISTOL_BULLET" || data.sMeansOfDeath == "MOD_RIFLE_BULLET" )
	{

		weaponClass = getWeaponClass( data.sWeapon );
		ch_bulletDamageCommon( data, player, time, weaponClass );
	
		if ( isEnvironmentWeapon( data.sWeapon ) )
		{
			player MGKill();
		}
		else
		{
			baseWeapon = getBaseWeaponName( data.sWeapon );
			
			if ( isDefined( level.challengeInfo["ch_marksman_" + baseWeapon] ) )
				player processChallenge( "ch_marksman_" + baseWeapon );

			if ( isDefined( level.challengeInfo["pr_marksman_" + baseWeapon] ) )
				player processChallenge( "pr_marksman_" + baseWeapon );
				
			//track daily weaponclass challenges
			weaponClass = tablelookup( "mp/statstable.csv", 4, baseWeapon, 2 );
			
			switch ( weaponClass )
			{
				case "weapon_smg":
					player processChallenge( "ch_smg_kill" );
					break;
				case "weapon_assault":
					player processChallenge( "ch_ar_kill" );
					break;
				case "weapon_shotgun":
					player processChallenge( "ch_shotgun_kill" );
					break;
				case "weapon_sniper":
					player processChallenge( "ch_sniper_kill" );
					break;
				case "weapon_handgun":
					player processChallenge( "ch_handgun_kill" );
					break;
				case "weapon_machine_pistol":
					player processChallenge( "ch_machine_pistols_kill" );
					break;
				default:
			}
			
		}
	}
	else if ( isSubStr( data.sMeansOfDeath, "MOD_GRENADE" ) || isSubStr( data.sMeansOfDeath, "MOD_EXPLOSIVE" ) || isSubStr( data.sMeansOfDeath, "MOD_PROJECTILE" ) )
	{
		if ( isStrStart( data.sWeapon, "frag_grenade_short" ) && ( !isDefined( data.victim.explosiveInfo["throwbackKill"] ) || !data.victim.explosiveInfo["throwbackKill"] ) )
			player processChallenge( "ch_martyr" );

		// this isdefined check should not be needed... find out where these mystery explosions are coming from
		if ( isDefined( data.victim.explosiveInfo["damageTime"] ) && data.victim.explosiveInfo["damageTime"] == time )
		{
			if ( data.sWeapon == "none" )
				data.sWeapon = data.victim.explosiveInfo["weapon"];
			
			expId = time + "_" + data.victim.explosiveInfo["damageId"];
			if ( !isDefined( player.explosiveKills[expId] ) )
			{
				player.explosiveKills[expId] = 0;
			}
			player thread clearIDShortly( expId );
			
			player.explosiveKills[expId]++;
			
			baseWeapon = getBaseWeaponName( data.sWeapon );
			
			if ( baseWeapon == "javelin" || baseWeapon == "m79" || baseWeapon == "at4" || baseWeapon == "rpg" || baseWeapon == "iw5_smaw" )
			{
				//daily/weekly challenge
				player processChallenge( "ch_launcher_kill" );	
				
				if ( player.explosiveKills[expId] > 1 )
				{
					player processChallenge( "pr_expert_" + baseWeapon );
				}
			}	
			
			weaponAttachments = getWeaponAttachments( data.sWeapon );
			foreach( weaponAttachment in weaponAttachments )
			{
				switch ( weaponAttachment )
				{
				case "gl":
				case "m320":
				case "gp25":
					if( isStrStart( data.sWeapon, "alt_" ) )
						player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
					continue;
				}
			}
			
			if ( isDefined( data.victim.explosiveInfo["stickKill"] ) && data.victim.explosiveInfo["stickKill"] )
			{
				if ( isDefined( data.modifiers["revenge"] ) ) 
					player processChallenge( "ch_overdraft" );				

				if ( isDefined( player.finalKill ) )
					player processChallenge( "ch_stickman" );

				if ( player.explosiveKills[expId] > 1 )
					player processChallenge( "ch_grouphug" );
			}

			if ( isDefined( data.victim.explosiveInfo["stickFriendlyKill"] ) && data.victim.explosiveInfo["stickFriendlyKill"] )
			{
				player processChallenge( "ch_resourceful" );
			}
			
			if ( !isSubStr( baseWeapon, "stinger" ) )
			{
				if ( isDefined( level.challengeInfo["ch_marksman_" + baseWeapon] ) )
					player processChallenge( "ch_marksman_" + baseWeapon );
	
				if ( isDefined( level.challengeInfo["pr_marksman_" + baseWeapon] ) )
					player processChallenge( "pr_marksman_" + baseWeapon );
			}
			
			if ( isStrStart( data.sWeapon, "frag_" ) )
			{
				if ( player.explosiveKills[expId] > 1 )
					player processChallenge( "ch_multifrag" );
	
				if ( isDefined( data.modifiers["revenge"] ) ) 
					player processChallenge( "ch_bangforbuck" );				
				
				player processChallenge( "ch_grenadekill" );
				
				if ( data.victim.explosiveInfo["cookedKill"] )
					player processChallenge( "ch_masterchef" );
				
				if ( data.victim.explosiveInfo["suicideGrenadeKill"] )
					player processChallenge( "ch_miserylovescompany" );
				
				if ( data.victim.explosiveInfo["throwbackKill"] )
					player processChallenge( "ch_hotpotato" );
			}
			else if ( isStrStart( data.sWeapon, "semtex_" ) )
			{
				if ( isDefined( data.modifiers["revenge"] ) ) 
					player processChallenge( "ch_timeismoney" );				
			}
			else if ( isStrStart( data.sWeapon, "c4_" ) )
			{
				if ( isDefined( data.modifiers["revenge"] ) ) 
					player processChallenge( "ch_iamrich" );				

				if ( player.explosiveKills[expId] > 1 )
					player processChallenge( "ch_multic4" );

				if ( data.victim.explosiveInfo["returnToSender"] )
					player processChallenge( "ch_returntosender" );				
				
				if ( data.victim.explosiveInfo["counterKill"] )
					player processChallenge( "ch_counterc4" );
				
				if ( data.victim.explosiveInfo["bulletPenetrationKill"] )
					player processChallenge( "ch_howthe" );

				if ( data.victim.explosiveInfo["chainKill"] )
					player processChallenge( "ch_dominos" );

				player processChallenge( "ch_c4shot" );
			}
			else if ( isStrStart( data.sWeapon, "claymore_" ) )
			{
				if ( isDefined( data.modifiers["revenge"] ) ) 
					player processChallenge( "ch_breakbank" );				

				player processChallenge( "ch_claymoreshot" );

				if ( player.explosiveKills[expId] > 1 )
					player processChallenge( "ch_multiclaymore" );

				if ( data.victim.explosiveInfo["returnToSender"] )
					player processChallenge( "ch_returntosender" );				

				if ( data.victim.explosiveInfo["counterKill"] )
					player processChallenge( "ch_counterclaymore" );
				
				if ( data.victim.explosiveInfo["bulletPenetrationKill"] )
					player processChallenge( "ch_howthe" );

				if ( data.victim.explosiveInfo["chainKill"] )
					player processChallenge( "ch_dominos" );
			}
			else if ( isStrStart( data.sWeapon, "bouncingbetty_" ) )
			{
				player processChallenge( "ch_bouncingbetty" );
			}
			else if ( data.sWeapon == "explodable_barrel" )
			{
				//player processChallenge( "ch_redbarrelsurprise" );
			}
			else if ( data.sWeapon == "destructible_car" )
			{
				player processChallenge( "ch_carbomb" );
			}
			else if ( isStrStart( data.sWeapon, "rpg_" ) || isStrStart( data.sWeapon, "at4_" ) || isStrStart( data.sWeapon, "iw5_smaw_" ) )
			{
				if ( player.explosiveKills[expId] > 1 )
					player processChallenge( "ch_multirpg" );
			}
		}
	}
	else if ( isSubStr( data.sMeansOfDeath,	"MOD_MELEE" ) && !isSubStr( data.sWeapon, "riotshield_mp" ) )
	{
		player endMGStreak();
		
		player processChallenge( "ch_knifevet" );
		player.pers["meleeKillStreak"]++;

		if ( player.pers["meleeKillStreak"] == 3 )
			player processChallenge( "ch_slasher" );
		
		if ( player IsItemUnlocked( "specialty_quieter" ) && player _hasPerk( "specialty_quieter" ) )
			player processChallenge( "ch_deadsilence_pro" );
		
		vAngles = data.victim.anglesOnDeath[1];
		pAngles = player.anglesOnKill[1];
		angleDiff = AngleClamp180( vAngles - pAngles );
		if ( abs(angleDiff) < 30 )
		{
			player processChallenge( "ch_backstabber" );
			
			if ( isDefined( player.attackers ) )
			{
				foreach ( attacker in player.attackers )
				{
					if ( attacker != data.victim )
						continue;
						
					player processChallenge( "ch_neverforget" );
					break;
				}
			}
		}

		if ( !player playerHasAmmo() )
			player processChallenge( "ch_survivor" );
			
		/*if ( isDefined( player.infected ) )
			data.victim processChallenge( "ch_infected" );

		if ( isDefined( data.victim.plague ) )
			player processChallenge( "ch_plague" );*/
		
		baseWeapon = getBaseWeaponName( data.sWeapon );
		weaponAttachments = getWeaponAttachments( data.sWeapon );
		foreach( weaponAttachment in weaponAttachments )
		{
			switch ( weaponAttachment )
			{
			case "tactical":
				player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				if( isDefined( level.challengeInfo[ "ch_marksman_" + baseWeapon ] ) )
					player processChallenge( "ch_marksman_" + baseWeapon );
				if( isDefined( level.challengeInfo[ "pr_marksman_" + baseWeapon ] ) )
					player processChallenge( "pr_marksman_" + baseWeapon );
				continue;
			}
		}
	}
	else if ( isSubStr( data.sMeansOfDeath,	"MOD_MELEE" ) && isSubStr( data.sWeapon, "riotshield_mp" ) )
	{
		player endMGStreak();
		
		player processChallenge( "ch_shieldvet" );
		player.pers["shieldKillStreak"]++;

		if ( player.pers["shieldKillStreak"] == 3 )
			player processChallenge( "ch_smasher" );

		if ( isDefined( player.finalKill ) )
			player processChallenge( "ch_owned" );
		
		//IW5 daily/weekly
		player processChallenge( "ch_riot_kill" );
		
		vAngles = data.victim.anglesOnDeath[1];
		pAngles = player.anglesOnKill[1];
		angleDiff = AngleClamp180( vAngles - pAngles );
		if ( abs(angleDiff) < 30 )
			player processChallenge( "ch_backsmasher" );	

		if ( !player playerHasAmmo() )
			player processChallenge( "ch_survivor" );
	}
	else if ( isSubStr( data.sMeansOfDeath,	"MOD_IMPACT" ) )
	{
		if ( isStrStart( data.sWeapon, "frag_" ) )
			player processChallenge( "ch_thinkfast" );
		else if ( isStrStart( data.sWeapon, "concussion_" ) )
			player processChallenge( "ch_thinkfastconcussion" );
		else if ( isStrStart( data.sWeapon, "flash_" ) )
			player processChallenge( "ch_thinkfastflash" );

		if ( data.sWeapon == "throwingknife_mp" )
		{
			if ( isDefined( data.modifiers["revenge"] ) )
				player processChallenge( "ch_atm" );			

			if ( time < player.flashEndTime || time < player.concussionEndTime )
				player processChallenge( "ch_didyouseethat" );

			if ( isDefined( player.finalKill ) )
				player processChallenge( "ch_unbelievable" );
				
			player processChallenge( "ch_carnie" );
			
			if ( isDefined( data.victim.attackerData[player.guid].isPrimary ) )
				player processChallenge( "ch_its_personal" );
		}
		
		weaponAttachments = getWeaponAttachments( data.sWeapon );
		baseWeapon = getBaseWeaponName( data.sWeapon );
		foreach( weaponAttachment in weaponAttachments )
		{
			switch ( weaponAttachment )
			{
			case "gl":
			case "m320":
			case "gp25":
				if( isStrStart( data.sWeapon, "alt_" ) )
				{
					player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
					if( isDefined( level.challengeInfo[ "ch_marksman_" + baseWeapon ] ) )
						player processChallenge( "ch_marksman_" + baseWeapon );
					if( isDefined( level.challengeInfo[ "pr_marksman_" + baseWeapon ] ) )
						player processChallenge( "pr_marksman_" + baseWeapon );
					player processChallenge( "ch_ouch" );
				}
				continue;
			}
		}
	}
	else if ( data.sMeansOfDeath == "MOD_HEAD_SHOT" )
	{
		weaponClass = getWeaponClass( data.sWeapon );
		
		ch_bulletDamageCommon( data, player, time, weaponClass );
	
		switch ( weaponClass )
		{
			case "weapon_smg":
				player processChallenge( "ch_expert_smg" );
				break;
			case "weapon_lmg":
				player processChallenge( "ch_expert_lmg" );
				break;
			case "weapon_assault":
				player processChallenge( "ch_expert_assault" );
				break;
		}

		if ( isDefined( data.modifiers["revenge"] ) )
			player processChallenge( "ch_colorofmoney" );

		if ( isEnvironmentWeapon( data.sWeapon ) )
		{
			player MGKill();
		}
		else if ( isStrStart( data.sWeapon, "frag_" ) )
		{
			player processChallenge( "ch_thinkfast" );
		}
		else if ( isStrStart( data.sWeapon, "concussion_" ) )
		{
			player processChallenge( "ch_thinkfastconcussion" );
		}
		else if ( isStrStart( data.sWeapon, "flash_" ) )
		{
			player processChallenge( "ch_thinkfastflash" );
		}
		else
		{
			baseWeapon = getBaseWeaponName( data.sWeapon );
			
			if ( isDefined( level.challengeInfo["ch_expert_" + baseWeapon] ) )
				player processChallenge( "ch_expert_" + baseWeapon );

			if ( isDefined( level.challengeInfo["pr_expert_" + baseWeapon] ) )
				player processChallenge( "pr_expert_" + baseWeapon );

			if ( isDefined( level.challengeInfo["ch_marksman_" + baseWeapon] ) )
				player processChallenge( "ch_marksman_" + baseWeapon );

			if ( isDefined( level.challengeInfo["pr_marksman_" + baseWeapon] ) )
				player processChallenge( "pr_marksman_" + baseWeapon );
		}
	}
	
	
	if( ( data.sMeansOfDeath == "MOD_PISTOL_BULLET" || data.sMeansOfDeath == "MOD_RIFLE_BULLET" || data.sMeansOfDeath == "MOD_HEAD_SHOT" ) && 
		!isKillstreakWeapon( data.sWeapon ) && 
		!isEnvironmentWeapon( data.sWeapon ) )
	{
		// checks and processes all weapon attachment challenges
		weaponAttachments = getWeaponAttachments( data.sWeapon );
		baseWeapon = getBaseWeaponName( data.sWeapon );
		foreach( weaponAttachment in weaponAttachments )
		{		
			switch ( weaponAttachment )
			{
			case "acog":
			case "acogsmg":
				weaponAttachment = "acog";
				if ( player PlayerAds() )
					player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "akimbo":
				player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "eotech":
			case "eotechsmg":
			case "eotechlmg":
				weaponAttachment = "eotech";
				if ( player PlayerAds() )
					player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "grip":
				player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "heartbeat":
				player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "hamrhybrid":
				if ( player PlayerAds() )
					player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "hybrid":
				if ( player PlayerAds() )
					player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "reflex":
			case "reflexsmg":
			case "reflexlmg":
				weaponAttachment = "reflex";
				if ( player PlayerAds() )
					player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "rof":
				player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "shotgun":
				if( isStrStart( data.sWeapon, "alt_" ) )
					player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "silencer":
			case "silencer01":
			case "silencer02":
			case "silencer03":
				player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "thermal":
			case "thermalsmg":
				weaponAttachment = "thermal";
				if ( player PlayerAds() )
					player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "vzscope":
				if ( player PlayerAds() )
					player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			case "xmags":
				player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
				continue;
			//case "fmj":
			//	if ( data.victim.iDFlags & level.iDFLAGS_PENETRATION )	
			//		player processChallenge( "ch_" + baseWeapon + "_" + weaponAttachment );
			//	continue;
			default:
				continue;					
			}
		}
			
		if( player IsItemUnlocked( "specialty_autospot" ) && player _hasPerk( "specialty_autospot" ) && ( player.holdingBreath && player PlayerAds() ) )
			player processChallenge( "ch_autospot_pro" );

		if ( player IsItemUnlocked( "specialty_bulletaccuracy" ) && player _hasPerk( "specialty_bulletaccuracy" ) && !player PlayerAds() )
			player processChallenge( "ch_bulletaccuracy_pro" );
		
		if ( player IsItemUnlocked( "specialty_stalker" ) && player _hasPerk( "specialty_stalker" ) && player PlayerAds() )
			player processChallenge( "ch_stalker_pro" );

		if ( distanceSquared( player.origin, data.victim.origin ) < 65536 )// 256^2 
		{
			if ( player IsItemUnlocked( "specialty_quieter" ) && player _hasPerk( "specialty_quieter" ) )
				player processChallenge( "ch_deadsilence_pro" );
		}
		
		if ( player IsItemUnlocked( "specialty_fastreload" ) && player _hasPerk( "specialty_fastreload" ) )
			player processChallenge( "ch_sleightofhand_pro" );
		
		if ( player isBuffUnlockedForWeapon( "specialty_marksman", baseWeapon ) && player isBuffEquippedOnWeapon( "specialty_marksman", baseWeapon ) && player _hasPerk( "specialty_marksman" ) && player PlayerAds() )
			player processChallenge( "ch_kickstop" );

		if ( data.victim.iDFlagsTime == time )
		{
			if ( data.victim.iDFlags & level.iDFLAGS_PENETRATION )
			{
				if( player isBuffUnlockedForWeapon( "specialty_bulletpenetration", baseWeapon ) && player isBuffEquippedOnWeapon( "specialty_bulletpenetration", baseWeapon ) && player _hasPerk( "specialty_bulletpenetration" ) )
					player processChallenge( "ch_xrayvision" ); 
			}
		}

		if ( player isBuffUnlockedForWeapon( "specialty_bling", baseWeapon ) && player isBuffEquippedOnWeapon( "specialty_bling", baseWeapon ) && player _hasPerk( "specialty_bling" ) && weaponAttachments.size > 1 )
			player processChallenge( "ch_blingbling" );

		if ( player isBuffUnlockedForWeapon( "specialty_sharp_focus", baseWeapon ) && player isBuffEquippedOnWeapon( "specialty_sharp_focus", baseWeapon ) && player _hasPerk( "specialty_sharp_focus" ) && player.health < player.maxHealth && IsDefined( player.attackers ) )
		{
			foreach( attacker in player.attackers )
			{
				if( attacker == data.victim )
				{
					player processChallenge( "ch_unshakeable" );
					break;
				}
			}
		}

		if( player isBuffUnlockedForWeapon( "specialty_holdbreathwhileads", baseWeapon ) && player isBuffEquippedOnWeapon( "specialty_holdbreathwhileads", baseWeapon ) && player _hasPerk( "specialty_holdbreathwhileads" ) && ( player.holdingBreath && player PlayerAds() ) )
			player processChallenge( "ch_holditrightthere" );

		if( player isBuffUnlockedForWeapon( "specialty_reducedsway", baseWeapon ) && player isBuffEquippedOnWeapon( "specialty_reducedsway", baseWeapon ) && player _hasPerk( "specialty_reducedsway" ) && player PlayerAds() )
			player processChallenge( "ch_swayless" );

		if( player isBuffUnlockedForWeapon( "specialty_longerrange", baseWeapon ) && player isBuffEquippedOnWeapon( "specialty_longerrange", baseWeapon ) && player _hasPerk( "specialty_longerrange" ) )
			player processChallenge( "ch_longishshot" );

		if( player isBuffUnlockedForWeapon( "specialty_lightweight", baseWeapon ) && player isBuffEquippedOnWeapon( "specialty_lightweight", baseWeapon ) && player _hasPerk( "specialty_lightweight" ) )
			player processChallenge( "ch_lightweight" );

		if( player isBuffUnlockedForWeapon( "specialty_moredamage", baseWeapon ) && player isBuffEquippedOnWeapon( "specialty_moredamage", baseWeapon ) && player _hasPerk( "specialty_moredamage" ) )
			player processChallenge( "ch_moredamage" );
	}
	
	if( data.sMeansOfDeath == "MOD_MELEE" )
	{
		baseWeapon = getBaseWeaponName( data.sWeapon );
		if( player isBuffUnlockedForWeapon( "specialty_fastermelee", baseWeapon ) && player isBuffEquippedOnWeapon( "specialty_fastermelee", baseWeapon ) && player _hasPerk( "specialty_fastermelee" ) )
			player processChallenge( "ch_coldsteel" );
	}

	if( player IsItemUnlocked( "specialty_quickdraw" ) && player _hasPerk( "specialty_quickdraw" ) && ( player.adsTime > 0 && player.adsTime < 3 ) )
		player processChallenge( "ch_quickdraw_pro" );		

	if( player IsItemUnlocked( "specialty_coldblooded" ) && player _hasPerk( "specialty_coldblooded" ) )
	{
		if( level.teambased )
		{
			uavUp = false;
			foreach( uav in level.uavmodels[ getOtherTeam( player.team ) ] )
			{
				switch( uav.uavType )
				{
				case "counter":
				case "remote_mortar":
					continue;
				}

				uavUp = true;
				break;
			}	
			if( uavUp )
				player processChallenge( "ch_coldblooded_pro" );		
		}
		else
		{
			activeUAVs = 0;
			foreach( otherPlayer in level.players )
			{
				if( otherPlayer == player )
					continue;
				activeUAVs += level.activeUAVs[ otherPlayer.guid ];
			}
			// enemy uav is up
			if( activeUAVs > 0 )
				player processChallenge( "ch_coldblooded_pro" );
		}
	}

	if( player IsItemUnlocked( "specialty_empimmune" ) && player _hasPerk( "specialty_empimmune" ) )
	{
		if( level.teambased )
		{
			cuavUp = false;
			foreach( cuav in level.uavmodels[ getOtherTeam( player.team ) ] )
			{
				if( cuav.uavType != "counter" )
					continue;

				cuavUp = true;
				break;
			}	
			if( cuavUp || player isEMPed() )
				player processChallenge( "ch_spygame" );		
		}
		else
		{
			// enemy cuav or emp is up
			if( player.isRadarBlocked || player isEMPed() )
			{
				player processChallenge( "ch_spygame" );
			}
		}
	}

	if ( isDefined( data.victim.isPlanting ) && data.victim.isPlanting )
		player processChallenge( "ch_bombplanter" );		

	if ( isDefined( data.victim.isDefusing ) && data.victim.isDefusing )
		player processChallenge( "ch_bombdefender" );

	if ( isDefined( data.victim.isBombCarrier ) && data.victim.isBombCarrier && ( !isDefined( level.dd ) || !level.dd ) )
		player processChallenge( "ch_bombdown" );

	if ( isDefined( data.victim.wasTI ) && data.victim.wasTI )
		player processChallenge( "ch_tacticaldeletion" );
		
	if( player IsItemUnlocked( "specialty_quickswap" ) && player _hasPerk( "specialty_quickswap" ) )
	{
		if( IsDefined( player.lastPrimaryWeaponSwapTime ) && ( GetTime() - player.lastPrimaryWeaponSwapTime ) < 3000 )
			player processChallenge( "ch_quickswap" );
	}

	if( player IsItemUnlocked( "specialty_extraammo" ) && player _hasPerk( "specialty_extraammo" ) )
		player processChallenge( "ch_extraammo" );

	if( IsExplosiveDamageMOD( data.sMeansOfDeath ) )
	{
		switch( data.sWeapon )
		{
		case "frag_grenade_mp":
		case "semtex_mp":
		case "throwingkinfe_mp":
		case "flash_grenade_mp":
		case "concussion_grenade_mp":
		case "emp_grenade_mp":
			if( player IsItemUnlocked( "specialty_fastoffhand" ) && player _hasPerk( "specialty_fastoffhand" ) )
				player processChallenge( "ch_fastoffhand" );
			break;
		}
	}

	if ( player IsItemUnlocked( "specialty_overkillpro" ) && player _hasPerk( "specialty_overkillpro" ) )
	{
		if( player.secondaryWeapon == data.sWeapon )
		{
			weaponAttachments = getWeaponAttachments( data.sWeapon );
			if( weaponAttachments.size > 0 )
				player processChallenge( "ch_secondprimary" );
		}
	}

	if( player IsItemUnlocked( "specialty_stun_resistance" ) && player _hasPerk( "specialty_stun_resistance" ) )
	{
		if( IsDefined( player.lastFlashedTime ) && ( GetTime() - player.lastFlashedTime ) < 5000 )
			player processChallenge( "ch_stunresistance" );
		else if( IsDefined( player.lastConcussedTime ) && ( GetTime() - player.lastConcussedTime ) < 5000 )
			player processChallenge( "ch_stunresistance" );
	}

	if( player IsItemUnlocked( "specialty_selectivehearing" ) && player _hasPerk( "specialty_selectivehearing" ) )
		player processChallenge( "ch_selectivehearing" );

	if( player IsItemUnlocked( "specialty_fastsprintrecovery" ) && player _hasPerk( "specialty_fastsprintrecovery" ) )
	{
		if( IsDefined( player.lastSprintEndTime ) && ( GetTime() - player.lastSprintEndTime ) < 3000 )
			player processChallenge( "ch_fastsprintrecovery" );
	}
}

ch_bulletDamageCommon( data, player, time, weaponClass )
{
	if ( !isEnvironmentWeapon( data.sWeapon ) )
		player endMGStreak();
		
	if ( isKillstreakWeapon( data.sWeapon ) )
		return;
	
	if ( player.pers["lastBulletKillTime"] == time )
		player.pers["bulletStreak"]++;
	else
		player.pers["bulletStreak"] = 1;
	
	player.pers["lastBulletKillTime"] = time;

	if ( !data.victimOnGround )
		player processChallenge( "ch_hardlanding" );
	
	assert( data.attacker == player );
	if ( !data.attackerOnGround )
		player.pers["midairStreak"]++;
	
	if ( player.pers["midairStreak"] == 2 )
		player processChallenge( "ch_airborne" );
	
	if ( time < data.victim.flashEndTime )
		player processChallenge( "ch_flashbangvet" );
	
	if ( time < player.flashEndTime )
		player processChallenge( "ch_blindfire" );
	
	if ( time < data.victim.concussionEndTime )
		player processChallenge( "ch_concussionvet" );
	
	if ( time < player.concussionEndTime )
		player processChallenge( "ch_slowbutsure" );
	
	
	if ( player.pers["bulletStreak"] == 2  )
	{
		if ( isDefined( data.modifiers["headshot"] ) )
		{
			foreach ( killData in player.killsThisLife )
			{
				if ( killData.time != time )
					continue;
					
				if ( !isDefined( data.modifiers["headshot"] ) )
					continue;
					
				player processChallenge( "ch_allpro" );
			}
		}

		if ( weaponClass == "weapon_sniper" )
			player processChallenge( "ch_collateraldamage" );
	}
	
	if ( weaponClass == "weapon_pistol" )
	{
		if ( isdefined( data.victim.attackerData ) && isdefined( data.victim.attackerData[player.guid] ) )
		{
			if ( isDefined ( data.victim.attackerData[player.guid].isPrimary ) )
				player processChallenge( "ch_fastswap" );
		}
	}
	
	if( !IsDefined( player.inFinalStand ) || !player.inFinalStand )
	{
		if ( data.attackerStance == "crouch" )
		{
			player processChallenge( "ch_crouchshot" );
		}
		else if ( data.attackerStance == "prone" )
		{
			player processChallenge( "ch_proneshot" );
			if ( weaponClass == "weapon_sniper" )
			{
				player processChallenge( "ch_invisible" );
			}
		}
	}
	
	if ( weaponClass == "weapon_sniper" )
	{
		if ( isDefined( data.modifiers["oneshotkill"] ) )
			player processChallenge( "ch_ghillie" );	
	}
	
	if ( isSubStr( data.sWeapon, "silencer" ) )
		player processChallenge( "ch_stealthvet" ); 
}

ch_roundplayed( data )
{
	player = data.player;
	
	if ( player.wasAliveAtMatchStart )
	{
		deaths = player.pers[ "deaths" ];
		kills = player.pers[ "kills" ];

		kdratio = 1000000;
		if ( deaths > 0 )
			kdratio = kills / deaths;
		
		if ( kdratio >= 5.0 && kills >= 5.0 )
		{
			player processChallenge( "ch_starplayer" );
		}
		
		if ( deaths == 0 && getTimePassed() > 5 * 60 * 1000 )
			player processChallenge( "ch_flawless" );
		
		//not enough players to count as winning
		if ( level.placement["all"].size < 3 )
			return;
			
		if ( player.score > 0 )
		{
			switch ( level.gameType )
			{
				case "dm":
					if ( data.place < 3 )
					{
						player processChallenge( "ch_victor_dm" );	
						player processChallenge( "ch_ffa_win" );					
					}
					player processChallenge( "ch_ffa_participate" );	
					break;
				case "war":
					if ( data.winner )
					{
						player processChallenge( "ch_war_win" );
					}
					player processChallenge( "ch_war_participate" );
					break;
				case "kc":
					if ( data.winner )
					{
						player processChallenge( "ch_kc_win" );
					}
					player processChallenge( "ch_kc_participate" );
					break;
				case "dd":
					if ( data.winner )
					{
						player processChallenge( "ch_dd_win" );
					}
					player processChallenge( "ch_dd_participate" );
					break;
				case "koth":
					if ( data.winner )
					{
						player processChallenge( "ch_koth_win" );
					}
					player processChallenge( "ch_koth_participate" );
					break;
				case "sab":
					if ( data.winner )
					{
						player processChallenge( "ch_sab_win" );
					}
					player processChallenge( "ch_sab_participate" );
					break;
				case "sd":
					if ( data.winner )
					{
						player processChallenge( "ch_sd_win" );
					}
					player processChallenge( "ch_sd_participate" );
					break;
				case "dom":
					if ( data.winner )
					{
						player processChallenge( "ch_dom_win" );
					}
					player processChallenge( "ch_dom_participate" );
					break;
				case "ctf":
					if ( data.winner )
					{
						player processChallenge( "ch_ctf_win" );
					}
					player processChallenge( "ch_ctf_participate" );
					break;
				case "tdef":
					if ( data.winner )
					{
						player processChallenge( "ch_tdef_win" );
					}
					player processChallenge( "ch_tdef_participate" );
					break;
			}
		}
	}
}


ch_roundwin( data )
{
	if ( !data.winner )
		return;
		
	player = data.player;
	if ( player.wasAliveAtMatchStart )
	{
		switch ( level.gameType )
		{
			case "war":
				if ( level.hardcoreMode )
				{
					player processChallenge( "ch_teamplayer_hc" );
					if ( data.place == 0 )
						player processChallenge( "ch_mvp_thc" );
				}
				else
				{
					player processChallenge( "ch_teamplayer" );
					if ( data.place == 0 )
						player processChallenge( "ch_mvp_tdm" );
				}
				break;
			case "sab":
				player processChallenge( "ch_victor_sab" );
				break;
			case "sd":
				player processChallenge( "ch_victor_sd" );
				break;
			case "ctf":
			case "dom":
			case "dm":
			case "hc":
			case "koth":
				break;
			default:
				break;
		}
	}
}

/*
char *modNames[MOD_NUM] =
{
	"MOD_UNKNOWN",
	"MOD_PISTOL_BULLET",
	"MOD_RIFLE_BULLET",
	"MOD_GRENADE",
	"MOD_GRENADE_SPLASH",
	"MOD_PROJECTILE",
	"MOD_PROJECTILE_SPLASH",
	"MOD_MELEE",
	"MOD_HEAD_SHOT",
	"MOD_CRUSH",
	"MOD_TELEFRAG",
	"MOD_FALLING",
	"MOD_SUICIDE",
	"MOD_TRIGGER_HURT",
	"MOD_EXPLOSIVE",
	"MOD_IMPACT",
};

static const char *g_HitLocNames[] =
{
	"none",
	"helmet",
	"head",
	"neck",
	"torso_upper",
	"torso_lower",
	"right_arm_upper",
	"left_arm_upper",
	"right_arm_lower",
	"left_arm_lower",
	"right_hand",
	"left_hand",
	"right_leg_upper",
	"left_leg_upper",
	"right_leg_lower",
	"left_leg_lower",
	"right_foot",
	"left_foot",
	"gun",
};

*/

// ==========================================
// Callback functions

playerDamaged( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, sHitLoc )
{
	self endon("disconnect");
	if ( isdefined( attacker ) )
		attacker endon("disconnect");
	
	wait .05;
	WaitTillSlowProcessAllowed();

	data = spawnstruct();

	data.victim = self;
	data.eInflictor = eInflictor;
	data.attacker = attacker;
	data.iDamage = iDamage;
	data.sMeansOfDeath = sMeansOfDeath;
	data.sWeapon = sWeapon;
	data.sHitLoc = sHitLoc;
	
	data.victimOnGround = data.victim isOnGround();
	
	if ( isPlayer( attacker ) )
	{
		data.attackerInLastStand = isDefined( data.attacker.lastStand );
		data.attackerOnGround = data.attacker isOnGround();
		data.attackerStance = data.attacker getStance();
	}
	else
	{
		data.attackerInLastStand = false;
		data.attackerOnGround = false;
		data.attackerStance = "stand";
	}
	
	doMissionCallback("playerDamaged", data);
}

playerKilled( eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon, sPrimaryWeapon, sHitLoc, modifiers )
{
	self.anglesOnDeath = self getPlayerAngles();
	if ( isdefined( attacker ) )
		attacker.anglesOnKill = attacker getPlayerAngles();
	
	self endon("disconnect");

	data = spawnstruct();

	data.victim = self;
	data.eInflictor = eInflictor;
	data.attacker = attacker;
	data.iDamage = iDamage;
	data.sMeansOfDeath = sMeansOfDeath;
	data.sWeapon = sWeapon;
	data.sPrimaryWeapon = sPrimaryWeapon;
	data.sHitLoc = sHitLoc;
	data.time = gettime();
	data.modifiers = modifiers;
	
	data.victimOnGround = data.victim isOnGround();
	
	if ( isPlayer( attacker ) )
	{
		data.attackerInLastStand = isDefined( data.attacker.lastStand );
		data.attackerOnGround = data.attacker isOnGround();
		data.attackerStance = data.attacker getStance();
	}
	else
	{
		data.attackerInLastStand = false;
		data.attackerOnGround = false;
		data.attackerStance = "stand";
	}

	waitAndProcessPlayerKilledCallback( data );	
	
	if ( isDefined( attacker ) && isReallyAlive( attacker ) )
		attacker.killsThisLife[attacker.killsThisLife.size] = data;	

	data.attacker notify( "playerKilledChallengesProcessed" );
}


vehicleKilled( owner, vehicle, eInflictor, attacker, iDamage, sMeansOfDeath, sWeapon )
{
	data = spawnstruct();

	data.vehicle = vehicle;
	data.victim = owner;
	data.eInflictor = eInflictor;
	data.attacker = attacker;
	data.iDamage = iDamage;
	data.sMeansOfDeath = sMeansOfDeath;
	data.sWeapon = sWeapon;
	data.time = gettime();
	
	if ( IsDefined( attacker ) && isPlayer( attacker ) && ( !IsDefined( owner ) || attacker != owner ) && !isKillstreakWeapon( sWeapon ) )
	{
		attacker maps\mp\killstreaks\_killstreaks::giveAdrenaline( "vehicleDestroyed" );

		switch( sWeapon )
		{
		case "stinger_mp":
			// stinger marksman is kill n vehicles, stinger expert is kill n helicopters
			if( IsDefined( vehicle.helitype ) && 
				( vehicle.helitype == "flares" || vehicle.helitype == "littlebird" || vehicle.helitype == "helicopter" || vehicle.heliType == "airdrop" ) )
			{
				attacker processChallenge( "pr_expert_stinger" );
			}
			attacker processChallenge( "ch_marksman_stinger" );
			attacker processChallenge( "pr_marksman_stinger" );
			break;

		// all other weapons can process this vehicle kill as a kill
		default:
			baseWeapon = getBaseWeaponName( sWeapon );

			if( IsDefined( level.challengeInfo["ch_marksman_" + baseWeapon] ) )
				attacker processChallenge( "ch_marksman_" + baseWeapon );

			if( IsDefined( level.challengeInfo["pr_marksman_" + baseWeapon] ) )
				attacker processChallenge( "pr_marksman_" + baseWeapon );
			break;
		}

		// only check lock-on weapon for the faster lock-on challenge
		switch( sWeapon )
		{
		case "iw5_smaw_mp":
		case "stinger_mp":
		case "javelin_mp":
			if( attacker IsItemUnlocked( "specialty_fasterlockon" ) && attacker _hasPerk( "specialty_fasterlockon" ) )
				attacker processChallenge( "ch_fasterlockon" );
			break;
		}
		
		if ( attacker IsItemUnlocked( "specialty_blindeye" ) && attacker _hasPerk( "specialty_blindeye" ) )
		{
			// we give blind eye when you spawn and if you're in a scrambler, so make sure that isn't the case now
			process = true;
			if( IsDefined( attacker.scramProxyPerk ) && attacker.scramProxyPerk )
				process = false;
			if( IsDefined( attacker.spawnPerk ) && attacker.spawnPerk )
				process = false;

			if( process )
				attacker processChallenge( "ch_blindeye_pro" );
		}
	}
}


waitAndProcessPlayerKilledCallback( data )
{
	if ( isdefined( data.attacker ) )
		data.attacker endon("disconnect");
	
	self.processingKilledChallenges = true;
	wait 0.05;
	WaitTillSlowProcessAllowed();
	
	doMissionCallback( "playerKilled", data );
	self.processingKilledChallenges = undefined;
}

playerAssist()
{
	data = spawnstruct();

	data.player = self;

	doMissionCallback( "playerAssist", data );
}


useHardpoint( hardpointType )
{
	// since this is threaded we need this endon in case they player disconnects, this fixes an sre when calling the ac130 and leaving the game as you are entering it
	self endon( "disconnect" );

	wait .05;
	WaitTillSlowProcessAllowed();

	data = spawnstruct();

	data.player = self;
	data.hardpointType = hardpointType;

	doMissionCallback( "playerHardpoint", data );
}


roundBegin()
{
	doMissionCallback( "roundBegin" );
}

roundEnd( winner )
{
	data = spawnstruct();
	
	if ( level.teamBased )
	{
		team = "allies";
		for ( index = 0; index < level.placement[team].size; index++ )
		{
			data.player = level.placement[team][index];
			data.winner = (team == winner);
			data.place = index;

			doMissionCallback( "roundEnd", data );
		}
		team = "axis";
		for ( index = 0; index < level.placement[team].size; index++ )
		{
			data.player = level.placement[team][index];
			data.winner = (team == winner);
			data.place = index;

			doMissionCallback( "roundEnd", data );
		}
	}
	else
	{
		for ( index = 0; index < level.placement["all"].size; index++ )
		{
			data.player = level.placement["all"][index];
			data.winner = (isdefined( winner ) && isPlayer( winner ) && (data.player == winner));
			data.place = index;

			doMissionCallback( "roundEnd", data );
		}		
	}
}

doMissionCallback( callback, data )
{
	if ( !mayProcessChallenges() )
		return;
	
	if ( getDvarInt( "disable_challenges" ) > 0 )
		return;
	
	if ( !isDefined( level.missionCallbacks[callback] ) )
		return;
	
	if ( isDefined( data ) ) 
	{
		for ( i = 0; i < level.missionCallbacks[callback].size; i++ )
			thread [[level.missionCallbacks[callback][i]]]( data );
	}
	else 
	{
		for ( i = 0; i < level.missionCallbacks[callback].size; i++ )
			thread [[level.missionCallbacks[callback][i]]]();
	}
}

monitorSprintDistance()
{
	level endon( "game_ended" );
	self endon( "spawned_player" );
	self endon( "death" );
	self endon( "disconnect" );
	
	while(1)
	{
		self waittill("sprint_begin");
		
		self.sprintDistThisSprint = 0;
		self thread monitorSprintTime();
		self monitorSingleSprintDistance();
		
		if ( self IsItemUnlocked( "specialty_longersprint" ) && self _hasPerk( "specialty_longersprint" ) )
			self processChallenge( "ch_longersprint_pro", int( self.sprintDistThisSprint/12) );
	}
}

monitorSingleSprintDistance()
{
	level endon( "game_ended" );
	self endon( "spawned_player" );
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "sprint_end" );
	
	prevpos = self.origin;
	while(1)
	{
		wait .1;

		self.sprintDistThisSprint += distance( self.origin, prevpos );
		prevpos = self.origin;
	}
}

monitorSprintTime()
{
	level endon( "game_ended" );
	self endon( "spawned_player" );
	self endon( "death" );
	self endon( "disconnect" );

	startTime = getTime();
	
	self waittill( "sprint_end" );
	
	sprintTime = int( getTime() - startTime );
	self incPlayerStat( "sprinttime", sprintTime );
	
	self.lastSprintEndTime = GetTime();

	//total = self getPlayerStat( "sprinttime" );
	//println( "SprintTime: ", sprintTime, " Total:", total );
}	

monitorFallDistance()
{
	self endon("disconnect");

	self.pers["midairStreak"] = 0;
	
	while(1)
	{
		if ( !isAlive( self ) )
		{
			self waittill("spawned_player");
			continue;
		}
		
		if ( !self isOnGround() )
		{
			self.pers["midairStreak"] = 0;
			highestPoint = self.origin[2];
			while( !self isOnGround() && isAlive( self ) )
			{
				if ( self.origin[2] > highestPoint )
					highestPoint = self.origin[2];
				wait .05;
			}
			self.pers["midairStreak"] = 0;

			falldist = highestPoint - self.origin[2];
			if ( falldist < 0 )
				falldist = 0;
			
			if ( falldist / 12.0 > 15 && isAlive( self ) )
				self processChallenge( "ch_basejump" );

			if ( falldist / 12.0 > 30 && !isAlive( self ) )
				self processChallenge( "ch_goodbye" );
			
			//println( "You fell ", falldist / 12.0, " feet");
		}
		wait .05;
	}
}


// TODO: Make this challenge happen after winning while being the last person on your team
lastManSD()
{
	if ( !mayProcessChallenges() )
		return;

	if ( !self.wasAliveAtMatchStart )
		return;
	
	if ( self.teamkillsThisRound > 0 )
		return;
	
	self processChallenge( "ch_lastmanstanding" );
}


monitorBombUse()
{
	self endon( "disconnect" );
	
	for ( ;; )
	{
		result = self waittill_any_return( "bomb_planted", "bomb_defused" );
		
		if ( !isDefined( result ) )
			continue;
			
		if ( result == "bomb_planted" )
		{
			self processChallenge( "ch_saboteur" );
		}
		else if ( result == "bomb_defused" )
			self processChallenge( "ch_hero" );
	}
}


monitorLiveTime()
{
	for ( ;; )
	{
		self waittill ( "spawned_player" );
		
		self thread survivalistChallenge();
	}
}

survivalistChallenge()
{
	self endon("death");
	self endon("disconnect");
	
	wait 5 * 60;
	
	if ( isDefined(self) )
		self processChallenge( "ch_survivalist" );
}


monitorStreaks()
{
	self endon ( "disconnect" );

	self.pers["airstrikeStreak"] = 0;
	self.pers["meleeKillStreak"] = 0;
	self.pers["shieldKillStreak"] = 0;

	self thread monitorMisc();

	for ( ;; )
	{
		self waittill ( "death" );
		
		self.pers["airstrikeStreak"] = 0;
		self.pers["meleeKillStreak"] = 0;
		self.pers["shieldKillStreak"] = 0;
	}
}


monitorMisc()
{
	self thread monitorMiscSingle( "destroyed_explosive" );
	self thread monitorMiscSingle( "begin_airstrike" );
	self thread monitorMiscSingle( "destroyed_car" );
	self thread monitorMiscSingle( "destroyed_helicopter" );
	self thread monitorMiscSingle( "used_uav" );
	self thread monitorMiscSingle( "used_double_uav" );
	self thread monitorMiscSingle( "used_triple_uav" );
	self thread monitorMiscSingle( "used_counter_uav" );
	self thread monitorMiscSingle( "used_directional_uav" );
	self thread monitorMiscSingle( "used_airdrop" );
	self thread monitorMiscSingle( "used_emp" );
	self thread monitorMiscSingle( "used_nuke" );
	self thread monitorMiscSingle( "crushed_enemy" );
	
	self waittill("disconnect");
	
	// make sure the threads end when we disconnect.
	// (this allows one disconnect waittill instead of 4 disconnect endons)
	self notify( "destroyed_explosive" );
	self notify( "begin_airstrike" );
	self notify( "destroyed_car" );
	self notify( "destroyed_helicopter" );
}

monitorMiscSingle( waittillString )
{
	// don't need to endon disconnect because we will get the notify we're waiting for when we disconnect.
	// avoiding the endon disconnect saves a lot of script variables (5 * 4 threads * 64 players = 1280)
	
	while(1)
	{
		self waittill( waittillString );
		
		if ( !isDefined( self ) )
			return;
		
		monitorMiscCallback( waittillString );
	}
}

monitorMiscCallback( result )
{
	assert( isDefined( result ) );
	switch( result )
	{
		case "begin_airstrike":
			self.pers["airstrikeStreak"] = 0;
		break;

		case "destroyed_explosive":		
			if ( self IsItemUnlocked( "specialty_detectexplosive" ) && self _hasPerk( "specialty_detectexplosive" ) )
				self processChallenge( "ch_detectexplosives_pro" );

			self processChallenge( "ch_backdraft" );
		break;

		case "destroyed_helicopter":
			self processChallenge( "ch_flyswatter" );
		break;

		case "destroyed_car":
			self processChallenge( "ch_vandalism" );
		break;
		
		case "crushed_enemy":
			self processChallenge( "ch_heads_up" );

			if ( isDefined( self.finalKill ) )
				self processChallenge( "ch_droppincrates" );
		break;
	}
}


healthRegenerated()
{
	if ( !isalive( self ) )
		return;
	
	if ( !mayProcessChallenges() )
		return;
	
	if ( !self rankingEnabled() )
		return;
	
	self thread resetBrinkOfDeathKillStreakShortly();
	
	self notify( "healed" );
	
	if ( isdefined( self.lastDamageWasFromEnemy ) && self.lastDamageWasFromEnemy )
	{
		// TODO: this isn't always getting incremented when i regen
		self.healthRegenerationStreak++;
		if ( self.healthRegenerationStreak >= 5 )
		{
			self processChallenge( "ch_invincible" );
		}
	}
}

resetBrinkOfDeathKillStreakShortly()
{
	self endon("disconnect");
	self endon("death");
	self endon("damage");
	
	wait 1;
	
	self.brinkOfDeathKillStreak = 0;
}

playerSpawned()
{
	self.brinkOfDeathKillStreak = 0;
	self.healthRegenerationStreak = 0;
	self.pers["MGStreak"] = 0;
}

playerDied()
{
	self.brinkOfDeathKillStreak = 0;
	self.healthRegenerationStreak = 0;
	self.pers["MGStreak"] = 0;
}

isAtBrinkOfDeath()
{
	ratio = self.health / self.maxHealth;
	return (ratio <= level.healthOverlayCutoff);
}


processChallenge( baseName, progressInc, forceSetProgress )
{
	if ( !mayProcessChallenges() )
		return;
	
	if ( level.players.size < 2 )
		return;
	
	if ( !self rankingEnabled() )
		return;
	
	if ( !isDefined( progressInc ) )
		progressInc = 1;	
	
	/#
	if ( getDvarInt( "debug_challenges" ) )
		println( "CHALLENGE PROGRESS - " + baseName + ": " + progressInc );
	#/
	
	// need to check for daily and weekly challenges as well, but don't let it get recursive
	//*if( !IsSubStr( baseName, "_daily" ) && !IsSubStr( baseName, "_weekly" ) && self isItemUnlocked("tier_90") )
	//*{
	//*	self thread processChallenge( baseName + "_daily", progressInc, forceSetProgress );
	//*	self thread processChallenge( baseName + "_weekly", progressInc, forceSetProgress );
	//*}

	missionStatus = getChallengeStatus( baseName );
	
	if ( missionStatus == 0 )
		return;
	
	// challenge already completed
	if ( missionStatus > level.challengeInfo[baseName]["targetval"].size )
		return;

	// get the current progress from the player data
	currentProgress = ch_getProgress( baseName );

	if ( isDefined( forceSetProgress ) && forceSetProgress )
	{
		newProgress = progressInc;
		assertex( newProgress >= currentProgress, "Attempted progress regression (forceSet) for challenge '" + baseName + "' - from " + currentProgress + " to " + newProgress + " for player " + self.name );
	}
	else
	{
		newProgress = currentProgress + progressInc;
		assertex( newProgress >= currentProgress, "Attempted progress regression (inc) for challenge '" + baseName + "' - from " + currentProgress + " to " + newProgress + " for player " + self.name );
	}
	

	// check whether we've completed this tier
	targetProgress = level.challengeInfo[baseName]["targetval"][missionStatus];
	if ( newProgress >= targetProgress )
	{
		reachedNewTier = true;
		newProgress = targetProgress;
		assertex( newProgress >= currentProgress, "Attempted progress regression (tiered up) for challenge '" + baseName + "' - from " + currentProgress + " to " + newProgress + " for player " + self.name );
	}
	else
	{
		reachedNewTier = false;
	}

	// defensive, don't set the progress if it would be a regression
	if ( currentProgress < newProgress )
		self ch_setProgress( baseName, newProgress );

	if ( reachedNewTier )
	{
		self thread giveRankXpAfterWait( baseName, missionStatus );
		self maps\mp\_matchdata::logChallenge( baseName, missionStatus );
		
		if ( !isDefined( self.challengesCompleted ) )
		{
			self.challengesCompleted = [];
		}
		
		//remove duplicate entries.
		chFound = false;
		foreach ( challenge in self.challengesCompleted )
		{
			if ( challenge == baseName )
				chFound = true;
		}
		
		if ( !chFound )
			self.challengesCompleted[ self.challengesCompleted.size ] = baseName;
		
		missionStatus++;
		self ch_setState( baseName, missionStatus );
		self.challengeData[baseName] = missionStatus;

		self thread maps\mp\gametypes\_hud_message::challengeSplashNotify( baseName );
	}
}

giveRankXpAfterWait( baseName, missionStatus )
{
	self endon ( "disconnect" );

	wait( 0.25 );
	self maps\mp\gametypes\_rank::giveRankXP( "challenge", level.challengeInfo[baseName]["reward"][missionStatus], undefined, undefined, baseName );
}


getMarksmanUnlockAttachment( baseName, index )
{
	return ( tableLookup( UNLOCK_TABLE_REF, 0, baseName, 4 + index ) );
}


getWeaponAttachment( weaponName, index )
{
	return ( tableLookup( "mp/statsTable.csv", 4, weaponName, 11 + index ) );
}


masteryChallengeProcess( baseWeapon )
{
	if ( tableLookup( ALL_CHALLENGES_TABLE_REF, 0 , "ch_" + baseWeapon + "_mastery", 1 ) == "" )
		return;

	progress = 0;	
	for ( index = 0; index <= 10; index++ )
	{
		attachmentName = getWeaponAttachment( baseWeapon, index );
		
		if ( attachmentName == "" )
			continue;
			
		if ( self maps\mp\gametypes\_class::isAttachmentUnlocked( baseWeapon, attachmentName ) )
			progress++;
	}
			
	processChallenge( "ch_" + baseWeapon + "_mastery", progress, true );
}


updateChallenges()
{
	self.challengeData = [];

	self endon( "disconnect" );
	
	if ( !mayProcessChallenges() )
		return;

	if ( !self IsItemUnlocked( "challenges" ) )
		return;
	
	challengeCount = 0;

	foreach ( challengeRef, levelChallengeData in level.challengeInfo )
	{
		// limit the number of these we do in a single server frame so that it doesn't cause jitter as clients join
		// with ~2500 challenges at 20Hz, processing 40 per frame should take 3.125 total seconds to complete.
		challengeCount++;
		if ( (challengeCount % 40) == 0 )
			wait( 0.05 );

		self.challengeData[challengeRef] = 0;
		
		// make sure the challenge is unlocked
		if ( !self IsItemUnlocked( challengeRef ) )
			continue;
		
		// make sure the weapon and attachment are unlocked
		if( isWeaponChallenge( challengeRef ) )
		{
			baseWeapon = getWeaponFromChallenge( challengeRef );
			if( !self IsItemUnlocked( baseWeapon ) )
				continue;

			attachment = getWeaponAttachmentFromChallenge( challengeRef );
			if( IsDefined( attachment ) )
			{
				if( !maps\mp\gametypes\_class::isAttachmentUnlocked( baseWeapon, attachment ) )
					continue;
			}
		}
		// make sure the killstreak is unlocked
		else if( isKillstreakChallenge( challengeRef ) )
		{
			killstreakName = getKillstreakFromChallenge( challengeRef );
			if( IsDefined( killstreakName ) )
			{
				if( !self GetPlayerData( "killstreakUnlocked", killstreakName ) )
					continue;
			}
		}
		else if( !isInUnlockTable( challengeRef ) )
		{
			// most challenges will not be in the unlocktable so we need to check for the tier
			filter = getChallengeFilter( challengeRef );
			if( filter != "" )
			{
				table = getChallengeTable( filter );
				if( table != "" )
				{
					tier = getTierFromTable( table, challengeRef );
					if( tier != "" )
					{
						if( !self IsItemUnlocked( tier ) )
							continue;
					}
				}
			}
		}

		if ( isDefined( levelChallengeData["requirement"] ) && !self IsItemUnlocked( levelChallengeData["requirement"] ) )
			continue;
		
		assertEx( isDefined( levelChallengeData["type"] ), "Challenge type not defined: " + challengeRef + " for player " + self.name + " from " + level.challengeInfo.size + " total challenges" );
		/*if ( levelChallengeData["type"] == CH_DAILY )
		{
			dailyRef = self getDailyRef( challengeRef );
			if( dailyRef == "" )
				continue;
		}
		else if ( levelChallengeData["type"] == CH_WEEKLY )
		{
			weeklyRef = self getWeeklyRef( challengeRef );
			if( weeklyRef == "" )
				continue;
		}*/
		
		status = ch_getState( challengeRef );
		if ( status == 0 )
		{
			ch_setState( challengeRef, 1 );
			status = 1;
		}
		
		self.challengeData[challengeRef] = status;
	}
}

isInUnlockTable( challengeName )
{
	return ( TableLookup( UNLOCK_TABLE_REF, 0, challengeName, 0 ) != "" );
}

getChallengeFilter( challengeName )
{
	return TableLookup( ALL_CHALLENGES_TABLE_REF, 0, challengeName, 5 );
}

getChallengeTable( challengeFilter )
{
	return TableLookup( CHALLENGE_TABLE_REF, 8, challengeFilter, 4 );
}

getTierFromTable( challengeTable, challengeName )
{
	return TableLookup( challengeTable, 0, challengeName, 1 );
}

isWeaponChallenge( challengeName )
{
	if( !IsDefined( challengeName ) )
		return false;

	// riot shield has different named challenges than something like ch_marksman_m4 where the weapon name is part of the challenge
	tableValue = getChallengeFilter( challengeName );
	if( IsDefined( tableValue ) && tableValue == "riotshield" )
		return true;

	// is this a weapon challenge? search the challenge name for the weapon name
	// we could do a table lookup but this is probably just as effecient for now
	tokens = StrTok( challengeName, "_" );
	for( i = 0; i < tokens.size; i++ )
	{
		concatName = tokens[i];
		if( concatName == "iw5" )
		{
			concatName = tokens[i] + "_" + tokens[ i + 1 ];
		}

		if( maps\mp\gametypes\_class::isValidPrimary( concatName, false ) || maps\mp\gametypes\_class::isValidSecondary( concatName, "specialty_null", "specialty_null", false ) )
			return true;
	}

	return false;
}

getWeaponFromChallenge( challengeRef )
{
	prefix = "ch_";
	if ( isSubStr( challengeRef, "ch_marksman_" ) )
		prefix = "ch_marksman_";
	else if ( isSubStr( challengeRef, "ch_expert_" ) )
		prefix = "ch_expert_";
	else if ( isSubStr( challengeRef, "pr_marksman_" ) )
		prefix = "pr_marksman_";
	else if ( isSubStr( challengeRef, "pr_expert_" ) )
		prefix = "pr_expert_";

	weaponName = GetSubStr( challengeRef, prefix.size, challengeRef.size );
	// now strip off the attachment
	weaponTokens = StrTok( weaponName, "_" );
	weaponName = undefined;
	if( weaponTokens[0] == "iw5" )
		weaponName = weaponTokens[0] + "_" + weaponTokens[1];
	else
		weaponName = weaponTokens[0];

	return weaponName;
}

getWeaponAttachmentFromChallenge( challengeRef )
{
	prefix = "ch_";
	if ( isSubStr( challengeRef, "ch_marksman_" ) )
		prefix = "ch_marksman_";
	else if ( isSubStr( challengeRef, "ch_expert_" ) )
		prefix = "ch_expert_";
	else if ( isSubStr( challengeRef, "pr_marksman_" ) )
		prefix = "pr_marksman_";
	else if ( isSubStr( challengeRef, "pr_expert_" ) )
		prefix = "pr_expert_";

	baseWeapon = GetSubStr( challengeRef, prefix.size, challengeRef.size );
	// now strip off the attachment
	weaponTokens = StrTok( baseWeapon, "_" );
	attachment = undefined;
	if( IsDefined( weaponTokens[2] ) && isAttachment( weaponTokens[2] ) )
		attachment = weaponTokens[2];

	return attachment;
}

isKillstreakChallenge( challengeName )
{
	if( !IsDefined( challengeName ) )
		return false;

	// look at the filter column to see if this is a killstreak challenge
	tableValue = getChallengeFilter( challengeName );
	if( IsDefined( tableValue ) && ( tableValue == "killstreaks_assault" || tableValue == "killstreaks_support" ) )
		return true;

	return false;
}

getKillstreakFromChallenge( challengeRef )
{
	prefix = "ch_";
	killstreakName = GetSubStr( challengeRef, prefix.size, challengeRef.size );

	if( killstreakName == "assault_streaks" || killstreakName == "support_streaks" )
		killstreakName = undefined;

	return killstreakName;
}

/*
	challenge_targetVal and rewardVal should cast their return values to int
*/
challenge_targetVal( tableName, refString, tierId )
{
	value = tableLookup( tableName, CH_REF_COL, refString, CH_TARGET_COL + ((tierId-1)*2) );
	return int( value );
}


challenge_rewardVal( tableName, refString, tierId )
{
	value = tableLookup( tableName, CH_REF_COL, refString, CH_REWARD_COL + ((tierId-1)*2) );
	return int( value );
}

buildChallengeTableInfo( tableName, typeId )
{
	index = 0;
	totalRewardXP = 0;

	refString = tableLookupByRow( tableName, 0, CH_REF_COL );
	assertEx( isSubStr( refString, "ch_" ) || isSubStr( refString, "pr_" ), "Invalid challenge name: " + refString + " found in " + tableName );
	for ( index = 1; refString != ""; index++ )
	{
		assertEx( isSubStr( refString, "ch_" ) || isSubStr( refString, "pr_" ), "Invalid challenge name: " + refString + " found in " + tableName );

		level.challengeInfo[refString] = [];
		level.challengeInfo[refString]["type"] = typeId;
		level.challengeInfo[refString]["targetval"] = [];
		level.challengeInfo[refString]["reward"] = [];

		for ( tierId = 1; tierId < 11; tierId++ )
		{
			targetVal = challenge_targetVal( tableName, refString, tierId );
			rewardVal = challenge_rewardVal( tableName, refString, tierId );

			if ( targetVal == 0 )
				break;

			level.challengeInfo[refString]["targetval"][tierId] = targetVal;
			level.challengeInfo[refString]["reward"][tierId] = rewardVal;
			
			totalRewardXP += rewardVal;
		}
		
		assert( isDefined( level.challengeInfo[refString]["targetval"][1] ) );

		refString = tableLookupByRow( tableName, index, CH_REF_COL );
	}

	/#
	printLn( "Added " + (index - 1) + " challenges from " + tableName );
	#/
	
	return int( totalRewardXP );
}

buildChallegeInfo()
{
	level.challengeInfo = [];

	totalRewardXP = 0;
	
	totalRewardXP += buildChallengeTableInfo( ALL_CHALLENGES_TABLE_REF, CH_REGULAR );
	//*totalRewardXP += buildChallengeTableInfo( DAILY_CHALLENGES_TABLE_REF, CH_DAILY );
	//*totalRewardXP += buildChallengeTableInfo( WEEKLY_CHALLENGES_TABLE_REF, CH_WEEKLY );
	
	/#
	printLn( "TOTAL CHALLENGE REWARD XP: " + totalRewardXP );
	#/

	tierTable = tableLookupByRow( "mp/challengeTable.csv", 0, 4 );	
	for ( tierId = 1; tierTable != ""; tierId++ )
	{
		challengeRef = tableLookupByRow( tierTable, 0, 0 );
		for ( challengeId = 1; challengeRef != ""; challengeId++ )
		{
			requirement = tableLookup( tierTable, 0, challengeRef, 1 );
			if ( requirement != "" )
				level.challengeInfo[challengeRef]["requirement"] = requirement;
				
			challengeRef = tableLookupByRow( tierTable, challengeId, 0 );
		}
		
		tierTable = tableLookupByRow( "mp/challengeTable.csv", tierId, 4 );	
	}
}

/#
verifyMarksmanChallenges()
{
}

verifyExpertChallenges()
{
}
#/

/#
completeAllChallenges( percentage )
{
	foreach ( challengeRef, challengeData in level.challengeInfo )
	{
		finalTarget = 0;
		finalTier = 0;
		for ( tierId = 1; isDefined( challengeData["targetval"][tierId] ); tierId++ )
		{
			finalTarget = challengeData["targetval"][tierId];
			finalTier = tierId + 1;
		}
		
		if ( percentage != 1.0 )
		{
			finalTarget--;
			finalTier--;
		}

		if ( self IsItemUnlocked( challengeRef ) || percentage == 1.0 )
		{		
			self setPlayerData( "challengeProgress", challengeRef, finalTarget );
			self setPlayerData( "challengeState", challengeRef, finalTier );
		}
		
		wait ( 0.05 );
	}
	
	println( "Done unlocking challenges" );
}
#/

monitorProcessChallenge()
{
	self endon( "disconnect" );
	level endon( "game_end" );
	
	for( ;; )
	{
		if( !mayProcessChallenges() )
			return;
			
		self waittill( "process", challengeName );
		self processChallenge( challengeName );
	}	
}

monitorKillstreakProgress()
{
	self endon( "disconnect" );
	level endon( "game_end" );
	
	for( ;; )
	{
		self waittill ( "got_killstreak", streakCount );
		
		//for scr_givkillstreak
		if( !isDefined( streakCount ) )
			continue;
		
		switch ( streakCount )
		{
			case 3:
				self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "3streak" ); 
				break;
			case 4:
				self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "4streak" ); 
				break;
			case 5:
				self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "5streak" ); 
				break;
			case 6:
				self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "6streak" ); 
				break;
			case 7:
				self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "7streak" ); 
				break;
			case 8:
				self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "8streak" ); 
				break;
			case 9:
				self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "9streak" ); 	
				break;
			case 10:
				self maps\mp\killstreaks\_killstreaks::giveAdrenaline( "10streak" ); 
				break;
			default:
				break;
		}
		
		if ( streakCount == 10 && self.killstreaks.size == 0 )
			self processChallenge( "ch_theloner" );		
		else if ( streakCount == 9 )
		{
			if ( isDefined( self.killstreaks[7] ) && isDefined( self.killstreaks[8] ) && isDefined( self.killstreaks[9] ) )
			{
				self processChallenge( "ch_6fears7" );
			}
		}
	}
}


monitorKilledKillstreak()
{
	self endon( "disconnect" );
	level endon( "game_end" );
	
	for( ;; )
	{
		self waittill( "destroyed_killstreak", weapon );
		
		if ( self IsItemUnlocked( "specialty_blindeye" ) && self _hasPerk( "specialty_blindeye" ) )
			self processChallenge( "ch_blindeye_pro" );

		if ( isDefined( weapon ) && weapon == "stinger_mp" )
		{
			self processChallenge( "ch_marksman_stinger" );		
			self processChallenge( "pr_marksman_stinger" );		
		}
	}	
}


genericChallenge( challengeType, value )
{
	switch ( challengeType )
	{
		case "hijacker_airdrop":
			self processChallenge( "ch_smoothcriminal" );
			break;
		case "hijacker_airdrop_mega":
			self processChallenge( "ch_poolshark" );
			break;
		case "wargasm":
			self processChallenge( "ch_wargasm" );
			break;
		case "weapon_assault":
			self processChallenge( "ch_surgical_assault" );
			break;
		case "weapon_smg":
			self processChallenge( "ch_surgical_smg" );
			break;
		case "weapon_lmg":
			self processChallenge( "ch_surgical_lmg" );
			break;
		case "weapon_sniper":
			self processChallenge( "ch_surgical_sniper" );
			break;
		case "shield_damage":
			if( !self isJuggernaut() )
				self processChallenge( "ch_shield_damage", value );
			break;
		case "shield_bullet_hits":
			if( !self isJuggernaut() )
				self processChallenge( "ch_shield_bullet", value );
			break;
		case "shield_explosive_hits":
			if( !self isJuggernaut() )
				self processChallenge( "ch_shield_explosive", value );
			break;
	}	
}

playerHasAmmo()
{
	primaryWeapons = self getWeaponsListPrimaries();	

	foreach ( primary in primaryWeapons )
	{
		if ( self GetWeaponAmmoClip( primary ) )
			return true;
			
		altWeapon = weaponAltWeaponName( primary );

		if ( !isDefined( altWeapon ) || (altWeapon == "none") )
			continue;

		if ( self GetWeaponAmmoClip( altWeapon ) )
			return true;
	}
	
	return false;
}

monitorADSTime()
{
	self endon ( "disconnect" );

	self.adsTime = 0.0;
	while( true )
	{
		if( self PlayerAds() == 1 )
		{
			self.adsTime += 0.066;
		}
		else
		{
			self.adsTime = 0.0;
		}

		wait( 0.05 );
	}
}

monitorHoldBreath()
{
	self endon ( "disconnect" );

	self.holdingBreath = false;
	while( true )
	{
		self waittill( "hold_breath" );
		self.holdingBreath = true;
		self waittill( "release_breath" );
		self.holdingBreath = false;
	}
}

monitorMantle()
{
	self endon( "disconnect" );

	self.mantling = false;
	while( true )
	{
		self waittill( "jumped" );
		prevWeaponName = self GetCurrentWeapon();
		self waittill_notify_or_timeout( "weapon_change", 1 );
		currWeaponName = self GetCurrentWeapon();
		if( currWeaponName == "none" )
			self.mantling = true;
		else
			self.mantling = false;
		
		if( self.mantling )
		{
			if( self IsItemUnlocked( "specialty_fastmantle" ) && self _hasPerk( "specialty_fastmantle" ) )
				self processChallenge( "ch_fastmantle" );

			self waittill_notify_or_timeout( "weapon_change", 1 );
			currWeaponName = self GetCurrentWeapon();
			if( currWeaponName == prevWeaponName )
				self.mantling = false;
		}
	}
}

monitorWeaponSwap()
{
	self endon( "disconnect" );

	prevWeaponName = self GetCurrentWeapon();
	while( true )
	{
		self waittill( "weapon_change", newWeaponName );

		if( newWeaponName == "none" )
			continue;

		if( newWeaponName == prevWeaponName )
			continue;

		if( isKillstreakWeapon( newWeaponName ) || isDeathStreakWeapon( newWeaponName ) )
			continue;

		if( newWeaponName == "briefcase_bomb_mp" || newWeaponName == "briefcase_bomb_defuse_mp" )
			continue;

		weaponInvType = WeaponInventoryType( newWeaponName );
		if( weaponInvType != "primary" )
			continue;

		self.lastPrimaryWeaponSwapTime = GetTime();
	}
}

monitorFlashbang()
{
	self endon( "disconnect" );

	while( true )
	{
		self waittill( "flashbang", origin, amount_distance, amount_angle, attacker );
		
		if( self == attacker )
			continue;

		self.lastFlashedTime = GetTime();
	}
}

monitorConcussion()
{
	self endon( "disconnect" );

	while( true )
	{
		self waittill( "concussed", attacker );

		if( self == attacker )
			continue;

		self.lastConcussedTime = GetTime();
	}
}

monitorMineTriggering()
{
	self endon( "disconnect" );

	while( true )
	{
		// made this very simple, if they trip a mine, claymore, ims and live the delay mine amount of time then process challenge
		self waittill_any( "triggered_mine", "triggered_claymore", "triggered_ims" );

		self thread waitDelayMineTime();
	}
}

waitDelayMineTime()
{
	self endon( "death" );
	self endon( "disconnect" );
	level endon( "game_ended" );

	// add more time to give the mine a chance to detonate and kill
	wait( level.delayMineTime + 2 );

	self processChallenge( "ch_delaymine" );
}