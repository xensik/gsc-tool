#include common_scripts\utility;
#include maps\_utility;
#include maps\_shg_common;
#include maps\castle_code;
#include maps\_stealth_utility;
#include maps\_anim;
#include maps\_vehicle;
#include maps\_audio;

CONTEXTUAL_MELEE_DIST_SQ = 130 * 130;
CONTEXTUAL_MELEE_DOT = .5;

SPOTLIGHT_DOT = .988;

// Start Functions	/////////////////////////////////////////////////////////////////////////////////////
start()
{
	//maps\castle_courtyard_activity::delete_player_clip();
	flag_set( "start_stealth_guard_patroll" );
	flag_set( "ruins_done" );
	
	spawn_vehicles_from_targetname( "courtyard_stealth_btr1" );
	spawn_vehicles_from_targetname( "courtyard_stealth_btr2" );
	
	array_spawn_targetname( "courtyard_stealth_guys", true );
	array_spawn_targetname( "courtyard_activity_guys", true );

	setup_price_for_start( "start_courtyard_stealth", ::price_stealth_think );
	move_player_to_start( "start_courtyard_stealth" );
	
	flag_set( "player_approaches_overlook" );
	flag_set( "stadium_lights_on" );
	flag_set( "courtyard_activity_done" );
	
	GetEnt( "startvista", "targetname" ) Hide();
	
	maps\castle_courtyard_activity::courtyard_scene_guards();
}

start_platform()
{
	spawn_vehicles_from_targetname( "courtyard_stealth_btr1" );
	spawn_vehicles_from_targetname( "courtyard_stealth_btr2" );
	
	array_spawn_targetname( "courtyard_stealth_guys", true );
	array_spawn_targetname( "courtyard_activity_guys", true );
	
	flag_set( "stealth_move_to_crawl_truck" );
	flag_set( "stealth_price_crawl_under_truck" );
	flag_set( "stealth_player_under_truck" );
	flag_set( "stadium_lights_on" );
	flag_set( "courtyard_activity_done" );
	flag_set( "ruins_done" );
	road_patrollers = GetEntArray( "road_patrollers", "script_noteworthy" );
	array_delete( road_patrollers );
	
	setup_price_for_start( "start_platform_crawl", ::price_stealth_think );
	move_player_to_start( "start_platform_crawl" );
	
	ai_melee = get_ai_when_spawned( "ai_motorpool_melee", "script_noteworthy" );
	ai_melee delayCall( 0.05, ::Delete );
	
	flag_set( "player_approaches_overlook" ); // turns on spotlight
	flag_set( "stealth_player_in_motorpool" );
	maps\_utility::vision_set_fog_changes( "castle_exterior", 0 );

	GetEnt( "startvista", "targetname" ) Hide();
	
	maps\castle_courtyard_activity::courtyard_scene_guards();
}

// Spawn Fucntions	/////////////////////////////////////////////////////////////////////////////////////

setup_spawn_funcs()
{
	array_spawn_function_targetname( "courtyard_stealth_guys",	::spawn_func_courtyard_stealth_guys );
	array_spawn_function_targetname( "courtyard_activity_guys",	::spawn_func_courtyard_activity_guys );
	
	array_spawn_function_targetname( "courtyard_stealth_btr1",	::spawn_func_btr1 );
	array_spawn_function_targetname( "courtyard_stealth_btr2",	::spawn_func_btr2 );
}

spawn_func_courtyard_stealth_guys()
{
	self thread setup_road_patrollers();
	add_cleanup_ent( self, "courtyard_stealth" );
}

setup_road_patrollers()
{
	if ( ( level.start_point != "platform_crawl" ) && ( IsDefined( self.script_noteworthy ) && ( self.script_noteworthy == "road_patrollers" ) ))
	{
		if( !IsDefined( level.road_patroller_1 ) )
		{
			level.road_patroller_1 = self;
			level.road_patroller_1.animname = "road_patroller_1";
			self thread stop_road_patrollers_conv();
		}
		else
		{
			level.road_patroller_2 = self;
			level.road_patroller_2.animname = "road_patroller_2";
			self thread stop_road_patrollers_conv();
			thread road_patrollers_conv();
		}
		
	}
}

stop_road_patrollers_conv()
{
	self waittill_either( "damage" , "death" );

	level notify( "stop_road_patrollers_conv" );
	if (IsDefined(self))
	{
		self StopSounds();
	}
}

road_patrollers_conv()
{
	level endon( "_stealth_spotted" );
	level endon( "stop_road_patrollers_conv" );
	
	flag_wait( "start_road_patrollers_conv" );

	//You're crazy... I don't get why you don't just go to the Medical Officer...
	level.road_patroller_1 dialogue_queue( "castle_ru3_crazy" );
	
	wait .5;
	
	//And tell him what?
	level.road_patroller_2 dialogue_queue( "castle_ru4_andtellhimwhat" );
	
	wait .5;
	
	//The truth!... Or - something close to the truth.
	level.road_patroller_1 dialogue_queue( "castle_ru3_thetruth" );
	
	wait .5;
	
	//What if he submits a report?... I'll be up on charges!
	level.road_patroller_2 dialogue_queue( "castle_ru4_submitsreport" );

	wait .5;
	
	//Better that, than what you're going through now. (beat) Is it stills changing color?
	level.road_patroller_1 dialogue_queue( "castle_ru3_betterthat" );
	
	wait .5;
	
	//Not any more... It's been blue since Tuesday.
	level.road_patroller_2 dialogue_queue( "castle_ru4_notanymore" );
	
	wait .5;
	
	//Maybe it's getting better...
	level.road_patroller_1 dialogue_queue( "castle_ru3_gettingbetter" );
	
	wait .5;
	
	//Thanks.
	level.road_patroller_2 dialogue_queue( "castle_ru4_thanks" );
	
	wait .5;
	
	//Or maybe it'll just fall off...
	level.road_patroller_1 dialogue_queue( "castle_ru3_justfalloff" );
}

spawn_func_courtyard_activity_guys()
{
	add_cleanup_ent( self, "courtyard_stealth" );
}

spawn_func_btr1()
{
	level.stealth_btr1 = self;
	level.stealth_btr1 mgoff();
	
	add_cleanup_ent( self, "courtyard_stealth" );
	
	self waittill("damage");
	flag_set( "_stealth_spotted" );
}

spawn_func_btr2()
{
	level.stealth_btr2 = self;
	level.stealth_btr2 mgoff();
	
	add_cleanup_ent( self, "courtyard_stealth" );
}

// Main Functions	/////////////////////////////////////////////////////////////////////////////////////

init_event_flags()
{
	//Objective flags
	flag_init( "objective_motorpool_melee" );
	flag_init( "objective_motorpool_melee_complete" );
	flag_init( "objective_bomb_plant" );
	flag_init( "platform_bomb_planted" );
	flag_init( "Price_Plant_bomb_instead" );
	flag_init("motorpool_melee_guards_leave");
	
	// Other flags
	flag_init("price_under_truck");
	flag_init("price_plants_truckc4");
	flag_init( "price_ready_to_catch" );
	flag_init( "animating_stealth_catch" );
	flag_init( "price_kill_melee_guard" );
	flag_init( "animating_stealth_melee" );
	flag_init( "platform_flashlight_passed" );
	flag_init( "guard_jumped_down" );
	flag_init( "price_run_up_security_office" );
	flag_init( "move_price_up_to_bomb_plant" );
	flag_init( "platform_guy_away" );
	flag_init( "player_planted_bomb" );
	flag_init( "platform_light_on" );
	
	//conv flags
	flag_init( "start_platform_guards_conv" );
	flag_init( "start_road_patrollers_conv" );
	
	// JZ - adding missing inits
	flag_init( "safe_prone_area" );
	flag_init( "safe_crouch_area" );
	flag_init( "player_in_backcrawl" );
	flag_init( "player_approaches_exit1" );
	
	// Dialog flags
	flag_init( "price_say_go" );
	flag_init( "price_say_some_timing" );
	flag_init( "price_say_your_turn" );
	flag_init( "price_say_wait_for_flashlight" );
	flag_init( "player_going_first");
	
}

main()
{
	/#
		iprintln( "courtyard stealth" );
//		level thread test();
	#/
	init_event();

	level.price.price_under_platform = false;
		
	level thread break_stealth();
	thread dont_shoot_the_trucks();

	level thread spotlight_road();
	
	flag_wait("courtyard_activity_done");

	battlechatter_off("axis");
//	if this thread ends, the security office thread starts which causes lots of bad problems.
//	level endon("_stealth_spotted");
	
	thread platform_mantle_handler();
	
	level.platform_bomb = GetEnt( "platform_bomb", "targetname" );
	level.platform_bomb Hide();
	
	level.price_truck_bomb = Getent("price_truck_bomb", "targetname");
	level.price_truck_bomb delete();
	
	level thread stealth_stinger_status();
	level thread setup_road_trigger();
		
	set_rain_level( 5 );
	set_lightning( 3, 10 );
	set_cloud_lightning( 3, 6 );
	
	battlechatter_off( "allies" );
		
	setup_price( ::price_move_think );
	
	
	flag_wait( "stealth_player_in_motorpool" );
	
    save_game( "courtyard_stealth" );
	
	// start looking for player now
	level.road_spotlight thread castle_spotlight_detect_player();
	
    flag_wait ("stealth_move_to_crawl_truck");
	
	level thread platform_guards_animate();
	level thread prone_hint( "truck_hint", "stealth_player_under_truck" );	
	level thread prone_hint( "platform_hint", "player_under_platform" );	
//	level thread motorpool_guards();
	level thread price_skip_ahead();
	
	motorpool_melee();
	platform_crawl();
	
	level waittill("price_say_security_office");
	flag_wait( "price_run_up_security_office" );
	//trigger_wait_targetname( "spawn_security_office" );	// go to next event script
	battlechatter_on("axis");
	
	level thread cleanup();
}

