#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

init()
{
	if ( !isDefined( game["gamestarted"] ) )
	{
		//setMatchDataDef( "mp/matchdata_" + level.gametype + ".def" );
		setMatchDataDef( "mp/matchdata.def" );
		setMatchData( "map", level.script );
		if( level.hardcoremode )
		{
			tmp = level.gametype + " hc";
			setMatchData( "gametype", tmp );
		}
		else
		{
			setMatchData( "gametype", level.gametype );
		}
		setMatchData( "buildVersion", getBuildVersion() );
		setMatchData( "buildNumber", getBuildNumber() );
		setMatchData( "dateTime", getSystemTime() );
		setMatchDataID();
	}

	level.MaxLives = 285; // must match MaxKills in matchdata definition
	level.MaxNameLength = 26; // must match Player xuid size in clientmatchdata definition
	level.MaxEvents = 150;
	level.MaxKillstreaks = 125;
	level.MaxLogClients = 30;
	level.MaxNumChallengesPerPlayer = 10;
	level.MaxNumAwardsPerPlayer = 10;
	
	level thread gameEndListener();
	level thread endOfGameSummaryLogger();
}

getMatchDateTime()
{
	return GetMatchData( "dateTime" );
}

logKillstreakEvent( event, position )
{
	assertEx( isPlayer( self ), "self is not a player: " + self.code_classname );
	
	if ( !canLogClient( self ) || !canLogKillstreak() )
		return;

	eventId = getMatchData( "killstreakCount" );
	setMatchData( "killstreakCount", eventId+1 );
	
	setMatchData( "killstreaks", eventId, "eventType", event );
	setMatchData( "killstreaks", eventId, "player", self.clientid );
	setMatchData( "killstreaks", eventId, "eventTime", getTime() );	
	setMatchData( "killstreaks", eventId, "eventPos", 0, int( position[0] ) );	
	setMatchData( "killstreaks", eventId, "eventPos", 1, int( position[1] ) );	
	setMatchData( "killstreaks", eventId, "eventPos", 2, int( position[2] ) );	
}


logGameEvent( event, position )
{
	assertEx( isPlayer( self ), "self is not a player: " + self.code_classname );

	if ( !canLogClient( self ) || !canLogEvent() )
		return;
		
	eventId = getMatchData( "eventCount" );
	setMatchData( "eventCount", eventId+1 );
	
	setMatchData( "events", eventId, "eventType", event );
	setMatchData( "events", eventId, "player", self.clientid );
	setMatchData( "events", eventId, "eventTime", getTime() );	
	setMatchData( "events", eventId, "eventPos", 0, int( position[0] ) );	
	setMatchData( "events", eventId, "eventPos", 1, int( position[1] ) );	
	setMatchData( "events", eventId, "eventPos", 2, int( position[2] ) );	
}


logKillEvent( lifeId, eventRef )
{
	if ( !canLogLife( lifeId ) )
		return;

	setMatchData( "lives", lifeId, "modifiers", eventRef, true );
}


logMultiKill( lifeId, multikillCount )
{
	if ( !canLogLife( lifeId ) )
		return;

	setMatchData( "lives", lifeId, "multikill", multikillCount );
}


logPlayerLife( lifeId )
{
	if ( !canLogClient( self ) || !canLogLife( lifeId ) )
		return;
		
	setMatchData( "lives", lifeId, "player", self.clientid );
	setMatchData( "lives", lifeId, "spawnPos", 0,  int( self.spawnPos[0] ) );
	setMatchData( "lives", lifeId, "spawnPos", 1,  int( self.spawnPos[1] ) );
	setMatchData( "lives", lifeId, "spawnPos", 2,  int( self.spawnPos[2] ) );
	setMatchData( "lives", lifeId, "wasTacticalInsertion", self.wasTI );
	setMatchData( "lives", lifeId, "team", self.team );
	setMatchData( "lives", lifeId, "spawnTime", self.spawnTime );	
	setMatchData( "lives", lifeId, "duration", getTime() - self.spawnTime );
		
	self logLoadout( lifeId );
}

