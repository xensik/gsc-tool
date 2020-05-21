#include maps\mp\_utility;
#include common_scripts\utility;


init()
{
	//* needed by the UAV
	level._effect[ "ac130_engineeffect" ]		= loadfx( "fire/jet_engine_ac130" );

	/*level.ac130_use_duration = 40;
	level.ac130_num_flares = 2;
	
	makeDvarServerInfo( "ui_ac130usetime", level.ac130_use_duration );
	
	precacheShader( "black" );
	
	precacheString( &"AC130_HUD_FLIR" );
	precacheString( &"AC130_HUD_OPTICS" );
	
	precacheMenu( "ac130timer" );
	
	precacheModel( "vehicle_ac130_coop" );
	
	precacheItem("ac130_25mm_mp");
	precacheItem("ac130_40mm_mp");
	precacheItem("ac130_105mm_mp");
	
	PrecacheMiniMapIcon( "compass_objpoint_ac130_friendly" );
	PrecacheMiniMapIcon( "compass_objpoint_ac130_enemy" );
	
	precacheShellShock("ac130");

	angelFlarePrecache();
	
	level._effect[ "cloud" ] 					= loadfx( "misc/ac130_cloud" );
	level._effect[ "beacon" ] 					= loadfx( "misc/ir_beacon_coop" );
	level._effect[ "ac130_explode" ] 			= loadfx( "explosions/aerial_explosion_ac130_coop" );
	level._effect[ "ac130_flare" ] 				= loadfx( "misc/flares_cobra" );
	level._effect[ "ac130_light_red" ] 			= loadfx( "misc/aircraft_light_wingtip_red" );
	level._effect[ "ac130_light_white_blink" ] 	= loadfx( "misc/aircraft_light_white_blink" );
	level._effect[ "ac130_light_red_blink" ]	= loadfx( "misc/aircraft_light_red_blink" );

	// ac130 muzzleflash effects for player on ground to see
	level._effect[ "coop_muzzleflash_105mm" ] = loadfx( "muzzleflashes/ac130_105mm" );
	level._effect[ "coop_muzzleflash_40mm" ] = loadfx( "muzzleflashes/ac130_40mm" );
	
	level.radioForcedTransmissionQueue = [];
	level.enemiesKilledInTimeWindow = 0;
	level.lastRadioTransmission = getTime();
	
	level.color[ "white" ] = ( 1, 1, 1 );
	level.color[ "red" ] = ( 1, 0, 0 );
	level.color[ "blue" ] = ( .1, .3, 1 );
	
	level.cosine = [];
	level.cosine[ "45" ] = cos( 45 );
	level.cosine[ "5" ] = cos( 5 );
	
	level.HUDItem = [];
	
	level.physicsSphereRadius[ "ac130_25mm_mp" ] = 60;
	level.physicsSphereRadius[ "ac130_40mm_mp" ] = 600;
	level.physicsSphereRadius[ "ac130_105mm_mp" ] = 1000;
	
	level.physicsSphereForce[ "ac130_25mm_mp" ] = 0;
	level.physicsSphereForce[ "ac130_40mm_mp" ] = 3.0;
	level.physicsSphereForce[ "ac130_105mm_mp" ] = 6.0;
	
	level.weaponReloadTime[ "ac130_25mm_mp" ] = 1.5;
	level.weaponReloadTime[ "ac130_40mm_mp" ] = 3.0;
	level.weaponReloadTime[ "ac130_105mm_mp" ] = 5.0;
	
	level.ac130_Speed[ "move" ] = 250;
	level.ac130_Speed[ "rotate" ] = 70;
	
	//flag_init( "ir_beakons_on" );
	flag_init( "allow_context_sensative_dialog" );
	flag_set( "allow_context_sensative_dialog" );
	minimapOrigins = getEntArray( "minimap_corner", "targetname" );
	ac130Origin = (0,0,0);
	
	if ( miniMapOrigins.size )
		ac130Origin = maps\mp\gametypes\_spawnlogic::findBoxCenter( miniMapOrigins[0].origin, miniMapOrigins[1].origin );
	
	level.ac130 = spawn( "script_model", ac130Origin );
	level.ac130 setModel( "c130_zoomrig" );
	level.ac130.angles = ( 0, 115, 0 );
	level.ac130.owner = undefined;
	level.ac130.thermal_vision = "ac130_thermal_mp";
	level.ac130.enhanced_vision = "ac130_enhanced_mp";
	
	// used for debug printing
	level.ac130.targetname = "ac130rig_script_model";

	level.ac130 hide();
*/

	//* Wii: Needed By Sam Turret Script. -- ARomo
	level.ac130InUse = false;

/*	
	init_sounds();

	thread rotatePlane( "on" );
	thread ac130_spawn();
	thread onPlayerConnect();
	
	thread handleIncomingStinger();
	thread handleIncomingSAM();
	
	level.killstreakFuncs["ac130"] = ::tryUseAC130;
	
	level.ac130Queue = [];
*/
/#
	//*SetDevDvarIfUninitialized( "scr_ac130_timeout", level.ac130_use_duration );
	//*SetDevDvarIfUninitialized( "scr_debugac130", 0 );
	//*level thread debug_AC130();
#/
}


tryUseAC130( lifeId )
{
	if ( isDefined( level.civilianJetFlyBy ) )
	{
		self iPrintLnBold( &"MP_CIVILIAN_AIR_TRAFFIC" );
		return false;
	}

	if ( isDefined( level.ac130player ) || level.ac130InUse )
	{
		self iPrintLnBold( &"MP_AIR_SPACE_TOO_CROWDED" );
		return false;
	}

	if ( self isUsingRemote() )
	{
		return false;
	}
	
	if ( self isAirDenied() )
	{
		return false;
	}
	
	if ( self isEMPed() )
	{
		return false;
	}

	self setUsingRemote( "ac130" );
	result = self maps\mp\killstreaks\_killstreaks::initRideKillstreak();
	if ( result != "success" )
	{
		if ( result != "disconnect" )
			self clearUsingRemote();

		return false;
	}	

	result = setAC130Player( self );
	
	// this needs to get set after we say the player is using it because this could get set to true and then they leave the game
	// this fixes a bug where a player calls it, leaves before getting fully in it and then no one else can call it because it thinks it's being used
	if( result )
	{
		self maps\mp\_matchdata::logKillstreakEvent( "ac130", self.origin );

		//self.ac130LifeId = lifeId;
		level.ac130.planeModel.crashed = undefined;

		level.ac130InUse = true;
	}
	else
	{
		self clearUsingRemote();
	}

	return result;
}


