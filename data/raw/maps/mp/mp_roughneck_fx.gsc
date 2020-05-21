main()
{
	level._effect[ "mp_rn_rigpipefire" ]								 = loadfx( "maps/mp_roughneck/mp_rn_rigpipefire" );
	level._effect[ "mp_rn_rain" ]										 = loadfx( "maps/mp_roughneck/mp_rn_rain" ); 
	level._effect[ "mp_rn_mp_rn_vistafire" ]							 = loadfx( "maps/mp_roughneck/mp_rn_vistafire" );
	level._effect[ "mp_rn_mp_rn_steam" ]				     			 = loadfx( "maps/mp_roughneck/mp_rn_steam" );
	level._effect[ "mp_rn_mp_rn_mist" ]				     	     		 = loadfx( "maps/mp_roughneck/mp_rn_mist" );
	level._effect[ "mp_rn_mp_rn_drips" ]				     			 = loadfx( "maps/mp_roughneck/mp_rn_drips" );
	level._effect[ "mp_rn_redflash" ]				     			     = loadfx( "maps/mp_roughneck/mp_rn_redflash" );
	level._effect[ "mp_rn_blueflash" ]				     			     = loadfx( "maps/mp_roughneck/mp_rn_blueflash" );
	level._effect[ "mp_rn_whiteflash" ]				     			     = loadfx( "maps/mp_roughneck/mp_rn_whiteflash" );
	level._effect[ "mp_rn_whiteflash_2" ]				     			 = loadfx( "maps/mp_roughneck/mp_rn_whiteflash_2" );
	level._effect[ "mp_rn_whiteflash_3" ]				     			 = loadfx( "maps/mp_roughneck/mp_rn_whiteflash_3" );
	level._effect[ "mp_rn_lightning" ]				     			     = loadfx( "maps/mp_roughneck/mp_rn_lightning" );
	level._effect[ "mp_rn_rigvents" ]				     			     = loadfx( "maps/mp_roughneck/mp_rn_rigvents" );
	level._effect[ "mp_rn_roomsmoke" ]				     			     = loadfx( "maps/mp_roughneck/mp_rn_roomsmoke" );
	level._effect[ "mp_rn_lightsmoke" ]				     			     = loadfx( "maps/mp_roughneck/mp_rn_lightsmoke" );
	level._effect[ "mp_rn_distantsmoke" ]				     			 = loadfx( "maps/mp_roughneck/mp_rn_distantsmoke" );
	level._effect[ "mp_rn_bluelight" ]				     			     = loadfx( "maps/mp_roughneck/mp_rn_bluelight" );
	level._effect[ "mp_rn_yellowlight" ]				     			 = loadfx( "maps/mp_roughneck/mp_rn_yellowlight" );
	level._effect["water_bubbles_random_runner_qad" ]	      		     =loadfx("water/water_bubbles_random_runner_qad" );
	level._effect["body_splash" ]	             						=loadfx("water/body_splash" );
	level._effect[ "mp_rn_spotlights" ]				     				 = loadfx( "maps/mp_roughneck/mp_rn_spotlights" );
	level._effect[ "mp_rn_rainsplashes" ]				     			 = loadfx( "maps/mp_roughneck/mp_rn_rainsplashes" );
    level._effect[ "mp_rn_steamjet" ]				     				 = loadfx( "maps/mp_roughneck/mp_rn_steamjet" );
    level._effect[ "mp_rn_dripshvy" ]				     				 = loadfx( "maps/mp_roughneck/mp_rn_dripshvy" );
    
	
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_roughneck_fx::main();
#/

}
