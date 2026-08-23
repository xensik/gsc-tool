#include common_scripts\utility;
#include common_scripts\_createfx;

initFX()
{
	if ( !isdefined( level.func ) )
	{
		// this array will be filled with code commands that SP or MP may use but doesn't exist in the other.
		level.func = [];
	}
	if( !isdefined( level.func[ "create_triggerfx" ] ) )
		 level.func[ "create_triggerfx" ] = ::create_triggerfx;
		 
	create_lock( "createfx_looper", 20 );

	// wrapper for the exploder function so we dont have to use flags and do ifs/waittills on every exploder call
	level.exploderFunction = ::exploder_before_load;
	waittillframeend;// Wait one frame so the effects get setup by the maps fx thread
	waittillframeend;// Wait another frame so effects can be loaded based on start functions. Without this FX are initialiazed before they are defined by start functions.
	level.exploderFunction = ::exploder_after_load;
	
	/# setDevDvarIfUninitialized( "scr_map_exploder_dump", 0 ); #/

	level.server_culled_sounds = 0;
	if ( GetDvarInt( "serverCulledSounds" ) == 1 )
		level.server_culled_sounds = 1;
	if ( level.createFX_enabled )
		level.server_culled_sounds = 0;
	/#
	if ( GetDvarInt( "r_reflectionProbeGenerate" ) == 1 )
		level.server_culled_sounds = 0;
	#/

	// Give createfx_common time to delete triggers to free up entity slots.
	if ( level.createFX_enabled )
	{
		level waittill( "createfx_common_done" );
	}
	
	// allow a delay so createfx sounds do not all play on the early frames
	if ( IsDefined( level.delay_createfx_seconds ) )
	{
		wait level.delay_createfx_seconds;
	}

	for ( i = 0; i < level.createFXent.size; i++ )
	{
		ent = level.createFXent[ i ];
		ent set_forward_and_up_vectors();

		if ( ent.v[ "type" ] == "loopfx" )
			ent thread loopfxthread();
		if ( ent.v[ "type" ] == "oneshotfx" )
			ent thread oneshotfxthread();
		if ( ent.v[ "type" ] == "soundfx" )
			ent thread create_loopsound();
		if ( ent.v[ "type" ] == "soundfx_interval" )
			ent thread create_interval_sound();
	}
}


print_org( fxcommand, fxId, fxPos, waittime )
{
	if ( GetDvar( "debug" ) == "1" )
	{
		println( "{" );
		println( "\"origin\" \"" + fxPos[ 0 ] + " " + fxPos[ 1 ] + " " + fxPos[ 2 ] + "\"" );
		println( "\"classname\" \"script_model\"" );
		println( "\"model\" \"fx\"" );
		println( "\"script_fxcommand\" \"" + fxcommand + "\"" );
		println( "\"script_fxid\" \"" + fxId + "\"" );
		println( "\"script_delay\" \"" + waittime + "\"" );
		println( "}" );
	}
}

OneShotfx( fxId, fxPos, waittime, fxPos2 )
{
//	level thread print_org ("OneShotfx", fxId, fxPos, waittime);
//    level thread OneShotfxthread (fxId, fxPos, waittime, fxPos2);
}

