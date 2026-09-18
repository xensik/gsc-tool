#include maps\_utility_code;
#include maps\_utility;
#include maps\_audio_reverb;
#include maps\_audio_stream_manager;
#include maps\_audio_dynamic_ambi;
#include maps\_audio_zone_manager;
#include common_scripts\utility;
#include maps\_audio_music;
#include maps\_audio_mix_manager;
#include maps\_audio_whizby;
#include maps\_audio_vehicles;
#include maps\_shg_common;

//-----------------------------------------------------------------------------------------------------
//	Audio Initialization.
//-----------------------------------------------------------------------------------------------------
aud_init()
{
	if (!IsDefined(level.aud)) // don't reinit audio if it's already been inited
	{
		if ( !isdefined( level.script ) )
			level.script = ToLower( GetDvar( "mapname" ) );
		
		level.aud = SpawnStruct();
	
		//	Init audio level global vars.
		if (!IsDefined(level._audio))
		{
			level._audio = SpawnStruct();	
		}	
		
		level._audio.using_string_tables = false;	
		level._audio.stringtables = []; // list of level stringtable names
		
		// Create a struct to index the preset files on load
		// to optimize loading finding presets
		index = spawnstruct();
		level._audio.index = spawnstruct();
		level._audio.index.local = get_index_struct(); // level-specific indices
		level._audio.index.common = get_index_struct(); // common indices
		index_common_presets();
		
		// Init Audio Message Receiver.
		level._audio.message_handlers = [];
		
		// Create Audio Callback Trigger - Callback Array
		level._audio.progress_trigger_callbacks = [];
		
		// Maps used for custom zone blending
		level._audio.progress_maps = [];
				
		level._audio.filter_disabled = false;
		level._audio.current_filter = "";
		level._audio.current_filter_indices = ["", ""];
		
		level._audio.zone_occlusion_and_filtering_disabled = false; // RAVEN jsypult: disable zone filter/occlusion processing but maintain zone presets
				
		// VO Duck State.
		level._audio.vo_duck_active = false;
		
		// Set up Player State struct for interactivity (e.g., music auto-fade).
		level._audio.sticky_threat							= undefined;
		level._audio.player_state								= SpawnStruct();
		level._audio.player_state.locamote			= "idle";
		level._audio.player_state.locamote_prev = "idle";
		
		// IW LEGACY VARIABLES:
		// variables used by many other script systems...
		level.ambient_reverb = [];
		level.ambient_track = []; 
		level.fxfireloopmod = 1;  // used in _fx.gsc.. 		
		level.reverb_track = "";
		level.eq_main_track = 0;
		level.eq_mix_track = 1;
		level.eq_track[ level.eq_main_track ] = "";
		level.eq_track[ level.eq_mix_track ] = "";
		
		// Init Stream Manager 
		SM_init();
		
		// Init Dynamic Ambience System 
		DAMB_init();
		
		// Audio Zone Triggers (NOTE: this is now being done in _load.gsc
		//trigger_multiple_audio_init();
		
		// Audio Zone Manager 
		AZM_init();
		
		// Audio Mix System
		thread MM_init();
		
		// Audio Reverb Manager
		RVB_init();
		
		// Music Cue Playback System
		MUS_init();
		
		// Initialize the Whizby Preset Parameters
		WHIZ_init();
		
		// Dynamic Vehicle System
		VM_init();
		
		// set up level fade in
		thread aud_level_fadein();		
		
		// mission-fail music thread
		thread aud_wait_for_mission_fail_music();
		
		// Register Level Audio Message Handler Function. 
		aud_register_msg_handler(::_audio_msg_handler);
		
		/#
		if (aud_get_enable_player_monitor())
		{
			thread aud_player_movement_monitor();
			//thread aud_ambi_scaler(level._audio.ambi_scaler_env);
		}
		#/
		
		/#
		// dvar-triggered debug modes/huds
		
		level._audio.using_ambi_hud = false;
		level._audio.using_volmod_submix_hud = false;
		level._audio.using_submix_hud = false;
		
		// used to store incoming hud sets so when hud is enabled
		// dynamically, it will display latest info
		level._audio.hud_input = spawnstruct();
		
		thread aud_dvar_monitor_thread();
		#/
		
		/#
		if (aud_get_godmode())
		{
			self.godmode = true;	// Set based on Launcher DVar
		}
		#/
	}
}

//////////////////////////////////////////////////////
// STUBS FOR OLD PRESET SYSTEM:

AUDIO_PRESETS_DYNAMIC_AMBIENCE(name, p)
{
	aud_print_error("CALLING DYNAMIC_AMBIENCE PRESET USING OLD METHOD!");
}

AUDIO_PRESETS_DYNAMIC_AMBIENCE_COMPONENTS(name, p)
{
	aud_print_error("CALLING DYNAMIC_AMBIENCE_COMPONENTS PRESET USING OLD METHOD!");
}

AUDIO_PRESETS_DYNAMIC_AMBIENCE_LOOP_DEFINITIONS(name, p)
{
	aud_print_error("CALLING DYNAMIC_AMBIENCE_LOOP_DEFINITIONS PRESET USING OLD METHOD!");
}

AUDIO_PRESETS_MIX(name, p)
{
	aud_print_error("CALLING MIX PRESET USING OLD METHOD!");
}

AUDIO_PRESETS_OCCLUSION(name, eq)
{
	aud_print_error("CALLING OCCLUSION PRESET USING OLD METHOD!");
}

AUDIO_PRESETS_REVERB(name, p)
{
	aud_print_error("CALLING REVERB PRESET USING OLD METHOD!");
}

AUDIO_PRESETS_WHIZBY(name, p)
{
	aud_print_error("CALLING WHIZBY PRESET USING OLD METHOD!");
}

AUDIO_PRESETS_ZONES(name, p)
{
	aud_print_error("CALLING ZONE PRESET USING OLD METHOD!");
}

//////////////////////////////////////////////////////
// STREAM PRIMING UTILITIES
////////////////////////////////////////////////////

/*
// use case example of stream priming with continual updating
myent aud_prime_stream(alias1, true); // prime streams using the constant re-prime method
myent aud_prime_stream(alias2, true); // can prime multiple streams

if (event) // wait for some event
{
	myent aud_release_stream(alias2);
	myent aud_wait_till_primed(alias1);
	// start animation here
	myent playsound(alias1);
}
else
{
	myent aud_release_stream(alias1);
	myent aud_wait_till_primed(alias2);
	// start animation here
	myent playsound(alias2);
}

////////////////////////////////////////////////////
// using the flag-based method (still waiting for the sound to prime):
myent aud_prime_stream(alias);

level waittill("some big event");
myent aud_wait_till_primed(alias);
// do animation here too
myent playsound(alias);

////////////////////////////////////////////////////
// ensuring that the priming is ready to go when needed 
// make sure the stream is playing on the highest priority channel
// or it might get stolen

myent aud_prime_stream(alias);
wait 5; // wait an appropriate amount

// now, some animation is ready to play
isprimed = myent aud_is_stream_primed(alias);
assert(isprimed);

// play animation
myent playsound(alias); // should be ready to go
*/

// call on entity to prime the alias
// this continually primes the stream if given update_, otherwise sets a flag when it's primed
aud_prime_stream(alias, update_, updaterate_)
{
	update = false;
	if (IsDefined(update_))
		update = update_;
		
	assert(IsString(alias));
	self endon("release" + alias);
	while(true)
	{
		self PrefetchSound(alias, "primed" + alias);
		self waittill("primed" + alias);
		if (!IsDefined(self.primed_streams))
			self.primed_streams = [];
			
		self.primed_streams[alias] = true;
		if (!update)
		{
			return;
		}
		else
		{
			if (IsDefined(updaterate_)) // optional update rate, otherwise immediately waits to prime again, which is ok
				wait updaterate_;
		}
	}
}

aud_is_stream_primed(alias)
{
	if (IsDefined(self.primed_streams) && IsDefined(self.primed_streams[alias]) && self.primed_streams[alias] )
		return true;
	else
		return false;
}

aud_error_if_not_primed(alias)
{
	/#
	if (self aud_is_stream_primed(alias) == false)
	{
		aud_print_error("alias " + alias + " is not primed.");
	}
	#/
}

// releases the stream from getting primed
aud_release_stream(alias, callstopsound_)
{
	callstopsound = false;
	if (IsDefined(callstopsound_))
		callstopsound = callstopsound_;
		
	self notify("release" + alias);
	if (callstopsound && IsDefined(self))
		self stopsounds();
}

// pauses the thread until the sound is notified that it is primed
aud_wait_till_primed(alias)
{
	if (IsDefined(self.primed_streams) && IsDefined(self.primed_streams[alias]) && self.primed_streams[alias])
		return;

	self waittill("primed" + alias);
	self notify("release" + alias);
}

aud_prime_and_play_internal(alias, wait_time, use_slowmo_)
{
	self aud_prime_stream(alias);
	if (IsDefined(use_slowmo_) && use_slowmo_)
	{
		aud_slomo_wait(wait_time);
	}
	else
	{
		wait(wait_time);
	}
	assert(self aud_is_stream_primed(alias));
	self playsound(alias, "sounddone");
	self waittill("sounddone");
	wait(0.05);
	self delete();
}

aud_prime_and_play(alias, wait_time, origin_, use_slowmo_)
{
	assert(IsDefined(alias));
	assert(IsDefined(wait_time));
	
	origin = level.player.origin;
	if (IsDefined(origin_))
	{
		origin = origin_;
	}
	
	ent = spawn("script_origin", origin);
	assert(IsDefined(ent));
	ent thread aud_prime_and_play_internal(alias, wait_time, use_slowmo_); // this function plays sound after the specified wait time then cleans up "ent"
	return ent;
}

////////////////////////////////////////////////////
// PROGRESS MAPPING FUNCTIONS
////////////////////////////////////////////////////

// add a named mapping array for custom progress/zone blending.
aud_add_progress_map(name, map_array)
{
	assert(IsDefined(level._audio.progress_maps));
	level._audio.progress_maps[name] = map_array;
}

aud_get_progress_map(name)
{
	assert(IsDefined(name));
	assert(IsDefined(level._audio.progress_maps));
	if (IsDefined(level._audio.progress_maps[name]))
		return level._audio.progress_maps[name];
}

////////////////////////////////////////////////////
// DEATHSDOOR FUNCTIONS
////////////////////////////////////////////////////

is_deathsdoor_audio_enabled()
{
	if (!IsDefined(level._audio.deathsdoor_enabled))
	{
		return true;
	}
	else
	{
		return level._audio.deathsdoor_enabled;
	}
}

aud_enable_deathsdoor_audio()
{
	level.player.disable_breathing_sound = false;
	level._audio.deathsdoor_enabled = true;
}

aud_disable_deathsdoor_audio()
{
	level.player.disable_breathing_sound = true;
	level._audio.deathsdoor_enabled = false;
}

// used to restore the state of occlusion, filter, and reverb after recovering from deathsdoor
restore_after_deathsdoor()
{
	if (is_deathsdoor_audio_enabled() || isdefined(level._audio.in_deathsdoor))
	{
		level._audio.in_deathsdoor = undefined;
		assert(IsDefined(level._audio.deathsdoor));
		// ok for these values to be undefined:
		thread aud_set_occlusion(level._audio.deathsdoor.occlusion);
		thread aud_set_filter(level._audio.deathsdoor.filter);
		thread RVB_start_preset(level._audio.deathsdoor.reverb);
	}
}

// used to send the game audio state to "deathsdoor". 
set_deathsdoor()
{
	level._audio.in_deathsdoor = true;
		
	if (!IsDefined(level._audio.deathsdoor))
	{
		level._audio.deathsdoor = spawnstruct();
	}
	
	// ok for these to be undefined:
	level._audio.deathsdoor.filter = undefined;
	level._audio.deathsdoor.occlusion = undefined;
	level._audio.deathsdoor.reverb  = undefined;
	
	// cache the current state of the filter, occlusion and reverb
	level._audio.deathsdoor.filter =  level._audio.current_filter;
	level._audio.deathsdoor.occlusion = level._audio.current_occlusion;
	level._audio.deathsdoor.reverb = level._audio.current_reverb;

	if (is_deathsdoor_audio_enabled())
	{	
		thread aud_set_filter("deathsdoor");
		thread RVB_start_preset("deathsdoor");
	}
}


////////////////////////////////////////////////////
// MISSION FAILED FUNCTIONS
////////////////////////////////////////////////////
aud_set_mission_failed_music(alias)
{
	level._audio.failed_music_alias = alias;
}

aud_wait_for_mission_fail_music()
{
	wait(0.05);
	assert(isDefined(level.flag));
	while (!flag_exist("missionfailed"))
	{
		wait(0.05);
	}

	music_alias = "shg_mission_failed_stinger";

	flag_wait("missionfailed");
	
	if (IsDefined(level._audio.failed_music_alias))
	{
		music_alias = level._audio.failed_music_alias;
	}
	
	if (SoundExists(music_alias))
	{
		MUS_play(music_alias, 2, 4);
	}
}

////////////////////////////////////////////////////
// FILTER PRESET FUNCTIONS
////////////////////////////////////////////////////

aud_set_filter_internal(presetname, stringtable, index, is_common)
{
	/#
	if (aud_check_fastfiles()) return;
	#/

	assert(IsString(presetname));
	assert(IsString(stringtable));
	assert(IsDefined(index));
	assert(IsDefined(level._audio.filter_presets[presetname])); // the cached array, needs to be defined before this function
	assert(IsDefined(is_common));
	
	numparams = 7;
	row_value = "";
	row_count = 0;
	preset = [];
	param_names = [];
	found_preset = false;
	empty_rows = 0;
	
	// grab the indexed row from this preset 
	index = get_indexed_preset("filter", presetname, is_common);
	if (index != -1)
	{
		row_count = index;
	}
	else if ((is_common && aud_is_common_indexed()) || (!is_common && aud_is_local_indexed()))
	{
		return false; // preset doesn't exist
	}
	
	while(row_value != "EOF" && empty_rows < 10 ) // end of file
	{
		row_value = tablelookupbyrow(stringtable, row_count, 0);
		if (row_value != "")
			empty_rows = 0;
						
		while(row_value == presetname)  // this is the beginning of the preset
		{
			found_preset = true;
			preset = undefined;
			for (col = 1; col < numparams; col++)
			{
				if (!IsDefined(param_names[col]))
					param_names[col] = tablelookupbyrow(stringtable, 0, col); // cache param name
					
				paramname = param_names[col];
				paramvalue = tablelookupbyrow(stringtable, row_count, col);
				
				if (paramvalue != "")
				{
					switch(paramname)
					{
						case "channel_name":
						preset = spawnstruct();
						preset.channel = paramvalue;
						break;
						
						case "band":
						/#
						if (!IsDefined(preset))
						{
							aud_print_error("In filter preset table, " + stringtable + ", the channel_name column must be before any other parameter.");
							return;
						}
						#/
						preset.band = int(paramvalue);
						break;
						
						case "type":
						/#
						if (!IsDefined(preset))
						{
							aud_print_error("In filter preset table, " + stringtable + ", the channel_name column must be before any other parameter.");
							return;
						}
						#/
						preset.type = paramvalue;
						break;
						
						case "freq":
						/#
						if (!IsDefined(preset))
						{
							aud_print_error("In filter preset table, " + stringtable + ", the channel_name column must be before any other parameter.");
							return;
						}
						#/
						preset.freq = float(paramvalue);
						break;
						
						case "gain":
						/#
						if (!IsDefined(preset))
						{
							aud_print_error("In filter preset table, " + stringtable + ", the channel_name column must be before any other parameter.");
							return;
						}
						#/
						preset.gain = float(paramvalue);
						break;
						
						case "q":
						/#
						if (!IsDefined(preset))
						{
							aud_print_error("In filter preset table, " + stringtable + ", the channel_name column must be before any other parameter.");
							return;
						}
						#/
						preset.q = float(paramvalue);
						break;
						
						default:
						/#
						aud_print_error("In filter preset table, " + stringtable + ", there is an improperly labeled parameter column, \"" + paramname + "\".");
						return;
						#/
						break;
					}
				}	
			} // now have our data			
			
			// do some simple validation
			/#
			if (!IsDefined(preset))
			{
				aud_print_error("In filter preset table, " + stringtable + ", there is an invalid entry for preset " + presetname + ".");
				return;
			}
			if (!IsDefined(preset.channel))
			{
				aud_print_error("In filter preset table, " + stringtable + ", a channel must be given for preset " + presetname + ".");
				return;
			}
			
			if (!IsDefined(preset.band))
			{
				aud_print_error("In filter preset table, " + stringtable + ", a band must be given for each channel for preset " + presetname + ".");
				return;
			}
			
			if (!IsDefined(preset.type))
			{
				aud_print_error("In filter preset table, " + stringtable + ", a type must be given for each channel for preset " + presetname + ".");
				return;
			}
			
			if (!IsDefined(preset.gain))
			{
				aud_print_error("In filter preset table, " + stringtable + ", a gain must be given for each channel for preset " + presetname + ".");
				return;
			}
			
			if (!IsDefined(preset.q))
			{
				aud_print_error("In filter preset table, " + stringtable + ", a q must be given for each channel for preset " + presetname + ".");
				return;
			}
			#/
			// cache the preset so no need to parse the stringtable anymore
			if (!IsDefined(level._audio.filter_presets[presetname]))
				level._audio.filter_presets[presetname] = [];
			
			level._audio.filter_presets[presetname][level._audio.filter_presets[presetname].size] = preset;	
			
			row_count++;
			row_value = tablelookupbyrow(stringtable, row_count, 0);
		}
		empty_rows++;
		// require preset parameters to be grouped together
		if (found_preset)
			return true; // successful!
		row_count++;
	}	
	return false; // not successful
}

aud_set_filter_threaded(presetname, index_, max_server_calls_per_frame_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsString(presetname));

	// create preset cache if haven't yet
	if (!IsDefined(level._audio.filter_presets))
		level._audio.filter_presets = [];

	index = 0;
	if (IsDefined(index_))
		index = index_;

	if (!IsDefined(level._audio.filter_presets[presetname]))
	{
		level._audio.filter_presets[presetname] = []; // the cached preset array, prevents reparsing stringtable
		
		common_stringtable = "soundtables/common_filter.csv"; // always use the common stringtable here
		level_stringtable = get_filter_stringtable();

		success = true;
		success = aud_set_filter_internal(presetname, level_stringtable, index, false);
		if (!success)
			success = aud_set_filter_internal(presetname, common_stringtable, index, true);
		
		if (!success)
		{
			/#
			aud_print_error("Error setting filter, \"" + presetname + "\", from either " + level_stringtable + " or " + common_stringtable + " soundtable.");
			#/
			return;
		}	
	}
	
	assert(IsDefined(level._audio.filter_presets[presetname]));
	
	level._audio.current_filter = presetname;
	if (level._audio.current_filter_indices[index] != presetname)
	{
		level._audio.current_filter_indices[index] = presetname; // store preset name on this index
		
		// simple server throttling algorithm 
		max_server_calls_per_frame = 10;
		if (IsDefined(max_server_calls_per_frame_))
			max_server_calls_per_frame = max_server_calls_per_frame_;
	
		count = 0;
		
		
		foreach( preset in level._audio.filter_presets[presetname] )
		{
			assert(IsDefined(preset.channel));
			assert(IsDefined(preset.band));
			assert(IsDefined(preset.type));
			assert(IsDefined(preset.gain));
			assert(IsDefined(preset.q));
					
			level.player seteq(preset.channel, index, preset.band, preset.type, preset.gain, preset.freq, preset.q);
			
			if (count <  max_server_calls_per_frame) // only set a max number of preset settings per frame...
			{
				count++;
			}
			else
			{
				count = 0;
				wait(0.05);
			}
		}
	}
}

