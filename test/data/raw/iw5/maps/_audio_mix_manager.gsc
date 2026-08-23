#include maps\_audio;


// ------------------------------------------------------------------------------
// PUBLIC FUNCTIONS - functions intended to be used outside of this file by users
// ------------------------------------------------------------------------------

/*
///ScriptDocBegin
"Name: MM_init()"
"Summary: Inits Mix Utilities."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: none."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_init()
{
	// this allows arbitrary ordering of initializing audio sub-utilities
	if (!IsDefined(level._audio))
	{
		level._audio = SpawnStruct();	
	}	
	if (!IsDefined(level._audio.mix))
	{
		level._audio.mix = SpawnStruct();	
	}
	
	MMx_init_volmods();
	
	// some useful mix utility flags
	/#
	level._audio.mix.print_mix_error_messages = true;	
	level._audio.mix.assert_if_setting_mix_too_often = true;
	#/
	
	level._audio.mix.use_string_table_presets = false;
	level._audio.mix.use_iw_presets = false;
	level._audio.mix.blending = false; // if we are performing a mix blend, then we can't apply submixes or mixes until MM_reset_blend is called.	
	level._audio.mix.debug_mix_mode = false;
	
	// data for server message throttling
	max_messages = 10; // max number of messages to send at a time
	thread MMx_mix_server_throttler(max_messages);  
	thread MMx_volmod_server_throttler(max_messages);
	/# 					
	level._audio.mix.min_mix_time = 50; // ms
	#/
	
	// the most recently applied mix or submix name
	level._audio.mix.curr_preset = "";
	level._audio.mix.prev_preset = "";
			
	// these submixes won't get cleared
	level._audio.mix.sticky_submixes = [];
	
	// create a default volmod submix based on the file.
	if (!IsDefined(level._audio.volmod_submixes))
		level._audio.volmod_submixes = [];
	
	level._audio.mix.volmod_submixblends = [];
	
	// cache of mix presets
	level._audio.mix.preset_cache = [];

	// array of changed presets *this* frame. Used to optimize preset updating
	level._audio.mix.changed_presets = [];
	
	// setup headroom data
	level._audio.mix.headroom = 0.85; // default headroom set to 1.0 by default
	
	/#
	headroom_dvar = aud_get_headroom_dvar();
	if (headroom_dvar > 0 && headroom_dvar <= 100)
	{
		headroom_dvar = headroom_dvar/100;
		level._audio.mix.headroom = headroom_dvar;
	}
	#/
/*
	preset = MMx_get_mix_preset("headroom"); // the default headroom preset
	if (IsDefined(preset))
	{
		level._audio.mix.headroom_preset = preset; // the default headroom preset
	}
*/				
	// mix blending functionality support
	level._audio.mix.blend_value = 0;
	level._audio.mix.blend_name = "";

	// defered mix update thread, forces updates to happen at most once per frame
	thread MMx_update_mix_thread();
	
	// wait till everything is set up, then apply the first mix
	waittillframeend; 													
	
	thread MMx_apply_initial_mix();	
}


