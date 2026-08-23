#include maps\_utility_code;
#include maps\_utility;
#include common_scripts\utility;

// core audio logic file
#include maps\_audio;

// audio manager files
#include maps\_audio_dynamic_ambi;
#include maps\_audio_stream_manager;
#include maps\_audio_reverb;
#include maps\_audio_mix_manager;


/********************************************************************
	PUBLIC FUNCTIONS
********************************************************************/
AZM_init()
{
	// Create main data struct.
	if (!IsDefined(level._audio.zone_mgr))
	{
		level._audio.zone_mgr = SpawnStruct();
		level._audio.zone_mgr.current_zone = "";
		level._audio.zone_mgr.zones = [];
		
		// structures to support overriding preset values if zone hasn't been retrieved yet
		level._audio.zone_mgr.overrides = spawnstruct();
		level._audio.zone_mgr.overrides.samb = []; // key: zone_name, value: new_value
		level._audio.zone_mgr.overrides.damb = [];
		level._audio.zone_mgr.overrides.mix = [];
		level._audio.zone_mgr.overrides.rev = [];
		level._audio.zone_mgr.overrides.occ = [];
		
		level._audio.zone_mgr.use_string_table_presets = false;
		level._audio.zone_mgr.use_iw_presets = false;
	}
	
	// this is a flag used to indicate whether or not a particular 
	// level has defined their audio zones in the level file rather than the global preset file		
	if (!IsDefined(level._audio.use_level_audio_zones))
	{
		level._audio.level_audio_zones_function = undefined;
	}
}

AZM_use_string_table()
{
	level._audio.zone_mgr.use_string_table_presets = true;
	level._audio.zone_mgr.use_iw_presets = false;
}

AZM_use_iw_presets()
{
	level._audio.zone_mgr.use_iw_presets = true;
	level._audio.zone_mgr.use_string_table_presets = false;
}

