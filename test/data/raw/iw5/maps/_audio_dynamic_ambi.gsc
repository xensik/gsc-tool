#include maps\_utility_code;
#include maps\_utility;
#include common_scripts\utility;
#include maps\_audio;

// --------------------------------------------
// DYNAMIC AMBIENCE MANAGER
// --------------------------------------------
// OVERVIEW
// 	The dynamic ambience manager manages playing ram-based 
// 	3D positional audio at various randomized event rates.
//  This system is intended to be run in paralell with the
// 	streamed ambience manager.
// --------------------------------------------


/***************************************
PUBLIC FUNCTIONS
****************************************/

DAMB_init()
{
	if (!IsDefined(level._audio))
	{
		level._audio = SpawnStruct();
	}
	
	if (!IsDefined(level._audio.damb))
	{
		level._audio.damb = SpawnStruct();
		level._audio.damb.loop_handle_index = 0; 		// unique indices to keep track of where sound entity handles are stored for cleanup
		level._audio.damb.single_loop_handle_index = 0;
		level._audio.damb.oneshot_handle_index = 0;
		level._audio.damb.serial_playback_lock = true; // whether or not serial playback of dynamic ambiences require the previous event to stop before starting a new one
		level._audio.damb.playing = [];
		level._audio.damb.playing["zone"] = []; // two types of dynamic ambiences, zone = played from zone manager
		level._audio.damb.playing["free"] = []; // free = from outside of zone manager
		level._audio.damb.component_weights = [];
		level._audio.damb.callbacks = [];

		// cache arrays so we don't have to reload presets once their loaded
		level._audio.damb.preset_cache = [];
		level._audio.damb.component_cache = [];
		level._audio.damb.loop_cache = [];
		
		level._audio.damb.use_string_table_presets = false;
		level._audio.damb.use_iw_presets = false;
		level._audio.damb.entity_ref_count = 0;
		level._audio.damb.loop_entity_ref_count = 0;
		level._audio.damb.max_entities = 15;
	}
}

DAMB_set_max_entities(max_entities)
{
	assert(IsDefined(max_entities));
	level._audio.damb.max_entities = max_entities;
}

DAMB_use_string_table()
{
	level._audio.damb.use_string_table_presets = true;
	level._audio.damb.use_iw_presets = false;
}

DAMB_use_iw_presets()
{
	level._audio.damb.use_iw_presets = true;
	level._audio.damb.use_string_table_presets = false;
}

DAMB_zone_start_preset(name, prob_scale_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/

	DAMBx_start_preset("zone", name, undefined, prob_scale_);
}

// plays the indicated damb preset at the given prob_scale
DAMB_start_preset(name, label_, prob_scale_, linked_dambs_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/

	DAMBx_start_preset("free", name, label_, prob_scale_, undefined, undefined, linked_dambs_);
}

DAMB_start_preset_at_point(preset_name, point, label_, max_distance_, fadeoutmaxdistance_, linked_dambs_)  // DAMB_start_preset_at_point("example", (3, 401, 219));
{
	/#
	if (aud_check_fastfiles()) return;
	#/

	assert(IsDefined(point));
	
	// optionally monitor player distance so it can start/stop itself automatically based on max distance
	if (IsDefined(max_distance_)) 
		thread DAMBx_monitor_damb_point_distance(preset_name, point, label_, max_distance_, fadeoutmaxdistance_, linked_dambs_);
	else
		DAMBx_start_preset("free", preset_name, label_, undefined, point, linked_dambs_);
	
}

DAMB_stop_preset_at_point(name, label_, fade_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	if (IsString(label_))
		preset_id = label_;
	else
		preset_id = name;

	level notify(preset_id + "dist_monitor_stop");	// Stop monitoring distance.
	DAMB_stop_preset(preset_id, fade_);				// Stop the damb preset.
}

DAMB_make_linked_damb(preset_name, point, label, min_delay, max_delay)
{
	assert(Isdefined(preset_name));
	assert(IsDefined(point));
	assert(IsDefined(label));
	assert(IsDefined(min_delay));
	assert(IsDefined(max_delay));
	
	linked_damb = spawnstruct();
	linked_damb.name = preset_name;
	linked_damb.point = point;
	linked_damb.label = label;
	linked_damb.min_delay = min_delay;
	linked_damb.max_delay = max_delay;
	
	return linked_damb;
}

DAMBx_monitor_damb_point_distance(name, point, label_, max_distance, fadeoutmaxdistance_, linked_dambs_)
{	
	assert(IsDefined(name));
	assert(IsDefined(point));
	assert(IsDefined(max_distance));
	
	if (IsString(label_))
		level endon(label_ + "dist_monitor_stop");
	else
		level endon(name + "dist_monitor_stop");

	fade = 1.0;
	if (IsDefined(fadeoutmaxdistance_))
	{
		fade = fadeoutmaxdistance_;
	}
	
	is_stopped = true;
	
	while(true)
	{
		dist = distance(level.player.origin, point);
		if (dist < max_distance)
		{
			if (is_stopped)
			{
				is_stopped = false;
				DAMBx_start_preset("free", name, label_, undefined, point, linked_dambs_);
			}
		}
		else
		{
			if (!is_stopped)
			{
				is_stopped = true;
				if (IsDefined(label_))
					DAMBx_stop_preset("free", label_, fade);
				else
					DAMBx_stop_preset("free", name, fade);
			}
		}
		
		wait(1);
	}
	
}

DAMB_start_preset_on_entity(name, entity, label_, mode_, prob_scale_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsDefined(entity));
	mode = "attach";
	if (IsDefined(mode_))
	{
		assert(mode_ == "attach" || mode_ == "free");
		mode = mode_;
	}
	assert(IsDefined(mode));
	DAMBx_start_preset("free", name, label_, prob_scale_, undefined, entity, mode);
}


// stops all playing dambs
// type_ can be "free", "zone", or "all". Defaults to "all".
DAMB_stop(fade_, type_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/

	fade = 2.0;
	if (IsDefined(fade_))
	{
		assertEx(fade_ >= 0.0, "DAMB_stop: \"fade_\" must be greater than zero.");
		fade = fade_;
	}
	
	type = "all";
	
	if (IsDefined(type_))
	{
		assert(type_ == "free" || type_ == "zone" || type_ == "all");
		type = type_;
	}
	
	if (type == "free" || type == "all")
	{
		foreach(name, value in level._audio.damb.playing["free"])
		{
			assert(IsString(name)); // there shouldn't be any numbered indices in the playing array
			DAMB_stop_preset(name, fade);
		}
	}
	
	if (type == "zone" || type == "all")
	{
		foreach(name, value in level._audio.damb.playing["zone"])
		{
			assert(IsString(name)); // there shouldn't be any numbered indices in the playing array
			DAMB_zone_stop_preset(name, fade);
		}
	}
}

DAMB_stop_zone(fade_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	DAMBx_stop_preset("zone", undefined, fade_); // stops both name and labeled dambs
}

DAMB_zone_stop_preset(name, fade_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	DAMBx_stop_preset("zone", name, fade_); // stops both name and labeled dambs
}

// stops a specific damb
DAMB_stop_preset(stored_name, fade_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	DAMBx_stop_preset("free", stored_name, fade_);
}

// probability mixes the two indiced damb presets
DAMB_prob_mix_damb_presets(name1, prob1, name2, prob2)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	if (IsDefined(name1) && name1 != "none")
	{
		assertEx(IsString(name1), "DAMB_mix_damb_presets: \"name1\" must be a string.");
		assertEx(IsDefined(prob1) && (prob1 >= 0.0 && prob1 <= 1.0), "DAMB_mix_damb_presets: \"prob1\" must be defined and between 0 and 1.");

		if (prob1 == 0)
		{
			DAMB_zone_stop_preset(name1, 2.0);
		}
		else
		{
			DAMB_zone_start_preset(name1, prob1);
		}
	}
	
	if (IsDefined(name2) && name2 != "none")
	{
		assertEx(IsString(name2), "DAMB_mix_damb_presets: \"name2\" must be a string.");
		assertEx(IsDefined(prob2) && (prob2 >= 0.0 && prob2 <= 1.0), "DAMB_mix_damb_presets: \"prob2\" must be defined and between 0 and 1.");
				
		if (prob2 == 0)
		{
			DAMB_zone_stop_preset(name2, 2.0);
		}
		else
		{
			DAMB_zone_start_preset(name2, prob2);
		}
	}
	
	/#
	// HUD CODE
	if (IsDefined(name1) && IsDefined(name2))
	{
		if (name1 == "none")
			name1 = "";
		if (name2 == "none")
			name2 = "";
			
		if (prob1 != 0 && prob2 == 0)
		{
			set_damb_to_hud("", "");
			set_damb_from_hud("", "");
			set_damb_hud(name1);
		}
		else if (prob1 == 0 && prob2 != 0)
		{
			set_damb_to_hud("", "");
			set_damb_from_hud("", "");
			set_damb_hud(name2);
		}
		else if (prob1 != 0 && prob2 != 0)
		{
			set_damb_to_hud(name2, prob2);
			set_damb_from_hud(name1, prob1);
			set_damb_hud("blending");
		}
	}
	else if (IsDefined(name1))
	{
		if (name1 == "none")
			name1 = "";
			
		set_damb_to_hud("", "");
		if (prob1 == 0)
		{
			set_damb_from_hud("", "");
			set_damb_hud("");
		}
		else if (prob1 == 1)
		{
			set_damb_from_hud("", "");
			set_damb_hud(name1);
		}
		else 
		{
			set_damb_from_hud(name1, prob1);
			set_damb_hud("progress");
		}
	}
	else if (IsDefined(name2))
	{
		if (name2 == "none")
			name2 = "";
			
		set_damb_from_hud("", "");
		if (prob2 == 1)
		{
			set_damb_to_hud("", "");
			set_damb_hud(name2);
		}
		else if (prob2 == 0)
		{
			set_damb_to_hud("", "");
			set_damb_hud("");
		}
		else 
		{
			set_damb_to_hud(name2, prob2);
			set_damb_hud("progress");
		}
	}
	#/

}

