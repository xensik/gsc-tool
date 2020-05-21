main()
{
  level._effect[ "water_bubbles" ]		                                           = loadfx( "water/bubble_trail01" );
	level._effect[ "water_wake" ]			                                             = loadfx( "water/player_water_wake" );
	level._effect[ "water_splash_emerge" ]	                                       = loadfx( "water/zodiac_splash_bounce_small" );
	level._effect[ "water_splash_enter" ]	                                         = loadfx( "water/body_splash" );
	level._effect[ "grand_piano_exp" ]		                                         = loadfx( "props/grand_piano_exp" );
	level._effect[ "sand_spray_detail_oriented_runner_mp_meteora" ] 		           = loadfx( "dust/sand_spray_detail_oriented_runner_mp_meteora" );
	level._effect[ "sand_spray_detail_oriented_runner_mp_meteora_shadow" ]         = loadfx( "dust/sand_spray_detail_oriented_runner_mp_meteora_shadow" );
  level._effect[ "insects_carcass_flies" ]                     			             = loadfx( "misc/insects_carcass_flies" );
	level._effect[ "insects_light_hunted_a_mp" ]                 			             = loadfx( "misc/insects_light_hunted_a_mp" );
  level._effect[ "flocking_birds_mp" ]                         			             = loadfx( "misc/flocking_birds_mp" );
	level._effect[ "firelp_small_cheap_mp" ]                     			             = loadfx( "fire/firelp_small_cheap_mp" );
	level._effect[ "car_fire_mp" ]                               		               = loadfx( "fire/car_fire_mp" );
  level._effect[ "light_dust_motes_ceiling_hs" ]  	 						                 = loadfx( "dust/light_dust_motes_ceiling_hs" );   
	level._effect[ "light_dust_motes_light_hs" ]  	 						                   = loadfx( "dust/light_dust_motes_light_hs" );	
  level._effect[ "fireplace" ] 		                					                     = loadfx( "fire/fireplace" );
	level._effect[ "fire_falling_runner_point_mp" ] 		            	             = loadfx( "fire/fire_falling_runner_point_mp" );
	level._effect[ "embers_small_fire" ] 		            				                   = loadfx( "fire/embers_small_fire" );
	level._effect["sand_medium_mp" ]										                           = loadfx( "sand/sand_medium_mp" );
	level._effect["sand_medium_mp_lt" ]										                         = loadfx( "sand/sand_medium_mp_lt" );
	level._effect["sand_medium_mp_directional" ]							                     = loadfx( "sand/sand_medium_mp_directional" );
	level._effect["sand_medium_mp_lt_directional" ]							                   = loadfx( "sand/sand_medium_mp_lt_directional" );
	level._effect[ "leaves_fall_strongwind_green_meteora" ]      			             = loadfx( "misc/leaves_fall_strongwind_green_meteora" );
  level._effect[ "birds_takeof_runner" ]                         			           = loadfx( "misc/birds_takeof_runner" );	
  level._effect[ "fireplace_smoulder" ] 		                			               = loadfx( "smoke/fireplace_smoulder" );
  level._effect[ "palm_leaves_hs" ]                         			               = loadfx( "misc/palm_leaves_hs" ); 
  level._effect[ "fireplace_smoulder_sm" ] 		                			             = loadfx( "smoke/fireplace_smoulder_sm" );  
  level._effect[ "bird_flock_large_hillside" ]                         			     = loadfx( "animals/bird_flock_large_hillside" );
  
   level._effect[ "foliage_dub_potted_palm_01" ]                         			     = loadfx( "props/foliage_dub_potted_palm_01" );
   level._effect[ "foliage_dub_potted_spikey_plant" ]                         			     = loadfx( "props/foliage_dub_potted_spikey_plant" );
   level._effect[ "foliage_dub_potted_spikey_plant_halfsize" ]                         			     = loadfx( "props/foliage_dub_potted_spikey_plant_halfsize" );

  
	
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_hillside_ss_fx::main();
#/

}