AZM_start_zone(name, fade_, specops_player_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assertEx(IsString(name), "AZM_start_zone: name must be a string.");

/#
	if (IsDefined(specops_player_))
	{
		assert(specops_player_ == level.player);
	}
#/

	if (level._audio.zone_mgr.current_zone == name)
	{
		return;
	}
	else if (level._audio.zone_mgr.current_zone != "")
	{
		AZM_stop_zone(level._audio.zone_mgr.current_zone, fade_);
	}

	level._audio.zone_mgr.current_zone = name;
	
	assert(IsDefined(level._audio.zone_mgr.zones));
	if (IsDefined(level._audio.zone_mgr.zones[name]) && IsDefined(level._audio.zone_mgr.zones[name]["state"]) && level._audio.zone_mgr.zones[name]["state"] != "stopping")
	{
		aud_print_warning("ZONEM_start_zone(\"" + name + "\") being called even though audio zone, \"" + name + "\", is already started.");
		return;
	}
	
	fade = 2.0;
	if (IsDefined(fade_))
	{
		assertEx(fade_ >= 0.0, "ZONEM_start_zone: fade_ must be greater than zero.");
		fade = fade_;
	}
	
	if (!IsDefined(level._audio.zone_mgr.zones[name])) // if we were in "stopping" mode, the zone will already exist, so no need to reload it from the preset
	{
		zone = AZMx_load_zone(name);
		if (!IsDefined(zone))
			return;
		level._audio.zone_mgr.zones[name] = zone;
	}
	zone = level._audio.zone_mgr.zones[name];
	
	aud_print_zone("ZONE START: " + name);	
	
	// set the state to "playing"
	level._audio.zone_mgr.zones[name]["state"] = "playing";
	
	// grab the priority and interrupt fade
	priority = zone["priority"];
	interrupt_fade = zone["interrupt_fade"];
	
	// the "ambient track" is the audio zone name
	/#
	set_zone_hud(name);
	#/
	
	// now start everything up if it's been defined for the zone	
	if (IsDefined(zone["streamed_ambience"]))
	{
		if (zone["streamed_ambience"] != "none")
		{
			SM_start_preset(zone["streamed_ambience"], fade, priority, interrupt_fade);
		}
		else
		{
			SM_stop_ambience(fade);
		}
	}
	
	if (IsDefined(zone["dynamic_ambience"]))
	{
		
		if (zone["dynamic_ambience"] != "none")
		{
			/#
			set_damb_hud( zone["dynamic_ambience"] );
			set_damb_to_hud("","");
			set_damb_from_hud("","");
			#/
			DAMB_zone_start_preset(zone["dynamic_ambience"], 1.0);
		}
		else
		{
			/#
			set_damb_hud( "" );
			set_damb_to_hud("","");
			set_damb_from_hud("","");
			#/
			DAMB_stop_zone(1.0);
		}
	}

	if (IsDefined(zone["occlusion"]))
	{
		if (zone["occlusion"] != "none")
		{
			aud_set_occlusion(zone["occlusion"]);
		}
		else
		{
			aud_deactivate_occlusion();
		}
	}
	
	// apply the occlusion, reverb, and mix, which may or may not have values...
	if (IsDefined(zone["filter"]))
	{
		if (zone["filter"] != "none")
		{
			aud_set_filter(zone["filter"], 0);
			level.player SetEqLerp( 1, 0 );	
		}
		// if starting an occlusion preset FROm a zone start, then there should be no
		// lerping going on, and there should be only one eq... which is the main (in slot 1)
	}	
	
	if (IsDefined(zone["reverb"]))
	{
		if (zone["reverb"] != "none")
		{
			RVB_start_preset(zone["reverb"]);
		}
		else
		{
			RVB_deactive_reverb();
		}
	}
	
	if (IsDefined(zone["mix"]))
	{
		if (zone["mix"] != "none")
		{
			MM_start_zone_preset(zone["mix"]);
		}
		else
		{
			MM_clear_zone_mix(1.0);
		}
	}
}

// The following set of functions set the given preset name and immediately sets it if the current zone is the zone we're changing
// else if the zone hasn't been called yet, it adds the setting to a temp structure, which will be used whent he zone is first called
AZM_set_zone_streamed_ambience(zone_name, streamed_ambience, fade_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	success = AZMx_set_param_internal(zone_name, "streamed_ambience", streamed_ambience, ::AZMx_restart_stream, fade_);
	if (!success)
	{
		if (!IsDefined(streamed_ambience)) // need to stare as "none" because can't store undefined
			streamed_ambience = "none";
		level._audio.zone_mgr.overrides.samb[zone_name] = streamed_ambience;
	}
}

AZM_set_zone_dynamic_ambience(zone_name, dynamic_ambience, fade_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	if (!IsDefined(dynamic_ambience)) // need to stare as "none" because can't store undefined
		dynamic_ambience = "none";

	AZMx_set_param_internal(zone_name, "dynamic_ambience", dynamic_ambience, ::AZMx_restart_damb, fade_);
	level._audio.zone_mgr.overrides.damb[zone_name] = dynamic_ambience;
}

AZM_set_zone_reverb(zone_name, reverb_name, fade_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	if (!IsDefined(reverb_name)) // need to stare as "none" because can't store undefined
		reverb_name = "none";
	AZMx_set_param_internal(zone_name, "reverb", reverb_name, ::AZMx_restart_reverb, fade_);	
	level._audio.zone_mgr.overrides.rev[zone_name] = reverb_name;
}

AZM_set_zone_occlusion(zone_name, occlusion_name, fade_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/

	if (!IsDefined(occlusion_name)) // need to stare as "none" because can't store undefined
		occlusion_name = "none";
	AZMx_set_param_internal(zone_name, "occlusion", occlusion_name, ::AZMx_restart_occlusion, fade_);
	level._audio.zone_mgr.overrides.mix[occlusion_name] = occlusion_name;
}

