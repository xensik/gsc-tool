#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;


init()
{
	path_start = getentarray( "heli_start", "targetname" ); 		// start pointers, point to the actual start node on path
	loop_start = getentarray( "heli_loop_start", "targetname" ); 	// start pointers for loop path in the map

	if ( !path_start.size && !loop_start.size)
		return;

	level.heli_types = [];

	/////////////////////////////////
	// HELICOPTER MODELS, VEHICLES, WEAPONS

	// unused??
	//precacheitem( "cobra_FFAR_mp" );
	//precacheitem( "cobra_player_minigun_mp" );
	
	// generic pull out weapon when killstreak is used
	precacheitem( "heli_remote_mp" );
	
	// attack helicopter
	precacheHelicopter( "vehicle_cobra_helicopter_fly_low", "cobra" );
	precacheHelicopter( "vehicle_mi24p_hind_mp", "hind" );
	//precacheHelicopter( "vehicle_apache_iw5", "apache" );
	precacheVehicle( "cobra_mp" );
	precacheitem( "cobra_20mm_mp" ); // minigun

	// airdrop helicopter ( this is precached and spawned in airdrop.gsc )
	//precacheHelicopter( "vehicle_little_bird_armed", "cobra" );

	// chopper gunner
	//precacheHelicopter( "vehicle_mi-28_mp", "mi28" );
	//precacheHelicopter( "vehicle_apache_mp", "apache" );
	//precacheVehicle( "cobra_minigun_mp" );

	// pavelow
	precacheHelicopter( "vehicle_pavelow",			"pavelow" );
	precacheHelicopter( "vehicle_pavelow_opfor",	"pavelow" );
	precacheVehicle( "pavelow_mp" );
	precacheTurret(	"pavelow_minigun_mp" );
	level._effect[ "ac130_flare" ] 				= loadfx( "misc/flares_cobra" );
	// END HELICOPTER MODELS, VEHICLES, WEAPONS
	/////////////////////////////////


	PreCacheString( &"SPLASHES_DESTROYED_PAVELOW" );
	PreCacheString( &"SPLASHES_DESTROYED_MINIGUNNER" );
	PreCacheString( &"SPLASHES_DESTROYED_HELICOPTER" );
	
	level.chopper = undefined;

	// array of paths, each element is an array of start nodes that all leads to a single destination node
	level.heli_start_nodes = getEntArray( "heli_start", "targetname" );
	assertEx( level.heli_start_nodes.size, "No \"heli_start\" nodes found in map!" );

	level.heli_loop_nodes = getEntArray( "heli_loop_start", "targetname" );
	assertEx( level.heli_loop_nodes.size, "No \"heli_loop_start\" nodes found in map!" );

	level.heli_leave_nodes = getEntArray( "heli_leave", "targetname" );
	assertEx( level.heli_leave_nodes.size, "No \"heli_leave\" nodes found in map!" );

	level.heli_crash_nodes = getEntArray( "heli_crash_start", "targetname" );
	assertEx( level.heli_crash_nodes.size, "No \"heli_crash_start\" nodes found in map!" );
	
	level.heli_missile_rof 	= 5;	// missile rate of fire, one every this many seconds per target, could fire two at the same time to different targets
	level.heli_maxhealth 	= 2000;	// max health of the helicopter
	level.heli_debug 		= 0;	// debug mode, draws debugging info on screen
	
	level.heli_targeting_delay 	= 0.5;	// targeting delay
	level.heli_turretReloadTime = 1.5;	// mini-gun reload time
	level.heli_turretClipSize 	= 40;	// mini-gun clip size, rounds before reload
	level.heli_visual_range 	= 3700;	// distance radius helicopter will acquire targets (see)
			
	level.heli_target_spawnprotection 	= 5;		// players are this many seconds safe from helicopter after spawn
	level.heli_target_recognition 		= 0.5;		// percentage of the player's body the helicopter sees before it labels him as a target
	level.heli_missile_friendlycare 	= 256;		// if friendly is within this distance of the target, do not shoot missile
	level.heli_missile_target_cone 		= 0.3;		// dot product of vector target to helicopter forward, 0.5 is in 90 range, bigger the number, smaller the cone
	level.heli_armor_bulletdamage 		= 0.3;		// damage multiplier to bullets onto helicopter's armor
	
	level.heli_attract_strength 		= 1000;
	level.heli_attract_range 			= 4096;	
	
	level.heli_angle_offset 			= 90;
	level.heli_forced_wait 				= 0;

	// helicopter fx
	level.chopper_fx["explode"]["death"] = [];
	level.chopper_fx["explode"]["large"] = loadfx ("explosions/helicopter_explosion_secondary_small");
	level.chopper_fx["explode"]["medium"] = loadfx ("explosions/aerial_explosion");
	level.chopper_fx["smoke"]["trail"] = loadfx ("smoke/smoke_trail_white_heli");
	level.chopper_fx["fire"]["trail"]["medium"] = loadfx ("fire/fire_smoke_trail_L_emitter");
	level.chopper_fx["fire"]["trail"]["large"] = loadfx ("fire/fire_smoke_trail_L");

	level.chopper_fx["damage"]["light_smoke"] = loadfx ("smoke/smoke_trail_white_heli_emitter");
	level.chopper_fx["damage"]["heavy_smoke"] = loadfx ("smoke/smoke_trail_black_heli_emitter");
	level.chopper_fx["damage"]["on_fire"] = loadfx ("fire/fire_smoke_trail_L_emitter");

	level.chopper_fx["light"]["left"] = loadfx( "misc/aircraft_light_wingtip_green" );
	level.chopper_fx["light"]["right"] = loadfx( "misc/aircraft_light_wingtip_red" );
	level.chopper_fx["light"]["belly"] = loadfx( "misc/aircraft_light_red_blink" );
	level.chopper_fx["light"]["tail"] = loadfx( "misc/aircraft_light_white_blink" );

	level.fx_heli_dust = loadfx ("treadfx/heli_dust_default");
	level.fx_heli_water = loadfx ("treadfx/heli_water");

	makeHeliType( "cobra", "explosions/helicopter_explosion", ::defaultLightFX );
	addAirExplosion( "cobra", "explosions/aerial_explosion_heli" );

	makeHeliType( "pavelow", "explosions/helicopter_explosion", ::pavelowLightFx );
	addAirExplosion( "pavelow", "explosions/aerial_explosion_heli_large" );

	makeHeliType( "mi28", "explosions/helicopter_explosion", ::defaultLightFX );
	addAirExplosion( "mi28", "explosions/aerial_explosion_heli" );

	makeHeliType( "hind", "explosions/helicopter_explosion", ::defaultLightFX );
	addAirExplosion( "hind", "explosions/aerial_explosion_heli" );

	makeHeliType( "apache", "explosions/helicopter_explosion", ::defaultLightFX );
	addAirExplosion( "apache", "explosions/aerial_explosion_heli" );

	makeHeliType( "littlebird", "explosions/aerial_explosion_heli", ::defaultLightFX );
	addAirExplosion( "littlebird", "explosions/aerial_explosion_heli" );

	//makeHeliType( "harrier", "explosions/harrier_exposion_ground", ::defaultLightFX );


	level.killstreakFuncs["helicopter"] = ::useHelicopter;
	level.killstreakFuncs["helicopter_blackbox"] = ::useHelicopterBlackbox;
	level.killstreakFuncs["helicopter_flares"] = ::useHelicopterFlares;
	level.killstreakFuncs["helicopter_minigun"] = ::useHelicopterMinigun;
	level.killstreakFuncs["helicopter_mk19"] = ::useHelicopterMK19;
	
	level.heliDialog["tracking"][0] = "ac130_fco_moreenemy";
	level.heliDialog["tracking"][1] = "ac130_fco_getthatguy";
	level.heliDialog["tracking"][2] = "ac130_fco_guyrunnin";
	level.heliDialog["tracking"][3] = "ac130_fco_gotarunner";
	level.heliDialog["tracking"][4] = "ac130_fco_personnelthere";
	level.heliDialog["tracking"][5] = "ac130_fco_rightthere";
	level.heliDialog["tracking"][6] = "ac130_fco_tracking";

	level.heliDialog["locked"][0] = "ac130_fco_lightemup";
	level.heliDialog["locked"][1] = "ac130_fco_takehimout";
	level.heliDialog["locked"][2] = "ac130_fco_nailthoseguys";

	level.lastHeliDialogTime = 0;	
	
	queueCreate( "helicopter" );
}


makeHeliType( heliType, deathFx, lightFXFunc )
{
	level.chopper_fx["explode"]["death"][ heliType ] = loadFx( deathFX );
	level.lightFxFunc[ heliType ] = lightFXFunc;
}

addAirExplosion( heliType, explodeFx )
{
	level.chopper_fx["explode"]["air_death"][ heliType ] = loadFx( explodeFx );
}