/*
///ScriptDocBegin
"Name: MM_precache_preset(<preset_name>)"
"Summary: Caches the indicated mix preset."
"Module: Audio"
"CallOn: Nothing"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_precache_preset(preset_name)
{
	MMx_get_mix_preset(preset_name);
}


MM_set_headroom_mix(preset_name, headroom_value, fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	assert(IsDefined(preset_name));
	assert(IsDefined(headroom_value));
	
	assert(IsDefined(level._audio.mix.debug_mix_mode));
	if (!level._audio.mix.debug_mix_mode)
	{
		fade_time = 1.0;
		if (IsDefined(fade_time_))
			fade_time = fade_time_;
		
		level._audio.mix.headroom = headroom_value;
		
		preset = MMx_get_mix_preset(preset_name);
		if (IsDefined(preset))
		{
			level._audio.mix.headroom_preset = preset;
			MMx_update_mix(fade_time, preset_name);
		}
	}
}

MM_enabled_debug_mode()
{
	level._audio.mix.debug_mix_mode = true;
}

MM_disable_debug_mode()
{
	level._audio.mix.debug_mix_mode = false;
}

MM_use_string_table()
{
	level._audio.mix.use_string_table_presets = true;
	level._audio.mix.use_iw_presets = false;
}


/*
///ScriptDocBegin
"Name: MM_start_preset(preset_name, fade)"
"Summary: Starts a named mix preset. This will clear any submixes, and result in only the given mix name."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <preset_name> : A valid preset name."
"OptionalArg: <fade> : fade time in seconds."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_start_preset(preset_name, fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/

	assert(IsString(preset_name) && preset_name != "");	
	
	assert(IsDefined(level._audio.mix.debug_mix_mode));
	if (!level._audio.mix.debug_mix_mode && !level._audio.mix.blending)
	{
		assert(IsString(preset_name));	
		assert(IsDefined(level._audio.mix.curr_preset));
		
		// don't apply the same mix preset name twice
		if (preset_name != level._audio.mix.curr_preset)
		{		
			MMx_clear_submixes(false);
			MMx_set_mix(preset_name, fade_time_);
		}
	}
}


MM_start_zone_preset(preset_name)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsDefined(level._audio.mix.debug_mix_mode));
	if (!level._audio.mix.debug_mix_mode && !level._audio.mix.blending)
	{
		assert(IsString(preset_name));
		preset = MMx_get_mix_preset(preset_name);
		if (!IsDefined(preset))
		{
			/#
			set_mix_hud("undefined");
			#/
			return;
		}

		// set existing zone_mix values to 1.0 (to clear them)
		if (IsDefined(level._audio.mix.volmod_submixes["zone_mix"]))
		{
			foreach(channel_name, value in level._audio.mix.volmod_submixes["zone_mix"])
			{
				if (channel_name != "fade_time" && channel_name != "preset_name")
				{
					level._audio.mix.volmod_submixes["zone_mix"][channel_name].current_volume = 1.0;
				}
			}
		}
		else
		{
			level._audio.mix.volmod_submixes["zone_mix"] = [];
		}

		// create or override volmod names for the new mix
		level._audio.mix.volmod_submixes["zone_mix"]["preset_name"] = preset_name; // store preset name for debug info
		foreach(channel_name, value in preset)
		{
			if (channel_name != "fade_time" && channel_name != "name")
			{
				level._audio.mix.volmod_submixes["zone_mix"][channel_name] = SpawnStruct();
				level._audio.mix.volmod_submixes["zone_mix"][channel_name].current_volume = value;
				level._audio.mix.volmod_submixes["zone_mix"][channel_name].original_volume = value;
			}
		}

		/#
		set_mix_hud(preset_name);
		#/

		fade = 1.0;
		if (IsDefined(preset["fade_time"]))
		{
			fade = preset["fade_time"];
		}
		MMx_update_mix(fade, "zone_mix");
	}
}

MM_clear_zone_mix(fade_)
{
	/#
	set_mix_hud("");
	#/
	
	fade = 1.0;
	if (IsDefined(fade_))
	{
		fade = fade_;
	}
	if (IsDefined(level._audio.mix.volmod_submixes["zone_mix"]))
	{
		level._audio.mix.volmod_submixes["zone_mix"]["CLEAR"] = true;
		MMx_update_mix(fade, "zone_mix");
	}
}



/*
///ScriptDocBegin
"Name: MM_clear_submixes()"
"Summary: Clears all added submixes."
"Module: Audio"
"CallOn: Nothing"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_clear_submixes(fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	MMx_clear_submixes(true, fade_time_);
}

/*
///ScriptDocBegin
"Name: MM_make_submix_sticky(preset_name)"
"Summary: Makes the given submix preset name unclearable (i.e. sticky)."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <preset_name> : The name of the submix to make sticky."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_make_submix_sticky(preset_name)
{
	level._audio.mix.sticky_submixes[preset_name] = true;
}

/*
///ScriptDocBegin
"Name: MM_make_submix_unsticky(preset_name)"
"Summary: Makes the given submix preset name clearable (i.e. unsticky)."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <preset_name> : The name of the submix to make unsticky."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_make_submix_unsticky(preset_name)
{
	level._audio.mix.sticky_submixes[preset_name] = undefined;
}

/*
///ScriptDocBegin
"Name: MM_add_submix(preset_name, fade, initial_volume_scale)"
"Summary: Adds the given submix to the submix chain."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <preset_name> : The name of the submix to add."
"OptionalArg: <fade> : A fade time (in seconds)."
"OptionalArg: <initial_volume_scale> : An initial volume scale."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_add_submix(preset_name, fade_time_, initial_volume_scale_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsDefined(level._audio.mix.debug_mix_mode));
	if (!level._audio.mix.debug_mix_mode  && !level._audio.mix.blending)
	{
		assert(IsString(preset_name));
		MMx_set_mix(preset_name, fade_time_, initial_volume_scale_);
	}
}

// blends toward the given submix name from a virtual submix of all 1.0
MM_add_submix_blend_to(preset_name, label, blendvalue_, fadetime_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsString(preset_name));
	assert(IsString(label));
	
	if (!IsDefined(level._audio.mix.volmod_submixblends[label]))
	{
		submixblend = MMx_create_submix_blend(undefined, preset_name, blendvalue_);
		if (!IsDefined(submixblend))
		{
			/#
			aud_print_error("Failed to add a submix \"blend_to\", " + preset_name + " with label: " + label);
			#/
			return;
		}
		
		level._audio.mix.volmod_submixblends[label] = submixblend;
		MMx_update_mix(fadetime_, preset_name);
	}
}

/*
///ScriptDocBegin
"Name: MM_add_submix_blend(<preset_name_A>, <preset_name_B>, <label>, [blendvalue], [fade_time])"
"Summary: Creates a special submix blend that creates an aggregate submix interpolated between preset_name_A and preset_name_B."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <preset_name_A> : The name of a mix preset for the first half of the submix blend."
"MandatoryArg: <preset_name_B> : The name of a mix preset for the second half of the submix blend."
"MandatoryArg: <label> : A unique label for the submix blend for this particular submix blend."
"OptionalArg: [blendvalue] : An initial blend value, between 0 and 1. Defaults to 0."
"OptionalArg: [fade] : A fade time (in seconds). Defaults to 1.0."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_add_submix_blend(preset_name_A, preset_name_B, label, blendvalue_, fadetime_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsString(preset_name_A));
	assert(IsString(preset_name_B));
	assert(IsString(label));
	
	if (!IsDefined(level._audio.mix.volmod_submixblends[label]))
	{
		submixblend = MMx_create_submix_blend(preset_name_A, preset_name_B, blendvalue_);
		if (!IsDefined(submixblend))
		{
			/#
			aud_print_error("Failed to add a submix \"blend\", from " + preset_name_A + " to " + preset_name_B + " with label: " + label);
			#/
			return;
		}
				
		level._audio.mix.volmod_submixblends[label] = submixblend;
		
		MMx_update_mix(fadetime_, label);
	}
}

/*
///ScriptDocBegin
"Name: MM_set_submix_blend_value(<label>, <blendvalue>, [fade_time])"
"Summary: Sets the blend value (interpolation amount) for the labeled submix blend."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <label> : The label of the submix_blend to set the blend value for."
"MandatoryArg: <blendvalue> : The blend value to set for the labeled submix blend."
"OptionalArg: [fade] : A fade time (in seconds). Defaults to 1.0."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_set_submix_blend_value(label, blendvalue, fadetime_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsString(label));
	assert(IsDefined(blendvalue));
	
	if (IsDefined(level._audio.mix.volmod_submixblends[label]))
	{
		assert(IsDefined(level._audio.mix.volmod_submixblends[label].blendvalue));
		level._audio.mix.volmod_submixblends[label].blendvalue = clamp(blendvalue, 0, 1);
		MMx_update_mix(fadetime_, label);
	}
}


/*
///ScriptDocBegin
"Name: MM_clear_submix_blend(<label>, [fade_time])"
"Summary: Clears the labeled submix blend."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <label> : The label of the submix_blend to clear."
"OptionalArg: [fade] : A fade time (in seconds). Defaults to 1.0"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_clear_submix_blend(label, fadetime_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsString(label));
	
	if (IsDefined(level._audio.mix.volmod_submixblends[label]))
	{
		level._audio.mix.volmod_submixblends[label].clear = true;
		MMx_update_mix(fadetime_, label);
	}
}

/*
///ScriptDocBegin
"Name: MM_scale_submix(<preset_name>, <volume_scale>, [fade])"
"Summary: Scales the volume settings of the given applied submix. If submix hasn't already been added, it will first add it."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <preset_name> : The name of the submix to scale."
"MandatoryArg: <volume_scale> : The volume scale."
"OptionalArg: [fade] : A fade time (in seconds). Defaults to 1.0"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_scale_submix(preset_name, volume_scale, fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	assert(IsDefined(level._audio.mix.debug_mix_mode));
	if (!level._audio.mix.debug_mix_mode && !level._audio.mix.blending)
	{
		assert(IsString(preset_name));
		assert(IsDefined(volume_scale));
		assert(IsDefined(level._audio.mix.volmod_submixes));
		
		if (IsDefined(level._audio.mix.volmod_submixes[preset_name]))
		{
			MMx_scale_submix(preset_name, volume_scale);
		}
		else // doesn't already exist, so need to make it, with the default volume_scale
		{
			MMx_make_new_submix(preset_name, volume_scale);
		}	
		MMx_update_mix(fade_time_, preset_name);
	}
}

/*
///ScriptDocBegin
"Name: MM_restore_submix(<preset_name>, [fade])"
"Summary: Restores the given submix to it's original preset values."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <preset_name> : The submix name to restore."
"OptionalArg: [fade] : A fade time (in seconds). Default is 1.0."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_restore_submix(preset_name, fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsDefined(level._audio.mix.debug_mix_mode));
	if (!level._audio.mix.debug_mix_mode && !level._audio.mix.blending)
	{
		assert(IsString(preset_name));
		assert(IsDefined(level._audio.mix.volmod_submixes));
		
		if (IsDefined(level._audio.mix.volmod_submixes[preset_name]))
		{
			level._audio.mix.volmod_submixes[preset_name].current_volume = level._audio.mix.volmod_submixes[preset_name].original_volume;
			MMx_update_mix(fade_time_, preset_name);
		}
	}
}

/*
///ScriptDocBegin
"Name: MM_clear_submix(<preset_name>, [fade])"
"Summary: Clears the given submix preset from the submix chain."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <preset_name> : The submix name to clear."
"OptionalArg: [fade] : A fade time (in seconds). Default is 1.0"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_clear_submix(preset_name, fade_time_)
{	
	/#
	if (aud_check_fastfiles()) return;
	#/
	assert(IsDefined(level._audio.mix.debug_mix_mode));
	if (!level._audio.mix.debug_mix_mode && !level._audio.mix.blending)
	{
		assert(IsString(preset_name));
		if(preset_name == "default")
			return;
		
		assert(IsDefined(level._audio.mix.volmod_submixes));
		
		if (!IsDefined(level._audio.mix.sticky_submixes[preset_name]) && IsDefined(level._audio.mix.volmod_submixes[preset_name]))
		{
			level._audio.mix.volmod_submixes[preset_name]["CLEAR"] = true; 
			MMx_update_mix(fade_time_, preset_name);
		}
	}
}


/*
///ScriptDocBegin
"Name: MM_get_applied_preset_name()"
"Summary: Returns active mix name."
"Module: Audio"
"CallOn: Nothing"
"Returns: Name of currently applied mix preset."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_get_applied_preset_name()
{
	return level._audio.mix.curr_preset;
}


/*
///ScriptDocBegin
"Name: MM_add_dynamic_volmod_submix(<submixname>, <channels>, [fade])"
"Summary: Sets the volume of the array of volmod groups with the given fade_time. This function allows on-the-fly submixes that don't need to be defined in a mix preset."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <submixname> : name of the submix, used when clearing this submix."
"MandatoryArg: <channels> : An array of mixchannelname-volume pairs. e.g. ["music", 0.3, "voice", 0.5, "weapons", 0.3]"
"OptionalArg: [fade] : A fade time for the submix (in seconds). defaults to 1.0"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_add_dynamic_volmod_submix(submixname, channels, fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	assert(IsDefined(level._audio.mix.debug_mix_mode));
	if (!level._audio.mix.debug_mix_mode)
	{
		assertEx(IsString(submixname), "MM_add_dynamic_submix: must give a submixname.");
		assertEx(IsArray(channels), "MM_add_dynamic_submix: must give an array of channelnames-volume pairs.");
		// assert size is even
		assertEx(aud_is_even(channels.size), "MM_add_dynamic_submix: must give array of channelnames-volume pairs.");

		if (IsDefined(level._audio.mix.volmod_submixes[submixname]))
		{
			/#
			aud_print_error("Trying to add a dynamic volmod submix with a name that already is being used by a volmod submix.");
			#/
			return;
		}
		
		assert(!IsDefined(level._audio.mix.volmod_submixes[submixname]));
		level._audio.mix.volmod_submixes[submixname] = [];
		
		count = 0;
		channel_name = undefined;
		foreach(value in channels)
		{
			if (aud_is_even(count))
			{
				assert(!IsDefined(channel_name));
				assertEx(IsString(value), "MM_add_dynamic_submix: must give array of channelnames-volume pairs. " + value + " is an invalid channel name.");
				channel_name = value;
			}
			else
			{
				assert(IsDefined(channel_name));
				if (!MMx_is_volmod_channel(channel_name))
				{
					level._audio.mix.volmod_submixes[submixname] = undefined;
					/#
					aud_print_error("Trying to add a dynamic volmod submix with a volmod that isn't defined: " + channel_name);
					#/
					return;
				}
				level._audio.mix.volmod_submixes[submixname][channel_name] = spawnstruct();
				level._audio.mix.volmod_submixes[submixname][channel_name].current_volume = value;
				level._audio.mix.volmod_submixes[submixname][channel_name].original_volume = value;
				channel_name = undefined;
			}
			count++;
		}
		MMx_update_mix(fade_time_, submixname);
	}
}


/*
///ScriptDocBegin
"Name: MM_add_dynamic_submix(<submixname>, <channels>, [fade])"
"Summary: Sets the volume of the array of mix channels with the given fade_time. This function allows on-the-fly submixes that don't need to be defined in a mix preset."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <submixname> : name of the submix, used when clearing this submix."
"MandatoryArg: <channels> : An array of mixchannelname-volume pairs. e.g. ["music", 0.3, "voice", 0.5, "weapons", 0.3]"
"OptionalArg: [fade] : A fade time for the submix (in seconds). defaults to 1.0"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_add_dynamic_submix(submixname, volmods, fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	assert(IsDefined(level._audio.mix.debug_mix_mode));
	if (!level._audio.mix.debug_mix_mode)
	{
		assertEx(IsString(submixname), "MM_add_dynamic_submix: must give a submixname.");
		assertEx(IsArray(volmods), "MM_add_dynamic_submix: must give an array of volmodname-volume pairs.");
		assertEx(aud_is_even(volmods.size), "MM_add_dynamic_submix: must give array of volmodname-volume pairs.");
		
		assert(!IsDefined(level._audio.mix.volmod_submixes[submixname]));
		level._audio.mix.volmod_submixes[submixname] = [];
		
		count = 0;
		channel_name = undefined;
		foreach(volmod in volmods)
		{
			if (aud_is_even(count))
			{
				assert(!IsDefined(channel_name));
				assertEx(IsString(volmod), "MM_add_dynamic_submix: must give array of volmod-volume pairs. " + volmod + " is an invalid volmod name.");
				channel_name = volmod;
			}
			else
			{
				assert(IsDefined(channel_name));
				level._audio.mix.volmod_submixes[submixname][channel_name] = spawnstruct();
				level._audio.mix.volmod_submixes[submixname][channel_name].current_volume = volmod;
				level._audio.mix.volmod_submixes[submixname][channel_name].original_volume = volmod;
				channel_name = undefined;
			}
			count++;
		}
		MMx_update_mix(fade_time_, submixname);
	}
}

/*
///ScriptDocBegin
"Name: MM_does_submix_exist(<submixname>)"
"Summary: Returns true if VOLMOD submix exists; otherwise, returns false."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <submixname> : Name of a submix."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_does_volmod_submix_exist(submixname)
{
	return IsDefined(level._audio.mix.volmod_submixes[submixname]);
}

/*
///ScriptDocBegin
"Name: MM_mute_volmods(<volmods>, [fade])"
"Summary: Mutes the array of volmod groups with the given fade_time."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <volmods> : A valid array of volmod groups to mute."
"OptionalArg: [fade] : A fade time for the mute (in seconds). Default 1.0"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_mute_volmods(channels, fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	assert(IsDefined(level._audio.mix.debug_mix_mode));
	if (!level._audio.mix.debug_mix_mode)
	{			
		// make (or clear) special mix manager mute submix
		level._audio.mix.volmod_submixes["mm_mute"] = [];
		
		// mute the one channel
		if (IsString(channels))
		{
			if (!IsDefined(level._audio.mix.volmod_submixes["mm_mute"][channels]))
			{
				level._audio.mix.volmod_submixes["mm_mute"][channels] = spawnstruct();
			}
				
			level._audio.mix.volmod_submixes["mm_mute"][channels].current_volume = 0.0;
			level._audio.mix.volmod_submixes["mm_mute"][channels].original_volume = 1.0;
		}
		else
		{			
			assert(IsArray(channels));
			// turn back on the channels in the input channels array
			foreach(channel in channels)
			{
				if (!IsDefined(level._audio.mix.volmod_submixes["mm_mute"][channel]))
				{
					level._audio.mix.volmod_submixes["mm_mute"][channel] = spawnstruct();
				}
				level._audio.mix.volmod_submixes["mm_mute"][channel].current_volume = 0.0;
				level._audio.mix.volmod_submixes["mm_mute"][channel].original_volume = 1.0;
			}
		}
		MMx_update_mix(fade_time_, "mm_mute");
	}
}


/*
///ScriptDocBegin
"Name: MM_clear_volmod_mute_mix([fade])"
"Summary: Clears the mute volmod submix."
"Module: Audio"
"CallOn: Nothing"
"OptionalArg: [fade] : A fade time for the mute (in seconds). Default 1.0"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_clear_volmod_mute_mix(fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	if (IsDefined(level._audio.volmod_submixes["mm_mute"]))
	{
		level._audio.volmod_submixes["mm_mute"] = undefined;
		MMx_update_mix(fade_time_, "mm_mute");
	}
}

/*
///ScriptDocBegin
"Name: MM_solo_volmods(<volmods>, [fade])"
"Summary: Solos the array of volmod groups with the given fade_time."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <volmods> : A valid array of mix channels to solo."
"OptionalArg: [fade] : A fade time for the solo (in seconds). Defaults to 1.0"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_solo_volmods(channels, fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	assert(IsDefined(level._audio.mix.debug_mix_mode));
	if (!level._audio.mix.debug_mix_mode)
	{
		// make (or clear) special mix manager solo submix;
		level._audio.mix.volmod_submixes["mm_solo"] = [];
		
		// mute all channels in this submix
		foreach(channel_name, _ in level._audio.mix.volmod_vals)
		{
			level._audio.mix.volmod_submixes["mm_solo"][channel_name] = spawnstruct();
			level._audio.mix.volmod_submixes["mm_solo"][channel_name].current_volume = 0.0;
			level._audio.mix.volmod_submixes["mm_solo"][channel_name].original_volume = 1.0;
		}

		if (IsString(channels))
		{
			level._audio.mix.volmod_submixes["mm_solo"][channels].current_volume = 1.0;
		}
		else
		{
			assert(IsArray(channels));
			// turn back on the channels in the input channels array
			foreach(channel in channels)
			{
				level._audio.mix.volmod_submixes["mm_solo"][channel].current_volume = 1.0;
			}
		}
		MMx_update_mix(fade_time_, "mm_solo");
	}
}

/*
///ScriptDocBegin
"Name: MM_clear_solo_volmods([fade])"
"Summary: Clears the soloed array of volmod groups with the given fade_time."
"Module: Audio"
"CallOn: Nothing"
"OptionalArg: [fade] : A fade time for the solo (in seconds). Defaults to 1.0"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_clear_solo_volmods(fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	if (IsDefined(level._audio.mix.volmod_submixes["mm_solo"]))
	{
		level._audio.mix.volmod_submixes["mm_solo"] = undefined;
		MMx_update_mix(fade_time_, "mm_solo");
	}
}


/*
///ScriptDocBegin
"Name: MM_get_channel_names()"
"Summary: Returns the array of channel names."
"Module: Audio"
"CallOn: Nothing"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_get_channel_names()
{
	assert(IsDefined(level._audio) && IsDefined(level._audio.mix));
	return level._audio.mix.channel_names;
}


/*
///ScriptDocBegin
"Name: MM_get_num_volmod_submixes()"
"Summary: Returns the number of volmod submixes currently applied."
"Module: Audio"
"CallOn: Nothing"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_get_num_volmod_submixes()
{
	return level._audio.mix.volmod_submixes.size;
}

/*
///ScriptDocBegin
"Name: MM_get_num_submixes()"
"Summary: Returns the number of submixes currently applied."
"Module: Audio"
"CallOn: Nothing"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_get_num_submixes()
{
	return 0;
}

/*
///ScriptDocBegin
"Name: MM_get_volmod_submix_name_by_index(<index>)"
"Summary: Returns the volmod submix at the given index."
"MandatoryArg: <index> : The index at which to retrieve the volmod submix."
"Module: Audio"
"CallOn: Nothing"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_get_volmod_submix_name_by_index(index)
{
	assert(IsDefined(index) && index >= 0);
	result = undefined;
	if (IsDefined(level._audio.mix.volmod_submixes) && index < level._audio.mix.volmod_submixes.size)
	{
		count = 0;
		foreach( volmod_submix_name, volmod_submix in level._audio.mix.volmod_submixes)
		{
			if (volmod_submix.size > 0)
			{
				if (count == index)
				{
					if (volmod_submix_name == "zone_mix")
					{
						assert(IsDefined(level._audio.mix.volmod_submixes["zone_mix"]));
						real_name = level._audio.mix.volmod_submixes["zone_mix"]["preset_name"];
						volmod_submix_name = "zone_mix : " + real_name;
					}
					result = volmod_submix_name;
					break;
				}
				count++;
			}
		}
	}
	return result;
}


/*
///ScriptDocBegin
"Name: MM_get_volmod_submix_by_name(<name>)"
"Summary: Returns the submix array structure (volmodname-value pairs) of the indicated name."
"MandatoryArg: <name> : The name of the volmod submix to retrieve."
"Module: Audio"
"CallOn: Nothing"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_get_volmod_submix_by_name(name)
{
	assert(IsString(name));
	result = undefined;
	
	if (GetSubStr(name, 0, 8) == "zone_mix")
		name = "zone_mix";
	
	if (IsDefined(level._audio.mix.volmod_submixes) && IsDefined(level._audio.mix.volmod_submixes[name]))
	{
		if (level._audio.mix.volmod_submixes[name].size > 0)
			result = level._audio.mix.volmod_submixes[name];
	}
	return result;
}


/*
///ScriptDocBegin
"Name: MM_set_default_volmod(<volmod_name>, <val>, <fade_time_>)"
"Summary: Set the default volmod's current value."
"MandatoryArg: <volmod_name> : Name of the volmod."
"MandatoryArg: <val> : The valule the volmod is to be set to."
"Optional: <fade_time_> : Time to go from current val to target val."
"Module: Audio"
"CallOn: Nothing"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_set_default_volmod(volmod_name, val, fade_time_)
{
	assert(IsString(volmod_name));
	assert(IsDefined(val));
	assert(IsDefined(level._audio.mix.volmod_submixes));

	val = clamp(val, 0, 1); // validate

	if (IsDefined(level._audio.mix.volmod_submixes["default"])) // there *should* be a default volmod submix on every level now...
	{
		if (IsDefined(level._audio.mix.volmod_submixes["default"][volmod_name]))
		{
			level._audio.mix.volmod_submixes["default"][volmod_name].current_volume = val;
			MMx_update_mix(fade_time_, "default"); // update mix... this wakes up the throttling queue
		}
		else
		{
			aud_print_error("Trying to set a volmod value on the default submix but the volmod doesn't exist: " + volmod_name);
		}
	}
	else
	{
		aud_print_error("Trying to set a volmod value on the default submix but \"default\" doesn't exist.");
	}
}

/*
///ScriptDocBegin
"Name: MM_get_original_default_volmod(<volmod_name>)"
"Summary: Get's the original default value of volmod."
"MandatoryArg: <volmod_name> : Name of the volmod."
"Module: Audio"
"CallOn: Nothing"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_get_original_default_volmod(volmod_name)
{
	result = undefined;
	assert(IsString(volmod_name));
	assert(IsDefined(level._audio.mix.volmod_submixes));

	if (IsDefined(level._audio.mix.volmod_submixes["default"])) // there *should* be a default volmod submix on every level now...
	{
		if (IsDefined(level._audio.mix.volmod_submixes["default"][volmod_name]))
		{
			result = level._audio.mix.volmod_submixes["default"][volmod_name].original_volume;
		}
		else
		{
			aud_print_error("Trying to set a volmod value on the default submix but the volmod doesn't exist: " + volmod_name);
		}
	}
	else
	{
		aud_print_error("Trying to set a volmod value on the default submix but \"default\" doesn't exist.");
	}
	
	return result;
}

/*
///ScriptDocBegin
"Name: MM_restore_original_default_volmod(<volmod_name>, <fade_time_>)"
"Summary: Set the volmod to it's original default value over <fade_time>."
"MandatoryArg: <volmod_name> : Name of the volmod."
"Optional: <fade_time_> : Time to go from current val to target val."
"Module: Audio"
"CallOn: Nothing"
"SPMP: singleplayer"
///ScriptDocEnd
*/
MM_restore_original_default_volmod(volmod_name, fade_time_)
{
	original_value = MM_get_original_default_volmod(volmod_name);
	if (IsDefined(original_value))
	{
			MM_set_default_volmod(volmod_name, original_value, fade_time_);
	}
}

