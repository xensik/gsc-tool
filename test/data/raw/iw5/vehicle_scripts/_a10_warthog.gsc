#include maps\_utility;
#include common_scripts\utility;
#include maps\_vehicle_aianim;
#include maps\_vehicle;
#using_animtree( "vehicles" );
main( model, type, classname )
{
	build_template( "a10_warthog", model, type, classname );
	build_localinit( ::init_local );

	build_deathmodel( "vehicle_a10_warthog" );

	//special for a10_warthog/////
	level._effect[ "engineeffect" ]				= loadfx( "fire/a10_warthog_afterburner" );
	level._effect[ "afterburner" ]				= loadfx( "fire/a10_warthog_afterburner_ignite" );
	level._effect[ "contrail" ]					= loadfx( "smoke/a10_warthog_jet_contrail" );
	level._effect[ "sonicboom" ]				= loadfx( "smoke/a10_warthog_sonic_boom" );
	////////////////////////

	build_deathfx( "explosions/large_vehicle_explosion", undefined, "explo_metal_rand", undefined, undefined, undefined, undefined, undefined, undefined, 0 );
	build_life( 999, 500, 1500 );
	build_rumble( "mig_rumble", 0.1, 0.2, 11300, 0.05, 0.05 );
	build_treadfx();
	build_team( "allies" );

	randomStartDelay = randomfloatrange( 0, 1 );
	lightmodel = get_light_model( model, classname );
	build_light( lightmodel, "wingtip_green", 	"TAG_LEFT_WINGTIP", 	"misc/aircraft_light_wingtip_green", 	"running", 		randomStartDelay );
	build_light( lightmodel, "tail_green", 		"TAG_LEFT_TAIL", 		"misc/aircraft_light_wingtip_green", 	"running", 		randomStartDelay );
	build_light( lightmodel, "wingtip_red", 		"TAG_RIGHT_WINGTIP", 	"misc/aircraft_light_wingtip_red", 		"running", 		randomStartDelay );
	build_light( lightmodel, "tail_red", 		"TAG_RIGHT_TAIL", 		"misc/aircraft_light_wingtip_red", 		"running", 		randomStartDelay );
	build_light( lightmodel, "white_blink", 		"TAG_LIGHT_BELLY", 		"misc/aircraft_light_white_blink", 		"running", 		randomStartDelay );
	build_light( lightmodel, "landing_light01", 	"TAG_LIGHT_LANDING01", 	"misc/light_mig29_landing", 			"landing", 		0.0 );

}

init_local()
{
	//thread playEngineEffects();
	thread playConTrail();
	thread landing_gear_up();
	thread play_sonic_boom();
	maps\_vehicle::lights_on( "running" );
}

#using_animtree( "vehicles" );
set_vehicle_anims( positions )
{
	ropemodel = "rope_test";
	precachemodel( ropemodel );
	return positions;
}

