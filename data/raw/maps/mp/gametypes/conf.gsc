#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;
/*
	Confirmed Kill
	Objective: 	Score points for your team by eliminating players on the opposing team.
				Score bonus points for picking up dogtags from downed enemies.
	Map ends:	When one team reaches the score limit, or time limit is reached
	Respawning:	No wait / Near teammates

	Level requirementss
	------------------
		Spawnpoints:
			classname		mp_tdm_spawn
			All players spawn from these. The spawnpoint chosen is dependent on the current locations of teammates and enemies
			at the time of spawn. Players generally spawn behind their teammates relative to the direction of enemies.

		Spectator Spawnpoints:
			classname		mp_global_intermission
			Spectators spawn from these and intermission is viewed from these positions.
			Atleast one is required, any more and they are randomly chosen between.
*/


main()
{
	if(getdvar("mapname") == "mp_background")
		return;
	
	maps\mp\gametypes\_globallogic::init();
	maps\mp\gametypes\_callbacksetup::SetupCallbacks();
	maps\mp\gametypes\_globallogic::SetupCallbacks();

	if ( isUsingMatchRulesData() )
	{
		level.initializeMatchRules = ::initializeMatchRules;
		[[level.initializeMatchRules]]();
		level thread reInitializeMatchRulesOnMigration();			
	}
	else
	{
		registerRoundSwitchDvar( level.gameType, 0, 0, 9 );
		registerTimeLimitDvar( level.gameType, 10 );
		registerScoreLimitDvar( level.gameType, 65 );
		registerRoundLimitDvar( level.gameType, 1 );
		registerWinLimitDvar( level.gameType, 1 );
		registerNumLivesDvar( level.gameType, 0 );
		registerHalfTimeDvar( level.gameType, 0 );
		
		level.matchRules_damageMultiplier = 0;
		level.matchRules_vampirism = 0;	
	}

	level.teamBased = true;
	level.initGametypeAwards = ::initGametypeAwards;
	level.onStartGameType = ::onStartGameType;
	level.getSpawnPoint = ::getSpawnPoint;
	level.onNormalDeath = ::onNormalDeath;
	level.onPrecacheGameType = ::onPrecacheGameType;
	
	if ( level.matchRules_damageMultiplier || level.matchRules_vampirism )
		level.modifyPlayerDamage = maps\mp\gametypes\_damage::gamemodeModifyPlayerDamage;

	game["dialog"]["gametype"] = "kill_confirmed";
	
	level.conf_vo["axis"] = "RU_1mc_kill_confirmed";	
	level.conf_vo["allies"] = "US_1mc_kill_confirmed";
	
	level.conf_fx["vanish"] = loadFx( "impacts/small_snowhit" );
}


initializeMatchRules()
{
	//	set common values
	setCommonRulesFromMatchRulesData();
	
	//	set everything else (private match options, default .cfg file values, and what normally is registered in the 'else' below)
	SetDynamicDvar( "scr_conf_roundswitch", 0 );
	registerRoundSwitchDvar( "conf", 0, 0, 9 );
	SetDynamicDvar( "scr_conf_roundlimit", 1 );
	registerRoundLimitDvar( "conf", 1 );		
	SetDynamicDvar( "scr_conf_winlimit", 1 );
	registerWinLimitDvar( "conf", 1 );			
	SetDynamicDvar( "scr_conf_halftime", 0 );
	registerHalfTimeDvar( "conf", 0 );
		
	SetDynamicDvar( "scr_conf_promode", 0 );	
}


onPrecacheGameType()
{
	precachemodel( "prop_dogtags_friend" );
	precachemodel( "prop_dogtags_foe" );
	precacheshader( "waypoint_dogtags" );
}