/# // UNIT TEST
MM_default_volmod_test()
{
	wait(5);
	
	max_vol = MM_get_original_default_volmod("max");
	MM_set_default_volmod("music", max_vol, 10);

	wait(10);

	foley_plr_vol = MM_get_original_default_volmod("foley_plr");
	MM_set_default_volmod("music", foley_plr_vol, 10);
	
	wait(10);
	
	music_vol = MM_get_original_default_volmod("music");
	MM_set_default_volmod("music", music_vol, 10);
	
	wait(10);
	
	MM_set_default_volmod("music", 0, 10);
	
	wait(10);
	
	MM_restore_original_default_volmod("music", 10);
}
#/

//-------------------------------------------------------------------
//PRIVATE FUNCTIONS BEGIN - functions intended only for mix utilities
//------------------------------------------------------------------- 
MMx_set_mix(preset_name, fade_time_, initial_volume_scale_)
{
	MMx_make_new_submix(preset_name, initial_volume_scale_);
		
	// store the curr mix to the prev mix
	level._audio.mix.prev_preset = level._audio.mix.curr_preset;	
	level._audio.mix.curr_preset = preset_name;

	MMx_update_mix(fade_time_, preset_name);	
}

MMx_scale_submix(preset_name, volume_scale)
{
	assert(IsString(preset_name));
	assert(IsDefined(volume_scale));
	
	if (IsDefined(level._audio.mix.volmod_submixes[preset_name]))
	{
		foreach(channel_name, channel_info in level._audio.mix.volmod_submixes[preset_name])
		{
			level._audio.mix.volmod_submixes[preset_name][channel_name].current_volume = channel_info.original_volume * volume_scale; // only modify "current_volume", not "original_volume"
		}
	}
}


