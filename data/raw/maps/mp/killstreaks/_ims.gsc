#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

/*
	I.M.S. (Intelligent Munitions System) killstreaks: the player will be able to place this in the world like a sentry gun, once deployed it'll protect a radius around it
		with a rain of explosives and it'll have more than one shot
*/

init()
{
	level.killStreakFuncs[ "ims" ] 	= ::tryUseIMS;
	
	level.imsSettings = [];
	
	level.imsSettings[ "ims" ] = spawnStruct();
	level.imsSettings[ "ims" ].weaponInfo =				"ims_projectile_mp";
	level.imsSettings[ "ims" ].modelBase =				"ims_scorpion_body";
	level.imsSettings[ "ims" ].modelPlacement =			"ims_scorpion_body_placement";
	level.imsSettings[ "ims" ].modelPlacementFailed =	"ims_scorpion_body_placement";
	level.imsSettings[ "ims" ].modelDestroyed =			"ims_scorpion_body";	
	level.imsSettings[ "ims" ].modelBombSquad =			"ims_scorpion_body";	
	level.imsSettings[ "ims" ].hintString =				&"MP_IMS_PICKUP";	
	level.imsSettings[ "ims" ].placeString =			&"MP_IMS_PLACE";	
	level.imsSettings[ "ims" ].cannotPlaceString =		&"MP_IMS_CANNOT_PLACE";	
	level.imsSettings[ "ims" ].streakName =				"ims";	
	level.imsSettings[ "ims" ].splashName =				"used_ims";	
	level.imsSettings[ "ims" ].lifeSpan =				90.0;	
	level.imsSettings[ "ims" ].gracePeriod =			0.75; // time once triggered when it'll fire	
	level.imsSettings[ "ims" ].attacks =				4;	// how many times can it attack before being done
	level.imsSettings[ "ims" ].modelExplosive1 =		"ims_scorpion_explosive1";
	level.imsSettings[ "ims" ].modelExplosive2 =		"ims_scorpion_explosive2";
	level.imsSettings[ "ims" ].modelExplosive3 =		"ims_scorpion_explosive3";
	level.imsSettings[ "ims" ].modelExplosive4 =		"ims_scorpion_explosive4";
	level.imsSettings[ "ims" ].modelLid1 =				"ims_scorpion_lid1";
	level.imsSettings[ "ims" ].modelLid2 =				"ims_scorpion_lid2";
	level.imsSettings[ "ims" ].modelLid3 =				"ims_scorpion_lid3";
	level.imsSettings[ "ims" ].modelLid4 =				"ims_scorpion_lid4";
	level.imsSettings[ "ims" ].tagExplosive1 =			"tag_explosive1";
	level.imsSettings[ "ims" ].tagExplosive2 =			"tag_explosive2";
	level.imsSettings[ "ims" ].tagExplosive3 =			"tag_explosive3";
	level.imsSettings[ "ims" ].tagExplosive4 =			"tag_explosive4";
	level.imsSettings[ "ims" ].tagLid1 =				"tag_lid1";
	level.imsSettings[ "ims" ].tagLid2 =				"tag_lid2";
	level.imsSettings[ "ims" ].tagLid3 =				"tag_lid3";
	level.imsSettings[ "ims" ].tagLid4 =				"tag_lid4";

	foreach ( imsType in level.imsSettings )
	{
		PreCacheItem( imsType.weaponInfo );
		PreCacheModel( imsType.modelBase );		
		PreCacheModel( imsType.modelPlacement );		
		PreCacheModel( imsType.modelPlacementFailed );		
		PreCacheModel( imsType.modelDestroyed );		
		PreCacheModel( imsType.modelBombSquad );		
		PreCacheModel( imsType.modelExplosive1 );		
		PreCacheModel( imsType.modelExplosive2 );		
		PreCacheModel( imsType.modelExplosive3 );		
		PreCacheModel( imsType.modelExplosive4 );		
		PreCacheModel( imsType.modelLid1 );		
		PreCacheModel( imsType.modelLid2 );		
		PreCacheModel( imsType.modelLid3 );		
		PreCacheModel( imsType.modelLid4 );		
		PreCacheString( imsType.hintString );
		PreCacheString( imsType.placeString );
		PreCacheString( imsType.cannotPlaceString );
	}
	
	PreCacheString( &"PLATFORM_HOLD_TO_USE" );

	// TODO: get fx for this
	level._effect[ "ims_explode_mp" ]		= LoadFX( "explosions/sentry_gun_explosion" );
	level._effect[ "ims_smoke_mp" ]			= LoadFX( "smoke/car_damage_blacksmoke" );
	level._effect[ "ims_sensor_trail" ]		= LoadFX( "smoke/smoke_geotrail_rpg" );
	level._effect[ "ims_sensor_explode" ]	= LoadFX( "explosions/generator_sparks_d" );
	level._effect[ "ims_antenna_light_mp" ]	= LoadFX( "lights/light_detonator_blink" );
}

/* ============================
	Killstreak Functions
   ============================ */

