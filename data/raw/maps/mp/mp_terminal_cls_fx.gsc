main()
{
	//ambient fx
	level._effect[ "ground_smoke_1200x1200" ]		= loadfx( "smoke/ground_smoke1200x1200" );
	level._effect[ "hallway_smoke_light" ]			= loadfx( "smoke/hallway_smoke_light" );
	level._effect[ "room_smoke_200" ]				= loadfx( "smoke/room_smoke_200" );
	level._effect[ "room_smoke_400" ]				= loadfx( "smoke/room_smoke_400" );
	level._effect[ "light_shaft_motes_airport" ]	= loadfx( "dust/light_shaft_motes_airport" );
	
	level._effect[ "test_effect" ]										 = loadfx( "misc/moth_runner" );
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_terminal_cls_fx::main();
#/

}