logPlayerXP( xp, xpName  )
{
	if ( !canLogClient( self ) )
		return;
	setMatchData( "players", self.clientid, xpName, xp );
}


logLoadout( lifeId )
{
	if ( !canLogClient( self ) || !canLogLife( lifeId ) || self.curClass == "gamemode" )
		return;

	class = self.curClass;

	if ( class == "copycat" )
	{
		clonedLoadout = self.pers["copyCatLoadout"];

		loadoutPrimary = clonedLoadout["loadoutPrimary"];
		loadoutPrimaryAttachment = clonedLoadout["loadoutPrimaryAttachment"];
		loadoutPrimaryAttachment2 = clonedLoadout["loadoutPrimaryAttachment2"] ;
		loadoutPrimaryCamo = clonedLoadout["loadoutPrimaryCamo"];
		loadoutPrimaryBuff = clonedLoadout["loadoutPrimaryBuff"];
		loadoutSecondary = clonedLoadout["loadoutSecondary"];
		loadoutSecondaryAttachment = clonedLoadout["loadoutSecondaryAttachment"];
		loadoutSecondaryAttachment2 = clonedLoadout["loadoutSecondaryAttachment2"];
		loadoutSecondaryCamo = clonedLoadout["loadoutSecondaryCamo"];
		loadoutSecondaryBuff = clonedLoadout["loadoutSecondaryBuff"];
		loadoutEquipment = clonedLoadout["loadoutEquipment"];
		loadoutPerk1 = clonedLoadout["loadoutPerk1"];
		loadoutPerk2 = clonedLoadout["loadoutPerk2"];
		loadoutPerk3 = clonedLoadout["loadoutPerk3"];
		loadoutOffhand = clonedLoadout["loadoutOffhand"];
		loadoutDeathStreak = clonedLoadout["loadoutDeathstreak"];
		loadoutStreakType = clonedLoadout["loadoutStreakType"];
		loadoutKillstreak1 = clonedLoadout["loadoutKillstreak1"];
		loadoutKillstreak2 = clonedLoadout["loadoutKillstreak2"];
		loadoutKillstreak3 = clonedLoadout["loadoutKillstreak3"];
	}
	else if( isSubstr( class, "custom" ) )
	{
		class_num = maps\mp\gametypes\_class::getClassIndex( class );

		loadoutPrimary = maps\mp\gametypes\_class::cac_getWeapon( class_num, 0 );
		loadoutPrimaryAttachment = maps\mp\gametypes\_class::cac_getWeaponAttachment( class_num, 0 );
		loadoutPrimaryAttachment2 = maps\mp\gametypes\_class::cac_getWeaponAttachmentTwo( class_num, 0 );

		loadoutSecondary = maps\mp\gametypes\_class::cac_getWeapon( class_num, 1 );
		loadoutSecondaryAttachment = maps\mp\gametypes\_class::cac_getWeaponAttachment( class_num, 1 );
		loadoutSecondaryAttachment2 = maps\mp\gametypes\_class::cac_getWeaponAttachmentTwo( class_num, 1 );

		loadoutOffhand = maps\mp\gametypes\_class::cac_getOffhand( class_num );

		loadoutEquipment = maps\mp\gametypes\_class::cac_getPerk( class_num, 0 );
		loadoutPerk1 = maps\mp\gametypes\_class::cac_getPerk( class_num, 1 );
		loadoutPerk2 = maps\mp\gametypes\_class::cac_getPerk( class_num, 2 );
		loadoutPerk3 = maps\mp\gametypes\_class::cac_getPerk( class_num, 3 );
		loadoutStreakType = maps\mp\gametypes\_class::cac_getPerk( class_num, 5 );
		loadoutDeathStreak = maps\mp\gametypes\_class::cac_getDeathstreak( class_num );
		loadoutPrimaryBuff = maps\mp\gametypes\_class::cac_getWeaponBuff( class_num, 0 );
		loadoutSecondaryBuff = maps\mp\gametypes\_class::cac_getWeaponBuff( class_num, 1 );
		loadoutKillstreak1 = maps\mp\gametypes\_class::cac_getKillstreak( class_num, loadoutStreakType, 0 );
		loadoutKillstreak2 = maps\mp\gametypes\_class::cac_getKillstreak( class_num, loadoutStreakType, 1 );
		loadoutKillstreak3 = maps\mp\gametypes\_class::cac_getKillstreak( class_num, loadoutStreakType, 2 );
	}
	else
	{
		class_num = maps\mp\gametypes\_class::getClassIndex( class );
		
		loadoutPrimary = maps\mp\gametypes\_class::table_getWeapon( level.classTableName, class_num, 0 );
		loadoutPrimaryAttachment = maps\mp\gametypes\_class::table_getWeaponAttachment( level.classTableName, class_num, 0 , 0);
		loadoutPrimaryAttachment2 = maps\mp\gametypes\_class::table_getWeaponAttachment( level.classTableName, class_num, 0, 1 );

		loadoutSecondary = maps\mp\gametypes\_class::table_getWeapon( level.classTableName, class_num, 1 );
		loadoutSecondaryAttachment = maps\mp\gametypes\_class::table_getWeaponAttachment( level.classTableName, class_num, 1 , 0);
		loadoutSecondaryAttachment2 = maps\mp\gametypes\_class::table_getWeaponAttachment( level.classTableName, class_num, 1, 1 );;

		loadoutOffhand = maps\mp\gametypes\_class::table_getOffhand( level.classTableName, class_num );

		loadoutEquipment = maps\mp\gametypes\_class::table_getEquipment( level.classTableName, class_num, 0 );
		loadoutPerk1 = maps\mp\gametypes\_class::table_getPerk( level.classTableName, class_num, 1 );
		loadoutPerk2 = maps\mp\gametypes\_class::table_getPerk( level.classTableName, class_num, 2 );
		loadoutPerk3 = maps\mp\gametypes\_class::table_getPerk( level.classTableName, class_num, 3 );
		loadoutStreakType = maps\mp\gametypes\_class::table_getPerk( level.classTableName, class_num, 5 );
		loadoutDeathStreak = maps\mp\gametypes\_class::table_getDeathstreak( level.classTableName, class_num );
		loadoutPrimaryBuff = maps\mp\gametypes\_class::table_getWeaponBuff( level.classTableName, class_num, 0 );
		loadoutSecondaryBuff = maps\mp\gametypes\_class::table_getWeaponBuff( level.classTableName, class_num, 1 );
		loadoutKillstreak1 = maps\mp\gametypes\_class::table_getKillstreak( level.classTableName, class_num, 1 );
		loadoutKillstreak2 = maps\mp\gametypes\_class::table_getKillstreak( level.classTableName, class_num, 2 );
		loadoutKillstreak3 = maps\mp\gametypes\_class::table_getKillstreak( level.classTableName, class_num, 3 );
	}
	
	loadoutPrimaryAttachment = validateAttachment( loadoutPrimaryAttachment );
	loadoutPrimaryAttachment2 = validateAttachment( loadoutPrimaryAttachment2 );
	loadoutSecondaryAttachment = validateAttachment( loadoutSecondaryAttachment );
	loadoutSecondaryAttachment2 = validateAttachment( loadoutSecondaryAttachment2 );
	
	setMatchData( "lives", lifeId, "primaryWeapon", loadoutPrimary );
	setMatchData( "lives", lifeId, "primaryAttachments", 0, loadoutPrimaryAttachment );
	setMatchData( "lives", lifeId, "primaryAttachments", 1, loadoutPrimaryAttachment2 );

	setMatchData( "lives", lifeId, "secondaryWeapon", loadoutSecondary );
	setMatchData( "lives", lifeId, "secondaryAttachments", 0,  loadoutSecondaryAttachment );
	setMatchData( "lives", lifeId, "secondaryAttachments", 1,  loadoutSecondaryAttachment );

	setMatchData( "lives", lifeId, "offhandWeapon", loadoutOffhand );

	setMatchData( "lives", lifeId, "equipment", loadoutEquipment );
	setMatchData( "lives", lifeId, "perks", 0, loadoutPerk1 );
	setMatchData( "lives", lifeId, "perks", 1, loadoutPerk2 );
	setMatchData( "lives", lifeId, "perks", 2, loadoutPerk3 );
	setMatchData( "lives", lifeId, "strikePackage", loadoutStreakType );
	setMatchData( "lives", lifeId, "deathstreak", loadoutDeathStreak );
	setMatchData( "lives", lifeId, "weaponBuff", 0, loadoutPrimaryBuff );
	setMatchData( "lives", lifeId, "weaponBuff", 1, loadoutSecondaryBuff );
	switch( loadoutStreakType )
	{
	case "streaktype_assault":
		setMatchData( "lives", lifeId, "assaultStreaks", 0, loadoutKillstreak1 );
		setMatchData( "lives", lifeId, "assaultStreaks", 1, loadoutKillstreak2 );
		setMatchData( "lives", lifeId, "assaultStreaks", 2, loadoutKillstreak3 );
		break;
	case "streaktype_support":
		setMatchData( "lives", lifeId, "defenseStreaks", 0, loadoutKillstreak1 );
		setMatchData( "lives", lifeId, "defenseStreaks", 1, loadoutKillstreak2 );
		setMatchData( "lives", lifeId, "defenseStreaks", 2, loadoutKillstreak3 );
		break;
	case "streaktype_specialist":
		setMatchData( "lives", lifeId, "specialistStreaks", 0, loadoutKillstreak1 );
		setMatchData( "lives", lifeId, "specialistStreaks", 1, loadoutKillstreak2 );
		setMatchData( "lives", lifeId, "specialistStreaks", 2, loadoutKillstreak3 );
		break;
	case "none":
		break;
	}
}


