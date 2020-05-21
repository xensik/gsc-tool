#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

UAV_REMOTE_FLY_TIME = 60;
UAV_REMOTE_AIM_ASSIST_RANGE = 200;
UAV_REMOTE_MAX_PAST_RANGE = 200;
UAV_REMOTE_MIN_HELI_PROXIMITY = 150;
UAV_REMOTE_MAX_HELI_PROXIMITY = 300;
UAV_REMOTE_PAST_RANGE_COUNTDOWN = 6;
UAV_REMOTE_HELI_RANGE_COUNTDOWN = 3;
UAV_REMOTE_COLLISION_RADIUS = 18;
UAV_REMOTE_Z_OFFSET = -9;

init()
{	
	//*precacheModel( "vehicle_remote_uav" );
	//*precacheModel( "test_vehicle_little_bird_toy_placement" );
	//*precacheModel( "test_vehicle_little_bird_toy_placement_failed" );
	
	//*precacheVehicle( "remote_uav_mp" );
	//*precacheItem( "uav_remote_mp" );
	//*precacheItem( "killstreak_remote_uav_mp" );
	
	//*precacheShader( "veh_hud_target" );
	//*precacheShader( "veh_hud_target_marked" );
	//*precacheShader( "compassping_sentry_enemy" );
	//*precacheShader( "compassping_enemy_uav" );
	//*precacheShader( "hud_fofbox_hostile_vehicle" );
	
	//*precacheRumble( "damage_light" );
	
	//*precacheString( &"MP_REMOTE_UAV_PLACE" );
	//*precacheString( &"MP_REMOTE_UAV_CANNOT_PLACE" );
	//*precacheString( &"SPLASHES_DESTROYED_REMOTE_UAV" );
	//*precacheString( &"SPLASHES_MARKED_BY_REMOTE_UAV" );
	//*precacheString( &"SPLASHES_REMOTE_UAV_MARKED" );
	//*precacheString( &"SPLASHES_TURRET_MARKED_BY_REMOTE_UAV" );
	//*precacheString( &"SPLASHES_REMOTE_UAV_ASSIST" );

	//*level.RemoteUAV_fx["hit"] = loadfx("impacts/large_metal_painted_hit");
	//*level.RemoteUAV_fx["smoke"] = loadfx( "smoke/remote_heli_damage_smoke_runner" );
	//*level.RemoteUAV_fx["explode"] = loadfx( "explosions/bouncing_betty_explosion" );
	//*level.RemoteUAV_fx["missile_explode"] = loadfx( "explosions/stinger_explosion" );	
	
	//*level.RemoteUAV_dialog["launch"][0] = "ac130_plt_yeahcleared";
	//*level.RemoteUAV_dialog["launch"][1] = "ac130_plt_rollinin";
	//*level.RemoteUAV_dialog["launch"][2] = "ac130_plt_scanrange";
	
	//*level.RemoteUAV_dialog["out_of_range"][0] = "ac130_plt_cleanup";
	//*level.RemoteUAV_dialog["out_of_range"][1] = "ac130_plt_targetreset";	
	
	//*level.RemoteUAV_dialog["track"][0] = "ac130_fco_moreenemy";
	//*level.RemoteUAV_dialog["track"][1] = "ac130_fco_getthatguy";
	//*level.RemoteUAV_dialog["track"][2] = "ac130_fco_guymovin";
	//*level.RemoteUAV_dialog["track"][3] = "ac130_fco_getperson";
	//*level.RemoteUAV_dialog["track"][4] = "ac130_fco_guyrunnin";
	//*level.RemoteUAV_dialog["track"][5] = "ac130_fco_gotarunner";
	//*level.RemoteUAV_dialog["track"][6] = "ac130_fco_backonthose";
	//*level.RemoteUAV_dialog["track"][7] = "ac130_fco_gonnagethim";
	//*level.RemoteUAV_dialog["track"][8] = "ac130_fco_personnelthere";
	//*level.RemoteUAV_dialog["track"][9] = "ac130_fco_rightthere";
	//*level.RemoteUAV_dialog["track"][10] = "ac130_fco_tracking";

	//*level.RemoteUAV_dialog["tag"][0] = "ac130_fco_nice";
	//*level.RemoteUAV_dialog["tag"][1] = "ac130_fco_yougothim";
	//*level.RemoteUAV_dialog["tag"][2] = "ac130_fco_yougothim2";
	//*level.RemoteUAV_dialog["tag"][3] = "ac130_fco_okyougothim";	
	
	//*level.RemoteUAV_dialog["assist"][0] = "ac130_fco_goodkill";
	//*level.RemoteUAV_dialog["assist"][1] = "ac130_fco_thatsahit";
	//*level.RemoteUAV_dialog["assist"][2] = "ac130_fco_directhit";
	//*level.RemoteUAV_dialog["assist"][3] = "ac130_fco_rightontarget";
	
	//*level.RemoteUAV_lastDialogTime = 0;
	
	level.RemoteUAV_noDeployZones = GetEntArray( "no_vehicles", "targetname" );

	//*level.killstreakFuncs["remote_uav"] = ::useRemoteUAV;
	
	level.remote_uav = [];	
/#
	SetDevDvarIfUninitialized( "scr_remoteUAVFlyTime", 60 );
#/
}	


useRemoteUAV( lifeId )
{
	return tryUseRemoteUAV( lifeId, "remote_uav" );
}


tryUseRemoteUAV( lifeId, streakName )
{ 
	if ( self isUsingRemote() || isDefined( level.nukeIncoming ) )
	{
		return false;
	}	
	
	numIncomingVehicles = 1;
	if ( isDefined( level.remote_uav[self.team] ) || level.littleBirds.size >= 4 )
	{
		self iPrintLnBold( &"MP_AIR_SPACE_TOO_CROWDED" );
		return false;
	}		
	else if( currentActiveVehicleCount() >= maxVehiclesAllowed() || level.fauxVehicleCount + numIncomingVehicles >= maxVehiclesAllowed() )
	{
		self iPrintLnBold( &"MP_TOO_MANY_VEHICLES" );
		return false;
	}		
	
	//	ui vars		
	self setPlayerData( "reconDroneState", "staticAlpha", 0 );
	self setPlayerData( "reconDroneState", "incomingMissile", false );	
		
	// increment the faux vehicle count before we spawn the vehicle so no other vehicles try to spawn
	incrementFauxVehicleCount();

	result = self giveCarryRemoteUAV( lifeId, streakName );
	if ( result )
	{
		self maps\mp\_matchdata::logKillstreakEvent( streakName, self.origin );
		self thread teamPlayerCardSplash( "used_remote_uav", self );
	}
	else
	{
		// decrement the faux vehicle count since this failed to spawn
		decrementFauxVehicleCount();
	}
	
	self.isCarrying = false;
	return ( result );
}