AZM_set_zone_mix(zone_name, mix_name, fade_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	if (!IsDefined(mix_name)) // need to stare as "none" because can't store undefined
		mix_name = "none";

	AZMx_set_param_internal(zone_name, "mix", mix_name, ::AZMx_restart_mix, fade_);
	level._audio.zone_mgr.overrides.mix[mix_name] = mix_name;
}

// stops all zones
AZM_stop_zones(fade_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	fade = 1.0;
	if (IsDefined(fade_))
	{
		assertEx(fade_ >= 0.0, "ZONEM_stop_zone: fade_ must be greater or equal to zero.");
		fade = fade_;
	}
	
	aud_print_zone("ZONE STOP ALL"); 
		
	foreach (zone in level._audio.zone_mgr.zones)
	{
		assert(IsDefined(zone["name"]));
		AZM_stop_zone(zone["name"], fade, false); // false = don't print in this case
	}
}

// stops a particular zone
AZM_stop_zone(name, fade_, print_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	assertEx(IsString(name), "ZONEM_stop_zone: name must be a string.");

	// only stop the zone if it has already played	
	if (IsDefined(level._audio.zone_mgr.zones[name]) && IsDefined(level._audio.zone_mgr.zones[name]["state"]) && level._audio.zone_mgr.zones[name]["state"] != "stopping")
	{
		fade = 1.0;
		if (IsDefined(fade_))
		{
			assertEx(fade_ >= 0.0, "ZONEM_stop_zone: fade_ must be greater or equal to zero.");
			fade = fade_;
		}
		
		zone = level._audio.zone_mgr.zones[name];
		
		do_print = false;
		if (IsDefined(print_))
		{
			do_print = print_;
		}
		
		if (do_print)
		{
			aud_print_zone("ZONE STOP ZONE: " + name);
		}
		
		// "stopping" an audio zone currently only stops the streamed ambience and the dynamic ambience
		// it doesn't "stop" the reverb, the occlusion, or the mix, since it doesn't really make 
		// sense to stop those systems. 
		
		if (IsDefined(zone["streamed_ambience"]))
		{
			SM_stop_ambient_alias(zone["streamed_ambience"], fade);
		}
		
		if (IsDefined(zone["dynamic_ambience"]))
		{
			DAMB_zone_stop_preset(zone["dynamic_ambience"], fade);
		}
		
		level._audio.zone_mgr.zones[name]["state"] = "stopping"; // make sure that we don't try to stop WHILE we're already stopping
		
		thread AZMx_wait_till_fade_done_and_remove_zone(name, fade);
	}
}

AZM_get_current_zone()
{
 return level._audio.zone_mgr.current_zone;
}

AZM_set_current_zone(zone)
{
	assert(IsString(zone));
	level._audio.zone_mgr.current_zone = zone;
}

AZM_print_enter_blend(zone_from, zone_to, progress_)
{
}

AZM_print_exit_blend(zone_to)
{
	//aud_print_zone("ZONE ENTER: " + zone_to);
}

AZM_print_progress(progress)
{
	//aud_print_zone_small("ZONE PROGRESS: " + progress);
}

