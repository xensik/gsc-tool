scriptPrintln( channel, msg )
{
	setprintchannel( channel );
	println( msg );
	setprintchannel( "script" );
}

debugPrintln( channel, msg )
{
	setprintchannel( "script_debug" );
	println( msg );
	setprintchannel( "script" );
}

draw_debug_line( start, end, timer )
{
	for ( i = 0;i < timer * 20;i++ )
	{
		line( start, end, ( 1, 1, 0.5 ) );
		wait( 0.05 );
	}
}

waittillend( msg )
{
	self waittillmatch( msg, "end" );
}

/*
=============
///ScriptDocBegin
"Name: noself_func( <func> , <parm1> , <parm2> , <parm3> , <parm4> )"
"Summary: Runs a function from level.func, if it exists. Stand alone, doesn't run on anything. Useful for common scripts where a code function may not exist in one codebase or the other."
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <func>: String reference to level.func array."
"OptionalArg: <parm1>: "
"OptionalArg: <parm2>: "
"OptionalArg: <parm3>: "
"OptionalArg: <parm4>: "
"Example: noself_func( "setsaveddvar", "r_spotlightbrightness", maxVal );"
"SPMP: both"
///ScriptDocEnd
=============
*/
noself_func( func, parm1, parm2, parm3, parm4 )
{
	if ( !isdefined( level.func ) )
		return;
	if ( !isdefined( level.func[ func ] ) )
		return;
	
	if ( !isdefined( parm1 ) )
	{
		call [[ level.func[ func ] ]]();
		return;
	}
	
	if ( !isdefined( parm2 ) )
	{
		call [[ level.func[ func ] ]]( parm1 );
		return;
	}
	if ( !isdefined( parm3 ) )
	{
		call [[ level.func[ func ] ]]( parm1, parm2 );
		return;
	}
	if ( !isdefined( parm4 ) )
	{
		call [[ level.func[ func ] ]]( parm1, parm2, parm3 );
		return;
	}
	
	call [[ level.func[ func ] ]]( parm1, parm2, parm3, parm4 );
}

/*
=============
///ScriptDocBegin
"Name: self_func( <func> , <parm1> , <parm2> , <parm3> , <parm4> )"
"Summary: Runs a function from level.func, if it exists. Runs on whatever calls it. Useful for common scripts where a code function may not exist in one codebase or the other."
"Module: Utility"
"CallOn: An entity"
"MandatoryArg: <func>: String reference to level.func array."
"OptionalArg: <parm1>: "
"OptionalArg: <parm2>: "
"OptionalArg: <parm3>: "
"OptionalArg: <parm4>: "
"Example: level.player self_func( "some_player_function", 1, 2 );"
"SPMP: both"
///ScriptDocEnd
=============
*/
self_func( func, parm1, parm2, parm3, parm4 )
{
	if ( !isdefined( level.func[ func ] ) )
		return;
	
	if ( !isdefined( parm1 ) )
	{
		self call [[ level.func[ func ] ]]();
		return;
	}
	
	if ( !isdefined( parm2 ) )
	{
		self call [[ level.func[ func ] ]]( parm1 );
		return;
	}
	if ( !isdefined( parm3 ) )
	{
		self call [[ level.func[ func ] ]]( parm1, parm2 );
		return;
	}
	if ( !isdefined( parm4 ) )
	{
		self call [[ level.func[ func ] ]]( parm1, parm2, parm3 );
		return;
	}
	
	self call [[ level.func[ func ] ]]( parm1, parm2, parm3, parm4 );
}

/*
=============
///ScriptDocBegin
"Name: randomvector( <num> )"
"Summary: returns a random vector centered on <num>"
"Module: Vector"
"CallOn: Level"
"MandatoryArg: <num>: "
"Example: direction = randomvector( 1 )"
"SPMP: both"
///ScriptDocEnd
=============
*/
randomvector( num )
{
	return( randomfloat( num ) - num * 0.5, randomfloat( num ) - num * 0.5, randomfloat( num ) - num * 0.5 );
}

/*
=============
///ScriptDocBegin
"Name: randomvectorrange( <num_min>, <num_max> )"
"Summary: returns a random vector centered between <num_min> and <num_max>"
"Module: Vector"
"CallOn: Level"
"MandatoryArg: <num_min>: "
"MandatoryArg: <num_max>: "
"Example: direction = randomvectorrange( 5, 10 )"
"SPMP: both"
///ScriptDocEnd
=============
*/
randomvectorrange( num_min, num_max )
{
	assert( isdefined( num_min ) );
	assert( isdefined( num_max ) );

	x = randomfloatrange( num_min, num_max );
	if ( randomint( 2 ) == 0 )
		x *= -1;

	y = randomfloatrange( num_min, num_max );
	if ( randomint( 2 ) == 0 )
		y *= -1;

	z = randomfloatrange( num_min, num_max );
	if ( randomint( 2 ) == 0 )
		z *= -1;

	return( x, y, z );
}

angle_dif ( oldangle, newangle )
{
	// returns the difference between two yaws
	if ( oldangle == newangle )
		return 0;

	while ( newangle > 360 )
		newangle -= 360;

	while ( newangle < 0 )
		newangle += 360;

	while ( oldangle > 360 )
		oldangle -= 360;

	while ( oldangle < 0 )
		oldangle += 360;

	olddif = undefined;
	newdif = undefined;

	if ( newangle > 180 )
		newdif = 360 - newangle;
	else
		newdif = newangle;

	if ( oldangle > 180 )
		olddif = 360 - oldangle;
	else
		olddif = oldangle;

	outerdif = newdif + olddif;
	innerdif = 0;

	if ( newangle > oldangle )
		innerdif = newangle - oldangle;
	else
		innerdif = oldangle - newangle;

	if ( innerdif < outerdif )
		return innerdif;
	else
		return outerdif;
}


sign( x )
{
	if ( x >= 0 )
		return 1;
	return - 1;
}


track( spot_to_track )
{
	if ( isdefined( self.current_target ) )
	{
		if ( spot_to_track == self.current_target )
			return;
	}
	self.current_target = spot_to_track;
}

get_enemy_team( team )
{
	assertEx( team != "neutral", "Team must be allies or axis" );

	teams = [];
	teams[ "axis" ] = "allies";
	teams[ "allies" ] = "axis";

	return teams[ team ];
}


clear_exception( type )
{
	assert( isdefined( self.exception[ type ] ) );
	self.exception[ type ] = anim.defaultException;
}

set_exception( type, func )
{
	assert( isdefined( self.exception[ type ] ) );
	self.exception[ type ] = func;
}

set_all_exceptions( exceptionFunc )
{
	keys = getArrayKeys( self.exception );
	for ( i = 0; i < keys.size; i++ )
	{
		self.exception[ keys[ i ] ] = exceptionFunc;
	}
}

/*
=============
///ScriptDocBegin
"Name: cointoss()"
"Summary: 50/50 returns true"
"Module: Utility"
"CallOn: Level"
"Example: if(cointoss())"
"SPMP: both"
///ScriptDocEnd
=============
*/
cointoss()
{
	return randomint( 100 ) >= 50 ;
}


choose_from_weighted_array( values, weights )
{
	assert( values.size == weights.size );
	
	randomval = randomint( weights[ weights.size - 1 ] + 1 );
	
	for ( i = 0; i < weights.size; i++ )
	{
		if ( randomval <= weights[i] )
			return values[i];
	}	
}

get_cumulative_weights( weights )
{
	cumulative_weights = [];
	
	sum = 0;
	for ( i = 0; i < weights.size; i++ )
	{
		sum += weights[i];
		cumulative_weights[i] = sum;
	}
	
	return cumulative_weights;
}


waittill_string( msg, ent )
{
	if ( msg != "death" )
		self endon( "death" );

	ent endon( "die" );
	self waittill( msg );
	ent notify( "returned", msg );
}


waittill_multiple( string1, string2, string3, string4, string5 )
{
	self endon( "death" );
	ent = spawnstruct();
	ent.threads = 0;

	if ( isdefined( string1 ) )
	{
		self thread waittill_string( string1, ent );
		ent.threads++;
	}
	if ( isdefined( string2 ) )
	{
		self thread waittill_string( string2, ent );
		ent.threads++;
	}
	if ( isdefined( string3 ) )
	{
		self thread waittill_string( string3, ent );
		ent.threads++;
	}
	if ( isdefined( string4 ) )
	{
		self thread waittill_string( string4, ent );
		ent.threads++;
	}
	if ( isdefined( string5 ) )
	{
		self thread waittill_string( string5, ent );
		ent.threads++;
	}

	while ( ent.threads )
	{
		ent waittill( "returned" );
		ent.threads--;
	}

	ent notify( "die" );
}

waittill_multiple_ents( ent1, string1, ent2, string2, ent3, string3, ent4, string4 )
{
	self endon( "death" );
	ent = spawnstruct();
	ent.threads = 0;

	if ( isdefined( ent1 ) )
	{
		assert( isdefined( string1 ) );
		ent1 thread waittill_string( string1, ent );
		ent.threads++;
	}
	if ( isdefined( ent2 ) )
	{
		assert( isdefined( string2 ) );
		ent2 thread waittill_string( string2, ent );
		ent.threads++;
	}
	if ( isdefined( ent3 ) )
	{
		assert( isdefined( string3 ) );
		ent3 thread waittill_string( string3, ent );
		ent.threads++;
	}
	if ( isdefined( ent4 ) )
	{
		assert( isdefined( string4 ) );
		ent4 thread waittill_string( string4, ent );
		ent.threads++;
	}

	while ( ent.threads )
	{
		ent waittill( "returned" );
		ent.threads--;
	}

	ent notify( "die" );
}

