#include common_scripts\utility;
#include maps\_utility;
#include maps\_anim;

main()
{
	player_anims();
	price_anims();
	generic_human();
	vehicle_anims();
	script_model_anims();
	animated_props_anims();
	
	level thread fxanims();

	dialog_lines();
}

#using_animtree( "player" );
player_anims()
{
	//Rig setup
	level.scr_animtree[ "player_rig" ] 		= #animtree;
	level.scr_model[ "player_rig" ] 		= level.player_viewhand_model;

	level.scr_anim[ "player_rig" ][ "escape_player_deploy_chute" ]			= %castle_truck_escape_player_deploy_chute;
	
	
	
	level.scr_anim[ "player_parachute" ][ "landing" ] = %o_castle_3_3_player_chute_landing;

	level.scr_anim[ "player_rig" ][ "landing" ]		 		= %int_castle_3_3_player_landing;
	addNotetrack_customFunction( "player_rig", "player_hits_ground", maps\castle_parachute::landing_hit_ground, "landing" );
	
//	level.scr_anim[ "player_rig" ][ "stealth_melee" ] 		= %castle_contextual_melee_searchlight_player;
	level.scr_anim[ "player_rig" ][ "stealth_melee" ] 		= %castle_6_2_spotlight_kill_player;
		
	level.scr_anim[ "player_rig" ][ "bomb_plant" ]	 		= %castle_player_platformcrawl_bombplant_alt; 
	addNotetrack_customFunction( "player_rig", "detach",  maps\castle_courtyard_stealth::place_bomb_model,  "bomb_plant" );
	
	level.scr_anim[ "player_rig" ][ "bridge_bomb_plant" ]	= %int_castle_9_2_player_shimmy_bombplant;
	level.scr_anim[ "player_rig" ][ "bridge_jump" ]			= %int_castle_14_4_player_jump;
	addNotetrack_customFunction( "player_rig", "gun_up",  maps\castle_courtyard_battle::handle_bridge_jump,  "bridge_jump" );
	//level.scr_anim[ "player_rig" ][ "level_end" ]			= %int_castle_15_7_end_vignette;
	
		

	// Wall Climb
	level.scr_anim[ "player_rig" ][ "wall_climb_start" ]				= %castle_player_wetwall_climb_get_in;
	addNotetrack_customFunction( "player_rig", "left_hand_on",  maps\castle_into_wet_wall::left_hand_plant,  "wall_climb_start" );
	addNotetrack_customFunction( "player_rig", "right_hand_on", maps\castle_into_wet_wall::right_hand_plant, "wall_climb_start" );

	level.scr_anim[ "player_rig" ][ "wall_climb_full" ]					= %castle_player_wetwall_climb_full;
/*
	level.scr_anim[ "player_rig" ][ "wall_climb_start_idle" ][0]		= %castle_player_wetwall_climb_idle;
	level.scr_anim[ "player_rig" ][ "wall_climb_idle" ][0]				= %castle_player_wetwall_climb_climbing_idle;

//	level.scr_anim[ "player_rig" ][ "wall_climb_right_hand" ]			= %castle_player_wetwall_climb_righthand;
	level.scr_anim[ "player_rig" ][ "wall_climb_right_hand" ]			= %castle_player_wetwall_climb_climbing_right;
	addNotetrack_customFunction( "player_rig", "right_hand_on", maps\castle_into_wet_wall::right_hand_plant, "wall_climb_right_hand" );
	
	level.scr_anim[ "player_rig" ][ "wall_climb_right_hand_idle" ][0]	= %castle_player_wetwall_climb_righthand_idle;

	level.scr_anim[ "player_rig" ][ "wall_climb_left_hand" ]			= %castle_player_wetwall_climb_lefthand;
	addNotetrack_customFunction( "player_rig", "left_hand_on",  maps\castle_into_wet_wall::left_hand_plant,  "wall_climb_left_hand" );

	level.scr_anim[ "player_rig" ][ "wall_climb_both_hands_idle" ][0]	= %castle_player_wetwall_climb_bothhands_idle;
	level.scr_anim[ "player_rig" ][ "wall_climb_both_hands_push_up" ]	= %castle_player_wetwall_climb_bothhands_push_up;
	level.scr_anim[ "player_rig" ][ "wall_climb_slip" ]				= %castle_player_wetwall_climb_slip;
*/	
	level.scr_anim[ "player_rig" ][ "wall_climb_peek_start" ]		= %castle_player_wetwall_climb_hole_peek_get_in;
	
	level.scr_anim[ "player_rig" ][ "wall_climb_peek_idle" ][0]		= %castle_player_wetwall_climb_hole_peek_idle;
	level.scr_anim[ "player_rig" ][ "wall_climb_peek_slip" ]		= %castle_player_wetwall_climb_hole_peek_slip;
	level.scr_anim[ "player_rig" ][ "wall_climb_peek_fall" ]		= %castle_player_wetwall_climb_hole_peek_fall;
	addNotetrack_flag( "player_rig", "wallbreak", "kitchen_start", "wall_climb_peek_fall" );
	addNotetrack_sound( "player_rig", "slatbreak", "wall_climb_peek_slip", "scn_castle_wetwall_wood_slat_break" );

	
	level.scr_anim[ "player_rig" ][ "cliffjump_glide" ]	= %castle_truck_escape_glide_player;
	
	//riding in truck	
	level.scr_anim[ "player_rig" ][ "truck_enter" ]				= %castle_truck_escape_mount_player;
	
		
	/****************************************
			Base Jump
	****************************************/
	
	level.scr_anim[ "player_rig" ][ "cliffjump_new" ]	= %castle_truck_escape_player;
	
	
	level.scr_anim[ "escape_chute_player" ][ "cliffjump_glide" ]		= %castle_truck_escape_glide_chute;	
	level.scr_animtree[ "escape_chute_player" ]							= #animtree;
	level.scr_model[ "escape_chute_player" ]							= "ctl_parachute_player";	
			
}

