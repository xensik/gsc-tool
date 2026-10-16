#include maps\_audio_presets_vehicles;
#include maps\_audio;
#include common_scripts\utility;

VM_init()
{
	if (!IsDefined(level._audio))
	{
		level._audio = spawnstruct();
	}
	
	if (!IsDefined(level._audio.veh))
	{
		level._audio.veh = spawnstruct();

		level._audio.veh.minrate = 0.1;
		level._audio.veh.defrate = 0.5;
		level._audio.veh.defsmooth = 0.1;
		level._audio.veh.minpitch = 0.5;
		level._audio.veh.maxpitch = 1.5;
		level._audio.veh.fadein_time = 2.0;
		// array of custom callbacks
		level._audio.veh.callbacks = [];
		
		level._audio.veh.print_speed = false;
		level._audio.veh.print_tilt = false;
		level._audio.veh.print_yaw = false;
		level._audio.veh.print_roll = false;
		level._audio.veh.print_altitude = false;
		level._audio.veh.print_throttle = false;
		
		// array of loaded presets and maps (so don't have to reload them all the time)
		level._audio.veh.presets = [];
		level._audio.veh.maps = [];
		level._audio.veh.instances = [];
		level._audio.veh.ducked_instances = [];
		level._audio.veh.duck_starts = []; // array of instances which cause ducking of engine sounds during a start/stop oneshot sound
		level._audio.veh.duck_stops = [];
	}
}

// registers a custom callback for the vehicle manager
VM_register_custom_callback(name, function)
{
	assert(IsString(name));
	assert(IsDefined(function));
	assert(IsDefined(level._audio.veh.callbacks));
	
	level._audio.veh.callbacks[name] = function;	
}

VM_start_preset(instance_name, preset_name, vehicle_entity, fadein_, startalias_, offset_)
{
	assert(IsString(instance_name));
	assert(IsString(preset_name));
	assert(IsDefined(vehicle_entity));
	
	wait(0.25);
	
	if (IsDefined(level._audio.veh.instances[instance_name]))
	{
		VM_stop_preset_instance(instance_name);
	}

	if (IsDefined(startalias_))
	{
		thread aud_play_linked_sound(startalias_, vehicle_entity, undefined, undefined, offset_);
	}

	level._audio.veh.instances[instance_name] = [];
	level._audio.veh.instances[instance_name]["entity"] = vehicle_entity;

	// don't reload the preset if we've already loaded it
	if (!IsDefined(level._audio.veh.presets[preset_name]))
	{
		preset = [];
		preset = AUDIO_PRESETS_VEHICLES(preset_name, preset);
		/#
		VMx_validate_preset(preset, preset_name);
		#/
		level._audio.veh.presets[preset_name] = preset;
	}
	
	assert(IsDefined(level._audio.veh.presets[preset_name]));
	
	level._audio.veh.instances[instance_name]["entity"] = vehicle_entity;
	
	// setup the looping callback functions
	foreach (param, settings in level._audio.veh.presets[preset_name])
	{
		// figure out which callback to call
		args = spawnstruct();
		
		
		args.instance_name = instance_name;
		args.vehicle = vehicle_entity;
		
		switch (param)
		{
			case "tilt":
				args.type = "tilt";
				args.callback = ::VMx_get_tilt;
				args.min = -45.0; // each param type will have different default absolute bounds
				args.max = 45.0;
			break;
			
			case "yaw":
				args.type = "yaw";
				args.callback = ::VMx_get_yaw;
				args.min = 0.0; // or -180.0 to 180.0
				args.max = 360.0;
			break;
			
			case "roll":
				args.type = "roll";
				args.callback = ::VMx_get_roll;
				args.min = -45.0;
				args.max = 45.0;
			break;
			
			case "speed":
				args.type = "speed";
				args.callback = ::VMx_get_speed;
				args.min = 0.0;
				args.max = 100.0;
			break;
			
			case "altitude":
				args.type = "altitude";
				args.callback = ::VMx_get_altitude;
				args.min = 0.0;
				args.max = 100.0;
			break;
			
			case "start_stop":
				args.type = "start_stop";
				args.callback = ::VMx_get_throttle;
				args.min = 0.0;
				args.max = 1.0;
			break;
				
			default:
				assert(false); // unrecognized param type, should never get here (VMx_validate_preset above should catch any problems already)
			break;
		}
		assert(IsDefined(args.callback));
			
		args.smoothness = level._audio.veh.defsmooth;
		args.smooth_up = undefined; // optional smooth values for going up or down
		args.smooth_down = undefined;
		args.updaterate = level._audio.veh.defrate;
		args.alias_data = [];
		
		args.fadein = 0.5;
		if (IsDefined(fadein_))
		{
			args.fadein = fadein_;
		}
		
		
		foreach ( key, value in settings)
		{
			// get user-definable parameters
			switch(value[0])
			{
				case "updaterate":
				args.updaterate = value[1];
				break;
				
				case "smoothness":
				args.smoothness = value[1];
				break;
				
				case "smooth_up":
				args.smooth_up = value[1];
				break;
				
				case "smooth_down":
				args.smooth_down = value[1];
				break;
				
				case "heightmax":
				args.heightmax = value[1];
				break;
				
				case "callback":
				custom_callback_name = value[1];
				args.custom_callback = level._audio.veh.callbacks[custom_callback_name];
				break;
				
				case "range":
				args.min = min(value[1], value[2]);
				args.max = max(value[1], value[2]);
				break;
				
				case "multiply_by_throttle":
				args.multiply_by_throttle = true;
				break;
				
				case "multiply_by_leftstick":
				args.multiply_by_leftstick = true;
				break;
				
				case "start":
				assert(args.type == "start_stop");
				args.start_alias_data = spawnstruct();
				args.start_alias_data.name = value[1];
				for (i = 2; i < value.size; i++)
				{
					if (IsArray(value[i]))
					{
						maptype = value[i][0];
						mapname = value[i][1];
						if (maptype == "pitch")
						{
							args.start_alias_data.pitch_map_name = mapname;
						}
						else if (maptype == "volume")
						{
							args.start_alias_data.volume_map_name = mapname;						
						}
						
						if (!IsDefined(level._audio.veh.maps[mapname]))
						{
							map = [];
							map = AUDIO_PRESETS_VEHICLE_MAPS(mapname, map); // map should already be validated
							level._audio.veh.maps[mapname] = map;
						}
					}
					else
					{
						level._audio.veh.duck_starts[instance_name] = value[i];
					}
				}
				break;
				
				case "stop":
				assert(args.type == "start_stop");
				args.stop_alias_data = spawnstruct();
				args.stop_alias_data.name = value[1];
				for (i = 2; i < value.size; i++)
				{
					if (IsArray(value[i]))
					{
						maptype = value[i][0];
						mapname = value[i][1];
						if (maptype == "pitch")
						{
							args.stop_alias_data.pitch_map_name = mapname;
						}
						else if (maptype == "volume")
						{
							args.stop_alias_data.volume_map_name = mapname;						
						}
						
						if (!IsDefined(level._audio.veh.maps[mapname]))
						{
							map = [];
							map = AUDIO_PRESETS_VEHICLE_MAPS(mapname, map); // map should already be validated
							level._audio.veh.maps[mapname] = map;
						}
					}
					else
					{
						level._audio.veh.duck_stops[instance_name] = value[i];
					}
				}
				break;
				
				case "throttle_input":
				args.throttle_input = value[1];
				break;
				
				case "on_threshold":
				assert(args.type == "start_stop");
				args.on_threshold = value[1];
				break;
				
				case "off_threshold":
				assert(args.type == "start_stop");
				args.off_threshold = value[1];
				break;
				
				case "oneshot_duck":
				assert(args.type != "start_stop");
				args.duck_amount = value[1];
				break;
				
				case "oneshot_duck_time":
				assert(args.type != "start_stop");
				args.duck_time = value[1];
				break;
				
				case "offset":
				args.offset = value[1];
				break;
				
				default:
				assert(args.type != "start_stop");
				// "value" is now this line: ["alias_name1", ["pitch", "mapping_name1"], ["volume", "mapping_name2"]]
				new_data = spawnstruct();
				new_data.alias_name = value[0]; // alias name
				
				for (i = 1; i < value.size; i++)
				{
					mapname = value[i][1];
					if (value[i][0] == "pitch")
					{
						new_data.pitch_map_name = mapname;
					}	
					else
					{
						new_data.vol_map_name = mapname;
					}
					
					// load the map preset if it hasn't been loaded already
					if (!IsDefined(level._audio.veh.maps[mapname]))
					{
						map = [];
						map = AUDIO_PRESETS_VEHICLE_MAPS(mapname, map); // map should already be validated
						level._audio.veh.maps[mapname] = map;
					}
				}
				args.alias_data[args.alias_data.size] = new_data; // store the data struct in the N-length array
				break;
			}
		}

		/#		
		// lets do some minor dev validation on this with smoothness, smooth_up, and smooth_down
		if (IsDefined(args.smooth_up))
		{
			assertEx(IsDefined(args.smoothness) || IsDefined(args.smooth_down), "If defining a \"smooth_up\", you need to define either a \"smoothness\" or a \"smooth_down\"");
		}
		if (IsDefined(args.smooth_down))
		{
			assertEx(IsDefined(args.smoothness) || IsDefined(args.smooth_up), "If defining a \"smooth_down\", you need to define either a \"smoothness\" or a \"smooth_up\"");
		}
		#/
		
		if (args.type == "start_stop")
		{
			thread VMx_do_start_stop_callback(args);
		}
		else
		{
			thread VMx_callback(args); 
		}
	}	
}

