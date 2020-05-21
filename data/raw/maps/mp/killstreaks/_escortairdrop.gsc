#include maps\mp\_utility;
#include common_scripts\utility;
#include maps\mp\gametypes\_hud_util;


init()
{		
	level.ospreySettings = [];

	level.ospreySettings[ "escort_airdrop" ] = SpawnStruct();
	level.ospreySettings[ "escort_airdrop" ].vehicle =			"osprey_mp";
	level.ospreySettings[ "escort_airdrop" ].modelBase =		"vehicle_v22_osprey_body_mp";
	level.ospreySettings[ "escort_airdrop" ].modelBlades =		"vehicle_v22_osprey_blades_mp";
	level.ospreySettings[ "escort_airdrop" ].tagHatchL =		"tag_le_door_attach";
	level.ospreySettings[ "escort_airdrop" ].tagHatchR =		"tag_ri_door_attach";
	level.ospreySettings[ "escort_airdrop" ].tagDropCrates =	"tag_turret_attach";
	level.ospreySettings[ "escort_airdrop" ].prompt =			&"MP_DEFEND_AIRDROP_PACKAGES";
	level.ospreySettings[ "escort_airdrop" ].name =				&"KILLSTREAKS_ESCORT_AIRDROP";
	level.ospreySettings[ "escort_airdrop" ].weaponInfo =		"osprey_minigun_mp";
	level.ospreySettings[ "escort_airdrop" ].heliType =			"osprey";
	level.ospreySettings[ "escort_airdrop" ].dropType =			"airdrop_escort";
	level.ospreySettings[ "escort_airdrop" ].maxHealth =		level.heli_maxhealth * 2;
	level.ospreySettings[ "escort_airdrop" ].timeOut =			60.0;

	//* no osprey on Wii
	/*level.ospreySettings[ "osprey_gunner" ] = SpawnStruct();
	level.ospreySettings[ "osprey_gunner" ].vehicle =			"osprey_player_mp";
	level.ospreySettings[ "osprey_gunner" ].modelBase =			"vehicle_v22_osprey_body_mp";
	level.ospreySettings[ "osprey_gunner" ].modelBlades =		"vehicle_v22_osprey_blades_mp";
	level.ospreySettings[ "osprey_gunner" ].tagHatchL =			"tag_le_door_attach";
	level.ospreySettings[ "osprey_gunner" ].tagHatchR =			"tag_ri_door_attach";
	level.ospreySettings[ "osprey_gunner" ].tagDropCrates =		"tag_turret_attach";
	level.ospreySettings[ "osprey_gunner" ].prompt =			&"MP_DEFEND_AIRDROP_PACKAGES";
	level.ospreySettings[ "osprey_gunner" ].name =				&"KILLSTREAKS_OSPREY_GUNNER";
	level.ospreySettings[ "osprey_gunner" ].weaponInfo =		"osprey_player_minigun_mp";
	level.ospreySettings[ "osprey_gunner" ].heliType =			"osprey_gunner";
	level.ospreySettings[ "osprey_gunner" ].dropType =			"airdrop_osprey_gunner";
	level.ospreySettings[ "osprey_gunner" ].maxHealth =			level.heli_maxhealth * 2;
	level.ospreySettings[ "osprey_gunner" ].timeOut =			75.0;
	*/
	foreach ( ospreyInfo in level.ospreySettings )
	{
		PrecacheVehicle( ospreyInfo.vehicle );
		PreCacheItem( ospreyInfo.weaponInfo );
		PreCacheModel( ospreyInfo.modelBase );	
		PreCacheModel( ospreyInfo.modelBlades );	
		PreCacheString( ospreyInfo.prompt );
		PreCacheString( ospreyInfo.name );

		level.chopper_fx["explode"]["death"][ ospreyInfo.modelBase ] =					LoadFX( "explosions/helicopter_explosion" );
		level.chopper_fx["explode"]["air_death"][ ospreyInfo.modelBase ] =				LoadFX( "explosions/helicopter_explosion_osprey_air_mp" );

		level.chopper_fx["anim"]["blades_anim_up"][ ospreyInfo.modelBase ] =			LoadFX( "props/osprey_blades_anim_up" );
		level.chopper_fx["anim"]["blades_anim_down"][ ospreyInfo.modelBase ] =			LoadFX( "props/osprey_blades_anim_down" );
		level.chopper_fx["anim"]["blades_static_up"][ ospreyInfo.modelBase ] =			LoadFX( "props/osprey_blades_up" );
		level.chopper_fx["anim"]["blades_static_down"][ ospreyInfo.modelBase ] =		LoadFX( "props/osprey_blades_default" );	

		level.chopper_fx["anim"]["hatch_left_static_up"][ ospreyInfo.modelBase ] =		LoadFX( "props/osprey_bottom_door_left_default" );
		level.chopper_fx["anim"]["hatch_left_anim_down"][ ospreyInfo.modelBase ] =		LoadFX( "props/osprey_bottom_door_left_anim_open" );
		level.chopper_fx["anim"]["hatch_left_static_down"][ ospreyInfo.modelBase ] =	LoadFX( "props/osprey_bottom_door_left_up" );
		level.chopper_fx["anim"]["hatch_left_anim_up"][ ospreyInfo.modelBase ] =		LoadFX( "props/osprey_bottom_door_left_anim_close" );

		level.chopper_fx["anim"]["hatch_right_static_up"][ ospreyInfo.modelBase ] =		LoadFX( "props/osprey_bottom_door_right_default" );
		level.chopper_fx["anim"]["hatch_right_anim_down"][ ospreyInfo.modelBase ] =		LoadFX( "props/osprey_bottom_door_right_anim_open" );
		level.chopper_fx["anim"]["hatch_right_static_down"][ ospreyInfo.modelBase ] =	LoadFX( "props/osprey_bottom_door_right_up" );
		level.chopper_fx["anim"]["hatch_right_anim_up"][ ospreyInfo.modelBase ] =		LoadFX( "props/osprey_bottom_door_right_anim_close" );
	}

	//maps\mp\killstreaks\_helicopter::makeHeliType( "osprey", "explosions/helicopter_explosion_cobra_low", ::defaultLightFX );
	//maps\mp\killstreaks\_helicopter::addAirExplosion( "osprey", "explosions/aerial_explosion_cobra_low_mp" );		
		
	level.chopper_fx["smoke"]["signal_smoke_30sec"] = LoadFX( "smoke/signal_smoke_airdrop_30sec" );

	level.air_support_locs = [];
	
	level.killStreakFuncs["escort_airdrop"] = ::tryUseEscortAirdrop;
	level.killStreakFuncs["osprey_gunner"] = ::tryUseOspreyGunner;

/#
	//* Wii: Both Gunner and Escort Rely On This Dvar, But Struct For Gunner Doesn't Exist So Plugging In Value Manually
	SetDevDvarIfUninitialized( "scr_ospreygunner_timeout", 75.0 );
#/
}


