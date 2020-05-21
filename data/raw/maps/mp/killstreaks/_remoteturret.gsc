#include maps\mp\_utility;
#include common_scripts\utility;

/*
	Remote Turret killstreak: the player will throw this and it will stick to the ground and give a remote view with a small turret
*/

init()
{
	level.turretType = [];
	level.turretType[ "mg_turret" ]	= "remote_mg_turret";

	level.killStreakFuncs[ "remote_mg_turret" ] = ::tryUseRemoteMGTurret;

	level.turretSettings = [];

	level.turretSettings[ "mg_turret" ] = spawnStruct();
	level.turretSettings[ "mg_turret" ].sentryModeOn =			"manual";	
	level.turretSettings[ "mg_turret" ].sentryModeOff =			"sentry_offline";	
	level.turretSettings[ "mg_turret" ].timeOut =				60.0;	
	level.turretSettings[ "mg_turret" ].health =				999999; // keep it from dying anywhere in code	
	level.turretSettings[ "mg_turret" ].maxHealth =				1000; // this is what we check against for death	
	level.turretSettings[ "mg_turret" ].streakName =			"remote_mg_turret";
	level.turretSettings[ "mg_turret" ].weaponInfo =			"remote_turret_mp";
	level.turretSettings[ "mg_turret" ].modelBase =				"mp_remote_turret";
	level.turretSettings[ "mg_turret" ].modelPlacement =		"mp_remote_turret_placement";
	level.turretSettings[ "mg_turret" ].modelPlacementFailed =	"mp_remote_turret_placement";
	level.turretSettings[ "mg_turret" ].modelDestroyed =		"mp_remote_turret";	
	//level.turretSettings[ "mg_turret" ].modelBombSquad =		"mp_remote_turret_bombsquad";	
	level.turretSettings[ "mg_turret" ].teamSplash =			"used_remote_mg_turret";	
	level.turretSettings[ "mg_turret" ].hintEnter =				&"MP_ENTER_REMOTE_TURRET";	
	level.turretSettings[ "mg_turret" ].hintEnterWii =			&"MP_ENTER_REMOTE_TURRET_WIIMOTE";	
	level.turretSettings[ "mg_turret" ].hintExit =				&"MP_EARLY_EXIT";	
	level.turretSettings[ "mg_turret" ].hintExitWii =			&"MP_EARLY_EXIT_WIIMOTE";	
	level.turretSettings[ "mg_turret" ].hintPickUp =			&"MP_DOUBLE_TAP_TO_CARRY";
	level.turretSettings[ "mg_turret" ].placeString =			&"MP_TURRET_PLACE";	
	level.turretSettings[ "mg_turret" ].cannotPlaceString =		&"MP_TURRET_CANNOT_PLACE";	
	level.turretSettings[ "mg_turret" ].voDestroyed =			"remote_sentry_destroyed";
	level.turretSettings[ "mg_turret" ].laptopInfo =			"killstreak_remote_turret_laptop_mp";
	level.turretSettings[ "mg_turret" ].remoteInfo =			"killstreak_remote_turret_remote_mp";

	foreach ( turretInfo in level.turretSettings )
	{
		PreCacheItem( turretInfo.weaponInfo );
		PreCacheModel( turretInfo.modelBase );	
		PreCacheModel( turretInfo.modelPlacement );
		PreCacheModel( turretInfo.modelPlacementFailed );
		PreCacheModel( turretInfo.modelDestroyed );
		//PreCacheModel( turretInfo.modelBombSquad );
		PreCacheString( turretInfo.hintEnter );
		PreCacheString( turretInfo.hintEnterWii );
		PreCacheString( turretInfo.hintExit );
		PreCacheString( turretInfo.hintExitWii );
		PreCacheString( turretInfo.placeString );
		PreCacheString( turretInfo.cannotPlaceString );
		PreCacheItem( turretInfo.laptopInfo );
		PreCacheItem( turretInfo.remoteInfo );
	}

	level._effect[ "sentry_explode_mp" ]	= loadfx( "explosions/sentry_gun_explosion" );
	level._effect[ "sentry_smoke_mp" ]		= loadfx( "smoke/car_damage_blacksmoke" );
	level._effect[ "antenna_light_mp" ]		= loadfx( "lights/light_detonator_blink" );

/#
	SetDevDvarIfUninitialized( "scr_remote_turret_timeout", 60.0 );
	SetDevDvarIfUninitialized( "scr_remote_turret_scalar", 100 );
	SetDevDvarIfUninitialized( "scr_remote_turret_addz", 10 );
#/
}

