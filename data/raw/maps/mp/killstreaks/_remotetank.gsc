#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

PLACEMENT_RADIUS = 25.0;
PLACEMENT_HEIGHT = 25.0;
PLACEMENT_FORWARD_DISTANCE = 50.0;
PLACEMENT_UP_DISTANCE = 40.0;
PLACEMENT_SWEEP_DISTANCE = 80.0;
PLACEMENT_MIN_NORMAL = 0.7;

init()
{
	level.killStreakFuncs[ "remote_tank" ] = ::tryUseRemoteTank;

	level.tankSettings = [];

	level.tankSettings[ "remote_tank" ] = spawnStruct();
	level.tankSettings[ "remote_tank" ].timeOut =				60.0;
	level.tankSettings[ "remote_tank" ].health =				99999; // keep it from dying anywhere in code
	level.tankSettings[ "remote_tank" ].maxHealth =				1000; // this is what we check against for death	
	level.tankSettings[ "remote_tank" ].streakName =			"remote_tank";
	level.tankSettings[ "remote_tank" ].mgTurretInfo =			"ugv_turret_mp";
	//level.tankSettings[ "remote_tank" ].glTurretInfo =			"ugv_gl_turret_mp";
	level.tankSettings[ "remote_tank" ].missileInfo =			"remote_tank_projectile_mp";
	level.tankSettings[ "remote_tank" ].sentryModeOff =			"sentry_offline";	
	level.tankSettings[ "remote_tank" ].vehicleInfo =			"remote_ugv_mp";
	level.tankSettings[ "remote_tank" ].modelBase =				"vehicle_ugv_talon_mp";
	level.tankSettings[ "remote_tank" ].modelMGTurret =			"vehicle_ugv_talon_gun_mp";
	//level.tankSettings[ "remote_tank" ].modelGLTurret =			"vehicle_ugv_talon_gl_mp";
	level.tankSettings[ "remote_tank" ].modelPlacement =		"vehicle_ugv_talon_obj";
	level.tankSettings[ "remote_tank" ].modelPlacementFailed =	"vehicle_ugv_talon_obj_red";
	level.tankSettings[ "remote_tank" ].modelDestroyed =		"vehicle_ugv_talon_mp";	
	level.tankSettings[ "remote_tank" ].stringPlace =			&"MP_REMOTE_TANK_PLACE";	
	level.tankSettings[ "remote_tank" ].stringCannotPlace =		&"MP_REMOTE_TANK_CANNOT_PLACE";	
	level.tankSettings[ "remote_tank" ].laptopInfo =			"killstreak_remote_tank_laptop_mp";
	level.tankSettings[ "remote_tank" ].remoteInfo =			"killstreak_remote_tank_remote_mp";

	makeDvarServerInfo( "ui_remoteTankUseTime", level.tankSettings[ "remote_tank" ].timeOut );
	PrecacheMenu( "remotetank_timer" );

	foreach( tankInfo in level.tankSettings )
	{
		PreCacheModel( tankInfo.modelBase );
		PreCacheModel( tankInfo.modelMGTurret );
		//PreCacheModel( tankInfo.modelGLTurret );
		precacheModel( tankInfo.modelPlacement );		
		precacheModel( tankInfo.modelPlacementFailed );		
		PreCacheModel( tankInfo.modelDestroyed );
		PreCacheTurret( tankInfo.mgTurretInfo );
		//PreCacheTurret( tankInfo.glTurretInfo );
		PrecacheVehicle( tankInfo.vehicleInfo );
		PreCacheString( tankInfo.stringPlace );
		PreCacheString( tankInfo.stringCannotPlace );
		PreCacheItem( tankInfo.laptopInfo );
		PreCacheItem( tankInfo.remoteInfo );
		PreCacheItem( tankInfo.missileInfo );
	}
	
	// TODO: get fx
	level._effect[ "remote_tank_dying" ]			= LoadFX( "explosions/killstreak_explosion_quick" );
	level._effect[ "remote_tank_explode" ]			= LoadFX( "explosions/bouncing_betty_explosion" );
	level._effect[ "remote_tank_spark" ]			= LoadFX( "impacts/large_metal_painted_hit" );
	level._effect[ "remote_tank_antenna_light_mp" ]	= LoadFX( "misc/aircraft_light_red_blink" );
	level._effect[ "remote_tank_camera_light_mp" ]	= LoadFX( "misc/aircraft_light_wingtip_green" );

	level.remote_tank_armor_bulletdamage = 0.5;	// damage multiplier to bullets onto remote tank's armor

/#
	SetDevDvarIfUninitialized( "scr_remotetank_timeout", 60.0 );
#/
}		

tryUseRemoteTank( lifeId )
{ 
	numIncomingVehicles = 1;
	if( !self validateUseStreak() )
	{
		return false;
	}		
	else if( currentActiveVehicleCount() >= maxVehiclesAllowed() || level.fauxVehicleCount + numIncomingVehicles >= maxVehiclesAllowed() )
	{
		self iPrintLnBold( &"MP_TOO_MANY_VEHICLES" );
		return false;
	}		

	// increment the faux vehicle count before we spawn the vehicle so no other vehicles try to spawn
	incrementFauxVehicleCount();

	result = self giveTank( lifeId, "remote_tank" );
	if( result )
	{
		self maps\mp\_matchdata::logKillstreakEvent( "remote_tank", self.origin );
		self thread teamPlayerCardSplash( "used_remote_tank", self );

		// take the killstreak weapons
		self takeKillstreakWeapons( "remote_tank" );
	}
	else
	{
		// decrement the faux vehicle count since this failed to spawn
		decrementFauxVehicleCount();
	}

	// we're done carrying for sure and sometimes this might not get reset
	// this fixes a bug where you could be carrying and have it in a place where it won't plant, get killed, now you can't scroll through killstreaks
	self.isCarrying = false;

	return result;
}