init_event()
{
}

//test()
//{
//	while ( true )
//	{
//		v_eye = level.player GetEye();
//		a_trace = BulletTrace( v_eye, v_eye + AnglesToUp( level.player.angles ) * -1000, false, undefined, true );
//		n_height = Distance( a_trace[ "position" ], v_eye );
//
//		IPrintLn( n_height );
//
//		wait .05;
//	}
//}

dont_shoot_the_trucks()
{
	level endon("courtyard_stealth_cleanup");

	trucks = GetEntArray("destructible_vehicle", "targetname");
	foreach (truck in trucks)
	{
		truck thread truck_shot();
	}

	trucks_shot = 0;
	free_shots = 3;
	
	skill = getDifficulty();
	switch( skill )
	{
		case "medium":
			free_shots = 2;
			break;
		case "hard":
			free_shots = 1;
			break;
		case "fu":
			free_shots = 0;
			break;
	}
	
	while (trucks_shot <= free_shots)
	{
		level waittill("truck_shot");
		trucks_shot++;
		
		// say warning line here
		
		
		if (!flag("stealth_player_in_motorpool"))
		{
			// guys are more sensitive before you drop in.  shoot one vehicle, and you're done.
			break;
		}
	}
	flag_set( "_stealth_spotted" );
}

truck_shot()
{
	level endon("courtyard_stealth_cleanup");
	
	self waittill("damage");
	level notify("truck_shot");
}

motorpool_guard()
{
	self endon( "death" );
	self endon( "stealth_enemy_endon_alert" );
	self endon( "bulletwhizby");
	self endon( "flashbang" );
	self endon(	"grenade danger"); 
	self endon( "explode" );
	level endon( "_stealth_spotted");

	self thread grenade_throw_break_stealth();

	self.animname = self.script_noteworthy;
	self stealth_anim_loop(self, "truckguard_idle");
}

motorpool_patrol()
{
	self endon( "death" );
	self endon( "stealth_enemy_endon_alert" );
	self endon( "bulletwhizby");
	self endon( "flashbang" );
	self endon(	"grenade danger"); 
	self endon( "explode" );
	level endon( "_stealth_spotted");

	
	self.animname = self.script_noteworthy;

	self thread break_stealth_forgiving();
	self thread motorpool_patrol_semi_alerted();
	
	if( isdefined( self.animname ) )
	{
		self.noragdoll = true;	
	}
	
	wait (RandomFloat(0.5));
	self thread maps\_patrol::patrol( self.target );
	self waittill("reached_path_end");
	
	self thread anim_loop_solo(self, "pairguards_idle");
	
	flag_wait( "price_under_truck" );

	self stop_current_anim();	
	
	newdest = undefined;
	
	switch(self.script_noteworthy)
	{
		case "activity_group2_guard1":
			newdest = "motorpool_patrol_path1";
			break;
		case "activity_group2_guard2":
			newdest = "motorpool_patrol_path2";
			break;
	}
	if (IsDefined(newdest))
	{
		self thread maps\_patrol::patrol( newdest );
	}

}


motorpool_patrol_semi_alerted()
{
	self endon("death");
	level endon("_stealth_spotted");
	
	self waittill("enemy");
	
	if (self.script_noteworthy == "activity_group2_guard2")
	{
		wait 1.5;
		if (IsAlive(self) && !flag("price_under_truck") )
		{
			// price take this guy out
			level.price delayThread(1, ::dialogue_queue, "castle_pri_dobetter");
			level.price shoot();
			self die();
		}
	}
}



motorpool_guards()
{
	level endon( "_stealth_spotted" );
//	level endon( "stealth_player_under_truck" );
	
	align = get_new_anim_node( "anim_align_road" );
	ai_truckguard = get_ai_when_spawned( "activity_group2_guard3", "script_noteworthy" );
	align thread stealth_anim_loop( ai_truckguard, "truckguard_idle" );
	
	
	ai_guy1 = get_ai_when_spawned( "activity_group2_guard1", "script_noteworthy" );
	ai_guy2 = get_ai_when_spawned( "activity_group2_guard2", "script_noteworthy" );
	
	ai_guy2 thread motorpool_patroller(	"motorpool_patrol_path2" );
	//wait( 1.0 );
	ai_guy1 thread motorpool_patroller(	"motorpool_patrol_path1" );
	trigger = getent("player_detection_trigger", "targetname");
	
	
	player_right_angle_limit = -161;
	player_left_angle_limit = -16;
	
	
	while(1)
	{
		if(IsAlive(ai_guy1) || IsAlive(ai_guy1))
		{
			wait(0.05);
		}
		else
		{
			
			while(1)
			{
				trigger waittill("trigger");
				if(level.player.angles[1] > player_right_angle_limit && level.player.angles[1] < player_left_angle_limit)
				{
					flag_set("move_price_up_to_bomb_plant");
					flag_set( "stealth_move_to_crawl_truck" );
					flag_set( "price_say_go" );	
					flag_set("stealth_price_crawl_under_truck");
					flag_set("stealth_player_under_truck");
					return;
				}
				wait(0.05);
			}
		}
	
	}
}
			
	



//
//	Scripted anim patroller for the motorpool area
motorpool_patroller( str_patrol_path )
{
	self endon( "death" );
	self endon( "awareness_alert_level" );
	self endon( "bulletwhizby");
	
	align = get_new_anim_node( "anim_align_road" );
	align stealth_anim_single( self, "pairguards_intro" );
	align thread stealth_anim_loop( self, "pairguards_idle" );
	
	flag_wait( "stealth_price_crawl_under_truck" );

// This has them going the opposite way	
	//align stealth_anim_single( self, "pairguards_walk" );
	
	self stop_current_anim();	
	self thread maps\_patrol::patrol( str_patrol_path );
	
}


motorpool_melee()
{
	if ( flag( "_stealth_spotted" ) )
	{
		return;
	}
	
	level endon( "price_kill_guard" );
	level endon( "_stealth_spotted" );
	
	ai_melee = get_ai_when_spawned( "ai_motorpool_melee", "script_noteworthy" );
	ai_melee.melee_fake_death = false;
	//ai_melee thread price_shoot_melee_guard();
	AssertEx( IsAlive( ai_melee ), "Failed to init motor pool melee AI" );

	level.ai_melee_target = ai_melee;
	
	// set him up to stay in place and wait for getting killed
	ai_melee thread melee_guy_behavior();
	//level thread disable_stealth_on_non_silenced_fire();
	ai_melee endon( "death" );
	
	flag_wait( "objective_motorpool_melee" );
	level thread custom_truck_melee_guard_stealth_setting();
	
/*
	// delete old "courtyard activity" guy who "becomes" the melee guard.
	cleanup = GetEntArray( "activity_group3_guard3", "script_noteworthy" );
	foreach ( ent in cleanup )
	{
		ent Delete();
	}
*/

	
	ai_melee thread waittill_melee();
	ai_melee wait_for_damage();

	level.player AllowMelee( true );
	if ( flag( "animating_stealth_melee" ) )
	{
		ai_melee thread animate_melee();
	}
	
	level thread stealth_settings();
}


price_shoot_melee_guard()
{
	//self endon("death");
	
	if ( flag( "_stealth_spotted" ) )
	{
		return;
	}
	
	level endon( "_stealth_spotted" );
	level endon( "animating_stealth_melee" );
	level endon( "animating_stealth_catch" );
	
	align = get_new_anim_node( "anim_align_road" );
/*	
	wait(15);
	level thread add_dialogue_line( "Price", "Come on Yuri, Take him out!" );
	wait(5);
*/
	wait 20;
	level waittill("sprint_go");

	level notify( "price_kill_guard" );
	self.maxhealth = 10000;
	self.health = 10000;
	self disable_pain();
	self.allowdeath = false;
	//Lost your edge?  Let me show you how it's done.
	level.price thread dialogue_queue( "castle_pri_lostyouredge" );
	
	level.ai_motorpool_melee stop_everything();
	level thread hint_fade();
	
	level.price.dont_break_anim = true;
	align thread anim_single_solo( level.price, "price_shoot_guard" );
	level.price waittill( "start_melee_guard_anim" );
	align anim_single_solo( self, "price_shoot_melee" );
	self.allowdeath = true;
	kill_melee_victim( self );
	level.price.dont_break_anim = false;
	
	flag_set( "price_kill_melee_guard" );
	flag_set( "objective_motorpool_melee_complete" );
	
	
	
}

//
//	Stick in place and make sure to restore him to normal if spotted
melee_guy_behavior()
{
	level.ai_motorpool_melee = self;
	
	self.animname = "melee_victim";

	self deletable_magic_bullet_shield();

	e_origin = Spawn( "script_origin", self.origin );
	self LinkTo( e_origin );
	
	waittill_any_ents( self, "death", level, "_stealth_spotted" );

	if ( IsAlive( self ) && !flag("animating_stealth_catch") )
	{
		self Unlink();
		if ( IsDefined( self.magic_bullet_shield ) && self.magic_bullet_shield )
		{
			self stop_magic_bullet_shield();
		}
	}
	e_origin Delete();
}