logPlayerDeath( lifeId, attacker, iDamage, sMeansOfDeath, sWeapon, sPrimaryWeapon, sHitLoc )
{	
	if ( !canLogClient( self ) || ( isPlayer( attacker ) && !canLogClient( attacker ) ) || !canLogLife( lifeId ) )
		return;
	
	if ( lifeId >= level.MaxLives )
		return;
	
	if ( sWeapon == "none" )
	{
		sWeaponType = "none";
		sWeaponClass = "none";
	}
	else
	{
		sWeaponType = weaponInventoryType( sWeapon );
		sWeaponClass = weaponClass( sWeapon );
	}
	
	if ( isSubstr( sWeapon, "destructible" ) )
		sWeapon = "destructible";
	
	if ( isDefined( sWeaponType ) && (sWeaponType == "primary" || sWeaponType == "altmode") && (sWeaponClass == "pistol" || sWeaponClass == "smg" || sWeaponClass == "rifle" || sWeaponClass == "spread" || sWeaponClass == "mg" || sWeaponClass == "grenade" || sWeaponClass == "rocketlauncher" || sWeaponClass == "sniper") )
	{
		sWeaponOriginal = undefined;
		
		if ( sWeaponType == "altmode" )
		{
			sWeaponOriginal = sWeapon;
			sWeapon = sPrimaryWeapon;
			
			setMatchData( "lives", lifeId, "altMode", true );
		}
		
		assertEx( isDefined(sWeapon), "No weapon defined in log player death" );
		
		weaponTokens = strTok( sWeapon, "_" );

		/#
		if ( !(weaponTokens.size > 1 && weaponTokens.size <= 4) )
		{
			PrintLn( "attacker: ", attacker );
			PrintLn( "iDamage: ", iDamage );
			PrintLn( "sMeansOfDeath: ", sMeansOfDeath );
			
			if ( isDefined( sWeaponOriginal ) )
				PrintLn( "sWeaponOriginal: ", sWeaponOriginal );
				
			PrintLn( "sWeapon: ", sWeapon );
			PrintLn( "sPrimaryWeapon: ", sPrimaryWeapon );
			PrintLn( "--------------------------------" );
			PrintLn( "sWeaponType: ", sWeaponType );
			PrintLn( "sWeaponClass: ", sWeaponClass );
			PrintLn( "--------------------------------" );
			PrintLn( "weaponTokens.size: ", weaponTokens.size );

			tokenCount = 0;
			foreach ( token in weaponTokens )
			{
				PrintLn( "weaponTokens[", tokenCount, "]: ", weaponTokens[tokenCount] );
				tokenCount++;
			}
		}
		#/
		
		if ( weaponTokens[0] == "iw5" )
		{
			assert( weaponTokens.size > 1 );
			
			baseMW5WeaponName = weaponTokens[0] + "_" + weaponTokens[1];
			
			/*
			if ( isSubStr( baseMW5WeaponName, "akimbo" ) )
			{
				baseMW5WeaponName = fixAkimboString( baseMW5WeaponName, false );
			}
			*/
					
			setMatchData( "lives", lifeId, "weapon", baseMW5WeaponName );
			
			if( isDefined( weaponTokens[3] ) && isSubStr( weaponTokens[3], "scope" ) && isSubStr( weaponTokens[3], "vz" ) )
					weaponTokens[3] = "vzscope";
					
			if( isDefined( weaponTokens[4] ) && isSubStr( weaponTokens[4], "scope" ) && isSubStr( weaponTokens[4], "vz" ) )
					weaponTokens[4] = "vzscope";
			
			if( isDefined( weaponTokens[3] ) && isSubStr( weaponTokens[3], "scope" ) && !isSubStr( weaponTokens[3], "vz" ) )
				weaponTokens[3] = undefined;
					
			if( isDefined( weaponTokens[4] ) && isSubStr( weaponTokens[4], "scope" ) && !isSubStr( weaponTokens[4], "vz" ) )
				weaponTokens[4] = undefined;
			
			
			if ( isDefined( weaponTokens[3] ) && isAttachment( weaponTokens[3] ) )
			{
				weaponAttachment = validateAttachment( weaponTokens[3] );
				setMatchData( "lives", lifeId, "attachments", 0, weaponAttachment );
			}
				
			if ( isDefined( weaponTokens[4] ) && isAttachment( weaponTokens[4] ) )
			{
				weaponAttachment = validateAttachment( weaponTokens[4] );
				setMatchData( "lives", lifeId, "attachments", 1, weaponAttachment );
			}
		}
		else if( weaponTokens[0] == "alt" )	
		{
			assert( weaponTokens.size > 1 );
			
			baseMW5WeaponName = weaponTokens[1] + "_" + weaponTokens[2];
					
			setMatchData( "lives", lifeId, "weapon", baseMW5WeaponName );
			
			if ( isDefined( weaponTokens[4] ) && isAttachment( weaponTokens[4] ) )	
			{
				weaponAttachment = validateAttachment( weaponTokens[4] );
				setMatchData( "lives", lifeId, "attachments", 0, weaponAttachment );
			}
				
			if ( isDefined( weaponTokens[5] ) && isAttachment( weaponTokens[5] ) )
			{
				weaponAttachment = validateAttachment( weaponTokens[5] );
				setMatchData( "lives", lifeId, "attachments", 1, weaponAttachment );
			}
		}
		else
		{
			assert( weaponTokens.size > 1 && weaponTokens.size <= 4 );
	
			assertEx( weaponTokens[weaponTokens.size - 1] == "mp", "weaponTokens[weaponTokens.size - 1]: " + weaponTokens[weaponTokens.size - 1] );
			weaponTokens[weaponTokens.size - 1] = undefined; // remove the trailing "mp"
					
			setMatchData( "lives", lifeId, "weapon", weaponTokens[0] );
	
			if ( isDefined( weaponTokens[1] ) && sWeaponType != "altmode" )
			{
				weaponAttachment = validateAttachment( weaponTokens[1] );
				setMatchData( "lives", lifeId, "attachments", 0, weaponAttachment );
			}
		
			if ( isDefined( weaponTokens[2] ) && sWeaponType != "altmode" )
			{
				weaponAttachment = validateAttachment( weaponTokens[2] );
				setMatchData( "lives", lifeId, "attachments", 1, weaponAttachment );
			}
		
		}
	}
	else if ( sWeaponType == "item" || sWeaponType == "offhand" )
	{
		weaponName = strip_suffix( sWeapon, "_mp" );
		setMatchData( "lives", lifeId, "weapon", weaponName );		
	}
	else
	{
		setMatchData( "lives", lifeId, "weapon", sWeapon );
	}
	
	if ( isKillstreakWeapon( sWeapon ) )
		setMatchData( "lives", lifeId, "modifiers", "killstreak", true );
		
	setMatchData( "lives", lifeId, "mod", sMeansOfDeath );
	if ( isPlayer( attacker ) )
	{
		setMatchData( "lives", lifeId, "attacker", attacker.clientid );
		setMatchData( "lives", lifeId, "attackerPos", 0, int( attacker.origin[0] ) );
		setMatchData( "lives", lifeId, "attackerPos", 1, int( attacker.origin[1] ) );
		setMatchData( "lives", lifeId, "attackerPos", 2, int( attacker.origin[2] ) );

		victimForward = anglesToForward( (0,self.angles[1],0) );
		attackDirection = (self.origin - attacker.origin);
		attackDirection = VectorNormalize( (attackDirection[0], attackDirection[1], 0) );
		setMatchData( "lives", lifeId, "dotOfDeath", VectorDot( victimForward, attackDirection ) );

		if( attacker isJuggernaut() )
			SetMatchData( "lives", lifeId, "attackerIsJuggernaut", true );
	}
	else
	{
		// 255 is world
		setMatchData( "lives", lifeId, "attacker", 255 );
		setMatchData( "lives", lifeId, "attackerPos", 0, int( self.origin[0] ) );
		setMatchData( "lives", lifeId, "attackerPos", 1, int( self.origin[1] ) );
		setMatchData( "lives", lifeId, "attackerPos", 2, int( self.origin[2] ) );
	}
	
	setMatchData( "lives", lifeId, "player", self.clientid );
	setMatchData( "lives", lifeId, "deathPos", 0, int( self.origin[0] ) );
	setMatchData( "lives", lifeId, "deathPos", 1, int( self.origin[1] ) );
	setMatchData( "lives", lifeId, "deathPos", 2, int( self.origin[2] ) );

	setMatchData( "lives", lifeId, "deathAngles", 0, int( self.angles[0] ) );
	setMatchData( "lives", lifeId, "deathAngles", 1, int( self.angles[1] ) );
	setMatchData( "lives", lifeId, "deathAngles", 2, int( self.angles[2] ) );	
}