AZMx_load_zone(name)
{
	assert(IsDefined(name));
	if (IsDefined(level._audio.zone_mgr.zones[name]))
	{
		return;
	}
	if (!IsDefined(level._audio.zone_mgr.preset_cache))
		level._audio.zone_mgr.preset_cache = [];

	zone = [];

	if (IsDefined(level._audio.zone_mgr.preset_cache[name]))
	{
		zone = level._audio.zone_mgr.preset_cache[name];
	}
	else
	{
			zone = AZMx_get_preset_from_string_table(name, true);
	}
	
	if (!IsDefined(zone) || zone.size == 0)
	{
		/#
		aud_print_error("failed to load audio zone: " + name);
		#/
		return;
	}

	level._audio.zone_mgr.preset_cache[name] = zone;
	
	// instantiate the temp override values before validating
	assert(IsDefined(zone));
	recache = false;
		
	if (IsDefined(level._audio.zone_mgr.overrides.samb[name]))
	{
		if (level._audio.zone_mgr.overrides.samb[name] == "none")
			zone["streamed_ambience"] = undefined;
		else
			zone["streamed_ambience"] = level._audio.zone_mgr.overrides.samb[name];

		recache = true;
		level._audio.zone_mgr.overrides.samb[name] = undefined;
	}
	
	if (IsDefined(level._audio.zone_mgr.overrides.damb[name]))
	{
		if (level._audio.zone_mgr.overrides.damb[name] == "none")
			zone["dynamic_ambience"] = undefined;
		else
			zone["dynamic_ambience"] = level._audio.zone_mgr.overrides.damb[name];

		recache = true;
		level._audio.zone_mgr.overrides.damb[name] = undefined;
	}
	
	if (IsDefined(level._audio.zone_mgr.overrides.rev[name]))
	{
		if (level._audio.zone_mgr.overrides.rev[name] == "none")
			zone["reverb"] = undefined;
		else
			zone["reverb"] = level._audio.zone_mgr.overrides.rev[name];

		recache = true;
		level._audio.zone_mgr.overrides.rev[name] = undefined;
	}
	
	if (IsDefined(level._audio.zone_mgr.overrides.occ[name]))
	{
		if (level._audio.zone_mgr.overrides.occ[name] == "none")
			zone["occlusion"] = undefined;
		else
			zone["occlusion"] = level._audio.zone_mgr.overrides.occ[name];
			
		recache = true;
		level._audio.zone_mgr.overrides.occ[name] = undefined;
	}
	
	if (IsDefined(level._audio.zone_mgr.overrides.mix[name]))
	{
		if (level._audio.zone_mgr.overrides.mix[name] == "none")
			zone["mix"] = undefined;
		else
			zone["mix"] = level._audio.zone_mgr.overrides.mix[name];
		
		recache = true;
		level._audio.zone_mgr.overrides.mix[name] = undefined;
	}
	
	// override the cache with the new overrides if needed so next time it's called, it uses the overrides
	if (recache)
	{
		level._audio.zone_mgr.preset_cache[name] = zone;
	}
	
	// note: zone may still not have any contents if it was just a label (i.e. this ok behavior)
	
	/#
	AZMx_validate_zone_preset(zone, name);
	#/
	
	// store the name with this zone
	zone["name"] = name;
	
	// grab the priority and interrupt fade if they've been defined
	if (!IsDefined(zone["priority"]))
	{
		zone["priority"] = 1;
	}
	
	if (!IsDefined(zone["interrupt_fade"]))
	{
		zone["interrupt_fade"] = 0.1;
	}

/*	
  // we decided to change the design for the mix preset, no longer does it assume a default mix 10/6/10
	if (!IsDefined(zone["mix"]))
	{
		zone["mix"] = "default";
	}
*/
	
	return zone;// was successful load
}

AZMx_get_preset_from_string_table(presetname, checklevel)
{
	assert(IsString(presetname));
	assert(IsDefined(checklevel));

	common_stringtable = "soundtables/common_zone.csv";	
	level_stringtable = maps\_audio::get_zone_stringtable();
	preset = [];
	
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	if (checklevel)
		preset = AZMx_get_zone_preset_from_stringtable_internal(level_stringtable, presetname);
	
	if (!IsDefined(preset) || preset.size == 0)
		preset = AZMx_get_zone_preset_from_stringtable_internal(common_stringtable, presetname);

	if (!IsDefined(preset) || preset.size == 0)
	{
		return;
	}	
	return preset;
}