init_sounds()
{
	setAC130Ambience( "ambient_ac130_int1" );
	
	level.scr_sound["foo"]["bar"] = "";
	//-------------------------------------------------------------------------------------------------
	//CONTEXT SENSATIVE DIALOG
	//-------------------------------------------------------------------------------------------------
	
	add_context_sensative_dialog( "ai", "in_sight", 0, "ac130_fco_moreenemy" );			// More enemy personnel.
	add_context_sensative_dialog( "ai", "in_sight", 1, "ac130_fco_getthatguy" );		// Get that guy.
	add_context_sensative_dialog( "ai", "in_sight", 2, "ac130_fco_guymovin" );			// Roger, guy movin'.
	add_context_sensative_dialog( "ai", "in_sight", 3, "ac130_fco_getperson" );			// Get that person.
	add_context_sensative_dialog( "ai", "in_sight", 4, "ac130_fco_guyrunnin" );			// Guy runnin'.
	add_context_sensative_dialog( "ai", "in_sight", 5, "ac130_fco_gotarunner" );		// Uh, we got a runner here.
	add_context_sensative_dialog( "ai", "in_sight", 6, "ac130_fco_backonthose" );		// Get back on those guys.
	add_context_sensative_dialog( "ai", "in_sight", 7, "ac130_fco_gonnagethim" );		// You gonna get him?
	add_context_sensative_dialog( "ai", "in_sight", 8, "ac130_fco_personnelthere" );	// Personnel right there.
	add_context_sensative_dialog( "ai", "in_sight", 9, "ac130_fco_nailthoseguys" );		// Nail those guys.
	add_context_sensative_dialog( "ai", "in_sight", 11, "ac130_fco_lightemup" );		// Light ‘em up.
	add_context_sensative_dialog( "ai", "in_sight", 12, "ac130_fco_takehimout" );		// Yeah take him out.
	add_context_sensative_dialog( "ai", "in_sight", 14, "ac130_plt_yeahcleared" );		// Yeah, cleared to engage.
	add_context_sensative_dialog( "ai", "in_sight", 15, "ac130_plt_copysmoke" );		// Copy, smoke ‘em.
	add_context_sensative_dialog( "ai", "in_sight", 16, "ac130_fco_rightthere" );		// Right there...tracking.
	add_context_sensative_dialog( "ai", "in_sight", 17, "ac130_fco_tracking" );			// Tracking.
	
	add_context_sensative_dialog( "ai", "wounded_crawl", 0, "ac130_fco_movingagain" );		// Ok he’s moving again.
	add_context_sensative_timeout( "ai", "wounded_crawl", undefined, 6 );
	
	add_context_sensative_dialog( "ai", "wounded_pain", 0, "ac130_fco_doveonground" );		// Yeah, he just dove on the ground.	
	add_context_sensative_dialog( "ai", "wounded_pain", 1, "ac130_fco_knockedwind" );		// Probably just knocked the wind out of him.
	add_context_sensative_dialog( "ai", "wounded_pain", 2, "ac130_fco_downstillmoving" );	// That guy's down but still moving.
	add_context_sensative_dialog( "ai", "wounded_pain", 3, "ac130_fco_gettinbackup" );		// He's gettin' back up.
	add_context_sensative_dialog( "ai", "wounded_pain", 4, "ac130_fco_yepstillmoving" );	// Yep, that guy’s still moving.
	add_context_sensative_dialog( "ai", "wounded_pain", 5, "ac130_fco_stillmoving" );		// He's still moving.
	add_context_sensative_timeout( "ai", "wounded_pain", undefined, 12 );
	
	add_context_sensative_dialog( "weapons", "105mm_ready", 0, "ac130_gnr_gunready1" );
	
	add_context_sensative_dialog( "weapons", "105mm_fired", 0, "ac130_gnr_shot1" );
	
	add_context_sensative_dialog( "plane", "rolling_in", 0, "ac130_plt_rollinin" );
	
	add_context_sensative_dialog( "explosion", "secondary", 0, "ac130_nav_secondaries1" );
	add_context_sensative_dialog( "explosion", "secondary", 1, "ac130_tvo_directsecondary1" );
	add_context_sensative_dialog( "explosion", "secondary", 1, "ac130_tvo_directsecondary2" );
	add_context_sensative_timeout( "explosion", "secondary", undefined, 7 );
	
	add_context_sensative_dialog( "kill", "single", 0, "ac130_plt_gottahurt" );			// Ooo that's gotta hurt.
	add_context_sensative_dialog( "kill", "single", 1, "ac130_fco_iseepieces" );		// Yeah, good kill. I see lots of little pieces down there.
	add_context_sensative_dialog( "kill", "single", 2, "ac130_fco_oopsiedaisy" );		// (chuckling) Oopsie-daisy.
	add_context_sensative_dialog( "kill", "single", 3, "ac130_fco_goodkill" );			// Good kill good kill.
	add_context_sensative_dialog( "kill", "single", 4, "ac130_fco_yougothim" );			// You got him.
	add_context_sensative_dialog( "kill", "single", 5, "ac130_fco_yougothim2" );		// You got him!
	add_context_sensative_dialog( "kill", "single", 6, "ac130_fco_thatsahit" );			// That's a hit.
	add_context_sensative_dialog( "kill", "single", 7, "ac130_fco_directhit" );			// Direct hit.
	add_context_sensative_dialog( "kill", "single", 8, "ac130_fco_rightontarget" );		// Yep, that was right on target.
	add_context_sensative_dialog( "kill", "single", 9, "ac130_fco_okyougothim" );		// Ok, you got him. Get back on the other guys.
	add_context_sensative_dialog( "kill", "single", 10, "ac130_fco_within2feet" );		// All right you got the guy. That might have been within two feet of him.
	
	add_context_sensative_dialog( "kill", "small_group", 0, "ac130_fco_nice" );			// (chuckling) Niiiice.
	add_context_sensative_dialog( "kill", "small_group", 1, "ac130_fco_directhits" );	// Yeah, direct hits right there.
	add_context_sensative_dialog( "kill", "small_group", 2, "ac130_fco_iseepieces" );	// Yeah, good kill. I see lots of little pieces down there.
	add_context_sensative_dialog( "kill", "small_group", 3, "ac130_fco_goodkill" );		// Good kill good kill.
	add_context_sensative_dialog( "kill", "small_group", 4, "ac130_fco_yougothim" );	// You got him.
	add_context_sensative_dialog( "kill", "small_group", 5, "ac130_fco_yougothim2" );	// You got him!
	add_context_sensative_dialog( "kill", "small_group", 6, "ac130_fco_thatsahit" );	// That's a hit.
	add_context_sensative_dialog( "kill", "small_group", 7, "ac130_fco_directhit" );	// Direct hit.
	add_context_sensative_dialog( "kill", "small_group", 8, "ac130_fco_rightontarget" );// Yep, that was right on target.
	add_context_sensative_dialog( "kill", "small_group", 9, "ac130_fco_okyougothim" );	// Ok, you got him. Get back on the other guys.
	
	add_context_sensative_dialog( "misc", "action", 0, "ac130_plt_scanrange" );		// Set scan range.
	add_context_sensative_timeout( "misc", "action", 0, 70 );
	
	add_context_sensative_dialog( "misc", "action", 1, "ac130_plt_cleanup" );		// Clean up that signal.
	add_context_sensative_timeout( "misc", "action", 1, 80 );
	
	add_context_sensative_dialog( "misc", "action", 2, "ac130_plt_targetreset" );	// Target reset.
	add_context_sensative_timeout( "misc", "action", 2, 55 );
	
	add_context_sensative_dialog( "misc", "action", 3, "ac130_plt_azimuthsweep" );	// Recalibrate azimuth sweep angle. Adjust elevation scan.
	add_context_sensative_timeout( "misc", "action", 3, 100 );
}


add_context_sensative_dialog( name1, name2, group, soundAlias )
{
	assert( isdefined( name1 ) );
	assert( isdefined( name2 ) );
	assert( isdefined( group ) );
	assert( isdefined( soundAlias ) );

	fullSoundAlias = maps\mp\gametypes\_teams::getTeamVoicePrefix( "allies" ) + soundAlias;
	//assertex( soundexists( fullSoundAlias ), "ERROR: missing soundalias " + fullSoundAlias );

	fullSoundAlias = maps\mp\gametypes\_teams::getTeamVoicePrefix( "axis" ) + soundAlias;
	//assertex( soundexists( fullSoundAlias ), "ERROR: missing soundalias " + fullSoundAlias );
	
	if( ( !isdefined( level.scr_sound[ name1 ] ) ) || ( !isdefined( level.scr_sound[ name1 ][ name2 ] ) ) || ( !isdefined( level.scr_sound[ name1 ][ name2 ][group] ) ) )
	{
		// creating group for the first time
		level.scr_sound[ name1 ][ name2 ][group] = spawnStruct();
		level.scr_sound[ name1 ][ name2 ][group].played = false;
		level.scr_sound[ name1 ][ name2 ][group].sounds = [];
	}
	
	//group exists, add the sound to the array
	index = level.scr_sound[ name1 ][ name2 ][group].sounds.size;
	level.scr_sound[ name1 ][ name2 ][group].sounds[index] = soundAlias;
}


add_context_sensative_timeout( name1, name2, groupNum, timeoutDuration )
{
	if( !isdefined( level.context_sensative_dialog_timeouts ) )
		level.context_sensative_dialog_timeouts = [];
	
	createStruct = false;
	if ( !isdefined( level.context_sensative_dialog_timeouts[ name1 ] ) )
		createStruct = true;
	else if ( !isdefined( level.context_sensative_dialog_timeouts[ name1 ][ name2 ] ) )
		createStruct = true;
	if ( createStruct )
		level.context_sensative_dialog_timeouts[ name1 ][ name2 ] = spawnStruct();
	
	if ( isdefined( groupNum ) )
	{
		level.context_sensative_dialog_timeouts[ name1 ][ name2 ].groups = [];
		level.context_sensative_dialog_timeouts[ name1 ][ name2 ].groups[ string( groupNum ) ] = spawnStruct();
		level.context_sensative_dialog_timeouts[ name1 ][ name2 ].groups[ string( groupNum ) ].v["timeoutDuration"] = timeoutDuration * 1000;
		level.context_sensative_dialog_timeouts[ name1 ][ name2 ].groups[ string( groupNum ) ].v["lastPlayed"] = ( timeoutDuration * -1000 );
	}
	else
	{
		level.context_sensative_dialog_timeouts[ name1 ][ name2 ].v["timeoutDuration"] = timeoutDuration * 1000;
		level.context_sensative_dialog_timeouts[ name1 ][ name2 ].v["lastPlayed"] = ( timeoutDuration * -1000 );
	}
}


/* 
 ============= 
///ScriptDocBegin
"Name: play_sound_on_entity( <alias> )"
"Summary: Play the specified sound alias on an entity at it's origin"
"Module: Sound"
"CallOn: An entity"
"MandatoryArg: <alias> : Sound alias to play"
"Example: level.player play_sound_on_entity( "breathing_better" );"
"SPMP: singleplayer"
///ScriptDocEnd
 ============= 
 */ 
play_sound_on_entity( alias )
{
	play_sound_on_tag( alias );
}

within_fov( start_origin, start_angles, end_origin, fov )
{
	normal = vectorNormalize( end_origin - start_origin );
	forward = anglestoforward( start_angles );
	dot = vectorDot( forward, normal );

	return dot >= fov;
}

