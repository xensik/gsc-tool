#include maps\_utility;
#include common_scripts\utility;

globalThink()
{
	if ( !isdefined( self.vehicletype ) )
		return;

	isHelicopter = false;
	if ( (self.vehicletype == "hind") || (self.vehicletype == "ny_harbor_hind"))
	{
		isHelicopter = true;
	}
	if ( ( self.vehicletype == "cobra" ) || ( self.vehicletype == "cobra_player" ) )
	{
		self thread attachMissiles( "chopperpilot_hellfire", "cobra_Sidewinder" );
		if ( isdefined( self.fullModel ) )
			self.fullModel thread attachMissiles( "chopperpilot_hellfire", "cobra_Sidewinder" );
		isHelicopter = true;
	}

	if ( !isHelicopter )
		return;

	level thread flares_think( self );
	level thread maps\_helicopter_ai::evasive_think( self );

	if ( getdvar( "cobrapilot_wingman_enabled" ) == "1" )
	{
		if ( isdefined( self.script_wingman ) )
		{
			level.wingman = self;
			level thread maps\_helicopter_ai::wingman_think( self );
		}
	}
}

flares_think( vehicle )
{
	vehicle endon( "death" );
	
	notifyOnCommand( "flare_button", "+frag" );
	notifyOnCommand( "flare_button", "+usereload" );
	notifyOnCommand( "flare_button", "+activate" );
	//notifyOnCommand( "flare_button", "-smoke" );
	
	while ( vehicle.health > 0 )
	{
		if ( isdefined( vehicle.playercontrolled ) )
		{
			vehicle.pilot waittill( "flare_button" );
		}
		else
		{
			vehicle waittill( "incomming_missile", eMissile );
			if ( !isdefined( eMissile ) )
				continue;

			//sometimes dont drop flares
			if ( randomint( 3 ) == 0 )
				continue;

			wait randomfloatrange( 0.5, 1.0 );
		}

		thread flares_fire( vehicle );

		//wait 0.05;
		//if ( !isdefined( vehicle.playercontrolled ) )
		wait 3.0;
	}
}

flares_fire_burst( vehicle, fxCount, flareCount, flareTime )
{
	assert( isdefined( level.flare_fx[ vehicle.vehicletype ] ) );

	assert( fxCount >= flareCount );
	
	everyOther = true;
	for ( i = 0 ; i < fxCount ; i++ )
	{
		playfx( level.flare_fx[ vehicle.vehicletype ], vehicle getTagOrigin( "tag_flare" ) );

		if ( isdefined( vehicle.playercontrolled ) )
		{
			level.stats[ "flares_used" ]++ ;
			vehicle notify( "dropping_flares" );
			if ( everyOther )
				vehicle playSound( "cobra_flare_fire" );
			everyOther = !everyOther;
		}
		
		if ( i <= flareCount - 1 )
			thread flares_redirect_missiles( vehicle, flareTime );

		wait 0.1;
	}
}

flares_fire( vehicle )
{
	vehicle endon( "death" );
	
	flareTime = 5.0;
	if ( isdefined( vehicle.flare_duration ) )
		flareTime = vehicle.flare_duration;
	
	flares_fire_burst( vehicle, 8, 1, flareTime );
}

create_missileAttractor_on_player_chopper()
{
	assert( isdefined( self ) );
	assert( isdefined( self.centerAimPoint ) );
	
	if ( isdefined( self.missileAttractor ) )
		Missile_DeleteAttractor( self.missileAttractor );
	
	self.missileAttractor = Missile_CreateAttractorEnt( self.centerAimPoint, 10000, 10000 );
}