DAMB_set_oneshot_callback_for_component(component_name, callback_function)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	if (!IsDefined(	level._audio.damb.callback ))
	{
		level._audio.damb.callback = [];
	}
	
	level._audio.damb.callback[component_name] = callback_function;
}

DAMB_set_oneshot_callback_for_dynamic_ambience(ambience_name, callback_function)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	damb = [];

	if (IsDefined(level._audio.damb.preset_cache[ambience_name]))
		damb = level._audio.damb.preset_cache[ambience_name];
	else if (level._audio.damb.use_string_table_presets)
	{
		// if we've explicitely said to use string table presets, check BOTH level and common
		damb = DAMBx_get_preset_from_string_table(ambience_name, true);
		level._audio.damb.preset_cache[ambience_name] = damb;
	}
	else
	{
		// if we've not explicitly said to use string table presets, look in common...
		damb = DAMBx_get_preset_from_string_table(ambience_name, false);
		if (damb.size == 0) // if didn't find it with common, then look up the old SHG style presets
		{		
			damb = AUDIO_PRESETS_DYNAMIC_AMBIENCE(ambience_name, damb);
		}
		level._audio.damb.preset_cache[ambience_name] = damb;
	}
	
	foreach (component in damb["components"])
	{
		DAMB_set_oneshot_callback_for_component(component, callback_function);
	}
}

// pauses a damb from making new events
DAMB_pause_damb(label, type_)
{
	type = "free";
	if (IsDefined(type_))
		type = type_;
		
	if (IsDefined(level._audio.damb.playing[type][label]))
	{
		level._audio.damb.playing[type][label]["paused"] = true;
	}
}

// unpauses a playing damb
DAMB_unpause_damb(label, type_)
{
	type = "free";
	if (IsDefined(type_))
		type = type_;

	if (IsDefined(level._audio.damb.playing[type][label]))
	{
		level._audio.damb.playing[type][label]["paused"] = false;
		level notify(type + "_" + label + "_event"); 
	}
}

// manually triggers an event of a paused damb
DAMB_manual_trigger(label, type_)
{
	assert(IsDefined(label));
	type = "free";
	if (IsDefined(type_))
		type = type_;
		
	if (IsDefined(level._audio.damb.playing[type][label]))
	{
		level notify(type + "_" + label + "_event"); 
	}
}

// links a playing damb to another damb so that when the first damb has an event, the second damb will also have an event within the min/max delay time
DAMB_link_to_damb(label, linked_to_label, min_delay, max_delay)
{
	assert(IsDefined(label));
	assert(IsDefined(linked_to_label));
	assert(IsDefined(min_delay));
	assert(IsDefined(max_delay));
	
	type = "free"; // can only link free dambs
	
	// only if both dambs are playing
	if (IsDefined(level._audio.damb.playing[type][label]) && IsDefined(level._audio.damb.playing[type][linked_to_label]))
	{
		min_delay = min(min_delay, max_delay);
		max_delay = max(min_delay, max_delay);
		if (!IsDefined( level._audio.damb.playing[type][label]["linked_dambs"]))
			level._audio.damb.playing[type][label]["linked_dambs"] = [];
		
		num_currently_linked = level._audio.damb.playing[type][label]["linked_dambs"].size;
		level._audio.damb.playing[type][label]["linked_dambs"][num_currently_linked] = spawnstruct();
		level._audio.damb.playing[type][label]["linked_dambs"][num_currently_linked].name = linked_to_label;
		level._audio.damb.playing[type][label]["linked_dambs"][num_currently_linked].min_delay = max(min_delay, 0);
		level._audio.damb.playing[type][label]["linked_dambs"][num_currently_linked].max_delay = max(max_delay, 0);
	}
}

/***************************************
PRIVATE FUNCTIONS
****************************************/
DAMBx_start_preset(type, name, label_, prob_scale_, point_, entity_, mode_, linked_dambs_)
{
	assert(IsString(type));
	assertEx(IsString(name), "DAMB_play_damb_preset: \"name\" must be a string.");
	assert(IsString(type));
	assert(IsDefined(level._audio.damb.playing[type]));
	
	prob_scale = 1.0;
	if (IsDefined(prob_scale_))
	{
		assertEx(prob_scale_ >= 0.0 && prob_scale <= 1.0, "DAMB_play_damb_preset: prob_scale_ must be between 0.0 and 1.0.");
		prob_scale = prob_scale_;
	}
	
	stored_name = name;
	if (IsString(label_))
	{
		stored_name = label_;
	}
	
	if (!IsDefined(level._audio.damb.playing[type][stored_name])) // if it hasn't already been started
	{
		damb = DAMBx_get_damb_preset(name);
		if (!IsDefined(damb)) // error loading file
			return;

		level._audio.damb.playing[type][stored_name] = damb; // store the fact that this damb is currently playing
		level._audio.damb.playing[type][stored_name]["prob_scale"] = prob_scale;
		level._audio.damb.playing[type][stored_name]["paused"] = false;
		
		if (IsDefined(linked_dambs_))
		{
			DAMBx_start_linked_dambs(stored_name, linked_dambs_);
		}
		
		if (IsDefined(entity_)) // tell this damb that it is using an entity
		{
			level._audio.damb.playing[type][stored_name]["entity"] = entity_; 
			assert(IsDefined(mode_));
			level._audio.damb.playing[type][stored_name]["mode"] = mode_; // mode_ can be "free", "attach"
		}
		
		thread DAMBx_play(type, stored_name, point_); // spawn a thread which will use the stored copy of the damb to update itself
	}
	else if (level._audio.damb.playing[type][stored_name]["prob_scale"] != prob_scale) // the damb is already playing, but it might need to scale it's probability
	{
		level._audio.damb.playing[type][stored_name]["prob_scale"] = prob_scale;
	}
}

DAMBx_start_linked_dambs(parent_label, linked_dambs)
{
	if (IsArray(linked_dambs)) // an array of linked dambs given
	{
		foreach(linked_damb in linked_dambs)
		{
			assert(Isdefined(linked_damb.name));
			assert(IsDefined(linked_damb.point));
			assert(IsDefined(linked_damb.label));
			assert(IsDefined(linked_damb.min_delay));
			assert(IsDefined(linked_damb.max_delay));
			
			DAMBx_start_preset("free", linked_damb.name, linked_damb.label, undefined, linked_damb.point); // start linked damb
			DAMB_pause_damb(linked_damb.label); // pause it
			
			DAMB_link_to_damb(parent_label, linked_damb.label, linked_damb.min_delay, linked_damb.max_delay);
		}
	}
	else // only one linked damb given
	{
		assert(Isdefined(linked_dambs.name));
		assert(IsDefined(linked_dambs.point));
		assert(IsDefined(linked_dambs.label));
		assert(IsDefined(linked_dambs.min_delay));
		assert(IsDefined(linked_dambs.max_delay));
		
		DAMBx_start_preset("free", linked_dambs.name, linked_dambs.label, undefined, linked_dambs.point); // start linked damb
		DAMB_pause_damb(linked_dambs.label); // pause it
		
		DAMB_link_to_damb(parent_label, linked_dambs.label, linked_dambs.min_delay, linked_dambs.max_delay);
	}
}


DAMBx_stop_preset(type, stored_name, fade_)
{
	assert(IsString(type));
	
	/#
	if (type == "free")
		assertEx(IsString(stored_name), "DAMB_stop_damb_preset: \"stored_name\" must be a string.");
	#/
	
	fade = 2.0;
	if (IsDefined(fade_))
	{
		assertEx(fade_ >= 0.0, "DAMB_stop_damb_preset: \"fade_\" must be greater than zero.");
		fade = fade_;
	}

/#
// update the zone hud
	if (type == "zone")
	{
		set_damb_to_hud("", "");
		set_damb_from_hud("", "");
		set_damb_hud("");
	}
#/

	if (type == "zone" && !IsDefined(stored_name)) // stop all zone dambs in this case
	{
		if (IsDefined(level._audio.damb.playing[type]))
		{
			foreach(stored_name, value in level._audio.damb.playing[type])
			{
				level._audio.damb.playing[type][stored_name]["fade"] = fade;
				level notify(type + "_" + stored_name + "_stop");
			}
		}
	}	
	else if (IsDefined(level._audio.damb.playing[type][stored_name])) // stop this particular damb
	{
		level._audio.damb.playing[type][stored_name]["fade"] = fade;
		level notify(type + "_" + stored_name + "_stop");
	}
}

