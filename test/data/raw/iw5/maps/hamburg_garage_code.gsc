#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;
#include maps\hamburg_code;

ORIGIN_ZERO = ( 0, 0, 0 );

//---------------------------------------------------------
// Swinging Lights Section
//---------------------------------------------------------
swing_light_org_think_hunted()
{
	swing_light_org_think( true );
}

swing_light_org_think( do_hunted_style )
{
	if ( !IsDefined( do_hunted_style ) )
		do_hunted_style = false;
	lamp = spawn_anim_model( "lamp" );
	
	yaw = RandomFloatRange( -30, 30 );
	
	lamp AddYaw( RandomFloatRange( 1, 360 ) );
	
	
	lamp.origin = self.origin;
	
	if( !isdefined( level.swinging_lamps ) )
		level.swinging_lamps = [];
		
	level.swinging_lamps[ level.swinging_lamps.size ] = lamp;

	if( do_hunted_style )
	{
		light = lamp spot_light( "hamburg_garage_spotlIght", "hamburg_garage_spotlight_cheap", "j_hanging_light_04", lamp );
	}
	else
	{
		light = swing_lamp_get_nearby_primary( lamp );
		if( isdefined( light ) )
		{
			linkent = spawn_tag_origin();
			linkent LinkTo( lamp, "J_Hanging_Light_END", ORIGIN_ZERO, ORIGIN_ZERO );
			light thread manual_linkto( linkent );
			PlayFXOnTag( getfx( "hamburg_garage_spotlight_cheap" ) , linkent, "tag_origin" );
		}
	}
	
	lamp.animname = "lamp";// uses one set of anims
	lamp DontCastShadows();

//	lamp thread lamp_animates( self );
}

swing_lamp_get_nearby_primary( lamp )
{
	endorg = lamp GetTagOrigin( "J_Hanging_Light_END" );
	
	lights = GetEntArray( "lamp_primary", "targetname" );
	foreach( light in lights )
		if( distance( light.origin, endorg ) < 15 )
			return light;
}

lamps_swing_from_shot()
{
	while ( true )
	{
		level waittill ( "swing", other );
		foreach( lamp in level.swinging_lamps )
			lamp thread lamp_animates( other );
	}
}

swing_light_org_off_think()
{
	lamp = spawn_anim_model( "lamp_off" );
	lamp thread lamp_animates();
}

lamp_animates( other )
{
	self notify ( "lamp_animates" );
	self endon ( "lamp_animates" );

	childthread lamp_rotates_yaw();
	
	dist = distance( self.origin, other.origin ); 
	
	weight = 1;
	anime = self getanim( "swing_aggro" );
	if( dist > 800 )
	{
		anime = self getanim( "swing" );

		max_dist = 1500 - 800;
		dist -= 800;
		weight = 1 - ( dist / max_dist );
	}

	if ( weight <= 0 )
	{
		return;
	}
	
	anim_length = GetAnimLength( anime );
	self ClearAnim(  self getanim( "swing_root" ), 0.2 );
	self SetAnimRestart( anime, weight, 0.3, 1 );
	wait anim_length;
	
	self ClearAnim( self getanim( "swing_root" ), 0.4 );
}

lamp_rotates_yaw()
{
	if ( !IsDefined( self.yawent ) )
		self.yawent = spawn_tag_origin();
	
	ent = self.yawent;	

	for ( ;; )
	{
		yaw = RandomFloatRange( -30, 30 );
		ent AddYaw( yaw );
		time = RandomFloatRange( 0.5, 1.5 );
		self RotateTo( ent.angles, time, time * 0.4, time * 0.4 );
		wait( time );
	}
}



//---------------------------------------------------------
// PostSpawn Section
//---------------------------------------------------------
postspawn_player_tank_garage_ai()
{
	self.targetname = "player_tank_garage_ai";

	if ( IsDefined( self.target ) )
	{
		volume = GetEnt( self.target, "targetname" );
		self ai_set_goalvolume( volume );
	}
}

//---------------------------------------------------------
// GoalVolume Section
//---------------------------------------------------------
ai_goalvolume_thread( noteworthy, tank )
{
	volume = GetEnt( noteworthy, "script_noteworthy" );
	start_volume = volume;

	// Init volumes
	num = 0;
	while ( 1 )
	{
		volume.script_index = num;
		num++;

		if ( !IsDefined( volume.target ) )
		{
			break;
		}

		volume = GetEnt( volume.target, "targetname" );
	}

	volume = start_volume;

	if ( tank == level.player_tank )
	{
		ai_targetname = "player_tank_garage_ai";
	}
	else
	{
		ai_targetname = "hero_tank_garage_ai";
	}

	while ( 1 )
	{
		tank ent_flag_wait( volume.script_flag_wait );

		if ( !IsDefined( volume.target ) )
		{
			return;
		}

		volume = GetEnt( volume.target, "targetname" );

		ais = GetEntArray( ai_targetname, "targetname" );
		ais = SortByDistance( ais, volume.origin );
		ais = array_reverse( ais );

		foreach ( ai in ais )
		{
			if ( !IsDefined( ai ) )
			{
				continue;
			}

			if ( !IsAlive( ai ) )
			{
				continue;
			}

			ai ai_set_goalvolume( volume );
			volume script_delay();
		}		
	}
}