onStartGameType()
{
	setClientNameMode("auto_change");

	if ( !isdefined( game["switchedsides"] ) )
		game["switchedsides"] = false;

	if ( game["switchedsides"] )
	{
		oldAttackers = game["attackers"];
		oldDefenders = game["defenders"];
		game["attackers"] = oldDefenders;
		game["defenders"] = oldAttackers;
	}

	setObjectiveText( "allies", &"OBJECTIVES_CONF" );
	setObjectiveText( "axis", &"OBJECTIVES_CONF" );
	
	if ( level.splitscreen )
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_CONF" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_CONF" );
	}
	else
	{
		setObjectiveScoreText( "allies", &"OBJECTIVES_CONF_SCORE" );
		setObjectiveScoreText( "axis", &"OBJECTIVES_CONF_SCORE" );
	}
	setObjectiveHintText( "allies", &"OBJECTIVES_CONF_HINT" );
	setObjectiveHintText( "axis", &"OBJECTIVES_CONF_HINT" );
			
	level.spawnMins = ( 0, 0, 0 );
	level.spawnMaxs = ( 0, 0, 0 );	
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_tdm_spawn_allies_start" );
	maps\mp\gametypes\_spawnlogic::placeSpawnPoints( "mp_tdm_spawn_axis_start" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "allies", "mp_tdm_spawn" );
	maps\mp\gametypes\_spawnlogic::addSpawnPoints( "axis", "mp_tdm_spawn" );
	
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );	
	
	maps\mp\gametypes\_rank::registerScoreInfo( "kill", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "kill_confirmed", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "kill_denied", 50 );
	maps\mp\gametypes\_rank::registerScoreInfo( "tags_retrieved", 250 );
	
	level.dogtags = [];
	
	allowed[0] = level.gameType;
	
	maps\mp\gametypes\_gameobjects::main(allowed);	
}


getSpawnPoint()
{
	spawnteam = self.pers["team"];
	if ( game["switchedsides"] )
		spawnteam = getOtherTeam( spawnteam );

	if ( level.inGracePeriod )
	{
		spawnPoints = maps\mp\gametypes\_spawnlogic::getSpawnpointArray( "mp_tdm_spawn_" + spawnteam + "_start" );
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_Random( spawnPoints );
	}
	else
	{
		spawnPoints = maps\mp\gametypes\_spawnlogic::getTeamSpawnPoints( spawnteam );
		spawnPoint = maps\mp\gametypes\_spawnlogic::getSpawnpoint_NearTeam( spawnPoints );
	}
	
	return spawnPoint;
}


onNormalDeath( victim, attacker, lifeId )
{
	//score = maps\mp\gametypes\_rank::getScoreInfoValue( "kill" );
	//assert( isDefined( score ) );

	level thread spawnDogTags( victim, attacker );

	//attacker maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( attacker.pers["team"], score );
	
	if ( game["state"] == "postgame" && game["teamScores"][attacker.team] > game["teamScores"][level.otherTeam[attacker.team]] )
		attacker.finalKill = true;
}