DAMBx_update_serially(type, stored_name, point_)
{
	assert(IsString(type));
	assert(IsString(stored_name));
	
	assert(IsDefined(level._audio.damb.playing[type][stored_name]["event_time"]));
	
	level endon(type + "_" + stored_name + "_stop");
		
	event_time_array = level._audio.damb.playing[type][stored_name]["event_time"];
	assert(IsArray(event_time_array) && event_time_array.size == 2);

	min_time = min(event_time_array[0], event_time_array[1]);
	max_time = max(event_time_array[0], event_time_array[1]);
	
	first_min_time = undefined;
	first_max_time = undefined;
	if (IsDefined(level._audio.damb.playing[type][stored_name]["first_event"]))
	{
		event_time_array = level._audio.damb.playing[type][stored_name]["first_event"];
		first_min_time = min(event_time_array[0], event_time_array[1]);
		first_max_time = max(event_time_array[0], event_time_array[1]);
	}
	
	wait_time = undefined;
	if (IsDefined(first_min_time))
	{
		assert(IsDefined(first_max_time));
		wait_time = RandomFloatRange(first_min_time, first_max_time);
	}
	else
	{
		wait_time = RandomFloatRange(min_time, max_time);
	}
	
	assert(IsDefined(wait_time));
	assert(IsDefined(min_time) && IsDefined(max_time));
	
	while(true)
	{
		if (level._audio.damb.playing[type][stored_name]["paused"])
		{
			// if paused, wait only for a manual event notify
			level waittill(type + "_" + stored_name + "_event");
		}
		
		if (!level._audio.damb.playing[type][stored_name]["paused"])
		{
			wait(wait_time);
		}
		// figure out which component to play
		chosen_component = DAMBx_pick_random_component(type, stored_name);		
		if (!IsDefined(chosen_component))
			continue; // ignore failed load and continue to next wait

		data = DAMBx_get_component_data(type, stored_name, chosen_component, stored_name);
		
		if (data.using_oneshots_or_loops)
		{
			// before doing anything, need to check if we are using an entity to play the 
			// damb on and it gets deleted. If so, then we need to stop the dynamic ambience!
			if (data.using_entity && !IsDefined(data.ent)) 
			{
				level notify(type + "_" + stored_name + "_stop");
				break; // leave while loop
			}
					
			event = DAMBx_create_damb_event(data, stored_name, chosen_component);
			assert(IsDefined(event));
			assert(IsDefined(event.success));
			if (event.success)
			{
				assert(IsDefined(level._audio.damb.serial_playback_lock)); // used to determine if we wait for sound event to be done before waiting again				
				if (level._audio.damb.serial_playback_lock)
				{
					DAMBx_perform_play_event(type, stored_name, event); // play synchronously if we're locked
				}
				else
				{		
					thread DAMBx_perform_play_event(type, stored_name, event); // play on separate thread if we're not locked (which means they can overlap)
				}
			}
		}
		else
		{
			aud_print_warning("Dynamic ambience is playing back serially and using components which do not define oneshots or loops");
		}
				
		wait_time = RandomFloatRange(min_time, max_time);
	}	
}

DAMBx_play_component_loops(type, stored_name, component, point_, entity_)
{
	assert(IsDefined(type));
	assert(IsDefined(stored_name));
	assert(IsDefined(component));
	
	if (IsDefined(component["single_loops"]))
	{
		foreach(loop_alias in component["single_loops"])
		{
			entity = undefined;
			if (IsDefined(entity_))
				entity = spawn("script_origin", entity_.origin);
			else if (IsDefined(point_))
				entity = spawn("script_origin", point_);
			else
				entity = spawn("script_origin", level.player.origin);
			
			level._audio.damb.loop_entity_ref_count++; // NOTE: "single_loops" aren't going to be entity-refcounted in the same pool
			
			assert(isdefined(entity));
			
			entity PlayLoopSound(loop_alias);
			if (IsDefined(entity_))
				entity LinkTo(entity_);
			
			single_loop_handle_index = level._audio.damb.single_loop_handle_index;
			level._audio.damb.playing[type][stored_name]["single_loops"][single_loop_handle_index] = entity;
			level._audio.damb.single_loop_handle_index++;
		}
	}
}

DAMBx_get_component_data(type, stored_name, component, stored_name)
{
	assert(IsDefined(type));
	assert(IsDefined(stored_name));
	assert(IsDefined(component));
	
	data = spawnstruct();
	
	data.using_oneshots_or_loops = false;
	
	if (!IsDefined(component["single_loops"]))
		data.single_loops = false;
	else
		data.single_loops = true;
	
	if (IsDefined(component["oneshots"]) || IsDefined(component["loops"]))
	{
		data.using_oneshots_or_loops = true;
		
		if (!IsDefined(component["radius"]))
			component["radius"] = [0.0, 0.01]; // basically on top of the position
		
		data.min_radius = min(component["radius"][0], component["radius"][1]);
		data.max_radius = max(component["radius"][0], component["radius"][1]); 
		
		if (IsArray(component["event_time"]))
		{
			assert(component["event_time"].size == 2);
			data.min_time = min(component["event_time"][0], component["event_time"][1]);
			data.max_time = max(component["event_time"][0], component["event_time"][1]);
		}
				
		if(IsArray(component["first_event"]))
		{
			assert(component["first_event"].size == 2);
			data.first_event = true;
			data.first_event_min = min(component["first_event"][0], component["first_event"][1]);
			data.first_event_max = max(component["first_event"][0], component["first_event"][1]);
		}
		
		if (IsArray(component["pitch"]))
		{
			assert(component["pitch"].size == 2);
			data.min_pitch = min(component["pitch"][0], component["pitch"][1]);
			data.max_pitch = max(component["pitch"][0], component["pitch"][1]);
		}
			
		if (IsArray(component["travel_time"]))
		{
			assert(component["travel_time"].size == 2);
			data.min_trav_time = min(component["travel_time"][0], component["travel_time"][1]);
			data.max_trav_time = max(component["travel_time"][0], component["travel_time"][1]);		
			if (IsArray(component["delta"]))
			{
				assert(component["delta"].size == 2);
				data.min_delta = min(component["delta"][0], component["delta"][1]);
				data.max_delta = max(component["delta"][0], component["delta"][1]);
			}
			else
			{
				assert(IsArray(component["delta_angle"]));
				assert(component["delta_angle"].size == 2);
				data.min_delta_angle = min(component["delta_angle"][0], component["delta_angle"][1]);
				data.max_delta_angle = max(component["delta_angle"][0], component["delta_angle"][1]);
			}
		}

	
		if (IsArray(component["pitch_time"]))
		{
			assert(component["pitch_time"].size == 2);
			data.min_pitch_time = min(component["pitch_time"][0], component["pitch_time"][1]);
			data.max_pitch_time = max(component["pitch_time"][0], component["pitch_time"][1]);				
		}		
		
		if (IsDefined(component["cone"]))
		{
			data.min_start_angle = min(component["cone"][0], component["cone"][1]);
			data.max_start_angle = max(component["cone"][0], component["cone"][1]);
		}
		
		assert(IsDefined(data.min_radius));
		assert(IsDefined(data.max_radius));
	}
	else
	{
		data.using_oneshots_or_loops = false;
	}
	assert(IsDefined(data.using_oneshots_or_loops));
	
	data.using_entity = false;
	if (IsDefined(level._audio.damb.playing[type][stored_name]["entity"]))
	{
		data.using_entity = true;
		data.ent = level._audio.damb.playing[type][stored_name]["entity"];
		assert(IsDefined(level._audio.damb.playing[type][stored_name]["mode"]));
		data.mode = level._audio.damb.playing[type][stored_name]["mode"];
	}
	
	assert(IsDefined(level._audio.damb.playing[type][stored_name]["prob_scale"]));
	data.prob_scale = level._audio.damb.playing[type][stored_name]["prob_scale"];
	
	assert(IsDefined(data.using_entity));
	assert(IsDefined(data.using_oneshots_or_loops));
	assert(IsDefined(data.single_loops));
	assert(IsDefined(data.prob_scale));
	return data;
}

DAMBx_monitor_single_loops_on_ent(type, stored_name, ent)
{
	assert(IsDefined(ent));
	while(true)
	{
		if (!IsDefined(ent))
		{
			level notify(type + "_" + stored_name + "_stop");
		}
		wait(1.0);
	}
}

DAMBx_create_damb_event(data, stored_name, component, point_)
{
	assert(IsDefined(data));
	assert(IsString(stored_name));
	
	event = SpawnStruct();
	
	if (RandomFloat(1.0) < data.prob_scale) // if prob_scale == 1.0, then this will always be true
	{
		event.success = true;
		
		// check to see if there is an associated one-shot callback function to call
		if (IsDefined(level._audio.damb.callbacks[stored_name]))
		{
			thread [[ level._audio.damb.callback[stored_name] ]]();
		}
		else
		{							
			// new event:
			event.alias = DAMBx_pick_random_alias(component);
			
			event.point = point_; // note: ok for "point_", "ent", "mode" to be undefined
			event.ent = data.ent;
			event.mode = data.mode;
			
			assert(IsString(event.alias["name"])); // name of the alias (or loop preset)
			assert(IsString(event.alias["type"])); // loop or oneshot
			
			// create start position
			r = RandomFloatRange(data.min_radius, data.max_radius);
			
			theta = undefined;
			if (IsDefined(data.min_start_angle))
			{
				assert(IsDefined(data.max_start_angle));
				theta = RandomFloatRange(data.min_start_angle, data.max_start_angle);
			}
			else
			{
				theta = RandomFloatRange(0, 360);
			}
			assert(IsDefined(theta));
			x = r * cos(theta);
			y = r * sin(theta);
			event.start_position = (x, y, 0);
		
			// create an optional end position
			if (IsDefined(data.min_trav_time))
			{
				assert(IsDefined(event.start_position));
				assert(IsDefined(data.max_trav_time));
				assert((IsDefined(data.min_delta) && IsDefined(data.max_delta)) || (IsDefined(data.min_delta_angle) && IsDefined(data.max_delta_angle)));
					
				event.travel_time = RandomFloatRange(data.min_trav_time, data.max_trav_time);
				
				if (IsDefined(data.min_delta))
				{
					r = RandomFloatRange(data.min_delta, data.max_delta);
					theta = RandomFloatRange(0, 360);
					x = r * cos(theta);
					y = r * sin(theta);
					// end position is an offset from the start position
					event.end_position = event.start_position + (x, y, 0);
				}
				else
				{
					angle = RandomFloatRange(data.min_delta_angle, data.max_delta_angle);
					angle *= 0.5; 
					
					sound_origin = level.player.origin; // can optionally pass in an arbitrary world point
					if (IsDefined(point_))
					{
						sound_origin = point_;
					}
					
					vec = event.start_position - sound_origin;
					// rotation calculation
					x = vec[0] * cos(angle) - vec[1] * sin(angle);
					y = vec[0] * sin(angle) + vec[1] * cos(angle);						
					event.end_position = event.start_position + (x, y, 0);
				}
			}
		
			if (IsDefined(data.min_pitch))
			{
				assert(IsDefined(data.max_pitch));
				event.start_pitch = RandomFloatRange(data.min_pitch, data.max_pitch);
			}
			
			if (IsDefined(data.min_pitch_time))
			{
				assert(IsDefined(data.min_pitch));
				assert(IsDefined(data.max_pitch));
				assert(IsDefined(data.max_pitch_time));
				
				event.end_pitch = RandomFloatRange(data.min_pitch, data.max_pitch);
				event.pitch_time = RandomFloatRange(data.min_pitch_time, data.max_pitch_time);
			}
		}
	}
	else
	{
		event.success = false;
	}
	return event;
}

