#include maps\_utility;
#include common_scripts\utility;
#include maps\_audio;
#include maps\_audio_stream_manager;
#include maps\_audio_mix_manager;
#include maps\_audio_presets_music;

/********************************************************************
 Public Music Cue Functions.
********************************************************************/
MUS_init()
{
	/*** Init Music Globals. ***/
	if (!IsDefined(level._audio))
	{
		level._audio = SpawnStruct();	
	}	
	level._audio.music										= SpawnStruct();	
	level._audio.music.cue_cash						= [];
	level._audio.music.curr_cue_name			= "";
	level._audio.music.prev_cue_name			= "";
	level._audio.music.enable_auto_mix		= false;

	level._audio.music.env_threat_to_vol	= [ 
		[0.0, 0.5], 
		[0.9, 1.0], 
		[1.0, 1.0] 
	];
	
	/*** Launch Thread to Monitor Game Variables that Affect Music. ***/
	thread MUSx_monitor_game_vars();
}

/*
///ScriptDocBegin
"Name: MUS_play()"
"Summary: Plays a music alias."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <alias> alias name."
"OptionalArgs: <fade_in_time_> : fade time in seconds, <cross_fade_out_time_> : prev cue fade out time in seconds, <volume_> : volume scalar, <forceplay_> : fprces a retrigger even if already playing."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MUS_play(alias, fade_in_time_, cross_fade_out_time_, volume_, forceplay_)
{	
	/#
	if (aud_get_enable_music() == 0)
	{
		return;
	}
	#/
	
	stop_adaptive_music_ = undefined; // obsolete.
	
	/#
	if (!aud_get_enable_music())
	{
		return;
	}
	aud_print("MUS ALIAS: " + alias, "music");
	#/
	
	// Get Currently playing cue if any.
	curr_cue = MUS_get_playing_cue_preset();
	
	// Construct new or retrieve cashed cue preset.
	new_cue = MUSx_construct_cue(alias); 
							// Note:  this is the only place in the code that should call this function; use MUSx_get_cashed_cue().
	/#
		MUSx_validate_cue(new_cue);
	#/

	// Allow for behavior override via optional params.
	
	// Determine fade-in time of new cue.
	fade_in_time = new_cue["fade_in_time"];
	if (IsDefined(fade_in_time_))	
	{
		fade_in_time = fade_in_time_;
	}
	
	// Determine fade-out time of currently playing cue (if playing).
	cross_fade_out_time = 2.0;
	if (IsDefined(curr_cue))
	{
		if (IsDefined(cross_fade_out_time_))
		{
			cross_fade_out_time = cross_fade_out_time_;
		}
		else if (IsDefined(fade_in_time_))
		{
			cross_fade_out_time = fade_in_time_;
		}
		else if (IsDefined(curr_cue["fade_out_time"]))
		{
			cross_fade_out_time = curr_cue["fade_out_time"];
		}
	}

	// Determine volume scale of new cue.
	volume = new_cue["volume"];
	if (IsDefined(volume_))	
	{
		volume = volume_;
	}
		
	// Start new music cue.
	MUSx_start_cue(new_cue["name"], fade_in_time, cross_fade_out_time, volume, forceplay_);	
}

/*
///ScriptDocBegin
"Name: MUS_stop()"
"Summary: Stops a music alias."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: non."
"OptionalArgs: <fade_out_time_> : fade out time in seconds."
"SPMP: singleplayer"
///ScriptDocEnd
*/
MUS_stop(fade_out_time_)
{
	fade_out_time = 3.0; // Assume default.
	if (MUS_is_playing())
	{
		cue = MUSx_get_cashed_cue(level._audio.music.curr_cue_name);
		/#
			MUSx_validate_cue(cue);
		#/
		fade_out_time = cue["fade_out_time"];	// Default to curr playing cue fade time if exists.
	}
	
	if (IsDefined(fade_out_time_))		// Allow override of cue fade out time.
	{
		fade_out_time = fade_out_time_;
	}
	
	MUSx_stop_all_music(fade_out_time);
}


// Returns true if there is a cue currently playing.
MUS_is_playing()
{
	assert(IsDefined(level._audio) && IsDefined(level._audio.music));
	
	return IsDefined(level._audio.music.curr_cue_name) && level._audio.music.curr_cue_name != "";
}

// Returns currently playing cue or undefined if no cue is playing.
MUS_get_playing_cue_preset()
{
	cue_preset = undefined;
	
	assert(IsDefined(level._audio) && IsDefined(level._audio.music));
	
	if (MUS_is_playing())
	{
		assert(IsDefined(level._audio.music.curr_cue_name));
		cue_preset = MUSx_get_cashed_cue(level._audio.music.curr_cue_name);
	}
	
	return cue_preset;
}

/********************************************************************
	Private Music Functions.
********************************************************************/