spawnDogTags( victim, attacker )
{
	if ( isDefined( level.dogtags[victim.guid] ) )
	{
		PlayFx( level.conf_fx["vanish"], level.dogtags[victim.guid].curOrigin );
		level.dogtags[victim.guid] notify( "reset" );
		
		//if ( isDefined( level.dogtags[victim.guid].attacker ) /*&& level.dogtags[victim.guid].attacker != attacker*/ && isAlive( level.dogtags[victim.guid].attacker ) )
			//level.dogtags[victim.guid].attacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_UNCONFIRMED_KILL" );		
	}
	else
	{
		visuals[0] = spawn( "script_model", (0,0,0) );
		visuals[0] setModel( "prop_dogtags_foe" );
		visuals[1] = spawn( "script_model", (0,0,0) );
		visuals[1] setModel( "prop_dogtags_friend" );
		
		trigger = spawn( "trigger_radius", (0,0,0), 0, 32, 32 );
		
		level.dogtags[victim.guid] = maps\mp\gametypes\_gameobjects::createUseObject( "any", trigger, visuals, (0,0,16) );
		
		//	we don't need these
		_objective_delete( level.dogtags[victim.guid].objIDAllies );
		_objective_delete( level.dogtags[victim.guid].objIDAxis );		
		maps\mp\gametypes\_objpoints::deleteObjPoint( level.dogtags[victim.guid].objPoints["allies"] );
		maps\mp\gametypes\_objpoints::deleteObjPoint( level.dogtags[victim.guid].objPoints["axis"] );		
		
		level.dogtags[victim.guid] maps\mp\gametypes\_gameobjects::setUseTime( 0 );
		level.dogtags[victim.guid].onUse = ::onUse;
		level.dogtags[victim.guid].victim = victim;
		level.dogtags[victim.guid].victimTeam = victim.pers["team"];
		
		level.dogtags[victim.guid].objId = maps\mp\gametypes\_gameobjects::getNextObjID();	
		objective_add( level.dogtags[victim.guid].objId, "invisible", (0,0,0) );
		objective_icon( level.dogtags[victim.guid].objId, "waypoint_dogtags" );	
		
		level thread clearOnVictimDisconnect( victim );
	}	
	
	pos = victim.origin + (0,0,14);
	level.dogtags[victim.guid].curOrigin = pos;
	level.dogtags[victim.guid].trigger.origin = pos;
	level.dogtags[victim.guid].visuals[0].origin = pos;
	level.dogtags[victim.guid].visuals[1].origin = pos;
	
	level.dogtags[victim.guid] maps\mp\gametypes\_gameobjects::allowUse( "any" );	
			
	level.dogtags[victim.guid].visuals[0] thread showToTeam( level.dogtags[victim.guid], getOtherTeam( victim.pers["team"] ) );
	level.dogtags[victim.guid].visuals[1] thread showToTeam( level.dogtags[victim.guid], victim.pers["team"] );
	
	level.dogtags[victim.guid].attacker = attacker;
	//level.dogtags[victim.guid] thread timeOut( victim );
	
	objective_position( level.dogtags[victim.guid].objId, pos );
	objective_state( level.dogtags[victim.guid].objId, "active" );
	objective_player( level.dogtags[victim.guid].objId, attacker getEntityNumber() );		
	
	playSoundAtPos( pos, "mp_killconfirm_tags_drop" );
	
	level.dogtags[victim.guid] thread bounce();
}


showToTeam( gameObject, team )
{
	gameObject endon ( "death" );
	gameObject endon( "reset" );

	self hide();

	foreach ( player in level.players )
	{
		if( player.team == team )
			self ShowToPlayer( player );
	}

	for ( ;; )
	{
		level waittill ( "joined_team" );
		
		self hide();
		foreach ( player in level.players )
		{
			if ( player.team == team )
				self ShowToPlayer( player );
				
			if ( gameObject.victimTeam == player.team && player == gameObject.attacker )
				objective_state( gameObject.objId, "invisible" );
		}
	}	
}


onUse( player )
{
	pos = self.curOrigin;
	
	self notify( "reset" );
	self.visuals[0] hide();
	self.visuals[1] hide();
	self.curOrigin = (0,0,1000);
	self.trigger.origin = (0,0,1000);
	self.visuals[0].origin = (0,0,1000);
	self.visuals[1].origin = (0,0,1000);
	self maps\mp\gametypes\_gameobjects::allowUse( "none" );	
	objective_state( self.objId, "invisible" );		 
	
	//	friendly pickup
	if ( player.pers["team"] == self.victimTeam )
	{
		self.trigger playSound( "mp_killconfirm_tags_deny" );
		
		player incPlayerStat( "killsdenied", 1 );
		player incPersStat( "denied", 1 );
		player maps\mp\gametypes\_persistence::statSetChild( "round", "denied", player.pers["denied"] );
			
		if ( self.victim == player )
		{
			event = "tags_retrieved";
			splash = &"SPLASHES_TAGS_RETRIEVED";
		}
		else
		{
			event = "kill_denied";
			splash = &"SPLASHES_KILL_DENIED";	
		}
		
		//	tell the attacker their kill was denied
		if ( isDefined( self.attacker ) )
			self.attacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DENIED_KILL", (1,0.5,0.5) );
	}
	//	enemy pickup
	else
	{
		self.trigger playSound( "mp_killconfirm_tags_pickup" );
		
		event = "kill_confirmed";
		splash = &"SPLASHES_KILL_CONFIRMED";
		
		player incPlayerStat( "killsconfirmed", 1 );
		player incPersStat( "confirmed", 1 );
		player maps\mp\gametypes\_persistence::statSetChild( "round", "confirmed", player.pers["confirmed"] );
		
		//	if not us, tell the attacker their kill was confirmed
		if ( self.attacker != player )
			self.attacker onPickup( event, splash );
		
		player playLocalSound( game["voice"][player.pers["team"]] + "kill_confirmed" );
		
		player maps\mp\gametypes\_gamescore::giveTeamScoreForObjective( player.pers["team"], 1 );			
	}	
		
	player onPickup( event, splash );
	
	self.attacker = undefined;
}