aud_clear_filter(index_)
{
	index = 0;
	if (IsDefined(index_))
	{
		assert(index_ == 0 || index_ == 1);
		index = index_;
	}
	
	level._audio.current_filter_indices[index] = "";
	
	aud_set_filter(undefined, index);
}

aud_disable_zone_filter()
{
	level._audio.filter_zone_disabled = true;
}

aud_enable_zone_filter()
{
	level._audio.filter_zone_disabled = undefined;
}

aud_is_zone_filter_enabled()
{
	return !IsDefined(level._audio.filter_zone_disabled);
}

aud_set_filter(presetname, index_, max_server_calls_per_frame_, set_hud_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/

	if (level._audio.filter_disabled)
		return;

	// red flashing overwrites eq
	if ( IsDefined(level.player.ent_flag) && IsDefined( level.player.ent_flag[ "player_has_red_flashing_overlay" ] ) && level.player maps\_utility::ent_flag( "player_has_red_flashing_overlay" ) )
		return;

	index = 0;
	if (IsDefined(index_))
		index = index_;

	if (!IsDefined(presetname) || (IsDefined(presetname) && presetname == "")) // possible to give undefined preset name
	{
			level._audio.current_filter = undefined;
			level.player Deactivateeq(index); // kill filter if given an undefined preset name...
			/#
			set_filter_hud("");
			set_filter_from_hud("", "");
			set_filter_to_hud("", "");
			#/
			return;
	}

	/#
	set_hud = true;
	if (IsDefined(set_hud_))
	{
		set_hud = set_hud_;
	}
	if (set_hud)
	{
		set_filter_hud(presetname);
	}
	#/

	thread aud_set_filter_threaded(presetname, index_, max_server_calls_per_frame_);
}

aud_disable_filter_setting(channel_)
{
	level._audio.filter_disabled = true;
}

aud_enable_filter_setting(channel_)
{
	level._audio.filter_disabled = false;
}

////////////////////////////////////////////////////
// TIMESCALE PRESET FUNCTIONS
////////////////////////////////////////////////////

aud_set_timescale_internal(presetname)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsString(presetname));
	assert(IsDefined(level._audio.timescale_presets[presetname]));
	
	stringtable = "soundtables/common_timescale.csv";
	numparams = 2;
	row_value = "";
	row_count = 0;
	preset = [];
	param_names = [];
	found_preset = false;
	empty_rows = 0;
	
	// grab the indexed row from this preset 
	index = get_indexed_preset("timescale", presetname, true); // this is always in common
	if (index != -1)
	{
		row_count = index;
	}
	else if (aud_is_common_indexed())
	{
		return false; // preset doesn't exist
	}
	
	while(row_value != "EOF" && empty_rows < 10) // end of file
	{
		row_value = tablelookupbyrow(stringtable, row_count, 0);
		if (row_value != "")
			empty_rows = 0;
			
		while(row_value == presetname)  // this is the beginning of the preset
		{		
			found_preset = true;
			preset = undefined;
			for (col = 1; col < numparams + 1; col++)
			{
				if (!IsDefined(param_names[col]))
					param_names[col] = tablelookupbyrow(stringtable, 0, col); // cache param name
					
				paramname = param_names[col];
				paramvalue = tablelookupbyrow(stringtable, row_count, col);
				
				if (paramvalue != "")
				{
					switch(paramname)
					{
						
						case "channel_name":
							preset = spawnstruct();
							preset.channel = paramvalue;
						break;
						
						case "scalefactor":
							/#
							if (!IsDefined(preset))
							{
								aud_print_error("In timescale preset table, common_timescale.csv, the channel_name column must be before any other parameter.");
							}
							#/
							preset.scalefactor = float(paramvalue);
						break;
						
						default:
							aud_print_error("In timescale preset table, common_timescale.csv, there is an improperly labeled parameter column, \"" + paramname + "\".");
						break;
						
					}
				}	
			} // now have our data
		
			if (IsDefined(preset))
			{
				assert(IsDefined(preset.channel));
				/#
				if (!IsDefined(preset.scalefactor))
				{
					aud_print_error("In timescale preset table, common_timescale.csv, a scalefactor must be given for each channel.");
				}
				#/
				level._audio.timescale_presets[presetname][level._audio.timescale_presets[presetname].size] = preset;	
			}
			row_count++;
			row_value = tablelookupbyrow(stringtable, row_count, 0);
		}
		empty_rows++;
		
		// require preset parameters to be grouped together
		if (found_preset)
			return true;
		row_count++;
	}
	return false;
}

aud_set_timescale_threaded(presetname_, max_server_calls_per_frame_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	presetname = "default";
	if (IsDefined(presetname_))
	{
		assert(IsString(presetname_));
		presetname = presetname_;
	}
	
	if (!IsDefined(level._audio.timescale_presets))
		level._audio.timescale_presets = [];
	
	success = true;
	if (!IsDefined(level._audio.timescale_presets[presetname]))
	{
		level._audio.timescale_presets[presetname] = [];
		success = aud_set_timescale_internal(presetname);
	}
	
	if (!success)
	{
		/#
		aud_print_error("Error setting timescale preset, \"" + presetname + "\", from soundtables/common_timescale.csv soundtable.");
		#/
		return;
	}
	
	max_server_calls_per_frame = 10;
	if (IsDefined(max_server_calls_per_frame_))
		max_server_calls_per_frame = max_server_calls_per_frame_;
		
	count = 0;
	foreach(preset in level._audio.timescale_presets[presetname])
	{
		assert(IsDefined(preset.channel));
		assert(IsDefined(preset.scalefactor));

		SoundSetTimeScaleFactor(preset.channel, preset.scalefactor);						
		
		if (count < max_server_calls_per_frame)
			count++;
		else
		{
			count = 0;
			wait(0.05);
		}
	}
}

aud_set_timescale(presetname_, max_server_calls_per_frame_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/

	thread aud_set_timescale_threaded(presetname_, max_server_calls_per_frame_);
}

////////////////////////////////////////////////////
// OCCLUSION PRESET FUNCTIONS
////////////////////////////////////////////////////

aud_set_occlusion_internal(presetname)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	assert(IsDefined(level._audio.occlusion_presets[presetname]));

	// if undefined, return
	if (!IsDefined(presetname))
		return;	

	stringtable = "soundtables/common_occlusion.csv";
	
	numparams = 5;
	row_value = "";
	row_count = 0;
	preset = [];
	param_names = [];
	found_preset = false;
	empty_rows = 0;
	
	// grab the indexed row from this preset 
	index = get_indexed_preset("occlusion", presetname, true); // always is common
	if (index != -1)
	{
		row_count = index;
	}
	else if (aud_is_common_indexed())
	{
		return false; // preset doesn't exist
	}
	
	while(row_value != "EOF" && empty_rows < 10 )
	{
		row_value = tablelookupbyrow(stringtable, row_count, 0);
		if (row_value != "")
			empty_rows = 0;
			
		while(row_value == presetname) // this is the beginning of the preset
		{
			found_preset = true;
			preset = undefined;
			for (col = 1; col < numparams + 1; col++)
			{
				if (!IsDefined(param_names[col]))
					param_names[col] = tablelookupbyrow(stringtable, 0, col); // cache param name
				
				paramname = param_names[col];
				paramvalue = tablelookupbyrow(stringtable, row_count, col);
				
				if (paramvalue != "")
				{
					switch(paramname)
					{
						case "channel_name":
							preset = spawnstruct();
							preset.channel = paramvalue;
						break;
						case "frequency":
							/#
							if (!IsDefined(preset))
							{
								aud_print_error("In occlusion preset table, common_occlusion.csv, the channel_name column must be before the other parameter names.");
							}
							#/
							preset.freq = float(paramvalue);
						break;
						case "type":
							/#
							if (!IsDefined(preset))
							{
								aud_print_error("In occlusion preset table, common_occlusion.csv, the channel_name column must be before the other parameter names.");
							}
							#/
							preset.type = paramvalue;
						break;
						case "gain":
							/#
							if (!IsDefined(preset))
							{
								aud_print_error("In occlusion preset table, common_occlusion.csv, the channel_name column must be before the other parameter names.");
							}
							#/
							preset.gain = float(paramvalue);
						break;
						case "q":
							/#
							if (!IsDefined(preset))
							{
								aud_print_error("In occlusion preset table, common_occlusion.csv, the channel_name column must be before the other parameter names.");
							}
							#/
							preset.q = float(paramvalue);
						break;
						default:
							aud_print_error("In occlusion preset table, common_occlusion.csv, there is an improperly labeled parameter column, \"" + paramname + "\".");
						break;
					}
				}
			} // now have the preset contstructed
			
			assert(IsDefined(preset));
				
			assert(IsDefined(preset.channel));
			
			// set the default occlusion settings
			if (!IsDefined(preset.freq))
				preset.freq = 600;
			if (!IsDefined(preset.type))
				preset.type = "highshelf";
			if (!IsDefined(preset.gain))
				preset.gain = -12;
			if (!IsDefined(preset.q))
				preset.q = 1;
			
			level._audio.occlusion_presets[presetname][level._audio.occlusion_presets[presetname].size] = preset;	
			
			row_count++;
			row_value = tablelookupbyrow(stringtable, row_count, 0);
		}
		empty_rows++;
		// require preset parameters to be grouped together
		if (found_preset)
			return true;
		
		row_count++;
	}
	return false;
}

aud_set_occlusion_threaded(presetname_, max_server_calls_per_frame_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	
	presetname = "default";
	if (IsDefined(presetname_))
	{
		assert(IsString(presetname_));
		presetname = presetname_;
	}
	
	if (!IsDefined(level._audio.occlusion_presets))
		level._audio.occlusion_presets = [];
	
	success = true;
	if (!IsDefined(level._audio.occlusion_presets[presetname]))
	{
		level._audio.occlusion_presets[presetname] = [];
		success = aud_set_occlusion_internal(presetname);
	}
	
	if (!success)
	{
		/#
		aud_print_error("aud_set_occlusion: an error occured while loading occlusion preset, " + presetname + " from soundtables/common_occlusion.csv");
		#/
		return;
	}
	
	// store the presetname to the current presetname
	level._audio.current_occlusion = presetname;
	
	// RAVEN jsypult: we still want to keep track of zone filtering/occlusion transitions internally
	// if zone filtering/occlusion is not disabled, set the occlusion
	if (!(IsDefined(level._audio.zone_occlusion_and_filtering_disabled) && level._audio.zone_occlusion_and_filtering_disabled))
	{
		max_server_calls_per_frame = 10;
		if (IsDefined(max_server_calls_per_frame_))
			max_server_calls_per_frame = max_server_calls_per_frame;
		
		count = 0;
		foreach(preset in level._audio.occlusion_presets[presetname])
		{
			assert(IsDefined(preset.channel));
			assert(IsDefined(preset.freq));
			assert(IsDefined(preset.type));
			assert(isDefined(preset.gain));
			assert(isDefined(preset.q));

			level.player SetOcclusion(preset.channel, preset.freq, preset.type, preset.gain, preset.q);			

			if (count < max_server_calls_per_frame)
				count++;
			else
			{
				count = 0;
				wait(0.05);
			}
		}
	}
}

aud_set_occlusion(presetname_, max_server_calls_per_frame_)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
		
	// red flashing overwrites eq
	if ( IsDefined(level.player.ent_flag) && IsDefined( level.player.ent_flag[ "player_has_red_flashing_overlay" ] ) && level.player maps\_utility::ent_flag( "player_has_red_flashing_overlay" ) )
		return;

	if (!IsDefined(presetname_))
	{
		level._audio.current_filter = undefined;
		/#
		set_occlusion_hud("");
		#/
		return;
	}
	
	/#
	// RAVEN jsypult: let our developers know that occlusion is still "tracking" but disabled
	if ((IsDefined(level._audio.zone_occlusion_and_filtering_disabled) && level._audio.zone_occlusion_and_filtering_disabled))
		set_occlusion_hud(presetname_+" (disabled)");
	else
		set_occlusion_hud(presetname_);
	#/
	thread aud_set_occlusion_threaded(presetname_, max_server_calls_per_frame_);
}

// clears occlusion
aud_deactivate_occlusion(max_server_calls_per_frame_)
{
	max_server_calls_per_frame = 10;
	if (IsDefined(max_server_calls_per_frame_))
		max_server_calls_per_frame = max_server_calls_per_frame;
		
	count = 0;
	foreach(channel_name, val in level._audio.mix.channel_names)
	{
		level.player DeactivateOcclusion(channel_name);
		
		if (count < max_server_calls_per_frame)
			count++;
		else
		{
			count = 0;
			wait(0.05);
		}
	}
}

// RAVEN jsypult: this is what we use to stop zone filtering/occlusion from being processed & applied
// however, internal zone changes are still maintained so we know what filter/occlusion settings to "restore" to
aud_disable_zone_occlusion_and_filtering(max_server_calls_per_frame_)
{
	max_server_calls_per_frame = 10;
	if (IsDefined(max_server_calls_per_frame_))
		max_server_calls_per_frame = max_server_calls_per_frame;

	aud_set_filter(undefined, 0, max_server_calls_per_frame);
	aud_set_filter(undefined, 1, max_server_calls_per_frame);
	//aud_set_occlusion("", max_server_calls_per_frame); // this wipes occlusion from the debug hud
	aud_deactivate_occlusion(max_server_calls_per_frame);
	
	level._audio.zone_occlusion_and_filtering_disabled = true;
	
	/#
	// RAVEN jsypult: let our developers know that occlusion is still "tracking" but disabled
	if ((IsDefined(level._audio.zone_occlusion_and_filtering_disabled) && level._audio.zone_occlusion_and_filtering_disabled))
		set_occlusion_hud(level._audio.current_occlusion +" (disabled)");
	#/
	
}

// RAVEN jsypult: re-enables zone filtering/occlusion if it was previously disabled
// it will restore current_occlusion since internal zone changes have been maintained
aud_enable_zone_occlusion_and_filtering(max_server_calls_per_frame_)
{
	filter_presetname = undefined;
	occlusion_presetname = "default";

	max_server_calls_per_frame = 10;
	if (IsDefined(max_server_calls_per_frame_))
		max_server_calls_per_frame = max_server_calls_per_frame;

	if ( IsDefined(level._audio.zone_mgr.current_zone) && IsDefined(level._audio.zone_mgr.zones[level._audio.zone_mgr.current_zone]) )
	{
		current_zone = AZM_get_current_zone();
		zone = level._audio.zone_mgr.zones[current_zone];
		
		// grab the zone filter and occlusion settings, which may or may not have values...
		if (IsDefined(zone["occlusion"]) && zone["occlusion"] != "none")
			occlusion_presetname = zone["occlusion"];

		if (IsDefined(zone["filter"]) && zone["filter"] != "none")
			filter_presetname = zone["filter"];
	}
	
	// TODO: current_occlusion appears to be updated more frequently than zone["occlusion"]?
	if (level._audio.current_occlusion != occlusion_presetname) occlusion_presetname = level._audio.current_occlusion;
	
	// clear this flag now to restore filter and occlusion to their appropriate state
	level._audio.zone_occlusion_and_filtering_disabled = false;
	
	aud_set_filter(filter_presetname, 0, max_server_calls_per_frame);
	aud_set_filter(undefined, 1, max_server_calls_per_frame); // RAVEN jsypult: TODO confirm if this is right
	aud_set_occlusion(occlusion_presetname, max_server_calls_per_frame);
}

aud_use_level_zones(level_audio_zones_function)
{	
	assert(IsDefined(level._audio));
	level._audio.level_audio_zones_function = level_audio_zones_function;
}

aud_use_level_reverb(level_audio_reverb_function)
{
	assert(IsDefined(level._audio));
	level._audio.level_audio_reverb_function = level_audio_reverb_function;
}

aud_use_level_filters(level_audio_filter_function)
{
	assert(IsDefined(level._audio));
	level._audio.level_audio_filter_function = level_audio_filter_function;
}

aud_use_string_tables(do_index_)
{
	do_index = true;
	if (IsDefined(do_index_))
	{
		do_index = do_index_;
	}
	level._audio.using_string_tables = true;
	AZM_use_string_table();
	RVB_use_string_table();
	DAMB_use_string_table();
	MM_use_string_table();
	WHIZ_use_string_table();
	
	if (do_index)
	{
		aud_index_presets();
	}
	WHIZ_set_preset("default");
}

// GETTERS ANDS SETTERS FOR STRINGTABLE NAMES

// sets the default base map name for all stringtables
set_stringtable_mapname(name)
{
	aud_use_string_tables(false); // don't index yet
	level._audio.stringtables["map"] = name;
	aud_index_presets(); // index the presets now
}

get_stringtable_mapname()
{
	if (IsDefined(level._audio.stringtables["map"]))
		return level._audio.stringtables["map"];
	else
		return get_template_level();
}

// setters and getters for specific stringtables
set_mix_stringtable(name)
{
	assert(IsString(name));
	level._audio.stringtables["mix"] = name;
}

get_mix_stringtable()
{
	if (!IsDefined(level._audio.stringtables["mix"]))
		return "soundtables/" + get_stringtable_mapname() + "_mix.csv";
	else
		return "soundtables/" + level._audio.stringtables["mix"];
}

set_damb_stringtable(name)
{
	assert(IsString(name));
	level._audio.stringtables["damb"] = name;
}

get_damb_stringtable()
{
	if (!IsDefined(level._audio.stringtables["damb"]))
		return "soundtables/" + get_stringtable_mapname() + "_damb.csv";
	else
		return "soundtables/" + level._audio.stringtables["damb"];
}

set_damb_component_stringtable(name)
{
	assert(IsString(name));
	level._audio.stringtables["damb_comp"] = name;
}

get_damb_component_stringtable(name)
{
	if (!IsDefined(level._audio.stringtables["damb_comp"]))
		return "soundtables/" + get_stringtable_mapname() + "_damb_components.csv";
	else
		return "soundtables/" + level._audio.stringtables["damb_comp"];
}

set_damb_loops_stringtable(name)
{
	assert(IsString(name));
	level._audio.stringtables["damb_loops"] = name;
}

get_damb_loops_stringtable(name)
{
	if (!IsDefined(level._audio.stringtables["damb_loops"]))
		return "soundtables/" + get_stringtable_mapname() + "_damb_loops.csv";
	else
		return "soundtables/" + level._audio.stringtables["damb_loops"];
}

set_reverb_stringtable(name)
{
	assert(IsString(name));
	level._audio.stringtables["reverb"] = name;
}

get_reverb_stringtable()
{
	if (!IsDefined(level._audio.stringtables["reverb"]))
		return "soundtables/" + get_stringtable_mapname() + "_reverb.csv";
	else
		return "soundtables/" + level._audio.stringtables["reverb"];
}

