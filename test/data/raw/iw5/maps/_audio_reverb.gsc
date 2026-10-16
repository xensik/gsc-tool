#include maps\_audio;

/***************************************************************************************

	REVERB CODE

	"RVB_" functions are considered to be the public interface

***************************************************************************************/


/*******************
* PUBLIC FUNCTIONS *
********************/

/*
///ScriptDocBegin
"Name: RVB_init()"
"Summary: Inititalizes the Occlusion EQ System."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: none."
"Example: RVB_init();
"SPMP: singleplayer"
///ScriptDocEnd
*/
RVB_init(args)
{
	if (!IsDefined(level._audio))
	{
		level._audio = SpawnStruct();
	}
	level._audio.reverb = SpawnStruct();
	level._audio.reverb.use_string_table_presets = false;
	level._audio.reverb.use_iw_presets = false;	
	level._audio.reverb.current_reverb = "";
}


RVB_use_string_table()
{
	level._audio.reverb.use_string_table_presets = true;
	level._audio.reverb.use_iw_presets = false;
}

RVB_use_iw_presets()
{
	level._audio.reverb.use_iw_presets = true;
	level._audio.reverb.use_string_table_presets = false;
}



/*
///ScriptDocBegin
"Name: RVB_set_dry_level( <reverb>, <value> )"
"Summary: Twiddles the dry level 'knob' of the given reverb. "
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <reverb> : A valid reverb struct with which to twiddle."
"MandatoryArg: <value> : The twiddled value of dry level."
"Example: RVB_set_dry_level(myReverbStruct, 0.5);
"SPMP: singleplayer"
///ScriptDocEnd
*/
RVB_set_dry_level(reverb, value)
{
	/#
	RVBx_validate(reverb);
	#/
	value = clamp(value, 0, 1.0);
	reverb.drylevel = value;
}

/*
///ScriptDocBegin
"Name: RVB_set_wet_level( <reverb>, <value> )"
"Summary: Twiddles the wet level 'knob' of the given reverb. "
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <reverb> : A valid EQ struct with which to twiddle."
"MandatoryArg: <value> : The twiddled value of the wet level."
"Example: RVB_set_wet_level(myReverbStruct, 0.8);
"SPMP: singleplayer"
///ScriptDocEnd
*/
RVB_set_wet_level(reverb, value)
{
	/#
	RVBx_validate(reverb);
	#/
	value = clamp(value, 0, 1.0);
	reverb.wetlevel = value;
}

/*
///ScriptDocBegin
"Name: RVB_apply_reverb( <reverb>, <fade_time_> )"
"Summary: Applies the given reverb. "
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <reverb> : A valid reverb struct with which to apply."
"OptionalArg: <fade_time_> : A fade time override of the reverb struct preset."
"Example: RVB_apply_reverb(myReverbStruct);
"SPMP: singleplayer"
///ScriptDocEnd
*/
RVB_apply_reverb(reverb, fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	assert(IsDefined(level._audio));
	assert(IsDefined(level._audio.reverb));
	/#
	RVBx_validate(reverb); 
	#/
	
	// Apply reverb if not already applied.
	if (!IsDefined(level._audio.reverb.applied_reverb) || (level._audio.reverb.applied_reverb != reverb))
	{
		// Store most recently applied reverb for later queries.
		level._audio.reverb.applied_reverb = reverb;
		
		fade_time = undefined;
		if (IsDefined(fade_time_))
		{
			assert(fade_time_ >= 0.0);
			fade_time = fade_time_;
		}
		else
		{
			fade_time = reverb.fadetime;
		}
		assert(IsDefined(fade_time));
		
		// Apply the reverb.
		level.player SetReverb(reverb.priority, reverb.roomtype, reverb.drylevel, reverb.wetlevel, fade_time);
	}
}

/*
///ScriptDocBegin
"Name: RVB_start_reverb_preset( <reverb_preset_name>, <fade_time_> )"
"Summary: Applies the given reverb preset. "
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <reverb_preset_name> : A valid reverb preset name with which to apply."
"OptionalArg: <fade_time_> : An optional override fadetime between reverbs."
"Example: RV_apply_reverb_preset("my_reverb_preset");
"SPMP: singleplayer"
///ScriptDocEnd
*/

