#include maps\_audio;
#include maps\_audio_reverb;


setup_new_eq_settings( track, eqIndex )
{	
	if ( !isdefined( track ) || !isdefined( level.ambient_eq[ track ] ) )
	{
		deactivate_index( eqIndex );
		return false;
	}

	if ( level.eq_track[ eqIndex ] == track )
	{
		// already doing this one
		return false;
	}
	
	level.eq_track[ eqIndex ] = track;

	use_eq_settings( track, eqIndex );
	return true;
}

/*
=============
///ScriptDocBegin
"Name: use_eq_settings( <presetname> , <eqIndex> )"
"Summary: Enable EQ track settings on one of the two EQ indices."
"Module: Ambience"
"MandatoryArg: <presetname>: The EQ preset from either soundtables/common_filter.csv or soundtables/LEVELNAME_filter.csv"
"MandatoryArg: <eqIndex>: You must select either the main track or the mix track, preferably using level.eq_main_track or level.eq_mix_track. See ::blend_to_eq_track."
"Example: thread maps\_ambient::use_eq_settings( "gulag_cavein", level.eq_mix_track );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
use_eq_settings( presetname, eqIndex )
{
	assertEx(IsString(presetname), "use_eq_settings: requires a presetname.");
	assertEx(IsDefined(eqIndex), "use_eq_settings: requires an eqIndex parameter.");
	
	// red flashing overwrites eq
	if ( level.player maps\_utility::ent_flag( "player_has_red_flashing_overlay" ) )
		return;	
	
	aud_set_filter(presetname, eqIndex);
		
}

deactivate_index( eqIndex )
{
	assert(IsDefined(eqIndex));
	
	level.eq_track[ eqIndex ] = "";
	level.player deactivateeq( eqIndex );
}

/*
=============
///ScriptDocBegin
"Name: blend_to_eq_track( <eqIndex> , <time> )"
"Summary: Blends from one EQ track to another. NOTE that when you play this command, it will blend from zero to 100% on the track you select. If you were already on this track, this may sound weird."
"Module: Ambience"
"MandatoryArg: <eqIndex>: Which of the two EQ tracks to blend to, main or mix (level.eq_main_track, level.eq_mix_track)"
"OptionalArg: <time>: How much time to blend over. (defaults: 1.0 sec)"
"Example: thread maps\_ambient::blend_to_eq_track( level.eq_mix_track, 2 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blend_to_eq_track( eqIndex, time_ )
{
	assertEx(IsDefined(eqIndex), "blend_to_eq_track requires an eqIndex.");
	
	time = 1.0;
	if (IsDefined(time_))
		time = time_;

	interval = .05;
	count = time / interval;
	fraction = 1 / count;
	
	for ( i = 0; i <= 1; i += fraction )
	{
		level.player SetEqLerp( i, eqIndex );
		wait( interval );
	}
	
	level.player SetEqLerp( 1, eqIndex );
}


use_reverb_settings( reverb_preset )
{
	assert(IsString(reverb_preset));
	
	// red flashing overwrites reverb
	if ( level.player maps\_utility::ent_flag( "player_has_red_flashing_overlay" ) )
		return;

	RVB_start_preset( reverb_preset );
}

deactivate_reverb()
{
	RVB_deactive_reverb();
}

ambientDelay( foo, bar, baz)
{
	aud_print_warning("ambientDelay called, this is deprecated! Use new preset string tables.");
}

ambientEvent( track, name, weight, min_dist, max_dist, start_angle, end_angle )
{
	aud_print_warning("ambientEvent called, this is deprecated! Use new preset string tables.");
}

ambientEventStart( track )
{
	aud_print_warning("ambientEventStart called, this is deprecated! Use maps\_utility::set_ambient( track, fade_ ).");
	maps\_utility::set_ambient(track);
}

start_ambient_event( track )
{
	aud_print_warning("start_ambient_event called, this is deprecated! Use maps\_utility::set_ambient( track, fade_ ).");
	maps\_utility::set_ambient(track);
}

// NOTE: this was put _utility.gsc, don't call it from here
get_progess(start, end, dist, org)
{
	maps\_utility::get_progress( start, end, org, dist );
}