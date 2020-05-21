#include maps\mp\_utility;
#include common_scripts\utility;
#include maps\mp\gametypes\_hud_util;

/*
	Deployable box killstreaks: the player will be able to place a box in the world and teammates can grab items from it
		this will be used on multiple killstreaks where you can place a box in the world with something in it
*/

HEADICON_OFFSET = ( 0, 0, 20 );

init()
{
	level.killStreakFuncs[ "deployable_vest" ] 	= ::tryUseDeployableVest;

	level.boxSettings = [];

	level.boxSettings[ "deployable_vest" ] = spawnStruct();
	level.boxSettings[ "deployable_vest" ].weaponInfo =				"deployable_vest_marker_mp";
	level.boxSettings[ "deployable_vest" ].modelBase =				"com_deploy_ballistic_vest_friend_world";
	level.boxSettings[ "deployable_vest" ].hintString =				&"MP_LIGHT_ARMOR_PICKUP";	
	level.boxSettings[ "deployable_vest" ].capturingString =		&"MP_BOX_GETTING_VEST";	
	level.boxSettings[ "deployable_vest" ].eventString =			&"MP_DEPLOYED_VEST";	
	level.boxSettings[ "deployable_vest" ].streakName =				"deployable_vest";	
	level.boxSettings[ "deployable_vest" ].splashName =				"used_deployable_vest";	
	level.boxSettings[ "deployable_vest" ].shaderName =				"compass_objpoint_deploy_friendly";	
	level.boxSettings[ "deployable_vest" ].lifeSpan =				60.0;	
	level.boxSettings[ "deployable_vest" ].xp =						50;	
	level.boxSettings[ "deployable_vest" ].voDestroyed =			"ballistic_vest_destroyed";	

	foreach ( box in level.boxSettings )
	{
		PreCacheItem( box.weaponInfo );		
		PreCacheModel( box.modelBase );		
		PreCacheString( box.hintString );
		PreCacheString( box.capturingString );
		PreCacheString( box.eventString );
		PreCacheShader( box.shaderName );
	}

	PreCacheString( &"PLATFORM_HOLD_TO_USE" );

	level._effect[ "box_explode_mp" ]	= loadfx( "fire/ballistic_vest_death" );
}

tryUseDeployableVest( lifeId ) // self == player
{
	result = self beginDeployableViaMarker( lifeId, "deployable_vest" );

	if( ( !IsDefined( result ) || !result ) )
	{
		return false;
	}

	self maps\mp\_matchdata::logKillstreakEvent( "deployable_vest", self.origin );

	return true;
}

///////////////////////////////////////////////////
// MARKER FUNCTIONS
//////////////////////////////////////////////////

beginDeployableViaMarker( lifeId, boxType )
{
	self endon ( "death" );
	self.marker = undefined;

	self thread watchMarkerUsage( lifeId, boxType );

	while( self isChangingWeapon() )
		wait ( 0.05 );	

	currentWeapon = self getCurrentWeapon();

	if ( isMarker( currentWeapon ) )
		markerWeapon = currentWeapon;
	else
		markerWeapon = undefined;

	while( isMarker( currentWeapon ) )
	{
		self waittill( "weapon_change", currentWeapon );

		if ( isMarker( currentWeapon ) )
			markerWeapon = currentWeapon;
	}

	self notify ( "stopWatchingMarker" );

	if ( !isDefined( markerWeapon ) )
		return false;

	return( !( self getAmmoCount( markerWeapon ) && self hasWeapon( markerWeapon ) ) );
}

watchMarkerUsage( lifeId, boxType ) // self == player
{
	self notify( "watchMarkerUsage" );

	self endon( "death" );
	self endon( "disconnect" );
	self endon( "watchMarkerUsage" );
	self endon( "stopWatchingMarker" );

	self thread watchMarker( lifeId, boxType );

	while( true )
	{
		self waittill( "grenade_pullback", weaponName );

		if ( !isMarker( weaponName ) )
			continue;

		self _disableUsability();

		self beginMarkerTracking();
	}
}

watchMarker( lifeId, boxType ) // self == player
{
	self notify( "watchMarker" );

	self endon( "watchMarker" );
	self endon( "spawned_player" );
	self endon( "disconnect" );
	self endon( "stopWatchingMarker" );

	while( true )
	{
		self waittill( "grenade_fire", marker, weapName );

		if ( !isMarker( weapName ) )
			continue;
		if( !IsAlive( self ) )
		{
			marker delete();
			return;
		}

		marker.owner = self;
		marker.weaponName = weapName;

		self.marker = marker;

		self thread takeWeaponOnStuck( marker, weapName );

		marker thread markerActivate( lifeId, boxType, ::box_setActive );		
	}
}