takeKillstreakWeapons( tankType ) // self == owner
{
	killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( level.tankSettings[ tankType ].streakName );
	maps\mp\killstreaks\_killstreaks::takeKillstreakWeaponIfNoDupe( killstreakWeapon );

	self TakeWeapon( level.tankSettings[ tankType ].laptopInfo );
	self TakeWeapon( level.tankSettings[ tankType ].remoteInfo );
}

removePerks()
{
	if ( self _hasPerk( "specialty_explosivebullets" ) )
	{
		self.restorePerk = "specialty_explosivebullets";
		self _unsetPerk( "specialty_explosivebullets" );
	}		
}

restorePerks()
{
	if ( IsDefined( self.restorePerk ) )
	{
		self givePerk( self.restorePerk, false );	
		self.restorePerk = undefined;
	}	
}

waitRestorePerks()
{
	self endon( "death" );
	self endon( "disconnect" );
	level endon( "game_ended" );
	wait( 0.05 );
	self restorePerks();
}

removeWeapons()
{
	// since we're taking your weapons we need to keep track of the ammo for when we restore them
	foreach( weapon in self.weaponlist )
	{
		weaponTokens = StrTok( weapon, "_" );
		if( weaponTokens[0] == "alt" )
		{
			// we don't need to take the alt weapons but we do need to store the ammo for when we restore them
			self.restoreWeaponClipAmmo[ weapon ] = self GetWeaponAmmoClip( weapon );
			self.restoreWeaponStockAmmo[ weapon ] = self GetWeaponAmmoStock( weapon );
			continue;
		}

		self.restoreWeaponClipAmmo[ weapon ] = self GetWeaponAmmoClip( weapon );
		self.restoreWeaponStockAmmo[ weapon ] = self GetWeaponAmmoStock( weapon );
	}

	// now take the weapons
	foreach( weapon in self.weaponlist )
	{
		weaponTokens = StrTok( weapon, "_" );
		if( weaponTokens[0] == "alt" )
			continue;

		self TakeWeapon( weapon );
	}
}

restoreWeapons()
{
	if( !IsDefined( self.restoreWeaponClipAmmo ) ||
		!IsDefined( self.restoreWeaponStockAmmo ) )
		return;

	altWeapons = [];
	foreach( weapon in self.weaponlist )
	{
		weaponTokens = StrTok( weapon, "_" );
		if( weaponTokens[0] == "alt" )
		{
			// we don't need to give the alt weapons but we do need to restore the ammo
			altWeapons[ altWeapons.size ] = weapon;
			continue;
		}

		self _giveWeapon( weapon );
		if( IsDefined( self.restoreWeaponClipAmmo[ weapon ] ) )
			self SetWeaponAmmoClip( weapon, self.restoreWeaponClipAmmo[ weapon ] );
		if( IsDefined( self.restoreWeaponStockAmmo[ weapon ] ) )
			self SetWeaponAmmoStock( weapon, self.restoreWeaponStockAmmo[ weapon ] );
	}

	foreach( altWeapon in altWeapons )
	{
		if( IsDefined( self.restoreWeaponClipAmmo[ altWeapon ] ) )
			self SetWeaponAmmoClip( altWeapon, self.restoreWeaponClipAmmo[ altWeapon ] );
		if( IsDefined( self.restoreWeaponStockAmmo[ altWeapon ] ) )
			self SetWeaponAmmoStock( altWeapon, self.restoreWeaponStockAmmo[ altWeapon ] );
	}

	self.restoreWeaponClipAmmo = undefined;
	self.restoreWeaponStockAmmo = undefined;
}

waitRestoreWeapons()
{
	self endon( "death" );
	self endon( "disconnect" );
	level endon( "game_ended" );
	wait( 0.05 );
	self restoreWeapons();
}

giveTank( lifeId, tankType ) // self == player
{
	tankForPlayer = createTankForPlayer( tankType, self );
	tankForPlayer.lifeId = lifeId;

	//	returning from this streak activation seems to strip this?
	//	manually removing and restoring
	self removePerks();		
	self removeWeapons();

	result = self setCarryingTank( tankForPlayer, true );

	self thread restorePerks();
	self thread restoreWeapons();

	if( !IsDefined( result ) )
		result = false;

	return result;
}

createTankForPlayer( tankType, owner )
{
	assertEx( IsDefined( owner ), "createTankForPlayer() called without owner specified" );

	tank = SpawnTurret( "misc_turret", owner.origin + ( 0, 0, 25 ), level.tankSettings[ tankType ].mgTurretInfo );

	tank.angles = owner.angles;
	tank.tankType = tankType;
	tank.owner = owner;

	tank SetModel( level.tankSettings[ tankType ].modelBase );

	tank MakeTurretInoperable();
	tank SetTurretModeChangeWait( true );
	tank SetMode( "sentry_offline" );
	tank MakeUnusable();
	tank SetSentryOwner( owner );

	return tank;
}

