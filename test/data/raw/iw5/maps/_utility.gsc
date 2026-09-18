#include common_scripts\utility;
#include animscripts\utility;
#include maps\_utility_code;

/*
=============
///ScriptDocBegin
"Name: is_coop()"
"Summary: returns true if co-op is in use"
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_coop()
{
	if ( IsSplitScreen() || ( GetDvar( "coop" ) == "1" ) )
	{
		AssertEx( IsDefined( level.player2 ), "In co-op mode but level.player2 is undefined. IsSplitScreen=" + IsSplitScreen() + " coop dvar=" + GetDvar( "coop" ) );
		return true;
	}

	return false;
}

/*
=============
///ScriptDocBegin
"Name: is_coop_online()"
"Summary: Returns true if co-op is in use and the game is online."
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_coop_online()
{
	if ( issplitscreen() )
		return false;

	if ( !is_coop() )
		return false;

	return true;
}

/*
=============
///ScriptDocBegin
"Name: is_player_down( <player> )"
"Summary: Returns true if a player is in last stand mode or dead."
"Module: Entity"
"CallOn: A player"
"MandatoryArg: <player>: The player you want to check."
"Example: return is_player_down( level.player );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_player_down( player )
{
	AssertEx( IsDefined( player ) && IsPlayer( player ), "is_player_down() requires a valid player to test." );
	
	if ( player ent_flag_exist( "laststand_downed" ) )
		return player ent_flag( "laststand_downed" );
	
	if ( IsDefined( player.laststand ) )
		return player.laststand;

	return !IsAlive( player );
}

/*
=============
///ScriptDocBegin
"Name: is_player_down_and_out( <player> )"
"Summary: Returns true if a player is in last stand mode AND been knocked into "out" mode... where they have no weapon."
"Module: Entity"
"CallOn: A player"
"MandatoryArg: <player>: "
"Example: bool = is_player_down_and_out( leve.player );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_player_down_and_out( player )
{
	assertex( isdefined( player ) && isplayer( player ), "is_player_down_and_out() requires a valid player to test." );
	
	if ( !isdefined( player.down_part2_proc_ran ) )
		return false;

	return player.down_part2_proc_ran;
}

/*
=============
///ScriptDocBegin
"Name: killing_will_down()"
"Summary: Returns true if damaging the player to death will put them in laststand. Doesn't account for armor."
"Module: Entity"
"CallOn: A player"
"MandatoryArg: <player>: "
"Example: bool = killing_will_down( level.player )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
killing_will_down( player )
{
	AssertEx( IsDefined( player ) && IsPlayer( player ), "Invalid player." );
	
	if ( laststand_enabled() )
	{
		assertex( isdefined( level.laststand_initialized ), "Laststand not initialized yet." );
		
		return player maps\_laststand::laststand_downing_will_fail() == false;
	}
	
	return false;
}

/*
=============
///ScriptDocBegin
"Name: clear_custom_eog_summary()"
"Summary: Clears all dvars for custom end-of-game summary for special ops"
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
clear_custom_eog_summary()
{
	// player 1 to 2
	for( p = 1; p <= 2; p++ )
	{
		// column 1 to 4
		for ( j = 1; j <= 4; j++ )
		{
			// row 1 to 9
			for ( i = 1; i <= 9; i++ )
			{
				SetDvar( "ui_eog_r" + i + "c"+ j + "_player" + p, "" );
				SetDvar( "ui_eog_r" + i + "c"+ j + "_player" + p, "" );
			}
		}
		SetDvar( "ui_eog_success_heading_player" + p, "" );
	}
}

/*
=============
///ScriptDocBegin
"Name: set_custom_eog_summary( <int row>, <int col >, <string data> )"
"Summary: Called on player to set custom end-of-game summary for special ops"
"Module: Utility"
"MandatoryArg: <int row>: Row number to set the data in. Currently row is between 1 to 6."
"MandatoryArg: <int col>: Column number to set the data in. Currently column is between 1 to 2."
"MandatoryArg: <string data>: Data to be set in string."
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_custom_eog_summary( row, col, data )
{
	AssertEx( IsDefined( self ) && IsPlayer( self ), "set_custom_eog_summary() Must be called on a Player entity!" );
	//AssertEx( IsDefined( level.eog_summary_callback ), "Setting custom eog display data when callback function is not set. level.ego_summary_callback function pointer is undefined." );

	r = Int( row );
	c = Int( col );

	AssertEx( r >= 1 && r <= 9, "Row: " + r + " is out of bound, row = 1->9." );
	AssertEx( c >= 1 && c <= 4, "Column: " + c + " is out of bound, column = 1->4." );

	eog_dvar = "";
	if ( level.players.size > 1 )
	{
		if ( self == level.player )
			eog_dvar = "ui_eog_r" + r + "c" + c + "_player1";
		else if ( self == level.player2 )
			eog_dvar = "ui_eog_r" + r + "c" + c + "_player2";
		else
			AssertEx( true, "set_custom_eog_summary() Must be called on a Player entity!" );
	}
	else
	{
		eog_dvar = "ui_eog_r" + r + "c" + c + "_player1";
	}

	SetDvar( eog_dvar, data );
}

/*
=============
///ScriptDocBegin
"Name: add_custom_eog_summary_line( <eog_title> , <eog_value1> , <eog_value2> , <eog_value3>, <eog_line_override> )"
"Summary: Compressed way to add a line to the eog summary. By default will add itself in the order it was added."
"Module: Utility"
"CallOn: A player"
"MandatoryArg: <eog_title>: The title message to display in the left column."
"MandatoryArg: <eog_value1>: The value to display in the left data column."
"OptionalArg: <eog_value2>: The value to display in the middle data column."
"OptionalArg: <eog_value3>: The value to display in the right data column."
"OptionalArg: <eog_line_override>: Optional value to override the line the summary is going to display on."
"Example: add_custom_eog_summary_line( "@SPECIAL_OP_KILLS", player1.kill_count, player2.kill_count, death_count, 1 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_custom_eog_summary_line( eog_title, eog_value1, eog_value2, eog_value3, eog_line_override )
{
	assertex( isdefined( eog_title ), "so_add_eog_summary_line() requires a valid eog_title." );
	assertex( isdefined( self ) && isplayer( self ), "so_add_eog_summary_line() must be called on a player." );

	if ( !isdefined( self.eog_line ) )
		self.eog_line = 0;

	eog_line = undefined;
	if ( isdefined( eog_line_override ) )
	{
		eog_line = eog_line_override;
		
		if ( eog_line_override > self.eog_line )
			self.eog_line = eog_line_override;
	}
	else
	{
		self.eog_line++;
		eog_line = self.eog_line;
	}
	
	self set_custom_eog_summary( eog_line, 1, eog_title );
	
	// The values passed can be in configuration and still be right justified
	value_array = [];
	
	if ( isdefined( eog_value3 ) )
		value_array[ value_array.size ] = eog_value3;
		
	if ( isdefined( eog_value2 ) )
		value_array[ value_array.size ] = eog_value2;
		
	if ( isdefined( eog_value1 ) )
		value_array[ value_array.size ] = eog_value1;
	
	for ( i = 0; i < value_array.size; i ++ )
		self set_custom_eog_summary( eog_line, 4 - i, value_array[ i ] );
}

/*
=============
///ScriptDocBegin
"Name: add_custom_eog_summary_line_blank( <add_custom_eog_summary_line_blank> )"
"Summary: Simple function that auto-advances the line that the EOG summary is drawing on. Useful to clearly show what the EOG summary is doing."
"Module: Utility"
"Example: add_custom_eog_summary_line_blank();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_custom_eog_summary_line_blank()
{
	if ( !isdefined( self.eog_line ) )
		self.eog_line = 0;

	self.eog_line++;
}

/*
=============
///ScriptDocBegin
"Name: set_eog_success_heading( <string data> )"
"Summary: Sets mission sucess custom heading end-of-game summary for special ops"
"Module: Utility"
"MandatoryArg: <string data>: Title to be set in string."
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_eog_success_heading( title )
{
	AssertEx( IsDefined( self ) && IsPlayer( self ), "set_custom_eog_summary() Must be called on a Player entity!" );
	//AssertEx( IsDefined( level.eog_summary_callback ), "Setting custom eog display data when callback function is not set. level.ego_summary_callback function pointer is undefined." );

	eog_dvar = "";
	if ( level.players.size > 1 )
	{
		if ( self == level.player )
			eog_dvar = "ui_eog_success_heading_player1";
		else if ( self == level.player2 )
			eog_dvar = "ui_eog_success_heading_player2";
		else
			AssertEx( true, "set_eog_success_heading() Must be called on a Player entity!" );
	}
	else
	{
		eog_dvar = "ui_eog_success_heading_player1";
	}

	SetDvar( eog_dvar, title );
}

/*
=============
///ScriptDocBegin
"Name: is_survival()"
"Summary: returns true if map is in Special Op Survival mode."
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_survival()
{
	return ( is_specialop() && ( GetDvarInt( "so_survival" ) > 0 ) );
}

/*
=============
///ScriptDocBegin
"Name: laststand_enabled()"
"Summary: returns true if the player will enter last stand on death."
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
laststand_enabled()
{
	return IsDefined( level.laststand_type ) && level.laststand_type > 0;
}

/*
=============
///ScriptDocBegin
"Name: is_specialop()"
"Summary: returns true if map is in Special Op mode."
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_specialop()
{
	return GetDvarInt( "specialops" ) >= 1;
}

/*
=============
///ScriptDocBegin
"Name: convert_to_time_string( <timer>, <show_tenths> )"
"Summary: Takes a number and returns a string in Minutes:Seconds format."
"Module: Utility"
"MandatoryArg: <timer>: The number in seconds you want to convert."
"MandatoryArg: <show_tenths>: Option to display up to the tenths place for the seconds portion."
"Example: time_string = convert_to_time_string( time_seconds );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
convert_to_time_string( timer, show_tenths )
{
	string = "";
	if ( timer < 0 )
		string += "-";

	// Before computing the time string round
	// up the tenths place.
	timer = round_float( timer, 1, false );

	timer_clipped = timer * 100;
	timer_clipped = int( timer_clipped );
	timer_clipped = abs( timer_clipped );

	minutes = timer_clipped / 6000;
	minutes = int( minutes );
	string += minutes;

	seconds = timer_clipped / 100;
	seconds = int( seconds );
	seconds -= minutes * 60;
	if ( seconds < 10 )
		string += ":0" + seconds;
	else
		string += ":" + seconds;

	if ( IsDefined( show_tenths ) && show_tenths )
	{
		tenths = timer_clipped;
		tenths -= minutes * 6000;
		tenths -= seconds * 100;
		tenths = int( tenths/10 );
		string += "." + tenths;
	}

	return string;
}


/*
=============
///ScriptDocBegin
"Name: round_float( <value> , <place> , <up> )"
"Summary: Takes a float value and rounds that value according to the specificed place and whether or not up or down is specified."
"Module: Utility"
"MandatoryArg: <value>: The float value to round"
"MandatoryArg: <precision>: The place to round to. Valid params are: 0 for "integer", 1 for "tenths", 2 for "hundredths", 3 for "thousandths" and 4 for "ten_thousandths"."
"OptionalArg: <down>: Boolean value representing whether to round down or up. Defaults to down when undefined."
"Example: float_rounded = round_float( 2.339, 2, false )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

round_float( value, precision, down )
{
	AssertEx( IsDefined( value ), "value must be defined." );
	AssertEx( IsDefined( precision ), "precision must be defined." );
	AssertEx( precision == int( precision ), "precision must be an integer." );
	
	precision = int( precision );
	
	if ( precision < 0 || precision > 4 )
	{
		AssertMsg( "Precision value must be an integer that is >= 0 and <= 4. This was passed in: " + precision );
		return value;
	}
	
	// Start at no decimal offset
	decimal_offset = 1;
	for ( i = 1; i <= precision; i++ )
	{
		decimal_offset *= 10;
	}
	
	value_clipped = value * decimal_offset;
	
	if ( !IsDefined( down ) || down )
	{
		value_clipped = floor( value_clipped );
	}
	else
	{
		value_clipped = ceil( value_clipped );	
	}
	
	value = value_clipped / decimal_offset;
	
	return value;
}

/*
=============
///ScriptDocBegin
"Name: round_millisec_on_sec( <value> , <precision> , <down> )"
"Summary: Takes milliseconds, converts to seconds, rounds to the desired precision and then converts back to milliseconds."
"Module: Utility"
"MandatoryArg: <value>: The time in milliseconds to be rounded."
"MandatoryArg: <precision>: The placeround the value according to seconds. Valid params are: 0 for "integer", 1 for "tenths", 2 for "hundredths", 3 for "thousandths" and 4 for "ten_thousandths"."
"OptionalArg: <down>: Boolean value representing whether to round down or up. Defaults to down when undefined."
"Example: time_mill_rounded = round_millisec_on_sec( time_mil )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

round_millisec_on_sec( value, precision, down )
{
	// Divide by 1000 instead of multiplying by
	// 0.001 because the latter causes excess
	// decimal places due to floating point error - JC
	value_seconds = value / 1000;
	
	value_seconds = round_float( value_seconds, precision, down );
	
	value = value_seconds * 1000;
	
	return int( value );
}

/*
=============
///ScriptDocBegin
"Name: isdefined_test( <value> , <test_value> , <test_style> )"
"Summary: Tests whether a value is defined and meets the test requirements. If no test_value specified, just tests ifdefined(). If no test_style is specified assumes ==."
"Module: Utility"
"MandatoryArg: <value>: Variable to test if it is defined and if it meets the test requirements."
"OptionalArg: <test_value>: Value to compare against."
"OptionalArg: <test_style>: Style of comparison to make. "==", "<", ">", "<=", ">=" are allowed."
"Example: if ( isdefined_test( my_variable, current_value, "<=" ) ) return true"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
isdefined_test( value, test_value, test_style )
{
	if ( !isdefined( value ) )
		return false;
	if ( !isdefined( test_value ) )
		return true;

	if ( !isdefined( test_style ) )
		test_style = "==";

	switch ( test_style )
	{
		case "==":	return ( value == test_value );
		case "<":	return ( value < test_value );
		case ">":	return ( value > test_value );
		case "<=":	return ( value <= test_value );
		case ">=":	return ( value >= test_value );
	}
	return true;
}

/*
=============
///ScriptDocBegin
"Name: set_vision_set( <visionset> , <transition_time> )"
"Summary: Sets the vision set over time"
"Module: Utility"
"MandatoryArg: <visionset>: Visionset file to use"
"OptionalArg: <transition_time>: Time to transition to the new vision set. Defaults to 1 second."
"Example: set_vision_set( "blackout_darkness", 0.5 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_vision_set( visionset, transition_time )
{
	if ( init_vision_set( visionset ) )
		return;

	if ( !isdefined( transition_time ) )
		transition_time = 1;
	//iprintlnbold( visionset );
	VisionSetNaked( visionset, transition_time );
	SetDvar( "vision_set_current", visionset );
}

/*
=============
///ScriptDocBegin
"Name: set_vision_set_player( <visionset> , <transition_time> )"
"Summary: Sets the vision set over time for a specific player in coop"
"Module: Utility"
"MandatoryArg: <visionset>: Visionset file to use"
"OptionalArg: <transition_time>: Time to transition to the new vision set. Defaults to 1 second."
"Example: level.player2 set_vision_set_player( "blackout_darkness", 0.5 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_vision_set_player( visionset, transition_time )
{
	if ( init_vision_set( visionset ) )
		return;

	Assert( IsDefined( self ) );
	Assert( level != self );

	if ( !isdefined( transition_time ) )
		transition_time = 1;
	self VisionSetNakedForPlayer( visionset, transition_time );
}

/*
=============
///ScriptDocBegin
"Name: set_nvg_vision( <visionset> , <transition_time> )"
"Summary: Sets the night vision set over time"
"Module: Utility"
"MandatoryArg: <visionset>: Visionset file to use"
"OptionalArg: <transition_time>: Time to transition to the new vision set. Defaults to 1 second."
"Example: set_nvg_vision( "blackout_darkness", 0.5 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_nvg_vision( visionset, transition_time )
{
//	init_vision_set( visionset );

	if ( !isdefined( transition_time ) )
		transition_time = 1;
	VisionSetNight( visionset, transition_time );
}

/*
 =============
///ScriptDocBegin
"Name: sun_light_fade( <startSunColor>, <endSunColor>, <fTime> )"
"Summary: Fade to a given sunlight RGB value over the specified time"
"Module: Utility"
"MandatoryArg: <startSunColor> : Starting RGB values (use whatever the current sun is set to)"
"MandatoryArg: <endSunColor> : Target RGB values the sun colors should change to"
"MandatoryArg: <fTime> : Time in seconds for the fade to occur"
"Example: thread sun_light_fade( (.5,.8,.75), (3.5,3.5,3.5), 2 )"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

sun_light_fade( startSunColor, endSunColor, fTime )
{
	fTime = Int( fTime * 20 );

	// determine difference btwn starting and target sun RGBs
	increment = [];
	for ( i = 0; i < 3; i++ )
		increment[ i ] = ( startSunColor[ i ] - endSunColor[ i ] ) / fTime;

	// change gradually to new sun color over time
    newSunColor = [];
    for ( i = 0; i < fTime; i++ )
    {
    	wait( 0.05 );
    	for ( j = 0; j < 3; j++ )
    		newSunColor[ j ] = startSunColor[ j ] - ( increment[ j ] * i );
		SetSunLight( newSunColor[ 0 ], newSunColor[ 1 ], newSunColor[ 2 ] );
    }
    //set sunlight to new target values to account for rounding off decimal places
    SetSunLight( endSunColor[ 0 ], endSunColor[ 1 ], endSunColor[ 2 ] );
}

/*
 =============
///ScriptDocBegin
"Name: ent_flag_wait( <flagname> )"
"Summary: Waits until the specified flag is set on self. Even handles some default flags for ai such as 'goal' and 'damage'"
"Module: Flag"
"CallOn: Any entity (script_origin, script_struct, ai, script_model, script_brushmodel, player)"
"MandatoryArg: <flagname> : name of the flag to wait on"
"Example: enemy ent_flag_wait( "goal" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
ent_flag_wait( msg )
{
	AssertEx( ( !IsSentient( self ) && IsDefined( self ) ) || IsAlive( self ), "Attempt to check a flag on entity that is not alive or removed" );

	while ( IsDefined( self ) && !self.ent_flag[ msg ] )
		self waittill( msg );
}

/*
 =============
///ScriptDocBegin
"Name: ent_flag_wait_vehicle_node( <flagname> )"
"Summary: Waits until the specified flag is set on self. Even handles some default flags for ai such as 'goal' and 'damage'"
"Module: Flag"
"CallOn: Any entity (script_origin, script_struct, ai, script_model, script_brushmodel, player)"
"MandatoryArg: <flagname> : name of the flag to wait on"
"Example: enemy ent_flag_wait( "goal" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
ent_flag_wait_vehicle_node( msg )
{
	AssertEx( IsDefined( self ) , "Attempt to check a flag on node that is is not defined" );

	while ( IsDefined( self ) && !self.ent_flag[ msg ] )
		self waittill( msg );
}


 /*
 =============
///ScriptDocBegin
"Name: ent_flag_wait_either( <flagname1> , <flagname2> )"
"Summary: Waits until either of the the specified flags are set on self. Even handles some default flags for ai such as 'goal' and 'damage'"
"Module: Flag"
"CallOn: Any entity (script_origin, script_struct, ai, script_model, script_brushmodel, player)"
"MandatoryArg: <flagname1> : name of one flag to wait on"
"MandatoryArg: <flagname2> : name of the other flag to wait on"
"Example: enemy ent_flag_wait( "goal", "damage" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
ent_flag_wait_either( flag1, flag2 )
{
	AssertEx( ( !IsSentient( self ) && IsDefined( self ) ) || IsAlive( self ), "Attempt to check a flag on entity that is not alive or removed" );

	while ( IsDefined( self ) )
	{
		if ( ent_flag( flag1 ) )
			return;
		if ( ent_flag( flag2 ) )
			return;

		self waittill_either( flag1, flag2 );
	}
}

 /*
 =============
///ScriptDocBegin
"Name: ent_flag_wait_or_timeout( <flagname> , <timer> )"
"Summary: Waits until either the flag gets set on self or the timer elapses. Even handles some default flags for ai such as 'goal' and 'damage'"
"Module: Flag"
"CallOn: Any entity (script_origin, script_struct, ai, script_model, script_brushmodel, player)"
"MandatoryArg: <flagname1: Name of one flag to wait on"
"MandatoryArg: <timer> : Amount of time to wait before continuing regardless of flag."
"Example: ent_flag_wait_or_timeout( "time_to_go", 3 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
ent_flag_wait_or_timeout( flagname, timer )
{
	AssertEx( ( !IsSentient( self ) && IsDefined( self ) ) || IsAlive( self ), "Attempt to check a flag on entity that is not alive or removed" );

	start_time = GetTime();
	while ( IsDefined( self ) )
	{
		if ( self.ent_flag[ flagname ] )
			break;

		if ( GetTime() >= start_time + timer * 1000 )
			break;

		self ent_wait_for_flag_or_time_elapses( flagname, timer );
	}
}

/*
=============
///ScriptDocBegin
"Name: ent_flag_waitopen( <msg> )"
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
ent_flag_waitopen( msg )
{
	AssertEx( ( !IsSentient( self ) && IsDefined( self ) ) || IsAlive( self ), "Attempt to check a flag on entity that is not alive or removed" );

	while ( IsDefined( self ) && self.ent_flag[ msg ] )
		self waittill( msg );
}

ent_flag_assert( msg )
{
	AssertEx( !self ent_flag( msg ), "Flag " + msg + " set too soon on entity" );
}


 /*
 =============
///ScriptDocBegin
"Name: ent_flag_waitopen_either( <flagname1> , <flagname2> )"
"Summary: Waits until either of the the specified flags are open on self. Even handles some default flags for ai such as 'goal' and 'damage'"
"Module: Flag"
"CallOn: Any entity (script_origin, script_struct, ai, script_model, script_brushmodel, player)"
"MandatoryArg: <flagname1> : name of one flag to waitopen on"
"MandatoryArg: <flagname2> : name of the other flag to waitopen on"
"Example: enemy ent_flag_waitopen_either( "goal", "damage" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
ent_flag_waitopen_either( flag1, flag2 )
{
	AssertEx( ( !IsSentient( self ) && IsDefined( self ) ) || IsAlive( self ), "Attempt to check a flag on entity that is not alive or removed" );

	while ( IsDefined( self ) )
	{
		if ( !ent_flag( flag1 ) )
			return;
		if ( !ent_flag( flag2 ) )
			return;

		self waittill_either( flag1, flag2 );
	}
}

 /*
 =============
///ScriptDocBegin
"Name: ent_flag_init( <flagname> )"
"Summary: Initialize a flag to be used. All flags must be initialized before using ent_flag_set or ent_flag_wait.  Some flags for ai are set by default such as 'goal', 'death', and 'damage'"
"Module: Flag"
"CallOn: Any entity (script_origin, script_struct, ai, script_model, script_brushmodel, player)"
"MandatoryArg: <flagname> : name of the flag to create"
"Example: enemy ent_flag_init( "hq_cleared" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
ent_flag_init( message )
{
	if ( !isDefined( self.ent_flag ) )
	{
		self.ent_flag = [];
		self.ent_flags_lock = [];
	}

	/#
	if ( IsDefined( level.first_frame ) && level.first_frame == -1 )
		AssertEx( !isDefined( self.ent_flag[ message ] ), "Attempt to reinitialize existing message: " + message + " on entity." );
	#/

	self.ent_flag[ message ] = false;
/#
	self.ent_flags_lock[ message ] = false;
#/
}

 /*
 =============
///ScriptDocBegin
"Name: ent_flag_exist( <flagname> )"
"Summary: checks to see if a flag exists"
"Module: Flag"
"CallOn: Any entity (script_origin, script_struct, ai, script_model, script_brushmodel, player)"
"MandatoryArg: <flagname> : name of the flag to check"
"Example: if( enemy ent_flag_exist( "hq_cleared" ) );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
ent_flag_exist( message )
{
	if ( IsDefined( self.ent_flag ) && IsDefined( self.ent_flag[ message ] ) )
		return true;
	return false;
}

 /*
 =============
///ScriptDocBegin
"Name: ent_flag_set_delayed( <flagname> , <delay> )"
"Summary: Sets the specified flag after waiting the delay time on self, all scripts using ent_flag_wait on self will now continue."
"Module: Flag"
"CallOn: Any entity (script_origin, script_struct, ai, script_model, script_brushmodel, player)"
"MandatoryArg: <flagname> : name of the flag to set"
"MandatoryArg: <delay> : time to wait before setting the flag"
"Example: entity flag_set_delayed( "hq_cleared", 2.5 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
ent_flag_set_delayed( message, delay )
{
	self endon( "death" );

	wait( delay );
	self ent_flag_set( message );
}

 /*
 =============
///ScriptDocBegin
"Name: ent_flag_set( <flagname> )"
"Summary: Sets the specified flag on self, all scripts using ent_flag_wait on self will now continue."
"Module: Flag"
"CallOn: Any entity (script_origin, script_struct, ai, script_model, script_brushmodel, player)"
"MandatoryArg: <flagname> : name of the flag to set"
"Example: enemy ent_flag_set( "hq_cleared" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
ent_flag_set( message )
{
/#
 	AssertEx( IsDefined( self ), "Attempt to set a flag on entity that is not defined" );
	AssertEx( IsDefined( self.ent_flag[ message ] ), "Attempt to set a flag before calling flag_init: " + message + " on entity." );
	Assert( self.ent_flag[ message ] == self.ent_flags_lock[ message ] );
	self.ent_flags_lock[ message ] = true;
#/
	self.ent_flag[ message ] = true;
	self notify( message );
}

 /*
 =============
///ScriptDocBegin
"Name: ent_flag_clear( <flagname> )"
"Summary: Clears the specified flag on self."
"Module: Flag"
"CallOn: Any entity (script_origin, script_struct, ai, script_model, script_brushmodel, player)"
"MandatoryArg: <flagname> : name of the flag to clear"
"Example: enemy ent_flag_clear( "hq_cleared" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
ent_flag_clear( message )
{
/#
 	AssertEx( IsDefined( self ), "Attempt to clear a flag on entity that is not defined" );
	AssertEx( IsDefined( self.ent_flag[ message ] ), "Attempt to set a flag before calling flag_init: " + message + " on entity." );
	Assert( self.ent_flag[ message ] == self.ent_flags_lock[ message ] );
	self.ent_flags_lock[ message ] = false;
#/
	//do this check so we don't unneccessarily send a notify
	if ( 	self.ent_flag[ message ] )
	{
		self.ent_flag[ message ] = false;
		self notify( message );
	}
}

/*
=============
///ScriptDocBegin
"Name: ent_flag_clear_delayed( <message> , <delay> )"
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
ent_flag_clear_delayed( message, delay )
{
	wait( delay );
	self ent_flag_clear( message );
}

 /*
 =============
///ScriptDocBegin
"Name: ent_flag( <flagname> )"
"Summary: Checks if the flag is set on self. Returns true or false."
"Module: Flag"
"CallOn: Any entity (script_origin, script_struct, ai, script_model, script_brushmodel, player)"
"MandatoryArg: <flagname> : name of the flag to check"
"Example: enemy ent_flag( "death" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
ent_flag( message )
{
	AssertEx( IsDefined( message ), "Tried to check flag but the flag was not defined." );
	AssertEx( IsDefined( self.ent_flag[ message ] ), "Tried to check flag " + message + " but the flag was not initialized." );

	return self.ent_flag[ message ];
}
 /*
 =============
///ScriptDocBegin
"Name: get_closest_to_player_view( <array>, <player>, <use_eye> )"
"Summary: Returns array member closest to player's view"
"Module: Utility"
"CallOn: Variable"
"MandatoryArg: <array>: The array of items to test against"
"OptionalArg: <player>: Player to test against. If undefined defaults to level.player"
"OptionalArg: <use_eye>: Check from the player's eye point. If undefined uses the player's origin."
"OptionalArg: <min_dot>: min dot"
"Example: enemy get_closest_to_player_view( enemies, level.player2, true );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_closest_to_player_view( array, player, use_eye, min_dot )
{
	if ( !array.size )
		return;

	if ( !isdefined( player ) )
		player = level.player;

	if ( !isdefined( min_dot ) )
		min_dot = -1;

	player_origin = player.origin;
	if ( IsDefined( use_eye ) && use_eye )
		player_origin = player GetEye();

	ent = undefined;

	player_angles = player GetPlayerAngles();
	player_forward = AnglesToForward( player_angles );

	dot = -1;
	foreach ( array_item in array )
	{
		angles = VectorToAngles( array_item.origin - player_origin );
		forward = AnglesToForward( angles );

		newdot = VectorDot( player_forward, forward );
		if ( newdot < dot )
			continue;
		if ( newdot < min_dot )
			continue;
		dot = newdot;
		ent = array_item;
	}
	return ent;
}

/*
 =============
///ScriptDocBegin
"Name: get_closest_index_to_player_view( <array>, <player>, <use_eye> )"
"Summary: Returns array index of item closest to player's view"
"Module: Utility"
"CallOn: Variable"
"MandatoryArg: <array>: The array of items to test against"
"OptionalArg: <player>: Player to test against. If undefined defaults to level.player"
"OptionalArg: <use_eye>: Check from the player's eye point. If undefined uses the player's origin."
"OptionalArg: <return_index>: If true, will return the index within the array rather than the actual array element."
"Example: enemy get_closest_index_to_player_view( enemies, level.player2, true );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_closest_index_to_player_view( array, player, use_eye )
{
	if ( !array.size )
		return;

	if ( !isdefined( player ) )
		player = level.player;

	player_origin = player.origin;
	if ( IsDefined( use_eye ) && use_eye )
		player_origin = player GetEye();

	index = undefined;

	player_angles = player GetPlayerAngles();
	player_forward = AnglesToForward( player_angles );

	dot = -1;
	for ( i = 0; i < array.size; i++ )
	{
		angles = VectorToAngles( array[ i ].origin - player_origin );
		forward = AnglesToForward( angles );

		newdot = VectorDot( player_forward, forward );
		if ( newdot < dot )
			continue;

		dot = newdot;
		index = i;
	}
	return index;
}

flag_trigger_init( message, trigger, continuous )
{
	flag_init( message );

	if ( !isDefined( continuous ) )
		continuous = false;

	Assert( IsSubStr( trigger.classname, "trigger" ) );
	trigger thread _flag_wait_trigger( message, continuous );

	return trigger;
}


flag_triggers_init( message, triggers, all )
{
	flag_init( message );

	if ( !isDefined( all ) )
		all = false;

	for ( index = 0; index < triggers.size; index++ )
	{
		Assert( IsSubStr( triggers[ index ].classname, "trigger" ) );
		triggers[ index ] thread _flag_wait_trigger( message, false );
	}

	return triggers;
}


/*
=============
///ScriptDocBegin
"Name: flag_set_delayed( <flagname> , <delay> )"
"Summary: Sets the specified flag after waiting the delay time, all scripts using flag_wait will now continue."
"Module: Flag"
"CallOn: "
"MandatoryArg: <flagname> : name of the flag to set"
"MandatoryArg: <delay> : time to wait before setting the flag"
"Example: flag_set_delayed( "hq_cleared", 2.5 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
*/
flag_set_delayed( message, delay )
{
	wait( delay );
	flag_set( message );
}

/*
=============
///ScriptDocBegin
"Name: flag_clear_delayed( <flagname> , <delay> )"
"Summary: Clears the specified flag after waiting the delay time, all scripts using flag_waitopen will now continue."
"Module: Flag"
"CallOn: "
"MandatoryArg: <flagname> : name of the flag to clear"
"MandatoryArg: <delay> : time to wait before clearing the flag"
"Example: flag_clear_delayed( "hq_cleared", 2.5 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
*/
flag_clear_delayed( message, delay )
{
	wait( delay );
	flag_clear( message );
}

_flag_wait_trigger( message, continuous )
{
	self endon( "death" );

	for ( ;; )
	{
		self waittill( "trigger", other );
		flag_set( message );

		if ( !continuous )
			return;

		while ( other IsTouching( self ) )
			wait( 0.05 );

		flag_clear( message );
	}
}

level_end_save()
{
	if ( arcadeMode() )
		return;

	if ( level.MissionFailed )
		return;

	if ( flag( "game_saving" ) )
		return;

	for ( i = 0; i < level.players.size; i++ )
	{
		player = level.players[ i ];
		if ( !isAlive( player ) )
			return;
	}

	flag_set( "game_saving" );

	imagename = "levelshots / autosave / autosave_" + level.script + "end";

	// string not found for AUTOSAVE_AUTOSAVE
	SaveGame( "levelend", &"AUTOSAVE_AUTOSAVE", imagename, true );// does not print "Checkpoint Reached"

	flag_clear( "game_saving" );
}

/*
=============
///ScriptDocBegin
"Name: add_extra_autosave_check( <name> , <func> , <msg> )"
"Summary: Adds an extra autosave check that must pass for an autosave to happen"
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <name>: identify the index, of this autosave check ( so you can overwrite it )"
"MandatoryArg: <func>: function should return true for the check to pass"
"MandatoryArg: <msg>: this is what will print to the console when this check fails"
"Example: 		add_extra_autosave_check( "boat_check_trailing" , ::autosave_boat_check_trailing , "trailing too far behind the enemy boat." );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_extra_autosave_check( name, func, msg )
{
	level._extra_autosave_checks[ name ] = [];
	level._extra_autosave_checks[ name ][ "func" ] = func;
	level._extra_autosave_checks[ name ][ "msg" ] = msg;
}

/*
=============
///ScriptDocBegin
"Name: remove_extra_autosave_check( <name> )"
"Summary: removes the extra autosave game condtions added by add_extra_autosave_check"
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <param1>: Name"
"Example: add_extra_autosave_check( "boat_check_trailing" ); "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
remove_extra_autosave_check( name )
{
	level._extra_autosave_checks[ name ] = undefined;
}

/*
=============
///ScriptDocBegin
"Name: autosave_stealth()"
"Summary: autosave the game if it's 'safe' to do so in a stealth level, internally threaded and handles any 'dangerous' situations that we wouldn't want to save at during stealth gameplay"
"Module: Autosave"
"CallOn: "
"Example: autosave_stealth();"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
*/
autosave_stealth()
{
	thread autosave_by_name_thread( "autosave_stealth", 8, true );
}

/*
=============
///ScriptDocBegin
"Name: autosave_tactical()"
"Summary: autosave the game if it's 'safe' during tactical gameplay...meaning don't autosave if the player has any current enemies or has thrown a grenade. ( internally threaded )"
"Module: Autosave"
"CallOn: "
"Example: autosave_tactical();"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
*/
autosave_tactical()
{
	autosave_tactical_setup();
	thread autosave_tactical_proc();
}

/*
=============
///ScriptDocBegin
"Name: autosave_by_name( <savename> )"
"Summary: autosave the game with the specified save name"
"Module: Autosave"
"CallOn: "
"MandatoryArg: <savename> : name of the save file to create"
"Example: thread autosave_by_name( "building2_cleared" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
*/
autosave_by_name( name )
{
	thread autosave_by_name_thread( name );
}

/*
=============
///ScriptDocBegin
"Name: autosave_by_name_silent( <savename> )"
"Summary: autosave the game with the specified save name without printing a checkpoint msg"
"Module: Autosave"
"CallOn: "
"MandatoryArg: <savename> : name of the save file to create"
"Example: thread autosave_by_name_silent( "building2_cleared" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
*/
autosave_by_name_silent( name )
{
	thread autosave_by_name_thread( name, undefined, undefined, true );
}

autosave_by_name_thread( name, timeout, doStealthChecks, suppress_hint )
{
	if ( !isDefined( level.curAutoSave ) )
		level.curAutoSave = 1;

	imageName = "levelshots/autosave/autosave_" + level.script + level.curAutoSave;
	result = level maps\_autosave::tryAutoSave( level.curAutoSave, "autosave", imagename, timeout, doStealthChecks, suppress_hint );
	if ( IsDefined( result ) && result )
		level.curAutoSave++;
}

/*
=============
///ScriptDocBegin
"Name: autosave_or_timeout( <name> , <timeout> )"
"Summary: Autosaves with the specified name but times out if the time elapses"
"Module: Autosave"
"MandatoryArg: <name>: The name"
"MandatoryArg: <timeout>: The timeout"
"Example: autosave_or_timeout( "thename", 3.5 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
autosave_or_timeout( name, timeout )
{
	thread autosave_by_name_thread( name, timeout );
}

/*
=============
///ScriptDocBegin
"Name: debug_message( <message> , <origin>, <duration>, <entity> )"
"Summary: Prints 3d debug text at the specified location for a duration of time."
"Module: Debug"
"MandatoryArg: <message>: String to print"
"MandatoryArg: <origin>: Location of string ( x, y, z )"
"OptionalArg: <duration>: Time to keep the string on screen. Defaults to 5 seconds."
"OptionalArg: <entity>: Overrides any origin value so that message can print on a moving entity"
"Example: debug_message( "I am the enemy", enemy.origin, 3.0 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
debug_message( message, origin, duration, entity )
{
	if ( !isDefined( duration ) )
		duration = 5;

	if ( IsDefined( entity ) )
	{
		entity endon( "death" );
		origin = entity.origin;
	}


	for ( time = 0; time < ( duration * 20 ); time++ )
	{
		if ( !isdefined( entity ) )
			Print3d( ( origin + ( 0, 0, 45 ) ), message, ( 0.48, 9.4, 0.76 ), 0.85 );
		else
			Print3d( entity.origin, message, ( 0.48, 9.4, 0.76 ), 0.85 );
		wait 0.05;
	}
}

/*
=============
///ScriptDocBegin
"Name: debug_message_ai( <message>, <duration> )"
"Summary: Prints 3d debug text at the ai's origin and follows the ai that passed the function."
"Module: Debug"
"CallOn: An AI"
"MandatoryArg: <message>: String to print"
"OptionalArg: <duration>: Time to keep the string on screen. Defaults to 5 seconds."
"Example: debug_message_ai( "I am the enemy", 3.0 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
debug_message_ai( message, duration )
{
	self notify( "debug_message_ai" );
	self endon( "debug_message_ai" );
	self endon( "death" );

	if ( !isDefined( duration ) )
		duration = 5;

	for ( time = 0; time < ( duration * 20 ); time++ )
	{
		Print3d( ( self.origin + ( 0, 0, 45 ) ), message, ( 0.48, 9.4, 0.76 ), 0.85 );
		wait 0.05;
	}
}

/*
=============
///ScriptDocBegin
"Name: debug_message_clear( <message> , <origin>, <duration>, <extraEndon> )"
"Summary: Prints 3d debug text at the specified location for a duration of time, but can be cleared before the normal time has passed if a notify occurs."
"Module: Debug"
"MandatoryArg: <message>: String to print"
"MandatoryArg: <origin>: Location of string ( x, y, z )"
"OptionalArg: <duration>: Time to keep the string on screen. Defaults to 5 seconds."
"OptionalArg: <extraEndon>: Level notify string that will make this text go away before the time expires."
"Example: debug_message( "I am the enemy", enemy.origin, 3.0, "enemy died" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
debug_message_clear( message, origin, duration, extraEndon )
{
	if ( IsDefined( extraEndon ) )
	{
		level notify( message + extraEndon );
		level endon( message + extraEndon );
	}
	else
	{
		level notify( message );
		level endon( message );
	}

	if ( !isDefined( duration ) )
		duration = 5;

	for ( time = 0; time < ( duration * 20 ); time++ )
	{
		Print3d( ( origin + ( 0, 0, 45 ) ), message, ( 0.48, 9.4, 0.76 ), 0.85 );
		wait 0.05;
	}
}

chain_off( chain )
{
	trigs = GetEntArray( "trigger_friendlychain", "classname" );
	for ( i = 0; i < trigs.size; i++ )
	if ( ( IsDefined( trigs[ i ].script_chain ) ) && ( trigs[ i ].script_chain == chain ) )
	{
		if ( IsDefined( trigs[ i ].oldorigin ) )
			trigs[ i ].origin = trigs[ i ].oldorigin;
		else
			trigs[ i ].oldorigin = trigs[ i ].origin;

		trigs[ i ].origin = trigs[ i ].origin + ( 0, 0, -5000 );
	}
}

chain_on( chain )
{
	trigs = GetEntArray( "trigger_friendlychain", "classname" );
	for ( i = 0; i < trigs.size; i++ )
	if ( ( IsDefined( trigs[ i ].script_chain ) ) && ( trigs[ i ].script_chain == chain ) )
	{
		if ( IsDefined( trigs[ i ].oldorigin ) )
			trigs[ i ].origin = trigs[ i ].oldorigin;
	}
}

precache( model )
{
	ent = Spawn( "script_model", ( 0, 0, 0 ) );
	ent.origin = level.player GetOrigin();
	ent SetModel( model );
	ent Delete();
}


closerFunc( dist1, dist2 )
{
	return dist1 >= dist2;
}

fartherFunc( dist1, dist2 )
{
	return dist1 <= dist2;
}

 /*
 =============
///ScriptDocBegin
"Name: getClosest( <org> , <array> , <dist> )"
"Summary: Returns the closest entity in < array > to location < org > "
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be closest to."
"MandatoryArg: <array> : Array of entities to check distance on"
"OptionalArg: <maxdist> : Minimum distance to check"
"Example: friendly = getClosest( level.player.origin, allies );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
getClosest( org, array, maxdist )
{
	if ( !IsDefined( maxdist ) )
		maxdist = 500000; // twice the size of the grid

	ent = undefined;
	foreach ( item in array )
	{
		newdist = Distance( item.origin, org );
		if ( newdist >= maxdist )
			continue;
		maxdist = newdist;
		ent = item;
	}
	return ent;
}

 /*
 =============
///ScriptDocBegin
"Name: getFarthest( <org> , <array> , <dist> )"
"Summary: Returns the farthest entity in < array > to location < org > "
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be farthest from."
"MandatoryArg: <array> : Array of entities to check distance on"
"OptionalArg: <maxdist> : Maximum distance to check"
"Example: target = getFarthest( level.player.origin, targets );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
getFarthest( org, array, maxdist )
{
	if ( !IsDefined( maxdist ) )
		maxdist = 500000; // twice the size of the grid

	dist = 0;
	ent = undefined;
	foreach ( item in array )
	{
		newdist = Distance( item.origin, org );
		if ( newdist <= dist || newdist >= maxdist )
			continue;
		dist = newdist;
		ent = item;
	}
	return ent;
}

 /*
 =============
///ScriptDocBegin
"Name: getClosestFx( <org> , <fxarray> , <dist> )"
"Summary: Returns the closest fx struct created by createfx in < fxarray > to location < org > "
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be closest to."
"MandatoryArg: <array> : Array of createfx structs to check distance on. These are obtained with getfxarraybyID( <fxid> )"
"OptionalArg: <dist> : Minimum distance to check"
"Example: fxstruct = getClosestFx( hallway_tv, fxarray );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
getClosestFx( org, fxarray, dist )
{
	return compareSizesFx( org, fxarray, dist, ::closerFunc );
}



 /*
 =============
///ScriptDocBegin
"Name: get_closest_point( <origin> , <points> , <maxDist> )"
"Summary: Returns the closest point from array < points > from location < origin > "
"Module: Distance"
"CallOn: "
"MandatoryArg: <origin> : Origin to be closest to."
"MandatoryArg: <points> : Array of points to check distance on"
"OptionalArg: <maxDist> : Maximum distance to check"
"Example: target = getFarthest( level.player.origin, targets );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_closest_point( origin, points, maxDist )
{
	Assert( points.size );

	closestPoint = points[ 0 ];
	dist = Distance( origin, closestPoint );

	for ( index = 0; index < points.size; index++ )
	{
		testDist = Distance( origin, points[ index ] );
		if ( testDist >= dist )
			continue;

		dist = testDist;
		closestPoint = points[ index ];
	}

	if ( !isDefined( maxDist ) || dist <= maxDist )
		return closestPoint;

	return undefined;
}

 /*
 =============
///ScriptDocBegin
"Name: get_farthest_ent( <origin> , <array> )"
"Summary: Returns the farthest entity in <array> from location < origin > "
"Module: Distance"
"CallOn: "
"MandatoryArg: <origin> : Origin to be farthest from."
"MandatoryArg: <array> : Array of entities to choose from"
"Example: dude = get_farthest_ent( level.player.origin, aFriendlies );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_farthest_ent( org, array )
{
	if ( array.size < 1 )
		return;

	dist = Distance( array[ 0 ] GetOrigin(), org );
	ent = array[ 0 ];
	for ( i = 0; i < array.size; i++ )
	{
		newdist = Distance( array[ i ] GetOrigin(), org );
		if ( newdist < dist )
			continue;
		dist = newdist;
		ent = array[ i ];
	}
	return ent;
}


 /*
 =============
///ScriptDocBegin
"Name: get_within_range( <org> , <array> , <dist> )"
"Summary: Returns all elements from the array that are within DIST range to ORG."
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be closest to."
"MandatoryArg: <array> : Array of entities to check distance on"
"OptionalArg: <dist> : Maximum distance to check"
"Example: close_ai = get_within_range( level.player.origin, ai, 500 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_within_range( org, array, dist )
{
	guys = [];
	for ( i = 0; i < array.size; i++ )
	{
		if ( Distance( array[ i ].origin, org ) <= dist )
			guys[ guys.size ] = array[ i ];
	}
	return guys;
}

 /*
 =============
///ScriptDocBegin
"Name: get_outside_range( <org> , <array> , <dist> )"
"Summary: Returns all elements from the array that are outside DIST range to ORG."
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be closest to."
"MandatoryArg: <array> : Array of entities to check distance on"
"OptionalArg: <dist> : Maximum distance to check"
"Example: close_ai = get_outside_range( level.player.origin, ai, 500 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_outside_range( org, array, dist )
{
	guys = [];
	for ( i = 0; i < array.size; i++ )
	{
		if ( Distance( array[ i ].origin, org ) > dist )
			guys[ guys.size ] = array[ i ];
	}
	return guys;
}

 /*
 =============
///ScriptDocBegin
"Name: get_closest_living( <org> , <array> , <dist> )"
"Summary: Returns the closest living entity from the array from the origin"
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be closest to."
"MandatoryArg: <array> : Array of entities to check distance on"
"OptionalArg: <dist> : Maximum distance to check"
"Example: kicker = get_closest_living( node.origin, ai );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_closest_living( org, array, dist )
{
	if ( !isdefined( dist ) )
		dist = 9999999;
	if ( array.size < 1 )
		return;
	ent = undefined;
	for ( i = 0; i < array.size; i++ )
	{
		if ( !isalive( array[ i ] ) )
			continue;
		newdist = Distance( array[ i ].origin, org );
		if ( newdist >= dist )
			continue;
		dist = newdist;
		ent = array[ i ];
	}
	return ent;
}

/*
=============
///ScriptDocBegin
"Name: get_highest_dot( <start> , <end> , <array> )"
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
get_highest_dot( start, end, array )
{
	if ( !array.size )
		return;

	ent = undefined;

	angles = VectorToAngles( end - start );
	dotforward = AnglesToForward( angles );
	dot = -1;

	foreach ( member in array )
	{
		angles = VectorToAngles( member.origin - start );
		forward = AnglesToForward( angles );

		newdot = VectorDot( dotforward, forward );
		if ( newdot < dot )
			continue;
		dot = newdot;
		ent = member;
	}
	return ent;
}

 /*
 =============
///ScriptDocBegin
"Name: get_closest_index( <org> , <array> , <dist> )"
"Summary: same as getClosest but returns the closest entity's array index instead of the actual entity."
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be closest to."
"MandatoryArg: <array> : Array of entities to check distance on."
"OptionalArg: <dist> : Maximum distance to check"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_closest_index( org, array, dist )
{
	if ( !isdefined( dist ) )
		dist = 9999999;
	if ( array.size < 1 )
		return;
	index = undefined;
	foreach ( i, ent in array )
	{
		newdist = Distance( ent.origin, org );
		if ( newdist >= dist )
			continue;
		dist = newdist;
		index = i;
	}
	return index;
}

/*
=============
///ScriptDocBegin
"Name: get_closest_exclude( <org> , <ents> , <excluders> )"
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
get_closest_exclude( org, ents, excluders )
{
	if ( !isdefined( ents ) )
		return undefined;

	range = 0;
	if ( IsDefined( excluders ) && excluders.size )
	{
		exclude = [];
		for ( i = 0; i < ents.size; i++ )
			exclude[ i ] = false;

		for ( i = 0; i < ents.size; i++ )
		for ( p = 0; p < excluders.size; p++ )
		if ( ents[ i ] == excluders[ p ] )
			exclude[ i ] = true;

		found_unexcluded = false;
		for ( i = 0; i < ents.size; i++ )
		if ( ( !exclude[ i ] ) && ( IsDefined( ents[ i ] ) ) )
		{
			found_unexcluded = true;
			range = Distance( org, ents[ i ].origin );
			ent = i;
			i = ents.size + 1;
		}

		if ( !found_unexcluded )
			return( undefined );
	}
	else
	{
		for ( i = 0; i < ents.size; i++ )
		if ( IsDefined( ents[ i ] ) )
		{
			range = Distance( org, ents[ 0 ].origin );
			ent = i;
			i = ents.size + 1;
		}
	}

	ent = undefined;

	for ( i = 0; i < ents.size; i++ )
	if ( IsDefined( ents[ i ] ) )
	{
		exclude = false;
		if ( IsDefined( excluders ) )
		{
			for ( p = 0; p < excluders.size; p++ )
			if ( ents[ i ] == excluders[ p ] )
				exclude = true;
		}

		if ( !exclude )
		{
			newrange = Distance( org, ents[ i ].origin );
			if ( newrange <= range )
			{
				range = newrange;
				ent = i;
			}
		}
	}

	if ( IsDefined( ent ) )
		return ents[ ent ];
	else
		return undefined;
}

 /*
 =============
///ScriptDocBegin
"Name: get_closest_player( <org> )"
"Summary: Returns the closest coop player to the specified origin."
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be closest to."
"Example: player = get_closest_player( tank.origin );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_closest_player( org )
{
	if ( level.players.size == 1 )
		return level.player;

	player = getClosest( org, level.players );
	return player;
}

 /*
 =============
///ScriptDocBegin
"Name: get_closest_player_healthy( <org> )"
"Summary: Returns the closest player that is not bleeding out to the specified origin."
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be closest to."
"Example: player = get_closest_player_healthy( tank.origin );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_closest_player_healthy( org )
{
	// JC-Laststand:ToDo - This assumes that all logic has ended once both players have gone down. This "may" be incorrect after last stand works in sp Specops
	if ( level.players.size == 1 )
		return level.player;

	healthyPlayers = get_players_healthy();

	player = getClosest( org, healthyPlayers );

	return player;
}

 /*
 =============
///ScriptDocBegin
"Name: get_players_healthy()"
"Summary: Returns all players not bleeding out."
"Module: Utility"
"Example: players = get_players_healthy();"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_players_healthy()
{
	healthy_players = [];
	foreach ( player in level.players )
	{
		if ( is_player_down( player ) )
			continue;
		
		healthy_players[ healthy_players.size ] = player;
	}
	
	return healthy_players;
}

 /*
 =============
///ScriptDocBegin
"Name: get_closest_ai( <org> , <team> )"
"Summary: Returns the closest AI of the specified team to the specified origin."
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be closest to."
"MandatoryArg: <team> : Team to use. Can be "allies", "axis", or "both"."
"Example: friendly = get_closest_ai( level.player.origin, "allies" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_closest_ai( org, team, excluders )
{
	if ( IsDefined( team ) )
		ents = GetAIArray( team );
	else
		ents = GetAIArray();

	if ( ents.size == 0 )
		return undefined;

	if ( IsDefined( excluders ) )
	{
		Assert( excluders.size > 0 );
		ents = array_remove_array( ents, excluders );
	}

	return getClosest( org, ents );
}

 /*
 =============
///ScriptDocBegin
"Name: get_array_of_farthest( <org> , <array> , <excluders> , <max>, <maxdist>, <mindist> )"
"Summary: Returns an array of all the entities in < array > sorted in order of farthest to closest."
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be farthest from."
"MandatoryArg: <array> : Array of entities to check distance on."
"OptionalArg: <excluders> : Array of entities to exclude from the check."
"OptionalArg: <max> : Max size of the array to return"
"OptionalArg: <maxdist> : Max distance from the origin to return acceptable entities"
"OptionalArg: <mindist> : Min distance from the origin to return acceptable entities"
"Example: allies_sort = get_array_of_closest( originFC1.origin, allies );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_array_of_farthest( org, array, excluders, max, maxdist, mindist )
{
	aArray = get_array_of_closest( org, array, excluders, max, maxdist, mindist );
	aArray = array_reverse( aArray );
	return aArray;
}



 /*
 =============
///ScriptDocBegin
"Name: get_array_of_closest( <org> , <array> , <excluders> , <max>, <maxdist>, <mindist> )"
"Summary: Returns an array of all the entities in < array > sorted in order of closest to farthest."
"Module: Distance"
"CallOn: "
"MandatoryArg: <org> : Origin to be closest to."
"MandatoryArg: <array> : Array of entities to check distance on."
"OptionalArg: <excluders> : Array of entities to exclude from the check."
"OptionalArg: <max> : Max size of the array to return"
"OptionalArg: <maxdist> : Max distance from the origin to return acceptable entities"
"OptionalArg: <mindist> : Min distance from the origin to return acceptable entities"
"Example: allies_sort = get_array_of_closest( originFC1.origin, allies );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_array_of_closest( org, array, excluders, max, maxdist, mindist )
{
	// pass an array of entities to this function and it will return them in the order of closest
	// to the origin you pass, you can also set max to limit how many ents get returned
	if ( !isdefined( max ) )
		max = array.size;
	if ( !isdefined( excluders ) )
		excluders = [];

	maxdist2rd = undefined;
	if ( IsDefined( maxdist ) )
		maxdist2rd = maxdist * maxdist;

	mindist2rd = 0;
	if ( IsDefined( mindist ) )
		mindist2rd = mindist * mindist;

	// optimize the common case of a simple sort
	if ( excluders.size == 0 && max >= array.size && mindist2rd == 0 && !isdefined( maxdist2rd ) )
		return SortByDistance( array, org );

	newArray = [];
	foreach ( ent in array )
	{
		excluded = false;
		foreach ( excluder in excluders )
		{
			if ( ent == excluder )
			{
				excluded = true;
				break;
			}
		}
		if ( excluded )
			continue;

		dist2rd = DistanceSquared( org, ent.origin );

		if ( IsDefined( maxdist2rd ) && dist2rd > maxdist2rd )
			continue;

		if ( dist2rd < mindist2rd )
			continue;

		newArray[ newArray.size ] = ent;
	}

	newArray = SortByDistance( newArray, org );

	if ( max >= newArray.size )
		return newArray;

	finalArray = [];
	for ( i = 0; i < max; i++ )
		finalArray[ i ] = newArray[ i ];

	return finalArray;
}

/*
=============
///ScriptDocBegin
"Name: get_closest_ai_exclude( <org> , <team> , <excluders> )"
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
get_closest_ai_exclude( org, team, excluders )
{
	if ( IsDefined( team ) )
		ents = GetAIArray( team );
	else
		ents = GetAIArray();

	if ( ents.size == 0 )
		return undefined;

	return get_closest_exclude( org, ents, excluders );
}

/*
=============
///ScriptDocBegin
"Name: get_progress( <start> , <end> , <org>, <dist> )"
"Summary: Gets the progress of the given org between the start and end points. Supply the distance for optimization."
"Module: Vector"
"CallOn: nothing"
"MandatoryArg: <start>: start point."
"MandatoryArg: <end>: end point."
"MandatoryArg: <org>: the current point of the progression."
"OptionalArg: <dist>: the distance between start and end point (give for optimization, if not given, will calculate distance)."
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_progress( start, end, org, dist_)
{
	assert(IsDefined(start));
	assert(IsDefined(end));
	assert(Isdefined(org));
	
	dist = dist_;
	if (!IsDefined(dist))
		dist = Distance( start, end );		

	dist = max(0.01, dist); // avoid division by zero
	normal = vectorNormalize( end - start );
	vec = org - start;
	progress = vectorDot( vec, normal );
	progress = progress / dist;
	progress = clamp(progress, 0, 1);
	return progress;
}

/*
=============
///ScriptDocBegin
"Name: can_see_origin( <origin>, <test_characters> )"
"Summary: Checks to see if the specified point is within the player's view."
"Module: Sentient"
"CallOn: An AI or player"
"MandatoryArg: <origin>: Origin you wish to see whether the player or AI can see."
"OptionalArg: <test_characters>: Set to determine whether the sight trace should check against characters."
"Example: level.player can_see_origin( entity.origin, true );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
can_see_origin( origin, test_characters )
{
	AssertEx( IsDefined( origin ), "can_see_origin() requires a valid origin to be passed in." );
	AssertEx( IsPlayer( self ) || IsAI( self ), "can_see_origin() can only be called on a player or AI." );

	if ( !isdefined( test_characters ) )
		test_characters = true;

	// if not in FOV, return false
	if ( !self point_in_fov( origin ) )
	{
		return false;
	}

	// if in FOV but sight trace fails, return false
	if ( !SightTracePassed( self GetEye(), origin, test_characters, self ) )
	{
		return false;
	}

	// if in FOV with successful trace, return true
	return true;
}

/*
=============
///ScriptDocBegin
"Name: point_in_fov( <origin> )"
"Summary: Checks to see if the point is within a standard player view FOV."
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <origin>: The point to check if it is within view."
"Example: level.player point_in_fov( weapon_respawn.origin );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
point_in_fov( origin )
{
    forward = AnglesToForward( self.angles );
    normalVec = VectorNormalize( origin - self.origin );

    dot = VectorDot( forward, normalVec );
    return dot > 0.766;// fov = 80
}

 /*
 =============
///ScriptDocBegin
"Name: stop_magic_bullet_shield()"
"Summary: Stops magic bullet shield on an AI, setting his health back to a normal value and making him vulnerable to death."
"Module: AI"
"CallOn: AI"
"Example: friendly stop_magic_bullet_shield();"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

stop_magic_bullet_shield()
{
	self notify( "stop_magic_bullet_shield" );
	AssertEx( IsDefined( self.magic_bullet_shield ) && self.magic_bullet_shield, "Tried to stop magic bullet shield on a guy without magic bulletshield" );

	if ( IsAI( self ) )
		self.attackeraccuracy = 1;

	self.magic_bullet_shield = undefined;
	self.damageShield = false;

	self notify( "internal_stop_magic_bullet_shield" );
}

// For future projects we should distinguish between "death" and "deletion"
// Since we currently do not, bulletshield has to be turned off before deleting characters, or you will get the 2nd assert below
magic_bullet_death_detection()
{
	/#
	self endon( "internal_stop_magic_bullet_shield" );
	export = self.export;
	entnum = self GetEntNum();

	self waittill( "death" );
	if ( IsDefined( self ) )
		AssertEx( 0, "Magic bullet shield guy with export " + export + " died some how." );
	else
		AssertEx( 0, "Magic bullet shield guy with export " + export + " died, most likely deleted from spawning guys." );

	export = export;// extra line so you can get this info in the debugger without a breakpoint.

	#/
}

 /*
 =============
///ScriptDocBegin
"Name: magic_bullet_shield( <no_death_detection> )"
"Summary: Makes an AI invulnerable to death. When he gets shot, he is ignored by enemies for < time > seconds and his health is regenerated."
"Module: AI"
"CallOn: AI"
"OptionalArg: <no_death_detection> : Set this to make the AI not script error on death, like if you want the guy to be deletable."
"Example: friendly thread magic_bullet_shield();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

magic_bullet_shield( no_death_detection )
{
	if ( IsAI( self ) )// AI only
	{
		AssertEx( IsAlive( self ), "Tried to do magic_bullet_shield on a dead or undefined guy." );
		AssertEx( !self.delayedDeath, "Tried to do magic_bullet_shield on a guy about to die." );
		AssertEx( !isDefined( self.Melee ), "Trying to turn on magic_bullet_shield while melee in progress (might be about to die)." );
	}
	else
	{
		self.health = 100000;
	}


	self endon( "internal_stop_magic_bullet_shield" );
	AssertEx( !isdefined( self.magic_bullet_shield ), "Can't call magic bullet shield on a character twice. Use make_hero and remove_heroes_from_array so that you don't end up with shielded guys in your logic." );

	if ( IsAI( self ) )// AI only
		self.attackeraccuracy = 0.1;

	/#
	if ( !isdefined( no_death_detection ) )
		thread magic_bullet_death_detection();
	else
		AssertEx( no_death_detection, "no_death_detection must be undefined or true" );
	#/

	self.magic_bullet_shield = true;
	self.damageShield = true;
}


/*
=============
///ScriptDocBegin
"Name: disable_long_death(  )"
"Summary: Disables long death on Self"
"Module: Utility"
"CallOn: An enemy AI"
"Example: level.zakhaev disable_long_death()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_long_death()
{
	AssertEx( IsAlive( self ), "Tried to disable long death on a non living thing" );
	self.a.disableLongDeath = true;
}

/*
=============
///ScriptDocBegin
"Name: enable_long_death(  )"
"Summary: Enables long death on Self"
"Module: Utility"
"CallOn: An enemy AI"
"Example: level.zakhaev enable_long_death(0"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_long_death()
{
	AssertEx( IsAlive( self ), "Tried to enable long death on a non living thing" );
	self.a.disableLongDeath = false;
}

/*
=============
///ScriptDocBegin
"Name: enable_blood_pool( <enable_blood_pool> )"
"Summary: enables blood pools on AI deaths( on by default )"
"Module: AI"
"CallOn: An AI"
"Example: ai enable_blood_pool()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_blood_pool()
{
	self.skipBloodPool = undefined;
}

/*
=============
///ScriptDocBegin
"Name: disable_blood_pool( <enable_blood_pool> )"
"Summary: disables blood pools on AI deaths( on by default )"
"Module: AI"
"CallOn: An AI"
"Example: ai disable_blood_pool()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_blood_pool()
{
	self.skipBloodPool = true;
}

/*
=============
///ScriptDocBegin
"Name: deletable_magic_bullet_shield()"
"Summary: A version of magic bullet shield that does not error if the AI dies. Useful for guys that can be deleted but you want them to have aspects of MBS."
"Module: AI"
"CallOn: AI"
"Example: friendly thread magic_bullet_shield();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
deletable_magic_bullet_shield()
{
	magic_bullet_shield( true );
}


/*
=============
///ScriptDocBegin
"Name: get_ignoreme( <get_ignoreme> )"
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
get_ignoreme()
{
	return self.ignoreme;
}

/*
=============
///ScriptDocBegin
"Name: set_ignoreme( <val> )"
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
set_ignoreme( val )
{
	AssertEx( IsSentient( self ), "Non ai tried to set ignoreme" );
	self.ignoreme = val;
}

/*
=============
///ScriptDocBegin
"Name: set_ignoreall( <val> )"
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
set_ignoreall( val )
{
	AssertEx( IsSentient( self ), "Non ai tried to set ignoraell" );
	self.ignoreall = val;
}


/*
=============
///ScriptDocBegin
"Name: set_favoriteenemy( <enemy> )"
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
set_favoriteenemy( enemy )
{
	self.favoriteenemy = enemy;
}

/*
=============
///ScriptDocBegin
"Name: get_pacifist( <get_pacifist> )"
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
get_pacifist()
{
	return self.pacifist;
}

/*
=============
///ScriptDocBegin
"Name: set_pacifist( <val> )"
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
set_pacifist( val )
{
	AssertEx( IsSentient( self ), "Non ai tried to set pacifist" );
	self.pacifist = val;
}

ignore_me_timer( time )
{
	self notify( "new_ignore_me_timer" );
	self endon( "new_ignore_me_timer" );
	self endon( "death" );

	if ( !isdefined( self.ignore_me_timer_prev_value ) )
		self.ignore_me_timer_prev_value = self.ignoreme;

	ai = GetAIArray( "bad_guys" );

	foreach ( guy in ai )
	{
		if ( !isalive( guy.enemy ) )
			continue;
		if ( guy.enemy != self )
			continue;

		guy ClearEnemy();
	}

	self.ignoreme = true;
	wait( time );

	self.ignoreme = self.ignore_me_timer_prev_value;
	self.ignore_me_timer_prev_value = undefined;
}


 /*
 =============
///ScriptDocBegin
"Name: array_randomize( <array> )"
"Summary: Randomizes the array and returns the new array."
"Module: Array"
"CallOn: "
"MandatoryArg: <array> : Array to be randomized."
"Example: roof_nodes = array_randomize( roof_nodes );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
array_randomize( array )
{
    for ( i = 0; i < array.size; i++ )
    {
        j = RandomInt( array.size );
        temp = array[ i ];
        array[ i ] = array[ j ];
        array[ j ] = temp;
    }
    return array;
}
 /*
 =============
///ScriptDocBegin
"Name: array_reverse( <array> )"
"Summary: Reverses the order of the array and returns the new array."
"Module: Array"
"CallOn: "
"MandatoryArg: <array> : Array to be reversed."
"Example: patrol_nodes = array_reverse( patrol_nodes );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
array_reverse( array )
{
	array2 = [];
	for ( i = array.size - 1; i >= 0; i-- )
		array2[ array2.size ] = array[ i ];
	return array2;
}

/*
=============
///ScriptDocBegin
"Name: delete_exploder( <num> )"
"Summary: deletes an exploder and its brushes forever."
"Module: Level"
"CallOn: Level"
"MandatoryArg: <num>: number of the exploder that you want to delete"
"Example: delete_exploder( 3 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

delete_exploder( num )
{
	num += "";

	//prof_begin( "delete_exploder" );
	if (isdefined(level.createFXexploders))
	{	// do optimized flavor if available
		exploders = level.createFXexploders[num];
		if (isdefined(exploders))
		{
			foreach (ent in exploders)
			{
				if ( IsDefined( ent.model ) )
					ent.model Delete();
			}
		}
	}
	else
	{
		for ( i = 0; i < level.createFXent.size; i++ )
		{
			ent = level.createFXent[ i ];
			if ( !isdefined( ent ) )
				continue;
	
			if ( ent.v[ "type" ] != "exploder" )
				continue;
	
			// make the exploder actually removed the array instead?
			if ( !isdefined( ent.v[ "exploder" ] ) )
				continue;
	
			if ( ent.v[ "exploder" ] + "" != num )
				continue;
	
			if ( IsDefined( ent.model ) )
				ent.model Delete();
		}
	}
	//ends trigger threads.
	level notify( "killexplodertridgers" + num );

	//prof_end( "delete_exploder" );
}

/*
=============
///ScriptDocBegin
"Name: hide_exploder_models( <num> )"
"Summary: Hides the models for an exploder."
"Module: Level"
"CallOn: Level"
"MandatoryArg: <num>: number of the exploder that you want to hide"
"Example: hide_exploder_models( 3 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

hide_exploder_models( num )
{
	num += "";

	//prof_begin( "hide_exploder" );

	if (isdefined(level.createFXexploders))
	{	// do optimized flavor if available
		exploders = level.createFXexploders[num];
		if (isdefined(exploders))
		{
			foreach (ent in exploders)
			{
				if ( IsDefined( ent.model ) )
					ent.model Hide();
			}
		}
	}
	else
	{
		for ( i = 0; i < level.createFXent.size; i++ )
		{
			ent = level.createFXent[ i ];
			if ( !isdefined( ent ) )
				continue;
	
			if ( ent.v[ "type" ] != "exploder" )
				continue;
	
			// make the exploder actually removed the array instead?
			if ( !isdefined( ent.v[ "exploder" ] ) )
				continue;
	
			if ( ent.v[ "exploder" ] + "" != num )
				continue;
	
	
			if ( IsDefined( ent.model ) )
					ent.model Hide();
	
		}
	}
	//prof_end( "hide_exploder" );
}

/*
=============
///ScriptDocBegin
"Name: show_exploder_models( <num> )"
"Summary: shows the models for an exploder."
"Module: Level"
"CallOn: Level"
"MandatoryArg: <num>: number of the exploder that you want to hide"
"Example: show_exploder_models( 3 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

show_exploder_models( num )
{
	num += "";

	//prof_begin( "hide_exploder" );
	if (isdefined(level.createFXexploders))
	{	// do optimized flavor if available
		exploders = level.createFXexploders[num];
		if (isdefined(exploders))
		{
			foreach (ent in exploders)
			{
				//pre exploded geo.  don't worry about deleted exploder geo..
				if ( ! exploder_model_starts_hidden( ent.model ) && ! exploder_model_is_damaged_model( ent.model ) && !exploder_model_is_chunk( ent.model ) )
				{
						ent.model Show();
				}
	
				//exploded geo and should be shown
				if ( IsDefined( ent.brush_shown ) )
					ent.model Show();
			}
		}
	}
	else
	{
		for ( i = 0; i < level.createFXent.size; i++ )
		{
			ent = level.createFXent[ i ];
			if ( !isdefined( ent ) )
				continue;
	
			if ( ent.v[ "type" ] != "exploder" )
				continue;
	
			// make the exploder actually removed the array instead?
			if ( !isdefined( ent.v[ "exploder" ] ) )
				continue;
	
			if ( ent.v[ "exploder" ] + "" != num )
				continue;
	
			if ( IsDefined( ent.model ) )
			{
	
				//pre exploded geo.  don't worry about deleted exploder geo..
				if ( ! exploder_model_starts_hidden( ent.model ) && ! exploder_model_is_damaged_model( ent.model ) && !exploder_model_is_chunk( ent.model ) )
				{
						ent.model Show();
				}
	
				//exploded geo and should be shown
				if ( IsDefined( ent.brush_shown ) )
					ent.model Show();
	
			}
		}
	}
	//prof_end( "hide_exploder" );
}

exploder_model_is_damaged_model( ent )
{
	return( IsDefined( ent.targetname ) ) && ( ent.targetname == "exploder" );
}

exploder_model_starts_hidden( ent )
{
	return( ent.model == "fx" ) && ( ( !isdefined( ent.targetname ) ) || ( ent.targetname != "exploderchunk" ) );
}

exploder_model_is_chunk( ent )
{
	return( IsDefined( ent.targetname ) ) && ( ent.targetname == "exploderchunk" );
}

/*
=============
///ScriptDocBegin
"Name: stop_exploder( <num> )"
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
stop_exploder( num )
{
	num += "";

	if (isdefined(level.createFXexploders))
	{	// do optimized flavor if available
		exploders = level.createFXexploders[num];
		if (isdefined(exploders))
		{
			foreach (ent in exploders)
			{
				if ( !isdefined( ent.looper ) )
					continue;
		
				ent.looper Delete();
			}
		}
	}
	else
	{
		for ( i = 0; i < level.createFXent.size; i++ )
		{
			ent = level.createFXent[ i ];
			if ( !isdefined( ent ) )
				continue;
	
			if ( ent.v[ "type" ] != "exploder" )
				continue;
	
			// make the exploder actually removed the array instead?
			if ( !isdefined( ent.v[ "exploder" ] ) )
				continue;
	
			if ( ent.v[ "exploder" ] + "" != num )
				continue;
	
			if ( !isdefined( ent.looper ) )
				continue;
	
			ent.looper Delete();
		}
	}
}

/*
=============
///ScriptDocBegin
"Name: get_exploder_array( <msg> )"
"Summary: Return an array of exploders"
"Module: Utility"
"MandatoryArg: <msg>: Exploder num/name"
"Example: exploders = get_exploder_array( "boom" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_exploder_array( msg )
{
	msg += "";
	array = [];
	if (isdefined(level.createFXexploders))
	{	// do optimized flavor if available
		exploders = level.createFXexploders[msg];
		if (isdefined(exploders))
		{
			array = exploders;
		}
	}
	else
	{
		foreach ( ent in level.createFXent )
		{
			if ( ent.v[ "type" ] != "exploder" )
				continue;
	
			// make the exploder actually removed the array instead?
			if ( !isdefined( ent.v[ "exploder" ] ) )
				continue;
	
			if ( ent.v[ "exploder" ] + "" != msg )
				continue;
	
			array[ array.size ] = ent;
		}
	}
	return array;
}

flood_spawn( spawners )
{
	maps\_spawner::flood_spawner_scripted( spawners );
}

/*
=============
///ScriptDocBegin
"Name: set_ambient( <track>, <fade> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <track>: the name of the ambient track. This will set the ambient stream, dynamic ambience, mix, reverb, and occlusion."
"OptionalArg: <fade>: the crossfade time to the new ambience."
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_ambient( track, fade_ )
{
	maps\_audio_zone_manager::AZM_start_zone(track, fade_);
}

/*
=============
///ScriptDocBegin
"Name: force_crawling_death( <angle> , <num_crawls> , <array> , <nofallanim> )"
"Summary: Force an AI to crawl"
"Module: Utility"
"CallOn: An AI"
"MandatoryArg: <angle>: The angle to crawl"
"MandatoryArg: <num_crawls>: How many times to crawl"
"OptionalArg: <array>: Sets self.a.custom_crawling_death_array"
"OptionalArg: <nofallanim>: Sets self.nofallanim"
"Example: self force_crawling_death( self.angles[ 1 ], 2, level.scr_anim[ "crawl_death_1" ], 1 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
force_crawling_death( angle, num_crawls, array, nofallanim )
{
	if ( !isdefined( num_crawls ) )
		num_crawls = 4;

	self thread force_crawling_death_proc( angle, num_crawls, array, nofallanim );
}

#using_animtree( "generic_human" );
override_crawl_death_anims()
{
	if ( IsDefined( self.a.custom_crawling_death_array ) )
	{
		self.a.array[ "crawl" ] = self.a.custom_crawling_death_array[ "crawl" ];
		self.a.array[ "death" ] = self.a.custom_crawling_death_array[ "death" ];
		self.a.crawl_fx_rate = self.a.custom_crawling_death_array[ "blood_fx_rate" ];
		if( isdefined( self.a.custom_crawling_death_array[ "blood_fx" ] ) )
			self.a.crawl_fx = self.a.custom_crawling_death_array[ "blood_fx" ];
	}

	self.a.array[ "stand_2_crawl" ] = [];
	self.a.array[ "stand_2_crawl" ][ 0 ] = %dying_stand_2_crawl_v3;

	if ( IsDefined( self.nofallanim ) )
		self.a.pose = "prone";

	self OrientMode( "face angle", self.a.force_crawl_angle );
	self.a.force_crawl_angle = undefined;
}

force_crawling_death_proc( angle, num_crawls, array, nofallanim )
{
	self.forceLongDeath = true;
	self.a.force_num_crawls = num_crawls;
	self.noragdoll = true;
	self.nofallanim = nofallanim;

	self.a.custom_crawling_death_array = array;
	self.crawlingPainAnimOverrideFunc = ::override_crawl_death_anims;

	self.maxhealth = 100000;
	self.health = 100000;
	self enable_long_death();

	if ( !isdefined( nofallanim ) || nofallanim == false )
		self.a.force_crawl_angle = angle + 181.02;
	else
	{
		self.a.force_crawl_angle = angle;
		self thread animscripts\notetracks::noteTrackPoseCrawl();
	}
}

get_friendly_chain_node( chainstring )
{
	chain = undefined;
	trigger = GetEntArray( "trigger_friendlychain", "classname" );
	for ( i = 0; i < trigger.size; i++ )
	{
		if ( ( IsDefined( trigger[ i ].script_chain ) ) && ( trigger[ i ].script_chain == chainstring ) )
		{
			chain = trigger[ i ];
			break;
		}
	}

	if ( !isdefined( chain ) )
	{
/#
		error( "Tried to get chain " + chainstring + " which does not exist with script_chain on a trigger." );
#/
		return undefined;
	}

	node = GetNode( chain.target, "targetname" );
	return node;
}

shock_ondeath()
{
	Assert( IsPlayer( self ) );

	PreCacheShellShock( "default" );
	self waittill( "death" );

	if ( IsDefined( self.specialDeath ) )
		return;

	if ( GetDvar( "r_texturebits" ) == "16" )
		return;
	self ShellShock( "default", 3 );
}

/*
=============
///ScriptDocBegin
"Name: delete_on_death_wait_sound( <ent> , <sounddone> )"
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
delete_on_death_wait_sound( ent, sounddone )
{
	ent endon( "death" );
	self waittill( "death" );
	if ( IsDefined( ent ) )
	{
		if ( ent IsWaitingOnSound() )
			ent waittill( sounddone );

		ent Delete();
	}
}

is_dead_sentient()
{
	return IsSentient( self ) && !isalive( self );
}

 /*
 =============
///ScriptDocBegin
"Name: play_sound_on_tag( <alias> , <tag>, <ends_on_death> )"
"Summary: Play the specified sound alias on a tag of an entity"
"Module: Sound"
"CallOn: An entity"
"MandatoryArg: <alias> : Sound alias to play"
"OptionalArg: <tag> : Tag on the entity to play sound on. If no tag is specified the entities origin will be used."
"OptionalArg: <ends_on_death> : The sound will be cut short if the entity dies. Defaults to false."
"OptionalArg: <op_notify_string> : Optional notify string on sound done."
"Example: vehicle thread play_sound_on_tag( "horn_honk", "tag_engine" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
play_sound_on_tag( alias, tag, ends_on_death, op_notify_string, radio_dialog )
{
	if ( is_dead_sentient() )
		return;

	org = Spawn( "script_origin", ( 0, 0, 0 ) );
	org endon( "death" );

	thread delete_on_death_wait_sound( org, "sounddone" );
	if ( IsDefined( tag ) )
		org LinkTo( self, tag, ( 0, 0, 0 ), ( 0, 0, 0 ) );
	else
	{
		org.origin = self.origin;
		org.angles = self.angles;
		org LinkTo( self );
	}

	/#
	if ( IsDefined( level.player_radio_emitter ) && ( self == level.player_radio_emitter ) )
		PrintLn( "**dialog alias playing radio: " + alias );
	#/

	org PlaySound( alias, "sounddone" );
	if ( IsDefined( ends_on_death ) )
	{
		AssertEx( ends_on_death, "ends_on_death must be true or undefined" );
		if ( !isdefined( wait_for_sounddone_or_death( org ) ) )
			org StopSounds(); // don't call StopSounds (redundantly) when the sound stopped since this can cut off sounds in SO for the non host
		wait( 0.05 );// stopsounds doesnt work if the org is deleted same frame
	}
	else
	{
		org waittill( "sounddone" );
	}
	if ( IsDefined( op_notify_string ) )
		self notify( op_notify_string );
	org Delete();
}


/*
=============
///ScriptDocBegin
"Name: play_sound_on_tag_endon_death( <alias>, <tag> )"
"Summary: Play the specified sound alias on a tag of an entity but gets cut short if the entity dies"
"Module: Sound"
"CallOn: An entity"
"MandatoryArg: <alias> : Sound alias to play"
"OptionalArg: <tag> : Tag on the entity to play sound on. If no tag is specified the entities origin will be used."
"Example: vehicle thread play_sound_on_tag_endon_death( "horn_honk", "tag_engine" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
play_sound_on_tag_endon_death( alias, tag )
{
	play_sound_on_tag( alias, tag, true );
}

 /*
 =============
///ScriptDocBegin
"Name: play_sound_on_entity( <alias> , <op_notify_string> )"
"Summary: Play the specified sound alias on an entity at it's origin"
"Module: Sound"
"CallOn: An entity"
"MandatoryArg: <alias> : Sound alias to play"
"OptionalArg: <op_notify_string> : Optional notify string on sound done."
"Example: level.player play_sound_on_entity( "breathing_better" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
play_sound_on_entity( alias, op_notify_string )
{
	AssertEx( !isSpawner( self ), "Spawner tried to play a sound" );

	play_sound_on_tag( alias, undefined, undefined, op_notify_string );
}

 /*
 =============
///ScriptDocBegin
"Name: play_loop_sound_on_tag( <alias> , <tag>, bStopSoundOnDeath, bStopSoundOnRemoved )"
"Summary: Play the specified looping sound alias on a tag of an entity"
"Module: Sound"
"CallOn: An entity"
"MandatoryArg: <alias> : Sound alias to loop"
"OptionalArg: <tag> : Tag on the entity to play sound on. If no tag is specified the entities origin will be used."
"OptionalArg: <bStopSoundOnDeath> : Defaults to true. If true, will stop the looping sound when self dies"
"OptionalArg: <bStopSoundOnRemoved> : Defaults to false. If true, will stop the looping sound when self is undefined without dying. Safty measure to avoid infinite looping sound"
"Example: vehicle thread play_loop_sound_on_tag( "engine_belt_run", "tag_engine" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
play_loop_sound_on_tag( alias, tag, bStopSoundOnDeath, bStopSoundOnRemoved )
{
	org = Spawn( "script_origin", ( 0, 0, 0 ) );
	org endon( "death" );
	
	if ( !isdefined( bStopSoundOnDeath ) )
		bStopSoundOnDeath = true;
	if ( bStopSoundOnDeath )
		thread delete_on_death( org );
		
	if ( !isdefined( bStopSoundOnRemoved ) )
		bStopSoundOnRemoved = false;
	if ( bStopSoundOnRemoved )
		thread delete_on_removed( org );
		
	if ( IsDefined( tag ) )
		org LinkTo( self, tag, ( 0, 0, 0 ), ( 0, 0, 0 ) );
	else
	{
		org.origin = self.origin;
		org.angles = self.angles;
		org LinkTo( self );
	}
// 	org endon( "death" );
	org PlayLoopSound( alias );
// 	PrintLn( "playing loop sound ", alias, " on entity at origin ", self.origin, " at ORIGIN ", org.origin );
	self waittill( "stop sound" + alias );
	org StopLoopSound( alias );
	org Delete();
}

delete_on_removed( ent )
{
	//self ==> the entity you want to wait to be undefined either by death or removed before deleting the ent
	ent endon( "death" );
	
	while( isdefined( self ) )
		wait 0.05;
	
	//self waittill( "death" );
	if ( IsDefined( ent ) )
		ent Delete();
}

save_friendlies()
{
	ai = GetAIArray( "allies" );
	game_characters = 0;
	for ( i = 0; i < ai.size; i++ )
	{
		if ( IsDefined( ai[ i ].script_friendname ) )
			continue;

// 		attachsize =
// 		PrintLn( "attachSize = ", self GetAttachSize() );

		game[ "character" + game_characters ] = ai[ i ] codescripts\character::save();
		game_characters++;
	}

	game[ "total characters" ] = game_characters;
}

 /*
 =============
///ScriptDocBegin
"Name: spawn_failed( <spawn> )"
"Summary: Checks to see if the spawned AI spawned correctly or had errors. Also waits until all spawn initialization is complete. Returns true or false."
"Module: AI"
"CallOn: "
"MandatoryArg: <spawn> : The actor that just spawned"
"Example: spawn_failed( level.price );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
spawn_failed( spawn )
{
	if ( !isalive( spawn ) )
		return true;
	if ( !isdefined( spawn.finished_spawning ) )
		spawn waittill_either( "finished spawning", "death" );

	if ( IsAlive( spawn ) )
		return false;

	return true;
}

spawn_setcharacter( data )
{
	codescripts\character::precache( data );

	self waittill( "spawned", spawn );
	if ( maps\_utility::spawn_failed( spawn ) )
		return;

	PrintLn( "Size is ", data[ "attach" ].size );
	spawn codescripts\character::new();
	spawn codescripts\character::load( data );
}

key_hint_print( message, binding )
{
	// Note that this will insert only the first bound key for the action
	IPrintLnBold( message, binding[ "key1" ] );
}

view_tag( tag )
{
	self endon( "death" );
	for ( ;; )
	{
		maps\_debug::drawTag( tag );
		wait( 0.05 );
	}
}

 /*
 =============
///ScriptDocBegin
"Name: assign_animtree( <animname> )"
"Summary: Assigns the level.scr_animtree for the given animname to self."
"Module: _Anim"
"OptionalArg: <animname> : You can optionally assign the animname for self at this juncture."
"Example: model = assign_animtree( "whatever" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

assign_animtree( animname )
{

/*
=============
///ScriptFieldDocBegin
"Name: .animname"
"Summary: animname"
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
	if ( IsDefined( animname ) )
		self.animname = animname;

	AssertEx( IsDefined( level.scr_animtree[ self.animname ] ), "There is no level.scr_animtree for animname " + self.animname );
	self UseAnimTree( level.scr_animtree[ self.animname ] );
}

/*
=============
///ScriptDocBegin
"Name: assign_model( <assign_model> )"
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
assign_model()
{
	AssertEx( IsDefined( level.scr_model[ self.animname ] ), "There is no level.scr_model for animname " + self.animname );

	if ( IsArray( level.scr_model[ self.animname ] ) )
	{
		randIndex = RandomInt( level.scr_model[ self.animname ].size );
		self SetModel( level.scr_model[ self.animname ][ randIndex ] );
	}
	else
		self SetModel( level.scr_model[ self.animname ] );
}

 /*
 =============
///ScriptDocBegin
"Name: spawn_anim_model( <animname>, <origin> )"
"Summary: Spawns a script model and gives it the animtree and model associated with that animname"
"Module: _Anim"
"MandatoryArg: <animname> : Name of the animname from this map_anim.gsc."
"OptionalArg: <origin> : Optional origin."
"Example: model = spawn_anim_model( "player_rappel" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

spawn_anim_model( animname, origin )
{
	if ( !isdefined( origin ) )
		origin = ( 0, 0, 0 );
	model = Spawn( "script_model", origin );
	model.animname = animname;
	model assign_animtree();
	model assign_model();
	return model;
}

 /*
 =============
///ScriptDocBegin
"Name: trigger_wait( <strName> , <strKey> )"
"Summary: Waits until a trigger with the specified key / value is triggered"
"Module: Trigger"
"CallOn: "
"MandatoryArg: <strName> : Name of the key on this trigger"
"MandatoryArg: <strKey> : Key on the trigger to use, example: "targetname" or "script_noteworthy""
"Example: trigger_wait( "player_in_building1", "targetname" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
trigger_wait( strName, strKey )
{
	eTrigger = GetEnt( strName, strKey );
	if ( !isdefined( eTrigger ) )
	{
		AssertMsg( "trigger not found: " + strName + " key: " + strKey );
		return;
	}
	eTrigger waittill( "trigger", eOther );
	level notify( strName, eOther );
	return eOther;
}
 /*
 =============
///ScriptDocBegin
"Name: trigger_wait_targetname( <strName> )"
"Summary: Waits until a trigger with the specified key / value is triggered"
"Module: Trigger"
"CallOn: "
"MandatoryArg: <strKey> : targetname key to waitfor"
"Example: trigger_wait_targetname( "player_in_building1" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

trigger_wait_targetname( strName )
{
	eTrigger = GetEnt( strName, "targetname" );
	if ( !isdefined( eTrigger ) )
	{
		AssertMsg( "trigger not found: " + strName + " targetname " );
		return;
	}
	eTrigger waittill( "trigger", eOther );
	level notify( strName, eOther );
	return eOther;
}

/*
=============
///ScriptDocBegin
"Name: set_flag_on_dead( <spawners> , <strFlag> )"
"Summary: the function will set the flag <strFlag> after the actors from <spawners> have spawned and then died "
"Module: AI"
"CallOn: "
"MandatoryArg: <spawners>: the array of spawners"
"MandatoryArg: <strFlag>: the flag to set"
"Example: set_flag_on_dead( spawners, "base_guys_dead" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_flag_on_dead( spawners, strFlag )
{
	thread set_flag_on_func_wait_proc( spawners, strFlag, ::waittill_dead, "set_flag_on_dead" );
}

/*
=============
///ScriptDocBegin
"Name: set_flag_on_dead_or_dying( <spawners> , <strFlag> )"
"Summary: the function will set the flag <strFlag> after the actors from <spawners> have spawned and then are dead or dying ( long death )."
"Module: AI"
"CallOn: "
"MandatoryArg: <spawners>: the array of spawners"
"MandatoryArg: <strFlag>: the flag to set"
"Example: set_flag_on_dead_or_dying( spawners, "base_guys_dead" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_flag_on_dead_or_dying( spawners, strFlag )
{
	thread set_flag_on_func_wait_proc( spawners, strFlag, ::waittill_dead_or_dying, "set_flag_on_dead_or_dying" );
}

/*
=============
///ScriptDocBegin
"Name: set_flag_on_spawned( <spawners> , <strFlag> )"
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
set_flag_on_spawned( spawners, strFlag )
{
	thread set_flag_on_func_wait_proc( spawners, strFlag, ::empty_func, "set_flag_on_spawned" );
}

empty_func( var )
{
	return;
}

set_flag_on_spawned_ai_proc( system, internal_flag )
{
	self waittill( "spawned", guy );
	if ( maps\_utility::spawn_failed( guy ) )
		return;

	system.ai[ system.ai.size ] = guy;

	self ent_flag_set( internal_flag );
}

set_flag_on_func_wait_proc( spawners, strFlag, waitfunc, internal_flag )
{
	system = SpawnStruct();
	system.ai = [];

	AssertEx( spawners.size, "spawners is empty" );

	foreach ( key, spawn in spawners )
		spawn ent_flag_init( internal_flag );

	array_thread( spawners, ::set_flag_on_spawned_ai_proc, system, internal_flag );

	foreach ( key, spawn in spawners )
		spawn ent_flag_wait( internal_flag );

	[[ waitfunc ]]( system.ai );
	flag_set( strFlag );
}

 /*
 =============
///ScriptDocBegin
"Name: set_flag_on_trigger( <eTrigger> , <strFlag> )"
"Summary: Calls flag_set to set the specified flag when the trigger is triggered"
"Module: Trigger"
"CallOn: "
"MandatoryArg: <eTrigger> : trigger entity to use"
"MandatoryArg: <strFlag> : name of the flag to set"
"Example: set_flag_on_trigger( trig, "player_is_outside" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
set_flag_on_trigger( eTrigger, strFlag )
{
	if ( !flag( strFlag ) )
	{
		eTrigger waittill( "trigger", eOther );
		flag_set( strFlag );
		return eOther;
	}
}

 /*
 =============
///ScriptDocBegin
"Name: set_flag_on_targetname_trigger( <flag> )"
"Summary: Sets the specified flag when a trigger with targetname < flag > is triggered."
"Module: Trigger"
"CallOn: "
"MandatoryArg: <flag> : name of the flag to set, and also the targetname of the trigger to use"
"Example:  set_flag_on_targetname_trigger( "player_is_outside" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
set_flag_on_targetname_trigger( msg )
{
	Assert( IsDefined( level.flag[ msg ] ) );
	if ( flag( msg ) )
		return;

	trigger = GetEnt( msg, "targetname" );
	trigger waittill( "trigger" );
	flag_set( msg );
}

 /*
 =============
///ScriptDocBegin
"Name: is_in_array( <aeCollection> , <eFindee> )"
"Summary: Returns true if < eFindee > is an entity in array < aeCollection > . False if it is not. "
"Module: Array"
"CallOn: "
"MandatoryArg: <aeCollection> : array of entities to search through"
"MandatoryArg: <eFindee> : entity to check if it's in the array"
"Example: qBool = is_in_array( eTargets, vehicle1 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
is_in_array( aeCollection, eFindee )
{
	for ( i = 0; i < aeCollection.size; i++ )
	{
		if ( aeCollection[ i ] == eFindee )
			return( true );
	}

	return( false );
}

 /*
 =============
///ScriptDocBegin
"Name: waittill_dead( <guys> , <num> , <timeoutLength> )"
"Summary: Waits until all the AI in array < guys > are dead."
"Module: AI"
"CallOn: "
"MandatoryArg: <guys> : Array of actors to wait until dead"
"OptionalArg: <num> : Number of guys that must die for this function to continue"
"OptionalArg: <timeoutLength> : Number of seconds before this function times out and continues"
"Example: waittill_dead( GetAIArray( "axis" ) );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
waittill_dead( guys, num, timeoutLength )
{
	// verify the living - ness of the ai
	/#
	allAlive = true;
	foreach ( member in guys )
	{
		if ( IsAlive( member ) )
			continue;
		allAlive = false;
		break;
	}
	AssertEx( allAlive, "Waittill_Dead was called with dead or removed AI in the array, meaning it will never pass." );
	if ( !allAlive )
	{
		newArray = [];
		foreach ( member in guys )
		{
			if ( IsAlive( member ) )
				newArray[ newArray.size ] = member;
		}
		guys = newArray;
	}
	#/

	ent = SpawnStruct();
	if ( IsDefined( timeoutLength ) )
	{
		ent endon( "thread_timed_out" );
		ent thread waittill_dead_timeout( timeoutLength );
	}

	ent.count = guys.size;
	if ( IsDefined( num ) && num < ent.count )
		ent.count = num;
	array_thread( guys, ::waittill_dead_thread, ent );

	while ( ent.count > 0 )
		ent waittill( "waittill_dead guy died" );
}

 /*
 =============
///ScriptDocBegin
"Name: waittill_dead_or_dying( <guys> , <num> , <timeoutLength> )"
"Summary: Similar to waittill_dead(). Waits until all the AI in array < guys > are dead OR dying (long deaths)."
"Module: AI"
"CallOn: "
"MandatoryArg: <guys> : Array of actors to wait until dead or dying"
"OptionalArg: <num> : Number of guys that must die or be dying for this function to continue"
"OptionalArg: <timeoutLength> : Number of seconds before this function times out and continues"
"Example: waittill_dead_or_dying( GetAIArray( "axis" ) );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
waittill_dead_or_dying( guys, num, timeoutLength )
{
	// verify the living - ness and healthy - ness of the ai
	newArray = [];
	foreach ( member in guys )
	{
		if ( IsAlive( member ) && !member.ignoreForFixedNodeSafeCheck )
			newArray[ newArray.size ] = member;
	}
	guys = newArray;

	ent = SpawnStruct();
	if ( IsDefined( timeoutLength ) )
	{
		ent endon( "thread_timed_out" );
		ent thread waittill_dead_timeout( timeoutLength );
	}

	ent.count = guys.size;

	// optional override on count
	if ( IsDefined( num ) && num < ent.count )
		ent.count = num;

	array_thread( guys, ::waittill_dead_or_dying_thread, ent );

	while ( ent.count > 0 )
		ent waittill( "waittill_dead_guy_dead_or_dying" );
}

waittill_dead_thread( ent )
{
	self waittill( "death" );
	ent.count--;
	ent notify( "waittill_dead guy died" );
}

waittill_dead_or_dying_thread( ent )
{
	self waittill_either( "death", "pain_death" );
	ent.count--;
	ent notify( "waittill_dead_guy_dead_or_dying" );
}

waittill_dead_timeout( timeoutLength )
{
	wait( timeoutLength );
	self notify( "thread_timed_out" );
}

waittill_aigroupcleared( aigroup )
{
	while ( level._ai_group[ aigroup ].spawnercount || level._ai_group[ aigroup ].aicount )
		wait( 0.25 );
}

waittill_aigroupcount( aigroup, count )
{
	while ( level._ai_group[ aigroup ].spawnercount + level._ai_group[ aigroup ].aicount > count )
		wait( 0.25 );
}

get_ai_group_count( aigroup )
{
	return( level._ai_group[ aigroup ].spawnercount + level._ai_group[ aigroup ].aicount );
}

get_ai_group_sentient_count( aigroup )
{
	return( level._ai_group[ aigroup ].aicount );
}

get_ai_group_ai( aigroup )
{
	aiSet = [];
	for ( index = 0; index < level._ai_group[ aigroup ].ai.size; index++ )
	{
		if ( !isAlive( level._ai_group[ aigroup ].ai[ index ] ) )
			continue;

		aiSet[ aiSet.size ] = level._ai_group[ aigroup ].ai[ index ];
	}

	return( aiSet );
}

 /*
 =============
///ScriptDocBegin
"Name: waittill_notetrack_or_damage( <notetrack> )"
"Summary: Waits until the entity hits a certain notetrack or is damaged or killed"
"Module: AI"
"CallOn: An AI"
"MandatoryArg: <notetrack> : the notetrack to wait for"
"Example: self waittill_notetrack_or_damage( "bodyfall large" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

waittill_notetrack_or_damage( notetrack )
{
	self endon( "damage" );
	self endon( "death" );
	self waittillmatch( "single anim", notetrack );
}

 /*
 =============
///ScriptDocBegin
"Name: get_living_ai( <name> , <type> )"
"Summary: Returns single spawned ai in the level of <name> and <type>. Error if used on more than one ai with same name and type "
"Module: AI"
"CallOn: "
"MandatoryArg: <name> : the value of the targetname or script_noteworthy of the ai"
"MandatoryArg: <type> : valid types are targetname and script_noteworthy"
"Example: patroller = get_living_ai( "patrol", "script_noteworthy" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_living_ai( name, type )
{
	array = get_living_ai_array( name, type );
	if ( array.size > 1 )
	{
		AssertMsg( "get_living_ai used for more than one living ai of type " + type + " called " + name + "." );
		return undefined;
	}
	return array[ 0 ];
}

 /*
 =============
///ScriptDocBegin
"Name: get_living_ai_array( <name> , <type> )"
"Summary: Returns array of spawned ai in the level of <name> and <type> "
"Module: AI"
"CallOn: "
"MandatoryArg: <name> : the value of the targetname or script_noteworthy of the ai"
"MandatoryArg: <type> : valid types are targetname and script_noteworthy"
"Example: patrollers = get_living_ai_array( "patrol", "script_noteworthy" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_living_ai_array( name, type )
{
	ai = GetAISpeciesArray( "all", "all" );

	array = [];
	foreach ( actor in ai )
	{
		if ( !isalive( actor ) )
			continue;

		switch( type )
		{
			case "targetname":{
				if ( IsDefined( actor.targetname ) && actor.targetname == name )
					array[ array.size ] = actor;
			}break;
		 	case "script_noteworthy":{
				if ( IsDefined( actor.script_noteworthy ) && actor.script_noteworthy == name )
					array[ array.size ] = actor;
			}break;
		}
	}
	return array;
}
 /*
 =============
///ScriptDocBegin
"Name: get_vehicle( <name> , <type> )"
"Summary: Returns the vehicle spawned from the SHIFT-V radient menu of <name> and <type> "
"Module: Vehicle"
"CallOn: "
"MandatoryArg: <name> : the value of the targetname or script_noteworthy of the vehicle"
"MandatoryArg: <type> : valid types are targetname and script_noteworthy"
"Example: patrollers = get_vehicle( "heli_1", "script_noteworthy" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_vehicle( name, type )
{
	Assert( IsDefined( name ) );
	Assert( IsDefined( type ) );
	array = get_vehicle_array( name, type );
	if ( !array.size )
		return undefined;

	AssertEx( array.size == 1, "tried to get_vehicle() on vehicles with key-pair: " + name + "," + type );
	return array[ 0 ];
}

 /*
 =============
///ScriptDocBegin
"Name: get_vehicle_array( <name> , <type> )"
"Summary: Returns the vehicles spawned from the SHIFT-V radient menu of <name> and <type> "
"Module: Vehicle"
"CallOn: "
"MandatoryArg: <name> : the value of the targetname or script_noteworthy of the vehicle"
"MandatoryArg: <type> : valid types are targetname and script_noteworthy"
"Example: helis = get_vehicle_array( "tower_helis", "script_noteworthy" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_vehicle_array( name, type )
{
	array = GetEntArray( name, type );
	vehicle = [];

	merge_array = [];

	foreach ( object in array )
	{
		if ( object.code_classname != "script_vehicle" )
			continue;
		merge_array[ 0 ] = object;
		//since vehicles lose their targetname return the last vehicle spawned from the spawner.
		if ( IsSpawner( object ) )
		{
			if ( IsDefined( object.last_spawned_vehicle ) )
			{
				merge_array[ 0 ] = object.last_spawned_vehicle;
				vehicle = array_merge( vehicle, merge_array );// least tricky way for me to do this.
			}
			continue;
		}
		vehicle = array_merge( vehicle, merge_array );// least tricky way for me to do this.
	}
	return vehicle;
}
 /*
 =============
///ScriptDocBegin
"Name: get_living_aispecies( <name> , <type>, <breed> )"
"Summary: Returns single spawned ai in the level of <name> and <type>. Error if used on more than one ai with same name and type "
"Module: AI"
"CallOn: "
"MandatoryArg: <name> : the value of the targetname or script_noteworthy of the ai"
"MandatoryArg: <type> : valid types are targetname and script_noteworthy"
"OptionalArg: <bread> : the breadof spieces, if none is given, defaults to 'all' "
"Example: patroller = get_living_aispecies( "patrol", "script_noteworthy", "dog" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_living_aispecies( name, type, breed )
{
	array = get_living_ai_array( name, type, breed );
	if ( array.size > 1 )
	{
		AssertMsg( "get_living_aispecies used for more than one living ai of type " + type + " called " + name + "." );
		return undefined;
	}
	return array[ 0 ];
}

 /*
 =============
///ScriptDocBegin
"Name: get_living_aispecies_array( <name> , <type>, <breed> )"
"Summary: Returns array of spawned ai of any speices in the level of <name>, <type>, and <breed> "
"Module: AI"
"CallOn: "
"MandatoryArg: <name> : the value of the targetname or script_noteworthy of the ai"
"MandatoryArg: <type> : valid types are targetname and script_noteworthy"
"OptionalArg: <bread> : the breadof spieces, if none is given, defaults to 'all' "
"Example: patrollers = get_living_aispecies_array( "patrol", "script_noteworthy", "dog" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_living_aispecies_array( name, type, breed )
{
	if ( !isdefined( breed ) )
		breed = "all";

	ai = GetAISpeciesArray( "allies", breed );
	ai = array_combine( ai, GetAISpeciesArray( "axis", breed ) );

	array = [];
	for ( i = 0; i < ai.size; i++ )
	{
		switch( type )
		{
			case "targetname":{
				if ( IsDefined( ai[ i ].targetname ) && ai[ i ].targetname == name )
					array[ array.size ] = ai[ i ];
			}break;
		 	case "script_noteworthy":{
				if ( IsDefined( ai[ i ].script_noteworthy ) && ai[ i ].script_noteworthy == name )
					array[ array.size ] = ai[ i ];
			}break;
		}
	}
	return array;
}

// Creates an event based on this message if none exists, and sets it to true after the delay.
gather_delay_proc( msg, delay )
{
	if ( IsDefined( level.gather_delay[ msg ] ) )
	{
		if ( level.gather_delay[ msg ] )
		{
			wait( 0.05 );
			if ( IsAlive( self ) )
				self notify( "gather_delay_finished" + msg + delay );
			return;
		}

		level waittill( msg );
		if ( IsAlive( self ) )
			self notify( "gather_delay_finished" + msg + delay );
		return;
	}

	level.gather_delay[ msg ] = false;
	wait( delay );
	level.gather_delay[ msg ] = true;
	level notify( msg );
	if ( IsAlive( self ) )
		self notify( "gather_delay_finished" + msg + delay );
}

gather_delay( msg, delay )
{
	thread gather_delay_proc( msg, delay );
	self waittill( "gather_delay_finished" + msg + delay );
}

set_environment( env )
{
	animscripts\utility::setEnv( env );
}

death_waiter( notifyString )
{
	self waittill( "death" );
	level notify( notifyString );
}

getchar( num )
{
	if ( num == 0 )
		return "0";
	if ( num == 1 )
		return "1";
	if ( num == 2 )
		return "2";
	if ( num == 3 )
		return "3";
	if ( num == 4 )
		return "4";
	if ( num == 5 )
		return "5";
	if ( num == 6 )
		return "6";
	if ( num == 7 )
		return "7";
	if ( num == 8 )
		return "8";
	if ( num == 9 )
		return "9";
}

getlinks_array( array, linkMap )// don't pass stuff through as an array of struct.linkname[] but only linkMap[]
{
	ents = [];
	for ( j = 0; j < array.size; j++ )
	{
		node = array[ j ];
		script_linkname = node.script_linkname;
		if ( !isdefined( script_linkname ) )
			continue;
		if ( !isdefined( linkMap[ script_linkname ] ) )
			continue;
		ents[ ents.size ] = node;
	}
	return ents;
}

// Adds only things that are new to the array.
// Requires the arrays to be of node with script_linkname defined.
/*
=============
///ScriptDocBegin
"Name: array_merge_links( <array1> , <array2> )"
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
array_merge_links( array1, array2 )
{
	if ( !array1.size )
		return array2;
	if ( !array2.size )
		return array1;

	linkMap = [];

	for ( i = 0; i < array1.size; i++ )
	{
		node = array1[ i ];
		linkMap[ node.script_linkName ] = true;
	}

	for ( i = 0; i < array2.size; i++ )
	{
		node = array2[ i ];
		if ( IsDefined( linkMap[ node.script_linkName ] ) )
			continue;
		linkMap[ node.script_linkName ] = true;
		array1[ array1.size ] = node;
	}

	return array1;
}

 /*
 =============
///ScriptDocBegin
"Name: array_merge( <array1> , <array2> )"
"Summary: Combines the two arrays and returns the resulting array. Adds only things that are new to the array, no duplicates."
"Module: Array"
"CallOn: "
"MandatoryArg: <array1> : first array"
"MandatoryArg: <array2> : second array"
"Example: combinedArray = array_merge( array1, array2 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
array_merge( array1, array2 )// adds only things that are new to the array
{
	if ( array1.size == 0 )
		return array2;
	if ( array2.size == 0 )
		return array1;
	newarray = array1;
	foreach ( array2_ent in array2 )
	{
		foundmatch = false;

		foreach ( array1_ent in array1 )
		{
			if ( array1_ent == array2_ent )
			{
				foundmatch = true;
				break;
			}
		}
		if ( foundmatch )
			continue;
		else
			newarray[ newarray.size ] = array2_ent;
	}
	return newarray;
}

 /*
 =============
///ScriptDocBegin
"Name: array_exclude( <array> , <arrayExclude> )"
"Summary: Returns an array excluding all members of < arrayExclude > "
"Module: Array"
"CallOn: "
"MandatoryArg: <array> : Array containing all items"
"MandatoryArg: <arrayExclude> : Arary containing all items to remove"
"Example: newArray = array_exclude( array1, array2 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
array_exclude( array, arrayExclude )// returns "array" minus all members of arrayExclude
{
	newarray = array;
	for ( i = 0; i < arrayExclude.size; i++ )
	{
		if ( is_in_array( array, arrayExclude[ i ] ) )
			newarray = array_remove( newarray, arrayExclude[ i ] );
	}

	return newarray;
}

/*
=============
///ScriptDocBegin
"Name: array_compare( <array1> , <array2> )"
"Summary: checks whether 2 arrays are equal.  Returns true if they are, false if they are not"
"Module: Array"
"CallOn: "
"MandatoryArg: <array1>: the first array to compare "
"MandatoryArg: <array2>: the second array to compare "
"Example:  if( array_compare( array1, array2 ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_compare( array1, array2 )
{
	if ( array1.size != array2.size )
		return false;

	foreach ( key, member in array1 )
	{
		if ( !isdefined( array2[ key ] ) )
			return false;

		member2 = array2[ key ];

		if ( member2 != member )
			return false;
	}

	return true;
}

/*
=============
///ScriptDocBegin
"Name: array_contains( <array> , <compare> )"
"Summary: Checks whether an item is in the array or not."
"Module: Array"
"CallOn: "
"MandatoryArg: <array>: The array to search."
"MandatoryArg: <compare>: The item to see if it exists in the array"
"Example:  if( arrray_contains( array, important_item ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_contains( array, compare )
{
	if ( array.size <= 0 )
		return false;

	foreach ( member in array )
	{
		if ( member == compare )
			return true;
	}

	return false;
}

/*
=============
///ScriptDocBegin
"Name: getLinkedVehicleNodes()"
"Summary: Returns an array of vehicle nodes that SELF is linked to"
"Module: Utility"
"CallOn: An entity that links to vehicle nodes"
"Example: spawners = heli get_linked_ents()"
"SPMP: both"
///ScriptDocEnd
=============
*/
getLinkedVehicleNodes()
{
	array = [];

	if ( IsDefined( self.script_linkTo ) )
	{
		linknames = get_links();
		foreach ( name in linknames )
		{
			entities = GetVehicleNodeArray( name, "script_linkname" );
			array = array_combine( array, entities );
		}
	}

	return array;
}




 /*
 =============
///ScriptDocBegin
"Name: draw_line( <org1> , <org2> , <r> , <g> , <b> )"
"Summary: Draws a line from < org1 > to < org2 > in the specified color forever"
"Module: Debug"
"CallOn: "
"MandatoryArg: <org1> : starting origin for the line"
"MandatoryArg: <org2> : ending origin for the line"
"MandatoryArg: <r> : red color value( 0 to 1 )"
"MandatoryArg: <g> : green color value( 0 to 1 )"
"MandatoryArg: <b> : blue color value( 0 to 1 )"
"Example: thread draw_line( level.player.origin, vehicle.origin, 1, 0, 0 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
draw_line( org1, org2, r, g, b )
{
	while ( 1 )
	{
		Line( org1, org2, ( r, g, b ), 1 );
		wait .05;
	}

}

 /*
 =============
///ScriptDocBegin
"Name: draw_line_to_ent_for_time( <org1> , <ent> , <r> , <g> , <b> , <timer> )"
"Summary: Draws a line from < org1 > to < ent > origin in the specified color for the specified duration. Updates to the entities origin each frame."
"Module: Debug"
"CallOn: "
"MandatoryArg: <org1> : starting origin for the line"
"MandatoryArg: <ent> : entity to draw line to"
"MandatoryArg: <r> : red color value( 0 to 1 )"
"MandatoryArg: <g> : green color value( 0 to 1 )"
"MandatoryArg: <b> : blue color value( 0 to 1 )"
"MandatoryArg: <timer> : time in seconds the line should last"
"Example: thread draw_line_to_ent_for_time( level.player.origin, vehicle, 1, 0, 0, 10.0 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
draw_line_to_ent_for_time( org1, ent, r, g, b, timer )
{
	timer = GetTime() + ( timer * 1000 );
	while ( GetTime() < timer )
	{
		Line( org1, ent.origin, ( r, g, b ), 1 );
		wait .05;
		if ( !isdefined( ent ) || !isdefined( ent.origin ) )
			return;
	}

}

/*
=============
///ScriptDocBegin
"Name: draw_line_from_ent_for_time( <ent> , <org> , <r> , <g> , <b> , <timer> )"
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
draw_line_from_ent_for_time( ent, org, r, g, b, timer )
{
	draw_line_to_ent_for_time( org, ent, r, g, b, timer );
}

 /*
 =============
///ScriptDocBegin
"Name: draw_line_from_ent_to_ent_for_time( <ent1> , <ent2> , <r> , <g> , <b> , <timer> )"
"Summary: Draws a line from one entity origin to another entity origin in the specified color for the specified duration. Updates to the entities origin each frame."
"Module: Debug"
"CallOn: "
"MandatoryArg: <ent1> : entity to draw line from"
"MandatoryArg: <ent2> : entity to draw line to"
"MandatoryArg: <r> : red color value( 0 to 1 )"
"MandatoryArg: <g> : green color value( 0 to 1 )"
"MandatoryArg: <b> : blue color value( 0 to 1 )"
"MandatoryArg: <timer> : time in seconds the line should last"
"Example: thread draw_line_from_ent_to_ent_for_time( level.player, vehicle, 1, 0, 0, 10.0 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
draw_line_from_ent_to_ent_for_time( ent1, ent2, r, g, b, timer )
{
	ent1 endon( "death" );
	ent2 endon( "death" );

	timer = GetTime() + ( timer * 1000 );
	while ( GetTime() < timer )
	{
		Line( ent1.origin, ent2.origin, ( r, g, b ), 1 );
		wait .05;
	}

}

 /*
 =============
///ScriptDocBegin
"Name: draw_line_from_ent_to_ent_until_notify( <ent1> , <ent2> , <r> , <g> , <b> , <notifyEnt> , <notifyString> )"
"Summary: Draws a line from one entity origin to another entity origin in the specified color until < notifyEnt > is notified < notifyString > . Updates to the entities origin each frame."
"Module: Debug"
"CallOn: "
"MandatoryArg: <ent1> : entity to draw line from"
"MandatoryArg: <ent2> : entity to draw line to"
"MandatoryArg: <r> : red color value( 0 to 1 )"
"MandatoryArg: <g> : green color value( 0 to 1 )"
"MandatoryArg: <b> : blue color value( 0 to 1 )"
"MandatoryArg: <notifyEnt> : entity that waits for the notify"
"MandatoryArg: <notifyString> : notify string that will make the line stop being drawn"
"Example: thread draw_line_from_ent_to_ent_until_notify( level.player, guy, 1, 0, 0, guy, "anim_on_tag_done" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
draw_line_from_ent_to_ent_until_notify( ent1, ent2, r, g, b, notifyEnt, notifyString )
{
	Assert( IsDefined( notifyEnt ) );
	Assert( IsDefined( notifyString ) );

	ent1 endon( "death" );
	ent2 endon( "death" );

	notifyEnt endon( notifyString );

	while ( 1 )
	{
		Line( ent1.origin, ent2.origin, ( r, g, b ), 0.05 );
		wait .05;
	}

}

 /*
 =============
///ScriptDocBegin
"Name: draw_line_until_notify( <org1> , <org2> , <r> , <g> , <b> , <notifyEnt> , <notifyString> )"
"Summary: Draws a line from < org1 > to < org2 > in the specified color until < notifyEnt > is notified < notifyString > "
"Module: Debug"
"CallOn: "
"MandatoryArg: <org1> : starting origin for the line"
"MandatoryArg: <org2> : ending origin for the line"
"MandatoryArg: <r> : red color value( 0 to 1 )"
"MandatoryArg: <g> : green color value( 0 to 1 )"
"MandatoryArg: <b> : blue color value( 0 to 1 )"
"MandatoryArg: <notifyEnt> : entity that waits for the notify"
"MandatoryArg: <notifyString> : notify string that will make the line stop being drawn"
"Example: thread draw_line_until_notify( self.origin, targetLoc, 1, 0, 0, self, "stop_drawing_line" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
draw_line_until_notify( org1, org2, r, g, b, notifyEnt, notifyString )
{
	Assert( IsDefined( notifyEnt ) );
	Assert( IsDefined( notifyString ) );

	notifyEnt endon( notifyString );

	while ( 1 )
	{
		draw_line_for_time( org1, org2, r, g, b, 0.05 );
	}
}

 /*
 =============
///ScriptDocBegin
"Name: draw_line_from_ent_to_vec_for_time( <ent> , <vec> , <length> , <r> , <g> , <b> , <timer> )"
"Summary: Draws a line from < org1 > to < ent > origin in the specified color for the specified duration. Updates to the entities origin each frame."
"Module: Debug"
"CallOn: "
"MandatoryArg: <ent> : entity to draw line to"
"MandatoryArg: <vec> : vector to draw the line at"
"MandatoryArg: <length> : length of the vector line"
"MandatoryArg: <r> : red color value( 0 to 1 )"
"MandatoryArg: <g> : green color value( 0 to 1 )"
"MandatoryArg: <b> : blue color value( 0 to 1 )"
"MandatoryArg: <timer> : time in seconds the line should last"
"Example: thread draw_line_from_ent_to_vec_for_time( vehicle, ( 0, 1, 0 ), 10, 1, 0, 0, 10.0 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
draw_line_from_ent_to_vec_for_time( ent, vec, length, r, g, b, timer )
{
	timer = GetTime() + ( timer * 1000 );
	vec *= length;
	while ( GetTime() < timer )
	{
		Line( ent.origin, ent.origin + vec, ( r, g, b ), 1 );
		wait .05;
		if ( !isdefined( ent ) || !isdefined( ent.origin ) )
			return;
	}
}

 /*
 =============
///ScriptDocBegin
"Name: draw_circle_until_notify( <center> , <radius> , <r> , <g> , <b> , <notifyEnt> , <notifyString> )"
"Summary: Draws a circle at < center > with < radius > in the specified color until < notifyEnt > is notified < notifyString > "
"Module: Debug"
"CallOn: "
"MandatoryArg: <center> : origin center of the circle"
"MandatoryArg: <radius> : radius of the circle to draw"
"MandatoryArg: <r> : red color value( 0 to 1 )"
"MandatoryArg: <g> : green color value( 0 to 1 )"
"MandatoryArg: <b> : blue color value( 0 to 1 )"
"MandatoryArg: <notifyEnt> : entity that waits for the notify"
"MandatoryArg: <notifyString> : notify string that will make the line stop being drawn"
"Example: thread draw_circle_until_notify( self.origin, self.radius, 1, 0, 0, self, "stop_drawing_circle" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
draw_circle_until_notify( center, radius, r, g, b, notifyEnt, notifyString )
{
	circle_sides = 16;

	angleFrac = 360 / circle_sides;

	// Z circle
	circlepoints = [];
	for ( i = 0; i < circle_sides; i++ )
	{
		angle = ( angleFrac * i );
		xAdd = Cos( angle ) * radius;
		yAdd = Sin( angle ) * radius;
		x = center[ 0 ] + xAdd;
		y = center[ 1 ] + yAdd;
		z = center[ 2 ];
		circlepoints[ circlepoints.size ] = ( x, y, z );
	}
	thread draw_circle_lines_until_notify( circlepoints, r, g, b, notifyEnt, notifyString );
	/*
	// X circle
	circlepoints = [];
	for ( i = 0 ; i < circle_sides ; i++ )
	{
		angle = ( angleFrac * i );
		xAdd = Cos( angle ) * radius;
		yAdd = Sin( angle ) * radius;
		x = center[ 0 ];
		y = center[ 1 ] + xAdd;
		z = center[ 2 ] + yAdd;
		circlepoints[ circlepoints.size ] = ( x, y, z );
	}
	thread debug_circle_drawlines( circlepoints, 5.0, ( 1, 0, 0 ), center );

	// Y circle
	circlepoints = [];
	for ( i = 0 ; i < circle_sides ; i++ )
	{
		angle = ( angleFrac * i );
		xAdd = Cos( angle ) * radius;
		yAdd = Sin( angle ) * radius;
		x = center[ 0 ] + yAdd;
		y = center[ 1 ];
		z = center[ 2 ] + xAdd;
		circlepoints[ circlepoints.size ] = ( x, y, z );
	}
	thread debug_circle_drawlines( circlepoints, 5.0, ( 1, 0, 0 ), center );
	*/
}

draw_circle_lines_until_notify( circlepoints, r, g, b, notifyEnt, notifyString )
{
	for ( i = 0; i < circlepoints.size; i++ )
	{
		start = circlepoints[ i ];
		if ( i + 1 >= circlepoints.size )
			end = circlepoints[ 0 ];
		else
			end = circlepoints[ i + 1 ];

		thread draw_line_until_notify( start, end, r, g, b, notifyEnt, notifyString );
	}
}

clear_enemy_passthrough()
{
	self notify( "enemy" );
	self ClearEnemy();
}

 /*
 =============
///ScriptDocBegin
"Name: battlechatter_off( <team> )"
"Summary: Disable battlechatter for the specified team"
"Module: Battlechatter"
"CallOn: "
"MandatoryArg: <team> : team to disable battlechatter on"
"Example: battlechatter_off( "allies" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
battlechatter_off( team )
{
	level notify( "battlechatter_off_thread" );

	animscripts\battlechatter::bcs_setup_chatter_toggle_array();

	if ( IsDefined( team ) )
	{
		set_battlechatter_variable( team, false );
		soldiers = GetAIArray( team );
	}
	else
	{
		foreach ( team in anim.teams )
		{
			set_battlechatter_variable( team, false );
		}

		soldiers = GetAIArray();
	}

	if ( !isDefined( anim.chatInitialized ) || !anim.chatInitialized )
		return;

	for ( index = 0; index < soldiers.size; index++ )
		soldiers[ index ].battlechatter = false;

	for ( index = 0; index < soldiers.size; index++ )
	{
		soldier = soldiers[ index ];
		if ( !isalive( soldier ) )
			continue;

		if ( !soldier.chatInitialized )
			continue;

		if ( !soldier.isSpeaking )
			continue;

		soldier wait_until_done_speaking();
	}

	speakDiff = GetTime() - anim.lastTeamSpeakTime[ "allies" ];

	if ( speakDiff < 1500 )
		wait( speakDiff / 1000 );

	if ( IsDefined( team ) )
		level notify( team + " done speaking" );
	else
		level notify( "done speaking" );
}

 /*
 =============
///ScriptDocBegin
"Name: battlechatter_on( <team> )"
"Summary: Enable battlechatter for the specified team"
"Module: Battlechatter"
"CallOn: "
"MandatoryArg: <team> : team to enable battlechatter on"
"Example: battlechatter_on( "allies" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
battlechatter_on( team )
{
	thread battlechatter_on_thread( team );
}

battlechatter_on_thread( team )
{
	level endon( "battlechatter_off_thread" );

	animscripts\battlechatter::bcs_setup_chatter_toggle_array();

	while ( !IsDefined( anim.chatInitialized ) )
	{
		wait( 0.05 );
	}

	flag_set( "battlechatter_on_thread_waiting" );

	// buffer time
	wait( 1.5 );

	flag_clear( "battlechatter_on_thread_waiting" );

	if ( IsDefined( team ) )
	{
		set_battlechatter_variable( team, true );
		soldiers = GetAIArray( team );
	}
	else
	{
		foreach ( team in anim.teams )
		{
			set_battlechatter_variable( team, true );
		}
		soldiers = GetAIArray();
	}

	for ( index = 0; index < soldiers.size; index++ )
		soldiers[ index ] set_battlechatter( true );
}

/*
=============
///ScriptDocBegin
"Name: set_battlechatter( <state> )"
"Summary: Turns an AI's battlechatter on/off.  Will be overridden if a spawner's .script_bcdialog is set to 0."
"Module: Battlechatter"
"CallOn: An AI"
"MandatoryArg: <state>: True/false, describes whether battlechatter should be on or off for this AI"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_battlechatter( state )
{
	if ( !anim.chatInitialized )
		return;

	if ( self.type == "dog" )
		return;

	if ( state )
	{
		if ( IsDefined( self.script_bcdialog ) && !self.script_bcdialog )
			self.battlechatter = false;
		else
			self.battlechatter = true;
	}
	else
	{
		self.battlechatter = false;

		if ( IsDefined( self.isSpeaking ) && self.isSpeaking )
			self waittill( "done speaking" );
	}
}
/*
=============
///ScriptDocBegin
"Name: set_team_bcvoice( <team>, <newvoice> )"
"Summary: Changes all the battlechatter voices for a certain team.  Useful for switching between loud/stealth chatter."
"Module: Battlechatter"
"CallOn: "
"MandatoryArg: <team>: Allies/Axis/Team3, which team should change voices"
"MandatoryArg: <newvoice>: What voice should they use.  See 'anim.countryIDs' keys for valid voices"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_team_bcvoice( team, newvoice )
{
	if ( !anim.chatInitialized )
		return;
		
	supported_voicetypes = GetArrayKeys( anim.countryIDs );
	in_supported_voicetypes = array_contains( supported_voicetypes, newvoice );
	assertEx( in_supported_voicetypes, "Tried to change ai's voice to " + newvoice + " but that voicetype is not supported!" );
	
	if ( !in_supported_voicetypes )
		return;
		
	allies = GetAIArray( team );	
	foreach( ai in allies )
		ai set_ai_bcvoice( newvoice );
}

/*
=============
///ScriptDocBegin
"Name: set_ai_bcvoice( <newvoice> )"
"Summary: Changes all the battlechatter voices for a single ai.  Useful for switching between loud/stealth chatter."
"Module: Battlechatter"
"CallOn: an AI"
"MandatoryArg: <newvoice>: What voice should they use.  See 'anim.countryIDs' keys for valid voices"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_ai_bcvoice( newvoice )
{
	if ( !anim.chatInitialized )
		return;
		
	supported_voicetypes = GetArrayKeys( anim.countryIDs );
	in_supported_voicetypes = array_contains( supported_voicetypes, newvoice );
	assertEx( in_supported_voicetypes, "Tried to change ai's voice to " + newvoice + " but that voicetype is not supported!" );
	
	if ( !in_supported_voicetypes )
		return;

	if ( self.type == "dog" )
		return;

	if ( IsDefined( self.isSpeaking ) && self.isSpeaking )
	{
		self waittill( "done speaking" );
		wait( 0.1 );
	}
	
	self animscripts\battlechatter_ai::removeFromSystem();
	wait( 0.1 ); // give ai time to remove himself from the system
	self.voice = newvoice;
	self animscripts\battlechatter_ai::addToSystem();
}

/*
=============
///ScriptDocBegin
"Name: flavorbursts_on( <team> )"
"Summary: Gives all the AIs on a team the ability to play flavor burst transmissions.  (Only US allies can use FBTs.)  Note: if the battlechatter system is not working, the flavorbursts will not work even if the AIs have this set on them."
"Module: Battlechatter"
"CallOn: "
"OptionalArg: <team>: which team? Usually, only allies have flavorbursts."
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
flavorbursts_on( team )
{
	thread set_flavorbursts_team_state( true, team );
}

/*
=============
///ScriptDocBegin
"Name: flavorbursts_off( <team> )"
"Summary: Removes the ability to play flavor burst transmissions from all AIs on a team.  (Only US allies can use FBTs.)"
"Module: Battlechatter"
"CallOn: "
"OptionalArg: <team>: which team? Usually, only allies have flavorbursts."
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
flavorbursts_off( team )
{
	thread set_flavorbursts_team_state( false, team );
}

set_flavorbursts_team_state( state, team )
{
	if ( !IsDefined( team ) )
	{
		team = "allies";
	}

	if ( !anim.chatInitialized )
	{
		return;
	}

	// buffer time
	wait( 1.5 );

	level.flavorbursts[ team ] = state;

	guys = [];
	guys = GetAIArray( team );

	array_thread( guys, ::set_flavorbursts, state );
}

/*
=============
///ScriptDocBegin
"Name: set_flavorbursts( <state> )"
"Summary: Turns battlechatter flavor burst transmissions for an AI on or off"
"Module: Entity"
"CallOn: An AI"
"MandatoryArg: <state> "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_flavorbursts( state )
{
	self.flavorbursts = state;
}

/*
=============
///ScriptDocBegin
"Name: friendlyfire_warnings_off()"
"Summary: Disables player-originated friendly fire warnings for all allied AI."
"Module: Entity"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
friendlyfire_warnings_off()
{
	ais = GetAiArray( "allies" );

	foreach( guy in ais )
	{
		if( IsAlive( guy ) )
		{
			guy set_friendlyfire_warnings( false );
		}
	}

	level.friendlyfire_warnings = false;
}

/*
=============
///ScriptDocBegin
"Name: friendlyfire_warnings_on()"
"Summary: Enables player-originated friendly fire warnings for all allied AI."
"Module: Entity"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
friendlyfire_warnings_on()
{
	ais = GetAiArray( "allies" );

	foreach( guy in ais )
	{
		if( IsAlive( guy ) )
		{
			guy set_friendlyfire_warnings( true );
		}
	}

	level.friendlyfire_warnings = true;
}

/*
=============
///ScriptDocBegin
"Name: set_friendlyfire_warnings( <state> )"
"Summary: Turns player-originated friendly fire warnings for an AI on or off"
"Module: Entity"
"CallOn: An AI"
"MandatoryArg: <state> "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_friendlyfire_warnings( state )
{
	if( state )
	{
		self.friendlyfire_warnings_disable = undefined;
	}
	else
	{
		self.friendlyfire_warnings_disable = true;
	}
}


//
// This is for scripted sequence guys that the LD has setup to not
// get interrupted in route.
//
set_friendly_chain_wrapper( node )
{
	level.player SetFriendlyChain( node );
	level notify( "newFriendlyChain", node.script_noteworthy );
}


// Newvillers objective management
 /*
	level.currentObjective = "obj1";// disables non obj1 friendly chains if you're using newvillers style friendlychains
	objEvent = get_obj_event( "center_house" );// a trigger with targetname objective_event and a script_deathchain value

	objEvent waittill_objectiveEvent();// this waits until the AI with the event's script_deathchain are dead,
											then waits for trigger from the player. If it targets a friendly chain then it'll
											make the friendlies go to the chain.
 */

get_obj_origin( msg )
{
	objOrigins = GetEntArray( "objective", "targetname" );
	for ( i = 0; i < objOrigins.size; i++ )
	{
		if ( objOrigins[ i ].script_noteworthy == msg )
			return objOrigins[ i ].origin;
	}
}

get_obj_event( msg )
{
	objEvents = GetEntArray( "objective_event", "targetname" );
	for ( i = 0; i < objEvents.size; i++ )
	{
		if ( objEvents[ i ].script_noteworthy == msg )
			return objEvents[ i ];
	}
}


waittill_objective_event()
{
	waittill_objective_event_proc( true );
}

waittill_objective_event_notrigger()
{
	waittill_objective_event_proc( false );
}


obj_set_chain_and_enemies()
{
	objChain = GetNode( self.target, "targetname" );
	objEnemies = GetEntArray( self.target, "targetname" );
	flood_and_secure_scripted( objEnemies );
// 	array_thread(, ::flood_begin );
	level notify( "new_friendly_trigger" );
	level.player set_friendly_chain_wrapper( objChain );
}

flood_begin()
{
	self notify( "flood_begin" );
}

flood_and_secure_scripted( spawners, instantRespawn )
{
	 /*
		The "scripted" version acts as if it had been player triggered.

		Spawns AI that run to a spot then get a big goal radius. They stop spawning when auto delete kicks in, then start
		again when they are retriggered or the player gets close.

		trigger targetname flood_and_secure
		ai spawn and run to goal with small goalradius then get large goalradius
		spawner starts with a notify from any flood_and_secure trigger that triggers it
		spawner stops when an AI from it is deleted to make space for a new AI or when count is depleted
		spawners with count of 1 only make 1 guy.
		Spawners with count of more than 1 only deplete in count when the player kills the AI.
		spawner can target another spawner. When first spawner's ai dies from death( not deletion ), second spawner activates.
	 */

	if ( !isdefined( instantRespawn ) )
		instantRespawn = false;

	if ( !isdefined( level.spawnerWave ) )
		level.spawnerWave = [];
	array_thread( spawners, maps\_spawner::flood_and_secure_spawner, instantRespawn );

	for ( i = 0; i < spawners.size; i++ )
	{
		spawners[ i ].playerTriggered = true;
		spawners[ i ] notify( "flood_begin" );
	}
}


debugorigin()
{
// 	self endon( "killanimscript" );

	self notify( "Debug origin" );
	self endon( "Debug origin" );
	self endon( "death" );
	for ( ;; )
	{
		forward = AnglesToForward( self.angles );
		forwardFar = ( forward * 30 );
		forwardClose = ( forward * 20 );
		right = AnglesToRight( self.angles );
		left = ( right * -10 );
		right = ( right * 10 );
		Line( self.origin, self.origin + forwardFar, ( 0.9, 0.7, 0.6 ), 0.9 );
		Line( self.origin + forwardFar, self.origin + forwardClose + right, ( 0.9, 0.7, 0.6 ), 0.9 );
		Line( self.origin + forwardFar, self.origin + forwardClose + left, ( 0.9, 0.7, 0.6 ), 0.9 );
		wait( 0.05 );
	}
}



/*
=============
///ScriptDocBegin
"Name: get_linked_structs()"
"Summary: Returns an array of entities that SELF is linked to"
"Module: Utility"
"CallOn: An entity that links to other entities"
"Example: spawners = heli get_linked_structs()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_linked_structs()
{
	array = [];

	if ( IsDefined( self.script_linkTo ) )
	{
		linknames = get_links();
		for ( i = 0; i < linknames.size; i++ )
		{
			ent = getstruct( linknames[ i ], "script_linkname" );
			if ( IsDefined( ent ) )
			{
				array[ array.size ] = ent;
			}
		}
	}

	return array;
}

 /*
 =============
///ScriptDocBegin
"Name: get_last_ent_in_chain( <sEntityType> )"
"Summary: Get the last entity/node/vehiclenode in a chain of targeted entities"
"Module: Entity"
"CallOn: Any entity that targets a chain of linked nodes, vehiclenodes or other entities like script_origin"
"MandatoryArg: <sEntityType>: needs to be specified as 'vehiclenode', 'pathnode', 'ent' or 'struct'"
"Example: eLastNode = eVehicle get_last_ent_in_chain( "vehiclenode" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_last_ent_in_chain( sEntityType )
{
	ePathpoint = self;
	while ( IsDefined( ePathpoint.target ) )
	{
		wait( 0.05 );
		if ( IsDefined( ePathpoint.target ) )
		{
			switch( sEntityType )
			{
				case "vehiclenode":
					ePathpoint = GetVehicleNode( ePathpoint.target, "targetname" );
					break;
				case "pathnode":
					ePathpoint = GetNode( ePathpoint.target, "targetname" );
					break;
				case "ent":
					ePathpoint = GetEnt( ePathpoint.target, "targetname" );
					break;
				case "struct":
					ePathpoint = getstruct( ePathpoint.target, "targetname" );
					break;
				default:
					AssertMsg( "sEntityType needs to be 'vehiclenode', 'pathnode', 'ent' or 'struct'" );
			}
		}
		else
			break;
	}
	ePathend = ePathpoint;
	return ePathend;
}


player_seek( timeout )
{
	goalent = Spawn( "script_origin", level.player.origin );
	goalent LinkTo( level.player );
	if ( IsDefined( timeout ) )
		self thread timeout( timeout );
	self SetGoalEntity( goalent );
	if ( !isdefined( self.oldgoalradius ) )
		self.oldgoalradius = self.goalradius;
	self.goalradius = 300;
	self waittill_any( "goal", "timeout" );
	if ( IsDefined( self.oldgoalradius ) )
	{
		self.goalradius = self.oldgoalradius;
		self.oldgoalradius = undefined;
	}
	goalent Delete();
}

timeout( timeout )
{
	self endon( "death" );
	wait( timeout );
	self notify( "timeout" );
}

/*
=============
///ScriptDocBegin
"Name: set_forcegoal( <set_forcegoal> )"
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
set_forcegoal()
{
	if ( IsDefined( self.set_forcedgoal ) )
		return;

	self.oldfightdist 	 = self.pathenemyfightdist;
	self.oldmaxdist 	 = self.pathenemylookahead;
	self.oldmaxsight 	 = self.maxsightdistsqrd;

	self.pathenemyfightdist = 8;
	self.pathenemylookahead = 8;
	self.maxsightdistsqrd = 1;
	self.set_forcedgoal = true;
}

/*
=============
///ScriptDocBegin
"Name: unset_forcegoal( <unset_forcegoal> )"
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
unset_forcegoal()
{
	if ( !isdefined( self.set_forcedgoal ) )
		return;

	self.pathenemyfightdist = self.oldfightdist;
	self.pathenemylookahead = self.oldmaxdist;
	self.maxsightdistsqrd 	 = self.oldmaxsight;
	self.set_forcedgoal = undefined;
}


/*
=============
///ScriptDocBegin
"Name: array_add( <array> , <ent> )"
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
array_add( array, ent )
{
	array[ array.size ] = ent;
	return array;
}

/*
=============
///ScriptDocBegin
"Name: array_removeDead_keepkeys( <array> )"
"Summary: Remove dead from an array but keep keys intact"
"Module: Utility"
"CallOn: An array"
"MandatoryArg: <array>: The array "
"Example: array = array_removeDead_keepkeys( <array> );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_removeDead_keepkeys( array )
{
	newArray = [];
	keys = GetArrayKeys( array );
	for ( i = 0; i < keys.size; i++ )
	{
		key = keys[ i ];
		if ( !isalive( array[ key ] ) )
			continue;
		newArray[ key ] = array[ key ];
	}

	return newArray;
}

 /*
 =============
///ScriptDocBegin
"Name: array_removeDead( <array> )"
"Summary: Returns a new array of < array > minus the dead entities"
"Module: Array"
"CallOn: "
"MandatoryArg: <array> : The array to search for dead entities in."
"Example: friendlies = array_removeDead( friendlies );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
array_removeDead( array )
{
	newArray = [];
	foreach ( member in array )
	{
		if ( !isalive( member ) )
			continue;
		newArray[ newArray.size ] = member;
	}

	return newArray;
}

/*
=============
///ScriptDocBegin
"Name: array_removeDead_or_dying( <array> )"
"Summary:  Returns a new array of < array > minus the dead or dying ai"
"Module: Array"
"CallOn: "
"MandatoryArg: <array> : The array to search for dead ai in."
"Example: friendlies = array_removeDead_or_dying( friendlies );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_removeDead_or_dying( array )
{
	newArray = [];
	foreach ( member in array )
	{
		if ( !isalive( member ) )
			continue;
		if ( member doingLongDeath() )
			continue;
		newArray[ newArray.size ] = member;
	}

	return newArray;

}

 /*
 =============
///ScriptDocBegin
"Name: array_insert( <array> , <object> , <index> )"
"Summary: Returns a new array of < array > plus < object > at the specified index"
"Module: Array"
"CallOn: "
"MandatoryArg: <array> : The array to add to."
"MandatoryArg: <object> : The entity to add"
"MandatoryArg: <index> : The index position < object > should be added to."
"Example: ai = array_insert( ai, spawned, 0 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
array_insert( array, object, index )
{
	if ( index == array.size )
	{
		temp = array;
		temp[ temp.size ] = object;
		return temp;
	}
	temp = [];
	offset = 0;
	for ( i = 0; i < array.size; i++ )
	{
		if ( i == index )
		{
			temp[ i ] = object;
			offset = 1;
		}
		temp[ i + offset ] = array[ i ];
	}

	return temp;
}



/*
=============
///ScriptDocBegin
"Name: array_remove_nokeys( <ents> , <remover> )"
"Summary: array_remove used on non keyed arrays doesn't flip the array "
"Module: Utility"
"CallOn: Level"
"MandatoryArg: <ents>: array to remove from"
"MandatoryArg: <remover>: thing to remove from the array"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

array_remove_nokeys( ents, remover )
{
	newents = [];
	for ( i = 0; i < ents.size; i++ )
		if ( ents[ i ] != remover )
			newents[ newents.size ] = ents[ i ];
	return newents;
}

/*
=============
///ScriptDocBegin
"Name: array_remove_index( <array> , <index> )"
"Summary: Removes the element in the array with this index, resulting array order is intact."
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_remove_index( array, index )
{
	for ( i = 0; i < array.size - 1; i++ )
	{
		if ( i == index )
		{
			array[ i ] = array[ i + 1 ];
			index++;
		}
	}
	array[ array.size - 1 ] = undefined;
	return array;
}

/*
=============
///ScriptDocBegin
"Name: array_notify( <ents> , <notifier> )"
"Summary: notify this array of entities with <notifier>"
"Module: Array"
"CallOn: array of entities"
"MandatoryArg: <ents>: "
"MandatoryArg: <notifier>: "
"Example: array_notify( enemies, "time_to_dance" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_notify( ents, notifier, match )
{
	foreach ( key, value in ents )
		value notify( notifier, match );
}


// fancy quicker struct array handling, assumes array elements are objects with which an index can be asigned to( IE: can't do 5.struct_array_index )
// also have to be sure that objects can't be a part of another structarray setup as the index position is asigned to the object


struct_arrayspawn()
{
	struct = SpawnStruct();
	struct.array = [];
	struct.lastindex = 0;
	return struct;
}

 /*
structarray_add( struct, object )
{
	struct.array[ struct.lastindex ] = SpawnStruct();
	struct.array[ struct.lastindex ].object = object;
	struct.array[ struct.lastindex ].struct_array_index = struct.lastindex;
	struct.lastindex ++ ;
}
 */
structarray_add( struct, object )
{
	Assert( !isdefined( object.struct_array_index ) );// can't have elements of two structarrays on these. can add that later if it's needed
	struct.array[ struct.lastindex ] = object;
	object.struct_array_index = struct.lastindex;
	struct.lastindex++;
}

 /*
 =============
///ScriptDocBegin
"Name: structarray_remove( <struct> , <object )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1> : "
"OptionalArg: <param2> : "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

structarray_remove( struct, object )
{
	structarray_swaptolast( struct, object );
	struct.array[ struct.lastindex - 1 ] = undefined;
	struct.lastindex--;
}

structarray_remove_index( struct, index )
{
	// if it has a last item, copy it to the index and delete the last
	if ( IsDefined( struct.array[ struct.lastindex - 1 ] ) )
	{
		// overwrite the index to remove with the last in the array
		struct.array[ index ] = struct.array[ struct.lastindex - 1 ];
		struct.array[ index ].struct_array_index = index;

		// remove the last from the array since it's now at position 'index'
		struct.array[ struct.lastindex - 1 ] = undefined;
		struct.lastindex = struct.array.size;
	}
	else
	{
		// is not guaranteed to have a last item, could have been
		//   deleted the same frame, rebuild the array
		struct.array[ index ] = undefined;
		structarray_remove_undefined( struct );
	}
}

structarray_remove_undefined( struct )
{
	// remove undefined ents from array
	newArray = [];
	foreach( object in struct.array )
	{
		if ( !isdefined( object ) )
			continue;
		newArray[ newArray.size ] = object;
	}
	struct.array = newArray;

	// reassign all the index vars
	foreach( i, object in struct.array )
	{
		object.struct_array_index = i;
	}
	struct.lastindex = struct.array.size;
}

structarray_swaptolast( struct, object )
{
	struct structarray_swap( struct.array[ struct.lastindex - 1 ], object );
}

structarray_shuffle( struct, shuffle )
{
	for ( i = 0; i < shuffle; i++ )
		struct structarray_swap( struct.array[ i ], struct.array[ RandomInt( struct.lastindex ) ] );
}



// starts this ambient track
set_ambient_alias( ambient, alias )
{
	zone = ambient;
	maps\_audio_zone_manager::AZM_set_zone_streamed_ambience(zone, alias);
}


/*
=============
///ScriptDocBegin
"Name: get_use_key( <get_use_key> )"
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
get_use_key()
{
	if ( level.console )
	 	return " + usereload";
 	else
 		return " + activate";
}


doom()
{
	// send somebody far away then delete them
	self Teleport( ( 0, 0, -15000 ) );
	self Kill( ( 0, 0, 0 ) );
}


/*
=============
///ScriptDocBegin
"Name: custom_battlechatter( <phrase> )"
"Summary: Call this on an AI to get him to use the battlechatter system to say a specific kind of phrase.  AIs who have battlechatter turned off won't be able to say the phrase.  Returns false if it couldn't do the custom battlechatter for some reason (will output to console or assert with errors, depending on severity)."
"Module: Battlechatter"
"CallOn: An AI"
"MandatoryArg: <phrase>: the string ID for the phrase that the AI will try to say.  Legit phrases are: "order_move_combat", "order_move_noncombat", "order_action_coverme", "inform_reloading""
"Example: level.sarge custom_battlechatter( "move_combat" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
custom_battlechatter( phrase )
{
	return self animscripts\battlechatter_ai::custom_battlechatter_internal( phrase );
}


/*
=============
///ScriptDocBegin
"Name: get_stop_watch( <time> , <othertime> )"
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
get_stop_watch( time, othertime )
{
	watch = NewHudElem();
	if ( level.console )
	{
		watch.x = 68;
		watch.y = 35;
	}
	else
	{
		watch.x = 58;
		watch.y = 95;
	}

	watch.alignx = "center";
	watch.aligny = "middle";
	watch.horzAlign = "left";
	watch.vertAlign = "middle";
	if ( IsDefined( othertime ) )
		timer = othertime;
	else
		timer = level.explosiveplanttime;
	watch SetClock( timer, time, "hudStopwatch", 64, 64 );// count down for level.explosiveplanttime of 60 seconds, size is 64x64
	return watch;
}

objective_is_active( msg )
{
	active = false;
	// objective must be active for this trigger to hit
	for ( i = 0; i < level.active_objective.size; i++ )
	{
		if ( level.active_objective[ i ] != msg )
			continue;
		active = true;
		break;
	}
	return( active );
}

objective_is_inactive( msg )
{
	inactive = false;
	// objective must be active for this trigger to hit
	for ( i = 0; i < level.inactive_objective.size; i++ )
	{
		if ( level.inactive_objective[ i ] != msg )
			continue;
		inactive = true;
		break;
	}
	return( inactive );
}

set_objective_inactive( msg )
{
	// remove the objective from the active list
	array = [];
	for ( i = 0; i < level.active_objective.size; i++ )
	{
		if ( level.active_objective[ i ] == msg )
			continue;
		array[ array.size ] = level.active_objective[ i ];
	}
	level.active_objective = array;


	// add it to the inactive list
	exists = false;
	for ( i = 0; i < level.inactive_objective.size; i++ )
	{
		if ( level.inactive_objective[ i ] != msg )
			continue;
		exists = true;
	}
	if ( !exists )
		level.inactive_objective[ level.inactive_objective.size ] = msg;

	/#
	// assert that each objective is only on one list
	for ( i = 0; i < level.active_objective.size; i++ )
	{
		for ( p = 0; p < level.inactive_objective.size; p++ )
			AssertEx( level.active_objective[ i ] != level.inactive_objective[ p ], "Objective is both inactive and active" );
	}
	#/
}

set_objective_active( msg )
{
	// remove the objective from the inactive list
	array = [];
	for ( i = 0; i < level.inactive_objective.size; i++ )
	{
		if ( level.inactive_objective[ i ] == msg )
			continue;
		array[ array.size ] = level.inactive_objective[ i ];
	}
	level.inactive_objective = array;

	// add it to the active list
	exists = false;
	for ( i = 0; i < level.active_objective.size; i++ )
	{
		if ( level.active_objective[ i ] != msg )
			continue;
		exists = true;
	}
	if ( !exists )
		level.active_objective[ level.active_objective.size ] = msg;

	/#
	// assert that each objective is only on one list
	for ( i = 0; i < level.active_objective.size; i++ )
	{
		for ( p = 0; p < level.inactive_objective.size; p++ )
			AssertEx( level.active_objective[ i ] != level.inactive_objective[ p ], "Objective is both inactive and active" );
	}
	#/
}


/*
=============
///ScriptDocBegin
"Name: detect_friendly_fire( <detect_friendly_fire> )"
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
detect_friendly_fire()
{
	level thread maps\_friendlyfire::detectFriendlyFireOnEntity( self );
}

/*
=============
///ScriptDocBegin
"Name: missionFailedWrapper( <missionFailedWrapper> )"
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
missionFailedWrapper()
{
	if ( level.MissionFailed )
		return;

	if ( IsDefined( level.nextmission ) )
		return;// don't fail the mission while the game is on it's way to the next mission.

/*	// will return in the next game
	/#
	if ( IsGodMode( level.player ) )
	{
		PrintLn( GetDvar( "ui_deadquote" ) );
		return;
	}
	#/
*/

	level.MissionFailed = true;
	flag_set( "missionfailed" );

	if ( arcadeMode() )
		return;

	if ( GetDvar( "failure_disabled" ) == "1" )
		return;

	if ( is_specialop() )
	{
		level.challenge_end_time = gettime();
		thread maps\_specialops_code::failure_summary_display();
		return;
	}

	//{NOT_IN_SHIP
	mission_recon( false );	// track failed mission
	//}NOT_IN_SHIP
	MissionFailed();
}


/*
=============
///ScriptDocBegin
"Name: script_delay( <script_delay> )"
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
script_delay()
{
	if ( IsDefined( self.script_delay ) )
	{
		wait( self.script_delay );
		return true;
	}
	else
	if ( IsDefined( self.script_delay_min ) && IsDefined( self.script_delay_max ) )
	{
		wait( RandomFloatRange( self.script_delay_min, self.script_delay_max ) );
		return true;
	}

	return false;
}


/*
=============
///ScriptDocBegin
"Name: script_wait( <script_wait> )"
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
script_wait()
{
	startTime = GetTime();
	if ( IsDefined( self.script_wait ) )
	{
		wait( self.script_wait );

		if ( IsDefined( self.script_wait_add ) )
			self.script_wait += self.script_wait_add;
	}
	else if ( IsDefined( self.script_wait_min ) && IsDefined( self.script_wait_max ) )
	{
		wait( RandomFloatRange( self.script_wait_min, self.script_wait_max ) );

		if ( IsDefined( self.script_wait_add ) )
		{
			self.script_wait_min += self.script_wait_add;
			self.script_wait_max += self.script_wait_add;
		}
	}

	return( GetTime() - startTime );
}

/*
=============
///ScriptDocBegin
"Name: guy_enter_vehicle( <guy> )"
"Summary: Makes a guy get in a vehicle"
"Module: Utility"
"CallOn: A vehicle"
"MandatoryArg: <guy>: The guy getting in"
"Example: tank guy_enter_vehicle( guy );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
guy_enter_vehicle( guy )
{
	self maps\_vehicle_aianim::guy_enter( guy );
}

/*
=============
///ScriptDocBegin
"Name: guy_runtovehicle_load( <guy> , <vehicle> )"
"Summary: "
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
guy_runtovehicle_load( guy, vehicle )
{
	maps\_vehicle_aianim::guy_runtovehicle( guy, vehicle );
}


/*
=============
///ScriptDocBegin
"Name: get_force_color_guys( <team> , <color> )"
"Summary: gets array of guys on this team with"
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <team>:a team name, either 'axis', 'allies', 'team3', 'neutral', or 'bad_guys' (for all bad guy teams)  "
"MandatoryArg: <color>: color group"
"Example: 	ai = get_force_color_guys( "allies", "c" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

get_force_color_guys( team, color )
{
	ai = GetAIArray( team );
	guys = [];
	for ( i = 0; i < ai.size; i++ )
	{
		guy = ai[ i ];
		if ( !isdefined( guy.script_forcecolor ) )
			continue;

		if ( guy.script_forcecolor != color )
			continue;
		guys[ guys.size ] = guy;
	}

	return guys;
}

get_all_force_color_friendlies()
{
	ai = GetAIArray( "allies" );
	guys = [];
	for ( i = 0; i < ai.size; i++ )
	{
		guy = ai[ i ];
		if ( !isdefined( guy.script_forcecolor ) )
			continue;
		guys[ guys.size ] = guy;
	}

	return guys;
}

/*
=============
///ScriptDocBegin
"Name: get_all_target_ents( <target> )"
"Summary: Returns array of targetted ent, structs, nodes"
"Module: Utility"
"OptionalArg: <target>: Optional target override"
"Example: node = guy get_target_ent();"
"SPMP: both"
///ScriptDocEnd
=============
*/
get_all_target_ents( target )
{
	if ( !isdefined( target ) )
		target = self.target;

	AssertEx( IsDefined( target ), "Self had no target!" );
	array = [];

	ents = GetEntArray( target, "targetname" );
	array = array_combine( array, ents );

	ents = GetNodeArray( target, "targetname" );
	array = array_combine( array, ents );

	ents = getstructarray( target, "targetname" );
	array = array_combine( array, ents );

	ents = GetVehicleNodeArray( target, "targetname" );
	array = array_combine( array, ents );

	return array;
}



/*
=============
///ScriptDocBegin
"Name: enable_ai_color( )"
"Summary: Enables color movement system on an AI"
"Module: Entity"
"CallOn: An entity"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_ai_color()
{
	if ( IsDefined( self.script_forcecolor ) )
		return;
	if ( !isdefined( self.old_forceColor ) )
		return;

	set_force_color( self.old_forcecolor );
	self.old_forceColor = undefined;
}

/*
=============
///ScriptDocBegin
"Name: enable_ai_color_dontmove( )"
"Summary: Enables color movement system on an AI, but wont cause them to move to that color until another order is given by script or trigger"
"Module: Entity"
"CallOn: An entity"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_ai_color_dontmove()
{
	self.dontColorMove = true;
	self enable_ai_color();
}

/*
=============
///ScriptDocBegin
"Name: disable_ai_color( <disable_ai_color> )"
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
disable_ai_color()
{
	if ( IsDefined( self.new_force_color_being_set ) )
	{
		self endon( "death" );
		// setting force color happens after waittillframeend so we need to wait until it finishes
		// setting before we disable it, so a set followed by a disable will send the guy to a node.
		self waittill( "done_setting_new_color" );
	}

	self ClearFixedNodeSafeVolume();
	// any color on this guy?
	if ( !isdefined( self.script_forcecolor ) )
	{
		return;
	}

	AssertEx( !isdefined( self.old_forcecolor ), "Tried to disable forcecolor on a guy that somehow had a old_forcecolor already. Investigate!!!" );

	self.old_forceColor = self.script_forceColor;


	// first remove the guy from the force color array he used to belong to
	level.arrays_of_colorForced_ai[ self maps\_colors::get_team() ][ self.script_forcecolor ] = array_remove( level.arrays_of_colorForced_ai[ self maps\_colors::get_team() ][ self.script_forcecolor ], self );
// 	self maps\_colors::removeAIFromColorNumberArray();

	maps\_colors::left_color_node();
	self.script_forcecolor = undefined;
	self.currentColorCode = undefined;
	/#
	update_debug_friendlycolor( self.unique_id );
	#/
}

/*
=============
///ScriptDocBegin
"Name: clear_force_color( <clear_force_color> )"
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
clear_force_color()
{
	disable_ai_color();
}

/*
=============
///ScriptDocBegin
"Name: check_force_color( <_color> )"
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
check_force_color( _color )
{
	color = level.colorCheckList[ ToLower( _color ) ];
	if ( IsDefined( self.script_forcecolor ) && color == self.script_forcecolor )
		return true;
	else
		return false;
}

/*
=============
///ScriptDocBegin
"Name: get_force_color( <get_force_color> )"
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
get_force_color()
{
	color = self.script_forceColor;
	return color;
}

shortenColor( color )
{
	AssertEx( IsDefined( level.colorCheckList[ ToLower( color ) ] ), "Tried to set force color on an undefined color: " + color );
	return level.colorCheckList[ ToLower( color ) ];
}


/*
=============
///ScriptDocBegin
"Name: set_force_color( <_color> )"
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
set_force_color( _color )
{
	// shorten and lowercase the ai's forcecolor to a single letter
	color = shortenColor( _color );

	AssertEx( maps\_colors::colorIsLegit( color ), "Tried to set force color on an undefined color: " + color );

	if ( !isAI( self ) )
	{
		set_force_color_spawner( color );
		return;
	}

	AssertEx( IsAlive( self ), "Tried to set force color on a dead / undefined entity." );
	 /*
	 /#
	thread insure_player_does_not_set_forcecolor_twice_in_one_frame();
	#/
	 */

	if ( self.team == "allies" )
	{
		// enable fixed node mode.
		self.fixednode = true;
		self.fixednodesaferadius = 64;
		self.pathenemyfightdist = 0;
		self.pathenemylookahead = 0;
	}

// 	maps\_colors::removeAIFromColorNumberArray();
	self.script_color_axis = undefined;
	self.script_color_allies = undefined;
	self.old_forcecolor = undefined;

	team = maps\_colors::get_team();

	if ( IsDefined( self.script_forcecolor ) )
	{
		// first remove the guy from the force color array he used to belong to
		level.arrays_of_colorForced_ai[ team ][ self.script_forcecolor ] = array_remove( level.arrays_of_colorForced_ai[ team ][ self.script_forcecolor ], self );
	}
	self.script_forcecolor = color;

	// get added to the new array of AI that are forced to this color
	level.arrays_of_colorForced_ai[ team ][ color ] = array_removeDead( level.arrays_of_colorForced_ai[ team ][ color ] );
	level.arrays_of_colorForced_ai[ team ][ self.script_forcecolor ] = array_add( level.arrays_of_colorForced_ai[ team ][ self.script_forcecolor ], self );

	// set it here so that he continues in script as the correct color
	thread new_color_being_set( color );
}

set_force_color_spawner( color )
{
	 /*
	team = undefined;
	colorTeam = undefined;
	if( IsSubStr( self.classname, "axis" ) )
	{
		colorTeam = self.script_color_axis;
		team = "axis";
	}

	if( IsSubStr( self.classname, "ally" ) )
	{
		colorTeam = self.script_color_allies;
		team = "allies";
	}

	maps\_colors::removeSpawnerFromColorNumberArray();
	 */

	self.script_forcecolor = color;
// 	self.script_color_axis = undefined;
// 	self.script_color_allies = undefined;
	self.old_forceColor = undefined;
// 	thread maps\_colors::spawner_processes_colorCoded_ai();
}

issue_color_orders( color_team, team )
{
	colorCodes = StrTok( color_team, " " );
	colors = [];
	colorCodesByColorIndex = [];

	for ( i = 0; i < colorCodes.size; i++ )
	{
		color = undefined;
		if ( IsSubStr( colorCodes[ i ], "r" ) )
			color = "r";
		else
		if ( IsSubStr( colorCodes[ i ], "b" ) )
			color = "b";
		else
		if ( IsSubStr( colorCodes[ i ], "y" ) )
			color = "y";
		else
		if ( IsSubStr( colorCodes[ i ], "c" ) )
			color = "c";
		else
		if ( IsSubStr( colorCodes[ i ], "g" ) )
			color = "g";
		else
		if ( IsSubStr( colorCodes[ i ], "p" ) )
			color = "p";
		else
		if ( IsSubStr( colorCodes[ i ], "o" ) )
			color = "o";
		else
			AssertEx( 0, "Trigger at origin " + self GetOrigin() + " had strange color index " + colorCodes[ i ] );

		colorCodesByColorIndex[ color ] = colorCodes[ i ];
		colors[ colors.size ] = color;
	}

	Assert( colors.size == colorCodes.size );

	for ( i = 0; i < colorCodes.size; i++ )
	{
		// remove deleted spawners
		level.arrays_of_colorCoded_spawners[ team ][ colorCodes[ i ] ] = array_removeUndefined( level.arrays_of_colorCoded_spawners[ team ][ colorCodes[ i ] ] );

		AssertEx( IsDefined( level.arrays_of_colorCoded_spawners[ team ][ colorCodes[ i ] ] ), "Trigger refer to a color# that does not exist in any node for this team." );
		// set the .currentColorCode on each appropriate spawner
		for ( p = 0; p < level.arrays_of_colorCoded_spawners[ team ][ colorCodes[ i ] ].size; p++ )
			level.arrays_of_colorCoded_spawners[ team ][ colorCodes[ i ] ][ p ].currentColorCode = colorCodes[ i ];
	}

	for ( i = 0; i < colors.size; i++ )
	{
		// remove the dead from the color forced ai
		level.arrays_of_colorForced_ai[ team ][ colors[ i ] ] = array_removeDead( level.arrays_of_colorForced_ai[ team ][ colors[ i ] ] );

		// set the destination of the color forced spawners
		level.currentColorForced[ team ][ colors[ i ] ] = colorCodesByColorIndex[ colors[ i ] ];
	}

	for ( i = 0; i < colorCodes.size; i++ )
		self thread maps\_colors::issue_color_order_to_ai( colorCodes[ i ], colors[ i ], team );
}


// TODO: Non - hacky rumble.
flashRumbleLoop( duration )
{
	Assert( IsPlayer( self ) );

	goalTime = GetTime() + duration * 1000;

	while ( GetTime() < goalTime )
	{
		self PlayRumbleOnEntity( "damage_heavy" );
		wait( 0.05 );
	}
}

flashMonitorEnableHealthShield( time )
{
	self endon( "death" );
	self endon( "flashed" );

	wait 0.2;

	self EnableHealthShield( false );

	wait time + 2;

	self EnableHealthShield( true );
}

nineBangHandler( origin, percent_distance, percent_angle, attacker, team )
{
	waits = [ 0.8, 0.7, 0.7, 0.6 ];
	banglens = [ 1.0, 0.8, 0.6, 0.6 ];
	foreach( i, banglen in banglens)
	{
		// if it's close enough, angle doesn't matter so much
		frac = ( percent_distance - 0.85 ) / ( 1 - 0.85 );
		if ( frac > percent_angle )
			percent_angle = frac;

		if ( percent_angle < 0.25 )
			percent_angle = 0.25;

		// at 300 or less of the full range of 1000 units, get the full effect
		minamountdist = 0.3;
		if ( percent_distance > 1 - minamountdist )
			percent_distance = 1.0;
		else
			percent_distance = percent_distance / ( 1 - minamountdist );

		if ( team != self.team )
			seconds = percent_distance * percent_angle * 6.0;
		else
			seconds = percent_distance * percent_angle * 3.0;

		if ( seconds < 0.25 )
			continue;

		seconds = banglen * seconds;
		if ( IsDefined( self.maxflashedseconds ) && seconds > self.maxflashedseconds )
 			seconds = self.maxflashedseconds;

		self.flashingTeam = team;
		self notify( "flashed" );
		self.flashendtime = GetTime() + seconds * 1000;// player is flashed if flashDoneTime > GetTime()
		self ShellShock( "flashbang", seconds );
		
		flag_set( "player_flashed" );

		if ( percent_distance * percent_angle > 0.5 )
			self thread flashMonitorEnableHealthShield( seconds );
		wait waits[i];
	}
	thread unflash_flag( 0.05 );
}

flashMonitor()
{
	Assert( IsPlayer( self ) );

	self endon( "death" );

	for ( ;; )
	{
		self waittill( "flashbang", origin, percent_distance, percent_angle, attacker, team );

		if ( "1" == GetDvar( "noflash" ) )
			continue;

		if ( is_player_down( self ) )
			continue;

		if (isdefined(self.threw_ninebang))
		{
			player_range_percent = 1000/1250;	// standard fb radius / 9b radius
			om_player_range_percent = 1.0 - player_range_percent;
			self.threw_ninebang = undefined;
			// percent_distance == 0 at max range, 1 at min_range and less
			if (percent_distance < om_player_range_percent)
				continue;	// outside player's radius so skip it
			percent_distance = (percent_distance-om_player_range_percent) / player_range_percent;	// rescale percent_distance to match standard fb
		}
		// PrintLn( "Flashed by a grenade from team '", team, "'." );

		// if it's close enough, angle doesn't matter so much
		frac = ( percent_distance - 0.85 ) / ( 1 - 0.85 );
		if ( frac > percent_angle )
			percent_angle = frac;

		if ( percent_angle < 0.25 )
			percent_angle = 0.25;

		// at 300 or less of the full range of 1000 units, get the full effect
		minamountdist = 0.3;
		if ( percent_distance > 1 - minamountdist )
			percent_distance = 1.0;
		else
			percent_distance = percent_distance / ( 1 - minamountdist );

		if ( team != self.team )
			seconds = percent_distance * percent_angle * 6.0;
		else
			seconds = percent_distance * percent_angle * 3.0;

		if ( seconds < 0.25 )
			continue;

		if ( IsDefined( self.maxflashedseconds ) && seconds > self.maxflashedseconds )
 			seconds = self.maxflashedseconds;

		self.flashingTeam = team;
		self notify( "flashed" );
		self.flashendtime = GetTime() + seconds * 1000;// player is flashed if flashDoneTime > GetTime()
		self ShellShock( "flashbang", seconds );
		flag_set( "player_flashed" );
		thread unflash_flag( seconds );

		if ( percent_distance * percent_angle > 0.5 )
			self thread flashMonitorEnableHealthShield( seconds );

		if ( seconds > 2 )
			thread flashRumbleLoop( 0.75 );
		else
			thread flashRumbleLoop( 0.25 );

		// if it's an enemy's flash grenade,
		// flash nearby allies so they can't take out enemies going after the player
		if ( team != "allies" )
			self thread flashNearbyAllies( seconds, team );
	}
}


flashNearbyAllies( baseDuration, team )
{
	Assert( IsPlayer( self ) );

	wait .05;

	allies = GetAIArray( "allies" );
	for ( i = 0; i < allies.size; i++ )
	{
		if ( DistanceSquared( allies[ i ].origin, self.origin ) < 350 * 350 )
		{
			duration = baseDuration + RandomFloatRange( -1000, 1500 );
			if ( duration > 4.5 )
				duration = 4.5;
			else if ( duration < 0.25 )
				continue;

			newendtime = GetTime() + duration * 1000;
			if ( !isdefined( allies[ i ].flashendtime ) || allies[ i ].flashendtime < newendtime )
			{
				allies[ i ].flashingTeam = team;
				allies[ i ] flashBangStart( duration );
			}
		}
	}
}

/*
=============
///ScriptDocBegin
"Name: restartEffect( <restartEffect> )"
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
restartEffect()
{
	self common_scripts\_createfx::restart_fx_looper();
}

/*
=============
///ScriptDocBegin
"Name: pauseExploder( <num> )"
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
pauseExploder( num )
{
	num += "";

	if (isdefined(level.createFXexploders))
	{	// do optimized flavor if available
		exploders = level.createFXexploders[num];
		if (isdefined(exploders))
		{
			foreach (ent in exploders)
			{
				ent pauseEffect();
			}
		}
	}
	else
	{
		foreach ( fx in level.createFXent )
		{
			if ( !isdefined( fx.v[ "exploder" ] ) )
				continue;
	
			if ( fx.v[ "exploder" ] != num )
				continue;
	
			fx pauseEffect();
		}
	}
}

/*
=============
///ScriptDocBegin
"Name: restartExploder( <num> )"
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
restartExploder( num )
{
	num += "";
	if (isdefined(level.createFXexploders))
	{	// do optimized flavor if available
		exploders = level.createFXexploders[num];
		if (isdefined(exploders))
		{
			foreach (ent in exploders)
			{
				ent restartEffect();
			}
		}
	}
	else
	{
		foreach ( fx in level.createFXent )
		{
			if ( !isdefined( fx.v[ "exploder" ] ) )
				continue;
	
			if ( fx.v[ "exploder" ] != num )
				continue;
	
			fx restartEffect();
		}
	}
}

/*
=============
///ScriptDocBegin
"Name: getfxarraybyID( <fxid> )"
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
getfxarraybyID( fxid )
{
	array = [];
	if (isdefined(level.createFXbyFXID))
	{
		fxids = level.createFXbyFXID[fxid];
		if (isdefined(fxids))
			array = fxids;
	}
	else
	{
		for ( i = 0; i < level.createFXent.size; i++ )
		{
			if ( level.createFXent[ i ].v[ "fxid" ] == fxid )
				array[ array.size ] = level.createFXent[ i ];
		}
	}
	return array;
}

ignoreAllEnemies( qTrue )
{
	self notify( "ignoreAllEnemies_threaded" );
	self endon( "ignoreAllEnemies_threaded" );

	if ( qTrue )
	{
		// put the ai in a threat bias group that ignores all the other groups so he
		// doesnt get distracted and go into exposed while his goal radius is too small

		self.old_threat_bias_group = self GetThreatBiasGroup();

		num = undefined;
		/#
			num = self GetEntNum();
			PrintLn( "entity: " + num + "ignoreAllEnemies TRUE" );
			PrintLn( "entity: " + num + " threatbiasgroup is " + self.old_threat_bias_group );
		#/

		CreateThreatBiasGroup( "ignore_everybody" );
		/#
			PrintLn( "entity: " + num + "ignoreAllEnemies TRUE" );
			PrintLn( "entity: " + num + " SetThreatBiasGroup( ignore_everybody )" );
		#/
		self SetThreatBiasGroup( "ignore_everybody" );
		teams = [];
		teams[ "axis" ] = "allies";
		teams[ "allies" ] = "axis";

		AssertEx( self.team != "neutral", "Why are you making a guy have team neutral? And also, why is he doing anim_reach?" );
		ai = GetAIArray( teams[ self.team ] );
		groups = [];
		for ( i = 0; i < ai.size; i++ )
			groups[ ai[ i ] GetThreatBiasGroup() ] = true;

		keys = GetArrayKeys( groups );
		for ( i = 0; i < keys.size; i++ )
		{
			/#
				PrintLn( "entity: " + num + "ignoreAllEnemies TRUE" );
				PrintLn( "entity: " + num + " SetThreatBias( " + keys[ i ] + ", ignore_everybody, 0 )" );
			#/
			SetThreatBias( keys[ i ], "ignore_everybody", 0 );
		}

		// should now be impossible for this guy to attack anybody on the other team
	}
	else
	{
		num = undefined;
		AssertEx( IsDefined( self.old_threat_bias_group ), "You can't use ignoreAllEnemies( false ) on an AI that has never ran ignoreAllEnemies( true )" );
		/#
			num = self GetEntNum();
			PrintLn( "entity: " + num + "ignoreAllEnemies FALSE" );
			PrintLn( "entity: " + num + " self.old_threat_bias_group is " + self.old_threat_bias_group );
		#/
		if ( self.old_threat_bias_group != "" )
		{
			/#
				PrintLn( "entity: " + num + "ignoreAllEnemies FALSE" );
				PrintLn( "entity: " + num + " SetThreatBiasGroup( " + self.old_threat_bias_group + " )" );
			#/
			self SetThreatBiasGroup( self.old_threat_bias_group );
		}
		self.old_threat_bias_group = undefined;
	}
}



/*
=============
///ScriptDocBegin
"Name: vehicle_detachfrompath( <vehicle_detachfrompath> )"
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
vehicle_detachfrompath()
{
	maps\_vehicle::vehicle_pathdetach();
}

 /*
 =============
///ScriptDocBegin
"Name: vehicle_resumepath()"
"Summary: will resume to the last path a vehicle was on.  Only used for helicopters, ground vehicles don't ever deviate."
"Module: Vehicle"
"CallOn: An entity"
"Example: helicopter vehicle_resumepath();"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

vehicle_resumepath()
{
	thread maps\_vehicle::vehicle_resumepathvehicle();
}

 /*
 =============
///ScriptDocBegin
"Name: vehicle_land( <neargoaldist>)"
"Summary: lands a vehicle on the ground, _vehicle scripts take care of offsets and determining where the ground is relative to the origin.  Returns when land is complete"
"Module: Vehicle"
"CallOn: An entity"
"OptionalArg: <neargoaldist>: neargoal distance for notifying near_goal"
"Example: helicopter vehicle_land();"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

vehicle_land( neargoaldist )
{
	maps\_vehicle::vehicle_landvehicle( neargoaldist );
}

/*
=============
///ScriptDocBegin
"Name: vehicle_liftoff( <height> )"
"Summary: make a vehicle lift of to the specified height. if the vehicle was on a path and went through vehicle_land, this will resume that path"
"Module: Entity"
"CallOn: An entity"
"OptionalArg: <height>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
vehicle_liftoff( height )
{
	maps\_vehicle::vehicle_liftoffvehicle( height );
}

/*
=============
///ScriptDocBegin
"Name: vehicle_dynamicpath( <node> , <bwaitforstart> )"
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
vehicle_dynamicpath( node, bwaitforstart )
{
	maps\_vehicle::vehicle_paths( node, bwaitforstart );
}

 /*
 =============
///ScriptDocBegin
"Name: groundpos( <origin> )"
"Summary: bullettraces to the ground and returns the position that it hit."
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <origin> : "
"Example: groundposition = helicopter groundpos( helicopter.origin ); "
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

groundpos( origin )
{
	return BulletTrace( origin, ( origin + ( 0, 0, -100000 ) ), 0, self )[ "position" ];
}

change_player_health_packets( num )
{
	Assert( IsPlayer( self ) );

	self.player_health_packets += num;
	self notify( "update_health_packets" );

	if ( self.player_health_packets >= 3 )
		self.player_health_packets = 3;

// 	if( self.player_health_packets <= 0 )
// 		self Kill();
}

/*
=============
///ScriptDocBegin
"Name: getvehiclespawner( <targetname> )"
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
getvehiclespawner( targetname )
{
	spawners = getvehiclespawnerarray( targetname );
	Assert( spawners.size == 1 );
	return spawners[ 0 ];
}

/*
=============
///ScriptDocBegin
"Name: getvehiclespawnerarray( <targetname> )"
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
getvehiclespawnerarray( targetname )
{
	return maps\_vehicle::_getvehiclespawnerarray( targetname );
}


/*
=============
///ScriptDocBegin
"Name: describe_start( <msg> , <func> , <loc_string> , <optional_func> )"
"Summary: Use this for Describing an add_start() function, meant for reducing upward dependancy on <LevelName>_starts.gsc "
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <msg>: SEEDOC:Utility\add_start"
"MandatoryArg: <func>: SEEDOC:Utility\add_start"
"OptionalArg: <loc_string>: SEEDOC:Utility\add_start"
"OptionalArg: <optional_func>: SEEDOC:Utility\add_start"
"Example: "
"SPMP: singleplayer"
"NoteLine: with describe_start the order doesn't matter. you are not actually creating the start point order untill you add_start()"
///ScriptDocEnd
=============
*/

describe_start( msg, func, loc_string, optional_func )
{
    add_start_assert();

    if( !IsDefined( level.start_description ) )
        level.start_description = [];
    
    AssertEx( !isdefined( level.start_description[ msg ] ), "You are describing this start point more than once" );
        
    level.start_description[ msg ]  = add_start_construct( msg, func, loc_string, optional_func );
    
}

/*
=============
///ScriptDocBegin
"Name: add_start( <msg> , <func> , <loc_string> , <optional_func> )"
"Summary: add start with a string"
"Module: Utility"
"CallOn: Level"
"MandatoryArg: <msg>: string to identify the start"
"MandatoryArg: <func>: thread to start when this start is initialized.  This Argument is optional when a start is described using describe_start. SEEDOC:Utility\describe_start"
"OptionalArg: <loc_string>: Localizated string to display, this became a requirement when loc_warnings were turned on."
"OptionalArg: <Optional_func>: The main logic function associated with this start point, will run in the order of the start points when a previous function completes."
"Example: 	add_start( "first_hind", ::start_first_hind, &"STARTS_FIRSTHIND" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

add_start( msg, func, loc_string, optional_func )
{
    add_start_assert();
    
	msg = ToLower( msg );

	
	if ( IsDefined( level.start_description ) && IsDefined( level.start_description[ msg ]  ) )
	{
	    /#
    	    assert_msg = "This start is already described. you only need add_start( msg )";
    	    AssertEx( ! IsDefined( func ), assert_msg );
    	    AssertEx( ! IsDefined( loc_string ), assert_msg );
    	    AssertEx( ! IsDefined( optional_func ), assert_msg );
	    #/
	    array = level.start_description[ msg ];
	}
	else
    	array = add_start_construct( msg, func, loc_string, optional_func );
    	
    	
    if( !IsDefined( func ) )
    {
        if ( !IsDefined( level.start_description ) )
            AssertEx( IsDefined( func ), "add_start() called with no descriptions set and no func parameter.." );
        else if( !IsSubStr( msg, "no_game" ) ) 
        {
            if ( !IsDefined( level.start_description[ msg ] ) )
                return; // want to ignore all the other starts. when descriptions are made.
        }
    }

	level.start_functions[ level.start_functions.size ] = array;
	level.start_arrays[ msg ] = array;
}

is_no_game_start()
{
    return IsSubStr( level.start_point, "no_game" );
}

add_start_construct( msg, func, loc_string, optional_func )
{
    
    /#
	if ( IsDefined( loc_string ) )
	{
		PreCacheString( loc_string );
	}
	#/

	array = [];
	array[ "name" ] = msg;
	array[ "start_func" ] = func;
	array[ "start_loc_string" ] = loc_string;
	array[ "logic_func" ] = optional_func;
    return array;
}

add_start_assert()
{
   	AssertEx( !isdefined( level._loadStarted ), "Can't create starts after _load" );
	if ( !isdefined( level.start_functions ) )
		level.start_functions = [];
}

level_has_start_points()
{
	// account for no_game start point
	return level.start_functions.size > 1;
}

/*
=============
///ScriptDocBegin
"Name: set_default_start( <start> )"
"Summary: Set the default start point by name."
"Module: Utility"
"MandatoryArg: <start>: Which start to use as the default start."
"Example: set_default_start( "ride" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_default_start( start )
{
	level.default_start_override = start;
}

/*
=============
///ScriptDocBegin
"Name: default_start( <func> )"
"Summary: "
"Module: Utility"
"CallOn: Level"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
default_start( func )
{
	level.default_start = func;
}

linetime( start, end, color, timer )
{
	thread linetime_proc( start, end, color, timer );
}

 /*
 =============
///ScriptDocBegin
"Name: within_fov( <start_origin> , <start_angles> , <end_origin> , <fov> )"
"Summary: Returns true if < end_origin > is within the players field of view, otherwise returns false."
"Module: Vector"
"CallOn: "
"MandatoryArg: <start_origin> : starting origin for FOV check( usually the players origin )"
"MandatoryArg: <start_angles> : angles to specify facing direction( usually the players angles )"
"MandatoryArg: <end_origin> : origin to check if it's in the FOV"
"MandatoryArg: <fov> : cosine of the FOV angle to use"
"Example: qBool = within_fov( level.player.origin, level.player.angles, target1.origin, Cos( 45 ) );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
within_fov( start_origin, start_angles, end_origin, fov )
{
	normal = VectorNormalize( end_origin - start_origin );
	forward = AnglesToForward( start_angles );
	dot = VectorDot( forward, normal );

	return dot >= fov;
}

 /*
 =============
///ScriptDocBegin
"Name: within_fov_2d( <start_origin> , <start_angles> , <end_origin> , <fov> )"
"Summary: Returns true if < end_origin > is within the players field of view, otherwise returns false. Compares in 2d only."
"Module: Vector"
"CallOn: "
"MandatoryArg: <start_origin> : starting origin for FOV check( usually the players origin )"
"MandatoryArg: <start_angles> : angles to specify facing direction( usually the players angles )"
"MandatoryArg: <end_origin> : origin to check if it's in the FOV"
"MandatoryArg: <fov> : cosine of the FOV angle to use"
"Example: qBool = within_fov_2d( level.player.origin, level.player.angles, target1.origin, Cos( 45 ) );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
within_fov_2d( start_origin, start_angles, end_origin, fov )
{
	start_origin = set_z( start_origin, 0 );
	end_origin = set_z( end_origin, 0 );
	start_angles = ( 0, start_angles[ 1 ], 0 );

	normal = VectorNormalize( end_origin - start_origin );
	forward = AnglesToForward( start_angles );
	dot = VectorDot( forward, normal );

	return dot >= fov;
}


 /*
 =============
///ScriptDocBegin
"Name: get_dot( <start_origin> , <start_angles> , <end_origin> )"
"Summary: Returns the dot product."
"Module: Vector"
"CallOn: "
"MandatoryArg: <start_origin> : starting origin for FOV check( usually the players origin )"
"MandatoryArg: <start_angles> : angles to specify facing direction( usually the players angles )"
"MandatoryArg: <end_origin> : origin to check if it's in the FOV"
"Example: fov = get_dot( level.player.origin, level.player.angles, target1.origin );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
get_dot( start_origin, start_angles, end_origin )
{
	normal = VectorNormalize( end_origin - start_origin );
	forward = AnglesToForward( start_angles );
	dot = VectorDot( forward, normal );

	return dot;
}



 /*
 =============
///ScriptDocBegin
"Name: within_fov_of_players( <end_origin> , <fov> )"
"Summary: Returns true if < end_origin > is within the all of the players field of view (single or coop), otherwise returns false. Start origin and start angles are of the individual players in the map (single or coop)"
"Module: Vector"
"CallOn: "
"MandatoryArg: <end_origin> : origin to check if it's in the FOV"
"MandatoryArg: <fov> : cosine of the FOV angle to use"
"Example: qBool = within_fov_of_players( target1.origin, Cos( 45 ) );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
within_fov_of_players( end_origin, fov )
{
	bDestInFOV = undefined;
	for ( i = 0; i < level.players.size; i++ )
	{
		playerEye = level.players[ i ] GetEye();
		bDestInFOV = within_fov( playerEye, level.players[ i ] GetPlayerAngles(), end_origin, fov );
		if ( !bDestInFOV )
			return false;
	}
	return true;
}

waitSpread( start, end )
{
	if ( !isdefined( end ) )
	{
		end = start;
		start = 0;
	}
	AssertEx( IsDefined( start ) && IsDefined( end ), "Waitspread was called without defining amount of time" );

	// temporarily disabling waitspread until I have time to fix it properly
	wait( RandomFloatRange( start, end ) );
	if ( 1 )
		return;

	personal_wait_index = undefined;

	if ( !isdefined( level.active_wait_spread ) )
	{
		// the first guy sets it up and runs the master logic. Thread it off in case he dies

		level.active_wait_spread = true;
		level.wait_spreaders = 0;
		personal_wait_index = level.wait_spreaders;
		level.wait_spreaders++;
		thread waitSpread_code( start, end );
	}
	else
	{
		personal_wait_index = level.wait_spreaders;
		level.wait_spreaders++;
		waittillframeend;// give every other waitspreader in this frame a chance to increment wait_spreaders
	}

	waittillframeend;// wait for the logic to setup the waits

	wait( level.wait_spreader_allotment[ personal_wait_index ] );

}

/*
=============
///ScriptDocBegin
"Name: wait_for_buffer_time_to_pass( <start_time> , <buffer_time> )"
"Summary: Wait until the current time is equal or greater than the start_time (in ms) + buffer_time (in seconds)"
"Module: Utility"
"MandatoryArg: <start_time>: The GetTime() at the start of the scene."
"MandatoryArg: <buffer_time>: The amount of time you want to insure has passed since start_time."
"Example: wait_for_buffer_time_to_pass( level.last_time_we_checked, 3 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
wait_for_buffer_time_to_pass( last_queue_time, buffer_time )
{
	timer = buffer_time * 1000 - ( GetTime() - last_queue_time );
	timer *= 0.001;
	if ( timer > 0 )
	{
		// 500ms buffer time between radio or dialogue sounds
		wait( timer );
	}
}

bcs_scripted_dialogue_start()
{
	anim.scriptedDialogueStartTime = GetTime();
}

/*
=============
///ScriptDocBegin
"Name: dialogue_queue( <msg> )"
"Summary: Plays an anim_single_queue on the guy, with the guy as the actor"
"Module: Utility"
"CallOn: An ai"
"MandatoryArg: <msg>: The dialogue scene, defined as level.scr_sound[ guys.animname ][ "scene" ] "
"Example: level.price dialogue_queue( "nice_find_macgregor" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
dialogue_queue( msg )
{
	bcs_scripted_dialogue_start();

	self maps\_anim::anim_single_queue( self, msg );
}

/*
=============
///ScriptDocBegin
"Name: generic_dialogue_queue( <msg>, <timeout> )"
"Summary: Plays an anim_generic_queue on the guy, with the guy as the actor"
"Module: Utility"
"CallOn: An ai"
"MandatoryArg: <msg>: The dialogue scene, defined as level.scr_sound[ "generic" ][ "scene" ] "
"OptionalArg: <timeout>: optional timeout to forget the radio dialogue if it's been in the queue for longer than this many seconds"
"Example: level.price dialogue_queue( "nice_find_macgregor" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

generic_dialogue_queue( msg, timeout )
{
	bcs_scripted_dialogue_start();

	self maps\_anim::anim_generic_queue( self, msg, undefined, undefined, timeout );
}

/*
=============
///ScriptDocBegin
"Name: radio_dialogue( <msg> )"
"Summary: puts radio dialogue into a queue. Dialogue plays when it gets it's turn in the queue."
"Module: Utility"
"MandatoryArg: <msg>: the radio dialogue alias to play"
"OptionalArg: <timeout>: optional timeout to forget the radio dialogue if it's been in the queue for longer than this many seconds"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
radio_dialogue( msg, timeout )
{
	AssertEx( IsDefined( level.scr_radio[ msg ] ), "Tried to play radio dialogue " + msg + " that did not exist! Add it to level.scr_radio" );

	//this is so we have a universal entity to stack radio dialogue on without worrying about
	//any other scripts dirtying up the stack with functions not related to radio_dialogue
	if ( !isdefined( level.player_radio_emitter ) )
	{
		ent = Spawn( "script_origin", ( 0, 0, 0 ) );
		ent LinkTo( level.player, "", ( 0, 0, 0 ), ( 0, 0, 0 ) );
		level.player_radio_emitter = ent;
	}

	bcs_scripted_dialogue_start();

	success = false;
	if ( !IsDefined( timeout ) )
	{
		success = level.player_radio_emitter function_stack( ::play_sound_on_tag, level.scr_radio[ msg ], undefined, true );
	}
	else
	{
		success = level.player_radio_emitter function_stack_timeout( timeout, ::play_sound_on_tag, level.scr_radio[ msg ], undefined, true );
	}

	return success;
}

/*
=============
///ScriptDocBegin
"Name: radio_dialogue_overlap( <msg> )"
"Summary: Play a radio dialogue sound on top of whatever radio dialogue is currently playing (overlapping)."
"Module: Utility"
"MandatoryArg: <msg>: The dialogue alias"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
radio_dialogue_overlap( msg )
{
	AssertEx( IsDefined( level.scr_radio[ msg ] ), "Tried to play radio dialogue " + msg + " that did not exist! Add it to level.scr_radio" );
	AssertEx( IsDefined( level.player_radio_emitter ), "Tried to overlap dialogue but no radio dialogue was playing, use radio_dialogue." );

	level.player_radio_emitter play_sound_on_tag( level.scr_radio[ msg ], undefined, true );
}

/*
=============
///ScriptDocBegin
"Name: radio_dialogue_stop()"
"Summary: Stops any radio dialogue currently playing and Stops any further radio dialogue queued up from playing ( removes those requests from the queue )"
"Module: Utility"
"Example: radio_dialogue_stop();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
radio_dialogue_stop()
{
	if ( !isdefined( level.player_radio_emitter ) )
		return;
	//level.player_radio_emitter function_stack_clear(); ->don't need it - kills the funciton stack already
	level.player_radio_emitter Delete();
}

/*
=============
///ScriptDocBegin
"Name: radio_dialogue_clear_stack()"
"Summary: Stops any further radio dialogue queued up from playing ( removes those requests from the queue )"
"Module: Utility"
"Example: radio_dialogue_clear_stack();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
radio_dialogue_clear_stack()
{
	if ( !isdefined( level.player_radio_emitter ) )
		return;
	level.player_radio_emitter function_stack_clear();
}

/*
=============
///ScriptDocBegin
"Name: radio_dialogue_interupt( <msg> )"
"Summary: plays a radio dialogue line and oversteps any previous radio dialogue being played (doesn't stop any previous dialogue being played )"
"Module: Utility"
"MandatoryArg: <msg>: the radio dialogue alias to play"
"Example: radio_dialogue_interupt( "shutup" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
radio_dialogue_interupt( msg )
{
	AssertEx( IsDefined( level.scr_radio[ msg ] ), "Tried to play radio dialogue " + msg + " that did not exist! Add it to level.scr_radio" );

	if ( !isdefined( level.player_radio_emitter ) )
	{
		ent = Spawn( "script_origin", ( 0, 0, 0 ) );
		ent LinkTo( level.player, "", ( 0, 0, 0 ), ( 0, 0, 0 ) );
		level.player_radio_emitter = ent;
	}

	level.player_radio_emitter play_sound_on_tag( level.scr_radio[ msg ], undefined, true );
}

/*
=============
///ScriptDocBegin
"Name: radio_dialogue_safe( <msg> )"
"Summary: trys to play a radio dialogue line - only plays if there is no other radio dialogue playing"
"Module: Utility"
"MandatoryArg: <msg>: the radio dialogue alias to play"
"Example: radio_dialogue_interupt( "shutup_please" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
radio_dialogue_safe( msg )
{
	return radio_dialogue( msg, .05 );
}

/////////////////////// DELETE ME ////////////////////////
radio_dialogue_queue( msg )
{
	radio_dialogue( msg );
}

// HUD ELEMENT STUFF
hint_create( text, background, backgroundAlpha )
{
	struct = SpawnStruct();
	if ( IsDefined( background ) && background == true )
		struct.bg = NewHudElem();
	struct.elm = NewHudElem();

	struct hint_position_internal( backgroundAlpha );
	// elm.label 		 = struct.text;
	// elm.debugtext 	 = struct.text;
	struct.elm SetText( text );

	return struct;
}

hint_delete()
{
	self notify( "death" );

	if ( IsDefined( self.elm ) )
		self.elm Destroy();
	if ( IsDefined( self.bg ) )
		self.bg Destroy();
}

hint_position_internal( bgAlpha )
{
	if ( level.console )
		self.elm.fontScale = 2;
	else
		self.elm.fontScale = 1.6;

	self.elm.x 			 = 0;
	self.elm.y		 	 = -40;
	self.elm.alignX 	 = "center";
	self.elm.alignY 	 = "bottom";
	self.elm.horzAlign 	 = "center";
	self.elm.vertAlign 	 = "middle";
	self.elm.sort		 = 1;
	self.elm.alpha		 = 0.8;

	if ( !isdefined( self.bg ) )
		return;

	self.bg.x 			 = 0;
	self.bg.y 			 = -40;
	self.bg.alignX 		 = "center";
	self.bg.alignY 		 = "middle";
	self.bg.horzAlign 	 = "center";
	self.bg.vertAlign 	 = "middle";
	self.bg.sort		 = -1;

	if ( level.console )
		self.bg SetShader( "popmenu_bg", 650, 52 );
	else
		self.bg SetShader( "popmenu_bg", 650, 42 );

	if ( !isdefined( bgAlpha ) )
		bgAlpha = 0.5;

	self.bg.alpha = bgAlpha;
}

/*
=============
///ScriptDocBegin
"Name: string( <num> )"
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
string( num )
{
	return( "" + num );
}

ignoreEachOther( group1, group2 )
{
	// these threatbias groups ignore each other
	AssertEx( ThreatBiasGroupExists( group1 ), "Tried to make threatbias group " + group1 + " ignore " + group2 + " but " + group1 + " does not exist!" );
	AssertEx( ThreatBiasGroupExists( group2 ), "Tried to make threatbias group " + group2 + " ignore " + group1 + " but " + group2 + " does not exist!" );
	SetIgnoreMeGroup( group1, group2 );
	SetIgnoreMeGroup( group2, group1 );
}

 /*
 =============
///ScriptDocBegin
"Name: add_global_spawn_function( <team> , <func> , <param1> , <param2> , <param3> )"
"Summary: All spawners of this team will run this function on spawn."
"Module: Utility"
"MandatoryArg: <team> : The team of the spawners that will run this function."
"MandatoryArg: <func> : The function to run."
"OptionalArg: <param1> : An optional parameter."
"OptionalArg: <param2> : An optional parameter."
"OptionalArg: <param3> : An optional parameter."
"Example: add_global_spawn_function( "axis", ::do_the_amazing_thing, some_amazing_parameter );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

add_global_spawn_function( team, function, param1, param2, param3 )
{
	AssertEx( IsDefined( level.spawn_funcs ), "Tried to add_global_spawn_function before calling _load" );

	func = [];
	func[ "function" ] = function;
	func[ "param1" ] = param1;
	func[ "param2" ] = param2;
	func[ "param3" ] = param3;

	level.spawn_funcs[ team ][ level.spawn_funcs[ team ].size ] = func;
}

 /*
 =============
///ScriptDocBegin
"Name: remove_global_spawn_function( <team> , <func> )"
"Summary: Remove this function from the global spawn functions for this team."
"Module: Utility"
"MandatoryArg: <team> : The team of the spawners that will no longer run this function."
"MandatoryArg: <func> : The function to remove."
"Example: remove_global_spawn_function( "allies", ::do_the_amazing_thing );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

remove_global_spawn_function( team, function )
{
	AssertEx( IsDefined( level.spawn_funcs ), "Tried to remove_global_spawn_function before calling _load" );

	array = [];
	for ( i = 0; i < level.spawn_funcs[ team ].size; i++ )
	{
		if ( level.spawn_funcs[ team ][ i ][ "function" ] != function )
		{
			array[ array.size ] = level.spawn_funcs[ team ][ i ];
		}
	}

	//assertEx( level.spawn_funcs[ team ].size != array.size, "Tried to remove a function from level.spawn_funcs, but that function didn't exist!" );
	level.spawn_funcs[ team ] = array;
}

 /*
 =============
///ScriptDocBegin
"Name: exists_global_spawn_function( <team> , <func> )"
"Summary: Check if thisfunction from the global spawn functions for this team exists. Returns true or false."
"Module: Utility"
"MandatoryArg: <team> : The team of the spawners that will no longer run this function."
"MandatoryArg: <func> : The function to remove."
"Example: if ( exists_global_spawn_function( "allies", ::do_the_amazing_thing ) )"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

exists_global_spawn_function( team, function )
{
	if ( !isdefined( level.spawn_funcs ) )
		return false;

	for ( i = 0; i < level.spawn_funcs[ team ].size; i++ )
	{
		if ( level.spawn_funcs[ team ][ i ][ "function" ] == function )
			return true;
	}

	return false;
}


 /*
 =============
///ScriptDocBegin
"Name: remove_spawn_function( <func> )"
"Summary: Remove this spawn function from this spawner."
"Module: Utility"
"MandatoryArg: <func1> : The function to remove."
"Example: spawner remove_spawn_function( ::do_the_amazing_thing );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

remove_spawn_function( function )
{
	AssertEx( !isalive( self ), "Tried to remove_spawn_function to a living guy." );
	AssertEx( IsSpawner( self ), "Tried to remove_spawn_function to something that isn't a spawner." );
	AssertEx( IsDefined( self.spawn_functions ), "Tried to remove_spawn_function before calling _load" );

	new_spawn_functions = [];

	foreach ( func_array in self.spawn_functions )
	{
		if ( func_array[ "function" ] == function )
			continue;

		new_spawn_functions[ new_spawn_functions.size ] = func_array;
	}


	self.spawn_functions = new_spawn_functions;
}

 /*
 =============
///ScriptDocBegin
"Name: add_spawn_function( <func> , <param1> , <param2> , <param3>, <param4>, <param5> )"
"Summary: Anything that spawns from this spawner will run this function. Anything."
"Module: Utility"
"MandatoryArg: <func1> : The function to run."
"OptionalArg: <param1> : An optional parameter."
"OptionalArg: <param2> : An optional parameter."
"OptionalArg: <param3> : An optional parameter."
"OptionalArg: <param4> : An optional parameter."
"OptionalArg: <param5> : An optional parameter."
"Example: spawner add_spawn_function( ::do_the_amazing_thing, some_amazing_parameter );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

add_spawn_function( function, param1, param2, param3, param4, param5 )
{
	AssertEx( !isalive( self ), "Tried to add_spawn_function to a living guy." );
	AssertEx( IsSpawner( self ), "Tried to add_spawn_function to something that isn't a spawner." );
	AssertEx( IsDefined( self.spawn_functions ), "Tried to add_spawn_function before calling _load" );

	foreach ( func_array in self.spawn_functions )
	{
		if ( func_array[ "function" ] == function )
			return;
	}

	func = [];
	func[ "function" ] = function;
	func[ "param1" ] = param1;
	func[ "param2" ] = param2;
	func[ "param3" ] = param3;
	func[ "param4" ] = param4;
	func[ "param5" ] = param5;

	self.spawn_functions[ self.spawn_functions.size ] = func;
}

/*
=============
///ScriptDocBegin
"Name: array_delete( <array> )"
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
array_delete( array )
{
	for ( i = 0; i < array.size; i++ )
	{
		array[ i ] Delete();
	}
}

/*
=============
///ScriptDocBegin
"Name: array_kill( <array> )"
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
array_kill( array )
{
	for ( i = 0; i < array.size; i++ )
	{
		array[ i ] kill();
	}
}
ignore_triggers( timer )
{
	// ignore triggers for awhile so others can trigger the trigger we're in.
	self endon( "death" );
	self.ignoreTriggers = true;
	if ( IsDefined( timer ) )
	{
		wait( timer );
	}
	else
	{
		wait( 0.5 );
	}
	self.ignoreTriggers = false;
}

/*
=============
///ScriptDocBegin
"Name: activate_trigger_with_targetname( <name> )"
"Summary: Notifies a trigger of 'trigger'"
"Module: Trigger"
"MandatoryArg: <name>: string get the entity that has a targetname of <name>"
"Example: activate_trigger_with_targetname( "red_team1" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
activate_trigger_with_targetname( msg )
{
	trigger = GetEnt( msg, "targetname" );
	trigger activate_trigger();
}

/*
=============
///ScriptDocBegin
"Name: activate_trigger_with_noteworthy( <name> )"
"Summary: Notifies a trigger of 'trigger'"
"Module: Trigger"
"MandatoryArg: <name>: string get the entity that has a script_noteworthy of <name>"
"Example: activate_trigger_with_noteworthy( "red_team1" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
activate_trigger_with_noteworthy( msg )
{
	trigger = GetEnt( msg, "script_noteworthy" );
	trigger activate_trigger();
}

/*
=============
///ScriptDocBegin
"Name: disable_trigger_with_targetname( <name> )"
"Summary: calls trigger_off() on a trigger with targetname of <name>"
"Module: Trigger"
"MandatoryArg: <name>: string get the entity that has a targetname of <name>"
"Example: disable_trigger_with_targetname( "red_team1" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_trigger_with_targetname( msg )
{
	trigger = GetEnt( msg, "targetname" );
	trigger trigger_off();
}

/*
=============
///ScriptDocBegin
"Name: disable_trigger_with_noteworthy( <name> )"
"Summary: calls trigger_off() on a trigger with script_noteworthy of <name>"
"Module: Trigger"
"MandatoryArg: <name>: string get the entity that has a script_noteworthy of <name>"
"Example: disable_trigger_with_noteworthy( "red_team1" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_trigger_with_noteworthy( msg )
{
	trigger = GetEnt( msg, "script_noteworthy" );
	trigger trigger_off();
}

/*
=============
///ScriptDocBegin
"Name: enable_trigger_with_targetname( <name> )"
"Summary: calls trigger_on() on a trigger with targetname of <name>"
"Module: Trigger"
"MandatoryArg: <name>: string get the entity that has a targetname of <name>"
"Example: enable_trigger_with_targetname( "red_team1" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_trigger_with_targetname( msg )
{
	trigger = GetEnt( msg, "targetname" );
	trigger trigger_on();
}

/*
=============
///ScriptDocBegin
"Name: enable_trigger_with_noteworthy( <name> )"
"Summary: calls trigger_on() on a trigger with script_noteworthy of <name>"
"Module: Trigger"
"MandatoryArg: <name>: string get the entity that has a script_noteworthy of <name>"
"Example: enable_trigger_with_noteworthy( "red_team1" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_trigger_with_noteworthy( msg )
{
	trigger = GetEnt( msg, "script_noteworthy" );
	trigger trigger_on();
}

/*
=============
///ScriptDocBegin
"Name: is_hero()"
"Summary: check to see if AI is a hero"
"Module: AI"
"Example: level.price ishero()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_hero()
{
	return IsDefined( level.hero_list[ get_ai_number() ] );
}

/*
=============
///ScriptDocBegin
"Name: get_ai_number()"
"Summary: gets an AI's ai number"
"Module: AI"
"Example: num = level.price get_ai_number()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_ai_number()
{
	if ( !isdefined( self.unique_id ) )
	{
		set_ai_number();
	}
	return self.unique_id;
}

/*
=============
///ScriptDocBegin
"Name: set_ai_number( <set_ai_number> )"
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
set_ai_number()
{
/*
=============
///ScriptFieldDocBegin
"Name: .unique_id"
"Summary: unique_id"
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

	self.unique_id = "ai" + level.ai_number;
	level.ai_number++;
}

/*
=============
///ScriptDocBegin
"Name: make_hero()"
"Summary: makes an AI a hero"
"Module: AI"
"Example: level.price make_hero()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
make_hero()
{
	level.hero_list[ self.unique_id ] = true;
}

/*
=============
///ScriptDocBegin
"Name: unmake_hero()"
"Summary: makes an AI not a hero"
"Module: Utility"
"Example: level.price unmake_hero()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
unmake_hero()
{
	level.hero_list[ self.unique_id ] = undefined;
}

/*
=============
///ScriptDocBegin
"Name: get_heroes()"
"Summary: returns an array of hero AI"
"Module: Utility"
"Example: level.heros =  get_heroes()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_heroes()
{
	array = [];
	ai = GetAIArray( "allies" );
	for ( i = 0; i < ai.size; i++ )
	{
		if ( ai[ i ] is_hero() )
			array[ array.size ] = ai[ i ];
	}
	return array;
}

/*
=============
///ScriptDocBegin
"Name: set_team_pacifist( <team> , <val> )"
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
set_team_pacifist( team, val )
{
	ai = GetAIArray( team );
	for ( i = 0; i < ai.size; i++ )
	{
		ai[ i ].pacifist = val;
	}
}

/*
=============
///ScriptDocBegin
"Name: replace_on_death()"
"Summary: Color friendlies that run this will be replaced when they die"
"Module: Utility"
"CallOn: A friendly"
"Example: red_shirt thread replace_on_death(); // poor guy"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
replace_on_death()
{
	// kill with either:
	// level notify( "kill_color_replacements" );
	// or
	// self notify( "_disable_reinforcement" );

	maps\_colors::colorNode_replace_on_death();
}

spawn_reinforcement( classname, color )
{
	maps\_colors::colorNode_spawn_reinforcement( classname, color );
}

clear_promotion_order()
{
	level.current_color_order = [];
}

set_promotion_order( deadguy, replacer )
{
	if ( !isdefined( level.current_color_order ) )
	{
		level.current_color_order = [];
	}

	deadguy = shortenColor( deadguy );
	replacer = shortenColor( replacer );

	level.current_color_order[ deadguy ] = replacer;

	// if there is no color order for the replacing color than
	// let script assume that it is meant to be replaced by
	// respawning guys
	if ( !isdefined( level.current_color_order[ replacer ] ) )
		set_empty_promotion_order( replacer );
}

set_empty_promotion_order( deadguy )
{
	if ( !isdefined( level.current_color_order ) )
	{
		level.current_color_order = [];
	}

	level.current_color_order[ deadguy ] = "none";
}

/*
=============
///ScriptDocBegin
"Name: remove_dead_from_array( <array> )"
"Summary: remove_dead_from_array"
"Module: Utility"
"Example: array = remove_dead_from_array( array )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
remove_dead_from_array( array )
{
	newarray = [];
	foreach ( item in array )
	{
		if ( !isalive( item ) )
			continue;
		newarray[ newarray.size ] = item;
	}
	return newarray;
}

/*
=============
///ScriptDocBegin
"Name: remove_heroes_from_array( <array> )"
"Summary: remove_heroes_from_array"
"Module: Utility"
"Example: array = remove_heroes_from_array( array )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
remove_heroes_from_array( array )
{
	newarray = [];
	for ( i = 0; i < array.size; i++ )
	{
		if ( array[ i ] is_hero() )
			continue;
		newarray[ newarray.size ] = array[ i ];
	}
	return newarray;
}

/*
=============
///ScriptDocBegin
"Name: remove_all_animnamed_guys_from_array( <array> )"
"Summary: remove_all_animnamed_guys_from_array"
"Module: Utility"
"Example: array = remove_all_animnamed_guys_from_array( array )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
remove_all_animnamed_guys_from_array( array )
{
	newarray = [];
	for ( i = 0; i < array.size; i++ )
	{
		if ( IsDefined( array[ i ].animname ) )
			continue;
		newarray[ newarray.size ] = array[ i ];
	}
	return newarray;
}


/*
=============
///ScriptDocBegin
"Name: remove_color_from_array( <array> , <color> )"
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
remove_color_from_array( array, color )
{
	newarray = [];
	for ( i = 0; i < array.size; i++ )
	{
		guy = array[ i ];
		if ( !isdefined( guy.script_forcecolor ) )
			continue;
		if ( guy.script_forcecolor == color )
			continue;
		newarray[ newarray.size ] = guy;
	}
	return newarray;
}

/*
=============
///ScriptDocBegin
"Name: remove_noteworthy_from_array( <array> , <noteworthy> )"
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
remove_noteworthy_from_array( array, noteworthy )
{
	newarray = [];
	for ( i = 0; i < array.size; i++ )
	{
		guy = array[ i ];
		if ( !isdefined( guy.script_noteworthy ) )
			continue;
		if ( guy.script_noteworthy == noteworthy )
			continue;
		newarray[ newarray.size ] = guy;
	}
	return newarray;
}

/*
=============
///ScriptDocBegin
"Name: get_closest_colored_friendly( <color> , <origin> )"
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
get_closest_colored_friendly( color, origin )
{
	allies = get_force_color_guys( "allies", color );
	allies = remove_heroes_from_array( allies );

	if ( !isdefined( origin ) )
		friendly_origin = level.player.origin;
	else
		friendly_origin = origin;

	return getClosest( friendly_origin, allies );
}

/*
=============
///ScriptDocBegin
"Name: remove_without_classname( <array> , <classname> )"
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
remove_without_classname( array, classname )
{
	newarray = [];
	for ( i = 0; i < array.size; i++ )
	{
		if ( !issubstr( array[ i ].classname, classname ) )
			continue;
		newarray[ newarray.size ] = array[ i ];
	}
	return newarray;
}

/*
=============
///ScriptDocBegin
"Name: remove_without_model( <array> , <model> )"
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
remove_without_model( array, model )
{
	newarray = [];
	for ( i = 0; i < array.size; i++ )
	{
		if ( !issubstr( array[ i ].model, model ) )
			continue;
		newarray[ newarray.size ] = array[ i ];
	}
	return newarray;
}

/*
=============
///ScriptDocBegin
"Name: get_closest_colored_friendly_with_classname( <color> , <classname> , <origin> )"
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
get_closest_colored_friendly_with_classname( color, classname, origin )
{
	allies = get_force_color_guys( "allies", color );
	allies = remove_heroes_from_array( allies );

	if ( !isdefined( origin ) )
		friendly_origin = level.player.origin;
	else
		friendly_origin = origin;

	allies = remove_without_classname( allies, classname );

	return getClosest( friendly_origin, allies );
}



/*
=============
///ScriptDocBegin
"Name: promote_nearest_friendly( <colorFrom> , <colorTo> )"
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
promote_nearest_friendly( colorFrom, colorTo )
{
	for ( ;; )
	{
		friendly = get_closest_colored_friendly( colorFrom );
		if ( !isalive( friendly ) )
		{
			wait( 1 );
			continue;
		}

		friendly set_force_color( colorTo );
		return;
	}
}

/*
=============
///ScriptDocBegin
"Name: instantly_promote_nearest_friendly( <colorFrom> , <colorTo> )"
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
instantly_promote_nearest_friendly( colorFrom, colorTo )
{
	for ( ;; )
	{
		friendly = get_closest_colored_friendly( colorFrom );
		if ( !isalive( friendly ) )
		{
			AssertEx( 0, "Instant promotion from " + colorFrom + " to " + colorTo + " failed!" );
			return;
		}

		friendly set_force_color( colorTo );
		return;
	}
}

/*
=============
///ScriptDocBegin
"Name: instantly_promote_nearest_friendly_with_classname( <colorFrom> , <colorTo> , <classname> )"
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
instantly_promote_nearest_friendly_with_classname( colorFrom, colorTo, classname )
{
	for ( ;; )
	{
		friendly = get_closest_colored_friendly_with_classname( colorFrom, classname );
		if ( !isalive( friendly ) )
		{
			AssertEx( 0, "Instant promotion from " + colorFrom + " to " + colorTo + " failed!" );
			return;
		}

		friendly set_force_color( colorTo );
		return;
	}
}

/*
=============
///ScriptDocBegin
"Name: promote_nearest_friendly_with_classname( <colorFrom> , <colorTo> , <classname> )"
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
promote_nearest_friendly_with_classname( colorFrom, colorTo, classname )
{
	for ( ;; )
	{
		friendly = get_closest_colored_friendly_with_classname( colorFrom, classname );
		if ( !isalive( friendly ) )
		{
			wait( 1 );
			continue;
		}

		friendly set_force_color( colorTo );
		return;
	}
}

/*
=============
///ScriptDocBegin
"Name: riotshield_lock_orientation( <yaw_angle> )"
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
riotshield_lock_orientation( yaw_angle )
{
	self OrientMode( "face angle", yaw_angle );
	self.lockOrientation = true;
}

/*
=============
///ScriptDocBegin
"Name: riotshield_unlock_orientation( <riotshield_unlock_orientation> )"
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
riotshield_unlock_orientation()
{
	self.lockOrientation = false;
}

/*
=============
///ScriptDocBegin
"Name: instantly_set_color_from_array_with_classname( <array> , <color> , <classname> )"
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
instantly_set_color_from_array_with_classname( array, color, classname )
{
	// the guy is removed from the array so the function can be run on the array again
	foundGuy = false;
	newArray = [];
	for ( i = 0; i < array.size; i++ )
	{
		guy = array[ i ];
		if ( foundGuy || !isSubstr( guy.classname, classname ) )
		{
			newArray[ newArray.size ] = guy;
			continue;
		}

		foundGuy = true;
		guy set_force_color( color );
	}
	return newArray;
}

/*
=============
///ScriptDocBegin
"Name: instantly_set_color_from_array( <array> , <color> )"
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
instantly_set_color_from_array( array, color )
{
	// the guy is removed from the array so the function can be run on the array again
	foundGuy = false;
	newArray = [];
	for ( i = 0; i < array.size; i++ )
	{
		guy = array[ i ];
		if ( foundGuy )
		{
			newArray[ newArray.size ] = guy;
			continue;
		}

		foundGuy = true;
		guy set_force_color( color );
	}
	return newArray;
}

/*
=============
///ScriptDocBegin
"Name: wait_for_script_noteworthy_trigger( <msg> )"
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
wait_for_script_noteworthy_trigger( msg )
{
	wait_for_trigger( msg, "script_noteworthy" );
}

/*
=============
///ScriptDocBegin
"Name: wait_for_targetname_trigger( <msg> )"
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
wait_for_targetname_trigger( msg )
{
	wait_for_trigger( msg, "targetname" );
}

/*
=============
///ScriptDocBegin
"Name: wait_for_flag_or_timeout( <msg> , <timer> )"
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
wait_for_flag_or_timeout( msg, timer )
{
	if ( flag( msg ) )
		return;

	ent = SpawnStruct();
	ent thread ent_waits_for_level_notify( msg );
	ent thread ent_times_out( timer );
	ent waittill( "done" );
}

/*
=============
///ScriptDocBegin
"Name: wait_for_notify_or_timeout( <msg> , <timer> )"
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
wait_for_notify_or_timeout( msg, timer )
{
	ent = SpawnStruct();
	ent thread ent_waits_for_notify( self, msg );
	ent thread ent_times_out( timer );
	ent waittill( "done" );
}

/*
=============
///ScriptDocBegin
"Name: wait_for_trigger_or_timeout( <timer> )"
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
wait_for_trigger_or_timeout( timer )
{
	ent = SpawnStruct();
	ent thread ent_waits_for_trigger( self );
	ent thread ent_times_out( timer );
	ent waittill( "done" );
}

/*
=============
///ScriptDocBegin
"Name: wait_for_either_trigger( <msg1> , <msg2> )"
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
wait_for_either_trigger( msg1, msg2 )
{
	ent = SpawnStruct();
	array = [];
	array = array_combine( array, GetEntArray( msg1, "targetname" ) );
	array = array_combine( array, GetEntArray( msg2, "targetname" ) );
	for ( i = 0; i < array.size; i++ )
	{
		ent thread ent_waits_for_trigger( array[ i ] );
	}

	ent waittill( "done" );
}


/*
=============
///ScriptDocBegin
"Name: dronespawn_bodyonly( <spawner> )"
"Summary: Create a drone body, doesn't take damage, die, etc."
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
dronespawn_bodyonly( spawner )
{
	drone = maps\_spawner::spawner_dronespawn( spawner );
	Assert( IsDefined( drone ) );

	return drone;
}


/*
=============
///ScriptDocBegin
"Name: dronespawn( <spawner> )"
"Summary: Create a drone, make it behave like AI"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
dronespawn( spawner )
{
	if ( !isdefined( spawner ) )
		spawner = self;
	drone = maps\_spawner::spawner_dronespawn( spawner );
	Assert( IsDefined( drone ) );

	AssertEx( IsDefined( level.drone_spawn_func ), "You need to put maps\_drone_civilian::init(); OR maps\_drone_ai::init(); in your level script! Use the civilian version if your drone is a civilian and the _ai version if it's a friendly or enemy." );
	drone [[ level.drone_spawn_func ]]();

	drone.spawn_funcs = spawner.spawn_functions;
	drone thread maps\_spawner::run_spawn_functions();

	return drone;
}

/*
=============
///ScriptDocBegin
"Name: makerealai( <drone> )"
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
makerealai( drone )
{
	return maps\_spawner::spawner_makerealai( drone );
}

/*
=============
///ScriptDocBegin
"Name: get_trigger_flag( <get_trigger_flag> )"
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
get_trigger_flag()
{
	if ( IsDefined( self.script_flag ) )
	{
		return self.script_flag;
	}

	if ( IsDefined( self.script_noteworthy ) )
	{
		return self.script_noteworthy;
	}

	AssertEx( 0, "Flag trigger at " + self.origin + " has no script_flag set." );
}


set_default_pathenemy_settings()
{
	self.pathenemylookahead = 192;
	self.pathenemyfightdist = 192;
}

/*
=============
///ScriptDocBegin
"Name: cqb_walk( <on_or_off> )"
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
cqb_walk( on_or_off )// ( deprecated )
{
	if ( on_or_off == "on" )
	{
		self enable_cqbwalk();
	}
	else
	{
		Assert( on_or_off == "off" );
		self disable_cqbwalk();
	}
}

/*
=============
///ScriptDocBegin
"Name: enable_cqbwalk( <autoEnabled> )"
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
enable_cqbwalk( autoEnabled )
{
	if ( !isdefined( autoEnabled ) )
		self.cqbEnabled = true;

	self.cqbwalking = true;
	self.turnRate = 0.2;
	level thread animscripts\cqb::findCQBPointsOfInterest();

	/#
	self thread animscripts\cqb::CQBDebug();
	#/
}

/*
=============
///ScriptDocBegin
"Name: disable_cqbwalk( <disable_cqbwalk> )"
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
disable_cqbwalk()
{
	self.cqbwalking = undefined;
	self.cqbEnabled = undefined;
	self.turnRate = 0.3;
	self.cqb_point_of_interest = undefined;

	/#
	self notify( "end_cqb_debug" );
	#/
}

/*
=============
///ScriptDocBegin
"Name: enable_readystand( )"
"Summary: Set actor to use a ready idle position."
"Module: Entity"
"CallOn: An entity"
"Example: self enable_readystand()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_readystand()
{
	self.bUseReadyIdle = true;
}

/*
=============
///ScriptDocBegin
"Name: disable_readystand( )"
"Summary: Set actor to not use a ready idle position."
"Module: Entity"
"CallOn: An entity"
"Example: self disable_readystand()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_readystand()
{
	self.bUseReadyIdle = undefined;
}

/*
=============
///ScriptDocBegin
"Name: cqb_aim( <the_target> )"
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
cqb_aim( the_target )
{
	if ( !isdefined( the_target ) )
	{
		self.cqb_target = undefined;
	}
	else
	{
		self.cqb_target = the_target;

		if ( !isdefined( the_target.origin ) )
			AssertMsg( "target passed into cqb_aim does not have an origin!" );
	}
}


/*
=============
///ScriptDocBegin
"Name: set_force_cover( <val> )"
"Summary: true to be suppressed, false to turn off
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_force_cover( val )
{
 	AssertEx( !isdefined( val ) || val == false || val == true, "invalid force cover set on guy" );
	AssertEx( IsAlive( self ), "Tried to set force cover on a dead guy" );
	if ( IsDefined( val ) && val )
		self.forceSuppression = true;
	else
		self.forceSuppression = undefined;
}

/*
=============
///ScriptDocBegin
"Name: do_in_order( <func1> , <param1> , <func2> , <param2> )"
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
do_in_order( func1, param1, func2, param2 )
{
	if ( IsDefined( param1 ) )
		[[ func1 ]]( param1 );
	else
		[[ func1 ]]();
	if ( IsDefined( param2 ) )
		[[ func2 ]]( param2 );
	else
		[[ func2 ]]();
}

scrub()
{
	// sets an AI to default settings, ignoring the .script_ values on him.
	self maps\_spawner::scrub_guy();
}

/*
=============
///ScriptDocBegin
"Name: send_notify( <msg> , <optional_param> )"
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
send_notify( msg, optional_param )
{
	// functionalized so it can be function pointer'd
	if ( IsDefined( optional_param ) )
		self notify( msg, optional_param );
	else
		self notify( msg );
}


/*
=============
///ScriptDocBegin
"Name: waittill_match_or_timeout( <msg> , <match>, <timer> )"
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
waittill_match_or_timeout( msg, match, timer )
{
	ent = SpawnStruct();
	ent endon( "complete" );
	ent delayThread( timer, ::send_notify, "complete" );

	self waittillmatch( msg, match );
}


deleteEnt( ent )
{
	// created so entities can be deleted using array_thread
	ent notify( "deleted" );
	ent Delete();
}


/*
=============
///ScriptDocBegin
"Name: first_touch( <ent> )"
"Summary: Returns true the first time this check is run against an entity."
"Module: Utility"
"CallOn: An entity that notifies trigger to a trigger."
"MandatoryArg: <ent>: The ent that caused trigger to be notified "
"Example: if ( first_touch( guy ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
first_touch( ent )
{
	if ( !isdefined( self.touched ) )
		self.touched = [];

	AssertEx( IsDefined( ent ), "Ent is not defined!" );
	AssertEx( IsDefined( ent.unique_id ), "Ent has no unique_id" );

	if ( IsDefined( self.touched[ ent.unique_id ] ) )
		return false;

	self.touched[ ent.unique_id ] = true;
	return true;
}

/*
=============
///ScriptDocBegin
"Name: getanim( <anime> )"
"Summary: Gets the animation referenced by the string for the animname of the caller"
"Module: Animation"
"CallOn: An entity that has an animname."
"MandatoryArg: <anime> The animation scene. "
"Example: animation = guy getanim( "run" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
getanim( anime )
{
	AssertEx( IsDefined( self.animname ), "Called getanim on a guy with no animname" );
	AssertEx( IsDefined( level.scr_anim[ self.animname ][ anime ] ), "Called getanim on an inexistent anim" );
	return level.scr_anim[ self.animname ][ anime ];
}

/*
=============
///ScriptDocBegin
"Name: hasanim( <anime> )"
"Summary: Returns whether a guy has the animation referenced by the string for the animname of the caller."
"Module: Animation"
"CallOn: An entity that has an animname."
"MandatoryArg: <anime> The animation scene. "
"Example: if( guy hasanim( "run" ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
hasanim( anime )
{
	AssertEx( IsDefined( self.animname ), "Called getanim on a guy with no animname" );
	return IsDefined( level.scr_anim[ self.animname ][ anime ] );
}

/*
=============
///ScriptDocBegin
"Name: getanim_from_animname( <anime> , <animname> )"
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
getanim_from_animname( anime, animname )
{
	AssertEx( IsDefined( animname ), "Must supply an animname" );
	AssertEx( IsDefined( level.scr_anim[ animname ][ anime ] ), "Called getanim on an inexistent anim" );
	return level.scr_anim[ animname ][ anime ];
}

/*
=============
///ScriptDocBegin
"Name: getanim_generic( <anime> )"
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
getanim_generic( anime )
{
	AssertEx( IsDefined( level.scr_anim[ "generic" ][ anime ] ), "Called getanim_generic on an inexistent anim" );
	return level.scr_anim[ "generic" ][ anime ];
}

/*
=============
///ScriptDocBegin
"Name: add_hint_string( <name> , <string> , <optionalFunc> )"
"Summary: Adds a hint string that will be displayed with display_hint. The hint runs until the function returns true"
"Module: Hint"
"MandatoryArg: <name>: Name of the hint"
"MandatoryArg: <string>: String to display for the hint"
"MandatoryArg: <optionalFunc>: Draw the string until this function returns true."
// Press^3 [{+actionslot 1}] ^7to disable Night Vision Goggles.
"Example: add_hint_string( "disable_nvg", &"SCRIPT_NIGHTVISION_STOP_USE", maps\_nightvision::should_break_disable_nvg_print );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_hint_string( name, string, optionalFunc )
{
	if ( !isdefined( level.trigger_hint_string ) )
	{
		level.trigger_hint_string = [];
		level.trigger_hint_func = [];
	}

	AssertEx( IsDefined( name ), "Set a name for the hint string. This should be the same as the script_hint on the trigger_hint." );
	AssertEx( IsDefined( string ), "Set a string for the hint string. This is the string you want to appear when the trigger is hit." );
	AssertEx( !isdefined( level.trigger_hint_string[ name ] ), "Tried to redefine hint " + name );

	level.trigger_hint_string[ name ] = string;
	PreCacheString( string );
	if ( IsDefined( optionalFunc ) )
	{
		level.trigger_hint_func[ name ] = optionalFunc;
	}
}

show_hint( struct )
{
	AssertEx( IsDefined( struct.string ), "Need a localized string associated with the hint" );
	thread ShowHintPrint_struct( struct );
}

hide_hint( struct )
{
	struct.timeout = true;
}

fire_radius( origin, radius )
{
	/#
	if ( level.createFX_enabled )
		return;
	#/

	trigger = Spawn( "trigger_radius", origin, 0, radius, 48 );

	for ( ;; )
	{
		trigger waittill( "trigger", other );
		AssertEx( IsPlayer( other ), "Tried to burn a non player in a fire" );
		level.player DoDamage( 5, origin );
	}
}

clearThreatBias( group1, group2 )
{
	SetThreatBias( group1, group2, 0 );
	SetThreatBias( group2, group1, 0 );
}

scr_println( msg )
{
	// so println can be called from a function pointer
	PrintLn( msg );
}

// use in moderation!
ThrowGrenadeAtPlayerASAP()
{
	animscripts\combat_utility::ThrowGrenadeAtPlayerASAP_combat_utility();
}


/*
=============
///ScriptDocBegin
"Name: array_combine_keys( <array1> , <keys> , <keys> )"
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
array_combine_keys( array1, array2 )// mashes them in. array 2 will overwrite like keys, this works for what I'm using it for - Nate.
{
	if ( !array1.size )
		return array2;
	keys = GetArrayKeys( array2 );
	for ( i = 0; i < keys.size; i++ )
		array1[ keys[ i ] ] = array2[ keys[ i ] ];
	return array1;
}

/*
=============
///ScriptDocBegin
"Name: set_ignoreSuppression( <val> )"
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
set_ignoreSuppression( val )
{
	self.ignoreSuppression = val;
}

/*
=============
///ScriptDocBegin
"Name: set_goalradius( <radius> )"
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
set_goalradius( radius )
{
	self.goalradius = radius;
}

try_forever_spawn()
{
	export = self.export;
	for ( ;; )
	{
		AssertEx( IsDefined( self ), "Spawner with export " + export + " was deleted." );
		guy = self DoSpawn();
		if ( spawn_failed( guy ) )
		{
			wait( 1 );
			continue;
		}
		return guy;
	}
}

/*
=============
///ScriptDocBegin
"Name: set_allowdeath( <val> )"
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
set_allowdeath( val )
{
	self.allowdeath = val;
}

/*
=============
///ScriptDocBegin
"Name: set_run_anim( <anime> , <alwaysRunForward> )"
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
set_run_anim( anime, alwaysRunForward )
{
	AssertEx( IsDefined( anime ), "Tried to set run anim but didn't specify which animation to ues" );
	AssertEx( IsDefined( self.animname ), "Tried to set run anim on a guy that had no anim name" );
	AssertEx( IsDefined( level.scr_anim[ self.animname ][ anime ] ), "Tried to set run anim but the anim was not defined in the maps _anim file" );

	//this is good for slower run animations like patrol walks
	if ( IsDefined( alwaysRunForward ) )
		self.alwaysRunForward = alwaysRunForward;
	else
		self.alwaysRunForward = true;

	self disable_turnAnims();
	self.run_overrideanim = level.scr_anim[ self.animname ][ anime ];
	self.walk_overrideanim = self.run_overrideanim;
}

/*
=============
///ScriptDocBegin
"Name: set_dog_walk_anim( <set_dog_walk_anim> )"
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
set_dog_walk_anim()
{
	AssertEx( self.type == "dog" );

	self.a.movement = "walk";
	self.disablearrivals = true;
	self.disableexits = true;
	self.script_nobark = 1;
}


/*
=============
///ScriptDocBegin
"Name: set_combat_stand_animset( <fire>, <aim_straight>, <idle>, <reload> )"
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
set_combat_stand_animset( fire_anim, aim_straight, idle_anim, reload_anim )
{
	self animscripts\animset::init_animset_custom_stand( fire_anim, aim_straight, idle_anim, reload_anim );
}


/*
=============
///ScriptDocBegin
"Name: set_move_animset( <move_mode>, <move_anim>, <sprint_anim> )"
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
set_move_animset( move_mode, move_anim, sprint_anim )
{
	AssertEx( IsDefined( anim.animsets.move[ move_mode ] ), "Default anim set is not defined" );

	// init with defaults
	animset = anim.animsets.move[ move_mode ];

	if ( IsArray( move_anim ) )
	{
		Assert( move_anim.size == 4 );

		animset[ "straight" ] = move_anim[ 0 ];

		animset[ "move_f" ] = move_anim[ 0 ];
		animset[ "move_l" ] = move_anim[ 1 ];
		animset[ "move_r" ] = move_anim[ 2 ];
		animset[ "move_b" ] = move_anim[ 3 ];
	}
	else
	{
		animset[ "straight" ] = move_anim;
		animset[ "move_f" ] = move_anim;
	}

	if ( IsDefined( sprint_anim ) )
		animset[ "sprint" ] = sprint_anim;

	self.customMoveAnimSet[ move_mode ] = animset;
}


/*
=============
///ScriptDocBegin
"Name: set_generic_idle_anim( <anime> )"
"Summary: Sets the override idle anim, needs to be set each time he idles"
"Module: Utility"
"CallOn: An ai"
"MandatoryArg: <anime>: The idle scene "
"Example: guy set_idle_anim( "yay" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_generic_idle_anim( anime )
{
	AssertEx( IsDefined( anime ), "Tried to set generic idle but didn't specify which animation to ues" );
	AssertEx( IsDefined( level.scr_anim[ "generic" ][ anime ] ), "Tried to set generic run anim but the anim was not defined in the maps _anim file" );

	idleAnim = level.scr_anim[ "generic" ][ anime ];

	if ( IsArray( idleAnim ) )
		self.specialIdleAnim = idleAnim;
	else
		self.specialIdleAnim[ 0 ] = idleAnim;
}

/*
=============
///ScriptDocBegin
"Name: set_idle_anim( <anime> )"
"Summary: Sets the override idle anim, needs to be set each time he idles"
"Module: Utility"
"CallOn: An ai"
"MandatoryArg: <anime>: The idle scene "
"Example: guy set_idle_anim( "yay" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_idle_anim( anime )
{
	AssertEx( IsDefined( self.animname ), "No animname!" );
	AssertEx( IsDefined( anime ), "Tried to set idle anim but didn't specify which animation to ues" );
	AssertEx( IsDefined( level.scr_anim[ self.animname ][ anime ] ), "Tried to set generic run anim but the anim was not defined in the maps _anim file" );

	idleAnim = level.scr_anim[ self.animname ][ anime ];

	if ( IsArray( idleAnim ) )
		self.specialIdleAnim = idleAnim;
	else
		self.specialIdleAnim[ 0 ] = idleAnim;
}


/*
=============
///ScriptDocBegin
"Name: clear_generic_idle_anim()"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
clear_generic_idle_anim()
{
	self.specialIdleAnim = undefined;
	self notify( "stop_specialidle" );
}


/*
=============
///ScriptDocBegin
"Name: set_generic_run_anim( <anime> , <alwaysRunForward> )"
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
set_generic_run_anim( anime, alwaysRunForward )
{
	set_generic_run_anim_array( anime, undefined, alwaysRunForward );
}

/*
=============
///ScriptDocBegin
"Name: clear_generic_run_anim()"
"Summary: clear the generic run anims set by set_generic_run_anim "
"Module: Entity"
"CallOn: An entity"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

clear_generic_run_anim()
{
	self notify( "movemode" );
	self enable_turnAnims();
	self.run_overrideanim = undefined;
	self.walk_overrideanim = undefined;
}


/*
=============
///ScriptDocBegin
"Name: set_generic_run_anim_array( <array>, <weights>, <alwaysRunForward> )"
"Summary: "
"Module: AI"
"CallOn: An AI"
"MandatoryArg: <string anime>: index to an array of run cycles (run cycle and twitches) to pass"
"OptionalArg: <string weights>: relative weights of animation variations, if not specified, all are equal"
"OptionalArg: <alwaysRunForward>: bool to always face in the direction of motion or not"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_generic_run_anim_array( anime, weights, alwaysRunForward )
{
	AssertEx( IsDefined( anime ), "Tried to set generic run anim but didn't specify which animation to ues" );
	AssertEx( IsDefined( level.scr_anim[ "generic" ][ anime ] ), "Tried to set generic run anim but the anim was not defined in the maps _anim file" );
	AssertEx( !isdefined(weights) || isdefined(level.scr_anim[ "generic" ][weights]), "weights needs to be a valid entry in level.scr_anim" );
	//weights has to be undefined or an array
	//we saw improper use passing in a 2nd animation as the weights param
	AssertEx( !isdefined(weights) || isarray(level.scr_anim[ "generic" ][weights]), "weights needs to be an array of animation weights (ascending order)" );
	
	//if you dont pass in an array of animations you should not be passing in a weights param
	AssertEx( isarray(level.scr_anim[ "generic" ][anime]) 
		|| !isdefined(weights), "its not valid to pass in a weights param and not an array of anims to run" );
	
	//if you do pass in weights it needs to match the size of the anime array that is passed in
	AssertEx( !isdefined(weights) || (level.scr_anim[ "generic" ][weights].size == level.scr_anim[ "generic" ][anime].size), "the weights array must equal the size of the anims array" );
	
	self notify( "movemode" );

	//this is good for slower run animations like patrol walks
	if ( !isdefined( alwaysRunForward ) || alwaysRunForward )
		self.alwaysRunForward = true;
	else
		self.alwaysRunForward = undefined;

	self disable_turnAnims();
	self.run_overrideanim = level.scr_anim[ "generic" ][ anime ];
	self.walk_overrideanim = self.run_overrideanim;

	if ( IsDefined( weights ) )
	{
		self.run_override_weights = level.scr_anim[ "generic" ][ weights ];
		self.walk_override_weights = self.run_override_weights;
	}
	else
	{
		self.run_override_weights = undefined;
		self.walk_override_weights = undefined;
	}
}

/*
=============
///ScriptDocBegin
"Name: set_run_anim_array( <array>, <weights>, <alwaysRunForward> )"
"Summary: "
"Module: AI"
"CallOn: An AI"
"MandatoryArg: <string anime>: index to an array of run cycles (run cycle and twitches) to pass"
"OptionalArg: <string weights>: relative weights of animation variations, if not specified, all are equal"
"OptionalArg: <alwaysRunForward>: bool to always face in the direction of motion or not"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_run_anim_array( anime, weights, alwaysRunForward )
{
	AssertEx( IsDefined( anime ), "Tried to set generic run anim but didn't specify which animation to ues" );
	AssertEx( IsDefined( self.animname ), "Tried to set run anim on a guy that had no anim name" );
	AssertEx( IsDefined( level.scr_anim[ self.animname ][ anime ] ), "Tried to set run anim but the anim was not defined in the maps _anim file" );
	self notify( "movemode" );

	//this is good for slower run animations like patrol walks
	if ( !isdefined( alwaysRunForward ) || alwaysRunForward )
		self.alwaysRunForward = true;
	else
		self.alwaysRunForward = undefined;

	self disable_turnAnims();
	self.run_overrideanim = level.scr_anim[ self.animname ][ anime ];
	self.walk_overrideanim = self.run_overrideanim;

	if ( IsDefined( weights ) )
	{
		self.run_override_weights = level.scr_anim[ self.animname ][ weights ];
		self.walk_override_weights = self.run_override_weights;
	}
	else
	{
		self.run_override_weights = undefined;
		self.walk_override_weights = undefined;
	}
}


/*
=============
///ScriptDocBegin
"Name: clear_run_anim( <clear_run_anim> )"
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
clear_run_anim()
{
	self notify( "clear_run_anim" );
	self notify( "movemode" );

	if ( self.type == "dog" )
	{
		self.a.movement = "run";
		self.disablearrivals = false;
		self.disableexits = false;
		self.script_nobark = undefined;
		return;
	}

	if ( !isdefined( self.casual_killer ) )
		self enable_turnAnims();

	self.alwaysRunForward = undefined;
	self.run_overrideanim = undefined;
	self.walk_overrideanim = undefined;

	self.run_override_weights = undefined;
	self.walk_override_weights = undefined;
}

debugvar( msg, timer )
{
	SetDvarIfUninitialized( msg, timer );
	return GetDvarFloat( msg );
}

physicsjolt_proximity( outer_radius, inner_radius, force )
{
	// Usage: <entity > thread physicjolt_proximity( 400, 256, ( 0, 0, 0.1 ) );

	self endon( "death" );
	self endon( "stop_physicsjolt" );

	if ( !isdefined( outer_radius ) || !isdefined( inner_radius ) || !isdefined( force ) )
	{
		outer_radius = 400;
		inner_radius = 256;
		force = ( 0, 0, 0.075 );	// no direction on this one.
	}

	fade_distance = outer_radius * outer_radius;

	fade_speed = 3;
	base_force = force;

	while ( true )
	{
		wait 0.1;

		force = base_force;

		if ( self.code_classname == "script_vehicle" )
		{
			speed = self Vehicle_GetSpeed();
			if ( speed < fade_speed )
			{
				scale = speed / fade_speed;
				force = ( base_force* scale );
			}
		}

		dist = DistanceSquared( self.origin, level.player.origin );
		scale = fade_distance / dist;
		if ( scale > 1 )
			scale = 1;
		force = ( force* scale );
		total_force = force[ 0 ] + force[ 1 ] + force[ 2 ];

		if ( total_force > 0.025 )
			PhysicsJitter( self.origin, outer_radius, inner_radius, force[ 2 ], force[ 2 ] * 2.0 );
	}
}

/*
=============
///ScriptDocBegin
"Name: set_goal_entity( <ent> )"
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
set_goal_entity( ent )
{
	self SetGoalEntity( ent );
}

/*
=============
///ScriptDocBegin
"Name: activate_trigger( <name> , <type> )"
"Summary: Notifies a trigger of 'trigger'"
"Module: Trigger"
"MandatoryArg: <name>: string to get the entity with"
"MandatoryArg: <type>: type that string refers to (ie. targetname, script_noteworthy, target )"
"Example: activate_trigger( "red_team1", "targetname" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
activate_trigger( name, type, triggeringEnt )
{
	if ( !isdefined( name ) )
		self activate_trigger_process( triggeringEnt );
	else
		array_thread( GetEntArray( name, type ), ::activate_trigger_process, triggeringEnt );
}

activate_trigger_process( triggeringEnt )
{
	AssertEx( !isdefined( self.trigger_off ), "Tried to activate trigger that is OFF( either from trigger_off or from flags set on it through shift - G menu" );

	if ( IsDefined( self.script_color_allies ) )
	{
		// so we don't run activate_color_trigger twice, we set this var
		self.activated_color_trigger = true;
		maps\_colors::activate_color_trigger( "allies" );
	}

	if ( IsDefined( self.script_color_axis ) )
	{
		// so we don't run activate_color_trigger twice, we set this var
		self.activated_color_trigger = true;
		maps\_colors::activate_color_trigger( "axis" );
	}

	self notify( "trigger", triggeringEnt );

	/*
	if ( self.classname != "trigger_friendlychain" )
		return;

	node = GetNode( self.target, "targetname" );
	AssertEx( IsDefined( node ), "Trigger_friendlychain at " + self.origin + " doesn't target a node" );
	level.player SetFriendlyChain( node );
	*/
}

 /*
 =============
///ScriptDocBegin
"Name: self_delete()"
"Summary: Just calls the Delete() script command on self. Reason for this is so that we can use array_thread to delete entities"
"Module: Entity"
"CallOn: An entity"
"Example: ai[ 0 ] thread self_delete();"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
self_delete()
{
	self Delete();
}

remove_noColor_from_array( ai )
{
	newarray = [];
	for ( i = 0; i < ai.size; i++ )
	{
		guy = ai[ i ];
		if ( guy has_color() )
			newarray[ newarray.size ] = guy;
	}

	return newarray;
}

has_color()
{
	// can lose color during the waittillframeend in left_color_node
	if ( self maps\_colors::get_team() == "axis" )
	{
		return IsDefined( self.script_color_axis ) || IsDefined( self.script_forcecolor );
	}

	return IsDefined( self.script_color_allies ) || IsDefined( self.script_forcecolor );
}

clear_colors()
{
	clear_team_colors( "axis" );
	clear_team_colors( "allies" );
}

clear_team_colors( team )
{
	level.currentColorForced[ team ][ "r" ] = undefined;
	level.currentColorForced[ team ][ "b" ] = undefined;
	level.currentColorForced[ team ][ "c" ] = undefined;
	level.currentColorForced[ team ][ "y" ] = undefined;
	level.currentColorForced[ team ][ "p" ] = undefined;
	level.currentColorForced[ team ][ "o" ] = undefined;
	level.currentColorForced[ team ][ "g" ] = undefined;
}


/*
=============
///ScriptDocBegin
"Name: get_script_palette( <get_script_palette> )"
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
get_script_palette()
{
	rgb = [];
	rgb[ "r" ] = ( 1, 0, 0 );
	rgb[ "o" ] = ( 1, 0.5, 0 );
	rgb[ "y" ] = ( 1, 1, 0 );
	rgb[ "g" ] = ( 0, 1, 0 );
	rgb[ "c" ] = ( 0, 1, 1 );
	rgb[ "b" ] = ( 0, 0, 1 );
	rgb[ "p" ] = ( 1, 0, 1 );
	return rgb;
}

 /*
 =============
///ScriptDocBegin
"Name: notify_delay( <notify_string> , <delay> )"
"Summary: Notifies self the string after waiting the specified delay time"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <notify_string> : The string to notify"
"MandatoryArg: <delay> : Time to wait( in seconds ) before sending the notify."
"Example: vehicle notify_delay( "start_to_smoke", 3.5 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
notify_delay( sNotifyString, fDelay )
{
	Assert( IsDefined( self ) );
	Assert( IsDefined( sNotifyString ) );
	Assert( IsDefined( fDelay ) );

	self endon( "death" );
	if ( fDelay > 0 )
		wait fDelay;
	if ( !isdefined( self ) )
		return;
	self notify( sNotifyString );
}

 /*
 =============
///ScriptDocBegin
"Name: gun_remove()"
"Summary: Removed the gun from the given AI. Often used for scripted sequences where you dont want the AI to carry a weapon."
"Module: AI"
"CallOn: An AI"
"Example: level.price gun_remove();"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
gun_remove()
{
	if ( IsAI( self ) )		// regular AI
		self animscripts\shared::placeWeaponOn( self.weapon, "none" );
	else					// Drone
		self Detach( GetWeaponModel( self.weapon ), "tag_weapon_right" );
}


 /*
 =============
///ScriptDocBegin
"Name: gun_recall()"
"Summary: Give the AI his gun back."
"Module: AI"
"CallOn: An AI"
"Example: level.price gun_recall();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
 */
gun_recall()
{
	if ( IsAI( self ) )		// regular AI
		self animscripts\shared::placeWeaponOn( self.weapon, "right" );
	else					// Drone
		self Attach( GetWeaponModel( self.weapon ), "tag_weapon_right" );
}


 /*
 =============
///ScriptDocBegin
"Name: place_weapon_on( <weapon>, <location> )"
"Summary: Equip a wepaon on an AI."
"Module: AI"
"CallOn: An AI"
"MandatoryArg: <weapon> : The name of the weapon to equip"
"MandatoryArg: <> : Slot to store the weapon in. 'right', 'left', 'chest', or 'back'."
"Example: level.price place_weapon_on( "at4", "back" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
 place_weapon_on( weapon, location )
 {
	Assert( IsAI( self ) );

	if ( !AIHasWeapon( weapon ) )
		animscripts\init::initWeapon( weapon );

	animscripts\shared::placeWeaponOn( weapon, location );
 }


 /*
 =============
///ScriptDocBegin
"Name: forceUseWeapon( <newWeapon>, <targetSlot> )"
"Summary: Forces the AI to switch to a specified weapon."
"Module: AI"
"CallOn: An AI"
"MandatoryArg: <newWeapon> : The name of the weapon to use/give"
"MandatoryArg: <target slot> : Slot to store the weapon in. primary, secondary or sidearm."
"Example: level.price forceUseWeapon( "glock", "sidearm" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
forceUseWeapon( newWeapon, targetSlot )
{
	Assert( IsDefined( newWeapon ) );
	Assert( newWeapon != "none" );
	Assert( IsDefined( targetSlot ) );
	AssertEx( ( targetSlot == "primary" ) || ( targetSlot == "secondary" ) || ( targetSlot == "sidearm" ), "Target slot is either primary, secondary or sidearm." );

	// Setup the weaponInfo if it wasn't already done
	if ( !animscripts\init::isWeaponInitialized( newWeapon ) )
		animscripts\init::initWeapon( newWeapon );

	// Figure out whether the current and target weapons are side arms, and which slot to go to
	hasWeapon = ( self.weapon != "none" );
	isCurrentSideArm = usingSidearm();
	isNewSideArm = ( targetSlot == "sidearm" );
	isNewSecondary = ( targetSlot == "secondary" );

	// If we have a weapon and we're not replacing it with one of the same "type", we need to hoslter it first
	if ( hasWeapon && ( isCurrentSideArm != isNewSideArm ) )
	{
		Assert( self.weapon != newWeapon );

		// Based on the current weapon - Hide side arms completely, and holster based on the new target otherwise
		if ( isCurrentSideArm )
			holsterTarget = "none";
		else if ( isNewSecondary )
			holsterTarget = "back";
		else
			holsterTarget = "chest";
		animscripts\shared::placeWeaponOn( self.weapon, holsterTarget );

		// Remember we switched out of that weapon
		self.lastWeapon = self.weapon;
	}
	else
	{
		// We didn't have a weapon before, or we're going to loose the one we had, so reset the lastWeapon.
		self.lastWeapon = newWeapon;
	}

	// Put the new weapon in hand
	animscripts\shared::placeWeaponOn( newWeapon, "right" );

	// Replace the equipped weapon slot of the same type with the new weapon ( could stay the same, too )
	// If the AI was using a secondary, replace that slot instead of primary
	if ( isNewSideArm )
		self.sideArm = newWeapon;
	else if ( isNewSecondary )
		self.secondaryweapon = newWeapon;
	else
		self.primaryweapon = newWeapon;

	// Set our current weapon to the new one
	self.weapon = newWeapon;
	self.bulletsinclip = WeaponClipSize( self.weapon );
	self notify( "weapon_switch_done" );
}


/*
=============
///ScriptDocBegin
"Name: lerp_player_view_to_tag( <player>, <tag> , <lerptime> , <fraction> , <right_arc> , <left_arc> , <top_arc> , <bottom_arc> )"
"Summary: Lerps the player's view to the tag on the entity that calls the function.."
"Module: Utility"
"CallOn: An entity you want to lerp the player's view to."
"MandatoryArg: <player> : Player to do the lerp on"
"MandatoryArg: <tag> : Tag on the entity that you're lerping to."
"MandatoryArg: <lerptime> : Time to lerp over."
"OptionalArg: <fraction> : 0 to 1 amount that the rotation of the player's view should be effected by the entity. If you set it less than 1 then the player's view will not get all the way to the final angle."
"OptionalArg: <arcs> : Various arcs that limit how far the player can change his view."
"Example: car lerp_player_view_to_tag( "tag_windshield", 1 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

lerp_player_view_to_tag( player, tag, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc )
{
	lerp_player_view_to_tag_internal( player, tag, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc, false );
}

/*
=============
///ScriptDocBegin
"Name: lerp_player_view_to_tag_and_hit_geo( <player>, <tag> , <lerptime> , <fraction> , <right_arc> , <left_arc> , <top_arc> , <bottom_arc> )"
"Summary: Lerps the player's view to the tag on the entity that calls the function. Geo will block the player."
"Module: Utility"
"CallOn: An entity you want to lerp the player's view to."
"MandatoryArg: <player> : Player to do the lerp on"
"MandatoryArg: <tag> : Tag on the entity that you're lerping to."
"MandatoryArg: <lerptime> : Time to lerp over."
"OptionalArg: <fraction> : 0 to 1 amount that the rotation of the player's view should be effected by the entity. If you set it less than 1 then the player's view will not get all the way to the final angle."
"OptionalArg: <arcs> : Various arcs that limit how far the player can change his view."
"Example: car lerp_player_view_to_tag_and_hit_geo( "tag_windshield", 1 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

lerp_player_view_to_tag_and_hit_geo( player, tag, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc )
{
	lerp_player_view_to_tag_internal( player, tag, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc, true );
}

 /*
 =============
///ScriptDocBegin
"Name: lerp_player_view_to_position( <origin> , <angles> , <lerptime> , <fraction> , <right_arc> , <left_arc> , <top_arc> , <bottom_arc>, <hit_geo> )"
"Summary: Lerps the player's view to an origin and angles. See lerp_player_view_to_tag."
"Module: Utility"
"CallOn: A player (optional. If not cvalled on player, will default to level.player)"
"MandatoryArg: <origin> : The origin you're lerping to."
"MandatoryArg: <angles> : The angles you're lerping to."
"MandatoryArg: <lerptime> : Time to lerp over."
"OptionalArg: <fraction> : 0 to 1 amount that the rotation of the player's view should be effected by the destination angles. If you set it less than 1 then the player's view will not get all the way to the final angle."
"OptionalArg: <arcs> : Various arcs that limit how far the player can change his view."
"OptionalArg: <hit_geo> : Sets if the player will hit geo."
"Example: lerp_player_view_to_position( org.origin, org.angles );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

lerp_player_view_to_position( origin, angles, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc, hit_geo, player )
{
	player = get_player_from_self();

	linker = Spawn( "script_origin", ( 0, 0, 0 ) );
	linker.origin = player.origin;
	linker.angles = player GetPlayerAngles();

	if ( IsDefined( hit_geo ) && hit_geo )
	{
		player PlayerLinkTo( linker, "", fraction, right_arc, left_arc, top_arc, bottom_arc, hit_geo );
	}
	else
	if ( IsDefined( right_arc ) )
	{
		player PlayerLinkTo( linker, "", fraction, right_arc, left_arc, top_arc, bottom_arc );
	}
	else
	if ( IsDefined( fraction ) )
	{
		player PlayerLinkTo( linker, "", fraction );
	}
	else
	{
		player PlayerLinkTo( linker );
	}

	linker MoveTo( origin, lerptime, lerptime * 0.25 );
	linker RotateTo( angles, lerptime, lerptime * 0.25 );
	wait( lerptime );
	linker Delete();
}


/*
=============
///ScriptDocBegin
"Name: lerp_player_view_to_tag_oldstyle( <player>, <tag> , <lerptime> , <fraction> , <right_arc> , <left_arc> , <top_arc> , <bottom_arc> )"
"Summary: Lerps the player's view to the tag on the entity that calls the function, using the oldstyle link which moves the player's view when the tag rotates."
"Module: Utility"
"CallOn: An entity you want to lerp the player's view to."
"MandatoryArg: <player> : Which player."
"MandatoryArg: <tag> : Tag on the entity that you're lerping to."
"MandatoryArg: <lerptime> : Time to lerp over."
"OptionalArg: <fraction> : 0 to 1 amount that the rotation of the player's view should be effected by the entity. If you set it less than 1 then the player's view will not get all the way to the final angle."
"OptionalArg: <arcs> : Various arcs that limit how far the player can change his view."
"Example: car lerp_player_view_to_tag_oldstyle( "tag_windshield", 1 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
lerp_player_view_to_tag_oldstyle( player, tag, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc )
{
	lerp_player_view_to_tag_oldstyle_internal( player, tag, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc, false );
}

 /*
 =============
///ScriptDocBegin
"Name: lerp_player_view_to_position_oldstyle( <origin> , <angles> , <lerptime> , <fraction> , <right_arc> , <left_arc> , <top_arc> , <bottom_arc>, <hit_geo> )"
"Summary: Lerps the player's view to an origin and angles. See lerp_player_view_to_tag_oldstyle. Oldstyle means that you're going to move to the point where the player's feet would be, rather than directly below the point where the view would be."
"Module: Utility"
"MandatoryArg: <origin> : The origin you're lerping to."
"MandatoryArg: <angles> : The angles you're lerping to."
"MandatoryArg: <lerptime> : Time to lerp over."
"OptionalArg: <fraction> : 0 to 1 amount that the rotation of the player's view should be effected by the destination angles. If you set it less than 1 then the player's view will not get all the way to the final angle."
"OptionalArg: <arcs> : Various arcs that limit how far the player can change his view."
"OptionalArg: <hit_geo> : Sets if the player will hit geo."
"Example: lerp_player_view_to_position_oldstyle( org.origin, org.angles );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

lerp_player_view_to_position_oldstyle( origin, angles, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc, hit_geo )
{
	player = get_player_from_self();

	linker = Spawn( "script_origin", ( 0, 0, 0 ) );
	linker.origin = player get_player_feet_from_view();
	linker.angles = player GetPlayerAngles();

	if ( IsDefined( hit_geo ) )
	{
		player PlayerLinkToDelta( linker, "", fraction, right_arc, left_arc, top_arc, bottom_arc, hit_geo );
	}
	else
	if ( IsDefined( right_arc ) )
	{
		player PlayerLinkToDelta( linker, "", fraction, right_arc, left_arc, top_arc, bottom_arc );
	}
	else
	if ( IsDefined( fraction ) )
	{
		player PlayerLinkToDelta( linker, "", fraction );
	}
	else
	{
		player PlayerLinkToDelta( linker );
	}

	linker MoveTo( origin, lerptime, lerptime * 0.25 );
	linker RotateTo( angles, lerptime, lerptime * 0.25 );
	wait( lerptime );
	linker Delete();
}

 /*
 =============
///ScriptDocBegin
"Name: player_moves( <dist> )"
"Summary: Returns when the player has moved < dist > distance."
"Module: Utility"
"MandatoryArg: <dist> : The distance the player must move for the function to return."
"Example: player_moves( 500 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

player_moves( dist )
{
	org = level.player.origin;
	for ( ;; )
	{
		if ( Distance( org, level.player.origin ) > dist )
			break;
		wait( 0.05 );
	}
}


 /*
 =============
///ScriptDocBegin
"Name: waittill_either_function( <func1> , <parm1> , <func2> , <parm2> )"
"Summary: Returns when either func1 or func2 have returned."
"Module: Utility"
"MandatoryArg: <func1> : A function pointer to a function that may return at some point."
"MandatoryArg: <func2> : Another function pointer to a function that may return at some point."
"OptionalArg: <parm1> : An optional parameter for func1."
"OptionalArg: <parm2> : An optional parameter for func2."
"Example: player_moves( 500 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

waittill_either_function( func1, parm1, func2, parm2 )
{
	ent = SpawnStruct();
	thread waittill_either_function_internal( ent, func1, parm1 );
	thread waittill_either_function_internal( ent, func2, parm2 );
	ent waittill( "done" );
}

/*
=============
///ScriptDocBegin
"Name: waittill_msg( <msg> )"
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
waittill_msg( msg )
{
	self waittill( msg );
}


 /*
 =============
///ScriptDocBegin
"Name: display_hint( <hint> )"
"Summary: Displays a hint created with add_hint_string."
"Module: Utility"
"MandatoryArg: <hint> : The hint reference created with add_hint_string."
"Example: display_hint( "huzzah" )"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
display_hint( hint, parm1, parm2, parm3 )
{
	player = get_player_from_self();

	// hint triggers have an optional function they can boolean off of to determine if the hint will occur
	// such as not doing the NVG hint if the player is using NVGs already
	if ( IsDefined( level.trigger_hint_func[ hint ] ) )
	{
		if ( player [[ level.trigger_hint_func[ hint ] ]]() )
			return;

		player thread HintPrint( level.trigger_hint_string[ hint ], level.trigger_hint_func[ hint ], parm1, parm2, parm3, 30 );
	}
	else
	{
		player thread HintPrint( level.trigger_hint_string[ hint ], undefined, undefined, undefined, undefined, 30 );
	}
}


/*
=============
///ScriptDocBegin
"Name: display_hint_timeout( <hint> , <timeout> , <parm1> , <parm2> , <parm3> )"
"Summary: Displays a hint created with add_hint_string."
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <hint> : The hint reference created with add_hint_string."
"MandatoryArg: <timeout>: "
"MandatoryArg: <parm1>: "
"MandatoryArg: <parm2>: "
"MandatoryArg: <parm3>: "
"Example: display_hint_timeout( "huzzah",3 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

display_hint_timeout( hint, timeout, parm1, parm2, parm3 )
{
	player = get_player_from_self();


	AssertEx( IsDefined( level.trigger_hint_func[ hint ] ), "Can't have a hint with a timeout if is has no break function, because hints without break functions display for a set period of time." );

	// hint triggers have an optional function they can boolean off of to determine if the hint will occur
	// such as not doing the NVG hint if the player is using NVGs already
	if ( player [[ level.trigger_hint_func[ hint ] ]]() )
		return;

	player thread HintPrint( level.trigger_hint_string[ hint ], level.trigger_hint_func[ hint ], parm1, parm2, parm3, timeout );
}

/*
=============
///ScriptDocBegin
"Name: getGenericAnim( <anime> )"
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
getGenericAnim( anime )
{
	AssertEx( IsDefined( level.scr_anim[ "generic" ][ anime ] ), "Generic anim " + anime + " was not defined in your _anim file." );
	return level.scr_anim[ "generic" ][ anime ];
}

/*
=============
///ScriptDocBegin
"Name: enable_careful()"
"Summary: Makes an AI not advance into his fixednode safe radius if an enemy enters it."
"Module: AI"
"Example: guy enable_careful()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_careful()
{
	AssertEx( IsAI( self ), "Tried to make an ai careful but it wasn't called on an AI" );
	self.script_careful = true;
}

/*
=============
///ScriptDocBegin
"Name: disable_careful()"
"Summary: Turns off careful mode for this AI."
"Module: AI"
"Example: guy disable_careful()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_careful()
{
	AssertEx( IsAI( self ), "Tried to unmake an ai careful but it wasn't called on an AI" );
	self.script_careful = false;
	self notify( "stop_being_careful" );
}

/*
=============
///ScriptDocBegin
"Name: enable_sprint()"
"Summary: Force an ai to sprint."
"Module: AI"
"Example: guy enable_sprint()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_sprint()
{
	AssertEx( IsAI( self ), "Tried to make an ai sprint but it wasn't called on an AI" );
	self.sprint = true;
}

/*
=============
///ScriptDocBegin
"Name: disable_sprint()"
"Summary: Disable forced sprinting."
"Module: AI"
"Example: guy disable_sprint()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_sprint()
{
	AssertEx( IsAI( self ), "Tried to unmake an ai sprint but it wasn't called on an AI" );
	self.sprint = undefined;
}

/*
=============
///ScriptDocBegin
"Name: disable_bulletwhizbyreaction()"
"Summary: disables the bulletwhizby reactions by ai"
"Module: AI"
"CallOn: An AI"
"Example: level.price disable_bulletwhizbyreaction();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_bulletwhizbyreaction()
{

/*
=============
///ScriptFieldDocBegin
"Name: .disableBulletWhizbyReaction"
"Summary: self explanatory"
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

	self.disableBulletWhizbyReaction = true;
}

/*
=============
///ScriptDocBegin
"Name: enable_bulletwhizbyreaction()"
"Summary: renables the bulletwhizby reactions by ai"
"Module: AI"
"CallOn: An AI"
"Example: level.price enable_bulletwhizbyreaction();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_bulletwhizbyreaction()
{
	self.disableBulletWhizbyReaction = undefined;
}

clear_dvar( msg )
{
	SetDvar( msg, "" );
}

/*
=============
///ScriptDocBegin
"Name: mission( <name> )"
"Summary: Returns true if name is the current mission"
"Module: Utility"
"MandatoryArg: <name>: Name of the mission to test"
"Example: if ( mission( "bog_a" ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
mission( name )
{
	return level.script == name;
}

/*
=============
///ScriptDocBegin
"Name: set_fixednode_true( <set_fixednode_true> )"
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
set_fixednode_true()
{
	self.fixednode = true;
}

/*
=============
///ScriptDocBegin
"Name: set_fixednode_false( <set_fixednode_false> )"
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
set_fixednode_false()
{
	self.fixednode = false;
}


/*
=============
///ScriptDocBegin
"Name: spawn_ai( <bForceSpawn> )"
"Summary: Spawns the AI spawner and returns the alive AI"
"Module: Entity"
"CallOn: An entity"
"OptionalArg: <bForceSpawn>: Set to true to force spawn the AI"
"OptionalArg: <bMagicBulletShield>: Set to true to start magic_bullet_shield immediately"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
spawn_ai( bForceSpawn, bMagicBulletShield )
{
	if ( IsDefined( self.script_delay_spawn ) )
	{
		self endon( "death" );
		wait( self.script_delay_spawn );
	}
	spawnedGuy = undefined;

	dontShareEnemyInfo = ( IsDefined( self.script_stealth ) && flag( "_stealth_enabled" ) && !flag( "_stealth_spotted" ) );

	if ( ( IsDefined( self.script_forcespawn ) ) || ( IsDefined( bForceSpawn ) ) )
	{
		if ( !isdefined( self.script_drone ) )
			spawnedGuy = self StalingradSpawn( dontShareEnemyInfo );
		else
			spawnedGuy = dronespawn( self );
	}

	else
	{
		if ( !isdefined( self.script_drone ) )
			spawnedGuy = self DoSpawn( dontShareEnemyInfo );
		else
			spawnedGuy = dronespawn( self );
	}

	// This is to prevent a race condition where the guy could be killed while waiting inside spawn_failed(),
	// and thus die before this function returns and the caller has a chance to call magic_bullet_shield().
	if ( isdefined(bMagicBulletShield) && bMagicBulletShield && IsAlive( spawnedGuy ) )
		spawnedGuy magic_bullet_shield();
	
	if ( !isdefined( self.script_drone ) )
		spawn_failed( spawnedGuy );
	//this assert should still be here - but the functions calling this (pyramid spawner for example ) don't care if
	//the guy is actually spawned or not...seems to be more of an issue with pyramid spawner ( why is trying to spawn guys )
	//and not caring about the consiquences...tracked it down to this function being called twice on the same spawner in the same frame
	//in bog B, maybe further evaluation should be taken of pyramid spawner and why it's trying to do that - but for now - just commenting out
	//the assert and assuming we don't care why we can't spawn 2 guys in the same frame...  -MO
	//assert( IsDefined( spawnedGuy ) );
	
	if( IsDefined( self.script_spawn_once ) )
	    self Delete();

	return spawnedGuy;
}

 /*
 =============
///ScriptDocBegin
"Name: function_stack( <function>, <param1>, <param2>, <param3>, <param4>, <param5> )"
"Summary: function stack is used to thread off multiple functions one after another an insure that they get called in the order you sent them in (like a FIFO queue or stack). function_stack will wait for the function to finish before continuing the next line of code, but since it internally threads the function off, the function will not end if the parent function which called function_stack() ends.  function_stack is also local to the entity that called it, if you call it on nothing it will use level and all functions sent to the stack will wait on the previous one sent to level.  The same works for entities.  This way you can have 2 AI's that thread off multiple functions but those functions are in individual stacks for each ai"
"Module: Utility"
"CallOn: level or an entity."
"MandatoryArg: <function> : the function to send to the stack"
"OptionalArg: <param1> : An optional parameter for <function>."
"OptionalArg: <param2> : An optional parameter for <function>."
"OptionalArg: <param3> : An optional parameter for <function>."
"OptionalArg: <param4> : An optional parameter for <function>."
"OptionalArg: <param5> : An optional parameter for <function>."
"Example: level thread function_stack(::radio_dialogue, "scoutsniper_mcm_okgo" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
function_stack( func, param1, param2, param3, param4, param5 )
{
	//self might die - but if we endon( "death" ) this function will return without a bool, which is bad.
	//self endon( "death" );

	localentity = SpawnStruct();
	localentity thread function_stack_proc( self, func, param1, param2, param3, param4, param5 );

	return self function_stack_wait_finish( localentity );
}

/*
=============
///ScriptDocBegin
"Name: function_stack_timeout( <timeout> , <func> , <param1> , <param2> , <param3> , <param4> )"
"Summary: function stack is used to thread off multiple functions one after another an insure that they get called in the order you sent them in (like a FIFO queue or stack). function_stack will wait for the function to finish before continuing the next line of code, but since it internally threads the function off, the function will not end if the parent function which called function_stack() ends.  function_stack is also local to the entity that called it, if you call it on nothing it will use level and all functions sent to the stack will wait on the previous one sent to level.  The same works for entities.  This way you can have 2 AI's that thread off multiple functions but those functions are in individual stacks for each ai"
"Module: Utility"
"CallOn: level or an entity."
"MandatoryArg: <timeout> : number of seconds before this function times out of the stack"
"MandatoryArg: <function> : the function to send to the stack"
"OptionalArg: <param1> : An optional parameter for <function>."
"OptionalArg: <param2> : An optional parameter for <function>."
"OptionalArg: <param3> : An optional parameter for <function>."
"OptionalArg: <param4> : An optional parameter for <function>."
"OptionalArg: <param5> : An optional parameter for <function>."
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
function_stack_timeout( timeout, func, param1, param2, param3, param4, param5 )
{
	//self might die - but if we endon( "death" ) this function will return without a bool, which is bad.
	//self endon( "death" );

	localentity = SpawnStruct();
	localentity thread function_stack_proc( self, func, param1, param2, param3, param4, param5 );

	if ( IsDefined( localentity.function_stack_func_begun ) || ( localentity waittill_any_timeout( timeout, "function_stack_func_begun" ) != "timeout" ) )
	{
		return self function_stack_wait_finish( localentity );
	}
	else
	{
		localentity notify( "death" );
		return false;
	}
}

/*
=============
///ScriptDocBegin
"Name: function_stack_clear()"
"Summary: kills the stack of funcitons waiting to run"
"Module: Utility"
"CallOn: level or entity"
"Example: level function_stack_clear();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
function_stack_clear()
{
	newstack = [];
	if ( IsDefined( self.function_stack[ 0 ] ) && IsDefined( self.function_stack[ 0 ].function_stack_func_begun ) )
		newstack[ 0 ] = self.function_stack[ 0 ];

	//clear the stack and stop further processes
	self.function_stack = undefined;
	self notify( "clear_function_stack" );

	//the notify ends a function in the stack process waiting it's turn...it checks to
	//see if there is a function_stack on self to either run the function or just quit
	//in rare cases if you clear the stack and start piling stuff onto a new one, you'll
	//create the new stack before the process has a chance to check if the stack is undefined
	//and then all your functions run at once instead of being actually cleared...this
	//waittillframeend makes sure that doesn't happen
	waittillframeend;

	if ( !newstack.size )
		return;

	if ( !newstack[ 0 ].function_stack_func_begun )
		return;

	self.function_stack = newstack;
}


/*
=============
///ScriptDocBegin
"Name: geo_off( <geo_off> )"
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
geo_off()
{
	if ( IsDefined( self.geo_off ) )
		return;

	self.realorigin = self GetOrigin();
	self MoveTo( self.realorigin + ( 0, 0, -10000 ), .2 );

	self.geo_off = true;
}

/*
=============
///ScriptDocBegin
"Name: geo_on( <geo_on> )"
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
geo_on()
{
	if ( !isDefined( self.geo_off ) )
		return;

	self MoveTo( self.realorigin, .2 );
	self waittill( "movedone" );
	self.geo_off = undefined;
}

/*
=============
///ScriptDocBegin
"Name: disable_exits()"
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
disable_exits()
{
	self.disableexits = true;
}

/*
=============
///ScriptDocBegin
"Name: enable_exits( <enable_exits> )"
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
enable_exits()
{
	self.disableexits = undefined;
}

/*
=============
///ScriptDocBegin
"Name: disable_turnAnims( <disable_turnAnims> )"
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
disable_turnAnims()
{
/*
=============
///ScriptFieldDocBegin
"Name: .noTurnAnims"
"Summary: don't do turning animations"
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

	self.noTurnAnims = true;
}

/*
=============
///ScriptDocBegin
"Name: enable_turnAnims()"
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
enable_turnAnims()
{
	self.noTurnAnims = undefined;
}

/*
=============
///ScriptDocBegin
"Name: disable_arrivals()"
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
disable_arrivals()
{
	self.disablearrivals = true;
}

/*
=============
///ScriptDocBegin
"Name: enable_arrivals()"
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
enable_arrivals()
{
	self endon( "death" );
	// wait until after anim_reach has turned arrivals off
	waittillframeend;
	self.disablearrivals = undefined;
}

 /*
 =============
///ScriptDocBegin
"Name: set_blur( <magnitude>, <transition time> )"
"Summary: calls script command SetBlur( <magnitude>, <transition time> )"
"Module: Utility"
"CallOn: "
"MandatoryArg: <magnitude> : amount of blur to transition to"
"MandatoryArg: <transition time> : time in seconds to transition to desired blur amount"
"Example: set_blur( 8, 3.1 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
set_blur( magnitude, time )
{
	SetBlur( magnitude, time );
}

 /*
 =============
///ScriptDocBegin
"Name: set_goal_radius( <radius> )"
"Summary: sets .goalradius parameter on ai to <radius>"
"Module: AI"
"CallOn: AI"
"MandatoryArg: <radius> : radius to set ai's .goalradius to"
"Example: guy set_goal_radius( 128 );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
set_goal_radius( radius )
{
	self.goalradius = radius;
}

 /*
 =============
///ScriptDocBegin
"Name: set_goal_node( <node> )"
"Summary: calls script command SetGoalNode( <node> ), but also sets self.last_set_goalnode to <node>"
"Module: AI"
"CallOn: AI"
"MandatoryArg: <node> : node to send the ai to"
"Example: guy set_goal_node( node );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
set_goal_node( node )
{
/*
=============
///ScriptFieldDocBegin
"Name: .last_set_goalnode"
"Summary: last_set_goalnode -> set in script and only defined when using set_goal_node instead of setgoalnode"
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
	self.last_set_goalnode 	 = node;
	self.last_set_goalpos 	 = undefined;
	self.last_set_goalent 	 = undefined;

	self SetGoalNode( node );
}

 /*
 =============
///ScriptDocBegin
"Name: set_goal_node_targetname( <targetname> )"
"Summary: gets the node with the spedified targetname then calls script command SetGoalNode( <node> ), but also sets self.last_set_goalnode to <node>"
"Module: AI"
"CallOn: AI"
"MandatoryArg: <targetname> : node targetname to send the ai to"
"Example: guy set_goal_node( "first_node" );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
set_goal_node_targetname( targetname )
{
	Assert( IsDefined( targetname ) );
	node = GetNode( targetname, "targetname" );
	Assert( IsDefined( node ) );

	self set_goal_node( node );
}

 /*
 =============
///ScriptDocBegin
"Name: set_goal_pos( <origin> )"
"Summary: calls script command SetGoalPos( <origin> ), but also sets self.last_set_goalpos to <origin>"
"Module: AI"
"CallOn: AI"
"MandatoryArg: <origin> : origin to send the ai to"
"Example: guy set_goal_pos( vector );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
set_goal_pos( origin )
{
	self.last_set_goalnode 	 = undefined;

/*
=============
///ScriptFieldDocBegin
"Name: .last_set_goalpos"
"Summary: last_set_goalpos -> set in script and only defined when using set_goal_pos instead of setgoalpos"
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
	self.last_set_goalpos 	 = origin;
	self.last_set_goalent 	 = undefined;

	self SetGoalPos( origin );
}

/*
=============
///ScriptDocBegin
"Name: set_goal_ent( <entity> )"
"Summary: calls script command SetGoalPos( <entity>.origin ), but also sets self.last_set_goalent to <origin>"
"Module: AI"
"CallOn: AI"
"MandatoryArg: <entity> : entity with .origin variable to send the ai to"
"Example: guy set_goal_ent( script_origin );"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
set_goal_ent( target )
{
	set_goal_pos( target.origin );
/*
=============
///ScriptFieldDocBegin
"Name: .last_set_goalent"
"Summary: last_set_goalent -> set in script and only defined when using set_goal_ent( entity ) instead of setgoalpos( entity.origin )"
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
	self.last_set_goalent 	 = target;
}

/*
=============
///ScriptDocBegin
"Name: objective_complete( <obj> )"
"Summary: Sets an objective to DONE"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <obj>: The objective index"
"Example: objective_complete( 3 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
objective_complete( obj )
{
	//{NOT_IN_SHIP
	objective_recon( obj );
	//}NOT_IN_SHIP
	Objective_State( obj, "done" );
	level notify( "objective_complete" + obj );
}


/*
=============
///ScriptDocBegin
"Name: handsignal( <xanim> , <ender> , <waiter> )"
"Summary: Makes an AI do a handsignal"
"Module: Utility"
"CallOn: An ai"
"MandatoryArg: <xanim>: The string name of the animation. Options are 'moveout', 'moveup', 'stop', 'onme', 'enemy', 'go'."
"OptionalArg: <wait anim done>: if true, wait till animation is over. Defaults to false."
"OptionalArg: <ender>: An optional ender "
"OptionalArg: <waiter>: An optional string to wait for level notify on "
"Example: level.price handsignal( "go" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============

Add this to your _anim script:
	level.scr_anim[ "generic" ][ "signal_onme" ]				= %CQB_stand_wave_on_me;
	level.scr_anim[ "generic" ][ "signal_go" ]					= %CQB_stand_wave_go_v1;
	level.scr_anim[ "generic" ][ "signal_stop" ]				= %CQB_stand_signal_stop;


*/
handsignal( xanim, waitAnimDone, ender, waiter )
{
	returnImmediate = true;
	if ( IsDefined( waitAnimDone ) )
		returnImmediate = !waitAnimDone;

	if ( IsDefined( ender ) )
		level endon( ender );

	if ( IsDefined( waiter ) )
		level waittill( waiter );

	animName = "signal_" + xanim;

	if ( self.a.pose == "crouch" )
		animName = animName + "_crouch";
	else if ( self.script == "cover_right" )
		animName = animName + "_coverR";
	else if ( self isCQBWalking() )
		animName = animName + "_cqb";

	if ( returnImmediate )
		self SetAnimRestart( getGenericAnim( animName ), 1, 0, 1.1 );
	else
		self maps\_anim::anim_generic( self, animName );
}

/*
=============
///ScriptDocBegin
"Name: get_guy_with_script_noteworthy_from_spawner( <script_noteworthy> )"
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
get_guy_with_script_noteworthy_from_spawner( script_noteworthy )
{
	spawner = GetEntArray( script_noteworthy, "script_noteworthy" );
	AssertEx( spawner.size == 1, "Tried to get guy from spawner but there were zero or multiple spawners" );
	guys = array_spawn( spawner );
	return guys[ 0 ];
}

/*
=============
///ScriptDocBegin
"Name: get_guy_with_targetname_from_spawner( <targetname> )"
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
get_guy_with_targetname_from_spawner( targetname )
{
	spawner = GetEntArray( targetname, "targetname" );
	AssertEx( spawner.size == 1, "Tried to get guy from spawner but there were zero or multiple spawners" );
	guys = array_spawn( spawner );
	return guys[ 0 ];
}

/*
=============
///ScriptDocBegin
"Name: get_guys_with_targetname_from_spawner( <targetname> )"
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
get_guys_with_targetname_from_spawner( targetname )
{
	spawners = GetEntArray( targetname, "targetname" );
	AssertEx( spawners.size > 0, "Tried to get guy from spawner but there were zero spawners" );
	return array_spawn( spawners );
}

/*
=============
///ScriptDocBegin
"Name: array_spawn( <spawners>, <bForceSpawn> )"
"Summary: spawns every spawner in the array and then returns an array of the alive AI that were spawned"
"Module: Utility"
"CallOn: An array of spawners"
"MandatoryArg: <spawners>: The spawners"
"OptionalArg: <bForceSpawn>: use stalingradspawn to force spawn the AI"
"OptionalArg: <skipIncorrectNumberAssert>: skips the assert saying that it spawned the incorrect number of guys"
"Example: guys = array_spawn( hooligans );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_spawn( spawners, bForceSpawn, skipIncorrectNumberAssert )
{
	if ( !isdefined( skipIncorrectNumberAssert ) )
		skipIncorrectNumberAssert = 0;
	
	guys = [];
	foreach ( spawner in spawners )
	{
		spawner.count = 1;

		if ( GetSubStr( spawner.classname, 7, 10 ) == "veh" )
		{
			guy = spawner spawn_vehicle();

			/#
			if ( IsDefined( spawner.export ) )
				AssertEx( IsAlive( guy ), "Vehicle with export " + spawner.export + " failed to spawn." );
			else
				AssertEx( IsAlive( guy ), "Vehicle at " + spawner.origin + " failed to spawn." );
			#/
			if ( IsDefined( guy.target ) && !IsDefined( guy.script_moveoverride ) )
				guy thread maps\_vehicle::gopath();
			guys[ guys.size ] = guy;
		}
		else
		{
			guy = spawner spawn_ai( bForceSpawn );

			if ( !skipIncorrectNumberAssert )
				AssertEx( IsAlive( guy ), "Guy with export " + spawner.export + " failed to spawn." );
			guys[ guys.size ] = guy;
		}
	}
	
	if ( !skipIncorrectNumberAssert )
		AssertEx( guys.size == spawners.size, "Didnt spawn correct number of guys" );

	return guys;
}

/*
=============
///ScriptDocBegin
"Name: array_spawn_targetname( <targetname>, <forcespawn> )"
"Summary: Spawn guys with this targetname"
"Module: Utility"
"MandatoryArg: <targetname>: The targetname "
"OptionalArg: <forcespawn>: force the spawn "
"OptionalArg: <skipIncorrectNumberAssert>: skips the assert saying that it spawned the incorrect number of guys"
"Example: array_spawn_targetname( "badguy_spawner" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_spawn_targetname( targetname, forcespawn, skipIncorrectNumberAssert, deleteDronePool )
{
	spawners = GetEntArray( targetname, "targetname" );
	if ( IsDefined( level.spawn_pool_enabled ) )
	{
		struct_spawners = getstructarray( targetname, "targetname" );
		if ( IsDefined( deleteDronePool ) && deleteDronePool )
			deletestructarray_ref( struct_spawners );
		pool_spawners = maps\_spawner::get_pool_spawners_from_structarray( struct_spawners );
		spawners = array_combine( spawners, pool_spawners );
	}
	AssertEx( spawners.size, "Tried to spawn spawners with targetname " + targetname + " but there are no spawners" );
	return array_spawn( spawners, forcespawn, skipIncorrectNumberAssert );
}

/*
=============
///ScriptDocBegin
"Name: array_spawn_noteworthy( <noteworthy>, <forcespawn> )"
"Summary: Spawn guys with this noteworthy"
"Module: Utility"
"MandatoryArg: <noteworthy>: The noteworthy "
"OptionalArg: <forcespawn>: force the spawn "
"OptionalArg: <skipIncorrectNumberAssert>: skips the assert saying that it spawned the incorrect number of guys"
"Example: array_spawn_noteworthy( "badguy_spawner" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_spawn_noteworthy( noteworthy, forcespawn, skipIncorrectNumberAssert, deleteDronePool  )
{
	spawners = GetEntArray( noteworthy, "script_noteworthy" );
	if ( IsDefined( level.spawn_pool_enabled ) )
	{
		struct_spawners = getstructarray( noteworthy, "script_noteworthy" );
		if ( IsDefined( deleteDronePool ) && deleteDronePool )
			deletestructarray_ref( struct_spawners );
		pool_spawners = maps\_spawner::get_pool_spawners_from_structarray( struct_spawners );
		spawners = array_combine( spawners, pool_spawners );
	}
	AssertEx( spawners.size, "Tried to spawn spawners with targetname " + noteworthy + " but there are no spawners" );
	return array_spawn( spawners, forcespawn, skipIncorrectNumberAssert );
}


/*
=============
///ScriptDocBegin
"Name: spawn_script_noteworthy( <script_noteworthy> )"
"Summary: Spawns an AI spawner with a specific script_noteworthy"
"Module: Utility"
"MandatoryArg: <script_noteworthy>: The script_noteworthy of the spawner"
"Example: level.price = spawn_script_noteworthy( "friendly_price" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
spawn_script_noteworthy( script_noteworthy, bForceSpawn )
{
	spawner = GetEnt( script_noteworthy, "script_noteworthy" );
	AssertEx( IsDefined( spawner ), "Spawner with script_noteworthy " + script_noteworthy + " does not exist." );

	guy = spawner spawn_ai( bForceSpawn );
	return guy;
}

/*
=============
///ScriptDocBegin
"Name: spawn_targetname( <targetname>, <bForcespawn>: )"
"Summary: Spawns an AI spawner with a specific targetname"
"Module: Utility"
"MandatoryArg: <targetname>: The targetname of the spawner"
"OptionalArg: <bForcespawn>: make this spawn with stalingradspawn"
"Example: level.price = targetname( "targetname" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
spawn_targetname( targetname, bForceSpawn )
{
	spawner = GetEnt( targetname, "targetname" );
	AssertEx( IsDefined( spawner ), "Spawner with targetname " + targetname + " does not exist." );

	guy = spawner spawn_ai( bForceSpawn );
	return guy;
}

/*
=============
///ScriptDocBegin
"Name: add_dialogue_line( <name> , <msg>, <name_color> )"
"Summary: Prints temp dialogue on the screen in lieu of a sound alias."
"Module: Utility"
"MandatoryArg: <name>: The character."
"MandatoryArg: <msg>: The dialogue."
"OptionalArg: <name_color>: An optional string of a color to give the name (makes different names delivering dialogue easier to follow...colors red, green, yellow, blue, cyan, purple, white, black "
"Example: thread add_dialogue_line( "MacMillan", "Put me down over there on the slope by the mattress." );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_dialogue_line( name, msg, name_color )
{
	if ( GetDvarInt( "loc_warnings", 0 ) )
		return;// I'm not localizing your damn temp dialog lines - Nate.

	if ( !isdefined( level.dialogue_huds ) )
	{
		level.dialogue_huds = [];
	}

	for ( index = 0; ; index++ )
	{
		if ( !isdefined( level.dialogue_huds[ index ] ) )
			break;
	}
	color = "^3";

	if ( IsDefined( name_color ) )
	{
		switch( name_color )
		{
			case "r":
			case "red":
				color = "^1";
				break;
			case "g":
			case "green":
				color = "^2";
				break;
			case "y":
			case "yellow":
				color = "^3";
				break;
			case "b":
			case "blue":
				color = "^4";
				break;
			case "c":
			case "cyan":
				color = "^5";
				break;
			case "p":
			case "purple":
				color = "^6";
				break;
			case "w":
			case "white":
				color = "^7";
				break;
			case "bl":
			case "black":
				color = "^8";
				break;
		}
	}

	level.dialogue_huds[ index ] = true;

	hudelem = maps\_hud_util::createFontString( "default", 1.5 );
	hudelem.location = 0;
	hudelem.alignX = "left";
	hudelem.alignY = "top";
	hudelem.foreground = 1;
	hudelem.sort = 20;

	hudelem.alpha = 0;
	hudelem FadeOverTime( 0.5 );
	hudelem.alpha = 1;
	hudelem.x = 40;
	hudelem.y = 260 + index * 18;
	hudelem.label = " " + color + "< " + name + " > ^7" + msg;
	hudelem.color = ( 1, 1, 1 );

	wait( 2 );
	timer = 2 * 20;
	hudelem FadeOverTime( 6 );
	hudelem.alpha = 0;

	for ( i = 0; i < timer; i++ )
	{
		hudelem.color = ( 1, 1, 0 / ( timer - i ) );
		wait( 0.05 );
	}
	wait( 4 );

	hudelem Destroy();

	level.dialogue_huds[ index ] = undefined;
}

/*
=============
///ScriptDocBegin
"Name: destructible_disable_explosion()"
"Summary: Disables a destructibles ( ie destructible vehicle ) ability to explode. It will catch fire, take window damage etc but not explode."
"Module: Destructibles"
"CallOn: Destructible"
"Example: car thread destructible_disable_explosion();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
destructible_disable_explosion()
{
	self common_scripts\_destructible::disable_explosion();
}

/*
=============
///ScriptDocBegin
"Name: destructible_force_explosion()"
"Summary: Forces a destructible ( ie destructible vehicle ) to explode immediately."
"Module: Destructibles"
"CallOn: Destructible"
"Example: car thread destructible_force_explosion();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
destructible_force_explosion()
{
	self common_scripts\_destructible::force_explosion();
}

set_grenadeammo( count )
{
	self.grenadeammo = count;
}

/*
=============
///ScriptDocBegin
"Name: get_player_feet_from_view( <get_player_feet_from_view> )"
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
get_player_feet_from_view()
{
	Assert( IsPlayer( self ) );

	tagorigin = self.origin;
	upvec = AnglesToUp( self GetPlayerAngles() );
	height = self GetPlayerViewHeight();

	player_eye = tagorigin + ( 0, 0, height );
	player_eye_fake = tagorigin + ( upvec*height );

	diff_vec = player_eye - player_eye_fake;

	fake_origin = tagorigin + diff_vec;
	return fake_origin;
}


/*
=============
///ScriptDocBegin
"Name: set_baseaccuracy( <val> )"
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
set_baseaccuracy( val )
{
	self.baseaccuracy = val;
}

/*
=============
///ScriptDocBegin
"Name: set_console_status( <set_console_status> )"
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
set_console_status()
{
	if ( !isdefined( level.Console ) )
		level.Console = GetDvar( "consoleGame" ) == "true";
	else
		AssertEx( level.Console == ( GetDvar( "consoleGame" ) == "true" ), "Level.console got set incorrectly." );

	if ( !isdefined( level.xenon ) )
		level.xenon = GetDvar( "xenonGame" ) == "true";
	else
		AssertEx( level.xenon == ( GetDvar( "xenonGame" ) == "true" ), "Level.xenon got set incorrectly." );

	if ( !isdefined( level.ps3 ) )
		level.ps3 = GetDvar( "ps3Game" ) == "true";
	else
		AssertEx( level.ps3 == ( GetDvar( "ps3Game" ) == "true" ), "Level.ps3 got set incorrectly." );
}

/*
=============
///ScriptDocBegin
"Name: autosave_now( <suppress_print> )"
"Summary: "
"Module: Utility"
"CallOn: Level"
"OptionalArg: <suppress_print>: "
"Example: thread autosave_now();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
autosave_now( suppress_print )
{
	return maps\_autosave::_autosave_game_now( suppress_print );
}

/*
=============
///ScriptDocBegin
"Name: autosave_now_silent()"
"Summary: No checkpoint msg"
"Module: Utility"
"CallOn: Level"
"OptionalArg: <suppress_print>: "
"Example: thread autosave_now_silent();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
autosave_now_silent()
{
	return maps\_autosave::_autosave_game_now( true );
}

/*
=============
///ScriptDocBegin
"Name: set_generic_deathanim( <deathanim> )"
"Summary: Sets a deathanim for a generic guy"
"Module: Utility"
"CallOn: AI"
"MandatoryArg: <deathanim>: The death animation reference"
"Example: guy set_generic_deathanim( "explosive_death" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_generic_deathanim( deathanim )
{
	self.deathanim = getGenericAnim( deathanim );
}

/*
=============
///ScriptDocBegin
"Name: set_deathanim( <deathanim> )"
"Summary: Sets the deathanim on an AI"
"Module: Utility"
"CallOn: AI"
"MandatoryArg: <deathanim>: The death animation reference"
"Example: guy set_deathanim( "death" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_deathanim( deathanim )
{
	self.deathanim = getanim( deathanim );
}

/*
=============
///ScriptDocBegin
"Name: clear_deathanim( <clear_deathanim> )"
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
clear_deathanim()
{
	self.deathanim = undefined;
}

/*
=============
///ScriptDocBegin
"Name: hunted_style_door_open( <soundalias> )"
"Summary: Animates the door/gate/whatever in the style of Hunted's cool price door opening."
"Module: Utility"
"CallOn: A door or gate calls it"
"OptionalArg: <Soundalias>: A soundalias to play "
"Example: door hunted_style_door_open( "door_wood_slow_creaky_open" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
hunted_style_door_open( soundalias )
{
	wait( 1.75 );

	if ( IsDefined( soundalias ) )
		self PlaySound( soundalias );
	else
		self PlaySound( "door_wood_slow_open" );

	self RotateTo( self.angles + ( 0, 70, 0 ), 2, .5, 0 );
	self ConnectPaths();
	self waittill( "rotatedone" );
	self RotateTo( self.angles + ( 0, 40, 0 ), 2, 0, 2 );
}

/*
=============
///ScriptDocBegin
"Name: palm_style_door_open( <soundalias> )"
"Summary: Animates the door/gate/whatever in the style of Hunted's cool price door opening but with the palm instead of door knob."
"Module: Utility"
"CallOn: A door or gate calls it"
"OptionalArg: <Soundalias>: A soundalias to play "
"Example: door palm_style_door_open( "door_wood_slow_creaky_open" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
palm_style_door_open( soundalias )
{
	wait( 1.35 );

	if ( IsDefined( soundalias ) )
		self PlaySound( soundalias );
	else
		self PlaySound( "door_wood_slow_open" );

	self RotateTo( self.angles + ( 0, 70, 0 ), 2, .5, 0 );
	self ConnectPaths();
	self waittill( "rotatedone" );
	self RotateTo( self.angles + ( 0, 40, 0 ), 2, 0, 2 );
}



/*
=============
///ScriptDocBegin
"Name: lerp_fov_overtime( <time> , <destfov> )"
"Summary: lerps from the current cg_fov value to the destfov value linearly over time.  Sleeps for the given time."
"Module: Player"
"CallOn: Level"
"MandatoryArg: <time>: time to lerp"
"OptionalArg: <destfov>: field of view to go to"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

lerp_fov_overtime( time, destfov )
{
	// this used to be implemented in script, and wasn't smooth due to the 20/60 thing.
	// Now using the engine call instead.
	foreach( player in level.players )
		player LerpFOV( destfov, time );
	wait time;
}

/*
=============
///ScriptDocBegin
"Name: lerp_fovscale_overtime( <time> , <destfovscale> )"
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
lerp_fovscale_overtime( time, destfovscale )
{
	basefov = GetDvarFloat( "cg_fovscale" );
	incs = Int( time / .05 );

	incfov = ( destfovscale - basefov ) / incs ;
	currentfov = basefov;
	for ( i = 0; i < incs; i++ )
	{
		currentfov += incfov;
		SetSavedDvar( "cg_fovscale", currentfov );
		wait .05;
	}

	SetSavedDvar( "cg_fovscale", destfovscale );
}

/*
=============
///ScriptDocBegin
"Name: putGunAway()"
"Summary: Puts the AI's weapon away"
"Module: Utility"
"CallOn: An ai"
"Example: level.price putGunAaway();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

putGunAway()
{
	animscripts\shared::placeWeaponOn( self.weapon, "none" );
	self.weapon = "none";
}

/*
=============
///ScriptDocBegin
"Name: apply_fog()"
"Summary: Applies the "start" fog settings for this trigger"
"Module: Utility"
"CallOn: A trigger_fog"
"Example: trigger_fog apply_fog()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
apply_fog()
{
	maps\_load::set_fog_progress( 0 );
}

/*
=============
///ScriptDocBegin
"Name: apply_end_fog()"
"Summary: Applies the "end" fog settings for this trigger"
"Module: Utility"
"CallOn: A trigger_fog"
"Example: trigger_fog apply_end_fog()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
apply_end_fog()
{
	maps\_load::set_fog_progress( 1 );
}


/*
=============
///ScriptDocBegin
"Name: anim_stopanimscripted()"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_stopanimscripted()
{
	self StopAnimScripted();
	self notify( "stop_loop" );// default ender.
	self notify( "single anim", "end" );
	self notify( "looping anim", "end" );
}

/*
=============
///ScriptDocBegin
"Name: disable_pain()"
"Summary: Disables pain on the AI"
"Module: Utility"
"CallOn: An ai"
"Example: level.zakhaev disable_pain();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_pain()
{
	AssertEx( IsAI( self ), "Tried to disable pain on a non ai" );
	self.a.disablePain = true;
	self.allowPain = false;
}

/*
=============
///ScriptDocBegin
"Name: enable_pain()"
"Summary: Enables pain on the AI"
"Module: Utility"
"CallOn: An ai"
"Example: level.zakhaev enable_pain();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_pain()
{
	AssertEx( IsAI( self ), "Tried to enable pain on a non ai" );
	self.a.disablePain = false;
	self.allowPain = true;
}

/*
=============
///ScriptDocBegin
"Name: _delete( <_delete> )"
"Summary: "
"Module: Code Wrappers"
"CallOn: An entity"
"Example: pointer = ::_delete"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
_delete()
{
	self Delete();
}

/*
=============
///ScriptDocBegin
"Name: _kill( <_kill> )"
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
_kill()
{
	self Kill();
}

/*
=============
///ScriptDocBegin
"Name: kill_wrapper( <kill_wrapper> )"
"Summary: Wrapper to safely handle killing entities. Does special checks to ensure stability when killing players in Special Ops. Returns true or false depending on whether it actually killed the player."
"Module: Entity"
"CallOn: An entity"
"Example: level.player kill_wrapper();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
kill_wrapper()
{
	// Only do special checking in special ops for now, and only on players.
	// Players are put into invulnerable states that are unpredictable in Special Ops which can result in
	// attempts to call kill() directly to assert. If the special op has already terminated just exit out. If the
	// player is downed force invulnerability off so the kill will be able to succeed.
	
	if ( isplayer( self ) )
	{
		if ( flag_exist( "special_op_terminated" ) && flag( "special_op_terminated" ) )
		{
			return false;
		}

		if ( is_player_down( self ) )
		{
			self disableinvulnerability();
		}
	}
	
	self EnableDeathShield( false );
	self kill();
	return true;
}

/*
=============
///ScriptDocBegin
"Name: _setentitytarget( <target> )"
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
_setentitytarget( target )
{
	self SetEntityTarget( target );
}

/*
=============
///ScriptDocBegin
"Name: _ClearEntityTarget()"
"Summary: "
"Module: Code Wrappers"
"CallOn: An entity"
"Example: pointer = ::_ClearEntityTarget"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
_ClearEntityTarget()
{
	self ClearEntityTarget();
}

/*
=============
///ScriptDocBegin
"Name: _unlink()"
"Summary: "
"Module: Code Wrappers"
"CallOn: An entity"
"Example: pointer = ::_unlink"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
_unlink()
{
	self Unlink();
}


/*
=============
///ScriptDocBegin
"Name: disable_oneshotfx_with_noteworthy( <noteworthy> )"
"Summary: Disables _global_fx that have the given noteworthy on them"
"Module: Utility"
"MandatoryArg: <noteworthy>: The script_noteworthy"
"Example: disable_oneshotfx_with_noteworthy( "blackout_spotlight_fx" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_oneshotfx_with_noteworthy( noteworthy )
{
	AssertEx( IsDefined( level._global_fx_ents[ noteworthy ] ), "No _global_fx ents have noteworthy " + noteworthy );
	keys = GetArrayKeys( level._global_fx_ents[ noteworthy ] );
	for ( i = 0; i < keys.size; i++ )
	{
		level._global_fx_ents[ noteworthy ][ keys[ i ] ].looper Delete();
		level._global_fx_ents[ noteworthy ][ keys[ i ] ] = undefined;
	}
}

/*
=============
///ScriptDocBegin
"Name: _setLightIntensity( <val> )"
"Summary: function pointer to code command SetLightIntensity()"
"Module: Code Wrappers"
"CallOn: An entity"
"MandatoryArg: <val>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

_setLightIntensity( val )
{
	self SetLightIntensity( val );
}


/*
=============
///ScriptDocBegin
"Name: _linkto( <targ> , <tag> , <org> , <angles> )"
"Summary: wrapper for linkto
"Module: Code Wrappers"
"CallOn: An entity"
"MandatoryArg: <targ>: "
"OptionalArg: <tag>: "
"OptionalArg: <org>: "
"OptionalArg: <angles>: "
"Example: array_thread( guys, ::_linkto, blackhawk, "tag_detach" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
_linkto( targ, tag, org, angles )
{
	if ( IsDefined( angles ) )
	{
		self LinkTo( targ, tag, org, angles );
		return;
	}
	if ( IsDefined( org ) )
	{
		self LinkTo( targ, tag, org );
		return;
	}
	if ( IsDefined( tag ) )
	{
		self LinkTo( targ, tag );
		return;
	}
	self LinkTo( targ );
}

/*
=============
///ScriptDocBegin
"Name: array_wait( <array>, <msg>, <timeout> )"
"Summary: waits for every entry in the <array> to recieve the <msg> notify, die, or timeout"
"Module: Utility"
"MandatoryArg: <array>: the array of entities to wait on"
"MandatoryArg: <msg>: the msg each array entity will wait on"
"OptionalArg: <timeout>: timeout to kill the wait prematurely"
"Example: array_wait( guys, "at the hq" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_wait( array, msg, timeout )
{
	keys = GetArrayKeys( array );
	structs = [];
	for ( i = 0; i < keys.size; i++ )
	{
		key = keys[ i ];

	}

	for ( i = 0; i < keys.size; i++ )
	{
		key = keys[ i ];
		structs[ key ] = SpawnStruct();
		structs[ key ]._array_wait = true;

		structs[ key ] thread array_waitlogic1( array[ key ], msg, timeout );
	}

	for ( i = 0; i < keys.size; i++ )
	{
		key = keys[ i ];
		if ( IsDefined( array[ key ] ) && structs[ key ]._array_wait )
			structs[ key ] waittill( "_array_wait" );
	}
}

/*
=============
///ScriptDocBegin
"Name: die()"
"Summary: The entity does damage to itself of > health value"
"Module: Utility"
"CallOn: An entity"
"Example: enemy die();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
die()
{
	self Kill( ( 0, 0, 0 ) );
}

/*
=============
///ScriptDocBegin
"Name: getmodel( <model> )"
"Summary: Returns the level.scr_model[ model ]"
"Module: Utility"
"MandatoryArg: <model>: The string index into level.scr_model"
"Example: SetModel( getmodel( "zakhaevs arm" ) );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
getmodel( str )
{
	AssertEx( IsDefined( level.scr_model[ str ] ), "Tried to getmodel on model " + str + " but level.scr_model[ " + str + " was not defined." );
	return level.scr_model[ str ];
}

/*
=============
///ScriptDocBegin
"Name: isADS()"
"Summary: Returns true if the player is more than 50% ads"
"Module: Utility"
"Example: player_is_ads = isADS();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
isADS()
{
	Assert( IsPlayer( self ) );
	return( self PlayerAds() > 0.5 );
}

/*
=============
///ScriptDocBegin
"Name: enable_auto_adjust_threatbias()"
"Summary: Allows auto adjust to change the player threatbias. Defaults to on"
"Module: Utility"
"Example: enable_auto_adjust_threatbias();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

enable_auto_adjust_threatbias()
{
	// this needs to be made to work again, broke when coop difficulty was done
	// (sorry)

	level.auto_adjust_threatbias = true;

	if ( level.gameskill >= 2 )
	{
		// hard and vet use locked values
		level.player.threatbias = Int( maps\_gameskill::get_locked_difficulty_val_player( "threatbias", 1 ) );
		return;
	}

	// set the threatbias based on the current difficulty frac
	level.auto_adjust_difficulty_frac = GetDvarInt( "autodifficulty_frac" );
	current_frac = level.auto_adjust_difficulty_frac * 0.01;
	level.player.threatbias = Int( maps\_gameskill::get_blended_difficulty( "threatbias", current_frac ) );
}

/*
=============
///ScriptDocBegin
"Name: disable_auto_adjust_threatbias()"
"Summary: Disallows auto adjust to change the player threatbias. Defaults to on"
"Module: Utility"
"Example: disable_auto_adjust_threatbias();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

disable_auto_adjust_threatbias()
{
	level.auto_adjust_threatbias = false;
}

/*
=============
///ScriptDocBegin
"Name: disable_replace_on_death()"
"Summary: Disables replace on death"
"Module: Color"
"CallOn: An AI"
"Example: guy disable_replace_on_death();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_replace_on_death()
{
	self.replace_on_death = undefined;
	self notify( "_disable_reinforcement" );
}

/*
=============
///ScriptDocBegin
"Name: waittill_player_lookat( <dot>, <timer>, <dot_only>, <timeout>  )"
"Summary: Waits until the player is looking at this entity."
"Module: Utility"
"CallOn: An AI or entity"
"OptionalArg: <dot>: Overwrite the default dot of .92 "
"OptionalArg: <timer>: Optional parameter to control how long you have to look before it triggers"
"OptionalArg: <dot_only>: Set to false if the player must trace to the entity to pass"
"OptionalArg: <timeout>: Time to pass before this function will timeout and give up"
"OptionalArg: <player>: When specified, is the player you want to detect is doing the looking."
"Example: level.price waittill_player_lookat();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waittill_player_lookat( dot, timer, dot_only, timeout, ignore_ent, player )
{
	if ( !isdefined( player ) )
		player = level.player;

	timeoutEnt = SpawnStruct();
	if ( IsDefined( timeout ) )
		timeoutEnt thread notify_delay( "timeout", timeout );
	timeoutEnt endon( "timeout" );

	if ( !isdefined( dot ) )
		dot = 0.92;

	if ( !isdefined( timer ) )
		timer = 0;

	base_time = Int( timer * 20 );
	count = base_time;
	self endon( "death" );
	ai_guy = IsAI( self );
	org = undefined;
	for ( ;; )
	{
		if ( ai_guy )
			org = self GetEye();
		else
			org = self.origin;

		if ( player player_looking_at( org, dot, dot_only, ignore_ent ) )
		{
			count--;
			if ( count <= 0 )
				return true;
		}
		else
		{
			count = base_time;
		}
		wait( 0.05 );
	}
}

/*
=============
///ScriptDocBegin
"Name: waittill_player_lookat_for_time( <timer> , <dot> )"
"Summary: Wait until the player is looking at this entity for x time"
"Module: Utility"
"CallOn: An AI"
"MandatoryArg: <timer>: How long the player must look before the timer passes "
"OptionalArg: <dot>: Optional override dot"
"OptionalArg: <dot_only>: If true, it will only check FOV and not tracepassed"
"Example: self waittill_player_lookat_for_time( 0.5 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waittill_player_lookat_for_time( timer, dot, dot_only, ignore_ent )
{
	AssertEx( IsDefined( timer ), "Tried to do waittill_player_lookat_for_time with no time parm." );
	waittill_player_lookat( dot, timer, dot_only, undefined, ignore_ent );
}

/*
=============
///ScriptDocBegin
"Name: player_looking_at( <org>, <dot> )"
"Summary: Checks to see if the player can dot and trace to a point"
"Module: Utility"
"MandatoryArg: <org>: The position you're checking if the player is looking at"
"OptionalArg: <dot>: Optional override dot"
"OptionalArg: <dot_only>: If true, it will only check FOV and not tracepassed"
"Example: if ( player_looking_at( org.origin ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_looking_at( start, dot, dot_only, ignore_ent )
{
	if ( !isdefined( dot ) )
		dot = 0.8;
	player = get_player_from_self();

	end = player GetEye();

	angles = VectorToAngles( start - end );
	forward = AnglesToForward( angles );
	player_angles = player GetPlayerAngles();
	player_forward = AnglesToForward( player_angles );

	new_dot = VectorDot( forward, player_forward );
	if ( new_dot < dot )
	{
		return false;
	}

	if ( IsDefined( dot_only ) )
	{
		AssertEx( dot_only, "dot_only must be true or undefined" );
		return true;
	}

	trace = BulletTrace( start, end, false, ignore_ent );
	return trace[ "fraction" ] == 1;
}


/*
=============
///ScriptDocBegin
"Name: players_looking_at( <org>, <dot>, <dot_only> )"
"Summary: Checks to see if all players can dot and trace to a point"
"Module: Utility"
"MandatoryArg: <org>: The position you're checking if the players are all looking at"
"OptionalArg: <dot>: Optional override dot"
"OptionalArg: <dot_only>: If true, it will only check FOV and not tracepassed"
"Example: if ( players_looking_at( org.origin ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
players_looking_at( org, dot, dot_only, ignore_ent )
{
	for ( i = 0; i < level.players.size; i++ )
	{
		if ( !level.players[ i ] player_looking_at( org, dot, dot_only, ignore_ent ) )
			return false;
	}
	return true;
}

/*
=============
///ScriptDocBegin
"Name: either_player_looking_at( <org>, <dot>, <dot_only> )"
"Summary: returns true when either of the two players can trace and/or dot to a point"
"Module: Utility"
"MandatoryArg: <org>: The position you're checking if a player is looking at"
"OptionalArg: <dot>: Optional override dot"
"OptionalArg: <dot_only>: If true, it will only check FOV and not tracepassed"
"Example: if ( either_player_looking_at( org.origin ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
either_player_looking_at( org, dot, dot_only, ignore_ent )
{
	for ( i = 0; i < level.players.size; i++ )
	{
		if ( level.players[ i ] player_looking_at( org, dot, dot_only, ignore_ent ) )
			return true;
	}
	return false;
}


/*
=============
///ScriptDocBegin
"Name: player_can_see_ai( <ai> )"
"Summary: Rough method to test if an AI is in view of the player - only checks three points on the AI (low, mid, high)."
"Module: Utility"
"MandatoryArg: <ai>: The AI whom you're testing if the player can see."
"Example: if( player_can_see_ai( ambushGuy ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_can_see_ai( ai, latency )
{
	currentTime = getTime();

	if ( !isdefined( latency ) )
		latency = 0;

	if ( isdefined( ai.playerSeesMeTime ) && ai.playerSeesMeTime + latency >= currentTime )
	{
		assert( isdefined( ai.playerSeesMe ) );
		return ai.playerSeesMe;
	}

	ai.playerSeesMeTime = currentTime;

	if ( !within_fov( level.player.origin, level.player.angles, ai.origin, 0.766 ) )
	{
		ai.playerSeesMe = false;
		return false;
	}

	playerEye = level.player GetEye();

	feetOrigin = ai.origin;
	if ( SightTracePassed( playerEye, feetOrigin, true, level.player, ai ) )
	{
		ai.playerSeesMe = true;
		return true;
	}

	eyeOrigin = ai GetEye();
	if ( SightTracePassed( playerEye, eyeOrigin, true, level.player, ai ) )
	{
		ai.playerSeesMe = true;
		return true;
	}

	midOrigin = ( eyeOrigin + feetOrigin ) * 0.5;
	if ( SightTracePassed( playerEye, midOrigin, true, level.player, ai ) )
	{
		ai.playerSeesMe = true;
		return true;
	}

	ai.playerSeesMe = false;
	return false;
}


/*
=============
///ScriptDocBegin
"Name: players_within_distance( <fDist>, <org> )"
"Summary: Determines if any players are within a distance of a certain point. Returns false if any players are within the distance"
"Module: Utility"
"MandatoryArg: <fDist>: The distance away from the <org>"
"MandatoryArg: <org>: The location in space we are checking distance from"
"Example: if ( players_within_distance( 1024, enemy.origin ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
players_within_distance( fDist, org )
{
	fDistSquared = fDist * fDist;
	for ( i = 0; i < level.players.size; i++ )
	{
		if ( DistanceSquared( org, level.players[ i ].origin ) < fDistSquared )
			return true;
	}
	return false;
}
/*
=============
///ScriptDocBegin
"Name: AI_delete_when_out_of_sight( <aAI_to_delete>, <fDist> )"
"Summary: Deletes all of the AI in the array passed as players reach a certain distance away (and are not looking at them)"
"Module: Utility"
"MandatoryArg: <aAI_to_delete>: The array of AI to delete"
"MandatoryArg: <fDist>: The distance away from the players the AI will be deleted"
"Example: thread AI_delete_when_out_of_sight( aEnemies, 2048 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
AI_delete_when_out_of_sight( aAI_to_delete, fDist )
{
	if ( !isdefined( aAI_to_delete ) )
		return;

	off_screen_dot = 0.75;
	if ( IsSplitScreen() )
	{
		off_screen_dot = 0.65;
	}

	while ( aAI_to_delete.size > 0 )
	{
		wait( 1 );

		for ( i = 0; i < aAI_to_delete.size; i++ )
		{
			/*-----------------------
			KEEP LOOPING AND REMOVE ENEMY IF DEAD/DELETED
			-------------------------*/
			if ( ( !isdefined( aAI_to_delete[ i ] ) ) || ( !isalive( aAI_to_delete[ i ] ) ) )
			{
				aAI_to_delete = array_remove( aAI_to_delete, aAI_to_delete[ i ] );
				continue;
			}
			/*-----------------------
			KEEP LOOPING IF ANY PLAYERS TOO CLOSE OR IS FACING THE AI
			-------------------------*/
			if ( players_within_distance( fDist, aAI_to_delete[ i ].origin ) )
				continue;
			if ( either_player_looking_at( aAI_to_delete[ i ].origin + ( 0, 0, 48 ), off_screen_dot, true ) )
				continue;
			/*-----------------------
			ALL TESTS PASSED, DELETE THE BASTARD
			-------------------------*/
			if ( IsDefined( aAI_to_delete[ i ].magic_bullet_shield ) )
				aAI_to_delete[ i ] stop_magic_bullet_shield();
			aAI_to_delete[ i ] Delete();
			aAI_to_delete = array_remove( aAI_to_delete, aAI_to_delete[ i ] );
		}
	}
}
/*
=============
///ScriptDocBegin
"Name: add_wait( <func> , <parm1> , <parm2> , <parm3> )"
"Summary: Adds a function that you want to wait for completion on. Self of the function will be whatever add_wait is called on. Make sure you call add_wait before any wait, since the functions are stored globally."
"Module: Utility"
"MandatoryArg: <func>: The function."
"OptionalArg: <parm1>: Optional parameter"
"OptionalArg: <parm2>: Optional parameter"
"OptionalArg: <parm3>: Optional parameter"
"Example: add_wait( ::waittill_player_lookat );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_wait( func, parm1, parm2, parm3 )
{
	/#
	thread add_wait_asserter();
	#/

	ent = SpawnStruct();

	ent.caller = self;
	ent.func = func;
	ent.parms = [];
	if ( IsDefined( parm1 ) )
	{
		ent.parms[ ent.parms.size ] = parm1;
	}
	if ( IsDefined( parm2 ) )
	{
		ent.parms[ ent.parms.size ] = parm2;
	}
	if ( IsDefined( parm3 ) )
	{
		ent.parms[ ent.parms.size ] = parm3;
	}

	level.wait_any_func_array[ level.wait_any_func_array.size ] = ent;
}
/*
=============
///ScriptDocBegin
"Name: add_abort( <func> , <parm1> , <parm2> , <parm3> )"
"Summary: Adds a function that when completed aborts both the do_wait and any add_funcs added to the system."
"Module: Utility"
"MandatoryArg: <func>: The function."
"OptionalArg: <parm1>: Optional parameter"
"OptionalArg: <parm2>: Optional parameter"
"OptionalArg: <parm3>: Optional parameter"
"Example: add_abort( ::flag_wait, "shazam" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_abort( func, parm1, parm2, parm3 )
{
	/#
	thread add_wait_asserter();
	#/

	ent = SpawnStruct();

	ent.caller = self;
	ent.func = func;
	ent.parms = [];
	if ( IsDefined( parm1 ) )
	{
		ent.parms[ ent.parms.size ] = parm1;
	}
	if ( IsDefined( parm2 ) )
	{
		ent.parms[ ent.parms.size ] = parm2;
	}
	if ( IsDefined( parm3 ) )
	{
		ent.parms[ ent.parms.size ] = parm3;
	}

	level.abort_wait_any_func_array[ level.abort_wait_any_func_array.size ] = ent;
}

/*
=============
///ScriptDocBegin
"Name: add_func( <func> , <parm1> , <parm2> , <parm3> )"
"Summary: Adds a function that runs after an add_wait/do_wait completes."
"Module: Utility"
"MandatoryArg: <func>: The function."
"OptionalArg: <parm1>: Optional parameter"
"OptionalArg: <parm2>: Optional parameter"
"OptionalArg: <parm3>: Optional parameter"
"Example: add_func( ::waittill_player_lookat );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_func( func, parm1, parm2, parm3, parm4, parm5 )
{
	/#
	thread add_wait_asserter();
	#/

	ent = SpawnStruct();

	ent.caller = self;
	ent.func = func;
	ent.parms = [];
	if ( IsDefined( parm1 ) )
	{
		ent.parms[ ent.parms.size ] = parm1;
	}
	if ( IsDefined( parm2 ) )
	{
		ent.parms[ ent.parms.size ] = parm2;
	}
	if ( IsDefined( parm3 ) )
	{
		ent.parms[ ent.parms.size ] = parm3;
	}
	if ( IsDefined( parm4 ) )
	{
		ent.parms[ ent.parms.size ] = parm4;
	}
	if ( IsDefined( parm5 ) )
	{
		ent.parms[ ent.parms.size ] = parm5;
	}

	level.run_func_after_wait_array[ level.run_func_after_wait_array.size ] = ent;
}

/*
=============
///ScriptDocBegin
"Name: add_call( <func> , <parm1> , <parm2> , <parm3> )"
"Summary: Adds a code function call that runs after an add_wait/do_wait completes."
"Module: Utility"
"MandatoryArg: <func>: The function."
"OptionalArg: <parm1>: Optional parameter"
"OptionalArg: <parm2>: Optional parameter"
"OptionalArg: <parm3>: Optional parameter"
"Example: level.player add_call( ::playerlinktodelta, node );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_call( func, parm1, parm2, parm3, parm4, parm5 )
{
	/#
	thread add_wait_asserter();
	#/

	ent = SpawnStruct();

	ent.caller = self;
	ent.func = func;
	ent.parms = [];
	if ( IsDefined( parm1 ) )
	{
		ent.parms[ ent.parms.size ] = parm1;
	}
	if ( IsDefined( parm2 ) )
	{
		ent.parms[ ent.parms.size ] = parm2;
	}
	if ( IsDefined( parm3 ) )
	{
		ent.parms[ ent.parms.size ] = parm3;
	}
	if ( IsDefined( parm4 ) )
	{
		ent.parms[ ent.parms.size ] = parm4;
	}
	if ( IsDefined( parm5 ) )
	{
		ent.parms[ ent.parms.size ] = parm5;
	}

	level.run_call_after_wait_array[ level.run_call_after_wait_array.size ] = ent;
}

/*
=============
///ScriptDocBegin
"Name: add_noself_call( <func> , <parm1> , <parm2> , <parm3> )"
"Summary: Adds a code function call that runs after an add_wait/do_wait completes."
"Module: Utility"
"MandatoryArg: <func>: The function."
"OptionalArg: <parm1>: Optional parameter"
"OptionalArg: <parm2>: Optional parameter"
"OptionalArg: <parm3>: Optional parameter"
"Example: add_noself_call( ::earthquake, blah, blah, blah );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_noself_call( func, parm1, parm2, parm3, parm4, parm5 )
{
	/#
	thread add_wait_asserter();
	#/

	ent = SpawnStruct();

	ent.func = func;
	ent.parms = [];
	if ( IsDefined( parm1 ) )
	{
		ent.parms[ ent.parms.size ] = parm1;
	}
	if ( IsDefined( parm2 ) )
	{
		ent.parms[ ent.parms.size ] = parm2;
	}
	if ( IsDefined( parm3 ) )
	{
		ent.parms[ ent.parms.size ] = parm3;
	}
	if ( IsDefined( parm4 ) )
	{
		ent.parms[ ent.parms.size ] = parm4;
	}
	if ( IsDefined( parm5 ) )
	{
		ent.parms[ ent.parms.size ] = parm5;
	}

	level.run_noself_call_after_wait_array[ level.run_noself_call_after_wait_array.size ] = ent;
}

/*
=============
///ScriptDocBegin
"Name: add_endon( <endon> )"
"Summary: Adds an endon that will kill a do_wait. Threads can't acquire a parent's endons so this is a way to force an endon in cases where a do_wait could be killed, otherwise it'll cause a thread leak."
"Module: Utility"
"MandatoryArg: <endon>: The endon."
"Example: level.price add_endon( "shazam" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_endon( name )
{
	/#
	thread add_wait_asserter();
	#/

	ent = SpawnStruct();
	ent.caller = self;
	ent.ender = name;

	level.do_wait_endons_array[ level.do_wait_endons_array.size ] = ent;
}

/*
=============
///ScriptDocBegin
"Name: do_wait_any()"
"Summary: Waits until any of functions defined by add_wait complete. Clears the global variable where the functions were being stored."
"Module: Utility"
"Example: do_wait_any();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
do_wait_any()
{
	AssertEx( IsDefined( level.wait_any_func_array ), "Tried to do a do_wait without addings funcs first" );
	AssertEx( level.wait_any_func_array.size > 0, "Tried to do a do_wait without addings funcs first" );
	do_wait( level.wait_any_func_array.size - 1 );
}

/*
=============
///ScriptDocBegin
"Name: do_wait()"
"Summary: Waits until all of the functions defined by add_wait complete. Clears the global variable where the functions were being stored."
"Module: Utility"
"Example: do_wait();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
do_wait( count_to_reach )
{
	if ( !isdefined( count_to_reach ) )
		count_to_reach = 0;

	/#
	level notify( "kill_add_wait_asserter" );
	#/

	AssertEx( IsDefined( level.wait_any_func_array ), "Tried to do a do_wait without addings funcs first" );
	ent = SpawnStruct();
	array 		 = level.wait_any_func_array;
	endons 		 = level.do_wait_endons_array;
	after_array = level.run_func_after_wait_array;
	call_array	 = level.run_call_after_wait_array;
	nscall_array = level.run_noself_call_after_wait_array;
	abort_array = level.abort_wait_any_func_array;

 	level.wait_any_func_array 		 = [];
 	level.run_func_after_wait_array = [];
 	level.do_wait_endons_array 		 = [];
 	level.abort_wait_any_func_array = [];
 	level.run_call_after_wait_array = [];
 	level.run_noself_call_after_wait_array = [];

	ent.count = array.size;

	ent array_levelthread( array, ::waittill_func_ends, endons );
	ent thread do_abort( abort_array );

	ent endon( "any_funcs_aborted" );

	for ( ;; )
	{
		if ( ent.count <= count_to_reach )
			break;
		ent waittill( "func_ended" );
	}
	ent notify( "all_funcs_ended" );

	array_levelthread( after_array, ::exec_func, [] );
	array_levelthread( call_array, ::exec_call );
	array_levelthread( nscall_array, ::exec_call_noself );
}

/*
=============
///ScriptDocBegin
"Name: do_funcs()"
"Summary: Calls a series of add_funcs in order. When one finishes, the next starts. Etc."
"Module: Utility"
"Example: thread do_funcs();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
do_funcs()
{
	/#
	level notify( "kill_add_wait_asserter" );
	#/

	AssertEx( IsDefined( level.wait_any_func_array ), "Tried to do a do_wait without addings funcs first" );
	ent = SpawnStruct();

	AssertEx( !level.wait_any_func_array.size, "Don't use add_wait and do_funcs together." );
	AssertEx( !level.do_wait_endons_array.size, "Don't use add_endon and do_funcs together." );
	AssertEx( !level.run_call_after_wait_array.size, "Don't use add_call and do_funcs together." );
	AssertEx( !level.run_noself_call_after_wait_array.size, "Don't use add_call and do_funcs together." );
	AssertEx( !level.abort_wait_any_func_array.size, "Do_funcs doesn't support add_abort." );

	after_array = level.run_func_after_wait_array;

 	level.run_func_after_wait_array = [];

 	foreach ( func_struct in after_array )
 	{
 		level exec_func( func_struct, [] );
 	}

	ent notify( "all_funcs_ended" );
}

/*
=============
///ScriptDocBegin
"Name: is_default_start()"
"Summary: Returns true if you're playing from the default start"
"Module: Utility"
"Example: if ( is_default_start() )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_default_start()
{
    if( isdefined( level.forced_start_catchup ) &&  level.forced_start_catchup == true )
        return false;
    
	if ( IsDefined( level.default_start_override ) && level.default_start_override == level.start_point )
		return true;

	if ( IsDefined( level.default_start ) )
		return level.start_point == "default";

	if ( level_has_start_points() )
		return level.start_point == level.start_functions[ 0 ][ "name" ];

	return level.start_point == "default";
}


/*
=============
///ScriptDocBegin
"Name: force_start_catchup()"
"Summary: used in test map sections of the full level. setting this makes is_default_start() return false. "
"Module: Entity"
"CallOn: An entity"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

force_start_catchup()
{
    level.forced_start_catchup = true;
}

/*
=============
///ScriptDocBegin
"Name: is_first_start()"
"Summary: Returns true if it is the first start point in the list of starts."
"Module: Utility"
"Example: if ( is_first_start() )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_first_start()
{
	if ( !level_has_start_points() )
		return true;

	return level.start_point == level.start_functions[ 0 ][ "name" ];
}



/*
=============
///ScriptDocBegin
"Name: is_after_start( <name> )"
"Summary: returns true if the current start point is after name, useful for handling things that have already happened in a start point."
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <name>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

is_after_start( name )
{
	hit_current_start = false;

	if( level.start_point == name )
		return false;

	for ( i = 0; i < level.start_functions.size; i++ )
	{
		if ( level.start_functions[ i ][ "name" ] == name )
		{
			hit_current_start = true;
			continue;
		}
		if( level.start_functions[ i ][ "name" ] == level.start_point )
			return hit_current_start;
	}
}

/*
=============
///ScriptDocBegin
"Name: _Earthquake( <scale> , <duration> , <source> , <radius> )"
"Summary: Wrapper for earthquake command"
"Module: Code Wrappers"
"CallOn: Level"
"MandatoryArg: <scale>: "
"MandatoryArg: <duration>: "
"MandatoryArg: <source>: "
"MandatoryArg: <radius>: "
"Example: delayThread( 0.1, ::_Earthquake, 0.4, 1.2, ent.origin, 6000 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
_Earthquake( scale, duration, source, radius )
{
	Earthquake( scale, duration, source, radius );
}

/*
=============
///ScriptDocBegin
"Name: waterfx( <endflag> )"
"Summary: Makes AI have trails in water. Can be used on the player as well, so you're not a vampire."
"Module: Utility"
"CallOn: An AI or player"
"OptionalArg: <endflag>: A flag to end on "
"Example: level.price thread waterfx();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waterfx( endflag, soundalias )
{
// currently using these devraw fx:
//	level._effect[ "water_stop" ]						= LoadFX( "misc/parabolic_water_stand" );
//	level._effect[ "water_movement" ]					= LoadFX( "misc/parabolic_water_movement" );

	self endon( "death" );

	play_sound = false;
	if ( IsDefined( soundalias ) )
		play_sound = true;

	if ( IsDefined( endflag ) )
	{
		flag_assert( endflag );
		level endon( endflag );
	}
	for ( ;; )
	{
		wait( RandomFloatRange( 0.15, 0.3 ) );
		start = self.origin + ( 0, 0, 150 );
		end = self.origin - ( 0, 0, 150 );
		trace = BulletTrace( start, end, false, undefined );
		if ( trace[ "surfacetype" ] != "water" )
			continue;

		fx = "water_movement";
		
		if ( IsPlayer( self ) )
		{
			if ( Distance( self GetVelocity(), ( 0, 0, 0 ) ) < 5 )
			{
				fx = "water_stop";
			}
		}
		else if ( IsDefined( level._effect[ "water_" + self.a.movement ] ) )
		{
			fx = "water_" + self.a.movement;
		}

		water_fx = getfx( fx );
		start = trace[ "position" ];
		//angles = vectortoangles( trace[ "normal" ] );
		angles = (0,self.angles[1],0);
		forward = anglestoforward( angles );
		up = anglestoup( angles );
		PlayFX( water_fx, start, up, forward );
		
		if ( fx != "water_stop" && play_sound )
			thread play_sound_in_space( soundalias, start );
	}
}

/*
=============
///ScriptDocBegin
"Name: playerSnowFootsteps( <endflag> )"
"Summary: Make the player have footstep fx in snow"
"Module: Utility"
"CallOn: player"
"OptionalArg: <endflag>: A flag to end on "
"Example: level.player thread playerSnowFootsteps();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
playerSnowFootsteps( endflag )
{
// currently using these devraw fx:
//	level._effect[ "footstep_snow_small" ]				= LoadFX( "impacts/footstep_snow_small" );
//	level._effect[ "footstep_snow" ]					= LoadFX( "impacts/footstep_snow" );

	if ( IsDefined( endflag ) )
	{
		flag_assert( endflag );
		level endon( endflag );
	}

	for ( ;; )
	{
		wait( RandomFloatRange( 0.25, .5 ) );
		start = self.origin + ( 0, 0, 0 );
		end = self.origin - ( 0, 0, 5 );
		trace = BulletTrace( start, end, false, undefined );
		forward = AnglesToForward( self.angles );
		mydistance = Distance( self GetVelocity(), ( 0, 0, 0 ) );
		if ( IsDefined( self.vehicle ) )
			continue;
		if ( trace[ "surfacetype" ] != "snow" )
			continue;
		if ( mydistance <= 10 )
			continue;
		fx = "snow_movement";
		//iprintlnbold( "Moved" + mydistance );
		if ( Distance( self GetVelocity(), ( 0, 0, 0 ) ) <= 154 )
		{
			PlayFX( getfx( "footstep_snow_small" ), trace[ "position" ], trace[ "normal" ], forward );
		}
		if ( Distance( self GetVelocity(), ( 0, 0, 0 ) ) > 154 )
		{
			PlayFX( getfx( "footstep_snow" ), trace[ "position" ], trace[ "normal" ], forward );
		}
	}
}


/*
=============
///ScriptDocBegin
"Name: mix_up( <sound> )"
"Summary: Used to blend sounds on a script model vehicle. See maps\sniperescape_code::seaknight_sound()"
"Module: Utility"
"CallOn: A sound blend entity"
"OptionalArg: <Sound>: The sound alias to blend, blends with the _off version of the alias. "
"Example: maps\sniperescape_code::seaknight_sound();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
mix_up( sound )
{
	timer = 3 * 20;
	for ( i = 0; i < timer; i++ )
	{
		self SetSoundBlend( sound, sound + "_off", ( timer - i ) / timer );
		wait( 0.05 );
	}
}

/*
=============
///ScriptDocBegin
"Name: mix_down( <sound> )"
"Summary: Used to blend sounds on a script model vehicle. See maps\sniperescape_code::seaknight_sound()"
"Module: Utility"
"CallOn: A sound blend entity"
"OptionalArg: <Sound>: The sound alias to blend, blends with the _off version of the alias. "
"Example: maps\sniperescape_code::seaknight_sound();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
mix_down( sound )
{
	timer = 3 * 20;
	for ( i = 0; i < timer; i++ )
	{
		self SetSoundBlend( sound, sound + "_off", i / timer );
		wait( 0.05 );
	}
}

/*
=============
///ScriptDocBegin
"Name: manual_linkto( <entity> , <offset> )"
"Summary: Sets an entity to the origin of another entity every server frame, for entity types that don't support linkto"
"Module: Utility"
"CallOn: An entity that doesn't support linkto, like soundblend entities."
"MandatoryArg: <entity>: The entity to link to "
"OptionalArg: <offset>: The offset to use "
"Example: flyblend thread manual_linkto( self, (0,0,0) );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
manual_linkto( entity, offset )
{
	entity endon( "death" );
	self endon( "death" );
	// for entities that don't support linkto, like soundblend entities
	if ( !isdefined( offset ) )
	{
		offset = ( 0, 0, 0 );
	}

	for ( ;; )
	{
		self.origin = entity.origin + offset;
		self.angles = entity.angles;
		wait( 0.05 );
	}
}

/*
=============
///ScriptDocBegin
"Name: nextmission()"
"Summary: Sends level to nextmission via _endmission script, one place for handling transitions"
"Module: Code Wrappers"
"CallOn: Level"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

nextmission()
{
	//{NOT_IN_SHIP
	mission_recon();
	//}NOT_IN_SHIP
	maps\_endmission::_nextmission();
}

/*
=============
///ScriptDocBegin
"Name: make_array( <index1> , <index2> , <index3> , <index4> , <index5> )"
"Summary: make an array with the stuff. (up to 5 things) "
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <index1>: "
"OptionalArg: <index2>: "
"OptionalArg: <index3>: "
"OptionalArg: <index4>: "
"OptionalArg: <index5>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
make_array( index1, index2, index3, index4, index5 )
{
	AssertEx( IsDefined( index1 ), "Need to define index 1 at least" );
	array = [];
	array[ array.size ] = index1;
	if ( IsDefined( index2 ) )
	{
		array[ array.size ] = index2;
	}

	if ( IsDefined( index3 ) )
	{
		array[ array.size ] = index3;
	}

	if ( IsDefined( index4 ) )
	{
		array[ array.size ] = index4;
	}

	if ( IsDefined( index5 ) )
	{
		array[ array.size ] = index5;
	}

	return array;
}


/*
=============
///ScriptDocBegin
"Name: fail_on_friendly_fire()"
"Summary: If this is run, the player will fail the mission if he kills a friendly"
"Module: Utility"
"Example: fail_on_friendly_fire();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
fail_on_friendly_fire()
{
	level.failOnFriendlyFire = true;
}

/*
=============
///ScriptDocBegin
"Name: normal_friendly_fire_penalty()"
"Summary: Returns friendly fire penalty to normal"
"Module: Utility"
"Example: normal_friendly_fire_penalty();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
normal_friendly_fire_penalty()
{
	level.failOnFriendlyFire = false;
}

/*
=============
///ScriptDocBegin
"Name: getPlayerClaymores()"
"Summary: Returns the number of claymores the player has"
"Module: Utility"
"Example: count = getPlayerClaymores();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
getPlayerClaymores()
{
	Assert( IsPlayer( self ) );

	heldweapons = self GetWeaponsListAll();
	stored_ammo = [];
	for ( i = 0; i < heldweapons.size; i++ )
	{
		weapon = heldweapons[ i ];
		stored_ammo[ weapon ] = self GetWeaponAmmoClip( weapon );
	}


	claymoreCount = 0;
	if ( IsDefined( stored_ammo[ "claymore" ] ) && stored_ammo[ "claymore" ] > 0 )
	{
		claymoreCount = stored_ammo[ "claymore" ];
	}
	return claymoreCount;
}

/*
=============
///ScriptDocBegin
"Name: getPlayerC4()"
"Summary: Returns the number of c4 the player has"
"Module: Utility"
"Example: count = getPlayerC4();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
getPlayerC4()
{
	Assert( IsPlayer( self ) );

	heldweapons = self GetWeaponsListAll();
	stored_ammo = [];
	for ( i = 0; i < heldweapons.size; i++ )
	{
		weapon = heldweapons[ i ];
		stored_ammo[ weapon ] = self GetWeaponAmmoClip( weapon );
	}


	c4Count = 0;
	if ( IsDefined( stored_ammo[ "c4" ] ) && stored_ammo[ "c4" ] > 0 )
	{
		c4Count = stored_ammo[ "c4" ];
	}
	return c4Count;
}

/*
=============
///ScriptDocBegin
"Name: _wait( <timer> )"
"Summary: wrapper for wait command"
"Module: Code Wrappers"
"CallOn: An entity"
"MandatoryArg: <timer>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
_wait( timer )
{
	wait( timer );
}

/*
=============
///ScriptDocBegin
"Name: _waittillmatch( <msg> , <match> )"
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
_waittillmatch( msg, match )
{
	self waittillmatch( msg, match );
}

/*
=============
///ScriptDocBegin
"Name: _setsaveddvar( <var> , <val> )"
"Summary: code wrapper for setsaveddvar"
"Module: Code Wrappers"
"CallOn: Level"
"MandatoryArg: <var>: dvar"
"OptionalArg: <val>: value to set"
"Example: delayThread( 9, ::_setsaveddvar, "g_friendlynamedist", level.friendlynamedist );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
_setsaveddvar( var, val )
{
	SetSavedDvar( var, val );
}

/*
=============
///ScriptDocBegin
"Name: lerp_savedDvar( <name> , <value> , <time> )"
"Summary: lerps a saveddvar float setting over time"
"Module: dvar"
"CallOn: "
"MandatoryArg: <name>: the name of the dvar"
"MandatoryArg: <value>: the value to set it to"
"MandatoryArg: <time>: the time to blend to the new value"
"Example: thread lerp_savedDvar( "r_lightGridIntensity", .695, .75 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
lerp_savedDvar( name, value, time )
{
	curr = 	GetDvarFloat( name );

	range = value - curr;

	interval = .05;
	count = Int( time / interval );

	delta = range / count;

	while ( count )
	{
		curr += delta;
		SetSavedDvar( name, curr );

		wait interval;
		count--;
	}

	SetSavedDvar( name, value );
}

/*
=============
///ScriptDocBegin
"Name: giveachievement_wrapper( <achievement> )"
"Summary: Gives achievement to all players. Only does so if the player isn't cheating and hasn't cheated."
"Module: Code Wrappers"
"MandatoryArg: <achievement>: "
"Example: giveachievement_wrapper( "RESCUE_ROYCEWICZ" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
giveachievement_wrapper( achievement )
{
	if ( is_demo() )
	{
		return;
	}

	if( level.script == "ending" && isdefined( level.level_mode ) && level.level_mode == "free" )//char museum
		return;

	foreach ( player in level.players )
	{
		player GiveAchievement( achievement );
	}

	/#
		println( "ACHIEVEMENT: " + achievement );
	#/
}

/*
=============
///ScriptDocBegin
"Name: player_giveachievement_wrapper( <achievement> )"
"Summary: Gives achievement to a specific player. Only does so if the player isn't cheating and hasn't cheated."
"Module: Code Wrappers"
"CallOn: Player"
"MandatoryArg: <achievement>: "
"Example: player giveachievement_wrapper( "RESCUE_ROYCEWICZ" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_giveachievement_wrapper( achievement )
{
	if ( is_demo() )
	{
		return;
	}

	if( level.script == "ending" && isdefined( level.level_mode ) && level.level_mode == "free" )//char museum
		return;

	self GiveAchievement( achievement );

	/#
		println( "ACHIEVEMENT: " + achievement );
	#/
}

/*
=============
///ScriptDocBegin
"Name: add_jav_glow( <optional_glow_delete_flag> )"
"Summary: Adds glow to the Javelin."
"Module: Utility"
"CallOn: A Javelin weapon"
"OptionalArg: <optional_glow_delete_flag>: Flag to disable the glow. "
"Example: jav thread add_jav_glow( "overpass_baddies_flee" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_jav_glow( optional_glow_delete_flag )
{
	jav_glow = Spawn( "script_model", ( 0, 0, 0 ) );
	jav_glow SetContents( 0 );
	jav_glow SetModel( "weapon_javelin_obj" );

	jav_glow.origin = self.origin;
	jav_glow.angles = self.angles;

	self add_wait( ::delete_on_not_defined );
	if ( IsDefined( optional_glow_delete_flag ) )
	{
		flag_assert( optional_glow_delete_flag );
		add_wait( ::flag_wait, optional_glow_delete_flag );
	}

	do_wait_any();

	jav_glow Delete();
}

/*
=============
///ScriptDocBegin
"Name: add_c4_glow( <optional_glow_delete_flag> )"
"Summary: Adds glow to the C4."
"Module: Utility"
"CallOn: A C4 weapon"
"OptionalArg: <optional_glow_delete_flag>: Flag to disable the glow. "
"Example: c4 thread add_c4_glow( "overpass_baddies_flee" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_c4_glow( optional_glow_delete_flag )
{
	c4_glow = Spawn( "script_model", ( 0, 0, 0 ) );
	c4_glow SetContents( 0 );
	c4_glow SetModel( "weapon_c4_obj" );

	c4_glow.origin = self.origin;
	c4_glow.angles = self.angles;

	self add_wait( ::delete_on_not_defined );
	if ( IsDefined( optional_glow_delete_flag ) )
	{
		flag_assert( optional_glow_delete_flag );
		add_wait( ::flag_wait, optional_glow_delete_flag );
	}

	do_wait_any();

	c4_glow Delete();
}

/*
=============
///ScriptDocBegin
"Name: delete_on_not_defined()"
"Summary: Weapons don't seem to notify death when they're picked up."
"Module: Utility"
"CallOn: An entity"
"Example: javelin delete_on_not_defined()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
delete_on_not_defined()
{
	for ( ;; )
	{
		if ( !isdefined( self ) )
			return;
		wait( 0.05 );
	}
}




/*
=============
///ScriptDocBegin
"Name: slowmo_start( <slowmo_start> )"
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
slowmo_start()
{
}

/*
=============
///ScriptDocBegin
"Name: slowmo_end( <slowmo_end> )"
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
slowmo_end()
{
}

/*
=============
///ScriptDocBegin
"Name: slowmo_setspeed_slow( <speed> )"
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
slowmo_setspeed_slow( speed )
{
	level.slowmo.speed_slow = speed;
}

/*
=============
///ScriptDocBegin
"Name: slowmo_setspeed_norm( <speed> )"
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
slowmo_setspeed_norm( speed )
{
	level.slowmo.speed_norm = speed;
}

/*
=============
///ScriptDocBegin
"Name: slowmo_setlerptime_in( <time> )"
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
slowmo_setlerptime_in( time )
{
	level.slowmo.lerp_time_in = time;
}

/*
=============
///ScriptDocBegin
"Name: slowmo_setlerptime_out( <time> )"
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
slowmo_setlerptime_out( time )
{
	level.slowmo.lerp_time_out = time;
}

/*
=============
///ScriptDocBegin
"Name: slowmo_lerp_in( <slowmo_lerp_in> )"
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
slowmo_lerp_in()
{
	if(IsDefined(level.no_slowmo) && level.no_slowmo)
		return;
	
	SetSlowMotion( level.slowmo.speed_norm, level.slowmo.speed_slow, level.slowmo.lerp_time_in );
	//setslowmotionview( level.slowmo.speed_norm, level.slowmo.speed_slow, level.slowmo.lerp_time_in ); //changed  for slomo breach
}

/*
=============
///ScriptDocBegin
"Name: slowmo_lerp_out( <slowmo_lerp_out> )"
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
slowmo_lerp_out()
{	
	if(IsDefined(level.no_slowmo) && level.no_slowmo)
		return;
	
	setslowmotion( level.slowmo.speed_slow, level.slowmo.speed_norm, level.slowmo.lerp_time_out );
}

/*
=============
///ScriptDocBegin
"Name: add_earthquake( <name> , <mag> , <duration> , <radius> )"
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
add_earthquake( name, mag, duration, radius )
{
	level.earthquake[ name ][ "magnitude" ] = mag;
	level.earthquake[ name ][ "duration" ] = duration;
	level.earthquake[ name ][ "radius" ] = radius;
}

/*
=============
///ScriptDocBegin
"Name: arcadeMode_kill( <origin> , <damage_type> , <amount> )"
"Summary: Rewards points for a kill in arcade mode."
"Module: ArcadeMode"
"MandatoryArg: <origin>: Location of kill"
"MandatoryArg: <damage_type>: explosive, pistol, rifle, or melee"
"MandatoryArg: <amount>: Amount of points rewarded"
"Example: arcadeMode_kill( self.origin, "explosive", 500 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
arcadeMode_kill( origin, damage_type, amount )
{
	if ( GetDvar( "arcademode" ) != "1" )
		return;
	thread maps\_arcademode::arcadeMode_add_points( origin, true, damage_type, amount );
}

/*
=============
///ScriptDocBegin
"Name: arcadeMode_damage( <origin> , <damage_type> , <amount> )"
"Summary: Rewards points for a kill in arcade mode."
"Module: ArcadeMode"
"MandatoryArg: <origin>: Location of kill"
"MandatoryArg: <damage_type>: explosive, pistol, rifle, or melee"
"MandatoryArg: <amount>: Amount of points rewarded"
"Example: arcadeMode_damage( self.origin, "explosive", 500 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
arcadeMode_damage( origin, damage_type, amount )
{
	if ( GetDvar( "arcademode" ) != "1" )
		return;
	thread maps\_arcademode::arcadeMode_add_points( origin, false, damage_type, amount );
}

/*
=============
///ScriptDocBegin
"Name: arcademode_checkpoint( <minutes_remaining> )"
"Summary: Gives a checkpoint in Arcademode and sets a new remaining time."
"Module: ArcadeMode"
"MandatoryArg: <minutes_remaining>: The time the player has until they fail or reach the next checkpoint or win "
"Example: arcademode_checkpoint( 3 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
arcademode_checkpoint( time_remaining, unique_id )
{
	if ( 1 )
		return;
	if ( GetDvar( "arcademode" ) != "1" )
		return;

	id = maps\_arcadeMode::arcademode_checkpoint_getid( unique_id );
	if ( !isdefined( id ) )
	{
		id = level.arcadeMode_checkpoint_dvars.size;
		// add the unique_id to the list if it doesn't exist yet
		level.arcadeMode_checkpoint_dvars[ level.arcadeMode_checkpoint_dvars.size ] = unique_id;
		AssertEx( level.arcadeMode_checkpoint_dvars.size <= level.arcadeMode_checkpoint_max, "Exceeded max number of arcademode checkpoints." );
	}

	// make sure we don't do the same checkpoint twice
	if ( GetDvar( "arcademode_checkpoint_" + id ) == "1" )
		return;

	SetDvar( "arcademode_checkpoint_" + id, "1" );

	if ( GetDvar( "arcademode_full" ) == "1" )
	{
		if ( level.gameskill == 2 )
			time_remaining *= 2.0;
		if ( level.gameskill == 3 )
			time_remaining *= 2.5;
	}

	// save the remaining time to add it back on at the end
	// then set the remaining time to the new time_remaining
	remaining_time = GetDvarInt( "arcademode_time" );
	stored_time = GetDvarInt( "arcademode_stored_time" );
	stored_time += remaining_time;
	SetDvar( "arcademode_stored_time", stored_time );
	SetDvar( "arcademode_time", time_remaining * 60 );

	start_offset = 800;
	movetime = 0.8;

	level.player thread play_sound_in_space( "arcademode_checkpoint", level.player GetEye() );

	thread maps\_arcademode::draw_checkpoint( start_offset, movetime, 1 );
	thread maps\_arcademode::draw_checkpoint( start_offset, movetime, -1 );
}


/*
=============
///ScriptDocBegin
"Name: arcadeMode()"
"Summary: returns true if arcade mode is on"
"Module: Utility"
"CallOn: Level"
"Example: if(arcademode){ dothestuf(); }"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
arcadeMode()
{
	return GetDvar( "arcademode" ) == "1";
}

/*
=============
///ScriptDocBegin
"Name: arcadeMode_stop_timer()"
"Summary: Stops the countdown timer in arcademode, for missions that have non-competitive ending sequences."
"Module: ArcadeMode"
"Example: arcadeMode_stop_timer();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
arcadeMode_stop_timer()
{
 	if ( !isdefined( level.arcadeMode_hud_timer ) )
 		return;

 	level notify( "arcadeMode_remove_timer" );
 	level.arcademode_stoptime = GetTime();

	level.arcadeMode_hud_timer Destroy();
	level.arcadeMode_hud_timer = undefined;
}

/*
=============
///ScriptDocBegin
"Name: MusicPlayWrapper( <song> , <timescale> , <overrideCheat> )"
"Summary: wrapper for music play for arcade mode stuff."
"Module: Code Wrappers"
"CallOn: Level"
"MandatoryArg: <song>: song to play"
"OptionalArg: <timescale>: timescale param to pass to musicplay"
"OptionalArg: <overrideCheat>: overrideCheat param to pass to musicplay"
"Example: MusicPlayWrapper( "credits_bog_victory" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

MusicPlayWrapper( song, timescale, overrideCheat )
{
	level.last_song = song;
	if ( !arcadeMode() || !flag( "arcadeMode_multiplier_maxed" ) )
	{
		if ( !isdefined( timescale ) )
			timescale = true;
		if ( !isdefined( overrideCheat ) )
			overrideCheat = false;

		MusicStop( 0 );
		// backwards compatible (though, timescale is no longer used: timescale for music is set by channel)
		// MusicPlay( <music>, <fadeTime>, <volumeScale>, <isExclusive>, <overrideCheat> )
		MusicPlay( song, 0, 1.0, true, overrideCheat );
	}
}

/*
=============
///ScriptDocBegin
"Name: music_loop( <name> , <time>, <fade_time> )"
"Summary: stops any previously playing music, and plays a track of music that loops."
"Module: Utility"
"CallOn: "
"MandatoryArg: <name>: the name of the music track"
"MandatoryArg: <time>: The amount of time to wait between loops. If > 10, will be ignored."
"OptionalArg: <fade_time>: optional fade time IN SECONDS to fade out any previously playing music...if undefined, previously playing music will end immediately"
"Example: music_loop( 'ICBM_tension_music', 112 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
music_loop( name, time, fade_time, timescale, overrideCheat )
{
	thread music_loop_internal( name, time, fade_time, timescale, overrideCheat );
}

/*
=============
///ScriptDocBegin
"Name: music_loop_stealth( <name> , <length>, <fade_time> )"
"Summary: stops any previously playing music, and plays a track of music that loops.  The music will automatically pause on stealth_spotted and resume on stealth_hidden."
"Module: Utility"
"CallOn: "
"MandatoryArg: <name>: the name of the music track"
"MandatoryArg: <length>: the length of the music track IN SECONDS (if short, the song will end and loop early )"
"OptionalArg: <fade_time>: optional fade time IN SECONDS to fade out any previously playing music...if undefined, previously playing music will end immediately"
"Example: music_loop_stealth( 'ICBM_tension_music', 112 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
music_loop_stealth( name, length, fade_time, timescale, overrideCheat )
{
	thread music_loop_internal( name, length, fade_time, timescale, overrideCheat, true );
}

/*
=============
///ScriptDocBegin
"Name: music_play( <name> , <fade_time> )"
"Summary: stops any previously playing music, and plays a new piece of music."
"Module: Utility"
"CallOn: "
"MandatoryArg: <name>: the name of the music track"
"OptionalArg: <fade_time>: optional fade time IN SECONDS to fade out any previously playing music...if undefined, previously playing music will end immediately"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
music_play( name, fade_time, timescale, overrideCheat )
{
	if ( IsDefined( fade_time ) && fade_time > 0 )
	{
		thread music_play_internal_stop_with_fade_then_call( name, fade_time, timescale, overrideCheat );
		return;
	}
	music_stop();

	MusicPlayWrapper( name, timescale, overrideCheat );
}

/*
// Wraps the old "AmbientPlay" function in the new paradigm... don't uncomment until code hook is removed from code
AmbientPlay(alias, fade_, timescale_)
{
	assert(IsDefined(alias));
	sam = maps\_audio_stream_manager::SMx_get_ambience_manager();
	
	// make sure all the slots are stopped before moving on.
	// this function causes a syncronous fade out for the lower-weighted slot (if any is playing)
	maps\_audio_stream_manager::SMx_stop_all_slots(sam, fade_);
	maps\_audio_stream_manager::SMx_play_on_available_slot(sam, alias, fade_, undefined, undefined, timescale_);	
}

AmbientStop(fade_)
{
	maps\_audio_stream_manager::SM_stop_ambience(fade_);
}

// Wraps the old "MusicPlay" function in the new paradigm... don't uncomment until code hook is removed from code
MusicPlay(alias, timescale_, fade_)
{
	assert(IsDefined(alias));
	
	smm = maps\_audio_stream_manager::SMx_get_music_manager();
			
	// make sure all the slots are stopped before moving on.
	// this function causes a syncronous fade out for the lower-weighted slot (if any is playing)
	maps\_audio_stream_manager::SMx_stop_all_slots(smm, undefined, fade_);	
	maps\_audio_stream_manager::SMx_play_on_available_slot(smm, alias, fade_, undefined, undefined, timescale_);
}

MusicStop(fade_)
{
	crossfade = false;
	maps\_audio_stream_manager::SM_stop_music(fade_); // stop the music syncronously
}
*/


/*
=============
///ScriptDocBegin
"Name: music_stop( <fade_time> )"
"Summary: stops any currently playing music, including loops"
"Module: Entity"
"CallOn: An entity"
"OptionalArg: <fade_time>: the time IN SECONDS to stop the currently playing music"
"Example: music_stop( 3 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
music_stop( fade_time )
{
	if ( !isdefined( fade_time ) || fade_time <= 0 )
		MusicStop();
	else
		MusicStop( fade_time );
	level notify( "stop_music" );
}

/*
=============
///ScriptDocBegin
"Name: player_is_near_live_grenade()"
"Summary: Returns true if player(s) is near a live grenade"
"Module: Utility"
"CallOn: Level"
"Example: if( player_is_near_live_grenade() )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_is_near_live_grenade()
{
	grenades = GetEntArray( "grenade", "classname" );
	for ( i = 0; i < grenades.size; i++ )
	{
		grenade = grenades[ i ];
		if ( grenade.model == "weapon_claymore" )
			continue;

		for ( playerIndex = 0; playerIndex < level.players.size; playerIndex++ )
		{
			player = level.players[ playerIndex ];
			if ( DistanceSquared( grenade.origin, player.origin ) < ( 275 * 275 ) )// grenade radius is 256
			{
				/# maps\_autosave::AutoSavePrint( "autosave failed: live grenade too close to player" ); #/
				return true;
			}
		}
	}
	return false;
}

/*
=============
///ScriptDocBegin
"Name: player_died_recently()"
"Summary: check the player_died_recently dvar"
"Module: Utility"
"CallOn: Level"
"Example: if(player_died_recently())"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_died_recently()
{
	return GetDvarInt( "player_died_recently", "0" ) > 0;
}

 /*
 =============
///ScriptDocBegin
"Name: all_players_istouching( eVolume )"
"Summary: Returns true/false if all coop players are currently touching eVolume. Does IsTouching() code function on all coop players (or just single player if no coop enabled)."
"Module: Player"
"MandatoryArg: <eVolume>: The volume you are checking to see that the players are touching."
"Example: while ( coop_players_touching( eRoomVolume ) )....<do something>"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
all_players_istouching( eVolume )
{
	AssertEx( IsDefined( eVolume ), "eVolume parameter not defined" );
	foreach ( player in level.players )
	{
		if ( !player IsTouching( eVolume ) )
			return false;
	}
	return true;
}

 /*
 =============
///ScriptDocBegin
"Name: any_players_istouching( eVolume )"
"Summary: Returns true/false if any coop players are currently touching eVolume. Does IsTouching() code function on all coop players (or just single player if no coop enabled)."
"Module: Player"
"MandatoryArg: <eVolume>: The volume you are checking to see that the players are touching."
"Example: while ( coop_players_touching( eRoomVolume ) )....<do something>"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
any_players_istouching( eVolume )
{
	AssertEx( IsDefined( eVolume ), "eVolume parameter not defined" );
	foreach ( player in level.players )
	{
		if ( player IsTouching( eVolume ) )
			return true;
	}
	return false;
}

 /*
 =============
///ScriptDocBegin
"Name: get_ent_closest_to_flag_trig( sFlagName, aEnts )"
"Summary: Returns the entity that is closest to a given flag trigger"
"Module: Distance"
"MandatoryArg: <sFlagName>: The script_flag value of the trigger in question."
"MandatoryArg: <aEnts>: Array of entities you want to check."
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

get_ent_closest_to_flag_trig( sFlagName, aEnts )
{
	AssertEx( IsDefined( sFlagName ), "You need to specify the name of the script_flag key for this function" );
	AssertEx( IsDefined( aEnts ), "You need to specify the array of entities you want to check" );
	AssertEx( aEnts.size > 0, "The array passed is empty" );
	if ( aEnts.size == 1 )
		return aEnts[ 0 ];

	flag_trig = undefined;
	eEnt = undefined;
	trigs = GetEntArray( "trigger_multiple", "classname" );
	for ( i = 0; i < trigs.size; i++ )
	{
		if ( ( IsDefined( trigs[ i ].script_flag ) ) && ( trigs[ i ].script_flag == sFlagName ) )
		{
			flag_trig = trigs[ i ];
			break;
		}
	}
	AssertEx( IsDefined( flag_trig ), "Cannot find a flag trigger with the script_flag name of :" + sFlagName );
	eEnt = getClosest( flag_trig.origin, aEnts );
	AssertEx( IsDefined( eEnt ), "Could not determine which entity was closest to flag trigger " + sFlagName );
	return eEnt;
}

/*
=============
///ScriptDocBegin
"Name: getDifficulty( <getDifficulty> )"
"Summary: Returns level difficulty in "easy","medium", "hard", or "fu" format."
"Module: Utility"
"CallOn: Level"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
getDifficulty()
{
	Assert( IsDefined( level.gameskill ) );
	if ( level.gameskill < 1 )
		return "easy";
	if ( level.gameskill < 2 )
		return "medium";
	if ( level.gameskill < 3 )
		return "hard";
	return "fu";
}

 /*
 =============
///ScriptDocBegin
"Name: hide_players( <qBool> )"
"Summary: Hides the player models."
"Module: Utility"
"MandatoryArg: <qBool>: True/false to hide/unhide the players."
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */

hide_players( qBool )
{
	for ( i = 0; i < level.players.size; i++ )
	{
		if ( qBool == true )
			level.players[ i ] Hide();
		else
			level.players[ i ] Show();
	}
}

/*
=============
///ScriptDocBegin
"Name: SetModelFunc( <modelFunc> )"
"Summary: Runs the model setting function on a player, to set a player's 3rd person model."
"Module: Utility"
"CallOn: A player"
"MandatoryArg: <modelFunc>: The function to run on the player "
"Example: self SetModelFunc( ::so_body_ranger_player1 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
SetModelFunc( modelFunc, starts_off )
{
	if ( !isdefined( starts_off ) )
		starts_off = false;
	thread maps\_loadout::UpdateModel( modelFunc );
}

/*
 =============
///ScriptDocBegin
"Name: getAveragePlayerOrigin()"
"Summary: Returns the average player origin of level.players array."
"Module: Utility"
"CallOn: "
"Example: org = getAveragePlayerOrigin();"
"SPMP: singleplayer"
///ScriptDocEnd
 =============
 */
getAveragePlayerOrigin()
{
	averageOrigin_x = 0;
	averageOrigin_y = 0;
	averageOrigin_z = 0;
	foreach ( player in level.players )
	{
		averageOrigin_x += player.origin[ 0 ];
		averageOrigin_y += player.origin[ 1 ];
		averageOrigin_z += player.origin[ 2 ];
	}
	averageOrigin_x = averageOrigin_x / level.players.size;
	averageOrigin_y = averageOrigin_y / level.players.size;
	averageOrigin_z = averageOrigin_z / level.players.size;
	return( averageOrigin_x, averageOrigin_y, averageOrigin_z );
}

/*
=============
///ScriptDocBegin
"Name: get_average_origin( <array> )"
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
get_average_origin( array )
{
	origin = ( 0, 0, 0 );
	foreach ( member in array )
		origin += member.origin;


	return origin *  ( 1.0 / array.size ) ;
}



generic_damage_think()
{
	self.damage_functions = [];
	for ( ;; )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, type, modelName, tagName );
		foreach ( func in self.damage_functions )
		{
			thread [[ func ]]( damage, attacker, direction_vec, point, type, modelName, tagName );
		}
	}
}


/*
=============
///ScriptDocBegin
"Name: add_damage_function( <func> )"
"Summary: Adds a damage function to an AI or Vehicle. It is called when the AI or Vehicle takes damage. The AI function must have all 7 of the required parameters."
"Module: Spawner"
"CallOn: An AI"
"MandatoryArg: <func > The function to be run when the AI takes damage. "
"Example: ai add_damage_function( ::got_hurt );"
"SPMP: singleplayer"
"NoteLine: thread [[ func ]]( damage, attacker, direction_vec, point, type, modelName, tagName );"
///ScriptDocEnd
=============
*/
add_damage_function( func )
{
	self.damage_functions[ self.damage_functions.size ] = func;
}

/*
=============
///ScriptDocBegin
"Name: remove_damage_function( <func> )"
"Summary: Removes a damage function that was added with add_damage_function."
"Module: Spawner"
"CallOn: An AI"
"MandatoryArg: <func > The function to be removed. "
"Example: ai remove_damage_function( ::got_hurt );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
remove_damage_function( damage_func )
{
	new_array = [];
	foreach ( func in self.damage_functions )
	{
		if ( func == damage_func )
			continue;
		new_array[ new_array.size ] = func;
	}
	self.damage_functions = new_array;
}


/*
=============
///ScriptDocBegin
"Name: giveXp( <type>, <value> )"
"Summary: Gives a player XP either by predefined <type> or customized <value>, single player XP gain feature must be enabled to use this."
"Module: Spawner"
"CallOn: A Player"
"MandatoryArg: <type> String name of type of XP given. Does not need to be an existing type, can be any label for the XP reward."
"OptionalArg: <value> Int value of XP given. If not defined, type's XP reward will be awarded. If type does not exist, default 'kill' type XP will be awarded."
"Example: level.player giveXp( "assist" ); level.player2 giveXp( "pwn", 10000 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
giveXp( type, value )
{
	self maps\_rank::updatePlayerScore( type, value );
}


/*
=============
///ScriptDocBegin
"Name: playLocalSoundWrapper( <soundalias> )"
"Summary: Calls playLocalSound on self. This function was made so it can be used in array_thread"
"Module: Player"
"CallOn: A Player"
"MandatoryArg: <soundalias> Soundalias to played."
"Example: level.player playLocalSoundWrapper( "mission_complete_sound" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
playLocalSoundWrapper( alias )
{
	Assert( IsDefined( alias ) );
	self PlayLocalSound( alias );
}


/*
=============
///ScriptDocBegin
"Name: enablePlayerWeapons( <bool> )"
"Summary: enables or disables weapons on single all players (singleplayer or coop)"
"Module: Player"
"MandatoryArg: <bool> True or false to enable or disable weapons"
"Example: enablePlayerWeapons( false );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enablePlayerWeapons( bool )
{
	AssertEx( IsDefined( bool ), "Need to pass either 'true' or 'false' to enable/disable weapons" );
	if ( level.players.size < 1 )
		return;
	foreach ( player in level.players )
	{
		if ( bool == true )
			player EnableWeapons();
		else
			player DisableWeapons();
	}
}

/*
=============
///ScriptDocBegin
"Name: teleport_players( aNodes )"
"Summary: Teleports coop players to an array of nodes"
"Module: Player"
"MandatoryArg: <aNodes> An array of exactly 2 nodes (to account for the possibility of a second player)"
"Example: teleport_players( aPlayerNodes, true );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
teleport_players( aNodes )
{
	//->not supporting coop in SP anymore
	//assertEx( aNodes.size == 2, "An array of exactly 2 nodes is required to teleport 2 coop players" );

	player1node = undefined;
	player2node = undefined;
	eNode = undefined;
	foreach ( node in aNodes )
	{
		if ( ( IsDefined( node.script_noteworthy ) ) && ( node.script_noteworthy == "player1" ) )
			player1node = node;
		else if ( ( IsDefined( node.script_noteworthy ) ) && ( node.script_noteworthy == "player2" ) )
			player2node = node;
		else
		{
			if ( !isdefined( player1node ) )
				player1node = node;
			if ( !isdefined( player2node ) )
				player2node = node;
		}
	}
	foreach ( player in level.players )
	{
		if ( player == level.player )
			eNode = player1node;
		else if ( player == level.player2 )
			eNode = player2node;
		player SetOrigin( eNode.origin );
		player SetPlayerAngles( eNode.angles );
	}
}

/*
=============
///ScriptDocBegin
"Name: teleport_player( <object> )"
"Summary: move level.player to the origin and angles of the specified object"
"Module: Player"
"CallOn: A Player"
"MandatoryArg: <param1>: "
"Example: 	teleport_player( getstruct("start_surprized_parachute_moment","script_noteworthy" ) );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

teleport_player( object )
{
	level.player SetOrigin( object.origin );
	if ( IsDefined( object.angles ) )
    	level.player SetPlayerAngles( object.angles );
}

/*
=============
///ScriptDocBegin
"Name: hide_player_model()"
"Summary: Hide the players model."
"Module: Utility"
"CallOn: A player"
"Example: level.players[0] hide_player_model(); "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
hide_player_model()
{

	if ( !is_coop() )
		return;

	self.is_hidden 	 = true;
	AssertEx( IsDefined( self.last_modelfunc ), "can't Hide player model on a player that hasn't been through maps\_loadout::UpdateModel()" );
	thread maps\_loadout::UpdateModel( undefined );
}

/*
=============
///ScriptDocBegin
"Name: show_player_model()"
"Summary: Show the players model."
"Module: Utility"
"CallOn: A player"
"Example: level.players[0] show_player_model(); "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

show_player_model()
{
	if ( !is_coop() )
		return;
	self.is_hidden 	 = false;
	AssertEx( IsDefined( self.last_modelfunc ), "can't Show player model on a player that hasn't been through maps\_loadout::UpdateModel()" );
	thread maps\_loadout::UpdateModel( self.last_modelfunc );
}



/*
=============
///ScriptDocBegin
"Name: translate_local()"
"Summary: Translates an entity in space"
"Module: Utility"
"CallOn: A spawnstruct"
"MandatoryArg: <.entity>: Member variable on spawnstruct that sets the entity that will be moved"
"OptionalArg: <.entities>: Member variable on spawnstruct that sets an array of entities to be moved"
"OptionalArg: <.forward>: Member variable on spawnstruct that determines how far forward the entity will move"
"OptionalArg: <.right>: Member variable on spawnstruct that determines how far right the entity will move"
"OptionalArg: <.up>: Member variable on spawnstruct that determines how far up the entity will move"
"OptionalArg: <.yaw>: Member variable on spawnstruct that determines how much to rotate the yaw"
"OptionalArg: <.pitch>: Member variable on spawnstruct that determines how much to rotate the pitch"
"OptionalArg: <.roll>: Member variable on spawnstruct that determines how much to rotate the roll"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
translate_local()
{
	entities = [];
	if ( IsDefined( self.entities ) )
		entities = self.entities;
	if ( IsDefined( self.entity ) )
	entities[ entities.size ] = self.entity;

	AssertEx( entities.size > 0, "Tried to do translate_local without any entities" );
	array_levelthread( entities, ::translate_local_on_ent );
}


/*
=============
///ScriptDocBegin
"Name: open_up_fov( <time> , <player_rig> , <tag> , <arcRight> , <arcLeft> , <arcTop> , <arcBottom> )"
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
open_up_fov( time, player_rig, tag, arcRight, arcLeft, arcTop, arcBottom )
{
	level.player endon( "stop_opening_fov" );
	wait( time );
	level.player PlayerLinkToDelta( player_rig, tag, 1, arcRight, arcLeft, arcTop, arcBottom, true );
}



/*
=============
///ScriptDocBegin
"Name: get_ai_touching_volume( sTeam, species )"
"Summary: Returns an array of all ai touching a specified info_volume"
"Module: Utility"
"CallOn: An info_volume"
"OptionalArg: <sTeam>: 'axis' or 'allies'. Left blank the function will return an array containing all ai of all teams."
"OptionalArg: <species>: 'human', 'dog', 'civilians'. Left blank the function will return an array containing all ai of all species."
"Example: aEnemies = eRoomVolume get_ai_touching_volume( team )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_ai_touching_volume( sTeam, species, bGetDrones )
{
	if ( !isdefined( sTeam ) )
		sTeam = "all";

	if ( !isdefined( species ) )
		species = "all";

	aTeam = GetAISpeciesArray( sTeam, species );

	aGuysTouchingVolume = [];
	foreach ( guy in aTeam )
	{
		AssertEx( IsAlive( guy ), "Got ai array yet got a dead guy!" );
		if ( guy IsTouching( self ) )
			aGuysTouchingVolume[ aGuysTouchingVolume.size ] = guy;
	}

	return aGuysTouchingVolume;
}

/*
=============
///ScriptDocBegin
"Name: get_drones_touching_volume( sTeam )"
"Summary: Returns an array of all ai touching a specified info_volume"
"Module: Utility"
"CallOn: An info_volume"
"OptionalArg: <sTeam>: 'axis', 'allies' or 'neutral. Left blank the function will return an array containing all ai of all teams."
"Example: aDrones = eRoomVolume get_drones_touching_volume( "axis" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_drones_touching_volume( sTeam )
{
	if ( !isdefined( sTeam ) )
		sTeam = "all";

	aDrones = [];
	if ( sTeam == "all" )
	{
		aDrones = array_merge( level.drones[ "allies" ].array, level.drones[ "axis" ].array );
		aDrones = array_merge( aDrones, level.drones[ "neutral" ].array );
	}
	else
		aDrones = level.drones[ sTeam ].array;

	aDronesToReturn = [];
	foreach ( drone in aDrones )
	{
		if ( !isdefined( drone ) )
			continue;
		if ( drone IsTouching( self ) )
			aDronesToReturn[ aDronesToReturn.size ] = drone;
	}
	return aDronesToReturn;
}


/*
=============
///ScriptDocBegin
"Name: get_drones_with_targetname( sTargetname )"
"Summary: Returns an array of all live drones with the specified targetname"
"Module: Utility"
"MandatoryArg: <"MandatoryArg>: Targetname of the drones you want."
"Example: aDrones = get_drones_with_targetname( bunker_drones )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_drones_with_targetname( sTargetname )
{
	aDrones = array_merge( level.drones[ "allies" ].array, level.drones[ "axis" ].array );
	aDrones = array_merge( aDrones, level.drones[ "neutral" ].array );
	aDronesToReturn = [];
	foreach ( drone in aDrones )
	{
		if ( !isdefined( drone ) )
			continue;
		if ( ( IsDefined( drone.targetname ) ) && ( drone.targetname == sTargetname ) )
			aDronesToReturn[ aDronesToReturn.size ] = drone;
	}
	return aDronesToReturn;
}

/*
=============
///ScriptDocBegin
"Name: get_other_player( <player> )"
"Summary: Gets the other player in Coop."
"Module: Utility"
"MandatoryArg: <player>: A player. The function will return the other player in coop"
"Example: other_player = get_other_player( player );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_other_player( player )
{
	Assert( is_coop() );
	Assert( isdefined( player ) && isplayer( player ) );

	foreach ( other_player in level.players )
	{
		if ( player == other_player )
			continue;
		return other_player;
	}

	AssertMsg( "get_other_player() tried to get other player but there is no other player." );
}

/*
=============
///ScriptDocBegin
"Name: is_other_player_downed( <player> )"
"Summary: Checks if other player in downed in Coop."
"Module: Utility"
"MandatoryArg: <player>: A player. The function will check if the other player in downed in coop"
"Example: if ( is_other_player_downed( player ); )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_other_player_downed( player )
{
	Assert( is_coop() );
	Assert( isdefined( player ) && isplayer( player ) );

	other_player = get_other_player( player );
	Assert( IsDefined( other_player ) );

	return is_player_down( other_player );
}

/*
=============
///ScriptDocBegin
"Name: set_count( <count> )"
"Summary: Set the count of a spawner"
"Module: Utility"
"CallOn: A spawner"
"MandatoryArg: <Count>: The count to set to"
"Example: spawner set_count( 3 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_count( count )
{
	/#
	AssertEx( IsDefined( self ), "Spawner wasn't defined!" );
	AssertEx( !isalive( self ), "Spawner was alive!" );
	#/
	self.count = count;
}/*
=============
///ScriptDocBegin
"Name: follow_path( <node>, <require_player_dist>, <arrived_at_node_func> )"
"Summary: Set's the AI on a path of nodes, script_structs, or script_origins.
Internally uses maps\_spawner::go_to_node which has the following attributes:
- if the node has .script_requires_player set, then the AI will stop at that node until the player catches up.
- if the node has .script_delay set, then the AI will stop at that node for the amount of delay"
- the function will return once all nodes are traversed, and will notify self 'path_end_reached'.
- follow_path stops maps\_spawner::go_to_node from exploding the AI's goal_radius after the last node is reached."
"Module: Utility"
"CallOn: AI"
"MandatoryArg: <node>: a node, script_struct, or script_origin that starts the path"
"OptionalArg: <require_player_dist>: The distance the player must be to the AI before the AI will move on from a node with .script_requires_player set, defaults to 300."
"OptionalArg: <arrived_at_node_func>: Optional function to run every time the AI reaches his goal."
"Example: other_player = get_other_player( player );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
follow_path( node, require_player_dist, arrived_at_node_func )
{
	self notify( "_utility::follow_path" );
	self endon( "_utility::follow_path" );
	self endon( "death" );

	goal_type = undefined;
	//only nodes and structs dont have classnames - ents do
	if ( !isdefined( node.classname ) )
	{
		//only structs don't have types, nodes do
		if ( !isdefined( node.type ) )
			goal_type = "struct";
		else
			goal_type = "node";
	}
	else
		goal_type = "entity";

	if ( !isdefined( require_player_dist ) )
		require_player_dist = 300;

	//set this so the radius doesn't explode.
	oldforcegoal = self.script_forcegoal;
	self.script_forcegoal = 1;

	self maps\_spawner::go_to_node( node, goal_type, arrived_at_node_func, require_player_dist );

	self.script_forcegoal = oldforcegoal;
}

/*
=============
///ScriptDocBegin
"Name: enable_dynamic_run_speed( <pushdist> , <sprintdist> , <stopdist> , <jogdist> , <group> , <dontChangeMovePlaybackRate> )"
"Summary: Turns on dynamic speed system for an AI, where the AI will run faster or slower based on average position of players.
make sure to call maps\_dynamic_run_speed::main(); after maps\_load::main(). maps\_dynamic_run_speed::main() takes an optional parameter
which is an array of dialogue lines the for the AI to say when they are stopped and want the player to catch up"
"Module: _dynamic_run_speed.gsc"
"CallOn: AI"
"OptionalArg: <pushdist>: The max distance from the player to the AI that the AI will go from a jog/walk to a run, at twice this distance the ai will stop. DEFAULTS to 250."
"OptionalArg: <sprintdist>: The min distance from the player to the AI where the AI will start sprinting. DEFAULTS to 125."
"Example: level.price enable_dynamic_run_speed();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_dynamic_run_speed( pushdist, sprintdist, stopdist, jogdist, group, dontChangeMovePlaybackRate )
{
	AssertEx( IsDefined( level.scr_anim[ "generic" ][ "DRS_sprint" ] ), " - -- -- -- -- -- -- add this line: 'maps\_dynamic_run_speed::main();' AFTER maps\\\_load::main(); -- -- -- -- -- -- - " );
	if ( !isdefined( pushdist ) )
		pushdist = 250;

	if ( !isdefined( sprintdist ) )
		sprintdist = 100;

	if ( !isdefined( stopdist ) )
		stopdist = pushdist * 2;

	if ( !isdefined( jogdist ) )
		jogdist = pushdist * 1.25;
	if ( !isdefined( dontChangeMovePlaybackRate ) )
		dontChangeMovePlaybackRate = false;

	self.dontChangeMovePlaybackRate = dontChangeMovePlaybackRate;

	self thread dynamic_run_speed_proc( pushdist, sprintdist, stopdist, jogdist, group );
}

/*
=============
///ScriptDocBegin
"Name: disable_dynamic_run_speed()"
"Summary: Stops Dynamic run speed logic on an AI."
"Module: _dynamic_run_speed.gsc"
"CallOn: AI"
"OptionalArg: <pushdist>: The max distance from the player to the AI that the AI will go from a jog/walk to a run, at twice this distance the ai will stop. DEFAULTS to 250."
"OptionalArg: <sprintdist>: The min distance from the player to the AI where the AI will start sprinting. DEFAULTS to 125."
"Example: level.price disable_dynamic_run_speed();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_dynamic_run_speed()
{
	self notify( "stop_dynamic_run_speed" );
}

/*
=============
///ScriptDocBegin
"Name: player_seek_enable()"
"Summary: Makes an enemy AI seek out the closest player."
"Module: AI"
"CallOn: AI"
"Example: enemy thread player_seek_enable();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_seek_enable()
{
	self endon( "death" );
	self endon( "stop_player_seek" );
	g_radius = 1200;
	if ( self has_shotgun() )
		g_radius = 250;

	newGoalRadius = Distance( self.origin, level.player.origin );
	for ( ;; )
	{
		wait 2;
		self.goalradius = newGoalRadius;
		player = get_closest_player( self.origin );
		self SetGoalEntity( player );
		newGoalRadius -= 175;
		if ( newGoalRadius < g_radius )
		{
			newGoalRadius = g_radius;
			return;
		}
	}
}

/*
=============
///ScriptDocBegin
"Name: player_seek_disable()"
"Summary: Makes an enemy AI stop seeking out the closest player. Disables behavior caused by funtion player_seek_enable()"
"Module: AI"
"CallOn: AI"
"Example: enemy thread player_seek_disable();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_seek_disable()
{
	self notify( "stop_player_seek" );
}

/*
=============
///ScriptDocBegin
"Name: waittill_entity_in_range_or_timeout( <entity>, <range>, <timeout> )"
"Summary: waits until a given entity is within range of the calling entity or timeout time passes"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <entity>: entity whose origin is checked to see if it is within range of the calling entity "
"OptionalArg: <range>: distance in units to check"
"OptionalArg: <timeout>: time in seconds to wait defaults to 5"
"Example: level.player waittill_entity_in_range_or_timeout( level.enemyHeli, 2048, 10 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waittill_entity_in_range_or_timeout( entity, range, timeout )
{
	self endon( "death" );
	entity endon( "death" );
	if ( !isdefined( timeout ) )
		timeout = 5;
	timeout_time = GetTime() + ( timeout * 1000 );
	while ( IsDefined( entity ) )
	{
		if ( Distance( entity.origin, self.origin ) <= range )
			break;
		if ( GetTime() > timeout_time )
			break;
		wait .1;
	}
}

/*
=============
///ScriptDocBegin
"Name: waittill_entity_in_range( <entity>, <range> )"
"Summary: waits until a given entity is within range of the calling entity"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <entity>: entity whose origin is checked to see if it is within range of the calling entity "
"OptionalArg: <range>: distance in units to check"
"Example: level.player waittill_entity_in_range( level.enemyHeli, 2048 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waittill_entity_in_range( entity, range )
{
	self endon( "death" );
	entity endon( "death" );
	while ( IsDefined( entity ) )
	{
		if ( Distance( entity.origin, self.origin ) <= range )
			break;
		wait .1;
	}
}
/*
=============
///ScriptDocBegin
"Name: waittill_entity_out_of_range( <entity>, <range> )"
"Summary: waits until a given entity is out of range of the calling entity"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <entity>: entity whose origin is checked"
"OptionalArg: <range>: distance in units to check"
"Example: level.player waittill_entity_out_of_range( level.enemyHeli, 2048 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waittill_entity_out_of_range( entity, range )
{
	self endon( "death" );
	entity endon( "death" );
	while ( IsDefined( entity ) )
	{
		if ( Distance( entity.origin, self.origin ) > range )
			break;
		wait .1;
	}
}

/*
=============
///ScriptDocBegin
"Name: has_shotgun()"
"Summary: returns true/false if AI has a shotgun"
"Module: AI"
"CallOn: AI"
"Example: self has_shotgun()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
has_shotgun()
{
	self endon( "death" );
	if ( !isdefined( self.weapon ) )
		return false;
	if ( self.weapon == "winchester1200" || self.weapon == "m1014" || self.weapon == "striker" || self.weapon == "ranger" || self.weapon == "aa12" )
		return true;
	else
		return false;
}

/*
=============
///ScriptDocBegin
"Name: isPrimaryWeapon( weaponName )"
"Summary: Returns if the weapon is a primary weapon."
"Example: isPrimaryWeapon( weaponName )"
///ScriptDocEnd
=============
*/

isPrimaryWeapon( weapName )
{
	if ( weapName == "none" )
		return false;
		
	if ( weaponInventoryType( weapName ) != "primary" )
		return false;

	switch ( weaponClass( weapName ) )
	{
		case "rifle":
		case "smg":
		case "mg":
		case "spread":
		case "pistol":
		case "rocketlauncher":
		case "sniper":
			return true;

		default:
			return false;
	}	
}

/*
=============
///ScriptDocBegin
"Name: player_has_thermal()"
"Summary: returns true/false if player has a weapon with a thermal scope"
"Module: Player"
"CallOn: Player"
"Example: if ( level.player player_has_thermal() )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_has_thermal()
{
	weapons = self GetWeaponsListAll();
	if ( !isdefined( weapons ) )
		return false;
	foreach ( weapon in weapons )
	{
		if ( IsSubStr( weapon, "thermal" ) )
			return true;
	}
	return false;
}

/*
=============
///ScriptDocBegin
"Name: waittill_true_goal( <origin> , <radius> )"
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
waittill_true_goal( origin, radius )
{
	self endon( "death" );

	if ( !isdefined( radius ) )
		radius = self.goalradius;

	while ( 1 )
	{
		self waittill( "goal" );
		if ( Distance( self.origin, origin ) < radius + 10 )// give a little leeway
			break;
	}
}

/*
=============
///ScriptDocBegin
"Name: player_speed_percent( <percent> , <time> )"
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
player_speed_percent( percent, time )
{
	currspeed = Int( GetDvar( "g_speed" ) );
	if ( !isdefined( level.player.g_speed ) )
		level.player.g_speed = currspeed;

	goalspeed = Int( level.player.g_speed * percent * .01 );

	level.player player_speed_set( goalspeed, time );
}

/*
=============
///ScriptDocBegin
"Name: blend_movespeedscale_percent( <percent> , <time> )"
"Summary: blends the player's speed percentage using setMoveSpeedScale over time"
"Module: player"
"CallOn: player"
"MandatoryArg: <percent>: percentage > 0 to scale to"
"OptionalArg: <time>: time in seconds to lerp over if none - set speed instantly"
"Example: level.player blend_movespeedscale_percent( 1.2, 3 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blend_movespeedscale_percent( percent, time )
{
	player = self;
	if ( !isplayer( player ) )
		player = level.player;

	if ( !isdefined( player.movespeedscale ) )
		player.movespeedscale = 1.0;

	goalscale = percent * .01;

	player blend_movespeedscale( goalscale, time );
}

/*
=============
///ScriptDocBegin
"Name: player_speed_set( <speed> , <time> )"
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
player_speed_set( speed, time )
{
	currspeed = Int( GetDvar( "g_speed" ) );
	if ( !isdefined( level.player.g_speed ) )
		level.player.g_speed = currspeed;

	get_func = ::g_speed_get_func;
	set_func = ::g_speed_set_func;
	level.player thread player_speed_proc( speed, time, get_func, set_func, "player_speed_set" );
}

/*
=============
///ScriptDocBegin
"Name: blend_movespeedscale( <scale> , <time> )"
"Summary: blends the player's speed scaler using setMoveSpeedScale over time"
"Module: player"
"CallOn: player"
"MandatoryArg: <scale>: scale > 0 to scale to"
"OptionalArg: <time>: time in seconds to lerp over if none - set speed instantly"
"Example: level.player blend_movespeedscale( 1.2, 3 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blend_movespeedscale( scale, time )
{
	player = self;
	if ( !isplayer( player ) )
		player = level.player;

	if ( !isdefined( player.movespeedscale ) )
		player.movespeedscale = 1.0;

	get_func = ::movespeed_get_func;
	set_func = ::movespeed_set_func;
	player thread player_speed_proc( scale, time, get_func, set_func, "blend_movespeedscale" );
}

player_speed_proc( speed, time, get_func, set_func, ender )
{
	self notify( ender );
	self endon( ender );

	currspeed = [[ get_func ]]();
	goalspeed = speed;

	if ( IsDefined( time ) )
	{
		range = goalspeed - currspeed;
		interval = .05;
		numcycles = time / interval;
		fraction = range / numcycles;

		while ( abs( goalspeed - currspeed ) > abs( fraction * 1.1 ) )
		{
			currspeed += fraction;
			[[ set_func ]]( currspeed );
			wait interval;
		}
	}

	[[ set_func ]]( goalspeed );
}

/*
=============
///ScriptDocBegin
"Name: player_speed_default( <time> )"
"Summary: blends the level.player's speed back to default using the dvar g_speed over time"
"Module: player"
"CallOn: "
"OptionalArg: <time>: the time to blend over, if none - then set speed instantly"
"Example: player_speed_default( 2 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_speed_default( time )
{
	if ( !isdefined( level.player.g_speed ) )
		return;

	level.player player_speed_set( level.player.g_speed, time );

	waittillframeend;
	level.player.g_speed = undefined;
}

/*
=============
///ScriptDocBegin
"Name: blend_movespeedscale_default( <time> )"
"Summary: blends the player's speed scale back to default using setmovespeedscale over time"
"Module: player"
"CallOn: player"
"OptionalArg: <time>: the time to blend over, if none - then set speed instantly"
"Example: level.player blend_movespeedscale_default( 2 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blend_movespeedscale_default( time )
{
	player = self;
	if ( !isplayer( player ) )
		player = level.player;

	if ( !isdefined( player.movespeedscale ) )
		return;

	player blend_movespeedscale( 1.0, time );

	waittillframeend;
	player.movespeedscale = undefined;
}

/*
=============
///ScriptDocBegin
"Name: drop_to_ground( <pos> )"
"Summary: Return the ground point for this origin"
"Module: Utility"
"MandatoryArg: <pos>: The origin you want to find the ground point for"
"OptionalArg: <updist>: Optional height to drop the point from"
"OptionalArg: <downdist>: Optional height to drop the point to"
"Example: ground_org = drop_to_ground( origin );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
drop_to_ground( pos, updist, downdist )
{
	if ( !isdefined( updist ) )
		updist = 1500;
	if ( !isdefined( downdist ) )
		downdist = -12000;

	return PhysicsTrace( pos + ( 0, 0, updist ), pos + ( 0, 0, downdist ) );
}

/*
=============
///ScriptDocBegin
"Name: teleport_ent( <ent> )"
"Summary: Teleport self to an ent"
"Module: Utility"
"CallOn: An entity you want to teleport"
"MandatoryArg: <ent>: The entity to teleport to"
"Example: level.player teleport_ent( player_start_ent );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
teleport_ent( ent )
{
	if ( IsPlayer( self ) )
	{
		self SetOrigin( ent.origin );
		self SetPlayerAngles( ent.angles );
	}
	else
	{
		self ForceTeleport( ent.origin, ent.angles );
	}
}


/*
=============
///ScriptDocBegin
"Name: teleport_to_ent_tag( <ent> , <tag> )"
"Summary: teleport self to the tag location and angles of an entity"
"Module: Utility"
"CallOn: An entity you want to teleport"
"MandatoryArg: <ent>: ent to teleport to"
"MandatoryArg: <tag>: tag on ent to teleport to"
"Example: self teleport_to_ent_tag( ent, tag );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

teleport_to_ent_tag( ent, tag )
{
    position = ent GetTagOrigin( tag );
    angles = ent GetTagAngles( tag );
    self DontInterpolate();
    
 	if ( IsPlayer( self ) )
	{
		self SetOrigin( position );
		self SetPlayerAngles( angles );
	}
	else if( IsAI( self ) )
	{
		self ForceTeleport( position, angles );
	}   
	else
	{
	    self.origin = position;
	    self.angles = angles;
	}
}


/*
=============
///ScriptDocBegin
"Name: teleport_ai( <eNode> )"
"Summary: Force teleport of an AI to a given node and set its goalpos and goalnode to the node"
"Module: Utility"
"CallOn: An AI you want to teleport"
"MandatoryArg: <eNode>: The node to teleport to"
"Example: level.price teleport_ai( eNode );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
teleport_ai( eNode )
{
	AssertEx( IsAI( self ), "Function teleport_ai can only be called on an AI entity" );
	AssertEx( IsDefined( eNode ), "Need to pass a node entity to function teleport_ai" );
	self ForceTeleport( eNode.origin, eNode.angles );
	self SetGoalPos( self.origin );
	self SetGoalNode( eNode );
}



/*
=============
///ScriptDocBegin
"Name: move_all_fx( <vec> )"
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
move_all_fx( vec )
{
	foreach ( fx in level.createFXent )
	{
		fx.v[ "origin" ] += vec;
	}
}

/*
=============
///ScriptDocBegin
"Name: IsSliding( <IsSliding> )"
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
IsSliding()
{
	return IsDefined( self.slideModel );
}

/*
=============
///ScriptDocBegin
"Name: BeginSliding( <velocity> , <allowedAcceleration> , <dampening> )"
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
BeginSliding( velocity, allowedAcceleration, dampening )
{
	Assert( IsPlayer( self ) );
	player = self;


	player thread play_sound_on_entity( "foot_slide_plr_start" );
	player thread play_loop_sound_on_tag( "foot_slide_plr_loop" );

	override_link_method = IsDefined( level.custom_linkto_slide );

	if ( !isDefined( velocity ) )
		velocity = player GetVelocity() + ( 0, 0, -10 );
	if ( !isDefined( allowedAcceleration ) )
		allowedAcceleration = 10;
	if ( !isDefined( dampening ) )
		dampening = .035;

	Assert( !isDefined( player.slideModel ) );
	// in the future, slideModel will actually be a script_model of legs
	slideModel = Spawn( "script_origin", player.origin );
	slideModel.angles = player.angles;
	player.slideModel = slideModel;

	slideModel MoveSlide( ( 0, 0, 15 ), 15, velocity );

	if ( override_link_method )
	{
		player PlayerLinkToBlend( slideModel, undefined, 1 );
	}
	else
	{
		player PlayerLinkTo( slideModel );
	}

	player DisableWeapons();
	player AllowProne( false );
	player AllowCrouch( true );
	player AllowStand( false );

	player thread DoSlide( slideModel, allowedAcceleration, dampening );
}


/*
=============
///ScriptDocBegin
"Name: EndSliding( <EndSliding> )"
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
EndSliding()
{
	Assert( IsPlayer( self ) );
	player = self;

	Assert( IsDefined( player.slideModel ) );

	player notify( "stop sound" + "foot_slide_plr_loop" );
	player thread play_sound_on_entity( "foot_slide_plr_end" );
	player Unlink();
	player SetVelocity( player.slidemodel.slideVelocity );
 	player.slideModel Delete();
 	player EnableWeapons();
	player AllowProne( true );
	player AllowCrouch( true );
	player AllowStand( true );

	player notify( "stop_sliding" );
}


/*
=============
///ScriptDocBegin
"Name: spawn_vehicle( <spawn_vehicle> )"
"Summary: Self is a vehicle spawner"
"Module: Vehicle"
LevelOn: A vehicle spawner"
"Example: vehicle = spawner spawn_vehicle();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
spawn_vehicle()
{
	/#
	// dev comments so we can catch the local variable in the debugger
	vehicle = maps\_vehicle::vehicle_spawn( self );
	return vehicle;
	#/

	// to conform with the style that AI are spawned;
	return maps\_vehicle::vehicle_spawn( self );
}

/*
=============
///ScriptDocBegin
"Name: getEntWithFlag( <flag> )"
"Summary: Returns an entity that has the flag"
"Module: Utility"
"MandatoryArg: <flag>: The flag "
"Example: flagEnt = getEntWithFlag( "give_c4_obj" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
getEntWithFlag( flag )
{
	trigger_classes = maps\_load::get_load_trigger_classes();

	triggers = [];

	foreach ( class, _ in trigger_classes )
	{
		if ( !IsSubStr( class, "flag" ) )
			continue;
		other_triggers = GetEntArray( class, "classname" );
		triggers = array_combine( triggers, other_triggers );
	}

	trigger_funcs = maps\_load::get_load_trigger_funcs();

	foreach ( func, _ in trigger_funcs )
	{
		if ( !IsSubStr( func, "flag" ) )
			continue;
		other_triggers = GetEntArray( func, "targetname" );
		triggers = array_combine( triggers, other_triggers );
	}

	found_trigger = undefined;
	/#
	foreach ( trigger in triggers )
	{
		AssertEx( IsDefined( trigger.script_flag ), "Flag trigger at " + trigger.origin + " has no script_flag" );

		if ( trigger.script_flag == flag )
		{
			AssertEx( !isdefined( found_trigger ), "Did getEntWithFlag on flag " + flag + " but found multiple entities with that flag" );
			found_trigger = trigger;
		}
	}

	//AssertEx( IsDefined( found_trigger ), "Tried to find entity with flag " + flag + " but found none" );
	//if ( 1 ) return found_trigger;
	#/

	foreach ( trigger in triggers )
	{
		if ( trigger.script_flag == flag )
		{
			return trigger;
		}
	}
}

/*
=============
///ScriptDocBegin
"Name: getEntArrayWithFlag( <flag> )"
"Summary: Returns an array of entities that have the flag"
"Module: Utility"
"MandatoryArg: <flag>: The flag "
"Example: flagEnt = getEntArrayWithFlag( "give_c4_obj" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
getEntArrayWithFlag( flag )
{
	trigger_classes = maps\_load::get_load_trigger_classes();

	triggers = [];

	foreach ( class, _ in trigger_classes )
	{
		if ( !IsSubStr( class, "flag" ) )
			continue;
		other_triggers = GetEntArray( class, "classname" );
		triggers = array_combine( triggers, other_triggers );
	}

	trigger_funcs = maps\_load::get_load_trigger_funcs();

	foreach ( func, _ in trigger_funcs )
	{
		if ( !IsSubStr( func, "flag" ) )
			continue;
		other_triggers = GetEntArray( func, "targetname" );
		triggers = array_combine( triggers, other_triggers );
	}

	found_triggers = [];
	/#
	foreach ( trigger in triggers )
	{
		AssertEx( IsDefined( trigger.script_flag ), "Flag trigger at " + trigger.origin + " has no script_flag" );

		if ( trigger.script_flag == flag )
		{
			found_triggers[ found_triggers.size ] = trigger;
		}
	}

	AssertEx( found_triggers.size, "Tried to find entity with flag " + flag + " but found none" );
	if ( 1 ) return found_triggers;
	#/

	foreach ( trigger in triggers )
	{
		if ( trigger.script_flag == flag )
		{
			found_triggers[ found_triggers.size ] = trigger;
		}
	}
	return found_triggers;
}

/*
=============
///ScriptDocBegin
"Name: set_z( <vec> , <z> )"
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
set_z( vec, z )
{
	return( vec[ 0 ], vec[ 1 ], z );
}

/*
=============
///ScriptDocBegin
"Name: set_y( <vec> , <y> )"
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
set_y( vec, y )
{
	return( vec[ 0 ], y, vec[ 2 ] );
}

/*
=============
///ScriptDocBegin
"Name: set_x( <vec> , <x> )"
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
set_x( vec, x )
{
	return( x, vec[ 1 ], vec[ 2 ] );
}

/*
=============
///ScriptDocBegin
"Name: player_using_missile()"
"Summary: detect whether player has a missile weapon equipped as his current weapon (AT4, RPG, Stinger)"
"Module: Utility"
"CallOn: Player"
"Example: if ( player_using_missile() )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_using_missile()
{
	weapon = self GetCurrentWeapon();

	if ( !isdefined( weapon ) )
		return false;

	if ( IsSubStr( ToLower( weapon ), "rpg" ) )
		return true;

	if ( IsSubStr( ToLower( weapon ), "stinger" ) )
		return true;

	if ( IsSubStr( ToLower( weapon ), "at4" ) )
		return true;

	if ( IsSubStr( ToLower( weapon ), "javelin" ) )
		return true;

	return false;
}

/*
=============
///ScriptDocBegin
"Name: doingLongDeath( <longDeath> )"
"Summary: Returns if an AI is doing long death"
"Module: Utility"
"CallOn: An AI"
"Example: if ( guy longDeath() )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
doingLongDeath()
{
	Assert( IsAI( self ) );
	return IsDefined( self.a.doingLongDeath );
}

/*
=============
///ScriptDocBegin
"Name: get_rumble_ent( <rumble> )"
"Summary: Create an entity to do rumble on. Set .intensity to change the rumble intensity or use blend commands below."
"Module: Rumble"
"OptionalArg: <rumble>: The rumble to use, if not specified steady_rumble is used. "
"Example: ent = get_rumble_ent();"
"NoteLine: WARNING: The rumble you pass in must have a fade range of 1000, otherwise blending will be wrong. "
"NoteLine: don't forget to add PreCacheRumble( "steady_rumble" ) or whatever rumble you decide to use to your script. "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_rumble_ent( rumble )
{
	if ( is_coop() )
		PrintLn( "^3Warning! Using get_rumble_ent will cause the same rumbles to apply to all of the coop players!" );

	player = get_player_from_self();
	if ( !IsDefined( rumble ) )
		rumble = "steady_rumble";
	ent = Spawn( "script_origin", player GetEye() );
	ent.intensity = 1;
	ent thread update_rumble_intensity( player, rumble );
	return ent;
}

set_rumble_intensity( intensity )
{
	AssertEx( intensity >= 0 && intensity <= 1, "Intensity must be between 0 and 1" );
	self.intensity = intensity;
}

/*
=============
///ScriptDocBegin
"Name: rumble_ramp_on( <time> )"
"Summary: Ramp rumble to 1 on entity"
"Module: Rumble"
"CallOn: A rumble entity created with get_rumble_ent()"
"MandatoryArg: <time>: Time in seconds over which to ramp "
"Example: rumble_ent rumble_ramp_on( 2 )";"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
rumble_ramp_on( time )
{
	thread rumble_ramp_to( 1, time );
}

/*
=============
///ScriptDocBegin
"Name: rumble_ramp_off( <time> )"
"Summary: Ramp rumble to 0 on entity"
"Module: Rumble"
"CallOn: A rumble entity created with get_rumble_ent()"
"MandatoryArg: <time>: Time in seconds over which to ramp "
"Example: rumble_ent rumble_ramp_off( 2 )";"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
rumble_ramp_off( time )
{
	thread rumble_ramp_to( 0, time );
}

/*
=============
///ScriptDocBegin
"Name: rumble_ramp_to( <dest> , <time> )"
"Summary: Ramp rumble to dest on entity"
"Module: Rumble"
"CallOn: A rumble entity created with get_rumble_ent()"
"MandatoryArg: <dest>: Value to blend rumble to "
"MandatoryArg: <time>: Time in seconds over which to ramp "
"Example: rumble_ent rumble_ramp_to( 1, 2 )";"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
rumble_ramp_to( dest, time )
{
	self notify( "new_ramp" );
	self endon( "new_ramp" );
	self endon( "death" );

	frames = time * 20;
	dif = dest - self.intensity;
	slice = dif / frames;

	for ( i = 0; i < frames; i++ )
	{
		self.intensity += slice;
		wait( 0.05 );
	}
	self.intensity = dest;
}

/*
=============
///ScriptDocBegin
"Name: get_player_from_self()"
"Summary: Returns a player, and if self is a player then it returns that player."
"Module: Utility"
"Example: player = get_player_from_self();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_player_from_self()
{
	if ( IsDefined( self ) )
	{
		if ( !is_in_array( level.players, self ) )
			return level.player;
		else
			return self;
	}
	else
		return level.player;
}

/*
=============
///ScriptDocBegin
"Name: get_player_gameskill( <get_player_gameskill> )"
"Summary: Returns the gameskill for a player based on the dvar."
"Module: Entity"
"CallOn: A player"
"Example: player get_player_gameskill()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_player_gameskill()
{
	AssertEx( IsPlayer( self ), "get_player_gameskill() can only be called on a player." );
	return Int( self GetPlayerSetting( "gameskill" ) );
}

/*
=============
///ScriptDocBegin
"Name: glow( <model> )"
"Summary: Makes a model glow with"
"Module: Utility"
"CallOn: An entity that should glow"
"OptionalArg: <Model>: A glow model to use. If not specified then _obj is appended to the current model, which is how it should normally work anyway. "
"Example: keyboard glow();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
glow( model )
{
	if ( IsDefined( self.non_glow_model ) )
		return;

	self.non_glow_model = self.model;

	if ( !isdefined( model ) )
		model = self.model + "_obj";
	self SetModel( model );
}

/*
=============
///ScriptDocBegin
"Name: stopGlow( <model> )"
"Summary: Stops a model from glowing."
"Module: Utility"
"CallOn: An entity that is glowing"
"Example: keyboard stopGlow();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
stopGlow( model )
{
	if ( !isdefined( self.non_glow_model ) )
		return;

	self SetModel( self.non_glow_model );
	self.non_glow_model = undefined;
}

/*
=============
///ScriptDocBegin
"Name: array_delete_evenly( <array> , <delete_size>, <set_size> )"
"Summary: Evenly remove entries from an array. For example delete 3 out of every 4 entries in an array."
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <array>: The array, order of the array determines the order stuff is removed."
"MandatoryArg: <delete_size>: The ratio of entries to delete."
"MandatoryArg: <set_size>: The size of each set."
"Example: array = array_delete_evenly( array, 1, 3 ); // Delete 1 out of every 3 entries in the array"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_delete_evenly( array, delete_size, set_size )
{
	AssertEx( delete_size > 0, "Save size must be at least 1" );
	AssertEx( set_size > 0, "Removal size must be at least 1" );
	AssertEx( delete_size < set_size, "Save size must be less than removal size" );
	removal = [];
	delete_size = set_size - delete_size;
	foreach ( entry in array )
	{
		removal[ removal.size ] = entry;
		if ( removal.size == set_size )
		{
			// remove 2 of every 3 entrys
			removal = array_randomize( removal );
			for ( i = delete_size; i < removal.size; i++ )
			{
				removal[ i ] Delete();
			}
			removal = [];
		}
	}

	new_array = [];
	foreach ( entry in array )
	{
		if ( !isdefined( entry ) )
			continue;
		new_array[ new_array.size ] = entry;
	}

	return new_array;
}

/*
=============
///ScriptDocBegin
"Name: waittill_in_range( <origin> , <range> )"
"Summary: Wait until and entity is within range or a given origin."
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <origin>: wait until entity is within range of this position."
"MandatoryArg: <range>: wait until entity is within this distance to the given position."
"OptionalArg: <resolution>: time between poling, if unspecified uses half a second."
"Example: 	level.player waittill_in_range( obj_origin, 600 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waittill_in_range( origin, range, resolution )
{
    if( !isdefined( resolution )  )
        resolution = 0.5;
	self endon( "death" );
	while ( IsDefined( self ) )
	{
		if ( Distance( origin, self.origin ) <= range )
			break;
		wait resolution;
	}
}


/*
=============
///ScriptDocBegin
"Name: add_trace_fx( <name> )"
"Summary: Adds FX that play off a trace from a tag. See _climb.gsc for examples."
"Module: Utility"
"MandatoryArg: <name>: Name the tracefx."
"Example: add_trace_fx( "ice_pick" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_trace_fx( name )
{
	ent = SpawnStruct();
	ent thread add_trace_fx_proc( name );
	return ent;
}

/*
=============
///ScriptDocBegin
"Name: traceFX_on_tag( <fx_name> , <tag> , <trace_depth> )"
"Summary: Plays a traceFX on the specified tag."
"Module: Utility"
"CallOn: An entity with a tag."
"MandatoryArg: <fx_name>: The name of the tracefx, created with add_trace_fx."
"MandatoryArg: <tag>: The tag to play the fx on."
"MandatoryArg: <trace_depth>: How far to trace to find a surface."
"Example: car traceFX_on_tag( "player_ice_pick", "tag_origin", 10 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
traceFX_on_tag( fx_name, tag, trace_depth )
{
	origin = self GetTagOrigin( tag );
	angles = self GetTagAngles( tag );
	traceFx( fx_name, origin, angles, trace_depth );
}


/*
=============
///ScriptDocBegin
"Name: traceFx( <fx_name> , <origin> , <angles> , <trace_depth> )"
"Summary: Trace from org/ang and then play an fx where it hits"
"Module: Utility"
"MandatoryArg: <fx_name>: The TraceFX name, added with add_trace_fx. "
"MandatoryArg: <origin>: The origin to trace from. "
"MandatoryArg: <angles>: The angles to trace from. "
"MandatoryArg: <trace_depth>: The depth to trace for a surface. "
"Example: traceFx( fx_name, origin, angles, trace_depth );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
traceFx( fx_name, origin, angles, trace_depth )
{
	// plays an effect based off surface type then deletes the tag that called it
	AssertEx( IsDefined( level.trace_fx[ fx_name ] ), "No level.trace_fx with name " + fx_name );
	AssertEx( IsDefined( level.trace_fx[ fx_name ][ "default" ] ), "No default fx defined for " + fx_name );


	forward = AnglesToForward( angles );
	trace = BulletTrace( origin, origin + forward * trace_depth, false, undefined );

	if ( trace[ "fraction" ] >= 1 )
	{
		/#
		if ( GetDvarInt( "debug_tracefx" ) )
			Line( origin, origin + forward * trace_depth, ( 1, 0, 0 ), 1, 0, 500 );
		#/
		// didn't hit anything
		return;
	}

	surface = trace[ "surfacetype" ];
	if ( !isdefined( level.trace_fx[ fx_name ][ surface ] ) )
		surface = "default";

	fx_info = level.trace_fx[ fx_name ][ surface ];

	if ( IsDefined( fx_info[ "fx" ] ) )
	{
		PlayFX( fx_info[ "fx" ], trace[ "position" ], trace[ "normal" ] );
	}

	if ( IsDefined( fx_info[ "fx_array" ] ) )
	{
		foreach ( fx in fx_info[ "fx_array" ] )
		{
			PlayFX( fx, trace[ "position" ], trace[ "normal" ] );
		}
	}

	if ( IsDefined( fx_info[ "sound" ] ) )
	{
		level thread play_sound_in_space( fx_info[ "sound" ], trace[ "position" ] );
	}

	if ( IsDefined( fx_info[ "rumble" ] ) )
	{
		player = get_player_from_self();
		player PlayRumbleOnEntity( fx_info[ "rumble" ] );
	}
}


/*
=============
///ScriptDocBegin
"Name: disable_surprise()"
"Summary: Disables AI surprise"
"Module: AI"
"CallOn: An AI"
"Example: guy disable_surprise();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_surprise()
{
	self.newEnemyReactionDistSq = 0;
}

/*
=============
///ScriptDocBegin
"Name: enable_surprise()"
"Summary: reenables AI surprise"
"Module: AI"
"CallOn: An AI"
"Example: guy enable_surprise();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_surprise()
{
	self.newEnemyReactionDistSq = squared( 512 );
}

/*
=============
///ScriptDocBegin
"Name: enable_heat_behavior( <shoot_while_moving> )"
"Summary: Enables heat behavior"
"Module: AI"
"CallOn: An AI"
"OptionalArg: <shoot_while_moving>: do regular AI shoot behavior while moving. Defaults to false"
"Example: guy enable_heat_behavior();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_heat_behavior( shoot_while_moving )
{
	self.heat = true;
	self.no_pistol_switch = true;
	self.useCombatScriptAtCover = true;

	if ( !isdefined( shoot_while_moving ) || !shoot_while_moving )
	{
		self.dontshootwhilemoving = true;
		self.maxfaceenemydist = 64;
		self.pathenemylookahead = 2048;
		self disable_surprise();
	}

	self.specialReloadAnimFunc = animscripts\animset::heat_reload_anim;

	self.customMoveAnimSet[ "run" ] = anim.animsets.move[ "heat_run" ];
}


/*
=============
///ScriptDocBegin
"Name: disable_heat_behavior()"
"Summary: Disables heat behavior"
"Module: AI"
"CallOn: An AI"
"Example: guy disable_heat_behavior();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_heat_behavior()
{
	self.heat = undefined;
	self.no_pistol_switch = undefined;
	self.dontshootwhilemoving = undefined;
	self.useCombatScriptAtCover = false;
	self.maxfaceenemydist = 512;
	self.specialReloadAnimFunc = undefined;

	self.customMoveAnimSet = undefined;
}


/*
=============
///ScriptDocBegin
"Name: getVehicleArray()"
"Summary: Returns Vehicle_GetArray();"
"Module: Utility"
"Example: vehicles = getVehicleArray()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
getVehicleArray()
{
	return Vehicle_GetArray();
}

/*
=============
///ScriptDocBegin
"Name: hint( string, timeOut )"
"Summary: Creates a simple white text string at the center of the screen;"
"Module: Utility"
"Example: thread hint( &"OILRIG_HINT_C4_SWITCH" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
hint( string, timeOut, zoffset )
{
	if ( !isdefined( zoffset ) )
		zoffset = 0;

	hintfade = 0.5;

	level endon( "clearing_hints" );

	if ( IsDefined( level.hintElement ) )
		level.hintElement maps\_hud_util::destroyElem();

	level.hintElement = maps\_hud_util::createFontString( "default", 1.5 );
	level.hintElement maps\_hud_util::setPoint( "MIDDLE", undefined, 0, 30 + zoffset );
	level.hintElement.color = ( 1, 1, 1 );
	level.hintElement SetText( string );
	level.hintElement.alpha = 0;
	level.hintElement FadeOverTime( 0.5 );
	level.hintElement.alpha = 1;
	wait( 0.5 );
	level.hintElement endon( "death" );

	if ( IsDefined( timeOut ) )
		wait( timeOut );
	else
		return;

	level.hintElement FadeOverTime( hintfade );
	level.hintElement.alpha = 0;
	wait( hintfade );

	level.hintElement maps\_hud_util::destroyElem();
}


/*
=============
///ScriptDocBegin
"Name: hint_fade()"
"Summary: Fades out a text hint created with the hint() function"
"Module: Utility"
"Example: thread hint( &"OILRIG_HINT_C4_SWITCH" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
hint_fade()
{
	hintfade = 1;
	if ( IsDefined( level.hintElement ) )
	{
		level notify( "clearing_hints" );
		level.hintElement FadeOverTime( hintfade );
		level.hintElement.alpha = 0;
		wait( hintfade );
	}
}

/*
=============
///ScriptDocBegin
"Name: kill_deathflag( <theFlag>, <time> )"
"Summary: Kill everything associated with a deathflag"
"Module: Utility"
"MandatoryArg: <theFlag>: The flag to kill on "
"OptionalArg: <time>: random amount of time to wait before death "
"Example: kill_deathflag( "tower_cleared" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
kill_deathflag( theFlag, time )
{
	//assertex( IsDefined( level.flag[ theFlag ] ), "Tried to kill_deathFlag on a flag " + theFlag + " which does not exist." );
	if ( !isdefined( level.flag[ theFlag ] ) )
		return;

	if ( !isdefined( time ) )
		time = 0;

	foreach ( deathTypes in level.deathFlags[ theFlag ] )
	{
		foreach ( element in deathTypes )
		{
			if ( IsAlive( element ) )
			{
				element thread kill_deathflag_proc( time );
			}
			else
			{
				element Delete();
			}
		}
	}
}

/*
=============
///ScriptDocBegin
"Name: get_player_view_controller( <model> , <tag>, <originoffset>, <turret> )"
"Summary: Returns a turret that you can link the player to. Link the player to tag_aim."
"Module: Utility"
"MandatoryArg: <model>: The model to link to."
"MandatoryArg: <tag>: The tag to link to."
"OptionalArg: <originoffset>: Optional offset from the tag."
"OptionalArg: <turret>: Optional turret to use."
"Example: player_view_controller = get_player_view_controller( level.player_heli, "tag_guy2" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_player_view_controller( model, tag, originoffset, turret )
{
	if ( !IsDefined( turret ) )
	{
		turret = "player_view_controller";
	}

	if ( !isdefined( originoffset ) )
		originoffset = ( 0, 0, 0 );
	origin = model GetTagOrigin( tag );
	player_view_controller = SpawnTurret( "misc_turret", origin, turret );
	player_view_controller.angles = model GetTagAngles( tag );
	player_view_controller SetModel( "tag_turret" );
	player_view_controller LinkTo( model, tag, originoffset, ( 0, 0, 0 ) );
	player_view_controller MakeUnusable();
	player_view_controller Hide();
	player_view_controller SetMode( "manual" );
	/*
	player_view_controller thread maps\_debug::drawTagForever( "tag_origin" );
	player_view_controller thread maps\_debug::drawTagForever( "TAG_player", (1,0,0) );
	player_view_controller thread maps\_debug::drawTagForever( "TAG_Weapon", (0,1,0) );
	player_view_controller thread maps\_debug::drawTagForever( "tag_flash", (1,0,1) );
	model thread maps\_debug::drawTagForever( tag );
	player_view_controller thread maps\_debug::drawTagForever( "TAG_aim", (0,0,1) );
	*/
	return player_view_controller;
}

/*
=============
///ScriptDocBegin
"Name: blend_dof( <start> , <end> , <time> )"
"Summary: Blend DOF from start to end over time"
"Module: Utility"
"MandatoryArg: <start>: Starting dof values, usually level.dofDefault"
"MandatoryArg: <end>: Values you want to blend to"
"MandatoryArg: <time>: Amount of time to blend over"
"Example: blend_dof( start, end, 14 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
blend_dof( start, end, time )
{
	blend = level create_blend( ::blend_default_dof, start, end );
	blend.time = time;
}


/*
=============
///ScriptDocBegin
"Name: create_blend( <func> , <var1> , <var2> , <var3> )"
"Summary: Creates a spawnstruct that blends values over time, using a function you create (see blend_dof)"
"Module: Utility"
"MandatoryArg: <func>: The function that will blend the values "
"OptionalArg: <var1>: Optional var to use."
"OptionalArg: <var2>: Optional var to use."
"OptionalArg: <var3>: Optional var to use."
"Example: blend = create_blend( ::blend_dof, start, end );     blend.time = 14;"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
create_blend( func, var1, var2, var3 )
{
	ent = SpawnStruct();
	ent childthread process_blend( func, self, var1, var2, var3 );
	return ent;
}


/*
=============
///ScriptDocBegin
"Name: store_players_weapons( <scene> )"
"Summary: Store the player's inventory to a variable that you can recall later"
"Module: Utility"
"CallOn: A player"
"MandatoryArg: <scene>: String to store the inventory to."
"Example: level.player store_players_weapons( "c4_scene" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
store_players_weapons( scene )
{
	if ( !isdefined( self.stored_weapons ) )
	{
		self.stored_weapons = [];
	}

	array = [];
	weapons = self GetWeaponsListAll();
	foreach ( weapon in weapons )
	{
		array[ weapon ] = [];
		array[ weapon ][ "clip_left" ] = self GetWeaponAmmoClip( weapon, "left" );
		array[ weapon ][ "clip_right" ] = self GetWeaponAmmoClip( weapon, "right" );
		array[ weapon ][ "stock" ] = self GetWeaponAmmoStock( weapon );
	}

	if ( !isdefined( scene ) )
		scene = "default";

	self.stored_weapons[ scene ] = [];
	self.stored_weapons[ scene ][ "current_weapon" ] = self GetCurrentWeapon();
	self.stored_weapons[ scene ][ "inventory" ] = array;
}

/*
=============
///ScriptDocBegin
"Name: restore_players_weapons( <scene> )"
"Summary: Restore the player's inventory from a variable that you stored earlier."
"Module: Utility"
"MandatoryArg: <scene>: String to store the inventory to."
"Example: level.player restore_players_weapons( "c4_scene" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
restore_players_weapons( scene )
{
	if ( !isdefined( scene ) )
		scene = "default";

	if ( !isdefined( self.stored_weapons ) || !isdefined( self.stored_weapons[ scene ] ) )
	{
		PrintLn( "^3Warning! Tried to restore weapons for scene " + scene + " but they weren't stored" );
		return;
	}

	self TakeAllWeapons();
	foreach ( weapon, array in self.stored_weapons[ scene ][ "inventory" ] )
	{
		// We cannot give "alt-fire" weapons
		if ( WeaponInventoryType( weapon ) != "altmode" )
		{
			self GiveWeapon( weapon );
		}

		self SetWeaponAmmoClip( weapon, array[ "clip_left" ], "left" );
		self SetWeaponAmmoClip( weapon, array[ "clip_right" ], "right" );
		self SetWeaponAmmoStock( weapon, array[ "stock" ] );
	}

	current_weapon = self.stored_weapons[ scene ][ "current_weapon" ];
	if ( current_weapon != "none" )
		self SwitchToWeapon( current_weapon );
}

/*
=============
///ScriptDocBegin
"Name: hide_entity()"
"Summary: Used to hide large groups of ents when you are unsure of the exact classname. Will use appropriate functions for turning off triggers, connecting paths in brushmodels, etc. if appropriate."
"Module: Utility"
"CallOn: An entity"
"Example: array_thread( group_of_misc_entities,::hide_entity );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
hide_entity()
{

	switch( self.code_classname )
	{
		case "light_spot":
		case "script_vehicle":
		case "script_model":
			self Hide();
			break;
		case "script_brushmodel":
			self Hide();
			self NotSolid();
			if ( self.spawnflags & 1 )
				self ConnectPaths();
			break;
		case "trigger_radius":
		case "trigger_multiple":
		case "trigger_use":
		case "trigger_use_touch":
		case "trigger_multiple_flag_set":
		case "trigger_multiple_breachIcon":
		case "trigger_multiple_flag_lookat":
		case "trigger_multiple_flag_looking":
			self trigger_off();
			break;
		default:
			AssertMsg( "Unable to hide entity at " + self.origin + ". Need to define a method for handling entities of classname " + self.code_classname );
	}
}

/*
=============
///ScriptDocBegin
"Name: show_entity()"
"Summary: Used to show large groups of hidden ents when you are unsure of the exact classname. Will use appropriate functions for turning off triggers, disconnecting paths in brushmodels, etc. if appropriate."
"Module: Utility"
"CallOn: An entity"
"Example: array_thread( group_of_misc_entities,::show_entity );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
show_entity()
{
	switch( self.code_classname )
	{
		case "light_spot":
		case"script_vehicle":
		case"script_model":
			self Show();
			break;
		case "script_brushmodel":
			self Show();
			self Solid();
			if ( self.spawnflags & 1 )
				self DisconnectPaths();
			break;
		case "trigger_radius":
		case "trigger_multiple":
		case "trigger_use":
		case "trigger_use_touch":
		case "trigger_multiple_flag_set":
		case "trigger_multiple_breachIcon":
		case "trigger_multiple_flag_lookat":
		case "trigger_multiple_flag_looking":
			self trigger_on();
			break;
		default:
			AssertMsg( "Unable to show entity at " + self.origin + ". Need to define a method for handling entities of classname " + self.code_classname );
	}
}
/*
=============
///ScriptDocBegin
"Name: _rotateyaw( <yaw_angle> , <time> , <time> , <time> )"
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
_rotateyaw( yaw_angle, time, acc_time, dec_time )
{
	if ( IsDefined( dec_time ) )
		self RotateYaw( yaw_angle, time, acc_time, dec_time );
	else
	if ( IsDefined( acc_time ) )
		self RotateYaw( yaw_angle, time, acc_time );
	else
		self RotateYaw( yaw_angle, time );
}

/*
=============
///ScriptDocBegin
"Name: set_moveplaybackrate( <rate>, <time> )"
"Summary: set an AI's .moveplaybackrate over time"
"Module: AI"
"CallOn: AI"
"MandatoryArg: <rate>: the speed of the playbackrate ( default rate is 1 )"
"OptionalArg: <time>: time to lerp the rate in - if no time then set instantly"
"Example: level.price set_moveplaybackrate( 1.1 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_moveplaybackrate( rate, time )
{
	self notify( "set_moveplaybackrate" );
	self endon( "set_moveplaybackrate" );

	if ( IsDefined( time ) )
	{
		range = rate - self.moveplaybackrate;
		interval = .05;
		numcycles = time / interval;
		fraction = range / numcycles;

		while ( abs( rate - self.moveplaybackrate ) > abs( fraction * 1.1 ) )
		{
			self.moveplaybackrate += fraction;
			wait interval;
		}
	}

	self.moveplaybackrate = rate;
}

/*
=============
///ScriptDocBegin
"Name: array_spawn_function( <array> , <func>, param1, param2, param3, param4 )"
"Summary: Adds a spawn function to an array of spawners"
"Module: Utility"
"MandatoryArg: <array>: Array of spawners"
"MandatoryArg: <func>: Function to run on the guy when he spawns"
"OptionalArg: <param1> : An optional parameter."
"OptionalArg: <param2> : An optional parameter."
"OptionalArg: <param3> : An optional parameter."
"OptionalArg: <param4> : An optional parameter."
"Example: array_spawn_function( spawners, ::do_it, do_it_parameter );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_spawn_function( array, func, param1, param2, param3, param4 )
{
	AssertEx( IsDefined( array ), "That isn't an array!" );
	AssertEx( IsArray( array ), "That isn't an array!" );
	AssertEx( array.size, "That array is empty!" );
	foreach ( spawner in array )
	{
		AssertEx( IsSpawner( spawner ), "This isn't a spawner!" );
		spawner thread add_spawn_function( func, param1, param2, param3, param4 );
	}
}

/*
=============
///ScriptDocBegin
"Name: array_spawn_function_targetname( <key> , <func>, param1, param2, param3, param4 )"
"Summary: Gets spawners with the specified targetname and adds a spawn function to them"
"Module: Utility"
"MandatoryArg: <key>: targetname of spawners"
"MandatoryArg: <func>: Function to run on the guys when they spawn"
"OptionalArg: <param1> : An optional parameter."
"OptionalArg: <param2> : An optional parameter."
"OptionalArg: <param3> : An optional parameter."
"OptionalArg: <param4> : An optional parameter."
"Example: array_spawn_function_targetname( "specialguy", ::do_it );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_spawn_function_targetname( key, func, param1, param2, param3, param4 )
{
	array = GetEntArray( key, "targetname" );
	array_spawn_function( array, func, param1, param2, param3, param4 );
}


/*
=============
///ScriptDocBegin
"Name: array_spawn_function_noteworthy( <key> , <func>, param1, param2, param3, param4 )"
"Summary: Gets spawners with the specified noteworthy and adds a spawn function to them"
"Module: Utility"
"MandatoryArg: <key>: noteworthy of spawners"
"MandatoryArg: <func>: Function to run on the guys when they spawn"
"OptionalArg: <param1> : An optional parameter."
"OptionalArg: <param2> : An optional parameter."
"OptionalArg: <param3> : An optional parameter."
"OptionalArg: <param4> : An optional parameter."
"Example: array_spawn_function_noteworthy( "specialguy", ::do_it );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_spawn_function_noteworthy( key, func, param1, param2, param3, param4 )
{
	array = GetEntArray( key, "script_noteworthy" );
	array_spawn_function( array, func, param1, param2, param3, param4 );
}




/*
=============
///ScriptDocBegin
"Name: enable_dontevershoot( <enable_dontevershoot> )"
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
enable_dontevershoot()
{

/*
=============
///ScriptFieldDocBegin
"Name: .dontEverShoot"
"Summary: dontEverShoot"
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

	self.dontEverShoot = true;
}

/*
=============
///ScriptDocBegin
"Name: disable_dontevershoot( <disable_dontevershoot> )"
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
disable_dontevershoot()
{
	self.dontEverShoot = undefined;
}

/*
=============
///ScriptDocBegin
"Name: create_vision_set_fog( <fogset> )"
"Summary: Stores fog settings that get executed automatically with trigger_multiple_visionset"
"Module: Utility"
"MandatoryArg: <fogset>: Name, must be the same as the vision set it works with. "
"Example: ent = create_vision_set_fog( "gulag" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
create_vision_set_fog( fogset )
{
	if ( !isdefined( level.vision_set_fog ) )
		level.vision_set_fog = [];
	ent = SpawnStruct();
	ent.name = fogset;

	level.vision_set_fog[ fogset ] = ent;
	return ent;
}

/*
=============
///ScriptDocBegin
"Name: get_vision_set_fog( <fogset> )"
"Summary: Get vision set fog defined by create_vision_set_fog( fogset ). Returns Undefined if doesn't exist."
"Module: Utility"
"MandatoryArg: <fogset>: Unique vision set name"
"Example: ent = get_vision_set_fog( "contingency_bridge" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_vision_set_fog( fogset )
{
	if ( !isdefined( level.vision_set_fog ) )
		level.vision_set_fog = [];

	ent = level.vision_set_fog[ fogset ];
	//assertex( IsDefined( ent ), "visiont set fog: " + fogset + "does not exist, use create_vision_set_fog( " + fogset + " ) in your level_fog.gsc." );
	return ent;
}


/*
=============
///ScriptDocBegin
"Name: create_fog( <fogset> )"
"Summary: Stores fog settings that get executed automatically with trigger_multiple_fog"
"Module: Utility"
"MandatoryArg: <fogset>: Unique fog setting name"
"Example: ent = create_fog( "contingency_bridge" );"
"NoteLine: Here are some values you might set on the ent:"
"NoteLine: ent.startDist"
"NoteLine: ent.halfwayDist"
"NoteLine: ent.red"
"NoteLine: ent.green"
"NoteLine: ent.blue"
"NoteLine: ent.maxOpacity"
"NoteLine: ent.sunRed"
"NoteLine: ent.sunGreen"
"NoteLine: ent.sunBlue"
"NoteLine: ent.sunDir"
"NoteLine: ent.sunBeginFadeAngle"
"NoteLine: ent.sunEndFadeAngle"
"NoteLine: ent.normalFogScale"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

create_fog( fogset )
{
	if ( !isdefined( level.fog_set ) )
		level.fog_set = [];
	ent = SpawnStruct();
	ent.name = fogset;

	level.fog_set[ fogset ] = ent;
	return ent;
}

/*
=============
///ScriptDocBegin
"Name: get_fog( <fogset> )"
"Summary: Get fog defined by create_fog( fogset ). Returns Undefined if doesn't exist."
"Module: Utility"
"MandatoryArg: <fogset>: Unique fog setting name"
"Example: ent = get_fog( "contingency_fog_forest" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_fog( fogset )
{
	if ( !isdefined( level.fog_set ) )
		level.fog_set = [];

	ent = level.fog_set[ fogset ];
	//assertex( IsDefined( ent ), "fog set: " + fogset + "does not exist, use create_fog( " + fogset + " ) in your level_fog.gsc." );
	return ent;
}


init_self_fog_transition()
{
	if ( !IsDefined( self.fog_transition_ent ) )
	{
		self.fog_transition_ent = SpawnStruct();
		self.fog_transition_ent.fogset = "";
		self.fog_transition_ent.time = 0;
	}
}


/*
=============
///ScriptDocBegin
"Name: fog_set_changes( <fog_set> , <transition_time> )"
"Summary: Switches to a fog set over a transition time."
"Module: Utility"
"Call on: The Player"
"MandatoryArg: <fog_set>: The fog set name, defined by create_fog( name )"
"MandatoryArg: <transition_time>: How long to transition for"
"Example: level.player fog_set_changes( "contingency_fog_forest", 10 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
fog_set_changes( fog_set, transition_time )
{
	if ( !isPlayer( self ) )
		maps\_art::init_fog_transition();
	else
		init_self_fog_transition();
	
	if ( !isdefined( level.fog_set ) )
		level.fog_set = [];

	ent = level.fog_set[ fog_set ];
	if ( !isdefined( ent ) )
	{
		AssertEx( IsDefined( level.vision_set_fog ), "Fog set:" + fog_set + " does not exist, use create_fog( " + fog_set + " ) or create_vision_set_fog( " + fog_set + " ); in your /createart/level_fog.gsc" );
		ent = level.vision_set_fog[ fog_set ];
	}

	AssertEx( IsDefined( ent ), "Fog set:" + fog_set + " does not exist, use create_fog( " + fog_set + " ) or create_vision_set_fog( " + fog_set + " ); in your /createart/level_fog.gsc" );

	//if ( !isdefined( ent ) )
	//	return;

	// transition time override
	if ( !isdefined( transition_time ) )
		transition_time = ent.transitiontime;
	AssertEx( IsDefined( transition_time ), "Fog set: " + fog_set + " does not have a transition_time defined and a time was not specified in the function call." );

	if(  GetDvarInt( "scr_art_tweak") != 0 )
	{
		translateEntTosliders(ent );
		//pending some mechanism to handle transition while your editting, just set to zero for now since it leaves less room for ugly.
		transition_time = 0;
	}

	if ( !isPlayer( self ) )
	{
		// this the same fog set we're already doing?
		if ( level.fog_transition_ent.fogset == fog_set && level.fog_transition_ent.time == transition_time )
			return;

		set_fog_to_ent_values( ent, transition_time  );

		level.fog_transition_ent.fogset = fog_set;
		level.fog_transition_ent.time = transition_time;	
	}
	else
	{
		// this the same fog set we're already doing?
		if ( self.fog_transition_ent.fogset == fog_set && self.fog_transition_ent.time == transition_time )
			return;

		self set_fog_to_ent_values( ent, transition_time  );

		self.fog_transition_ent.fogset = fog_set;
		self.fog_transition_ent.time = transition_time;
	}
}

translateEntTosliders(ent)
{
	/#
		SetDevDvar( "scr_fog_exp_halfplane", ent.halfwayDist );
		SetDevDvar( "scr_fog_nearplane", ent.startDist);

		color = ( ent.red, ent.green, ent.blue );
		SetDevDvar( "scr_fog_color", color  );
		SetDevDvar( "scr_fog_max_opacity", ent.maxOpacity );

		if ( IsDefined( ent.sunFogEnabled ) && ent.sunFogEnabled)
		{

			SetDevDvar( "scr_sunFogEnabled", 1 );
			SetDevDvar( "scr_sunFogColor", (ent.sunRed, ent.sunGreen,ent.sunBlue) );
			SetDevDvar( "scr_sunFogDir", ent.sunDir );
			SetDevDvar( "scr_sunFogBeginFadeAngle", ent.sunBeginFadeAngle );
			SetDevDvar( "scr_sunFogEndFadeAngle", ent.sunEndFadeAngle );
			SetDevDvar( "scr_sunFogScale", ent.normalFogScale );
		}
		else
		{
			SetDevDvar( "scr_sunFogEnabled", 0 );
		}

	#/



}

set_fog_to_ent_values( ent, transition_time )
{
	if ( IsDefined( ent.sunFogEnabled) && ent.sunFogEnabled)
	{
		if ( !isPlayer( self ) )
		{
			SetExpFog(
			ent.startDist,
			ent.halfwayDist,
			ent.red,
			ent.green,
			ent.blue,
			ent.maxOpacity,
			transition_time,
			ent.sunRed,
			ent.sunGreen,
			ent.sunBlue,
			ent.sunDir,
			ent.sunBeginFadeAngle,
			ent.sunEndFadeAngle,
			ent.normalFogScale );
		}
		else
		{
			self PlayerSetExpFog(
			ent.startDist,
			ent.halfwayDist,
			ent.red,
			ent.green,
			ent.blue,
			ent.maxOpacity,
			transition_time,
			ent.sunRed,
			ent.sunGreen,
			ent.sunBlue,
			ent.sunDir,
			ent.sunBeginFadeAngle,
			ent.sunEndFadeAngle,
			ent.normalFogScale );
		}	
	}
	else
	{
		if ( !isPlayer( self ) )
		{
			SetExpFog(
			ent.startDist,
			ent.halfwayDist,
			ent.red,
			ent.green,
			ent.blue,
			ent.maxOpacity,
			transition_time );
		}
		else
		{
			self PlayerSetExpFog(
			ent.startDist,
			ent.halfwayDist,
			ent.red,
			ent.green,
			ent.blue,
			ent.maxOpacity,
			transition_time );
		}	
	}
}

/*
=============
///ScriptDocBegin
"Name: vision_set_fog_changes( <vision_set> , <transition_time> )"
"Summary: Switches to a vision set over a transition time and changes fog, safely overwriting other calls to the same function. "
"Module: Utility"
"Call on: The Player"
"MandatoryArg: <vision_set>: The vision set file"
"MandatoryArg: <transition_time>: How long to transition for"
"Example: level.player vision_set_fog_changes( "gulag_flying", 10 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
vision_set_fog_changes( vision_set, transition_time )
{
	do_fog = vision_set_changes( vision_set, transition_time );
	if ( do_fog && IsDefined( get_vision_set_fog( vision_set ) ) )
	{
		fog_set_changes( vision_set, transition_time );
	}
}

init_self_visionset()
{
	if ( !IsDefined( self.vision_set_transition_ent ) )
	{
		self.vision_set_transition_ent = SpawnStruct();
		self.vision_set_transition_ent.vision_set = "";
		self.vision_set_transition_ent.time = 0;
	}
}

/*
=============
///ScriptDocBegin
"Name: vision_set_changes( <vision_set> , <transition_time> )"
"Summary: Switches to a vision set over a transition time, safely overwriting other calls to the same function. "
"Module: Utility"
"MandatoryArg: <vision_set>: The vision set file"
"MandatoryArg: <transition_time>: How long to transition for"
"Example: vision_set_changes( "gulag_flying", 10 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
vision_set_changes( vision_set, transition_time )
{
	if ( !IsPlayer( self ) )
	{
		vision_set_initd = true;
		if ( !isdefined( level.vision_set_transition_ent ) )
		{
			level.vision_set_transition_ent = SpawnStruct();
			level.vision_set_transition_ent.vision_set = "";
			level.vision_set_transition_ent.time = 0;
			vision_set_initd = false;
		}

		// this the same vision set we're already doing?
		if ( level.vision_set_transition_ent.vision_set == vision_set && level.vision_set_transition_ent.time == transition_time )
		{
			return false;// no fog
		}

		level.vision_set_transition_ent.vision_set = vision_set;
		level.vision_set_transition_ent.time = transition_time;

		if( vision_set_initd && ( GetDvarInt( "scr_art_tweak") != 0 ) )
		{
/#
			transition_time = 0;
			VisionSetNaked( vision_set, transition_time );
			level.player openpopupmenu("dev_vision_exec");
			wait( 0.05 );
			level.player closepopupmenu();
	#/
		}
		else
		{
			VisionSetNaked( vision_set, transition_time );
		}

		//iprintlnbold( vision_set );
		level.lvl_visionset = vision_set;
		SetDvar( "vision_set_current", vision_set );
	}
	else
	{
		self init_self_visionset();
		self.vision_set_transition_ent.vision_set = GetDvar( "vision_set_current" );

		// this the same vision set we're already doing?
		if ( self.vision_set_transition_ent.vision_set == vision_set && self.vision_set_transition_ent.time == transition_time )
			return false;// no fog

		self.vision_set_transition_ent.vision_set = vision_set;
		self.vision_set_transition_ent.time = transition_time;

		self VisionSetNakedForPlayer( vision_set, transition_time );
	}

	return true;// do fog
}




set_art_tweaked_vision_set()
{
	/#
	ent = level.vision_set_vision[ level.vision_set_transition_ent.vision_set ];

		if( !isdefined(ent.r_glow ) )
		{
			VisionSetNaked( level.vision_set_transition_ent.vision_set, 0 );
			level.player openpopupmenu("dev_vision_update_from_static");
			ent.selected = true;
			wait .05;
			level.player closepopupmenu();
			return;
		}

		setdvar( "scr_glowTweakEnable", ent.r_glow );
		setdvar( "scr_glowTweakRadius0", ent.r_glowRadius0 );
		setdvar( "scr_glowTweakBloomCutoff", ent.r_glowBloomCutoff );
		setdvar( "scr_glowTweakBloomDesaturation", ent.r_glowBloomDesaturation );
		setdvar( "scr_glowTweakBloomIntensity0", ent.r_glowBloomIntensity0 );
		setdvar( "scr_filmTweakEnable", ent.r_filmEnable );
		setdvar( "scr_filmTweakContrast", ent.r_filmContrast );
		setdvar( "scr_filmTweakBrightness", ent.r_filmBrightness );
		setdvar( "scr_filmTweakDesaturation", ent.r_filmDesaturation );
		setdvar( "scr_filmTweakDesaturationDark", ent.r_filmDesaturationDark );
		setdvar( "scr_filmTweakInvert", ent.r_filmInvert );
		setdvar( "scr_filmTweakLightTint", ent.r_filmLightTint );
		setdvar( "scr_filmTweakMediumTint", ent.r_filmMediumTint );
		setdvar( "scr_filmTweakDarkTint", ent.r_filmDarkTint );
		setdvar( "scr_primaryLightUseTweaks", ent.r_primaryLightUseTweaks );
		setdvar( "scr_primaryLightTweakDiffuseStrength", ent.r_primaryLightTweakDiffuseStrength );
		setdvar( "scr_primaryLightTweakSpecularStrength", ent.r_primaryLightTweakSpecularStrength );

		level.player openpopupmenu( "dev_vision_exec" );
		wait .05;
		level.player closepopupmenu();
	#/
}

/*
=============
///ScriptDocBegin
"Name: enable_teamflashbangImmunity( <enable_teamflashbangImmunity> )"
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
enable_teamflashbangImmunity()
{
	self thread enable_teamflashbangImmunity_proc();
}

enable_teamflashbangImmunity_proc()
{
	self endon( "death" );

	while ( 1 )
	{
		self.teamFlashbangImmunity = true;
		wait .05;
	}
}

/*
=============
///ScriptDocBegin
"Name: disable_teamflashbangImmunity( <disable_teamflashbangImmunity> )"
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
disable_teamflashbangImmunity()
{
	self.teamFlashbangImmunity = undefined;
}

/*
=============
///ScriptDocBegin
"Name: _radiusdamage( <origin> , <range> , <maxdamage> , <mindamage> , <attacker> )"
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
_radiusdamage( origin, range, maxdamage, mindamage, attacker )
{
	if ( !isdefined( attacker ) )
		RadiusDamage( origin, range, maxdamage, mindamage );
	else
		RadiusDamage( origin, range, maxdamage, mindamage, attacker );
}



/*
=============
///ScriptDocBegin
"Name: mask_interactives_in_volumes( <volumes> )"
"Summary: Masks interactive tvs in volumes so they don't use entities. Must be done before _load."
"Module: Utility"
"MandatoryArg: <volumes>: Array of volumes to hide interactive objects in"
"Example: mask_interactives_in_volumes( volumes );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
mask_interactives_in_volumes( volumes )
{
	tvs = GetEntArray( "interactive_tv", "targetname" );

	foreach ( volume in volumes )
	{
		volume.interactives = [];
	}

	foreach ( tv in tvs )
	{
		foreach ( volume in volumes )
		{
			if ( !volume IsTouching( tv ) )
				continue;

			volume put_interactive_in_volume( tv );
			break;
		}
	}
}

/*
=============
///ScriptDocBegin
"Name: activate_interactives_in_volume()"
"Summary: Activates masked interactive tvs in a volume"
"Module: Utility"
"CallOn: A masking volume"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: volume activate_interactives_in_volume();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
activate_interactives_in_volume()
{
	if ( !isdefined( self.interactives ) )
		return;

	foreach ( ent in self.interactives )
	{
		toy = Spawn( "script_model", ( 0, 0, 0 ) );

		toy SetModel( ent.toy_model );
		toy.origin = ent.origin;
		toy.angles = ent.angles;
		toy.script_noteworthy = ent.script_noteworthy;
		toy.target = ent.target;
		toy.targetname = ent.targetname;

		toy thread maps\_interactive_objects::tv_logic();
	}

	self.interactives = [];
}

/*
=============
///ScriptDocBegin
"Name: mask_destructibles_in_volumes( <volumes> )"
"Summary: Masks destructibles in an array of volumes so they dont use entities. Must be done before _load.""
"Module: Utility"
"MandatoryArg: <volumes>: Array of volumes "
"Example: mask_destructibles_in_volumes( vols );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
mask_destructibles_in_volumes( volumes )
{
	destructible_toy = GetEntArray( "destructible_toy", "targetname" );
	destructible_vehicles = GetEntArray( "destructible_vehicle", "targetname" );
	
	combined_destructibles = array_combine( destructible_toy, destructible_vehicles );
	
	foreach ( volume in volumes )
	{
		volume.destructibles = [];
	}

	foreach ( toy in combined_destructibles )
	{
		foreach ( volume in volumes )
		{
			if ( !volume IsTouching( toy ) )
				continue;

			volume put_toy_in_volume( toy );
			break;
		}
	}
}

/*
=============
///ScriptDocBegin
"Name: mask_exploders_in_volume( <volumes> )"
"Summary: Masks exploders in an array of volumes so they dont use entities. Must be done before _load.""
"Module: Utility"
"MandatoryArg: <volumes>: Array of volumes "
"Example: mask_exploders_in_volume( vols );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

mask_exploders_in_volume( volumes )
{
    if( GetDvar( "createfx" ) != "" )
        return;
	// Hide exploder models.
	ents = GetEntArray( "script_brushmodel", "classname" );
	smodels = GetEntArray( "script_model", "classname" );
	for ( i = 0; i < smodels.size; i++ )
		ents[ ents.size ] = smodels[ i ];

    foreach( volume in volumes )
    	foreach ( ent in ents )
    	{
    		if ( IsDefined( ent.script_prefab_exploder ) )
    			ent.script_exploder = ent.script_prefab_exploder;
    
    		if ( !IsDefined( ent.script_exploder ) )
    		    continue;
            
            if ( !IsDefined( ent.model ) )
                continue;
                
            if ( ent.code_classname != "script_model" )
                continue;
            
            if ( !ent IsTouching( volume ) )
                continue;
                
            ent.masked_exploder = true;
    	}
}


/*
=============
///ScriptDocBegin
"Name: activate_exploders_in_volume()"
"Summary: Activates masked exploders in a volume"
"Module: Utility"
"CallOn: A masking volume"
"Example: volume activate_exploders_in_volume();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

activate_exploders_in_volume()
{
    test_org = Spawn( "script_origin", ( 0, 0, 0 ) );
    
	foreach ( EntFx in level.createfxent )
	{
	    if ( !IsDefined( EntFx.v[ "masked_exploder" ] ) )
	        continue;
        test_org.origin = EntFx.v[ "origin" ];
        test_org.angles = EntFx.v[ "angles" ];

        if( !test_org IsTouching( self ) )
            continue;
        
	    model_name = EntFx.v[ "masked_exploder" ];
	    spawnflags = EntFx.v[ "masked_exploder_spawnflags" ];
	    disconnect_paths = EntFX.v[ "masked_exploder_script_disconnectpaths" ];
	    new_ent = Spawn( "script_model", ( 0, 0, 0 ), spawnflags );
	    new_ent SetModel( model_name );
	    new_ent.origin = EntFx.v[ "origin" ];
	    new_ent.angles = EntFx.v[ "angles" ];
	    Entfx.v[ "masked_exploder" ]  = undefined;
	    Entfx.v[ "masked_exploder_spawnflags" ]  = undefined;
	    Entfx.v[ "masked_exploder_script_disconnectpaths" ]  = undefined;
	    new_ent.disconnect_paths = disconnect_paths;
	    new_ent.script_exploder = EntFx.v[ "exploder" ];
	    maps\_load::setup_individual_exploder( new_ent );
	    EntFX.model = new_ent;
	}
	test_org delete();
}

/*
=============
///ScriptDocBegin
"Name: precache_destructible( <destructible_type> )"
"Summary: precaches a destructible. Useful for when you want to spawn a destructible at runtime."
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <destructible_type>: type found in _destructible_types "
"Example:  toy precache_destructible( toy.destructible_type );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
precache_destructible( destructible_type )
{
    infoIndex = common_scripts\_destructible_types::getInfoIndex(  destructible_type );

    // if it's already been created dont create it again
    if ( infoIndex != -1 )
        return;
        
	struct = SpawnStruct();
	struct.destructibleInfo= self common_scripts\_destructible_types::makeType( destructible_type );
	struct thread common_scripts\_destructible::precache_destructibles();
	struct thread common_scripts\_destructible::add_destructible_fx();
}

/*
=============
///ScriptDocBegin
"Name: delete_destructibles_in_volumes( <volumes> )"
"Summary: deletes destructibles in an array of volumes so they dont use entities."
"Module: Utility"
"MandatoryArg: <volumes>: Array of volumes "
"Example: delete_destructibles_in_volumes( vols );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

delete_destructibles_in_volumes( volumes, dodelayed )
{
	foreach ( volume in volumes )
		volume.destructibles = [];
	names = [ "destructible_toy", "destructible_vehicle" ];
	incs = 0;
	
	if ( !IsDefined( dodelayed ) )
		dodelayed = false;
	foreach( name in names )
	{
		destructible_toy = GetEntArray( name, "targetname" );
		foreach ( toy in destructible_toy )
		{
			foreach ( volume in volumes )
			{
				if( dodelayed )
				{
					incs++;
					incs %= 5;
					if( incs == 1 )
						wait 0.05;
				}
				if ( !volume IsTouching( toy ) )
					continue;
				toy delete();
				break;
			}
		}
		
	}
}

/*
=============
///ScriptDocBegin
"Name: delete_interactives_in_volumes( <volumes> )"
"Summary: Delete interactive tvs in volumes so they don't use entities. "
"Module: Utility"
"MandatoryArg: <volumes>: Array of volumes to hide interactive objects in"
"Example: delete_interactives_in_volumes( volumes );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

delete_interactives_in_volumes( volumes, dodelayed )
{
	tvs = GetEntArray( "interactive_tv", "targetname" );

	foreach ( volume in volumes )
	{
		volume.interactives = [];
	}

	incs = 0;
	if ( !IsDefined( dodelayed ) )
		dodelayed = false;

	foreach ( tv in tvs )
	{
		foreach ( volume in volumes )
		{
			if ( dodelayed )
			{
				incs++;
				incs  %= 5;
				if ( incs == 1 )
					wait 0.05;
			}
			
			if ( !volume IsTouching( tv ) )
				continue;

			tv Delete();
			break;
		}
	}
}


/*
=============
///ScriptDocBegin
"Name: delete_exploders_in_volumes( <volumes> )"
"Summary: Delete exploders in volumes so they don't use entities."
"Module: Utility"
"MandatoryArg: <volumes>: Array of volumes to delete entities in"
"Example: delete_exploders_in_volumes( volumes );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

delete_exploders_in_volumes( volumes, dodelayed  )
{
	ents = GetEntArray( "script_brushmodel", "classname" );
	smodels = GetEntArray( "script_model", "classname" );
	for ( i = 0; i < smodels.size; i++ )
		ents[ ents.size ] = smodels[ i ];
		
    delete_ents = [];
    
    test_org = Spawn( "script_origin", ( 0, 0, 0 ) );

	incs = 0;
	if ( !IsDefined( dodelayed ) )
		dodelayed = false;


    foreach( volume in volumes )
    	foreach ( ent in ents )
    	{
    		if ( !IsDefined( ent.script_exploder ) )
    		    continue;
            test_org.origin = ent GetOrigin();
            if( !volume IsTouching( test_org ) )
                continue;
            delete_ents[ delete_ents.size ]  = ent;
    	}
    	
	array_delete( delete_ents );
    
    test_org Delete();
}
/*
=============
///ScriptDocBegin
"Name: activate_destructibles_in_volume()"
"Summary: Activate destructibles in a masked volume."
"Module: Utility"
"CallOn: A mask volume"
"Example: vol activate_destructibles_in_volume();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
activate_destructibles_in_volume()
{
	if ( !isdefined( self.destructibles ) )
		return;

	foreach ( ent in self.destructibles )
	{
		toy = Spawn( "script_model", ( 0, 0, 0 ) );

		toy SetModel( ent.toy_model );
		toy.origin = ent.origin;
		toy.angles = ent.angles;
		toy.script_noteworthy = ent.script_noteworthy;
		toy.targetname = ent.targetname;
		toy.target = ent.target;
		toy.script_linkto = ent.script_linkto;
		toy.destructible_type = ent.destructible_type;
		toy.script_noflip = ent.script_noflip;

		toy common_scripts\_destructible::setup_destructibles( true );// true meaning don't precache
	}

	self.destructibles = [];
}

/*
=============
///ScriptDocBegin
"Name: setFlashbangImmunity( <immune> )"
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
setFlashbangImmunity( immune )
{
	self.flashBangImmunity = immune;
}


/*
=============
///ScriptDocBegin
"Name: flashBangGetTimeLeftSec()"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"Example: duration = flashBangGetTimeLeftSec();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
flashBangGetTimeLeftSec()
{
	Assert( IsDefined( self ) );
	Assert( IsDefined( self.flashEndTime ) );

	// duration is the flash time left
	durationMs = self.flashEndTime - GetTime();
	if ( durationMs < 0 )
		return 0;

	// return the duration in seconds
	return( durationMs * 0.001 );
}


/*
=============
///ScriptDocBegin
"Name: flashBangIsActive()"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"Example: active = flashBangIsActive();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
flashBangIsActive()
{
	return( flashBangGetTimeLeftSec() > 0 );
}


/*
=============
///ScriptDocBegin
"Name: flashBangStart( <duration> )"
"Summary: I'm guessing it makes a guy get flash banged, maybe somebody could FILL IN THE FREAKING DOCS"
"Module: Entity"
"CallOn: An entity"
"Example: actor flashBangStart( 4.5 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
flashBangStart( duration )
{
	Assert( IsDefined( self ) );
	Assert( IsDefined( duration ) );
/*
=============
///ScriptFieldDocBegin
"Name: flashBangImmunity"
"Summary: flashBangImmunity"
"Module: Utility"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
	if ( IsDefined( self.flashBangImmunity ) && self.flashbangImmunity )
		return;

	// If we're alreayd flashing, update the time to the one that would last the longest
	newFlashEndTime = GetTime() + ( duration * 1000.0 );

	if ( IsDefined( self.flashendtime ) )
		self.flashEndTime = max( self.flashendtime, newFlashEndTime );
	else
		self.flashendtime = newFlashEndTime;

	self notify( "flashed" );
	self SetFlashBanged( true );
}

/*
=============
///ScriptDocBegin
"Name: waittill_volume_dead()"
"Summary: Waits for all the guys in a volume to die."
"Module: Utility"
"CallOn: A volume"
"Example: volume waittill_volume_dead()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waittill_volume_dead()
{
	for ( ;; )
	{
		ai = GetAISpeciesArray( "axis", "all" );

		found_guy = false;
		foreach ( guy in ai )
		{
			if ( !isalive( guy ) )
				continue;
			if ( guy IsTouching( self ) )
			{
				found_guy = true;
				break;
			}

			// check all the time, 4 guys per frame
			wait( 0.0125 );
		}
		if ( !found_guy )
		{
			// do one more complete check
			aHostiles = self get_ai_touching_volume( "axis" );
			if ( !aHostiles.size )
				break;
		}
		wait( 0.05 );

		//aHostiles = self get_ai_touching_volume( "axis" );
		//if ( !aHostiles.size )
		//	break;
		//wait(
		//waittill_dead( aHostiles );
	}
}

/*
=============
///ScriptDocBegin
"Name: waittill_volume_dead_or_dying()"
"Summary: Waits for all the guys in a volume to die or do long death."
"Module: Utility"
"CallOn: A volume"
"Example: volume waittill_volume_dead_or_dying()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waittill_volume_dead_or_dying()
{
	ever_found_guy = false;
	for ( ;; )
	{
		ai = GetAISpeciesArray( "axis", "all" );

		found_guy = false;
		foreach ( guy in ai )
		{
			if ( !isalive( guy ) )
				continue;
			if ( guy IsTouching( self ) )
			{
				if ( guy doingLongDeath() )
					continue;

				found_guy = true;
				ever_found_guy = true;
				break;
			}

			// check all the time, 4 guys per frame
			wait( 0.0125 );
		}
		if ( !found_guy )
		{
			// do one more complete check
			aHostiles = self get_ai_touching_volume( "axis" );
			if ( !aHostiles.size )
			{
				break;
			}
			else
			{
				ever_found_guy = true;
			}
		}
		wait( 0.05 );

		//aHostiles = self get_ai_touching_volume( "axis" );
		//if ( !aHostiles.size )
		//	break;
		//wait(
		//waittill_dead( aHostiles );
	}
	return ever_found_guy;
}

/*
=============
///ScriptDocBegin
"Name: waittill_volume_dead_then_set_flag( <sFlag> )"
"Summary: Read the function name."
"Module: Utility"
"CallOn: A volume"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: volume waittill_volume_dead_then_set_flag( "some_flag" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waittill_volume_dead_then_set_flag( sFlag )
{
	self waittill_volume_dead();
	flag_set( sFlag );
}

/*
=============
///ScriptDocBegin
"Name: waittill_targetname_volume_dead_then_set_flag( <targetname> , <msg> )"
"Summary: Read the function name."
"Module: Utility"
"MandatoryArg: <targetname>: The targetname "
"OptionalArg: <msg>: The flag "
"Example: waittill_targetname_volume_dead_then_set_flag( "some_targetname", "some_flag" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waittill_targetname_volume_dead_then_set_flag( targetname, msg )
{
	volume = GetEnt( targetname, "targetname" );
	AssertEx( IsDefined( volume ), "No volume for targetname " + targetname );
	volume waittill_volume_dead_then_set_flag( msg );
}

/*
=============
///ScriptDocBegin
"Name: player_can_be_shot()"
"Summary: The player gets correct attackeraccuracy again."
"Module: Utility"
"Example: player_can_be_shot();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_can_be_shot()
{
	level.player ent_flag_clear( "player_zero_attacker_accuracy" );
	level.player.IgnoreRandomBulletDamage = false;
	level.player maps\_gameskill::update_player_attacker_accuracy();
}

/*
=============
///ScriptDocBegin
"Name: player_cant_be_shot()"
"Summary: The player gets 0 attackeraccuracy and won't get his attackeraccuracy overwritten by _gameskill."
"Module: Utility"
"Example: player_cant_be_shot();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_cant_be_shot()
{
	level.player ent_flag_set( "player_zero_attacker_accuracy" );
	level.player.attackeraccuracy = 0;
	level.player.IgnoreRandomBulletDamage = true;
}

/*
=============
///ScriptDocBegin
"Name: set_player_attacker_accuracy( <val> )"
"Summary: Sets the player's attacker accuracy correctly so _gameskill won't overwrite it"
"Module: Utility"
"CallOn: A player"
"MandatoryArg: <val>: The attacker accuracy"
"Example: level.player set_player_attacker_accuracy( 0.5 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_player_attacker_accuracy( val )
{
	// sets player attackeraccuracy
	player = get_player_from_self();
	player.gs.player_attacker_accuracy = val;
	player maps\_gameskill::update_player_attacker_accuracy();
}

/*
=============
///ScriptDocBegin
"Name: array_index_by_parameters( <array> )"
"Summary: Indexes and array by its script_parameter values and returns the array"
"Module: Utility"
"MandatoryArg: <array>: The array of entities that all have script_parameters "
"Example: orgs = array_index_by_parameters( friendly_escape_orgs );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_index_by_parameters( old_array )
{
	array = [];
	foreach ( item in old_array )
	{
		array[ item.script_parameters ] = item;
	}
	return array;
}

/*
=============
///ScriptDocBegin
"Name: array_index_by_classname( <array> )"
"Summary: Indexes and array by its classname values and returns the array"
"Module: Utility"
"MandatoryArg: <array>: The array of entities that all have classnames "
"Example: orgs = array_index_by_classname( friendly_escape_orgs );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_index_by_classname( old_array )
{
	array = [];
	foreach ( item in old_array )
	{
		array[ item.classname ] = item;
	}
	return array;
}

/*
=============
///ScriptDocBegin
"Name: array_index_by_script_index( <array> )"
"Summary: Indexes and array by its script_index values and returns the array"
"Module: Utility"
"MandatoryArg: <array>: The array of entities that all have script_indexs "
"Example: orgs = array_index_by_script_index( friendly_escape_orgs );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
array_index_by_script_index( array )
{
	// sort ents by order of script_index
	newarray = [];
	foreach ( ent in array )
	{
		index = ent.script_index;
		if ( IsDefined( index ) )
		{
			AssertEx( !isdefined( newarray[ index ] ), "Multiple ents had the same script_index of " + index );

			newarray[ index ] = ent;
		}
	}

	return newarray;
}



/*
=============
///ScriptDocBegin
"Name: add_target_pivot()"
"Summary: Adds a .pivot to an entity, from the entity's .target."
"Module: Utility"
"CallOn: An entity that is going to rotate around a pivot point."
"OptionalArg: <ent>: Optional override ent"
"Example: evac_rock add_target_pivot();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_target_pivot( ent )
{
	if ( IsDefined( ent ) )
	{
		self.pivot = ent;
	}
	else
	{
		AssertEx( IsDefined( self.target ), "Tried to add pivot to an entity but it has no target." );
		self.pivot = GetEnt( self.target, "targetname" );
		AssertEx( IsDefined( self.pivot ), "Tried to add pivot but there was no pivot entity. Must be a script mover, like a script_origin not script_struct." );
	}

	self LinkTo( self.pivot );
}

/*
=============
///ScriptDocBegin
"Name: get_color_volume_from_trigger()"
"Summary: Gets the color volume from a trigger that has only one color code"
"Module: Color"
"CallOn: A color trigger"
"Example: volume = trigger get_color_volume_from_trigger();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_color_volume_from_trigger()
{
	info = self get_color_info_from_trigger();
	team = info[ "team" ];

	foreach ( code in info[ "codes" ] )
	{
		volume = level.arrays_of_colorCoded_volumes[ team ][ code ];
		if ( IsDefined( volume ) )
			return volume;
	}

	return undefined;
}

/*
=============
///ScriptDocBegin
"Name: get_color_nodes_from_trigger()"
"Summary: Gets the color nodes from a trigger that has only one color code"
"Module: Color"
"CallOn: A color trigger"
"Example: nodes = trigger get_color_nodes_from_trigger();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_color_nodes_from_trigger()
{
	info = self get_color_info_from_trigger();
	team = info[ "team" ];

	foreach ( code in info[ "codes" ] )
	{
		nodes = level.arrays_of_colorCoded_nodes[ team ][ code ];
		if ( IsDefined( nodes ) )
			return nodes;
	}

	return undefined;
}


/*
=============
///ScriptDocBegin
"Name: flashBangStop()"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"Example: actor flashBangStop();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
flashBangStop()
{
	self.flashendtime = undefined;
	self SetFlashBanged( false );
}

/*
=============
///ScriptDocBegin
"Name: getent_or_struct( param1, param2 )"
"Summary: "
"Module: Entity"
"MandatoryArg: <param1>: first param of a key/value pair, such as 'self.target'"
"MandatoryArg: <param2>: second param of a key/value pair, such as 'targetname'"
"Example: nextNode = getent_or_struct( self.target, "targetname" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
getent_or_struct( param1, param2 )
{
	ent = GetEnt( param1, param2 );
	if ( IsDefined( ent ) )
		return ent;
	return getstruct( param1, param2 );
}


grenade_earthQuake()
{
	// grenades die when they explode so we wait until the end of the frame before killing the thread.
	// not doing so would kill the thread before the fx could happen.
	self thread endOnDeath();
	self endon( "end_explode" );

	self waittill( "explode", position );

	dirt_on_screen_from_position( position );
}

endOnDeath()
{
	self waittill( "death" );
	waittillframeend;
	self notify( "end_explode" );
}

/*
=============
///ScriptDocBegin
"Name: dirt_on_screen_from_position( <position> )"
"Summary: Self explanatory"
"Module: Utility"
"MandatoryArg: <position>: origin of explosion"
"Example: dirt_on_screen_from_position( from_on_high );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
dirt_on_screen_from_position( position )
{
	PlayRumbleOnPosition( "grenade_rumble", position );
	Earthquake( 0.3, 0.5, position, 400 );

	foreach ( player in level.players )
	{
		if ( Distance( position, player.origin ) > 600 )
			continue;

		if ( player DamageConeTrace( position ) )
			player thread dirtEffect( position );
	}
}

/*
=============
///ScriptDocBegin
"Name: player_rides_shotgun_in_humvee( <right> , <left> , <up> , <down> )"
"Summary: Makes the player pop into the humvee's shotgun seat. Returns the org used to dismount the player"
"Module: Utility"
"CallOn: The humvee"
"OptionalArg: <directions> FOV limits for the player "
"Example: org = humvee player_rides_shotgun_in_humvee( 45,45,45,45 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_rides_shotgun_in_humvee( right, left, up, down )
{
	return self player_rides_in_humvee( "shotgun", level.player, right, left, up, down );
}

player_rides_in_humvee( seat, rider, right, left, up, down )
{
	if ( !isdefined( rider ) )
		rider = level.player;
	assert( isplayer( rider ) );

	rider AllowCrouch( false );
	rider AllowProne( false );
	rider DisableWeapons();

	org = spawn_tag_origin();
	org LinkTo( self, "tag_passenger", player_rides_in_humvee_offset( seat ), ( 0, 0, 0 ) );
	org.player_dismount = spawn_tag_origin();
	org.player_dismount LinkTo( self, "tag_body", player_rides_humvee_offset_dismount( seat ), ( 0, 0, 0 ) );

	if ( !isdefined( right ) )
		right = 90;
	if ( !isdefined( left ) )
		left = 90;
	if ( !isdefined( up ) )
		up = 40;
	if ( !isdefined( down ) )
		down = 40;

	rider DisableWeapons();
	rider PlayerLinkTo( org, "tag_origin", 0.8, right, left, up, down );
	rider.humvee_org = org;

	return org;
}

player_rides_in_humvee_offset( seat )
{
	switch( seat )
	{
		case "shotgun" :	return ( -5, 10, -34 );
		case "backleft" :	return ( -45, 45, -34 );
		case "backright" :	return ( -45, 5, -34 );
	}

	assertmsg( "No offset for " + seat + " was available in player_rides_in_humvee_offset()" );
}

player_rides_humvee_offset_dismount( seat )
{
	switch( seat )
	{
		case "shotgun" :	return ( -8, -90, -12.6 );
		case "backleft" :	return ( -58, 85, -12.6 );
		case "backright" :	return ( -58, -95, -12.6 );
	}

	assertmsg( "No offset for " + seat + " was available in player_rides_humvee_offset_dismount()" );
}

player_leaves_humvee( skip_offset )
{
	if ( !isdefined( skip_offset ) )
		skip_offset = false;

	// Backwards compatibility calling on the org itself rather than the player.
	org = self;
	rider = level.player;
	if ( isplayer( self ) )
	{
		rider = self;
		org = rider.humvee_org;
	}

	org Unlink();
	if ( !skip_offset )
	{
		move_time = 0.6;
		org MoveTo( org.player_dismount.origin, move_time, move_time * 0.5, move_time * 0.5 );
		wait( move_time );
	}

	rider Unlink();
	rider EnableWeapons();
	rider AllowCrouch( true );
	rider AllowProne( true );
	rider.humvee_org = undefined;

	org.player_dismount Delete();
	org Delete();
}

/*
=============
///ScriptDocBegin
"Name: dirtEffect( <position> )"
"Summary: plays a grenade dirt effect on the screen"
"Module: player"
"CallOn: player"
"MandatoryArg: <position>: the position of the event that causes the effect"
"Example: level.player dirtEffect( fx.origin );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
dirtEffect( position, attacker )
{
	sides = screen_effect_sides( position );

	foreach ( type, _ in sides )
	{
		self thread maps\_gameskill::grenade_dirt_on_screen( type );
	}
}

bloodsplateffect( position )
{
	if ( !IsDefined( self.damageAttacker ) )
	{
		return;
	}

	sides = screen_effect_sides( self.damageAttacker.origin );

	foreach ( type, _ in sides )
	{
		self thread maps\_gameskill::blood_splat_on_screen( type );
	}
}

screen_effect_sides( position )
{
	forwardVec = VectorNormalize( AnglesToForward( self.angles ) );
	rightVec = VectorNormalize( AnglesToRight( self.angles ) );
	entVec = VectorNormalize( position - self.origin );

	fDot = VectorDot( entVec, forwardVec );
	rDot = VectorDot( entVec, rightVec );

	sides = [];
	curWeapon = self GetCurrentWeapon();
	if ( fDot > 0 && fDot > 0.5 && WeaponType( curWeapon ) != "riotshield" )
	{
		sides[ "bottom" ] = true;
	}

	if ( abs( fDot ) < 0.866 )
	{
		if ( rDot > 0 )
		{
			sides[ "right" ] = true;
		}
		else
		{
			sides[ "left" ] = true;
		}
	}

	return sides;
}

/*
=============
///ScriptDocBegin
"Name: pathrandompercent_set( <value> )"
"Summary: sets self.pathrandompercent to the value"
"Module: AI"
"CallOn: An AI"
"MandatoryArg: <value>: the value of self.pathrandompercent"
"Example: level.price pathrandompercent_set( 0 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
pathrandompercent_set( value )
{
	if ( !isdefined( self.old_pathrandompercent ) )
		self.old_pathrandompercent = self.pathrandompercent;
	self.pathrandompercent = value;
}

/*
=============
///ScriptDocBegin
"Name: pathrandompercent_zero()"
"Summary: sets self.pathrandompercent to 0"
"Module: AI"
"CallOn: An AI"
"Example: level.price pathrandompercent_zero();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
pathrandompercent_zero()
{
	if ( IsDefined( self.old_pathrandompercent ) )
		return;

	self.old_pathrandompercent = self.pathrandompercent;
	self.pathrandompercent = 0;
}

/*
=============
///ScriptDocBegin
"Name: pathrandompercent_reset()"
"Summary: resets self.pathrandompercent ( see pathrandompercent_zero )"
"Module: AI"
"CallOn: An AI"
"Example: level.price pathrandompercent_reset();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
pathrandompercent_reset()
{
	Assert( IsDefined( self.old_pathrandompercent ) );

	self.pathrandompercent = self.old_pathrandompercent;
	self.old_pathrandompercent = undefined;
}

/*
=============
///ScriptDocBegin
"Name: walkdist_zero()"
"Summary: sets self.walkdist and self.old_walkDistFacingMotion to 0"
"Module: AI"
"CallOn: An AI"
"Example: level.price walkdist_zero();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
walkdist_zero()
{
	if ( IsDefined( self.old_walkDistFacingMotion ) )
		return;

	self.old_walkDist 				 = self.walkDist;
	self.old_walkDistFacingMotion 	 = self.walkDistFacingMotion;

	self.walkdist 				 = 0;
	self.walkDistFacingMotion 	 = 0;
}

/*
=============
///ScriptDocBegin
"Name: walkdist_reset()"
"Summary: resets self.walkdist and self.old_walkDistFacingMotion ( see walkdist_zero )"
"Module: AI"
"CallOn: An AI"
"Example: level.price walkdist_reset();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
walkdist_reset()
{
	Assert( IsDefined( self.old_walkDist ) );
	Assert( IsDefined( self.old_walkDistFacingMotion ) );

	self.walkdist 				 = self.old_walkDist;
	self.walkDistFacingMotion 	 = self.old_walkDistFacingMotion;

	self.old_walkDist 				 = undefined;
	self.old_walkDistFacingMotion 	 = undefined;
}

/*
=============
///ScriptDocBegin
"Name: enable_ignorerandombulletdamage_drone()"
"Summary: effectively has the same effect as .IgnoreRandomBulletDamage on AI, but for drones"
"Module: Entity"
"CallOn: An a drone"
"Example: guy enable_ignorerandombulletdamage_drone()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_ignorerandombulletdamage_drone()
{
	//threading internally so script doesn't stop here...most our enable/disable utility code doesn't stop script.
	self thread ignorerandombulletdamage_drone_proc();
}

ignorerandombulletdamage_drone_proc()
{
	AssertEx( !IsSentient( self ), "AI tried to run enable_ignorerandombulletdamage_drone" );

	self endon( "disable_ignorerandombulletdamage_drone" );
	self endon( "death" );

	//just an easy variable we can check for debugging - doesn't actually do anything in code.
	self.IgnoreRandomBulletDamage = true;
	self.fakehealth = self.health;
	self.health = 1000000;

	while ( 1 )
	{
		self waittill( "damage", damage, attacker );

		if ( !isplayer( attacker ) && IsSentient( attacker ) )
		{
			if ( IsDefined( attacker.enemy ) && attacker.enemy != self )
				continue;
		}

		self.fakehealth -= damage;

		if ( self.fakehealth <= 0 )
			break;
	}

	self Kill();
}

/*
=============
///ScriptDocBegin
"Name: hide_notsolid( <hide_notsolid> )"
"Summary: Hide an entity and make it truly notsolid via setContents"
"Module: Utility"
"CallOn: An entity"
"Example: model hide_notsolid();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
hide_notsolid()
{
	if ( !isdefined( self.oldContents ) )
	{
		self.oldContents = self SetContents( 0 );
	}

	self Hide();
}

/*
=============
///ScriptDocBegin
"Name: show_solid( <hide_notsolid> )"
"Summary: Show an entity and retrieve its prior contents."
"Module: Utility"
"CallOn: An entity"
"Example: model show_solid();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
show_solid()
{
	if ( !isai( self ) )
		self Solid();

	if ( IsDefined( self.oldContents ) )
	{
		self SetContents( self.oldContents );
	}

	self Show();
}

/*
=============
///ScriptDocBegin
"Name: set_brakes( <num> )"
"Summary: Sets the brakes on the vehicle"
"Module: Utility"
"CallOn: A vehicle"
"MandatoryArg: <num>: The brakes, 0 to 1. "
"Example: vehicle set_brakes( 0.5 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_brakes( num )
{
	self.veh_brake = num;
}


/*
=============
///ScriptDocBegin
"Name: disable_ignorerandombulletdamage_drone()"
"Summary: stops ignoring random bullet damage"
"Module: Entity"
"CallOn: An a drone"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_ignorerandombulletdamage_drone()
{
	if ( !isalive( self ) )
		return;
	if ( !isdefined( self.IgnoreRandomBulletDamage ) )
		return;

	self notify( "disable_ignorerandombulletdamage_drone" );
	self.IgnoreRandomBulletDamage = undefined;
	self.health = self.fakehealth;
}

timeOutEnt( timeOut )
{
    ent = SpawnStruct();
    ent delayThread( timeOut, ::send_notify, "timeout" );
    return ent;
}



/*
=============
///ScriptDocBegin
"Name: delayThread( <delay>, <function>, <arg1>, <arg2>, <arg3>, <arg4>, <arg5>, <arg6> )"
"Summary: Delaythread is cool! It saves you from having to write extra script for once off commands. Note you don’t have to thread it off. Delaythread is that smart!"
"Module: Utility"
"MandatoryArg: <delay> : The delay before the function occurs"
"MandatoryArg: <delay> : The function to run."
"OptionalArg: <arg1> : parameter 1 to pass to the process"
"OptionalArg: <arg2> : parameter 2 to pass to the process"
"OptionalArg: <arg3> : parameter 3 to pass to the process"
"OptionalArg: <arg4> : parameter 4 to pass to the process"
"OptionalArg: <arg5> : parameter 5 to pass to the process"
"OptionalArg: <arg6> : parameter 6 to pass to the process"
"Example: delayThread( 3, ::flag_set, "player_can_rappel" );
"SPMP: both"
///ScriptDocEnd
=============
*/
delayThread( timer, func, param1, param2, param3, param4, param5, param6 )
{
	// to thread it off
	thread delayThread_proc( func, timer, param1, param2, param3, param4, param5, param6 );
}


/*
=============
///ScriptDocBegin
"Name: enable_danger_react( <duration_seconds> )"
"Summary: if nearby teammate is shot, makes AI stop at current position, find nearby cover if available, and fight."
"Module: AI"
"CallOn: An AI"
"MandatoryArg: <duration_seconds>: how long to stop and fight"
"Example: self enable_danger_react( 10 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_danger_react( duration )
{
	duration *= 1000;

	Assert( IsAI( self ) );
	self.doDangerReact = true;
	self.dangerReactDuration = duration;
	self.neverSprintForVariation = undefined;
}


/*
=============
///ScriptDocBegin
"Name: disable_danger_react()"
"Summary: disable danger reaction. See enable_danger_react"
"Module: AI"
"CallOn: An AI"
"Example: self disable_danger_react();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_danger_react()
{
	Assert( IsAI( self ) );
	self.doDangerReact = false;
	self.neverSprintForVariation = true;
}


/*
=============
///ScriptDocBegin
"Name: set_group_advance_to_enemy_parameters( <interval> <group size> )"
"Summary: sets how often and group size for AI advancing directly toward their enemy"
"Module: AI"
"CallOn: level"
"MandatoryArg: <interval millisec>: how often"
"MandatoryArg: <group size>: how many"
"Example: self set_group_advance_to_enemy_parameters( 30000, 5 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_group_advance_to_enemy_parameters( interval, group_size )
{
	level.advanceToEnemyInterval = interval;		// how often AI will try to run directly to their enemy if the enemy is not visible
	level.advanceToEnemyGroupMax = group_size;		// group size for AI running to their enemy
}


/*
=============
///ScriptDocBegin
"Name: reset_group_advance_to_enemy_timer( <team> )"
"Summary: reset the advance-to-enemy time for a team. Useful when player advances to a new section of a level"
"Module: AI"
"CallOn: level"
"MandatoryArg: <team>: team to reset the timer for"
"Example: self reset_group_advance_to_enemy_timer( "team3" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
reset_group_advance_to_enemy_timer( team )
{
	Assert( IsDefined( level.lastAdvanceToEnemyTime[ team ] ) );
	level.lastAdvanceToEnemyTime[ team ] = GetTime();
}

/*
=============
///ScriptDocBegin
"Name: set_custom_gameskill_func( <func> )"
"Summary: Sets a custom func to run at the end of _gameskill::setskill(), so you can change difficulty settings."
"Module: Utility"
"MandatoryArg: <func>: The function to call after _gameskill::setskill()"
"Example: set_custom_gameskill_func( maps\_gameskill::solo_player_in_coop_gameskill_settings );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_custom_gameskill_func( func )
{
	Assert( IsDefined( func ) );
	level.custom_gameskill_func = func;

	// reset so it takes effect
	thread maps\_gameskill::resetSkill();
}

/*
=============
///ScriptDocBegin
"Name: clear_custom_gameskill_func()"
"Summary: Sets a custom func to run at the end of _gameskill::setskill(), so you can change difficulty settings."
"Module: Utility"
"MandatoryArg: <func>: The function to call after _gameskill::setskill()"
"Example: set_custom_gameskill_func( maps\_gameskill::solo_player_in_coop_gameskill_settings );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
clear_custom_gameskill_func()
{
	level.custom_gameskill_func = undefined;

	// reset so it takes effect
	thread maps\_gameskill::resetSkill();
}

/*
=============
///ScriptDocBegin
"Name: set_wind( <weight>, <rate>, <variance> )"
"Summary: sets the blend weight,rate on the strong wind animation for animated trees. defaults at 1 and .4."
"Module: Level"
"CallOn: The Level"
"MandatoryArg: <weight>: the weight of the animation"
"MandatoryArg: <rate>: the weight of the animation"
"OptionalArg: <variance>: How much random speed is added to the rate for each loop of the animation. "
"Example: set_wind( 100,6 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_wind( weight, rate, variance )
{
	Assert( IsDefined( weight ) );
	Assert( IsDefined( rate ) );
	maps\_animatedmodels::init_wind_if_uninitialized();
	if ( IsDefined( variance ) )
		level.wind.variance = variance;
	level.wind.rate = rate;
	level.wind.weight = weight;
	level notify( "windchange", "strong" );
}

/*
=============
///ScriptDocBegin
"Name: string_is_single_digit_integer( <str> )"
"Summary: Tests whether a string is a single digit integer. Helpful for situations like parsing strings for indexes, etc."
"Module: Utility"
"CallOn: the level"
"MandatoryArg: <str>: the string you want to test."
"Example: bIsInt = string_is_single_digit_integer( "1" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
string_is_single_digit_integer( str )
{
	if ( str.size > 1 )
	{
		return false;
	}

	arr = [];
	arr[ "0" ] = true;
	arr[ "1" ] = true;
	arr[ "2" ] = true;
	arr[ "3" ] = true;
	arr[ "4" ] = true;
	arr[ "5" ] = true;
	arr[ "6" ] = true;
	arr[ "7" ] = true;
	arr[ "8" ] = true;
	arr[ "9" ] = true;

	if ( IsDefined( arr[ str ] ) )
	{
		return true;
	}

	return false;
}


set_battlechatter_variable( team, val )
{
	// used internally
	level.battlechatter[ team ] = val;
	update_battlechatter_hud();
}

/*
=============
///ScriptDocBegin
"Name: objective_clearAdditionalPositions( <objective_number> )"
"Summary: Clears the positions for this objective"
"Module: Utility"
"MandatoryArg: <objective_number>: The index for the objective"
"Example: objective_clearAdditionalPositions( objective_index );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
objective_clearAdditionalPositions( objective_number )
{
	// can have up to 8 positions, so clear them all
	for ( i = 0; i < 8; i++ )
	{
		objective_additionalposition( objective_number, i, (0,0,0) );
	}
}


/*
=============
///ScriptDocBegin
"Name: get_minutes_and_seconds( <milliseconds> )"
"Summary: Returns how many minutes and seconds are in the milliseconds provided. Returns array with index "minutes" and index "seconds"."
"Module: Utility"
"CallOn: the level"
"MandatoryArg: <milliseconds>: Number of milliseconds to check"
"Example: time = get_minutes_and_seconds( GetTime() ); minutes = time[ "minutes" ]; seconds = time[ "seconds" ];"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
get_minutes_and_seconds( milliseconds )
{
	time = [];
	time[ "minutes" ] = 0;
	time[ "seconds" ] = Int( milliseconds / 1000 );

	while ( time[ "seconds" ] >= 60 )
	{
		time[ "minutes" ]++;
		time[ "seconds" ] -= 60;
	}
	if ( time[ "seconds" ] < 10 )
		time[ "seconds" ] = "0" + time[ "seconds" ];

	return time;
}

/*
=============
///ScriptDocBegin
"Name: player_has_weapon( <weap> )"
"Summary: Returns true if the player has the wepaon."
"Module: Utility"
"MandatoryArg: <weap>: The weapon"
"Example: if ( player_has_weapon( "riotshield" ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_has_weapon( weap )
{
	weaponList = level.player GetWeaponsListPrimaries();
	foreach ( weapon in weaponList )
	{
		if ( weapon == weap )
			return true;
	}
	return false;
}

/*
=============
///ScriptDocBegin
"Name: obj( <msg> )"
"Summary: A simple script macro for translating objective strings into indices"
"Module: Utility"
"MandatoryArg: <msg>: The string to refer to the objective"
"Example: Objective_Add( obj( "exfil" ), "current", &"ROADKILL_OBJECTIVE_REPORT", struct.origin );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
obj( msg )
{
	if ( !isdefined( level.obj_array ) )
	{
		level.obj_array = [];
	}

	if ( !isdefined( level.obj_array[ msg ] ) )
	{
		level.obj_array[ msg ] = level.obj_array.size + 1; // cause objs start at 1 not 0
	}

	return level.obj_array[ msg ];
}

/*
=============
///ScriptDocBegin
"Name: MusicLoop( <alias> , <minutes> , <seconds> )"
"Summary: Loop a music alias"
"Module: Utility"
"MandatoryArg: <alias>: The alias for the music "
"MandatoryArg: <minutes>: The number of minutes between loops "
"MandatoryArg: <seconds>: The number of seconds between loops "
"Example: thread MusicLoop( "roadkill_armored_and_combat", 8, 24 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
MusicLoop( alias, delay_between_tracks )
{
	if ( !isdefined( delay_between_tracks ) )
		delay_between_tracks = 0;

	time = musicLength( alias );

	assertex( time + delay_between_tracks > 0, "No time for delay" );

	level notify( "stop_music" );
	level endon( "stop_music" );
	for ( ;; )
	{
		MusicPlayWrapper( alias );
		wait time;
		wait delay_between_tracks;

	}
}

/*
=============
///ScriptDocBegin
"Name: player_mount_vehicle( <vehicle> )"
"Summary: Makes player drive the specified vehicle"
"Module: Player"
"CallOn: A player"
"MandatoryArg: <vehicle>: the vehicle for the player to ride"
"Example: level.player player_mount_vehicle( snowmobile );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_mount_vehicle( vehicle )
{
	assert( isplayer( self ) );
	self MountVehicle( vehicle );
	self.drivingVehicle = vehicle;
}

/*
=============
///ScriptDocBegin
"Name: player_dismount_vehicle()"
"Summary: Makes player stop driving the vehicle"
"Module: Player"
"CallOn: A player"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
player_dismount_vehicle()
{
	assert( isplayer( self ) );
	self DismountVehicle();
	self.drivingVehicle = undefined;
}


/*
=============
///ScriptDocBegin
"Name: graph_position( <v> , <min_x> , <min_y> , <max_x> , <max_y> )"
"Summary: Input graph parameters and variable, returns the result."
"Module: Utility"
"MandatoryArg: <v>: The variable to plot on the graph"
"MandatoryArg: <min_x>: The first x value on the graph"
"MandatoryArg: <min_y>: The first y value on the graph"
"MandatoryArg: <max_x>: The last x value on the graph"
"MandatoryArg: <max_y>: The last y value on the graph"
"Example: x = graph_position( val, 0, 0, 1, 1 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
graph_position( v, min_x, min_y, max_x, max_y )
{
	rise = max_y - min_y;
	run = max_x - min_x;
	assertex( run != 0, "max and min x must be different, or you havent defined any graph space." );
	slope = rise / run;

	v -= max_x;

	v = slope * v;

	v += max_y;

	return v;
}

/*
=============
///ScriptDocBegin
"Name: enable_achievement_harder_they_fall()"
"Summary: enables this AI's death to count towards the achievement THE HARDER THEY FALL"
"Module: AI"
"CallOn: An AI"
"Example: repeller enable_achievement_harder_they_fall()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
enable_achievement_harder_they_fall()
{
	self.rappeller = true;
}

/*
=============
///ScriptDocBegin
"Name: disable_achievement_harder_they_fall()"
"Summary: disables this AI's death to count towards the achievement THE HARDER THEY FALL"
"Module: AI"
"CallOn: An AI"
"Example: repeller disable_achievement_harder_they_fall()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
disable_achievement_harder_they_fall()
{
	self.rappeller = undefined;
}

enable_achievement_harder_they_fall_guy( guy )
{
	guy enable_achievement_harder_they_fall();
}

disable_achievement_harder_they_fall_guy( guy )
{
	guy disable_achievement_harder_they_fall();
}

/*
=============
///ScriptDocBegin
"Name: musicLength( <alias> )"
"Summary: Returns the length of a music alias, from main/sound/soundlength.csv, which is auto generated on convert."
"Module: Utility"
"MandatoryArg: <alias>: The music alias"
"Example: time = musicLength( "gulag_ending_music" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
musicLength( alias )
{
	time = TableLookup( "sound/soundlength.csv", 0, alias, 1 );

	if ( !isdefined( time ) || ( time == "" ) )
	{
		assertmsg( "No time stored in sound/soundlength.csv for " + alias + "." );
		return -1;
	}

	time = int( time );
	assertex( time > 0, "Music alias " + alias + " had zero time." );
	time *= 0.001;
	return time;
}

/*
=============
///ScriptDocBegin
"Name: is_command_bound( <cmd> )"
"Summary: Returns the amount of keys bound to the given command."
"Module: Utility"
"MandatoryArg: <cmd>: The command to check if it is bound, ie: "+attack", "+toggleads_throw""
"Example: if ( is_command_bound( "+toggleads_throw" ) )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_command_bound( cmd )
{
	binding = GetKeyBinding( cmd );
	return binding[ "count" ];
}


/*
=============
///ScriptDocBegin
"Name: linear_interpolate( <percentage> , <min_value> , <max_value> )"
"Summary: Calculates the linear interpolation result based on the current percentage and min and max values. Typically uses a value of 0 to 1 for the percentage, but this is not required."
"Module: Utility"
"MandatoryArg: <percentage>: Generally a value from 0 to 1. 0 will return min, 1 will return max, anything in between will return ( percentage * ( max - min ) )."
"MandatoryArg: <min_value>: Minimum value to return"
"MandatoryArg: <max_value>: Maximum value to return"
"Example: move_dist = linear_interpolate( time_passed / time_total, 0, 1000 )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
linear_interpolate( percentage, min_value, max_value )
{
	assert( isdefined( percentage ) );
	assert( isdefined( min_value ) );
	assert( isdefined( max_value ) );

	max_adjustment = max_value - min_value;
	real_adjustment = percentage * max_adjustment;
	final_value = min_value + real_adjustment;

	return final_value;
}

/*
=============
///ScriptDocBegin
"Name: is_iw4_map_sp()"
"Summary: returns true if the current level.script matches an old cod4 map name"
"Module: Level"
"CallOn: An entity"
"Example: if( is_iw4_map_sp() ) "
"SPMP: singleplayer"
"NoteLine: This is intended to be used to maintain legacy support for those old maps. Eventually it should be phased out once IW5 exists."
///ScriptDocEnd
=============
*/

is_iw4_map_sp()
{
	switch( level.script )
	{
		case "oilrig":
		case "boneyard":
		case "cliffhanger":
		case "dcburning":
		case "estate":
		case "airport":

		case "favela":
		case "gulag":
		case "trainer":
		case "favela_escape":
		case "af_chase":
		case "ending":
		case "roadkill":
		case "arcadia":
		case "af_caves":
		case "dcemp":
		case "dc_whitehouse":
		case "iw4_credits":
		case "so_escape_airport":
		case "so_download_arcadia":
		case "so_intel_boneyard":
		case "so_bridge":
		case "so_crossing_so_bridge":
		case "so_demo_so_bridge":
		case "so_sabotage_cliffhanger":
		case "so_snowrace1_cliffhanger":
		case "so_snowrace2_cliffhanger":
		case "so_rooftop_contingency":
		case "so_forest_contingency":
		case "so_defuse_favela_escape":
		case "so_takeover_estate":
		case "so_juggernauts_favela":
		case "so_killspree_favela":
		case "so_ghillies":
		case "so_hidden_so_ghillies":
		case "so_showers_gulag":
		case "co_hunted":
		case "so_ac130_co_hunted":
		case "so_chopper_invasion":
		case "so_killspree_invasion":
		case "so_defense_invasion":
		case "so_assault_oilrig":
		case "so_takeover_oilrig":
		case "so_killspree_trainer":
		
		case "so_civilrescue":

		case "contingency":
		case "invasion":
		
		case "bog_b":

			return true;
		default:
			return false;
	}
}

/*
=============
///ScriptDocBegin
"Name: define_loadout( <levelname> )"
"Summary: for use in test map situation where we want to borrow another levels loadout"
"Module: Utility"
"MandatoryArg: <levelname>: name of level loadout"
"Example: define_loadout( "london" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

define_loadout( levelname )
{
    level.loadout = levelname;
}

/*
=============
///ScriptDocBegin
"Name: template_level( <levelname> )"
"Summary: Used as a generic template override when a test level needs to borrow it's root levels name"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <levelname>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

template_level( levelname )
{
	define_loadout( levelname );
	define_introscreen( levelname );
	level.template_script = levelname;
}

/*
=============
///ScriptDocBegin
"Name: template_so_level( <levelname> )"
"Summary: Used as a generic template override for SO Mission level where it's root levels name is needed"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <levelname>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

template_so_level( levelname )
{
	// audio script expects base level name
	level.audio_stringtable_mapname = levelname;
}

/*
=============
///ScriptDocBegin
"Name: define_introscreen( <levelname> )"
"Summary: for use in test map situation where we want to borrow another levels introscreen"
"Module: Utility"
"MandatoryArg: <levelname>: name of level introscreen"
"Example: define_introscreen( "london" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

define_introscreen( levelname )
{
    level.introscreen_levelname = levelname;
}


/*
=============
///ScriptDocBegin
"Name: fx_volume_pause_noteworthy( <noteworthy> )"
"Summary: Pauses the effects in a trigger_multiple_fx_volume with the specified script_noteworthy key"
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <noteworthy>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

fx_volume_pause_noteworthy( noteworthy, dodelayed )
{
    thread fx_volume_pause_noteworthy_thread( noteworthy, dodelayed );
}

fx_volume_pause_noteworthy_thread( noteworthy, dodelayed )
{
    volume = GetEnt( noteworthy, "script_noteworthy" );
    volume notify ( "new_volume_command" );
    volume endon ( "new_volume_command" );
    wait 0.05;
    fx_volume_pause( volume, dodelayed );
    
}

fx_volume_pause( volume, dodelayed )
{
    Assert( IsDefined( volume ) );
    volume.fx_paused = true;
    if ( !IsDefined( dodelayed ) )
    	dodelayed = false;
    	
    if( dodelayed )
	    array_thread_mod_delayed( volume.fx, ::pauseeffect );
    else
	    array_thread( volume.fx, ::pauseeffect );
}

array_thread_mod_delayed( array, threadname, mod )
{
	inc = 0;
	if ( !IsDefined( mod ) )
		mod = 5;	
		
	send_array = [];
	foreach( object in array )
	{
		send_array[ send_array.size ] = object;
		inc ++;
		inc %= mod;
		if( mod == 0 )
		{
			array_thread( send_array, threadname );
			wait 0.05;
			send_array = [];
		}
	}
}


/*
=============
///ScriptDocBegin
"Name: fx_volume_restart_noteworthy( <noteworthy> )"
"Summary: used for restarting all the createFX effects contained in a trigger_multiple_fx_volume"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <noteworthy>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

fx_volume_restart_noteworthy( noteworthy )
{
    thread fx_volume_restart_noteworthy_thread( noteworthy );
}

fx_volume_restart_noteworthy_thread( noteworthy )
{
    volume = GetEnt( noteworthy, "script_noteworthy" );
    volume notify ( "new_volume_command" );
    volume endon ( "new_volume_command" );
    
    wait 0.05;
    if( ! IsDefined( volume.fx_paused ) )
        return;
    volume.fx_paused = undefined;
    
    fx_volume_restart( volume );
}

fx_volume_restart( volume )
{
    Assert( IsDefined( volume ) );
    array_thread( volume.fx, ::restartEffect );
}


flag_count_increment( msg )
{
    AssertEx( flag_exist( msg ), "Attempt to increment flag before calling flag_init: " + msg );
    if ( !IsDefined( level.flag_count ) )
        level.flag_count = [];
    if ( ! IsDefined( level.flag_count[ msg ] ) )
        level.flag_count[ msg ]   = 1;
    else
        level.flag_count[ msg ]++;
}

flag_count_decrement( msg )
{
    AssertEx( flag_exist( msg ) , "Attempt to decrement flag before calling flag_init: " + msg );
    AssertEx( IsDefined( level.flag_count ) && IsDefined( level.flag_count[ msg ] ), "Can't decrement a flag that's never been set/incremented." );
    level.flag_count[ msg ]--;
    level.flag_count[ msg ]  = int( max( 0, level.flag_count[ msg ] ) );
    if ( level.flag_count[ msg ] )
        return;
    flag_set( msg );
}

flag_count_set( msg, count )
{
    AssertEx( count, "don't support setting to Zero" );
    AssertEx( flag_exist( msg ) , "Attempt to set flag count before calling flag_init: " + msg );
    level.flag_count[ msg ]   = count;
}


/*
=============
///ScriptDocBegin
"Name: add_cleanup_ent( <ent> , <groupname> )"
"Summary: Adds an entity to be cleaned up SEEDOC:Utility\cleanup_ents"
"Module: Utility"
"CallOn: Level"
"MandatoryArg: <ent>: entity to be deleted by cleanup_ents() "
"MandatoryArg: <groupname>: name used by cleanup_ents to delete"
"Example: add_cleanup_ent( guy, "guys_on_train" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

add_cleanup_ent( ent, groupname )
{
    Assert( IsDefined( ent ) );
    Assert( IsDefined( groupname ) );
    
    if ( !IsDefined( level.cleanup_ents ) )
        level.cleanup_ents = [];
        
    if ( !IsDefined( level.cleanup_ents[ groupname ] ) )
        level.cleanup_ents[ groupname ]   = [];
    /#
    if ( array_contains( level.cleanup_ents[ groupname ] , ent ) )
        AssertMsg( "add_cleanup_ent - this ent already added" );
    #/   
    level.cleanup_ents[ groupname ][ level.cleanup_ents[ groupname ].size ]   = ent;
}

/*
=============
///ScriptDocBegin
"Name: cleanup_ents( <groupname> )"
"Summary: deletes ents specified by add_cleanup_ent"
"Module: Utility"
"CallOn: Level"
"MandatoryArg: <groupname>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

cleanup_ents( groupname ) 
{
    Assert( IsDefined(  level.cleanup_ents ) );
    Assert( IsDefined(  level.cleanup_ents[ groupname ]  ) );
    
    array = level.cleanup_ents[ groupname ];
    array = array_removeUndefined( array );
    array_delete( array );
    
    level.cleanup_ents[ groupname ] = undefined;
}

/*
=============
///ScriptDocBegin
"Name: cleanup_ents_removing_bullet_shield( <groupname> )"
"Summary: deletes ents specified by add_cleanup_ent also removes the bulletshield"
"Module: Utility"
"CallOn: Level"
"MandatoryArg: <groupname>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

cleanup_ents_removing_bullet_shield( groupname ) 
{
    if( ! IsDefined(  level.cleanup_ents ) ) 
    	return;
    if( ! IsDefined(  level.cleanup_ents[ groupname ]  ) )
    	return;
    
    array = level.cleanup_ents[ groupname ];
    array = array_removeUndefined( array );

    foreach( obj in array ) 
    {
    	if ( ! IsAI( obj ) )
    		continue;
		if ( !IsAlive( obj ) )
			continue;
		if ( ! IsDefined( obj.magic_bullet_shield ) )
			continue;
		if( !obj.magic_bullet_shield )
			continue;	
		obj stop_magic_bullet_shield();
    }

    array_delete( array );
    
    level.cleanup_ents[ groupname ] = undefined;
}

/*
=============
///ScriptDocBegin
"Name: add_trigger_function( <function> )"
"Summary: adds a function to be called when a trigger is triggered"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <function>: function to add"
"Example: scn_london_subway_truck_trans add_trigger_function( ::scn_london_subway_truck_trans );"
"SPMP: singleplayer"
"NoteLine: function is called with trigger as self and first param as the triggering entity"
///ScriptDocEnd
=============
*/

add_trigger_function( function )
{
    if( !isdefined( self.trigger_functions ) )
        self thread add_trigger_func_thread();
    self.trigger_functions[ self.trigger_functions.size ] = function;
}

/*
=============
///ScriptDocBegin
"Name: getallweapons( <getallweapons> )"
"Summary: gets all the entities containing classname 'weapon_'.. expensive"
"Module: Entity"
"CallOn: An entity"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

getallweapons()
{
    array = [];
    entities = GetEntArray();
    foreach( ent in entities )
    {
        if ( !IsDefined( ent.classname ) )
            continue;
        if ( IsSubStr( ent.classname, "weapon_" ) )
            array[array.size] = ent;
    }
    return array;
}

radio_add( dialog )
{
     level.scr_radio[dialog ] = dialog;
}



/*
=============
///ScriptDocBegin
"Name: move_with_rate( <origin> , <angles> , <moverate> )"
"Summary: move and rotate an entity to a position with a rate"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <origin>: "
"MandatoryArg: <angles>: "
"MandatoryArg: <moverate>: rate in Units Per Second"
"Example: dummy move_with_rate( tank.origin, tank.angles, 280 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

move_with_rate( origin, angles, moverate )
{
	Assert( IsDefined( origin ) );
	Assert( IsDefined( angles ) );
	Assert( IsDefined( moverate ) );
	
	self notify( "newmove" );
	self endon( "newmove" );

	if ( !isdefined( moverate ) )
		moverate = 200;

	dist = Distance( self.origin, origin );
	movetime = dist / moverate;
	movevec = VectorNormalize( origin - self.origin );

	self MoveTo( origin, movetime, 0, 0 );
	self RotateTo( angles, movetime, 0, 0 );
	wait movetime;

	if ( !isdefined( self ) )
		return;
	self.velocity = movevec * ( dist / movetime );
}

/*
=============
///ScriptDocBegin
"Name: flag_on_death( <msg> )"
"Summary: sets this flag when self dies "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <msg>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

flag_on_death( msg )
{
	level endon( msg );
	self waittill( "death" );
	flag_set( msg );
}

/*
=============
///ScriptDocBegin
"Name: enable_damagefeedback()"
"Summary: Enable damage feedback that draws a crosshair when player hits NPC."
"Module: Utility"
"Example: enable_damagefeedback();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

enable_damagefeedback()
{
	level.damagefeedback = true;
}

/*
=============
///ScriptDocBegin
"Name: disable_damagefeedback()"
"Summary: Disable damage feedback that draws a crosshair when player hits NPC."
"Module: Utility"
"Example: disable_damagefeedback();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

disable_damagefeedback()
{
	level.damagefeedback = false;
}

/*
=============
///ScriptDocBegin
"Name: is_damagefeedback_enabled()"
"Summary: Return boolean - if damage feed back is enabled or not."
"Module: Utility"
"Example: if ( is_damagefeedback_enabled() ){ //blah }"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

is_damagefeedback_enabled()
{
	return ( isdefined( level.damagefeedback ) && level.damagefeedback );
}

/*
=============
///ScriptDocBegin
"Name: add_damageFeedback()"
"Summary: Add damage feedback monitor on this entity. Call enable_damagefeedback() to enable globally"
"Module: Entity"
"CallOn: An entity"
"Example: chopper add_damagefeedback();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_damagefeedback()
{
	assert( isdefined( self ) );
	self maps\_damagefeedback::monitorDamage();
}

/*
=============
///ScriptDocBegin
"Name: remove_damagefeedback()"
"Summary: Remove damage feedback monitor on this entity."
"Module: Entity"
"CallOn: An entity"
"Example: chopper remove_damagefeedback();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
remove_damagefeedback()
{
	assert( isdefined( self ) );
	self maps\_damagefeedback::stopMonitorDamage();
}

/*
=============
///ScriptDocBegin
"Name: is_demo()"
"Summary: Determines if the level is set for demo or not
"Module: Utility"
"Example: if ( is_demo() )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
is_demo()
{
	if ( GetDvar( "e3demo" ) == "1" )
	{
		return true;
	}

	return false;
}

/*
=============
///ScriptDocBegin
"Name: deletestructarray( <value> , <key> , <delay> )"
"Summary: Deletes a array of structs ( Used for structs placed in the Level Editor )"
"Module: Utility"
"MandatoryArg: <value>: "
"MandatoryArg: <key>: "
"OptionalArg:  <delay> : delay between deleting structs. Use when you are freeing up many structs"
"Example: deletestructarray( "my_struct", "targetname" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

deletestructarray( value, key, delay )
{
	structs = getstructarray( value, key );
	deletestructarray_ref( structs, delay );
}

/*
=============
///ScriptDocBegin
"Name: deletestruct_ref( <struct> )"
"Summary: Delete a struct via reference ( Used for a struct in the Level Editor )"
"Module: Utility"
"MandatoryArg: <struct>: "
"Example: deletestruct_ref( struct )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

deletestruct_ref( struct )
{
	if ( !IsDefined( struct ) )
		return;

	value = struct.script_linkname;
	
	if ( IsDefined( value ) && 
		 IsDefined( level.struct_class_names[ "script_linkname" ] ) &&
		 IsDefined( level.struct_class_names[ "script_linkname" ][ value ] ) )
	{
		foreach( i, _struct in level.struct_class_names[ "script_linkname" ][ value ] )
			if ( IsDefined( _struct ) && struct == _struct )
				level.struct_class_names[ "script_linkname" ][ value ][ i ] = undefined;
				
		if ( level.struct_class_names[ "script_linkname" ][ value ].size == 0 )
			level.struct_class_names[ "script_linkname" ][ value ] = undefined;
	}
	
	value = struct.script_noteworthy;
	
	if ( IsDefined( value ) && 
		 IsDefined( level.struct_class_names[ "script_noteworthy" ] ) &&
		 IsDefined( level.struct_class_names[ "script_noteworthy" ][ value ] ) )
	{
		foreach( i, _struct in level.struct_class_names[ "script_noteworthy" ][ value ] )
			if ( IsDefined( _struct ) && struct == _struct )
				level.struct_class_names[ "script_noteworthy" ][ value ][ i ] = undefined;
				
		if ( level.struct_class_names[ "script_noteworthy" ][ value ].size == 0 )
			level.struct_class_names[ "script_noteworthy" ][ value ] = undefined;
	}
	
	value = struct.target;
	
	if ( IsDefined( value ) && 
		 IsDefined( level.struct_class_names[ "target" ] ) &&
		 IsDefined( level.struct_class_names[ "target" ][ value ] ) )
	{
		foreach( i, _struct in level.struct_class_names[ "target" ][ value ] )
			if ( IsDefined( _struct ) && struct == _struct )
				level.struct_class_names[ "target" ][ value ][ i ] = undefined;
				
		if ( level.struct_class_names[ "target" ][ value ].size == 0 )
			level.struct_class_names[ "target" ][ value ] = undefined;
	}
	
	value = struct.targetname;
	
	if ( IsDefined( value ) && 
		 IsDefined( level.struct_class_names[ "targetname" ] ) &&
		 IsDefined( level.struct_class_names[ "targetname" ][ value ] ) )
	{
		foreach( i, _struct in level.struct_class_names[ "targetname" ][ value ] )
			if ( IsDefined( _struct ) && struct == _struct )
				level.struct_class_names[ "targetname" ][ value ][ i ] = undefined;
				
		if ( level.struct_class_names[ "targetname" ][ value ].size == 0 )
			level.struct_class_names[ "targetname" ][ value ] = undefined;
	}
	
	// You Should Remove level.struct on level start if you use this!!
	
	if ( IsDefined( level.struct ) )
		foreach ( i, _struct in level.struct )
			if ( struct == _struct )
				level.struct[ i ] = undefined;
}

/*
=============
///ScriptDocBegin
"Name: deletestructarray_ref( <structs> , <delay> )"
"Summary: Delete an array of structs via references ( Used for a struct placed in the Level Editor )"
"Module: Utility"
"MandatoryArg: <structs>: "
"OptionalArg:  <delay> : delay between deleting structs. Use when you are freeing up many structs"
"Example: deletestructarray_ref( structs )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

deletestructarray_ref( structs, delay )
{
	if ( !IsDefined( structs ) || !IsArray( structs ) || structs.size == 0 )
		return;
		
	delay = ter_op( IsDefined( delay ), delay, 0 );
	delay = ter_op( delay > 0, delay, 0 );
	
	if ( delay > 0 )
	{
		foreach ( struct in structs )
		{
			deletestruct_ref( struct );
			wait delay;
		}
	}
	else
		foreach ( struct in structs )
			deletestruct_ref( struct );
}

/*
=============
///ScriptDocBegin
"Name: getstruct_delete( <value> , <key> )"
"Summary: Just like getstruct, but deletes the struct from global level struct list"
"Module: Utility"
"MandatoryArg: <value>: "
"MandatoryArg: <key>: "
"Example: struct = getstruct_delete( "my_struct", "targetname" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

getstruct_delete( value, key )
{
	struct = getstruct( value, key );
	deletestruct_ref( struct );
	return struct;
}

/*
=============
///ScriptDocBegin
"Name: getstructarray_delete( <value> , <key> , <delay> )"
"Summary: Just like getstructarray, but deletes the structs from the global level struct list"
"Module: Utility"
"MandatoryArg: <value>: "
"MandatoryArg: <key>: "
"OptionalArg:  <delay> : delay between deleting structs. Use when you are freeing up many structs"
"Example: structs = getstructarray_delete( "my_struct", "targetname" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

getstructarray_delete( value, key, delay )
{
	structs = getstructarray( value, key );
	deletestructarray_ref( structs, delay );
	return structs;
}

/*
=============
///ScriptDocBegin
"Name: getent_or_struct_or_node( <value> , <key> )"
"Summary: Returns a ent or struct or node or vehicle node"
"Module: Utility"
"MandatoryArg: <value>: "
"MandatoryArg: <key>: "
"Example: ent = getent_or_struct_or_node( "my_ent", "targetname" )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

getent_or_struct_or_node( value, key )
{
    Assert( IsDefined( value ) );
    Assert( IsDefined( key ) );
    
    ent = getent_or_struct( value, key );
    
    if ( !IsDefined( ent ) )
    	ent = GetNode( value, key );
    if ( !IsDefined( ent ) )
    	ent = GetVehicleNode( value, key );
    return ent;
}


/*
=============
///ScriptDocBegin
"Name: setEntityHeadIcon( <shader>, <width>, <height>, <offset_vector>, <reference_point_func> )"
"Summary: Places head icon on an entity. The head icon changes size to the observer and is using newclienthudelem(). Called on the entity."
"Module: Utility"
"MandatoryArg: <shader>: Icon shader, must be precached to be used."
"MandatoryArg: <width>: Widthof icon."
"MandatoryArg: <height>: Height of icon."
"OptionalArg: <offset_vector>: Offset vector from the origin of the entity."
"OptionalArg: <reference_point_func>: Function that returns dynamic reference vector."
"Example: AI setEntityHeadIcon( "delta_airsupport", ( 0, 0, 20 ), level.getAiEyePos_func )"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

setEntityHeadIcon( icon_shader, icon_width, icon_height, offset, reference_point_func )
{
	// self is entity
	assertex( isdefined( icon_shader ), "setEntityHeadIcon() requires icon shader passed in." );
	
	if ( isDefined( offset ) )
		self.entityHeadIconOffset = offset;
	else
		self.entityHeadIconOffset = (0,0,0);
	
	if( isDefined( reference_point_func ) )
		self.entityHeadIconReferenceFunc = reference_point_func;

	self notify( "new_head_icon" );

	headIcon = newhudelem();
	headIcon.archived = true;
	headIcon.alpha = .8;
	headIcon setShader( icon_shader, icon_width, icon_height );
	headIcon setWaypoint( false, false, false, true );
	self.entityHeadIcon = headIcon;
	self updateEntityHeadIconOrigin();
	
	self thread updateEntityHeadIcon();
	self thread destroyEntityHeadIconOnDeath();
}

/*
=============
///ScriptDocBegin
"Name: removeEntityHeadIcon()"
"Summary: Removes head icon on an entity that setEntityHeadIcon() set earlier. Called on the entity."
"Module: Utility"
"Example: AI removeEntityHeadIcon()"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
removeEntityHeadIcon()
{
	// self is entity, self.entityHeadIcon is the HudElem
	
	if ( !isdefined( self.entityHeadIcon ) )
		return;
	
	self.entityHeadIcon destroy();
}

updateEntityHeadIcon()
{
	// self is entity, self.entityHeadIcon is the HudElem
	
	self endon( "new_head_icon" );
	self endon( "death" );
	
	pos = self.origin;
	while(1)
	{
		if ( pos != self.origin ) 
		{
			self updateEntityHeadIconOrigin();
			pos = self.origin;
		}
		wait .05;
	}
}

updateEntityHeadIconOrigin()
{
	// self is entity, self.entityHeadIcon is the HudElem
	if( isDefined( self.entityHeadIconReferenceFunc ) )
	{
		entityHeadIconReference = self [[ self.entityHeadIconReferenceFunc ]]();
		
		if( isdefined( entityHeadIconReference ) )
		{	
			self.entityHeadIcon.x = self.entityHeadIconOffset[0] + entityHeadIconReference[0];
			self.entityHeadIcon.y = self.entityHeadIconOffset[1] + entityHeadIconReference[1];
			self.entityHeadIcon.z = self.entityHeadIconOffset[2] + entityHeadIconReference[2];	

			return;
		}
	}

	self.entityHeadIcon.x = self.origin[0] + self.entityHeadIconOffset[0];
	self.entityHeadIcon.y = self.origin[1] + self.entityHeadIconOffset[1];
	self.entityHeadIcon.z = self.origin[2] + self.entityHeadIconOffset[2];
}

destroyEntityHeadIconOnDeath()
{
	// self is entity, self.entityHeadIcon is the HudElem
	
	self endon( "new_head_icon" );
	self waittill( "death" );

	if( !isDefined(self.entityHeadIcon) )
		return;

	self.entityHeadIcon destroy();
}