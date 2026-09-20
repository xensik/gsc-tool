#include maps\_utility;
#include common_scripts\utility;

blizzard_main()
{
	level.sandstormSpawnrate = 0.1;
	blizzard_flags();
	fx_init();
	blizzard_level_set( "none" );
	thread blizzard_start();
	
	level.global_ambience_blend_func = ::blizzard_ice_overlay_blend;

}

blizzard_flags()
{
	flag_init( "pause_blizzard_ground_fx" );
}

blizzard_start()
{
	if ( !isdefined( level.players ) )
		level waittill( "level.players initialized" );

	array_thread( level.players, ::blizzard_start_proc );
	//array_thread( level.players, ::blizzard_start_screen_proc );
	thread pause_blizzard_ground_fx();
}


blizzard_start_screen_proc()
{
	screen_tag = self spawn_tag_origin();
	screenEffect = false;
	while(1)
	{
		// Need to add coop version
		if (!is_coop() && level.snowLevel == 6)
		{
			if (!screenEffect )
			{
				screenEffect = true;
				PlayFXOnTag(level._effect["particle_fog2"],screen_tag,"tag_origin");
			}
			playerAngles = self GetPlayerAngles();
			screen_tag.origin = self.origin;
			screen_tag.angles = playerAngles;
		}
		else
		{
			if (screenEffect )
			{
				StopFXOnTag(level._effect["particle_fog2"],screen_tag,"tag_origin");
				screenEffect = false;
			}
		}
		wait(.05);
	}
}
blizzard_start_proc()
{
	
	while ( 1 )
	{
		if ( is_coop() )
			PlayFXOnTagForClients( level._effect[ "blizzard_main" ], self, "tag_origin", self );
		else
			playfx( level._effect[ "blizzard_main" ], (self groundpos(self.origin)+(0,0,86)) );
		wait(level.sandstormSpawnrate);
	}
}
set_sandstorm_spawnrate(rate)
{
	if (!IsDefined(rate))
	{
		switch(level.snowLevel)
		{
		case 0:
			level.sandstormSpawnrate = .3;
			//lerp_sandstorm_spawnrate(0.3);
			break;
		case 1:
			level.sandstormSpawnrate = .08;
			//lerp_sandstorm_spawnrate(0.08);
			break;
		case 2:
			level.sandstormSpawnrate = .17;
			//lerp_sandstorm_spawnrate(0.3);
			break;
		case 3:
			level.sandstormSpawnrate = .3;
			//(0.3);
			break;
		case 4:
			level.sandstormSpawnrate = .24;
			//lerp_sandstorm_spawnrate(0.07,.11);
			break;
		case 5:
			level.sandstormSpawnrate = .14;
			//lerp_sandstorm_spawnrate(0.07,.11);
			break;
		case 6:
			level.sandstormSpawnrate = .07;
			//lerp_sandstorm_spawnrate(0.07,.11);
			break;
		}
	}
	else
	{
		level.sandstormSpawnrate = rate;
	}
}
lerp_sandstorm_spawnrate(rate,transitionSpeed)
{
	if (!IsDefined(transitionSpeed))
	{
		transitionSpeed = .05;	
	}
	if (rate > level.sandstormSpawnrate)
	{
		while(rate > level.sandstormSpawnrate)
		{
			wait(level.sandstormSpawnrate);
			newRate = level.sandstormSpawnrate+transitionSpeed;
			level.sandstormSpawnrate = min(newRate,rate);
		}
	}	
	else
	{
		while(rate < level.sandstormSpawnrate)
		{
			wait(level.sandstormSpawnrate);
			newRate = level.sandstormSpawnrate-transitionSpeed;
			level.sandstormSpawnrate = max(newRate,rate);
		}
	}
}
fx_init()
{
	setsaveddvar( "r_outdoorfeather", "32" ); //helps keep blizzard close to the ground while allowing outdoor only particles to work (Doesn't work on overhangs). -RoBoTg

	level._effect[ "blizzard_level_0" ]	 = loadfx( "misc/blank" );
	level._effect[ "blizzard_level_1" ]	 = loadfx( "sand/sand_light" );
	level._effect[ "blizzard_level_2" ]	 = loadfx( "sand/sand_medium_2" );
	level._effect[ "blizzard_level_3" ]	 = loadfx( "sand/sand_medium_2" );
	level._effect[ "blizzard_level_4" ]	 = loadfx( "sand/sand_medium_2" );
	level._effect[ "blizzard_level_5" ]	 = loadfx( "sand/sand_extreme" );
	level._effect[ "blizzard_level_6" ]	 = loadfx( "sand/sand_extreme" );
	level._effect[ "blizzard_level_7" ]  = loadfx( "sand/sand_aftermath" );

	sun_array = GetMapSunLight();
	level.default_sun = ( sun_array[0], sun_array[1], sun_array[2] );
	level.sun_intensity = 1.0;
	level.blizzard_overlay_alpha = 0;
}