flares_redirect_missiles( vehicle, flareTime )
{
	vehicle notify( "flares_out" );
	vehicle endon( "death" );
	vehicle endon( "flares_out" );

	if ( !isdefined( flareTime ) )
		flareTime = 5.0;

	// create a script_origin at the flares location and move it down with gravity
	vec = flares_get_vehicle_velocity( vehicle );
	flare = spawn( "script_origin", vehicle getTagOrigin( "tag_flare" ) );
	flare movegravity( vec, flareTime );
	
	// redirect missiles to flares for player vehicle
	flareMissileAttractor = undefined;
	if ( isdefined( vehicle.playercontrolled ) )
	{
		// delete the attractor on the heli
		if ( isdefined( vehicle.missileAttractor ) )
			Missile_DeleteAttractor( vehicle.missileAttractor );
		// make an attractor that will fall with the flares
		flareMissileAttractor = Missile_CreateAttractorEnt( flare, 10000, 10000 );
	}
	
	// redirect all incomming missiles to the new flares
	if ( isdefined( vehicle.incomming_Missiles ) )
	{
		for ( i = 0 ; i < vehicle.incomming_Missiles.size ; i++ )
			vehicle.incomming_Missiles[ i ] Missile_SetTargetEnt( flare );
	}

	// wait for flares to burn out	
	wait flareTime;
	
	// get rid of missile attractor and put one back on the chopper
	if ( isdefined( vehicle.playercontrolled ) )
	{
		if ( isdefined( flareMissileAttractor ) )
			Missile_DeleteAttractor( flareMissileAttractor );
		vehicle thread create_missileAttractor_on_player_chopper();
	}
	
	if ( !isdefined( vehicle.script_targetoffset_z ) )
		vehicle.script_targetoffset_z = 0;
	offset = ( 0, 0, vehicle.script_targetoffset_z );
	
	// when the flares burn out redirect missiles to the main target again ( if missile is still alive )
	if ( !isdefined( vehicle.incomming_Missiles ) )
		return;
	for ( i = 0 ; i < vehicle.incomming_Missiles.size ; i++ )
		vehicle.incomming_Missiles[ i ] Missile_SetTargetEnt( vehicle, offset );
}

flares_get_vehicle_velocity( vehicle )
{
	org1 = vehicle.origin;
	wait 0.05;
	vec = ( vehicle.origin - org1 );
	return ( vec * 20 );
}

missile_deathWait( eMissile, eMissile_Target )
{
	eMissile_Target endon( "death" );

	eMissile waittill( "death" );

	if ( !isdefined( eMissile_Target.incomming_Missiles ) )
		return;

	eMissile_Target.incomming_Missiles = array_remove( eMissile_Target.incomming_Missiles, eMissile );
}

getEnemyTarget( fRadius, iFOVcos, getAITargets, doSightTrace, getVehicleTargets, randomizeTargetArray, aExcluders )
{
	if ( !isdefined( getAITargets ) )
		getAITargets = false;

	if ( !isdefined( doSightTrace ) )
		doSightTrace = false;

	if ( !isdefined( getVehicleTargets ) )
		getVehicleTargets = true;

	if ( !isdefined( randomizeTargetArray ) )
		randomizeTargetArray = false;

	// look for a vehicle target
	eTargets = [];
	eClosestValidTarget = undefined;

	enemyTeam = common_scripts\utility::get_enemy_team( self.script_team );
	possibleTargets = [];
	//prof_begin( "cobrapilot_ai" );

	if ( getVehicleTargets )
	{
		assert( isdefined( level.vehicles[ enemyTeam ] ) );
		for ( i = 0 ; i < level.vehicles[ enemyTeam ].size ; i++ )
			possibleTargets[ possibleTargets.size ] = level.vehicles[ enemyTeam ][ i ];
	}

	if ( getAITargets )
	{
		enemyAI = getaiarray( enemyTeam );
		for ( i = 0 ; i < enemyAI.size ; i++ )
		{
			if( isdefined( enemyAI[ i ].ignored_by_attack_heli ) )
				continue;
			possibleTargets[ possibleTargets.size ] = enemyAI[ i ];
		}
		if ( enemyTeam == "allies" )
		{
			for ( i = 0; i < level.players.size; i++ )
			{
				possibleTargets[ possibleTargets.size ] = level.players[ i ];
			}
		}
	}

	if ( isdefined( aExcluders ) )
		possibleTargets = array_exclude( possibleTargets, aExcluders );

	if ( randomizeTargetArray )
		possibleTargets = array_randomize( possibleTargets );

	forwardvec = anglestoforward( self.angles );
	for ( i = 0 ; i < possibleTargets.size ; i++ )
	{
		// threatbias - if this is an ignored group then dont consider this target
		if ( ( isSentient( possibleTargets[ i ] ) ) && ( isSentient( self ) ) && ( self getThreatBiasGroup() != "" ) )
		{
			bias = getThreatBias( possibleTargets[ i ] getThreatBiasGroup(), self getThreatBiasGroup() );
			if ( bias <= -1000000 )
				continue;
		}

		// check if the target is within range
		if ( isdefined( fRadius ) && ( fRadius > 0 ) )
		{
			if ( distance( self.origin, possibleTargets[ i ].origin ) > fRadius )
				continue;
		}

		// check if the target is within fov
		if ( isdefined( iFOVcos ) )
		{
			normalvec = vectorNormalize( possibleTargets[ i ].origin - ( self.origin ) );
			vecdot = vectordot( forwardvec, normalvec );
			if ( vecdot <= iFOVcos )
				continue;
		}

		// check if a sight trace passes
		if ( doSightTrace )
		{
			sightTracePassed = false;
			if ( isAi( possibleTargets[ i ] ) )
				TraceZoffset = 48;
			else
				TraceZoffset = 150;
			sightTracePassed = sighttracepassed( self.origin, possibleTargets[ i ].origin + ( 0, 0, TraceZoffset ), false, self );
			if ( !sightTracePassed )
				continue;
		}

		eTargets[ eTargets.size ] = possibleTargets[ i ];
	}

	//prof_end( "cobrapilot_ai" );

	self notify( "gunner_new_target" );

	// return if no targets were found
	if ( eTargets.size == 0 )
		return eClosestValidTarget;

	// if only one target was found return it
	if ( eTargets.size == 1 )
		return eTargets[ 0 ];

	// return the closest of the targets
	//prof_begin( "cobrapilot_ai" );
	theTarget = getClosest( self.origin, eTargets );
	//prof_end( "cobrapilot_ai" );

	return theTarget;
}