giveCarryRemoteUAV( lifeId, streakName )
{
	//	create carry object
	carryRemoteUAV = createCarryRemoteUAV( streakName, self );	
	
	//	get rid of clicker and give hand model
	self takeWeapon( "killstreak_uav_mp" );
	self _giveWeapon( "killstreak_remote_uav_mp" );
	self SwitchToWeaponImmediate( "killstreak_remote_uav_mp" );		
	
	//	give carry object and wait for placement (blocking loop)
	self setCarryingRemoteUAV( carryRemoteUAV );
	
	//	we're back, what happened?
	if ( isAlive( self ) && isDefined( carryRemoteUAV ) )
	{		
		//	if it placed, start the killstreak at that location
		origin = carryRemoteUAV.origin;
		angles = self.angles;
		carryRemoteUAV delete();		
		
		result = self startRemoteUAV( lifeId, streakName, origin, angles );		
	}	
	else
	{
		//	cancelled placement or died
		result = false;
		if ( isAlive( self ) )
		{							
			//	get rid of hand model
			self takeWeapon( "killstreak_remote_uav_mp" );
			
			//	give back the clicker to be able to active killstreak again
			self _giveWeapon( "killstreak_uav_mp" );		
		}	
	}
	
	return result;
}


//	Carry Remote UAV


createCarryRemoteUAV( streakName, owner )
{
	pos = owner.origin + ( anglesToForward( owner.angles ) * 4 ) + ( anglesToUp( owner.angles ) * 50 );	

	carryRemoteUAV = spawnTurret( "misc_turret", pos, "sentry_minigun_mp" );
	carryRemoteUAV.angles = owner.angles;	
	
	carryRemoteUAV.sentryType = "sentry_minigun";
	carryRemoteUAV.canBePlaced = true;
	carryRemoteUAV setTurretModeChangeWait( true );
	carryRemoteUAV setMode( "sentry_offline" );
	carryRemoteUAV makeUnusable();	
	carryRemoteUAV makeTurretInoperable();
	carryRemoteUAV.owner = owner;
	carryRemoteUAV SetSentryOwner( carryRemoteUAV.owner );
	carryRemoteUAV.scale = 3;
	carryRemoteUAV.inHeliProximity = false;

	carryRemoteUAV thread carryRemoteUAV_handleExistence();
	
	carryRemoteUAV.rangeTrigger = GetEnt( "remote_uav_range", "targetname" );
	if ( !isDefined( carryRemoteUAV.rangeTrigger ) )
	{
		heightEnt = GetEnt( "airstrikeheight", "targetname" );
		carryRemoteUAV.maxHeight = heightEnt.origin[2];
		carryRemoteUAV.maxDistance = 3600;		
	}	
	
	//	none of these do anything, no warning, error, or sound
	//carryRemoteUAV playLoopSound( "recondrone_idle_low" );
	//carryRemoteUAV playLoopSound( "recondrone_eng_low" );
	//carryRemoteUAV playLoopSound( "recondrone_idle_high" );
	//carryRemoteUAV playLoopSound( "recondrone_eng_high" );

	return carryRemoteUAV;	
}


setCarryingRemoteUAV( carryRemoteUAV )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	
	carryRemoteUAV thread carryRemoteUAV_setCarried( self );		

	self notifyOnPlayerCommand( "place_carryRemoteUAV", "+attack" );
	self notifyOnPlayerCommand( "place_carryRemoteUAV", "+attack_akimbo_accessible" ); // support accessibility control scheme
	self notifyOnPlayerCommand( "cancel_carryRemoteUAV", "+actionslot 4" );
	
	for ( ;; )
	{
		result = waittill_any_return( "place_carryRemoteUAV", "cancel_carryRemoteUAV", "weapon_switch_started" );

		self forceUseHintOff();
		
		if ( result != "place_carryRemoteUAV" )
		{							
			self.isCarrying = false;	
			carryRemoteUAV delete();		
			break;
		}

		if ( !carryRemoteUAV.canBePlaced )
		{
			if ( self.team != "spectator" )
				self ForceUseHintOn( &"MP_REMOTE_UAV_CANNOT_PLACE" );
			continue;	
		}					
		
		if( isDefined( level.nukeIncoming ) || 
			self isEMPed() || 
			isDefined( level.remote_uav[self.team] ) || 
			currentActiveVehicleCount() >= maxVehiclesAllowed() || 
			level.fauxVehicleCount >= maxVehiclesAllowed() )
		{
			if ( isDefined( level.nukeIncoming ) || self isEMPed() )
				self iPrintLnBold( &"MP_UNAVAILABLE_FOR_N_WHEN_EMP", level.empTimeRemaining );
			else
				self iPrintLnBold( &"MP_TOO_MANY_VEHICLES" );
			self.isCarrying = false;	
			carryRemoteUAV delete();		
			break;
		}		

		self.isCarrying = false;
		carryRemoteUAV.carriedBy = undefined;		
	
		carryRemoteUAV playSound( "sentry_gun_plant" );	
		carryRemoteUAV notify ( "placed" );		
		break;
	}
}


carryRemoteUAV_setCarried( carrier )
{
	self setCanDamage( false );
	self setSentryCarrier( carrier );
	self setContents( 0 );

	self.carriedBy = carrier;
	carrier.isCarrying = true;

	carrier thread updateCarryRemoteUAVPlacement( self );
	self notify ( "carried" );	
}


isInRemoteNoDeploy()
{
	if ( isDefined( level.RemoteUAV_noDeployZones ) && level.RemoteUAV_noDeployZones.size )
	{
		foreach( zone in level.RemoteUAV_noDeployZones )
		{
			if ( self isTouching( zone ) )
				return true;
		}
	}
	return false;
}


updateCarryRemoteUAVPlacement( carryRemoteUAV )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	carryRemoteUAV endon ( "placed" );
	carryRemoteUAV endon ( "death" );
	
	carryRemoteUAV.canBePlaced = true;
	lastCanPlaceCarryRemoteUAV = -1; // force initial update

	for( ;; )
	{		
		heightOffset = UAV_REMOTE_COLLISION_RADIUS;
		switch( self getStance() )
		{
			case "stand":
				heightOffset = 40;
				break;
			case "crouch":
				heightOffset = 25;
				break;
			case "prone":
				heightOffset = 10;
				break;
		}
		
		placement = self CanPlayerPlaceTank( 22, 22, 50, heightOffset, 0, 0 );
		carryRemoteUAV.origin = placement[ "origin" ] + ( anglesToUp(self.angles) * ( UAV_REMOTE_COLLISION_RADIUS - UAV_REMOTE_Z_OFFSET ) );
		carryRemoteUAV.angles = placement[ "angles" ];		
		carryRemoteUAV.canBePlaced = self isOnGround() && placement[ "result" ] && carryRemoteUAV remoteUAV_in_range() && !carryRemoteUAV isInRemoteNoDeploy();			
	
		if ( carryRemoteUAV.canBePlaced != lastCanPlaceCarryRemoteUAV )
		{
			if ( carryRemoteUAV.canBePlaced )
			{
				if ( self.team != "spectator" )
					self ForceUseHintOn( &"MP_REMOTE_UAV_PLACE" );
				
				//	if they're holding it in launch position just launch now
				if ( self attackButtonPressed() )
					self notify( "place_carryRemoteUAV" );				
			}
			else
			{
				if ( self.team != "spectator" )
					self ForceUseHintOn( &"MP_REMOTE_UAV_CANNOT_PLACE" );
			}
		}
		
		lastCanPlaceCarryRemoteUAV = carryRemoteUAV.canBePlaced;		
		wait ( 0.05 );
	}
}


