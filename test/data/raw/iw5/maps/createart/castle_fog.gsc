// _createart generated.  modify at your own risk.
main()
{
	ent = maps\_utility::create_vision_set_fog( "castle_intro" );
	ent.startDist = 1000;
	ent.halfwayDist = 6000;
	ent.red = 0.218899;
	ent.green = 0.286112;
	ent.blue = 0.330931;
	ent.maxOpacity = 0.62;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.40;
	ent.sunGreen = 0.47;
	ent.sunBlue = 0.47;
	ent.sunDir = ( 0, 0, -1);
	ent.sunBeginFadeAngle = 30;
	ent.sunEndFadeAngle = 60;
	ent.normalFogScale = 2;
 
	ent = maps\_utility::create_vision_set_fog( "castle_exterior" );
	ent.startDist = 1000;
	ent.halfwayDist = 6000;
	ent.red = 0.218899;
	ent.green = 0.286112;
	ent.blue = 0.330931;
	ent.maxOpacity = 0.62;
	ent.transitionTime = 0.5;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.40;
	ent.sunGreen = 0.47;
	ent.sunBlue = 0.47;
	ent.sunDir = (0, 0, -1);
	ent.sunBeginFadeAngle = 70;
	ent.sunEndFadeAngle = 90;
	ent.normalFogScale = 5;
 
	ent = maps\_utility::create_vision_set_fog( "castle_light_switch" );
	ent.startDist = 1000;
	ent.halfwayDist = 6000;
	ent.red = 0.31;
	ent.green = 0.32;
	ent.blue = 0.32;
	ent.maxOpacity = 0.62;
	ent.transitionTime = 0.5;
	ent.sunFogEnabled = 1;
	ent.normalFogScale = 0;
	ent.sunRed = 0.40;
	ent.sunGreen = 0.47;
	ent.sunBlue = 0.47;
	ent.sunDir = (0, 0, -1);
	ent.sunBeginFadeAngle = 88;
	ent.sunEndFadeAngle = 97;
	ent.normalFogScale = 0;
 
	ent = maps\_utility::create_vision_set_fog( "castle_interior" );
	ent.startDist = 1000;
	ent.halfwayDist = 6000;
	ent.red = 0.31;
	ent.green = 0.32;
	ent.blue = 0.32;
	ent.maxOpacity = 0.62;
	ent.transitionTime = 0.5;
	ent.sunFogEnabled = 1;
	ent.normalFogScale = 0.5;
	ent.sunRed = 0.40;
	ent.sunGreen = 0.47;
	ent.sunBlue = 0.47;
	ent.sunDir = (0, 0, -1);
	ent.sunBeginFadeAngle = 88;
	ent.sunEndFadeAngle = 97;
	ent.normalFogScale = 1.5;
 
	ent = maps\_utility::create_vision_set_fog( "castle_courtyard" );
	ent.startDist = 1000;
	ent.halfwayDist = 6000;
	ent.red = 0.218899;
	ent.green = 0.286112;
	ent.blue = 0.330931;
	ent.maxOpacity = 0.62;
	ent.transitionTime = 0.5;
	ent.sunFogEnabled = 1;
	ent.sunRed = 0.40;
	ent.sunGreen = 0.47;
	ent.sunBlue = 0.47;
	ent.sunDir = (0, 0, -1);
	ent.sunBeginFadeAngle = 70;
	ent.sunEndFadeAngle = 90;
	ent.normalFogScale = 5;
 
 
	ent = maps\_utility::create_vision_set_fog( "castle_forest" );
	ent.startDist = 3764.17;
	ent.halfwayDist = 19391;
	ent.red = 0.661137;
	ent.green = 0.554261;
	ent.blue = 0.454014;
	ent.maxOpacity = 0.7;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 0;
 
	ent = maps\_utility::create_vision_set_fog( "castle_nvg_grain" );
	ent.startDist = 5000;
	ent.halfwayDist = 8000;
	ent.red = 0;
	ent.green = 0;
	ent.blue = 0;
	ent.maxOpacity = 0;
	ent.transitionTime = 0;
	ent.sunFogEnabled = 0;
 
	maps\_utility::vision_set_fog_changes( "castle_intro", 0 );
}