waittill_melee()
{
	self endon( "death" );
	level endon( "animating_stealth_catch" );
	level endon( "_stealth_spotted" );
	level endon( "price_kill_guard" );

	showing_melee_hint = false;

	while ( true )
	{
		wait .05;
		
		if ( player_can_melee( self ) )
		{
			level.player AllowMelee(false);
			
			if ( !showing_melee_hint )
			{
				showing_melee_hint = true;
//				level thread hint( &"CASTLE_HINT_MELEE" );
			}
			
			if ( level.player MeleeButtonPressed() )
			{
				level.player AllowMelee( true );
//				level thread hint_fade();
				showing_melee_hint = false;
				flag_set( "animating_stealth_melee" );
				return;
			}
		}
		else
		{
			level.player AllowMelee( true );
			
			if ( showing_melee_hint )
			{
//				level thread hint_quick_fade();
				showing_melee_hint = false;
			}
			
			if ( !IsAlive( self ) )
			{
				return;
			}
		}
	}
}



//
//	Wait for melee damage or wait for player to press melee
// self is the melee guy
wait_for_damage()
{
	self endon( "death" );
	level endon( "animating_stealth_melee" );
	level endon( "_stealth_spotted" );
	level endon( "price_kill_guard");
	
	self waittill( "damage", amount, attacker, direction_vec, point, type );

	self.melee_fake_death = true;

	if( self.alertlevel != "noncombat" )
	{
		flag_set( "animating_stealth_catch" );	
	}
	else if ( type == "MOD_MELEE" )
	{
		flag_set("animating_stealth_melee");
//		flag_set( "animating_stealth_catch" );	
	}
	else if ( flag( "price_ready_to_catch" ) )
	{
		flag_set( "animating_stealth_catch" );
	}
	else
	{
		self stop_magic_bullet_shield();
		self die();
	}
}


//
//
player_can_melee( guy )
{
	can_melee = false;
	
	if ( IsAlive( guy ) && level.player GetStance() != "prone" && guy.alertlevel == "noncombat" )
	{
		dist = DistanceSquared( guy.origin, level.player.origin );
		if ( dist < CONTEXTUAL_MELEE_DIST_SQ )
		{
			looking_at = player_looking_at( guy GetTagOrigin( "J_Neck" ), .7, true );
			
			facing_dot = VectorDot(AnglesToForward(guy.angles), AnglesToForward(level.player GetPlayerAngles()));
			facing_same_way = facing_dot > CONTEXTUAL_MELEE_DOT;
			
			can_melee = ( looking_at && facing_same_way );
		}
	}
	
	return can_melee;
}

// self = guard
animate_melee()
{
	flag_wait( "animating_stealth_melee" );

	aud_send_msg("player_stealth_kill");
	
	self.team = "neutral";
	
//	self notify( "death" );
	self.allowdeath = false;
	self set_ignoreme( true );
	self set_ignoreall( true );
	self stop_everything();
	
	level.player.ignoreme = 1;
	level.player SetStance( "stand" );
	level.player FreezeControls( true );

	// Spawn Drone to take his place
//	sp_melee = GetEntArray( "ai_motorpool_melee", "script_noteworthy" );
//	m_dummy = dronespawn( sp_melee );
	
	wait .05; // let stance take effect
	
	align = get_new_anim_node( "anim_align_road" );
	align thread do_player_anim( "stealth_melee", make_array(self, level.price), true, 0.25 );
	level.player.m_player_rig Attach( "weapon_parabolic_knife", "TAG_WEAPON_RIGHT", true );
	
	wait 1;
	playfxontag( getfx( "knife_attack_throat_fx" ), level.player.m_player_rig, "tag_knife_fx" );
	playfxontag( getfx( "knife_attack_throat_fx2" ), self, "J_Neck" );
	
	level.price	waittillmatch("single anim", "end");
	
//	align waittill( "stealth_melee" );

	flag_clear( "animating_stealth_melee" );
	level.player FreezeControls( false );
	level.player.ignoreme = 0;
	
	//save_game( "melee" );
		
	kill_melee_victim( self );

	flag_set( "objective_motorpool_melee_complete" );
}

kill_melee_victim( guy )
{
	if ( IsDefined( guy.magic_bullet_shield ) && guy.magic_bullet_shield )
	{
		guy stop_magic_bullet_shield();
	}
	guy.a.nodeath = true; 
	guy set_allowdeath(true);
	guy die();
}

stop_everything()
{
	//self disable_stealth_for_ai();
	//self maps\_stealth_shared_utilities::enemy_stop_current_behavior();
	self.ignoreall = true;
}

BACKCRAWL_VIEW_PITCH_UP		= 165;
BACKCRAWL_VIEW_PITCH_DOWN	= -110;

platform_crawl()
{
	level thread bomb_plant();
//	level do_player_crawl();
}


//
//	Put the platform guys in position
platform_guards_animate()
{
	level endon("_stealth_spotted");
	
	if (flag("_stealth_spotted"))
	{
		return;
	}
	
	for ( i=1; i<=5; i++ )
	{
		if ( i==3 )	// this guy's used for something else
		{
			continue;
		}
		
		ai_guy = get_ai_when_spawned( "activity_group3_guard"+i, "script_noteworthy" );
		ai_guy.animname = "platformguard"+i;
		ai_guy thread platform_guard();
		ai_guy.noragdoll = true;
		
		if( IsDefined( ai_guy.animname ) && ( ai_guy.animname == "platformguard1" ) )
		{
			level.platformguard1 = ai_guy;
			self thread stop_platform_guards_conv();
		}
		
		if( IsDefined( ai_guy.animname ) && ( ai_guy.animname == "platformguard2" ) )
		{
			level.platformguard2 = ai_guy;
			self thread stop_platform_guards_conv();
		}
	}

	ai_guy = GetEnt( "platform_flashlight_guy", "targetname" ) spawn_ai( true );
	if ( spawn_failed( ai_guy ) )
	{
		AssertMsg( "Platform flashlight patroller failed to spawn" );
	}
	ai_guy thread platform_flashlight_guard();
	level.ai_platform_flashlight = ai_guy;
	
	thread platform_guards_conv();
}

stop_platform_guards_conv()
{
	self waittill_either( "damage" , "death" );
	
	level notify( "stop_ruins_patrol_conv" );
}

platform_guards_conv()
{
	level endon( "_stealth_spotted" );
	level endon( "stop_platform_guards_conv" );
	
	flag_wait( "start_platform_guards_conv" );

	//Trying to look busy, Mikhail?
	level.platformguard1 dialogue_queue( "castle_ru3_lookbusy" );
	
	wait .5;
	
	//What do you mean?... There's nothing to do.
	level.platformguard2 dialogue_queue( "castle_ru4_nothingtodo" );
	
	wait .5;
	
	//At least the others are seeing some action.
	level.platformguard1 dialogue_queue( "castle_ru3_someaction" );
	
	wait .5;
	
	//I think I'm more likely to die of boredom.
	level.platformguard2 dialogue_queue( "castle_ru4_dieofboredom" );
}

/*
do_player_crawl()
{
	level endon( "courtyard_stealth_cleanup" );
		
	align = get_new_anim_node( "backward_crawl" );
	
	while ( !flag( "player_under_platform" ) || ( level.player GetStance() == "stand" ) )
	{
		wait .05;
	}
	
	level.player SetStance( "crouch" );
		
	level.player _disableWeapon();
	
	level.player AllowStand( false );
	
	align do_player_anim( "backcrawl_into", undefined, true, .5 );
		
	align crawl();
	
	align do_player_anim( "backcrawl_exit", undefined, true, .5 );
		
	level.player AllowStand( true );
	level.player _enableWeapon();
}
*/
crawl_rumbles()
{
	self endon( "death" );
	
	while ( true )
	{
		self waittillmatch( "crawl", "rumble" );
		level.player PlayRumbleOnEntity( "damage_light" );
	}
}

#using_animtree( "player" );

CRAWL_CLAMP_LEFT = 10;
CRAWL_CLAMP_RIGHT = 10;
CRAWL_CLAMP_UP = 65;
CRAWL_CLAMP_DOWN = 20;

/*
crawl()
{
	ANIM_FORWARD = %castle_player_platformcrawl_towards_exit;
	ANIM_BACKWARD = %castle_player_platformcrawl_towards_entrance;

	anim_current = ANIM_FORWARD;
	anim_dest = ANIM_FORWARD;
	
	level.player.m_crawl_rig = spawn_anim_model( "player_rig" );
	m_player_rig = level.player.m_crawl_rig;
	
	level.player.m_crawl_rig thread crawl_rumbles();
	
	m_player_rig.origin = GetStartOrigin( self.origin, self.angles, ANIM_FORWARD );
	m_player_rig.angles = GetStartAngles( self.origin, self.angles, ANIM_FORWARD );
	
	m_player_rig SetFlaggedAnim( "crawl", anim_current, 1, 0, 0 );
	m_player_rig SetAnimTime( anim_current, 0 );
	
	level.player PlayerLinkToDelta( m_player_rig, "tag_player", 1, CRAWL_CLAMP_RIGHT, CRAWL_CLAMP_LEFT, CRAWL_CLAMP_UP, CRAWL_CLAMP_DOWN );
	
	movement_updated = true;
	n_current_time = 0;
	
	MAX_SPEED_SCALE = .8;
	
	while ( ( n_current_time < 1 ) || ( anim_current != ANIM_FORWARD ) )
	{
		wait 0.05;

		normalized_movement = level.player GetNormalizedMovement();
		if ( !IsAlive( level.player ) )
		{
			normalized_movement = ( 0, 0, 0 );
		}
		
		forward_movement = normalized_movement[0];

		if ( forward_movement == 0 )
		{
			if ( movement_updated )
			{
				m_player_rig SetAnim( anim_current, 1, 0.2, 0 );
			}

			movement_updated = false;
			continue;
		}
		else if ( forward_movement < 0 )
		{
			anim_dest = ANIM_BACKWARD;
		}
		else
		{
			anim_dest = ANIM_FORWARD;
		}
		
		n_current_time = m_player_rig GetAnimTime( anim_current );
		
		movement_updated = true;
		if ( anim_current != anim_dest )
		{
			anim_fraction = 1 - n_current_time;
			
			m_player_rig ClearAnim( anim_current, 0 );
			m_player_rig SetFlaggedAnim( "crawl", anim_dest, 1, 0, clamp( abs( forward_movement ), 0, MAX_SPEED_SCALE ) );
			m_player_rig SetAnimTime( anim_dest, anim_fraction );
			
			anim_current = anim_dest;
			n_current_time = anim_fraction;
		}
		else
		{
			m_player_rig SetFlaggedAnim( "crawl", anim_current, 1, 0, clamp( abs( forward_movement ), 0, MAX_SPEED_SCALE ) );
		}
		
		if ( !flag( "platform_bomb_planted" ) && ( n_current_time > .80 ) && ( anim_current == ANIM_FORWARD ) )
		{
			m_player_rig SetFlaggedAnim( "crawl", anim_current, 1, 0, 0 );
		}
	}
	
	m_player_rig Delete();
}
*/