/*
=============
///ScriptDocBegin
"Name: array_remove_nokeys( <ents> , <remover> )"
"Summary: array_remove used on non keyed arrays doesn't flip the array "
"Module: Utility"
"CallOn: Level"
"MandatoryArg: <ents>: array to remove from"
"MandatoryArg: <remover>: thing to remove from the array"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

array_remove_nokeys( ents, remover )
{
	newents = [];
	for ( i = 0; i < ents.size; i++ )
		if ( ents[ i ] != remover )
			newents[ newents.size ] = ents[ i ];
	return newents;
}

array_remove_index( array, index )
{
	newArray = [];
	keys = getArrayKeys( array );
	for ( i = ( keys.size - 1 );i >= 0 ; i -- )
	{
		if ( keys[ i ] != index )
			newArray[ newArray.size ] = array[ keys[ i ] ];
	}

	return newArray;
}


string( num )
{
	return( "" + num );
}


onPlayerConnect()
{
	for(;;)
	{
		level waittill( "connected", player );
		
		player thread onPlayerSpawned();
	}
}


onPlayerSpawned()
{
	self endon("disconnect");

	for(;;)
	{
		self waittill("spawned_player");
	}
}


deleteOnAC130PlayerRemoved()
{
	level waittill ( "ac130player_removed" );
	
	self delete();
}

setAC130Player( player )
{
	self endon ( "ac130player_removed" );
	
	if( IsDefined( level.ac130player ) )
		return false;

	level.ac130player = player;
	level.ac130.owner = player;
	level.ac130.planeModel show();
	level.ac130.planemodel thread playAC130Effects();
	level.ac130.incomingMissile = false;
	
	level.ac130.planeModel playLoopSound( "veh_ac130_ext_dist" );

	level.ac130.planeModel thread damageTracker();

	objModel = spawnPlane( player, "script_model", level.ac130.planeModel.origin, "compass_objpoint_ac130_friendly", "compass_objpoint_ac130_enemy" );
	objModel notSolid();
	objModel linkTo( level.ac130, "tag_player", ( 0, 80, 32 ), ( 0, -90, 0 ) );
	objModel thread deleteOnAC130PlayerRemoved();
	
	player startAC130();
	player openMenu( "ac130timer" );

	level.ac130.numFlares = level.ac130_num_flares;

/*
	result = player maps\mp\killstreaks\_killstreaks::initRideKillstreak();
	if ( result != "success" )
	{
		if ( result != "disconnect" )
		{
			if ( result == "fail" )
				player maps\mp\killstreaks\_killstreaks::giveKillstreak( "ac130", player.ac130LifeId == player.pers["deaths"], false );

			level thread removeAC130Player( player, result == "disconnect" );
		}

		return;
	}
*/
	thread teamPlayerCardSplash( "used_ac130", player );
	
	// with the way we do visionsets we need to wait for the clearRideIntro() is done before we set thermal
	player thread waitSetThermal( 1.0 );

	if ( getDvarInt( "camera_thirdPerson" ) )
		player setThirdPersonDOF( false );
	
	player _giveWeapon("ac130_105mm_mp");
	player _giveWeapon("ac130_40mm_mp");
	player _giveWeapon("ac130_25mm_mp");
	player SwitchToWeapon("ac130_105mm_mp");

	player SetPlayerData( "ac130Ammo105mm", player GetWeaponAmmoClip( "ac130_105mm_mp" ) );
	player SetPlayerData( "ac130Ammo40mm", player GetWeaponAmmoClip( "ac130_40mm_mp" ) );
	player SetPlayerData( "ac130Ammo25mm", player GetWeaponAmmoClip( "ac130_25mm_mp" ) );

	player thread overlay( player );
	player thread attachPlayer( player );
	player thread changeWeapons();
	player thread weaponFiredThread();
	player thread context_Sensative_Dialog();
	player thread shotFired();
	player thread clouds();
	
	player thread removeAC130PlayerAfterTime( level.ac130_use_duration * player.killStreakScaler );
	player thread removeAC130PlayerOnDisconnect();
	player thread removeAC130PlayerOnChangeTeams();
	player thread removeAC130PlayerOnSpectate();
	//player thread removeAC130PlayerOnDeath();
	player thread removeAC130PlayerOnCrash();
	//player thread removeAC130PlayerOnGameEnd();
	player thread removeAC130PlayerOnGameCleanup();
	
	thread AC130_AltScene();

	return true;
}

waitSetThermal( delay )
{
	self endon( "disconnect" );
	level endon( "ac130player_removed" );

	wait( delay	);

	self VisionSetThermalForPlayer( game["thermal_vision"], 0 );
	self ThermalVisionOn();
	self ThermalVisionFOFOverlayOn();
	self thread thermalVision();
}

playAC130Effects()
{
	wait .05;
	PlayFXOnTag( level._effect[ "ac130_light_red_blink" ] , self, "tag_light_belly" );
	PlayFXOnTag( level._effect[ "ac130_engineeffect" ] , self, "tag_body" );
	wait .5;
	PlayFXOnTag( level._effect[ "ac130_light_white_blink" ] , self, "tag_light_tail" );
	PlayFXOnTag( level._effect[ "ac130_light_red" ] , self, "tag_light_top" );
}

AC130_AltScene()
{
	// need team check
	foreach ( player in level.players )
	{
		if ( player != level.ac130player && player.team == level.ac130player.team )
			player thread setAltSceneObj( level.ac130.cameraModel, "tag_origin", 20 );
	}
}


removeAC130PlayerOnGameEnd()
{
	self endon ( "ac130player_removed" );
	
	level waittill ( "game_ended" );

	level thread removeAC130Player( self, false );
}


removeAC130PlayerOnGameCleanup()
{
	self endon ( "ac130player_removed" );
	
	level waittill ( "game_cleanup" );

	level thread removeAC130Player( self, false );
}


removeAC130PlayerOnDeath()
{
	self endon ( "ac130player_removed" );
	
	self waittill ( "death" );

	level thread removeAC130Player( self, false );
}


removeAC130PlayerOnCrash()
{
	self endon ( "ac130player_removed" );
	
	level.ac130.planeModel waittill ( "crashing" );

	level thread removeAC130Player( self, false );
}


removeAC130PlayerOnDisconnect()
{
	self endon ( "ac130player_removed" );

	self waittill ( "disconnect" );

	level thread removeAC130Player( self, true );
}

removeAC130PlayerOnChangeTeams()
{
	self endon ( "ac130player_removed" );

	self waittill ( "joined_team" );

	level thread removeAC130Player( self, false);
}

removeAC130PlayerOnSpectate()
{
	self endon ( "ac130player_removed" );

	self waittill_any ( "joined_spectators", "spawned" );

	level thread removeAC130Player( self, false);
}

removeAC130PlayerAfterTime( removeDelay )
{
	self endon ( "ac130player_removed" );
	
	lifeSpan = removeDelay;
/#
	lifeSpan = GetDvarFloat( "scr_ac130_timeout" );
#/
	SetDvar( "ui_ac130usetime", lifeSpan );
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( lifeSpan );
	
	level thread removeAC130Player( self, false );
}


removeAC130Player( player, disconnected )
{
	player notify ( "ac130player_removed" );
	level notify ( "ac130player_removed" );
	
	level.ac130.cameraModel notify ( "death" );
	
	waittillframeend;

	if ( !disconnected )
	{
		player clearUsingRemote();

		player stopLocalSound( "missile_incoming" ); 

		player show();
		player unlink();

		player ThermalVisionOff();
		player ThermalVisionFOFOverlayOff();
		player VisionSetThermalForPlayer( level.ac130.thermal_vision, 0 );
		player setBlurForPlayer( 0, 0 );
		player stopAC130();

		if ( getDvarInt( "camera_thirdPerson" ) )
			player setThirdPersonDOF( true );

		// take the killstreak weapons
		killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( "ac130" );
		player TakeWeapon( killstreakWeapon );
		player TakeWeapon( "ac130_105mm_mp" );
		player TakeWeapon( "ac130_40mm_mp" );
		player TakeWeapon( "ac130_25mm_mp" );

		if ( isDefined( player.darkScreenOverlay ) )
			player.darkScreenOverlay destroy();	

		keys = getArrayKeys( level.HUDItem );	
		
		foreach ( key in keys )
		{
			level.HUDItem[key] destroy();
			level.HUDItem[key] = undefined;
		}
	}
	
	// delay before AC130 can be used again
	wait ( 0.5 );
	
	level.ac130.planeModel playSound( "veh_ac130_ext_dist_fade" );
	
	wait ( 0.5 );

	// TODO: this might already be undefined if the player disconnected... need a better solution.
	// we could set it to "true" or something... but we'll have to check places it is used for potential issues with that.
	level.ac130player = undefined;
	level.ac130.planeModel hide();
	level.ac130.planeModel stopLoopSound();
	
	if ( isDefined( level.ac130.planeModel.crashed ) )
	{
		level.ac130InUse = false;
		return;
	}
	
	ac130model = spawn( "script_model", level.ac130.planeModel getTagOrigin( "tag_origin" ) );
	ac130model.angles = level.ac130.planeModel.angles;
	ac130model setModel( "vehicle_ac130_coop" );
	destPoint = ac130model.origin + ( anglestoright( ac130model.angles ) * 20000 );

	ac130model thread playAC130Effects();	
	ac130model moveTo( destPoint, 40.0, 0.0, 0.0 );
	ac130model thread deployFlares( true );

	wait ( 5.0 );
	ac130model thread deployFlares( true );

	wait ( 5.0 );
	ac130model thread deployFlares( true );

	level.ac130InUse = false;

	wait ( 30.0 );

	ac130model delete();
}


damageTracker() // self == level.ac130.planeModel
{
	self endon( "death" );
	self endon( "crashing" );
	level endon( "game_ended" );
	level endon( "ac130player_removed" );

	self.health = 999999; // keep it from dying anywhere in code
	self.maxHealth = 1000; // this is the health we'll check
	self.damageTaken = 0; // how much damage has it taken

	for ( ;; )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, sMeansOfDeath, modelName, tagName, partName, iDFlags, sWeapon );

		if ( isDefined( level.ac130player ) && level.teambased && isPlayer( attacker ) && attacker.team == level.ac130player.team && !isDefined( level.nukeDetonated ) )
			continue;

		if ( sMeansOfDeath == "MOD_RIFLE_BULLET" || sMeansOfDeath == "MOD_PISTOL_BULLET" || sMeansOfDeath == "MOD_EXPLOSIVE_BULLET" )
			continue;
		
		self.wasDamaged = true;

		modifiedDamage = damage;

		if ( isPlayer( attacker ) )
		{
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "ac130" );
		}
		
		// in case we are shooting from a remote position, like being in the osprey gunner shooting this
		if( IsDefined( attacker.owner ) && IsPlayer( attacker.owner ) )
		{
			attacker.owner maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "ac130" );
		}
		
		self.damageTaken += modifiedDamage;		

		if ( self.damageTaken >= self.maxHealth )
		{
			if ( isPlayer( attacker ) )
			{
				thread maps\mp\gametypes\_missions::vehicleKilled( level.ac130player, self, undefined, attacker, damage, sMeansOfDeath, sWeapon );
				thread teamPlayerCardSplash( "callout_destroyed_ac130", attacker );
				attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 400, sWeapon, sMeansOfDeath );
				attacker notify( "destroyed_killstreak" );
			}

			level thread crashPlane( 10.0 );
		}
	}
}


