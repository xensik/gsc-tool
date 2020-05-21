main()
{
	level._effect[ "test_effect" ]										= loadfx( "misc/moth_runner" );
	
	// fire & smoke
	level._effect[ "oil_field_fire_burn_ss" ]							= loadfx( "fire/oil_field_fire_burn_ss" );
	level._effect[ "oil_field_smoke_ss" ]								= loadfx( "smoke/oil_field_smoke_ss" );
	level._effect[ "car_fire_mp" ]										= loadfx( "fire/car_fire_mp" );
	level._effect[ "amb_smoke_distant_burn_ss" ]						= loadfx( "smoke/amb_smoke_distant_burn_ss" );
	level._effect[ "smolder_mp_burn" ]									= loadfx( "smoke/smolder_mp_burn" );
	level._effect[ "sand_medium_mp_lt" ]								= loadfx( "sand/sand_medium_mp_lt_burn" );
	
	// sand & trash
	level._effect[ "sand_blowing_mp_burn" ]								= loadfx( "sand/sand_blowing_mp_burn" );
	level._effect[ "trash_spiral_runner" ]								= loadfx( "misc/trash_spiral_runner" );
	level._effect[ "sand_spray_runner_400x400_burn" ]					= loadfx( "sand/sand_spray_runner_400x400_burn" );
	
	// oil
	level._effect[ "oil_drop_small" ]									= loadfx( "misc/oil_drip_small" );
	
	// A10 Flyby
	level._effect[ "a10_flyby_runner_noshadow" ]						= loadfx( "maps/mp_burn/a10_flyby_runner_noshadow" );
	
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_burn_ss_fx::main();
#/

}
