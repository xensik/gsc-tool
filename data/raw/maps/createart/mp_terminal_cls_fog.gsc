// _createart generated.  modify at your own risk. 
main()
{
	ent = maps\_utility::create_vision_set_fog( "mp_terminal_cls" );

  ent.startDist = 2219;
	ent.halfwayDist = 13307;
	ent.red = 0.721;
	ent.green = 0.737;
	ent.blue = 0.759;
	ent.maxOpacity = 0.530;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 0;

	
	maps\_utility::vision_set_fog_changes( "mp_terminal_cls", 0 );
}
