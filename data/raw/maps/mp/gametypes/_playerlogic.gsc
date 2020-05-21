#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;


TimeUntilWaveSpawn( minimumWait )
{
	if ( !self.hasSpawned )
		return 0;

	// the time we'll spawn if we only wait the minimum wait.
	earliestSpawnTime = gettime() + minimumWait * 1000;
	
	lastWaveTime = level.lastWave[self.pers["team"]];
	waveDelay = level.waveDelay[self.pers["team"]] * 1000;
	
	// the number of waves that will have passed since the last wave happened, when the minimum wait is over.
	numWavesPassedEarliestSpawnTime = (earliestSpawnTime - lastWaveTime) / waveDelay;
	// rounded up
	numWaves = ceil( numWavesPassedEarliestSpawnTime );
	
	timeOfSpawn = lastWaveTime + numWaves * waveDelay;

	// don't push our spawn out because we watched killcam
	if ( isDefined( self.respawnTimerStartTime ) )
	{
		timeAlreadyPassed = (gettime() - self.respawnTimerStartTime) / 1000.0;
		
		if ( self.respawnTimerStartTime < lastWaveTime )
			return 0;
	}
	
	// avoid spawning everyone on the same frame
	if ( isdefined( self.waveSpawnIndex ) )
		timeOfSpawn += 66 * self.waveSpawnIndex;
	
	return (timeOfSpawn - gettime()) / 1000;
}

TeamKillDelay()
{
	teamKills = self.pers["teamkills"];

	if ( level.maxAllowedTeamKills < 0 || teamkills <= level.maxAllowedTeamKills )
		return 0;

	exceeded = (teamkills - level.maxAllowedTeamKills);
	return maps\mp\gametypes\_tweakables::getTweakableValue( "team", "teamkillspawndelay" ) * exceeded;
}


TimeUntilSpawn( includeTeamkillDelay )
{
	if ( (level.inGracePeriod && !self.hasSpawned) || level.gameended )
		return 0;
	
	respawnDelay = 0;
	if ( self.hasSpawned )
	{
		result = self [[level.onRespawnDelay]]();
		if ( isDefined( result ) )
			respawnDelay = result;
		else
			respawnDelay = getDvarInt( "scr_" + level.gameType + "_playerrespawndelay" );
		
		if ( includeTeamkillDelay && isDefined( self.pers["teamKillPunish"] ) && self.pers["teamKillPunish"] )
			respawnDelay += TeamKillDelay();
		
		if ( isDefined( self.respawnTimerStartTime ) )
		{
			timeAlreadyPassed = (gettime() - self.respawnTimerStartTime) / 1000.0;
			respawnDelay -= timeAlreadyPassed;
			if ( respawnDelay < 0 )
				respawnDelay = 0;
		}
		
		// Spawning with tactical insertion
    	if ( isDefined( self.setSpawnPoint) )
    		respawnDelay += level.tiSpawnDelay;
		
	}

	waveBased = (getDvarInt( "scr_" + level.gameType + "_waverespawndelay" ) > 0);

	if ( waveBased )
		return self TimeUntilWaveSpawn( respawnDelay );
	
	return respawnDelay;
}


maySpawn()
{
	if ( getGametypeNumLives() || isDefined( level.disableSpawning ) )
	{
		if ( isDefined( level.disableSpawning ) && level.disableSpawning )
			return false;

		if ( isDefined( self.pers["teamKillPunish"] ) && self.pers["teamKillPunish"] )
			return false;

		if ( !self.pers["lives"] && gameHasStarted() )
		{
			return false;
		}
		else if ( gameHasStarted() )
		{
			// disallow spawning for late comers
			if ( !level.inGracePeriod && !self.hasSpawned )
				return false;
		}
	}
	return true;
}


spawnClient()
{
	assert(	isDefined( self.team ) );
	assert(	isValidClass( self.class ) );
	
	if ( !self maySpawn() )
	{
		currentorigin =	self.origin;
		currentangles =	self.angles;
		
		self notify ( "attempted_spawn" );

		if ( isDefined( self.pers["teamKillPunish"] ) && self.pers["teamKillPunish"] )
		{
			self.pers["teamkills"] = max( self.pers["teamkills"] - 1, 0 );
			setLowerMessage( "friendly_fire", &"MP_FRIENDLY_FIRE_WILL_NOT" );

			if ( !self.hasSpawned && self.pers["teamkills"] <= level.maxAllowedTeamkills )
				self.pers["teamKillPunish"] = false;

		}
		else if ( isRoundBased() && !isLastRound() )
		{
			setLowerMessage( "spawn_info", game["strings"]["spawn_next_round"] );
			self thread removeSpawnMessageShortly( 3.0 );
		}

		self thread	spawnSpectator( currentorigin	+ (0, 0, 60), currentangles	);
		return;
	}
	
	if ( self.waitingToSpawn )
		return;
		
	self.waitingToSpawn = true;
	
	self waitAndSpawnClient();
	
	if ( isdefined( self ) )
		self.waitingToSpawn = false;
}