/****************************************
		Price
****************************************/
#using_animtree( "generic_human" );
price_anims()
{
	level.scr_anim[ "price" ][ "intro" ]				= %ch_castle_1_1_price_chute_intro;
	
	level.scr_anim[ "price" ][ "chute_idle" ][0]		= %ch_castle_1_1_price_chute_idl;
	level.scr_anim[ "price" ][ "chute_left2right"] 		= %ch_castle_1_1_price_chute_left2right; 	
	level.scr_anim[ "price" ][ "chute_right2left"] 		= %ch_castle_1_1_price_chute_right2left; 		
	level.scr_anim[ "price" ][ "landing" ]				= %ch_castle_3_3_price_landing;
	
	level.scr_anim[ "price" ][ "chute_loop" ]			= %ch_castle_1_1_price_chute_idl_new;
	level.scr_anim[ "price" ][ "chute_right" ]			= %ch_castle_1_1_price_chute_rightturn_new;
	level.scr_anim[ "price" ][ "chute_left" ]			= %ch_castle_1_1_price_chute_leftturn_new;
	level.scr_anim[ "price" ][ "chute_up" ]				= %ch_castle_1_1_price_chute_updraft_new;
	
	// 	YURI!
	//level.scr_sound[ "price" ][ "landing" ] = "castle_pri_yuri";
	
	addNotetrack_customFunction( "price", "gun_in_hand", maps\castle_parachute::price_landing_gun, "landing" );
	addNotetrack_customFunction( "price", "fire", maps\castle_parachute::price_landing_shoot, "landing" );
	
	level.scr_anim[ "price" ][ "ruins_start" ]				= %ch_castle_4_1_price_startmove;
	level.scr_anim[ "price" ][ "ruins_talk" ]				= %ch_castle_4_1_price_speech;
	level.scr_anim[ "price" ][ "ruins_run_to_cover" ]		= %ch_castle_4_1_price_run2cover2;
	level.scr_anim[ "price" ][ "ruins_cover_wait" ][0]		= %ch_castle_4_1_price_cover2_wait;
	level.scr_anim[ "price" ][ "ruins_cover_hide" ]			= %ch_castle_4_1_price_cover2idl;
	level.scr_anim[ "price" ][ "ruins_run_to_patrol" ]		= %ch_castle_4_1_price_run2patrol;
//	level.scr_anim[ "price" ][ "ruins_patrol_hide" ][0]		= %ch_castle_4_1_price_patrol_hide_idle;
	
//	addNotetrack_dialogue( "price", "dialog01", "ruins_talk", "castle_pri_lookworried" ); // You looked worried, Yuri...	
//	addNotetrack_dialogue( "price", "dialog02", "ruins_talk", "castle_pri_trustme" ); // ... Don't you trust me?
	
	addNotetrack_customFunction( "price", "hide_pistol",  maps\castle_ruins::hide_pistol,  "ruins_talk" );	
//	addNotetrack_customFunction( "price", "start_patrol", maps\castle_ruins::do_second_patrol_group, "ruins_run_to_patrol" );
	addNotetrack_customFunction( "price", "start_patrol", maps\castle_ruins::ruins_patrol_lightning_flash, "lightning_flash" );
	
//	level.scr_anim[ "price" ][ "run_to_outlook" ]			= %ch_castle_4_2_price_run2outlook;
	level.scr_anim[ "price" ][ "do_not_engage" ][0]			= %ch_castle_5_1_price_do_not_engage;
//	level.scr_anim[ "price" ][ "put_on_goggles" ]			= %ch_castle_5_1_price_put_on_goggles;
//	level.scr_anim[ "price" ][ "night_watch" ][0]			= %ch_castle_5_1_price_nightwatch;
//	level.scr_anim[ "price" ][ "not_much_at_all" ]			= %ch_castle_5_1_price_not_much_at_all;
//	level.scr_anim[ "price" ][ "remove_goggles" ]			= %ch_castle_5_2_price_remove_goggles;
//	level.scr_anim[ "price" ][ "assess_situation" ][0]		= %ch_castle_5_2_price_assess_situation;
	
//	addNotetrack_customFunction( "price", "dialog02", maps\castle_courtyard_activity::nvg_line_check_1, "put_on_goggles" );
//	addNotetrack_customFunction( "price", "dialog06", maps\castle_courtyard_activity::nvg_line_check_2, "remove_goggles" );
//	addNotetrack_dialogue( "price", "dialog03", "not_much_at_all", "castle_pri_menpatrolling" ); // Ten men patrolling the area?
//	addNotetrack_dialogue( "price", "dialog04", "not_much_at_all", "castle_pri_notmuch" ); // Not much at all... This should be -  	
//	addNotetrack_dialogue( "price", "dialog05", "not_much_at_all", "castle_pri_shit" ); // SHIT! 	
//	addNotetrack_dialogue( "price", "dialog07", "remove_goggles", "castle_pri_youokay" ); // You alright?	
//	addNotetrack_customFunction( "price", "base_lights_on", maps\castle_courtyard_activity::base_lights_on, "not_much_at_all" );
	
	level.scr_anim[ "price" ][ "approach_overlook" ]		= %Castle_overlook_run_to_idle_price;
	
	level.scr_anim[ "price" ][ "security_office_talk" ]		= %ch_castle_6_1_security_office_price_talk;
	level.scr_anim[ "price" ][ "jump_down" ]				= %ch_castle_6_1_price_jump_down;
	
	addNotetrack_customFunction( "price", "dialog11", ::overlook_vo_1, "security_office_talk");
	addNotetrack_customFunction( "price", "dialog12", ::overlook_vo_2, "jump_down");
//	addNotetrack_dialogue( "price", "dialog11", "security_office_talk", "castle_pri_moveasimove" ); //When we're down there, you move when I move.  Do as I do.  Understand?
//	addNotetrack_dialogue( "price", "dialog12", "security_office_talk", "castle_pri_letsgo2" ); // Let's go.	.	
	addNotetrack_flag( "price", "dialog11", "start_stealth_guard_patroll", "security_office_talk" );
	
	level.scr_anim[ "price" ][ "move_to_stealth" ]			= %ch_castle_6_2_price_move2stealth;
	level.scr_anim[ "price" ][ "stealth_intro_wait" ][0]		= %ch_castle_6_2_price_wait_stealth_intro;
	level.scr_anim[ "price" ][ "stealth_intro" ]			= %ch_castle_6_2_price_stealth_intro;
	level.scr_anim[ "price" ][ "stealth_idle" ][0]			= %ch_castle_6_2_price_stealth_idl_truck;
	level.scr_anim[ "price" ][ "move_to_crawltruck" ]		= %ch_castle_6_2_price_stealth_move2_crawltruck;
	level.scr_anim[ "price" ][ "crawltruck_idle" ][0]		= %ch_castle_6_2_price_stealth_crawltruck_idl;
	level.scr_anim[ "price" ][ "crawltruck_crawl" ]			= %ch_castle_6_2_price_stealth_crawltruck_crawl;
	addNotetrack_customFunction( "price", "price_is_prone", ::price_disable_ragdoll, "crawltruck_crawl" );
	level.scr_anim[ "price" ][ "crawltruck_under_idle" ][0]	= %ch_castle_6_2_price_stealth_crawltruck_prone_idl;
	level.scr_anim[ "price" ][ "crawltruck_to_run" ]		= %ch_castle_6_2_price_stealth_crawltruck_crawl2run;
		addNotetrack_customFunction( "price", "price_is_not_prone", ::price_enable_ragdoll, "crawltruck_to_run" );
	
	level.scr_anim[ "price" ][ "melee_idle" ][0]			= %ch_castle_6_2_price_truck_idl;
	level.scr_anim[ "price" ][ "place_charge" ]				= %ch_castle_6_2_price_sets_charge;
	addNotetrack_customFunction( "price", "bomb_appear",  maps\castle_courtyard_stealth::place_price_bomb_model,  "place_charge" );
	addNotetrack_customFunction( "price", "bomb_plant", maps\castle_courtyard_stealth::remove_price_bomb_model, "place_charge" );
	
	level.scr_anim[ "price" ][ "indicate_guard" ]			= %ch_castle_6_2_price_indicates_guard;
	level.scr_anim[ "price" ][ "stealth_catch" ]			= %ch_castle_6_2_price_catch;
	level.scr_anim[ "price" ][ "stealth_melee" ]			= %castle_6_2_spotlight_kill_price;
	
	level.scr_anim[ "price" ][ "road_sprint_into" ]			= %ch_castle_6_2_price_sprint_setup_crouch2idl;
	level.scr_anim[ "price" ][ "road_sprint_wait_loop" ][0]	= %ch_castle_6_2_price_sprint_setup_start_idl;
	level.scr_anim[ "price" ][ "road_sprint" ]				= %ch_castle_6_2_price_sprint;
	level.scr_anim[ "price" ][ "road_sprint_end_loop" ][0]	= %ch_castle_6_2_price_sprint_end_idl;
	level.scr_anim[ "price" ][ "road_sprint_exit" ]			= %ch_castle_6_2_price_exit_sprint_end;
	
	level.scr_anim[ "price" ][ "wait_before_backcrawl" ][0]	= %ch_castle_6_3_price_crawl_intro_start_idl;
	level.scr_anim[ "price" ][ "move_to_backcrawl" ]		= %ch_castle_6_3_price_crawl_intro_move2crawl;
	level.scr_anim[ "price" ][ "get_into_backcrawl" ]		= %ch_castle_6_3_price_crawl_intro_ready2crawl;
	addNotetrack_customFunction( "price", "price_is_prone", ::price_disable_ragdoll, "get_into_backcrawl" );
	
	level.scr_anim[ "price" ][ "price_shoot_guard" ] = %ch_castle_6_2_price_shoot_melee;
	addNotetrack_customFunction( "price", "start_guard_anim", ::price_shoot_guard_animation, "price_shoot_guard" );
	
//	level.scr_anim[ "price" ][ "backcrawl_a" ]				= %ch_castle_6_3_price_backward_crawl_a;
//	level.scr_anim[ "price" ][ "backcrawl_idle_a" ][0]		= %ch_castle_6_3_price_backward_crawl_a_wait;
//	level.scr_anim[ "price" ][ "backcrawl_stoptalk" ]		= %ch_castle_6_3_price_backward_crawl_a_stoptalk;
	
	level.scr_anim[ "price" ][ "backcrawl_gap" ]			= %ch_castle_6_3_price_backward_crawl_b;
	addNotetrack_flag( "price", "price_says_wait", "price_says_wait", "backcrawl_gap" );
	
	level.scr_anim[ "price" ][ "backcrawl_gap_idle" ][0]	= %ch_castle_6_3_price_backward_crawl_b_wait;
	level.scr_anim[ "price" ][ "backcrawl_bomb" ]			= %ch_castle_6_3_price_backward_crawl_c;
	level.scr_anim[ "price" ][ "backcrawl_stoptalk" ]		= %ch_castle_6_3_price_backward_crawl_c_stoptalk;
	level.scr_anim[ "price" ][ "backcrawl_bomb_idle" ][0]	= %ch_castle_6_3_price_backward_crawl_c_wait;
	
	level.scr_anim[ "price" ][ "backcrawl" ]				= %ch_castle_6_3_price_backward_crawl;
	level.scr_anim[ "price" ][ "backcrawl_idle" ][0]		= %ch_castle_6_3_price_backward_crawl_wait;
	
	level.scr_anim[ "price" ][ "backcrawl_exit1" ]			= %ch_castle_6_3_price_crawl_exit;
	addNotetrack_customFunction( "price", "price_is_not_prone", ::price_enable_ragdoll, "backcrawl_exit1" );
	level.scr_anim[ "price" ][ "backcrawl_exit_wait1" ][0]	= %ch_castle_6_3_price_hide1_idl;
	level.scr_anim[ "price" ][ "backcrawl_exit2" ]			= %ch_castle_6_3_price_move2hide2;
	level.scr_anim[ "price" ][ "backcrawl_exit_wait2" ][0]	= %ch_castle_6_3_price_crawl_exit_hide_idl;
	
	level.scr_anim[ "price" ][ "start_into_idle" ]	= %ch_castle_6_3_price_into_start_idl;
	level.scr_anim[ "price" ][ "bomb_plant_platform" ] = %ch_castle_6_3_price_crawl_plant_bomb;
	addNotetrack_customFunction( "price", "bomb_appear",  maps\castle_courtyard_stealth::place_price_bomb_model,  "bomb_plant_platform" );
	addNotetrack_customFunction( "price", "bomb_disappear", maps\castle_courtyard_stealth::remove_price_bomb_model, "bomb_plant_platform" );
	
	//Section 2
	//price in the security office
	level.scr_anim[ "price" ][ "security_office_run_up"] = %ch_castle_7_1_price_entry_run_up_steps;
	level.scr_anim[ "price" ][ "security_office_entry_idle" ][0]			= %ch_castle_7_1_price_entry_cover_idl;
	level.scr_anim[ "price" ][ "security_office_entry" ] 					= %castle_comm_office_entry_price;
	addNotetrack_customFunction( "price", "grab_pistol", maps\castle_prison_battle::grab_pistol, "security_office_entry" );
	addNotetrack_customFunction( "price", "knock1", maps\castle_prison_battle::knock1, "security_office_entry" );	
	addNotetrack_customFunction( "price", "knock2", maps\castle_prison_battle::knock2, "security_office_entry" );
	addNotetrack_customFunction( "price", "kill_right", maps\castle_prison_battle::kill_right, "security_office_entry" );	
	addNotetrack_customFunction( "price", "kill_left", maps\castle_prison_battle::kill_left, "security_office_entry" );	
	addNotetrack_customFunction( "price", "kill_mid", maps\castle_prison_battle::kill_mid, "security_office_entry" );	
	addNotetrack_customFunction( "price", "hide_pistol", maps\castle_prison_battle::hide_pistol, "security_office_entry" );
	addNotetrack_customFunction( "price", "hide_knife", maps\castle_prison_battle::hide_knife, "security_office_entry" );
	addNotetrack_customFunction( "price", "grab_rifle", maps\castle_prison_battle::grab_rifle, "security_office_entry" );
	
	level.scr_anim[ "price" ][ "security_office_drag" ]				= %ch_castle_7_5_price_drag_guard_price;
	addNotetrack_customFunction( "price", "door2_trigger", maps\castle_prison_battle::door2_trigger, "security_office_drag" );
	addNotetrack_customFunction( "price", "monitor_trigger", maps\castle_prison_battle::monitor_trigger, "security_office_drag" );
	addNotetrack_customFunction( "price", "door_trigger", maps\castle_prison_battle::cage_pad_open, "security_office_drag" );
	addNotetrack_customFunction( "price", "dialogue01", maps\castle_prison_battle::dialogue01, "security_office_drag" );	
	addNotetrack_customFunction( "price", "dialogue02", maps\castle_prison_battle::dialogue02, "security_office_drag" );
	addNotetrack_customFunction( "price", "dialogue03", maps\castle_prison_battle::dialogue03, "security_office_drag" );	


	//price goes to switch and uses it
	level.scr_anim[ "price" ][ "goto_power_switch" ]			= %ch_castle_7_6_price_run_stairs;
	level.scr_anim[ "price" ][ "power_switch_wait" ][0]			= %ch_castle_7_6_price_light_switch_idl;
	level.scr_anim[ "price" ][ "power_switch_off" ]				= %ch_castle_7_6_price_lights_off;	
	addNotetrack_customFunction( "price", "lights_off", maps\castle_prison_battle::lights_off, "power_switch_off" );

	//Price closes the door to the prison (close to scaffolding) and talks a bit
	level.scr_anim[ "price" ][ "prison_exit_briefing_open" ]			= %ch_castle_8_7_price_door_briefing;
	level.scr_anim[ "price" ][ "prison_exit_briefing_open_idle" ][0]	= %ch_castle_8_7_price_door_briefing_idl;
	level.scr_anim[ "price" ][ "prison_exit_briefing_close" ]			= %ch_castle_8_7_price_door_briefing_close;
	
	level.scr_anim[ "price" ][ "bridge_instruct_bombplant" ] 		= %ch_castle_9_2_price_instructs_bombplant;
	level.scr_anim[ "price" ][ "bridge_instruct_idle" ][0]					= %ch_castle_9_2_price_instructs_idl;
	level.scr_anim[ "price" ][ "bridge_shimmy" ]					= %ch_castle_9_2_price_shimmy;
	level.scr_anim[ "price" ][ "bridge_mantle" ]					= %ch_castle_9_2_price_mantle_scaffold;
	
	level.scr_anim[ "price" ][ "wet_wall_investigate" ] 			= %ch_castle_10_1_price_kneel_down;
	level.scr_anim[ "price" ][ "wet_wall_place_detcord" ] 			= %ch_castle_10_2_price_set_det_chord;
	level.scr_anim[ "price" ][ "wet_wall_signal_move_to_window" ]	= %ch_castle_10_2_price_signal_run_to_window;
	level.scr_anim[ "price" ][ "wet_wall_signal_idle" ][0]			= %ch_castle_10_2_price_signal_idl;
	level.scr_anim[ "price" ][ "wet_wall_signal_flash" ] 			= %ch_castle_10_2_price_signals_detonate;
	level.scr_anim[ "price" ][ "spiderclimb_enter" ]				= %ch_castle_10_3_wall_enter_price;

	//addNotetrack_dialogue( "price", "dialogue01", "spiderclimb_enter", "castle_pri_sewagesystem" );	//	Shit... The cavity must be part of the castle's old sewage system?
	//addNotetrack_dialogue( "price", "dialogue02", "spiderclimb_enter", "castle_pri_holdyourbreath" );	//	You might want to hold your breath.	
	//addNotetrack_dialogue( "price", "dialogue03", "spiderclimb_enter", "castle_pri_comeon" ); 		//	Come on?
	
	level.scr_anim[ "price" ][ "spiderclimb_wait_idle" ][0]			= %ch_castle_10_4_looking_down_price;
	level.scr_anim[ "price" ][ "spiderclimb_climb_up" ]				= %ch_castle_10_4_spider_walk_price;
	level.scr_anim[ "price" ][ "peep_show_wait_idle" ][0]			= %ch_castle_10_5_wait_idle_price;
	level.scr_anim[ "price" ][ "peep_show" ]						= %ch_castle_10_5_peep_show_price;

	//addNotetrack_dialogue( "price", "dialogue18", "peep_show", "castle_pri_wrong" );	//	Something's wrong.
	//addNotetrack_dialogue( "price", "dialogue20",  "peep_show", "castle_pri_withthis" );		//	This should buy us some time.
	addNotetrack_customFunction( "price", "dialogue15", maps\castle_into_wet_wall::price_VO1, "peep_show" );
	addNotetrack_customFunction( "price", "dialogue16", maps\castle_into_wet_wall::price_VO2, "peep_show" );
	addNotetrack_customFunction( "price", "dialogue18", maps\castle_into_wet_wall::price_VO3, "peep_show" );
	addNotetrack_customFunction( "price", "dialogue20", maps\castle_into_wet_wall::price_VO4, "peep_show" );
	addNotetrack_customFunction( "price", "grenade_pullout", maps\castle_into_wet_wall::wetwall_grenade, "peep_show" );
	
	level.scr_anim[ "price" ][ "peep_show_fall" ]					= %ch_castle_10_9_wall_fall_price;

	//Section 3
	//run up the stairs to the generator rooom
	level.scr_anim[ "price" ][ "stair_start" ][0]			= %ch_castle_12_1_price_pacing_startidl;
	level.scr_anim[ "price" ][ "stair_move" ]				= %ch_castle_12_1_price_pacing_move;
	level.scr_anim[ "price" ][ "stair_wait" ][0]			= %ch_castle_12_1_price_pacing_waitidl;
	level.scr_anim[ "price" ][ "stair_finish" ]				= %ch_castle_12_1_price_pacing_exit;
	
		
	//react to flash grenade
	level.scr_anim[ "price" ][ "flash_react" ]				= %ch_castle_12_3_price_flash_react;
	level.scr_anim[ "price" ][ "flash_effect" ]				= %exposed_flashbang_v1;
	
	//slide over table
	level.scr_anim[ "price" ][ "table_slide" ]				= %ch_castle_12_1_price_table_mantle;
	
	//custom melee out of courtyard
	//level.scr_anim[ "price" ][ "inner_courtyard_door_kick"] = %ch_castle_13_1_kick_door_price;
	//level.scr_anim[ "price" ][ "inner_courtyard_melee" ]	= %ch_castle_13_1_takedown_price_price;
	
	//addNotetrack_customFunction( "price", "kick", maps\castle_inner_courtyard::door_kick, "inner_courtyard_door_kick" );
		
	//telling Yuri to trigger the C4
	level.scr_anim[ "price" ][ "overlook_intro" ]			= %ch_castle_14_2_move2idl;
	level.scr_anim[ "price" ][ "overlook_idle" ][0]			= %ch_castle_14_2_detonate_charge_price_idl;
	level.scr_anim[ "price" ][ "overlook_talk" ]			= %ch_castle_14_2_detonate_charge_price_talk;
	level.scr_anim[ "price" ][ "overlook_nag" ]				= %ch_castle_14_2_detonate_charge_price_nag;
	level.scr_anim[ "price" ][ "overlook_exit" ]			= %ch_castle_14_2_detonate_charge_price_exit;
	
	//custom shoot on the bridge
	level.scr_anim[ "price" ][ "bridge_idle" ][0]			= %ch_castle_14_5_price_shoots_guard_price_idl;
	//level.scr_anim[ "price" ][ "bridge_resume" ]			= %ch_castle_14_5_price_shoots_guard_price_resume;
	//level.scr_anim[ "price" ][ "bridge_shoot" ]				= %ch_castle_14_5_price_shoots_guard_price_shoot;
	
	//detonate C4 in outer courtyard
	//level.scr_anim[ "price" ][ "c4_detonate_idle" ][0]		= %ch_castle_14_7_price_detonates_motorpool_idl;
	//level.scr_anim[ "price" ][ "c4_detonate" ]				= %ch_castle_14_7_price_detonates_motorpool_trigger;
	
	//addNotetrack_dialogue( "price", "dialog", "c4_detonate", "castle_pri_detonating" ); //	Detonating C4... NOW!	
	//addNotetrack_customFunction( "price", "boom", maps\castle_courtyard_battle::courtyard_detonate_c4, "c4_detonate" );

	//run down the hill sequence
	/*level.scr_anim[ "price" ][ "escape_turn" ]				= %ch_castle_15_5_turn_price;
	level.scr_anim[ "price" ][ "escape_hill" ]				= %ch_castle_15_5_downhill_sprint_price;
	level.scr_anim[ "price" ][ "escape_jump" ]				= %ch_castle_15_5_jump_price;
	level.scr_anim[ "price" ][ "escape_parachute" ]			= %ch_castle_15_6_parachute_price;
	level.scr_anim[ "price" ][ "escape_land" ]				= %ch_castle_15_6_wait_price;
	level.scr_anim[ "price" ][ "escape_finish" ]			= %ch_castle_15_7_end_vignette_price;
	level.scr_anim[ "price" ][ "crawling_death"]            = %dying_crawl_death_v1;*/
	                          
	
//	addNotetrack_customFunction( "price", "dialog01", maps\castle_escape_new::variant_vo, "escape_finish" );
	//addNotetrack_dialogue( "price", "dialog02", "escape_finish", "castle_pri_cantletmakarov" ); // We can't let Makarov get to the President's daughter?
	//addNotetrack_dialogue( "price", "dialog03", "escape_finish", "castle_pri_wordtosandman2" ); // Let's get the Hell out of here and get the word to Sandman.
	//addNotetrack_customFunction( "price", "fade_out", maps\castle_escape_new::level_end, "escape_finish" );
	
	//idling in truck
	level.scr_anim[ "price" ][ "truck_idle"][0]            = %castle_truck_escape_wait_idle_price;
	
	//start driving
	level.scr_anim[ "price" ][ "truck_start_drive"]           = %castle_truck_escape_drive_start_price;
	level.scr_anim[ "price" ][ "truck_turn_left"]             = %castle_truck_escape_turn_left_price;
	level.scr_anim[ "price" ][ "truck_turn_right"]            = %castle_truck_escape_turn_right_price;
	level.scr_anim[ "price" ][ "truck_hit_react"]            = %castle_truck_escape_crash_reaction_price;	
	
	
	level.scr_anim[ "price" ][ "cliffjump_new"]            = %castle_truck_escape_price;
	
	

		
}