ac130_spawn()
{
	wait 0.05;
	
	ac130model = spawn( "script_model", level.ac130 getTagOrigin( "tag_player" ) );
	ac130model setModel( "vehicle_ac130_coop" );
	
	// used for debug printing
	ac130model.targetname = "vehicle_ac130_coop";

	ac130model setCanDamage( true );
	ac130model.maxhealth = 1000;
	ac130model.health = ac130model.maxhealth;
		
	//ac130model linkTo( level.ac130, "tag_player", ( 0, 0, 32 ), ( -25, 0, 0 ) );
	ac130model linkTo( level.ac130, "tag_player", ( 0, 80, 32 ), ( -25, 0, 0 ) );
	level.ac130.planeModel = ac130model;
	level.ac130.planeModel hide();

	ac130CameraModel = spawn( "script_model", level.ac130 getTagOrigin( "tag_player" ) );
	ac130CameraModel setModel( "tag_origin" );
	ac130CameraModel hide();

	// used for debug printing
	ac130CameraModel.targetname = "ac130CameraModel";

	ac130CameraModel linkTo( level.ac130, "tag_player", ( 0, 0, 32 ), ( -25, 0, 0 ) );
	level.ac130.cameraModel = ac130CameraModel;
	
	level.ac130player = level.players[0];
}


overlay( player )
{
	level.HUDItem = [];
	
	//thermalEnabled =  getIntProperty( "ac130_hud_text_thermal", 0 );
	//if( thermalEnabled )
	//{
		level.HUDItem[ "thermal_vision" ] = NewClientHudElem( player );
		level.HUDItem[ "thermal_vision" ].x = 200;
		level.HUDItem[ "thermal_vision" ].y = 0;
		level.HUDItem[ "thermal_vision" ].alignX = "left";
		level.HUDItem[ "thermal_vision" ].alignY = "top";
		level.HUDItem[ "thermal_vision" ].horzAlign = "left";
		level.HUDItem[ "thermal_vision" ].vertAlign = "top";
		level.HUDItem[ "thermal_vision" ].fontScale = 2.5;
		level.HUDItem[ "thermal_vision" ] SetText( &"AC130_HUD_FLIR" );
		level.HUDItem[ "thermal_vision" ].alpha = 1.0;

		level.HUDItem[ "enhanced_vision" ] = NewClientHudElem( player );
		level.HUDItem[ "enhanced_vision" ].x = -200;
		level.HUDItem[ "enhanced_vision" ].y = 0;
		level.HUDItem[ "enhanced_vision" ].alignX = "right";
		level.HUDItem[ "enhanced_vision" ].alignY = "top";
		level.HUDItem[ "enhanced_vision" ].horzAlign = "right";
		level.HUDItem[ "enhanced_vision" ].vertAlign = "top";
		level.HUDItem[ "enhanced_vision" ].fontScale = 2.5;
		level.HUDItem[ "enhanced_vision" ] SetText( &"AC130_HUD_OPTICS" );
		level.HUDItem[ "enhanced_vision" ].alpha = 1.0;
	//}
	
	//if( !level.splitscreen )
		player thread overlay_coords();
	
	//if ( thermalEnabled )
	//{
		player setBlurForPlayer( 1.2, 0 );
	//}
}


//hud_timer( duration )
//{
//	self endon ( "ac130player_removed" );
//	
//	level.HUDItem[ "timer" ] = NewClientHudElem( self );
//	level.HUDItem[ "timer" ].x = -100;
//	level.HUDItem[ "timer" ].y = 0;
//	level.HUDItem[ "timer" ].alignX = "right";
//	level.HUDItem[ "timer" ].alignY = "bottom";
//	level.HUDItem[ "timer" ].horzAlign = "right_adjustable";
//	level.HUDItem[ "timer" ].vertAlign = "bottom_adjustable";
//	level.HUDItem[ "timer" ].fontScale = 2.5;
//	level.HUDItem[ "timer" ] setTimer( 1.0 );
//	level.HUDItem[ "timer" ].alpha = 1.0;
//	
//	level.HUDItem[ "timer" ] setTimer( duration );
//}

overlay_coords()
{
	self endon ( "ac130player_removed" );
	
	// ac130 plane model position
	level.HUDItem[ "coord1_posx" ] = NewClientHudElem( self );
	level.HUDItem[ "coord1_posx" ].x = 60;
	level.HUDItem[ "coord1_posx" ].y = 100;
	level.HUDItem[ "coord1_posx" ].alignX = "right";
	level.HUDItem[ "coord1_posx" ].alignY = "middle";
	level.HUDItem[ "coord1_posx" ].horzAlign = "center";
	level.HUDItem[ "coord1_posx" ].vertAlign = "middle";
	level.HUDItem[ "coord1_posx" ].fontScale = 1.0;
	level.HUDItem[ "coord1_posx" ].alpha = 1.0;
	
	level.HUDItem[ "coord1_posy" ] = NewClientHudElem( self );
	level.HUDItem[ "coord1_posy" ].x = 100;
	level.HUDItem[ "coord1_posy" ].y = 100;
	level.HUDItem[ "coord1_posy" ].alignX = "right";
	level.HUDItem[ "coord1_posy" ].alignY = "middle";
	level.HUDItem[ "coord1_posy" ].horzAlign = "center";
	level.HUDItem[ "coord1_posy" ].vertAlign = "middle";
	level.HUDItem[ "coord1_posy" ].fontScale = 1.0;
	level.HUDItem[ "coord1_posy" ].alpha = 1.0;
	
	level.HUDItem[ "coord1_posz" ] = NewClientHudElem( self );
	level.HUDItem[ "coord1_posz" ].x = 140;
	level.HUDItem[ "coord1_posz" ].y = 100;
	level.HUDItem[ "coord1_posz" ].alignX = "right";
	level.HUDItem[ "coord1_posz" ].alignY = "middle";
	level.HUDItem[ "coord1_posz" ].horzAlign = "center";
	level.HUDItem[ "coord1_posz" ].vertAlign = "middle";
	level.HUDItem[ "coord1_posz" ].fontScale = 1.0;
	level.HUDItem[ "coord1_posz" ].alpha = 1.0;
		
	// player position
	level.HUDItem[ "coord2_posx" ] = NewClientHudElem( self );
	level.HUDItem[ "coord2_posx" ].x = 60;
	level.HUDItem[ "coord2_posx" ].y = 110;
	level.HUDItem[ "coord2_posx" ].alignX = "right";
	level.HUDItem[ "coord2_posx" ].alignY = "middle";
	level.HUDItem[ "coord2_posx" ].horzAlign = "center";
	level.HUDItem[ "coord2_posx" ].vertAlign = "middle";
	level.HUDItem[ "coord2_posx" ].fontScale = 1.0;
	level.HUDItem[ "coord2_posx" ].alpha = 1.0;

	level.HUDItem[ "coord2_posy" ] = NewClientHudElem( self );
	level.HUDItem[ "coord2_posy" ].x = 100;
	level.HUDItem[ "coord2_posy" ].y = 110;
	level.HUDItem[ "coord2_posy" ].alignX = "right";
	level.HUDItem[ "coord2_posy" ].alignY = "middle";
	level.HUDItem[ "coord2_posy" ].horzAlign = "center";
	level.HUDItem[ "coord2_posy" ].vertAlign = "middle";
	level.HUDItem[ "coord2_posy" ].fontScale = 1.0;
	level.HUDItem[ "coord2_posy" ].alpha = 1.0;

	level.HUDItem[ "coord2_posz" ] = NewClientHudElem( self );
	level.HUDItem[ "coord2_posz" ].x = 140;
	level.HUDItem[ "coord2_posz" ].y = 110;
	level.HUDItem[ "coord2_posz" ].alignX = "right";
	level.HUDItem[ "coord2_posz" ].alignY = "middle";
	level.HUDItem[ "coord2_posz" ].horzAlign = "center";
	level.HUDItem[ "coord2_posz" ].vertAlign = "middle";
	level.HUDItem[ "coord2_posz" ].fontScale = 1.0;
	level.HUDItem[ "coord2_posz" ].alpha = 1.0;

	// aiming position
	level.HUDItem[ "coord3_posx" ] = NewClientHudElem( self );
	level.HUDItem[ "coord3_posx" ].x = -120;
	level.HUDItem[ "coord3_posx" ].y = 100;
	level.HUDItem[ "coord3_posx" ].alignX = "right";
	level.HUDItem[ "coord3_posx" ].alignY = "middle";
	level.HUDItem[ "coord3_posx" ].horzAlign = "center";
	level.HUDItem[ "coord3_posx" ].vertAlign = "middle";
	level.HUDItem[ "coord3_posx" ].fontScale = 1.0;
	level.HUDItem[ "coord3_posx" ].alpha = 1.0;

	level.HUDItem[ "coord3_posy" ] = NewClientHudElem( self );
	level.HUDItem[ "coord3_posy" ].x = -80;
	level.HUDItem[ "coord3_posy" ].y = 100;
	level.HUDItem[ "coord3_posy" ].alignX = "right";
	level.HUDItem[ "coord3_posy" ].alignY = "middle";
	level.HUDItem[ "coord3_posy" ].horzAlign = "center";
	level.HUDItem[ "coord3_posy" ].vertAlign = "middle";
	level.HUDItem[ "coord3_posy" ].fontScale = 1.0;
	level.HUDItem[ "coord3_posy" ].alpha = 1.0;

	level.HUDItem[ "coord3_posz" ] = NewClientHudElem( self );
	level.HUDItem[ "coord3_posz" ].x = -40;
	level.HUDItem[ "coord3_posz" ].y = 100;
	level.HUDItem[ "coord3_posz" ].alignX = "right";
	level.HUDItem[ "coord3_posz" ].alignY = "middle";
	level.HUDItem[ "coord3_posz" ].horzAlign = "center";
	level.HUDItem[ "coord3_posz" ].vertAlign = "middle";
	level.HUDItem[ "coord3_posz" ].fontScale = 1.0;
	level.HUDItem[ "coord3_posz" ].alpha = 1.0;

	wait 0.05;
	self thread updateAimingCoords();
	while( true )
	{
		level.HUDItem[ "coord1_posx" ] SetValue( abs( level.ac130.planeModel.origin[0] ) );
		level.HUDItem[ "coord1_posy" ] SetValue( abs( level.ac130.planeModel.origin[1] ) );
		level.HUDItem[ "coord1_posz" ] SetValue( abs( level.ac130.planeModel.origin[2] ) );

		level.HUDItem[ "coord2_posx" ] SetValue( abs( self.origin[0] ) );
		level.HUDItem[ "coord2_posy" ] SetValue( abs( self.origin[1] ) );
		level.HUDItem[ "coord2_posz" ] SetValue( abs( self.origin[2] ) );
		
		//pos = physicstrace( self.origin, self.origin - ( 0, 0, 100000 ) );
		//if( ( isdefined( pos ) ) && ( isdefined( pos[2] ) ) )
		//{
		//	alt = ( ( self.origin[2] - pos[2] ) * 1.5 );
		//	level.HUDItem[ "coordinate_agl" ] SetValue( abs( int( alt ) ) );
		//}
		
		//wait ( 0.75 + randomfloat( 2 ) );
		wait( 0.5 );
	}
}