tryUseIMS( lifeId ) // self == player
{
	// need to get current ims list to compare later
	prevIMSList = [];
	if( IsDefined( self.imsList ) )
		prevIMSList = self.imsList;

	result = self giveIMS( "ims" );

	// result can come back as undefined if the player dies in a place where the ims can't plant, or plants it on death
	// this is different from the autosentry because it uses the same model for trying to place to when it is placed, this doesn't
	if( !IsDefined( result ) )
	{
		result = false;
		// check the current ims list against the previous, if this ims got placed return true so it'll be taken from the player's inventory
		if( IsDefined( self.imsList ) )
		{
			if( !prevIMSList.size && self.imsList.size )
				result = true;
			if( prevIMSList.size && prevIMSList[0] != self.imsList[0] )
				result = true;
		}
	}

	if( result )
	{
		self maps\mp\_matchdata::logKillstreakEvent( level.imsSettings[ "ims" ].streakName, self.origin );
		
		// take the killstreak weapon
		killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( level.imsSettings[ "ims" ].streakName );
		self TakeWeapon( killstreakWeapon );
	}
	
	// we're done carrying for sure and sometimes this might not get reset
	// this fixes a bug where you could be carrying and have it in a place where it won't plant, get killed, now you can't scroll through killstreaks
	self.isCarrying = false;

	return ( result );
}

giveIMS( imsType ) // self == player
{
	imsForPlayer = createIMSForPlayer( imsType, self );
	
	//	returning from this streak activation seems to strip this?
	//	manually removing and restoring
	self removePerks();		
	
	result = self setCarryingIMS( imsForPlayer, true );
	
	self thread restorePerks();

	return result;
}


/* ============================
	Player Functions
   ============================ */

