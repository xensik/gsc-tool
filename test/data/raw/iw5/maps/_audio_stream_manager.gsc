#include maps\_utility_code;
#include maps\_utility;
#include common_scripts\utility;
#include maps\_audio;

/*
///ScriptDocBegin
"Name: SM_init()"
"Summary: Initializes the streamed audio manager. This should be done at the beginning of a level. "
"Module: Audio"
"CallOn: Nothing"
"SPMP: singleplayer"
///ScriptDocEnd
*/
SM_init()
{
	assert(IsDefined(level._audio));
	
	// structs for debugging purposes
	level._audio.stream = spawnstruct();
	
	level._audio.stream.music = spawnstruct();
	level._audio.stream.music.curr = SMx_create_struct();
	level._audio.stream.music.prev = SMx_create_struct();
	
	level._audio.stream.ambience = spawnstruct();
	level._audio.stream.ambience.curr = SMx_create_struct();
	level._audio.stream.ambience.prev = SMx_create_struct();
}

/*
///ScriptDocBegin
"Name: SM_start_preset(<alias>, <fade>, <priority>, <interrupt_fade>, <volscale>)"
"Summary: Starts a streamed ambience with the streamed ambience manager."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <alias> : A valid sound alias to stream in the streamed audio manager. Can have a single secondary alias (to play a quad streamed ambienc)."
"OptionalArg: <fade> : A fade in time for the streamed ambience (in seconds)."
"OptionalArg: <priority> : A number indicating relative priority of this streamed ambience. A lower priority stream will be stopped quickly if a SM_start is called fo ra new ambience."
"OptionalArg: <interrupt_fade> : How fast this ambience will fade out a lower priority stream if needed."
"OptionalArg: <volscale> : A starting volume scale for the streamed ambience."
"OptionalArg: <specops_player_> : Which specops player the stream is for (1 or 2)."
"SPMP: singleplayer"
///ScriptDocEnd
*/
SM_start_preset(alias, fade_, priority_, interrupt_fade_, volscale_)
{
	assert(IsDefined(alias));

	fadetime = 1.0;
	if (IsDefined(fade_))
	{
		fadetime = max(fade_, 0);
	}
		
	volscale = 1.0;
	if (IsDefined(volscale_))
	{
		volscale = max(volscale_, 0);
	}
	
	SMx_set_values_for_struct(level._audio.stream.ambience.prev, level._audio.stream.ambience.curr.name, level._audio.stream.ambience.curr.vol, level._audio.stream.ambience.curr.fade);
	SMx_set_values_for_struct(level._audio.stream.ambience.curr, alias, volscale, fadetime);
	
	/#
	set_stream_hud(alias);
	set_stream_to_hud("", "");
	set_stream_from_hud("", "");
	#/
	
	ambientplay(alias, fadetime, volscale);
}

SM_start_music(alias, fade_in_time_, cross_fade_out_time_, volscale_, prev_alias)
{
	assert(IsDefined(alias));
	
	fadetime = 1.0;
	if (IsDefined(fade_in_time_))
	{
		fadetime = max(fade_in_time_, 0);
	}
	
	fadeouttime = 1.0;
	if (IsDefined(cross_fade_out_time_))
	{
		fadeouttime = cross_fade_out_time_;
	}
	
	volscale = 1.0;
	if (IsDefined(volscale_))
	{
		volscale = max(volscale_, 0);
	}

	SMx_set_values_for_struct(level._audio.stream.music.prev, level._audio.stream.music.curr.name, level._audio.stream.music.curr.vol, level._audio.stream.music.curr.fade);
	SMx_set_values_for_struct(level._audio.stream.music.curr, alias, volscale, fadetime);	
	
	/#
	set_music_hud(alias);
	#/
	
	if (IsDefined(prev_alias))
	{
		musicstop(fadeouttime, prev_alias);
		musicplay(alias, fadetime, volscale, false); // not exclusive
	}
	else
	{
		musicplay(alias, fadetime, volscale);
	}
}

/*
///ScriptDocBegin
"Name: SM_stop_alias(<alias>, <fade>, <force_sync>)"
"Summary: Stops the indicated alias if it is playing."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <alias> : A valid sound alias to stop in the streamed audio manager. Can have a single secondary alias (to play a quad streamed ambienc)."
"OptionalArg: <fade> : A fade out time (in seconds)."
"SPMP: singleplayer"
///ScriptDocEnd
*/
SM_stop_ambient_alias(alias, fade_)
{
	assert(IsDefined(alias));
	
	if (alias != "none")
	{
		fade = 1.0;
		if (IsDefined(fade_))
		{
			fade = max(fade_, 0);
		}
		
		if (level._audio.stream.ambience.curr.name == alias)
		{
			level._audio.stream.ambience.curr = level._audio.stream.ambience.prev;
			/#
			set_stream_hud("");
			set_stream_to_hud("", "");
			set_stream_from_hud("", "");
			#/
			SMx_clear_struct(level._audio.stream.ambience.prev);
		}
		else if (level._audio.stream.ambience.prev.name == alias)
		{
			SMx_clear_struct(level._audio.stream.ambience.prev);
		}
	
		ambientstop(fade, alias);
	}
}