exploderfx( num, fxId, fxPos, waittime, fxPos2, fireFx, fireFxDelay, fireFxSound, fxSound, fxQuake, fxDamage, soundalias, repeat, delay_min, delay_max, damage_radius, fireFxTimeout, exploder_group )
{
	if ( 1 )
	{
		ent = createExploder( fxId );
		ent.v[ "origin" ] = fxPos;
		ent.v[ "angles" ] = ( 0, 0, 0 );
		if ( isdefined( fxPos2 ) )
			ent.v[ "angles" ] = vectortoangles( fxPos2 - fxPos );
		ent.v[ "delay" ] = waittime;
		ent.v[ "exploder" ] = num;
		if (isdefined(level.createFXexploders))
		{	// if we're using the optimized lookup, add it in the proper place
			ary = level.createFXexploders[ ent.v[ "exploder" ] ];
			if (!isdefined(ary))
				ary = [];
			ary[ary.size] = ent;
			level.createFXexploders[ ent.v[ "exploder" ] ] = ary;
		}
		// deprecated
		return;
	}
	fx = spawn( "script_origin", ( 0, 0, 0 ) );
//	println ("total ", getentarray ("script_origin","classname").size);
	fx.origin = fxPos;
	fx.angles = vectortoangles( fxPos2 - fxPos );
//	fx.targetname = "exploder";
	fx.script_exploder = num;
	fx.script_fxid = fxId;
	fx.script_delay = waittime;

	fx.script_firefx = fireFx;
	fx.script_firefxdelay = ( fireFxDelay );// for awhile the script exported strings for this value so we cast it to float
	fx.script_firefxsound = fireFxSound;

	fx.script_sound = fxSound;
	fx.script_earthquake = fxQuake;
	fx.script_damage = ( fxDamage );
	fx.script_radius = ( damage_radius );
	fx.script_soundalias = soundalias;
	fx.script_firefxtimeout = ( fireFxTimeout );
	fx.script_repeat = ( repeat );
	fx.script_delay_min = ( delay_min );
	fx.script_delay_max = ( delay_max );
	fx.script_exploder_group = exploder_group;

	forward = anglestoforward( fx.angles );
	forward  *= ( 150 );
	fx.targetPos = fxPos + forward;

	if ( !isdefined( level._script_exploders ) )
		level._script_exploders = [];
	level._script_exploders[ level._script_exploders.size ] = fx;

	createfx_showOrigin( fxid, fxPos, waittime, fxpos2, "exploderfx", fx, undefined, fireFx, fireFxDelay,
	fireFxSound, fxSound, fxQuake, fxDamage, soundalias, repeat, delay_min, delay_max, damage_radius, fireFxTimeout );
}


/*
loopfxRotate(fxId, fxPos, waittime, angle, fxStart, fxStop, timeout)
{
	level thread print_org ("loopfx", fxId, fxPos, waittime);
    level thread loopfxthread (fxId, fxPos, waittime, fxPos2, fxStart, fxStop, timeout);
}
*/


loopfx( fxId, fxPos, waittime, fxPos2, fxStart, fxStop, timeout )
{
	println( "Loopfx is deprecated!" );
	ent = createLoopEffect( fxId );
	ent.v[ "origin" ] = fxPos;
	ent.v[ "angles" ] = ( 0, 0, 0 );
	if ( isdefined( fxPos2 ) )
		ent.v[ "angles" ] = vectortoangles( fxPos2 - fxPos );
	ent.v[ "delay" ] = waittime;
}

/*
loopfx(fxId, fxPos, waittime, fxPos2, fxStart, fxStop, timeout)
{
	level thread print_org ("loopfx", fxId, fxPos, waittime);
    level thread loopfxthread (fxId, fxPos, waittime, fxPos2, fxStart, fxStop, timeout);
}
*/

create_looper()
{
	//assert (isdefined(self.looper));
	self.looper = playLoopedFx( level._effect[ self.v[ "fxid" ] ], self.v[ "delay" ], self.v[ "origin" ], 0, self.v[ "forward" ], self.v[ "up" ] );
	create_loopsound();
}

create_loopsound()
{
	self notify( "stop_loop" );
	if ( isdefined( self.v[ "soundalias" ] ) && ( self.v[ "soundalias" ] != "nil" ) )
	{
		if ( isdefined( self.v[ "stopable" ] ) && self.v[ "stopable" ] )
		{
			if ( isdefined( self.looper ) )
				self.looper thread loop_fx_sound( self.v[ "soundalias" ], self.v[ "origin" ], 0, "death" );
			else
				thread loop_fx_sound( self.v[ "soundalias" ], self.v[ "origin" ], 0, "stop_loop" );
		}
		else
		{
			if ( isdefined( self.looper ) )
				self.looper thread loop_fx_sound( self.v[ "soundalias" ], self.v[ "origin" ], 0 );
			else
			{
				culled = 0;

				if ( level.server_culled_sounds == 1 && isdefined( self.v[ "server_culled" ] ) )
				{
					culled = self.v[ "server_culled" ];
				}

				thread loop_fx_sound( self.v[ "soundalias" ], self.v[ "origin" ], culled );
			}
		}
	}
}