setCarryingTank( tankForPlayer, allowCancel )
{
	self endon ( "death" );
	self endon ( "disconnect" );

	assert( isReallyAlive( self ) );

	tankForPlayer thread tank_setCarried( self );

	self _disableWeapon();

	self notifyOnPlayerCommand( "place_tank", "+attack" );
	self notifyOnPlayerCommand( "place_tank", "+attack_akimbo_accessible" ); // support accessibility control scheme
	self notifyOnPlayerCommand( "cancel_tank", "+actionslot 4" );

	while( true )
	{
		result = waittill_any_return( "place_tank", "cancel_tank", "force_cancel_tank" );

		if ( result == "cancel_tank" || result == "force_cancel_tank" )
		{
			if ( !allowCancel && result == "cancel_tank" )
				continue;

			// failsafe because something takes away the killstreak weapon on occasions where you have them stacked in the gimme slot
			//	for example, if you stack uav, sam turret, emp and then use the emp, then pull out the sam turret, the list item weapon gets taken away before you plant it
			//	so to "fix" this, if the user cancels then we give the weapon back to them only if the selected killstreak is the same and the item list is zero
			//	this is done for anything you can pull out and plant (ims, sentry, sam turret, remote turret, remote tank)
			if( result == "cancel_tank" )
			{
				killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( level.tankSettings[ tankForPlayer.tankType ].streakName );
				if( IsDefined( self.killstreakIndexWeapon ) && 
					killstreakWeapon == maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( self.pers["killstreaks"][self.killstreakIndexWeapon].streakName ) &&
					!( self GetWeaponsListItems() ).size )
				{
					self _giveWeapon( killstreakWeapon, 0 );
					self _setActionSlot( 4, "weapon", killstreakWeapon );
				}
			}

			tankForPlayer tank_setCancelled();
			self _enableWeapon();
			return false;
		}

		if ( !tankForPlayer.canBePlaced )
			continue;

		tankForPlayer thread tank_setPlaced();		
		self _enableWeapon();		
		return true;
	}
}

tank_setCarried( carrier ) // self == tankForPlayer
{
	assert( isPlayer( carrier ) );
	assertEx( carrier == self.owner, "tank_setCarried() specified carrier does not own this ims" );

	self SetModel( level.tankSettings[ self.tankType ].modelPlacement );

	self SetSentryCarrier( carrier );
	self SetContents( 0 );
	self SetCanDamage( false );

	self.carriedBy = carrier;
	carrier.isCarrying = true;

	carrier thread updateTankPlacement( self );

	self thread tank_onCarrierDeath( carrier );
	self thread tank_onCarrierDisconnect( carrier );
	self thread tank_onGameEnded();

	self notify ( "carried" );
}

updateTankPlacement( tank )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );

	tank endon ( "placed" );
	tank endon ( "death" );

	tank.canBePlaced = true;
	lastCanPlaceTank = -1; // force initial update

	while( true )
	{
		placement = self CanPlayerPlaceTank( PLACEMENT_RADIUS, PLACEMENT_HEIGHT, PLACEMENT_FORWARD_DISTANCE, PLACEMENT_UP_DISTANCE, PLACEMENT_SWEEP_DISTANCE, PLACEMENT_MIN_NORMAL );

		tank.origin = placement[ "origin" ];
		tank.angles = placement[ "angles" ];
		tank.canBePlaced = self isOnGround() && placement[ "result" ] && ( abs( placement[ "origin" ][2] - self.origin[2] ) < 20 );

		if( tank.canBePlaced != lastCanPlaceTank )
		{
			if( tank.canBePlaced )
			{
				tank SetModel( level.tankSettings[ tank.tankType ].modelPlacement );
				if ( self.team != "spectator" )
					self ForceUseHintOn( level.tankSettings[ tank.tankType ].stringPlace );
			}
			else
			{
				tank SetModel( level.tankSettings[ tank.tankType ].modelPlacementFailed );
				if ( self.team != "spectator" )
					self ForceUseHintOn( level.tankSettings[ tank.tankType ].stringCannotPlace );
			}
		}

		lastCanPlaceTank = tank.canBePlaced;		
		wait ( 0.05 );
	}
}

tank_onCarrierDeath( carrier ) // self == tankForPlayer
{
	self endon ( "placed" );
	self endon ( "death" );

	carrier waittill ( "death" );

	self tank_setCancelled();
}


tank_onCarrierDisconnect( carrier ) // self == tankForPlayer
{
	self endon ( "placed" );
	self endon ( "death" );

	carrier waittill ( "disconnect" );

	self tank_setCancelled();
}

tank_onGameEnded( carrier ) // self == tankForPlayer
{
	self endon ( "placed" );
	self endon ( "death" );

	level waittill ( "game_ended" );

	self tank_setCancelled();
}

tank_setCancelled() // self == tankForPlayer
{
	if( IsDefined( self.carriedBy ) )
		self.carriedBy forceUseHintOff();

	if( IsDefined( self.owner ) )
		self.owner.isCarrying = false;

	self delete();
}

tank_setPlaced() // self == tankForPlayer
{
	self endon( "death" );
	level endon( "game_ended" );

	self notify ( "placed" );
	self.carriedBy forceUseHintOff();
	self.carriedBy = undefined;

	if( !IsDefined( self.owner ) )
		return false;

	owner = self.owner;

	owner.isCarrying = false;

	//owner freezeControlsWrapper( true );
	//result = owner maps\mp\killstreaks\_killstreaks::initRideKillstreak();
	//owner freezeControlsWrapper( false );
	//if( result != "success" )
	//{
	//	if ( result != "disconnect" && owner isUsingRemote() )
	//		owner clearUsingRemote();

	//	self tank_setCancelled();
	//	owner _enableWeapon();

	//	return false;
	//}	

	tank = createTank( self );
	if( !IsDefined( tank ) )
		return false;		

	// TODO: get sound for this
	tank playSound( "sentry_gun_plant" );

	tank notify ( "placed" );
	tank thread tank_setActive();

	self delete();
}

