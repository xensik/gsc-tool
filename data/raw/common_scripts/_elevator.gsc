//#include maps\mp\_utility;
#include common_scripts\utility;

init()
{
	if ( getdvar( "scr_elevator_disabled" ) == "1" )
		return;

	// skip if no elevators in this level
	elevator_groups = getentarray( "elevator_group", "targetname" );
	if ( !isdefined( elevator_groups ) )
		return;
	if ( !elevator_groups.size )
		return;

	// Press and hold &&1 to call elevator.
	precacheString( &"ELEVATOR_CALL_HINT" );
	// Press and hold &&1 to use elevator.
	precacheString( &"ELEVATOR_USE_HINT" );
	// Press and hold &&1 to select floor.
	precacheString( &"ELEVATOR_FLOOR_SELECT_HINT" );

	precacheMenu( "elevator_floor_selector" );

	thread elevator_update_global_dvars();

	// find and build all elevators in the level
	level.elevators = [];

	// elevator construction dvars:
	// vertical units for "call button" to link near by elevator per floor
	level.elevator_callbutton_link_v = elevator_get_dvar_int( "scr_elevator_callbutton_link_v", "96" );
	// horizontal units for "call button" to link near by elevator per floor
	level.elevator_callbutton_link_h = elevator_get_dvar_int( "scr_elevator_callbutton_link_h", "256" );

	build_elevators();
	position_elevators();
	elevator_call();

	if ( !level.elevators.size )
		return;

	foreach ( elevator in level.elevators )
	{
		elevator thread elevator_think();
		elevator thread elevator_sound_think();
	}

	thread elevator_debug();
}

elevator_update_global_dvars()
{
	while ( 1 )
	{
		level.elevator_accel			 = elevator_get_dvar( "scr_elevator_accel", "0.2" ); 				// acceleration time in seconds
		level.elevator_decel			 = elevator_get_dvar( "scr_elevator_decel", "0.2" ); 				// deceleration time in seconds
		level.elevator_music			 = elevator_get_dvar_int( "scr_elevator_music", "1" ); 				// elevator music
		level.elevator_speed			 = elevator_get_dvar_int( "scr_elevator_speed", "96" ); 			// units per second
		level.elevator_innerdoorspeed	 = elevator_get_dvar_int( "scr_elevator_innerdoorspeed", "14" ); 	// inner door speed
		level.elevator_outterdoorspeed 	 = elevator_get_dvar_int( "scr_elevator_outterdoorspeed", "16" ); 	// outter door speed
		level.elevator_return			 = elevator_get_dvar_int( "scr_elevator_return", "0" ); 			// 1: elevator returns to original floor
		level.elevator_waittime			 = elevator_get_dvar_int( "scr_elevator_waittime", "6" ); 			// wait in seconds before closing door
		level.elevator_aggressive_call	 = elevator_get_dvar_int( "scr_elevator_aggressive_call", "0" ); 	// calls all available elevators to floor
		level.elevator_debug			 = elevator_get_dvar_int( "debug_elevator", "0" ); 					// 2: full 1: simple, 0: debug off

		// mp & sp default differences:
		if ( isSP() )
		{
			level.elevator_motion_detection	 = elevator_get_dvar_int( "scr_elevator_motion_detection", "0" );// calls elevators via motion detection
		}
		else
		{
			level.elevator_motion_detection = elevator_get_dvar_int( "scr_elevator_motion_detection", "1" );// calls elevators via motion detection
		}

		wait 1;
	}
}

//==========================================================================//
//							===	ELEVATOR LOGIC ===							//
//==========================================================================//

elevator_think()
{
	// self is elevator, self.e[]
	self elevator_fsm( "[A]" );
}

elevator_call()
{
	foreach ( callbutton in level.elevator_callbuttons )
		callbutton thread monitor_callbutton();
}

floor_override( inside_trig )
{
	self endon( "elevator_moving" );

	self.floor_override = 0;
	self.overrider = undefined;

	while ( 1 )
	{
		inside_trig waittill( "trigger", player );
		self.floor_override = 1;
		self.overrider = player;
		break;
	}
	self notify( "floor_override" );
}

