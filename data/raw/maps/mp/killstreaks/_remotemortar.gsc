#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

init()
{
	//*precacheString( &"MP_LASE_TARGET_FOR_GUIDED_MORTAR" );
	//*precacheString( &"MP_WAIT_FOR_MORTAR_READY" );
	//*precacheString( &"MP_MORTAR_ROUNDS_DEPLETED" );
	//*precacheString( &"SPLASHES_DESTROYED_REMOTE_MORTAR" );
	
	//*precacheModel( "vehicle_predator_b" );
	//*precacheItem( "remote_mortar_missile_mp" );
	//*precacheItem( "mortar_remote_mp" );
	//*precacheItem( "mortar_remote_zoom_mp" );
	
	//*precacheShader( "compass_waypoint_bomb" );
	//*precacheShader( "viper_locked_box" );
	//*PrecacheMiniMapIcon( "compass_objpoint_reaper_friendly" );
	//*PrecacheMiniMapIcon( "compass_objpoint_reaper_enemy" );
	
	//*level.remote_mortar_fx["laserTarget"] = loadfx("misc/laser_glow");
	//*level.remote_mortar_fx["missileExplode"] = loadfx( "explosions/bouncing_betty_explosion" );
	
	//*level.killstreakFuncs["remote_mortar"] = ::tryUseRemoteMortar;
	
	level.remote_mortar = undefined;

/#
		SetDevDvarIfUninitialized( "scr_remote_mortar_timeout", 40.0 );
#/
}


tryUseRemoteMortar( lifeId )
{	
	if ( isDefined( level.remote_mortar ) )
	{
		self iPrintLnBold( &"MP_AIR_SPACE_TOO_CROWDED" );
		return false;
	}
	if ( !self validateUseStreak() )
		return false;			

	self setUsingRemote( "remote_mortar" );
	result = self maps\mp\killstreaks\_killstreaks::initRideKillstreak( "remote_mortar" );
	if ( result != "success" )
	{
		if ( result != "disconnect" )
			self clearUsingRemote();

		return false;
	}
	//	check again, could have filled up while initRideKillstreak was running
	else if ( isDefined( level.remote_mortar ) )
	{
		self iPrintLnBold( &"MP_AIR_SPACE_TOO_CROWDED" );
		self clearUsingRemote();
		return false;
	}	
	
	self maps\mp\_matchdata::logKillstreakEvent( "remote_mortar", self.origin );
	
	return startRemoteMortar( lifeId );
}


startRemoteMortar( lifeId )
{
	remote = spawnRemote( lifeId, self );
	if ( !isDefined( remote ) )
		return false;
		
	level.remote_mortar = remote;
	
	self remoteRide( remote );
	
	self thread teamPlayerCardSplash( "used_remote_mortar", self );
	return true;
}


spawnRemote( lifeId, owner )
{
	remote = spawnPlane( owner, "script_model", level.UAVRig getTagOrigin( "tag_origin" ), "compass_objpoint_reaper_friendly", "compass_objpoint_reaper_enemy" );
	if ( !isDefined( remote ) )
		return undefined;
		
	remote setModel( "vehicle_predator_b" );
	remote.lifeId = lifeId;
	remote.team = owner.team;
	remote.owner = owner;
	remote.numFlares = 1;
	
	remote setCanDamage( true );	
	remote thread damageTracker();
	
	remote.heliType = "remote_mortar";	
	
	//	for target lists (javelin, stinger, sam, emp, etc)
	remote.uavType = "remote_mortar";	
	remote maps\mp\killstreaks\_uav::addUAVModel();

	//	same height and radius as the AC130 with random angle and counter rotation
	zOffset = 6300;
	angle = randomInt( 360 );
	radiusOffset = 6100;
	xOffset = cos( angle ) * radiusOffset;
	yOffset = sin( angle ) * radiusOffset;
	angleVector = vectorNormalize( (xOffset,yOffset,zOffset) );
	angleVector = ( angleVector * 6100 );
	remote linkTo( level.UAVRig, "tag_origin", angleVector, (0,angle-90,10) );	
	
	//	hud stuff
	owner SetClientDvar( "ui_reaper_targetDistance", -1 );
	owner SetClientDvar( "ui_reaper_ammoCount", 14 );
	
	remote thread handleDeath( owner );
	remote thread handleTimeout( owner );
	remote thread handleOwnerChangeTeam( owner );
	remote thread handleOwnerDisconnect( owner );
	remote thread handleIncomingStinger();
	remote thread handleIncomingSAM();

	return remote;	
}


