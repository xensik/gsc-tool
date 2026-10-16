/* 
	AUDIO MUSIC PRESETS
	
	Music moods are called using:
		
		 AMS_play("action");
	
	"action" in this case is a music mood defined in the tables below. Calling AMS_play will transition from the 
	currently playing mood, and transition to the specified mood.
	
		Moods consist of groups of cues which are mapped to various control ranges. A "control" value is a generic term which
	refers to any value fed into the mood used to differentiate between different cue groups. A "control" value might, for example
	be derived from adding up numbers of enemies weighted by their distance, and thus, calculuate an aggregate "threat" value. The 
	higher the "threat", the more intense the action music.
	
	Defining a cue groups of a mood are as follows:
	
	p["cue_groups"] = [
											["group_name_1", 0.8, 1.0],
											["group_name_2", 0.5, 0.8],
											["group_name_3", 0.0, 0.5]
										];
										
		The array of cue groups refers to an array of group-name, control-range pairs. The group name refers to another preset defined in the second
	preset function in this file, "AUDIO_PRESETS_MUSIC_CUE_GROUPS". It is essentially a group of aliases and associated random weights.  The second
	number pair refers to a control range. If the control value is 0.9, then "group_name_1" will be the cue group from which to play.
	
		Optionally, on a cue group definition, you can specify what mood to play if the control value has been on a particular cue group for a given 
	amount of time:
	
	p["cue_groups"] = [
											["action_0", 0.8, 1.0],
											["action_1", 0.5, 0.8],
											["action_2", 0.0, 0.5, "ambient", 30.0 ]
										];
	
		In this case, we are saying that if the control value has been inbetween 0.0 and 0.5 for 30 seconds, then play the "ambient" mood. This is a 
	generic mechanism which can be used to transition moods if control ranges are in one range for any period of time. For example, it might
	be used to transition to a different high intensity action music if we have been in super intense action for a very long time. In this case,
	it's used to transition to a more ambient mood the control (here, action) has been low for 30 seconds.
	
		The next require argument is a pointer to a behavior function which calculates some number derived from the game state. This function can
	do whatever it wants to return a single control number. This control number then is used to figure out which cue group to play. Coupled with
	the behavior function is it's associated callback rate. Finally, each mood can optionally specify how "smooth" the control values will be. A 
	lower smooth number will result in a smoother, slower-reacting mood. The closer to 1.0 the smooth value is, the more jittery the control value
	will be.
	
*/
#include maps\_audio;
#include maps\_audio_music;
// THIS IS DEPRECATED - FUNCTIONS ARE NOW STUBS
AUDIO_PRESETS_MUSIC_MOODS(name, p)
{	
	breakpoint;
	aud_print_warning("CALLING MUSIC_MOODS PRESET USING OLD METHOD!");
}

AUDIO_PRESETS_MUSIC_CUE_GROUPS(name, p)
{
	breakpoint;
	aud_print_warning("CALLING MUSIC_CUE_GROUPS PRESET USING OLD METHOD!");
}


//------------------------------ MUSIC CUES ------------------------------//

AUDIO_PRESETS_MUSIC_CUES(name, p)
{	
	breakpoint;
	aud_print_warning("CALLING MUSIC_CUES PRESET USING OLD METHOD!");
}
