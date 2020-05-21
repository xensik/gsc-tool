#include maps\mp\_utility;
#include common_scripts\utility;


init()
{
	level._effect[ "emp_flash" ] = loadfx( "explosions/emp_flash_mp" );

	level.teamEMPed["allies"] = false;
	level.teamEMPed["axis"] = false;
	level.empPlayer = undefined;
	level.empTimeout = 60.0;
	level.empTimeRemaining = int( level.empTimeout );

	if ( level.teamBased )
		level thread EMP_TeamTracker();
	else
		level thread EMP_PlayerTracker();
	
	level.killstreakFuncs["emp"] = ::EMP_Use;
	
	level thread onPlayerConnect();
	
/#
	SetDevDvarIfUninitialized( "scr_emp_timeout", 60.0 );
	SetDevDvarIfUninitialized( "scr_emp_damage_debug", 0 );
#/
}



onPlayerConnect()
{
	for(;;)
	{
		level waittill("connected", player);
		player thread onPlayerSpawned();
	}
}


onPlayerSpawned()
{
	self endon("disconnect");

	for(;;)
	{
		self waittill( "spawned_player" );
		
		if ( (level.teamBased && level.teamEMPed[self.team]) || (!level.teamBased && isDefined( level.empPlayer ) && level.empPlayer != self) )
			self setEMPJammed( true );
	}
}


EMP_Use( lifeId )
{
	assert( isDefined( self ) );

	if ( ! self validateUseStreak() )
		return false;
	
	myTeam = self.pers["team"];
	otherTeam = level.otherTeam[myTeam];
	
	if ( level.teamBased )
		self thread EMP_JamTeam( otherTeam );
	else
		self thread EMP_JamPlayers( self );

	self maps\mp\_matchdata::logKillstreakEvent( "emp", self.origin );
	self notify( "used_emp" );

	return true;
}


EMP_JamTeam( teamName )
{
	level endon ( "game_ended" );
	
	assert( teamName == "allies" || teamName == "axis" );

	thread teamPlayerCardSplash( "used_emp", self );

	level notify ( "EMP_JamTeam" + teamName );
	level endon ( "EMP_JamTeam" + teamName );
	
	foreach ( player in level.players )
	{
		player playLocalSound( "emp_activate" );
		
		if ( player.team != teamName )
			continue;
		
		if ( player _hasPerk( "specialty_localjammer" ) )
			player RadarJamOff();
	}
	
	VisionSetNaked( "coup_sunblind", 0.1 );
	thread empEffects();
	
	wait ( 0.1 );
	
	// resetting the vision set to the same thing won't normally have an effect.
	// however, if the client receives the previous visionset change in the same packet as this one,
	// this will force them to lerp from the bright one to the normal one.
	VisionSetNaked( "coup_sunblind", 0 );
	if( IsDefined( level.nukeDetonated ) )
		VisionSetNaked( level.nukeVisionSet, 3.0 );
	else
		VisionSetNaked( "", 3.0 ); // go to default visionset
	
	level.teamEMPed[teamName] = true;
	level notify ( "emp_update" );
	
	level destroyActiveVehicles( self, teamName );
	
/#
	level.empTimeout = GetDvarFloat( "scr_emp_timeout" );
#/
	level thread keepEMPTimeRemaining();
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( level.empTimeout );
	
	level.teamEMPed[teamName] = false;
	
	foreach ( player in level.players )
	{
		if ( player.team != teamName )
			continue;
		
		if ( player _hasPerk( "specialty_localjammer" ) )
			player RadarJamOn();
	}
	
	level notify ( "emp_update" );
}

