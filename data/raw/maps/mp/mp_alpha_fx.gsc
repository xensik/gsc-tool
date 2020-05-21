main()
{
	//level._effect[ "test_effect" ]										 = loadfx( "misc/moth_runner" );
/#
    if ( getdvar( "clientSideEffects", "1" ) != "1" )
        maps\createfx\mp_alpha_fx::main();
#/
//ambient fx
	level._effect[ "falling_dirt_frequent_runner" ]     = loadfx( "dust/falling_dirt_frequent_runner" );
	level._effect[ "dust_wind_fast_paper" ]						  = loadfx( "dust/dust_wind_fast_paper" );
	level._effect[ "dust_wind_slow_paper" ]						  = loadfx( "dust/dust_wind_slow_paper" );
	level._effect[ "trash_spiral_runner" ]						  = loadfx( "misc/trash_spiral_runner" );
  level._effect[ "room_dust_200_mp_vacant" ]					= loadfx( "dust/room_dust_200_blend_mp_vacant" );	
  level._effect[ "insects_carcass_flies" ] 		            = loadfx( "misc/insects_carcass_flies" );	
	level._effect[ "spark_fall_runner_mp" ] 		            = loadfx( "explosions/spark_fall_runner_mp" );
  level._effect[ "ash_prague" ]								                  = loadfx( "weather/ash_prague" );
  level._effect[ "embers_prague_light" ]								        = loadfx( "weather/embers_prague_light" );
	level._effect[ "firelp_med_pm" ] 		                          = loadfx( "fire/firelp_med_pm" );
	level._effect[ "firelp_small" ] 		                          = loadfx( "fire/firelp_small" );
	level._effect[ "thin_black_smoke_s_fast" ] 		                = loadfx( "smoke/thin_black_smoke_s_fast" );
	level._effect[ "falling_dirt_frequent_runner" ]               = loadfx( "dust/falling_dirt_frequent_runner" );
	level._effect[ "steam_manhole" ] 		                          = loadfx( "smoke/steam_manhole" );
	level._effect[ "battlefield_smokebank_S_warm_dense" ] 		    = loadfx( "smoke/battlefield_smokebank_S_warm_dense" );
  level._effect[ "bg_smoke_plume" ] 		                        = loadfx( "smoke/bg_smoke_plume" );
	level._effect[ "firelp_med_pm_cheap" ] 		                    = loadfx( "fire/firelp_med_pm_cheap" );
	level._effect[ "banner_fire" ] 		                            = loadfx( "fire/banner_fire" );
	level._effect[ "light_glow_white_lamp" ]		                  = loadfx( "misc/light_glow_white_lamp" );
	level._effect[ "fire_wall_50" ] 		                          = loadfx( "fire/fire_wall_50" );
	level._effect[ "white_battle_smoke" ] 		                    = loadfx( "smoke/white_battle_smoke" );
	level._effect[ "after_math_embers" ] 		                      = loadfx( "fire/after_math_embers" );
	level._effect[ "wall_fire_mp" ] 		                          = loadfx( "fire/wall_fire_mp" );
	level._effect[ "car_fire_mp" ] 		                            = loadfx( "fire/car_fire_mp" );
	level._effect[ "firelp_small_cheap_mp" ] 		                  = loadfx( "fire/firelp_small_cheap_mp" );
	level._effect[ "falling_ash_mp" ] 		                        = loadfx( "misc/falling_ash_mp" );


}
