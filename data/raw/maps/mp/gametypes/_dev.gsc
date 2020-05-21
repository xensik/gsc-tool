#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

init()
{
	/#
	SetDevDvarIfUninitialized("scr_showspawns", "0");

	precacheItem("defaultweapon_mp");
	precacheModel("test_sphere_silver");
	precacheModel("test_sphere_redchrome");

	level.devSpawnFXid = loadfx( maps\mp\gametypes\_teams::getTeamFlagFX( "axis" ) );

	thread addTestClients();
	thread haveTestClientKillPlayer();
	thread haveTestClientCallKillstreak();
	thread haveTestClientPlantExplosive();
	thread haveTestClientThrowDeployableVest();
	thread addTestClientJuggernaut();
	thread addTestClientSpawnPoint();
	thread warpEnemies();
	thread warpFriendlies();
	thread giveEquipment();
	thread giveSpecialGrenade();
	thread watchNoClip();
	thread watchUFO();
	thread printPerks();
	thread devGivePerks();
	thread devClearPerks();
	thread devHurtPlayer();
	thread devHurtPlayerReset();
	thread devHurtPlayerDirectional();
	thread devChangeTimeLimit();
	thread devWeaponXP();
	thread devPlayerXP();
	thread devScriptMoversDebugDraw();
	thread devHeliPathDebugDraw();
	thread devPredatorMissileDebugDraw();
	thread devPrintDailyWeeklyChallenges();

	SetDevDvarIfUninitialized( "scr_testclients", "0" );
	SetDevDvarIfUninitialized( "scr_testclients_killplayer", "0" );
	SetDevDvarIfUninitialized( "scr_testclients_givekillstreak", "" );
	SetDevDvarIfUninitialized( "scr_testclients_givekillstreak_toggleall", "0" );
	SetDevDvarIfUninitialized( "scr_testclients_givekillstreak_toggleall_sametime", "0" );
	SetDevDvarIfUninitialized( "scr_testclients_plantexplosive", "" );
	SetDevDvarIfUninitialized( "scr_testclients_throw_deployable_vest", "0" );
	SetDevDvarIfUninitialized( "scr_testclients_jugg", "" );
	SetDevDvarIfUninitialized( "scr_testclients_spawnpoint", "0" );
	SetDevDvarIfUninitialized( "scr_warpenemies", "0" );
	SetDevDvarIfUninitialized( "scr_warpfriendlies", "0" );
	SetDevDvarIfUninitialized( "scr_debuguav", "0" );
	SetDevDvarIfUninitialized( "scr_debugairstrike", "0" );
	SetDevDvarIfUninitialized( "scr_printperks", "0" );
	SetDevDvarIfUninitialized( "scr_devnoclip", "0" );
	SetDevDvarIfUninitialized( "scr_devufo", "0" );
	SetDevDvarIfUninitialized( "scr_devgiveperk", "" );
	SetDevDvarIfUninitialized( "scr_devgivedeathstreak", "0" );
	SetDevDvarIfUninitialized( "scr_devdeathstreakoverride", "specialty_null" );
	SetDevDvarIfUninitialized( "scr_devclearperks", "0" );
	SetDevDvarIfUninitialized( "scr_devhurtplayer", "0" );
	SetDevDvarIfUninitialized( "scr_devhurtplayerreset", "0" );
	SetDevDvarIfUninitialized( "scr_devhurtplayerdirectional", "" );
	SetDevDvarIfUninitialized( "scr_dir_blood", "0" );
	SetDevDvarIfUninitialized( "scr_devchangetimelimit", "0" );
	SetDevDvarIfUninitialized( "scr_devweaponxp", "0" );
	SetDevDvarIfUninitialized( "scr_devresetweaponxp", "0" );
	SetDevDvarIfUninitialized( "scr_devplayerxp", "0" );
	SetDevDvarIfUninitialized( "scr_devScriptMoversDebugDraw", "0" );
	SetDevDvarIfUninitialized( "scr_devHeliPathsDebugDraw", "0" );
	SetDevDvarIfUninitialized( "scr_devPredatorMissileDebugDraw", "0" );
	SetDevDvarIfUninitialized( "scr_devPrintDailyWeeklyChallenges", "" );

	SetDevDvar( "scr_givspecialgrenade", "" );
	SetDevDvar( "scr_giveequipment", "" );
	SetDevDvar( "scr_list_weapons", "" );
	SetDevDvar( "scr_givekillstreak", "" );
	SetDevDvar( "scr_devgivecarepackage", "" );
	SetDevDvar( "scr_devgivecarepackagetype", "" );
	SetDevDvar( "scr_useGambit", "" );

	SetDevDvar( "scr_predatorme", "" );
	SetDevDvar( "scr_setdefcon", "" );
	SetDevDvar( "scr_showcard", "" );
	SetDevDvar( "scr_showoutcome", "" );

	SetDevDvar( "scr_enemykillhost", "" );

	SetDevDvar( "scr_giveperk", "" );
	SetDevDvar( "scr_takeperk", "" );
	
	SetDevDvar( "scr_sre", "" );
	SetDevDvar( "scr_testmigration", "" );
	
	SetDevDvar( "scr_show_splash", "" );
	SetDevDvar( "scr_spam_splashes", "" );
	SetDevDvar( "scr_spam_usedsplash", "" );
	SetDevDvar( "scr_spam_eventsplash", "" );
	SetDevDvar( "scr_spam_boteventsplash", "" );
	SetDevDvar( "scr_spam_ranksplash", "" );
	SetDevDvar( "scr_spam_weaponranksplash", "" );
	
	SetDevDvar( "scr_show_endgameupdate", "" );
	
	SetDevDvar( "scr_goto_spawn", "" );
	
	SetDevDvar( "scr_showOrigin", "" );

	level.baseWeaponList = maps\mp\gametypes\_weapons::buildWeaponData( true );	

	SetDevDvarIfUninitialized( "debug_reflection", "0" );

	level thread onPlayerConnect();	
	
	for(;;)
	{
		wait .05;
		updateDevSettings();
	}
	#/
}