setCarryingIMS( imsForPlayer, allowCancel )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	
	assert( isReallyAlive( self ) );
	
	imsForPlayer thread ims_setCarried( self );
	
	self _disableWeapon();

	self notifyOnPlayerCommand( "place_ims", "+attack" );
	self notifyOnPlayerCommand( "place_ims", "+attack_akimbo_accessible" ); // support accessibility control scheme
	self notifyOnPlayerCommand( "cancel_ims", "+actionslot 4" );
	
	for ( ;; )
	{
		result = waittill_any_return( "place_ims", "cancel_ims", "force_cancel_ims" );

		if ( result == "cancel_ims" || result == "force_cancel_ims" )
		{
			if ( !allowCancel && result == "cancel_ims" )
				continue;
				
			// failsafe because something takes away the killstreak weapon on occasions where you have them stacked in the gimme slot
			//	for example, if you stack uav, sam turret, emp and then use the emp, then pull out the sam turret, the list item weapon gets taken away before you plant it
			//	so to "fix" this, if the user cancels then we give the weapon back to them only if the selected killstreak is the same and the item list is zero
			//	this is done for anything you can pull out and plant (ims, sentry, sam turret, remote turret, remote tank)
			if( result == "cancel_ims" )
			{
				killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( level.imsSettings[ imsForPlayer.imsType ].streakName );
				if( IsDefined( self.killstreakIndexWeapon ) && 
					killstreakWeapon == maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( self.pers["killstreaks"][self.killstreakIndexWeapon].streakName ) &&
					!( self GetWeaponsListItems() ).size )
				{
					self _giveWeapon( killstreakWeapon, 0 );
					self _setActionSlot( 4, "weapon", killstreakWeapon );
				}
			}

			imsForPlayer ims_setCancelled();
			self _enableWeapon();
			return false;
		}

		if ( !imsForPlayer.canBePlaced )
			continue;
			
		imsForPlayer thread ims_setPlaced();		
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
	if ( isDefined( self.restoreWeapon ) )	
	{
		self _giveWeapon( self.restoreWeapon );
		self.restoreWeapon = undefined;
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

/* ============================
	IMS Functions
   ============================ */

createIMSForPlayer( imsType, owner )
{
	assertEx( isDefined( owner ), "createIMSForPlayer() called without owner specified" );

	ims = SpawnTurret( "misc_turret", owner.origin + ( 0, 0, 25 ), "sentry_minigun_mp" );

	ims.angles = owner.angles;
	ims.imsType = imsType;
	ims.owner = owner;
	
	ims SetModel( level.imsSettings[ imsType ].modelBase );

	ims MakeTurretInoperable();
	ims SetTurretModeChangeWait( true );
	ims SetMode( "sentry_offline" );
	ims MakeUnusable();
	ims SetSentryOwner( owner );

	return ims;
}

createIMS( carriedIMS )
{
	owner = carriedIMS.owner;
	imsType = carriedIMS.imsType;

	ims = Spawn( "script_model", carriedIMS.origin );
	ims SetModel( level.imsSettings[ imsType ].modelBase );
	ims.scale = 3;
	ims.health = 1000;
	ims.angles = owner.angles;
	ims.imsType = imsType;
	ims.owner = owner;
	ims.team = owner.team;
	ims.shouldSplash = false;
	ims.hidden = false;
	ims.attacks = level.imsSettings[ imsType ].attacks;

	ims.lid1 = Spawn( "script_model", ims GetTagOrigin( level.imsSettings[ imsType ].tagLid1 + "_attach" ) );
	ims.lid1 SetModel( level.imsSettings[ imsType ].modelLid1 );
	ims.lid1.tag = level.imsSettings[ imsType ].tagLid1;
	ims.lid1 LinkTo( ims );

	ims.lid2 = Spawn( "script_model", ims GetTagOrigin( level.imsSettings[ imsType ].tagLid2 + "_attach" ) );
	ims.lid2 SetModel( level.imsSettings[ imsType ].modelLid2 );
	ims.lid2.tag = level.imsSettings[ imsType ].tagLid2;
	ims.lid2 LinkTo( ims );

	ims.lid3 = Spawn( "script_model", ims GetTagOrigin( level.imsSettings[ imsType ].tagLid3 + "_attach" ) );
	ims.lid3 SetModel( level.imsSettings[ imsType ].modelLid3 );
	ims.lid3.tag = level.imsSettings[ imsType ].tagLid3;
	ims.lid3 LinkTo( ims );

	ims.lid4 = Spawn( "script_model", ims GetTagOrigin( level.imsSettings[ imsType ].tagLid4 + "_attach" ) );
	ims.lid4 SetModel( level.imsSettings[ imsType ].modelLid4 );
	ims.lid4.tag = level.imsSettings[ imsType ].tagLid4;
	ims.lid4 LinkTo( ims );

	ims.explosive1 = Spawn( "script_model", ims GetTagOrigin( level.imsSettings[ imsType ].tagExplosive1 + "_attach" ) );
	ims.explosive1 SetModel( level.imsSettings[ imsType ].modelExplosive1 );
	ims.explosive1.tag = level.imsSettings[ imsType ].tagExplosive1;
	ims.explosive1 LinkTo( ims );

	ims.explosive2 = Spawn( "script_model", ims GetTagOrigin( level.imsSettings[ imsType ].tagExplosive2 + "_attach" ) );
	ims.explosive2 SetModel( level.imsSettings[ imsType ].modelExplosive2 );
	ims.explosive2.tag = level.imsSettings[ imsType ].tagExplosive2;
	ims.explosive2 LinkTo( ims );

	ims.explosive3 = Spawn( "script_model", ims GetTagOrigin( level.imsSettings[ imsType ].tagExplosive3 + "_attach" ) );
	ims.explosive3 SetModel( level.imsSettings[ imsType ].modelExplosive3 );
	ims.explosive3.tag = level.imsSettings[ imsType ].tagExplosive3;
	ims.explosive3 LinkTo( ims );

	ims.explosive4 = Spawn( "script_model", ims GetTagOrigin( level.imsSettings[ imsType ].tagExplosive4 + "_attach" ) );
	ims.explosive4 SetModel( level.imsSettings[ imsType ].modelExplosive4 );
	ims.explosive4.tag = level.imsSettings[ imsType ].tagExplosive4;
	ims.explosive4 LinkTo( ims );

	ims ims_setInactive();
	ims thread ims_handleOwnerDisconnect();
	ims thread ims_handleDeath();
	ims thread ims_handleUse();
	ims thread ims_handleDamage();
	ims thread ims_timeOut();
	ims thread ims_createBombSquadModel();

	return ims;	
}

ims_createBombSquadModel() // self == ims
{
	bombSquadModel = spawn( "script_model", self.origin );
	bombSquadModel.angles = self.angles;
	bombSquadModel hide();

	team = level.otherTeam[ self.team ];
	bombSquadModel thread maps\mp\gametypes\_weapons::bombSquadVisibilityUpdater( team, self.owner );
	bombSquadModel setModel( level.imsSettings[ self.imsType ].modelBombSquad );
	bombSquadModel SetSwitchToObjective( 1 );
	bombSquadModel linkTo( self );
	bombSquadModel SetContents( 0 );

	self waittill ( "death" );

	bombSquadModel delete();
}

/* ============================
	IMS Handlers
   ============================ */

ims_handleDamage() // self == ims
{
	self endon( "death" );
	level endon( "game_ended" );

	self.health = 999999; // keep it from dying anywhere in code
	self.maxHealth = 300; // this is the health we'll check
	self.damageTaken = 0; // how much damage has it taken

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
			case "smoke_grenade_mp":
			case "ims_projectile_mp": // shouldn't take damage from itself or another one
				continue;
			}
		}

		if ( !IsDefined( self ) )
			return;
		if( self.hidden )
			return;

		if ( meansOfDeath == "MOD_MELEE" )
			self.damageTaken += self.maxHealth;

		if( IsExplosiveDamageMOD( meansOfDeath ) )
			damage *= 1.5;

		if ( isDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
			self.wasDamagedFromBulletPenetration = true;

		self.wasDamaged = true;

		modifiedDamage = damage;
		if ( isPlayer( attacker ) )
		{
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "ims" );

			if ( attacker _hasPerk( "specialty_armorpiercing" ) )
			{
				modifiedDamage = damage * level.armorPiercingMod;			
			}
		}

		// in case we are shooting from a remote position, like being in the osprey gunner shooting this
		if( IsDefined( attacker.owner ) && IsPlayer( attacker.owner ) )
		{
			attacker.owner maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "ims" );
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
			if ( isPlayer( attacker ) && (!isDefined(self.owner) || attacker != self.owner) )
			{
				attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 100, weapon, meansOfDeath );				
				attacker notify( "destroyed_killstreak" );
			}

			if ( isDefined( self.owner ) )
				self.owner thread leaderDialogOnPlayer( "ims_destroyed" );

			self notify ( "death" );
			return;
		}
	}
}

