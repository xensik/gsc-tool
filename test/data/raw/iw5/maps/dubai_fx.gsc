#include common_scripts\utility;
#include maps\_utility;
#include maps\_audio;
#include maps\_weather;
#include maps\_shg_fx;
#include maps\_vehicle;

main()
{
	if ( !getdvarint( "r_reflectionProbeGenerate" ) )
	
	if(!isdefined(level.createFXent))
		level.createFXent = [];
	
	//Global threads
	maps\createfx\dubai_fx::main();
	setup_shg_fx();
	

	flag_init( "restaurant_drop_section_falling" );
	flag_init( "restaurant_tilt" );
	flag_init( "restaurant_destruction_floor_done" );
	flag_init( "finale_player_jump_start" );
	flag_init( "off_flag");
	flag_init( "stop_makarov_blobshadow");
	
	/*--------------------------------------------------------
	
	START FX LOGIC THREADS HERE
	
	--------------------------------------------------------*/
	
	//thread playerWeather();	// make the actual rain effect generate around the player
	thread precacheFX();		
	thread rainInit( "hard" );// "none" "light" or "hard"	
	thread setup_street_lights();
	thread init_smVals();
	thread restaurant_collapse_se_vfx();
	thread setup_elevator_lights();
	thread treadfx_override();
	thread topfloor_init_dmg_hall1();
	thread topfloor_init_dmg_hall2();
	thread topfloor_init_dmg_hall3();
	
	thread geo_fog_fx();	
	
		
	/*--------------------------------------------------------
	
	ZONE WATCHER
	
	--------------------------------------------------------*/
	thread fx_zone_watcher(1000,"msg_fx_zone1000");//intro exterior
	thread fx_zone_watcher(1500,"msg_fx_zone1000","msg_fx_zone1500");//exterior things that can be seen from lobby (water fountain)
	thread fx_zone_watcher(2000,"msg_fx_zone2000");//lobby 1st floor
	thread fx_zone_watcher(3000,"msg_fx_zone3000");//lobby second floor
	thread fx_zone_watcher(4000,"msg_fx_zone4000");//elevator
//	if(!flag_exist("fx_zone_5000_active")) flag_init("fx_zone_5000_active");
//	if(!flag_exist("fx_zone_5000_inactive")) flag_init("fx_zone_5000_inactive");

//	thread fx_zone_watcher_either_off_killthread(5000,"off_flag","msg_fx_zone5000","msg_fx_zone5000");//restaurant
	thread fx_zone_watcher(5000,"msg_fx_zone5000","msg_fx_zone5000","off_flag");//elevator
	thread fx_zone_watcher(15050,"msg_fx_zone15050");//stairs before rooftop
	thread fx_zone_watcher(6000,"msg_fx_zone6000");//rooftops
	
	//exploder 10000 series is for restaurant destruction SE
	//exploder 15000 series is for post restaurant destructio SE ambient vfx
	
	
}

/*-----------------------------------------------------------

Additional Exploder Index

1100's = intro fx
100		= elevator
101-112	elevator shaft destruction
150-153	restaurant tables
190-191	restaurant columns
200's = fake suburban destruction fx
250		= restaurant back section
300		= restaurant beams
500		= restaurant floor and walls
600		= restaurant column
700		= restaurant debris

5001 = top floor fires (so that can be turned off for finale)
5002 = top floor FINALE ambient fx.
5003 = top floor FINALE ambient fx delayed.
5004 = top floor ENDING ambient fx.
5030 = restaurant destruction character lighting
5100 = topfloor ambient damage 1
5200 = topfloor ambient damage 2
5300 = topfloor ambient damage 3

5066 = scripted light for hanging sequence (fx zone trigger needed to only have it turn on when on top floor, not roof)

7000 = rooftop ambient fx that need to be disabled after
			 player gets to the helicopter.
7001 = rooftop blinking lights (not currently activated)
7500 = atmospherics for heli sequence
11000 = restaurant fallen rubble fires.
20000's = post heli crash fire
20222 = gun light used to light mak's gun on ground at a distance
20110 = gun light used to light mak's gun on ground at a distance
21000's = skylight vfx:
			skylight cracks are called in dubai_anim
			skylight shatter vfx and glass impacts on balcony are called in dubai_finale
22000's = additional skylight vfx (dubai_anim)
			
------------------------------------------------------------*/



geo_fog_fx()
{
	level waitframe();
	fog_exp = get_exploder_entarray( -11 );
	foreach( curr in fog_exp )
	{
		ent = spawn( "script_model", curr.v["origin"] );
		ent.origin = curr.v["origin"];
		ent.angles = vectortoangles( vectornormalize( curr.v["origin"] - level.player.origin ) * -1 );
		ent setmodel( "fx_db_clouds" );
	}
}


