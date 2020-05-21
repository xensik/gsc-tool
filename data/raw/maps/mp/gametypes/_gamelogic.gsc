#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

FACTION_REF_COL 					= 0;
FACTION_NAME_COL 					= 1;
FACTION_SHORT_NAME_COL 				= 1;
FACTION_WIN_GAME_COL 				= 3; 
FACTION_WIN_ROUND_COL 				= 4;
FACTION_MISSION_ACCOMPLISHED_COL 	= 5;
FACTION_ELIMINATED_COL 				= 6;
FACTION_FORFEITED_COL 				= 7;
FACTION_ICON_COL 					= 8;
FACTION_HUD_ICON_COL 				= 9;
FACTION_VOICE_PREFIX_COL 			= 10;
FACTION_SPAWN_MUSIC_COL 			= 11;
FACTION_WIN_MUSIC_COL 				= 12;
FACTION_COLOR_R_COL 				= 13;
FACTION_COLOR_G_COL 				= 14;
FACTION_COLOR_B_COL 				= 15;

// when a team leaves completely, that team forfeited, team left wins round, ends game
onForfeit( team )
{
	if ( isDefined( level.forfeitInProgress ) )
		return;

	level endon( "abort_forfeit" );			//end if the team is no longer in forfeit status

	level thread forfeitWaitforAbort();

	level.forfeitInProgress = true;
	
	// in 1v1 DM, give players time to change teams
	if ( !level.teambased && level.players.size > 1 )
		wait 10;
	
	level.forfeit_aborted = false;
	forfeit_delay = 20.0;						//forfeit wait, for switching teams and such
	matchForfeitTimer( forfeit_delay );
	
	endReason = &"";
	if ( !isDefined( team ) )
	{
		endReason = game["strings"]["players_forfeited"];
		winner = level.players[0];
	}
	else if ( team == "allies" )
	{
		endReason = game["strings"]["allies_forfeited"];
		winner = "axis";
	}
	else if ( team == "axis" )
	{
		endReason = game["strings"]["axis_forfeited"];
		winner = "allies";
	}
	else
	{
		//shouldn't get here
		assertEx( isdefined( team ), "Forfeited team is not defined" );
		assertEx( 0, "Forfeited team " + team + " is not allies or axis" );
		winner = "tie";
	}
	//exit game, last round, no matter if round limit reached or not
	level.forcedEnd = true;
	
	if ( isPlayer( winner ) )
		logString( "forfeit, win: " + winner getXuid() + "(" + winner.name + ")" );
	else
		logString( "forfeit, win: " + winner + ", allies: " + game["teamScores"]["allies"] + ", opfor: " + game["teamScores"]["axis"] );
	thread endGame( winner, endReason );
}


forfeitWaitforAbort()
{
	level endon ( "game_ended" );
	
	level waittill ( "abort_forfeit" );
	
	level.forfeit_aborted = true;
	if( IsDefined( level.matchForfeitTimer ) )
		level.matchForfeitTimer destroyElem();
	if( IsDefined( level.matchForfeitText ) )
		level.matchForfeitText destroyElem();
}

matchForfeitTimer_Internal( countTime, matchForfeitTimer )
{
	waittillframeend; // wait till cleanup of previous forfeit timer if multiple happen at once

	level endon( "match_forfeit_timer_beginning" );
	// make sure we aren't in grace period or else the 'match resumes in' text will overlap the forfeit text
	while ( countTime > 0 && !level.gameEnded && !level.forfeit_aborted && !level.inGracePeriod )
	{
		matchForfeitTimer thread maps\mp\gametypes\_hud::fontPulse( level );
		wait ( matchForfeitTimer.inFrames * 0.066 );
		matchForfeitTimer setValue( countTime );
		countTime--;
		wait ( 1 - (matchForfeitTimer.inFrames * 0.066) );
	}
}

matchForfeitTimer( duration )
{
	level notify( "match_forfeit_timer_beginning" );

	matchForfeitText = createServerFontString( "objective", 1.5 );
	matchForfeitText setPoint( "CENTER", "CENTER", 0, -40 );
	matchForfeitText.sort = 1001;
	matchForfeitText setText( game["strings"]["opponent_forfeiting_in"] ); // "Enemies forfeiting in:"
	matchForfeitText.foreground = false;
	matchForfeitText.hidewheninmenu = true;

	matchForfeitTimer = createServerFontString( "hudbig", 1 );
	matchForfeitTimer setPoint( "CENTER", "CENTER", 0, 0 );
	matchForfeitTimer.sort = 1001;
	matchForfeitTimer.color = (1,1,0);
	matchForfeitTimer.foreground = false;
	matchForfeitTimer.hidewheninmenu = true;

	matchForfeitTimer maps\mp\gametypes\_hud::fontPulseInit();

	countTime = int( duration );

	level.matchForfeitTimer = matchForfeitTimer;
	level.matchForfeitText = matchForfeitText;

	matchForfeitTimer_Internal( countTime, matchForfeitTimer );

	matchForfeitTimer destroyElem();
	matchForfeitText destroyElem();
}

default_onDeadEvent( team )
{
	if ( team == "allies" )
	{
		iPrintLn( game["strings"]["allies_eliminated"] );

		logString( "team eliminated, win: opfor, allies: " + game["teamScores"]["allies"] + ", opfor: " + game["teamScores"]["axis"] );
		
		thread endGame( "axis", game["strings"]["allies_eliminated"] );
	}
	else if ( team == "axis" )
	{
		iPrintLn( game["strings"]["axis_eliminated"] );

		logString( "team eliminated, win: allies, allies: " + game["teamScores"]["allies"] + ", opfor: " + game["teamScores"]["axis"] );

		thread endGame( "allies", game["strings"]["axis_eliminated"] );
	}
	else
	{
		logString( "tie, allies: " + game["teamScores"]["allies"] + ", opfor: " + game["teamScores"]["axis"] );

		if ( level.teamBased )
			thread endGame( "tie", game["strings"]["tie"] );
		else
			thread endGame( undefined, game["strings"]["tie"] );
	}
}


default_onOneLeftEvent( team )
{
	if ( level.teamBased )
	{		
		assert( team == "allies" || team == "axis" );
		
		lastPlayer = getLastLivingPlayer( team );
		lastPlayer thread giveLastOnTeamWarning();
	}
	else
	{
		lastPlayer = getLastLivingPlayer();
		
		logString( "last one alive, win: " + lastPlayer.name );
		thread endGame( lastPlayer, &"MP_ENEMIES_ELIMINATED" );
	}

	return true;
}


default_onTimeLimit()
{
	winner = undefined;
	level.finalKillCam_winner = "none";
	
	if ( level.teamBased )
	{
		if ( game["teamScores"]["allies"] == game["teamScores"]["axis"] )
			winner = "tie";
		else if ( game["teamScores"]["axis"] > game["teamScores"]["allies"] )
		{
			level.finalKillCam_winner = "axis";
			winner = "axis";
		}
		else
		{
			level.finalKillCam_winner = "allies";
			winner = "allies";
		}

		logString( "time limit, win: " + winner + ", allies: " + game["teamScores"]["allies"] + ", opfor: " + game["teamScores"]["axis"] );
	}
	else
	{
		winner = maps\mp\gametypes\_gamescore::getHighestScoringPlayer();

		if ( isDefined( winner ) )
			logString( "time limit, win: " + winner.name );
		else
			logString( "time limit, tie" );
	}
	
	thread endGame( winner, game["strings"]["time_limit_reached"] );
}


default_onHalfTime()
{
	winner = undefined;
	
	thread endGame( "halftime", game["strings"]["time_limit_reached"] );
}


forceEnd()
{
	if ( level.hostForcedEnd || level.forcedEnd )
		return;

	winner = undefined;
	level.finalKillCam_winner = "none";

	if ( level.teamBased )
	{
		if ( game["teamScores"]["allies"] == game["teamScores"]["axis"] )
			winner = "tie";
		else if ( game["teamScores"]["axis"] > game["teamScores"]["allies"] )
		{
			level.finalKillCam_winner = "axis";
			winner = "axis";
		}
		else
		{
			level.finalKillCam_winner = "allies";
			winner = "allies";
		}
		logString( "host ended game, win: " + winner + ", allies: " + game["teamScores"]["allies"] + ", opfor: " + game["teamScores"]["axis"] );
	}
	else
	{
		winner = maps\mp\gametypes\_gamescore::getHighestScoringPlayer();
		if ( isDefined( winner ) )
			logString( "host ended game, win: " + winner.name );
		else
			logString( "host ended game, tie" );
	}
	
	level.forcedEnd = true;
	level.hostForcedEnd = true;
	
	if ( level.splitscreen )
		endString = &"MP_ENDED_GAME";
	else
		endString = &"MP_HOST_ENDED_GAME";
	
	thread endGame( winner, endString );
}


onScoreLimit()
{	
	scoreText = game["strings"]["score_limit_reached"];	
	winner = undefined;
	
	level.finalKillCam_winner = "none";	
	
	if ( level.teamBased )
	{
		if ( game["teamScores"]["allies"] == game["teamScores"]["axis"] )
			winner = "tie";
		else if ( game["teamScores"]["axis"] > game["teamScores"]["allies"] )
		{
			winner = "axis";
			level.finalKillCam_winner = "axis";	
		}
		else
		{
			winner = "allies";
			level.finalKillCam_winner = "allies";	
		}
		logString( "scorelimit, win: " + winner + ", allies: " + game["teamScores"]["allies"] + ", opfor: " + game["teamScores"]["axis"] );
	}
	else
	{
		winner = maps\mp\gametypes\_gamescore::getHighestScoringPlayer();
		if ( isDefined( winner ) )
			logString( "scorelimit, win: " + winner.name );
		else
			logString( "scorelimit, tie" );
	}
	
	thread endGame( winner, scoreText );
	return true;
}


