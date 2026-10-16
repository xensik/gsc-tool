#include common_scripts\utility;
#include maps\_utility;
#include maps\_hud_util;
/* 
	Functions called only from _utility
*/ 

linetime_proc( start, end, color, timer )
{
	for ( i = 0; i < timer * 20; i++ )
	{
		Line( start, end, color );
		wait( 0.05 );
	}
}

structarray_swap( object1, object2 )
{
	index1 = object1.struct_array_index;
	index2 = object2.struct_array_index;
	self.array[ index2 ] = object1;
	self.array[ index1 ] = object2;
	self.array[ index1 ].struct_array_index = index1;
	self.array[ index2 ].struct_array_index = index2;
}

waitSpread_code( start, end )
{
	waittillframeend;// give every other waitspreader in this frame a chance to increment wait_spreaders

	Assert( level.wait_spreaders >= 1 );

	allotment = [];

	if ( level.wait_spreaders == 1 )
	{
		allotment[ 0 ] = RandomFloatRange( start, end );
		level.wait_spreader_allotment = allotment;
		level.active_wait_spread = undefined;
		return;
	}

	allotment[ 0 ] = start;
	allotment[ allotment.size ] = end;

	for ( i = 1; i < level.wait_spreaders - 1; i++ )
	{
		allotment = waitSpread_insert( allotment );
	}

	level.wait_spreader_allotment = array_randomize( allotment );
	level.active_wait_spread = undefined;
}

waitSpread_insert( allotment )
{
	gapIndex = -1;
	gap = 0;
	// get the largest waitspread gap
	for ( p = 0; p < allotment.size - 1; p++ )
	{
		newgap = allotment[ p + 1 ] - allotment[ p ];
		if ( newgap <= gap )
			continue;

		gap = newgap;
		gapIndex = p;
	}

	Assert( gap > 0 );
	newAllotment = [];

	for ( i = 0; i < allotment.size; i++ )
	{
		if ( gapIndex == i - 1 )
		{
			newAllotment[ newAllotment.size ] = RandomFloatRange( allotment[ gapIndex ], allotment[ gapIndex + 1 ] );
		}
		newAllotment[ newAllotment.size ] = allotment[ i ];
	}

	return newAllotment;
}


waittill_objective_event_proc( requireTrigger )
{
	while ( level.deathSpawner[ self.script_deathchain ] > 0 )
		level waittill( "spawner_expired" + self.script_deathchain );

	if ( requireTrigger )
		self waittill( "trigger" );

	flag = self get_trigger_flag();
	flag_set( flag );
}

wait_until_done_speaking()
{
	self endon( "death" );
	while ( self.isSpeaking )
	{
		wait( 0.05 );
	}
}

wait_for_trigger_think( ent )
{
	self endon( "death" );
	ent endon( "trigger" );
	self waittill( "trigger" );

	ent notify( "trigger" );
}

wait_for_trigger( msg, type )
{
	triggers = GetEntArray( msg, type );
	ent = SpawnStruct();

	array_thread( triggers, ::wait_for_trigger_think, ent );
	ent waittill( "trigger" );
}


ent_waits_for_level_notify( msg )
{
	level waittill( msg );
	self notify( "done" );
}

ent_waits_for_notify( ent, msg )
{
	ent waittill( msg );
	self notify( "done" );
}

ent_waits_for_trigger( trigger )
{
	trigger waittill( "trigger" );
	self notify( "done" );
}

ent_times_out( timer )
{
	wait( timer );
	self notify( "done" );
}

update_debug_friendlycolor_on_death()
{
	self notify( "debug_color_update" );
	self endon( "debug_color_update" );
	num = self.unique_id;
	self waittill( "death" );
	level.debug_color_friendlies[ num ] = undefined;

	// updates the debug color friendlies info
	level notify( "updated_color_friendlies" );
}


update_debug_friendlycolor( num )
{
	thread update_debug_friendlycolor_on_death();
	if ( IsDefined( self.script_forcecolor ) )
	{
		level.debug_color_friendlies[ num ] = self.script_forceColor;
	}
	else
	{
		level.debug_color_friendlies[ num ] = undefined;
	}
	// updates the debug color friendlies info
	level notify( "updated_color_friendlies" );
}

insure_player_does_not_set_forcecolor_twice_in_one_frame()
{
	/#
	AssertEx( !isdefined( self.setforcecolor ), "Tried to set forceColor on an ai twice in one frame. Don't spam set_force_color." );
	self.setforcecolor = true;
	waittillframeend;
	if ( !isalive( self ) )
		return;
	self.setforcecolor = undefined;
	#/
}


new_color_being_set( color )
{
	self notify( "new_color_being_set" );
	self.new_force_color_being_set = true;
	maps\_colors::left_color_node();

	self endon( "new_color_being_set" );
	self endon( "death" );

	// insure we're only getting one color change, multiple in one frame will get overwritten.
	waittillframeend;
	waittillframeend;

	if ( IsDefined( self.script_forcecolor ) )
	{
		// grab the current colorCode that AI of this color are forced to, if there is one
		self.currentColorCode = level.currentColorForced[ self maps\_colors::get_team() ][ self.script_forcecolor ];
		if ( IsDefined( self.dontColorMove ) )
			self.dontColorMove = undefined;
		else
			self thread maps\_colors::goto_current_ColorIndex();
	}

	self.new_force_color_being_set = undefined;
	self notify( "done_setting_new_color" );
	/#
	update_debug_friendlycolor( self.unique_id );
	#/
}

radio_queue_thread( msg )
{
	queueTime = GetTime();
	for ( ;; )
	{
		if ( !isdefined( self._radio_queue ) )
			break;

		self waittill( "finished_radio" );
		if ( GetTime() > queueTime + 7500 )
			return;
	}

	self._radio_queue = true;

	wait_for_buffer_time_to_pass( level.last_mission_sound_time, 0.5 );

	level.player play_sound_on_entity( level.scr_radio[ msg ] );
	self._radio_queue = undefined;
	level.last_mission_sound_time = GetTime();

	self notify( "finished_radio" );
}

ent_wait_for_flag_or_time_elapses( flagname, timer )
{
	self endon( flagname );
	wait( timer );
}

waittill_either_function_internal( ent, func, parm )
{
	ent endon( "done" );
	[[ func ]]( parm );
	ent notify( "done" );
}