bomb_plant()
{
	level endon( "courtyard_stealth_cleanup" );
	level endon( "_stealth_spotted" );
	level endon( "price_plant_bomb_instead" );
	
	t_bomb_plant = GetEnt( "trig_platform_bomb", "targetname" );
	t_bomb_plant trigger_off();
	
	t_bomb_plant thread turn_off_trigger_when_alerted();
	
	flag_wait( "objective_bomb_plant" );
	
	//price start checking to see if he will plant or not.
	align = get_new_anim_node( "backward_crawl" );	// switch align nodes
	align thread price_plant_bomb_instead();
	
	t_bomb_plant childthread turn_off_trigger_when_not_looking();
	level.platform_bomb Show();
	
	t_bomb_plant waittill( "trigger" );

	t_bomb_plant Delete();
	level thread do_bomb_plant();
}

turn_off_trigger_when_not_looking()
{
	self endon("trigger");
	
	while(1)
	{
		player_to_bomb_obj_norm = VectorNormalize(level.platform_bomb.origin - level.player.origin);
		player_look_dir = AnglesToForward(level.player GetPlayerAngles());
		
		player_to_bomb_minus_z = VectorNormalize((player_to_bomb_obj_norm[0],player_to_bomb_obj_norm[1],0));
		player_look_dir_minus_z = VectorNormalize((player_look_dir[0],player_look_dir[1],0));
		horizontal_dot = VectorDot(player_to_bomb_minus_z,player_look_dir_minus_z);
		total_dot = VectorDot(player_to_bomb_obj_norm,player_look_dir);
		
		dot_limit_total = 0.75;
		dot_limit_horizontal = 0.95;
		player_dist_to_target = Distance(level.platform_bomb.origin,level.player.origin);
		if ( player_dist_to_target < 50 )
		{
			dot_limit_total = 0.60;
			dot_limit_horizontal = 0.75;
		}
		
		if ( total_dot > dot_limit_total && horizontal_dot > dot_limit_horizontal )
		{
			self trigger_on();
		}
		else
		{
			self trigger_off();
		}
		wait(0.2);
	}
}

turn_off_trigger_when_alerted()
{
	level endon( "courtyard_stealth_cleanup" );
	
	level waittill_Any("_stealth_spotted", "price_plant_bomb_instead");
	
	if( isdefined( self ) )
	{
		self trigger_off();
	
	}
		level.platform_bomb hide();
	
}

do_bomb_plant()
{
	flag_set( "player_planted_bomb" );
	level endon( "courtyard_stealth_cleanup" );
	level endon( "price_plant_bomb_instead" );
		
	level.player FreezeControls(true);
	level.player DisableWeapons();

	hands_rig = spawn_anim_model( "player_rig", level.player.origin - (0,0,5) );
	hands_rig.angles = level.player.angles;
	hands_rig thread anim_single_solo(hands_rig, "bomb_plant");

	thread manage_player_reference_ent(hands_rig);
	
	flag_set( "platform_bomb_planted" );
	level notify( "platform_bomb_planted" );
	
	aud_send_msg("player_plant_c4_platform");
	
	hands_rig Attach( "weapon_c4", "tag_weapon", true );
	level.platform_bomb Delete();
	
	hands_rig waittillmatch("single anim", "end");
	
	level.player FreezeControls(false);
	level.player EnableWeapons();
	hands_rig Delete();
	level.player PlayerSetGroundReferenceEnt(undefined);
	level.ref_ent delete();
}

manage_player_reference_ent(rig)
{
	level.ref_ent = Spawn("script_origin", level.player.origin);
	level.ref_ent.angles = rig GetTagAngles("tag_weapon_left");
	offset = 90 - (level.player GetPlayerAngles())[1];
	level.ref_ent LinkTo(rig,"tag_weapon_left",(0,0,0),(0,offset,0));
	
	player_angles = level.player GetPlayerAngles();
	if ( player_angles[0] < 0 )
	{
		ref_ent_reached_player_pitch = false;
		while(!ref_ent_reached_player_pitch)
		{
			wait(0.05);
			
			player_angles = level.player GetPlayerAngles();
			
			pitch = min(abs(level.ref_ent.angles[0]),abs(level.ref_ent.angles[0] - 360));
			roll = min(abs(level.ref_ent.angles[2]),abs(level.ref_ent.angles[2] - 360));
			ref_ent_pitch_normalized = pitch + roll;
			player_pitch_normalized = player_angles[0] * -1;
			
			if ( player_pitch_normalized - ref_ent_pitch_normalized < 0 )
			{
				ref_ent_reached_player_pitch = true;
			}
		}
	}

	level.player SetPlayerAngles((0,player_angles[1],player_angles[2]));
	level.player playerSetGroundReferenceEnt( level.ref_ent );
}

place_bomb_model( m_player_rig )
{
	tag_weapon_location = m_player_rig GetTagOrigin( "tag_weapon" );
	bomb_location = (tag_weapon_location[0], tag_weapon_location[1], 44);
	
	level.platform_bomb = Spawn( "script_model", bomb_location );
	level.platform_bomb.angles = m_player_rig GetTagAngles( "tag_weapon" );
	level.platform_bomb SetModel( "weapon_c4" );
	
	level.platform_bomb hide();
	wait(1);
	level.platform_bomb show();
}

place_price_bomb_model( price )
{
	level.price Attach( "weapon_c4", "tag_weapon_left", true );
	
}

remove_price_bomb_model( price )
{
	level.price_truck_bomb = Spawn( "script_model", level.price GetTagOrigin( "tag_weapon_left" ) );
	level.price_truck_bomb.angles = level.price GetTagAngles( "tag_weapon_left" );
	level.price_truck_bomb SetModel( "weapon_c4" );
	level.price Detach( "weapon_c4", "tag_weapon_left");
}


platform_guard()
{
	level endon( "_stealth_spotted" );
	
	align = get_new_anim_node( "backward_crawl" );
		
	self endon( "death" );
	self endon( "awareness_alert_level" );
	self endon( "bulletwhizby" );
	
	self thread grenade_throw_break_stealth();
	self thread unforgiving_stealth_breaker();
	align thread stealth_anim_loop( self, "platform_idle" );
	
	flag_wait( "player_in_backcrawl" );
	
	self thread platform_guard_part2( align );
}

unforgiving_stealth_breaker()
{
	// wait till they notice something (probably the player making too much noise)
	self waittill("awareness_alert_level");
	
	 // make sure they can see price
	level.price.ignoreme = false;
	wait 1;
	level notify("_stealth_spotted");
}

platform_guard_part2( align )
{
	self endon( "death" );
	
	//level endon( "_stealth_spotted");
	
	if ( !flag( "_stealth_spotted" ) )
	{
		//self stealth_reset();
	
	    //	wait .5;	
	    
		self endon( "awareness_alert_level" );
		self endon( "bulletwhizby" );
	
		align stealth_anim_single( self, "platform_walk" );
	
		align thread stealth_anim_loop( self, "platform_idle_end" );
		
		if ( self.animname == "platformguard1" )
		{
			// Also spawn cigarette
			m_cigarette = spawn_anim_model( "cigarette" );
			self thread delete_cig_on_death(m_cigarette);
			add_cleanup_ent( m_cigarette, "courtyard_stealth" );
			
			align thread anim_loop_solo( m_cigarette, "platform_idle_end" );
			
//			flag_wait( "player_approaches_backcrawl_end" );
			flag_wait( "platform_bomb_planted" );

			align notify( "stop_loop" );
			
			align thread anim_single_solo( m_cigarette, "jump_down" );
			align thread stealth_anim_single( self, "jump_down" );
			
			wait 0.5;
			aud_send_msg("guard_jumps_down", self);
			PlayFXOnTag( level._effect["cigarette_off"], m_cigarette, "tag_origin" );
			m_cigarette hide();
			
			flag_set("platform_guy_away");
			
            self waittillmatch("single anim", "end");
			
		    self thread maps\_patrol::patrol( "platform_jump_down_guy_patrol_node" );
		}
	}
}
delete_cig_on_death( cig )
{
	level endon( "courtyard_stealth_cleanup" );
	           
	self waittill_any("death", "_stealth_spotted");
	
	if( isdefined(cig) )
	{
		cig delete();	
	}
}

platform_flashlight_guard()
{
	self endon( "death" );

	level endon( "_stealth_spotted" );

	self thread platform_flashlight();
	
	self.animname = "platformguard3";
	
	align = get_new_anim_node( "backward_crawl" );
	
	self endon( "awareness_alert_level" );
	
	self endon( "bulletwhizby" );
	
	add_cleanup_ent( self, "courtyard_stealth" );
	
	self thread grenade_throw_break_stealth();
	// will be reset when stealth is broken
	//self.ignoreall = true;
	align thread stealth_anim_loop( self, "platform_idle" );
	
	//flag_wait( "player_in_backcrawl" );
	flag_wait( "start_flashlight_guard" );
	
	align thread stealth_anim_single( self, "platform_walk" );
	wait ( 14 );

	flag_set( "platform_flashlight_passed" );
	align waittill( "platform_walk" );

	align thread stealth_anim_loop( self, "platform_idle_end" );
	
}

