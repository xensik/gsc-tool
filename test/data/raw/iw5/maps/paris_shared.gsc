#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;

#include maps\_audio;

#include maps\_hud_util;

paris_equip_player()
{
	/*
	PreCacheItem( "scar_h_acog" );

	level.player giveWeapon( "scar_h_acog" );
	level.player SwitchToWeapon( "scar_h_acog" );
	
	level.player SetOffhandPrimaryClass( "frag" );
	level.player giveWeapon( "fraggrenade" );
	
	level.player SetOffhandSecondaryClass( "flash" );
	level.player giveWeapon( "ninebang_grenade" );
	*/
}

teleport_to_scriptstruct(name)
{
	scriptstruct = GetStruct(name, "script_noteworthy");
	level.player SetOrigin(scriptstruct.origin);
	if(IsDefined(scriptstruct.angles))
		level.player SetPlayerAngles(scriptstruct.angles);
                
                
	allies = GetEntArray("hero", "script_noteworthy");
    
    foreach(ally in allies)
    {
    	if(IsSpawner(ally)) allies = array_remove(allies, ally);	
    }
                
	ally_structs = GetStructArray(scriptstruct.target, "targetname");
                
	for(i = 0; i < allies.size; i++)
	{
		if(i < ally_structs.size)
		{
			allies[i] ForceTeleport(ally_structs[i].origin, ally_structs[i].angles);
			allies[i] SetGoalPos(ally_structs[i].origin);
		}
		else
		{
			allies[i] ForceTeleport(level.player.origin, level.player.angles);	
			allies[i] SetGoalPos(level.player.origin);
		}
	}
}

// todo: move this to shg_common?
getent_safe(name, type)
{
	ret = GetEnt(name, type);
	/#
	AssertEx(IsDefined(ret), "Couldn't find entity with \"" + type + "\" = \"" + name + "\"");
	#/
	return ret;
}


/#
debug_magic()
{
	dvar_name = "debug_magic";
	SetDevDvar(dvar_name, "0");
	
	foreach(spawner in GetSpawnerArray())
	{
		spawner.spawner_targetname = spawner.targetname;
		spawner.orig_count = spawner.count;	
		spawner add_spawn_function(::debug_magic_spawn_func);
	}
	
	for(;;)
	{
		if(GetDebugDvar(dvar_name) != "0")
		{
			allies = GetAIArray("allies", "axis");
			foreach(ally in allies)
			{
				str = "";
				
				if(IsDefined(ally.script_noteworthy))
				{
					str += "nw: " + ally.script_noteworthy + "\n";
				}

				if(IsDefined(ally.spawner_targetname))
				{
					str += "stn: " + ally.spawner_targetname + "\n";
				}
				
				color = (1, 1, 1);
				if(IsDefined(ally.script_forcecolor))
				{
					color = get_script_palette()[ally.script_forcecolor];
					//str += "color: " + ally.script_forcecolor + "\n";
				}
				
				if(IsDefined(ally.magic_bullet_shield))
				{
					str += "magic\n";
				}
				
				if(IsDefined(ally.spawned_by_flood_spawner) && IsDefined(ally.orig_count) && IsDefined(ally.spawn_number) && ally.orig_count > 1)
				{
					str += ally.spawn_number + " of " + ally.orig_count;	
				}
				
				if(IsDefined(ally.script_parameters))
				{
					str += "params: " + ally.script_parameters + "\n";	
				}
				
				goalvolume = ally GetGoalVolume();
				if(IsDefined(goalvolume) && IsDefined(goalvolume.targetname))
				{
					str += "goalvolume: " + goalvolume.targetname + "\n";
				}
				
				if(IsDefined(ally.goalradius))
				{
					str += "radius: " + ally.goalradius;
				}
				
				lines = StrTok(str, "\n");
				line_height = 8;
				offset = 48 + line_height * lines.size;
				foreach(line in lines)
				{			
					Print3D(ally.origin + (0, 0, offset), line, color, 1, .5);			
					offset -= line_height;
				}
			}	
		}
		else
		{
			wait 1;
		}
		waitframe();	
	}	
}

debug_magic_spawn_func()
{
	if(IsDefined(self.spawner) && IsDefined(self.spawner.count) && IsDefined(self.spawner.orig_count))
	{
		self.spawn_number = self.spawner.orig_count - self.spawner.count;	
	}
}

#/


spawn_metrics_init()
{
	level.spawn_metrics_spawn_count = [];
	level.spawn_metrics_death_count = [];
	
	add_global_spawn_function("axis", ::spawn_metrics_spawn_func);
	
	// account for guys already created (not spawners)
	foreach(guy in GetAIArray("axis"))
	{
		if(!IsSpawner(guy) && IsAlive(guy))
		{
			guy spawn_metrics_spawn_func();	
		}
	}	
}

spawn_metrics_spawn_func()
{
	Assert(IsDefined(self));
	Assert(IsAlive(self));
	Assert(!IsSpawner(self));
	Assert(IsAI(self));
	
	if(IsDefined(self.script_noteworthy))
	{
		if(IsDefined(level.spawn_metrics_spawn_count[self.script_noteworthy]))
		{
			level.spawn_metrics_spawn_count[self.script_noteworthy] += 1;
		}
		else
		{
			level.spawn_metrics_spawn_count[self.script_noteworthy] = 1;
		}
		
		self thread spawn_metrics_death_watcher();
	}
}

spawn_metrics_death_watcher()
{
	Assert(IsDefined(self));
	Assert(IsDefined(self.script_noteworthy));
	
	orig_script_noteworthy = self.script_noteworthy;
	
	self waittill("death");
		
	if(IsDefined(level.spawn_metrics_death_count[orig_script_noteworthy]))
	{
		level.spawn_metrics_death_count[orig_script_noteworthy] += 1;
	}	
	else
	{
		level.spawn_metrics_death_count[orig_script_noteworthy] = 1;
	}
}

spawn_metrics_number_spawned(script_noteworthy)
{
	if(IsArray(script_noteworthy))
	{
		sum = 0;
		foreach(nw in script_noteworthy)
			sum += spawn_metrics_number_spawned(nw);
		return sum;
	}
	
	if(IsDefined(level.spawn_metrics_spawn_count[script_noteworthy]))
		return level.spawn_metrics_spawn_count[script_noteworthy];
	else
		return 0;
}

spawn_metrics_number_died(script_noteworthy)
{
	if(IsArray(script_noteworthy))
	{
		sum = 0;
		foreach(nw in script_noteworthy)
			sum += spawn_metrics_number_died(nw);
		return sum;
	}
	
	if(IsDefined(level.spawn_metrics_death_count[script_noteworthy]))
		return level.spawn_metrics_death_count[script_noteworthy];
	else
		return 0;
}

spawn_metrics_number_alive(script_noteworthy)
{
	/#
	// also do a simple count as a sanity check
	
	if(IsArray(script_noteworthy))
		nw_array = script_noteworthy;
	else
		nw_array = [script_noteworthy];
	count = 0;
	foreach(nw in nw_array)
		foreach(guy in GetEntArray(nw, "script_noteworthy"))
			if(IsAlive(guy))
				count++;
	AssertEx(count == spawn_metrics_number_spawned(script_noteworthy) - spawn_metrics_number_died(script_noteworthy), "spawn_metrics count was wrong - potential progression blocker?  Some guys may not have had spawn functions run on them.");
	#/
	
	return spawn_metrics_number_spawned(script_noteworthy) - spawn_metrics_number_died(script_noteworthy);
}

spawn_metrics_waittill_count_reaches(count, noteworthies, debug)
{
	if(!IsArray(noteworthies)) noteworthies = [noteworthies];
	
	// sigh, give people a chance to spawn if they're spawned in threads
	waittillframeend;
	
	for(;; wait 1)
	{
		current = 0;
		foreach(noteworthy in noteworthies)
		{
			current += spawn_metrics_number_alive(noteworthy);
		}
		
		/#
		if(IsDefined(debug) && debug)
		{
			debug_print(current + " alive, waiting till " + count);
		}	
		#/
			
		if(current <= count)
		{
			break;
		}
	}	
}

spawn_metrics_waittill_deaths_reach(death_count, noteworthies, debug)
{
	if(!IsArray(noteworthies)) noteworthies = [noteworthies];
	
	for(;; wait 1)
	{
		deaths = 0;
		foreach(noteworthy in noteworthies)
		{
			deaths += spawn_metrics_number_died(noteworthy);
		}
		
		/#
		if(IsDefined(debug) && debug)
		{
			debug_print(deaths + " have died, waiting till " + death_count);
		}	
		#/
		
		if(deaths >= death_count)
		{
			break;
		}
	}
}

delete_spawners(noteworthies)
{
	if(!IsArray(noteworthies)) noteworthies = [noteworthies];
	
	foreach(noteworthy in noteworthies)
	{
		foreach(spawner in GetEntArray(noteworthy, "script_noteworthy"))
		{
			if(IsSpawner(spawner))
			{
				spawner Delete();
			}
		}
	}
}

// this ought to be generally useful
// todo: maybe move this to shg_common?
array_filter(array, method)
{
	result = [];
	foreach(key, value in array)
	{
		if(self [[method]](value))
		{
			result[key]	= value;
		}
	}
	return result;	
}

cleanup_ai_with_script_noteworthy(script_noteworthy, distance)
{
	if(!IsDefined(distance))
	{
		distance = 512;
	}
	
	ai_array = [];
	foreach(ai_or_spawner in GetEntArray(script_noteworthy, "script_noteworthy"))
	{
		if(IsSpawner(ai_or_spawner))
		{
			ai_or_spawner Delete();	
		}
		else
		{
			ai_array[ai_array.size] = ai_or_spawner;
		}
	}
	thread AI_delete_when_out_of_sight(ai_array, distance);
}

