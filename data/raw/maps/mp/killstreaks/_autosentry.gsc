#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;


init()
{
	level.sentryType = [];
	level.sentryType[ "sentry_minigun" ] 	= "sentry";
	//level.sentryType[ "minigun_turret" ] 	= "minigun_turret";
	//level.sentryType[ "gl_turret" ] 		= "gl_turret";
	level.sentryType[ "sam_turret" ] 		= "sam_turret";
	
	level.killStreakFuncs[ level.sentryType[ "sentry_minigun" ] ] 	= ::tryUseAutoSentry;
	//level.killStreakFuncs[ level.sentryType[ "minigun_turret" ] ] 	= ::tryUseMinigun;
	//level.killStreakFuncs[ level.sentryType[ "gl_turret" ] ] 		= ::tryUseGL;
	level.killStreakFuncs[ level.sentryType[ "sam_turret" ] ] 		= ::tryUseSAM;
	
	level.sentrySettings = [];
	
	level.sentrySettings[ "sentry_minigun" ] = spawnStruct();
	level.sentrySettings[ "sentry_minigun" ].health =				999999; // keep it from dying anywhere in code
	level.sentrySettings[ "sentry_minigun" ].maxHealth =			1000; // this is the health we'll check
	level.sentrySettings[ "sentry_minigun" ].burstMin =				20;
	level.sentrySettings[ "sentry_minigun" ].burstMax =				120;
	level.sentrySettings[ "sentry_minigun" ].pauseMin =				0.15;
	level.sentrySettings[ "sentry_minigun" ].pauseMax =				0.35;	
	level.sentrySettings[ "sentry_minigun" ].sentryModeOn =			"sentry";	
	level.sentrySettings[ "sentry_minigun" ].sentryModeOff =		"sentry_offline";	
	level.sentrySettings[ "sentry_minigun" ].timeOut =				90.0;	
	level.sentrySettings[ "sentry_minigun" ].spinupTime =			0.05;	
	level.sentrySettings[ "sentry_minigun" ].overheatTime =			8.0;	
	level.sentrySettings[ "sentry_minigun" ].cooldownTime =			0.1;	
	level.sentrySettings[ "sentry_minigun" ].fxTime =				0.3;	
	level.sentrySettings[ "sentry_minigun" ].streakName =			"sentry";
	level.sentrySettings[ "sentry_minigun" ].weaponInfo =			"sentry_minigun_mp";
	level.sentrySettings[ "sentry_minigun" ].modelBase =			"sentry_minigun_weak";
	level.sentrySettings[ "sentry_minigun" ].modelPlacement =		"sentry_minigun_weak_obj";
	level.sentrySettings[ "sentry_minigun" ].modelPlacementFailed = "sentry_minigun_weak_obj";
	level.sentrySettings[ "sentry_minigun" ].modelDestroyed =		"sentry_minigun_weak_destroyed";	
	level.sentrySettings[ "sentry_minigun" ].hintString =			&"SENTRY_PICKUP";	
	level.sentrySettings[ "sentry_minigun" ].headIcon =				true;	
	level.sentrySettings[ "sentry_minigun" ].teamSplash =			"used_sentry";	
	level.sentrySettings[ "sentry_minigun" ].shouldSplash =			false;	
	level.sentrySettings[ "sentry_minigun" ].voDestroyed =			"sentry_destroyed";	

	//level.sentrySettings[ "minigun_turret" ] = spawnStruct();
	//level.sentrySettings[ "minigun_turret" ].sentryModeOn =			"manual";	
	//level.sentrySettings[ "minigun_turret" ].sentryModeOff =		"sentry_offline";	
	//level.sentrySettings[ "minigun_turret" ].timeOut =				90.0;	
	//level.sentrySettings[ "minigun_turret" ].spinupTime =			0.05;	
	//level.sentrySettings[ "minigun_turret" ].overheatTime =			4.0;	
	//level.sentrySettings[ "minigun_turret" ].cooldownTime =			0.5;	
	//level.sentrySettings[ "minigun_turret" ].fxTime =				0.3;	
	//level.sentrySettings[ "minigun_turret" ].weaponInfo =			"manned_minigun_turret_mp";
	//level.sentrySettings[ "minigun_turret" ].modelBase =			"sentry_minigun";
	//level.sentrySettings[ "minigun_turret" ].modelPlacement =		"sentry_minigun_obj";
	//level.sentrySettings[ "minigun_turret" ].modelPlacementFailed = "sentry_minigun_obj_red";
	//level.sentrySettings[ "minigun_turret" ].modelDestroyed =		"sentry_minigun_destroyed";		
	//level.sentrySettings[ "minigun_turret" ].hintString =			&"PLATFORM_HOLD_TO_USE";	
	//level.sentrySettings[ "minigun_turret" ].ownerHintString =		&"MP_DOUBLE_TAP_TO_CARRY";	
	//level.sentrySettings[ "minigun_turret" ].headIcon =				false;	
	//level.sentrySettings[ "minigun_turret" ].teamSplash =			"used_minigun_turret";	
	//level.sentrySettings[ "minigun_turret" ].shouldSplash =			false;	
	//level.sentrySettings[ "minigun_turret" ].voDestroyed =			"sentry_destroyed";	

	//level.sentrySettings[ "gl_turret" ] = spawnStruct();
	//level.sentrySettings[ "gl_turret" ].sentryModeOn =			"manual";	
	//level.sentrySettings[ "gl_turret" ].sentryModeOff =			"sentry_offline";	
	//level.sentrySettings[ "gl_turret" ].timeOut =				90.0;	
	//level.sentrySettings[ "gl_turret" ].spinupTime =			0.05;	
	//level.sentrySettings[ "gl_turret" ].overheatTime =			2.5;	
	//level.sentrySettings[ "gl_turret" ].cooldownTime =			0.5;	
	//level.sentrySettings[ "gl_turret" ].fxTime =				0.3;	
	//level.sentrySettings[ "gl_turret" ].weaponInfo =			"manned_gl_turret_mp";
	//level.sentrySettings[ "gl_turret" ].modelBase =				"sentry_minigun";
	//level.sentrySettings[ "gl_turret" ].modelPlacement =		"sentry_minigun_obj";
	//level.sentrySettings[ "gl_turret" ].modelPlacementFailed =	"sentry_minigun_obj_red";
	//level.sentrySettings[ "gl_turret" ].modelDestroyed =		"sentry_minigun_destroyed";		
	//level.sentrySettings[ "gl_turret" ].hintString =			&"PLATFORM_HOLD_TO_USE";	
	//level.sentrySettings[ "gl_turret" ].ownerHintString =		&"MP_DOUBLE_TAP_TO_CARRY";	
	//level.sentrySettings[ "gl_turret" ].headIcon =				false;	
	//level.sentrySettings[ "gl_turret" ].teamSplash =			"used_gl_turret";	
	//level.sentrySettings[ "gl_turret" ].shouldSplash =			false;	
	//level.sentrySettings[ "gl_turret" ].voDestroyed =			"sentry_destroyed";	

	level.sentrySettings[ "sam_turret" ] = spawnStruct();
	level.sentrySettings[ "sam_turret" ].health =				999999; // keep it from dying anywhere in code
	level.sentrySettings[ "sam_turret" ].maxHealth =			1000; // this is the health we'll check
	level.sentrySettings[ "sam_turret" ].burstMin =				20;
	level.sentrySettings[ "sam_turret" ].burstMax =				120;
	level.sentrySettings[ "sam_turret" ].pauseMin =				0.15;
	level.sentrySettings[ "sam_turret" ].pauseMax =				0.35;	
	level.sentrySettings[ "sam_turret" ].sentryModeOn =			"sentry";	
	level.sentrySettings[ "sam_turret" ].sentryModeOff =		"sentry_offline";	
	level.sentrySettings[ "sam_turret" ].timeOut =				90.0;	
	level.sentrySettings[ "sam_turret" ].spinupTime =			0.05;	
	level.sentrySettings[ "sam_turret" ].overheatTime =			8.0;	
	level.sentrySettings[ "sam_turret" ].cooldownTime =			0.1;	
	level.sentrySettings[ "sam_turret" ].fxTime =				0.3;	
	level.sentrySettings[ "sam_turret" ].streakName =			"sam_turret";
	level.sentrySettings[ "sam_turret" ].weaponInfo =			"sam_mp";
	level.sentrySettings[ "sam_turret" ].modelBase =			"mp_sam_turret";
	level.sentrySettings[ "sam_turret" ].modelPlacement =		"mp_sam_turret_placement";
	level.sentrySettings[ "sam_turret" ].modelPlacementFailed = "mp_sam_turret_placement";
	level.sentrySettings[ "sam_turret" ].modelDestroyed =		"mp_sam_turret";	
	level.sentrySettings[ "sam_turret" ].hintString =			&"SENTRY_PICKUP";	
	level.sentrySettings[ "sam_turret" ].headIcon =				true;	
	level.sentrySettings[ "sam_turret" ].teamSplash =			"used_sam_turret";	
	level.sentrySettings[ "sam_turret" ].shouldSplash =			false;	
	level.sentrySettings[ "sam_turret" ].voDestroyed =			"sam_destroyed";	

	foreach ( sentryInfo in level.sentrySettings )
	{
		precacheItem( sentryInfo.weaponInfo );
		precacheModel( sentryInfo.modelBase );		
		precacheModel( sentryInfo.modelPlacement );		
		precacheModel( sentryInfo.modelPlacementFailed );		
		precacheModel( sentryInfo.modelDestroyed );		
		PreCacheString( sentryInfo.hintString );	
		if( IsDefined( sentryInfo.ownerHintString ) )
			PreCacheString( sentryInfo.ownerHintString );
	}

	PreCacheItem( "sam_projectile_mp" );

	level._effect[ "sentry_overheat_mp" ]	= loadfx( "smoke/sentry_turret_overheat_smoke" );
	level._effect[ "sentry_explode_mp" ]	= loadfx( "explosions/sentry_gun_explosion" );
	level._effect[ "sentry_smoke_mp" ]		= loadfx( "smoke/car_damage_blacksmoke" );

/#
	SetDevDvarIfUninitialized( "scr_sam_timeout", 90.0 );
#/
}

