#include maps\_utility;
#include common_scripts\utility;
#include common_scripts\_fx;
#include maps\_anim;
#include maps\_vehicle;
#include maps\_hud_util;
#include maps\_shg_common;
#include maps\castle_anim;
#include animscripts\shared;
#include maps\_stealth_utility;

#using_animtree( "generic_human" );

N_LIGHTNING_INTENSITY = 3.0;

setup_price_for_start( str_start, func_init_price, b_fake )
{
	if ( !IsDefined( b_fake ) )
	{
		b_fake = false;
	}
	
	setup_price( func_init_price, b_fake );
	
	if ( IsDefined( str_start ) )
	{
		str_targetname = str_start + "_price";
		
		s_price = getstruct( str_targetname, "targetname" );		
		if ( !IsDefined( s_price ) )
		{
			s_price = GetVehicleNode( str_targetname, "targetname" );
			level.price.target = str_targetname;
			
			AssertEx( IsDefined( s_price ), "No struct for Price to start at." );
		}
		else
		{
			if ( b_fake )
			{
				level.price.origin = s_price.origin;
				level.price.angles = s_price.angles;
			}
			else
			{
				level.price ForceTeleport( s_price.origin, s_price.angles );
			}
		}		
		
		if ( !b_fake )
		{
			level.price SetGoalPos( s_price.origin );
		}
	}	
}