takeWeaponOnStuck( weap, weapName )
{
	self endon( "death" );
	self endon( "disconnect" );
	level endon( "game_ended" );

	weap waittill_any_timeout( 5, "missile_stuck" );
	
	weap playSound( "mp_vest_deployed_ui" );
	
	// take the weapon away now because they've used it
	// this let's us not do a endon("grenade_fire") in beginStrikeViaMarker so it can finish correctly
	if( self HasWeapon( weapName ) )
	{
		self TakeWeapon( weapName );
		self SwitchToWeapon( self getLastWeapon() );
	}
}

beginMarkerTracking() // self == player
{
	self notify( "beginMarkerTracking" );
	self endon( "beginMarkerTracking" );
	self endon( "death" );
	self endon( "disconnect" );

	self waittill_any( "grenade_fire", "weapon_change" );
	self _enableUsability();
}

markerActivate( lifeId, boxType, usedCallback ) // self == marker
{	
	self notify( "markerActivate" );
	self endon( "markerActivate" );
	//self waittill( "explode", position );
	self waittill( "missile_stuck" );
	owner = self.owner;
	position = self.origin;

	if ( !isDefined( owner ) )
		return;

	box = createBoxForPlayer( boxType, position, owner );
	wait 0.05;

	//self playSound( "sentry_gun_beep" );
	box thread [[ usedCallback ]]();

	self delete();
}

isMarker( weaponName )
{
	switch ( weaponName )
	{
	case "deployable_vest_marker_mp":
		return true;
	default:
		return false;
	}
}

///////////////////////////////////////////////////
// END MARKER FUNCTIONS
//////////////////////////////////////////////////

///////////////////////////////////////////////////
// BOX HANDLER FUNCTIONS
//////////////////////////////////////////////////

createBoxForPlayer( boxType, position, owner )
{
	assertEx( isDefined( owner ), "createBoxForPlayer() called without owner specified" );

	box = Spawn( "script_model", position );
	box setModel( level.boxSettings[ boxType ].modelBase );
	box.health = 1000;
	box.angles = owner.angles;
	box.boxType = boxType;
	box.owner = owner;
	box.team = owner.team;

	box box_setInactive();
	box thread box_handleOwnerDisconnect();

	return box;	
}