logPlayerData()
{
	if ( !canLogClient( self ) )
		return;
		
	setMatchData( "players", self.clientid, "score", self getPersStat( "score" ) );
	
	if( self getPersStat( "assists" ) > 255 )
		setMatchData( "players", self.clientid, "assists", 255 );
	else
		setMatchData( "players", self.clientid, "assists", self getPersStat( "assists" ) );
		
	if( self getPersStat( "longestStreak" ) > 255 )
		setMatchData( "players", self.clientid, "longestStreak", 255 );
	else
		setMatchData( "players", self.clientid, "longestStreak", self getPersStat( "longestStreak" ) );
}


// log the weapons and weaponXP to playerdata.
endOfGameSummaryLogger()
{
	level waittill ( "game_ended" );
	
	foreach ( player in level.players )
	{	
		wait( 0.05 );
			
		if ( isDefined ( player.weaponsUsed ) )
		{
			player doubleBubbleSort();
			counter = 0;
			
			if ( player.weaponsUsed.size > 3 )
			{
				for ( i = (player.weaponsUsed.size - 1); i > (player.weaponsUsed.size - 3); i-- )
				{
					player setPlayerData( "round", "weaponsUsed", counter, player.weaponsUsed[i] );
					player setPlayerData( "round", "weaponXpEarned", counter, player.weaponXpEarned[i] );
					counter++;
				}
			}
			else
			{
				for ( i = (player.weaponsUsed.size - 1); i >= 0; i-- )
				{
					player setPlayerData( "round", "weaponsUsed", counter, player.weaponsUsed[i] );
					player setPlayerData( "round", "weaponXpEarned", counter, player.weaponXpEarned[i] );
					counter++;
				}
			}
		}
		else
		{
			player setPlayerData( "round", "weaponsUsed", 0, "none" );
			player setPlayerData( "round", "weaponsUsed", 1, "none" );
			player setPlayerData( "round", "weaponsUsed", 2, "none" );
			player setPlayerData( "round", "weaponXpEarned", 0, 0 );
			player setPlayerData( "round", "weaponXpEarned", 1, 0 );
			player setPlayerData( "round", "weaponXpEarned", 2, 0 );
		}
		
		if ( isDefined ( player.challengesCompleted ) )
		{	
			player setPlayerData( "round", "challengeNumCompleted", player.challengesCompleted.size );
		}
		else 
		{
			player setPlayerData( "round", "challengeNumCompleted", 0 );
		}	
		
		for ( i = 0; i < 20; i++ )
		{
			if ( isDefined( player.challengesCompleted ) && isDefined( player.challengesCompleted[i] ) && player.challengesCompleted[i] != "ch_prestige" && !IsSubStr( player.challengesCompleted[i], "_daily" ) && !IsSubStr( player.challengesCompleted[i], "_weekly" ) )		
				player setPlayerData( "round", "challengesCompleted", i, player.challengesCompleted[i] );
			else
				player setPlayerData( "round", "challengesCompleted", i, "" );
		}
	}
	
}

