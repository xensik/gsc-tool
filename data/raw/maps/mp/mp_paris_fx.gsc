main()
{
/#
    if ( getdvar( "clientSideEffects", "1" ) != "1" )
		maps\createfx\mp_paris_fx::main();
#/

	level._effect[ "falling_dirt_light_1_runner_bravo" ] 			= loadfx( "dust/falling_dirt_light_1_runner_bravo" );
	level._effect[ "falling_dirt_frequent_runner" ] 				= loadfx( "dust/falling_dirt_frequent_runner" );
	level._effect[ "room_dust_200_z150_mp" ] 						= loadfx( "dust/room_dust_200_z150_mp" );

	level._effect[ "ash_prague" ] 									= loadfx( "weather/ash_prague" );
	level._effect[ "embers_prague_light" ] 							= loadfx( "weather/embers_prague_light" );
	level._effect[ "ceiling_smoke_seatown" ] 						= loadfx( "weather/ceiling_smoke_seatown" );
	
	level._effect[ "chimney_smoke_mp" ] 							= loadfx( "smoke/chimney_smoke_mp" );
	level._effect[ "chimney_smoke_large_mp" ] 						= loadfx( "smoke/chimney_smoke_large_mp" );


	level._effect[ "falling_ash_mp" ] 								= loadfx( "misc/falling_ash_mp" );
	level._effect[ "trash_spiral_runner" ] 							= loadfx( "misc/trash_spiral_runner" );
	level._effect[ "leaves_fall_gentlewind_lambeth" ] 				= loadfx( "misc/leaves_fall_gentlewind_lambeth" );
	level._effect[ "leaves_spiral_runner" ] 						= loadfx( "misc/leaves_spiral_runner" );
	level._effect[ "antiair_runner_cloudy" ] 						= loadfx( "misc/antiair_runner_cloudy" );

	level._effect[ "insects_carcass_runner" ] 						= loadfx( "misc/insects_carcass_runner" );
	level._effect[ "insects_light_hunted_a_mp" ] 					= loadfx( "misc/insects_light_hunted_a_mp" );
	level._effect[ "insect_trail_runner_icbm" ] 					= loadfx( "misc/insect_trail_runner_icbm" );


	level._effect[ "firelp_med_pm" ] 								= loadfx( "fire/firelp_med_pm" );
	level._effect[ "firelp_small" ] 								= loadfx( "fire/firelp_small" );
	level._effect[ "firelp_small_cheap_mp" ] 						= loadfx( "fire/firelp_small_cheap_mp" );
	level._effect[ "firelp_med_pm_cheap" ] 							= loadfx( "fire/firelp_med_pm_cheap" );

	level._effect[ "building_hole_embers_mp" ] 						= loadfx( "fire/building_hole_embers_mp" );



}