precacheFX()
{
	level._effect[ "db_head_shadow2" ] 	= LoadFX( "maps/dubai/db_head_shadow2" );//placed by fxman
	level._effect[ "db_body_shadow2" ] 	= LoadFX( "maps/dubai/db_body_shadow2" );//placed by fxman
	level._effect[ "db_leg_shadow2" ] 	= LoadFX( "maps/dubai/db_leg_shadow2" );//placed by fxman
	level._effect[ "dubai_lights_rest_yuririm" ] 	= LoadFX( "maps/dubai/dubai_lights_rest_yuririm" );//placed by fxman
	level._effect[ "dubai_lights_rest_yurikey" ] 	= LoadFX( "maps/dubai/dubai_lights_rest_yurikey" );//placed by fxman
	level._effect[ "db_blade_shadow" ] 	= LoadFX( "maps/dubai/db_blade_shadow" );//placed by fxman
	level._effect[ "db_dmg_dust" ] 	= LoadFX( "maps/dubai/db_dmg_dust" );//placed by fxman
	level._effect[ "db_heli_rooftread" ] 	= LoadFX( "maps/dubai/db_heli_rooftread" );//placed by fxman
	level._effect[ "dubai_lights_finale_rim1" ] 	= LoadFX( "lights/dubai_lights_finale_rim1" );//placed by fxman
	level._effect[ "db_blade_fire" ] 	= LoadFX( "maps/dubai/db_blade_fire" );//placed by fxman
	level._effect[ "db_fire_line_sm" ] 	= LoadFX( "maps/dubai/db_fire_line_sm" );//placed by fxman
	level._effect[ "db_helifire_embers" ] 	= LoadFX( "maps/dubai/db_helifire_embers" );//placed by fxman
	level._effect[ "db_leg_shadow" ] 	= LoadFX( "maps/dubai/db_leg_shadow" );//placed by fxman
	level._effect[ "db_head_shadow" ] 	= LoadFX( "maps/dubai/db_head_shadow" );//placed by fxman
	level._effect[ "db_body_shadow" ] 	= LoadFX( "maps/dubai/db_body_shadow" );//placed by fxman
	level._effect[ "db_mak_light" ] 	= LoadFX( "maps/dubai/db_mak_light" );//placed by fxman
	level._effect[ "db_helifire_bg" ] 	= LoadFX( "maps/dubai/db_helifire_bg" );//placed by fxman
	level._effect[ "db_helifire" ] 	= LoadFX( "maps/dubai/db_helifire" );//placed by fxman
	
	//intro fx
	level._effect[ "door_truck_kick_dubai" ]					 			= loadfx( "dust/door_truck_kick_dubai" );
	level._effect[ "ceiling_dust_truck_dubai" ]					 			= loadfx( "dust/ceiling_dust_truck_dubai" );
	level._effect[ "door_gate_breach_dubai_line" ]					 			= loadfx( "dust/door_gate_breach_dubai_line" );
	level._effect[ "door_breach_truck_dubai" ]					 			= loadfx( "dust/door_breach_truck_dubai" );
	level._effect[ "glass_dust_trail_child_dubai" ]					 			= loadfx( "dust/glass_dust_trail_child_dubai" );
	level._effect[ "glass_dust_trail_parent_dubai" ]					 			= loadfx( "dust/glass_dust_trail_parent_dubai" );
	level._effect[ "truck_dubai_ambient_dust" ]					 			= loadfx( "dust/truck_dubai_ambient_dust" );
	level._effect[ "light_shaft_dust_dubai" ]					 			= loadfx( "dust/light_shaft_dust_dubai" );

	//fake vehicle destruction
	level._effect["vehicle_exp_fire_spwn_child"]						= loadfx("fire/vehicle_exp_fire_spwn_child");
	level._effect["vehicle_exp_fire_spwn_child_nodeath"]						= loadfx("fire/vehicle_exp_fire_spwn_child_nodeath");
	level._effect["vehicle_exp_fire_spwn_child_sm"]						= loadfx("fire/vehicle_exp_fire_spwn_child_sm");
	
	//chopper spotlights
	level._effect[ "spotlight" ]						 			= loadfx( "maps/dubai/spotlight_large" );
	
	
	//lighting
	level._effect[ "lighthaze_dubai" ]					 			= loadfx( "misc/lighthaze_dubai" );
	level._effect[ "dubai_lights_glow_white" ]					 	= loadfx( "lights/dubai_lights_glow_white" );
	level._effect[ "lights_conelight_smokey" ]					 	= loadfx( "lights/lights_conelight_smokey" );
	level._effect[ "dubai_lantern_lights_glow" ]					= loadfx( "lights/dubai_lantern_lights_glow");
	level._effect[ "light_blink_paris_police" ]					= loadfx( "lights/light_blink_paris_police");
	level._effect[ "light_blink_suv_dubai_top" ]					= loadfx( "lights/light_blink_suv_dubai_top");
	level._effect[ "lights_godray_beam" ]					= loadfx( "lights/lights_godray_beam");
	level._effect[ "car_suburban_combined_emission" ]					= loadfx( "misc/car_suburban_combined_emission");
	level._effect[ "car_suburban_bottom_front_strobe_l" ]					= loadfx( "misc/car_suburban_bottom_front_strobe_l");
	level._effect[ "car_suburban_bottom_front_strobe_r" ]					= loadfx( "misc/car_suburban_bottom_front_strobe_r");
	level._effect[ "car_sedan_headlight_r" ]					= loadfx( "misc/car_sedan_headlight_r");
	level._effect[ "car_sedan_headlight_l" ]					= loadfx( "misc/car_sedan_headlight_l");
	level._effect[ "car_sedan_taillights_combined_emission" ]					= loadfx( "misc/car_sedan_taillights_combined_emission");
	level._effect[ "dubai_godray_skylight" ]					= loadfx( "maps/dubai/dubai_godray_skylight");
	level._effect[ "dubai_godray_destroyed_restaurant" ]					= loadfx( "maps/dubai/dubai_godray_destroyed_restaurant");
	level._effect[ "dubai_godray_destroyed_restaurant_large" ]					= loadfx( "maps/dubai/dubai_godray_destroyed_restaurant_large");
	level._effect[ "dubai_searchlight_flare" ]					= loadfx( "lights/dubai_searchlight_flare");
	level._effect["dubai_helicopter_console_light"]							= loadfx("maps/dubai/dubai_helicopter_console_light");
	level._effect["dubai_helicopter_console_light_2"]							= loadfx("maps/dubai/dubai_helicopter_console_light_2");
	level._effect["dubai_lights_atrium"]							= loadfx("lights/dubai_lights_atrium");
	level._effect["restaurant_destruction_character_light"]							= loadfx("maps/dubai/restaurant_destruction_character_light");
	level._effect[ "suburban_strobe_centered_r" ]					= loadfx( "misc/suburban_strobe_centered_r");
	level._effect[ "suburban_strobe_centered_l" ]					= loadfx( "misc/suburban_strobe_centered_l");
	level._effect[ "db_crashsite_fill_light" ]					= loadfx( "maps/dubai/db_crashsite_fill_light");
	level._effect[ "db_crashsite_fill_light_sm" ]					= loadfx( "maps/dubai/db_crashsite_fill_light_sm");
	level._effect[ "db_crashsite_gun_light_ground" ]					= loadfx( "maps/dubai/db_crashsite_gun_light_ground");
	level._effect[ "db_atrium_godray" ]					= loadfx( "maps/dubai/db_atrium_godray");
	level._effect[ "db_crashsite_gun_light_pickup" ]					= loadfx( "maps/dubai/db_crashsite_gun_light_pickup");
	
	//Ambient VFX In Distance Out On Water
	level._effect[ "dubai_bg_fog" ]					 				= loadfx( "maps/dubai/dubai_bg_fog" );
	level._effect[ "dubai_bg_fog_dark" ]					 		= loadfx( "maps/dubai/dubai_bg_fog_dark" );
	level._effect[ "dubai_bg_fog_xlarge" ]					 				= loadfx( "maps/dubai/dubai_bg_fog_xlarge" );
			
	//elevator
	level._effect[ "elevator_explosion" ] 							= loadfx( "maps/dubai/elevator_crash");
	level._effect["dubai_lights_elevator_flare"]					= loadfx("lights/dubai_lights_elevator_flare");
	level._effect["dubai_elevator_light"]							= loadfx("maps/dubai/dubai_elevator_light");
	level._effect["fire_smoke_trail_m_emitter"]						= loadfx("fire/fire_smoke_trail_m_emitter");
	level._effect["heli_engine_fire"]								= loadfx("fire/heli_engine_fire");
	level._effect["elevator_sparks"]								= loadfx("maps/dubai/elevator_sparks");
	level._effect["elevator_smoke"]									= loadfx("maps/dubai/elevator_smoke");
	level._effect["elevator_brake_sparks"]							= loadfx("maps/dubai/elevator_brake_sparks");
	level._effect["elevator_heli_crash"]							= loadfx("maps/dubai/elevator_heli_crash");
	level._effect["elevator_drop"]									= loadfx("maps/dubai/elevator_drop");
	level._effect["elevator_drop_2"]									= loadfx("maps/dubai/elevator_drop_2");
	level._effect["elevator_drop_sparks"]									= loadfx("maps/dubai/elevator_drop_sparks");
	level._effect["fire_yuri_body"]									= loadfx("maps/dubai/fire_yuri_body");
	level._effect["fire_yuri_limb"]									= loadfx("maps/dubai/fire_yuri_limb");
	level._effect["fire_yuri_limb_2"]								= loadfx("maps/dubai/fire_yuri_limb_2");
	level._effect["fire_yuri_limb_3"]								= loadfx("maps/dubai/fire_yuri_limb_3");
	level._effect["fire_player_limb"]								= loadfx("maps/dubai/fire_player_limb");
	level._effect["limb_fire_off"]									= loadfx("maps/dubai/limb_fire_off");
	level._effect["body_fire_off"]									= loadfx("maps/dubai/body_fire_off");
	level._effect["player_fire_off"]									= loadfx("maps/dubai/player_fire_off");
	level._effect["player_helmet_fire_off"]									= loadfx("maps/dubai/player_helmet_fire_off");
	
	level._effect["blackhawk_flash_armada"]								= loadfx("muzzleflashes/blackhawk_flash_armada");
	
	//elevator floor #
	level._effect["dubai_elevator_num_l"]									= loadfx("maps/dubai/dubai_elevator_num_l");
	level._effect["dubai_elevator_num_g"]									= loadfx("maps/dubai/dubai_elevator_num_g");
	level._effect["dubai_elevator_num_0"]									= loadfx("maps/dubai/dubai_elevator_num_0");
	level._effect["dubai_elevator_num_1"]									= loadfx("maps/dubai/dubai_elevator_num_1");
	level._effect["dubai_elevator_num_2"]									= loadfx("maps/dubai/dubai_elevator_num_2");
	level._effect["dubai_elevator_num_3"]									= loadfx("maps/dubai/dubai_elevator_num_3");
	level._effect["dubai_elevator_num_4"]									= loadfx("maps/dubai/dubai_elevator_num_4");
	level._effect["dubai_elevator_num_5"]									= loadfx("maps/dubai/dubai_elevator_num_5");
	level._effect["dubai_elevator_num_6"]									= loadfx("maps/dubai/dubai_elevator_num_6");
	level._effect["dubai_elevator_num_7"]									= loadfx("maps/dubai/dubai_elevator_num_7");
	level._effect["dubai_elevator_num_8"]									= loadfx("maps/dubai/dubai_elevator_num_8");
	level._effect["dubai_elevator_num_9"]									= loadfx("maps/dubai/dubai_elevator_num_9");
	


	
	//Ambient VFX
	level._effect[ "dubai_fountain_splash" ]					 	= loadfx( "maps/dubai/dubai_fountain_splash" );
	level._effect[ "dubai_fountain_splash_l" ]					 	= loadfx( "maps/dubai/dubai_fountain_splash_l" );
	level._effect[ "dubai_fountain_rock_splash" ]					 	= loadfx( "maps/dubai/dubai_fountain_rock_splash" );
	level._effect[ "dubai_water_fountain" ]					 		= loadfx( "maps/dubai/dubai_water_fountain" );
	level._effect[ "dubai_water_fountain_plume_runner" ]					 		= loadfx( "maps/dubai/dubai_water_fountain_plume_runner" );
	level._effect[ "dubai_falling_leaves" ]					 	= loadfx( "maps/dubai/dubai_falling_leaves" );
	level._effect[ "dubai_ocean_rock_splash" ]					 	= loadfx( "maps/dubai/dubai_ocean_rock_splash" );
	level._effect[ "dubai_ocean_rock_splash_2" ]					 	= loadfx( "maps/dubai/dubai_ocean_rock_splash_2" );
	level._effect[ "dubai_vista_glow_green" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_green" );
	level._effect[ "dubai_vista_glow_yellow" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_yellow" );
	level._effect[ "dubai_vista_glow_yellow_s" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_yellow_s" );
	level._effect[ "dubai_vista_glow_yellow_s_2" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_yellow_s_2" );
	level._effect[ "dubai_vista_glow_yellow_s_3" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_yellow_s_3" );
	level._effect[ "dubai_vista_glow_green_l" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_green_l" );
	level._effect[ "dubai_vista_glow_blue" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_blue" );
	level._effect[ "dubai_vista_glow_blue_l" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_blue_l" );
	level._effect[ "dubai_vista_glow_purple" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_purple" );
	level._effect[ "dubai_vista_glow_red" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_red" );
	level._effect[ "boat_red_glow" ]					 				= loadfx( "maps/dubai/boat_red_glow" );
	level._effect[ "dubai_vista_glow_red_2" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_red_2" );
	level._effect[ "dubai_vista_glow_white" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_white" );
	level._effect[ "dubai_vista_glow_white_2" ]					 	= loadfx( "maps/dubai/dubai_vista_glow_white_2" );
	level._effect[ "vista_traffic_car" ]					 	= loadfx( "maps/dubai/vista_traffic_car" );
	level._effect[ "vista_traffic_car_2" ]					 	= loadfx( "maps/dubai/vista_traffic_car_2" );
	level._effect[ "vista_traffic_car_short" ]					 	= loadfx( "maps/dubai/vista_traffic_car_short" );
	level._effect[ "vista_traffic_car_u" ]					 	= loadfx( "maps/dubai/vista_traffic_car_u" );
	level._effect[ "dust_spiral_dubai" ]					 		= loadfx( "dust/dust_spiral_dubai" );
	level._effect[ "amb_dust_battlefield" ]					 		= loadfx( "dust/amb_dust_battlefield" );
	level._effect[ "amb_smoke_add_dubai" ]					 		= loadfx( "smoke/amb_smoke_add_dubai" );	
	level._effect[ "pool_splash_fountain" ]					 		= loadfx( "maps/dubai/pool_splash_fountain" );	
	level._effect[ "birds_takeof_runner" ]					 		= loadfx( "maps/dubai/dubai_bird_runner" );	
	level._effect[ "dubai_wind" ]					 							= loadfx( "maps/dubai/dubai_wind" );
	level._effect[ "amb_smoke_add_dubai_light" ]					 		= loadfx( "smoke/amb_smoke_add_dubai_light" );	

	
	//blood impact vfx
	level._effect[ "flesh_hit" ]					 				= loadfx( "impacts/flesh_hit" );
	
	//prop destruct vfx
	level._effect[ "grand_piano_exp" ]					 			= loadfx( "props/grand_piano_exp" );
	level._effect[ "rest_flower_vase" ]					 			= loadfx( "props/rest_flower_vase" );
	level._effect[ "foliage_dub_potted_palm_01" ]			= loadfx( "props/foliage_dub_potted_palm_01" );
	level._effect[ "dub_vase_02" ]										= loadfx( "props/dub_vase_02" );
	level._effect[ "foliage_dub_potted_spikey_plant" ]			= loadfx( "props/foliage_dub_potted_spikey_plant" );
	level._effect[ "rest_plates" ]					 				= loadfx( "props/rest_plates" );
	level._effect[ "rest_plates_vase" ]					 			= loadfx( "props/rest_plates_vase" );
	level._effect[ "dubai_elevator_glass" ]					 			= loadfx( "breakables/dubai_elevator_glass" );
	level._effect[ "bottles_brandy_destruct" ]						    	= loadfx( "props/bottles_brandy_destruct" );
	level._effect[ "bottles_wine_destruct" ]						    	= loadfx( "props/bottles_wine_destruct" );
	level._effect[ "bottles_vodka_destruct" ]						    	= loadfx( "props/bottles_vodka_destruct" );
	level._effect[ "bottles_water_destruct" ]						    	= loadfx( "props/bottles_water_destruct" );
	level._effect[ "bottles_tea_destruct" ]						    	= loadfx( "props/bottles_tea_destruct" );
	level._effect[ "bottles_misc1_destruct" ]						    	= loadfx( "props/bottles_misc1_destruct" );
	level._effect[ "bottles_misc2_destruct" ]						    	= loadfx( "props/bottles_misc2_destruct" );
	level._effect[ "bottles_misc3_destruct" ]						    	= loadfx( "props/bottles_misc3_destruct" );
	level._effect[ "bottles_misc4_destruct" ]						    	= loadfx( "props/bottles_misc4_destruct" );
	level._effect[ "bottles_misc5_destruct" ]						    	= loadfx( "props/bottles_misc5_destruct" );
	
	level._effect[ "dubai_rest_anim_round_table" ]					 		= loadfx( "props/rest_table_rnd_nodressing_dest" );
	level._effect[ "dubai_rest_anim_sqr_table" ]					 			= loadfx( "props/rest_table_sqr_nodressing_dest" );
	level._effect[ "dubai_rest_anim_sqr_table_solo" ]					 	= loadfx( "props/rest_table_square_dest" );
	
	//ambient vfx post collapse in restauran
	level._effect[ "water_pipe_spray" ]								= loadfx( "water/water_pipe_spray" );
	level._effect[ "water_drips_fat_fast_speed" ]			 		= loadfx( "water/water_drips_fat_fast_speed" );
	level._effect[ "drips_fast" ]			 						= loadfx( "misc/drips_fast" );
	level._effect[ "drips_slow" ]			 						= loadfx( "misc/drips_slow" );
	level._effect[ "falling_dirt_light_1_runner" ]					= loadfx( "dust/falling_dirt_light_1_runner" );
	level._effect[ "smoke_white_room_linger" ]						= loadfx( "smoke/smoke_white_room_linger" );
	level._effect[ "powerline_runner" ]								= loadfx( "explosions/powerline_runner" );
	level._effect[ "cloud_ash_lite" ]						    	= loadfx( "weather/cloud_ash_lite" );
	level._effect[ "paper_blowing_trash" ]							= loadfx( "misc/paper_blowing_trash" );
	level._effect[ "dust_wind_fast_paper" ]							= loadfx( "dust/dust_wind_fast_paper" );
	level._effect[ "fire_generic_atlas_curl_nosmoke" ]				= loadFX( "fire/fire_generic_atlas_curl_nosmoke" );
	level._effect[ "firelp_med_pm_cheap_nodist_light" ]				= loadfx( "fire/firelp_med_pm_cheap_nodist_light" );
	level._effect[ "firelp_med_pm_nolight_nodist" ]					= loadfx( "fire/firelp_med_pm_nolight_nodist" );
	level._effect[ "firelp_small_streak_pm_h" ]						= loadfx( "fire/firelp_small_streak_pm_h" );
	level._effect[ "fire_line_sm" ]						  			= loadfx( "fire/fire_line_sm" );
	level._effect[ "fire_falling_runner_angled" ]					= loadfx( "fire/fire_falling_runner_angled" );
	level._effect[ "fire_ceiling_md_slow" ]							= loadFX( "fire/fire_ceiling_md_slow" );
	level._effect[ "trash_spirallo_runner" ] 						= LoadFX( "misc/trash_spirallo_runner" );
	level._effect[ "smoldering_smoke_windy" ] 						= LoadFX( "smoke/smoldering_smoke_windy" );
	level._effect[ "smoke_rolling_wind" ] 						= LoadFX( "smoke/smoke_rolling_wind" );
	level._effect[ "smoke_rolling_wind_short" ] 						= LoadFX( "smoke/smoke_rolling_wind_short" );
	level._effect[ "smoke_rolling_wind_dark" ] 						= LoadFX( "smoke/smoke_rolling_wind_dark" );
	level._effect[ "smoke_rolling_wind_thick" ] 						= LoadFX( "smoke/smoke_rolling_wind_thick" );
	
	//tread fx
	level._effect[ "tread_dust_paris_small" ] 						= LoadFX( "treadfx/tread_dust_paris_small" );
	level._effect[ "no_effect" ] 						= LoadFX( "misc/no_effect" );
	level._effect[ "tread_road_sniperescape" ] 						= LoadFX( "treadfx/tread_road_sniperescape" );
	level._effect[ "tread_road_dubai" ] 						= LoadFX( "treadfx/tread_road_dubai" );
	level._effect[ "tread_road_dubai_parent" ] 						= LoadFX( "treadfx/tread_road_dubai_parent" );
	level._effect[ "pb_jeep_trail_road_skid_long" ] 						= LoadFX( "treadfx/pb_jeep_trail_road_skid_long" );
	level._effect[ "pb_jeep_trail_road_skid_long_db01" ] 						= LoadFX( "treadfx/pb_jeep_trail_road_skid_long_db01" );
	level._effect[ "pb_jeep_trail_road_skid_long_db02" ] 						= LoadFX( "treadfx/pb_jeep_trail_road_skid_long_db02" );
	level._effect[ "pb_jeep_trail_road_skid_long_db03" ] 						= LoadFX( "treadfx/pb_jeep_trail_road_skid_long_db03" );
	level._effect[ "pb_jeep_trail_road_skid_long_db04" ] 						= LoadFX( "treadfx/pb_jeep_trail_road_skid_long_db04" );

	
	
	/*----------------------------------------------
		RESTAURANT DESTRUCT SE VFX
	----------------------------------------------*/
	
	level._effect[ "db_rest_dest_wall_explo" ]					 	= loadfx( "maps/dubai/db_rest_dest_wall_explo" );
	level._effect[ "db_rest_dest_metal_structure_explo" ]			= loadfx( "maps/dubai/db_rest_dest_metal_structure_explo" );
	level._effect[ "db_rest_dest_window_explo" ]					= loadfx( "maps/dubai/db_rest_dest_window_explo" );
	level._effect[ "db_rest_dest_window_ceiling_explo" ]			= loadfx( "maps/dubai/db_rest_dest_window_ceiling_explo" );
	level._effect[ "db_rest_dest_debris_flyingout" ]				= loadfx( "maps/dubai/db_rest_dest_debris_flyingout" );
	level._effect[ "ceiling_marble_collapse" ]						= loadfx( "explosions/ceiling_marble_collapse" );
	level._effect[ "db_rest_dest_fire_line_trailing" ]				= loadfx( "maps/dubai/db_rest_dest_fire_line_trailing" );
	level._effect[ "db_rest_dest_dust_rock_fall_wall" ]				= loadfx( "maps/dubai/db_rest_dest_dust_rock_fall_wall" );
	level._effect[ "db_rest_dest_dust_rock_fall_ceiling" ]			= loadfx( "maps/dubai/db_rest_dest_dust_rock_fall_ceiling" );
	level._effect[ "db_rest_dest_rokt_hit_flr_imp" ]				= loadfx( "maps/dubai/db_rest_dest_rokt_hit_flr_imp" );
	level._effect[ "db_rest_dest_marblefall_grn_linger" ]			= loadfx( "maps/dubai/db_rest_dest_marblefall_grn_linger" );
	level._effect[ "db_rest_dest_column_shatter_debris" ]			= loadfx( "maps/dubai/db_rest_dest_column_shatter_debris" );
	level._effect[ "db_rest_dest_column_shatter2_debris" ]			= loadfx( "maps/dubai/db_rest_dest_column_shatter2_debris" );
	level._effect[ "pipe_fire_looping" ]							= loadfx( "impacts/pipe_fire_looping" );
	level._effect[ "pipe_steam_looping" ]							= loadfx( "impacts/pipe_steam_looping" );
	level._effect[ "column_fall_dust_impact" ]						= loadfx( "dust/column_fall_dust_impact" );
	level._effect[ "db_rest_dest_smoldering_smk_grnd" ]				= loadfx( "maps/dubai/db_rest_dest_smoldering_smk_grnd" );
	level._effect[ "db_rest_dest_smoldering_smk_grnd_narrow" ]		= loadfx( "maps/dubai/db_rest_dest_smoldering_smk_grnd_narrow" );
	level._effect[ "db_rest_dest_falling_debris" ]					= loadfx( "maps/dubai/db_rest_dest_falling_debris" );
	level._effect[ "water_generic_explosion" ]						= loadfx( "water/water_generic_explosion" );
	level._effect[ "firelp_small_pm_a_nolight" ]					= loadfx( "fire/firelp_small_pm_a_nolight" );
	level._effect[ "firelp_small_pm_a" ]							= loadfx( "fire/firelp_small_pm_a" );
	level._effect[ "db_rest_dest_debris_rolling" ]					= loadfx( "maps/dubai/db_rest_dest_debris_rolling" );
	level._effect[ "db_throw_bottles" ]					= loadfx( "maps/dubai/db_throw_bottles" );
	
	level._effect[ "yuri_blood" ]					 	= loadfx( "maps/dubai/yuri_blood" );
	level._effect[ "yuri_blood_2" ]					 	= loadfx( "maps/dubai/yuri_blood_2" );
	level._effect[ "yuri_blood_3" ]					 	= loadfx( "maps/dubai/yuri_blood_3" );
	level._effect[ "yuri_blood_4" ]					 	= loadfx( "maps/dubai/yuri_blood_4" );
	level._effect[ "yuri_blood_5" ]					 	= loadfx( "maps/dubai/yuri_blood_5" );
	level._effect[ "yuri_blood_floor" ]			= loadfx( "maps/dubai/yuri_blood_floor" );
	level._effect[ "yuri_blood_body" ]					 	= loadfx( "maps/dubai/yuri_blood_body" );
	level._effect[ "blood_drip_price_nose" ]					 	= loadfx( "maps/dubai/blood_drip_price_nose" );
	
	
	
	/*----------------------------------------------
		FINALE SE VFX
	----------------------------------------------*/
	
	level._effect[ "knife_attack_throat" ]			= loadfx( "maps/dubai/knife_attack_throat" );
	level._effect[ "copilot_muzzleflash" ]			= loadfx( "maps/dubai/copilot_muzzleflash" );
	level._effect[ "heli_fire" ]			= loadfx( "maps/dubai/heli_fire" );
	level._effect[ "db_heli_fire_reflect" ]			= loadfx( "maps/dubai/db_heli_fire_reflect" );
	level._effect[ "heli_sparks" ]			= loadfx( "maps/dubai/heli_sparks" );
	level._effect[ "punch_pilot" ]			= loadfx( "maps/dubai/punch_pilot" );
	level._effect[ "rooftop_heli_crash" ]			= loadfx( "maps/dubai/rooftop_heli_crash" );
	level._effect[ "yuri_headshot_blood" ]			= loadfx( "maps/dubai/yuri_headshot_blood" );
	level._effect[ "yuri_chestshot_blood" ]			= loadfx( "maps/dubai/yuri_chestshot_blood" );
	level._effect[ "generic_chestshot_blood" ]			= loadfx( "maps/dubai/generic_chestshot_blood" );
  	level._effect[ "yuri_shot_blood_decal" ]			= loadfx( "maps/dubai/yuri_shot_blood_decal" );
	level._effect[ "makarov_blood" ]			= loadfx( "maps/dubai/makarov_blood" );
	level._effect[ "makarov_blood_floor" ]			= loadfx( "maps/dubai/makarov_blood_floor" );
	level._effect[ "makarov_blood_floor_2" ]			= loadfx( "maps/dubai/makarov_blood_floor_2" );
	level._effect[ "makarov_blood_floor_3" ]			= loadfx( "maps/dubai/makarov_blood_floor_3" );
	level._effect[ "makarov_blood_cough_1" ]					 	= loadfx( "maps/dubai/makarov_blood_cough_1" );
	level._effect[ "makarov_blood_cough_2" ]					 	= loadfx( "maps/dubai/makarov_blood_cough_2" );
	level._effect[ "makarov_muzzle_flash" ]			= loadfx( "maps/dubai/makarov_muzzle_flash" );
	level._effect[ "makarov_muzzle_flash_simple" ]			= loadfx( "maps/dubai/makarov_muzzle_flash_simple" );
	level._effect[ "makarov_muzzle_flash_simple_nodepth" ]			= loadfx( "maps/dubai/makarov_muzzle_flash_simple_nodepth" );
	level._effect[ "yuri_muzzle_flash" ]			= loadfx( "maps/dubai/yuri_muzzle_flash" );
	level._effect[ "makarov_punch_r" ]					 	= loadfx( "maps/dubai/makarov_punch_r" );
	level._effect[ "makarov_punch_r2" ]					 	= loadfx( "maps/dubai/makarov_punch_r2" );
	level._effect[ "makarov_punch_l" ]					 	= loadfx( "maps/dubai/makarov_punch_l" );
	level._effect[ "zippo_fire" ]			= loadfx( "maps/dubai/zippo_fire" );
	level._effect[ "zippo_sparks" ]			= loadfx( "maps/dubai/zippo_sparks" );
	level._effect[ "cigar_lite" ]			= loadfx( "maps/dubai/cigar_lite" );
	level._effect[ "cigar_puff" ]			= loadfx( "maps/dubai/cigar_puff" );
	level._effect[ "cigar_lite_smoke" ]			= loadfx( "maps/dubai/cigar_lite_smoke" );
	level._effect[ "cigar_smoke" ]			= loadfx( "maps/dubai/cigar_smoke" );
	level._effect[ "cigar_drop" ]			= loadfx( "maps/dubai/cigar_drop" );
	level._effect[ "blob_shadow_character" ]			= loadfx( "misc/blob_shadow_character" );
	level._effect[ "blood_smear" ]									= loadfx( "impacts/blood_smear_decal_dubai" );
	level._effect[ "blood_pool" ]									= loadfx( "impacts/deathfx_bloodpool_dubai" );
	
	
	//skylight cracks
	level._effect[ "db_finale_glass_cracks_1" ]						= loadfx( "maps/dubai/db_finale_glass_cracks_1" );
	//level._effect[ "db_finale_glass_cracks_2" ]						= loadfx( "maps/dubai/db_finale_glass_cracks_2" );
	//level._effect[ "db_finale_glass_cracks_3" ]						= loadfx( "maps/dubai/db_finale_glass_cracks_3" );
	//level._effect[ "db_finale_glass_cracks_4" ]						= loadfx( "maps/dubai/db_finale_glass_cracks_4" );
	//level._effect[ "db_finale_glass_cracks_5" ]						= loadfx( "maps/dubai/db_finale_glass_cracks_5" );
	//level._effect[ "db_finale_glass_cracks_reflection" ]			= loadfx( "maps/dubai/db_finale_glass_cracks_reflection" );
	level._effect[ "dub_head_impact_dust" ]						= loadfx( "dust/dub_head_impact_dust" );
	level._effect[ "dub_head_impact_bits" ]						= loadfx( "dust/dub_head_impact_bits" );
	level._effect[ "dub_head_impact_bits_delay" ]						= loadfx( "dust/dub_head_impact_bits_delay" );
	level._effect[ "dub_head_impact_bits_close" ]						= loadfx( "dust/dub_head_impact_bits_close" );
	
  	level._effect[ "db_finale_skylight_shatter" ]					= loadfx( "maps/dubai/db_finale_skylight_shatter" );
  	level._effect[ "db_finale_skylight_glass_impact" ]				= loadfx( "maps/dubai/db_finale_skylight_glass_impact" );
	
	
	/*----------------------------------------------
		FINALE ENV FX
	----------------------------------------------*/
	level._effect[ "db_finale_dust_grnd" ]			= loadfx( "maps/dubai/db_finale_dust_grnd" );
	level._effect[ "cloud_ash_lite_wind" ]						    	= loadfx( "weather/cloud_ash_lite_wind" );
	level._effect[ "leaves_fall_intense_dubai" ]						    	= loadfx( "misc/leaves_fall_intense_dubai" );
	level._effect[ "leaves_blow_intense_dubai" ]						    	= loadfx( "misc/leaves_blow_intense_dubai" );
	level._effect[ "leaves_blow_intense_dubai_med" ]						    	= loadfx( "misc/leaves_blow_intense_dubai_med" );
	level._effect[ "leaves_blow_intense_dubai_large" ]						    	= loadfx( "misc/leaves_blow_intense_dubai_large" );
	level._effect[ "dust_ground_gust_runner_dubai" ]						    	= loadfx( "dust/dust_ground_gust_runner_dubai" );
	level._effect[ "dust_ground_gust_runner_dubai_tree" ]						    	= loadfx( "dust/dust_ground_gust_runner_dubai_tree" );
	level._effect[ "dust_ground_gust_runner_dubai_slow" ]						    	= loadfx( "dust/dust_ground_gust_runner_dubai_slow" );
	level._effect[ "leaves_blow_tumble_dubai" ]						    	= loadfx( "misc/leaves_blow_tumble_dubai" );
	level._effect[ "light_blue_pulse" ]						    	= loadfx( "misc/light_blue_pulse" );
	level._effect[ "light_blue_pulse_offset" ]						    	= loadfx( "misc/light_blue_pulse_offset" );
	level._effect[ "dubai_lights_elevator_flare_00" ]						    	= loadfx( "lights/dubai_lights_elevator_flare_00" );
	level._effect[ "dust_ground_gust_runner_dubai_billboard" ]						    	= loadfx( "dust/dust_ground_gust_runner_dubai_billboard" );
	level._effect[ "leaves_blow_tumble_dubai_light" ]						    	= loadfx( "misc/leaves_blow_tumble_dubai_light" );
	level._effect[ "light_blue_pulse_light" ]						    	= loadfx( "misc/light_blue_pulse_light" );
	level._effect[ "light_blue_pulse_light_offset" ]						    	= loadfx( "misc/light_blue_pulse_light_offset" );
	level._effect[ "fire_line_sm_cheap_intro" ]						    	= loadfx( "fire/fire_line_sm_cheap_intro" );
	level._effect[ "fire_generic_atlas_small_nocull" ]						    	= loadfx( "fire/fire_generic_atlas_small_nocull" );
	level._effect[ "fire_generic_glow" ]						    	= loadfx( "fire/fire_generic_glow" );
	level._effect[ "fire_generic_atlas_small_decal" ]						    	= loadfx( "fire/fire_generic_atlas_small_decal" );
	level._effect[ "fire_generic_glow_small" ]						    	= loadfx( "fire/fire_generic_glow_small" );
	level._effect[ "fire_generic_atlas_curl" ]						    	= loadfx( "fire/fire_generic_atlas_curl" );
	level._effect[ "electrical_transformer_spark_runner_tight" ]						    	= loadfx( "explosions/electrical_transformer_spark_runner_tight" );
	level._effect[ "spark_fountain" ]						    	= loadfx( "misc/spark_fountain" );
	level._effect[ "amb_smoke_add_dubai_bright" ]						    	= loadfx( "smoke/amb_smoke_add_dubai_bright" );
	level._effect[ "amb_smoke_add_dubai_bright_spot" ]						    	= loadfx( "smoke/amb_smoke_add_dubai_bright_spot" );
	level._effect[ "amb_smoke_add_dubai_bright_end" ]						    	= loadfx( "smoke/amb_smoke_add_dubai_bright_end" );
	level._effect[ "amb_smoke_add_dubai_bright_end_dark" ]						    	= loadfx( "smoke/amb_smoke_add_dubai_bright_end_dark" );
	level._effect[ "amb_smoke_add_dubai_fast_end" ]						    	= loadfx( "smoke/amb_smoke_add_dubai_fast_end" );
	level._effect[ "amb_smoke_add_dubai_dark" ]						    	= loadfx( "smoke/amb_smoke_add_dubai_dark" );
	level._effect[ "dub_ending_godray" ]						    	= loadfx( "misc/dub_ending_godray" );
	level._effect[ "dub_ending_godray_light" ]						    	= loadfx( "misc/dub_ending_godray_light" );

	level._effect[ "foliage_dub_entrace_planter01" ]						    	= loadfx( "props/foliage_dub_entrace_planter01" );
	

	level._effect[ "dust_specks_ambient_dubai" ]						    	= loadfx( "dust/dust_specks_ambient_dubai" );
	level._effect[ "light_shaft_dust_large_dubai" ]						    	= loadfx( "dust/light_shaft_dust_large_dubai" );
	
	level._effect[ "field_fire_smolder_dubai" ]						    	= loadfx( "fire/field_fire_smolder_dubai" );
	level._effect[ "fire_generic_ball_burst_large_dubai" ]						    	= loadfx( "fire/fire_generic_ball_burst_large_dubai" );
	level._effect[ "thick_black_smoke_l_dubai" ]						    	= loadfx( "smoke/thick_black_smoke_l_dubai" );
	level._effect[ "embers_finale_dubai" ]						    	= loadfx( "fire/embers_finale_dubai" );
	level._effect[ "amb_smoke_add_dubai_fast" ]						    	= loadfx( "smoke/amb_smoke_add_dubai_fast" );



}


init_smVals()
{
	setsaveddvar("fx_alphathreshold",10);
}

exterior_suv_skid1(exterior_suv_1)
{
	
	
	left_wheel_tag_ent = spawn_tag_origin();
	left_wheel_tag_ent.origin = exterior_suv_1 gettagorigin("tag_wheel_back_left");
	left_wheel_tag_ent.angles = vectortoangles((0,0,1));
	left_wheel_tag_ent linkto(exterior_suv_1, "tag_wheel_back_left");
	
	right_wheel_tag_ent = spawn_tag_origin();
	right_wheel_tag_ent.origin = exterior_suv_1 gettagorigin("tag_wheel_back_right");
	right_wheel_tag_ent.angles = vectortoangles((0,0,1));
	right_wheel_tag_ent linkto(exterior_suv_1, "tag_wheel_back_right");
	
	wait(2.35);
	playfxontag(getfx("pb_jeep_trail_road_skid_long_db01"),left_wheel_tag_ent,"tag_origin");
	playfxontag(getfx("pb_jeep_trail_road_skid_long_db01"),right_wheel_tag_ent,"tag_origin");
}

exterior_suv_skid2(exterior_suv_2)
{
	
	
	left_wheel_tag_ent = spawn_tag_origin();
	left_wheel_tag_ent.origin = exterior_suv_2 gettagorigin("tag_wheel_back_left");
	left_wheel_tag_ent.angles = vectortoangles((0,0,1));
	left_wheel_tag_ent linkto(exterior_suv_2, "tag_wheel_back_left");
	
	right_wheel_tag_ent = spawn_tag_origin();
	right_wheel_tag_ent.origin = exterior_suv_2 gettagorigin("tag_wheel_back_right");
	right_wheel_tag_ent.angles = vectortoangles((0,0,1));
	right_wheel_tag_ent linkto(exterior_suv_2, "tag_wheel_back_right");
	
	wait(2.0);
	playfxontag(getfx("pb_jeep_trail_road_skid_long_db02"),left_wheel_tag_ent,"tag_origin");
	playfxontag(getfx("pb_jeep_trail_road_skid_long_db02"),right_wheel_tag_ent,"tag_origin");
}

exterior_suv_skid3(exterior_suv_left)
{
	
	
	left_wheel_tag_ent = spawn_tag_origin();
	left_wheel_tag_ent.origin = exterior_suv_left gettagorigin("tag_wheel_back_left");
	left_wheel_tag_ent.angles = vectortoangles((0,0,1));
	left_wheel_tag_ent linkto(exterior_suv_left, "tag_wheel_back_left");
	
	right_wheel_tag_ent = spawn_tag_origin();
	right_wheel_tag_ent.origin = exterior_suv_left gettagorigin("tag_wheel_back_right");
	right_wheel_tag_ent.angles = vectortoangles((0,0,1));
	right_wheel_tag_ent linkto(exterior_suv_left, "tag_wheel_back_right");
	
	wait(1.0);
	playfxontag(getfx("pb_jeep_trail_road_skid_long_db03"),left_wheel_tag_ent,"tag_origin");
	playfxontag(getfx("pb_jeep_trail_road_skid_long_db03"),right_wheel_tag_ent,"tag_origin");
}

exterior_suv_skid4(exterior_suv_right)
{
	
	
	left_wheel_tag_ent = spawn_tag_origin();
	left_wheel_tag_ent.origin = exterior_suv_right gettagorigin("tag_wheel_back_left");
	left_wheel_tag_ent.angles = vectortoangles((0,0,1));
	left_wheel_tag_ent linkto(exterior_suv_right, "tag_wheel_back_left");
	
	right_wheel_tag_ent = spawn_tag_origin();
	right_wheel_tag_ent.origin = exterior_suv_right gettagorigin("tag_wheel_back_right");
	right_wheel_tag_ent.angles = vectortoangles((0,0,1));
	right_wheel_tag_ent linkto(exterior_suv_right, "tag_wheel_back_right");
	
	wait(1.15);
	playfxontag(getfx("pb_jeep_trail_road_skid_long_db04"),left_wheel_tag_ent,"tag_origin");
	playfxontag(getfx("pb_jeep_trail_road_skid_long_db04"),right_wheel_tag_ent,"tag_origin");
}

intro_breach_fx()
{
	truck_door_ent = getent("intro_truck", "targetname");

	
	wait(24.80);
	playfxontag(getfx("glass_dust_trail_parent_dubai"),truck_door_ent,"tag_fx4");
	exploder(1104);
	wait(0.1);
	exploder(1103);
	wait(0.0);
	exploder(1100);
	wait(0.0);
	exploder(1101);
	wait(0.1);
	exploder(1102);
}

intro_dof()
{
	start = level.dofDefault;	

	dof_intro = [];
	dof_intro[ "nearStart" ] = .1;
	dof_intro[ "nearEnd" ] = .2;
	dof_intro[ "nearBlur" ] = 4.0;
	dof_intro[ "farStart" ] = 1000;
	dof_intro[ "farEnd" ] = 15000;
	dof_intro[ "farBlur" ] = 1.25;
	
	blend_dof( start, dof_intro, .2 );
	
	flag_wait( "parachute_near_window" );
	
	blend_dof ( dof_intro, start, 2 );
	
}


setup_street_lights()
{
		waitframe();
		//place glow fx on streetlights
		ents = getstructarray_delete( "dubai_streetlight_01_FX_origin", "targetname" );
		if ( !isdefined( ents ) )
			return;
		if ( ents.size <= 0 )
			return;
			
		foreach(myEnt in ents)
		{
			// default effect angles if they dont exist
			if ( !isdefined( myEnt.angles ) )
				myEnt.angles = ( 0, 0, 0 );
			
			fx = spawnfx(getfx("lighthaze_dubai"), myEnt.origin, anglestoforward(myEnt.angles), anglestoUp(myEnt.angles));
			triggerfx(fx,-5);
				/*ent = createOneshotEffect( "lighthaze_dubai" );
				ent.v[ "fxid" ] = "lighthaze_dubai";
				ent.v[ "origin" ] = obj.origin;
				ent.v[ "angles" ] =  obj.angles;
				ent.v[ "delay" ] = -5;*/
		}
}


/*--------------------------------------------
	elevator se VFX
--------------------------------------------*/	
body_fire_vfx()
{
		if ( ( level.Console && level.ps3 ) || !level.Console )
	{
		SetHalfResParticles( true );
	}
	thread stop_vista_fx();
	
	aud_send_msg("start_yuri_fire");
	
	PlayFXOnTag( getfx( "fire_yuri_body" ), level.yuri, "J_MainRoot" );
	PlayFXOnTag( getfx( "fire_yuri_limb" ), level.yuri, "J_Wrist_RI" );
	PlayFXOnTag( getfx( "fire_yuri_limb_3" ), level.yuri, "J_Wrist_LE" );
	PlayFXOnTag( getfx( "fire_yuri_limb_3" ), level.yuri, "J_Knee_RI" );
	wait(0.1);
	PlayFXOnTag( getfx( "fire_yuri_limb" ), level.yuri, "J_Knee_LE" );
	PlayFXOnTag( getfx( "fire_yuri_limb_3" ), level.yuri, "J_Ankle_RI" );
	PlayFXOnTag( getfx( "fire_yuri_limb_3" ), level.yuri, "J_Ankle_LE" );
	PlayFXOnTag( getfx( "fire_yuri_limb_2" ), level.yuri, "J_Neck" );
	wait(4.2);
	PlayFXOnTag( getfx( "limb_fire_off" ), level.yuri, "J_Neck" );
	wait(2.0);
	PlayFXOnTag( getfx( "body_fire_off" ), level.yuri, "J_MainRoot" );
	
	aud_send_msg("stop_yuri_fire");
	
}

player_fire_vfx(player_rig)
{
	PlayFXOnTag( getfx( "fire_player_limb" ), player_rig, "J_Wrist_RI" );
	PlayFXOnTag( getfx( "fire_player_limb" ), player_rig, "J_Wrist_LE" );
	wait(5.1);
	StopFXOnTag( getfx( "fire_player_limb" ), player_rig, "J_Wrist_RI" );
	wait(4.1);
	PlayFXOnTag( getfx( "player_helmet_fire_off" ), player_rig, "J_Elbow_LE" );
	wait(5.7);
	PlayFXOnTag( getfx( "player_fire_off" ), player_rig, "J_Elbow_LE" );
	
	thread start_vista_fx();
}

elevator_sparks_vfx(elev_origin)
{
	aud_send_msg("elevator_fire_start", elev_origin.origin);
	PlayFX( level._effect[ "elevator_heli_crash" ], elev_origin.origin );
	PlayFX( level._effect[ "elevator_sparks" ], elev_origin.origin );
	wait(10.0);
	PlayFX( level._effect[ "elevator_smoke" ], elev_origin.origin );
	wait(3.0);
	PlayFX( level._effect[ "elevator_smoke" ], elev_origin.origin );
	wait(3.0);
	PlayFX( level._effect[ "elevator_smoke" ], elev_origin.origin );
	
}

elevator_drop_vfx(elev_origin)
{
	PlayFX( level._effect[ "elevator_drop" ], elev_origin.origin );
	PlayFX( level._effect[ "elevator_smoke" ], elev_origin.origin );
}

elevator_drop_vfx_2(elev_origin)
{
	PlayFX( level._effect[ "elevator_drop_2" ], elev_origin.origin );
	PlayFX( level._effect[ "elevator_smoke" ], elev_origin.origin );
}

elevator_drop_brake_vfx(elev_origin)
{
	PlayFX( level._effect[ "elevator_drop_sparks" ], elev_origin.origin );
}

elevator_brake_vfx(elev_origin)
{
	PlayFX( level._effect[ "elevator_brake_sparks" ], elev_origin.origin );
	
			if ( ( level.Console && level.ps3 ) || !level.Console )
	{
		SetHalfResParticles( false );
	}
	
	
}

setup_elevator_lights()
{
	waitframe();
	elevator_initial_model=getent("elevator_initial_model","script_noteworthy");
	playfxontag(getfx("dubai_elevator_light"),elevator_initial_model,"tag_light");
	
	flag_wait( "elevator_chopper_crash_done" );
	stopfxontag(getfx("dubai_elevator_light"),elevator_initial_model,"tag_light");
	
	wait(2);
	
	elevator_replacement_model=getent("elevator_replacement_model","script_noteworthy");
	playfxontag(getfx("dubai_elevator_light"),elevator_replacement_model,"tag_light");
	
}	


topfloor_spawn_roomfx( currRoom )
{
		
		exploder( currRoom.v["exploder"] );
		currRoom.v["numVFX"] +=1;
		wait( currRoom.v["vfxLife"] );
		currRoom.v["numVFX"] -=1;
}

topfloor_heal_room( currRoom )
{
	for(;;)
	{
		wait(1.0);
		currRoom.v["health"] -= currRoom.v["healrate"];
		if (currRoom.v["health"]<0) currRoom.v["health"] = 0;
		if(flag( "room_dmg_killall" )) 
		{
			currRoom.v["health"] = 0;
			kill_exploder( currRoom.v["exploder"] );
			currRoom.v["numVFX"] = 0;
		}

	}	
}

topfloor_roomfx_think( currRoom )
{
	for(;;)
	{
		wait(7.0);
		if( currRoom.v["health"] >50 && currRoom.v["numVFX"] < 6)	thread topfloor_spawn_roomfx(currRoom);
		if( currRoom.v["health"] >150 && currRoom.v["numVFX"] < 6)	thread topfloor_spawn_roomfx(currRoom);
		if( currRoom.v["health"] >300 && currRoom.v["numVFX"] < 6)	thread topfloor_spawn_roomfx(currRoom);
	}
}

topfloor_dmg_trigger_think( targetRoom )
{
	for(;;)
	{
		amount = 0;
		self waittill("damage",amount);
		targetRoom.v["health"] += clamp( int( amount * .035 ), 1, 20 );
	}
}


topfloor_room_dmg_start( currRoom )
{
	thread topfloor_heal_room( currRoom );
	thread topfloor_roomfx_think( currRoom );
	for( i=0; i < (currRoom.v["roomTriggers"]).size; i++ )
	{
		currRoom.v["roomTriggers"][i] thread topfloor_dmg_trigger_think( currRoom );
	}
}


topfloor_def_room( triggers )
{
	if( !flag_exist( "room_dmg_killall" ) ) flag_init( "room_dmg_killall" );
	roomInfo = spawnStruct();
	if ( !isdefined( level.fx_room ) )
		level.fx_room = [];
	level.fx_room[ level.fx_room.size ] = roomInfo;
	roomInfo.v["health"] = 0;
	roomInfo.v["healrate"] = 10;
	roomInfo.v["numVFX"] = 0;
	roomInfo.v["vfxLife"] = 10;
	roomInfo.v["vfxOffset"]=(0,0,0);
	roomInfo.v["fxid"] = "";
	roomInfo.v["exploder"] = 0;
	roomInfo.v["roomTriggers"] = triggers;
	return roomInfo;
}

topfloor_init_dmg_hall1()
{
	dmgtrigs = getentarray( "dmg_hall1" ,"targetname" );
	dmgarea = topfloor_def_room( dmgtrigs );
	dmgarea.v["healrate"] = 10;
	dmgarea.v["exploder"] = 5100;
	thread topfloor_room_dmg_start( dmgarea );
}

topfloor_init_dmg_hall2()
{
	dmgtrigs = getentarray( "dmg_hall2" ,"targetname" );
	dmgarea = topfloor_def_room( dmgtrigs );
	dmgarea.v["healrate"] = 10;
	dmgarea.v["exploder"] = 5200;
	thread topfloor_room_dmg_start( dmgarea );
}

topfloor_init_dmg_hall3()
{
	dmgtrigs = getentarray( "dmg_hall3" ,"targetname" );
	dmgarea = topfloor_def_room( dmgtrigs );
	dmgarea.v["healrate"] = 10;
	dmgarea.v["exploder"] = 5300;
	thread topfloor_room_dmg_start( dmgarea );
}

topfloor_kill_all()
{
	if( flag_exist( "room_dmg_killall" ) ) flag_set( "room_dmg_killall" );
}

/*--------------------------------------------
	RESTAURANT DESTRUCTION SE VFX START
--------------------------------------------*/	

restaurant_yuri_light()
{
	rig = self;
	wait 5.0;
	playfxontag( getfx( "dubai_lights_rest_yurikey" ), rig, "tag_rim" );
	flag_wait( "finale_player_jump_start" );
	stopfxontag( getfx( "dubai_lights_rest_yurikey" ), rig, "tag_rim" );
	
	//starts on idle animation
	//level waittill( "fx_beatdown_msg" );//msg signals beginning of tackle (beatdown) animation
	//level waittill( "fx_beatdown_msg_startchoke" );//msg signals beginning of choke
	//level waittill( "fx_beatdown_msg_startslam" );//msg signals beginning of slam
	
	
}


restaurant_halfresparticles_on()
{
	if ( ( level.Console && level.ps3 ) || !level.Console )
	{
		SetHalfResParticles( true );
	}
}

restaurant_halfresparticles_off()
{
	if ( ( level.Console && level.ps3 ) || !level.Console )
	{
		SetHalfResParticles( false );
	}
}

restaurant_collapse_se_vfx()
{
	flag_wait( "restaurant_destruction" );
	
	thread stop_vista_fx();
	
	thread topfloor_kill_all();
	
	thread restaurant_halfresparticles_on();
	
	thread restaurant_rocket_hit_ground_impact_vfx();  //fire where heli rocket hits the player that triggers all the destruction
	delaythread (2.6, ::restaurant_explode_postfx);
	
	wait 2.65;
		
	delaythread (20, ::restaurant_halfresparticles_off);
		
	thread restaurant_detach_init_vfx(); //falling rock and burst vfx when restaurant detaches apart	
	thread restaurant_structure_cable_explosion();
	thread restaurant_wall_explosion();
	thread restaurant_ceiling_skylight_explosion();
	thread restaurant_first_section_falling_vfx(); //vfx falling with the restaurant
	thread restaurant_ground_smoderling_smk_vfx();
	delaythread (0, ::restaurant_column_shatter_1_vfx);
	thread restaurant_first_section_env_vfx();
	thread restaurant_ceilingbeam01_fire_vfx();
	//thread restaurant_ceilingbeam01_pipesteam_vfx();
	thread restaurant_floor_tilt_ground_fire_vfx(); //fire on ground during the floor tilting
	delaythread (3.8, ::restaurant_rolling_debris_vfx);
	delaythread (3.5, ::restaurant_column_2_slowmo); 
	delaythread (3.65, ::restaurant_column_shatter_2_vfx); 
	delaythread (5.5, ::restaurant_ceilingbar01_ground_impact_vfx);
	delaythread (4.0, ::restaurant_falling_character_lighting); 
	delaythread (4.3, ::restaurant_player_slide_dof);
	delaythread (9.0, ::restaurant_ledge_falling_debris_vfx);
	delaythread (9.65, ::restaurant_ledge_poolwater_explosion);
	delaythread (11.0, ::restaurant_post_destruction_se_amb_vfx);
		
	//kill all amb env vfx in restaurant once finale se starts
	flag_wait( "finale_player_jump_start" );
	thread restaurant_env_vfx_kill(); 
}			

restaurant_falling_character_lighting()
{
	exploder(5030);
	wait(6.0);
	kill_exploder(5030);
}

restaurant_rocket_hit_ground_impact_vfx()
{
	delaythread (.35, ::exploder, 10095); //ground impact on rocket hit
	wait (0.3);
	exploder(10096); //fire around rocket hit spot
	
	flag_wait( "restaurant_drop_section_falling" );
	wait(4.0);
	kill_exploder(10096);
}

restaurant_explode_postfx()
{
	currVis = getdvar("vision_set_current");
	visionsetnaked("dubai_restaurant_explosion_flash",.1);
	setblur(4, .1);
	
	wait(.3);
	
	visionsetnaked(currVis,.7);
	//wait(.1);
	setblur(0, .6);
}

restaurant_structure_cable_explosion()
{
	exploder (10001);
}

restaurant_wall_explosion()
{
	exploder (10004);
}

restaurant_ceiling_skylight_explosion()
{
	//delaythread (.1, ::exploder, 10007); //1st ceiling window explosion
	delaythread (.3, ::exploder, 10008); //2nd ceiling window explosion 
	delaythread (3.8, ::exploder, 10009); //3rd ceiling window explosion, happened when column shatter 2 happens
	
	delaythread (.15, ::exploder, 10006);//debris flying out when window destroyed
	
	wait 5.0;
	
	kill_exploder(10006);
}

restaurant_column_shatter_1_vfx()
{
	exploder(10030);	
}

restaurant_column_2_slowmo()
{
	slowmo_setspeed_slow( 0.25 ); //(0.2)
	slowmo_setlerptime_in( 0.5 ); // 
	slowmo_lerp_in();
				
	wait .4;
		
	slowmo_setlerptime_out( 0.3 );  // (0)
	slowmo_lerp_out();
}

restaurant_column_shatter_2_vfx()
{
	exploder(10035);	
}	

restaurant_detach_init_vfx()
{
	flag_wait( "restaurant_drop_section_falling" );
	
	wait 0.25;
	exploder("10050");//falling rock and dust, x2
	
	//need another explosion on the left side where the ceiling marble bends
}

restaurant_first_section_env_vfx()
{
	//env amb vfx triggered after the first section drops
	wait 1.0;
	exploder(15010);
}

restaurant_first_section_falling_vfx()
{
	flag_wait( "restaurant_drop_section_falling" );
	
	data = spawnStruct();
	get_restaurant_collapse_fx("10100",data);
	fire_locs = data.v["origins"];
	fire_angs = data.v["angles"];
	ents = data.v["ents"];
	
	fire_origins = [];
	
	for (i=0; i<fire_locs.size;i++)
	{
		fire_origins[i] = spawn_tag_origin();
		fire_origins[i].origin = fire_locs[i];
		fire_origins[i].angles = fire_angs[i];
		fire_origins[i] linkto(level.fx_dummy,"tag_origin");
	}
	
	for(i=0; i<fire_locs.size;i++)
	{
		PlayFxOnTag( getfx( "db_rest_dest_fire_line_trailing" ), fire_origins[i], "tag_origin" );
	}
	
	wait 2.0;
	
	for(i=0; i<fire_locs.size;i++)
	{
		StopFxOnTag( getfx( "db_rest_dest_fire_line_trailing" ), fire_origins[i], "tag_origin" );
		fire_origins[i] Delete();
	}
}

restaurant_ceilingbeam01_fire_vfx()
{
	flag_wait( "restaurant_drop_section_falling" );
	
	wait 0.75;

	entarray = getentarray( "des_ceilingbeam_fall_01", "script_noteworthy" );
	beam = spawn( "script_origin", (0, 0, 0 ));
				
	foreach ( ent in entarray)
	{
		if (ent.classname == "script_model")
		{
			beam = ent;
			break;
		}
	}
	
	fx_dummy_2 = spawn_tag_origin();	
	fx_dummy_2 linkto (beam);
		
	data = spawnStruct();
	get_restaurant_collapse_fx("10300",data);
	fire_locs = data.v["origins"];
	fire_angs = data.v["angles"];
	ents = data.v["ents"];
	
	fire_origins = [];
	
	for (i=0; i<fire_locs.size;i++)
	{
		fire_origins[i] = spawn_tag_origin();
		fire_origins[i].origin = fire_locs[i];
		fire_origins[i].angles = fire_angs[i];
		fire_origins[i] linkto(fx_dummy_2,"tag_origin");
	}
	
	for(i=0; i<fire_locs.size;i++)
	{
		PlayFxOnTag( getfx( "db_rest_dest_fire_line_trailing" ), fire_origins[i], "tag_origin" );
	}
	
	flag_wait( "restaurant_destruction_floor_done" );
	
	wait 4.0;
	
	for(i=0; i<fire_locs.size;i++)
	{
		StopFxOnTag( getfx( "db_rest_dest_fire_line_trailing" ), fire_origins[i], "tag_origin" );
		fire_origins[i] Delete();
	}
	
	fx_dummy_2 delete();
}

restaurant_ceilingbeam01_pipesteam_vfx()
{
	flag_wait( "restaurant_drop_section_falling" );
	
	wait 0.1;

	entarray = getentarray( "des_ceilingbeam_fall_01", "script_noteworthy" );
	beam1 = spawn( "script_origin", (0, 0, 0 ));
				
	foreach ( ent in entarray)
	{
		if (ent.classname == "script_model")
		{
			beam1 = ent;
			break;
		}
	}
	
	fx_dummy_3 = spawn_tag_origin();	
	fx_dummy_3 linkto (beam1);
		
	data = spawnStruct();
	get_restaurant_collapse_fx("10400",data);
	fire_locs = data.v["origins"];
	fire_angs = data.v["angles"];
	ents = data.v["ents"];
	
	fire_origins = [];
	
	for (i=0; i<fire_locs.size;i++)
	{
		fire_origins[i] = spawn_tag_origin();
		fire_origins[i].origin = fire_locs[i];
		fire_origins[i].angles = fire_angs[i];
		fire_origins[i] linkto(fx_dummy_3,"tag_origin");
	}
	
	for(i=0; i<fire_locs.size;i++)
	{
		PlayFxOnTag( getfx( "pipe_steam_looping" ), fire_origins[i], "tag_origin" );
	}
	
	flag_wait( "restaurant_destruction_floor_done" );
	
	wait 4.0;
	
	for(i=0; i<fire_locs.size;i++)
	{
		StopFxOnTag( getfx( "pipe_steam_looping" ), fire_origins[i], "tag_origin" );
		fire_origins[i] Delete();
	}
	
	fx_dummy_3 delete();
}

restaurant_floor_tilt_ground_fire_vfx()
{
	flag_wait( "restaurant_drop_section_falling" );
	
	wait 0.5;
	
	//iprintlnbold("floor_fall_start"); 
	
	data = spawnStruct();
	get_restaurant_collapse_fx("10200",data);
	fire_locs = data.v["origins"];
	fire_angs = data.v["angles"];
	ents = data.v["ents"];
	
	fire_origins = [];
	
	for (i=0; i<fire_locs.size;i++)
	{
		fire_origins[i] = spawn_tag_origin();
		fire_origins[i].origin = fire_locs[i];
		fire_origins[i].angles = fire_angs[i];
		fire_origins[i] linkto(level.fx_dummy_1,"tag_origin");
	}
	
	for(i=0; i<fire_locs.size;i++)
	{
		PlayFxOnTag( getfx( "db_rest_dest_fire_line_trailing" ), fire_origins[i], "tag_origin" );
	}
	
	flag_wait( "restaurant_destruction_floor_done" );
	
	wait 2.0;
	
	for(i=0; i<fire_locs.size;i++)
	{
		StopFxOnTag( getfx( "db_rest_dest_fire_line_trailing" ), fire_origins[i], "tag_origin" );
		fire_origins[i] Delete();
	}
}

restaurant_ground_smoderling_smk_vfx()
{
	flag_wait( "restaurant_drop_section_falling" );
	
	data = spawnStruct();
	get_restaurant_collapse_fx("10500",data);
	fire_locs = data.v["origins"];
	fire_angs = data.v["angles"];
	ents = data.v["ents"];
	
	fire_origins = [];
	
	for (i=0; i<fire_locs.size;i++)
	{
		fire_origins[i] = spawn_tag_origin();
		fire_origins[i].origin = fire_locs[i];
		fire_origins[i].angles = fire_angs[i];
		fire_origins[i] linkto(level.fx_dummy_4,"tag_origin");
	}
	
	for(i=0; i<fire_locs.size;i++)
	{
		PlayFxOnTag( getfx( "db_rest_dest_smoldering_smk_grnd" ), fire_origins[i], "tag_origin" );
	}
	
	flag_wait( "restaurant_destruction_floor_done" );
	
	wait 5.0;
	
	for(i=0; i<fire_locs.size;i++)
	{
		StopFxOnTag( getfx( "db_rest_dest_smoldering_smk_grnd" ), fire_origins[i], "tag_origin" );
		fire_origins[i] Delete();
	}
}

get_restaurant_collapse_fx(num, data)
{
	org = [];
	ang = [];
	ents = [];
	id = string(num);
	exploders = GetExploders( id );
	
	if (isdefined(exploders))
		{
		foreach (ent in exploders)
			{
				org[(org.size)]=ent.v["origin"];
				ang[(ang.size)]=ent.v["angles"];
				ents[(ents.size)]=ent;
			}
		}	
	data.v["origins"] =  org;
	data.v["angles"] = ang;
	data.v["ents"] = ents;
}	

restaurant_ceilingbar01_ground_impact_vfx()
{
	//iprintlnbold("smack");	(-1030 210 7684)
	exploder(15111); //x2 with offset time and position
	wait (2.65);
	exploder("throw_bottle");
}

restaurant_player_slide_dof()
{
	level endon( "restaurant_player_falling_to_death" );
	
	start = level.dofDefault;	

	far_blur = [];
	far_blur[ "nearStart" ] = 5;
	far_blur[ "nearEnd" ] = 10;
	far_blur[ "nearBlur" ] = 4;
	far_blur[ "farStart" ] = 600;
	far_blur[ "farEnd" ] = 5500;
	far_blur[ "farBlur" ] = 4;	
	
	near_blur = [];
	near_blur[ "nearStart" ] = 20;
	near_blur[ "nearEnd" ] = 140;
	near_blur[ "nearBlur" ] = 8;
	near_blur[ "farStart" ] = 800;
	near_blur[ "farEnd" ] = 5500;
	near_blur[ "farBlur" ] = 1;
	
	//iprintlnbold("near_blur");
	blend_dof( start, near_blur, .3 );
		
	wait(3.0); 
	//iprintlnbold("far_blur");
	blend_dof ( near_blur, far_blur, .2 );
		
	wait(3.1);
	//iprintlnbold("orig");
	blend_dof ( far_blur, start, .8 );

}

restaurant_rolling_debris_vfx()
{
	exploder (10600);
}

restaurant_post_destruction_se_amb_vfx()
{
	exploder (15000);
	//wait 5.0;
	//exploder (15050); //amb vfx during the side path way between the restaurant
}

restaurant_env_vfx_kill()
{
	kill_exploder(15000);
	kill_exploder(15010);
	//kill_exploder(15050);
}

restaurant_ledge_falling_debris_vfx()
{
	exploder (10071);	
}

restaurant_ledge_poolwater_explosion()
{
	// x65 water explosion happening at pool, timing offset in exploder nodes
	exploder (10072);
}

yuri_blood_vfx()
{
	wait(4.0);
	exploder(98);
	playfxontag( getfx( "yuri_blood_body" ), level.yuri, "J_SpineUpper" );	
	wait(1.5);
	playfxontag( getfx( "yuri_blood_4" ), level.yuri, "J_Jaw" );
	wait(1.0);
	playfxontag( getfx( "yuri_blood" ), level.yuri, "J_Jaw" );	
	wait(3.5);
	playfxontag( getfx( "yuri_blood_5" ), level.yuri, "J_Jaw" );	
	wait(5.0);
	playfxontag( getfx( "yuri_blood_2" ), level.yuri, "J_Jaw" );
	wait(1.0);
	playfxontag( getfx( "yuri_blood_3" ), level.yuri, "J_Jaw" );	
	//wait(1.5);
	//playfxontag( getfx( "yuri_blood_3" ), level.yuri, "J_Jaw" );	
	//wait(3.5);
	//playfxontag( getfx( "yuri_blood_3" ), level.yuri, "J_Jaw" );	
	wait(3.0);
	thread start_vista_fx();
	//rooftop vista glow fx
	exploder(6500);
}

/*--------------------------------------------
	RESTAURANT DESTRUCTION SE VFX END
--------------------------------------------*/	

sedan_enable_lights_01()
{
	lobby_sedan_01 = getent("sedan_dest_still_01", "script_noteworthy");
	playfxontag(getfx("car_sedan_headlight_l"),lobby_sedan_01,"tag_light_left_front");
	playfxontag(getfx("car_sedan_headlight_r"),lobby_sedan_01,"tag_light_right_front");
	playfxontag(getfx("car_sedan_taillights_combined_emission"),lobby_sedan_01,"tag_body");
	lobby_sedan_01 waittill("exploded");
	stopfxontag(getfx("car_sedan_headlight_l"),lobby_sedan_01,"tag_light_left_front");
	stopfxontag(getfx("car_sedan_headlight_r"),lobby_sedan_01,"tag_light_right_front");
	stopfxontag(getfx("car_sedan_taillights_combined_emission"),lobby_sedan_01,"tag_body");
}

sedan_enable_lights_02()
{
	lobby_sedan_02 = getent("sedan_dest_still_02", "script_noteworthy");
	playfxontag(getfx("car_sedan_headlight_l"),lobby_sedan_02,"tag_light_left_front");
	playfxontag(getfx("car_sedan_headlight_r"),lobby_sedan_02,"tag_light_right_front");
	playfxontag(getfx("car_sedan_taillights_combined_emission"),lobby_sedan_02,"tag_body");
	lobby_sedan_02 waittill("exploded");
	stopfxontag(getfx("car_sedan_headlight_l"),lobby_sedan_02,"tag_light_left_front");
	stopfxontag(getfx("car_sedan_headlight_r"),lobby_sedan_02,"tag_light_right_front");
	stopfxontag(getfx("car_sedan_taillights_combined_emission"),lobby_sedan_02,"tag_body");
}

suv_enable_lights()
{
	strobetag_l = spawn_tag_origin();
	strobetag_l.origin = self gettagorigin("tag_light_left_front");
	strobetag_l.angles = vectortoangles((0,0,1));
	strobetag_l linkto(self, "tag_headlight_left", (7.5,3,-13.5), (0,0,0));
	
	strobetag_r = spawn_tag_origin();
	strobetag_r.origin = self gettagorigin("tag_light_right_front");
	strobetag_r.angles = vectortoangles((0,0,1));
	strobetag_r linkto(self, "tag_headlight_right", (7.5,-3,-13.5), (0,0,0));
	
	self vehicle_lights_on("combined");
	//self vehicle_lights_on("headlights");
	//self vehicle_lights_on("taillights");
	self vehicle_lights_on("strobelights");
	
	playfxontag(getfx("suburban_strobe_centered_l"),strobetag_r,"tag_origin");
	wait(.35);
	playfxontag(getfx("suburban_strobe_centered_l"),strobetag_l,"tag_origin");
	
	
	
	self waittill("death");
	
	self vehicle_lights_off("combined");
	stopfxontag(getfx("suburban_strobe_centered_l"),strobetag_r,"tag_origin");
	stopfxontag(getfx("suburban_strobe_centered_l"),strobetag_l,"tag_origin");
	
	//self vehicle_lights_off("headlights");

	//self vehicle_lights_off("taillights");

	self vehicle_lights_off("strobelights");
}

topfloor_environmentfx_start()
{
	//exploder(5001);
}

topfloor_environmentfx_stop()
{
	//kill_exploder(5001);
}


roof_environmentfx_start()
{
	exploder(7000);
}

roof_environmentfx_stop()
{
	kill_exploder(7000);
}

restaurant_rubblefx_start()
{
	exploder(11000);
}

restaurant_rubblefx_stop()
{
	kill_exploder(11000);
}

heli_environmentfx_start()
{
	exploder(7500);
}

heli_environmentfx_stop()
{
	kill_exploder(7500);
}


finale_environmentfx_start()
{
	exploder(5002);
}

finale2_environmentfx_start()
{
	wait(15.0);
	exploder(5003);
}


treadfx_override()
{
	wait(0.025);
	

	//sedan tread fx
	//fx = "treadfx/tread_dust_paris_small";
	//fx = "treadfx/tread_road_sniperescape";
	fx = "treadfx/tread_road_dubai";
	no_fx = "misc/no_effect";
	vehicletype_fx[0] = "script_vehicle_suburban";
	

	foreach(vehicletype in vehicletype_fx)
	{
		maps\_treadfx::setvehiclefx( vehicletype, "brick", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "bark", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "carpet", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "cloth", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "concrete", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "dirt", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "flesh", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "foliage", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "glass", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "grass", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "gravel", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "ice", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "metal", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "mud", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "paper", fx );
	  maps\_treadfx::setvehiclefx( vehicletype, "plaster", no_fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "rock", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "sand", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "snow", fx );
	 	//maps\_treadfx::setvehiclefx( vehicletype, "water", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "wood", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "asphalt", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "ceramic", no_fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "plastic", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "rubber", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "cushion", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "fruit", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "paintedmetal", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "riotshield", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "slush", fx );
	 	maps\_treadfx::setvehiclefx( vehicletype, "default", fx );
		maps\_treadfx::setvehiclefx( vehicletype, "none" );
	}
	
}


/*--------------------------------------------
	FINALE VFX 
--------------------------------------------*/

// light for helicopter cockpit
setup_helicopter_finale_light()
{
	waitframe();
	PlayFXOnTag( getfx( "dubai_helicopter_console_light" ), level.finale_chopper, "plane_dial_01" );
}	

// light for helicopter cockpit
kill_helicopter_finale_light()
{
	wait(1.0);
	stopfxontag(getfx("dubai_helicopter_console_light"),level.finale_chopper,"plane_dial_01");
	PlayFXOnTag(getfx("dubai_helicopter_console_light_2"),level.finale_chopper,"plane_dial_01");
}	
	


 finale_mysterious_stranger_shadow( fx_name, joint, time )
{
	//attach a volume shadow to makarov's head, torso and left_leg
	shadow_tag = spawn_tag_origin();
	shadow_tag.origin = self gettagorigin( joint );
	f_time = 20 * time;
	playfxontag( getfx(fx_name), shadow_tag, "tag_origin" );
	for( i=0; i < f_time; i++ )
	{
		shadow_tag.origin = self gettagorigin( joint );
		level waitframe();
	}
	stopfxontag( getfx(fx_name), shadow_tag, "tag_origin" );
}



finale_mysterious_stranger_shadow_start()
{
	self thread  finale_mysterious_stranger_shadow("db_body_shadow2","j_spine4",60.0);
	self thread  finale_mysterious_stranger_shadow("db_head_shadow2","j_head",60.0);
	self thread  finale_mysterious_stranger_shadow("db_leg_shadow2","j_hip_le",60.0);
	
}

	
//light for main fire key light at crashsite	
setup_rooftop_searchlight_key()
{
	light = GetEnt( "rooftop_searchlight_key", "targetname" );
	light setLightColor( ( 1.20, 1.0, 0.76 ) );	
	light thread maps\_lights::flickerLight( ( 1.20, 1.0, 0.76 ), ( .3, 0.26, 0.18 ), .005, .15 );
	light setLightIntensity( 2.5 );
	light SetLightRadius( 390 );
	light SetLightFovRange( 95, 90 );
}

// light for rim on stranger after credits
setup_mysterious_stranger_rimlight()
{
	flag_wait( "end_of_credits");
	light = GetEnt( "mysterious_stranger_rimlight", "targetname" );
	light setLightIntensity( 8.0 );	
	light SetLightFovRange( 35, 15 );
}

// light for rim on hanging mak during finale
setup_atrium_fire_light_key()
{
	light = GetEnt( "atrium_fire_light_key", "targetname" );
	light setLightColor( ( 0.90, 0.7, 0.46 ) );	
	light thread maps\_lights::flickerLight( ( 0.90, 0.7, 0.46 ), ( .5, 0.46, 0.38 ), .005, .15 );
	light setLightIntensity( 2.9 );	
	light SetLightFovRange( 100, 90 );
	light SetLightRadius( 265 );
}

// light for main heli flickering fire
setup_heli_fire_flicker_light()
{
	wait(8.8);
	exploder(20110);
	flag_wait( "beatdown_tackle_start" );
	kill_exploder(20110);
		
}

// light for mak gun attached...highlights gun up close when it's pointed at the player
setup_mak_gun_light()
{
	wait(8.6);
	PlayFXOnTag( getfx( "db_crashsite_gun_light_pickup" ), level.gun, "TAG_FLASH" );
	flag_wait( "beatdown_tackle_start" );
	stopfxontag( getfx( "db_crashsite_gun_light_pickup" ), level.gun, "TAG_FLASH" );
	
}

setup_mak_gun_light_fail()
{
	PlayFXOnTag( getfx( "db_crashsite_gun_light_pickup" ), level.gun, "TAG_FLASH" );
	
}

// light for mak gun to highlight gun at a distance for gameplay
setup_mak_gun_distant_light()
{
	exploder(20222);
	flag_wait( "player_started_draw" );
	kill_exploder(20222);
		
}

// lowered spec vision set and lowered light for fall through glass
setup_glass_fall_lighting()
{
	thread vision_set_fog_changes("dubai_cigar_nospec",3.5);
	wait(4.0);
	thread vision_set_fog_changes("dubai_cigar",3.5);
}

// vision set to turn off bloom during beatdown sequence
turn_off_bloom_beatdown()
{
	flag_wait( "beatdown_tackle_start" );
	thread vision_set_fog_changes("dubai_fall_nobloom",3.5);
}

heli_fire_vfx()
{
			if ( ( level.Console && level.ps3 ) || !level.Console )
	{
		SetHalfResParticles( true );
	}
	
	PlayFXOnTag( getfx( "heli_fire" ), level.finale_chopper, "footPedalB_L" );
	wait(1.5);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "air_climb_dial_01" );
	wait(1.2);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "wind_speed_dial_01" );
	wait(1.4);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "air_climb_dial_01" );
	wait(1.3);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "wind_speed_dial_01" );
	wait(0.9);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "altimeter_dial_01" );
	wait(1.0);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "plane_dial_01" );
	wait(0.8);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "horizon_dial_01" );
	wait(0.9);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "altimeter_dial_01" );
	wait(0.6);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "plane_dial_01" );
	wait(0.8);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "altimeter_dial_01" );
	wait(0.4);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "horizon_dial_01" );
	wait(0.6);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "air_climb_dial_01" );
	wait(0.3);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "altimeter_dial_01" );
	wait(0.5);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "plane_dial_01" );
	wait(0.4);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "wind_speed_dial_01" );
	wait(0.3);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "plane_dial_01" );
	wait(0.5);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "altimeter_dial_01" );
	wait(0.3);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "horizon_dial_01" );
	wait(0.1);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "wind_speed_dial_01" );
	wait(0.3);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "horizon_dial_01" );
	wait(0.5);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "altimeter_dial_01" );
	wait(0.3);
	PlayFXOnTag( getfx( "heli_sparks" ), level.finale_chopper, "horizon_dial_01" );
	wait(0.1);
	PlayFXOnTag( getfx( "rooftop_heli_crash" ), level.finale_chopper, "horizon_dial_01" );
	wait(3.0);
				if ( ( level.Console && level.ps3 ) || !level.Console )
	{
		SetHalfResParticles( false );
	}
}

 roof_heli_mac_shadow( fx_name, joint, time )
{
	//attach a volume shadow to makarov's head, torso and left_leg
	shadow_tag = spawn_tag_origin();
	shadow_tag.origin = level.makarov gettagorigin( joint );
	f_time = 20 * time;
	playfxontag( getfx(fx_name), shadow_tag, "tag_origin" );
	for( i=0; i < f_time; i++ )
	{
		shadow_tag.origin = level.makarov gettagorigin( joint );
		level waitframe();
	}
	stopfxontag( getfx(fx_name), shadow_tag, "tag_origin" );
}


