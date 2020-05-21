#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

init()
{
	initAwards();

	level thread onPlayerConnect();
	level thread monitorMovementDistance();
	level thread monitorEnemyDistance();
}

onPlayerConnect()
{
	for(;;)
	{
		level waittill( "connected", player );

		// Reset player awards to none
		
		if ( !isDefined( player.pers["stats"] ) )
			player.pers["stats"] = [];

		player.stats = player.pers["stats"];
		
		if ( !player.stats.size )
		{
			player setPlayerData( "round", "awardCount", 0 );

			// Initialize player stats
			foreach ( ref, award in level.awards )
			{
				if ( isDefined( level.awards[ ref ].defaultvalue ) )
					player initPlayerStat( ref, level.awards[ ref ].defaultvalue );
				else
					player initPlayerStat( ref );
			}
		}

		player.prevPos = player.origin;
		player.previousDeaths = 0;
		player.altitudePolls = 0;
		player.totalAltitudeSum = 0;
		player.usedWeapons = [];
		
		player thread onPlayerSpawned();
		player thread monitorPositionCamping();
	}
}

onPlayerSpawned()
{
	self endon( "disconnect" );

	for(;;)
	{
		self waittill( "spawned_player" );

		self thread monitorReloads();
		self thread monitorShotsFired();
		self thread monitorSwaps();
		self thread monitorExplosionsSurvived();
		self thread monitorShieldBlocks();
		self thread monitorFlashHits();
		self thread monitorStunHits();
		self thread monitorStanceTime();
	}
}