tryUseRemoteMGTurret( lifeId )
{
	result = tryUseRemoteTurret( lifeId, "mg_turret" );

	if( result )
	{
		self maps\mp\_matchdata::logKillstreakEvent( level.turretSettings[ "mg_turret" ].streakName, self.origin );

		// take the killstreak weapon
		self takeKillstreakWeapons( "mg_turret" );
	}

	// we're done carrying for sure and sometimes this might not get reset
	// this fixes a bug where you could be carrying and have it in a place where it won't plant, get killed, now you can't scroll through killstreaks
	self.isCarrying = false;

	return result; 
}

takeKillstreakWeapons( turretType ) // self == owner
{
	killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( level.turretSettings[ turretType ].streakName );
	maps\mp\killstreaks\_killstreaks::takeKillstreakWeaponIfNoDupe( killstreakWeapon );

	self TakeWeapon( level.turretSettings[ turretType ].laptopInfo );
	self TakeWeapon( level.turretSettings[ turretType ].remoteInfo );
}

tryUseRemoteTurret( lifeId, turretType )
{
	if ( self isUsingRemote() )
	{
		return false;
	}
	
	turret = createTurretForPlayer( turretType, self );
	
	//	returning from this streak activation seems to strip this?
	//	manually removing and restoring
	self removePerks();		

	self setCarryingTurret( turret, true );

	self thread restorePerks();

	// if we failed to place the turret, it will have been deleted at this point
	if ( isDefined( turret ) )
		return true;
	else
		return false;
}

///////////////////////////////////////////////////
// CARRY FUNCTIONS
//////////////////////////////////////////////////

setCarryingTurret( turret, allowCancel ) // self == player
{
	self endon ( "death" );
	self endon ( "disconnect" );

	assert( isReallyAlive( self ) );

	turret turret_setCarried( self );

	self _disableWeapon();

	self notifyOnPlayerCommand( "place_turret", "+attack" );
	self notifyOnPlayerCommand( "place_turret", "+attack_akimbo_accessible" ); // support accessibility control scheme
	self notifyOnPlayerCommand( "cancel_turret", "+actionslot 4" );

	for ( ;; )
	{
		result = waittill_any_return( "place_turret", "cancel_turret" );

		if ( result == "cancel_turret" )
		{
			if ( !allowCancel )
				continue;

			// failsafe because something takes away the killstreak weapon on occasions where you have them stacked in the gimme slot
			//	for example, if you stack uav, sam turret, emp and then use the emp, then pull out the sam turret, the list item weapon gets taken away before you plant it
			//	so to "fix" this, if the user cancels then we give the weapon back to them only if the selected killstreak is the same and the item list is zero
			//	this is done for anything you can pull out and plant (ims, sentry, sam turret, remote turret, remote tank)
			if( result == "cancel_turret" )
			{
				killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( level.turretSettings[ turret.turretType ].streakName );
				if( IsDefined( self.killstreakIndexWeapon ) && 
					killstreakWeapon == maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( self.pers["killstreaks"][self.killstreakIndexWeapon].streakName ) &&
					!( self GetWeaponsListItems() ).size )
				{
					self _giveWeapon( killstreakWeapon, 0 );
					self _setActionSlot( 4, "weapon", killstreakWeapon );
				}
			}

			turret turret_setCancelled();
			self _enableWeapon();
			return false;
		}

		if ( !turret.canBePlaced )
			continue;

		turret turret_setPlaced();		
		self _enableWeapon();		
		return true;
	}
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
	if ( isDefined( self.restorePerk ) )
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

turret_setPlaced() // self == turret
{
	self SetModel( level.turretSettings[ self.turretType ].modelBase );

	self SetSentryCarrier( undefined );
	self SetCanDamage( true );

	self.carriedBy forceUseHintOff();
	self.carriedBy = undefined;
	
	if( IsDefined( self.owner ) )
		self.owner.isCarrying = false;

	// TODO: get sound for this
	self playSound( "sentry_gun_plant" );

	self thread turret_setActive();
	self notify ( "placed" );
}

turret_setCancelled()
{
	self.carriedBy forceUseHintOff();
	if( IsDefined( self.owner ) )
		self.owner.isCarrying = false;

	self delete();
}

turret_setCarried( carrier ) // self == turret
{
	assert( isPlayer( carrier ) );
	assertEx( carrier == self.owner, "turret_setCarried() specified carrier does not own this turret" );

	self SetModel( level.turretSettings[ self.turretType ].modelPlacement );

	self SetCanDamage( false );
	self SetSentryCarrier( carrier );
	self SetContents( 0 );

	self.carriedBy = carrier;
	carrier.isCarrying = true;

	carrier thread updateTurretPlacement( self );

	self thread turret_onCarrierDeath( carrier );
	self thread turret_onCarrierDisconnect( carrier );
	self thread turret_onCarrierChangedTeam( carrier );
	self thread turret_onGameEnded();

	self SetDefaultDropPitch( -89.0 );

	self turret_setInactive();

	self notify ( "carried" );
}

updateTurretPlacement( turret )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );

	turret endon ( "placed" );
	turret endon ( "death" );

	turret.canBePlaced = true;
	lastCanPlaceTurret = -1; // force initial update

	for( ;; )
	{
		placement = self canPlayerPlaceSentry();

		turret.origin = placement[ "origin" ];
		turret.angles = placement[ "angles" ];
		turret.canBePlaced = self isOnGround() && placement[ "result" ] && ( abs(turret.origin[2]-self.origin[2]) < 10 );

		if ( turret.canBePlaced != lastCanPlaceTurret )
		{
			if ( turret.canBePlaced )
			{
				turret SetModel( level.turretSettings[ turret.turretType ].modelPlacement );
				turret setSwitchToSecondObjective( 0 );
				self ForceUseHintOn( level.turretSettings[ turret.turretType ].placeString );
			}
			else
			{
				turret SetModel( level.turretSettings[ turret.turretType ].modelPlacementFailed );
				turret setSwitchToSecondObjective( 1 );
				self ForceUseHintOn( level.turretSettings[ turret.turretType ].cannotPlaceString );
			}
		}

		lastCanPlaceTurret = turret.canBePlaced;		
		wait ( 0.05 );
	}
}