doubleBubbleSort()
{
	A = self.weaponXpEarned;
	n = self.weaponXpEarned.size;
  
  	for (i =(n-1); i > 0; i--)
    { 
    	for (j = 1; j <= i; j++)
        {
        	if( A[j-1] < A[j] )
           	{
           		temp = self.weaponsUsed[j];          
				self.weaponsUsed[j] = self.weaponsUsed[j-1];     
				self.weaponsUsed[j-1] = temp; 
				
				temp2 = self.weaponXpEarned[j];          
				self.weaponXpEarned[j] = self.weaponXpEarned[j-1];     
				self.weaponXpEarned[j-1] = temp2; 
				A = self.weaponXpEarned;
        	}
        }
    }
}


/*Recursive nonsense sorts based on array 1 and sorts array 2's indexes (should be logn)
quickDoubleSort() 
{
	quickDoubleSortMid( 0, self.weaponsUsed.size -1 );
}
quickDoubleSortMid( start, end )
{
	i = start;
	k = end;

	if (end - start >= 1)
    {
        pivot = self.weaponXpEarned[start];  

        while (k > i)         
        {
	        while (self.weaponXpEarned[i] <= pivot && i <= end && k > i)  
	        	i++;                                 
	        while (self.weaponXpEarned[k] > pivot && k >= start && k >= i) 
	            k--;                                      
	        if (k > i)                                 
	           self.weaponXpEarned = doubleSwap( i, k );                    
        }
        array = doubleSwap( start, k );                                               
        array = quickDoubleSortMid(start, k - 1); 
        array = quickDoubleSortMid(k + 1, end);   
    }
}
doubleSwap(index1, index2) 
{
	temp = self.weaponsUsed[index1];          
	self.weaponsUsed[index1] = self.weaponsUsed[index2];     
	self.weaponsUsed[index2] = temp; 
	
	temp2 = self.weaponXpEarned[index1];          
	self.weaponXpEarned[index1] = self.weaponXpEarned[index2];     
	self.weaponXpEarned[index2] = temp2;     
}
*///end recursive nightmare sort.


