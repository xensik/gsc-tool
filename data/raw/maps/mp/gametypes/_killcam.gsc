#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;

init()
{
	precacheString(&"PLATFORM_PRESS_TO_SKIP");
	precacheString(&"PLATFORM_PRESS_TO_RESPAWN");
	precacheString(&"PLATFORM_PRESS_TO_COPYCAT");
	//precacheShader("specialty_copycat");
	
	level.killcam = maps\mp\gametypes\_tweakables::getTweakableValue( "game", "allowkillcam" );
}

killcam(
	attackerNum, // entity number of the attacker
	killcamentityindex, // entity number of the entity to view (grenade, airstrike, etc)
	killcamentitystarttime, // time at which the killcamentity came into being
	sWeapon, // killing weapon
	predelay, // time between player death and beginning of killcam
	offsetTime, // something to do with how far back in time the killer was seeing the world when he made the kill; latency related, sorta
	timeUntilRespawn, // will the player be allowed to respawn after the killcam?
	maxtime, // time remaining until map ends; the killcam will never last longer than this. undefined = no limit
	attacker, // entity object of attacker
	victim // entity object of the victim
)
{
	// monitors killcam and hides HUD elements during killcam session
	//if ( !level.splitscreen )
	//	self thread killcam_HUD_off();
	
	self endon("disconnect");
	self endon("spawned");
	level endon("game_ended");
	
	if ( attackerNum < 0 )
		return;

	// length from killcam start to killcam end
	if (getdvar("scr_killcam_time") == "") {
		if ( sWeapon == "artillery_mp" || sWeapon == "stealth_bomb_mp" || sWeapon == "remote_mortar_missile_mp" )
			camtime = (gettime() - killcamentitystarttime) / 1000 - predelay - .1;
		else if ( level.showingFinalKillcam	)
			camtime = 4.0;
		else if ( sWeapon == "apache_minigun_mp" )
			camtime = 3.0;
		else if ( sWeapon == "javelin_mp" || sWeapon == "uav_strike_projectile_mp" )
			camtime = 8;
		else if ( issubstr( sWeapon, "remotemissile_" ) )
			camtime = 5;
		else if ( !timeUntilRespawn || timeUntilRespawn > 5.0 ) // if we're not going to respawn, we can take more time to watch what happened
			camtime = 5.0;
		else if ( sWeapon == "frag_grenade_mp" || sWeapon == "frag_grenade_short_mp" || sWeapon == "semtex_mp" )
			camtime = 4.25; // show long enough to see grenade thrown
		else
			camtime = 2.5;
	}
	else
		camtime = getdvarfloat("scr_killcam_time");

	if (isdefined(maxtime)) {
		if (camtime > maxtime)
			camtime = maxtime;
		if (camtime < .066)
			camtime = .066;
	}
	
	// time after player death that killcam continues for
	if (getdvar("scr_killcam_posttime") == "")
		postdelay = 2;
	else {
		postdelay = getdvarfloat("scr_killcam_posttime");
		if (postdelay < 0.066)
			postdelay = 0.066;
	}
	
	/* timeline:
	
	|        camtime       |      postdelay      |
	|                      |   predelay    |
	
	^ killcam start        ^ player death        ^ killcam end
	                                       ^ player starts watching killcam
	
	*/
	
	killcamlength = camtime + postdelay;
	
	// don't let the killcam last past the end of the round.
	if (isdefined(maxtime) && killcamlength > maxtime)
	{
		// first trim postdelay down to a minimum of 1 second.
		// if that doesn't make it short enough, trim camtime down to a minimum of 1 second.
		// if that's still not short enough, cancel the killcam.
		if ( maxtime < 2 )
			return;

		if (maxtime - camtime >= 1) {
			// reduce postdelay so killcam ends at end of match
			postdelay = maxtime - camtime;
		}
		else {
			// distribute remaining time over postdelay and camtime
			postdelay = 1;
			camtime = maxtime - 1;
		}
		
		// recalc killcamlength
		killcamlength = camtime + postdelay;
	}

	killcamoffset = camtime + predelay;
	
	startTime = getTime();
	self notify ( "begin_killcam", startTime );

	if ( isDefined( attacker ) ) // attacker may have disconnected
		attacker visionsyncwithplayer( victim );
	
	self.sessionstate = "spectator";
	self.forcespectatorclient = attackerNum;
	self.killcamentity = -1;
	if ( killcamentityindex >= 0 )
		self thread setKillCamEntity( killcamentityindex, killcamoffset, killcamentitystarttime );
	self.archivetime = killcamoffset;
	self.killcamlength = killcamlength;
	self.psoffsettime = offsetTime;
	
	// ignore spectate permissions
	self allowSpectateTeam("allies", true);
	self allowSpectateTeam("axis", true);
	self allowSpectateTeam("freelook", true);
	self allowSpectateTeam("none", true);

	if ( isDefined( attacker ) && level.showingFinalKillcam ) // attacker may have disconnected
	{
		self openMenu( "killedby_card_display" );
		self SetCardDisplaySlot( attacker, 7 );
	}
	
	self thread endedKillcamCleanup();

	// wait till the next server frame to allow code a chance to update archivetime if it needs trimming
	wait 0.05;	
	
	assertex( self.archivetime <= killcamoffset + 0.0001, "archivetime: " + self.archivetime + ", killcamoffset: " + killcamoffset );
	if ( self.archivetime < killcamoffset )
		println( "WARNING: Code trimmed killcam time by " + (killcamoffset - self.archivetime) + " seconds because it doesn't have enough game time recorded!" );
	
	camtime = self.archivetime - .066 - predelay;
	killcamlength = camtime + postdelay;
	self.killcamlength = killcamlength;
	
	if ( camtime <= 0 ) // if we're not looking back in time far enough to even see the death, cancel
	{
		println( "Cancelling killcam because we don't even have enough recorded to show the death." );
		
		self.sessionstate = "dead";
		self.forcespectatorclient = -1;
		self.killcamentity = -1;
		self.archivetime = 0;
		self.psoffsettime = 0;
		
		self notify ( "killcam_ended" );
		
		return;
	}
	
	//*if ( level.showingFinalKillcam )
	//*	thread doFinalKillCamFX( camtime );
	
	self.killcam = true;

	self initKCElements();

	if ( !level.splitscreen )
	{	
		self.kc_timer.alpha = 1;
		self.kc_timer setTenthsTimer(camtime);
	}

	if ( timeUntilRespawn && !level.gameEnded )
	{
		// I'm not sure why this if check was here, if we're in the killcam we should always show the skip text, even if they are waiting to respawn
		//if ( timeUntilRespawn > 0 )
		//	setLowerMessage( "kc_info", game["strings"]["waiting_to_spawn"] );
		//else
			setLowerMessage( "kc_info", &"PLATFORM_PRESS_TO_SKIP", undefined, undefined, undefined, undefined, undefined, undefined, true );
	}
	else if ( !level.gameEnded )
	{
		setLowerMessage( "kc_info", &"PLATFORM_PRESS_TO_RESPAWN", undefined, undefined, undefined, undefined, undefined, undefined, true );
	}
	
	if ( !level.showingFinalKillcam )
		self.kc_skiptext.alpha = 1;
	else
		self.kc_skiptext.alpha = 0;

	self.kc_othertext.alpha = 0;
	self.kc_icon.alpha = 0;

	self thread spawnedKillcamCleanup();

	if ( self == victim && victim _hasPerk( "specialty_copycat" ) && isDefined( victim.pers["copyCatLoadout"] ) && ( !attacker isJuggernaut() ) )
		self thread waitKCCopyCatButton( attacker );

	if ( !level.showingFinalKillcam )
		self thread waitSkipKillcamButton( timeUntilRespawn );
	else
		self notify ( "showing_final_killcam" );
	
	self thread endKillcamIfNothingToShow();
	
	self waittillKillcamOver();
	
	if ( level.showingFinalKillcam )
	{
		self thread maps\mp\gametypes\_playerlogic::spawnEndOfGame();
		return;
	}
	
	self thread calculateKillCamTime( startTime );
	
	self thread killcamCleanup( true );
}


