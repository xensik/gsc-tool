main()
{
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_restrepo_ss_fx::main();
#/

	level._effect["sand_medium_mp" ]							= loadfx( "sand/sand_medium_mp" );
	level._effect["sand_medium_mp_lt" ]							= loadfx( "sand/sand_medium_mp_lt" );
	level._effect["sand_blowing_mp"] 							= loadfx("sand/sand_blowing_mp");
	level._effect["rooftop_smolder_mp_wind"] 					= loadfx("smoke/rooftop_smolder_mp_wind");
	
	
	
	
	level._effect["spark_fall_runner_mp_infrequent"]			= loadfx("explosions/spark_fall_runner_mp_infrequent");
	level._effect["payback_insects"]							= loadfx("maps/payback/payback_insects");
	level._effect["sand_blowing_rooftops"] 						= loadfx("sand/sand_blowing_rooftops");
	level._effect["room_dust_100_mp"] 							= loadfx("dust/room_dust_100_mp");
	level._effect["paper_blowing_trash_fast_model"] 			= loadfx("misc/paper_blowing_trash_fast_model");
	level._effect["falling_dirt_light_2_runner_wind"]				= loadfx("dust/falling_dirt_light_2_runner_wind");
	level._effect["falling_dirt_light_2_runner"]				= loadfx("dust/falling_dirt_light_2_runner");
	level._effect["firelp_cheap_mp_wind"]						= loadfx("fire/firelp_cheap_mp_wind");
	
}
