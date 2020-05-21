// _createart generated.  modify at your own risk. 
main()
{
	ent = maps\_utility::create_vision_set_fog( "mp_nola" );
	ent.startDist = 168.45;
	ent.halfwayDist = 5503.32;
	ent.red = 0.681;
	ent.green = 0.684;
	ent.blue = 0.687;
	ent.maxOpacity = 0.2875;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.826;
	ent.sunGreen = 0.763;
	ent.sunBlue = 0.696;
	ent.sunDir = (-0.046, -0.780, 0.622);
	ent.sunBeginFadeAngle = 0;
	ent.sunEndFadeAngle = 115.8;
	ent.normalFogScale = 1.0;
	
	ent = maps\_utility::create_vision_set_fog( "mp_nola_indoor" );
	ent.startDist = 300;
	ent.halfwayDist = 7971;
	ent.red = 0.681;
	ent.green = 0.684;
	ent.blue = 0.687;
	ent.maxOpacity = 0.20;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.826;
	ent.sunGreen = 0.763;
	ent.sunBlue = 0.696;
	ent.sunDir = (-0.046, -0.780, 0.622);
	ent.sunBeginFadeAngle = 0;
	ent.sunEndFadeAngle = 105.8;
	ent.normalFogScale = 1.0;
	
	ent = maps\_utility::create_vision_set_fog( "mp_nola_church" );
	ent.startDist = 300;
	ent.halfwayDist = 7971;
	ent.red = 0.681;
	ent.green = 0.684;
	ent.blue = 0.687;
	ent.maxOpacity = 0.20;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.826;
	ent.sunGreen = 0.763;
	ent.sunBlue = 0.696;
	ent.sunDir = (-0.046, -0.780, 0.622);
	ent.sunBeginFadeAngle = 0;
	ent.sunEndFadeAngle = 105.8;
	ent.normalFogScale = 1.0;
 
	
 
 
	maps\_utility::vision_set_fog_changes( "mp_nola", 0 );
}