tank_giveWeaponOnPlaced() // self == tank
{
	self endon( "death" );
	level endon( "game_ended" );

	if( !IsDefined( self.owner ) )
		return;

	owner = self.owner;
	owner endon( "death" );

	self waittill( "placed" );
	
	owner takeKillstreakWeapons( self.tankType );

	owner _giveWeapon( level.tankSettings[ self.tankType ].laptopInfo );
	owner SwitchToWeaponImmediate( level.tankSettings[ self.tankType ].laptopInfo );
}

createTank( tankForPlayer )
{
	owner = tankForPlayer.owner;
	tankType = tankForPlayer.tankType;
	lifeId = tankForPlayer.lifeId;

	// temp, push the placement slightly out more so the model isn't in the player
	//placement[ "origin" ] += AnglesToForward( owner.angles ) * 20;

	remoteTank = SpawnVehicle( level.tankSettings[ tankType ].modelBase, tankType, level.tankSettings[ tankType ].vehicleInfo, tankForPlayer.origin, tankForPlayer.angles, owner );
	if ( !IsDefined( remoteTank ) )
		return undefined;
	
	//gunTagOrigin = remoteTank GetTagOrigin( "tag_gun" );
	turretAttachTagOrigin = remoteTank GetTagOrigin( "tag_turret_attach" );
/#
	//remoteTank thread drawDebugTag( "tag_gun" );
	//maps\mp\killstreaks\_ac130::debug_circle( remoteTank.origin, 32, 10, ( 0, 0, 1 ) );
#/
	mgTurret = SpawnTurret( "misc_turret", turretAttachTagOrigin, level.tankSettings[ tankType ].mgTurretInfo, false );
	mgTurret LinkTo( remoteTank, "tag_turret_attach", ( 0, 0, 0 ), ( 0, 0, 0 ) );
	mgTurret SetModel( level.tankSettings[ tankType ].modelMGTurret );
	mgTurret.health = level.tankSettings[ tankType ].health;
	// no need to set up max health because it will piggy back off of the tank max health
	mgTurret.owner = owner;
	mgTurret.angles = owner.angles;
	mgTurret.specialDamageCallback = ::Callback_VehicleDamage;
	mgTurret.tank = remoteTank;
	mgTurret MakeUnusable();
	mgTurret SetDefaultDropPitch( 0 );
	mgTurret SetCanDamage( false );

	//glTurret = SpawnTurret( "misc_turret", gunTagOrigin, level.tankSettings[ tankType ].glTurretInfo );
	//glTurret LinkTo( mgTurret, "tag_launcher_attach", ( 0, 0, 0 ), ( 0, 0, 0 ) );
	//glTurret SetModel( level.tankSettings[ tankType ].modelGLTurret );
	//glTurret.health = level.tankSettings[ tankType ].health;
	//// no need to set up max health because it will piggy back off of the tank max health
	//glTurret.owner = owner;
	//glTurret.angles = owner.angles;
	//glTurret.specialDamageCallback = ::Callback_VehicleDamage;
	//glTurret.tank = remoteTank;
	//glTurret MakeUnusable();
	//glTurret SetDefaultDropPitch( 0 );

	remoteTank.specialDamageCallback = ::Callback_VehicleDamage;
	remoteTank.lifeId = lifeId;
	remoteTank.team = owner.team;
	remoteTank.owner = owner;
	remoteTank.mgTurret = mgTurret;
	//remoteTank.glTurret = glTurret;

	remoteTank.health = level.tankSettings[ tankType ].health;
	remoteTank.maxHealth = level.tankSettings[ tankType ].maxHealth;
	remoteTank.damageTaken = 0;	
	remoteTank.destroyed = false;
	remoteTank SetCanDamage( false );
	remoteTank.tankType = tankType;

	mgTurret SetTurretModeChangeWait( true );
	//glTurret SetTurretModeChangeWait( true );
	remoteTank tank_setInactive();
	mgTurret SetSentryOwner( owner );
	//glTurret SetSentryOwner( owner );

	owner.using_remote_tank = false;

	////owner SetClientDvar( "ui_ugv_mine", 1 );
	//owner SetClientDvar( "ui_ugv_missile", 1 );
	////owner SetClientDvar( "ui_ugv_gl", 1 );
	//owner SetClientDvar( "ui_ugv_damage_fade", 1.0 );
	//owner SetClientDvar( "ui_ugv_damaged", 0 );
	//owner SetClientDvar( "ui_ugv_damage_state", 0 );
	//owner SetClientDvar( "ui_ugv_bullets", 0 );
	//owner SetClientDvar( "ui_ugv_max_bullets", 0 );
	
	owner SetPlayerData( "ugvMissile", 1 );
	owner SetPlayerData( "ugvDamageFade", 1.0 );
	owner SetPlayerData( "ugvDamaged", 0 );
	owner SetPlayerData( "ugvDamageState", 0 );
	owner SetPlayerData( "ugvBullets", 0 );
	owner SetPlayerData( "ugvMaxBullets", 0 );

	//for( i = 1; i < 11; i++ )
	//{
	//	owner SetClientDvar( "ui_ugv_rand_xpos" + i, 0 );
	//	owner SetClientDvar( "ui_ugv_rand_ypos" + i, 0 );
	//	owner SetClientDvar( "ui_ugv_rand_w" + i, 0 );
	//	owner SetClientDvar( "ui_ugv_rand_h" + i, 0 );
	//}

	remoteTank.damageFade = 1.0;
	remoteTank thread tank_incrementDamageFade();
	remoteTank thread tank_watchLowHealth();
	remoteTank thread tank_giveWeaponOnPlaced();

	return remoteTank;	
}