HintPrintWait( length, breakfunc )
{
	if ( !isdefined( breakfunc ) )
	{
		wait( length );
		return;
	}

	timer = length * 20;
	for ( i = 0; i < timer; i++ )
	{
		if ( [[ breakfunc ]]() )
			break;
		wait( 0.05 );
	}
}

hint_timeout( timeout )
{
	wait( timeout );
	self.timed_out = true;
}

HintPrint( string, breakfunc, parm1, parm2, parm3, timeout )
{
	Assert( IsPlayer( self ) );

	if ( !isalive( self ) )
		return;

	MYFADEINTIME = 1.0;
	MYFLASHTIME = 0.75;
	MYALPHAHIGH = 0.95;
	MYALPHALOW = 0.4;
	fontscale = 2;
	if (isdefined(level.hint_fontscale))
		fontscale = level.hint_fontscale;

	if ( isdefined( self.current_global_hint ) )
	{
		if ( self.current_global_hint == string )
			return;
	}

	ent_flag_waitopen( "global_hint_in_use" );
	if ( isdefined( self.current_global_hint ) )
	{
		if ( self.current_global_hint == string )
			return;
	}
		
	ent_flag_set( "global_hint_in_use" );

	self.current_global_hint = string;
	
	Hint = createClientFontString( "default", fontscale );
	level.current_hint = Hint;
	
	thread destroy_hint_on_friendlyfire( hint );
	level endon( "friendlyfire_mission_fail" );
	
	//Hint.color = ( 1, 1, .5 ); //remove color so that color highlighting on PC can show up.
	Hint.alpha = 0.9;
	Hint.x = 0;
	Hint.y = -68;
	Hint.alignx = "center";
	Hint.aligny = "middle";
	Hint.horzAlign = "center";
	Hint.vertAlign = "middle";
	Hint.foreground = false;
	Hint.hidewhendead = true;
	Hint.hidewheninmenu = true;

	Hint SetText( string );

	Hint.alpha = 0;
	Hint FadeOverTime( MYFADEINTIME );
	Hint.alpha = MYALPHAHIGH;
	HintPrintWait( MYFADEINTIME, breakfunc );

	parms = 0;
	if ( IsDefined( parm3 ) )
		parms = 3;
	else
	if ( IsDefined( parm2 ) )
		parms = 2;
	else
	if ( IsDefined( parm1 ) )
		parms = 1;

	timeout_ent = SpawnStruct();
	timeout_ent.timed_out = false;
	if ( IsDefined( timeout ) )
	{
		timeout_ent thread hint_timeout( timeout );
	}

	if ( IsDefined( breakfunc ) )
	{
		for ( ;; )
		{

			Hint FadeOverTime( MYFLASHTIME );
			Hint.alpha = MYALPHALOW;
			HintPrintWait( MYFLASHTIME, breakfunc );

			if ( parms == 3 )
			{
				if ( [[ breakfunc ]]( parm1, parm2, parm3 ) )
					break;
			}
			else
			if ( parms == 2 )
			{
				if ( [[ breakfunc ]]( parm1, parm2 ) )
					break;
			}
			else
			if ( parms == 1 )
			{
				if ( [[ breakfunc ]]( parm1 ) )
					break;
			}
			else
			{
				if ( [[ breakfunc ]]() )
					break;
			}

			Hint FadeOverTime( MYFLASHTIME );
			Hint.alpha = MYALPHAHIGH;
			HintPrintWait( MYFLASHTIME, breakfunc );

			if ( timeout_ent.timed_out )
				break;

			if ( parms == 3 )
			{
				if ( [[ breakfunc ]]( parm1, parm2, parm3 ) )
					break;
			}
			else
			if ( parms == 2 )
			{
				if ( [[ breakfunc ]]( parm1, parm2 ) )
					break;
			}
			else
			if ( parms == 1 )
			{
				if ( [[ breakfunc ]]( parm1 ) )
					break;
			}
			else
			{
				if ( [[ breakfunc ]]() )
					break;
			}
		}
	}
	else
	{
		for ( i = 0; i < 1; i++ )
		{
			Hint FadeOverTime( MYFLASHTIME );
			Hint.alpha = MYALPHALOW;
			HintPrintWait( MYFLASHTIME, breakfunc );

			Hint FadeOverTime( MYFLASHTIME );
			Hint.alpha = MYALPHAHIGH;
			HintPrintWait( MYFLASHTIME, breakfunc );
		}
	}
	
	hint notify( "destroying" );
	self.current_global_hint = undefined;
	Hint Destroy();
	level.current_hint = undefined;
	ent_flag_clear( "global_hint_in_use" );
}

destroy_hint_on_friendlyfire( hint )
{
	hint endon( "destroying" );
	
	level waittill( "friendlyfire_mission_fail" );
	
	if ( !isdefined( hint ) )
		return;
	
	self.current_global_hint = undefined;
	hint Destroy();
	ent_flag_clear( "global_hint_in_use" );
}
	

ShowHintPrint_struct( struct )
{
	struct.timed_out = false;
	Assert( IsPlayer( self ) );

	if ( !isalive( self ) )
		return;

	MYFADEINTIME = 1.0;
	MYFLASHTIME = 0.75;
	MYALPHAHIGH = 0.95;
	MYALPHALOW = 0.4;

	ent_flag_waitopen( "global_hint_in_use" );
	ent_flag_set( "global_hint_in_use" );

	// could have been stopped while waiting for the hint area to open
	if ( struct.timed_out )
		return;

	if ( IsDefined( struct.timeout ) )
	{
		struct thread hint_timeout( struct.timeout );
	}

	Hint = createClientFontString( "objective", 2 );

	//Hint.color = ( 1, 1, .5 ); //remove color so that color highlighting on PC can show up.
	Hint.alpha = 0.9;
	Hint.x = 0;
	Hint.y = -38;
	Hint.alignx = "center";
	Hint.aligny = "middle";
	Hint.horzAlign = "center";
	Hint.vertAlign = "middle";
	Hint.foreground = false;
	Hint.hidewhendead = true;

	Hint SetText( struct.string );

	Hint.alpha = 0;
	Hint FadeOverTime( MYFADEINTIME );
	Hint.alpha = MYALPHAHIGH;
	HintPrintWait( MYFADEINTIME );

	for ( ;; )
	{
		Hint FadeOverTime( MYFLASHTIME );
		Hint.alpha = MYALPHALOW;
		HintPrintWait( MYFLASHTIME );

		if ( struct.timed_out )
			break;

		Hint FadeOverTime( MYFLASHTIME );
		Hint.alpha = MYALPHAHIGH;
		HintPrintWait( MYFLASHTIME );

		if ( struct.timed_out )
			break;
	}

	Hint Destroy();
	ent_flag_clear( "global_hint_in_use" );
}