/*
///ScriptDocBegin
"Name: SM_stop_music_alias(<alias>, <fade>)"
"Summary: Stops the indicated alias if it is playing."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <alias> : A valid sound alias to stop in the streamed audio manager. Can have a single secondary alias (to play a quad streamed ambienc)."
"OptionalArg: <fade> : A fade out time (in seconds)."
"OptionalArg: <force_sync> : Boolean indicating whether or not the thread which calls this function is paused for the duration of the fade-out."
"SPMP: singleplayer"
///ScriptDocEnd
*/
SM_stop_music_alias(alias, fade_)
{
	assert(IsDefined(alias));
	
	fade = 1.0;
	if (IsDefined(fade_))
	{
		fade = max(fade_, 0);
	}
	
	if (level._audio.stream.music.curr.name == alias)
	{
		level._audio.stream.music.curr = level._audio.stream.music.prev;
		SMx_clear_struct(level._audio.stream.music.prev);
	}
	else if (level._audio.stream.ambience.prev.name == alias)
	{
		SMx_clear_struct(level._audio.stream.music.prev);
	}
	
	musicstop(fade, alias);
}

/*
///ScriptDocBegin
"Name: SM_stop_ambience(<fade>)"
"Summary: Stops all the ambiences."
"Module: Audio"
"CallOn: Nothing"
"OptionalArg: <fade> : A fade out time (in seconds)."
"SPMP: singleplayer"
///ScriptDocEnd
*/
SM_stop_ambience(fade_)
{
	fade = 1.0;
	if (IsDefined(fade_))
		fade = fade_;
		
	/#
	SMx_clear_struct(level._audio.stream.ambience.curr);
	SMx_clear_struct(level._audio.stream.ambience.prev);
	// update the zone hud
	set_stream_hud("");
	set_stream_from_hud("", "");
	set_stream_to_hud("", "");
	#/

	ambientstop(fade);
}

/*
///ScriptDocBegin
"Name: SM_stop_music(<fade>)"
"Summary: Stops all the music."
"Module: Audio"
"CallOn: Nothing"
"OptionalArg: <fade> : A fade out time (in seconds)."
"SPMP: singleplayer"
///ScriptDocEnd
*/
SM_stop_music(fade_)
{
	fade = 1.0;
	if (IsDefined(fade_))
		fade = fade_;
		
	SMx_clear_struct(level._audio.stream.music.curr);
	SMx_clear_struct(level._audio.stream.music.prev);
	
	musicstop(fade);
}

/*
///ScriptDocBegin
"Name: SM_mix_ambience(<info_array>)"
"Summary: Mixes two ambience streams together according to the structure of the info_array."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <info_array> : An array of structs with a set of required arguments: alias and volume."
"SPMP: singleplayer"
///ScriptDocEnd
*/
SM_mix_ambience(info_array)
{
	assert(IsArray(info_array));	
	assert(info_array.size <= 2 && info_array.size > 0);
	
	threshold = 0.009;
	
	if (info_array.size == 1)
	{
		/#
		set_stream_from_hud("", "");
		
		if (info_array[0].vol < threshold || 1.0 - info_array[0].vol < threshold)
		{
			set_stream_to_hud("", "");
			if (1.0 - info_array[0].vol < threshold)
				set_stream_hud(info_array[0].alias);
			else
				set_stream_hud("");
		}
		else
			set_stream_to_hud(info_array[0].alias, info_array[0].vol);
		#/
		SMx_set_values_for_struct(level._audio.stream.ambience.curr, info_array[0].alias, info_array[0].vol, info_array[0].fade);
	}
	else if (info_array.size == 2) // 0 is from, 1 is to
	{
		/#
		// if either close to zero or close to 1
		to_is_close = false;
		if (info_array[1].vol < threshold || 1.0 - info_array[1].vol < threshold)
			to_is_close = true;
			
		from_is_close = false;
		if (info_array[0].vol < threshold || 1.0 - info_array[0].vol < threshold)
			from_is_close = true;
			
		alias0 = info_array[0].alias;
		if (alias0 == "none")
			alias0 = "";
		
		alias1 = info_array[1].alias;
		if (alias1 == "none")
			alias1 = "";
		
		if (to_is_close && from_is_close)
		{
			set_stream_to_hud("", "");
			set_stream_from_hud("", "");
				
			if (info_array[0].vol > info_array[1].vol)
				set_stream_hud(alias0);
			else
				set_stream_hud(alias1);
		}
		else
		{
			set_stream_to_hud(alias1, info_array[1].vol);
			set_stream_from_hud(alias0, info_array[0].vol);
			set_stream_hud("blending");
		}
		#/
		SMx_set_values_for_struct(level._audio.stream.ambience.prev, info_array[0].alias, info_array[0].vol, info_array[0].fade);
		SMx_set_values_for_struct(level._audio.stream.ambience.curr, info_array[1].alias, info_array[1].vol, info_array[1].fade);
	}
		
	for (i = 0; i < info_array.size; i++)
	{
		assert(IsDefined(info_array[i].alias));
		assert(IsDefined(info_array[i].vol));
		assert(IsDefined(info_array[i].fade));
		
		alias = info_array[i].alias;
		vol = max(info_array[i].vol, 0);
		fade = clamp(info_array[i].fade, 0, 1);

		if (alias != "none")
		{
			if (vol < threshold)
				ambientstop(fade, alias);
			else
				ambientplay(alias, fade, vol, false); // non-exclusive mix
		}
	}
}

SM_get_current_ambience_name()
{
	return level._audio.stream.ambience.curr.name;
}

SM_get_current_music_name()
{
	return level._audio.stream.music.curr.name;
}

SMx_set_values_for_struct(struct, name, vol, fade)
{
	struct.name = name;
	struct.vol = vol;
	struct.fade = fade;
}


SMx_create_struct()
{
	struct = spawnstruct();
	struct.name = "";
	struct.vol = 0.0;
	struct.fade = 0.0;
	
	return struct;
}


SMx_clear_struct(input_struct)
{
	input_struct.name = "";
	input_struct.vol = 0.0;
	input_struct.fade = 0.0;
}


