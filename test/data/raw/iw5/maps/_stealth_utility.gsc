#include common_scripts\utility;
#include maps\_utility;
#include maps\_anim;


/*
=============
///ScriptDocBegin
"Name: stealth_default()"
"Summary: runs default stealth behavior on AI or the player"
"Module: Stealth"
"CallOn: An ai or the player"
"Example: level.price stealth_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_default()
{
	self stealth_plugin_basic();

	if ( isplayer( self ) )
		return;

	switch( self.team )
	{
		case "axis":
		case "team3":
			self stealth_plugin_threat();
			self stealth_enable_seek_player_on_spotted();
			self stealth_plugin_corpse();
			self stealth_plugin_event_all();
			break;

		case "allies":
			self stealth_plugin_aicolor();
			self stealth_plugin_accuracy();
			self stealth_plugin_smart_stance();
	}
}

/*
=============
///ScriptDocBegin
"Name: stealth_set_default_stealth_function( <key> , <func> )"
"Summary: sets the function in <func> to a key.  The KEY is referenced in radient with script_stealth_function. any spawner 
with that key will run the function referenced here.  This function should be similar in form to stealth_default "
"Module: Stealth"
"CallOn: "
"MandatoryArg: <key>: the reference which matches the script_stealth_function key set on a spawner in radient"
"MandatoryArg: <func>: the pointer to a function which will be called at spawn"
"Example: stealth_set_default_stealth_function( "top guys", ::stealth_cliffhanger );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_set_default_stealth_function( key, func )
{
	level.stealth_default_func[ key ] = func;
}

/*
=============
///ScriptDocBegin
"Name: stealth_plugin_basic()"
"Summary: runs BASIC stealth logic on AI. Handles proper animations, and setting the '_stealth_spotted' flag"
"Module: Stealth"
"CallOn: An ai"
"Example: level.price stealth_plugin_basic()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_plugin_basic( custom_state_funcs )
{
	assertex( isdefined( level._stealth.logic ), "call maps\_stealth::main()" );

	if ( isplayer( self ) )
	{
		self maps\_stealth_visibility_friendly::stealth_visibility_friendly_main();
		return;
	}

	if ( !isdefined( self._stealth ) || !isdefined( self._stealth.plugins.basic ) )
	{
		switch( self.team )
		{
			case "allies":
				self maps\_stealth_visibility_friendly::stealth_visibility_friendly_main();
				self maps\_stealth_behavior_friendly::stealth_behavior_friendly_main();
				break;
			case "axis":
			case "team3":
				self maps\_stealth_visibility_enemy::stealth_visibility_enemy_main();
				self maps\_stealth_behavior_enemy::stealth_behavior_enemy_main();
				break;
		}
	}
	if ( isdefined( custom_state_funcs ) )
		self stealth_basic_states_custom( custom_state_funcs );

	self._stealth.plugins.basic = true;
}

/*
=============
///ScriptDocBegin
"Name: stealth_basic_states_custom( <array> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_basic_states_custom( array )
{
	switch( self.team )
	{
		case "allies":
			self maps\_stealth_behavior_friendly::friendly_custom_state_behavior( array );
			break;
		case "axis":
		case "team3":
			self maps\_stealth_behavior_enemy::enemy_custom_state_behavior( array );
			break;
	}
}

/*
=============
///ScriptDocBegin
"Name: stealth_basic_states_default()"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_basic_states_default()
{
	switch( self.team )
	{
		case "allies":
			self maps\_stealth_behavior_friendly::friendly_default_state_behavior();
			break;
		case "axis":
		case "team3":
			self maps\_stealth_behavior_enemy::enemy_default_state_behavior();
			break;
	}
}

/*
=============
///ScriptDocBegin
"Name: stealth_pre_spotted_function_custom( <func> )"
"Summary: replaces the default function for what an AI will do between the period he's realized there is a threat, and sets the flag for _stealth_spotted. 
Good for writing custom AI behavior like running to an alarm before alerting his buddies of _stealth_spotted"
"Module: Stealth"
"CallOn: An AI"
"MandatoryArg: <func>: a function pointer to the custom function"
"Example: enemy stealth_pre_spotted_function_custom( ::run_to_alarm_func );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_pre_spotted_function_custom( func )
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );

	self maps\_stealth_visibility_enemy::enemy_alert_level_set_pre_spotted_func( func );
}

/*
=============
///ScriptDocBegin
"Name: stealth_pre_spotted_function_default()"
"Summary: sets the behavior for what to do between realizing a threat and setting the _stealth_spotted flag back to default. ( which is just waiting a couple seconds )"
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_pre_spotted_function_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_pre_spotted_function_default()
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );

	self maps\_stealth_visibility_enemy::enemy_alert_level_default_pre_spotted_func();
}

/*
=============
///ScriptDocBegin
"Name: stealth_plugin_threat( <custom_behavior_array> )"
"Summary: Runs threat behavior logic on an AI -> basically all the 'huh, what was that, who's there' behavior. 
stealth_plugin_basic() needs to be called on the AI before this"
"Module: Stealth"
"CallOn: An AI"
"OptionalArg: <custom_behavior_array>: array of functions that internally get's passed to 'stealth_threat_behavior_replace()'. please refer to stealth_threat_behavior_replace() for detailed help"
"Example: enemy stealth_plugin_threat();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_plugin_threat( custom_behavior_array )
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );
	assertex( self isBadGuy(), "stealth_plugin_accuracy is a plugin for enemies only" );

	//this way scripters can just call this function to change the behavior array instead of remembering two functions
	if ( !isdefined( self._stealth.plugins.threat ) )
		self maps\_stealth_threat_enemy::stealth_threat_enemy_main();

	if ( isdefined( custom_behavior_array ) )
		self stealth_threat_behavior_replace( custom_behavior_array );
}

/*
=============
///ScriptDocBegin
"Name: stealth_enable_seek_player_on_spotted()"
"Summary: Runs behavior logic on AI where AI will slowly close in the player's position once stealth is broken"
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_enable_seek_player_on_spotted();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_enable_seek_player_on_spotted()
{
	assertex( isdefined( self._stealth.plugins.threat ), "call maps\_stealth_utility::stealth_plugin_threat() on the AI first" );

	self.script_stealth_dontseek = false;
}

/*
=============
///ScriptDocBegin
"Name: stealth_disable_seek_player_on_spotted()"
"Summary: Stops ai from slowly closing in on the player's postion once stealth is broken"
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_disable_seek_player_on_spotted();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_disable_seek_player_on_spotted()
{
	assertex( isdefined( self._stealth.plugins.threat ), "call maps\_stealth_utility::stealth_plugin_threat() on the AI first" );

	self.script_stealth_dontseek = true;
}

/*
=============
///ScriptDocBegin
"Name: stealth_threat_behavior_custom( <threat_array>, <anim_array> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"OptionalArg: <threat_array>: an array of functions which dictate the behavior for the AI based on their current state (which corrispond to the key values in the array)\n
Valid key values are 'reset', 'normal' 'attack', 'warningX' where the X is a number between 1 and whatever.  You can have as many warning behaviors as you like or none at all, but if you do have warnings they must start with warning1 and follow in consecutive numbers.\n
You don't need to change all the behaviors, only the ones you want.  But if you dont have any 'warningX' keys in the array then there will be NO WARNING behavior. 
If you do not make 'reset', 'normal', or 'attack' entries in the array, the system will pick the default ones because those are mandatory behavior options.
\n reset is the function that occurs if an ai attacked you, and then lost you (right now defaults to going back to normal)
\n normal is the function that handles going back to original behavior from any of the other states
\n attack is the function that handles how the ai will attack once stealth is broken
\n warning1 through X decide how many times and what kinds of behavior the AI will do when sighting an enemy before they attack."
"OptionalArg: <anim_array>: an array of functions which dictate the animation reaction for the AI based on their current state (which corrispond to the key values in the array)\n
Valid key values are 'reset', 'normal' 'attack', 'warning'.  There is only one warning reaction anim for all the warning behaviors.\n
You don't need to change all the behaviors, only the ones you want.  The system fills in the default animation functions for ALL states, even warnings."
"Example: \n
custom_array = [];\n
custom_array[ "attack" ] = ::attack_func;\n
custom_array[ "warning1" ] = ::warning1_func;\n
custom_array[ "warning2" ] = ::warning2_func;\n
custom_array[ "warning3" ] = ::warning3_func;\n
custom_array[ "warning4" ] = ::warning4_func;\n
custom_array[ "warning5" ] = ::warning5_func;\n
enemy stealth_threat_behavior_custom( custom_array )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_threat_behavior_custom( threat_array, anim_array )
{
	assertex( isdefined( self._stealth.plugins.threat ), "call maps\_stealth_utility::stealth_plugin_threat() on the AI first" );

	if ( isdefined( threat_array ) )
		self maps\_stealth_threat_enemy::enemy_set_threat_behavior( threat_array );
	if ( isdefined( anim_array ) )
		self maps\_stealth_threat_enemy::enemy_set_threat_anim_behavior( anim_array );
}

/*
=============
///ScriptDocBegin
"Name: stealth_threat_behavior_replace( <threat_array>, <anim_array> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"OptionalArg: <threat_array>: an array of functions which dictate the behavior for the AI based on their current state (which corrispond to the key values in the array)\n
Valid key values are 'reset', 'normal' 'attack', 'warningX' where the X is a number between 1 and whatever.  You can have as many warning behaviors as you like or none at all, but if you do have warnings they must start with warning1 and follow in consecutive numbers.\n
You don't need to change all the behaviors, only the ones you want.  unlike stealth_threat_behavior_custom, stealth_threat_behavior_replace will fill in any warning functions the ai already has. 
If you do not make 'reset', 'normal', or 'attack' entries in the array, the system will pick the default ones because those are mandatory behavior options.
\n reset is the function that occurs if an ai attacked you, and then lost you (right now defaults to going back to normal)
\n normal is the function that handles going back to original behavior from any of the other states
\n attack is the function that handles how the ai will attack once stealth is broken
\n warning1 through X decide how many times and what kinds of behavior the AI will do when sighting an enemy before they attack."
"OptionalArg: <anim_array>: an array of functions which dictate the animation reaction for the AI based on their current state (which corrispond to the key values in the array)\n
Valid key values are 'reset', 'normal' 'attack', 'warning'.  There is only one warning reaction anim for all the warning behaviors.\n
You don't need to change all the behaviors, only the ones you want.  The system fills in the default animation functions for ALL states, even warnings."
"Example: \n
custom_array = [];\n
custom_array[ "attack" ] = ::attack_func;\n
custom_array[ "warning1" ] = ::warning1_func;\n
custom_array[ "warning2" ] = ::warning2_func;\n
custom_array[ "warning3" ] = ::warning3_func;\n
custom_array[ "warning4" ] = ::warning4_func;\n
custom_array[ "warning5" ] = ::warning5_func;\n
enemy stealth_threat_behavior_replace( custom_array )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_threat_behavior_replace( threat_array, anim_array )
{
	name = "threat";
	string = "warning";
	num = 1;
	key = string + num;

	if ( isdefined( threat_array ) )
	{
		while ( isdefined( self._stealth.behavior.ai_functions[ name ][ key ] ) )
		{
			if ( !isdefined( threat_array[ key ] ) )
				threat_array[ key ] = maps\_stealth_shared_utilities::ai_get_behavior_function( name, key );
			num++ ;
			key = string + num;
		}
	}

	self stealth_threat_behavior_custom( threat_array, anim_array );
}

/*
=============
///ScriptDocBegin
"Name: stealth_threat_behavior_default_no_warnings()"
"Summary: uses standard attack and reset behavior for threats, but there are no warning behaviors -> no 'huh, what was that, who's there' behavior."
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_threat_behavior_default_no_warnings();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_threat_behavior_default_no_warnings()
{
	array = [];
	self stealth_threat_behavior_custom( array );
}

/*
=============
///ScriptDocBegin
"Name: stealth_threat_behavior_default()"
"Summary: resets an AI back to standard behaviors for threat detection"
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_threat_behavior_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_threat_behavior_default()
{
	assertex( isdefined( self._stealth.plugins.threat ), "call maps\_stealth_utility::stealth_plugin_threat() on the AI first" );

	self maps\_stealth_threat_enemy::enemy_default_threat_behavior();
	self maps\_stealth_threat_enemy::enemy_default_threat_anim_behavior();
}


/*
=============
///ScriptDocBegin
"Name: stealth_alert_level_duration( <time> )"
"Summary: resets an AI back to standard behaviors for threat detection"
"Module: Stealth"
"CallOn: Level"
"MandatoryArg: <time>: time in seconds for each alert level"
"Example: stealth_alert_level_duration( 0.75 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_alert_level_duration( time )
{
	level._stealth.logic.min_alert_level_duration = time;
}


/*
=============
///ScriptDocBegin
"Name: stealth_plugin_corpse( <custom_corpse_array> )"
"Summary: Runs corpse behavior logic on an AI -> basically all the 'is that a body? hey guys i found a dead body!!' behavior. 
stealth_plugin_basic() needs to be called on the AI before this"
"Module: Stealth"
"CallOn: An AI"
"OptionalArg: <custom_corpse_array>: array of functions that internally get's passed to 'stealth_corpse_behavior_custom()'. please refer to stealth_corpse_behavior_custom() for detailed help"
"Example: enemy stealth_plugin_corpse();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_plugin_corpse( custom_corpse_array )
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );
	assertex( self isBadGuy(), "stealth_plugin_accuracy is a plugin for enemies only" );

	//this way scripters can just call this function to change the behavior array instead of remembering two functions
	if ( !isdefined( self._stealth.plugins.corpse ) )
		self maps\_stealth_corpse_enemy::stealth_corpse_enemy_main();

	if ( isdefined( custom_corpse_array ) )
		self stealth_corpse_behavior_custom( custom_corpse_array );
}

/*
=============
///ScriptDocBegin
"Name: stealth_corpse_behavior_custom( <corpse_functions> )"
"Summary: sets the corpse behavior functions for individual ai, basically what they will do when they think they see a corpse, and then when they find one"
"Module: Stealth"
"CallOn: AI"
"OptionalArg: <corpse_functions>: an array of 3 functions with keys 'saw', 'found', and 'reset' which are function pointers to overwrite default behavior for seeing and finding a corpse, and then going back to normal.If some keys do not exist - those functions will use the default behavior"
"Example: enemy stealth_corpse_behavior_custom( corpse_functions );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_corpse_behavior_custom( corpse_functions )
{
	assertex( isdefined( self._stealth.plugins.corpse ), "call maps\_stealth_utility::stealth_plugin_corpse() on the AI first" );

	self maps\_stealth_corpse_enemy::enemy_custom_corpse_behavior( corpse_functions );
}
/*
=============
///ScriptDocBegin
"Name: stealth_corpse_behavior_default()"
"Summary: sets the corpse behavior functions for individual ai back to default."
"Module: Stealth"
"CallOn: AI"
"Example: enemy stealth_corpse_behavior_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_corpse_behavior_default()
{
	assertex( isdefined( self._stealth.plugins.corpse ), "call maps\_stealth_utility::stealth_plugin_corpse() on the AI first" );

	self maps\_stealth_corpse_enemy::enemy_default_corpse_behavior();
}

/*
=============
///ScriptDocBegin
"Name: stealth_corpse_forget_time_default()"
"Summary: sets the amount of time that passes for a dead body to disappear back to default ( 60 seconds ) "
"Module: Stealth"
"CallOn: "
"Example: stealth_corpse_forget_time_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_corpse_forget_time_default()
{
	maps\_stealth_corpse_system::stealth_corpse_default_forget_time();
}

/*
=============
///ScriptDocBegin
"Name: stealth_corpse_forget_time_custom( <time> )"
"Summary: sets a custom amount of time in seconds that must pass for a dead body to disappear"
"Module: Stealth"
"CallOn: "
"MandatoryArg: <time>: time in seconds"
"Example: stealth_corpse_forget_time_custom( 20 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_corpse_forget_time_custom( time )
{
	maps\_stealth_corpse_system::stealth_corpse_set_forget_time( time );
}

/*
=============
///ScriptDocBegin
"Name: stealth_corpse_reset_time_default()"
"Summary: sets the amount of time that passes for to go back to normal after finding a dead body back to default ( 25 seconds ) "
"Module: Stealth"
"CallOn: "
"Example: stealth_corpse_reset_time_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_corpse_reset_time_default()
{
	maps\_stealth_corpse_system::stealth_corpse_default_reset_time();
}

/*
=============
///ScriptDocBegin
"Name: stealth_corpse_reset_time_custom( <time> )"
"Summary: sets a custom amount of time in seconds that must pass for ai to go back to normal after finding a dead body"
"Module: Stealth"
"CallOn: "
"MandatoryArg: <time>: time in seconds"
"Example: stealth_corpse_reset_time_custom( 50 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_corpse_reset_time_custom( time )
{
	maps\_stealth_corpse_system::stealth_corpse_set_reset_time( time );
}

/*
=============
///ScriptDocBegin
"Name: stealth_corpse_collect_func( <func> )"
"Summary: sets a custom function to be used for getting all existing corpses in a level."
"Module: Stealth"
"CallOn: "
"MandatoryArg: <func>: Script function that returns an array of corspes."
"Example: stealth_corpse_collect_func( ::get_corpse_array );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_corpse_collect_func( func )
{
	maps\_stealth_corpse_system::stealth_corpse_set_collect_func( func );
}

/*
=============
///ScriptDocBegin
"Name: stealth_corpse_collect_func_default()"
"Summary: Resets the stealth corpse collect function to the default."
"Module: Stealth"
"CallOn: "
"Example: stealth_corpse_collect_func_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_corpse_reset_collect_func()
{
	maps\_stealth_corpse_system::stealth_corpse_default_collect_func();
}

/*
=============
///ScriptDocBegin
"Name: stealth_plugin_event_all( <array> )"
"Summary: Runs all event behavior logic to various possible events that AI could react to in the game.
stealth_plugin_basic() needs to be called on the AI before this"
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_plugin_event_all();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_plugin_event_all( array )
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );

	self stealth_plugin_event_main();
	self maps\_stealth_event_enemy::stealth_event_mod_all();

	if ( isdefined( array ) )
	{
		foreach ( key, value in array )
			self maps\_stealth_event_enemy::stealth_event_mod( key, value );
	}
}

stealth_plugin_event_main()
{
	assertex( self isBadGuy(), "stealth_plugin_accuracy is a plugin for enemies only" );

	if ( !isdefined( self._stealth.plugins.event ) )
		self maps\_stealth_event_enemy::stealth_event_enemy_main();
}

/*
=============
///ScriptDocBegin
"Name: stealth_plugin_event_heard_scream( <behavior_function>, <animation_function> )"
"Summary: 
Runs the behavior for an AI in the event that his team mate yells out that he's found an enemy ( 'stealth_spotted' ).
You can optionally pass in your own custom behavior and animation functions for this event if you want.
Stealth_plugin_basic() needs to be called on the AI before this"
"Module: Stealth"
"CallOn: An AI"
"OptionalArg: <behavior_function>: the custom behavioral function to handle what the AI will do in this event"
"OptionalArg: <animation_function>: the custom animation function to handle what the AI will do in this event "
"Example: enemy stealth_plugin_event_heard_scream();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_plugin_event_heard_scream( behavior_function, animation_function )
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );

	self stealth_plugin_event_main();
	self maps\_stealth_event_enemy::stealth_event_mod( "heard_scream", behavior_function, animation_function );
}

/*
=============
///ScriptDocBegin
"Name: stealth_plugin_event_flashbang( <behavior_function>, <animation_function> )"
"Summary: 
Runs the behavior for an AI in the event that a flashbang goes off.
You can optionally pass in your own custom behavior and animation functions for this event if you want.
Stealth_plugin_basic() needs to be called on the AI before this"
"Module: Stealth"
"CallOn: An AI"
"OptionalArg: <behavior_function>: the custom behavioral function to handle what the AI will do in this event"
"OptionalArg: <animation_function>: the custom animation function to handle what the AI will do in this event "
"Example: enemy stealth_plugin_event_flashbang();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_plugin_event_flashbang( behavior_function, animation_function )
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );

	self stealth_plugin_event_main();
	self maps\_stealth_event_enemy::stealth_event_mod( "doFlashBanged", behavior_function, animation_function );
}

/*
=============
///ScriptDocBegin
"Name: stealth_plugin_event_explosion( <behavior_function>, <animation_function> )"
"Summary: 
Runs the behavior for an AI in the event that a distant explosion goes off.
You can optionally pass in your own custom behavior and animation functions for this event if you want.
Stealth_plugin_basic() needs to be called on the AI before this"
"Module: Stealth"
"CallOn: An AI"
"OptionalArg: <behavior_function>: the custom behavioral function to handle what the AI will do in this event"
"OptionalArg: <animation_function>: the custom animation function to handle what the AI will do in this event "
"Example: enemy stealth_plugin_event_explosion();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_plugin_event_explosion( behavior_function, animation_function )
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );

	self stealth_plugin_event_main();
	self maps\_stealth_event_enemy::stealth_event_mod( "explode", behavior_function, animation_function );
}

/*
=============
///ScriptDocBegin
"Name: stealth_plugin_event_custom( <type> , <behavior_function> , <animation_function> , <bad_event> , <event_listener> )"
"Summary: 
Runs behavior for an AI for a CUSTOM event type (one the scripter creates).
the <event_listener> arguement toggles whether this new event type is a code driven event with a notify that has to be listened for. 
If not then you NEED TO MAKE SURE the AI is notified of the <type> for him to exhibit the behavior during the custom event. -> DEFAULTS to FALSE
Stealth_plugin_basic() needs to be called on the AI before this."
"Module: Stealth"
"CallOn: An AI"
"MandatoryArg: <type>: the new type of event that the AI will be notified"
"MandatoryArg: <behavior_function>: the behavior the AI should run when the event happens"
"MandatoryArg: <animation_function>: the animation the AI should run when the event happens"
"OptionalArg: <event_listener>: bool that toggles whether this new event type is a code driven event with a notify that has to be listened for. 
If not then you NEED TO MAKE SURE the AI is notified of the <type> for him to exhibit the behavior during the custom event. -> DEFAULTS to FALSE"
"Example: enemy stealth_plugin_event_custom( "base_alarm", ::base_alarm_behavior, ::base_alarm_animation, true, false );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_plugin_event_custom( type, behavior_function, animation_function, event_listener )
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );

	self stealth_plugin_event_main();
	self maps\_stealth_event_enemy::stealth_event_mod( type, behavior_function, animation_function, event_listener );
}

/*
=============
///ScriptDocBegin
"Name: stealth_plugin_aicolor( <custom_color_array> )"
"Summary: Runs ai color state logic on an AI -> basically when stealth is hidden, ai color is off, when stealth is spotted ai color turns on. 
Good way to set up a paths with color triggers/nodes for when stealth is broken that is seperate from paths based on stealth hidden.
stealth_plugin_basic() needs to be called on the AI before this"
"Module: Stealth"
"CallOn: An AI"
"OptionalArg: <custom_color_array>: array of functions that internally get's passed to 'stealth_color_state_custom()'. please refer to stealth_color_state_custom() for detailed help"
"Example: enemy stealth_plugin_aicolor();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_plugin_aicolor( custom_color_array )
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );
	assertex( self.team == "allies", "stealth_plugin_accuracy is a plugin for friendlies only" );

	//this way scripters can just call this function to change the behavior array instead of remembering two functions
	if ( !isdefined( self._stealth.plugins.color_system ) )
		self maps\_stealth_color_friendly::stealth_color_friendly_main();

	if ( isdefined( custom_color_array ) )
		self stealth_color_state_custom( custom_color_array );
}

/*
=============
///ScriptDocBegin
"Name: stealth_color_state_custom( <array> )"
"Summary: sets the color state functions for individual ai, what you want to do with ai colors based on stealth hidden or spotted"
"Module: Stealth"
"CallOn: AI"
"OptionalArg: <array>: an array of 2 functions with keys 'hidden' and 'spotted' which are function pointers to overwrite default states for ai color. If a key is not in the array, that key will use default functions"
"Example: enemy stealth_color_state_custom( array );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_color_state_custom( array )
{
	assertex( isdefined( self._stealth.plugins.color_system ), "call maps\_stealth_utility::stealth_plugin_aicolor() on the AI first" );

	self maps\_stealth_color_friendly::friendly_custom_color_behavior( array );
}

/*
=============
///ScriptDocBegin
"Name: stealth_color_state_default()"
"Summary: sets the color state functions for individual ai back to default"
"Module: Stealth"
"CallOn: AI"
"Example: enemy stealth_color_state_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_color_state_default()
{
	assertex( isdefined( self._stealth.plugins.color_system ), "call maps\_stealth_utility::stealth_plugin_aicolor() on the AI first" );

	self maps\_stealth_color_friendly::friendly_default_color_behavior();
}

/*
=============
///ScriptDocBegin
"Name: stealth_plugin_accuracy( <custom_acc_array> )"
"Summary: Runs accuracy state logic on an AI -> basically when stealth is hidden, ai accuracy is really high, when stealth is spotted ai accuracy is low. 
stealth_plugin_basic() needs to be called on the AI before this"
"Module: Stealth"
"CallOn: An AI"
"OptionalArg: <custom_acc_array>: array of functions that internally get's passed to 'stealth_accuracy_state_custom()'. please refer to stealth_accuracy_state_custom() for detailed help"
"Example: enemy stealth_plugin_accuracy();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_plugin_accuracy( custom_acc_array )
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );
	assertex( self.team == "allies", "stealth_plugin_accuracy is a plugin for friendlies only" );

	//this way scripters can just call this function to change the behavior array instead of remembering two functions
	if ( !isdefined( self._stealth.plugins.accaracy_mod ) )
		self maps\_stealth_accuracy_friendly::stealth_accuracy_friendly_main();

	if ( isdefined( custom_acc_array ) )
		self stealth_accuracy_state_custom( custom_acc_array );
}

/*
=============
///ScriptDocBegin
"Name: stealth_accuracy_state_custom( <array> )"
"Summary: sets the accuracy state functions for individual ai, what you want to do with ai accuracy based on stealth hidden or spotted"
"Module: Stealth"
"CallOn: AI"
"OptionalArg: <array>: an array of 2 functions with keys 'hidden' and 'spotted' which are function pointers to overwrite default states for ai accuracy. If a key is not in the array, that key will use default functions"
"Example: enemy stealth_accuracy_state_custom( array );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_accuracy_state_custom( array )
{
	assertex( isdefined( self._stealth.plugins.accaracy_mod ), "call maps\_stealth_utility::stealth_plugin_accuracy() on the AI first" );

	self maps\_stealth_accuracy_friendly::friendly_custom_acc_behavior( array );
}

/*
=============
///ScriptDocBegin
"Name: stealth_accuracy_state_default()"
"Summary: sets the accuracy state functions for individual ai back to default"
"Module: Stealth"
"CallOn: AI"
"Example: enemy stealth_accuracy_state_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_accuracy_state_default()
{
	assertex( isdefined( self._stealth.plugins.accaracy_mod ), "call maps\_stealth_utility::stealth_plugin_accuracy() on the AI first" );

	self maps\_stealth_accuracy_friendly::friendly_default_acc_behavior();
}

/*
=============
///ScriptDocBegin
"Name: stealth_plugin_smart_stance()"
"Summary: Runs smart stance logic on a friendly, basically makes the AI look smart and change stances based on awareness of enemy positions. 
Use enable_stealth_smart_stance() and disable_stealth_smart_stance() to dynamically turn on and off ( defaults to off ).
stealth_plugin_basic() needs to be called on the AI before this"
"Module: Stealth"
"CallOn: An AI"
"Example: level.price stealth_plugin_smart_stance();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_plugin_smart_stance()
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );
	assertex( self.team == "allies", "stealth_plugin_accuracy is a plugin for friendlies only" );

	self maps\_stealth_smartstance_friendly::stealth_smartstance_friendly_main();
}

/*
=============
///ScriptDocBegin
"Name: enable_stealth_smart_stance()"
"Summary: turns on smart stance handling under the stealth system.
stealth_plugin_basic() and stealth_plugin_smart_stance() needs to be called on the AI before this"
"Module: Stealth"
"CallOn: An AI"
"Example: level.price enable_stealth_smart_stance();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_stealth_smart_stance()
{
	assertex( isdefined( self._stealth.plugins.smartstance ), "call maps\_stealth_utility::stealth_plugin_smart_stance() on the AI first" );

	self ent_flag_set( "_stealth_stance_handler" );
}

/*
=============
///ScriptDocBegin
"Name: disable_stealth_smart_stance()"
"Summary: turns off smart stance handling under the stealth system.
stealth_plugin_basic() and stealth_plugin_smart_stance() needs to be called on the AI before this"
"Module: Stealth"
"CallOn: An AI"
"Example: level.price disable_stealth_smart_stance();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_stealth_smart_stance()
{
	assertex( isdefined( self._stealth.plugins.smartstance ), "call maps\_stealth_utility::stealth_plugin_smart_stance() on the AI first" );

	self ent_flag_clear( "_stealth_stance_handler" );
}



/*
=============
///ScriptDocBegin
"Name: stealth_enemy_waittill_alert()"
"Summary: returns when the enemy ai has been alerted to something in stealth gameplay"
"Module: Stealth"
"CallOn: An ai"
"Example: enemy stealth_enemy_waittill_alert();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_enemy_waittill_alert()
{
	waittillframeend;// to ensure the ent flag below is init'ed

	self ent_flag_waitopen( "_stealth_normal" );
}

/*
=============
///ScriptDocBegin
"Name: stealth_is_everything_normal()"
"Summary: return true if everyone in the system is normal, otherwise returns false"
"Module: Stealth"
"CallOn: An entity"
"Example: if( stealth_is_everything_normal() )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_is_everything_normal()
{
	groups = level._stealth.group.groups;
		
	foreach ( key, value in groups )
	{
		ai = maps\_stealth_shared_utilities::group_get_ai_in_group( key );
		
		foreach( actor in ai )
		{
			if( !actor ent_flag( "_stealth_normal" ) )
				return false;
		}
	}
	
	return true;
}

/*
=============
///ScriptDocBegin
"Name: stealth_enemy_endon_alert()"
"Summary: notifies self of "stealth_enemy_endon_alert" when the ai has been alerted to something in stealth gameplay...a good function to thread off and catch the notify if we want to endon the notify"
"Module: Stealth"
"CallOn: An ai"
"Example: enemy thread stealth_enemy_endon_alert(); enemy endon( "stealth_enemy_endon_alert" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_enemy_endon_alert()
{
	stealth_enemy_waittill_alert();
	//just in case we're already spotted when this function get's called
	//we want to wait one frame to allow any lines with the endon to be passed
	//so that they don't miss the notify below
	waittillframeend;
	self notify( "stealth_enemy_endon_alert" );
}

/*
=============
///ScriptDocBegin
"Name: stealth_event_handler( <dialogue_array> , <ender_array> )"
"Summary: Run this function to handle events that aren't about being spotted, such as explosions and corpses being found.
When that happens the flag '_stealth_event' gets set, it gets cleared when all enemy ai go back to normal.  If passed a 
Dialogue array, then a random radio dialogue line will be played during such an event."
"Module: Stealth"
"CallOn:"
"OptionalArg: <dialogue_array>: an array of strings that are radio dialogue lines to explain the situation. 
Things like, 'don't do something stupid' or 'they're not onto us yet'."
"OptionalArg: <ender_array>: an array of strings that should kill this function on a level notify.  They can be flags"
"Example: stealth_event_handler();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_event_handler( dialogue_array, ender_array )
{
	thread maps\_stealth_shared_utilities::event_awareness_main( dialogue_array, ender_array );
}

/*
=============
///ScriptDocBegin
"Name: stealth_detect_ranges_set( <hidden>, <alert>, <spotted> )"
"Summary: tweaks with the default detection distances for stealth gameplay.  These are based on stance. PLEASE refer to the top of maps\_stealth_logic.gsc for an indepth explanation of the stealth system."
"Module: Stealth"
"CallOn: "
"OptionalArg: <hidden>: an array of 3 indices with keys 'stand', 'crouch', and 'prone' which reflect the detection distance for each of those stances in the hidden state."
"OptionalArg: <spotted>: an array of 3 indices with keys 'stand', 'crouch', and 'prone' which reflect the detection distance for each of those stances in the spotted state."
"Example: stealth_logic_system_detect_ranges_set( hidden_array );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_detect_ranges_set( hidden, spotted )
{
	maps\_stealth_visibility_system::system_set_detect_ranges( hidden, spotted );
}

/*
=============
///ScriptDocBegin
"Name: stealth_detect_ranges_default()"
"Summary: sets the detection distances for stealth gameplay back to default.  These are based on stance. PLEASE refer to the top of maps\_stealth_logic.gsc for an indepth explanation of the stealth system."
"Module: Stealth"
"CallOn: "
"Example: stealth_detect_ranges_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_detect_ranges_default()
{
	maps\_stealth_visibility_system::system_default_detect_ranges();
}

/*
=============
///ScriptDocBegin
"Name: stealth_corpse_ranges_custom( <distances> )"
"Summary: sets the various distances that ai see, find, and respond to a corpse"
"Module: Stealth"
"CallOn: "
"MandatoryArg: <distances>: an array of numbers that represents the distances, the keys are listed below, and you only need to fill in the ones you want to change:
\n sight_dist: this is the min distance to the corpse the ai have to be in order to possibly see it
\n detect_dist: this is the max distance from a corpse that the ai automatically detect a corpse ->regardless of whether they are looking at it or not ( this is a small number )
\n found_dist: this is the distance at which a stop running up to the corpse and start shouting out that they've found one
\n found_dog_dist: same as found distance but for dogs "
"Example: 
array = [];
array[ "sight_dist" ] = 512;
stealth_corpse_ranges_custom( array )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_corpse_ranges_custom( distances )
{
	maps\_stealth_corpse_system::stealth_corpse_set_distances( distances );
}

/*
=============
///ScriptDocBegin
"Name: stealth_corpse_ranges_default()"
"Summary: sets the various distances that ai see, find, and respond to a corpse back to default"
"Module: Stealth"
"CallOn: "
"Example: stealth_corpse_ranges_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_corpse_ranges_default()
{
	maps\_stealth_corpse_system::stealth_corpse_default_distances();
}

/*
=============
///ScriptDocBegin
"Name: stealth_ai_event_dist_custom( <array> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_ai_event_dist_custom( array )
{
	state = level._stealth.logic.detection_level;

	maps\_stealth_visibility_system::system_set_event_distances( array );
	maps\_stealth_visibility_system::system_event_change( state );
}

/*
=============
///ScriptDocBegin
"Name: stealth_ai_event_dist_default( <stealth_ai_event_dist_default> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_ai_event_dist_default()
{
	state = level._stealth.logic.detection_level;

	maps\_stealth_visibility_system::system_default_event_distances();
	maps\_stealth_visibility_system::system_event_change( state );
}

/*
=============
///ScriptDocBegin
"Name: stealth_friendly_movespeed_scale_set( <hidden>, <alert>, <spotted> )"
"Summary: sets the scalar for the movespeed score which is calculated into the huristic for stealth detection.  If the scalar is set to 0, then movement has no effect on detection.  These are based on stance and usually defualt to 2. PLEASE refer to the top of maps\_stealth_logic.gsc for an indepth explanation of the stealth system."
"Module: Stealth"
"CallOn: AI"
"OptionalArg: <hidden>: an array of 3 indices with keys 'stand', 'crouch', and 'prone' which reflect the scalar that movement speed should be multiplied by when being caclulated for the huristic of detection for each of those stances in the hidden state."
"OptionalArg: <spotted>: an array of 3 indices with keys 'stand', 'crouch', and 'prone' which reflect the scalar that movement speed should be multiplied by when being caclulated for the huristic of detection for each of those stances in the spotted state."
"Example: level.price stealth_friendly_movespeed_scale_set( hidden );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_friendly_movespeed_scale_set( hidden, spotted )
{
	self maps\_stealth_visibility_friendly::friendly_set_movespeed_scale( hidden, spotted );
}

/*
=============
///ScriptDocBegin
"Name: stealth_friendly_movespeed_scale_default()"
"Summary: sets the scalar for the movespeed score which is calculated into the huristic for stealth detection back to defaults.  If the scalar is set to 0, then movement has no effect on detection.  These are based on stance and usually defualt to 2. PLEASE refer to the top of maps\_stealth_logic.gsc for an indepth explanation of the stealth system."
"Module: Stealth"
"CallOn: AI"
"Example: level.price stealth_friendly_movespeed_scale_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_friendly_movespeed_scale_default()
{
	self maps\_stealth_visibility_friendly::friendly_default_movespeed_scale();
}

/*
=============
///ScriptDocBegin
"Name: stealth_friendly_stance_handler_distances_set( <hidden>, <alert> )"
"Summary: tweaks the distances for which the smart stance handler for friendlies decides which stance to be in. PLEASE refer to the top of maps\_stealth_behacior.gsc for an indepth explanation of the stealth system."
"Module: Stealth"
"CallOn: AI"
"OptionalArg: <hidden>: a 2D array of 3x3 indices. the first bracket element is an array of 3 with keys 'looking_away', 'neutral' and 'looking_towards' which corrispond to which way enemies are facing relative to the friendly. the 2nd bracket element is an array of 3 with keys 'stand', 'crouch' and 'prone' corrisponding to the distances the friendly should use for the smart stance check within the parameters of the first bracket element"
"Example: level.price stealth_friendly_stance_handler_distances_set( hidden );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_friendly_stance_handler_distances_set( looking_away, neutral, looking_towards )
{
	self maps\_stealth_smartstance_friendly::friendly_set_stance_handler_distances( looking_away, neutral, looking_towards );
}

/*
=============
///ScriptDocBegin
"Name: stealth_friendly_stance_handler_distances_default()"
"Summary: sets the distances for which the smart stance handler for friendlies decides which stance to be in to default. PLEASE refer to the top of maps\_stealth_behacior.gsc for an indepth explanation of the stealth system."
"Module: Stealth"
"CallOn: AI"
"Example: level.price stealth_friendly_stance_handler_distances_default();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_friendly_stance_handler_distances_default()
{
	self maps\_stealth_smartstance_friendly::friendly_default_stance_handler_distances();
}

/*
=============
///ScriptDocBegin
"Name: stealth_ai_clear_custom_idle_and_react( <wait_anim_end> )"
"Summary: stops and clears any custom reaction and idle animation for the ai. PLEASE refer to the top of maps\_stealth_behacior.gsc for an indepth explanation of the stealth system."
"Module: Stealth"
"CallOn: AI"
"OptionalArg: <wait_anim_end>: if set to true, the animation loop will finish it's last cycle instead of ending immediately"
"Example: enemy stealth_ai_clear_custom_react_and_idle();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_ai_clear_custom_idle_and_react( wait_anim_end )
{
	self maps\_stealth_shared_utilities::ai_clear_custom_animation_reaction_and_idle( wait_anim_end );
}

/*
=============
///ScriptDocBegin
"Name: stealth_ai_clear_custom_react()"
"Summary: clears any custom reaction animation for the ai. PLEASE refer to the top of maps\_stealth_behacior.gsc for an indepth explanation of the stealth system."
"Module: Stealth"
"CallOn: AI"
"Example: enemy stealth_ai_clear_custom_react();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_ai_clear_custom_react()
{
	self maps\_stealth_shared_utilities::ai_clear_custom_animation_reaction();
}

/*
=============
///ScriptDocBegin
"Name: stealth_ai_idle_and_react( <guy>, <idle_anim>, <reaction_anim>, <tag> )"
"Summary: this starts an AI in an idle animation defined by <idle_anim> and then plays the reaction animation defined by <reaction_anim> when appropriate."
"Module: Stealth"
"CallOn: reference node or ent"
"MandatoryArg: <self>: the node or reference entity or self to play the animation off of" 
"MandatoryArg: <guy> : the actor doing the animation"
"MandatoryArg: <idle_anim> : the idle animation to play (setup so anim_generic can use)"
"MandatoryArg: <reaction_anim> : the reaction animation to play (setup so anim_generic can use)"
"OptionalArg: <tag>: the tag to play off of the <reference_ent>"
"OptionalArg: <no_gravity>: set to true if you don't want to use the gravity animmode (like if you want the bounding box to clip some geo)"
"Example: node stealth_ai_idle_and_react( self, "smoke_idle", "smoke_react" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/	
stealth_ai_idle_and_react( guy, idle_anim, reaction_anim, tag, no_gravity )
{	
	if ( IsDefined( no_gravity ) )
		AssertEx( no_gravity, "no_gravity must be true or undefined" );
	
	guy stealth_insure_enabled();

	spotted_flag = guy maps\_stealth_shared_utilities::group_get_flagname( "_stealth_spotted" );

	if ( flag( spotted_flag ) )
		return;

	ender = "stop_loop";

	guy.allowdeath = true;
	
	if( !isdefined( no_gravity ) )
		self thread maps\_anim::anim_generic_custom_animmode_loop( guy, "gravity", idle_anim, tag );
	else
		self thread maps\_anim::anim_generic_loop( guy, idle_anim, tag );
		
	guy maps\_stealth_shared_utilities::ai_set_custom_animation_reaction( self, reaction_anim, tag, ender );

	self add_wait( ::waittill_msg, "stop_idle_proc" );
	self add_func( ::stealth_ai_clear_custom_idle_and_react );
	
	self thread do_wait_thread();
}

// do_wait should not be used on something that can become undefined.
do_wait_thread()
{
	self endon( "death" );
	self do_wait();
}

/*
=============
///ScriptDocBegin
"Name: stealth_ai_react( <guy>, <idle_anim>, <reaction_anim>, <tag> )"
"Summary: this plays the reaction animation defined by <reaction_anim> when appropriate."
"Module: Stealth"
"CallOn: reference node or ent"
"MandatoryArg: <self>: the node or reference entity or self to play the animation off of" 
"MandatoryArg: <guy> : the actor doing the animation"
"MandatoryArg: <reaction_anim> : the reaction animation to play (setup so anim_generic can use)"
"OptionalArg: <tag>: the tag to play off of the <reference_ent>"
"Example: bike stealth_ai_react( self, "bike_climb_off" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_ai_react( guy, reaction_anim, tag )
{
	guy stealth_insure_enabled();
	guy maps\_stealth_shared_utilities::ai_set_custom_animation_reaction( self, reaction_anim, tag, "stop_loop" );
}

/*
=============
///ScriptDocBegin
"Name: stealth_ai_reach_idle_and_react( <guy>, <reach_anim>, <idle_anim>, <reaction_anim>, <tag> )"
"Summary: this has the ai reach his position and then start in an idle animation defined by <idle_anim> and then plays the reaction animation defined by <reaction_anim> when appropriate."
"Module: Stealth"
"CallOn: reference node or ent"
"MandatoryArg: <self>: the node or reference entity or self to play the animation off of" 
"MandatoryArg: <guy> : the actor doing the animation"
"MandatoryArg: <reach_anim> : the reach animation to play..often times just a copy of the idle anim not setup in a 2d array (setup so anim_generic can use)"
"MandatoryArg: <idle_anim> : the idle animation to play (setup so anim_generic can use)"
"MandatoryArg: <reaction_anim> : the reaction animation to play (setup so anim_generic can use)"
"OptionalArg: <tag>: the tag to play off of the <reference_ent>"
"Example: node stealth_ai_reach_idle_and_react( self, "smoke_idle_reach", "smoke_idle", "smoke_react" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/	
stealth_ai_reach_idle_and_react( guy, reach_anim, idle_anim, reaction_anim, tag )
{
	guy stealth_insure_enabled();
	self thread stealth_ai_reach_idle_and_react_proc( guy, reach_anim, idle_anim, reaction_anim, tag );
}

stealth_ai_reach_idle_and_react_proc( guy, reach_anim, idle_anim, reaction_anim, tag )
{
	guy stealth_insure_enabled();

	guy thread stealth_enemy_endon_alert();
	guy endon( "stealth_enemy_endon_alert" );
	guy endon( "death" );

	self maps\_anim::anim_generic_reach( guy, reach_anim, tag );
	stealth_ai_idle_and_react( guy, idle_anim, reaction_anim, tag );
}

/*
=============
///ScriptDocBegin
"Name: stealth_ai_reach_and_arrive_idle_and_react( <guy>, <reach_anim>, <idle_anim>, <reaction_anim>, <tag> )"
"Summary: this has the ai reach his position with an arrival and then start in an idle animation defined by <idle_anim> and then plays the reaction animation defined by <reaction_anim> when appropriate."
"Module: Stealth"
"CallOn: reference node or ent"
"MandatoryArg: <self>: the node or reference entity or self to play the animation off of" 
"MandatoryArg: <guy> : the actor doing the animation"
"MandatoryArg: <idle_anim> : the reach animation to play..often times just a copy of the idle anim not setup in a 2d array (setup so anim_generic can use)"
"MandatoryArg: <idle_anim> : the idle animation to play (setup so anim_generic can use)"
"MandatoryArg: <reaction_anim> : the reaction animation to play (setup so anim_generic can use)"
"OptionalArg: <tag>: the tag to play off of the <reference_ent>"
"Example: node stealth_ai_reach_and_arrive_idle_and_react( self, "smoke_idle_reach", "smoke_idle", "smoke_react" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/	
stealth_ai_reach_and_arrive_idle_and_react( guy, reach_anim, idle_anim, reaction_anim, tag )
{
	guy stealth_insure_enabled();
	self thread stealth_ai_reach_and_arrive_idle_and_react_proc( guy, reach_anim, idle_anim, reaction_anim, tag );
}

stealth_ai_reach_and_arrive_idle_and_react_proc( guy, reach_anim, idle_anim, reaction_anim, tag )
{
	guy stealth_insure_enabled();

	guy thread stealth_enemy_endon_alert();
	guy endon( "stealth_enemy_endon_alert" );
	guy endon( "death" );

	self maps\_anim::anim_generic_reach_and_arrive( guy, reach_anim, tag );
	stealth_ai_idle_and_react( guy, idle_anim, reaction_anim, tag );
}


stealth_insure_enabled()
{
	assertex( isdefined( self._stealth.plugins.basic ), "call maps\_stealth_utility::stealth_plugin_basic() on the AI first" );
}

/*
=============
///ScriptDocBegin
"Name: stealth_group_return_groups_with_spotted_flag()"
"Summary: returns an array of the names of the groups with this flag set"
"Module: Stealth"
"CallOn: "
"Example: stealth_group_return_groups_with_spotted_flag()"
///ScriptDocEnd
=============
*/
stealth_group_return_groups_with_spotted_flag()
{
	return maps\_stealth_shared_utilities::group_return_groups_with_flag_set( "_stealth_spotted" );
}