roof_heli_jumpdof()
{
	//anim starts at 210
	//frame 398 - start far blur
	//frame 415 - far blur complete
	//frame 430 - start focus on city
	//frame 454 - focus on city ends
	//frame 918 - start final blur

	c_frame = 210.00;
	t_frame = 398.00;
	wait((t_frame-c_frame)/30.00);
	c_frame = t_frame;
	
	//start rotor wash
	exploder(21025);
	tag_ent = spawn_tag_origin();
	tag_ent.origin = ( level.player.origin[0], level.player.origin[1], 6625.13);
	tag_ent.angles = ( 270, 0, 0 );
	playfxontag( getfx("db_heli_rooftread"), tag_ent, "tag_origin" );
	//ent = get_exploder(21025);
	for( i=0; i<100; i++ )
	{
		start_pos_z = 6625.13;
		new_pos = ( level.player.origin[0], level.player.origin[1], start_pos_z);
		tag_ent.origin = new_pos;
		level waitframe();
	}
	stopfxontag( getfx("db_heli_rooftread"), tag_ent, "tag_origin" );
	tag_ent delete();
	/*
	start = level.dofDefault;
	curr_org = level.finale_chopper gettagorigin("tag_turret");
	curr_eye = level.player.origin;
	curr_dist = length(curr_org - curr_eye);
	dof_heli_jump = [];
	last_dof = [];
	dof_heli_jump[ "nearStart" ] = 2;
	dof_heli_jump[ "nearEnd" ] = 10;
	dof_heli_jump[ "nearBlur" ] = 10;
	dof_heli_jump[ "farStart" ] = curr_dist+500;
	dof_heli_jump[ "farEnd" ] = curr_dist+2000;
	dof_heli_jump[ "farBlur" ] = 8;
	blend_dof( start, dof_heli_jump, 1 );
	last_dof = dof_heli_jump;
	
	t_frame = 430.00;
	wait((t_frame-c_frame)/30.00);
	c_frame = t_frame;

	curr_org = level.finale_chopper gettagorigin("tag_turret");
	curr_eye = level.player.origin;
	curr_dist = length(curr_org - curr_eye);
	dof_heli_jump[ "farBlur" ] = 0;
	blend_dof( last_dof, dof_heli_jump, 1 );
	last_dof = dof_heli_jump;
	
	t_frame = 918.00;
	wait((t_frame-c_frame)/30.00);
	c_frame = t_frame;

	dof_heli_jump[ "farBlur" ] = .5;
	blend_dof( last_dof, dof_heli_jump, .5 );
	last_dof = dof_heli_jump;


	flag_wait( "finale_chopper_crash_complete" );
	level.player PainVisionOff();
	blend_dof( last_dof, start, .1 );
	*/
	
	


}


