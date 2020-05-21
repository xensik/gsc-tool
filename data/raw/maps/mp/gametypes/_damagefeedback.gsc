init()
{
	precacheShader("damage_feedback");
	precacheShader("damage_feedback_j");
	precacheShader("damage_feedback_lightarmor");
	precacheShader("damage_feedback_juggernaut");
	precacheShader("scavenger_pickup");

	level thread onPlayerConnect();
}

onPlayerConnect()
{
	for(;;)
	{
		level waittill("connected", player);

		player.hud_damagefeedback = newdamageindicatorhudelem(player); //*newClientHudElem(player);
		player.hud_damagefeedback.horzAlign = "center";
		player.hud_damagefeedback.vertAlign = "middle";
		player.hud_damagefeedback.x = -12;
		player.hud_damagefeedback.y = -12;
		player.hud_damagefeedback.alpha = 0;
		player.hud_damagefeedback.archived = true;
		player.hud_damagefeedback setShader("damage_feedback", 24, 48);
		
		player scavenger_hud_create();
	}
}

scavenger_hud_create()
{
	self.scavenger_icon = NewClientHudElem( self );
	self.scavenger_icon.horzAlign = "center";
	self.scavenger_icon.vertAlign = "middle";
	self.scavenger_icon.x = -36;
	self.scavenger_icon.y = 32;
	self.scavenger_icon.alpha = 0;

	width = 64;
	height = 32;

	self.scavenger_icon setShader( "scavenger_pickup", width, height );
}


updateDamageFeedback( typeHit )
{
	if ( !isPlayer( self ) )
		return;
	
	x = -12;
	y = -12;

	if ( getDvarInt( "camera_thirdPerson" ) )
		yOffset = self GetThirdPersonCrosshairOffset() * 240;
	else
		yOffset = getdvarfloat( "cg_crosshairVerticalOffset" ) * 240;
	
	if ( level.splitscreen )	
		yOffset *= 0.5;

	feedbackDurationOverride = 0;
	startAlpha = 1;
	
	if ( typeHit == "hitBodyArmor" )
	{
		self.hud_damagefeedback setShader("damage_feedback_j", 24, 48);
		self playlocalsound("MP_hit_alert"); // TODO: change sound?
	}
	else if ( typeHit == "hitLightArmor" )
	{
		self.hud_damagefeedback setShader("damage_feedback_lightarmor", 24, 48);
		self playlocalsound("MP_hit_alert");		
	}
	else if ( typeHit == "hitJuggernaut" )
	{
		self.hud_damagefeedback setShader("damage_feedback_juggernaut", 24, 48);
		self playlocalsound("MP_hit_alert");		
	}
	else if ( typeHit == "none" )
	{
		return;	
	}
	else if ( typeHit == "scavenger" && !level.hardcoreMode )
	{
		//changed to use the scavanger icon so it doens't follow the reticule
		self.scavenger_icon.alpha = startAlpha;
		self.scavenger_icon fadeOverTime( 2.5 );
		self.scavenger_icon.alpha = 0;
		return;
	}
	else
	{
		self.hud_damagefeedback setShader("damage_feedback", 24, 48);
		self playlocalsound("MP_hit_alert");
	}
	
	self.hud_damagefeedback.alpha = startAlpha;
	if ( feedBackDurationOverride != 0 )
		self.hud_damagefeedback fadeOverTime(feedbackDurationOverride);
	else	
		self.hud_damagefeedback fadeOverTime(1);
	
	self.hud_damagefeedback.alpha = 0;

	// only update hudelem positioning when necessary
	if ( self.hud_damagefeedback.x != x )
		self.hud_damagefeedback.x = x;	

	y = y - int( yOffset );
	if ( self.hud_damagefeedback.y != y )
		self.hud_damagefeedback.y = y;	
}