pavelowLightFX()
{
	playFXOnTag( level.chopper_fx["light"]["left"], self, "tag_light_L_wing1" );
	wait ( 0.05 );
	playFXOnTag( level.chopper_fx["light"]["right"], self, "tag_light_R_wing1" );
	wait ( 0.05 );
	playFXOnTag( level.chopper_fx["light"]["belly"], self, "tag_light_belly" );
	wait ( 0.05 );
	playFXOnTag( level.chopper_fx["light"]["tail"], self, "tag_light_tail" );
	wait ( 0.05 );
	playFXOnTag( level.chopper_fx["light"]["tail"], self, "tag_light_tail2" );
	wait ( 0.05 );
	playFXOnTag( level.chopper_fx["light"]["belly"], self, "tag_light_cockpit01" );
}


defaultLightFX()
{
	playFXOnTag( level.chopper_fx["light"]["left"], self, "tag_light_L_wing" );
	wait ( 0.05 );
	playFXOnTag( level.chopper_fx["light"]["right"], self, "tag_light_R_wing" );
	wait ( 0.05 );
	playFXOnTag( level.chopper_fx["light"]["belly"], self, "tag_light_belly" );
	wait ( 0.05 );
	playFXOnTag( level.chopper_fx["light"]["tail"], self, "tag_light_tail" );
}


useHelicopter( lifeId )
{
	return tryUseHelicopter( lifeId, "helicopter" );
}

useHelicopterBlackbox( lifeId )
{
	return tryUseHelicopter( lifeId, "blackbox" );
}

useHelicopterFlares( lifeId )
{
	return tryUseHelicopter( lifeId, "flares" );
}


useHelicopterMinigun( lifeId )
{
	if ( isDefined( self.lastStand ) && !self _hasPerk( "specialty_finalstand" ) )
	{
		self iPrintLnBold( &"MP_UNAVILABLE_IN_LASTSTAND" );
		return false;
	}

	return tryUseHelicopter( lifeId, "minigun" );
}


useHelicopterMK19( lifeId )
{
	if ( isDefined( self.lastStand ) && !self _hasPerk( "specialty_finalstand" ) )
	{
		self iPrintLnBold( &"MP_UNAVILABLE_IN_LASTSTAND" );
		return false;
	}
	return tryUseHelicopter( lifeId, "mk19" );
}