lookCenter()
{
	wait( 0.05 );
	
	lookVec = vectorToAngles( level.UAVRig.origin - self GetEye() );
	
	self setPlayerAngles( lookVec  );
}


remoteRide( remote )
{
	self _giveWeapon("mortar_remote_mp");
	self SwitchToWeapon("mortar_remote_mp");	
	
	// with the way we do visionsets we need to wait for the clearRideIntro() is done before we set thermal
	self thread waitSetThermal( 1.0, remote );

	if ( getDvarInt( "camera_thirdPerson" ) )
		self setThirdPersonDOF( false );

	self PlayerLinkWeaponviewToDelta( remote, "tag_player", 1.0, 40, 40, 25, 40 );	
	self thread lookCenter();
	
	self _disableWeaponSwitch();
	
	self thread remoteTargeting( remote );
	self thread remoteFiring( remote );
	self thread remoteZoom( remote );
}

waitSetThermal( delay, remote )
{
	self endon( "disconnect" );
	remote endon( "death" );

	wait( delay	);

	self VisionSetThermalForPlayer( level.ac130.enhanced_vision, 0 );
	self ThermalVisionOn();
	self ThermalVisionFOFOverlayOn();	
}

remoteTargeting( remote )
{	
	level  endon( "game_ended" );
	self   endon( "disconnect" );
	remote endon( "remote_done" );
	remote endon( "death" );	

	remote.targetEnt = SpawnFx( level.remote_mortar_fx["laserTarget"], (0,0,0) );	
	
	while ( true )
	{
	 	origin = self GetEye();
		forward = AnglesToForward( self GetPlayerAngles() );
		endpoint = origin + forward * 15000;
		traceData = BulletTrace( origin, endpoint, false, remote.targetEnt );
		if ( isDefined( traceData["position"] ) )
		{
			remote.targetEnt.origin = traceData["position"];
			triggerFX( remote.targetEnt );
		}		
		wait( 0.05 );
	}
}
	

remoteFiring( remote )
{
	level  endon( "game_ended" );
	self   endon( "disconnect" );
	remote endon( "remote_done" );
	remote endon( "death" );
	
	curTime = getTime();
	lastFireTime = curTime-2200;
	ammo = 14;
	self.firingReaper = false;
	
	while( true )
	{
		curTime = getTime();
		if ( self attackButtonPressed() && ( curTime - lastFireTime > 3000 ) )
		{
			ammo--;
			self SetClientDvar( "ui_reaper_ammoCount", ammo );
			lastFireTime = curTime;
			self.firingReaper = true;
			
			self playLocalSound( "reaper_fire" );
			self PlayRumbleOnEntity( "damage_heavy" );

			origin = self GetEye();
			forward = AnglesToForward( self GetPlayerAngles() );
			right = AnglesToRight( self GetPlayerAngles() );
			offset = origin + ( forward * 100 ) + ( right * -100 );			
			missile = MagicBullet( "remote_mortar_missile_mp", offset, remote.targetEnt.origin, self );
			Earthquake( 0.3, 0.5, origin, 256 );
			
			//// attach a kill cam ent so we can customize the view
			//killCamEnt = Spawn( "script_model", missile.origin + ( forward * -75 ) + ( right * 25 ) );
			//killCamEnt LinkTo( missile );
			//missile.killCamEnt = killCamEnt;

			missile Missile_SetTargetEnt( remote.targetEnt );
			missile Missile_SetFlightmodeDirect();
			
			missile thread remoteMissileDistance( remote );
			missile thread remoteMissileLife( remote );
			
			missile waittill( "death" );
			
			//if( IsDefined( killCamEnt ) )
			//	killCamEnt delete();

			self SetClientDvar( "ui_reaper_targetDistance", -1 );
			self.firingReaper = false;
			
			if ( ammo == 0 )
				break;		
		}
		else
			wait( 0.05 );		
	}	
	
	self notify( "removed_reaper_ammo" );
	self remoteEndRide( remote );
	remote thread remoteLeave();	
}