updateGameEvents()
{
	if ( matchMakingGame() && !level.inGracePeriod )
	{
		if ( level.teamBased )
		{
			// if allies disconnected, and axis still connected, axis wins round and game ends to lobby
			if ( level.teamCount["allies"] < 1 && level.teamCount["axis"] > 0 && game["state"] == "playing" )
			{
				//allies forfeited
				thread onForfeit( "allies" );
				return;
			}
			
			// if axis disconnected, and allies still connected, allies wins round and game ends to lobby
			if ( level.teamCount["axis"] < 1 && level.teamCount["allies"] > 0 && game["state"] == "playing" )
			{
				//axis forfeited
				thread onForfeit( "axis" );
				return;
			}
	
			if ( level.teamCount["axis"] > 0 && level.teamCount["allies"] > 0 )
			{
				level.forfeitInProgress = undefined;
				level notify( "abort_forfeit" );
			}
		}
		else
		{
			if ( level.teamCount["allies"] + level.teamCount["axis"] == 1 && level.maxPlayerCount > 1 )
			{
				thread onForfeit();
				return;
			}

			if ( level.teamCount["axis"] + level.teamCount["allies"] > 1 )
			{
				level.forfeitInProgress = undefined;
				level notify( "abort_forfeit" );
			}
		}
	}

	if ( !getGametypeNumLives() && (!isDefined( level.disableSpawning ) || !level.disableSpawning) )
		return;
		
	if ( !gameHasStarted() ) 
		return;
	
	if ( level.inGracePeriod )
		return;

	if ( level.teamBased )
	{
		livesCount["allies"] = level.livesCount["allies"];
		livesCount["axis"] = level.livesCount["axis"];

		if ( isDefined( level.disableSpawning ) && level.disableSpawning )
		{
			livesCount["allies"] = 0;
			livesCount["axis"] = 0;
		}
		
		// if both allies and axis were alive and now they are both dead in the same instance
		if ( !level.aliveCount["allies"] && !level.aliveCount["axis"] && !livesCount["allies"] && !livesCount["axis"] )
		{
			return [[level.onDeadEvent]]( "all" );
		}

		// if allies were alive and now they are not
		if ( !level.aliveCount["allies"] && !livesCount["allies"] )
		{
			return [[level.onDeadEvent]]( "allies" );
		}

		// if axis were alive and now they are not
		if ( !level.aliveCount["axis"] && !livesCount["axis"] )
		{
			return [[level.onDeadEvent]]( "axis" );
		}

		// one ally left
		if ( level.aliveCount["allies"] == 1 && !livesCount["allies"] )
		{
			if ( !isDefined( level.oneLeftTime["allies"] ) )
			{
				level.oneLeftTime["allies"] = getTime();
				return [[level.onOneLeftEvent]]( "allies" );
			}
		}

		// one axis left
		if ( level.aliveCount["axis"] == 1 && !livesCount["axis"] )
		{
			if ( !isDefined( level.oneLeftTime["axis"] ) )
			{
				level.oneLeftTime["axis"] = getTime();
				return [[level.onOneLeftEvent]]( "axis" );
			}
		}
	}
	else
	{
		// everyone is dead
		if ( (!level.aliveCount["allies"] && !level.aliveCount["axis"]) && (!level.livesCount["allies"] && !level.livesCount["axis"]) )
		{
			return [[level.onDeadEvent]]( "all" );
		}

		livePlayers = getPotentialLivingPlayers();
		
		if ( livePlayers.size == 1 )
		{
			return [[level.onOneLeftEvent]]( "all" );
		}
	}
}


waittillFinalKillcamDone()
{
	if ( !IsDefined( level.finalKillCam_winner ) )
		return false;
		
	//*level waittill( "final_killcam_done" );

	return true;
}


timeLimitClock_Intermission( waitTime )
{
	setGameEndTime( getTime() + int(waitTime*1000) );
	clockObject = spawn( "script_origin", (0,0,0) );
	clockObject hide();
	
	if ( waitTime >= 10.0 )
		wait ( waitTime - 10.0 );
		
	for ( ;; )
	{
		clockObject playSound( "ui_mp_timer_countdown" );
		wait ( 1.0 );
	}	
}


waitForPlayers( maxTime )
{
	endTime = gettime() + maxTime * 1000 - 200;
	
	if ( level.teamBased )
		while( (!level.hasSpawned[ "axis" ] || !level.hasSpawned[ "allies" ]) && gettime() < endTime )
			wait ( 0.05 );
	else
		while ( level.maxPlayerCount < 2 && gettime() < endTime )
			wait ( 0.05 );
}


prematchPeriod()
{
	level endon( "game_ended" );

	if ( level.prematchPeriod > 0 )
	{
		if ( level.console )
		{
			thread matchStartTimer( "match_starting_in", level.prematchPeriod );
			wait ( level.prematchPeriod );
		}
		else
		{
			matchStartTimerPC();
		}
	}
	else
	{
		matchStartTimerSkip();
	}
	
	for ( index = 0; index < level.players.size; index++ )
	{
		level.players[index] freezeControlsWrapper( false );
		level.players[index] enableWeapons();

		hintMessage = getObjectiveHintText( level.players[index].pers["team"] );
		if ( !isDefined( hintMessage ) || !level.players[index].hasSpawned )
			continue;

		level.players[index] setClientDvar( "scr_objectiveText", hintMessage );
		level.players[index] thread maps\mp\gametypes\_hud_message::hintMessage( hintMessage );
	}

	if ( game["state"] != "playing" )
		return;
}


gracePeriod()
{
	level endon("game_ended");
	
	while ( level.inGracePeriod > 0 )
	{
		wait ( 1.0 );
		level.inGracePeriod--;
	}

	//wait ( level.gracePeriod );
	
	level notify ( "grace_period_ending" );
	wait ( 0.05 );
	
	gameFlagSet( "graceperiod_done" );
	level.inGracePeriod = false;
	
	if ( game["state"] != "playing" )
		return;
	
	if ( getGametypeNumLives() )
	{
		// Players on a team but without a weapon show as dead since they can not get in this round
		players = level.players;
		
		for ( i = 0; i < players.size; i++ )
		{
			player = players[i];
			
			if ( !player.hasSpawned && player.sessionteam != "spectator" && !isAlive( player ) )
				player.statusicon = "hud_status_dead";
		}
	}
	
	level thread updateGameEvents();
}


updateWinStats( winner )
{
	if ( !winner rankingEnabled() )
		return;
	
	winner maps\mp\gametypes\_persistence::statAdd( "losses", -1 );
	
	println( "setting winner: " + winner maps\mp\gametypes\_persistence::statGet( "wins" ) );
	winner maps\mp\gametypes\_persistence::statAdd( "wins", 1 );
	winner updatePersRatio( "winLossRatio", "wins", "losses" );
	winner maps\mp\gametypes\_persistence::statAdd( "currentWinStreak", 1 );
	
	cur_win_streak = winner maps\mp\gametypes\_persistence::statGet( "currentWinStreak" );
	if ( cur_win_streak > winner maps\mp\gametypes\_persistence::statGet( "winStreak" ) )
		winner maps\mp\gametypes\_persistence::statSet( "winStreak", cur_win_streak );
	
	winner maps\mp\gametypes\_persistence::statSetChild( "round", "win", true );
	winner maps\mp\gametypes\_persistence::statSetChild( "round", "loss", false );
}


updateLossStats( loser )
{
	if ( !loser rankingEnabled() )
		return;
	
	loser maps\mp\gametypes\_persistence::statAdd( "losses", 1 );
	loser updatePersRatio( "winLossRatio", "wins", "losses" );
	loser maps\mp\gametypes\_persistence::statSetChild( "round", "loss", true );
}


updateTieStats( loser )
{	
	if ( !loser rankingEnabled() )
		return;
	
	loser maps\mp\gametypes\_persistence::statAdd( "losses", -1 );
	
	loser maps\mp\gametypes\_persistence::statAdd( "ties", 1 );
	loser updatePersRatio( "winLossRatio", "wins", "losses" );
	loser maps\mp\gametypes\_persistence::statSet( "currentWinStreak", 0 );	
}


updateWinLossStats( winner )
{
	if ( privateMatch() )
		return;
		
	if ( !wasLastRound() )
		return;
		
	players = level.players;

	if ( !isDefined( winner ) || ( isDefined( winner ) && isString( winner ) && winner == "tie" ) )
	{
		foreach ( player in level.players )
		{
			if ( isDefined( player.connectedPostGame ) )
				continue;

			if ( level.hostForcedEnd && player isHost() )
			{
				player maps\mp\gametypes\_persistence::statSet( "currentWinStreak", 0 );
				continue;
			}
				
			updateTieStats( player );
		}		
	} 
	else if ( isPlayer( winner ) )
	{
		if ( level.hostForcedEnd && winner isHost() )
		{
			winner maps\mp\gametypes\_persistence::statSet( "currentWinStreak", 0 );
			return;
		}
				
		updateWinStats( winner );
	}
	else if ( isString( winner ) )
	{
		foreach ( player in level.players )
		{
			if ( isDefined( player.connectedPostGame ) )
				continue;

			if ( level.hostForcedEnd && player isHost() )
			{
				player maps\mp\gametypes\_persistence::statSet( "currentWinStreak", 0 );
				continue;
			}

			if ( winner == "tie" )
				updateTieStats( player );
			else if ( player.pers["team"] == winner )
				updateWinStats( player );
			else
				player maps\mp\gametypes\_persistence::statSet( "currentWinStreak", 0 );
		}
	}
}


freezePlayerForRoundEnd( delay )
{
	self endon ( "disconnect" );
	self clearLowerMessages();
	
	if ( !isDefined( delay ) )
		delay = 0.066;
	
	self closepopupMenu();
	self closeInGameMenu();
	
	wait ( delay );
	self freezeControlsWrapper( true );
//	self disableWeapons();
}