/*
=============
///ScriptDocBegin
"Name: stealth_group_return_groups_with_event_flag()"
"Summary: returns an array of the names of the groups with this flag set"
"Module: Stealth"
"CallOn: "
"MandatoryArg: <_flag>: the flag you with to check for ( , "_stealth_event", "_stealth_found_corpse")"
"Example: stealth_group_return_groups_with_event_flag"
///ScriptDocEnd
=============
*/
stealth_group_return_groups_with_event_flag()
{
	return maps\_stealth_shared_utilities::group_return_groups_with_flag_set( "_stealth_event" );
}

/*
=============
///ScriptDocBegin
"Name: stealth_group_return_groups_with_corpse_flag()"
"Summary: returns an array of the names of the groups with this flag set"
"Module: Stealth"
"CallOn: "
"Example: stealth_group_return_groups_with_corpse_flag"
///ScriptDocEnd
=============
*/
stealth_group_return_groups_with_corpse_flag()
{
	return maps\_stealth_shared_utilities::group_return_groups_with_flag_set( "_stealth_found_corpse" );
}

/*
=============
///ScriptDocBegin
"Name: stealth_group_return_ai_with_spotted_flag()"
"Summary: returns an array of the ai in groups with this flag set"
"Module: Stealth"
"CallOn: "
"Example: stealth_group_return_ai_with_spotted_flag"
///ScriptDocEnd
=============
*/
stealth_group_return_ai_with_spotted_flag()
{
	return maps\_stealth_shared_utilities::group_return_ai_with_flag_set( "_stealth_spotted" );
}
/*
=============
///ScriptDocBegin
"Name: stealth_group_return_ai_with_event_flag()"
"Summary: returns an array of the ai in groups with this flag set"
"Module: Stealth"
"CallOn: "
"Example: stealth_group_return_ai_with_event_flag"
///ScriptDocEnd
=============
*/
stealth_group_return_ai_with_event_flag()
{
	return maps\_stealth_shared_utilities::group_return_ai_with_flag_set( "_stealth_event" );
}
/*
=============
///ScriptDocBegin
"Name: stealth_group_return_ai_with_corpse_flag()"
"Summary: returns an array of the ai in groups with this flag set"
"Module: Stealth"
"CallOn: "
"Example: stealth_group_return_ai_with_corpse_flag"
///ScriptDocEnd
=============
*/
stealth_group_return_ai_with_corpse_flag()
{
	return maps\_stealth_shared_utilities::group_return_ai_with_flag_set( "_stealth_found_corpse" );
}