carryRemoteUAV_handleExistence()
{
	level endon ( "game_ended" );
	self.owner endon ( "place_carryRemoteUAV" );
	self.owner endon ( "cancel_carryRemoteUAV" );

	self.owner waittill_any( "death", "disconnect", "joined_team", "joined_spectators" );

	if ( isDefined( self ) )
	{
		//	can't see viewmodel heli in player's hand from other player's perspective so no point blowing it up
		//playFX( level.RemoteUAV_fx["explode"], self.origin );		
		self delete();
	}
}


//	Remote UAV


removeRemoteWeapon()
{
	level endon( "game_ended" );
	self endon ( "disconnect" );
	
	wait(0.7);
	
}


startRemoteUAV( lifeId, streakName, origin, angles )
{		
	self lockPlayerForRemoteUAVLaunch();
	self setUsingRemote( streakName );
	
	self _giveWeapon("uav_remote_mp");
	self SwitchToWeaponImmediate("uav_remote_mp");	
	self VisionSetNakedForPlayer( "black_bw", 0.0 );	
	result = self maps\mp\killstreaks\_killstreaks::initRideKillstreak( "remote_uav" );		
	
	if ( result != "success" )
	{
		if ( result != "disconnect" )
		{
			self notify( "remoteuav_unlock" );
			self takeWeapon("uav_remote_mp");
			self clearUsingRemote();
		}
		return false;
	}	
	
	if( isDefined( level.remote_uav[self.team] ) || 
		currentActiveVehicleCount() >= maxVehiclesAllowed() || 
		level.fauxVehicleCount >= maxVehiclesAllowed() )
	{
		self iPrintLnBold( &"MP_TOO_MANY_VEHICLES" );
		self notify( "remoteuav_unlock" );
		self takeWeapon("uav_remote_mp");
		self clearUsingRemote();
		return false;
	}		

	self notify( "remoteuav_unlock" );
	remoteUAV = createRemoteUAV( lifeId, self, streakName, origin, angles );
	if ( isDefined( remoteUAV ) )
	{
		self thread remoteUAV_Ride( lifeId, remoteUAV, streakName );
		return true;
	}
	else
	{
		self iPrintLnBold( &"MP_TOO_MANY_VEHICLES" );
		self takeWeapon("uav_remote_mp");
		self clearUsingRemote();
		return false;	
	}		
}


remoteUAV_clearRideIntro()
{
	if ( IsDefined( level.nukeDetonated ) )
		self VisionSetNakedForPlayer( level.nukeVisionSet, 0 );
	else
		self VisionSetNakedForPlayer( "", 0 ); // go to default visionset	
}


lockPlayerForRemoteUAVLaunch()
{
	//	lock
	lockSpot = spawn( "script_origin", self.origin );
	lockSpot hide();	
	self playerLinkTo( lockSpot );	
	
	//	wait for unlock
	self thread clearPlayerLockFromRemoteUAVLaunch( lockSpot );
}


clearPlayerLockFromRemoteUAVLaunch( lockSpot )
{
	level endon( "game_ended" );
	
	msg = self waittill_any_return( "disconnect", "death", "remoteuav_unlock" );
	
	//	do unlock stuff
	if ( msg != "disconnect" )
		self unlink();
	lockSpot delete();
}


createRemoteUAV( lifeId, owner, streakName, origin, angles )
{
	remoteUAV = spawnHelicopter( owner, origin, angles, "remote_uav_mp", "vehicle_remote_uav" );	
	if ( !isDefined( remoteUAV ) )
		return undefined;
	
	remoteUAV maps\mp\killstreaks\_helicopter::addToLittleBirdList();
	remoteUAV thread maps\mp\killstreaks\_helicopter::removeFromLittleBirdListOnDeath();

	//radius and offset should match vehHelicopterBoundsRadius (GDT) and bg_vehicle_sphere_bounds_offset_z.
	remoteUAV MakeVehicleSolidCapsule( UAV_REMOTE_COLLISION_RADIUS, UAV_REMOTE_Z_OFFSET, UAV_REMOTE_COLLISION_RADIUS ); 
		
	remoteUAV.lifeId = lifeId;
	remoteUAV.team = owner.team;
	remoteUAV.pers["team"] = owner.team;	
	remoteUAV.owner = owner;

	remoteUAV.health = 999999; // keep it from dying anywhere in code
	remoteUAV.maxHealth = 250; // this is the health we'll check
	remoteUAV.damageTaken = 0;	
	remoteUAV.destroyed = false;
	remoteUAV setCanDamage( true );
	remoteUAV.specialDamageCallback = ::Callback_VehicleDamage;
	
	//	scrambler
	remoteUAV.scrambler = spawn( "script_model", origin );
	remoteUAV.scrambler linkTo( remoteUAV, "tag_origin", (0,0,-160), (0,0,0) );
	remoteUAV.scrambler makeScrambler( owner );
	
	remoteUAV.smoking = false;
	remoteUAV.inHeliProximity = false;		
	remoteUAV.heliType = "remote_uav";	
	remoteUAV.markedPlayers = [];
		
	remoteUAV thread remoteUAV_light_fx();
	remoteUAV thread remoteUAV_explode_on_disconnect();
	remoteUAV thread remoteUAV_explode_on_changeTeams();
	remoteUAV thread remoteUAV_explode_on_death();
	remoteUAV thread remoteUAV_clear_marked_on_gameEnded();
	remoteUAV thread remoteUAV_leave_on_timeout();
	remoteUAV thread remoteUAV_watch_distance();
	remoteUAV thread remoteUAV_watchHeliProximity();	
	remoteUAV thread remoteUAV_handleDamage();
	
	remoteUAV.numFlares = 2;
	remoteUAV.hasIncoming = false;
	remoteUAV.incomingMissiles = [];	
	remoteUAV thread remoteUAV_clearIncomingWarning();
	remoteUAV thread remoteUAV_handleIncomingStinger();
	remoteUAV thread remoteUAV_handleIncomingSAM();
	
	level.remote_uav[remoteUAV.team] = remoteUAV;
	return remoteUAV;
}


remoteUAV_ride( lifeId, remoteUAV, streakName )
{		
	remoteUAV.playerLinked = true;
	self.restoreAngles = self.angles;
	
	if ( getDvarInt( "camera_thirdPerson" ) )
		self setThirdPersonDOF( false );	
		
	if( self isJuggernaut() )
		self.juggernautOverlay.alpha = 0;		
	
	self CameraLinkTo( remoteUAV, "tag_origin" );	
	self RemoteControlVehicle( remoteUAV );	
	
	self thread remoteUAV_playerExit( remoteUAV );
	self thread remoteUAV_Track( remoteUAV );
	self thread remoteUAV_Fire( remoteUAV );
	//self thread remoteUAV_operationRumble( remoteUAV );

	self.remote_uav_rideLifeId = lifeId;
	self.remoteUAV = remoteUAV;
	
	self thread remoteUAV_delayLaunchDialog( remoteUAV );
	
	self VisionSetNakedForPlayer( "black_bw", 0.0 );
	if ( IsDefined( level.nukeDetonated ) )
		self VisionSetNakedForPlayer( level.nukeVisionSet, 1 );
	else
		self VisionSetNakedForPlayer( "", 1 ); // go to default visionset	
	
}


