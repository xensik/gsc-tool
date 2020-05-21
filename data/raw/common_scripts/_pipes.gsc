#include common_scripts\utility;

//////////////////////////////////////////////////////////////////////////////
//									CONSTANTS								//
//////////////////////////////////////////////////////////////////////////////
level_limit_pipe_fx = 8;
max_fires_from_entity = 4;
level_pipe_fx_chance = 33;


//////////////////////////////////////////////////////////////////////////////
//									LOGIC									//
//////////////////////////////////////////////////////////////////////////////
main()
{
	level._pipe_fx_time = 25;
	pipes = GetEntArray( "pipe_shootable", "targetname" );
	if ( !pipes.size )
		return;
	level._pipes = SpawnStruct();
	level._pipes.num_pipe_fx	 = 0;

	pipes thread precacheFX();
	pipes thread methodsInit();

	waittillframeend;// insure that structs are initialized
	array_thread( pipes, ::pipesetup );
}

pipesetup()
{
	self SetCanDamage( true );
	self SetCanRadiusDamage( false ); // optimization
	self.pipe_fx_array = [];

	node = undefined;

	if ( IsDefined( self.target ) )
	{
		node = getstruct( self.target, "targetname" );
		self.A = node.origin;
		vec = AnglesToForward( node.angles );
		vec = ( vec * 128 );
		self.B = self.A + vec;
	}
	else
	{
		vec = AnglesToForward( self.angles );
		vec1 = ( vec * 64 );
		self.A = self.origin + vec1;
		vec1 = ( vec * -64 );
		self.B = self.origin + vec1;
	}

	self thread pipe_wait_loop();
}

pipe_wait_loop()
{
	P = ( 0, 0, 0 );// just to initialize P as a vector
	
	hasTakenDamage = false;
	remaining = max_fires_from_entity;
	
	while ( 1 )
	{
		self waittill( "damage", damage, other, direction_vec, P, type );
		
		// random so we don't get so many fx, but the very first time is guarenteed
		if ( hasTakenDamage )
		{
			if ( randomint( 100 ) <= level_pipe_fx_chance )
				continue;
		}
		hasTakenDamage = true;
		
		result = self pipe_logic( direction_vec, P, type, other );
		if ( result )
			remaining--;
		
		if ( remaining <= 0 )
			break;
	}
	
	self SetCanDamage( false );
}

pipe_logic( direction_vec, P, type, damageOwner )
{
	if ( level._pipes.num_pipe_fx > level_limit_pipe_fx )
		return false;

	if ( !isDefined( level._pipes._pipe_methods[ type ] ) )
		P = self pipe_calc_nofx( P, type );
	else
	P = self [[ level._pipes._pipe_methods[ type ] ]]( P, type );

	if ( !isdefined( P ) )
		return false;

	if ( IsDefined( damageOwner.classname ) && damageOwner.classname == "worldspawn" )
		return false;

	foreach ( value in self.pipe_fx_array )
	{
		if ( DistanceSquared( P, value.origin ) < 25 )
			return false;
	}

	//calculate the vector derived from the center line of our pipe and the point of damage
	vec = VectorFromLineToPoint( self.A, self.B, P );
	self thread pipefx( P, vec, damageOwner );
	return true;
}

pipefx( P, vec, damageOwner )
{
	time 		 = level._pipes.fx_time[ self.script_noteworthy ] ;
	intervals 	 = Int( level._pipe_fx_time / time );// loops for 25 seconds
	hitsnd 		 = level._pipes._sound[ self.script_noteworthy + "_hit" ];
	loopsnd 	 = level._pipes._sound[ self.script_noteworthy + "_loop" ];
	endsnd 		 = level._pipes._sound[ self.script_noteworthy + "_end" ];

	snd = Spawn( "script_origin", P );
	snd Hide();
	snd PlaySound( hitsnd );
	snd PlayLoopSound( loopsnd );
	self.pipe_fx_array[ self.pipe_fx_array.size ] = snd;

	level._pipes.num_pipe_fx++;

		if ( isSP() || self.script_noteworthy != "steam" )
			self thread pipe_damage( P, vec, damageOwner, snd );

		//do it once without checking for newer fx being played ( we're the newest )
		PlayFX( level._pipes._effect[ self.script_noteworthy ], P, vec );
		wait time;
		intervals--;

		//now check	for other fx and rest of intervals
		while ( level._pipes.num_pipe_fx <= level_limit_pipe_fx && intervals > 0 )
		{
			PlayFX( level._pipes._effect[ self.script_noteworthy ], P, vec );
			wait time;
			intervals--;
		}
		snd PlaySound( endsnd );
		wait( .5 );
		snd StopLoopSound( loopsnd );
		snd Delete();
		self.pipe_fx_array = array_removeUndefined( self.pipe_fx_array );

	level._pipes.num_pipe_fx--;
}

