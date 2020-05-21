main()
{
	level._effect[ "Smoke_Column" ]									  = loadfx( "maps/mp_nola/mp_nl_smokecol" );
	level._effect[ "Smoke_Filler" ]									  = loadfx( "maps/mp_nola/mp_nl_smokefiller" );
	level._effect[ "Smoke_ac" ]										  = loadfx( "maps/mp_nola/mp_nl_acsmoke" );
	level._effect[ "Dust_motes" ]									  = loadfx( "maps/mp_nola/mp_nl_ambdust" );
	level._effect[ "Ground_fog" ]									  = loadfx( "maps/mp_nola/mp_nl_lowfog" );
	level._effect[ "chimney" ]										  = loadfx( "maps/mp_nola/mp_nl_chimney" );
	level._effect[ "Sparks" ]										  = loadfx( "maps/mp_nola/mp_nl_sparks" );
	level._effect[ "Fallfire" ]										  = loadfx( "maps/mp_nola/mp_nl_fallingfire" );
	level._effect[ "Smallfire" ]									  = loadfx( "maps/mp_nola/mp_nl_smallfire" );
	level._effect[ "BLDGfire" ]									      = loadfx( "maps/mp_nola/mp_nl_bldfire" );
	level._effect[ "Window_fire" ]									  = loadfx( "maps/mp_nola/mp_nl_winfire" );
	level._effect[ "Thick_smoke" ]									  = loadfx( "maps/mp_nola/mp_nl_thicksmoke" );
	level._effect[ "Falling_dust" ]									  = loadfx( "maps/mp_nola/mp_nl_dustfall" );
	level._effect[ "Godray_thin" ]									  = loadfx( "maps/mp_nola/mp_nl_godray_thin" );
	level._effect[ "Spiral_trash" ]									  = loadfx( "maps/mp_nola/mp_nl_spiraltrash" );
	level._effect[ "Slow_trash" ]									  = loadfx( "maps/mp_nola/mp_nl_paperslow" );
	level._effect[ "Burnt_smoke" ]									  = loadfx( "maps/mp_nola/mp_nl_burntsmoke" );
	level._effect[ "Godray_large" ]									  = loadfx( "maps/mp_nola/mp_nl_godraylarge" );
	level._effect[ "Carfire" ]									      = loadfx( "maps/mp_nola/mp_nl_carfire" );
	level._effect[ "lightash" ]									      = loadfx( "maps/mp_nola/mp_nl_lightash" );
	level._effect[ "Embers" ]									      = loadfx( "maps/mp_nola/mp_nl_embers" );
	level._effect[ "Godray_win" ]									  = loadfx( "maps/mp_nola/mp_nl_godraywin" );
	level._effect[ "Candle" ]									      = loadfx( "maps/mp_nola/mp_nl_candle" );
	level._effect[ "Vent_steam" ]									  = loadfx( "maps/mp_nola/mp_nl_ventsteam" );
	level._effect[ "churchsmoke" ]									  = loadfx( "maps/mp_nola/mp_nl_churchsmoke" );
	
	level._effect[ "bottles_brandy_destruct" ]						    	= loadfx( "props/bottles_brandy_destruct" );
	level._effect[ "bottles_misc1_destruct" ]						    	= loadfx( "props/bottles_misc1_destruct" );
	level._effect[ "bottles_misc2_destruct" ]						    	= loadfx( "props/bottles_misc2_destruct" );
	level._effect[ "bottles_misc3_destruct" ]						    	= loadfx( "props/bottles_misc3_destruct" );
	level._effect[ "bottles_misc4_destruct" ]						    	= loadfx( "props/bottles_misc4_destruct" );
	
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_nola_fx::main();
#/

}