VM_stop(fade_)
{
	level notify("aud_veh_stop");

	fade = 1.0;
	if (IsDefined(fade_))
	{
		fade = max(0.1, fade_);
	}
	
	foreach(playing_preset_sounds in level._audio.veh.playing_presets)
	{
		assert(IsDefined(playing_preset_sounds.size));
		
		if (playing_preset_sounds.size > 0)
		{			
			// stop all the sound handles (fading them out)
			foreach( sndEntity in playing_preset_sounds )
			{
				thread aud_fade_out_and_delete(sndEntity, fade);
			}
		}
	}
	level._audio.veh.playing_presets = [];
}

VM_stop_preset_instance(instance_name, fade_)
{
	fade = 1.0;
	if (IsDefined(fade_))
		fade = max(0.01, fade_);
		
	if (IsDefined(level._audio.veh.instances[instance_name]))
	{
		level notify("aud_veh_stop_" + instance_name);
		assert(IsDefined(level._audio.veh.instances[instance_name].size));
		if (level._audio.veh.instances[instance_name].size > 0)
		{
			foreach( key, sndEntity in level._audio.veh.instances[instance_name] )
			{
				if (key != "entity" && key != "speed" && key != "throttle")
				{
					sndEntity ScaleVolume(0.0, fade);
				}
			}
		}
		wait(fade + 0.05);
		if (level._audio.veh.instances[instance_name].size > 0)
		{
			foreach( key, sndEntity in level._audio.veh.instances[instance_name] )
			{
				if (key != "entity" && key != "speed" && key != "throttle")
				{
					sndEntity delete();
				}
			}
		}

		level._audio.veh.instances[instance_name] = undefined;
	}
}
// *** RUNTIME OVERRIDE PARAMETERS start_attack_heli
// These functions allow you to adjust vehicle preset settings in runtime so that you can adjust vehicle preset
// behavior to changing environments. These functions only affect the currently playing vehicle preset, subsequent calls
// to VM_start_preset will erase any stored data due to these functions.

// call on vehicle entity
VM_set_range(type, min, max)
{
	assert(IsDefined(type));
	assert(IsDefined(min));
	assert(IsDefined(max));

	if ( !isdefined(self.aud_overrides))
	{
		self.aud_overrides = [];
	}
	
	self.aud_overrides[type] = spawnstruct();

	self.aud_overrides[type].min_range = min;
	self.aud_overrides[type].max_range = max;
}


VMx_monitor_oneshot_ent()
{
	self.sound_playing = true;
	self waittill("sounddone");
	self.sound_playing = false;
}

// monitors for ending flags and deletes the sound entity 
VMx_waittill_endon_delete(instance_name)
{
	level waittill_any("aud_veh_stop", "aud_veh_stop_" + instance_name);
	assert(Isdefined(self.sound_playing));
	if (self.sound_playing) // gracefully stop the sound
	{
		self ScaleVolume(0.0, 0.1);
		wait(0.1);
		self StopSounds();
		wait(0.05);
	}
	self delete();
}

VMx_stop_sound(fade_)
{
	self scalevolume(0.0, 0.05);
	wait(0.05);
	self StopSounds();
	wait (0.05);
	self.sound_playing = false;
}

VMx_play_oneshot_sound(name)
{
	if (self.sound_playing)
	{
		self VMx_stop_sound(0.0);
	}
	self playsound(name, "sounddone");
	self thread VMx_monitor_oneshot_ent();
}