roof_heli_blade_fire_think(ent)
{
	dist = 100000;
	for(;;)
	{
		if( dist < 15 )
		{
			playfxontag( getfx("db_blade_fire"),ent,"tag_origin" );
			wait 1.5;
			stopfxontag( getfx("db_blade_fire"),ent,"tag_origin" );
		}
		level waitframe();
		dist = distance( ent.origin, ( 591.584, -262.406, 8179.62 ) );
	}
}

roof_heli_blade_fire_think2(ent)
{
	dist = .5;
	pt1 = ( 613, -232, 8191 );
	pt2 = ( 581.784, -307.321, 8182.8 );
	aim_v = vectornormalize( pt2 - pt1 );
	for(;;)
	{
		if( dist > .8  )
		{
			wait(4.5);
			playfxontag( getfx("db_blade_shadow"),ent,"tag_origin" );
			wait 1.5;
			stopfxontag( getfx("db_blade_shadow"),ent,"tag_origin" );
		}
		level waitframe();
		curr_pos = ent gettagorigin( "tag_origin" );
		test_v = vectornormalize( curr_pos - pt1 );
		dist = vectordot( test_v, aim_v );
		//dist = distance( ent.origin, ( 581.784, -307.321, 8182.8 ) );
	}
}

//Called from maps\dubia_finale::finale_chopper_crash_rotor_spin()
roof_heli_blade_fire()
{
	//self = the heli blade
	fxents = get_exploder_entarray( 20004 );//line fires aligned to the heli blade
	foreach( ent in fxents )
	{
		parent_ent = spawn_tag_origin();
		parent_ent.origin = ent.v[ "origin" ];
		parent_ent.angles = ent.v[ "angles" ];
		parent_ent linkto(self);
		thread roof_heli_blade_fire_think(parent_ent);
	}
	fxents = get_exploder_entarray( 20005 );//line shadows aligned to the heli blade
	foreach( ent in fxents )
	{
		parent_ent = spawn_tag_origin();
		parent_ent.origin = ent.v[ "origin" ];
		parent_ent.angles = ent.v[ "angles" ];
		parent_ent linkto(self);
		thread roof_heli_blade_fire_think2(parent_ent);
	}
}