tryUseHelicopter( lifeId, heliType )
{
	if ( isDefined( level.civilianJetFlyBy ) )
	{
		self iPrintLnBold( &"MP_CIVILIAN_AIR_TRAFFIC" );
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
	
	numIncomingVehicles = 1;
	if ( (!isDefined( heliType ) || heliType == "flares") && isDefined( level.chopper ) )
	{		
		self iPrintLnBold( &"MP_HELI_IN_QUEUE" );
		
		if ( isDefined( heliType ) )
			streakName = "helicopter_" + heliType;
		else
			streakName = "helicopter";
			
		//	The chopper won't go out immediately but we'll consider the killstreak used by the player.
		//	Update their killstreaks now. 
		self thread maps\mp\killstreaks\_killstreaks::updateKillstreaks();	
		
		queueEnt = spawn( "script_origin", (0,0,0) );
		queueEnt hide();
		queueEnt thread deleteOnEntNotify( self, "disconnect" );
		queueEnt.player = self;
		queueEnt.lifeId = lifeId;
		queueEnt.heliType = heliType;
		queueEnt.streakName = streakName;
		
		queueAdd( "helicopter", queueEnt );
		
		return false;
	}
	else if ( isDefined( level.chopper ) )
	{
		self iPrintLnBold( &"MP_AIR_SPACE_TOO_CROWDED" );
		return false;
	}		
	else if( currentActiveVehicleCount() >= maxVehiclesAllowed() || level.fauxVehicleCount + numIncomingVehicles >= maxVehiclesAllowed() )
	{
		self iPrintLnBold( &"MP_TOO_MANY_VEHICLES" );
		return false;
	}		

	numIncomingVehicles = 1;
	if ( isDefined( heliType ) && heliType == "minigun" )
	{
		self setUsingRemote( "helicopter_" + heliType );
		result = self maps\mp\killstreaks\_killstreaks::initRideKillstreak();

		if ( result != "success" )
		{
			if ( result != "disconnect" )
				self clearUsingRemote();
	
			return false;
		}

		if ( isDefined( level.chopper ) )
		{
			self clearUsingRemote();
			self iPrintLnBold( &"MP_AIR_SPACE_TOO_CROWDED" );
			return false;
		}
		else if( currentActiveVehicleCount() >= maxVehiclesAllowed() || level.fauxVehicleCount + numIncomingVehicles >= maxVehiclesAllowed() )
		{
			self clearUsingRemote();
			self iPrintLnBold( &"MP_TOO_MANY_VEHICLES" );
			return false;
		}		
	}

	// increment the faux vehicle count before we spawn the vehicle so no other vehicles try to spawn
	incrementFauxVehicleCount();

	self startHelicopter( lifeId, heliType );
	return true;
}


deleteOnEntNotify( ent, notifyString )
{
	self endon ( "death" );
	ent waittill ( notifyString );
	
	self delete();
}


startHelicopter( lifeId, heliType )
{
	if ( !isDefined( heliType ) )
		heliType = "";

	switch ( heliType )
	{
		case "flares":
			self thread pavelowMadeSelectionVO();
			eventType = "helicopter_flares";
			break;
		case "minigun":
			eventType = "helicopter_minigun";
			break;
		default:
			eventType = "helicopter";
			break;
	}
	
	team = self.pers["team"];
	
	startNode = level.heli_start_nodes[ randomInt( level.heli_start_nodes.size ) ];

	self maps\mp\_matchdata::logKillstreakEvent( eventType, self.origin );
	
	thread heli_think( lifeId, self, startNode, self.pers["team"], heliType );
}


precacheHelicopter( model, heliType )
{
	deathfx = loadfx ("explosions/tanker_explosion");

	precacheModel( model );
	
	level.heli_types[model] = heliType;
	
	/******************************************************/
	/*					SETUP WEAPON TAGS				  */
	/******************************************************/
	
	level.cobra_missile_models = [];
	level.cobra_missile_models["cobra_Hellfire"] = "projectile_hellfire_missile";

	precachemodel( level.cobra_missile_models["cobra_Hellfire"] );
	
	// helicopter sounds:
	level.heli_sound["allies"]["hit"] = "cobra_helicopter_hit";
	level.heli_sound["allies"]["hitsecondary"] = "cobra_helicopter_secondary_exp";
	level.heli_sound["allies"]["damaged"] = "cobra_helicopter_damaged";
	level.heli_sound["allies"]["spinloop"] = "cobra_helicopter_dying_loop";
	level.heli_sound["allies"]["spinstart"] = "cobra_helicopter_dying_layer";
	level.heli_sound["allies"]["crash"] = "cobra_helicopter_crash";
	level.heli_sound["allies"]["missilefire"] = "weap_cobra_missile_fire";
	level.heli_sound["axis"]["hit"] = "cobra_helicopter_hit";
	level.heli_sound["axis"]["hitsecondary"] = "cobra_helicopter_secondary_exp";
	level.heli_sound["axis"]["damaged"] = "cobra_helicopter_damaged";
	level.heli_sound["axis"]["spinloop"] = "cobra_helicopter_dying_loop";
	level.heli_sound["axis"]["spinstart"] = "cobra_helicopter_dying_layer";
	level.heli_sound["axis"]["crash"] = "cobra_helicopter_crash";
	level.heli_sound["axis"]["missilefire"] = "weap_cobra_missile_fire";
}


spawn_helicopter( owner, origin, angles, vehicleType, modelName )
{
	chopper = spawnHelicopter( owner, origin, angles, vehicleType, modelName );
	
	if ( !isDefined( chopper ) )
		return undefined;

	chopper.heli_type = level.heli_types[ modelName ];
	
	chopper thread [[ level.lightFxFunc[ chopper.heli_type ] ]]();
	
	chopper addToHeliList();
		
	chopper.zOffset = (0,0,chopper getTagOrigin( "tag_origin" )[2] - chopper getTagOrigin( "tag_ground" )[2]);
	chopper.attractor = Missile_CreateAttractorEnt( chopper, level.heli_attract_strength, level.heli_attract_range );
	
	return chopper;
}


heliRide( lifeId, chopper )
{
	self endon ( "disconnect" );
	chopper endon ( "helicopter_done" );

	thread teamPlayerCardSplash( "used_helicopter_minigun", self );
	self VisionSetThermalForPlayer( "black_bw", 0 );
	//self RemoteCameraSoundscapeOn();
	self _giveWeapon("heli_remote_mp");
	self SwitchToWeapon("heli_remote_mp");
	self VisionSetThermalForPlayer( game["thermal_vision"], 6 );
	self ThermalVisionOn();
	self ThermalVisionFOFOverlayOn();
	self thread thermalVision( chopper );
	if ( getDvarInt( "camera_thirdPerson" ) )
		self setThirdPersonDOF( false );

	chopper VehicleTurretControlOn( self );
	
	self PlayerLinkWeaponviewToDelta( chopper, "tag_player", 1.0, 180, 180, 0, 180, true );
	
	chopper.gunner = self;	

	self.heliRideLifeId = lifeId;

	self thread endRideOnHelicopterDone( chopper );
	
	self thread weaponLockThink( chopper );

	while ( true )
	{
		chopper waittill( "turret_fire" );
		chopper fireWeapon();
		
		earthquake (0.2, 1, chopper.origin, 1000);
	}
}


thermalVision( chopper )
{
	chopper endon ( "helicopter_done" );
	
	if ( getIntProperty( "ac130_thermal_enabled", 1 ) == 0 )
		return;
	
	inverted = false;

	self VisionSetThermalForPlayer( level.ac130.enhanced_vision, 1 );

	self notifyOnPlayerCommand( "switch thermal", "+usereload" );
	self notifyOnPlayerCommand( "switch thermal", "+activate" );

	for (;;)
	{
		self waittill ( "switch thermal" );
		
		if ( !inverted )
		{
			self VisionSetThermalForPlayer( level.ac130.thermal_vision, 0.62 );
		}
		else
		{
			self VisionSetThermalForPlayer( level.ac130.enhanced_vision, 0.51 );
		}

		inverted = !inverted;
	}
}


weaponLockThink( chopper )
{
	self endon ( "disconnect" );
	chopper endon ( "helicopter_done" );

	if ( !isDefined( level.heliTargetOrigin ) )
	{
		level.heliTargetOrigin = spawn( "script_origin", (0,0,0) );
		level.heliTargetOrigin hide();
	}

	for ( ;; )
	{
		trace = bulletTrace( self getEye(), self getEye() + (anglesToForward( self getPlayerAngles() ) * 100000 ), 1, self );
		level.heliTargetOrigin.origin = trace["position"];

		targetListLOS = [];
		targetListNoLOS = [];
		foreach ( player in level.players )
		{
			if ( !isAlive( player ) )
				continue;

			if ( level.teamBased && player.team == self.team )
				continue;
				
			if ( player == self )
				continue;

			if ( player _hasPerk( "specialty_blindeye" ) )
				continue;

			if ( isDefined( player.spawntime ) && ( getTime() - player.spawntime )/1000 <= 5 )
				continue;

			player.remoteHeliLOS = true;
			if ( !bulletTracePassed( self getEye(), player.origin + (0,0,32), false, chopper ) )
			{
				//if ( distance( player.origin, trace["position"] ) > 256 )
				//	continue;
				
				targetListNoLOS[targetListNoLOS.size] = player;
			}
			else
			{
				targetListLOS[targetListLOS.size] = player;
			}
		}

		targetsInReticle = [];

		/*
		foreach ( target in targetList )
		{
			insideReticle = self WorldPointInReticle_Circle( target.origin, 65, 1200 );
			
			if ( !insideReticle )
				continue;
				
			targetsInReticle[targetsInReticle.size] = target;
		}
		*/
		
		targetsInReticle = targetListLOS;
		foreach ( target in targetListNoLos )
		{
			targetListLOS[targetListLOS.size] = target;
		}
		
		if ( targetsInReticle.size != 0 )
		{
			sortedTargets = SortByDistance( targetsInReticle, trace["position"] );

			if ( distance( sortedTargets[0].origin, trace["position"] ) < 384 && sortedTargets[0] DamageConeTrace( trace["position"] ) )
			{
				self weaponLockFinalize( sortedTargets[0] );
				heliDialog( "locked" );
			}
			else
			{
				self weaponLockStart( sortedTargets[0] );
				heliDialog( "tracking" );
			}
		}
		else
		{
			self weaponLockFree();
		}

		wait ( 0.05 );
	}
}


heliDialog( dialogGroup )
{
	if ( getTime() - level.lastHeliDialogTime < 6000 )
		return;
	
	level.lastHeliDialogTime = getTime();
	
	randomIndex = randomInt( level.heliDialog[ dialogGroup ].size );
	soundAlias = level.heliDialog[ dialogGroup ][ randomIndex ];
	
	fullSoundAlias = maps\mp\gametypes\_teams::getTeamVoicePrefix( self.team ) + soundAlias;
	
	self playLocalSound( fullSoundAlias );
}


endRide( chopper )
{
	self RemoteCameraSoundscapeOff();
	self ThermalVisionOff();
	self ThermalVisionFOFOverlayOff();
	self unlink();
	self switchToWeapon( self getLastWeapon() );
	self clearUsingRemote();

	if ( getDvarInt( "camera_thirdPerson" ) )
		self setThirdPersonDOF( true );

	self visionSetThermalForPlayer( game["thermal_vision"], 0 );

	// take the killstreak weapon
	if( isDefined( chopper ) )
	{
		killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( "helicopter_minigun" );
		self TakeWeapon( killstreakWeapon );

		chopper VehicleTurretControlOff( self );
	}

	self notify ( "heliPlayer_removed" );
}	


endRideOnHelicopterDone( chopper )
{
	self endon ( "disconnect" );
	
	chopper waittill ( "helicopter_done" );

	self endRide( chopper );
}


getPosNearEnemies()
{
	validEnemies = [];
	
	foreach ( player in level.players )
	{
		if ( player.team == "spectator" )
			continue;
			
		if ( player.team == self.team )
			continue;
			
		if ( !isAlive( player ) )
			continue;

		if ( !bulletTracePassed( player.origin, player.origin + (0,0,2048), false, player ) )
			continue;
			
		player.remoteHeliDist = 0;
		validEnemies[validEnemies.size] = player;		
	}
	
	if ( !validEnemies.size )
		return undefined;

	for ( i = 0; i < validEnemies.size; i++ )
	{
		for ( j = i + 1; j < validEnemies.size; j++ )
		{
			dist = distanceSquared( validEnemies[i].origin, validEnemies[j].origin );
			
			validEnemies[i].remoteHeliDist += dist;
			validEnemies[j].remoteHeliDist += dist;
		}
	}
	
	bestPlayer = validEnemies[0];
	foreach ( player in validEnemies )
	{
		if ( player.remoteHeliDist < bestPlayer.remoteHeliDist )
			bestPlayer = player;
	}

	return ( bestPlayer.origin );
}


updateAreaNodes( areaNodes )
{
	validEnemies = [];

	foreach ( node in areaNodes )
	{
		node.validPlayers = [];
		node.nodeScore = 0;
	}
	
	foreach ( player in level.players )
	{
		if ( !isAlive( player ) )
			continue;

		if ( player.team == self.team )
			continue;
			
		foreach ( node in areaNodes )
		{
			if ( distanceSquared( player.origin, node.origin ) > 1048576 )
				continue;
				
			node.validPlayers[node.validPlayers.size] = player;
		}
	}

	bestNode = areaNodes[0];
	foreach ( node in areaNodes )
	{
		heliNode = getEnt( node.target, "targetname" );
		foreach ( player in node.validPlayers )
		{
			node.nodeScore += 1;
			
			if ( bulletTracePassed( player.origin + (0,0,32), heliNode.origin, false, player ) )
				node.nodeScore += 3;
		}
		
		if ( node.nodeScore > bestNode.nodeScore )
			bestNode = node;
	}
	
	return ( getEnt( bestNode.target, "targetname" ) );
}


// spawn helicopter at a start node and monitors it
heli_think( lifeId, owner, startNode, heli_team, heliType )
{
	heliOrigin = startNode.origin;
	heliAngles = startNode.angles;

	switch( heliType )
	{
		case "minigun":
			vehicleType = "cobra_minigun_mp";
			if ( owner.team == "allies" )
				vehicleModel = "vehicle_apache_mp";
			else
				vehicleModel = "vehicle_mi-28_mp";
			break;
		case "flares":
			vehicleType = "pavelow_mp";
			if ( owner.team == "allies" )
				vehicleModel = "vehicle_pavelow";
			else
				vehicleModel = "vehicle_pavelow_opfor";
			break;
		default:
			vehicleType = "cobra_mp";
			if ( owner.team == "allies" )
			//	vehicleModel = "vehicle_apache_iw5";
				vehicleModel = "vehicle_cobra_helicopter_fly_low";
			else
				vehicleModel = "vehicle_mi24p_hind_mp";
			break;		
	}

	chopper = spawn_helicopter( owner, heliOrigin, heliAngles, vehicleType, vehicleModel );

	if ( !isDefined( chopper ) )
		return;
		
	level.chopper = chopper;
	chopper.heliType = heliType;
	chopper.lifeId = lifeId;
	chopper.team = heli_team;
	chopper.pers["team"] = heli_team;	
	chopper.owner = owner;

	if ( heliType == "flares" )
		chopper.maxhealth = level.heli_maxhealth*2;			// max health
	else
		chopper.maxhealth = level.heli_maxhealth;			// max health

	chopper.targeting_delay = level.heli_targeting_delay;		// delay between per targeting scan - in seconds
	chopper.primaryTarget = undefined;					// primary target ( player )
	chopper.secondaryTarget = undefined;				// secondary target ( player )
	chopper.attacker = undefined;						// last player that shot the helicopter
	chopper.currentstate = "ok";						// health state
	
	if ( heliType == "flares" || heliType == "minigun" )
		chopper thread heli_flares_monitor();
	
	// helicopter loop threads
	chopper thread heli_leave_on_disconnect( owner );
	chopper thread heli_leave_on_changeTeams( owner );
	chopper thread heli_leave_on_gameended( owner );
	chopper thread heli_damage_monitor();				// monitors damage
	chopper thread heli_health();						// display helicopter's health through smoke/fire
	chopper thread heli_existance();

	// flight logic
	chopper endon ( "helicopter_done" );
	chopper endon ( "crashing" );
	chopper endon ( "leaving" );
	chopper endon ( "death" );

	// initial flight into play space	
	if ( heliType == "minigun" )
	{
		owner thread heliRide( lifeId, chopper );
		chopper thread heli_leave_on_spawned( owner );
	}

	attackAreas = getEntArray( "heli_attack_area", "targetname" );
	//attackAreas = [];
	loopNode = level.heli_loop_nodes[ randomInt( level.heli_loop_nodes.size ) ];	

	// specific logic per type
	switch ( heliType )
	{
		case "minigun":
			chopper thread heli_targeting();
			chopper heli_fly_simple_path( startNode );
			chopper thread heli_leave_on_timeout( 40.0 );
			if ( attackAreas.size )
				chopper thread heli_fly_well( attackAreas );
			else
				chopper thread heli_fly_loop_path( loopNode );
			break;
		case "flares":
			chopper thread makeGunShip();
			thread teamPlayerCardSplash( "used_helicopter_flares", owner );
			chopper heli_fly_simple_path( startNode );
			chopper thread heli_leave_on_timeout( 60.0 );
			chopper thread heli_fly_loop_path( loopNode );
			break;
		default:
			chopper thread attack_targets();
			chopper thread heli_targeting();
			chopper heli_fly_simple_path( startNode );
			chopper thread heli_leave_on_timeout( 60.0 );
			chopper thread heli_fly_loop_path( loopNode );
			break;
	}
}


makeGunShip()
{
	self endon ( "death" );
	self endon ( "helicopter_done" );

	wait ( 0.5 );

	mgTurret = spawnTurret( "misc_turret", self.origin, "pavelow_minigun_mp" );
	mgTurret.lifeId = self.lifeId;
	mgTurret linkTo( self, "tag_gunner_left", ( 0,0,0 ), ( 0,0,0) );
	mgTurret setModel( "weapon_minigun" );
	mgTurret.owner = self.owner;
 	mgTurret.team = self.team;
 	mgTurret makeTurretInoperable();
 	mgTurret.pers["team"] = self.team;
 	mgTurret.killCamEnt = self;
 	self.mgTurretLeft = mgTurret; 
 	self.mgTurretLeft SetDefaultDropPitch( 0 );

	mgTurret = spawnTurret( "misc_turret", self.origin, "pavelow_minigun_mp" );
	mgTurret.lifeId = self.lifeId;
	mgTurret linkTo( self, "tag_gunner_right", ( 0,0,0 ), ( 0,0,0) );
	mgTurret setModel( "weapon_minigun" );
	mgTurret.owner = self.owner;
 	mgTurret.team = self.team;
 	mgTurret makeTurretInoperable();
 	mgTurret.pers["team"] = self.team;
 	mgTurret.killCamEnt = self;
 	self.mgTurretRight = mgTurret; 
 	self.mgTurretRight SetDefaultDropPitch( 0 );

	if ( level.teamBased )
	{
		self.mgTurretLeft setTurretTeam( self.team );
		self.mgTurretRight setTurretTeam( self.team );
	}

 	self.mgTurretLeft setMode( "auto_nonai" );
 	self.mgTurretRight setMode( "auto_nonai" );
 	
	self.mgTurretLeft SetSentryOwner( self.owner );
	self.mgTurretRight SetSentryOwner( self.owner );
	
	self.mgTurretLeft SetTurretMinimapVisible( false );
	self.mgTurretRight SetTurretMinimapVisible( false );

	self.mgTurretLeft thread sentry_attackTargets();
	self.mgTurretRight thread sentry_attackTargets();
 
 	self thread deleteTurretsWhenDone();
}


deleteTurretsWhenDone()
{
 	self waittill ( "helicopter_done" );
 	
 	self.mgTurretRight delete();
 	self.mgTurretLeft delete();
}


sentry_attackTargets()
{
	self endon( "death" );
	self endon ( "helicopter_done" );

	level endon( "game_ended" );

	for ( ;; )
	{
		self waittill( "turretstatechange" );

		if ( self isFiringTurret() )
			self thread sentry_burstFireStart();
		else
			self thread sentry_burstFireStop();
	}
}


sentry_burstFireStart()
{
	self endon( "death" );
	self endon( "stop_shooting" );
	self endon( "leaving" );

	level endon( "game_ended" );

	fireTime = 0.1;
	minShots = 40;
	maxShots = 80;
	minPause = 1.0;
	maxPause = 2.0;

	for ( ;; )
	{		
		numShots = randomIntRange( minShots, maxShots + 1 );
		
		for ( i = 0; i < numShots; i++ )
		{
			targetEnt = self getTurretTarget( false );
			if ( isDefined( targetEnt ) && (!isDefined( targetEnt.spawntime ) || ( gettime() - targetEnt.spawntime )/1000 > 5) )
				self shootTurret();

			wait ( fireTime );
		}
		
		wait ( randomFloatRange( minPause, maxPause ) );
	}
}


sentry_burstFireStop()
{
	self notify( "stop_shooting" );
}


heli_existance()
{
	entityNumber = self getEntityNumber();
	
	self waittill_any( "death", "crashing", "leaving" );

	self removeFromHeliList( entityNumber );
	
	self notify( "helicopter_done" );
	//	for escort airdrop
	self notify( "helicopter_removed" );
	
	player = undefined;
	queueEnt = queueRemoveFirst( "helicopter" );
	if ( !isDefined( queueEnt ) )
	{
		level.chopper = undefined;
		return;
	}
	
	player = queueEnt.player;
	lifeId = queueEnt.lifeId;
	streakName = queueEnt.streakName;
	heliType = queueEnt.heliType;
	queueEnt delete();
	
	if ( isDefined( player ) && (player.sessionstate == "playing" || player.sessionstate == "dead") )
	{
		player maps\mp\killstreaks\_killstreaks::usedKillstreak( streakName, true );
		player startHelicopter( lifeId, heliType );
	}
	else
	{
		level.chopper = undefined;
	}
}


// helicopter targeting logic
heli_targeting()
{
	self endon ( "death" );
	self endon ( "helicopter_done" );
	
	// targeting sweep cycle
	for ( ;; )
	{		
		// array of helicopter's targets
		targets = [];
		self.primaryTarget = undefined;
		self.secondaryTarget = undefined;

		players = level.players;
		
		foreach ( player in level.players )
		{
			if ( !canTarget_turret( player ) )
				continue;

			targets[targets.size] = player;
		}
	
		if ( targets.size )
		{
			targetPlayer = getBestPrimaryTarget( targets );
			self.primaryTarget = targetPlayer;
			self notify( "primary acquired" );
		}

		if ( isDefined( level.harriers ) )
		{
			foreach( harrier in level.harriers )
			{
				if( !isDefined( harrier ) )
					continue;
				
				if ( (level.teamBased && harrier.team != self.team) || (!level.teamBased && harrier.owner != self.owner) )
				{
					self notify( "secondary acquired" );
					self.secondaryTarget = harrier;
				}
			}
		}

		wait ( 0.5 );
	}	
}

// targetability
canTarget_turret( player )
{
	canTarget = true;
	
	if ( !isAlive( player ) || player.sessionstate != "playing" )
		return false;

	if ( self.heliType == "remote_mortar" )
	{
		if ( player sightConeTrace( self.origin, self ) < 1 )
			return false;
	}	
	else if ( self.heliType != "flares" )
	{
		if ( !self Vehicle_CanTurretTargetPoint( player.origin+(0,0,40), 1, self ) )
			return false;
	}
		
	if ( distance( player.origin, self.origin ) > level.heli_visual_range )
		return false;
	
	if ( level.teamBased && player.pers["team"] == self.team )
		return false;
	
	if ( player == self.owner )
		return false;
	
	if ( isdefined( player.spawntime ) && ( gettime() - player.spawntime )/1000 <= 5 )
		return false;

	if ( player _hasPerk( "specialty_blindeye" ) )
		return false;
		
	heli_centroid = self.origin + ( 0, 0, -160 );
	heli_forward_norm = anglestoforward( self.angles );
	heli_turret_point = heli_centroid + 144*heli_forward_norm;
	
	if ( player sightConeTrace( heli_turret_point, self) < level.heli_target_recognition )
		return false;	
	
	return canTarget;
}


getBestPrimaryTarget( targets )
{
	foreach ( player in targets )
		update_player_threat( player );
			
	// find primary target, highest threat level
	highest = 0;	
	primaryTarget = undefined;
	
	corners = GetEntArray( "minimap_corner", "targetname" );
	foreach ( player in targets )
	{
		assertEx( isDefined( player.threatlevel ), "Target player does not have threat level" );
		
		// as a failsafe, make sure the player is within the play space
		if( corners.size == 2 )
		{
			min = corners[0].origin;
			max = corners[0].origin;
			if ( corners[1].origin[0] > max[0] )
				max = (corners[1].origin[0], max[1], max[2]);
			else
				min = (corners[1].origin[0], min[1], min[2]);
			if( corners[1].origin[1] > max[1] )
				max = (max[0], corners[1].origin[1], max[2]);
			else
				min = (min[0], corners[1].origin[1], min[2]);
			
			if( player.origin[0] < min[0] || player.origin[0] > max[0] || player.origin[1] < min[1] || player.origin[1] > max[1] )
				continue;
		}

		if ( player.threatlevel < highest )
			continue;

		highest = player.threatlevel;
		primaryTarget = player;
	}
	
	assertEx( isDefined( primaryTarget ), "Targets exist, but none was assigned as primary" );

	return ( primaryTarget );
}


// threat factors
update_player_threat( player )
{
	player.threatlevel = 0;
	
	// distance factor
	dist = distance( player.origin, self.origin );
	player.threatlevel += ( (level.heli_visual_range - dist)/level.heli_visual_range )*100; // inverse distance % with respect to helicopter targeting range
	
	// behavior factor
	if ( isdefined( self.attacker ) && player == self.attacker )
		player.threatlevel += 100;
	
	// player score factor
	player.threatlevel += player.score*4;
		
	if( isdefined( player.antithreat ) )
		player.threatlevel -= player.antithreat;
		
	if( player.threatlevel <= 0 )
		player.threatlevel = 1;
}


// resets helicopter's motion values
heli_reset()
{
	self clearTargetYaw();
	self clearGoalYaw();
	self Vehicle_SetSpeed( 60, 25 );	
	self setyawspeed( 75, 45, 45 );
	//self setjitterparams( (30, 30, 30), 4, 6 );
	self setmaxpitchroll( 30, 30 );
	self setneargoalnotifydist( 256 );
	self setturningability(0.9);
}

addRecentDamage( damage )
{
	self endon( "death" );

	self.recentDamageAmount += damage;

	wait ( 4.0 );
	self.recentDamageAmount -= damage;
}


// accumulate damage and react
heli_damage_monitor()
{
	self endon( "death" );
	self endon( "crashing" );
	self endon( "leaving" );
	
	self.health = 999999; // keep it from dying anywhere in code
	self.damageTaken = 0;
	self.recentDamageAmount = 0;
	
	for( ;; )
	{
		// this damage is done to self.health which isnt used to determine the helicopter's health, damageTaken is.
		self waittill( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );

		assert( isDefined( attacker ) );
		
		// check if the attacker is sent as world spawn (player that called out the vehicle that died last doesnt get credit for the vehicle kill)
		//	we don't want to exit this function though or else the vehicle becomes invincible
		if( isDefined( attacker.class ) && attacker.class == "worldspawn" )
			continue; 
		// don't let us kill ourselves
		else if( attacker == self )
			continue; 
			
		if ( attacker.team == self.team && attacker != self.owner )
			continue;

		self.attacker = attacker;

		modifiedDamage = damage;
		if ( isPlayer( attacker ) )
		{
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "" );

			if ( meansOfDeath == "MOD_RIFLE_BULLET" || meansOfDeath == "MOD_PISTOL_BULLET" )
			{
				if( self.heliType == "flares" )
					modifiedDamage *= level.heli_armor_bulletdamage;
				
				if ( attacker _hasPerk( "specialty_armorpiercing" ) )
					modifiedDamage += ( damage * level.armorPiercingMod );
			}
		}

		// in case we are shooting from a remote position, like being in the osprey gunner shooting this
		if( IsDefined( attacker.owner ) && IsPlayer( attacker.owner ) )
		{
			attacker.owner maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "helicopter" );
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

			case "sam_projectile_mp":
				self.largeProjectileDamage = true;		
				switch( self.heliType )
				{
				case "flares":
				case "osprey":
				case "osprey_gunner":
					modifiedDamage = self.maxHealth * 0.07; // takes about 4 bursts of sam rockets
					break;
				case "littlebird":
				case "helicopter":
					modifiedDamage = self.maxHealth * 0.09; // takes about 3 bursts of sam rockets
					break;
				}
				break;

			case "emp_grenade_mp":
				self.largeProjectileDamage = false;
				modifiedDamage = self.maxHealth + 1;
				break;

			case "osprey_player_minigun_mp":
				self.largeProjectileDamage = false;
				modifiedDamage *= 2; // since it's a larger caliber, make it hurt
				break;
			}				
		}

		self.damageTaken += modifiedDamage;

		self thread addRecentDamage( modifiedDamage );

		if( self.damageTaken >= self.maxhealth )
		{
			if ( (level.teamBased && self.team != attacker.team) || !level.teamBased )
			{
				validAttacker = undefined;
				if ( isDefined( attacker.owner ) && (!isDefined(self.owner) || attacker.owner != self.owner) )
					validAttacker = attacker.owner;
				else if ( !isDefined(attacker.owner) && attacker.classname == "script_vehicle" )
					return;
				else if ( !isDefined(self.owner) || attacker != self.owner )
					validAttacker = attacker;
	
				if ( isDefined( validAttacker ) )
				{
					validAttacker notify( "destroyed_helicopter" );
	
					switch( self.heliType )
					{
					case "flares":
						validAttacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DESTROYED_PAVELOW" );					
						thread teamPlayerCardSplash( "callout_destroyed_helicopter_flares", validAttacker );
						xpVal = 400;
						break;
					case "minigun":
						validAttacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DESTROYED_MINIGUNNER" );
						thread teamPlayerCardSplash( "callout_destroyed_helicopter_minigun", validAttacker );
						xpVal = 300;
						break;
					case "osprey":
					case "osprey_gunner":
						validAttacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DESTROYED_OSPREY" );
						thread teamPlayerCardSplash( "callout_destroyed_osprey", validAttacker );
						xpVal = 300;
						break;
					case "littlebird":
						validAttacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DESTROYED_LITTLE_BIRD" );
						thread teamPlayerCardSplash( "callout_destroyed_little_bird", validAttacker );
						xpVal = 200;

					default:
						validAttacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DESTROYED_HELICOPTER" );
						thread teamPlayerCardSplash( "callout_destroyed_helicopter", validAttacker );
						xpVal = 200;
						break;
					}
					
					validAttacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", xpVal,weapon, meansOfDeath );
					thread maps\mp\gametypes\_missions::vehicleKilled( self.owner, self, undefined, validAttacker, damage, meansOfDeath, weapon );				
				}
			}
		}
	}
}