platform_flashlight()
{
	self endon( "death" );
	
	flashlight_on( true );
	
	flag_wait( "player_in_backcrawl" );
	
	wait 2; // give time to turn off the road spotlight

	thread platform_flashlight_manager();

	self thread castle_spotlight_detect_player( "tag_flash", .97 );
}

platform_flashlight_manager()
{
	while (!flag("platform_bomb_planted"))
	{
		flag_wait("platform_light_on");
		flashlight_on( false, "flashlight_ai_grate" );
		flag_waitopen("platform_light_on");
		flashlight_on( true );
	}
}

stealth_reset()
{
	//*** Copied right out of maps\_stealth_visibility_enemy::enemy_threat_logic() ***//
	// Makes sure guys get reset before the player exits the platform
	if ( isdefined( self.enemy ) )
	{
		self maps\_stealth_shared_utilities::enemy_alert_level_forget( self.enemy, 0 );
	}
	
	self ClearEnemy();
	self maps\_stealth_threat_enemy::enemy_alert_level_change( "reset" );
	//********************************************************************************//
}

price_hold_vo()
{
	level endon("_stealth_spotted");
	
	wait 3.5;
	//Hold...
	self dialogue_queue( "castle_pri_hold2" );
	wait 1;
	//Only shoot at what you can kill.	
	self dialogue_queue( "castle_pri_whatyoukill" );
}

/////////////////////////////////////////////////////

//	Move Price throughout the stealth section
// self is Price
price_move_think()
{
	level endon( "_stealth_spotted" );
	
	align = get_new_anim_node( "anim_align_road" );
	
	if ( level.start_point != "platform_crawl" )
	{
		self thread price_courtyard_stealth_dialog();
		
		// Jump down
		flag_wait( "courtyard_activity_done" );

		align anim_single_solo( self, "move_to_stealth" );
		align thread custom_price_loop_anim( self, "stealth_intro_wait" );
		
		// Move up to the first gap in the trucks		
		flag_wait( "stealth_player_in_motorpool" );
		thread price_hold_vo();

//		save_game( "motorpool" );
		
		//self thread skip_ahead_if_player_run_ahead();
	
		
		self price_skippable_anim( align, "stealth_intro", "stealth_idle" );
		// Go to the crawl truck

		flag_wait( "stealth_move_to_crawl_truck" );
		flag_set( "price_say_go" );
		
		self price_skippable_anim( align, "move_to_crawltruck", "crawltruck_idle" );
		
		// Crawl under and move to the bomb
		flag_wait( "stealth_price_crawl_under_truck" );
		flag_set("price_under_truck");

	self.dont_break_anim = true;
	self.no_ai = true;
	self.price_under_platform = true;
	self allowedStances("prone");
	self.a.nodeath = true;
	self.allowpain = false;
	self.skipDeathAnim = true;
	
		self price_skippable_anim( align, "crawltruck_crawl", "crawltruck_under_idle" );
//		align notify( "stop_loop" );
//		self.is_looping = false;
//		align anim_single_solo( self, "crawltruck_crawl" );
//		align thread custom_price_loop_anim( self, "crawltruck_under_idle" );
		
		
		// Plant the bomb
	    flag_wait( "stealth_player_under_truck" );
		align notify( "stop_loop" );
		self.is_looping = false;
		aud_send_msg("price_sets_c4");
		flag_set("price_plants_truckc4");
		align anim_single_solo( self, "place_charge" );
		align thread custom_price_loop_anim( self, "crawltruck_under_idle" );
		
		// Get ready to take out guard
		save_game( "under_truck" );
		
		flag_wait( "motorpool_melee_lookat" );

		//wait(2);
		align notify( "stop_loop" );
		self.is_looping = false;
		delayThread(3, ::flag_set, "motorpool_melee_guards_leave");
		
		align thread anim_single_solo( self, "crawltruck_to_run" );

		wait 5;
		
	self allowedStances("stand", "crouch", "prone");
	self.a.nodeath = false;
	self.no_ai = undefined;
	self.allowpain = true;
	self.skipDeathAnim = undefined;
	self.dont_break_anim = false;
	self.price_under_platform = false;
		
		
		self waittillmatch("single anim", "end");
	
		flag_set( "objective_motorpool_melee" );


	
		align thread price_indicate_guard( );
		
		if ( !flag( "objective_motorpool_melee_complete" ) )
		{
			align thread price_catch_guard();
			level.ai_melee_target thread price_shoot_melee_guard();
		}
		
		// 
		flag_wait( "objective_motorpool_melee_complete" );
		
		// Get ready to run across the road
		align notify( "stop_loop" );
		
/*		
		if( flag ( "price_kill_melee_guard" ) )
		{
			//do nothing for now.
			
		}
		else if ( !flag( "animating_stealth_catch" ) )
		{
			align anim_reach_solo( self, "road_sprint_into" );
			align anim_single_solo( self, "road_sprint_into" );
		}
		else
		{
			align anim_reach_solo( self, "road_sprint_wait_loop" );
		}
*/		
		flag_set( "price_say_some_timing" );
		save_game( "melee" );
		align thread custom_price_loop_anim( self, "road_sprint_wait_loop" );
		
		//level waittill( "sprint_go" );
		
		//wait 1.0;
		
		
		//wait for safe spot for price to run across.
		while(1)
		{
			if(level.light_away_from_price == false)
			{
				wait(0.5);
			}
			else
			{
				break;	
			}
					
		}
		
		
		// Run Price, run!
		wait 1;
		align notify( "stop_loop" );
		self.is_looping = false;
		self.start_road_running = true;
		//Now!	
		self thread dialogue_queue("castle_pri_now2");

		align anim_single_solo( self, "road_sprint" );
		flag_set( "price_say_your_turn" );
		if (!flag("player_across_road"))
		{
			align thread custom_price_loop_anim( self, "road_sprint_end_loop" ); // not sure we need this, probably should just animate to a cover node
		}
	}
	price_time = GetTime();
	//nd_after_road = GetNode( "nd_after_road", "targetname" );
	//self SetGoalNode( nd_after_road );
	
	flag_wait( "player_across_road" );
	
	// if player took 10 seconds or more to get across road, berate them
	player_time = GetTime();
	if (player_time - price_time > 10000)
	{
		//You have to move when I move.  Don't screw this up.	
		self thread dialogue_queue("castle_pri_screwthisup2");
	}

	save_game( "player_across_road" );
	align notify( "stop_loop" );
	self.is_looping = false;
	self thread price_platform_stealth_dialog();

	align anim_single_run_solo( self, "road_sprint_exit" );
	
	align = get_new_anim_node( "backward_crawl" );	// switch align nodes

 /*
	//set price stance to prone only.
	self allowedStances("prone");
	self.a.nodeath = true;
	//self.noragdoll = true;
	self.allowpain = false;
	self.skipDeathAnim = true;
	//self.ignoreall = true;
*/	
	align anim_reach_and_approach_solo( self, "start_into_idle" );
	align anim_single_solo( self, "start_into_idle" );
	align thread custom_price_loop_anim( self, "wait_before_backcrawl" );
	
	flag_wait( "player_approaches_backcrawl" );
	
	align notify( "stop_loop" );
	self.is_looping = false;
	align anim_single_solo( self, "move_to_backcrawl" );
	
	self.dont_break_anim = true;
	self.no_ai = true;
	self.price_under_platform = true;
	self allowedStances("prone");
	self.a.nodeath = true;
	self.allowpain = false;
	self.skipDeathAnim = true;
	self.ignoreall = true;

	align anim_single_solo( self, "get_into_backcrawl" );

	align anim_single_solo( self, "backcrawl_gap" );
	flag_set( "price_say_wait_for_flashlight" );
	
	align thread custom_price_loop_anim( self, "backcrawl_gap_idle" );
	
	if ( !flag( "platform_flashlight_passed" ) && IsAlive( level.ai_platform_flashlight ) )
	{
		waittill_any_ents( level, "platform_flashlight_passed", level.ai_platform_flashlight, "death" );
	}
	
	align notify( "stop_loop" );
	self.is_looping = false;
	align anim_single_solo( self, "backcrawl_bomb" );
//	align anim_single_solo( self, "backcrawl_stoptalk" );
//	align thread anim_loop_solo( self, "backcrawl_bomb_idle" );
	
//	align notify( "stop_loop" );
	align anim_single_solo( self, "backcrawl" );
	align thread custom_price_loop_anim( self, "backcrawl_idle" );
	
//	flag_wait( "player_approaches_backcrawl_end" );
	flag_wait( "platform_bomb_planted" );
	
	thread setup_security_office_door();
	
	if( !flag( "player_planted_bomb" ) )
	{
		self.a.pose = "prone";
		
		align notify( "stop_loop" );
		self.is_looping = false;
		align thread custom_price_loop_anim( self, "backcrawl_idle" );
	}
	
	flag_wait( "platform_guy_away" );
	
	align notify( "stop_loop" );
	self.is_looping = false;

	//Clear.  Go.
	self delayThread(7.5, ::dialogue_queue, "castle_pri_cleargo");
	
	align anim_single_solo( self, "backcrawl_exit1" );
	
	self.is_looping = false;
	self allowedStances("stand", "crouch", "prone");
	self.a.nodeath = false;
	self.no_ai = undefined;
	//self.noragdoll = false;
	self.allowpain = true;
	self.skipDeathAnim = undefined;
	//self.ignoreall = false;
	self.dont_break_anim = false;
	self.price_under_platform = false;


	align thread custom_price_loop_anim( self, "backcrawl_exit_wait1" );
	flag_wait( "player_approaches_exit1" );
	align notify( "stop_loop" );

	//We're good.  Keep moving.
	self thread dialogue_queue( "castle_pri_weregood3" );

	align anim_single_solo( self, "backcrawl_exit2" );
/*	
	align anim_reach_solo(self, "backcrawl_exit_wait2");
	align thread anim_loop_solo( self, "backcrawl_exit_wait2" );
*/
	enable_ai_color();
	
	flag_wait( "player_approaches_exit" );
	
//	align notify( "stop_loop" );
	// use colors to get to door
	activate_trigger( "spawn_security_office", "targetname", level.player );
	level notify( "price_say_security_office" );
	
	save_game( "security_office" );
}