DAMBx_trigger_linked_damb(linked_damb, delay_time)
{
	wait(delay_time);
	DAMB_manual_trigger(linked_damb);
}

DAMBx_make_first_wait(data)
{
	assert(IsDefined(data));
	
	wait_time = undefined;
	// compute the first wait_time
	if (IsDefined(data.first_event))
	{
		assert(IsDefined(data.first_event_min) && IsDefined(data.first_event_max));
		wait_time = RandomFloatRange(data.first_event_min, data.first_event_max);
	}
	else
	{
		assert(IsDefined(data.min_time) && IsDefined(data.max_time));
		wait_time   = RandomFloatRange(data.min_time, data.max_time);
	}	
	assert(IsDefined(wait_time));
	return wait_time;
}

DAMBx_update(type, stored_name, component, point_)
{
	assert(IsString(type));
	assert(IsString(stored_name));
	assert(IsDefined(component));
	
	level endon(type + "_" + stored_name + "_stop");
	
	assert(IsDefined(level._audio.damb.playing[type][stored_name]));
	
	data = DAMBx_get_component_data(type, stored_name, component, stored_name);
	
	if (data.single_loops)
	{
		DAMBx_play_component_loops(type, stored_name, component, point_, data.ent);
		
		// don't need to monitor the entity here if using oneshots or loops
		if (data.using_entity && !data.using_oneshots_or_loops) 
		{
			assert(IsDefined(data.ent));
			thread DAMBx_monitor_single_loops_on_ent(type, stored_name, data.ent);						
		}
	}

	if (data.using_oneshots_or_loops)
	{
		assert(IsDefined(component["oneshots"]) || IsDefined(component["loops"]));
		
		/#
		if (data.using_entity)
		{
			assert(IsDefined(data.ent));
		}
		#/
				

		wait_time = DAMBx_make_first_wait(data);
		assert(IsDefined(wait_time));
			
		while(true)
		{
			if (level._audio.damb.playing[type][stored_name]["paused"])
			{
				// if paused, wait only for a manual event notify
				level waittill(type + "_" + stored_name + "_event");
			}
			
			if (!level._audio.damb.playing[type][stored_name]["paused"])
			{
				wait(wait_time);
			}
			
			// before doing anything, need to check if we are using an entity to play the 
			// damb on and it gets deleted. If so, then we need to stop the dynamic ambience!
			if (data.using_entity && !IsDefined(data.ent)) 
			{
				level notify(type + "_" + stored_name + "_stop");
				break; 
			}
			
			// check for any linked dambs to play an event
			if (IsDefined(level._audio.damb.playing[type][stored_name]["linked_dambs"]))
			{
				foreach(linked_damb in level._audio.damb.playing[type][stored_name]["linked_dambs"])
				{
					assert(IsDefined(linked_damb.name));
					assert(IsDefined(linked_damb.min_delay));
					assert(IsDefined(linked_damb.max_delay));
					delay_time = RandomFloatRange(linked_damb.min_delay, linked_damb.max_delay);
					thread DAMBx_trigger_linked_damb(linked_damb.name, delay_time);
				}
			}
			
			// update the probability
			data.prob_scale = level._audio.damb.playing[type][stored_name]["prob_scale"];
			
			event = DAMBx_create_damb_event(data, stored_name, component, point_);
			assert(IsDefined(event));
			assert(IsDefined(event.success));
 			
 			// if event.success == false that means that probabilistically speaking, it didn't succeed in making a damb event
 			if (event.success)
			{			
				thread DAMBx_perform_play_event(type, stored_name, event); 
			}
			// new wait time...
			wait_time = RandomFloatRange(data.min_time, data.max_time);
		}
	}
}

DAMBx_wait_till_sound_done_and_remove_handle(type, stored_name, oneshot_index, entity)
{
	assert(IsString(type));
	assert(IsString(stored_name));
	assert(IsDefined(oneshot_index));
	assert(IsDefined(entity));
	
	level endon(type + "_" + stored_name + "_stop");
	entity waittill("sounddone");
	
	if (IsDefined(level._audio.damb.playing[type][stored_name]["oneshots"][oneshot_index]))
	{
		entity delete();
		decrement_ref_count();
		level._audio.damb.playing[type][stored_name]["oneshots"][oneshot_index] = undefined;
	}
}

DAMBx_perform_play_event(type, stored_name, event)
{
	assert(IsString(type));
	assert(IsString(stored_name));
	assert(IsDefined(event));

	level endon(type + "_" + stored_name + "_stop");
	
	if (event.alias["type"] == "loop")
	{
		DAMBx_perform_loop_event(type, stored_name, event);
	}
	else
	{
		DAMBx_perform_oneshot_event(type, stored_name, event);
	}
}

DAMBx_perform_oneshot_event(type, stored_name, event)
{
	assert(IsString(type));
	assert(IsString(stored_name));
	assert(IsDefined(event));
	assert(event.alias["type"] == "oneshot");
	
	level endon(type + "_" + stored_name + "_stop");	
	
	// the point to base the start/end positions from (can optionally pass in a world point)
	sound_origin = level.player.origin;
	if (IsDefined(event.ent))
	{
		sound_origin = event.ent.origin;
	}
	else if (IsDefined(event.point))
	{
		sound_origin = event.point;
	}
	
	// play the sound at the start position
	if (level._audio.damb.entity_ref_count < level._audio.damb.max_entities)
	{
		entity = spawn("script_origin", sound_origin + event.start_position);

		if (IsDefined(event.ent) && event.mode == "attach") 
		{
			entity LinkTo(event.ent);
		}
		
		assert(IsString(event.alias["name"]));
		
		entity PlaySound(event.alias["name"], "sounddone");
		entity thread aud_check_sound_done();
	
		if (!entity.sounddone)
		{	
			oneshot_index = level._audio.damb.oneshot_handle_index;
			level._audio.damb.playing[type][stored_name]["oneshots"][oneshot_index] = entity;
			level._audio.damb.oneshot_handle_index++;
			increment_ref_count();

			if (IsDefined(event.end_position) && !IsDefined(event.entity)) // can't move a sound if attached to an entity
			{
				accel_time = 0.1 * event.travel_time;
				
				entity MoveTo(sound_origin + event.end_position, event.travel_time, accel_time, accel_time);
			}
			
			// now perform pitch operations
			if (IsDefined(event.start_pitch))
			{
				entity ScalePitch(event.start_pitch);
			}
			
			if (IsDefined(event.pitch_time))
			{
				assert(IsDefined(event.end_pitch));
				wait(0.05); 	
				if (IsDefined(entity) && !entity.sounddone) 
				{
					entity ScalePitch(event.end_pitch, event.pitch_time);	
				}
			}
			
			// spawn a thread to clean up the oneshot sound when the sound is done playing
			thread DAMBx_wait_till_sound_done_and_remove_handle(type, stored_name, oneshot_index, entity);

			entity waittill("sounddone"); // wait for the case of serial playback, and pause this thread until it's done
		}
		else 
		{
			// sound finished instantly, so just delete the entity
			entity delete();
		}
	}
	else
	{
		aud_print_warning("TRYING TO PLAY ONESHOT WITH DAMB REF COUNT AT MAXIMUM!");
	}
}

