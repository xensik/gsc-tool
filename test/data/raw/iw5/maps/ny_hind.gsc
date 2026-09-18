#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;
#include maps\_shg_common;

CONST_MPHTOIPS = 17.6;


clear_path_type()
{
	if (isdefined(self.curpathtype))
		return;	// thread is already running for this self
	self endon("death");
	self.curpathtype = "none";
	while (true)
	{
		self waittill("reached_dynamic_path_end");
		if (self.curpathtype == "smooth")
			self.lastpathnode = self.curNode;
		else if (self.curpathtype == "normal")
			self.lastpathnode = self.currentNode;
		else
			self.lastpathnode = undefined;
		self.curpathtype="none";
	}
}

/*
	prvpoint is our previous waypoint.  If undefined, then prvpoint is set to be self.origin
	curpoint is our current target waypoint
	nxtpoint is the next target waypoint
	lookahead is in seconds, how far ahead to look
	returns a point to go towards at based on the params
*/

get_lookahead_point( prvnode, curnode, nxtnode, lookahead)
{
	pathdist = 0;
	pathlen = 0;
	prvpoint = self.origin;
	speed = self Vehicle_GetSpeed() * CONST_MPHTOIPS;
	if (!isdefined(prvnode))
	{
		pathdist = 0;
		deltapath = curnode.origin - self.origin;
		pathlen = Length(deltapath);
		deltapath = VectorNormalize(deltapath);
	}
	else
	{
		prvpoint = prvnode.origin;
		origin = self.origin;
		deltapath = curnode.origin - prvnode.origin;
		pathlen = Length(deltapath);
		deltapath = VectorNormalize(deltapath);
		deltaorigin = origin - prvnode.origin;
		pathdist = VectorDot(deltapath, deltaorigin);
	
		if (pathdist < 0)
			pathdist = 0;
	}
		
	lookaheadlen = speed*lookahead;
	pathdist += lookaheadlen;
	
	// see if our lookahead point is before nxtpoint
	lookaheadpoint = prvpoint + pathdist*deltapath;
	while (pathdist >= pathlen)
	{
		pathdist -= pathlen;
		if (!isdefined(nxtnode))
		{	// just make the goal curnode
			lookaheadpoint = curnode.origin;
			pathdist = 0;
		}
		else
		{
			deltanext = nxtnode.origin - curnode.origin;
			pathlen = Length(deltanext);
			if (pathdist < pathlen)
			{	// point is between cur and nxt
				deltanext = pathdist * VectorNormalize(deltanext);
				lookaheadpoint = curnode.origin + deltanext;
			}
			else
			{	// path is between next nodes
				prvnode = curnode;
				curnode = nxtnode;
				if (isdefined(nxtnode.target))
				{
					nxtnode = getstruct(nxtnode.target, "targetname");
				}
				else
				{
					nxtnode = undefined;
				}
			}
		}
	}
	return lookaheadpoint;
}

smooth_vehicle_path_node_reached( nextpoint )
{
	// this handling code is taken straight from _vehicle.gsc
	if ( IsDefined( nextpoint.script_prefab_exploder ) )
	{
		nextpoint.script_exploder = nextpoint.script_prefab_exploder;
		nextpoint.script_prefab_exploder = undefined;
	}

	if ( IsDefined( nextpoint.script_exploder ) )
	{
		delay = nextpoint.script_exploder_delay;
		if ( IsDefined( delay ) )
		{
			level delayThread( delay, ::exploder, nextpoint.script_exploder );
		}
		else
		{
			level exploder( nextpoint.script_exploder );
		}
	}

	if ( IsDefined( nextpoint.script_flag_set ) )
	{
		if ( IsDefined( self.vehicle_flags ) )
			self.vehicle_flags[ nextpoint.script_flag_set ] = true;
		self notify( "vehicle_flag_arrived", nextpoint.script_flag_set );
		flag_set( nextpoint.script_flag_set );
	}

	if ( IsDefined( nextpoint.script_ent_flag_set ) )
	{
		self ent_flag_set( nextpoint.script_ent_flag_set );
	}

	if ( IsDefined( nextpoint.script_ent_flag_clear ) )
	{
		self ent_flag_clear( nextpoint.script_ent_flag_clear );
	}

	if ( IsDefined( nextpoint.script_flag_clear ) )
	{
		if ( IsDefined( self.vehicle_flags ) )
			self.vehicle_flags[ nextpoint.script_flag_clear ] = false;
		flag_clear( nextpoint.script_flag_clear );
	}

	if ( IsDefined( nextpoint.script_noteworthy ) )
	{
		if ( nextpoint.script_noteworthy == "kill" )
			self force_kill();
		if ( nextpoint.script_noteworthy == "godon" )
			self godon();
		if ( nextpoint.script_noteworthy == "godoff" )
			self godoff();
		if ( nextpoint.script_noteworthy == "deleteme" )
		{
			level thread deleteent( self );
			return;// this could be disasterous
		}
	}

	if ( IsDefined( nextpoint.script_crashtypeoverride ) )
		self.script_crashtypeoverride = nextpoint.script_crashtypeoverride;
	if ( IsDefined( nextpoint.script_badplace ) )
		self.script_badplace = nextpoint.script_badplace;
	if ( IsDefined( nextpoint.script_turretmg ) )
		self.script_turretmg = nextpoint.script_turretmg;
	if ( IsDefined( nextpoint.script_team ) )
		self.script_team = nextpoint.script_team;
	if ( IsDefined( nextpoint.script_turningdir ) )
		self notify( "turning", nextpoint.script_turningdir );

	if ( IsDefined( nextpoint.script_deathroll ) )
		if ( nextpoint.script_deathroll == 0 )
			self thread deathrolloff();
		else
			self thread deathrollon();

}