waitAndSpawnClient()
{
	self endon ( "disconnect" );
	self endon ( "end_respawn" );
	level endon ( "game_ended" );
	
	self notify ( "attempted_spawn" );

	spawnedAsSpectator = false;
	
	if ( isDefined( self.pers["teamKillPunish"] ) && self.pers["teamKillPunish"] )
	{
		teamKillDelay = TeamKillDelay();
		
		if ( teamKillDelay > 0 )
		{
			setLowerMessage( "friendly_fire", &"MP_FRIENDLY_FIRE_WILL_NOT", teamKillDelay );
			
			self thread	respawn_asSpectator( self.origin + (0, 0, 60), self.angles );
			spawnedAsSpectator = true;
			
			wait( teamKillDelay );
			clearLowerMessage( "friendly_fire" );
			self.respawnTimerStartTime = gettime();
		}
		
		self.pers["teamKillPunish"] = false;
	}
	else if ( TeamKillDelay() )
	{
		self.pers["teamkills"] = max( self.pers["teamkills"] - 1, 0 );
	}
	
	// for missiles, helicopters, ac130, etc...
	if ( self isUsingRemote() )
	{
		//	- when killed while using a remote, the player's location remains at their corpse
		//	- the using remote variable is cleared before they are actually respawned and moved
		//	- if you want control over proximity related events with relation to their corpse location
		//    between the clearing of the remote variables and their actual respawning somewhere else use this variable	
		self.spawningAfterRemoteDeath = true;
		self waittill ( "stopped_using_remote" );
	}
	
	if ( !isdefined( self.waveSpawnIndex ) && isdefined( level.wavePlayerSpawnIndex[self.team] ) )
	{
		self.waveSpawnIndex = level.wavePlayerSpawnIndex[self.team];
		level.wavePlayerSpawnIndex[self.team]++;
	}
	
	timeUntilSpawn = TimeUntilSpawn( false );
	
	self thread predictAboutToSpawnPlayerOverTime( timeUntilSpawn );
	
	if ( timeUntilSpawn > 0 )
	{
		// spawn player into spectator on death during respawn delay, if he switches teams during this time, he will respawn next round
		setLowerMessage( "spawn_info", game["strings"]["waiting_to_spawn"], timeUntilSpawn, 1, true );
		
		if ( !spawnedAsSpectator )
			self thread	respawn_asSpectator( self.origin + (0, 0, 60), self.angles );
		spawnedAsSpectator = true;
		
		self waitForTimeOrNotify( timeUntilSpawn, "force_spawn" );
		
		self notify("stop_wait_safe_spawn_button");
	}
	
	waveBased = (getDvarInt( "scr_" + level.gameType + "_waverespawndelay" ) > 0);
	if ( maps\mp\gametypes\_tweakables::getTweakableValue( "player", "forcerespawn" ) == 0 && self.hasSpawned && !waveBased && !self.wantSafeSpawn )
	{
		setLowerMessage( "spawn_info", game["strings"]["press_to_spawn"], undefined, undefined, undefined, undefined, undefined, undefined, true );
		
		if ( !spawnedAsSpectator )
			self thread	respawn_asSpectator( self.origin + (0, 0, 60), self.angles );
		spawnedAsSpectator = true;
		
		self waitRespawnButton();
	}
	
	// do not wait after this point
	
	self.waitingToSpawn = false;
	
	self clearLowerMessage( "spawn_info" );
	
	self.waveSpawnIndex = undefined;
	
	self thread	spawnPlayer();
}


waitRespawnButton()
{
	self endon("disconnect");
	self endon("end_respawn");

	while (1)
	{
		if ( self useButtonPressed() )
			break;

		wait .05;
	}
}


removeSpawnMessageShortly( delay )
{
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	waittillframeend; // so we don't endon the end_respawn from spawning as a spectator
	
	self endon("end_respawn");
	
	wait delay;
	
	self clearLowerMessage( "spawn_info" );
}


lastStandRespawnPlayer()
{
	self LastStandRevive();

	if ( self _hasPerk( "specialty_finalstand" ) && !level.dieHardMode )
		self _unsetPerk( "specialty_finalstand" );

	if ( level.dieHardMode )
		self.headicon = "";
	
	self setStance( "crouch" );	
	self.revived = true;
	
	self notify ( "revive" );
	
	// should only be defined if level.diehardmode
	if ( isDefined( self.standardmaxHealth ) )
		self.maxHealth = self.standardMaxHealth;
	
	self.health = self.maxHealth;
	self _enableUsability();
	
	if ( game["state"] == "postgame" )
	{
		assert( !level.intermission );
		// We're in the victory screen, but before intermission
		self maps\mp\gametypes\_gamelogic::freezePlayerForRoundEnd();
	}
}

getDeathSpawnPoint()
{
	spawnpoint = spawn( "script_origin", self.origin );
	spawnpoint hide();
	spawnpoint.angles = self.angles;
	return spawnpoint;

}

showSpawnNotifies()
{
	if ( isDefined( game["defcon"] ) )
		thread maps\mp\gametypes\_hud_message::defconSplashNotify( game["defcon"], false );	

	if ( self isRested() )
		thread maps\mp\gametypes\_hud_message::splashNotify( "rested" );
}


predictAboutToSpawnPlayerOverTime( preduration )
{
	self endon( "disconnect" );
	self endon( "spawned" );
	self endon( "used_predicted_spawnpoint" );
	self notify( "predicting_about_to_spawn_player" );
	self endon( "predicting_about_to_spawn_player" );
	
	if ( preduration <= 0 )
		return; // no point predicting if no time will pass. (if time until spawn is unknown, use 0.1)
	
	if ( preduration > 1.0 )
		wait preduration - 1.0;
	
	self predictAboutToSpawnPlayer();
	
	self PredictStreamPos( self.predictedSpawnPoint.origin + (0,0,60), self.predictedSpawnPoint.angles );
	self.predictedSpawnPointTime = gettime();
	
	for ( i = 0; i < 30; i++ )
	{
		wait .4; // this time is carefully selected: we want it as long as possible, but we want the loop to iterate about .1 to .3 seconds before people spawn for our final check
		
		prevPredictedSpawnPoint = self.predictedSpawnPoint;
		self predictAboutToSpawnPlayer();
		
		if ( self.predictedSpawnPoint != prevPredictedSpawnPoint )
		{
			self PredictStreamPos( self.predictedSpawnPoint.origin + (0,0,60), self.predictedSpawnPoint.angles );
			self.predictedSpawnPointTime = gettime();
		}
	}
}

predictAboutToSpawnPlayer()
{
	assert( !isReallyAlive( self ) );
	
	// test predicting spawnpoints to see if we can eliminate streaming pops
	
	if ( self TimeUntilSpawn( true ) > 1.0 )
	{
		spawnpointname = "mp_global_intermission";
		spawnpoints = getentarray(spawnpointname, "classname");
		assert( spawnpoints.size );
		self.predictedSpawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random(spawnpoints);
		return;
	}
	
	if ( isDefined( self.setSpawnPoint ) )
	{
		self.predictedSpawnPoint = self.setSpawnPoint;
		return;
	}
	spawnPoint = self [[level.getSpawnPoint]]();
	self.predictedSpawnPoint = spawnPoint;
}

checkPredictedSpawnpointCorrectness( spawnpointorigin )
{
	/#
	if ( !isdefined( level.spawnpointPrediction ) )
	{
		level.spawnpointPrediction = spawnstruct();
		level.spawnpointPrediction.failures = 0;
		for ( i = 0; i < 7; i++ )
			level.spawnpointPrediction.buckets[i] = 0;
	}
	
	if ( !isdefined( self.predictedSpawnPoint ) )
	{
		println( "Failed to predict spawn for player " + self.name + " at " + spawnpointorigin );
		level.spawnpointPrediction.failures++;
	}
	else
	{
		dist = distance( self.predictedSpawnPoint.origin, spawnpointorigin );
		if ( dist <= 0 )
			level.spawnpointPrediction.buckets[0]++;
		else if ( dist <= 128 )
			level.spawnpointPrediction.buckets[1]++;
		else if ( dist <= 256 )
			level.spawnpointPrediction.buckets[2]++;
		else if ( dist <= 512 )
			level.spawnpointPrediction.buckets[3]++;
		else if ( dist <= 1024 )
			level.spawnpointPrediction.buckets[4]++;
		else if ( dist <= 2048 )
			level.spawnpointPrediction.buckets[5]++;
		else
			level.spawnpointPrediction.buckets[6]++;
		
		if ( dist > 0 )
			println( "Predicted player " + self.name + " would spawn at " + self.predictedSpawnPoint.origin + ", but spawned " + dist + " units away at " + spawnpointorigin );
		else
			println( "Predicted " + self.name + "'s spawn " + ((gettime() - self.predictedSpawnPointTime) / 1000) + " seconds ahead of time" );
	}
	#/
	
	self notify( "used_predicted_spawnpoint" );
	self.predictedSpawnPoint = undefined;
}