doFinalKillCamFX( camTime )
{
	if ( isDefined( level.doingFinalKillcamFx ) )
		return;
	level.doingFinalKillcamFx = true;
	
	intoSlowMoTime = camTime;
	if ( intoSlowMoTime > 1.0 )
	{
		intoSlowMoTime = 1.0;
		wait( camTime - 1.0 );
	}
	
	setSlowMotion( 1.0, 0.25, intoSlowMoTime ); // start timescale, end timescale, lerp duration
	wait( intoSlowMoTime + .5 );
	setSlowMotion( 0.25, 1, 1.0 );
	
	level.doingFinalKillcamFx = undefined;
}


calculateKillCamTime( startTime )
{
	watchedTime = int(getTime() - startTime);
	//*self incPlayerStat( "killcamtimewatched", watchedTime );
}

waittillKillcamOver()
{
	self endon("abort_killcam");
	
	wait(self.killcamlength - 0.066);
}

setKillCamEntity( killcamentityindex, killcamoffset, starttime )
{
	self endon("disconnect");
	self endon("killcam_ended");
	
	killcamtime = (gettime() - killcamoffset * 1000);
	
	if ( starttime > killcamtime )
	{
		wait .05;
		// code may have trimmed archivetime after the first frame if we couldn't go back in time as far as requested.
		killcamoffset = self.archivetime;
		killcamtime = (gettime() - killcamoffset * 1000);
		
		if ( starttime > killcamtime )
			wait (starttime - killcamtime) / 1000;
	}
	self.killcamentity = killcamentityindex;
}