// todo: maybe ought to be a util
// grr, basically all anim functions need to be doubled to include a _generic version
anim_generic_set_rate_single( guys, anime, rate )
{
	array_thread( guys, ::anim_set_rate_internal, anime, rate, "generic" );
}


goto_node(node_or_script_noteworthy, bWait, radius)
{
	self endon("stop_goto_node");
	
	if(!IsDefined(radius)) radius = 16;
	
	self set_goal_radius(radius);

	if(IsString(node_or_script_noteworthy))
	{
		node = 	GetNode(node_or_script_noteworthy, "script_noteworthy");
	}
	else
	{
		node = node_or_script_noteworthy;
	}
	
	if(IsDefined(node))
	{
		self set_goal_node(node);
	}
	else	
	{	
		node = GetStruct(node_or_script_noteworthy, "script_noteworthy");	
		AssertEx(IsDefined(node), "Couldn't find node or struct with script_noteworthy " + node_or_script_noteworthy);
		
		self set_goal_pos(node.origin);
	}	

	if(bWait)
	{
		/#	
		AssertEx(!IsDefined(self.script_forcecolor), "Must disable_ai_color() before calling goto_node() with bWait == true");
		self childthread assert_on_color();
		#/
		
		self waittill("goal");
		
		/#
		self notify("stop_assert_on_color");
		
		if(Distance2D(self.origin, node.origin) > radius * 1.1)
		{
			AssertEx(false, "goto_node finished but wasn't close enough (see the green arrow)");	
			
			thread draw_arrow_time(self.origin, node.origin, (0, 1, 0), 10);
		}	
		#/	
	}
}

/#
assert_on_color()
{
	self endon("stop_assert_on_color");
	for(;; waitframe())
	{
		if(IsDefined(self.script_forcecolor))
		{
			AssertEx(false, "Color got enabled during goto_node().");
			break;
		}
	}
}
#/

animname_not_overridden(guy)
{
	return !(guy animname_is_overridden());	
}

animname_override(new_animname)
{
	AssertEx(!IsDefined(self.old_animname), "Tried to override animname " + to_str(self.old_animname) + " to " + to_str(new_animname) + " but it was already overridden to " + to_str(self.animname));
	self.old_animname = self.animname;
	self.animname = new_animname;
	
	self.animname_overridden = true;
}

animname_restore()
{
	AssertEx(animname_is_overridden(), "called animname_restore() without first calling animname_override() on " + to_str(self.animname));
	self.animname = self.old_animname;
	self.old_animname = undefined;
	
	self.animname_overridden = undefined;
}

animname_is_overridden()
{
	return IsDefined(self.animname_overridden);	
}

to_str(obj)
{
	if(!IsDefined(obj)) obj = "(undefined)";
	return obj + "";	
}


anim_set_rate_single_delay(guy, scene, rate)
{
	waittillframeend;
	self anim_set_rate_single(guy, scene, rate);
	wait(0.05);
	self anim_set_rate_single(guy, scene, rate);
}

waittill_range_or_eta(origin, min_range, min_eta)
{
	AssertEx(IsPlayer(self), "waittill_range_or_eta() only works on players");
	
	for(;; waitframe())
	{
		self_to_origin = origin - self.origin;
		range = Length(self_to_origin);
		
		if(range < min_range)
			break;
		
		projected_velocity = VectorDot(self GetVelocity(), VectorNormalize(self_to_origin));
		if(projected_velocity > 0)
		{
			eta = range / projected_velocity;

			if(eta < min_eta)
				break;
		}
	}	
}



/#
warn_on_death(name)
{
	self endon("warn_on_death_stop");
	
	Print("warning on death" + name);
	
	AssertEx(IsDefined(self), "warn_on_death(), self was undefined");	
		
	for(;; waitframe())
	{
		AssertEx(IsAlive(self), "warn_on_death(), " + name + " has died");	
		if(!IsAlive(self)) break;
	}
}

warn_on_death_stop()
{
	self notify("warn_on_death_stop");	
}
#/

_waittill(msg)
{
	self waittill(msg);	
}

// todo: document where this came from
fade_in( fade_time )
{
	if ( level.MissionFailed )
		return;
	level notify( "now_fade_in" );
		
	black_overlay = get_black_overlay();
	if ( fade_time )
		black_overlay FadeOverTime( fade_time );

	black_overlay.alpha = 0;

	wait( fade_time );
}


fade_out( fade_out_time )
{
	black_overlay = get_black_overlay();
	if ( fade_out_time )
		black_overlay FadeOverTime( fade_out_time );

	black_overlay.alpha = 1;

	wait( fade_out_time );
}

get_black_overlay()
{
	if ( !IsDefined( level.black_overlay ) )
		level.black_overlay = create_client_overlay( "black", 0, level.player );
	level.black_overlay.sort = -1;
	level.black_overlay.foreground = false;
	return level.black_overlay;
}

// disables grenade usage for all enemy NPCs
disable_enemy_grenades()
{
	add_global_spawn_function("axis", ::disable_grenades);
	
	foreach(guy in GetAIArray("axis"))
	{
		if(IsAlive(guy))
		{
			guy disable_grenades();
		}	
	}
}

// re-enables grenade usage for all enemy NPCs
enable_enemy_grenades()
{
	remove_global_spawn_function("axis", ::disable_grenades);
	
	foreach(guy in GetAIArray("axis"))
	{
		if(IsAlive(guy))
		{
			guy enable_grenades();
		}	
	}
}

// disables grenades for one NPC, saving his grenade ammo count
disable_grenades()
{
	Assert(IsAI(self), "disable_grenades() is for AI");
	if(IsDefined(self.grenadeammo) && !IsDefined(self.oldgrenadeammo))
		self.oldgrenadeammo = self.grenadeammo;			
	self.grenadeammo = 0;
}

// restores an NPCs grenade ammo count so he can fire again
enable_grenades()
{
	Assert(IsAI(self), "enable_grenades() is for AI");
	if(IsDefined(self.oldgrenadeammo))
	{
		self.grenadeammo = self.oldgrenadeammo;
		self.oldgrenadeammo = undefined;	
	}
}

spawn_corpses(targetname, anime_override)
{	
	corpses = [];
	
	// old system - look up all spawners with the given targetname, spawn corpses with them
	// problem is the engine insists on dropping them to the ground before spawning, so we can't
	// sit them at chairs, slumped over tables, etc.
	foreach(corpse_spawner in GetEntArray(targetname, "targetname"))
	{
		if(IsSpawner(corpse_spawner))
		{
			anime = corpse_spawner.script_noteworthy;
			if(IsDefined(anime_override))
			{
				anime = anime_override;	
			}
			corpses[corpses.size] = spawn_corpse(corpse_spawner, anime, corpse_spawner.origin, corpse_spawner.angles);
		}
	}
	
	// new system - corpses are structs, and they search for a spawner with the classname of the struct's script_noteworthy
	// the spawner must have a script_noteworthy of "corpse_spawner"
	structs = getstructarray(targetname, "targetname");	
	foreach(corpse_struct in structs)
	{
		AssertEx(IsDefined(corpse_struct.script_noteworthy), "Corpse struct needs script_noteworthy of the classname of actor to spawn");
		spawner_classname = corpse_struct.script_noteworthy;
		
		spawners = GetEntArray(spawner_classname, "classname");
		spawner = undefined;
		foreach(possible_spawner in spawners)
		{
			if(IsSpawner(possible_spawner) && IsDefined(possible_spawner.script_noteworthy) && possible_spawner.script_noteworthy == "corpse_spawner")
			{
				spawner = possible_spawner;
				break;
			}			
		}
		if(IsDefined(spawner))
		{
			// ok, found a spawner
			AssertEx(IsDefined(corpse_struct.script_animation), "Corpse struct needs script_animation set to the anime of the animation");
			
			corpses[corpses.size] = spawn_corpse(spawner, corpse_struct.script_animation, corpse_struct.origin, corpse_struct.angles);
		}
		else
		{
			AssertEx(false, "couldn't find spawner with classname " + spawner_classname + "and script_noteworthy corpse_spawner for spawning a corpse (NOTE: classnames are case-sensitive)");
		}
		
	}
	
	return corpses;
}

spawn_corpse(spawner, anime, origin, angles)
{
	spawner.count++;

	// we're reusing spawners, but the spawn may fail silently due to being called on the same frame...
	corpse_drone = undefined;
	while(true)
	{
		corpse_drone = spawner spawn_ai( true );
		if(IsDefined(corpse_drone))
			break;
		waitframe();
	}
	
	if(IsDefined(corpse_drone))
	{
		corpse_drone.animname = "generic";
		corpse_drone gun_remove();
		corpse_drone ForceTeleport(origin, angles);
		sAnim = corpse_drone getanim(anime);
		corpse_drone anim_generic_first_frame(corpse_drone, anime);
		dummy = maps\_vehicle_aianim::convert_guy_to_drone(corpse_drone);
		dummy SetAnim( sAnim, 1, .2 );
		dummy NotSolid();
		return dummy;
	}			
}


