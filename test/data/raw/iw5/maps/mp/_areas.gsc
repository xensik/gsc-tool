#include maps\mp\_utility;
#include common_scripts\utility;

/*QUAKED trigger_multiple_area (0.12 0.23 1.0)
defaulttexture="trigger"
"script_area" - A localized string that names the area. e.g. "MP_FLOWER_SHOP"
Defines an area that the player is in.*/

/*QUAKED trigger_multiple_softlanding (0.12 0.23 1.0)
defaulttexture="trigger"
"script_type" - "car", "boxes", "trash"
Defines a soft landing area.*/


init()
{
	level.softLandingTriggers = getEntArray( "trigger_multiple_softlanding", "classname" );

	destructibles = getEntArray( "destructible_vehicle", "targetname" );
	
	foreach ( trigger in level.softLandingTriggers )
	{
		if ( trigger.script_type != "car" )
			continue;
		
		foreach ( destructible in destructibles )
		{
			/*
			if ( !trigger isTouching( destructible ) )
			{
				println( distance( trigger.origin, destructible.origin ) );
				continue;
			}
			*/
			
			if ( distance( trigger.origin, destructible.origin ) > 64.0 )
				continue;
				
			assert( !isDefined( trigger.destructible ) );
				
			trigger.destructible = destructible;
		}	
	}
	
	//foreach ( trigger in level.softLandingTriggers )
	//	trigger thread common_scripts\_dynamic_world::triggerTouchThink( ::playerEnterSoftLanding, ::playerLeaveSoftLanding );
		
	thread onPlayerConnect();
}


onPlayerConnect()
{
	for ( ;; )
	{
		level waittill ( "connected", player );
		
		player.softLanding = undefined;
		
		player thread softLandingWaiter();
	}
}


playerEnterSoftLanding( trigger )
{
	self.softLanding = trigger;
}


playerLeaveSoftLanding( trigger )
{
	self.softLanding = undefined;
}


softLandingWaiter()
{
	self endon ( "disconnect" );
	
	for ( ;; )
	{
		self waittill ( "soft_landing", trigger, damage );
		
		//if ( damage < 10 )
		//	continue;
		
		if ( !isDefined( trigger.destructible ) )
			continue;

		//magicBullet( "mp5_mp", self.origin, self.origin + (0,0,-100), self );

		//self waittill( "damage", damage, attacker, direction_vec, point, type, modelName, tagName, partName, dflags );

		//traceData = bulletTrace( self.origin, self.origin + (0,0,-100), true, self );

	}
}