ims_handleDeath()
{
	entNum = self GetEntityNumber();

	self addToIMSList( entNum );

	self waittill ( "death" );

	self removeFromIMSList( entNum );

	// this handles cases of deletion
	if ( !isDefined( self ) )
		return;

	self setModel( level.imsSettings[ self.imsType ].modelDestroyed );

	self ims_setInactive();

	// TODO: get sound for this
	self playSound( "ims_destroyed" );

	if ( isDefined( self.inUseBy ) )
	{
		PlayFX( getfx( "ims_explode_mp" ), self.origin + ( 0, 0, 10 ) );
		PlayFX( getfx( "ims_smoke_mp" ), self.origin );
		//playFxOnTag( getFx( "ims_explode_mp" ), self, "tag_origin" );
		//playFxOnTag( getFx( "ims_smoke_mp" ), self, "tag_origin" );

		self.inUseBy restorePerks();
		self.inUseBy restoreWeapons();				

		self notify( "deleting" );
		wait ( 1.0 );
		//StopFXOnTag( getFx( "ims_explode_mp" ), self, "tag_origin" );
		//StopFXOnTag( getFx( "ims_smoke_mp" ), self, "tag_origin" );
	}	
	else
	{		
		PlayFX( getfx( "ims_explode_mp" ), self.origin + ( 0, 0, 10 ) );
		//playFxOnTag( getFx( "ims_explode_mp" ), self, "tag_origin" );
		wait ( 1.5 );		
		// TODO: get sound for this
		self playSound( "ims_fire" );
		for ( smokeTime = 8; smokeTime > 0; smokeTime -= 0.4 )
		{
			PlayFX( getfx( "ims_smoke_mp" ), self.origin );
			//playFxOnTag( getFx( "ims_smoke_mp" ), self, "tag_origin" );
			wait ( 0.4 );
		}
		self notify( "deleting" );
	}

	if ( isDefined( self.objIdFriendly ) )
		_objective_delete( self.objIdFriendly );

	if ( isDefined( self.objIdEnemy ) )
		_objective_delete( self.objIdEnemy );

	if( IsDefined( self.lid1 ) )
		self.lid1 delete();
	if( IsDefined( self.lid2 ) )
		self.lid2 delete();
	if( IsDefined( self.lid3 ) )
		self.lid3 delete();
	if( IsDefined( self.lid4 ) )
		self.lid4 delete();

	if( IsDefined( self.explosive1 ) )
	{
		if( IsDefined( self.explosive1.killCamEnt ) )
			self.explosive1.killCamEnt delete();
		self.explosive1 delete();
	}
	if( IsDefined( self.explosive2 ) )
	{
		if( IsDefined( self.explosive2.killCamEnt ) )
			self.explosive2.killCamEnt delete();
		self.explosive2 delete();
	}
	if( IsDefined( self.explosive3 ) )
	{
		if( IsDefined( self.explosive3.killCamEnt ) )
			self.explosive3.killCamEnt delete();
		self.explosive3 delete();
	}
	if( IsDefined( self.explosive4 ) )
	{
		if( IsDefined( self.explosive4.killCamEnt ) )
			self.explosive4.killCamEnt delete();
		self.explosive4 delete();
	}

	self delete();
}

ims_handleUse() // self == ims
{
	self endon ( "death" );
	level endon ( "game_ended" );
	
	for ( ;; )
	{
		self waittill ( "trigger", player );
		
		assert( player == self.owner );
		assert( !isDefined( self.carriedBy ) );

		if ( !isReallyAlive( player ) )
			continue;
		
		imsForPlayer = createIMSForPlayer( self.imsType, player );
		imsForPlayer.ims = self;
		self ims_setInactive();
		self ims_hideAllParts();		
		player setCarryingIMS( imsForPlayer, false );
	}
}

ims_handleOwnerDisconnect()
{
	self endon ( "death" );
	level endon ( "game_ended" );

	self notify ( "ims_handleOwner" );
	self endon ( "ims_handleOwner" );

	self.owner waittill_any( "disconnect", "joined_team", "joined_spectators" );

	self notify( "death" );
}

/* ============================
	IMS Utility Functions
   ============================ */

