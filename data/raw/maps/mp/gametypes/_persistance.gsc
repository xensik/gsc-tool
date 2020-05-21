#include maps\mp\_utility;

init()
{
	level.persistentDataInfo = [];

	maps\mp\gametypes\_class::init();
	maps\mp\gametypes\_rank::init();
	maps\mp\gametypes\_missions::init();
	maps\mp\gametypes\_playercards::init();

	level thread updateBufferedStats();
	
	level thread uploadGlobalStatCounters();
}


initBufferedStats()
{
	println( "Init Buffered Stats for " + self.name );

	self.bufferedStats = [];
	self.bufferedStats[ "totalShots" ] = self getPlayerData( "totalShots" );	
	self.bufferedStats[ "accuracy" ] = self getPlayerData( "accuracy" );	
	self.bufferedStats[ "misses" ] = self getPlayerData( "misses" );	
	self.bufferedStats[ "hits" ] = self getPlayerData( "hits" );	
	self.bufferedStats[ "timePlayedAllies" ] = self getPlayerData( "timePlayedAllies" );	
	self.bufferedStats[ "timePlayedOpfor" ] = self getPlayerData( "timePlayedOpfor" );	
	self.bufferedStats[ "timePlayedOther" ] = self getPlayerData( "timePlayedOther" );	
	self.bufferedStats[ "timePlayedTotal" ] = self getPlayerData( "timePlayedTotal" );

	println( "timePlayedAllies " + self.bufferedStats[ "timePlayedAllies" ] );
	println( "timePlayedOpfor " + self.bufferedStats[ "timePlayedOpfor" ] );
	println( "timePlayedOther " + self.bufferedStats[ "timePlayedOther" ] );
	println( "timePlayedTotal " + self.bufferedStats[ "timePlayedTotal" ] );
	
	self.bufferedChildStats = [];
	self.bufferedChildStats[ "round" ] = [];
	self.bufferedChildStats[ "round" ][ "timePlayed" ] = self getPlayerData( "round", "timePlayed" );

	self.bufferedChildStats[ "xpMultiplierTimePlayed" ] = [];
	self.bufferedChildStats[ "xpMultiplierTimePlayed" ][ 0 ] = self getPlayerData( "xpMultiplierTimePlayed", 0 );
	self.bufferedChildStats[ "xpMultiplierTimePlayed" ][ 1 ] = self getPlayerData( "xpMultiplierTimePlayed", 1 );
	self.bufferedChildStats[ "xpMultiplierTimePlayed" ][ 2 ] = self getPlayerData( "xpMultiplierTimePlayed", 2 );

	self.bufferedChildStatsMax[ "xpMaxMultiplierTimePlayed" ] = [];
	self.bufferedChildStatsMax[ "xpMaxMultiplierTimePlayed" ][ 0 ] = self getPlayerData( "xpMaxMultiplierTimePlayed", 0 );
	self.bufferedChildStatsMax[ "xpMaxMultiplierTimePlayed" ][ 1 ] = self getPlayerData( "xpMaxMultiplierTimePlayed", 1 );
	self.bufferedChildStatsMax[ "xpMaxMultiplierTimePlayed" ][ 2 ] = self getPlayerData( "xpMaxMultiplierTimePlayed", 2 );

	self.bufferedChildStats[ "challengeXPMultiplierTimePlayed" ] = [];
	self.bufferedChildStats[ "challengeXPMultiplierTimePlayed" ][ 0 ] = self getPlayerData( "challengeXPMultiplierTimePlayed", 0 );

	self.bufferedChildStatsMax[ "challengeXPMaxMultiplierTimePlayed" ] = [];
	self.bufferedChildStatsMax[ "challengeXPMaxMultiplierTimePlayed" ][ 0 ] = self getPlayerData( "challengeXPMaxMultiplierTimePlayed", 0 );

	self.bufferedChildStats[ "weaponXPMultiplierTimePlayed" ] = [];
	self.bufferedChildStats[ "weaponXPMultiplierTimePlayed" ][ 0 ] = self getPlayerData( "weaponXPMultiplierTimePlayed", 0 );

	self.bufferedChildStatsMax[ "weaponXPMaxMultiplierTimePlayed" ] = [];
	self.bufferedChildStatsMax[ "weaponXPMaxMultiplierTimePlayed" ][ 0 ] = self getPlayerData( "weaponXPMaxMultiplierTimePlayed", 0 );
	
	//IW5 prestige reward double XP
	self.bufferedStats["prestigeDoubleXp"] = self getPlayerData( "prestigeDoubleXp" );
	self.bufferedStats["prestigeDoubleXpTimePlayed"] = self getPlayerData( "prestigeDoubleXpTimePlayed" );
	self.bufferedStatsMax["prestigeDoubleXpMaxTimePlayed"] = self getPlayerData( "prestigeDoubleXpMaxTimePlayed" );
	
	//IW5 prestige reward double Weapon XP
	self.bufferedStats["prestigeDoubleWeaponXp"] = self getPlayerData( "prestigeDoubleWeaponXp" );
	self.bufferedStats["prestigeDoubleWeaponXpTimePlayed"] = self getPlayerData( "prestigeDoubleWeaponXpTimePlayed" );
	self.bufferedStatsMax["prestigeDoubleWeaponXpMaxTimePlayed"] = self getPlayerData( "prestigeDoubleWeaponXpMaxTimePlayed" );
	
}


