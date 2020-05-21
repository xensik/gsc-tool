#include maps\mp\_utility;

init()
{
	if (!level.teambased)
		return;
	
	precacheShader("headicon_dead");

	level thread onPlayerConnect();
}

onPlayerConnect()
{
	for(;;)
	{
		level waittill("connected", player);

		player.selfDeathIcons = []; // icons that other people see which point to this player when he's dead
	}
}

updateDeathIconsEnabled()
{
	//if (!self.enableDeathIcons)
	//	self removeOtherDeathIcons();
}

addDeathIcon( entity, dyingplayer, team, timeout )
{
	if ( !level.teambased )
		return;
	
	iconOrg = entity.origin;
	
	dyingplayer endon("spawned_player");
	dyingplayer endon("disconnect");
	
	wait .05;
	WaitTillSlowProcessAllowed();
	
	assert(team == "allies" || team == "axis");
	
	if ( getDvar( "ui_hud_showdeathicons" ) == "0" )
		return;
	if ( level.hardcoreMode )
		return;
	
	if ( isdefined( self.lastDeathIcon ) )
		self.lastDeathIcon destroy();
	
	newdeathicon = newTeamHudElem( team );
	newdeathicon.x = iconOrg[0];
	newdeathicon.y = iconOrg[1];
	newdeathicon.z = iconOrg[2] + 54;
	newdeathicon.alpha = .61;
	newdeathicon.archived = true;
	if ( level.splitscreen )
		newdeathicon setShader("headicon_dead", 14, 14);
	else
		newdeathicon setShader("headicon_dead", 7, 7);
	newdeathicon setwaypoint( false );
	
	self.lastDeathIcon = newdeathicon;
	
	newdeathicon thread destroySlowly ( timeout );
}

destroySlowly( timeout )
{
	self endon("death");
	
	wait timeout;
	
	self fadeOverTime(1.0);
	self.alpha = 0;
	
	wait 1.0;
	self destroy();
}