VMx_init_oneshot_ents(instance)
{
	if (!IsDefined(level._audio.veh.start_ents))
	{
		level._audio.veh.start_ents = [];
	}
	if (!IsDefined(level._audio.veh.stop_ents))
	{
		level._audio.veh.stop_ents = [];
	}
	if (!IsDefined(level._audio.veh.start_ent_count))
	{
		level._audio.veh.start_ent_count = [];
	}
	if (!IsDefined(level._audio.veh.stop_ent_count))
	{
		level._audio.veh.stop_ent_count = [];
	}
	
	level._audio.veh.start_ents[instance] = [];
	level._audio.veh.start_ent_count[instance] = 0;
	level._audio.veh.stop_ents[instance] = [];
	level._audio.veh.stop_ent_count[instance] = 0;
}

// returns whether or not the accompany vehicle paramter mapper/stream should duck with the playing start/stop oneshot sounds
VMx_get_need_to_duck(instance)
{
	do_duck = false;
	
	if (IsDefined(level._audio.veh.duck_starts[instance]) && level._audio.veh.duck_starts[instance] && VMx_get_start_sound_playing(instance))
	{
		do_duck = true;
	}
	
	if (IsDefined(level._audio.veh.duck_stops[instance]) && level._audio.veh.duck_stops[instance] && VMx_get_stop_sound_playing(instance))
	{
		do_duck = true;
	}
	return do_duck;
}

VMx_get_start_sound_playing(instance)
{
	assert(IsDefined(level._audio.veh.start_ents[instance]));
	
	
	if (level._audio.veh.start_ents[instance].size > 0)
	{
		return true;
	}
	return false;
}

VMx_get_stop_sound_playing(instance)
{
	assert(IsDefined(level._audio.veh.stop_ents[instance]));
	
	if (level._audio.veh.stop_ents[instance].size > 0)
	{
		return true;
	}
	return false;
}

VMx_scale_start_sound_pitch(val, fade, instance)
{
	assert(IsDefined(level._audio.veh.start_ents[instance]));
	
	foreach( ent in level._audio.veh.start_ents[instance])
	{
		if (IsDefined(ent))
		{
			ent setpitch(val, fade);
		}
	}
}

VMx_scale_stop_sound_pitch(val, fade, instance)
{
	assert(IsDefined(level._audio.veh.stop_ents[instance]));
	
	foreach( ent in level._audio.veh.stop_ents[instance])
	{
		if (IsDefined(ent))
		{
			ent setpitch(val, fade);
		}
	}
}

VMx_scale_start_sound_volume(val, fade, instance)
{
	assert(IsDefined(level._audio.veh.start_ents[instance]));
	
	foreach( ent in level._audio.veh.start_ents[instance])
	{
		if (IsDefined(ent))
		{
			ent scalevolume(val, fade);
		}
	}
}

VMx_scale_stop_sound_volume(val, fade, instance)
{
	assert(IsDefined(level._audio.veh.stop_ents[instance]));
	
	foreach( ent in level._audio.veh.stop_ents[instance])
	{
		if (IsDefined(ent))
		{
			ent scalevolume(val, fade);
		}
	}
}

VMx_play_start_sound(name, vehicle_ent, instance, offset_)
{
	assert(IsDefined(level._audio.veh.start_ents[instance]));

	offset = 0;
	if (IsDefined(offset_))
	{
		offset = offset_;
	}	
	ent = spawn("script_origin", vehicle_ent.origin);
	ent linkto(vehicle_ent, "tag_origin", (offset, 0, 0), (0,0,0));
	ent.ref = level._audio.veh.start_ent_count[instance];
	ent playsound(name, "sounddone");
	ent thread VMx_monitor_start_ent(instance);
	level._audio.veh.start_ents[instance][ent.ref] = ent;
	level._audio.veh.start_ent_count[instance]++;
}

VMx_play_stop_sound(name, vehicle_ent, instance, offset_)
{
	assert(IsDefined(level._audio.veh.stop_ents[instance]));
	
	offset = 0;
	if (IsDefined(offset_))
	{
		offset = offset_;
	}
	
	ent = spawn("script_origin", vehicle_ent.origin);
	ent linkto(vehicle_ent, "tag_origin", (offset, 0, 0), (0,0,0));
	ent.ref = level._audio.veh.stop_ent_count[instance];
	ent playsound(name, "sounddone");
	level._audio.veh.stop_ents[instance][ent.ref] = ent;
	level._audio.veh.stop_ent_count[instance]++;
	wait(0.05);
	ent thread VMx_monitor_stop_ent(instance);

}

VMx_monitor_start_ent(instance)
{
	assert(IsDefined(level._audio.veh.start_ents[instance]));

	self endon("kill");
	self waittill("sounddone");
	level._audio.veh.start_ents[instance][self.ref] = undefined;
	// stop any duck instances if they exist
	if (IsDefined(level._audio.veh.ducked_instances[instance]))
	{
		level._audio.veh.ducked_instances[instance] = undefined;
	}
	self delete();
}

VMx_monitor_stop_ent(instance)
{
	assert(IsDefined(level._audio.veh.stop_ents[instance]));
	
	self endon("kill");
	self waittill("sounddone");
	level._audio.veh.stop_ents[instance][self.ref] = undefined;
		// stop any duck instances if they exist
	if (IsDefined(level._audio.veh.ducked_instances[instance]))
	{
		level._audio.veh.ducked_instances[instance] = undefined;
	}
	self delete();
}

VMx_stop_stop_ent(ent, fade_, instance)
{
	assert(IsDefined(level._audio.veh.stop_ents[instance]));
	
	// stop any duck instances if they exist
	if (IsDefined(level._audio.veh.ducked_instances[instance]))
	{
		level._audio.veh.ducked_instances[instance] = undefined;
	}
	
	fade = 0.1;
	if (IsDefined(fade_))
	{
		fade = fade_;
	}
	level._audio.veh.stop_ents[instance][ent.ref] = undefined;
	ent ScaleVolume(0.0, fade + 0.05);
	ent notify("kill");
	wait(fade+0.05);
	ent stopsounds();
	wait(0.05);
	ent delete();
}