generic_human()
{
	/****************************************
			Generic Enemies
	****************************************/
	//
	
	level.scr_animtree["security_guard_chair"] = #animtree;
	
	level.scr_anim[ "generic" ][ "kitchen_death" ] = %dying_back_death_v1;
	
	//Landing Guards
	level.scr_anim[ "landing_guard1" ][ "landing" ]	= %ch_castle_3_3_price_landing_guard_1;
//	level.scr_anim[ "landing_guard2" ][ "landing" ]	= %ch_castle_3_3_price_landing_guard_2;
	level.scr_anim[ "landing_guard2" ][ "react_to_parachute" ] = %patrol_bored_react_walkstop;
	
	level.scr_anim[ "ruins_patroller1" ][ "ruins_patrol" ]						= %ch_castle_4_2_patrol_guard_1;
	level.scr_anim[ "ruins_patroller2" ][ "ruins_patrol" ]						= %ch_castle_4_2_patrol_guard_2;
//	level.scr_anim[ "ruins_patroller3" ][ "ruins_patrol" ]						= %ch_castle_4_2_patrol_guard_3;
	level.scr_anim[ "ruins_patroller3" ][ "ruins_patrol" ]						= %ch_castle_4_2_patrol_guard_3_walk;
//	level.scr_anim[ "ruins_patroller3" ][ "ruins_patrol_wait" ][0] 				= %ch_castle_4_2_patrol_guard_3_wait;
//	level.scr_anim[ "ruins_patroller3" ][ "ruins_patrol_continue" ]				= %ch_castle_4_2_patrol_guard_3_sweep;
//	level.scr_anim[ "ruins_patroller4" ][ "ruins_patrol" ]						= %ch_castle_4_2_patrol_guard_4;
	level.scr_anim[ "ruins_patroller4" ][ "ruins_patrol" ]						= %ch_castle_4_2_patrol_guard_4_walk;
	
	//Courtyard Activity
	level.scr_anim[ "activity_initial_group2_guard1" ][ "courtyard_activity" ]	= %ch_castle_5_3_heavy_activity_2_guard1_initial;
	level.scr_anim[ "activity_initial_group2_guard2" ][ "courtyard_activity" ]	= %ch_castle_5_3_heavy_activity_2_guard2_initial;
	level.scr_anim[ "activity_initial_group2_guard3" ][ "courtyard_activity" ]	= %ch_castle_5_3_heavy_activity_2_guard3_initial;	
	
	level.scr_anim[ "activity_group2_guard1" ][ "courtyard_activity" ]			= %ch_castle_5_3_heavy_activity_2_guard1;
	//level.scr_anim[ "activity_group2_guard1" ][ "courtyard_activity_idle" ][0]	= %ch_castle_5_3_heavy_activity_2_guard1_idl;
	level.scr_anim[ "activity_group2_guard2" ][ "courtyard_activity" ]			= %ch_castle_5_3_heavy_activity_2_guard2;
	level.scr_anim[ "activity_group2_guard2" ][ "courtyard_activity_idle" ][0]	= %ch_castle_5_3_heavy_activity_2_guard2_idl;
	level.scr_anim[ "activity_group2_guard3" ][ "courtyard_activity" ]			= %ch_castle_5_3_heavy_activity_2_guard3;
	level.scr_anim[ "activity_group2_guard3" ][ "courtyard_activity_idle" ][0]	= %ch_castle_5_3_heavy_activity_2_guard3_idl;

	level.scr_anim[ "activity_group3_guard1" ][ "courtyard_activity" ]			= %ch_castle_5_3_heavy_activity_3_guard1;
	level.scr_anim[ "activity_group3_guard1" ][ "courtyard_activity_idle" ][0]	= %ch_castle_5_3_heavy_activity_3_guard1_idl;
	level.scr_anim[ "activity_group3_guard2" ][ "courtyard_activity" ]			= %ch_castle_5_3_heavy_activity_3_guard2;
	level.scr_anim[ "activity_group3_guard2" ][ "courtyard_activity_idle" ][0]	= %ch_castle_5_3_heavy_activity_3_guard2_idl;
//	level.scr_anim[ "activity_group3_guard3" ][ "courtyard_activity" ]			= %ch_castle_5_3_heavy_activity_3_guard3;
	//level.scr_anim[ "activity_group3_guard3" ][ "courtyard_activity_idle" ][0]	= %ch_castle_5_3_heavy_activity_3_guard3_idl;
	
	level.scr_anim[ "btr_lift_guard1" ][ "courtyard_activity_runup" ]			= %ch_castle_5_4_btr_lift_guard1_runup;
	level.scr_anim[ "btr_lift_guard2" ][ "courtyard_activity_runup" ]			= %ch_castle_5_4_btr_lift_guard2_runup;
	level.scr_anim[ "btr_lift_guard3" ][ "courtyard_activity_runup" ]			= %ch_castle_5_4_btr_lift_guard3_runup;
	level.scr_anim[ "btr_lift_guard4" ][ "courtyard_activity_runup" ]			= %ch_castle_5_4_btr_lift_guard4_runup;
	level.scr_anim[ "btr_lift_guard5" ][ "courtyard_activity_runup" ]			= %ch_castle_5_4_btr_lift_guard5_runup;
	level.scr_anim[ "btr_lift_guard1" ][ "courtyard_activity" ]					= %ch_castle_5_4_btr_lift_guard1;
	level.scr_anim[ "btr_lift_guard1" ][ "courtyard_activity_idle" ][0]			= %ch_castle_5_4_btr_lift_guard1_endidl;
	level.scr_anim[ "btr_lift_guard2" ][ "courtyard_activity" ]					= %ch_castle_5_4_btr_lift_guard2;
	level.scr_anim[ "btr_lift_guard2" ][ "courtyard_activity_idle" ][0]			= %ch_castle_5_4_btr_lift_guard2_endidl;
	level.scr_anim[ "btr_lift_guard3" ][ "courtyard_activity" ]					= %ch_castle_5_4_btr_lift_guard3;
	level.scr_anim[ "btr_lift_guard3" ][ "courtyard_activity_idle" ][0]			= %ch_castle_5_4_btr_lift_guard3_endidl;
	level.scr_anim[ "btr_lift_guard4" ][ "courtyard_activity" ]					= %ch_castle_5_4_btr_lift_guard4;
	level.scr_anim[ "btr_lift_guard4" ][ "courtyard_activity_idle" ][0]			= %ch_castle_5_4_btr_lift_guard4_endidl;
	level.scr_anim[ "btr_lift_guard5" ][ "courtyard_activity" ]					= %ch_castle_5_4_btr_lift_guard5;
	
	// road patrol
	level.scr_anim[ "activity_group2_guard_walker1" ][ "pairguards_idle" ][0]	= %ch_castle_6_2_pairguard1_idl;
	level.scr_anim[ "activity_group2_guard_walker2" ][ "pairguards_idle" ][0]	= %ch_castle_6_2_pairguard2_idl;
	
	//Motorpool
	level.scr_anim[ "activity_group2_guard3" ][ "truckguard_idle" ][0]	= %ch_castle_6_2_truckguard;
	
//	level.scr_anim[ "activity_group2_guard1" ][ "pairguards_intro" ]	= %ch_castle_6_2_pairguard1_introidl;
	level.scr_anim[ "activity_group2_guard1" ][ "pairguards_idle" ][0]	= %ch_castle_6_2_pairguard1_idl;
	level.scr_anim[ "activity_group2_guard1" ][ "pairguards_walk" ]		= %ch_castle_6_2_pairguard1_walk;
	
//	level.scr_anim[ "activity_group2_guard2" ][ "pairguards_intro" ]	= %ch_castle_6_2_pairguard2_introwalk;
	level.scr_anim[ "activity_group2_guard2" ][ "pairguards_idle" ][0]	= %ch_castle_6_2_pairguard2_idl;
	level.scr_anim[ "activity_group2_guard2" ][ "pairguards_walk" ]		= %ch_castle_6_2_pairguard2_walk;
	
	//Stealth
//	level.scr_anim[ "melee_victim" ][ "stealth_melee" ] 			= %castle_contextual_melee_searchlight_victim;
	level.scr_anim[ "melee_victim" ][ "stealth_melee" ] 			= %castle_6_2_spotlight_kill_guard;
	
//	addNotetrack_customFunction( "melee_victim", "start_ragdoll", maps\castle_courtyard_stealth::kill_melee_victim, "stealth_melee" );
	level.scr_anim[ "melee_victim" ][ "stealth_catch" ] 				= %ch_castle_6_2_price_catch_guard;
	level.scr_anim[ "melee_victim" ][ "stealth_catch_loop" ][0] 		= %ch_castle_6_2_price_catch_guard_deadloop;

	//price shoot guard animation
	level.scr_anim[ "melee_victim" ][ "price_shoot_melee" ] = %ch_castle_6_2_price_shoot_melee_guard;
	level.scr_anim[ "melee_victim" ][ "price_shoot_melee_dead" ][0] = %ch_castle_6_2_price_shoot_melee_guard_deadloop;
	
	//Platform Guards
	level.scr_anim[ "platformguard1" ][ "platform_idle" ][0]		= %ch_castle_6_3_crawl_guards_guard1_startidl;
	level.scr_anim[ "platformguard1" ][ "platform_walk" ]			= %ch_castle_6_3_crawl_guards_guard1_walk;
	level.scr_anim[ "platformguard1" ][ "platform_idle_end" ][0]	= %ch_castle_6_3_jumping_guard_startidl;
	level.scr_anim[ "platformguard1" ][ "jump_down" ]				= %ch_castle_6_3_jumping_guard;
	
	level.scr_anim[ "platformguard2" ][ "platform_idle" ][0]		= %ch_castle_6_3_crawl_guards_guard2_startidl;
	level.scr_anim[ "platformguard2" ][ "platform_walk" ]			= %ch_castle_6_3_crawl_guards_guard2_walk;
	level.scr_anim[ "platformguard2" ][ "platform_idle_end" ][0]	= %ch_castle_6_3_crawl_guards_guard2_endidl;
	
	level.scr_anim[ "platformguard3" ][ "platform_idle" ][0]		= %ch_castle_6_3_crawl_guards_guard3_startidl;
	level.scr_anim[ "platformguard3" ][ "platform_walk" ]			= %ch_castle_6_3_crawl_guards_guard3_walk;
	level.scr_anim[ "platformguard3" ][ "platform_idle_end" ][0]	= %ch_castle_6_3_crawl_guards_guard3_endidl;
	
	level.scr_anim[ "platformguard4" ][ "platform_idle" ][0]		= %ch_castle_6_3_crawl_guards_guard4_startidl;
	level.scr_anim[ "platformguard4" ][ "platform_walk" ]			= %ch_castle_6_3_crawl_guards_guard4_walk;
	level.scr_anim[ "platformguard4" ][ "platform_idle_end" ][0]	= %ch_castle_6_3_crawl_guards_guard4_endidl;
	
	level.scr_anim[ "platformguard5" ][ "platform_idle" ][0]		= %ch_castle_6_3_crawl_guards_guard5_startidl;
	level.scr_anim[ "platformguard5" ][ "platform_walk" ]			= %ch_castle_6_3_crawl_guards_guard5_walk;
	level.scr_anim[ "platformguard5" ][ "platform_idle_end" ][0]	= %ch_castle_6_3_crawl_guards_guard5_endidl;
	
	//Escort enemies
	level.scr_anim[ "generic" ][ "patrol_bored_idle" ][0] = %patrol_bored_idle;

	//Section 2: Security Office
	level.scr_anim[ "security_guard_1" ][ "security_office_idle" ][0]							= %ch_castle_7_3_guard1_idle;
	level.scr_anim[ "security_guard_1" ][ "security_office_react" ]								= %ch_castle_7_3_guard1;
	level.scr_anim[ "security_guard_2" ][ "security_office_react" ]								= %exposed_idle_reactB;
	level.scr_anim[ "security_guard_2" ][ "generic_death" ]										= %exposed_death_falltoknees;
	level.scr_anim[ "security_guard_3" ][ "security_office_entry_guard" ]						= %castle_comm_office_entry_guard;
	addNotetrack_customFunction( "security_guard_3", "stab_enter", maps\castle_prison_battle::stab_enter, "security_office_entry_guard" );
	addNotetrack_customFunction( "security_guard_3", "throat_cut", maps\castle_prison_battle::throat_cut, "security_office_entry_guard" );
	addNotetrack_customFunction( "security_guard_3", "land", maps\castle_prison_battle::land, "security_office_entry_guard" );
	addNotetrack_customFunction( "security_guard_3", "kill_dude", maps\castle_prison_battle::kill_dude, "security_office_entry_guard" );
	
	level.scr_anim[ "security_guard_chair" ][ "security_office_guard_chair_idle" ][ 0 ]			= %ch_castle_7_2_guard_chair_idl;
	level.scr_anim[ "security_guard_chair" ][ "security_office_react" ]							= %ch_castle_7_2_guard_chair;
	level.scr_anim[ "security_guard_chair" ][ "security_office_react_stand" ]					= %ch_castle_7_2_guard_chair_to_stand;
	level.scr_anim[ "security_guard_chair" ][ "security_office_react_death" ]					= %ch_castle_7_2_guard_chair_death_fall;
	level.scr_anim[ "security_guard_chair" ][ "security_office_guard_chair_death_idle" ][ 0 ] 	= %ch_castle_7_2_guard_chair_death_idl;

	level.scr_anim[ "security_guard_chair" ][ "security_office_drag" ]					= %ch_castle_7_5_price_drag_guard_guard;
	level.scr_anim[ "security_guard_chair" ][ "security_office_guard_drag_end" ][ 0 ]	= %ch_castle_7_5_price_drag_guard_guard_end_idle;
	
	//Section 2: Prisoners
	level.scr_anim[ "prisoner1" ][ "harass_loop" ][ 0 ]			= %ch_castle_7_1_guard_taunting_prisoner_loop;
	level.scr_anim[ "prisoner1" ][ "harass_react" ]				= %ch_castle_7_1_guard_taunting_prisoner_react;
	level.scr_anim[ "prisoner1" ][ "harass_end_loop" ][ 0 ]		= %ch_castle_7_1_guard_taunting_prisoner_end_idl;;
	level.scr_anim[ "prisoner3" ][ "harass_loop" ][ 0 ]			= %ch_castle_7_1_guard_taunting_prisoner3_loop;
	level.scr_anim[ "prisoner3" ][ "harass_react" ]				= %ch_castle_7_1_guard_taunting_prisoner3_react;
	level.scr_anim[ "prisoner3" ][ "harass_end_loop" ][ 0 ]		= %ch_castle_7_1_guard_taunting_prisoner3_end_idl;;

	//GUARDS rattling prisoners
	level.scr_anim[ "guard3" ][ "harass_loop" ][ 0 ]			= %ch_castle_7_1_guard3_taunting_loop;
	level.scr_anim[ "guard3" ][ "harass_react" ]				= %ch_castle_7_1_guard3_taunting_react;	
	level.scr_anim[ "guard3" ][ "blinded_react_loop"][0] 		= %castle_dungeon_blind_idle_guard;	
	
	level.scr_anim[ "generic" ][ "payback_pmc_sandstorm_stumble_1_single"]		= %payback_pmc_sandstorm_stumble_1;
	level.scr_anim[ "generic" ][ "payback_pmc_sandstorm_stumble_1"][0]			= %payback_pmc_sandstorm_stumble_1;
	
	level.scr_anim[ "generic" ][ "castle_dungeon_blind_idle_guard_single"]		= %castle_dungeon_blind_idle_guard;
	level.scr_anim[ "generic" ][ "castle_dungeon_blind_idle_guard"][0]			= %castle_dungeon_blind_idle_guard;
	level.scr_anim[ "generic" ][ "find_wall_guard"]								= %castle_dungeon_find_wall_guard;
	level.scr_anim[ "generic" ][ "stair_stumble_back_guard"]					= %castle_dungeon_stair_stumble_back_guard;
	level.scr_anim[ "generic" ][ "stair_stumble_forward_guard"]					= %castle_dungeon_stair_stumble_forward_guard;	

	level.scr_anim[ "generic" ][ "corner_standR_alert_idle" ][0]				= %corner_standR_alert_idle;
	level.scr_anim[ "generic" ][ "covercrouch_blindfire_1" ]					= %covercrouch_blindfire_1;
	level.scr_anim[ "generic" ][ "covercrouch_hide_idle" ][0]					= %covercrouch_hide_idle;
	level.scr_anim[ "generic" ][ "cover_twitch_01" ]							= %covercrouch_twitch_1;
	level.scr_anim[ "generic" ][ "cover_twitch_02" ]							= %covercrouch_blindfire_1;	

	// PRISONERS unaligned anims for cell filling
	level.scr_anim[ "generic" ][ "prisoner_cower2" ][ 0 ]			= %ch_castle_8_5_prisoner_cower_2;
	level.scr_anim[ "generic" ][ "prisoner_shake1" ][ 0 ]			= %ch_castle_8_5_prisoner_shake_cage_1;
	level.scr_anim[ "generic" ][ "prisoner_pace_lean" ][0]			= %ch_castle_8_8_cell_1_guy1;  // guy leaning against wall on left arm, pacing
	level.scr_anim[ "generic" ][ "prisoner_sitting" ][0]			= %ch_castle_8_8_cell_1_guy2;  //guy sitting, right arm on knee
	level.scr_anim[ "generic" ][ "prisoner_arms_crossed" ][0]		= %ch_castle_8_8_cell_1_guy4;  //guy leaning up against wall with arms crossed
	level.scr_anim[ "generic" ][ "prisoner_cowering_floor" ][0]		= %ch_castle_8_8_cell_2_guy2;  //guy cowering on floor
	level.scr_anim[ "generic" ][ "prisoner_shifting_looking" ][0]	= %ch_castle_8_8_cell_2_guy7;  //guy shifting on feet looking out of cell
	level.scr_anim[ "generic" ][ "prisoner_shifting_looking2" ][0]	= %ch_castle_8_8_cell_3_guy3;  //guy shifting on feet looking of cell2
	level.scr_anim[ "generic" ][ "prisoner_shaking_bars1" ][0]		= %ch_castle_8_8_cell_6_guy5;  //guy shaking cage
	level.scr_anim[ "generic" ][ "prisoner_shaking_bars2" ][0]		= %ch_castle_8_8_cell_3_guy5;  //guy shaking cage2
	level.scr_anim[ "generic" ][ "prisoner_pacing_gesturing" ][0]	= %ch_castle_8_8_cell_6_guy1;  //guy pacing, gesturing
	level.scr_anim[ "generic" ][ "prisoner_crouch_cower" ][0]		= %ch_castle_8_8_cell_4_guy2;  //guy crouch cowering (freakout)

	//flare room 
	level.scr_anim[ "generic" ][ "guard_flare_toss" ]						= %ch_castle_8_3_guard_flare;	
	
	//meatshield
	level.scr_anim[ "meatshield_guard" ][ "meatshield_start" ]				= %ch_castle_8_5_prisoner_hostage_guard;
	level.scr_anim[ "meatshield_prisoner" ][ "meatshield_start" ]			= %ch_castle_8_5_prisoner_hostage_prisoner;
	
	level.scr_anim[ "meatshield_guard" ][ "meatshield_idle" ][0]			= %ch_castle_8_5_prisoner_hostage_guard_idl;
	level.scr_anim[ "meatshield_prisoner" ][ "meatshield_idle" ][0]			= %ch_castle_8_5_prisoner_hostage_prisoner_idl;
	
	level.scr_anim[ "meatshield_prisoner" ][ "meatshield_dies" ]			= %ch_castle_8_5_prisoner_hostage_death;
	level.scr_anim[ "meatshield_prisoner" ][ "meatshield_dies_idle" ][0] 	= %ch_castle_8_5_prisoner_hostage_death_idle;

	level.scr_anim[ "meatshield_prisoner" ][ "meatshield_survives" ]		= %ch_castle_8_5_prisoner_hostage_prisoner_to_cover;
	level.scr_anim[ "meatshield_prisoner" ][ "meatshield_survives_idle" ][0]	= %ch_castle_8_5_prisoner_hostage_prisoner_to_cover_idl;

	level.scr_anim[ "meatshield_guard" ][ "meatshield_double_kill" ]		= %ch_castle_8_5_guard_double_kill;
	level.scr_anim[ "meatshield_prisoner" ][ "meatshield_double_kill" ]		= %ch_castle_8_5_prisoner_double_kill;

	// TV room 
	level.scr_anim[ "alexi" ][ "peep_show" ]								= %ch_castle_10_6_peep_show_alexei;
	addNotetrack_customFunction( "alexi", "dialogue12",  maps\castle_into_wet_wall::alexi_vo1,  "peep_show" ); //	Check with Security... Find out what's going on.
	addNotetrack_customFunction( "alexi", "dialogue14",  maps\castle_into_wet_wall::alexi_vo2,  "peep_show" ); //	Yes, sir... Our men in Berlin have no doubt?
	addNotetrack_customFunction( "alexi", "dialogue16",  maps\castle_into_wet_wall::alexi_vo3,  "peep_show" ); //	The daughter is there.  We will have her in a matter of hours.
	addNotetrack_customFunction( "alexi", "alarm_start",  maps\castle_into_wet_wall::alarm_start,  "peep_show" );
	
	level.scr_anim[ "tv_room_guy1" ][ "peep_show" ]							= %ch_castle_10_6_peep_show_henchman_01;
	level.scr_anim[ "tv_room_guy2" ][ "peep_show" ]							= %ch_castle_10_6_peep_show_henchman_02;
	level.scr_anim[ "tv_room_guy3" ][ "peep_show" ]							= %ch_castle_10_6_peep_show_henchman_03;
	addNotetrack_customFunction( "tv_room_guy3", "dialog01",  maps\castle_into_wet_wall::henchman3_vo,  "peep_show" );
	level.scr_anim[ "tv_room_guy4" ][ "peep_show" ]							= %ch_castle_10_6_peep_show_henchman_04;

	// TV Monitor
	level.scr_anim[ "makarov" ][ "tv_scene" ]		= %ch_castle_10_7_tv_monitor_makarov_cheap;
	addNotetrack_dialogue( "makarov", "dialogue08", "tv_scene", "castle_mkv_isee" );	//	I see?
	addNotetrack_dialogue( "makarov", "dialogue09", "tv_scene", "castle_mkv_thisiswhat" );	//	This is what we are dealing with, brothers....  	
	addNotetrack_dialogue( "makarov", "dialogue10", "tv_scene", "castle_mkv_oldman" );	//	...A stubborn old man, hopelessly out of step with the changing world.	
	addNotetrack_dialogue( "makarov", "dialogue11", "tv_scene", "castle_mkv_youtoo" );	//	You too, will change.	
	addNotetrack_dialogue( "makarov", "dialogue13", "tv_scene", "castle_mkv_confirmed" );	//	Alexi - Has your Intel been confirmed?	
	addNotetrack_dialogue( "makarov", "dialogue15", "tv_scene", "castle_mkv_listening" );	//	Are you listening?	
	addNotetrack_dialogue( "makarov", "dialogue17", "tv_scene", "castle_mkv_updated" );	//	Keep me updated.	

	level.scr_anim[ "president" ][ "tv_scene" ]		= %ch_castle_10_7_tv_monitor_president_cheap;
	addNotetrack_dialogue( "president", "dialogue04", "tv_scene", "castle_prs_forthelast" );	//	For the last... time?
	addNotetrack_dialogue( "president", "dialogue06", "tv_scene", "castle_prs_notbow" );	//	I...will not bow... to the demands... of terrorist thugs?
	addNotetrack_dialogue( "president", "dialogue07", "tv_scene", "castle_prs_iwilldie" );	//	I will die before I surrender the nuclear launch codes?

	// TV Room React
	level.scr_anim[ "alexi" ][ "peep_show_react" ]							= %ch_castle_10_8_discovered_alexei;
	addNotetrack_customFunction( "alexi", "dialogue17",  maps\castle_into_wet_wall::alexi_vo4,  "peep_show_react" );
	addNotetrack_customFunction( "alexi", "startshooting",  maps\castle_into_wet_wall::wet_wall_bullet_holes,  "peep_show_react" );
	addNotetrack_customFunction( "alexi", "slipstart",  maps\castle_into_wet_wall::slip_start,  "peep_show_react" );
	
	level.scr_anim[ "tv_room_guy1" ][ "peep_show_react" ]					= %ch_castle_10_8_discovered_henchman_01;
	addNotetrack_customFunction( "tv_room_guy1", "dialogue01",  maps\castle_into_wet_wall::henchman1_vo,  "peep_show_react" );
	level.scr_anim[ "tv_room_guy2" ][ "peep_show_react" ]					= %ch_castle_10_8_discovered_henchman_02;
	level.scr_anim[ "tv_room_guy3" ][ "peep_show_react" ]					= %ch_castle_10_8_discovered_henchman_03;

	// Kitchen battle
	level.scr_anim[ "kitchen_guy1" ][ "wall_break_react" ]					= %ch_castle_11_1_guard_entry_dive;
	level.scr_anim[ "kitchen_guy2" ][ "wall_break_react" ]					= %ch_castle_11_1_guard_entry_shotgun;
	level.scr_anim[ "kitchen_guy3" ][ "wall_break_react" ]					= %ch_castle_11_1_guard_entry_slide;
	level.scr_anim[ "kitchen_guy4" ][ "wall_break_react" ]					= %ch_castle_11_1_guard_run_out;
	level.scr_anim[ "kitchen_guy5" ][ "wall_break_react" ]					= %ch_castle_11_1_guard_cooking_grab_gun;
	level.scr_anim[ "generic" ][ "catch_fire" ]						= %ch_castle_11_1_guard_on_fire;
	
	//Section 3: Interior
	level.scr_anim[ "generic" ][ "guard_stumble" ]					= %ch_castle_12_1_guard_stumble;
	level.scr_anim[ "generic" ][ "guard_double_take" ]				= %ch_castle_12_5_guard_double_take;
	level.scr_anim[ "guarda" ][ "foyer_door_kick" ]					= %ch_castle_guard_doorkick_A;
	level.scr_anim[ "guardb" ][ "foyer_door_kick" ]					= %ch_castle_guard_doorkick_B;
	
	addNotetrack_customFunction( "guarda", "doorkick_A", maps\castle_interior::foyer_door_right, "foyer_door_kick" );
	addNotetrack_customFunction( "guardb", "doorkick_B", maps\castle_interior::foyer_door_left, "foyer_door_kick" );
	/*
	level.scr_anim[ "generic" ][ "inner_courtyard_entry_01" ]		= %ch_castle_13_1_guardentry_01;
	level.scr_anim[ "generic" ][ "inner_courtyard_entry_02" ]		= %ch_castle_13_1_guardentry_02;
	level.scr_anim[ "generic" ][ "inner_courtyard_entry_03" ]		= %ch_castle_13_1_guardentry_03;
	level.scr_anim[ "generic" ][ "inner_courtyard_entry_04" ]		= %ch_castle_13_1_guardentry_04;
	level.scr_anim[ "generic" ][ "inner_courtyard_entry_05" ]		= %ch_castle_13_1_guardentry_05;
	*/	
	//level.scr_anim[ "generic" ][ "inner_courtyard_truck_01" ]		= %ch_castle_13_1_guardentry_truck_01;
	//level.scr_anim[ "generic" ][ "inner_courtyard_truck_02" ]		= %ch_castle_13_1_guardentry_truck_02;
	//level.scr_anim[ "generic" ][ "inner_courtyard_truck_03" ]		= %ch_castle_13_1_guardentry_truck_03;
	level.scr_anim[ "generic" ][ "inner_courtyard_roof_fall" ]		= %ch_castle_13_1_guard_roof_fall;
	//level.scr_anim[ "guard" ][ "inner_courtyard_melee" ]			= %ch_castle_13_1_takedown_price_guard;
				
	level.scr_anim[ "guard0" ][ "bridge_entrance" ]					= %ch_castle_14_1_btr_escort_guard1;
	level.scr_anim[ "guard1" ][ "bridge_entrance" ]					= %ch_castle_14_1_btr_escort_guard2;
	level.scr_anim[ "guard2" ][ "bridge_entrance" ]					= %ch_castle_14_1_btr_escort_guard3;
	level.scr_anim[ "guard3" ][ "bridge_entrance" ]					= %ch_castle_14_1_btr_escort_guard4;
	level.scr_anim[ "guard4" ][ "bridge_entrance" ]					= %ch_castle_14_1_btr_escort_guard5;
	level.scr_anim[ "guard5" ][ "bridge_entrance" ]					= %ch_castle_14_1_btr_escort_guard6;
	level.scr_anim[ "guard6" ][ "bridge_entrance" ]					= %ch_castle_14_1_btr_escort_guard7;
	level.scr_anim[ "guard7" ][ "bridge_entrance" ]					= %ch_castle_14_1_btr_escort_guard8;
	level.scr_anim[ "guard8" ][ "bridge_entrance" ]					= %ch_castle_14_1_btr_escort_guard9;
	level.scr_anim[ "guard9" ][ "bridge_entrance" ]					= %ch_castle_14_1_btr_escort_guard10;
	level.scr_anim[ "guard0" ][ "bridge_idle" ][0]					= %ch_castle_14_1_btr_escort_guard1_idl;
	level.scr_anim[ "guard1" ][ "bridge_idle" ][0]					= %ch_castle_14_1_btr_escort_guard2_idl;
	level.scr_anim[ "guard2" ][ "bridge_idle" ][0]					= %ch_castle_14_1_btr_escort_guard3_idl;
	level.scr_anim[ "guard3" ][ "bridge_idle" ][0]					= %ch_castle_14_1_btr_escort_guard4_idl;
	level.scr_anim[ "guard4" ][ "bridge_idle" ][0]					= %ch_castle_14_1_btr_escort_guard5_idl;
	level.scr_anim[ "guard5" ][ "bridge_idle" ][0]					= %ch_castle_14_1_btr_escort_guard6_idl;
	level.scr_anim[ "guard6" ][ "bridge_idle" ][0]					= %ch_castle_14_1_btr_escort_guard7_idl;
	level.scr_anim[ "guard7" ][ "bridge_idle" ][0]					= %ch_castle_14_1_btr_escort_guard8_idl;
	level.scr_anim[ "guard8" ][ "bridge_idle" ][0]					= %ch_castle_14_1_btr_escort_guard9_idl;
	level.scr_anim[ "guard9" ][ "bridge_idle" ][0]					= %ch_castle_14_1_btr_escort_guard10_idl;
	level.scr_anim[ "guard0" ][ "bridge_alert" ]					= %ch_castle_14_1_btr_escort_guard1_idl2fire;
	level.scr_anim[ "guard1" ][ "bridge_alert" ]					= %ch_castle_14_1_btr_escort_guard2_idl2fire;
	level.scr_anim[ "guard2" ][ "bridge_alert" ]					= %ch_castle_14_1_btr_escort_guard3_idl2fire;
	level.scr_anim[ "guard3" ][ "bridge_alert" ]					= %ch_castle_14_1_btr_escort_guard4_idl2fire;
	level.scr_anim[ "guard4" ][ "bridge_alert" ]					= %ch_castle_14_1_btr_escort_guard5_idl2fire;
	level.scr_anim[ "guard5" ][ "bridge_alert" ]					= %ch_castle_14_1_btr_escort_guard6_idl2fire;
	level.scr_anim[ "guard6" ][ "bridge_alert" ]					= %ch_castle_14_1_btr_escort_guard7_idl2fire;
	level.scr_anim[ "guard7" ][ "bridge_alert" ]					= %ch_castle_14_1_btr_escort_guard8_idl2fire;
	level.scr_anim[ "guard8" ][ "bridge_alert" ]					= %ch_castle_14_1_btr_escort_guard9_idl2fire;
	level.scr_anim[ "guard9" ][ "bridge_alert" ]					= %ch_castle_14_1_btr_escort_guard10_idl2fire;
	level.scr_anim[ "guard0" ][ "bridge_explode" ]					= %ch_castle_14_3_flung_guard1;
	level.scr_anim[ "guard1" ][ "bridge_explode" ]					= %ch_castle_14_3_flung_guard2;
	level.scr_anim[ "guard2" ][ "bridge_explode" ]					= %ch_castle_14_3_flung_guard3;
	level.scr_anim[ "guard3" ][ "bridge_explode" ]					= %ch_castle_14_3_flung_guard4;
	level.scr_anim[ "guard4" ][ "bridge_explode" ]					= %ch_castle_14_3_flung_guard5;
	level.scr_anim[ "guard5" ][ "bridge_explode" ]					= %ch_castle_14_3_flung_guard6;
	level.scr_anim[ "guard6" ][ "bridge_explode" ]					= %ch_castle_14_3_flung_guard7;
	level.scr_anim[ "guard7" ][ "bridge_explode" ]					= %ch_castle_14_3_flung_guard8;
	level.scr_anim[ "guard8" ][ "bridge_explode" ]					= %ch_castle_14_3_flung_guard9;
	level.scr_anim[ "guard9" ][ "bridge_explode" ]					= %ch_castle_14_3_flung_guard10;
	level.scr_anim[ "guard0" ][ "bridge_dying" ][0]					= %ch_castle_14_5_guard1_dying;
	level.scr_anim[ "guard1" ][ "bridge_deadloop" ]				= %ch_castle_14_5_guard2_deadloop;
	level.scr_anim[ "guard2" ][ "bridge_deadloop" ]				= %ch_castle_14_5_guard3_deadloop;
	level.scr_anim[ "guard3" ][ "bridge_dying" ][0]					= %ch_castle_14_5_guard4_dying;
	level.scr_anim[ "guard7" ][ "bridge_deadloop" ]				= %ch_castle_14_5_guard8_deadloop;
	level.scr_anim[ "guard8" ][ "bridge_dying" ][0]					= %ch_castle_14_5_guard9_dying;
	level.scr_anim[ "guard0" ][ "bridge_death" ]					= %ch_castle_14_5_price_shoots_guard_guard1;
	level.scr_anim[ "guard0" ][ "bridge_deadloop" ]				= %ch_castle_14_5_price_shoots_guard_guard1dead;
	level.scr_anim[ "guard3" ][ "bridge_shot" ]						= %ch_castle_14_5_guard4_shot;
	level.scr_anim[ "guard3" ][ "bridge_deadloop" ]				= %ch_castle_14_5_guard4_deadloop;
	level.scr_anim[ "guard8" ][ "bridge_shot" ]						= %ch_castle_14_5_guard9_shot;
	level.scr_anim[ "guard8" ][ "bridge_deadloop" ]				= %ch_castle_14_5_guard9_deadloop;
}