/#
updateDevSettings()
{
	showspawns = getdvarInt("scr_showspawns");
	if(showspawns > 1)
		showspawns = 1;
	else if(showspawns < 0)
		showspawns = 0;
	
	if(!isdefined(level.showspawns) || level.showspawns != showspawns)
	{
		level.showspawns = showspawns;
		SetDevDvar("scr_showspawns", level.showspawns);

		if(level.showspawns)
			showSpawnpoints();
		else
			hideSpawnpoints();
	}
	
	updateMinimapSetting();
	
	if ( getDvar( "scr_test_weapon" ) != "" )
	{
		foreach ( player in level.players )
		{
			player thread initForWeaponTests();
			player setTestWeapon( getDvar( "scr_test_weapon" ) );
		}

		SetDevDvar( "scr_test_weapon", "" );
	}

	if ( getDvar( "scr_dump_ranks" ) != "" )
	{

		SetDevDvar( "scr_dump_ranks", "" );

		for ( rId = 0; rId <= level.maxRank; rId++ )
		{
			rankName = tableLookupIString( "mp/rankTable.csv", 0, rId, 5 );
			iprintln( "REFERENCE           UNLOCKED_AT_LV" + (rId+1) );
			iprintln( "LANG_ENGLISH        Unlocked at ", rankName, " (Lv" + (rId+1) + ")" );
			
			wait ( 0.05 );
		}		
	}
	
	if ( getDvar( "scr_list_weapons" ) != "" )
	{
		foreach ( baseWeapon, _ in level.baseWeaponList )
			iPrintLn( baseWeapon );

		SetDevDvar( "scr_list_weapons", "" );
	}

	if ( getdvarint("scr_predatorme") == 1 )
	{
		foreach ( player in level.players )
			level thread maps\mp\killstreaks\_remotemissile::_fire_noplayer( 0, player );

		SetDevDvar( "scr_predatorme", "" );
	}

	if ( getdvarfloat("scr_complete_all_challenges") != 0 )
	{
		foreach ( player in level.players )
		{
			player thread maps\mp\gametypes\_missions::completeAllChallenges( getdvarfloat("scr_complete_all_challenges") );
		}

		SetDevDvar( "scr_complete_all_challenges", "" );
	}

	if ( getDvarInt("scr_setdefcon") != 0 )
	{
		maps\mp\_defcon::updateDefcon( getDvarInt("scr_setdefcon") ); 
		SetDevDvar( "scr_setdefcon", "" );
	}

	if ( getDvar("scr_givekillstreak") != "" )
	{
		streakName = getDvar( "scr_givekillstreak" );
		
		resetEMPDvar = false;
		EMPTime = undefined;
		if( streakName == "emp_quick" )
		{
			resetEMPDvar = true;
			EMPTime = GetDvarFloat( "scr_emp_timeout" );
			streakName = "emp";
			SetDevDvar( "scr_emp_timeout", 1.0 );
		}
		
		if( streakName == "juggernaut" || streakName == "juggernaut_recon" )
		{
			if( level.players[0] isJuggernaut() )
			{
				level.players[0] notify( "lost_juggernaut" );
				wait( 0.05 );
			}

			level.players[0] thread maps\mp\killstreaks\_juggernaut::giveJuggernaut( streakname );
		}
		else if ( isDefined( level.killstreakFuncs[streakName] ) && tableLookup( "mp/killstreakTable.csv", 1, streakName, 0 ) != "" )
		{
			foreach ( player in level.players )
			{
				if( isDefined( player.pers[ "isBot" ] ) && player.pers[ "isBot" ] )
					continue;

				if ( player.team != "spectator" )
					player maps\mp\killstreaks\_killstreaks::giveKillstreak( streakName );
			}
		}
		else
		{
			println( "\"" + getDvar("scr_givekillstreak") + "\" is not a valid value for scr_givekillstreak. Try:" );
			foreach ( killstreak, value in level.killstreakFuncs )
			{				
				if ( tableLookup( "mp/killstreakTable.csv", 1, killstreak, 0 ) != "" )
					println( "    " + killstreak );
			}
			println( "" );
		}

		if( resetEMPDvar )
		{
			level thread waitResetDvar( 5.0, "scr_emp_timeout", EMPTime );
		}

		SetDevDvar( "scr_givekillstreak", "" );
	}

	if ( GetDvarInt( "scr_devgivedeathstreak" ) > 0 )
	{
		streakName = GetDvar( "scr_devdeathstreakoverride" );

		foreach( player in level.players )
		{
			if( isDefined( player.pers[ "isBot" ] ) && player.pers[ "isBot" ] )
				continue;

			if( player.team == "spectator" )
				continue;

			player.pers["cur_death_streak"] = int( TableLookup( "mp/perkTable.csv", 1, streakName, 6 ) );
			SetDevDvar( "scr_testclients_killplayer", 1 );
		}

		SetDevDvar( "scr_devgivedeathstreak", 0 );
	}

	if ( getDvar("scr_devgivecarepackage") != "" )
	{
		streakName = getDvar( "scr_devgivecarepackage" );
		streakType = getDvar( "scr_devgivecarepackagetype" );

		if ( ( isDefined( level.killstreakFuncs[streakName] ) && tableLookup( "mp/killstreakTable.csv", 1, streakName, 0 ) != "" ) || streakName == "random" )
		{
			foreach ( player in level.players )
			{
				if( isDefined( player.pers[ "isBot" ] ) && player.pers[ "isBot" ] )
					continue;

				if ( player.team != "spectator" )
					player maps\mp\killstreaks\_killstreaks::giveKillstreak( "airdrop_assault" );

				if( streakName != "random" )
				{
					SetDevDvar( "scr_crateOverride", streakName );
					SetDevDvar( "scr_crateTypeOverride", streakType );
				}
				else
				{
					SetDevDvar( "scr_crateOverride", "" );
					SetDevDvar( "scr_crateTypeOverride", "" );
				}
			}
		}
		else
		{
			println( "\"" + getDvar("scr_devgivecarepackage") + "\" is not a valid value for scr_devgivecarepackage. Try:" );
			foreach ( killstreak, value in level.killstreakFuncs )
			{				
				if ( tableLookup( "mp/killstreakTable.csv", 1, killstreak, 0 ) != "" )
					println( "    " + killstreak );
			}
			println( "" );
		}

		SetDevDvar( "scr_devgivecarepackage", "" );
		SetDevDvar( "scr_devgivecarepackagetype", "" );
	}

	if ( getDvar("scr_showcard") != "" )
	{
		tokens = strTok( getDvar( "scr_showcard" ), " " );

		if ( tokens.size )
		{
			playerName = tokens[0];
	
			if ( isDefined( tokens[1] ) )
				slotId = int(tokens[1]);
			else
				slotId = 0;
	
			owner = undefined;
			foreach ( player in level.players )
			{
				if ( player.name == playerName )
				{
					owner = player;	
					player SetCardDisplaySlot( player, slotId );					
					break;
				}
			}
			
			if ( !isDefined( owner ) )
				printLn( "Player " + playerName + "not found!" );				
		}

		SetDevDvar( "scr_showcard", "" );
	}

	if ( getDvar("scr_usekillstreak") != "" )
	{
		tokens = strTok( getDvar( "scr_usekillstreak" ), " " );

		if ( tokens.size > 1 )
		{
			playerName = tokens[0];
			streakName = tokens[1];

			if ( !isDefined( level.killstreakFuncs[streakName] ) )
				printLn( "Killstreak " + streakName + "not found!" );
			
			owner = undefined;
			foreach ( player in level.players )
			{
				if ( player.name == playerName )
				{
					owner = player;
					
					player maps\mp\killstreaks\_killstreaks::giveKillstreak( streakName );
					
					if ( isDefined( tokens[2] ) )
						player thread maps\mp\killstreaks\_killstreaks::killstreakUsePressed();
					else
						player thread [[ level.killstreakFuncs[ streakName ] ]]();
					
					if ( isSubStr( streakName, "airstrike" ) )
					{
						wait .05;
						player notify( "confirm_location", level.mapCenter, 0 );
					}
					
					if ( isSubStr( streakName, "airdrop" ) )
					{
						wait .05;
						
						switch( streakName )
						{
						case "airdrop_assault":
						case "airdrop_support":
							level thread maps\mp\killstreaks\_airdrop::doFlyBy( player, level.mapCenter, randomFloat( 360 ), streakName );
							break;
						case "airdrop_mega":
							level thread maps\mp\killstreaks\_airdrop::doC130FlyBy( player, level.mapCenter, randomFloat( 360 ), streakName );
							break;
						}
					}
					break;
				}
			}
			
			if ( !isDefined( owner ) )
				printLn( "Player " + playerName + "not found!" );				
		}
		SetDevDvar( "scr_usekillstreak", "" );
	}

	if ( getDvar("scr_playertoorigin") != "" )
	{
		tokens = strTok( getDvar( "scr_playertoorigin" ), " " );

		newOrigin = (int(tokens[0]), int(tokens[1]), int(tokens[2]));

		playerName = tokens[3];
		foreach ( player in level.players )
		{
			if ( player.name == playerName )
			{
				player setOrigin( newOrigin );
				break;
			}
		}

		SetDevDvar( "scr_playertoorigin", "" );
	}
	
	if ( getDvar("scr_useGambit") != "" )
	{
		tokens = strTok( getDvar( "scr_useGambit" ), " " );

		if ( tokens.size > 1 )
		{
			playerName = tokens[0];
			gambitName = tokens[1];

			if ( !isDefined( level.scriptPerks[gambitName] ) )
				printLn( "Gambit " + gambitName + "not found!" );
			
			owner = undefined;
			foreach ( player in level.players )
			{
				if ( player.name == playerName )
				{
					owner = player;
					player notify("gambit_on");
					break;
				}
			}
			
			if ( !isDefined( owner ) )
				printLn( "Player " + playerName + "not found!" );				
		}
		SetDevDvar( "scr_useGambit", "" );
	}
	
	if ( getDvar("scr_levelnotify" ) != "" )
	{
		level notify ( getDvar( "scr_levelnotify" ) );
		SetDevDvar( "scr_levelnotify", "" );
	}

	if ( getdvar("scr_giveperk") != "" )
	{
		perk = getdvar("scr_giveperk");

		for ( i = 0; i < level.players.size; i++ )
			level.players[i] thread givePerk( perk, false );

		SetDevDvar( "scr_giveperk", "" );
	}
	if ( getdvar("scr_takeperk") != "" )
	{
		perk = getdvar("scr_takeperk");
		for ( i = 0; i < level.players.size; i++ )
		{
			level.players[i] unsetPerk( perk, true );
			level.players[i].extraPerks[ perk ] = undefined;
		}
		SetDevDvar( "scr_takeperk", "" );
	}
	
	if ( getDvar( "scr_x_kills_y" ) != "" )
	{
		nameTokens = strTok( getDvar( "scr_x_kills_y" ), " " );
		if ( nameTokens.size > 1 )
			thread xKillsY( nameTokens[0], nameTokens[1] );

		SetDevDvar( "scr_x_kills_y", "" );
	}

	if ( getDvar( "scr_enemykillhost" ) != "" )
	{
		hostPlayer = undefined;
		enemyPlayer = undefined;
		foreach ( player in level.players )
		{
			if ( !player isHost() )
				continue;
				
			hostPlayer = player;
			break;
		}
		
		
		foreach ( player in level.players )
		{
			if ( level.teamBased )
			{
				if ( player.team == hostPlayer.team )
					continue;
					
				enemyPlayer = player;
				break;
			}
			else
			{
				if ( player isHost() )
					continue;
					
				enemyPlayer = player;
				break;
			}
		}
		
		if ( isDefined( enemyPlayer ) )
			thread xKillsY( enemyPlayer.name, hostPlayer.name );

		SetDevDvar( "scr_enemykillhost", "" );
	}

	if ( getDvar( "scr_drop_weapon" ) != "" )
	{
		weapon = spawn( "weapon_" + getDvar( "scr_drop_weapon" ), level.players[0].origin );
		SetDevDvar( "scr_drop_weapon", "" );
	}

	if ( getDvar( "scr_set_rank" ) != "" )
	{
		level.players[0].pers["rank"] = 0;
		level.players[0].pers["rankxp"] = 0;
		
		newRank = min( getDvarInt( "scr_set_rank" ), 54 );
		newRank = max( newRank, 1 );

		SetDevDvar( "scr_set_rank", "" );

		if ( level.teamBased && (!level.teamCount["allies"] || !level.teamCount["axis"]) )
			println( "scr_set_rank may not work because there are not players on both teams" );
		else if ( !level.teamBased && (level.teamCount["allies"] + level.teamCount["axis"] < 2) )
			println( "scr_set_rank may not work because there are not at least two players" );
		
		level.players[0] setPlayerData( "restXPGoal", 0 );
		
		lastXp = 0;
		for ( index = 0; index <= newRank; index++ )		
		{
			newXp = maps\mp\gametypes\_rank::getRankInfoMinXP( index );
			level.players[0] thread maps\mp\gametypes\_rank::giveRankXP( "kill", newXp - lastXp );
			lastXp = newXp;
			wait ( 0.25 );
			self notify ( "cancel_notify" );
		}
	}

	if ( getDvar( "scr_givexp" ) != "" )
	{
		level.players[0] thread maps\mp\gametypes\_rank::giveRankXP( "challenge", getDvarInt( "scr_givexp" ) );
		
		SetDevDvar( "scr_givexp", "" );
	}

	if ( getDvar( "scr_do_notify" ) != "" )
	{
		for ( i = 0; i < level.players.size; i++ )
			level.players[i] maps\mp\gametypes\_hud_message::oldNotifyMessage( getDvar( "scr_do_notify" ), getDvar( "scr_do_notify" ), game["icons"]["allies"] );
		
		announcement( getDvar( "scr_do_notify" ) );
		SetDevDvar( "scr_do_notify", "" );
	}	

	if ( getDvar( "scr_spam_splashes" ) != "" )
	{
		foreach( player in level.players )
		{
			player thread maps\mp\gametypes\_hud_message::splashNotifyDelayed( "longshot" );
			player thread maps\mp\gametypes\_hud_message::splashNotifyDelayed( "headshot" );
			player thread maps\mp\gametypes\_hud_message::challengeSplashNotify( "ch_marksman_iw5_m4" );
			player thread maps\mp\gametypes\_hud_message::splashNotifyDelayed( "execution" );
			player thread maps\mp\gametypes\_hud_message::killstreakSplashNotify( "uav", 3 );
			player thread maps\mp\gametypes\_hud_message::killstreakSplashNotify( "ac130", 11 );
			level thread teamPlayerCardSplash( "used_emp", player, player.team );
			player thread maps\mp\gametypes\_rank::updateRankAnnounceHUD();
			player thread maps\mp\gametypes\_rank::updateWeaponRankAnnounceHUD();
			
			player SetCardDisplaySlot( player, 8 );
			player openMenu( "youkilled_card_display" );
			wait( 2.0 );
			player SetCardDisplaySlot( player, 7 );
			player openMenu( "killedby_card_display" );
		}
		
		SetDevDvar( "scr_spam_splashes", "" );	
	}

	if ( getDvar( "scr_spam_usedsplash" ) != "" )
	{
		foreach( player in level.players )
		{
			level thread teamPlayerCardSplash( "used_emp", player, player.team );
			level thread teamPlayerCardSplash( "used_ac130", player, player.team );
			level thread teamPlayerCardSplash( "used_sentry", player, player.team );
			level thread teamPlayerCardSplash( "used_remote_mortar", player, player.team );
			level thread teamPlayerCardSplash( "used_remote_mg_turret", player, player.team );
			level thread teamPlayerCardSplash( "used_littlebird_support", player, player.team );
			level thread teamPlayerCardSplash( "used_littlebird_flock", player, player.team );
			level thread teamPlayerCardSplash( "used_ims", player, player.team );
			level thread teamPlayerCardSplash( "used_remote_tank", player, player.team );
		}

		SetDevDvar( "scr_spam_usedsplash", "" );	
	}

	if ( getDvar( "scr_spam_eventsplash" ) != "" )
	{
		foreach( player in level.players )
		{
			level thread teamPlayerCardSplash( "callout_firstblood", player );
			level thread teamPlayerCardSplash( "callout_grabbedtheflag", player );
			level thread teamPlayerCardSplash( "callout_lastenemyalive", player );
			level thread teamPlayerCardSplash( "callout_lastteammemberalive", player );
			level thread teamPlayerCardSplash( "callout_eliminated", player );
			level thread teamPlayerCardSplash( "callout_destroyed_helicopter_flares", player );
			level thread teamPlayerCardSplash( "callout_destroyed_little_bird", player );
			level thread teamPlayerCardSplash( "callout_bombdefused", player );
			level thread teamPlayerCardSplash( "callout_3xpluskill", player );
		}

		SetDevDvar( "scr_spam_eventsplash", "" );	
	}

	if ( getDvar( "scr_spam_boteventsplash" ) != "" )
	{
		// get the first player and make them the "host"
		notBot = level.players[0];
		foreach( player in level.players )
		{
			if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
			{
				notBot = player;
				break;
			}
		}

		bot = getBot( notBot );

		level thread teamPlayerCardSplash( "callout_firstblood", bot );
		level thread teamPlayerCardSplash( "callout_grabbedtheflag", bot );
		level thread teamPlayerCardSplash( "callout_lastenemyalive", bot );
		level thread teamPlayerCardSplash( "callout_lastteammemberalive", bot );
		level thread teamPlayerCardSplash( "callout_eliminated", bot );
		level thread teamPlayerCardSplash( "callout_destroyed_helicopter_flares", bot );
		level thread teamPlayerCardSplash( "callout_destroyed_little_bird", bot );
		level thread teamPlayerCardSplash( "callout_bombdefused", bot );
		level thread teamPlayerCardSplash( "callout_3xpluskill", bot );

		SetDevDvar( "scr_spam_boteventsplash", "" );	
	}

	if ( getDvar( "scr_spam_ranksplash" ) != "" )
	{
		foreach( player in level.players )
		{
			player thread rankSplash( 5, 2.0 );
		}

		SetDevDvar( "scr_spam_ranksplash", "" );	
	}

	if ( getDvar( "scr_spam_weaponranksplash" ) != "" )
	{
		foreach( player in level.players )
		{
			player thread weaponRankSplash( 5, 2.0 );
		}

		SetDevDvar( "scr_spam_weaponranksplash", "" );	
	}

	if ( getDvar( "scr_show_splash" ) != "" )
	{
		splashName = getDvar( "scr_show_splash" );
		splashValue = 1;
		splashType = tableLookup( "mp/splashTable.csv", 0, splashName, 11 );
		
		if ( splashType == "" || splashType == "none" )
		{
			println( "splash not found in splash table" );
		}
		else
		{
			switch( splashType )
			{
				case "splash":
					foreach( player in level.players )
						player thread maps\mp\gametypes\_hud_message::splashNotify( splashName, splashValue );
					break;
				case "killstreak":
					foreach( player in level.players )
						player thread maps\mp\gametypes\_hud_message::killstreakSplashNotify( splashName, splashValue );
					break;
				case "challenge":
				case "perk_challenge":
					foreach( player in level.players )
					{
						player ch_setState( splashName, 2 );
						player.challengeData[splashName] = 2;
						player thread maps\mp\gametypes\_hud_message::challengeSplashNotify( splashName );
					}
					break;
				case "splooge":
					foreach( player in level.players )
					{
						player thread maps\mp\gametypes\_hud_message::challengeSplashNotify( "ch_marksman_m16" );
						player thread maps\mp\gametypes\_hud_message::killstreakSplashNotify( "uav", 3 );
						player thread maps\mp\gametypes\_hud_message::killstreakSplashNotify( "ac130", 11 );
					}
					break;
				default:
					break;
			}
		}
		SetDevDvar( "scr_show_splash", "" );
	}	

	if ( getDvar( "scr_addlower" ) != "" )
	{
		foreach ( player in level.players )
			player thread testLowerMessage();
		
		SetDevDvar( "scr_addlower", "" );
	}	

	if ( getDvar( "scr_entdebug" ) != "" )
	{
		ents = getEntArray();
		level.entArray = [];
		level.entCounts = [];
		level.entGroups = [];
		for ( index = 0; index < ents.size; index++ )
		{
			classname = ents[index].classname;
			if ( !isSubStr( classname, "_spawn" ) )
			{
				curEnt = ents[index];

				level.entArray[level.entArray.size] = curEnt;
				
				if ( !isDefined( level.entCounts[classname] ) )
					level.entCounts[classname] = 0;
			
				level.entCounts[classname]++;

				if ( !isDefined( level.entGroups[classname] ) )
					level.entGroups[classname] = [];
			
				level.entGroups[classname][level.entGroups[classname].size] = curEnt;
			}
		}
	}
	
	if ( getDvar( "scr_sre" ) != "" )
	{
		assertmsg( "Testing script runtime error" );
		SetDevDvar( "scr_sre", "" );
	}
	
	if ( getDvar( "scr_testmigration" ) != "" )
	{
		SetDevDvar( "scr_testmigration", "" );
		thread maps\mp\gametypes\_hostmigration::Callback_HostMigration();
		thread hostMigrationEndTimer_dev();
	}
	
	if ( getDvar( "scr_show_endgameupdate" ) != "" )
	{
		promotion = ( getDvar( "scr_show_endgameupdate" ) == "2" );
		
		foreach( player in level.players )
			player thread testEndGameUpdate( promotion );
		
		SetDevDvar( "scr_show_endgameupdate", "" );	
	}
	
	if ( getDvar( "scr_goto_spawn" ) != "" )
	{
		if ( getDvar( "scr_goto_spawn" ) == "next" )
			gotoNextSpawn();
		else if ( getDvar( "scr_goto_spawn" ) == "prev" )
			gotoPrevSpawn();
			
		SetDevDvar( "scr_goto_spawn", "" );
	}
	
	if ( getDvar( "scr_showOrigin" ) != "" )
	{
		ent = undefined;
		
		if ( isDefined( level.player ) )
			ent = level.player;
		else if ( isDefined( level.players[0] ) )
			ent = level.players[0];
			
		if ( isDefined( ent ) )
			println( "Player origin - X: " + ent.origin[0] + ", Y: " + ent.origin[1] + ", Z: " + ent.origin[2] );
		else
			println( "NO PLAYER" );
			
		SetDevDvar( "scr_showOrigin", "" );
	}
}