EMP_JamPlayers( owner )
{
	level notify ( "EMP_JamPlayers" );
	level endon ( "EMP_JamPlayers" );
	
	assert( isDefined( owner ) );
		
	foreach ( player in level.players )
	{
		player playLocalSound( "emp_activate" );
		
		if ( player == owner )
			continue;
		
		if ( player _hasPerk( "specialty_localjammer" ) )
			player RadarJamOff();
	}
	
	VisionSetNaked( "coup_sunblind", 0.1 );
	thread empEffects();

	wait ( 0.1 );
	
	// resetting the vision set to the same thing won't normally have an effect.
	// however, if the client receives the previous visionset change in the same packet as this one,
	// this will force them to lerp from the bright one to the normal one.
	VisionSetNaked( "coup_sunblind", 0 );
	if( IsDefined( level.nukeDetonated ) )
		VisionSetNaked( level.nukeVisionSet, 3.0 );
	else
		VisionSetNaked( "", 3.0 ); // go to default visionset
	
	level notify ( "emp_update" );
	
	level.empPlayer = owner;
	level.empPlayer thread empPlayerFFADisconnect();
	level destroyActiveVehicles( owner );
	
	level notify ( "emp_update" );
	
/#
	level.empTimeout = GetDvarFloat( "scr_emp_timeout" );
#/
	level thread keepEMPTimeRemaining();
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( level.empTimeout );
	
	foreach ( player in level.players )
	{
		if ( player == owner )
			continue;
		
		if ( player _hasPerk( "specialty_localjammer" ) )
			player RadarJamOn();
	}
	
	level.empPlayer = undefined;
	level notify ( "emp_update" );
	level notify ( "emp_ended" );
}

keepEMPTimeRemaining()
{
	level notify( "keepEMPTimeRemaining" );
	level endon( "keepEMPTimeRemaining" );

	level endon( "emp_ended" );

	// we need to know how much time is left for the unavailable string
	level.empTimeRemaining = int( level.empTimeout );
	while( level.empTimeRemaining )
	{
		wait( 1.0 );
		level.empTimeRemaining--;
	}
}

empPlayerFFADisconnect()
{
	level endon ( "EMP_JamPlayers" );	
	level endon ( "emp_ended" );
	
	self waittill( "disconnect" );
	level notify ( "emp_update" );
}

empEffects()
{
	foreach( player in level.players )
	{
		playerForward = anglestoforward( player.angles );
		playerForward = ( playerForward[0], playerForward[1], 0 );
		playerForward = VectorNormalize( playerForward );
	
		empDistance = 20000;

		empEnt = Spawn( "script_model", player.origin + ( 0, 0, 8000 ) + ( playerForward * empDistance ) );
		empEnt setModel( "tag_origin" );
		empEnt.angles = empEnt.angles + ( 270, 0, 0 );
		empEnt thread empEffect( player );
	}
}

empEffect( player )
{
	player endon( "disconnect" );

	wait( 0.5 );
	PlayFXOnTagForClients( level._effect[ "emp_flash" ], self, "tag_origin", player );
}

EMP_TeamTracker()
{
	level endon ( "game_ended" );
	
	for ( ;; )
	{
		level waittill_either ( "joined_team", "emp_update" );
		
		foreach ( player in level.players )
		{
			if ( player.team == "spectator" )
				continue;
				
			player setEMPJammed( level.teamEMPed[player.team] );
		}
	}
}


EMP_PlayerTracker()
{
	level endon ( "game_ended" );
	
	for ( ;; )
	{
		level waittill_either ( "joined_team", "emp_update" );
		
		foreach ( player in level.players )
		{
			if ( player.team == "spectator" )
				continue;
				
			if ( isDefined( level.empPlayer ) && level.empPlayer != player )
				player setEMPJammed( true );
			else
				player setEMPJammed( false );				
		}
	}
}