lerp_player_view_to_tag_internal( player, tag, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc, hit_geo )
{
	if ( IsDefined( self.first_frame_time ) && self.first_frame_time == GetTime() )
	{
		// the base ai / vehicle / model just was put into the first frame and it takes a server frame for the
		// tags to get into position
		wait( 0.10 );
	}

	origin = self GetTagOrigin( tag );
	angles = self GetTagAngles( tag );
	player lerp_player_view_to_position( origin, angles, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc, hit_geo );

	if ( hit_geo )
		return;

	player PlayerLinkTo( self, tag, fraction, right_arc, left_arc, top_arc, bottom_arc, false );
}

lerp_player_view_to_tag_oldstyle_internal( player, tag, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc, hit_geo )
{
	if ( IsDefined( self.first_frame_time ) && self.first_frame_time == GetTime() )
	{
		// the base ai / vehicle / model just was put into the first frame and it takes a server frame for the
		// tags to get into position
		wait( 0.10 );
	}

	origin = self GetTagOrigin( tag );
	angles = self GetTagAngles( tag );
	player lerp_player_view_to_position_oldstyle( origin, angles, lerptime, fraction, right_arc, left_arc, top_arc, bottom_arc, true );

	if ( hit_geo )
		return;

	player PlayerLinkToDelta( self, tag, fraction, right_arc, left_arc, top_arc, bottom_arc, false );
}

function_stack_wait( localentity )
{
	self endon( "death" );
	localentity waittill_either( "function_done", "death" );
}

function_stack_wait_finish( localentity )
{
	function_stack_wait( localentity );

	if ( !isdefined( self ) )
		return false;

	//if isdefined but not sentient -> good enough
	if ( !issentient( self ) )
		return true;

	//if is defined and is sentient and is alive -> good
	if ( IsAlive( self ) )
		return true;

	//if is defined and is sentient but dead -> false
	return false;
}

function_stack_proc( caller, func, param1, param2, param3, param4, param5 )
{
	self endon( "death" );

	if ( !isdefined( caller.function_stack ) )
		caller.function_stack = [];

	caller.function_stack[ caller.function_stack.size ] = self;

	self thread function_stack_self_death( caller );
	function_stack_caller_waits_for_turn( caller );

	if ( IsDefined( caller ) && IsDefined( caller.function_stack ) )
	{
		self.function_stack_func_begun = true;
		self notify( "function_stack_func_begun" );

		if ( IsDefined( param5 ) )
			caller [[ func ]]( param1, param2, param3, param4, param5 );
		else
		if ( IsDefined( param4 ) )
			caller [[ func ]]( param1, param2, param3, param4 );
		else
		if ( IsDefined( param3 ) )
			caller [[ func ]]( param1, param2, param3 );
		else
		if ( IsDefined( param2 ) )
			caller [[ func ]]( param1, param2 );
		else
		if ( IsDefined( param1 ) )
			caller [[ func ]]( param1 );
		else
			caller [[ func ]]();
		
		if ( IsDefined( caller ) && IsDefined( caller.function_stack ) )
		{
			caller.function_stack = array_remove( caller.function_stack, self );
			caller notify( "level_function_stack_ready" );
		}
	}

	if ( IsDefined( self ) )
	{
		self.function_stack_func_begun = false;
		self notify( "function_done" );
	}
}

function_stack_self_death( caller )
{
	self endon( "function_done" );

	self waittill( "death" );

	if ( IsDefined( caller ) )
	{
		caller.function_stack = array_remove( caller.function_stack, self );
		caller notify( "level_function_stack_ready" );
	}
}


function_stack_caller_waits_for_turn( caller )
{
	caller endon( "death" );
	self endon( "death" );
	caller endon( "clear_function_stack" );

	while ( caller.function_stack[ 0 ] != self )
		caller waittill( "level_function_stack_ready" );
}

unflash_flag( seconds )
{
	level endon( "player_flashed" );
	wait( seconds );
	flag_clear( "player_flashed" );
}

wait_for_sounddone_or_death( org )
{
	self endon( "death" );
	org waittill( "sounddone" );
	return true;
}

init_vision_set( visionset )
{
	level.lvl_visionset = visionset;

	if ( !isdefined( level.vision_cheat_enabled ) )
		level.vision_cheat_enabled = false;

	return level.vision_cheat_enabled;
}

array_waitlogic1( ent, msg, timeout )
{
	self array_waitlogic2( ent, msg, timeout );

	self._array_wait = false;
	self notify( "_array_wait" );
}

array_waitlogic2( ent, msg, timeout )
{
	ent endon( msg );
	ent endon( "death" );

	if ( IsDefined( timeout ) )
		wait timeout;
	else
		ent waittill( msg );
}

exec_call( func )
{
	if ( func.parms.size == 0 )
	{
		func.caller call [[ func.func ]]();
	}
	else
	if ( func.parms.size == 1 )
	{
		func.caller call [[ func.func ]]( func.parms[ 0 ] );
	}
	else
	if ( func.parms.size == 2 )
	{
		func.caller call [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ] );
	}
	else
	if ( func.parms.size == 3 )
	{
		func.caller call [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ], func.parms[ 2 ] );
	}
	if ( func.parms.size == 4 )
	{
		func.caller call [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ], func.parms[ 2 ], func.parms[ 3 ] );
	}
	if ( func.parms.size == 5 )
	{
		func.caller call [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ], func.parms[ 2 ], func.parms[ 3 ], func.parms[ 4 ] );
	}
}