rankSplash( increments, delay )
{
	for( i = 0; i < increments; i++ )
	{
		self thread maps\mp\gametypes\_rank::updateRankAnnounceHUD();
		wait( delay );
	}
}

weaponRankSplash( increments, delay )
{
	for( i = 0; i < increments; i++ )
	{
		self thread maps\mp\gametypes\_rank::updateWeaponRankAnnounceHUD();
		wait( delay );
	}
}

testEndGameUpdate( promotion )
{
	self setClientDvars( "ui_challenge_1_ref", "ch_marksman_ak47",
						 "ui_challenge_2_ref", "ch_ak47_gl",
						 "ui_challenge_3_ref", "ch_ak47_reflex",
						 "ui_challenge_4_ref", "ch_ak47_silencer",
						 "ui_challenge_5_ref", "ch_ak47_acog",
						 "ui_challenge_6_ref", "ch_ak47_fmj",
						 "ui_challenge_7_ref", "ch_ak47_mastery" );

	if ( isDefined( promotion ) && promotion )
		self setClientDvar( "ui_promotion", 1 );
	else
		self setClientDvar( "ui_promotion", 0 );
	
	self closepopupMenu();
	self closeInGameMenu();
	
	self openMenu( game["menu_endgameupdate"] );

	waitTime = 4.0 + min( 7, 3 );
	while ( waitTime )
	{
		wait ( 0.25 );
		waitTime -= 0.25;

		self openMenu( game["menu_endgameupdate"] );
	}
	
	self closeMenu( game["menu_endgameupdate"] );
}

hostMigrationEndTimer_dev()
{
	level endon( "host_migration_begin" );
	wait randomfloat( 20 );
	level notify( "hostmigration_enoughplayers" );
}


testLowerMessage()
{
	self setLowerMessage( "spawn_info", game["strings"]["waiting_to_spawn"], 10 );
	wait ( 3.0 );

	self setLowerMessage( "last_stand", &"PLATFORM_COWARDS_WAY_OUT", undefined, 50 );
	wait ( 3.0 );

	self clearLowerMessage( "last_stand" );
	wait ( 10.0 );

	self clearLowerMessage( "spawn_info" );
}


giveExtraPerks()
{
	if ( !isdefined( self.extraPerks ) )
		return;
	
	perks = getArrayKeys( self.extraPerks );
	
	for ( i = 0; i < perks.size; i++ )
		self givePerk( perks[i], false );
}

xKillsY( attackerName, victimName )
{
	attacker = undefined;
	victim = undefined;
	
	for ( index = 0; index < level.players.size; index++ )
	{
		if ( level.players[index].name == attackerName )
			attacker = level.players[index];
		else if ( level.players[index].name == victimName )
			victim = level.players[index];
	}
	
	if ( !isAlive( attacker ) || !isAlive( victim ) )
		return;
		
	victim thread [[level.callbackPlayerDamage]](
		attacker, // eInflictor The entity that causes the damage.(e.g. a turret)
		attacker, // eAttacker The entity that is attacking.
		500, // iDamage Integer specifying the amount of damage done
		0, // iDFlags Integer specifying flags that are to be applied to the damage
		"MOD_RIFLE_BULLET", // sMeansOfDeath Integer specifying the method of death
		"scar_mp", // sWeapon The weapon number of the weapon used to inflict the damage
		(0,0,0), // vPoint The point the damage is from?
		(0,0,0), // vDir The direction of the damage
		"none", // sHitLoc The location of the hit
		0 // psOffsetTime The time offset for the damage
	);
}