initAwards()
{
	if ( isDefined( level.initGametypeAwards ) )
		[[ level.initGametypeAwards ]]();

	// flags generated from other stats, these are not awards,
	// but are checked against for the assignment of some awards
	initAwardFlag( "10kills", 			   ::isAtleast, 10, "kills" );
	initAwardFlag( "1death", 			   ::isAtleast, 1, "deaths" );
	initAwardFlag( "nodeaths",		 	   ::isAtMost, 0, "deaths" );
	initAwardFlag( "nokills",		 	   ::isAtMost, 0, "kills" );

	// ordered in priority assigned
	// TODO: should decouple dependency processing order from order assigned
	initMultiAward( "mvp", 							"kills", "deaths" );
	initMultiAward( "punisher", 					"kills", "killstreak" );
	initMultiAward( "overkill", 					"kills", "headshots" );
	//initMultiAward( "highlander",					"10kills", "nodeaths" );
	//initThresholdAward( "kdratio10",				::isAtleast, 10, "kdratio" );
	//initDerivedAward( "killedotherteamonelife" );	
	//initDerivedAward( "finalkill" );
	//initDerivedAward( "killedotherteam" );	
	initStatAward( "kdratio", 						0, ::highestWins );
	initStatAward( "kills",							0, ::highestWins );
	initStatAward( "higherrankkills", 				0, ::highestWins );
	initStatAward( "deaths", 						0, ::lowestWithHalfPlayedTime );
	initStatAward( "killstreak",					0, ::highestWins );
	initStatAward( "headshots",						0, ::highestWins );
	initStatAward( "closertoenemies", 				0, ::highestWins );
	initStatAward( "throwingknifekills",			0, ::highestWins );
	initStatAward( "grenadekills", 					0, ::highestWins );
	initStatAward( "helicopters", 					0, ::highestWins );
	initStatAward( "airstrikes", 					0, ::highestWins );
	initStatAward( "uavs", 							0, ::highestWins );
	initStatAward( "mostmultikills",				0, ::highestWins );
	initStatAward( "multikill", 					0, ::highestWins );
	initStatAward( "knifekills", 					0, ::highestWins );
	initStatAward( "flankkills", 					0, ::highestWins );
	initStatAward( "bulletpenkills", 				0, ::highestWins );
	initStatAward( "laststandkills", 				0, ::highestWins );
	initStatAward( "laststanderkills", 				0, ::highestWins );
	initStatAward( "assists", 						0, ::highestWins );
	initStatAward( "c4kills", 						0, ::highestWins );
	initStatAward( "claymorekills", 				0, ::highestWins );
	initStatAward( "fragkills", 					0, ::highestWins );	
	initStatAward( "semtexkills", 					0, ::highestWins );
	initStatAward( "explosionssurvived",			0, ::highestWins );	
	initStatAward( "mosttacprevented",				0, ::highestWins );	
	initStatAward( "avengekills", 					0, ::highestWins );
	initStatAward( "rescues", 						0, ::highestWins );
	initStatAward( "longshots", 					0, ::highestWins );
	initStatAward( "adskills", 						0, ::highestWins );
	initStatAward( "hipfirekills", 					0, ::highestWins );
	initStatAward( "revengekills", 					0, ::highestWins );
	initStatAward( "longestlife", 					0, ::highestWins );
	initStatAward( "throwbacks", 					0, ::highestWins );
	initStatAward( "otherweaponkills", 				0, ::highestWins );
	initStatAward( "killedsameplayer",				0, ::highestWins, 2 );
	initStatAward( "mostweaponsused",				0, ::highestWins, 3 );
	initStatAward( "distancetraveled",				0, ::highestWins );
	initStatAward( "mostreloads",					0, ::highestWins );
	initStatAward( "mostswaps",						0, ::highestWins );
	initStat( "flankdeaths", 						0 );	
	//initDerivedAward( "noflankdeaths",			::isAtMostWithHalfPlayedTime, 0, "flankdeaths" );
	initStatAward( "thermalkills", 					0, ::highestWins );		
	initStatAward( "mostcamperkills",				0, ::highestWins );
	initStatAward( "fbhits",						0, ::highestWins );
	initStatAward( "stunhits",						0, ::highestWins );
	initStatAward( "scopedkills", 					0, ::highestWins );
	initStatAward( "arkills", 						0, ::highestWins );
	initStatAward( "arheadshots", 					0, ::highestWins );
	initStatAward( "lmgkills", 						0, ::highestWins );
	initStatAward( "lmgheadshots", 					0, ::highestWins );
	initStatAward( "sniperkills", 					0, ::highestWins );
	initStatAward( "sniperheadshots", 				0, ::highestWins );
	initStatAward( "shieldblocks",					0, ::highestWins );
	initStatAward( "shieldkills",					0, ::highestWins );
	initStatAward( "smgkills", 						0, ::highestWins );
	initStatAward( "smgheadshots", 					0, ::highestWins );
	initStatAward( "shotgunkills", 					0, ::highestWins );
	initStatAward( "shotgunheadshots", 				0, ::highestWins );
	initStatAward( "pistolkills", 					0, ::highestWins );
	initStatAward( "pistolheadshots", 				0, ::highestWins );
	initStatAward( "rocketkills", 					0, ::highestWins );
	initStatAward( "equipmentkills",				0, ::highestWins );
	initStatAward( "mostclasseschanged",			0, ::highestWins );
	initStatAward( "lowerrankkills", 				0, ::highestWins );
	initStatAward( "sprinttime", 					0, ::highestWins, 1 );
	initStatAward( "crouchtime",					0, ::highestWins );
	initStatAward( "pronetime",						0, ::highestWins );	
	initStatAward( "comebacks", 					0, ::highestWins );
	initStatAward( "mostshotsfired",				0, ::highestWins );
	initStatAward( "timeinspot",					0, ::highestWins );	
	//*initStatAward( "killcamtimewatched",			0, ::highestWins );
	initStatAward( "greatestavgalt",				0, ::highestWins );
	initStatAward( "leastavgalt",					9999999, ::lowestWins );
	//initStatAward( "mostcaps",					0, ::highestWins );
	initStatAward( "weaponxpearned",				0, ::highestWins );
	initStatAward( "assaultkillstreaksused",		0, ::highestWins );
	initStatAward( "supportkillstreaksused",		0, ::highestWins );
	initStatAward( "specialistkillstreaksearned",	0, ::highestWins );
	initStatAward( "killsconfirmed",				0, ::highestWins );
	initStatAward( "killsdenied",					0, ::highestWins );
	initStatAward( "holdingteamdefenderflag",		0, ::highestWins );
	initStatAward( "damagedone",					0, ::highestWins );
	initStatAward( "damagetaken",					0, ::lowestWins );

	// Offline/private match only awards
	if ( !matchMakingGame() )
	{
		//*initStatAward( "killcamskipped",	0, ::highestWins );	
		initStatAward( "killsteals",		0, ::highestWins );
		if ( !getGametypeNumLives() )
			initStatAward( "deathstreak", 	0, ::highestWins );
		initStatAward( "shortestlife", 		9999999, ::lowestWins );
		initStatAward( "suicides", 			0, ::highestWins );
		initStatAward( "mostff",			0, ::highestWins );
		initStatAward( "shotgundeaths", 	0, ::highestWins );
		initStatAward( "shielddeaths",		0, ::highestWins );
		initStatAward( "flankdeaths", 		0, ::highestWins ); // sets the process property of the "stat only" init above
		//initMultiAward( "participant", 		   "nokills", "1death" );
		//initMultiAward( "afk", 				   "nokills", "nodeaths" );

		// special case post process award
		//initDerivedAward( "noawards" );
	}
}