AZMx_get_zone_preset_from_stringtable_internal(stringtable, presetname)
{
	assert(IsString(stringtable));
	assert(IsString(presetname));
	
	preset = [];
	paramname = "";
	value = "";

	numparams = 8;
	for( i = 1; i < numparams; i++)
	{
		if (paramname != "comments" && value != "")
			preset[paramname] = value;

		paramname = tablelookup(stringtable, 0, "zone_names", i);
		value = tablelookup(stringtable, 0, presetname, i);	
		
		if (paramname != "comment" && paramname != "comments" && value != "")
		{
			switch(paramname)
			{
				case "streamed_ambience":
				preset["streamed_ambience"] = value;
				break;
				
				case "dynamic_ambience":
				preset["dynamic_ambience"] = value;
				break;
				
				case "mix":
				preset["mix"] = value;
				break;
				
				case "reverb":
				preset["reverb"] = value;
				break;
				
				case "filter":
				preset["filter"] = value;
				break;
				
				case "occlusion":
				preset["occlusion"] = value;
				break;
				
				default:
				assertEx(false, "For audio zone preset stringtable, param name, \"" + paramname + "\", is unknown.");
				break;
			}
		}
	}
	
	return preset;
}


// function pointer
AZMx_restart_stream(zone_name, fade_)
{
	assert(IsDefined(zone_name));
	streamed_ambience = level._audio.zone_mgr.zones[zone_name]["streamed_ambience"];
	if (IsDefined(streamed_ambience))
		SM_start_preset(streamed_ambience, fade_);
	else
		SM_stop_ambience(fade_);
}

// function pointer
AZMx_restart_damb(zone_name, fade_)
{
	assert(IsDefined(zone_name));
	
	fade = 1.0;
	if (IsDefined(fade_))
		fade = fade_;
		
	dynamic_ambience = level._audio.zone_mgr.zones[zone_name]["dynamic_ambience"];
	if (IsDefined(dynamic_ambience))
	{
		DAMB_zone_start_preset(dynamic_ambience, fade);
	}
	else
	{
		// stops all dambs
		DAMB_zone_stop_preset(undefined, fade);
	}
}

// function pointer
AZMx_restart_reverb(zone_name, fade_)
{
	assert(IsDefined(zone_name));
	reverb = level._audio.zone_mgr.zones[zone_name]["reverb"];
	if (IsDefined(reverb))
		RVB_start_preset(reverb);
}

// function pointer
AZMx_restart_occlusion(zone_name, fade_)
{
	assert(IsDefined(zone_name));
	occlusion = level._audio.zone_mgr.zones[zone_name]["occlusion"];
	if (IsDefined(occlusion))
		aud_set_occlusion(occlusion);
}

// function pointer
AZMx_restart_mix(zone_name, fade_)
{
	assert(IsDefined(zone_name));
	mix = level._audio.zone_mgr.zones[zone_name]["mix"];
	if (IsDefined(mix))
		MM_start_preset(mix);
}

AZMx_set_param_internal(zone_name, param_name, param, function_pointer, fade_)
{
	assert(IsString(zone_name));
	assert(IsString(param_name));
	assert(IsString(param_name));
	assert(IsDefined(function_pointer));
	
	if (IsDefined(level._audio.zone_mgr.zones[zone_name]))
	{
		
		if ((IsDefined(level._audio.zone_mgr.zones[zone_name][param_name]) && level._audio.zone_mgr.zones[zone_name][param_name] != param) 
					|| (!IsDefined(level._audio.zone_mgr.zones[zone_name][param_name]) && param != "none"))
		{
			if (param == "none")
				level._audio.zone_mgr.zones[zone_name][param_name] = undefined;
			else
				level._audio.zone_mgr.zones[zone_name][param_name] = param; // store the name of the new streamed ambience in the zone	
			
			// restart!
			if (zone_name == AZM_get_current_zone())
			{
				[[ function_pointer ]](zone_name, fade_);
			}
		}
		return true; // we don't need to store the value
	}
	else // hasn't been run yet, so need to store it in the temporary array
	{
		return false;
	}	
}