/* ============================
	Killstreak Functions
   ============================ */

tryUseAutoSentry( lifeId )
{
	result = self giveSentry( "sentry_minigun" );
	if ( result )
	{
		self maps\mp\_matchdata::logKillstreakEvent( level.sentrySettings[ "sentry_minigun" ].streakName, self.origin );

		// take the killstreak weapon
		killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( level.sentrySettings[ "sentry_minigun" ].streakName );
		self TakeWeapon( killstreakWeapon );
	}
	
	return ( result );
}

//tryUseMinigun( lifeId )
//{
//	result = self giveSentry( "minigun_turret" );
//	if ( result )
//		self maps\mp\_matchdata::logKillstreakEvent( "minigun_turret", self.origin );
//	
//	return ( result );	
//}
//
//tryUseGL( lifeId )
//{
//	result = self giveSentry( "gl_turret" );
//	if ( result )
//		self maps\mp\_matchdata::logKillstreakEvent( "gl_turret", self.origin );
//
//	return ( result );	
//}
//
//tryUseAutoGlSentry( lifeId )
//{
//	result = self giveSentry( "sentry_gun" );
//	if ( result )
//		self maps\mp\_matchdata::logKillstreakEvent( "sentry_gl", self.origin );
//		
//	return ( result );
//}

tryUseSAM( lifeId )
{
	result = self giveSentry( "sam_turret" );
	if ( result )
	{
		self maps\mp\_matchdata::logKillstreakEvent( level.sentrySettings[ "sam_turret" ].streakName, self.origin );

		// take the killstreak weapon
		killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( level.sentrySettings[ "sam_turret" ].streakName );
		self TakeWeapon( killstreakWeapon );
	}

	return ( result );
}

giveSentry( sentryType )
{
	if ( ! self validateUseStreak() )
		return false;
	
	self.last_sentry = sentryType;

	sentryGun = createSentryForPlayer( sentryType, self );
	
	//	returning from this streak activation seems to strip this?
	//	manually removing and restoring
	self removePerks();		
	
	result = self setCarryingSentry( sentryGun, true );
	
	self thread waitRestorePerks();
	
	// we're done carrying for sure and sometimes this might not get reset
	// this fixes a bug where you could be carrying and have it in a place where it won't plant, get killed, now you can't scroll through killstreaks
	self.isCarrying = false;

	// if we failed to place the sentry, it will have been deleted at this point
	if ( IsDefined( sentryGun ) )
		return true;
	else
		return false;
}


/* ============================
	Player Functions
   ============================ */