updateMinimapSetting()
{	
	// use 0 for no required map aspect ratio.
	requiredMapAspectRatio = getdvarfloat("scr_requiredMapAspectRatio", 1);
	
	if (!isdefined(level.minimapheight)) {
		SetDevDvar("scr_minimap_height", "0");
		level.minimapheight = 0;
	}
	minimapheight = getdvarfloat("scr_minimap_height");
	if (minimapheight != level.minimapheight)
	{
		if (isdefined(level.minimaporigin)) {
			level.minimapplayer unlink();
			level.minimaporigin delete();
			level notify("end_draw_map_bounds");
		}
		
		if (minimapheight > 0)
		{
			level.minimapheight = minimapheight;
			
			players = getentarray("player", "classname");
			if (players.size > 0)
			{
				player = players[0];
				
				corners = getentarray("minimap_corner", "targetname");
				if (corners.size == 2)
				{
					viewpos = (corners[0].origin + corners[1].origin);
					viewpos = (viewpos[0]*.5, viewpos[1]*.5, viewpos[2]*.5);

					maxcorner = (corners[0].origin[0], corners[0].origin[1], viewpos[2]);
					mincorner = (corners[0].origin[0], corners[0].origin[1], viewpos[2]);
					if (corners[1].origin[0] > corners[0].origin[0])
						maxcorner = (corners[1].origin[0], maxcorner[1], maxcorner[2]);
					else
						mincorner = (corners[1].origin[0], mincorner[1], mincorner[2]);
					if (corners[1].origin[1] > corners[0].origin[1])
						maxcorner = (maxcorner[0], corners[1].origin[1], maxcorner[2]);
					else
						mincorner = (mincorner[0], corners[1].origin[1], mincorner[2]);
					
					viewpostocorner = maxcorner - viewpos;
					viewpos = (viewpos[0], viewpos[1], viewpos[2] + minimapheight);
					
					origin = spawn("script_origin", player.origin);
					
					northvector = (cos(getnorthyaw()), sin(getnorthyaw()), 0);
					eastvector = (northvector[1], 0 - northvector[0], 0);
					disttotop = vectordot(northvector, viewpostocorner);
					if (disttotop < 0)
						disttotop = 0 - disttotop;
					disttoside = vectordot(eastvector, viewpostocorner);
					if (disttoside < 0)
						disttoside = 0 - disttoside;
					
					// extend map bounds to meet the required aspect ratio
					if ( requiredMapAspectRatio > 0 )
					{
						mapAspectRatio = disttoside / disttotop;
						if ( mapAspectRatio < requiredMapAspectRatio )
						{
							incr = requiredMapAspectRatio / mapAspectRatio;
							disttoside *= incr;
							addvec = vecscale( eastvector, vectordot( eastvector, maxcorner - viewpos ) * (incr - 1) );
							mincorner -= addvec;
							maxcorner += addvec;
						}
						else
						{
							incr = mapAspectRatio / requiredMapAspectRatio;
							disttotop *= incr;
							addvec = vecscale( northvector, vectordot( northvector, maxcorner - viewpos ) * (incr - 1) );
							mincorner -= addvec;
							maxcorner += addvec;
						}
					}
					
					if ( level.console )
					{
						aspectratioguess = 16.0/9.0;
						// .8 would be .75 but it needs to be bigger because of safe area
						angleside = 2 * atan(disttoside * .8 / minimapheight);
						angletop = 2 * atan(disttotop * aspectratioguess * .8 / minimapheight);
					}
					else
					{
						aspectratioguess = 4.0/3.0;
						angleside = 2 * atan(disttoside / minimapheight);
						angletop = 2 * atan(disttotop * aspectratioguess / minimapheight);
					}
					if (angleside > angletop)
						angle = angleside;
					else
						angle = angletop;
					
					znear = minimapheight - 1000;
					if (znear < 16) znear = 16;
					if (znear > 10000) znear = 10000;
					
					player playerlinkto(origin);
					origin.origin = viewpos + (0,0,-62);
					origin.angles = (90, getnorthyaw(), 0);
					

					player TakeAllWeapons();
					player _giveWeapon( "defaultweapon_mp" );
					player setclientdvar("cg_drawgun", "0");
					player setclientdvar("cg_draw2d", "0");
					player setclientdvar("cg_drawfps", "0");
					player setclientdvar("fx_enable", "0");
					player setclientdvar("r_fog", "0");
					player setclientdvar("r_highLodDist", "0"); // (turns of lods)
					player setclientdvar("r_znear", znear); // (reduces z-fighting)
					player setclientdvar("r_lodscale", "0");
					player setclientdvar("cg_drawversion", "0");
					player setclientdvar("sm_enable", "1");
					SetDevDvar("player_view_pitch_down", "90");
					SetDevDvar("player_view_pitch_up", "0");
					player setclientdvar("cg_fov", angle);
					player setclientdvar("cg_fovmin", "1");
					
					// hide 3D icons
					if ( isdefined( level.objPoints ) )
					{
						for ( i = 0; i < level.objPointNames.size; i++ )
						{
							if ( isdefined( level.objPoints[level.objPointNames[i]] ) )
								level.objPoints[level.objPointNames[i]] destroy();
						}
						level.objPoints = [];
						level.objPointNames = [];
					}
					
					level.minimapplayer = player;
					level.minimaporigin = origin;
					
					thread drawMiniMapBounds(viewpos, mincorner, maxcorner);
					
					wait .05;
					
					player setplayerangles(origin.angles);
				}
				else
					println("^1Error: There are not exactly 2 \"minimap_corner\" entities in the level.");
			}
			else
				SetDevDvar("scr_minimap_height", "0");
		}
	}
}

vecscale(vec, scalar)
{
	return (vec[0]*scalar, vec[1]*scalar, vec[2]*scalar);
}

drawMiniMapBounds(viewpos, mincorner, maxcorner)
{
	level notify("end_draw_map_bounds");
	level endon("end_draw_map_bounds");
	
	viewheight = (viewpos[2] - maxcorner[2]);
	
	north = (cos(getnorthyaw()), sin(getnorthyaw()), 0);
	
	diaglen = length(mincorner - maxcorner);

	/*diagonal = maxcorner - mincorner;
	side = vecscale(north, vectordot(diagonal, north));
	
	origcorner0 = mincorner;
	origcorner1 = mincorner + side;
	origcorner2 = maxcorner;
	origcorner3 = maxcorner - side;*/
	
	mincorneroffset = (mincorner - viewpos);
	mincorneroffset = vectornormalize((mincorneroffset[0], mincorneroffset[1], 0));
	mincorner = mincorner + vecscale(mincorneroffset, diaglen * 1/800);
	maxcorneroffset = (maxcorner - viewpos);
	maxcorneroffset = vectornormalize((maxcorneroffset[0], maxcorneroffset[1], 0));
	maxcorner = maxcorner + vecscale(maxcorneroffset, diaglen * 1/800);
	
	diagonal = maxcorner - mincorner;
	side = vecscale(north, vectordot(diagonal, north));
	sidenorth = vecscale(north, abs(vectordot(diagonal, north)));
	
	corner0 = mincorner;
	corner1 = mincorner + side;
	corner2 = maxcorner;
	corner3 = maxcorner - side;
	
	toppos = vecscale(mincorner + maxcorner, .5) + vecscale(sidenorth, .51);
	textscale = diaglen * .003;
	
	while(1)
	{
		line(corner0, corner1, (0,1,0));
		line(corner1, corner2, (0,1,0));
		line(corner2, corner3, (0,1,0));
		line(corner3, corner0, (0,1,0));

		/*line(origcorner0, origcorner1, (1,0,0));
		line(origcorner1, origcorner2, (1,0,0));
		line(origcorner2, origcorner3, (1,0,0));
		line(origcorner3, origcorner0, (1,0,0));*/
		
		print3d(toppos, "This Side Up", (1,1,1), 1, textscale);
		
		wait .05;
	}
}

addTestClients()
{
	wait 5;

	for(;;)
	{
		if(getdvarInt("scr_testclients") > 0)
			break;
		wait 1;
	}

//	for ( index = 1; index < 24; index++ )
//		kick( index );

	testclients = getdvarInt("scr_testclients");
	SetDevDvar( "scr_testclients", 0 );
	for(i = 0; i < testclients; i++)
	{
		ent[i] = addtestclient();

		if (!isdefined(ent[i])) {
			println("Could not add test client");
			wait 1;
			continue;
		}
			
		ent[i].pers["isBot"] = true;
		ent[i] TestClient( "autoassign" );
	}
	
	if ( matchMakingGame() )
		setMatchData( "hasBots", true );
	
	// default to not moving or firing
	//SetDevDvar( "testClients_doMove", false );
	//SetDevDvar( "testClients_doAttack", false );

	thread addTestClients();
}


TestClient(team)
{	
	self endon( "disconnect" );

	while(!isdefined(self.pers["team"]))
		wait( 0.05 );

	if ( allowTeamChoice() )
	{
		self notify("menuresponse", game["menu_team"], team);
		wait( 0.5 );
	}
		
	if ( allowClassChoice() )
	{
		class = "class" + randomInt( 5 );		
		self notify("menuresponse", "changeclass", class);
	}

	self waittill_notify_or_timeout( "spawned_player", 0.5 );
	wait( 0.10 );		
}

haveTestClientKillPlayer()
{
	// for testing deathstreaks quickly
	for(;;)
	{
		if( getdvarInt( "scr_testclients_killplayer" ) > 0 )
			break;
		wait 1;
	}

	SetDevDvar( "scr_testclients_killplayer", 0 );

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	bot = getBot( notBot );

	if( isDefined( bot ) )
	{
		notBot thread [[level.callbackPlayerDamage]](
			bot, // eInflictor The entity that causes the damage.(e.g. a turret)
			bot, // eAttacker The entity that is attacking.
			500, // iDamage Integer specifying the amount of damage done
			0, // iDFlags Integer specifying flags that are to be applied to the damage
			"MOD_RIFLE_BULLET", // sMeansOfDeath Integer specifying the method of death
			bot.primaryweapon, // sWeapon The weapon number of the weapon used to inflict the damage
			bot.origin, // vPoint The point the damage is from?
			(0, 0, 0), // vDir The direction of the damage
			"none", // sHitLoc The location of the hit
			0 // psOffsetTime The time offset for the damage
		);
	}

	wait( 1 );
	thread haveTestClientKillPlayer();
}

haveTestClientCallKillstreak()
{
	// for testing killstreaks quickly
	for(;;)
	{
		if( getdvar( "scr_testclients_givekillstreak" ) != "" )
			break;
		wait 1;
	}

	killstreak = GetDvar( "scr_testclients_givekillstreak" );
	SetDevDvar( "scr_testclients_givekillstreak", "" );

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	bot = getBot( notBot );

	if( GetDvarInt( "scr_testclients_givekillstreak_toggleall" ) )
	{
		foreach( player in level.players )
		{
			if( isDefined( player.pers[ "isBot" ] ) && player.pers[ "isBot" ] )
			{
				bot = player;
			}

			if( isDefined( bot ) )
			{
				bot botUseKillstreak( killstreak );
			}
		}
	}
	else if( GetDvarInt( "scr_testclients_givekillstreak_toggleall_sametime" ) )
	{
		foreach( player in level.players )
		{
			if( isDefined( player.pers[ "isBot" ] ) && player.pers[ "isBot" ] )
			{
				bot = player;
			}

			if( isDefined( bot ) )
			{
				bot thread botUseKillstreak( killstreak );
			}
		}
	}
	else
	{
		if( isDefined( bot ) )
		{
			bot botUseKillstreak( killstreak );
		}
	}

	thread haveTestClientCallKillstreak();
}

botUseKillstreak( killstreak ) // self == bot
{
	resetEMPDvar = false;
	EMPTime = undefined;
	if( killstreak == "emp_quick" )
	{
		resetEMPDvar = true;
		EMPTime = GetDvarFloat( "scr_emp_timeout" );
		killstreak = "emp";
		SetDevDvar( "scr_emp_timeout", 1.0 );
	}

	self maps\mp\killstreaks\_killstreaks::giveKillstreak( killstreak );
	wait( 0.1 );

	switch( killstreak )
	{
	case "littlebird_flock":
	case "osprey_gunner":
	case "precision_airstrike":
	case "stealth_airstrike":
		self thread maps\mp\killstreaks\_killstreaks::killstreakUsePressed();
		wait( 1.0 );
		self notify( "confirm_location", level.mapCenter, 0 );
		break;
	case "ims":
		self thread maps\mp\killstreaks\_killstreaks::killstreakUsePressed();
		wait( 1.0 );
		self notify( "place_ims" );
		break;
	case "sentry":
	case "sam_turret":
		self thread maps\mp\killstreaks\_killstreaks::killstreakUsePressed();
		wait( 1.0 );
		self notify( "place_sentry" );
		break;
	case "remote_mg_turret":
		self thread maps\mp\killstreaks\_killstreaks::killstreakUsePressed();
		wait( 1.0 );
		self notify( "place_turret" );
		break;
	case "remote_tank":
		self thread maps\mp\killstreaks\_killstreaks::killstreakUsePressed();
		wait( 1.0 );
		self notify( "place_tank" );
	case "remote_uav":
		self thread maps\mp\killstreaks\_killstreaks::killstreakUsePressed();
		wait( 1.0 );
		self notify( "place_carryRemoteUAV" );
		break;
	case "airdrop_trap":
	case "airdrop_assault":
		result = self maps\mp\killstreaks\_killstreaks::killstreakUsePressed();
		if( !result )
			return;
		wait( 1.0 );
		level thread maps\mp\killstreaks\_airdrop::doFlyBy( self, self.origin, randomFloat( 360 ), killstreak );
		break;
	case "escort_airdrop":
		result = self maps\mp\killstreaks\_killstreaks::killstreakUsePressed();
		if( !result )
			return;
		wait( 1.0 );
		self maps\mp\killstreaks\_escortairdrop::finishSupportEscortUsage( -1, self.origin, randomFloat( 360 ), killstreak );
		break;
	default:
		self thread maps\mp\killstreaks\_killstreaks::killstreakUsePressed();
		break;
	}

	if( resetEMPDvar )
	{
		level thread waitResetDvar( 1.0, "scr_emp_timeout", EMPTime );
	}
}