/*
=============
///ScriptDocBegin
"Name: stealth_group_spotted_flag()"
"Summary: checks the 'stealth_spotted' flag for the stealth group of the AI that's calling the function."
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_group_spotted_flag();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_group_spotted_flag()
{
	name = self maps\_stealth_shared_utilities::group_get_flagname( "_stealth_spotted" );
	return flag( name );
}
/*
=============
///ScriptDocBegin
"Name: stealth_group_corpse_flag()"
"Summary: checks the '_stealth_found_corpse' flag for the stealth group of the AI that's calling the function."
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_group_corpse_flag();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_group_corpse_flag()
{
	name = self maps\_stealth_shared_utilities::group_get_flagname( "_stealth_found_corpse" );
	return flag( name );
}

/*
=============
///ScriptDocBegin
"Name: stealth_group_spotted_flag_wait()"
"Summary: waits for the 'stealth_spotted' flag to be set for the stealth group of the AI that's calling the function."
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_group_spotted_flag_wait();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_group_spotted_flag_wait()
{
	name = self maps\_stealth_shared_utilities::group_get_flagname( "_stealth_spotted" );
	flag_wait( name );
}
/*
=============
///ScriptDocBegin
"Name: stealth_group_corpse_flag_wait()"
"Summary: waits for the '_stealth_found_corpse' flag to be set for the stealth group of the AI that's calling the function."
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_group_corpse_flag_wait();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_group_corpse_flag_wait()
{
	name = self maps\_stealth_shared_utilities::group_get_flagname( "_stealth_found_corpse" );
	flag_wait( name );
}

/*
=============
///ScriptDocBegin
"Name: stealth_group_spotted_flag_waitopen()"
"Summary: waits for the 'stealth_spotted' flag to be cleared for the stealth group of the AI that's calling the function."
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_group_spotted_flag_waitopen();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_group_spotted_flag_waitopen()
{
	name = self maps\_stealth_shared_utilities::group_get_flagname( "_stealth_spotted" );
	return flag_waitopen( name );
}
/*
=============
///ScriptDocBegin
"Name: stealth_group_corpse_flag_waitopen()"
"Summary: waits for the '_stealth_found_corpse' flag to be cleared for the stealth group of the AI that's calling the function."
"Module: Stealth"
"CallOn: An AI"
"Example: enemy stealth_group_corpse_flag_waitopen();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_group_corpse_flag_waitopen()
{
	name = self maps\_stealth_shared_utilities::group_get_flagname( "_stealth_found_corpse" );
	return flag_waitopen( name );
}

/*
=============
///ScriptDocBegin
"Name: stealth_get_group_spotted_flag()"
"Summary: Returns the stealth flag for '_stealth_spotted' that's specific for this AI's group"
"Module: Stealth"
"CallOn: An AI"
"Example: flag = guy stealth_get_group_spotted_flag()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_get_group_spotted_flag()
{
	return self maps\_stealth_shared_utilities::group_get_flagname( "_stealth_spotted" );
}
/*
=============
///ScriptDocBegin
"Name: stealth_get_group_corpse_flag()"
"Summary: Returns the stealth flag for '_stealth_found_corpse' that's specific for this AI's group"
"Module: Stealth"
"CallOn: An AI"
"Example: flag = guy stealth_get_group_corpse_flag()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_get_group_corpse_flag()
{
	return self maps\_stealth_shared_utilities::group_get_flagname( "_stealth_found_corpse" );
}

/*
=============
///ScriptDocBegin
"Name: stealth_set_group( <var> )"
"Summary: sets the stealth group of the ai - stealth groups are used to section off groups of ai as far as their awareness and stealth detection goes"
"Module: Stealth"
"CallOn: An AI"
"MandatoryArg: <var>: the number or string to set the group to"
"Example: guy stealth_set_group( "base guys" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_set_group( var )
{
	self stealth_set_group_proc( var );
}

/*
=============
///ScriptDocBegin
"Name: stealth_set_group_default( <var> )"
"Summary: sets the stealth group of the ai back to the default group - stealth groups are used to section off groups of ai as far as their awareness and stealth detection goes"
"Module: Stealth"
"CallOn: An AI"
"Example: guy stealth_set_group_default()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_set_group_default()
{
	self stealth_set_group_proc( "default" );
}

stealth_set_group_proc( var )
{
	if ( isdefined( self.script_stealthgroup ) )
		level._stealth.group.groups[ self.script_stealthgroup ] = array_remove( level._stealth.group.groups[ self.script_stealthgroup ], self );

	self.script_stealthgroup = string( var );

	if ( isdefined( self._stealth.plugins.basic ) )
	{
		self maps\_stealth_shared_utilities::group_flag_init( "_stealth_spotted" );
		self maps\_stealth_shared_utilities::group_flag_init( "_stealth_event" );
		self maps\_stealth_shared_utilities::group_flag_init( "_stealth_found_corpse" );
		self maps\_stealth_shared_utilities::group_add_to_global_list();
	}
}

/*
=============
///ScriptDocBegin
"Name: stealth_get_group( <var> )"
"Summary: Returns the stealth group value of the ai - stealth groups are used to section off groups of ai as far as their awareness and stealth detection goes"
"Module: Stealth"
"CallOn: An AI"
"Example: group = guy stealth_get_group()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stealth_get_group()
{
	return self.script_stealthgroup;
}

/*
=============
///ScriptDocBegin
"Name: enable_stealth_system( <enable_stealth_system> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_stealth_system()
{
	flag_set( "_stealth_enabled" );
	ai = getaispeciesarray( "all", "all" );
	foreach ( key, value in ai )
		value enable_stealth_for_ai();
		
	foreach ( player in level.players )
		player maps\_stealth_visibility_friendly::friendly_visibility_logic();
		
	maps\_stealth_visibility_system::system_event_change( "hidden" );
}

/*
=============
///ScriptDocBegin
"Name: disable_stealth_system( <disable_stealth_system> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_stealth_system()
{
	flag_clear( "_stealth_enabled" );
	ai = getaispeciesarray( "all", "all" );
	foreach ( key, value in ai )
		value disable_stealth_for_ai();
		
	foreach ( player in level.players )
	{
		player.maxVisibleDist = 8192;	
		
		if ( player ent_flag_exist( "_stealth_enabled" ) )
			player ent_flag_clear( "_stealth_enabled" );
	}
		
	maps\_stealth_visibility_system::system_event_change( "spotted" );
}

/*
=============
///ScriptDocBegin
"Name: enable_stealth_for_ai( <enable_stealth_for_ai> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_stealth_for_ai()
{
	if ( self ent_flag_exist( "_stealth_enabled" ) )
		self ent_flag_set( "_stealth_enabled" );
		
	if ( self.team == "allies" )		
		self maps\_stealth_visibility_friendly::friendly_visibility_logic();
}

/*
=============
///ScriptDocBegin
"Name: disable_stealth_for_ai( <disable_stealth_for_ai> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_stealth_for_ai()
{
	if ( self ent_flag_exist( "_stealth_enabled" ) )
		self ent_flag_clear( "_stealth_enabled" );
		
	self.maxVisibleDist = 8192;
}