/#
// This is a wrapper for IPrintLn that turns off in exec demo mode.
debug_print(msg)
{
	// The goal here is to turn off IPrintLn() when exec demo mode is enabled.  Exec demo mode works
	// by executing demo.cfg, which just sets a bunch of dvars.  One of the dvars is developer_script.
	// That dvar should turn off code in /# #/ comments, but it is only read at map init time, so if you
	// run the map and choose exec demo, it's too late.
	
	// Another way we could stop the IPrintLn()s would be with cl_noprint, however, this also disables
	// checkpoint updated messages, which are important.
	
	// Since there is now an option to run "exec demo" but leave developer_script enabled, we'll instead use the
	// developer dvar instead.
	
	if(GetDebugDvarInt("developer") != 0)
	{
		IPrintLn(msg);	
	}	
}
#/

	
	
vehicle_scripted_animation_wait(anim_ent, animation)
{
	Assert(IsDefined(anim_ent));
	Assert(IsDefined(anim_ent.origin));
	Assert(IsDefined(anim_ent.angles));
	
	if(IsString(animation)) animation = self getanim(animation);
	
	start_origin = GetStartOrigin(anim_ent.origin, anim_ent.angles, animation);
	start_angles = GetStartAngles(anim_ent.origin, anim_ent.angles, animation);
	
	// we're assuming the vehicle faces forwards during the start of the animation
	start_forward = AnglesToForward(start_angles);

	while(Distance(start_origin, self.origin) > 512 || VectorDot(start_origin - self.origin, start_forward) > 0)
	{
		waitframe();
	}
}

vehicle_scripted_animation(anim_ent, animation, should_pop, pop_flatten_only, vehicle_end_node, rate, print_debug_info)
{
	self endon("death");
	Assert(IsDefined(anim_ent));
	Assert(IsDefined(anim_ent.origin));
	Assert(IsDefined(anim_ent.angles));
	if(!IsDefined(should_pop)) should_pop = true;
	if(!IsDefined(pop_flatten_only)) pop_flatten_only = false;
	if(!IsDefined(rate)) rate = 1;
	if(!IsDefined(print_debug_info)) print_debug_info = false;
	
	if(IsString(animation)) animation = self getanim(animation);
		
	start_origin = GetStartOrigin(anim_ent.origin, anim_ent.angles, animation);
	start_angles = GetStartAngles(anim_ent.origin, anim_ent.angles, animation);
	
	vehicle_origin = self.origin;
	vehicle_angles = self.angles;	

	/#
	if(print_debug_info)
	{
		// tweak the vehicle origin (a) back to the line we would wake up on, and (b) ignoring pitch and roll
		start_forward = AnglesToForward(start_angles);
		vehicle_origin_tweaked = vehicle_origin - VectorDot(vehicle_origin - start_origin, start_forward) * start_forward;
		vehicle_angles_tweaked = (0, vehicle_angles[1], 0);
				
		adjusted_anim_ent = TransformMove(vehicle_origin_tweaked, vehicle_angles_tweaked, start_origin, start_angles, anim_ent.origin, anim_ent.angles);
			
		debug_print("starting a vehicle animation");
		debug_print("ideal vehicle origin: " + start_origin);
		debug_print("ideal vehicle angles: " + start_angles);
		debug_print("ideal anim_ent origin: " + adjusted_anim_ent["origin"]);
		debug_print("off by " + Distance(adjusted_anim_ent["origin"], anim_ent.origin));
		debug_print("ideal anim_ent angles: " + adjusted_anim_ent["angles"]);
		debug_print("should be ccw by " + AngleClamp180(adjusted_anim_ent["angles"][1] - anim_ent.angles[1]));
		debug_print("vehicle speed before animation: " + Length(self Vehicle_GetVelocity()) / 17.6);
	}
	#/
	
	if(should_pop)
	{
		if(pop_flatten_only)
		{
			// keep our yaw, but pitch and roll according to the animation
			// (not sure if this is correct if there is an initial roll in the animation)
			vehicle_angles = (start_angles[0], self.angles[1], start_angles[2]);
			// we don't actually teleport the vehicle, just save these angles for use computing adjusted_anim_ent
		}
		else
		{
			vehicle_origin = start_origin;
			vehicle_angles = start_angles;
			
			// if you teleport here, your position will pop, but the suspension won't be affected
			// sort of a trade-off			
			if(Distance(vehicle_origin, self.origin) > 3)
			{
				self Vehicle_Teleport(vehicle_origin, vehicle_angles);
			}
		}
	}

	// where anim_ent would be if start were moved to self
	adjusted_anim_ent = TransformMove(vehicle_origin, vehicle_angles, start_origin, start_angles, anim_ent.origin, anim_ent.angles);
	
	if(IsDefined(self.animscripted_root))
		self AnimScripted("vehicle_scripted_animation", adjusted_anim_ent["origin"], adjusted_anim_ent["angles"], animation, "normal", self.animscripted_root);
	else
		self AnimScripted("vehicle_scripted_animation", adjusted_anim_ent["origin"], adjusted_anim_ent["angles"], animation);
		
	self SetFlaggedAnim("vehicle_scripted_animation", animation, 1, 0, rate);
	
	self.last_velocity_ips = self Vehicle_GetVelocity();
	self childthread vehicle_speed_watcher(print_debug_info);

	self waittillmatch("vehicle_scripted_animation", "end");
			
	if(IsDefined(vehicle_end_node))
	{				
		/#
		if(print_debug_info && should_pop && !pop_flatten_only)
		{
			debug_print("ideal pathnode position is: " + self.origin);
			debug_print("off by " + Distance(self.origin, vehicle_end_node.origin));
			debug_print("ideal pathnode angles are: " + self.angles);
			debug_print("should be ccw by " + AngleClamp180(self.angles[1] - vehicle_end_node.angles[1]));
			debug_print("ending speed is " + (Length(self.last_velocity_ips) / 17.6));
		}
		#/

		// for good measure:
		self StopAnimScripted();
		
		self thread vehicle_paths(vehicle_end_node, false);
		self StartPath(vehicle_end_node);
	
		resume_speed_mph = Length(self.last_velocity_ips) / 17.6;	
		self Vehicle_SetSpeedImmediate(resume_speed_mph, 100, 100);
		self ResumeSpeed(10);
	}
}

anim_scripted_in_place(notifier, animation, mode, root)
{
	start_origin = GetStartOrigin((0, 0, 0), (0, 0, 0), animation);
	start_angles = GetStartAngles((0, 0, 0), (0, 0, 0), animation);
	
	adjusted = TransformMove(self.origin, self.angles, start_origin, start_angles, (0, 0, 0), (0, 0, 0));
	
	if(IsDefined(mode) && IsDefined(root))
		self AnimScripted(notifier, adjusted["origin"], adjusted["angles"], animation, mode, root);	
	else if(IsDefined(mode))
		self AnimScripted(notifier, adjusted["origin"], adjusted["angles"], animation, mode);	
	else
		self AnimScripted(notifier, adjusted["origin"], adjusted["angles"], animation);	
}

vehicle_speed_watcher(print_debug_info)
{
	self endon("death");
	self endon("vehicle_scripted_animation_done");

	for(i = 0; ; i++)
	{
		waittillframeend;
		if(self Vehicle_IsPhysVeh())
		{
			self.last_velocity_ips = self Vehicle_GetVelocity();
		}
		else
		{
			// ug, no good way to get the speed of animating non-physics vehicles
			if(IsDefined(self.last_origin))
			{
				self.last_velocity_ips = (self.origin - self.last_origin) * 20;
			}
			else
			{
				self.last_velocity_ips = (0, 0, 0);	
			}
			self.last_origin = self.origin;			
		}		

		/#
		if(print_debug_info && i == 1)
		{
			debug_print("speed at start of animation (mph): " + Length(self.last_velocity_ips / 17.6));
		}
		#/

		waitframe();
	}	
}

// sadly necessary because add_wait only takes 3 parameters
array_to_parameters(func, parameter_array)
{
	switch(parameter_array.size)
	{
		case 0:
			self [[func]]();
		break;
		case 1:
			self [[func]](parameter_array[0]);
		break;
		case 2:
			self [[func]](parameter_array[0], parameter_array[1]);
		break;
		case 3:
			self [[func]](parameter_array[0], parameter_array[1], parameter_array[2]);
		break;
		case 4:
			self [[func]](parameter_array[0], parameter_array[1], parameter_array[2], parameter_array[3]);
		break;
		case 5:
			self [[func]](parameter_array[0], parameter_array[1], parameter_array[2], parameter_array[3], parameter_array[4]);
		break;
		case 6:
			self [[func]](parameter_array[0], parameter_array[1], parameter_array[2], parameter_array[3], parameter_array[4], parameter_array[5]);
		break;
		case 7:
			self [[func]](parameter_array[0], parameter_array[1], parameter_array[2], parameter_array[3], parameter_array[4], parameter_array[5], parameter_array[6]);
		break;
		case 8:
			self [[func]](parameter_array[0], parameter_array[1], parameter_array[2], parameter_array[3], parameter_array[4], parameter_array[5], parameter_array[6], parameter_array[7]);
		break;
		case 9:
			self [[func]](parameter_array[0], parameter_array[1], parameter_array[2], parameter_array[3], parameter_array[4], parameter_array[5], parameter_array[6], parameter_array[7], parameter_array[8]);
		break;
		case 10:		
			self [[func]](parameter_array[0], parameter_array[1], parameter_array[2], parameter_array[3], parameter_array[4], parameter_array[5], parameter_array[6], parameter_array[7], parameter_array[8], parameter_array[9]);
		break;
		default:
			AssertEx("array_to_parameters called with too many parameters");
	}	
}

add_wait_arg_array(func, arg_array)
{
	add_wait(::array_to_parameters, func, arg_array);
}

