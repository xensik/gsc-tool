#include maps\mp\_utility;
#include common_scripts\utility;

processLobbyScoreboards()
{
	foreach ( player in level.placement["all"] )
		player setPlayerScoreboardInfo();

	if ( level.teamBased )
	{
		alliesScore = getTeamScore( "allies" );
		axisScore = getTeamScore( "axis" );
	
		if ( alliesScore == axisScore )
			winner = "tied";
		else if ( alliesScore > axisScore )
			winner = "allies";
		else
			winner = "axis";

		if ( winner == "tied" )
		{
			// build both, assign type to your team
			buildScoreboardType( "allies" );
			buildScoreboardType( "axis" );
			
			foreach ( player in level.players )	
			{
				if ( player.pers["team"] == "spectator" )
					player setPlayerData( "round", "scoreboardType", "allies" );
				else
					player setPlayerData( "round", "scoreboardType", player.pers["team"] );
			}
		}
		else
		{
			// build just winner, assign type to winner
			buildScoreboardType( winner );

			foreach ( player in level.players )	
				player setPlayerData( "round", "scoreboardType", winner );
		}
	}
	else // not teambased
	{
		buildScoreboardType( "neutral" );

		foreach ( player in level.players )	
			player setPlayerData( "round", "scoreboardType", "neutral" );
	}

	foreach ( player in level.players )
	{
		// TODO: convert this to round stats
		player setClientDvars(
				"player_summary_xp", player.pers["summary"]["xp"],
				"player_summary_score", player.pers["summary"]["score"],
				"player_summary_challenge", player.pers["summary"]["challenge"],
				"player_summary_match", player.pers["summary"]["match"],
				"player_summary_misc", player.pers["summary"]["misc"]
			);
	}
}

setPlayerScoreboardInfo()
{
	scoreboardPlayerCount = getClientMatchData( "scoreboardPlayerCount" );
	if ( scoreboardPlayerCount <= 24 ) //MaxPlayers
	{
		setClientMatchData( "players", self.clientMatchDataId, "score", self.pers["score"] );
		println( "Scoreboard: [" + self.name + "(" + self.clientMatchDataId + ")][score]: " + self.pers["score"] );

		kills = self getPlayerStat( "kills" );
		setClientMatchData( "players", self.clientMatchDataId, "kills", kills );
		println( "Scoreboard: [" + self.name + "(" + self.clientMatchDataId + ")][kills]: " + kills );
		
		assists = self getPlayerStat( "assists" );
		setClientMatchData( "players", self.clientMatchDataId, "assists", assists );
		println( "Scoreboard: [" + self.name + "(" + self.clientMatchDataId + ")][assists]: " + assists );
		
		deaths = self getPlayerStat( "deaths" );
		setClientMatchData( "players", self.clientMatchDataId, "deaths", deaths );
		println( "Scoreboard: [" + self.name + "(" + self.clientMatchDataId + ")][deaths]: " + deaths );

		faction = game[self.pers["team"]];
		setClientMatchData( "players", self.clientMatchDataId, "faction", faction );
		println( "Scoreboard: [" + self.name + "(" + self.clientMatchDataId + ")][faction]: " + faction );

		println( "Scoreboard: scoreboardPlayerCount was " + scoreboardPlayerCount );
		scoreboardPlayerCount++;
		setClientMatchData( "scoreboardPlayerCount", scoreboardPlayerCount );
		println( "Scoreboard: scoreboardPlayerCount now " + scoreboardPlayerCount );
	}
	else
	{
		println( "Scoreboard: scoreboardPlayerCount is greater than 24 (" + scoreboardPlayerCount + ")" );
	}
}

buildScoreboardType( team )
{
	assert( team == "allies" || team == "axis" || team == "neutral" );

	println( "Scoreboard: Building scoreboard (" + team + ")" );

	if ( team == "neutral" )
	{
		index = 0;
		foreach ( player in level.placement["all"] )
		{
			setClientMatchData( "scoreboards", team, index, player.clientMatchDataId );
			println( "Scoreboard: [scoreboards][" + team + "][" + index + "][" + player.clientMatchDataId + "]" );
			index++;
		}
	}
	else
	{
		otherTeam = getOtherTeam( team );
		
		index = 0;
		foreach ( player in level.placement[team] )
		{
			setClientMatchData( "scoreboards", team, index, player.clientMatchDataId );
			println( "Scoreboard: [scoreboards][" + team + "][" + index + "][" + player.name + "(" + player.clientMatchDataId + ")]" );
			index++;
		}
		
		foreach ( player in level.placement[otherTeam] )
		{
			setClientMatchData( "scoreboards", team, index, player.clientMatchDataId );
			println( "Scoreboard: [scoreboards][" + team + "][" + index + "][" + player.name + "(" + player.clientMatchDataId + ")]" );
			index++;
		}
	}
}