#include maps\mp\_utility;
#include common_scripts\utility;

init()
{
	precacheVehicle( "attack_littlebird_mp" );
	
	//precacheString( &"HELICOPTER_FLOCK_INBOUND" );
	
	precacheModel( "vehicle_apache_mp" );
	precacheModel( "vehicle_apache_mg" );
	precacheTurret( "apache_minigun_mp" );	
	precacheVehicle( "apache_strafe_mp" );
	
	level.killStreakFuncs["littlebird_flock"] = ::tryUseLbFlock;
}


tryUseLbFlock( lifeId, kID )
{
	if ( ! self validateUseStreak() )
		return false;
	
	numIncomingVehicles = 5;
	if( currentActiveVehicleCount() >= maxVehiclesAllowed() || level.fauxVehicleCount + numIncomingVehicles >= maxVehiclesAllowed() )
	{
		self iPrintLnBold( &"MP_TOO_MANY_VEHICLES" );
		return false;
	}		

	// increment the faux vehicle count before we spawn the vehicle so no other vehicles try to spawn
	incrementFauxVehicleCount();
	incrementFauxVehicleCount();
	incrementFauxVehicleCount();
	incrementFauxVehicleCount();
	incrementFauxVehicleCount();

	result = self selectLbStrikeLocation( lifeId, "littlebird_flock" );	
	if ( ( !isDefined( result ) || !result ) )
	{
		// decrement the faux vehicle count since this failed to spawn
		decrementFauxVehicleCount();
		decrementFauxVehicleCount();
		decrementFauxVehicleCount();
		decrementFauxVehicleCount();
		decrementFauxVehicleCount();

		return false;
	}	
	
	level thread teamPlayerCardSplash( "used_littlebird_flock", self, self.team );

	return true;
}

selectLbStrikeLocation( lifeId, streakName )
{	
	self PlayLocalSound( game[ "voice" ][ self.team ] + "KS_lbd_inposition" );
	self _beginLocationSelection( streakName, "map_artillery_selector", true, 500 );	
	self endon( "stop_location_selection" );
	
	// wait for the selection
	self waittill( "confirm_location", location, locationYaw);
	
	if( currentActiveVehicleCount() >= maxVehiclesAllowed() || level.fauxVehicleCount >= maxVehiclesAllowed() )
	{
		self iPrintLnBold( &"MP_TOO_MANY_VEHICLES" );
		self notify( "cancel_location" );
		return false;
	}			

	self thread littlebirdMadeSelectionVO();							       
	self thread finishLbStrikeUsage( lifeId, location, ::callStrike, locationYaw );

	self setblurforplayer( 0, 0.3 );
	
	return true;
}


littlebirdMadeSelectionVO()
{
	self endon( "death" );
	self endon( "disconnect" );

	self PlayLocalSound( game[ "voice" ][ self.team ] + "KS_hqr_littlebird" );
	wait( 3.0 );
	self PlayLocalSound( game[ "voice" ][ self.team ] + "KS_lbd_inbound" );
}


finishLbStrikeUsage( lifeId, location, usedCallback, locationYaw )
{
	self notify( "used" );
		
	wait ( 0.05 );
	self thread stopLocationSelection( false );
	
	if ( isDefined( self ) )
		self thread [[usedCallback]]( lifeId, location, locationYaw );
}


callStrike( lifeId, location, locationYaw )
{		
	level endon( "game_ended" );		
	self endon("disconnect");
	
	//if ( level.teambased )
	//{
	//	players = level.players;
	//	
	//	for ( i = 0; i < level.players.size; i++ )
	//	{
	//		player = level.players[i];
	//		playerteam = player.pers["team"];
	//		if ( isdefined( playerteam ) )
	//		{
	//			if ( playerteam == self.pers["team"] )
	//				player iprintln( &"MP_HELICOPTER_FLOCK_INBOUND", self );
	//		}
	//	}
	//}
	
	//	stop double kills
	self.flock_victims = [];	
	
	//	get flight paths all at once
	flightPath1 = getFlightPath( location, locationYaw, 0 );
	flightPath2 = getFlightPath( location, locationYaw, -520 );	
	flightPath3 = getFlightPath( location, locationYaw, 520 );	
	flightPath4 = getFlightPath( location, locationYaw, -1040 );	
	flightPath5 = getFlightPath( location, locationYaw, 1040 );			
		
	//	leader
	level thread doLbStrike( lifeId, self, flightPath1 );
	
	wait( 0.3 );
	
	//	left wingman
	level thread doLbStrike( lifeId, self, flightPath2 );	
	
	//	right wingman
	level thread doLbStrike( lifeId, self, flightPath3 );
	
	wait( 0.3 );
	
	//	left wingman
	level thread doLbStrike( lifeId, self, flightPath4 );	
	
	//	right wingman
	level thread doLbStrike( lifeId, self, flightPath5 );
	
	//	log it
	self maps\mp\_matchdata::logKillstreakEvent( "littlebird_flock", location );
}