ai_set_goalvolume( volume )
{
	if ( IsDefined( self.goal_volume ) )
	{
		if ( self.goal_volume.script_index >= volume.script_index )
		{
			return;
		}
	}

	self.ignoreall = true;
	self delaythread( 3, ::set_ignoreall, false );

	self SetGoalVolumeAuto( volume );
	self.goal_volume = volume;
}

//---------------------------------------------------------
// Extra Tank Functions
//---------------------------------------------------------
both_tank_flag_wait( msg )
{
	level.hero_tank ent_flag_wait( msg );
	level.player_tank ent_flag_wait( msg );

	flag_set( msg );
}

tank_monster_clip()
{
	tanks = [ level.hero_tank, level.player_tank ];
	clips = GetEntArray( "tank_monster_clip", "targetname" );

	foreach ( idx, tank in tanks )
	{
		tank.monster_clip = clips[ idx ];
		
		origin = tank.origin + ( 0, 0, 32 );
		origin = origin + ( AnglesToForward( tank.angles ) * 160 );
		toucher = Spawn( "script_origin", origin );
		toucher LinkTo( tank );
		tank.toucher = toucher;

		level thread tank_monster_clip_think( tank );
	}
}

tank_monster_clip_think( tank )
{
	clip = tank.monster_clip;
	toucher = tank.toucher;
	disconnected = false;
	while ( 1 )
	{
		wait( 0.1 );

		if ( !IsDefined( tank ) ) 
		{
			break;
		}

		if ( !IsAlive( tank ) )
		{
			break;
		}

		is_touching = tank.toucher IsTouching( clip );

		if ( !is_touching )
		{
			clip.origin = tank.origin;
			clip.angles = tank.angles;

			clip DisconnectPaths();
		}
	}

	clip Delete();
	toucher Delete();
}

//---------------------------------------------------------
// RPG Vehicles
//---------------------------------------------------------
spawn_rpg_vehicle()
{
	self script_delay();

	vehicle = self spawn_vehicle_and_gopath();
	return vehicle;
}


postspawn_rpg_vehicle()
{
	self SetModel( "projectile_rpg7" );

	fx = getfx( "rpg_trail_garage" );
	PlayFXOnTag( fx, self, "tag_origin" );

	fx = getfx( "rpg_muzzle" );
	PlayFXOnTag( fx, self, "tag_origin" );

	self PlaySound( "weap_rpg_fire_npc" );

	if ( IsDefined( self.script_sound ) )
	{
		if ( IsDefined( self.script_wait ) )
		{
			self delaycall( self.script_wait, ::PlaySound, self.script_sound );
		}
		else
		{
			self PlaySound( self.script_sound );
		}
	}
	else
	{
		self PlayLoopSound( "weap_rpg_loop" );
	}

	self waittill( "reached_end_node" );
	self notify( "explode", self.origin );

	exploded = false;
	if ( IsDefined( self.script_exploder ) )
	{
		exploder( self.script_exploder );
		exploded = true;
	}
	else if ( IsDefined( self.currentnode ) )
	{
		// Be sure we have the last node
		lastnode = undefined;
		next = self.currentnode;
		while ( IsDefined( next ) )
		{
			lastnode = next;

			if ( !IsDefined( next.target ) )
			{
				break;
			}

			next = GetVehicleNode( next.target, "targetname" );
		}

		if ( IsDefined( lastnode.target ) )
		{
			struct = getstruct( lastnode.target, "targetname" );
			if ( IsDefined( struct ) )
			{
				level thread rpg_explosion( struct.origin, struct.angles );
				exploded = true;
			}
		}
	}

	if ( !exploded )
	{
		struct = SpawnStruct();
		struct.origin = self.origin;
		struct.angles = ( -90, 0, 0 );
		level thread rpg_explosion( struct.origin, struct.angles );
	}

	self Delete();
}

rpg_explosion( origin, angles )
{
	fx = getfx( "rpg_explode" );
	PlayFx( fx, origin, AnglesToForward( angles ), AnglesToUp( angles ) );
	RadiusDamage( origin, 200, 150, 50 );
	thread play_sound_in_space( "scn_hamburg_garage_rocket_exp", origin );
}