percentage( a, b )
{
	return a + " (" + int(a / b * 100) + "%)";
}

printPredictedSpawnpointCorrectness()
{
	/#
	if ( !isdefined( level.spawnpointPrediction ) )
		return;
	
	total = level.spawnpointPrediction.failures;
	for ( i = 0; i < 7; i++ )
		total += level.spawnpointPrediction.buckets[i];
	
	if ( total <= 0 )
		return;
	
	println( "****** Spawnpoint Prediction *******" );
	println( "There were " + total + " spawns. " + percentage( level.spawnpointPrediction.failures, total ) + " failed to be predicted." );
	
	total -= level.spawnpointPrediction.failures;
	if ( total > 0 )
	{
		println( "Out of the predicted ones..." );
		
		println( " " + percentage( level.spawnpointPrediction.buckets[0], total ) + " were perfect" );
		println( " " + percentage( level.spawnpointPrediction.buckets[1], total ) + " were within 128 units" );
		println( " " + percentage( level.spawnpointPrediction.buckets[2], total ) + " were within 256 units" );
		println( " " + percentage( level.spawnpointPrediction.buckets[3], total ) + " were within 512 units" );
		println( " " + percentage( level.spawnpointPrediction.buckets[4], total ) + " were within 1024 units" );
		println( " " + percentage( level.spawnpointPrediction.buckets[5], total ) + " were within 2048 units" );
		println( " " + percentage( level.spawnpointPrediction.buckets[6], total ) + " were beyond 2048 units" );
	}
	
	println( "*************" );
	#/
}

getSpawnOrigin( spawnpoint )
{
	if ( !positionWouldTelefrag( spawnpoint.origin ) )
		return spawnpoint.origin;
	
	if ( !isdefined( spawnpoint.alternates ) )
		return spawnpoint.origin;
	
	foreach( alternate in spawnpoint.alternates )
	{
		if ( !positionWouldTelefrag( alternate ) )
			return alternate;
	}
	
	return spawnpoint.origin;
}

tiValidationCheck()
{
	if ( !isDefined( self.setSpawnPoint ) )
		return false;
		
	carePackages = getEntArray( "care_package", "targetname" );
	
	foreach ( package in carePackages )
	{
		if ( distance( package.origin, self.setSpawnPoint.playerSpawnPos ) > 64 )
			continue;
		
		if ( isDefined( package.owner ) )
			self maps\mp\gametypes\_hud_message::playerCardSplashNotify( "destroyed_insertion", package.owner );

		maps\mp\perks\_perkfunctions::deleteTI( self.setSpawnpoint );
		return false;
	}	
	
	return true;
}