initBaseAward( ref )
{
	assert( isDefined( ref ) );

	level.awards[ ref ] = spawnStruct();
	level.awards[ ref ].winners = [];
	level.awards[ ref ].exclusive = true; // For now just make all awards exclusive
}

initAwardProcess( ref, process, var1, var2 )
{
	if ( isDefined( process ) )
		level.awards[ ref ].process = process;

	if ( isDefined( var1 ) )
		level.awards[ ref ].var1 = var1;

	if ( isDefined( var2 ) )
		level.awards[ ref ].var2 = var2;
}

initStat( ref, defaultvalue )
{
	initBaseAward( ref );
	level.awards[ ref ].defaultvalue = defaultvalue;
	level.awards[ ref ].type = "stat";
}

initStatAward( ref, defaultvalue, process, var1, var2 )
{
	initBaseAward( ref );
	initAwardProcess( ref, process, var1, var2 );
	level.awards[ ref ].defaultvalue = defaultvalue;
	level.awards[ ref ].type = "stat";
}

initDerivedAward( ref, process, var1, var2 )
{
	initBaseAward( ref );
	initAwardProcess( ref, process, var1, var2 );
	level.awards[ ref ].type = "derived";
}

initAwardFlag( ref, process, var1, var2 )
{
	initBaseAward( ref );
	initAwardProcess( ref, process, var1, var2 );
	level.awards[ ref ].type = "flag";
}

initMultiAward( ref, award1_ref, award2_ref )
{
	assert( isDefined( award1_ref ) );
	assert( isDefined( award2_ref ) );

	initBaseAward( ref );
	level.awards[ ref ].award1_ref = award1_ref;
	level.awards[ ref ].award2_ref = award2_ref;
	level.awards[ ref ].type = "multi";
}

initThresholdAward( ref, process, var1, var2 )
{
	initBaseAward( ref );
	initAwardProcess( ref, process, var1, var2 );
	level.awards[ ref ].type = "threshold";
}

setMatchRecordIfGreater( ref )
{
	playerValue = self getPlayerStat( ref );
	playerTime = self getPlayerStatTime( ref );
	recordValue = getAwardRecord( ref );
	recordTime = getAwardRecordTime( ref );

	if ( !IsDefined( recordValue ) || ( playerValue > recordValue ) )
	{
		clearAwardWinners( ref );
		addAwardWinner( ref, self.clientid );
		setAwardRecord( ref, playerValue, playerTime );
	}
	else if ( playerValue == recordValue )
	{
		if ( isAwardExclusive( ref ) )
		{				
			if ( !IsDefined( recordTime ) || ( playerTime < recordTime ) )
			{
				clearAwardWinners( ref );
				addAwardWinner( ref, self.clientid );
				setAwardRecord( ref, playerValue, playerTime );
			}
		}
		else
			addAwardWinner( ref, self.clientid );
	}
}

