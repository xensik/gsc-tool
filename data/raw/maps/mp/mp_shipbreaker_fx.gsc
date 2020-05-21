main()
{
	level._effect[ "Rain" ]									 = loadfx( "maps/mp_shipbreaker/mp_ship_rainlite" );
	level._effect[ "Ambdust" ]								 = loadfx( "maps/mp_shipbreaker/mp_ship_ambdust" );
	level._effect[ "Smokestack" ]							 = loadfx( "maps/mp_shipbreaker/mp_ship_smokestack" );
	level._effect[ "SplashA" ]								 = loadfx( "maps/mp_shipbreaker/mp_ship_splash" );
    level._effect[ "Darksmoke" ]							 = loadfx( "maps/mp_shipbreaker/mp_ship_darksmoke" );
	level._effect[ "Trashslow" ]							 = loadfx( "maps/mp_shipbreaker/mp_ship_paperslow" );
	level._effect[ "Flies" ]							     = loadfx( "maps/mp_shipbreaker/mp_ship_insects" );
	level._effect[ "Lightning" ]							 = loadfx( "maps/mp_shipbreaker/mp_ship_ltng_runner" );
	level._effect[ "Blowing sand" ]							  = loadfx( "maps/mp_shipbreaker/mp_ship_dust_fast" );
	level._effect[ "Dripping blood" ]						  = loadfx( "water/drips_blood_slow" );
	level._effect[ "Firebarrel" ]							  = loadfx( "fire/fire_barrel_trash_sb" );
	level._effect[ "Firetrash" ]							  = loadfx( "fire/fire_trash" );
	level._effect[ "Seagulls" ]							      = loadfx( "maps/mp_shipbreaker/mp_ship_seagulls" );
	level._effect[ "Sparks_welding" ]						  = loadfx( "maps/mp_shipbreaker/mp_ship_weld_runner" );
	level._effect[ "Searchlight" ]						      = loadfx( "maps/mp_shipbreaker/mp_ship_lighthouse" );
	level._effect[ "Spiraltrash" ]						      = loadfx( "maps/mp_shipbreaker/mp_ship_spiraltrash" );
	level._effect[ "waterdrips_long" ]						  = loadfx( "maps/mp_shipbreaker/mp_ship_waterdrips_long" );
	level._effect[ "Bulb" ]						              = loadfx( "maps/mp_shipbreaker/mp_ship_bglow" );
	level._effect[ "Glowstick" ]						       = loadfx( "maps/mp_shipbreaker/mp_ship_glowstick" );
	level._effect[ "Godraylarge" ]						       = loadfx( "maps/mp_shipbreaker/mp_ship_godraylarge" );
	level._effect[ "Godray_win_A" ]						       = loadfx( "maps/mp_shipbreaker/mp_ship_gray_win_a" );
	level._effect[ "Godray_win_B" ]						       = loadfx( "maps/mp_shipbreaker/mp_ship_gray_win_b" );
	level._effect[ "Live weld" ]						       = loadfx( "maps/mp_shipbreaker/mp_ship_weld_loop" );
	level._effect[ "Towerglow" ]						       = loadfx( "maps/mp_shipbreaker/mp_ship_towerglow" );
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_shipbreaker_fx::main();
#/

}
