main()
{

	level._effect[ "leavesfall" ]					    = loadfx( "maps/mp_moab/mp_mo_leavesfall" );
	level._effect[ "sandwhisp" ]					    = loadfx( "maps/mp_moab/mp_mo_sandwhisp" );
	level._effect[ "waterfall" ]					    = loadfx( "maps/mp_moab/mp_mo_waterfall" );
	level._effect[ "waterfallsplash" ]			         = loadfx( "maps/mp_moab/mp_mo_waterfallsplash" );
	level._effect[ "Waterlock" ]			             = loadfx( "maps/mp_moab/mp_mo_waterlock" );
	level._effect[ "Watershore" ]			             = loadfx( "maps/mp_moab/mp_mo_watershore" );
	level._effect[ "Ambdust" ]			                 = loadfx( "maps/mp_moab/mp_mo_ambdust" );
	level._effect[ "Watermist" ]			             = loadfx( "maps/mp_moab/mp_mo_watermist" );
	level._effect[ "Sand_runner" ]			             = loadfx( "maps/mp_moab/mp_mo_sandrunner" );
	level._effect[ "Dustfallr" ]			             = loadfx( "maps/mp_moab/mp_mo_dustfall" );
	level._effect[ "Godray_thin" ]			             = loadfx( "maps/mp_moab/mp_mo_graythin" );
	level._effect[ "Largefall" ]			             = loadfx( "maps/mp_moab/mp_mo_largefall" );
	level._effect[ "Wheelsplash" ]			             = loadfx( "maps/mp_moab/mp_mo_wheelsplash" );
	level._effect[ "Splash_grating" ]			         = loadfx( "water/wheel_splash_moab" );
	level._effect[ "Shoresplash" ]			             = loadfx( "maps/mp_moab/mp_mo_watersplash_shore" );
	level._effect[ "Wheel_drip_small" ]			         = loadfx( "maps/mp_moab/mp_mo_wheeldrip_small" );
	level._effect[ "Lightglow" ]			             = loadfx( "maps/mp_moab/mp_mo_lightglow" );
	level._effect[ "Birds" ]			                 = loadfx( "maps/mp_moab/mp_mo_bird" );
	level._effect[ "Rainbow" ]			                 = loadfx( "maps/mp_moab/mp_mo_rainbow" );
	level._effect[ "Waterdrip" ]			             = loadfx( "maps/mp_moab/mp_mo_waterdrip" );
	level._effect[ "Rocksplash" ]			             = loadfx( "maps/mp_moab/mp_mo_rocksplash" );
	level._effect[ "carfire" ]			                  = loadfx( "maps/mp_moab/mp_mo_carfire" );
	level._effect[ "Rapidwater" ]			             = loadfx( "maps/mp_moab/mp_mo_rapidwater" );
	level._effect["sand_blowing_moab"] 					= loadfx("sand/sand_blowing_moab");
	level._effect["Clouds_far"] 					    = loadfx("weather/cloud_mountains_moab");
	level._effect["Flies"] 					            = loadfx("maps/mp_moab/mp_mo_flies");
	level._effect["Condor"] 					        = loadfx("maps/mp_moab/mp_mo_condor");
	level._effect["Dustsplash"] 					    = loadfx("maps/mp_moab/mp_mo_dustsplash");
	level._effect["Valleymist"] 					    = loadfx("weather/mist_valley_moab");
	level._effect["Clouds_cliff"] 					    = loadfx("weather/cloud_cliffs_moab");
	level._effect["dust_cloud"] 					    = loadfx("dust/dust_cloud_moab");
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_moab_fx::main();
#/

}