updateMatchBonusScores( winner )
{
	if ( !game["timePassed"] )
		return;

	if ( !matchMakingGame() )
		return;

	if ( !getTimeLimit() || level.forcedEnd )
	{
		gameLength = getTimePassed() / 1000;		
		// cap it at 20 minutes to avoid exploiting
		gameLength = min( gameLength, 1200 );
	}
	else
	{
		gameLength = getTimeLimit() * 60;
	}
		
	if ( level.teamBased )
	{
		if ( winner == "allies" )
		{
			winningTeam = "allies";
			losingTeam = "axis";
		}
		else if ( winner == "axis" )
		{
			winningTeam = "axis";
			losingTeam = "allies";
		}
		else
		{
			winningTeam = "tie";
			losingTeam = "tie";
		}

		if ( winningTeam != "tie" )
		{
			winnerScale = maps\mp\gametypes\_rank::getScoreInfoValue( "win" );
			loserScale = maps\mp\gametypes\_rank::getScoreInfoValue( "loss" );
			setWinningTeam( winningTeam );
		}
		else
		{
			winnerScale = maps\mp\gametypes\_rank::getScoreInfoValue( "tie" );
			loserScale = maps\mp\gametypes\_rank::getScoreInfoValue( "tie" );
		}
		
		foreach ( player in level.players )
		{
			if ( isDefined( player.connectedPostGame ) )
				continue;
			
			if ( !player rankingEnabled() )
				continue;
			
			if ( player.timePlayed["total"] < 1 || player.pers["participation"] < 1 )
			{
				player thread maps\mp\gametypes\_rank::endGameUpdate();
				continue;
			}
	
			// no bonus for hosts who force ends
			if ( level.hostForcedEnd && player isHost() )
				continue;

			spm = player maps\mp\gametypes\_rank::getSPM();				
			if ( winningTeam == "tie" )
			{
				playerScore = int( (winnerScale * ((gameLength/60) * spm)) * (player.timePlayed["total"] / gameLength) );
				player thread giveMatchBonus( "tie", playerScore );
				player.matchBonus = playerScore;
			}
			else if ( isDefined( player.pers["team"] ) && player.pers["team"] == winningTeam )
			{
				playerScore = int( (winnerScale * ((gameLength/60) * spm)) * (player.timePlayed["total"] / gameLength) );
				player thread giveMatchBonus( "win", playerScore );
				player.matchBonus = playerScore;
			}
			else if ( isDefined(player.pers["team"] ) && player.pers["team"] == losingTeam )
			{
				playerScore = int( (loserScale * ((gameLength/60) * spm)) * (player.timePlayed["total"] / gameLength) );
				player thread giveMatchBonus( "loss", playerScore );
				player.matchBonus = playerScore;
			}
		}
	}
	else
	{
		if ( isDefined( winner ) )
		{
			winnerScale = maps\mp\gametypes\_rank::getScoreInfoValue( "win" );
			loserScale = maps\mp\gametypes\_rank::getScoreInfoValue( "loss" );
		}
		else
		{
			winnerScale = maps\mp\gametypes\_rank::getScoreInfoValue( "tie" );
			loserScale = maps\mp\gametypes\_rank::getScoreInfoValue( "tie" );
		}
		
		foreach ( player in level.players )
		{
			if ( isDefined( player.connectedPostGame ) )
				continue;
			
			if ( player.timePlayed["total"] < 1 || player.pers["participation"] < 1 )
			{
				player thread maps\mp\gametypes\_rank::endGameUpdate();
				continue;
			}
			
			spm = player maps\mp\gametypes\_rank::getSPM();

			isWinner = false;
			for ( pIdx = 0; pIdx < min( level.placement["all"].size, 3 ); pIdx++ )
			{
				if ( level.placement["all"][pIdx] != player )
					continue;
				isWinner = true;				
			}
			
			if ( isWinner )
			{
				playerScore = int( (winnerScale * ((gameLength/60) * spm)) * (player.timePlayed["total"] / gameLength) );
				player thread giveMatchBonus( "win", playerScore );
				player.matchBonus = playerScore;
			}
			else
			{
				playerScore = int( (loserScale * ((gameLength/60) * spm)) * (player.timePlayed["total"] / gameLength) );
				player thread giveMatchBonus( "loss", playerScore );
				player.matchBonus = playerScore;
			}
		}
	}
}


giveMatchBonus( scoreType, score )
{
	self endon ( "disconnect" );

	level waittill ( "give_match_bonus" );
	
	self maps\mp\gametypes\_rank::giveRankXP( scoreType, score );
	//logXPGains();
	
	self maps\mp\gametypes\_rank::endGameUpdate();
}


setXenonRanks( winner )
{
	players = level.players;

	for ( i = 0; i < players.size; i++ )
	{
		player = players[i];

		if( !isdefined(player.score) || !isdefined(player.pers["team"]) )
			continue;

	}

	for ( i = 0; i < players.size; i++ )
	{
		player = players[i];

		if( !isdefined(player.score) || !isdefined(player.pers["team"]) )
			continue;		
		
		setPlayerTeamRank( player, player.clientid, player.score - 5 * player.deaths );
	}
}


checkTimeLimit( prevTimePassed )
{
	if ( isDefined( level.timeLimitOverride ) && level.timeLimitOverride )
		return;
	
	if ( game["state"] != "playing" )
	{
		setGameEndTime( 0 );
		return;
	}
		
	if ( getTimeLimit() <= 0 )
	{
		if ( isDefined( level.startTime ) )
			setGameEndTime( level.startTime );
		else
			setGameEndTime( 0 );
		return;
	}
		
	if ( !gameFlag( "prematch_done" ) )
	{
		setGameEndTime( 0 );
		return;
	}
	
	if ( !isdefined( level.startTime ) )
		return;
	
	timeLeft = getTimeRemaining();
	
	// want this accurate to the millisecond
//	if ( getHalfTime() && game["status"] != "halftime" )
//		setGameEndTime( getTime() + (int(timeLeft) - int(getTimeLimit()*60*1000*0.5)) );
//	else
		setGameEndTime( getTime() + int(timeLeft) );

	if ( timeLeft > 0 )
	{
		if ( getHalfTime() && checkHalfTime( prevTimePassed ) )
			[[level.onHalfTime]]();

		return;
	}
	
	[[level.onTimeLimit]]();
}


checkHalfTime( prevTimePassed )
{
	if ( !level.teamBased )
		return false;
		
	if ( getTimeLimit() )
	{
		halfTime = (getTimeLimit() * 60 * 1000) * 0.5;
		
		if ( getTimePassed() >= halfTime && prevTimePassed < halfTime && prevTimePassed > 0 )
		{
			game["roundMillisecondsAlreadyPassed"] = getTimePassed();
			return true;
		}
	}
	
	return false;
}



getTimeRemaining()
{
	return getTimeLimit() * 60 * 1000 - getTimePassed();
}


checkTeamScoreLimitSoon( team )
{
	assert( isDefined( team ) );

	if ( getWatchedDvar( "scorelimit" ) <= 0 || isObjectiveBased() )
		return;
		
	if ( isDefined( level.scoreLimitOverride ) && level.scoreLimitOverride )
		return;
		
	if ( level.gameType == "conf" )
		return;
		
	if ( !level.teamBased )
		return;

	// No checks until a minute has passed to let wild data settle
	if ( getTimePassed() < (60 * 1000) ) // 1 min
		return;
	
	timeLeft = estimatedTimeTillScoreLimit( team );

	if ( timeLeft < 2 )
		level notify( "match_ending_soon", "score" );
}


checkPlayerScoreLimitSoon()
{
	if ( getWatchedDvar( "scorelimit" ) <= 0 || isObjectiveBased() )
		return;
		
	if ( level.teamBased )
		return;

	// No checks until a minute has passed to let wild data settle
	if ( getTimePassed() < (60 * 1000) ) // 1 min
		return;

	timeLeft = self estimatedTimeTillScoreLimit();

	if ( timeLeft < 2 )
		level notify( "match_ending_soon", "score" );
}


checkScoreLimit()
{
	if ( isObjectiveBased() )
		return false;

	if ( isDefined( level.scoreLimitOverride ) && level.scoreLimitOverride )
		return false;
	
	if ( game["state"] != "playing" )
		return false;

	if ( getWatchedDvar( "scorelimit" ) <= 0 )
		return false;

	if ( level.teamBased )
	{
		if( game["teamScores"]["allies"] < getWatchedDvar( "scorelimit" ) && game["teamScores"]["axis"] < getWatchedDvar( "scorelimit" ) )
			return false;
	}
	else
	{
		if ( !isPlayer( self ) )
			return false;

		if ( self.score < getWatchedDvar( "scorelimit" ) )
			return false;
	}

	return onScoreLimit();
}


updateGameTypeDvars()
{
	level endon ( "game_ended" );
	
	while ( game["state"] == "playing" )
	{
		// make sure we check time limit right when game ends
		if ( isdefined( level.startTime ) )
		{
			if ( getTimeRemaining() < 3000 )
			{
				wait .1;
				continue;
			}
		}
		wait 1;
	}
}


matchStartTimerPC()
{
	thread matchStartTimer( "waiting_for_teams", level.prematchPeriod + level.prematchPeriodEnd );
	
	waitForPlayers( level.prematchPeriod );
	
	if ( level.prematchPeriodEnd > 0 )
		matchStartTimer( "match_starting_in", level.prematchPeriodEnd );
}

matchStartTimer_Internal( countTime, matchStartTimer )
{
	waittillframeend; // wait till cleanup of previous start timer if multiple happen at once
	visionSetNaked( "mpIntro", 0 );
	
	level endon( "match_start_timer_beginning" );
	while ( countTime > 0 && !level.gameEnded )
	{
		matchStartTimer thread maps\mp\gametypes\_hud::fontPulse( level );
		wait ( matchStartTimer.inFrames * 0.066 );
		matchStartTimer setValue( countTime );
		if ( countTime == 0 )
			visionSetNaked( "", 0 );	// Disable override
		countTime--;
		wait ( 1 - (matchStartTimer.inFrames * 0.066) );
	}
}

matchStartTimer( type, duration )
{
	level notify( "match_start_timer_beginning" );
	
	matchStartText = createServerFontString( "objective", 1.5 );
	matchStartText setPoint( "CENTER", "CENTER", 0, -40 );
	matchStartText.sort = 1001;
	matchStartText setText( game["strings"]["waiting_for_teams"] );
	matchStartText.foreground = false;
	matchStartText.hidewheninmenu = true;
	
	matchStartText setText( game["strings"][type] ); // "match begins in:"
	
	matchStartTimer = createServerFontString( "hudbig", 1 );
	matchStartTimer setPoint( "CENTER", "CENTER", 0, 0 );
	matchStartTimer.sort = 1001;
	matchStartTimer.color = (1,1,0);
	matchStartTimer.foreground = false;
	matchStartTimer.hidewheninmenu = true;
	
	matchStartTimer maps\mp\gametypes\_hud::fontPulseInit();

	countTime = int( duration );
	
	if ( countTime >= 2 )
	{
		matchStartTimer_Internal( countTime, matchStartTimer );
		visionSetNaked( "", 3.0 );	// Disable override
	}
	else
	{
		visionSetNaked( "mpIntro", 0 );
		visionSetNaked( "", 1.0 ); 	// Disable override
	}
	
	matchStartTimer destroyElem();
	matchStartText destroyElem();
}

matchStartTimerSkip()
{
	visionSetNaked( "", 0 );	// Disable override
}