onPickup( event, splash, stat )
{
	self thread maps\mp\gametypes\_rank::xpEventPopup( splash );
	maps\mp\gametypes\_gamescore::givePlayerScore( event, self, undefined, true );
	self thread maps\mp\gametypes\_rank::giveRankXP( event );
	
	//self notify( "objective", event );
	//self incPlayerStat( stat, 1 );
	//self thread maps\mp\_matchdata::logGameEvent( event, self.origin );	
}


bounce()
{
	level endon( "game_ended" );
	self endon( "reset" );	
	
	bottomPos = self.curOrigin;
	topPos = self.curOrigin + (0,0,12);
	
	while( true )
	{
		self.visuals[0] moveTo( topPos, 0.5, 0.15, 0.15 );
		self.visuals[0] rotateYaw( 180, 0.5 );
		self.visuals[1] moveTo( topPos, 0.5, 0.15, 0.15 );
		self.visuals[1] rotateYaw( 180, 0.5 );
		
		wait( 0.5 );
		
		self.visuals[0] moveTo( bottomPos, 0.5, 0.15, 0.15 );
		self.visuals[0] rotateYaw( 180, 0.5 );	
		self.visuals[1] moveTo( bottomPos, 0.5, 0.15, 0.15 );
		self.visuals[1] rotateYaw( 180, 0.5 );
		
		wait( 0.5 );		
	}
}


timeOut( victim )
{
	level  endon( "game_ended" );
	victim endon( "disconnect" );
	self notify( "timeout" );
	self endon( "timeout" );
	
	level maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 30.0 );
	//wait( 30 );
	
	self.visuals[0] hide();
	self.visuals[1] hide();
	self.curOrigin = (0,0,1000);
	self.trigger.origin = (0,0,1000);
	self.visuals[0].origin = (0,0,1000);
	self.visuals[1].origin = (0,0,1000);
	self maps\mp\gametypes\_gameobjects::allowUse( "none" );			
}


clearOnVictimDisconnect( victim )
{
	level endon( "game_ended" );	
	
	guid = victim.guid;
	victim waittill( "disconnect" );
	
	if ( isDefined( level.dogtags[guid] ) )
	{
		//	block further use
		level.dogtags[guid] maps\mp\gametypes\_gameobjects::allowUse( "none" );
		
		//	tell the attacker their kill was denied
		if ( isDefined( level.dogtags[guid].attacker ) )
			level.dogtags[guid].attacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DENIED_KILL", (1,0.5,0.5) );		
		
		//	play vanish effect, reset, and wait for reset to process
		PlayFx( level.conf_fx["vanish"], level.dogtags[guid].curOrigin );
		level.dogtags[guid] notify( "reset" );		
		wait( 0.05 );
		
		//	sanity check before removal
		if ( isDefined( level.dogtags[guid] ) )
		{
			//	delete objective and visuals
			objective_delete( level.dogtags[guid].objId );
			level.dogtags[guid].trigger delete();
			for ( i=0; i<level.dogtags[guid].visuals.size; i++ )
				level.dogtags[guid].visuals[i] delete();
			level.dogtags[guid] notify ( "deleted" );
			
			//	remove from list
			level.dogtags[guid] = undefined;		
		}	
	}	
}


initGametypeAwards()
{
	//maps\mp\_awards::initStatAward( "killsconfirmed",		0, maps\mp\_awards::highestWins );
}