spawnPlayer()
{
	self endon( "disconnect" );
	self endon( "joined_spectators" );
	self notify( "spawned" );
	self notify( "end_respawn" );
	
    if ( isDefined( self.setSpawnPoint ) && self tiValidationCheck() )
	{
		spawnPoint = self.setSpawnPoint;

		self playLocalSound( "tactical_spawn" );
		
		if ( level.teamBased )
			self playSoundToTeam( "tactical_spawn", level.otherTeam[self.team] );
		else
			self playSound( "tactical_spawn" );

		assert( isDefined( spawnPoint.playerSpawnPos ) );
		assert( isDefined( spawnPoint.angles ) );
			
		spawnOrigin = self.setSpawnPoint.playerSpawnPos;
		spawnAngles = self.setSpawnPoint.angles;		

		if ( isDefined( self.setSpawnPoint.enemyTrigger ) )
			 self.setSpawnPoint.enemyTrigger Delete();
		
		self.setSpawnPoint delete();

		spawnPoint = undefined;
	}
	else
	{
		spawnPoint = self [[level.getSpawnPoint]]();

		assert( isDefined( spawnPoint ) );
		assert( isDefined( spawnPoint.origin ) );
		assert( isDefined( spawnPoint.angles ) );

		spawnOrigin = spawnpoint.origin;
		spawnAngles = spawnpoint.angles;
	}
	
	
	self setSpawnVariables();

	/#
	if ( !getDvarInt( "scr_forcerankedmatch" ) )
		assert( (level.teamBased && ( !allowTeamChoice() || self.sessionteam == self.team )) || (!level.teamBased && self.sessionteam == "none") );
	#/

	hadSpawned = self.hasSpawned;

	self.fauxDead = undefined;

	self.killsThisLife = [];
	
	self updateSessionState( "playing", "" );
	self ClearKillcamState();
	self.cancelkillcam = 1;
	self openMenu( "killedby_card_hide" );

	self.maxhealth = maps\mp\gametypes\_tweakables::getTweakableValue( "player", "maxhealth" );

	self.health = self.maxhealth;
	
	self.friendlydamage = undefined;
	self.hasSpawned = true;
	self.spawnTime = getTime();
	self.wasTI = !isDefined( spawnPoint );
	self.afk = false;
	self.lastStand = undefined;
	self.infinalStand = undefined;
	self.inC4Death = undefined;
	self.damagedPlayers = [];
	self.moveSpeedScaler = 1;
	self.killStreakScaler = 1;
	self.xpScaler = 1;
	self.objectiveScaler = 1;
	self.inLastStand = false;
	self.clampedHealth = undefined;
	self.shieldDamage = 0;
	self.shieldBulletHits = 0;
	self.recentShieldXP = 0;
	
	self.disabledWeapon = 0;
	self.disabledWeaponSwitch = 0;
	self.disabledOffhandWeapons = 0;
	self resetUsability();

	// trying to stop killstreaks from targeting the newly spawned
	self.avoidKillstreakOnSpawnTimer = 5.0;

	if ( self.pers["lives"] == getGametypeNumLives() )
	{
		maps\mp\gametypes\_playerlogic::addToLivesCount();
	}
	
	if ( self.pers["lives"] )
		self.pers["lives"]--;

	self maps\mp\gametypes\_playerlogic::addToAliveCount();

	if ( !hadSpawned || gameHasStarted() || (gameHasStarted() && level.inGracePeriod && self.hasDoneCombat) )
		self maps\mp\gametypes\_playerlogic::removeFromLivesCount();

	if ( !self.wasAliveAtMatchStart )
	{
		acceptablePassedTime = 20;
		if ( getTimeLimit() > 0 && acceptablePassedTime < getTimeLimit() * 60 / 4 )
			acceptablePassedTime = getTimeLimit() * 60 / 4;
		
		if ( level.inGracePeriod || getTimePassed() < acceptablePassedTime * 1000 )
			self.wasAliveAtMatchStart = true;
	}
	
	self setClientDvar( "cg_thirdPerson", "0" );
	self setDepthOfField( 0, 0, 512, 512, 4, 0 );
	self setClientDvar( "cg_fov", "65" );

	// Don't do this stuff for TI spawn points	
	if ( isDefined( spawnPoint ) )
	{
		self maps\mp\gametypes\_spawnlogic::finalizeSpawnpointChoice( spawnpoint );
		spawnOrigin = getSpawnOrigin( spawnpoint );
		spawnAngles = spawnpoint.angles;
	}
	else
	{
		// the only useful part of finalizeSpawnpointChoice() when using tactical insertion
		self.lastSpawnTime = getTime();
	}

	self.spawnPos = spawnOrigin;

	self spawn( spawnOrigin, spawnAngles );
	[[level.onSpawnPlayer]]();
	
	// Don't do this stuff for TI spawn points	
	if ( isDefined( spawnPoint ) )
		self checkPredictedSpawnpointCorrectness( spawnPoint.origin );
	
	self maps\mp\gametypes\_missions::playerSpawned();
	
	prof_begin( "spawnPlayer_postUTS" );
	
	assert( isValidClass( self.class ) );
	
	self maps\mp\gametypes\_class::setClass( self.class );
	self maps\mp\gametypes\_class::giveLoadout( self.team, self.class );

	if ( getDvarInt( "camera_thirdPerson" ) )
		self setThirdPersonDOF( true );

	if ( !gameFlag( "prematch_done" ) )
		self freezeControlsWrapper( true );
	else
		self freezeControlsWrapper( false );

	if ( !gameFlag( "prematch_done" ) || !hadSpawned && game["state"] == "playing" )
	{
		self setClientDvar( "scr_objectiveText", getObjectiveHintText( self.pers["team"] ) );

		team = self.pers["team"];
		
		if ( game["status"] == "overtime" )
			thread maps\mp\gametypes\_hud_message::oldNotifyMessage( game["strings"]["overtime"], game["strings"]["overtime_hint"], undefined, (1, 0, 0), "mp_last_stand" );
		else if ( getIntProperty( "useRelativeTeamColors", 0 ) )
			thread maps\mp\gametypes\_hud_message::oldNotifyMessage( game["strings"][team + "_name"], undefined, game["icons"][team] + "_blue", game["colors"]["blue"] );
		else
			thread maps\mp\gametypes\_hud_message::oldNotifyMessage( game["strings"][team + "_name"], undefined, game["icons"][team], game["colors"][team] );

		thread showSpawnNotifies();
	}

	if ( !level.splitscreen && getIntProperty( "scr_showperksonspawn", 1 ) == 1 && game["state"] != "postgame" )
	{
		self openMenu( "perk_display" );
		self thread hidePerksAfterTime( 4.0 );
		self thread hidePerksOnDeath();
	}

	prof_end( "spawnPlayer_postUTS" );

	//self logstring( "S " + self.origin[0] + " " + self.origin[1] + " " + self.origin[2] );
	
	// give "connected" handlers a chance to start
	// many of these start onPlayerSpawned handlers which rely on the "spawned_player"
	// notify which can happen on the same frame as the "connected" notify
	waittillframeend;

	//	- when killed while using a remote, the player's location remains at their corpse
	//	- the using remote variable is cleared before they are actually respawned and moved
	//	- if you want control over proximity related events with relation to their corpse location
	//    between the clearing of the remote variables and their actual respawning somewhere else use this variable
	self.spawningAfterRemoteDeath = undefined;

	self notify( "spawned_player" );
	level notify ( "player_spawned", self );
	
	if ( game["state"] == "postgame" )
	{
		assert( !level.intermission );
		// We're in the victory screen, but before intermission
		self maps\mp\gametypes\_gamelogic::freezePlayerForRoundEnd();
	}	
}

hidePerksAfterTime( delay )
{
	self endon("disconnect");
	self endon("perks_hidden");
	
	wait delay;

	self openMenu( "perk_hide" );
	self notify("perks_hidden");
}

hidePerksOnDeath()
{
	self endon("disconnect");
	self endon("perks_hidden");

	self waittill("death");
	
	self openMenu( "perk_hide" );
	self notify("perks_hidden");
}

hidePerksOnKill()
{
	self endon("disconnect");
	self endon("death");
	self endon("perks_hidden");

	self waittill( "killed_player" );
	
	self openMenu( "perk_hide" );
	self notify("perks_hidden");
}


spawnSpectator( origin, angles )
{
	self notify("spawned");
	self notify("end_respawn");
	self notify("joined_spectators");
	in_spawnSpectator( origin, angles );
}

// spawnSpectator clone without notifies for spawning between respawn delays
respawn_asSpectator( origin, angles )
{
	in_spawnSpectator( origin, angles );
}

// spawnSpectator helper
in_spawnSpectator( origin, angles )
{
	self setSpawnVariables();
	
	// don't clear lower message if not actually a spectator,
	// because it probably has important information like when we'll spawn
	if ( isDefined( self.pers["team"] ) && self.pers["team"] == "spectator" && !level.gameEnded )
		self clearLowerMessage( "spawn_info" );
	
	self.sessionstate = "spectator";
	self ClearKillcamState();
	self.friendlydamage = undefined;

	if( isDefined( self.pers["team"] ) && self.pers["team"] == "spectator" )
		self.statusicon = "";
	else
		self.statusicon = "hud_status_dead";

	maps\mp\gametypes\_spectating::setSpectatePermissions();

	onSpawnSpectator( origin, angles );
	
	if ( level.teamBased && !level.splitscreen )
		self setDepthOfField( 0, 128, 512, 4000, 6, 1.8 );
}


getPlayerFromClientNum( clientNum )
{
	if ( clientNum < 0 )
		return undefined;
	
	for ( i = 0; i < level.players.size; i++ )
	{
		if ( level.players[i] getEntityNumber() == clientNum )
			return level.players[i];
	}
	return undefined;
}