set_filter_stringtable(name)
{
	assert(IsString(name));
	level._audio.stringtables["filter"] = name;
}

get_filter_stringtable()
{
	if (!IsDefined(level._audio.stringtables["filter"]))
		return "soundtables/" + get_stringtable_mapname() + "_filter.csv";
	else
		return "soundtables/" + level._audio.stringtables["filter"];
}

set_zone_stringtable(name)
{
	assert(IsString(name));
	level._audio.stringtables["zone"] = name;
}

get_zone_stringtable()
{
	if (!IsDefined(level._audio.stringtables["zone"]))
		return "soundtables/" + get_stringtable_mapname() + "_zone.csv";
	else
		return "soundtables/" + level._audio.stringtables["zone"];
}

set_occlusion_stringtable(name)
{
	assert(IsString(name));
	level._audio.stringtables["occlusion"] = name;
}

get_occlusion_stringtable()
{
	if (!IsDefined(level._audio.stringtables["occlusion"]))
		return "soundtables/" + get_stringtable_mapname() + "_occlusion.csv";
	else
		return "soundtables/" + level._audio.stringtables["occlusion"];
}

//-----------------------------------------------------------------------------------------------------
//	Register Audio Message Handlers.
//-----------------------------------------------------------------------------------------------------
aud_register_msg_handler(msg_handler)
{
	level._audio.message_handlers[level._audio.message_handlers.size] = msg_handler;
}

/*
///ScriptDocBegin
"Name: aud_send_msg(msg, args, notificaion_string)"
"Summary: Main audio script interface. Insures all audio msgs are asynchronous."
"Module: Audio"
"CallOn: Entity on which audio should be played (or pass the entity in as an argument)"
"MandatoryArg: <msg> : Any message string."
"OptionalArg: <args> : Optional parameter(s) in any form, either a single parameter, a struct, or array."
"OptionalArg: <notificaion_string> : Notification string to be used when audio task is complete. "
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_send_msg(msg, args, notificaion_string)
{
	//aud_print("ENTER:-->>aud_send_msg()\n");

	thread aud_dispatch_msg(msg, args, notificaion_string);	
	
	//aud_print("EXIT:<<--aud_send_msg()\n");
}

// Called from top-level aud_send_msg, aud_dispatch_msg insures that all msg handlers are asynch.
aud_dispatch_msg(msg, args, notificaion_string)
{
	assert(IsString(msg));
	msg_was_handled = false;
	result					= false;
	
	foreach (msg_handler in level._audio.message_handlers)
	{
		result = self [[msg_handler]](msg, args); // result may be undefined if the case statement leaves the case
		
		if (!msg_was_handled && IsDefined(result) && result == true)
		{
			msg_was_handled = result;
		}
		else if (!msg_was_handled && !IsDefined(result)) // means somebody early-returned from the handler, so handle that case
		{
			msg_was_handled = true;
		}
	}
	
	if (IsDefined(notificaion_string))
	{
		self notify(notificaion_string);
	}
	
	assert(IsDefined(msg_was_handled));
	if (!msg_was_handled)
	{
		aud_print_warning("\tAUDIO MESSAGE NOT HANDLED: " + msg);
	}
}

//-----------------------------------------------------------------------------------------------------
//	Audio Threads.
//-----------------------------------------------------------------------------------------------------
/#
aud_player_movement_monitor()
{
	CONST_updatePeriod							= 0.25;
	CONST_idle_to_moving_threshold	= 1.0;
	CONST_moving_to_idle_threshold	= 5.0;
		
	while (!isdefined(level.player))
	{
		wait(0.05);
	}
	level._audio.player_state.locamote = "idle";
	
	prevPos				= level.player.origin;
	prevTime			= 0;
	currTime			= 0;
	idle					= true;
	transTime			= 0;
	state					= "idle";
	
	// To Be Handled:  aud_send_msg("player_idle");
	
	while (1)
	{
		wait(CONST_updatePeriod);
		currTime += CONST_updatePeriod;
		currPos = level.player.origin;
		
		switch (level._audio.player_state.locamote)
		{
			case "idle":
			{
				if (currPos != prevPos) // No longer idle?
				{
					level._audio.player_state.locamote = "transToMoving";	// STATE CHANGE -> "transToMoving".
					transTime = 0;
				}
			}
			break;
			
			case "transToMoving":
			{
				if (currPos == prevPos)	// No longer moving?
				{
					level._audio.player_state.locamote = "idle";		// STATE CHANGE -> "idle".
				}
				else	// Stay in this state until we hit the time threshold.
				{
					transTime += CONST_updatePeriod;
					if (transTime >= CONST_idle_to_moving_threshold)
					{		
						level._audio.player_state.locamote = "moving";				// STATE CHANGE -> "moving".		
						// To Be Handled:  aud_send_msg("player_moving");
					}
				}
			}
			break;
			
			case "moving":
			{
				if (currPos == prevPos) // No longer moving?
				{				
					level._audio.player_state.locamote = "transToIdle";	// STATE CHANGE -> "transToIdle".
					transTime = 0;
				}
			}
			break;
			
			case "transToIdle":
			{
				if (currPos != prevPos)	// No longer idle?
				{
					level._audio.player_state.locamote = "moving";		// STATE CHANGE -> "moving".
				}
				else // Stay in this state until we hit the time threshold.
				{
					transTime += CONST_updatePeriod;
					if (transTime >= CONST_moving_to_idle_threshold)
					{	
						level._audio.player_state.locamote = "idle";				// STATE CHANGE -> "idle".	
						// To Be Handled:  aud_send_msg("player_idle");	
					}
				}
			}
			break;
			
			default:
			{
				assert(6 == 9); // WTF?
			}
			break;
		}
		
		prevPos = currPos;	// Remember current position for next time.
	}
}
#/

aud_get_player_locamote_state()
{
	assert(IsDefined(level._audio));
	assert(IsDefined(level._audio.player_state));
	assert(IsDefined(level._audio.player_state.locamote));
	return level._audio.player_state.locamote;
}

/*
///ScriptDocBegin
"Name: aud_get_threat_level(alert_level_, min_yards_, max_yards_)"
"Summary: Returns a float between 0 an d 1.0 (inclusive) that indicates the current threat based on enemy awareness/combat."
"Module: Audio"
"CallOn: none"
"MandatoryArg: none."
"OptionalArg: alert_level_ :  defines whether an enemy is a threat or not: >=2 requires enemy to be alert, >=3 requires enemy to be in combat. Default is combat."
"OptionalArg: alert_level_ :  ."
"OptionalArg: alert_level_ :  ."
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_get_threat_level(alert_level_, min_yards_, max_yards_)
{
	threat_level = 0;
	
	sticky_threat = aud_get_sticky_threat();
	if (IsDefined(sticky_threat))
	{
		threat_level = sticky_threat;
	}
	else
	{	
		alert_level	= 3;
		min_yards = 10;
		max_yards = 100;
		
		if (IsDefined(alert_level_))
		{
			alert_level = alert_level_;
		}
		if (IsDefined(max_yards_))
		{
			max_yards = max_yards_;
		}
		if (IsDefined(max_yards_))
		{
			min_yards = min_yards_;
		}
		max_dist	= 36 * max_yards;
		min_dist	= 36 * min_yards;
		
		
		enemies					= GetAiArray( "bad_guys" );
		num_aware_and_close_dudes	= 0;
		weight_total		= 0;
	
		foreach(dude in enemies)
		{
			if(IsDefined(dude.alertlevelint) && dude.alertlevelint >= alert_level) // notAlert = 1, alert = 2, combat = 3
			{
				dist = Distance(level.player.origin, dude.origin);
				
				if (dist < max_dist)
				{
					num_aware_and_close_dudes++;
					
					if (dist < min_dist)
					{
						weight_dude = 1.0;
					}
					else
					{				
						weight_dude = 1.0 - (dist - min_dist)/(max_dist - min_dist);
					}
					weight_total += weight_dude;
				}
			}
		}	
		
		if (num_aware_and_close_dudes > 0)
		{
			threat_level = weight_total/num_aware_and_close_dudes;
			//aud_print("Threat = " + threat_level, "debug");	
		}
		else
		{
			threat_level = 0;
		}
	}
	
	return threat_level;
}

aud_get_sticky_threat()
{
	return level._audio.sticky_threat;
}

aud_set_sticky_threat(threat_level)
{
	level._audio.sticky_threat = threat_level;
}

aud_clear_sticky_threat()
{
	level._audio.sticky_threat = undefined;
}

aud_num_alive_enemies(max_yards_)
{
	result	= 0;
	radius	= 36 * 100;	// Default in yards.
	
	if (IsDefined(max_yards_))
	{
		radius = 36 * max_yards_;
	}
	
	enemies = GetAiArray( "bad_guys" );
	
	foreach(dude in enemies)
	{
		if(IsAlive(dude))
		{
			dist = Distance(level.player.origin, dude.origin);
			
			if (dist < radius)
			{
				result++;
			}
		}
	}
	
	return result;
}

//-----------------------------------------------------------------------------------------------------
//	Level Audio Message Handler Function.
//-----------------------------------------------------------------------------------------------------

_audio_msg_handler(msg, args)
{
	msg_handled = true;
	
	switch(msg)
	{
		//--------------------------------------
		// GAME-WIDE "GLOBAL" HANDLERS 
		//--------------------------------------
		case "level_fade_to_black":
		{
			assert(IsArray(args) && IsDefined(args[0]) && IsDefined(args[1]));
			delay_time	= args[0];
			fade_time		= args[1];
			wait(delay_time);
			MM_start_preset("mute_all", fade_time);
		}
		break;

		case "generic_building_bomb_shake":
		{
			level.player playsound("sewer_bombs");
		}
		break;
		
		case "start_player_slide_trigger":
		{
			// Global Stub. Write your own handler in level_aud.gsc.
		}
		break;
		
		case "end_player_slide_trigger":
		{
			// Global Stub. Write your own handler in level_aud.gsc.
		}
		break;
		
		case "missile_fired":
		// do nothing
		break;
		
		case "msg_audio_fx_ambientExp":
		// do nothing
		break;
		
		case "aud_play_sound_at":
		{
			assert(IsDefined(args.alias));
			assert(IsDefined(args.pos));
			
			aud_play_sound_at(args.alias, args.pos);
		}
		break;
		
		case "aud_play_dynamic_explosion":
		{
			// Assert required args.
			assert(IsDefined(args.explosion_pos));
			assert(IsDefined(args.left_alias));
			assert(IsDefined(args.right_alias));
			
			// Get optional args.
			if (IsDefined(args.spread_width))
				spread_width = args.spread_width;
			else
				spread_width = undefined;
			
			if (IsDefined(args.rear_dist))
				rear_dist = args.rear_dist;
			else
				rear_dist = undefined;
				
			if (IsDefined(args.velocity))
				velocity = args.velocity;
			else
				velocity = undefined;
			
			// Call function.
			aud_play_dynamic_explosion(args.explosion_pos, args.left_alias, args.right_alias, spread_width, rear_dist, velocity);
		}
		break;
		
		case "aud_play_conversation":
		{
			aud_play_conversation(msg, args);
		}
		break;
		
		case "xm25_contact_explode":
		{
			if (soundexists("xm25_proj_explo"))
			{
				impact_point = args;
				thread play_sound_in_space("xm25_proj_explo", impact_point);
			}
		}
		break;
		
		case "light_flicker_on":
		{
			light_model = args;
			aud_handle_flickering_light(light_model);
		}
		break;
		
		
		default:
		{
			msg_handled = false;
		}
	}

	return msg_handled;
}

aud_handle_flickering_light(light_model)
{
	// for specific lights
	specific_light_played = false;
	switch(light_model.model)
	{
		case "furniture_lamp_floor1_off":
		case "com_cafe_light_part1_off":
		case "furniture_lamp_table1":
		{
			specific_light_played = true;
			if (SoundExists("paris_lamplight_flicker"))
			{
				thread play_sound_in_space("paris_lamplight_flicker", light_model.origin);
			}
		}
		break;

		default:
		{
			specific_light_played = false;
		}
	}

	return specific_light_played;
}

//-------------------------------------
//	Plays a conversation via passed in array of {ent, sound_alias, delay} structs.
//-------------------------------------
aud_play_conversation(msg, args)
{
	assert(IsDefined(args));
	lines = args;
	
	// Save and clear Battle Chatter state each dude.
	chatter_states = [];
	for (i = 0; i < lines.size; i++)
	{
		chatter_states[i] = lines[i].ent.battlechatter;
		lines[i].ent.battlechatter = 0;
	}
	
	// Play each line at the pos of the dude.
	foreach (line in lines)
	{
		assert(IsDefined(line.ent));
		assert(IsDefined(line.sound));
		
		if (IsDefined(line.delay))
		{
			wait(line.delay);
		}

		/*
		line.ent PlaySound(line.sound, "sounddone");
		line.ent waittill("sounddone");
		*/
		
		ent = Spawn( "script_origin", ( 0, 0, 0 ) );
		ent LinkTo( line.ent, "", ( 0, 0, 0 ), ( 0, 0, 0 ) );
		
		ent PlaySound(line.sound, "sounddone");
		ent waittill("sounddone");
		wait(0.05);
		ent delete();

	}
	
	// Restore Battle Chatter state each dude.
	for (i = 0; i < lines.size; i++)
	{
		lines[i].ent.battlechatter = chatter_states[i];
	}
}

// Registers callbacks for the trigger_multiple_audio
trigger_multiple_audio_register_callback(callbacks)
{
	assert(IsDefined(callbacks));

	if (!IsDefined(level._audio.trigger_functions))
	{
		level._audio.trigger_functions = [];
	}
	
	for (i = 0; i < callbacks.size; i++)
	{
		callback_array = callbacks[i];
		assert(callback_array.size == 2);
		
		callback_key = callback_array[0];
		assert(IsString(callback_key));
		
		callback_function = callback_array[1];
		
		level._audio.trigger_functions[callback_key] = callback_function;
	}
	
	// validate that all the keys that radiant is listening to has been registed with functions
	// still possible that somebody registered a function pointer with a key that nobody cares about (yet)
	if (IsDefined(level._audio.trigger_function_keys))
	{
		foreach ( callback_key in level._audio.trigger_function_keys)
		{
			assertEx(IsDefined(level._audio.trigger_functions[callback_key]), "trigger_multiple_audio_callback: " + callback_key + " not registered with a function pointer.");
		}
		level._audio.trigger_function_keys = undefined;
	}
}

get_target_ent_target()
{
	target_ent = get_target_ent();
	return target_ent.target;
}

get_target_ent_origin()
{
	target_ent = get_target_ent();
	return target_ent.origin;
}

get_target_ent_target_ent()
{
	target_ent = get_target_ent();
	return target_ent get_target_ent();
}

get_target_ent_target_ent_origin()
{
	target_ent_target_ent = get_target_ent_target_ent();
	return target_ent_target_ent.origin;
}

get_zone_from(tokens, is_backwards)
{
	if (!IsDefined(tokens) || !IsDefined(is_backwards))
	{
		return undefined;
	}
	
	assert(IsDefined(tokens[0]) && IsDefined(tokens[1]));
	
	if (is_backwards)
	{
		return tokens[1];
	}
	else
	{
		return tokens[0];
	}
}

get_zone_to(tokens, is_backwards)
{
	assert(IsDefined(is_backwards));
	
	if (!IsDefined(tokens) || !IsDefined(is_backwards))
	{
		return undefined;
	}
	
	assert(IsDefined(tokens[0]) && IsDefined(tokens[1]));
	
	if (is_backwards)
	{
		return tokens[0];
	}
	else
	{
		return tokens[1];
	}
}

//-----------------------------------------------------------------------------------------------------
//	TRIGGER HANDLER:  AUDIO TRIGGER (trigger_multiple_audio)
//-----------------------------------------------------------------------------------------------------
/*QUAKED trigger_multiple_audio (1.0 0.23 1.0) ? AI_AXIS AI_ALLIES AI_NEUTRAL NOTPLAYER VEHICLE TRIGGER_SPAWN TOUCH_ONCE
defaulttexture="ambient"
Crossfades between two "Audio Zones" defined via the Audio Zone Manager.
Audio zones may contain the following (defined in _audio_presets_zones.gsc):  Streamed Ambience, Dynamic Ambience, Mix Snaphot, Music Specification, etc.
Calls messages and/or functions when entering, exiting or progressing through the trigger.

Key: script_audio_zones -- Value = Pair of location names to be blended.
Key: script_audio_blend_mode -- Value = Mode is either "blend" or "trigger", defaults to "blend".
Key: script_audio_progress_map -- Value = Name of mapping array specified in aud_add_progress_map(name, map_array) function.

Key: script_audio_enter_msg -- Value = Message to be called when entering the trigger.
Key: script_audio_exit_msg -- Value = Message to be called when exiting the trigger.
Key: script_audio_progress_msg -- Value = Message to be called while progressing through the trigger.

Key: script_audio_enter_func -- Value = Key in an array pointing to a registered callback function when entering the trigger. 
Key: script_audio_exit_func -- Value = Key in an array pointing to a registered callback function when exiting the trigger.
Key: script_audio_progress_func -- Value = Key in an array pointing to a registered callback function while progressing through the trigger.
Key: script_audio_point_func -- Value = Key in an array pointing to a registered callback function while progressing through the trigger.
Note:  Register callback functions using trigger_multiple_audio_register_callback()

Key: script_audio_update_rate -- Value = Time in seconds (float) that the progress will wait per loop while player is inside trigger.
*/