updateAimingCoords()
{
	self endon ( "ac130player_removed" );

	while( true )
	{
		origin = self GetEye();
		angles = self GetPlayerAngles();
		forward = AnglesToForward( angles );
		endpoint = origin + forward * 15000;
		pos = PhysicsTrace( origin, endpoint );
		level.HUDItem[ "coord3_posx" ] SetValue( abs( pos[0] ) );
		level.HUDItem[ "coord3_posy" ] SetValue( abs( pos[1] ) );
		level.HUDItem[ "coord3_posz" ] SetValue( abs( pos[2] ) );

		wait( 0.05 );
	}
}


ac130ShellShock()
{
	self endon ( "ac130player_removed" );

	level endon( "post_effects_disabled" );
	duration = 5;
	for (;;)
	{
		self shellshock( "ac130", duration );
		wait duration;
	}
}


rotatePlane( toggle )
{
	level notify("stop_rotatePlane_thread");
	level endon("stop_rotatePlane_thread");
	
	if (toggle == "on")
	{
		rampupDegrees = 10;
		rotateTime = ( level.ac130_Speed[ "rotate" ] / 360 ) * rampupDegrees;
		level.ac130 rotateyaw( level.ac130.angles[ 2 ] + rampupDegrees, rotateTime, rotateTime, 0 );
		
		for (;;)
		{
			level.ac130 rotateyaw( 360, level.ac130_Speed[ "rotate" ] );
			wait level.ac130_Speed[ "rotate" ];
		}
	}
	else if (toggle == "off")
	{
		slowdownDegrees = 10;
		rotateTime = ( level.ac130_Speed[ "rotate" ] / 360 ) * slowdownDegrees;
		level.ac130 rotateyaw( level.ac130.angles[ 2 ] + slowdownDegrees, rotateTime, 0, rotateTime );
	}
}

/#
debug_AC130()
{
	level endon( "game_ended" );
	while( true )
	{
		if( GetDvarInt( "scr_debugac130" ) )
		{
			if( IsDefined( level.ac130.planeModel ) )
			{
				Line( level.ac130.origin, self.ac130.planeModel.origin, ( 1, 0, 0 ) );
				Print3d( level.ac130 getTagOrigin( "tag_player" ), "tag_player", ( 0, 0, 1 ) );
				Print3d( level.ac130.origin, "level.ac130 origin", ( 0, 0, 1 ) );
				Print3d( level.ac130.planeModel.origin, "level.ac130.planeModel origin", ( 0, 0, 1 ) );
			}
		}
		wait( 0.05 );
	}
}
#/

attachPlayer( player )
{
	self PlayerLinkWeaponviewToDelta( level.ac130, "tag_player", 1.0, 35, 35, 35, 35 );
	self setPlayerAngles( level.ac130 getTagAngles( "tag_player" ) );	
}


changeWeapons()
{
	self endon ( "ac130player_removed" );

	wait( 0.05 );
	self EnableWeapons();

	for(;;)
	{
		self waittill ( "weapon_change", newWeapon );

		self thread play_sound_on_entity( "ac130_weapon_switch" );	
	}
}


weaponFiredThread()
{
	self endon ( "ac130player_removed" );

	for(;;)
	{
		self waittill( "weapon_fired" );
		
		weapon = self getCurrentWeapon();
		
		switch( weapon )
		{
		case "ac130_105mm_mp":
			self thread gun_fired_and_ready_105mm();			
			earthquake (0.2, 1, level.ac130.planeModel.origin, 1000);
			self SetPlayerData( "ac130Ammo105mm", self GetWeaponAmmoClip( weapon ) );
			break;
		case "ac130_40mm_mp":
			earthquake (0.1, 0.5, level.ac130.planeModel.origin, 1000);
			self SetPlayerData( "ac130Ammo40mm", self GetWeaponAmmoClip( weapon ) );
			break;
		case "ac130_25mm_mp":
			self SetPlayerData( "ac130Ammo25mm", self GetWeaponAmmoClip( weapon ) );
			break;
		}

		if ( self GetWeaponAmmoClip( weapon ) )
			continue;
			
		self thread weaponReload( weapon );
	}
}


weaponReload( weapon )
{
	self endon ( "ac130player_removed" );

	wait level.weaponReloadTime[ weapon ];
	
	self setWeaponAmmoClip( weapon, 9999 );
	
	switch( weapon )
	{
	case "ac130_105mm_mp":
		self SetPlayerData( "ac130Ammo105mm", self GetWeaponAmmoClip( weapon ) );
		break;
	case "ac130_40mm_mp":
		self SetPlayerData( "ac130Ammo40mm", self GetWeaponAmmoClip( weapon ) );
		break;
	case "ac130_25mm_mp":
		self SetPlayerData( "ac130Ammo25mm", self GetWeaponAmmoClip( weapon ) );
		break;
	}

	// force the reload to stop if we're currently using the weapon
	if ( self getCurrentWeapon() == weapon )
	{
		self takeWeapon( weapon );
		self _giveWeapon( weapon );
		self switchToWeapon( weapon );
	}
}


thermalVision()
{
	self endon ( "ac130player_removed" );
	
	if ( getIntProperty( "ac130_thermal_enabled", 1 ) == 0 )
		return;
	
	inverted = false;

	self VisionSetThermalForPlayer( level.ac130.enhanced_vision, 1 );
	level.HUDItem["thermal_vision"].alpha = 0.25;
	level.HUDItem["enhanced_vision"].alpha = 1.0;

	self notifyOnPlayerCommand( "switch thermal", "+usereload" );
	self notifyOnPlayerCommand( "switch thermal", "+activate" );

	for (;;)
	{
		self waittill ( "switch thermal" );
		
		if ( !inverted )
		{
			self VisionSetThermalForPlayer( level.ac130.thermal_vision, 0.62 );
			level.HUDItem["thermal_vision"].alpha = 1.0;
			level.HUDItem["enhanced_vision"].alpha = 0.25;
		}
		else
		{
			self VisionSetThermalForPlayer( level.ac130.enhanced_vision, 0.51 );
			level.HUDItem["thermal_vision"].alpha = 0.25;
			level.HUDItem["enhanced_vision"].alpha = 1.0;
		}

		inverted = !inverted;
	}
}




clouds()
{
	self endon ( "ac130player_removed" );

	wait 6;
	clouds_create();
	for(;;)
	{
		wait( randomfloatrange( 40, 80 ) );
		clouds_create();
	}
}


clouds_create()
{
	if ( ( isdefined( level.playerWeapon ) ) && ( issubstr( tolower( level.playerWeapon ), "25" ) ) )
		return;
	playfxontagforclients( level._effect[ "cloud" ], level.ac130, "tag_player", level.ac130player );
}


gun_fired_and_ready_105mm()
{
	self endon ( "ac130player_removed" );
	level notify( "gun_fired_and_ready_105mm" );
	level endon( "gun_fired_and_ready_105mm" );
	
	wait 0.5;
	
	if ( randomint( 2 ) == 0 )
		thread context_Sensative_Dialog_Play_Random_Group_Sound( "weapons", "105mm_fired" );
	
	wait 5.0;
	
	thread context_Sensative_Dialog_Play_Random_Group_Sound( "weapons", "105mm_ready" );
}


shotFired()
{
	self endon ( "ac130player_removed" );
	
	for (;;)
	{
		self waittill( "projectile_impact", weaponName, position, radius );
		
		if ( issubstr( tolower( weaponName ), "105" ) )
		{
			earthquake( 0.4, 1.0, position, 3500 );
			self thread shotFiredDarkScreenOverlay();
		}
		else if ( issubstr( tolower( weaponName ), "40" ) )
		{
			earthquake( 0.2, 0.5, position, 2000 );
		}
		
		if ( getIntProperty( "ac130_ragdoll_deaths", 0 ) )
			thread shotFiredPhysicsSphere( position, weaponName );
			
		wait 0.05;
	}
}


shotFiredPhysicsSphere( center, weapon )
{
	wait 0.1;
	physicsExplosionSphere( center, level.physicsSphereRadius[ weapon ], level.physicsSphereRadius[ weapon ] / 2, level.physicsSphereForce[ weapon ] );
}


shotFiredDarkScreenOverlay()
{
	self endon( "ac130player_removed" );
	self notify( "darkScreenOverlay" );
	self endon( "darkScreenOverlay" );
	
	if ( !isdefined( self.darkScreenOverlay ) )
	{
		self.darkScreenOverlay = NewClientHudElem( self );
		self.darkScreenOverlay.x = 0;
		self.darkScreenOverlay.y = 0;
		self.darkScreenOverlay.alignX = "left";
		self.darkScreenOverlay.alignY = "top";
		self.darkScreenOverlay.horzAlign = "fullscreen";
		self.darkScreenOverlay.vertAlign = "fullscreen";
		self.darkScreenOverlay setshader ( "black", 640, 480 );
		self.darkScreenOverlay.sort = -10;
		self.darkScreenOverlay.alpha = 0.0;
	}
	
	self.darkScreenOverlay.alpha = 0.0;
	self.darkScreenOverlay fadeOverTime( 0.2 );
	self.darkScreenOverlay.alpha = 0.6;
	wait 0.4;
	self.darkScreenOverlay fadeOverTime( 0.8 );
	self.darkScreenOverlay.alpha = 0.0;
}