smooth_vehicle_path_set_lookahead( lookahead )
{
	self.lookahead = lookahead;
}

smooth_vehicle_path_set_override_speed( speed, accel, decel )
{
	if ((speed > self.veh_speed) && (speed < accel))
		accel = speed;	// cap it here to avoid warnings from code
	self.override_speed = speed;
	self.override_accel = accel;
	self.override_decel = decel;
	self Vehicle_SetSpeed( speed, accel, decel );
}

smooth_vehicle_path_clear_override_speed()
{
	if (isdefined(self.override_speed))
		self.override_speed = undefined;
	if (isdefined(self.override_accel))
		self.override_accel = undefined;
	if (isdefined(self.override_decel))
		self.override_decel = undefined;
}

smooth_vehicle_path_SetTargetYaw( yaw )
{
	while (yaw < -180)
		yaw += 360;
	while (yaw > 180)
		yaw -= 360;
	self.targetyawset = yaw;
	self SetTargetYaw(yaw);
}

smooth_vehicle_path_ClearTargetYaw( )
{
	self.targetyawset = undefined;
	self ClearTargetYaw();
}

smooth_vehicle_debug_node( )
{
	/#
	self endon("newpath");
	while (true)
	{
		if (isdefined(self.debug_smooth_path) && self.debug_smooth_path)
		{
			if (isdefined(self.curnode_set))
				draw_point( self.curnode_set.origin, 24, (1,0,1));
		}
		wait 0.05;
	}
	#/
}

ny_start_heli_path( startnode, lookahead, radius)
{
	self.curpathstart = startnode.targetname;
	if (test_if_smooth_path( startnode ))
	{
		self thread clear_path_type();
		self thread smooth_vehicle_path( startnode, lookahead, radius );
		self.curpathtype = "smooth";
	}
	else
	{
		self thread clear_path_type();
		self thread vehicle_paths( startnode );
		self.curpathtype = "normal";
	}
}

test_if_smooth_path(startnode)
{
	if (isdefined(startnode.spawnflags) && (startnode.spawnflags & 2))
		return true;
	return false;
}

smooth_vehicle_setgoal( tgt_point, endOfPath )
{
	self.curnode_set = self.curnode;
	if ( IsDefined( self.prvnode ) )
	{	// change these params after we've gone by the node
		airResistance = self.prvnode.script_airresistance;
		speed = self.prvnode.speed;
		accel = self.prvnode.script_accel;
		decel = self.prvnode.script_decel;
	}
	else
	{
		airResistance = undefined;
		speed = undefined;
		accel = undefined;
		decel = undefined;
	}
	if (isdefined(self.override_speed))
	{
		speed = self.override_speed;
		accel = self.override_accel;
		decel = self.override_decel;
	}
	if (IsDefined( self.curnode.lookahead) )
		lookahead = self.curnode.lookahead;
	if (IsDefined( self.curnode.radius) )
		radius = self.curnode.radius;
	// Dealing with stopnode, unload, flag_wait, and endOfPath may need some work to act correctly
	stopnode = IsDefined( self.curnode.script_stopnode ) && self.curnode.script_stopnode;
	unload = IsDefined( self.curnode.script_unload );
	flag_wait = ( IsDefined( self.curnode.script_flag_wait ) && !flag( self.curnode.script_flag_wait ) ); // // if the flag gets set during flight, we should update the setvehgoalpos to not stop
	hasDelay = IsDefined( self.curnode.script_delay );
	if ( IsDefined( self.curnode.angles ) )
		yaw = self.curnode.angles[ 1 ];
	else
		yaw = 0;

	self Vehicle_HeliSetAI( tgt_point, speed, accel, decel, self.curnode.script_goalyaw, self.curnode.script_anglevehicle, yaw, airResistance, hasDelay, stopnode, unload, flag_wait, endOfPath );
	// store some info to help following
	self.smooth_tgt_point = tgt_point;
	self.smooth_speed = speed;
	self.smooth_accel = accel;
	self.smooth_decel = decel;
	if ((!isdefined(self.curnode.script_goalyaw) || !self.curnode.script_goalyaw) && isdefined(self.targetyawset))
	{	// since the vehicle_helisetai call will ClearTargetYaw, we set it again here
		self SetTargetYaw( self.targetyawset );
	}
	//self SetVehGoalPos( tgt_point, 0 );
	/#
	self UpdateCapturePath();
	#/
}

