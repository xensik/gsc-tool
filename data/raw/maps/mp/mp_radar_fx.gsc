main()
{
	level._effect[ "test_effect" ]										 = loadfx( "misc/moth_runner" );
/#
    if ( getdvar( "clientSideEffects", "1" ) != "1" )
        maps\createfx\mp_radar_fx::main();
#/


	//Ambient fx
	level._effect[ "tree_snow_dump_fast" ]							          = loadfx( "snow/tree_snow_dump_fast" );
	level._effect[ "tree_snow_dump_fast_small" ]					        = loadfx( "snow/tree_snow_dump_fast_small" );
	level._effect[ "tree_snow_fallen_heavy" ]						          = loadfx( "snow/tree_snow_fallen_heavy" );
	level._effect[ "tree_snow_fallen" ]								            = loadfx( "snow/tree_snow_fallen" );
	level._effect[ "tree_snow_fallen_small" ]						          = loadfx( "snow/tree_snow_fallen_small" );
	level._effect[ "tree_snow_dump_runner" ]						          = loadfx( "snow/tree_snow_dump_runner" );
	level._effect[ "snow_spray_detail_contingency_runner_0x400" ]	= loadfx( "snow/snow_spray_detail_contingency_runner_0x400" );
	level._effect[ "snow_spray_detail_oriented_runner_0x400" ]		= loadfx( "snow/snow_spray_detail_oriented_runner_0x400" );
	level._effect[ "snow_spray_detail_oriented_runner_400x400" ]	= loadfx( "snow/snow_spray_detail_oriented_runner_400x400" );
	level._effect[ "snow_spray_detail_oriented_runner" ]			    = loadfx( "snow/snow_spray_detail_oriented_runner" );
	level._effect[ "snow_spray_detail_oriented_runner_large" ]		= loadfx( "snow/snow_spray_detail_oriented_large_runner" );
	level._effect[ "snow_spray_large_oriented_radar_od_runner" ]		= loadfx( "snow/snow_spray_large_oriented_radar_od_runner" );	
	level._effect[ "snow_spray_large_oriented_runner" ]				    = loadfx( "snow/snow_spray_large_oriented_runner" );
	level._effect[ "snow_vortex_runner_cheap" ]						        = loadfx( "snow/snow_vortex_runner_cheap" );
	level._effect[ "room_smoke_200" ] 								= loadfx( "smoke/room_smoke_200" );
	level._effect[ "snow_spiral_runner" ]		          = loadfx( "snow/snow_spiral_runner" );
	level._effect[ "snow_blowoff_ledge_runner" ]		  = loadfx( "snow/snow_blowoff_ledge_runner" );
	level._effect[ "snow_clifftop_runner" ]		        = loadfx( "snow/snow_clifftop_runner" );
	level._effect[ "radar_windy_snow" ]		            = loadfx( "snow/radar_windy_snow" );
	level._effect[ "blowing_ground_snow" ]		        = loadfx( "snow/blowing_ground_snow" );
	level._effect[ "tree_snow_dump_radar_runner" ]		= loadfx( "snow/tree_snow_dump_radar_runner" );
	level._effect[ "water_drips_fat_slow_speed" ]		  = loadfx( "water/water_drips_fat_slow_speed" );
	level._effect[ "snow_blizzard_radar" ]		        = loadfx( "snow/snow_blizzard_radar" );
	level._effect[ "light_glow_white_lamp" ]		      = loadfx( "misc/light_glow_white_lamp" );
	level._effect[ "snow_gust_runner_radar" ]		      = loadfx( "snow/snow_gust_runner_radar" );
	level._effect[ "heat_lamp_distortion" ]		        = loadfx( "fire/heat_lamp_distortion" );
  level._effect[ "car_fire_mp" ] 		                = loadfx( "fire/car_fire_mp" );
	level._effect[ "firelp_cheap_mp" ] 		            = loadfx( "fire/firelp_cheap_mp" );	
	level._effect[ "radar_windy_snow_no_mist" ]		    = loadfx( "snow/radar_windy_snow_no_mist" );	
	level._effect[ "radar_windy_snow_small_area" ]		= loadfx( "snow/radar_windy_snow_small_area" );		
	
	
	
}