create_interval_sound()
{
	self notify( "stop_loop" );
	
	if ( !IsDefined( self.v[ "soundalias" ] ) )
		return;
	if ( self.v[ "soundalias" ] == "nil" )
		return;

	ender = undefined;
	runner = self;
	
	if( ( IsDefined( self.v[ "stopable" ] ) && self.v[ "stopable" ] ) || level.createFX_enabled )
	{
		if ( IsDefined( self.looper ) )
		{
			runner = self.looper;
			ender = "death";
		}
		else
			ender = "stop_loop";
		
	}
	runner thread loop_fx_sound_interval( self.v[ "soundalias" ], self.v[ "origin" ], ender, undefined, self.v[ "delay_min" ], self.v[ "delay_max" ] );
}

loopfxthread()
{
	waitframe();
//	println ( "fx testing running Id: ", fxId );
//    if ((isdefined (level.scr_sound)) && (isdefined (level.scr_sound[fxId])))
//	   loopSound(level.scr_sound[fxId], fxPos);

	if ( isdefined( self.fxStart ) )
		level waittill( "start fx" + self.fxStart );

	while ( 1 )
	{
		/*
		if (isdefined (ent.org2))
		{
			fxAngle = vectorNormalize (ent.org2 - ent.org);
			looper = playLoopedFx( level._effect[fxId], ent.delay, ent.org, 0, fxAngle );
		}
		else
			looper = playLoopedFx( level._effect[fxId], ent.delay, ent.org, 0 );
		*/
		create_looper();

		if ( isdefined( self.timeout ) )
			thread loopfxStop( self.timeout );

		if ( isdefined( self.fxStop ) )
			level waittill( "stop fx" + self.fxStop );
		else
			return;

		if ( isdefined( self.looper ) )
			self.looper delete();

		if ( isdefined( self.fxStart ) )
			level waittill( "start fx" + self.fxStart );
		else
			return;
	}
}

loopfxChangeID( ent )
{
	self endon( "death" );
	ent waittill( "effect id changed", change );
}

loopfxChangeOrg( ent )
{
	self endon( "death" );
	for ( ;; )
	{
		ent waittill( "effect org changed", change );
		self.origin = change;
	}
}

loopfxChangeDelay( ent )
{
	self endon( "death" );
	ent waittill( "effect delay changed", change );
}

loopfxDeletion( ent )
{
	self endon( "death" );
	ent waittill( "effect deleted" );
	self delete();
}

loopfxStop( timeout )
{
	self endon( "death" );
	wait( timeout );
	self.looper delete();
}

loopSound( sound, Pos, waittime )
{
//	level thread print_org ("loopSound", sound, Pos, waittime);
	level thread loopSoundthread( sound, Pos, waittime );
}

loopSoundthread( sound, pos, waittime )
{
	org = spawn( "script_origin", ( pos ) );

	org.origin = pos;
//	println ("hello1 ", org.origin, sound);
	org playLoopSound( sound );
}

gunfireloopfx( fxId, fxPos, shotsMin, shotsMax, shotdelayMin, shotdelayMax, betweenSetsMin, betweenSetsMax )
{
    thread gunfireloopfxthread( fxId, fxPos, shotsMin, shotsMax, shotdelayMin, shotdelayMax, betweenSetsMin, betweenSetsMax );
}

