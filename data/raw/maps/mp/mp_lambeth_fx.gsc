main()
{

/#
    if ( getdvar( "clientSideEffects", "1" ) != "1" )
        maps\createfx\mp_lambeth_fx::main();
#/


//	level._effect[ "dust_wind_fast" ]				 				= loadfx( "dust/dust_wind_fast_paper" );
//	level._effect[ "dust_wind_fast_no_paper" ]				 		= loadfx( "dust/dust_wind_fast_no_paper" );
//	level._effect[ "dust_wind_fast_no_paper_airiel" ] 				= loadfx( "dust/dust_wind_fast_no_paper_airiel" );
	level._effect[ "falling_dirt_infrequent_runner" ] 				= loadfx( "dust/falling_dirt_infrequent_runner" );
		
//	level._effect[ "electrical_transformer_falling_fire_runner" ] 	= loadfx( "explosions/electrical_transformer_falling_fire_runner" );
//	level._effect[ "electrical_transformer_spark_runner_tight" ] 	= loadfx( "explosions/electrical_transformer_spark_runner_tight" );
	
	level._effect[ "car_fire_mp" ]			 						= loadfx( "fire/car_fire_mp" );
	level._effect[ "firelp_small_cheap_mp" ]			 			= loadfx( "fire/firelp_small_cheap_mp" );
	level._effect[ "firelp_small_cheap_dist_mp" ]			 		= loadfx( "fire/firelp_small_cheap_dist_mp" );
	level._effect[ "firelp_med_cheap_dist_mp" ]			 			= loadfx( "fire/firelp_med_cheap_dist_mp" );
	level._effect[ "fire_falling_runner_point_infrequent_mp" ]		= loadfx( "fire/fire_falling_runner_point_infrequent_mp" );		
//	level._effect[ "fire_fallingdebris_cheap_mp" ]			 		= loadfx( "fire/fire_fallingdebris_cheap_mp" );	
//	level._effect[ "wall_fire_mp" ]			 						= loadfx( "fire/wall_fire_mp" );

	
	level._effect[ "dust_wind_spiral" ]				 				= loadfx( "misc/trash_spiral_runner" );
//	level._effect[ "falling_brick_runner_line_75" ] 				= loadfx( "misc/falling_brick_runner_line_75" );
	level._effect[ "falling_brick_runner_line_100" ] 				= loadfx( "misc/falling_brick_runner_line_100" );
	level._effect[ "falling_brick_runner_line_200" ] 				= loadfx( "misc/falling_brick_runner_line_200" );
	level._effect[ "falling_brick_runner_line_300" ] 				= loadfx( "misc/falling_brick_runner_line_300" );
	level._effect[ "falling_brick_runner_line_400" ] 				= loadfx( "misc/falling_brick_runner_line_400" );
	level._effect[ "falling_brick_runner_line_600" ] 				= loadfx( "misc/falling_brick_runner_line_600" );
	
	level._effect[ "insects_carcass_runner" ] 		 				= loadfx( "misc/insects_carcass_runner" );
	level._effect[ "insect_trail_runner_icbm" ] 		 			= loadfx( "misc/insect_trail_runner_icbm" );
	level._effect[ "insects_dragonfly_runner_a" ] 		 			= loadfx( "misc/insects_dragonfly_runner_a" );
//	level._effect[ "insects_firefly_a" ] 		 					= loadfx( "misc/insects_firefly_a" );
	level._effect[ "insects_light_complex" ] 		 				= loadfx( "misc/insects_light_complex" );
	
	level._effect[ "leaves_fall_gentlewind_lambeth" ]				 = loadfx( "misc/leaves_fall_gentlewind_lambeth" );
	level._effect[ "falling_ash_mp" ]				 				= loadfx( "misc/falling_ash_mp" );
//	level._effect[ "generic_fallingdebris" ]				 		= loadfx( "misc/generic_fallingdebris" );
//	level._effect[ "leaves_fall_gentlewind" ]				 		= loadfx( "misc/leaves_fall_gentlewind" );
//	level._effect[ "leaves_fall_gentlewind_far" ]				 	= loadfx( "misc/leaves_fall_gentlewind_far" );
	level._effect[ "leaves_spiral_runner" ]				 			= loadfx( "misc/leaves_spiral_runner" );
	
	level._effect[ "battlefield_smokebank_s_cheap_mp_carbon" ] 		= loadfx( "smoke/battlefield_smokebank_s_cheap_mp_carbon" );
	level._effect[ "battlefield_smokebank_s_cheap_heavy_mp" ] 		= loadfx( "smoke/battlefield_smokebank_s_cheap_heavy_mp" );
	level._effect[ "hallway_smoke_light" ]			 				= loadfx( "smoke/hallway_smoke_light" );
	level._effect[ "room_smoke_200" ] 				 				= loadfx( "smoke/room_smoke_200" );
	level._effect[ "room_smoke_400" ] 				 				= loadfx( "smoke/room_smoke_400" );
//	level._effect[ "steam_large_vent_rooftop" ] 					= loadfx( "smoke/steam_large_vent_rooftop" );
//	level._effect[ "steam_manhole" ] 								= loadfx( "smoke/steam_manhole" );
	level._effect[ "steam_roof_ac" ] 								= loadfx( "smoke/steam_roof_ac" );
	level._effect[ "steam_jet_loop_cheap_mp_carbon" ] 				= loadfx( "smoke/steam_jet_loop_cheap_mp_carbon" );
	level._effect[ "thin_black_smoke_m_mp" ] 				 		= loadfx( "smoke/thin_black_smoke_m_mp" );
//	level._effect[ "large_battle_smoke_mp" ] 						= loadfx( "smoke/large_battle_smoke_mp" );
	level._effect[ "mist_drifting_groundfog_lambeth" ] 				= loadfx( "smoke/mist_drifting_groundfog_lambeth" );
	level._effect[ "mist_drifting_lambeth" ] 						= loadfx( "smoke/mist_drifting_lambeth" );
//	level._effect[ "mist_drifting_sky_lambeth" ] 					= loadfx( "smoke/mist_drifting_sky_lambeth" );
	
	
	level._effect[ "water_drips_fat_fast_singlestream_mp_carbon" ] 	= loadfx( "water/water_drips_fat_fast_singlestream_mp_carbon" );
	
	level._effect[ "ceiling_smoke" ] 								= loadfx( "weather/ceiling_smoke" );
	
	
}