// ==========================================
// Script persistent data functions
// These are made for convenience, so persistent data can be tracked by strings.
// They make use of code functions which are prototyped below.

/*
=============
statGet

Returns the value of the named stat
=============
*/
statGet( dataName )
{
	assert( !isDefined( self.bufferedStats[ dataName ] ) ); // should use statGetBuffered consistently with statSetBuffered
	return self GetPlayerData( dataName );
}

/*
=============
statSet

Sets the value of the named stat
=============
*/
statSet( dataName, value )
{
	assert( !isDefined( self.bufferedStats[ dataName ] ) ); // should use statGetBuffered consistently with statSetBuffered
	
	if ( !self rankingEnabled() )
		return;
	
	self SetPlayerData( dataName, value );
}

/*
=============
statAdd

Adds the passed value to the value of the named stat
=============
*/
statAdd( dataName, value, optionalArrayInd )
{	
	assert( !isDefined( self.bufferedStats[ dataName ] ) ); // should use statGetBuffered consistently with statSetBuffered		
	
	if ( !self rankingEnabled() )
		return;
	
	if ( isDefined( optionalArrayInd ) )
	{
		curValue = self GetPlayerData( dataName, optionalArrayInd );
		self SetPlayerData( dataName, optionalArrayInd, value + curValue );
	}
	else
	{
		curValue = self GetPlayerData( dataName );
		self SetPlayerData( dataName, value + curValue );
	}
}


statGetChild( parent, child )
{
	return self GetPlayerData( parent, child );
}


statSetChild( parent, child, value )
{
	if ( !self rankingEnabled() )
		return;
	
	self SetPlayerData( parent, child, value );
}


statAddChild( parent, child, value )
{
	assert( isDefined( self.bufferedChildStats[ parent ][ child ] ) );

	if ( !self rankingEnabled() )
		return;
	
	curValue = self GetPlayerData( parent, child );
	self SetPlayerData( parent, child, curValue + value );
}


statGetChildBuffered( parent, child )
{
	assert( isDefined( self.bufferedChildStats[ parent ][ child ] ) );
	
	return self.bufferedChildStats[ parent ][ child ];
}


statSetChildBuffered( parent, child, value )
{
	assert( isDefined( self.bufferedChildStats[ parent ][ child ] ) );
	
	if ( !self rankingEnabled() )
		return;

	self.bufferedChildStats[ parent ][ child ] = value;
}


statAddChildBuffered( parent, child, value )
{
	assert( isDefined( self.bufferedChildStats[ parent ][ child ] ) );

	if ( !self rankingEnabled() )
		return;
	
	curValue = statGetChildBuffered( parent, child );
	statSetChildBuffered( parent, child, curValue + value );
}


statAddBufferedWithMax( stat, value, max )
{
	assert( isDefined( self.bufferedStats[ stat ] ) );

	if ( !self rankingEnabled() )
		return;
	
	newValue = statGetBuffered( stat ) + value;
	
	if ( newValue > max )
		newValue = max;
		
	if ( newValue < statGetBuffered( stat ) )	// has wrapped so keep at the max
		newValue = max;
		
	statSetBuffered( stat, newValue );
}