#using_animtree( "vehicles" );
vehicle_anims()
{
	level.scr_anim[ "ai_parachute" ][ "intro" ] = %o_castle_1_1_parachute_intro;
	
	level.scr_anim[ "price_parachute" ][ "landing" ] = %o_castle_3_3_price_chute_landing;
	
	level.scr_anim[ "player_parachute" ][ "chute_deploy" ] = %castle_player_escape_chutepull_chute;
	level.scr_anim[ "player_parachute" ][ "chute_release" ] = %castle_player_escape_chuterelease_chute;
	level.scr_anim[ "price_parachute"][ "escape_parachute" ] = %o_castle_15_6_parachute_chute;
	
	level.scr_anim[ "btr" ][ "btr_lift" ] = %v_castle_5_4_btr_lift_btr;
	
	level.scr_anim[ "btr_helicopter" ][ "btr_lift" ] = %v_castle_5_4_btr_lift_heli;
	
	level.scr_anim[ "btr" ][ "bridge_entrance" ] = %v_castle_14_1_btr;
	level.scr_anim[ "btr" ][ "bridge_death" ] = %fxanim_castle_bridge_btr_anim;
	
	addNotetrack_flag( "btr", "btr_explode", "bridge_btr_kill", "bridge_death" );
	
	level.scr_anim[ "escape_truck_real" ][ "hit_gate" ] = %castle_truck_escape_player_view_adjust_at_cliff;	
	
	
}