rooftop_lighting_rig()
{
	rig = self;
	playfxontag( getfx( "dubai_lights_finale_rim1" ), rig, "tag_key" );
	//starts on idle animation
	level waittill( "fx_beatdown_msg" );//msg signals beginning of tackle (beatdown) animation
	level waittill( "fx_beatdown_msg_startchoke" );//msg signals beginning of choke
	level waittill( "fx_beatdown_msg_startslam" );//msg signals beginning of slam
	
	//level waittill( "fx_beatdown_msg_startslam" );//msg signals beginning of slam

	

}


roof_heli_postcrash_fx()
{
	thread makarov_blood_vfx();
  
  // setup lighting scripts for crashsite area
  thread setup_rooftop_searchlight_key();
  thread setup_atrium_fire_light_key();
  thread calc_heli_fire_reflection();
  thread calc_makarov_blob_shadow();
  thread setup_mak_gun_light();
  //thread setup_mak_gun_distant_light();
  thread setup_heli_fire_flicker_light();
  thread vision_set_fog_changes("dubai_fall",0.05);
  thread turn_off_bloom_beatdown();
  
	exploder(20000);
	exploder(20001);
	level waittill("fx_mak_light");
	level waitframe();
	thread roof_heli_mac_shadow("db_body_shadow","j_spine4",33.0);
	level waitframe();
	thread roof_heli_mac_shadow("db_head_shadow","j_head",24.0);
	thread roof_heli_mac_shadow("db_leg_shadow","j_hip_le",24.0);
	fx_head_light = spawn_tag_origin();
	fx_head_light.origin = level.makarov gettagorigin("j_head");
	playfxontag(getfx("db_mak_light"),fx_head_light,"tag_origin");
	recorded_pos = false;
	keep_light_pos = fx_head_light.origin;
	curr_time = 0;
	for(i=0;(i/20.00)<44.00;i++)
	{
		if(!recorded_pos)
		{
			fx_head_light.origin = level.makarov gettagorigin("j_head");
			
		}
		else
		{
			origin_temp = level.makarov gettagorigin("j_head");
			fx_head_light.origin = (origin_temp[0],origin_temp[1],keep_light_pos[2]);
		}
		level waitframe();
		curr_time++;
		if((curr_time/20.00)>22 && !recorded_pos) 
		{
			recorded_pos = true;
			keep_light_pos = fx_head_light.origin;
			//iprintlnbold("set");
		}
		
	}
	stopfxontag(getfx("db_mak_light"),fx_head_light,"tag_origin");
	fx_head_light delete();
	
	level waittill("fx_beatdown_msg");
	kill_exploder(20001);
	exploder(20002);
}