VMx_stop_start_ent(ent, fade_, instance)
{
	assert(IsDefined(level._audio.veh.start_ents[instance]));
	
	// stop any duck instances if they exist
	if (IsDefined(level._audio.veh.ducked_instances[instance]))
	{
		level._audio.veh.ducked_instances[instance] = undefined;
	}
	
	fade = 0.1;
	if (IsDefined(fade_))
	{
		fade = fade_;
	}
	level._audio.veh.start_ents[instance][ent.ref] = undefined;
	ent ScaleVolume(0.0, fade + 0.05);
	ent notify("kill");
	wait(fade+0.05);
	ent stopsounds();
	wait(0.05);
	ent delete();
}


VMx_do_start_stop_callback(args)
{
	assert(IsDefined(args));
	assert(IsDefined(args.callback));
	assert(IsDefined(args.updaterate));
	assert(IsDefined(args.instance_name));
	assert(IsDefined(args.throttle_input));
	assert(IsDefined(args.vehicle));
	assert(Isdefined(args.start_alias_data));
	assert(IsDefined(args.stop_alias_data));
	assert(IsDefined(args.on_threshold));
	assert(IsDefined(args.off_threshold));
	assert(IsDefined(args.type) && args.type == "start_stop");
	instance_name = args.instance_name;
	
	level endon("aud_veh_stop");
	level endon("aud_veh_stop_" + instance_name);
	level._audio.veh.instances[instance_name]["entity"] endon( "death" );
	
	current_value = 0;
	previous_value = 0;
		
	prev_val = -1;
	vehicle_state = "off"; // can be "on" or "off";
	
	smoothness = args.smoothness;
	smooth_up = args.smooth_up;
	smooth_down = args.smooth_down;
	min = args.min;
	max = args.max;
		
	unsmoothed_value = 0;
	
	VMx_init_oneshot_ents(instance_name);
	prev_time = GetTime();
	
	while(true)
	{
		value = [[ args.callback ]](args);
		
		// normalize it to 0 to 1 using the min/max parameters
		assert(args.max != args.min);
		value = (value - args.min) / ( args.max - args.min);
		value = clamp(value, 0.0, 1.0);
		
		unsmoothed_value = value;
		
		if (IsDefined(smooth_up) && value > current_value)
		{
			current_value = current_value + smooth_up * (value - current_value);
		}
		else if (IsDefined(smooth_down) && value <= current_value)
		{
			current_value = current_value + smooth_down * (value - current_value);
		}
		else // just do the regular smoothing
		{
			current_value = current_value + smoothness * (value - current_value);
		}

		// acceleration (or delta)
		delta = current_value - previous_value;
		previous_value = current_value;
		
		current_time = GetTime();
		delta_time = current_time - prev_time; // this is used to prevent crazy input
		do_start_pitch = false;  // only do one-shot pitch at the very start of the trigger
		do_stop_pitch = false;
		
		if ( ( delta >= args.on_threshold || unsmoothed_value >= 0.99 ) && vehicle_state == "off" && delta_time > 200 )
		{
			prev_time = current_time;
			vehicle_state = "on";
			do_start_pitch = true;
			//iprintlnbold("VEHICLE ON!!");
			wait(0.05);
			// if restarting, just turn the volume back up (to avoid "restart" sound)
			ent = level._audio.veh.instances[instance_name]["entity"];
			thread VMx_play_start_sound(args.start_alias_data.name, ent, args.instance_name, args.offset);
			if (IsDefined(level._audio.veh.stop_ents[args.instance_name]))
			{
				stopent_array = level._audio.veh.stop_ents[args.instance_name];
				foreach ( ent in stopent_array )
				{
					thread VMx_stop_stop_ent(ent, undefined, args.instance_name);
				}
			}
		}
		else if ( ( delta <= args.off_threshold || unsmoothed_value <= 0.01 ) && vehicle_state == "on" && delta_time > 200 )
		{
			prev_time = current_time;
			vehicle_state = "off";
			do_stop_pitch = true;
			//iprintlnbold("VEHICLE OFF!!");
			wait(0.05);
			ent = level._audio.veh.instances[instance_name]["entity"];
			thread VMx_play_stop_sound(args.stop_alias_data.name, ent, args.instance_name, args.offset);
			
			if (IsDefined(level._audio.veh.start_ents[args.instance_name]))
			{
				startents = level._audio.veh.start_ents[args.instance_name];
				foreach ( ent in startents )
				{
					thread VMx_stop_start_ent(ent, undefined, args.instance_name);
				}
			}
		}

		// do parameter mapping of the one-shot sounds
		pitch_value = undefined;
		volume_value = undefined;
		if (VMx_get_start_sound_playing(args.instance_name))
		{
			if (do_start_pitch)
			{
				do_start_pitch = false;
				// map pitch
				if (IsDefined(args.start_alias_data.pitch_map_name))
				{
					pitch_value = aud_map(current_value, level._audio.veh.maps[args.start_alias_data.pitch_map_name]);
					// pitch_value is 0 to 1, map to min and max
					pitch_value = level._audio.veh.minpitch + pitch_value * (level._audio.veh.maxpitch - level._audio.veh.minpitch);
					VMx_scale_start_sound_pitch(pitch_value, args.updaterate, args.instance_name);
				}
			}
			// map volume
			if (IsDefined(args.start_alias_data.vol_map_name))
			{
				volume_value = aud_map(current_value, level._audio.veh.maps[args.start_alias_data.vol_map_name]);
				VMx_scale_start_sound_volume(volume_value, args.updaterate, args.instance_name);
			}
		}
		
		if (VMx_get_stop_sound_playing(args.instance_name))
		{
			// map pitch
			if (do_stop_pitch)
			{
				do_stop_pitch = false;
				if (IsDefined(args.stop_alias_data.pitch_map_name))
				{
					pitch_value = aud_map(current_value, level._audio.veh.maps[args.stop_alias_data.pitch_map_name]);
					// pitch_value is 0 to 1, map to min and max
					pitch_value = level._audio.veh.minpitch + pitch_value * (level._audio.veh.maxpitch - level._audio.veh.minpitch);
					//iprintlnbold("PITCH OFF: " + pitch_value);
					VMx_scale_stop_sound_pitch(pitch_value, args.updaterate, args.instance_name);
				}
			}
			// map volume
			if (IsDefined(args.stop_alias_data.vol_map_name))
			{
				volume_value = aud_map(current_value, level._audio.veh.maps[args.stop_alias_data.vol_map_name]);
				VMx_scale_stop_sound_volume(volume_value, args.updaterate, args.instance_name);
			}
		}
		
		prev_val = current_value;
		wait(args.updaterate);
	}
	
}

// call on a vehicle entity that the current vehicle system is working on
VM_DisableThrottleUpdate(throttle_override_)
{	
	self.aud_engine_disable = true;
	if (IsDefined(throttle_override_)) // defaults to 0 below
	{
		self.aud_engine_throttle_amount = throttle_override_;
	}
}

