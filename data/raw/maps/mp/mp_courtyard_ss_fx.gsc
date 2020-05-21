main()
{
	level._effect[ "Volcano" ]										     = loadfx( "maps/mp_courtyard_ss/mp_ct_volcano" );
	level._effect[ "Godrays_A" ]										 = loadfx( "maps/mp_courtyard_ss/mp_ct_godrays_a" );
	level._effect[ "Godrays_B" ]										 = loadfx( "maps/mp_courtyard_ss/mp_ct_godrays_b" );
	level._effect[ "Godrays_C" ]										 = loadfx( "maps/mp_courtyard_ss/mp_ct_godrays_c" );
	level._effect[ "Ash" ]										         = loadfx( "maps/mp_courtyard_ss/mp_ct_ash" );
    level._effect[ "Ambient_dust" ]										 = loadfx( "maps/mp_courtyard_ss/mp_ct_ambdust" );
    level._effect[ "Insects" ]										     = loadfx( "maps/mp_courtyard_ss/mp_ct_insects" );
    level._effect[ "Dragonflies" ]										  = loadfx( "misc/insects_dragonfly_runner_a" );
   
	
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_courtyard_ss_fx::main();
#/
		
	precache_audio_fx();
}

precache_audio_fx()
{
	level._effect[ "audio_elm_volcano" ]									= loadfx( "maps/mp_courtyard_ss/audio_elm_volcano" );
}