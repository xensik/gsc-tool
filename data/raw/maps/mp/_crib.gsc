#include maps\mp\_utility;
#include common_scripts\utility;

CONST_default_radial_radius			= 8; 		// default distance between radial button and center
CONST_radial_center_extrude_dist	= 40; 		// this is the distance between the floating radial center and the oberver's eye
CONST_direct_travel					= 1;		// no path, directly zoom to position
CONST_view_travel_unit_dist			= 1200;		// distance unit per travel interval
CONST_view_travel_unit_time			= 1; 		// in seconds per travel interval
CONST_blur_strength					= 3;		// blur strength during view travel, sine curved over travel duration

init()
{
	precacheShellShock( "frag_grenade_mp" );
	
	radial_button_definitions();				// define radial button sets and buttons
	radial_init();								// setup radial button mechanism
	view_path_setup();							// setup view flight paths
	player_init();
}

// ====================================================================================
// ==                                 		inits 	                                 ==
// ====================================================================================

radial_button_definitions()
{
	newRadialButtonGroup( "main", 				"player_view1_start", 	"player_view1_end" );
	
	//	Main menu's buttons:
		bWeapons_a 	= newRadialButton( "main", 	"Primary Weapon", 		"radial_weapons_primary", 	::action_weapons_primary );
		bWeapons_b	= newRadialButton( "main", 	"Secondary Weapon", 	"radial_weapons_secondary", ::action_weapons_secondary );
		bGears 		= newRadialButton( "main", 	"Gears", 				"radial_gears", 			::action_gears );
		bKillStreaks= newRadialButton( "main", 	"Kill Streaks", 		"radial_killstreaks",		::action_killstreak );
		bLeadboards = newRadialButton( "main", 	"Leaderboards", 		"radial_leaderboards",		::action_leaderboards );
	//
	
	newRadialButtonGroup( "gears", 				"player_view2_start", 	"player_view2_end" );
	newRadialButtonGroup( "weapons_primary", 	"player_view3_start", 	"player_view3_end" );
	newRadialButtonGroup( "weapons_secondary", 	"player_view3_start", 	"player_view3_end" );
	newRadialButtonGroup( "killstreak", 		"player_view4_start", 	"player_view4_end" );
	newRadialButtonGroup( "leaderboards", 		"player_view5_start", 	"player_view5_end" );
}


radial_init()
{
	// calculate start & end angles of all buttons for range selection
	foreach ( button_group in level.radial_button_group )
	{
		// sort buttons by angle so we can calculate mid angles in sequence
		sort_buttons_by_angle( button_group );
		
		for ( i = 0; i < button_group.size; i ++ )
		{
			if ( isdefined( button_group[ i + 1 ] ) )
			{
				mid_angle = getMidAngle( button_group[ i ].pos_angle, button_group[ i + 1 ].pos_angle );
				button_group[ i ].end_angle = mid_angle;
				button_group[ i + 1 ].start_angle = mid_angle;
			}
			else
			{
				mid_angle = getMidAngle( button_group[ i ].pos_angle, button_group[ 0 ].pos_angle ) + 180;	// +180 to mirror angle
				if ( mid_angle > 360 )
					mid_angle -= 360;

				button_group[ i ].end_angle = mid_angle;
				button_group[ 0 ].start_angle = mid_angle;
			}
		}
	}
	
	// monitors
	thread updateSelectedButton();
	thread watchSelectButtonPress();
	thread watchBackButtonPress();
	thread debug_toggle();
}


debug_toggle()
{
	level endon( "game_ended" );
	level.crib_debug = 1;
	
	while ( 1 )
	{
		if ( !isdefined( level.observer ) )
		{
			wait 0.05;
			continue;
		}
		
		button_reset = true;
		while ( !( level.observer buttonPressed( "BUTTON_Y" ) ) )
			wait 0.05;
		
		level.observer playsound("mouse_click");
		
		if ( button_reset )
		{
			level.crib_debug *= -1;
			button_reset = false;
		}
		
		while ( level.observer buttonPressed( "BUTTON_Y" ) )
			wait 0.05;
	}
}