landing_gear_up()
{
	self UseAnimTree( #animtree );
	self setanim( %mig_landing_gear_up );
}



#using_animtree( "generic_human" );

setanims()
{
	positions = [];
	for ( i = 0;i < 1;i++ )
		positions[ i ] = spawnstruct();

	return positions;
}

playEngineEffects()
{
	self endon( "death" );
	self endon( "stop_engineeffects" );

	self ent_flag_init( "engineeffects" );
	self ent_flag_set( "engineeffects" );
	engineeffects = getfx( "engineeffect" );

	for ( ;; )
	{
		self ent_flag_wait( "engineeffects" );
		playfxontag( engineeffects, self, "tag_engine_right" );
		playfxontag( engineeffects, self, "tag_engine_left" );
		self ent_flag_waitopen( "engineeffects" );
		StopFXOnTag( engineeffects, self, "tag_engine_left" );
		StopFXOnTag( engineeffects, self, "tag_engine_right" );
	}
}

playAfterBurner()
{
	//After Burners are pretty much like turbo boost. They don't use them all the time except when 
	//bursts of speed are needed. Needs a cool sound when they're triggered. Currently, they are set
	//to be on all the time, but it would be cool to see them engauge as they fly away.
	self endon( "death" );
	self endon( "stop_afterburners" );

	self ent_flag_init( "afterburners" );
	self ent_flag_set( "afterburners" );
	afterburners = getfx( "afterburner" );

	for ( ;; )
	{
		self ent_flag_wait( "afterburners" );
		playfxontag( afterburners, self, "tag_engine_right" );
		playfxontag( afterburners, self, "tag_engine_left" );
		self ent_flag_waitopen( "afterburners" );
		StopFXOnTag( afterburners, self, "tag_engine_left" );
		StopFXOnTag( afterburners, self, "tag_engine_right" );
	}
}

play_sonic_boom()
{
	self endon( "death" );
	self endon( "stop_afterburners" );

	self ent_flag_init( "afterburners" );
	self ent_flag_set( "afterburners" );
	sonicboom = getfx( "sonicboom" );

	for ( ;; )
	{
		self ent_flag_wait( "afterburners" );
		playfxontag( sonicboom, self, "TAG_GUN" );
		self ent_flag_waitopen( "afterburners" );
		StopFXOnTag( sonicboom, self, "TAG_GUN" );
	}
}

playConTrail()
{
	
	
	//This is a geoTrail effect that loops forever. It has to be enabled and disabled while playing as 
	//one effect. It can't be played in a wait loop like other effects because a geo trail is one 
	//continuous effect. ConTrails should only be played during high "G" or high speed maneuvers.
	tag1 = add_contrail( "TAG_RIGHT_WINGTIP", 1 );
	tag2 = add_contrail( "TAG_LEFT_WINGTIP", -1 );
	contrail = getfx( "contrail" );
	
	self endon( "death" );	


	ent_flag_init( "contrails" );	
	ent_flag_set( "contrails" );
	for ( ;; )
	{
		ent_flag_wait( "contrails" );
		playfxontag( contrail, tag1, "tag_origin" );
		playfxontag( contrail, tag2, "tag_origin" );
		ent_flag_waitopen( "contrails" );
		stopfxontag( contrail, tag1, "tag_origin" );
		stopfxontag( contrail, tag2, "tag_origin" );
	}
	
	
//	playfxontag( level._effect[ "contrail" ], self, "tag_engine_right" );
//	playfxontag( level._effect[ "contrail" ], self, "tag_engine_left" );
}

add_contrail( fx_tag_name, offset )
{
	// translate the posts into the proper positions for the effect
	fx_tag = spawn_tag_origin();
	fx_tag.origin = self getTagOrigin( fx_tag_name );
	fx_tag.angles = self getTagAngles( fx_tag_name );
	ent = spawnstruct();
	ent.entity = fx_tag;
	ent.forward = -156;
	ent.up = 0;
	ent.right = 1 * offset;
	ent.yaw = 0;
	ent.pitch = 0;
	ent translate_local();
	fx_tag LinkTo( self, fx_tag_name );
	return fx_tag;
}

playerisclose( other )
{
	infront = playerisinfront( other );
	if ( infront )
		dir = 1;
	else
		dir = -1;
	a = flat_origin( other.origin );
	b = a + ( anglestoforward( flat_angle( other.angles ) ) * ( dir * 100000 ) );
	point = pointOnSegmentNearestToPoint( a, b, level.player.origin );
	dist = distance( a, point );
	if ( dist < 3000 )
		return true;
	else
		return false;
}

playerisinfront( other )
{
	forwardvec = anglestoforward( flat_angle( other.angles ) );
	normalvec = vectorNormalize( flat_origin( level.player.origin ) - other.origin );
	dot = vectordot( forwardvec, normalvec );
	if ( dot > 0 )
		return true;
	else
		return false;
}

plane_sound_node()
{
	self waittill( "trigger", other );
	other endon( "death" );
	self thread plane_sound_node();// spawn new thread for next plane that passes through this pathnode
	other thread play_loop_sound_on_entity( "veh_a10_warthog_dist_loop" );
	while ( playerisinfront( other ) )
		wait .05;
	wait .5;// little delay for the boom
	other thread play_sound_in_space( "veh_a10_warthog_sonic_boom" );
	other waittill( "reached_end_node" );
	other stop_sound( "veh_a10_warthog_dist_loop" );
	other delete();
}

plane_bomb_node()
{
	level._effect[ "plane_bomb_explosion1" ]			 = loadfx( "explosions/airlift_explosion_large" );
	level._effect[ "plane_bomb_explosion2" ]			 = loadfx( "explosions/tanker_explosion" );
	self waittill( "trigger", other );
	other endon( "death" );
	self thread plane_bomb_node();// spawn new thread for next plane that passes through this pathnode

	// get array of targets
	aBomb_targets = getentarray( self.script_linkTo, "script_linkname" );
	assertEx( isdefined( aBomb_targets ), "Plane bomb node at " + self.origin + " needs to script_linkTo at least one script_origin to use as a bomb target" );
	assertEx( aBomb_targets.size > 1, "Plane bomb node at " + self.origin + " needs to script_linkTo at least one script_origin to use as a bomb target" );

	//sort array of targets from nearest to furthest to determine order of bombing
	aBomb_targets = get_array_of_closest( self.origin, aBomb_targets, undefined, aBomb_targets.size );
	iExplosionNumber = 0;

	wait randomfloatrange( .3, .8 );
	for ( i = 0;i < aBomb_targets.size;i++ )
	{
		iExplosionNumber++ ;
		if ( iExplosionNumber == 3 )
			iExplosionNumber = 1;
		aBomb_targets[ i ] thread play_sound_on_entity( "airstrike_explosion" );
		//aBomb_targets[i] thread play_sound_on_entity( "rocket_explode_sand" );
		playfx( level._effect[ "plane_bomb_explosion" + iExplosionNumber ], aBomb_targets[ i ].origin );
		wait randomfloatrange( .3, 1.2 );
	}
}

plane_bomb_cluster()
{
	/*-----------------------
	WAIT FOR PLANE TO HIT NODE
	-------------------------*/		
	self waittill( "trigger", other );
	other endon( "death" );
	plane = other;
	plane thread plane_bomb_cluster();// spawn new thread for next plane that passes through this pathnode

	/*-----------------------
	SPAWN A BOMB MODEL
	-------------------------*/				
	bomb = spawn( "script_model", plane.origin - ( 0, 0, 100 ) );
	bomb.angles = plane.angles;
	bomb setModel( "projectile_cbu97_clusterbomb" );

	/*-----------------------
	LAUNCH FROM PLANE UNTIL CLOSE TO GROUND
	-------------------------*/		
	vecForward = ( anglestoforward( plane.angles ) * 2 );
	vecUp = ( anglestoup( plane.angles ) * -0.2 );	// invert the up angles
	vec = [];
	for ( i = 0; i < 3; i++ )
		vec[ i ] = ( vecForward[ i ] + vecUp[ i ] ) / 2;
	vec = ( vec[ 0 ], vec[ 1 ], vec[ 2 ] );
	vec = ( vec * 7000 );
	bomb moveGravity( vec, 2.0 );
	wait( 1.2 );

	newBomb = spawn( "script_model", bomb.origin );
	newBomb setModel( "tag_origin" );
	newBomb.origin = bomb.origin;
	newBomb.angles = bomb.angles;
	wait( 0.05 );

	bomb delete();
	bomb = newBomb;

	/*-----------------------
	PLAY FX ON INVISIBLE BOMB
	-------------------------*/	
	bombOrigin = bomb.origin;
	bombAngles = bomb.angles;
	playfxontag( level.airstrikefx, bomb, "tag_origin" );

	wait 1.6;
	repeat = 12;
	minAngles = 5;
	maxAngles = 55;
	angleDiff = ( maxAngles - minAngles ) / repeat;

	for ( i = 0; i < repeat; i++ )
	{
		traceDir = anglesToForward( bombAngles + ( maxAngles - ( angleDiff * i ), randomInt( 10 ) - 5, 0 ) );
		traceEnd = bombOrigin + ( traceDir * 10000 );
		trace = bulletTrace( bombOrigin, traceEnd, false, undefined );

		traceHit = trace[ "position" ];

		radiusDamage( traceHit + ( 0, 0, 16 ), 512, 400, 30 );// targetpos, radius, maxdamage, mindamage

		if ( i%3 == 0 )
		{
			thread play_sound_in_space( "airstrike_explosion", traceHit );
			playRumbleOnPosition( "artillery_rumble", traceHit );
			earthquake( 0.7, 0.75, traceHit, 1000 );
		}

		wait( 0.75 / repeat );
	}
	wait( 1.0 );
	bomb delete();

}

stop_sound( alias )
{
	self notify( "stop sound" + alias );
}


/*QUAKED script_vehicle_a10_warthog (1 0 0) (-16 -16 -24) (16 16 32) USABLE SPAWNER

This will be added to your precache script when compile with Repackage Zone/Script:

vehicle_scripts\_a10_warthog::main( "vehicle_a10_warthog", undefined, "script_vehicle_a10_warthog" );

These will be added to your levels CSV when compile with Repackage Zone/Script:

include,vehicle_a10_warthog
sound,vehicle_a10_warthog,vehicle_standard,all_sp


defaultmdl="vehicle_a10_warthog"
default:"vehicletype" "a10_warthog"
default:"script_team" "allies"
*/