RVB_start_preset(reverb_name, fade_time_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/

	// red flashing overwrites 
	if ( level.player maps\_utility::ent_flag( "player_has_red_flashing_overlay" ) )
	{
		// store this request to set reverb during red_flashing_overlay so that when it turns off
		// it can restore the reverb to what it would be. This happens when setting reverb during deathsdoor
		
		if (IsDefined(reverb_name) && reverb_name != "none")
		{
			reverb = RVBx_get_reverb_preset(reverb_name);
			if (!IsDefined(reverb))
			{
				aud_print_warning("Failed to load reverb preset: " + reverb_name);
				return; // failed to load
			}
			if (reverb_name != "deathsdoor") // need to store non-deathsdoor reverb settings
			{
				RVBx_store_current_reverb_track(reverb_name, reverb);
				// if reverb is getting set *while* the ref flashing overlay is happening, then it is set during
				// the deathsdoor sequence, which means we need to update teh deathsdoor reverb
				level._audio.deathsdoor.reverb = reverb_name;
			}
		}
		else
		{
			RVBx_store_current_reverb_track("none", undefined);
			level._audio.deathsdoor.reverb = "none";
		}
		return;
	}

	if (((IsDefined(reverb_name) && reverb_name == "none") || !IsDefined(reverb_name)) 
			&& IsDefined(level._audio.current_reverb)) // is ok to have an undefined reverb_name (deathsdoor)
	{
		// this needs to be deactivated if the reverb_name is undefined
		level.player DeactivateReverb( "snd_enveffectsprio_level", 1 );
		/#
		set_reverb_hud("");
		#/
		level._audio.current_reverb = undefined; // can be "deathsdoor"
		level._audio.reverb.current_reverb = ""; // reverb-internal flag, can never be "deathsdoor"
		return;
	}
	else if (!IsDefined(reverb_name) || (IsDefined(reverb_name) && reverb_name == "none"))
	{
		return;
	}

	reverb = RVBx_get_reverb_preset(reverb_name);
	if (!IsDefined(reverb))
	{
		aud_print_warning("Failed to load reverb preset: " + reverb_name);
		return; // failed to load
	}

	level._audio.current_reverb = reverb_name; // used to keep track of current reverb 
	
	// this is deprecated (leaving it in for now... 2/11/2011)
	if (reverb_name != "deathsdoor") // need to store non-deathsdoor reverb settings
	{
		RVBx_store_current_reverb_track(reverb_name, reverb);
	}
	
	if (level._audio.reverb.current_reverb != reverb_name)
	{
	  level._audio.reverb.current_reverb = reverb_name;
		assert(IsDefined(reverb));
		RVB_apply_reverb(reverb, fade_time_);

		/#
		set_reverb_hud(reverb_name);
		#/
	}
}

RVBx_store_current_reverb_track(reverb_name, reverb)
{
	assert(IsString(reverb_name));
	// update this global variable used by other script systems (i.e. pain system)
	assert(IsDefined(level.reverb_track));
	if (reverb_name != "deathsdoor") // deathsdoor requires the data to be stored, temp fix
	{
		level.reverb_track = reverb_name;
		assert(IsArray(level.ambient_reverb));
		if (reverb_name == "none" && !IsDefined(level.ambient_reverb["none"]))
		{
			level.ambient_reverb["none"] = true;
		}
		else if (!IsDefined(level.ambient_reverb[reverb_name]))
		{
			assert(IsDefined(reverb));
			level.ambient_reverb[reverb_name] = [];
			level.ambient_reverb[reverb_name]["priority"] = "snd_enveffectsprio_level";
			level.ambient_reverb[reverb_name]["roomtype"] = reverb.roomtype;
			level.ambient_reverb[reverb_name]["drylevel"] = reverb.drylevel;
			level.ambient_reverb[reverb_name]["wetlevel"] = reverb.wetlevel;
			level.ambient_reverb[reverb_name]["fadetime"] = reverb.fadetime;
		}
	}
}


RVB_deactive_reverb()
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	level.reverb_track = "";
	level.player deactivatereverb( "snd_enveffectsprio_level", 2 );
	

	/#
	set_reverb_hud("");
	#/
	level._audio.current_reverb = undefined; // can be "deathsdoor"
	level._audio.reverb.current_reverb = ""; // reverb-internal flag, can never be "deathsdoor"
}