ims_setPlaced() // self == imsForPlayer
{
	self endon( "death" );
	level endon( "game_ended" );

	self.carriedBy forceUseHintOff();
	self.carriedBy = undefined;

	if( IsDefined( self.owner ) )
		self.owner.isCarrying = false;
	
	ims = undefined;
	if( IsDefined( self.ims ) )
	{
		ims = self.ims;
		ims endon ( "death" );
		ims.origin = self.origin;
		ims.angles = self.angles;
		ims.carriedBy = undefined;
		wait( 0.05 ); // make sure everything moves before we continue because the kill cam ents are going to be remade in the new position
		ims ims_showAllParts();
	}
	else
	{
		ims = createIMS( self );
	}
	ims SetCanDamage( true );
	self playSound( "ims_plant" );

	self notify ( "placed" );
	ims thread ims_setActive();
	
	self delete();
}

ims_setCancelled()
{
	if( IsDefined( self.carriedBy ) )
		self.carriedBy forceUseHintOff();
	
	if( IsDefined( self.owner ) )
		self.owner.isCarrying = false;

	if( IsDefined( self.lid1 ) )
		self.lid1 delete();
	if( IsDefined( self.lid2 ) )
		self.lid2 delete();
	if( IsDefined( self.lid3 ) )
		self.lid3 delete();
	if( IsDefined( self.lid4 ) )
		self.lid4 delete();

	if( IsDefined( self.explosive1 ) )
		self.explosive1 delete();
	if( IsDefined( self.explosive2 ) )
		self.explosive2 delete();
	if( IsDefined( self.explosive3 ) )
		self.explosive3 delete();
	if( IsDefined( self.explosive4 ) )
		self.explosive4 delete();

	self delete();
}

ims_setCarried( carrier ) // self == imsForPlayer
{
	assert( isPlayer( carrier ) );
	assertEx( carrier == self.owner, "ims_setCarried() specified carrier does not own this ims" );

	self SetModel( level.imsSettings[ self.imsType ].modelPlacement );

	self SetSentryCarrier( carrier );
	self SetContents( 0 );
	self SetCanDamage( false );

	self.carriedBy = carrier;
	carrier.isCarrying = true;

	carrier thread updateIMSPlacement( self );
	
	self thread ims_onCarrierDeath( carrier );
	self thread ims_onCarrierDisconnect( carrier );
	self thread ims_onGameEnded();

	//self ims_setInactive();
	
	self notify ( "carried" );

	if( IsDefined( self.ims ) )
	{
		self.ims notify( "carried" );
		self.ims.carriedBy = carrier;
	}
}

updateIMSPlacement( ims )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	ims endon ( "placed" );
	ims endon ( "death" );
	
	ims.canBePlaced = true;
	lastCanPlaceIMS = -1; // force initial update

	for( ;; )
	{
		placement = self canPlayerPlaceSentry();

		ims.origin = placement[ "origin" ];
		ims.angles = placement[ "angles" ];
		ims.canBePlaced = self isOnGround() && placement[ "result" ] && ( abs(ims.origin[2]-self.origin[2]) < 10 );
	
		if ( ims.canBePlaced != lastCanPlaceIMS )
		{
			if ( ims.canBePlaced )
			{
				ims setModel( level.imsSettings[ ims.imsType ].modelPlacement );
				ims setSwitchToSecondObjective( 0 );
				self ForceUseHintOn( level.imsSettings[ ims.imsType ].placeString );
			}
			else
			{
				ims setModel( level.imsSettings[ ims.imsType ].modelPlacementFailed );
				ims setSwitchToSecondObjective( 1 );
				self ForceUseHintOn( level.imsSettings[ ims.imsType ].cannotPlaceString );
			}
		}
		
		lastCanPlaceIMS = ims.canBePlaced;		
		wait ( 0.05 );
	}
}

ims_onCarrierDeath( carrier ) // self == imsForPlayer
{
	self endon ( "placed" );
	self endon ( "death" );

	carrier waittill ( "death" );
	
	if ( self.canBePlaced )
		self thread ims_setPlaced();
	else
		self ims_setCancelled();
}


ims_onCarrierDisconnect( carrier ) // self == imsForPlayer
{
	self endon ( "placed" );
	self endon ( "death" );

	carrier waittill ( "disconnect" );
	
	self ims_setCancelled();
}

ims_onGameEnded( carrier ) // self == imsForPlayer
{
	self endon ( "placed" );
	self endon ( "death" );

	level waittill ( "game_ended" );
	
	self ims_setCancelled();
}