setMatchRecordIfLower( ref )
{
	playerValue = self getPlayerStat( ref );
	playerTime = self getPlayerStatTime( ref );
	recordValue = getAwardRecord( ref );
	recordTime = getAwardRecordTime( ref );

	if ( !IsDefined( recordValue ) || ( playerValue < recordValue ) )
	{
		clearAwardWinners( ref );
		addAwardWinner( ref, self.clientid );
		setAwardRecord( ref, playerValue, playerTime );
	}
	else if ( playerValue == recordValue )
	{
		if ( isAwardExclusive( ref ) )
		{				
			if ( !IsDefined( recordTime ) || ( playerTime < recordTime ) )
			{
				clearAwardWinners( ref );
				addAwardWinner( ref, self.clientid );
				setAwardRecord( ref, playerValue, playerTime );
			}
		}
		else
			addAwardWinner( ref, self.clientid );
	}
}

getDecodedRatio( value )
{
	loVal = getRatioLoVal( value );
	hiVal = getRatioHiVal( value );
	
	if ( !loVal )
		return ( hiVal + 0.001 ); // favor the "n:0" case
		
	return ( hiVal / loVal );	
}

setPersonalBestIfGreater( ref )
{
	recordValue = self getPlayerData( "bests", ref );
	playerValue = self getPlayerStat( ref );

    if ( recordValue == 0 || ( playervalue > recordValue ) )
    {
	    playerValue = getFormattedValue( ref, playerValue );
	    self setPlayerData( "bests", ref, playerValue );
    }
}

setPersonalBestIfLower( ref )
{
	recordvalue = self getPlayerData( "bests", ref );
	playervalue = self getPlayerStat( ref );

	if ( recordValue == 0 || ( playervalue < recordvalue ) )
	{
		playerValue = getFormattedValue( ref, playerValue );
		self setPlayerData( "bests", ref, playerValue );
	}
}

incPlayerRecord( ref )
{
	recordValue = self getPlayerData( "awards", ref );
	self setPlayerData( "awards", ref, recordValue + 1 );
	
	/#
	if ( !isDefined( self.statprint ) )
		self.statprint = [];

	if ( hasDisplayValue( ref ) )
		value = self getPlayerStat( ref );
	else
		value = true;

	stat = spawnstruct();
	stat.ref = ref;
	stat.value = value;

	self.statprint[ self.statprint.size ] = stat;
	#/
}

addAwardWinner( ref, clientid )
{
	foreach ( winner in level.awards[ ref ].winners )
	{
		if ( winner == clientid )
			return;
	}

	level.awards[ ref ].winners[ level.awards[ ref ].winners.size ] = clientid;
}

getAwardWinners( ref )
{
	return level.awards[ ref ].winners;
}

clearAwardWinners( ref )
{
	level.awards[ ref ].winners = [];
}

setAwardRecord( ref, value, time )
{
	level.awards[ ref ].value = value;
	level.awards[ ref ].time = time;
}

getAwardRecord( ref )
{
	return level.awards[ ref ].value;
}

getAwardRecordTime( ref )
{
	return level.awards[ ref ].time;
}