exec_call_noself( func )
{
	if ( func.parms.size == 0 )
	{
		call [[ func.func ]]();
	}
	else
	if ( func.parms.size == 1 )
	{
		call [[ func.func ]]( func.parms[ 0 ] );
	}
	else
	if ( func.parms.size == 2 )
	{
		call [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ] );
	}
	else
	if ( func.parms.size == 3 )
	{
		call [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ], func.parms[ 2 ] );
	}
	if ( func.parms.size == 4 )
	{
		call [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ], func.parms[ 2 ], func.parms[ 3 ] );
	}
	if ( func.parms.size == 5 )
	{
		call [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ], func.parms[ 2 ], func.parms[ 3 ], func.parms[ 4 ] );
	}
}

exec_func( func, endons )
{
	if ( !isdefined( func.caller ) )
		return;

	for ( i = 0; i < endons.size; i++ )
	{
		endons[ i ].caller endon( endons[ i ].ender );
	}

	if ( func.parms.size == 0 )
	{
		func.caller [[ func.func ]]();
	}
	else
	if ( func.parms.size == 1 )
	{
		func.caller [[ func.func ]]( func.parms[ 0 ] );
	}
	else
	if ( func.parms.size == 2 )
	{
		func.caller [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ] );
	}
	else
	if ( func.parms.size == 3 )
	{
		func.caller [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ], func.parms[ 2 ] );
	}
	if ( func.parms.size == 4 )
	{
		func.caller [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ], func.parms[ 2 ], func.parms[ 3 ] );
	}
	if ( func.parms.size == 5 )
	{
		func.caller [[ func.func ]]( func.parms[ 0 ], func.parms[ 1 ], func.parms[ 2 ], func.parms[ 3 ], func.parms[ 4 ] );
	}
}

waittill_func_ends( func, endons )
{
	self endon( "all_funcs_ended" );
	self endon( "any_funcs_aborted" );
	exec_func( func, endons );
	self.count--;
	self notify( "func_ended" );
}

waittill_abort_func_ends( func, endons )
{
	self endon( "all_funcs_ended" );
	self endon( "any_funcs_aborted" );
	exec_func( func, endons );
	self.abort_count--;
	self notify( "abort_func_ended" );
}

do_abort( array )
{
	self endon( "all_funcs_ended" );

	if ( !array.size )
		return;

	count_to_reach = 0;
	self.abort_count = array.size;
	endons = [];

	self array_levelthread( array, ::waittill_abort_func_ends, endons );

	for ( ;; )
	{
		if ( self.abort_count <= count_to_reach )
			break;
		self waittill( "abort_func_ended" );
	}
	self notify( "any_funcs_aborted" );
}


translate_local_on_ent( entity )
{
	if ( IsDefined( self.forward ) )
	{
		forward = AnglesToForward( entity.angles );
		entity.origin += forward * self.forward;
	}
	if ( IsDefined( self.right ) )
	{
		right = AnglesToRight( entity.angles );
		entity.origin += right * self.right;
	}
	if ( IsDefined( self.up ) )
	{
		up = AnglesToUp( entity.angles );
		entity.origin += up * self.up;
	}

	if ( IsDefined( self.yaw ) )
	{
		entity AddYaw( self.yaw );
	}
	if ( IsDefined( self.pitch ) )
	{
		entity AddPitch( self.pitch );
	}
	if ( IsDefined( self.roll ) )
	{
		entity AddRoll( self.roll );
	}
}

dynamic_run_speed_proc( pushdist, sprintdist, stopdist, jogdist, group )
{
	self notify( "start_dynamic_run_speed" );

	self endon( "death" );
	self endon( "stop_dynamic_run_speed" );
	self endon( "start_dynamic_run_speed" );
	level endon( "_stealth_spotted" );

	if ( self ent_flag_exist( "_stealth_custom_anim" ) )
		self ent_flag_waitopen( "_stealth_custom_anim" );

	if ( !self ent_flag_exist( "dynamic_run_speed_stopped" ) )
	{
		self ent_flag_init( "dynamic_run_speed_stopped" );
		self ent_flag_init( "dynamic_run_speed_stopping" );
	}
	else
	{
		self ent_flag_clear( "dynamic_run_speed_stopping" );
		self ent_flag_clear( "dynamic_run_speed_stopped" );
	}

	self.run_speed_state = "";
	self.old_moveplaybackrate = self.moveplaybackrate;

	self thread stop_dynamic_run_speed();

	//MUCH faster to do distancesquared checks than distance
	pushdist2rd 	 = pushdist * pushdist;
	sprintdist2rd 	 = sprintdist * sprintdist;
	stopdist2rd 	 = stopdist * stopdist;
	jogdist2rd		 = jogdist * jogdist;

	while ( 1 )
	{
		wait .05;

		//the player that is the closest to us should have the most effect on us, therefore
		//the player closest to us will determine if we run, jog, or stop. sprinting to catch up
		//is actually done through both this test and a second test to see if the player further 
		//away is actually ahead of us (that's done in dynamic_run_ahead test ) which uses the 
		//wait_for_player function in go_to_node in _spawner

		player = level.players[ 0 ];
		foreach ( value in level.players )
		{
			if ( DistanceSquared( player.origin, self.origin ) > DistanceSquared( value.origin, self.origin ) )
				player = value;
		}

		vec = AnglesToForward( self.angles );
		vec2 = VectorNormalize( ( player.origin - self.origin ) );
		vecdot = VectorDot( vec, vec2 );

		//how far is the player
		dist2rd 		 = DistanceSquared( self.origin, player.origin );
		dist2rd_group 	 = dist2rd;

		if ( IsDefined( group ) )
		{
			//not worrying about supporting multiple players since coop is not a priority
			key = getClosest( player.origin, group );
			dist2rd_group = DistanceSquared( key.origin, player.origin );
		}

		//is the player actually ahead of us, even though we're not facing him?
		ahead = false;
		if ( IsDefined( self.last_set_goalent ) )
			ahead = [[ level.drs_ahead_test ]]( self.last_set_goalent, sprintdist );
		else if ( IsDefined( self.last_set_goalnode ) )
			ahead = [[ level.drs_ahead_test ]]( self.last_set_goalnode, sprintdist );

		if ( IsDefined( self.cqbwalking ) && self.cqbwalking && !self.dontChangeMovePlaybackRate )
				self.moveplaybackrate = 1;

		if ( dist2rd < sprintdist2rd || vecdot > - .25 || ahead )
		{
			dynamic_run_set( "sprint" );
			wait .5;
			continue;
		}

		else if ( dist2rd < pushdist2rd || vecdot > - .25 )
		{
			dynamic_run_set( "run" );
			wait .5;
			continue;
		}

		//noticed when didn't check the current movement - guys would jump out of cover to a kneal (which is default for stopping on the run )			
		else if ( dist2rd_group > stopdist2rd )
		{
			if ( self.a.movement != "stop" )
			{
				dynamic_run_set( "stop" );
				wait .5;
			}
			continue;
		}

		else if ( dist2rd > jogdist2rd )
		{
			dynamic_run_set( "jog" );
			wait .5;
			continue;
		}
	}
}