smooth_vehicle_path( node, lookahead, radius )
{
	self notify("newpath");
	self endon("newpath");
	/#
	self thread smooth_vehicle_debug_node();
	#/
	self smooth_vehicle_path_clear_override_speed();
	self.lookahead = lookahead;
	self.prvnode = undefined;
	self.curnode = node;
	self.nxtnode = undefined;
	if (isdefined(self.curnode.target))
		self.nxtnode = getstruct(self.curnode.target, "targetname");
	while (isdefined(self.curnode))
	{
		curpoint = self.curnode.origin;
		if ( IsDefined( self.heliheightoverride ) )
			curpoint = ( curpoint[0], curpoint[1], self.heliheightoverride );	// this is used to force the z of the helipath
		dist = Length(curpoint - self.origin);
		tgt_point = get_lookahead_point( self.prvnode, self.curnode, self.nxtnode, self.lookahead);
		if ( IsDefined( self.heliheightoverride ) )
			tgt_point = ( tgt_point[0], tgt_point[1], self.heliheightoverride );	// this is used to force the z of the helipath
		// get the distance for closest point from origin to tgt_point of curpoint
		org2tgt = self.origin - tgt_point;
		org2tgt_n = VectorNormalize(org2tgt);
		org2cur = self.origin - curpoint;
		if (!isdefined(self.nxtnode))
			dist2cur = radius + 10;
		else
			dist2cur = VectorDot(org2tgt_n, org2cur);
		if ((dist < radius) || (dist2cur < radius))
		{	// reached next point
			smooth_vehicle_path_node_reached( self.curnode );
			if (!isdefined(self.nxtnode) && isdefined(self.curnode))
			{	// this last call we treat as the endOfPath
				self smooth_vehicle_setgoal( self.curnode.origin, 1 );
			}
			self.prvnode = self.curnode;
			self.curnode = self.nxtnode;
			self.nxtnode = undefined;
			if (isdefined(self.curnode) && isdefined(self.curnode.target))
				self.nxtnode = getstruct(self.curnode.target, "targetname");
		}
		else
		{
			/#
			if (isdefined(self.debug_smooth_path) && self.debug_smooth_path)
			{
				if (isdefined(self.prvnode))
					draw_point( self.prvnode.origin, 24, (0,0,1));
				if (isdefined(self.curnode))
					draw_point( self.curnode.origin, 24, (1,0,0));
				if (isdefined(self.nxtnode))
					draw_point( self.nxtnode.origin, 24, (0,1,0));
				draw_point( tgt_point, 24, (1,1,1));
			}
			#/
			self smooth_vehicle_setgoal( tgt_point, 0 );
			wait 0.05;
		}
	}
	self StopCapturePath();
	
	if ( IsDefined(self.prvnode) && IsDefined( self.prvnode.script_land ) )
		self thread vehicle_landvehicle();

	self notify( "reached_dynamic_path_end" );

	if ( IsDefined(self.prvnode) && IsDefined( self.prvnode.script_vehicle_selfremove ) )
		self Delete();
}

smooth_vehicle_show_switch( startnode, newnode, forward )
{
	/#
	self notify("stop_show_switch");
	self endon("stop_show_switch");
	selfstart = self.origin;
	while (true)
	{
		// draw the path
		prvnode = undefined;
		node = startnode;
		looped = false;
		while (isdefined(node))
		{
			if (isdefined(prvnode))
				line(prvnode.origin, node.origin, (1,1,1));
			if (looped)
				break;
			prvnode = node;
			if (isdefined(node.target))
				node = getstruct(node.target,"targetname");
			else
				node = undefined;
			if (isdefined(node))
			{
				if (node == startnode)
				{
					looped = true;
				}
			}
		}
		// draw from the current location to the newnode
		line(selfstart, newnode.origin, (1,0,0));
		// draw the forward direction from the time we chose the node
		line(selfstart, selfstart + 120*forward, (1,1,0));
		wait 0.05;
	}
	#/
}