box_setActive() // self == box
{
	self setCursorHint( "HINT_NOICON" );
	self setHintString( level.boxSettings[ self.boxType ].hintString );

	// TODO: need a way to show an enemy model but not hinder explosive damage
	//		right now if you have two models there then the explosive damage won't count
	//self setModel( maps\mp\gametypes\_teams::getTeamDeployModel( self.team ) );

	//self.friendlyModel = Spawn( "script_model", self.origin );
	//self.friendlyModel.angles = self.angles;
	//self.friendlyModel setModel( level.boxSettings[ self.boxType ].modelFriendly );
	//self.enemyModel = spawn( "script_model", self.origin );
	//self.enemyModel.angles = self.angles;
	//self.enemyModel setModel( level.boxSettings[ self.boxType ].modelEnemy );

	//self.friendlyModel thread deleteOnOwnerDeath( self );
	//self.friendlyModel thread box_ModelTeamUpdater( self.team );

	//self thread box_ModelTeamUpdater( self.team );

	//self.enemyModel thread deleteOnOwnerDeath( self );
	//self.enemyModel thread box_ModelTeamUpdater( level.otherTeam[self.team] );

	self.inUse = false;

	//self CloneBrushmodelToScriptmodel( level.airDropCrateCollision );

	//self PhysicsLaunchServer( ( 0, 0, 0 ), ( 0, 0, 0.05 ) );		
	//self waittill( "physics_finished" );

	if ( level.teamBased )
	{
		curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
		Objective_Add( curObjID, "invisible", (0,0,0) );
		Objective_Position( curObjID, self.origin );
		Objective_State( curObjID, "active" );
		Objective_Icon( curObjID, level.boxSettings[ self.boxType ].shaderName );
		Objective_Team( curObjID, self.team );
		self.objIdFriendly = curObjID;

		//curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
		//objective_add( curObjID, "invisible", (0,0,0) );
		//objective_position( curObjID, self.origin );
		//objective_state( curObjID, "active" );
		//objective_team( curObjID, level.otherTeam[self.team] );
		//objective_icon( curObjID, "compass_objpoint_ammo_enemy" );
		//self.objIdEnemy = curObjID;

		foreach ( player in level.players )
		{
			if ( self.team == player.team && !player isJuggernaut() )
				self maps\mp\_entityheadIcons::setHeadIcon( player, maps\mp\killstreaks\_killstreaks::getKillstreakCrateIcon( level.boxSettings[ self.boxType ].streakName ), HEADICON_OFFSET, 14, 14, undefined, undefined, undefined, undefined, undefined, false );
		}
	}
	else
	{
		curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
		Objective_Add( curObjID, "invisible", (0,0,0) );
		Objective_Position( curObjID, self.origin );
		Objective_State( curObjID, "active" );
		Objective_Icon( curObjID, level.boxSettings[ self.boxType ].shaderName );
		Objective_Player( curObjID, self.owner GetEntityNumber() );
		self.objIdFriendly = curObjID;

		if( !self.owner isJuggernaut() )
			self maps\mp\_entityheadIcons::setHeadIcon( self.owner, maps\mp\killstreaks\_killstreaks::getKillstreakCrateIcon( level.boxSettings[ self.boxType ].streakName ), HEADICON_OFFSET, 14, 14, undefined, undefined, undefined, undefined, undefined, false );
	}

	self MakeUsable();
	self.isUsable = true;
	self SetCanDamage( true );
	self thread box_handleDamage();
	self thread box_handleDeath();
	self thread box_timeOut();
	self thread disableWhenJuggernaut();

	foreach ( player in level.players )
	{
		if( level.teambased )
		{
			if ( self.team == player.team )
			{
				if( player isJuggernaut() )
				{
					self DisablePlayerUse( player );
					// if this player is already a juggernaut then when they die, let them use the box
					self thread doubleDip( player );
				}
				else
				{
					self EnablePlayerUse( player );
				}
				self thread boxThink( player );
			}
			else
			{
				self DisablePlayerUse( player );
			}
			self thread box_playerJoinedTeam( player );
		}
		else
		{
			if ( IsDefined( self.owner ) && self.owner == player )
			{
				if( player isJuggernaut() )
				{
					self DisablePlayerUse( player );
					// if this player is already a juggernaut then when they die, let them use the box
					self thread doubleDip( player );
				}
				else
				{
					self EnablePlayerUse( player );
				}
				self thread boxThink( player );
			}
			else
			{
				self DisablePlayerUse( player );
			}
		}
	}

	level thread teamPlayerCardSplash( level.boxSettings[ self.boxType ].splashName, self.owner, self.team );

	self thread box_playerConnected();
}

box_playerConnected() // self == box
{
	self endon( "death" );

	// when new players connect they need a boxthink thread run on them
	level waittill( "connected", player );
	player waittill( "spawned_player" );
	if ( level.teamBased )
	{
		if ( self.team == player.team )
		{
			self EnablePlayerUse( player );
			self thread boxThink( player );
			self maps\mp\_entityheadIcons::setHeadIcon( player, maps\mp\killstreaks\_killstreaks::getKillstreakCrateIcon( level.boxSettings[ self.boxType ].streakName ), HEADICON_OFFSET, 14, 14, undefined, undefined, undefined, undefined, undefined, false );
		}
		else
		{
			self DisablePlayerUse( player );
			self maps\mp\_entityheadIcons::setHeadIcon( player, "", (0,0,0) );
		}
	}
}

box_playerJoinedTeam( player ) // self == box
{
	self endon( "death" );
	player endon( "disconnect" );

	// when new players connect they need a boxthink thread run on them
	while( true )
	{
		player waittill( "joined_team" );
		if ( level.teamBased )
		{
			if ( self.team == player.team )
			{
				self EnablePlayerUse( player );
				self thread boxThink( player );
				self maps\mp\_entityheadIcons::setHeadIcon( player, maps\mp\killstreaks\_killstreaks::getKillstreakCrateIcon( level.boxSettings[ self.boxType ].streakName ), HEADICON_OFFSET, 14, 14, undefined, undefined, undefined, undefined, undefined, false );
			}
			else
			{
				self DisablePlayerUse( player );
				self maps\mp\_entityheadIcons::setHeadIcon( player, "", (0,0,0) );
			}
		}
	}
}

box_setInactive()
{
	self makeUnusable();
	self.isUsable = false;
	self maps\mp\_entityheadIcons::setHeadIcon( "none", "", (0,0,0) );
	if ( isDefined( self.objIdFriendly ) )
		_objective_delete( self.objIdFriendly );	
}

