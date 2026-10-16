#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;

//	if ( game["state"] == "postgame" && game["teamScores"][attacker.team] > game["teamScores"][level.otherTeam[attacker.team]] )

ICONSIZE = 20;

init()
{
	if ( !isDefined( level.defconMode ) || level.defconMode == false )
		return;
	
	if ( !isDefined( game["defcon"] ) )
		game["defcon"] = 4;

	makeDvarServerInfo( "scr_defcon", game["defcon"] );
	
	/# setDevDvarIfUninitialized( "scr_defconStreak", 10 );	#/
		
	level.defconStreakAdd[5] = 0;
	level.defconStreakAdd[4] = 0;
	level.defconStreakAdd[3] = -1;
	level.defconStreakAdd[2] = -1;
	level.defconStreakAdd[1] = -1;

	level.defconPointMod[5] = 1;
	level.defconPointMod[4] = 1;
	level.defconPointMod[3] = 1;
	level.defconPointMod[2] = 1;
	level.defconPointMod[1] = 2;
		
	updateDefcon( game["defcon"] );
	thread defconKillstreakThread();
}

defconKillstreakWait( streakCount )
{
	for ( ;; )
	{
		level waittill ( "player_got_killstreak_" + streakCount, player );		
		level notify ( "defcon_killstreak", streakCount, player );
	}
}


defconKillstreakThread()
{
	level endon ( "game_ended" );

	requiredKillCount = 10;

	/#
	requiredKillCount = getDvarInt( "scr_defconStreak" );
	#/

	level thread defconKillstreakWait( requiredKillCount );
	level thread defconKillstreakWait( requiredKillCount - 1 );
	level thread defconKillstreakWait( requiredKillCount - 2 );

	level thread defconKillstreakWait( (requiredKillCount * 2) );
	level thread defconKillstreakWait( (requiredKillCount * 2) - 1 );
	level thread defconKillstreakWait( (requiredKillCount * 2) - 2 );

	level thread defconKillstreakWait( (requiredKillCount * 3) );
	level thread defconKillstreakWait( (requiredKillCount * 3) - 1 );
	level thread defconKillstreakWait( (requiredKillCount * 3) - 2 );

	for ( ;; )
	{
		level waittill ( "defcon_killstreak", streakCount, changingPlayer );

		if ( game["defcon"] <= 1 )
			continue;

		if ( (streakCount % requiredKillCount) == requiredKillCount - 2 )
		{
			foreach ( player in level.players )
			{
				if ( !isAlive( player ) )
					continue;
					
				player thread maps\mp\gametypes\_hud_message::playerCardSplashNotify( "two_from_defcon", changingPlayer );
			}
		}
		else if ( (streakCount % requiredKillCount) == requiredKillCount - 1 )
		{
			foreach ( player in level.players )
			{
				if ( !isAlive( player ) )
					continue;
					
				player thread maps\mp\gametypes\_hud_message::playerCardSplashNotify( "one_from_defcon", changingPlayer );
			}
		}
		else
		{
			updateDefcon( game["defcon"] - 1, changingPlayer, streakCount );
		}
	}
}


updateDefcon( newDefcon, changingPlayer, streakCount )
{
	newDefcon = int( newDefcon );
	oldDefcon = game["defcon"];
	game["defcon"] = newDefcon;

//	level.killStreakMod = level.defconStreakAdd[newDefcon];
	level.objectivePointsMod = level.defconPointMod[newDefcon];

	setDvar( "scr_defcon", game["defcon"] );
	
	//isdefined used for variable init
	if( isDefined( changingPlayer ) )
		changingPlayer notify( "changed_defcon" );

	if ( newDefcon == oldDefcon )
		return;

	if ( game["defcon"] == 3 && isDefined( changingPlayer ) )
	{
		changingPlayer maps\mp\killstreaks\_killstreaks::giveKillstreak( "airdrop_mega" );
		changingPlayer thread maps\mp\gametypes\_hud_message::splashNotify( "caused_defcon" , streakCount );
	}
		
	foreach ( player in level.players )
	{
		if ( isAlive( player ) )
		{
			player thread maps\mp\gametypes\_hud_message::defconSplashNotify( game["defcon"], newDefcon < oldDefcon );
			if ( isDefined( changingPlayer ) )
				player thread maps\mp\gametypes\_hud_message::playerCardSplashNotify( "changed_defcon", changingPlayer );
		}
	}
}