setup_security_office_door()
{
	s_align = get_new_anim_node( "security_room" );
	m_security_door = GetEnt( "security_front_door", "targetname" );
	m_security_door.animname = "door";
	m_security_door assign_animtree();
	s_align anim_first_frame_solo(m_security_door, "security_office_entry");
}

price_skippable_anim(align, animation, animation_idle)
{
	if(flag("move_price_up_to_bomb_plant"))
	{
		return;		
	}
	level endon("move_price_up_to_bomb_plant");
	
	align notify( "stop_loop" );
	self.is_looping = false;
	align anim_single_solo( self, animation );
	align thread custom_price_loop_anim( self, animation_idle );

}




price_plant_bomb_instead()
{
	level endon("platform_bomb_planted");
	
	wait(20);
	level notify("price_plant_bomb_instead");
	level.price dialogue_queue( "castle_pri_nevermind2" ); //Nevermind.  I'll handle it.
	flag_set("Price_Plant_bomb_instead");
	
	level.platform_bomb delete();
	
	self anim_single_solo( level.price, "bomb_plant_platform" );
	
	flag_set( "platform_bomb_planted" );
}


//
//	If the player shoots the guard, then catch him
// self is the align node
price_catch_guard( )
{
	if ( flag( "animating_stealth_melee" ) )
	{
		return;
	}

	flag_set( "price_ready_to_catch" );
	
	flag_wait( "animating_stealth_catch" );

	waitframe();
	
	if (flag("_stealth_spotted"))
	{
		return;
	}
	level.ai_motorpool_melee DropWeapon(level.ai_motorpool_melee.weapon, "right", 1);
	level.ai_motorpool_melee gun_remove();
	level endon( "_stealth_spotted" );
	level endon( "animating_stealth_melee" );
	thread watch_for_melee_spotted();
	
	level.ai_motorpool_melee.allowdeath = false;
	level.ai_motorpool_melee set_ignoreme( true );
	level.ai_motorpool_melee set_ignoreall( true );
	level.ai_motorpool_melee stop_everything();
	
	aud_send_msg("price_drag_body");
	level thread hint_fade();
	self notify( "stop_loop" );
//	align = get_new_anim_node( "anim_align_road" );
//	level.price.dont_break_anim = true;
	self thread anim_single_solo( level.price, "stealth_catch" );
	level.ai_motorpool_melee.team = "neutral";
	self anim_single_solo( level.ai_motorpool_melee, "stealth_catch" );
	level.ai_motorpool_melee.allowdeath=true;
	kill_melee_victim( level.ai_motorpool_melee );
//	level.price.dont_break_anim = false;
	level.price	waittillmatch("single anim", "end");
	
	//remove the animation pop if player somehow set off the alert during price catch animat
	flag_set( "objective_motorpool_melee_complete" );
}

watch_for_melee_spotted()
{
	flag_wait_any("_stealth_spotted", "objective_motorpool_melee_complete");
	
	if (!flag("objective_motorpool_melee_complete") )
	{
		kill_melee_victim( level.ai_motorpool_melee );
		level.ai_motorpool_melee stop_current_anim();
		level.ai_motorpool_melee StartRagdoll();
	}
}

//
//	Point out the guard
// self is the align node
price_indicate_guard( )
{
	level endon( "animating_stealth_melee" );
	level endon( "animating_stealth_catch" );
	
	// take him out
	level.price thread dialogue_queue( "castle_pri_takehimout" );

	self anim_single_solo( level.price, "indicate_guard" );
	self thread custom_price_loop_anim( level.price, "melee_idle" );
}


price_wait_vo()
{
	level endon( "_stealth_spotted" );
	
	flag_wait( "motorpool_melee_lookat" );
	
	//	Wait?
	self dialogue_queue( "castle_pri_wait" );
}

//	Dialog for courtyard jumpdown through outside of security office
//	self is Price
price_courtyard_stealth_dialog()
{
	self endon( "death" );
	level endon( "_stealth_spotted" );
	level endon( "stealth_not_following_price1" );
	
	flag_wait( "stealth_player_in_motorpool" );

	thread price_wait_vo();
	
	flag_wait( "price_say_go" );
	wait( 1.0 );
	
	if ( !flag( "stealth_price_crawl_under_truck" ) )
    {
		//	Go?
		self thread dialogue_queue( "castle_pri_go2" );
	}
	    
	flag_wait( "price_under_truck" );

	if ( !flag(	"stealth_player_under_truck" ) )
	{
		//	Under the trucks.
		self thread dialogue_queue( "castle_pri_undertrucks2" );
	}
	
	flag_wait( "price_plants_truckc4" );
	//	We'll plant C4 throughout the castle, in case we need to cover our escape.	
	self dialogue_queue( "castle_pri_plantc4" );
	//We'll burn this place down if we have to.	
	self dialogue_queue( "castle_pri_burnthisplace");
	
	//	Get in close - use your knife.  	
	//self dialogue_queue( "castle_pri_useknife" );
	//	And whatever you do, don't get caught in the spotlight.	
	//self dialogue_queue( "castle_pri_spotlight" );

	flag_wait( "objective_motorpool_melee_complete" );
/*	
	if ( !flag( "_stealth_spotted" ) )
	{
		//	Nice.	
		self dialogue_queue( "castle_pri_nice2" );
	}
*/
	flag_wait( "price_say_some_timing" );
	//Wait for it...	
	self dialogue_queue( "castle_pri_waitforit" );
	//wait until price make his move.
	level waittill("sprint_go");
	
	while(1)
	{
		if(!isdefined(self.start_road_running))
		{
			wait(0.05);
		}
		else
		{
			break;
		}
	
	}
/*
	if( !flag( "player_going_first" ) )
	{
	    self dialogue_queue( "castle_pri_illgofirst" );
	}

	flag_wait( "price_say_your_turn" );
	if ( !flag( "player_going_first" ) )
	{
		//	Your turn, Yuri.
		self dialogue_queue( "castle_pri_yourturn" );
	}
*/	
	wait .7;
	
}


//	Dialog for courtyard jumpdown through outside of security office
//	self is Price
price_platform_stealth_dialog()
{
	self endon( "death" );
	level endon( "stealth_not_following_price2" );
	level endon("_stealth_spotted");
/*
	if ( !flag( "stealth_not_following_price1" ) )
	{
		//	More sentries up ahead... Stay low.	
		self dialogue_queue( "castle_pri_moresentries" );
	}
*/
	//Over here.	
	self dialogue_queue( "castle_pri_overhere" );

	
	// Wait for the flashlight guy to pass
	self thread price_flashlight_wait();
	
	//TODO This needs to be a notetrack in flashlight guy's animation
	if ( !flag( "platform_flashlight_passed" ) && IsAlive( level.ai_platform_flashlight ) )
	{
		waittill_any_ents( level, "platform_flashlight_passed", level.ai_platform_flashlight, "death" );
		
		//	We're good.	
		self dialogue_queue( "castle_pri_weregood2" );
	}
	
	flag_wait( "price_say_wait_for_flashlight" );
	flag_set( "objective_bomb_plant" );
	wait 1;
	//Plant C4 on the platform.	
	self dialogue_queue( "castle_pri_c4platform" );

	//	Hurry up and get that C4 planted.	
	//	What are you waiting for?  Plant that C4.	
	a_nag_lines = [ "castle_pri_plantthec4", "castle_pri_daft" ];
	nag_vo_until_flag( a_nag_lines, "platform_bomb_planted", 15, false, false );

	flag_wait( "platform_bomb_planted" );
	wait 4;
	//Easy...	
	self thread dialogue_queue( "castle_pri_easy");

	
	level waittill( "price_say_security_office" );
	
	//	There's the security office.
	self dialogue_queue( "castle_pri_securityoffice2" );

}


//
// Price will say wait if either he or the player gets near the gap, but the player
//	needs to be under the platform as well
// 	self is Price
price_flashlight_wait()
{
	level endon( "platform_flashlight_passed" );
	//level endon( "price_said_wait_already" );
	
	flag_wait_any( "price_say_wait_for_flashlight", "player_approaches_gap", "price_says_wait" );

	flag_wait( "start_flashlight_guard" );	// Make sure the player is under the platform at least

	if ( IsAlive( level.ai_platform_flashlight ) )
	{
		//	Wait?
		self dialogue_queue( "castle_pri_stopdontmove" );
	}
}