setCarryingSentry( sentryGun, allowCancel )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	
	assert( isReallyAlive( self ) );
	
	sentryGun sentry_setCarried( self );
	
	self _disableWeapon();

	self notifyOnPlayerCommand( "place_sentry", "+attack" );
	self notifyOnPlayerCommand( "place_sentry", "+attack_akimbo_accessible" ); // support accessibility control scheme
	self notifyOnPlayerCommand( "cancel_sentry", "+actionslot 4" );
	
	for ( ;; )
	{
		result = waittill_any_return( "place_sentry", "cancel_sentry", "force_cancel_sentry" );

		if ( result == "cancel_sentry" || result == "force_cancel_sentry" )
		{
			if ( !allowCancel && result == "cancel_sentry" )
				continue;
				
			// failsafe because something takes away the killstreak weapon on occasions where you have them stacked in the gimme slot
			//	for example, if you stack uav, sam turret, emp and then use the emp, then pull out the sam turret, the list item weapon gets taken away before you plant it
			//	so to "fix" this, if the user cancels then we give the weapon back to them only if the selected killstreak is the same and the item list is zero
			//	this is done for anything you can pull out and plant (ims, sentry, sam turret, remote turret, remote tank)
			if( result == "cancel_sentry" )
			{
				killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( level.sentrySettings[ sentryGun.sentryType ].streakName );
				if( IsDefined( self.killstreakIndexWeapon ) && 
					killstreakWeapon == maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( self.pers["killstreaks"][self.killstreakIndexWeapon].streakName ) &&
					!( self GetWeaponsListItems() ).size )
				{
					self _giveWeapon( killstreakWeapon, 0 );
					self _setActionSlot( 4, "weapon", killstreakWeapon );
				}
			}

			sentryGun sentry_setCancelled();
			self _enableWeapon();		
			return false;
		}

		if ( !sentryGun.canBePlaced )
			continue;
			
		sentryGun sentry_setPlaced();		
		self _enableWeapon();		
		return true;
	}
}