elevator_fsm( state )
{
	/*				finite state machine
	
	state A: 	rest
	state B: 	closing doors - interrupt threaded
	state C: 	opening doors
	state D: 	moving elevator
	?1: 		if not resting at initial floor
			
				.-------delay-------.
				|					|
			  	?1					V
	start --> [A] --inside_trig--> [B] --delay--> [D]
				^					| 			   |
				|				door_trig		   |
				|		            |			   |
              	|					V			   |
				'-----delay------- [C] <---delay---'
	*/

	/* self is elevator, self.e[] */

	self.eState = state;

	door_trig = self get_housing_door_trigger();		// triggers door interrupt
	inside_trig = self get_housing_inside_trigger();	// presence

	while ( 1 )
	{
		//state A: rest
		if ( self.eState == "[A]" )
		{
			// ?1: if not resting at initial floor
			if ( level.elevator_return && ( self get_curFloor() != self get_initFloor() ) )
			{
				self.moveto_floor = self get_initFloor();
				self thread floor_override( inside_trig );
				self waittill_or_timeout( "floor_override", level.elevator_waittime );

				if ( self.floor_override && isdefined( self.overrider ) && isPlayer( self.overrider ) )
					self get_floor( self.overrider );

				self.eState = "[B]";
				continue;
			}

			// wait for player use trigger
			while ( 1 )
			{
				// if elevator already has destination but interrupted, it should continue previous order
				if ( self.moveto_floor == self get_curFloor() )
					param = inside_trig discrete_waittill( "trigger" );
				else
					param = "elevator_called";	// as if called onto the destination floor

				// elevator call hack
				if ( isString( param ) && ( param == "elevator_called" ) && ( self.moveto_floor != self get_curFloor() ) )
				{
					self.eState = "[B]";
					break;
				}

				if ( isdefined( param ) && isPlayer( param ) && isAlive( param ) )
				{
					isTouching_trigger = ( param istouching( inside_trig ) );
					isTouching_motion_trigger = ( isdefined( inside_trig.motion_trigger ) && param istouching( inside_trig.motion_trigger ) );
					player_isTouching_trigger = ( isTouching_trigger || isTouching_motion_trigger );

					if ( player_isTouching_trigger )
					{
						player = param;
						self get_floor( player );

						if ( self.moveto_floor == self get_curFloor() )
							continue;

						self.eState = "[B]";
						break;
					}
				}
			}
		}

		//state B: closing doors - interrupt threaded
		if ( self.eState == "[B]" )
		{
			self thread elevator_interrupt( door_trig );
			floor_num = self get_curFloor();

			// call to close doors
			self thread close_inner_doors();
			self thread close_outer_doors( floor_num );

			self waittill_any( "closed_inner_doors", "interrupted" );  	// Wait for inner doors to close for the safty of our valued customers.

			if ( self.elevator_interrupted )
			{
				self.eState = "[C]";
				continue;
			}

			self.eState = "[D]";
			continue;
		}

		//state C: opening doors
		if ( self.eState == "[C]" )
		{
			floor_num = self get_curFloor();

			self thread open_inner_doors();
			self thread open_outer_doors( floor_num );

			self waittill( "opened_floor_" + floor_num + "_outer_doors" );

			if ( self.elevator_interrupted )
			{
				self.eState = "[B]";
				continue;
			}

			self.eState = "[A]";
			continue;
		}

		//state D: moving elevator
		if ( self.eState == "[D]" )
		{
			assertex( isdefined( self.moveto_floor ), "Missing destination floor number" );

			if ( self.moveto_floor != self get_curFloor() )
			{
				self thread elevator_move( self.moveto_floor );
				self waittill( "elevator_moved" );
			}

			self.eState = "[C]";
			continue;
		}
	}
}

monitor_callbutton()
{
	while ( 1 )
	{
		// call button used by player
		player = self discrete_waittill( "trigger" );

		call_floor = undefined;
		call_elevators = [];
		// fake loop, always loop only once
		foreach ( idx, linked_elevators in self.e )
		{
			call_floor = idx;
			call_elevators = linked_elevators;
		}
		assert( isdefined( call_floor ) && isdefined( call_elevators ) && call_elevators.size );

		elevator_called = 0;

		// prefilter elevators to see if any already at this floor
		foreach ( elevator in call_elevators )
		{
			moving = elevator elevator_floor_update();

			// if in non-aggressive mode; this elevator is already stationary at the requested floor, we skip!
			if ( !level.elevator_aggressive_call && !moving )
			{
				if ( elevator get_curFloor() == call_floor )
				{
					elevator_called = 1;
					call_elevators = [];
					break;
				}
			}
		}

		// check all elevators to see if any can be called to this floor		
		foreach ( elevator in call_elevators )
		{
			if ( elevator.eState == "[A]" )
			{
				// call only elevators in a state of rest [A]
				elevator call_elevator( call_floor );

				elevator_called = 1;

				// aggressive call
				if ( !level.elevator_aggressive_call )
					break;
			}
		}

		if ( elevator_called )
			self playsound( "elev_bell_ding" );
	}
}

call_elevator( call_floor )
{
	self.moveto_floor = call_floor;

	// call elevator via trigger hack
	inside_trigger = self get_housing_inside_trigger();
	inside_trigger notify( "trigger", "elevator_called" );
	if ( level.elevator_motion_detection )
		inside_trigger.motion_trigger notify( "trigger", "elevator_called" );
}

// opens menu to select floors
get_floor( player )
{
	// skips popup menu if only two floors present
	bifloor = self get_outer_doorsets();
	if ( bifloor.size == 2 )
	{
		curFloor = self get_curFloor();
		self.moveto_floor = !curFloor;
		return;
	}

	player openpopupmenu( "elevator_floor_selector" );
	player setClientDvar( "player_current_floor", self get_curFloor() );

	while ( 1 )
	{
		player waittill( "menuresponse", menu, response );

		if ( menu == "elevator_floor_selector" )
		{
			if ( response != "none" )
				self.moveto_floor = int( response );

			break;
		}
	}
}

elevator_interrupt( door_trig )
{
	self notify( "interrupt_watch" );
	level notify( "elevator_interior_button_pressed" );
	self endon( "interrupt_watch" );	// no duplicate interrupts
	self endon( "elevator_moving" );

	self.elevator_interrupted = 0;
	wait 0.5;// buffer time to have the door jitter...
	door_trig waittill( "trigger", player );

	/*while ( 1 )
	{
		wait 0.5; // buffer time to have the door jitter... realisticaly, im serious!
		
		door_trig waittill( "trigger", player );			
		if ( isdefined( player ) && isPlayer( player ) )
			break;
	}*/

	self notify( "interrupted" );
	self.elevator_interrupted = 1;

	//self elevator_fsm( "[C]" );
}

// returns if elevator is moving, also updates the floor number if not moving
elevator_floor_update()
{
	mainframe = self get_housing_mainframe();
	cur_pos = mainframe.origin;

	moving = 1;
	foreach ( idx, eFloor in self get_outer_doorsets() )
	{
		floor_pos = self.e[ "floor" + idx + "_pos" ];
		if ( cur_pos == floor_pos )
		{
			self.e[ "current_floor" ] = idx;
			moving = 0;
		}
	}

	return moving;
}

