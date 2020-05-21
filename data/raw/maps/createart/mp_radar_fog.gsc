// _createart generated.  modify at your own risk. 
main()
{
	ent = maps\_utility::create_vision_set_fog( "mp_radar" );
	ent.startDist = 431;
	ent.halfwayDist = 2370;
	ent.red = 0.762;
	ent.green = 0.806;
	ent.blue = 0.887;
	ent.maxOpacity = 0.885;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 0;

        ent = maps\_utility::create_vision_set_fog( "bunker_area" );
	ent.startDist = 731;
	ent.halfwayDist = 2370;
	ent.red = 0.762;
	ent.green = 0.806;
	ent.blue = 0.887;
	ent.maxOpacity = 0.15;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 0;
}