heli_health()
{
	self endon( "death" );
	self endon( "leaving" );
	self endon( "crashing" );
	
	self.currentstate = "ok";
	self.laststate = "ok";
	self setdamagestage( 3 );
	
	damageState = 3;
	self setDamageStage( damageState );
	
	for ( ;; )
	{
		if ( self.damageTaken >= (self.maxhealth * 0.33) && damageState == 3 )
		{
			damageState = 2;
			self setDamageStage( damageState );
			self.currentstate = "light smoke";
			playFxOnTag( level.chopper_fx["damage"]["light_smoke"], self, "tag_engine_left" );
		}
		else if ( self.damageTaken >= (self.maxhealth * 0.66) && damageState == 2 )
		{
			damageState = 1;
			self setDamageStage( damageState );
			self.currentstate = "heavy smoke";
			stopFxOnTag( level.chopper_fx["damage"]["light_smoke"], self, "tag_engine_left" );
			playFxOnTag( level.chopper_fx["damage"]["heavy_smoke"], self, "tag_engine_left" );
		}
		else if( self.damageTaken > self.maxhealth )
		{
			damageState = 0;
			self setDamageStage( damageState );

			stopFxOnTag( level.chopper_fx["damage"]["heavy_smoke"], self, "tag_engine_left" );
			
			if ( IsDefined( self.largeProjectileDamage ) && self.largeProjectileDamage )
			{
				self thread heli_explode( true );
			}
			else
			{
				playFxOnTag( level.chopper_fx["damage"]["on_fire"], self, "tag_engine_left" );
				self thread heli_crash();
			}
		}
		
		wait 0.05;
	}
}