remoteUAV_delayLaunchDialog( remoteUAV )
{
	level endon( "game_ended" );
	self endon ( "disconnect" );
	remoteUAV endon ( "death" );
	remoteUAV endon ( "end_remote" );
	remoteUAV endon ( "end_launch_dialog" );	
	
	wait( 3 );
	self remoteUAV_dialog( "launch" );
}


remoteUAV_endride( remoteUAV )
{
	if ( isDefined( remoteUAV ) )
	{		
		remoteUAV.playerLinked = false;
		
		remoteUAV notify( "end_remote" );
		
		self clearUsingRemote();
		
		if ( getDvarInt( "camera_thirdPerson" ) )
			self setThirdPersonDOF( true );			
			
		if( self isJuggernaut() )
			self.juggernautOverlay.alpha = 1;				
		
		self CameraUnlink( remoteUAV );
		self RemoteControlVehicleOff( remoteUAV );
		
		self ThermalVisionOff();
		
		self setPlayerAngles( self.restoreAngles );	
		
		self switchToWeapon( self getLastWeapon() );
		self TakeWeapon( "uav_remote_mp" );
			
		self thread remoteUAV_freezeBuffer();
	}
	self.remoteUAV = undefined;
}


remoteUAV_freezeBuffer()
{
	self endon( "disconnect" );
	self endon( "death" );
	level endon( "game_ended" );
	
	self freezeControlsWrapper( true );
	wait( 0.5 );
	self freezeControlsWrapper( false );
}


remoteUAV_playerExit( remoteUAV )
{
	level endon( "game_ended" );
	self endon ( "disconnect" );
	remoteUAV endon ( "death" );
	remoteUAV endon ( "end_remote" );
	
	//	delay exit for transition into remote
	wait( 2 );
	
	while( true )
	{
		timeUsed = 0;
		while(	self UseButtonPressed() )
		{	
			timeUsed += 0.066;
			if( timeUsed > 0.75 )
			{	
				remoteUAV thread remoteUAV_leave();
				return;
			}
			wait( 0.05 );
		}
		wait( 0.05 );
	}
}


remoteUAV_Track( remoteUAV )
{
	level endon ( "game_ended" );
	self endon ( "disconnect" );
	remoteUAV endon ( "death" );
	remoteUAV endon ( "end_remote" );	
	
	remoteUAV.lastTrackingDialogTime = 0;
	
	self.lockedTarget = undefined;
	self weaponLockFree();
	
	//	finish transitioning into remote
	wait( 1 );
	
	//	now loop and track
	while( true )
	{		
		//	aim assist 'lock on' target for radius check
		pos = remoteUAV getTagOrigin( "tag_turret" );		
		forward = anglesToForward( self getPlayerAngles() );
		endpos = pos + forward * 1024;				
		trace = bulletTrace( pos, endpos, true, remoteUAV );
		if ( isDefined( trace["position"] ) )
			targetPos = trace["position"];
		else
		{
			targetPos = endpos;		
			trace["endpos"] = endpos;
		}
		remoteUAV.trace = trace;
				
		//	track all targetable entities, update head icons, check lock-on
		lockedPlayer = self remoteUAV_trackEntities( remoteUAV, level.players, targetPos );
		lockedTurret = self remoteUAV_trackEntities( remoteUAV, level.turrets, targetPos );
		lockedUAV = undefined;
		if ( level.teamBased )
			lockedUAV = self remoteUAV_trackEntities( remoteUAV, level.uavmodels[level.otherTeam[self.team]], targetPos );
		else
			lockedUAV = self remoteUAV_trackEntities( remoteUAV, level.uavmodels, targetPos );
		
		lockedTarget = undefined;
		if ( isDefined( lockedPlayer ) )
			lockedTarget = lockedPlayer;
		else if ( isDefined( lockedTurret ) )
			lockedTarget = lockedTurret;
		else if ( isDefined( lockedUAV ) )
			lockedTarget = lockedUAV;

		if ( isDefined( lockedTarget ) )
		{
			if ( !isDefined( self.lockedTarget ) || ( isDefined( self.lockedTarget ) && self.lockedTarget != lockedTarget ) )
			{			
				self weaponLockFinalize( lockedTarget );
				self.lockedTarget = lockedTarget;
				
				//	do vo for players
				if ( isDefined( lockedPlayer ) )
				{
					//	cancels the launch dialog delay if we get a target before then
					remoteUAV notify( "end_launch_dialog" );
					self remoteUAV_dialog( "track" );					
				}
			}
		}		
		else
		{
			self weaponLockFree();
			self.lockedTarget = undefined;
		}
		
		wait( 0.05 );	
	}	
}