ims_setActive() // self == ims
{
	self setCursorHint( "HINT_NOICON" );
	self setHintString( level.imsSettings[ self.imsType ].hintString );

	owner = self.owner;
	owner ForceUseHintOff();

	if ( level.teamBased )
		self maps\mp\_entityheadicons::setTeamHeadIcon( self.team, (0,0,45) );
	else
		self maps\mp\_entityheadicons::setPlayerHeadIcon( owner, (0,0,45) );

	self MakeUsable();
	self SetCanDamage( true );

	// destroy any other ims and put this one in the list
	if( IsDefined( owner.imsList ) )
	{
		foreach( ims in owner.imsList )
		{
			// make sure we aren't just picking up and placing the same one again
			if( ims == self )
				continue;

			ims notify( "death" );
		}
	}
	owner.imsList = [];
	owner.imsList[0] = self;

	foreach ( player in level.players )
	{
		if( player == owner )
			self enablePlayerUse( player );
		else
			self disablePlayerUse( player );
	}	

	if( self.shouldSplash )
	{
		level thread teamPlayerCardSplash( level.imsSettings[ self.imsType ].splashName, owner );
		self.shouldSplash = false;
	}

	// make sure we don't go too high if there's something above it
	// need to shoot bullet traces from each pod and pick the lowest, this way it'll minimize instances where the sensor won't shoot because it's under a hole in the ceiling
	positionOffset = ( 0, 0, 20 );
	traceOffset = ( 0, 0, 256 );
	results = [];
	tagOrigin = self GetTagOrigin( level.imsSettings[ self.imsType ].tagExplosive1 ) + positionOffset;
	results[0] = BulletTrace( tagOrigin, tagOrigin + ( traceOffset - positionOffset ), false, self );
	tagOrigin = self GetTagOrigin( level.imsSettings[ self.imsType ].tagExplosive2 ) + positionOffset;
	results[1] = BulletTrace( tagOrigin, tagOrigin + ( traceOffset - positionOffset ), false, self );
	tagOrigin = self GetTagOrigin( level.imsSettings[ self.imsType ].tagExplosive3 ) + positionOffset;
	results[2] = BulletTrace( tagOrigin, tagOrigin + ( traceOffset - positionOffset ), false, self );
	tagOrigin = self GetTagOrigin( level.imsSettings[ self.imsType ].tagExplosive4 ) + positionOffset;
	results[3] = BulletTrace( tagOrigin, tagOrigin + ( traceOffset - positionOffset ), false, self );
	
	lowestZ = results[0];
	for( i = 0; i < results.size; i++ )
	{
		if( results[i][ "position" ][2] < lowestZ[ "position" ][2] )
			lowestZ = results[i];
	}

	// minus some units on the z so this will work in cramped places like in a train
	self.attackHeightPos = lowestZ[ "position" ] - ( 0, 0, 20 );
	// trigger height should be around 100 so you don't trigger it from the second floor
	attackTrigger = Spawn( "trigger_radius", self.origin, 0, 256, 100 );
	self.attackTrigger = attackTrigger;
	// move at 200 units per second
	self.attackMoveTime = Distance( self.origin, self.attackHeightPos ) / 200;

	self.killCamOffset = ( 0, 0, 12 );
	// since you can pick this up and place again, delete the kill cam ents and remake them
	if( IsDefined( self.explosive1.killCamEnt ) )
		self.explosive1.killCamEnt delete();
	if( IsDefined( self.explosive2.killCamEnt ) )
		self.explosive2.killCamEnt delete();
	if( IsDefined( self.explosive3.killCamEnt ) )
		self.explosive3.killCamEnt delete();
	if( IsDefined( self.explosive4.killCamEnt ) )
		self.explosive4.killCamEnt delete();
	
	owner.imsKillCamEnt = undefined;
	if( IsDefined( self.explosive1 ) )
	{
		self.explosive1.killCamEnt = Spawn( "script_model", self.explosive1.origin + self.killCamOffset );
		if( !IsDefined( owner.imsKillCamEnt ) )
			owner.imsKillCamEnt = self.explosive1.killCamEnt;
	}
	if( IsDefined( self.explosive2 ) )
	{
		self.explosive2.killCamEnt = Spawn( "script_model", self.explosive2.origin + self.killCamOffset );
		if( !IsDefined( owner.imsKillCamEnt ) )
			owner.imsKillCamEnt = self.explosive2.killCamEnt;
	}
	if( IsDefined( self.explosive3 ) )
	{
		self.explosive3.killCamEnt = Spawn( "script_model", self.explosive3.origin + self.killCamOffset );
		if( !IsDefined( owner.imsKillCamEnt ) )
			owner.imsKillCamEnt = self.explosive3.killCamEnt;
	}
	if( IsDefined( self.explosive4 ) )
	{
		self.explosive4.killCamEnt = Spawn( "script_model", self.explosive4.origin + self.killCamOffset );
		if( !IsDefined( owner.imsKillCamEnt ) )
			owner.imsKillCamEnt = self.explosive4.killCamEnt;
	}

	self thread ims_blinky_light();

	self thread ims_attackTargets();
	self thread ims_playerConnected();
	
	foreach( player in level.players )
		self thread ims_playerJoinedTeam( player );
}

ims_playerConnected() // self == ims
{
	self endon( "death" );

	// when new players connect they need to not be able to use the planted ims
	level waittill( "connected", player );
	player waittill( "spawned_player" );

	// this can't possibly be the owner because the ims is destroyed if the owner leaves the game, so disable use for this player
	self DisablePlayerUse( player );
}

ims_playerJoinedTeam( player ) // self == ims
{
	self endon( "death" );
	player endon( "disconnect" );

	// when new players connect they need to not be able to use the planted ims
	while( true )
	{
		player waittill( "joined_team" );
		
		// this can't possibly be the owner because the ims is destroyed if the owner leaves the game, so disable use for this player
		self DisablePlayerUse( player );
	}
}