MMx_make_new_submix(preset_name, volume_scale_)
{
	assert(IsString(preset_name));
	
	if (preset_name == "default")
	{
		/#
		aud_print_error("Can't set a volmod mix preset with the name, \"default\". That is reserved for the volumemodgroups.svmod file.");
		#/
		return;
	}
	
	if (!IsDefined(level._audio.mix.volmod_submixes[preset_name])) // only call this when submix has not yet been made!
	{
		preset = MMx_get_mix_preset(preset_name);
		if (!IsDefined(preset))
			return;
		
		volume_scale = 1.0;
		if (IsDefined(volume_scale_))
		{
			volume_scale = volume_scale_;
			volume_scale = max(volume_scale, 0.0);
		}
		
		level._audio.mix.volmod_submixes[preset_name] = [];
		foreach(channel_name, value in preset)
		{
			if (channel_name != "name" && channel_name != "fade_time")
			{
				level._audio.mix.volmod_submixes[preset_name][channel_name] = spawnstruct();
				level._audio.mix.volmod_submixes[preset_name][channel_name].current_volume = value * volume_scale; // the actual volume of this channel for this submix
				level._audio.mix.volmod_submixes[preset_name][channel_name].original_volume = value; // the original volume of this channel for this submix (from the preset)
			}
		}
	}
}