elevator_sound_think()
{
	// self is elevator, self.e[]
	// play elevator sounds on notify of behavior

	// always play musak
	musak_model = self get_housing_musak_model();
	
	if ( level.elevator_music && isdefined( musak_model ) )
		musak_model playloopsound( "elev_musak_loop" );

	self thread listen_for ( "closing_inner_doors" );
	self thread listen_for ( "opening_inner_doors" );
	self thread listen_for ( "closed_inner_doors" );
	self thread listen_for ( "opened_inner_doors" );

	foreach ( idx, eFloor in self get_outer_doorsets() )
	{
		self thread listen_for ( "closing_floor_" + idx + "_outer_doors" );
		self thread listen_for ( "opening_floor_" + idx + "_outer_doors" );
		self thread listen_for ( "closed_floor_" + idx + "_outer_doors" );
		self thread listen_for ( "opened_floor_" + idx + "_outer_doors" );
	}

	self thread listen_for ( "interrupted" );
	//self thread listen_for( "interrupt_watch" );
	self thread listen_for ( "elevator_moving" );
	self thread listen_for ( "elevator_moved" );
}

/*
-elev_musak_loop,,music/mx_musak_stolen_elev_proc1.wav,1,1,foley,1,1,120,500,effects1,,,rlooping,,all_mp
-elev_door_open,,events/elev_door_open1.wav,1,1,foley,0.95,1.05,120,2500,voice,,,,,all_mp
-elev_door_close,,events/elev_door_close1.wav,1,1,foley,0.95,1.05,120,2500,voice,,,,,all_mp
-elev_door_interupt,,events/elev_door_interupt1.wav,1,1,foley,0.95,1.05,120,2500,voice,,,,,all_mp
-elev_bell_ding,,events/elev_bell_ding1.wav,1,1,foley,1,1,120,2500,voice,,,,,all_mp
-elev_run_start,,events/elev_run_start01.wav,1,1,foley,1,1,120,500,voice,,,,,all_mp
-elev_run_loop,,events/elev_run_loop01.wav,1,1,foley,1,1,120,500,voice,,,rlooping,,all_mp
-elev_run_end,,events/elev_run_stop01.wav,1,1,foley,1,1,120,500,voice,,,,,all_mp
*/

listen_for ( msg )
{
	while ( 1 )
	{
		self waittill( msg );
		mainframe = self get_housing_mainframe();

		if ( issubstr( msg, "closing_" ) )
			mainframe playsound( "elev_door_close" );

		if ( issubstr( msg, "opening_" ) )
			mainframe playsound( "elev_door_open" );

		if ( msg == "elevator_moving" )
		{
			mainframe playsound( "elev_run_start" );
			mainframe playloopsound( "elev_run_loop" );
		}

		if ( msg == "interrupted" )
			mainframe playsound( "elev_door_interupt" );

		if ( msg == "elevator_moved" )
		{
			mainframe stoploopsound( "elev_run_loop" );
			mainframe playsound( "elev_run_end" );
			mainframe playsound( "elev_bell_ding" );
		}

		//if ( isdefined( level.players[0] ) && level.elevator_debug )
		//	level.players[0] iprintln( "(e" + self.e[ "id" ] + ") " + msg );
	}
}

//==========================================================================//
//							===	MOVEMENTS ===								//
//==========================================================================//

// position elevators
position_elevators()
{
	// closing all outer doors on floors elevator isnt at
	foreach ( e, elevator in level.elevators )
	{
		elevator.moveto_floor = elevator get_curFloor();

		foreach ( floor_num, outer_doorset in elevator get_outer_doorsets() )
		{
			if ( elevator get_curFloor() != floor_num )
				elevator thread close_outer_doors( floor_num );
		}
	}
}

elevator_move( floor_num )
{
	// self is elevator, self.e[]
	self notify( "elevator_moving" );
	self endon( "elevator_moving" );

	mainframe = self get_housing_mainframe();
	delta_vec = self.e[ "floor" + floor_num + "_pos" ] - mainframe.origin;

	speed = level.elevator_speed;
	dist = abs( distance( self.e[ "floor" + floor_num + "_pos" ], mainframe.origin ) );
	moveTime = dist / speed;

	// move housing:
	mainframe moveTo( mainframe.origin + delta_vec, moveTime, moveTime * level.elevator_accel, moveTime * level.elevator_decel );

	// move doors and triggers and other script models
	foreach ( part in self get_housing_children() )
	{
		moveto_pos = part.origin + delta_vec;

		if ( !issubstr( part.classname, "trigger_" ) )
			part moveTo( moveto_pos, moveTime, moveTime * level.elevator_accel, moveTime * level.elevator_decel );
		else
			part.origin = moveto_pos;
	}

	// making sure elevator housing gets to destination floor
	self waittill_finish_moving( mainframe, self.e[ "floor" + floor_num + "_pos" ] );

	self notify( "elevator_moved" );
}

close_inner_doors()
{
	// self is elevator set
	self notify( "closing_inner_doors" );
	self endon( "closing_inner_doors" ); 						// when interrupted
	self endon( "opening_inner_doors" ); 						// when interrupted

	left_door = self get_housing_leftdoor();					// ent
	right_door = self get_housing_rightdoor();					// ent

	mainframe = self get_housing_mainframe();					// ent
	old_closed_pos = self get_housing_closedpos();				// vec
	closed_pos = ( old_closed_pos[ 0 ], old_closed_pos[ 1 ], mainframe.origin[ 2 ] );	// adjusted closed position after floor change

	speed = level.elevator_innerdoorspeed;						// scaler
	dist = abs( distance( left_door.origin, closed_pos ) );		// scaler
	moveTime = dist / speed;										// scaler

	left_door moveTo( closed_pos, moveTime, moveTime * 0.1, moveTime * 0.25 );
	right_door moveTo( closed_pos, moveTime, moveTime * 0.1, moveTime * 0.25 );

	self waittill_finish_moving( left_door, closed_pos, right_door, closed_pos );
	self notify( "closed_inner_doors" );
}