setup_price( func_init_price, b_fake )
{
	if ( !IsDefined( b_fake ) )
	{
		b_fake = false;
	}
	
	if ( !b_fake )
	{
		if ( !IsAlive( level.price ) )
		{
			sp_price = GetEnt( "price", "targetname" );
			level.price = sp_price spawn_ai( true );
		
			AssertEx( IsAlive( level.price ), "Failed to spawn price!" );
		
			level.price thread magic_bullet_shield();
		}
	}
	else if ( !IsDefined( level.price ) )
	{
		level.price = Spawn( "script_model", ( 0, 0, 0 ) );
		//level.price character\character_sp_sas_woodland_price::main();
		level.price setModel("body_price_europe_assault_a");
		level.price.voice = "british";
		level.price UseAnimTree( #animtree );
	}
	
	level.price.animname = "price";
	
	level.n_price_attitude = 0;	// This value represents Price's feelings about your performance

	if ( IsDefined( func_init_price ) )
	{
		level.price thread [[ func_init_price ]]();
	}
}

stealth_settings()
{
	ai_event[ "ai_eventDistDeath" ] 		 = [];
	ai_event[ "ai_eventDistPain" ] 			 = [];
	ai_event[ "ai_eventDistExplosion" ] 	 = [];
	ai_event[ "ai_eventDistBullet" ] 		 = [];
	ai_event[ "ai_eventDistFootstep" ] 		 = [];
	ai_event[ "ai_eventDistFootstepWalk" ] 	 = [];
	ai_event[ "ai_eventDistFootstepSprint" ] = [];
	ai_event[ "ai_eventDistGunShot" ] 		 = [];
//	ai_event[ "ai_eventDistGunShotTeam" ]	 = [];
	ai_event[ "ai_eventDistNewEnemy" ] 		 = [];

	ai_event[ "ai_eventDistDeath" ][ "spotted" ]			= 1000;
	ai_event[ "ai_eventDistDeath" ][ "hidden" ]				= 400;

	ai_event[ "ai_eventDistPain" ][ "spotted" ]				= 400;
	ai_event[ "ai_eventDistPain" ][ "hidden" ]				= 250;

	ai_event[ "ai_eventDistExplosion" ][ "spotted" ]		= 6000;
	ai_event[ "ai_eventDistExplosion" ][ "hidden" ]			= 5000;

	ai_event[ "ai_eventDistBullet" ][ "spotted" ]			= 400;
	ai_event[ "ai_eventDistBullet" ][ "hidden" ]			= 100;

	ai_event[ "ai_eventDistFootstep" ][ "spotted" ]			= 150;
	ai_event[ "ai_eventDistFootstep" ][ "hidden" ]			= 100;

	ai_event[ "ai_eventDistFootstepWalk" ][ "spotted" ]		= 125;
	ai_event[ "ai_eventDistFootstepWalk" ][ "hidden" ]		= 100;
	
	ai_event[ "ai_eventDistFootstepSprint" ][ "spotted" ]	= 400;
	ai_event[ "ai_eventDistFootstepSprint" ][ "hidden" ]	= 150;
	
	ai_event[ "ai_eventDistGunShot" ][ "spotted" ]			= 1500;
	ai_event[ "ai_eventDistGunShot" ][ "hidden" ]			= 1000;

//	I don't have different groups so I don't think I need this
//	ai_event[ "ai_eventDistGunShotTeam" ][ "spotted" ]		= 750;
//	ai_event[ "ai_eventDistGunShotTeam" ][ "hidden" ]		= 750;
	
	ai_event[ "ai_eventDistNewEnemy" ][ "spotted" ]			= 600;
	ai_event[ "ai_eventDistNewEnemy" ][ "hidden" ]			= 300;
	
	stealth_ai_event_dist_custom( ai_event );
	
	rangesHidden[ "prone" ]		= 250;
	rangesHidden[ "crouch" ]	= 400;
	rangesHidden[ "stand" ]		= 450;

	rangesSpotted[ "prone" ]	= 400;
	rangesSpotted[ "crouch" ]	= 600;
	rangesSpotted[ "stand" ]	= 900;
	
	stealth_detect_ranges_set( rangesHidden, rangesSpotted );

	array[ "player_dist" ]	 = 0;
	array[ "sight_dist" ]	 = 0;
	array[ "detect_dist" ]	 = 0;
	
	stealth_corpse_ranges_custom( array );
}

custom_truck_melee_guard_stealth_setting()
{

	ai_event[ "ai_eventDistFootstepWalk" ] 	 = [];
	ai_event[ "ai_eventDistFootstepSprint" ] = [];

	ai_event[ "ai_eventDistFootstepWalk" ][ "hidden" ]		= 50;
	ai_event[ "ai_eventDistFootstepSprint" ][ "hidden" ]	= 50;	
	
	stealth_ai_event_dist_custom( ai_event );
	
}

//Set up nightvision
nightvision_setup()
{
	vision_set_changes( "castle", 4 );
	
	maps\_nightvision::main( level.players );
	VisionSetNight( "castle_nvg_grain" );
	level.player SetActionSlot( 1, "" ); // nightvision turns this on
	
	level thread night_vision_flags();

	PreCacheString( &"SCRIPT_NIGHTVISION_USE" );
	PreCacheString( &"SCRIPT_NIGHTVISION_STOP_USE" );

	// Press^3 [{+actionslot 1}] ^7to use Night Vision Goggles.
	add_hint_string( "nvg", &"SCRIPT_NIGHTVISION_USE", maps\_nightvision::ShouldBreakNVGHintPrint );
	// Press^3 [{+actionslot 1}] ^7to disable Night Vision Goggles.
	add_hint_string( "disable_nvg", &"SCRIPT_NIGHTVISION_STOP_USE", maps\_nightvision::should_break_disable_nvg_print );

	level.player thread nightvision_logic();
}

night_vision_flags()
{
	flag_init( "nvg_on" );
	
	while ( true )
	{
		level.player waittill( "night_vision_on" );
		flag_set( "nvg_on" );
		level.player waittill( "night_vision_off" );
		flag_clear( "nvg_on" );
	}
}

nightvision_logic()
{
	self SetActionSlot( 1, "nightvision" ); // player can now use night vision
	self ent_flag_set( "nightvision_dlight_enabled" );

	flag_wait("display_nvg_on_hint");	
	self display_hint_timeout( "nvg", 15 );

	flag_wait("display_nvg_off_hint");
	self display_hint_timeout( "disable_nvg", 15);
}

parachute_control_setup()
{
	PreCacheString( &"CASTLE_HINT_PARACHUTE_FLARE" );
	PreCacheString( &"CASTLE_HINT_PARACHUTE_STEER" );

	// Press^3 [{+actionslot 1}] ^7to use Night Vision Goggles.
	add_hint_string( "parachute_flare", &"CASTLE_HINT_PARACHUTE_FLARE", ::ShouldBreakFlareHintPrint );
	add_hint_string( "parachute_steer", &"CASTLE_HINT_PARACHUTE_STEER" );
}

ShouldBreakFlareHintPrint()
{
	Assert( IsPlayer( self ) );
	return ( self.parachute_dynamics[ "flare_state" ] == "flare_in" );
}

register_anim_node( targetname )
{
	if ( !IsDefined( level.anim_nodes ) )
	{
		level.anim_nodes = [];
	}
	
	node = getstruct( targetname, "targetname" );
	
	AssertEx( IsDefined( node ), "Can't register anim node.  Node does not exist." );
	
	level.anim_nodes[ targetname ] = node;
}

get_new_anim_node( targetname, b_script_origin )
{
	if ( !IsDefined( b_script_origin ) )
	{
		b_script_origin = false;
	}
	
	if ( IsDefined( level.anim_nodes[ targetname ] ) )
	{
		if ( b_script_origin )
		{
			node = Spawn( "script_origin", ( 0, 0, 0 ) );
		}
		else
		{
			node = SpawnStruct();
		}
		
		node.origin = level.anim_nodes[ targetname ].origin;
		node.angles = level.anim_nodes[ targetname ].angles;
		return node;
	}
	else
	{
		AssertMsg( "Can't get new anim node.  Anim node not registered." );
	}
}

get_ai_when_spawned( val, key )
{
	ai = get_living_ai( val, key );
	if ( !IsAlive( ai ) )
	{
		sp = GetEnt( val, key ); // assume it's a spawner
		
		AssertEx( IsSpawner( sp ), "No spawner, get_ai_when_spawned will never return!" );
		
		sp waittill( "spawned", ai );
	}
	
	if ( !spawn_failed( ai ) )
	{
		return ai;
	}
}

run_thread_when_spawned( val, key, func, arg1 )
{
	ai = get_ai_when_spawned( val, key );
	
	if ( IsDefined( func ) )
	{
		if ( IsDefined( arg1 ) )
		{
			ai thread [[ func ]]( arg1 );
		}
		else
		{
			ai thread [[ func ]]();
		}
	}
}

set_rain_level( n_level )
{
	if ( n_level == 0 )
	{
		level notify( "_rain_thread" );
	}
	else
	{
		level thread _rain_thread( n_level );
		
		/#
			IPrintLn( "rain level: " + n_level );
		#/
	}
}

_rain_thread( n_level )
{
	RAIN_HIGHT = 0;
	
	level notify( "_rain_thread" );
	level endon( "_rain_thread" );
	
	fx = getfx( "rain" + n_level );
	
	while ( true )
	{
		v_player_pos = level.player GetOrigin();
		PlayFX( fx, v_player_pos + ( 0, 0, RAIN_HIGHT) );
		
		wait .3;
	}
}


//
//	Generates lightning flashes every n_interval_min to n_interval_max seconds.
//	PARAMS:
//		n_interval_min 	- minimum time between lightning flashes
//		n_interval_max 	- maximum time between lightning flashes
//		v_light_dir 	- Optional light direction override (as angles)
//		str_local_lights- Optional name of dynamic light entities that will flash with the lightning
//		local_flash_intensity- Optional intensity of dynamic light entities that will flash with the lightning (3.0 is default)
//		local_flash_color- Optional color of dynamic light entities that will flash with the lightning (no change to color is default)
set_lightning( n_interval_min, n_interval_max, v_light_dir, str_local_lights, local_flash_intensity, local_flash_color )
{
	if ( IsDefined( str_local_lights ) )
	{
		level thread _setup_local_lightning_lights( str_local_lights, local_flash_intensity, local_flash_color );
	}

	if ( ( n_interval_min == 0 ) && ( n_interval_max == 0 ) )
	{
		level notify( "_lightning_thread" );
	}
	else
	{
		level thread _lightning_thread( n_interval_min, n_interval_max, v_light_dir );
		
		/#
			IPrintLn( "lightning interval: " + n_interval_min + "," + n_interval_max );
		#/
	}	
}

_remove_local_lightning_lights( str_local_lights )
{
	// Reduce given lights back to normal
	a_e_lights = GetEntArray( str_local_lights, "targetname" );
	foreach( e_light in a_e_lights )
	{
		e_light SetLightIntensity( e_light.n_intensity_base );
		e_light SetLightColor( e_light.v_color_base );
	}
	
	// Remove them from the lightning local lights list
	level.a_e_local_lightning = array_remove_array( level.a_e_local_lightning, a_e_lights );
}

_disable_local_lightning_lights( str_local_lights )
{
	_remove_local_lightning_lights( str_local_lights );
		
	// Disable given lights
	a_e_lights = GetEntArray( str_local_lights, "targetname" );
	foreach( e_light in a_e_lights )
	{
		e_light SetLightIntensity( 0.01 );
	}
}

// Setup the dynamic lights that will flash in time with the lightning
_setup_local_lightning_lights( str_local_lights, flash_intensity, flash_color )
{
	// Reduce old lights back to nothing
	foreach( e_light in level.a_e_local_lightning )
	{
		e_light SetLightIntensity( e_light.n_intensity_base );
		e_light SetLightColor( e_light.v_color_base );
	}
	
	level.a_e_local_lightning = GetEntArray( str_local_lights, "targetname" );
	if ( !IsDefined( level.a_e_local_lightning ) )
	{
		level.a_e_local_lightning = [];
	}
	else
	{
		// Save off the original light level of the new lights
		foreach( e_light in level.a_e_local_lightning )
		{
			if ( !IsDefined( e_light.n_intensity_base ) )
			{
				e_light.n_intensity_base = e_light GetLightIntensity();
				e_light.v_color_base = e_light GetLightColor();
			}

			e_light SetLightIntensity( e_light.n_intensity_base );
			e_light SetLightColor( e_light.v_color_base );
			
			if ( IsDefined( flash_intensity ) )
			{
				e_light.n_intensity_flash = flash_intensity;
			}
			else
			{
				e_light.n_intensity_flash = N_LIGHTNING_INTENSITY;
			}
			
			if ( IsDefined( flash_color ) )
			{
				e_light.v_color_flash = flash_color;				
			}
			else
			{
				e_light.v_color_flash = e_light.v_color_base;	
			}
		}
	}
}


//
_lightning_thread( n_interval_min, n_interval_max, v_light_dir )
{
	LIGHTNING_DIST = 15000;
	SUN_OFFSET = ( 0, 0, 5000 );
	
	LIGHTNING_TIME_SHORT = 0.3;
	LIGHTNING_TIME_LONG = 0.8;
	
	v_UP = ( 1, 0, 0 );
	
	v_LIGHTNING_SUN_LIGHT = ( 1.0, 1.0, 1.0 );
	
	a_MAP_SUN_LIGHT = GetMapSunLight();
	v_MAP_SUN_LIGHT = ( a_MAP_SUN_LIGHT[0], a_MAP_SUN_LIGHT[1], a_MAP_SUN_LIGHT[2] );
	
	v_MAP_SUN_DIR = GetMapSunDirection();
	
	level notify( "_lightning_thread" );
	level endon( "_lightning_thread" );
	
	//ResetSunDirection();
	ResetSunLight();

	v_player_forward = undefined;	// scope declaration
	while ( true )
	{
		v_player_pos = level.player GetOrigin();
		
		if ( IsDefined( v_light_dir ) )
		{
			v_player_forward = AnglesToForward( v_light_dir ) * LIGHTNING_DIST;
			v_offset = v_player_forward;
		}
		else
		{
			v_player_forward = AnglesToForward( level.player.angles ) * LIGHTNING_DIST;
			v_offset = maps\castle_fx::rotate_vector( v_player_forward, ( 0, RandomIntRange( -50, 50 ), 0 ) );
		}
		v_fx = v_player_pos + v_offset;
		
		fx = getfx( "lightning_bolt_fast" );
		
		time = LIGHTNING_TIME_SHORT;
		fade_out_frames = 5;
	
		if ( RandomIntRange( 0, 100 ) < 30 ) // chance of longer lightning bolt
		{
			fx = getfx( "lightning_bolt_slow" );
			
			time = LIGHTNING_TIME_LONG;
			fade_out_frames = 15;
		}
	
		level notify( "lightning_bolt" );
		PlayFX( fx, v_fx, v_UP );
		
		if ( !IsDefined( v_light_dir ) )
		{
			v_lightning_sun_dir = v_fx + SUN_OFFSET;
		}
		else
		{
			v_lightning_sun_dir = AnglesToForward( v_light_dir );
		}
		
		//SetSunDirection( v_lightning_sun_dir );
		SetSunLight( v_LIGHTNING_SUN_LIGHT[0], v_LIGHTNING_SUN_LIGHT[1], v_LIGHTNING_SUN_LIGHT[2] );

		// Lightning flash with local lights
		foreach( e_light in level.a_e_local_lightning )
		{
			e_light SetLightIntensity( e_light.n_intensity_flash );
			e_light SetLightColor( e_light.v_color_flash );
		}

		wait time;

		// Lerp the sun light and direction back to the map settings
		for ( frames = 0; frames <= fade_out_frames; frames++ )
		{
			lerp_coef = frames / fade_out_frames;
			
			v_sun_light = VectorLerp( v_LIGHTNING_SUN_LIGHT, v_MAP_SUN_LIGHT, lerp_coef );
			SetSunLight( v_sun_light[0], v_sun_light[1], v_sun_light[2] );
			
			//v_sun_dir = VectorLerp( v_lightning_sun_dir, v_MAP_SUN_DIR, lerp_coef );
			//SetSunDirection( v_sun_dir );
			
			// We're lerping here from the max back down to the original intensity/color for each light
			foreach( e_light in level.a_e_local_lightning )
			{
				e_light SetLightIntensity( e_light.n_intensity_flash + ((e_light.n_intensity_base - e_light.n_intensity_flash) * lerp_coef) );
				e_light SetLightColor( VectorLerp( e_light.v_color_flash, e_light.v_color_base, lerp_coef ) );
			}
			
			wait .05;
		}
		
		wait RandomFloatRange( n_interval_min, n_interval_max );
	}
}

set_cloud_lightning( n_interval_min, n_interval_max )
{
	if ( ( n_interval_min == 0 ) && ( n_interval_max == 0 ) )
	{
		level notify( "_cloud_lightning_thread" );
	}
	else
	{
		level thread _cloud_lightning_thread( n_interval_min, n_interval_max );
		
		/#
			IPrintLn( "cloud lightning interval: " + n_interval_min + "," + n_interval_max );
		#/
	}	
}

_cloud_lightning_thread( n_interval_min, n_interval_max )
{
	LIGHTNING_DIST = 50000;
	LIGHTNING_HEIGHT = 10000;
	
	level notify( "_cloud_lightning_thread" );
	level endon( "_cloud_lightning_thread" );
	
	while ( true )
	{
		v_player_pos = level.player GetOrigin();
		v_player_forward = AnglesToForward( level.player.angles ) * LIGHTNING_DIST;
		v_offset = maps\castle_fx::rotate_vector( v_player_forward, ( 0, RandomIntRange( -50, 50 ), 0 ) );
		v_fx = v_player_pos + v_offset;
	
		fx = getfx( "lightning" );
		PlayFX( fx, v_fx + ( 0, 0, LIGHTNING_HEIGHT ) );
		
		wait RandomFloatRange( n_interval_min, n_interval_max );
	}
}

palm_style_door_open_outward( soundalias )
{
	wait( 1.35 );

	if ( IsDefined( soundalias ) )
		self PlaySound( soundalias );
	else
		self PlaySound( "door_wood_slow_open" );

	self RotateTo( self.angles + ( 0, -70, 0 ), 2, .5, 0 );
	self ConnectPaths();
	self waittill( "rotatedone" );
	self RotateTo( self.angles + ( 0, -40, 0 ), 2, 0, 2 );
}

price_stealth_think()
{
	level endon( "price_stealth_end" );

	self.pacifist = true;
	self.ignoreme = true;
	self.grenadeammo = 0;
	self.disableLongDeath = true;
	
	self enable_cqbwalk();
	
	flag_wait( "_stealth_spotted" );
	
	self disable_cqbwalk();
	
	self.pacifist = false;	
	self.ignoreme = false;
}


// 	Make Price die if AI can't kill him right away
//
kill_price_if_taking_too_long()
{
	self endon( "death" );
	
	if(isdefined(self.price_under_platform) && self.price_under_platform == true)
	{
//		self.a.special = "dying_crawl";
//		self.a.pose = "prone";
//		origin =  self.origin - (0, 0, 30);
//		self forceteleport(origin, self.angles);
//		self die();
		//return;
		
		wait(1);
		//self ClearAnim( %root, 0 );
		self setAnim( %dying_crawl_death_v1, 1, 0.2, 1);
		wait(0.5);
		self setAnim( %dying_crawl_death_v1, 1, 0.2, 0);
		setDvar( "ui_deadquote", &"CASTLE_YOUR_ACTIONS_GOT_PRICE" );
		missionFailedWrapper();
		
	}
	else
	{
		wait 15;
		self die();
	}
}


save_game( name )
{
	// autosave stealth is not actually set up to use ::_autosave_stealthcheck, 
	// but that function doesn't actually work right anyway, 
	// so most of this code is stolen from there and modified to work.
	
	if ( !flag( "_stealth_spotted" ) && stealth_is_everything_normal() && !flag( "_stealth_player_nade" ) && maps\_autosave::autoSaveCheck(true, true) )
	{
		vehicles = getentarray( "destructible_vehicle", "targetname" );
		foreach ( vehicle in vehicles )
		{
			if ( isDefined( vehicle.healthDrain ) )
				return ;
		}
//		level thread autosave_by_name( name );
//		level thread autosave_stealth();
		level thread autosave_now();
	}
}


//
//	Spawn a body to play an animation and link the player to it
do_player_anim( str_scene, additional_ents, b_ground_trace, b_lerp_time, b_freeze_controls, b_allow_look, n_max_right, n_max_left, n_max_up, n_max_down, tag )
{
	player_anim_start( str_scene, additional_ents, b_ground_trace, b_lerp_time, b_freeze_controls, b_allow_look, n_max_right, n_max_left, n_max_up, n_max_down,tag );
		
	player_anim_cleanup( b_ground_trace, b_freeze_controls );
}


//
//	Sets up the player rig for an animation.
//	Call by itself if you need to play a string of related player animations.
//	If you only have one anim, call do_player_anim
player_anim_start( str_scene, additional_ents, b_ground_trace, b_lerp_time, b_freeze_controls, b_allow_look, n_max_right, n_max_left, n_max_up, n_max_down, tag )
{
	if ( !IsDefined( b_lerp_time ) )
	{
		b_lerp_time = false;
	}

	if ( !IsDefined( b_freeze_controls ) )
	{
		b_freeze_controls = false;
	}

	level.player _disableWeapon();
	
	if ( !IsDefined( level.player.m_player_rig ) )
	{
		level.player.m_player_rig = spawn_anim_model( "player_rig" );
		level.player.m_player_rig Hide();
	}

	anim_ents = [];
	if ( IsArray( additional_ents ) )
	{
		anim_ents = array_add( additional_ents, level.player.m_player_rig );
	}
	else
	{
		anim_ents = make_array( level.player.m_player_rig, additional_ents );
	}
	
	s_align = self;
	if ( s_align == level )
	{
		s_align = SpawnStruct();
		s_align.origin = level.player.origin;
		s_align.angles = level.player.angles;
	}
	
	s_align anim_first_frame_solo( level.player.m_player_rig, str_scene, tag );

	if ( b_freeze_controls )
	{
		level.player FreezeControls( b_freeze_controls );
	}

	if ( b_lerp_time > 0 )
	{
		level.player PlayerLinkToBlend( level.player.m_player_rig, "tag_player", b_lerp_time, b_lerp_time * 0.25, b_lerp_time * 0.25 );
		wait b_lerp_time;
	}
	else if ( IsDefined( b_allow_look ) && b_allow_look )
	{
		level.player PlayerLinkToDelta( level.player.m_player_rig, "tag_player", 1.0, n_max_left, n_max_right, n_max_up, n_max_down );
	}
	else
	{
		// NOTE: Getting AdsButtonPressed input doesn't work with this option.
		level.player PlayerLinkToAbsolute( level.player.m_player_rig, "tag_player" );
	}
	
	level.player HideViewModel();

	
	waittillframeend;
	wait( 0.05 );
	level.player notify( "player_anim_started" );
	
	level.player.m_player_rig Show();
	s_align anim_single( anim_ents, str_scene, tag );
}


//
//	Call this when you're done animating the player
player_anim_cleanup( b_ground_trace, b_froze_controls )
{
	if ( !IsDefined( b_froze_controls ) )
	{
		b_froze_controls = false;
	}

	level.player Unlink();
	level.player.m_player_rig Delete();
	
	if ( b_froze_controls )
	{
		level.player FreezeControls( false );
	}
	
	level.player ShowViewModel();
	level.player _enableWeapon();
	
	if ( IsDefined( b_ground_trace ) && b_ground_trace )
	{
		// Make sure player in not in the ground
		a_trace = BulletTrace( level.player.origin + ( 0, 0, 40 ), level.player.origin + ( 0, 0, -100 ), false, undefined, true );
		level.player SetOrigin( a_trace["position"] );
	}
}

player_rain_drops()
{
	e_fx = spawn_tag_origin();
	draw_frame = true;
	level.blizzard_overlay_alpha_cap = 1;
	
	level.rain_overlay = [];
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_large";
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_large_02";
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_small";
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_small_02";
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_large";
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_large_02";
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_small";
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_small_02";
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_large";
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_large_02";
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_small";
	level.rain_overlay[ level.rain_overlay.size ] = "overlay_rain_small_02";
	
	while ( IsAlive( self ) )
	{
		e_fx.origin = self GetEye();
		e_fx.angles = self GetPlayerAngles();
			

		if( e_fx.angles[0] < -60 )
		{
			traceData = BulletTrace(e_fx.origin, e_fx.origin  + (0,0,500), false );
				
			if( tracedata[ "fraction" ] == 1)
			{
   				rain_overlay_alpha(3.0, 0, 1);
		      	wait(0.05);
		      	continue;
			}
		}

		wait 0.5;	
	}
}

//*****************************************************************************************
//	SHIMMY FROM PARIS_A
//	Shamelessly stolen from Paris.  We should try to make this a utility file if possible.
//*****************************************************************************************
player_shimmy( str_endon )
{
//TODO Different from Paris - added an endon
	if ( IsDefined( str_endon ) )
	{
		level endon( str_endon );
	}
	level.player endon( "death" );
	
	state = SpawnStruct();

	// tunable params

	speed = 40; // inches per second
	time_to_fall = 0.5; // how long you must try to walk off the ledge before you fall off
	// extra space added to each end so we aren't right on the edge of coming off when we attach
	// could probably lerp thickness between points if necessary in the geo
	link_duration = 1;  // time to link at the start
	unlink_duration = 1; // time to unlink when walking off the end
	jump_duration = .5;  // time to unlink when falling off the left side
	thickness = 16;
	angle_smoothing = .7;
	
	speed_amplitude = 24;
	speed_angular_frequency = 360 / 1.25;  // degrees per second of phase (360 / footstep time)
	footstep_phase = 270; // degrees, where in the footstep we play effects
	
	// when you get on, advance this far past the first origin.  Shouldn't be farther than the distance to the second origin.
	start_distance = 48;
	
	// when you get off, we put you this far past the end of the last segment.
	end_distance = 24;
	
	// when you jum off, we move you this far out
	jump_distance = 24;
	
	// view constraints while you're linked
	right_arc = 40;
	left_arc = 40;
	top_arc = 20;
	bottom_arc = 5;
	
	// this is an engine constant, and what would be returned by level.player GetPlayerViewHeight(), assuming the player is standing.
	// we use a constant in case he's not standing when we start.
	player_view_height = 60;
	
	state.min_left = thickness * -0.5;
	state.max_left = thickness *  0.5;
	dt = 0.05;
	
	// arrays describing the path
	state.points = [];
	state.angles = [];
	state.to_next = [];
	state.dir_to_next = [];
	state.dist_to_next = [];
	state.left_dir = [];
	
	// read in all the points on the path
	struct = getstruct("struct_player_shimmy_start", "script_noteworthy");
	i = 0;
	while(IsDefined(struct))
	{
		Assert(IsDefined(struct.angles), "Shimmy structs all need angles");
		
		state.points[i] = struct.origin;
		state.angles[i] = struct.angles;		
				
		if(i > 0)
		{
			state.to_next[i - 1] = state.points[i] - state.points[i - 1];
			state.dir_to_next[i - 1] = VectorNormalize(state.to_next[i - 1]);
			state.dist_to_next[i - 1] = Length(state.to_next[i - 1]);
			state.left_dir[i - 1] = VectorNormalize(VectorCross((0, 0, 1), state.dir_to_next[i - 1]));
			Assert(state.dist_to_next[i - 1] != 0);
			Assert(state.left_dir[i - 1] != (0, 0, 0));
		}
		
		if(IsDefined(struct.target))
		{
			struct = GetStruct(struct.target, "targetname");
			i++;
		}
		else
		{
			break;	
		}
	}
	Assert(state.points.size >= 2, "It takes two points to shimmy.");
	// we add some extra distance to the last segment to provide some hysteresis when getting on at the end.
	state.dist_to_next[state.dist_to_next.size - 1] += .125;
	
	while(true)
	{
		
		// wait for player to hit first or last point
		for(;; waitframe())
		{
			if(player_shimmy_in_segment(state, 0) || player_shimmy_in_segment(state, state.points.size - 2))
				break;
		}
	
		player_shimmy_origin_to_state(state, level.player.origin);
		Assert(IsDefined(state.segment_index));
		if(!IsDefined(state.segment_index))
			continue;
		
		player_control_off(false);
//TODO commented out for castle
//		aud_send_msg("mus_ledge_walk");
//		flag_set("flag_dialogue_watch_your_step");
		
		// do the cheating to start you somewhat into the sequence
		player_shimmy_origin_to_state(state, level.player.origin);
		if(state.segment_index == 0)
		{
			state.segment_forward += start_distance;
		}
		else
		{
			state.segment_forward -= start_distance;
		}
		state.segment_left = clamp(state.segment_left, state.min_left, state.max_left);
		
		struct = player_shimmy_state_to_point(state);
		
		// these are updated in the main loop
		logical_origin = struct.origin;  // needed because the real player_link_ent.origin needs to be tweaked based on pitch.
		smooth_angles = struct.angles;
		
		using_initial_player_angles = true;
		initial_player_angles = level.player.angles;
		
		player_link_ent = spawn_tag_origin();
		
		lerp_vector = (struct.origin + (0, 0, player_view_height)) - (level.player GetEye()); 
		
		lerp_params = compute_lerp_params(
			link_duration,
			VectorDot(level.player GetVelocity(), VectorNormalize(lerp_vector)),
			Length(lerp_vector));
		
		level.player lerp_player_camera(
			struct.origin + (0, 0, player_view_height), struct.angles,
			link_duration, lerp_params.accel_time, lerp_params.decel_time, link_duration * .4, link_duration * .4,
			player_link_ent,
			right_arc, left_arc, top_arc, bottom_arc);
		
		// main loop
		can_fall_yet = false;
		fall_duration = 0;
		moving_time = 0;
		next_footstep_time = footstep_phase / speed_angular_frequency;
		state.jumped = false;
		while(true)
		{			
			player_shimmy_origin_to_state(state, logical_origin);
			
			// if we fell off the end
			if(!IsDefined(state.segment_index))
				break;
			
			state.last_segment_index = state.segment_index;
			
			stick = level.player GetNormalizedMovement();
					
			// switch to right-handed coordinates
			stick = (stick[0], stick[1] * -1, 0);
			
			// forget the initial orientation when you get below .25 forward
			if(stick[0] < .25)
			{				
				using_initial_player_angles = false;
			}
			// don't let you fall until you stop moving
			if(Length(stick) < .1) 
			{				
				can_fall_yet = true;
			}
						
			if(using_initial_player_angles)
				player_to_global_angles = initial_player_angles;
			else
				player_to_global_angles = level.player.angles;
				
			stick_player_angles = VectorToAngles(stick);
			stick_global_angles = flat_angle(CombineAngles(player_to_global_angles, stick_player_angles));
			stick_global = AnglesToForward(stick_global_angles) * Length(stick);
			
			stick_local_forward = VectorDot(stick_global, state.dir_to_next[state.segment_index]);
			stick_local_left = VectorDot(stick_global, state.left_dir[state.segment_index]);
			
			// sine-wave speed to simulate footsteps
			if(abs(stick_local_forward) > .1)
			{
				moving_time += dt;
			}
			else
			{
				moving_time = 0;
				next_footstep_time = footstep_phase / speed_angular_frequency;
			}
			cur_speed = speed + speed_amplitude * Sin(moving_time * speed_angular_frequency);
			
			if(moving_time > next_footstep_time)
			{
				fx_origin = state.points[state.segment_index] + state.dir_to_next[state.segment_index] * state.segment_forward;
				player_shimmy_foostep_effect_placeholder(fx_origin);
				
				next_footstep_time += 360.0 / speed_angular_frequency;
			}
//TODO commented out for castle
/*				
			// don't clip through NPCs
			// note: only works for NPCs ahead of us.
			if(stick_local_forward > 0)
			{
				closest_npc = shimmy_moment_get_closest_npc(logical_origin);
				if(IsDefined(closest_npc))
				{
					to_npc = closest_npc.origin - logical_origin;
					if(VectorDot(to_npc, state.dir_to_next[state.segment_index]) > 0)
					{
						dist = Length(to_npc);
						stick_local_forward = linear_map_clamp(dist, 32, 64, 0, stick_local_forward);
					}
				}
			}				
*/				
			// advance our position
			state.segment_forward += stick_local_forward * cur_speed * dt;
			state.segment_left += stick_local_left * cur_speed * dt;
			
			// allow falling off on the left side of the path
//			if(can_fall_yet && state.segment_left > state.max_left && stick[0] > .5)
//			{
//				fall_duration += dt;
//			}
//			else
//			{
//				fall_duration = 0;
//			}
//			
//			if(fall_duration > time_to_fall)
//			{
//				state.jumped = true;
//				break;	
//			}				
						
			state.segment_left = clamp(state.segment_left, state.min_left, state.max_left);
	
			struct = player_shimmy_state_to_point(state);
			

			// time-based smoothing to cover discontinuties in our parametric position when the path goes around a bend
			// can't just use RotateTo because it uses quat slerp which can result in a roll angle.
			
			smooth_angles = euler_lerp(struct.angles, smooth_angles, angle_smoothing);
			
			player_link_ent.angles = smooth_angles;
			
			// want to do player_link_ent.origin = struct.origin, but then when we detach, we'd be facing down.
			// instead we need to set player_link_ent's position to the position such that, when we detach, the player
			// would end up at struct.origin
			
			logical_origin = struct.origin;
			player_link_ent.origin = logical_origin + (0, 0, player_view_height) - AnglesToUp(smooth_angles) * player_view_height;
			
			/#
			//thread draw_line_for_time(player_link_ent.origin + 60 * AnglesToUp(player_link_ent.angles), player_link_ent.origin + 60 * AnglesToUp(player_link_ent.angles) + AnglesToForward(struct.angles) * 32, 1, 0, 0, 10);
			//thread draw_line_for_time(logical_origin, state.points[state.segment_index] + state.dir_to_next[state.segment_index] * state.segment_forward, 0, 1, 0, 10);
			#/
			
			wait(dt);			
		}
		
		// we're done, lerp out smoothly.
		if(IsDefined(state.last_segment_index))
		{
			if(state.jumped)
			{
				state.segment_index = state.last_segment_index;
				state.segment_left += jump_distance;
				
				ending_origin = player_shimmy_state_to_point(state).origin;
				ending_forward = AnglesToForward(level.player GetPlayerAngles());
				
				level.player EnableWeapons();
			
				accel_time = jump_duration * .2;
				decel_time = jump_duration * .5;
				level.player LerpViewAngleClamp(jump_duration, accel_time, decel_time, 0, 0, 0, 0);
				player_link_ent RotateTo(VectorToAngles(ending_forward), jump_duration, accel_time, decel_time);
				player_link_ent MoveTo(ending_origin, jump_duration, accel_time, decel_time);
				wait(jump_duration);
			}
			else
			{
				// cheat ourselves forward so we move during the blend (note this involes out of bounds positions on the segment)				
				state.segment_index = state.last_segment_index;
				if(state.segment_index == 0)
				{
					state.segment_forward -= end_distance;
				}
				else
				{
					state.segment_forward += end_distance;
				}
				ending_origin = player_shimmy_state_to_point(state).origin;
							
				ending_forward = state.dir_to_next[state.last_segment_index];
				if(state.last_segment_index == 0)
					ending_forward *= -1;
			
				// cast down to account for irregularities in the ground
				ground_position = GetGroundPosition(ending_origin, 16, 24, 24);
				if(IsDefined(ground_position))
					ending_origin = ground_position;
			
				level.player EnableWeapons();
			
				accel_time = unlink_duration * .2;
				decel_time = unlink_duration * .5;
				level.player LerpViewAngleClamp(unlink_duration, accel_time, decel_time, 180, 180, 90, 90);
				player_link_ent RotateTo(VectorToAngles(ending_forward), unlink_duration, accel_time, decel_time);
				player_link_ent MoveTo(ending_origin, unlink_duration, accel_time, decel_time);
				wait(unlink_duration);
			}
		}

		
		player_control_on();
		player_link_ent Delete();
		
		// must give the player a chance to move back to his logical_origin before re-evaluating whether to get back on
		waitframe();
		waitframe();
	}
}


lerp_player_camera(target_eye_origin, target_eye_angles, time, linear_accel_time, linear_decel_time, camera_accel_time, camera_decel_time, target_link_ent, right, left, top, bottom)
{
	Assert(IsPlayer(self));
	test = level.player GetPlayerViewHeight();
	player_view_height = 60;  // using GetPlayerViewHeight wouldn't work if we're crouched, which we disallow anyway
	
	player_eye_ent = spawn_tag_origin();
	player_eye_ent.angles = self GetPlayerAngles();
	// not sure why we need to compensate for two frames of velocity, instead of just one, but it seems to work.
	// also, instead of calling GetEye() directly, we compute what it should be if we were standing
	//player_eye_ent.origin = self GetEye() + (self GetVelocity()) * .1;
	player_eye_ent.origin = self.origin + (0, 0, player_view_height) + (self GetVelocity()) * .1;
		
	player_link_ent = spawn_tag_origin();
	player_link_ent LinkTo(player_eye_ent, "tag_origin", (0, 0, -1 * player_view_height), (0, 0, 0));
	
	self PlayerLinkToDelta(player_link_ent, "tag_origin", 1, 0, 0, 0, 0, true);

	player_eye_ent MoveTo(target_eye_origin, time, linear_accel_time, linear_decel_time);
	player_eye_ent RotateTo(target_eye_angles, time, camera_accel_time, camera_decel_time);
		
	wait time;
		
	// we pass in the link ent so we can avoid ever unlinking the player, supressing Unlinked In Solid spam.
	target_link_ent.origin = target_eye_origin + (0, 0, player_view_height) - AnglesToUp(target_eye_angles) * player_view_height;
	target_link_ent.angles = target_eye_angles;	
	
	self PlayerLInkToDelta(target_link_ent, "tag_origin", 1, right, left, top, bottom, true);
	
	player_link_ent Delete();
	player_eye_ent Delete();
}

compute_lerp_params(duration, init_speed, distance)
{
	min_slope_time = duration * .25;
	
	ret = SpawnStruct();
	
	if(distance > 0 && init_speed > 0)
	{
		init_parametric_speed = init_speed / distance;
		
		// to compute maxspeed in the blend, the code does this:
		// maxSpeed = 2.0f / ( ( 2.0f * totalTime ) - totalAccelTime - totalDecelTime );
		// we consider totalAccelTime = 0 and solve for totalDecelTime
		
		totalDecelTime  = (2.0 * duration) - 2.0 / init_parametric_speed;
		
		if(totalDecelTime > min_slope_time)
		{
			if(totalDecelTime <= duration)
			{
				// the good case, where our speeds will match
				ret.accel_time = 0;
				ret.decel_time = totalDecelTime;
			}
			else
			{
				// going too fast, so we will decelerate as much as possible but there will be a discontinuity
				// in this case we could decrease the total duration, but that might make it even more abrupt.
				ret.accel_time = 0;
				ret.decel_time = duration;				
			}
		}
		else
		{
			// going too slow, our deceleration would need to be too steep (or impossible)
			// so we will have to speed up.  figure what our max speed would be with zero accel and min_slope_time decel
			// we could increase the transition time in this case, but it could be unboundedly long so that wouldn't totally solve the problem.
			max_parametric_speed = 2.0 / (( 2.0 * duration) - min_slope_time);
			
			if(init_parametric_speed > max_parametric_speed * 0.5)
			{
				// doing that is better than starting from a dead stop
				ret.accel_time = 0;
				ret.decel_time = min_slope_time;
			}
			else
			{
				// going so slow it's better to pop to stopped than pop to max speed
				ret.accel_time = min_slope_time;
				ret.decel_time = min_slope_time;
			}			
		}
	}
	else
	{
		// totally stopped or no distance to cover, use sensible defaults
		ret.accel_time = min_slope_time;
		ret.decel_time = min_slope_time;
	}
	
	return ret;
}

player_shimmy_in_segment(state, i)
{
	point_to_pos = level.player.origin - state.points[i];
	point_to_pos_parallel = VectorDot(point_to_pos, state.dir_to_next[i]);
	
	if(point_to_pos_parallel > 0 && point_to_pos_parallel < state.dist_to_next[i])
	{
		left = VectorDot(point_to_pos, state.left_dir[i]);
		
		// make it easier to get on, since we need narrow widths to avoid getting off in geo.
		// only in the direction you can't fall in, so we don't get stuck in a falling loop.
		if(left > state.min_left * 2.5 && left < state.max_left * 2.5)
		{
			return true;
		}
	}
	return false;
}

player_shimmy_origin_to_state(state, pos)
{
	state.segment_index = undefined;
	
	for(i = 0; i < state.points.size - 1; i++)
	{
		point_to_pos = pos - state.points[i];
		
		point_to_pos_parallel = VectorDot(point_to_pos, state.dir_to_next[i]);

		if(point_to_pos_parallel < state.dist_to_next[i])
		{
			state.segment_left = VectorDot(point_to_pos, state.left_dir[i]);
			state.segment_index = i;
			state.segment_forward = point_to_pos_parallel;
			break;
		}				
	}
	
	// -0.125 is to provide some hysterisis 
	if(IsDefined(state.segment_index) && state.segment_index == 0 && state.segment_forward < -0.125)
	{
		state.segment_index = undefined;	
	}
}

player_shimmy_state_to_point(state)
{
	struct = SpawnStruct();
	
	i = state.segment_index;
	struct.origin = state.points[i] + state.dir_to_next[i] * state.segment_forward + state.left_dir[i] * state.segment_left;
	
	// tweak logical_origin for smooth travel around corners
	corner = undefined;
	if(state.segment_forward > state.dist_to_next[state.segment_index] && state.segment_index + 1 < state.dist_to_next.size)
		corner = state.points[state.segment_index + 1];
	if(state.segment_forward < 0 && state.segment_index > 0)
		corner = state.points[state.segment_index];
	
	if(IsDefined(corner))
	{
		corner_to_origin = struct.origin - corner;
		corner_to_origin_dist = Length(corner_to_origin);
		
		clamp_radius = -1 * state.min_left;
		if(state.segment_left > 0)
			clamp_radius = state.max_left;
		
		if(corner_to_origin_dist > clamp_radius)
		{
			corner_to_origin *= (clamp_radius / corner_to_origin_dist);
			struct.origin = corner + corner_to_origin;
		}				
	}
	
	// cubic spline, interval already scaled to [0, 1]	
	t = clamp(state.segment_forward / state.dist_to_next[i], 0, 1);
	pk = angles_clamp_180(state.angles[i]);
	pkp1 = pk;
	pkm1 = pk;
	if(i + 1 < state.angles.size)
		pkp1 = angles_clamp_180(state.angles[i + 1]);
	if(i - 1 > 0)
		pkm1 = angles_clamp_180(state.angles[i - 1]);
	pkp2 = pkp1;
	if(i + 2 < state.angles.size)
		pkp2 = angles_clamp_180(state.angles[i + 2]);

	
	h00 = (1 + 2 * t) * Squared(1 - t);
	h10 = t * Squared(1 - t);
	h01 = Squared(t) * (3 - 2 * t);
	h11 = Squared(t) * (t - 1);
	
	mk = (pkp1 - pkm1) / 2;  // t difference between adjacent points is always 1
	mkp1 = (pkp2 - pk) / 2;
	
	struct.angles = angles_clamp(h00 * pk + h10 * mk + h01 * pkp1 + h11 * mkp1);
	
	// simple linear blending
	//struct.angles = euler_lerp(state.angles[i], state.angles[i + 1], t);
		
	return struct;
}

player_shimmy_foostep_effect_placeholder(fx_origin)
{
//TODO commented out for castle
//	playfx(getfx("ledge_footstep_dust"), fx_origin);
}

angles_clamp_180(v)
{
	return (AngleClamp180(v[0]), AngleClamp180(v[1]), AngleClamp180(v[2]));
}

angles_clamp(v)
{
	return (AngleClamp(v[0]), AngleClamp(v[1]), AngleClamp(v[2]));
}

linear_map(x, in_min, in_max, out_min, out_max)
{
	return out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min);
}