DAMBx_perform_loop_event(type, stored_name, event)
{
	assert(IsString(type));
	assert(IsDefined(stored_name));
	assert(IsDefined(event));
	assert(event.alias["type"] == "loop");
	
	level endon(type + "_" + stored_name + "_stop");
	
		// play the sound at the start position
	if (level._audio.damb.entity_ref_count < level._audio.damb.max_entities)
	{
		// the point to base the start/end positions from (can optionally pass in a world point)
		sound_origin = level.player.origin;
		if (IsDefined(event.ent))
		{
			assert(IsDefined(event.mode));
			assert(event.mode == "attach" || event.mode == "free");
			sound_origin = event.ent.origin;
		}
		else if (IsDefined(event.point))
		{
			sound_origin = event.point;
		}
		
		// compute the loop-related data
		loop_preset_name = event.alias["name"];
	
		loop_preset = DAMBx_get_loop_preset(loop_preset_name);
		if (!IsDefined(loop_preset))
			return;	
		
		min_dur = min(loop_preset["duration"][0], loop_preset["duration"][1]);
		max_dur = max(loop_preset["duration"][0], loop_preset["duration"][1]);
	
		duration = RandomFloatRange(min_dur, max_dur);
		
		start_alias = loop_preset["loop_alias"];
		
		fade_in = loop_preset["fade_in"];
		fade_out = loop_preset["fade_out"];
		
		// end aliases might be optional
		end_alias = undefined;
		if (IsDefined(loop_preset["end_alias"]))
		{
			end_alias = loop_preset["end_alias"];
		}
		
		entity = spawn("script_origin", sound_origin + event.start_position);	
		
		if (IsDefined(event.ent) && event.mode == "attach") 
		{
			entity LinkTo(event.ent);
		}
	
		entity PlayLoopSound(start_alias);
		if (IsDefined(fade_in))
		{
			assert(fade_in >= 0.0);
			entity scalevolume(0.0);
			wait(0.05);
			entity scalevolume(1.0, fade_in);
		}
		entity thread aud_check_sound_done();
	
		if (!entity.sounddone)
		{
			// store this entity onto the sound handle list in case this thread gets endon'd
			loop_index = level._audio.damb.loop_handle_index;
			level._audio.damb.playing[type][stored_name]["loops"][loop_index] = entity;
			increment_ref_count();
			level._audio.damb.loop_handle_index++;
			
			is_moving = false;
			if (IsDefined(event.mode) && event.mode == "free" && IsDefined(event.end_position))
				is_moving = true;
			else if (!IsDefined(event.mode) && IsDefined(event.end_position))
				is_moving = true;
			
			// move the entity if we are supposed to
			if (is_moving) 
			{
				assert(IsDefined(event.travel_time));
				// note, i'm putting in some smoothing acceleration which is 10% the travel time, if this something we want to put in the preset, let me know - aaron
				accel_time = 0.1 * event.travel_time;
				entity MoveTo(sound_origin + event.end_position, event.travel_time, accel_time, accel_time); 
			}
			
			// now perform pitch operations
			if (IsDefined(event.start_pitch))
			{
				entity SetPitch(event.start_pitch);
			}
			
			if (IsDefined(event.pitch_time))
			{
				assert(IsDefined(event.end_pitch));		
				wait(0.05);
				if (IsDefined(entity) && !entity.sounddone) // make sure the entity is still defined (in case it was killed by a different thread, since we waited here)
				{
					entity SetPitch(event.end_pitch, event.pitch_time);
				}
			}
			
			// now wait the duration
			wait(duration); 
			
			if (!entity.sounddone)
			{
				// only try and do anything if this hasn't been turned off or killed by other threads
				if (IsDefined(level._audio.damb.playing[type][stored_name]["loops"][loop_index]))
				{
					if (IsDefined(end_alias))
					{
						// play the end_alias!
						
						// create the end entity
						end_entity = spawn("script_origin", entity.origin); // create a new entity at the origin of the old entity (remember, it might be half-way through it's destination)
											
						end_entity PlaySound(end_alias, "sounddone");
						
						// store the entity handle so it can be stopped in case we are stopped
						oneshot_index = level._audio.damb.oneshot_handle_index;
						level._audio.damb.oneshot_handle_index++;
						level._audio.damb.playing[type][stored_name]["oneshots"][oneshot_index] = end_entity;
						increment_ref_count();
						
						// spawn a thread to clean up the end sound when the sound is done playing
						thread DAMBx_wait_till_sound_done_and_remove_handle(type, stored_name, oneshot_index, end_entity);
					}
					
					// now stop the looping sound and clean up
					if (IsDefined(fade_out))
					{
						thread aud_fade_loop_out_and_delete(entity, fade_out);
					}
					else
					{
						entity StopLoopSound();
						wait(0.05);
						entity delete();
					}
					decrement_ref_count();
					level._audio.damb.playing[type][stored_name]["loops"][loop_index] = undefined;
				}
			}
			else
			{
				// now stop the looping sound and clean up
				entity StopLoopSound(); 
				entity delete();
				decrement_ref_count();
				level._audio.damb.playing[type][stored_name]["loops"][loop_index] = undefined;
			}
		}
		else
		{
			// something stopped this loop instantly, need to clean up
			entity delete();
		}
	}
	else
	{
		aud_print_warning("TRYING TO PLAY LOOP WITH DAMB REF COUNT AT MAXIMUM!");
	}
}

DAMBx_pick_random_component(type, name)
{
	assert(IsDefined(level._audio.damb.playing[type][name]));
	assert(IsDefined(level._audio.damb.playing[type][name]["components"]));
	
	total_weight = 0;
	foreach( comp_weight_pair in level._audio.damb.playing[type][name]["components"])
	{
		assert(IsDefined(comp_weight_pair[1]));
		weight = comp_weight_pair[1];
		total_weight += weight;
	}
	
	choice = randomfloat(total_weight);
	
	prev_val = 0.0;
	chosen_component = undefined;
	foreach( comp_weight_pair in level._audio.damb.playing[type][name]["components"])
	{
		next_val = prev_val + comp_weight_pair[1];
		if (choice >= prev_val && choice < next_val)
		{
			assert(IsString(comp_weight_pair[0]));
			chosen_component = comp_weight_pair[0];
			break;
		}
		prev_val = next_val;
	}
	assert(IsDefined(chosen_component));
	
	component_preset = DAMBx_get_component_preset(chosen_component);
	if (!IsDefined(component_preset))
		return;

	component_preset["name"] = chosen_component;
	return component_preset;
}

DAMBx_pick_random_alias(component)
{
	assert(IsDefined(component));
	assert(IsDefined(component["name"]));
	assert(IsDefined(level._audio.damb.component_weights));
	
	loops = component["loops"];
	oneshots = component["oneshots"];
	
	total_weight = undefined;
	// add up total weight
	if (!IsDefined(level._audio.damb.component_weights[component["name"]]))
	{
		total_weight = 0;
		if (IsDefined(loops))
		{
			if (IsString(loops[0])) // this is a single entry
			{
				total_weight = total_weight + loops[1];
			}
			else
			{
				foreach(entry in loops)
				{
					total_weight = total_weight + entry[1];
				}
			}
		}
		if (IsDefined(oneshots))
		{		
			if (IsString(oneshots[0])) // this is a single entry
			{
				total_weight = total_weight + oneshots[1];
			}
			else
			{
				foreach(entry in oneshots)
				{
					total_weight = total_weight + entry[1];
				}
			}
		}
		level._audio.damb.component_weights[component["name"]] = total_weight;
	}
	else
	{
		total_weight = level._audio.damb.component_weights[component["name"]];
	}
	
	assert(IsDefined(total_weight));

	// now make a random choice
	random_choice = RandomFloatRange(0.0, total_weight);
	
	// figure out which alias was picked	
	chosen_alias = undefined;
	alias_type = undefined;
	prev_val = 0.0;
	if (IsDefined(loops))
	{
		if (IsString(loops[0]))
		{
			next_val = prev_val + loops[1];
			if (random_choice >= prev_val && random_choice < next_val)
			{
				chosen_alias = loops[0];
				alias_type = "loop";
			}
			else
			{
				prev_val = next_val;
			}
		}
		else
		{
			foreach(entry in loops)
			{
				next_val = prev_val + entry[1];
				if (random_choice >= prev_val && random_choice < next_val)
				{
					chosen_alias = entry[0];
					alias_type = "loop";
					break;
				}
				else
				{
					prev_val = next_val;
				}
			}
		}
	}
	
	if (!IsDefined(chosen_alias) && IsDefined(oneshots))
	{
		if (IsArray(oneshots))
		{
			foreach(entry in oneshots)
			{
				next_val = prev_val + entry[1];
				if (random_choice >= prev_val && random_choice < next_val)
				{
					chosen_alias = entry[0];
					alias_type = "oneshot";
					break;
				}
				else
				{
					prev_val = next_val;
				}
			}
		}
		else
		{
			next_val = prev_val + oneshots[1];
			if (random_choice >= prev_val && random_choice < next_val)
			{
				chosen_alias = oneshots[0];
				alias_type = "oneshot";
			}
			else
			{
				prev_val = next_val;
			}
		}
	}
	
	assert(IsString(chosen_alias));
	assert(IsString(alias_type));
	
	result = [];
	result["name"] = chosen_alias;
	result["type"] = alias_type;
	return result;
}

DAMBx_get_loop_preset(loop_preset_name)
{
	loop_preset = [];

	if (IsDefined(level._audio.damb.loop_cache[loop_preset_name]))
	{
		loop_preset = level._audio.damb.loop_cache[loop_preset_name];
	}
	else if (level._audio.damb.use_string_table_presets)
	{
		loop_preset = DAMBx_get_loop_def_from_string_table(loop_preset_name, true);		
	}
	else
	{
		loop_preset = DAMBx_get_loop_def_from_string_table(loop_preset_name, false); // only check common	
		if (!IsDefined(loop_preset) || loop_preset.size == 0)
			loop_preset = AUDIO_PRESETS_DYNAMIC_AMBIENCE_LOOP_DEFINITIONS(loop_preset_name, loop_preset);		
	}
	
	if (!IsDefined(loop_preset) || loop_preset.size == 0)
	{
		/#
		aud_print_error("failed to get dynamic ambience loop preset: " + loop_preset_name);
		#/
		return;
	}
	level._audio.damb.loop_cache[loop_preset_name] = loop_preset;
	return loop_preset;
}


DAMBx_get_component_preset(name)
{
	assert(IsString(name));
	if (!IsDefined(level._audio.damb.component_cache))
		level._audio.damb.component_cache = [];
		
	component = [];
	if (IsDefined(level._audio.damb.component_cache[name]))
	{
		component = level._audio.damb.component_cache[name];
	}
	else if (level._audio.damb.use_string_table_presets)
	{
		component = DAMBx_get_component_from_string_table(name, true); // check level + common files
	}
	else
	{
		component = DAMBx_get_component_from_string_table(name, false); // check common files
		if (!IsDefined(component) || component.size == 0)
			component = AUDIO_PRESETS_DYNAMIC_AMBIENCE_COMPONENTS(name, component);
			
	}
	
	if (!IsDefined(component) || component.size == 0)
	{
		/#
		aud_print_error("failed to load dynamic ambience component: " + name);
		#/
		return;
	}
	
	// store in cache
	level._audio.damb.component_cache[name] = component;
	return component;
}