remoteUAV_trackEntities( remoteUAV, entities, targetPos )
{
	level endon( "game_ended" );
	
	lockedTarget = undefined;
	foreach ( entity in entities )
	{
		if ( level.teamBased && entity.team == self.team )
			continue;
			
		if ( isPlayer( entity ) )
		{
			if ( !isAlive( entity ) )
				continue;
			
			if ( entity == self )
				continue;	
				
			id = entity.guid;	
		}
		else
			id = entity.birthtime;
			
		//	offset
		if ( isDefined( entity.sentryType ) || isDefined( entity.turretType ) )
		{
			offset = (0,0,32);
			unmarkedShader = "hud_fofbox_hostile_vehicle";
		}
		else if ( isDefined( entity.uavType ) )
		{
			offset = (0,0,-52);
			unmarkedShader = "hud_fofbox_hostile_vehicle";
		}
		else
		{
			offset = (0,0,26);
			unmarkedShader = "veh_hud_target_unmarked";
		}
	
		//	already marked
		if ( isDefined( entity.UAVRemoteMarkedBy ) )
		{
			//	marked, but no headicon yet
			if ( !isDefined( remoteUAV.markedPlayers[id] ) )
			{
				remoteUAV.markedPlayers[id] = [];		
				remoteUAV.markedPlayers[id]["player"] = entity;
				remoteUAV.markedPlayers[id]["icon"] = entity maps\mp\_entityheadIcons::setHeadIcon( self, "veh_hud_target_marked", offset, 10, 10, false, 0.05, false, false, false, false );		
				remoteUAV.markedPlayers[id]["icon"].shader = "veh_hud_target_marked";
				
				if ( !isDefined( entity.sentryType ) || !isDefined( entity.turretType ) )
					remoteUAV.markedPlayers[id]["icon"] SetTargetEnt( entity );			
			}
			//	headicon hasn't been switched to marked yet
			else if ( isDefined( remoteUAV.markedPlayers[id] ) && isDefined( remoteUAV.markedPlayers[id]["icon"] ) && isDefined( remoteUAV.markedPlayers[id]["icon"].shader ) && remoteUAV.markedPlayers[id]["icon"].shader != "veh_hud_target_marked" )
			{
				remoteUAV.markedPlayers[id]["icon"].shader = "veh_hud_target_marked";
				remoteUAV.markedPlayers[id]["icon"] setShader( "veh_hud_target_marked", 10, 10 );
				remoteUAV.markedPlayers[id]["icon"] setWaypoint( false, false, false, false );				
			}
		}
		//	not marked yet
		else 
		{
			//	exceptions
			if ( isPlayer( entity ) )
			{
				spawnProtected = ( isDefined( entity.spawntime ) && ( getTime() - entity.spawntime )/1000 <= 5 );
				hudTargetProtected = entity _hasPerk( "specialty_blindeye" );
				carried = false;
				leaving = false;
			}
			else
			{
				spawnProtected = false;
				hudTargetProtected = false;
				carried = isDefined( entity.carriedBy );
				leaving = ( isDefined( entity.isLeaving ) && entity.isLeaving == true );
			}
			
			//	no headicon yet
			if ( !isDefined( remoteUAV.markedPlayers[id] ) && !spawnProtected && !hudTargetProtected && !carried && !leaving )					 
			{
				remoteUAV.markedPlayers[id] = [];		
				remoteUAV.markedPlayers[id]["player"] = entity;
				remoteUAV.markedPlayers[id]["icon"] = entity maps\mp\_entityheadIcons::setHeadIcon( self, unmarkedShader, offset, 10, 10, false, 0.05, false, false, false, false );
				remoteUAV.markedPlayers[id]["icon"].shader = unmarkedShader;	
				
				if ( !isDefined( entity.sentryType ) || !isDefined( entity.turretType ) )
					remoteUAV.markedPlayers[id]["icon"] SetTargetEnt( entity );		
			}			
			
			//	lock on? (don't allow aim assist for spawn campers)
			if ( ( !isDefined( lockedTarget ) || lockedTarget != entity ) &&
				 ( isDefined( remoteUAV.trace["entity"] ) && remoteUAV.trace["entity"] == entity && !carried && !leaving ) || 
			     ( distance( entity.origin, targetPos ) < UAV_REMOTE_AIM_ASSIST_RANGE * remoteUAV.trace[ "fraction" ] && !spawnProtected && !carried && !leaving ) ||
			     ( !leaving && remoteUAV_canTargetUAV( remoteUAV, entity ) ) )
			{
				//	final check, make sure there is line of sight
				trace = bulletTrace( remoteUAV.origin, entity.origin + (0,0,32), true, remoteUAV );
				if ( ( isDefined( trace["entity"] ) && trace["entity"] == entity ) || trace["fraction"] == 1 )
				{
					self playLocalSound( "recondrone_lockon" );
					lockedTarget = entity;
				}				
			}	
		}
	}
	return lockedTarget;	
}


remoteUAV_canTargetUAV( remoteUAV, uav )
{
	//	lenient targeting for other uavs, just point in the correct direction and ignore range to keep players flying low
	if ( isDefined( uav.uavType ) )
	{
		forward = anglesToForward( self getPlayerAngles() );
		toUAV = vectorNormalize( uav.origin - remoteUAV getTagOrigin( "tag_turret" ) );
		dot = vectorDot( forward, toUAV );
		if ( dot > 0.985 )
			return true;
	}
	return false;
}


remoteUAV_Fire( remoteUAV )
{
	self endon ( "disconnect" );
	remoteUAV endon ( "death" );
	level endon ( "game_ended" );
	remoteUAV endon ( "end_remote" );	
	
	//	transition into remote
	wait( 1 );
	
	self notifyOnPlayerCommand( "remoteUAV_tag", "+attack" );
	self notifyOnPlayerCommand( "remoteUAV_tag", "+attack_akimbo_accessible" ); // support accessibility control scheme	
	
	while ( true )
	{		
		self waittill( "remoteUAV_tag" ); 
		
		if ( isDefined( self.lockedTarget ) )
		{
			self playLocalSound( "recondrone_tag" );
			
			//	hit FX
			self maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "" );
			//	mark target
			self thread remoteUAV_markPlayer( self.lockedTarget );
			//	feedback
			self thread remoteUAV_Rumble( remoteUAV, 3 );
			
			wait( 0.25 );			
		}
		else
		{
			wait( 0.05 );	
		}		
	}
}


remoteUAV_Rumble( remoteUAV, amount )
{
	self      endon ( "disconnect" );
	remoteUAV endon ( "death" );
	level     endon ( "game_ended" );
	remoteUAV endon ( "end_remote" );
	remoteUAV notify( "end_rumble" );
	remoteUAV endon ( "end_rumble" );
	
	for( i=0; i<amount; i++ )
	{
		self playRumbleOnEntity( "damage_heavy" );
		wait( 0.05 );
	}	
}


remoteUAV_markPlayer( targetPlayer )
{	
	level endon( "game_ended" );
	
	//	set the target player as marked by RC driver
	targetPlayer.UAVRemoteMarkedBy = self;
		
	//	hit and notify target player
	if ( isPlayer( targetPlayer ) && !targetPlayer isUsingRemote() )
	{
		targetPlayer playLocalSound( "player_hit_while_ads_hurt" );
		targetPlayer thread maps\mp\_flashgrenades::applyFlash(2.0, 1.0);
		targetPlayer thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_MARKED_BY_REMOTE_UAV" );
	}
	//	hack for uav, removed entity on death has no .birthtime
	else if ( isDefined( targetPlayer.uavType ) )
	{
		targetPlayer.birth_time = targetPlayer.birthtime; 
	}
	//	turret, notify owner
	else if ( isDefined( targetPlayer.owner ) && isAlive( targetPlayer.owner ) )
	{
		targetPlayer.owner thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_TURRET_MARKED_BY_REMOTE_UAV" );
	}	
	
	//	notify operator
	//self.remoteUAV playSound( "mp_suitcase_pickup" );
	self remoteUAV_dialog( "tag" );
	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_REMOTE_UAV_MARKED" );
	maps\mp\gametypes\_gamescore::givePlayerScore( "kill", self, undefined, true );
	self thread maps\mp\gametypes\_rank::giveRankXP( "kill" );
	
	//	put em on the minimap	
	if ( isPlayer( targetPlayer ) )
		targetPlayer setPerk( "specialty_radarblip", true, false );
	else
	{
		if ( isDefined( targetPlayer.uavType ) )
			shaderName = "compassping_enemy_uav";
		else
			shaderName = "compassping_sentry_enemy";
		if ( level.teamBased )
		{
			curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
			objective_add( curObjID, "invisible", (0,0,0) );
			objective_OnEntity( curObjID, targetPlayer );
			objective_state( curObjID, "active" );
			objective_team( curObjID, self.team );
			objective_icon( curObjID, shaderName );
			targetPlayer.remoteUAVMarkedObjID01 = curObjID;
		}
		else
		{
			curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
			objective_add( curObjID, "invisible", (0,0,0) );
			objective_OnEntity( curObjID, targetPlayer );
			objective_state( curObjID, "active" );
			objective_team( curObjID, level.otherTeam[self.team] );
			objective_icon( curObjID, shaderName );
			targetPlayer.remoteUAVMarkedObjID02 = curObjID;
			
			curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
			objective_add( curObjID, "invisible", (0,0,0) );
			objective_OnEntity( curObjID, targetPlayer );
			objective_state( curObjID, "active" );
			objective_team( curObjID, self.team );
			objective_icon( curObjID, shaderName );
			targetPlayer.remoteUAVMarkedObjID03 = curObjID;
		}	
	}
	
	
	//	track their existence to remove from marked players list and minimap
	targetPlayer thread remoteUAV_unmarkRemovedPlayer( self.remoteUAV );
}