smooth_vehicle_switch_path( startnode, lookahead, radius, force_smooth, force_normal )
{
	// find the closest point within this new path that's in front of the vehicle
	node = startnode;
	if (isdefined(startnode.target))
	{
		node = getstruct(startnode.target, "targetname");
		if (!isdefined(node))
			node = startnode;
	}
	nodes[0] = startnode;
	while (node != startnode)
	{
		nodes[nodes.size] = node;
		if (isdefined(node.target))
		{
			node = getstruct(node.target, "targetname");
			if (!isdefined(node))
				break;
		}
		else
			break;
	}
	// now we have a list of all of the nodes, so find the closest one that is also in front
	origin = self.origin;
	//forward = AnglesToForward(self.angles);
	if (!isdefined(self.curpathtype))
	{
		forward = self Vehicle_GetVelocity();	// use the velocity as forward
	}
	else if ((self.curpathtype == "normal") && (isdefined(self.currentnode)))
	{	// if we have a currentNode and are still on a path, use it as our forward reference
		forward = self.origin - self.currentnode.origin;
	}
	else if ((self.curpathtype == "smooth") && (isdefined(self.curnode)))
	{	// if we have a currentNode and are still on a path, use it as our forward reference
		forward = self.origin - self.curnode.origin;
	}
	else
		forward = self Vehicle_GetVelocity();	// use the velocity as forward
	
	forward = VectorNormalize(forward);
	bestnode = undefined;
	bestwdist = 1000000;
	closestnode = undefined;
	closestdist = 1000000;
	foreach (node in nodes)
	{
		org2node = node.origin - origin;
		org2node_n = VectorNormalize(org2node);
		dp = VectorDot(org2node_n,forward);
		dist = Length(org2node);
		if (dp > 0)
		{
			wdist = (1 - dp) * dist;	// weight the distance so the closer to in front the better
			if (wdist < bestwdist)
			{
				bestnode = node;
				bestwdist = wdist;
			}
		}
		if (dist < closestdist)
		{
			closestnode = node;
			closestdist = dist;
		}
	}
	if (!isdefined(bestnode))
		bestnode = closestnode;
	self.curpathstart = bestnode.targetname;
//self thread smooth_vehicle_show_switch( startnode, bestnode, forward );
	if (isdefined(force_smooth) || (test_if_smooth_path( startnode ) && !isdefined(force_normal)))
	{
		self thread clear_path_type();
		self thread smooth_vehicle_path( bestnode, lookahead, radius );
		self.curpathtype = "smooth-s";
	}
	else
	{
		self thread clear_path_type();
		self thread vehicle_paths( bestnode );
		self.curpathtype = "normal-s";
	}
}


adjust_follow_offset_angoff( offset, angoff, t )
{
	assert(isdefined(self.follow_offset));
	self notify("stop_adjust");
	self endon("stop_adjust");
	self endon("death");
	dt = 1;
	count = 0;
	if (t > 0)
	{
		dt = 0.05/t;
		count = int(t/0.05);
	}	
	doff = dt*(offset - self.follow_offset);
	dang = dt*(angoff - self.follow_angoff);
	while (count > 0)
	{
		self.follow_offset += doff;
		self.follow_angoff += dang;
		count--;
		wait 0.05;
	}
	self.follow_offset = offset;
	self.follow_angoff = angoff;
}

// 0 = off, 1 = self, 2 = enemy
set_useVelAng( whoseVel )
{
	self.follow_useVelAng = whoseVel;
}

/*
	follow an enemy, trying to stay offset behind it
*/
follow_enemy_vehicle( enemy, offset, angoff, useVelAng )
{
	self notify("newpath");
	self endon("newpath");
	enemy endon("death");
	self endon("death");
	
	self thread clear_path_type();
	self.curpathtype = "follow";
	self.curpathstart = undefined;
		
	predicttime = 0.0;	// used to project the goal forward for better behavior from the internal path system
	self.follow_offset = offset;	// allows external code to adjust
	self.follow_angoff = angoff;
	self.follow_useVelAng = useVelAng;
	while (true)
	{
		offset = self.follow_offset;
		tgtpos = enemy.origin;
		tgtvel = enemy Vehicle_GetVelocity();
		ourvel = self Vehicle_GetVelocity();
		tgtspeed = enemy Vehicle_GetSpeed();
		tgtforward = VectorNormalize(tgtvel);
		tgtright = VectorCross((0, 0, 1), tgtforward);
		tgtright = VectorNormalize(tgtright);
		tgtup = VectorCross( tgtforward, tgtright );
		tgtup = VectorNormalize( tgtup );
		goal = tgtpos + offset[0] * tgtforward + offset[1] * tgtright + offset[2] * tgtup;
		err = goal - self.origin;
		errdist = Length(err);
	/* original version */
		dist = Length(self.origin - tgtpos);
		idealdist = Length(offset);
		offdir = VectorNormalize(offset);
		dp = VectorDot(tgtforward,err);	// dp > 0 => we need to speedup, 
		speed = tgtspeed;
		if (dp > 0)
		{ // speedup
			threshdist = 1.5*Length(offset);
			basespeedup = 1.0;
			if (errdist > threshdist)
			{
				speed = (1.0 + basespeedup) * speed;
				accel = speed;
				decel = speed;
			}
			else
			{
				scale =  1.0 + (basespeedup*errdist/threshdist);
				speed = scale * speed;
				accel = 0.75 * speed;
				decel = 0.75 * speed;
			}
		}
		else
		{	// slowdown
			threshdist = Length(offset);
			if (offset[0] <= 0)
				baseslowdown= 0.95;
			else
				baseslowdown= 0.75;
			if (errdist > threshdist)
			{
				scale = baseslowdown*threshdist/errdist;
				speed = scale * speed;
				accel = speed;
				decel = speed;
			}
			else
			{
				errscale = 1.0 - errdist/threshdist;
				speed = (baseslowdown + errscale*(1-baseslowdown))  * speed;
				accel = 0.75 * speed;
				decel = 0.75 * speed;
			}
		}
		predicttime = 1.0;
		
	/*
		if (errdist > 600)	// 50ft
		{	// if far enough away, we'll try to close as fast as we can
			speed = 2*tgtspeed;
		}
		else
		{	// use prediction
			predictt = errdist / tgtspeed;	// how long it would take to cross the distance at enemy's current speed
			velfollow = (1.0/predictt) * err + ourvel;	// ideal velocity to match velocities at some future time
			speed = Length(velfollow);
			goal = goal + predictt * tgtvel;	// we target a point at the time when we want to be matching vel.
		}		
	*/	
		self Vehicle_SetSpeed( speed, accel, decel );
		
		if (isdefined(self.follow_useVelAng) && (self.follow_useVelAng > 0))
		{
			// get the yaw based on the current velocity
			if (self.follow_useVelAng == 1)
				velocity = self Vehicle_GetVelocity();
			else
				velocity = enemy Vehicle_GetVelocity();
			mag = Length(velocity);	// ips
			if (mag > 24)
			{	// don't change the yaw if we have a low velocity
				forwyaw = VectorToYaw( velocity );
				self smooth_vehicle_path_SetTargetYaw ( forwyaw + self.follow_angoff );
			}
		}
		else
		{
			playeryaw = VectorToYaw ( enemy.origin - (level.player GetEye()) );
			self smooth_vehicle_path_SetTargetYaw ( playeryaw + self.follow_angoff );
		}
		
		pgoal = goal + predicttime*tgtvel;
		self SetVehGoalPos( pgoal );
		/#
		self UpdateCapturePath();
		if (isdefined(self.debug_follow) && self.debug_follow)
		{
			iprintln("tgtspeed="+tgtspeed);
			iprintln("speed   ="+speed);
			draw_point( goal, 24, (1,0,0));
			draw_point( pgoal, 24, (1,1,0));
			line( tgtpos, tgtpos + tgtvel, (0,0,1));
		}
		#/
		wait 0.05;
	}
}