#using_animtree( "animated_props" );
animated_props_anims()
{
	//		Wetwall Price grenade
	level.scr_animtree[ "peep_hole_grenade" ]						= #animtree;
	level.scr_model[ "peep_hole_grenade" ]							= "generic_prop_raven";
	level.scr_anim[ "peep_hole_grenade" ][ "wall_climb_grenade_toss" ]	= %o_castle_10_8_grenade_toss;	
	
	level.scr_anim[ "escape_truck" ][ "cliffjump_new" ]		= %castle_truck_escape_truck;	
	level.scr_animtree[ "escape_truck" ]						= #animtree;
	level.scr_model[ "escape_truck" ]								= "vehicle_uaz_open_player_ride";	
	
	//escape parachute for price
	level.scr_anim[ "escape_chute_price" ][ "cliffjump_new" ]		= %castle_truck_escape_prices_parachute;	
	level.scr_animtree[ "escape_chute_price" ]						= #animtree;
	level.scr_model[ "escape_chute_price" ]								= "ctl_parachute_deployable";	
	
	level.scr_anim[ "escape_chute_price_2" ][ "cliffjump_new" ]		= %castle_truck_escape_prices_parachute2;	
	level.scr_animtree[ "escape_chute_price_2" ]						= #animtree;
	level.scr_model[ "escape_chute_price_2" ]							= "ctl_parachute_ai";
	
		
	level.scr_animtree[ "player_rig_ripcord" ] 		= #animtree;
	level.scr_model[ "player_rig_ripcord" ] 		= "viewmodel_parachute_ripcord";
	level.scr_anim[ "player_rig_ripcord" ][ "escape_player_deploy_chute" ]			= %castle_truck_escape_player_deploy_chute_ripcord;

}

#using_animtree( "script_model" );
script_model_anims()
{
	// Price Intro Gun
	level.scr_animtree[ "price_pistol" ]									= #animtree;
	level.scr_model[ "price_pistol" ]									= "ctl_weapon_usp_silencer_animated";
	level.scr_anim[ "price_pistol" ][ "ruins_start" ]					= %o_castle_4_1_price_pistol_startmove;
	level.scr_anim[ "price_pistol" ][ "ruins_talk" ]					= %o_castle_4_1_price_pistol_speech;
	
	// 		Rope
	level.scr_animtree[ "btr_rope" ]				= #animtree;
	level.scr_model[ "btr_rope" ]					= "fxanim_castle_btr_rope_mod";
	level.scr_anim[ "btr_rope"][ "btr_lift" ] 		= %o_castle_5_4_btr_lift_rope;
	
	//		Chains
	level.scr_animtree[ "fxanim" ]										= #animtree;
	level.scr_anim[ "fxanim" ][ "fxanim_gp_chain_arch_sm" ][0]			= %fxanim_gp_chain_arch_sm_anim;
	level.scr_anim[ "fxanim" ][ "fxanim_gp_chain_short" ][0]			= %fxanim_gp_chain_short_anim;
	level.scr_anim[ "fxanim" ][ "fxanim_gp_chain_arch_sm_mod" ][0]		= %fxanim_gp_chain_arch_sm_anim;
	level.scr_anim[ "fxanim" ][ "fxanim_gp_chain_short_mod" ][0]		= %fxanim_gp_chain_short_anim;
	level.scr_anim[ "fxanim" ][ "fxanim_gp_chain_med_hook_mod" ][0]		= %fxanim_gp_chain_med_hook_anim;
	level.scr_anim[ "fxanim" ][ "fxanim_gp_chain_med_pulley_mod" ][0]	= %fxanim_gp_chain_med_pulley_anim;

	//		Generators
	level.scr_anim[ "fxanim" ][ "fxanim_castle_generator_mod" ][0] 	= %fxanim_castle_generator_anim;

	//		Cigarette
	level.scr_animtree[ "cigarette" ]							= #animtree;
	level.scr_model[ "cigarette" ]								= "bo_p_glo_cigarette01_animated";
	level.scr_anim[ "cigarette" ][ "platform_idle_end" ][0] 	= %o_castle_6_3_jumping_guard_cigarette_startidl;
	level.scr_anim[ "cigarette" ][ "jump_down" ] 				= %o_castle_6_3_jumping_guard_cigarette;
	
	//		Chair
	level.scr_animtree[ "chair" ]												= #animtree;
	level.scr_anim[ "chair" ][ "security_office_guard_chair_idle" ][0] 			= %o_castle_7_2_guard_chair_idl_chair;
	level.scr_anim[ "chair" ][ "security_office_guard_chair_move" ] 			= %o_castle_7_2_guard_chair_death_chair;
	level.scr_anim[ "chair" ][ "security_office_guard_chair_death_idle" ][0] 	= %o_castle_7_2_guard_chair_death_chair_idl;

	// 		Security Room entrance
	level.scr_animtree[ "door" ]											= #animtree;
	level.scr_model[ "door" ]												= "paris_catacombs_door_pry_kick_rigged";
	level.scr_anim[ "door" ][ "security_office_entry_door_close" ]			= %o_castle_7_2_entry_door_close;
	level.scr_anim[ "door" ][ "security_office_entry"]						= %castle_comm_office_entry_door;
	
	// 		Prison airlock door, outer
	level.scr_animtree[ "airlock_door" ]					= #animtree;
	level.scr_anim[ "airlock_door" ][ "security_office_door_close" ]		= %o_castle_7_5_price_door_close_door;
	level.scr_anim[ "airlock_door" ][ "security_office_drag" ]				= %o_castle_7_5_price_drag_guard_door_open;

	// 		Guard baton
	level.scr_animtree[ "baton" ]										= #animtree;
	level.scr_model[ "baton" ]											= "ctl_baton_wood_animated";
	level.scr_anim[ "baton" ][ "harass_loop" ][0]						= %o_castle_7_1_baton_loop;
	level.scr_anim[ "baton" ][ "harass_drop" ]							= %o_castle_7_1_baton_drop;
	level.scr_anim[ "baton" ][ "harass_drop_idle" ][0]					= %o_castle_7_1_baton_end_idl;

	// Power switch
//	level.scr_animtree[ "power_switch" ]							= #animtree;
////	level.scr_model[ "power_switch" ]								= "ctl_light_switch_panel";
//	level.scr_anim[ "power_switch" ][ "power_switch_off" ]			= %o_castle_7_6_price_lights_off;

	// 		Prison exit	door
	level.scr_anim[ "door" ][ "prison_exit_briefing_open" ]				= %o_castle_8_7_price_door_briefing_door;
	level.scr_anim[ "door" ][ "prison_exit_briefing_open_idle" ][0]		= %o_castle_8_7_price_door_briefing_door_open_idl;
	level.scr_anim[ "door" ][ "prison_exit_briefing_close" ]			= %o_castle_8_7_price_door_briefing_door_close;

	//		Flare
	level.scr_animtree[ "flare" ]									= #animtree;
	level.scr_model[ "flare" ]										= "ctl_emergency_flare_animated";
	level.scr_anim[ "flare" ][ "guard_flare_toss" ]					= %o_castle_8_3_guard_flare;	
	level.scr_anim[ "flare" ][ "guard_flare_toss2" ]				= %o_castle_8_3_guard_flare2;
	level.scr_anim[ "flare" ][ "guard_flare_toss3" ]				= %o_castle_8_3_guard_flare3;
	
	// 		Bridge tarp
	level.scr_animtree[ "bridge_tarp" ]								= #animtree;
	level.scr_anim[ "bridge_tarp" ][ "gone_with_the_wind" ]			= %fxanim_castle_bridge_tarp06_anim;
	
	// 		Fiber Optic cam
	level.scr_animtree[ "camera" ]									= #animtree;
	level.scr_model[ "camera" ]										= "ctl_fiber_optic_cam_animated";
	level.scr_anim[ "camera" ][ "wet_wall_investigate" ]			= %o_castle_10_2_set_det_chord_optic_cam;
	
	// 		Detcord
	level.scr_animtree[ "detcord" ]									= #animtree;
	level.scr_model[ "detcord" ]									= "ctl_detcord_animated";
	level.scr_anim[ "detcord" ][ "wet_wall_place_detcord" ]			= %o_castle_10_2_set_det_chord_det_chord;
	
	//		Wet wall blast
	level.scr_animtree[ "wet_wall" ]								= #animtree;
	level.scr_model[ "wet_wall" ]									= "fxanim_castle_enter_wall_mod";
	level.scr_anim[ "wet_wall" ][ "detonate" ]						= %fxanim_castle_enter_wall_anim;	
	
	// 		Wetwall wooden slat
	level.scr_animtree[ "peep_hole_piece" ]							= #animtree;
	level.scr_model[ "peep_hole_piece" ]							= "ctl_peep_hole_piece";
	level.scr_anim[ "peep_hole_piece" ][ "wall_climb_peek_slip" ]	= %castle_player_wetwall_climb_hole_peek_slip_slatbreak;	
	
	level.scr_animtree[ "peep_hole_fx" ]							= #animtree;
	level.scr_model[ "peep_hole_fx" ]								= "fxanim_castle_peep_hole_boards_mod";
	level.scr_anim[ "peep_hole_fx" ][ "wall_climb_peek_slip" ]		= %fxanim_castle_peep_hole_boards_anim;
		
	//		Kitchen Wall
	level.scr_animtree[ "kitchen_wall" ]							= #animtree;
	level.scr_model[ "kitchen_wall" ]								= "fxanim_castle_kitchen_wall_mod";
	level.scr_anim[ "kitchen_wall" ][ "crash_thru" ]				= %fxanim_castle_kitchen_wall_anim;	

	// 		Hanging meat	
	level.scr_animtree[ "meat" ]									= #animtree;
	level.scr_model[ "meat" ]										= "fxanim_castle_meat_large_mod";
	level.scr_anim[ "meat" ][ "swing" ][0]							= %fxanim_castle_meat_large_anim;	

	// 		Backup Chute
	level.scr_animtree[ "secondary_chute" ]							= #animtree;
	level.scr_model[ "secondary_chute" ]							= "ctl_parachute_handle_backup";
	level.scr_anim[ "secondary_chute" ][ "release" ]				= %castle_player_escape_chuterelease_chutestrap;
	
	// 		Bridge scaffolding large shake
	level.scr_animtree[ "bridge_scaffolding_large" ]				= #animtree;
	level.scr_model[ "bridge_scaffolding_large" ]					= "fxanim_castle_scaff_lrg_x_mod";
	level.scr_anim[ "bridge_scaffolding_large" ][ "shake" ][0]		= %fxanim_castle_scaff_lrg_x_anim;
	
	// 		Bridge scaffolding small shake
	level.scr_animtree[ "bridge_scaffolding_small" ]				= #animtree;
	level.scr_model[ "bridge_scaffolding_small" ]					= "fxanim_castle_scaff_sm_mod";
	level.scr_anim[ "bridge_scaffolding_small" ][ "shake" ][0]		= %fxanim_castle_scaff_sm_anim;
	
	//		C4 Detonator
	//level.scr_animtree[ "c4_detonator" ]							= #animtree;
	//level.scr_model[ "c4_detonator" ]								= "ctl_weapon_c4_detonator_animated";
	//level.scr_anim[ "c4_detonator" ][ "c4_detonate" ]				= %o_castle_14_7_price_detonates_motorpool_detonator;
	
	// Swaying Trees
	level.scr_animtree[ "tree_large" ]							= #animtree;
	level.scr_model[ "tree_large" ]								= "fxanim_castle_tree_large_sway_mod";
	level.scr_anim[ "tree_large" ][ "sway" ][0]				= %fxanim_castle_tree_large_sway_anim;
	level.scr_anim[ "tree_large" ][ "stop" ]				= %fxanim_castle_tree_large_sway_stop_anim;
	
	level.scr_animtree[ "tree_small" ]							= #animtree;
	level.scr_model[ "tree_small" ]								= "fxanim_castle_tree_small_sway_mod";
	level.scr_anim[ "tree_small" ][ "sway" ][0]				= %fxanim_castle_tree_small_sway_anim;
	level.scr_anim[ "tree_small" ][ "stop" ]				= %fxanim_castle_tree_small_sway_stop_anim;
	
	level.scr_animtree[ "power_switch" ] = #animtree;
	level.scr_model[ "power_switch" ] = "ctl_light_switch_panel_arm_animated";
	level.scr_anim[ "power_switch" ][ "power_off" ]				= %o_castle_7_6_price_lights_off;
	

/*	
	// 		Bridge board breaking
	level.scr_animtree[ "bridge_boards" ]							= #animtree;
	level.scr_model[ "bridge_boards" ]								= "fxanim_castle_bridge_boards_mod";
	level.scr_anim[ "bridge_boards" ][ "break" ]					= %fxanim_castle_bridge_boards_anim;
*/
}