MMx_create_submix_blend(preset_name_A, preset_name_B, blendvalue_)
{
	// note: preset_name_A can be undefined... 	
	assert(IsString(preset_name_B));
	
	blendvalue = 0;
	
	if (IsDefined(blendvalue_))
		blendvalue = clamp(blendvalue_, 0, 1);
		
	submixblend = spawnstruct();
	// get B first
	presetB = MMx_get_mix_preset(preset_name_B);
	if (!IsDefined(presetB))
	{
		return;
	}
	
	// let the blend know if it is a volmod submix blend
	submixblend.presetB = presetB;

	// no fadetimes or names in submix blends
	submixblend.presetB["fade_time"] = undefined;
	submixblend.presetB["name"] = undefined;

	if (IsDefined(preset_name_A))
	{
		presetA = MMx_get_mix_preset(preset_name_A);
		if (!IsDefined(presetA))
			return;
		
		submixblend.presetA = presetA;
		
		assert(IsDefined(submixblend.presetA));
		// no fadetimes or names
		submixblend.presetA["fade_time"] = undefined;
		submixblend.presetA["name"] = undefined;
		
		/#
		// validate the submix preset blends -- they need to have the same channels defined in both
		foreach(channel_name, value in submixblend.presetA)
			assertEx(IsDefined(submixblend.presetB[channel_name]), "Submix blends \"" + preset_name_A + "\" and \"" + preset_name_B + "\" need to have the same channels defined in both submixes.");
		#/
	}
	else
	{
		// make an "artificial" preset A of all 1.0 for each channel of preset B
		submixblend.presetA = [];
		foreach( channel_name, value in submixblend.presetB)
			submixblend.presetA[channel_name] = 1.0;
	}
		
	submixblend.blendvalue = blendvalue;
	
	return submixblend;
}

MMx_clear_submixes(update_, fade_time_)
{
	update = true;
	if (IsDefined(update_)) // note: this can be called without updating internally
	{
		update = update_;
	}
	
	foreach(submix_name, submix in level._audio.mix.volmod_submixes)
	{
		// do not clear these special-case submixes
		if (submix_name != "default" 
				&& submix_name != "zone_mix" 
				&& !IsDefined(level._audio.mix.sticky_submixes[submix_name]) 
				&& submix_name != "mm_solo" 
				&& submix_name != "mm_mute" )
		{
			level._audio.mix.volmod_submixes[submix_name]["CLEAR"] = true; // keyword to clear it during update
			level._audio.mix.changed_presets[submix_name] = true;
		}
	}
	
	if (update)
	{
		MMx_update_mix(fade_time_, undefined);
	}
}

// preset_name is the mix that has been updated
MMx_update_mix(fade_time_, preset_name)
{
	level._audio.mix.last_fade_time = fade_time_;
	if (IsDefined(preset_name))
	{
		level._audio.mix.changed_presets[preset_name] = true;
	}
	level notify("mix_update");
}

// defered mix update thread, forces updates to happen at most once per frame
MMx_update_mix_thread()
{
	level waittill("mix_update");
	while(true)
	{
		waittillframeend;
		fade_time = 0;
		if (IsDefined(level._audio.mix.last_fade_time))
		{
			fade_time = level._audio.mix.last_fade_time;
		}
		MMx_update_volmod_groups(fade_time); // the volmod update function
		assert(level._audio.mix.changed_presets.size == 0);
		/#
		update_volmod_submix_hud();
		#/
		level waittill("mix_update");
	}
}


MMx_mix_in_non_changed_submixes()
{
	// now see if any non-changed volmod submixes have channels that need to be mixed into
	// the volume products array
	assert(IsDefined(level._audio.mix.volume_products));
	assert(IsDefined(level._audio.mix.volmod_submixes));
	
	not_changed_submixes = [];
	foreach(submix_name, submix in level._audio.mix.volmod_submixes)
	{
		if (!IsDefined(level._audio.mix.changed_presets[submix_name]))
		{
			not_changed_submixes[submix_name] = true;
		}
	}
	
	
	// the idea is that the volume_products array size should usually be much smaller than 
	// all the submix arrays
	foreach(volmod_name, v1 in level._audio.mix.volume_products)
	{
		foreach(submix_name, v2 in not_changed_submixes)
		{
			if (IsDefined(level._audio.mix.volmod_submixes[submix_name][volmod_name]))
			{
				level._audio.mix.volume_products[volmod_name] *= level._audio.mix.volmod_submixes[submix_name][volmod_name].current_volume;
			}
		}
	}
}


MMx_update_volmod_groups(fade_time_)
{
	assert(IsDefined(level._audio.mix));
	assert(IsArray(level._audio.mix.volmod_submixes));
	assert(IsDefined(level._audio.mix.headroom));
	
	fade_time = 1.0;
	if (IsDefined(fade_time_))
	{
		fade_time = fade_time_;
		fade_time = max(fade_time, 0.0);
	}
	
	// get the volume products of the submixes that have changed this frame
	level._audio.mix.volume_products = undefined;
	MMx_set_volume_products_volmods(false);
	assert(IsDefined(level._audio.mix.volume_products));
	
	// this mixes in the non-changed submixes per-channel
	MMx_mix_in_non_changed_submixes();
	
	has_changed = false;
	
	// loop through all channel volumes, and if the new computed volume product is different than current setting, enque it
	foreach(volmod, volume in level._audio.mix.volume_products)
	{
		if (volmod != "voiceover_critical" && volmod != "fullvolume")
		{
			// BUG FIX THAT WOULD CHANGE MIX TOO MUCH.
			// FIX FOR NEXT GAME. THIS IS SUPPOSED TO BE CLAMPED BEFORE APPLYING HEADROOM. -- aaron (*head in shame*)
			//volume = clamp(volume, 0, 1);
			volume *= level._audio.mix.headroom;
		}

		if (volume != level._audio.mix.volmod_vals[volmod].volume)
		{
			has_changed = true;
			level._audio.mix.volmod_vals[volmod].volume = volume; // update the chan_info for the channel_volumes
			level._audio.mix.volmod_vals[volmod].fade_time = fade_time;
			MMx_volmod_setting_enqueue(volmod, volume, fade_time);
		}
	}
	
	level._audio.mix.changed_presets = [];

	if (has_changed)
	{
		level notify("aud_new_volmod_set");
	}
}

