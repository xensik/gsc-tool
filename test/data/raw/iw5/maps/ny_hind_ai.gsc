#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_audio;
#include maps\_vehicle;
#include maps\_helicopter_globals;
#include maps\_hud_util;
#include maps\_shg_common;
#include maps\ny_hind;


//*****************************************************************************************
// Pseudo Heli Turret AI
nym_burst_fire_settings( setting )
{
	if ( setting == "delay" )
		return 0.2;
	else
	if ( setting == "delay_range" )
		return 0.5;
	else
	if ( setting == "burst" )
		return 0.5;
	else
//	if (setting == "burst_range")
		return 1.5;
}

nym_cleanup_tt()
{
	self waittill("death");
	self.turret_target Delete();
	self.turret_target = undefined;
}

nym_hind_turret_target_around_player()
{
	if (!isdefined(self))
		return;
	assert(!isdefined(self.turret_target));	// ensure we haven't called it twice
	self endon("death");
	level.player_hind endon("death");
	self.turret_target = spawn_tag_origin();
	self thread nym_cleanup_tt();
	turtgt = self.turret_target;
	turtgt.origin = level.player_hind.origin;
	curangle=0;
	self.main_turret["around_dangle"] = 360/(20*3);	// 3 seconds for a complete once around
	self.main_turret["around_radius"] = 120;
	self.main_turret["target"] = turtgt;
	self.main_turret["aimspeed"] = 80;
	while (true)
	{
		// orbit the tgt around the origin perpindicular to a vec from the shooter to the player_hind
		ref_origin = 0.5 * (level.player GetEye() + level.player.origin);
		//ref_origin = level.player GetEye();

		to_player_hind = ref_origin - self.origin;
		to_player_hind = VectorNormalize(to_player_hind);
		perp_to_ph = VectorCross(to_player_hind,(0,0,1));
		cs = cos(curangle);
		sn = sin(curangle);
		dir = cs * perp_to_ph + sn * (0,0,1);
		turtgt.origin = ref_origin + self.main_turret["around_radius"]*dir;
		curangle += self.main_turret["around_dangle"];
		if (curangle > 360)
			curangle -= 360;
		wait 0.05;
	}
}

nym_hind_turret_punish_player()
{
	if (!isdefined(self))
		return;
	self.main_turret["target"] = level.player;
	self.main_turret["mintimebtnfires"] = 0.1;
	self.main_turret["maxtimebtnfires"] = 0.5;

	self.main_turret["aimspeed"] = 80;
	self.main_turret["aimcount"] = 120;
	
	self.main_turret["sweepspeed"] = 10;
	self.main_turret["sweepcount"] = 0;

	self.main_turret["delay"] = 0.0;
	self.main_turret["delayrange"] = 0.1;
	
	self.main_turret["burst"] = 0.5;
	self.main_turret["burstrange"] = 1.5;
	self notify("turretstatechange");
}

nym_disallow_shooting()
{
	if (!isdefined(self))
		return;
	self.main_turret["delay"] = 120.0;
	self.main_turret["delayrange"] = 0.1;
	
	self.main_turret["burst"] = 0.0;
	self.main_turret["burstrange"] = 0.0;
	
	self.main_turret["mintimebtnfires"] = 10000;
	self.main_turret["maxtimebtnfires"] = 10000;
	
	self notify("turretstatechange");
}

nym_Hind_Turret_AI()
{
	self endon( "death" );
	self endon( "stop_ai");
	nym_hind_default_turret();
	self thread nym_hind_burst_fire_unmanned();
	self thread nym_Hind_Aiming();

	while (true)
	{
		t = RandomFloatRange( self.main_turret["mintimebtnfires"], self.main_turret["maxtimebtnfires"]);
		wait t;
		self.is_firing =true;
		self waittill("turretstatechange");
		wait 0.05;
	}
}

nym_Hind_burst_fire_unmanned()
{
	self endon( "death" );
	self endon( "stop_ai");
	self endon( "stop_burst_fire_unmanned" );
	
	pauseUntilTime = gettime();
	turretState = "start";
	self.is_firing = false;

	for ( ;; )
	{
		duration = ( pauseUntilTime - gettime() ) * 0.001;
		if ( self.is_firing && ( duration <= 0 ) )
		{
			if ( turretState != "fire" )
			{
				turretState = "fire";
				thread nym_Hind_DoShoot();
			}

			duration = self.main_turret["burst"] + randomfloat( self.main_turret["burstrange"] );

			//println("fire duration: ", duration);
			thread nym_Hind_TurretTimer( duration );

			self waittill( "turretstatechange" );// code or script

			duration = self.main_turret["delay"] + randomfloat( self.main_turret["delayrange"] );
			//println("stop fire duration: ", duration);

			pauseUntilTime = gettime() + int( duration * 1000 );
		}
		else
		{
			if ( turretState != "aim" )
			{
				turretState = "aim";
			}

			//println("aim duration: ", duration);
			if (duration <= 0)
				duration = 0.1;
			thread nym_Hind_TurretTimer( duration );

			self waittill( "turretstatechange" );// code or script
		}
	}
}