waitResetDvar( waitTime, dvarName, dvarValue )
{
	wait( waitTime );
	SetDevDvar( dvarName, dvarValue );
}

haveTestClientPlantExplosive()
{
	// for testing bouncing betty quickly
	for(;;)
	{
		if( GetDvar( "scr_testclients_plantexplosive" ) != "" )
			break;
		wait 1;
	}

	explosive = GetDvar( "scr_testclients_plantexplosive" );
	SetDevDvar( "scr_testclients_plantexplosive", "" );

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	bot = getBot( notBot );

	if( isDefined( bot ) )
	{
		trace = bulletTrace( bot.origin + (0, 0, 4), bot.origin - (0, 0, 4), false, bot );
		normal = vectornormalize( trace["normal"] );
		plantAngles = vectortoangles( normal );
		plantAngles += ( 90, 0, 0 );

		switch( explosive )
		{
		case "bouncing_betty":
			mine = maps\mp\gametypes\_weapons::spawnMine( bot.origin, bot, "equipment", plantAngles );
			mine.trigger = spawn( "script_origin", mine.origin + (0,0,25) );
			mine thread maps\mp\gametypes\_weapons::equipmentWatchUse( bot );
			mine.killCamEnt = Spawn( "script_model", mine.origin + ( 0, 0, 5 ) );
			break;

		case "claymore":
			// TODO: need a way to spawn a grenade, because a claymore is a grenade
			//bot.claymorearray = array_removeUndefined( bot.claymorearray );

			//if( bot.claymoreArray.size >= level.maxPerPlayerExplosives )
			//	bot.claymoreArray[0] detonate();

			//claymore = Spawn( "script_model", bot.origin );
			//claymore.angles = bot.angles;
			//claymore SetModel( "weapon_claymore" );
			//bot.claymorearray[ bot.claymorearray.size ] = claymore;
			//claymore.owner = bot;
			//claymore.team = bot.team;
			//claymore.weaponName = "claymore_mp";
			//claymore.trigger = spawn( "script_origin", claymore.origin );

			//level.mines[level.mines.size] = claymore;
			//claymore thread maps\mp\gametypes\_weapons::c4Damage();
			//claymore thread maps\mp\gametypes\_weapons::c4EMPDamage();
			//claymore thread maps\mp\gametypes\_weapons::c4EMPKillstreakWait();
			//claymore thread maps\mp\gametypes\_weapons::claymoreDetonation();
			//claymore thread maps\mp\gametypes\_weapons::equipmentWatchUse( bot );
			//claymore thread maps\mp\gametypes\_weapons::setClaymoreTeamHeadIcon( bot.pers[ "team" ] );
			break;
		}
	}

	thread haveTestClientPlantExplosive();
}

haveTestClientThrowDeployableVest()
{
	// for testing bouncing betty quickly
	for(;;)
	{
		if( GetDvarInt( "scr_testclients_throw_deployable_vest" ) > 0 )
			break;
		wait 1;
	}

	SetDevDvar( "scr_testclients_throw_deployable_vest", 0 );

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	bot = getBot( notBot );

	if( isDefined( bot ) )
	{
		trace = bulletTrace( bot.origin + (0, 0, 4), bot.origin - (0, 0, 4), false, bot );
		box = maps\mp\killstreaks\_deployablebox::createBoxForPlayer( "deployable_vest", trace[ "position" ], bot );
		wait 0.05;
		box thread maps\mp\killstreaks\_deployablebox::box_setActive();
	}

	thread haveTestClientThrowDeployableVest();
}

addTestClientJuggernaut()
{
	// for testing juggernauts quickly
	for(;;)
	{
		if( GetDvar( "scr_testclients_jugg" ) != "" )
			break;
		wait 1;
	}

	juggType = GetDvar( "scr_testclients_jugg" );
	SetDevDvar( "scr_testclients_jugg", "" );

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	bot = getBot( notBot );

	if( isDefined( bot ) )
		bot thread maps\mp\killstreaks\_juggernaut::giveJuggernaut( juggType );

	thread addTestClientJuggernaut();
}

addTestClientSpawnPoint()
{
	// let you pick the spot where the test client will spawn, so you can put the test client in one particular spot
	for(;;)
	{
		if( GetDvarInt( "scr_testclients_spawnpoint" ) > 0 )
			break;
		wait 1;
	}

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	if( !IsDefined( notBot ) )
	{
		SetDevDvar( "scr_testclients_spawnpoint", 0 );
		thread addTestClientSpawnPoint();
		return;
	}
	if( !IsAlive( notBot ) )
	{
		SetDevDvar( "scr_testclients_spawnpoint", 0 );
		thread addTestClientSpawnPoint();
		return;
	}

	// show a marker in the ground
	markerPos = BulletTrace( notBot GetEye(), notBot.origin + ( AnglesToForward( notBot GetPlayerAngles() ) * 10000 ), false, notBot );
	marker = Spawn( "script_model", markerPos[ "position" ] );
	//markerPos = notBot.origin + ( AnglesToForward( notBot.angles ) * 200 );
	//marker = Spawn( "script_model", markerPos );
	marker SetModel( "projectile_bouncing_betty_grenade" );
	
	// keep it on the ground
	trace = BulletTrace( marker.origin + ( 0, 0, 50 ), marker.origin + ( 0, 0, -100 ), false, marker );
	marker.origin = trace[ "position" ];
	
	marker thread showFX();

	while( GetDvarInt( "scr_testclients_spawnpoint" ) > 0 )
	{
		markerPos = BulletTrace( notBot GetEye(), notBot.origin + ( AnglesToForward( notBot GetPlayerAngles() ) * 10000 ), false, marker );
		marker.origin = markerPos[ "position" ];
		//markerPos = notBot.origin + ( AnglesToForward( notBot.angles ) * 200 );
		//marker.origin = markerPos;

		// keep it on the ground
		trace = BulletTrace( marker.origin + ( 0, 0, 50 ), marker.origin + ( 0, 0, -100 ), false, marker );
		marker.origin = trace[ "position" ];

		if( notBot UseButtonPressed() )
		{
			ent = addtestclient();

			if( !IsDefined( ent ) )
			{
				PrintLn("Could not add test client");
				wait 1;
				continue;
			}

			ent.pers[ "isBot" ] = true;
			ent thread TestClient( getOtherTeam( notBot.team ) );
			ent waittill_notify_or_timeout( "spawned_player", 3.0 );
			ent setOrigin( marker.origin );

			if( matchMakingGame() )
				setMatchData( "hasBots", true );

			break;
		}

		wait( 0.05 );
	}

	marker delete();
	SetDevDvar( "scr_testclients_spawnpoint", 0 );
	thread addTestClientSpawnPoint();
}

showFX()
{
	self endon( "death" );
	wait( 1.0 );
	PlayFXOnTag( level.devSpawnFXid, self, "tag_fx" );
}

warpEnemies()
{
	// warp enemies to the host
	for(;;)
	{
		if( getdvarInt( "scr_warpenemies" ) > 0 )
			break;
		wait 1;
	}

	SetDevDvar( "scr_warpenemies", 0 );

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	foreach( player in level.players )
	{
		if( level.teambased )
		{
			if( player.team != notBot.team )
			{
				player setOrigin( notBot.origin );
			}
		}
		else
			player setOrigin( notBot.origin );
	}

	thread warpEnemies();
}

warpFriendlies()
{
	// warp friendlies to the host
	for(;;)
	{
		if( getdvarInt( "scr_warpfriendlies" ) > 0 )
			break;
		wait 1;
	}

	SetDevDvar( "scr_warpfriendlies", 0 );

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	foreach( player in level.players )
	{
		if( level.teambased )
		{
			if( player.team == notBot.team )
			{
				player setOrigin( notBot.origin );
			}
		}
		else
			player setOrigin( notBot.origin );
	}

	thread warpFriendlies();
}

giveEquipment()
{
	for(;;)
	{
		if( GetDvar( "scr_giveequipment" ) != "" )
			break;
		wait 1;
	}

	equipment = GetDvar( "scr_giveequipment" );

	if( IsDefined( equipment ) )
	{
		foreach( player in level.players )
		{
			currentWeapon = player GetCurrentOffhand();
			player TakeWeapon( currentWeapon );
			player SetOffhandPrimaryClass( "other" );
			equipment = maps\mp\perks\_perks::validatePerk( 1, equipment );
			player givePerk( equipment, true );
		}
	}

	SetDevDvar( "scr_giveequipment", "" );

	thread giveEquipment();
}

giveSpecialGrenade()
{
	for(;;)
	{
		if( GetDvar( "scr_givespecialgrenade" ) != "" )
			break;
		wait 1;
	}

	equipment = GetDvar( "scr_givespecialgrenade" );

	if( IsDefined( equipment ) )
	{
		foreach( player in level.players )
		{
			weaponList = player GetWeaponsListOffhands();
			foreach( weapon in weaponList )
			{
				switch( weapon )
				{
				case "flash_grenade_mp":
				case "concussion_grenade_mp":
				case "smoke_grenade_mp":
				case "flare_mp":
				case "trophy_mp":
				case "scrambler_mp":
				case "portable_radar_mp":
				case "emp_grenade_mp":
					player TakeWeapon( weapon );
					break;
				}
			}
			
			if ( equipment == "flash_grenade_mp" )
				player SetOffhandSecondaryClass( "flash" );
			else if ( equipment == "smoke_grenade_mp" || equipment == "concussion_grenade_mp" )
				player SetOffhandSecondaryClass( "smoke" );	
			else 
				player SetOffhandSecondaryClass( "flash" );

			switch( equipment )
			{
			case "smoke_grenade_mp":
				player giveWeapon( equipment );
				player setWeaponAmmoClip( equipment, 1 );
				break;
			case "flash_grenade_mp":
				player giveWeapon( equipment );
				player setWeaponAmmoClip( equipment, 2 );
				break;
			case "concussion_grenade_mp":
				player giveWeapon( equipment );
				player setWeaponAmmoClip( equipment, 2 );
				break;
			case "emp_grenade_mp":
				player giveWeapon( equipment );
				player setWeaponAmmoClip( equipment, 1 );
				break;
			case "specialty_portable_radar":
				player givePerk( equipment, false );
				player setWeaponAmmoClip( "portable_radar_mp", 1 );
				break;
			case "specialty_scrambler":
				player givePerk( equipment, false );
				player setWeaponAmmoClip( "scrambler_mp", 1 );
				break;
			case "specialty_tacticalinsertion":
				player givePerk( equipment, false );
				player setWeaponAmmoClip( "flare_mp", 1 );
				break;
			case "trophy_mp":
				player givePerk( equipment, false );
				player setWeaponAmmoClip( equipment, 1 );
				break;
			default:
				player giveWeapon( equipment );
				player setWeaponAmmoClip( equipment, 1 );
				break;
			}
		}
	}

	SetDevDvar( "scr_givespecialgrenade", "" );

	thread giveSpecialGrenade();
}

initForWeaponTests()
{
	if ( isDefined( self.initForWeaponTests ) )
		return;
		
	self.initForWeaponTests = true;
	
	self thread changeCamoListener();
	self thread thirdPersonToggle();
	
	self waittill ( "death" );
	self.initForWeaponTests = undefined;
}


setTestWeapon( weaponName )
{
	if ( !isDefined( level.baseWeaponList[weaponName] ) )
	{
		self iPrintLnBold( "Unknown weapon: " + weaponName );
		return;
	}

	self notify ( "new_test_weapon" );	
	self.baseWeapon = weaponName;
	self thread weaponChangeListener();
	
	self updateTestWeapon();
}


