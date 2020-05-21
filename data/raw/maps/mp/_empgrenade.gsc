#include maps\mp\_utility;
#include common_scripts\utility;


init()
{
	precacheShellshock("flashbang_mp");
	thread onPlayerConnect();
}

onPlayerConnect()
{
	for(;;)
	{
		level waittill("connected", player);
		player thread onPlayerSpawned();
	}
}


onPlayerSpawned()
{
	self endon("disconnect");

	for(;;)
	{
		self waittill( "spawned_player" );
		
		self thread monitorEMPGrenade();
	}
}


monitorEMPGrenade()
{
	self endon("death");
	self endon("disconnect");
	self.empEndTime = 0;
	
	while(1)
	{
		self waittill( "emp_grenaded", attacker );
		
		if ( !isalive( self ) )
			continue;
		
		if ( isDefined( self.usingRemote ) )
			continue;

		//MW3 emp resistance perk
		if ( self _hasPerk( "specialty_empimmune" ) )
			continue;
		
		hurtVictim = true;
		hurtAttacker = false;
		
		assert(isdefined(self.pers["team"]));
		
		if (level.teamBased && isdefined(attacker) && isdefined(attacker.pers["team"]) && attacker.pers["team"] == self.pers["team"] && attacker != self)
		{
			if(level.friendlyfire == 0) // no FF
			{
				continue;
			}
			else if(level.friendlyfire == 1) // FF
			{
				hurtattacker = false;
				hurtvictim = true;
			}
			else if(level.friendlyfire == 2) // reflect
			{
				hurtvictim = false;
				hurtattacker = true;
			}
			else if(level.friendlyfire == 3) // share
			{
				hurtattacker = true;
				hurtvictim = true;
			}
		}		
		else if( isDefined(attacker) )
		{
			attacker notify( "emp_hit" );
			if( attacker != self )
				attacker maps\mp\gametypes\_missions::processChallenge( "ch_onthepulse" );
		}

		if ( hurtvictim && isDefined(self) )
			self thread applyEMP();
		if ( hurtattacker && isDefined(attacker) )
			attacker thread applyEMP();
	}
}

applyEMP()
{
	self notify( "applyEmp" );
	self endon( "applyEmp" );
	
	self endon( "death" );
	
	wait .05;
	self.empDuration = 10;
	
	self.empGrenaded = true;
	self shellshock( "flashbang_mp", 1 ); 
	self.empEndTime = getTime() + (self.empDuration * 1000);
	
	self thread empRumbleLoop( .75 );
	self setEMPJammed( true );
	
	self thread empGrenadeDeathWaiter();
	wait ( self.empDuration );
	self notify( "empGrenadeTimedOut" );
	self checkToTurnOffEmp();
}

empGrenadeDeathWaiter()
{
	self notify( "empGrenadeDeathWaiter" );
	self endon( "empGrenadeDeathWaiter" );
	
	self endon( "empGrenadeTimedOut" );
	
	self waittill( "death" );
	self checkToTurnOffEmp();
}

checkToTurnOffEmp()
{
	self.empGrenaded = false;
	
	//dont shut off emp because the team is emp'd
	if ( (level.teamBased && level.teamEMPed[self.team]) || (!level.teamBased && isDefined( level.empPlayer ) && level.empPlayer != self) )
			return;
	
	self setEMPJammed( false );
		
}

empRumbleLoop( duration )
{
	self endon("emp_rumble_loop");
	self notify("emp_rumble_loop");
	
	goalTime = getTime() + duration * 1000;
	
	while ( getTime() < goalTime )
	{
		self PlayRumbleOnEntity( "damage_heavy" );
		wait( 0.05 );
	}
}


isEMPGrenaded()
{
	return isDefined( self.empEndTime ) && gettime() < self.empEndTime;
}
