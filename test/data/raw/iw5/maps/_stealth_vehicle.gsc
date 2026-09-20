#include common_scripts\utility;
#include maps\_utility;
#include maps\_anim;
#include maps\_specialops;
#include maps\_stealth_utility;
#include maps\_vehicle;
#include maps\_stealth_shared_utilities;

// ---------------------------------------------------------------------------------

flags_init()
{
	level._effect[ "lighthaze_snow_headlights" ]			= loadfx( "misc/lighthaze_snow_headlights" );
	level._effect[ "car_taillight_uaz_l" ]					= loadfx( "misc/car_taillight_uaz_l" );
	
	flag_init( "truck_guys_alerted" );
	flag_init( "jeep_blown_up" );
	flag_init( "jeep_stopped" );
}



increase_fov_when_player_is_near()
{
	self endon( "death" );
	self endon( "enemy" );

	while ( 1 )
	{
		if ( player_is_near() )
		{
			self.fovcosine = 0.01;
			return;
		}
		wait 0.5;
	}
}

player_is_near()
{
	foreach ( player in level.players )
	{
		if ( DistanceSquared( self.origin, player.origin ) < squared( self.footstepDetectDistSprint ) )
			return true;
	}
	
	return false;
}


stealth_truck_think()
{

//	level.truck_patrol thread play_loop_sound_on_entity( "cliffhanger_truck_music" );
	thread base_truck_think();
	thread truck_headlights();
	self waittill( "death" );
	flag_set( "jeep_blown_up" );
//	level.truck_patrol notify( "stop sound" + "cliffhanger_truck_music" );
}

base_truck_guys_think()
{
	self endon( "death" );

	//if ( flag( "_stealth_spotted" ) || self ent_flag( "_stealth_attack" ) )
	//	return;
		
	level endon( "_stealth_spotted" );
	self endon( "_stealth_attack" );

	self ent_flag_init( "jumped_out" );
	self thread truck_guys_think_jumpout();

	corpse_array = [];
	corpse_array[ "saw" ] 	 = ::truck_guys_reaction_behavior;
	corpse_array[ "found" ] = ::truck_guys_reaction_behavior;

	alert_array = [];
	alert_array[ "warning1" ] = ::truck_guys_reaction_behavior;
	alert_array[ "warning2" ] = ::truck_guys_reaction_behavior;
	alert_array[ "attack" ] = ::truck_alert_level_attack;

	awareness_array = [];
	awareness_array[ "explode" ] = ::truck_guys_no_enemy_reaction_behavior;
	awareness_array[ "heard_scream" ] = ::truck_guys_no_enemy_reaction_behavior;
	awareness_array[ "doFlashBanged" ] = ::truck_guys_no_enemy_reaction_behavior;

	self maps\_stealth_shared_utilities::ai_create_behavior_function( "animation", "wrapper", ::truck_animation_wrapper );
	self stealth_threat_behavior_custom( alert_array );
	self stealth_corpse_behavior_custom( corpse_array );
	foreach ( key, value in awareness_array )
		self maps\_stealth_event_enemy::stealth_event_mod( key, value );

	self ent_flag_set( "_stealth_behavior_reaction_anim" );
}


truck_guys_base_search_behavior( node )
{
	self endon( "_stealth_enemy_alert_level_change" );
	level endon( "_stealth_spotted" );
	self endon( "_stealth_attack" );
	self endon( "death" );
	self endon( "pain_death" );

	self thread base_truck_guys_attacked_again();

	self.disablearrivals = false;
	self.disableexits = false;

	distance = distance( node.origin, self.origin );

	self setgoalnode( node );
	self.goalradius = distance * .5;

	wait 0.05;	// because stealth system keeps clearing run anim on every enemy_animation_wrapper
	self set_generic_run_anim( "_stealth_patrol_cqb" );
	self waittill( "goal" );

	if ( !flag( "_stealth_spotted" ) && ( !isdefined( self.enemy ) || !self cansee( self.enemy ) ) )
	{
		set_search_walk();
		
		self maps\_stealth_shared_utilities::enemy_runto_and_lookaround( node );
	}
}

base_truck_guys_attacked_again()
{
	self endon( "death" );
	self endon( "_stealth_attack" );
	level endon( "_stealth_spotted" );
		
	wait 2;
		
	self waittill( "_stealth_bad_event_listener" );
	
	self maps\_stealth_shared_utilities::enemy_reaction_state_alert();

	self ent_flag_set( "not_first_attack" );
}