handleToggleZoom( remote )
{
	level  endon( "game_ended" );
	self   endon( "disconnect" );
	remote endon( "remote_done" );
	remote endon( "death" );
	
	self notifyOnPlayerCommand( "remote_mortar_toggleZoom1", "+ads_akimbo_accessible" );
	
	while ( true )
	{
		result = waittill_any_return( "remote_mortar_toggleZoom1" );
		
		if ( !isDefined( self.remote_mortar_toggleZoom ) )
			self.remote_mortar_toggleZoom = 0;
		
		self.remote_mortar_toggleZoom = 1-self.remote_mortar_toggleZoom;
	}		
}


remoteZoom( remote )
{	
	level  endon( "game_ended" );
	self   endon( "disconnect" );
	remote endon( "remote_done" );
	remote endon( "death" );	

	self.remote_mortar_toggleZoom = undefined;
	self thread handleToggleZoom( remote );
	
	remote.zoomed = false;
	usingToggle = false;
	
	//	first find out how zoom was initiated
	while ( true )
	{
		if ( self adsButtonPressed() )
		{
			wait( 0.05 );
			if ( isDefined( self.remote_mortar_toggleZoom ) )
				usingToggle = true;
			break;
		}
		wait( 0.05 );
	}
		
	while ( true )	
	{
	 	if ( ( !usingToggle && self adsButtonPressed() ) || ( usingToggle && self.remote_mortar_toggleZoom ) )
	 	{
	 		if ( remote.zoomed == false )
	 		{
				self _giveWeapon("mortar_remote_zoom_mp");
				self SwitchToWeapon("mortar_remote_zoom_mp");	 			
	 			remote.zoomed = true;		 			
	 		}
	 	}
 		else if ( ( !usingToggle && !self adsButtonPressed() ) || ( usingToggle && !self.remote_mortar_toggleZoom ) )
 		{
 			if ( remote.zoomed == true )
 			{
				self _giveWeapon("mortar_remote_mp");
				self SwitchToWeapon("mortar_remote_mp");	 			
	 			remote.zoomed = false;				
	 		}
 		}	 
	 	
	 	wait( 0.05 );
	}
}


remoteMissileDistance( remote )
{
	level  endon( "game_ended" );
	remote endon( "death" );
	remote endon( "remote_done" );
	self   endon( "death" );
	
	while( true )
	{
		targetDist = distance( self.origin, remote.targetent.origin );
		remote.owner SetClientDvar( "ui_reaper_targetDistance", int( targetDist / 12 ) );
		
		wait( 0.05 );
	}
}	


remoteMissileLife( remote )
{
	self endon( "death" );
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 6 );
	
	playFX( level.remote_mortar_fx["missileExplode"], self.origin );
	self delete();
}