// does this work correctly for roundbased games?
assignAwards()
{
	println( "Awards: Assigning" );
	
	// Special case handling of awards which get stat values updated at the end of a game
	foreach ( player in level.players )
	{
		kills = player getPlayerStat( "kills" );
		deaths = player getPlayerStat( "deaths" );

		if ( deaths == 0 )
			deaths = 1;
		
		player setPlayerStat( "kdratio", ( kills / deaths ) );

		if ( isAlive( player ) )
		{
			timeAlive = getTime() - player.spawnTime;
			player setPlayerStatIfGreater( "longestlife", timeAlive );
		}
	}

	// process end of match stats
	foreach ( ref, award in level.awards )
	{
		if ( !isDefined( level.awards[ ref ].process ) )
			continue;
			
		process = level.awards[ ref ].process;
		var1 = level.awards[ ref ].var1;
		var2 = level.awards[ ref ].var2;

		if ( isDefined( var1 ) && isDefined( var2 ) )
			[[ process ]]( ref, var1, var2 );
		else if ( isDefined( var1 ) )
			[[ process ]]( ref, var1 );
		else
			[[ process ]]( ref );
	}

	// set multi-award winners
	foreach ( ref, award in level.awards )
	{
		if ( !isMultiAward( ref ) )
			continue;
		
		award1_ref = level.awards[ ref ].award1_ref;
		award2_ref = level.awards[ ref ].award2_ref;
		award1_winners = getAwardWinners( award1_ref );
		award2_winners = getAwardWinners( award2_ref );

		if ( !isDefined( award1_winners ) || !isDefined( award2_winners ) )
			continue;
			
		foreach ( winner1 in award1_winners )
		{
			foreach ( winner2 in award2_winners )
			{
				if ( winner1 == winner2 )
				{
					addAwardWinner( ref, winner1 );
					player = playerForClientId( winner1 );
					stat1 = player getPlayerStat( award1_ref );
					stat2 = player getPlayerStat( award2_ref );
					player setPlayerStat( ref, encodeRatio( stat1, stat2 ) );
				}
			}
		}
	}

	// assign awards
	foreach ( ref, award in level.awards )
	{
		if ( !isAwardFlag( ref ) )
			assignAward( ref );
	}

	/* assign "noawards" winners
	if ( !matchMakingGame() )
	{
		foreach ( player in level.players )
		{
			awardCount = player getPlayerData( "round", "awardCount" );
			if ( awardCount == 0 )
				player giveAward( "noawards" );
		}
	}*/

	foreach ( player in level.players )
	{
		awardCount = player getPlayerData( "round", "awardCount" );

		println( "Awards: [", player.name, "] won ", awardCount, " awards" );
		
		for ( i = 0; (i < awardCount && i < 3 ); i++ )
		{
			award = player getPlayerData( "round", "awards", i, "award" );
			value = player getPlayerData( "round", "awards", i, "value" );

			println( "Awards: [", player.name, "][", i, "] ", award, " ", value );
		}
		
		/#
		if ( isDefined( player.statprint ) )
		{
			for ( i = 3; i < player.statprint.size; i++ )
				println( "Awards: [", player.name, "][", i, "] ", player.statprint[i].ref, " ", player.statprint[i].value );
		}
		#/
	}
	
	println( "Awards: Finished assigning" );
}

assignAward( ref )
{
	winners = getAwardWinners( ref );
	if ( !isDefined( winners ) )
		return;
		
	foreach ( winner in winners )
	{
		foreach ( player in level.players )
		{
			if ( player.clientid == winner )
			{
				player giveAward( ref );
				// /# player writeAwardLine( ref ); #/
			}
		}
	}
}

getAwardType( ref )
{
	if ( isDefined( level.awards[ ref ].type ) )
		return level.awards[ ref ].type;
	else
		return "none";
}

isMultiAward( ref )
{
	return ( getAwardType( ref ) == "multi" );
}

isStatAward( ref )
{
	return ( getAwardType( ref ) == "stat" );
}

isThresholdAward( ref )
{
	return ( getAwardType( ref ) == "threshold" );
}

isAwardFlag( ref )
{
	return ( getAwardType( ref ) == "flag" );
}

isAwardExclusive( ref )
{
	if ( isDefined( level.awards[ ref ].exclusive ) )
		return level.awards[ ref ].exclusive;
	else
		return true;
}

hasDisplayValue( ref )
{
	type = getAwardType( ref );
	switch ( type )
	{
		case "derived":
			hasDisplayValue = false;
			break;
		case "stat":
		case "multi":
		default:
			hasDisplayValue = true;
			break;					
	}
	
	return ( hasDisplayValue );
}