break_stealth()
{
	level endon( "courtyard_stealth_cleanup" );
	level notify( "ruins_break_stealth_stop" );
	level.price endon( "death" );
	
	
	flag_wait ("ruins_done");
	
	flag_wait( "_stealth_spotted" );
	
	battlechatter_on("axis");
	level.price thread check_for_price_death();
	if (!IsDefined(level.price.magic_bullet_shield) && level.price.price_under_platform )
	{
		level.price.allowdeath = false;
	}
	   
	a_enemies = [ level.price, level.player ];

	clips = GetEntArray("melee_sight_block", "targetname");
	foreach (clip in clips)
	{
		clip delete();
	}
	
	// Attack!	
	a_ai = GetAISpeciesArray( "axis", "all" );
	foreach( ai in a_ai )
	{
		
		if( !isdefined( ai ) || !IsDefined(ai.finished_spawning))
		{
		   continue;
		}
		
		if(isdefined(ai.script_noteworthy) && ai.script_noteworthy == "ai_motorpool_melee" )
		{
			if(isdefined(ai._animActive) && ai._animActive > 0)
				continue;	
		}
		
		ai set_ignoreall( false );
		ai set_goalradius( 512 );
		ai GetEnemyInfo( level.price );
		ai GetEnemyInfo( level.player );
		
		// Track down an enemy
		b_got_enemy = false;		
		foreach( enemy in a_enemies )
		{
			if ( ai CanSee( enemy ) )
			{
				ai SetGoalEntity( enemy );
				b_got_enemy = true;
				break;
			}
		}
		if ( !b_got_enemy )
		{
			// Randomly pick one
			ai SetGoalEntity( a_enemies[ RandomInt( a_enemies.size ) ] );
		}
		//wait( 0.1 );
	}
	
	turn_on_alarm_lights();
	
	Objective_Delete( obj( "motorpool_melee" ) );
	Objective_Delete( obj( "platform_bomb_plant" ) );
	
//	level thread bring_in_the_hounds();
	
	if ( IsDefined( level.stealth_btr1 ) )
	{
		level.stealth_btr1 thread btr_kill_allies();
	}
/*	
	if ( IsDefined( level.stealth_btr2 ) )
	{
		level.stealth_btr2 thread btr_kill_allies();
	}
*/	
	array_call( GetEntArray( "platform_nosight", "targetname" ), ::Delete );
	
	wait .05; // make sure price's anim threads get killed on "_stealth_spotted" before stopping his animation
	
	level thread hint_fade();

	level.price StopSounds();
	wait( 1.0 );	// time delay from realization to verbalization
	
	if (IsAlive(level.price))
	{
		level.price thread dialogue_queue( "castle_pri_spotted" );
	
		level.price.allowdeath = true;	// just in case
		
		if ( IsDefined(level.price.magic_bullet_shield) && 	!level.price.price_under_platform)
		{
			level.price stop_magic_bullet_shield();
		}
	 	
		
		level.price thread kill_price_if_taking_too_long();
		
		if(isdefined(level.price.dont_break_anim))
		{
			while(level.price.dont_break_anim == true)
			{	
				wait(0.05);
			}
		}		
		if( isdefined( level.price ) )
		{
			level.price set_ignoreall( false );
			level.price anim_stopanimscripted();
			level.price.goalradius = 512;	
		}
	}
}

check_for_price_death()
{
	quote = undefined;
	
	level.price waittill( "death", other );
	level.price StopSounds();
	
	if ( isplayer( other ) )
	{
		quote = &"SCRIPT_MISSIONFAIL_KILLTEAM_BRITISH";
	}
	else
	{
		quote = &"CASTLE_YOUR_ACTIONS_GOT_PRICE";
	}
	
	wait(2);
	setDvar( "ui_deadquote", quote );
	missionFailedWrapper();
}
	



//
//	Attack allies, kill Price if you can and the player's not too close
btr_kill_allies()
{
	self endon( "death" );
	
	self thread btr_track_ent( level.player );

	while ( true )
	{
		self waittill( "turret_on_target" );
		
		self FireWeapon();
		wait RandomFloatRange( 0.2, 0.3 );
	}
}

btr_track_ent( e_target )
{
	self endon( "death" );

	/* only one of these at a time */
	self notify( "castle_spotlight_track_ent" );
	self endon( "castle_spotlight_track_ent" );
	
	ent = Spawn( "script_origin", e_target.origin );
	self SetTurretTargetEnt( ent );
	
	units_per_second = 600;

	while ( true )
	{
		dist = Distance( e_target.origin, ent.origin );

		vec = RandomVector( 1 );
		extra_z = RandomFloatRange( -16, 16 );
		vec += ( 0, 0, extra_z );
		time = dist / units_per_second;
		random_min = RandomFloatRange( 0.5, 1.0 );
		
		if ( time < random_min )
		{
			time = random_min;
		}

		spotlight_org = e_target.origin + vec;
		ent MoveTo( spotlight_org, time, time * 0.4, time * 0.4 );
		
		wait time;
		
//		self notify( "turret_on_target" );
	}
}


turn_on_alarm_lights()
{
	a_lights = GetEntArray( "alarm_lights", "targetname" );
	
	foreach ( light in a_lights )
	{
		PlayFXOnTag( level._effect[ "fx_lights_strobe_red" ], light, "tag_origin" );
	}
}

spotlight_road()
{
	s_target_across_road = getstruct( "road_spotlight_target_across_road", "targetname" );
	s_target_motor_pool = getstruct( "road_spotlight_target_motorpool", "targetname" );
	post_melee_target = getstruct("road_spotlight_target_motorpool_postmelee", "targetname");
	
	level.light_away_from_price = false;
	
	road_spotlight = GetEnt( "road_spotlight", "targetname" );
	level.road_spotlight = road_spotlight;
	
	road_spotlight SetModel( "ctl_spotlight_modern_3x_on" );
	road_spotlight thread road_spotlight_fx();
	road_spotlight thread road_spotlight_death();
	
	road_spotlight endon( "death" );
	
	road_spotlight.e_target = Spawn( "script_origin", s_target_motor_pool.origin );
	road_spotlight thread castle_spotlight_track_ent( road_spotlight.e_target );
	
	road_spotlight.e_target MoveTo( s_target_motor_pool.origin, .1, 0, 0 );
	
//	flag_wait( "price_ready_to_catch" );
	
	// move target back and forth across the road
	
	while ( !flag("ruins_done") || (flag("ruins_done") && !flag( "_stealth_spotted" )) )
	{
		level.light_away_from_price = true;
		level notify("sprint_go");
//		road_spotlight.e_target MoveTo( s_target_across_road.origin, 0.05, 0, 0 );
		road_spotlight.e_target MoveTo( s_target_across_road.origin, 3.5, 0.5, 3 );
		road_spotlight.e_target waittill( "movedone" );
		
		road_spotlight waittill( "spotlight_on_target" );
		
		wait(2.5);
		level.light_away_from_price = false;
		wait(2.5);

		if (flag("_stealth_spotted"))
		{
			break;
		}
		//wait_across_the_road();

//		road_spotlight.e_target MoveTo( s_target_motor_pool.origin, 0.05, 0, 0 );
		if (flag("animating_stealth_catch") || flag("animating_stealth_melee") || flag("objective_motorpool_melee_complete"))
		{
			road_spotlight.e_target MoveTo( post_melee_target.origin, 3.5, 0.5, 3 );
		}
		else
		{
			road_spotlight.e_target MoveTo( s_target_motor_pool.origin, 3.5, 0.5, 3 );
		}
		if (flag("_stealth_spotted"))
		{
			break;
		}

	    road_spotlight.e_target waittill( "movedone" );
		if (flag("_stealth_spotted"))
		{
			break;
		}
		
		road_spotlight waittill( "spotlight_on_target" );

		if (flag("_stealth_spotted"))
		{
			break;
		}

		wait 3.0;
		
		// keep the spotlight on the melee dude until price is in position to kill him
		if ( flag("price_plants_truckc4") && !flag("objective_motorpool_melee_complete") )
		{
			flag_wait_any("price_ready_to_catch", "_stealth_spotted");
		}
	}
	
	road_spotlight thread castle_spotlight_track_ent( level.player );
}

road_spotlight_death()
{
	level endon( "courtyard_stealth_cleanup" );
	
	trigger_wait_targetname( self.target );
	
	self notify( "death" );
	self.dead = true;
	
	flag_set( "_stealth_spotted" );
	
	PlayFXOnTag( getfx( "spotlight_destroy" ), self, "tag_origin" );
	StopFXOnTag( getfx( "spotlight_modern_rain" ), self, "tag_light" );	
		
	self SetModel( "ctl_spotlight_modern_3x_destroyed" );
}

road_spotlight_fx()
{
	self endon( "death" );
	
	flag_wait( "stadium_lights_on" );
	
	PlayFXOnTag( getfx( "spotlight_modern_rain" ), self, "tag_light" );
	
	flag_wait( "player_in_backcrawl" );
	
	//kill the spotlight detection thread for a bit
	level notify( "disable_spotlight_for_crawl" );
	StopFXOnTag( getfx( "spotlight_modern_rain" ), self, "tag_light" );
	self SetModel( "ctl_spotlight_modern_3x" );
	
	flag_wait( "player_approaches_exit1" );
	
	PlayFXOnTag( getfx( "spotlight_modern_rain" ), self, "tag_light" );
	self SetModel( "ctl_spotlight_modern_3x_on" );
	self thread castle_spotlight_track_ent( self.e_target );
}

wait_across_the_road()
{
	//flag_waitopen( "animating_stealth_melee" );
	//wait 5;
	//flag_waitopen( "animating_stealth_melee" );
}