turret_onCarrierDeath( carrier ) // self == turret
{
	self endon ( "placed" );
	self endon ( "death" );

	carrier waittill ( "death" );

	if ( self.canBePlaced )
		self turret_setPlaced();
	else
		self delete();
}

turret_onCarrierDisconnect( carrier ) // self == turret
{
	self endon ( "placed" );
	self endon ( "death" );

	carrier waittill ( "disconnect" );

	self delete();
}

turret_onCarrierChangedTeam( carrier ) // self == turret
{
	self endon ( "placed" );
	self endon ( "death" );

	carrier waittill_any( "joined_team", "joined_spectators" );

	self delete();
}

turret_onGameEnded( carrier ) // self == turret
{
	self endon ( "placed" );
	self endon ( "death" );

	level waittill ( "game_ended" );

	self delete();
}

///////////////////////////////////////////////////
// END CARRY FUNCTIONS
//////////////////////////////////////////////////

createTurretForPlayer( turretType, owner )
{
	assertEx( IsDefined( owner ), "createTurretForPlayer() called without owner specified" );

	turret = SpawnTurret( "misc_turret", owner.origin, level.turretSettings[ turretType ].weaponInfo );
	turret.angles = owner.angles;
	turret SetModel( level.turretSettings[ turretType ].modelBase );

	turret.owner = owner;
	turret.health = level.turretSettings[ turretType ].health;
	turret.maxHealth = level.turretSettings[ turretType ].maxHealth;
	turret.damageTaken = 0;
	turret.turretType = turretType;
	turret.stunned = false;
	turret.stunnedTime = 5.0;

	turret SetTurretModeChangeWait( true );
	turret turret_setInactive();
	turret SetSentryOwner( owner );
	turret SetTurretMinimapVisible( true );

	turret SetDefaultDropPitch( -89.0 );	// setting this mainly prevents Turret_RestoreDefaultDropPitch() from running
	
	turret thread turret_handleOwnerDisconnect();

	owner SetPlayerData( "remoteTurretDamageFade", 1.0 );
	owner SetPlayerData( "remoteTurretDamaged", 0 );
	owner SetPlayerData( "remoteTurretDamageState", 0 );

	turret.damageFade = 1.0;
	turret thread turret_incrementDamageFade();
	turret thread turret_watchLowHealth();

	return turret;
}

//turret_createBombSquadModel() // self == turret
//{
//	bombSquadModel = spawn( "script_model", self.origin );
//	bombSquadModel.angles = self.angles;
//	bombSquadModel hide();
//
//	team = undefined;
//	if( level.teambased )
//		team = level.otherTeam[ self.team ];
//
//	bombSquadModel thread maps\mp\gametypes\_weapons::bombSquadVisibilityUpdater( team, self.owner );
//	bombSquadModel SetModel( level.turretSettings[ self.turretType ].modelBombSquad );
//	bombSquadModel linkTo( self );
//	bombSquadModel SetContents( 0 );
//
//	self waittill ( "death" );
//
//	bombSquadModel delete();
//}

