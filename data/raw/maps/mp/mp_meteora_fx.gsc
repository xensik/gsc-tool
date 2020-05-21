main()
{
	
//	level._effect[ "sand_spray_detail_oriented_runner_mp_dome" ] 			= loadfx( "dust/sand_spray_detail_oriented_runner_mp_dome" );
	level._effect[ "sand_spray_detail_oriented_runner_mp_meteora" ] 		= loadfx( "dust/sand_spray_detail_oriented_runner_mp_meteora" );
	level._effect[ "sand_spray_detail_oriented_runner_mp_meteora_shadow" ] = loadfx( "dust/sand_spray_detail_oriented_runner_mp_meteora_shadow" );
//	level._effect[ "sewer_pipe_drip" ]                           			= loadfx( "water/sewer_pipe_drip" );
	level._effect[ "insects_carcass_flies" ]                     			= loadfx( "misc/insects_carcass_flies" );
	level._effect[ "insects_light_hunted_a_mp" ]                 			= loadfx( "misc/insects_light_hunted_a_mp" );
	level._effect[ "room_dust_100_blend" ]                       			= loadfx( "dust/room_dust_100_blend" );   
	level._effect[ "battlefield_smokebank_S_warm" ]              			= loadfx( "smoke/battlefield_smokebank_S_warm" );
	level._effect[ "falling_dirt_frequent_runner" ]              			= loadfx( "dust/falling_dirt_frequent_runner" );
	level._effect[ "falling_dirt_frequent_runner_meteora" ]              	= loadfx( "dust/falling_dirt_frequent_runner_meteora" );
	level._effect[ "flocking_birds_mp" ]                         			= loadfx( "misc/flocking_birds_mp" );
	level._effect[ "firelp_small_cheap_mp" ]                     			= loadfx( "fire/firelp_small_cheap_mp" );
//	level._effect[ "car_fire_mp" ]                               			= loadfx( "fire/car_fire_mp" );
//	level._effect[ "leaves_spiral_runner" ]                   	 			= loadfx( "misc/leaves_spiral_runner" );
//	level._effect[ "leaves_ground_gentlewind" ]               	 			= loadfx( "misc/leaves_ground_gentlewind" );
//	level._effect[ "trash_spiral_runner" ]               		 			= loadfx( "misc/trash_spiral_runner" );
//	level._effect[ "room_dust_200_mp_seatown" ]                  			= loadfx( "dust/room_dust_200_blend_mp_seatown" );      
//	level._effect[ "room_dust_200_blend_seatown_wind_fast" ]  	 			= loadfx( "dust/room_dust_200_blend_seatown_wind_fast" );   
	level._effect[ "light_dust_motes_ceiling" ]  	 						= loadfx( "dust/light_dust_motes_ceiling" );   
	
	level._effect[ "waterfall_drainage_splash_small" ] 		                = loadfx( "water/waterfall_drainage_splash_small" );
	level._effect[ "water_fountain_spout" ] 		                		= loadfx( "water/water_fountain_spout" );
	level._effect[ "chimney_smoke_brown" ] 		                			= loadfx( "smoke/chimney_smoke_brown" );
	level._effect[ "fireplace" ] 		                					= loadfx( "fire/fireplace" );
	level._effect[ "fire_falling_runner_point_mp" ] 		            	= loadfx( "fire/fire_falling_runner_point_mp" );
	level._effect[ "embers_small_fire" ] 		            				= loadfx( "fire/embers_small_fire" );
	
//	level._effect["sand_blowing_rooftops"] 									= loadfx("sand/sand_blowing_rooftops");
	
	level._effect["paper_blowing_trash_fast_model"] 						= loadfx("misc/paper_blowing_trash_fast_model");
//	level._effect["sand_medium_mp" ]										= loadfx( "sand/sand_medium_mp" );
//	level._effect["sand_medium_mp_lt" ]										= loadfx( "sand/sand_medium_mp_lt" );
//	level._effect["sand_medium_mp_directional" ]							= loadfx( "sand/sand_medium_mp_directional" );
	level._effect["sand_medium_mp_lt_directional" ]							= loadfx( "sand/sand_medium_mp_lt_directional" );
	
	level._effect[ "leaves_fall_strongwind_green" ]           	 			= loadfx( "misc/leaves_fall_strongwind_green" );
	level._effect[ "leaves_fall_strongwind_pine" ]           	 			= loadfx( "misc/leaves_fall_strongwind_pine" );
	level._effect[ "leaves_fall_strongwind_brown" ]           	 			= loadfx( "misc/leaves_fall_strongwind_brown" );
	level._effect[ "leaves_fall_strongwind_yellow" ]           	 			= loadfx( "misc/leaves_fall_strongwind_yellow" );
	level._effect[ "leaves_fall_strongwind_large" ]           	 			= loadfx( "misc/leaves_fall_strongwind_large" );
	level._effect[ "leaves_fall_strongwind_green_meteora" ]      			= loadfx( "misc/leaves_fall_strongwind_green_meteora" );


/#
    if ( getdvar( "clientSideEffects", "1" ) != "1" )
        maps\createfx\mp_meteora_fx::main();
#/

}