open_inner_doors()
{
	// self is elevator set
	self notify( "opening_inner_doors" );
	self endon( "opening_inner_doors" ); 								// when interrupted

	left_door = self get_housing_leftdoor();							// ent
	right_door = self get_housing_rightdoor();							// ent

	mainframe = self get_housing_mainframe();							// ent
	old_left_opened_pos = self get_housing_leftdoor_opened_pos();		// vec
	old_right_opened_pos = self get_housing_rightdoor_opened_pos();		// vec

	left_opened_pos = ( old_left_opened_pos[ 0 ], old_left_opened_pos[ 1 ], mainframe.origin[ 2 ] );
	right_opened_pos = ( old_right_opened_pos[ 0 ], old_right_opened_pos[ 1 ], mainframe.origin[ 2 ] );

	speed = level.elevator_innerdoorspeed;								// scaler
	dist = abs( distance( left_opened_pos, right_opened_pos ) * 0.5 );	// scaler
	moveTime = ( dist / speed ) * 0.5;										// scaler

	left_door moveTo( left_opened_pos, moveTime, moveTime * 0.1, moveTime * 0.25 );
	right_door moveTo( right_opened_pos, moveTime, moveTime * 0.1, moveTime * 0.25 );

	self waittill_finish_moving( left_door, left_opened_pos, right_door, right_opened_pos );
	self notify( "opened_inner_doors" );
}

// close outer elevator doors per floor
close_outer_doors( floor_num )
{
	// self is elevator set
	self notify( "closing_floor_" + floor_num + "_outer_doors" );
	self endon( "closing_floor_" + floor_num + "_outer_doors" ); 		// when interrupted
	self endon( "opening_floor_" + floor_num + "_outer_doors" ); 		// when interrupted

	left_door = self get_outer_leftdoor( floor_num );					// ent
	right_door = self get_outer_rightdoor( floor_num );					// ent

	left_opened_pos = self get_outer_leftdoor_openedpos( floor_num );	// vec
	closed_pos = self get_outer_closedpos( floor_num );					// vec

	speed = level.elevator_outterdoorspeed;								// scaler
	dist = abs( distance( left_opened_pos, closed_pos ) );				// scaler
	moveTime = dist / speed;												// scaler

	left_door moveTo( closed_pos, moveTime, moveTime * 0.1, moveTime * 0.25 );
	right_door moveTo( closed_pos, moveTime, moveTime * 0.1, moveTime * 0.25 );

	self waittill_finish_moving( left_door, closed_pos, right_door, closed_pos );
	self notify( "closed_floor_" + floor_num + "_outer_doors" );
}

// open outer elevator doors per floor
open_outer_doors( floor_num )
{
	// self is elevator set
	level notify( "elevator_doors_opening" );
	self notify( "opening_floor_" + floor_num + "_outer_doors" );
	self endon( "opening_floor_" + floor_num + "_outer_doors" ); 		// when interrupted

	left_door = self get_outer_leftdoor( floor_num );					// ent
	right_door = self get_outer_rightdoor( floor_num );					// ent

	left_opened_pos = self get_outer_leftdoor_openedpos( floor_num );	// vec
	right_opened_pos = self get_outer_rightdoor_openedpos( floor_num );	// vec
	closed_pos = self get_outer_closedpos( floor_num );					// vec

	speed = level.elevator_outterdoorspeed;								// scaler
	dist = abs( distance( left_opened_pos, closed_pos ) );				// scaler
	moveTime = ( dist / speed ) * 0.5;										// scaler

	left_door moveTo( left_opened_pos, moveTime, moveTime * 0.1, moveTime * 0.25 );
	right_door moveTo( right_opened_pos, moveTime, moveTime * 0.1, moveTime * 0.25 );

	self waittill_finish_moving( left_door, left_opened_pos, right_door, right_opened_pos );
	self notify( "opened_floor_" + floor_num + "_outer_doors" );
}

//==========================================================================//
//							===	BUILD ELEVATORS ===							//
//==========================================================================//