fxanims()
{
	wait 1;
	
	/* chains under back-crawl platform */
	a_chains1 = GetEntArray( "fxanim_gp_chain_arch_sm", "targetname" );
	foreach ( m_chain in a_chains1 )
	{
		m_chain.animname = "fxanim";
		m_chain assign_animtree();
		m_chain thread anim_loop_solo( m_chain, "fxanim_gp_chain_arch_sm" );
		wait RandomFloatRange( .1, 1 );
	}
	
	a_chains2 = GetEntArray( "fxanim_gp_chain_short", "targetname" );
	foreach ( m_chain in a_chains2 )
	{
		m_chain.animname = "fxanim";
		m_chain assign_animtree();
		m_chain thread anim_loop_solo( m_chain, "fxanim_gp_chain_short" );
		wait RandomFloatRange( .1, 1 );
	}
	
	// Prison anims, using:
	//	"fxanim_gp_chain_arch_sm_mod"
	//	"fxanim_gp_chain_short_mod"
	//	"fxanim_gp_chain_med_hook_mod"
	//	"fxanim_gp_chain_med_pulley_mod"
	flag_wait( "entered_security_office_cage" );
	
	a_m_fxanims = GetEntArray( "fxanim_prison", "script_noteworthy" );
	foreach ( m_fxanim in a_m_fxanims )
	{
		m_fxanim.animname = "fxanim";
		m_fxanim assign_animtree();
		m_fxanim thread anim_loop_solo( m_fxanim, m_fxanim.targetname, "stop_fxanim" );
		wait RandomFloatRange( .1, 1 );
	}

	a_generators = GetEntArray( "fxanim_castle_generator_mod", "targetname" );
	foreach ( m_generator in a_generators )
	{
		m_generator.animname = "fxanim";
		m_generator UseAnimTree( #animtree );
		m_generator thread anim_loop_solo( m_generator, "fxanim_castle_generator_mod" );
		wait RandomFloatRange( .1, 3 );
	}
}

#using_animtree( "generic_human" );

//
//	All dialog lines for castle
//	This is a temp function until the lines get moved to their appropriate sections with the animations
//---JZ organizing all VO so each scripter can trim out what they need.
//---JZ didn't search scripts, just played through and ordered it how I heard it.
dialog_lines()
{
//**************
//----OLD VO----

			
	//---ESCAPE---
			
//**************
//----END OLD VO----


//**************
//----NEW VO----
	
	//---CURRENTLY UNUSED---
	//Cover our backs!
	level.scr_sound[ "price" ][ "castle_pri_coverourbacks" ] = "castle_pri_coverourbacks";
	//Yuri!  Behind us!!
	level.scr_sound[ "price" ][ "castle_pri_behindus" ] = "castle_pri_behindus";
	
	//---INTRO---
	
	//---RUINS START---
	//Keep up or I leave you behind.
	level.scr_sound[ "price" ][ "castle_pri_keepup" ] = "castle_pri_keepup";
	//Get down.	
	level.scr_sound[ "price" ][ "castle_pri_getdown" ] = "castle_pri_getdown";
	//Get caught in those lights, and we're done before we've started.	
	level.scr_sound[ "price" ][ "castle_pri_beforestarted" ] = "castle_pri_beforestarted";
	//Move.	
	level.scr_sound[ "price" ][ "castle_pri_move3" ] = "castle_pri_move3";
	//Wait...	
	level.scr_sound[ "price" ][ "castle_pri_wait3" ] = "castle_pri_wait3";
	//This way.  Now.	
	level.scr_sound[ "price" ][ "castle_pri_thisway3" ] = "castle_pri_thisway3";
	//You're lagging behind Yuri...	
	level.scr_sound[ "price" ][ "castle_pri_laggingbehind" ] = "castle_pri_laggingbehind";
	//Stop slowing me down.	
	level.scr_sound[ "price" ][ "castle_pri_slowingme" ] = "castle_pri_slowingme";
	//Keep falling behind, and you're on your own.	
	level.scr_sound[ "price" ][ "castle_pri_onyourown" ] = "castle_pri_onyourown";
	//Next time, I let them kill you.	
	level.scr_sound[ "price" ][ "castle_pri_nexttime" ] = "castle_pri_nexttime";
	//No more mistakes.  Let's go.	
	level.scr_sound[ "price" ][ "castle_pri_mistakes" ] = "castle_pri_mistakes";
	
	//---COURTYARD ACTIVITY---
	
	//When we're down there, you move when I move.  Do as I do.  Understand?
	level.scr_sound[ "price" ][ "castle_pri_moveasimove" ] = "castle_pri_moveasimove";
	level.scr_face[ "price" ][ "castle_pri_moveasimove" ]  = %castle_1_12n_price_face;
	//Let's go.	
	level.scr_sound[ "price" ][ "castle_pri_letsgo2" ] = "castle_pri_letsgo2";
	level.scr_face[ "price" ][ "castle_pri_letsgo2" ]  = %castle_1_13n_price_face;
	
	//---BROKE STEALTH / SLOPPY KILLS---
	//We've been spotted! Open Fire!
	level.scr_sound[ "price" ][ "castle_pri_spotted" ] = "castle_pri_beenspotted";
	//They're on to us!  Light 'em up!
	level.scr_sound[ "price" ][ "castle_pri_lightemup" ] = "castle_pri_lightemup";
	//We're compromised!  Take 'em down!
	level.scr_sound[ "price" ][ "castle_pri_compromised" ] = "castle_pri_compromised";
	//Do that again and I'll take care of you myself.
	level.scr_sound[ "price" ][ "castle_pri_dothatagain" ] = "castle_pri_dothatagain";
	//Pitiful.
	level.scr_sound[ "price" ][ "castle_pri_pitiful" ] = "castle_pri_pitiful";
	//You'll have to do better than that...
	level.scr_sound[ "price" ][ "castle_pri_dobetter" ] = "castle_pri_dobetter";

	
	//---COURTYARD STEALTH---
	//Hold...
	level.scr_sound[ "price" ][ "castle_pri_hold2" ] = "castle_pri_hold2";
	//Only shoot at what you can kill.	
	level.scr_sound[ "price" ][ "castle_pri_whatyoukill" ] = "castle_pri_whatyoukill";
	//Go
	level.scr_sound[ "price" ][ "castle_pri_go2" ] = "castle_pri_go";
	//Under the trucks.	
	level.scr_sound[ "price" ][ "castle_pri_undertrucks2" ] = "castle_pri_undertrucks2";
	//Get under the trucks.	
	level.scr_sound[ "price" ][ "castle_pri_getunder" ] = "castle_pri_getunder";
	//I don't have time for this, Yuri.  Get over here.	
	level.scr_sound[ "price" ][ "castle_pri_donthavetime" ] = "castle_pri_donthavetime";
	//C'mon.	
	level.scr_sound[ "price" ][ "castle_pri_cmon" ] = "castle_pri_cmon";
	//Wait
	level.scr_sound[ "price" ][ "castle_pri_wait" ] = "castle_pri_wait4";
	//We'll plant C4 to cover our escape.
	level.scr_sound[ "price" ][ "castle_pri_plantc4" ] = "castle_pri_plantc4cover";
	//We'll burn this place down if we have to.	
	level.scr_sound[ "price" ][ "castle_pri_burnthisplace" ] = "castle_pri_burnthisplace";
	
	//---SPOTLIGHT KILL---
	//Take him out - but don't get caught in that spotlight.
	level.scr_sound[ "price" ][ "castle_pri_takehimout" ] = "castle_pri_takehimout";
	level.scr_face [ "price" ][ "castle_pri_takehimout" ] = %castle_2_7n_price_face;
	//Use your knife.  Hurry.	
	level.scr_sound[ "price" ][ "castle_pri_useknife2" ] = "castle_pri_useknife2";
	//Lost your edge?  Let me show you how it's done.	
	level.scr_sound[ "price" ][ "castle_pri_lostyouredge" ] = "castle_pri_lostyouredge";
	
	//---SPOTLIGHT RUN---
	//Wait for it...
	level.scr_sound[ "price" ][ "castle_pri_waitforit" ] = "castle_pri_waitforit";
	level.scr_face [ "price" ][ "castle_pri_waitforit" ] = %castle_2_10n_price_face;
	//Now!	
	level.scr_sound[ "price" ][ "castle_pri_now2" ] = "castle_pri_now2";
	//You have to move when I move.  Don't screw this up.	
	level.scr_sound[ "price" ][ "castle_pri_screwthisup2" ] = "castle_pri_screwthisup2";
	
	//---PLATFORM CRAWL---	
	//Over here.
 	level.scr_sound[ "price" ][ "castle_pri_overhere" ] = "castle_pri_overhere";
		
	//---WAIT FOR FLASHLIGHT UNDER PLATFORM---
	//Stop...don't move.
	level.scr_sound[ "price" ][ "castle_pri_stopdontmove" ] = "castle_pri_stopdontmove";
	//Alright...c'mon.
	level.scr_sound[ "price" ][ "castle_pri_weregood2" ] = "castle_pri_alrightcmon";
	
	//---PLANT C4 UNDER PLATFORM---
	//Plant C4 on the platform.
	level.scr_sound[ "price" ][ "castle_pri_c4platform" ] = "castle_pri_c4platform";
	//Plant the C4, Yuri.
	level.scr_sound[ "price" ][ "castle_pri_plantthec4" ] = "castle_pri_plantthec4";
	//Are you daft?  Follow directions.	
	level.scr_sound[ "price" ][ "castle_pri_daft" ] = "castle_pri_daft";
	//Nevermind.  I'll handle it.
	level.scr_sound[ "price" ][ "castle_pri_nevermind2" ] = "castle_pri_nevermind2";
		
	//---WAIT FOR SMOKING GUY UNDER PLATFORM---
	//Easy...	
	level.scr_sound[ "price" ][ "castle_pri_easy" ] = "castle_pri_easy";
	//Clear.  Go.	
	level.scr_sound[ "price" ][ "castle_pri_cleargo" ] = "castle_pri_cleargo";
	//We're good.  Keep moving.	
	level.scr_sound[ "price" ][ "castle_pri_weregood3" ] = "castle_pri_weregood3";
	level.scr_face [ "price" ][ "castle_pri_weregood3" ] = %castle_3_11r_price_face;
	
	//---SECURITY OFFICE---
	//There's the security office.
	level.scr_sound[ "price" ][ "castle_pri_securityoffice2" ] = "castle_pri_securityoffice2";
		
	//---BEFORE KNOCKING---
	//I'll handle this
	level.scr_sound[ "price" ][ "castle_pri_illhandle" ] = "castle_pri_illhandle";
	//---AFTER EVERYONE IS DEAD IN OFFICE
	//Clear.
	level.scr_sound[ "price" ][ "castle_pri_clear" ] = "castle_pri_clear";
	//They've got cameras outside the command center.  Both sides - here, and here.	
	level.scr_sound[ "price" ][ "castle_pri_camerasout" ] = "castle_pri_camerasout";
	level.scr_face[ "price" ][ "castle_pri_camerasout" ]  = %ch_castle_7_5_price_drag_guard_face_camerasout;
	//We'll just have to knock on the door.	
	level.scr_sound[ "price" ][ "castle_pri_knock" ] = "castle_pri_knock";
	level.scr_face[ "price" ][ "castle_pri_knock" ]  = %ch_castle_7_5_price_drag_guard_face_knockdoor;
	//Cheers.	
	level.scr_sound[ "price" ][ "castle_pri_cheers" ] = "castle_pri_cheers";
	level.scr_face[ "price" ][ "castle_pri_cheers" ]  = %ch_castle_7_5_price_drag_guard_face_cheers;
	
	//---PRISON BATTLE START---
	//Quiet...
	level.scr_sound[ "price" ][ "castle_pri_quiet" ] = "castle_pri_quiet";
	//Night-vision on.	
	level.scr_sound[ "price" ][ "castle_pri_nightvisionon" ] = "castle_pri_nightvisionon";
	//I'll take care of the lights.
	level.scr_sound[ "price" ][ "castle_pri_takecare" ] = "castle_pri_takecare";
	//Ready?	
	level.scr_sound[ "price" ][ "castle_pri_ready" ] = "castle_pri_ready";
	//Weapons free!	
	level.scr_sound[ "price" ][ "castle_pri_weaponsfree" ] = "castle_pri_weaponsfree";
	//Sweep through this area fast.	
	level.scr_sound[ "price" ][ "castle_pri_sweepthrough" ] = "castle_pri_sweepthrough";
	//They won't know how few we are in the dark.	
	level.scr_sound[ "price" ][ "castle_pri_howfew" ] = "castle_pri_howfew";
	
	//---PRISON BATTLE FLARE ROOM---
	//They're using flares!
	level.scr_sound[ "price" ][ "castle_pri_usingflares" ] = "castle_pri_usingflares";
	//Take your night-vision off.  We'll do this the old way.	
	level.scr_sound[ "price" ][ "castle_pri_oldway" ] = "castle_pri_oldway";
	//They're bringing in reinforcements!	
	level.scr_sound[ "price" ][ "castle_pri_reinforcements2" ] = "castle_pri_reinforcements2";
	//You're on point.  Go.	
	level.scr_sound[ "price" ][ "castle_pri_onpoint" ] = "castle_pri_onpoint";
	//This is when you start moving, Yuri.	
	level.scr_sound[ "price" ][ "castle_pri_startmoving" ] = "castle_pri_startmoving";
	//Get out of here.  GO!	
	level.scr_sound[ "price" ][ "castle_pri_getoutofhere2" ] = "castle_pri_getoutofhere2";
	//He wouldn't have made it anyway
	level.scr_sound[ "price" ][ "castle_pri_nevermind" ] = "castle_pri_nevermind";
	//We have about ten minutes until they find their dead.	
	level.scr_sound[ "price" ][ "castle_pri_tenminutes" ] = "castle_pri_tenminutes";
	level.scr_face[ "price" ][ "castle_pri_tenminutes" ]  = %castle_6_5_price_face;
	//Try not to fall behind, eh?	
	level.scr_sound[ "price" ][ "castle_pri_fallbehind" ] = "castle_pri_fallbehind";
	
	//---BRIDGE CROSSING---
	//This bridge is the only way in or out of the base.
	level.scr_sound[ "price" ][ "castle_pri_thisbridge2" ] = "castle_pri_thisbridge2";
	//Plant some more C4 on the column.	
	level.scr_sound[ "price" ][ "castle_pri_c4oncolumn" ] = "castle_pri_c4oncolumn";
	//Plant the damn C4, Yuri.  Hurry.	
	level.scr_sound[ "price" ][ "castle_pri_plantc4hurry" ] = "castle_pri_plantc4hurry";
	//You're good for nothing.  I'll plant the damn thing myself.
	level.scr_sound[ "price" ][ "castle_pri_goodfornothing" ] = "castle_pri_goodfornothing";
	//This whole thing looks like it's about to collapse...
	level.scr_sound[ "price" ][ "castle_pri_abouttocollapse" ] = "castle_pri_abouttocollapse";
	//...so take it slow.
	level.scr_sound[ "price" ][ "castle_pri_sotakeitslow" ] = "castle_pri_sotakeitslow";
	//A little too slow, Yuri.
	level.scr_sound[ "price" ][ "castle_pri_alittletooslow" ] = "castle_pri_alittletooslow";
	
	
	//---DESTROY WET WALL---
	//Hold on...
	level.scr_sound[ "price" ][ "castle_pri_holdon" ] = "castle_pri_holdon";
	//Change of plan.	
	level.scr_sound[ "price" ][ "castle_pri_changeofplan" ] = "castle_pri_changeofplan";
	//The control centre is just above us.	
	level.scr_sound[ "price" ][ "castle_pri_justaboveus" ] = "castle_pri_justaboveus";
	//Looks like we won't have to shoot our way in.	
	level.scr_sound[ "price" ][ "castle_pri_shootourway" ] = "castle_pri_shootourway";
	//The thunder will hide the sound of the blast.  Wait for my signal.	
	level.scr_sound[ "price" ][ "castle_pri_waitformysignal2" ] = "castle_pri_waitformysignal2";
	//Now.	
	level.scr_sound[ "price" ][ "castle_pri_now3" ] = "castle_pri_now3";
	//Are you dim?  You're going to get us killed.	
	level.scr_sound[ "price" ][ "castle_pri_areyoudim" ] = "castle_pri_areyoudim";
	//Your timing is piss poor.
	level.scr_sound[ "price" ][ "castle_pri_pisspoor" ] = "castle_pri_pisspoor";
	//---NAGS FOR DESTROYING THE WET WALL---
	//Go.
	level.scr_sound[ "price" ][ "castle_pri_go3" ] = "castle_pri_go3";
	//Blow it.
	level.scr_sound[ "price" ][ "castle_pri_blowit" ] = "castle_pri_blowit";
	//Do it.
	level.scr_sound[ "price" ][ "castle_pri_doit2" ] = "castle_pri_doit2";
	//Damn it, Yuri. Pay attention.
	level.scr_sound[ "price" ][ "castle_pri_payattention" ] = "castle_pri_pisspoor";
	//Focus Yuri
	level.scr_sound[ "price" ][ "castle_pri_focusyuri" ] = "castle_pri_focusyuri";
	
	//---INTO WET WALL---
	//We can climb up here.  C'mon.	
	level.scr_sound[ "price" ][ "castle_pri_climbuphere" ] = "castle_pri_climbuphere";
	
	//---WATCHING INTERROGATION---
	//For the last... time...
	level.scr_sound[ "president" ][ "castle_prs_forthelast" ] = "castle_prs_forthelast";
	//I...will not bow... to the demands... of terrorist thugs...	
	level.scr_sound[ "president" ][ "castle_prs_notbow" ] = "castle_prs_notbow";
	//I will die before I surrender the nuclear launch codes...	
	level.scr_sound[ "president" ][ "castle_prs_iwilldie" ] = "castle_prs_iwilldie";
	//Makarov.	
	level.scr_sound[ "price" ][ "castle_pri_makarov" ] = "castle_pri_makarov";
	level.scr_face [ "price" ][ "castle_pri_makarov" ] = %castle_wetwall_price_facial_8_4;
	//I see...	
	level.scr_sound[ "makarov" ][ "castle_mkv_isee" ] = "castle_mkv_isee";
	//This is what we are dealing with, brothers....  	
	level.scr_sound[ "makarov" ][ "castle_mkv_thisiswhat" ] = "castle_mkv_thisiswhat";
	//...A stubborn old man, hopelessly out of step with the changing world.	
	level.scr_sound[ "makarov" ][ "castle_mkv_oldman" ] = "castle_mkv_oldman";
	//You too, will change.	
	level.scr_sound[ "makarov" ][ "castle_mkv_youtoo" ] = "castle_mkv_youtoo";
	//Sir, still no response from the security room.
	level.scr_sound[ "tv_room_guy3" ][ "castle_ru1_noresponse" ] = "castle_ru1_noresponse";
	//Get down there.  Find out what's going on.	
	level.scr_sound[ "alexi" ][ "castle_alx_checkwith" ] = "castle_alx_checkwith";
	//Alexi - Has your Intel been confirmed?	
	level.scr_sound[ "makarov" ][ "castle_mkv_confirmed" ] = "castle_mkv_confirmed";
	//Yes, sir... Our men are already on the way to Berlin.	
	level.scr_sound[ "alexi" ][ "castle_alx_yessir" ] = "castle_alx_yessir";
	//Are you listening?	
	level.scr_sound[ "makarov" ][ "castle_mkv_listening" ] = "castle_mkv_listening";
	//The daughter is there.  We will have her in a matter of hours.	
	level.scr_sound[ "alexi" ][ "castle_alx_thedaughter" ] = "castle_alx_thedaughter";
	level.scr_face [ "alexi" ][ "castle_alx_thedaughter" ] = %ch_castle_10_6_peep_show_alexei_hours_face;
	//Keep me updated.	
	level.scr_sound[ "makarov" ][ "castle_mkv_updated" ] = "castle_mkv_updated";
	
	//---ALARM GOES OFF---
	//What the hell is going on?!  Did we get an answer from the security team or not?!  Get some men to start searching the grounds!
	level.scr_sound[ "alexi" ][ "castle_alx_whatgoingon" ] = "castle_alx_whatgoingon";
	//Something's wrong...	
	level.scr_sound[ "price" ][ "castle_pri_wrong" ] = "castle_pri_wrong";
	//Time to go.
	level.scr_sound[ "price" ][ "castle_pri_timetogo" ] = "castle_pri_timetogo";
	level.scr_face [ "price" ][ "castle_pri_timetogo" ] = %castle_wetwall_price_facial_4_35;
	//This should buy us some time.
	level.scr_sound[ "price" ][ "castle_pri_withthis" ] = "castle_pri_withthis";
	level.scr_face [ "price" ][ "castle_pri_withthis" ] = %castle_wetwall_price_facial_8_15_4;
	//They must have found the bodies.
	level.scr_sound[ "price" ][ "castle_pri_thebodies" ] = "castle_pri_thebodies";
	level.scr_face [ "price" ][ "castle_pri_thebodies" ] = %castle_wetwall_price_facial_8_15_3;
	//GRENADE!!!
	level.scr_sound[ "tv_room_guy1" ][ "castle_ru1_grenade" ] = "castle_ru1_grenade";
	//Down!  Now!	
	level.scr_sound[ "price" ][ "castle_pri_downnow" ] = "castle_pri_downnow";
	
	//---KITCHEN BATTLE---
	//On your feet!  We're leaving!
	level.scr_sound[ "price" ][ "castle_pri_onyourfeet" ] = "castle_pri_onyourfeet";
	//Nikolai, the daughter is in Berlin!  Makarov has men on their way!	
	level.scr_sound[ "price" ][ "castle_pri_inberlin" ] = "castle_pri_inberlin";
	//I'll contact the American.	
	level.scr_radio[ "castle_nik_contact" ] = "castle_nik_contact";
	//Nikolai - Vorshevsky WILL break if they threaten the girl!	
	level.scr_sound[ "price" ][ "castle_pri_willbreak" ] = "castle_pri_willbreak";
	//Da, Captain Price.  I won't let you down.	
	level.scr_radio[ "castle_nik_letyoudown" ] = "castle_nik_letyoudown";
	
	//---INTERIOR---
	//Left side!
	level.scr_sound[ "price" ][ "castle_pri_leftside2" ] = "castle_pri_leftside2";
	//Keep moving!	
	level.scr_sound[ "price" ][ "castle_pri_keepmoving2" ] = "castle_pri_keepmoving2";
	//Don't slow down now, Yuri!	
	level.scr_sound[ "price" ][ "castle_pri_dontslowdown" ] = "castle_pri_dontslowdown";
	//Sort em out!	
	level.scr_sound[ "price" ][ "castle_pri_sortemout" ] = "castle_pri_sortemout";
	//Through here!  Move!	
	level.scr_sound[ "price" ][ "castle_pri_throughhere" ] = "castle_pri_throughhere";
	//	FLASHBANG!	
	level.scr_sound[ "price" ][ "castle_pri_flashbang" ] = "castle_pri_flashbang";
	
	//---INNER COURTYARD---
	//RPGs!
	level.scr_sound[ "price" ][ "castle_pri_rpgs" ] = "castle_pri_rpgs";
	//Get through here fast!	
	level.scr_sound[ "price" ][ "castle_pri_throughere" ] = "castle_pri_throughere";
	//On me.	
	level.scr_sound[ "price" ][ "castle_pri_onme2" ] = "castle_pri_onme2";
	//Get over here!	
	level.scr_sound[ "price" ][ "castle_pri_overehere" ] = "castle_pri_overehere";
	//	Stay with me, Yuri.	
	level.scr_sound[ "price" ][ "castle_pri_staywithmeyuri" ] = "castle_pri_staywithmeyuri";
	
	//---BRIDGE EXPLODE---
	//They're just in time.
	level.scr_sound[ "price" ][ "castle_pri_justintime" ] = "castle_pri_justintime";
	//Do it.	
	level.scr_sound[ "price" ][ "castle_pri_doit" ] = "castle_pri_doit";
	//Detonate the charges!	
	level.scr_sound[ "price" ][ "castle_pri_detonate" ] = "castle_pri_detonate";
	//Move!	
	level.scr_sound[ "price" ][ "castle_pri_move4" ] = "castle_pri_move4";
	//Fine. I'll do it	
	level.scr_sound[ "price" ][ "castle_pri_illdoit" ] = "castle_pri_illdoit";
	//You're a sloppy bastard, y'know that?
	level.scr_sound[ "price" ][ "castle_pri_sloppybastard" ] = "castle_pri_sloppybastard";
	
	//---JUMP OUT WINDOW---
	//Jump - GO!	
	level.scr_sound[ "price" ][ "castle_pri_jumpgo" ] = "castle_pri_jumpgo2";
	
	//---COURTYARD BATTLE---
	//The whole damn base is gonna come down on us!  We need to move!
	level.scr_sound[ "price" ][ "castle_pri_wholebase" ] = "castle_pri_wholebase";
	//That BTR's blocking our way out!!!	
	level.scr_sound[ "price" ][ "castle_pri_btrblocking" ] = "castle_pri_btrblocking";	
	//Yuri, get in!!
	level.scr_sound[ "price" ][ "castle_pri_getin" ] = "castle_pri_getin";
	//	Detonating C4... NOW!	
	level.scr_sound[ "price" ][ "castle_pri_detonating" ] = "castle_pri_detonating";
	

	//---ESCAPE---
	//Hold on!!!	
	level.scr_sound[ "price" ][ "castle_pri_holdon2" ] = "castle_pri_holdon2";
	//Hope you're still carrying your reserve, Yuri!
	level.scr_sound[ "price" ][ "castle_pri_reserve" ] = "castle_pri_reserve";
	//BTRs!!!
	level.scr_sound[ "price" ][ "castle_pri_BTRs" ] = "castle_pri_BTRs";
	//Get your chute ready!	
	level.scr_sound[ "price" ][ "castle_pri_chuteready" ] = "castle_pri_chuteready";
	//JUMP!	
	level.scr_sound[ "price" ][ "castle_pri_jump" ] = "castle_pri_jump";
	//Nikolai, get us out of here.	
	level.scr_sound[ "price" ][ "castle_pri_getusout" ] = "castle_pri_getusout";
	//Roger.  I'm on my way.	
	level.scr_radio[ "castle_nik_onmyway" ] = "castle_nik_onmyway";
	
	
	//---ALERTED CONVERSATION---	
	// Sir, still no response from the security room.
	level.scr_sound[ "guard1" ][ "castle_ru1_noresponse" ] ="castle_ru1_noresponse";
	//Everyone off! Set up a defensive positions.
	level.scr_sound[ "guard1" ][ "castle_ru1_everyoneoff" ] ="castle_ru1_everyoneoff";
	//No one goes in or out, understood?	
	level.scr_sound[ "guard1" ][ "castle_ru1_inorout" ] ="castle_ru1_inorout";
	//Kill intruders on sight!	
	level.scr_sound[ "guard1" ][ "castle_ru1_killintruders" ] ="castle_ru1_killintruders";
	
		
	//---RANDOM CONVERSATION 2---	 guys below the overlook - castle_courtyard_stealth script noteworthy: overlook_intro_guard
	
	//Security team four - Northern perimeter sweep complete. (beat) All clear.
	// NO ALIAS WAS GIVEN FOR THIS LINE YET
	//level.scr_sound[ "guy1" ][ "" ] ="";
	//Hey Vadim! What did you screw up to get put on security detail?
	level.scr_sound[ "guard2" ][ "castle_ru2_securitydetail" ] ="castle_ru2_securitydetail";
	//Don't ask me.  I just do what I'm told...	
	level.scr_sound[ "guard3" ][ "castle_ru3_dontaskme" ] ="castle_ru3_dontaskme";
	//If you did what you were told you wouldn't be out here getting soaked...	
	level.scr_sound[ "guard2" ][ "castle_ru2_gettingsoaked" ] ="castle_ru2_gettingsoaked";
	//Enough bullshit.  Continue your patrol.	
	level.scr_sound[ "guard1" ][ "castle_ru1_enough" ] ="castle_ru1_enough";
	//I'm watching you, Vadim.
	level.scr_sound[ "guard1" ][ "castle_ru1_watchingyou" ] ="castle_ru1_watchingyou";
		
	//HOOKED UP	
	//---RANDOM CONVERSATION 3---	1st ruins patrol  - castle_ruins: script_noteworthy: ruins_patroller4 and ruins_patroller3
	// put in castle_ruins::first_patrol()
	
	//Hey, Alexi.  How's life?
	level.scr_sound[ "ruins_patroller4" ][ "castle_ru1_howslife" ] ="castle_ru1_howslife";
	//Cold, dark and wet.	
	level.scr_sound[ "ruins_patroller3" ][ "castle_ru2_colddark" ] ="castle_ru2_colddark";
	//I wasn't talking about your love life...
	level.scr_sound[ "ruins_patroller4" ][ "castle_ru1_lovelife" ] ="castle_ru1_lovelife";
	//Ha Ha.  Very funny.
	level.scr_sound[ "ruins_patroller3" ][ "castle_ru2_veryfunny" ] ="castle_ru2_veryfunny";
	
	//HOOKED UP	
	//---RANDOM CONVERSATION 4---	 platform guys - any 2 guys in castle_courtyard_stealth::platform_guards_animate()
	//Trying to look busy, Mikhail?
	level.scr_sound[ "platformguard1" ][ "castle_ru3_lookbusy" ] ="castle_ru3_lookbusy";
	//What do you mean?... There's nothing to do.
	level.scr_sound[ "platformguard2" ][ "castle_ru4_nothingtodo" ] ="castle_ru4_nothingtodo";
	//At least the others are seeing some action.
	level.scr_sound[ "platformguard1" ][ "castle_ru3_someaction" ] ="castle_ru3_someaction";
	//I think I'm more likely to die of boredom.
	level.scr_sound[ "platformguard2" ][ "castle_ru4_dieofboredom" ] ="castle_ru4_dieofboredom";
	
	//HOOKED UP
	//---RANDOM CONVERSATION 5---	spotlight guys - castle_courtyard_stealth: script_noteworthy: road_patrollers
	//You're crazy... I don't get why you don't just go to the Medical Officer...
	level.scr_sound[ "road_patroller_1" ][ "castle_ru3_crazy" ] ="castle_ru3_crazy";
	//And tell him what?
	level.scr_sound[ "road_patroller_2" ][ "castle_ru4_andtellhimwhat" ] ="castle_ru4_andtellhimwhat";
	//The truth!... Or - something close to the truth.
	level.scr_sound[ "road_patroller_1" ][ "castle_ru3_thetruth" ] = "castle_ru3_thetruth";
	//What if he submits a report?... I'll be up on charges!
	level.scr_sound[ "road_patroller_2" ][ "castle_ru4_submitsreport" ] ="castle_ru4_submitsreport";
	//Better that, than what you're going through now. (beat) Is it stills changing color?
	level.scr_sound[ "road_patroller_1" ][ "castle_ru3_betterthat" ] ="castle_ru3_betterthat";
	//Not any more... It's been blue since Tuesday.
	level.scr_sound[ "road_patroller_2" ][ "castle_ru4_notanymore" ] ="castle_ru4_notanymore";
	//Maybe it's getting better...
	level.scr_sound[ "road_patroller_1" ][ "castle_ru3_gettingbetter" ] ="castle_ru3_gettingbetter";
	//Thanks.
	level.scr_sound[ "road_patroller_2" ][ "castle_ru4_thanks" ] ="castle_ru4_thanks";
	//Or maybe it'll just fall off...
	level.scr_sound[ "road_patroller_1" ][ "castle_ru3_justfalloff" ] ="castle_ru3_justfalloff";
								

		
	//---RANDOM PRISON GUARD VO---	
	//Intruders!!!
	level.scr_sound[ "generic" ][ "castle_ru1_intruders" ] = "castle_ru1_intruders";	
	//Sound the alarm!!!
	level.scr_sound[ "generic" ][ "castle_ru1_soundalarm" ] = "castle_ru1_soundalarm";	
	//Settle down, you good for nothing mongrels!
	level.scr_sound[ "generic" ][ "castle_ru2_goodfornothing" ] = "castle_ru2_goodfornothing";	
	//You're here till WE say otherwise!
	level.scr_sound[ "generic" ][ "castle_ru2_tillwesay" ] = "castle_ru2_tillwesay";	
	//Now sit down and SHUT UP!!!
	level.scr_sound[ "generic" ][ "castle_ru2_sitdown" ] = "castle_ru2_sitdown";	
	//What the Hell?!!!
	level.scr_sound[ "guard3" ][ "castle_ru2_whatthehell" ] = "castle_ru2_whatthehell";	
	//On the stairs!!!
	level.scr_sound[ "generic" ][ "castle_ru2_onthestairs" ] = "castle_ru2_onthestairs";	
	
	//---RANDOM PRISONER CROWD VO---
	//What's happening?
	level.scr_sound[ "generic" ][ "castle_cop1_whatshappening" ] = "castle_cop1_whatshappening";
	//Who are those guys?
	level.scr_sound[ "generic" ][ "castle_cop1_whoarethose" ] = "castle_cop1_whoarethose";		
	//They're here to set us free!	
	level.scr_sound[ "generic" ][ "castle_cop1_setusfree" ] = "castle_cop1_setusfree";		
	//Get us out of here!
	level.scr_sound[ "generic" ][ "castle_cop1_getusout" ] = "castle_cop1_getusout";	
	//It's about time!
	level.scr_sound[ "generic" ][ "castle_cop1_abouttime" ] = "castle_cop1_abouttime";	
	//Hurray! /(various cheers)
	level.scr_sound[ "generic" ][ "castle_cop1_hurray" ] = "castle_cop1_hurray";	
	//What's happening?	
	//Who are those guys?	
	//They're here to set us free!	
	//Get us out of here!	
	//It's about time!	
	//Hurray! /(various cheers)	
	//What's happening?	
	//Who are those guys?	
	//They're here to set us free!	
	//Get us out of here!	
	//It's about time!	
	//Hurray! /(various cheers)	
	//Yeah!/(various cheers)
	level.scr_sound[ "generic" ][ "castle_cop1_yeah" ] = "castle_cop1_yeah";	
	//Hurray! /(various cheers)	
	//Yeah!/(various cheers)	
	//Shoot the bastards!	
	level.scr_sound[ "generic" ][ "castle_cop1_shootthe" ] = "castle_cop1_shootthe";	
	//Yeah!/(various cheers)	
	//Shoot the bastards!	
	//Yeah!/(various cheers)	
	//Shoot the bastards!	
	//Help!!!
	level.scr_sound[ "generic" ][ "castle_rup1_help" ] = "castle_rup1_help";	
	//Please - Let us out!	
	level.scr_sound[ "generic" ][ "castle_rup2_letusout" ] = "castle_rup2_letusout";	
	//We are innocents!!!
	level.scr_sound[ "generic" ][ "castle_rup3_innocents" ] = "castle_rup3_innocents";	
	//Are you here for us?
	level.scr_sound[ "generic" ][ "castle_rup1_hereforus" ] = "castle_rup1_hereforus";	
	//We can help you!
	level.scr_sound[ "generic" ][ "castle_rup2_wecanhelp" ] = "castle_rup2_wecanhelp";	
	//Death to Makarov!
	level.scr_sound[ "generic" ][ "castle_rup3_deathtomakarov" ] = "castle_rup3_deathtomakarov";	
	//Over here!
	level.scr_sound[ "generic" ][ "castle_rup1_overhere" ] = "castle_rup1_overhere";	
	//We need a doctor!
	level.scr_sound[ "generic" ][ "castle_rup2_doctor" ] = "castle_rup2_doctor";	
	//Help us, please!!!
	level.scr_sound[ "generic" ][ "castle_rup3_helpusplease" ] = "castle_rup3_helpusplease";	
	//What the hell is going on?!!
	level.scr_sound[ "generic" ][ "castle_rup1_whatsgoingon" ] = "castle_rup1_whatsgoingon";	
	//Who is out there?!!
	level.scr_sound[ "generic" ][ "castle_rup2_outthere" ] = "castle_rup2_outthere";	
	//Open the doors!
	level.scr_sound[ "generic" ][ "castle_rup3_openthedoors" ] = "castle_rup3_openthedoors";	
	//Yes!!!!
	level.scr_sound[ "generic" ][ "castle_rup1_yes" ] = "castle_rup1_yes";	
	//Kill them!  Kill them all!!
	level.scr_sound[ "generic" ][ "castle_rup2_killthem" ] = "castle_rup2_killthem";		
	
	//---RANDOM GUARD VO---
	//We have gunfire!!!
	level.scr_sound[ "generic" ][ "castle_ru1_gunfire" ] = "castle_ru1_gunfire";	
	//Spread out! Find them!!
	level.scr_sound[ "generic" ][ "castle_ru2_spreadout" ] = "castle_ru2_spreadout";	
	//Alert the commander!
	level.scr_sound[ "generic" ][ "castle_ru3_alertcommander" ] = "castle_ru3_alertcommander";	
	//Lock down the facility!!!
	level.scr_sound[ "generic" ][ "castle_ru1_lockdown" ] = "castle_ru1_lockdown";	
	//Get the power back on!
	level.scr_sound[ "generic" ][ "castle_ru2_powerback" ] = "castle_ru2_powerback";		
	//Where are they?
	level.scr_sound[ "generic" ][ "castle_ru3_wherearethey" ] = "castle_ru3_wherearethey";	
	//Move!  Find them!!!
	level.scr_sound[ "generic" ][ "castle_ru1_findthem" ] = "castle_ru1_findthem";	
	//Unidentified personnel have breached the facility!
	level.scr_sound[ "generic" ][ "castle_ru2_unidentified" ] = "castle_ru2_unidentified";	
}


#using_animtree( "generic_human" );
spawn_fake_security_office_dead_model()
{	
	level.fake_security_character = spawn("script_model", (0, 0, 0));
	level.fake_security_character hide();
	level.fake_security_character setmodel(self.model);
	level.fake_security_character attach(self.headmodel, "", true);
	level.fake_security_character.animname = "security_guard_chair";
	level.fake_security_character SetAnimTree();
	
}

price_shoot_guard_animation( price )
{
	price notify( "start_melee_guard_anim" );
	
}

price_disable_ragdoll(guy)
{
	guy.noragdoll = true;
	guy allowedStances("prone");
}

price_enable_ragdoll(guy)
{
		guy.noragdoll = false;
		guy allowedStances("stand", "crouch", "prone");
}

overlook_vo_1(price)
{
	price dialogue_queue("castle_pri_moveasimove");
}

overlook_vo_2(price)
{
	price dialogue_queue("castle_pri_letsgo2");
}


// vehicle anim overrides
/*setanims_bm21_castle( positions )
{
	positions = vehicle_scripts\_bm21_troops::setanims();
	positions[ 0 ].getin = %castle_truck_escape_mount_price;
	positions[ 0 ].idle = %castle_truck_escape_idle_price;
	return positions;
}


#using_animtree( "vehicles" );
setvehicleanims_bm21_castle(positions)
{
	positions = vehicle_scripts\_bm21_troops::set_vehicle_anims(positions);
	positions[ 0 ].vehicle_getinanim = %castle_truck_escape_mount_truck;		
	return positions;	
}
*/