/#
//drawDebugTag( tagName )
//{
//	self endon( "death" );
//	while( true )
//	{
//		tagOrigin = self GetTagOrigin( tagName );
//		tagAngles = self GetTagAngles( tagName );
//		Line( tagOrigin, tagOrigin + ( AnglesToForward( tagAngles ) * 10 ), ( 1, 0, 0 ) );
//		Line( tagOrigin, tagOrigin + ( AnglesToRight( tagAngles ) * 10 ), ( 0, 1, 0 ) );
//		Line( tagOrigin, tagOrigin + ( AnglesToUp( tagAngles ) * 10 ), ( 0, 0, 1 ) );
//		wait( 0.05 );
//	}
//}
#/

tank_setActive() // self == tank
{	
	self endon( "death" );
	self.owner endon( "disconnect" );
	level endon( "game_ended" );

	self MakeUnusable();
	self.mgTurret MakeTurretSolid();
	//self.glTurret MakeTurretSolid();
	self.mgTurret SetCanDamage( true );
	//self.glTurret SetCanDamage( true );
	//self.mgTurret SetTurretMinimapVisible( true );

	self MakeVehicleSolidCapsule( 23, 23, 23 );
	self SetCanDamage( true );
	
	if( !IsDefined( self.owner ) )
		return;

	owner = self.owner;

	headIconOffset = ( 0, 0, 20 );
	if ( level.teamBased )
	{
		self.team = owner.team;
		self.mgTurret.team = owner.team;
		//self.glTurret.team = owner.team;
		self.mgTurret SetTurretTeam( owner.team );
		//self.glTurret SetTurretTeam( owner.team );
		
		// only show the head icon to players on the team and not the owner, this will keep it from obscuring the view
		foreach( player in level.players )
		{
			if( player != owner && player.team == owner.team )
			{
				headIcon = self.mgTurret maps\mp\_entityheadicons::setHeadIcon( player, maps\mp\gametypes\_teams::getTeamHeadIcon( self.team ), headIconOffset, 10, 10, false, 0.05, false, true, false, true );				
				if ( isDefined( headIcon ) ) 
				{				
					headIcon SetTargetEnt( self );
				}
			}
		}
	}
	//else
	//{
	//	self.mgTurret maps\mp\_entityheadicons::setPlayerHeadIcon( self.owner, headIconOffset );
	//}

	self thread tank_handleDisconnect();
	self thread tank_handleChangeTeams();
	self thread tank_handleDeath();
	self thread tank_handleTimeout();	
	self thread tank_blinkyLightAntenna();
	self thread tank_blinkyLightCamera();

	self startUsingTank();
	owner openMenu( "remotetank_timer" );
}

startUsingTank() // self == tank
{
	owner = self.owner;

	owner setUsingRemote( self.tankType );

	//owner VisionSetThermalForPlayer( "black_bw", 0 );
	//owner VisionSetThermalForPlayer( game["thermal_vision"], 1.5 );
	//owner ThermalVisionOn();
	//owner ThermalVisionFOFOverlayOn();
	//if ( isdefined( level.HUDItem[ "thermal_mode" ] ) )
	//	level.HUDItem[ "thermal_mode" ] settext ( "" );

	if ( getDvarInt( "camera_thirdPerson" ) )
		owner setThirdPersonDOF( false );

	//owner PlayerLinkWeaponViewToDelta( self.mgTurret, "tag_player", 0, 180, 180, 50, 25, false );
	//owner PlayerLinkedSetViewZNear( false );
	//owner PlayerLinkedSetUseBaseAngleForViewClamp( true );

	owner.restoreAngles = owner.angles;

	//owner setClientDvar( "vehCam_mode", "1" );
	//owner setClientDvar( "vehCam_angles3P", "15 0 0" );
	//owner setClientDvar( "vehCam_offset3P", "100 -6 0" );	//"65 -6 0"

	//owner ControlsLinkTo( self );
	//owner CameraLinkTo( self, "tag_origin" );	

	owner freezeControlsWrapper( true );
	result = owner maps\mp\killstreaks\_killstreaks::initRideKillstreak();
	if( result != "success" )
	{
		if ( result != "disconnect" )
			owner clearUsingRemote();

		if( IsDefined( owner.disabledWeapon ) && owner.disabledWeapon )
			owner _enableWeapon();
		self notify( "death" );

		return false;
	}	
	owner freezeControlsWrapper( false );

	owner RemoteControlVehicle( self );
	owner RemoteControlTurret( self.mgTurret );
	
	owner thread tank_WatchFiring( self );
	//owner thread tank_FireGL( self );
	owner thread tank_FireMissiles( self );
	//owner thread tank_DropMines( self );
	self thread tank_Earthquake();
	self thread tank_playerExit();

	owner.using_remote_tank = true;

	if( owner isJuggernaut() )
		owner.juggernautOverlay.alpha = 0;

	owner _giveWeapon( level.tankSettings[ self.tankType ].remoteInfo );
	owner SwitchToWeaponImmediate( level.tankSettings[ self.tankType ].remoteInfo );

	// don't handle damage until the user is all the way in the killstreak
	// this keeps from getting stuck in a black screen if the user and the tank die as you're getting in
	self thread tank_handleDamage();
	self.mgTurret thread tank_turret_handleDamage();
	//self.glTurret thread tank_turret_handleDamage();
}

tank_blinkyLightAntenna() // self == tank
{
	self endon( "death" );

	while ( true )
	{
		PlayFXOnTag( getfx( "remote_tank_antenna_light_mp" ), self.mgTurret, "tag_headlight_right" );
		wait( 1.0 );
		StopFXOnTag( getfx( "remote_tank_antenna_light_mp" ), self.mgTurret, "tag_headlight_right" );
	}
}

tank_blinkyLightCamera() // self == tank
{
	self endon( "death" );

	while ( true )
	{
		PlayFXOnTag( getfx( "remote_tank_camera_light_mp" ), self.mgTurret, "tag_tail_light_right" );
		wait( 2.0 );
		StopFXOnTag( getfx( "remote_tank_camera_light_mp" ), self.mgTurret, "tag_tail_light_right" );
	}
}