watchControllerChanges( turret, altmessage, ccpmessage, wiimessage )
{
	self notify( "clearlowermessage" );
	turret endon( "death" );
	self endon( "clearlowermessage" );
//EO	
	if (!using_wii())
		self setLowerMessage( altmessage, ccpmessage, undefined, undefined, undefined, true, 0.25, 3.0 );
	else
	{
		classic = -1;
		while (1)
		{
			newclassic = self using_classic_controller();
			if ( newclassic != classic )
			{
				if (!newclassic)
					self setLowerMessage( altmessage, wiimessage, undefined, undefined, undefined, true, 0.25, 3.0 );
				else
					self setLowerMessage( altmessage, ccpmessage, undefined, undefined, undefined, true, 0.25, 3.0 );
				classic = newclassic;
			}
			wait 0.07;	
		}
	}
}


turret_setActive() // self == turret
{
	self endon( "death" );
	self.owner endon( "disconnect" );

	self SetDefaultDropPitch( 0.0 );
	self MakeUnusable();
	self MakeTurretSolid();

	if( !IsDefined( self.owner ) )
		return;

	owner = self.owner;

	// spawn a trigger so we know if the owner is within range to pick it up
	self.ownerTrigger = Spawn( "trigger_radius", self.origin + ( 0, 0, 1 ), 0, 32, 64 );
	assert( IsDefined( self.ownerTrigger ) );
	owner thread turret_handlePickup( self );

	// destroy any other remote turrets and put this one in the list
	if( IsDefined( owner.remoteTurretList ) )
	{
		foreach( turret in owner.remoteTurretList )
		{
			turret notify( "death" );
		}
	}
	owner.remoteTurretList = [];
	owner.remoteTurretList[0] = self;

	// show a message to enter the turret
	owner.using_remote_turret = false;
	if( IsAlive( owner ) )
		owner thread watchControllerChanges( self, "enter_remote_turret", level.turretSettings[ self.turretType ].hintEnter, level.turretSettings[ self.turretType ].hintEnterWii );
//		owner setLowerMessage( "enter_remote_turret", level.turretSettings[ self.turretType ].hintEnter, undefined, undefined, undefined, true, 0.25, 3.0 );

	owner thread watchOwnerMessageOnDeath( self );

	if ( level.teamBased )
	{
		self.team = owner.team;
		self setTurretTeam( owner.team );
		self maps\mp\_entityheadicons::setTeamHeadIcon( self.team, ( 0, 0, 65 ) );
	}
	else
	{
		self maps\mp\_entityheadicons::setPlayerHeadIcon( self.owner, ( 0, 0, 65 ) );
	}

	self thread watchEnterAndExit();
	self thread turret_handleDeath();
	self thread turret_handleDamage();
	self thread turret_timeOut();
	//self thread turret_createBombSquadModel();
	self thread turret_blinky_light();
}

startUsingRemoteTurret() // self == turret
{
	owner = self.owner;

	owner setUsingRemote( self.turretType );

	owner freezeControlsWrapper( true );
	result = owner maps\mp\killstreaks\_killstreaks::initRideKillstreak();
	if( result != "success" )
	{
		if ( result != "disconnect" )
			owner clearUsingRemote();

		return false;
	}	

	owner _giveWeapon( level.turretSettings[ self.turretType ].remoteInfo );
	owner SwitchToWeaponImmediate( level.turretSettings[ self.turretType ].remoteInfo );

	owner freezeControlsWrapper( false );

	// with the way we do visionsets we need to wait for the clearRideIntro() is done before we set thermal
	owner thread waitSetThermal( 1.0, self );

	if ( !isdefined( level.HUDItem ) )
		level.HUDItem = [];
		
	if ( isdefined( level.HUDItem[ "thermal_mode" ] ) )
		level.HUDItem[ "thermal_mode" ] settext ( "" );

	if ( getDvarInt( "camera_thirdPerson" ) )
		owner setThirdPersonDOF( false );

	owner PlayerLinkWeaponViewToDelta( self, "tag_player", 0, 180, 180, 50, 25, false );
	owner PlayerLinkedSetViewZNear( false );
	owner PlayerLinkedSetUseBaseAngleForViewClamp( true );
	owner RemoteControlTurret( self );

	owner notify( "clearlowermessage" );
	owner clearLowerMessage( "enter_remote_turret" );
	owner thread watchControllerChanges( self, "early_exit", level.turretSettings[ self.turretType ].hintExit, level.turretSettings[ self.turretType ].hintExitWii );
	//owner setLowerMessage( "early_exit", level.turretSettings[ self.turretType ].hintExit );

	if( owner isJuggernaut() )
		owner.juggernautOverlay.alpha = 0;
}

waitSetThermal( delay, remoteTurret )
{
	self endon( "disconnect" );
	remoteTurret endon( "death" );

	wait( delay	);

	self VisionSetThermalForPlayer( game["thermal_vision"], 1.5 );
	self ThermalVisionOn();
	self ThermalVisionFOFOverlayOn();
}

