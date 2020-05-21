main()
{
	// Clientsideeffects for MP
	/#
    if ( getdvar( "clientSideEffects", "1" ) != "1" )
	        maps\createfx\mp_overwatch_fx::main();
	#/
	precache_createfx_fx();
	precache_scripted_fx();
}

precache_createfx_fx()
	
{
	level._effect["light_godray_bloom_a"]					= loadfx("maps/mp_overwatch/light_godray_bloom_a");	
	level._effect["light_godray_bloom_b"]					= loadfx("maps/mp_overwatch/light_godray_bloom_b");	
	
	level._effect["wall_fire_mp2"]							= loadfx("fire/wall_fire_mp2");
	
	//Playspace
	level._effect["light_dust_motes_fog"] 					= loadfx("maps/mp_overwatch/light_dust_motes_fog");
	level._effect["light_dust_motes_fog_outdoor"] 			= loadfx("maps/mp_overwatch/light_dust_motes_fog_outdoor");
	level._effect["fog_bog_a_wind"] 						= loadfx("maps/mp_overwatch/fog_bog_a_wind");
	level._effect["fog_bog_a_wind_fast"] 					= loadfx("maps/mp_overwatch/fog_bog_a_wind_fast");
	level._effect["wind_blowing_rooftops"] 					= loadfx("maps/mp_overwatch/wind_blowing_rooftops");
	level._effect["generator_spark_runner_loop_interchange"]= loadfx("explosions/generator_spark_runner_l_nolight");
	
	//Background
	level._effect["aftermath"]								= loadfx("maps/mp_overwatch/aftermath");	
	level._effect["aftermath_lt"]							= loadfx("maps/mp_overwatch/aftermath_lt");	
	level._effect["fan_dust_spiral"]						= loadfx("maps/mp_overwatch/fan_dust_spiral");
	level._effect["building_smolder_sm"]					= loadfx("maps/mp_overwatch/building_smolder_sm");
	level._effect["building_smolder_sm_noember"]			= loadfx("maps/mp_overwatch/building_smolder_sm_noember");	
	level._effect["godray_solid"]						 	= loadfx("maps/mp_overwatch/godray_solid");	
	level._effect["godray_solid_sm"]						 	= loadfx("maps/mp_overwatch/godray_solid_sm");	
	
	level._effect["paratrp_jet_mp_r"]						= loadfx("maps/mp_overwatch/paratrp_jet_mp_r");	
	level._effect["jet_flyby_runner_noshadow"] 				= loadfx("maps/mp_park/jet_flyby_runner_noshadow");
	level._effect["building_missilehit_runner_mp"] 			= loadfx("explosions/building_missilehit_runner_mp");
	level._effect["field_fire_distant_mp"] 					= loadfx("fire/field_fire_distant_mp");
	level._effect["antiair_runner_flak_day_mp"] 				= loadfx("misc/antiair_runner_flak_day_mp");
	level._effect["ground_fog_mp_highrise_far2"] 			= loadfx("smoke/ground_fog_mp_highrise_far2");
	level._effect["building_fire_lg_bg_nosmoke"]			= loadfx("maps/mp_overwatch/building_fire_lg_bg_nosmoke");
	level._effect["building_smoke_lg_bg"]					= loadfx("maps/mp_overwatch/building_smoke_lg_bg");
	level._effect["building_smoke_lg_bg2"]					= loadfx("maps/mp_overwatch/building_smoke_lg_bg2");
	level._effect["building_smoke_lg_bg3"]					= loadfx("maps/mp_overwatch/building_smoke_lg_bg3");
	level._effect["waterbarrage_slow_mp"]					= loadfx("maps/mp_overwatch/waterbarrage_slow_mp");
	level._effect["pipe_drips"]								= loadfx("maps/mp_overwatch/pipe_drips");
	level._effect["steam_vent_small_nomodel"]				= loadfx("smoke/steam_vent_small_nomodel");
}

precache_scripted_fx()
{
}