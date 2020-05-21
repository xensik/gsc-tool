// _createart generated.  modify at your own risk. 
main()
{
	ent = maps\_utility::create_vision_set_fog( "mp_roughneck" );
	ent.startDist = 512.098;
	ent.halfwayDist = 4150;
	ent.red = 0.331909;
	ent.green = 0.373677;
	ent.blue = 0.394813;
	ent.maxOpacity = 1;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.837117;
	ent.sunGreen = 0.834223;
	ent.sunBlue = 0.813915;
	ent.sunDir = (-0.00178854, 0.413538, 0.910485);
	ent.sunBeginFadeAngle = 0;
	ent.sunEndFadeAngle = 121.977;
	ent.normalFogScale = 0.310851;
	
	ent = maps\_utility::create_vision_set_fog( "mp_roughneck_indoor" );
	ent.startDist = 256;
	ent.halfwayDist = 2700;
	ent.red = 0.331909;
	ent.green = 0.373677;
	ent.blue = 0.394813;
	ent.maxOpacity = 0.75;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.837117;
	ent.sunGreen = 0.834223;
	ent.sunBlue = 0.813915;
	ent.sunDir = (-0.00178854, 0.413538, 0.910485);
	ent.sunBeginFadeAngle = 0;
	ent.sunEndFadeAngle = 121.977;
	ent.normalFogScale = 0.310851;
 
	ent = maps\_utility::create_vision_set_fog( "mp_roughneck_water" );
	ent.startDist = 0.0;
	ent.halfwayDist = 97.41;
	ent.red = 0.1;
	ent.green = 0.2;
	ent.blue = 0.2;
	ent.maxOpacity = 1.00;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.267;
	ent.sunGreen = 0.275;
	ent.sunBlue = 0.277;
	ent.sunDir = (0.72, -0.60, 0.32);
	ent.sunBeginFadeAngle = 24.1;
	ent.sunEndFadeAngle = 52.7;
	ent.normalFogScale = 8.3;
	
	ent = maps\_utility::create_vision_set_fog( "mp_roughneck_water_deep" );
	ent.startDist = 0.0;
	ent.halfwayDist = 97.41;
	ent.red = 0.1;
	ent.green = 0.2;
	ent.blue = 0.2;
	ent.maxOpacity = 1.00;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.267;
	ent.sunGreen = 0.275;
	ent.sunBlue = 0.277;
	ent.sunDir = (0.72, -0.60, 0.32);
	ent.sunBeginFadeAngle = 24.1;
	ent.sunEndFadeAngle = 52.7;
	ent.normalFogScale = 8.3;
	
	maps\_utility::vision_set_fog_changes( "mp_roughneck", 0 );
}