player_init()
{
	level thread onPlayerConnect();
	level thread return_hud();
}


return_hud()
{
	level waittill( "game_ended" );
	setdvar( "cg_draw2d", 1 );	
}


onPlayerConnect()
{
	level waittill("connected", player);
	
	player thread readyPlayer();
	player waittill( "spawned_player" );
	
	wait 1;
	
	player takeallweapons();
	setdvar( "cg_draw2d", 0 );
	
	if ( !isdefined( player ) )
		return;
	else
		level.observer = player;
	
	player thread get_right_stick_angle();	
	
	zoom_to_radial_menu( "main" );	// fly to the first radial menu
}


readyPlayer()
{
	self endon( "disconnect" );
	
	team = "autoassign";

	while(!isdefined(self.pers["team"]))
		wait .05;

	self notify("menuresponse", game["menu_team"], team);
	wait 0.5;

	classes = getArrayKeys( level.classMap );
	okclasses = [];
	for ( i = 0; i < classes.size; i++ )
	{
		if ( !isSubStr( classes[i], "custom" ) )
			okclasses[ okclasses.size ] = classes[i];
	}
	
	assert( okclasses.size );

	while( 1 )
	{
		class = okclasses[ 0 ];
		self notify("menuresponse", "changeclass", class);
			
		self waittill( "spawned_player" );
		wait ( 0.10 );
	}
}

// ====================================================================================
// ==                                Radial Mechanics                                ==
// ====================================================================================

get_right_stick_angle()
{
	// self is user
	level endon( "game_ended" );
	self endon( "disconnect" );
	
	while ( 1 )
	{
		rs_vec = self GetNormalizedMovement();
		rs_angles = vectortoangles( rs_vec );
		level.rs_angle = int( rs_angles[1] );			

		wait 0.05;	// update rate
	}
}


newRadialButtonGroup( group_name, view_start, view_end )
{
	if ( isdefined( level.radial_button_group ) && level.radial_button_group.size )
		assertex( !isdefined( level.radial_button_group[ group_name ] ), "Radial button group: " + group_name + " is already defined." );

	player_view_ent = getent( view_end, "targetname" );
	assertex( isdefined( player_view_ent ), "Missing player view entity, can not setup radial menu in space" );

	extruded_vec = ( VectorNormalize( AnglesToForward( player_view_ent.angles ) ) * CONST_radial_center_extrude_dist );

	level.radial_button_group[ group_name ] = [];
	level.radial_button_group_info[ group_name ][ "view_start" ] 		= view_start;
	level.radial_button_group_info[ group_name ][ "view_pos" ] 			= player_view_ent.origin + extruded_vec;
	level.radial_button_group_info[ group_name ][ "player_view_pos" ] 	= player_view_ent.origin;
	level.radial_button_group_info[ group_name ][ "view_angles" ] 		= player_view_ent.angles;
}


newRadialButton( button_group, button_label, button_ent_name, action_func )
{
	assertex( isdefined( level.radial_button_group[ button_group ] ), "Radial button group: " + button_group + " does not exist." );
	
	ent = getent( button_ent_name, "targetname" );
	new_button_angle = getRadialAngleFromEnt( button_group, ent );
	
	button 				= spawnstruct();
	button.pos 			= ent.origin;
	button.label 		= button_label;
	button.font_size	= 1;
	button.font_color	= ( 0.5, 0.5, 1 );
	button.pos_angle 	= new_button_angle;
	button.action_func 	= action_func;
	button.radius_pos 	= CONST_default_radial_radius;
	
	level.radial_button_group[ button_group ][ level.radial_button_group[ button_group ].size ] = button;
	return button;
}