blizzard_level_set( type )
{
	level.snowLevel = blizzard_level_get_count( type );

	blizzard_set_fx();
}


/*
=============
///ScriptDocBegin
"Name: blizzard_level_transition_none( <time> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blizzard_level_transition_none( time )
{
	blizzard_set();
	thread blizzard_level_transition( "none", time );
	//setExpFog( 6552, 25874, level.fog_color[ "r" ], level.fog_color[ "g" ], level.fog_color[ "b" ], 1, time );
	maps\_utility::vision_set_fog_changes( "payback", time );
	thread blizzard_set_culldist( 0, 0 );
	thread blizzard_set_shadowquality( 0, 1.0 );
	SetHalfResParticles( false );
	flag_set( "pause_blizzard_ground_fx" );
	blizzard_overlay_alpha( time, 0 );
	resetsunlight();
}


/*
=============
///ScriptDocBegin
"Name: blizzard_no_fog( <time> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blizzard_no_fog( time )
{
	blizzard_set();
	thread blizzard_level_transition( "none", time );
	//setExpFog( 100, 27955, level.fog_color[ "r" ], level.fog_color[ "g" ], level.fog_color[ "b" ], .57, time );
	maps\_utility::vision_set_fog_changes( "payback", time );
	thread blizzard_set_culldist( 0, 0 );
	thread blizzard_set_shadowquality( 0, 1.0 );
	SetHalfResParticles( false );
	flag_set( "pause_blizzard_ground_fx" );
	blizzard_overlay_alpha( time, 0.25 );
	resetsunlight();
}


/*
=============
///ScriptDocBegin
"Name: blizzard_level_transition_light( <time> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blizzard_level_transition_light( time )
{
	//iprintln("SANDSTORM: LIGHT (payback)");
	blizzard_set();
	thread blizzard_level_transition( "light", time );
	//setExpFog( 2000, 10000, level.fog_color[ "r" ], level.fog_color[ "g" ], level.fog_color[ "b" ], .47, time );
	maps\_utility::vision_set_fog_changes( "payback", time );
	thread blizzard_set_culldist( 0, 0 );
	thread blizzard_set_shadowquality( 0, 1.0 );
	SetHalfResParticles( false );
	flag_set( "pause_blizzard_ground_fx" );
	blizzard_overlay_alpha( time, 0.45 );
	thread blizzard_set_sunlight( 1.0, time );
/*
	intensity = .555;
	thread blizzard_set_sunlight( intensity, time );
*/
}

/*
=============
///ScriptDocBegin
"Name: blizzard_level_transition_med( <time> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blizzard_level_transition_med( time )
{
	//iprintln("SANDSTORM: MEDIUM (payback_medium)");
	blizzard_set();
	thread blizzard_level_transition( "med", time );
//	setExpFog( 0, 500, level.fog_color[ "r" ], level.fog_color[ "g" ], level.fog_color[ "b" ], .8, time );
	maps\_utility::vision_set_fog_changes( "payback_medium", time );
	thread blizzard_set_culldist( time, 4500 );
	thread blizzard_set_shadowquality( time, 0.5 );
	SetHalfResParticles( false );
	flag_set( "pause_blizzard_ground_fx" );
	blizzard_overlay_alpha( time, 0.5 );
/*
	intensity = .16;
	thread blizzard_set_sunlight( intensity, time );
*/
}