removeWeapons()
{
	if ( self HasWeapon( "riotshield_mp" ) )
	{
		self.restoreWeapon = "riotshield_mp";
		self takeWeapon( "riotshield_mp" );
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

restoreWeapons()
{
	if ( IsDefined( self.restoreWeapon ) )	
	{
		self _giveWeapon( self.restoreWeapon );
		self.restoreWeapon = undefined;
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

/* ============================
	Sentry Functions
   ============================ */

createSentryForPlayer( sentryType, owner )
{
	assertEx( IsDefined( owner ), "createSentryForPlayer() called without owner specified" );

	sentryGun = spawnTurret( "misc_turret", owner.origin, level.sentrySettings[ sentryType ].weaponInfo );
	sentryGun.angles = owner.angles;
	
	sentryGun sentry_initSentry( sentryType, owner );
	
	return ( sentryGun );	
}


sentry_initSentry( sentryType, owner ) // self == sentry, turret, sam
{
	self.sentryType = sentryType;
	self.canBePlaced = true;

	self setModel( level.sentrySettings[ self.sentryType ].modelBase );
	self.shouldSplash = true; // we only want to splash on the first placement

	self setCanDamage( true );
	switch( sentryType )
	{
	case "minigun_turret":
	case "gl_turret":
		self SetLeftArc( 80 );
		self SetRightArc( 80 );
		self SetBottomArc( 50 );
		self SetDefaultDropPitch( 0.0 );
		self.originalOwner = owner;
		break;
	case "sam_turret":
		self makeTurretInoperable();
		self SetLeftArc( 180 );
		self SetRightArc( 180 );
		self SetTopArc( 80 );
		self SetDefaultDropPitch( -89.0 );	// setting this mainly prevents Turret_RestoreDefaultDropPitch() from running
		self.laser_on = false;
		
		// needs a kill cam ent
		killCamEnt = Spawn( "script_model", self GetTagOrigin( "tag_laser" ) );
		killCamEnt LinkTo( self );
		self.killCamEnt = killCamEnt;
		break;
	default:
		self makeTurretInoperable();
		self SetDefaultDropPitch( -89.0 );	// setting this mainly prevents Turret_RestoreDefaultDropPitch() from running
		break;
	}
	
	self setTurretModeChangeWait( true );
//	self setConvergenceTime( .25, "pitch" );
//	self setConvergenceTime( .25, "yaw" );
	self sentry_setInactive();
	
	self sentry_setOwner( owner );
	self thread sentry_handleDamage();
	self thread sentry_handleDeath();
	self thread sentry_timeOut();
	
	switch( sentryType )
	{
	case "minigun_turret":
		self.momentum = 0;
		self.heatLevel = 0;
		self.overheated = false;		
		self thread sentry_heatMonitor();
		break;
	case "gl_turret":
		self.momentum = 0;
		self.heatLevel = 0;
		self.cooldownWaitTime = 0;
		self.overheated = false;		
		self thread turret_heatMonitor();
		self thread turret_coolMonitor();
		break;
	case "sam_turret":
		self thread sentry_handleUse();
		self thread sentry_beepSounds();	
		break;
	default:
		self thread sentry_handleUse();
		self thread sentry_attackTargets();
		self thread sentry_beepSounds();	
		break;
	}
}


/* ============================
	Sentry Handlers
   ============================ */

sentry_handleDamage()
{
	self endon( "death" );
	level endon( "game_ended" );

	self.health = level.sentrySettings[ self.sentryType ].health;
	self.maxHealth = level.sentrySettings[ self.sentryType ].maxHealth;
	self.damageTaken = 0; // how much damage has it taken

	while ( true )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		
		// don't allow people to destroy equipment on their team if FF is off
		if ( !maps\mp\gametypes\_weapons::friendlyFireCheck( self.owner, attacker ) )
			continue;

		if ( IsDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
			self.wasDamagedFromBulletPenetration = true;

		// up the damage for airstrikes, stealth bombs, and bomb sites
		switch( weapon )
		{
		case "artillery_mp":
		case "stealth_bomb_mp":
			damage *= 4;
			break;
		case "bomb_site_mp":
			damage = self.maxHealth;
			break;
		}

		if ( meansOfDeath == "MOD_MELEE" )
			self.damageTaken += self.maxHealth;

		modifiedDamage = damage;
		if ( isPlayer( attacker ) )
		{
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "sentry" );

			if ( attacker _hasPerk( "specialty_armorpiercing" ) )
			{
				modifiedDamage = damage * level.armorPiercingMod;			
			}			
		}

		// in case we are shooting from a remote position, like being in the osprey gunner shooting this
		if( IsDefined( attacker.owner ) && IsPlayer( attacker.owner ) )
		{
			attacker.owner maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "sentry" );
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
			thread maps\mp\gametypes\_missions::vehicleKilled( self.owner, self, undefined, attacker, damage, meansOfDeath, weapon );

			if ( isPlayer( attacker ) && (!IsDefined(self.owner) || attacker != self.owner) )
			{
				attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 100, weapon, meansOfDeath );				
				attacker notify( "destroyed_killstreak" );
				
				if ( IsDefined( self.UAVRemoteMarkedBy ) && self.UAVRemoteMarkedBy != attacker )
					self.UAVRemoteMarkedBy thread maps\mp\killstreaks\_remoteuav::remoteUAV_processTaggedAssist();
			}
		
			if ( IsDefined( self.owner ) )
				self.owner thread leaderDialogOnPlayer( level.sentrySettings[ self.sentryType ].voDestroyed );
		
			self notify ( "death" );
			return;
		}
	}
}

sentry_watchDisabled()
{
	self endon( "carried" );
	self endon( "death" );
	level endon( "game_ended" );

	while( true )
	{
		// this handles any flash or concussion damage
		self waittill( "emp_damage", attacker, duration );

		PlayFXOnTag( getfx( "sentry_explode_mp" ), self, "tag_aim" );

		self SetDefaultDropPitch( 40 );
		self SetMode( level.sentrySettings[ self.sentryType ].sentryModeOff );

		wait( duration );

		self SetDefaultDropPitch( -89.0 );
		self SetMode( level.sentrySettings[ self.sentryType ].sentryModeOn );
	}
}

sentry_handleDeath()
{
	entNum = self GetEntityNumber();
	
	switch( self.sentryType )
	{
	case "gl_turret":
		break;
	default:
		self addToTurretList( entNum );
		break;
	}
	
	self waittill ( "death" );

	switch( self.sentryType )
	{
	case "gl_turret":
		break;
	default:
		self removeFromTurretList( entNum );
		break;
	}
	
	// this handles cases of deletion
	if ( !IsDefined( self ) )
		return;
		
	self setModel( level.sentrySettings[ self.sentryType ].modelDestroyed );

	self sentry_setInactive();
	self SetDefaultDropPitch( 40 );
	self SetSentryOwner( undefined );
	self SetTurretMinimapVisible( false );
	
	if( IsDefined( self.ownerTrigger ) )
		self.ownerTrigger delete();

	self playSound( "sentry_explode" );		
	
	switch( self.sentryType )
	{
	case "minigun_turret":
	case "gl_turret":
		self.forceDisable = true;
		self TurretFireDisable(); 
		break;
	default:
		break;
	}

	if ( IsDefined( self.inUseBy ) )
	{
		playFxOnTag( getFx( "sentry_explode_mp" ), self, "tag_origin" );
		playFxOnTag( getFx( "sentry_smoke_mp" ), self, "tag_aim" );
		
		self.inUseBy.turret_overheat_bar destroyElem();
		self.inUseBy restorePerks();
		self.inUseBy restoreWeapons();				
		
		self notify( "deleting" );
		wait ( 1.0 );
		StopFXOnTag( getFx( "sentry_explode_mp" ), self, "tag_origin" );
		StopFXOnTag( getFx( "sentry_smoke_mp" ), self, "tag_aim" );
	}	
	else
	{		
		playFxOnTag( getFx( "sentry_explode_mp" ), self, "tag_aim" );
		wait ( 1.5 );		
		self playSound( "sentry_explode_smoke" );
		for ( smokeTime = 8; smokeTime > 0; smokeTime -= 0.4 )
		{
			playFxOnTag( getFx( "sentry_smoke_mp" ), self, "tag_aim" );
			wait ( 0.4 );
		}
		self notify( "deleting" );
	}
		
	if( IsDefined( self.killCamEnt ) )
		self.killCamEnt delete();

	self delete();
}


sentry_handleUse()
{
	self endon ( "death" );
	level endon ( "game_ended" );
	
	for ( ;; )
	{
		self waittill ( "trigger", player );
		
		assert( player == self.owner );
		assert( !IsDefined( self.carriedBy ) );

		if ( !isReallyAlive( player ) )
			continue;
		
		if( self.sentryType == "sam_turret" )
			self setMode( level.sentrySettings[ self.sentryType ].sentryModeOff );

		player setCarryingSentry( self, false );
	}
}

turret_handlePickup( turret ) // self == owner (player)
{
	self endon( "disconnect" );
	level endon( "game_ended" );
	turret endon( "death" );

	if( !IsDefined( turret.ownerTrigger ) )
		return;

	buttonTime = 0;
	for ( ;; )
	{
		if( IsAlive( self ) && 
			self IsTouching( turret.ownerTrigger ) && 
			!IsDefined( turret.inUseBy ) && 
			!IsDefined( turret.carriedBy ) &&
			self IsOnGround() )
		{
			if ( self UseButtonPressed() )
			{
				if( IsDefined( self.using_remote_turret ) && self.using_remote_turret )
					continue;

				buttonTime = 0;
				while ( self UseButtonPressed() )
				{
					buttonTime += 0.066;
					wait( 0.05 );
				}

				println( "pressTime1: " + buttonTime );
				if ( buttonTime >= 0.66 )
					continue;

				buttonTime = 0;
				while ( !self UseButtonPressed() && buttonTime < 0.5 )
				{
					buttonTime += 0.066;
					wait( 0.05 );
				}

				println( "delayTime: " + buttonTime );
				if ( buttonTime >= 0.66 )
					continue;

				if ( !isReallyAlive( self ) )
					continue;

				if( IsDefined( self.using_remote_turret ) && self.using_remote_turret )
					continue;

				turret setMode( level.sentrySettings[ turret.sentryType ].sentryModeOff );
				self thread setCarryingSentry( turret, false );
				turret.ownerTrigger delete();
				return;
			}
		}
		wait( 0.05 );
	}
}

turret_handleUse() // self == turret
{
	self notify ( "turret_handluse" );
	self endon ( "turret_handleuse" );
	self endon ( "deleting" );
	level endon ( "game_ended" );
	
	self.forceDisable = false;
	colorStable = (1, 0.9, 0.7);
	colorUnstable = (1, 0.65, 0);
	colorOverheated = (1, 0.25, 0);
		
	for( ;; )
	{
		self waittill( "trigger", player );	
		
		//	exceptions
		if( IsDefined( self.carriedBy ) )
			continue;
		if( IsDefined( self.inUseBy ) )
			continue;
		if( !isReallyAlive( player ) )
			continue;		
		player removePerks();
		player removeWeapons();	
		
		//	ownership
		self.inUseBy = player;
		self setMode( level.sentrySettings[ self.sentryType ].sentryModeOff );
		self sentry_setOwner( player );	
		self setMode( level.sentrySettings[ self.sentryType ].sentryModeOn );							
		player thread turret_shotMonitor( self );
		
		//	overheat bar
		player.turret_overheat_bar = player createBar( colorStable, 100, 6 );
		player.turret_overheat_bar setPoint("CENTER", "BOTTOM", 0, -70 );		
		player.turret_overheat_bar.alpha = 0.65;
		player.turret_overheat_bar.bar.alpha = 0.65;
		
		//lastHeatLevel = self.heatLevel;
		//firing = false;
		
		playingHeatFX = false;
		
		for( ;; )
		{
			//	exceptions
			if ( !isReallyAlive( player ) )
			{
				self.inUseBy = undefined;
				player.turret_overheat_bar destroyElem();
				break;	
			}					
			if ( !player IsUsingTurret() )
			{
				self notify( "player_dismount" );
				self.inUseBy = undefined;
				player.turret_overheat_bar destroyElem();
				player restorePerks();
				player restoreWeapons();
				self setHintString( level.sentrySettings[ self.sentryType ].hintString );
				self setMode( level.sentrySettings[ self.sentryType ].sentryModeOff );
				self sentry_setOwner( self.originalOwner );	
				self setMode( level.sentrySettings[ self.sentryType ].sentryModeOn );							
				break;
			}
						
			if ( self.heatLevel >= level.sentrySettings[ self.sentryType ].overheatTime )
				barFrac = 1;
			else
				barFrac = self.heatLevel / level.sentrySettings[ self.sentryType ].overheatTime;
			player.turret_overheat_bar updateBar( barFrac );
			
			if ( self.forceDisable || self.overheated )
			{
				self TurretFireDisable();
				player.turret_overheat_bar.bar.color = colorOverheated;	
				playingHeatFX = false;			
			}
			else if ( self.heatLevel > level.sentrySettings[ self.sentryType ].overheatTime * 0.75  && self.sentryType == "minigun_turret" )
			{
				player.turret_overheat_bar.bar.color = colorUnstable;
				if ( RandomIntRange( 0, 10 ) < 6 )
					self TurretFireEnable();
				else
					self TurretFireDisable();
				if ( !playingHeatFX )
				{
					playingHeatFX = true;
					self thread PlayHeatFX();	
				}	
			}
			else
			{
				player.turret_overheat_bar.bar.color = colorStable;
				self TurretFireEnable();	
				playingHeatFX = false;
				self notify( "not_overheated" );		
			}
			/*
			if ( !firing && lastHeatLevel < self.heatLevel )
			{
				firing = true;
				self.momentum = 1;
				self StartBarrelSpin();
			}
			else if ( firing && lastHeatLevel > self.heatLevel )
			{
				firing = false;
				self.momentum = 0;
				self StopBarrelSpin();
			}			
			lastHeatLevel = self.heatLevel;
			*/
			wait( 0.05 );
		}
		self SetDefaultDropPitch( 0.0 );
	}
}

sentry_handleOwnerDisconnect()
{
	self endon ( "death" );
	level endon ( "game_ended" );
	
	self notify ( "sentry_handleOwner" );
	self endon ( "sentry_handleOwner" );
	
	self.owner waittill_any( "disconnect", "joined_team", "joined_spectators" );
	
	self notify( "death" );
}


/* ============================
	Sentry Utility Functions
   ============================ */

sentry_setOwner( owner )
{
	assertEx( IsDefined( owner ), "sentry_setOwner() called without owner specified" );
	assertEx( isPlayer( owner ), "sentry_setOwner() called on non-player entity type: " + owner.classname );

	self.owner = owner;

	self SetSentryOwner( self.owner );
	self SetTurretMinimapVisible( true );
	
	if ( level.teamBased )
	{
		self.team = self.owner.team;
		self setTurretTeam( self.team );
	}
	
	self thread sentry_handleOwnerDisconnect();
}


sentry_setPlaced()
{
	self setModel( level.sentrySettings[ self.sentryType ].modelBase );

	// failsafe check, for some reason this could be manual and setSentryCarried doesn't like that
	if( self GetMode() == "manual" )
		self SetMode( level.sentrySettings[ self.sentryType ].sentryModeOff );

	self setSentryCarrier( undefined );
	self setCanDamage( true );
	
	//	JDS TODO: - turret aligns to ground normal which the player will align to when they mount the turret
	//						- temp fix to keep up vertical
	switch( self.sentryType )
	{
	case "minigun_turret":
	case "gl_turret":
		self.angles = self.carriedBy.angles;
		// show the pickup message
		if( IsAlive( self.originalOwner ) )
			self.originalOwner setLowerMessage( "pickup_hint", level.sentrySettings[ self.sentryType ].ownerHintString, 3.0, undefined, undefined, undefined, undefined, undefined, true );
		// spawn a trigger so we know if the owner is within range to pick it up
		self.ownerTrigger = Spawn( "trigger_radius", self.origin + ( 0, 0, 1 ), 0, 105, 64 );
		assert( IsDefined( self.ownerTrigger ) );
		self.originalOwner thread turret_handlePickup( self );
		self thread turret_handleUse();
		break;
	default:
		break;
	}
	
	self sentry_makeSolid();

	self.carriedBy forceUseHintOff();
	self.carriedBy = undefined;

	if( IsDefined( self.owner ) )
		self.owner.isCarrying = false;

	self sentry_setActive();

	self playSound( "sentry_gun_plant" );

	self notify ( "placed" );
}


sentry_setCancelled()
{
	self.carriedBy forceUseHintOff();
	if( IsDefined( self.owner ) )
		self.owner.isCarrying = false;

	self delete();
}


sentry_setCarried( carrier )
{
	assert( isPlayer( carrier ) );
	if( IsDefined( self.originalOwner ) )
		assertEx( carrier == self.originalOwner, "sentry_setCarried() specified carrier does not own this sentry" );
	else
		assertEx( carrier == self.owner, "sentry_setCarried() specified carrier does not own this sentry" );

	self setModel( level.sentrySettings[ self.sentryType ].modelPlacement );

	self setSentryCarrier( carrier );
	self setCanDamage( false );
	self sentry_makeNotSolid();

	self.carriedBy = carrier;
	carrier.isCarrying = true;

	carrier thread updateSentryPlacement( self );
	
	self thread sentry_onCarrierDeath( carrier );
	self thread sentry_onCarrierDisconnect( carrier );
	self thread sentry_onCarrierChangedTeam( carrier );
	self thread sentry_onGameEnded();

	// setting the drop pitch here again because they could pick it up while it was stunned
	self SetDefaultDropPitch( -89.0 );

	self sentry_setInactive();
	
	self notify ( "carried" );
}

updateSentryPlacement( sentryGun )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	sentryGun endon ( "placed" );
	sentryGun endon ( "death" );
	
	sentryGun.canBePlaced = true;
	lastCanPlaceSentry = -1; // force initial update

	for( ;; )
	{
		placement = self canPlayerPlaceSentry();

		sentryGun.origin = placement[ "origin" ];
		sentryGun.angles = placement[ "angles" ];
		sentryGun.canBePlaced = self isOnGround() && placement[ "result" ] && ( abs(sentryGun.origin[2]-self.origin[2]) < 10 );
	
		if ( sentryGun.canBePlaced != lastCanPlaceSentry )
		{
			if ( sentryGun.canBePlaced )
			{
				sentryGun setModel( level.sentrySettings[ sentryGun.sentryType ].modelPlacement );
				sentryGun setSwitchToSecondObjective( 0 );
				self ForceUseHintOn( &"SENTRY_PLACE" );
			}
			else
			{
				sentryGun setModel( level.sentrySettings[ sentryGun.sentryType ].modelPlacementFailed );
				sentryGun setSwitchToSecondObjective( 1 );
				self ForceUseHintOn( &"SENTRY_CANNOT_PLACE" );
			}
		}
		
		lastCanPlaceSentry = sentryGun.canBePlaced;		
		wait ( 0.05 );
	}
}