remoteUAV_processTaggedAssist( victim )
{
	self remoteUAV_dialog( "assist" );
	self thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_REMOTE_UAV_ASSIST" );
	if ( isDefined( victim ) )
		self thread maps\mp\gametypes\_gamescore::processAssist( victim );	
	else
	{
		maps\mp\gametypes\_gamescore::givePlayerScore( "assist", self, victim, true );
		self thread maps\mp\gametypes\_rank::giveRankXP( "assist" );		
	}
}


remoteUAV_unmarkRemovedPlayer( remoteUAV )
{
	level endon( "game_ended" );
	
	msg = self waittill_any_return( "death", "disconnect", "carried", "leaving" );
	
	//	hack for uavs
	if ( msg == "leaving" || !isDefined( self.uavType ) )
		self.UAVRemoteMarkedBy = undefined;
	if ( isDefined( remoteUAV ) )
	{
		if ( isPlayer( self ) )
			id = self.guid;
		else if ( isDefined( self.birthtime ) )
			id = self.birthtime;
		else
			id = self.birth_time; // hack for uav, removed entity on death has no .birthtime
				
		if ( msg == "carried" || msg == "leaving" )
		{
			remoteUAV.markedPlayers[id]["icon"] destroy();
			remoteUAV.markedPlayers[id]["icon"] = undefined;			
		}				
		if ( isDefined( id ) && isDefined( remoteUAV.markedPlayers[id] ) )
		{
			remoteUAV.markedPlayers[id] = undefined;
			remoteUAV.markedPlayers = array_removeUndefined( remoteUAV.markedPlayers );
		}
	}
	
	if ( isPlayer( self ) )
		self unsetPerk( "specialty_radarblip", true );
	else 
	{
		if( isDefined( self.remoteUAVMarkedObjID01 ) )
			_objective_delete( self.remoteUAVMarkedObjID01 );	
		if( isDefined( self.remoteUAVMarkedObjID02 ) )
			_objective_delete( self.remoteUAVMarkedObjID02 );	
		if( isDefined( self.remoteUAVMarkedObjID03 ) )
			_objective_delete( self.remoteUAVMarkedObjID03 );
	}
}


remoteUAV_clearMarkedForOwner()
{	
	foreach( markedPlayer in self.markedPlayers )
	{
		if ( isDefined( markedPlayer["icon"] ) )
		{
			markedPlayer["icon"] destroy();
			markedPlayer["icon"] = undefined;
		}	
	}
	self.markedPlayers = undefined;
}


remoteUAV_operationRumble( remoteUAV )
{
	self      endon ( "disconnect" );
	remoteUAV endon ( "death" );
	level     endon ( "game_ended" );
	remoteUAV endon ( "end_remote" );
	
	while( true )
	{
		//	JDS TODO: make a light, subtle buzzing
		self PlayRumbleOnEntity( "damage_light" );
		wait( 0.5 );
	}	
}


remoteUAV_watch_distance()
{
	self endon ("death" );
	
	//	script distance and airstrike height until in range triggers are created for levels
	self.rangeTrigger = GetEnt( "remote_uav_range", "targetname" );
	if ( !isDefined( self.rangeTrigger ) )
	{
		heightEnt = GetEnt( "airstrikeheight", "targetname" );
		self.maxHeight = heightEnt.origin[2];
		self.maxDistance = 12800;		
	}	

	//	ent to put headicon on for pointing to inside of map when they go out of range
	self.centerRef = Spawn( "script_model", level.mapCenter );
	
	//	shouldn't be possible to start out of range, but just in case
	inRangePos = self.origin;		
	
	self.rangeCountdownActive = false;
	
	//	loop
	while ( true )
	{
		if ( !self remoteUAV_in_range() )
		{
			//	increase static with distance from exit point or distance to heli in proximity
			staticAlpha = 0;		
			while ( !self remoteUAV_in_range() )
			{
				self.owner remoteUAV_dialog( "out_of_range" );
				if ( !self.rangeCountdownActive )
				{
					self.rangeCountdownActive = true;
					self thread remoteUAV_rangeCountdown();
				}
				if ( isDefined( self.heliInProximity ) )
				{
					dist = distance( self.origin, self.heliInProximity.origin );
					staticAlpha = 1 - ( (dist-UAV_REMOTE_MIN_HELI_PROXIMITY) / (UAV_REMOTE_MAX_HELI_PROXIMITY-UAV_REMOTE_MIN_HELI_PROXIMITY) );
				}
				else
				{
					dist = distance( self.origin, inRangePos );
					staticAlpha = min( 1, dist/UAV_REMOTE_MAX_PAST_RANGE );					
				}
				
				self.owner setPlayerData( "reconDroneState", "staticAlpha", staticAlpha );				
				
				wait ( 0.05 );
			}
			
			//	end countdown
			self notify( "in_range" );
			self.rangeCountdownActive = false;
			
			//	fade out static
			self thread remoteUAV_staticFade( staticAlpha );
		}		
		inRangePos = self.origin;
		wait ( 0.05 );
	}
}


remoteUAV_in_range()
{
	if ( isDefined( self.rangeTrigger ) )
	{
		if ( !self isTouching( self.rangeTrigger ) && !self.inHeliProximity )
			return true;
	}
	else
	{
		if ( distance2D( self.origin, level.mapCenter ) < self.maxDistance && self.origin[2] < self.maxHeight && !self.inHeliProximity )
			return true;
	}
	return false;
}


remoteUAV_staticFade( staticAlpha )
{
	self endon ( "death" );
	while( self remoteUAV_in_range() )
	{
		staticAlpha -= 0.066;
		if ( staticAlpha < 0 )
		{
			self.owner setPlayerData( "reconDroneState", "staticAlpha", 0 );
			break;
		}
		self.owner setPlayerData( "reconDroneState", "staticAlpha", staticAlpha );			
		
		wait( 0.05 );
	}
}


remoteUAV_rangeCountdown()
{
	self endon( "death" );
	self endon( "in_range" );
	
	if ( isDefined( self.heliInProximity ) )
		countdown = UAV_REMOTE_HELI_RANGE_COUNTDOWN;
	else
		countdown = UAV_REMOTE_PAST_RANGE_COUNTDOWN;
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( countdown );
	
	self notify( "death" );
}


remoteUAV_explode_on_disconnect()
{
	self endon ( "death" );	

	self.owner waittill( "disconnect" );
	
	self notify( "death" );
}


remoteUAV_explode_on_changeTeams()
{
	self endon ( "death" );	

	self.owner waittill_any( "joined_team", "joined_spectators" );
	
	self notify( "death" );
}


remoteUAV_clear_marked_on_gameEnded()
{
	self endon ( "death" );
	
	level waittill( "game_ended" );
	
	self remoteUAV_clearMarkedForOwner();
}


remoteUAV_leave_on_timeout()
{
	self endon ( "death" );	
	
	flyTime = 60.0;
/#
	flyTime = GetDvarInt( "scr_remoteUAVFlyTime", flyTime );
#/	
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( flyTime );
	
	self thread remoteUAV_leave();
}