nym_hind_default_turret()
{
	if (!isdefined(self))
		return;
	self.main_turret["mintimebtnfires"] = .5;
	self.main_turret["maxtimebtnfires"] = 4;

	self.main_turret["aimspeed"] = 40;
	self.main_turret["aimcount"] = 120;
	
	self.main_turret["sweepspeed"] = 10;
	self.main_turret["sweepcount"] = 60;
	
	self.main_turret["state"] = "aiming";
	self.main_turret["oldstate"] = "xxxx";
	
	self.main_turret["delay"] = 0.2;
	self.main_turret["delayrange"] = 0.5;
	
	self.main_turret["burst"] = 0.5;
	self.main_turret["burstrange"] = 1.5;
	
	self.main_turret["target"] = level.player;
}

nym_hind_change_turret_state( state )
{
	if (!isdefined(self))
		return;
	self.main_turret["state"] = state;
}

nym_Hind_Aiming()
{
	self endon( "stop_ai");
	if (!isdefined(self.main_turret))
	{
		assertex(false, "main_turret settings must be initialized before hind ai can be run" );
		return;
	}
	self endon( "death" );
	forward = AnglesToForward( self.angles );
	prvTarget = self.origin + 1200*forward;
	count = 0;
	debug = false;
	
	while (true)
	{
		/#
		if (debug)
		{
			color = (1, 0, 0);
			if (self.main_turret["state"] == "sweeping")
				color = (0, 0, 1);
			if (self.main_turret["state"] == "idle")
				color = (0, 1, 0);
			draw_point( prvTarget, 24, color);
		}
		#/
		self SetTurretTargetVec( prvTarget );
		if (self.main_turret["oldstate"] != self.main_turret["state"])
		{
			count = 0;
			self.main_turret["oldstate"] = self.main_turret["state"];
		}
		count++;
		if (self.main_turret["state"] == "sweeping")
		{
			len = distance(level.player.origin, self.origin);
			forward = AnglesToForward( self.angles );
			target = self.origin + len*forward;
			delta = target - prvTarget;
			len = distance(target, prvTarget);
			delta = VectorNormalize(delta);
			if (len > self.main_turret["aimspeed"])
				len = self.main_turret["aimspeed"];
			prvTarget = prvTarget + len*delta;
			if (count > self.main_turret["sweepcount"])
			{
				count = 0;
				self.main_turret["state"] = "aiming";
			}
		}
		else if (self.main_turret["state"] == "aiming")
		{
			ent = self.main_turret["target"];
			if (!isdefined(ent) || (isAI(ent) && !isAlive(ent)))
			{
				self.main_turret["state"] = "idle";
				continue;
			}
			if (isAI(ent) || isPlayer(ent))
				target = 0.5 * (ent GetEye() + ent.origin);
			else
				target = ent.origin;
			delta = target - prvTarget;
			len = distance(target, prvTarget);
			delta = VectorNormalize(delta);
			if (len > self.main_turret["aimspeed"])
				len = self.main_turret["aimspeed"];
			prvTarget = prvTarget + len*delta;
			if (count > self.main_turret["aimcount"])
			{
				count = 0;
				self.main_turret["state"] = "sweeping";
			}
		}
		else
		{	// idle
			forward = AnglesToForward( self.angles );
			prvTarget = self.origin + 1200*forward;
			count = 0;	// ensure this is correct if we change states
		}
		wait 0.05;
	}
}

nym_Hind_StopShooting()
{
	self waittill( "turretstatechange" );
	self.is_firing = false;
}

nym_Hind_DoShoot()
{
	self endon( "death" );
	self endon( "stop_ai");
	self endon( "turretstatechange" );// code or script
	self thread nym_Hind_StopShooting();
	
	weaponName = "hind_turret";

	for ( ;; )
	{
		self setVehWeapon( weaponName );
		self fireWeapon( );
		self.is_firing = true;
		wait 0.1;
	}
}

nym_Hind_TurretTimer( duration )
{
	if ( duration <= 0 )
		return;

	self endon( "turretstatechange" );// code
	self endon( "stop_ai");

	//println("start turret timer");

	wait duration;
	if ( isdefined( self ) )
		self notify( "turretstatechange" );

	//println("end turret timer");
}