linear_map_clamp(x, in_min, in_max, out_min, out_max)
{
	return clamp(linear_map(x, in_min, in_max, out_min, out_max), out_min, out_max);
}

angle_lerp(from, to, fraction)
{
	return AngleClamp(from + AngleClamp180(to - from) * fraction);	
}

euler_lerp(from, to, fraction)
{
	return (
	angle_lerp(from[0], to[0], fraction),
	angle_lerp(from[1], to[1], fraction),
	angle_lerp(from[2], to[2], fraction)
	);	
}

// turn off all the stuff we typically disable before scripted viewmodel animations
// might want to merge this with maps\_shg_common::SetUpPlayerForAnimations(), though it has some differences
player_control_off(bWait)
{
	if(!IsDefined(bWait)) bWait = true;
	
	level.player DisableWeapons();
	level.player AllowStand(true);
	level.player AllowCrouch(false);
	level.player AllowProne(false);	
	level.player AllowSprint(false);
	level.player SetStance("stand");
		
	if(bWait)
	{
		while((level.player GetStance() != "stand") || level.player IsThrowingGrenade() || level.player IsSwitchingWeapon())
			waitframe();	
	}
}

castle_hud_hint( string, zoffset )
{
	if ( !isdefined( zoffset ) )
		zoffset = 0;

	hintfade = 0.5;

	level endon( "clearing_hints" );

	if ( IsDefined( level.hintElement ) )
		level.hintElement maps\_hud_util::destroyElem();

	level.hintElement = maps\_hud_util::createFontString( "default", 1.5 );
	level.hintElement maps\_hud_util::setPoint( "MIDDLE", undefined, 0, 30 + zoffset );
	level.hintElement.color = ( 1, 1, 1 );
	level.hintElement SetText( string );
	level.hintElement.alpha = 0;
	level.hintElement FadeOverTime( 0.5 );
	level.hintElement.alpha = 1;
	wait( 0.5 );
	level.hintElement endon( "death" );
}