thirdPersonToggle()
{
	self endon ( "death" );
	self notifyOnPlayerCommand( "dpad_down", "+actionslot 2" );
	
	thirdPersonElem = self createFontString( "default", 1.5 );
	thirdPersonElem setPoint( "TOPRIGHT", "TOPRIGHT", 0, 72 + 260 );
	thirdPersonElem setText( "3rd Person: " + getDvarInt( "camera_thirdPerson" ) + "  [{+actionslot 2}]" );
	self thread destroyOnDeath( thirdPersonElem );
	
	for ( ;; )
	{
		self waittill( "dpad_down" );

		setDvar( "camera_thirdPerson", !getDvarInt( "camera_thirdPerson" ) );
		
		thirdPersonElem setText( "3rd Person: " + getDvarInt( "camera_thirdPerson" ) + "  [{+actionslot 2}]" );
	}
}


changeCamoListener()
{
	self endon ( "death" );
	self notifyOnPlayerCommand( "dpad_up", "+actionslot 1" );
	
	camoList = [];
	
	for ( rowIndex = 0; tableLookupByRow( "mp/camoTable.csv", rowIndex, 1 ) != ""; rowIndex++ )
		camoList[camoList.size] = tableLookupByRow( "mp/camoTable.csv", rowIndex, 1 );

	self.camoIndex = 0;
	
	camoElem = self createFontString( "default", 1.5 );
	camoElem setPoint( "TOPRIGHT", "TOPRIGHT", 0, 52 + 260 );
	camoElem setText( "Camo: " + tableLookup( "mp/camoTable.csv", 0, self.camoIndex, 1 ) + "  [{+actionslot 1}]" );
	self thread destroyOnDeath( camoElem );
	
	for ( ;; )
	{
		self waittill( "dpad_up" );
		
		self.camoIndex++;
		if ( self.camoIndex > (camoList.size - 1) )
			self.camoIndex = 0;
		
		camoElem setText( "Camo: " + tableLookup( "mp/camoTable.csv", 0, self.camoIndex, 1 ) + "  [{+actionslot 1}]" );
		self updateTestWeapon();
	}
}


weaponChangeListener()
{
	self endon ( "death" );
	self endon ( "new_test_weapon" );
	
	self notifyOnPlayerCommand( "next_weapon", "weapnext" );

	if ( !isDefined( self.weaponElem ) )
	{
		self.weaponElem = self createFontString( "default", 1.5 );
		self.weaponElem setPoint( "TOPRIGHT", "TOPRIGHT", 0, 32 + 260 );
		self thread destroyOnDeath( self.weaponElem );
	}
	self.variantIndex = 0;

	self.weaponElem setText( "Weapon: " + level.baseWeaponList[self.baseWeapon].variants[self.variantIndex] + "  [{weapnext}]" );

	for ( ;; )
	{
		self waittill ( "next_weapon" );
		
		self.variantIndex++;
		if ( self.variantIndex > (level.baseWeaponList[self.baseWeapon].variants.size - 1) )
			self.variantIndex = 0;
		
		self.weaponElem setText( "Weapon: " + level.baseWeaponList[self.baseWeapon].variants[self.variantIndex] + "  [{weapnext}]" );
		self updateTestWeapon();
	}	
}


destroyOnDeath( hudElem )
{
	self waittill ( "death" );
	
	hudElem destroy();
}

updateTestWeapon()
{
	self takeAllWeapons();
	
	wait ( 0.05 );
	
	weaponName = level.baseWeaponList[self.baseWeapon].variants[self.variantIndex];
	
	self _giveWeapon( weaponName, int(self.camoIndex) );
	self switchToWeapon( weaponName );
	self giveMaxAmmo( weaponName );
}

watchNoClip()
{
	// when a player is spawned thread them
	level waittill( "player_spawned", player );
	if( !IsDefined( player.pers[ "isBot" ] ) )
	{
		player NotifyOnPlayerCommand( "ls_down_noclip", "+breath_sprint" );
		player NotifyOnPlayerCommand( "dpad_down_noclip", "+actionslot 2" );
		player thread playerNoClip();
	}
	level thread watchNoClip();
}

playerNoClip() // self == player
{
	self endon( "disconnect" );
	self endon( "death" );

	self.devNoClipLS = false;
	self.devNoClipDpad = false;
	self thread watchNoClipLS();
	self thread watchNoClipDpad();

	while( true )
	{
		if( GetDvarInt( "scr_devnoclip" ) > 0 )
		{
			if( self.devNoClipLS && self.devNoClipDpad )		
				self noclip();
		}

		wait( 0.2 );
	}
}

watchNoClipLS() // self == player
{
	self endon( "disconnect" );
	self endon( "death" );

	while( true )
	{
		self waittill( "ls_down_noclip" );

		self.devNoClipLS = true;

		wait( 0.2 );

		self.devNoClipLS = false;
	}
}

watchNoClipDpad() // self == player
{
	self endon( "disconnect" );
	self endon( "death" );

	while( true )
	{
		self waittill( "dpad_down_noclip" );

		self.devNoClipDpad = true;

		wait( 0.2 );

		self.devNoClipDpad = false;
	}
}

watchUFO()
{
	// when a player is spawned thread them
	level waittill( "player_spawned", player );
	if( !IsDefined( player.pers[ "isBot" ] ) )
	{
		player NotifyOnPlayerCommand( "ls_down_ufo", "+breath_sprint" );
		player NotifyOnPlayerCommand( "dpad_up_ufo", "+actionslot 1" );
		player thread playerUFO();
	}
	level thread watchUFO();
}

playerUFO() // self == player
{
	self endon( "disconnect" );
	self endon( "death" );

	self.devUFOLS = false;
	self.devUFODpad = false;
	self thread watchUFOLS();
	self thread watchUFODpad();

	while( true )
	{
		if( GetDvarInt( "scr_devufo" ) > 0 )
		{
			if( self.devUFOLS && self.devUFODpad )		
				self ufo();
		}

		wait( 0.2 );
	}
}

watchUFOLS() // self == player
{
	self endon( "disconnect" );
	self endon( "death" );

	while( true )
	{
		self waittill( "ls_down_ufo" );

		self.devUFOLS = true;

		wait( 0.2 );

		self.devUFOLS = false;
	}
}

watchUFODpad() // self == player
{
	self endon( "disconnect" );
	self endon( "death" );

	while( true )
	{
		self waittill( "dpad_up_ufo" );

		self.devUFODpad = true;

		wait( 0.2 );

		self.devUFODpad = false;
	}
}

printPerks()
{
	while( true )
	{
		if( GetDvarInt( "scr_printperks" ) > 0 )
			break;
		wait 1;
	}

	foreach( player in level.players )
	{
		// just players
		if( GetDvarInt( "scr_printperks" ) == 1 && !isDefined( player.pers[ "isBot" ] ) )
		{
			PrintLn( player.name );
			foreach( perk, value in player.perks )
			{
				PrintLn( perk );
			}
		}
		// just bots
		else if( GetDvarInt( "scr_printperks" ) == 2 && isDefined( player.pers[ "isBot" ] ) && player.pers[ "isBot" ] )
		{
			PrintLn( player.name );
			foreach( perk, value in player.perks )
			{
				PrintLn( perk );
			}
		}
	}

	SetDevDvar( "scr_printperks", 0 );
	thread printPerks();
}

devGivePerks()
{
	while( true )
	{
		if( GetDvar( "scr_devgiveperk" ) != "" )
			break;
		wait 1;
	}

	perk = GetDvar( "scr_devgiveperk" );
	foreach( player in level.players )
	{
		player thread givePerk( perk, false );
	}

	SetDevDvar( "scr_devgiveperk", "" );

	thread devGivePerks();
}

devClearPerks()
{
	while( true )
	{
		if( GetDvarInt( "scr_devclearperks" ) > 0 )
			break;
		wait 1;
	}

	SetDevDvar( "scr_devclearperks", 0 );

	foreach( player in level.players )
	{
		player thread _clearPerks();
	}

	thread devClearPerks();
}

devHurtPlayer()
{
	while( true )
	{
		if( GetDvarInt( "scr_devhurtplayer" ) > 0 )
			break;
		wait 1;
	}

	damageVal = GetDvarInt( "scr_devhurtplayer" );

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	if( damageVal >= 100 )
	{
		damageVal = notBot.health - 1;
	}

	bot = getBot( notBot );

	if( IsDefined( bot ) )
	{
		notBot thread [[level.callbackPlayerDamage]](
			bot, // eInflictor The entity that causes the damage.(e.g. a turret)
			bot, // eAttacker The entity that is attacking.
			damageVal, // iDamage Integer specifying the amount of damage done
			0, // iDFlags Integer specifying flags that are to be applied to the damage
			"MOD_RIFLE_BULLET", // sMeansOfDeath Integer specifying the method of death
			bot.primaryweapon, // sWeapon The weapon number of the weapon used to inflict the damage
			bot.origin, // vPoint The point the damage is from?
			(0, 0, 0), // vDir The direction of the damage
			"none", // sHitLoc The location of the hit
			0 // psOffsetTime The time offset for the damage
			);
	}

	SetDevDvar( "scr_devhurtplayer", 0 );

	thread devHurtPlayer();
}

devHurtPlayerReset()
{
	while( true )
	{
		if( GetDvarInt( "scr_devhurtplayerreset" ) > 0 )
			break;
		wait 1;
	}

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	notBot.health = 100;

	SetDevDvar( "scr_devhurtplayerreset", 0 );

	thread devHurtPlayerReset();
}

devHurtPlayerDirectional()
{
	while( true )
	{
		if( GetDvar( "scr_devhurtplayerdirectional" ) != "" )
			break;
		wait 1;
	}

	bot = undefined;
	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	bot = getBot( notBot );

	if( IsDefined( bot ) )
	{
		switch( GetDvar( "scr_devhurtplayerdirectional" ) )
		{
		case "right100":
			bot SetOrigin( notbot.origin + ( 0, 0, 5 ) + ( AnglesToRight( notbot.angles ) * 100 ) );
			break;
		case "left100":
			bot SetOrigin( notbot.origin + ( 0, 0, 5 ) + ( ( AnglesToRight( notbot.angles ) * 100 ) * -1 ) );
			break;
		case "center100":
			bot SetOrigin( notbot.origin + ( 0, 0, 5 ) + ( AnglesToForward( notbot.angles ) * 100 ) );
			break;
		case "right600":
			bot SetOrigin( notbot.origin + ( 0, 0, 5 ) + ( AnglesToRight( notbot.angles ) * 600 ) );
			break;
		case "left600":
			bot SetOrigin( notbot.origin + ( 0, 0, 5 ) + ( ( AnglesToRight( notbot.angles ) * 600 ) * -1 ) );
			break;
		case "center600":
			bot SetOrigin( notbot.origin + ( 0, 0, 5 ) + ( AnglesToForward( notbot.angles ) * 600 ) );
			break;
		}

		wait( 0.1 );
		MagicBullet( "iw5_usp45_mp", bot.origin + ( 0, 0, 35 ), notbot.origin + ( 0, 0, 35 ), bot );
	}

	SetDevDvar( "scr_devhurtplayerdirectional", "" );

	thread devHurtPlayerDirectional();
}