stopUsingRemoteTurret() // self == turret
{
	owner = self.owner;

	if ( owner isUsingRemote() )
	{
		owner ThermalVisionOff();
		owner ThermalVisionFOFOverlayOff();
		owner RemoteControlTurretOff( self );
		owner unlink();
		owner switchToWeapon( owner getLastWeapon() );
		owner clearUsingRemote();

		if ( getDvarInt( "camera_thirdPerson" ) )
			owner setThirdPersonDOF( true );

		owner VisionSetThermalForPlayer( game["thermal_vision"], 0 );

		// take the killstreak weapon
		killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( level.turretSettings[ self.turretType ].streakName );
		owner TakeWeapon( killstreakWeapon );
	}
	if( self.stunned )
	{
		owner StopShellShock();
	}
	owner notify( "clearlowermessage" );
	owner clearLowerMessage( "early_exit" );
	if( !IsDefined( owner.using_remote_turret_when_died ) || !owner.using_remote_turret_when_died )
		owner thread watchControllerChanges( self, "enter_remote_turret", level.turretSettings[ self.turretType ].hintEnter, level.turretSettings[ self.turretType ].hintEnterWii );
		//owner setLowerMessage( "enter_remote_turret", level.turretSettings[ self.turretType ].hintEnter, undefined, undefined, undefined, true, 0.25, 3.0 );

	if( owner isJuggernaut() )
		owner.juggernautOverlay.alpha = 1;

	self notify( "exit" );
}

watchOwnerMessageOnDeath( turret ) // self == owner
{
	self endon( "disconnect" );
	turret endon( "death" );

	// we need to reset the lower message when the owner dies, this way the respawn message shows
	self.using_remote_turret_when_died = false;
	while( true )
	{
		if( IsAlive( self ) )
			self waittill( "death" );

		self notify( "clearlowermessage" );
		self clearLowerMessage( "enter_remote_turret" );
		self clearLowerMessage( "pickup_remote_turret" );

		if( self.using_remote_turret )
			self.using_remote_turret_when_died = true;
		else
			self.using_remote_turret_when_died = false;

		self waittill( "spawned_player" );
		
		if( !self.using_remote_turret_when_died )
			self thread watchControllerChanges( turret, "enter_remote_turret", level.turretSettings[ self.turretType ].hintEnter, level.turretSettings[ self.turretType ].hintEnterWii );
//			self setLowerMessage( "enter_remote_turret", level.turretSettings[ turret.turretType ].hintEnter, undefined, undefined, undefined, true, 0.25, 3.0 );
		else
			turret notify( "death" );
	}
}

ActivateButtonPressed()
{
	if ( using_wii() )
	{
		if (!self using_classic_controller())
		{
			return self InventoryButtonPressed();
		}
	}
	return self UseButtonPressed();
}


watchEnterAndExit() // self == turret
{
	self endon( "death" );
	self endon( "carried" );
	level endon( "game_ended" );

	owner = self.owner;
	while( true )
	{
		// need to make sure we can't get into the remote turret while already in a killstreak (like ac130)
		currentWeapon = owner GetCurrentWeapon();
		if( isKillstreakWeapon( currentWeapon ) && 
			currentWeapon != level.turretSettings[ self.turretType ].weaponInfo && 
			currentWeapon != level.turretSettings[ self.turretType ].laptopInfo && 
			currentWeapon != level.turretSettings[ self.turretType ].remoteInfo && 
			currentWeapon != "none" &&
			( !owner isJuggernaut() || owner isUsingRemote() ) )
		{
			if( !IsDefined( owner.enter_message_deleted ) || !owner.enter_message_deleted )
			{
				owner.enter_message_deleted = true;
				owner notify( "clearlowermessage" );
				owner clearLowerMessage( "enter_remote_turret" );
			}
			wait( 0.05 );
			continue;
		}

		// since we can pick this back up, if we're in the trigger clear the message
		if( owner IsTouching( self.ownerTrigger ) )
		{
			if( !IsDefined( owner.enter_message_deleted ) || !owner.enter_message_deleted )
			{
				owner.enter_message_deleted = true;
				owner clearLowerMessage( "enter_remote_turret" );
			}
			wait( 0.05 );
			continue;
		}

		// if we had to delete the message while in a killstreak, bring it back once we're done
		if( IsDefined( owner.enter_message_deleted ) && 
			owner.enter_message_deleted && 
			currentWeapon != "none" )
		{
			owner thread watchControllerChanges( self, "enter_remote_turret", level.turretSettings[ self.turretType ].hintEnter, level.turretSettings[ self.turretType ].hintEnterWii );
			//owner setLowerMessage( "enter_remote_turret", level.turretSettings[ self.turretType ].hintEnter, undefined, undefined, undefined, true, 0.25, 3.0 );
			owner.enter_message_deleted = false;
		}

		// entering and exiting the remote turret
		timeUsed = 0;
		while(	owner ActivateButtonPressed() && 
				!owner FragButtonPressed() && 
				!IsDefined( owner.throwingGrenade ) &&
				!owner SecondaryOffhandButtonPressed() &&
				!owner IsUsingTurret() &&
				owner IsOnGround() &&
				!owner IsTouching( self.ownerTrigger ) )
		{
			if( IsDefined( owner.isCarrying ) && owner.isCarrying )
				break;

			if( IsDefined( owner.isCapturingCrate ) && owner.isCapturingCrate )
				break;

			if( !IsAlive( owner ) )
				break;

			if( !owner.using_remote_turret && owner isUsingRemote() )
				break;

			timeUsed += 0.066;
			if( timeUsed > 0.75 )
			{
				owner.using_remote_turret = !owner.using_remote_turret;
				
				if( owner.using_remote_turret )
				{
					owner removeWeapons();
					owner takeKillstreakWeapons( self.turretType );
					owner _giveWeapon( level.turretSettings[ self.turretType ].laptopInfo );
					owner SwitchToWeaponImmediate( level.turretSettings[ self.turretType ].laptopInfo );

					self startUsingRemoteTurret();

					owner restoreWeapons();
				}
				else
				{
					owner takeKillstreakWeapons( self.turretType );
					self stopUsingRemoteTurret();
				}

				wait( 2.0 ); // this wait is to keep you from going in and out by holding X too long
				break;
			}

			wait( 0.05 );
		}

		wait( 0.05 );
	}
}