AZMx_wait_till_fade_done_and_remove_zone(name, fade)
{
	assert(IsDefined(name));
	assert(IsDefined(fade));
	
	wait(fade);
	wait(0.05);
	assert(IsDefined(level._audio.zone_mgr.zones[name])); // nobody else but this function should be removing the levels
	
	// somebody might have tried to restart the zone during the fade-out
	if (level._audio.zone_mgr.zones[name]["state"] == "stopping")
	{
//		level._audio.zone_mgr.zones[name] = undefined; // remove
	}	
}


AZMx_get_blend_args(zone_from_name, zone_to_name)
{
	/*** INIT ARGS ***/
	args								= SpawnStruct();
	args.zone_from_name	= zone_from_name;
	args.zone_to_name		= zone_to_name;
	args.samb1_name			= undefined;
	args.samb2_name			= undefined;	
	args.damb1_name			= undefined;
	args.damb2_name			= undefined;	
	args.occlusion1			= undefined;
	args.occlusion2			= undefined;
	args.filter1				= undefined;
	args.filter2				= undefined;
	args.reverb1				= undefined;
	args.reverb2				= undefined;
	args.mix1_name			= undefined;
	args.mix2_name			= undefined;
	
	// the current zone (which should be "from")
	
	if (!IsDefined(level._audio.zone_mgr.zones[zone_from_name]))
	{
		zone = AZMx_load_zone(zone_from_name);
		if (!IsDefined(zone))
		{
			aud_print_warning("Couldn't find zone: " + zone_from_name );
			return; // failed to load
		}
		level._audio.zone_mgr.zones[zone_from_name] = zone;
	}
	current_zone = level._audio.zone_mgr.zones[zone_from_name];

	if (!IsDefined(level._audio.zone_mgr.zones[zone_to_name]))
	{
		zone = AZMx_load_zone(zone_to_name);
		if (!IsDefined(zone)) 
		{
			aud_print_warning("Couldn't find zone: " + zone_to_name );
			return; // failed to load zone
		}
		level._audio.zone_mgr.zones[zone_to_name] = zone;
	}	
	destination_zone = level._audio.zone_mgr.zones[zone_to_name];
		
	/*** STORE THE OCCLUSION, REVERB, and MIX ***/
	args.occlusion1			= current_zone["occlusion"];
	args.occlusion2			= destination_zone["occlusion"];
	args.filter1				= current_zone["filter"];
	args.filter2 				= destination_zone["filter"];
	args.reverb1				= current_zone["reverb"];
	args.reverb2				= destination_zone["reverb"];
	args.mix1						= current_zone["mix"];
	args.mix2						= destination_zone["mix"];
	
	/*** SET UP STREAMED AMBI ARGS ***/
	args.samb1_name = current_zone["streamed_ambience"];
	args.samb2_name = destination_zone["streamed_ambience"];
	
	
	/*** SET UP DYNAMIC AMBI ARGS ***/

	num_damb_playing = level._audio.damb.playing["zone"].size;
	// make sure we only have 1 dyn ambi playing before blending

	// stop existing zone dambs
	if (num_damb_playing != 1)
	{
		DAMB_stop(1.0, "zone");
	}
	
	if (num_damb_playing == 1)
	{
		foreach(key, val in level._audio.damb.playing["zone"])
		{
			args.damb1_name = key; // damb name
			break;
		}
		/#
		if (IsDefined(current_zone["dynamic_ambience"]))
		{
			if (args.damb1_name != current_zone["dynamic_ambience"])
			{
				aud_print_warning("Blending from a dynamic ambience (" + args.damb1_name + ") which isn't the current zone's (" + current_zone["dynamic_ambience"] + ").");
			}
		}
		#/
	}
		
	args.damb2_name = destination_zone["dynamic_ambience"];
	
	return args;
}

