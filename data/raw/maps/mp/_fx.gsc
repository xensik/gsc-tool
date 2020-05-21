#include common_scripts\utility;
#include common_scripts\_fx;
#include common_scripts\_createfx;
#include maps\mp\_utility;
#include maps\mp\_createfx;

/*
	****************************************************************************************************************
	OneShotfx: Fires an effect once.
	maps\mp\_fx::OneShotfx( effectname, (x y z), predelay);

	Example:
	maps\mp\_fx::OneShotfx(level.medFire,		// Medium fire effect
					(-701, -18361, 148),	// Origin
					5);						// Wait 5 seconds before doing effect
	****************************************************************************************************************


	****************************************************************************************************************
	Loopfx: Loops an effect with a waittime.
	maps\mp\_fx::loopfx( effectname, (x y z), delay_between_shots);

	Example:
	maps\mp\_fx::loopfx(level.medFire,			// Medium fire effect
					(-701, -18361, 148),	// Origin
					0.3);					// Wait 0.3 seconds between shots
	****************************************************************************************************************


	****************************************************************************************************************
	GunFireLoopfx: Simulates bursts of fire.
	maps\mp\_fx::gunfireloopfx(fxId, fxPos, shotsMin, shotsMax, shotdelayMin, shotdelayMax, betweenSetsMin, betweenSetsMax)

	Example:
	maps\mp\_fx::gunfireloopfx (level.medFire,			// Medium fire effect
							(-701, -18361, 148),	// Origin
							10, 15,					// 10 to 15 shots
							0.1, 0.3,				// 0.1 to 0.3 seconds between shots
							2.5, 9);				// 2.5 to 9 seconds between sets of shots.
	****************************************************************************************************************

	****************************************************************************************************************
	GrenadeExplosionfx: Creates a grenade explosion with view jitter.
	maps\mp\_fx::GrenadeExplosionfx((x y z));

	Example:
	maps\mp\_fx::GrenadeExplosionfx( (-701, -18361, 148) ); // origin
	****************************************************************************************************************
*/

script_print_fx()
{
	if ( ( !isdefined( self.script_fxid ) ) || ( !isdefined( self.script_fxcommand ) ) || ( !isdefined( self.script_delay ) ) )
	{
		println( "Effect at origin ", self.origin, " doesn't have script_fxid/script_fxcommand/script_delay" );
		self delete();
		return;
	}

	if ( isdefined( self.target ) )
		org = getent( self.target ).origin;
	else
		org = "undefined";

//	println ("^a Command:", self.script_fxcommand, " Effect:", self.script_fxID, " Delay:", self.script_delay, " ", self.origin);
	if ( self.script_fxcommand == "OneShotfx" )
		println( "maps\mp\_fx::OneShotfx(\"" + self.script_fxid + "\", " + self.origin + ", " + self.script_delay + ", " + org + ");" );

	if ( self.script_fxcommand == "loopfx" )
		println( "maps\mp\_fx::LoopFx(\"" + self.script_fxid + "\", " + self.origin + ", " + self.script_delay + ", " + org + ");" );

	if ( self.script_fxcommand == "loopsound" )
		println( "maps\mp\_fx::LoopSound(\"" + self.script_fxid + "\", " + self.origin + ", " + self.script_delay + ", " + org + ");" );
}

script_playfx( id, pos, pos2 )
{
	if ( !id )
		return;

	if ( isdefined( pos2 ) )
		playfx( id, pos, pos2 );
	else
		playfx( id, pos );
}

script_playfxontag( id, ent, tag )
{
	if ( !id )
		return;

	playfxontag( id, ent, tag );
}

GrenadeExplosionfx( pos )
{
	playfx( level._effect[ "mechanical explosion" ], pos );
	earthquake( 0.15, 0.5, pos, 250 );
	// TODO: Add explosion effect and view jitter
//	println("The script command grenadeExplosionEffect has been removed. maps\\mp\\_fx::GrenadeExplosionfx must be set up to make an effect and jitter the view.");
}