// Takes a music cue preset name and returns a cue struct.
MUSx_construct_cue(name)
{
	assert(IsDefined(name));
	
	// First see if we've already been here and cashed it.
	result = MUSx_get_cashed_cue(name);
	
	if (!IsDefined(result))
	{
		// Fill in default preset values.
		result = [];
		result["alias"]					= name;
		result["volume"]				= 1.0;
		result["fade_in_time"]	= 1.5;
		result["fade_out_time"]	= 1.5;
		result["auto_mix"]			= false;	
		
		// Designer not allowed to change this:
		result["name"] = name;
					
		MUSx_cash_cue(result);
	}
	/#
	MUSx_validate_cue(result);
	#/
	return result;
}

MUSx_start_cue(new_cue_name, fade_in_time, cross_fade_out_time, volume, forceplay_)
{
	assert(IsDefined(new_cue_name) && IsString(new_cue_name));
	assert(IsDefined(fade_in_time));
	assert(IsDefined(cross_fade_out_time));
	
	forceplay = false;
	
	if (IsDefined(forceplay_))
		forceplay = forceplay_;
		
	if (new_cue_name == level._audio.music.curr_cue_name && !forceplay)
	{
		return; // SAME CUE ALREADY PLAYING: Ignore request to prevent double-triggering.
	}
	else
	{
		/*
			Set curr/prev mus state variables BEFORE calling any other functions/threads/waits to avoid 
			a new request coming in during a wait() somewhere ***BEFORE*** this thread exits,
			resulting in potentially double-triggering the same cue.
		*/
		// Save for use later.
		prev_cue_name	= level._audio.music.prev_cue_name;
		curr_cue_name	= level._audio.music.curr_cue_name;
		// Update global state vars.
		level._audio.music.prev_cue_name	= level._audio.music.curr_cue_name;
		level._audio.music.curr_cue_name	= new_cue_name;
		
		
		
		/*** Start New Music ***/
		new_cue  = MUSx_get_cashed_cue(level._audio.music.curr_cue_name);
		prev_cue = MUSx_get_cashed_cue(level._audio.music.prev_cue_name);
		prev_cue_alias = undefined;
		if (IsDefined(prev_cue))
		{
			prev_cue_alias = prev_cue["alias"];
		}
		
		/#
		MUSx_validate_cue(new_cue);
		#/
		SM_start_music(new_cue["alias"], fade_in_time, cross_fade_out_time, volume, prev_cue_alias); //SM_start_music(alias, fade_, volscale_, alias_to_kill_, priority_, interrupt_fade_)
	}
}

MUSx_stop_all_music(fade_time)
{
	assert(IsDefined(fade_time));	// Defaults should be handled above this call.
	SM_stop_music(fade_time);
}

MUSx_get_auto_mix()
{
	return level._audio.music.enable_auto_mix;
}

MUSx_get_cashed_cue(cue_name)
{
	/#
		MUSx_validate_globals();
	#/
	return level._audio.music.cue_cash[cue_name];
}

MUSx_cash_cue(cue_preset)
{
	/#
		MUSx_validate_cue(cue_preset);
	#/
	level._audio.music.cue_cash[cue_preset["name"]] = cue_preset;
}	

MUSx_monitor_game_vars()
{
	if (MUSx_get_auto_mix())
	{
		CONST_updatePeriod = 1.0; //0.25;
				
		while (1)
		{
			wait(CONST_updatePeriod);
		
			if (MUSx_get_auto_mix())
			{
				threat_level = aud_get_threat_level();
				
				mus_scalar = aud_map(threat_level, level._audio.music.env_threat_to_vol);
				
				// SCALE MUSIC HERE IF FEATURE IS ENABLED IN THE CURRENTLY PLAYING MUSIC CUE.
				//TODO: look at this in the future - dv
				//MM_perform_music_auto_fade(mus_scalar, 5.0);
			}
		}
	}
}

/#
MUSx_validate_globals()
{
	assert(IsDefined(level._audio));
	assert(IsDefined(level._audio.music));
	assert(IsDefined(level._audio.music.cue_cash));
	assert(IsDefined(level._audio.music.curr_cue_name));
	assert(IsDefined(level._audio.music.prev_cue_name));
	assert(IsDefined(level._audio.music.enable_auto_mix));
	assert(IsDefined(level._audio.music.env_threat_to_vol));
}

MUSx_validate_cue(preset)
{
	assertEx(IsDefined(preset), "Music cue preset is undefined.");
	assertEx(IsDefined(preset["name"]), "Music cue preset has no name.");
	assertEx(IsString(preset["name"]), "Music cue preset name is not a string.");
	assertEx(IsDefined(preset["alias"]), "Music cue " + preset["name"] + " has an undefined alias.");
	assertEx(IsString(preset["alias"]), "Music cue " + preset["name"] + " has an alias that is not a string.");
	assertEx(IsDefined(preset["volume"]), "Music cue " + preset["name"] + " has no volume param.");
	assertEx(IsDefined(preset["fade_in_time"]), "Music cue " + preset["name"] + " has no fade_in_time param.");
	assertEx(IsDefined(preset["fade_out_time"]), "Music cue " + preset["name"] + " has no fade_out_time param.");
	assertEx(IsDefined(preset["auto_mix"]), "Music cue " + preset["name"] + " has no auto_mix param.");
}
#/