/*
///ScriptDocBegin
"Name: RVB_get_applied_reverb()"
"Summary: Returns most recently applied reverb. "
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: None"
"Example: current_reverb = RVB_get_applied_reverb();
"SPMP: singleplayer"
///ScriptDocEnd
*/
RVB_get_applied_reverb()
{
	reverb = undefined;
	assert(IsDefined(level._audio));
	assert(IsDefined(level._audio.reverb));
	
	if (IsDefined(level._audio.reverb.applied_reverb))
	{
		reverb = level._audio.reverb.applied_reverb;	
	}	

	return reverb;
}


/********************
* PRIVATE FUNCTIONS *
*********************/

RVBx_get_preset_from_string_table(presetname, checklevel)
{
	assert(IsDefined(checklevel));
	assert(IsString(presetname));

	level_stringtable = maps\_audio::get_reverb_stringtable();	
	common_stringtable = "soundtables/common_reverb.csv";
	preset = [];
	
	/#
	if (aud_check_fastfiles()) return preset;
	#/

	if (checklevel)
		preset = RVBx_get_reverb_preset_from_stringtable_internal(level_stringtable, presetname);

	if (!IsDefined(preset) || preset.size == 0)
		preset = RVBx_get_reverb_preset_from_stringtable_internal(common_stringtable, presetname);

	if (!IsDefined(preset) || preset.size == 0)
	{
		return;
	}

	return preset;
}

RVBx_get_reverb_preset_from_stringtable_internal(stringtable, presetname)
{
	assert(IsString(stringtable));
	assert(IsString(presetname));
	
	preset = [];
	paramname = "";
	value = "";

	numparams = 6;
	for (i = 1; i < numparams; i++)
	{
		paramname = tablelookup(stringtable, 0, "reverb_names", i);
		value = tablelookup(stringtable, 0, presetname, i);	

		if (paramname != "comments" && value != "")
		{
			if (paramname != "roomtype")
				preset[paramname] = float(value);
			else
				preset[paramname] = value;
		}
	}
	
	return preset;
}


/#
RVBx_validate_preset_array(preset, name)
{
	assert(IsDefined(preset));
	assert(IsDefined(name));
	
	is_valid = true;
	reason = "";
	
	RVBx_construct_reverb_room_type_array();
	
	if (!IsDefined(preset["roomtype"]))
	{
		is_valid = false;
		reason = "roomtype is not defined.";
	}
	else if (!IsDefined(preset["drylevel"]))
	{
		is_valid = false;
		reason = "drylevel is not defined.";
	}
	else if (!IsDefined(preset["wetlevel"]))
	{
		is_valid = false;
		reason = "wetlevel is not defined.";
	}
	else if (!IsDefined(preset["fadetime"]))
	{
		is_valid = false;
		reason = "fadetime is not defined.";
	}
	else if (!IsDefined(level._audio.reverb.roomtypes[preset["roomtype"]]))
	{
		is_valid = false;
		reason = "roomtype is unknown.";
	}
	else if (preset["drylevel"] < 0.0 || preset["drylevel"] > 1.0)
	{
		is_valid = false;
		reason = "drylevel is invalid (" + preset["drylevel"] + ").";
	}
	else if (preset["wetlevel"] < 0.0 || preset["wetlevel"] > 1.0)
	{
		is_valid = false;
		reason = "wetlevel is invalid (" + preset["wetlevel"] + ").";
	}
	else if (preset["fadetime"] < 0.0)
	{
		is_valid = false;
		reason = "fadetime is invalid (" + preset["fadetime"] + ").";
	}
	
	if (!is_valid)
	{
		assertEx(false, "REVERB PRESET '" + name + "' IS INVALID! reason: " + reason);
	}
}
#/

// Wait until player is actually created before applying inital reverb.
RVBx_apply_inital_reverb()
{
	while (!IsDefined(level.player))
	{
		wait(0.5);
	}
	RVB_apply_reverb(level._audio.reverb.default_reverb);
}