MMx_set_volume_products_volmods(except_default)
{
	assert(IsDefined(except_default));
	assert(!IsDefined(level._audio.mix.volume_products));
	assert(IsDefined(level._audio.mix.changed_presets));
	
	level._audio.mix.volume_products = [];
	submixblendproducts = [];
	
	
	// loop through only the submix presets that have changed this frame
	foreach(submix_name, _ in level._audio.mix.changed_presets)
	{
		// check submixes first
		if (IsDefined(level._audio.mix.volmod_submixes[submix_name])) 
		{
			submix = level._audio.mix.volmod_submixes[submix_name];
			submix["name"] = undefined;
			submix["fade_time"] = undefined;
			submix["preset_name"] = undefined;
			
			// see if this is a special "clear" preset update
			is_cleared = false;
			if (IsDefined(submix["CLEAR"]))
				is_cleared = true;
			submix["CLEAR"] = undefined;
			
			foreach(channel_name, channel_info in submix)
			{
				if (IsDefined(level._audio.mix.volume_products[channel_name]) && !is_cleared) // scale existing entry with new scale factor
				{
					level._audio.mix.volume_products[channel_name] *= channel_info.current_volume; // mix in
				}
				else if (is_cleared && !IsDefined(level._audio.mix.volume_products[channel_name])) // if we are clearing, but the volume_product doesn't yet exist, set to 1.0 (no effect)
				{
					level._audio.mix.volume_products[channel_name] = 1.0;
				}
				else if (!is_cleared) // make new entry if doesn't exist and not clearing
				{
					level._audio.mix.volume_products[channel_name] = channel_info.current_volume;
				}
				
				// if a submix has 1.0 as the value, clear it to optimize future updates

/*			TODO: commenting out to revisit optimization idea later
				if (channel_info.current_volume == 1.0)
				{
					level._audio.mix.volmod_submixes[submix_name][channel_name] = undefined;
				}
*/
			}
			
			if (is_cleared)
				level._audio.mix.volmod_submixes[submix_name] = undefined;
		}
		else if (IsDefined(level._audio.mix.volmod_submixblends[submix_name]))
		{
			submixblend = level._audio.mix.volmod_submixblends[submix_name];
	
			is_cleared = false;
			if (IsDefined(submixblend.clear))
			{
				is_cleared = true;
			}
			
			// loop through each channel in presetA, it is asserted
			foreach( channel_name, value in submixblend.presetA )
			{
				// create a placeholder for the channel in the submixblendproducts
				if (!IsDefined(submixblendproducts[channel_name]))
				{
					submixblendproducts[channel_name] = 1.0;
				}
				
				assert(IsDefined(submixblend.presetB[channel_name])); // should alreayd be validated, but just to make sure
				
				if (!is_cleared)
				{
					valB = submixblend.presetB[channel_name];
					valA = submixblend.presetA[channel_name];
					blend = submixblend.blendvalue;
					assert(valA >= 0.0);
					assert(valB >= 0.0);
					assert(blend >= 0.0 && blend <= 1.0);
					blendresult = blend * ( valB - valA ) + valA;
					assert(blendresult >= 0.0);
					submixblendproducts[channel_name] *= blendresult;
				}
			}
			
			if (is_cleared)
				level._audio.mix.volmod_submixblends[submix_name] = undefined;
			
		}
	}
	
	// mix in the submixblendproducts with the non-submixblend products
	
	foreach( channel, value in submixblendproducts)
	{
		if (IsDefined(level._audio.mix.volume_products[channel]))
		{
			level._audio.mix.volume_products[channel] *= value; // mix in if already in the volume products
		}
		else
			level._audio.mix.volume_products[channel] = value; // else just add it
	}
}

MMx_apply_initial_mix()
{
	////////////////////////////////////////////////////////////////////////
	// Support for setting a debug mix/submix from a dvar, 
	// and bypassing dynamic mixing during gameplay	
	////////////////////////////////////////////////////////////////////////
	
	// Handle Debug Mix.
	debug_mix = undefined;
	/#
	debug_mix = aud_get_debug_mix(); 
	if (IsString(debug_mix))
	{
		level._audio.mix.debug_mix_mode = true;
		thread MMx_apply_debug_mix(debug_mix);
	}
	#/

	// Handle Debug Submix.
	debug_submix = undefined;
	/#
	debug_submix = aud_get_debug_submix(); 
	if (IsString(debug_submix))
	{
		MM_add_submix(debug_submix);
		MM_make_submix_sticky(debug_submix);
	}
	#/
}

MMx_apply_debug_mix(debug_mix)
{
	if (level._audio.mix.debug_mix_mode)
	{
		// wait until player is defined
		while (!IsDefined(level.player))
		{
			wait(0.05);
		}
		assert(IsString(debug_mix));
		MMx_set_mix(debug_mix); // note: not using MM_start_preset for this
	}
}

/#
// Checks against the given min-time for mix setting and prints an error message or asserts.
MMx_mix_timer_check(mix_preset_name_)
{
	time_difference = undefined;
	
	if (!IsDefined(level._audio.mix.min_mix_time))
	{
		level._audio.mix.min_mix_time = 50;
	}
			
	// it's possible to set a mix without using a preset, so "undefined" is a valid preset name for the debug messages below...
	mix_preset_name = "undefined";
	if (IsDefined(mix_preset_name_))
	{
		mix_preset_name = mix_preset_name_;
	}
	
	curr_time = getTime();
	
	if (IsDefined(level._audio.mix.lastTime))
	{
		time_difference = curr_time - level._audio.mix.lastTime;

		if (time_difference < level._audio.mix.min_mix_time)
		{
			if (level._audio.mix.print_mix_error_messages)
			{
				aud_print_error("AUDIO MIX MESSAGE SENT TOO OFTEN! Name: " + mix_preset_name + ". Time since last: " + time_difference + ". Min time: " + level._audio.mix.min_mix_time + "."); 
			}
			
			if (level._audio.mix.assert_if_setting_mix_too_often)
			{
				AssertEX(false, "AUDIO MIX MESSAGE SENT TOO OFTEN! Mix preset name: " + mix_preset_name );
			}
		}
	}
}
#/

// // this function enqueues the volmod setting the caller notifies the thread to wake up and deque this queue 
MMx_volmod_setting_enqueue(volmod_name, volume, fade_time)
{
	assert(IsDefined(volmod_name));
	assert(IsDefined(volume));
	assert(IsDefined(fade_time));
	
	if (!IsDefined(level._audio.mix.volmod_queue))
	{
		level._audio.mix.volmod_queue = [];
		level._audio.mix.volmod_index = 0;
	}
	
	already_queued = false;
	// see if the channel has already been enqueued, and just ovewrite it...
	foreach(key, value in level._audio.mix.volmod_queue)
	{
		if (value["volmod"] == volmod_name)
		{
			already_queued = true;
			level._audio.mix.volmod_queue[key]["volume"] = volume;
			level._audio.mix.volmod_queue[key]["fade_time"] = fade_time;
			break;
		}
	}
	
	if (!already_queued)
	{
		new_mix_queue = [];
		new_mix_queue["volmod"] = volmod_name;
		new_mix_queue["volume"] = volume;
		new_mix_queue["fade_time"] = fade_time;
		
		level._audio.mix.volmod_queue[level._audio.mix.volmod_index] = new_mix_queue;
		level._audio.mix.volmod_index++;
	}
}

// this function enqueues the mix setting the caller notifies the thread to wake up and deque this queue 
MMx_mix_setting_enqueue(channel, volume, fade_time)
{
	assert(IsDefined(channel));
	assert(IsDefined(volume));
	assert(IsDefined(fade_time));
	
	if (!IsDefined(level._audio.mix.queue))
	{
		level._audio.mix.queue = [];
		level._audio.mix.index = 0;
	}
	
	channel_already_queued = false;
	// see if the channel has already been enqueued, and just ovewrite it...
	foreach(key, value in level._audio.mix.queue)
	{
		if (value["channel"] == channel)
		{
			channel_already_queued = true;
			level._audio.mix.queue[key]["volume"] = volume;
			level._audio.mix.queue[key]["fade_time"] = fade_time;
			break;
		}
	}
	
	if (!channel_already_queued)
	{
		new_mix_queue = [];
		new_mix_queue["channel"] = channel;
		new_mix_queue["volume"] = volume;
		new_mix_queue["fade_time"] = fade_time;
		
		level._audio.mix.queue[level._audio.mix.index] = new_mix_queue;
		level._audio.mix.index++;
	}
}