updateSelectedButton()
{
	level endon( "game_ended" );
	
	while ( 1 )
	{
		if ( !isdefined( level.radial_button_current_group ) )
		{
			wait 0.05;
			continue;
		}
		
		last_active_button = level.active_button;
		
		foreach ( button in level.radial_button_group[ level.radial_button_current_group ] )
		{
			if ( isInRange( button.start_angle, button.end_angle ) )	
				level.active_button = button;
			else
				button.font_color	= ( 0.5, 0.5, 1 );
		}
		
		if ( isdefined ( level.active_button ) )
		{
			level.active_button.font_color	= ( 1, 1, 0.5 );
		
			if ( isdefined( last_active_button ) && last_active_button != level.active_button )
				level.observer playsound("mouse_over");	
		}
		
		wait 0.05;
	}
}


watchSelectButtonPress()
{
	level endon( "game_ended" );
	
	while ( 1 )
	{
		if ( !isdefined( level.observer ) )
		{
			wait 0.05;
			continue;
		}
		
		button_reset = true;		
		while ( !( level.observer buttonPressed( "BUTTON_A" ) ) )
			wait 0.05;
			
		level.observer playsound("mouse_click");
				
		if ( isdefined( level.active_button ) && button_reset )
		{
			level.active_button notify( "select_button_pressed" );
			[[level.active_button.action_func]]();
			button_reset = false;
		}
		
		while ( level.observer buttonPressed( "BUTTON_A" ) )
			wait 0.05;
	}
}


watchBackButtonPress()
{
	level endon( "game_ended" );
	
	while ( 1 )
	{
		if ( !isdefined( level.observer ) )
		{
			wait 0.05;
			continue;
		}
		
		button_reset = true;
		while ( !( level.observer buttonPressed( "BUTTON_X" ) ) )
			wait 0.05;

		level.observer playsound("mouse_click");
		
		if ( button_reset )
		{
			action_back();
			button_reset = false;
		}
		
		while ( level.observer buttonPressed( "BUTTON_X" ) )
			wait 0.05;
	}
}


sort_buttons_by_angle( button_group )
{
	// button_group is actual array
	// bubble sort buttons
	for ( i = 0; i < button_group.size - 1; i++ )
	{
		for ( j = 0; j < button_group.size - 1 - i; j++ )
		{
			if ( button_group[ j + 1 ].pos_angle < button_group[ j ].pos_angle )
				button_switch( button_group[ j ], button_group[ j + 1 ] );
		}
	}
}


button_switch( button1, button2 )
{
	temp_pos 			= button1.pos;
	temp_label 			= button1.label;
	temp_pos_angle 		= button1.pos_angle;
	temp_action_func 	= button1.action_func;
	temp_radius_pos		= button1.radius_pos;
	
	button1.pos         = button2.pos;        
	button1.label       = button2.label;      
	button1.pos_angle   = button2.pos_angle;  
    button1.action_func = button2.action_func;
    button1.radius_pos  = button2.radius_pos; 
    
 	button2.pos         = temp_pos; 			    
	button2.label       = temp_label; 			
	button2.pos_angle   = temp_pos_angle;		
    button2.action_func = temp_action_func; 	    
    button2.radius_pos  = temp_radius_pos;
}


draw_radial_buttons( button_group )
{
	foreach ( button in level.radial_button_group[ button_group ] )
		button thread draw_radial_button( button_group );
}


