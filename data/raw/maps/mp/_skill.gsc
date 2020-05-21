#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

init()
{
	level thread onPlayerConnect();
	level thread onPlayerDisconnect();
}

onPlayerConnect()
{
	for(;;)
	{
		level waittill( "connected", player );

		// look at how spawning works
		player.connectTime = getTime();
		player.targets = [];
		
		player thread onWeaponFired();		
		player thread onDeath();
	}
}

onPlayerDisconnect()
{
	for(;;)
	{
		level waittill( "disconnected", player );

		player.targets = [];		
	}
}


onWeaponFired()
{
	level endon( "game_ended" );
	self endon( "disconnected" );

	for ( ;; )
	{
		self waittill( "weapon_fired" );

		// find likely target
		// find target and tag when they shot me.
		//self.target 
	}
}

onDeath()
{
	level endon( "game_ended" );
	self endon( "disconnected" );

	for ( ;; )
	{
		self waittill( "death" );

		//
		// find target and tag when they shot me.
		//self.target 
	}
}


processKill( attacker, defender )
{
	updateSkill( attacker, defender, "war", 1.0 );
}