follow_enemy_vehicle_thats_using_smoothpath( enemy, offset, angoff, useVelAng )
{
	self notify("newpath");
	self endon("newpath");
	enemy endon("death");
	self endon("death");
	
	self thread clear_path_type();
	self.curpathtype = "followsm";
	self.curpathstart = undefined;
	
	self.follow_offset = offset;	// allows external code to adjust
	self.follow_angoff = angoff;
	self.follow_useVelAng = useVelAng;
	while (true)
	{
		offset = self.follow_offset;
		tgtpos = enemy.origin;
		tgtvel = enemy Vehicle_GetVelocity();
		tgtspeed = enemy Vehicle_GetSpeed();
		tgtforward = VectorNormalize(tgtvel);
		tgtright = VectorCross((0, 0, 1), tgtforward);
		tgtright = VectorNormalize(tgtright);
		tgtup = VectorCross( tgtforward, tgtright );
		tgtup = VectorNormalize( tgtup );
		
		tgt_point = enemy.smooth_tgt_point;
		tgt_speed =	enemy.smooth_speed;
		tgt_accel =	enemy.smooth_accel;
		tgt_decel =	enemy.smooth_decel;

		curoff = offset[0] * tgtforward + offset[1] * tgtright + offset[2] * tgtup;
		tgt_goal = tgt_point + curoff;
		goal = tgtpos + curoff;
		err = goal - self.origin;
		errdist = Length(err);
		dist = Length(self.origin - tgtpos);
		idealdist = Length(offset);
		offdir = VectorNormalize(offset);
		dp = VectorDot(tgtforward,err);	// dp > 0 => we need to speedup, 
		speed = tgtspeed;
		if (dp > 0)
		{ // speedup
			threshdist = 1.5*Length(offset);
			basespeedup = 1.0;
			if (errdist > threshdist)
			{
				speed = (1.0 + basespeedup) * speed;
				accel = speed;
				decel = speed;
			}
			else
			{
				scale =  1.0 + (basespeedup*errdist/threshdist);
				speed = scale * speed;
				accel = 0.75 * speed;
				decel = 0.75 * speed;
			}
		}
		else
		{	// slowdown
			threshdist = Length(offset);
			if (offset[0] <= 0)
				baseslowdown= 0.95;
			else
				baseslowdown= 0.75;
			if (errdist > threshdist)
			{
				scale = baseslowdown*threshdist/errdist;
				speed = scale * speed;
				accel = speed;
				decel = speed;
			}
			else
			{
				errscale = 1.0 - errdist/threshdist;
				speed = (baseslowdown + errscale*(1-baseslowdown))  * speed;
				accel = 0.75 * speed;
				decel = 0.75 * speed;
			}
		}
		self Vehicle_SetSpeed( speed, speed, speed );
		
		if (isdefined(self.follow_useVelAng) && (self.follow_useVelAng > 0))
		{
			// get the yaw based on the current velocity
			if (self.follow_useVelAng == 1)
				velocity = self Vehicle_GetVelocity();
			else
				velocity = enemy Vehicle_GetVelocity();
			mag = Length(velocity);	// ips
			if (mag > 24)
			{	// don't change the yaw if we have a low velocity
				forwyaw = VectorToYaw( velocity );
				self smooth_vehicle_path_SetTargetYaw ( forwyaw + self.follow_angoff );
			}
		}
		else
		{
			playeryaw = VectorToYaw ( enemy.origin - (level.player GetEye()) );
			self smooth_vehicle_path_SetTargetYaw ( playeryaw + self.follow_angoff );
		}
		
		self SetVehGoalPos( tgt_goal );
		/#
		self UpdateCapturePath();
		if (isdefined(self.debug_follow) && self.debug_follow)
		{
			iprintln("tgtspeed="+tgtspeed);
			iprintln("speed   ="+speed);
			draw_point( goal, 24, (1,0,0));
		}
		#/
		wait 0.05;
	}
}