// builds elevators into 'level.elevators' struct array containing parts list
build_elevators()
{
	// triggers that enclose elevator, to distinguish between elevators
	elevator_groups = getentarray( "elevator_group", "targetname" );
	assertex( isdefined( elevator_groups ) && ( elevator_groups.size ), "Radiant: Missing elevator bounding origins" );

	elevator_housings = getentarray( "elevator_housing", "targetname" );
	assertex( isdefined( elevator_housings ) && ( elevator_housings.size >= elevator_groups.size ), "Fail! Missing the whole elevator, script_brushmodel with [targetname = elevator_housing] must be correctly placed" );

	// sets of elevator outter door prefabs placed
	elevator_doorsets = getentarray( "elevator_doorset", "targetname" );
	assertex( isdefined( elevator_doorsets ) && ( elevator_doorsets.size >= elevator_groups.size ), "Radiant: Missing elevator door(s)" );

	// build found elevators
	foreach ( elevator_bound in elevator_groups )
	{
		elevator_bound_end = getent( elevator_bound.target, "targetname" );

		min_max_xy = [];
		min_max_xy[ 0 ] = min( elevator_bound.origin[ 0 ], elevator_bound_end.origin[ 0 ] );// min_x
		min_max_xy[ 1 ] = max( elevator_bound.origin[ 0 ], elevator_bound_end.origin[ 0 ] );// max_x
		min_max_xy[ 2 ] = min( elevator_bound.origin[ 1 ], elevator_bound_end.origin[ 1 ] );// min_y
		min_max_xy[ 3 ] = max( elevator_bound.origin[ 1 ], elevator_bound_end.origin[ 1 ] );// max_y

		parts = spawnstruct();
		parts.e[ "id" ] = level.elevators.size;

		// === build elevator housing ===
		/*
			Elevator's mainframe brushmodel
			
			script_brushmodel targeting:
			"elevator_housing" -> left door -> right door -> door trigger -> inside trigger
				
			Housing is the body that moves between floors
		*/
		parts.e[ "housing" ] = [];
		parts.e[ "housing" ][ "mainframe" ] = [];

		foreach ( elevator_housing in elevator_housings )
		{
			if ( elevator_housing isInbound( min_max_xy ) )
			{
				parts.e[ "housing" ][ "mainframe" ][ parts.e[ "housing" ][ "mainframe" ].size ] = elevator_housing;

				if ( elevator_housing.classname == "script_model" )
					continue;

			if ( elevator_housing.code_classname == "light" )
					continue;

				inner_leftdoor = getent( elevator_housing.target, "targetname" );
				parts.e[ "housing" ][ "left_door" ] = inner_leftdoor;
				parts.e[ "housing" ][ "left_door_opened_pos" ] = inner_leftdoor.origin;

				inner_rightdoor = getent( inner_leftdoor.target, "targetname" );
				parts.e[ "housing" ][ "right_door" ] = inner_rightdoor;
				parts.e[ "housing" ][ "right_door_opened_pos" ] = inner_rightdoor.origin;

				inner_door_closed_pos = ( inner_leftdoor.origin - inner_rightdoor.origin ) * ( 0.5, 0.5, 0.5 ) + inner_rightdoor.origin;
				parts.e[ "housing" ][ "door_closed_pos" ] = inner_door_closed_pos;

				door_trigger = getent( inner_rightdoor.target, "targetname" );
				parts.e[ "housing" ][ "door_trigger" ] = door_trigger;

				inside_trigger = getent( door_trigger.target, "targetname" );
				parts.e[ "housing" ][ "inside_trigger" ] = inside_trigger;
				inside_trigger make_discrete_trigger();

				// for motion triggers
				inside_trigger.motion_trigger = spawn( "trigger_radius", elevator_housing.origin, 0, 64, 128 );
				assert( isdefined( inside_trigger.motion_trigger ) );
			}
		}
		assert( isdefined( parts.e[ "housing" ] ) );

		// === build elevator outer doorsets ===
		/*
			Elevator's outer door sets ( per floor ) are chained together from a script_origin 
			targeting to the left door, then left door targets to right door
			
			Outer door sets are bodies that only moves to open/close
		*/
		parts.e[ "outer_doorset" ] = [];
		foreach ( elevator_doorset in elevator_doorsets )
		{
			if ( elevator_doorset isInbound( min_max_xy ) )
			{
				
				// closed for lighting is for compiling lighting in the closed position rather than the open position. 
				door_starts_closed = isdefined( elevator_doorset.script_noteworthy ) && elevator_doorset.script_noteworthy == "closed_for_lighting";
		
				door_set_id = parts.e[ "outer_doorset" ].size;

				parts.e[ "outer_doorset" ][ door_set_id ] = [];
				parts.e[ "outer_doorset" ][ door_set_id ][ "door_closed_pos" ] = elevator_doorset.origin;

				leftdoor = getent( elevator_doorset.target, "targetname" );
				parts.e[ "outer_doorset" ][ door_set_id ][ "left_door" ] = leftdoor;
				parts.e[ "outer_doorset" ][ door_set_id ][ "left_door_opened_pos" ] = leftdoor.origin;

				rightdoor = getent( leftdoor.target, "targetname" );
				parts.e[ "outer_doorset" ][ door_set_id ][ "right_door" ] = rightdoor;
				parts.e[ "outer_doorset" ][ door_set_id ][ "right_door_opened_pos" ] = rightdoor.origin;
				
				//put them back into the would be positions 
				if( door_starts_closed )
				{
					left_door_vec = elevator_doorset.origin - leftdoor.origin;
					elevator_doorset.origin = leftdoor.origin;
					leftdoor.origin += left_door_vec;
					rightdoor.origin -= left_door_vec; 
					parts.e[ "outer_doorset" ][ door_set_id ][ "door_closed_pos" ] = elevator_doorset.origin;
					parts.e[ "outer_doorset" ][ door_set_id ][ "left_door_opened_pos" ] = leftdoor.origin;
					parts.e[ "outer_doorset" ][ door_set_id ][ "right_door_opened_pos" ] = rightdoor.origin;
				}
			}
		}
		assert( isdefined( parts.e[ "outer_doorset" ] ) );

		// bubble sort floors
		for ( i = 0; i < parts.e[ "outer_doorset" ].size - 1; i++ )
		{
			for ( j = 0; j < parts.e[ "outer_doorset" ].size - 1 - i; j++ )
			{
				if ( parts.e[ "outer_doorset" ][ j + 1 ][ "door_closed_pos" ][ 2 ] < parts.e[ "outer_doorset" ][ j ][ "door_closed_pos" ][ 2 ] )
				{
					//swap j-1 with j
					temp_left_door = parts.e[ "outer_doorset" ][ j ][ "left_door" ];
					temp_left_door_opened_pos = parts.e[ "outer_doorset" ][ j ][ "left_door_opened_pos" ];
					temp_right_door = parts.e[ "outer_doorset" ][ j ][ "right_door" ];
					temp_right_door_opened_pos = parts.e[ "outer_doorset" ][ j ][ "right_door_opened_pos" ];
					temp_closed_pos = parts.e[ "outer_doorset" ][ j ][ "door_closed_pos" ];

					parts.e[ "outer_doorset" ][ j ][ "left_door" ] = parts.e[ "outer_doorset" ][ j + 1 ][ "left_door" ];
					parts.e[ "outer_doorset" ][ j ][ "left_door_opened_pos" ] = parts.e[ "outer_doorset" ][ j + 1 ][ "left_door_opened_pos" ];
					parts.e[ "outer_doorset" ][ j ][ "right_door" ] = parts.e[ "outer_doorset" ][ j + 1 ][ "right_door" ];
					parts.e[ "outer_doorset" ][ j ][ "right_door_opened_pos" ] = parts.e[ "outer_doorset" ][ j + 1 ][ "right_door_opened_pos" ];
					parts.e[ "outer_doorset" ][ j ][ "door_closed_pos" ] = parts.e[ "outer_doorset" ][ j + 1 ][ "door_closed_pos" ];

					parts.e[ "outer_doorset" ][ j + 1 ][ "left_door" ] = temp_left_door;
					parts.e[ "outer_doorset" ][ j + 1 ][ "left_door_opened_pos" ] = temp_left_door_opened_pos;
					parts.e[ "outer_doorset" ][ j + 1 ][ "right_door" ] = temp_right_door;
					parts.e[ "outer_doorset" ][ j + 1 ][ "right_door_opened_pos" ] = temp_right_door_opened_pos;
					parts.e[ "outer_doorset" ][ j + 1 ][ "door_closed_pos" ] = temp_closed_pos;
				}
			}
		}

		// === build elevator floor pos ===
		floor_pos = [];
		foreach ( i, doorset in parts.e[ "outer_doorset" ] )
		{
			mainframe = parts get_housing_mainframe();

			floor_pos = ( mainframe.origin[ 0 ], mainframe.origin[ 1 ], doorset[ "door_closed_pos" ][ 2 ] );
			parts.e[ "floor" + i + "_pos" ] = floor_pos;

			if ( mainframe.origin == floor_pos )
			{
				parts.e[ "initial_floor" ] = i;
				parts.e[ "current_floor" ] = i;
			}
		}

		// === save build info ===
		level.elevators[ level.elevators.size ] = parts;

		// trash all script origins no longer needed
		elevator_bound delete();
		elevator_bound_end delete();
	}
	foreach ( elevator_doorset in elevator_doorsets )
		elevator_doorset delete();

	build_call_buttons();

	if ( !level.elevator_motion_detection )
		setup_hints();

	// turn on all primary lights for elevators if they have em
	foreach ( elevator in level.elevators )
	{
		pLights = elevator get_housing_primarylight();
		if ( isdefined( pLights ) && pLights.size )
		{
			foreach ( pLight in pLights )
				pLight setlightintensity( 0.75 );
		}
	}
}