ims_blinky_light() // self == ims
{
	self endon( "death" );
	self endon( "carried" );

	while ( true )
	{
		//PlayLoopedFX( getfx( "ims_antenna_light_mp" ), 1.0, self GetTagOrigin( "tag_fx" ) );
		PlayFXOnTag( getfx( "ims_antenna_light_mp" ), self, "tag_fx" );
		wait( 1.0 );
		StopFXOnTag( getfx( "ims_antenna_light_mp" ), self, "tag_fx" );
	}
}

ims_setInactive()
{
	self MakeUnusable();

	if ( level.teamBased )
		self maps\mp\_entityheadicons::setTeamHeadIcon( "none", ( 0, 0, 0 ) );
	else if ( isDefined( self.owner ) )
		self maps\mp\_entityheadicons::setPlayerHeadIcon( undefined, ( 0, 0, 0 ) );

	if( IsDefined( self.attackTrigger ) )
		self.attackTrigger delete();
}

isFriendlyToIMS( ims )
{
	if ( level.teamBased && self.team == ims.team )
		return true;
		
	return false;
}

/* ============================
	IMS Logic Functions
   ============================ */

ims_attackTargets() // self == ims
{
	level endon( "game_ended" );

	// watch the radius, if something enters, shot sensor up and drop bombs down
	while( true )
	{
		// checking for the attackTrigger will tell us if this has been set to inactive and is dying
		if( !IsDefined( self.attackTrigger ) )
			break;

		self.attackTrigger waittill( "trigger", targetEnt );

		if( IsPlayer( targetEnt ) )
		{
			// don't attack the owner
			if( IsDefined( self.owner ) && targetEnt == self.owner )
				continue;

			if( level.teambased && targetEnt.pers["team"] == self.team )
				continue;

			if( !isReallyAlive( targetEnt ) )
				continue;
		}
		else // things like the remote tank can trip this
		{
			if( IsDefined( targetEnt.owner ) )
			{
				// don't attack the owner
				if( IsDefined( self.owner ) && targetEnt.owner == self.owner )
					continue;

				if( level.teambased && targetEnt.owner.pers["team"] == self.team )
					continue;
			}
		}

		// make sure the sensor that shoots up in the air can see the target and the pods can see the target (using the lid tags on each pod)
		// this fixes an issue where the ims will kill someone who is on the other side of tall cover
		if( !SightTracePassed( self.attackHeightPos, targetEnt.origin + ( 0, 0, 50 ), false, self ) ||
			( !SightTracePassed( self GetTagOrigin( level.imsSettings[ self.imsType ].tagLid1 ) + ( 0, 0, 5 ), targetEnt.origin + ( 0, 0, 50 ), false, self ) &&
			 !SightTracePassed( self GetTagOrigin( level.imsSettings[ self.imsType ].tagLid2 ) + ( 0, 0, 5 ), targetEnt.origin + ( 0, 0, 50 ), false, self ) &&
			 !SightTracePassed( self GetTagOrigin( level.imsSettings[ self.imsType ].tagLid3 ) + ( 0, 0, 5 ), targetEnt.origin + ( 0, 0, 50 ), false, self ) &&
			 !SightTracePassed( self GetTagOrigin( level.imsSettings[ self.imsType ].tagLid4 ) + ( 0, 0, 5 ), targetEnt.origin + ( 0, 0, 50 ), false, self ) ) )
			continue;

		self playsound( "ims_trigger" );

		if( IsPlayer( targetEnt ) && targetEnt _hasPerk( "specialty_delaymine" ) )
		{
			targetEnt notify( "triggered_ims" );
			wait( level.delayMineTime );
			
			// checking for the attackTrigger will tell us if this has been set to inactive and is dying
			if( !IsDefined( self.attackTrigger ) )
				break;
		}
		else 
			wait( level.imsSettings[ self.imsType ].gracePeriod );

		// shoot sensor up
		if( IsDefined( self.explosive1 ) )
		{
			fire_sensor( targetEnt, self.explosive1, self.lid1 );
		}
		else if( IsDefined( self.explosive2 ) )
		{
			fire_sensor( targetEnt, self.explosive2, self.lid2 );
		}
		else if( IsDefined( self.explosive3 ) )
		{
			fire_sensor( targetEnt, self.explosive3, self.lid3 );
		}
		else if( IsDefined( self.explosive4 ) )
		{
			fire_sensor( targetEnt, self.explosive4, self.lid4 );
		}

		self.attacks--;
		if( self.attacks <= 0 )
			break;

		wait( 2.0 );
	
		if( !IsDefined( self.owner ) )
			break;
	}

	// if the owner is carrying it, don't send death notify
	if( IsDefined( self.carriedBy ) && IsDefined( self.owner ) && self.carriedBy == self.owner )
		return;

	self notify( "death" );
}