remoteUAV_leave()
{
	level endon( "game_ended" );
	self endon( "death" );
	
	//	disengage player
	self notify( "leaving" );
	self.owner remoteUAV_endride( self );

	//	remove	
	self notify( "death" );
}


remoteUAV_explode_on_death()
{
	level endon( "game_ended" );
	
	self waittill( "death" );			
		
	self playSound( "recondrone_destroyed" );
	playFX( level.RemoteUAV_fx["explode"], self.origin );
	remoteUAV_cleanup();	
}


remoteUAV_cleanup()
{
	if ( self.playerLinked == true && isDefined( self.owner ) )
		self.owner remoteUAV_endride( self );		
		
	if ( isDefined( self.scrambler ) )
		self.scrambler delete();
		
	if ( isDefined( self.centerRef ) )
		self.centerRef delete();
	
	self remoteUAV_clearMarkedForOwner();
	
	stopFXOnTag( level.RemoteUAV_fx["smoke"], self, "tag_origin" );
	
	level.remote_uav[self.team] = undefined;
	self delete();	
}


remoteUAV_light_fx()
{
	playFXOnTag( level.chopper_fx["light"]["belly"], self, "tag_light_nose" );
	wait ( 0.05 );
	playFXOnTag( level.chopper_fx["light"]["tail"], self, "tag_light_tail1" );	
}


remoteUAV_dialog( dialogGroup )
{
	if ( dialogGroup == "tag" )
		waitTime = 1000;
	else
		waitTime = 5000;
	
	if ( getTime() - level.RemoteUAV_lastDialogTime < waitTime )
		return;
	
	level.RemoteUAV_lastDialogTime = getTime();
	
	randomIndex = randomInt( level.remoteUAV_dialog[ dialogGroup ].size );
	soundAlias = level.remoteUAV_dialog[ dialogGroup ][ randomIndex ];
	
	fullSoundAlias = maps\mp\gametypes\_teams::getTeamVoicePrefix( self.team ) + soundAlias;
	
	self playLocalSound( fullSoundAlias );
}


remoteUAV_handleIncomingStinger()
{
	level endon ( "game_ended" );
	self endon ( "death" );
	self endon ( "end_remote" );

	while ( true )
	{
		level waittill ( "stinger_fired", player, missile, lockTarget );
		
		if ( !IsDefined( lockTarget ) || (lockTarget != self) )
			continue;
		
		//	notify owner
		self.owner PlayLocalSound( "javelin_clu_lock" );
		self.owner setPlayerData( "reconDroneState", "incomingMissile", true );		
		self.hasIncoming = true;
		self.incomingMissiles[self.incomingMissiles.size] = missile;		
		
		//	track missile
		missile.owner = player;
		missile thread watchStingerProximity( lockTarget );
	}	
}


remoteUAV_handleIncomingSAM()
{
	level endon ( "game_ended" );
	self endon ( "death" );
	self endon ( "end_remote" );		

	while ( true )
	{
		level waittill ( "sam_fired", player, missileGroup, lockTarget );

		if ( !IsDefined( lockTarget ) || ( lockTarget != self ) )
			continue;
		
		//	notify owner
		self.owner PlayLocalSound( "javelin_clu_lock" );
		self.owner setPlayerData( "reconDroneState", "incomingMissile", true );	
		self.hasIncoming = true;
		foreach ( missile in missileGroup )
		{
			self.incomingMissiles[self.incomingMissiles.size] = missile;	
			missile.owner = player;
		}	
		
		//	track missile
		level thread watchSAMProximity( lockTarget, missileGroup );
	}
}


watchStingerProximity( missileTarget )
{
	level endon( "game_ended" );
	self endon ( "death" );
	
	self Missile_SetTargetEnt( missileTarget );

	lastVecToTarget = vectorNormalize( missileTarget.origin - self.origin );
	
	while( isDefined( missileTarget ) )
	{			
		center = missileTarget GetPointInBounds( 0, 0, 0 );
		curDist = distance( self.origin, center );

		//	flares?
		if ( missileTarget.numFlares > 0 && curDist < 4000 )
		{
			newTarget = missileTarget deployFlares();
			self Missile_SetTargetEnt( newTarget );	
			return;
		}
		//	still on target?
		else
		{
			curVecToTarget = vectorNormalize( missileTarget.origin - self.origin );
			if ( vectorDot( curVecToTarget, lastVecToTarget ) < 0 )
			{
				self playSound( "exp_stinger_armor_destroy" );
				playFX( level.RemoteUAV_fx["missile_explode"], self.origin );
				if ( isDefined( self.owner ) )
					RadiusDamage( self.origin, 400, 1000, 1000, self.owner, "MOD_EXPLOSIVE", "stinger_mp" );
				else
					RadiusDamage( self.origin, 400, 1000, 1000, undefined, "MOD_EXPLOSIVE", "stinger_mp" );
				self hide();
				wait ( 0.05 );
				self delete();
			}
			else
				lastVecToTarget = curVecToTarget;
		}			
			
		wait ( 0.05 );
	}	
}


watchSAMProximity( missileTarget, missileGroup )
{
	level endon ( "game_ended" );
	missileTarget endon( "death" );	

	foreach ( missile in missileGroup )
	{
		if ( isDefined( missile ) )
		{
			missile Missile_SetTargetEnt( missileTarget );
			missile.lastVecToTarget = vectorNormalize( missileTarget.origin - missile.origin );
		}
	}

	while( missileGroup.size && isDefined( missileTarget ) )
	{
		center = missileTarget GetPointInBounds( 0, 0, 0 );
		foreach ( missile in missileGroup )
		{
			if ( isDefined( missile ) )
			{
				if ( isDefined( self.markForDetete ) )
				{
					self delete();
					continue;
				}					
				
				//	flares?
				if ( missileTarget.numFlares > 0 )
				{
					distToTarget = distance( missile.origin, center );
					if ( distToTarget < 4000 )
					{
						newTarget = missileTarget deployFlares();
						foreach ( missileToRedirect in missileGroup )					
							if ( IsDefined( missileToRedirect ) )
								missileToRedirect Missile_SetTargetEnt( newTarget );
						return;						
					}					
				}
				//	still on target?
				else
				{
					curVecToTarget = vectorNormalize( missileTarget.origin - missile.origin );
					if ( vectorDot( curVecToTarget, missile.lastVecToTarget ) < 0 )
					{
						missile playSound( "exp_stinger_armor_destroy" );
						playFX( level.RemoteUAV_fx["missile_explode"], missile.origin );
						if ( isDefined( missile.owner ) )
							RadiusDamage( missile.origin, 400, 1000, 1000, missile.owner, "MOD_EXPLOSIVE", "stinger_mp" );
						else
							RadiusDamage( missile.origin, 400, 1000, 1000, undefined, "MOD_EXPLOSIVE", "stinger_mp" );
						missile hide();
						missile.markForDetete = true;					
					}
					else
						missile.lastVecToTarget = curVecToTarget;					
				}
			}
		}
		missileGroup = array_removeUndefined( missileGroup );
		
		wait ( 0.05 );
	}	
}