trigger_multiple_audio_trigger(use_old_key_compatibility)
{
	if (!IsDefined(level._audio))
		level._audio = spawnstruct();
	
	if (!IsDefined(level._audio.trigger_functions))
		level._audio.trigger_functions = [];
	
	// Get Ambience Names 
	// check for new "script_audio_zones" first...
	
	tokens = undefined;
	
	if (IsDefined(use_old_key_compatibility) && use_old_key_compatibility)
	{
		if (IsDefined(self.ambient))
		{
			tokens = strtok(self.ambient, " ");
		}
	}
	else
	{	
		if (IsDefined(self.script_audio_zones))
		{
			tokens = strtok(self.script_audio_zones, " ");
		}
		else if (Isdefined(self.audio_zones))
		{
			tokens = strtok( self.audio_zones, " " );
		}
	}
		
	if (IsDefined(tokens) && tokens.size == 2)
	{
		assertEx(IsDefined(self.target), "Trigger Multiple Audio Trigger: audio zones given without setting up target entities (script_origins).");		
	}
	else if (IsDefined(tokens) && tokens.size == 1) // in this case, NO BLENDING will go on, so no special tokens, and we enter a special mode... this is deprecated, and supported for backward compatibility
	{
		for ( ; ; )
		{
			self waittill( "trigger", other );
			assertEx( isplayer( other ), "Non - player entity touched an ambient trigger." );

			AZM_start_zone( tokens[0], self.script_duration );
		}
	}
	
	if (IsDefined(self.script_audio_progress_map))
	{
		assert(IsDefined(level._audio.progress_maps));
		
		if (!IsDefined(level._audio.progress_maps[self.script_audio_progress_map]))
		{
			aud_print_error("Trying to set a progress_map_function without defining the envelope in the level.aud.envs array.");
			self.script_audio_progress_map = undefined;
		}
	}
		
	if(!IsDefined(level._audio.trigger_function_keys))
	{
		level._audio.trigger_function_keys = [];
	}
	
	if (IsDefined(self.script_audio_enter_func))
	{
		level._audio.trigger_function_keys[level._audio.trigger_function_keys.size] = self.script_audio_enter_func;
	}
	
	if (IsDefined(self.script_audio_exit_func))
	{
		level._audio.trigger_function_keys[level._audio.trigger_function_keys.size] = self.script_audio_exit_func;
	}

	if (IsDefined(self.script_audio_progress_func))
	{
		level._audio.trigger_function_keys[level._audio.trigger_function_keys.size] = self.script_audio_progress_func;
	}

	if (IsDefined(self.script_audio_point_func))
	{
		level._audio.trigger_function_keys[level._audio.trigger_function_keys.size] = self.script_audio_point_func;
	}

	if (!IsDefined(self.script_audio_blend_mode))
	{
		self.script_audio_blend_mode = "blend";
	}
		
	point_a = undefined;
	point_b = undefined;
	dist = undefined;

	if (IsDefined(self.target))
	{
		if (!IsDefined(get_target_ent()))
		{
			aud_print_error("Audo Zone Trigger at " + self.origin + " has defined a target, " + self.target + ", but that target doesn't exist.");
			return;
		}
		
		// if there are 2 script origins.
		if (IsDefined(get_target_ent_target())) 
		{
			point_a = get_target_ent_origin();
			if (!IsDefined(get_target_ent_target_ent()))
			{
				aud_print_error("Audo Zone Trigger at " + self.origin + " has defined a target, " + get_target_ent_target() + ", but that target doesn't exist.");
				return;
			}
			point_b  = get_target_ent_target_ent_origin();
		}
		else
		{
			// NOTE: THIS CODE IS TAKEN FROM IW CODE TO SUPPORT ONE SCRIPT ORIGIN.
			// It is deprecated for SHG maps
			assert(IsDefined(self.target));
			target_ent = get_target_ent();
			diff = 2*(self.origin - target_ent.origin);
			// otherwise double the difference between the target origin and start to get the endpoint
			angles = VectorToAngles(diff);
			point_a = get_target_ent_origin();
			point_b = point_a + diff;
			// If the pitch is not steep enough
			// Make sure the Z is level so you do not get a "pitched" plane when checking for progress.
			// If you want the angled pitched plane less than 45, then use 2 structs/ents.
			if (AngleClamp180(angles[0]) < 45)
			{
				point_a = (point_a[0], point_a[1], 0);
				point_b = (point_b[0], point_b[1], 0);
			}
		}
		
		dist = distance(point_a, point_b);
	}
	
	is_backward = false;
	
	while (1)
	{
		// Wait Until Player Hits Trigger 
		self waittill("trigger", other);
		assertEx( IsPlayer(other), "Non - player entity touched an ambient trigger." );
		
		// in specops, if we are not in split screen, and the person who triggers this is 
		// not the local client (level.player), then don't do any zone transitions
		if (aud_is_specops() && other != level.player)
		{
			/#
			if (IsSplitScreen() && IsDefined(tokens))
			{
				if (IsDefined(tokens[1]))
				{
					level._audio.specops_zones[1].zonename = tokens[1];
				}
				else if (IsDefined(tokens[0]))
				{
					level._audio.specops_zones[1].zonename = tokens[1];
				}
			}
			#/
			continue;
		}
		
		/#
		// If disabled, then do nothing. 
		if (!aud_get_enable_azblender()) continue;
		#/
		
		// At this point, we know which side of the trigger we're hitting. 
		
		if (IsDefined(point_a) && IsDefined(point_b))
		{
			progress = trigger_multiple_audio_progress(point_a, point_b, dist, other.origin);
			if (progress < 0.5) // We're going forward.
			{
				is_backward = false;
				// Going from zone a to zone b.
				
				if (IsDefined(self.script_audio_enter_msg))
				{
					if (IsDefined(tokens) && IsDefined(tokens[0]))
					{
						aud_send_msg(self.script_audio_enter_msg, tokens[0]);
					}
					else
					{
						aud_send_msg(self.script_audio_enter_msg, "front"); // still specify which side, even if the audio zone isn't defined
					}
				}
				
				if (IsDefined(self.script_audio_enter_func))
				{
					if (IsDefined(tokens) && IsDefined(tokens[0]))
					{
						if (IsDefined(level._audio.trigger_functions[self.script_audio_enter_func]))
						{
							[[ level._audio.trigger_functions[self.script_audio_enter_func] ]](tokens[0]);
						}
					}
					else
					{
						if (IsDefined(level._audio.trigger_functions[self.script_audio_enter_func]))
						{
							[[ level._audio.trigger_functions[self.script_audio_enter_func] ]]("front");
						}
					}
				}
			}
			else // We're going backward.
			{
				is_backward = true;
				// Going from zone a to zone b.
				
				if (IsDefined(self.script_audio_enter_msg))
				{
					if (IsDefined(tokens) && IsDefined(tokens[1]))
					{
						aud_send_msg(self.script_audio_enter_msg, tokens[1]);
					}
					else
					{
						aud_send_msg(self.script_audio_enter_msg, "back"); // still specify which side, even if the audio zone isn't defined
					}
				}
				
				// call the optional function pointer
				if (IsDefined(self.script_audio_enter_func))
				{
					if (IsDefined(tokens) && IsDefined(tokens[1]))
					{
						if (IsDefined(level._audio.trigger_functions[self.script_audio_enter_func]))
						{
							[[ level._audio.trigger_functions[self.script_audio_enter_func] ]](tokens[1]);
						}
					}
					else
					{
						if (IsDefined(level._audio.trigger_functions[self.script_audio_enter_func]))
						{
							[[ level._audio.trigger_functions[self.script_audio_enter_func] ]]("back");
						}
					}
				}
			}
		}
		else
		{
				if (IsDefined(self.script_audio_enter_msg))
				{
					aud_send_msg(self.script_audio_enter_msg); // still specify which side, even if the audio zone isn't defined
				}
				
				if (IsDefined(self.script_audio_enter_func))
				{
					if (IsDefined(level._audio.trigger_functions[self.script_audio_enter_func]))
					{
						[[ level._audio.trigger_functions[self.script_audio_enter_func] ]]();
					}
				}
		}
		blend_args = undefined;
		if (Isdefined(get_zone_from(tokens, is_backward)) && IsDefined(get_zone_to(tokens, is_backward)))
		{
			blend_args = AZMx_get_blend_args(get_zone_from(tokens, is_backward), get_zone_to(tokens, is_backward));
			if (!IsDefined(blend_args))
			{
				return;
			}
			// add the blend mode to the blend_args
			assert(IsDefined(self.script_audio_blend_mode));
			blend_args.mode = self.script_audio_blend_mode;
			
			/#
			AZM_print_enter_blend(get_zone_from(tokens, is_backward), get_zone_to(tokens, is_backward));
			#/
		}
				
		if (IsDefined(blend_args) && aud_is_zone_filter_enabled())
		{
			if (IsDefined(blend_args.filter1) || IsDefined(blend_args.filter2))
			{
				level.player deactivateeq(1); 
			}
		}

/#		
		if (aud_is_specops() && IsDefined(blend_args))
		{
			assert(other == level.player);
			aud_set_specops_zone(other, "blending");
		}
#/
		
		// Loop while player is inside trigger. 
		last_progress = -1;
		progress = -1;
		while ( other istouching( self ) )
		{
			if (IsDefined(self.script_audio_point_func))
			{
				progress_point = trigger_multiple_audio_progress_point(point_a, point_b, other.origin);
				if (IsDefined(level._audio.trigger_functions[self.script_audio_point_func]))
				{
					[[ level._audio.trigger_functions[self.script_audio_point_func] ]](progress_point);
				}
			}
			
			// don't do any blend functionality without defined points (from the script_origins)
			if (IsDefined(point_a) && IsDefined(point_b))
			{
				// get the progress value
				progress = trigger_multiple_audio_progress(point_a, point_b, dist, other.origin);
				
				if (IsDefined(self.script_audio_progress_map))
				{
					assert(IsDefined(level._audio.progress_maps[self.script_audio_progress_map]));
					progress = aud_map(progress, level._audio.progress_maps[self.script_audio_progress_map]);
				}
				
				// Blend the ambiences base on progress. 
				if (progress != last_progress)
				{
					if (IsDefined(get_zone_from(tokens, is_backward)) && IsDefined(get_zone_to(tokens, is_backward)))
						AZM_print_enter_blend(get_zone_from(tokens, is_backward), get_zone_to(tokens, is_backward), progress);
					
					if (IsDefined(self.script_audio_progress_msg))
					{
						aud_send_msg(self.script_audio_progress_msg, progress);
					}
					
					if (IsDefined(self.script_audio_progress_func))
					{
						if (IsDefined(level._audio.trigger_functions[self.script_audio_progress_func]))
						{
							[[ level._audio.trigger_functions[self.script_audio_progress_func] ]](progress);
						}
					}
					
					if (IsDefined(blend_args))
					{
						// Perform blend.
						trigger_multiple_audio_blend(progress, blend_args, is_backward); 
					}
					// Store progress.
					last_progress = progress;
					AZM_print_progress(progress);	
				}
			}
			
			// Sleep a little while.
			if (IsDefined(self.script_audio_update_rate))
			{
				wait(self.script_audio_update_rate);
			}
			else
			{
				wait(0.1);
			}
		}

		
		// don't do any blend functionality without defined points (from the script_origins)
		if (IsDefined(point_a) && IsDefined(point_b))
		{
			assert(IsDefined(progress));
			// Clean Up:  Just exited trigger, so only one abmbinece should play; no more blending. 
			if (progress > 0.5)
			{
				/#
				if (IsDefined(get_zone_from(tokens, is_backward)) && IsDefined(get_zone_to(tokens, is_backward)))
				{
					set_zone_hud(tokens[1]);
				}
				#/
				
				if (IsDefined(tokens) && IsDefined(tokens[1]))
				{
					AZM_set_current_zone(tokens[1]);
				}
				
				if (IsDefined(self.script_audio_exit_msg))
				{
					if (IsDefined(tokens) && IsDefined(tokens[1]))
					{
						aud_send_msg(self.script_audio_exit_msg, tokens[1]);
					}
					else
					{
						aud_send_msg(self.script_audio_exit_msg, "back");
					}
				}
				
				// call the optional function pointer
				if (IsDefined(self.script_audio_exit_func))
				{
					if (IsDefined(tokens) && IsDefined( tokens[1] ))
					{
						if (IsDefined(level._audio.trigger_functions[self.script_audio_exit_func]))
						{
							[[ level._audio.trigger_functions[self.script_audio_exit_func] ]](tokens[1]);
						}
					}
					else
					{
						if (IsDefined(level._audio.trigger_functions[self.script_audio_exit_func]))
						{
							[[ level._audio.trigger_functions[self.script_audio_exit_func] ]]("back");
						}
					}
				}			
				progress = 1;
			}
			else
			{
				/#
				if (IsDefined(get_zone_from(tokens, is_backward)) && IsDefined(get_zone_to(tokens, is_backward)))
				{
					set_zone_hud(tokens[0]);
				}
				#/
				
				if (IsDefined(tokens) && IsDefined(tokens[0]))
				{
					AZM_set_current_zone(tokens[0]);
				}
	
				if (IsDefined(self.script_audio_exit_msg))
				{
					if (IsDefined(tokens) && IsDefined(tokens[0]))
					{
						aud_send_msg(self.script_audio_exit_msg, tokens[0]);	
					}
					else
					{
						aud_send_msg(self.script_audio_exit_msg, "front");	
					}
				}
									
				// call the optional function pointer
				if (IsDefined(self.script_audio_exit_func))
				{
					if (IsDefined(tokens) && IsDefined(tokens[0]))
					{
						if (IsDefined(level._audio.trigger_functions[self.script_audio_exit_func]))
						{
							[[ level._audio.trigger_functions[self.script_audio_exit_func] ]](tokens[0]);
						}
					}
					else
					{
						if (IsDefined(level._audio.trigger_functions[self.script_audio_exit_func]))
						{
							[[ level._audio.trigger_functions[self.script_audio_exit_func] ]]("front");
						}
					}
				}
				progress = 0;
			}
			
			if (IsDefined(blend_args))
			{
				// FINAL BLEND:  One full off, the other full on.
				trigger_multiple_audio_blend(progress, blend_args, is_backward);
				
				/#
				
				filter_progress = progress;
				if (is_backward) // flip progress if going backward
				{
					filter_progress = 1.0 - progress;
				}
				if (filter_progress < 0.5 && IsDefined(blend_args.filter2))
				{
					set_filter_hud(blend_args.filter1);
				}
				else if (filter_progress > 0.5 && IsDefined(blend_args.filter1))
				{
					set_filter_hud(blend_args.filter2);
				}
				set_filter_from_hud("", "");
				set_filter_to_hud("", "");
				#/
				
			}
		}
		else
		{
				if (IsDefined(self.script_audio_exit_msg))
				{
					aud_send_msg(self.script_audio_exit_msg);
				}
				
				if (IsDefined(self.script_audio_exit_func))
				{
					if (IsDefined(level._audio.trigger_functions[self.script_audio_exit_func]))
					{
						[[ level._audio.trigger_functions[self.script_audio_exit_func] ]]();
					}
				}
		}
		
		// PRINT:  We are done here, display which side we came out of.
		// At this pont progress is either 1 or 0.
		/#
		if (IsDefined(point_a) && IsDefined(point_b))
		{
			assert(progress == 1 || progress == 0);
			AZM_print_progress(progress);
			if (IsDefined(tokens) && IsDefined(tokens[0]) && IsDefined(tokens[1]))
			{
				if (progress == 0)
				{
					
					if (aud_is_specops())
					{
						aud_set_specops_zone(other, tokens[0]);
					}
					
					AZM_print_exit_blend(tokens[0]);
				}
				else
				{
					
					if (aud_is_specops())
					{
						aud_set_specops_zone(other, tokens[1]);
					}
					
					AZM_print_exit_blend(tokens[1]);
				}
			}
		}
		else
		{
			// no points were defined, so we need to print that we exited, but can't say which side
			AZM_print_exit_blend("generic trigger");
		}
		#/
	}
}

/#
aud_set_specops_zone(other, zone)
{
	assert(aud_is_specops());
	assert(level.player == other);
	level._audio.specops_zones[0].zonename = zone;
}
#/

trigger_multiple_audio_progress( start, end, dist, org  )
{
	normal = vectorNormalize( end - start );
	vec = org - start;
	progress = vectorDot( vec, normal );
	progress = progress / dist;			
	return clamp(progress, 0, 1.0);
}

trigger_multiple_audio_progress_point( start, end, org )
{
	normal = vectorNormalize( end - start );
	vec = org - start;
	progress_length = vectorDot( vec, normal ); // projection of vec on normal
	
	return normal * progress_length + start; // offset from the start
}


trigger_multiple_audio_blend(progress, blend_args, is_backward)
{
	assert(IsDefined(progress));
	assert(IsDefined(blend_args));
	
	progress = clamp(progress, 0, 1.0);
	
	// flip the context of what "progress" means if we are going backward... 
	if (is_backward)
	{
		progress = 1.0 - progress;
	}
		
	assert(IsDefined(blend_args.mode));
	mode = blend_args.mode;
	assert(mode == "blend" || mode == "trigger");
	if (mode == "blend")
	{
		level_a = 1.0 - progress;
		level_b = progress;
		AZMx_blend_zones(level_a, level_b, blend_args);
	}
	else
	{
		if (progress < 0.33)
		{
			AZM_start_zone(blend_args.zone_from_name);
		}
		else if (progress > 0.66)
		{
			AZM_start_zone(blend_args.zone_to_name);
		}
	}
}


//-----------------------------------------------------------------------------------------------------
/*
	Dynamic Explosion Support
	Supports dynamically moving explostion/debris sounds from the 
	point of the explosion out toward the player, increasing the 
	panoramic spread as the sound approaches the player.
	
	Required arguments:
		explo_pos:		Position of the initial explosion; i.e., where the sound starts.
		left_alias:		Sound that is moved toward and left of the player.
		right_alias:	Sound that is moved toward and right of the player.
	Optional arguments:
		spread_width:		The distance the sounds will spread left and right of the player.
		rear_dist:	The distance the sounds will travel beyond the player.
		velocity:			The speed at which the sounds will travel from explosion point to spread points.
*/
//-----------------------------------------------------------------------------------------------------
aud_play_dynamic_explosion(explo_pos, left_alias, right_alias, spread_width, rear_dist, velocity)
{	
	assert(IsDefined(explo_pos));
	assert(IsDefined(left_alias));
	assert(IsDefined(right_alias));
	
	// Create a "center point" entity, and set it to the player position.
	player_ent = Spawn( "script_origin", level.player.origin );				
	
	// Create an "explostion point" entity, and set it to the position of the initial explosion.
	explo_ent = Spawn( "script_origin", explo_pos );		
	
	// If optional spread_width arg not supplied, use a reasonable default.
	if (!IsDefined(spread_width))
	{
		spread_width = Distance(explo_ent.origin, player_ent.origin);
	}
	
	// If optional backDist param not supplied, use a reasonable default.
	if (!IsDefined(rear_dist))
	{
		yards = 30;	// Number of yards the sound travels behind you.
		rear_dist = 12 * 3 * yards; 
	}

	// Calculate final locations of the moving explosion l/r stereo pair.
	final_explo_positions = aud_do_dynamic_explosion_math(explo_ent.origin, player_ent.origin, spread_width, rear_dist);
	assert(IsDefined(final_explo_positions));
	assert(final_explo_positions.size == 2);
		
	// Make sure the z-axis points are same as the player
	final_explo_positions[0] = (final_explo_positions[0][0], final_explo_positions[0][1], player_ent.origin[2]);
	final_explo_positions[1] = (final_explo_positions[1][0], final_explo_positions[1][1], player_ent.origin[2]);
	
	// Calc total distance that each sound travels.
	distance_traveled = Distance( explo_ent.origin, final_explo_positions[0] );


	// If optional velocity param not supplied, use a reasonable default.
	if (!IsDefined(velocity))
	{
		// The speed of sound at sea level = 340.29 meters per second 
		// 1 meter = 39.3700787 inches
		// So SOS in inches per second, SOS = (340.29 * 39.3700787) inches/second
		// This would result in velocity = 13397.2441 inches/sec, and a "move rate" of about 0.08s, which doesn't sound good.
		// So... pick a default that sounds good.
		velocity = 12 * 3 * 50; // 100 yards per second.
	}
		
	// Calc "move time" or "rate" from distance travled and velocity:  
	// d = r*t, so time = distance/rate where rate is velecity.
	// So, t = (distance_traveled)/velocity
	move_time = distance_traveled/velocity;
	
	// Play Sounds and move them over time.
	if (IsDefined(final_explo_positions) && final_explo_positions.size == 2)
	{
		// Start the pair at the initial explosion point.
		left_ent = Spawn( "script_origin", explo_ent.origin );
		right_ent = Spawn( "script_origin", explo_ent.origin );
		left_ent PlaySound(left_alias);
		right_ent PlaySound(right_alias);
		
		// Move the sounds to their final destination points.
		left_ent  moveTo( final_explo_positions[0], move_time, 0, 0);
		right_ent moveTo( final_explo_positions[1], move_time, 0, 0);
		
		/*	FOR DEBUGGING
		Print3d( level.player.origin, "PlayerPt", (1.0, 0.8, 0.5), 1, 5, 10);
		Print3d( final_explo_positions[0], "LeftPt", (1.0, 0.8, 0.5), 1, 5, 10);
		Print3d( final_explo_positions[1], "RightPt", (1.0, 0.8, 0.5), 1, 5, 10);
		
		inchesPerYard = 12 * 3;
		aud_print("spread_width: " + spread_width/inchesPerYard + " yards.");
		aud_print("rear_dist: " + rear_dist/inchesPerYard + " yards.");
		aud_print("velocity: " + velocity/inchesPerYard + " yards/second.");
		aud_print("move_time: " + move_time + " seconds.");
		*/
	}	
}