tryUseEscortAirdrop( lifeId, kId )
{
	numIncomingVehicles = 1;
	if ( isDefined( self.lastStand ) && !self _hasPerk( "specialty_finalstand" ) )
	{
		self iPrintLnBold( &"MP_UNAVILABLE_IN_LASTSTAND" );
		return false;
	}
	else if ( isDefined( level.civilianJetFlyBy ) )
	{
		self iPrintLnBold( &"MP_CIVILIAN_AIR_TRAFFIC" );
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
	else if ( self isUsingRemote() )
	{
		return false;
	}		
	
	/#
	heightEnt = GetEnt( "airstrikeheight", "targetname" );
	assertEx( isDefined( heightEnt ), "NO HEIGHT ENT IN LEVEL:  Don't know what this means, ask Ned or Jordan" );
	
	if ( !isDefined(heightEnt) )
		return false;
	#/
	
	if ( self isAirDenied() )
	{
		return false;
	}
	
	if ( self isEMPed() )
	{
		return false;
	}
		
	// increment the faux vehicle count before we spawn the vehicle so no other vehicles try to spawn
	incrementFauxVehicleCount();

/#
	// let bots use the full functionality of the killstreak usage	
	if( IsDefined( self.pers[ "isBot" ] ) && self.pers[ "isBot" ] )
		return true;
#/

	//	select location  
	result = self maps\mp\killstreaks\_airdrop::beginAirdropViaMarker( lifeId, kID, "escort_airdrop" );
	if ( !isDefined( result ) || !result )
	{
		self notify( "markerDetermined" );

		// decrement the faux vehicle count since this failed to spawn
		decrementFauxVehicleCount();

		return false;
	}
	
	self maps\mp\_matchdata::logKillstreakEvent( "escort_airdrop", self.origin );

	return true;
}

tryUseOspreyGunner( lifeId, kId )
{
	numIncomingVehicles = 1;
	if ( isDefined( self.lastStand ) && !self _hasPerk( "specialty_finalstand" ) )
	{
		self iPrintLnBold( &"MP_UNAVILABLE_IN_LASTSTAND" );
		return false;
	}
	else if ( isDefined( level.civilianJetFlyBy ) )
	{
		self iPrintLnBold( &"MP_CIVILIAN_AIR_TRAFFIC" );
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
	else if ( self isUsingRemote() )
	{
		return false;
	}		
	
	/#
	heightEnt = GetEnt( "airstrikeheight", "targetname" );
	assertEx( isDefined( heightEnt ), "NO HEIGHT ENT IN LEVEL:  Don't know what this means, ask Ned or Jordan" );
	
	if ( !isDefined(heightEnt) )
		return false;
	#/
	
	if ( self isAirDenied() )
	{
		return false;
	}
	
	if ( self isEMPed() )
	{
		return false;
	}
		
	// increment the faux vehicle count before we spawn the vehicle so no other vehicles try to spawn
	incrementFauxVehicleCount();

	//	select location
	result = self selectDropLocation( lifeId, "osprey_gunner", "compass_objpoint_osprey_friendly", "compass_objpoint_osprey_enemy", &"MP_SELECT_MOBILE_MORTAR_LOCATION" );	
	if ( !isDefined( result ) || !result )
	{
		// decrement the faux vehicle count since this failed to spawn
		decrementFauxVehicleCount();

		return false;
	}
	
	self maps\mp\_matchdata::logKillstreakEvent( "osprey_gunner", self.origin );

	return true;
}

finishSupportEscortUsage( lifeId, location, directionYaw, ospreyType )
{
	self notify( "used" );
	
	direction = ( 0, directionYaw, 0 );
	planeHalfDistance = 12000;
	
	heightEnt = GetEnt( "airstrikeheight", "targetname" );
	
	flyHeight = heightEnt.origin[2];

	startNode = level.heli_start_nodes[ randomInt( level.heli_start_nodes.size ) ];
	pathStart = startNode.origin;
	//pathStart = location + ( AnglesToForward( direction ) * ( -1 * planeHalfDistance ) );
	//pathStart += (0,0,flyHeight);
	
	pathGoal = (location[0], location[1], flyHeight);
	//pathGoal = location + (0,0,flyHeight);	

	pathEnd = location + ( AnglesToForward( direction ) * planeHalfDistance );
	forward = vectorToAngles( pathGoal - pathStart );	

	guardPosition = location;
	location = (location[0], location[1], flyHeight);

	airShip = createAirship( self, lifeId, pathStart, forward, location, ospreyType );
		
	pathStart = startNode;
	self useSupportEscortAirdrop( lifeId, airShip, pathStart, pathGoal, pathEnd, flyHeight, guardPosition );
}

finishOspreyGunnerUsage( lifeId, location, directionYaw, ospreyType )
{
	self notify( "used" );
	
	direction = ( 0, directionYaw, 0 );
	planeHalfDistance = 12000;
	
	heightEnt = GetEnt( "airstrikeheight", "targetname" );
	
	flyHeight = heightEnt.origin[2];

	startNode = level.heli_start_nodes[ randomInt( level.heli_start_nodes.size ) ];
	pathStart = startNode.origin;
	//pathStart = location + ( AnglesToForward( direction ) * ( -1 * planeHalfDistance ) );
	//pathStart += (0,0,flyHeight);
	
	pathGoal = (location[0], location[1], flyHeight);	
	//pathGoal = location + (0,0,flyHeight);	

	pathEnd = location + ( AnglesToForward( direction ) * planeHalfDistance );
	forward = vectorToAngles( pathGoal - pathStart );	

	location = (location[0], location[1], flyHeight);

	airShip = createAirship( self, lifeId, pathStart, forward, location, ospreyType );
		
	pathStart = startNode;
	self useOspreyGunner( lifeId, airShip, pathStart, pathGoal, pathEnd, flyHeight );
}

stopSelectionWatcher()
{
	self waittill( "stop_location_selection", reason );
	
	switch( reason )
	{
	case "cancel_location":
	case "death":
	case "disconnect":
	case "emp":
		self notify ( "customCancelLocation" );	
		break;
	}
}

selectDropLocation( lifeId, ospreyType, icon_friendly, icon_enemy, instruction_text )
{	
	self endon( "customCancelLocation" );
	
	locIndex = undefined;	
	targetSize = level.mapSize / 6.46875; // 138 in 720
	
	if ( level.splitscreen )
		targetSize *= 1.5;
	
	self _beginLocationSelection( ospreyType, "map_artillery_selector", false, 500 );	
	
	self thread stopSelectionWatcher();
	self waittill( "confirm_location", location, directionYaw );
	self stopLocationSelection( false );
	
	//	init rideable killstreak
	self setUsingRemote( ospreyType );
	result = self maps\mp\killstreaks\_killstreaks::initRideKillstreak( ospreyType );
	
	if ( result != "success" )
	{
		if ( result != "disconnect" )
			self clearUsingRemote();

		return false;
	}
	
	if( isDefined( level.chopper ) )
	{
		self clearUsingRemote();
		self iPrintLnBold( &"MP_AIR_SPACE_TOO_CROWDED" );
		return false;
	}
	else if( currentActiveVehicleCount() >= maxVehiclesAllowed() || level.fauxVehicleCount >= maxVehiclesAllowed() )
	{
		self clearUsingRemote();
		self iPrintLnBold( &"MP_TOO_MANY_VEHICLES" );
		return false;
	}		

	
	self thread finishOspreyGunnerUsage( lifeId, location, directionYaw, ospreyType );
	
	return true;
}

showIcons( icon_friendly, icon_enemy, instruction_text, num_icons )
{
	msg = self maps\mp\gametypes\_hud_util::createFontString( "bigfixed", 0.5 );
	msg maps\mp\gametypes\_hud_util::setPoint( "CENTER", "CENTER", 0 , -150 );
	msg setText( instruction_text );	
	
	self.locationObjectives = [];
	
	for ( i=0; i<num_icons; i++ )
	{
		self.locationObjectives[i] = maps\mp\gametypes\_gameobjects::getNextObjID();	
		objective_add( self.locationObjectives[i], "invisible", (0,0,0) );
		objective_position( self.locationObjectives[i], level.air_support_locs[level.script][i]["origin"] );
		objective_state( self.locationObjectives[i], "active" );
		objective_player( self.locationObjectives[i], self getEntityNumber() );
		if ( level.air_support_locs[level.script][i]["in_use"] == true )
			objective_icon( self.locationObjectives[i], icon_enemy );
		else
			objective_icon( self.locationObjectives[i], icon_friendly );			
	}
	
	self waittill_any( "cancel_location", "picked_location", "stop_location_selection" );
	
	msg destroyElem();
	for ( i=0; i<num_icons; i++ )
	{
		_objective_delete( self.locationObjectives[i] );
	}	
}

createAirship( owner, lifeId, pathStart, forward, locIndex, ospreyType )
{	
	//	main body
	airShip = spawnHelicopter( owner, pathStart, forward, level.ospreySettings[ ospreyType ].vehicle, level.ospreySettings[ ospreyType ].modelBase );
	if ( !isDefined( airShip ) )	
		return undefined;
		
	airShip.ospreyType = ospreyType;

	//	state vars
	// NOTE: this heli_type thing is stupid, we should just be using the killstreak name, whomever set up the _helicopter.gsc messed up by adding this
	airShip.heli_type = level.ospreySettings[ ospreyType ].modelBase;

	airShip.heliType = level.ospreySettings[ ospreyType ].heliType;
	airShip.attractor = Missile_CreateAttractorEnt( airShip, level.heli_attract_strength, level.heli_attract_range );	
	airShip.lifeId = lifeId;
	airShip.team = owner.pers["team"];
	airShip.pers["team"] = owner.pers["team"];	
	airShip.owner = owner;
	airShip.maxhealth = level.ospreySettings[ ospreyType ].maxHealth;
	airShip.zOffset = (0,0,0);
	airShip.targeting_delay = level.heli_targeting_delay;
	airShip.primaryTarget = undefined;
	airShip.secondaryTarget = undefined;
	airShip.attacker = undefined;
	airShip.currentstate = "ok";	
	airShip.dropType = level.ospreySettings[ ospreyType ].dropType;
	
	level.chopper = airShip;	
	airShip maps\mp\killstreaks\_helicopter::addToHeliList();
	
	//airShip thread maps\mp\killstreaks\_helicopter::defaultLightFX();
	airShip thread maps\mp\killstreaks\_helicopter::heli_flares_monitor();	
	airShip thread maps\mp\killstreaks\_helicopter::heli_leave_on_disconnect( owner );
	airShip thread maps\mp\killstreaks\_helicopter::heli_leave_on_changeTeams( owner );
	airShip thread maps\mp\killstreaks\_helicopter::heli_leave_on_gameended( owner );
	lifeSpan = level.ospreySettings[ ospreyType ].timeOut;
/#
	lifeSpan = GetDvarFloat( "scr_ospreygunner_timeout" );
#/
	airShip thread maps\mp\killstreaks\_helicopter::heli_leave_on_timeout( lifeSpan );
	airShip thread maps\mp\killstreaks\_helicopter::heli_damage_monitor();
	airShip thread maps\mp\killstreaks\_helicopter::heli_health();
	airShip thread maps\mp\killstreaks\_helicopter::heli_existance();
	airShip thread airshipFX();

	if( ospreyType == "escort_airdrop" )
	{
		killCamOrigin = ( airShip.origin + ( ( AnglesToForward( airShip.angles ) * -200 ) + ( AnglesToRight( airShip.angles ) * -200 )  ) ) + ( 0, 0, 200 );
		airShip.killCamEnt = Spawn( "script_model", killCamOrigin );
		airShip.killCamEnt LinkTo( airShip, "tag_origin" );
	}

	return airShip;	
}

airshipFX()
{
	self endon( "death" );

	// spacing these out with waits to makes sure they play after the airship is completely ready
	//	static rotors and back hatch
	wait( 0.05 );
	PlayFXOnTag( level.chopper_fx["anim"]["blades_static_down"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, "TAG_BLADES_ATTACH" );	
	wait( 0.05 );
	PlayFXOnTag( level.chopper_fx["anim"]["hatch_left_static_up"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchL );		
	wait( 0.05 );
	PlayFXOnTag( level.chopper_fx["anim"]["hatch_right_static_up"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchR );		

	wait( 0.05 );
	// lights
	PlayFXOnTag( level.chopper_fx["light"]["belly"], self, "tag_light_belly" );
	wait( 0.05 );
	PlayFXOnTag( level.chopper_fx["light"]["tail"], self, "tag_light_tail" );
}

useSupportEscortAirdrop( lifeId, airShip, pathStart, pathGoal, pathEnd, flyHeight, guardPosition )
{
	// behavior	
	airShip thread airshipFlyDefense( self, pathStart, pathGoal, pathEnd, flyHeight, guardPosition );
}

useOspreyGunner( lifeId, airShip, pathStart, pathGoal, pathEnd, flyHeight )
{
	// manage gunner	
	self thread rideGunner( lifeId, airShip );

	// behavior	
	airShip thread airshipFlyGunner( self, pathStart, pathGoal, pathEnd, flyHeight );
}

rideGunner( lifeId, airShip )
{
	self endon ( "disconnect" );
	airShip endon ( "helicopter_done" );

	thread teamPlayerCardSplash( "used_osprey_gunner", self );
	self _giveWeapon( "heli_remote_mp" );
	self SwitchToWeapon( "heli_remote_mp" );	
	if ( getDvarInt( "camera_thirdPerson" ) )
		self setThirdPersonDOF( false );		

	airShip VehicleTurretControlOn( self );

	//	link camera			
	// NOTE: the arc values don't work here when passed in to PlayerLinkWeaponViewToDelta, set them in the osprey_player_mp gdt entry
	self PlayerLinkWeaponViewToDelta( airship, "tag_player", 1.0, 0, 0, 0, 0, true );	
	self setPlayerAngles( airship getTagAngles( "tag_player" ) );	
	
	//	weapon
	airShip thread maps\mp\killstreaks\_helicopter::heli_targeting();
	self thread maps\mp\killstreaks\_helicopter::weaponLockThink( airShip );
	
	//	unity
	airShip.gunner = self;	
	self.heliRideLifeId = lifeId;	
	self thread endRideOnAirshipDone( airShip );	

	// with the way we do visionsets we need to wait for the clearRideIntro() is done before we set thermal
	self thread waitSetThermal( 1.0, airShip );

	//	fire
	while ( true )
	{
		airShip waittill( "turret_fire" );			
		airShip fireWeapon();	
		earthquake (0.2, 1, airShip.origin, 1000);
	}
}
	
waitSetThermal( delay, airShip )
{
	self endon( "disconnect" );
	airShip endon( "death" );

	wait( delay	);

	self VisionSetThermalForPlayer( level.ac130.enhanced_vision, 0 );
	self ThermalVisionOn();
	self ThermalVisionFOFOverlayOn();
	self thread maps\mp\killstreaks\_helicopter::thermalVision( airShip );
}

showDefendPrompt( airShip )
{
	self endon ( "disconnect" );
	airShip endon ( "helicopter_done" );	
	
	self.escort_prompt = self maps\mp\gametypes\_hud_util::createFontString( "bigfixed", 1.5 );
	self.escort_prompt setPoint( "CENTER", "CENTER", 0 , -150 );
	self.escort_prompt setText( level.ospreySettings[ airShip.ospreyType ].prompt );	
	
	wait( 6 );
	
	if ( isDefined( self.escort_prompt ) )
		self.escort_prompt destroyElem();
}	
	
airShipPitchPropsUp()
{
	self endon( "crashing" );
	self endon( "death" );
	
	StopFXOnTag( level.chopper_fx["anim"]["blades_static_down"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, "TAG_BLADES_ATTACH" );	
	PlayFXOnTag( level.chopper_fx["anim"]["blades_anim_up"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, "TAG_BLADES_ATTACH" );
	wait( 1.0 );
	if ( isDefined( self ) )
		PlayFXOnTag( level.chopper_fx["anim"]["blades_static_up"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, "TAG_BLADES_ATTACH" );	
}	

airShipPitchPropsDown()
{
	self endon( "crashing" );
	self endon( "death" );
	
	StopFXOnTag( level.chopper_fx["anim"]["blades_static_up"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, "TAG_BLADES_ATTACH" );	
	PlayFXOnTag( level.chopper_fx["anim"]["blades_anim_down"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, "TAG_BLADES_ATTACH" );
	wait( 1.0 );
	if ( isDefined( self ) )
		PlayFXOnTag( level.chopper_fx["anim"]["blades_static_down"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, "TAG_BLADES_ATTACH" );	
}

airShipPitchHatchUp()
{
	self endon( "crashing" );
	self endon( "death" );
	
	StopFXOnTag( level.chopper_fx["anim"]["hatch_left_static_down"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchL );
	PlayFXOnTag( level.chopper_fx["anim"]["hatch_left_anim_up"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchL );
	StopFXOnTag( level.chopper_fx["anim"]["hatch_right_static_down"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchR );
	PlayFXOnTag( level.chopper_fx["anim"]["hatch_right_anim_up"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchR );
	wait( 1.0 );
	if ( isDefined( self ) )
	{
		PlayFXOnTag( level.chopper_fx["anim"]["hatch_left_static_up"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchL );
		PlayFXOnTag( level.chopper_fx["anim"]["hatch_right_static_up"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchR );
	}
}

airShipPitchHatchDown()
{
	self endon( "crashing" );
	self endon( "death" );
	
	StopFXOnTag( level.chopper_fx["anim"]["hatch_left_static_up"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchL );
	PlayFXOnTag( level.chopper_fx["anim"]["hatch_left_anim_down"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchL );
	StopFXOnTag( level.chopper_fx["anim"]["hatch_right_static_up"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchR );
	PlayFXOnTag( level.chopper_fx["anim"]["hatch_right_anim_down"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchR );
	wait( 1.0 );	
	if ( isDefined( self ) )
	{
		PlayFXOnTag( level.chopper_fx["anim"]["hatch_left_static_down"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchL );
		PlayFXOnTag( level.chopper_fx["anim"]["hatch_right_static_down"][ level.ospreySettings[ self.ospreyType ].modelBase ], self, level.ospreySettings[ self.ospreyType ].tagHatchR );
	}
	self notify( "hatch_down" );
}

getBestHeight( centerPoint )
{
	self endon ( "helicopter_removed" );
	self endon ( "heightReturned" );
	
	heightEnt = GetEnt( "airstrikeheight", "targetname" );
	
	if ( isDefined( heightEnt ) )
		trueHeight = heightEnt.origin[2];
	else if( isDefined( level.airstrikeHeightScale ) )
		trueHeight = 850 * level.airstrikeHeightScale;
	else
		trueHeight = 850;
	
	// default the best height to the true height until the checks below, this fixes an undefined bug in the airshipFlyDefense() and airshipFlyGunner() functions
	self.bestHeight = trueHeight;

	bestHeight = 200;
	offset = 0;
	offset2 = 0;
	
	for( i = 0; i < 125; i++ )
	{
		wait( 0.05 );
		
		turn = i % 8; 
		
		globalOffset = i*3;
		
		switch ( turn )
		{
		case 0:
			offset = globalOffset;
			offset2 = globalOffset;
			break;
		case 1:
			offset = globalOffset * -1;
			offset2 = globalOffset * -1;
			break;
		case 2:
			offset = globalOffset * -1;
			offset2 = globalOffset;
			break;
		case 3:
			offset = globalOffset;
			offset2 = globalOffset * -1;
			break;
		case 4:
			offset = 0;
			offset2 = globalOffset * -1;
			break;
		case 5:
			offset = globalOffset * -1;
			offset2 = 0;
			break;
		case 6:
			offset = globalOffset;
			offset2 = 0;
			break;
		case 7:
			offset = 0;
			offset2 = globalOffset;
			break;	
		
		default:
			break;
		}
		
		trace = BulletTrace( centerPoint + (offset, offset2, 1000), centerPoint + (offset, offset2,-10000), true, self );		
		
/#
		//self thread drawLine( (centerPoint + (offset, offset2, 1000)), (centerPoint + (offset, offset2,-10000)), 120 );
#/		
		if ( trace["position"][2] > bestHeight )
		{
			bestHeight = trace["position"][2];
/#
			//self thread drawLine( centerPoint, trace["position"], 120 );
#/
		}
	}
	
	self.bestHeight = bestHeight + 300;
/#
	//self thread drawLine( centerPoint, ( centerPoint[0], centerPoint[1], self.bestHeight ), 120 );
#/
}

/#	
drawLine( start, end, timeSlice )
{
	drawTime = int(timeSlice * 15);
	for( time = 0; time < drawTime; time++ )
	{
		line( start, end, (1,0,0),false, 1 );
		wait ( 0.05 );
	}
}
#/
	

airshipFlyDefense( owner, pathStart, pathGoal, pathEnd, flyHeight, guardPosition )
{
	self notify( "airshipFlyDefense");
	self endon( "airshipFlyDefense" );
	self endon ( "helicopter_removed" );
	self endon ( "death" );
	
	// go to where the user selected to drop the packages
	self thread getBestHeight( pathGoal );

	// use the helicopter entrance to avoid collisions with things
	self maps\mp\killstreaks\_helicopter::heli_fly_simple_path( pathStart );

	// store this for the rise and leave
	self.pathGoal = pathGoal;

	dropForward = self.angles;			
	
	//self Vehicle_SetSpeedImmediate( 75, 50, 50 );
	self SetYawSpeed( 30, 30, 30, .3 );
	
	curOrg = self.origin;
	yaw = self.angles[1];
	forward = self.angles[0];
	//pathGoal += AnglesToForward( (0,yaw,0) )* 1.02;
	
	self.timeOut = level.ospreySettings[ self.ospreyType ].timeOut;
	self setVehGoalPos( pathGoal, 1 );		
	startTime = GetTime();
	self waittill ( "goal" );	
	endTime = ( GetTime() - startTime ) * 0.001;
	self.timeOut -= endTime;
	
	//	pitch props up
	self thread airShipPitchPropsUp();
	
	dropPos = pathGoal * (1,1,0);
	dropPos += (0,0,self.bestHeight);
	
	self Vehicle_SetSpeed( 25, 10, 10 );
	self SetYawSpeed( 20, 10, 10, .3 );
	
	self setVehGoalPos( dropPos, 1 );		
	startTime = GetTime();
	self waittill ( "goal" );	
	endTime = ( GetTime() - startTime ) * 0.001;
	self.timeOut -= endTime;
	
	self SetHoverParams( 65, 50, 50 );
	self ospreyDropCratesLowImpulse( 1, level.ospreySettings[ self.ospreyType ].tagDropCrates, dropPos );
	
	//thread move about and do stuff and things
	self thread killGuysNearCrates( guardPosition );
	
	////	hang out
	//if ( IsDefined( owner ) )
	//	owner waittill_any_timeout( self.timeOut, "disconnect" );
		
	self waittill( "leaving" );

	self notify( "osprey_leaving" );
	
	////	rise
	//self setVehGoalPos( pathGoal, 1 );	
	//self waittill ( "goal" );	
		
	//	pitch props down
	self thread airShipPitchPropsDown();
	
	//self Vehicle_SetSpeed( 80, 60 );
	//self SetYawSpeed( 180, 180, 180, .3 );
	//
	//// make sure it doesn't fly away backwards
	//endEnt = Spawn( "script_origin", pathEnd );
	//if( IsDefined( endEnt ) )
	//{
	//	self SetLookAtEnt( endEnt );
	//	endEnt thread wait_and_delete( 3.0 );
	//}
	//self setVehGoalPos( (pathEnd + (0,0,1000)) * 4, 1 );
	//wait( 6 );
	//
	//self Vehicle_SetSpeed( 130, 60 );
	//
	//wait( 10 );

	//self delete();
}

wait_and_delete( waitTime )
{
	self endon( "death" );
	level endon( "game_ended" );
	wait( waitTime );
	self delete();
}

killGuysNearCrates( guardPosition )
{
	self endon( "osprey_leaving" );
	self endon ( "helicopter_removed" );
	self endon ( "death" );

	targetCenter = guardPosition;
	//targetCenter =  GetGroundPosition( dropPos, 2, 20000, self.origin[2] );
/#
	//self thread drawLine( dropPos, targetCenter, 120 );
#/
	for( ;; )
	{
		
		foreach( player in level.players )
		{
			wait ( 0.05);
			
			if( !IsDefined( self ) )
				return;
				
			if ( !isDefined( player ) )
				continue;
				
			if ( !isReallyAlive(player) )
				continue;

			if( level.teambased && ( player.team == self.team ) )
				continue;
			
			if( isDefined(self.owner) && ( player == self.owner ) )
				continue;
				
			if( player _hasPerk( "specialty_blindeye" ) )
				continue;
			
			if ( distanceSquared( targetCenter, player.origin ) > 500000 )
				continue;
			
			self thread aiShootPlayer( player, targetCenter );
			
			self waitForConfirmation();
		}
	}
}

aiShootPlayer( targetPlayer, center )
{
	self notify( "aiShootPlayer" );
	self endon( "aiShootPlayer" );
	
	self endon ( "helicopter_removed" );
	self endon ( "leaving" );
	targetPlayer endon( "death" );
	
	self SetTurretTargetEnt( targetPlayer );
	self SetLookAtEnt( targetPlayer );
	
	self thread targetDeathWaiter( targetPlayer );
	
	numShots = 6;
	vollies = 2;
	
	for ( ;; )
	{
		numShots--;
		self FireWeapon( "tag_flash", targetPlayer );
		wait ( .15);
		
		if ( numShots <= 0 )
		{
			vollies--;
			numShots = 6;
			
			if ( distanceSquared( targetPlayer.origin, center ) > 500000 || vollies <= 0 || !isReallyAlive(targetPlayer) )
			{
				self notify ("abandon_target");
				return;
			}
			
			wait (1);
		}
	}
}

targetDeathWaiter( targetPlayer )
{
	self endon ( "abandon_target" );
	self endon ( "leaving" );
	self endon ( "helicopter_removed" );
	
	targetPlayer waittill( "death" );
	self notify( "target_killed" );
}


waitForConfirmation()
{
	self endon ( "helicopter_removed" );
	self endon ( "leaving" );
	self endon ( "target_killed" );
	self endon ( "abandon_target" );
	
	for( ;; )
	{
		wait 0.05;	
	}
		
}

airshipFlyGunner( owner, pathStart, pathGoal, pathEnd, flyHeight )
{
	self notify( "airshipFlyGunner");
	self endon( "airshipFlyGunner" );
	self endon ( "helicopter_removed" );
	self endon ( "death" );
	
	// go to where the user selected to drop the packages
	self thread getBestHeight( pathGoal );

	// use the helicopter entrance to avoid collisions with things
	self maps\mp\killstreaks\_helicopter::heli_fly_simple_path( pathStart );
	self thread maps\mp\killstreaks\_helicopter::heli_leave_on_timeout( level.ospreySettings[ self.ospreyType ].timeOut );

	dropForward = self.angles;			
		
	//self Vehicle_SetSpeedImmediate( 75, 50, 50 );
	self SetYawSpeed( 30, 30, 30, .3 );

	curOrg = self.origin;
	yaw = self.angles[1];
	forward = self.angles[0];
	//pathGoal += ( AnglesToForward( self.angles ) * 1000 );

/#
	//self thread drawLine( pathGoal, NewPathGoal, 120 );
#/
	//leaveTime = 6.0;
	//self.timeOut = level.ospreySettings[ self.ospreyType ].timeOut - leaveTime;
	self.timeOut = level.ospreySettings[ self.ospreyType ].timeOut;

	self setVehGoalPos( pathGoal, 1 );		
	startTime = GetTime();
	self waittill ( "goal" );	
	endTime = ( GetTime() - startTime ) * 0.001;
	self.timeOut -= endTime;

	//	pitch props up
	self thread airShipPitchPropsUp();
	
	dropPos = pathGoal * (1,1,0);
	dropPos += (0,0,self.bestHeight);

	self Vehicle_SetSpeed( 25, 10, 10 );
	self SetYawSpeed( 20, 10, 10, .3 );
	
	self setVehGoalPos( dropPos, 1 );		
	startTime = GetTime();
	self waittill ( "goal" );	
	endTime = ( GetTime() - startTime ) * 0.001;
	self.timeOut -= endTime;
	
	//dropOrigin = self GetTagOrigin( "TAG_DOOR_REAR_ATTACH" );
	self ospreyDropCrates( 1, level.ospreySettings[ self.ospreyType ].tagDropCrates, dropPos );
	
	//	hang out
	waitTime = 1.0;
	if ( IsDefined( owner ) )
		owner waittill_any_timeout( waitTime, "disconnect" );
	self.timeOut -= waitTime;

	//	rise
	self setVehGoalPos( pathGoal, 1 );	
	startTime = GetTime();
	self waittill ( "goal" );	
	endTime = ( GetTime() - startTime ) * 0.001;
	self.timeOut -= endTime;
		
	// circle or use attack areas
	attackAreas = getEntArray( "heli_attack_area", "targetname" );
	loopNode = level.heli_loop_nodes[ randomInt( level.heli_loop_nodes.size ) ];	
	if ( attackAreas.size )
		self thread maps\mp\killstreaks\_helicopter::heli_fly_well( attackAreas );
	else
		self thread maps\mp\killstreaks\_helicopter::heli_fly_loop_path( loopNode );
	//// move towards the center of the map and circle 2 times at 45 degree increments
	//cycles = ( 360 * 2 ) / 45;
	//
	//self SetYawSpeed( 30, 10, 10, .3 );

	////moveForward = AnglesToForward( self.angles ) * -1000;
	////moveToPoint = self.origin + ( moveForward[0], moveForward[1], 0 );
	//moveToPoint = ( level.mapCenter[0], level.mapCenter[1], self.origin[2] );
	//self setVehGoalPos( moveToPoint, 1 );
	//waitTime = 3.0;
	//wait( waitTime );
	//self.timeOut -= waitTime;
	//
	//waitTime = self.timeOut / cycles;

	//self SetYawSpeed( 20, 10, 10, .3 );

	//for( i = 0; i < cycles; i++ )
	//{
	//	moveForward = AnglesToForward( self.angles ) * 1000;
	//	moveRight = AnglesToRight( self.angles ) * 1000;
	//	moveAngles = moveForward + moveRight;
	//	moveToPoint = self.origin + ( moveAngles[0], moveAngles[1], 0 );
	//	self setVehGoalPos( moveToPoint, 0 );
	//	wait( waitTime );
	//}
	
	self waittill( "leaving" );
	// pitch props down and leave
	self thread airShipPitchPropsDown();
	
	//self Vehicle_SetSpeed( 80, 60 );
	//self SetYawSpeed( 180, 180, 180, .3 );
	//
	//self setVehGoalPos( ( pathEnd + ( 0, 0, 1000 ) ) * 4, 0 );
	//waitTime = leaveTime;
	//wait( waitTime );
	
	//if ( IsDefined( owner ) )
	//{
	//	owner TakeWeapon( "heli_remote_mp" );
	//	self notify( "helicopter_done" );
	//}
	
	//self Vehicle_SetSpeed( 130, 60 );
	//
	//wait( 10 );

	//self delete();
}


ospreyDropCratesLowImpulse( timeBetween, dropFromTag, dropPos )
{
	//	pitch hatch down
	self thread airShipPitchHatchDown();	
	self waittill( "hatch_down" );

	//	drop first crate
	//pathStart = self GetTagOrigin( dropFromTag ) + ( AnglesToForward( self.angles ) * 100 ) + ( 0, 0, 50 );
	//dropImpulse = AnglesToForward( self.angles ) * -200;
	//crateType[0] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( level.osprey_location, self.dropType, dropPos, false, undefined, pathStart, dropImpulse + (randomInt(10),randomInt(10),randomInt(10)) );
	crateType[0] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( undefined, self.dropType, undefined, false, undefined, self.origin, (randomInt(10),randomInt(10),randomInt(10)), undefined, dropFromTag );
	wait( 0.05 );
	self notify( "drop_crate" );
	
	//	drop second create
	wait( timeBetween );
	//pathStart = self GetTagOrigin( dropFromTag ) + ( AnglesToForward( self.angles ) * 100 ) + ( 0, 0, 50 );
	//dropImpulse = AnglesToForward( self.angles ) * -200;
	//crateType[1] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( level.osprey_location, self.dropType, dropPos, false, undefined, pathStart, dropImpulse + (randomInt(20),randomInt(20),randomInt(20)), crateType );
	crateType[1] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( undefined, self.dropType, undefined, false, undefined, self.origin, (RandomInt(100),randomInt(100),randomInt(100)), crateType, dropFromTag );
	wait( 0.05 );
	self notify( "drop_crate" );
	
	//	drop third crate
	wait( timeBetween );	
	//pathStart = self GetTagOrigin( dropFromTag ) + ( AnglesToForward( self.angles ) * 100 ) + ( 0, 0, 50 );
	//dropImpulse = AnglesToForward( self.angles ) * -200;
	//crateType[2] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( level.osprey_location, self.dropType, dropPos, false, undefined, pathStart, dropImpulse + (randomInt(10),randomInt(10),randomInt(10)), crateType );
	crateType[2] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( undefined, self.dropType, undefined, false, undefined, self.origin, (randomInt(50),randomInt(50),randomInt(50)), crateType, dropFromTag );
	wait( 0.05 );
	self notify( "drop_crate" );
	
	//	drop fourth create
	wait( timeBetween );
	//pathStart = self GetTagOrigin( dropFromTag ) + ( AnglesToForward( self.angles ) * 100 ) + ( 0, 0, 50 );
	//dropImpulse = AnglesToForward( self.angles ) * -200;
	//crateType[3] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( level.osprey_location, self.dropType, dropPos, false, undefined, pathStart, dropImpulse + (randomInt(20),randomInt(20),randomInt(20)), crateType );
	crateType[3] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( undefined, self.dropType, undefined, false, undefined, self.origin, (RandomIntRange(-100, 0),RandomIntRange(-100, 0),RandomIntRange(-100, 0)), crateType, dropFromTag );
	wait( 0.05 );
	self notify( "drop_crate" );
	
	//	drop fifth create
	wait( timeBetween );	
	//pathStart = self GetTagOrigin( dropFromTag ) + ( AnglesToForward( self.angles ) * 100 ) + ( 0, 0, 50 );
	//dropImpulse = AnglesToForward( self.angles ) * -200;
	//self thread maps\mp\killstreaks\_airdrop::dropTheCrate( level.osprey_location, self.dropType, dropPos, false, undefined, pathStart, dropImpulse + (randomInt(10),randomInt(10),randomInt(10)), crateType );
	self thread maps\mp\killstreaks\_airdrop::dropTheCrate( undefined, self.dropType, undefined, false, undefined, self.origin, (RandomIntRange(-50, 0),RandomIntRange(-50, 0),RandomIntRange(-50, 0)), crateType, dropFromTag );
	wait( 0.05 );
	self notify( "drop_crate" );	
	
	//	pitch hatch up
	wait( 1.0 );
	self thread airShipPitchHatchUp();
}

ospreyDropCrates( timeBetween, dropFromTag, dropPos )
{
	//	pitch hatch down
	self thread airShipPitchHatchDown();	
	self waittill( "hatch_down" );

	//	drop first crate
	//pathStart = self GetTagOrigin( dropFromTag ) + ( AnglesToForward( self.angles ) * 100 ) + ( 0, 0, 50 );
	//dropImpulse = AnglesToForward( self.angles ) * -200;
	//crateType[0] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( level.osprey_location, self.dropType, dropPos, false, undefined, pathStart, dropImpulse + (randomInt(10),randomInt(10),randomInt(10)) );
	crateType[0] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( undefined, self.dropType, undefined, false, undefined, self.origin, (randomInt(10),randomInt(10),randomInt(10)), undefined, dropFromTag );
	wait( 0.05 );
	self.timeOut -= 0.066;
	self notify( "drop_crate" );
	
	//	drop second create
	wait( timeBetween );
	self.timeOut -= timeBetween;
	//pathStart = self GetTagOrigin( dropFromTag ) + ( AnglesToForward( self.angles ) * 100 ) + ( 0, 0, 50 );
	//dropImpulse = AnglesToForward( self.angles ) * -200;
	//crateType[1] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( level.osprey_location, self.dropType, dropPos, false, undefined, pathStart, dropImpulse + (randomInt(50),randomInt(50),randomInt(50)), crateType );
	crateType[1] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( undefined, self.dropType, undefined, false, undefined, self.origin, (randomInt(100),randomInt(100),randomInt(100)), crateType, dropFromTag );
	wait( 0.05 );
	self.timeOut -= 0.066;
	self notify( "drop_crate" );
	
	//	drop third crate
	wait( timeBetween );	
	self.timeOut -= timeBetween;
	//pathStart = self GetTagOrigin( dropFromTag ) + ( AnglesToForward( self.angles ) * 100 ) + ( 0, 0, 50 );
	//dropImpulse = AnglesToForward( self.angles ) * -200;
	//crateType[2] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( level.osprey_location, self.dropType, dropPos, false, undefined, pathStart, dropImpulse + (randomInt(25),randomInt(25),randomInt(25)), crateType );
	crateType[2] = self thread maps\mp\killstreaks\_airdrop::dropTheCrate( undefined, self.dropType, undefined, false, undefined, self.origin, (randomInt(50),randomInt(50),randomInt(50)), crateType, dropFromTag );
	wait( 0.05 );
	self.timeOut -= 0.066;
	self notify( "drop_crate" );
	
	//	pitch hatch up
	wait( 1.0 );
	self thread airShipPitchHatchUp();
}


endRide( airShip )
{
	if ( isDefined( self.escort_prompt ) )
		self.escort_prompt destroyElem();
	
	self RemoteCameraSoundscapeOff();
	self ThermalVisionOff();
	self ThermalVisionFOFOverlayOff();
	self unlink();
	self clearUsingRemote();
	if ( getDvarInt( "camera_thirdPerson" ) )
		self setThirdPersonDOF( true );
	self visionSetThermalForPlayer( game["thermal_vision"], 0 );
	
	if ( isDefined( airShip ) )
		airShip VehicleTurretControlOff( self );

	self notify ( "heliPlayer_removed" );
	
	self SwitchToWeapon( self getLastWeapon() );
	self TakeWeapon( "heli_remote_mp" );
}	
	
endRideOnAirshipDone( airShip )
{
	self endon ( "disconnect" );
	
	airShip waittill ( "helicopter_done" );

	self endRide( airShip );
}