turret_handlePickup( turret ) // self == owner (player)
{
	self endon( "disconnect" );
	level endon( "game_ended" );
	turret endon( "death" );

	if( !IsDefined( turret.ownerTrigger ) )
		return;
	
	// defensive bot hack because they keep picking it up right after they place it
	if( IsDefined( self.pers["isBot"] ) && self.pers["isBot"] )
		return;

	buttonTime = 0;
	while( true )
	{
		// need to make sure we can't pick up the remote turret while already in a killstreak (like ac130)
		currentWeapon = self GetCurrentWeapon();
		if( isKillstreakWeapon( currentWeapon ) && 
			currentWeapon != level.turretSettings[ turret.turretType ].weaponInfo && 
			currentWeapon != level.turretSettings[ turret.turretType ].laptopInfo && 
			currentWeapon != level.turretSettings[ turret.turretType ].remoteInfo && 
			currentWeapon != "none" &&
			( !self isJuggernaut() || self isUsingRemote() ) )
		{
			if( !IsDefined( self.pickup_message_deleted ) || !self.pickup_message_deleted )
			{
				self.pickup_message_deleted = true;
				self clearLowerMessage( "pickup_remote_turret" );
			}
			wait( 0.05 );
			continue;
		}

		// since we can pick this back up, if we're not in the trigger clear the message
		if( !self IsTouching( turret.ownerTrigger ) )
		{
			if( !IsDefined( self.pickup_message_deleted ) || !self.pickup_message_deleted )
			{
				self.pickup_message_deleted = true;
				self clearLowerMessage( "pickup_remote_turret" );
			}
			wait( 0.05 );
			continue;
		}

		if( isReallyAlive( self ) && 
			self IsTouching( turret.ownerTrigger ) && 
			!IsDefined( turret.carriedBy ) &&
			self IsOnGround() )
		{
			// if we had to delete the message while in a killstreak, bring it back once we're done
			if( IsDefined( self.pickup_message_deleted ) && 
				self.pickup_message_deleted && 
				currentWeapon != "none" )
			{
				self setLowerMessage( "pickup_remote_turret", level.turretSettings[ turret.turretType ].hintPickUp, undefined, undefined, undefined, true, 0.25, 3.0, true );
				self.pickup_message_deleted = false;
			}

			if ( self UseButtonPressed() )
			{
				if( IsDefined( self.using_remote_turret ) && self.using_remote_turret )
					continue;

				buttonTime = 0;
				while ( self UseButtonPressed() )
				{
					buttonTime += 0.05;
					wait( 0.05 );
				}

				println( "pressTime1: " + buttonTime );
				if ( buttonTime >= 0.5 )
					continue;

				buttonTime = 0;
				while ( !self UseButtonPressed() && buttonTime < 0.5 )
				{
					buttonTime += 0.05;
					wait( 0.05 );
				}

				println( "delayTime: " + buttonTime );
				if ( buttonTime >= 0.5 )
					continue;

				if ( !isReallyAlive( self ) )
					continue;

				if( IsDefined( self.using_remote_turret ) && self.using_remote_turret )
					continue;

				turret SetMode( level.turretSettings[ turret.turretType ].sentryModeOff );
				self thread setCarryingTurret( turret, false );
				turret.ownerTrigger delete();
				self.remoteTurretList = undefined;
				self.pickup_message_deleted = undefined;
				self clearLowerMessage( "pickup_remote_turret" );
				return;
			}
		}
		wait( 0.05 );
	}
}