MMx_volmod_server_throttler(max_count_)
{
	if (!IsDefined(level._audio.mix.volmod_queue))
	{
		level._audio.mix.volmod_queue = [];
		level._audio.mix.volmod_index = 0;
	}
		
	// the max number of mix messages to send per frame	
	max_count = 5;
	if (IsDefined(max_count_))
	{
		max_count = max_count_;
		max_count = max(max_count, 1);
	}
		
	while(true)
	{
		// wake up this thread when a new mix is set
		level waittill("aud_new_volmod_set");
		assert(IsDefined(level._audio.mix.volmod_queue));

		// as long as the queue is nonzero, keep looping here
		while(level._audio.mix.volmod_queue.size > 0)
		{
			mix_message_count = 0;
			keys_used = [];
			foreach( key_index, mix in level._audio.mix.volmod_queue)
			{
				// only send over a limited number of server commands this frame
				if (mix_message_count < max_count) 
				{
					mix_message_count++;
					// keep track of which unique key indices sent over this frame
					keys_used[keys_used.size] = key_index;
					// get the mix setting
					mix_setting = level._audio.mix.volmod_queue[key_index];
					assert(IsDefined(mix_setting));
					assert(IsDefined(mix_setting["volmod"]));
					assert(IsDefined(mix_setting["volume"]));
					assert(IsDefined(mix_setting["fade_time"]));
					
					// set it over the server 
					channel = mix_setting["volmod"];
					volume = mix_setting["volume"];
					fade_time = mix_setting["fade_time"];
					volume = clamp(volume, 0.0, 1.0);
					
					assert(MMx_is_volmod_channel(channel));
					level.player SetVolMod(channel, volume, fade_time);
				}
				else
				{
					break; 
				}
			}
			
			// undefine the elements in the queue which were sent
			for (i = 0; i < keys_used.size; i++)
			{
				key = keys_used[i];
				level._audio.mix.volmod_queue[key] = undefined;
			}
			
			// wait till end of frame to do another round of messages
			wait(0.05);
		}
	}
}

// Makes sure to only use a max number of SetChannelVolume functions per frame
MMx_mix_server_throttler(max_count_)
{
	if (!IsDefined(level._audio.mix.queue))
	{
		level._audio.mix.queue = [];		
		level._audio.mix.index = 0; 	
	}
		
	// the max number of mix messages to send per frame	
	max_count = 5;
	if (IsDefined(max_count_))
	{
		max_count = max_count_;
		max_count = max(max_count, 1);
	}
		
	while(true)
	{
		// wake up this thread when a new mix is set
		level waittill("aud_new_mix_set");
		assert(IsDefined(level._audio.mix.queue));

		// as long as the queue is nonzero, keep looping here
		while(level._audio.mix.queue.size > 0)
		{
			mix_message_count = 0;
			keys_used = [];
			foreach( key_index, mix in level._audio.mix.queue)
			{
				// only send over a limited number of server commands this frame
				if (mix_message_count < max_count) 
				{
					mix_message_count++;
					// keep track of which unique key indices sent over this frame
					keys_used[keys_used.size] = key_index;
					// get the mix setting
					mix_setting = level._audio.mix.queue[key_index];
					assert(IsDefined(mix_setting));
					assert(IsDefined(mix_setting["channel"]));
					assert(IsDefined(mix_setting["volume"]));
					assert(IsDefined(mix_setting["fade_time"]));
					
					// set it over the server 
					channel = mix_setting["channel"];
					volume = mix_setting["volume"];
					fade_time = mix_setting["fade_time"];
					volume = clamp(volume, 0.0, 1.0);
					
					level.player SetChannelVolume(channel, volume, fade_time);
				}
				else
				{
					break; 
				}
			}
			
			// undefine the elements in the queue which were sent
			for (i = 0; i < keys_used.size; i++)
			{
				key = keys_used[i];
				level._audio.mix.queue[key] = undefined;
			}
			
			// wait till end of frame to do another round of messages
			wait(0.05);
		}
	}
}

MMx_get_preset_from_string_table(presetname, checklevel)
{
	assert(IsString(presetname));
		
	preset = [];
	level_stringtable = maps\_audio::get_mix_stringtable();
	common_stringtable = "soundtables/common_mix.csv";
	
	/#
	if (aud_check_fastfiles()) return preset;
	#/

	if (!IsDefined(level._audio.mix.preset_cache))
		level._audio.mix.preset_cache = [];

	if (IsDefined(level._audio.mix.preset_cache[presetname]))
	{
		preset = level._audio.mix.preset_cache[presetname];
	}
	else
	{
		if (checklevel)
			preset = MMx_get_mix_preset_from_stringtable_internal(level_stringtable, presetname, false);
		
		if (!IsDefined(preset) || preset.size == 0)
			preset = MMx_get_mix_preset_from_stringtable_internal(common_stringtable, presetname, true);
		
		if (!IsDefined(preset) || preset.size == 0)
			return;
			
		level._audio.mix.preset_cache[presetname] = preset;
	}
	
	return preset;
}

MMx_get_mix_preset_from_stringtable_internal(stringtable, presetname, is_common)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsString(stringtable));
	assert(IsString(presetname));
	assert(IsDefined(is_common));

	numparams = 4;
	row_value = "";
	row_count = 0;
	found_preset = false;
	empty_rows = 0;
	
	fade_time = undefined;
	preset = [];
	
	// cache the param col names (per stringtable file) to reduce the amount of parsing
	if (!IsDefined(level._audio.mix.param_names))
	{
		level._audio.mix.param_names = [];
	}
	if (!IsDefined(level._audio.mix.param_names[stringtable]))
	{
		level._audio.mix.param_names[stringtable] = [];
		for (col = 1; col < numparams; col++)
		{
			paramname = tablelookupbyrow(stringtable, 0, col);
			level._audio.mix.param_names[stringtable][paramname] = col; // cache param name (channels, value, fade_time)
		}
	}

	// grab the indexed row from this preset 
	index = get_indexed_preset("mix", presetname, is_common);
	if (index != -1)
	{
		row_count = index;
	}
	else if ((is_common && aud_is_common_indexed()) || (!is_common && aud_is_local_indexed()))
	{
		return preset; // preset doesn't exist
	}
	
	entry_count = 0; // counts entries in each preset
	
	while(row_value != "EOF" && empty_rows < 10 ) // end of file
	{
		row_value = tablelookupbyrow(stringtable, row_count, 0);
		if (row_value != "")
			empty_rows = 0;
		
		while(row_value == presetname)  // this is the beginning of the preset
		{
			found_preset = true;
			
			// grab the optionally set fade_time parameter of the preset
			if (!IsDefined(fade_time))
			{
				fade_time_col = level._audio.mix.param_names[stringtable]["fade_time"];
				fade_time = tablelookupbyrow(stringtable, row_count, fade_time_col);
				if (!IsDefined(fade_time) || (IsDefined(fade_time) && fade_time == ""))
				{
					fade_time = 1.0;
				}
			}
			
			// get the channel-value settings
			channel_name_col = level._audio.mix.param_names[stringtable]["channels"]; 
			channel_val_col = level._audio.mix.param_names[stringtable]["value"];
			
			channel_name = tablelookupbyrow(stringtable, row_count, channel_name_col);
			channel_val = tablelookupbyrow(stringtable, row_count, channel_val_col);
			
			assertEx(IsDefined(channel_name) && channel_name != "", "In soundtable " + stringtable + " there is a format problem in preset " + presetname);
			assertEx(IsDefined(channel_val) && channel_name != "", "In soundtable " + stringtable + " there is a format problem in preset " + presetname);
			
			// check for keyword "set_all" -- which is used to prevent having to set every channel in the preset file
			if ((channel_name == "set_all" || channel_name == "setall"))
			{
				assertEx(entry_count == 0, "In soundtable " + stringtable + " the \"set_all\" keyword needs to be the first entry in the preset " + presetname);
				if (float(channel_val) < 1) // do *not* make a submix with everything set to 1
					preset = volmod_mix_with_all_channels_at(float(channel_val));
			}
			else
			{
				assert(IsDefined(level._audio.mix.volmodfile));
				if (!IsDefined(level._audio.mix.volmodfile[channel_name]))
				{
					aud_print_error("In soundtable " + stringtable + ", " +  presetname + " uses a volmod group name that doesn't exist in the volmodgroups.csv file.");
					return;
				}
				preset[channel_name] = float(channel_val);
			}

			row_count++;
			row_value = tablelookupbyrow(stringtable, row_count, 0);
			entry_count++;
		}
		empty_rows++;
		// require preset parameters to be grouped together
		if (found_preset)
			break; // successful!
		row_count++;
	}
	
	// add fade_time preset at the end
	if (found_preset && IsDefined(fade_time))
	{
		preset["fade_time"] = float(fade_time);
	}
	return preset;
}

