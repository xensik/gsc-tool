main()
{
	
	
	
	level._effect[ "tornado_wind" ]						                              = loadfx( "weather/tornado_wind" );
	level._effect[ "insects_carcass_flies_dark" ]                     			= loadfx( "misc/insects_carcass_flies_dark" );	
	level._effect[ "sand_spray_detail_oriented_runner_mp_meteora" ]         = loadfx( "dust/sand_spray_detail_oriented_runner_mp_meteora" );	
	level._effect[ "hay_stack_ambient_bits" ]                     			    = loadfx( "misc/hay_stack_ambient_bits" );		
	level._effect[ "leaves_fall_strongwind_brown" ]           	 			      = loadfx( "misc/leaves_fall_strongwind_brown" );	
	level._effect[ "leaves_fall_strongwind_green" ]           	 			      = loadfx( "misc/leaves_fall_strongwind_green" );	
	level._effect[ "sand_detail_oriented_runner_mp_six" ]                   = loadfx( "dust/sand_detail_oriented_runner_mp_six" );	
	level._effect[ "ambient_green_leaves_mp_six" ]           	 			        = loadfx( "misc/ambient_green_leaves_mp_six" );	
	level._effect[ "sand_detail_oriented_dark_runner_mp_six" ]              = loadfx( "dust/sand_detail_oriented_dark_runner_mp_six" );		
	
	
	
	
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_six_ss_fx::main();
#/

}