///////////////////////////////////////////////////////
// explosion_vector = (0,0,0)
// player_vector = (0,0,0)
// spread_width = spread in game units of the final position of the explosion trajectory
// rear_dist = distance behind player (on other side of explosion) of the final position of the explosion trajectory
// return: array[0] = left_ent, array[1] = right_ent
///////////////////////////////////////////////////////
aud_do_dynamic_explosion_math(explosion_vector, player_vector, spread_width, rear_dist)
{	
	centerVector = player_vector - explosion_vector; // subtract explosion from player, now have vector from origin
	leftVector = aud_copy_vector(centerVector); // copy vectors (left and right are the destination vectors)
	rightVector = aud_copy_vector(centerVector);
	
	// scale the left and right vector according to the spread_width
	leftRightVectorMag = aud_vector_magnitude_2d(leftVector);
	leftRightVectorMultiplier = 0.5 * spread_width / leftRightVectorMag; // use sidewidth parameter
	leftVector = aud_scale_vector_2d(leftVector, leftRightVectorMultiplier);
	rightVector = aud_scale_vector_2d(rightVector, leftRightVectorMultiplier);
			
	// perform the rotation math around z-axis for left and right vectors	
	leftVector = aud_rotate_vector_yaw(leftVector, 90);
	rightVector = aud_rotate_vector_yaw(rightVector, -90);

	// now figure how the left and right vectors are to be displaced	using the rear_dist
	centerVectorMag = aud_vector_magnitude_2d(centerVector); // distance from player to explosion
	centerVectorMultiplier = rear_dist / centerVectorMag; // use rear_dist parameter

	scaledCenterVector = aud_scale_vector_2d(centerVector, centerVectorMultiplier); // scale the center vector by the backdistance	
	scaledCenterVector = scaledCenterVector + centerVector; // then add it back to the center vector
	
  // displace the left and right vectors (which are scaled and rotated) by the new scaled center vector
	scaledCenterVector = scaledCenterVector + centerVector; 
	leftVector = leftVector + scaledCenterVector;
	rightVector = rightVector + scaledCenterVector;

	// package results, and return it	
	result = [];
	result[0] = leftVector;
	result[1] = rightVector;
	
	return result;
}

//-----------------------------------------------------------------------------------------------------
//	Misc Utils
//-----------------------------------------------------------------------------------------------------

aud_get_optional_param(optional_parameter_, default_value)
{
	assert(IsDefined(default_value));
	result = default_value; 					
	
	if (IsDefined(optional_parameter_))
	{
		result = optional_parameter_;
	}
	
	return result;
}

aud_scale_vector_2d(vec, scalar)
{
	return(vec[0] * scalar, vec[1] * scalar, vec[2]);
}

aud_scale_vector(vec, scalar)
{
	return(vec[0] * scalar, vec[1] * scalar, vec[2] * scalar );
}

aud_rotate_vector_yaw(vec, angle)
{
	vecX = vec[0] * cos(angle) - vec[1] * sin(angle);
	vecY = vec[0] * sin(angle) + vec[1] * cos(angle);
	return (vecX, vecY, vec[2]); 
}

aud_copy_vector(input_vector)
{
	new_vector = (0,0,0);
	new_vector = new_vector + input_vector;
	return new_vector;
}

aud_vector_magnitude_2d(input_vector) // or distance?
{
	return sqrt(input_vector[0] * input_vector[0] + input_vector[1] * input_vector[1]);
}

aud_print_synch(msg)
{
	aud_print(msg, "synch_frame");
}

aud_print(msg, msg_type_)
{
	/#
	verbosity = aud_get_verbosity();
	
	msg_enabled	= false;
	modifier		= undefined;
	msg_type		= "debug";
	
	if (isdefined(msg_type_))
	{
		msg_type = msg_type_;
	}

	switch (msg_type)
	{
		case "error":
			if (verbosity >= 1)
			{
				msg = "AUDIO ERROR: " + msg;
				if (aud_get_print_on_warnings())
				{
					msg_enabled = true;
				}
				if (aud_get_assert_on_errors())
				{
					assertEx(false, msg); // cause an audio error assert with the msg
				}
			}
		break;
		
		case "warning":
			if (verbosity >= 2)
			{
				msg = "AUDIO WARNING: " + msg;
				if (aud_get_print_on_warnings())
				{
					msg_enabled = true;
				}
			}
		break;
		
		case "debug":
			if (verbosity >= 3)
			{
				msg_enabled = true;
				msg = "AUDIO DEBUG: " + msg;	
			}
		break;
		
		case "music":
			msg_enabled = aud_get_print_music_cues();
		break;
		
		case "ams":
			msg_enabled = aud_get_print_music_cues();
			modifier = "small";
		break;
		
		case "zone":
			msg_enabled = aud_get_print_audio_zones();
		break;
		
		case "zone_small":
			msg_enabled = aud_get_print_audio_zones();
			modifier = "small";
		break;
		
		case "synch_frame":
			msg_enabled = aud_get_print_synch_frames();
		break;
	}
	
	if (msg_enabled)
	{
		audx_print(msg, modifier);
	}
	#/
}
/#
audx_print(msg, size_)
{
	size = "large";
	if (IsDefined(size_))
	{
		size = size_;
	}
	
	// Echo to video screen.
	if (aud_get_use_iprint()) // Note: iPrint echos to console.
	{
		if (size == "large")
		{
			IPrintLnBold(msg);
		}
		else
		{
			IPrintLn(msg);
		}
	}
	else
	{
		// Print to console only.
		println(msg);	
	}
}
#/

// flavors of aud_print
aud_print_warning(msg)
{
	aud_print(msg, "warning");
}

aud_print_error(msg)
{
	aud_print(msg, "error");
}

aud_print_debug(msg)
{
	aud_print(msg);
}

aud_print_zone(msg)
{
	aud_print(msg, "zone");
}

aud_print_zone_small(msg)
{
	aud_print(msg, "zone_small");	
}

equal_strings(str1, str2)
{
	if (isdefined(str1) && isdefined(str2))
	{
		return str1 == str2;
	}
	else
	{
		return !isdefined(str1) && !isdefined(str2);
	}
}

IsUndefined(x)
{
	return !IsDefined(x);
}

delete_on_sounddone(ent)
{
	ent waittill("sounddone");
	ent delete_sound_entity();
}

delete_sound_entity()
{
	self delaycall(0.05, ::delete);
}

/*
///ScriptDocBegin
"Name: aud_fade_out_and_delete(sndEntity, fade)"
"Summary: Fades out the sound entity and then deletes the entity."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <sndEntity> : Sound entity handle."
"MandatoryArg: <fade> : The time to fade to zero. (in seconds)"
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_fade_out_and_delete(sndEntity, fade)
{
	sndEntity ScaleVolume(0.0, fade);
	sndEntity delaycall(fade + 0.05, ::stopsounds);
	sndEntity delaycall(fade + 0.1, ::delete);
}

aud_fade_loop_out_and_delete(sndEntity, fade)
{
	sndEntity ScaleVolume(0.0, fade);
	wait(fade + 0.05);
	sndEntity StopLoopSound();
	wait(0.05);
	sndEntity delete();
}

aud_min(val1, val2)
{
	if (val1 <= val2)
	{
		return val1;
	}
	else
	{
		return val2;
	}
}

aud_max(val1, val2)
{
	if (val1 >= val2)
	{
		return val1;
	}
	else
	{
		return val2;
	}
}

aud_clamp(input, min, max)
{
	if (input < min)
	{
		input = min;
	}
	else if (input > max)
	{
		input = max;
	}
	return input;
}

aud_fade_sound_in(ent, alias_name, vol, fade_in_time, is_loop_)
{
	assert(IsDefined(ent));
	assert(IsString(alias_name));
	assert(IsDefined(vol));
	assert(IsDefined(fade_in_time));
	
	vol = aud_clamp(vol, 0.0, 1.0);
	fade_in_time = aud_max(0.05, fade_in_time);
	
	is_loop = false;
	if (IsDefined(is_loop_))
	{
		is_loop = is_loop_;
	}
	if (is_loop)
	{
		ent playloopsound(alias_name);
	}
	else
	{
		ent PlaySound(alias_name);
	}
	
	ent ScaleVolume(0.0);
	ent delaycall(0.05, ::ScaleVolume, vol, fade_in_time);
}
    
/*
///ScriptDocBegin
"Name: aud_map(input, env_points)"
"Summary: Remaps input_value to corresponding output_value based on values in envelop_array."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: <env_points> : Array of "node-points" that define a function envelope."
"MandatoryArg: <input_value> : Value to be remapped."
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_map2(input_x, env_points)
{
	// find min from the envelope
	assert(IsDefined(env_points));
	assert(env_points.size >= 2);
	
	/#
	// assert that the x-values of the env are monotonically increasing
	prev_x = env_points[0][0];
	for(i = 0; i < env_points.size; i++)
	{
		assertEx(env_points[i][0] >= prev_x, "aud_map_2: envelope points must be in increasing order");
		prev_x = env_points[i][0];
	}
	#/
	
	min_x = env_points[0][0];
	max_x = env_points[env_points.size - 1][0];
	
	min_y = env_points[0][1];
	max_y = env_points[env_points.size - 1][1];
	output = undefined;
	
	if (input_x <= min_x)
	{
		output = min_y;
	}
	else if (input_x >= max_x)
	{
		output = max_y;
	}
	else
	{
		curr_x = undefined;
		prev_x = min_x;
		prev_y = min_y;
		for (i = 0; i < env_points.size; i++)
		{
			curr_x = env_points[i][0];
			curr_y = env_points[i][1];
			if (input_x >= prev_x && input_x < curr_x) // boundary check
			{
				fraction = (input_x - prev_x) / (curr_x - prev_x);
				output = prev_y + fraction * (curr_y - prev_y); // linearly interpolate the output
				break;
			}
			prev_x = curr_x;
			prev_y = curr_y;
		}
	}
	
	assert(IsDefined(output));
	return output;
}

aud_map(input, env_points)
{
	// input is zero to one
	assert(IsDefined(input));
	assert(input >= 0.0 && input <= 1.0);
	assert(IsDefined(env_points));
	
	/# 
	// this ensures that the given envelope is in order, otherwise we'd have to perform a sorting function.
	audx_validate_env_array(env_points);
	#/
	output = 0.0;
	num_points = env_points.size;
	
	// find the x-values which are relevant for the input
	prev_point = env_points[0]; // grab the first point
	for (i = 1; i < env_points.size; i++)
	{
		next_point = env_points[i];
		if (input >= prev_point[0] && input <= next_point[0])
		{
			prev_x = prev_point[0];
			next_x = next_point[0];
			prev_y = prev_point[1];
			next_y = next_point[1];
			x_fract = (input - prev_x) / (next_x - prev_x);
			output = prev_y + x_fract * (next_y - prev_y);
			break;
		}
		else
		{
			prev_point = next_point;
		}
	}
	
	assert(output >= 0.0 && output <= 1.0);
	
	return output;
}

aud_map_range(input, range_min, range_max, env_points)
{
	assert(IsDefined(input));
	assert(IsDefined(env_points));
	
	assert(range_max != range_min);
	val = (input - range_min) / ( range_max - range_min);
	val = clamp(val, 0.0, 1.0);
	return aud_map(val, env_points);
}

// A simple one pole lowpass filter. Smooth's range is (0.0, 1.0]
// Used to smooth out data to avoid large leaps.
aud_smooth(prev, curr, smooth)
{
	assert(IsDefined(prev));
	assert(IsDefined(curr));
	assert(IsDefined(smooth) && smooth > 0.0 && smooth <= 1.0);
	return prev + smooth * (curr - prev);
}

aud_is_even(number)
{
	assert(IsDefined(number));
	return (number == Int(number / 2) * 2);
}

// some helper functions for eq presets
all_mix_channels_except(exception_array)
{
	assert(IsDefined(exception_array));
	all_mix_channels = MM_get_channel_names();
	assert(IsDefined(all_mix_channels));

	result = [];
	
	foreach( channel in exception_array)
	{
		assert(IsString(channel));
		// remove from all channels array
		all_mix_channels[channel] = undefined;
	}
	
	// pack it in the right array type
	foreach (channel, _ in all_mix_channels)
	{
		assert(IsString(channel));
		result[result.size] = channel;
	}
	return result;
}

all_mix_channels()
{
	all_mix_channels = MM_get_channel_names();
	
	result = [];
	assert(IsDefined(all_mix_channels));
	foreach(channel, _ in all_mix_channels)
	{
		assert(IsString(channel));
		result[result.size] = channel;
	}
	return result;
}

aud_SetAllTimeScaleFactors(value)
{
	assert(IsDefined(value) && !IsString(value));
	value = clamp(value, 0, 1.0);
	
	chans = all_mix_channels();
	aud_SetTimeScaleFactors(chans, value);
}

aud_SetTimeScaleFactors(chans, value)
{
	thread audx_SetTimeScaleFactors(chans, value);
}

// TODO:  This should use a throttle system.
audx_SetTimeScaleFactors(chans, value)
{
	assert(IsDefined(chans) && IsDefined(value));
	burstMax = 8;
	burst = 0;
	i = 0;
	next = 0;
	
	while (i < chans.size)
	{
		next = i;
		for (burst = 0; burst < burstMax && next < chans.size; burst++)
		{
			SoundSetTimeScaleFactor(chans[next], value);
			next++;
		}
		wait(0.05);
		i += burstMax;
	}
	
//	for (i = 0; i < chans.size; i++)
//	{
//		SoundSetTimeScaleFactor(chans[i], value);
//		wait(0.05);
//	}
}

// TODO:  This should use a throttle system.
aud_set_breach_time_scale_factors()
{
	chans = all_mix_channels();
	aud_SetTimeScaleFactors(chans, 1.0);
	wait(0.5);
	
	//set up dynamic sound channels that will only be partially affected by slomo (taken from breach code)
	SoundSetTimeScaleFactor( "Music", 0 );
	SoundSetTimeScaleFactor( "Menu", 0 );
	SoundSetTimeScaleFactor( "local3", 0.0 );
	SoundSetTimeScaleFactor( "Mission", 0.0 );
	SoundSetTimeScaleFactor( "Announcer", 0.0 );
	SoundSetTimeScaleFactor( "Bulletimpact", .60 );
	SoundSetTimeScaleFactor( "Voice", 0.40 );
	SoundSetTimeScaleFactor( "effects1", 0.20 );
	SoundSetTimeScaleFactor( "effects2", 0.20 );
	SoundSetTimeScaleFactor( "local", 0.20 );
	SoundSetTimeScaleFactor( "local2", 0.20 );
	SoundSetTimeScaleFactor( "physics", 0.20 );
	SoundSetTimeScaleFactor( "ambient", 0.50 );
	SoundSetTimeScaleFactor( "auto", 0.50 );
}

/*  Example of how to define an envelope 
env_points = [];
env_points[env_points.size] = [0.0, 1.0];
env_points[env_points.size] = [0.2, 0.7];
env_points[env_points.size] = [0.4, 0.5];
env_points[env_points.size] = [1.0, 0.0];
*/

/#
audx_validate_env_array(env_points)
{
	assert(IsDefined(env_points));
	assert(env_points.size >= 2); // need at least 2 points
	
	// assert that the first point defines x = 0 behavior
	first_point = env_points[0];
	assert(first_point[0] == 0.0);
	
	// assert that the last point defines x = 1.0 behavior
	last_point = env_points[env_points.size - 1];
	assert(last_point[0] == 1.0);
	
	// lets enforce that the person who creates the envelope has to do it in increasing x-value order
	prev_x_value = -1.0;
	is_monotonic = true;
	for (i = 0; i < env_points.size; i++)
	{
		point = env_points[i];
		// assert both x and y values are given
		assert(IsDefined(point[0])); 
		assert(IsDefined(point[1]));
		
		// assert that the points are in valid ranges
		
		if(!(point[0] >= 0.0 && point[0] <= 1.0))
			aud_print_error("Envelope x value is out of range.");
		if (!(point[1] >= 0.0 && point[1] <= 1.0))
			aud_print_error("Envelope y value is out of range.");
		
		if (point[0] <= prev_x_value)
		{
			is_monotonic = false;
			break;
		}
		else
		{
			prev_x_value = point[0];
		}
	}
	
	if (!is_monotonic)
	{
		aud_print_error("Supplied envelope array's x-values are not monotonically increasing.");
	}
}
#/

//-----------------------------------------------------------------------------------------------------
//	Audio DVars
//-----------------------------------------------------------------------------------------------------
/#
aud_get_dvar(dvar, default_value_)
{
	result = undefined;
	default_value = 0;	// Assume values are integers, not strings.
	
	// Make sure passed in DVar Name is a valid string.
	assert(IsDefined(dvar) && IsString(dvar));
		
	// Get default value, if any.
	if (IsDefined(default_value_))
	{
		default_value = default_value_;
	}
	
	if (IsString(default_value))	
	{
		result = GetDVar(dvar, default_value);
	}
	else
	{
		result = GetDVarInt(dvar, default_value);
	}	
	
	return result;
}

aud_set_dvar(dvar, value)
{
	assert(IsDefined(dvar) && IsString(dvar));
	assert(IsDefined(value));
	value_str = "";
	if (IsString(value))
	{
		value_str = value;
	}
	else
	{
		value_str = "" + value;
	}
	SetDVar(dvar, value_str);
}

aud_get_debug_submix()
{
	result = aud_get_dvar("_aud_debug_submix", "");
		// NOTE:	Passing in a String default vs. Int indicates 
		// 				that we want a string value not an int value (GetDVar() vs. GetDVarInt()).
	
	if (result == "" || result == "0")
	{
		result = undefined;
	}
	
	return result;
}

aud_set_debug_submix(value)
{
	assert(IsDefined(value) && IsString(value));
	aud_set_dvar("_aud_debug_submix", value);
}

aud_get_debug_mix()
{
	result = aud_get_dvar("_aud_debug_mix", "");	
		// NOTE:	Passing in a String default vs. Int indicates 
		// 				that we want a string value not an int value (GetDVar() vs. GetDVarInt()).
	
	if (result == "" || result == "0")
	{
		result = undefined;
	}
	
	return result;
}

