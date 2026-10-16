#include maps\_utility;
#include common_scripts\utility;

main()
{
	leaks = getentarray( "leaking", "targetname" );
	if ( !leaks.size )
		return;

	leaks thread precacheFX();
	leaks thread methodsInit();

	array_thread( leaks, ::leak_setup );
}

leak_setup()
{
	switch( self.script_noteworthy )
	{
		case "barrel_oil":{
			self leak_barrel_setup();
			}break;
		case "barrel_acid":{
			self leak_barrel_setup();
			}break;
		case "barrel_sludge":{
			self leak_barrel_setup();
			}break;
		case "barrel_water":{
			self leak_barrel_setup();
			}break;
	}
	self thread	leak_think();
}

leak_barrel_setup()
{
	self.A = self.origin;
	self.up = anglestoup( self.angles );
	worldup = anglestoup( ( 0, 90, 0 ) );

	self.org = self.A + ( self.up * 22 );
	self.A = self.A + ( self.up * 1.5 );
	self.B = self.A + ( self.up * 41.4 );
	self.volume = ( 3.1416 * ( 14 * 14 ) * 42 );// pi * ( r squared ) * height
	self.curvol = self.volume;

	dot = vectordot( self.up, worldup );
	top = self.B;
	if ( dot < 0 )
		top = self.A;

	dot = abs( 1 - abs( dot ) );

	self.lowZ = ( physicstrace( ( self.org ), ( self.org + ( 0, 0, -80 ) ) ) )[ 2 ];
	self.highZ = top[ 2 ] + ( dot * 14 );
}

leak_think()
{
	self setcandamage( true );

	self endon( "drained" );

	while ( 1 )
	{
		self waittill( "damage", damage, other, direction_vec, P, type );
		if ( type == "MOD_MELEE" || type == "MOD_IMPACT" )
			continue;

		P = self [[ level._leak_methods[ type ] ]]( P, type );

		if ( !isdefined( P ) )
			continue;

		self thread leak_drain( P );
	}
}

leak_drain( P )
{
	Q = pointOnSegmentNearestToPoint( self.A, self.B, P );
	vec = undefined;

	if ( Q == self.A )
		vec = ( self.up * -1 );
	else if ( Q == self.B )
		vec = self.up;
	else
		vec = vectorFromLineToPoint( self.A, self.B, P );

	depth = P[ 2 ] - self.lowZ;
	if ( depth < .02 )
		depth = 0;

	ratio = ( depth / ( self.highZ - self.lowZ ) ) * self.volume;

	if ( self.curvol > ratio )
	{
		while ( self.curvol > ratio )
		{
			playfx( level._effect[ "leak_interactive_leak" ][ self.script_noteworthy ], P, vec );
			self.curvol -= 100;
			wait .1;
		}
		playfx( level._effect[ "leak_interactive_drain" ][ self.script_noteworthy ], P, vec );
	}
	if ( ( self.curvol / self.volume ) <= .05 )
		self notify( "drained" );
}

methodsInit()
{
	level._leak_methods = [];
	level._leak_methods[ "MOD_UNKNOWN" ] 				 = ::leak_calc_splash;
	level._leak_methods[ "MOD_PISTOL_BULLET" ] 		 = ::leak_calc_ballistic;
	level._leak_methods[ "MOD_RIFLE_BULLET" ] 		 = ::leak_calc_ballistic;
	level._leak_methods[ "MOD_GRENADE" ] 				 = ::leak_calc_splash;
	level._leak_methods[ "MOD_GRENADE_SPLASH" ] 		 = ::leak_calc_splash;
	level._leak_methods[ "MOD_PROJECTILE" ] 			 = ::leak_calc_splash;
	level._leak_methods[ "MOD_PROJECTILE_SPLASH" ] 	 = ::leak_calc_splash;
	level._leak_methods[ "MOD_MELEE" ] 				 = ::leak_calc_nofx;
	level._leak_methods[ "MOD_HEAD_SHOT" ] 			 = ::leak_calc_nofx;
	level._leak_methods[ "MOD_CRUSH" ] 				 = ::leak_calc_nofx;
	level._leak_methods[ "MOD_TELEFRAG" ] 			 = ::leak_calc_nofx;
	level._leak_methods[ "MOD_FALLING" ] 				 = ::leak_calc_nofx;
	level._leak_methods[ "MOD_SUICIDE" ] 				 = ::leak_calc_nofx;
	level._leak_methods[ "MOD_TRIGGER_HURT" ] 		 = ::leak_calc_splash;
	level._leak_methods[ "MOD_EXPLOSIVE" ] 			 = ::leak_calc_splash;
	level._leak_methods[ "MOD_IMPACT" ] 				 = ::leak_calc_nofx;
}

leak_calc_ballistic( P, type )
{
	return P;
}

leak_calc_splash( P, type )
{
	vec = vectornormalize( vectorFromLineToPoint( self.A, self.B, P ) );
	P = pointOnSegmentNearestToPoint( self.A, self.B, P );
	return( P + ( vec * 4 ) );
	//return P;
}

leak_calc_nofx( P, type )
{
	return undefined;
}

leak_calc_assert( P, type )
{
	assertMsg( "BUG to MOHAMMAD ALAVI under LEVEL DESIGN. leaking object at (" + self getorigin() + ") was impacted with unknown type: " + type + "." );
}

precacheFX()
{
	for ( i = 0; i < self.size; i++ )
	{
		if ( self[ i ].script_noteworthy != "barrel_oil" )
			continue;

		level._effect[ "leak_interactive_leak" ][ self[ i ].script_noteworthy ]		 = loadfx( "impacts/barrel_leak" );
		level._effect[ "leak_interactive_drain" ][ self[ i ].script_noteworthy ]		 = loadfx( "impacts/barrel_drain" );
		//level._sound["leak_interactive"][self[i].script_noteworthy] 		= "mtl_steam_pipe_hit";
		//level.pipe_fx_time[self[i].script_noteworthy]			= 5;

		break;
	}
	for ( i = 0; i < self.size; i++ )
	{
		if ( self[ i ].script_noteworthy != "barrel_acid" )
			continue;
		level._effect[ "leak_interactive_leak" ][ self[ i ].script_noteworthy ]		 = loadfx( "impacts/barrel_leak" );
		level._effect[ "leak_interactive_drain" ][ self[ i ].script_noteworthy ]		 = loadfx( "impacts/barrel_drain" );
		break;
	}
	for ( i = 0; i < self.size; i++ )
	{
		if ( self[ i ].script_noteworthy != "barrel_water" )
			continue;
		level._effect[ "leak_interactive_leak" ][ self[ i ].script_noteworthy ]		 = loadfx( "impacts/barrel_leak" );
		level._effect[ "leak_interactive_drain" ][ self[ i ].script_noteworthy ]		 = loadfx( "impacts/barrel_drain" );
		break;
	}
	for ( i = 0; i < self.size; i++ )
	{
		if ( self[ i ].script_noteworthy != "barrel_sludge" )
			continue;
		level._effect[ "leak_interactive_leak" ][ self[ i ].script_noteworthy ]		 = loadfx( "impacts/barrel_leak" );
		level._effect[ "leak_interactive_drain" ][ self[ i ].script_noteworthy ]		 = loadfx( "impacts/barrel_drain" );
		break;
	}
}