onRoundSwitch()
{
	if ( !isDefined( game["switchedsides"] ) )
		game["switchedsides"] = false;
	
	// overtime
	if ( game["roundsWon"]["allies"] == getWatchedDvar( "winlimit" ) - 1 && game["roundsWon"]["axis"] == getWatchedDvar( "winlimit" ) - 1 )
	{
		aheadTeam = getBetterTeam();
		if ( aheadTeam != game["defenders"] )
		{
			game["switchedsides"] = !game["switchedsides"];
		}
		else
		{
			level.halftimeSubCaption = "";
		}
		level.halftimeType = "overtime";
	}
	else
	{
		level.halftimeType = "halftime";
		game["switchedsides"] = !game["switchedsides"];
	}
}


checkRoundSwitch()
{
	if ( !level.teamBased )
		return false;
		
	if ( !isDefined( level.roundSwitch ) || !level.roundSwitch )
		return false;
		
	assert( game["roundsPlayed"] > 0 );	
	if ( game["roundsPlayed"] % level.roundSwitch == 0 )
	{
		onRoundSwitch();
		return true;
	}
		
	return false;
}


// returns the best guess of the exact time until the scoreboard will be displayed and player control will be lost.
// returns undefined if time is not known
timeUntilRoundEnd()
{
	if ( level.gameEnded )
	{
		timePassed = (getTime() - level.gameEndTime) / 1000;
		timeRemaining = level.postRoundTime - timePassed;
		
		if ( timeRemaining < 0 )
			return 0;
		
		return timeRemaining;
	}
	
	if ( getTimeLimit() <= 0 )
		return undefined;
	
	if ( !isDefined( level.startTime ) )
		return undefined;
	
	tl = getTimeLimit();
	
	timePassed = (getTime() - level.startTime)/1000;
	timeRemaining = (getTimeLimit() * 60) - timePassed;
	
	if ( isDefined( level.timePaused ) )
		timeRemaining += level.timePaused; 
	
	return timeRemaining + level.postRoundTime;
}



freeGameplayHudElems()
{
	// free up some hud elems so we have enough for other things.
	
	// perk icons
	if ( isdefined( self.perkicon ) )
	{
		if ( isdefined( self.perkicon[0] ) )
		{
			self.perkicon[0] destroyElem();
			self.perkname[0] destroyElem();
		}
		if ( isdefined( self.perkicon[1] ) )
		{
			self.perkicon[1] destroyElem();
			self.perkname[1] destroyElem();
		}
		if ( isdefined( self.perkicon[2] ) )
		{
			self.perkicon[2] destroyElem();
			self.perkname[2] destroyElem();
		}
	}
	self notify("perks_hidden"); // stop any threads that are waiting to hide the perk icons
	
	// lower message
	self.lowerMessage destroyElem();
	self.lowerTimer destroyElem();
	
	// progress bar
	if ( isDefined( self.proxBar ) )
		self.proxBar destroyElem();
	if ( isDefined( self.proxBarText ) )
		self.proxBarText destroyElem();
}


getHostPlayer()
{
	players = getEntArray( "player", "classname" );
	
	for ( index = 0; index < players.size; index++ )
	{
		if ( players[index] isHost() )
			return players[index];
	}
}


hostIdledOut()
{
	hostPlayer = getHostPlayer();
	
	// host never spawned
	if ( isDefined( hostPlayer ) && !hostPlayer.hasSpawned && !isDefined( hostPlayer.selectedClass ) )
		return true;

	return false;
}



roundEndWait( defaultDelay, matchBonus )
{
	//setSlowMotion( 1.0, 0.15, defaultDelay / 2 );

	notifiesDone = false;
	while ( !notifiesDone )
	{
		players = level.players;
		notifiesDone = true;
		
		foreach ( player in players )
		{
			if ( !isDefined( player.doingSplash ) )
				continue;

			if ( !player maps\mp\gametypes\_hud_message::isDoingSplash() )
				continue;

			notifiesDone = false;
		}
		wait ( 0.5 );
	}

	if ( !matchBonus )
	{
		wait ( defaultDelay );
		level notify ( "round_end_finished" );
		//setSlowMotion( 1.0, 1.0, 0.05 );
		return;
	}

    wait ( defaultDelay / 2 );
	level notify ( "give_match_bonus" );
	wait ( defaultDelay / 2 );

	notifiesDone = false;
	while ( !notifiesDone )
	{
		players = level.players;
		notifiesDone = true;
		foreach ( player in players )
		{
			if ( !isDefined( player.doingSplash ) )
				continue;

			if ( !player maps\mp\gametypes\_hud_message::isDoingSplash() )
				continue;

			notifiesDone = false;
		}
		wait ( 0.5 );
	}
	//setSlowMotion( 1.0, 1.0, 0.05);
	
	level notify ( "round_end_finished" );
}


roundEndDOF( time )
{
	self setDepthOfField( 0, 128, 512, 4000, 6, 1.8 );
}