build_call_buttons()
{
	level.elevator_callbuttons = getentarray( "elevator_call", "targetname" );
	assertex( isdefined( level.elevator_callbuttons ) && ( level.elevator_callbuttons.size > 1 ), "Missing or not enough elevator call buttons" );

	// per call button
	foreach ( callbutton in level.elevator_callbuttons )
	{
		callbutton.e = [];
		callbutton_v_vec = ( 0, 0, callbutton.origin[ 2 ] );
		callbutton_h_vec = ( callbutton.origin[ 0 ], callbutton.origin[ 1 ], 0 );

		temp_elevator_list = [];
		// per elevator
		foreach ( e_idx, elevator in level.elevators )
		{
			// per floor
			foreach ( f_idx, eFloor in elevator get_outer_doorsets() )
			{
				v_vec = ( 0, 0, elevator.e[ "floor" + f_idx + "_pos" ][ 2 ] );
				h_vec = ( elevator.e[ "floor" + f_idx + "_pos" ][ 0 ], elevator.e[ "floor" + f_idx + "_pos" ][ 1 ], 0 );

				if ( abs( distance( callbutton_v_vec, v_vec ) ) <= level.elevator_callbutton_link_v )
				{
					if ( abs( distance( callbutton_h_vec, h_vec ) ) <= level.elevator_callbutton_link_h )
					{
						temp_elevator_list[ temp_elevator_list.size ] = elevator;	// build list of elevators linked on floor f_idx
						callbutton.e[ f_idx ] = temp_elevator_list;
					}
				}
			}
		}
		callbutton make_discrete_trigger();
		assertex( isdefined( callbutton.e ) && callbutton.e.size, "Elevator call button at " + callbutton.origin + " failed to grab near by elevators, placed too far?" );

		// build motion detection triggers for motion triggered calls
		callbutton.motion_trigger = spawn( "trigger_radius", callbutton.origin + ( 0, 0, -32 ), 0, 32, 64 );
	}
}

setup_hints()
{
	// elevator inside use trigger hint
	foreach ( elevator in level.elevators )
	{
		use_trig = elevator get_housing_inside_trigger();
		floors = elevator get_outer_doorsets();
		num_of_floors = floors.size;

		use_trig SetCursorHint( "HINT_NOICON" );
		if ( num_of_floors > 2 )
			// Press and hold &&1 to select floor.
			use_trig setHintString( &"ELEVATOR_FLOOR_SELECT_HINT" );
		else
			// Press and hold &&1 to use elevator.
			use_trig setHintString( &"ELEVATOR_USE_HINT" );
	}

	// elevator call button hint
	foreach ( callbutton in level.elevator_callbuttons )
	{
		callbutton SetCursorHint( "HINT_NOICON" );
		// Press and hold &&1 to call elevator.
		callbutton setHintString( &"ELEVATOR_CALL_HINT" );
	}
}

//==========================================================================//
//								===	HELPERS	===								//
//==========================================================================//

// setup discrete trigger for discrete waittill
make_discrete_trigger()
{
	self.enabled = 1;			// enable now for disabling trigger
	self disable_trigger(); 	// disable trigger, enable again only when waittill on
}

// trigger only exist when waittill upon
discrete_waittill( msg )
{
	assert( isdefined( self.motion_trigger ) );

	self enable_trigger();	// this is for disabling trigger immediately after triggering

	if ( level.elevator_motion_detection )
		self.motion_trigger waittill( msg, param );
	else
		self waittill( msg, param );

	self disable_trigger();
	return param;
}