// attach helicopter on crash path
heli_crash()
{
	self notify( "crashing" );

	crashNode = level.heli_crash_nodes[ randomInt( level.heli_crash_nodes.size ) ];	

	self thread heli_spin( 180 );
	self thread heli_secondary_explosions();
	self heli_fly_simple_path( crashNode );
	
	self thread heli_explode();
}

heli_secondary_explosions()
{
	playFxOnTag( level.chopper_fx["explode"]["large"], self, "tag_engine_left" );
	self playSound ( level.heli_sound[self.team]["hitsecondary"] );

	wait ( 3.0 );

	if ( !isDefined( self ) )
		return;
         
	playFxOnTag( level.chopper_fx["explode"]["large"], self, "tag_engine_left" );
	self playSound ( level.heli_sound[self.team]["hitsecondary"] );
}

// self spin at one rev per 2 sec
heli_spin( speed )
{
	self endon( "death" );
	
	// play hit sound immediately so players know they got it
	self playSound ( level.heli_sound[self.team]["hit"] );
	
	// play heli crashing spinning sound
	self thread spinSoundShortly();
	
	// spins until death
	self setyawspeed( speed, speed, speed );
	while ( isdefined( self ) )
	{
		self settargetyaw( self.angles[1]+(speed*0.9) );
		wait ( 1 );
	}
}