destroyActiveVehicles( attacker, teamEMPed )
{
	// making variables out of these values so we can change them here, once
	//heli_radius = 384;
	//lb_radius = 384;
	//turret_radius = 16;
	//uav_radius = 384;
	//ac130_radius = 1000;
	//ims_radius = 16;
	//ugv_radius = 16;

	//ac130_offset = ( 0, 0, 10 );
	//ims_offset = ( 0, 0, 10 );
	//ugv_offset = ( 0, 0, 10 );

	meansOfDeath = "MOD_EXPLOSIVE";
	weapon = "killstreak_emp_mp";

	damage = 5000;
	direction_vec = ( 0, 0, 0 );
	point = ( 0, 0, 0 );
	modelName = "";
	tagName = "";
	partName = "";
	iDFlags = undefined;

	if ( level.teamBased && IsDefined( teamEMPed ) )
	{
		foreach ( heli in level.helis )
		{
			if( IsDefined( heli.team ) && heli.team != teamEMPed )
				continue;

			heli notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}

		foreach ( lb in level.littleBirds )
		{
			if( IsDefined( lb.team ) && lb.team != teamEMPed )
				continue;

			lb notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}

		foreach ( turret in level.turrets )
		{
			if( IsDefined( turret.team ) && turret.team != teamEMPed )
				continue;

			turret notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}

		foreach ( rocket in level.rockets )
		{
			if( IsDefined( rocket.team ) && rocket.team != teamEMPed )
				continue;

			PlayFX( level.remotemissile_fx[ "explode" ], rocket.origin );
			rocket delete();
		}

		foreach ( uav in level.uavModels[ teamEMPed ] )
		{
			uav notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}

		if ( IsDefined( level.ac130player ) && IsDefined( level.ac130player.team ) && level.ac130player.team == teamEMPed )
			level.ac130.planeModel notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );

		foreach ( ims in level.ims )
		{
			if( IsDefined( ims.team ) && ims.team != teamEMPed )
				continue;

			ims notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}

		foreach ( ugv in level.ugvs )
		{
			if( IsDefined( ugv.team ) && ugv.team != teamEMPed )
				continue;

			ugv notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
/#
			//if( GetDvarInt( "scr_emp_damage_debug" ) )				
			//	level thread drawEMPDamageOrigin( ugv.origin + ugv_offset, ugv.angles, ugv_radius );
#/
		}
	}
	else
	{	
		foreach ( heli in level.helis )
		{
			if( IsDefined( heli.owner ) && heli.owner == attacker )
				continue;

			heli notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}

		foreach ( lb in level.littleBirds )
		{
			if( IsDefined( lb.owner ) && lb.owner == attacker )
				continue;

			lb notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}

		foreach ( turret in level.turrets )
		{
			if( IsDefined( turret.owner ) && turret.owner == attacker )
				continue;

			turret notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}

		foreach ( rocket in level.rockets )
		{
			if( IsDefined( rocket.owner ) && rocket.owner == attacker )
				continue;

			PlayFX( level.remotemissile_fx[ "explode" ], rocket.origin );
			rocket delete();
		}

		foreach ( uav in level.uavModels )
		{
			if( IsDefined( uav.owner ) && uav.owner == attacker )
				continue;

			uav notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}

		if ( IsDefined( level.ac130player ) )
		{
			if( !IsDefined( level.ac130.owner ) || ( IsDefined( level.ac130.owner ) && level.ac130.owner != attacker ) )
				level.ac130.planeModel notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}

		foreach ( ims in level.ims )
		{
			if( IsDefined( ims.owner ) && ims.owner == attacker )
				continue;

			ims notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}

		foreach ( ugv in level.ugvs )
		{
			if( IsDefined( ugv.owner ) && ugv.owner == attacker )
				continue;

			ugv notify( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );
		}
	}
}

/#
drawEMPDamageOrigin( pos, ang, radius )
{
	while( GetDvarInt( "scr_emp_damage_debug" ) )
	{
		Line( pos, pos + ( AnglesToForward( ang ) * radius ), ( 1, 0, 0 ) );
		Line( pos, pos + ( AnglesToRight( ang ) * radius ), ( 0, 1, 0 ) );
		Line( pos, pos + ( AnglesToUp( ang ) * radius ), ( 0, 0, 1 ) );

		Line( pos, pos - ( AnglesToForward( ang ) * radius ), ( 1, 0, 0 ) );
		Line( pos, pos - ( AnglesToRight( ang ) * radius ), ( 0, 1, 0 ) );
		Line( pos, pos - ( AnglesToUp( ang ) * radius ), ( 0, 0, 1 ) );

		wait( 0.05 );
	}
}
#/