// syntactic sugar for adding dialogue lines to the tables, used in paris_{a,b}_vo.gsc
add_lines(character, lines)
{
	foreach(line in lines)
	{
		level.scr_sound[character][line] = line;	
	}	
}

// syntactic sugar for adding radio lines to the tables, used in paris_{a,b}_vo.gsc
add_radio(lines)
{
	foreach(line in lines)
	{
		level.scr_radio[line] = line;	
	}	
}

// call this when you're just about to start several consequetive dialogeu lines 
// it will handle ducking the mix for the entire time, and also will sequence conversations
// in case you have some random points at which these are triggered.
conversation_begin()
{
	/#
	if(flag("flag_conversation_in_progress"))
	{
		debug_print("conversation_begin(): conversation is being delayed by another conversation.");
	}
	#/
	
	flag_waitopen("flag_conversation_in_progress");
	flag_set("flag_conversation_in_progress");
	
	/#
	thread conversation_debug_timer();
	#/
}

// make sure you always call this after calling conversation_begin()
conversation_end()
{
	flag_clear("flag_conversation_in_progress");	
}


/#
conversation_debug_timer()
{
	flag_waitopen_or_timeout("flag_conversation_in_progress", 60);
	if(flag("flag_conversation_in_progress"))
	{
		AssertEx(false, "A conversation lasted > 60 seconds, and other dialogue might be waiting.  Possible misplaced conversation_begin()?");	
	}
}
#/

Objective_OnEntity_safe(objective_number, entity, offset)
{
	thread Objective_OnEntity_safe_internal(objective_number, entity, offset);
}

Objective_OnEntity_safe_internal(objective_number, entity, offset)
{
	if(IsDefined(offset))
		Objective_OnEntity(objective_number, entity, offset);
	else	
		Objective_OnEntity(objective_number, entity);
		
	entity waittill("death");
	// amazingly this clears the objective dot, rather than moving it to the origin.
	Objective_Position(objective_number, (0, 0, 0));
}

disable_awareness()
{
	Assert(IsDefined(self));
	self.ignoreall = true;
	self.dontmelee = true;
	self.ignoreSuppression = true;
	assert(!isdefined(self.suppressionwait_old));
	self.suppressionwait_old = self.suppressionwait;
	self.suppressionwait = 0;
	self disable_surprise();
	self.IgnoreRandomBulletDamage = true;
	self disable_bulletwhizbyreaction();
	self disable_pain();
	
	// not playing with danger react anymore since we don't use that system, and it can
	// interfere with NPCs staying on the node we assign.	
//	self disable_danger_react();
	
	self.grenadeawareness = 0;
	self.ignoreme = 1;
	self enable_dontevershoot();
	self.disableFriendlyFireReaction = true;
	self setFlashbangImmunity(true);
}

enable_awareness()
{
	Assert(IsDefined(self));
	self.ignoreall = false;
	self.dontmelee = undefined;
	self.ignoreSuppression = false;
	if(isdefined(self.suppressionwait_old))
	{
		self.suppressionwait = self.suppressionwait_old;
		self.suppressionwait_old = undefined;
	}
	self enable_surprise();
	self.IgnoreRandomBulletDamage = false;
	self enable_bulletwhizbyreaction();
	self enable_pain();
	
	// not playing with danger react anymore since we don't use that system, and it can
	// interfere with NPCs staying on the node we assign.	
//	self enable_danger_react(3);
	
	self.grenadeawareness = 1;
	self.ignoreme = 0;
	self disable_dontevershoot();
	self.disableFriendlyFireReaction = undefined;
	self setFlashbangImmunity(false);
}

create_player_rig(anim_ent, tag, anime)
{
	player_rig = spawn_anim_model("player_rig", level.player.origin);
	player_rig Hide();
	anim_ent anim_first_frame_solo(player_rig, anime, tag);	
	if(IsDefined(anim_ent.classname) && anim_ent.classname != "script_struct")
	{
		player_rig LinkTo(anim_ent, tag);
	}
	return player_rig;
}

// turn off all the stuff we typically disable before scripted viewmodel animations
// might want to merge this with maps\_shg_common::SetUpPlayerForAnimations(), though it has some differences
player_control_off(bWait)
{
	Assert(IsPlayer(self));	
	if(!IsDefined(bWait)) bWait = true;
	
	self DisableWeapons();
	self AllowStand(true);
	self AllowCrouch(false);
	self AllowProne(false);	
	self AllowSprint(false);
	self SetStance("stand");
		
	if(bWait)
	{
		while((self GetStance() != "stand") || self IsThrowingGrenade() || self IsSwitchingWeapon())
			waitframe();	
	}
}

// turn back on all the stuff disabled in player_control_disable()
player_control_on()
{
	Assert(IsPlayer(self));
	self EnableWeapons();
	self AllowStand(true);
	self AllowCrouch(true);
	self AllowProne(true);	
	self AllowSprint(true);
}

// returns a struct with origin and angles, such that if the anime (can be animation or string) were
// played on self relative to the returned struct, self's position would not change.
create_anim_ent_for_my_position(anime)
{
	Assert(IsDefined(self.origin));
	Assert(IsDefined(self.angles));
	if(IsString(anime)) anime = self getanim(anime);
	
	ideal_start_origin = GetStartOrigin((0, 0, 0), (0, 0, 0), anime);
	ideal_start_angles = GetStartAngles((0, 0, 0), (0, 0, 0), anime);

	adjusted_anim_ent = TransformMove(self.origin, self.angles,                //         was moved here
	                                  ideal_start_origin, ideal_start_angles,  // if this
	                                  (0, 0, 0), (0, 0, 0));                   //                        where would these be?
		
	anim_ent = SpawnStruct();
	anim_ent.origin = adjusted_anim_ent["origin"];
	anim_ent.angles = adjusted_anim_ent["angles"];
	return anim_ent;
}

bob_mask( hudElement )
{
	self endon( "stop_mask_bob" );

	weapIdleTime = 0;
	previousAngles = level.player GetPlayerAngles();
	offsetY = 0;	// for vertical changes. eg. jumping
	offsetX = 0;	// for turning left/right
	
	addYoffset = hudElement.y;
	addXoffset = hudElement.x;
	
	frameTime = 0.05;
	while (1)
	{
		if ( IsDefined( hudElement ) )
		{
			angles = level.player GetPlayerAngles();
			velocity = level.player GetVelocity();
			zVelocity = velocity[2];
			velocity = velocity - velocity * ( 0, 0, 1 ); // zero out z velocity ( up/down velocity )
			speedXY = Length( velocity );
			stance = level.player GetStance();

			// speedScale goes from 0 to 1 as speed goes between 0 and full sprint
			speedScale = clamp( speedXY, 0, 280 ) / 280;
			// bobXFraction and bobXFraction control the amount of the maximum xy displacement that is allocated to the bob motion.
			// The remainder goes to the xy offset due to turn and z velocity.
			// As speed increases more displacement goes to bob and less to the xy offset due to turn and z velocity.
			bobXFraction = 0.1 + speedScale * 0.25;
			bobYFraction = 0.1 + speedScale * 0.25;

			// bobScale controls the amount of bob displacement based on stance
			bobScale = 1.0;	// default
			if ( stance == "crouch" )	bobScale = 0.75;
			if ( stance == "prone" )	bobScale = 0.4;
			if ( stance == "stand" )	bobScale = 1.0;

			// bobSpeed controls the frequency of the bob cycle
			idleSpeed = 5.0;
			ADSSpeed = 0.9;
			playerADS = level.player playerADS();
			// lerp bobSpeed between idleSpeed and ADSSpeed
			bobSpeed = idleSpeed * ( 1.0 - playerADS ) + ADSSpeed * playerADS;
			bobSpeed = bobSpeed * ( 1 + speedScale * 2 );

			maxXYDisplacement = 5;	// corresponds to 650 by 490 in the hud elem SetShader()
			bobAmplitudeX = maxXYDisplacement * bobXFraction * bobScale;
			bobAmplitudeY = maxXYDisplacement * bobYFraction * bobScale;

			// control the bob motion in the same pattern as the viewmodel bob - through it will not be in phase
			weapIdleTime = weapIdleTime + frameTime * 1000.0 * bobSpeed;
			rad_to_deg = 57.295779513; // radians to degrees
			 // the constants 0.001 and 0.0007 match those in BG_ComputeAndApplyWeaponMovement_IdleAngles()
			verticalBob   = sin( weapIdleTime * 0.001  * rad_to_deg );
			horizontalBob = sin( weapIdleTime * 0.0007 * rad_to_deg );

			// calculate some x offset based on player turning
			angleDiffYaw = AngleClamp180( angles[ 1 ] - previousAngles[ 1 ] );
			angleDiffYaw = clamp( angleDiffYaw, -10, 10 );
			offsetXTarget = ( angleDiffYaw / 10 ) * maxXYDisplacement * ( 1 - bobXFraction );
			offsetXChange = offsetXTarget - offsetX;
			offsetX = offsetX + clamp( offsetXChange, -1.0, 1.0 );

			// calculate some y offset based on vertical velocity
			offsetYTarget = ( clamp( zVelocity, -200, 200 ) / 200 ) * maxXYDisplacement * ( 1 - bobYFraction );
			offsetYChange = offsetYTarget - offsetY;
			offsetY = offsetY + clamp( offsetYChange, -0.6, 0.6 );
			
			hudElement MoveOverTime( 0.05 );
			hudElement.x = addXoffset + clamp( ( verticalBob   * bobAmplitudeX + offsetX - maxXYDisplacement ), ( 0 - 2 * maxXYDisplacement ), 0 );
			hudElement.y = addYoffset + clamp( ( horizontalBob * bobAmplitudeY + offsetY - maxXYDisplacement ), ( 0 - 2 * maxXYDisplacement ), 0 );
			previousAngles = angles;
			
			// /# debug_print("hud " + hudElement.x + ", " + hudElement.y); #/
		}
		wait frameTime;
	}
}