// unlink player and turn back on all the stuff disabled in player_control_disable()
player_control_on()
{
	level.player Unlink();
	level.player EnableWeapons();
	level.player AllowStand(true);
	level.player AllowCrouch(true);
	level.player AllowProne(true);	
	level.player AllowSprint(true);
}

//*****************************************************************************************
//	SHIMMY FROM PARIS_A
//	Shamelessly stolen from Paris.  We should try to make this a utility file if possible.
//	END 
//*****************************************************************************************

flashlight_on( b_cheap, fx_override )
{
	if ( !IsDefined( b_cheap ) )
	{
		b_cheap = true;
	}
	
	flashlight_off();
	
	fx = getfx( "flashlight_ai" );
	
	if ( IsDefined( fx_override ) )
	{
		fx = getfx( fx_override );
	}
	else if ( b_cheap )
	{
		fx = getfx( "flashlight_ai_cheap" );
	}
	
	PlayFXOnTag( fx, self, "tag_flash" );
	
	self.flashlight_fx = fx;
}

flashlight_off()
{
	if ( IsDefined( self.flashlight_fx ) )
	{
		StopFXOnTag( self.flashlight_fx, self, "tag_flash" );		
		self.flashlight_fx = undefined;
	}
}

anim_stealth_alert( ai_guy, str_scene )
{
	self endon( str_scene );
	ai_guy endon( "death" );
	ai_guy endon( "stop_current_anim" );
	
	ai_guy waittill_any( "awareness_alert_level", "damage" );
	ai_guy.engage_enemy = true;
	
	ai_guy stop_current_anim();
	//ai_guy ClearAnim( %root, 0 );
}