aud_set_debug_mix(value)
{
	assert(IsDefined(value) && IsString(value));
	aud_set_dvar("_aud_debug_mix", value);
}

aud_get_headroom_dvar()
{
	return aud_get_dvar("_aud_headroom", 0);
}

aud_set_headroom_dvar(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_headroom", value);
}

aud_get_godmode()
{
	return aud_get_dvar("_aud_godmode", 0);
}

aud_set_godmode(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_godmode", value);
}

aud_get_verbosity()
{
	return aud_get_dvar("_aud_verbosity", 2);
}

aud_set_verbosity(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_verbosity", value);
}

aud_get_use_iprint()
{
	return aud_get_dvar("_aud_use_iprint", 0);
}

aud_set_use_iprint(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_use_iprint", value);
}

aud_get_print_audio_zones()
{
	return aud_get_dvar("_aud_print_audio_zones", 0);
}

aud_get_assert_on_errors()
{
	return aud_get_dvar("_aud_assert_on_errors", 0);
}

aud_get_print_on_warnings()
{
	return aud_get_dvar("_aud_assert_on_errors", 0);
}

aud_set_print_audio_zones(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_print_audio_zones", value);
}

aud_get_print_music_cues()
{
	return aud_get_dvar("_aud_print_music_cues", 0);
}

aud_set_print_music_cues(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_print_music_cues", value);
}

aud_get_print_synch_frames()
{
	return aud_get_dvar("_aud_print_synch_frames", 0);
}

aud_set_print_synch_frames(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_print_synch_frames", value);
}

aud_get_enable_music()
{
	return aud_get_dvar("_aud_enable_music", 1);
}

aud_set_enable_music(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_enable_music", value);
}

aud_get_enable_streaming()
{
	return aud_get_dvar("_aud_enable_streaming", 1);
}

aud_set_enable_streaming(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_enable_streaming", value);
}

aud_get_enable_azblender()
{
	return aud_get_dvar("_aud_enable_azblender", 1);
}

aud_set_enable_azblender(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_enable_azblender", value);
}

aud_get_enable_callback_trigs()
{
	return aud_get_dvar("_aud_enable_callback_trigs", 1);
}

aud_set_enable_callback_trigs(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_enable_callback_trigs", value);
}

aud_get_enable_player_monitor()
{
	return aud_get_dvar("_aud_enable_player_monitor", 1);
}

aud_set_enable_player_monitor(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_enable_player_monitor", value);
}
	
aud_get_display_mus_sub()
{
	return aud_get_dvar("_aud_display_mus_sub", 0);
}

aud_set_display_mus_sub(value)
{
	assert(IsDefined(value) && !IsString(value));
	aud_set_dvar("_aud_display_mus_sub", value);
}
#/

//-----------------------------------------------------------------------------------------------------
//	ENTITY-BASED PLAY SOUND FUNCTIONS
//-----------------------------------------------------------------------------------------------------


play_2d_sound_internal(aliasname)
{
	self playsound(aliasname, "sounddone");
	self waittill("sounddone");
	wait(0.05);
	self delete();
}

aud_delay_play_2d_sound_internal(aliasname, delay, use_slowmo_)
{
	if (IsDefined(use_slowmo_) && use_slowmo_)
	{
		aud_slomo_wait(delay);
	}
	else
	{
		wait(delay);
	}
	
	ent = spawn("script_origin", level.player.origin);
	ent thread play_2d_sound_internal(aliasname); // this function cleans up "ent"
	return ent;
}