// enable the throttle updates again
VM_EnableThrottleUpdate()
{
	self.aud_engine_disable = undefined;
}


VMx_callback(args)
{
	assert(IsDefined(args));
	assert(IsDefined(args.callback));
	assert(IsDefined(args.updaterate));
	assert(IsDefined(args.instance_name));
	assert(IsDefined(args.alias_data));
	assert(IsDefined(args.type));
	assert(IsDefined(args.fadein));
	instance_name = args.instance_name;
	
	// will stop everything
	level endon("aud_veh_stop"); 
	// support stopping specific instances of presets
	level endon("aud_veh_stop_" + instance_name);
	
	current_value = undefined;
	
	// original values of settings which can be overridden in runtime
	smoothness = args.smoothness;
	smooth_up = args.smooth_up;
	smooth_down = args.smooth_down;
	min = args.min;
	max = args.max;
	
	if (IsDefined(args.heightmax))
	{
		ent = level._audio.veh.instances[instance_name]["entity"];
		args.init_height = ent.origin[2]; // get z value of vehicle at start of callback
	}

	starting = true;

	while(true)
	{
		// grab override parameters if the override parameters are defined
		// else set them to the original values passed in by the preset
			args.smoothness = smoothness;
			args.smooth_up = smooth_up;
			args.smooth_down = smooth_down;
			ent = level._audio.veh.instances[instance_name]["entity"];
			
			if (IsDefined(ent.aud_overrides) 
					&& IsDefined(ent.aud_overrides[args.type])
					&& IsDefined(ent.aud_overrides[args.type].min_range))
			{
				assert(IsDefined(ent.aud_overrides[args.type].max_range));
				args.min = ent.aud_overrides[args.type].min_range;
				args.max =ent.aud_overrides[args.type].max_range;
			}
			else
			{
				args.min = min;
				args.max = max;
			}
		
		// somebody deleted the entity without telling us... so we need to stop updating
		if (!IsDefined(ent))
		{
			VM_stop(args.instance_name);
			return;
		}
		
		engine_disable = false;
		throttle_amount = 0;
		// allow turning off engine while vehicle system is going
		if (IsDefined(ent.aud_engine_disable)) // check on the vehicle entity
		{
			engine_disable = ent.aud_engine_disable;
			if (IsDefined(ent.aud_engine_throttle_amount))
			{
				throttle_amount = ent.aud_engine_throttle_amount;
			}
		}
		
		// get new raw value of the parameter
		value = [[ args.callback ]](args);
		
		if (IsDefined(args.multiply_by_throttle))
		{
			if (engine_disable) // overriding the throttle value 
			{
				throttle = throttle_amount;
			}
			else
			{
				throttle = VMx_get_throttle(args);
			}
			if (level._audio.veh.print_throttle)
			{
				iprintln("throttle: " + throttle);
			}
			value *= throttle;
		}
		
		// normalize it to 0 to 1 using the min/max parameters
		assert(args.max != args.min);
		value = (value - args.min) / ( args.max - args.min);
		value = clamp(value, 0.0, 1.0);
		
		// smooth it out
		if (IsDefined(current_value))
		{
			// optionally, different smooth values for going up/down
			if (IsDefined(args.smooth_up) && value > current_value)
			{
				current_value = current_value + args.smooth_up * (value - current_value);
			}
			else if (IsDefined(args.smooth_down) && value <= current_value)
			{
				current_value = current_value + args.smooth_down * (value - current_value);
			}
			else // just do the regular smoothing
			{
				current_value = current_value + args.smoothness * (value - current_value);
			}
		}
		else
		{
			current_value = value;
		}
		
		if (IsDefined(args.custom_callback))
		{
			[[ args.custom_callback ]](ent, current_value);
		}
		// update the sounds
		foreach(alias_info in args.alias_data)
		{
			thread VMx_update_sound(alias_info, args, current_value, instance_name, starting);
		}

		if (starting)
		{
			starting = false;
			wait(args.fadein);
		}
		else
		{
			wait(args.updaterate);
		}
	}
}

VMx_update_sound(alias_info, args, current_value, instance_name, starting)
{
	pitch_value = undefined;
	volume_value = undefined;
	if (IsDefined(alias_info.pitch_map_name))
	{
		pitch_value = aud_map(current_value, level._audio.veh.maps[alias_info.pitch_map_name]);
		// pitch_value is 0 to 1, map to min and max
		pitch_value = level._audio.veh.minpitch + pitch_value * (level._audio.veh.maxpitch - level._audio.veh.minpitch);
	}
	if (IsDefined(alias_info.vol_map_name))
	{
		volume_value = aud_map(current_value, level._audio.veh.maps[alias_info.vol_map_name]);
	}
	
	do_duck = false;
	first_time = false;
	// check to see if already ducked
	if (IsDefined(level._audio.veh.ducked_instances[instance_name]))
	{
		previous_time = level._audio.veh.ducked_instances[instance_name]; // the last time, clears when oneshot is done
		current_time = GetTime();
		duck_time = 2.5;
		if (IsDefined(args.duck_time))
		{
			duck_time = args.duck_time;
		}
		if ((current_time - previous_time) < duck_time*1000)
		{
			do_duck = true;
		}
	}
	
	if (!do_duck)
	{
		// check to see if time to do ducking
		if (!IsDefined(level._audio.veh.ducked_instances[instance_name]) && VMx_get_need_to_duck(instance_name))
		{
			do_duck = true;  // start ducking
			level._audio.veh.ducked_instances[instance_name] = GetTime();
		}
	}
	
	// apply ducking
	if (do_duck)
	{
		duck_amount = 0.7;
		if (IsDefined(args.duck_amount))
		{
			duck_amount = args.duck_amount;
		}

		volume_value *= duck_amount;
	}
	
	if (IsDefined(args.heightmax))
	{
		height = args.vehicle.origin[2]; // current z value;
		assert(IsDefined(args.init_height));
		delta_height = height - args.init_height;
		if (delta_height > args.heightmax)
		{
			volume_value = 0;
		}
	}
	
	// if the handle to a sound of this name hasn't been made yet, we need to make it and store the data, and play the sound
	if (!IsDefined(level._audio.veh.instances[instance_name][alias_info.alias_name]))
	{
		assert(IsDefined(args.vehicle.origin));
		level._audio.veh.instances[instance_name][alias_info.alias_name] = spawn("script_origin", args.vehicle.origin);
		offset = 0;
		if (IsDefined(args.offset))
		{
			offset = args.offset;
		}
		level._audio.veh.instances[instance_name][alias_info.alias_name] linkto(args.vehicle, "tag_origin", (offset, 0, 0),(0,0,0) ); // link the sound entity to the vehicle
		level._audio.veh.instances[instance_name][alias_info.alias_name] playloopsound(alias_info.alias_name);
		level._audio.veh.instances[instance_name][alias_info.alias_name] scalevolume(0.0);
		wait(0.05);
		level._audio.veh.instances[instance_name][alias_info.alias_name] scalevolume(volume_value, args.fadein);
	}
	else
	{
		assert(IsDefined(level._audio.veh.instances[instance_name][alias_info.alias_name]));
		if(IsDefined(pitch_value))
		{
			level._audio.veh.instances[instance_name][alias_info.alias_name] setpitch(pitch_value, args.updaterate);
		}
		if (IsDefined(volume_value))
		{
			level._audio.veh.instances[instance_name][alias_info.alias_name] scalevolume(volume_value, args.updaterate);
		}
	}
}