giveAward( ref )
{
	awardCount = self getPlayerData( "round", "awardCount" );
	self incPlayerRecord( ref );

	if ( hasDisplayValue( ref ) )
	{
		if ( isStatAward( ref ) )
			assertex( self getPlayerStat( ref ) == getAwardRecord( ref ), "Ref is: " + ref + ", PlayerStat is: " + self getPlayerStat( ref ) + ", MatchRecord is: " + getAwardRecord( ref ) );
		
		value = self getPlayerStat( ref );
	}
	else
		value = true;

	value = getFormattedValue( ref, value );

	if ( awardCount < 5 )
	{	
		self setPlayerData( "round", "awards", awardCount, "award", ref );
		self setPlayerData( "round", "awards", awardCount, "value", value );
	}
	
	awardCount++;
	self SetPlayerData( "round", "awardCount", awardCount );
	self maps\mp\_matchdata::logAward( ref );

	if ( awardCount == 1 )
		maps\mp\_highlights::giveHighlight( ref, value );
}

getFormattedValue( ref, value )
{
	awardFormat = tableLookup( "mp/awardTable.csv", 1, ref, 7 );
	switch ( awardFormat )
	{
		case "float":
			value = limitDecimalPlaces( value, 2 );
			value = value * 100;
			break;
		case "ratio":
		case "multi":
		case "count":
		case "time":
		case "distance":
		case "none":
		default:
			break;					
	}

	value = int( value );
	return ( value );
}

highestWins( ref, minAwardable )
{
	foreach ( player in level.players )
	{
		if ( player statValueChanged( ref ) && ( !isDefined( minAwardable ) || player getPlayerStat( ref ) >= minAwardable ) )
		{
			player setMatchRecordIfGreater( ref );
			if ( !isAwardFlag( ref ) )
				player setPersonalBestIfGreater( ref );
		}
	}
}

lowestWins( ref, maxAwardable)
{
	foreach ( player in level.players )
	{
		if ( player statValueChanged( ref ) && ( !isDefined( maxAwardable ) || player getPlayerStat( ref ) <= maxAwardable ) )
		{
			player setMatchRecordIfLower( ref );	
			if ( !isAwardFlag( ref ) )
				player setPersonalBestIfLower( ref );
		}
	}
}

lowestWithHalfPlayedTime( ref )
{
	gameLength = getTimePassed() / 1000;
	halfGameLength = gameLength * 0.5;

	foreach ( player in level.players )
	{
		// hasSpawned check is required or players who pick a team and never spawn can win awards
		if ( player.hasSpawned && player.timePlayed["total"] >= halfGameLength )
		{
			player setMatchRecordIfLower( ref );
			if ( !isAwardFlag( ref ) )
				player setPersonalBestIfLower( ref );
		}
	}
}

statValueChanged( ref )
{
	playervalue = self getPlayerStat( ref );
	defaultvalue = level.awards[ ref ].defaultvalue;

	if ( playervalue == defaultvalue )
		return false;
	else
		return true;
}


isAtLeast( ref, minimum, checkAwardRef )
{
	foreach ( player in level.players )
	{
		playerValue = player getPlayerStat( checkAwardRef );
		checkValue = playerValue;

		if ( checkValue >= minimum )
			addAwardWinner( ref, player.clientid );

		// TODO: Instead of copying the value, reference the other stat directly
		if ( isThresholdAward( ref ) || isAwardFlag( ref ) )
			player setPlayerStat( ref, playerValue );
	}
}


isAtMost( ref, maximum, award_ref )
{
	foreach ( player in level.players )
	{
		playerValue = player getPlayerStat( award_ref );

		if ( playerValue <= maximum )
			addAwardWinner( ref, player.clientid );
	}
}


isAtMostWithHalfPlayedTime( ref, maximum, award_ref )
{
	gameLength = getTimePassed() / 1000;
	halfGameLength = gameLength * 0.5;
	
	foreach ( player in level.players )
	{
		// hasSpawned check is required or players who pick a team and never spawn can win awards
		if ( player.hasSpawned && player.timePlayed["total"] >= halfGameLength )
		{
			playerValue = player getPlayerStat( award_ref );
	
			if ( playerValue <= maximum )
				addAwardWinner( ref, player.clientid );
		}
	}
}