makarov_blood_vfx()
{
	wait(9.0);
	//PlayFXOnTag( getfx( "fire_yuri_limb_3" ), level.makarov, "J_Ankle_RI" );
	//PlayFXOnTag( getfx( "fire_yuri_limb_3" ), level.makarov, "J_Ankle_LE" );
	wait(4.0);
	playfxontag( getfx( "makarov_blood_cough_1" ), level.makarov, "J_Jaw" );
	wait(2.0);
	playfxontag( getfx( "makarov_blood_cough_2" ), level.makarov, "J_Jaw" );
	wait(1.0);
	playfxontag( getfx( "makarov_blood_cough_2" ), level.makarov, "J_Jaw" );
	wait(2.0);
	playfxontag( getfx( "makarov_blood_cough_1" ), level.makarov, "J_Jaw" );
	wait(2.0);
	playfxontag( getfx( "makarov_blood_cough_2" ), level.makarov, "J_Jaw" );
	wait(1.0);
	playfxontag( getfx( "makarov_blood_cough_2" ), level.makarov, "J_Jaw" );
	wait(1.0);
	playfxontag( getfx( "makarov_blood_cough_1" ), level.makarov, "J_Jaw" );
	wait(2.0);
	playfxontag( getfx( "makarov_blood_cough_2" ), level.makarov, "J_Jaw" );
	wait(0.2);
	exploder(101);
}
showdown_vfx()
{
	wait(0.2);
	PlayFXOnTag( getfx( "makarov_blood" ), level.makarov, "J_Clavicle_LE" );
	wait(0.4);
	exploder(99);
	wait(1.5);
	PlayFXOnTag( getfx( "makarov_muzzle_flash" ), level.gun, "TAG_FLASH" );
	wait(0.1);
	PlayFXOnTag( getfx( "yuri_chestshot_blood" ), level.yuri, "J_Shoulder_RI" );
  	wait(0.1);
  	exploder(905);
  	wait(0.6);
	PlayFXOnTag( getfx( "makarov_muzzle_flash" ), level.gun, "TAG_FLASH" );
	wait(0.1);
	PlayFXOnTag( getfx( "yuri_headshot_blood" ), level.yuri, "J_Clavicle_LE" );
  	wait(0.1);
  	exploder(906);
  	wait(0.7);
	PlayFXOnTag( getfx( "makarov_muzzle_flash" ), level.gun, "TAG_FLASH" );
	PlayFXOnTag( getfx( "yuri_headshot_blood" ), level.yuri, "TAG_EYE" );
  	wait(0.1);
  	exploder(907);
}

