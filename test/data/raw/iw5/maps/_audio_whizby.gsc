#include maps\_audio;

WHIZ_init()
{
	// for SHG, this is going to be turned on by default
	SetSavedDVar("snd_newWhizby", 1);
	// use the default preset for the initial whizby initialization
	level._audio.whiz = spawnstruct();
	level._audio.whiz.use_string_table_presets = false;
}


WHIZ_use_string_table()
{
	level._audio.whiz.use_string_table_presets = true;
}

WHIZ_set_preset(name)
{
	/#
	if (aud_check_fastfiles()) return;
	#/
	assert(IsDefined(name));
	
	preset = [];
	
	if (level._audio.whiz.use_string_table_presets)
	{
		preset = WHIZx_get_stringtable_preset(name);
	}
	else
	{
		preset = AUDIO_PRESETS_WHIZBY(name, preset);
	}
	
	preset["name"] = name;	
	/#
	WHIZx_validate_preset(preset, preset["name"]);
	#/
	
	prob = preset["probability"];
	spread = preset["spread"];
	rad = preset["radius"];
	offset = preset["offset"];
	
	level.player SetWhizbyProbabilities(prob[0], prob[1], prob[2]);
	level.player SetWhizbySpreads(spread[0], spread[1], spread[2]);
	level.player SetWhizbyRadii(rad[0], rad[1], rad[2]);
	level.player SetWhizbyOffset(offset);
}

// Helper functions to set particlar aspects of the whizby presets at runtime
WHIZ_set_probabilities(near, medium, far)
{
	assert(IsDefined(near));
	assert(IsDefined(medium));
	assert(IsDefined(far));
	
	level.player SetWhizbyProbabilities(near, medium, far);
}

WHIZ_set_spreads(near, medium, far)
{
	assert(IsDefined(near));
	assert(IsDefined(medium));
	assert(IsDefined(far));
	
	level.player SetWhizbySpreads(near, medium, far);
}

WHIZ_set_radii(near, medium, far)
{
	assert(IsDefined(near));
	assert(IsDefined(medium));
	assert(IsDefined(far));
	
	level.player SetWhizbyRadii(near, medium, far);
}

WHIZ_set_offset(offset)
{
	assert(IsDefined(offset));

	level.player SetWhizbyOffset(offset);
}

WHIZx_get_stringtable_preset(presetname)
{
	assert(IsString(presetname));
	
	common_stringtable = "soundtables/common_whizby.csv";
	// note: for now, no level version of whizby presets
	//level_stringtable = "soundtables/" + level.script + "_whizby.csv";
	
	preset = [];
	
/#
	if (aud_check_fastfiles()) return preset;
#/

	// first check level stringtable
//	preset = WHIZx_get_mix_preset_from_stringtable_internal(level_stringtable, presetname);
//	if (preset.size == 0)
	preset = WHIZx_get_mix_preset_from_stringtable_internal(common_stringtable, presetname);

	assertEx(preset.size != 0, "Failed to get whizby preset, \"" + presetname + "\" from either " +  common_stringtable + " stringtable.");

	return preset;
}

WHIZx_get_mix_preset_from_stringtable_internal(stringtable, presetname)
{
	assert(IsString(stringtable));
	assert(IsString(presetname));
	
	preset = [];
	paramname = "";
	value = "";
	numparams = 12;
	
	radius = [];
	spread = [];
	probability = [];
	offset = 0;
	numparamsfound = 0;
	for (i = 1; i < numparams; i++)
	{
		paramname = tablelookup(stringtable, 0, "whizby_preset", i);
		value = tablelookup(stringtable, 0, presetname, i);	
		
		if (!IsDefined(value))  // means file was not found, which is ok in this case
			break;
		
		if (value != "" && value != "comments")
		{
			numparamsfound++;
			switch(paramname)
			{
				case "radius_offset":
				offset = float(value);
				break;
				case "near_radius":
				radius[0] = float(value);
				break;
				case "medium_radius":
				radius[1] = float(value);
				break;
				case "far_radius":
				radius[2] = float(value);
				break;
				case "near_spread":
				spread[0] = float(value);
				break;
				case "medium_spread":
				spread[1] = float(value);
				break;
				case "far_spread":
				spread[2] = float(value);
				break;
				case "near_prob":
				probability[0] = float(value);
				break;
				case "medium_prob":
				probability[1] = float(value);
				break;
				case "far_prob":
				probability[2] = float(value);
				break;
			}
		}
	}

	if (numparamsfound > 0)
	{
		// validate the preset
		assertEx(IsDefined(radius[0]) && IsDefined(radius[1]) && IsDefined(radius[2]), "Audio whizby string table preset: you need to define near, medium, and far radii.");
		assertEx(IsDefined(spread[0]) && IsDefined(spread[1]) && IsDefined(spread[2]), "Audio whizby string table preset: you need to define near, medium, and far spread.");
		assertEx(IsDefined(probability[0]) && IsDefined(probability[1]) && IsDefined(probability[2]), "Audio whizby string table preset: you need to define near, medium, and far probability.");	

		preset["radius"] = radius;
		preset["spread"] = spread;
		preset["probability"] = probability;

		if (IsDefined(offset))
			preset["offset"] = offset;			
	}
	
	return preset;	
}


/#
WHIZx_validate_preset_type(preset, name, type)
{
	assertEx(preset[type].size == 3, "Whizby preset, " + name + ", requires 3 " + type + " numbers for near, medium, and far whizby \"" + type + "\".");
	for (i = 0; i < 3; i++)
	{
		assert(preset[type][i] >= 0.0, "Whizby preset, " + name + ", has a " + type + " number less than zero." );
	}
}
#/


/#
WHIZx_validate_preset(preset, name)
{
	assertEx(IsDefined(preset["radius"]), "Whizby preset, " + name + ", requires a radius definition.");
	assertEx(IsDefined(preset["spread"]), "Whizby preset, " + name + ", requires a spread definition.");
	assertEx(IsDefined(preset["probability"]), "Whizby preset, " + name + ", requires a probability definition.");
	assertEx(IsDefined(preset["offset"]), "Whizby preset, " + name + ", requires an offset definition.");
	
	WHIZx_validate_preset_type(preset, name, "radius");
	WHIZx_validate_preset_type(preset, name, "spread");
	WHIZx_validate_preset_type(preset, name, "probability");
	
	assertEx(preset["offset"] >= 0, "Whizby preset, " + name + ", has an offset number less than zero." );
}
#/