// log the lives of players who are still alive at match end.
gameEndListener()
{
	level waittill ( "game_ended" );
	
	foreach ( player in level.players )
	{		
		player logPlayerData();
		
		if ( !isAlive( player ) )
			continue;
			
		lifeId = getNextLifeId();
		player logPlayerLife( lifeId );
	}
}

canLogClient( client )
{
	assertEx( isPlayer( client ) , "Client is not a player: " + client.code_classname );
	return ( client.clientid < level.MaxLogClients );
}

canLogEvent()
{
	return ( getMatchData( "eventCount" ) < level.MaxEvents );
}

canLogKillstreak()
{
	return ( getMatchData( "killstreakCount" ) < level.MaxKillstreaks );
}

canLogLife( lifeId )
{
	return ( getMatchData( "lifeCount" ) < level.MaxLives );
}

logWeaponStat( weaponName, statName, incValue )
{
	if ( !canLogClient( self ) )
		return;
	
	if( isKillstreakWeapon( weaponName ) )
		return;

	oldValue = getMatchData( "players", self.clientid, "weaponStats", weaponName, statName );
	if( statName == "kills" || statName == "deaths" || statName == "headShots" )
	{
		if( oldValue+incValue > 255 )
		{
			setMatchData( "players", self.clientid, "weaponStats", weaponName, statName, 255 );	
		}
		else
		{
			setMatchData( "players", self.clientid, "weaponStats", weaponName, statName, oldValue+incValue );	
		} 
	}
	setMatchData( "players", self.clientid, "weaponStats", weaponName, statName, oldValue+incValue );	
}