eval_bezier( pts, t)
{
	omt = 1-t;
	switch(pts[4])
	{
		case 1:
			return pts[0] + t*(pts[3] - pts[0]);
		case 3:
			omt2 = omt*omt;
			omt3 = omt*omt2;
			t2 = t*t;
			t3 = t*t2;
			return omt3*pts[0] + 3*omt2*t*pts[1] + 3*omt*t2*pts[2] + t3*pts[3];
	}
}

determine_dir(P0, P3, tangent)
{
	tween = P3 - P0;
	dist = Length(tween);
	dp = VectorDot(VectorNormalize(tween),tangent);
	if (dp != 0)
	{
		len = 0.5*dist/dp;
		return len*tangent;
	}
	else
	{
		len = 0.5*dist;
		return len*tangent;
	}
}

bezier_points( origin, prvprvpos, prvnode, curnode, nxtnode)
{
	pts[4] = 3;
	pts[3] = curnode.origin;
	if (isdefined(prvnode))
	{
		pts[0] = prvnode.origin;
		if (isdefined(nxtnode))
		{	// tangent at curnode is in dir of pts[0] to nxtnode.origin
			tangent = VectorNormalize(nxtnode.origin - pts[0]);
			pts[2] = pts[3] - determine_dir(pts[0], pts[3], tangent);
			if (isdefined(prvprvpos))
			{
				tangent = VectorNormalize(curnode.origin - prvprvpos);
				pts[1] = pts[0] + determine_dir(pts[0], pts[3], tangent);
			}
			else
			{
				pts[1] = pts[2];
			}
		}
		else
		{	// no nxtnode, but there is a prvnode
			if (isdefined(prvprvpos))
			{
				tangent = VectorNormalize(curnode.origin - prvprvpos);
				pts[1] = pts[0] + determine_dir(pts[0], pts[3], tangent);
				pts[2] = pts[1];
			}
			else
			{	// no nxtnode, and no prvprvpos, so linear between prvnode and curnode
				pts[4] = 1;
			}
		}
	}
	else
	{	// no prvnode
		pts[0] = origin;
		if (!isdefined(nxtnode))
		{	// use linear
			pts[4] = 1;
		}
		else
		{	// there is a nxtnode
			tangent = VectorNormalize(nxtnode.origin - pts[0]);
			pts[2] = pts[3] - determine_dir(pts[0], pts[3], tangent);
			pts[1] = pts[2];
		}
	}
	return pts;
}

bezier_length(pts)
{
	if (pts[4] == 1)
		dist = Length(pts[3] - pts[0]);	// inches
	else
	{
		dist = 0;
		step = 0.05;
		prvpoint = eval_bezier( pts, 0.0);
		for (t=step; t <= 1.0; t += step)
		{
			curpoint = eval_bezier( pts, t );
			dist += Length(curpoint - prvpoint);
			prvpoint = curpoint;
		}
		return dist;
	}
}