//print3d(<origin>, <text>, <color>, <alpha>, <scale>, <duration> )
draw_radial_button( button_group )
{
	level endon( "game_ended" );	
	self endon( "remove_button" );
	
	floating_origin = level.radial_button_group_info[ button_group ][ "view_pos" ];
	button_radial_pos = floating_origin + radial_angle_to_vector( self.pos_angle, 4 );

	while ( 1 )
	{
		//line( level.radial_button_group_info[ button_group ][ "view_pos" ], self.pos, ( 0, 1, 0 ), 0.05, false );
		
		range_color = ( 1, 0, 0 );
		if ( isInRange( self.start_angle, self.end_angle ) )
			range_color = ( 1, 1, 0 );
			
		print3d( self.pos, self.label, self.font_color, 0.75, self.font_size, 1 );
		
		if ( isdefined( level.crib_debug ) && level.crib_debug > 0 )
		{
			print3d( button_radial_pos, ".("+int(self.pos_angle)+")", range_color, 0.75, 0.05, 1 );
	
			line( floating_origin, floating_origin + radial_angle_to_vector( self.start_angle, 2 ), range_color, 0.05 );
			line( floating_origin + radial_angle_to_vector( self.start_angle, 2 ), floating_origin + radial_angle_to_vector( self.end_angle, 2 ), range_color, 0.05 );
	
			// right stick debug ling
			r_radial_pos = floating_origin + radial_angle_to_vector( level.rs_angle, 2 );
			line( floating_origin, r_radial_pos, ( 1, 1, 1 ), 0.05 );
			
			
		}
		print3d( floating_origin - ( 0, 0, 4.5 ), "(A)=Select (X)=Back", (1, 1, 1), 0.5, 0.05, 1 );
		
		wait 0.05;
	}
}


Zoom_To_Radial_Menu( button_group, reverse )
{
	level.active_button = undefined;
	
	assertex( isdefined( level.observer ), "Missing observer (connected player), can not attach player to view path" );
	
	if ( isdefined( level.radial_button_current_group ) && level.radial_button_current_group != "" )
	{
		level.radial_button_previous_group = level.radial_button_current_group;
	}
	else
	{
		level.radial_button_previous_group = "main";
		level.radial_button_current_group = "main";
	}
	
	foreach ( button in level.radial_button_group[ level.radial_button_previous_group ] )
			button notify( "remove_button" );

	//iPrintLnBold( "flying to: " + button_group );
	
	if ( isdefined( reverse ) && reverse )
		level.observer go_path_by_targetname_reverse( level.radial_button_group_info[ level.radial_button_previous_group ][ "view_start" ], button_group );
	else
		level.observer go_path_by_targetname( level.radial_button_group_info[ button_group ][ "view_start" ] );
	
	level thread draw_radial_buttons( button_group );
	level.radial_button_current_group = button_group;
}


// ====================================================================================
// ==                              	Radial menu - math		                         ==
// ====================================================================================

// edit function with care, returns orientation-sensistive angles
getRadialAngleFromEnt( button_group, ent )
{
	assertex( isdefined( level.radial_button_group[ button_group ] ), "getRadialAngleFromEnt: Radial button group does not exist." );
	assertex( isdefined( ent ), "getRadialAngleFromEnt: Missing entity to be measured." );
	
	rAngle 		 = level.radial_button_group_info[ button_group ][ "view_angles" ];
	rPos 		 = level.radial_button_group_info[ button_group ][ "view_pos" ];
	rPos 		+= ( VectorNormalize( AnglesToForward( rAngle ) ) * CONST_radial_center_extrude_dist );
	rForward 	 = AnglesToForward( rAngle );
	rUpwardNorm  = VectorNormalize( AnglesToUp( rAngle ) );
	
	eAngle 		 = ent.angles;
	ePos 		 = ent.origin;

	projNorm 	 = VectorNormalize( VectorFromLineToPoint( rPos, ( rPos + rForward ), ePos ) );
	radial_angle = Acos( VectorDot( projNorm, rUpwardNorm ) );

	// vector mirroring
	if ( VectorDot( AnglesToRight( rAngle ), projNorm ) < 0 )
		radial_angle = 360 - radial_angle;
		
	return radial_angle;
}


// converts projected angle into player's view plane into a vector
radial_angle_to_vector( angle, scaler )
{
	b_angles 	= ( 270 - ( angle ), 0 , 0 );		// 270 degrees offset to face the player
	b_vec 		= AnglesToForward( b_angles );
	b_vec_norm 	= VectorNormalize( b_vec );
	b_vec_final = ( b_vec_norm * scaler );
	
	return b_vec_final;
}


