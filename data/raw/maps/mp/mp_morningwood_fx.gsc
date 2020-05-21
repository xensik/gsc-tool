main()
{

/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_morningwood_fx::main();
#/

	precache_audio_fx();

//ambient fx
	level._effect[ "dust_wind_fast_paper" ]						  = loadfx( "maps/mp_morningwood/mp_mwd_paperfast" );
	level._effect[ "dust_wind_slow_paper" ]						  = loadfx( "maps/mp_morningwood/mp_mwd_paperslow" );
    level._effect[ "embers_prague_light" ]						 = loadfx( "weather/embers_prague_light" );
	level._effect[ "firelp_med_pm" ] 		                          = loadfx( "fire/firelp_med_pm" );
	level._effect[ "bg_smoke_plume" ] 		                        = loadfx( "maps/mp_morningwood/mp_mwd_smokeplume" );
	level._effect[ "bg_smoke_nofire" ] 		                        = loadfx( "maps/mp_morningwood/mp_mwd_smoke_nofire" );
	level._effect[ "firelp_med_pm_cheap" ] 		                    = loadfx( "maps/mp_morningwood/mp_mwd_fire_cheap" );
	level._effect[ "fire_small" ] 		                            = loadfx( "maps/mp_morningwood/mp_mwd_fire_small" );
	level._effect[ "light_glow_white_lamp" ]		                  = loadfx( "misc/light_glow_white_lamp" );
    level._effect[ "wall_fire_mp" ] 		                          = loadfx( "maps/mp_morningwood/mp_mwd_wallfire" );
	level._effect[ "bg_smoke_short" ] 		                        = loadfx( "maps/mp_morningwood/mp_mwd_shortsmoke" );
	level._effect[ "Ground fog" ] 		                            = loadfx( "maps/mp_morningwood/mp_mwd_groundfog" );
	level._effect[ "Embers" ] 		                               = loadfx( "maps/mp_morningwood/mp_mwd_embers" );
	level._effect[ "Firefall" ] 		                            = loadfx( "maps/mp_morningwood/mp_mwd_fallingfire" );
   	level._effect[ "Ambient smoke" ] 		                         = loadfx( "maps/mp_morningwood/mp_mwd_ashsteam" );
	level._effect[ "waterdrips" ] 		                         = loadfx( "maps/mp_morningwood/mp_mwd_waterdrips" );
	level._effect[ "Wall smoke" ] 		                         = loadfx( "maps/mp_morningwood/mp_mwd_wallsmoke" );
	level._effect[ "Int Sparks" ] 		                         = loadfx( "maps/mp_morningwood/mp_mwd_sparks_int" );
	level._effect[ "Int Sparks 2" ] 		                     = loadfx( "maps/mp_morningwood/mp_mwd_sparks_int2" );
	level._effect["godray_large"]                                 = loadfx( "maps/mp_morningwood/mp_mwd_godraylarge" );
	level._effect["Ambient dust"]                                 = loadfx( "maps/mp_morningwood/mp_mwd_ambdust" );
	level._effect["VistaFX"]                                   = loadfx( "maps/mp_morningwood/mp_mwd_vistafx" );
	level._effect["Trash spiral"]                                = loadfx( "maps/mp_morningwood/mp_mwd_spiraltrash" );
	
	

	
}

precache_audio_fx()
{
	level._effect["aud_metal_debris01"]					= loadfx("maps/mp_morningwood/aud_metal_debris01");
	level._effect["aud_metal_debris02"]					= loadfx("maps/mp_morningwood/aud_metal_debris02");
	level._effect["aud_wood_debris01"]					= loadfx("maps/mp_morningwood/aud_wood_debris01");
	level._effect["aud_wood_debris02"]					= loadfx("maps/mp_morningwood/aud_wood_debris02");
}