bezier_vehicle_path( node, lookahead, radius )
{
	self endon("newpath");
	/#
	self thread smooth_vehicle_debug_node();
	self StartDebugPath();
	#/
	self thread clear_path_type();
	self.curpathtype = "bezier";
	self.curpathstart = node.targetname;
	
	self.lookahead = lookahead;
	startorigin = self.origin;
	self.prvprvpos = undefined;
	self.prvnode = undefined;
	self.curnode = node;
	self.nxtnode = undefined;
	if (isdefined(self.curnode.target))
		self.nxtnode = getstruct(self.curnode.target, "targetname");
	while (isdefined(self.curnode))
	{
		pts = bezier_points( self.origin, self.prvprvpos, self.prvnode, self.curnode, self.nxtnode);
		
		if ( IsDefined( self.prvnode ) )
		{	// change these params after we've gone by the node
			airResistance = self.prvnode.script_airresistance;
			speed = self.prvnode.speed;
			accel = self.prvnode.script_accel;
			decel = self.prvnode.script_decel;
		}
		else
		{
			airResistance = undefined;
			speed = undefined;
			accel = undefined;
			decel = undefined;
		}
		if (IsDefined( self.curnode.lookahead) )
			lookahead = self.curnode.lookahead;
		if (IsDefined( self.curnode.radius) )
			radius = self.curnode.radius;
		// Dealing with stopnode, unload, flag_wait, and endOfPath may need some work to act correctly
		stopnode = IsDefined( self.curnode.script_stopnode ) && self.curnode.script_stopnode;
		unload = IsDefined( self.curnode.script_unload );
		flag_wait = ( IsDefined( self.curnode.script_flag_wait ) && !flag( self.curnode.script_flag_wait ) ); // // if the flag gets set during flight, we should update the setvehgoalpos to not stop
		endOfPath = !IsDefined( self.curnode.target );
		hasDelay = IsDefined( self.curnode.script_delay );
		if ( IsDefined( self.curnode.angles ) )
			yaw = self.curnode.angles[ 1 ];
		else
			yaw = 0;

		// Use the length to determine how far into the curve we are
		blength = bezier_length(pts);
		dist = 0;
		distahead = radius;	// how far ahead in inches we'll try to ensure we've setup
		prv_point = eval_bezier( pts, 0.0);
		/#
		AddDebugPoint(pts[0],(1,0,0));
		AddDebugPoint(pts[3],(0,1,0));
		if (pts[4] == 3)
		{
			AddDebugPoint(pts[1],(1,0,1));
			AddDebugPoint(pts[2],(0,1,1));
		}
		#/
		cur_point = prv_point;
		
		t=0.0;
		while (t < 1.0)
		{
			dist += Length(cur_point - prv_point);
			t = (dist + distahead)/blength;
			if (t > 1.0)
				t = 1.0;
			tgt_point = eval_bezier( pts, t);
			self UpdateDebugPath(tgt_point);
			self Vehicle_HeliSetAI( tgt_point, speed, accel, decel, self.curnode.script_goalyaw, self.curnode.script_anglevehicle, yaw, airResistance, hasDelay, stopnode, unload, flag_wait, endOfPath );
			if (Length(self.origin - prv_point) < radius)
			{
				cur_point = prv_point;
				prv_point = tgt_point;
			}
			//self SetVehGoalPos( tgt_point, 0 );
			self UpdateCapturePath();
			/#
			if (isdefined(self.debug_smooth_path) && self.debug_smooth_path)
			{
				draw_point( pts[0], 24, (0,0,1));
				draw_point( pts[3], 24, (0,1,0));
				if (pts[4] == 3)
				{
					draw_point( pts[1], 24, (1,0,1));
					draw_point( pts[2], 24, (0,1,1));
				}
				draw_point( tgt_point, 24, (1,1,1));
			}
			#/

			t += 0.05;
			wait 0.05;
		}

		// reached next point
		smooth_vehicle_path_node_reached( self.curnode );
		if (isdefined(self.prvnode))
			self.prvprvpos = self.prvnode.origin;
		else
			self.prvprvpos = startorigin;
		self.prvnode = self.curnode;
		self.curnode = self.nxtnode;
		self.nxtnode = undefined;
		if (isdefined(self.curnode) && isdefined(self.curnode.target))
			self.nxtnode = getstruct(self.curnode.target, "targetname");
	}
	self StopCapturePath();
}



StartCapturePath()
{
	/#
	self notify("newcapturepath");
	self.capture_path=undefined;
	self.capture_path_enabled=true;
	self thread DrawCapturePath();
	#/
}

UpdateCapturePath()
{
	/#
	if (isdefined(self.capture_path_enabled) && self.capture_path_enabled)
	{
		if (!isdefined(self.capture_path))
			self.capture_path[0] = self.origin;
		else
			self.capture_path[self.capture_path.size] = self.origin;
	}
	#/
}

StopCapturePath()
{
	/#
	if (isdefined(self.capture_path_enabled) && self.capture_path_enabled)
		self.capture_path_enabled = false;
	#/
}

DrawCapturePath()
{
	/#
	self endon("newcapturepath");
	colr = (1,0.5,0.5);
	while (true)
	{
		if (isdefined(self.capture_path))
		{
			for (i=1; i<self.capture_path.size; i++)
			{
				line(self.capture_path[i-1], self.capture_path[i], colr);
			}
		}
		wait 0.05;
	}
	#/
}

TrackEntity( bAngles )
{
	/#
	self endon("death");
	self StartDebugPath( bAngles );
	while (true)
	{
		waittillframeend;
		self UpdateDebugPath(self.origin, self.angles);
		wait 0.05;
	}
	#/
}

StartDebugPath( bAngles )
{
	/#
	self notify("newdebugpath");
	self.debug_path=undefined;
	self.debug_path_angles=undefined;
	self.debug_path_enabled=true;
	self.debug_path_bangles = bAngles;
	self thread DrawDebugPath();
	#/
}