onSpawnSpectator( origin, angles)
{
	if( isDefined( origin ) && isDefined( angles ) )
	{
		self SetSpectateDefaults( origin, angles );
		self spawn(origin, angles);
		
		self checkPredictedSpawnpointCorrectness( origin );
		return;
	}
	
	spawnpointname = "mp_global_intermission";
	spawnpoints = getentarray(spawnpointname, "classname");
	assert( spawnpoints.size );
	spawnpoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random(spawnpoints);

	self SetSpectateDefaults(spawnpoint.origin, spawnpoint.angles);
	self spawn(spawnpoint.origin, spawnpoint.angles);
	
	self checkPredictedSpawnpointCorrectness( spawnpoint.origin );
}


spawnIntermission()
{
	self endon( "disconnect" );
	
	self notify( "spawned" );
	self notify( "end_respawn" );
	
	self setSpawnVariables();
	self closepopupMenu();
	self closeInGameMenu();
	
	self clearLowerMessages();
	
	self freezeControlsWrapper( true );
	
	self setClientDvar( "cg_everyoneHearsEveryone", 1 );

	if ( level.rankedMatch && ( self.postGamePromotion || self.pers["postGameChallenges"] ) )
	{
		if ( self.postGamePromotion )
			self playLocalSound( "mp_level_up" );
		else
			self playLocalSound( "mp_challenge_complete" );

		if ( self.postGamePromotion > level.postGameNotifies )
			level.postGameNotifies = 1;

		if ( self.pers["postGameChallenges"] > level.postGameNotifies )
			level.postGameNotifies = self.pers["postGameChallenges"];

		self closepopupMenu();
		self closeInGameMenu();	

		self openMenu( game["menu_endgameupdate"] );

		waitTime = 4.0 + min( self.pers["postGameChallenges"], 3 );		
		while ( waitTime )
		{
			wait ( 0.25 );
			waitTime -= 0.25;

			self openMenu( game["menu_endgameupdate"] );
		}
		
		self closeMenu( game["menu_endgameupdate"] );
	}
	
	self.sessionstate = "intermission";
	self ClearKillcamState();
	self.friendlydamage = undefined;
	
	spawnPoints = getEntArray( "mp_global_intermission", "classname" );
	assertEx( spawnPoints.size, "NO mp_global_intermission SPAWNPOINTS IN MAP" );

	spawnPoint = spawnPoints[0];
	self spawn( spawnPoint.origin, spawnPoint.angles );
	
	self checkPredictedSpawnpointCorrectness( spawnPoint.origin );
	
	self setDepthOfField( 0, 128, 512, 4000, 6, 1.8 );
}


spawnEndOfGame()
{
	if ( 1 )
	{
		self freezeControlsWrapper( true );
		self spawnSpectator();
		self freezeControlsWrapper( true );
		return;
	}
	
	self notify("spawned");
	self notify("end_respawn");
	
	self setSpawnVariables();
	self closepopupMenu();
	self closeInGameMenu();
	
	self clearLowerMessages();

	self setClientDvar( "cg_everyoneHearsEveryone", 1 );

	self.sessionstate = "dead";
	self ClearKillcamState();
	self.friendlydamage = undefined;

	spawnPoints = getEntArray( "mp_global_intermission", "classname" );
	assertEx( spawnPoints.size, "NO mp_global_intermission SPAWNPOINTS IN MAP" );

	spawnPoint = spawnPoints[0];
	self spawn( spawnPoint.origin, spawnPoint.angles );
	
	self checkPredictedSpawnpointCorrectness( spawnPoint.origin );
	
	spawnPoint setModel( "tag_origin" );
	
	//self playerLinkTo( spawnPoint, "tag_origin", (0,0,0), spawnPoint.angles );
	self playerLinkTo( spawnPoint );

	self PlayerHide();
	self freezeControlsWrapper( true );
	
	self setDepthOfField( 0, 128, 512, 4000, 6, 1.8 );
}


setSpawnVariables()
{
	// Stop shellshock and rumble
	self StopShellshock();
	self StopRumble( "damage_heavy" );
}


notifyConnecting()
{
	waittillframeend;

	if( isDefined( self ) )
		level notify( "connecting", self );
}


Callback_PlayerDisconnect()
{
	if ( !isDefined( self.connected ) )
		return;

	self removePlayerOnDisconnect();

	if ( !level.teamBased )
		game["roundsWon"][self.guid] = undefined;
	
	//if ( !level.gameEnded )
	//	self logXPGains();
	
	if ( level.splitscreen )
	{
		players = level.players;
		
		if ( players.size <= 1 )
			level thread maps\mp\gametypes\_gamelogic::forceEnd();
	}

	if ( isDefined( self.score ) && isDefined( self.pers["team"] ) )
	{
		setPlayerTeamRank( self, self.clientid, self.score - 5 * self.deaths );		
	}
	
	lpselfnum = self getEntityNumber();
	lpGuid = self.guid;
	logPrint("Q;" + lpGuid + ";" + lpselfnum + ";" + self.name + "\n");

	self thread maps\mp\_events::disconnected();

	if ( level.gameEnded )
		self maps\mp\gametypes\_gamescore::removeDisconnectedPlayerFromPlacement();
	
	if ( isDefined( self.team ) )
		self maps\mp\gametypes\_playerlogic::removeFromTeamCount();
	
	if ( self.sessionstate == "playing" )
		self maps\mp\gametypes\_playerlogic::removeFromAliveCount( true );
	else if ( self.sessionstate == "spectator" )
		level thread maps\mp\gametypes\_gamelogic::updateGameEvents();
}


removePlayerOnDisconnect()
{
	found = false;
	for ( entry = 0; entry < level.players.size; entry++ )
	{
		if ( level.players[entry] == self )
		{
			found = true;
			while ( entry < level.players.size-1 )
			{
				level.players[entry] = level.players[entry + 1];
				assert( level.players[entry] != self );
				entry++;
			}
			level.players[entry] = undefined;
			break;
		}
	}
	assert( found );
}


