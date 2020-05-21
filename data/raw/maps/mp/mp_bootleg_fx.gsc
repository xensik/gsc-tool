main()
{
	//level._effect[ "test_effect" ]										 //= loadfx( "misc/moth_runner" );
/#
    if ( getdvar( "clientSideEffects", "1" ) != "1" )
        maps\createfx\mp_bootleg_fx::main();
#/

	//ambient fx
	level._effect[ "falling_dirt_frequent_runner" ] 							= loadfx( "dust/falling_dirt_frequent_runner" );
	level._effect[ "dust_wind_fast_paper" ]												= loadfx( "dust/dust_wind_fast_paper" );
	level._effect[ "dust_wind_slow_paper" ]												= loadfx( "dust/dust_wind_slow_paper" );
	level._effect[ "trash_spiral_runner" ]												= loadfx( "misc/trash_spiral_runner" );
  level._effect[ "room_dust_200_mp_vacant_light" ]							= loadfx( "dust/room_dust_200_blend_mp_vacant_light" );	
  level._effect[ "insects_carcass_flies" ] 		      						= loadfx( "misc/insects_carcass_flies" );	
	level._effect[ "spark_fall_runner_mp" ] 		                  = loadfx( "explosions/spark_fall_runner_mp" );
  level._effect[ "embers_prague_light" ]								        = loadfx( "weather/embers_prague_light" );
	level._effect[ "firelp_med_pm" ] 		                          = loadfx( "fire/firelp_med_pm" );
	level._effect[ "firelp_small" ] 		                          = loadfx( "fire/firelp_small" );
	level._effect[ "thin_black_smoke_s_fast" ] 		                = loadfx( "smoke/thin_black_smoke_s_fast" );
	level._effect[ "falling_dirt_frequent_runner" ]               = loadfx( "dust/falling_dirt_frequent_runner" );
	level._effect[ "steam_manhole" ] 		                          = loadfx( "smoke/steam_manhole" );
	level._effect[ "battlefield_smokebank_S_warm_dense" ] 		    = loadfx( "smoke/battlefield_smokebank_S_warm_dense" );
  level._effect[ "bg_smoke_plume" ] 		                        = loadfx( "smoke/bg_smoke_plume" );
	level._effect[ "firelp_med_pm_cheap" ] 		                    = loadfx( "fire/firelp_med_pm_cheap" );
	level._effect[ "car_fire_mp" ] 		                            = loadfx( "fire/car_fire_mp" );
	level._effect[ "firelp_small_cheap_mp" ] 		              		= loadfx( "fire/firelp_small_cheap_mp" );
	level._effect[ "falling_ash_mp" ] 		            					  = loadfx( "misc/falling_ash_mp" );	
	level._effect[ "flocking_birds_mp" ] 													= loadfx( "misc/flocking_birds_mp" );
	level._effect[ "insects_light_hunted_a_mp" ] 		              = loadfx( "misc/insects_light_hunted_a_mp" );
	level._effect[ "rain_mp_bootleg" ]								            = loadfx( "weather/rain_mp_bootleg" );
	level._effect[ "rain_noise_splashes" ]			                  = loadfx( "weather/rain_noise_splashes" );
	level._effect[ "rain_splash_lite_64x64" ]			                = loadfx( "weather/rain_splash_lite_64x64" );
	level._effect[ "water_drips_fat_fast_speed" ]			            = loadfx( "water/water_drips_fat_fast_speed" );
	level._effect[ "bg_smoke_plume" ] 		                        = loadfx( "smoke/bg_smoke_plume" );
	level._effect[ "bootleg_alley_steam" ] 		                    = loadfx( "smoke/bootleg_alley_steam" );
	level._effect[ "palm_leaves" ] 		         				            = loadfx( "misc/palm_leaves" );
	level._effect[ "light_glow_white_lamp" ]		                  = loadfx( "misc/light_glow_white_lamp" );
	level._effect[ "waterfall_drainage_short_london" ]			      = loadfx( "water/waterfall_drainage_short_london" );
	level._effect[ "waterfall_splash_medium_london" ]			        = loadfx( "water/waterfall_splash_medium_london" );
	level._effect[ "drainpipe_mp_bootleg" ]			                  = loadfx( "water/drainpipe_mp_bootleg" );
	

}