sentry_onCarrierDeath( carrier )
{
	self endon ( "placed" );
	self endon ( "death" );

	carrier waittill ( "death" );
	
	if ( self.canBePlaced )
		self sentry_setPlaced();
	else
		self delete();
}


sentry_onCarrierDisconnect( carrier )
{
	self endon ( "placed" );
	self endon ( "death" );

	carrier waittill ( "disconnect" );
	
	self delete();
}

sentry_onCarrierChangedTeam( carrier ) // self == sentry
{
	self endon ( "placed" );
	self endon ( "death" );

	carrier waittill_any( "joined_team", "joined_spectators" );

	self delete();
}

sentry_onGameEnded( carrier )
{
	self endon ( "placed" );
	self endon ( "death" );

	level waittill ( "game_ended" );
	
	self delete();
}


sentry_setActive()
{
	self SetMode( level.sentrySettings[ self.sentryType ].sentryModeOn );
	self setCursorHint( "HINT_NOICON" );
	self setHintString( level.sentrySettings[ self.sentryType ].hintString );
	
	if( level.sentrySettings[ self.sentryType ].headIcon )
	{
		if ( level.teamBased )
			self maps\mp\_entityheadicons::setTeamHeadIcon( self.team, (0,0,65) );
		else
			self maps\mp\_entityheadicons::setPlayerHeadIcon( self.owner, (0,0,65) );
	}

	self makeUsable();

	foreach ( player in level.players )
	{
		switch( self.sentryType )
		{
		case "minigun_turret":
		case "gl_turret":
			self enablePlayerUse( player );
			break;
		default:
			if( player == self.owner )
				self enablePlayerUse( player );
			else
				self disablePlayerUse( player );
			break;
		}
	}	

	if( self.shouldSplash )
	{
		level thread teamPlayerCardSplash( level.sentrySettings[ self.sentryType ].teamSplash, self.owner, self.owner.team );
		self.shouldSplash = false;
	}

	if( self.sentryType == "sam_turret" )
	{
		self thread sam_attackTargets();
	}

	self thread sentry_watchDisabled();
}