getMidAngle( a1, a2 )
{
	// 0 -> 360 domain
	mid_angle = ( ( a1 + a2 + 720 ) / 2 ) - 360;		
	return mid_angle;
}


isInRange( start_angle, end_angle )
{
	inside_big_angle 	= ( level.rs_angle > start_angle && level.rs_angle < 360 );
	inside_small_angle 	= ( level.rs_angle > 0 && level.rs_angle < end_angle );
	
	if ( start_angle > end_angle )
		in_range = ( inside_big_angle || inside_small_angle );
	else
		in_range = ( level.rs_angle > start_angle && level.rs_angle < end_angle );

	return in_range;
}

// ====================================================================================
// ==                          Button action functions                               ==
// ====================================================================================

// close radial buttons
action_back()
{
	//if ( isdefined( level.radial_button_previous_group ) && level.radial_button_previous_group != "" )
	//	zoom_to_radial_menu( level.radial_button_previous_group );
	/*else*/ if ( isdefined( level.radial_button_current_group ) && level.radial_button_current_group != "main" )
		zoom_to_radial_menu( "main", true );
	else
		return;
}


// ==== main ====
action_weapons_primary()
{
	iPrintLnBold( "action_weapons_primary" );
	zoom_to_radial_menu( "weapons_primary" );
}


action_weapons_secondary()
{
	iPrintLnBold( "action_weapons_secondary" );	
	zoom_to_radial_menu( "weapons_secondary" );
}

action_gears()
{
	iPrintLnBold( "action_gears" );	
	zoom_to_radial_menu( "gears" );
}


action_killstreak()
{
	iPrintLnBold( "action_killstreak" );	
	zoom_to_radial_menu( "killstreak" );
}


action_leaderboards()
{
	iPrintLnBold( "action_leaderboards" );	
	zoom_to_radial_menu( "leaderboards" );
}

// ====================================================================================
// ==                             Pathing functions                                  ==
// ====================================================================================

view_path_setup()
{
	// setup all paths
	level.view_paths = [];
	
	// build paths
	build_path_by_targetname( "player_view1_start" );
	build_path_by_targetname( "player_view2_start" );
	build_path_by_targetname( "player_view3_start" );
	build_path_by_targetname( "player_view4_start" );
	build_path_by_targetname( "player_view5_start" );
}


build_path_by_targetname( path_name )
{
	level.view_paths[ path_name ] = [];
	
	path_node = getent( path_name, "targetname" );
	level.view_paths[ path_name ][ level.view_paths[ path_name ].size ] = path_node;
	
	while( isdefined( path_node ) && isdefined( path_node.target ) )
	{
		next_node = getent( path_node.target, "targetname" );
		level.view_paths[ path_name ][ level.view_paths[ path_name ].size ] = next_node;
		path_node = next_node;
	}
}


