main()
{
	
	level._effect[ "steam_manhole" ]								     = loadfx( "maps/mp_crosswalk_ss/mp_cw_guttersteam" );
	level._effect[ "trash_slow" ]								         = loadfx( "maps/mp_crosswalk_ss/mp_cw_paperslow" );
	level._effect[ "waterdrip" ]								         = loadfx( "maps/mp_crosswalk_ss/mp_cw_dripfast" );
	level._effect[ "smokefiller" ]								         = loadfx( "maps/mp_crosswalk_ss/mp_cw_smokefiller" );
	level._effect[ "smokestack" ]								         = loadfx( "maps/mp_crosswalk_ss/mp_cw_smokestack" );
	level._effect[ "amb_dust" ]								            = loadfx( "maps/mp_crosswalk_ss/mp_cw_ambdust" );
	level._effect[ "flies" ]								            = loadfx( "maps/mp_crosswalk_ss/mp_cw_insects" );
	level._effect[ "Carfire" ]								            = loadfx( "maps/mp_crosswalk_ss/mp_cw_carfire" );
	level._effect[ "Steam_vent" ]								         = loadfx( "maps/mp_crosswalk_ss/mp_cw_steamvent" );
	level._effect[ "Police_Cruiser_Lights2" ]							= loadfx( "maps/mp_crosswalk_ss/mp_cw_policelights2" );
    level._effect[ "mp_cw_yeltraflight" ]						    	= loadfx( "maps/mp_crosswalk_ss/mp_cw_yeltraflight" );	
    level._effect[ "mp_cw_carfirelit" ]						        	= loadfx( "maps/mp_crosswalk_ss/mp_cw_carfirelit" );
	level._effect[ "mp_cw_sunflare" ]						        	= loadfx( "maps/mp_crosswalk_ss/mp_cw_sunflare" );    
    
    
    
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_crosswalk_ss_fx::main();
#/

}