statAddChildBufferedWithMax( parent, child, value, max )
{
	assert( isDefined( self.bufferedChildStats[ parent ][ child ] ) );

	if ( !self rankingEnabled() )
		return;
	
	newValue = statGetChildBuffered( parent, child ) + value;
	
	if ( newValue > max )
		newValue = max;
		
	if ( newValue < statGetChildBuffered( parent, child ) )	// has wrapped so keep at the max
		newValue = max;
		
	statSetChildBuffered( parent, child, newValue );
}


/*
=============
statGetBuffered

Returns the value of the named stat
=============
*/
statGetBuffered( dataName )
{
	assert( isDefined( self.bufferedStats[ dataName ] ) );
	
	return self.bufferedStats[ dataName ];
}

/*
=============
statSet

Sets the value of the named stat
=============
*/
statSetBuffered( dataName, value )
{
	assert( isDefined( self.bufferedStats[ dataName ] ) );

	if ( !self rankingEnabled() )
		return;
	
	self.bufferedStats[ dataName ] = value;
}

/*
=============
statAdd

Adds the passed value to the value of the named stat
=============
*/
statAddBuffered( dataName, value )
{	
	assert( isDefined( self.bufferedStats[ dataName ] ) );
	assert( value >= 0 );

	if ( !self rankingEnabled() )
		return;
	
	curValue = statGetBuffered( dataName );
	statSetBuffered( dataName, curValue + value );
}


updateBufferedStats()
{
	// give the first player time to connect
	wait ( 0.15 );
	
	nextToUpdate = 0;
	while ( !level.gameEnded )
	{
		maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();

		nextToUpdate++;
		if ( nextToUpdate >= level.players.size )
			nextToUpdate = 0;

		if ( isDefined( level.players[nextToUpdate] ) )
		{
			level.players[nextToUpdate] writeBufferedStats();
			level.players[nextToUpdate] updateWeaponBufferedStats();
		}

		wait ( 2.0 );
	}
	
	foreach ( player in level.players )
	{
		player writeBufferedStats();
		player updateWeaponBufferedStats();
	}
			
}


writeBufferedStats()
{
	foreach ( statName, statVal in self.bufferedStats )
	{
		self setPlayerData( statName, statVal );
	}

	foreach ( statName, statVal in self.bufferedChildStats )
	{
		foreach ( childStatName, childStatVal in statVal )
			self setPlayerData( statName, childStatName, childStatVal );
	}
}

incrementWeaponStat( weaponName, stat, incValue )
{
	if( isKillstreakWeapon( weaponName ) )
		return;

	if ( self rankingEnabled() )
	{
		oldval = self getPlayerData( "weaponStats", weaponName, stat );			
		self setPlayerData( "weaponStats", weaponName, stat, oldval+incValue );
	}
}

incrementAttachmentStat( attachmentName, stat, incValue )
{
	if ( self rankingEnabled() )
	{
		oldval = self getPlayerData( "attachmentsStats", attachmentName, stat );			
		self setPlayerData( "attachmentsStats", attachmentName, stat, oldval+incValue );
	}
}