sentry_setInactive()
{
	self setMode( level.sentrySettings[ self.sentryType ].sentryModeOff );
	self makeUnusable();

	if ( level.teamBased )
		self maps\mp\_entityheadicons::setTeamHeadIcon( "none", ( 0, 0, 0 ) );
	else if ( IsDefined( self.owner ) )
		self maps\mp\_entityheadicons::setPlayerHeadIcon( undefined, ( 0, 0, 0 ) );
}


sentry_makeSolid()
{
	self makeTurretSolid();
}


sentry_makeNotSolid()
{
	self setContents( 0 );
}


isFriendlyToSentry( sentryGun )
{
	if ( level.teamBased && self.team == sentryGun.team )
		return true;
		
	return false;
}


addToTurretList( entNum )
{
	level.turrets[entNum] = self;	
}


removeFromTurretList( entNum )
{
	level.turrets[entNum] = undefined;
}

/* ============================
	Sentry Logic Functions
   ============================ */

sentry_attackTargets()
{
	self endon( "death" );
	level endon( "game_ended" );

	self.momentum = 0;
	self.heatLevel = 0;
	self.overheated = false;
	
	self thread sentry_heatMonitor();
	
	for ( ;; )
	{
		self waittill_either( "turretstatechange", "cooled" );

		if ( self isFiringTurret() )
		{
			self thread sentry_burstFireStart();
		}
		else
		{
			self sentry_spinDown();
			self thread sentry_burstFireStop();
		}
	}
}

sentry_timeOut()
{
	self endon( "death" );
	level endon ( "game_ended" );
	
	lifeSpan = level.sentrySettings[ self.sentryType ].timeOut;
/#
	if( self.sentryType == "sam_turret" )	
		lifeSpan = GetDvarInt( "scr_sam_timeout", 90 );
#/
	
	while ( lifeSpan )
	{
		wait ( 1.0 );
		maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();
		
		if ( !IsDefined( self.carriedBy ) )
			lifeSpan = max( 0, lifeSpan - 1.0 );
	}
	
	if ( IsDefined( self.owner ) )
	{
		if	( self.sentryType == "sam_turret" )
			self.owner thread leaderDialogOnPlayer( "sam_gone" );
		else
			self.owner thread leaderDialogOnPlayer( "sentry_gone" );
	}
	self notify ( "death" );
}

sentry_targetLockSound()
{
	self endon ( "death" );
	
	self playSound( "sentry_gun_beep" );
	wait ( 0.1 );
	self playSound( "sentry_gun_beep" );
	wait ( 0.1 );
	self playSound( "sentry_gun_beep" );
}

sentry_spinUp()
{
	self thread sentry_targetLockSound();
	
	while ( self.momentum < level.sentrySettings[ self.sentryType ].spinupTime )
	{
		self.momentum += 0.1;
		
		wait ( 0.1 );
	}
}

sentry_spinDown()
{
	self.momentum = 0;
}