box_handleDamage()
{
	self.health = 999999; // keep it from dying anywhere in code
	self.maxHealth = 300; // this is the health we'll check
	self.damageTaken = 0; // how much damage has it taken

	while( true )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );

		// don't allow people to destroy equipment on their team if FF is off
		if( !maps\mp\gametypes\_weapons::friendlyFireCheck( self.owner, attacker ) )
			continue;

		if( IsDefined( weapon ) )
		{
			switch( weapon )
			{
			case "concussion_grenade_mp":
			case "flash_grenade_mp":
			case "smoke_grenade_mp":
				continue;
			}
		}

		if( !IsDefined( self ) )
			return;

		if( meansOfDeath == "MOD_MELEE" )
			self.damageTaken += self.maxHealth;

		if( IsDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
			self.wasDamagedFromBulletPenetration = true;

		self.wasDamaged = true;

		modifiedDamage = damage;

		if( IsPlayer( attacker ) )
		{
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "deployable_bag" );

			if( meansOfDeath == "MOD_RIFLE_BULLET" || meansOfDeath == "MOD_PISTOL_BULLET" )
			{
				if( attacker _hasPerk( "specialty_armorpiercing" ) )
					modifiedDamage += damage * level.armorPiercingMod;
			}
		}

		// in case we are shooting from a remote position, like being in the osprey gunner shooting this
		if( IsDefined( attacker.owner ) && IsPlayer( attacker.owner ) )
		{
			attacker.owner maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "deployable_bag" );
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
				self.largeProjectileDamage = false;
				modifiedDamage = self.maxHealth + 1;
				break;
			}
		}

		self.damageTaken += modifiedDamage;

		if( self.damageTaken >= self.maxHealth )
		{
			if( IsPlayer( attacker ) && (!IsDefined(self.owner) || attacker != self.owner) )
			{
				attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 100, weapon, meansOfDeath );				
				attacker notify( "destroyed_killstreak" );
			}

			if( IsDefined( self.owner ) )
				self.owner thread leaderDialogOnPlayer( level.boxSettings[ self.boxType ].voDestroyed );

			self notify( "death" );
			return;
		}
	}
}

box_handleDeath()
{
	self waittill ( "death" );

	// this handles cases of deletion
	if ( !isDefined( self ) )
		return;

	self box_setInactive();
	
	PlayFX( getfx( "box_explode_mp" ), self.origin );
	
	wait( 0.5 );

	self notify( "deleting" );

	self delete();
}

box_handleOwnerDisconnect() // self == box
{
	self endon ( "death" );
	level endon ( "game_ended" );

	self notify ( "box_handleOwner" );
	self endon ( "box_handleOwner" );

	self.owner waittill_any( "disconnect", "joined_team", "joined_spectators" );

	self notify( "death" );
}

boxThink( player )
{	
	self endon ( "death" );

	self thread boxCaptureThink( player );

	for ( ;; )
	{
		self waittill ( "captured", capturer );

		if( capturer != player )
			continue;

		switch( self.boxType )
		{
		case "deployable_vest":
			// TODO: get sound for this
			player playLocalSound( "ammo_crate_use" );
			player [[ level.killStreakFuncs["light_armor"] ]]();
			break;
		}

		// if this is not the owner then give the owner some xp
		if( IsDefined( self.owner ) && player != self.owner )
		{
			self.owner thread maps\mp\gametypes\_rank::xpEventPopup( level.boxSettings[ self.boxType ].eventString );
			self.owner thread maps\mp\gametypes\_rank::giveRankXP( "support", level.boxSettings[ self.boxType ].xp );
		}

		self maps\mp\_entityheadIcons::setHeadIcon( player, "", (0,0,0) );
		self DisablePlayerUse( player );
		self thread doubleDip( player );
	}
}

doubleDip( player ) // self == box
{
	self endon( "death" );
	player endon( "disconnect" );

	// once they die, let them take from the box again
	player waittill( "death" );

	if( level.teamBased )
	{
		if( self.team == player.team )
		{
			self maps\mp\_entityheadIcons::setHeadIcon( player, maps\mp\killstreaks\_killstreaks::getKillstreakCrateIcon( level.boxSettings[ self.boxType ].streakName ), HEADICON_OFFSET, 14, 14, undefined, undefined, undefined, undefined, undefined, false );
			self EnablePlayerUse( player );
		}
	}
	else
	{
		if( IsDefined( self.owner ) && self.owner == player )
		{
			self maps\mp\_entityheadIcons::setHeadIcon( player, maps\mp\killstreaks\_killstreaks::getKillstreakCrateIcon( level.boxSettings[ self.boxType ].streakName ), HEADICON_OFFSET, 14, 14, undefined, undefined, undefined, undefined, undefined, false );
			self EnablePlayerUse( player );
		}
	}
}