Callback_StartGameType()
{
	maps\mp\_load::main();
	
	levelFlagInit( "round_over", false );
	levelFlagInit( "game_over", false );
	levelFlagInit( "block_notifies", false ); 

	level.prematchPeriod = 0;
	level.prematchPeriodEnd = 0;
	level.postGameNotifies = 0;

	level.intermission = false;
	
	makeDvarServerInfo( "cg_thirdPersonAngle", 356 );

	makeDvarServerInfo( "scr_gameended", 0 );

	if ( !isDefined( game["gamestarted"] ) )
	{
		game["clientid"] = 0;
		
		alliesCharSet = getMapCustom( "allieschar" );
		if ( (!isDefined( alliesCharSet ) || alliesCharSet == "") )
		{
			if ( !isDefined( game["allies"] ) )
				alliesCharSet = "sas_urban";
			else
				alliesCharSet = game["allies"];
		}

		axisCharSet = getMapCustom( "axischar" );
		if ( (!isDefined( axisCharSet ) || axisCharSet == "") )
		{
			if ( !isDefined( game["axis"] ) )
				axisCharSet = "opforce_henchmen";
			else
				axisCharSet = game["axis"];
		}

		game["allies"] = alliesCharSet;
		game["axis"] = axisCharSet;	

		if ( !isDefined( game["attackers"] ) || !isDefined( game["defenders"]  ) )
			thread error( "No attackers or defenders team defined in level .gsc." );

		if (  !isDefined( game["attackers"] ) )
			game["attackers"] = "allies";
		if (  !isDefined( game["defenders"] ) )
			game["defenders"] = "axis";

		if ( !isDefined( game["state"] ) )
			game["state"] = "playing";
	
		precacheStatusIcon( "hud_status_dead" );
		precacheStatusIcon( "hud_status_connecting" );
		precacheString( &"MPUI_REVIVING" );
		precacheString( &"MPUI_BEING_REVIVED" );
		
		precacheRumble( "damage_heavy" );

		precacheShader( "white" );
		precacheShader( "black" );
			
		game["strings"]["press_to_spawn"] = &"PLATFORM_PRESS_TO_SPAWN";
		if ( level.teamBased )
		{
			game["strings"]["waiting_for_teams"] = &"MP_WAITING_FOR_TEAMS";
			game["strings"]["opponent_forfeiting_in"] = &"MP_OPPONENT_FORFEITING_IN";
		}
		else
		{
			game["strings"]["waiting_for_teams"] = &"MP_WAITING_FOR_MORE_PLAYERS";
			game["strings"]["opponent_forfeiting_in"] = &"MP_OPPONENT_FORFEITING_IN";
		}
		game["strings"]["match_starting_in"] = &"MP_MATCH_STARTING_IN";
		game["strings"]["match_resuming_in"] = &"MP_MATCH_RESUMING_IN";
		game["strings"]["waiting_for_players"] = &"MP_WAITING_FOR_PLAYERS";
		game["strings"]["spawn_next_round"] = &"MP_SPAWN_NEXT_ROUND";
		game["strings"]["waiting_to_spawn"] = &"MP_WAITING_TO_SPAWN";
		game["strings"]["waiting_to_safespawn"] = &"MP_WAITING_TO_SAFESPAWN";
		game["strings"]["match_starting"] = &"MP_MATCH_STARTING";
		game["strings"]["change_class"] = &"MP_CHANGE_CLASS_NEXT_SPAWN";
		game["strings"]["last_stand"] = &"MPUI_LAST_STAND";
		game["strings"]["final_stand"] = &"MPUI_FINAL_STAND";
		game["strings"]["c4_death"] = &"MPUI_C4_DEATH";
		
		game["strings"]["cowards_way"] = &"PLATFORM_COWARDS_WAY_OUT";
		
		game["strings"]["tie"] = &"MP_MATCH_TIE";
		game["strings"]["round_draw"] = &"MP_ROUND_DRAW";

		game["strings"]["grabbed_flag"] = &"MP_GRABBED_FLAG_FIRST";
		game["strings"]["enemies_eliminated"] = &"MP_ENEMIES_ELIMINATED";
		game["strings"]["score_limit_reached"] = &"MP_SCORE_LIMIT_REACHED";
		game["strings"]["round_limit_reached"] = &"MP_ROUND_LIMIT_REACHED";
		game["strings"]["time_limit_reached"] = &"MP_TIME_LIMIT_REACHED";
		game["strings"]["players_forfeited"] = &"MP_PLAYERS_FORFEITED";
		game["strings"]["S.A.S Win"] = &"SAS_WIN";
		game["strings"]["Spetsnaz Win"] = &"SPETSNAZ_WIN";

		game["colors"]["blue"] = (0.25,0.25,0.75);
		game["colors"]["red"] = (0.75,0.25,0.25);
		game["colors"]["white"] = (1.0,1.0,1.0);
		game["colors"]["black"] = (0.0,0.0,0.0);
		game["colors"]["green"] = (0.25,0.75,0.25);
		game["colors"]["yellow"] = (0.65,0.65,0.0);
		game["colors"]["orange"] = (1.0,0.45,0.0);

		game["strings"]["allies_eliminated"] = maps\mp\gametypes\_teams::getTeamEliminatedString( "allies" );
		game["strings"]["allies_forfeited"] = maps\mp\gametypes\_teams::getTeamForfeitedString( "allies" );
		game["strings"]["allies_name"] = maps\mp\gametypes\_teams::getTeamName( "allies" );	
		game["icons"]["allies"] = maps\mp\gametypes\_teams::getTeamIcon( "allies" );	
		game["colors"]["allies"] = maps\mp\gametypes\_teams::getTeamColor( "allies" );	

		game["strings"]["axis_eliminated"] = maps\mp\gametypes\_teams::getTeamEliminatedString( "axis" );
		game["strings"]["axis_forfeited"] = maps\mp\gametypes\_teams::getTeamForfeitedString( "axis" );
		game["strings"]["axis_name"] = maps\mp\gametypes\_teams::getTeamName( "axis" );	
		game["icons"]["axis"] = maps\mp\gametypes\_teams::getTeamIcon( "axis" );	
		game["colors"]["axis"] = maps\mp\gametypes\_teams::getTeamColor( "axis" );	
		
		if ( game["colors"]["allies"] == (0,0,0) )
			game["colors"]["allies"] = (0.5,0.5,0.5);

		if ( game["colors"]["axis"] == (0,0,0) )
			game["colors"]["axis"] = (0.5,0.5,0.5);

		[[level.onPrecacheGameType]]();

		if ( level.console )
		{
			if ( !level.splitscreen )
				level.prematchPeriod = maps\mp\gametypes\_tweakables::getTweakableValue( "game", "graceperiod" );
		}
		else
		{
			// first round, so set up prematch
			level.prematchPeriod = maps\mp\gametypes\_tweakables::getTweakableValue( "game", "playerwaittime" );
			level.prematchPeriodEnd = maps\mp\gametypes\_tweakables::getTweakableValue( "game", "matchstarttime" );
		}
	}
	else
	{
		// on round restarts wait this long before letting the users move to cover up the hitching that can happen by the server
		// thead stalling during this function call
		if ( level.console )
		{
			if ( !level.splitscreen )
				level.prematchPeriod = 5;
		}
		else
		{
			// first round, so set up prematch
			level.prematchPeriod = 5;
			level.prematchPeriodEnd = maps\mp\gametypes\_tweakables::getTweakableValue( "game", "matchstarttime" );
		}
	}

	if ( !isDefined( game["status"] ) )
		game["status"] = "normal";

	makeDvarServerInfo( "ui_overtime", (game["status"] == "overtime") );

	if ( game["status"] != "overtime" && game["status"] != "halftime" )
	{
		game["teamScores"]["allies"] = 0;
		game["teamScores"]["axis"] = 0;
	}
	
	if( !isDefined( game["timePassed"] ) )
		game["timePassed"] = 0;

	if( !isDefined( game["roundsPlayed"] ) )
		game["roundsPlayed"] = 0;

	if ( !isDefined( game["roundsWon"] ) )
		game["roundsWon"] = [];

	if ( level.teamBased )
	{
		if ( !isDefined( game["roundsWon"]["axis"] ) )
			game["roundsWon"]["axis"] = 0;
		if ( !isDefined( game["roundsWon"]["allies"] ) )		
			game["roundsWon"]["allies"] = 0;
	}
	
	level.gameEnded = false;
	level.forcedEnd = false;
	level.hostForcedEnd = false;

	level.hardcoreMode = getDvarInt( "g_hardcore" );
	if ( level.hardcoreMode )
		logString( "game mode: hardcore" );

	level.dieHardMode = getDvarInt( "scr_diehard" );
	
	if ( !level.teamBased )
		level.dieHardMode = 0;

	if ( level.dieHardMode )
		logString( "game mode: diehard" );

	level.killstreakRewards = getDvarInt( "scr_game_hardpoints" );

	/#
	printLn( "SESSION INFO" );
	printLn( "=====================================" );
	printLn( "  Map:         " + level.script );
	printLn( "  Script:      " + level.gametype );
	printLn( "  HardCore:    " + level.hardcoreMode );
	printLn( "  Diehard:     " + level.dieHardMode );
	printLn( "  3rd Person:  " + getDvarInt( "camera_thirdperson" ) );
	printLn( "  Round:       " + game[ "roundsPlayed" ] );
	printLn( "  scr_" + level.gametype + "_scorelimit " + getDvar( "scr_" + level.gametype + "_scorelimit" ) );
	printLn( "  scr_" + level.gametype + "_roundlimit " +getDvar( "scr_" + level.gametype + "_roundlimit" ) );
	printLn( "  scr_" + level.gametype + "_winlimit " + getDvar( "scr_" + level.gametype + "_winlimit" ) );
	printLn( "  scr_" + level.gametype + "_timelimit " + getDvar( "scr_" + level.gametype + "_timelimit" ) );
	printLn( "  scr_" + level.gametype + "_numlives " + getDvar( "scr_" + level.gametype + "_numlives" ) );
	printLn( "  scr_" + level.gametype + "_halftime " + getDvar( "scr_" + level.gametype + "_halftime" ) );
	printLn( "  scr_" + level.gametype + "_roundswitch " + getDvar( "scr_" + level.gametype + "_roundswitch" ) );
	printLn( "=====================================" );
	#/

	// this gets set to false when someone takes damage or a gametype-specific event happens.
	level.useStartSpawns = true;

	// multiplier for score from objectives
	level.objectivePointsMod = 1;

	if ( matchMakingGame() )	
		level.maxAllowedTeamKills = 2;
	else
		level.maxAllowedTeamKills = -1;
		
	thread maps\mp\gametypes\_persistence::init();
	thread maps\mp\gametypes\_menus::init();
	thread maps\mp\gametypes\_hud::init();
	thread maps\mp\gametypes\_serversettings::init();
	thread maps\mp\gametypes\_teams::init();
	thread maps\mp\gametypes\_weapons::init();
	thread maps\mp\gametypes\_killcam::init();
	thread maps\mp\gametypes\_shellshock::init();
	thread maps\mp\gametypes\_deathicons::init();
	thread maps\mp\gametypes\_damagefeedback::init();
	thread maps\mp\gametypes\_healthoverlay::init();
	thread maps\mp\gametypes\_spectating::init();
	thread maps\mp\gametypes\_objpoints::init();
	thread maps\mp\gametypes\_gameobjects::init();
	thread maps\mp\gametypes\_spawnlogic::init();
	thread maps\mp\gametypes\_battlechatter_mp::init();
	thread maps\mp\gametypes\_music_and_dialog::init();
	thread maps\mp\_matchdata::init();
	thread maps\mp\_awards::init();
	thread maps\mp\_skill::init();
	thread maps\mp\_areas::init();	
	thread maps\mp\killstreaks\_killstreaks::init();
	thread maps\mp\perks\_perks::init();
	thread maps\mp\_events::init();
	thread maps\mp\_defcon::init();
	thread maps\mp\_matchevents::init();
	//* thread maps\mp\gametypes\_damage::initFinalKillCam();

	if ( level.teamBased )
		thread maps\mp\gametypes\_friendicons::init();
		
	thread maps\mp\gametypes\_hud_message::init();

	if ( !level.console )
		thread maps\mp\gametypes\_quickmessages::init();

	foreach ( locString in game["strings"] )
		precacheString( locString );

	foreach ( icon in game["icons"] )
		precacheShader( icon );

	game["gamestarted"] = true;

	level.maxPlayerCount = 0;
	level.waveDelay["allies"] = 0;
	level.waveDelay["axis"] = 0;
	level.lastWave["allies"] = 0;
	level.lastWave["axis"] = 0;
	level.wavePlayerSpawnIndex["allies"] = 0;
	level.wavePlayerSpawnIndex["axis"] = 0;
	level.alivePlayers["allies"] = [];
	level.alivePlayers["axis"] = [];
	level.activePlayers = [];

	makeDvarServerInfo( "ui_scorelimit", 0 );
	makeDvarServerInfo( "ui_allow_classchange", getDvar( "ui_allow_classchange" ) );
	makeDvarServerInfo( "ui_allow_teamchange", 1 );
	SetDvar( "ui_allow_teamchange", 1 );
	
	if ( getGametypeNumLives() )
		setdvar( "g_deadChat", 0 );
	else
		setdvar( "g_deadChat", 1 );
	
	waveDelay = getDvarInt( "scr_" + level.gameType + "_waverespawndelay" );
	if ( waveDelay )
	{
		level.waveDelay["allies"] = waveDelay;
		level.waveDelay["axis"] = waveDelay;
		level.lastWave["allies"] = 0;
		level.lastWave["axis"] = 0;
		
		level thread maps\mp\gametypes\_gamelogic::waveSpawnTimer();
	}
	
	gameFlagInit( "prematch_done", false );
	
	level.gracePeriod = 15;
	
	level.inGracePeriod = level.gracePeriod;
	gameFlagInit( "graceperiod_done", false );
	
	level.roundEndDelay = 4;
	level.halftimeRoundEndDelay = 4;

	level.noRagdollEnts = getentarray( "noragdoll", "targetname" );
	
	if ( level.teamBased )
	{
		maps\mp\gametypes\_gamescore::updateTeamScore( "axis" );
		maps\mp\gametypes\_gamescore::updateTeamScore( "allies" );
	}
	else
	{
		thread maps\mp\gametypes\_gamescore::initialDMScoreUpdate();
	}

	thread updateUIScoreLimit();
	level notify ( "update_scorelimit" );

	
	[[level.onStartGameType]]();
	
	// this must be after onstartgametype for scr_showspawns to work when set at start of game
	/#
	thread maps\mp\gametypes\_dev::init();
	#/
	
	thread startGame();

	level thread updateWatchedDvars();
	level thread timeLimitThread();
	//* level thread maps\mp\gametypes\_damage::doFinalKillcam();
}


Callback_CodeEndGame()
{
	endparty();

	if ( !level.gameEnded )
		level thread maps\mp\gametypes\_gamelogic::forceEnd();
}


timeLimitThread()
{
	level endon ( "game_ended" );
	
	prevTimePassed = getTimePassed();
	
	while ( game["state"] == "playing" )
	{
		thread checkTimeLimit( prevTimePassed );
		prevTimePassed = getTimePassed();
		
		// make sure we check time limit right when game ends
		if ( isdefined( level.startTime ) )
		{
			if ( getTimeRemaining() < 3000 )
			{
				wait .1;
				continue;
			}
		}
		wait 1;
	}	
}


updateUIScoreLimit()
{
	for ( ;; )
	{
		level waittill_either ( "update_scorelimit", "update_winlimit" );
		
		if ( !isRoundBased() || !isObjectiveBased() )
		{
			SetDvar( "ui_scorelimit", getWatchedDvar( "scorelimit" ) );
			thread checkScoreLimit();
		}
		else
		{
			SetDvar( "ui_scorelimit", getWatchedDvar( "winlimit" ) );
		}
	}
}