enable_trigger()
{
	if ( !self.enabled )
	{
		self.enabled = 1;
		self.origin += ( 0, 0, 10000 );

		if ( isdefined( self.motion_trigger ) )
			self.motion_trigger.origin += ( 0, 0, 10000 );
	}
}

disable_trigger()
{
	self notify( "disable_trigger" );
	if ( self.enabled )
		self thread disable_trigger_helper();
}

disable_trigger_helper()
{
	self endon( "disable_trigger" );
	self.enabled = 0;
	wait 1.5;
	self.origin += ( 0, 0, -10000 );

	if ( isdefined( self.motion_trigger ) )
		self.motion_trigger.origin += ( 0, 0, -10000 );
}

// ========== OUTER DOOR SETS ===========
// returns array of outer doorsets for this floor - ent[]
get_outer_doorset( floor_num )
{
	return self.e[ "outer_doorset" ][ floor_num ];
}

// returns array of floors of doorsets - int[]
get_outer_doorsets()
{
	return self.e[ "outer_doorset" ];
}

// returns outer door closed position for this floor - vec
get_outer_closedpos( floor_num )
{
	return self.e[ "outer_doorset" ][ floor_num ][ "door_closed_pos" ];
}

// returns left door entity for this floor - ent
get_outer_leftdoor( floor_num )
{
	return self.e[ "outer_doorset" ][ floor_num ][ "left_door" ];
}

// returns right door entity for this floor - ent
get_outer_rightdoor( floor_num )
{
	return self.e[ "outer_doorset" ][ floor_num ][ "right_door" ];
}

// returns left door opened position for this floor - vec
get_outer_leftdoor_openedpos( floor_num )
{
	return self.e[ "outer_doorset" ][ floor_num ][ "left_door_opened_pos" ];
}

// returns right door opened position for this floor - vec
get_outer_rightdoor_openedpos( floor_num )
{
	return self.e[ "outer_doorset" ][ floor_num ][ "right_door_opened_pos" ];
}

// ========= HOUSING =========
// returns all the entities that will move when the elevator moves between floors - ent[]
get_housing_children()
{
	children = [];

	door_trig 	 = self get_housing_door_trigger();
	use_trig 	 = self get_housing_inside_trigger();
	motion_trig = use_trig.motion_trigger;
	left_door	 = self get_housing_leftdoor();
	right_door	 = self get_housing_rightdoor();

	children[ children.size ] = door_trig;
	children[ children.size ] = use_trig;
	children[ children.size ] = left_door;
	children[ children.size ] = right_door;

	if ( isdefined( motion_trig ) )
		children[ children.size ] = motion_trig;

	// append script models as children of elevator moving body
	script_models = self get_housing_models();
	foreach ( eModel in script_models )
		children[ children.size ] = eModel;

	// append primary light(s) as children of elevator moving body
	primarylights = get_housing_primarylight();
	foreach ( pLight in primarylights )
		children[ children.size ] = pLight;

	return children;
}

// returns only the mainframe script_brushmodel, there can only be one per elevator! - ent
get_housing_mainframe()
{
	parts = self.e[ "housing" ][ "mainframe" ];

	housing_model = undefined;
	foreach ( part in parts )
	{
		if ( part.classname != "script_model" && part.code_classname != "light"  )
		{
			assertex( !isdefined( housing_model ), "Fail! Found more than one elevator housing script_brushmodels per elevator" );
			housing_model = part;
		}
	}
	assertex( isdefined( housing_model ), "Epic fail! No elevator housing script_brushmodel found" );
	return housing_model;
}

// returns an array of script_models used as part of the elevator prefab - ent[]
get_housing_models()
{
	parts = self.e[ "housing" ][ "mainframe" ];
	temp_model_array = [];

	foreach ( part in parts )
	{
		if ( part.classname == "script_model" )
			temp_model_array[ temp_model_array.size ] = part;
	}
	return temp_model_array;
}

// returns an array of lights - ent[]
get_housing_primarylight()
{
	parts = self.e[ "housing" ][ "mainframe" ];
	temp_primarylights = [];

	foreach ( part in parts )
	{
		if ( part.code_classname == "light" )
			temp_primarylights[ temp_primarylights.size ] = part;
	}
	return temp_primarylights;
}

// returns a single model to play elevator music on, this must exist and only one! - ent
get_housing_musak_model()
{
	models = self get_housing_models();
	musak_model = undefined;

	foreach ( eModel in models )
	{
		if ( isdefined( eModel.script_noteworthy ) && eModel.script_noteworthy == "play_musak" )
			musak_model = eModel;
	}
	//assertex( isdefined( musak_model ), "Fail! Missing script_model to play elevator music on, [script_noteworthy = play_musak]" );
	
	return musak_model;
}

// returns interrupt trigger for elevator doors - ent trig
get_housing_door_trigger()
{
	return self.e[ "housing" ][ "door_trigger" ];
}

// returns trigger for floor selection inside the elevator - ent trig
get_housing_inside_trigger()
{
	return self.e[ "housing" ][ "inside_trigger" ];
}

// returns inner door's closing position - vec
get_housing_closedpos()
{
	return self.e[ "housing" ][ "door_closed_pos" ];
}

// returns inner left door entity - ent
get_housing_leftdoor()
{
	return self.e[ "housing" ][ "left_door" ];
}

// returns inner right door entity - ent
get_housing_rightdoor()
{
	return self.e[ "housing" ][ "right_door" ];
}

// returns inner left door opened position - vec
get_housing_leftdoor_opened_pos()
{
	return self.e[ "housing" ][ "left_door_opened_pos" ];
}

// returns inner right door opened position - vec
get_housing_rightdoor_opened_pos()
{
	return self.e[ "housing" ][ "right_door_opened_pos" ];
}

// floor currently the elevator is on - int
get_curFloor()
{
	moving = self elevator_floor_update();
	return self.e[ "current_floor" ];
}