updateWeaponBufferedStats()
{
	if( !isdefined( self.trackingWeaponName ) )
		return;
		
	if( self.trackingWeaponName == "" || self.trackingWeaponName == "none" )
		return;
	
	tmp = self.trackingWeaponName;
	
	//if( isSubStr( self.trackingWeaponName, "iw5_" ) )
	//tmp = GetSubStr( self.trackingWeaponName, 4, self.trackingWeaponName.size );
	
	// check for killstreak and environment before we start tokenizing the weapon name
	if( isKillstreakWeapon( tmp ) || isEnvironmentWeapon( tmp ) )
		return;
	
	/*stripping out akimbo and adding it in as it were an attachment for tracking
	if ( isSubStr( tmp, "akimbo" ) )
	{
		tmp = fixAkimboString( tmp );
	}
	*/
		
	tokens = strTok( tmp, "_" );
	
	//updating for IW5 weapons
	if ( tokens[0] == "iw5" )
		tokens[0] = tokens[0] + "_" + tokens[1];
	
	if ( tokens[0] == "alt" )
	{
		foreach( token in tokens )
		{
			if ( token == "gl" || token == "gp25" || token == "m320" )
			{
				tokens[0] = "gl";
				break;	
			}
			if ( token == "shotgun" )
			{
				tokens[0] = "shotgun";
				break;	
			}
		}
		
		//For Hybrid Scopes
		if ( tokens[0] == "alt" )
		{
			tokens[0] = tokens[1] + "_" + tokens[2];
		}
		
	}
	
	//when you hit someone or kill someone with the gl it will come in as the first token
	if( tokens[0] == "gl" || tokens[0] == "shotgun" )
	{
		//println(" player is " + self.name);
		//println( "weapon is  " + tokens[0]);
		if( self.trackingWeaponShots > 0 )
		{
			self incrementAttachmentStat( tokens[0], "shots", self.trackingWeaponShots ); 
			self maps\mp\_matchdata::logAttachmentStat( tokens[0], "shots", self.trackingWeaponShots);
			//println("wrote shots");
		}
		
		if( self.trackingWeaponKills > 0 )
		{
			self incrementAttachmentStat( tokens[0], "kills", self.trackingWeaponKills ); 
			self maps\mp\_matchdata::logAttachmentStat( tokens[0], "kills", self.trackingWeaponKills);
			//println("wrote kills");
		}
		
		if(	self.trackingWeaponHits > 0 )
		{
			self incrementAttachmentStat( tokens[0], "hits", self.trackingWeaponHits ); 
			self maps\mp\_matchdata::logAttachmentStat( tokens[0], "hits", self.trackingWeaponHits);
			//println("wrote hits");
		}
		
		if( self.trackingWeaponHeadShots > 0 )
		{
			self incrementAttachmentStat( tokens[0], "headShots", self.trackingWeaponHeadShots ); 
			self maps\mp\_matchdata::logAttachmentStat( tokens[0], "headShots", self.trackingWeaponHeadShots);
			//println("wrote headshots");
		}
			
		if( self.trackingWeaponDeaths > 0 )
		{
			self incrementAttachmentStat( tokens[0], "deaths", self.trackingWeaponDeaths ); 
			self maps\mp\_matchdata::logAttachmentStat( tokens[0], "deaths", self.trackingWeaponDeaths);
			//println("wrote deaths");
		}
		
		self.trackingWeaponName = "none";
		self.trackingWeaponShots = 0;
		self.trackingWeaponKills = 0;
		self.trackingWeaponHits = 0;
		self.trackingWeaponHeadShots = 0;
		self.trackingWeaponDeaths = 0;
		return;
	}
	
	if ( !isCACPrimaryWeapon( tokens[0] ) && !isCACSecondaryWeapon( tokens[0] ) )
		return;
	
	//log the weapon
	//println(" player is " + self.name);
	//println( "weapon is  " + tokens[0]);
	if( self.trackingWeaponShots > 0 )
	{
		self incrementWeaponStat( tokens[0], "shots", self.trackingWeaponShots );
		self maps\mp\_matchdata::logWeaponStat( tokens[0], "shots", self.trackingWeaponShots);
		//println("wrote shots");
	}
	
	if( self.trackingWeaponKills > 0 )
	{
		self incrementWeaponStat( tokens[0], "kills", self.trackingWeaponKills );
		self maps\mp\_matchdata::logWeaponStat( tokens[0], "kills", self.trackingWeaponKills);
		//println("wrote kills");
	}
	
	if(	self.trackingWeaponHits > 0 )
	{
		self incrementWeaponStat( tokens[0], "hits", self.trackingWeaponHits );
		self maps\mp\_matchdata::logWeaponStat( tokens[0], "hits", self.trackingWeaponHits);
		//println("wrote hits");
	}
	
	if( self.trackingWeaponHeadShots > 0 )
	{
		self incrementWeaponStat( tokens[0], "headShots", self.trackingWeaponHeadShots );
		self maps\mp\_matchdata::logWeaponStat( tokens[0], "headShots", self.trackingWeaponHeadShots);
		//println("wrote headshots");
	}
	
	if( self.trackingWeaponDeaths > 0 )
	{
		self incrementWeaponStat( tokens[0], "deaths", self.trackingWeaponDeaths );
		self maps\mp\_matchdata::logWeaponStat( tokens[0], "deaths", self.trackingWeaponDeaths);
		//println("wrote deaths");
	}
	
	//retokenize for attachments.
	tokens = strTok( tmp, "_" );
	
	//log the attachments
	if( tokens[0] != "none" )
	{
		for( i = 0; i < tokens.size; i++ )
		{
			if( tokens[i] == "mp" || tokens[i] == "scope1" || tokens[i] == "scope2" || tokens[i] == "scope3" || tokens[i] == "scope4" || tokens[i] == "scope5" || tokens[i] == "scope6" || tokens[i] == "scope7" || tokens[i] == "scope8" || tokens[i] == "scope9" || tokens[i] == "scope10" )
				continue;
			
			if ( isSubStr( tokens[i], "camo" ) )
				continue;
			
			//handles iw5 scoped weapons
			if( isSubStr( tokens[i], "scope" ) && !isSubStr( tokens[i], "vz" ) )
				continue; 
			
			//iw5 token magic	
			if(tokens[i] == "alt" )
			{	
				i += 2;
				continue;			
			}	
			
			//iw5 token magic	
			if(tokens[i] == "iw5" )
			{	
				i += 1;
				continue;
			}
			
			//turns alternate silencers and gls into correct stat track
			tokens[i] = validateAttachment( tokens[i] );
			if( tokens[i] == "gl" || tokens[i] == "shotgun" )
				continue;
			
			if ( isSubStr( tokens[i], "scope" ) && isSubStr( tokens[i], "vz" ) )
				tokens[i] = "vzscope";
			
			//IW4 weapon check
			if ( i == 0 && ( tokens[i] != "iw5" && tokens[i] != "alt" ) )
				continue;
			
			//println( "weapon is  " + tokens[i]);
			if( self.trackingWeaponShots > 0 )
			{
				self incrementAttachmentStat( tokens[i], "shots", self.trackingWeaponShots ); 
				self maps\mp\_matchdata::logAttachmentStat( tokens[i], "shots", self.trackingWeaponShots);
				//println("wrote shots");
			}
	
			if( self.trackingWeaponKills > 0 )
			{
				self incrementAttachmentStat( tokens[i], "kills", self.trackingWeaponKills ); 
				self maps\mp\_matchdata::logAttachmentStat( tokens[i], "kills", self.trackingWeaponKills);
				//println("wrote kills");
			}
	
			if(	self.trackingWeaponHits > 0 )
			{
				self incrementAttachmentStat( tokens[i], "hits", self.trackingWeaponHits ); 
				self maps\mp\_matchdata::logAttachmentStat( tokens[i], "hits", self.trackingWeaponHits);
				//println("wrote hits");
			}
	
			if( self.trackingWeaponHeadShots > 0 )
			{
				self incrementAttachmentStat( tokens[i], "headShots", self.trackingWeaponHeadShots ); 
				self maps\mp\_matchdata::logAttachmentStat( tokens[i], "headShots", self.trackingWeaponHeadShots);
				//println("wrote headshots");
			}
	
			if( self.trackingWeaponDeaths > 0 )
			{
				self incrementAttachmentStat( tokens[i], "deaths", self.trackingWeaponDeaths ); 
				self maps\mp\_matchdata::logAttachmentStat( tokens[i], "deaths", self.trackingWeaponDeaths);
				//println("wrote deaths");
			}
			
		}
	}
	
	self.trackingWeaponName = "none";
	self.trackingWeaponShots = 0;
	self.trackingWeaponKills = 0;
	self.trackingWeaponHits = 0;
	self.trackingWeaponHeadShots = 0;
	self.trackingWeaponDeaths = 0;
}


uploadGlobalStatCounters()
{
	level waittill( "game_ended" );
	
	if( !matchMakingGame() )
		return;
		
	totalKills = 0;
	totalDeaths = 0;
	totalAssists = 0;
	totalHeadshots = 0;
	totalSuicides = 0;
	totalTimePlayed = 0;
	
	foreach ( player in level.players ) 
	{
		totalTimePlayed += player.timePlayed["total"];
	}

	incrementCounter( "global_minutes", int( totalTimePlayed / 60 ) );

	if ( !wasLastRound() )
		return;

	wait( 0.05 );
	
	foreach ( player in level.players ) 
	{
		totalKills += player.kills;
		totalDeaths += player.deaths;
		totalAssists += player.assists;
		totalHeadshots += player.headshots;	
		totalSuicides += player.suicides;
	}

	incrementCounter( "global_kills", totalKills );
	incrementCounter( "global_deaths", totalDeaths );
	incrementCounter( "global_assists", totalAssists );
	incrementCounter( "global_headshots", totalHeadshots );
	incrementCounter( "global_suicides", totalSuicides );
	incrementCounter( "global_games", 1 );
}