remoteEndRide( remote )
{
	if ( isDefined( remote ) )
	{
		remote notify( "helicopter_done" );
		//if ( isDefined( remote.laserEnt ) )
			//remote.laserEnt LaserOff();
	}
	
	self ThermalVisionOff();
	self ThermalVisionFOFOverlayOff();
	self VisionSetThermalForPlayer( game["thermal_vision"], 0 );
	if ( IsDefined( level.nukeDetonated ) )
		self VisionSetNakedForPlayer( level.nukeVisionSet, 0 );
	else
		self VisionSetNakedForPlayer( "", 0 ); // go to default visionset
	
	
	self unlink();
	self clearUsingRemote();
	if ( getDvarInt( "camera_thirdPerson" ) )
		self setThirdPersonDOF( true );
	
	self switchToWeapon( self getLastWeapon() );
	// take the killstreak weapons
	killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( "remote_mortar" );
	self TakeWeapon( killstreakWeapon );
	self TakeWeapon( "mortar_remote_zoom_mp" );
	self TakeWeapon( "mortar_remote_mp" );

	self _enableWeaponSwitch();
}


handleTimeout( owner )
{
	level endon( "game_ended" );
	owner endon( "disconnect" );
	owner endon( "removed_reaper_ammo" );
	self  endon( "death" );	
	
	lifeSpan = 40.0;
/#
	lifeSpan = GetDvarInt( "scr_remote_mortar_timeout", lifeSpan );
#/
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( lifeSpan );
	
	while( owner.firingReaper )
		wait( 0.05 );
	
	if ( isDefined( owner ) )
		owner remoteEndRide( self );
	self thread remoteLeave();	
}


handleDeath( owner )
{
	level endon( "game_ended" );	
	owner endon( "disconnect" );
	self  endon( "remote_done" );
	owner endon( "removed_reaper_ammo" );

	self waittill( "death" );
	
	if ( isDefined( owner ) )
		owner remoteEndRide( self );		
	level thread removeRemote( self );
}


handleOwnerChangeTeam( owner )
{
	level endon( "game_ended" );
	self  endon( "remote_done" );
	self  endon( "death" );
	owner endon( "disconnect" );
	owner endon( "removed_reaper_ammo" );
		
	owner waittill_any( "joined_team", "joined_spectators" );
	
	if ( isDefined( owner ) )
		owner remoteEndRide( self );
	self thread remoteLeave();	
}


handleOwnerDisconnect( owner )
{
	level endon( "game_ended" );
	self  endon( "remote_done" );
	self  endon( "death" );
	owner endon( "removed_reaper_ammo" );
	
	owner waittill( "disconnect" );
	
	self thread remoteLeave();
}


removeRemote( remote )
{
	self notify( "remote_removed" );
	
	if ( isDefined( remote.targetEnt ) )
		remote.targetEnt delete();

	if( IsDefined( remote ) )
	{
		remote delete();	
		remote maps\mp\killstreaks\_uav::removeUAVModel();
	}
	
	level.remote_mortar = undefined;
}


remoteLeave()
{
	level endon( "game_ended" );
	self  endon( "death" );
	
	self notify( "remote_done" );			

	self unlink();
	destPoint = self.origin + ( AnglesToForward( self.angles ) * 20000 );
	self moveTo( destPoint, 30 );
	PlayFXOnTag( level._effect[ "ac130_engineeffect" ] , self, "tag_origin" );
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 3 );

	self moveTo( destPoint, 4, 4, 0.0 );
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 4 );		
	
	level thread removeRemote( self );		
}