deployFlares()
{
	//	decrement
	self.numFlares--;
	
	//	player feedback
	self.owner thread remoteUAV_Rumble( self, 6 );	
	self playSound( "WEAP_SHOTGUNATTACH_FIRE_NPC" );	
	
	//	fx
	self thread playFlareFx();			
	
	//	flare
	spawnPos = self.origin + (0,0,-100);
	flareObject = spawn( "script_origin", spawnPos );
	flareObject.angles = self.angles;	
	flareObject moveGravity( (0,0,-1), 5.0 );	
	flareObject thread deleteAfterTime( 5.0 );

	return flareObject;
}


playFlareFx()
{
	for ( i = 0; i < 5; i++ )
	{
		if ( !isDefined( self ) )
			return;
		PlayFXOnTag( level._effect[ "ac130_flare" ], self, "TAG_FLARE" );
		wait ( 0.15 );
	}
}


deleteAfterTime( delay )
{
	wait ( delay );
	
	self delete();
}


remoteUAV_clearIncomingWarning()
{
	level endon ( "game_ended" );
	self endon ( "death" );
	self endon ( "end_remote" );	
	
	while( true )
	{		
		numIncoming = 0;
		for ( i=0; i<self.incomingMissiles.size; i++ )
		{
			if ( isDefined( self.incomingMissiles[i] ) && missile_isIncoming( self.incomingMissiles[i], self ) )
				numIncoming++;
		}		
		if ( self.hasIncoming && !numIncoming )
		{
			self.hasIncoming = false;
			self.owner setPlayerData( "reconDroneState", "incomingMissile", false );			
		}
		self.incomingMissiles = array_removeUndefined( self.incomingMissiles );
		wait( 0.05 );		
	}
}


missile_isIncoming( missile, remoteUAV )
{
	vecToRemote = vectorNormalize( remoteUAV.origin - missile.origin );
	vecToFacing = anglesToForward( missile.angles );
	
	return ( vectorDot( vecToRemote, vecToFacing ) > 0 );
}


remoteUAV_watchHeliProximity()
{
	level endon( "game_ended" );
	self  endon( "death" );
	self  endon( "end_remote" );
	
	while( true )
	{
		inHeliProximity = false;
		foreach( heli in level.helis )
		{
			if ( distance( heli.origin, self.origin ) < UAV_REMOTE_MAX_HELI_PROXIMITY )
			{
				inHeliProximity = true;
				self.heliInProximity = heli;
			}
		}
		foreach( littlebird in level.littleBirds )
		{
			if ( littlebird != self && ( !isDefined(littlebird.heliType) || littlebird.heliType != "remote_uav" ) && distance( littlebird.origin, self.origin ) < UAV_REMOTE_MAX_HELI_PROXIMITY )
			{
				inHeliProximity = true;
				self.heliInProximity = littlebird;	
			}
		}
		
		if ( !self.inHeliProximity && inHeliProximity )
			self.inHeliProximity = true;
		else if ( self.inHeliProximity && !inHeliProximity )
		{
			self.inHeliProximity = false;
			self.heliInProximity = undefined;
		}
		
		wait( 0.05 );
	}
}


remoteUAV_handleDamage() // self == heli
{
	level endon( "game_ended" );
	self  endon( "death" );
	self  endon( "end_remote" );

	while( true )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );

		if( IsDefined( self.specialDamageCallback ) )
			self [[self.specialDamageCallback]]( undefined, attacker, damage, iDFlags, meansOfDeath, weapon, point, direction_vec, undefined, undefined, modelName, partName );
	}
}


Callback_VehicleDamage( inflictor, attacker, damage, iDFlags, meansOfDeath, weapon, point, dir, hitLoc, timeOffset, modelIndex, partName )
{
	if ( self.destroyed == true )
		return;
		
	team = self.team;
	if ( isDefined( attacker.team ) )
		otherTeam = attacker.team;
	else
		otherTeam = "none";		
	
	//	allow owner but not team to damage
	if ( !isDefined( attacker ) || ( attacker != self.owner && level.teamBased && otherTeam == team ) )
		return;
		
	if ( IsDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
		self.wasDamagedFromBulletPenetration = true;

	modifiedDamage = damage;

	if ( isPlayer( attacker ) )
	{
		attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "remote_uav" );		

		if ( attacker _hasPerk( "specialty_armorpiercing" ) )
		{
			modifiedDamage = damage * level.armorPiercingMod;			
		}
	}
	
	// in case we are shooting from a remote position, like being in the osprey gunner shooting this
	if( IsDefined( attacker.owner ) && IsPlayer( attacker.owner ) )
	{
		attacker.owner maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "remote_uav" );
	}

	if( IsDefined( weapon ) )
	{
		switch( weapon )
		{
		case "ac130_105mm_mp":
		case "ac130_40mm_mp":
		case "stinger_mp":
		case "javelin_mp":
		case "remote_mortar_missile_mp":		
		case "remotemissile_projectile_mp":
			self.largeProjectileDamage = true;
			modifiedDamage = self.maxHealth + 1;
			break;

		case "bomb_site_mp":
		case "emp_grenade_mp":
			self.largeProjectileDamage = false;
			modifiedDamage = self.maxHealth + 1;
			break;
		}
	}
	
	if ( isDefined( meansOfDeath ) && meansOfDeath == "MOD_MELEE" )
	{
		modifiedDamage = self.maxHealth + 1;
	}

	self.damageTaken += modifiedDamage;		
	PlayFXOnTagForClients( level.RemoteUAV_fx["hit"], self, "tag_origin", self.owner );
	self playsound( "recondrone_damaged" );
	
	if ( self.smoking == false && self.damageTaken >= self.maxhealth/2 )
	{
		self.smoking = true;

		playFxOnTag( level.RemoteUAV_fx["smoke"], self, "tag_origin" );
		println( "Remote UAV at half health: starting smoke" );
	}
	
	if ( self.damageTaken >= self.maxhealth  && ( (level.teamBased && team != otherTeam) || !level.teamBased) )
	{
		self.destroyed = true;
		validAttacker = undefined;
		if ( isDefined( attacker.owner ) && (!isDefined(self.owner) || attacker.owner != self.owner) )
			validAttacker = attacker.owner;				
		else if ( !isDefined(self.owner) || attacker != self.owner )
			validAttacker = attacker;
			
		//	sanity checks	
		if ( !isDefined(attacker.owner) && attacker.classname == "script_vehicle" )
				validAttacker = undefined;
		if ( isDefined( attacker.class ) && attacker.class == "worldspawn" )
				validAttacker = undefined;	
		if ( attacker.classname == "trigger_hurt" )
				validAttacker = undefined;		

		if ( isDefined( validAttacker ) )
		{
			validAttacker notify( "destroyed_killstreak", weapon );
			thread teamPlayerCardSplash( "callout_destroyed_remote_uav", validAttacker );			
			validAttacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 50, weapon, meansOfDeath );			
			validAttacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DESTROYED_REMOTE_UAV" );
			thread maps\mp\gametypes\_missions::vehicleKilled( self.owner, self, undefined, validAttacker, damage, meansOfDeath, weapon );	
		}

		self notify ( "death" );
	}			
}