initClientDvars()
{
	makeDvarServerInfo( "cg_drawTalk", 1 );
	makeDvarServerInfo( "cg_drawCrosshair", 1 );
	makeDvarServerInfo( "cg_drawCrosshairNames", 1 );
	makeDvarServerInfo( "cg_hudGrenadeIconMaxRangeFrag", 250 );

	if ( level.hardcoreMode )
	{
		setDvar( "cg_drawTalk", 3 );
		setDvar( "cg_drawCrosshair", 0 );
		setDvar( "cg_drawCrosshairNames", 1 );
		setDvar( "cg_hudGrenadeIconMaxRangeFrag", 0 );
	}

	self setClientDvars( "cg_drawSpectatorMessages", 1,
						 "g_compassShowEnemies", getDvar( "scr_game_forceuav" ),
						 "cg_scoreboardPingGraph", 1 );

	if ( level.splitScreen || self IsSplitscreenPlayer() )
	{
		self setClientDvars("cg_hudGrenadeIconHeight", "37.5", 
							"cg_hudGrenadeIconWidth", "37.5", 
							"cg_hudGrenadeIconOffset", "75", 
							"cg_hudGrenadePointerHeight", "18", 
							"cg_hudGrenadePointerWidth", "37.5", 
							"cg_hudGrenadePointerPivot", "18 40.5", 
							"cg_fovscale", "0.75" );
	}
	else
	{
		self setClientDvars("cg_hudGrenadeIconHeight", "25", 
							"cg_hudGrenadeIconWidth", "25", 
							"cg_hudGrenadeIconOffset", "50", 
							"cg_hudGrenadePointerHeight", "12", 
							"cg_hudGrenadePointerWidth", "25", 
							"cg_hudGrenadePointerPivot", "12 27", 
							"cg_fovscale", "1");
	}

	if ( getGametypeNumLives() )
	{
		self setClientDvars("cg_deadChatWithDead", 1,
							"cg_deadChatWithTeam", 0,
							"cg_deadHearTeamLiving", 0,
							"cg_deadHearAllLiving", 0);
	}
	else
	{
		self setClientDvars("cg_deadChatWithDead", 0,
							"cg_deadChatWithTeam", 1,
							"cg_deadHearTeamLiving", 1,
							"cg_deadHearAllLiving", 0);
	}
	
	if ( level.teamBased )
		self setClientDvars("cg_everyonehearseveryone", 0);
	
	self setClientDvar( "ui_altscene", 0 );

	if ( getdvarint("scr_hitloc_debug") )
	{
		for ( i = 0; i < 6; i++ )
		{
			self setClientDvar( "ui_hitloc_" + i, "" );
		}
		self.hitlocInited = true;
	}
}

getLowestAvailableClientId()
{
	found = false;
	
	for ( i = 0; i < 30; i++ )
	{
		foreach( player in level.players )
		{
			if( !isDefined( player ) )
				continue;
			
			if( player.clientId == i )
			{
				found = true;
				break; 
			}
			
			found = false;
		}
		
		if( !found )
		{
			return i;
		}
	}
	//would get here if nothing found (shouldnt be possible).
}

Callback_PlayerConnect()
{
	thread notifyConnecting();

	self.statusicon = "hud_status_connecting";
	self waittill( "begin" );
	self.statusicon = "";
	
	connectTime = undefined;
	/#
	connectTime = getTime();
	#/

	level notify( "connected", self );
	self.connected = true;

	if ( self isHost() )
		level.player = self;
	
	// only print that we connected if we haven't connected in a previous round
	if( !level.splitscreen && !isDefined( self.pers["score"] ) )
		iPrintLn(&"MP_CONNECTED", self);
	
	self.usingOnlineDataOffline = self isUsingOnlineDataOffline();

	self initClientDvars();
	self initPlayerStats();
	
	if( getdvar( "r_reflectionProbeGenerate" ) == "1" )
		level waittill( "eternity" );

	self.guid = self getGuid();

	firstConnect = false;
	if ( !isDefined( self.pers["clientid"] ) )
	{
		if ( game["clientid"] >= 30 )
		{
			self.pers["clientid"] = getLowestAvailableClientId();
		}
		else
		{
			self.pers["clientid"] = game["clientid"];
		}
		
		if ( game["clientid"] < 30 )
			game["clientid"]++;
		
		firstConnect = true;
	}

	// if first time connecting, reset killstreaks so they don't carry over after a disconnect
	if( firstConnect )
		self maps\mp\killstreaks\_killstreaks::resetAdrenaline();

	self.clientid = self.pers["clientid"];
	self.pers["teamKillPunish"] = false;

	logPrint("J;" + self.guid + ";" + self getEntityNumber() + ";" + self.name + "\n");

	if ( game["clientid"] <= 30 && game["clientid"] != getMatchData( "playerCount" ) )
	{
		connectionIDChunkHigh = 0;
		connectionIDChunkLow = 0;
		
		
		setMatchData( "playerCount", game["clientid"] );
		setMatchData( "players", self.clientid, "xuid", self getXuid() );
		setMatchData( "players", self.clientid, "gamertag", self.name );
		connectionIDChunkLow = self getplayerdata( "connectionIDChunkLow" );
		connectionIDChunkHigh = self getplayerdata( "connectionIDChunkHigh" );
		setMatchData( "players", self.clientid, "connectionIDChunkLow", connectionIDChunkLow );
		setMatchData( "players", self.clientid, "connectionIDChunkHigh", connectionIDChunkHigh );
		setmatchclientip( self, self.clientid );
		
		if( matchMakingGame() && allowTeamChoice() )
		{
			/#
			if ( ( getDvarInt( "scr_forcerankedmatch" ) && level.teamBased ) || ( isDefined( self.pers["isBot"] ) && level.teamBased ) )
				self.sessionteam = maps\mp\gametypes\_menus::getTeamAssignment();
			#/		
			assert( getdvarint( "scr_runlevelandquit" ) == 1 || (level.teamBased && (self.sessionteam == "allies" || self.sessionteam == "axis")) || (!level.teamBased && self.sessionteam == "none" ) );
			//assert( (level.teamBased && self.sessionteam == self.team) || (!level.teamBased && self.sessionteam == "none") );
			setMatchData( "players", self.clientid, "team", self.sessionteam );
		}
	}

	if ( !level.teamBased )
		game["roundsWon"][self.guid] = 0;
	
	self.leaderDialogQueue = [];
	self.leaderDialogActive = "";
	self.leaderDialogGroups = [];
	self.leaderDialogGroup = "";

	if( !IsDefined( self.pers["cur_kill_streak"] ) )
		self.pers["cur_kill_streak"] = 0;
	if( !IsDefined( self.pers["cur_death_streak"] ) )
		self.pers["cur_death_streak"] = 0;
	if( !IsDefined( self.pers["assistsToKill"] ) )
		self.pers["assistsToKill"] = 0;
	if( !IsDefined( self.pers["cur_kill_streak_for_nuke"] ) )
		self.pers["cur_kill_streak_for_nuke"] = 0;
	
	self.kill_streak = self maps\mp\gametypes\_persistence::statGet( "killStreak" );

	self.lastGrenadeSuicideTime = -1;

	self.teamkillsThisRound = 0;
	
	self.hasSpawned = false;
	self.waitingToSpawn = false;
	self.wantSafeSpawn = false;
	
	self.wasAliveAtMatchStart = false;
	self.moveSpeedScaler = 1;
	self.killStreakScaler = 1;
	self.xpScaler = 1;
	self.objectiveScaler = 1;
	self.isSniper = false;
	
	self.saved_actionSlotData = [];
	
	self setRestXPGoal();
	
	for( slotID = 1; slotID <= 4; slotID++ )
	{
		self.saved_actionSlotData[slotID] = spawnStruct();
		self.saved_actionSlotData[slotID].type = "";
		self.saved_actionSlotData[slotID].item = undefined;
	}
		
	self thread maps\mp\_flashgrenades::monitorFlash();
	
	// give any threads waiting on the "connected" notify a chance to process before we are added to level.players
	// this should ensure that all . variables on the player are correctly initialized by this point
	waittillframeend;
	/#
	foreach ( player in level.players )
		assert( player != self );
	#/
	level.players[level.players.size] = self;
	
	if ( level.teambased )
		self updateScores();
	
	// When joining a game in progress, if the game is at the post game state (scoreboard) the connecting player should spawn into intermission
	if ( game["state"] == "postgame" )
	{
		self.connectedPostGame = true;
		
		if ( matchMakingGame() )
			self maps\mp\gametypes\_menus::addToTeam( maps\mp\gametypes\_menus::getTeamAssignment(), true );
		else
			self maps\mp\gametypes\_menus::addToTeam( "spectator", true );
		
		self setClientDvars( "cg_drawSpectatorMessages", 0 );
		
		spawnIntermission();
		return;
	}

	/#
	if ( getDvarInt( "scr_debug_postgameconnect" ) )
	{
		self.pers["class"] = "";
		self.class = "";
		if ( self.sessionteam != "spectator" )
			self.pers["team"] = self.sessionteam;
		self.team = undefined;
	}
	#/

	// only give a loss on the first connect
	if ( firstConnect )
		maps\mp\gametypes\_gamelogic::updateLossStats( self );
	
	level endon( "game_ended" );
	
	if ( isDefined( level.hostMigrationTimer ) )
		self thread maps\mp\gametypes\_hostmigration::hostMigrationTimerThink();


	if ( isDefined( level.onPlayerConnectAudioInit ) )
	{
		[[ level.onPlayerConnectAudioInit ]]();
	}
	
	// first connect only
	if ( !isDefined( self.pers["team"] ) )
	{
		if ( matchMakingGame() )
		{
			self thread spawnSpectator();
			self [[level.autoassign]]();
			self thread kickIfDontSpawn();
			return;
		}
		else if ( allowTeamChoice() )
		{		
			self [[level.spectator]]();
			self maps\mp\gametypes\_menus::beginTeamChoice();
		}
		else
		{
			//self thread spawnSpectator();
			self [[level.spectator]]();
			self [[level.autoassign]]();
			return;			
		}
	}
	else
	{
		self maps\mp\gametypes\_menus::addToTeam( self.pers["team"], true );
		
		if ( isValidClass( self.pers["class"] ) )
		{
			self thread spawnClient();
			return;
		}

		self thread spawnSpectator();

		if ( self.pers["team"] == "spectator" )
		{
			if ( allowTeamChoice() )
				self maps\mp\gametypes\_menus::beginTeamChoice();
			else
				self [[level.autoassign]]();
		}
		else
			self maps\mp\gametypes\_menus::beginClassChoice();
	}

	/#	
	assert( connectTime == getTime() );
	#/
}