sentry_burstFireStart()
{
	self endon( "death" );
	self endon( "stop_shooting" );

	level endon( "game_ended" );

	self sentry_spinUp();

	fireTime = weaponFireTime( level.sentrySettings[ self.sentryType ].weaponInfo );
	minShots = level.sentrySettings[ self.sentryType ].burstMin;
	maxShots = level.sentrySettings[ self.sentryType ].burstMax;
	minPause = level.sentrySettings[ self.sentryType ].pauseMin;
	maxPause = level.sentrySettings[ self.sentryType ].pauseMax;

	for ( ;; )
	{		
		numShots = randomIntRange( minShots, maxShots + 1 );
		
		for ( i = 0; i < numShots && !self.overheated; i++ )
		{
			self shootTurret();
			self.heatLevel += fireTime;
			wait ( fireTime );
		}
		
		wait ( randomFloatRange( minPause, maxPause ) );
	}
}


sentry_burstFireStop()
{
	self notify( "stop_shooting" );
}


turret_shotMonitor( turret )
{
	self endon( "death" );
	self endon( "disconnect" );
	level endon ( "game_ended" );
	turret endon( "death" );
	turret endon( "player_dismount" );
	
	fireTime = weaponFireTime( level.sentrySettings[ turret.sentryType ].weaponInfo );
	for ( ;; )
	{	
		turret waittill ( "turret_fire" );	
		turret.heatLevel += fireTime;
		// need to reset the heat wait time so the overheat bar knows that we've fired again before cooldown
		turret.cooldownWaitTime = fireTime;
	}
}

// TODO: think about using the turret_heatMonitor and turret_coolMonitor instead of this because this has a small flaw where it waits twice and gets out of sync with the firing
sentry_heatMonitor()
{
	self endon ( "death" );

	fireTime = weaponFireTime( level.sentrySettings[ self.sentryType ].weaponInfo );

	lastHeatLevel = 0;
	lastFxTime = 0;
	
	overheatTime = level.sentrySettings[ self.sentryType ].overheatTime;
	overheatCoolDown = level.sentrySettings[ self.sentryType ].cooldownTime;

	for ( ;; )
	{
		if ( self.heatLevel != lastHeatLevel )
			wait ( fireTime );
		else
			self.heatLevel = max( 0, self.heatLevel - 0.066 );

		if ( self.heatLevel > overheatTime )
		{
			self.overheated = true;
			self thread PlayHeatFX();
			switch( self.sentryType )
			{
			case "minigun_turret":
				playFxOnTag( getFx( "sentry_smoke_mp" ), self, "tag_aim" );
				//self thread PlaySmokeFX();
				break;
			default:
				break;
			}
			
			while ( self.heatLevel )
			{
				self.heatLevel = max( 0, self.heatLevel - overheatCoolDown );	
				wait ( 0.1 );
			}

			self.overheated = false;
			self notify( "not_overheated" );
		}

		lastHeatLevel = self.heatLevel;
		wait ( 0.05 );
	}
}

turret_heatMonitor()
{
	self endon ( "death" );

	overheatTime = level.sentrySettings[ self.sentryType ].overheatTime;

	while( true )
	{
		if ( self.heatLevel > overheatTime )
		{
			self.overheated = true;
			self thread PlayHeatFX();
			switch( self.sentryType )
			{
			case "gl_turret":
				playFxOnTag( getFx( "sentry_smoke_mp" ), self, "tag_aim" );
				// TODO: get sound for overheating
				break;
			default:
				break;
			}

			while ( self.heatLevel )
			{
				wait ( 0.1 );
			}

			self.overheated = false;
			self notify( "not_overheated" );
		}

		wait ( 0.05 );
	}
}

turret_coolMonitor()
{
	self endon ( "death" );
	
	while( true )
	{
		if( self.heatLevel > 0 )
		{
			if( self.cooldownWaitTime <= 0 )
			{
				self.heatLevel = max( 0, self.heatLevel - 0.066 );
			}
			else
			{
				self.cooldownWaitTime = max( 0, self.cooldownWaitTime - 0.066 );
			}
		}

		wait( 0.05 );
	}
}


playHeatFX()
{
	self endon( "death" );
	self endon( "not_overheated" );
	level endon ( "game_ended" );
	
	self notify( "playing_heat_fx" );
	self endon( "playing_heat_fx" );
	
	for( ;; )
	{
		playFxOnTag( getFx( "sentry_overheat_mp" ), self, "tag_flash" );
	
		wait( level.sentrySettings[ self.sentryType ].fxTime );
	}
}

playSmokeFX()
{
	self endon( "death" );
	self endon( "not_overheated" );
	level endon ( "game_ended" );
	
	for( ;; )
	{
		playFxOnTag( getFx( "sentry_smoke_mp" ), self, "tag_aim" );
		wait ( 0.4 );
	}
}

sentry_beepSounds()
{
	self endon( "death" );
	level endon ( "game_ended" );

	for ( ;; )
	{
		wait ( 3.0 );

		if ( !IsDefined( self.carriedBy ) )
			self playSound( "sentry_gun_beep" );
	}
}

/* ============================
SAM Logic Functions
============================ */

sam_attackTargets() // self == sam
{
	self endon( "carried" );
	self endon( "death" );
	level endon( "game_ended" );

	self.samTargetEnt = undefined;
	self.samMissileGroups = [];

	while( true )
	{
		self.samTargetEnt = sam_acquireTarget();
		self sam_fireOnTarget();
		wait( 0.05 );
	}
}