playTickingSound()
{
	self endon("death");
	self endon("stop_ticking");
	level endon("game_ended");
	
	time = level.bombTimer;
	
	while(1)
	{
		self playSound( "ui_mp_suitcasebomb_timer" );
		
		if ( time > 10 )
		{
			time -= 1;
			wait 1;
		}
		else if ( time > 4 )
		{
			time -= .5;
			wait .5;
		}
		else if ( time > 1 )
		{
			time -= .4;
			wait .4;
		}
		else
		{
			time -= .3;
			wait .3;
		}
		maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();
	}
}

stopTickingSound()
{
	self notify("stop_ticking");
}

timeLimitClock()
{
	level endon ( "game_ended" );
	
	wait .05;
	
	clockObject = spawn( "script_origin", (0,0,0) );
	clockObject hide();
	
	while ( game["state"] == "playing" )
	{
		if ( !level.timerStopped && getTimeLimit() )
		{
			timeLeft = getTimeRemaining() / 1000;
			timeLeftInt = int(timeLeft + 0.5); // adding .5 and flooring rounds it.
			
			if ( getHalfTime() && timeLeftInt > (getTimeLimit()*60) * 0.5 )
				timeLeftInt -= int((getTimeLimit()*60) * 0.5);
			
			if ( (timeLeftInt >= 30 && timeLeftInt <= 60) )
				level notify ( "match_ending_soon", "time" );

			if ( timeLeftInt <= 10 || (timeLeftInt <= 30 && timeLeftInt % 2 == 0) )
			{
				level notify ( "match_ending_very_soon" );
				// don't play a tick at exactly 0 seconds, that's when something should be happening!
				if ( timeLeftInt == 0 )
					break;
				
				clockObject playSound( "ui_mp_timer_countdown" );
			}
			
			// synchronize to be exactly on the second
			if ( timeLeft - floor(timeLeft) >= .066 )
				wait timeLeft - floor(timeLeft);
		}

		wait ( 1.0 );
	}
}


gameTimer()
{
	level endon ( "game_ended" );
	
	level waittill("prematch_over");
	
	level.startTime = getTime();
	level.discardTime = 0;
	
	if ( isDefined( game["roundMillisecondsAlreadyPassed"] ) )
	{
		level.startTime -= game["roundMillisecondsAlreadyPassed"];
		game["roundMillisecondsAlreadyPassed"] = undefined;
	}
	
	prevtime = gettime();
	
	while ( game["state"] == "playing" )
	{
		if ( !level.timerStopped )
		{
			// the wait isn't always exactly 1 second. dunno why.
			game["timePassed"] += gettime() - prevtime;
		}
		prevtime = gettime();
		wait ( 1.0 );
	}
}

UpdateTimerPausedness()
{
	shouldBeStopped = level.timerStoppedForGameMode || isDefined( level.hostMigrationTimer );
	if ( !gameFlag( "prematch_done" ) )
		shouldBeStopped = false;
	
	if ( !level.timerStopped && shouldBeStopped )
	{
		level.timerStopped = true;
		level.timerPauseTime = gettime();
	}
	else if ( level.timerStopped && !shouldBeStopped )
	{
		level.timerStopped = false;
		level.discardTime += gettime() - level.timerPauseTime;
	}
}

pauseTimer()
{
	level.timerStoppedForGameMode = true;
	UpdateTimerPausedness();
}

resumeTimer()
{
	level.timerStoppedForGameMode = false;
	UpdateTimerPausedness();
}


startGame()
{
	thread gameTimer();
	level.timerStopped = false;
	level.timerStoppedForGameMode = false;
	thread maps\mp\gametypes\_spawnlogic::spawnPerFrameUpdate();

	prematchPeriod();
	gameFlagSet( "prematch_done" );	
	level notify("prematch_over");
	
	UpdateTimerPausedness();
	
	thread timeLimitClock();
	thread gracePeriod();

	thread maps\mp\gametypes\_missions::roundBegin();	
}


waveSpawnTimer()
{
	level endon( "game_ended" );

	while ( game["state"] == "playing" )
	{
		time = getTime();
		
		if ( time - level.lastWave["allies"] > (level.waveDelay["allies"] * 1000) )
		{
			level notify ( "wave_respawn_allies" );
			level.lastWave["allies"] = time;
			level.wavePlayerSpawnIndex["allies"] = 0;
		}

		if ( time - level.lastWave["axis"] > (level.waveDelay["axis"] * 1000) )
		{
			level notify ( "wave_respawn_axis" );
			level.lastWave["axis"] = time;
			level.wavePlayerSpawnIndex["axis"] = 0;
		}
		
		wait ( 0.05 );
	}
}


getBetterTeam()
{
	kills["allies"] = 0;
	kills["axis"] = 0;
	deaths["allies"] = 0;
	deaths["axis"] = 0;
	
	foreach ( player in level.players )
	{
		team = player.pers["team"];
		if ( isDefined( team ) && (team == "allies" || team == "axis") )
		{
			kills[ team ] += player.kills;
			deaths[ team ] += player.deaths;
		}
	}
	
	if ( kills["allies"] > kills["axis"] )
		return "allies";
	else if ( kills["axis"] > kills["allies"] )
		return "axis";
	
	// same number of kills

	if ( deaths["allies"] < deaths["axis"] )
		return "allies";
	else if ( deaths["axis"] < deaths["allies"] )
		return "axis";
	
	// same number of deaths
	
	if ( randomint(2) == 0 )
		return "allies";
	return "axis";
}


rankedMatchUpdates( winner )
{
	if ( matchMakingGame() )
	{
		setXenonRanks();
		
		if ( hostIdledOut() )
		{
			level.hostForcedEnd = true;
			logString( "host idled out" );
			endLobby();
		}

		updateMatchBonusScores( winner );
	}

	updateWinLossStats( winner );
}


displayRoundEnd( winner, endReasonText )
{
	foreach ( player in level.players )
	{
		if ( isDefined( player.connectedPostGame ) || player.pers["team"] == "spectator" )
			continue;
		
		if ( level.teamBased )
			player thread maps\mp\gametypes\_hud_message::teamOutcomeNotify( winner, true, endReasonText );
		else
			player thread maps\mp\gametypes\_hud_message::outcomeNotify( winner, endReasonText );
	}

	if ( !wasLastRound() )
		level notify ( "round_win", winner );
	
	if ( wasLastRound() )
		roundEndWait( level.roundEndDelay, false );
	else
		roundEndWait( level.roundEndDelay, true );	
}


displayGameEnd( winner, endReasonText )
{	
	// catching gametype, since DM forceEnd sends winner as player entity, instead of string
	foreach ( player in level.players )
	{
		if ( isDefined( player.connectedPostGame ) || player.pers["team"] == "spectator" )
			continue;
		
		if ( level.teamBased )
			player thread maps\mp\gametypes\_hud_message::teamOutcomeNotify( winner, false, endReasonText );
		else
			player thread maps\mp\gametypes\_hud_message::outcomeNotify( winner, endReasonText );
	}
	
	level notify ( "game_win", winner );
	
	roundEndWait( level.postRoundTime, true );
}


displayRoundSwitch()
{
	switchType = level.halftimeType;
	if ( switchType == "halftime" )
	{
		if ( getWatchedDvar( "roundlimit" ) )
		{
			if ( (game["roundsPlayed"] * 2) == getWatchedDvar( "roundlimit" ) )
				switchType = "halftime";
			else
				switchType = "intermission";
		}
		else if ( getWatchedDvar( "winlimit" ) )
		{
			if ( game["roundsPlayed"] == (getWatchedDvar( "winlimit" ) - 1) )
				switchType = "halftime";
			else
				switchType = "intermission";
		}
		else
		{
			switchType = "intermission";
		}
	}

	level notify ( "round_switch", switchType );

	foreach ( player in level.players )
	{
		if ( isDefined( player.connectedPostGame ) || player.pers["team"] == "spectator" )
			continue;
		
		player thread maps\mp\gametypes\_hud_message::teamOutcomeNotify( switchType, true, level.halftimeSubCaption );
	}
	
	roundEndWait( level.halftimeRoundEndDelay, false );
}


endGameOvertime( winner, endReasonText )
{
	VisionSetNaked( "mpOutro", 0.5 );		
	SetDvar( "scr_gameended", 3 );

	// freeze players
	foreach ( player in level.players )
	{
		player thread freezePlayerForRoundEnd( 0 );
		player thread roundEndDoF( 4.0 );
		
		player freeGameplayHudElems();

		player setClientDvars( "cg_everyoneHearsEveryone", 1 );
		player setClientDvars( "cg_drawSpectatorMessages", 0,
							   "g_compassShowEnemies", 0 );
							   
		if ( player.pers["team"] == "spectator" )
			player thread maps\mp\gametypes\_playerlogic::spawnIntermission();
	}

	level notify ( "round_switch", "overtime" );

	// catching gametype, since DM forceEnd sends winner as player entity, instead of string
	foreach ( player in level.players )
	{
		if ( isDefined( player.connectedPostGame ) || player.pers["team"] == "spectator" )
			continue;
		
		if ( level.teamBased )
			player thread maps\mp\gametypes\_hud_message::teamOutcomeNotify( winner, false, endReasonText );
		else
			player thread maps\mp\gametypes\_hud_message::outcomeNotify( winner, endReasonText );
	}
	
	roundEndWait( level.roundEndDelay, false );

	if( IsDefined( level.finalKillCam_winner ) )
	{
		level.finalKillCam_timeGameEnded[ level.finalKillCam_winner ] = getSecondsPassed();

		foreach ( player in level.players )
			player notify( "reset_outcome" );

		level notify( "game_cleanup" );

		waittillFinalKillcamDone();
	}

	game["status"] = "overtime";
	level notify ( "restarting" );
    game["state"] = "playing";
    map_restart( true );
}



