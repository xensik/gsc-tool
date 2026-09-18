// _createart generated.  modify at your own risk. 
main()
{
	ent = maps\_utility::create_vision_set_fog( "so_jeep_paris_b" );
	ent.startDist = 17346.26;
	ent.halfwayDist = 32487.6;
	ent.red = 0.583682;
	ent.green = 0.52939;
	ent.blue = 0.302793;
	ent.maxOpacity = 1;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 0;
	
	ent = maps\_utility::create_vision_set_fog( "paris_gasmask" );
	ent.startDist = 594.815;
	ent.halfwayDist = 3133.35;
	ent.red = 0.456554;
	ent.green = 0.482231;
	ent.blue = 0.53125;
	ent.maxOpacity = 0.40625;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 0;
	ent.sunRed = 1;
	ent.sunGreen = 0.809885;
	ent.sunBlue = 0.28125;
	ent.sunDir = (-0.913066, 0.39695, 0.0934982);
	ent.sunBeginFadeAngle = 15.2094;
	ent.sunEndFadeAngle = 46.6184;
	ent.normalFogScale = 2.21673;
	
 	maps\_utility::vision_set_fog_changes( "so_jeep_paris_b", 0 );
}