add_beacon_effect()
{
	self endon( "death" );
	
	flashDelay = 0.75;
	
	wait randomfloat(3.0);
	for (;;)
	{
		if ( level.ac130player )
			playfxontagforclients( level._effect[ "beacon" ], self, "j_spine4", level.ac130player );
		wait flashDelay;
	}
}


context_Sensative_Dialog()
{
	thread enemy_killed_thread();
	
	thread context_Sensative_Dialog_Guy_In_Sight();
	thread context_Sensative_Dialog_Guy_Crawling();
	thread context_Sensative_Dialog_Guy_Pain();
	thread context_Sensative_Dialog_Secondary_Explosion_Vehicle();
	thread context_Sensative_Dialog_Kill_Thread();
	thread context_Sensative_Dialog_Locations();
	thread context_Sensative_Dialog_Filler();
}


context_Sensative_Dialog_Guy_In_Sight()
{
	self endon ( "ac130player_removed" );

	for (;;)
	{
		if ( context_Sensative_Dialog_Guy_In_Sight_Check() )
			thread context_Sensative_Dialog_Play_Random_Group_Sound( "ai", "in_sight" );
		wait randomfloatrange( 1, 3 );
	}
}


context_Sensative_Dialog_Guy_In_Sight_Check()
{
	prof_begin( "AI_in_sight_check" );
	
	//enemies = getaiarray( "axis" );
	//replace with level of enemy team members?
	enemies = [];
	
	for( i = 0 ; i < enemies.size ; i++ )
	{
		if ( !isdefined( enemies[ i ] ) )
			continue;
		
		if ( !isalive( enemies[ i ] ) )
			continue;
		
		if ( within_fov( level.ac130player getEye(), level.ac130player getPlayerAngles(), enemies[ i ].origin, level.cosine[ "5" ] ) )
		{
			prof_end( "AI_in_sight_check" );
			return true;
		}
		wait 0.05;
	}
	
	prof_end( "AI_in_sight_check" );
	return false;
}


context_Sensative_Dialog_Guy_Crawling()
{
	self endon ( "ac130player_removed" );

	for (;;)
	{
		level waittill ( "ai_crawling", guy );
		
/#
		if ( ( isdefined( guy ) ) && ( isdefined( guy.origin ) ) )
		{
			if ( getdvar( "ac130_debug_context_sensative_dialog", 0 ) == "1" )
				thread debug_line(level.ac130player.origin, guy.origin, 5.0, ( 0, 1, 0 ) );
		}
#/		
		thread context_Sensative_Dialog_Play_Random_Group_Sound( "ai", "wounded_crawl" );
	}
}


context_Sensative_Dialog_Guy_Pain()
{
	self endon ( "ac130player_removed" );

	for (;;)
	{
		level waittill ( "ai_pain", guy );		
/#		
		if ( ( isdefined( guy ) ) && ( isdefined( guy.origin ) ) )
		{
			if ( getdvar( "ac130_debug_context_sensative_dialog" ) == "1" )
				thread debug_line( level.ac130player.origin, guy.origin, 5.0, ( 1, 0, 0 ) );
		}
#/		
		thread context_Sensative_Dialog_Play_Random_Group_Sound( "ai", "wounded_pain" );
	}
}


context_Sensative_Dialog_Secondary_Explosion_Vehicle()
{
	self endon ( "ac130player_removed" );
	
	for (;;)
	{
		level waittill ( "player_destroyed_car", player, vehicle_origin );	
		
		wait 1;	
/#
		if ( isdefined( vehicle_origin ) )
		{
			if ( getdvar( "ac130_debug_context_sensative_dialog" ) == "1" )
				thread debug_line( level.ac130player.origin, vehicle_origin, 5.0, ( 0, 0, 1 ) );
		}
#/
		
		thread context_Sensative_Dialog_Play_Random_Group_Sound( "explosion", "secondary" );
	}
}


enemy_killed_thread()
{
	self endon ( "ac130player_removed" );

	for ( ;; )
	{		
		level waittill ( "ai_killed", guy );
		
		// context kill dialog
		thread context_Sensative_Dialog_Kill( guy, level.ac130player );
	}
}


context_Sensative_Dialog_Kill( guy, attacker )
{
	if ( !isdefined( attacker ) )
		return;
	
	if ( !isplayer( attacker ) )
		return;
	
	level.enemiesKilledInTimeWindow++;
	level notify ( "enemy_killed" );

/#	
	if ( ( isdefined( guy ) ) && ( isdefined( guy.origin ) ) )
	{
		if ( getdvar( "ac130_debug_context_sensative_dialog" ) == "1" )
			thread debug_line( level.ac130player.origin, guy.origin, 5.0, ( 1, 1, 0 ) );
	}
#/

}


context_Sensative_Dialog_Kill_Thread()
{
	self endon ( "ac130player_removed" );

	timeWindow = 1;
	for (;;)
	{
		level waittill ( "enemy_killed" );
		wait timeWindow;
		println ( "guys killed in time window: " );
		println ( level.enemiesKilledInTimeWindow );
		
		soundAlias1 = "kill";
		soundAlias2 = undefined;
		
		if ( level.enemiesKilledInTimeWindow >= 2 )
			soundAlias2 = "small_group";
		else
		{
			soundAlias2 = "single";
			if ( randomint( 3 ) != 1 )
			{
				level.enemiesKilledInTimeWindow = 0;
				continue;
			}
		}
		
		level.enemiesKilledInTimeWindow = 0;
		assert( isdefined( soundAlias2 ) );
		
		thread context_Sensative_Dialog_Play_Random_Group_Sound( soundAlias1, soundAlias2, true );
	}
}


context_Sensative_Dialog_Locations()
{
	array_thread( getentarray( "context_dialog_car",		"targetname" ),	::context_Sensative_Dialog_Locations_Add_Notify_Event, "car" );
	array_thread( getentarray( "context_dialog_truck",		"targetname" ),	::context_Sensative_Dialog_Locations_Add_Notify_Event, "truck" );
	array_thread( getentarray( "context_dialog_building",	"targetname" ),	::context_Sensative_Dialog_Locations_Add_Notify_Event, "building" );
	array_thread( getentarray( "context_dialog_wall",		"targetname" ),	::context_Sensative_Dialog_Locations_Add_Notify_Event, "wall" );
	array_thread( getentarray( "context_dialog_field",		"targetname" ),	::context_Sensative_Dialog_Locations_Add_Notify_Event, "field" );
	array_thread( getentarray( "context_dialog_road",		"targetname" ),	::context_Sensative_Dialog_Locations_Add_Notify_Event, "road" );
	array_thread( getentarray( "context_dialog_church",		"targetname" ),	::context_Sensative_Dialog_Locations_Add_Notify_Event, "church" );
	array_thread( getentarray( "context_dialog_ditch",		"targetname" ),	::context_Sensative_Dialog_Locations_Add_Notify_Event, "ditch" );
	
	thread context_Sensative_Dialog_Locations_Thread();
}

context_Sensative_Dialog_Locations_Thread()
{
	self endon ( "ac130player_removed" );

	for (;;)
	{
		level waittill ( "context_location", locationType );
		
		if ( !isdefined( locationType ) )
		{
			assertMsg( "LocationType " + locationType + " is not valid" );
			continue;
		}
		
		if ( !flag( "allow_context_sensative_dialog" ) )
			continue;
		
		thread context_Sensative_Dialog_Play_Random_Group_Sound( "location", locationType );
		
		wait ( 5 + randomfloat( 10 ) );
	}
}

context_Sensative_Dialog_Locations_Add_Notify_Event( locationType )
{
	self endon ( "ac130player_removed" );

	for (;;)
	{
		self waittill ( "trigger", triggerer );
		
		if ( !isdefined( triggerer ) )
			continue;
		
		if ( ( !isdefined( triggerer.team) ) || ( triggerer.team != "axis" ) )
			continue;
		
		level notify ( "context_location", locationType );
		
		wait 5;
	}
}

context_Sensative_Dialog_VehicleSpawn( vehicle )
{
	if ( vehicle.script_team != "axis" )
		return;
	
	thread context_Sensative_Dialog_VehicleDeath( vehicle );
	
	vehicle endon( "death" );
	
	while( !within_fov( level.ac130player getEye(), level.ac130player getPlayerAngles(), vehicle.origin, level.cosine[ "45" ] ) )
		wait 0.5;
	
	context_Sensative_Dialog_Play_Random_Group_Sound( "vehicle", "incoming" );
}

context_Sensative_Dialog_VehicleDeath( vehicle )
{
	vehicle waittill( "death" );
	thread context_Sensative_Dialog_Play_Random_Group_Sound( "vehicle", "death" );
}

context_Sensative_Dialog_Filler()
{
	self endon ( "ac130player_removed" );

	for(;;)
	{
		if( ( isdefined( level.radio_in_use ) ) && ( level.radio_in_use == true ) )
			level waittill ( "radio_not_in_use" );
		
		// if 3 seconds has passed and nothing has been transmitted then play a sound
		currentTime = getTime();
		if ( ( currentTime - level.lastRadioTransmission ) >= 3000 )
		{
			level.lastRadioTransmission = currentTime;
			thread context_Sensative_Dialog_Play_Random_Group_Sound( "misc", "action" );
		}
		
		wait 0.25;
	}
}