pipe_damage( P, vec, damageOwner, fx )
{
	if ( !allow_pipe_damage() )
		return;
		
	fx endon( "death" );

	origin = fx.origin + ( VectorNormalize( vec ) * 40 );
	dmg = level._pipes._dmg[ self.script_noteworthy ];

	while ( 1 )
	{
		// do not pass damage owner if they have disconnected before the barrels explode.. the barrels?
		if ( !isdefined( self.damageOwner ) )
		{
			// MOD_TRIGGER_HURT so they dont do dirt on the player's screen
			self RadiusDamage( origin, 36, dmg, dmg * 0.75, undefined, "MOD_TRIGGER_HURT" );
		}
		else
		{
			// MOD_TRIGGER_HURT so they dont do dirt on the player's screen
			self RadiusDamage( origin, 36, dmg, dmg * 0.75, damageOwner, "MOD_TRIGGER_HURT" );
		}

		wait( 0.4 );
	}
}

allow_pipe_damage()
{
	if( !isSP() )
		return false;
	
	if ( !isDefined( level.pipesDamage ) )
		return true;
	
	return ( level.pipesDamage );
}

//////////////////////////////////////////////////////////////////////////////
//							CALCULATIONS / SETUP							//
//////////////////////////////////////////////////////////////////////////////

methodsInit()
{
	level._pipes._pipe_methods = [];
	level._pipes._pipe_methods[ "MOD_UNKNOWN" ] 				 = ::pipe_calc_splash;
	level._pipes._pipe_methods[ "MOD_PISTOL_BULLET" ] 		 = ::pipe_calc_ballistic;
	level._pipes._pipe_methods[ "MOD_RIFLE_BULLET" ] 			 = ::pipe_calc_ballistic;
	level._pipes._pipe_methods[ "MOD_GRENADE" ] 				 = ::pipe_calc_splash;
	level._pipes._pipe_methods[ "MOD_GRENADE_SPLASH" ] 		 = ::pipe_calc_splash;
	level._pipes._pipe_methods[ "MOD_PROJECTILE" ] 			 = ::pipe_calc_splash;
	level._pipes._pipe_methods[ "MOD_PROJECTILE_SPLASH" ] 	 = ::pipe_calc_splash;
	level._pipes._pipe_methods[ "MOD_TRIGGER_HURT" ] 			 = ::pipe_calc_splash;
	level._pipes._pipe_methods[ "MOD_EXPLOSIVE" ] 			 = ::pipe_calc_splash;
	level._pipes._pipe_methods[ "MOD_EXPLOSIVE_BULLET" ] 	 = ::pipe_calc_splash;
}

pipe_calc_ballistic( P, type )
{
	return P;
}

pipe_calc_splash( P, type )
{
	vec = VectorNormalize( VectorFromLineToPoint( self.A, self.B, P ) );
	P = PointOnSegmentNearestToPoint( self.A, self.B, P );
	return( P + ( vec * 4 ) );
}

pipe_calc_nofx( P, type )
{
	return undefined;
}

precacheFX()
{
	steam = false;
	fire = false;
	foreach ( value in self )
	{
		if ( value.script_noteworthy == "water" )
			value.script_noteworthy = "steam";

		if ( value.script_noteworthy == "steam" )
		{
			value willNeverChange();
			steam = true;
		}
		else if ( value.script_noteworthy == "fire" )
		{
			value willNeverChange();
			fire = true;
		}
		else
		{
			println( "Unknown 'pipe_shootable' script_noteworthy type '%s'\n", value.script_noteworthy );
		}
	}

	if ( steam )
	{
		level._pipes._effect[ "steam" ]		 = LoadFX( "impacts/pipe_steam" );
		level._pipes._sound[ "steam_hit" ] 	 = "mtl_steam_pipe_hit";
		level._pipes._sound[ "steam_loop" ] = "mtl_steam_pipe_hiss_loop";
		level._pipes._sound[ "steam_end" ] = "mtl_steam_pipe_hiss_loop_end";
		level._pipes.fx_time[ "steam" ]		 = 3;
		level._pipes._dmg[ "steam" ]		 = 5;
	}

	if ( fire )
	{
		level._pipes._effect[ "fire" ]		 = LoadFX( "impacts/pipe_fire" );
		level._pipes._sound[ "fire_hit" ]	 = "mtl_gas_pipe_hit";
		level._pipes._sound[ "fire_loop" ]	 = "mtl_gas_pipe_flame_loop";
		level._pipes._sound[ "fire_end" ]	 = "mtl_gas_pipe_flame_end";
		level._pipes.fx_time[ "fire" ]		 = 3;
		level._pipes._dmg[ "fire" ]			 = 5;
	}
}