gasmask_on_player(bFadeIn, fadeOutTime, fadeInTime, darkTime)
{
	Assert(IsPlayer(self));	
	
	if(!IsDefined(bFadeIn)) bFadeIn = true;
	if(!IsDefined(fadeOutTime)) fadeOutTime = 0;
	if(!IsDefined(fadeInTime)) fadeInTime = 1;
	if(!IsDefined(darkTime)) darkTime = .25;
	
	if(bFadeIn)
	{
		fade_out( fadeOutTime );
	}
	
	SetHUDLighting( true );

	// originally this was one fullscreen element with coordinates of 0,0, and size 650x490, and the bob_mask()
	// thread will generally move the coordinates to -5, -5, plus or minus 5 units based on sway.
	// We've broken it in half, and changed bob_mask() to take the initial coordinates into account.
	// Anyway, the position and size must be such that the coordinates can move between -10 and 0 from their inital value in each coordinate.
	
	self.gasmask_hud_elem = NewClientHudElem( self ); 
	self.gasmask_hud_elem.x = 0;
	self.gasmask_hud_elem.y = 0;
	self.gasmask_hud_elem.horzAlign = "fullscreen";
	self.gasmask_hud_elem.vertAlign = "fullscreen";
	self.gasmask_hud_elem.foreground = false;
	self.gasmask_hud_elem.sort = -1; // trying to be behind introscreen_generic_black_fade_in	
	self.gasmask_hud_elem SetShader("gasmask_overlay_delta2_top", 650, 138);
	self.gasmask_hud_elem.alpha = 1.0;
	
	self.gasmask_hud_elem1 = NewClientHudElem( self ); 
	self.gasmask_hud_elem1.x = 0;
	self.gasmask_hud_elem1.y = 490 - 138;
	self.gasmask_hud_elem1.horzAlign = "fullscreen";
	self.gasmask_hud_elem1.vertAlign = "fullscreen";
	self.gasmask_hud_elem1.foreground = false;
	self.gasmask_hud_elem1.sort = -1; // trying to be behind introscreen_generic_black_fade_in	
	self.gasmask_hud_elem1 SetShader("gasmask_overlay_delta2_bottom", 650, 138);
	self.gasmask_hud_elem1.alpha = 1.0;

	level.player delaythread( 1.0, ::gasmask_breathing );
	vision_set_fog_changes( "paris_gasmask", .5 );

	thread bob_mask( self.gasmask_hud_elem );
	thread bob_mask( self.gasmask_hud_elem1 );
		
	if(bFadeIn)
	{
		wait( darkTime );
		fade_in( fadeInTime );
	}
}
	
gasmask_off_player()
{
	Assert(IsPlayer(self));	
	
	fade_out( 0.25 );

	self notify( "stop_mask_bob" );

	if(IsDefined(self.gasmask_hud_elem))
	{
		self.gasmask_hud_elem Destroy();	
		self.gasmask_hud_elem = undefined;
	}

	if(IsDefined(self.gasmask_hud_elem1))
	{
		self.gasmask_hud_elem1 Destroy();	
		self.gasmask_hud_elem1 = undefined;
	}


	SetHUDLighting( false );

	vision_set_fog_changes( "paris_catacombs", 0 );
	level.player notify( "stop_breathing" ); 
	wait( 0.25 );
	fade_in( 1.5 );
}	

gasmask_breathing()
{
	delay = 1.0;
	self endon( "stop_breathing" );
	
	while ( 1 )
	{
		self play_sound_on_entity( "breathing_gasmask" );
		wait( delay );
	}
}

gasmask_on_npc()
{
	self.gasmask = Spawn("script_model", (0, 0, 0));
	self.gasmask SetModel("prop_sas_gasmask");
	self.gasmask LinkTo(self, "tag_eye", (-4, 0, 2), (120, 0, 0));
}

gasmask_off_npc()
{
	if(IsDefined(self.gasmask))
		self.gasmask Delete();
}

ally_keep_player_distance(ideal_distance, min_rate, max_rate, slope)
{
	
	self endon( "death" );
	// default values
	if(!IsDefined(min_rate)) min_rate = 0.7;
	if(!IsDefined(max_rate)) max_rate = 1.3;
	if(!IsDefined(slope)) slope = .5;
	
	// only one running at a time	
	self notify("ally_keep_player_distance_stop");
	self endon("ally_keep_player_distance_stop");
			
	// 0 to 1, lower values are smoother, framerate dependent
	rate_smoothing = .05;
	
	// each heuristic counts as 1, this is the number that must agree for max rate change
	heuristic_count = 1.5;
	
	// computed constants
	rate_unsmoothing = 1 - rate_smoothing;
	if(ideal_distance > 0)
	{
		min_rate_distance = ideal_distance * ((1 - min_rate) / slope + 1);
		max_rate_distance = ideal_distance * ((1 - max_rate) / slope + 1);
	}
	else
	{
		min_rate_distance = -1 * ideal_distance * ((1 - min_rate) / slope + 1) + ideal_distance * 2;
		max_rate_distance = -1 * ideal_distance * ((1 - max_rate) / slope + 1) + ideal_distance * 2;
	}
	center_rate = linear_map_clamp(ideal_distance, min_rate_distance, max_rate_distance, min_rate, max_rate);
	Assert(abs(center_rate - 1) < .001);
	Assert(min_rate_distance > max_rate_distance);
	
	last_rate = self.moveplaybackrate;
	
	for(;; waitframe())
	{
		// no heuristic if we're not moving, so we start more smoothly
		if(IsDefined(self.velocity) && Length(self.velocity) < .01)
		{
			self.moveplaybackrate = 1;
			last_rate = 1;
			continue;
		}
		
		player_to_self = flat_origin(self.origin - level.player.origin);
		player_to_self_dir = VectorNormalize(player_to_self);
	
		self_forward = AnglesToForward(flat_angle(self.angles));
		player_forward = AnglesToForward(flat_angle(level.player GetPlayerAngles()));
		
		flow = (0, 0, 0);
		
		// If I have a goal, and it's in front of the player, flow is from me to the goal.
		if(IsDefined(self.goalpos) && Distance(self.goalpos, self.origin) > 32)
		{
			player_to_goal = VectorNormalize(flat_origin(self.goalpos - level.player.origin));			
			flow += player_to_goal * clamp(VectorDot(player_to_goal, player_forward), 0, 1);
		}
		
		// If i'm facing the same way as the player, flow is in my facing direction.
		flow += self_forward * clamp(VectorDot(self_forward, player_forward), 0, 1);
		
		// If I'm facing the player, flow is towards the player.
		flow += -1.0 * player_to_self_dir * clamp(-1.0 * VectorDot(player_to_self, self_forward), 0, 1);
		
		heuristic_strength = clamp(Length(flow) / heuristic_count, 0, 1);
		
		if(IsDefined(self.goalpos))
		{
			// heuristic strength gets attenuated when you're close to your goal so we don't screw up transitions
			// by being at an odd speed
			start_attenuate = 96;
			stop_attenuate = 64;
			heuristic_strength *= clamp((Distance(self.goalpos, self.origin) - stop_attenuate) / (start_attenuate - stop_attenuate), 0, 1);
		}


		flow_dir = VectorNormalize(flow);
		
		distance = VectorDot(player_to_self, flow_dir);
		
		raw_rate = linear_map_clamp(distance, min_rate_distance, max_rate_distance, min_rate, max_rate);
		
		heuristic_rate = (raw_rate - 1) * heuristic_strength + 1;
						
		smooth_rate = heuristic_rate * rate_smoothing + last_rate * rate_unsmoothing;
				
		// for now, we never change the animation sets
		last_rate = self.moveplaybackrate;
		
		self.moveplaybackrate = smooth_rate;		
		
		///#
		//arrow_origin = self.origin + (0, 0, 4);
		//desired_pos = level.player.origin + flow_dir * ideal_distance;					
		//desired_pos = self.origin + flow_dir * (distance - ideal_distance);
		//draw_arrow(arrow_origin, arrow_origin + flow * 40, (1, 1, 1));
		//draw_arrow(arrow_origin, (desired_pos[0], desired_pos[1], arrow_origin[2]), (1, 0, 1));
		//Print3d(self.origin + (0, 0, 64), "" + smooth_rate);
		//#/
	}	
}

ally_keep_player_distance_stop()
{
	self notify("ally_keep_player_distance_stop");
	self.moveplaybackrate = 1;
}

linear_map(x, in_min, in_max, out_min, out_max)
{
	return out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min);
}

linear_map_clamp(x, in_min, in_max, out_min, out_max)
{
	return clamp(linear_map(x, in_min, in_max, out_min, out_max), out_min, out_max);
}

angle_lerp(from, to, fraction)
{
	return AngleClamp(from + AngleClamp180(to - from) * fraction);	
}

euler_lerp(from, to, fraction)
{
	return (
	angle_lerp(from[0], to[0], fraction),
	angle_lerp(from[1], to[1], fraction),
	angle_lerp(from[2], to[2], fraction)
	);	
}

fire_while_moving()
{
	self endon( "death" );
	self.accuracy = 0.08;
	self enable_heat_behavior( true );
}