endGameHalfTime()
{
	VisionSetNaked( "mpOutro", 0.5 );		
	SetDvar( "scr_gameended", 2 );

	game["switchedsides"] = !game["switchedsides"];

	// freeze players
	foreach ( player in level.players )
	{
		player thread freezePlayerForRoundEnd( 0 );
		player thread roundEndDoF( 4.0 );
		
		player freeGameplayHudElems();

		player setClientDvars( "cg_everyoneHearsEveryone", 1 );
		player setClientDvars( "cg_drawSpectatorMessages", 0,
							   "g_compassShowEnemies", 0 );
							   
		if ( player.pers["team"] == "spectator" )
			player thread maps\mp\gametypes\_playerlogic::spawnIntermission();
	}

	foreach ( player in level.players )
		player.pers["stats"] = player.stats;

	level notify ( "round_switch", "halftime" );
		
	foreach ( player in level.players )
	{
		if ( isDefined( player.connectedPostGame ) || player.pers["team"] == "spectator" )
			continue;

		player thread maps\mp\gametypes\_hud_message::teamOutcomeNotify( "halftime", true, level.halftimeSubCaption );
	}
	
	roundEndWait( level.roundEndDelay, false );

	if( IsDefined( level.finalKillCam_winner ) )
	{
		level.finalKillCam_timeGameEnded[ level.finalKillCam_winner ] = getSecondsPassed();

		foreach ( player in level.players )
			player notify( "reset_outcome" );

		level notify( "game_cleanup" );

		waittillFinalKillcamDone();
	}

	game["status"] = "halftime";
	level notify ( "restarting" );
    game["state"] = "playing";
    map_restart( true );
}


endGame( winner, endReasonText, nukeDetonated )
{
	if ( !isDefined(nukeDetonated) )
		nukeDetonated = false;
	
	// return if already ending via host quit or victory, or nuke incoming
	if ( game["state"] == "postgame" || level.gameEnded && ( !isDefined( level.gtnw ) || !level.gtnw ) )
		return;

	game["state"] = "postgame";

	level.gameEndTime = getTime();
	level.gameEnded = true;
	level.inGracePeriod = false;
	level notify ( "game_ended", winner );
	levelFlagSet( "game_over" );
	levelFlagSet( "block_notifies" );
	waitframe(); // give "game_ended" notifies time to process
	
	setGameEndTime( 0 ); // stop/hide the timers
	
	gameLength = getMatchData( "gameLength" );
	gameLength = gameLength + int( getSecondsPassed() );
	setMatchData( "gameLength", gameLength );	

	maps\mp\gametypes\_playerlogic::printPredictedSpawnpointCorrectness();
	
	if ( isDefined( winner ) && isString( winner ) && winner == "overtime" )
	{
		level.finalKillCam_winner = "none";
		endGameOvertime( winner, endReasonText );
		return;
	}
	
	if ( isDefined( winner ) && isString( winner ) && winner == "halftime" )
	{
		level.finalKillCam_winner = "none";
		endGameHalfTime();
		return;
	}
	
	if( IsDefined( level.finalKillCam_winner ) )
		level.finalKillCam_timeGameEnded[ level.finalKillCam_winner ] = getSecondsPassed();

	game["roundsPlayed"]++;
	
	if ( level.teamBased )
	{
		if ( winner == "axis" || winner == "allies" )
			game["roundsWon"][winner]++;

		maps\mp\gametypes\_gamescore::updateTeamScore( "axis" );
		maps\mp\gametypes\_gamescore::updateTeamScore( "allies" );
	}
	else
	{
		if ( isDefined( winner ) && isPlayer( winner ) )
			game["roundsWon"][winner.guid]++;
	}
	
	maps\mp\gametypes\_gamescore::updatePlacement();

	rankedMatchUpdates( winner );

	foreach ( player in level.players )
	{
		player setClientDvar( "ui_opensummary", 1 );

		if( wasOnlyRound() || wasLastRound() )
		{
			// since the game is over, clear their killstreaks so they don't carry over to another game
			player maps\mp\killstreaks\_killstreaks::clearKillstreaks();
		}
	}
	
	setDvar( "g_deadChat", 1 );
	setDvar( "ui_allow_teamchange", 0 );

	// freeze players
	foreach ( player in level.players )
	{
		player thread freezePlayerForRoundEnd( 1.0 );
		player thread roundEndDoF( 4.0 );
		
		player freeGameplayHudElems();

		player setClientDvars( "cg_everyoneHearsEveryone", 1 );
		player setClientDvars( "cg_drawSpectatorMessages", 0,
							   "g_compassShowEnemies", 0,
							   "cg_fovScale", 1 );
							   
		if ( player.pers["team"] == "spectator" )
			player thread maps\mp\gametypes\_playerlogic::spawnIntermission();
	}

	if( !nukeDetonated )
		visionSetNaked( "mpOutro", 0.5 );		
	
	// End of Round
	if ( !wasOnlyRound() && !nukeDetonated )
	{
		SetDvar( "scr_gameended", 2 );
	
		displayRoundEnd( winner, endReasonText );

		if ( IsDefined( level.finalKillCam_winner ) )
		{
			foreach ( player in level.players )
				player notify ( "reset_outcome" );

			level notify ( "game_cleanup" );

			waittillFinalKillcamDone();
		}
				
		if ( !wasLastRound() )
		{
			levelFlagClear( "block_notifies" );
			if ( checkRoundSwitch() )
				displayRoundSwitch();

			foreach ( player in level.players )
				player.pers["stats"] = player.stats;

        	level notify ( "restarting" );
            game["state"] = "playing";
            map_restart( true );
            return;
		}
		
		if ( !level.forcedEnd )
			endReasonText = updateEndReasonText( winner );
	}

	// different kill cam strings for different gametypes and endings
	if( endReasonText == game["strings"]["time_limit_reached"] )
	{
		SetDvar( "scr_gameended", 3 );
	}
	else
	{
		// these gametypes ended on score
		switch( level.gametype )
		{
		case "koth":
		case "dom":
		case "ctf":
		case "sd":
		case "sab":
		case "conf":
			SetDvar( "scr_gameended", 4 );
			break;

		default:
			SetDvar( "scr_gameended", 1 );
			break;
		}
	}
	
	if ( !isDefined( game["clientMatchDataDef"] ) )
	{
		game["clientMatchDataDef"] = "mp/clientmatchdata.def";
		setClientMatchDataDef( game["clientMatchDataDef"] );
	}

	maps\mp\gametypes\_missions::roundEnd( winner );

	displayGameEnd( winner, endReasonText );

	if ( IsDefined( level.finalKillCam_winner ) && wasOnlyRound() )
	{
		foreach ( player in level.players )
			player notify ( "reset_outcome" );

		level notify ( "game_cleanup" );

		waittillFinalKillcamDone();
	}				

	levelFlagClear( "block_notifies" );

	level.intermission = true;

	level notify ( "spawning_intermission" );
	
	foreach ( player in level.players )
	{
		player closepopupMenu();
		player closeInGameMenu();
		player notify ( "reset_outcome" );
		player thread maps\mp\gametypes\_playerlogic::spawnIntermission();
	}

	processLobbyData();

	wait ( 1.0 );
	
	checkForPersonalBests();
	if ( level.teamBased )
	{	
		if( winner == "axis" || winner == "allies" )
			setMatchData( "victor", winner );
		else
			setMatchData( "victor", "none" );
			
		setMatchData( "alliesScore", getTeamScore( "allies" ) );
		setMatchData( "axisScore", getTeamScore( "axis" ) );
	}
	else
	{
		setMatchData( "victor", "none" );
	}

	setMatchData( "host", level.hostname );
	
	sendMatchData();

	foreach ( player in level.players )
		player.pers["stats"] = player.stats;

	//logString( "game ended" );
	if( !nukeDetonated && !level.postGameNotifies )
	{
		if ( !wasOnlyRound() )
			wait 6.0;
		else
			wait 3.0;
	}
	else
	{
		wait ( min( 10.0, 4.0 + level.postGameNotifies ) );
	}
	
	level notify( "exitLevel_called" );
	exitLevel( false );
}

updateEndReasonText( winner )
{
	if ( !level.teamBased )
		return true;

	if ( hitRoundLimit() )
		return &"MP_ROUND_LIMIT_REACHED";
	
	if ( hitWinLimit() )
		return &"MP_SCORE_LIMIT_REACHED";
	
	if ( winner == "axis" )
		return &"SPETSNAZ_WIN";
	else
		return &"SAS_WIN";
}

estimatedTimeTillScoreLimit( team )
{
	assert( isPlayer( self ) || isDefined( team ) );

	scorePerMinute = getScorePerMinute( team );
	scoreRemaining = getScoreRemaining( team );

	estimatedTimeLeft = 999999;
	if ( scorePerMinute )
		estimatedTimeLeft = scoreRemaining / scorePerMinute;
	
	//println( "estimatedTimeLeft: " + estimatedTimeLeft );
	return estimatedTimeLeft;
}

getScorePerMinute( team )
{
	assert( isPlayer( self ) || isDefined( team ) );

	scoreLimit = getWatchedDvar( "scorelimit" );
	timeLimit = getTimeLimit();
	minutesPassed = (getTimePassed() / (60*1000)) + 0.0001;

	if ( isPlayer( self ) )
		scorePerMinute = self.score / minutesPassed;
	else
		scorePerMinute = getTeamScore( team ) / minutesPassed;
		
	return scorePerMinute;
}

getScoreRemaining( team )
{
	assert( isPlayer( self ) || isDefined( team ) );

	scoreLimit = getWatchedDvar( "scorelimit" );

	if ( isPlayer( self ) )
		scoreRemaining = scoreLimit - self.score;
	else
		scoreRemaining = scoreLimit - getTeamScore( team );
		
	return scoreRemaining;
}

giveLastOnTeamWarning()
{
	self endon("death");
	self endon("disconnect");
	level endon( "game_ended" );

	self waitTillRecoveredHealth( 3 );

	otherTeam = getOtherTeam( self.pers["team"] );
	thread teamPlayerCardSplash( "callout_lastteammemberalive", self, self.pers["team"] );
	thread teamPlayerCardSplash( "callout_lastenemyalive", self, otherTeam );
	level notify ( "last_alive", self );
}

processLobbyData()
{
	curPlayer = 0;
	foreach ( player in level.players )
	{
		if ( !isDefined( player ) )
			continue;

		player.clientMatchDataId = curPlayer;
		curPlayer++;

		// on PS3 cap long names
		if ( level.ps3 && (player.name.size > level.MaxNameLength) )
		{
			playerName = "";
			for ( i = 0; i < level.MaxNameLength-3; i++ )
				playerName += player.name[i];

			playerName += "...";
		}
		else
		{
			playerName = player.name;
		}
		
		setClientMatchData( "players", player.clientMatchDataId, "xuid", playerName );		
	}
	
	maps\mp\_awards::assignAwards();
	maps\mp\_scoreboard::processLobbyScoreboards();
	
	sendClientMatchData();
}

trackLeaderBoardDeathStats( sWeapon, sMeansOfDeath )
{
	self thread threadedSetWeaponStatByName( sWeapon, 1, "deaths" );
}