// this is on a thread
DAMBx_play(type, stored_name, point_)
{
	assert(IsString(type));
	assert(IsDefined(stored_name));
	assert(IsDefined(level._audio.damb.playing[type][stored_name]));
	
	// an array of loop handles
	level._audio.damb.playing[type][stored_name]["loops"] = [];
	level._audio.damb.playing[type][stored_name]["single_loops"] = [];
	level._audio.damb.playing[type][stored_name]["oneshots"] = [];
	
	if (!IsDefined(level._audio.damb.playing[type][stored_name]["event_time"]))
	{	
		foreach( component_name in level._audio.damb.playing[type][stored_name]["components"])
		{
			component = DAMBx_get_component_preset(component_name);			
			if (!IsDefined(component)) // error loading file
				return;
			component["name"] = component_name;
			thread DAMBx_update(type, stored_name, component, point_);
		}
	}
	else
	{
		thread DAMBx_update_serially(type, stored_name, point_);		
	}
	level waittill(type + "_" + stored_name + "_stop"); 
	wait(0.1);
	
	// perform cleanup of loops with a nice fade out defined by the DAMBx_stop function.
	assert(IsDefined(level._audio.damb.playing[type][stored_name]["fade"]));
	
	foreach(entity in level._audio.damb.playing[type][stored_name]["loops"])
	{
		thread DAMBx_fade_out_playing_loop(entity, level._audio.damb.playing[type][stored_name]["fade"], false);
	}
	
	foreach(entity in level._audio.damb.playing[type][stored_name]["single_loops"])
	{
		thread DAMBx_fade_out_playing_loop(entity, level._audio.damb.playing[type][stored_name]["fade"], true);
	}
	
	foreach(entity in level._audio.damb.playing[type][stored_name]["oneshots"])
	{
		thread DAMBx_fade_out_playing_sound(entity, level._audio.damb.playing[type][stored_name]["fade"]);
	}
	
	// remove the dynamic ambience from the playing list of dynamic ambiences
	level._audio.damb.playing[type][stored_name] = undefined; 
}

DAMBx_fade_out_playing_sound(entity, fade)
{
	if (IsDefined(entity))
	{
		assert(IsDefined(fade) && fade >= 0.0);
		entity ScaleVolume(0.0, fade);
		wait (fade);
		entity StopSounds();
		wait(0.05);
		entity delete();
		decrement_ref_count();
	}
}

DAMBx_fade_out_playing_loop(entity, fade, isSingle)
{
	assert(IsDefined(entity));
	assert(IsDefined(fade) && fade >= 0.0);
	entity ScaleVolume(0.0, fade); // scale out the volume
	wait (fade);
	entity StopLoopSound(); // then stop the loop
	wait(0.05);
	entity delete();
	if (isSingle)
	{
		level._audio.damb.loop_entity_ref_count--;
	}
	else
	{
		decrement_ref_count();
	}
}

DAMBx_get_list_value_from_string_table(table_value, type_name, label_name, add_probs_)
{
	add_probs = false;
	if (IsDefined(add_probs_))
		add_probs = add_probs_;
		
	result = [];
	has_weights = false;
	value_array = StrTok(table_value, "+");
	has_weights_been_set = false;
	for(i = 0; i < value_array.size; i++)
	{
		value = StrTok(value_array[i], " "); // get the possibly space-separated sub-string (which means it's a value-weight pair)
		assertEx(value.size > 0, "In dynamic ambience " + type_name + " \"" + label_name + "\" in dynamic_ambience.csv, there appears to be a dangling \"+\".");
		if (value.size == 1 && value[0] != "")
		{
			assertEx(has_weights == false, "In dynamic ambience " + type_name + " \"" + label_name + "\" in dynamic_ambience.csv, once you define a weight value on a oneshot, you must define a weight value on all oneshots.");
			result[result.size] = value[0];
		}
		else
		{
			assertEx(value.size == 2, "In dynamic ambience " + type_name + " \"" + label_name + "\" in dynamic_ambience.csv, unless specifying only a list of aliases, you must give a list value-weight pairs separated by + signs.");
			/#
			if (!has_weights_been_set)
			{
				has_weights_been_set = true;
				has_weights = true;
			}
		
			assertEx(has_weights == true, "In dynamic ambience " + type_name + " \"" + label_name + "\" in dynamic_ambience.csv, once you define a weight value, you must define a weight value on all elements.");
			#/
			result_size = result.size;
			result[result_size] = [];
			result[result_size][0] = value[0];  // the element name
			result[result_size][1] = float(value[1]); // the element weight			
		}
	}
		
	if (!has_weights && add_probs)
	{
		final_result = [];
		for( i = 0; i < result.size; i++)
		{
			final_result_size = final_result.size;
			final_result[final_result_size] = [];
			final_result[final_result_size][0] = result[i];
			final_result[final_result_size][1] = 1.0;
		}
		result = final_result;
	}
	
	
	return result;
}

/#
DAMBx_validate_string_table_pair(array_pair, type_name, param_name_min, param_name_max)
{
		if (IsDefined(array_pair[0]))
		{
			assertEx(IsDefined(array_pair[1]), "In dynamic ambience \"" + type_name + "\" in dynamic_ambience.csv, if you define one, you must define a value for both \"" + param_name_min + "\" and \"" + param_name_max + "\".");
		}	
}
#/

DAMBx_get_loop_def_from_string_table(loop_name, checklevel)
{
	assert(IsString(loop_name));
	assert(IsDefined(checklevel));
	
	common_stringtable = "soundtables/common_damb_loops.csv";
	level_stringtable = maps\_audio::get_damb_loops_stringtable();
	preset = [];
	
	/#
	if (aud_check_fastfiles()) return preset;
	#/
	
	if (checklevel)
		preset = DAMBx_get_loop_def_from_string_table_internal(level_stringtable, loop_name);
	
	if (!IsDefined(preset) || preset.size == 0)
		preset = DAMBx_get_loop_def_from_string_table_internal(common_stringtable, loop_name);
	
	if (!IsDefined(preset) || preset.size == 0) // error loading file
	{
		return;
	}
	
	return preset;
}

DAMBx_get_loop_def_from_string_table_internal(stringtable, loop_name)
{
	assert(IsString(stringtable));
	assert(IsString(loop_name));
	// find column number of when loop defs begin
	loop_def = [];
	num_loop_cols = 8;
	loop_alias = undefined;
	end_alias = undefined;
	fade_in = undefined;
	fade_out = undefined;
	duration = [];
		
	for(i = 0; i < num_loop_cols; i++)
	{
		col_name = tablelookup( stringtable, 0, "loop_defs", i);
		if (!IsDefined(col_name) || col_name == "")
		{
			assertEx(IsDefined(col_name),  "Couldn't find stringtable file \"" + stringtable + "\". Check zone source for errors.");
			return;
		}
		table_value = tablelookup( stringtable, 0, loop_name, i);

		if (table_value != "" && col_name != "comments")
		{
			switch(col_name)
			{
				case "loop_alias":
					assertEx(IsDefined(table_value) && table_value != "", "In dynamic_ambience.csv loop definition file, loop definition \"" + loop_name + "\" requires a loop_alias.");
					loop_alias = table_value;
				break;
				case "fade_in":
					if (IsDefined(table_value) && table_value != "")
					{
						fade_in = max(float(table_value), 0.0);
					}
				break;
				case "fade_out":
					if (IsDefined(table_value) && table_value != "")
					{
						fade_out = max(float(table_value), 0.0);
					}
				break;
				case "end_alias":
					if (IsDefined(table_value) && table_value != "")
					{
						end_alias = table_value;
					}
				break;
				case "duration_min":
					if (IsDefined(table_value) && table_value != "")
					{
						duration[0] = float(table_value);
					}
				break;
				case "duration_max":
					if (IsDefined(table_value) && table_value != "")
					{
						duration[1] = float(table_value);
					}
				break;
				default:
				break;
			}
		}
	}
	
	/#
	DAMBx_validate_string_table_pair(duration, "loop definition", "duration_min", "duration_max");
	assertEx(IsDefined(loop_alias), "In dynamic_ambience.csv loop definition file, loop definition \"" + loop_name + "\" requires a loop_alias.");
	#/
	
	loop_def["loop_alias"] = loop_alias;
	if (IsDefined(fade_in))
	{
		assert(fade_in >= 0.0);
		loop_def["fade_in"] = fade_in;
	}
	if (IsDefined(fade_out))
	{
		assert(fade_out >= 0.0);
		loop_def["fade_out"] = fade_out;
	}
	if (IsDefined(end_alias))
	{
		loop_def["end_alias"] = end_alias;
	}
	if (IsDefined(duration[0]))
	{
		loop_def["duration"] = DAMBx_get_two_value_float_array(duration);
	}
	
	return loop_def;
}

DAMBx_get_two_value_float_array(string_array)
{
	assert(IsArray(string_array) && string_array.size == 2);
	float_array = [];
	float_array[0] = float(string_array[0]);
	float_array[1] = float(string_array[1]);
	return float_array;
}