spinSoundShortly()
{
	self endon("death");
	
	wait .25;
	
	self stopLoopSound();
	wait .05;
	self playLoopSound( level.heli_sound[self.team]["spinloop"] );
	wait .05;
	self playLoopSound( level.heli_sound[self.team]["spinstart"] );
}


// crash explosion
heli_explode( altStyle )
{
	self notify( "death" );
	
	if ( isDefined( altStyle ) && isDefined( level.chopper_fx["explode"]["air_death"][self.heli_type] ) )
	{
		deathAngles = self getTagAngles( "tag_deathfx" );
		
		playFx( level.chopper_fx["explode"]["air_death"][self.heli_type], self getTagOrigin( "tag_deathfx" ), anglesToForward( deathAngles ), anglesToUp( deathAngles ) );
		//playFxOnTag( level.chopper_fx["explode"]["air_death"][self.heli_type], self, "tag_deathfx" );	
	}
	else
	{
		org = self.origin;	
		forward = ( self.origin + ( 0, 0, 1 ) ) - self.origin;
		playFx( level.chopper_fx["explode"]["death"][self.heli_type], org, forward );
	}
	
	
	// play heli explosion sound
	self playSound( level.heli_sound[self.team]["crash"] );

	// give "death" notify time to process
	wait ( 0.05 );
	
	if( IsDefined( self.killCamEnt ) )
		self.killCamEnt delete();

	self delete();
}


fire_missile( sMissileType, iShots, eTarget )
{
	if ( !isdefined( iShots ) )
		iShots = 1;
	assert( self.health > 0 );
	
	weaponName = undefined;
	weaponShootTime = undefined;
	defaultWeapon = "cobra_20mm_mp";
	tags = [];
	switch( sMissileType )
	{
		case "ffar":
			weaponName = "harrier_FFAR_mp";
				
			tags[ 0 ] = "tag_store_r_2";
			break;
		default:
			assertMsg( "Invalid missile type specified. Must be ffar" );
			break;
	}
	assert( isdefined( weaponName ) );
	assert( tags.size > 0 );
	
	weaponShootTime = weaponfiretime( weaponName );
	assert( isdefined( weaponShootTime ) );
	
	self setVehWeapon( weaponName );
	nextMissileTag = -1;
	for( i = 0 ; i < iShots ; i++ ) // I don't believe iShots > 1 is properly supported; we don't set the weapon each time
	{
		nextMissileTag++;
		if ( nextMissileTag >= tags.size )
			nextMissileTag = 0;
		
		self setVehWeapon( "harrier_FFAR_mp" );
		
		if ( isdefined( eTarget ) )
		{
			eMissile = self fireWeapon( tags[ nextMissileTag ], eTarget );
			eMissile Missile_SetFlightmodeDirect();
			eMissile Missile_SetTargetEnt( eTarget );
		}
		else
		{
			eMissile = self fireWeapon( tags[ nextMissileTag ] );
			eMissile Missile_SetFlightmodeDirect();
			eMissile Missile_SetTargetEnt( eTarget );
		}
		
		if ( i < iShots - 1 )
			wait weaponShootTime;
	}
	// avoid calling setVehWeapon again this frame or the client doesn't hear about the original weapon change
}

// checks if owner is valid, returns false if not valid
check_owner()
{
	if ( !isdefined( self.owner ) || !isdefined( self.owner.pers["team"] ) || self.owner.pers["team"] != self.team )
	{
		self thread heli_leave();
		
		return false;	
	}
	
	return true;
}


heli_leave_on_disconnect( owner )
{
	self endon ( "death" );
	self endon ( "helicopter_done" );

	owner waittill( "disconnect" );
	
	self thread heli_leave();
}

heli_leave_on_changeTeams( owner )
{
	self endon ( "death" );
	self endon ( "helicopter_done" );

	owner waittill_any( "joined_team", "joined_spectators" );
	
	self thread heli_leave();
}

heli_leave_on_spawned( owner )
{
	self endon ( "death" );
	self endon ( "helicopter_done" );

	owner waittill( "spawned" );
	
	self thread heli_leave();
}

heli_leave_on_gameended( owner )
{
	self endon ( "death" );
	self endon ( "helicopter_done" );

	level waittill ( "game_ended" );
	
	self thread heli_leave();	
}

heli_leave_on_timeout( timeOut )
{
	self endon ( "death" );
	self endon ( "helicopter_done" );
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( timeOut );
	
	self thread heli_leave();
}

attack_targets()
{
	//self thread turret_kill_players();
	self thread attack_primary();
	self thread attack_secondary();
}


// missile only
attack_secondary()
{
	self endon( "death" );
	self endon( "crashing" );
	self endon( "leaving" );	
	
	for( ;; )
	{
		if ( isdefined( self.secondaryTarget ) )
		{
			self.secondaryTarget.antithreat = undefined;
			self.missileTarget = self.secondaryTarget;
			
			antithreat = 0;

			while( isdefined( self.missileTarget ) && isalive( self.missileTarget ) )
			{
				// if selected target is not in missile hit range, skip
				if( self missile_target_sight_check( self.missileTarget ) )
					self thread missile_support( self.missileTarget, level.heli_missile_rof);
				else
					break;
				
				self waittill( "missile ready" );
				
				// target might disconnect or change during last assault cycle
				if ( !isdefined( self.secondaryTarget ) || ( isdefined( self.secondaryTarget ) && self.missileTarget != self.secondaryTarget ) )
					break;
			}
			// reset the antithreat factor
			if ( isdefined( self.missileTarget ) )
				self.missileTarget.antithreat = undefined;
		}
		self waittill( "secondary acquired" );
		
		// check if owner has left, if so, leave
		self check_owner();
	}	
}

// check if missile is in hittable sight zone
missile_target_sight_check( missiletarget )
{
	heli2target_normal = vectornormalize( missiletarget.origin - self.origin );
	heli2forward = anglestoforward( self.angles );
	heli2forward_normal = vectornormalize( heli2forward );

	heli_dot_target = vectordot( heli2target_normal, heli2forward_normal );
	
	if ( heli_dot_target >= level.heli_missile_target_cone )
	{
		debug_print3d_simple( "Missile sight: " + heli_dot_target, self, ( 0,0,-40 ), 40 );
		return true;
	}
	return false;
}

// if wait for turret turning is too slow, enable missile assault support
missile_support( target_player, rof )
{
	self endon( "death" );
	self endon( "crashing" );
	self endon( "leaving" );	
	
	if ( isdefined( target_player ) )
	{
		if ( level.teambased )
		{
			if ( isDefined( target_player.owner ) && target_player.team != self.team )
			{
				self fire_missile( "ffar", 1, target_player );
				self notify( "missile fired" );
			}				
		}
		else
		{
			if ( isDefined( target_player.owner ) && target_player.owner != self.owner )
			{
				self fire_missile( "ffar", 1, target_player );
				self notify( "missile fired" );
			}
		}
	}
	
	wait ( rof );
	self notify ( "missile ready" );
	
	return;
}

// mini-gun with missile support
attack_primary()
{
	self endon( "death" );
	self endon( "crashing" );
	self endon( "leaving" );
	
	while ( 1 )
	{
		wait ( 0.05 );

		if ( !isAlive( self.primaryTarget ) )
			continue;
			
		currentTarget = self.primaryTarget;

		currentTarget.antithreat = 0;

		if ( randomInt(5) < 3 )
			angle = currentTarget.angles[1] + randomFloatRange( -30, 30 );
		else
			angle = randomInt( 360 );

		radiusOffset = 96;

		xOffset = cos( angle ) * radiusOffset;
		yOffset = sin( angle ) * radiusOffset;

		self setTurretTargetEnt( currentTarget, (xOffset,yOffset,40) );
		
		self waitOnTargetOrDeath( currentTarget, 3.0 );
		
		if ( !isAlive( currentTarget ) || !self Vehicle_CanTurretTargetPoint( currentTarget.origin+(0,0,40) ) )
			continue;
		
		weaponShootTime = weaponFireTime( "cobra_20mm_mp" );
		
		convergenceMod = 1;
		shotsSinceLastSighting = 0;

		self playLoopSound( "weap_cobra_20mm_fire_npc" );
		for ( i = 0; i < level.heli_turretClipSize; i++ )
		{
			self setVehWeapon( "cobra_20mm_mp" );
			self fireWeapon( "tag_flash" );

			if ( i < level.heli_turretClipSize - 1 )
				wait weaponShootTime;

			if ( !isDefined( currentTarget ) )
				break;

			if ( self Vehicle_CanTurretTargetPoint( currentTarget.origin+(0,0,40), 1, self ) )
			{
				convergenceMod = max( convergenceMod - 0.05, 0 );
				shotsSinceLastSighting = 0;
			}
			else
			{
				shotsSinceLastSighting++;
			}

			if ( shotsSinceLastSighting > 10 )
				break;

			targetPos = ( (xOffset*convergenceMod)+randomFloatRange( -6, 6 ),(yOffset*convergenceMod)+randomFloatRange( -6, 6 ),40+randomFloatRange( -6, 6 ) );

			self setTurretTargetEnt( currentTarget, targetPos );
		}
		self stopLoopSound();

		// lower the target's threat since already assaulted on
		if ( isAlive( currentTarget ) )
			currentTarget.antithreat += 100;
		
		wait ( randomFloatRange( 0.5, 2.0 ) );
	}
}