gunfireloopfxthread( fxId, fxPos, shotsMin, shotsMax, shotdelayMin, shotdelayMax, betweenSetsMin, betweenSetsMax )
{
	level endon( "stop all gunfireloopfx" );
	waitframe();

	if ( betweenSetsMax < betweenSetsMin )
	{
		temp = betweenSetsMax;
		betweenSetsMax = betweenSetsMin;
		betweenSetsMin = temp;
	}

	betweenSetsBase = betweenSetsMin;
	betweenSetsRange = betweenSetsMax - betweenSetsMin;

	if ( shotdelayMax < shotdelayMin )
	{
		temp = shotdelayMax;
		shotdelayMax = shotdelayMin;
		shotdelayMin = temp;
	}

	shotdelayBase = shotdelayMin;
	shotdelayRange = shotdelayMax - shotdelayMin;

	if ( shotsMax < shotsMin )
	{
		temp = shotsMax;
		shotsMax = shotsMin;
		shotsMin = temp;
	}

	shotsBase = shotsMin;
	shotsRange = shotsMax - shotsMin;

	fxEnt = spawnFx( level._effect[ fxId ], fxPos );
	
	if ( !level.createFX_enabled )
		fxEnt willNeverChange();
		
    for ( ;; )
    {
		shotnum = shotsBase + randomint( shotsRange );
		for ( i = 0;i < shotnum;i++ )
		{
			triggerFx( fxEnt );

			wait( shotdelayBase + randomfloat( shotdelayRange ) );
		}
        wait( betweenSetsBase + randomfloat( betweenSetsRange ) );
    }
}

gunfireloopfxVec( fxId, fxPos, fxPos2, shotsMin, shotsMax, shotdelayMin, shotdelayMax, betweenSetsMin, betweenSetsMax )
{
    thread gunfireloopfxVecthread( fxId, fxPos, fxPos2, shotsMin, shotsMax, shotdelayMin, shotdelayMax, betweenSetsMin, betweenSetsMax );
}

gunfireloopfxVecthread( fxId, fxPos, fxPos2, shotsMin, shotsMax, shotdelayMin, shotdelayMax, betweenSetsMin, betweenSetsMax )
{
	level endon( "stop all gunfireloopfx" );
	waitframe();

	if ( betweenSetsMax < betweenSetsMin )
	{
		temp = betweenSetsMax;
		betweenSetsMax = betweenSetsMin;
		betweenSetsMin = temp;
	}

	betweenSetsBase = betweenSetsMin;
	betweenSetsRange = betweenSetsMax - betweenSetsMin;

	if ( shotdelayMax < shotdelayMin )
	{
		temp = shotdelayMax;
		shotdelayMax = shotdelayMin;
		shotdelayMin = temp;
	}

	shotdelayBase = shotdelayMin;
	shotdelayRange = shotdelayMax - shotdelayMin;

	if ( shotsMax < shotsMin )
	{
		temp = shotsMax;
		shotsMax = shotsMin;
		shotsMin = temp;
	}

	shotsBase = shotsMin;
	shotsRange = shotsMax - shotsMin;

	fxPos2 = vectornormalize( fxPos2 - fxPos );

	fxEnt = spawnFx( level._effect[ fxId ], fxPos, fxPos2 );

	if ( !level.createFX_enabled )
		fxEnt willNeverChange();

	for ( ;; )
	{
		shotnum = shotsBase + randomint( shotsRange );
		for ( i = 0;i < int( shotnum / level.fxfireloopmod );i++ )
		{
			triggerFx( fxEnt );
			delay = ( ( shotdelayBase + randomfloat( shotdelayRange ) ) * level.fxfireloopmod );
			if ( delay < .05 )
				delay = .05;
			wait delay;
		}
		wait( shotdelayBase + randomfloat( shotdelayRange ) );
		wait( betweenSetsBase + randomfloat( betweenSetsRange ) );
	}
}

setfireloopmod( value )
{
	level.fxfireloopmod = 1 / value;
}