getFlightPath( location, locationYaw, rightOffset )
{
	location = location * (1,1,0);
	initialDirection = ( 0, locationYaw, 0 );	
	planeHalfDistance = 12000;	
	flightPath = [];	
	
	if ( isDefined( rightOffset ) && rightOffset != 0 )
		location = location + ( AnglesToRight( initialDirection ) * rightOffset ) + ( 0, 0, RandomInt( 300 ) );	
	
	//	start point
	startPoint = ( location + ( AnglesToForward( initialDirection ) * ( -1 * planeHalfDistance ) ) );	

	//	end point
	endPoint = ( location + ( AnglesToForward( initialDirection ) * planeHalfDistance ) );	
	
	//	get height
	flyHeight = self maps\mp\killstreaks\_airdrop::getFlyHeightOffset( location ) + 256;
	flightPath["start"] = startPoint + ( 0, 0, flyHeight );		
	flightPath["end"] = endPoint + ( 0, 0, flyHeight );	
	
	return flightPath;
}


doLbStrike( lifeId, owner, flightPath )
{
	level endon( "game_ended" );

	if ( !isDefined( owner ) ) 
		return;	

	forward = vectorToAngles( flightPath["end"] - flightPath["start"] );
	lb = spawnAttackLittleBird( owner, flightPath["start"], forward );
	lb.lifeId = lifeId;
	lb.alreadyDead = false;
	
	lb thread watchTimeOut();	
	lb thread watchDeath();	
	lb thread flock_handleDamage();	
	lb thread startLbFiring1();
	lb thread monitorKills();

	lb endon( "death" );
	
	//	initial target run
	lb SetMaxPitchRoll( 120, 60 );		
	lb Vehicle_SetSpeed( 48, 48 );
	lb setVehGoalPos( flightPath["end"], 0 );
	lb waittill( "goal" );
	
	//	turn
	lb SetMaxPitchRoll( 30, 40 );
	lb Vehicle_SetSpeed( 32, 32 );
	lb setVehGoalPos( flightPath["start"], 0 );			
	wait( 2 );
	
	//	return	
	lb SetMaxPitchRoll( 100, 60 );
	lb Vehicle_SetSpeed( 64, 64 );
	lb waittill ( "goal" );
	lb notify( "gone" );
	
	//	remove
	lb removeLittlebird();		
	
	//	ok to happen multiple times
	owner.flock_victims = undefined;
}


spawnAttackLittleBird( owner, origin, forward )
{
	lb = spawnHelicopter( owner, origin, forward, "apache_strafe_mp" , "vehicle_apache_mp" );

	if ( !isDefined( lb ) )
		return;

	lb maps\mp\killstreaks\_helicopter::addToLittleBirdList();
	lb thread maps\mp\killstreaks\_helicopter::removeFromLittleBirdListOnDeath();

	lb.health = 999999; // keep it from dying anywhere in code 
	lb.maxHealth = 2000; // this is the health we'll check
	lb.damageTaken = 0; // how much damage has it taken
	lb setCanDamage( true );
	lb.owner = owner;
	lb.team = owner.team;
	lb.killCount = 0;
	lb.streakName = "littlebird_flock";
	lb.heliType = "littlebird";

	lb.specialDamageCallback = ::Callback_VehicleDamage;
	
	mgTurret1 = spawnTurret( "misc_turret", lb.origin, "apache_minigun_mp" );
	mgTurret1 linkTo( lb, "tag_turret", (0,0,0), (0,0,0) );
	mgTurret1 setModel( "vehicle_apache_mg" );
	mgTurret1.angles = lb.angles; 
	mgTurret1.owner = lb.owner;
	mgTurret1.team = mgTurret1.owner.team;
	mgTurret1 makeTurretInoperable();
	mgTurret1.vehicle = lb;	
	
	killCamOrigin = ( lb.origin + ( ( AnglesToForward( lb.angles ) * -200 ) + ( AnglesToRight( lb.angles ) * -200 )  ) ) + ( 0, 0, 50 );
	mgTurret1.killCamEnt = Spawn( "script_model", killCamOrigin );
	mgTurret1.killCamEnt LinkTo( lb, "tag_origin" );
	
	lb.mgTurret1 = mgTurret1; 
	lb.mgTurret1 SetDefaultDropPitch( 0 );
	
	lb.mgTurret1 setMode( "auto_nonai" );
 	
 	lb.mgTurret1 SetSentryOwner( lb.owner );
	
	if ( level.teamBased )
	{
		lb.mgTurret1 setTurretTeam( lb.owner.team );
	}
	
	return lb;
}


watchTimeOut()
{
	level endon( "game_ended" );
	self endon( "gone" );
	self endon( "death" );
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 60.0 );
	
	self notify( "death" );
}

monitorKills()
{
	level endon( "game_ended" );
	self endon( "gone" );
	self endon( "death" );
	self endon( "stopFiring" );
	
	for(;;)
	{
		self waittill( "killedPlayer", player );
		self.killCount++;
		self.owner.flock_victims[self.owner.flock_victims.size] = player;
	}
	
}