// floor elevator initially at on level load - int
get_initFloor()
{
	return self.e[ "initial_floor" ];
}

waittill_finish_moving( ent1, ent1_moveto_pos, ent2, ent2_moveto_pos )
{
	if ( !isdefined( ent2 ) && !isdefined( ent2_moveto_pos ) )
	{
		ent2 = ent1;
		ent2_moveto_pos = ent1_moveto_pos;
	}

	while ( 1 )
	{
		ent1_current_pos = ent1.origin;
		etn2_current_pos = ent2.origin;

		if ( ent1_current_pos == ent1_moveto_pos && etn2_current_pos == ent2_moveto_pos )
			break;

		wait 0.05;
	}
}

// return test of min max bound on xy plane, self = entity being tested - bool
isInbound( bounding_box )
{

	assertex( isdefined( self ) && isdefined( self.origin ), "Fail! Can not test bounds with the entity called on" );

	// the box isn't working on the angle that I have so I'm going to do it by a sphere shape.. -Nate 
	//special case cause I don't know if a sphere will break other levels.
	if( level.script == "plaza" || level.script == "highrise_test" )
		return isInBoundingSpere( bounding_box );

	v_x = self.origin[ 0 ];
	v_y = self.origin[ 1 ];

	min_x = bounding_box[ 0 ];
	max_x = bounding_box[ 1 ];
	min_y = bounding_box[ 2 ];
	max_y = bounding_box[ 3 ];

	return ( v_x >= min_x && v_x <= max_x && v_y >= min_y && v_y <= max_y );
}

isInBoundingSpere( bounding_box )
{
	v_x = self.origin[ 0 ];
	v_y = self.origin[ 1 ];
	min_x = bounding_box[ 0 ];
	max_x = bounding_box[ 1 ];
	min_y = bounding_box[ 2 ];
	max_y = bounding_box[ 3 ];
	
	mid_x = (min_x + max_x )/2;
	mid_y = (min_y + max_y )/2;
	radius = abs( Distance( (min_x,min_y,0 ), (mid_x,mid_y,0)) );
	return( abs( distance( (v_x,v_y,0), (mid_x,mid_y,0) ) )  < radius );
}

waittill_or_timeout( msg, timer )
{
	self endon( msg );
	wait( timer );
}

elevator_get_dvar_int( dvar, def )
{
	return int( elevator_get_dvar( dvar, def ) );
}

elevator_get_dvar( dvar, def )
{
	if ( getdvar( dvar ) != "" )
		return getdvarfloat( dvar );
	else
	{
		setdvar( dvar, def );
		return def;
	}
}

elevator_debug()
{
	if ( !level.elevator_debug )
		return;

	//print3d(<origin>, <text>, <color>, <alpha>, <scale>, <duration> )

	while ( 1 )
	{
		// simple debug info:

		if ( level.elevator_debug != 2 )
			continue;

		// full debug info:

		// print all parts for all elevators
		foreach ( i, elevator in level.elevators )
		{
			mainframe = elevator get_housing_mainframe();
			musak_model = elevator get_housing_musak_model();

			print3d( musak_model.origin, "[e" + i + "]musak_origin", ( 0.75, 0.75, 1.0 ), 1, 0.25, 20 );
			print3d( mainframe.origin, "[e" + i + "]mainframe", ( 0.75, 0.75, 1.0 ), 1, 0.25, 20 );
			print3d( elevator.e[ "housing" ][ "left_door" ].origin, "[e" + i + "]left door", ( 0.75, 0.75, 1.0 ), 1, 0.25, 20 );
			print3d( elevator.e[ "housing" ][ "right_door" ].origin, "[e" + i + "]right door", ( 0.75, 0.75, 1.0 ), 1, 0.25, 20 );
			print3d( elevator.e[ "housing" ][ "door_closed_pos" ], "[e" + i + "]->|<-", ( 0.75, 0.75, 1.0 ), 1, 0.25, 20 );
			print3d( elevator.e[ "housing" ][ "inside_trigger" ].origin, "[e" + i + "]USE", ( 0.75, 0.75, 1.0 ), 1, 0.25, 20 );

			foreach ( j, eFloor in elevator.e[ "outer_doorset" ] )
			{
				print3d( eFloor[ "left_door" ].origin + ( 0, 0, 8 ), "[e" + i + "][f" + j + "]left door", ( 0.75, 1.0, 0.75 ), 1, 0.25, 20 );
				print3d( eFloor[ "right_door" ].origin + ( 0, 0, 8 ), "[e" + i + "][f" + j + "]right door", ( 0.75, 1.0, 0.75 ), 1, 0.25, 20 );
				print3d( eFloor[ "door_closed_pos" ] + ( 0, 0, 8 ), "[e" + i + "][f" + j + "]->|<-", ( 0.75, 1.0, 0.75 ), 1, 0.25, 20 );
				print3d( elevator.e[ "floor" + j + "_pos" ] + ( 0, 0, 8 ), "[e" + i + "][f" + j + "]stop", ( 1.0, 0.75, 0.75 ), 1, 0.25, 20 );
			}
		}

		// per button
		foreach ( callbutton in level.elevator_callbuttons )
		{
			print3d( callbutton.origin, "linked to:", ( 0.75, 0.75, 1.0 ), 1, 0.25, 20 );

			// per floor
			foreach ( f_idx, eFloor in callbutton.e )
			{
				// per elevator linked
				printoffset = 0;
				foreach ( e_idx, eLinked in eFloor )
				{
					printoffset++ ;
					// e_idx is used to offset print
					print_pos = callbutton.origin + ( 0, 0, ( printoffset ) * ( -4 ) );
					print3d( print_pos, "[f" + f_idx + "][e" + eLinked.e[ "id" ] + "]", ( 0.75, 0.75, 1.0 ), 1, 0.25, 20 );
				}
			}
		}

		wait 0.05;
	}
}