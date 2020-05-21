// _createart generated.  modify at your own risk. 
main()
{
	ent = maps\_utility::create_vision_set_fog( "mp_overwatch" );
	ent.startDist = 1200;
	ent.halfwayDist = 88053.4;
	ent.red = 0.729014;
	ent.green = 0.702022;
	ent.blue = 0.698223;
	ent.maxOpacity = 0.156545;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.4312;
	ent.sunGreen = 0.4302;
	ent.sunBlue = 0.4313;
	ent.sunDir = ( 0, 0, -1);
	ent.sunBeginFadeAngle = 12;
	ent.sunEndFadeAngle = 78;
	ent.normalFogScale = 0.7343;
	
	maps\_utility::vision_set_fog_changes( "mp_overwatch", 0 );
}