VM_linkto_new_entity(instance_name, new_ent, tagname_, offset_)
{
	tagname = "tag_origin";
	
	if (isdefined(tagname_))
	{
		tagname = "tag_origin";
	}
	
	offset = 0;
	if (IsDefined(offset_))
	{
		offset = offset_;
	}
	
	if(IsDefined(level._audio.veh.instances[instance_name]))
	{
		foreach(key, sound_ent in level._audio.veh.instances[instance_name])
		{
			if (key != "entity" && key != "speed" && key != "throttle")
			{
				sound_ent unlink();
				sound_ent linkto(new_ent, tagname, (offset, 0, 0), (0, 0, 0));
			}
		}
		
		level._audio.veh.instances[instance_name]["entity"] = new_ent;
	}
}

VM_set_speed_callback(instance_name, new_speed_callback)
{
	if(IsDefined(level._audio.veh.instances[instance_name]))
	{
		level._audio.veh.instances[instance_name]["speed"] = new_speed_callback;
	}
}

VM_set_throttle_callback(instance_name, new_throttle_callback)
{
	if(IsDefined(level._audio.veh.instances[instance_name]))
	{
		level._audio.veh.instances[instance_name]["throttle"] = new_throttle_callback;
	}
}

VM_set_start_stop_callback(instance_name, new_start_stop_callback)
{
	if(IsDefined(level._audio.veh.instances[instance_name]))
	{
	}
}

VMx_get_tilt(args)
{
	ent = level._audio.veh.instances[args.instance_name]["entity"];
	assert(IsDefined(ent));
	val = ent.angles[0];
	if (level._audio.veh.print_tilt)
	{
		iprintln("tilt: " + val);
	}
	return val;
}

VMx_get_speed(args)
{
	ent = level._audio.veh.instances[args.instance_name]["entity"];
	assert(IsDefined(ent));
	
	speed = 0;
	
	// optionally override the callbacks
	if (IsDefined(level._audio.veh.instances[args.instance_name]["speed"]))
	{
		callback = level._audio.veh.instances[args.instance_name]["speed"];
		speed = ent [[ callback ]](); 
	}
	else
	{
		assert(IsDefined(args.vehicle));
		speed = args.vehicle Vehicle_GetSpeed();
	}
	
	if (level._audio.veh.print_speed)
	{
		iprintln("speed: " + speed);
	}
	
	return speed;
}

VMx_get_yaw(args)
{
	ent = level._audio.veh.instances[args.instance_name]["entity"];
	assert(IsDefined(ent));

	val = ent.angles[1];
	if (level._audio.veh.print_speed)
	{
		iprintln("yaw: " + val);
	}	
	return val;
}

VMx_get_roll(args)
{
	ent = level._audio.veh.instances[args.instance_name]["entity"];
	assert(IsDefined(ent));

	val = ent.angles[2];

	if (level._audio.veh.print_roll)
	{
			iprintln("roll: " + val);
	}
	return val;
}

VMx_get_altitude(args)
{
	ent = level._audio.veh.instances[args.instance_name]["entity"];
	assert(IsDefined(ent));

	// NEED TO FIGURE OUT A GOOD WAY TO CALCULATE THIS
	return 1.0;
}

VMx_get_throttle(args)
{
	ent = level._audio.veh.instances[args.instance_name]["entity"];
	assert(IsDefined(ent));
	
	val = 0;
	
	if (IsDefined(level._audio.veh.instances[args.instance_name]["throttle"]))
	{
		callback = level._audio.veh.instances[args.instance_name]["speed"];
		val = ent [[ callback ]]();
	}
	else if (IsDefined(args.throttle_input) && args.throttle_input == "leftstick")
	{
		input = level.player GetNormalizedMovement();
		xval = input[0];
		val = 0;
		if (xval >= 0)
		{
			val = xval;
		}
	}
	else if (IsDefined(args.throttle_input) && args.throttle_input == "leftstick_abs")
	{
		input = level.player GetNormalizedMovement();
		// get circular magnitude of x,y value
		xval = abs(input[0]);
		yval = abs(input[1]);		
		val = 2*sqrt(xval*xval + yval*yval);
		val = clamp(val, 0, 1);	
	}
	else if (IsDefined(args.throttle_input) && args.throttle_input == "attack")
	{
		if (level.player attackbuttonpressed())
		{
			val = 1.0;
		}
		else
		{
			val = 0.0;
		}
	}
	else
	{
		val = ent vehicle_getthrottle();
	}
	
	return val;
}


/#
VMx_validate_map(mapname)
{
	map = [];
	map = AUDIO_PRESETS_VEHICLE_MAPS(mapname, map);
	assertEx(map.size > 0, "Vehicle audio map preset \"" + mapname + "\ not found.");
	foreach ( key, value in map )
	{
		assertEx(IsDefined(value.size) && value.size == 2, "Vehicle audio map preset \"" + mapname + "\ has an improper format.");
		assertEx(value[0] >= 0.0 && value[1] <= 1.0, "Vehicle audio map preset \"" + mapname + "\ has map values outside of the proper range.");
	}
}
#/

