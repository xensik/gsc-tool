// _createart generated.  modify at your own risk. 
main()
{
	ent = maps\_utility::create_vision_set_fog( "mp_plaza2" );
	ent.startDist = 1550;
	ent.halfwayDist = 13965;
	ent.red = 0.63;
	ent.green = 0.70;
	ent.blue = 0.72;
	ent.maxOpacity = 0.264091;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.85;
	ent.sunGreen = 0.74;
	ent.sunBlue = 0.61;
	ent.sunDir = (0.230612, 0.972645, 0.0277892);
	ent.sunBeginFadeAngle = 0;
	ent.sunEndFadeAngle = 69;
	ent.normalFogScale = 0.96;

	ent = maps\_utility::create_vision_set_fog( "plaza_interior" );
	ent.startDist = 358;
	ent.halfwayDist = 29010;
	ent.red = 0;
	ent.green = 0.579312;
	ent.blue = 0.606125;
	ent.maxOpacity = 0.264091;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.999636;
	ent.sunGreen = 0.745874;
	ent.sunBlue = 0.519721;
	ent.sunDir = (0.230612, 0.972645, 0.0277892);
	ent.sunBeginFadeAngle = 0;
	ent.sunEndFadeAngle = 180;
	ent.normalFogScale = 1.4128;
}