setRatio( ref, award1_ref, award2_ref )
{
	foreach ( player in level.players )
	{
		playerValue1 = player getPlayerStat( award1_ref );
		playerValue2 = player getPlayerStat( award2_ref );

		if ( playerValue2 == 0 )
			player setPlayerStat( ref, playerValue1 );
		else
		{
			ratio = playerValue1 / playerValue2;
			player setPlayerStat( ref, ratio );
		}
	}
}

getKillstreakAwardRef( streakName )
{
	switch( streakName )
	{
	case "uav":
	case "uav_support":
	case "double_uav":
	case "triple_uav":
	case "counter_uav":
		return "uavs";
	case "airstrike":
	case "precision_airstrike":
	case "stealth_airstrike":
	case "harrier_airstrike":
	case "super_airstrike":
		return "airstrikes";
	case "helicopter":
	case "helicopter_minigun":
	case "helicopter_mk19":
	case "helicopter_blackbox":
	case "helicopter_flares":
	case "littlebird_support":
	case "littlebird_flock":
		return "helicopters";
	default:
		return undefined;
	}
}

monitorReloads()
{
	level endon( "game_ended" );
	self endon( "spawned_player" );
	self endon( "death" );
	self endon( "disconnect" );

	for ( ;; )
	{
		self waittill( "reload" );
		self incPlayerStat( "mostreloads", 1 );
	}
}

monitorShotsFired()
{
	level endon( "game_ended" );
	self endon( "spawned_player" );
	self endon( "death" );
	self endon( "disconnect" );

	for ( ;; )
	{
		self waittill( "weapon_fired" );
		self incPlayerStat( "mostshotsfired", 1 );
	}
}

monitorSwaps()
{
	level endon( "game_ended" );
	self endon( "spawned_player" );
	self endon( "death" );
	self endon( "disconnect" );

	lastWeapon = "none"; 

	for ( ;; )
	{
		self waittill( "weapon_change", weapon );
		
		if ( lastWeapon == weapon )
			continue;
		
		if ( weapon == "none" )
			continue;
		
		if ( ! maps\mp\gametypes\_weapons::isPrimaryWeapon( weapon ) )
			continue;
		
		lastWeapon = weapon;
		
		self incPlayerStat( "mostswaps", 1 );
		
		alreadyUsed = false;
		
		//creates an array of weapons used
		foreach( usedWeapon in self.usedWeapons )
		{
			if ( weapon == usedWeapon )
			{
				alreadyUsed = true;
				break;
			}
		}
	
		if ( !alreadyUsed )
		{
			self.usedWeapons[self.usedWeapons.size] = weapon;
			self incPlayerStat( "mostweaponsused", 1 );
		}
	}
}


monitorMovementDistance()
{
	level endon( "game_ended" );
	self endon( "disconnect" );

	for ( ;; )
	{
		foreach ( player in level.players )
		{
			if ( !isAlive( Player ) )
				continue;

			if ( player.deaths != player.previousDeaths )
			{
				player.prevPos = player.origin;
				player.previousDeaths = player.deaths;
			}

			distanceTraveled = Distance( player.origin, player.prevPos );
			player incPlayerStat( "distancetraveled", distanceTraveled );

			player.prevPos = player.origin;
			
			player.altitudePolls++;
			player.totalAltitudeSum += player.origin[2];
			avgAltitude = player.totalAltitudeSum / player.altitudePolls;
			player setPlayerStat( "leastavgalt", avgAltitude );
			player setPlayerStat( "greatestavgalt", avgAltitude );
			
			wait( 0.05 );
		}
		wait( 0.05 );
	}
}