DAMBx_get_component_from_string_table_internal(stringtable, component_name)
{
	assert(IsString(stringtable));
	assert(IsString(component_name));

	component = []; // the resulting component
	
	num_component_cols = 21;
	start = 8;
	oneshots = [];
	loops = [];
	single_loops = [];
	first_event = [];
	event_time = [];
	dist = [];
	cone = [];
	travel = [];
	travel_time = [];
	pitch = [];
	pitch_time = [];
	param_count = 0;
	for(i = 1; i < num_component_cols; i++)
	{
		col_name = tablelookup( stringtable, 0, "components", i);
		if (!IsDefined(col_name))
		{
			assertEx(false,  "Dynamic ambience preset file \"" + stringtable + "\" not found. Check zone source for errors.");	
			return;
		}
		table_value = tablelookup( stringtable, 0, component_name, i);

		if (table_value != "" && col_name != "comments")
		{
			param_count++;
			switch(col_name)
			{
				case "oneshots":
				oneshots = DAMBx_get_list_value_from_string_table(table_value, "component definition", "oneshots", true);	
				break;
				case "loops":
				loops = DAMBx_get_list_value_from_string_table(table_value, "component definition", "loops", true);
				break;
				case "single_loops":
				single_loops = DAMBx_get_list_value_from_string_table(table_value, "component definition", "single_loops", false);
				break;
				case "first_event_min":
				first_event[0] = float(table_value);
				break;
				case "first_event_max":
				first_event[1] = float(table_value);
				break;
				case "event_time_min":
				event_time[0] = float(table_value);
				break;
				case "event_time_max":
				event_time[1] = float(table_value);
				break;
				case "dist_min":
				dist[0] = float(table_value);
				break;
				case "dist_max":
				dist[1] = float(table_value);
				break;
				case "cone_min":
				cone[0] = float(table_value);
				break;
				case "cone_max":
				cone[1] = float(table_value);
				break;
				case "travel_min":
				travel[0] = float(table_value);
				break;
				case "travel_max":
				travel[1] = float(table_value);
				break;
				case "travel_time_min":
				travel_time[0] = float(table_value);
				break;
				case "travel_time_max":
				travel_time[1] = float(table_value);
				break;
				case "pitch_min":
				pitch[0] = float(table_value);
				break;
				case "pitch_max":
				pitch[1] = float(table_value);
				break;
				case "pitch_time_min":
				pitch_time[0] = float(table_value);
				break;
				case "pitch_time_max":
				pitch_time[1] = float(table_value);
				break;
				default: 
				assertEx(false, "In dynamic_ambience.csv preset definition file, column name \"" + col_name + "\" probably has a typo, please fix.");
				break;
			}
		}
	}
	
	if (param_count > 0) // param_count == 0, means that the component was found in this file
	{
		
		// now construct the component array
		
		/#
		assertEx(IsDefined(loops[0]) || IsDefined(oneshots[0]) || IsDefined(single_loops[0]), "In dynamic ambience component definition \"" + component_name + "\" in dynamic_ambience.csv, you mist define at least one loops, oneshots, or single_loops list.");
		DAMBx_validate_string_table_pair(first_event, "component definition", "first_event_min", "first_event_max");
		DAMBx_validate_string_table_pair(event_time, "component definition", "event_time_min", "event_time_max");
		DAMBx_validate_string_table_pair(dist, "component definition", "dist_min", "dist_max");
		DAMBx_validate_string_table_pair(cone, "component definition", "cone_min", "cone_max");
		DAMBx_validate_string_table_pair(travel, "component definition", "travel_min", "travel_max");
		DAMBx_validate_string_table_pair(travel_time, "component definition", "travel_time_min", "travel_time_max");
		DAMBx_validate_string_table_pair(pitch, "component definition", "pitch_min", "pitch_max");
		DAMBx_validate_string_table_pair(pitch_time, "component definition", "pitch_time_min", "pitch_time_max");
		
		if (IsDefined(travel[0]))
		{
			assertEx(IsDefined(travel_time[0]), "In dynamic ambience component definition in dynamic_ambience.csv, if you define one, you must define a \"travel\" value (min or max), you must also define a \"travel_time\" value (min and max).");
		}
		#/
		
		if (IsDefined(oneshots[0]))
		{
			if (IsString(oneshots[0]))
				oneshots[1] = 1.0;
				
			component["oneshots"] = oneshots;
		}
		if (IsDefined(loops[0]))
		{
			component["loops"] = loops;
		}
		if (IsDefined(single_loops[0]))
		{
			component["single_loops"] = single_loops;
		}
		if (IsDefined(first_event[0]))
		{
			component["first_event"] = DAMBx_get_two_value_float_array(first_event);		
		}
		if (IsDefined(event_time[0]))
		{
			component["event_time"] = DAMBx_get_two_value_float_array(event_time);
		}
		if (IsDefined(dist[0]))
		{
			component["radius"] = DAMBx_get_two_value_float_array(dist);
		}
		if (IsDefined(cone[0]))
		{
			component["cone"] = DAMBx_get_two_value_float_array(cone);
		}
		if (IsDefined(travel[0]))
		{
			component["delta"] = DAMBx_get_two_value_float_array(travel);
		}
		if (IsDefined(travel_time[0]))
		{
			component["travel_time"] = DAMBx_get_two_value_float_array(travel_time);
		}
		if (IsDefined(pitch[0]))
		{
			component["pitch"] = DAMBx_get_two_value_float_array(pitch);
		}
		if (IsDefined(pitch_time[0]))
		{
			component["pitch_time"] = DAMBx_get_two_value_float_array(pitch_time);
		}
		if (!IsDefined(component["radius"]))
		{
			component["radius"] = [0.0, 0.01];
		}
	}
	return component;
}

DAMBx_get_component_from_string_table(component_name, checklevel)
{
	assert(IsDefined(checklevel));
	assert(IsString(component_name));
	
	level_stringtable = maps\_audio::get_damb_component_stringtable();
	common_stringtable = "soundtables/common_damb_components.csv";
	preset = [];
	
	/#
	if (aud_check_fastfiles()) return preset;
	#/
	
	if (checklevel)
		preset = DAMBx_get_component_from_string_table_internal(level_stringtable, component_name);
	
	if (!IsDefined(preset) || preset.size == 0)
		preset = DAMBx_get_component_from_string_table_internal(common_stringtable, component_name);
	
	if (!IsDefined(preset) || preset.size == 0) // error loading file
	{	
		return;
	}
		
	return preset;
}

DAMBx_get_preset_from_stringtable_internal(stringtable, presetname)
{
	num_damb_cols = 7;
	preset = [];
	components = [];
	first_event = [];
	event_time = [];
	
	for (i = 1; i < num_damb_cols; i++)
	{
		col_name = tablelookup( stringtable, 0, "dynamic_ambience", i);
		assertEx(IsDefined(col_name), "Dynamic ambience preset file \"" + stringtable + "\" is not found (check zone source for errors)");
		table_value = tablelookup( stringtable, 0, presetname, i);
		assert(IsDefined(table_value));
		is_serial_dynamic_ambience = false;
		
		if (table_value != "" && col_name != "comments")
		{
			switch(col_name)
			{
				case "components": // construct the components preset array
					components = DAMBx_get_list_value_from_string_table(table_value, "preset definition", "components");
				break;
				case "first_event_min":
					if (IsDefined(table_value) && table_value != "")
					{
						first_event[0] = float(table_value);
					}
				break;
				case "first_event_max":
					if (IsDefined(table_value) && table_value != "")
					{
						first_event[1] = float(table_value);
					}
				break;
				case "event_time_min":
					if (IsDefined(table_value) && table_value != "")
					{
						event_time[0] = float(table_value);
					}
				break;
				case "event_time_max":
					if (IsDefined(table_value) && table_value != "")
					{
						event_time[1] = float(table_value);
					}
				case "comment":
				// do nothing
				break;	
				default: 
					assertEx(false, "In " + stringtable + " preset definition file, column name \"" + col_name + "\" probably has a typo, please fix.");
				break;		
			}
		}
	}
	
	// now construct the preset array
	
	/#
	// check the optional params consistency
	DAMBx_validate_string_table_pair(first_event, "preset", "first_event_min", "first_event_max");
	DAMBx_validate_string_table_pair(event_time, "preset", "event_time_min", "event_time_max");
	#/
	
	is_serial_dynamic_ambience = false;
	if (IsDefined(first_event[0]))
	{
		is_serial_dynamic_ambience = true;
		preset["first_event"] = first_event;
	}
	if (IsDefined(event_time[0]))
	{
		is_serial_dynamic_ambience = true;
		preset["event_time"] = event_time;
	}
	
	if (is_serial_dynamic_ambience)
	{
		if (IsDefined(components[0][1]))
		{
			preset["components"] = components;
		}
		else
		{
			preset["components"] = [];
			for(i = 0; i < components.size; i++)
			{
				preset["components"][preset["components"].size] = [ components[0], 1.0];
			}
			if (preset["components"].size == 0)
			{
				preset["components"] = undefined;
			}
		}
	}
	else if (components.size != 0)
	{
		preset["components"] = components;
	}
	
	return preset;
}


DAMBx_get_preset_from_string_table(presetname, checklevel)
{
	assert(IsString(presetname));
	assert(IsDefined(checklevel));

	level_stringtable = maps\_audio::get_damb_stringtable();	
	common_stringtable = "soundtables/common_damb.csv";
	preset = [];	
	
	if (checklevel)
		preset = DAMBx_get_preset_from_stringtable_internal(level_stringtable, presetname);
	
	if (!IsDefined(preset) || preset.size == 0)
		preset = DAMBx_get_preset_from_stringtable_internal(common_stringtable, presetname);
	
	if (!IsDefined(preset) || preset.size == 0)
	{
		return;
	}
	
	return preset;
}