Callback_PlayerMigrated()
{
	println( "Player " + self.name + " finished migrating at time " + gettime() );
	
	if ( isDefined( self.connected ) && self.connected )
	{
		self updateObjectiveText();
		self updateMainMenu();

		if ( level.teambased )
			self updateScores();
	}
	
	level.hostMigrationReturnedPlayerCount++;
	if ( level.hostMigrationReturnedPlayerCount >= level.players.size * 2 / 3 )
	{
		println( "2/3 of players have finished migrating" );
		level notify( "hostmigration_enoughplayers" );
	}
}


AddLevelsToExperience( experience, levels ) // lets you add "1500 experience + 1.5 levels" and returns the result in experience
{
	rank = maps\mp\gametypes\_rank::getRankForXp( experience );
	
	minXP = maps\mp\gametypes\_rank::getRankInfoMinXp( rank );
	maxXP = maps\mp\gametypes\_rank::getRankInfoMaxXp( rank );
	rank += (experience - minXP) / (maxXP - minXP);
	
	rank += levels;
	
	if ( rank < 0 )
	{
		rank = 0;
		fractionalPart = 0.0;
	}
	else if ( rank >= level.maxRank + 1.0 )
	{
		rank = level.maxRank;
		fractionalPart = 1.0;
	}
	else
	{
		fractionalPart = rank - floor( rank );
		rank = int(floor( rank ));
	}
	
	minXP = maps\mp\gametypes\_rank::getRankInfoMinXp( rank );
	maxXP = maps\mp\gametypes\_rank::getRankInfoMaxXp( rank );
	return int( fractionalPart * (maxXP - minXP) ) + minXP;
}


GetRestXPCap( experience )
{
	levelsToCap = getDvarFloat( "scr_restxp_cap" );
	return AddLevelsToExperience( experience, levelsToCap );
}


setRestXPGoal()
{
	if ( !getdvarint( "scr_restxp_enable" ) )
	{
		self setPlayerData( "restXPGoal", 0 );
		return;
	}
	
	secondsSinceLastGame = self getRestedTime();
	hoursSinceLastGame = secondsSinceLastGame / 3600;
	
	/#
	hoursSinceLastGame *= getDvarFloat( "scr_restxp_timescale" );
	#/
	
	experience = self getPlayerData( "experience" );
	
	minRestXPTime = getDvarFloat( "scr_restxp_minRestTime" ); // hours
	restXPGainRate = getDvarFloat( "scr_restxp_levelsPerDay" ) / 24.0;
	restXPCap = GetRestXPCap( experience );
	
	restXPGoal = self getPlayerData( "restXPGoal" );
	
	if ( restXPGoal < experience )
		restXPGoal = experience;
	
	oldRestXPGoal = restXPGoal;
	
	restLevels = 0;
	if ( hoursSinceLastGame > minRestXPTime )
	{
		restLevels = restXPGainRate * hoursSinceLastGame;
		restXPGoal = AddLevelsToExperience( restXPGoal, restLevels );
	}
	
	cappedString = "";
	if ( restXPGoal >= restXPCap )
	{
		restXPGoal = restXPCap;
		cappedString = " (hit cap)";
	}
	
	println( "Player " + self.name + " has rested for " + hoursSinceLastGame + " hours; gained " + restLevels + " levels of rest XP" + cappedString + ". Now has " + (restXPGoal - experience) + " rest XP; was " + (oldRestXPGoal - experience) );
	
	self setPlayerData( "restXPGoal", restXPGoal );
}


forceSpawn()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( "spawned" );

	wait ( 60.0 );

	if ( self.hasSpawned )
		return;
	
	if ( self.pers["team"] == "spectator" )
		return;
	
	if ( !isValidClass( self.pers["class"] ) )
	{
		self.pers["class"] = "CLASS_CUSTOM1";
		
		self.class = self.pers["class"];
	}
	
	self closeMenus();
	self thread spawnClient();
}