/*
=============
///ScriptDocBegin
"Name: waittill_any_return( <string1> , <string2> , <string3> , <string4> , <string5> )"
"Summary: Waits for any of several messages then returns what it was."
"Module: Utility"
"MandatoryArg: <string1>: A string to wait on"
"MandatoryArg: <string2>: A string to wait on"
"OptionalArg: <string3>: A string to wait on"
"OptionalArg: <string4>: A string to wait on"
"OptionalArg: <string5>: A string to wait on"
"Example: msg = level.player waittill_any_return( "weapon_fired", "player_flash", "player_frag" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
waittill_any_return( string1, string2, string3, string4, string5 )
{
	if ( ( !isdefined( string1 ) || string1 != "death" ) &&
	( !isdefined( string2 ) || string2 != "death" ) &&
	( !isdefined( string3 ) || string3 != "death" ) &&
	( !isdefined( string4 ) || string4 != "death" ) &&
	( !isdefined( string5 ) || string5 != "death" ) )
		self endon( "death" );

	ent = spawnstruct();

	if ( isdefined( string1 ) )
		self thread waittill_string( string1, ent );

	if ( isdefined( string2 ) )
		self thread waittill_string( string2, ent );

	if ( isdefined( string3 ) )
		self thread waittill_string( string3, ent );

	if ( isdefined( string4 ) )
		self thread waittill_string( string4, ent );

	if ( isdefined( string5 ) )
		self thread waittill_string( string5, ent );

	ent waittill( "returned", msg );
	ent notify( "die" );
	return msg;
}

/*
=============
///ScriptDocBegin
"Name: waittill_any_timeout( <timeOut> , <string1> , <string2> , <string3> , <string4> , <string5> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
waittill_any_timeout( timeOut, string1, string2, string3, string4, string5 )
{
	if ( ( !isdefined( string1 ) || string1 != "death" ) &&
	( !isdefined( string2 ) || string2 != "death" ) &&
	( !isdefined( string3 ) || string3 != "death" ) &&
	( !isdefined( string4 ) || string4 != "death" ) &&
	( !isdefined( string5 ) || string5 != "death" ) )
		self endon( "death" );

	ent = spawnstruct();

	if ( isdefined( string1 ) )
		self thread waittill_string( string1, ent );

	if ( isdefined( string2 ) )
		self thread waittill_string( string2, ent );

	if ( isdefined( string3 ) )
		self thread waittill_string( string3, ent );

	if ( isdefined( string4 ) )
		self thread waittill_string( string4, ent );

	if ( isdefined( string5 ) )
		self thread waittill_string( string5, ent );

	ent thread _timeout( timeOut );

	ent waittill( "returned", msg );
	ent notify( "die" );
	return msg;
}


_timeout( delay )
{
	self endon( "die" );

	wait( delay );
	self notify( "returned", "timeout" );
}


/*
=============
///ScriptDocBegin
"Name: waittill_any( <string1> , <string2> , <string3> , <string4> , <string5> , <string6> , <string7> , <string8> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <string1>: a notify on which the entity should wait"
"OptionalArg: <string2> - <string8>: optional other notifies to wait for"
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
waittill_any( string1, string2, string3, string4, string5, string6, string7, string8 )
{
	assert( isdefined( string1 ) );

	if ( isdefined( string2 ) )
		self endon( string2 );

	if ( isdefined( string3 ) )
		self endon( string3 );

	if ( isdefined( string4 ) )
		self endon( string4 );

	if ( isdefined( string5 ) )
		self endon( string5 );

	if ( isdefined( string6 ) )
		self endon( string6 );
		
	if ( isdefined( string7 ) )
		self endon( string7 );
		
	if ( isdefined( string8 ) )
		self endon( string8 );

	self waittill( string1 );
}

waittill_any_ents( ent1, string1, ent2, string2, ent3, string3, ent4, string4, ent5, string5, ent6, string6, ent7, string7 )
{
	assert( isdefined( ent1 ) );
	assert( isdefined( string1 ) );

	if ( ( isdefined( ent2 ) ) && ( isdefined( string2 ) ) )
		ent2 endon( string2 );

	if ( ( isdefined( ent3 ) ) && ( isdefined( string3 ) ) )
		ent3 endon( string3 );

	if ( ( isdefined( ent4 ) ) && ( isdefined( string4 ) ) )
		ent4 endon( string4 );

	if ( ( isdefined( ent5 ) ) && ( isdefined( string5 ) ) )
		ent5 endon( string5 );

	if ( ( isdefined( ent6 ) ) && ( isdefined( string6 ) ) )
		ent6 endon( string6 );

	if ( ( isdefined( ent7 ) ) && ( isdefined( string7 ) ) )
		ent7 endon( string7 );

	ent1 waittill( string1 );
}

/*
=============
///ScriptDocBegin
"Name: isFlashed()"
"Summary: Returns true if the player or an AI is flashed"
"Module: Utility"
"CallOn: An AI"
"Example: flashed = level.price isflashed();"
"SPMP: both"
///ScriptDocEnd
=============
*/
isFlashed()
{
	if ( !isdefined( self.flashEndTime ) )
		return false;

	return gettime() < self.flashEndTime;
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flag_exist( <flagname> )"
"Summary: checks to see if a flag exists"
"Module: Flag"
"MandatoryArg: <flagname> : name of the flag to check"
"Example: if( flag_exist( "hq_cleared" ) );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */
flag_exist( message )
{
	return isdefined( level.flag[ message ] );
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flag( <flagname>, <entity> )"
"Summary: Checks if the flag is set. Returns true or false."
"Module: Flag"
"MandatoryArg: <flagname> : name of the flag to check"
"OptionalArg: <entity> : You can check the flag settings for a specific entity by passing the entity"
"Example: if ( flag( "hq_cleared" ) )"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 

flag( message )
{
	assertEx( isdefined( message ), "Tried to check flag but the flag was not defined." );
	assertEx( isdefined( level.flag[ message ] ), "Tried to check flag " + message + " but the flag was not initialized." );

	return level.flag[ message ];
}


init_flags()
{
	level.flag = [];
	level.flags_lock = [];
	level.generic_index = 0;
	
	if ( !isdefined( level.sp_stat_tracking_func ) )
		level.sp_stat_tracking_func = ::empty_init_func;
		
	level.flag_struct = spawnstruct();
	level.flag_struct assign_unique_id();		
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flag_init( <flagname> )"
"Summary: Initialize a flag to be used. All flags must be initialized before using flag_set or flag_wait"
"Module: Flag"
"CallOn: "
"MandatoryArg: <flagname> : name of the flag to create"
"Example: flag_init( "hq_cleared" );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
flag_init( message )
{
	if ( !isDefined( level.flag ) )
	{
		init_flags();
	}

	/#
	if ( isdefined( level.first_frame ) && level.first_frame == -1 )
		assertEx( !isDefined( level.flag[ message ] ), "Attempt to reinitialize existing message: " + message );
	#/

	level.flag[ message ] = false;
/#
	// lock check
#/
	if ( !isdefined( level.trigger_flags ) )
	{
		init_trigger_flags();
		level.trigger_flags[ message ] = [];
	}
	else
	if ( !isdefined( level.trigger_flags[ message ] ) )
	{
		level.trigger_flags[ message ] = [];
	}

	if ( issuffix( message, "aa_" ) )
	{
		thread [[ level.sp_stat_tracking_func ]]( message );
	}
}

empty_init_func( empty )
{
}

issuffix( msg, suffix )
{
	if ( suffix.size > msg.size )
		return false;

	for ( i = 0; i < suffix.size; i++ )
	{
		if ( msg[ i ] != suffix[ i ] )
			return false;
	}
	return true;
}
 /* 
 ============= 
///ScriptDocBegin
"Name: flag_set( <flagname>, <setter> )"
"Summary: Sets the specified flag, all scripts using flag_wait will now continue."
"Module: Flag"
"MandatoryArg: <flagname> : name of the flag to set"
"OptionalArg: <setter> : Pass an entity with the flag_set"
"Example: flag_set( "hq_broiled" );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
flag_set( message, setter )
{
/#
	assertEx( isDefined( level.flag[ message ] ), "Attempt to set a flag before calling flag_init: " + message );
	//lock check
#/

	level.flag[ message ] = true;
	set_trigger_flag_permissions( message );
	if ( isdefined( setter ) )
	{
		level notify( message, setter );// notify needs to be very last thing called
	}
	else
	{
		level notify( message );// notify needs to be very last thing called
	}
}

assign_unique_id()
{
	self.unique_id = "generic" + level.generic_index;
	level.generic_index++;
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flag_wait( <flagname>, <entity> )"
"Summary: Waits until the specified flag is set."
"Module: Flag"
"MandatoryArg: <flagname> : name of the flag to wait on"
"OptionalArg: <entity> : You can wait until a flag is set for a specific entity"
"Example: flag_wait( "hq_cleared" );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
flag_wait( msg, entity )
{
	other = undefined;
	while ( !flag( msg ) )
	{
		other = undefined;
		level waittill( msg, other );

		// if we're waiting for the flag on a specific entity then we have to check
		// to see if the flag is set on that specific entity
		if ( isdefined( entity ) && flag( msg, entity ) )
			break;
	}
	if ( isdefined( other ) )
		return other;
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flag_clear( <flagname>, <entity> )"
"Summary: Clears the specified flag."
"Module: Flag"
"MandatoryArg: <flagname> : name of the flag to clear"
"Example: flag_clear( "hq_cleared" );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
flag_clear( message )
{
/#
	assertEx( isDefined( level.flag[ message ] ), "Attempt to set a flag before calling flag_init: " + message );
	// lock implementation tbd
#/
	//do this check so we don't unneccessarily send a notify
	if ( !flag( message ) )
		return;

	level.flag[ message ] = false;

	set_trigger_flag_permissions( message );
	level notify( message );// the notify needs to be the very last thing called in this function
}

/*
=============
///ScriptDocBegin
"Name: flag_waitopen( <flagname> )"
"Summary: Waits for the flag to open"
"Module: Flag"
"MandatoryArg: <flagname>: The flag"
"Example: flag_waitopen( "get_me_bagels" );"
"SPMP: both"
///ScriptDocEnd
=============
*/

flag_waitopen( msg )
{
	while ( flag( msg ) )
		level waittill( msg );
}

/*
=============
///ScriptDocBegin
"Name: waittill_either( <msg1> , <msg2> )"
"Summary: Waits until either message, on self"
"Module: Utility"
"CallOn: An entity or the level"
"MandatoryArg: <msg1>: First msg to wait on"
"MandatoryArg: <msg2>: Second msg to wait on"
"Example: level waittill_either( "yo", "no" );"
"SPMP: both"
///ScriptDocEnd
=============
*/
waittill_either( msg1, msg2 )
{
	self endon( msg1 );
	self waittill( msg2 );
}

/* 
 ============= 
///ScriptDocBegin
"Name: array_thread( <entities> , <process> , <var1> , <var2> , <var3> )"
"Summary: Threads the < process > function on every entity in the < entities > array. The entity will become "self" in the specified function."
"Module: Array"
"CallOn: "
"MandatoryArg: <entities> : array of entities to thread the process"
"MandatoryArg: <process> : pointer to a script function"
"OptionalArg: <var1> : parameter 1 to pass to the process"
"OptionalArg: <var2> : parameter 2 to pass to the process"
"OptionalArg: <var3> : parameter 3 to pass to the process"
"Example: array_thread( array_of_guys, ::set_ignoreme, false );"
"SPMP: both"
///ScriptDocEnd
 ============= 
*/ 
array_thread( entities, process, var1, var2, var3, var4, var5, var6, var7, var8, var9 )
{
	if ( !isdefined( var1 ) )
	{
		foreach ( ent in entities )
			ent thread [[ process ]]();
		return;
	}
	
	if ( !isdefined( var2 ) )
	{
		foreach ( ent in entities )
			ent thread [[ process ]]( var1 );
		return;
	}
	
	if ( !isdefined( var3 ) )
	{
		foreach ( ent in entities )
			ent thread [[ process ]]( var1, var2 );
		return;
	}
	
	if ( !isdefined( var4 ) )
	{
		foreach ( ent in entities )
			ent thread [[ process ]]( var1, var2, var3 );
		return;
	}
	
	if ( !isdefined( var5 ) )
	{
		foreach ( ent in entities )
			ent thread [[ process ]]( var1, var2, var3, var4 );
		return;
	}
	
	if ( !isdefined( var6 ) )
	{
		foreach ( ent in entities )
			ent thread [[ process ]]( var1, var2, var3, var4, var5 );
		return;
	}
	
	if ( !isdefined( var7 ) )
	{
		foreach ( ent in entities )
			ent thread [[ process ]]( var1, var2, var3, var4, var5, var6 );
		return;
	}
	
	if ( !isdefined( var8 ) )
	{
		foreach ( ent in entities )
			ent thread [[ process ]]( var1, var2, var3, var4, var5, var6, var7 );
		return;
	}
	
	if ( !isdefined( var9 ) )
	{
		foreach ( ent in entities )
			ent thread [[ process ]]( var1, var2, var3, var4, var5, var6, var7, var8 );
		return;
	}
	
	foreach ( ent in entities )
		ent thread [[ process ]]( var1, var2, var3, var4, var5, var6, var7, var8, var9 );
	return;
}

/* 
 ============= 
///ScriptDocBegin
"Name: array_call( <entities> , <process> , <var1> , <var2> , <var3> )"
"Summary: Runs the code < process > function on every entity in the < entities > array. The entity will become "self" in the specified function."
"Module: Array"
"CallOn: "
"MandatoryArg: <entities> : array of entities to thread the process"
"MandatoryArg: <process> : pointer to a code function"
"OptionalArg: <var1> : parameter 1 to pass to the process"
"OptionalArg: <var2> : parameter 2 to pass to the process"
"OptionalArg: <var3> : parameter 3 to pass to the process"
"Example: array_call( array_of_guys, ::set_ignoreme, false );"
"SPMP: both"
///ScriptDocEnd
 ============= 
*/ 
array_call( entities, process, var1, var2, var3 )
{
	if ( isdefined( var3 ) )
	{
		foreach ( ent in entities )
			ent call [[ process ]]( var1, var2, var3 );

		return;
	}

	if ( isdefined( var2 ) )
	{
		foreach ( ent in entities )
			ent call [[ process ]]( var1, var2 );

		return;
	}

	if ( isdefined( var1 ) )
	{
		foreach ( ent in entities )
			ent call [[ process ]]( var1 );

		return;
	}

	foreach ( ent in entities )
		ent call [[ process ]]();
}

/*
=============
///ScriptDocBegin
"Name: array_thread4( <entities> , <process> , <var1> , <var2> , <var3> , <var4> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
array_thread4( entities, process, var1, var2, var3, var4 )
{
	array_thread( entities, process, var1, var2, var3, var4 );
}

/*
=============
///ScriptDocBegin
"Name: array_thread5( <entities> , <process> , <var1> , <var2> , <var3> , <var4> , <var5> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
array_thread5( entities, process, var1, var2, var3, var4, var5 )
{
	array_thread( entities, process, var1, var2, var3, var4, var5 );
}

/* 
 ============= 
///ScriptDocBegin
"Name: trigger_on( <name>, <type> )"
"Summary: Turns a trigger on. This only needs to be called if it was previously turned off"
"Module: Trigger"
"CallOn: A trigger"
"OptionalArg: <name> : the name corrisponding to a targetname or script_noteworthy to grab the trigger internally"
"OptionalArg: <type> : the type( targetname, or script_noteworthy ) corrisponding to a name to grab the trigger internally"
"Example: trigger trigger_on(); -or- trigger_on( "base_trigger", "targetname" )"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
trigger_on( name, type )
{
	if ( isdefined( name ) && isdefined( type ) )
	{
		ents = getentarray( name, type );
		array_thread( ents, ::trigger_on_proc );
	}
	else
		self trigger_on_proc();
}

trigger_on_proc()
{
	if ( isDefined( self.realOrigin ) )
		self.origin = self.realOrigin;
	self.trigger_off = undefined;
}


 /* 
 ============= 
///ScriptDocBegin
"Name: trigger_off( <name>, <type> )"
"Summary: Turns a trigger off so it can no longer be triggered."
"Module: Trigger"
"CallOn: A trigger"
"OptionalArg: <name> : the name corrisponding to a targetname or script_noteworthy to grab the trigger internally"
"OptionalArg: <type> : the type( targetname, or script_noteworthy ) corrisponding to a name to grab the trigger internally"
"Example: trigger trigger_off();"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */
trigger_off( name, type )
{
	if ( isdefined( name ) && isdefined( type ) )
	{
		ents = getentarray( name, type );
		array_thread( ents, ::trigger_off_proc );
	}
	else
		self trigger_off_proc();
}

trigger_off_proc()
{
	if ( !isDefined( self.realOrigin ) )
		self.realOrigin = self.origin;

	if ( self.origin == self.realorigin )
		self.origin += ( 0, 0, -10000 );
	self.trigger_off = true;
}

set_trigger_flag_permissions( msg )
{
	// turns triggers on or off depending on if they have the proper flags set, based on their shift-g menu settings

	// this can be init before _load has run, thanks to AI.
	if ( !isdefined( level.trigger_flags ) )
		return;

	// cheaper to do the upkeep at this time rather than with endons and waittills on the individual triggers	
	level.trigger_flags[ msg ] = array_removeUndefined( level.trigger_flags[ msg ] );
	array_thread( level.trigger_flags[ msg ], ::update_trigger_based_on_flags );
}

update_trigger_based_on_flags()
{
	true_on = true;
	if ( isdefined( self.script_flag_true ) )
	{
		true_on = false;
		tokens = create_flags_and_return_tokens( self.script_flag_true );

		// stay off unless all the flags are false
		foreach ( token in tokens )
		{
			if ( flag( token ) )
			{
				true_on = true;
				break;
			}
		}
	}

	false_on = true;
	if ( isdefined( self.script_flag_false ) )
	{
		tokens = create_flags_and_return_tokens( self.script_flag_false );

		// stay off unless all the flags are false
		foreach ( token in tokens )
		{
			if ( flag( token ) )
			{
				false_on = false;
				break;
			}
		}
	}

	[[ level.trigger_func[ true_on && false_on ] ]]();
}

create_flags_and_return_tokens( flags )
{
	tokens = strtok( flags, " " );

	// create the flag if level script does not
	for ( i = 0; i < tokens.size; i++ )
	{
		if ( !isdefined( level.flag[ tokens[ i ] ] ) )
		{
			flag_init( tokens[ i ] );
		}
	}

	return tokens;
}

init_trigger_flags()
{
	level.trigger_flags = [];
	level.trigger_func[ true ] = ::trigger_on;
	level.trigger_func[ false ] = ::trigger_off;
}

/*
=============
///ScriptDocBegin
"Name: getstruct( <name> , <type> )"
"Summary: get a struct by target, targetname,script_noteworthy, or script_linkname types, must be called after maps\_load::main();"
"Module: Struct"
"CallOn: Level"
"MandatoryArg: <name>: name of key"
"MandatoryArg: <type>: key type"
"Example: position = getstruct("waypoint1","targetname");
"SPMP: both"
///ScriptDocEnd
=============
*/

getstruct( name, type )
{
	assertex( isdefined( name ) && isdefined( type ), "Did not fill in name and type" );
	assertEx( isdefined( level.struct_class_names ), "Tried to getstruct before the structs were init" );

	array = level.struct_class_names[ type ][ name ];
	if ( !isdefined( array ) )
	{
		return undefined;
	}

	if ( array.size > 1 )
	{
		assertMsg( "getstruct used for more than one struct of type " + type + " called " + name + "." );
		return undefined;
	}
	return array[ 0 ];
}

 /* 
 ============= 
///ScriptDocBegin
"Name: getstructarray( <name> , <type )"
"Summary: gets an array of script_structs"
"Module: Array"
"CallOn: An entity"
"MandatoryArg: <name> : "
"MandatoryArg: <type> : "
"Example: fxemitters = getstructarray( "streetlights", "targetname" )"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 

getstructarray( name, type )
{
	assertEx( isdefined( level.struct_class_names ), "Tried to getstruct before the structs were init" );

	array = level.struct_class_names[ type ][ name ];
	if ( !isdefined( array ) )
		return [];
	return array;
}

struct_class_init()
{
	assertEx( !isdefined( level.struct_class_names ), "level.struct_class_names is being initialized in the wrong place! It shouldn't be initialized yet." );

	level.struct_class_names = [];
	level.struct_class_names[ "target" ] = [];
	level.struct_class_names[ "targetname" ] = [];
	level.struct_class_names[ "script_noteworthy" ] = [];
	level.struct_class_names[ "script_linkname" ] = [];

	foreach ( struct in level.struct )
	{
		if ( isdefined( struct.targetname ) )
		{
			if ( !isdefined( level.struct_class_names[ "targetname" ][ struct.targetname ] ) )
				level.struct_class_names[ "targetname" ][ struct.targetname ] = [];

			size = level.struct_class_names[ "targetname" ][ struct.targetname ].size;
			level.struct_class_names[ "targetname" ][ struct.targetname ][ size ] = struct;
		}
		if ( isdefined( struct.target ) )
		{
			if ( !isdefined( level.struct_class_names[ "target" ][ struct.target ] ) )
				level.struct_class_names[ "target" ][ struct.target ] = [];

			size = level.struct_class_names[ "target" ][ struct.target ].size;
			level.struct_class_names[ "target" ][ struct.target ][ size ] = struct;
		}
		if ( isdefined( struct.script_noteworthy ) )
		{
			if ( !isdefined( level.struct_class_names[ "script_noteworthy" ][ struct.script_noteworthy ] ) )
				level.struct_class_names[ "script_noteworthy" ][ struct.script_noteworthy ] = [];

			size = level.struct_class_names[ "script_noteworthy" ][ struct.script_noteworthy ].size;
			level.struct_class_names[ "script_noteworthy" ][ struct.script_noteworthy ][ size ] = struct;
		}
		if ( isdefined( struct.script_linkname ) )
		{
			assertex( !isdefined( level.struct_class_names[ "script_linkname" ][ struct.script_linkname ] ), "Two structs have the same linkname" );
			level.struct_class_names[ "script_linkname" ][ struct.script_linkname ][ 0 ] = struct;
		}
	}
}

fileprint_start( file )
{
	/#
	filename = file;
	level.fileprint = 1;
	level.fileprintlinecount = 0;
	level.fileprint_filename = filename;
	#/
}

 /* 
 ============= 
///ScriptDocBegin
"Name: fileprint_map_start( <filename> )"
"Summary: starts map export with the file trees\cod3\cod3\map_source\xenon_export\ < filename > .map adds header / worldspawn entity to the map.  Use this if you want to start a .map export."
"Module: Fileprint"
"CallOn: Level"
"MandatoryArg: <param1> : "
"OptionalArg: <param2> : "
"Example: fileprint_map_start( filename );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 

fileprint_map_start()
{
	/#
	// for the entity count
	level.fileprint_mapentcount = 0;
	fileprint_map_header( true );
	#/

}

fileprint_map_header( bInclude_blank_worldspawn )
{
	if ( !isdefined( bInclude_blank_worldspawn ) )
		bInclude_blank_worldspawn = false;

	/#
	fileprint_launcher( "iwmap 6" );
	fileprint_launcher( "\"000_Global\" flags  active" );
	fileprint_launcher( "\"The Map\" flags" );

	if ( !bInclude_blank_worldspawn )
		return;

	 fileprint_map_entity_start();
	 fileprint_map_keypairprint( "classname", "worldspawn" );
	 fileprint_map_entity_end();

	#/
}

 /* 
 ============= 
///ScriptDocBegin
"Name: fileprint_map_keypairprint( <key1> , <key2> )"
"Summary: prints a pair of keys to the current open map( by fileprint_map_start() )"
"Module: Fileprint"
"CallOn: Level"
"MandatoryArg: <key1> : "
"MandatoryArg: <key2> : "
"Example: fileprint_map_keypairprint( "classname", "script_model" );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 

fileprint_map_keypairprint( key1, key2 )
{
	/#
	fileprint_launcher( "\"" + key1 + "\" \"" + key2 + "\"" );
	#/
}

 /* 
 ============= 
///ScriptDocBegin
"Name: fileprint_map_entity_start()"
"Summary: prints entity number and opening bracket to currently opened file"
"Module: Fileprint"
"CallOn: Level"
"Example: fileprint_map_entity_start();"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 

fileprint_map_entity_start()
{
	/#
	assert( isdefined( level.fileprint_mapentcount ), "need to start a map with fileprint_map_start() first" );
	assert( !isdefined( level.fileprint_entitystart ) );
	level.fileprint_entitystart = true;
	fileprint_launcher(  "entity " + level.fileprint_mapentcount );
	fileprint_launcher( "{" );
	level.fileprint_mapentcount++;
	#/
}

 /* 
 ============= 
///ScriptDocBegin
"Name: fileprint_map_entity_end()"
"Summary: close brackets an entity, required for the next entity to begin"
"Module: Fileprint"
"CallOn: Level"
"Example: fileprint_map_entity_end();"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 

fileprint_map_entity_end()
{
	/#
	fileprint_launcher( "}" );
	level.fileprint_entitystart = undefined;
	#/
}


 /* 
 ============= 
///ScriptDocBegin
"Name: fileprint_radiant_vec( <vector> )"
"Summary: this converts a vector to a .map file readable format"
"Module: Fileprint"
"CallOn: An entity"
"MandatoryArg: <vector> : "
"Example: origin_string = fileprint_radiant_vec( vehicle.angles )"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 

fileprint_radiant_vec( vector )
{
	/#
		string = "" + vector[ 0 ] + " " + vector[ 1 ] + " " + vector[ 2 ] + "";
		return string;
	#/
}

 /* 
 ============= 
///ScriptDocBegin
"Name: array_remove( <ents> , <remover> )"
"Summary: Returns < ents > array minus < remover > "
"Module: Array"
"CallOn: "
"MandatoryArg: <ents> : array to remove < remover > from"
"MandatoryArg: <remover> : entity to remove from the array"
"Example: ents = array_remove( ents, guy );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
array_remove( ents, remover )
{
	newents = [];
	foreach( ent in ents )
	{
		if ( ent != remover )
			newents[ newents.size ] = ent;
	}

	return newents;
}

/*
=============
///ScriptDocBegin
"Name: array_remove_array( <ents> , <remover_array> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
array_remove_array( ents, remover_array )
{
	foreach( remover in remover_array )
		ents = array_remove( ents, remover );	
	
	return ents;
}

 /* 
 ============= 
///ScriptDocBegin
"Name: array_removeUndefined( <array> )"
"Summary: Returns a new array of < array > minus the undefined indicies"
"Module: Array"
"CallOn: "
"MandatoryArg: <array> : The array to search for undefined indicies in."
"Example: ents = array_removeUndefined( ents );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
array_removeUndefined( array )
{
	newArray = [];
	foreach ( i, item in array )
	{
		if ( !IsDefined( item ) )
			continue;
		newArray[ newArray.size ] = item;
	}
	return newArray;
}

 /* 
 ============= 
///ScriptDocBegin
"Name: array_levelthread( <entities> , <process> , <var1> , <var2> , <var3> )"
"Summary: Threads the < process > function for every entity in the < entities > array. The level calls the function and each entity of the array is passed as the first parameter to the process."
"Module: Array"
"CallOn: "
"MandatoryArg: <entities> : array of entities to thread the process"
"MandatoryArg: <process> : pointer to a script function"
"OptionalArg: <var1> : parameter 1 to pass to the process"
"OptionalArg: <var2> : parameter 2 to pass to the process"
"OptionalArg: <var3> : parameter 3 to pass to the process"
"Example: array_levelthread( getentarray( "palm", "targetname" ), ::palmTrees );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
array_levelthread( array, process, var1, var2, var3 )
{
	if ( isdefined( var3 ) )
	{
		foreach ( ent in array )
			thread [[ process ]]( ent, var1, var2, var3 );

		return;
	}

	if ( isdefined( var2 ) )
	{
		foreach ( ent in array )
			thread [[ process ]]( ent, var1, var2 );

		return;
	}

	if ( isdefined( var1 ) )
	{
		foreach ( ent in array )
			thread [[ process ]]( ent, var1 );

		return;
	}

	foreach ( ent in array )
		thread [[ process ]]( ent );
}

 /* 
 ============= 
///ScriptDocBegin
"Name: array_levelcall( <entities> , <process> , <var1> , <var2> , <var3> )"
"Summary: Calls the < process > function for every entity in the < entities > array. The level calls the function and each entity of the array is passed as the first parameter to the process."
"Module: Array"
"CallOn: "
"MandatoryArg: <entities> : array of entities to thread the process"
"MandatoryArg: <process> : pointer to a code function"
"OptionalArg: <var1> : parameter 1 to pass to the process"
"OptionalArg: <var2> : parameter 2 to pass to the process"
"OptionalArg: <var3> : parameter 3 to pass to the process"
"Example: array_levelthread( array_of_trees, ::palmTrees );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
array_levelcall( array, process, var1, var2, var3 )
{
	if ( isdefined( var3 ) )
	{
		foreach ( ent in array )
			call [[ process ]]( ent, var1, var2, var3 );

		return;
	}

	if ( isdefined( var2 ) )
	{
		foreach ( ent in array )
			call [[ process ]]( ent, var1, var2 );

		return;
	}

	if ( isdefined( var1 ) )
	{
		foreach ( ent in array )
			call [[ process ]]( ent, var1 );

		return;
	}

	foreach ( ent in array )
		call [[ process ]]( ent );
}

/* 
============= 
///ScriptDocBegin
"Name: add_to_array( <array> , <ent> )"
"Summary: Adds < ent > to < array > and returns the new array."
"Module: Array"
"CallOn: "
"MandatoryArg: <array> : The array to add < ent > to."
"MandatoryArg: <ent> : The entity to be added."
"Example: nodes = add_to_array( nodes, new_node );"
"SPMP: both"
///ScriptDocEnd
============= 
*/ 
add_to_array( array, ent )
{
	if ( !isdefined( ent ) )
		return array;

	if ( !isdefined( array ) )
		array[ 0 ] = ent;
	else
		array[ array.size ] = ent;

	return array;
}



/*
=============
///ScriptDocBegin
"Name: flag_assert( <msg> )"
"Summary: Asserts that a flag is clear. Useful for proving an assumption of a flag's state"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <msg>: flag name"
"Example: flag_assert( "fairground_begins" );"
"SPMP: both"
///ScriptDocEnd
=============
*/
flag_assert( msg )
{
	assertEx( !flag( msg ), "Flag " + msg + " set too soon!" );
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flag_wait_either( <flagname1> , <flagname2> )"
"Summary: Waits until either of the the specified flags are set."
"Module: Flag"
"CallOn: "
"MandatoryArg: <flagname1> : name of one flag to wait on"
"MandatoryArg: <flagname2> : name of the other flag to wait on"
"Example: flag_wait( "hq_cleared", "hq_destroyed" );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
flag_wait_either( flag1, flag2 )
{
	for ( ;; )
	{
		if ( flag( flag1 ) )
			return;
		if ( flag( flag2 ) )
			return;

		level waittill_either( flag1, flag2 );
	}
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flag_wait_either_return( <flagname1> , <flagname2> )"
"Summary: Waits until either of the the specified flags are set, and returns the first one it found."
"Module: Flag"
"CallOn: "
"MandatoryArg: <flagname1> : name of one flag to wait on"
"MandatoryArg: <flagname2> : name of the other flag to wait on"
"Example: flag_wait( "hq_cleared", "hq_destroyed" );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
flag_wait_either_return( flag1, flag2 )
{
	for ( ;; )
	{
		if ( flag( flag1 ) )
			return flag1;
		if ( flag( flag2 ) )
			return flag2;

		msg = level waittill_any_return( flag1, flag2 );
		return msg;
	}
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flag_wait_any( <flagname1> , <flagname2>, <flagname3> , <flagname4> , <flagname5> , <flagname6> )"
"Summary: Waits until any of the the specified flags are set."
"Module: Flag"
"CallOn: "
"MandatoryArg: <flagname1> : name of a flag to wait on"
"MandatoryArg: <flagname2> : name of a flag to wait on"
"OptionalArg: <flagname3> : name of a flag to wait on"
"OptionalArg: <flagname4> : name of a flag to wait on"
"Example: flag_wait_any( "hq_cleared", "hq_destroyed", "hq_overrun", "hq_skipped" );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */
flag_wait_any( flag1, flag2, flag3, flag4, flag5, flag6 )
{
	array = [];
	if ( isdefined( flag6 ) )
	{
		array[ array.size ] = flag1;
		array[ array.size ] = flag2;
		array[ array.size ] = flag3;
		array[ array.size ] = flag4;
		array[ array.size ] = flag5;
		array[ array.size ] = flag6;
	}
	else if ( isdefined( flag5 ) )
	{
		array[ array.size ] = flag1;
		array[ array.size ] = flag2;
		array[ array.size ] = flag3;
		array[ array.size ] = flag4;
		array[ array.size ] = flag5;
	}
	else if ( isdefined( flag4 ) )
	{
		array[ array.size ] = flag1;
		array[ array.size ] = flag2;
		array[ array.size ] = flag3;
		array[ array.size ] = flag4;
	}
	else if ( isdefined( flag3 ) )
	{
		array[ array.size ] = flag1;
		array[ array.size ] = flag2;
		array[ array.size ] = flag3;
	}
	else if ( isdefined( flag2 ) )
	{
		flag_wait_either( flag1, flag2 );
		return;
	}
	else
	{
		assertmsg( "flag_wait_any() needs at least 2 flags passed to it" );
		return;
	}

	for ( ;; )
	{
		for ( i = 0; i < array.size; i++ )
		{
			if ( flag( array[ i ] ) )
				return;
		}

		level waittill_any( flag1, flag2, flag3, flag4, flag5, flag6 );
	}
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flag_wait_any_return( <flagname1> , <flagname2>, <flagname3> , <flagname4> , <flagname5> )"
"Summary: Waits until any of the the specified flags are set, and returns the first set flag that was found."
"Module: Flag"
"CallOn: "
"MandatoryArg: <flagname1> : name of a flag to wait on"
"MandatoryArg: <flagname2> : name of a flag to wait on"
"OptionalArg: <flagname3> : name of a flag to wait on"
"OptionalArg: <flagname4> : name of a flag to wait on"
"OptionalArg: <flagname5> : name of a flag to wait on"
"Example: returned = flag_wait_any_return( "hq_cleared", "hq_destroyed", "hq_overrun", "hq_skipped" );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */
flag_wait_any_return( flag1, flag2, flag3, flag4, flag5 )
{
	array = [];
	
	if ( isdefined( flag5 ) )
	{
		array[ array.size ] = flag1;
		array[ array.size ] = flag2;
		array[ array.size ] = flag3;
		array[ array.size ] = flag4;
		array[ array.size ] = flag5;
	}
	else if ( isdefined( flag4 ) )
	{
		array[ array.size ] = flag1;
		array[ array.size ] = flag2;
		array[ array.size ] = flag3;
		array[ array.size ] = flag4;
	}
	else if ( isdefined( flag3 ) )
	{
		array[ array.size ] = flag1;
		array[ array.size ] = flag2;
		array[ array.size ] = flag3;
	}
	else if ( isdefined( flag2 ) )
	{
		msg = flag_wait_either_return( flag1, flag2 );
		return msg;
	}
	else
	{
		assertmsg( "flag_wait_any_return() needs at least 2 flags passed to it" );
		return;
	}

	for ( ;; )
	{
		for ( i = 0; i < array.size; i++ )
		{
			if ( flag( array[ i ] ) )
				return array[ i ];
		}

		msg = level waittill_any_return( flag1, flag2, flag3, flag4, flag5 );
		return msg;
	}
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flag_wait_all( <flagname1> , <flagname2>, <flagname3> , <flagname4> )"
"Summary: Waits until all of the the specified flags are set."
"Module: Flag"
"CallOn: "
"MandatoryArg: <flagname1> : name of a flag to wait on"
"MandatoryArg: <flagname2> : name of a flag to wait on"
"OptionalArg: <flagname3> : name of a flag to wait on"
"OptionalArg: <flagname4> : name of a flag to wait on"
"Example: flag_wait_any( "hq_cleared", "hq_destroyed", "hq_overrun", "hq_skipped" );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */
flag_wait_all( flag1, flag2, flag3, flag4 )
{
	if ( isdefined( flag1 ) )
		flag_wait( flag1 );

	if ( isdefined( flag2 ) )
		flag_wait( flag2 );

	if ( isdefined( flag3 ) )
		flag_wait( flag3 );

	if ( isdefined( flag4 ) )
		flag_wait( flag4 );
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flag_wait_or_timeout( <flagname> , <timer> )"
"Summary: Waits until either the flag gets set or the timer elapses."
"Module: Flag"
"CallOn: "
"MandatoryArg: <flagname1: Name of one flag to wait on"
"MandatoryArg: <timer> : Amount of time to wait before continuing regardless of flag."
"Example: flag_wait_or_timeout( "time_to_go", 3 );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
flag_wait_or_timeout( flagname, timer )
{
	timerMS = timer * 1000;
	start_time = GetTime();
	
	for ( ;; )
	{
		if ( flag( flagname ) )
		{
			break;
		}

		if ( GetTime() >= start_time + timerMS )
		{
			break;
		}
		
		timeRemaining = timerMS - ( GetTime() - start_time );  // figure out how long we waited already, if at all
		timeRemainingSecs = timeRemaining / 1000;
		wait_for_flag_or_time_elapses( flagname, timeRemainingSecs );
	}
}

/* 
============= 
///ScriptDocBegin
"Name: flag_waitopen_or_timeout( <flagname> , <timer> )"
"Summary: Waits until either the flag gets cleared or the timer elapses."
"Module: Flag"
"CallOn: "
"MandatoryArg: <flagname1: Name of one flag to wait on"
"MandatoryArg: <timer> : Amount of time to wait before continuing regardless of flag."
"Example: flag_waitopen_or_timeout( "time_to_go", 3 );"
"SPMP: both"
///ScriptDocEnd
============= 
*/
flag_waitopen_or_timeout( flagname, timer )
{
	start_time = gettime();
	for ( ;; )
	{
		if ( !flag( flagname ) )
			break;

		if ( gettime() >= start_time + timer * 1000 )
			break;

		wait_for_flag_or_time_elapses( flagname, timer );
	}
}

wait_for_flag_or_time_elapses( flagname, timer )
{
	level endon( flagname );
	wait( timer );
}


 /* 
 ============= 
///ScriptDocBegin
"Name: delayCall( <delay> , <function> , <arg1> , <arg2> , <arg3> )"
"Summary: delayCall is cool! It saves you from having to write extra script for once off commands. Note you don’t have to thread it off. delaycall is that smart!"
"Module: Utility"
"MandatoryArg: <delay> : The delay before the function occurs"
"MandatoryArg: <function> : The function to run."
"OptionalArg: <arg1> : parameter 1 to pass to the process"
"OptionalArg: <arg2> : parameter 2 to pass to the process"
"OptionalArg: <arg3> : parameter 3 to pass to the process"
"OptionalArg: <arg4> : parameter 4 to pass to the process"
"OptionalArg: <arg5> : parameter 5 to pass to the process"
"OptionalArg: <arg6> : parameter 6 to pass to the process"
"OptionalArg: <arg7> : parameter 7 to pass to the process"
"OptionalArg: <arg8> : parameter 8 to pass to the process"
"Example: delayCall( ::flag_set, "player_can_rappel", 3 );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 

delayCall( timer, func, param1, param2, param3, param4, param5, param6, param7, param8 )
{
	// to thread it off
	thread delayCall_proc( func, timer, param1, param2, param3, param4, param5, param6, param7, param8 );
}

delayCall_proc( func, timer, param1, param2, param3, param4, param5, param6, param7, param8 )
{
	if ( isSP() )
		self endon( "death" );
			
	wait( timer );
	if ( isdefined( param8 ) )
		self call [[ func ]]( param1, param2, param3, param4, param5, param6, param7, param8 );
	else
	if ( isdefined( param7 ) )
		self call [[ func ]]( param1, param2, param3, param4, param5, param6, param7 );
	else
	if ( isdefined( param6 ) )
		self call [[ func ]]( param1, param2, param3, param4, param5, param6 );
	else
	if ( isdefined( param5 ) )
		self call [[ func ]]( param1, param2, param3, param4, param5 );
	else
	if ( isdefined( param4 ) )
		self call [[ func ]]( param1, param2, param3, param4 );
	else
	if ( isdefined( param3 ) )
		self call [[ func ]]( param1, param2, param3 );
	else
	if ( isdefined( param2 ) )
		self call [[ func ]]( param1, param2 );
	else
	if ( isdefined( param1 ) )
		self call [[ func ]]( param1 );
	else
		self call [[ func ]]();	
}

 /* 
 ============= 
///ScriptDocBegin
"Name: noself_delayCall( <delay> , <function> , <arg1> , <arg2> , <arg3>, <arg4> )"
"Summary: Calls a command with no self (some commands don't support having self)."
"Module: Utility"
"MandatoryArg: <delay> : The delay before the function occurs"
"MandatoryArg: <function> : The function to run."
"OptionalArg: <arg1> : parameter 1 to pass to the process"
"OptionalArg: <arg2> : parameter 2 to pass to the process"
"OptionalArg: <arg3> : parameter 3 to pass to the process"
"OptionalArg: <arg4> : parameter 4 to pass to the process"
"Example: noself_delayCall( ::setsaveddvar, "player_can_rappel", 1 );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 

noself_delayCall( timer, func, param1, param2, param3, param4 )
{
	// to thread it off
	thread noself_delayCall_proc( func, timer, param1, param2, param3, param4 );
}

noself_delayCall_proc( func, timer, param1, param2, param3, param4 )
{
	wait( timer );
	if ( isdefined( param4 ) )
		call [[ func ]]( param1, param2, param3, param4 );
	else
	if ( isdefined( param3 ) )
		call [[ func ]]( param1, param2, param3 );
	else
	if ( isdefined( param2 ) )
		call [[ func ]]( param1, param2 );
	else
	if ( isdefined( param1 ) )
		call [[ func ]]( param1 );
	else
		call [[ func ]]();
}

 /* 
 ============= 
///ScriptDocBegin
"Name: isSP()"
"Summary: Returns false if the level name begins with mp_"
"Module: Utility"
"Example: if ( isSP() );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
isSP()
{
	if ( !isdefined( level.isSP ) )
		level.isSP = !( string_starts_with( getdvar( "mapname" ), "mp_" ) );
		
	return level.isSP;
}


/* 
 ============= 
///ScriptDocBegin
"Name: isSP_TowerDefense()"
"Summary: Returns true if the level name begins with so_td_"
"Module: Utility"
"Example: if ( isSP_TowerDefense() );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
isSP_TowerDefense()
{
	if ( !isdefined( level.isSP_TowerDefense ) )
		level.isSP_TowerDefense = string_starts_with( getdvar( "mapname" ), "so_td_" );
		
	return level.isSP_TowerDefense;
}

/*
=============
///ScriptDocBegin
"Name: string_starts_with( <string>, <start> )"
"Summary: Returns true if the first string begins with the first string"
"Module: Utility"
"CallOn:"
"MandatoryArg: <string> String to check"
"MandatoryArg: <start> Beginning of string to check"
"Example: if ( string_starts_with( "somestring", "somest" ) )"
"SPMP: both"
///ScriptDocEnd
=============
*/
string_starts_with( string, start )
{
	assert( isdefined( string ) );
	assert( isdefined( start ) );
	if ( string.size < start.size )
		return false;

	for ( i = 0 ; i < start.size ; i++ )
	{
		if ( tolower( string[ i ] ) != tolower( start[ i ] ) )
			return false;
	}

	return true;
}

plot_points( plotpoints, r, g, b, timer )
{
	lastpoint = plotpoints[ 0 ];
	if ( !isdefined( r ) )
		r = 1;
	if ( !isdefined( g ) )
		g = 1;
	if ( !isdefined( b ) )
		b = 1;
	if ( !isdefined( timer ) )
		timer = 0.05;
	for ( i = 1;i < plotpoints.size;i++ )
	{
		thread draw_line_for_time( lastpoint, plotpoints[ i ], r, g, b, timer );
		lastpoint = plotpoints[ i ];
	}
}


 /* 
 ============= 
///ScriptDocBegin
"Name: draw_line_for_time( <org1> , <org2> , <r> , <g> , <b> , <timer> )"
"Summary: Draws a line from < org1 > to < org2 > in the specified color for the specified duration"
"Module: Debug"
"CallOn: "
"MandatoryArg: <org1> : starting origin for the line"
"MandatoryArg: <org2> : ending origin for the line"
"MandatoryArg: <r> : red color value( 0 to 1 )"
"MandatoryArg: <g> : green color value( 0 to 1 )"
"MandatoryArg: <b> : blue color value( 0 to 1 )"
"MandatoryArg: <timer> : time in seconds the line should last"
"Example: thread draw_line_for_time( level.player.origin, vehicle.origin, 1, 0, 0, 10.0 );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
draw_line_for_time( org1, org2, r, g, b, timer )
{
	timer = gettime() + ( timer * 1000 );
	while ( gettime() < timer )
	{
		line( org1, org2, ( r, g, b ), 1 );
		wait .05;
	}

}


 /* 
 ============= 
///ScriptDocBegin
"Name: array_combine( <array1> , <array2> )"
"Summary: Combines the two arrays and returns the resulting array. This function doesn't care if it produces duplicates in the array."
"Module: Array"
"CallOn: "
"MandatoryArg: <array1> : first array"
"MandatoryArg: <array2> : second array"
"Example: combinedArray = array_combine( array1, array2 );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
array_combine( array1, array2 )
{
	array3 = [];
	foreach ( item in array1 )
	{
		array3[ array3.size ] = item;
	}
	foreach ( item in array2 )
	{
		array3[ array3.size ] = item;
	}
	return array3;
}


 /* 
 ============= 
///ScriptDocBegin
"Name: flat_angle( <angle> )"
"Summary: Returns the specified angle as a flat angle.( 45, 90, 30 ) becomes( 0, 90, 30 ). Useful if you just need an angle around Y - axis."
"Module: Vector"
"CallOn: "
"MandatoryArg: <angle> : angles to flatten"
"Example: yaw = flat_angle( node.angles );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
flat_angle( angle )
{
	rangle = ( 0, angle[ 1 ], 0 );
	return rangle;
}

 /* 
 ============= 
///ScriptDocBegin
"Name: flat_origin( <org> )"
"Summary: Returns a flat origin of the specified origin. Moves Z corrdinate to 0.( x, y, z ) becomes( x, y, 0 )"
"Module: Vector"
"CallOn: "
"MandatoryArg: <org> : origin to flatten"
"Example: org = flat_origin( self.origin );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
flat_origin( org )
{
	rorg = ( org[ 0 ], org[ 1 ], 0 );
	return rorg;

}

 /* 
 ============= 
///ScriptDocBegin
"Name: draw_arrow_time( <start> , <end> , <color> , <duration> )"
"Summary: Draws an arrow pointing at < end > in the specified color for < duration > seconds."
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <start> : starting coordinate for the arrow"
"MandatoryArg: <end> : ending coordinate for the arrow"
"MandatoryArg: <color> :( r, g, b ) color array for the arrow"
"MandatoryArg: <duration> : time in seconds to draw the arrow"
"Example: thread draw_arrow_time( lasttarg.origin, targ.origin, ( 0, 0, 1 ), 5.0 );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
draw_arrow_time( start, end, color, duration )
{
	level endon( "newpath" );
	pts = [];
	angles = vectortoangles( start - end );
	right = anglestoright( angles );
	forward = anglestoforward( angles );
	up = anglestoup( angles );

	dist = distance( start, end );
	arrow = [];
	range = 0.1;

	arrow[ 0 ] =  start;
	arrow[ 1 ] = start + ( right * ( dist * range ) ) + ( forward * ( dist * - 0.1 ) );
	arrow[ 2 ] =  end;
	arrow[ 3 ] = start + ( right * ( dist * ( -1 * range ) ) ) + ( forward * ( dist * - 0.1 ) );

	arrow[ 4 ] =  start;
	arrow[ 5 ] = start + ( up * ( dist * range ) ) + ( forward * ( dist * - 0.1 ) );
	arrow[ 6 ] =  end;
	arrow[ 7 ] =  start + ( up* (dist * ( -1 * range ) )) + ( forward*( dist * - 0.1) );
	arrow[ 8 ] =  start;

	r = color[ 0 ];
	g = color[ 1 ];
	b = color[ 2 ];

	plot_points( arrow, r, g, b, duration );
}


/*
=============
///ScriptDocBegin
"Name: get_linked_ents()"
"Summary: Returns an array of entities that SELF is linked to"
"Module: Utility"
"CallOn: An entity that links to other entities"
"Example: spawners = heli get_linked_ents()"
"SPMP: both"
///ScriptDocEnd
=============
*/
get_linked_ents()
{
	array = [];

	if ( isdefined( self.script_linkto ) )
	{
		linknames = get_links();
		foreach ( name in linknames )
		{
			entities = getentarray( name, "script_linkname" );
			if ( entities.size > 0 )
				array = array_combine( array, entities );
		}
	}

	return array;
}


get_linked_vehicle_nodes()
{
	array = [];

	if ( IsDefined( self.script_linkto ) )
	{
		linknames = get_links();
		foreach ( name in linknames )
		{
			entities = GetVehicleNodeArray( name, "script_linkname" );
			if ( entities.size > 0 )
				array = array_combine( array, entities );
		}
	}
	return array;
}


/*
=============
///ScriptDocBegin
"Name: get_linked_ent()"
"Summary: Returns a single entity that SELF is linked to"
"Module: Utility"
"CallOn: An entity that links to another entity"
"Example: spawner = heli get_linked_ent()"
"SPMP: both"
///ScriptDocEnd
=============
*/
get_linked_ent()
{
	array = get_linked_ents();
	assert( array.size == 1 );
	assert( isdefined( array[ 0 ] ) );
	return array[ 0 ];
}

get_linked_vehicle_node()
{
	array = get_linked_vehicle_nodes();
	assert( array.size == 1 );
	assert( isdefined( array[ 0 ] ) );
	return array[ 0 ];
	
}


/*
=============
///ScriptDocBegin
"Name: get_links( <get_links> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
get_links()
{
	return strtok( self.script_linkTo, " " );
}



/*
=============
///ScriptDocBegin
"Name: run_thread_on_targetname( <msg> , <func> , <param1> , <param2> , <param3> )"
"Summary: Runs the specified thread on any entity with that targetname"
"Module: Utility"
"MandatoryArg: <msg>: The targetname"
"MandatoryArg: <func>: The function"
"OptionalArg: <param1>: Optional argument"
"OptionalArg: <param2>: Optional argument"
"OptionalArg: <param3>: Optional argument"
"Example: run_thread_on_targetname( "chopper_guys", ::add_spawn_function, ::chopper_guys_land );"
"SPMP: both"
///ScriptDocEnd
=============
*/

run_thread_on_targetname( msg, func, param1, param2, param3 )
{
	array = getentarray( msg, "targetname" );
	array_thread( array, func, param1, param2, param3 );

	array = getstructarray( msg, "targetname" );
	array_thread( array, func, param1, param2, param3 );

	array = call [[ level.getNodeArrayFunction ]]( msg, "targetname" );
	array_thread( array, func, param1, param2, param3 );
	
	array = getvehiclenodearray( msg, "targetname" );
	array_thread( array, func, param1, param2, param3 );
}


/*
=============
///ScriptDocBegin
"Name: run_thread_on_noteworthy( <msg> , <func> , <param1> , <param2> , <param3> )"
"Summary: Runs the specified thread on any entity with that noteworthy"
"Module: Utility"
"MandatoryArg: <msg>: The noteworthy"
"MandatoryArg: <func>: The function"
"OptionalArg: <param1>: Optional argument"
"OptionalArg: <param2>: Optional argument"
"OptionalArg: <param3>: Optional argument"
"Example: run_thread_on_noteworthy( "chopper_guys", ::add_spawn_function, ::chopper_guys_land );"
"SPMP: both"
///ScriptDocEnd
=============
*/


run_thread_on_noteworthy( msg, func, param1, param2, param3 )
{
	array = getentarray( msg, "script_noteworthy" );
	array_thread( array, func, param1, param2, param3 );
	
	array = getstructarray( msg, "script_noteworthy" );
	array_thread( array, func, param1, param2, param3 );
	
	array = call [[ level.getNodeArrayFunction ]]( msg, "script_noteworthy" );
	array_thread( array, func, param1, param2, param3 );
	
	array = getvehiclenodearray( msg, "script_noteworthy" );
	array_thread( array, func, param1, param2, param3 );
}


 /* 
 ============= 
///ScriptDocBegin
"Name: draw_arrow( <start> , <end> , <color> )"
"Summary: Draws an arrow pointing at < end > in the specified color for < duration > seconds."
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <start> : starting coordinate for the arrow"
"MandatoryArg: <end> : ending coordinate for the arrow"
"MandatoryArg: <color> :( r, g, b ) color array for the arrow"
"Example: draw_arrow( lasttarg.origin, targ.origin, ( 0, 0, 1 ));"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 

draw_arrow( start, end, color )
{
	level endon( "newpath" );
	pts = [];
	angles = vectortoangles( start - end );
	right = anglestoright( angles );
	forward = anglestoforward( angles );

	dist = distance( start, end );
	arrow = [];
	range = 0.05;
	arrow[ 0 ] =  start;
	arrow[ 1 ] = start + ( right * ( dist * ( range ) ) ) + ( forward * ( dist * - 0.2 ) );
	arrow[ 2 ] =  end;
	arrow[ 3 ] = start + ( right * ( dist * ( -1 * range ) ) ) + ( forward * ( dist * - 0.2 ) );

	for ( p = 0;p < 4;p++ )
	{
		nextpoint = p + 1;
		if ( nextpoint >= 4 )
			nextpoint = 0;
		line( arrow[ p ], arrow[ nextpoint ], color, 1.0 );
	}
}



/*
=============
///ScriptDocBegin
"Name: getfx( <fx> )"
"Summary: Gets the associated level._effect"
"Module: Utility"
"MandatoryArg: <fx>: The effect"
"Example: playfx ( getfx( "heli_dust_default" ), eOrgFx.origin + offset );	"
"SPMP: both"
///ScriptDocEnd
=============
*/
getfx( fx )
{
	assertEx( isdefined( level._effect[ fx ] ), "Fx " + fx + " is not defined in level._effect." );
	return level._effect[ fx ];
}

/*
=============
///ScriptDocBegin
"Name: fxExists( <fx> )"
"Summary: Returns whether or not an fx exists"
"Module: Utility"
"MandatoryArg: <fx>: The effect"
"Example: if ( fxExists( "blah" ) )"
"SPMP: both"
///ScriptDocEnd
=============
*/
fxExists( fx )
{
	return isdefined( level._effect[ fx ] );
}

print_csv_asset( asset, type )
{
	fileline = type + "," + asset;
	if ( isdefined( level.csv_lines[ fileline ] ) )
		return;
	level.csv_lines[ fileline ] = true;
//	fileprint_chk( level.fileprint, fileline );
}

fileprint_csv_start( file )
{
	/#
	file = "scriptgen/" + file + ".csv";
	level.csv_lines = [];
	#/
}

_loadfx( effect )
{
	return loadfx( effect );
}



/*
=============
///ScriptDocBegin
"Name: getLastWeapon( <getLastWeapon> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
getLastWeapon()
{
	assert( isDefined( self.saved_lastWeapon ) );

	return self.saved_lastWeapon;
}


/*
=============
///ScriptDocBegin
"Name: PlayerUnlimitedAmmoThread()"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
PlayerUnlimitedAmmoThread()
{
	/#
	if ( !isdefined( self ) || self == level || self.code_classname != "player" )
		player = level.player;
	else
		player = self;

	assert( isdefined( player ) );

	while ( 1 )
	{
		wait .5;

		if ( getdvar( "UnlimitedAmmoOff" ) == "1" )
			continue;

		currentWeapon = player getCurrentWeapon();
		if ( currentWeapon != "none" )
		{
			currentAmmo = player GetFractionMaxAmmo( currentWeapon );
			if ( currentAmmo < 0.2 )
				player GiveMaxAmmo( currentWeapon );
		}
		currentoffhand = player GetCurrentOffhand();
		if ( currentoffhand != "none" )
		{
			currentAmmo = player GetFractionMaxAmmo( currentoffhand );
			if ( currentAmmo < 0.4 )
				player GiveMaxAmmo( currentoffhand );
		}
	}
	#/
}


isUsabilityEnabled()
{
	return ( !self.disabledUsability );
}


_disableUsability()
{
	self.disabledUsability++;
	self DisableUsability();
}


_enableUsability()
{
	self.disabledUsability--;
	
	assert( self.disabledUsability >= 0 );
	
	if ( !self.disabledUsability )
		self EnableUsability();
}


resetUsability()
{
	self.disabledUsability = 0;
	self EnableUsability();
}


_disableWeapon()
{
	self.disabledWeapon++;
	self disableWeapons();
}

_enableWeapon()
{
	self.disabledWeapon--;
	
	assert( self.disabledWeapon >= 0 );
	
	if ( !self.disabledWeapon )
		self enableWeapons();
}

isWeaponEnabled()
{
	return ( !self.disabledWeapon );
}


_disableWeaponSwitch()
{
	self.disabledWeaponSwitch++;
	self disableWeaponSwitch();
}

_enableWeaponSwitch()
{
	self.disabledWeaponSwitch--;
	
	assert( self.disabledWeaponSwitch >= 0 );
	
	if ( !self.disabledWeaponSwitch )
		self enableWeaponSwitch();
}

isWeaponSwitchEnabled()
{
	return ( !self.disabledWeaponSwitch );
}


_disableOffhandWeapons()
{
	self.disabledOffhandWeapons++;
	self DisableOffhandWeapons();
}

_enableOffhandWeapons()
{
	self.disabledOffhandWeapons--;
	
	assert( self.disabledOffhandWeapons >= 0 );
	
	if ( !self.disabledOffhandWeapons )
		self EnableOffhandWeapons();
}

isOffhandWeaponEnabled()
{
	return ( !self.disabledOffhandWeapons );
}


/*
=============
///ScriptDocBegin
"Name: random( <array> )"
"Summary: chose a random element of an array"
"Module: Array"
"CallOn: Level"
"MandatoryArg: <param1>: "
"Example: select_spot = random( array );"
"SPMP: both"
///ScriptDocEnd
=============
*/
random( array )
{
	// process the array so it'll work with any string index arrays and arrays with missing entries.
	newarray = [];
	foreach ( index, value in array )
	{
		newarray[ newarray.size ] = value;
	}

	if ( !newarray.size )
		return undefined;
	
	return newarray[ randomint( newarray.size ) ];
}


/*
=============
///ScriptDocBegin
"Name: spawn_tag_origin()"
"Summary: Spawn a script model with tag_origin model"
"Module: Utility"
"Example: ent = spawn_tag_origin();"
"SPMP: both"
///ScriptDocEnd
=============
*/
spawn_tag_origin()
{
	tag_origin = spawn( "script_model", ( 0, 0, 0 ) );
	tag_origin setmodel( "tag_origin" );
	tag_origin hide();
	if ( isdefined( self.origin ) )
		tag_origin.origin = self.origin;
	if ( isdefined( self.angles ) )
		tag_origin.angles = self.angles;

	return tag_origin;
}


/*
=============
///ScriptDocBegin
"Name: waittill_notify_or_timeout( <msg> , <timer> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
waittill_notify_or_timeout( msg, timer )
{
	self endon( msg );
	wait( timer );
}

/*
=============
///ScriptDocBegin
"Name: fileprint_launcher_start_file()"
"Summary: Tells Launcher to start storing text to a file. Use in conjunction with fileprint_launcher() and fileprint_launcher_end_file() to append to that file and then instruct launcher to write the file."
"Module: Print"
"CallOn: Level"
"Example: fileprint_launcher_start_file();"
"SPMP: both"
///ScriptDocEnd
=============
*/

fileprint_launcher_start_file()
{
	AssertEx( ! isdefined( level.fileprint_launcher ), "Can't open more than one file at a time to print through launcher." );
	level.fileprintlauncher_linecount = 0;
	level.fileprint_launcher = true;
	fileprint_launcher( "GAMEPRINTSTARTFILE:" );
}

/*
=============
///ScriptDocBegin
"Name: fileprint_launcher( <string> )"
"Summary: Tell launcher to append text to current open file created by fileprint_launcher_start_file(), to be closed and written with fileprint_launcher_end_file() "
"Module: Print"
"CallOn: Level"
"MandatoryArg: <param1>: "
"Example: fileprint_launcher( "main()" );"
"SPMP: both"
///ScriptDocEnd
=============
*/

fileprint_launcher( string )
{
	assert( isdefined( level.fileprintlauncher_linecount ) );
	level.fileprintlauncher_linecount++;
	if( level.fileprintlauncher_linecount > 200 )
	{
		wait .05;
		level.fileprintlauncher_linecount = 0;
	}
	println( "LAUNCHERPRINTLN:" + string );
}


/*
=============
///ScriptDocBegin
"Name: fileprint_launcher_end_file( <file_relative_to_game> , <bIsPerforceEnabled> )"
"Summary: Tell launcher to write out Text that has been started and appended to using fileprint_launcher_start_file() and fileprint_launcher().  you must end a file before you can start a new one."
"Module: Print"
"CallOn: Level"
"MandatoryArg: <file_relative_to_game>: relative to game ( c:\trees\iw5\game )"
"OptionalArg: <bIsPerforceEnabled>: Enabled will tell Perforce to check in the file."
"Example: fileprint_launcher_end_file( "\\share\\raw\\maps\\createart\\\" + level.script + "_art.gsc, true );"
"SPMP: both"
///ScriptDocEnd
=============
*/

fileprint_launcher_end_file( file_relative_to_game, bIsPerforceEnabled )
{
	if( !isdefined( bIsPerforceEnabled ) )
		bIsPerforceEnabled = false;

	setDevDvarIfUninitialized("LAUNCHER_PRINT_FAIL", "0"); 
	setDevDvarIfUninitialized("LAUNCHER_PRINT_SUCCESS", "0"); 
		
	if( bIsPerforceEnabled )
		fileprint_launcher( "GAMEPRINTENDFILE:GAMEPRINTP4ENABLED:"+file_relative_to_game );
	else
		fileprint_launcher( "GAMEPRINTENDFILE:"+file_relative_to_game );
		
	// wait for launcher to tell us that it's done writing the file 
	TimeOut = gettime()+4000; // give launcher 4 seconds to print the file.
	while( getdvarint( "LAUNCHER_PRINT_SUCCESS" ) == 0 &&  getdvar( "LAUNCHER_PRINT_FAIL" ) == "0" && gettime() < TimeOut )
		wait .05;
	
	if( ! ( gettime() < TimeOut ) )
	{
		iprintlnbold("LAUNCHER_PRINT_FAIL:( TIMEOUT ): launcherconflict? restart launcher and try again? " );
		setdevdvar("LAUNCHER_PRINT_FAIL", "0");
		level.fileprint_launcher = undefined;
		return false;
	}
	 
	failvar = getdvar("LAUNCHER_PRINT_FAIL");
	if( failvar != "0" )
	{
		iprintlnbold("LAUNCHER_PRINT_FAIL:( "+ failvar + " ): launcherconflict? restart launcher and try again? " );
		setdevdvar("LAUNCHER_PRINT_FAIL", "0");
		level.fileprint_launcher = undefined;
		return false;
	}
		
	setdevdvar("LAUNCHER_PRINT_FAIL", "0");
	setdevdvar( "LAUNCHER_PRINT_SUCCESS", "0" ); 
	
	level.fileprint_launcher = undefined;
	return true;
}

/*
=============
///ScriptDocBegin
"Name: launcher_write_clipboard( <str> )"
"Summary: send a string to your Connected PC's clipboard through launcher"
"Module: Print"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: launcher_write_clipboard( Players_origin_string )"
"SPMP: both"
///ScriptDocEnd
=============
*/
launcher_write_clipboard( str )
{
	level.fileprintlauncher_linecount = 0;
	fileprint_launcher( "LAUNCHER_CLIP:" + str );
}

/*
=============
///ScriptDocBegin
"Name: isDestructible()"
"Summary: returns true if self is a destructible"
"Module: Entity"
"CallOn: An entity"
"Example: if ( self isDestructible() )"
"SPMP: both"
///ScriptDocEnd
=============
*/
isDestructible()
{
	if ( !isdefined( self ) )
		return false;
	return isdefined( self.destructible_type );
}

/*
=============
///ScriptDocBegin
"Name: pauseEffect( <pauseEffect> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
pauseEffect()
{
	common_scripts\_createfx::stop_fx_looper();
}

/*
=============
///ScriptDocBegin
"Name: activate_individual_exploder()"
"Summary: Activates an individual exploder, rather than all the exploders of a given number"
"Module: Utility"
"CallOn: An exploder"
"Example: exploder activate_individual_exploder();"
"SPMP: both"
///ScriptDocEnd
=============
*/
activate_individual_exploder()
{
	if ( IsDefined( self.v[ "firefx" ] ) )
		self thread fire_effect();

	if ( IsDefined( self.v[ "fxid" ] ) && self.v[ "fxid" ] != "No FX" )
		self thread cannon_effect();
	else
	if ( IsDefined( self.v[ "soundalias" ] ) && self.v[ "soundalias" ] != "nil" )
		self thread sound_effect();

	if ( IsDefined( self.v[ "loopsound" ] ) && self.v[ "loopsound" ] != "nil" )
		self thread effect_loopsound();

	if ( IsDefined( self.v[ "damage" ] ) )
		self thread exploder_damage();

	if ( IsDefined( self.v[ "earthquake" ] ) )
		self thread exploder_earthquake();

	if ( IsDefined( self.v[ "rumble" ] ) )
		self thread exploder_rumble();

	if ( self.v[ "exploder_type" ] == "exploder" )
		self thread brush_show();
	else
	if ( ( self.v[ "exploder_type" ] == "exploderchunk" ) || ( self.v[ "exploder_type" ] == "exploderchunk visible" ) )
		self thread brush_throw();
	else
		self thread brush_delete();
}

waitframe()
{
	wait( 0.07 );
}

brush_delete()
{
// 		if( ent.v[ "exploder_type" ] != "normal" && !isdefined( ent.v[ "fxid" ] ) && !isdefined( ent.v[ "soundalias" ] ) )
// 		if( !isdefined( ent.script_fxid ) )

	num = self.v[ "exploder" ];
	if ( IsDefined( self.v[ "delay" ] ) )
		wait( self.v[ "delay" ] );
	else
		wait( .05 );// so it disappears after the replacement appears

	if ( !isdefined( self.model ) )
		return;


	Assert( IsDefined( self.model ) );

	if( isDefined( self.model.classname ) ) // script_struct support - Nate -- self is always a struct so it will never have a classname, using self.model instead -Carlos
		if ( isSP() && ( self.model.spawnflags & 1 ) )
			self.model call [[ level.connectPathsFunction ]]();

	if ( level.createFX_enabled )
	{
		if ( IsDefined( self.exploded ) )
			return;

		self.exploded = true;
		self.model Hide();
		self.model NotSolid();

		wait( 3 );
		self.exploded = undefined;
		self.model Show();
		self.model Solid();
		return;
	}

	if ( !isdefined( self.v[ "fxid" ] ) || self.v[ "fxid" ] == "No FX" )
		self.v[ "exploder" ] = undefined;

	waittillframeend;// so it hides stuff after it shows the new stuff
	
//	if ( IsDefined( self.classname ) ) // script_struct support nate --- self is always a struct so it will never have a classname, using self.model instead -Carlos
		if ( isdefined( self.model ) && isdefined( self.model.classname ) )
		{
			self.model Delete();
		}
}

brush_throw()
{
	if ( IsDefined( self.v[ "delay" ] ) )
		wait( self.v[ "delay" ] );

	ent = undefined;
	if ( IsDefined( self.v[ "target" ] ) )
		ent = get_target_ent( self.v[ "target" ] );

	if ( !isdefined( ent ) )
	{
		self.model Delete();
		return;
	}

	self.model Show();

	if ( IsDefined( self.v[ "delay_post" ] ) )
		wait( self.v[ "delay_post" ] );

	startorg = self.v[ "origin" ];
	startang = self.v[ "angles" ];
	org = ent.origin;

	temp_vec = ( org - self.v[ "origin" ] );
	x = temp_vec[ 0 ];
	y = temp_vec[ 1 ];
	z = temp_vec[ 2 ];

	physics = IsDefined( self.v[ "physics" ] );
	if ( physics )
	{
		target = undefined;
		if ( IsDefined( ent.target ) )
			target = ent get_target_ent();

		if ( !isdefined( target ) )
		{
			contact_point = startorg;// no spin just push it.
			throw_vec = ent.origin;
		}
		else
		{
			contact_point = ent.origin;
			throw_vec = ( ( target.origin - ent.origin ) * self.v[ "physics" ] );

		}

// 		model = Spawn( "script_model", startorg );
// 		model.angles = startang;
// 		model PhysicsLaunchClient( model.origin, temp_vec );
		self.model PhysicsLaunchClient( contact_point, throw_vec );
		return;
	}
	else
	{
		self.model RotateVelocity( ( x, y, z ), 12 );
		self.model MoveGravity( ( x, y, z ), 12 );
	}

	if ( level.createFX_enabled )
	{
		if ( IsDefined( self.exploded ) )
			return;

		self.exploded = true;
		wait( 3 );
		self.exploded = undefined;
		self.v[ "origin" ] = startorg;
		self.v[ "angles" ] = startang;
		self.model Hide();
		return;
	}

	self.v[ "exploder" ] = undefined;
	wait( 6 );
	self.model Delete();
// 	self Delete();
}

/*
=============
///ScriptDocBegin
"Name: get_target_ent( <target> )"
"Summary: Returns whatever SINGLE ent is targetted, be it node, struct, or entity"
"Module: Utility"
"OptionalArg: <target>: Optional target override"
"Example: node = guy get_target_ent();"
"SPMP: both"
///ScriptDocEnd
=============
*/
get_target_ent( target )
{
	if ( !isdefined( target ) )
		target = self.target;

	AssertEx( IsDefined( target ), "Self had no target!" );

	ent = GetEnt( target, "targetname" );
	if ( IsDefined( ent ) )
		return ent;

	if ( isSP() )
	{
		ent = call [[ level.getNodeFunction ]]( target, "targetname" );
		if ( IsDefined( ent ) )
			return ent;
	}

	ent = getstruct( target, "targetname" );
	if ( IsDefined( ent ) )
		return ent;

	ent = GetVehicleNode( target, "targetname" );
	if ( IsDefined( ent ) )
		return ent;

	AssertEx( "Tried to get ent, but there was no ent." );
}

brush_show()
{
	if ( IsDefined( self.v[ "delay" ] ) )
		wait( self.v[ "delay" ] );

	Assert( IsDefined( self.model ) );

	if ( !IsDefined( self.model.script_modelname ) )
	{
		self.model Show();
		self.model Solid();
	}
	else // script_structs don't pass in their .model value SO use script_modelname on them saves an entity.
	{
		model = self.model spawn_tag_origin();
		if( isDefined( self.model.script_linkname ) )
			model.script_linkname = self.model.script_linkname;
		model SetModel( self.model.script_modelname  );
		model Show();
	}

	self.brush_shown = true; // used for hiding an exploder.

	if ( isSP() && !IsDefined( self.model.script_modelname ) && ( self.model.spawnflags & 1 ) )
	{
		if ( !isdefined( self.model.disconnect_paths ) )
			self.model call [[ level.connectPathsFunction ]]();
		else
			self.model call [[ level.disconnectPathsFunction ]]();
	}

	if ( level.createFX_enabled )
	{
		if ( IsDefined( self.exploded ) )
			return;

		self.exploded = true;
		wait( 3 );
		self.exploded = undefined;
		
		if( !IsDefined( self.model.script_modelname ) ) 
		{
			self.model Hide();
			self.model NotSolid();
		}
	}
}

exploder_earthquake()
{
	self exploder_delay();
	do_earthquake( self.v[ "earthquake" ], self.v[ "origin" ] );
}


/*
=============
///ScriptDocBegin
"Name: do_earthquake( <name> , <origin> )"
"Summary: play an earthquake that is defined by add_earthquake() "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <name>: "
"MandatoryArg: <origin>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

do_earthquake( name, origin )
{
	eq = level.earthquake[ name ];
	Earthquake( eq[ "magnitude" ], eq[ "duration" ], origin, eq[ "radius" ] );
	
}

exploder_rumble()
{
	if ( !isSP() )
		return;
	
	self exploder_delay();
	level.player PlayRumbleOnEntity( self.v[ "rumble" ] );
}

exploder_delay()
{
	if ( !isdefined( self.v[ "delay" ] ) )
		self.v[ "delay" ] = 0;

	min_delay = self.v[ "delay" ];
	max_delay = self.v[ "delay" ] + 0.001;// cant randomfloatrange on the same #
	if ( IsDefined( self.v[ "delay_min" ] ) )
		min_delay = self.v[ "delay_min" ];

	if ( IsDefined( self.v[ "delay_max" ] ) )
		max_delay = self.v[ "delay_max" ];

	if ( min_delay > 0 )
		wait( RandomFloatRange( min_delay, max_delay ) );
}

exploder_damage()
{
	if ( IsDefined( self.v[ "delay" ] ) )
		delay = self.v[ "delay" ];
	else
		delay = 0;

	if ( IsDefined( self.v[ "damage_radius" ] ) )
		radius = self.v[ "damage_radius" ];
	else
		radius = 128;

	damage = self.v[ "damage" ];
	origin = self.v[ "origin" ];

	wait( delay );
	// Range, max damage, min damage
	RadiusDamage( origin, radius, damage, damage );
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

effect_loopsound()
{
	if ( IsDefined( self.loopsound_ent ) )
	{
		self.loopsound_ent Delete();
	}
	// save off this info in case we delete the effect
	origin = self.v[ "origin" ];
	alias = self.v[ "loopsound" ];
	self exploder_delay();

	self.loopsound_ent = play_loopsound_in_space( alias, origin );
}

/* 
 ============= 
///ScriptDocBegin
"Name: play_loopsound_in_space( <alias> , <origin> , <master> )"
"Summary: Use the PlayLoopSound command at a position in space. Unrelated to caller."
"Module: Sound"
"CallOn: Level"
"MandatoryArg: <alias> : Sound alias to play"
"MandatoryArg: <origin> : Origin of the sound"
"Example: play_loopsound_in_space( "siren", level.speaker.origin );"
"SPMP: both"
///ScriptDocEnd
 ============= 
 */ 
play_loopsound_in_space( alias, origin )
{
	org = Spawn( "script_origin", ( 0, 0, 0 ) );
	if ( !isdefined( origin ) )
		origin = self.origin;

	org.origin = origin;

	org PlayLoopSound( alias );
	return org;
}

sound_effect()
{
	self effect_soundalias();
}

effect_soundalias()
{
	// save off this info in case we delete the effect
	origin = self.v[ "origin" ];
	alias = self.v[ "soundalias" ];
	self exploder_delay();
	play_sound_in_space( alias, origin );
}

/* 
 ============= 
///ScriptDocBegin
"Name: play_sound_in_space( <alias> , <origin> , <master> )"
"Summary: Play a sound at an origin, unrelated to caller"
"Module: Sound"
"CallOn: Level"
"MandatoryArg: <alias> : Sound alias to play"
"MandatoryArg: <origin> : Origin of the sound"
"OptionalArg: <master> : Play this sound as a master sound. Defaults to false"
"Example: play_sound_in_space( "siren", level.speaker.origin );"
"SPMP: singleplayer"
///ScriptDocEnd
 ============= 
 */ 
play_sound_in_space( alias, origin, master )
{
	org = Spawn( "script_origin", ( 0, 0, 1 ) );
	if ( !isdefined( origin ) )
		origin = self.origin;
	org.origin = origin;
	playRet = false;
	if ( isSP() )
	{
		if ( IsDefined( master ) && master )
			playret = org PlaySoundAsMaster( alias, "sounddone" );
		else
			playret = org PlaySound( alias, "sounddone" );
	}
	else
	{
		if ( IsDefined( master ) && master )
			playret = org PlaySoundAsMaster( alias );
		else
			playret = org PlaySound( alias );
	}
	//* Don't wait if the sound failed to play
	if (playret)
	{
		if( IsAudioDisabled() )
		{
			org ent_wait_for_flag_or_time_elapses_cs( "sounddone", 2.0 );
		}
		else
		{
			org waittill( "sounddone" );
		}
	}
	org Delete();
}

ent_wait_for_flag_or_time_elapses_cs( flagname, timer )
{
	self endon( flagname );
	wait( timer );
}

cannon_effect()
{
	if ( IsDefined( self.v[ "repeat" ] ) )
	{
		thread exploder_playSound();
		for ( i = 0; i < self.v[ "repeat" ]; i++ )
		{
			PlayFX( level._effect[ self.v[ "fxid" ] ], self.v[ "origin" ], self.v[ "forward" ], self.v[ "up" ] );
			self exploder_delay();
		}
		return;
	}
	self exploder_delay();

//	PlayFX( level._effect[ self.v[ "fxid" ] ], self.v[ "origin" ], self.v[ "forward" ], self.v[ "up" ] );
	if ( IsDefined( self.looper ) )
		self.looper Delete();

	self.looper = SpawnFx( getfx( self.v[ "fxid" ] ), self.v[ "origin" ], self.v[ "forward" ], self.v[ "up" ] );
	TriggerFX( self.looper );
	exploder_playSound();
}

exploder_playSound()
{
	if ( !isdefined( self.v[ "soundalias" ] ) || self.v[ "soundalias" ] == "nil" )
		return;

	play_sound_in_space( self.v[ "soundalias" ], self.v[ "origin" ] );
}

fire_effect()
{
	forward = self.v[ "forward" ];
	up = self.v[ "up" ];

	org = undefined;

	firefxSound = self.v[ "firefxsound" ];
	origin = self.v[ "origin" ];
	firefx = self.v[ "firefx" ];
	ender = self.v[ "ender" ];
	if ( !isdefined( ender ) )
		ender = "createfx_effectStopper";
	timeout = self.v[ "firefxtimeout" ];

	fireFxDelay = 0.5;
	if ( IsDefined( self.v[ "firefxdelay" ] ) )
		fireFxDelay = self.v[ "firefxdelay" ];

	self exploder_delay();

	if ( IsDefined( firefxSound ) )
		level thread loop_fx_sound( firefxSound, origin, 1, ender, timeout );

	PlayFX( level._effect[ firefx ], self.v[ "origin" ], forward, up );

// 	loopfx( 				fxId, 	fxPos, 	waittime, 	fxPos2, 	fxStart, 	fxStop, 	timeout )
// 	maps\_fx::loopfx( 	firefx, 	origin, 	delay, 		org, 	undefined, 	ender, 	timeout );
}

loop_fx_sound( alias, origin, culled, ender, timeout )
{
	if ( IsDefined( culled ) && culled == 1 )
	{
		// this is conflicting with restart fx looper.  so check for first frame. 
		//its clear the design of this is meant to never be stopped. we don't need to restart - Nate
		//I think some of this might be piggy backed on normal fx too, in which case we want to allow the effect to restart and not the sound.
		
		if ( !IsDefined( level.first_frame ) || level.first_frame == 1 )
			SpawnLoopingSound( alias, origin );
	}
	else
	{
		org = Spawn( "script_origin", ( 0, 0, 0 ) );
	
		if ( IsDefined( ender ) )
		{
			thread loop_sound_delete( ender, org );
			self endon( ender );
		}
		org.origin = origin;
		org PlayLoopSound( alias );
		createFX_enabled = false;
		if (IsDefined(level.createFX_enabled))
		{
			createFX_enabled = level.createFX_enabled;
		}
		if ( !isDefined( timeout ) && !createFX_enabled )
		{
			org willNeverChange();
			return;
		}
	
		if ( isDefined( timeout ) )
			wait( timeout );
//	 	org Delete();
	}
}


loop_fx_sound_interval( alias, origin, ender, timeout, delay_min, delay_max )
{
	
	org = Spawn( "script_origin", ( 0, 0, 0 ) );
	
	if ( IsDefined( ender ) )
	{
		thread loop_sound_delete( ender, org );
		self endon( ender );
	}

	org.origin = origin;
	
	if( delay_min >= delay_max )
	{
		while( true )
		{
			if (getdvar("snd_remote_enable") == "1")
			{
				Print3d( origin, "delay_min >= delay_max", (1,0,0), 1, 1);
			}
			wait .05;
		}
	}
	
	if ( !SoundExists( alias ) )
	{
		while( true )
		{
			if (getdvar("snd_remote_enable") == "1")
			{
				Print3d( origin, "no sound: "+ alias, (1,0,0), 1, 1);
			}
			wait .05;
		}
	}
	
	while( true )
	{
		lock( "createfx_looper" );
		thread play_sound_in_space( alias, org.origin );
		unlock( "createfx_looper" );
		wait RandomFloatRange( delay_min, delay_max );
	}
}

loop_sound_delete( ender, ent )
{
	ent endon( "death" );
	self waittill( ender );
	ent Delete();
}

exploder_before_load( num )
{
	// gotta wait twice because the createfx_init function waits once then inits all exploders. This guarentees
	// that if an exploder is run on the first frame, it happens after the fx are init.
	waittillframeend;
	waittillframeend;
	activate_exploder( num );
}

exploder_after_load( num )
{
	activate_exploder( num );
}

activate_exploder( num )
{
	num += "";
	//prof_begin( "activate_exploder" );

	//here's a hook so you can know when a certain number of an exploder is going off
	level notify( "exploding_" + num );
	
	if (isdefined(level.createFXexploders) && !level.createFX_enabled )
	{	// do optimized form if available
		exploders = level.createFXexploders[ num ];
		if (isdefined(exploders))
		{
			foreach (ent in exploders)
			{
				ent activate_individual_exploder();
			}
		}
	}
	else
	{
		for ( i = 0;i < level.createFXent.size;i++ )
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
	
			ent activate_individual_exploder();
		}
	}
	//prof_end( "activate_exploder" );
}

/*
=============
///ScriptDocBegin
"Name: createLoopEffect( <fxid> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
createLoopEffect( fxid )
{
	ent = common_scripts\_createfx::createEffect( "loopfx", fxid );
	ent.v[ "delay" ] = common_scripts\_createfx::getLoopEffectDelayDefault();
	return ent;
}

/*
=============
///ScriptDocBegin
"Name: createOneshotEffect( <fxid> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
createOneshotEffect( fxid )
{
	// uses triggerfx
	ent = common_scripts\_createfx::createEffect( "oneshotfx", fxid );
	ent.v[ "delay" ] = common_scripts\_createfx::getOneshotEffectDelayDefault();
	return ent;
}

/*
=============
///ScriptDocBegin
"Name: createExploder( <fxid> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
createExploder( fxid )
{
	ent = common_scripts\_createfx::createEffect( "exploder", fxid );
	ent.v[ "delay" ] = common_scripts\_createfx::getExploderDelayDefault();
	ent.v[ "exploder_type" ] = "normal";
	return ent;
}

/*
=============
///ScriptDocBegin
"Name: alphabetize( <array> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: both"
///ScriptDocEnd
=============
*/
alphabetize( array )
{
	if ( array.size <= 1 )
		return array;

	count = 0;
	for ( asize = array.size - 1; asize >= 1; asize-- )
	{
		largest = array[asize];
		largestIndex = asize;
		for ( i = 0; i < asize; i++ )
		{
			string1 = array[ i ];
			
			if ( StrICmp(string1, largest ) > 0 )
			{
				largest = string1;
				largestIndex = i;
			}
		}
		
		if(largestIndex != asize)
		{
			array[largestIndex] = array[asize];
			array[asize] = largest;
		}
	}

	return array;
}

is_later_in_alphabet( string1, string2 )
{
	return StrICmp( string1, string2 ) > 0;
}

alphabet_compare( a, b )
{
	list = [];
	val = 1;
	list[ "0" ] = val; val++;
	list[ "1" ] = val; val++;
	list[ "2" ] = val; val++;
	list[ "3" ] = val; val++;
	list[ "4" ] = val; val++;
	list[ "5" ] = val; val++;
	list[ "6" ] = val; val++;
	list[ "7" ] = val; val++;
	list[ "8" ] = val; val++;
	list[ "9" ] = val; val++;
	list[ "_" ] = val; val++;
	list[ "a" ] = val; val++;
	list[ "b" ] = val; val++;
	list[ "c" ] = val; val++;
	list[ "d" ] = val; val++;
	list[ "e" ] = val; val++;
	list[ "f" ] = val; val++;
	list[ "g" ] = val; val++;
	list[ "h" ] = val; val++;
	list[ "i" ] = val; val++;
	list[ "j" ] = val; val++;
	list[ "k" ] = val; val++;
	list[ "l" ] = val; val++;
	list[ "m" ] = val; val++;
	list[ "n" ] = val; val++;
	list[ "o" ] = val; val++;
	list[ "p" ] = val; val++;
	list[ "q" ] = val; val++;
	list[ "r" ] = val; val++;
	list[ "s" ] = val; val++;
	list[ "t" ] = val; val++;
	list[ "u" ] = val; val++;
	list[ "v" ] = val; val++;
	list[ "w" ] = val; val++;
	list[ "x" ] = val; val++;
	list[ "y" ] = val; val++;
	list[ "z" ] = val; val++;

	a = ToLower( a );
	b = ToLower( b );
	val1 = 0;
	if ( IsDefined( list[ a ] ) )
		val1 = list[ a ];

	val2 = 0;
	if ( IsDefined( list[ b ] ) )
		val2 = list[ b ];

	if ( val1 > val2 )
		return "1st";
	if ( val1 < val2 )
		return "2nd";
	return "same";
}

/* 
============= 
///ScriptDocBegin
"Name: play_loop_sound_on_entity( <alias> , <offset> )"
"Summary: Play loop sound alias on an entity"
"Module: Sound"
"CallOn: An entity"
"MandatoryArg: <alias> : Sound alias to loop"
"OptionalArg: <offset> : Offset for sound origin relative to the world from the models origin."
"Example: vehicle thread play_loop_sound_on_entity( "engine_belt_run" );"
"SPMP: both"
///ScriptDocEnd
============= 
*/ 
play_loop_sound_on_entity( alias, offset )
{
	org = Spawn( "script_origin", ( 0, 0, 0 ) );
	org endon( "death" );
	thread delete_on_death( org );
	
	if ( IsDefined( offset ) )
	{
		org.origin = self.origin + offset;
		org.angles = self.angles;
		org LinkTo( self );
	}
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

/* 
============= 
///ScriptDocBegin
"Name: stop_loop_sound_on_entity( <alias> )"
"Summary: Stop playing the the loop sound alias on an entity"
"Module: Sound"
"CallOn: An entity"
"MandatoryArg: <alias> : Sound alias to stop looping"
"Example: vehicle thread stop_loop_sound_on_entity( "engine_belt_run" );"
"SPMP: both"
///ScriptDocEnd
============= 
*/ 
stop_loop_sound_on_entity( alias )
{
	self notify( "stop sound" + alias );
}

/*
=============
///ScriptDocBegin
"Name: delete_on_death( <ent> )"
"Summary: Delete the entity when "self" dies."
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: level.helicopter thread delete_on_death( someRandomScriptOriginThatISpawned );"
"SPMP: both"
///ScriptDocEnd
=============
*/
delete_on_death( ent )
{
	//self ==> the entity you want to wait to die before deleting the ent
	ent endon( "death" );
	self waittill( "death" );
	if ( IsDefined( ent ) )
		ent Delete();
}

error( msg )
{
	PrintLn( "^c * ERROR * ", msg );
	waitframe();

	/#
	if ( GetDvar( "debug" ) != "1" )
		AssertMsg( "This is a forced error - attach the log file. \n" + msg );
	#/
}

/*
=============
///ScriptDocBegin
"Name: exploder( <num> )"
"Summary: Sets off the desired exploder"
"Module: Utility"
"MandatoryArg: <num>: The exploder number"
"Example: exploder( 5 );"
"SPMP: both"
///ScriptDocEnd
=============
*/
exploder( num )
{
	[[ level.exploderFunction ]]( num );
}


/*
=============
///ScriptDocBegin
"Name: create_dvar( <var> , <val> )"
"Summary: Initialize a dvar with a given value"
"Module: Utility"
"MandatoryArg: <var>: Name of the dvar"
"MandatoryArg: <val>: Default value"
"Example: create_dvar( "fish", "on" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
create_dvar( var, val )
{
	SetDvarIfUninitialized( var, val );
}


void()
{
}


/*
=============
///ScriptDocBegin
"Name: tag_project( <tagname> , <dist> )"
"Summary: returns a point projected off a tag"
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <tagname>: "
"MandatoryArg: <dist>: "
"Example: target = tank tag_project( "tag_flash", 99999 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

tag_project( tagname, dist  )
{
	org = self GetTagOrigin( tagname  );
	angle = self GetTagAngles( tagname );
	vector = AnglesToForward( angle );	
	vector = VectorNormalize( vector ) * dist;
	return org + vector;
}

/*
=============
///ScriptDocBegin
"Name: ter_op( <statement> , <true_value> , <false_value> )"
"Summary: Functon that serves as a tertiary operator in C/C++"
"Module: Utility"
"CallOn: "
"MandatoryArg: <statement>: The statement to evaluate"
"MandatoryArg: <true_value>: The value that is returned when the statement evaluates to true"
"MandatoryArg: <false_value>: That value that is returned when the statement evaluates to false"
"Example: x = ter_op( x > 5, 2, 7 );"
"SPMP: both"
///ScriptDocEnd
=============
*/

ter_op( statement, true_value, false_value )
{
	if ( statement )
		return true_value;
	return false_value;
}


create_lock( msg, count )
{
	if ( !IsDefined( count ) )
		count = 1;

	Assert( IsDefined( msg ) );
	
	if ( !IsDefined( level.lock ) )
		level.lock = [];
		
	lock_struct = SpawnStruct();
	lock_struct.max_count = count;
	lock_struct.count = 0;
	level.lock[ msg ] = lock_struct;
}

lock( msg )
{
	Assert( IsDefined( level.lock ) );	
	Assert( IsDefined( level.lock[ msg ] ) );
	lock = level.lock[ msg ];
	while ( lock.count >= lock.max_count )
		lock waittill ( "unlocked" );
	lock.count++;
}

is_locked( msg )
{
	Assert( IsDefined( level.lock ) );	
	Assert( IsDefined( level.lock[ msg ] ) );
	lock = level.lock[ msg ];
	return lock.count > lock.max_count;
}

unlock_wait( msg )
{
	//dodge endon issues
	thread unlock_thread( msg );
	wait 0.05;
}

unlock( msg )
{
	//dodge endon issues
	thread unlock_thread( msg );
}

unlock_thread( msg )
{
	wait 0.05;
	Assert( IsDefined( level.lock ) );	
	Assert( IsDefined( level.lock[ msg ] ) );
	lock = level.lock[ msg ];
	lock.count--;
	Assert( lock.count >= 0 );
	lock notify ( "unlocked" );
}

/*
=============
///ScriptDocBegin
"Name: get_template_level()"
"Summary: returns the templated level or level.script"
"Module: Entity"
"CallOn: An entity"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

get_template_level()
{
	script = level.script;
	if ( IsDefined( level.template_script ) )
		script = level.template_script;
	return script;
}

wii_play_grenade_rumble( position )
{
	foreach ( player in level.players )
	{
		if ( Distance( position, player.origin ) <= 400 )
			player PlayRumbleOnEntity( "wii_grenade_rumble" );
	}
}