getBot( notBot )
{
	bot = undefined;
	foreach( player in level.players )
	{
		if( IsDefined( player.pers[ "isBot" ] ) && player.pers[ "isBot" ] )
		{
			bot = player;
		}

		if( IsDefined( bot ) && IsDefined( notBot ) )
		{
			if( level.teambased )
			{ 
				if( bot.team != notBot.team )
					break;
			}
			else // ffa
				break;
		}
	}

	// if there is no bot, then make one
	if( !IsDefined( bot ) )
	{
		SetDevDvar( "scr_testclients", 1 );
		wait( 3.0 );

		foreach( player in level.players )
		{
			if( IsDefined( player.pers[ "isBot" ] ) && player.pers[ "isBot" ] )
			{
				bot = player;
			}

			if( IsDefined( bot ) )
			{
				if( level.teambased )
				{ 
					if( bot.team != notBot.team )
						break;
				}
				else // ffa
					break;
			}
		}
	}

	return bot;
}

devChangeTimeLimit()
{
	while( true )
	{
		if( GetDvarFloat( "scr_devchangetimelimit" ) > 0.0 )
			break;
		wait 1;
	}

	timelimit = GetDvarFloat( "scr_devchangetimelimit" ) / 60;
	level.startTime = getTime();
	gameMode = "scr_" + level.gametype + "_timelimit";
	level.watchDvars[ gameMode ].value = timelimit;
	SetDevDvar( gameMode, timelimit );

	SetDevDvar( "scr_devchangetimelimit", 0 );

	thread devChangeTimeLimit();
}

devWeaponXP()
{
	prev = GetDvarInt( "scr_devweaponxp" );
	while( true )
	{
		if( GetDvarInt( "scr_devweaponxp" ) != prev )
			break;
		wait 1;
	}

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	switch( GetDvarInt( "scr_devweaponxp" ) )
	{
	case 0:
		notBot notify( "devStopWeaponXP" );
		if( IsDefined( notBot.devWeaponXPBar ) )
			notBot.devWeaponXPBar destroyElem();
		if( IsDefined( notBot.devWeaponXPBarText ) )
			notBot.devWeaponXPBarText destroyElem();
		break;
	case 1:
		notBot.devWeaponXPBar = notBot createPrimaryProgressBar( 200, 250 );
		notBot.devWeaponXPBarText = notBot createPrimaryProgressBarText( 200, 250 );
		notBot.devWeaponXPBarText setPoint("RIGHT", undefined, level.primaryProgressBarTextX - 150, level.primaryProgressBarTextY + 250 );
		notBot.devWeaponXPBarText SetText( "weapon xp" );
		notBot thread devWatchWeaponXP();
		break;
	}

	thread devWeaponXP();
}

devWatchWeaponXP() // self == player (host only for now)
{
	level endon( "game_ended" );
	self endon( "devStopWeaponXP" );

	// we just want the weapon name up to the first underscore
	weapon = self GetCurrentWeapon();
	weaponTokens = StrTok( weapon, "_" );
	
	if ( weaponTokens[0] == "iw5" )
		weaponName = weaponTokens[0] + "_" + weaponTokens[1];
	else if ( weaponTokens[0] == "alt" )
		weaponName = weaponTokens[1] + "_" + weaponTokens[2];
	else
		weaponName = weaponTokens[0];

	if( weaponTokens[0] == "gl" )
		weaponName = weaponTokens[1];
	
	prevXP = self maps\mp\gametypes\_rank::getWeaponRankXP( weaponName );

	while( true )
	{
		weapon = self GetCurrentWeapon();
		if( weapon != "none" && !self isJuggernaut() )
		{
			weaponInvType = weaponInventoryType( weapon );

			if( weaponInvType == "primary" || weaponInvType == "altmode" )
			{
				weapon = self GetCurrentWeapon();
				weaponTokens = StrTok( weapon, "_" );

				if ( weaponTokens[0] == "iw5" )
					weaponName = weaponTokens[0] + "_" + weaponTokens[1];
				else if ( weaponTokens[0] == "alt" )
					weaponName = weaponTokens[1] + "_" + weaponTokens[2];
				else
					weaponName = weaponTokens[0];

				if( weaponTokens[0] == "gl" )
					weaponName = weaponTokens[1];

				currXP = self maps\mp\gametypes\_rank::getWeaponRankXP( weaponName );

				if( prevXP != currXP )
				{
					rank = maps\mp\gametypes\_rank::getWeaponRankForXp( currXP, weaponName );
					minXP = maps\mp\gametypes\_rank::getWeaponRankInfoMinXP( rank );
					nextXP = maps\mp\gametypes\_rank::getWeaponRankInfoXPAmt( rank );
					barFrac = ( currXP - minXP ) / nextXP;
					if( barFrac > 1.0 )
						barFrac = 1.0;
					self.devWeaponXPBar updateBar( barFrac, 0 );
					prevXP = currXP;

					self.devWeaponXPBarText SetText( weapon + " xp:" + currXP + " xp to next:" + nextXP + " rank:" + ( rank + 1 ) );
				}    
			}
		}

		wait ( 0.05 );
	}
}

devPlayerXP()
{
	prev = GetDvarInt( "scr_devplayerxp" );
	while( true )
	{
		if( GetDvarInt( "scr_devplayerxp" ) != prev )
			break;
		wait 1;
	}

	// get the first player and make them the "host"
	notBot = level.players[0];
	foreach( player in level.players )
	{
		if( !isDefined( player.pers[ "isBot" ] ) || ( IsDefined( player.pers[ "isBot" ] )&& !player.pers[ "isBot" ] ) )
		{
			notBot = player;
			break;
		}
	}

	switch( GetDvarInt( "scr_devplayerxp" ) )
	{
	case 0:
		notBot notify( "devStopPlayerXP" );
		if( IsDefined( notBot.devPlayerXPBar ) )
			notBot.devPlayerXPBar destroyElem();
		if( IsDefined( notBot.devPlayerXPBarText ) )
			notBot.devPlayerXPBarText destroyElem();
		break;
	case 1:
		notBot.devPlayerXPBar = notBot createPrimaryProgressBar( 200, 200 );
		notBot.devPlayerXPBarText = notBot createPrimaryProgressBarText( 200, 200 );
		notBot.devPlayerXPBarText SetText( "player xp" );
		notBot thread devWatchPlayerXP();
		break;
	}

	thread devPlayerXP();
}

devWatchPlayerXP() // self == player (host only for now)
{
	level endon( "game_ended" );
	self endon( "devStopPlayerXP" );

	prevXP = self maps\mp\gametypes\_rank::getRankXP();

	while( true )
	{
		currXP = self maps\mp\gametypes\_rank::getRankXP();

		if( prevXP != currXP )
		{
			rank = maps\mp\gametypes\_rank::getRankForXp( currXP );
			minXP = maps\mp\gametypes\_rank::getRankInfoMinXP( rank );
			nextXP = maps\mp\gametypes\_rank::getRankInfoXPAmt( rank );
			barFrac = ( currXP - minXP ) / nextXP;
			if( barFrac > 1.0 )
				barFrac = 1.0;
			self.devPlayerXPBar updateBar( barFrac, 0 );
			prevXP = currXP;

			self.devPlayerXPBarText SetText( "player xp:" + currXP + " xp to next:" + nextXP + " rank:" + ( rank + 1 ) );
		}    

		wait ( 0.05 );
	}
}

devScriptMoversDebugDraw()
{
	white =	( 1, 1, 1 );
	red =	( 1, 0, 0 );
	green = ( 0, 1, 0 );
	blue =	( 0, 0, 1 );

	while( true )
	{
		if( GetDvarInt( "scr_devScriptMoversDebugDraw" ) > 0 )
		{
			// get all script_models, script_origins, what ever else is a script mover, and show them
			script_models = GetEntArray( "script_model", "classname" );
			script_origins = GetEntArray( "script_origin", "classname" );

			foreach( ent in script_models )
			{
				Line( ent.origin, ent.origin + ( AnglesToForward( ent.angles ) * 10 ), red );
				Line( ent.origin, ent.origin + ( AnglesToRight( ent.angles ) * 10 ), green );
				Line( ent.origin, ent.origin + ( AnglesToUp( ent.angles ) * 10 ), blue );

				if( IsDefined( ent.targetname ) )
					Print3d( ent.origin, ent.targetname );
			}

			foreach( ent in script_origins )
			{
				Line( ent.origin, ent.origin + ( AnglesToForward( ent.angles ) * 10 ), red );
				Line( ent.origin, ent.origin + ( AnglesToRight( ent.angles ) * 10 ), green );
				Line( ent.origin, ent.origin + ( AnglesToUp( ent.angles ) * 10 ), blue );

				if( IsDefined( ent.targetname ) )
				{
					color = white;
					alpha = 1;
					scale = 1;
					switch( ent.targetname )
					{
					case "airstrikeheight":
						color = red;
						scale = 3;
						break;
					case "heli_start":
					case "heli_leave":
						color = green;
						scale = 3;
						break;
					}

					originString = "(" + ent.origin[0] + ", " + ent.origin[1] + ", " + ent.origin[2] + ")";
					Print3d( ent.origin, ent.targetname + originString, color, alpha, scale );
				}
			}
		}
		wait 0.05;
	}
}

devHeliPathDebugDraw()
{
	white =	( 1, 1, 1 );
	red =	( 1, 0, 0 );
	green = ( 0, 1, 0 );
	blue =	( 0, 0, 1 );

	textColor = white;
	textAlpha = 1;
	textScale = 1;

	maxDrawTime = 10;
	drawTime = maxDrawTime;
	
	originTextOffset = ( 0, 0, -30 );

	endonMsg = "devStopHeliPathsDebugDraw";

	while( true )
	{
		if( GetDvarInt( "scr_devHeliPathsDebugDraw" ) > 0 )
		{
			// get all script_models, script_origins, what ever else is a script mover, and show them
			script_origins = GetEntArray( "script_origin", "classname" );

			foreach( ent in script_origins )
			{
				if( IsDefined( ent.targetname ) )
				{
					switch( ent.targetname )
					{
					case "heli_start":
						textColor = blue;
						textAlpha = 1;
						textScale = 3;
						break;
					case "heli_loop_start":
						textColor = green;
						textAlpha = 1;
						textScale = 3;
						break;
					case "heli_attack_area":
						textColor = red;
						textAlpha = 1;
						textScale = 3;
						break;
					case "heli_leave":
						textColor = white;
						textAlpha = 1;
						textScale = 3;
						break;
					}

					switch( ent.targetname )
					{
					case "heli_start":
					case "heli_loop_start":
					case "heli_attack_area":
					case "heli_leave":
						// only call this thread every N time
						if( drawTime == maxDrawTime )
							ent thread drawPath( textColor, white, textAlpha, textScale, originTextOffset, drawTime, endonMsg );

						ent drawOriginLines();
						ent drawTargetNameText( textColor, textAlpha, textScale );
						ent drawOriginText( textColor, textAlpha, textScale, originTextOffset );
						break;
					}
				}
			}

			drawTime -= 0.05;
			if( drawTime < 0 )
				drawTime = maxDrawTime;
		}
		
		if( GetDvarInt( "scr_devHeliPathsDebugDraw" ) == 0 )
		{
			level notify( endonMsg );
			drawTime = maxDrawTime;
		}

		wait 0.05;
	}
}

drawOriginLines()
{
	red =	( 1, 0, 0 );
	green = ( 0, 1, 0 );
	blue =	( 0, 0, 1 );

	Line( self.origin, self.origin + ( AnglesToForward( self.angles ) * 10 ), red );
	Line( self.origin, self.origin + ( AnglesToRight( self.angles ) * 10 ), green );
	Line( self.origin, self.origin + ( AnglesToUp( self.angles ) * 10 ), blue );
}