monitorPositionCamping()
{
	level endon( "game_ended" );
	self endon( "disconnect" );

	self.lastCampChecked = getTime();
	self.positionArray = [];
	
	CAMPTHRESHOLD = 512;
	
	for ( ;; )
	{	
		if ( !isAlive( self ) )
		{
			wait( 0.5 );
			self.lastCampChecked = getTime();
			self.positionArray = [];	
			continue;
		}
		self.positionArray[self.positionArray.size] = self.origin;
				
		if ( ( getTime() - self.lastCampChecked ) >= 15000 )
		{
			if ( Distance( self.positionArray[0], self.origin ) < CAMPTHRESHOLD && Distance( self.positionArray[1], self.positionArray[0] ) < CAMPTHRESHOLD )
			{
				timeCamping = getTime() - self.lastCampChecked;
				self incPlayerStat( "timeinspot", timeCamping  );
			}
			
			self.positionArray = [];
			
			self.lastCampChecked = getTime();
		}
		wait( 5 );
	}		
}

encodeRatio( value1, value2 )
{
	return ( value1 + (value2 << 16) );
}

getRatioHiVal( value )
{
	return (value & 65535);
}

getRatioLoVal( value )
{
	return (value >> 16);
}

monitorEnemyDistance()
{
	level endon( "game_ended" );
	self endon( "disconnect" );
	
	while( level.players.size < 3 )
		wait( 1 );
	
	prof_begin( "EnemyDistance" );
	for ( ;; )
	{
		foreach ( player in level.players )
		{
			
			if ( !isdefined( player ) )
				continue;
				
			if ( player.team == "spectator" )
				continue;
			
			if ( !isAlive( player ) )
				continue;
			
			sortedPlayersByDistance = SortByDistance( level.players, player.origin );
			
			if( !sortedPlayersByDistance.size )
			{
				wait( 0.05 );
				continue;
			}
			
			if ( sortedPlayersByDistance.size < 2 )
			{
				wait( 0.05 );
				continue;
			}
			
			if ( sortedPlayersByDistance[1].team != player.team )
				player incPlayerStat( "closertoenemies", 0.05 );
			
			wait( 0.05 );
		}
		
		wait( 0.05);
	}

	prof_end( "EnemyDistance" );	
}

monitorExplosionsSurvived()
{
	level endon( "game_ended" );
	self endon( "spawned_player" );
	self endon( "death" );
	self endon( "disconnect" );
	
	for(;;)
	{
		self waittill( "survived_explosion", attacker );
		
		// don't let the player boost themselves
		if( IsDefined( attacker ) && IsPlayer( attacker ) && self == attacker )
			continue;

		self incPlayerStat( "explosionssurvived", 1 );
		wait( 0.05 );
	}
}

monitorShieldBlocks()
{
	level endon( "game_ended" );
	self endon( "spawned_player" );
	self endon( "death" );
	self endon( "disconnect" );
	
	for(;;)
	{
		self waittill( "shield_blocked" );
		self incPlayerStat( "shieldblocks", 1 );
		wait( 0.05 );
	}
}

monitorFlashHits()
{
	level endon( "game_ended" );
	self endon( "spawned_player" );
	self endon( "death" );
	self endon( "disconnect" );
	
	for(;;)
	{
		self waittill( "flash_hit" );
		self incPlayerStat( "fbhits", 1 );
		wait( 0.05 );
	}
}

monitorStunHits()
{
	level endon( "game_ended" );
	self endon( "spawned_player" );
	self endon( "death" );
	self endon( "disconnect" );
	
	for(;;)
	{
		self waittill( "stun_hit" );
		self incPlayerStat( "stunhits", 1 );
		wait( 0.05 );
	}
}

//this approximates a players time spent in crouch or prone.
monitorStanceTime()
{
	level endon( "game_ended" );
	self endon( "spawned_player" );
	self endon( "death" );
	self endon( "disconnect" );
	
	for(;;)
	{
		if ( self GetStance() == "crouch" )
			self incPlayerStat( "crouchtime", 500 );
		else if ( self GetStance() == "prone" )
			self incPlayerStat( "pronetime", 500 );
		
		wait( 0.5 );
	}
}	