turret_blinky_light() // self == turret
{
	self endon( "death" );
	self endon( "carried" );

	while ( true )
	{
		//PlayLoopedFX( getfx( "antenna_light_mp" ), 1.0, self GetTagOrigin( "tag_fx" ) );
		PlayFXOnTag( getfx( "antenna_light_mp" ), self, "tag_fx" );
		wait( 1.0 );
		StopFXOnTag( getfx( "antenna_light_mp" ), self, "tag_fx" );
	}
}

turret_setInactive() // self == turret
{
	self SetMode( level.turretSettings[ self.turretType ].sentryModeOff );

	if ( level.teamBased )
		self maps\mp\_entityheadicons::setTeamHeadIcon( "none", ( 0, 0, 0 ) );
	else if ( isDefined( self.owner ) )
		self maps\mp\_entityheadicons::setPlayerHeadIcon( undefined, ( 0, 0, 0 ) );

	if( !IsDefined( self.owner ) )
		return;

	owner = self.owner;

	if( IsDefined( owner.using_remote_turret ) && owner.using_remote_turret )
	{
		owner ThermalVisionOff();
		owner ThermalVisionFOFOverlayOff();
		owner RemoteControlTurretOff( self );
		owner unlink();
		owner switchToWeapon( owner getLastWeapon() );
		owner clearUsingRemote();

		if ( getDvarInt( "camera_thirdPerson" ) )
			owner setThirdPersonDOF( true );

		// need to clear the vision set because the turret could die while the player is fading into it, this will kick them back to their visionset
		// the problem comes up because we are ending on death in the function that calls initRideKillstreak(), so it doesn't get to finish
		owner maps\mp\killstreaks\_killstreaks::clearRideIntro();
		owner VisionSetThermalForPlayer( game["thermal_vision"], 0 );

		// just in case the turret is killed before you can get in it, the initRideKillstreak() does _disableUsability() and we unfortunately kill the thread on death
		if( IsDefined( owner.disabledUsability ) && owner.disabledUsability )
			owner _enableUsability();

		owner takeKillstreakWeapons( self.turretType );

		// turn juggernaut overlay back on
		if( owner isJuggernaut() )
			owner.juggernautOverlay.alpha = 1;
	}
}

turret_handleOwnerDisconnect() // self == turret
{
	self endon ( "death" );
	level endon ( "game_ended" );

	self notify ( "turret_handleOwner" );
	self endon ( "turret_handleOwner" );

	self.owner waittill_any( "disconnect", "joined_team", "joined_spectators" );

	self notify( "death" );
}

turret_timeOut() // self == turret
{
	self endon( "death" );
	level endon ( "game_ended" );

	lifeSpan = level.turretSettings[ self.turretType ].timeOut;
/#
	lifeSpan = GetDvarInt( "scr_remote_turret_timeout", 60 );
#/
	while ( lifeSpan )
	{
		wait ( 1.0 );
		maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();

		if ( !IsDefined( self.carriedBy ) )
			lifeSpan = max( 0, lifeSpan - 1.0 );
	}

	if ( isDefined( self.owner ) )
		self.owner thread leaderDialogOnPlayer( "sentry_gone" );

	self notify ( "death" );
}

turret_handleDeath() // self == turret
{
	self endon( "carried" );

	entNum = self GetEntityNumber();

	self maps\mp\killstreaks\_autosentry::addToTurretList( entNum );

	self waittill ( "death" );

	self maps\mp\killstreaks\_autosentry::removeFromTurretList( entNum );

	// this handles cases of deletion
	if ( !isDefined( self ) )
		return;

	self SetModel( level.turretSettings[ self.turretType ].modelDestroyed );

	self turret_setInactive();
	self setDefaultDropPitch( 40 );
	self SetSentryOwner( undefined );
	self SetTurretMinimapVisible( false );

	if( IsDefined( self.ownerTrigger ) )
		self.ownerTrigger delete();

	owner = self.owner;
	if( IsDefined( owner ) )
	{
		owner.using_remote_turret = false;
		owner clearLowerMessage( "enter_remote_turret" );
		owner clearLowerMessage( "early_exit" );
		owner clearLowerMessage( "pickup_remote_turret" );
		
		owner SetPlayerData( "remoteTurretDamageState", 0 );

		owner restorePerks();
		owner restoreWeapons();
		if( owner GetCurrentWeapon() == "none" )
			owner SwitchToWeapon( owner getLastWeapon() );
	}

	// TODO: get sound
	self playSound( "sentry_explode" );		

	PlayFXOnTag( getFx( "sentry_explode_mp" ), self, "tag_aim" );
	wait ( 1.5 );		
	self playSound( "sentry_explode_smoke" );
	for ( smokeTime = 8; smokeTime > 0; smokeTime -= 0.4 )
	{
		PlayFXOnTag( getFx( "sentry_smoke_mp" ), self, "tag_aim" );
		wait ( 0.4 );
	}
	self notify( "deleting" );

	if( IsDefined( self.target_ent ) )
		self.target_ent delete();

	self delete();
}