waitOnTargetOrDeath( target, timeOut )
{
	self endon ( "death" );
	self endon ( "helicopter_done" );

	target endon ( "death" );
	target endon ( "disconnect" );
	
	self waittill_notify_or_timeout( "turret_on_target", timeOut );
}


fireMissile( missileTarget )
{
	self endon( "death" );
	self endon( "crashing" );
	self endon( "leaving" );
	
	assert( self.health > 0 );
	
	if ( !isdefined( missileTarget ) )
		return;
		
	if ( Distance2D(self.origin, missileTarget.origin ) < 512 )
		return;

	self setVehWeapon( "harrier_FFAR_mp" );
	missile = self fireWeapon( "tag_flash", missileTarget );
	missile Missile_SetFlightmodeDirect();
	missile Missile_SetTargetEnt( missileTarget );
}


// ====================================================================================
//								Helicopter Pathing Logic
// ====================================================================================

getOriginOffsets( goalNode )
{
	startOrigin = self.origin;
	endOrigin = goalNode.origin;
	
	numTraces = 0;
	maxTraces = 40;
	
	traceOffset = (0,0,-196);
	
	traceOrigin = physicsTrace( startOrigin+traceOffset, endOrigin+traceOffset );

	while ( distance( traceOrigin, endOrigin+traceOffset ) > 10 && numTraces < maxTraces )
	{	
		println( "trace failed: " + distance( physicsTrace( startOrigin+traceOffset, endOrigin+traceOffset ), endOrigin+traceOffset ) );
			
		if ( startOrigin[2] < endOrigin[2] )
		{
			startOrigin += (0,0,128);
		}
		else if ( startOrigin[2] > endOrigin[2] )
		{
			endOrigin += (0,0,128);
		}
		else
		{	
			startOrigin += (0,0,128);
			endOrigin += (0,0,128);
		}
		
		//thread draw_line( startOrigin+traceOffset, endOrigin+traceOffset, (0,1,9), 200 );
		numTraces++;

		traceOrigin = physicsTrace( startOrigin+traceOffset, endOrigin+traceOffset );
	}
	
	offsets = [];
	offsets["start"] = startOrigin;
	offsets["end"] = endOrigin;
	return offsets;
}


travelToNode( goalNode )
{
	originOffets = getOriginOffsets( goalNode );
	
	if ( originOffets["start"] != self.origin )
	{
		// motion change via node
		if( isdefined( goalNode.script_airspeed ) && isdefined( goalNode.script_accel ) )
		{
			heli_speed = goalNode.script_airspeed;
			heli_accel = goalNode.script_accel;
		}
		else
		{
			heli_speed = 30+randomInt(20);
			heli_accel = 15+randomInt(15);
		}
		
		self Vehicle_SetSpeed( heli_speed, heli_accel );
		self setvehgoalpos( originOffets["start"] + (0,0,30), 0 );
		// calculate ideal yaw
		self setgoalyaw( goalNode.angles[ 1 ] + level.heli_angle_offset );
		
		//println( "setting goal to startOrigin" );
		
		self waittill ( "goal" );
	}
	
	if ( originOffets["end"] != goalNode.origin )
	{
		// motion change via node
		if( isdefined( goalNode.script_airspeed ) && isdefined( goalNode.script_accel ) )
		{
			heli_speed = goalNode.script_airspeed;
			heli_accel = goalNode.script_accel;
		}
		else
		{
			heli_speed = 30+randomInt(20);
			heli_accel = 15+randomInt(15);
		}
		
		self Vehicle_SetSpeed( heli_speed, heli_accel );
		self setvehgoalpos( originOffets["end"] + (0,0,30), 0 );
		// calculate ideal yaw
		self setgoalyaw( goalNode.angles[ 1 ] + level.heli_angle_offset );

		//println( "setting goal to endOrigin" );
		
		self waittill ( "goal" );
	}
}


heli_fly_simple_path( startNode )
{
	self endon ( "death" );
	self endon ( "leaving" );

	// only one thread instance allowed
	self notify( "flying");
	self endon( "flying" );
	
	heli_reset();
	
	currentNode = startNode;
	while ( isDefined( currentNode.target ) )
	{
		nextNode = getEnt( currentNode.target, "targetname" );
		assertEx( isDefined( nextNode ), "Next node in path is undefined, but has targetname. Bad Node Position: " + currentNode.origin );
		
		if( isDefined( currentNode.script_airspeed ) && isDefined( currentNode.script_accel ) )
		{
			heli_speed = currentNode.script_airspeed;
			heli_accel = currentNode.script_accel;
		}
		else
		{
			heli_speed = 30 + randomInt(20);
			heli_accel = 15 + randomInt(15);
		}

		self Vehicle_SetSpeed( heli_speed, heli_accel );
		
		// end of the path
		if ( !isDefined( nextNode.target ) )
		{
			self setVehGoalPos( nextNode.origin+(self.zOffset), true );
			self waittill( "near_goal" );
		}
		else
		{
			self setVehGoalPos( nextNode.origin+(self.zOffset), false );
			self waittill( "near_goal" );

			self setGoalYaw( nextNode.angles[ 1 ] );

			self waittillmatch( "goal" );
		}

		currentNode = nextNode;
	}
	
	printLn( currentNode.origin );
	printLn( self.origin );
}


heli_fly_loop_path( startNode )
{
	self endon ( "death" );
	self endon ( "crashing" );
	self endon ( "leaving" );

	// only one thread instance allowed
	self notify( "flying");
	self endon( "flying" );
	
	heli_reset();
	
	self thread heli_loop_speed_control( startNode );
	
	currentNode = startNode;
	while ( isDefined( currentNode.target ) )
	{
		nextNode = getEnt( currentNode.target, "targetname" );
		assertEx( isDefined( nextNode ), "Next node in path is undefined, but has targetname. Bad Node Position: " + currentNode.origin );
		
		if( isDefined( currentNode.script_airspeed ) && isDefined( currentNode.script_accel ) )
		{
			self.desired_speed = currentNode.script_airspeed;
			self.desired_accel = currentNode.script_accel;
		}
		else
		{
			self.desired_speed = 30 + randomInt( 20 );
			self.desired_accel = 15 + randomInt( 15 );
		}
		
		if ( self.heliType == "flares" )
		{
			self.desired_speed *= 0.5;
			self.desired_accel *= 0.5;
		}
		
		if ( isDefined( nextNode.script_delay ) && isDefined( self.primaryTarget ) && !self heli_is_threatened() )
		{
			self setVehGoalPos( nextNode.origin+(self.zOffset), true );
			self waittill( "near_goal" );

			wait ( nextNode.script_delay );
		}
		else
		{
			self setVehGoalPos( nextNode.origin+(self.zOffset), false );
			self waittill( "near_goal" );

			self setGoalYaw( nextNode.angles[ 1 ] );

			self waittillmatch( "goal" );
		}

		currentNode = nextNode;
	}
}


heli_loop_speed_control( currentNode )
{
	self endon ( "death" );
	self endon ( "crashing" );
	self endon ( "leaving" );

	if( isDefined( currentNode.script_airspeed ) && isDefined( currentNode.script_accel ) )
	{
		self.desired_speed = currentNode.script_airspeed;
		self.desired_accel = currentNode.script_accel;
	}
	else
	{
		self.desired_speed = 30 + randomInt( 20 );
		self.desired_accel = 15 + randomInt( 15 );
	}
	
	lastSpeed = 0;
	lastAccel = 0;
	
	while ( 1 )
	{
		goalSpeed = self.desired_speed;
		goalAccel = self.desired_accel;
		
		if ( self.heliType != "flares" && isDefined( self.primaryTarget ) && !self heli_is_threatened() )
			goalSpeed *= 0.25;
					
		if ( lastSpeed != goalSpeed || lastAccel != goalAccel )
		{
			self Vehicle_SetSpeed( goalSpeed, goalAccel );
			
			lastSpeed = goalSpeed;
			lastAccel = goalAccel;
		}
		
		wait ( 0.05 );
	}
}


heli_is_threatened()
{
	if ( self.recentDamageAmount > 50 )
		return true;

	if ( self.currentState == "heavy smoke" )
		return true;
		
	return false;	
}


