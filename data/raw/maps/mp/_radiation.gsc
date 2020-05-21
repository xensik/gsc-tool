#include maps\mp\_utility;
#include common_scripts\utility;

radiation()
{
	precacheString( &"SCRIPT_RADIATION_DEATH" );
	radiationFields = getentarray("radiation", "targetname");
	
	if (radiationFields.size > 0)
	{
		
		precacheshellshock( "mp_radiation_low" );
		precacheshellshock( "mp_radiation_med" );
		precacheshellshock( "mp_radiation_high" );
		
		foreach ( trigger in radiationFields )
			trigger thread common_scripts\_dynamic_world::triggerTouchThink( ::playerEnterArea, ::playerLeaveArea );
		
		thread onPlayerConnect();
	}
	
}

onPlayerConnect()
{
	for ( ;; )
	{
		level waittill ( "connected", player );
			player.numAreas = 0;
	}
}

playerEnterArea( trigger )
{
	self.numAreas++;
	
	if ( self.numAreas == 1 )
		self radiationEffect();
}


playerLeaveArea( trigger )
{
	self.numAreas--;
	assert( self.numAreas >= 0 );
	
	if ( self.numAreas != 0 )
		return;
	
	self.poison = 0;
	self notify( "leftTrigger");
	
	if ( isDefined( self.radiationOverlay ) )
		self.radiationOverlay fadeoutBlackOut( .10, 0 );
}

soundWatcher( soundOrg )
{
	self waittill_any( "death", "leftTrigger" );
	
	self stopLoopSound();
}

radiationEffect()
{
	self endon( "disconnect" );
	self endon( "game_ended" );
	self endon( "death" );
	self endon( "leftTrigger" );
	
	self.poison = 0;
	self thread soundWatcher( self );
	
	while (1)
	{
		self.poison ++;
		
		switch( self.poison )
		{
			case 1:				  
				self.radiationSound = "item_geigercouner_level2";
				self playLoopSound( self.radiationSound );
				self ViewKick( 1, self.origin );
				break;
			case 3:				  
				self shellshock( "mp_radiation_low", 4);
				self.radiationSound = "item_geigercouner_level3";
				self stopLoopSound();
				self playLoopSound( self.radiationSound );
				self ViewKick( 3, self.origin );
				self doRadiationDamage(15);
				break;
			case 4:
				self shellshock( "mp_radiation_med", 5);
				self.radiationSound = "item_geigercouner_level3";
				self stopLoopSound();
				self playLoopSound( self.radiationSound );
				self ViewKick( 15, self.origin );
				self thread blackout();
				self doRadiationDamage(25);
				break;
			case 6:
				self shellshock( "mp_radiation_high", 5);
				self.radiationSound = "item_geigercouner_level4";
				self stopLoopSound();
				self playLoopSound( self.radiationSound );
				self ViewKick( 75, self.origin );
				self doRadiationDamage(45);
				break;
			case 8:
				self shellshock( "mp_radiation_high", 5);
				self.radiationSound = "item_geigercouner_level4";
				self stopLoopSound();
				self playLoopSound( self.radiationSound );
				self ViewKick( 127, self.origin );
				self doRadiationDamage(175);

				break;
		}
		wait(1);
	}
	wait(5);
}
blackout( )
{
	self endon( "disconnect" );
	self endon( "game_ended" );
	self endon( "death" );
	self endon( "leftTrigger" );

	if ( !isDefined( self.radiationOverlay ) )
	{
		self.radiationOverlay = newClientHudElem( self );
		self.radiationOverlay.x = 0;
		self.radiationOverlay.y = 0;
		self.radiationOverlay setshader( "black", 640, 480 );
		self.radiationOverlay.alignX = "left";
		self.radiationOverlay.alignY = "top";
		self.radiationOverlay.horzAlign = "fullscreen";
		self.radiationOverlay.vertAlign = "fullscreen";
		self.radiationOverlay.alpha = 0;
	}

	min_length = 1;
	max_length = 2;
	min_alpha = .25;
	max_alpha = 1;

	min_percent = 5;
	max_percent = 100;

	fraction = 0;

	for ( ;; )
	{
		while ( self.poison > 1 )
		{
			percent_range = max_percent - min_percent;
			fraction = ( self.poison - min_percent ) / percent_range;

			if ( fraction < 0 )
				fraction = 0;
			else if ( fraction > 1 )
				fraction = 1;

			length_range = max_length - min_length;
			length = min_length + ( length_range * ( 1 - fraction ) );

			alpha_range = max_alpha - min_alpha;
			alpha = min_alpha + ( alpha_range * fraction );

			end_alpha = fraction * 0.5;

			if ( fraction == 1 )
				break;

			duration = length / 2;

			self.radiationOverlay fadeinBlackOut( duration, alpha );
			self.radiationOverlay fadeoutBlackOut( duration, end_alpha);

			// wait a variable amount based on self.radiation.totalpercent, this is the space in between pulses
			//wait 1;
			wait( fraction * 0.5 );
		}

		if ( fraction == 1 )
			break;

		if ( self.radiationOverlay.alpha != 0 )
			self.radiationOverlay fadeoutBlackOut( 1, 0);

		wait 0.05;
	}
	self.radiationOverlay fadeinBlackOut( 2, 0);
}

doRadiationdamage( iDamage )
{

	self thread [[ level.callbackPlayerDamage ]](
	self,// eInflictor The entity that causes the damage.( e.g. a turret )
	self,// eAttacker The entity that is attacking.
	iDamage,// iDamage Integer specifying the amount of damage done
	0,// iDFlags Integer specifying flags that are to be applied to the damage
	"MOD_SUICIDE",// sMeansOfDeath Integer specifying the method of death
	"claymore_mp",// sWeapon The weapon number of the weapon used to inflict the damage
	self.origin,// vPoint The point the damage is from?
	( 0,0,0 ) - self.origin,// vDir The direction of the damage
	"none",// sHitLoc The location of the hit
	0// psOffsetTime The time offset for the damage
	);
}

fadeinBlackOut( duration, alpha )
{
	self fadeOverTime( duration );
	self.alpha = alpha;
	wait duration;
}

fadeoutBlackOut( duration, alpha )
{
	self fadeOverTime( duration );
	self.alpha = alpha;
	wait duration;
}