/#
VMx_validate_preset(preset, preset_name)
{
	assertEx(preset.size > 0, "Vehicle audio preset \"" + preset_name + "\" not found.");
	foreach ( key, value in preset)
	{
		if ( key != "name" )
		{
			if ( key == "tilt" || key == "yaw" || key == "roll" || key == "speed" || key == "altitude" || key == "start_stop" )
			{
				foreach (k, setting in value)
				{
					assertEx(setting.size > 0, "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + "\" has no settings.");
					assertEx(IsString(setting[0][0]), "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is improperly formated.");
		
					if (setting[0] == "callback")
					{
						assertEx(setting.size == 2 && IsString(setting[1]), "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is trying to set a custom callback improperly.");
						assertEx(IsDefined(level._audio.veh.callbacks[setting[1]]), "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + "\" is trying to set a custom callback but that callback hasn't been registered.");
					}
					else if (setting[0] == "updaterate")
					{
						assertEx(setting.size == 2 && setting[1] > 0, "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is trying to set an update improperly.");
					}
					else if (setting[0] == "smoothness")
					{
						assertEx(setting.size == 2 && setting[1] > 0 && setting[1] <= 1, "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is trying to set a \"smoothness\" improperly.");
					}
					else if (setting[0] == "smooth_up")
					{
						assertEx(setting.size == 2 && setting[1] > 0 && setting[1] <= 1, "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is trying to set a \"smooth_up\" improperly.");
					}
					else if (setting[0] == "smooth_down")
					{
						assertEx(setting.size == 2 && setting[1] > 0 && setting[1] <= 1, "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is trying to set a \"smooth_down\" improperly.");
					}
					else if (setting[0] == "range")
					{
						assertEx(setting.size == 3, "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is improperly setup.");
						assertEx(setting[1] != setting[2], "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " can't have equal min/max values.");
					}
					else if (setting[0] == "multiply_by_throttle")
					{
						// nothing
					}	
					else if (setting[0] == "multiply_by_leftstick")
					{
						// nothing
					}	
					else if (setting[0] == "throttle_input")
					{
						// nothing
					}	
					else if (setting[0] == "on_threshold" || setting[0] == "off_threshold")
					{
						// nothing
					}
					else if (setting[0] == "start" || setting[0] == "stop")
					{
						// nothing
					}
					else if (setting[0] == "heightmax")
					{
						// nothing
					}
					else if (setting[0] == "oneshot_duck")
					{
						// nothing
					}
					else if (setting[0] == "oneshot_duck_time")
					{
						// nothing
					}
					else if (setting[0] == "offset")
					{
					}
					else // setting[0] is thus, an alias name
					{
						assertEx(setting.size >= 2, "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is trying to set an alias definition improperly.");
						foreach(key2, value2 in setting)
						{
							// is another array specifying either pitch or volume behavior
							if (!IsString(value2))
							{
								assertEx(value2.size > 1, "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is trying to set an alias definition improperly.");
								if (IsDefined(value2[0]))
								{
									assertEx(value2[0] == "pitch" || value2[0] == "volume", "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is trying to set an alias definition without specify either \"pitch\" or \"volume\" mapping behavior.");
									assertEx(IsString(value2[1]), "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is trying to set an alias definition improperly for parameter \"" + value2[0] + "\".");
									VMx_validate_map(value2[1]); // validate the map function
								}
							}
							else // it's the alias definition
							{
								assertEx(IsString(value2), "Vehicle audio preset \"" + preset_name + "\" for parameter \"" + key + " is trying to set an alias definition improperly.");
							}
						}			
					}
				}		
			}
			else
			{
				assertEx(false, "Vehicle audio preset " + key + " not recognized. Should be: \"tilt\", \"yaw\", \"roll\", \"speed\", or \"altitude\".");
			}
			
		
		}
	}
}
#/

/////////////////////////////////////////////////////////////////////
// GROUND VEHICLES
///////////////////////////////////////////////////////////////////////

VM_ground_vehicle_start(move_lo_lp_ , rolling_lp_, idle_lp_, engine_rev_lo_os_, breaks_os_, destruct_alias)
{
	self endon("death");
	
	self.veh_aliases = spawnstruct();
	
	// loops:
	self.veh_aliases.move_lo_lp = move_lo_lp_;
	self.veh_aliases.rolling_lp = rolling_lp_;
	self.veh_aliases.idle_lp = idle_lp_;
	
	// oneshots:
	self.veh_aliases.engine_rev_lo_os = engine_rev_lo_os_;
	self.veh_aliases.breaks_os = breaks_os_;

	self thread VMx_monitor_explosion(destruct_alias);
	self thread VMx_ground_vehicle_monitor_death();
	self thread VMx_cleanup_ents();
	
	self VMx_vehicle_engine();
}

VMx_vehicle_engine()
{	
	assert(isDefined(self.veh_aliases));
	
	self endon("death");
	
	self.do_rev = true;
	self.ents_mixed_in = false;
	self.has_idle_played = false;
	self.has_move_played = false;
	self.has_roll_played = false;
	
	self.veh_mix_ents = spawnstruct();

	self.veh_mix_ents.idle_ent = Spawn( "script_origin", self.origin);
	self.veh_mix_ents.idle_ent linkto(self);
		
	self.veh_mix_ents.move_ent = Spawn( "script_origin", self.origin); 
	self.veh_mix_ents.move_ent linkto(self);
	
	self.veh_mix_ents.roll_ent = Spawn( "script_origin", self.origin); 
	self.veh_mix_ents.roll_ent linkto(self);
	
	self.veh_mix_ents.one_shot = Spawn( "script_origin", self.origin);
	self.veh_mix_ents.one_shot linkto(self);
		
	// while the vehicle is stopped, monitor the speed, to see if it starts moving
	while(1)
	{
		vehicle_speed = self Vehicle_GetSpeed();
		
		// if it starts moving, monitor the movement
		if(vehicle_speed > 0.05)
		{
			self.do_rev = true;
			self VMx_ground_speed_watch(vehicle_speed);
		}
		// at this point, the vehicle has stopped, so we go back to watching the speed
		wait(0.25);
	}
}

VMx_ground_speed_watch(vehicle_speed)
{
	self endon("death");

	in_time = 0.5;
	out_time = 1.5;
	
	faded_in = false;
	
	while(1)
	{
		old_speed = vehicle_speed;
		wait(0.1);
		new_speed = 0.5 + self Vehicle_GetSpeed();
		
		// Vehicle has Started moving. Stop idle sounds, start up moving sounds.
		if(new_speed >= old_speed) 
		{
			// fade out the idle loop
			if (isDefined(self.veh_aliases.idle_lp) && self.has_idle_played)
			{
				self.veh_mix_ents.idle_ent thread VMx_aud_ent_fade_out(0.5);
			}
			
			// if first time, play the rev sound
			if (self.do_rev)
			{
				self.do_rev = false;
				// play the rev sound
				if (isDefined(self.veh_aliases.engine_rev_lo_os))
				{
					self.veh_mix_ents.one_shot playsound(self.veh_aliases.engine_rev_lo_os);
				}
			}
			else
			{
				// start roll ent
				if (isDefined(self.veh_aliases.rolling_lp) && !self.has_roll_played)
				{
					self.has_roll_played = true;
					self.veh_mix_ents.roll_ent playloopsound(self.veh_aliases.rolling_lp);
				}
				
				if (isDefined(self.veh_aliases.move_lo_lp) && !self.has_move_played)
				{
					self.has_move_played = true;
					self.veh_mix_ents.move_ent playloopsound(self.veh_aliases.move_lo_lp);
				}
				
				if(!faded_in)
				{
					
					if (isDefined(self.veh_aliases.move_lo_lp))
					{
						self.veh_mix_ents.move_ent thread VMx_aud_ent_fade_in(in_time);
					}
					
					if (isDefined(self.veh_aliases.rolling_lp))
					{
						self.veh_mix_ents.roll_ent thread VMx_aud_ent_fade_in(in_time);
					}
					
					faded_in = true;
				}
			}
		}
		else if (new_speed < old_speed) //Vehicle has stopped. Play airbreaks sounds, stop movement loops, start idle loop.
		{
			// if we have no played the idle sound, start it up
			if (IsDefined(self.veh_aliases.idle_lp))
			{
				if (!self.has_idle_played)
				{
					self.has_idle_played = true;
					self.veh_mix_ents.idle_ent playloopsound(self.veh_aliases.idle_lp);
				}
				
				// do the fade in
				self.veh_mix_ents.idle_ent thread VMx_aud_ent_fade_in(0.5);
			}
			
			// play the break one shot
			if (isDefined(self.veh_aliases.breaks_os))
			{
				self.veh_mix_ents.one_shot playsound(self.veh_aliases.breaks_os);
			}
			
			// fade out move ent
			if (isDefined(self.veh_aliases.move_lo_lp))
			{
				self.veh_mix_ents.move_ent thread VMx_aud_ent_fade_out(0.5);
			}
			
			// fade 
			if (isDefined(self.veh_aliases.move_lo_lp))
			{
				self.veh_mix_ents.roll_ent thread VMx_aud_ent_fade_out(0.1);
			}
			
			return;
		}
		wait(0.2);
	}
}

VMx_aud_ent_fade_out(fadetime)
{
	assert(fadetime >= 0);
	self ScaleVolume(0.0, fadetime);
}

VMx_aud_ent_fade_in(fadetime, vol_)
{
	vol = 1.0;
	if (IsDefined(vol_))
		vol = vol_;
		
	assert(fadetime >= 0);
	self ScaleVolume(0.0);
	wait(0.05);
	self ScaleVolume(vol, fadetime);
}

VMx_cleanup_ents()
{
	self waittill("cleanup_sound_ents");
	
	self.veh_mix_ents.idle_ent stoploopsound();
	self.veh_mix_ents.move_ent stoploopsound();
	self.veh_mix_ents.roll_ent stoploopsound();
	self.veh_mix_ents.one_shot stopsounds();
	wait(0.05);
	self.veh_mix_ents.idle_ent delete();
	self.veh_mix_ents.move_ent delete();
	self.veh_mix_ents.roll_ent delete();
	self.veh_mix_ents.one_shot delete();
}

VMx_ground_vehicle_monitor_death()
{
	self endon("cleanup_sound_ents");
	
	self waittill("death");
	self notify("cleanup_sound_ents");
}

VMx_monitor_explosion(destruct_alias)
{
	self endon("cleanup_sound_ents");
	
	while(true)
	{
		if (!isDefined(self))
			break;
			
		if (self.health < self.healthbuffer)
		{
			break;
		}
		wait(0.05);
	}
	
	self notify("died");

	if (IsDefined(destruct_alias))	
	{
		play_sound_in_space(destruct_alias, self.origin);
	}
	self notify("ceanup_sound_ents");
}

/////////////////////////////////////////////////////////////////////
// AIR VEHICLE FLYBYS
///////////////////////////////////////////////////////////////////////

VM_aud_air_vehicle_flyby(entity, alias_name, distance_threshold, print_distance_, dist3d_, destruct_alias_)
{
	assert(IsDefined(entity));
	assert(IsDefined(alias_name));
	assert(IsDefined(distance_threshold));
	
	debug_print = false;
	if (IsDefined(print_distance_))
		{
			debug_print = print_distance_;
		}

	distance3D = false;
	if (IsDefined(dist3d_))
		{
			distance3D = dist3d_;
		}

	while(isdefined(entity))
	{
			if (distance3D)
			{
				dist = Distance( entity.origin, level.player.origin ); //Test to see if vehicle is within range of player
			}
			else
			{
				dist = Distance2D( entity.origin, level.player.origin ); //Test to see if vehicle is within range of player				
			}

			if (debug_print)
			{
				iprintln("Distance: " + dist);
			}
							
			if ( dist < distance_threshold )  //If vehicle is within range of player, play the flyby sound
			{
				flyby_ent = spawn("script_origin", entity.origin);
				flyby_ent linkto( entity );
				flyby_ent playsound(alias_name, "sounddone");
				entity notify("flyby_sound_played");
				flyby_ent thread VMx_waittill_deathspin(entity);
				flyby_ent thread VMx_waittill_sounddone();
				flyby_ent waittill("flyby_ent", whathappened);

				if (whathappened == "deathspin")  //If vehicle is shot down then play explosion sound ad stop the flyby sound 
				{
					if (IsDefined(destruct_alias_))
					{
						thread play_sound_in_space(destruct_alias_, flyby_ent.origin);
					}


					flyby_ent scalevolume(0.0, 0.3);
					wait(0.4);
					flyby_ent stopsounds();
					wait(0.05);
					flyby_ent delete();
					return;
				}
				else if (whathappened == "sounddone") //Cleanup if flyby sound completes without vehicle being shot down
				{
					wait(0.1);
					flyby_ent delete();
					return;
				}
			}
			
			else
			{
				wait(0.05);
			}
	}
}

VMx_waittill_deathspin(entity)
{
	self endon("flyby_ent");
	entity waittill("deathspin");
	self notify("flyby_ent", "deathspin");
}

VMx_waittill_sounddone()
{
	self endon("flyby_ent");
	self waittill("sounddone");
	self notify("flyby_ent", "sounddone");
}