// Define mix presets with this function
MMx_get_mix_preset(preset_name)
{
	assert(IsString(preset_name));
	assert(IsDefined(level._audio.mix.preset_cache));

	if (!IsDefined(level._audio.mix.preset_cache))
		level._audio.mix.preset_cache = [];

	preset = [];
	if (IsDefined(level._audio.mix.preset_cache[preset_name])) // get cached version if exists
	{
		preset = level._audio.mix.preset_cache[preset_name];
	}
	else
	{
		preset = undefined;
		if (level._audio.mix.use_string_table_presets)
		{
			preset = MMx_get_preset_from_string_table(preset_name, true);
		}
		else
		{
			preset = MMx_get_preset_from_string_table(preset_name, false);
			if (!IsDefined(preset) || preset.size == 0)
			{
				preset = AUDIO_PRESETS_MIX(preset_name, preset);
			}
		}

		if(!IsDefined(preset) || preset.size == 0)
		{
			/#
			aud_print_error("Mix preset " + preset_name + " was not found.");
			#/
			return;
		}
	
		preset["name"] = preset_name; // for debug purposes
	
		// fade_time is optional in the preset, so if it wasn't given, put it in a default
		if (!IsDefined(preset["fade_time"]))
		{
			preset["fade_time"] = 1.0;
		}
		// store the preset
		level._audio.mix.preset_cache[preset_name] = preset; 
	}
	return preset;
}

MMx_init_volmods()
{
	assert(IsDefined(level._audio.mix));
		
	if (!IsDefined(level._audio.mix.volmodfile))
	{
		MMx_parse_volumemodgroups_csv();
	}
	
	level._audio.mix.volmod_vals = [];
	
	assert(IsDefined(level._audio.mix.volmodfile));
	foreach(chan_name, value in level._audio.mix.volmodfile)
	{
		level._audio.mix.volmod_vals[chan_name] = SpawnStruct();
		level._audio.mix.volmod_vals[chan_name].volume = value;
		level._audio.mix.volmod_vals[chan_name].fade_time = 0.0;
	}
	
	// set up the channel names
	MMx_init_channel_names();
}

MMx_init_channel_names()
{
	assert(IsDefined(level._audio) && IsDefined(level._audio.mix));

	if (!IsDefined(level._audio.mix.channel_names))
	{
		chans = [];
		chans["physics"] = true;
		chans["ambdist1"] = true;
		chans["ambdist2"] = true;
		chans["auto"] = true;
		chans["auto2"] = true;
		chans["auto2d"] = true;
		chans["autodog"] = true;
		chans["explosiondist1"] = true;
		chans["explosiondist2"] = true;
		chans["explosiveimpact"] = true;
		chans["element"] = true;
		chans["element_int"] = true;
		chans["element_ext"] = true;
		chans["bulletimpact"] = true;
		chans["bulletflesh1"] = true;
		chans["bulletflesh2"] = true;
		chans["bulletwhizby"] = true;
		chans["vehicle"] = true;
		chans["vehiclelimited"] = true;
		chans["menu"] = true;
		chans["body"] = true;
		chans["body2d"] = true;
		chans["reload"] = true;
		chans["reload2d"] = true;
		chans["item"] = true;
		chans["explosion1"] = true;
		chans["explosion2"] = true;
		chans["explosion3"] = true;
		chans["explosion4"] = true;
		chans["explosion5"] = true;
		chans["effects1"] = true;
		chans["effects2"] = true;
		chans["effects3"] = true;
		chans["effects2d1"] = true;
		chans["effects2d2"] = true;
		chans["vehicle2d"] = true;
		chans["weapon_dist"] = true;
		chans["weapon_mid"] = true;
		chans["weapon"] = true;
		chans["weapon2d"] = true;
		chans["nonshock"] = true;
		chans["nonshock2"] = true;
		chans["voice"] = true;
		chans["local"] = true;
		chans["local2"] = true;
		chans["local3"] = true;
		chans["ambient"] = true;
		chans["hurt"] = true;
		chans["player1"] = true;
		chans["player2"] = true;
		chans["music"] = true;
		chans["musicnopause"] = true;
		chans["grondo3d"] = true;
		chans["grondo2d"] = true;
		chans["mission"] = true;
		chans["critical"] = true;
		chans["announcer"] = true;
		chans["shellshock"] = true;
			
		level._audio.mix.channel_names = chans;
	}
	
	// make sure we have the right number of channels defined, if channels.def is changed, this number (and the table above) needs to be updated!!!
	assert(level._audio.mix.channel_names.size == 58); 
}


MMx_get_channel_volumes()
{
	assert(IsDefined(level._audio) && IsDefined(level._audio.mix));
	return level._audio.mix.channel_volumes;
}

// --------------------------------------------------
// HELPER FUNCTIONS - used in preset files
// --------------------------------------------------

volmod_mix_with_all_channels_at(vol)
{
	assert(IsDefined(level._audio.mix.volmodfile));
	
	preset = [];
	
	foreach(channel, value in level._audio.mix.volmodfile)
	{
		if (channel != "hud" && channel != "interface" && channel != "interface_music")
		{
			preset[channel] = vol;
		}
	}
	
	return preset;
}

MMx_parse_volumemodgroups_csv()
{
	stringtable = "soundaliases/volumemodgroups.svmod";
	level._audio.mix.volmodfile = [];
	
	maxblankcount = 10;
	currblankcount = 0;
	row = 0;
	while(currblankcount < maxblankcount)
	{
		volmodname = tablelookupbyrow(stringtable, row, 0); // name column

		// check for blanks
		if (volmodname == "")
		{
			currblankcount++;
			continue;
		}
		// check for comment
		first_char = GetSubStr(volmodname, 0, 0);
		if (first_char == "#")
			continue;

		volmodvalue = tablelookupbyrow(stringtable, row, 1); // value column
		
		// store
		level._audio.mix.volmodfile[volmodname] = float(volmodvalue);
		row++;
	}
	
	// create a default volmod submix based on the file.
	if (!IsDefined(level._audio.volmod_submixes))
		level._audio.volmod_submixes = [];
		
	level._audio.mix.volmod_submixes["default"] = [];
	foreach(volmodname, value in level._audio.mix.volmodfile)
	{
		level._audio.mix.volmod_submixes["default"][volmodname] = spawnstruct();
		level._audio.mix.volmod_submixes["default"][volmodname].current_volume = value; // the actual volume of this channel for this submix
		level._audio.mix.volmod_submixes["default"][volmodname].original_volume = value; // the original volume of this channel for this submix (from the preset)
	}
	
}

MMx_is_mix_channel(value)
{
	assert(IsDefined(level._audio.mix.channel_names));
	return IsDefined(level._audio.mix.channel_names[value]);
}

// determines whether the input value is a valid volmod channel
MMx_is_volmod_channel(value)
{
	assert(IsDefined(level._audio.mix.volmodfile));
	return IsDefined(level._audio.mix.volmodfile[value]);
}