showdown_yuri_vfx()
{
	wait(0.2);
	PlayFXOnTag( getfx( "yuri_muzzle_flash" ), level.yuri, "TAG_FLASH" );
	wait(0.9);
	PlayFXOnTag( getfx( "yuri_muzzle_flash" ), level.yuri, "TAG_FLASH" );
	wait(0.3);
	PlayFXOnTag( getfx( "yuri_muzzle_flash" ), level.yuri, "TAG_FLASH" );
	wait(0.6);
	PlayFXOnTag( getfx( "yuri_muzzle_flash" ), level.yuri, "TAG_FLASH" );

}

stop_vista_fx()
{
	PauseFXID("vista_traffic_car");
	PauseFXID("vista_traffic_car_2");
	PauseFXID("vista_traffic_car_short");
	PauseFXID("dubai_vista_glow_green");
	PauseFXID("dubai_vista_glow_yellow");
	PauseFXID("dubai_vista_glow_yellow_s");
	PauseFXID("dubai_vista_glow_yellow_s_2");
	PauseFXID("dubai_vista_glow_green_l");
	PauseFXID("dubai_vista_glow_blue");
	PauseFXID("dubai_vista_glow_blue_l");
	PauseFXID("dubai_vista_glow_purple");
	PauseFXID("dubai_vista_glow_red");
	PauseFXID("dubai_vista_glow_red_2");
	PauseFXID("dubai_vista_glow_white");
	PauseFXID("boat_red_glow");
  	PauseFXID("vista_traffic_car_u");
}