trackAttackerLeaderBoardDeathStats( sWeapon, sMeansOfDeath )
{
	if ( isdefined( self ) && isplayer( self ) )
	{
		if ( sMeansOfDeath != "MOD_FALLING" )
		{
			if( sMeansOfDeath == "MOD_MELEE" && !IsSubStr( sWeapon, "riotshield" ) )
				return;
				
			self thread threadedSetWeaponStatByName( sWeapon, 1, "kills" );
		}
		
		if ( sMeansOfDeath == "MOD_HEAD_SHOT" )
		{
			self thread threadedSetWeaponStatByName( sWeapon, 1, "headShots" );
		}
	}
}

setWeaponStat( name, incValue, statName )
{
	if ( !incValue )
		return;
	
	weaponClass = getWeaponClass( name );
	
	// we are not currently tracking killstreaks or deathstreaks
	if( isKillstreakWeapon( name ) || weaponClass == "killstreak" || weaponClass == "deathstreak" || weaponClass == "other" )
		return;
		
	// we don't want to track environment weapons, like a mounted turret
	if( isEnvironmentWeapon( name ) )
		return;

	if( weaponClass == "weapon_grenade" || weaponClass == "weapon_riot" || weaponClass == "weapon_explosive" )
	{
			weaponName = strip_suffix( name, "_mp" );
			self maps\mp\gametypes\_persistence::incrementWeaponStat( weaponName, statName, incValue );
			self maps\mp\_matchdata::logWeaponStat( weaponName, statName, incValue);
			return;
	}
	
	if( statName != "deaths" )
	{
		name = self getCurrentWeapon();  
	}
	
	// defensive check to ensure current weapon isnt killstreak or deathstreaks weapon
	if( isKillstreakWeapon( name ) || weaponClass == "killstreak" || weaponClass == "deathstreak" || weaponClass == "other" )
		return; 
	
	if( !isdefined( self.trackingWeaponName ) )
		self.trackingWeaponName = name;
	
	if( name != self.trackingWeaponName )
	{
		self maps\mp\gametypes\_persistence::updateWeaponBufferedStats();
		self.trackingWeaponName = name;
	}
	
	switch( statName )
	{
		case "shots":
			self.trackingWeaponShots++;
			break;
		case "hits":
			self.trackingWeaponHits++;
			break;
		case "headShots":
			self.trackingWeaponHeadShots++;
			self.trackingWeaponHits++;
			break;
		case "kills":
			self.trackingWeaponKills++;
			break;
	}
	
	if( statName == "deaths" )
	{
		println("wrote deaths");
		tmp = name;
		tokens = strTok( name, "_" );
		
		altAttachment = undefined;
	
		//updating for IW5 weapons
		if ( tokens[0] == "iw5" )
			weaponName = tokens[0] + "_" + tokens[1];
		else if( tokens[0] == "alt" )
			weaponName = tokens[1] + "_" + tokens[2];
		else
			weaponName = tokens[0];
			
		if ( !isCACPrimaryWeapon( weaponName ) && !isCACSecondaryWeapon( weaponName ) )
			return;
		
		/*
		if ( isSubStr( weaponName, "akimbo" ) )
		{
			weaponName = fixAkimboString( weaponName, false );
		}
		*/
		
		if ( tokens[0] == "alt" )
		{
			weaponName = tokens[1] + "_" + tokens[2];
			
			foreach( token in tokens )
			{
				if ( token == "gl" || token == "gp25" || token == "m320" )
				{
					altAttachment = "gl";
					break;	
				}
				if ( token == "shotgun" )
				{
					altAttachment = "shotgun";
					break;	
				}
			}
		}
		
		if( isDefined( altAttachment) && ( altAttachment == "gl" || altAttachment == "shotgun" ) )
		{
			self maps\mp\gametypes\_persistence::incrementAttachmentStat( altAttachment, statName, incValue ); 
			self maps\mp\_matchdata::logAttachmentStat( altAttachment, statName, incValue);
			return;
		}
	
		self maps\mp\gametypes\_persistence::incrementWeaponStat( weaponName, statName, incValue );
		self maps\mp\_matchdata::logWeaponStat( weaponName, "deaths", incValue );
	
		//weaponAttachments = getWeaponAttachments( name );
		if( tokens[0] != "none" )
		{
			for( i = 0; i < tokens.size; i++ )
			{
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
				
				if(tokens[i] == "mp" )
					continue;
				
				if( isSubStr( tokens[i], "camo" ) )
					continue;
				
				//handles iw5 scoped weapons
				if( isSubStr( tokens[i], "scope" ) && !isSubStr( tokens[i], "vz" ) )
					continue; 
				
				if ( isSubStr( tokens[i], "scope" ) && isSubStr( tokens[i], "vz" ) )
					tokens[i] = "vzscope";
				
				tokens[i] = validateAttachment( tokens[i] );				
				
				//IW4 weapon check
				if ( i == 0 && ( tokens[i] != "iw5" && tokens[i] != "alt" ) )
					continue;
					
				self maps\mp\gametypes\_persistence::incrementAttachmentStat( tokens[i], statName, incValue ); 
				self maps\mp\_matchdata::logAttachmentStat( tokens[i], statName, incValue);
			}
		}
	}
}

setInflictorStat( eInflictor, eAttacker, sWeapon )
{
	if ( !isDefined( eAttacker ) )
		return;

	if ( !isDefined( eInflictor ) )
	{
		eAttacker setWeaponStat( sWeapon, 1, "hits" );
		return;
	}

	if ( !isDefined( eInflictor.playerAffectedArray ) )
		eInflictor.playerAffectedArray = [];

	foundNewPlayer = true;
	for ( i = 0 ; i < eInflictor.playerAffectedArray.size ; i++ )
	{
		if ( eInflictor.playerAffectedArray[i] == self )
		{
			foundNewPlayer = false;
			break;
		}
	}

	if ( foundNewPlayer )
	{
		eInflictor.playerAffectedArray[eInflictor.playerAffectedArray.size] = self;
		eAttacker setWeaponStat( sWeapon, 1, "hits" );
	}
}

threadedSetWeaponStatByName( name, incValue, statName )
{
	self endon("disconnect");
	waittillframeend;
	
	setWeaponStat( name, incValue, statName );
}

checkForPersonalBests()
{
	foreach ( player in level.players )
	{
		if ( !isDefined( player ) )
			continue;
			
		if( player rankingEnabled() )
		{
			roundKills = player getPlayerData( "round", "kills" );
			roundDeaths = player getPlayerData( "round", "deaths" );
			roundXP = player.pers["summary"]["xp"];
		
			//println( "roundKills val is " + roundKills);
			//println( "roundXP val is " + roundXP);
			//println( "roundDeaths val is " + roundDeaths);
		
			bestKills = player getPlayerData( "bestKills" );
			mostDeaths = player getPlayerData( "mostDeaths" );
			mostXp = player getPlayerData( "mostXp" );
		
			//println( "bestKills val is " + bestKills);
			//println( "mostXp val is " + mostXp);
			//println( "mostDeaths val is " + mostDeaths);
		
			if( roundKills > bestKills )
			{
				player setPlayerData( "bestKills", roundKills );
			}
		
			if( roundXP > mostXp )
			{
				player setPlayerData( "mostXp", roundXP );
			}
		
			if( roundDeaths > mostDeaths )
			{
				player setPlayerData( "mostDeaths", roundDeaths );
			}
		
			player checkForBestWeapon();
			player maps\mp\_matchdata::logPlayerXP( roundXP, "totalXp" );
			player maps\mp\_matchdata::logPlayerXP( player.pers["summary"]["score"], "scoreXp" );
			player maps\mp\_matchdata::logPlayerXP( player.pers["summary"]["challenge"], "challengeXp" );
			player maps\mp\_matchdata::logPlayerXP( player.pers["summary"]["match"], "matchXp" );
			player maps\mp\_matchdata::logPlayerXP( player.pers["summary"]["misc"], "miscXp" );
		}
		
		if ( isDefined( player.pers["confirmed"] ) )
		{
			player maps\mp\_matchdata::logKillsConfirmed();
		}
		if ( isDefined( player.pers["denied"] ) )
		{
			player maps\mp\_matchdata::logKillsDenied();
		}
		
	}
}

checkForBestWeapon()
{
	baseWeaponList =  maps\mp\_matchdata::buildBaseWeaponList();
	
	for( i = 0; i < baseWeaponList.size; i++ )
	{
		weaponName = baseWeaponList[i];
		
		tokens = strTok( weaponName, "_" );
	
		//updating for IW5 weapons
		if ( tokens[0] == "iw5" )
			weaponName = tokens[0] + "_" + tokens[1];
		
		if ( tokens[0] == "alt" )
			weaponName = tokens[1] + "_" + tokens[2];
		
		/*
		if ( isSubStr( weaponName, "akimbo" ) )
		{
			weaponName = fixAkimboString( weaponName, false );
		}
		*/
		
		weaponClass = getWeaponClass( weaponName );
		
		if( !isKillstreakWeapon( weaponName ) && weaponClass != "killstreak" && weaponClass != "deathstreak" && weaponClass != "other" )
		{
		
			bestWeaponKills = self getPlayerData( "bestWeapon", "kills" );
		
			weaponKills = getMatchData( "players", self.clientid, "weaponStats", weaponName, "kills" );
		
			if( weaponKills > bestWeaponKills )
			{
				self setPlayerData( "bestWeapon", "kills", weaponKills );
				weaponShots = getMatchData( "players", self.clientid, "weaponStats", weaponName, "shots" );
				weaponHeadShots = getMatchData( "players", self.clientid, "weaponStats", weaponName, "headShots" );
				weaponHits = getMatchData( "players", self.clientid, "weaponStats", weaponName, "hits" );
				weaponDeaths = getMatchData( "players", self.clientid, "weaponStats", weaponName, "deaths" );
				weaponXP = getMatchData( "players", self.clientid, "weaponStats", weaponName, "XP" );
			
				self setPlayerData( "bestWeapon", "shots", weaponShots );
				self setPlayerData( "bestWeapon", "headShots", weaponHeadShots );
				self setPlayerData( "bestWeapon", "hits", weaponHits );
				self setPlayerData( "bestWeapon", "deaths", weaponDeaths );
				self setPlayerData( "bestWeaponXP", weaponXP );
				self setPlayerData( "bestWeaponIndex", i );
			}
		}
	}
}