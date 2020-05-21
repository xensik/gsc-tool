main()
{
	level._effect[ "test_effect" ]										 = loadfx( "misc/moth_runner" );
/#
    if ( getdvar( "clientSideEffects", "1" ) != "1" )
        maps\createfx\mp_carbon_fx::main();
#/

//	level._effect[ "firelp_med_pm_cheap" ]			 				= loadfx( "fire/firelp_med_pm_cheap" );
//	level._effect[ "firelp_small_pm_a_cheap" ]		 				= loadfx( "fire/firelp_small_pm_a_cheap" );
	level._effect[ "dust_wind_fast" ]				 				= loadfx( "dust/dust_wind_fast_paper" );
	level._effect[ "dust_wind_fast_no_paper" ]				 		= loadfx( "dust/dust_wind_fast_no_paper" );
	level._effect[ "dust_wind_slow" ]				 				= loadfx( "dust/dust_wind_slow_paper" );
	level._effect[ "dust_wind_spiral" ]				 				= loadfx( "misc/trash_spiral_runner" );
	level._effect[ "battlefield_smokebank_s_cheap_mp_carbon" ] 		= loadfx( "smoke/battlefield_smokebank_s_cheap_mp_carbon" );
	level._effect[ "hallway_smoke_light" ]			 				= loadfx( "smoke/hallway_smoke_light" );
//	level._effect[ "falling_brick_runner_line_400" ] 				= loadfx( "misc/falling_brick_runner_line_400" );
	level._effect[ "room_smoke_200" ] 				 				= loadfx( "smoke/room_smoke_200" );
	level._effect[ "room_smoke_400" ] 				 				= loadfx( "smoke/room_smoke_400" );
//	level._effect[ "insects_carcass_runner" ] 		 				= loadfx( "misc/insects_carcass_runner" );
//	level._effect[ "electrical_transformer_spark_runner_loop" ] 	= loadfx( "explosions/electrical_transformer_spark_runner_loop" );
	level._effect[ "electrical_transformer_falling_fire_runner" ] 	= loadfx( "explosions/electrical_transformer_falling_fire_runner" );
//	level._effect[ "smoke_plume_grey_01" ] 							= loadfx( "smoke/smoke_plume_grey_01" );
//	level._effect[ "smoke_plume_grey_02" ] 							= loadfx( "smoke/smoke_plume_grey_02" );
//	level._effect[ "thick_black_smoke_mp" ] 						= loadfx( "smoke/thick_black_smoke_mp" );
//	level._effect[ "falling_dirt_light_1_runner" ] 					= loadfx( "dust/falling_dirt_light_1_runner" );
//	level._effect[ "falling_dirt_light_2_runner" ] 					= loadfx( "dust/falling_dirt_light_2_runner" );
	
	level._effect[ "car_fire_mp" ]			 						= loadfx( "fire/car_fire_mp" );
	level._effect[ "firelp_small_cheap_mp" ]			 			= loadfx( "fire/firelp_small_cheap_mp" );
//	level._effect[ "fire_falling_runner_point_infrequent_mp" ]		= loadfx( "fire/fire_falling_runner_point_infrequent_mp" );
//	level._effect[ "fire_fallingdebris_cheap_mp" ]			 		= loadfx( "fire/fire_fallingdebris_cheap_mp" );
//	level._effect[ "wall_fire_mp" ]			 						= loadfx( "fire/wall_fire_mp" );


//	level._effect[ "smoke_plume01" ] 								= loadfx( "smoke/smoke_plume01" );
//	level._effect[ "smoke_plume02" ] 								= loadfx( "smoke/smoke_plume02" );
	level._effect[ "smoke_plume_grey_01" ] 							= loadfx( "smoke/smoke_plume_grey_01" );
	level._effect[ "smoke_plume_grey_02" ] 							= loadfx( "smoke/smoke_plume_grey_02" );
	level._effect[ "smoke_plume_white_01" ] 						= loadfx( "smoke/smoke_plume_white_01" );
	level._effect[ "smoke_plume_white_02" ] 						= loadfx( "smoke/smoke_plume_white_02" );
	
	level._effect[ "steam_large_vent_rooftop" ] 					= loadfx( "smoke/steam_large_vent_rooftop" );
	level._effect[ "steam_manhole" ] 								= loadfx( "smoke/steam_manhole" );
	level._effect[ "steam_roof_ac" ] 								= loadfx( "smoke/steam_roof_ac" );

	level._effect[ "flame_refinery_far" ] 							= loadfx( "fire/flame_refinery_far" );
	level._effect[ "flame_refinery_small_far" ] 					= loadfx( "fire/flame_refinery_small_far" );
	level._effect[ "flame_refinery_small_far_2" ] 					= loadfx( "fire/flame_refinery_small_far_2" );
	level._effect[ "flame_refinery_small_far_3" ] 					= loadfx( "fire/flame_refinery_small_far_3" );
	level._effect[ "steam_cs_mp_carbon" ] 							= loadfx( "smoke/steam_cs_mp_carbon" );
	level._effect[ "steam_jet_loop_cheap_mp_carbon" ] 				= loadfx( "smoke/steam_jet_loop_cheap_mp_carbon" );
	level._effect[ "dust_wind_fast_no_paper_airiel" ] 				= loadfx( "dust/dust_wind_fast_no_paper_airiel" );
	level._effect[ "water_drips_fat_fast_singlestream_mp_carbon" ] 	= loadfx( "water/water_drips_fat_fast_singlestream_mp_carbon" );
	level._effect[ "bootleg_alley_steam" ] 							= loadfx( "smoke/bootleg_alley_steam" );


}