startLbFiring1( )
{
	self endon( "gone" );
	self endon( "death" );
	self endon( "stopFiring" );
	
	for( ;; )
	{
		self.mgTurret1 waittill( "turret_on_target" );
		
		fireOnTarget = true;
		targetPlayer = self.mgTurret1 GetTurretTarget( false );
		foreach ( victim in self.owner.flock_victims )
		{
			if ( targetPlayer == victim )
			{
				self.mgTurret1 ClearTargetEntity();
				fireOnTarget = false;
				break;
			}
		}
		
		if ( fireOnTarget )
			self.mgTurret1 ShootTurret();
	}
}

flock_handleDamage() // self == heli
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

Callback_VehicleDamage( inflictor, attacker, damage, iDFlags, meansOfDeath, weapon, point, dir, hitLoc, timeOffset, modelIndex, partName )
{
	if( isDefined( self.alreadyDead ) && self.alreadyDead )
		return;

	if( !isDefined( attacker ) || attacker == self )
		return;
		
	// don't allow people to destroy things on their team if FF is off
	if( !maps\mp\gametypes\_weapons::friendlyFireCheck( self.owner, attacker ) )
		return;			
		
	if( isDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
		self.wasDamagedFromBulletPenetration = true;
	
	self.wasDamaged = true;

	modifiedDamage = damage;

	if ( isPlayer( attacker ) )
	{					
		attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "helicopter" );

		if( meansOfDeath == "MOD_RIFLE_BULLET" || meansOfDeath == "MOD_PISTOL_BULLET" )
		{
			if ( attacker _hasPerk( "specialty_armorpiercing" ) )
				modifiedDamage += damage * level.armorPiercingMod;
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
			modifiedDamage = self.maxHealth * 0.25; // takes about 1 burst of sam rockets
			break;

		case "emp_grenade_mp":
			self.largeProjectileDamage = false;
			modifiedDamage = self.maxHealth + 1;
			break;
		}
	}

	self.damageTaken += modifiedDamage;		

	if( self.damageTaken >= self.maxHealth )
	{
		if ( isPlayer( attacker ) && ( !isDefined( self.owner ) || attacker != self.owner ) )
		{
			self.alreadyDead = true;
			attacker notify( "destroyed_helicopter" );
			attacker notify( "destroyed_killstreak", weapon );
			thread teamPlayerCardSplash( "callout_destroyed_helicopter", attacker );			
			attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 300, weapon, meansOfDeath );			
			attacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DESTROYED_HELICOPTER" );
			thread maps\mp\gametypes\_missions::vehicleKilled( self.owner, self, undefined, attacker, damage, meansOfDeath, weapon );		
		}

		self notify ( "death" );
	}			
}

watchDeath()
{
	self endon( "gone" );	
	self waittill( "death" );
	
	self thread heliDestroyed();
}

heliDestroyed()
{
	self endon( "gone" );
	
	if (! isDefined(self) )
		return;
		
	self Vehicle_SetSpeed( 25, 5 );
	self thread lbSpin( RandomIntRange(180, 220) );
	
	wait( RandomFloatRange( .5, 1.5 ) );
	
	lbExplode();
}

lbSpin( speed )
{
	self endon( "explode" );
	
	// tail explosion that caused the spinning
	playfxontag( level.chopper_fx["explode"]["medium"], self, "tail_rotor_jnt" );
 	self thread trail_fx( level.chopper_fx["smoke"]["trail"], "tail_rotor_jnt", "stop tail smoke" );
	
	self setyawspeed( speed, speed, speed );
	while ( isdefined( self ) )
	{
		self settargetyaw( self.angles[1]+(speed*0.9) );
		wait ( 1 );
	}
}

trail_fx( trail_fx, trail_tag, stop_notify )
{
	// only one instance allowed
	self notify( stop_notify );
	self endon( stop_notify );
	self endon( "death" );
		
	for ( ;; )
	{
		playfxontag( trail_fx, self, trail_tag );
		wait( 0.05 );
	}
}

lbExplode()
{
	forward = ( self.origin + ( 0, 0, 1 ) ) - self.origin;

	deathAngles = self getTagAngles( "tag_deathfx" );
	playFx( level.chopper_fx["explode"]["air_death"]["littlebird"], self getTagOrigin( "tag_deathfx" ), anglesToForward( deathAngles ), anglesToUp( deathAngles ) );
	
	self playSound( "cobra_helicopter_crash" );
	self notify ( "explode" );
	
	self removeLittlebird();
}

removeLittlebird()
{	
	level.lbStrike = 0;
	
	if ( isDefined( self.mgTurret1 ) )
	{
		if ( isDefined( self.mgTurret1.killCamEnt ) )
			self.mgTurret1.killCamEnt delete();
		self.mgTurret1 delete();
	}	

	self delete();	
}