stop_dynamic_run_speed()
{
	self endon( "start_dynamic_run_speed" );
	self endon( "death" );

	self stop_dynamic_run_speed_wait();

	if ( !self.dontChangeMovePlaybackRate )
		self.moveplaybackrate = self.old_moveplaybackrate;

	if ( IsDefined( level.scr_anim[ "generic" ][ "DRS_run" ] ) )
	{
		if ( IsArray( level.scr_anim[ "generic" ][ "DRS_run" ] ) )
			self set_generic_run_anim_array( "DRS_run" );
		else
			self set_generic_run_anim( "DRS_run" );
	}
	else
		self clear_run_anim();

	self notify( "stop_loop" );
	self ent_flag_clear( "dynamic_run_speed_stopping" );
	self ent_flag_clear( "dynamic_run_speed_stopped" );
}

stop_dynamic_run_speed_wait()
{
	level endon( "_stealth_spotted" );
	self waittill( "stop_dynamic_run_speed" );
}

dynamic_run_ahead_test( node, dist )
{
	//only nodes and structs dont have classnames - ents do
	if ( !isdefined( node.classname ) )
	{
		//only structs don't have types, nodes do
		if ( !isdefined( node.type ) )
			getfunc = maps\_spawner::get_target_structs;
		else
			getfunc = maps\_spawner::get_target_nodes;
	}
	else
		getfunc = maps\_spawner::get_target_ents;

	return maps\_spawner::go_to_node_wait_for_player( node, getfunc, dist );
}

dynamic_run_set( speed )
{
	if ( self.run_speed_state == speed )
		return;

	self.run_speed_state = speed;

	switch( speed )
	{
		case "sprint":
			if ( IsDefined( self.cqbwalking ) && self.cqbwalking && !self.dontChangeMovePlaybackRate )
				self.moveplaybackrate = 1;
			else if ( !self.dontChangeMovePlaybackRate )
				self.moveplaybackrate = 1.15;

			if ( IsArray( level.scr_anim[ "generic" ][ "DRS_sprint" ] ) )
				self set_generic_run_anim_array( "DRS_sprint" );
			else
				self set_generic_run_anim( "DRS_sprint" );
			//self AllowedStances( "stand", "crouch", "prone" );

			self notify( "stop_loop" );
			self anim_stopanimscripted();
			self ent_flag_clear( "dynamic_run_speed_stopped" );
			break;
		case "run":
			if ( !self.dontChangeMovePlaybackRate )
				self.moveplaybackrate = self.old_moveplaybackrate;

			if ( IsDefined( level.scr_anim[ "generic" ][ "DRS_run" ] ) )
			{
				if ( IsArray( level.scr_anim[ "generic" ][ "DRS_run" ] ) )
					self set_generic_run_anim_array( "DRS_run" );
				else
					self set_generic_run_anim( "DRS_run" );
			}
			else
				self clear_run_anim();
			//self AllowedStances( "stand", "crouch", "prone" );

			self notify( "stop_loop" );
			self anim_stopanimscripted();
			self ent_flag_clear( "dynamic_run_speed_stopped" );
			break;
		case "stop":
			self thread dynamic_run_speed_stopped();
			break;
		case "jog":
			if ( !self.dontChangeMovePlaybackRate )
				self.moveplaybackrate = self.old_moveplaybackrate;

			if ( IsDefined( level.scr_anim[ "generic" ][ "DRS_combat_jog" ] ) )
			{
				if ( IsArray( level.scr_anim[ "generic" ][ "DRS_combat_jog" ] ) )
					self set_generic_run_anim_array( "DRS_combat_jog" );
				else
					self set_generic_run_anim( "DRS_combat_jog" );
			}
			else
				self clear_run_anim();
			//self AllowedStances( "stand", "crouch", "prone" );

			self notify( "stop_loop" );
			self anim_stopanimscripted();
			self ent_flag_clear( "dynamic_run_speed_stopped" );
			break;
		case "crouch":
			assertmsg( "thought this was depricated...come grab me - mo" );
			/*
			if ( !self.dontChangeMovePlaybackRate )
				self.moveplaybackrate = self.old_moveplaybackrate;

			self clear_run_anim();
			//self AllowedStances( "crouch" );

			self notify( "stop_loop" );
			self anim_stopanimscripted();
			self ent_flag_clear( "dynamic_run_speed_stopped" );
			*/
			break;
	}
}

dynamic_run_speed_stopped()
{
	self endon( "death" );

	if ( self ent_flag( "dynamic_run_speed_stopped" ) )
		return;
	if ( self ent_flag( "dynamic_run_speed_stopping" ) )
		return;

	self endon( "stop_dynamic_run_speed" );

	self ent_flag_set( "dynamic_run_speed_stopping" );
	self ent_flag_set( "dynamic_run_speed_stopped" );

	self endon( "dynamic_run_speed_stopped" );

	//->turned this off because I think checking the current movement would fix whatever this was trying to
	//if( self ent_flag_exist( "_stealth_stance_handler" ) )
	//	self ent_flag_waitopen( "_stealth_stance_handler" );

	stop = "DRS_run_2_stop";
	self maps\_anim::anim_generic_custom_animmode( self, "gravity", stop );
	self ent_flag_clear( "dynamic_run_speed_stopping" );// this flag gets cleared if we endon

	//if he's already playing a looping animation - we can assume its part of level logic and 
	//it makes sense not to play a stopping animation or play dialogue to tell you to catch up
	if ( IsDefined( self.loops ) && self.loops > 0 )
		return;

	while ( self ent_flag( "dynamic_run_speed_stopped" ) )
	{
		//->turned this off because I think checking the current movement would fix whatever this was trying to
		//if( self ent_flag_exist( "_stealth_stance_handler" ) )
		//	self ent_flag_waitopen( "_stealth_stance_handler" ); 

		idle = "DRS_stop_idle";
		self thread maps\_anim::anim_generic_loop( self, idle );

		if ( IsDefined( level.scr_anim[ "generic" ][ "signal_go" ] ) )
			self handsignal( "go" );

		wait RandomFloatRange( 12, 20 );

		if ( self ent_flag_exist( "_stealth_stance_handler" ) )
			self ent_flag_waitopen( "_stealth_stance_handler" );

		self notify( "stop_loop" );

		if ( !self ent_flag( "dynamic_run_speed_stopped" ) )
			return;

		if ( IsDefined( level.dynamic_run_speed_dialogue ) )
		{
			string = random( level.dynamic_run_speed_dialogue );
			level thread radio_dialogue_queue( string );
		}

		if ( IsDefined( level.scr_anim[ "generic" ][ "signal_go" ] ) )
			self handsignal( "go" );
	}
}