fire_sensor( targetEnt, sensorEnt, lidEnt ) // self == ims
{
	// lid blows off
	// TODO: get fx for this
	PlayFX( level._effect[ "ims_sensor_explode" ], lidEnt.origin );
	lidEnt Hide();

	sensorEnt Unlink();
	sensorEnt RotateYaw( 3600, self.attackMoveTime );
	sensorEnt MoveTo( self.attackHeightPos, self.attackMoveTime, self.attackMoveTime * 0.25, self.attackMoveTime * 0.25 );
	
	if( IsDefined( sensorEnt.killCamEnt ) )
	{
		// set the owner's kill cam ent here to make sure we always get the right kill cam for the latest sensor fired
		// this fixes a bug where you could place one ims, let it kill, then place a second, let it kill, and the kill cam would be wrong because we deleted the kill cam ent when the first one died
		if( IsDefined( self.owner ) )
			self.owner.imsKillCamEnt = sensorEnt.killCamEnt;
		
		sensorEnt.killCamEnt MoveTo( self.attackHeightPos + self.killCamOffset, self.attackMoveTime, self.attackMoveTime * 0.25, self.attackMoveTime * 0.25 );
		sensorEnt.killCamEnt thread deleteAfterTime( 5.0 );
	}
	
	sensorEnt playsound( "ims_launch" );
	// TODO: get fx for flying up
	//PlayFX( level._effect[ "ims_sensor_trail" ], sensorEnt.origin );
	sensorEnt waittill( "movedone" );
	// TODO: get fx for blowing up in the air
	//StopFXOnTag( level._effect[ "ims_sensor_trail" ], sensorEnt, sensorEnt.tag );
	PlayFX( level._effect[ "ims_sensor_explode" ], sensorEnt.origin );

	// drop bombs down
	dropBombs = [];
	//scalar = 150;
	//
	//angles = self.angles;
	//angForwardScaled = AnglesToForward( angles ) * scalar;
	//dropBombs[0] = self.origin + angForwardScaled;
	//
	//angles = ( self.angles[0], self.angles[1] + 90, self.angles[2] );
	//angForwardScaled = AnglesToForward( angles ) * scalar;
	//dropBombs[1] = self.origin + angForwardScaled;

	//angles = ( self.angles[0], self.angles[1] + 180, self.angles[2] );
	//angForwardScaled = AnglesToForward( angles ) * scalar;
	//dropBombs[2] = self.origin + angForwardScaled;

	//angles = ( self.angles[0], self.angles[1] + 270, self.angles[2] );
	//angForwardScaled = AnglesToForward( angles ) * scalar;
	//dropBombs[3] = self.origin + angForwardScaled;

	dropBombs[0] = targetEnt.origin;
	for( i = 0; i < dropBombs.size; i++ )
	{
		//level thread draw_line_for_time( self.origin, dropBombs[i], 1, 0, 0, 10 );
		if( IsDefined( self.owner ) )
			MagicBullet( "ims_projectile_mp", sensorEnt.origin, dropBombs[i], self.owner );
		else
			MagicBullet( "ims_projectile_mp", sensorEnt.origin, dropBombs[i] );
	}

	lidEnt delete();
	sensorEnt delete();
}

deleteAfterTime( time )
{
	self endon( "death" );

	level maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( time );

	if( IsDefined( self ) )
		self delete();
}

ims_timeOut()
{
	self endon( "death" );
	level endon ( "game_ended" );
	
	lifeSpan = level.imsSettings[ self.imsType ].lifeSpan;
	
	while ( lifeSpan )
	{
		wait ( 1.0 );
		maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();
		
		if ( !isDefined( self.carriedBy ) )
			lifeSpan = max( 0, lifeSpan - 1.0 );
	}
	
	// TODO: get sound for this
	//if ( isDefined( self.owner ) )
	//	self.owner thread leaderDialogOnPlayer( "ims_gone" );
	
	self notify ( "death" );
}

addToIMSList( entNum )
{
	level.ims[entNum] = self;	
}

removeFromIMSList( entNum )
{
	level.ims[entNum] = undefined;
}

ims_hideAllParts() // self == ims
{
	if( IsDefined( self.lid1 ) )
		self.lid1 Hide();
	if( IsDefined( self.lid2 ) )
		self.lid2 Hide();
	if( IsDefined( self.lid3 ) )
		self.lid3 Hide();
	if( IsDefined( self.lid4 ) )
		self.lid4 Hide();

	if( IsDefined( self.explosive1 ) )
		self.explosive1 Hide();
	if( IsDefined( self.explosive2 ) )
		self.explosive2 Hide();
	if( IsDefined( self.explosive3 ) )
		self.explosive3 Hide();
	if( IsDefined( self.explosive4 ) )
		self.explosive4 Hide();

	self Hide();
	self.hidden = true;
}

ims_showAllParts() // self == ims
{
	if( IsDefined( self.lid1 ) )
		self.lid1 Show();
	if( IsDefined( self.lid2 ) )
		self.lid2 Show();
	if( IsDefined( self.lid3 ) )
		self.lid3 Show();
	if( IsDefined( self.lid4 ) )
		self.lid4 Show();

	if( IsDefined( self.explosive1 ) )
		self.explosive1 Show();
	if( IsDefined( self.explosive2 ) )
		self.explosive2 Show();
	if( IsDefined( self.explosive3 ) )
		self.explosive3 Show();
	if( IsDefined( self.explosive4 ) )
		self.explosive4 Show();

	self Show();
	self.hidden = false;
}