start_vista_fx()
{
	RestartFXID("vista_traffic_car");
	RestartFXID("vista_traffic_car_2");
	RestartFXID("vista_traffic_car_short");
	RestartFXID("dubai_vista_glow_green");
	RestartFXID("dubai_vista_glow_yellow");
	RestartFXID("dubai_vista_glow_yellow_s");
	RestartFXID("dubai_vista_glow_yellow_s_2");
	RestartFXID("dubai_vista_glow_green_l");
	RestartFXID("dubai_vista_glow_blue");
	RestartFXID("dubai_vista_glow_blue_l");
	RestartFXID("dubai_vista_glow_purple");
	RestartFXID("dubai_vista_glow_red");
	RestartFXID("dubai_vista_glow_red_2");
	RestartFXID("dubai_vista_glow_white");
	RestartFXID("boat_red_glow");
  	PauseFXID("vista_traffic_car_u");
}

calc_heli_fire_reflection()
{
//	if(level.createfx_enabled) return 0;
	
	helifire = GetExploders( 20010 );
	foreach ( fx in helifire )
	{
		if ( !isdefined( fx ) )
			continue;

		if ( fx.v[ "type" ] != "exploder" )
			continue;

		// make the exploder actually removed the array instead?
		if ( !isdefined( fx.v[ "exploder" ] ) )
			continue;

		fx_origin = fx.v[ "origin" ];
		fx_type = fx.v[ "fxid" ];
		fx thread update_fire_reflections(fx_type,fx_origin);
		
	}
}


update_fire_reflections(fx_type,fx_origin)
{
	//spawn reflect fx and update them every frame
	my_tag = spawn_tag_origin();
	my_tag.origin = fx_origin;
	reflectfx = getFx(fx_type);
	if (isDefined(reflectfx))
		playfxontag(reflectfx, my_tag, "tag_origin");
	fx_distance = 1;
	while (fx_distance < 1500)
	{
		fx_distance = Distance(my_tag.origin, level.player.origin);
		angle_vector = my_tag.origin - (level.player geteye());
		constrained_angle = VectorToAngles(angle_vector);
		my_tag.angles = (-90,constrained_angle[1],0);
		wait 0.05;
	}	
	//if we are too far away, remove fx and go back to manager function that runs less frequently
	stopfxontag(reflectfx, my_tag, "tag_origin");
	my_tag delete();
}

calc_makarov_blob_shadow()
{
	wait 1;
	pt1 = ( 613, -232, 8191 );
	shadowheight = 8104;
	my_tag = spawn_tag_origin();
	my_tag.angles = (270,0,0);
	playfxontag(getfx("blob_shadow_character"), my_tag, "tag_origin");
	while(!flag("stop_makarov_blobshadow"))
	{
		makarov_origin = level.makarov gettagorigin("J_SpineUpper");
		my_tag.origin = (makarov_origin[0], makarov_origin[1], shadowheight);
		aim_v = vectornormalize( makarov_origin - pt1 );
		my_tag.angles = (270,aim_v[1], 0);
		wait 0.05;
	}
	stopfxontag(getfx("blob_shadow_character"), my_tag, "tag_origin");
	my_tag delete();
}

crack_on_reflection_vfx()
{
	wait 3.0;
	player_contents = level.player SetContents( 0 );      // disable collision on player
	MagicBullet( "nosound_magicbullet", ( 889, -79, 8110 ), ( 889, -79, 7900 ) , level.player );
	level.player SetContents( player_contents );          // restore collision on player
	
	wait 1.0;
	exploder(22003);
	wait(2.0);
	exploder(22003);
	wait(4.0);
	exploder(22003);
	
	//wait 6.0;
	player_contents = level.player SetContents( 0 );      // disable collision on player
	MagicBullet( "nosound_magicbullet", ( 887, -81, 8110 ), ( 887, -81, 7900 ) , level.player );
	level.player SetContents( player_contents );          // restore collision on player
	
	/*
	//spawning an additional crack at the center for lighting comparison
	//this needs to be deleted later
	player_contents = level.player SetContents( 0 );      // disable collision on player
	MagicBullet( "nosound_magicbullet", ( 738, 0, 8110 ), ( 738, 0, 7900 ) , level.player );
	level.player SetContents( player_contents );          // restore collision on player
	*/
	
}