g_speed_get_func()
{
	return Int( GetDvar( "g_speed" ) );
}

g_speed_set_func( goalspeed )
{
	SetSavedDvar( "g_speed", Int( goalspeed ) );
}

movespeed_get_func()
{
	return self.movespeedscale;
}

movespeed_set_func( scale )
{
	self.movespeedscale = scale;
	self SetMoveSpeedScale( scale );
}

autosave_tactical_setup()
{
	if ( flag_exist( "autosave_tactical_player_nade" ) )
		return;

	flag_init( "autosave_tactical_player_nade" );
	level.autosave_tactical_player_nades = 0;
	NotifyOnCommand( "autosave_player_nade", "+frag" );
	NotifyOnCommand( "autosave_player_nade", "-smoke" );
	NotifyOnCommand( "autosave_player_nade", "+smoke" );

	array_thread( level.players, ::autosave_tactical_grenade_check );
}

autosave_tactical_grenade_check()
{
	while ( 1 )
	{
		//this one hit's as soon as the button is pressed - that's why we want
		//to set the flag here and not after the grenade has left the hand
		//with "grenade fire" 
		self waittill( "autosave_player_nade" );
		flag_set( "autosave_tactical_player_nade" );

		self waittill( "grenade_fire", grenade );
		thread autosave_tactical_grenade_check_dieout( grenade );
	}
}

autosave_tactical_grenade_check_dieout( grenade )
{
	level.autosave_tactical_player_nades++;
	grenade waittill_notify_or_timeout( "death", 10 );
	level.autosave_tactical_player_nades--;

	//give stealth a chance to notify of any issues because of the grenade before we clear the flag
	//so that the system checking for saving the game can verify those notifies first
	waittillframeend;

	if ( !level.autosave_tactical_player_nades )
		flag_clear( "autosave_tactical_player_nade" );
}

autosave_tactical_proc()
{
	level notify( "autosave_tactical_proc" );
	level endon( "autosave_tactical_proc" );

	level thread notify_delay( "kill_save", 5 );
	level endon( "kill_save" );

	level endon( "autosave_tactical_player_nade" );
	if ( flag( "autosave_tactical_player_nade" ) )
	{
		flag_waitopen_or_timeout( "autosave_tactical_player_nade", 4 );

		//we still have nades?	
		if ( flag( "autosave_tactical_player_nade" ) )
			return;
	}

	enemies = GetAIArray( "axis" );
	foreach ( ai in enemies )
	{
		if ( IsDefined( ai.enemy ) && IsPlayer( ai.enemy ) )
			return;
	}

	waittillframeend;// give endon's a chance to register
	autosave_by_name();
}

music_play_internal_stop_with_fade_then_call( name, fade_time, timescale, overrideCheat )
{
	music_stop( fade_time );

	level endon( "stop_music" );

	wait fade_time;
	thread music_play( name, undefined, timescale, overrideCheat );
}

music_loop_internal_stop_with_fade_then_call( name, length, fade_time, timescale, overrideCheat, stop_for_stealth )
{
	music_stop( fade_time );

	level endon( "stop_music" );

	wait fade_time;
	thread music_loop_internal( name, length, undefined, timescale, overrideCheat, stop_for_stealth );
}

music_loop_internal( name, post_music_delay, fade_time, timescale, overrideCheat, stop_for_stealth )
{
	if ( IsDefined( fade_time ) && fade_time > 0 )
	{
		thread music_loop_internal_stop_with_fade_then_call( name, post_music_delay, fade_time, timescale, overrideCheat, stop_for_stealth );
		return;
	}
	music_stop();

	level endon( "stop_music" );

	MusicPlayWrapper( name, timescale, overrideCheat );

	if ( IsDefined( stop_for_stealth ) && stop_for_stealth == true && flag_exist( "_stealth_spotted" ) )
	{
		level endon( "_stealth_spotted" );
		thread music_loop_stealth_pause( name, post_music_delay, fade_time );
	}

	delay = musicLength( name );
	
	if ( !isdefined( post_music_delay ) )
		post_music_delay = 1;
		
	if ( post_music_delay <= 10 )
	{
		delay += post_music_delay;
	}
	
	wait delay;
	music_loop( name, post_music_delay, fade_time, timescale, overrideCheat );
}

music_loop_stealth_pause( name, length, fade_time )
{
	level endon( "stop_music" );

	flag_wait( "_stealth_spotted" );
	MusicStop( .5 );

	while ( flag( "_stealth_spotted" ) )
	{
		flag_waitopen( "_stealth_spotted" );
		wait 1;
	}

	thread music_loop( name, length, fade_time );
}

DoSlide( slideModel, allowedAcceleration, dampening )
{
	self endon( "death" );
	self endon( "stop_sliding" );

	player = self;

	entNum = undefined;
	/#
	entNum = slidemodel getEntNum();
	#/

	
	while ( 1 )
	{
		movement = player GetNormalizedMovement();
		forward = AnglesToForward( player.angles );
		right = AnglesToRight( player.angles );

		movement = ( movement[ 1 ] * right[ 0 ] + movement[ 0 ] * forward[ 0 ], movement[ 1 ] * right[ 1 ] + movement[ 0 ] * forward[ 1 ], 0 );

		// maybe we should plant movement to be perpendicular to ground normal?

		slideModel.slideVelocity += movement * allowedAcceleration;

		wait .05;

		slideModel.slideVelocity *= 1 - dampening;
	}
}

