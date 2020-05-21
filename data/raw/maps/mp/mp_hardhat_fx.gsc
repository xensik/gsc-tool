main()
{
	
/#
    if ( getdvar( "clientSideEffects", "1" ) != "1" )
        maps\createfx\mp_hardhat_fx::main();
#/



	level._effect[ "electrical_transformer_spark_runner_loop" ] 	= loadfx( "explosions/electrical_transformer_spark_runner_loop" );
	level._effect[ "large_vehicle_explosion_ir" ] 					= loadfx( "explosions/large_vehicle_explosion_ir" );
	level._effect[ "vehicle_explosion_btr80" ] 						= loadfx( "explosions/vehicle_explosion_btr80" );
	level._effect[ "generator_spark_runner_loop_interchange" ] 		= loadfx( "explosions/generator_spark_runner_loop_interchange" );
	level._effect[ "spark_fall_runner_mp" ] 						= loadfx( "explosions/spark_fall_runner_mp" );


	level._effect[ "falling_dirt_light_1_runner_bravo" ] 			= loadfx( "dust/falling_dirt_light_1_runner_bravo" );
//	level._effect[ "falling_dirt_frequent_runner" ] 				= loadfx( "dust/falling_dirt_frequent_runner" );
//	level._effect[ "dust_wind_fast_paper" ] 						= loadfx( "dust/dust_wind_fast_paper" );
//	level._effect[ "dust_wind_fast_no_paper" ] 						= loadfx( "dust/dust_wind_fast_no_paper" );
//	level._effect[ "dust_wind_slow_paper" ] 						= loadfx( "dust/dust_wind_slow_paper" );
//	level._effect[ "room_dust_200_blend_mp_vacant" ] 				= loadfx( "dust/room_dust_200_blend_mp_vacant" );
//	level._effect[ "room_dust_200_z150_mp" ] 						= loadfx( "dust/room_dust_200_z150_mp" );

	level._effect[ "ash_prague" ] 									= loadfx( "weather/ash_prague" );
	level._effect[ "embers_prague_light" ] 							= loadfx( "weather/embers_prague_light" );
//	level._effect[ "ceiling_smoke_seatown" ] 						= loadfx( "weather/ceiling_smoke_seatown" );
	
//	level._effect[ "steam_manhole" ] 								= loadfx( "smoke/ceiling_smoke_seatown" );
//	level._effect[ "battlefield_smokebank_s_cheap" ] 				= loadfx( "smoke/battlefield_smokebank_s_cheap" );
//	level._effect[ "battlefield_smokebank_S_warm_dense" ] 			= loadfx( "smoke/battlefield_smokebank_S_warm_dense" );
//	level._effect[ "battlefield_smokebank_s_cheap_mp_carbon" ] 		= loadfx( "smoke/battlefield_smokebank_s_cheap_mp_carbon" );
//	level._effect[ "battlefield_smokebank_s_cheap_heavy_mp" ] 		= loadfx( "smoke/battlefield_smokebank_s_cheap_heavy_mp" );
	level._effect[ "bg_smoke_plume_mp" ] 							= loadfx( "smoke/bg_smoke_plume_mp" );
//	level._effect[ "thin_black_smoke_s_fast" ] 						= loadfx( "smoke/thin_black_smoke_s_fast" );
//	level._effect[ "thin_black_smoke_m_mp" ] 						= loadfx( "smoke/thin_black_smoke_m_mp" );
	level._effect[ "white_battle_smoke" ] 							= loadfx( "smoke/white_battle_smoke" );
	level._effect[ "hallway_smoke_light" ] 							= loadfx( "smoke/hallway_smoke_light" );
//	level._effect[ "room_smoke_200" ] 								= loadfx( "smoke/room_smoke_200" );
	level._effect[ "room_smoke_400" ] 								= loadfx( "smoke/room_smoke_400" );
//	level._effect[ "steam_large_vent_rooftop" ] 					= loadfx( "smoke/steam_large_vent_rooftop" );
//	level._effect[ "steam_roof_ac" ] 								= loadfx( "smoke/steam_roof_ac" );
//	level._effect[ "steam_jet_loop_cheap_mp_carbon" ] 				= loadfx( "smoke/steam_jet_loop_cheap_mp_carbon" );
//	level._effect[ "building_hole_smoke_mp" ] 						= loadfx( "smoke/building_hole_smoke_mp" );
//	level._effect[ "bootleg_alley_steam" ] 							= loadfx( "smoke/bootleg_alley_steam" );
//	level._effect[ "chimney_smoke_mp" ] 							= loadfx( "smoke/chimney_smoke_mp" );
//	level._effect[ "chimney_smoke_large_mp" ] 						= loadfx( "smoke/chimney_smoke_large_mp" );
//	level._effect[ "large_battle_smoke_mp" ] 						= loadfx( "smoke/large_battle_smoke_mp" );
//	level._effect[ "mist_drifting_groundfog_lambeth" ] 				= loadfx( "smoke/mist_drifting_groundfog_lambeth" );
//	level._effect[ "mist_drifting_lambeth" ] 						= loadfx( "smoke/mist_drifting_lambeth" );
//	level._effect[ "mist_drifting_sky_lambeth" ] 					= loadfx( "smoke/mist_drifting_sky_lambeth" );
	
	level._effect[ "smoke_plume_grey_01" ] 							= loadfx( "smoke/smoke_plume_grey_01" );
	level._effect[ "smoke_plume_grey_02" ] 							= loadfx( "smoke/smoke_plume_grey_02" );


	level._effect[ "light_glow_white_lamp" ] 						= loadfx( "misc/light_glow_white_lamp" );
	level._effect[ "falling_ash_mp" ] 								= loadfx( "misc/falling_ash_mp" );
	level._effect[ "trash_spiral_runner" ] 							= loadfx( "misc/trash_spiral_runner" );
//	level._effect[ "flocking_birds_mp" ] 							= loadfx( "misc/flocking_birds_mp" );
//	level._effect[ "building_hole_paper_fall_mp" ] 					= loadfx( "misc/building_hole_paper_fall_mp" );
	level._effect[ "antiair_runner_cloudy" ] 						= loadfx( "misc/antiair_runner_cloudy" );

	level._effect[ "insects_carcass_runner" ] 						= loadfx( "misc/insects_carcass_runner" );
	level._effect[ "moth_runner" ] 									= loadfx( "misc/moth_runner" );
//	level._effect[ "insects_light_invasion" ] 						= loadfx( "misc/insects_light_invasion" );
//	level._effect[ "insects_light_hunted_a_mp" ] 					= loadfx( "misc/insects_light_hunted_a_mp" );
//	level._effect[ "insect_trail_runner_icbm" ] 					= loadfx( "misc/insect_trail_runner_icbm" );
//	level._effect[ "insects_dragonfly_runner_a" ] 					= loadfx( "misc/insects_dragonfly_runner_a" );
//	level._effect[ "insects_firefly_a" ] 							= loadfx( "misc/insects_firefly_a" );

//	level._effect[ "firelp_med_pm" ] 								= loadfx( "fire/firelp_med_pm" );
//	level._effect[ "firelp_small" ] 								= loadfx( "fire/firelp_small" );
	level._effect[ "firelp_small_cheap_mp" ] 						= loadfx( "fire/firelp_small_cheap_mp" );
//	level._effect[ "firelp_med_pm_cheap" ] 							= loadfx( "fire/firelp_med_pm_cheap" );

//	level._effect[ "wall_fire_mp" ] 								= loadfx( "fire/wall_fire_mp" );
//	level._effect[ "car_fire_mp" ] 									= loadfx( "fire/car_fire_mp" );
	level._effect[ "car_fire_mp_far" ] 									= loadfx( "fire/car_fire_mp_far" );
//	level._effect[ "after_math_embers" ] 							= loadfx( "fire/after_math_embers" );
//	level._effect[ "fire_wall_50" ] 								= loadfx( "fire/fire_wall_50" );
//	level._effect[ "banner_fire" ] 									= loadfx( "fire/banner_fire" );
//	level._effect[ "window_fire_large" ] 							= loadfx( "fire/window_fire_large" );
//	level._effect[ "building_hole_embers_mp" ] 						= loadfx( "fire/building_hole_embers_mp" );

//	level._effect[ "fire_falling_runner_point_infrequent_mp" ] 		= loadfx( "fire/fire_falling_runner_point_infrequent_mp" );
//	level._effect[ "fire_fallingdebris_cheap_mp" ] 					= loadfx( "fire/fire_fallingdebris_cheap_mp" );
	
//	level._effect[ "dust_cloud_mp_afghan" ] 						= loadfx( "dust/dust_cloud_mp_afghan" );
	level._effect[ "dust_cloud_mp_hardhat" ] 						= loadfx( "dust/dust_cloud_mp_hardhat" );
	level._effect[ "sand_spray_detail_oriented_runner_hardhat" ] 	= loadfx( "dust/sand_spray_detail_oriented_runner_hardhat" );
//	level._effect[ "sand_spray_cliff_oriented_runner_hardhat" ] 	= loadfx( "dust/sand_spray_cliff_oriented_runner_hardhat" );
	level._effect[ "dust_spiral_runner_small" ] 					= loadfx( "dust/dust_spiral_runner_small" );

	level._effect[ "jet_flyby_runner" ] 							= loadfx( "misc/jet_flyby_runner" );
	level._effect[ "building_missilehit_runner" ] 					= loadfx( "explosions/building_missilehit_runner" );



}