DAMBx_get_damb_preset(name)
{
	assert(IsString(name));
	
	damb = [];
	if (IsDefined(level._audio.damb.preset_cache[name]))
	{
		damb = level._audio.damb.preset_cache[name];
	}
	else
	{
		damb = DAMBx_get_preset_from_string_table(name, true); // check level + common
	}

	if (!IsDefined(damb) || damb.size == 0)
	{
		/#
		aud_print_error("failed to get dynamic ambience preset: " + name);
		#/
		return;
	}
	
	level._audio.damb.preset_cache[name] = damb;	
	damb["name"] = name;
	
	/#
	DAMBx_validate_damb_preset(damb); 
	#/
	
	return damb;
}


/#
DAMBx_validate_loop_preset(name, component_name)
{
	assert(IsDefined(name));
	assert(IsDefined(component_name));
	
	loop_preset = DAMBx_get_loop_preset(name);
	if (!IsDefined(loop_preset))
		return; // failed to load
	assertEx(loop_preset.size > 0, "Dynamic ambience component, \""  + component_name + "\", is trying to use an invalid loop preset name, \"" + name + "\".");
	assertEx(IsDefined(loop_preset["loop_alias"]), "Dynamic ambience component, \""  + component_name + "\", loop preset, \"" + name + "\", must define a \"loop_alias\".");
	assertEx(IsDefined(loop_preset["end_alias"]), "Dynamic ambience component, \""  + component_name + "\", loop preset, \"" + name + "\", must define a \"end_alias\".");
	assertEx(IsDefined(loop_preset["duration"]), "Dynamic ambience component, \""  + component_name + "\", loop preset, \"" + name + "\", must define a \"duration\".");
	DAMBx_validate_label(loop_preset, "duration", component_name);
	assertEx(IsString(loop_preset["loop_alias"]), "Dynamic ambience component, \""  + component_name + "\", loop preset, \"" + name + "\", must supply an alias for \"loop_alias\".");
	if (IsDefined(loop_preset["end_alias"]))
	{
		assertEx(IsString(loop_preset["end_alias"]), "Dynamic ambience component, \""  + component_name + "\", loop preset, \"" + name + "\", must supply an alias for optional \"end_alias\" label.");
	}
}
#/

/#
DAMBx_validate_loops(loops, component_name)
{
	assert(IsDefined(loops));
	assertEx(loops.size > 0, "Dynamic ambience component, \""  + component_name + "\", is using a \"loops\" label but not supplying any loop presets.");
	
	if (IsString(loops[0]))
	{
		if (loops.size != 2)
		{
			assertEx(false,  "Dynamic ambience component, \""  + component_name + "\", \"loops\" list is probably in the wrong format.");
		}
		else
		{
			assertEx(loops[1] >= 0.0, "Dynamic ambience component, \""  + component_name + "\", \"loops\" random weights must be greater than zero.");			
		}
		
		DAMBx_validate_loop_preset(loops[0], component_name);
	}
}
#/

/#
DAMBx_validate_oneshots(oneshots, component_name)
{
	assert(IsDefined(oneshots));
	assertEx(oneshots.size > 0, "Dynamic ambience component, \""  + component_name + "\", is using a \"oneshots\" label but not supplying any oneshot aliases.");

	// if the zeroth index is a string, then it is a single element list and the list should be of length 2
	if (IsString(oneshots[0]))
	{
		if (oneshots.size != 2)
		{
			assertEx(false,  "Dynamic ambience component, \""  + component_name + "\", \"oneshots\" list is probably in the wrong format.");
		}
		else
		{
			assertEx(oneshots[1] >= 0.0, "Dynamic ambience component, \""  + component_name + "\", \"oneshots\" random weights must be greater than zero.");
		}
	}
	else
	{
		for (i = 0; i < oneshots.size; i++)
		{
			oneshot = oneshots[i];
			assertEx(oneshot.size == 2 && IsString(oneshot[0]) && !IsString(oneshot[1]), "Dynamic ambience component, \""  + component_name + "\", \"oneshots\" array needs to be in the following format: [alias, weight].");
			assertEx(oneshot[1] >= 0.0, "Dynamic ambience component, \""  + component_name + "\", \"oneshots\" random weights must be greater than zero.");
		}
	}
}
#/


/#
DAMBx_validate_label(component, label, component_name)
{
	assertEx(IsDefined(component[label]), "Dynamic ambience component, \""  + component_name + "\", needs to define a \"" + label + "\" range.");
	assertEx(component[label].size == 2, "Dynamic ambience component, \"" + component_name + "\", needs to define a \"" + label + "\" range with 2 values.");
	assertEx(component[label][0] != component[label][1], "Dynamic ambience component, \"" + component_name + "\", can't have a \"" + label + "\" range with the same 2 values.");
	assertEx(component[label][0] >= 0.0 && component[label][1] >= 0.0, "Dynamic ambience component, \"" + component_name + "\", must have a \"" + label + "\" range values greater than zero.");
}
#/

/#
DAMBx_validate_damb_component(name, damb_name)
{
	component = DAMBx_get_component_preset(name);
	if (!IsDefined(component))
		return;
	// make sure the component was found
	assertEx(component.size > 0, "Dynamic ambience component, \"" + name + "\", from dynamic ambience preset, \"" + damb_name + "\", doesn't exist.");
	
	// check for existence of oneshots or loops
	if (!IsDefined(component["single_loops"]))
		assertEx(IsDefined(component["oneshots"]) || IsDefined(component["loops"]), "Dynamic ambience component, \"" + name + "\", needs either a \"oneshots\" or a \"loops\" list.");
	
	if (IsDefined(component["oneshots"]))
		DAMBx_validate_oneshots(component["oneshots"], name);
	
	// commenting out for now (loop format changed since this was written, need to revisit)
	//if (IsDefined(component["loops"]))
		//DAMBx_validate_loops(component["loops"]);
	
	if (IsDefined(component["single_loops"]))
	{
		foreach (value in component["single_loops"])
			assertEx(IsString(value), "Dynamic ambience component, \"" + name + "\" has invalid \"single_loops\" definition.");
	}
	
	// validate the required component labels (for loops or oneshots)
	if (IsDefined(component["oneshots"]) || IsDefined(component["loops"]))
		DAMBx_validate_label(component, "radius", name);

	if (IsDefined(component["event_time"]))
		DAMBx_validate_label(component, "event_time", name);
	
	// validate the optional component labels
	if (IsDefined(component["first_event"]))
			DAMBx_validate_label(component, "first_event", name);
	
	if (IsDefined(component["pitch"]))
		DAMBx_validate_label(component, "pitch", name);
	
	if (IsDefined(component["cone"]))
		DAMBx_validate_label(component, "cone", name);
		
	if (IsDefined(component["travel_time"]))
	{
		DAMBx_validate_label(component, "travel_time", name);
		// if we have a travel_time, we need a delta
		assertEx(IsDefined(component["delta"]) || IsDefined(component["delta_angle"]), "Dynamic ambience component, \"" + name + "\", requires a \"delta\" range if there is a \"travel_time\" range defined.");
		if (IsDefined(component["delta"]))
			DAMBx_validate_label(component, "delta", name);
		else
			DAMBx_validate_label(component, "delta_angle", name);
	}
	
	if (IsDefined(component["pitch_time"]))
		DAMBx_validate_label(component, "pitch_time", name);
}
#/

/#
DAMBx_validate_damb_preset(damb)
{
	assert(IsDefined(damb));
	assert(IsDefined(damb["name"]));
	name = damb["name"];
	assertEx(IsDefined(damb["components"]), "Dynamic ambience preset \"" + name + "\" didn't contain a \"components\" label.");
	assertEx(damb["components"].size > 0, "Dynamic ambience preset \"" + name + "\" didn't contain a \"components\" elements.");
	
	// if the first element in a components list is a string, then it is a damb defined to be parallel
	if (IsString(damb["components"][0]))
	{	
		for (i = 0; i < damb["components"].size; i++)
		{
			DAMBx_validate_damb_component(damb["components"][i], name);
		}
	}
	else
	{
		assertEx(IsDefined(damb["event_time"]), "Dynamic ambience preset \"" + name + "\" requires an \"event_time\" tag if it is going to be used serially.");
		assertEx(IsArray(damb["event_time"]) && damb["event_time"].size == 2, "Dynamic ambience preset \"" + name + "\"'s component list's \"event_time\" tag is set up incorrectly.");
		
		if (IsDefined(damb["first_event"]))
			assertEx(IsArray(damb["first_event"]) && damb["first_event"].size == 2, "Dynamic ambience preset \"" + name + "\"'s component list's \"event_time\" tag is set up incorrectly.");
		
		assertEx(IsArray(damb["components"][0]), "Dynamic ambience preset \"" + name + "\"'s component list is set up incorrectly.");
		for (i = 0; i < damb["components"].size; i++)
		{
			assertEx(damb["components"][i].size == 2, "Dynamic ambience preset \"" + name + "\"'s component list is set up incorrectly.");
			assertEx(IsString(damb["components"][i][0]), "Dynamic ambience preset \"" + name + "\"'s component list is set up incorrectly.");
			DAMBx_validate_damb_component(damb["components"][i][0], name);
					
			assertEx(damb["components"][i][1] >= 0.0, "Dynamic ambience preset \"" + name + "\"'s component list containing random weights must have weights greater than zero.");
		}
	}
}
#/

increment_ref_count()
{
	level._audio.damb.entity_ref_count++;
	/#
	set_damb_entity_hud(level._audio.damb.entity_ref_count);
	#/
}

decrement_ref_count()
{
	level._audio.damb.entity_ref_count--;
	/#
	set_damb_entity_hud(level._audio.damb.entity_ref_count);
	#/
}