kill_deathflag_proc( time )
{
	self endon( "death" );
	if ( IsDefined( time ) )
		wait( RandomFloat( time ) );

	PlayFXOnTag( getfx( "flesh_hit" ), self, "tag_eye" );
	self Kill( level.player.origin );
}

update_rumble_intensity( player, rumble )
{
	self endon( "death" );
	
	rumble_playing = false;
	
	for ( ;; )
	{
		// There is a code bug where if rumbles are played on the first frame, and then you quit and resume from the beginning-of-level save,
		// the rumble may not stop correctly.  To work around this, we don't play on the first frame.  GetTime() on the first frame will be
		// 300, which is (NUM_SETTLE_FRAMES + 1) * FRAME_MSEC
		
		if ( self.intensity > 0.0001 && GetTime() > 300 )
		{
			if ( !rumble_playing )
			{
				self PlayRumbleLoopOnEntity( rumble );
				rumble_playing = true;
			}
		}
		else
		{
			if ( rumble_playing )
			{
				self StopRumble( rumble );
				rumble_playing = false;
			}			
		}
				
		height = 1 - self.intensity;
		height *= 1000;
		self.origin = (player GetEye()) + ( 0, 0, height );
		/#
		if( is_coop() )
			PrintLn( "^3Warning! Using get_rumble_ent will cause the same rumbles to apply to all of the coop players!" );
		#/
		wait( 0.05 );
	}
}

start_glow( model )
{
	ent = Spawn( "script_model", self.origin );
	self.glow_model = ent;
	ent.angles = self.angles;
	ent SetModel( model );
	ent endon( "death" );
	self waittill( "death" );
	ent Delete();
}

blend_default_dof( progress, start, end )
{
	foreach ( key, value in level.dofDefault )
	{
		level.dofDefault[ key ] = start[ key ] * ( 1 - progress ) + end[ key ] * progress;
	}
}

process_blend( func, caller, var1, var2, var3 )
{
	waittillframeend;// wait for the blend settings to get set;
	AssertEx( IsDefined( self.time ), "Blend needs a .time set to know how long to blend over." );
	if ( !isdefined( self.start ) )
		self.start = 0;
	if ( !isdefined( self.end ) )
		self.end = 1;
	if ( !isdefined( self.base ) )
		self.base = 0;

	frames = self.time * 20;
	range = self.end - self.start;

	if ( IsDefined( var3 ) )
	{
		for ( i = 0; i <= frames; i++ )
		{
			value = self.base + ( i * range / frames );
			caller thread [[ func ]]( value, var1, var2, var3 );
			wait( 0.05 );
		}
	}
	else
	if ( IsDefined( var2 ) )
	{
		for ( i = 0; i <= frames; i++ )
		{
			value = self.base + ( i * range / frames );
			caller thread [[ func ]]( value, var1, var2 );
			wait( 0.05 );
		}
	}
	else
	if ( IsDefined( var1 ) )
	{
		for ( i = 0; i <= frames; i++ )
		{
			value = self.base + ( i * range / frames );
			caller thread [[ func ]]( value, var1 );
			wait( 0.05 );
		}
	}
	else
	{
		for ( i = 0; i <= frames; i++ )
		{
			value = self.base + ( i * range / frames );
			caller thread [[ func ]]( value );
			wait( 0.05 );
		}
	}
}

add_trace_fx_proc( name )
{
	waittillframeend;// give the scripts that set the params a chance to do so
	if ( !isdefined( level.trace_fx ) )
	{
		level.trace_fx = [];
	}

	AssertEx( IsDefined( self.surface ), "Tracefx for " + name + " has no .surface" );
	if ( !isdefined( level.trace_fx ) )
	{
		level.trace_fx[ name ] = [];
	}

	if ( IsDefined( self.fx ) )
		level.trace_fx[ name ][ self.surface ][ "fx" ] = self.fx;

	if ( IsDefined( self.fx_array ) )
		level.trace_fx[ name ][ self.surface ][ "fx_array" ] = self.fx_array;

	if ( IsDefined( self.sound ) )
		level.trace_fx[ name ][ self.surface ][ "sound" ] = self.sound;

	if ( IsDefined( self.rumble ) )
		level.trace_fx[ name ][ self.surface ][ "rumble" ] = self.rumble;

	if ( !isdefined( level.trace_fx[ name ][ "default" ] ) )
	{
		level.trace_fx[ name ][ "default" ] = level.trace_fx[ name ][ self.surface ];
	}
}

put_interactive_in_volume( toy )
{
	ent = SpawnStruct();
	PreCacheModel( toy.model );
	ent.toy_model = toy.model;
	ent.origin = toy.origin;
	ent.angles = toy.angles;
	ent.script_noteworthy = toy.script_noteworthy;
	ent.target = toy.target;
	ent.targetname = toy.targetname;

	self.interactives[ self.interactives.size ] = ent;

	toy Delete();
}

put_toy_in_volume( toy )
{
	ent = SpawnStruct();
	PreCacheModel( toy.model );
	ent.toy_model = toy.model;
	ent.origin = toy.origin;
	ent.angles = toy.angles;
	ent.script_noteworthy = toy.script_noteworthy;
	ent.script_linkto = toy.script_linkto;
	ent.targetname = toy.targetname;
	ent.target = toy.target;
	ent.destructible_type = toy.destructible_type;
	ent.script_noflip = toy.script_noflip;
	
    toy precache_destructible( toy.destructible_type );
	self.destructibles[ self.destructibles.size ] = ent;

	toy notify ( "masking_destructible" );
	toy Delete();
}

get_color_info_from_trigger()
{
	/#
	if ( IsDefined( self.script_color_allies ) )
	{
		AssertEx( !isdefined( self.script_color_axis ), "trigger had axis and allies" );
	}
	else
	if ( IsDefined( self.script_color_axis ) )
	{
		AssertEx( !isdefined( self.script_color_allies ), "trigger had axis and allies" );
	}
	else
		AssertMsg( "Trigger didnt have allies or axis" );
	#/

	team = "allies";
	if ( IsDefined( self.script_color_axis ) )
		team = "axis";

	team = maps\_colors::get_team( team );// to cast team3

	colorCodes = [];
	if ( team == "allies" )
	{
		array = maps\_colors::get_colorcodes_from_trigger( self.script_color_allies, "allies" );
		colorCodes = array[ "colorCodes" ];
	}
	else
	{
		array = maps\_colors::get_colorcodes_from_trigger( self.script_color_axis, "axis" );
		colorCodes = array[ "colorCodes" ];
	}

	AssertEx( colorCodes.size, "Tried to get codes from trigger but there were none" );

	info = [];
	info[ "team" ] = team;
	info[ "codes" ] = colorCodes;

	return info;
}