kickIfDontSpawn()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( "spawned" );
	self endon ( "attempted_spawn" );
	
	waittime = getdvarfloat("scr_kick_time", 90 );
	mintime = getdvarfloat("scr_kick_mintime", 45 );
	
	starttime = gettime();
	
	if ( self isHost() )
		kickWait( 120 );
	else
		kickWait( waittime );
	
	timePassed = (gettime() - starttime)/1000;
	if ( timePassed < waittime - .1 && timePassed < mintime )
		return;
	
	if ( self.hasSpawned )
		return;
	
	if ( self.pers["team"] == "spectator" )
		return;
	
	kick( self getEntityNumber(), "EXE_PLAYERKICKED_INACTIVE" );

	level thread maps\mp\gametypes\_gamelogic::updateGameEvents();
}


kickWait( waittime )
{
	level endon("game_ended");

	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( waittime );
}


updateSessionState( sessionState, statusIcon )
{
	assert( sessionState == "playing" || sessionState == "dead" || sessionState == "spectator" || sessionState == "intermission" );
	self.sessionstate = sessionState;
	self.statusicon = statusIcon;
}


initPlayerStats()
{
	self maps\mp\gametypes\_persistence::initBufferedStats();
	
	self.pers["lives"] = getGametypeNumLives();

	if ( !isDefined( self.pers["deaths"] ) )
		self initPersStat( "deaths" );
	self.deaths = self getPersStat( "deaths" );
	
	if ( !isDefined( self.pers["score"] ) )
		self initPersStat( "score" );
	self.score = self getPersStat( "score" );

	if ( !isDefined( self.pers["suicides"] ) )
		self initPersStat( "suicides" );
	self.suicides = self getPersStat( "suicides" );

	if ( !isDefined( self.pers["kills"] ) )
		self initPersStat( "kills" );
	self.kills = self getPersStat( "kills" );

	if ( !isDefined( self.pers["headshots"] ) )
		self initPersStat( "headshots" );
	self.headshots = self getPersStat( "headshots" );

	if ( !isDefined( self.pers["assists"] ) )
		self initPersStat( "assists" );
	self.assists = self getPersStat( "assists" );
	
	if ( !isDefined( self.pers["captures"] ) )
		self initPersStat( "captures" );
	self.captures = self getPersStat( "captures" );
	
	if ( !isDefined( self.pers["returns"] ) )
		self initPersStat( "returns" );
	self.returns = self getPersStat( "returns" );
	
	if ( !isDefined( self.pers["defends"] ) )
		self initPersStat( "defends" );
	self.defends = self getPersStat( "defends" );

	if ( !isDefined( self.pers["plants"] ) )
		self initPersStat( "plants" );
	self.plants = self getPersStat( "plants" );

	if ( !isDefined( self.pers["defuses"] ) )
		self initPersStat( "defuses" );
	self.defuses = self getPersStat( "defuses" );

	if ( !isDefined( self.pers["destructions"] ) )
		self initPersStat( "destructions" );
	self.destructions = self getPersStat( "destructions" );
	
	if ( !isDefined( self.pers["confirmed"] ) )
		self initPersStat( "confirmed" );
	self.confirmed = self getPersStat( "confirmed" );
	
	if ( !isDefined( self.pers["denied"] ) )
		self initPersStat( "denied" );
	self.denied = self getPersStat( "denied" );
	
	if ( !isDefined( self.pers["teamkills"] ) )
		self initPersStat( "teamkills" );

	if ( !isDefined( self.pers["teamKillPunish"] ) )
		self.pers["teamKillPunish"] = false;
	
	self initPersStat( "longestStreak" );	

	self.pers["lives"] = getGametypeNumLives();
	
	self maps\mp\gametypes\_persistence::statSetChild( "round", "kills", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "killStreak", 0 );
	//self maps\mp\gametypes\_persistence::statSetChild( "round", "deaths", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "score", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "loss", false );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "win", false );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "scoreboardType", "none" );
	self maps\mp\gametypes\_persistence::statSetChildBuffered( "round", "timePlayed", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "kills", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "killStreak", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "score", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "loss", false );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "win", false );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "scoreboardType", "none" );
	self maps\mp\gametypes\_persistence::statSetChildBuffered( "round", "timePlayed", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "captures", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "returns", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "defends", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "plants", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "defuses", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "destructions", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "confirmed", 0 );
	self maps\mp\gametypes\_persistence::statSetChild( "round", "denied", 0 );
}


addToTeamCount()
{
	assert( isPlayer( self ) );
	assert( isDefined( self.team ) );
	assert( isDefined( self.pers["team"] ) );
	assert( self.team == self.pers["team"] );
	
	level.teamCount[self.team]++;
	maps\mp\gametypes\_gamelogic::updateGameEvents();
}


removeFromTeamCount()
{
	assert( isPlayer( self ) );
	assert( isDefined( self.team ) );
	assert( isDefined( self.pers["team"] ) );
	assert( self.team == self.pers["team"] );
	
	level.teamCount[self.team]--;
}


addToAliveCount()
{
	assert( isPlayer( self ) );
	level.aliveCount[self.team]++;
	level.hasSpawned[self.team]++;

	if ( level.aliveCount["allies"] + level.aliveCount["axis"] > level.maxPlayerCount )
		level.maxPlayerCount = level.aliveCount["allies"] + level.aliveCount["axis"];
}


removeFromAliveCount( disconnected )
{
	assert( isPlayer( self ) );

	if ( isDefined( self.switching_teams ) || isDefined( disconnected ) )
	{
		self maps\mp\gametypes\_playerlogic::removeAllFromLivesCount();

		if ( isDefined( self.switching_teams ) )
			self.pers["lives"] = 0;
	}

	level.aliveCount[self.team]--;
	return maps\mp\gametypes\_gamelogic::updateGameEvents();
}


addToLivesCount()
{
	assert( isPlayer( self ) );
	level.livesCount[self.team] += self.pers["lives"];
}


removeFromLivesCount()
{
	assert( isPlayer( self ) );
	level.livesCount[self.team]--;

	// defensive, but we need to allow players to die/respawn when they're the only player in an offline game
	level.livesCount[self.team] = int( max( 0, level.livesCount[self.team] ) );
}


removeAllFromLivesCount()
{
	assert( isPlayer( self ) );
	level.livesCount[self.team] -= self.pers["lives"];

	// defensive, but we need to allow players to die/respawn when they're the only player in an offline game
	level.livesCount[self.team] = int( max( 0, level.livesCount[self.team] ) );
}