turret_handleDamage() // self == turret
{
	self endon( "death" );
	self endon( "carried" );
	//self.owner endon( "death" );

	self SetCanDamage( true );

	while( true )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );

		// don't allow people to destroy equipment on their team if FF is off
		if ( !maps\mp\gametypes\_weapons::friendlyFireCheck( self.owner, attacker ) )
			continue;

		if( IsDefined( weapon ) )
		{
			switch( weapon )
			{
			case "concussion_grenade_mp":
			case "flash_grenade_mp":
				if( meansOfDeath == "MOD_GRENADE_SPLASH" && self.owner.using_remote_turret )
				{
					self.stunned = true;
					self thread turret_stun();
				}
			case "smoke_grenade_mp":
				continue;
			}
		}

		if ( !IsDefined( self ) )
			return;

		if ( meansOfDeath == "MOD_MELEE" )
			self.damageTaken += self.maxHealth;

		if ( IsDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
			self.wasDamagedFromBulletPenetration = true;

		self.wasDamaged = true;
		
		self.damageFade = 0.0;
		self.owner SetPlayerData( "remoteTurretDamaged", 1 );

		modifiedDamage = damage;
		if( IsPlayer( attacker ) )
		{
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "remote_turret" );

			if ( attacker _hasPerk( "specialty_armorpiercing" ) )
			{
				modifiedDamage = damage * level.armorPiercingMod;			
			}
		}

		// in case we are shooting from a remote position, like being in the osprey gunner shooting this
		if( IsDefined( attacker.owner ) && IsPlayer( attacker.owner ) )
		{
			attacker.owner maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "remote_turret" );
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

			case "artillery_mp":
			case "stealth_bomb_mp":
				self.largeProjectileDamage = false;
				modifiedDamage += ( damage * 4 );
				break;

			case "bomb_site_mp":
			case "emp_grenade_mp":
				self.largeProjectileDamage = false;
				modifiedDamage = self.maxHealth + 1;
				break;
			}
		}

		self.damageTaken += modifiedDamage;

		if ( self.damageTaken >= self.maxHealth )
		{
			if ( IsPlayer( attacker ) && ( !IsDefined( self.owner ) || attacker != self.owner ) )
			{
				attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 100, weapon, meansOfDeath );				
				attacker notify( "destroyed_killstreak" );
			}
			if ( IsDefined( self.owner ) )
				self.owner thread leaderDialogOnPlayer( level.turretSettings[ self.turretType ].voDestroyed );

			self notify ( "death" );
			return;
		}
	}
}

turret_incrementDamageFade() // self == turret
{
	self endon( "death" );
	level endon( "game_ended" );

	// this is for the ui
	damaged = false;
	while( true )
	{
		if( self.damageFade < 1.0 )
		{
			self.owner SetPlayerData( "remoteTurretDamageFade", self.damageFade );
			self.damageFade += 0.1;
			damaged = true;
		}
		else
		{
			if( damaged )
			{
				self.damageFade = 1.0;
				self.owner SetPlayerData( "remoteTurretDamageFade", self.damageFade );
				
				self.owner SetPlayerData( "remoteTurretDamaged", 0 );
				damaged = false;
			}
		}
		wait( 0.1 );
	}
}

turret_watchLowHealth() // self == turret
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

				self.owner SetPlayerData( "remoteTurretDamageState", damageState );
				damageState++;
			}
		}
		else
		{
			if( self.damageTaken >= ( self.maxHealth * ( percentage * damageState ) )  )
			{
				self.owner SetPlayerData( "remoteTurretDamageState", damageState );
				damageState++;
			}
		}
		wait( 0.05 );
	}
}

turret_stun() // self == turret
{
	self notify( "stunned" );
	self endon( "stunned" );
	self endon( "death" );

	while( self.stunned )
	{
		self.owner ShellShock( "concussion_grenade_mp", self.stunnedTime );
		PlayFXOnTag( getFx( "sentry_explode_mp" ), self, "tag_origin" );

		time = 0;
		while( time < self.stunnedTime )
		{
			time += 0.066;
			wait( 0.05 );
		}

		self.stunned = false;
	}
}