RVBx_get_reverb_preset(name)
{
	assert(IsDefined(name));
	
	if (!IsDefined(level._audio.reverb.preset_cache))
		level._audio.reverb.preset_cache = [];
		
	// create the reverb struct
	reverb = RVBx_create(); 
	
	reverb_preset = [];
	if (IsDefined(level._audio.level_audio_reverb_function))
	{
		reverb_preset = [[ level._audio.level_audio_reverb_function ]](name, reverb_preset);
	}
	else if (IsDefined(level._audio.reverb.preset_cache[name]))
	{
		reverb_preset = level._audio.reverb.preset_cache[name];
	}
	else if (level._audio.reverb.use_string_table_presets)
	{
		reverb_preset = RVBx_get_preset_from_string_table(name, true); // check level and common
		if (!IsDefined(reverb_preset))
		{
			/#
			aud_print_error("failed to load reverb preset: " + name);
			#/
			return;
		}
		level._audio.reverb.preset_cache[name] = reverb_preset;
	}
	else
	{
		reverb_preset = RVBx_get_preset_from_string_table(name, false); // check common
		if (!IsDefined(reverb_preset) || reverb_preset.size == 0)
			reverb_preset = AUDIO_PRESETS_REVERB(name, reverb_preset);
			
		if (!IsDefined(reverb_preset))
		{
			/#
			aud_print_error("failed to load reverb preset: " + name);
			#/
			return;			
		}
		level._audio.reverb.preset_cache[name] = reverb_preset;
	}
	
	/#
	// validate preset for non-programmers, so they can track down bugs more easily
	RVBx_validate_preset_array(reverb_preset, name);
	#/
		
	// but we use the struct here because it makes more sense for reverbs since we don't iterate
	reverb.name 		= name;
	reverb.roomtype = reverb_preset["roomtype"];
	reverb.drylevel = reverb_preset["drylevel"];
	reverb.wetlevel = reverb_preset["wetlevel"];
	reverb.fadetime = reverb_preset["fadetime"];
	
	/#
	// this validates the reverb struct (not the preset array) and is more programmer-y.
	RVBx_validate(reverb);
	#/
	return reverb;
}

//Creates a new reverb struct with default values.
RVBx_create()
{
	reverb = spawnstruct();
	reverb.roomtype = "generic"; // just use the generic roomtype
	reverb.drylevel = 1.0; // these default values are derived from code. We always give these values in the reverb struct so that the script calls are simpler
	reverb.wetlevel = 0.5;
	reverb.fadetime = 0;
	reverb.priority = "snd_enveffectsprio_level"; // 99% of the time, this will be this priority. The other possibility is "snd_enveffectsprio_shellshock"
	return reverb;
}

/#

// Performs a validation on the given reverb struct.
RVBx_validate(reverb)
{
	assert(IsDefined(reverb.roomtype));
	RVBx_validate_room_type(reverb.roomtype);
	
	assert(IsDefined(reverb.drylevel));
	assert(reverb.drylevel >= 0 && reverb.drylevel <= 1.0);
	
	assert(IsDefined(reverb.wetlevel));
	assert(reverb.wetlevel >= 0 && reverb.wetlevel <= 1.0);

	assert(IsDefined(reverb.fadetime));
	assert(reverb.fadetime >= 0);
}
#/


/#

//A function which ensures that a reverb roomtype is valid. This list is pulled from xareverb.def.
RVBx_validate_room_type(room)
{
	RVBx_construct_reverb_room_type_array();
	assert(IsDefined(level._audio.reverb.roomtypes));
	assert(IsDefined(level._audio.reverb.roomtypes[room]));
}
#/

/#
RVBx_construct_reverb_room_type_array()
{
	if (!IsDefined(level._audio.reverb.roomtypes))
	{
		roomtypes = [];
		roomtypes["generic"] = true;
		roomtypes["paddedcell"] = true;
		roomtypes["room"] = true;
		roomtypes["bathroom"] = true;
		roomtypes["livingroom"] = true;
		roomtypes["generic"] = true;
		roomtypes["stoneroom"] = true;
		roomtypes["auditorium"] = true;
		roomtypes["concerthall"] = true;
		roomtypes["cave"] = true;
		roomtypes["arena"] = true;
		roomtypes["hangar"] = true;
		roomtypes["carpetedhallway"] = true;
		roomtypes["hallway"] = true;
		roomtypes["stonecorridor"] = true;
		roomtypes["alley"] = true;
		roomtypes["forest"] = true;
		roomtypes["city"] = true;
		roomtypes["mountains"] = true;
		roomtypes["quarry"] = true;
		roomtypes["plain"] = true;				
		roomtypes["parkinglot"] = true;
		roomtypes["sewerpipe"] = true;	
		roomtypes["underwater"] = true;
		roomtypes["drugged"] = true;
		roomtypes["dizzy"] = true;
		roomtypes["psychotic"] = true;
		assert(roomtypes.size == 26);
		level._audio.reverb.roomtypes = roomtypes;
	}
}
#/