//	Entities spawned from SpawnPlane do not respond to pre-damage callbacks 
//	so we have to wait until we get the post-damage event.
//
//	Because the damage has already happened by the time we find out about it,
//	we need to use an artificially high health value, restore it on erroneous damage
//	events and track a virtual damage taken against a virtual max health.
damageTracker()
{	
	level endon( "game_ended" );
	self.owner endon( "disconnect" );
	
	self.health = 999999; // keep it from dying anywhere in code
	self.maxHealth = 1500; // this is the health we'll check
	self.damageTaken = 0; // how much damage has it taken
	
	while( true )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );		
				
		// don't allow people to destroy things on their team if FF is off
		if ( !maps\mp\gametypes\_weapons::friendlyFireCheck( self.owner, attacker ) )
			continue;

		if ( !IsDefined( self ) )
			return;

		if ( isDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
			self.wasDamagedFromBulletPenetration = true;

		self.wasDamaged = true;

		modifiedDamage = damage;

		if( IsPlayer( attacker ) )
		{					
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "" );

			if( meansOfDeath == "MOD_RIFLE_BULLET" || meansOfDeath == "MOD_PISTOL_BULLET" )
			{
				if ( attacker _hasPerk( "specialty_armorpiercing" ) )
					modifiedDamage += damage * level.armorPiercingMod;
			}
		}

		if( IsDefined( weapon ) )
		{
			switch( weapon )
			{
			case "stinger_mp":
			case "javelin_mp":
				self.largeProjectileDamage = true;
				modifiedDamage = self.maxhealth + 1;
				break;

			case "sam_projectile_mp":
				self.largeProjectileDamage = true;		
				break;
			}
		}

		self.damageTaken += modifiedDamage;
		
		if( IsDefined( self.owner ) )
			self.owner playLocalSound( "reaper_damaged" );
					
		if ( self.damageTaken >= self.maxHealth )
		{
			if ( isPlayer( attacker ) && ( !isDefined( self.owner ) || attacker != self.owner ) )
			{						
				self Hide();
				forward = ( AnglesToRight( self.angles ) * 200 );
				playFx ( level.uav_fx[ "explode" ], self.origin, forward );	

				attacker notify( "destroyed_killstreak", weapon );
				thread teamPlayerCardSplash( "callout_destroyed_remote_mortar", attacker );			
				attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 50, weapon, meansOfDeath );			
				attacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DESTROYED_REMOTE_MORTAR" );
				thread maps\mp\gametypes\_missions::vehicleKilled( self.owner, self, undefined, attacker, damage, meansOfDeath, weapon );	
			}
			
			self notify( "death" );
			return;
		}			
	}	
}

handleIncomingStinger() // self == remote mortar
{
	level endon ( "game_ended" );
	self endon ( "death" );

	while( true )
	{
		level waittill ( "stinger_fired", player, missile, lockTarget );

		if ( !IsDefined( lockTarget ) || (lockTarget != self) )
			continue;

		missile thread stingerProximityDetonate( lockTarget, player );
	}
}

stingerProximityDetonate( missileTarget, player ) // self == missile
{
	self endon ( "death" );

	if( IsDefined( missileTarget.owner ) )
		missileTarget.owner PlayLocalSound( "missile_incoming" );

	self Missile_SetTargetEnt( missileTarget );

	minDist = Distance( self.origin, missileTarget GetPointInBounds( 0, 0, 0 ) );
	lastCenter = missileTarget GetPointInBounds( 0, 0, 0 );

	while( true )
	{		
		// already destroyed
		if( !IsDefined( missileTarget ) )
			center = lastCenter;
		else
			center = missileTarget GetPointInBounds( 0, 0, 0 );

		lastCenter = center;		

		curDist = Distance( self.origin, center );

		if( curDist < 3000 && isDefined( missileTarget.numFlares ) && missileTarget.numFlares > 0 )
		{
			missileTarget.numFlares--;			

			missileTarget thread maps\mp\killstreaks\_helicopter::playFlareFx();	
			newTarget = missileTarget maps\mp\killstreaks\_helicopter::deployFlares();

			self Missile_SetTargetEnt( newTarget );
			missileTarget = newTarget;
			
			if( IsDefined( missileTarget.owner ) )
				missileTarget.owner StopLocalSound( "missile_incoming" );

			return;
		}		

		if( curDist < minDist )
			minDist = curDist;

		if( curDist > minDist )
		{
			if( curDist > 1536 )
				return;

			if( IsDefined( missileTarget.owner ) )
			{
				missileTarget.owner stopLocalSound( "missile_incoming" ); 

				if( level.teambased )
				{
					if( missileTarget.team != player.team )
						RadiusDamage( self.origin, 1000, 1000, 1000, player, "MOD_EXPLOSIVE", "stinger_mp" );
				}
				else
				{
					RadiusDamage( self.origin, 1000, 1000, 1000, player, "MOD_EXPLOSIVE", "stinger_mp" );
				}
			}

			self Hide();

			wait( 0.05 );
			self delete();
		}

		wait ( 0.05 );
	}	
}