delayThread_proc( func, timer, param1, param2, param3, param4, param5, param6 )
{
	self endon( "death" );

	wait( timer );
	if ( !IsDefined( param1 ) )
	{
		assertex( !isdefined( param2 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param3 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param4 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param5 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param6 ), "Delaythread does not support vars after undefined." );
		thread [[ func ]]();
	}
	else
	if ( !IsDefined( param2 ) )
	{
		assertex( !isdefined( param3 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param4 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param5 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param6 ), "Delaythread does not support vars after undefined." );
		thread [[ func ]]( param1 );
	}
	else
	if ( !IsDefined( param3 ) )
	{
		assertex( !isdefined( param4 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param5 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param6 ), "Delaythread does not support vars after undefined." );
		thread [[ func ]]( param1, param2 );
	}
	else
	if ( !IsDefined( param4 ) )	
	{
		assertex( !isdefined( param5 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param6 ), "Delaythread does not support vars after undefined." );
		thread [[ func ]]( param1, param2, param3 );
	}
	else
	if ( !IsDefined( param5 ) )	
	{
		assertex( !isdefined( param6 ), "Delaythread does not support vars after undefined." );
		thread [[ func ]]( param1, param2, param3, param4 );
	}
	else
	if ( !IsDefined( param6 ) )
	{
		thread [[ func ]]( param1, param2, param3, param4, param5 );
	}
	else
	{
		thread [[ func ]]( param1, param2, param3, param4, param5, param6 );
	}
}

add_wait_asserter()
{
	level notify( "kill_add_wait_asserter" );
	level endon( "kill_add_wait_asserter" );

	// wait until the end of the frame
	for ( i = 0; i < 20; i++ )
	{
		waittillframeend;
	}
	AssertMsg( "Added a wait or func and then didn't do_wait immediately." );
}

update_battlechatter_hud()
{
	/#
	if ( getdvar( "loc_warnings", 0 ) == "1" )
		return;

	if ( getdvar( "debug_hud" ) != "" )
		return;

	if ( !isdefined( level.bcs_hud ) )
	{
		x = -50;
		y = 460;
		x_offset = 22;

		hud = newHudElem();
		hud.x = x;
		hud.y = y;
		hud.color = ( 0.4, 0.55, 0.9 );
		level.bcs_hud = hud;
	}

	msg = "BCS enabled:           ";
	count = 0;
	
	// just gonna ignore team3 and neutral since it doesnt apply often
	teams = [];
	teams[ "allies" ] = level.battlechatter[ "allies" ];
	teams[ "axis" ] = level.battlechatter[ "axis" ];
	
	foreach ( team, val in teams )
	{
		if ( val )
		{
			msg = msg + team + " ";
		}
		count++;
	}
	
	if ( count )
	{
		level.bcs_hud settext( msg );
	}
	else
	{
		level.bcs_hud settext( "BCS disabled" );
	}
	#/
}

compareSizesFx( org, array, dist, compareFunc )
{
	if ( !array.size )
		return undefined;
	if ( IsDefined( dist ) )
	{
		struct = undefined;
		keys = GetArrayKeys( array );
		for ( i = 0; i < keys.size; i++ )
		{
			newdist = Distance( array[ keys[ i ] ].v[ "origin" ], org );
			if ( [[ compareFunc ]]( newDist, dist ) )
				continue;
			dist = newdist;
			struct = array[ keys[ i ] ];
		}
		return struct;
	}

	keys = GetArrayKeys( array );
	struct = array[ keys[ 0 ] ];
	dist = Distance( struct.v[ "origin" ], org );
	for ( i = 1; i < keys.size; i++ )
	{
		newdist = Distance( array[ keys[ i ] ].v[ "origin" ], org );
		if ( [[ compareFunc ]]( newDist, dist ) )
			continue;
		dist = newdist;
		struct = array[ keys[ i ] ];
	}
	return struct;
}

waittill_triggered_current()
{
	while ( true )
	{
		self waittill ( "trigger", other );
		waittillframeend;
		if( other.currentnode == self )
			return other;
	}
}

add_trigger_func_thread()
{
    self.trigger_functions = [];
    
//    if ( !IsDefined( self.classname ) )
//    	other = waittill_triggered_current();  // vehicle nodes don't have classname and they need to have an extra check to make sure it's a valid trigger event.
//	else 
	    self waittill ( "trigger", other );
	    
    trigger_functions = self.trigger_functions;
    self.trigger_functions = undefined;
    foreach( function in trigger_functions )
        thread [[ function ]] ( other );
}

//{NOT_IN_SHIP
objective_recon( obj )
{
	if (!is_default_start())
		return;		// times only valid when not using debug_start to jump into middle of level
	time = get_leveltime();
	dtime = time;
	if (isdefined(level.recon_objective_lasttime))
		dtime = time - level.recon_objective_lasttime;
	level.recon_objective_lasttime = time;
    ReconEvent( "script_objective: objective %d, leveltime %d, deltatime %d", obj, time, dtime  );
    /#
    println("script_objective: objective "+obj+", leveltime "+time+", deltatime "+dtime);
    #/
}
//}NOT_IN_SHIP

//{NOT_IN_SHIP
mission_recon( success )
{
	if (is_default_start())
	{	// times only valid when not using debug_start to jump into middle of level
		if (!isdefined(success))
			success = true;
		time = get_leveltime();
		leveltime = time;	// TODO: check if we can clean out one of these
	    ReconEvent( "script_level: leveltime %d, deltatime %d, success %d", leveltime, time, success );
	    /#
	    println("script_level: leveltime "+time+" success "+success);
	    #/
	}
}
//}NOT_IN_SHIP

//{NOT_IN_SHIP
get_leveltime()
{
	return GetLevelTicks()*0.05;
}
//}NOT_IN_SHIP