context_Sensative_Dialog_Play_Random_Group_Sound( name1, name2, force_transmit_on_turn )
{
	level endon ( "ac130player_removed" );

	assert( isdefined( level.scr_sound[ name1 ] ) );
	assert( isdefined( level.scr_sound[ name1 ][ name2 ] ) );
	
	if ( !isdefined( force_transmit_on_turn ) )
		force_transmit_on_turn = false;
	
	if ( !flag( "allow_context_sensative_dialog" ) )
	{
		if ( force_transmit_on_turn )
			flag_wait( "allow_context_sensative_dialog" );
		else
			return;
	}
	
	validGroupNum = undefined;
	
	randGroup = randomint( level.scr_sound[ name1 ][ name2 ].size );
	
	// if randGroup has already played
	if ( level.scr_sound[ name1 ][ name2 ][ randGroup ].played == true )
	{
		//loop through all groups and use the next one that hasn't played yet
		
		for( i = 0 ; i < level.scr_sound[ name1 ][ name2 ].size ; i++ )
		{
			randGroup++;
			if ( randGroup >= level.scr_sound[ name1 ][ name2 ].size )
				randGroup = 0;
			if ( level.scr_sound[ name1 ][ name2 ][ randGroup ].played == true )
				continue;
			validGroupNum = randGroup;
			break;
		}
		
		// all groups have been played, reset all groups to false and pick a new random one
		if ( !isdefined( validGroupNum ) )
		{
			for( i = 0 ; i < level.scr_sound[ name1 ][ name2 ].size ; i++ )
				level.scr_sound[ name1 ][ name2 ][ i ].played = false;
			validGroupNum = randomint( level.scr_sound[ name1 ][ name2 ].size );
		}
	}
	else
		validGroupNum = randGroup;
	
	assert( isdefined( validGroupNum ) );
	assert( validGroupNum >= 0 );
	
	if ( context_Sensative_Dialog_Timedout( name1, name2, validGroupNum ) )
		return;
	
	level.scr_sound[ name1 ][ name2 ][ validGroupNum ].played = true;
	randSound = randomint( level.scr_sound[ name1 ][ name2 ][ validGroupNum ].size );
	playSoundOverRadio( level.scr_sound[ name1 ][ name2 ][ validGroupNum ].sounds[ randSound ], force_transmit_on_turn );
}

context_Sensative_Dialog_Timedout( name1, name2, groupNum )
{
	// dont play this sound if it has a timeout specified and the timeout has not expired
	
	if( !isdefined( level.context_sensative_dialog_timeouts ) )
		return false;
	
	if( !isdefined( level.context_sensative_dialog_timeouts[ name1 ] ) )
		return false;
	
	if( !isdefined( level.context_sensative_dialog_timeouts[ name1 ][name2 ] ) )
		return false;
	
	if( isdefined( level.context_sensative_dialog_timeouts[ name1 ][ name2 ].groups ) && isdefined( level.context_sensative_dialog_timeouts[ name1 ][ name2 ].groups[ string( groupNum ) ] ) )
	{
		assert( isdefined( level.context_sensative_dialog_timeouts[ name1 ][ name2 ].groups[ string( groupNum ) ].v[ "timeoutDuration" ] ) );
		assert( isdefined( level.context_sensative_dialog_timeouts[ name1 ][ name2 ].groups[ string( groupNum ) ].v[ "lastPlayed" ] ) );
		
		currentTime = getTime();
		if( ( currentTime - level.context_sensative_dialog_timeouts[ name1 ][ name2 ].groups[ string( groupNum ) ].v[ "lastPlayed" ] ) < level.context_sensative_dialog_timeouts[ name1 ][ name2 ].groups[ string( groupNum ) ].v[ "timeoutDuration" ] )
			return true;
		
		level.context_sensative_dialog_timeouts[ name1 ][ name2 ].groups[ string( groupNum ) ].v[ "lastPlayed" ] = currentTime;
	}
	else if ( isdefined( level.context_sensative_dialog_timeouts[ name1 ][ name2 ].v ) )
	{
		assert( isdefined( level.context_sensative_dialog_timeouts[ name1 ][ name2 ].v[ "timeoutDuration" ] ) );
		assert( isdefined( level.context_sensative_dialog_timeouts[ name1 ][ name2 ].v[ "lastPlayed" ] ) );
		
		currentTime = getTime();
		if( ( currentTime - level.context_sensative_dialog_timeouts[ name1 ][ name2 ].v[ "lastPlayed" ] ) < level.context_sensative_dialog_timeouts[ name1 ][ name2 ].v[ "timeoutDuration" ] )
			return true;
		
		level.context_sensative_dialog_timeouts[ name1 ][ name2 ].v[ "lastPlayed" ] = currentTime;
	}
	
	return false;
}

playSoundOverRadio( soundAlias, force_transmit_on_turn, timeout )
{
	if ( !isdefined( level.radio_in_use ) )
		level.radio_in_use = false;
	if ( !isdefined( force_transmit_on_turn ) )
		force_transmit_on_turn = false;
	if ( !isdefined( timeout ) )
		timeout = 0;
	timeout = timeout * 1000;
	soundQueueTime = gettime();
	
	soundPlayed = false;
	soundPlayed = playAliasOverRadio( soundAlias );
	if ( soundPlayed )
		return;
	
	// Dont make the sound wait to be played if force transmit wasn't set to true
	if ( !force_transmit_on_turn )
		return;
	
	level.radioForcedTransmissionQueue[ level.radioForcedTransmissionQueue.size ] = soundAlias;
	while( !soundPlayed )
	{
		if ( level.radio_in_use )
			level waittill ( "radio_not_in_use" );
		
		if ( ( timeout > 0 ) && ( getTime() - soundQueueTime > timeout ) )
			break;
			
		if ( !isDefined( level.ac130player ) )
			break;
		
		soundPlayed = playAliasOverRadio( level.radioForcedTransmissionQueue[ 0 ] );
		if ( !level.radio_in_use && isDefined( level.ac130player ) && !soundPlayed )
			assertMsg( "The radio wasn't in use but the sound still did not play. This should never happen." );
	}
	level.radioForcedTransmissionQueue = array_remove_index( level.radioForcedTransmissionQueue, 0 );
}


playAliasOverRadio( soundAlias )
{
	if ( level.radio_in_use )
		return false;
	
	if ( !isDefined( level.ac130player ) )
		return false;
	
	level.radio_in_use = true;
	if ( self.team == "allies" || self.team == "axis" )
	{
		soundAlias = maps\mp\gametypes\_teams::getTeamVoicePrefix( self.team ) + soundAlias;
		level.ac130player playLocalSound( soundAlias );
	}
	wait ( 4.0 );
	level.radio_in_use = false;
	level.lastRadioTransmission = getTime();
	level notify ( "radio_not_in_use" );
	return true;
}


debug_circle(center, radius, duration, color, startDelay, fillCenter)
{
	circle_sides = 16;
	
	angleFrac = 360/circle_sides;
	circlepoints = [];
	for(i=0;i<circle_sides;i++)
	{
		angle = (angleFrac * i);
		xAdd = cos(angle) * radius;
		yAdd = sin(angle) * radius;
		x = center[0] + xAdd;
		y = center[1] + yAdd;
		z = center[2];
		circlepoints[circlepoints.size] = (x,y,z);
	}
	
	if (isdefined(startDelay))
		wait startDelay;
	
	thread debug_circle_drawlines(circlepoints, duration, color, fillCenter, center);
}


debug_circle_drawlines(circlepoints, duration, color, fillCenter, center)
{
	if (!isdefined(fillCenter))
		fillCenter = false;
	if (!isdefined(center))
		fillCenter = false;
	
	for( i = 0 ; i < circlepoints.size ; i++ )
	{
		start = circlepoints[i];
		if (i + 1 >= circlepoints.size)
			end = circlepoints[0];
		else
			end = circlepoints[i + 1];
		
		thread debug_line( start, end, duration, color);
		
		if (fillCenter)
			thread debug_line( center, start, duration, color);
	}
}


debug_line(start, end, duration, color)
{
	if (!isdefined(color))
		color = (1,1,1);
	
	for ( i = 0; i < (duration * 20) ; i++ )
	{
		line(start, end, color);
		wait 0.05;
	}
}


handleIncomingStinger()
{
	level endon ( "game_ended" );
	
	for ( ;; )
	{
		level waittill ( "stinger_fired", player, missile, lockTarget );
		
		if ( !IsDefined( lockTarget ) || (lockTarget != level.ac130.planeModel) )
			continue;
		
		missile thread stingerProximityDetonate( player, player.team );
	}
}

deleteAfterTime( delay )
{
	wait ( delay );
	
	self delete();
}


stingerProximityDetonate( player, missileTeam )
{
	self endon ( "death" );
	
	if ( isDefined( level.ac130player ) )
		level.ac130player playLocalSound( "missile_incoming" );

	level.ac130.incomingMissile = true;

	missileTarget = level.ac130.planeModel;

	self Missile_SetTargetEnt( missileTarget );
	
	didSeatbelts = false;
	center = missileTarget GetPointInBounds( 0, 0, 0 );
	minDist = distance( self.origin, center );
	
	lastVecToTarget = vectorNormalize( center - self.origin );

	for ( ;; )
	{		
		if ( !isDefined( level.ac130player ) || ( isDefined( level.ac130.planeModel.crashed ) && level.ac130.planeModel.crashed == true ) )
		{
			self Missile_SetTargetPos( level.ac130.origin + (0,0,100000) );
			return;
		}
		
		center = missileTarget GetPointInBounds( 0, 0, 0 );
		
		curDist = distance( self.origin, center );
		
		if ( curDist < 3000 && missileTarget == level.ac130.planeModel && level.ac130.numFlares > 0 )
		{
			level.ac130.numFlares--;			

			newTarget = missileTarget deployFlares();
			
			self Missile_SetTargetEnt( newTarget );
			missileTarget = newTarget;
			
			if ( isDefined( level.ac130player ) )
				level.ac130player stopLocalSound( "missile_incoming" ); 
		
			return;
		}		
		
		if ( curDist < minDist )
		{
			speedPerFrame = (minDist - curDist) * 15;
			eta = (curDist / speedPerFrame);

			if ( eta < 1.5 && !didSeatbelts && missileTarget == level.ac130.planeModel )
			{	
				if ( isDefined( level.ac130player ) )
					level.ac130player playLocalSound( "fasten_seatbelts" );
					
				didSeatbelts = true;
			}
			
			minDist = curDist;
		}
		
		currVecToTarget = vectorNormalize( center - self.origin );
		if ( vectorDot( currVecToTarget, lastVecToTarget ) < 0 )
		{			
			if ( isDefined( level.ac130player ) )
			{
				level.ac130player stopLocalSound( "missile_incoming" ); 
				
				if ( level.ac130player.team != missileTeam )
					RadiusDamage( self.origin, 1000, 1000, 1000, player, "MOD_EXPLOSIVE", "stinger_mp" );
			}
			self hide();
			wait ( 0.05 );
			self delete();
		}
		else
			lastVecToTarget = currVecToTarget;
		
		wait ( 0.05 );
	}	
}

