#include common_scripts\utility;
#include common_scripts\_createfx;

main()
{
	level._effect[ "mp_bw_carfire" ]									 = loadfx( "maps/mp_boardwalk/mp_bw_carfire" );
	level._effect[ "mp_bw_distantsomke" ]								= loadfx( "maps/mp_boardwalk/mp_bw_distantsmoke" );
	level._effect[ "mp_bw_elecsparks" ]									 = loadfx( "maps/mp_boardwalk/mp_bw_elecsparks" );
	level._effect[ "mp_bw_embers" ]										 = loadfx( "maps/mp_boardwalk/mp_bw_embers" );
	level._effect[ "mp_bw_holesmoke" ]									 = loadfx( "maps/mp_boardwalk/mp_bw_holesmoke" );
	level._effect[ "mp_bw_sandblow" ]									 = loadfx( "maps/mp_boardwalk/mp_bw_sandblow" );
	level._effect[ "mp_bw_seagulls" ]									 = loadfx( "maps/mp_boardwalk/mp_bw_seagulls" );
	level._effect[ "mp_bw_smokeplumelrg" ]								 = loadfx( "maps/mp_boardwalk/mp_bw_smokeplumelrg" );
	level._effect[ "mp_bw_smolder" ]									= loadfx( "maps/mp_boardwalk/mp_bw_smolder" );
	level._effect[ "mp_bw_steam" ]										 = loadfx( "maps/mp_boardwalk/mp_bw_steam" );
	level._effect[ "mp_bw_trash" ]										 = loadfx( "maps/mp_boardwalk/mp_bw_trash" );
	level._effect[ "mp_bw_godray" ]										 = loadfx( "maps/mp_boardwalk/mp_bw_godray" );
	level._effect[ "mp_bw_seasplash" ]									= loadfx( "maps/mp_boardwalk/mp_bw_seasplash" );
	level._effect[ "mp_bw_waverunner" ]									= loadfx( "maps/mp_boardwalk/mp_bw_waverunner" );
	level._effect[ "dust/light_dust_motes_light_hs" ]					= loadfx( "dust/light_dust_motes_light_hs" );
	level._effect[ "fire/fire_barrel_trash" ]							= loadfx( "maps/mp_boardwalk/mp_bw_smallfire" );
	level._effect[ "mp_bw_flies" ]										= loadfx( "maps/mp_boardwalk/mp_bw_flies" );
	level._effect[ "mp_bw_fire" ]										= loadfx( "maps/mp_boardwalk/mp_bw_fire" );
	level._effect[ "mp_bw_clown01" ]									= loadfx( "maps/mp_boardwalk/mp_bw_clown01" );
	level._effect[ "mp_bw_clown02" ]									= loadfx( "maps/mp_boardwalk/mp_bw_clown02" );
	level._effect[ "mp_bw_clown03" ]									= loadfx( "maps/mp_boardwalk/mp_bw_clown03" );
	level._effect[ "mp_bw_clown04" ]									= loadfx( "maps/mp_boardwalk/mp_bw_clown04" );
	level._effect[ "mp_bw_clown05" ]									= loadfx( "maps/mp_boardwalk/mp_bw_clown05" );
	level._effect[ "mp_bw_game01" ]										= loadfx( "maps/mp_boardwalk/mp_bw_sparks_game01" );
	level._effect[ "mp_bw_game02" ]										= loadfx( "maps/mp_boardwalk/mp_bw_sparks_game02" );
	level._effect[ "mp_bw_game03" ]										= loadfx( "maps/mp_boardwalk/mp_bw_sparks_game03" );
	level._effect[ "mp_bw_ridesparks" ]									= loadfx( "maps/mp_boardwalk/mp_bw_ridesparks" );
	level._effect[ "mp_bw_waterflow" ]									= loadfx( "maps/mp_boardwalk/mp_bw_waterflow" );
	level._effect[ "mp_bw_waterfallsplash" ]							= loadfx( "maps/mp_boardwalk/mp_bw_waterfallsplash" );
	level._effect[ "mp_bw_waterpour" ]						   		 	= loadfx( "maps/mp_boardwalk/mp_bw_waterpour" );
	level._effect[ "mp_bw_paperwind" ]						   		 	= loadfx( "maps/mp_boardwalk/mp_bw_paperwind" );


	
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_boardwalk_fx::main();
#/

}