//
//	Display hint if the player is in the area and not prone.
prone_hint( str_flag, str_end_flag )
{
	if ( IsDefined( str_end_flag ) )
	{
		level endon( str_end_flag );
		level thread prone_hint_end( str_end_flag );
	}
	
	b_player_is_prone = false;
	b_showing_hint = false;

	while ( 1 )
	{
		flag_wait( str_flag );
		
		while ( flag( str_flag ) )
		{
			if (getDifficulty() == "easy")
			{
				b_player_is_prone = level.player GetStance() == "prone";
				if ( b_player_is_prone )
				{
					level thread hint_fade();
					return;
				}
				else
				{
					if ( !b_showing_hint )
					{
						level thread castle_hud_hint( &"CASTLE_HINT_PRONE", 95 );
						b_showing_hint = true;
					}
				}
				wait( 0.05 );
			}
			else
			{
				wait 0.5;
			}
		}
		
		if (b_showing_hint)
		{
			level thread hint_fade();
			b_showing_hint = false;
		}
	}	
}
//	Need to thread this so the hint fades out if it was there
prone_hint_end( str_end_flag )
{
	flag_wait( str_end_flag );
	
	level thread hint_fade();
}


castle_spotlight_track_ent( e_target )
{
	self endon( "death" );
	level endon( "courtyard_stealth_cleanup" );
	level endon( "disable_spotlight_for_crawl" );
	
	/* only one of these at a time */
	self notify( "castle_spotlight_track_ent" );
	self endon( "castle_spotlight_track_ent" );
	
	self SetMode( "manual" );
	
	ent = Spawn( "script_origin", e_target.origin );
	self SetTargetEntity( ent );
	
	units_per_second = 300;

	e_target_moved_dist = 0;
	catch_up = false;
	
	while ( true )
	{
		last_pos = e_target.origin;
		
		if (e_target_moved_dist <= 0.5 || catch_up)
		{
			// jitter when target is not moving
			dist = Distance( e_target.origin, ent.origin );
			vec = RandomVector( 1 );
			extra_z = RandomFloatRange( -16, 16 );
			vec += ( 0, 0, extra_z );
			time = dist / units_per_second;
			random_min = RandomFloatRange( 0.5, 0.8 );
			
			if ( time < random_min )
			{
				time = random_min;
			}
	
			spotlight_org = e_target.origin + vec;
			if ( IsDefined( level.spotlight_override_pos ) )
			{
				spotlight_org = level.spotlight_override_pos;
			}
	
			ent MoveTo( spotlight_org, time, time * 0.4, time * 0.4 );
			wait time;
			// catch up to spotlight if we need to.
			while ( Distance(last_pos, e_target.origin) > 10)
			{
				last_pos = e_target.origin;
				ent MoveTo(e_target.origin, 0.25, 0, 0);
				wait 0.25;
			}
		}
		else
		{
			// when the target is moving, just go where it is, no jitter.
			ent.origin = e_target.origin;
			waitframe();
		}
		
		e_target_moved_dist = Distance(last_pos, e_target.origin);
		
		self notify( "spotlight_on_target" );
	}
}

castle_spotlight_detect_player( str_light_tag, n_dot )
{
	self endon( "death" );
	
	s_target_motor_pool = getstruct( "road_spotlight_target_motorpool", "targetname" );
	
	while ( !flag( "_stealth_spotted" ) )
	{
		/#
			if ( IsGodMode( level.player ) || ( GetDvarInt( "disable_spotlight" ) == 1 ) )
		{
			wait .2;
			continue;
		}
		#/

//		if ( flag( "animating_stealth_melee" ) )
//		{
//			wait( 0.05 );
//			continue;
//		}
		if (flag("safe_prone_area") && (level.player GetStance()) == "prone")
		{
			wait (0.05);
			continue;
		}
		if (flag("safe_crouch_area") && (level.player GetStance()) == "crouch")
		{
			wait (0.05);
			continue;
		}			
		if( flag( "player_in_backcrawl" ) && !flag("player_approaches_exit1") && !IsAi( true ) )
		{
			wait(0.05);
			continue;
		}
			
		v_eye = level.player GetEye();
		if ( spotlight_cone_trace_passed( v_eye, str_light_tag, n_dot ) )
		{
			flag_set( "_stealth_spotted" );
			
			/#
				IPrintLn( "spotlight saw player" );
			#/
		}
		else 
		{
			a_corpses = GetCorpseArray();
			foreach ( corpse in a_corpses )
			{
				v_end = corpse.origin;
				if ( spotlight_cone_trace_passed( v_end, str_light_tag, n_dot ) )
				{
					flag_set( "_stealth_spotted" );
					
					/#
						IPrintLn( "spotlight saw corpse" );
					#/
				}
			}
		}
		
//		if(isdefined( level.ai_melee_target ) )//&& level.ai_melee_target.melee_fake_death == true )
//		{
//			//v_end =  s_target_motor_pool.origin;
//			iprintln(level.ai_melee_target.origin);
////			if ( spotlight_cone_trace_passed( v_end, str_light_tag, n_dot ) )
////			{
////				     //flag_set( "_stealth_spotted" );
////					/#
////						IPrintLn( "spotlight saw fake melee dead guy" );
////					#/
////	
////			}
//			
//		}
		
		

		if(isdefined( level.ai_melee_target ) && level.ai_melee_target.melee_fake_death == true )
		{
			//v_end =  s_target_motor_pool.origin;
			
			v_end =  level.ai_melee_target.origin + (0, 0, 30);
			if ( spotlight_cone_trace_passed( v_end, str_light_tag, n_dot ) )
			{
				     flag_set( "_stealth_spotted" );
					/#
						IPrintLn( "spotlight saw fake melee dead guy" );
					#/
			}
			
		}
		
		wait .05;
	}
	
	self notify( "awareness_alert_level", "warning" );
}

spotlight_cone_trace_passed( v_end, str_light_tag, n_test_dot )
{
	str_tag = "tag_light";
	if ( IsDefined( str_light_tag ) )
	{
		str_tag = str_light_tag;
	}
	
	v_tag_origin = self GetTagOrigin( str_tag );
	v_tag_angles = self GetTagAngles( str_tag );
	
	v_to_spot = v_end - v_tag_origin;
	
	n_dot = VectorDot( VectorNormalize( v_to_spot ), AnglesToForward( v_tag_angles ) );
	
	if ( !IsDefined( n_test_dot ) )
	{
		n_test_dot = SPOTLIGHT_DOT;
	}
	
	b_sight_trace_to_player = SightTracePassed( v_tag_origin, v_end, false, self );
	if ( b_sight_trace_to_player && ( n_dot > n_test_dot ) )
	{
		/#
			Line( v_tag_origin, v_end, ( 1, 0, 0 ), 1, false, 20 );
		#/
			
			return true;
	}
	else
	{
		return false;
	}
}


//
//	Handles if the player decides to lone wolf around.
price_skip_ahead()
{
	level endon( "enter_security_office" );
	
	// Player gets on helipad
	flag_wait( "stealth_not_following_price1" );

	adjust_price_attitude( -5 );
	// Skip to the platform
	flag_set( "stealth_move_to_crawl_truck" );
	flag_set( "stealth_price_crawl_under_truck" );
	flag_set( "stealth_player_under_truck" );
	flag_set( "motorpool_melee_lookat" );

	flag_wait( "price_ready_to_catch" );

	flag_set( "animating_stealth_catch" );
	flag_set( "player_across_road" );

	//	Player past the helipad
	flag_wait( "stealth_not_following_price2" );

	adjust_price_attitude( -5 );
	// Move up to security office
	flag_set( "player_approaches_backcrawl" );
	flag_set( "player_in_backcrawl" );
	flag_set( "start_flashlight_guard" );
	flag_set( "player_approaches_gap" );
	flag_set( "platform_flashlight_passed" );
	
	flag_wait( "price_say_wait_for_flashlight" );
	
	flag_set( "objective_bomb_plant" );
	flag_set( "platform_bomb_planted" );
	flag_set( "player_approaches_backcrawl_end" );
	flag_set( "player_approaches_exit1" );
	flag_set( "player_approaches_exit" );
}


//
//	
cleanup()
{
	// HACK: to not get failed assert when calling cleanup when no ents have been added to this group (for skiptos)
	add_cleanup_ent( Spawn( "script_origin", ( 0, 0, 0 ) ), "courtyard_stealth" );
	
	flag_wait( "security_office_closed" );		// door is closed, can't return to courtyard
	
	level notify( "courtyard_stealth_cleanup" );
	
	open_tower_gate();
	
	cleanup_ents( "courtyard_stealth" );
	
	disable_stealth_system();
	
	road_spotlight = GetEnt( "road_spotlight", "targetname" );
	StopFXOnTag( getfx( "spotlight_modern_rain" ), road_spotlight, "tag_light" );
	road_spotlight SetModel( "ctl_spotlight_modern_3x" );
	
	a_lights = GetEntArray( "alarm_lights", "targetname" );
	array_delete( a_lights );
	
	cleanup_ents = GetEntArray( "courtyard_stealth_cleanup", "script_noteworthy" );
	array_delete( cleanup_ents );

	// stop spotlights (one penetrates into the prison)
	stop_exploder( 501 );
	stop_exploder( 502 );
	stop_exploder( 503 );
	stop_exploder( 504 );
	stop_exploder( 505 );
	stop_exploder( 506 );
	stop_exploder( 520 );
}
custom_price_loop_anim( price, animation)
{
	align = self;
	price.is_looping = true;
	price StopAnimScripted();
	align thread anim_loop_solo( price, animation );
	
}


stealth_stinger_status()
{
	level endon ("courtyard_stealth_cleanup" );
	level endon( "_stealth_spotted" );

	stingers = GetEntArray( "stinger_emplacement", "targetname" );	
	
	for(i = 0 ; i < stingers.size; i++)
	{
		stingers[i] thread stinger_fire_break_stealth();
	}
}

setup_road_trigger()
{
	trigger = getent("I_go_first_dialog_trigger", "targetname");
	trigger waittill("trigger");
	
	flag_set("player_going_first");
	
	
}

platform_mantle_handler()
{
	mantle = GetEnt("platform_mantle", "targetname");
	mantle hide_entity();
	flag_wait("price_run_up_security_office");
	mantle show_entity();
}