setup_fx()
{
	if ( ( !isdefined( self.script_fxid ) ) || ( !isdefined( self.script_fxcommand ) ) || ( !isdefined( self.script_delay ) ) )
	{
//		println (self.script_fxid);
//		println (self.script_fxcommand);
//		println (self.script_delay);
//		println ("Effect at origin ", self.origin," doesn't have script_fxid/script_fxcommand/script_delay");
//		self delete();
		return;
	}

//	println ("^a Command:", self.script_fxcommand, " Effect:", self.script_fxID, " Delay:", self.script_delay, " ", self.origin);
	if ( isdefined( self.model ) )
		if ( self.model == "toilet" )
		{
			self thread burnville_paratrooper_hack();
			return;
		}

	org = undefined;
	if ( isdefined( self.target ) )
	{
		ent = getent( self.target, "targetname" );
		if ( isdefined( ent ) )
			org = ent.origin;
	}

	fxStart = undefined;
	if ( isdefined( self.script_fxstart ) )
		fxStart = self.script_fxstart;

	fxStop = undefined;
	if ( isdefined( self.script_fxstop ) )
		fxStop = self.script_fxstop;

	if ( self.script_fxcommand == "OneShotfx" )
		OneShotfx( self.script_fxId, self.origin, self.script_delay, org );
	if ( self.script_fxcommand == "loopfx" )
		loopfx( self.script_fxId, self.origin, self.script_delay, org, fxStart, fxStop );
	if ( self.script_fxcommand == "loopsound" )
		loopsound( self.script_fxId, self.origin, self.script_delay );

	self delete();
}

burnville_paratrooper_hack()
{
	normal = ( 0, 0, self.angles[ 1 ] );
//	println ("z:       paratrooper fx hack: ", normal);
	id = level._effect[ self.script_fxId ];
	origin = self.origin;

//	if (isdefined (self.script_delay))
//		wait (self.script_delay);

	wait 1;
	level thread burnville_paratrooper_hack_loop( normal, origin, id );
	self delete();
}

burnville_paratrooper_hack_loop( normal, origin, id )
{
	while ( 1 )
	{
	//	iprintln ("z:        playing paratrooper fx", origin);

		playfx( id, origin );
		wait( 30 + randomfloat( 40 ) );
	}
}

create_triggerfx()
{
	//assert (isdefined(self.looper));
	if( ! verify_effects_assignment( self.v[ "fxid" ] ) )
		return;
		
	self.looper = spawnFx( level._effect[ self.v[ "fxid" ] ], self.v[ "origin" ], self.v[ "forward" ], self.v[ "up" ] );
	triggerFx( self.looper, self.v[ "delay" ] );

	if ( !level.createFX_enabled )
		self.looper willNeverChange();

	create_loopsound();
}

verify_effects_assignment( effectID )
{
	if( isdefined ( level._effect[ effectID ] ) )
		return true;
	if( ! isdefined( level._missing_FX ) )
		level._missing_FX = [];
	level._missing_FX[ self.v[ "fxid" ] ] = effectID;
	verify_effects_assignment_print( effectID );
	return false;
}

verify_effects_assignment_print( effectID )
{
	
	level notify ( "verify_effects_assignment_print" );
	level endon ( "verify_effects_assignment_print" );
	wait .05; //allow errors on the same frame to que up before printing
	
	println("Error:");
	println("Error:**********MISSING EFFECTS IDS**********");
	keys = getarraykeys( level._missing_FX );
	foreach( key in keys )
	{
		println( "Error: Missing Effects ID assignment for: "+ key  );
	}
	println("Error:");
	
	assertmsg( "Missing Effects ID assignments ( see console )" );
}

OneShotfxthread()
{
	waitframe();

	if ( self.v[ "delay" ] > 0 )
	    wait self.v[ "delay" ];

	/*  
	if ( isdefined( self.v[ "fire_range" ] ) )
	{
		thread fire_radius( self.v[ "origin" ], self.v[ "fire_range" ] );
	}
	*/

	[[ level.func[ "create_triggerfx" ] ]]();
}