lower_accuracy()
{
	self endon( "death" );
	self.accuracy = 0.08;
}	

// fake death
bloody_death( delay )
{
	self endon( "death" );

	if( !IsSentient( self ) || !IsAlive( self ) )
	{
		return;
	}

	if( IsDefined( self.bloody_death ) && self.bloody_death )
	{
		return;
	}

	self.bloody_death = true;

	if( IsDefined( delay ) )
	{
		wait( RandomFloat( delay ) );
	}

	tags = [];
	tags[0] = "j_hip_le";
	tags[1] = "j_hip_ri";
	tags[2] = "j_head";
	tags[3] = "j_spine4";
	tags[4] = "j_elbow_le";
	tags[5] = "j_elbow_ri";
	tags[6] = "j_clavicle_le";
	tags[7] = "j_clavicle_ri";

	for( i = 0; i < 3 + RandomInt( 5 ); i++ )
	{
		random = RandomIntRange( 0, tags.size );
		//vec = self GetTagOrigin( tags[random] );
		self thread bloody_death_fx( tags[random], undefined );
		wait( RandomFloat( 0.1 ) );
	}

	self DoDamage( self.health + 50, self.origin );
}

bloody_death_fx( tag, fxName )
{
	if( !IsDefined( fxName ) )
	{
		fxName = level._effect["flesh_hit"];
	}

	PlayFxOnTag( fxName, self, tag );
}


/#
debug_npc_count()
{
	dvar_name = "debug_npc_count";
	SetDevDvar(dvar_name, "0");
		
	for(;; wait(1))
	{
		if(GetDebugDvar(dvar_name) != "0")
		{
			debug_print("AI Count: " + GetAICount());
		}
	}
}
#/

/#
debug_test_dialogue()
{
	dvar_name = "debug_dialogue_test";
	SetDevDvar(dvar_name, "0");
		
	for(;; wait(1))
	{
		if(GetDebugDvar(dvar_name) != "0")
		{
			SetDevDvar(dvar_name, "0");
			debug_test_dialogue_execute();
		}
	}
}

debug_test_dialogue_execute()
{
	friendlies = SortByDistance(GetAIArray("allies"), level.player.origin);
	AssertEx(friendlies.size != 0, "Couldn't find a friendly to play the dialogue");
	guy = friendlies[0];
	
	foreach(character, lines in level.scr_sound)
	{
		if(IsArray(lines))
		{
			foreach(line, sound in lines)
			{
				if(SoundExists(sound))
				{
					// not playing in the usual way because we need to override animname (gah, so inflexible)
					debug_print("playing " + sound);
					guy anim_single_solo(guy, line, undefined, 0, character);
				}	
				else
				{
					debug_print("ERROR: missing sound " + sound);
				}
			}
		}
	}
	foreach(line, sound in level.scr_radio)
	{
		if(SoundExists(sound))
		{
			debug_print("playing radio " + sound);
			radio_dialogue(line);
		}
		else
		{
			debug_print("ERROR: missing sound " + sound);
		}
	}
}
#/
	
	
// system to monitor events and make trees windy.
//   there's a wind system in _animatedmodels but it is
//   insufficient (sets wind globally)
windy_tree_system()
{
	thread monitor_all_tree_damage();
	
	windy_trees = [];
	
	// gather all the potential windy trees
	animated_models = GetEntArray( "animated_model", "targetname" );
	foreach ( model in animated_models )
	{
		keys = GetArrayKeys( level.anim_prop_models[ model.model ] );
		foreach ( key in keys )
		{
			if ( key == "windy_idle" )
			{
				windy_trees[ windy_trees.size ] = model;
			}
		}
	}
	
	// monitor windy events to decide when to make trees windy
	while ( true )
	{
		level waittill( "wind_blast", blast_origin, blast_radius, fade_in_time, fade_out_time, duration, ignore_z );
		
		foreach ( windy_tree in windy_trees )
		{
			distance_to_blast = undefined;
			if ( IsDefined( ignore_z ) && ignore_z )
			{
				windy_tree_xy = ( windy_tree.origin[0], windy_tree.origin[1], 0 );
				blast_origin_xy = ( blast_origin[0], blast_origin[1], 0 );
				distance_to_blast = Distance( windy_tree_xy, blast_origin_xy );
			}
			else
			{
				distance_to_blast = Distance( windy_tree.origin, blast_origin );
			}
			
			if ( distance_to_blast < blast_radius )
			{
				windy_tree thread shake_tree( fade_in_time, fade_out_time, duration );
			}
		}
	}
}

monitor_all_tree_damage()
{
	tree_damage_triggers = GetEntArray( "tree_damage_trigger", "targetname" );
	foreach ( tree_damage_trigger in tree_damage_triggers )
	{
		tree_damage_trigger thread monitor_tree_damage();
	}
}

monitor_tree_damage()
{
	self endon( "death" );
	
	while ( true )
	{
		self waittill( "damage", amount, attacker, direction, pos, mod );
		if ( mod == "MOD_GRENADE" || mod == "MOD_GRENADE_SPLASH" || mod == "MOD_PROJECTILE" || mod == "MOD_PROJECTILE_SPLASH" || mod == "MOD_EXPLOSIVE" )
		{
			level notify( "wind_blast", pos, 512, 0.2, 0.2, 1 );
		}
	}
}

shake_tree( fade_in_time, fade_out_time, duration )
{
	self notify( "playing_windy_idle" );
	self endon( "playing_windy_idle" );
	
	windy_idle_anim = level.anim_prop_models[ self.model ][ "windy_idle" ];

	self SetAnim( windy_idle_anim, 1, fade_in_time, 1 );
	wait duration;
	self ClearAnim( windy_idle_anim, fade_out_time );
}

// function to constantly send "wind_blast" notifies from ent's position.
//  Used by helicopters to get trees to play windy_idle.
//  wind_radius = radius that trees are affected
//  ignore_z = ignore height when doing radius distance check
entity_blast_wind( wind_radius, ignore_z )
{
	self endon( "death" );
	
	while ( true )
	{
		level notify( "wind_blast", self.origin, wind_radius, 0.2, 0.5, 1, ignore_z );
		wait 0.5;
	}
}

// a system to get a random element from an array without repeating elemnts
// generally useful for dialogue
// example usage:
//
// lines = randomizer_create(["foo", "bar", "baz"]);
// in a loop:
//     line = lines randomizer_get_no_repeat();
//
randomizer_create(array)
{
	Assert(array.size != 0);
	randomizer = SpawnStruct();
	randomizer.array = array;	
	return randomizer;
}

randomizer_get_no_repeat()
{
	Assert(self.array.size > 0);
	
	index = undefined;
	if(self.array.size > 1 && IsDefined(self.last_index))
	{
		index = RandomInt(self.array.size - 1);
		if(index >= self.last_index)
			index++;
	}
	else
	{
		index = RandomInt(self.array.size);
	}
	self.last_index = index;
	return self.array[index];
}

randomizer_get()
{
	return random(self.array);
}

introscreen_generic_fade_out( shader, pause_time, fade_in_time, fade_out_time )
{
	if ( !isdefined( fade_in_time ) )
		fade_in_time = 1.5;

	introblack = NewHudElem();
	introblack.x = 0;
	introblack.y = 0;
	introblack.horzAlign = "fullscreen";
	introblack.vertAlign = "fullscreen";
	introblack.foreground = true;
	introblack SetShader( shader, 640, 480 );

	if ( IsDefined( fade_out_time ) && fade_out_time > 0 )
	{
		introblack.alpha = 0;
		introblack FadeOverTime( fade_out_time );
		introblack.alpha = 1;
		wait( fade_out_time );
	}

	wait pause_time;

	// Fade out black
	if ( fade_in_time > 0 )
		introblack FadeOverTime( fade_in_time );

	introblack.alpha = 0;
	
	wait fade_in_time;
	
	introblack destroy();
	
}

// Sets a specific quote to be used when the player dies.
// Call alternate_deadquote_stop() to go back to the usual random wisdom quotes.
//
// Use this instead of setting the ui_deadquote dvar directly, because since that is not a saved
// dvar, there will be bugs if it is not set immediately before the player's death or MissionFailed()
alternate_deadquote(deadquote)
{		
	thread alternate_deadquote_internal(deadquote);
}


alternate_deadquote_internal(deadquote)
{
	// kill the normal death quote choosing code
	level notify( "new_quote_string" );
	level endon( "new_quote_string" );
	
	level endon( "mine death" );

	// player can be dead if the player died at the same point that setDeadQuote was called from another script
	if ( isalive( level.player ) )
		level.player waittill( "death" );
	
	if ( !level.missionfailed )
	{
		SetDvar("ui_deadquote", deadquote);
	}
}

alternate_deadquote_stop()
{
	// restart the usual death quote stuff
	level thread maps\_quotes::setDeadQuote();
}


vehicle_get_driver()
{
	foreach(guy in self.attachedguys)
	{
		if(IsDefined(guy.drivingVehicle) && guy.drivingVehicle)
			return guy;
	}	
}

vehicle_get_crash_struct(min_time, max_time, max_angle_degrees, slowdown_factor)
{
	crash_speed_ips = self Vehicle_GetSpeed() * 17.6 * slowdown_factor;
	min_range_sq = squared(crash_speed_ips * min_time);
	max_range_sq = squared(crash_speed_ips * max_time);
	min_dp = Cos(max_angle_degrees);
	
	crash_structs = SortByDistance(GetStructArray("vehicle_crash_struct", "script_noteworthy"), self.origin);
	
	foreach(crash_struct in crash_structs)
	{
		distance_sq = DistanceSquared(crash_struct.origin, self.origin);
		if(distance_sq < min_range_sq)
			continue;
		if(distance_sq > max_range_sq)
			break;
		if(IsDefined(crash_struct.used))
			continue;
		if(VectorDot(VectorNormalize(crash_struct.origin - self.origin), AnglesToForward(self.angles)) < min_dp)
			continue;
		
		return crash_struct;		
	}
	return undefined;
}