set_search_walk()
{
	self disable_cqbwalk();

	self set_generic_run_anim( "patrol_cold_gunup_search", true );

	self.disablearrivals = true;
	self.disableexits = true;
}




truck_guys_think_jumpout()
{
	self endon( "death" );
	self endon( "pain_death" );

	while ( 1 )
	{
		self waittill( "jumpedout" );
		self enemy_set_original_goal( self.origin );
		self.got_off_truck_origin = self.origin;
		self ent_flag_set( "jumped_out" );

		self waittill( "enteredvehicle" );
		wait .15;
		self ent_flag_clear( "jumped_out" );
		self ent_flag_set( "_stealth_behavior_reaction_anim" );
	}
}

truck_animation_wrapper( type )
{
	self endon( "death" );
	self endon( "pain_death" );

	flag_set( "truck_guys_alerted" );

	self ent_flag_wait( "jumped_out" );

	self maps\_stealth_shared_utilities::enemy_animation_wrapper( type );
}

truck_guys_reaction_behavior( type )
{
	self endon( "death" );
	self endon( "pain_death" );
	level endon( "_stealth_spotted" );	
	self endon( "_stealth_attack" );

	flag_set( "truck_guys_alerted" );
	
	self ent_flag_wait( "jumped_out" );

	if ( !flag( "truck_guys_alerted" ) )
		return;
	if ( flag_exist( "truck_guys_not_going_back" ) && flag( "truck_guys_not_going_back" ) )
		return;

	if ( !flag( "_stealth_spotted" ) && !self ent_flag( "_stealth_attack" ) )
	{
		player = get_closest_player( self.origin );
		node = maps\_stealth_shared_utilities::enemy_find_free_pathnode_near( player.origin, 1500, 128 );

		if ( isdefined( node ) )
			self thread truck_guys_base_search_behavior( node );
	}
	
	spotted_flag = self group_get_flagname( "_stealth_spotted" );
	if ( flag( spotted_flag ) )
		self flag_waitopen( spotted_flag );
	else
		self waittill( "normal" );		
}


truck_guys_no_enemy_reaction_behavior( type )
{
	self endon( "death" );
	self endon( "pain_death" );
	level endon( "_stealth_spotted" );	
	self endon( "_stealth_attack" );

	flag_set( "truck_guys_alerted" );
	
	self ent_flag_wait( "jumped_out" );

	if ( !flag( "truck_guys_alerted" ) )
		return;
	if ( flag_exist( "truck_guys_not_going_back" ) && flag( "truck_guys_not_going_back" ) )
		return;

	if ( !flag( "_stealth_spotted" ) && !self ent_flag( "_stealth_attack" ) )
	{
		origin = self._stealth.logic.event.awareness_param[ type ];

		node = self maps\_stealth_shared_utilities::enemy_find_free_pathnode_near( origin, 300, 40 );

		self thread maps\_stealth_shared_utilities::enemy_announce_wtf();

		if ( isdefined( node ) )
			self thread truck_guys_base_search_behavior( node );
	}

	spotted_flag = self group_get_flagname( "_stealth_spotted" );
	if ( flag( spotted_flag ) )
		self flag_waitopen( spotted_flag );
	else
		self waittill( "normal" );		
}


truck_alert_level_attack( enemy )
{
	self endon( "death" );
	self endon( "pain_death" );

	flag_set( "truck_guys_alerted" );
	self ent_flag_wait( "jumped_out" );

	// do something here?
}

set_alert_cold_patrol_anims()
{
	self.patrol_walk_anim = "patrol_cold_gunup";
	self.patrol_walk_twitch = "patrol_gunup_twitch_weights";
}

wait_reaction_time()
{
	//200 = 0, 700 = .5
	d = distance( self.origin, ( get_closest_player( self.origin ) ).origin );
	t = ( d - 200)/1000;
	t = clamp( t, 0, 0.5 );
	wait t;
	println( "---------reaction time: " + t );
}