/*
///ScriptDocBegin
"Name: aud_play_2d_sound(<aliasname>)"
"Summary: Plays a 2D sound (using player's positioin for safety) on a new entity."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: aliasname: sound alias string."
"Example: thread aud_play_2d_sound("best_sound_evar");"
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_play_2d_sound(aliasname)
{
	ent = spawn("script_origin", level.player.origin);
	ent thread play_2d_sound_internal(aliasname); // this function cleans up "ent"
	return ent;
}

/*
///ScriptDocBegin
"Name: aud_delay_play_2d_sound(<aliasname>, <delay>)"
"Summary: Plays a 2D sound (using player's positioin for safety) on a new entity after a specified wait time."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: aliasname: sound alias string, delay: float."
"Example: thread aud_play_2d_sound("best_sound_evar", 0.5);"
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_delay_play_2d_sound(aliasname, delay, use_slowmo_)
{
	ent = thread aud_delay_play_2d_sound_internal(aliasname, delay, use_slowmo_);
	return ent;
}

audx_play_linked_sound_internal(type, aliasname, loop_stop_notify_)
{
	if (type == "loop")
	{
		assert(IsDefined(loop_stop_notify_));
		level endon(loop_stop_notify_ + "internal");
		
		self playloopsound(aliasname);
		level waittill(loop_stop_notify_);
		if (IsDefined(self))
		{
			self stoploopsound(aliasname);
			wait(0.05);
			self delete();
		}
	}
	else if (type == "oneshot")
	{
		self playsound(aliasname, "sounddone");
		self waittill("sounddone");
		if (IsDefined(self))
		{
			self delete();
		}
	}
}

audx_monitor_linked_entity_health(ent, loop_stop_notify)
{
	assert(IsDefined(ent));
	assert(IsDefined(loop_stop_notify));
	
	level endon(loop_stop_notify);
	
	while(IsDefined(self))
	{
		wait(0.1);
	}
		
	// tell the normal playloopsound thread, audx_play_linked_sound_internal, to end
	level notify(loop_stop_notify + "internal");
	
	// the linked entity is no longer valid, so if ent is still valid, stop the looping sound + delete the entity
	if (IsDefined(ent))
	{
		ent stoploopsound();
		wait(0.05);
		ent delete();
	}
}

/*
///ScriptDocBegin
"Name: aud_play_linked_sound()"
"Summary: Utility function for playing a sound that is linked to another entity. Returns the entity used, but cleans the entity up itself when sound is done."
"Module: Audio"
"CallOn: Nothing"
"MandatoryArg: aliasname: sound alias string."
"MandatoryArg: ent_to_linkto: entity that you want to attach a sound to."
"OptionalArg: type_: "loop" or "oneshot". If a "loop", you must also supply a loop_stop_notify argument.
"OptionalArg: loop_stop_notify_: message to wait for to stop the loop. to stop the loop, and thus clean up the entity, do a "level notify(loop_stop_notify)" whereever you want."
"Example: thread aud_play_linked_sound(hind_alias, level.player_hind);"
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_play_linked_sound(aliasname, ent_to_linkto, type_, loop_stop_notify_, offset_)
{
	assert(IsDefined(ent_to_linkto));
	assert(IsDefined(aliasname));

	type = "oneshot";
	if (IsDefined(type_))
	{
		assert(type_ == "loop" || type_ == "oneshot");
		type = type_;
	}
	ent = spawn("script_origin", ent_to_linkto.origin);
	if (IsDefined(offset_))
	{
		ent linkto(ent_to_linkto, "tag_origin", offset_, (0, 0, 0));
	}
	else
	{
		ent linkto(ent_to_linkto);
	}
	
	if (type == "loop")
	{
		assertEx(IsDefined(loop_stop_notify_), "aud_play_linked_sound: need to supply a loop_stop_notify arg if using a loop.");
		// monitor the valid-ness of the linked entity to automatically stop the loop and delete the ent
		ent_to_linkto thread audx_monitor_linked_entity_health(ent, loop_stop_notify_);
	}
	
	ent thread audx_play_linked_sound_internal(type, aliasname, loop_stop_notify_);
	return ent;
}

aud_playsound_attach(alias, linktothis, soundtype_)
{
	ent = Spawn( "script_origin", linktothis.origin );
	ent LinkTo(linktothis);
			
	soundtype = "oneshot";
	if (IsDefined(soundtype_))
	{
		soundtype = soundtype_;
	}
			
	if (soundtype == "loop")
	{
		ent playloopsound(alias);
	}
	else
	{
		ent playsound(alias);	
	}
	
	return ent;
}

aud_play_sound_at_internal(alias, pos, duration_)
{
	self PlaySound( alias, "sounddone" );
	
	if (IsDefined(duration_))
	{
		wait(duration_);
		self StopSounds();
	}
	else
	{
		self waittill( "sounddone" );
	}

	wait( 0.05 ); // Avoids pops.	
	self delete();	// Cleanup.
}

aud_play_sound_at(alias, pos, duration_)
{
	assert( IsDefined( alias ) );
	assert( IsDefined( pos ) );	
	
	// Play sound at pos; wait till done; cleanup.
	ent = Spawn( "script_origin", pos );
	ent thread aud_play_sound_at_internal(alias, pos, duration_); // this function cleans up "ent"
	return ent;
}

aud_prime_point_source_loop(alias, position)
{
	// Validate required parms.
	assert(IsString(alias));
	assert(IsDefined(position));	
		
	// Create an entity on which to play the loop.
	loop_entity = Spawn("script_origin", position);
	assert(IsDefined(loop_entity));
	
	// Prime.
	loop_entity thread aud_prime_stream(alias, true, 0.1);
	
	// Return the sound entity.
	return loop_entity;
}

aud_play_primed_point_source_loop(alias, start_vol_, fade_time_)
{
	// Validate required parms.
	assert(IsString(alias));
	assert(IsDefined(self));	
	assert(self aud_is_stream_primed(alias));	
	
	// Get optional params.
	start_vol = aud_get_optional_param(start_vol_, 1.0);
	fade_time = aud_get_optional_param(fade_time_, 1.0);

	// Fade in the loop.
	aud_fade_sound_in(self, alias, start_vol, fade_time, true);
	
	// Release priming; no longer needs to be ready to play.
	aud_release_stream(alias);
}

aud_play_point_source_loop(alias, position, start_vol_, fade_time_)
{
	// Validate required parms.
	assert(IsString(alias));
	assert(IsDefined(position));	

	// Get optional params.
	start_vol = aud_get_optional_param(start_vol_, 1.0);
	fade_time = aud_get_optional_param(fade_time_, 1.0);
		
	// Create an entity on which to play the loop.
	loop_entity = Spawn("script_origin", position);
	assert(IsDefined(loop_entity));

	// Fade in the loop.
	aud_fade_sound_in(loop_entity, alias, start_vol, fade_time, true);
	
	// Return the sound entity.
	return loop_entity;
}

aud_stop_point_source_loop(loop_entity, fade_time_)
{
	// Validate required parms.
	assert(IsDefined(loop_entity));

	// Get optional params.
	fade_time = aud_get_optional_param(fade_time_, 1.0);
	
	// Fade out the sound & delete entity.
	aud_fade_out_and_delete(loop_entity, fade_time);
}

aud_set_point_source_loop_volume(loop_entity, vol, fade_time_)
{
	// Validate required parms.
	assert(IsDefined(loop_entity));
	assert(IsDefined(vol));
	vol = clamp(vol, 0, 1.0);
	
	// Get optional params.
	fade_time = aud_get_optional_param(fade_time_, 1.0);
	
	// Fade out the sound & delete entity.
	loop_entity ScaleVolume(vol, fade_time);
}

// plays a loop on a destructable (given by it's script_noteworthy name)
aud_play_loops_on_destructables_array(destructable_name, loop_alias, end_alias_, update_rate_)
{
	assert(IsString(destructable_name));
	assert(IsString(loop_alias));
	
	update_rate = 0.1; // one frame
	if (IsDefined(update_rate_))
	{
		update_rate = update_rate_;
	}
	
	destruct_entities = getentarray(destructable_name, "script_noteworthy");
	num_destructables = destruct_entities.size;
	
	// play the loop sounds on the entities
	foreach(destruct_ent in destruct_entities)
	{
		destruct_ent playloopsound(loop_alias);
		destruct_ent.loop_sound_stopped = false;   
	}
	
	while(num_destructables > 0)
	{
		wait(update_rate);
		foreach(destruct_ent in destruct_entities)
		{
			if (destruct_ent.health < 0 && !destruct_ent.loop_sound_stopped)
			{
				num_destructables--;
				destruct_ent stoploopsound();
				destruct_ent.loop_sound_stopped = true;
				
				// play destruct sound if given
				if (IsDefined(end_alias_))
				{
					play_sound_in_space(end_alias_, destruct_ent.origin);
				}
			}
		}
	}
}

aud_set_music_submix(volume, fade_time_)
{
	assert(IsDefined(volume));
	submix_name = "music_submix";
	
	// If submix doesn't exist already, create & add it.
	if (!MM_does_volmod_submix_exist(submix_name))
	{
		MM_add_dynamic_volmod_submix(submix_name, ["music", 1.0], fade_time_);
		MM_make_submix_sticky(submix_name);
	}

	// Scale it.
	MM_scale_submix(submix_name, volume, fade_time_);

	/#
	set_music_submix_hud(volume);
	#/
}

aud_set_ambi_submix(volume, fade_time_)
{
	assert(IsDefined(volume));
	submix_name = "ambi_submix";
	
	// If submix doesn't exist already, create & add it.
	if (!MM_does_volmod_submix_exist(submix_name))
	{
		MM_add_dynamic_volmod_submix(submix_name, ["ambience", 1.0], fade_time_);
		MM_make_submix_sticky(submix_name);
	}

	// Scale it.
	MM_scale_submix(submix_name, volume, fade_time_);
}


/#
aud_check_fastfiles()
{
	// Stringtables are disabled when !USING( FASTFILE_LOAD ).
	// Use useFastFile dvar to avoid enabling a broken pathway.
	if ( getDvarInt( "useFastFile", 1 ) == 0 )
	{
		aud_print_warning( "aud_use_string_tables() : Disabled due to dvar useFastFile == 0." );
		return true;
	}
	return false;
}
#/

aud_fade_in_music(fade_time_)
{
	fade_time = 10.0;
	if (IsDefined(fade_time_))
	{
		fade_time = fade_time_;
	}
	
	MM_add_submix("mute_music", 0.1);
	wait(0.05); // Give the system a chance...
	MM_clear_submix("mute_music", fade_time);
}

aud_check_sound_done()
{
	self endon("cleanup");
	if (!IsDefined(self.sounddone))
		self.sounddone = false;

	self waittill("sounddone");
	if (IsDefined(self))
	{
		self.sounddone = true;
		self notify("cleanup");
	}
}

aud_in_zone(zone_name)
{
	assert(IsString(zone_name));
	return equal_strings(AZM_get_current_zone(), zone_name);
}

/#
create_volmod_submix_hud()
{
	while(!IsDefined(level.uiParent))
	{
		wait(0.05);
	}

	level._audio.using_volmod_submix_hud = true;
	
	// store the names for hud object destruction
	level._audio.volmod_submix_hud = [];

	hud_data = undefined;
	if (IsDefined(level._audio.submix_data))
	{
		hud_data = level._audio.submix_data;
	}
	else
	{		
		hud_data = spawnstruct();	
		hud_data.fontsize = 1.0;
		hud_data.value_x = 50;
		hud_data.label_x = 100;
		hud_data.y = 50;
		hud_data.label_color = (0.4, 0.9, 0.6);
		hud_data.value_color = (0.4, 0.6, 0.9);
		hud_data.number_color = (1.0, 1.0, 1.0);
		hud_data.spacing = 10;
		level._audio.submix_data = hud_data;
	}
	
	y = hud_data.y;
	// calculate starting y value -- will be different if also drawing mix-channel submix debug hud
	if (level._audio.using_submix_hud)
	{
		num_submixes = mm_get_num_submixes();
		y = y + hud_data.spacing * ( num_submixes + 1) + 2; // start the y offset after the submix hud
	}
	// the volmod submix header/title
	new_volmod_hud("volmod_submixes_header", hud_data.label_x, y, hud_data.label_color, "Volume Mod Submixes:", hud_data.fontsize);
		
	update_volmod_submix_hud();
}
#/

/#
create_submix_hud()
{
	while(!IsDefined(level.uiParent))
	{
		wait(0.05);
	}
	
	level._audio.using_submix_hud = true;
	level._audio.using_volmod_submix_hud = true;
	
	hud_data = spawnstruct();	
	hud_data.fontsize = 1.0;
	hud_data.value_x = 50;
	hud_data.label_x = 100;
	hud_data.y = 100;
	hud_data.label_color = (0.4, 0.9, 0.6);
	hud_data.value_color = (0.4, 0.6, 0.9);
	hud_data.volmod_color = (0.9, 0.4, 0.6);

	hud_data.number_color = (1.0, 1.0, 1.0);
	hud_data.spacing = 10;
	
	level._audio.submix_data = hud_data;
	
	new_submix_hud("header", hud_data.label_x, hud_data.y, hud_data.label_color, "Submixes:", hud_data.fontsize);
		
	update_volmod_submix_hud();
}
#/

/#
destroy_submix_hud()
{
	foreach(submix_label, value in level._audio.submix_hud)
	{
		name = "submix_" + submix_label;
		DeleteDebugTextHud(name);
	}
	
	foreach(submix_label, value in level._audio.volmod_submix_hud)
	{
		name = "volmod_submix_" + submix_label;
		DeleteDebugTextHud(name);
	}
	level._audio.submix_hud = [];
	level._audio.volmod_submix_hud = [];
	level._audio.using_submix_hud = false;
}
#/
	
/#
new_volmod_hud(store_label, x, y, color, label, fontsize)
{
	CreateDebugTextHud("volmod_submix_" + store_label, x, y, color, label, fontsize);
	level._audio.volmod_submix_hud[store_label] = true;
}	
#/
	
/#
new_submix_hud(store_label, x, y, color, label, fontsize)
{
	CreateDebugTextHud("submix_" + store_label, x, y, color, label, fontsize);
	level._audio.submix_hud[store_label] = true;
}
#/
	
/#
delete_volmod_hud(store_label)
{
	if (IsDefined(level._audio.volmod_submix_hud[store_label]))
	{
		DeleteDebugTextHud("volmod_submix_" + store_label);
		level._audio.volmod_submix_hud[store_label] = undefined;
	}
}
#/
	
/#
delete_submix_hud(store_label)
{
	if (IsDefined(level._audio.submix_hud[store_label]))
	{
		DeleteDebugTextHud("submix_" + store_label);
		level._audio.submix_hud[store_label] = undefined;
	}	
}
#/

	
/#
// this is the indented list of currently applied submixes
update_volmod_submix_hud()
{
	if (level._audio.using_volmod_submix_hud)
	{
		num_volmods = mm_get_num_volmod_submixes();
		
		if (num_volmods <= 0)
			return;
			
		assert(IsDefined(level._audio.submix_data));
		
		hd = level._audio.submix_data;
		
		fontsize = hd.fontsize;
		label_x = hd.label_x;
		label_offset = label_x + 5; // no offset...
		value_color = hd.volmod_color;
		spacing = hd.spacing;
		y = hd.y + spacing;
		
		// first clear submix labels if they exist
		if (!IsDefined(level._audio.volmod_submix_hud))
			level._audio.volmod_submix_hud = [];

		is_different = false;

		// check to see if anything changed
		for (i = 0; i < num_volmods; i++)
		{
			name = mm_get_volmod_submix_name_by_index(i);
			if (!IsDefined(level._audio.volmod_submix_hud[name]))
			{
				is_different = true;
				break;
			}
		}
		
		if (!is_different)
		{
			foreach(submix_name, value in level._audio.volmod_submix_hud)
			{
				if (submix_name != "volmod_submixes_header")
				{
					submix = mm_get_volmod_submix_by_name(submix_name);
					if (!IsDefined(submix))
					{
						is_different = true;
						break;
					}
				}
			}	
		}
		
		
		if (is_different)
		{
			foreach(submix_name, value in level._audio.volmod_submix_hud)
			{
				if (submix_name != "volmod_submixes_header")
				{
					delete_volmod_hud(submix_name);
				}
			}
			
			// calculate starting y value -- will be different if also drawing mix-channel submix debug hud
			if (level._audio.using_submix_hud)
			{
				num_submixes = mm_get_num_submixes();
				y = y + spacing * ( num_submixes); // start the y offset after the submix hud
			}
			
			// now add the new labels for the submixes
			for (i = 0; i < num_volmods; i++)
			{
				volmod_submix_name = mm_get_volmod_submix_name_by_index(i);
				assert(IsDefined(volmod_submix_name));
				
				if (!IsDefined(level._audio.volmod_submix_hud[volmod_submix_name]))
				{ 
					label = i + " - " + volmod_submix_name; // give the index of the volmod, so that it lines up with the volmod submix matrix
					new_volmod_hud(volmod_submix_name, label_offset, y, value_color, label, fontsize);
					y += spacing;
				}
			}
		}
	}
}
#/

/#
destroy_volmod_submix_hud()
{
	
}
#/

/#
create_ambience_hud()
{
	level._audio.using_ambi_hud = true;
	// make sure the hud stuff is initialized
	while(!IsDefined(level.uiParent))
	{
		wait(0.05);
	}
	
	// store the names for easy destruction
	level._audio.hud = [];
	
	// store data to prevent reseting values
	level._audio.hud_data = [];
	
	fontsize = 1.0;
	value_x = 530;
	label_x = value_x - 75;
	y = 150;
	label_color = ( 0.4, 0.9, 0.6 );
	value_color = ( 0.4, 0.6, 0.9 );
	zone_color = ( 0.4, 0.9, 0.9 );
	number_color = (1.0, 1.0, 1.0);
	indent = 10; // sub-text from streamed ambience
	amp_indent = 30; // indents from label
	label_indent = amp_indent + 50; // indents from the amplitude
	zone_indent = 10;
	
	// ZONE
	CreateDebugTextHud( "zone_label", label_x, y, label_color, "Zone:", fontsize);
	CreateDebugTextHud( "zone_value", value_x, y, label_color, "", fontsize);
	
	level._audio.hud[level._audio.hud.size] = "zone_label";
	level._audio.hud[level._audio.hud.size] = "zone_value";
	
	// STREAM
	y += 13;
	
	CreateDebugTextHud( "stream_preset_label", label_x  + zone_indent, y, zone_color, "Streamed Ambience:", fontsize );
	CreateDebugTextHud( "stream_preset_label_value", value_x, y, zone_color, "", fontsize); // current streamed ambience

	level._audio.hud[level._audio.hud.size] = "stream_preset_label";
	level._audio.hud[level._audio.hud.size] = "stream_preset_label_value";

	// STREAM FROM
	y += 10;
	
	CreateDebugTextHud( "stream_preset_label_from", label_x  + zone_indent + indent, y, value_color, "From:", fontsize); // from label
	CreateDebugTextHud( "stream_preset_value_from_amp", label_x  + zone_indent + amp_indent, y, number_color, "", fontsize); // amp
	CreateDebugTextHud( "stream_preset_value_from", value_x, y, value_color, "", fontsize); // from stream name

	level._audio.hud[level._audio.hud.size] = "stream_preset_label_from";
	level._audio.hud[level._audio.hud.size] = "stream_preset_value_from_amp";
	level._audio.hud[level._audio.hud.size] = "stream_preset_value_from";

	// STREAM TO
	y += 10;
	
	CreateDebugTextHud( "stream_preset_label_to", label_x  + zone_indent + indent, y, value_color, "To:", fontsize); // to label
	CreateDebugTextHud( "stream_preset_value_to_amp", label_x  + zone_indent + amp_indent, y, number_color, "", fontsize); // amp
	CreateDebugTextHud( "stream_preset_value_to", value_x, y, value_color, "", fontsize); // to stream name

	level._audio.hud[level._audio.hud.size] = "stream_preset_label_to";
	level._audio.hud[level._audio.hud.size] = "stream_preset_value_to_amp";
	level._audio.hud[level._audio.hud.size] = "stream_preset_value_to";

	// DAMB
	y += 13;
	
	CreateDebugTextHud( "damb_preset_label", label_x + zone_indent, y, zone_color, "Dynamic Ambience:", fontsize );
	CreateDebugTextHud( "damb_preset_value", value_x, y, zone_color, "", fontsize);
	
	level._audio.hud[level._audio.hud.size] = "damb_preset_label";
	level._audio.hud[level._audio.hud.size] = "damb_preset_value";
	
	// DAMB FROM
	y += 10;
	
	CreateDebugTextHud( "damb_preset_label_from", label_x  + zone_indent + indent, y, value_color, "From:", fontsize); // from label
	CreateDebugTextHud( "damb_preset_value_from_amp", label_x  + zone_indent + amp_indent, y, number_color, "", fontsize); // amp
	CreateDebugTextHud( "damb_preset_value_from", value_x, y, value_color, "", fontsize); // from stream name

	level._audio.hud[level._audio.hud.size] = "damb_preset_label_from";
	level._audio.hud[level._audio.hud.size] = "damb_preset_value_from_amp";
	level._audio.hud[level._audio.hud.size] = "damb_preset_value_from";
	
	// DAMB TO
	y += 10;
	
	CreateDebugTextHud( "damb_preset_label_to", label_x  + zone_indent + indent, y, value_color, "To:", fontsize); // to label
	CreateDebugTextHud( "damb_preset_value_to_amp", label_x  + zone_indent + amp_indent, y, number_color, "", fontsize); // amp
	CreateDebugTextHud( "damb_preset_value_to", value_x, y, value_color, "", fontsize); // to stream name

	level._audio.hud[level._audio.hud.size] = "damb_preset_label_to";
	level._audio.hud[level._audio.hud.size] = "damb_preset_value_to_amp";
	level._audio.hud[level._audio.hud.size] = "damb_preset_value_to";
	
	
	// MIX
	y += 13;
	
	CreateDebugTextHud( "mix_preset_label", label_x + zone_indent, y, zone_color, "Mix:", fontsize );
	CreateDebugTextHud( "mix_preset_value", value_x, y, zone_color, "", fontsize);
	
	level._audio.hud[level._audio.hud.size] = "mix_preset_label";
	level._audio.hud[level._audio.hud.size] = "mix_preset_value";
	
	// REVERB
	y += 13;
	
	CreateDebugTextHud( "reverb_preset_label", label_x + zone_indent, y, zone_color, "Reverb:", fontsize );
	CreateDebugTextHud( "reverb_preset_value", value_x, y, zone_color, "", fontsize);
	
	level._audio.hud[level._audio.hud.size] = "reverb_preset_label";
	level._audio.hud[level._audio.hud.size] = "reverb_preset_value";
	
	// FILTER
	y += 13;
	
	CreateDebugTextHud( "filter_preset_label", label_x + zone_indent, y, zone_color, "Filter:", fontsize );
	CreateDebugTextHud( "filter_preset_value", value_x, y, zone_color, "", fontsize);
	
	level._audio.hud[level._audio.hud.size] = "filter_preset_label";
	level._audio.hud[level._audio.hud.size] = "filter_preset_value";
	
	// FILTER FROM
	y += 10;
	
	CreateDebugTextHud( "filter_preset_label_from", label_x  + zone_indent + indent, y, value_color, "From:", fontsize); // from label
	CreateDebugTextHud( "filter_preset_value_from_amp", label_x  + zone_indent + amp_indent, y, number_color, "", fontsize); // amp
	CreateDebugTextHud( "filter_preset_value_from", value_x, y, value_color, "", fontsize); // from stream name

	level._audio.hud[level._audio.hud.size] = "filter_preset_label_from";
	level._audio.hud[level._audio.hud.size] = "filter_preset_value_from_amp";
	level._audio.hud[level._audio.hud.size] = "filter_preset_value_from";

	// FILTER TO
	y += 10;
	
	CreateDebugTextHud( "filter_preset_label_to", label_x  + zone_indent + indent, y, value_color, "To:", fontsize); // to label
	CreateDebugTextHud( "filter_preset_value_to_amp", label_x  + zone_indent + amp_indent, y, number_color, "", fontsize); // amp
	CreateDebugTextHud( "filter_preset_value_to", value_x, y, value_color, "", fontsize); // to stream name

	level._audio.hud[level._audio.hud.size] = "filter_preset_label_to";
	level._audio.hud[level._audio.hud.size] = "filter_preset_value_to_amp";
	level._audio.hud[level._audio.hud.size] = "filter_preset_value_to";
	
	// OCCLUSION
	y += 13;
	
	CreateDebugTextHud( "occlusion_preset_label", label_x + zone_indent, y, zone_color, "Occlussion:", fontsize );
	CreateDebugTextHud( "occlusion_preset_value", value_x, y, zone_color, "", fontsize);

	level._audio.hud[level._audio.hud.size] = "occlusion_preset_label";
	level._audio.hud[level._audio.hud.size] = "occlusion_preset_value";
	
	// MUSIC
	y += 15;
	
	CreateDebugTextHud( "music_preset_label", label_x, y, label_color, "Music:", fontsize );
	CreateDebugTextHud( "music_preset_value", value_x, y, label_color, "", fontsize);
	
	level._audio.hud[level._audio.hud.size] = "music_preset_label";
	level._audio.hud[level._audio.hud.size] = "music_preset_value";

	// MUSIC SUBMIX
	y += 13;
	
	CreateDebugTextHud( "music_submix_label", label_x + zone_indent, y, zone_color, "Music Submix:", fontsize );
	CreateDebugTextHud( "music_submix_value", value_x, y, number_color, "", fontsize);
	
	level._audio.hud[level._audio.hud.size] = "music_submix_label";
	level._audio.hud[level._audio.hud.size] = "music_submix_value";

	// DAMB ENTITY COUNTER
	y += 15;
		
	CreateDebugTextHud( "damb_entity_count_label", label_x, y, label_color, "Ambient Entity Count:", fontsize );
	CreateDebugTextHud( "damb_entity_count_value", value_x, y, number_color, "", fontsize);
	level._audio.hud[level._audio.hud.size] = "damb_entity_count_label";
	level._audio.hud[level._audio.hud.size] = "damb_entity_count_value";
	
	set_hud_values();
}
#/

/#
set_hud_values()
{
	assert(IsDefined(level._audio.hud_input));
	if (IsDefined(level._audio.hud_input.occlusion))
	{
		set_occlusion_hud(level._audio.hud_input.occlusion);
	}
	
	if (IsDefined(level._audio.hud_input.filter_from_name))
	{
		name = level._audio.hud_input.filter_from_name;
		amp = level._audio.hud_input.filter_from_amp;
		set_filter_from_hud(name, amp);
	}
	
	if (IsDefined(level._audio.hud_input.filter_to_name))
	{
		name = level._audio.hud_input.filter_to_name;
		amp = level._audio.hud_input.filter_to_amp;
		set_filter_to_hud(name, amp);
	}
	
	if (IsDefined(level._audio.hud_input.filter))
	{
		name = level._audio.hud_input.filter;
		set_filter_hud(name);
	}
	
	if (IsDefined(level._audio.hud_input.reverb))
	{
		name = level._audio.hud_input.reverb;
		set_reverb_hud(name);
	}
	
	if (IsDefined(level._audio.hud_input.mix))
	{
		name = level._audio.hud_input.mix;
		set_mix_hud(name);
	}
	
	if (IsDefined(level._audio.hud_input.damb_from_name))
	{
		name = level._audio.hud_input.damb_from_name;
		amp = level._audio.hud_input.damb_from_amp;
		set_damb_from_hud(name, amp);
	}
	
	if (IsDefined(level._audio.hud_input.damb_to_name))
	{
		name = level._audio.hud_input.damb_to_name;
		amp = level._audio.hud_input.damb_to_amp;
		set_damb_to_hud(name, amp);
	}
	
	if (IsDefined(level._audio.hud_input.damb))
	{
		name = level._audio.hud_input.damb;
		set_damb_hud(name);
	}
	
	if (IsDefined(level._audio.hud_input.stream_from_name))
	{
		name = level._audio.hud_input.stream_from_name;
		amp = level._audio.hud_input.stream_from_amp;
		set_stream_from_hud(name, amp);
	}
	
	if (IsDefined(level._audio.hud_input.stream_to_name))
	{
		name = level._audio.hud_input.stream_to_name;
		amp = level._audio.hud_input.stream_to_amp;
		set_stream_to_hud(name, amp);
	}
	
	if (IsDefined(level._audio.hud_input.stream))
	{
		name = level._audio.hud_input.stream;
		set_stream_hud(name);
	}
	
	if (IsDefined(level._audio.hud_input.zone))
	{
		name =level._audio.hud_input.zone;
		set_zone_hud(name);
	}
	
	if (IsDefined(level._audio.hud_input.music))
	{
		name = level._audio.hud_input.music;
		set_music_hud(name);
	}
	
	if (IsDefined(level._audio.hud_input.music_submix))
	{
		amp = level._audio.hud_input.music_submix;
		set_music_submix_hud(amp);
	}
}
#/

/#
set_occlusion_hud(name)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.occlusion = name;
	thread set_hud_data(name, "occlusion_preset_value");
}
#/

/#
set_filter_from_hud(name, amp)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.filter_from_name = name;
	level._audio.hud_input.filter_from_hud = amp;
	thread set_from_or_to(name, amp, "filter_preset_value_from", "filter_preset_value_from_amp");
}
#/

/#
set_filter_to_hud(name, amp)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.filter_to_name = name;
	level._audio.hud_input.filter_to_hud = amp;
	thread set_from_or_to(name, amp, "filter_preset_value_to", "filter_preset_value_to_amp");
}
#/

/#
set_filter_hud(name)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.filter = name;
	thread set_hud_data(name, "filter_preset_value");
}
#/

/#
set_reverb_hud(name)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.reverb = name;
	thread set_hud_data(name, "reverb_preset_value");
}
#/

/#
set_mix_hud(name)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.mix = name;
	thread set_hud_data(name, "mix_preset_value");
}
#/

/#
set_damb_from_hud(name, amp)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.damb_from_name = name;
	level._audio.hud_input.damb_from_amp = amp;
	thread set_from_or_to(name, amp, "damb_preset_value_from", "damb_preset_value_from_amp");
}
#/

/#
set_damb_to_hud(name, amp)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.damb_to_name = name;
	level._audio.hud_input.damb_to_amp = amp;
	thread set_from_or_to(name, amp, "damb_preset_value_to", "damb_preset_value_to_amp");
}
#/

/#
set_damb_hud(name)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.damb = name;
	thread set_hud_data(name, "damb_preset_value");
}
#/

/#
set_stream_from_hud(name, amp)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.stream_from_name = name;
	level._audio.hud_input.stream_from_amp = amp;
	thread set_from_or_to(name, amp, "stream_preset_value_from", "stream_preset_value_from_amp");
}
#/

/#
set_stream_to_hud(name, amp)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.stream_to_name = name;
	level._audio.hud_input.stream_to_amp = amp;
	thread set_from_or_to(name, amp, "stream_preset_value_to", "stream_preset_value_to_amp");
}
#/

/#
set_stream_hud(name)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.stream = name;
	thread set_hud_data(name, "stream_preset_label_value");
}
#/

/#
set_zone_hud(name)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.zone = name;
	thread set_hud_data(name, "zone_value");
}
#/

/#
set_music_hud(name)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.music = name;
	thread set_hud_data(name, "music_preset_value");
}
#/

/#
set_music_submix_hud(value)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.music_submix = value;
	
	if (level._audio.using_ambi_hud)
	{
		// make sure the hud stuff is initialized
		while(!Isdefined(level._audio.hud))
		{
			wait(0.05);
		}
		
		assert(IsDefined(level._audio.hud_data));
		
		if (!IsDefined(level._audio.hud_data["music_submix_value"]))
			level._audio.hud_data["music_submix_value"] = "";
		
		string_value = value + "";
		if (level._audio.hud_data["music_submix_value"] != string_value)
		{
			level._audio.hud_data["music_submix_value"] = string_value;
			PrintDebugTextHud( "music_submix_value", value );
		}
	}
}
#/

/#
set_damb_entity_hud(value)
{
	assert(IsDefined(level._audio.hud_input));
	level._audio.hud_input.entity = value;
	
	if (level._audio.using_ambi_hud)
	{
		// make sure the hud stuff is initialized
		while(!Isdefined(level._audio.hud))
		{
			wait(0.05);
		}
		

		assert(IsDefined(level._audio.hud_data));
		
		if (!IsDefined(level._audio.hud_data["damb_entity_count_value"]))
			level._audio.hud_data["damb_entity_count_value"] = "";
		
		string_value = value + "";
		if (level._audio.hud_data["damb_entity_count_value"] != string_value)
		{
			level._audio.hud_data["damb_entity_count_value"] = string_value;
			PrintDebugTextHud( "damb_entity_count_value", value );
		}
	}
}
#/

/#
set_hud_data(name, preset_value)
{
	if (level._audio.using_ambi_hud)
	{
		// make sure the hud stuff is initialized
		while(!Isdefined(level._audio.hud))
		{
			wait(0.05);
		}
		
		if (!IsDefined(name))
		{
			name = "";
		}
		
		if (!IsDefined(preset_value))
		{
			preset_value = "";
		}

		assert(IsDefined(level._audio.hud_data));
		assert(IsString(preset_value));
		
		if (!IsDefined(level._audio.hud_data[preset_value]))
			level._audio.hud_data[preset_value] = "";
		
		if (level._audio.hud_data[preset_value] != name)
		{
			level._audio.hud_data[preset_value] = name;
			PrintDebugTextStringHud( preset_value, name );
		}
	}
}
#/

/#
// utility to set from or to labels in audio debug hud
set_from_or_to(name, amp, preset_value, preset_amp)
{
	if (level._audio.using_ambi_hud)
	{
		// make sure the hud stuff is initialized
		while(!Isdefined(level._audio.hud))
		{
			wait(0.05);
		}
		
		if (!IsDefined(name))
			name = "";
			
		if (!IsDefined(amp) || name == "")
			amp = "";
		
		assert(IsDefined(level._audio.hud_data));
		if (!IsDefined( level._audio.hud_data[preset_value]))
			level._audio.hud_data[preset_value] = "";
		
		if (level._audio.hud_data[preset_value] != name)
		{
			level._audio.hud_data[preset_value] = name;
			PrintDebugTextStringHud( preset_value, name );
		}

		if (!IsDefined( level._audio.hud_data[preset_amp]))
			level._audio.hud_data[preset_amp] = "";
		
		amp_string = amp + "";
		if (level._audio.hud_data[preset_amp] != amp_string)
		{
			level._audio.hud_data[preset_amp] = amp_string;
			if (IsString(amp))
			{
				PrintDebugTextStringHud(preset_amp, amp);
			}
			else
			{
				val = int(amp*1000);
				PrintDebugTextHud(preset_amp, val / 1000.0);
			}
		}
	}
}
#/

/#
destroy_ambience_hud()
{
	if (Isdefined(level._audio.hud))
	{
		for (i = 0; i < level._audio.hud.size; i++)
		{
			DeleteDebugTextHud(level._audio.hud[i]);
		}
		level._audio.hud = undefined;
		level._audio.hud_data = undefined;
		level._audio.using_ambi_hud = false;
	}
}
#/

/#
debug_hud_disabled()
{
	if ( getdvar( "loc_warnings", 0 ) == "1" )
		return true;
	if ( getdvarint( "debug_hud" ) )
		return true;
	return !isdefined( level._audio.hud );
}
#/


/#
aud_dvar_monitor_thread()
{
	wait( 0.1 ); // init wait for system initializations	
	while ( 1 )
	{
		wait( 0.5 );
		check_debug_mix_dvar();
		check_zone_hud_dvar();
		check_submix_hud_dvar();
	}
}
#/

/#
check_zone_hud_dvar()
{
	SetDvarIfUninitialized( "zone_hud", "0");
	dvar = GetDvar( "zone_hud" );
	if ( dvar == "1" )
	{
		if (!level._audio.using_ambi_hud)
		{
			create_ambience_hud();
		}
	}
	else if ( dvar == "0" )
	{
		if (level._audio.using_ambi_hud)
		{
			destroy_ambience_hud();
		}
	}

}
#/
	
/#
check_submix_hud_dvar()
{
	SetDvarIfUninitialized( "submix_hud", "0" );
	dvar = GetDvar( "submix_hud" );
	if ( dvar == "1")
	{
		if (!level._audio.using_submix_hud)
		{
			create_submix_hud();
		}				
	}
	else if ( dvar == "0" )
	{
		if (level._audio.using_submix_hud)
		{
			destroy_submix_hud();
		}
	}
}
#/
	
/#
check_debug_mix_dvar()
{
	SetDvarIfUninitialized( "debug_mix", "0" );
	if ( !IsDefined( level._audio ) )
	{
		return;
	}

	if ( !IsDefined( level._audio.mix ) )
	{
		return;
	}

	if ( !IsDefined( level._audio.mix.curr_preset ) )
	{
		return;
	}

	dvar = GetDvar( "debug_mix" );
	if ( dvar != "0" && dvar != level._audio.mix.curr_preset )
	{
		MM_start_preset( dvar, 0.5 );
	}	
}
#/

aud_find_exploder( num )
{
	if (isdefined(level.createFXexploders))
	{
		exploders = level.createFXexploders[""+num];
		if (isdefined(exploders))
			return exploders[0];
	}
	else
	{
		for ( j = 0;j < level.createFXent.size;j++ )
		{		
			fx_ent = level.createFXent[ j ];
			if ( !isdefined( fx_ent ) )
				continue;
							
			if ( fx_ent.v[ "type" ] != "exploder" )
				continue;
							
			if ( !isdefined( fx_ent.v[ "exploder" ] ) )
				continue;
							
			if ( int(fx_ent.v[ "exploder" ]) != num )
				continue;			
			
			return fx_ent;
		}
	}	
	return undefined;
}

aud_duck(submix, duck_time, fade_in_, fade_out_)
{
	thread audx_duck(submix, duck_time, fade_in_, fade_out_);
}

audx_duck(submix, duck_time, fade_in_, fade_out_)
{
	assert(IsString(submix));
	assert(IsDefined(duck_time));
	duck_time = clamp(duck_time, 0, 10);
	
	fade_in = 1.0;
	if (IsDefined(fade_in_))
	{
		fade_in = fade_in_;
	}

	fade_out = fade_in;
	if (IsDefined(fade_out_))
	{
		fade_out = fade_out_;
	}
		
	MM_add_submix(submix, fade_in);
	wait(duck_time);
	MM_clear_submix(submix, fade_out);	
}


// a struct which will contain presetnames/rownum pairs, used to optimize preset lookup
get_index_struct()
{
	index = spawnstruct();
	index.filter = [];
	index.mix = [];
	index.occlusion = [];
	index.timescale = [];
	index.indexed = false; // whether or not this has been indexed
	return index;
}

// INDEX PRESET FILES
aud_index_presets()
{
	assert(IsDefined(level._audio.index.local));
	level._audio.index.local.mix			= index_stringtable_internal(get_mix_stringtable());
	level._audio.index.local.filter		= index_stringtable_internal(get_filter_stringtable());
	level._audio.index.local.indexed 	= true;
}

aud_is_local_indexed()
{
	return level._audio.index.local.indexed;
}

index_common_presets()
{
	assert(IsDefined(level._audio.index.common));
	level._audio.index.common.mix				= index_stringtable_internal("soundtables/common_mix.csv");
	level._audio.index.common.occlusion	= index_stringtable_internal("soundtables/common_occlusion.csv");
	level._audio.index.common.timescale	= index_stringtable_internal("soundtables/common_timescale.csv");
	level._audio.index.common.filter		= index_stringtable_internal("soundtables/common_filter.csv");
	level._audio.index.common.indexed 	= true;
}

aud_is_common_indexed()
{
	return level._audio.index.common.indexed;
}

get_indexed_preset(type, preset_name, is_common_)
{
	assert(IsString(type));
	assert(IsString(preset_name));
	
	is_common = true;
	if (IsDefined(is_common_))
	{
		is_common = is_common_;
	}

	index_struct = undefined;

	if (is_common)
		index_struct = level._audio.index.common;
	else
		index_struct = level._audio.index.local;
	
	assert(IsDefined(index_struct));
	
	index = undefined;
	switch(type)
	{
		case "mix":
		index = index_struct.mix[preset_name];
		break;
		case "filter":
		index = index_struct.filter[preset_name];
		break;
		case "occlusion": 
		index = level._audio.index.common.occlusion[preset_name];
		break;
		case "timescale":
		index = level._audio.index.common.timescale[preset_name];
		break;
		default:
		break;
	}
	
	// if preset doesn't exist in index arrays, return -1
	if (!IsDefined(index))
		index = -1;

	return index;
}

get_mix_index(preset_name, is_common)
{
	assert(IsString(preset_name));
	assert(IsDefined(is_common));
	if (is_common)
	{
		return level._audio.index.common.mix[preset_name];
	}
	else
		return level._audio.index.local.mix[preset_name];
}

index_stringtable_internal(preset_file)
{
	assert(IsString(preset_file));
	
	curr_preset_name = "";
	blank_count = 0;
	row_count = 1;
	result = [];
	preset_name = "";
	while(blank_count < 10 && preset_name != "EOF")
	{
		preset_name = tablelookupbyrow(preset_file, row_count, 0);
		// NOTE: this will index "#" comments, but that's ok... rather not have to compare/construct substrings per row
		if (IsDefined(preset_name) && preset_name != curr_preset_name && preset_name != "" && preset_name != "EOF")
		{
			blank_count = 0;
			curr_preset_name = preset_name;
			/#
			if (IsDefined(result[curr_preset_name]))
			{
				aud_print_error("in preset file, " + preset_file + ", " + curr_preset_name + " is a duplicate entry!");
			}
			#/
			result[curr_preset_name] = row_count;
		}
		else if (preset_name == "")
		{
			blank_count++;
		}
		row_count++;
	}
	return result;
}

aud_percent_chance(percent)
{
	assert(IsDefined(percent)&& percent >= 0 && percent <= 100);
	return RandomIntRange(1, 100) <= percent;
}

/*

aud_play_paris_gunshot(weapontype)
{
	switch(weapontype)
	{
		case "grenade": // or whatever
			level.player playsound("grenade");
		break;
		
		case "missile":
			level.player playsound("missile");
		break;
		
		default:
			level.player playsound("mygunshot");
		break;
	}
}

aud_play_paris_impact(weapontype, damage, attacker, point, type)
{
	
}

// when the slow mo starts
thread aud_start_slow_mo_gunshot_callback(::aud_play_paris_gunshot, ::aud_play_paris_impact);

// when the slow mo endsliding
aud_stop_slow_mo_gunshot_callback();
*/