sam_acquireTarget() // self == sam turret
{
	eyeLine = self GetTagOrigin( "tag_laser" );
	if( !IsDefined( self.samTargetEnt ) )
	{
		// scan the air for targets
		if( level.teambased )
		{
			// uavs and cuavs
			foreach( uav in level.UAVModels[ level.otherTeam[ self.team ] ] )
			{
				if( IsDefined( uav.isLeaving ) && uav.isLeaving )
					continue;

				if( SightTracePassed( eyeLine, uav.origin, false, self ) )
				{
					return uav;
				}
			}

			// littlebirds
			foreach( lb in level.littleBirds )
			{
				if( IsDefined( lb.team ) && lb.team == self.team )
					continue;

				if( SightTracePassed( eyeLine, lb.origin, false, self ) )
				{
					return lb;
				}
			}

			// helicopters
			foreach( heli in level.helis )
			{
				if( IsDefined( heli.team ) && heli.team == self.team )
					continue;

				if( SightTracePassed( eyeLine, heli.origin, false, self ) )
				{
					return heli;
				}
			}

			// ac130
			if( level.ac130InUse && IsDefined( level.ac130.owner ) && level.ac130.owner.team != self.team )
			{
				if( SightTracePassed( eyeLine, level.ac130.planemodel.origin, false, self ) )
				{
					return level.ac130.planemodel;
				}
			}
			
			//remote uav
			foreach( uav in level.remote_uav )
			{
				if( !IsDefined( uav ) )
					continue;
			
				if( IsDefined( uav.team ) && uav.team == self.team )
					continue;

				if( SightTracePassed( eyeLine, uav.origin, false, self, uav ) )
				{
					return uav;
				}
			}
		}
		else
		{
			// uavs and cuavs
			foreach( uav in level.UAVModels )
			{
				if( IsDefined( uav.isLeaving ) && uav.isLeaving )
					continue;

				if( IsDefined( uav.owner ) && IsDefined( self.owner ) && uav.owner == self.owner )
					continue;

				if( SightTracePassed( eyeLine, uav.origin, false, self ) )
				{
					return uav;
				}
			}

			// littlebirds
			foreach( lb in level.littleBirds )
			{
				if( IsDefined( lb.owner ) && IsDefined( self.owner ) && lb.owner == self.owner )
					continue;

				if( SightTracePassed( eyeLine, lb.origin, false, self ) )
				{
					return lb;
				}
			}

			// helicopters
			foreach( heli in level.helis )
			{
				if( IsDefined( heli.owner ) && IsDefined( self.owner ) && heli.owner == self.owner )
					continue;

				if( SightTracePassed( eyeLine, heli.origin, false, self ) )
				{
					return heli;
				}
			}

			// ac130
			if( level.ac130InUse && IsDefined( level.ac130.owner ) && IsDefined( self.owner ) && level.ac130.owner != self.owner )
			{
				if( SightTracePassed( eyeLine, level.ac130.planemodel.origin, false, self ) )
				{
					return level.ac130.planemodel;
				}
			}
			
			//remote uav
			foreach( uav in level.remote_uav )
			{
				if( !IsDefined( uav ) )
					continue;
			
				if( IsDefined( uav.owner ) && IsDefined( self.owner ) && uav.owner == self.owner )
					continue;
				
				if( SightTracePassed( eyeLine, uav.origin, false, self, uav ) )
				{
					return uav;
				}
			}
			
		}

		self ClearTargetEntity();
		return undefined;
	}
	else
	{
		if( !SightTracePassed( eyeLine, self.samTargetEnt.origin, false, self ) )
		{
			self ClearTargetEntity();
			return undefined;
		}

		// since it is defined and still in sight return it
		return self.samTargetEnt;
	}
}

sam_fireOnTarget() // self == sam turret
{
	// locked on to target, turn on laser and fire
	if( IsDefined( self.samTargetEnt ) )
	{
		self SetTargetEntity( self.samTargetEnt );
		self waittill( "turret_on_target" );
		if( !IsDefined( self.samTargetEnt ) )
			return;
		
		// turn on the laser, also watch for if the target is crashing or leaving
		if( !self.laser_on )
		{
			self thread sam_watchLaser();
			self thread sam_watchCrashing();
			self thread sam_watchLeaving();
			self thread sam_watchLineOfSight();
		}

		wait( 2.0 );

		if( !IsDefined( self.samTargetEnt ) )
			return;

		rocketOffsets = [];
		rocketOffsets[ 0 ] = self GetTagOrigin( "tag_le_missile1" );
		rocketOffsets[ 1 ] = self GetTagOrigin( "tag_le_missile2" );
		rocketOffsets[ 2 ] = self GetTagOrigin( "tag_ri_missile1" );
		rocketOffsets[ 3 ] = self GetTagOrigin( "tag_ri_missile2" );

		missileGroup = self.samMissileGroups.size;
		for( i = 0; i < 4; i++ )
		{
			if( !IsDefined( self.samTargetEnt ) )
				return;

			if( IsDefined( self.carriedBy ) )
				return;

			// need to shoot the turret so it'll show up on the mini-map as it shoots, it will shoot blanks
			self ShootTurret();

			rocket = MagicBullet( "sam_projectile_mp", rocketOffsets[ i ], self.samTargetEnt.origin, self.owner );
			rocket Missile_SetTargetEnt( self.samTargetEnt );
			rocket Missile_SetFlightmodeDirect();
			rocket.samTurret = self;

			rocket.samMissileGroup = missileGroup;
			self.samMissileGroups[ missileGroup ][ i ] = rocket;
			
			level notify( "sam_missile_fired", self.owner, rocket, self.samTargetEnt );

			// get out before the wait on the last shot, that way the notify goes right after the last shot
			if( i == 3 )
				break;

			wait( 0.25 );
		}
		level notify( "sam_fired", self.owner, self.samMissileGroups[ missileGroup ], self.samTargetEnt );

		wait( 3.0 );
	}
}

sam_watchLineOfSight() // self == sam turret
{
	level endon( "game_ended" );
	self endon( "death" );

	while( IsDefined( self.samTargetEnt ) && IsDefined( self GetTurretTarget( true ) ) && self GetTurretTarget( true ) == self.samTargetEnt )
	{
		eyeLine = self GetTagOrigin( "tag_laser" );
		if( !SightTracePassed( eyeLine, self.samTargetEnt.origin, false, self, self.samTargetEnt ) )
		{
			self ClearTargetEntity();
			self.samTargetEnt = undefined;
			break;
		}

		wait( 0.05 );
	}
}

sam_watchLaser() // self == sam turret
{
	self endon( "death" );

	self LaserOn();
	self.laser_on = true;

	while( IsDefined( self.samTargetEnt ) && IsDefined( self GetTurretTarget( true ) ) && self GetTurretTarget( true ) == self.samTargetEnt )
	{
		wait( 0.05 );
	}

	self LaserOff();
	self.laser_on = false;
}

sam_watchCrashing() // self == sam turret
{
	self endon( "death" );
	self.samTargetEnt endon( "death" );

	if( !IsDefined( self.samTargetEnt.heliType ) )
		return;

	self.samTargetEnt waittill( "crashing" );
	self ClearTargetEntity();
	self.samTargetEnt = undefined;
}

sam_watchLeaving() // self == sam turret
{
	self endon( "death" );
	self.samTargetEnt endon( "death" );

	if( !IsDefined( self.samTargetEnt.model ) )
		return;

	if( self.samTargetEnt.model == "vehicle_uav_static_mp" )
	{
		self.samTargetEnt waittill( "leaving" );
		self ClearTargetEntity();
		self.samTargetEnt = undefined;
	}
}
/* ============================
END SAM Logic Functions
============================ */