/************************************************************************************************
	Filters out cases where we DO NOT want to change or xfade the ambis at all:
	1) The "to" ambi is undefined.
	2) The "from" ambi is already playing, and is the same ambi as the "to" ambi.
************************************************************************************************/	

AZMx_is_valid_damb_blend_request(amb1_name, amb2_name)
{
	result = false;
	if (IsDefined(amb1_name) && IsDefined(amb2_name) && amb1_name != amb2_name)
	{
		result = true;
	}
	else if ((IsDefined(amb2_name) && !IsDefined(amb1_name))) // if to is defined, but from is not
	{
		result = true;
	}
	else if ((IsDefined(amb1_name) && !IsDefined(amb2_name))) // this is ok for dambs
	{
		result = true;
	}
	return result;
}

AZMx_is_valid_samb_blend_request(amb1_name, amb2_name)
{
	result = false;
	if (IsDefined(amb1_name) && IsDefined(amb2_name) && amb1_name != amb2_name)
	{
		result = true;
	}
	else if ((IsDefined(amb2_name) && !IsDefined(amb1_name))) // if to is defined, but from is not
	{
		result = true;
	}
	return result;
}

AZMx_blend_zones(level_1, level_2, args)
{	
	/#
	if (aud_check_fastfiles()) return;
	#/
	assert(IsDefined(level_1));
	assert(IsDefined(level_2));
	assert(IsDefined(args));
	
	if	(AZMx_is_valid_samb_blend_request(args.samb1_name, args.samb2_name))
	{
		aliasInfo = [];
		index = 0;
					
		// Only fade the "from" ambi if it's already playing (don't start/fade it if it's not already playing).
		if (IsDefined(args.samb1_name) && args.samb1_name != "") 
		{
			zone1 = level._audio.zone_mgr.zones[args.zone_from_name];
			
			assert(IsDefined(zone1));
			
			aliasInfo[index] = SpawnStruct();
			aliasInfo[index].alias = args.samb1_name;
			aliasInfo[index].vol = level_1;
			aliasInfo[index].fade = zone1["interrupt_fade"];
			aliasInfo[index].priority = zone1["priority"];
			index++;
		}

		// Always blend the "to" ambi if it is defined.
		if (isdefined(args.samb2_name) && args.samb2_name != "")
		{
			zone2 = level._audio.zone_mgr.zones[args.zone_to_name];
			assert(IsDefined(zone2));
			
			aliasInfo[index] = SpawnStruct();
			aliasInfo[index].alias = args.samb2_name;
			aliasInfo[index].vol = level_2;
			aliasInfo[index].fade = zone2["interrupt_fade"];
			aliasInfo[index].priority = zone2["priority"];
		}

		if (aliasInfo.size > 0)
		{
			SM_mix_ambience(aliasInfo);
		}
	}

	if ( AZMx_is_valid_damb_blend_request(args.damb1_name, args.damb2_name) )
	{
		DAMB_prob_mix_damb_presets(args.damb1_name, level_1, args.damb2_name, level_2);
	}
	
	has_filter = false;
	
	// Store eq in slots 0 and 1.
	if (aud_is_zone_filter_enabled())
	{
		if (Isdefined(args.filter1))  // the "from" is the "main" eq
		{
			has_filter = true;
			aud_set_filter(args.filter1, 0, false);
			/#
			set_filter_from_hud(args.filter1, level_1);
			#/
		}
		else
		{
			aud_set_filter(undefined, 0, false);
			/#
			set_filter_from_hud("", "");
			#/
		}
		
		if (IsDefined(args.filter2))  // the "to" is the "mix" eq
		{
			has_filter = true;
			aud_set_filter(args.filter2, 1, false);
			/#
			set_filter_to_hud(args.filter2, level_2);
			#/
		}
		else
		{
			aud_set_filter(undefined, 1, false);
			/#
			set_filter_to_hud("", "");
			#/
		}
		
		// RAVEN jsypult: we still want to keep track of zone filtering/occlusion transitions internally
		// if zone filtering/occlusion is not disabled, set the EQ Lerp
		if (!(IsDefined(level._audio.zone_occlusion_and_filtering_disabled) && level._audio.zone_occlusion_and_filtering_disabled))
		{
			if (IsDefined(args.filter1) || IsDefined(args.filter2))
			{
				// Blend between eq slot 0 and 1 with a value between 0 and 1.0,
				// Here, level_1 progresses from 1.0 to 0, and level_2 progresses from 0 to 1.0.
				level.player SetEqLerp(level_1, 0);
			}
		}
	}

/#
	if (!aud_is_zone_filter_enabled())
	{
		set_filter_hud("disabled");
	}
	else if (has_filter)
	{
		set_filter_hud("blending");
	}
#/

	if (level_1 >= 0.75)
	{
		if(IsDefined(args.reverb1))
		{
			if (args.reverb1 == "none")
				RVB_start_preset(undefined);
			else
				RVB_start_preset(args.reverb1);
		}
	
		if (IsDefined(args.mix1))
		{
			if (args.mix1 == "none")
				MM_clear_zone_mix(2.0);
			else
				MM_start_zone_preset(args.mix1); // modify only the zone submix
		}
		
		if (aud_is_zone_filter_enabled())
		{
			if (IsDefined(args.occlusion1))
			{
				if (args.occlusion1 == "none")
					aud_deactivate_occlusion();
				else
					aud_set_occlusion(args.occlusion1);
			}
		}
		// set occlusion 1 here
	}
	else if (level_2 >= 0.75)
	{
		if(IsDefined(args.reverb2))
		{
			if (args.reverb2 == "none")
				RVB_start_preset(undefined);
			else
				RVB_start_preset(args.reverb2);
		}

		if (IsDefined(args.mix2))
		{
			if (args.mix2 == "none")
				MM_clear_zone_mix(2.0);
			else
				MM_start_zone_preset(args.mix2); // modify only the zone submix
		}
		
		if (aud_is_zone_filter_enabled())
		{
			if (IsDefined(args.occlusion2))
			{
				if (args.occlusion2 == "none")
					aud_deactivate_occlusion();
				else
					aud_set_occlusion(args.occlusion2);
			}
		}
	}
}

