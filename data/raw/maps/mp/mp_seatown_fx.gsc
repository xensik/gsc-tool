main()
{

//ambient fx

//	level._effect[ "sand_storm_light_outside" ]										= loadfx( "weather/sand_storm_mp_dome_exterior" );
//	level._effect[ "sand_storm_light_inside" ]										= loadfx( "weather/sand_storm_mp_dome_interior" );
//	level._effect[ "sand_storm_light_inside_outdoor_only" ]				= loadfx( "weather/sand_storm_mp_dome_interior_outdoor_only" );
//	level._effect[ "sand_spray_detail_runner0x400" ]	 						= loadfx( "dust/sand_spray_detail_runner_0x400" );
//	level._effect[ "sand_spray_detail_runner400x400" ]	 					= loadfx( "dust/sand_spray_detail_runner_400x400" );
	level._effect[ "sand_spray_detail_oriented_runner_mp_dome" ]		= loadfx( "dust/sand_spray_detail_oriented_runner_mp_dome" );
//	level._effect[ "sand_spray_cliff_oriented_runner" ] 					= loadfx( "dust/sand_spray_cliff_oriented_runner" );

//	level._effect[ "hallway_smoke" ]															= loadfx( "smoke/hallway_smoke_light" );
//	level._effect[ "light_shaft_dust_large" ]											= loadfx( "dust/light_shaft_dust_large" );	
//	level._effect[ "room_dust_200_blend" ]												= loadfx( "dust/room_dust_200_blend" );	
	level._effect[ "room_dust_100" ]																= loadfx( "dust/room_dust_100_blend" );	
	level._effect[ "battlefield_smokebank_S_warm" ]									= loadfx( "smoke/battlefield_smokebank_S_warm" );
//	level._effect[ "dust_ceiling_ash_large" ]											= loadfx( "dust/dust_ceiling_ash_large" );
//	level._effect[ "ash_spiral_runner" ]			 										= loadfx( "dust/ash_spiral_runner" );
	level._effect[ "dust_wind_fast_paper" ]													= loadfx( "dust/dust_wind_fast_paper" );
//	level._effect[ "dust_wind_slow_paper" ]												= loadfx( "dust/dust_wind_slow_paper" );
	level._effect[ "trash_spiral_runner" ]													= loadfx( "misc/trash_spiral_runner" );
//	level._effect[ "leaves_spiral_runner" ]												= loadfx( "misc/leaves_spiral_runner" );
//	level._effect[ "dust_ceiling_ash_large_mp_vacant" ]						= loadfx( "dust/dust_ceiling_ash_large_mp_vacant" );
	level._effect[ "room_dust_200_mp_seatown" ]											= loadfx( "dust/room_dust_200_blend_mp_seatown" );	
//	level._effect[ "light_shaft_dust_large_mp_vacant" ]						= loadfx( "dust/light_shaft_dust_large_mp_vacant" );	
//	level._effect[ "light_shaft_dust_large_mp_vacant_sidewall" ] 	= loadfx( "dust/light_shaft_dust_large_mp_vacant_sidewall" );	
	
//	level._effect[ "falling_brick_runner" ]												= loadfx( "misc/falling_brick_runner" );
//	level._effect[ "falling_brick_runner_line_400" ]							= loadfx( "misc/falling_brick_runner_line_400" );
//	level._effect[ "firelp_med_pm" ]					 										= loadfx( "fire/firelp_med_pm_nodistort" );
//	level._effect[ "firelp_small_pm" ]				 										= loadfx( "fire/firelp_small_pm" );
	level._effect[ "ceiling_smoke_seatown" ]												= loadfx( "weather/ceiling_smoke_seatown" );
	level._effect[ "insects_carcass_flies" ] 												= loadfx( "misc/insects_carcass_flies" );
//	level._effect[ "fire_falling_runner_point" ]		  						= loadfx( "fire/fire_falling_runner_point" );
	level._effect[ "spark_fall_runner_mp" ] 			                  = loadfx( "explosions/spark_fall_runner_mp" );
	level._effect[ "seatown_lookout_splash_runner" ] 								= loadfx( "water/seatown_lookout_splash_runner" );
	level._effect[ "seatown_pillar_mist" ] 													= loadfx( "water/seatown_pillar_mist" );
	level._effect[ "palm_leaves" ] 		         											= loadfx( "misc/palm_leaves" );
	level._effect[ "falling_dirt_frequent_runner" ] 								= loadfx( "dust/falling_dirt_frequent_runner" );
//	level._effect[ "sea_mist" ] 																	= loadfx( "water/sea_mist" );	
	level._effect[ "flocking_birds_mp" ] 					    							= loadfx( "misc/flocking_birds_mp" );
	level._effect[ "insects_light_hunted_a_mp" ] 		  							= loadfx( "misc/insects_light_hunted_a_mp" );
	level._effect[ "firelp_small_cheap_mp" ] 		      							= loadfx( "fire/firelp_small_cheap_mp" );
	level._effect[ "car_fire_mp" ] 		                							= loadfx( "fire/car_fire_mp" );
	level._effect[ "bg_smoke_plume" ] 		            							= loadfx( "smoke/bg_smoke_plume" );
	level._effect[ "room_dust_200_blend_seatown_wind_fast" ]							= loadfx( "dust/room_dust_200_blend_seatown_wind_fast" );	
	
/#		
	if ( getdvar( "clientSideEffects", "1" ) != "1" )
		maps\createfx\mp_seatown_fx::main();
#/		

}