UpdateDebugPath( origin, angles )
{
	/#
	if (isdefined(self.debug_path_enabled) && self.debug_path_enabled)
	{
		if (!isdefined(self.debug_path))
			self.debug_path[0] = origin;
		else
			self.debug_path[self.debug_path.size] = origin;
		if (isdefined(self.debug_path_bangles) && self.debug_path_bangles)
		{
			if (!isdefined(self.debug_path_angles))
				self.debug_path_angles[0] = angles;
			else
				self.debug_path_angles[self.debug_path_angles.size] = angles;
		}
	}
	#/
}

StopDebugPath()
{
	/#
	if (isdefined(self.debug_path_enabled) && self.debug_path_enabled)
		self.debug_path_enabled = false;
	#/
}

DrawDebugPath()
{
	/#
	self endon("newdebugpath");
	colr = (0.5,1.0,0.5);
	while (true)
	{
		waittillframeend;
		waittillframeend;	// ensure we are last (after the capture)
		if (isdefined(self.debug_path))
		{
			for (i=1; i<self.debug_path.size; i++)
			{
				line(self.debug_path[i-1], self.debug_path[i], colr);
			}
			if (isdefined(self.debug_path_bangles) && self.debug_path_bangles)
			{
				for (i=0; i<self.debug_path_angles.size; i++)
				{
					draw_axis( self.debug_path[i], self.debug_path_angles[i] );
				}
			}
		}
		wait 0.05;
	}
	#/
}


AddDebugPoint( origin, colr )
{
	/#
	if (!isdefined(self.debug_points))
	{
		self.debug_points[0][0] = origin;
		self.debug_points[0][1] = colr;
		self thread DrawDebugPoints();
	}
	else
	{
		tmp[0] = origin;
		tmp[1] = colr;
		self.debug_points[self.debug_points.size]= tmp;
	}
	#/
}

DrawDebugPoints()
{
	/#
	colr = (0.5,1.0,0.5);
	while (isdefined(self) && isdefined(self.debug_points))
	{
		for (i=0; i<self.debug_points.size; i++)
		{
			draw_point(self.debug_points[i][0], 120, self.debug_points[i][1]);
		}
		wait 0.05;
	}
	#/
}

// draws health and tracks hits
DebugHind(debugHealth, debugTrack)
{
	/#
	self thread DebugHindName();
	if (debugHealth)
	{
		self thread DebugHindHealth();
	}
	#/
}

DebugHindName()
{
	self endon("death");
	if (!isdefined(self.name))
		return;
	while (true)
	{
		origin = self.origin;
		offset = ( 0, 0, 60);
		Print3d( origin + offset, self.name, (1,1,0.5), 1, 1 );
		if (isdefined(self.curpathtype))
		{
			str = "PT:"+self.curpathtype;
			if (isdefined(self.curpathstart))
			{
				str = str + " - " + self.curpathstart;
				if (self.curpathtype == "normal")
				{
					if (isdefined(self.currentnode) && isdefined(self.currentnode.target))
						str = str + " > " + self.currentnode.target;
				}
				else if (self.curpathtype == "smooth")
				{
					if (isdefined(self.curnode) && isdefined(self.curnode.target))
						str = str + " > " + self.curnode.target;
				}
				else if (self.curpathtype == "none")
				{
					if (isdefined(self.lastpathnode) && isdefined(self.lastpathnode.targetname))
						str = str + " | " + self.lastpathnode.targetname;
				}
			}
			Print3d( origin - offset, str, (1,1,0.5), 1, 1 );
		}
		wait 0.05;
	}
}

DebugCatchHits()
{
	self endon("death");
	prvhealth = self.health - self.healthbuffer;
	while (self.health > 0)
	{
		self waittill( "damage", amount, attacker, direction_vec, point, type, modelName, tagName );
		if (isdefined(amount))
		{
			curhealth = self.health - self.healthbuffer;
			self.debug_health_recs[self.debug_health_recs.size] = curhealth;
			prvhealth = curhealth;
		}
	}
}

DebugHindHealth()
{
	self endon("death");
	self.debug_health_recs = [];
	self.debug_health_recs[0] = self.health - self.healthbuffer;
	self thread DebugCatchHits();
	zscale = 0.1;
	while (true)
	{
		origin = self.origin;
		curhealth = self.health - self.healthbuffer;
		colr = (0, 1, 0);
		if (curhealth < 0)
			colr = (1, 1, 0);
		line(origin, origin + (0, 0, curhealth*zscale), colr);
		for (i=0; i<self.debug_health_recs.size; i++)
		{
			if (i & 1)
				colr = (1,0,0);
			else
				colr = (0,0,1);
			nxthealth = self.debug_health_recs[i];
			line(origin + (0, 0, curhealth*zscale), origin + (0, 0, nxthealth*zscale), colr);
			curhealth = nxthealth;
		} 
		wait 0.05;
	}
}