tank_setInactive() // self == tank
{
	self.mgTurret SetMode( level.tankSettings[ self.tankType ].sentryModeOff );
	//self.glTurret SetMode( level.tankSettings[ self.tankType ].sentryModeOff );

	if ( level.teamBased )
		self maps\mp\_entityheadicons::setTeamHeadIcon( "none", ( 0, 0, 0 ) );
	else if ( IsDefined( self.owner ) )
		self maps\mp\_entityheadicons::setPlayerHeadIcon( undefined, ( 0, 0, 0 ) );

	if( !IsDefined( self.owner ) )
		return;

	owner = self.owner;
	if( IsDefined( owner.using_remote_tank ) && owner.using_remote_tank )
	{
		owner notify( "end_remote" );

		//owner ThermalVisionOff();
		//owner ThermalVisionFOFOverlayOff();		
		//owner ControlsUnlink( self );
		//owner CameraUnlink( self );

		owner RemoteControlVehicleOff( self );
		owner RemoteControlTurretOff( self.mgTurret );


		owner switchToWeapon( owner getLastWeapon() );
		owner clearUsingRemote();
		owner setPlayerAngles( owner.restoreAngles );

		if ( getDvarInt( "camera_thirdPerson" ) )
			owner setThirdPersonDOF( true );				

		//owner VisionSetThermalForPlayer( game["thermal_vision"], 0 );

		// just in case the tank is killed before you can get in it, the initRideKillstreak() does _disableUsability() and we unfortunately kill the thread on death
		if( IsDefined( owner.disabledUsability ) && owner.disabledUsability )
			owner _enableUsability();

		// take the killstreak weapons
		owner takeKillstreakWeapons( level.tankSettings[ self.tankType ].streakName );

		owner.using_remote_tank = false;

		owner thread tank_freezeBuffer();
	}
}

tank_freezeBuffer()
{
	self endon( "disconnect" );
	self endon( "death" );
	level endon( "game_ended" );
	
	self freezeControlsWrapper( true );
	wait( 0.5 );
	self freezeControlsWrapper( false );
}

tank_handleDisconnect()
{
	self endon ( "death" );	

	self.owner waittill( "disconnect" );
	
	self notify( "death" );
}

tank_handleChangeTeams()
{
	self endon ( "death" );	

	self.owner waittill_any( "joined_team", "joined_spectators" );
	
	self notify( "death" );
}

tank_handleTimeout()
{
	self endon ( "death" );	
	
	lifeSpan = level.tankSettings[ self.tankType ].timeOut;
/#
	lifeSpan = GetDvarFloat( "scr_remotetank_timeout", 60.0 );
#/
	SetDvar( "ui_remoteTankUseTime", lifeSpan );
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( lifeSpan );
	
	self notify( "death" );
}

tank_handleDeath() // self == tank
{
	level endon( "game_ended" );
	
	entNum = self GetEntityNumber();
	self addToUGVList( entNum );

	self waittill( "death" );			

	self playSound( "talon_destroyed" );
	
	self removeFromUGVList( entNum );

	self setModel( level.tankSettings[ self.tankType ].modelDestroyed );

	// make sure the owner gets out
	// there's a bug where you can get stuck in a black screen because the player and tank die at the same time and that ends scripts that would reset the view
	if ( IsDefined( self.owner ) && ( self.owner.using_remote_tank || self.owner isUsingRemote() ) )
	{
		self.owner SetPlayerData( "ugvDamageState", 0 );

		self tank_setInactive();

		self.owner.using_remote_tank = false;

		if( self.owner isJuggernaut() )
			self.owner.juggernautOverlay.alpha = 1;
	}

	self.mgTurret SetDefaultDropPitch( 40 );
	self.mgTurret SetSentryOwner( undefined );
	//self.mgTurret SetTurretMinimapVisible( false );
	
	self PlaySound( "sentry_explode" );		
	PlayFXOnTag( level._effect[ "remote_tank_dying" ], self.mgTurret, "tag_aim" );
	wait( 2.0 );
	PlayFX( level._effect[ "remote_tank_explode" ], self.origin );

	self.mgTurret delete();
	//self.glTurret delete();
	self delete();	
}

