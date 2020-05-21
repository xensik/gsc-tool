main()
{
	precacheShellshock("flashbang_mp");
}


startMonitoringFlash()
{
	self thread monitorFlash();
}


stopMonitoringFlash(disconnected)
{
	self notify("stop_monitoring_flash");
}


flashRumbleLoop( duration )
{
	self endon("stop_monitoring_flash");
	
	self endon("flash_rumble_loop");
	self notify("flash_rumble_loop");
	
	goalTime = getTime() + duration * 1000;
	
	while ( getTime() < goalTime )
	{
		self PlayRumbleOnEntity( "damage_heavy" );
		wait( 0.05 );
	}
}


monitorFlash()
{
	self endon("disconnect");
	self.flashEndTime = 0;
	while(1)
	{
		self waittill( "flashbang", origin, amount_distance, amount_angle, attacker );
		
		if ( !isalive( self ) )
			continue;
		
		if ( isDefined( self.usingRemote ) )
			continue;
		
		hurtattacker = false;
		hurtvictim = true;
		
		if ( amount_angle < 0.25 )
			amount_angle = 0.25;
		else if ( amount_angle > 0.8 )
			amount_angle = 1;

		duration = amount_distance * amount_angle * 5.5;
		
		//MW3 stun resistance perk
		if ( isDefined( self.stunScaler ) )
			duration = duration * self.stunScaler;
		
		if ( duration < 0.25 )
			continue;
			
		rumbleduration = undefined;
		if ( duration > 2 )
			rumbleduration = 0.75;
		else
			rumbleduration = 0.25;
		
		assert(isdefined(self.pers["team"]));
		if (level.teamBased && isdefined(attacker) && isdefined(attacker.pers["team"]) && attacker.pers["team"] == self.pers["team"] && attacker != self)
		{
			if(level.friendlyfire == 0) // no FF
			{
				continue;
			}
			else if(level.friendlyfire == 1) // FF
			{
			}
			else if(level.friendlyfire == 2) // reflect
			{
				duration = duration * .5;
				rumbleduration = rumbleduration * .5;
				hurtvictim = false;
				hurtattacker = true;
			}
			else if(level.friendlyfire == 3) // share
			{
				duration = duration * .5;
				rumbleduration = rumbleduration * .5;
				hurtattacker = true;
			}
		}
		else if( isDefined(attacker) )
		{
			attacker notify( "flash_hit" );
			if( attacker != self )
				attacker maps\mp\gametypes\_missions::processChallenge( "ch_indecentexposure" );
		}
		
		if ( hurtvictim && isDefined(self) )
		{
			self thread applyFlash(duration, rumbleduration);
			
			if ( isDefined(attacker) && attacker != self )
				attacker thread maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "flash" );
		}
		if ( hurtattacker && isDefined(attacker) )
		{
			attacker thread applyFlash(duration, rumbleduration);
		}
	}
}

applyFlash(duration, rumbleduration)
{
	// wait for the highest flash duration this frame,
	// and apply it in the following frame
	
	if (!isdefined(self.flashDuration) || duration > self.flashDuration)
		self.flashDuration = duration;
	if (!isdefined(self.flashRumbleDuration) || rumbleduration > self.flashRumbleDuration)
		self.flashRumbleDuration = rumbleduration;
	
	wait .05;
	
	if (isdefined(self.flashDuration)) {
		self shellshock( "flashbang_mp", self.flashDuration ); // TODO: avoid shellshock overlap
		self.flashEndTime = getTime() + (self.flashDuration * 1000);
	}
	if (isdefined(self.flashRumbleDuration)) {
		self thread flashRumbleLoop( self.flashRumbleDuration ); //TODO: Non-hacky rumble.
	}
	
	self.flashDuration = undefined;
	self.flashRumbleDuration = undefined;
}


isFlashbanged()
{
	return isDefined( self.flashEndTime ) && gettime() < self.flashEndTime;
}