shootEnemyTarget_Bullets( eTarget )
{
	self endon( "death" );
	self endon( "mg_off" );
	eTarget endon( "death" );
	self endon( "gunner_new_target" );
	if ( isdefined( self.playercontrolled ) )
		self endon( "gunner_stop_firing" );

	eTargetOffset = ( 0, 0, 0 );
	if ( isdefined( eTarget.script_targetoffset_z ) )
		eTargetOffset += ( 0, 0, eTarget.script_targetoffset_z );
	else if ( isSentient( eTarget ) )
		eTargetOffset = ( 0, 0, 32 );

	self setTurretTargetEnt( eTarget, eTargetOffset );

	while ( self.health > 0 )
	{
		randomShots = randomintrange( 1, 25 );
		if ( getdvar( "cobrapilot_debug" ) == "1" )
			iprintln( "randomShots = " + randomShots );

		for ( i = 0 ; i < randomShots ; i++ )
		{
			// if the vehicle firing the bullets is the players vehicle we have to switch to the 20mm gun
			if ( isdefined( self.playercontrolled ) )
			{
				if ( ( isdefined( level.cobraWeapon ) ) && ( level.cobraWeapon.size > 0 ) )
					self setVehWeapon( level.GunnerWeapon );
			}

			self thread shootEnemyTarget_Bullets_DebugLine( self, "tag_turret", eTarget, eTargetOffset, ( 1, 1, 0 ), 0.05 );
			self fireWeapon( "tag_flash" );

			// then switch it back to the players selection after the shots are fired
			if ( isdefined( self.playercontrolled ) )
				self setVehWeapon( level.cobraWeapon[ self.pilot.currentWeapon ].v[ "weapon" ] );

			wait 0.05;
		}

		wait randomFloatRange( 0.25, 2.5 );
	}
}

shootEnemyTarget_Bullets_DebugLine( eStartEnt, eStartEntTag, eTarget, eTargetOffset, color, timer )
{
	if ( getdvar( "cobrapilot_debug" ) != "1" )
		return;

	if ( !isdefined( color ) )
		color = ( 0, 0, 0 );

	eTarget endon( "death" );
	self endon( "gunner_new_target" );

	assert( isdefined( eStartEntTag ) );

	if ( !isdefined( eTargetOffset ) )
		eTargetOffset = ( 0, 0, 0 );

	if ( isdefined( timer ) )
	{
		timer = gettime() + ( timer * 1000 );
		while ( gettime() < timer )
		{
			line( eStartEnt getTagOrigin( eStartEntTag ), eTarget.origin + eTargetOffset, color );
			wait 0.05;
		}
	}
	else
	{
		for ( ;; )
		{
			line( eStartEnt getTagOrigin( eStartEntTag ), eTarget.origin + eTargetOffset, color );
			wait 0.05;
		}
	}
}