aud_start_slow_mo_gunshot_callback(gunshot_function_callback, impact_function_callback)
{
	assert(IsDefined(gunshot_function_callback));
	assert(IsDefined(impact_function_callback));
	
	level endon("aud_stop_slow_mo_gunshot");
	
	bad_guys = GetAiArray("axis");
	foreach(bad_guy in bad_guys)
	{
		bad_guy thread aud_impact_monitor(impact_function_callback);
	}
	
	button_triggered = false;
	weapon_type = level.player GetCurrentWeapon();
	while(true)
	{
		if (level.player AttackButtonPressed())
		{
			if (!button_triggered)
			{
				button_triggered = true;
				[[ gunshot_function_callback ]](weapon_type); // callback the function which does the sound effect (slow_mo_woosh)
			}
		}
		else
		{
			button_triggered = false;
		}
		wait(0.05);
	}
}

aud_impact_monitor(impact_function_callback)
{
	level endon("aud_stop_slow_mo_gunshot");
	
	assert(IsDefined(impact_function_callback));
	weapon_type = level.player GetCurrentWeapon();

	while(true)
	{
		self waittill("damage", damage, attacker, direction_vec, point, type);
		if (IsDefined(point))
		{
			[[impact_function_callback]](weapon_type, damage, attacker, point, type);
		}
	}
}

aud_stop_slow_mo_gunshot_callback()
{
	level notify("aud_stop_slow_mo_gunshot");
}

/*
///ScriptDocBegin
"Name: aud_play_distributed_sound(<alias_name>, <points>, <edge_spread>, <min_dist>, <max_dist>, [update_rate], [vol_scale])"
"Summary: Plays a 2D, mono-source sound as if it was distributed amongst the given array of points."
"Module: Audio"
"CallOn: Entity handle"
"MandatoryArg: <alias_name> : A 2D, mono-source alias name."
"MandatoryArg: <points> : An array of points (up to 16) that act as the distributed sound source."
"MandatoryArg: <edge_spread> : The length of the "virtual" speaker box around player."
"MandatoryArg: <min_dist> : Min dist of a point (same as min_dist in an alias)."
"MandatoryArg: <max_dist> : Max dist of a point (same as max_dist in an alias)."
"OptionalArg: [update_rate]: The time between updating the dynamic speaker map."
"OptionalArg: [vol_scale]: An additional volume scale on the 2D sound."
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_play_distributed_sound(alias_name, points, edge_spread, min_dist_, max_dist_, update_rate_, vol_scale_)
{
	return;	// shipping hack to avoid use of flawed distrbuted sound feature - only used for fountains in dubai
	
	assert(IsDefined(self));
	
	self.IsDistributedSound = true;
	
	// store arguments so it can be started/stopped at will
	self.alias = alias_name;
	self.points = points;
	self.edge_spread = edge_spread;
	self.update_rate = update_rate_;
	self.min_dist = min_dist_;
	self.max_dist = max_dist_;
	self.vol_scale = vol_scale_;
	
	self PlayLoopSound(alias_name);
	wait(0.1);
	self thread audx_distributed_sound_update_loop(points, edge_spread, update_rate_, min_dist_, max_dist_, vol_scale_ );
}

aud_stop_distributed_sound()
{
	self notify("stop");
}

aud_start_distributed_sound()
{
	return;	// shipping hack to avoid use of flawed distrbuted sound feature - only used for fountains in dubai
	
	if (IsDefined(self.IsDistributedSound))
	{
		assert(IsDefined(self.alias));
		self PlayLoopSound(self.alias);
		wait(0.1);
		self thread audx_distributed_sound_update_loop(self.points, self.edge_spread, self.update_rate, self.min_dist, self.max_dist, self.vol_scale);
	}
}

audx_distributed_sound_update_loop(points, edge_spread, update_rate_, min_dist_, max_dist_, vol_scale_)
{
	self endon("stop");
	
	update_rate = 0.1;
	if (IsDefined(update_rate_))
	{
		update_rate = update_rate_;
	}
	
	vol_scale = 1.0;
	if (IsDefined(vol_scale_))
	{
		vol_scale = vol_scale_;
	}
	
	if (IsDefined(min_dist_))
	{
		if (!IsDefined(max_dist_))
			return;
			
		while(IsDefined(self))
		{
			self SetDistributed2DSound(points, edge_spread, update_rate, vol_scale, min_dist_, max_dist_);
			wait(update_rate);
		}
	}
	else
	{
		while(IsDefined(self))
		{
			self SetDistributed2DSound(points, edge_spread, update_rate, vol_scale);
			wait(update_rate);
		}
	}
	
}

/*
///ScriptDocBegin
"Name: aud_slomo_wait(<waitttime>)"
"Summary: A wait that acts as if there was no timescale active -- compatible with timescale lerping, has some error, so use carefully."
"Module: Audio"
"CallOn: Nothing. Use as if it was a normal wait."
"MandatoryArg: <waitttime> : Waittime, as if game was no in timescale"
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_slomo_wait(waittime)
{
	waitent = spawn("script_origin", (0,0,0));
	waitent thread aud_slomo_wait_internal(waittime);
	waitent waittill("slo_mo_wait_done");
	waitent delete();
}

aud_slomo_wait_internal(waittime)
{
	total_wait = 0;
	while(total_wait < waittime)
	{
		timescale_val = GetDvarFloat("com_timescale");
		total_wait += 0.05 / timescale_val;
		wait(0.05);
	}
	self notify("slo_mo_wait_done");
}

aud_set_level_fade_time(fadetime)
{
	if (!IsDefined(level._audio))  
	{
		level._audio = spawnstruct();
	}
	level._audio.level_fade_time = fadetime;
}

aud_level_fadein()
{
	if (!IsDefined(level._audio.level_fade_time))
	{
		level._audio.level_fade_time = 1.0; // default...
	}
	wait(0.05);
	levelsoundfade(1, level._audio.level_fade_time);    
}

aud_is_specops()
{
	return IsDefined(level._audio.specops);
}

audx_set_spec_ops_internal()
{
	if (!IsDefined(level._audio))
	{
		level._audio = spawnstruct();
	}
	level._audio.specops = true;
	
	/#
	if (!IsDefined(level.players))
	{
		level waittill("level.players initialized");
	}
	
	// initialize a "zones" array to hold data on the current zones players are in
	level._audio.specops_zones = [];
	
	for(i = 0; i < level.players.size; i++)
	{
		level._audio.specops_zones[i] = spawnstruct();
		level._audio.specops_zones[i].player = level.players[i]; // the player entity for this zone
		level._audio.specops_zones[i].zonename = "none"; // the name of the zone this player is in
	}
	#/
}

/*
///ScriptDocBegin
"Name: aud_set_spec_ops()"
"Summary: Tells audio scripts it is in specops mode, which changes behavior of audio zones."
"Module: Audio"
"CallOn: Nothing."
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_set_spec_ops()
{
	thread audx_set_spec_ops_internal();
}

audx_play_line_emitter_internal()
{
	assert(IsString(self.label));
	assert(IsString(self.alias));
	assert(self.is_playing == false);
	assert(IsDefined(self.point1));
	assert(IsDefined(self.point2));
	assert(IsDefined(self.fade_in));
	
	level endon(self.label + "_line_emitter_stop");
	
	start_to_end = self.point2 - self.point1;
	start_to_end_norm = VectorNormalize(start_to_end);
	start_to_end_mag = Distance(self.point1, self.point2);
	
	update_rate = 0.1;
	
	while(true)
	{
		start_to_player = level.player.origin - self.point1;
		player_proj = VectorDot(start_to_player, start_to_end_norm);
		player_proj = clamp(player_proj, 0, start_to_end_mag);
		
		sound_origin = self.point1 + start_to_end_norm*player_proj;
		
		if (!self.is_playing)
		{
			self.origin = sound_origin; 
			self playloopsound(self.alias);
			self scalevolume(0);
			wait(0.05);
			self scalevolume(1.0, self.fade_in);
			self.is_playing = true;
		}
		else
		{
			self moveto(sound_origin, update_rate);
		}
		wait(update_rate);
	}
}

/*
///ScriptDocBegin
"Name: aud_slomo_wait(<waitttime>)"
"Summary: A wait that acts as if there was no timescale active -- compatible with timescale lerping, has some error, so use carefully."
"Module: Audio"
"CallOn: Nothing. Use as if it was a normal wait."
"MandatoryArg: <waitttime> : Waittime, as if game was no in timescale"
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_stop_line_emitter(label)
{
	level notify(label + "_line_emitter_stop");
}

/*
///ScriptDocBegin
"Name: aud_play_line_emitter(<label>, <alias>, <point1>, <point2>, [fade_], [fade_out_])"
"Summary: Play a sound on nearest point between two points."
"Module: Audio"
"CallOn: Nothing. Use as if it was a normal wait."
"MandatoryArg: <waitttime> : Waittime, as if game was no in timescale"
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_play_line_emitter(label, alias, point1, point2, fade_, fade_out_)
{
	assert(IsString(label));
	assert(IsString(alias));
	assert(IsDefined(point1));
	assert(IsDefined(point2));
	
	fade_in = 0.1;
	fade_out = 0.1;
	
	if (IsDefined(fade_))
	{
		fade_in = max(fade_, 0);
		fade_out = max(fade_, 0);
	}
	
	if (IsDefined(fade_out_))
	{
		fade_out = max(fade_out_, 0);
	}
	
	ent = spawn("script_origin", (0,0,0));

	ent.alias = alias;
	ent.is_playing = false;
	ent.point1 = point1;
	ent.point2 = point2;
	ent.fade_in = fade_in;
	ent.label = label;
	
	ent thread audx_play_line_emitter_internal();
	
	level waittill(label + "_line_emitter_stop");

	ent scalevolume(0, fade_out);
	wait(fade_out);
	ent stoploopsound();
	wait(0.05);
	ent delete();
}

/*
///ScriptDocBegin
"Name: aud_print_3d_on_ent(<msg> , <_size>, <_text_color> )"
"Summary: Create a print msg in 3d space that follows the entity this function is called on."
"Module: Audio"
"CallOn: The entity you wish to tag your print msg to."
"MandatoryArg: <msg> : Your print msg."
"SPMP: singleplayer"
///ScriptDocEnd
*/
aud_print_3d_on_ent(msg, _size, _text_color)
{
	if(IsDefined(self))
	{
		
		white = (1, 1, 1); //Default color if no arg is given.
		red = (1, 0, 0);
		green = (0, 1, 0);
		blue = (0, 1, 1);
	
		size = 5;
		text_color = white;
	
		if(IsDefined(_size))
		{
			size = _size;
		}
		
		if(IsDefined( _text_color))
		{
			text_color = _text_color;
					
			switch( text_color )
			{
				case "red":
				{
					text_color = red;
				}
				break;
				case "white":
				{
					text_color = white;	
				}
				break;
				case "blue":
				{
					text_color = blue;	
				}
				break;
				case "green":
				{
					text_color = green;	
				}
				break;
				
				default:
				{
					text_color = white;
				}
			}
		}
		
		self endon("death");
		
		while(IsDefined(self))
		{
			Print3d( self.origin, msg, text_color, 1, size, 1 );
			wait(0.05);
		}
	}
}