boxCaptureThink( player )
{
	while( isDefined( self ) )
	{
		self waittill( "trigger", tiggerer );

		if( tiggerer != player )
			continue;

		if ( !self useHoldThink( player, 2000 ) )
			continue;

		self notify( "captured", player );
	}
}

isFriendlyToBox( box )
{
	if ( level.teamBased && self.team == box.team )
		return true;

	return false;
}

box_timeOut() // self == box
{
	self endon( "death" );
	level endon ( "game_ended" );

	lifeSpan = level.boxSettings[ self.boxType ].lifeSpan;

	while ( lifeSpan )
	{
		wait ( 1.0 );
		maps\mp\gametypes\_hostmigration::waitTillHostMigrationDone();

		if ( !isDefined( self.carriedBy ) )
			lifeSpan = max( 0, lifeSpan - 1.0 );
	}

	// TODO: get sound for this
	//if ( isDefined( self.owner ) )
	//	self.owner thread leaderDialogOnPlayer( "sentry_gone" );

	self notify ( "death" );
}

deleteOnOwnerDeath( owner ) // self == box.friendlyModel or box.enemyModel, owner == box
{
	wait ( 0.25 );
	self linkTo( owner, "tag_origin", (0,0,0), (0,0,0) );

	owner waittill ( "death" );

	self delete();
}

box_ModelTeamUpdater( showForTeam ) // self == box model (enemy or friendly)
{
	self endon ( "death" );

	self hide();

	foreach ( player in level.players )
	{
		if ( player.team == showForTeam )
			self showToPlayer( player );
	}

	for ( ;; )
	{
		level waittill ( "joined_team" );

		self hide();
		foreach ( player in level.players )
		{
			if ( player.team == showForTeam )
				self showToPlayer( player );
		}
	}	
}

useHoldThink( player, useTime ) 
{
	player playerLinkTo( self );
	player playerLinkedOffsetEnable();

	player _disableWeapon();

	player.boxParams = SpawnStruct();
	player.boxParams.curProgress = 0;
	player.boxParams.inUse = true;
	player.boxParams.useRate = 0;

	if ( isDefined( useTime ) )
		player.boxParams.useTime = useTime;
	else
		player.boxParams.useTime = 3000;

	player thread personalUseBar( self );

	result = useHoldThinkLoop( player );
	assert ( isDefined( result ) );

	if ( isAlive( player ) )
	{
		player _enableWeapon();
		player unlink();
	}

	if ( !isDefined( self ) )
		return false;

	player.boxParams.inUse = false;
	player.boxParams.curProgress = 0;

	return ( result );
}

personalUseBar( object ) // self == player
{
	self endon( "disconnect" );

	useBar = createPrimaryProgressBar( 0, 25 );
	useBarText = createPrimaryProgressBarText( 0, 25 );
	useBarText setText( level.boxSettings[ object.boxType ].capturingString );

	lastRate = -1;
	while ( isReallyAlive( self ) && isDefined( object ) && self.boxParams.inUse && object.isUsable && !level.gameEnded )
	{
		if ( lastRate != self.boxParams.useRate )
		{
			if( self.boxParams.curProgress > self.boxParams.useTime)
				self.boxParams.curProgress = self.boxParams.useTime;

			useBar updateBar( self.boxParams.curProgress / self.boxParams.useTime, (1000 / self.boxParams.useTime) * self.boxParams.useRate );

			if ( !self.boxParams.useRate )
			{
				useBar hideElem();
				useBarText hideElem();
			}
			else
			{
				useBar showElem();
				useBarText showElem();
			}
		}    
		lastRate = self.boxParams.useRate;
		wait ( 0.05 );
	}

	useBar destroyElem();
	useBarText destroyElem();
}

useHoldThinkLoop( player )
{
	while( !level.gameEnded && isDefined( self ) && isReallyAlive( player ) && player useButtonPressed() && player.boxParams.curProgress < player.boxParams.useTime )
	{
		player.boxParams.curProgress += (66 * player.boxParams.useRate);

		if ( isDefined( player.objectiveScaler ) )
			player.boxParams.useRate = 1 * player.objectiveScaler;
		else
			player.boxParams.useRate = 1;

		if ( player.boxParams.curProgress >= player.boxParams.useTime )
			return ( isReallyAlive( player ) );

		wait 0.05;
	} 

	return false;
}

disableWhenJuggernaut() // self == box
{
	level endon( "game_ended" );
	self endon( "death" );

	while( true )
	{
		level waittill( "juggernaut_equipped", player );
		self maps\mp\_entityheadIcons::setHeadIcon( player, "", (0,0,0) );
		self DisablePlayerUse( player );
		self thread doubleDip( player );
	}
}