vehicle_wait_for_crash(args)
{
	self thread notify_delay("max_time", args.wait_time);
	self thread vehicle_detect_crash(args);
	// jolt seems to trigger too easily
	msg = self waittill_any_return("max_time", /*"veh_jolt",*/ "veh_collision", "script_vehicle_collision", "detect_crash");
	if(!IsDefined(msg))
		msg = "unknown";
	/#	
	debug_print("vehicle died from msg " + msg);
	#/	
	self notify("stop_vehicle_detect_crash");
}

vehicle_detect_crash(args)
{
	self endon("stop_vehicle_detect_crash");
	// delay until vehicle_wait_for_crash() is waiting for us
	waittillframeend;
	
	min_player_distance_sq = squared(39*6);
	if(IsDefined(level.vehicle_death_radiusdamage[self.classname]) && IsDefined(level.vehicle_death_radiusdamage[self.classname].range))
		min_player_distance_sq = squared(level.vehicle_death_radiusdamage[self.classname].range * .75);
	
	for(;; waitframe())
	{
		if(abs(AngleClamp180(self.angles[0])) > 30 || abs(AngleClamp180(self.angles[2])) > 30)
		{
			/# debug_print("detect_crash tilt"); #/	
			break;
		}
		if(DistanceSquared(self.origin, level.player.origin) < min_player_distance_sq)
		{
			/# debug_print("detect_crash too close to player"); #/	
			break;
		}
		if(self Vehicle_GetSpeed() / args.crash_speed_mph < .25)
		{
			/# debug_print("detect_crash speed"); #/
			break;
		}
		if(VectorDot(args.goal_pos - self.origin, args.vehicle_to_crash_struct_dir) < 0)
		{
			/# debug_print("detect_crash past goal"); #/
			break;
		}
	}
	self notify("detect_crash");
}

vehicle_crazy_steering(args)
{	
	max_angle = 45; // must be less than 90
	accel_time = 4;
	
	lookahead = 39*5;
	max_sideways = lookahead * Tan(max_angle);
		
	init_speed_mph = self Vehicle_GetSpeed();
	elapsed_time = 0;
	
	self endon("death");
	for(;;)
	{
		right_of_center = false;
		if(VectorDot(args.crash_struct.origin - self.origin, args.right_dir) < 0)
			right_of_center = true;
				
		sideways = RandomFloat(max_sideways);
		if(right_of_center)
			sideways *= -1;
		
		goal_pos = self.origin + args.vehicle_to_crash_struct_dir * lookahead + args.right_dir * sideways;
		
		t = clamp(elapsed_time / accel_time, 0, 1);
		speed_mph = linear_interpolate(t, init_speed_mph, args.crash_speed_mph);
		
		self vehicleDriveTo(goal_pos, args.crash_speed_mph);	
		
		/#
		//draw_arrow_time(self.origin, goal_pos, (255, 0, 0), .1);
		#/
		
		delay = RandomFloatRange(.05, .2);
		elapsed_time += delay;
		wait(delay);		
	}
}

// Call this on a vehicle if you want it to crash in pre-determined locations when the driver of the vehicle dies.
// To define the locations, you must link nodes on the vehicle's path to script_structs that have a script_noteworthy of "vehicle_crash_struct".
// This only works for physics vehicles.
paris_vehicle_death()
{
	self thread vehicle_crash_when_driver_dies();
	self thread vehicle_crash_on_death();
	self thread vehicle_crash_when_blocked();
}


vehicle_crash_when_driver_dies()
{
	AssertEx(IsDefined(self.script_allow_driver_death) && self.script_allow_driver_death, "script_allow_driver_death should be set the vehicle or vehicle_crash_when_driver_dies() won't work");
	
	self endon("death");

	self.vehicle_keeps_going_after_driver_dies = true;  // disable the system in _vehicle_aianim.gsc
	
	driver = self vehicle_get_driver();
	if(!IsDefined(driver))
	{
		AssertEx(false, "vehicle_crash_when_driver_dies() counldn't find a driver, so we're returning early");
		return;
	}
	driver waittill("death");
	if(IsDefined(driver))
		PlayFxOnTag( getfx( "blood_gaz_driver" ), driver, "tag_eye" );
		
	/#
	if(!IsDefined(self.vehicle_crashing_now)) debug_print("vehicle crashing because driver died");
	#/
	
	attacker = undefined;
	if(IsDefined(driver))
		attacker = driver.lastattacker;
		
	self vehicle_crash_now(attacker);
}

vehicle_crash_on_death()
{
	self.vehicle_stays_alive = true;
	while(self.health > 0)
	{
		self waittill("damage");
		waittillframeend;  // to let friendlyfire_sheild process our health
		
		if(self.health < self.healthbuffer)
			break;	
	}
	
	/#
	if(!IsDefined(self.vehicle_crashing_now)) debug_print("vehicle crashing because of damage");
	#/
	
	
	self vehicle_crash_now(self.attacker);
	
}

vehicle_crash_when_blocked()
{
	self endon("death");
	
	height = 24;
	start_forward = 39;
	end_forward = 39*4;
	
	attacker = undefined;
	
	for(;; wait .5)
	{
		start = self LocalToWorldCoords((start_forward, 0, height));
		end = self LocalToWorldCoords((end_forward, 0, height));
		
		result = BulletTrace(start, end, false, self);
		entity = result["entity"];
		if(IsDefined(entity))
		{
			
			if(entity.code_classname == "script_model" ||
				(entity.code_classname == "script_vehicle" && entity.health <= 0))
			{
				attacker = entity.attacker;				
				break;
			}
		}
		
		if(IsDefined(self.vehicle_crashing_now))
			return;
	}
	
	self thread vehicle_crash_now(attacker);
}

vehicle_crash_now(attacker)
{	
	// we look for a struct we can hit in this amount of time
	min_time = .75;
	max_time = 3;
	// only structs within this angle of our forward
	max_angle_degrees = 60;
	// we will slow down by this amount when crashing
	slowdown_factor = 1.5;
	// we overshoot the struct by this far when calling driveto
	overshoot_distance = 39*1;
	// adjust the time before blowing up by this factor
	wait_time_fudge_factor = 1.8;

	if(IsDefined(self.vehicle_crashing_now))
		return;
	self.vehicle_crashing_now = true;
	self notify("vehicle_crashing_now");

	crash_struct = vehicle_get_crash_struct(min_time, max_time, max_angle_degrees, slowdown_factor);
	if(IsDefined(crash_struct))
	{
		crash_struct.used = true;		
						
		args = SpawnStruct();
		args.crash_struct = crash_struct;
		args.vehicle = self;
		
		args.vehicle_to_crash_struct = args.crash_struct.origin - args.vehicle.origin;
		args.vehicle_to_crash_struct_dir = VectorNormalize(args.vehicle_to_crash_struct);
		args.right_dir = AnglesToRight(flat_angle(VectorToAngles(args.vehicle_to_crash_struct_dir)));
		args.goal_pos = args.crash_struct.origin + VectorNormalize(args.vehicle_to_crash_struct) * overshoot_distance;
		args.crash_speed_ips = max(self Vehicle_GetSpeed() * 17.6 * slowdown_factor, 1);
		args.crash_speed_mph = args.crash_speed_ips / 17.6;
		args.wait_time = Length(args.vehicle_to_crash_struct) / args.crash_speed_ips * wait_time_fudge_factor;
	
		self thread vehicle_crazy_steering(args);

		/#
		//draw_arrow_time(self.origin, args.goal_pos, (0, 255, 0), args.wait_time);
		#/
		
		vehicle_wait_for_crash(args);	
	}		
	else
	{
		/#
		debug_print("Tried to crash but couldn't find a suitable vehicle_crash_struct");	
		#/
	}
	
	
	self.vehicle_stays_alive = undefined;
	
	// grr, why can't code handle undefined arguments consistently?
	if(IsDefined(attacker))
		self DoDamage(self.health + 2000, self.origin, attacker, self);
	else
		self DoDamage(self.health + 2000, self.origin);
}

change_turret_accuracy_over_time( start_accuracy, end_accuracy, time )
{
	if ( IsDefined( self.mgturret ) )
	{
		foreach ( turret in self.mgturret )
		{
			if ( IsDefined( turret ) )
			{
				turret thread change_accuracy_over_time( start_accuracy, end_accuracy, time );
			}
		}
	}
}

change_accuracy_over_time( start_accuracy, end_accuracy, time )
{
	self endon( "death" );
	
	// wait until turret is owned
	while ( !IsDefined( self.aiowner ) )
	{
		wait 0.05;
	}
	
	self.aiowner endon( "death" );
	self.aiowner.ignoreme = true;
	self.aiowner.ignorerandombulletdamage = true;
	
	self SetMode( "manual_ai" );
	self SetTargetEntity( level.player, (0,0,32) );
	
	// wait until the turret is actually firing
	if ( !IsDefined( self.turretState ) || self.turretState != "fire" )
	{
		self waittill( "startfiring" );
	}
	
	start_time = GetTime();
	end_time = start_time + ( time * 1000 );
	
	time_pct = 0;
	while ( time_pct < 1 )
	{
		lerp_accuracy = ( ( end_accuracy - start_accuracy ) * time_pct ) + start_accuracy;
		self SetAISpread( lerp_accuracy );
		wait 0.05;
		time_pct = ( GetTime() - start_time ) / ( end_time - start_time );
	}

	self SetAISpread( end_accuracy );
}