drawTargetNameText( textColor, textAlpha, textScale, textOffset )
{
	if( !IsDefined( textOffset ) )
		textOffset = ( 0, 0, 0 );
	Print3d( self.origin + textOffset, self.targetname, textColor, textAlpha, textScale );
}

drawOriginText( textColor, textAlpha, textScale, textOffset )
{
	if( !IsDefined( textOffset ) )
		textOffset = ( 0, 0, 0 );
	originString = "(" + self.origin[0] + ", " + self.origin[1] + ", " + self.origin[2] + ")";
	Print3d( self.origin + textOffset, originString, textColor, textAlpha, textScale );
}

drawSpeedAccelText( textColor, textAlpha, textScale, textOffset )
{
	if( IsDefined( self.script_airspeed ) )
		Print3d( self.origin + ( 0, 0, textOffset[2] * 2 ), "script_airspeed:" + self.script_airspeed, textColor, textAlpha, textScale );
	if( IsDefined( self.script_accel ) )
		Print3d( self.origin + ( 0, 0, textOffset[2] * 3 ), "script_accel:" + self.script_accel, textColor, textAlpha, textScale );
}

drawPath( lineColor, textColor, textAlpha, textScale, textOffset, drawTime, endonMsg ) // self == starting node
{
	level endon( endonMsg );

	// draw lines from origin to origin until there is no target
	ent = self;
	entFirstTarget = ent.targetname;

	while( IsDefined( ent.target ) )
	{
		entTarget = GetEnt( ent.target, "targetname" );
		ent thread drawPathSegment( entTarget, lineColor, textColor, textAlpha, textScale, textOffset, drawTime, endonMsg );

		// store the first target because we have the loop nodes that will always have a target
		if( ent.targetname == "heli_loop_start" )
			entFirstTarget = ent.target;
		else if( ent.target == entFirstTarget )
			break;

		ent = entTarget;
		wait( 0.05 );
	}
}

drawPathSegment( entTarget, lineColor, textColor, textAlpha, textScale, textOffset, drawTime, endonMsg )
{
	level endon( endonMsg );

	// Di$oRdER was here. /
	while( drawTime > 0 )
	{
		Line( self.origin, entTarget.origin, lineColor );
		self drawSpeedAccelText( textColor, textAlpha, textScale, textOffset );
		drawTime -= 0.05;
		wait( 0.05 );
	}
}

devPredatorMissileDebugDraw()
{
	white =	( 1, 1, 1 );
	red =	( 1, 0, 0 );
	green = ( 0, 1, 0 );
	blue =	( 0, 0, 1 );

	textColor = white;
	textAlpha = 1;
	textScale = 1;

	maxDrawTime = 10;
	drawTime = maxDrawTime;

	originTextOffset = ( 0, 0, -30 );

	endonMsg = "devStopPredatorMissileDebugDraw";

	while( true )
	{
		if( GetDvarInt( "scr_devPredatorMissileDebugDraw" ) > 0 )
		{
			script_origins = GetEntArray( "remoteMissileSpawn", "targetname" );

			foreach( ent in script_origins )
			{
				textColor = red;
				textAlpha = 1;
				textScale = 1;

				if( drawTime == maxDrawTime )
					ent thread drawPath( textColor, white, textAlpha, textScale, originTextOffset, drawTime, endonMsg );

				ent drawOriginLines();
				ent drawTargetNameText( textColor, textAlpha, textScale );
				ent drawOriginText( textColor, textAlpha, textScale, originTextOffset );
			}

			drawTime -= 0.05;
			if( drawTime < 0 )
				drawTime = maxDrawTime;
		}

		if( GetDvarInt( "scr_devPredatorMissileDebugDraw" ) == 0 )
		{
			level notify( endonMsg );
			drawTime = maxDrawTime;
		}

		wait 0.05;
	}
}

devPrintDailyWeeklyChallenges()
{
	while( true )
	{
		if( GetDvar( "scr_devPrintDailyWeeklyChallenges" ) != "" )
			break;
		wait 1;
	}

	foreach( player in level.players )
	{
		if( IsDefined( player.pers[ "isBot" ] ) && player.pers[ "isBot" ] )
			continue;

		// Di$oRdER
		if( GetDvar( "scr_devPrintDailyWeeklyChallenges" ) == "daily" )
		{
			PrintLn( player.name );
			foreach( challenge, value in player.challengedata )
			{
				if( IsSubStr( challenge, "_daily" ) && value )
					PrintLn( "Daily: " + challenge );
			}
		}
		else if( GetDvar( "scr_devPrintDailyWeeklyChallenges" ) == "weekly" )
		{
			PrintLn( player.name );
			foreach( challenge, value in player.challengedata )
			{
				if( IsSubStr( challenge, "_weekly" ) && value )
					PrintLn( "Weekly: " + challenge );
			}
		}
	}

	SetDevDvar( "scr_devPrintDailyWeeklyChallenges", "" );
	thread devPrintDailyWeeklyChallenges();
}
#/

onPlayerConnect()
{
	for(;;)
	{
		level waittill( "connected", player );

		player thread updateReflectionProbe();
	}
}

showSpawnpoint( spawnpoint, classname, color )
{
	/#
	center = spawnpoint.origin;
	forward = anglestoforward(spawnpoint.angles);
	right = anglestoright(spawnpoint.angles);

	forward  *= 16;
	right  *= 16;

	a = center + forward - right;
	b = center + forward + right;
	c = center - forward + right;
	d = center - forward - right;
	
	thread lineUntilNotified(a, b, color, 0);
	thread lineUntilNotified(b, c, color, 0);
	thread lineUntilNotified(c, d, color, 0);
	thread lineUntilNotified(d, a, color, 0);

	thread lineUntilNotified(a, a + (0, 0, 72), color, 0);
	thread lineUntilNotified(b, b + (0, 0, 72), color, 0);
	thread lineUntilNotified(c, c + (0, 0, 72), color, 0);
	thread lineUntilNotified(d, d + (0, 0, 72), color, 0);

	a = a + (0, 0, 72);
	b = b + (0, 0, 72);
	c = c + (0, 0, 72);
	d = d + (0, 0, 72);
	
	thread lineUntilNotified(a, b, color, 0);
	thread lineUntilNotified(b, c, color, 0);
	thread lineUntilNotified(c, d, color, 0);
	thread lineUntilNotified(d, a, color, 0);

	center = center + (0, 0, 36);
	arrow_forward = anglestoforward(spawnpoint.angles);
	arrowhead_forward = anglestoforward(spawnpoint.angles);
	arrowhead_right = anglestoright(spawnpoint.angles);

	arrow_forward  *= 32;
	arrowhead_forward  *= 24;
	arrowhead_right *= 8;	
	a = center + arrow_forward;
	b = center + arrowhead_forward - arrowhead_right;
	c = center + arrowhead_forward + arrowhead_right;
	
	thread lineUntilNotified(center, a, (1, 1, 1), 0);
	thread lineUntilNotified(a, b, (1, 1, 1), 0);
	thread lineUntilNotified(a, c, (1, 1, 1), 0);
	
	foreach ( alternate in spawnpoint.alternates )
	{
		thread lineUntilNotified( spawnpoint.origin, alternate, color, 0);
	}
	
	thread print3DUntilNotified(spawnpoint.origin + (0, 0, 72), classname, color, 1, 1);
	#/
}

showSpawnpoints()
{
	/#
	if ( isdefined( level.spawnpoints ) )
	{
		foreach ( spawnpoint in level.spawnpoints )
		{
			showSpawnpoint( spawnpoint, spawnpoint.classname, (1,1,1) );
		}
	}
	if ( isdefined( level.extraspawnpointsused ) )
	{
		foreach ( spawnpoint in level.extraspawnpointsused )
		{
			showSpawnpoint( spawnpoint, spawnpoint.fakeclassname, (.5,.5,.5) );
		}
	}
	#/
}

print3DUntilNotified(origin, text, color, alpha, scale)
{
	/#
	level endon("hide_spawnpoints");
	
	for(;;)
	{
		print3d(origin, text, color, alpha, scale);
		wait .05;
	}
	#/
}

lineUntilNotified(start, end, color, depthTest)
{
	/#
	level endon("hide_spawnpoints");
	
	for(;;)
	{
		line(start, end, color, depthTest);
		wait .05;
	}
	#/
}

hideSpawnpoints()
{
	/#
	level notify("hide_spawnpoints");
	#/
}

updateReflectionProbe()
{
	/#
	for(;;)
	{
		if ( getDvarInt( "debug_reflection" ) == 1 )
		{
			if ( !isDefined( self.debug_reflectionobject ) )
			{
				self.debug_reflectionobject = spawn( "script_model", self geteye() + ( ( anglestoforward( self.angles ) * 100 ) ) );
				self.debug_reflectionobject setmodel( "test_sphere_silver" );
				self.debug_reflectionobject.origin = self geteye() + ( ( anglestoforward( self getplayerangles() ) * 100 ) );
				self thread reflectionProbeButtons();
			}
		}
		else if ( getDvarInt( "debug_reflection" ) == 0 )
		{
			if ( isDefined( self.debug_reflectionobject ) )
				self.debug_reflectionobject delete();
		}

		wait( 0.05 );
	}
	#/
}

reflectionProbeButtons()
{
	/#
	offset = 100;
	offsetinc = 50;

	while ( getDvarInt( "debug_reflection" ) == 1 )
	{
		if ( self buttonpressed( "BUTTON_X" ) )
			offset += offsetinc;
		if ( self buttonpressed( "BUTTON_Y" ) )
			offset -= offsetinc;
		if ( offset > 1000 )
			offset = 1000;
		if ( offset < 64 )
			offset = 64;

		self.debug_reflectionobject.origin = self GetEye() + ( ( AnglesToForward( self GetPlayerAngles() ) * offset ) );

		wait .05;
	}
	#/
}

gotoNextSpawn()
{
	/#
	if ( isDefined( level.spawnpoints ) )
	{
		foreach( player in level.players )
		{
			if ( !isDefined( player.debug_next_spawnpoint ) ) 
				player.debug_next_spawnpoint = 0;			
			
			player.spawnPos = level.spawnpoints[player.debug_next_spawnpoint].origin;
			player spawn( level.spawnpoints[player.debug_next_spawnpoint].origin, level.spawnpoints[player.debug_next_spawnpoint].angles );
			
			player.debug_prev_spawnpoint = player.debug_next_spawnpoint-1;
			if ( player.debug_prev_spawnpoint < 0 )
				player.debug_prev_spawnpoint = level.spawnpoints.size-1;
			player.debug_next_spawnpoint++;
			if ( player.debug_next_spawnpoint == level.spawnpoints.size )
				player.debug_next_spawnpoint = 0;	
		}	
	}	
	#/
}

gotoPrevSpawn()
{
	/#
	if ( isDefined( level.spawnpoints ) )
	{
		foreach( player in level.players )
		{
			if ( !isDefined( player.debug_prev_spawnpoint ) )
				player.debug_prev_spawnpoint = level.spawnpoints.size-1;		
	
			player.spawnPos = level.spawnpoints[player.debug_prev_spawnpoint].origin;
			player spawn( level.spawnpoints[player.debug_prev_spawnpoint].origin, level.spawnpoints[player.debug_prev_spawnpoint].angles );
			
			player.debug_next_spawnpoint = player.debug_prev_spawnpoint+1;
			if ( player.debug_next_spawnpoint == level.spawnpoints.size )
				player.debug_next_spawnpoint = 0;
			player.debug_prev_spawnpoint--;
			if ( player.debug_prev_spawnpoint < 0 )
				player.debug_prev_spawnpoint = level.spawnpoints.size-1;	
		}	
	}	
	#/
}