waitSkipKillcamButton( timeUntilRespawn )
{
	self endon("disconnect");
	self endon("killcam_ended");

	while(self useButtonPressed())
		wait .05;

	while(!(self useButtonPressed()))
		wait .05;
		
	//*if ( !matchMakingGame() )
	//*	self incPlayerStat( "killcamskipped", 1 );

	if ( timeUntilRespawn <= 0 )
		clearLowerMessage( "kc_info" );
	
	self notify("abort_killcam");
}

waitKCCopyCatButton( attacker )
{
	self endon("disconnect");
	self endon("killcam_ended");

	self waitCopyCatButton( attacker );

	self notify("abort_killcam");
}

waitDeathCopyCatButton( attacker )
{
	self endon ( "disconnect" );

	self initKCElements();
	
	usedCopycat = self waitCopyCatButton( attacker );

	if ( !isDefined( usedCopycat ) )
	{
		self.kc_icon.alpha = 0;
		self.kc_othertext.alpha = 0;
	}
}

waitCopyCatButton( attacker )
{
	self endon ( "spawned_player" );
	self endon ( "death_delay_finished" );
	self.kc_icon setShader( "specialty_copycat", 48, 48 );
	self.kc_othertext setText( &"PLATFORM_PRESS_TO_COPYCAT" );
	self.kc_othertext.alpha = 1;
	self.kc_icon.alpha = 1;
	
	self notifyOnPlayerCommand( "use_copycat", "weapnext" );
	
	self waittill( "use_copycat" );
	
	self.pers["copyCatLoadout"]["inUse"] = true;
	self.pers["copyCatLoadout"]["owner"] = attacker;

	self.kc_othertext fadeOverTime( 0.5 );
	self.kc_othertext.alpha = 0;

	self.kc_icon fadeOverTime( 0.25 );
	self.kc_icon scaleOverTime( 0.25, 512, 512 );
	self.kc_icon.alpha = 0;
	
	if ( isDefined( attacker ) )
		attacker thread maps\mp\gametypes\_hud_message::playerCardSplashNotify( "copied", self );

	self playLocalSound( "copycat_steal_class" );
		
	return true;
}

waitSkipKillcamSafeSpawnButton()
{
	self endon("disconnect");
	self endon("killcam_ended");
	
	if ( !self maps\mp\gametypes\_playerlogic::maySpawn() )
		return;
	
	while(self fragButtonPressed())
		wait .05;

	while(!(self fragButtonPressed()))
		wait .05;
	
	self.wantSafeSpawn = true;

	self notify("abort_killcam");
}

endKillcamIfNothingToShow()
{
	self endon("disconnect");
	self endon("killcam_ended");
	
	while(1)
	{
		// code may trim our archivetime to zero if there is nothing "recorded" to show.
		// this can happen when the person we're watching in our killcam goes into killcam himself.
		// in this case, end the killcam.
		if ( self.archivetime <= 0 )
			break;
		wait .05;
	}
	
	self notify("abort_killcam");
}

spawnedKillcamCleanup()
{
	self endon("disconnect");
	self endon("killcam_ended");
	
	self waittill("spawned");
	self thread killcamCleanup( false );
}

endedKillcamCleanup()
{
	self endon("disconnect");
	self endon("killcam_ended");
	
	level waittill("game_ended");

	self thread killcamCleanup( true );
}

killcamCleanup( clearState )
{
	if(isDefined(self.kc_skiptext))
		self.kc_skiptext.alpha = 0;

	if(isDefined(self.kc_timer))
		self.kc_timer.alpha = 0;

	if(isDefined(self.kc_icon))
		self.kc_icon.alpha = 0;

	if(isDefined(self.kc_othertext))
		self.kc_othertext.alpha = 0;

	self.killcam = undefined;

	if ( !level.gameEnded )
		self clearLowerMessage( "kc_info" );
	
	self thread maps\mp\gametypes\_spectating::setSpectatePermissions();
	
	self notify("killcam_ended"); // do this last, in case this function was called from a thread ending on it

	if ( !clearState )
		return;
			
	self.sessionstate = "dead";
	self ClearKillcamState();
}