go_path_by_targetname( path_name )
{	
	// self is player
	if ( !isdefined( level.dummy_mover ) )
	{
		start_node = level.view_paths[ path_name ][ 0 ];
		level.dummy_mover = spawn( "script_model", start_node.origin );
		level.dummy_mover.angles = start_node.angles;
		//self AllowedStances( "stand" );
		self setOrigin( level.dummy_mover.origin - ( 0, 0, 65 ) );
		self linkTo( level.dummy_mover );
		wait 0.05;
		self setplayerangles ( level.dummy_mover.angles );
		
		self thread force_player_angles();
	}
	
	/*
	travel_time = 1;
	dist = 0;
	foreach ( idx, node in level.view_paths[ path_name ] )
	{
		if ( isdefined( level.view_paths[ path_name ][ idx + 1 ] ) )
			dist += abs( distance( level.view_paths[ path_name ][ idx ].origin, level.view_paths[ path_name ][ idx + 1 ].origin ) );
	}*/
	
	travel_speed = CONST_view_travel_unit_time;
	total_distance = abs( distance( level.dummy_mover.origin, level.view_paths[ path_name ][ level.view_paths[ path_name ].size - 1 ].origin ) );
	travel_speed *= total_distance / CONST_view_travel_unit_dist;
	travel_speed = max( travel_speed, 0.1 );	// due to repeated button presses, the travel distance can be cut to 0 travel speed at times.
	
	blur_time = travel_speed;
	if ( !CONST_direct_travel )
		blur_time *= travel_speed * ( level.view_paths[ path_name ].size + 1 );
	self thread blur_sine( CONST_blur_strength, blur_time );
	
	foreach ( idx, node in level.view_paths[ path_name ] )
	{
		//travel_speed = travel_time * ( abs( distance( level.dummy_mover.origin, node.origin ) ) / dist );
		//travel_speed += 0.05;
		
		if ( CONST_direct_travel )
		{
			if ( idx != level.view_paths[ path_name ].size - 1 )
				continue;
		}
			
		//level.dummy_mover MoveTo( node.origin, travel_speed );
		level.dummy_mover MoveTo( node.origin, travel_speed, travel_speed * 0.5, 0 );
		level.dummy_mover RotateTo( node.angles, travel_speed, travel_speed * 0.5, 0);
		wait travel_speed;
	}
}


go_path_by_targetname_reverse( path_name, back_to_button_group )
{	
	assertex( isdefined( level.dummy_mover ), "go_path_by_targetname_reverse called before go_path_by_targetname" );
	
	travel_speed = CONST_view_travel_unit_time;
	total_distance = abs( distance( level.dummy_mover.origin, level.radial_button_group_info[ back_to_button_group ][ "player_view_pos" ] ) );
	travel_speed *= total_distance / CONST_view_travel_unit_dist;
	travel_speed = max( travel_speed, 0.1 );	// due to repeated button presses, the travel distance can be cut to 0 travel speed at times.
	
	blur_time = travel_speed;
	if ( !CONST_direct_travel )
		blur_time *= travel_speed * ( level.view_paths[ path_name ].size + 1 );
	self thread blur_sine( CONST_blur_strength, blur_time );
		
	if ( !CONST_direct_travel )
	{
		for ( idx = level.view_paths[ path_name ].size - 1; idx >= 0; idx-- )
		{
			node = level.view_paths[ path_name ][ idx ];
			level.dummy_mover MoveTo( node.origin, travel_speed );
			level.dummy_mover RotateTo( node.angles, travel_speed );
	
			//self thread travel_view_fx( travel_speed );
			wait travel_speed;
		}
	}
	
	self thread blur_sine( CONST_blur_strength, travel_speed );
	
	pos = level.radial_button_group_info[ back_to_button_group ][ "player_view_pos" ];
	angle = level.radial_button_group_info[ back_to_button_group ][ "view_angles" ];
	
	level.dummy_mover MoveTo( pos, travel_speed, travel_speed * 0.5, 0 );
	level.dummy_mover RotateTo( angle, travel_speed, travel_speed * 0.5, 0 );
	wait travel_speed;
}


travel_view_fx( time )
{
	self setblurforplayer( 20, ( time + 0.2 )/2 );
	self setblurforplayer( 0, ( time + 0.2 )/2 );		
	self shellshock( "frag_grenade_mp", time + 0.2 );	
}


blur_sine( strength, time )
{
	time_scaled = int( time/0.066 );
	
	for( i = 0; i < time_scaled; i ++ )
	{	
		fraction 	= ( i / ( time_scaled ) );
		cos_fraction= sin( 180 * fraction );
		blur_amount = strength * cos_fraction;
		
		setdvar( "r_blur", blur_amount );
		wait 0.05;
	}
	setdvar( "r_blur", 0 );
}


force_player_angles()
{
	level endon( "game_ended" );
	self endon( "disconnect" );
	level.dummy_mover endon( "remove_dummy" );
	
	while ( 1 )
	{
		self setplayerangles ( level.dummy_mover.angles );
		wait 0.05;
	}
}