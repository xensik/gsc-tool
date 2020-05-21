main()
{
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_park_fx::main();
#/

	precache_createfx_fx();
	precache_scripted_fx();
	precache_audio_fx();
}
precache_createfx_fx()
{
	
    level._effect["firelp_small_cheap_mp"] 		        	= loadfx("fire/firelp_small_cheap_mp");
    level._effect["firelp_small_cheap_mp_nodistortion"] 	= loadfx("fire/firelp_small_cheap_mp_nodistortion");
	level._effect["godray_intro_window"]					= loadfx("misc/godray_intro_window");	
	level._effect["roof_smolder"]							= loadfx("maps/mp_park/roof_smolder");	
	level._effect["godray_solid"]							= loadfx("maps/mp_park/godray_solid");	
	level._effect["building_smolder_embers"]				= loadfx("maps/mp_park/building_smolder_embers");	
	level._effect["leaves_falling_color"]					= loadfx("maps/mp_park/leaves_falling_color");
	level._effect["leaves_spiral_color_runner"]				= loadfx("maps/mp_park/leaves_spiral_color_runner");
	level._effect["leaves_blowing_color"]					= loadfx("maps/mp_park/leaves_blowing_color");
	level._effect["vista_fires"]							= loadfx("maps/mp_park/vista_fires");
	level._effect["fire_falling_runner_point_mp"]			= loadfx("fire/fire_falling_runner_point_mp");
	level._effect["wall_fire_mp2"]							= loadfx("fire/wall_fire_mp2");
	level._effect["wall_fire_mp3"]							= loadfx("fire/wall_fire_mp3");
	level._effect["water_fountain"]							= loadfx("maps/mp_park/water_fountain");
	level._effect["falling_dirt_light_2_runner"]			= loadfx("dust/falling_dirt_light_2_runner");
	level._effect["insects_carcass_flies"]					= loadfx("misc/insects_carcass_flies");
	level._effect["car_fire_mp"]							= loadfx("fire/car_fire_mp");
	level._effect["antiair_runner_flak_day"]				= loadfx("misc/antiair_runner_flak_day_mp");
	level._effect["burned_vehicle_sparks"]					= loadfx("fire/burned_vehicle_sparks");
	level._effect["jet_flyby_runner_noshadow"] 				= loadfx("maps/mp_park/jet_flyby_runner_noshadow");
	level._effect["building_missilehit_runner_mp"] 			= loadfx("explosions/building_missilehit_runner_mp");
	level._effect["park_smolder"]							= loadfx("maps/mp_park/park_smolder");
	level._effect["light_dust_motes_fog"] 					= loadfx("maps/mp_overwatch/light_dust_motes_fog");
	level._effect["generator_spark_runner_loop_interchange"]= loadfx("explosions/generator_spark_runner_l_nolight");
	level._effect["building_fire_lg_bg_nosmoke"]			= loadfx("maps/mp_overwatch/building_fire_lg_bg_nosmoke");
	level._effect["building_smoke_lg_bg"]					= loadfx("maps/mp_overwatch/building_smoke_lg_bg");
	level._effect["drips_mp_park"]							= loadfx("maps/mp_park/drips_mp_park");
}
precache_scripted_fx()
{
}

precache_audio_fx()
{
	level._effect["aud_wind_gust_leaves"]					= loadfx("maps/mp_park/aud_wind_gust_leaves");
	level._effect["aud_expl_dist"]							= loadfx("maps/mp_park/aud_expl_dist");
	level._effect["aud_gun_dist"]							= loadfx("maps/mp_park/aud_gun_dist");
}