handleIncomingSAM()
{
	level endon ( "game_ended" );

	for ( ;; )
	{
		level waittill ( "sam_fired", player, missileGroup, lockTarget );

		if ( !IsDefined( lockTarget ) || (lockTarget != level.ac130.planeModel) )
			continue;

		level thread samProximityDetonate( player, player.team, missileGroup );
	}
}

samProximityDetonate( player, missileTeam, missileGroup )
{
	if ( isDefined( level.ac130player ) )
		level.ac130player playLocalSound( "missile_incoming" );

	level.ac130.incomingMissile = true;

	missileTarget = level.ac130.planeModel;

	didSeatbelts = false;
	minDist = [];
	center = missileTarget GetPointInBounds( 0, 0, 0 );
	for( i = 0; i < missileGroup.size; i++ )
	{
		if( IsDefined( missileGroup[ i ] ) )
		{
			minDist[ i ] = distance( missileGroup[ i ].origin, center );
			missileGroup[ i ].lastVecToTarget = vectorNormalize( center - missileGroup[ i ].origin );
		}
		else
			minDist[ i ] = undefined;
	}

	for ( ;; )
	{
		if ( !isDefined( level.ac130player ) || ( isDefined( level.ac130.planeModel.crashed ) && level.ac130.planeModel.crashed == true ) )
		{
			for( i = 0; i < missileGroup.size; i++ )					
			{
				if( IsDefined( missileGroup[ i ] ) )
				{
					missileGroup[ i ] Missile_SetTargetPos( level.ac130.origin + ( 0, 0, 100000 ) );
				}
			}
			return;
		}

		center = missileTarget GetPointInBounds( 0, 0, 0 );

		curDist = [];
		for( i = 0; i < missileGroup.size; i++ )
		{
			if( IsDefined( missileGroup[ i ] ) )
				curDist[ i ] = distance( missileGroup[ i ].origin, center );
		}

		if ( !isDefined( level.ac130player ) )
		{
			return;
		}

		for( i = 0; i < curDist.size; i++ )
		{
			if( IsDefined( curDist[ i ] ) )
			{
				// if one of the missiles in the group get close, set off flares and redirect them all
				if ( curDist[ i ] < 3000 && missileTarget == level.ac130.planeModel && level.ac130.numFlares > 0 )
				{
					level.ac130.numFlares--;			

					newTarget = missileTarget deployFlares();

					for( j = 0; j < missileGroup.size; j++ )					
					{
						if( IsDefined( missileGroup[ j ] ) )
						{
							missileGroup[ j ] Missile_SetTargetEnt( newTarget );
						}
					}

					if ( isDefined( level.ac130player ) )
						level.ac130player stopLocalSound( "missile_incoming" ); 

					return;
				}		

				if ( curDist[ i ] < minDist[ i ] )
				{
					speedPerFrame = ( minDist[ i ] - curDist[ i ] ) * 15;
					eta = ( curDist[ i ] / speedPerFrame );

					if ( eta < 1.5 && !didSeatbelts && missileTarget == level.ac130.planeModel )
					{	
						if ( isDefined( level.ac130player ) )
							level.ac130player playLocalSound( "fasten_seatbelts" );

						didSeatbelts = true;
					}

					minDist[ i ] = curDist[ i ];
				}

				currVecToTarget = vectorNormalize( center - missileGroup[ i ].origin );
				if ( vectorDot( currVecToTarget, missileGroup[ i ].lastVecToTarget ) < 0 )
				{
					if ( isDefined( level.ac130player ) )
					{
						level.ac130player stopLocalSound( "missile_incoming" ); 

						if ( level.teambased )
						{
							if( level.ac130player.team != missileTeam )
								RadiusDamage( missileGroup[ i ].origin, 1000, 1000, 1000, player, "MOD_EXPLOSIVE", "sam_projectile_mp" );
						}
						else
						{
							RadiusDamage( missileGroup[ i ].origin, 1000, 1000, 1000, player, "MOD_EXPLOSIVE", "sam_projectile_mp" );
						}
					}

					missileGroup[ i ] hide();

					wait ( 0.05 );
					missileGroup[ i ] delete();
				}
			}
		}

		wait ( 0.05 );
	}	
}


crashPlane( crashTime )
{
	level.ac130.planeModel notify ( "crashing" );
	level.ac130.planeModel.crashed = true;

	playFxOnTag( level._effect[ "ac130_explode" ], level.ac130.planeModel, "tag_deathfx" );	
	wait .25;

	level.ac130.planeModel hide();
}


playFlareFx( flareCount )
{	
	for ( i = 0; i < flareCount; i++ )
	{
		self thread angel_flare();

		wait ( randomFloatRange( 0.1, 0.25 ) );
	}
}


deployFlares( fxOnly )
{
	self playSound( "ac130_flare_burst" );
	
	if ( !isDefined( fxOnly ) )
	{
		flareObject = spawn( "script_origin", level.ac130.planemodel.origin );
		flareObject.angles = level.ac130.planemodel.angles;
	
		flareObject moveGravity( (0, 0, 0), 5.0 );

		self thread playFlareFx( 10 );
		
		flareObject thread deleteAfterTime( 5.0 );
	
		return flareObject;
	}
	else
	{
		self thread playFlareFx( 5 );
	}
}


angelFlarePrecache()
{
	precacheModel( "angel_flare_rig" );

	precacheMpAnim( "ac130_angel_flares01" );
	precacheMpAnim( "ac130_angel_flares02" );
	precacheMpAnim( "ac130_angel_flares03" );

	level._effect[ "angel_flare_geotrail" ]			= loadfx( "smoke/angel_flare_geotrail" );
	level._effect[ "angel_flare_swirl" ]			= loadfx( "smoke/angel_flare_swirl_runner" );
}

angel_flare()
{
	rig = spawn( "script_model", self.origin );
	rig setModel( "angel_flare_rig" );

	rig.origin = self getTagOrigin( "tag_flash_flares" );
	rig.angles = self getTagAngles( "tag_flash_flares" );

	rig.angles = (rig.angles[0],rig.angles[1] + 180,rig.angles[2] + -90);

	fx_id = level._effect[ "angel_flare_geotrail" ];

	rig ScriptModelPlayAnim( "ac130_angel_flares0" + (randomInt( 3 )+1) );

	wait 0.1;
	PlayFXOnTag( fx_id, rig, "flare_left_top" );
	PlayFXOnTag( fx_id, rig, "flare_right_top" );
	wait 0.05;
	PlayFXOnTag( fx_id, rig, "flare_left_bot" );
	PlayFXOnTag( fx_id, rig, "flare_right_bot" );

	//rig waittillmatch( "flare_anim", "end" );
	wait ( 3.0 );

	StopFXOnTag( fx_id, rig, "flare_left_top" );
	StopFXOnTag( fx_id, rig, "flare_right_top" );
	StopFXOnTag( fx_id, rig, "flare_left_bot" );
	StopFXOnTag( fx_id, rig, "flare_right_bot" );
	
	rig delete();
}

/*
#using_animtree( "script_model" );
angel_flare_rig_anims()
{
	level.scr_animtree[ "angel_flare_rig" ] 						= #animtree;
	level.scr_model[ "angel_flare_rig" ] 							= "angel_flare_rig";

	level.scr_anim[ "angel_flare_rig" ][ "ac130_angel_flares" ][0]	= %ac130_angel_flares01;
	level.scr_anim[ "angel_flare_rig" ][ "ac130_angel_flares" ][1]	= %ac130_angel_flares02;
	level.scr_anim[ "angel_flare_rig" ][ "ac130_angel_flares" ][2]	= %ac130_angel_flares03;

}

assign_model()
{
	AssertEx( IsDefined( level.scr_model[ self.animname ] ), "There is no level.scr_model for animname " + self.animname );

	if ( IsArray( level.scr_model[ self.animname ] ) )
	{
		randIndex = RandomInt( level.scr_model[ self.animname ].size );
		self SetModel( level.scr_model[ self.animname ][ randIndex ] );
	}
	else
		self SetModel( level.scr_model[ self.animname ] );
}
assign_animtree( animname )
{
	if ( IsDefined( animname ) )
		self.animname = animname;

	AssertEx( IsDefined( level.scr_animtree[ self.animname ] ), "There is no level.scr_animtree for animname " + self.animname );
	self UseAnimTree( level.scr_animtree[ self.animname ] );
}

spawn_anim_model( animname, origin )
{
	if ( !isdefined( origin ) )
		origin = ( 0, 0, 0 );
	model = Spawn( "script_model", origin );
	model.animname = animname;
	model assign_animtree();
	model assign_model();
	return model;
}


angel_flare_burst( flare_count )
{
	// Angel Flare Swirl
	PlayFXOnTag( getfx( "angel_flare_swirl" ), self, "tag_flash_flares" );

	// Angel Flare Trails
	for( i=0; i<flare_count; i++ )
	{
		self thread angel_flare();
		wait randomfloatrange( 0.1, 0.25 );
	}
}
*/