// If your view is linked and you're pushing against the limits, and we unlink you, you will start movign very jerkily.
// Call this function a short time before unlinking, and we will lerp the view limits over time so that, if you are
// straining against the clamp limits, by the time you do unlink, your view is rotating at the rate it will be when
// you spin while not linked.
// You need to pass in the original clamp limits, and the time left before you unlink.
player_smooth_unclamp(duration, orig_clamp_right, orig_clamp_left, orig_clamp_top, orig_clamp_bottom)
{
	Assert(IsPlayer(self));
	Assert(duration > 0);
	Assert(orig_clamp_right  < 180);
	Assert(orig_clamp_left   < 180);
	Assert(orig_clamp_top    <  90);
	Assert(orig_clamp_bottom <  90);
	
	// these are const dvars, but can't even be read from script, so using their default values
	aim_turnrate_pitch     =  90.0;
	aim_turnrate_pitch_ads =  55.0;
	aim_turnrate_yaw       = 260.0;
	aim_turnrate_yaw_ads   =  90.0;
	
	sensitivity = self GetLocalPlayerProfileData("viewSensitivity");
	if(!IsDefined(sensitivity))
		sensitivity = 1;
	sensitivity = Float(sensitivity);
	if(sensitivity < .001)
		sensitivity = 1;	
	
	max_pitch_dps = aim_turnrate_pitch * sensitivity;
	max_yaw_dps   = aim_turnrate_yaw   * sensitivity;
	
	// if we don't have enough distance to travel, we will need to reduce the duration
	// and wait a bit before starting to unclamp.
	time_needed = duration;
	time_needed = Min(time_needed, 2 * (180 - orig_clamp_right ) / max_yaw_dps  );
	time_needed = Min(time_needed, 2 * (180 - orig_clamp_left  ) / max_yaw_dps  );
	time_needed = Min(time_needed, 2 * ( 90 - orig_clamp_top   ) / max_pitch_dps);
	time_needed = Min(time_needed, 2 * ( 90 - orig_clamp_bottom) / max_pitch_dps);
	
	Assert(time_needed > 0);
	
	wait_before_unclamp = duration - time_needed;
	if(wait_before_unclamp > 0)
		wait wait_before_unclamp;
	
	if(IsAlive(self) && self IsLinked())
	{
		self LerpViewAngleClamp(
			time_needed,
			time_needed,
			0,
			Min(180, orig_clamp_right  + 0.5 * time_needed * max_yaw_dps  ),
			Min(180, orig_clamp_left   + 0.5 * time_needed * max_yaw_dps  ),
			Min( 90, orig_clamp_top    + 0.5 * time_needed * max_pitch_dps),
			Min( 90, orig_clamp_bottom + 0.5 * time_needed * max_pitch_dps)
		);
	}

	wait(time_needed);		
}

/*
=============
///ScriptDocDisable - We shouldn't be putting level specific scripts in documentation. - Nate
"Name: scripted_sequence_recon( <scene_id_string>, <bPlayed>, <view_check_origin_or_ai>, <delay> )"
"Summary: Tells the Recon server whether a scripted sequence was played and seen by the player."
"Module: paris_shared"
"CallOn: none"
"MandatoryArg: <scene_id_string>: The name of the sequence, will populate the 'scene' field of the event record"
"MandatoryArg: <bPlayed>: true if the scene was played, false if it was skipped."
"OptionalArg: <view_check_origin_or_ai>: After the delay, we will check whether the player can see this position.  Pass either a vector or an AI."
"OptionalArg: <delay>: Wait this long before checking the position.  Even with nonzero delay, this function returns immediately."
"Example: scripted_sequence_recon("my_awesome_scene", true, main_actor_in_scene, time_of_coolest_moment);"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
scripted_sequence_recon(scene_id_string, bPlayed, view_check_origin_or_ai, delay)
{
	//{NOT_IN_SHIP
	thread scripted_sequence_recon_internal(scene_id_string, bPlayed, view_check_origin_or_ai, delay);
	//}NOT_IN_SHIP
}

//{NOT_IN_SHIP
scripted_sequence_recon_internal(scene_id_string, bPlayed, view_check_origin_or_ai, delay)
{
	view_check_origin = undefined;
	if(bPlayed && !IsAi(view_check_origin_or_ai))
	{
		view_check_origin = view_check_origin_or_ai;
	}
	
	if(IsDefined(delay))
		wait delay;
	
	if(bPlayed && !IsDefined(view_check_origin) && IsAI(view_check_origin_or_ai) && IsAlive(view_check_origin_or_ai))
	{
		view_check_origin = view_check_origin_or_ai GetShootAtPos();
	}
	
		seen = false;
		if(bPlayed && IsDefined(view_check_origin))
		{
			if(level.player can_see_origin(view_check_origin, false))
			{
				seen = true;
			}
		}
		
		ReconSpatialEvent(level.player.origin, "script_scripted_sequence: scene %s, played %b, seen %b", scene_id_string, bPlayed, seen);
	
	/#
		if(GetDebugDvar("debug_scripted_sequence_recon") == "1")
		{
			debug_print("recon scene:" + scene_id_string + " played: " + bPlayed + " seen: " + seen);
			if(IsDefined(view_check_origin))
			{
				color = (0, 1, 0);
				if(!seen)
					color = (1, 0, 0);
				
				for(i = 0; i < 10 * 20; i++)
				{
					Print3D(view_check_origin, scene_id_string, color);
					waitframe();
	}
			}
		}
	#/
}
	//}NOT_IN_SHIP

lerp_move_speed_scale(oldSpeedScale, targetSpeedScale, totalSeconds)
{
	Assert(IsPlayer(self));
	Assert(totalSeconds > 0);
	
	self notify("lerp_move_speed_scale");
	self endon("lerp_move_speed_scale");
	
	startSeconds = GetTime() * .001;
	for(;;)
	{
		currentSeconds = GetTime() * .001 - startSeconds;
		if(currentSeconds >= totalSeconds)
			break;
		self SetMoveSpeedScale(linear_interpolate(currentSeconds / totalSeconds, oldSpeedScale, targetSpeedScale));
		waitframe();
	}
	self SetMoveSpeedScale(targetSpeedScale);
}

setup_ignore_suppression_triggers()
{
	triggers = GetEntArray("trigger_ignore_suppression", "targetname");	
	foreach(trigger in triggers)
	{
		level thread ignore_suppression_trigger_think(trigger);	
	}
}

ignore_suppression_trigger_think(trigger)
{
	for(;;)
	{
		trigger waittill("trigger", other);
		if(IsDefined(other) &&  IsAI(other) && !other IsBadGuy())
		{
			other thread ignore_suppression_trigger_ai_think(trigger);	
		}		
	}	
}

ignore_suppression_trigger_ai_think(trigger)
{
	// self is the ai
	
	self notify("ignore_suppression_trigger_ai_think_stop");
	self endon("ignore_suppression_trigger_ai_think_stop");
	self endon("death");
	
	self set_ignoresuppression(true);
	
	while(self IsTouching(trigger))
	{
		wait .5;	
	}
	
	self set_ignoresuppression(false);
}

setup_ignore_all_triggers()
{
	triggers = GetEntArray("trigger_ignore_all", "targetname");	
	foreach(trigger in triggers)
	{
		level thread ignore_all_trigger_think(trigger);	
	}
}

ignore_all_trigger_think(trigger)
{
	for(;;)
	{
		trigger waittill("trigger", other);
		if(IsDefined(other) && other IsBadGuy())
		{
			other thread ignore_all_trigger_ai_think(trigger);	
		}		
	}	
}

ignore_all_trigger_ai_think(trigger)
{
	// self is the ai
	
	self notify("ignore_all_trigger_ai_think_stop");
	self endon("ignore_all_trigger_ai_think_stop");
	self endon("death");
	
	self set_ignoreall(true);
	self setFlashbangImmunity(true);
	
	while(self IsTouching(trigger))
	{
		wait .05;	
	}
	
	self set_ignoreall(false);
	self setFlashbangImmunity(false);
}

bomb_truck_hide_windshield()
{
	level.bomb_truck_model HidePart("windshield01");	
	level.bomb_truck_model HidePart("windshield02");
	level.bomb_truck_model HidePart("windshield03");
	level.bomb_truck_model HidePart("windshield04");
	level.bomb_truck_model HidePart("windshield05");
}

path_squad_with_trigger(targetname, touch_once)
{
	next_color_nodes = GetEnt( targetname, "targetname" );
	
	if(IsDefined(next_color_nodes))
		next_color_nodes notify( "trigger", level.player );
	
	if(!IsDefined(touch_once)) touch_once = false;
	
	if(touch_once && IsDefined(next_color_nodes))
	{
		next_color_nodes trigger_off();
	}
}

hud_off()
{
	SetSavedDvar( "compass", "0" );
	SetSavedDvar( "ammoCounterHide", "1" );
	SetSavedDvar( "hud_showstance", "0" );
	SetSavedDvar( "actionSlotsHide", "1" );
}
	
hud_on()
{
	SetSavedDvar( "compass", "1" );
	SetSavedDvar( "ammoCounterHide", "0" );
	SetSavedDvar( "hud_showstance", "1" );
	SetSavedDvar( "actionSlotsHide", "0" );
}