cancelKillCamOnUse()
{
	self.cancelKillcam = false;
	self thread cancelKillCamOnUse_specificButton( ::cancelKillCamUseButton, ::cancelKillCamCallback );
	//self thread cancelKillCamOnUse_specificButton( ::cancelKillCamSafeSpawnButton, ::cancelKillCamSafeSpawnCallback );
}

cancelKillCamUseButton()
{
	return self useButtonPressed();
}
cancelKillCamSafeSpawnButton()
{
	return self fragButtonPressed();
}
cancelKillCamCallback()
{
	self.cancelKillcam = true;
}
cancelKillCamSafeSpawnCallback()
{
	self.cancelKillcam = true;
	self.wantSafeSpawn = true;
}

cancelKillCamOnUse_specificButton( pressingButtonFunc, finishedFunc )
{
	self endon ( "death_delay_finished" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	for ( ;; )
	{
		if ( !self [[pressingButtonFunc]]() )
		{
			wait ( 0.05 );
			continue;
		}
		
		buttonTime = 0;
		while( self [[pressingButtonFunc]]() )
		{
			buttonTime += 0.066;
			wait ( 0.05 );
		}
		
		if ( buttonTime >= 0.66 )
			continue;
		
		buttonTime = 0;
		
		while ( !self [[pressingButtonFunc]]() && buttonTime < 0.5 )
		{
			buttonTime += 0.066;
			wait ( 0.05 );
		}
		
		if ( buttonTime >= 0.66 )
			continue;
			
		self [[finishedFunc]]();
		return;
	}	
}

initKCElements()
{
	if ( !isDefined( self.kc_skiptext ) )
	{
		self.kc_skiptext = newClientHudElem(self);
		self.kc_skiptext.archived = false;
		self.kc_skiptext.x = 0;
		self.kc_skiptext.alignX = "center";
		self.kc_skiptext.alignY = "top";
		self.kc_skiptext.horzAlign = "center_adjustable";
		self.kc_skiptext.vertAlign = "top_adjustable";
		self.kc_skiptext.sort = 1; // force to draw after the bars
		self.kc_skiptext.font = "default";
		self.kc_skiptext.foreground = true;
		self.kc_skiptext.hideWhenInMenu = true;
		
		if ( level.splitscreen )
		{
			self.kc_skiptext.y = 20;
			self.kc_skiptext.fontscale = 1.2; // 1.8/1.5
		}
		else
		{
			self.kc_skiptext.y = 32;
			self.kc_skiptext.fontscale = 1.8;
		}
	}
	
	if ( !isDefined( self.kc_othertext ) )
	{
		self.kc_othertext = newClientHudElem(self);
		self.kc_othertext.archived = false;		
		self.kc_othertext.y = 18;
		self.kc_othertext.alignX = "left";
		self.kc_othertext.alignY = "top";
		self.kc_othertext.horzAlign = "center";
		self.kc_othertext.vertAlign = "middle";
		self.kc_othertext.sort = 10; // force to draw after the bars
		self.kc_othertext.font = "small";
		self.kc_othertext.foreground = true;
		self.kc_othertext.hideWhenInMenu = true;
		
		if ( level.splitscreen )
		{
			self.kc_othertext.x = 16;
			self.kc_othertext.fontscale = 1.2;
		}
		else
		{
			self.kc_othertext.x = 62;
			self.kc_othertext.fontscale = 1.6;
		}
	}

	if ( !isDefined( self.kc_icon ) )
	{
		self.kc_icon = newClientHudElem(self);
		self.kc_icon.archived = false;
		self.kc_icon.x = 16;
		self.kc_icon.y = 16;
		self.kc_icon.alignX = "left";
		self.kc_icon.alignY = "top";
		self.kc_icon.horzAlign = "center";
		self.kc_icon.vertAlign = "middle";
		self.kc_icon.sort = 1; // force to draw after the bars
		self.kc_icon.foreground = true;
		self.kc_icon.hideWhenInMenu = true;		
	}

	if ( !level.splitscreen )
	{
		if ( !isdefined( self.kc_timer ) )
		{
			self.kc_timer = createFontString( "hudbig", 1.0 );
			self.kc_timer.archived = false;
			self.kc_timer.x = 0;
			self.kc_timer.alignX = "center";
			self.kc_timer.alignY = "middle";
			self.kc_timer.horzAlign = "center_safearea";
			self.kc_timer.vertAlign = "top_adjustable";
			self.kc_timer.y = 42;
			self.kc_timer.sort = 1; // force to draw after the bars
			self.kc_timer.font = "hudbig";
			self.kc_timer.foreground = true;
			self.kc_timer.color = (0.85,0.85,0.85);
			self.kc_timer.hideWhenInMenu = true;
		}
	}
}