Callback_VehicleDamage( inflictor, attacker, damage, iDFlags, meansOfDeath, weapon, point, dir, hitLoc, timeOffset, modelIndex, partName )
{
	vehicle = self;
	// the turrets and the tank are different objects, so if this is the turret, transfer damage to the tank
	if( IsDefined( self.tank ) )
		vehicle = self.tank;

	if( IsDefined( vehicle.alreadyDead ) && vehicle.alreadyDead )
		return;

	// don't allow people to destroy things on their team if FF is off
	if( !maps\mp\gametypes\_weapons::friendlyFireCheck( vehicle.owner, attacker ) )
		return;			

	if( IsDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
		vehicle.wasDamagedFromBulletPenetration = true;

	vehicle.wasDamaged = true;
	
	vehicle.damageFade = 0.0;
	vehicle.owner SetPlayerData( "ugvDamaged", 1 );

	// spark to show taking damage
	PlayFXOnTagForClients( level._effect[ "remote_tank_spark" ], vehicle, "tag_player", vehicle.owner );

	// up the damage for airstrikes and stealth bombs
	switch( weapon )
	{
	case "artillery_mp":
	case "stealth_bomb_mp":
		damage *= 4;
		break;
	}

	// do extra melee damage
	if( meansOfDeath == "MOD_MELEE" )
		damage = vehicle.maxHealth * 0.5;

	modifiedDamage = damage;

	if( isPlayer( attacker ) )
	{					
		attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "remote_tank" );

		if( meansOfDeath == "MOD_RIFLE_BULLET" || meansOfDeath == "MOD_PISTOL_BULLET" )
		{
			if ( attacker _hasPerk( "specialty_armorpiercing" ) )
				modifiedDamage += damage * level.armorPiercingMod;
		
			// armored
			//modifiedDamage *= level.remote_tank_armor_bulletdamage;
		}

		// do extra explosive damage
		if( IsExplosiveDamageMOD( meansOfDeath ) )
			modifiedDamage += damage;
	}

	// destroy it if a vehicle blows up next to it, so we don't get weird collision bugs with the destructible model that spawns in
	if( IsExplosiveDamageMOD( meansOfDeath ) && weapon == "destructible_car" )
		modifiedDamage = vehicle.maxHealth;

	// in case we are shooting from a remote position, like being in the osprey gunner shooting this
	if( IsDefined( attacker.owner ) && IsPlayer( attacker.owner ) )
	{
		attacker.owner maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "remote_tank" );
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
			vehicle.largeProjectileDamage = true;
			modifiedDamage = vehicle.maxHealth + 1;
			break;

		case "artillery_mp":
		case "stealth_bomb_mp":
			vehicle.largeProjectileDamage = false;
			modifiedDamage = ( vehicle.maxHealth * 0.5 );
			break;

		case "bomb_site_mp":
		case "emp_grenade_mp":
			vehicle.largeProjectileDamage = false;
			modifiedDamage = vehicle.maxHealth + 1;
			break;

		case "ims_projectile_mp":
			vehicle.largeProjectileDamage = true;
			modifiedDamage = ( vehicle.maxHealth * 0.5 );
			break;
		}
	}

	vehicle.damageTaken += modifiedDamage;
	vehicle playsound( "talon_damaged" );		

	if( vehicle.damageTaken >= vehicle.maxHealth )
	{
		if ( isPlayer( attacker ) && ( !IsDefined( vehicle.owner ) || attacker != vehicle.owner ) )
		{
			vehicle.alreadyDead = true;
			attacker notify( "destroyed_killstreak", weapon );
			thread teamPlayerCardSplash( "callout_destroyed_remote_tank", attacker );			
			attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 300, weapon, meansOfDeath );			
			attacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DESTROYED_REMOTE_TANK" );
			thread maps\mp\gametypes\_missions::vehicleKilled( vehicle.owner, vehicle, undefined, attacker, damage, meansOfDeath, weapon );		
		}

		vehicle notify ( "death" );
	}
}

tank_incrementDamageFade() // self == vehicle
{
	self endon( "death" );
	level endon( "game_ended" );

	// this is for the ui
	damaged = false;
	while( true )
	{
		if( self.damageFade < 1.0 )
		{
			self.owner SetPlayerData( "ugvDamageFade", self.damageFade );
			self.damageFade += 0.1;
			damaged = true;
		}
		else
		{
			if( damaged )
			{
				self.damageFade = 1.0;
				self.owner SetPlayerData( "ugvDamageFade", self.damageFade );

				self.owner SetPlayerData( "ugvDamaged", 0 );
				damaged = false;
			}
		}
		wait( 0.1 );
	}
}

tank_watchLowHealth() // self == vehicle
{
	self endon( "death" );
	level endon( "game_ended" );

	// every N% damage changes the damage state
	percentage = 0.1;

	damageState = 1;
	firstDamage = true;

	// this is for the ui
	while( true )
	{
		// first time they take damage show damage, then every percentage of health after that
		if( firstDamage )
		{
			if( self.damageTaken > 0 )
			{
				firstDamage = false;

				self.owner SetPlayerData( "ugvDamageState", damageState );
				damageState++;
			}
		}
		else
		{
			if( self.damageTaken >= ( self.maxHealth * ( percentage * damageState ) )  )
			{
				self.owner SetPlayerData( "ugvDamageState", damageState );
				damageState++;
			}
		}
		wait( 0.05 );
	}
}

tank_handleDamage() // self == tank
{
	self endon( "death" );
	level endon( "game_ended" );

	while( true )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );

		if( IsDefined( self.specialDamageCallback ) )
			self [[self.specialDamageCallback]]( undefined, attacker, damage, iDFlags, meansOfDeath, weapon, point, direction_vec, undefined, undefined, modelName, partName );
	}
}

tank_turret_handleDamage() // self == turret attached to tank
{
	self endon( "death" );
	level endon( "game_ended" );

	while( true )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );

		// if this is explosive damage then don't do it on the turret because the tank will do it, unless this is an airstrike or stealth bomb
		if( IsDefined( self.specialDamageCallback ) && 
			IsDefined( self.tank ) && 
			( !IsExplosiveDamageMOD( meansOfDeath ) || ( IsDefined( weapon ) && IsExplosiveDamageMOD( meansOfDeath ) && ( weapon == "stealth_bomb_mp" || weapon == "artillery_mp" ) ) ) )
			self.tank [[self.specialDamageCallback]]( undefined, attacker, damage, iDFlags, meansOfDeath, weapon, point, direction_vec, undefined, undefined, modelName, partName );
	}
}