handleIncomingSAM() // self == remote mortar
{
	level endon ( "game_ended" );
	self endon ( "death" );

	while( true )
	{
		level waittill ( "sam_fired", player, missileGroup, lockTarget );

		if ( !IsDefined( lockTarget ) || (lockTarget != self) )
			continue;

		level thread samProximityDetonate( lockTarget, player, missileGroup );
	}
}

samProximityDetonate( missileTarget, player, missileGroup )
{
	missileTarget endon( "death" );

	if( IsDefined( missileTarget.owner ) )
		missileTarget.owner PlayLocalSound( "missile_incoming" );

	sam_projectile_damage = 150; // this should match the gdt entry
	sam_projectile_damage_radius = 1000;

	minDist = [];
	for( i = 0; i < missileGroup.size; i++ )
	{
		if( IsDefined( missileGroup[ i ] ) )
			minDist[ i ] = Distance( missileGroup[ i ].origin, missileTarget GetPointInBounds( 0, 0, 0 ) );
		else
			minDist[ i ] = undefined;
	}

	while( true )
	{
		center = missileTarget GetPointInBounds( 0, 0, 0 );

		curDist = [];
		for( i = 0; i < missileGroup.size; i++ )
		{
			if( IsDefined( missileGroup[ i ] ) )
				curDist[ i ] = Distance( missileGroup[ i ].origin, center );
		}

		for( i = 0; i < curDist.size; i++ )
		{
			if( IsDefined( curDist[ i ] ) )
			{
				// if one of the missiles in the group get close, set off flares and redirect them all
				if( curDist[ i ] < 3000 && missileTarget.numFlares > 0 )
				{
					missileTarget.numFlares--;			

					missileTarget thread maps\mp\killstreaks\_helicopter::playFlareFx();	
					newTarget = missileTarget maps\mp\killstreaks\_helicopter::deployFlares();

					for( j = 0; j < missileGroup.size; j++ )					
					{
						if( IsDefined( missileGroup[ j ] ) )
						{
							missileGroup[ j ] Missile_SetTargetEnt( newTarget );
						}
					}

					if( IsDefined( missileTarget.owner ) )
						missileTarget.owner StopLocalSound( "missile_incoming" );

					return;
				}		

				if( curDist[ i ] < minDist[ i ] )
					minDist[ i ] = curDist[ i ];

				if( curDist[ i ] > minDist[ i ] )
				{
					if( curDist[ i ] > 1536 )
						continue;

					if( IsDefined( missileTarget.owner ) )
					{
						missileTarget.owner StopLocalSound( "missile_incoming" ); 

						if( level.teambased )
						{
							if( missileTarget.team != player.team )
								RadiusDamage( missileGroup[ i ].origin, sam_projectile_damage_radius, sam_projectile_damage, sam_projectile_damage, player, "MOD_EXPLOSIVE", "sam_projectile_mp" );
						}
						else
						{
							RadiusDamage( missileGroup[ i ].origin, sam_projectile_damage_radius, sam_projectile_damage, sam_projectile_damage, player, "MOD_EXPLOSIVE", "sam_projectile_mp" );
						}
					}

					missileGroup[ i ] Hide();

					wait ( 0.05 );
					missileGroup[ i ] delete();
				}
			}
		}

		wait ( 0.05 );
	}	
}