/#
AZMx_validate_string_param(zone, param_name, name)
{
	if (IsDefined(zone[param_name]))
	{
		assertEx(IsString(zone[param_name]), "ZONE preset, \"" + name + "\", must have a string-valued " + param_name + " preset.");
	}
}
#/

/#
AZMx_validate_zone_preset(zone, name)
{
	assert(IsDefined(zone));
	assert(IsDefined(name));
	if (zone.size == 0)
	{
		return; // nothing was specified in this zone, so nothing to validate
	}
	
	// NOTE: the validations performed here just make sure that the zone preset manager is filled out correctly. The
	// various managers do their own validation to ensure that they are themselves existent and set up correctly...
	if (IsDefined(zone["priority"]))
	{
		assertEx(zone["priority"] >= 0.0, "ZONE preset, \"" + name + "\", must have a priority greater than zero.");
	}
	
	if (IsDefined(zone["interrupt_fade"]))
	{
		assertEx(zone["interrupt_fade"] >= 0.0, "ZONE preset, \"" + name + "\", must have an interrupt fade greater than zero.");
	}
	AZMx_validate_string_param(zone, "streamed_ambience", name);
	AZMx_validate_string_param(zone, "dynamic_ambience", name);
	AZMx_validate_string_param(zone, "reverb", name);
	AZMx_validate_string_param(zone, "occlusion", name);
	AZMx_validate_string_param(zone, "mix", name);
}
#/