stop_current_anim()
{
	if ( IsDefined( self.align ) )
	{
		self.align notify( "stop_loop" );
	}
	
	self anim_stopanimscripted();
	self notify( "stop_current_anim" );
}

stealth_anim_single( ai_guy, str_scene )
{
	a_guys = make_anim_array( ai_guy );
	
	foreach ( ai_guy in a_guys )
	{
		ai_guy stop_current_anim();
		ai_guy.align = self;
		
		ai_guy.allowdeath = true;
		
		self thread anim_stealth_alert( ai_guy, str_scene );
	}

	self anim_single( a_guys, str_scene );
}

stealth_anim_loop( ai_guy, str_scene )
{
	a_guys = make_anim_array( ai_guy );
	
	foreach ( ai_guy in a_guys )
	{
		ai_guy stop_current_anim();
		ai_guy.align = self;
		
		ai_guy.allowdeath = true;
		
		self thread anim_stealth_alert( ai_guy, str_scene );
	}
	
	self anim_loop( a_guys, str_scene );
}

make_anim_array( ents )
{
	a_ents = [];
	if ( IsArray( ents ) )
	{
		a_ents = ents;
	}
	else
	{
		a_ents[0] = ents;
	}
	
	return a_ents;
}

open_tower_gate()
{
	m_left_gates = GetEntArray( "tower_gate_left", "targetname" );
	m_right_gates = GetEntArray( "tower_gate_right", "targetname" );
	
	foreach ( m_gate in m_left_gates )
	{
		m_gate ConnectPaths();
		m_gate Delete();
	}
	
	foreach ( m_gate in m_right_gates )
	{
		m_gate ConnectPaths();
		m_gate Delete();
	}
}
	
