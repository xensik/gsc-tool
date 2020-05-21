main()
{
	
/#
    if ( getdvar( "clientSideEffects", "1" ) != "1" )
        maps\createfx\mp_village_fx::main();
#/

	level._effect[ "heat_haze_mirage" ]				 				= loadfx( "distortion/heat_haze_mirage" );

//	level._effect[ "dust_wind_fast" ]				 				= loadfx( "dust/dust_wind_fast_paper" );
//	level._effect[ "dust_wind_fast_no_paper" ]				 		= loadfx( "dust/dust_wind_fast_no_paper" );
//	level._effect[ "dust_wind_slow" ]				 				= loadfx( "dust/dust_wind_slow_paper" );
	level._effect[ "falling_dirt_area_runner" ] 					= loadfx( "dust/falling_dirt_area_runner" );
//	level._effect[ "falling_dirt_light_1_runner" ] 					= loadfx( "dust/falling_dirt_light_1_runner" );
//	level._effect[ "falling_dirt_light_2_runner" ] 					= loadfx( "dust/falling_dirt_light_2_runner" );
//	level._effect[ "falling_dirt_light_1_runner_bravo" ]			= loadfx( "dust/falling_dirt_light_1_runner_bravo" );
//	level._effect[ "falling_dirt_frequent_runner" ]				 	= loadfx( "dust/falling_dirt_frequent_runner" );
//	level._effect[ "falling_dirt_infrequent_runner" ]				= loadfx( "dust/falling_dirt_infrequent_runner" );
//	level._effect[ "room_dust_200_blend_mp_vacant" ]				= loadfx( "dust/room_dust_200_blend_mp_vacant" );
//	level._effect[ "room_dust_200_z150_mp" ]				 		= loadfx( "dust/room_dust_200_z150_mp" );
//	level._effect[ "dust_cloud_mp_afghan" ]				 			= loadfx( "dust/dust_cloud_mp_afghan" );
//	level._effect[ "dust_cloud_mp_hardhat" ]				 		= loadfx( "dust/dust_cloud_mp_hardhat" );
	level._effect[ "sand_spray_detail_oriented_runner_hardhat" ]	= loadfx( "dust/sand_spray_detail_oriented_runner_hardhat" );
	level._effect[ "sand_spray_cliff_oriented_runner_hardhat" ]		= loadfx( "dust/sand_spray_cliff_oriented_runner_hardhat" );
	level._effect[ "dust_spiral_runner_small" ]				 		= loadfx( "dust/dust_spiral_runner_small" );
	
//	level._effect[ "electrical_transformer_spark_runner_loop" ] 	= loadfx( "explosions/electrical_transformer_spark_runner_loop" );
	
//	level._effect[ "firelp_med_pm_cheap" ]			 				= loadfx( "fire/firelp_med_pm_cheap" );
//	level._effect[ "firelp_small_pm_a_cheap" ]		 				= loadfx( "fire/firelp_small_pm_a_cheap" );
//	level._effect[ "fire_falling_runner_point_infrequent_mp" ]		= loadfx( "fire/fire_falling_runner_point_infrequent_mp" );
//	level._effect[ "fire_fallingdebris_cheap_mp" ]			 		= loadfx( "fire/fire_fallingdebris_cheap_mp" );
	level._effect[ "car_fire_mp" ]		 							= loadfx( "fire/car_fire_mp" );
	level._effect[ "car_fire_mp_far" ]		 						= loadfx( "fire/car_fire_mp_far" );
	
	level._effect[ "trash_spiral_runner" ]				 			= loadfx( "misc/trash_spiral_runner" );
//	level._effect[ "falling_brick_runner_line_400" ] 				= loadfx( "misc/falling_brick_runner_line_400" );
	level._effect[ "birds_takeoff_infrequent_runner" ]				= loadfx( "misc/birds_takeoff_infrequent_runner" );
//	level._effect[ "flocking_birds_mp" ]				 			= loadfx( "misc/flocking_birds_mp" );
//	level._effect[ "light_glow_white_lamp" ]				 		= loadfx( "misc/light_glow_white_lamp" );
//	level._effect[ "leaves_fall_gentlewind_paris" ]				 	= loadfx( "misc/leaves_fall_gentlewind_paris" );
	level._effect[ "leaves_fall_gentlewind_mp_village" ]			= loadfx( "misc/leaves_fall_gentlewind_mp_village" );
	level._effect[ "leaves_fall_gentlewind_mp_village_far" ]		= loadfx( "misc/leaves_fall_gentlewind_mp_village_far" );
	
//	level._effect[ "moth_runner" ] 		 							= loadfx( "misc/moth_runner" );
	level._effect[ "insects_carcass_runner" ] 		 				= loadfx( "misc/insects_carcass_runner" );
//	level._effect[ "insects_light_invasion" ] 		 				= loadfx( "misc/insects_light_invasion" );
	level._effect[ "insects_light_hunted_a_mp" ] 		 			= loadfx( "misc/insects_light_hunted_a_mp" );
	level._effect[ "insect_trail_runner_icbm" ] 		 			= loadfx( "misc/insect_trail_runner_icbm" );
	level._effect[ "insects_dragonfly_runner_a" ] 		 			= loadfx( "misc/insects_dragonfly_runner_a" );
//	level._effect[ "insects_firefly_a" ] 		 					= loadfx( "misc/insects_firefly_a" );

//	level._effect[ "battlefield_smokebank_s_cheap" ] 				= loadfx( "smoke/battlefield_smokebank_s_cheap" );
	level._effect[ "hallway_smoke_light" ]			 				= loadfx( "smoke/hallway_smoke_light" );
//	level._effect[ "room_smoke_200" ] 				 				= loadfx( "smoke/room_smoke_200" );
	level._effect[ "room_smoke_400" ] 				 				= loadfx( "smoke/room_smoke_400" );
//	level._effect[ "smoke_plume_grey_01" ] 							= loadfx( "smoke/smoke_plume_grey_01" );
//	level._effect[ "smoke_plume_grey_02" ] 							= loadfx( "smoke/smoke_plume_grey_02" );
//	level._effect[ "thick_black_smoke_mp" ] 						= loadfx( "smoke/thick_black_smoke_mp" );
	
//	level._effect[ "chimney_smoke_mp" ]			 					= loadfx( "smoke/chimney_smoke_mp" );
//	level._effect[ "chimney_smoke_large_mp" ]			 			= loadfx( "smoke/chimney_smoke_large_mp" );
//	level._effect[ "building_hole_smoke_mp" ]			 			= loadfx( "smoke/building_hole_smoke_mp" );
//	level._effect[ "bootleg_alley_steam" ]			 				= loadfx( "smoke/bootleg_alley_steam" );
//	level._effect[ "steam_manhole" ]			 					= loadfx( "smoke/steam_manhole" );
//	level._effect[ "battlefield_smokebank_s_cheap" ]			 	= loadfx( "smoke/battlefield_smokebank_s_cheap" );
//	level._effect[ "battlefield_smokebank_S_warm_dense" ]			= loadfx( "smoke/battlefield_smokebank_S_warm_dense" );
//	level._effect[ "battlefield_smokebank_s_cheap_mp_carbon" ]		= loadfx( "smoke/battlefield_smokebank_s_cheap_mp_carbon" );
//	level._effect[ "battlefield_smokebank_s_cheap_heavy_mp" ]		= loadfx( "smoke/battlefield_smokebank_s_cheap_heavy_mp" );
//	level._effect[ "bg_smoke_plume_mp" ]			 				= loadfx( "smoke/bg_smoke_plume_mp" );
//	level._effect[ "thin_black_smoke_s_fast" ]			 			= loadfx( "smoke/thin_black_smoke_s_fast" );
//	level._effect[ "thin_black_smoke_m_mp" ]			 			= loadfx( "smoke/thin_black_smoke_m_mp" );

//	level._effect[ "waterfall_mist" ]			 					= loadfx( "water/waterfall_mist" );
	level._effect[ "waterfall_mist_mp_village" ]			 		= loadfx( "water/waterfall_mist_mp_village" );
	level._effect[ "waterfall_mist_ground" ]			 			= loadfx( "water/waterfall_mist_ground" );
//	level._effect[ "waterfall_drainage" ]			 				= loadfx( "water/waterfall_drainage" );
	level._effect[ "waterfall_village_1" ]			 				= loadfx( "water/waterfall_village_1" );
	level._effect[ "waterfall_village_2" ]			 				= loadfx( "water/waterfall_village_2" );
//	level._effect[ "waterfall_village_3" ]			 				= loadfx( "water/waterfall_village_3" );
//	level._effect[ "waterfall_drainage_short" ]			 			= loadfx( "water/waterfall_drainage_short" );
//	level._effect[ "waterfall_drainage_distortion" ]			 	= loadfx( "water/waterfall_drainage_distortion" );
	level._effect[ "waterfall_drainage_splash" ]			 		= loadfx( "water/waterfall_drainage_splash" );
	level._effect[ "waterfall_drainage_splash_mp" ]			 		= loadfx( "water/waterfall_drainage_splash_mp" );
	level._effect[ "waterfall_drainage_splash_large" ]			 	= loadfx( "water/waterfall_drainage_splash_large" );
//	level._effect[ "waterfall_drainage_splash_falling" ]			= loadfx( "water/waterfall_drainage_splash_falling" );
	


}