base_truck_think()
{
	self endon( "death" );

	self thread dialog_truck_coming();
	self thread dialog_jeep_stopped();
	
	self thread unload_and_attack_if_stealth_broken_and_close();

	flag_wait( "truck_guys_alerted" );
	guys = get_living_ai_array( "truck_guys", "script_noteworthy" );
	
	if( guys.size == 0 )
	{
		self Vehicle_SetSpeed( 0, 15 );
		return;
	}
	
	screamer = random( guys );
	screamer maps\_stealth_shared_utilities::enemy_announce_wtf();

	self waittill( "safe_to_unload" );
	self Vehicle_SetSpeed( 0, 15 );
	wait 1;
	self maps\_vehicle::vehicle_unload();
	
	flag_set( "jeep_stopped" );
}

unload_and_attack_if_stealth_broken_and_close()
{	
	self endon( "truck_guys_alerted" );
	
	while( 1 )
	{
		flag_wait( "_stealth_spotted" );
		foreach( player in level.players )
			thread waittill_player_in_range( player );
		self waittill( "player_in_range" );
		if( !flag( "_stealth_spotted" ) )
			continue;
		else
			break;
	}
	flag_set( "truck_guys_alerted" );
}

waittill_player_in_range( player )
{
	self endon( "player_in_range" );

	player waittill_entity_in_range( self, 800 );

	self notify( "player_in_range" );
}

truck_headlights()
{
	//level.truck_patrol maps\_vehicle::lights_on( "headlights" );
	PlayFXOnTag( level._effect[ "lighthaze_snow_headlights" ], self, "TAG_LIGHT_RIGHT_FRONT" );
	PlayFXOnTag( level._effect[ "lighthaze_snow_headlights" ], self, "TAG_LIGHT_LEFT_FRONT" );
 	//level.truck_patrol maps\_vehicle::lights_on( "brakelights" );

	//taillights 
	PlayFXOnTag( level._effect[ "car_taillight_uaz_l" ], self, "TAG_LIGHT_LEFT_TAIL" );
	PlayFXOnTag( level._effect[ "car_taillight_uaz_l" ], self, "TAG_LIGHT_RIGHT_TAIL" );
 	
 	self waittill ( "death" );
 	
 	if( isdefined( self ) )
	 	delete_truck_headlights();
}	
 
delete_truck_headlights()
{
	StopFXOnTag( level._effect[ "lighthaze_snow_headlights" ], self, "TAG_LIGHT_RIGHT_FRONT" );
 	StopFXOnTag( level._effect[ "lighthaze_snow_headlights" ], self, "TAG_LIGHT_LEFT_FRONT" );
	StopFXOnTag( level._effect[ "car_taillight_uaz_l" ], self, "TAG_LIGHT_LEFT_TAIL" );
	StopFXOnTag( level._effect[ "car_taillight_uaz_l" ], self, "TAG_LIGHT_RIGHT_TAIL" );
}

dialog_truck_coming()
{
	level endon( "special_op_terminated" );
	level endon( "jeep_stopped" );
	level endon( "jeep_blown_up" );

	first_time = true;
	while ( 1 )
	{
		self waittill_player_in_truck_range();
		truck_coming = within_fov( self.origin, self.angles, self.close_player.origin, Cos( 45 ) );
		if ( truck_coming )
		{
			if ( !first_time && cointoss() )
			{
				//PRICE: The truck is coming back.
				radio_dialogue( "cliff_pri_truckcomingback" );
			}
			else
			{
				//PRICE: The truck is coming.
				radio_dialogue( "cliff_pri_truckiscoming" );
			}
			first_time = false;
			wait 10;
		}
		wait 1;
	}
}

waittill_player_in_truck_range()
{
	self.close_player = undefined;
	foreach ( player in level.players )
		player thread watch_for_truck( self );
		
	level waittill( "player_in_truck_range" );
}

watch_for_truck( truck )
{
	level endon( "player_in_truck_range" );

	truck waittill_entity_in_range( self, 1200 );
	truck.close_player = self;
	level notify( "player_in_truck_range" );
}

dialog_jeep_stopped()
{
	level endon( "special_op_terminated" );
	self waittill( "unloading" );

	if ( flag( "_stealth_spotted" ) )
		return;

	//Heads up, the truck just stopped.	
	radio_dialogue( "cliff_pri_headsup" );

	if ( flag( "_stealth_spotted" ) )
		return;

	//Four tangos just got out and are looking around.	
	radio_dialogue( "cliff_pri_lookingaround" );
}