logAttachmentStat( weaponName, statName, incValue )
{
	if ( !canLogClient( self ) )
		return;
	
	oldValue = getMatchData( "players", self.clientid, "attachmentsStats", weaponName, statName );
	setMatchData( "players", self.clientid, "attachmentsStats", weaponName, statName, oldValue+incValue );	
}

buildBaseWeaponList()
{
	baseWeapons = [];
	max_weapon_num = 149;
	for( weaponId = 0; weaponId <= max_weapon_num; weaponId++ )
	{
		weapon_name = tablelookup( "mp/statstable.csv", 0, weaponId, 4 );
		if( weapon_name == "" )
			continue;
		
		if ( !isSubStr( tableLookup( "mp/statsTable.csv", 0, weaponId, 2 ), "weapon_" ) )
			continue;
		
		if ( tableLookup( "mp/statsTable.csv", 0, weaponId, 2 ) == "weapon_other" )
			continue;
			 
		baseWeapons[baseWeapons.size] = weapon_name;
	}
	return baseWeapons;
}

logChallenge( challengeName, tier )
{
	if ( !canLogClient( self ) )
		return;
	
	// we don't want to log daily and weekly challenges
	//*if( IsSubStr( challengeName, "_daily" ) || IsSubStr( challengeName, "_weekly" ) )
	//*	return;

	challengeCount = getMatchData( "players", self.clientid, "challengeCount" );
	if( challengeCount < level.MaxNumChallengesPerPlayer )
	{
		setMatchData( "players", self.clientid, "challenge", challengeCount, challengeName );
		setMatchData( "players", self.clientid, "tier", challengeCount, tier );
		setMatchData( "players", self.clientid, "challengeCount", challengeCount + 1 );
	}
}

logAward( awardName )
{
	if ( !canLogClient( self ) )
		return;
	
	awardCount = getMatchData( "players", self.clientid, "awardCount" );
	if( awardCount < level.MaxNumAwardsPerPlayer )
	{
		setMatchData( "players", self.clientid, "awards", awardCount, awardName );
		setMatchData( "players", self.clientid, "awardCount", awardCount + 1 );
	}
}

logKillsConfirmed()
{
	if ( !canLogClient( self ) )
		return;
	
	setMatchData( "players", self.clientid, "killsConfirmed", self.pers["confirmed"] );
}

logKillsDenied()
{
	if ( !canLogClient( self ) )
		return;
		
	setMatchData( "players", self.clientid, "killsDenied", self.pers["denied"] );
}