soundfx( fxId, fxPos, endonNotify )
{
	org = spawn( "script_origin", ( 0, 0, 0 ) );
	org.origin = fxPos;
	org playloopsound( fxId );
	if ( isdefined( endonNotify ) )
		org thread soundfxDelete( endonNotify );

	/*
	ent = level thread createfx_showOrigin ( fxId, fxPos, undefined, undefined, "soundfx" );
	ent.delay = 0;
	ent endon ("effect deleted");
	ent.soundfx = org;
	*/
}

soundfxDelete( endonNotify )
{
	level waittill( endonNotify );
	self delete();
}


/*rainfx( fxId, fxId2, fxPos )
{
	org = spawn( "script_origin", ( 0, 0, 0 ) );
	org.origin = fxPos;
	org thread rainLoop( fxId, fxId2 );
	
	//ent = level thread createfx_showOrigin( fxId, fxPos, undefined, undefined, "rainfx", undefined, fxId2 );
	//ent.delay = 0;
	//ent endon ("effect deleted");
	//ent.soundfx = org;
}

rainLoop( hardRain, lightRain )
{
//	org playloopsound (fxId);
	self endon( "death" );
	blend = spawn( "sound_blend", ( 0.0, 0.0, 0.0 ) );
	blend.origin = self.origin;
	self thread blendDelete( blend );
	
	blend2 = spawn( "sound_blend", ( 0.0, 0.0, 0.0 ) );
	blend2.origin = self.origin;
	self thread blendDelete( blend2 );
	

// lerp of 0 will play _null only
	blend setSoundBlend( lightRain + "_null", lightRain, 0 );
	blend2 setSoundBlend( hardRain + "_null", hardRain, 1 );
	rain = "hard";
	blendTime = undefined;
	for ( ;; )
	{
		level waittill( "rain_change", change, blendTime );
		blendTime *= 15;// internal framerate
		assert( change == "hard" || change == "light" || change == "none" );
		assert( blendtime > 0 );
		
		if ( change == "hard" )
		{
			if ( rain == "none" )
			{
				blendTime *= 0.5;// gotta do 2 blends to go from none to hard
				for ( i = 0;i < blendtime;i++ )
				{
					blend setSoundBlend( lightRain + "_null", lightRain, i / blendtime );
					wait( 0.05 );
				}
				rain = "light";
			}
			if ( rain == "light" )
			{
				for ( i = 0;i < blendtime;i++ )
				{
					blend setSoundBlend( lightRain + "_null", lightRain, 1 - ( i / blendtime ) );
					blend2 setSoundBlend( hardRain + "_null", hardRain, i / blendtime );
					wait( 0.05 );
				}
			}
		}
		if ( change == "none" )
		{
			if ( rain == "hard" )
			{
				blendTime *= 0.5;// gotta do 2 blends to go from hard to none
				for ( i = 0;i < blendtime;i++ )
				{
					blend setSoundBlend( lightRain + "_null", lightRain, ( i / blendtime ) );
					blend2 setSoundBlend( hardRain + "_null", hardRain, 1 - ( i / blendtime ) );
					wait( 0.05 );
				}
				rain = "light";
			}
			if ( rain == "light" )
			{
				for ( i = 0;i < blendtime;i++ )
				{
					blend setSoundBlend( lightRain + "_null", lightRain, 1 - ( i / blendtime ) );
					wait( 0.05 );
				}
			}
		}
		if ( change == "light" )
		{
			if ( rain == "none" )
			{
				for ( i = 0;i < blendtime;i++ )
				{
					blend setSoundBlend( lightRain + "_null", lightRain, i / blendtime );
					wait( 0.05 );
				}
			}
			if ( rain == "hard" )
			{
				for ( i = 0;i < blendtime;i++ )
				{
					blend setSoundBlend( lightRain + "_null", lightRain, i / blendtime );
					blend2 setSoundBlend( hardRain + "_null", hardRain, 1 - ( i / blendtime ) );
					wait( 0.05 );
				}
			}
		}

		rain = change;
	}
}*/

blendDelete( blend )
{
	self waittill( "death" );
	blend delete();
}