tank_WatchFiring( remoteTank ) // self == owner
{
	self endon ( "disconnect" );
	self endon ( "end_remote" );
	remoteTank endon ( "death" );

	maxBullets = 50;
	numBullets = maxBullets;
	self SetPlayerData( "ugvMaxBullets", maxBullets );
	self SetPlayerData( "ugvBullets", numBullets );

	fireTime = WeaponFireTime( level.tankSettings[ remoteTank.tankType ].mgTurretInfo );
	while( true )
	{
		if( remoteTank.mgTurret IsFiringVehicleTurret() )
		{
			numBullets--;
			self SetPlayerData( "ugvBullets", numBullets );

			if( numBullets <= 0 )
			{
				remoteTank.mgTurret TurretFireDisable();
				
				// reload			
				wait( 2.5 );
				
				remoteTank PlaySound( "talon_reload" );
				self PlayLocalSound( "talon_reload_plr" );
				numBullets = maxBullets;
				self SetPlayerData( "ugvBullets", numBullets );
				
				remoteTank.mgTurret TurretFireEnable();
			}
		}

		wait( fireTime ); // should match the turret fireTime in the gdt
	}
}

//tank_FireGL( remoteTank ) // self == owner
//{
//	self endon ( "disconnect" );
//	self endon ( "end_remote" );
//	level endon ( "game_ended" );
//	remoteTank endon ( "death" );
//
//	rocketNum = 0;
//
//	while ( true )
//	{
//		if ( self FragButtonPressed() )
//		{
//			remoteTank.glTurret ShootTurret();
//			self PlayRumbleOnEntity( "damage_heavy" );
//			
//			// reload
//			// TODO: get sound for this
//			//remoteTank PlaySound( "talon_rocket_reload" );
//			self SetClientDvar( "ui_ugv_gl", 0 );
//
//			wait( 3.0 );
//
//			// TODO: get sound for this
//			remoteTank PlaySound( "talon_rocket_reload" );
//			self SetClientDvar( "ui_ugv_gl", 1 );
//		}	
//		else
//			wait( 0.05 );							
//	}
//}

tank_FireMissiles( remoteTank ) // self == owner
{
	self endon ( "disconnect" );
	self endon ( "end_remote" );
	level endon ( "game_ended" );
	remoteTank endon ( "death" );
		
	rocketNum = 0;

	while ( true )
	{
		if ( self FragButtonPressed() )
		{
			tagOrigin = remoteTank.mgTurret.origin;
			tagAngles = remoteTank.mgTurret.angles;
			switch( rocketNum )
			{
			case 0:
				tagOrigin = remoteTank.mgTurret GetTagOrigin( "tag_missile1" );
				tagAngles = remoteTank.mgTurret GetTagAngles( "tag_player" );
				break;
			case 1:
				tagOrigin = remoteTank.mgTurret GetTagOrigin( "tag_missile2" );
				tagAngles = remoteTank.mgTurret GetTagAngles( "tag_player" );
				break;
			}
			
			remoteTank PlaySound( "talon_missile_fire" );
			self PlayLocalSound( "talon_missile_fire_plr" );
			
			destPoint = tagOrigin + ( AnglesToForward( tagAngles ) * 100 );
			rocket = MagicBullet( level.tankSettings[ remoteTank.tankType ].missileInfo, tagOrigin, destPoint, self );
			//rocket Missile_SetTargetEnt( remoteTank.samTargetEnt );
			//rocket Missile_SetFlightmodeDirect();
			
			rocketNum = ( rocketNum + 1 ) % 2;
			
			self SetPlayerData( "ugvMissile", 0 );

			wait( 5.0 );

			remoteTank PlaySound( "talon_rocket_reload" );
			self PlayLocalSound( "talon_rocket_reload_plr" );
			
			self SetPlayerData( "ugvMissile", 1 );
		}	
		else
			wait( 0.05 );							
	}
}

//tank_DropMines( remoteTank ) // self == owner
//{
//	self endon ( "disconnect" );
//	self endon ( "end_remote" );
//	level endon ( "game_ended" );
//	remoteTank endon ( "death" );
//
//	while ( true )
//	{
//		if ( self SecondaryOffhandButtonPressed() )
//		{
//			trace = BulletTrace( remoteTank.origin + (0, 0, 4), remoteTank.origin - (0, 0, 4), false, remoteTank );
//			normal = VectorNormalize( trace["normal"] );
//			plantAngles = VectorToAngles( normal );
//			plantAngles += ( 90, 0, 0 );
//
//			mine = maps\mp\gametypes\_weapons::spawnMine( remoteTank.origin, self, "equipment", plantAngles );
//
//			// TODO: get sound for this
//			remoteTank PlaySound( "item_blast_shield_on" );
//
//			self SetClientDvar( "ui_ugv_mine", 0 );
//
//			wait( 5.0 );
//
//			self SetClientDvar( "ui_ugv_mine", 1 );
//		}	
//		else
//			wait( 0.05 );							
//	}
//}

tank_Earthquake() // self == tank
{
	self endon ( "death" );
	self.owner endon ( "end_remote" );

	while ( true )
	{
		Earthquake( 0.1, 0.25, self.mgTurret GetTagOrigin( "tag_player" ), 50 );
		//self PlayRumbleOnEntity( "damage_light" );
		wait( 0.25 );
	}
}

addToUGVList( entNum )
{
	level.ugvs[entNum] = self;	
}

removeFromUGVList( entNum )
{
	level.ugvs[entNum] = undefined;

	// decrement the faux vehicle count since this is being removed
	decrementFauxVehicleCount();
}

tank_playerExit() // self == tank
{
	if( !IsDefined( self.owner ) )
		return;

	owner = self.owner;

	level endon( "game_ended" );
	owner endon ( "disconnect" );
	owner endon ( "end_remote" );
	self endon ( "death" );

	while( true )
	{
		timeUsed = 0;
		while(	owner UseButtonPressed() )
		{	
			timeUsed += 0.05;
			if( timeUsed > 0.75 )
			{	
				self notify( "death" );
				return;
			}
			wait( 0.05 );
		}
		wait( 0.05 );
	}
}