heli_fly_well( destNodes )
{
	self notify( "flying");
	self endon( "flying" );

	self endon ( "death" );
	self endon ( "crashing" );
	self endon ( "leaving" );

	for ( ;; )	
	{
		currentNode = self get_best_area_attack_node( destNodes );
	
		travelToNode( currentNode );
		
		// motion change via node
		if( isdefined( currentNode.script_airspeed ) && isdefined( currentNode.script_accel ) )
		{
			heli_speed = currentNode.script_airspeed;
			heli_accel = currentNode.script_accel;
		}
		else
		{
			heli_speed = 30+randomInt(20);
			heli_accel = 15+randomInt(15);
		}
		
		self Vehicle_SetSpeed( heli_speed, heli_accel );	
		self setvehgoalpos( currentNode.origin + self.zOffset, 1 );
		self setgoalyaw( currentNode.angles[ 1 ] + level.heli_angle_offset );	

		if ( level.heli_forced_wait != 0 )
		{
			self waittill( "near_goal" ); //self waittillmatch( "goal" );
			wait ( level.heli_forced_wait );			
		}
		else if ( !isdefined( currentNode.script_delay ) )
		{
			self waittill( "near_goal" ); //self waittillmatch( "goal" );

			wait ( 5 + randomInt( 5 ) );
		}
		else
		{				
			self waittillmatch( "goal" );				
			wait ( currentNode.script_delay );
		}
	}
}


get_best_area_attack_node( destNodes )
{
	return updateAreaNodes( destNodes );
}


// helicopter leaving parameter, can not be damaged while leaving
heli_leave( leavePos )
{
	// escort airdrop needs to rise before it leaves
	if( IsDefined( self.heliType ) && self.heliType == "osprey" && IsDefined( self.pathGoal ) )
	{
		self SetVehGoalPos( self.pathGoal, 1 );	
		self waittill_any_timeout( 5, "goal" );	
	}

	self notify( "leaving" );
	
	if ( !isDefined( leavePos ) )
	{
		leaveNode = level.heli_leave_nodes[ randomInt( level.heli_leave_nodes.size ) ];
		leavePos = leaveNode.origin;
	}

	// make sure it doesn't fly away backwards
	endEnt = Spawn( "script_origin", leavePos );
	if( IsDefined( endEnt ) )
	{
		self SetLookAtEnt( endEnt );
		endEnt thread wait_and_delete( 3.0 );
	}

	self heli_reset();
	self Vehicle_SetSpeed( 100, 45 );	
	self setvehgoalpos( leavePos, 1 );
	self waittillmatch( "goal" );
	self notify( "death" );
	
	// give "death" notify time to process
	wait ( 0.05 );

	if( IsDefined( self.killCamEnt ) )
		self.killCamEnt delete();

	self delete();
}

wait_and_delete( waitTime )
{
	self endon( "death" );
	level endon( "game_ended" );
	wait( waitTime );
	self delete();
}


// ====================================================================================
// 								DEBUG INFORMATION
// ====================================================================================

debug_print3d( message, color, ent, origin_offset, frames )
{
	if ( isdefined( level.heli_debug ) && level.heli_debug == 1.0 )
		self thread draw_text( message, color, ent, origin_offset, frames );
}

debug_print3d_simple( message, ent, offset, frames )
{
	if ( isdefined( level.heli_debug ) && level.heli_debug == 1.0 )
	{
		if( isdefined( frames ) )
			thread draw_text( message, ( 0.8, 0.8, 0.8 ), ent, offset, frames );
		else
			thread draw_text( message, ( 0.8, 0.8, 0.8 ), ent, offset, 0 );
	}
}

debug_line( from, to, color, frames )
{
	if ( isdefined( level.heli_debug ) && level.heli_debug == 1.0 && !isdefined( frames ) )
	{
		thread draw_line( from, to, color );
	}
	else if ( isdefined( level.heli_debug ) && level.heli_debug == 1.0 )
		thread draw_line( from, to, color, frames);
}

draw_text( msg, color, ent, offset, frames )
{
	//level endon( "helicopter_done" );
	if( frames == 0 )
	{
		while ( isdefined( ent ) )
		{
			print3d( ent.origin+offset, msg , color, 0.5, 4 );
			wait 0.05;
		}
	}
	else
	{
		for( i=0; i < frames; i++ )
		{
			if( !isdefined( ent ) )
				break;
			print3d( ent.origin+offset, msg , color, 0.5, 4 );
			wait 0.05;
		}
	}
}

draw_line( from, to, color, frames )
{
	//level endon( "helicopter_done" );
	if( isdefined( frames ) )
	{
		for( i=0; i<frames; i++ )
		{
			line( from, to, color );
			wait 0.05;
		}		
	}
	else
	{
		for( ;; )
		{
			line( from, to, color );
			wait 0.05;
		}
	}
}



addToHeliList()
{
	level.helis[self getEntityNumber()] = self;	
}

removeFromHeliList( entityNumber )
{
	level.helis[entityNumber] = undefined;

	// decrement the faux vehicle count since this is being removed
	decrementFauxVehicleCount();
}	

addToLittleBirdList()
{
	level.littleBirds[ self GetEntityNumber() ] = self;	
}

removeFromLittleBirdListOnDeath()
{
	entNum = self GetEntityNumber();

	self waittill ( "death" );

	level.littleBirds[ entNum ] = undefined;

	// decrement the faux vehicle count since this is being removed
	decrementFauxVehicleCount();
}

exceededMaxLittlebirds( streakName )
{
	if ( level.littleBirds.size >= 4 || ( level.littleBirds.size >= 2 && streakName == "littlebird_flock" ) )
	{
		return true;	
	}
	else
		return false;	
}

playFlareFx()
{
	for ( i = 0; i < 10; i++ )
	{
		if ( !isDefined( self ) )
			return;
		PlayFXOnTag( level._effect[ "ac130_flare" ], self, "TAG_FLARE" );
		wait ( 0.15 );
	}
}


deployFlares() // self == missile target
{
	flareObject = spawn( "script_origin", self.origin );
	flareObject.angles = self.angles;

	flareObject moveGravity( (0, 0, 0), 5.0 );
	
	flareObject thread deleteAfterTime( 5.0 );

	return flareObject;
}


heli_flares_monitor()
{	
	switch( self.heliType )
	{
	case "osprey_gunner":
		self.numFlares = 2;
		break;
	default:
		self.numFlares = 1;
		break;
	}
	
	self thread handleIncomingSAM();
	self thread handleIncomingStinger();
}

handleIncomingStinger()
{
	level endon ( "game_ended" );
	self endon ( "death" );
	self endon ( "crashing" );
	self endon ( "leaving" );
	self endon ( "helicopter_done" );	

	for ( ;; )
	{
		level waittill ( "stinger_fired", player, missile, lockTarget );
		
		if ( !IsDefined( lockTarget ) || (lockTarget != self) )
			continue;
		
		missile thread watchStingerProximity( player, player.team, lockTarget );
	}	
}

watchStingerProximity( player, missileTeam, missileTarget ) // self == missile
{
	self endon ( "death" );

	while( true )
	{
		if ( !isDefined( missileTarget ) )
			break;
			
		center = missileTarget GetPointInBounds( 0, 0, 0 );

		curDist = distance( self.origin, center );

		if ( curDist < 4000 && missileTarget.numFlares > 0 )
		{
			missileTarget.numFlares--;			

			missileTarget thread playFlareFx();	
			newTarget = missileTarget deployFlares();
			self Missile_SetTargetEnt( newTarget );	
			return;
		}		
		wait ( 0.05 );
	}	
}

handleIncomingSAM( functionOverride )
{
	level endon ( "game_ended" );
	self endon ( "death" );
	self endon ( "crashing" );
	self endon ( "leaving" );
	self endon ( "helicopter_done" );	

	for ( ;; )
	{
		level waittill ( "sam_fired", player, missileGroup, lockTarget );

		if ( !IsDefined( lockTarget ) || ( lockTarget != self ) )
			continue;

		if( IsDefined( functionOverride ) )
			level thread [[ functionOverride ]]( player, player.team, lockTarget, missileGroup );
		else
			level thread watchSAMProximity( player, player.team, lockTarget, missileGroup );
	}
}

watchSAMProximity( player, missileTeam, missileTarget, missileGroup ) // self == level
{
	level endon ( "game_ended" );
	missileTarget endon( "death" );

	while( true )
	{
		center = missileTarget GetPointInBounds( 0, 0, 0 );

		curDist = [];
		for( i = 0; i < missileGroup.size; i++ )
		{
			if( IsDefined( missileGroup[ i ] ) )
				curDist[ i ] = distance( missileGroup[ i ].origin, center );
		}

		for( i = 0; i < curDist.size; i++ )
		{
			if( IsDefined( curDist[ i ] ) )
			{
				if ( curDist[ i ] < 4000 && missileTarget.numFlares > 0 )
				{
					missileTarget.numFlares--;			

					missileTarget thread playFlareFx();	
					newTarget = missileTarget deployFlares();
					for( j = 0; j < missileGroup.size; j++ )					
					{
						if( IsDefined( missileGroup[ j ] ) )
						{
							missileGroup[ j ] Missile_SetTargetEnt( newTarget );
						}
					}
					return;
				}	
			}
		}
		wait ( 0.05 );
	}	
}

deleteAfterTime( delay )
{
	wait ( delay );
	
	self delete();
}

pavelowMadeSelectionVO()
{
	self endon( "death" );
	self endon( "disconnect" );

	self PlayLocalSound( game[ "voice" ][ self.team ] + "KS_hqr_pavelow" );
	wait( 3.5 );
	self PlayLocalSound( game[ "voice" ][ self.team ] + "KS_pvl_inbound" );
}