attachMissiles( weapon1, weapon2, weapon3, weapon4 )
{
	self.hasAttachedWeapons = true;
	assert( isdefined( weapon1 ) );
	weapon = [];
	weapon[ 0 ] = weapon1;
	if ( isdefined( weapon2 ) )
		weapon[ 1 ] = weapon2;
	if ( isdefined( weapon3 ) )
		weapon[ 2 ] = weapon3;
	if ( isdefined( weapon4 ) )
		weapon[ 3 ] = weapon4;
	
	for ( i = 0 ; i < weapon.size ; i++ )
	{
		for ( k = 0 ; k < level.cobra_weapon_tags[ weapon[ i ] ].size ; k++ )
		{
			self attach( level.cobra_missile_models[ weapon[ i ] ], level.cobra_weapon_tags[ weapon[ i ] ][ k ] );
		}
	}
}

fire_missile( sMissileType, iShots, eTarget, fDelay, target_los )
{
	if ( !isdefined( iShots ) )
		iShots = 1;
	assert( self.health > 0 );

	weaponName = undefined;
	weaponShootTime = undefined;
	defaultWeapon = "cobra_20mm";
	tags = [];
	switch( sMissileType )
	{
		case "f15_missile":
			weaponName = "cobra_Sidewinder";
			tags[ 0 ] = "le_side_wing_jnt";
			tags[ 1 ] = "ri_side_wing_jnt";
			break;
		case "mi28_seeker":
			weaponName = "cobra_seeker";
			tags[ 0 ] = "tag_store_L_1_a";
			tags[ 1 ] = "tag_store_R_1_a";
			tags[ 2 ] = "tag_store_L_2_a";
			tags[ 3 ] = "tag_store_R_2_a";
			break;
		case "ffar":
			weaponName = "cobra_FFAR";
			tags[ 0 ] = "tag_store_r_2";
			break;
		case "seeker":
			weaponName = "cobra_seeker";
			tags[ 0 ] = "tag_store_r_2";
			break;
		case "ffar_bog_a_lite":
			weaponName = "cobra_FFAR_bog_a_lite";
			tags[ 0 ] = "tag_store_r_2";
			break;
		case "ffar_airlift":
			weaponName = "cobra_FFAR_airlift";
			tags[ 0 ] = "tag_store_L_wing";
			tags[ 1 ] = "tag_store_R_wing";
			break;
		case "ffar_airlift_nofx":
			weaponName = "cobra_FFAR_airlift_nofx";
			tags[ 0 ] = "tag_store_L_wing";
			tags[ 1 ] = "tag_store_R_wing";
			break;
		case "cobra_zippy":
			weaponName = "zippy_rockets";
			tags[ 0 ] = "tag_store_L_wing";
			tags[ 1 ] = "tag_store_R_wing";
			break;
		case "apache_zippy":
			weaponName = "zippy_rockets_apache";
			tags[ 0 ] = "tag_flash_2";
			tags[ 1 ] = "tag_flash_3";
			break;
		case "apache_zippy_nd":
			weaponName = "zippy_rockets_apache_nodamage";
			tags[ 0 ] = "tag_flash_2";
			tags[ 1 ] = "tag_flash_3";
			break;
		case "mi28_zippy":
			weaponName = "zippy_rockets_apache";
			tags[ 0 ] = "tag_store_L_wing";
			tags[ 1 ] = "tag_store_R_wing";
			break;
		case "mi28_zippy_cheap":
			weaponName = "zippy_rockets_apache_cheap";
			tags[ 0 ] = "tag_store_L_wing";
			tags[ 1 ] = "tag_store_R_wing";
			break;
		case "cobra_turret":
			weaponName = "hind_turret_penetration";
			tags[ 0 ] = "tag_store_L_wing";
			tags[ 1 ] = "tag_store_R_wing";
			break;
		case "ffar_hind":
			defaultWeapon = "hind_turret";
			weaponName = "hind_FFAR";
			tags[ 0 ] = "tag_missile_left";
			tags[ 1 ] = "tag_missile_right";
			break;
		case "hind_zippy":
			defaultWeapon = "hind_turret";
			weaponName = "zippy_rockets";
			tags[ 0 ] = "tag_missile_left";
			tags[ 1 ] = "tag_missile_right";
			break;
		case "hind_rpg":
			defaultWeapon = "hind_turret";
			weaponName = "rpg";
			tags[ 0 ] = "tag_missile_left";
			tags[ 1 ] = "tag_missile_right";
			break;
		case "hind_rpg_cheap":
			defaultWeapon = "hind_turret";
			weaponName = "rpg_cheap";
			tags[ 0 ] = "tag_missile_left";
			tags[ 1 ] = "tag_missile_right";
			break;
		case "ffar_hind_nodamage":
			defaultWeapon = "hind_turret";
			weaponName = "hind_FFAR_nodamage";
			tags[ 0 ] = "tag_missile_left";
			tags[ 1 ] = "tag_missile_right";
			break;
		case "ffar_mi28_village_assault":
			defaultWeapon = "hind_turret";
			weaponName = "mi28_ffar_village_assault";
			tags[ 0 ] = "tag_store_L_2_a";
			tags[ 1 ] = "tag_store_R_2_a";
			tags[ 2 ] = "tag_store_L_2_b";
			tags[ 3 ] = "tag_store_R_2_b";
			tags[ 4 ] = "tag_store_L_2_c";
			tags[ 5 ] = "tag_store_R_2_c";
			tags[ 6 ] = "tag_store_L_2_d";
			tags[ 7 ] = "tag_store_R_2_d";
			break;
		case "ffar_co_rescue":
			weaponName = "cobra_FFAR_bog_a_lite";
			tags[ 0 ] = "tag_store_R_2_a";
			tags[ 1 ] = "tag_store_L_2_a";
			break;
		default:
			assertMsg( "Invalid missile type specified." );
			break;
	}
	
	
	assert( isdefined( weaponName ) );
	assert( tags.size > 0 );

	weaponShootTime = weaponfiretime( weaponName );
	assert( isdefined( weaponShootTime ) );

	if ( IsDefined( self.nextMissileTag ) )
		nextMissileTag = self.nextMissileTag;
	else
		nextMissileTag = -1;
	
	
	for ( i = 0 ; i < iShots ; i++ )
	{
		nextMissileTag++;
		nextMissileTag %= tags.size;

		if ( sMissileType == "ffar_mi28_village_assault" )
		{
			if ( isdefined( eTarget ) && isdefined( eTarget.origin ) )
			{
				magicBullet( weaponName, self getTagOrigin( tags[ nextMissileTag ] ), eTarget.origin );
				if ( isdefined( level._effect[ "ffar_mi28_muzzleflash" ] ) )
					playfxontag( getfx( "ffar_mi28_muzzleflash" ), self, tags[ nextMissileTag ] );
				thread delayed_earthquake( 0.1, 0.5, 0.2, eTarget.origin, 1600 );
			}
		}
		else
		{
			self setVehWeapon( weaponName );
			if ( isdefined( eTarget ) )
			{
				eMissile = self fireWeapon( tags[ nextMissileTag ], eTarget );
				maps\_audio::aud_send_msg("missile_fired", emissile);
				
				switch( sMissileType )
				{
					case "ffar":
					case "ffar_bog_a_lite":
					case "ffar_airlift":
						eMissile thread missileLoseTarget( 0.1 );
						
						break;
					case "apache_zippy":
					case "apache_zippy_nd":
					case "apache_zippy_wall":
					case "mi28_zippy":
					case "mi28_zippy_cheap":
						if ( !IsDefined( target_los ) )
							eMissile thread missileLoseTarget( 0.6 );
						else
							eMissile thread missileLoseTarget( target_los );
						
						break;
					default:
						break;
				}
			}
			else
				eMissile = self fireWeapon( tags[ nextMissileTag ] );
				self notify( "missile_fired", eMissile );
		}
		self.nextMissileTag = nextMissileTag;

		if ( i < iShots - 1 )
			wait weaponShootTime;

		if ( isdefined( fDelay ) )
			wait( fDelay );
	}

	self setVehWeapon( defaultWeapon );
}

delayed_earthquake( fDelay, scale, duration, source, fRadius )
{
	wait fDelay;
	earthquake( scale, duration, source, fRadius );
}

missileLoseTarget( fDelay )
{
	self endon( "death" );
	wait fDelay;
	if ( isdefined( self ) )
		self Missile_ClearTarget();
}