/*	From T6
=============
///ScriptDocBegin
"Name: nag_vo_until_flag( <a_nag_lines>, <str_ender_flag>, [n_repeat_interval], [should_randomize], [b_play_line_now], [func_filter] )"
"Summary: Plays nag lines until a flag is set, with optional randomized order and scripter defined logic"
"Module: Utility"
"CallOn: Entity saying VO nag lines"
"MandatoryArg: <a_nag_lines> Array containing nag line references"
"MandatoryArg: <str_ender_flag> Name of flag that will kill nag lines when set"
"MandatoryArg: <n_repeat_interval> How often nag lines will play"
"OptionalArg: <should_randomize> Bool randomizing the nag line array. Defaults to false."
"OptionalArg: <b_play_line_now> Bool for playing lines immediately. Defaults to false."
"OptionalArg: <func_filter> Function pointer that should return a bool - use if you need extra logic for nag VO. Defaults to undefined."
"Example: nag_vo_until_flag( level.woods, a_car_nag_lines, "start_drive", 4, ::filter_nag_vo );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
nag_vo_until_flag( a_nag_lines, str_ender_flag, n_repeat_interval, should_randomize, b_play_line_now, func_filter )
{
	assert( IsDefined( a_nag_lines ), "a_nag_lines missing in nag_vo_until_flag" );
	assert( IsDefined( str_ender_flag ), "str_ender_flag missing in nag_vo_until_flag" );
	assert( IsDefined( n_repeat_interval ), "n_repeat_interval missing in nag_vo_until_flag" );
	assert( a_nag_lines.size > 1, "VO array is empty");
	
	// TFLAME - 4/20/2011 - Taking this out for now since we're moving in the direction of having no animnames for VO
	//assert( IsDefined( self.animname ), "ent number " + self GetEntityNumber() + " using nag_vo_until_flag is missing animname!" );	
	
	self notify( "_stop_nag_lines" );  // make sure only one instance of this function is being used on this entity
	self endon( "_stop_nag_lines" );
	level endon ( str_ender_flag );
	
	if ( flag( str_ender_flag )	)  // don't play lines if flag already set
	{
		return;
	}

	if ( !IsDefined( should_randomize ) )
	{
		should_randomize = false;
	}
	
	if ( !IsDefined( b_play_line_now ) ) 
	{
		b_play_line_now = false;
	}
	
	n_index = 0;
	b_line_played_once = false;
	a_vo_lines = a_nag_lines;  // initializing for scope
	level.n_nags_played = 0;	// we can check this later to see how many nags occurred
	level thread nag_evaluation( self, str_ender_flag, a_nag_lines.size );
	
	while ( !flag( str_ender_flag ) )
	{
		if ( !b_line_played_once || n_index == a_nag_lines.size )
		{
			// re-randomize if desired, then reset index count
			if ( should_randomize )
			{
				str_last_entry = a_vo_lines[a_vo_lines.size-1]; // TFLAME - 4/15/2011 - Want to make sure the last random entry is not the new first, so we avoid the same line repeated twice in a row
				for (i=0; i < 20; i++) // // if its tried 20 times it's probably just 1 line, avoid infinite loop
				{
					a_vo_lines = array_randomize( a_nag_lines );
					if (a_vo_lines[0] != str_last_entry ) 
						break;
				}
			}
			n_index = 0;
		}			
		
		if ( b_line_played_once || !b_play_line_now )
		{
			wait n_repeat_interval;
		}

		// runs a filter function if one is defined. it should return true or false for the check here
		if ( IsDefined( func_filter ) && !self [[ func_filter ]]())
		{
			continue;
		}				

//T6	self maps\_anim::anim_single( self, a_vo_lines[ n_index ] );  // if code API changes how dialogue is played, this will need updating
		if ( IsDefined( level.scr_sound[ self.animname ] ) &&
			 IsDefined( level.scr_sound[ self.animname ][ a_vo_lines[ n_index ] ] ) )
		{
			self dialogue_queue( a_vo_lines[ n_index ] );
		}
		else
		{
			thread add_dialogue_line( self.animname, a_vo_lines[ n_index ], "white" );
		}

		b_line_played_once = true;
		n_index++;
	}
}


//
//	Checks to see how many nag lines were played and adjusts Price's faction accordingly
nag_evaluation( e_ent, str_ender_flag, n_nag_size )
{
	// wait until the nag thread is done
	waittill_any_ents( e_ent, "_stop_nag_lines", level, str_ender_flag );
	
	// He likes you if he doesn't have to nag
	if ( level.n_nags_played == 0 )
	{
		adjust_price_attitude( 1 );
	}
	// He gets mad if he has to nag you a lot
	else if ( level.n_nags_played >= n_nag_size )
	{
		adjust_price_attitude( -1 );
	}
	level.n_nags_played = 0;
}


//
//	Adjusts 
adjust_price_attitude( n_amount )
{
	level.n_price_attitude += n_amount;
}

//called from castle_main to set up all the turrets in the level
dual_stinger_setup()
{
	stingers = GetEntArray( "stinger_emplacement", "targetname" );
	foreach ( stinger in stingers )
	{
		stinger MakeTurretSolid();
		stinger thread _dual_stinger_overlay();
	}
}

//called on each turret handling when a player gets on and off
_dual_stinger_overlay()
{
	self.n_ammo_count = 2;
	self.n_cooldown = 2.5;
	
	while( true )
	{
		//wait until the player is using a turret
		while( !level.player IsUsingTurret() )
		{
			waitframe();
		}
		
		turretOwner = self GetTurretOwner();
		
		//check if this turret it the one being
		if( IsDefined( turretOwner ) && IsPlayer( turretOwner ) )
		{
			//create all hud elements
			manual_r 	= _dual_stinger_create_hud( 0, 0, "right", "bottom", "stinger_emplacement_override_red", 100, 100, 0 );
			manual_w 	= _dual_stinger_create_hud( 0, 0, "right", "bottom", "stinger_emplacement_override_white", 100, 100, 0 );
			status		= _dual_stinger_create_hud( 0, 0, "center", "bottom", "stinger_emplacement_ready", 128, 64, 1 );
			stinger_1	= _dual_stinger_create_hud( 0, -40, "left", "bottom", "stinger_emplacement_missile_full", 64, 16, 1 );
			stinger_2	= _dual_stinger_create_hud( 0, -20, "left", "bottom", "stinger_emplacement_missile_full", 64, 16, 1 );
			
			self thread _dual_stinger_manual_text( manual_w, manual_r );
			self thread _dual_stinger_update_ammo( stinger_1, stinger_2, self.n_ammo_count );
			
			//make sure it doesn't say ready if it is out of ammo
			if ( self.n_ammo_count == 0 )
			{
				status SetShader( "stinger_emplacement_loading", 128, 64 );
				self thread _dual_stinger_loading_blink( status );
				self TurretFireDisable();
			}
			else
			{
				self thread _dual_stinger_fire( turretOwner, stinger_1, stinger_2, status );
				self TurretFireEnable();
			}
			
			//hide all normal hud elements
			SetSavedDvar( "compass", "0" );
			SetSavedDvar( "ui_hidemap", "1" );
			SetSavedDvar( "ammoCounterHide", "1" );
			SetSavedDvar( "actionSlotsHide", "1" );
			SetSavedDvar( "hud_showstance", "0" );
			
			//wait until the player gets off the turret			
			while ( turretOwner IsUsingTurret() )
			{
				waitframe();
			}
						
			//kill all related threads
			self notify( "stop_dual_stinger" );

			//restore normal hud
			SetSavedDvar( "compass", "1" );
			SetSavedDvar( "ui_hidemap", "0" );
			SetSavedDvar( "ammoCounterHide", "0" );
			SetSavedDvar( "actionSlotsHide", "0" );
			SetSavedDvar( "hud_showstance", "1" );
			
			manual_r Destroy();
			manual_w Destroy();
			status Destroy();
			stinger_1 Destroy();
			stinger_2 Destroy();
		}
		waitframe();
	}
}

_dual_stinger_fire( turretOwner, stinger_1, stinger_2, status )
{
	self endon( "stop_dual_stinger" );
	
	while( true )
	{
		self waittill( "turret_fire" );
		
		Earthquake( 0.6, 0.5, self.origin, 200 );
					
		self.n_ammo_count--;
		
		self thread _dual_stinger_loading( status, self.n_cooldown );
		self thread _dual_stinger_update_ammo( stinger_1, stinger_2, self.n_ammo_count );
		
		if ( self.n_ammo_count == 0 )
		{
			self TurretFireDisable();
			self SetModel( "ctl_missile_emplacement" );
			wait 0.5;
			self useby( turretOwner );
			break;
		}
		else
		{
			self TurretFireDisable();
			wait self.n_cooldown;
			self TurretFireEnable();
		}
	}
}

_dual_stinger_create_hud( xOffset, yOffset, horzAlign, vertAlign, shaderName, shaderWidth, shaderHeight, alpha )
{
	newHud = NewHudElem();
	newHud.x = xOffset;
	newHud.y = yOffset;
	if( horzAlign != "fullscreen" )
	{
		newHud.alignX = horzAlign;
		newHud.aligny = vertAlign;
	}
	newHud.horzAlign = horzAlign;
	newHud.vertAlign = vertAlign;
	newHud.foreground = true;
	newHud SetShader( shaderName , shaderWidth, shaderHeight );
	newHud.alpha = alpha;
	
	return newHud;
}

_dual_stinger_update_ammo( stinger_1, stinger_2, n_ammo_count )
{
	switch( n_ammo_count )
	{
		case 0:
			stinger_1 SetShader( "stinger_emplacement_missile_empty" , 64, 16 );
			stinger_2 SetShader( "stinger_emplacement_missile_empty" , 64, 16 );
			break;
		case 1:
			stinger_1 SetShader( "stinger_emplacement_missile_empty" , 64, 16 );
			break;
		case 2:
			break;
	}
}

_dual_stinger_loading( status, time )
{
	self endon( "stop_dual_stinger" );
	
	status SetShader( "stinger_emplacement_loading", 128, 64 );
	self thread _dual_stinger_loading_blink( status );
	
	wait time;
	
	self notify( "stop_loading" );
	status SetShader( "stinger_emplacement_ready", 128, 64 );
	status.alpha = 1;
}

_dual_stinger_loading_blink( status )
{
	self endon( "stop_loading" );
	self endon( "stop_dual_stinger" );
	
	while( true )
	{
		status fade_over_time( 0, 1.0 );
		status fade_over_time( 1, 1.0 );
	}
}

_dual_stinger_manual_text( manual_w, manual_r )
{
	self endon( "stop_dual_stinger" );
	
	while( true )
	{
		manual_w.alpha = 0;
		manual_r.alpha = 1;	

		wait 1;

		manual_w.alpha = 1;
		manual_r.alpha = 0;	
		
		wait 1;
	}
}

hint_quick_fade()
{
	hintfade = 0.1;
	if ( IsDefined( level.hintElement ) )
	{
		level notify( "clearing_hints" );
		level.hintElement FadeOverTime( hintfade );
		level.hintElement.alpha = 0;
		wait( hintfade );
	}
}

stinger_fire_break_stealth()
{
	level endon ("courtyard_stealth_cleanup" );
	level endon( "_stealth_spotted" );
	
	self waittill("turret_fire");
	
	flag_set( "_stealth_spotted" );	
}

grenade_throw_break_stealth()
{
	level endon ("courtyard_stealth_cleanup" );
	
	level endon ( "_stealth_spotted" );

	self waittill_any("flashbang", "explode", "bulletwhizby", "bullethit", "damage", "grenade danger", "killed");
	self anim_stopanimscripted();
	flag_set( "_stealth_spotted" );
}

break_stealth_forgiving()
{
	level endon ("courtyard_stealth_cleanup" );
	//level endon ( "_stealth_spotted" );
	self endon ("death");
	
	self waittill_any("flashbang", "explode", "bulletwhizby", "bullethit", "damage", "grenade danger");
	
	self anim_stopanimscripted();
	wait 1.5;
	if (IsAlive(self))
	{
		flag_set( "_stealth_spotted" );
	}
	
}

/*
=============
///ScriptDocBegin
"Name: rain_overlay_alpha( <time> , <alpha>, <skipCap> )"
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
rain_overlay_alpha( time, alpha, skipCap )
{
	player = self;
	if ( !isplayer( player ) )
		player = level.player;
	
	if( !isdefined( alpha ) )
		alpha = 1;
	
	// skipcap lets us modify the overlay without setting a new cap
	if ( !isdefined( skipCap ) )
		level.blizzard_overlay_alpha_cap = alpha;
	
	overlay = get_rain_overlay( player );

	

		
	overlay[0].x = 0;
	overlay[0].y = 0;
	overlay[0] setshader( "overlay_rain", 640, 480);
	overlay[0].sort = 50;
	overlay[0].lowresbackground = false;
	overlay[0].alignX = "left";
	overlay[0].alignY = "top";
	overlay[0].alpha = 0.85;
	overlay[0].horzAlign = "fullscreen";
	overlay[0].vertAlign = "fullscreen";
	overlay[0] fadeovertime( time );
	overlay[0].alpha = alpha; 
	
	for(i = 1; i < overlay.size; i++)
	{
	
		//overlay[i].x = 0;
		//overlay[i].y = 0;
		
		random_overlay = random(level.rain_overlay);
	
		overlay[i].x = 0 +  RandomInt(360);
		overlay[i].y = 0 +  RandomInt(360);
		overlay[i] setshader( random_overlay, 256, 256);
		overlay[i].sort = 50;
		overlay[i].lowresbackground = false;
				
		
		
//		rand = randomint(100);
//		
//		if(rand < 33 )
//		{
			overlay[i].alignX = "left";
			overlay[i].alignY = "top";
//		}
//		else if(rand > 66)
//		{
//			overlay[i].alignX = "left";
//			overlay[i].alignY = "bottom";
//		}
//		else
//		{
//			overlay[i].alignX = "right";
//			overlay[i].alignY = "top";	
//		}
//		
		
		overlay[i].horzAlign = "fullscreen";
		overlay[i].vertAlign = "fullscreen";
		overlay[i].alpha = RandomFloatRange(0.15, 0.3);
		overlay[i] fadeovertime( time );
		overlay[i].alpha = alpha; 
		wait(0.8);
	}
	
	level.blizzard_overlay_alpha = alpha;
}

/*
=============
///ScriptDocBegin
"Name: rain_overlay_clear( <timer> )"
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
rain_overlay_clear( timer )
{
	if ( !isdefined( timer ) || !timer )
	{
		player = self;
		
		if ( !isplayer( player ) )
			player = level.player;
		
		overlay = get_rain_overlay( player );
		
		for(i = 0; i < overlay.size; i++)
		{
			overlay[0] destroy();
		}
		
		return;
	}
	
	rain_overlay_alpha( timer, 0 );
}

get_rain_overlay( player )
{
	if ( !isdefined( player.overlay_frozen ) )
	{
		player.overlay_frozen = [];
		player.overlay_frozen[0] = newClientHudElem( player );
		player.overlay_frozen[1] = newClientHudElem( player );
		player.overlay_frozen[2] = newClientHudElem( player );
		player.overlay_frozen[3] = newClientHudElem( player );
		player.overlay_frozen[4] = newClientHudElem( player );
//		player.overlay_frozen[5] = newClientHudElem( player );
//		player.overlay_frozen[6] = newClientHudElem( player );
//		player.overlay_frozen[7] = newClientHudElem( player );
	}
	return player.overlay_frozen;	
}

use_button_held()
{
	init_button_wrappers();

	if(!IsDefined(self._use_button_think_threaded))
	{
		self thread button_held_think(level.BUTTON_USE);
		self._use_button_think_threaded = true;
	}

	return self._holding_button[level.BUTTON_USE];
}

button_held_think(which_button)
{
	if (!IsDefined(self._holding_button))
	{
		self._holding_button = [];
	}
	
	self._holding_button[which_button] = false;
	
	time_started = 0;
	use_time = 0.5;

	while(1)
	{
		if(self._holding_button[which_button])
		{
			if(!self [[level._button_funcs[which_button]]]())
			{
				self._holding_button[which_button] = false;
			}
		}
		else
		{
			if(self [[level._button_funcs[which_button]]]())
			{
				if(time_started == 0)
				{
					time_started = GetTime();
				}

				if((GetTime() - time_started) > use_time)
				{
					self._holding_button[which_button] = true;
				}
			}
			else
			{
				if(time_started != 0)
				{
					time_started = 0;
				}
			}
		}

		wait(0.05);
	}
}

init_button_wrappers()
{
	if (!IsDefined(level._button_funcs))
	{
		level.BUTTON_USE	= 0;

		level._button_funcs[level.BUTTON_USE]		= ::use_button_pressed;

	}
}

use_button_pressed()
{
	return (self UseButtonPressed());
}


price_catch_up_nag(nag_time, check_flag)
{
	if (!IsDefined(level.catchup_nag_count))
	{
		level.catchup_nag_count = 0;
	}
	
	lines = [];
	//You're lagging behind Yuri...
	lines[0] = "castle_pri_laggingbehind";
	//Stop slowing me down.	
	lines[1] = "castle_pri_slowingme";
	//Keep falling behind, and you're on your own.	
	lines[2] = "castle_pri_onyourown";
		//I don't have time for this, Yuri.  Get over here.	
	lines[3] = "castle_pri_donthavetime";

	wait nag_time;
	
	if (!flag(check_flag))
	{
		if (!flag("_stealth_spotted"))
		{
			level.price dialogue_queue(lines[level.catchup_nag_count]);
		}
		level.catchup_nag_count++;
		if (level.catchup_nag_count >= lines.size)
		{
			level.catchup_nag_count = 0;
		}
		
		// keep nagging
		thread price_catch_up_nag(nag_time*1.5, check_flag);
	}
}

set_ents_visible( str_targetname, b_visible )
{
	a_e_ents = GetEntArray( str_targetname, "targetname" );
	if ( b_visible )
	{
		array_call( a_e_ents, ::Show );
	}
	else
	{
		array_call( a_e_ents, ::Hide );
	}
}