/*
=============
///ScriptDocBegin
"Name: blizzard_level_transition_hard( <time> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blizzard_level_transition_hard( time )
{
	//iprintln("SANDSTORM: HEAVY (payback_heavy)");
	blizzard_set();
	thread blizzard_level_transition( "hard", time );
	//setExpFog( 470, 500, level.fog_color[ "r" ], level.fog_color[ "g" ], level.fog_color[ "b" ], 1, time );
	maps\_utility::vision_set_fog_changes( "payback_heavy", time );

	intensity = 1;
	thread blizzard_set_sunlight( intensity, time );
	thread blizzard_set_culldist( time, 0 );
	thread blizzard_set_shadowquality( time, 0 );
	SetHalfResParticles( false );

	//flag_clear( "pause_blizzard_ground_fx" );
	
	blizzard_overlay_alpha( time, 0.7 );
}

blizzard_level_transition_extreme( time,disable_fog )
{
	//iprintln("SANDSTORM: EXTREME (payback_heavy)");
	blizzard_set();
	thread blizzard_level_transition( "extreme", time );
	//setExpFog( 470, 500, level.fog_color[ "r" ], level.fog_color[ "g" ], level.fog_color[ "b" ], 1, time );


	intensity = 1;
	thread blizzard_set_sunlight( intensity, time );
	thread blizzard_set_culldist( time, 0 );
	thread blizzard_set_shadowquality( time, 0 );
	SetHalfResParticles( false );

	//flag_clear( "pause_blizzard_ground_fx" );
	
	blizzard_overlay_alpha( time, 0.7 );
	
	if (!IsDefined(disable_fog))
	{
		thread blizzard_level_transition_extreme_fog(time,0.05);
	}
}


blizzard_level_transition_extreme_fog_novision(time,delay)
{
	wait(delay);
	maps\_utility::vision_set_fog_changes( "payback_heavy_fogonly", time);	
}

blizzard_level_transition_extreme_fog(time,delay)
{
	if (IsDefined(delay))
	{
		wait(delay);
	}
	wait(delay);
	maps\_utility::vision_set_fog_changes( "payback_heavy", time);	
}
blizzard_level_transition_extreme_sat(time,delay)
{
	if (IsDefined(delay))
	{
		wait(delay);
	}
	maps\_utility::vision_set_fog_changes( "payback_heavy_sat", time);
}
blizzard_level_transition_extreme2(time,delay)
{
	if (IsDefined(delay))
	{
		wait(delay);
	}
	vision_set_changes("payback_heavy_75",time);
}

blizzard_level_transition_blackout( time )
{
	//iprintln("SANDSTORM: BLACKOUT (payback_blackout)");
	blizzard_set();
	thread blizzard_level_transition( "extreme", time );
	//setExpFog( 470, 500, level.fog_color[ "r" ], level.fog_color[ "g" ], level.fog_color[ "b" ], 1, time );
	maps\_utility::vision_set_fog_changes( "payback_blackout", time );

	intensity = 1;
	thread blizzard_set_sunlight( intensity, time );
	thread blizzard_set_culldist( time, 0 );
	thread blizzard_set_shadowquality( time, 0 );
	SetHalfResParticles( false );

	//flag_clear( "pause_blizzard_ground_fx" );
	
	blizzard_overlay_alpha( time, 0.7 );
}

blizzard_level_transition_aftermath( time )
{
	//iprintln("SANDSTORM: AFTERMATH (payback_heavy)");
	blizzard_set();
	thread blizzard_level_transition( "aftermath", time );
	//setExpFog( 470, 500, level.fog_color[ "r" ], level.fog_color[ "g" ], level.fog_color[ "b" ], 1, time );
	maps\_utility::vision_set_fog_changes( "payback_heavy", time );

	intensity = 1;
	thread blizzard_set_sunlight( intensity, time );
	thread blizzard_set_culldist( time, 0 );
	thread blizzard_set_shadowquality( time, 0.5 );
	SetHalfResParticles( false );

	//flag_clear( "pause_blizzard_ground_fx" );
	
	blizzard_overlay_alpha( time, 0.7 );
}

blizzard_set_culldist( time, to )
{
	level notify( "blizzard_set_culldist" );
	level endon( "blizzard_set_culldist" );
	// 0 means infinite so we need to use a really far value to represent that
	// Then swap with infinite when the transition is complete
	max_cull = 10000;
	
	from = level.blizzard_culldist;
	if ( !IsDefined( from ) || from == 0 )
	{
		from = max_cull;
	}
	
	if ( to == 0 )
	{
		to = max_cull;
	}

	trans_time = 0;
	startTime = (time * 0.5);
	while ( trans_time <= time )
	{
		if ( time > 0 )
		{
			// Do transition twice as fast, but dont start until half way through the transition
			// (Gives the sandstorm FX a chance to built up a bit before the far clip comes in)
			if ( trans_time >= startTime )
			{
				coef = (trans_time - startTime) / (time - startTime);
				level.blizzard_culldist = from + ((to - from) * coef);
			}
			else
			{
				level.blizzard_culldist = from;
			}
		}
		else
		{
			level.blizzard_culldist = to;
		}
		trans_time += blizzard_set_culldist_checked( level.blizzard_culldist );
	}
	
	// When at max cull, set to 0 which is infinite
	if ( to >= max_cull || to == 0 )
	{
		level.blizzard_culldist = 0;
		blizzard_set_culldist_checked( 0 );
	}
	else
	{
		// Have to keep checking in case the player leaves the area where culling is valid
		for(;;)
		{
			level.blizzard_culldist = to;
			blizzard_set_culldist_checked( to );
		}
	}
}

blizzard_set_culldist_checked( cull_dist )
{
	level notify( "blizzard_set_culldist_checked" );
	level endon( "blizzard_set_culldist" );
	level endon( "blizzard_set_culldist_checked" );
	
	cull_allowed = false;
	time_waited = 0;
	
	if ( !IsDefined( level.trig_enable_sandstorm_cull ) )
	{
		level.trig_enable_sandstorm_cull = GetEntArray("trig_enable_sandstorm_cull", "targetname");
	}
	
	// Player must be standing in a targetname:trig_enable_sandstorm_cull but not looking toward its avoid target spot
	while ( !cull_allowed )
	{
		if ( cull_dist == 0 )
		{
			// cull_dist == 0 means we are just setting to defualt which is always allowed
			cull_allowed = true;
		}
		else
		{
			// Always check the one they were last touching first
			if ( IsDefined( level.player.trig_enable_sandstorm_cull ) && level.player IsTouching( level.player.trig_enable_sandstorm_cull ) )
			{
				cull_allowed = blizzard_culldist_check_trigger( level.player.trig_enable_sandstorm_cull );
			}
			else
			{
				// Then check the others once no longer touching the last one
				foreach ( trig in level.trig_enable_sandstorm_cull )
				{
					if ( (!IsDefined( level.player.trig_enable_sandstorm_cull ) || trig != level.player.trig_enable_sandstorm_cull)
						    && level.player IsTouching( trig ) )
					{
						cull_allowed = blizzard_culldist_check_trigger( trig );
						level.player.trig_enable_sandstorm_cull = trig;
						break;
					}
				}
			}
			
			if ( !cull_allowed )
			{
				SetCullDist( 0 );
				//iprintlnBold( "CullDist: 0" );
			}
		}
				
		time_waited += 0.05;
		wait 0.05;
	}
	
	SetCullDist( cull_dist );
	//iprintlnBold( "CullDist: " + cull_dist );
	
	return time_waited;
}

blizzard_culldist_check_trigger( trig )
{
	cull_allowed = false;
	if ( IsDefined( trig.target ) )
	{
		avoid_look_at = getstruct(trig.target, "targetname");
		if ( IsDefined( avoid_look_at ) )
		{
			lookingDir = AnglesToForward( level.player GetPlayerAngles() );
			avoidDir = VectorNormalize( avoid_look_at.origin - level.player.origin );
			if ( VectorDot( lookingDir, avoidDir ) < 0.6 )
			{
				cull_allowed = true;
			}
		}
	}
	else
	{
		cull_allowed = true;
	}
	return cull_allowed;
}

blizzard_set_shadowquality( time, to )
{
	self notify( "blizzard_set_shadowquality" );
	self endon( "blizzard_set_shadowquality" );

	from = level.blizzard_shadowquality;
	if ( !IsDefined( from ) )
	{
		from = 1.0;
	}
	
	shadow_scale = 1;
	shadow_size_near = 0.25;

	trans_time = 0;
	while ( trans_time <= time )
	{
		if ( time > 0 )
		{
			coef = trans_time / time;
			level.blizzard_shadowquality = from + ((to - from) * coef);
		}
		else
		{
			level.blizzard_shadowquality = to;
		}
		
		shadow_scale = 0.25 + (level.blizzard_shadowquality * 0.75); 	// 0.25 to 1.00 (default)
		shadow_size_near = 0.1 + (level.blizzard_shadowquality * 0.15); // 0.10 to 0.25 (default)
				
		wait 0.05;

		// Slowly transitioning makes the shadows look all squirmy, instead take steps every second		
		if ( int( trans_time ) != int( trans_time + 0.05 ) )
		{
			SetSavedDvar( "sm_sunShadowScale", shadow_scale );
			SetSavedDvar( "sm_sunSampleSizeNear", shadow_size_near );
		}
		
		trans_time += 0.05;
	}

	SetSavedDvar( "sm_sunShadowScale", shadow_scale );
	SetSavedDvar( "sm_sunSampleSizeNear", shadow_size_near );
}


blizzard_set_sunlight( intensity, time )
{
	level notify( "blizzard_set_sunlight" );
	level endon( "blizzard_set_sunlight" );
		 
	interval = int( time * 20 );
	
	diff = intensity - level.sun_intensity;
	fraction = diff / interval;
	
	while( interval )
	{
		level.sun_intensity += fraction;
		new_sun = ( level.default_sun * level.sun_intensity );
			
		setsunlight( new_sun[ 0 ], new_sun[ 1 ], new_sun[ 2 ] );
		interval--;
		
		wait .05;
	}
	
	level.sun_intensity = intensity;
//	iprintlnbold( "Sun Intensity =" + intensity );
	new_sun = ( level.default_sun * level.sun_intensity );
			
	setsunlight( new_sun[ 0 ], new_sun[ 1 ], new_sun[ 2 ] );
}

blizzard_level_transition( type, time )
{
	level notify( "blizzard_level_change" );
	level endon( "blizzard_level_change" );

	newlevel = blizzard_level_get_count( type );
	if ( level.snowLevel > newlevel )
	{
		interval = level.snowLevel - newlevel;
		time /= interval;

		for ( i = 0; i < interval; i++ )
		{
			wait( time );
			level.snowLevel -- ;
			blizzard_set_fx();
		}
		assert( level.snowLevel == newlevel );
	}
	if ( level.snowLevel < newlevel )
	{
		interval = newlevel - level.snowLevel;
		time /= interval;

		for ( i = 0; i < interval; i++ )
		{
			wait( time );
			level.snowLevel++ ;
			blizzard_set_fx();
		}
		assert( level.snowLevel == newlevel );
	}
}

blizzard_set_fx()
{
	level._effect[ "blizzard_main" ] = level._effect[ "blizzard_level_" + level.snowLevel ];
	thread set_sandstorm_spawnrate();
}

blizzard_level_get_count( type )
{
	switch( type )
	{
		case "none":
			return 0;
		case "light":
			return 1;
		case "med":
			return 3;
		case "hard":
			return 5;
		case "extreme":
			return 6;
		case "aftermath":
			return 7;
	}
}

/*
=============
///ScriptDocBegin
"Name: blizzard_overlay_alpha( <time> , <alpha>, <skipCap> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blizzard_overlay_alpha( time, alpha, skipCap )
{
	player = self;
	if ( !isplayer( player ) )
		player = level.player;
	
	if( !isdefined( alpha ) )
		alpha = 1;
	
	// skipcap lets us modify the overlay without setting a new cap
	if ( !isdefined( skipCap ) )
		level.blizzard_overlay_alpha_cap = alpha;
	
	// r_fog_depthhack_scale - pull back on the heavy fog for in-view weapon geo while sandstorm is active
	if ( alpha > 0 )
	{
		SetSavedDvar("r_fog_depthhack_scale", "0.5");
	}
	else
	{
		SetSavedDvar("r_fog_depthhack_scale", "-1");
	}	
	
	overlay = get_frozen_overlay( player );
	overlay.x = 0;
	overlay.y = 0;
	overlay setshader( "overlay_sandstorm", 640, 480 );
	overlay.sort = 50;
	overlay.lowresbackground = true;
	overlay.alignX = "left";
	overlay.alignY = "top";
	overlay.horzAlign = "fullscreen";
	overlay.vertAlign = "fullscreen";
	overlay.alpha = level.blizzard_overlay_alpha;
	overlay fadeovertime( time );
	overlay.alpha = alpha; // should be 1 but the image is black
	
	level.blizzard_overlay_alpha = alpha;
}

/*
=============
///ScriptDocBegin
"Name: blizzard_overlay_clear( <timer> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blizzard_overlay_clear( timer )
{
	if ( !isdefined( timer ) || !timer )
	{
		player = self;
		if ( !isplayer( player ) )
			player = level.player;
		overlay = get_frozen_overlay( player );
		overlay destroy();
		return;
	}
	
	blizzard_overlay_alpha( timer, 0 );
}


get_frozen_overlay( player )
{
	if ( !isdefined( player.overlay_frozen ) )
		player.overlay_frozen = newClientHudElem( player );

	return player.overlay_frozen;	
}

pause_blizzard_ground_fx()
{
	fx = [];
	//fx = getfxarraybyID( "lighthaze_snow" );
	//fx = array_combine( fx, getfxarraybyID( "lighthaze_snow_headlights" ));
	//fx = array_combine( fx, getfxarraybyID( "snow_spray_detail_runner400x400" ));
	//fx = array_combine( fx, getfxarraybyID( "snow_spray_detail_runner0x400" ));
	//fx = array_combine( fx, getfxarraybyID( "snow_spray_detail_runner400x0" ));

	wait( 0.1 ); // must wait until fx are started	
	for ( ;; )
	{
		flag_wait( "pause_blizzard_ground_fx" );
		//iprintlnbold( "Stop Ground FX" );
		foreach ( oneshot in fx )
			oneshot pauseEffect();
		flag_waitopen( "pause_blizzard_ground_fx" );
		foreach ( oneshot in fx )
			oneshot restartEffect();
	}
}

blizzard_set()
{
	// added this common function so its easier to debug blizzard changes
	level notify( "blizzard_changed" );
	level notify( "blizzard_set_sunlight" );
}

blizzard_ice_overlay_blend( progress, inner, outer )
{
	cap = level.blizzard_overlay_alpha_cap;
	if ( !isdefined( cap ) )
		cap = 1;
	// find the exterior 
	if ( issubstr( inner, "exterior" ) )
	{
		blizzard_overlay_alpha( 1, ( 1 - progress ) * cap, true );
		return;
	}
	if ( issubstr( outer, "exterior" ) )
	{
		blizzard_overlay_alpha( 1, progress * cap, true );
	}
}
