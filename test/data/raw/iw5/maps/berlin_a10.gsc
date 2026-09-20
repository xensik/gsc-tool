#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_audio;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///START DYNAMIC A10 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


airstrike_on(bSuppress_initial_vo)
{
	if(!isdefined(bSuppress_initial_vo))
		bSuppress_initial_vo = false;
	//debug for changed how the player controls the a10
	//ads = ads to plant and direct
	//static = plant on use always direct
	//points = two points to direct a10
	SetDvarIfUninitialized("a10_strike_controls","points");
	SetDvarIfUninitialized("airstrike_weapon","a10");
	
	//for debuggin a10 paths
	SetDvarIfUninitialized("a10_strike_debug","0");
	//1 is reason for path failure
	//2 is is draw sight checks that failured
	//3 is is all sight checks
	//4 is draw evaluted paths on failure
	//5 show sight trace alternative results on failure
	
	//for generating paths from animation
	SetDvarIfUninitialized("a10_strike_generate_path","0");

	level.in_a10_vo = false;
	
	level.wait_time_before_strike = 2;//3 works well
	level.wait_time_after_strike = .5;//10 works well
	
	level.a10_confirm_second_point_wait_time = .15;
	
	level.a10_drop_vfx_for_destroy = false;
	
	level.a10_goggles_overlay_hi = true; //should we use the high res overlay?
	
	level.a10_fx_lifetime_sec = 1; 		//ANY FX LIFETIME CHANGES MUST BE REFLECTED HERE!
	
	level.a10_flytime = 3;
	level.a10_flyheight_increment = (0,0,512);
	level.a10_fly_distance_back_increment = 512;//increment the plane back each time the flyheight is increased so the gun works correctly.
	level.a10_distance_to_start_impacts_back_from_target = 512;
	level.a10_distance_to_stop_impacts_from_target = 512;
	level.a10_badplace_radius = 256;
	level.a10_friendly_ent_target_check = false;
	
	level.wait_time_total_for_strike = level.wait_time_before_strike + level.wait_time_after_strike;
	
	//allows us to override the cooldown in dev
	level.wait_time_total_for_strike = GetDVarInt("a10_strike_cooldown", level.wait_time_total_for_strike);
	
/#
	if(GetDVarInt("air_strike_dev", 0) == 1)
		level.wait_time_before_strike = .5;
#/
	
	//Setup hud text
	if ( !isdefined( level.a10_hint_hud_activate) )
	{
		level.a10_hint_hud_activate = maps\_hud_util::createFontString( "default", 2 );
		level.a10_hint_hud_activate maps\_hud_util::setPoint( "TOP", undefined, 0, 80 );
		level.a10_hint_hud_activate.label = &"BERLIN_ACTIVATE_A10";
		level.a10_hint_hud_activate.alpha = 1;
		level.a10_hint_hud_activate.sort = 0.5;
		level.a10_hint_hud_activate.foreground = 1;
	}
	
	if ( !isdefined( level.a10_hint_hud) )
	{
		level.a10_hint_hud = maps\_hud_util::createFontString( "default", 2 );
		level.a10_hint_hud maps\_hud_util::setPoint( "TOP", undefined, 0, 80 );
		level.a10_hint_hud.label = &"BERLIN_DIRECT_A10";
		level.a10_hint_hud.alpha = 0;
		level.a10_hint_hud.sort = 0.5;
	}
	
	
	//setup hud graphic
	level.player notifyOnPlayerCommand( "toggle_airstrike", "+actionslot 4" );
	
	if(!isdefined(level.a10_targets))
		level.a10_targets = [];
	
	//start checking for input
	thread airstrike_setup();
	wait(1);
	
	if(!bSuppress_initial_vo)
	{
		//notify the player strike is avalible
		thread airstrike_ready_radio_dialogue();
	}
}

airstrike_off()
{
	level.a10_final_shutdown = true;
	
	//send notify's to turn things off
	level.player notify("turn_off_airstrike");
	level.player notify("airstrike_deactivated");
	
	airstrike_shutdown();
	airstrike_clean_up_target_points( false );
		
	//remove hud icon
	level.player setWeaponHudIconOverride( "actionslot4", "none" );
}

airstrike_setup()
{
	level.player endon("turn_off_airstrike");
	level.player notify("airstrike_available");
	
	//check what controls are being used
	controls = GetDVar("a10_strike_controls");
	level.a10_strike_available = true;
	
	level.player setWeaponHudIconOverride( "actionslot4", "dpad_soflam_static" );
	
	airstrike_clean_up_target_points( false );
	
	level.player waittill("toggle_airstrike");
	
	//show interface
	level.player a10_interface_enable_view();
	level.player airstrike_disable_player_abilities(controls);

	
	if(level.player getcurrentweapon() != level.player getcurrentprimaryweapon())
	{
		level.player switchToWeapon( level.player getcurrentprimaryweapon() );
		wait(.5);
	}
	
	//hud
	if(isDefined(level.a10_hint_hud_activate))
		level.a10_hint_hud_activate.alpha = 0;
		
	if(controls == "static"){
		level.a10_hint_hud.label = &"BERLIN_DIRECT_A10_STATIC";
	}	
		
	level.a10_hint_hud.alpha = 1;

	/#
	if(GetDVarInt("air_strike_dev", 0) == 1)
		level.a10_hint_hud.alpha = 0;
	#/

	childthread monitor_invalid_weapons();
	childthread monitor_weapon_switch();
	
	level.player notifyOnPlayerCommand( "trigger_a10", "+attack" );
	thread airstrike_cancelled();
	thread airstrike_called();
	thread draw_target_aim( true );
}

//if the player has cancelled the airstrike
airstrike_cancelled()
{
	level.player endon("airstrike_called");
	level.player endon("turn_off_airstrike");
	level.player waittill("toggle_airstrike");
	level.player notify("airstrike_deactivated");
//	IPrintLn("cancelling strike");
	maps\_audio::aud_send_msg("a10_cancelled");
	airstrike_clean_up_target_points( false );
	airstrike_shutdown();  //shouldn't be a thread due to timing issues inside func. can create problems if we reinitilize the a10 before it's done.
	wait(.5);
	thread airstrike_setup();
}

//if the player has used it
airstrike_called()
{
	level.player endon("airstrike_deactivated");
	level.player endon("turn_off_airstrike");
	
	level.player waittill("airstrike_called");

	thread airstrike_called_radio_dialogue();
	wait( level.a10_confirm_second_point_wait_time );
	airstrike_clean_up_target_points( false );
	wait(0.7); //tiny delay so it feels better
	airstrike_shutdown();//shouldn't be a thread due to timing issues inside func. can create problems if we reinitilize the a10 before it's done.
	level.player setWeaponHudIconOverride( "actionslot4", "dpad_soflam_inactive" );
	
	level.player waittill("a10_anim_complete");
	wait(level.wait_time_total_for_strike);
	thread airstrike_setup();
	wait(1);
	thread airstrike_ready_radio_dialogue();
}

airstrike_shutdown()
{
	controls = GetDVar("a10_strike_controls");
	
	//hud off
	airstrike_hud_off();
	
	//turn off interface
	level.player a10_interface_disable_view();
	
	if( !isDefined( level.a10_final_shutdown ) ||  level.a10_final_shutdown == false )
	{
		thread monitor_airstrike_attempt_to_activate();
	}
	
	if(isdefined(level.lock_player))
	{
		stick_forward = level.player GetNormalizedMovement();
		if(stick_forward != (0,0,0))
		{
			wait(.5);
		}
		else
		{
			wait(0.3);
		}
		remove_player_lock();
	}
	else
	{
		wait(0.3);
	}
	
	level.player airstrike_enable_player_abilities(controls);
	
	level.a10_strike_available = false;	
}

monitor_airstrike_attempt_to_activate()
{
	level.player endon("turn_off_airstrike");
	level.player endon("airstrike_available");
	
	while( 1 )
	{
		level.player waittill("toggle_airstrike");
		airstrike_not_available_dialogue();
	}
}

create_aim_arrow()
{
	if(!isdefined(level.aim_arrow))
	{
		controls = getDvar("a10_strike_controls");
		
		/* CREATE aim_arrow fx */
		level.aim_arrow = Spawn( "script_model", (0,0,0) );
		level.aim_arrow SetModel( "tag_origin" );
		level.aim_arrow.angles = ( -90, 0, 0 );
		
		level.aim_arrow_view = Spawn( "script_model", (0,0,0) );
		level.aim_arrow_view SetModel( "tag_origin" );
		//align fx pointing towards player
		/*angle_vector = level.aim_arrow.origin - (level.player geteye());
		constrained_angle = VectorToAngles(angle_vector);
		level.aim_arrow.angles = (-90,constrained_angle[1],0);*/
		
		if(controls == "points")
		{
			playfxontag( getfx( "a10_point" ), level.aim_arrow, "tag_origin" );
		}
		else if(controls == "click")
		{
			playfxontag( getfx( "a10_point" ), level.aim_arrow, "tag_origin" );
		}
		else
		{
			playfxontag( getfx( "a10_target" ), level.aim_arrow, "tag_origin" );
			thread draw_directional_info();
			thread draw_directional_line();
		}
	}
}

draw_target_aim( skip_wait_for_cleanup )
{
	self endon("kill_draw_target_aim");
	level.player endon( "toggle_airstrike" );//so we can disable laser during cool down.
	level.player endon("airstrike_called");
	level.player endon("turn_off_airstrike");
	
	controls = getDvar("a10_strike_controls");
	if(controls == "points")
		level.player endon("airstrike_set_second_point");	
	
	if( !skip_wait_for_cleanup && isdefined( level.a10_fx_lifetime_sec ) && level.a10_fx_lifetime_sec > 0 )
		wait( level.a10_fx_lifetime_sec ); //incase there are old fx we need to wait for to finish destroying
	
	thread airstrike_trigger();
	while(1)
	{
		aim_target = calculate_target_pos();
		
		if(aim_target[ "fraction" ] < 1)
		{
			create_aim_arrow();
			level.aim_arrow.origin = aim_target["pos"];
			//align fx pointing towards player
			/*angle_vector = level.aim_arrow.origin - (level.player geteye());
			constrained_angle = VectorToAngles(angle_vector);
			level.aim_arrow.angles = (-90,constrained_angle[1],0);*/
			level.player notify("airstrike_first_point_confirmed");
			controls = getDvar("a10_strike_controls");
			if(controls == "ads")
			{
				//ADS controls when the player can direct the a10
				if(level.player ADSButtonPressed())
				{
					if(!isdefined(level.lock_player))
					{
							level.lock_player = spawn("script_origin",level.player.origin);
							level.player playerlinkto(level.lock_player);
					}
					
					set_aim_target_direction();
				}
				else if(isdefined(level.lock_player))
				{			
					remove_player_lock();
				}
			}
			else if(controls == "static")
			{
				if(!isdefined(level.lock_player))
				{
					//plants player on initilization
					level.lock_player = spawn("script_origin",level.player.origin);
					level.player playerlinkto(level.lock_player);
				}
				set_aim_target_direction();
			}
			else if(controls == "points")
			{
				//don't do anything here until we hit the trigger a second time.
			}
		}
		else
		{
			/#
			if(isdefined(aim_target["entity"]) && isdefined(aim_target["entity"].team) && aim_target["entity"].team == "allies")
			{
				if(!isdefined(level.berlin_a10_targetfriendly_print_time))
					level.berlin_a10_targetfriendly_print_time = 0;
					
				if(level.berlin_a10_targetfriendly_print_time + 5000 < GetTime() )
				{
					//iprintlnbold("cant target friendlies");
					level.berlin_a10_targetfriendly_print_time = GetTime();
				}
			}
			#/
			level.player notify("airstrike_first_point_failure");
			thread first_point_cleanup();
			wait(0.05);
			break;
		}
		wait(.05);
	}
}

set_aim_target_direction()
{
	//Setup rotation based on stick input
	stick_forward = level.player GetNormalizedMovement(); //to control angle of attack
		
	//if there is no input we dont do anything
	if(stick_forward != (0,0,0))
	{
		stick_angles = VectorToAngles(stick_forward);
		
		angles = CombineAngles(level.player.angles, (-1*stick_angles));
		//using the only two angles that matter, don't want to rotate the icon in 3d space.
		rotation = (level.aim_arrow.angles[0],angles[1], angles[2]);
		level.aim_arrow RotateTo( rotation, 0.2 );		

	}
	
	//forward = anglestoforward(angles);
	//line(level.aim_arrow.origin + (-1*forward) * 512, level.aim_arrow.origin + (forward * 512), (1,0,0));
}

create_second_point()
{
	assert(!isdefined(level.a10_second_point));
	level.a10_second_point = Spawn( "script_model", level.a10_start_point.origin );
	level.a10_second_point SetModel( "tag_origin" );
	level.a10_second_point.angles = level.aim_arrow.angles;
	level.a10_second_point.lineType = "green";
	playfxontag( getfx( "a10_point" ), level.a10_second_point, "tag_origin" );
	/*//align fx pointing towards player
	angle_vector = level.a10_second_point.origin - (level.player geteye());
	constrained_angle = VectorToAngles(angle_vector);
	level.a10_second_point.angles = (-90,constrained_angle[1],0);*/
}

destroy_second_point()
{
	if(isdefined(level.a10_second_point))
	{
		stopFxOnTag( getfx( "a10_point" ), level.a10_second_point, "tag_origin" );
		stopFxOnTag( getfx( "a10_point_active" ), level.a10_second_point, "tag_origin" );
		stopFxOnTag( getfx( "a10_point_invalid" ), level.a10_second_point, "tag_origin" );
		level.a10_second_point delete();
	}
}

destroy_start_point()
{
	if(isdefined(level.a10_start_point))
	{
		stopFxOnTag( getfx( "a10_point" ), level.a10_start_point, "tag_origin" );
		stopFxOnTag( getfx( "a10_point_active" ), level.a10_start_point, "tag_origin" );
		stopFxOnTag( getfx( "a10_point_invalid" ), level.a10_start_point, "tag_origin" );
		level.a10_start_point delete();
	}
}

set_aim_target_direction_point_vfx()
{
	level.player endon( "toggle_airstrike" );//so we can disable laser during cool down.
	level.player endon("airstrike_called");
	level.player endon("turn_off_airstrike");
	level.player endon("airstrike_path_fail");
	
	impact_start_buffer = 128;
	
	if(!isdefined(level.a10_start_point))
	{
		level.a10_start_point  = Spawn( "script_model", (0,0,0) );
		level.a10_start_point SetModel( "tag_origin" ); 
		level.a10_start_point.angles = level.aim_arrow.angles;
		level.a10_start_point.origin = level.aim_arrow.origin;
		stopFxOnTag( getfx( "a10_point" ), level.aim_arrow, "tag_origin" );
		playfxontag( getfx( "a10_point_active" ), level.a10_start_point, "tag_origin" );
	}
	
	create_second_point();
	thread draw_directional_line();
	prev_fail = false;
	
	while(1)
	{
		aim_target = calculate_target_pos();
		if(aim_target[ "fraction" ] < 1)
		{
			//draws a vfx line between the start and end points
			if(prev_fail)
			{
				create_second_point();
				thread draw_directional_line();
				prev_fail = false;
			}
			
			level.a10_second_point.origin = aim_target["pos"];
			
			/*//align second point fx pointing towards player
			angle_vector = level.a10_second_point.origin - (level.player geteye());
			constrained_angle = VectorToAngles(angle_vector);
			level.a10_second_point.angles = (-90,constrained_angle[1],0);
			
			//align first point fx pointing towards player
			angle_vector = level.a10_start_point.origin - (level.player geteye());
			constrained_angle = VectorToAngles(angle_vector);
			level.a10_start_point.angles = (-90,constrained_angle[1],0);*/
			
			//change indicator to red if you are past the strafe distance
			dist_max = level.a10_distance_to_start_impacts_back_from_target + level.a10_distance_to_stop_impacts_from_target;
			if(Distance(level.a10_start_point.origin, level.a10_second_point.origin) > dist_max)
			{
				if(level.a10_second_point.lineType == "green")
				{
					stopFxOnTag( getfx( "a10_point" ), level.a10_second_point, "tag_origin" );
					playfxontag( getfx( "a10_point_invalid" ), level.a10_second_point, "tag_origin" );
					level.a10_second_point.lineType = "red";
				}
			}
			else
			{
				if(level.a10_second_point.lineType == "red")
				{
					stopFxOnTag( getfx( "a10_point_invalid" ), level.a10_second_point, "tag_origin" );
					playfxontag( getfx( "a10_point" ), level.a10_second_point, "tag_origin" );
					level.a10_second_point.lineType = "green";
				}
			}
			
			controls = getDvar("a10_strike_controls");	
			if(controls != "points")
			{
				angles = vectortoangles( level.a10_second_point.origin - level.a10_start_point.origin );
				forward = anglestoforward( flat_angle(angles) );
			
				level.aim_arrow.origin = level.a10_start_point.origin + (forward*(level.a10_distance_to_start_impacts_back_from_target - impact_start_buffer));
			}	
			
			level.player notify("airstrike_second_point_confirmed");			
		}
		else
		{
			/#
			if(isdefined(aim_target["entity"]) && isdefined(aim_target["entity"].team) && aim_target["entity"].team == "allies")
			{
				if(!isdefined(level.berlin_a10_targetfriendly_print_time))
					level.berlin_a10_targetfriendly_print_time = 0;
					
				if(level.berlin_a10_targetfriendly_print_time + 5000 < GetTime() )
				{
//					iprintlnbold("cant target friendlies");
					level.berlin_a10_targetfriendly_print_time = GetTime();
				}
			}
			#/
			level.player notify("airstrike_second_point_failure");	
			destroy_directional_line( false );	
			destroy_second_point();
			prev_fail = true;
		}
		wait(.05);
	}
}



//sets start and end points around the center point, used for ads and static controls
draw_directional_info(){
	level.player endon( "toggle_airstrike" );
	level.player endon("airstrike_called");
	level.player endon("turn_off_airstrike");
	level.player endon("airstrike_path_fail");

	level.a10_start_point  = Spawn( "script_model", (0,0,0) );
	level.a10_start_point SetModel( "tag_origin" ); 
	level.a10_start_point.angles = level.aim_arrow.angles;
	playfxontag( getfx( "a10_point" ), level.a10_start_point, "tag_origin" );
	
	level.a10_second_point = Spawn( "script_model", (0,0,0) );
	level.a10_second_point SetModel( "tag_origin" );
	level.a10_second_point.angles = level.aim_arrow.angles;
	playfxontag( getfx( "a10_point" ), level.a10_second_point, "tag_origin" );
	
	while(1){
		forward = anglestoforward(flat_angle(level.aim_arrow.angles));
		level.a10_start_point.origin = level.aim_arrow.origin - forward * level.a10_distance_to_start_impacts_back_from_target;
		level.a10_second_point.origin = level.aim_arrow.origin + forward * level.a10_distance_to_stop_impacts_from_target;
		wait(.05);
	}	
}

//draws vfx line between start and end points
draw_directional_line()
{
	level.player endon( "toggle_airstrike" );
	level.player endon("airstrike_called");
	level.player endon("turn_off_airstrike");
	level.player endon("airstrike_path_fail");
	
	controls = getDvar("a10_strike_controls");	
	if(controls == "points")
	{
		level.player endon( "airstrike_second_point_failure" );
	}	
	
	dist_max = level.a10_distance_to_start_impacts_back_from_target + level.a10_distance_to_stop_impacts_from_target;
	
	//how much space between fx there is
	distance_delta = 64;

	if(!isdefined(level.direction_line))
		level.direction_line = [];

	while(1)
	{
		//how far from the start point the fx should appear
		//starts at 64 because we already place an fx at the start point
		current_distance = 64;
		
		assert(isdefined(level.a10_start_point));
		assert(isdefined(level.a10_second_point));
		
		line_distance = Distance(level.a10_start_point.origin, level.a10_second_point.origin);
		
		while(current_distance < line_distance)
		{
			angles = vectortoangles( level.a10_second_point.origin - level.a10_start_point.origin );
			forward = anglestoforward( angles );
			vfx_angle = angles * (0,1,1) + (270,90,0);
			fx_point = level.a10_start_point.origin + (0,0,10) + forward * current_distance;
			no_line_vfx = true;
			
			//update the dashes to the current direction set by player.
			foreach(line_vfx in level.direction_line)
			{
				//if line_vfx.dist is the next one we're looking for
				if(line_vfx.dist == current_distance)
				{
					//update the position and skip creation
					if(line_vfx.origin != fx_point || line_vfx.angles != vfx_angle)
					{
						line_vfx.origin = fx_point;
						line_vfx.angles = vfx_angle;
					}

					no_line_vfx = false;
				}
			}
			
			//spawn new dashes if the player has extended the line.
			//or if we cant find the old one for some reason
			if( no_line_vfx )
			{
				new_fx = spawn_tag_origin();
				new_fx.origin = fx_point;
				new_fx.angles = vfx_angle;
				//this is effectively the index in the line ( / distance_delta
				new_fx.dist = current_distance;
				
				array_idx = (current_distance / distance_delta);
				is_odd = ( int(array_idx) % 2);
				
				new_fx GetLineFx( (current_distance < dist_max), is_odd );
				
				
				new_fx.start_delay = .1 * array_idx;
				
				if(current_distance == distance_delta) //first thing in the line
				{
					level.direction_line_start_time = GetTime();
				}
				
				new_fx thread DelayedStartLineFx( array_idx );
				
				level.direction_line = array_add(level.direction_line, new_fx);
			}
			
			current_distance += distance_delta;
		}
		
		//remove any dashes that are beyond where the player is pointing.
		foreach(line_vfx in level.direction_line)
		{
			if(line_vfx.dist >= current_distance)
			{
				thread clean_up_direction_line(line_vfx, true);
			}
		}
	
		wait(.1);
	}
}

DelayedStartLineFx( line_idx )
{
	assert( isdefined( self.start_delay ) );
	
	//if the lifetime of the vfx we are playing changes this fx_lifetime_sec must be updated!
	fx_lifetime_sec = level.a10_fx_lifetime_sec;
	fx_lifetime_ms = fx_lifetime_sec * 1000;
	assert( isdefined( self.start_delay < fx_lifetime_sec ) );
	
	curr_time = GetTime();
	cycle_time_ms = curr_time - level.direction_line_start_time;
	cycle_modded_ms = cycle_time_ms % fx_lifetime_ms;
	
	if( cycle_modded_ms > ( 1000 * self.start_delay ) )
		self.start_delay += fx_lifetime_sec;
	
	self.start_delay -= cycle_modded_ms / 1000;
		
	//to confirm we have a zero time not a negative time being generated
	//PS3 one time returned -5.96046e-08 so as long as the start delay is less than one frame in the past we're cool
	AssertEx( self.start_delay >= -0.05, "start_delay " + self.start_delay + " GetTime " + curr_time + " level.direction_line_start_time " + level.direction_line_start_time + " cycle_modded_time_ms " + cycle_modded_ms + " line_idx " + line_idx );
	actual_wait = self.start_delay;
	
	if( actual_wait > 0 ) //its possible to generate a zero wait time
		wait actual_wait;
	
	if( isdefined( self ) )
	{
		assert( isdefined( self.vfx ) );
		PlayFXOnTag( getfx( self.vfx ), self, "tag_origin" );
		
		if( line_idx == 2 )
		{
			PlayFXOnTag( getfx( "a10_distance_number_0" ), self, "tag_origin" );
		}
		else if( line_idx == 6 )
		{
			PlayFXOnTag( getfx( "a10_distance_number_1" ), self, "tag_origin" );
		}
		else if( line_idx == 10 )
		{
			PlayFXOnTag( getfx( "a10_distance_number_2" ), self, "tag_origin" );
		}
		else if( line_idx == 14 )
		{
			PlayFXOnTag( getfx( "a10_distance_number_3" ), self, "tag_origin" );
		}
	}
}

GetLineFx( under_dist, is_odd )
{
	if( under_dist )
	{
		self.lineType = "green";
		self.vfx = "a10_green_line";
		if ( is_odd )
		{
			self.vfx = "a10_green_line_short";
		}
	}
	else
	{
		self.lineType = "red";
		self.vfx = "a10_red_line";					
		if ( is_odd )
		{
			self.vfx = "a10_red_line_short";
		}
	}	
}


clean_up_direction_line( line_vfx, force_drop )
{
	level.direction_line = array_remove( level.direction_line, line_vfx );

	if( level.a10_drop_vfx_for_destroy || force_drop )
	{
		line_vfx.origin += ( 0, 0, -10000 );
		wait( .05 );
	}
	
	if(line_vfx.lineType == "green")
	{
		stopFxOnTag( getfx( "a10_green_line" ), line_vfx, "tag_origin" );
	}
	else
	{
		stopFxOnTag( getfx( "a10_red_line" ), line_vfx, "tag_origin" );
	}
	
	line_vfx delete();
}


first_point_cleanup()
{
	self notify( "kill_draw_target_aim" );
	level.player endon( "toggle_airstrike" );
	wait( 0.05 );
	thread draw_target_aim( false );
}


monitor_second_point_cleanup()
{
	level.player endon( "toggle_airstrike" );
	level.player endon( "turn_off_airstrike" );
	level.player endon( "airstrike_second_point_confirmed" );
	
	level.player waittill( "airstrike_second_point_failure" );
	
	self notify("kill_airstrike_trigger");
	thread airstrike_trigger(true);
}

airstrike_trigger(skip_trigger)
{
	level.player endon( "toggle_airstrike" );
	level.player endon( "turn_off_airstrike" );
	self endon("kill_airstrike_trigger");
	
	if(!isdefined(skip_trigger))
		skip_trigger = false;
	
	controls = getDvar("a10_strike_controls");	
	if(controls == "points")
	{
		level.player endon( "airstrike_first_point_failure" );
	}
	
	if(!skip_trigger)
		level.player waittill("trigger_a10");
	
	if(controls == "points")
	{
		if(!skip_trigger)
			level.player waittill( "airstrike_first_point_confirmed" );
		
		maps\_audio::aud_send_msg("a10_first_point_confirmed");
		level.player notify("airstrike_set_second_point");
		childthread set_aim_target_direction_point_vfx();
		thread airstike_hint_text_points();
		level.player waittill("trigger_a10");
		if(controls == "points")
		{	
			thread monitor_second_point_cleanup();
		}
		level.player waittill("airstrike_second_point_confirmed");
	}
	
//	IPrintLn("strike confirmed");
	maps\_audio::aud_send_msg("a10_second_point_confirmed");
	
	weapon = GetDVar("airstrike_weapon", "a10");
	if(weapon == "random")
	{
		valid_weapon_arr = ["a10", "25mm", "40mm", "105mm", "hellfire", "artillery"];
		weapon = valid_weapon_arr[randomint(valid_weapon_arr.size)];
	}
	
	if(airstrike_get_path(weapon))
	{
		level.player notify( "airstrike_called" );

		target_ent_origin = level.aim_arrow.origin;
		target_ent_angles = level.aim_arrow.angles;
		
		if(controls == "points")
		{
			target_ent_origin = level.a10_start_point.origin;
			target_ent_angles = vectortoangles( level.a10_second_point.origin - level.a10_start_point.origin );
		}
		
		if(weapon == "a10")
		{
			thread airstrike_animated( target_ent_origin,target_ent_angles );
		}
		else if( weapon == "25mm" || weapon == "40mm" || weapon == "105mm")
		{
			wait(level.wait_time_before_strike);
	
			level.player notify( "airstrike_on_inbound" );
			//ac130_40mm
			//ac130_25mm
			//ac130_105mm
			
			proper_weapon_name = "ac130_" + weapon;
			
			//if(weapon == "25mm")
			variance = 300;
			shots = 12 + randomint(4);
			delay = 0.10;
			bEarthquake = false;
			eq_data = [];
			bRadiusDmg = true;
			
			if(weapon == "40mm")
			{
				variance = 400;
				shots = 3;
				delay = 0.75;
				bEarthquake = true;
				eq_data = [.5, .4];
				bRadiusDmg = false;
			}
			else if(weapon == "105mm")
			{
				variance = 100;
				shots = 1;
				delay = 0.05;
				bEarthquake = true;
				eq_data = [.8, .6];
				bRadiusDmg = false;
			}
			
			for(i = 0; i < shots; i += 1)
			{
				alt_name = proper_weapon_name;
				alt_to_use = randomint(3);
				if(alt_to_use == 1)
					alt_name += "_alt";
				else if(alt_to_use == 2)
					alt_name += "_alt2";
					
				start_point = target_ent_origin + (0,0,1000);
				end_point = target_ent_origin + (randomfloat(variance) - variance/2, randomfloat(variance) - variance/2, 0);
				MagicBullet( alt_name, start_point, end_point, level.player );
				if(bEarthquake)
					thread equake_wrapper( eq_data[0], eq_data[1], end_point, 5000 );
				if(bRadiusDmg)
					thread radius_dmg_wrapper( end_point, 128, 500, 100, level.player);
				wait(delay);
			}
		}
		else if(weapon == "hellfire")
		{
			wait(level.wait_time_before_strike);
		
			level.player notify( "airstrike_on_inbound" );
			step = 200;
			shots = randomint(2) + 3;
			delay = 0.8;
			
			//hellfires
			name = "hellfire_missile_af_caves_end";
		
			attack_angle = randomint(360);
			rotation = (cos(attack_angle), sin(attack_angle), 0);

			for(i = 0; i < shots; i += 1)
			{
				start_point = target_ent_origin + (0,0,1000);
				end_point = target_ent_origin + (rotation[0] * step * i, rotation[1] * step * i, 0);
				MagicBullet( name, start_point, end_point, level.player);
				radiusDamage(end_point, 512, 1000, 100, level.player);
				earthquake( 0.5, 0.5, end_point, 5000 );
				wait(delay);
			}
		}
		else if(weapon == "artillery")
		{
			wait(level.wait_time_before_strike);
	
			level.player notify( "airstrike_on_inbound" );
			
			variance = 400;
			shots = 3;
			delay = 1.15;
			
			effect_arr = ["artillery", "artillery_alt", "artillery_alt2", "artillery_alt3"];
			
			for(i = 0; i < shots; i += 1)
			{
				end_point = target_ent_origin + (randomfloat(variance) - variance/2, randomfloat(variance) - variance/2, 0);
				radiusDamage(end_point, 256, 1000, 100, level.player);
				effect = level._effect[effect_arr[randomint(effect_arr.size)] ];
				playfx( effect, end_point );
				earthquake( 0.3, 0.7, end_point, 3000 );
				thread play_sound_in_space( "exp_artillery_underground_low", end_point);
				wait(delay);
			}
			
		}
	}
	else
	{
		thread airstrike_cant_get_there_radio_dialogue();
		
		if(controls == "points")
		{
			level.player notify("airstrike_path_fail");
			
			if( isdefined( level.a10_start_point ) )
				playfxontag( getfx( "a10_point_invalid_active" ), level.a10_start_point, "tag_origin" );
			
			if( isdefined( level.a10_second_point ) )
				playfxontag( getfx( "a10_point_invalid_active" ), level.a10_second_point, "tag_origin" );
			
			if( isDefined( level.direction_line ) )
			{
				foreach( line_vfx in level.direction_line )
				{
					playfx( getfx( "a10_point_invalid_active" ), line_vfx.origin );
				}
			}
			
			airstrike_clean_up_target_points( true );
			
			if(isDefined(level.a10_hint_hud_points))
				level.a10_hint_hud_points.alpha = 0;
			if(isDefined(level.a10_hint_hud))
				level.a10_hint_hud.alpha = 1;
				
			thread draw_target_aim( false );
		}
		else
		{
			//wait for another trigger
			thread airstrike_trigger();
		}
	}
}

equake_wrapper( arg1, arg2, arg3, arg4 )
{
	wait 0.35;
	earthquake( arg1, arg2, arg3, arg4 );
}

radius_dmg_wrapper( arg1, arg2, arg3, arg4, arg5 )
{
	wait 0.4;
	radiusDamage( arg1, arg2, arg3, arg4, arg5);
}

airstrike_get_path(weapon)
{	
	level.player endon( "toggle_airstrike" );
	
	controls = getDvar("a10_strike_controls");	
	
	start_point = level.aim_arrow.origin;
	
	if(controls == "points")
	{
		start_point = level.a10_start_point.origin;
	}
	
	if(weapon == "a10")
	{
		flytime = level.a10_flytime;
		angles_copy = level.aim_arrow.angles;
		
		if(controls == "points")
		{
			angles_copy = vectortoangles( level.a10_second_point.origin - level.a10_start_point.origin );
		}
		
		airstrike_path = 1;
		path = undefined;
		
		while(airstrike_path < 4)
		{
			count = 0;
			flyheight = (0,0,0);
			flyback_distance = 0;
			level.flyheight_passed = flyheight;
			level.flyback_distance_passed = flyback_distance;
			
			while(count < 4)
			{
				path = setup_animated_path(start_point, angles_copy, flyheight, flyback_distance, airstrike_path);
				if(checkPath(path))
				{
					level.a10_path = path;
					level.flyheight_passed = flyheight;
					level.flyback_distance_passed = flyback_distance;
					break;				
				}

				else if(getdvarInt("a10_strike_debug", 0) == 4)
				{
					/#						
					thread a10_draw_debug_path(angles_copy, path, flytime);		
					#/						
				}
							

				count++;					
				
				//clean up bad path
				path = undefined;
				
				//go higher
				flyheight += level.a10_flyheight_increment;
				flyback_distance += level.a10_fly_distance_back_increment;
			}
			
			//if we have a path don't change the anim
			if(isdefined(path))
			{
				break;
			}
			//if the path check failed try and different anim
			airstrike_path++;
		}
		return isdefined(path);
	}
	else if( weapon == "25mm" || weapon == "40mm" || weapon == "105mm")
	{
		//comes almost straight down. 
		//bullet trace straight down?
		trace = BulletTrace(start_point + (0,0,1000), start_point + (0,0,16), false, undefined);
		return (trace["fraction"] > .8);
		return true;	
	}		
	
	return true; //default case
}

a10_draw_debug_path(angles, path, flytime)
{
	level endon("airstrike_second_point_confirmed");
	wingAngle = anglestoright(flat_angle(angles));
	RightWing = wingAngle * 352;
	LeftWing = (-1*wingAngle) * 352;
	
	color_arr = (.8,.4,.2);
	
	while(1){
		for(i=0; i<path.size -1; i++){
			line(path[i].origin, path[i+1].origin, color_arr);
			line(path[i].origin+rightwing, path[i+1].origin+rightwing, color_arr);
			line(path[i].origin+leftwing, path[i+1].origin+leftwing, color_arr);
		}
		wait(.05);
	}
}

set_oriented_points(target_origin, target_angels, org_origin, path_origin, path_angles ){
	xdelta = org_origin[0] - path_origin[0];
	ydelta = org_origin[1] - path_origin[1];
	
	angles = (target_angels - path_angles);
	
	newX = xdelta * cos(angles[1]) - ydelta * sin(angles[1]) + org_origin[0];
	newY = xdelta * sin(angles[1]) + ydelta * cos(angles[1]) + org_origin[1];
	
	new_point = [];
	new_point[0] = target_origin[0] - org_origin[0] + newX;
	new_point[1] = target_origin[1] - org_origin[1] + newY;
	new_point[2] = path_origin[2];
	return new_point;
}

setup_animated_path(target_org, target_angles, flyheight, flyback_distance, airstrike_path ){
	switch(airstrike_path)
	{
		case 1:
			
			path = airstrike_anim_2_path();
			level.airstrike_anim_name = "berlin_a10_strafe_run_02";
		break;
		case 2:
			path = airstrike_anim_3_path();
			level.airstrike_anim_name = "berlin_a10_strafe_run_03";
		break;
		case 3:
			path = airstrike_anim_1_path();
			level.airstrike_anim_name = "berlin_a10_strafe_run_01";
		break;
		default:
			path = airstrike_anim_1_path();
			level.airstrike_anim_name = "berlin_a10_strafe_run_01";
		break;
	}
	
	path_angles = vectortoangles((-1,0,0));
	forward = AnglesToForward(flat_angle(target_angles));
	
	foreach(point in path){
		if(!isstring(point))
		{
			newVector = set_oriented_points(target_org, target_angles,(0,0,0), point.origin, path_angles );
			point.origin = (newVector[0],newVector[1],newVector[2]+flyheight[2])+((-1*forward)*flyback_distance);
		}
	}
	return path;
}

airstrike_anim_1_path()
{
	path = [];

	path[0] = spawnstruct();
	path[0].origin = (-10056.9, 13.1325, 3909.61);
	path[1] = spawnstruct();
	path[1].origin = (-9288.56, 28.2926, 4284.37);
	path[2] = spawnstruct();
	path[2].origin = (-8548.17, 26.452, 4561.41);
	path[3] = spawnstruct();
	path[3].origin = (-7788.31, 18.3251, 4736.73);
	path[4] = spawnstruct();
	path[4].origin = (-6989.26, 14.8047, 4819.12);
	path[5] = spawnstruct();
	path[5].origin = (-6177.03, 23.9315, 4790.79);
	path[6] = spawnstruct();
	path[6].origin = (-5367.89, 34.9308, 4624.75);
	path[7] = spawnstruct();
	path[7].origin = (-4570.5, 34.8316, 4224.46);
	path[8] = spawnstruct();
	path[8].origin = (-3783.61, 21.0125, 3497.92);
	path[9] = spawnstruct();
	path[9].origin = (-2993.69, 7.80361, 2642.02);
	path[10] = spawnstruct();
	path[10].origin = (-2188.99, 5.64912, 1936.23);
	path[11] = spawnstruct();
	path[11].origin = (-1369.55, 5.40654, 1306.5);
	path[12] = spawnstruct();
	path[12].origin = (-532.087, 5.53242, 895.056);
	path[13] = spawnstruct();
	path[13].origin = (327.03, 6.24819, 937.038);
	path[14] = spawnstruct();
	path[14].origin = (1200.39, 6.99051, 1209.14);
	path[15] = spawnstruct();
	path[15].origin = (2107.8, 6.3943, 1653.24);
	path[16] = spawnstruct();
	path[16].origin = (3048.03, 6.18817, 2146.4);
	path[17] = spawnstruct();
	path[17].origin = (4014.69, 7.72807, 2638.88);
	path[18] = spawnstruct();
	path[18].origin = (4996.06, 6.71646, 3117.33);
	path[19] = spawnstruct();
	path[19].origin = (5982, -3.48998, 3558.96);
	path[20] = spawnstruct();
	path[20].origin = (6971.07, -26.779, 4002.91);
	path[21] = spawnstruct();
	path[21].origin = (7961.54, -28.7748, 4397.24);
	path[22] = spawnstruct();
	path[22].origin = (8949.47, -25.9104, 4602.09);
	path[23] = spawnstruct();
	path[23].origin = (9911.91, -28.1551, 4504.06);
	
	return path;
}

airstrike_anim_2_path()
{
	path = [];
/*
	path[0] = spawnstruct();
	path[0].origin = (-14573.8, 4.29401, 1093.32);
	path[1] = spawnstruct();
	path[1].origin = (-13734.2, 6.51784, 1590.65);
	path[2] = spawnstruct();
	path[2].origin = (-12903.5, 9.78488, 2064.97);
	path[3] = spawnstruct();
	path[3].origin = (-12085.2, 11.0998, 2456.43);
	path[4] = spawnstruct();
	path[4].origin = (-11284.1, 10.2934, 2708.67);
	path[5] = spawnstruct();
	path[5].origin = (-10504.6, 4.62841, 2838.43);
	path[6] = spawnstruct();
	path[6].origin = (-9772.71, 2.04831, 2901.63);*/
	path[0] = spawnstruct();
	path[0].origin = (-9091.65, -23.2342, 2924.63);
	path[1] = spawnstruct();
	path[1].origin = (-8429.11, -29.6148, 2884.12);
	path[2] = spawnstruct();
	path[2].origin = (-7754.02, -32.7071, 2793.82);
	path[3] = spawnstruct();
	path[3].origin = (-7045.23, -32.8687, 2669.79);
	path[4] = spawnstruct();
	path[4].origin = (-6319.91, -28.1018, 2518.06);
	path[5] = spawnstruct();
	path[5].origin = (-5587.42, -19.8092, 2349.16);
	path[6] = spawnstruct();
	path[6].origin = (-4854.06, -10.8168, 2174.63);
	path[7] = spawnstruct();
	path[7].origin = (-4124.35, -3.30188, 1995.74);
	path[8] = spawnstruct();
	path[8].origin = (-3392.13, 2.82406, 1793.46);
	path[9] = spawnstruct();
	path[9].origin = (-2654.41, 5.53648, 1600.61);
	path[10] = spawnstruct();
	path[10].origin = (-1912.24, 5.42406, 1436);
	path[11] = spawnstruct();
	path[11].origin = (-1167.66, 6.08207, 1285.22);
	path[12] = spawnstruct();
	path[12].origin = (-421.469, 5.42027, 1161.46);
	path[13] = spawnstruct();
	path[13].origin = (327.288, 6.19893, 1101.52);
	path[14] = spawnstruct();
	path[14].origin = (1074.6, 7.23231, 1101.37);
	path[15] = spawnstruct();
	path[15].origin = (1821.74, 5.79744, 1139.21);
	path[16] = spawnstruct();
	path[16].origin = (2564.38, 8.6126, 1234.25);
	path[17] = spawnstruct();
	path[17].origin = (3303.87, 18.014, 1399.4);
	path[18] = spawnstruct();
	path[18].origin = (4043.36, 27.5554, 1619.29);
	path[19] = spawnstruct();
	path[19].origin = (4785.79, 33.332, 1869.76);
	path[20] = spawnstruct();
	path[20].origin = (5535.7, 36.2899, 2122.15);
	path[21] = spawnstruct();
	path[21].origin = (6296.13, 37.8413, 2354.19);
	path[22] = spawnstruct();
	path[22].origin = (7068.21, 38.9115, 2553.21);
	path[23] = spawnstruct();
	path[23].origin = (7853.21, 41.6815, 2708.55);
	path[24] = spawnstruct();
	path[24].origin = (8650.68, 55.0736, 2800.63);
	/*path[32] = spawnstruct();
	path[32].origin = (9469.11, 40.1059, 2827.81);
	path[33] = spawnstruct();
	path[33].origin = (10309.5, -64.6017, 2781.27);
	path[34] = spawnstruct();
	path[34].origin = (11168, -254.417, 2659.07);
	path[35] = spawnstruct();
	path[35].origin = (12040.9, -514.223, 2461.02);
	path[36] = spawnstruct();
	path[36].origin = (12926.8, -827.767, 2186.36);
	path[37] = spawnstruct();
	path[37].origin = (13820.5, -1203.02, 1834.16);
	path[38] = spawnstruct();
	path[38].origin = (14719.6, -1645.39, 1407.2);
	path[39] = spawnstruct();
	path[39].origin = (15621.7, -2139.21, 905.134);
	path[40] = spawnstruct();
	path[40].origin = (16527.1, -2671.53, 326.621);*/
	
	return path;
}

airstrike_anim_3_path()
{
	path = [];
	/*path[0] = spawnstruct();
	path[0].origin = (-15177.9, 1.82415, 788.332);
	path[1] = spawnstruct();
	path[1].origin = (-14494.8, 1.86341, 1218.67);
	path[2] = spawnstruct();
	path[2].origin = (-13546, 1.67338, 1812.3);
	path[3] = spawnstruct();
	path[3].origin = (-12473.3, 2.37926, 2477.81);
	path[4] = spawnstruct();
	path[4].origin = (-11416.7, 5.80599, 3121.93);
	path[5] = spawnstruct();
	path[5].origin = (-10519.5, 12.1161, 3653.97);
	path[6] = spawnstruct();
	path[6].origin = (-9789.21, 20.1694, 4070.54);*/
	path[0] = spawnstruct();
	path[0].origin = (-9110.42, 29.6127, 4410.74);
	path[1] = spawnstruct();
	path[1].origin = (-8443.64, 24.4333, 4606.25);
	path[2] = spawnstruct();
	path[2].origin = (-7756.91, 18.272, 4606.93);
	path[3] = spawnstruct();
	path[3].origin = (-7037.71, 15.027, 4447.98);
	path[4] = spawnstruct();
	path[4].origin = (-6306.83, 21.478, 4158.94);
	path[5] = spawnstruct();
	path[5].origin = (-5577.11, 32.7816, 3770.47);
	path[6] = spawnstruct();
	path[6].origin = (-4856.11, 36.694, 3312.49);
	path[7] = spawnstruct();
	path[7].origin = (-4144.47, 27.9597, 2822.09);
	path[8] = spawnstruct();
	path[8].origin = (-3437.49, 14.1074, 2332.84);
	path[9] = spawnstruct();
	path[9].origin = (-2721.98, 6.54957, 1871.16);
	path[10] = spawnstruct();
	path[10].origin = (-1989.45, 5.55282, 1466.05);
	path[11] = spawnstruct();
	path[11].origin = (-1242.48, 5.18994, 1144.73);
	path[12] = spawnstruct();
	path[12].origin = (-489.53, 6.17668, 917.271);
	path[13] = spawnstruct();
	path[13].origin = (275.15, 6.53617, 849.875);
	path[14] = spawnstruct();
	path[14].origin = (1061.18, 7.11486, 936.346);
	path[15] = spawnstruct();
	path[15].origin = (1887.17, 6.92493, 1097.46);
	path[16] = spawnstruct();
	path[16].origin = (2753.27, 6.25139, 1303.29);
	path[17] = spawnstruct();
	path[17].origin = (3649.27, 7.25302, 1584.16);
	path[18] = spawnstruct();
	path[18].origin = (4564.32, 8.06856, 1930.43);
	path[19] = spawnstruct();
	path[19].origin = (5488.54, 4.33213, 2304.48);
	path[20] = spawnstruct();
	path[20].origin = (6409.78, -7.72615, 2700.24);
	path[21] = spawnstruct();
	path[21].origin = (7315.35, -26.545, 3221.62);
	path[22] = spawnstruct();
	path[22].origin = (8193.85, -29.4547, 3775.35);
	path[23] = spawnstruct();
	path[23].origin = (9038.56, -22.9634, 4201.68);
	path[24] = spawnstruct();
	path[24].origin = (9823.84, -25.876, 4347.68);
	/*
	path[32] = spawnstruct();
	path[32].origin = (10559.3, -19.928, 4202.55);
	path[33] = spawnstruct();
	path[33].origin = (11318.7, 67.044, 3828.11);
	path[34] = spawnstruct();
	path[34].origin = (12081.9, 252.546, 3291.18);
	path[35] = spawnstruct();
	path[35].origin = (12818.4, 542.8, 2653.36);
	path[36] = spawnstruct();
	path[36].origin = (13500.7, 947.098, 1974.97);
	path[37] = spawnstruct();
	path[37].origin = (14100, 1634.19, 1313.21);
	path[38] = spawnstruct();
	path[38].origin = (14585.3, 2569.63, 728.71);
	path[39] = spawnstruct();
	path[39].origin = (14918.8, 3431.02, 301.212);
	*/
	return path;
}



checkPath(path_array){

	for(i=0; i<path_array.size-1; i++)
	{
		if(!a10_sightTraceWrapper( path_array[i].origin, path_array[i+1].origin ))
		{
			/#
				if(getdvarInt("a10_strike_debug", 0) == 1)
				{
					thread hint("General Path Failure",3);
				}
			#/
			return false;
		}
	}
	
	if(!checkPathWings(path_array))
	{
		/#
			if(getdvarInt("a10_strike_debug", 0) == 1)
			{
				thread hint("Wing Path Failure",3);
			}
		#/
		return false;
	}
	
	return true;
}

a10_sightTraceWrapper( start, end )
{
	if(!SightTracePassed( start, end, false, false ))
	{
	/# 
		debug_val = getdvarInt("a10_strike_debug", 0);
		if( debug_val == 2 || debug_val == 3  || debug_val == 5 )
			thread maps\berlin_util::DLine( start, end, 3, (1,0,0) ); 
			
		if( debug_val == 5 )
		{
			physEnd = physicstrace( start, end );	
			IPrintLn( "start: " + start + " end: " + end + " physEnd: " + physEnd );
			bTrace = bulletTrace( start, end, false );
			IPrintLn( "bullet trace > trace results :");
			if(isdefined( bTrace["entity"] ))
				IPrintLn( "entity " + bTrace["entity"]);
			if(isdefined( bTrace["fraction"] ))
				IPrintLn( "fraction " + bTrace["fraction"]);
			if(isdefined( bTrace["position"] ))
				IPrintLn( "position " + bTrace["position"]);
			if(isdefined( bTrace["normal"] ))
				IPrintLn( "normal " + bTrace["normal"]);
			if(isdefined( bTrace["surfaceType"] ))
				IPrintLn( "surfacetype" + bTrace["surfacetype"]);
		}			
	#/			
		return false;
	}
	/# 
	if(getdvarInt("a10_strike_debug", 0) == 3)
		thread maps\berlin_util::DLine( start, end, 3, (0,0,1) ); 
	#/
	return true;
}

checkPathWings(path_array){
	wingAngle = anglestoright(flat_angle(level.aim_arrow.angles));
	RightWing = wingAngle * 352;
	LeftWing = (-1*wingAngle) * 352;
	
	for(i=0; i<path_array.size-1; i++){
		//right wing check
		current = path_array[i].origin;
		next = path_array[i+1].origin;
		if(!a10_sightTraceWrapper( current + RightWing, next + RightWing ))
			return false;
		//left wing check
		if(!a10_sightTraceWrapper( current + LeftWing, next + LeftWing ))
			return false;
	}
	
	return true;
}

airstrike_animated( target_ent_origin, target_ent_angles )
{
	thread maps\_audio::aud_send_msg("a10_airstrike_requested");
	
	//FLASH ALL HERE
	stopFxOnTag( getfx( "a10_point" ), level.a10_second_point, "tag_origin" );
	stopFxOnTag( getfx( "a10_point_invalid" ), level.a10_second_point, "tag_origin" );
	playfxontag( getfx( "a10_point_active" ), level.a10_second_point, "tag_origin" );
	
	stopFxOnTag( getfx( "a10_point" ), level.a10_start_point, "tag_origin" );
	playfxontag( getfx( "a10_point_active" ), level.a10_start_point, "tag_origin" );
	
	if(isDefined(level.direction_line))
	{
		foreach(line_vfx in level.direction_line)
		{
			stopFxOnTag( getfx( "a10_green_line_active" ),line_vfx,"tag_origin");
			stopFxOnTag( getfx( "a10_red_line" ),line_vfx,"tag_origin");
			playfxontag( getfx( "a10_green_line_active" ), line_vfx, "tag_origin" );
		}
	}
	
	wait( level.a10_confirm_second_point_wait_time );
	
	raw_angles = target_ent_angles;
	direction = flat_angle(raw_angles);	
	impact_direction = anglesToForward(direction);
	
	impact_start = target_ent_origin + ((-1*impact_direction) * level.a10_distance_to_start_impacts_back_from_target);
	impact_end = target_ent_origin + (impact_direction * level.a10_distance_to_stop_impacts_from_target);
	
	badplace_points = [impact_start, target_ent_origin, impact_end];
	
	do_a10_badplace( badplace_points, level.wait_time_before_strike + 4, "allies");
	
	wait(level.wait_time_before_strike);
	
	level.player notify( "airstrike_on_inbound" );
	animation_distance_back_from_center = 15700;
	animation_distance_up_from_center = 512;

	anim_ent = spawn("script_origin", target_ent_origin + ((-1*impact_direction) * (animation_distance_back_from_center+level.flyback_distance_passed))+(0,0,animation_distance_up_from_center)+level.flyheight_passed);

/#	
	////for generating points to define a10 path
	generate_path = getDvar("a10_strike_generate_path");
	if(generate_path == "1")
	{
		anim_ent delete();
		target_ent_origin = (0,0,0);
		direction = (0,0,0);
		impact_direction = anglesToForward(direction);
		anim_ent = spawn("script_origin", target_ent_origin + ((-1*impact_direction) * (animation_distance_back_from_center))+(0,0,animation_distance_up_from_center));
	}
#/
	
	if(!isdefined(level.a10_start_impact))
		level.a10_start_impact = spawnstruct();
	
	level.a10_start_impact.origin = impact_start;
	
	if(!isdefined(level.a10_end_impact))
		level.a10_end_impact = spawnstruct();
	
	level.a10_end_impact.origin = impact_end;

	anim_ent.angles = direction;
	assertex(!isDefined(level.a10_dynamic), "There is another A10 in the air, your timers for a10 are too short");
	spawner = getEnt("a10_dynamic", "script_noteworthy");
	level.a10_dynamic = spawner spawn_vehicle();
	level.a10_dynamic.angles = direction;
	level.a10_dynamic.animname = "a10";
	level.a10_dynamic thread airstrike_animated_rumble();
/#	
	////for generating points to define a10 path
	generate_path = getDvar("a10_strike_generate_path");
	if(generate_path == "1")
	{
		//prints out the points to the console for quicker use
		thread setup_a10_animated_path_points(level.a10_dynamic);
	}
#/
	delaythread(.1, ::anim_set_rate_single, level.a10_dynamic, level.airstrike_anim_name , 1.3);
	delaythread(3, ::do_a10_badplace, badplace_points, 5, "axis");
	aud_send_msg("a10_airstrike_start", level.a10_dynamic);
	anim_ent anim_single_solo(level.a10_dynamic,level.airstrike_anim_name );
	level.a10_dynamic delete();
	anim_ent delete();
	
	level.player notify("a10_anim_complete");
}

do_a10_badplace(pts, duration, team)
{
	assert(isArray(pts));
	assert(isdefined(duration));
	assert(duration > 0);
	assert(isdefined(team));
	foreach( p in pts )
	{
		badplace_cylinder( "", duration, p, level.a10_badplace_radius, 64, team );
	}
}

//adds rumble when a10 flys over, this is not handled in the vehicle script because the a10 does not have speed during the anim.
airstrike_animated_rumble()
{
	classname = self.classname;
	rumblestruct = undefined;
	if ( IsDefined( self.vehicle_rumble_unique ) )
	{
		rumblestruct = self.vehicle_rumble_unique;
	}
	else if ( IsDefined( level.vehicle_rumble_override ) && IsDefined( level.vehicle_rumble_override[ classname ] ) )
	{
		rumblestruct = level.vehicle_rumble_override;
	}
	else if ( IsDefined( level.vehicle_rumble[ classname ] ) )
	{
		rumblestruct = level.vehicle_rumble[ classname ];
	}

	if ( !IsDefined( rumblestruct ) )
	{
		return;
	}

	height = rumblestruct.radius * 2;
	zoffset = -1 * rumblestruct.radius;
	assert(!isdefined(level.a10_rumble_trigger_check));
	
	areatrigger = Spawn( "trigger_radius", self.origin + ( 0, 0, zoffset ), 0, rumblestruct.radius, height );
	areatrigger EnableLinkTo();
	areatrigger LinkTo( self );
	self.rumbletrigger = areatrigger;
	self.rumbletrigger = areatrigger;
	self endon( "death" );
	level.a10_rumble_trigger_check = self.rumbletrigger;
	areatrigger.radius = self.rumble_radius;
	while ( 1 )
	{
		areatrigger waittill( "trigger" );

		self PlayRumbleLoopOnEntity( rumblestruct.rumble );

		while ( level.player IsTouching( areatrigger ) )
		{
			Earthquake( self.rumble_scale, self.rumble_duration, self.origin, self.rumble_radius ); // scale duration source radius
			wait( self.rumble_basetime + RandomFloat( self.rumble_randomaditionaltime ) );
		}
		self StopRumble( rumblestruct.rumble );
	}
}

setup_a10_animated_path_points(a10)
{
	path = [];
	wait(.25);
	while(isdefined(a10))
	{
		tag_origin = a10 getTagOrigin("tag_gun");
		path = array_add(path, tag_origin);
		wait(.25);
	}
	i=0;
	foreach(point in path){
		println("path["+i+"] = spawnstruct();");
		println("path["+i+"].origin = "+point+";");
		i++;
	}
}

airstrike_fire(a10)
{
	raw_angles = a10.angles;
	direction = flat_angle(raw_angles);
	impact_direction = anglesToForward(direction);
	dist = distance( level.a10_start_impact.origin, level.a10_end_impact.origin );
	
	a10 thread maps\berlin_util::a10_muzzle_flash_fx("a10_muzzle_vfx_stop");
	aud_send_msg("a10_airstrike_fire", a10);
	//muzzle_smoke = getfx("a10_muzzle_flash");
	//PlayFXOnTag(muzzle_smoke, a10, "tag_gun");

	thread a10_kill_watcher();
	
	impacts = [];
	impacts["water"] = getfx("a10_impact_water");
	impacts["metal"] = getfx("a10_impact");
	impacts["asphalt"] = getfx("a10_impact");
	impacts["default"] = getfx("a10_impact");

	fx_inc = 64;//spread between each impact
	current_dist = 0; 
	wait_time = 0.07;
	count = 0;
	
	level notify("a10_muzzle_vfx_stop");
	
	for (;;)
	{
		
		org = level.a10_start_impact.origin + impact_direction * current_dist;
		/*
		vec_random = (randomintrange(-10,10),randomintrange(-10,10),0);
		gun = a10 getTagOrigin( "tag_gun" );
		gun_angles = a10 gettagangles( "tag_gun" );
		gun_forward = anglesToForward( gun_angles );
		gun_offset = ( 0, 0, -100 );
		*/
		//magicBullet( "a10_30mm",gun+(gun_forward*400)+ gun_offset, org+vec_random, level.player );
		
		//every time we want to draw effects and damage we need to shoot a ray down
		if(count == 3){
			trace = BulletTrace( org + (0,0,512), org - (0,0,4096), false );
			surfaceType = trace["surfacetype"];
			
			impact_fx = impacts["default"];
			if(isdefined(impacts[surfaceType]))
				impact_fx = impacts[surfaceType];
				
			ground_org = trace["position"];
			radiusDamage( ground_org, 256, 50000, 40000, level.player, "MOD_EXPLOSIVE", level.player.lastweapon );
			playfx(impact_fx, ground_org); 	
			aud_send_msg("a10_airstrike_ground_impact", ground_org); 
			count = 0;	
		}
		wait( wait_time );
		current_dist += fx_inc;
		count++;
		if(dist<current_dist)
			break;	
	}
	level notify("a10_gound_impacts_stop");
	//stopFxOnTag(muzzle_smoke, a10, "tag_gun");
}

a10_kill_watcher()
{
	if(!IsDefined(level.a10_kills))
		level.a10_kills = 0;
	
	level notify("stop_a10_kill_watcher");
	level endon("stop_a10_kill_watcher");
	
	array_thread(GetAIArray("axis"), ::a10_kill_watcher_ai);
	
	wait 2;
	
	level notify("stop_a10_kill_watcher");
}

a10_kill_watcher_ai()
{
	level endon("stop_a10_kill_watcher");
	if(!IsAlive(self))
		return;
	
	self waittill( "death", attacker, type, weapon );
	
	if(IsDefined(type) && type == "MOD_EXPLOSIVE")
	{
		level.a10_kills++;
		if(level.a10_kills == 9)
		{
			level.player thread player_giveachievement_wrapper( "NEIN" );
		}
	}
}

calculate_target_pos()
{
	min_target_distance = 128;
	max_target_distance = 6000;
	
	direction = level.player getPlayerAngles();
	direction_vec = anglesToForward( direction );
	trace_start_pos = level.player getEye();
	trace_start_pos = trace_start_pos + ( direction_vec * min_target_distance );
	trace_end_pos = trace_start_pos + ( direction_vec * max_target_distance );
	
	trace = BulletTrace( trace_start_pos, trace_end_pos, true, level.player );
	aim_target = [];
	aim_target["normal"] = (0,0,1);
	aim_target["pos"] = trace_end_pos;
	aim_target[ "fraction" ] = trace[ "fraction" ]; //how far did the trace travel
	
	if(trace_end_pos[2] > 3500) //you will not hit anything valid over 3500 height
		aim_target[ "fraction" ] = 1;
		
	aim_target["entity"] = trace["entity"];	
	if(level.a10_friendly_ent_target_check) //disabled per request
	{
		//reject firing on friendly targets?
		
		if( isdefined(aim_target["entity"]) && isdefined(aim_target["entity"].team) && aim_target["entity"].team == "allies")
			aim_target[ "fraction" ] = 1; //failure
	}
	
	if ( trace[ "fraction" ] < 1 ) //if we hit something
	{
		aim_target["pos"] = trace["position"];
	}

	return aim_target;
}

airstrike_clean_up_target_points( hide_points )
{
	if( isdefined( level.aim_arrow ) )
		level.aim_arrow delete();
		
	if( isdefined( level.a10_second_point ) && level.a10_drop_vfx_for_destroy )
		level.a10_second_point.origin += ( 0,0,-10000 );
	
	delayThread( .05, ::destroy_second_point );
	
	if( isdefined( level.a10_start_point ) && level.a10_drop_vfx_for_destroy )
		level.a10_start_point.origin += ( 0,0,-10000 );
	
	delayThread( .05, ::destroy_start_point );
		
	destroy_directional_line( hide_points );
}

destroy_directional_line( force_hide )
{
	if( isDefined( level.direction_line ) )
	{
		foreach( line_vfx in level.direction_line )
		{
			thread clean_up_direction_line( line_vfx, force_hide );
		}
	}
}

airstrike_called_radio_dialogue()
{
/#
	//no annoying chatter in dev
	if(GetDVarInt("air_strike_dev", 0) == 1)
	{
		IPrintLn("airstrike inbound");	
		return;
	}
#/
	level.in_a10_vo = true;
	ran = RandomIntRange(0,5);
	switch(ran)
	{
		case 0:
			radio_dialogue("berlin_plt_targetaquired");
		break;
		//case 1:
		//	radio_dialogue("berlin_plt_goinghot");
		//break;
		case 1:
			radio_dialogue("berlin_plt_tallytarget");
		break;
		case 2:
			radio_dialogue("berlin_plt_contact");
		break;
		case 3:
			radio_dialogue("berlin_plt_tallyontarget");
		break;
	}
	level.in_a10_vo = false;
}

airstrike_ready_radio_dialogue()
{
/#
	//no annoying chatter in dev
	if(GetDVarInt("air_strike_dev", 0) == 1)
		return;
#/
	if( !isdefined( level.a10_suppress_ready_vo ) || !level.a10_suppress_ready_vo )
	{
		level.in_a10_vo = true;
		ran = RandomIntRange(0,4);
		switch(ran){
			case 0:
				radio_dialogue("berlin_plt_inposition2");
			break;
			case 1:
				radio_dialogue("berlin_plt_standingby3");
			break;
			case 2:
				radio_dialogue("berlin_plt_ready");
			break;
			case 3:
				radio_dialogue("berlin_plt_standingby4");
			break;
		}
		level.in_a10_vo = false;
	}
}

airstrike_not_available_dialogue()
{
/#
	//no annoying chatter in dev
	if(GetDVarInt("air_strike_dev", 0) == 1)
		return;
#/
	
	if( !isdefined( level.in_a10_vo ) || !level.in_a10_vo )
	{
		level.in_not_ready_dialogue = true;
		level.in_a10_vo = true;
		randomnum = randomIntRange(0,5);
		switch(randomnum){
			case 0:
				radio_dialogue("berlin_plt_notinposition2");
			break;
			case 1:
				radio_dialogue("berlin_plt_negative");
			break;
			case 2:
				radio_dialogue("berlin_plt_circleback");
			break;
			case 3:
				radio_dialogue("berlin_plt_notinposition");
			break;
			case 4:
				radio_dialogue("berlin_plt_holdfast");
			break;
		}
		level.in_a10_vo = false;
		level.in_not_ready_dialogue = false;
	}
}

airstrike_cant_get_there_radio_dialogue()
{
/#
	//no annoying chatter in dev
	if(GetDVarInt("air_strike_dev", 0) == 1)
	{
		IPrintLn("no path found");	
		return;
	}
#/
		
	if( !isdefined( level.in_cant_get_there_dialogue ) || !level.in_cant_get_there_dialogue )
	{
		level.in_cant_get_there_dialogue = true;
		level.in_a10_vo = true;	
		randomnum = randomIntRange(0,7);
		switch(randomnum)
		{
			case 0:
				radio_dialogue("berlin_plt_altattack");
			break;
			case 1:
				radio_dialogue("berlin_plt_maxeffects");
			break;
			case 2:
				radio_dialogue("berlin_plt_reciprocal");
			break;
			case 3:
				radio_dialogue("berlin_plt_unable");
			break;
			case 4:
				radio_dialogue("berlin_plt_newrunin");
			break;
			case 5:
				radio_dialogue("berlin_plt_badapproach");
			break;
			case 6:
				radio_dialogue("berlin_plt_direction");
			break;
		}
		level.in_a10_vo = false;
		level.in_cant_get_there_dialogue = false;
	}
}

airstike_hint_text_points()
{
	level.a10_hint_hud.alpha = 0;
	
	if ( !isdefined( level.a10_hint_hud_points) )
	{
		level.a10_hint_hud_points = maps\_hud_util::createFontString( "default", 2 );
		level.a10_hint_hud_points maps\_hud_util::setPoint( "TOP", undefined, 0, 80 );
		level.a10_hint_hud_points.label = &"BERLIN_DIRECT_A10_POINTS";
		level.a10_hint_hud_points.alpha = 1;
		level.a10_hint_hud_points.sort = 0.5;
	}else{
		level.a10_hint_hud_points.alpha = 1;
	}
}

airstrike_hud_off()
{
	if(isdefined(level.a10_hint_hud))
		level.a10_hint_hud.alpha = 0;
	if(isdefined(level.a10_hint_hud_points))
		level.a10_hint_hud_points.alpha = 0;
	if(isDefined(level.a10_hint_hud_activate))
		level.a10_hint_hud_activate.alpha = 0;		
}

turn_on_a10_hud_hint()
{
	if(isDefined(level.a10_hint_hud_activate) && level.a10_hint_hud.alpha != 1)
		level.a10_hint_hud_activate.alpha = 1;
}


monitor_weapon_switch()
{
	level.player endon("turn_off_airstrike");
	level.player endon("toggle_airstrike");
	level.player endon("airstrike_deactivated");
	level.player endon("airstrike_called");
	
	level.player NotifyOnPlayerCommand( "LISTEN_switch_weapons", "weapnext" );
	
	level.player waittill("LISTEN_switch_weapons");
	
	level.player notify("toggle_airstrike");
}

monitor_invalid_weapons()
{
	level.player endon("airstrike_called");
	level.player endon("turn_off_airstrike");
	level.player endon("toggle_airstrike");
	level.player endon("airstrike_deactivated");
		
	while(1)
	{
		if(level.player getcurrentweapon() != level.player getcurrentprimaryweapon())
		{
			level.player notify("toggle_airstrike");
			break;
		}	
		
		wait(0.05);
	}
}

remove_player_lock()
{
	level.player unlink();
	level.lock_player delete();
	level.lock_player = undefined;
}

airstrike_disable_player_abilities(controls)
{
	if(controls == "ads")
		self AllowADS(false);
	self allowFire( false );
	self allowMelee( false );
}

airstrike_enable_player_abilities(controls)
{
	self allowMelee( true );
	self allowFire( true );	
	if(controls == "ads")
		self AllowADS(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///END DYNAMIC A10 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

a10_interface_init()
{
	//  51°30'10.45"N
	//  0° 0'44.32"W

	level.a10_interface_fontscale = 1.25;
	PrecacheShader( "uav_vertical_meter" );
	PrecacheShader( "uav_horizontal_meter" );
	PrecacheShader( "uav_arrow_up" );
	PrecacheShader( "uav_arrow_left" );
	PrecacheShader( "uav_vehicle_target" );
	PrecacheShader( "veh_hud_friendly" );
	PrecacheShader( "veh_hud_target" );
	PreCacheShader( "nightvision_overlay_goggles" );
	PreCacheShader( "laser_designator_overlay_lr" );
	PreCacheShader( "laser_designator_overlay_hr" );
	PreCacheShader( "remotemissile_infantry_target" );

	SetSavedDvar( "thermalBlurFactorNoScope", 50 );

	flag_init( "a10_interface_enabled" );
}

a10_interface_thread()
{
	self endon( "death" );
	level endon("a10_view_disabled");

	rate = 0.2;
//	curr_latitude = " 1°30'10.50"N"
//  curr_longitude = "0° 0'54.17"W"

	curr_latitude = 51.50291666;
	curr_longitude = 0.015047222 / 60;

	while ( 1 )
	{
		if ( flag( "a10_interface_enabled" ))
		{
			if(isdefined(level.aim_arrow))
				target_loc = level.aim_arrow.origin;
			else
				target_loc = (0,0,0);
				
			// Target data
//			range = Distance( self.origin, target_loc );//2nd self.origin = targetent
//			range = to_meters( range );
//			self a10_set_target_hud_data( "brg", AngleClamp( int( ( self.angles[ 1 ] - 90 ) ) * -1 ) ); // 90 is north
//			self a10_set_target_hud_data( "rng_m", int( range ) );
//			self a10_set_target_hud_data( "rng_nm", round_to( meters_to_nm( range ), 1000 ) );
//			self a10_set_target_hud_data( "elv", int( to_feet( target_loc[ 2 ] ) ) );//self.origin = targetent

			// Camera Arrows
//			self a10_update_hud_arrows( rate );
		}

		wait( rate );
	}
}

a10_update_hud_arrows( rate )
{
	player_angles = self GetPlayerAngles();
	pitch = self.angles[ 0 ] - player_angles[ 0 ] * -1;
	yaw = AngleClamp180( self.angles[ 1 ] );// - player_angles[ 1 ] );

	self a10_set_hud_data( "arrow_left", int( pitch ) );
	self a10_set_hud_data( "arrow_up", int( yaw ) );

	// Left Arrow
	hud_vert_meter = self.a10_huds[ "vert_meter" ];
	hud_left_arrow = self.a10_huds[ "arrow_left" ];

	pitch = Clamp( pitch, hud_vert_meter.min_value, hud_vert_meter.max_value );
	percent = abs( pitch / hud_vert_meter.range );
	meter_pos = hud_vert_meter.meter_size * percent;
	offset = meter_pos - ( hud_vert_meter.meter_size * 0.5 );
	y = hud_vert_meter.y + offset;

	hud_left_arrow MoveOverTime( 0.2 );
	hud_left_arrow.y = y;
	hud_left_arrow.data_value MoveOverTime( rate );
	hud_left_arrow.data_value.y = y;

	// Up Arrow
	hud_horz_meter = self.a10_huds[ "horz_meter" ];
	hud_up_arrow = self.a10_huds[ "arrow_up" ];

	percent = yaw / hud_horz_meter.range;
	meter_pos = hud_horz_meter.meter_size * percent;
	x = hud_horz_meter.x + meter_pos;

	hud_up_arrow MoveOverTime( 0.2 );
	hud_up_arrow.x = x;
	hud_up_arrow.data_value MoveOverTime( rate );
	hud_up_arrow.data_value.x = x;
}

to_feet( val )
{
	if(val == 0)
		return 0;
		
	return val / 12;
}

to_meters( val )
{
	return val * 0.0254;
}

meters_to_nm( val )
{
	return val * 0.000539956803;
}

round_to( val, mult )
{
	val = int( val * mult ) / mult;
	return val;
}

a10_interface_enable_playerhud()
{
	SetSavedDvar( "ammoCounterHide", "0" );
	SetSavedDvar( "actionSlotsHide", "0" );
	SetSavedDvar( "hud_showStance", "0");
}

a10_interface_disable_playerhud()
{
	SetSavedDvar( "hud_showStance", "1");
	SetSavedDvar( "actionSlotsHide", "1" );
	SetSavedDvar( "ammoCounterHide", "1" );
}

a10_interface_enable_view()
{
	//key: delaythread delay plus the fade_in_time should equal waittime in a10_goggles_on
	delaythread( .90, maps\_introscreen::introscreen_generic_black_fade_in, .1, .1, .1 );
	self a10_goggles_on();
	self thread a10_fov_enable();
	a10_interface_disable_playerhud();
	self.a10_huds = [];
	
	goggles_overlay = "laser_designator_overlay_lr";
	if(	level.a10_goggles_overlay_hi )
	{
		SetHUDLighting( true );
		goggles_overlay = "laser_designator_overlay_hr";
	}
	
	self.a10_huds[ "static_goggles" ] 	= create_hud_static_overlay(goggles_overlay, 1, 1);
	self.a10_huds[ "static_grain" ] 	= create_hud_static_overlay("nightvision_overlay_goggles", 0, .2);

	flag_set( "a10_interface_enabled" );
	self thread a10_draw_targets();
	self thread a10_interface_thread();

}

a10_fov_enable()
{
	self endon( "death" );
	level endon("a10_view_disabled");
	
	a10_fov_ads_value = .75;
	a10_fov_value = .75;
	
	//lower is slower
	adsaim_pitch_value = .3;
	adsaim_yaw_value = .3;
	
 	a10aim_pitch_value = .5;
	a10aim_yaw_value = .5;
	
	first_time = true;	
	
	while(1)
	{		
			if( level.player ADSButtonPressed() && ( first_time == false ) )
			{
				setsaveddvar( "cg_playerFovScale0", a10_fov_ads_value );
				level.player enableslowaim( adsaim_pitch_value, adsaim_yaw_value ); 
				first_time = true;
			}
			else if( ( !level.player ADSButtonPressed() ) && ( first_time == true ) )
			{
				setsaveddvar( "cg_playerFovScale0", a10_fov_value );
				level.player enableslowaim( a10aim_pitch_value, a10aim_yaw_value ); 
				first_time = false;
			}
		wait( .05 );
	}	
}

a10_fov_disable()
{
	setsaveddvar( "cg_playerFovScale0", 1 );
	level.player disableslowaim();
}


create_hud_static_overlay(overlay, sortOrder, alphaValue)
{
	hud = NewHudElem();
	hud.x = 0;
	hud.y = 0;
	hud.sort = sortOrder;
	hud.horzAlign = "fullscreen";
	hud.vertAlign = "fullscreen";
	hud.alpha = alphaValue;
	hud SetShader( overlay, 640, 480 );

	return hud;
}

create_hud_horizontal_meter()
{
	hud = NewHudElem();
	hud.x = 320;
	hud.y = 80;
	hud.sort = 0;
	hud.alignX = "center";
	hud.alignY = "bottom";
	hud SetShader( "uav_horizontal_meter", 96, 16 );

	return hud;
}

create_hud_vertical_meter()
{
	hud = NewHudElem();
	hud.x = 40;
	hud.y = 240;
	hud.sort = 0;
	hud.alignX = "right";
	hud.alignY = "middle";
	hud SetShader( "uav_vertical_meter", 16, 96 );

	return hud;
}

create_hud_crosshair()
{
	hud = NewHudElem();
	hud.x = 320;
	hud.y = 240;
	hud.sort = 0;
	hud.alignX = "center";
	hud.alignY = "middle";
	hud SetShader( "uav_crosshair", 320, 240 );

	return hud;
}

a10_set_target_hud_data( index, value )
{
	self.a10_huds[ "lower_right" ][ index ].data_value SetValue( value );
}

a10_set_hud_data( index, value )
{
	self.a10_huds[ index ].data_value SetValue( value );
}

create_hud_upper_left()
{
	data = [];
	data[ "nar" ]  		= [ "NAR", "none" ];	//
	data[ "white" ]  	= [ "WHT", "none" ];	//
	data[ "rate" ] 		= [ "RATE", "none" ];	//
	data[ "angle" ] 	= [ "ANGLE", "none" ];	//
	data[ "numbers" ] 	= [ "NUM", "none" ];	//
	data[ "temp" ] 		= [ "TEMP", "none" ];	//

	return create_hud_section( data, 10, 80, "left" );
}

create_hud_upper_right()
{
	data = [];
	data[ "acft" ]  	= [ "ACFT", "none" ];	//
	data[ "long" ]  	= [ "N", "none" ];	//
	data[ "lat" ] 		= [ "W", "none" ];	//
	data[ "angle" ] 	= [ "HAT", "none" ];	//

	return create_hud_section( data, 510, 80, "left" );
}

create_hud_lower_right()
{
	data = [];
	data[ "long" ]  	= [ &"N", "none" ];	//
	data[ "lat" ] 		= [ &"W", "none" ];	//

	huds = create_hud_section( data, 500, 335, "left" );

	data = [];
	data[ "brg" ] 		= [ "BRG", "" ];			// Bearing
	data[ "rng_m" ]  	= [ "RNG", "" ];		// Range Meters
	data[ "rng_nm" ] 	= [ "RNG", "" ];	// Range Nautical Miles
	data[ "elv" ] 	 	= [ "ELV", "" ];		// Elevation Feet

	huds2 = create_hud_section( data, 510, 360, "right" );

	foreach ( idx, hud in huds2 )
	{
		huds[ idx ] = hud;
	}

	return huds;
}

create_hud_section( data, x, y, align_x )
{
	huds = [];

	spacing = 10 * level.a10_interface_fontscale;
	foreach ( i, item in data )
	{
		hud = NewHudElem();
		hud.x = x;
		hud.y = y;
		hud.alignX = align_x;
		hud.alignY = "middle";
		hud.color = (1,1,1);
		hud.fontscale = level.a10_interface_fontscale;
		hud SetText( item[ 0 ] );

		if ( IsDefined( item[ 1 ] ) )
		{
			if ( !string_is_valid( item[ 1 ], "none" ) )
			{
				hud create_hud_data_value( item[ 1 ] );
			}
		}
		else
		{
			hud create_hud_data_value();
		}

		huds[ i ] = hud;

		y += spacing;
	}

	return huds;
}

string_is_valid( str, test )
{
	if ( IsString( str ) )
	{
		if ( str == test )
		{
			return true;
		}
	}

	return false;
}

create_hud_data_value( suffix )
{
	x_add = 75;

	if ( IsDefined( suffix ) && !string_is_valid( suffix, "" ) )
	{
		data_value_suffix = NewHudElem();
		data_value_suffix.x = self.x + x_add;
		data_value_suffix.y = self.y;
		data_value_suffix.alignX = "right";
		data_value_suffix.alignY = "middle";
		data_value_suffix.fontscale = level.a10_interface_fontscale;
		data_value_suffix SetText( suffix );

		self.data_value_suffix = data_value_suffix;

		size = 1;
		if ( suffix == "UAV_NM" )
		{
			size = 2;
		}

		x_add -= 10 * size;	
	}

	data_value = NewHudElem();
	data_value.x = self.x + x_add;
	data_value.y = self.y;
	data_value.alignX = "right";
	data_value.alignY = "middle";
	data_value.fontscale = level.a10_interface_fontscale;
	data_value SetValue( 0 );

	self.data_value = data_value;
}

create_hud_arrow( dir )
{
	if ( dir == "up" )
	{
		shader = "uav_arrow_up";
		parent_hud = self.a10_huds[ "horz_meter" ];
		x = 320;
		y = parent_hud.y + 10;
		x_align = "center";
		y_align = "top";
	}
	else
	{
		shader = "uav_arrow_left";
		parent_hud = self.a10_huds[ "vert_meter" ];
		x = parent_hud.x + 10;
		y = 240;
		x_align = "left";
		y_align = "middle";
	}

	hud = NewHudElem();
	hud.x = x;
	hud.y = y;
	hud.alignX = x_align;
	hud.alignY = y_align;
	hud SetShader( shader, 16, 16 );
	hud create_hud_arrow_value( dir );

	return hud;	
}

create_hud_arrow_value( dir )
{
	if ( dir == "up" )
	{
		x = self.x;
		y = self.y + 16;
		x_align = "center";
		y_align = "top";
	}
	else
	{
		x = self.x + 16;
		y = self.y;
		x_align = "left";
		y_align = "middle";
	}

	data_value = NewHudElem();
	data_value.x = x;
	data_value.y = y;
	data_value.alignX = x_align;
	data_value.alignY = y_align;
	data_value SetValue( 0 );

	self.data_value = data_value;
}

a10_interface_disable_view()
{
	flag_clear( "a10_interface_enabled" );
	level notify("a10_view_disabled");
	self DisableSlowAim();
	
	if(self GetCurrentWeapon() == "a10_designator_ads")//make sure the player is using the weapon if we do the blink
	{
	thread maps\_introscreen::introscreen_generic_black_fade_in( .1, .1, .1 );
	wait( .2 );
	}
	
	a10_stop_draw_targets();
	a10_interface_enable_playerhud();

	if(IsDefined(self.a10_huds))
	{
		foreach ( hud in self.a10_huds )
		{
			if(IsDefined(hud))
			{
				if ( IsArray( hud ) )
				{
					foreach ( elem in hud )
					{
						a10_destroy_hud( elem );
					}
		
					hud = undefined;
				}
				else
				{
					a10_destroy_hud( hud );
				}
			}
		}
	}
	
	SetHUDLighting( false );
	self a10_fov_disable();
	self a10_goggles_off();
	self a10_interface_enable_weapons();
}

a10_destroy_hud( hud )
{
	if(!IsDefined(hud))
		return;
		
	if ( IsDefined( hud.data_value ) )
	{
		hud.data_value Destroy();
	}

	if ( IsDefined( hud.data_value_suffix ) )
	{
		hud.data_value_suffix Destroy();
	}

	hud Destroy();
}

a10_interface_enable_weapons()
{
	self EnableWeapons();
	self EnableOffhandWeapons();
	self FreezeControls( false );
}

a10_goggles_on()
{
	self.lastweapon = self GetCurrentWeapon();
	assert(isdefined( self.lastweapon ) );
	weapon_name = "a10_designator_ads";
	level.player SetActionSlot( 4, "weapon", weapon_name );
	level.player GiveWeapon( weapon_name );
	level.player switchToWeapon( weapon_name );
	level.player set_ignoreme( true );
	
	maps\_audio::aud_send_msg("goggles_on");
	
	self DisableOffhandWeapons();	
	
	wait( 1.2 );
}

a10_goggles_off()
{
	weapon_name = "a10_designator_ads";
		
	
	if(self GetCurrentWeapon() == weapon_name)
	{
		assert(isdefined( self.lastweapon ) );
		self SwitchToWeapon( self.lastweapon );
		level.player set_ignoreme( false );
		maps\_audio::aud_send_msg("goggles_off");
		wait(1);
	}
	
	//anim handled by putting away
	level.player TakeWeapon( weapon_name );	
}

a10_target_tracking( ent, diff_override, forward_offset )
{
	self endon( "death" );
	self notify( "stop_a10_target_tracking" );
	self endon( "stop_a10_target_tracking" );

	diff = 0.94;
	time = 0.1;

	if ( IsDefined( diff_override ) )
	{
		diff = diff_override;
	}

//	self.target_ent thread draw_tracking( ent );

	while ( 1 )
	{
		dest = ent.origin + ( 0, 0, 60 );

		if ( IsDefined( forward_offset ) )
		{
			forward = AnglesToForward( ent.angles );
			dest = ent.origin + ( forward * forward_offset );
		}

		origin = ( self.target_ent.origin * diff ) + ( dest * ( 1.0 - diff ) );

		self.target_ent MoveTo( origin, time );
		wait( time );
	}
}

draw_tracking( ent )
{
/#
	self endon( "death" );
	self endon( "stop_a10_target_tracking" );

	while ( 1 )
	{
		Line( ent.origin, self.origin );
		wait( 0.05 );
	}
#/
}

GetTargetId(ent)
{
	if(!isdefined(self.my_a10_target_id))
	{
		if(!isdefined(level.berlin_a10_target_id_upcount))
			level.berlin_a10_target_id_upcount = 0;
		self.my_a10_target_id = level.berlin_a10_target_id_upcount;
		level.berlin_a10_target_id_upcount++;
	}
	return self.my_a10_target_id;	
}

a10_add_target()
{
	assert(!isdefined( level.a10_targets ) || !isdefined( level.a10_targets[ GetTargetId(self) ] ));
	level.a10_targets[ GetTargetId(self) ] = self;
}

a10_remove_target_ondeath()
{
	self waittill( "death" );
	
	if(isdefined(self))
	{
		self a10_remove_target();
	}
}

a10_remove_target()
{
	a10_stop_draw_target();
	assert(isdefined( level.a10_targets[ GetTargetId(self) ] ));
	level.a10_targets[ GetTargetId(self) ] = undefined;
}

a10_stop_draw_target()
{
	if ( IsDefined( self.has_target_shader ) )
	{
		self.has_target_shader = undefined;
		Target_Remove( self );
	}
}

a10_stop_draw_targets()
{
	level notify( "stop_draw_a10_targets" );
	foreach ( target in level.a10_targets )
	{
		if ( !IsDefined( target ) )
		{
			continue;
		}

		target a10_stop_draw_target();
	}	
}

a10_draw_targets()
{
	level endon( "stop_draw_a10_targets" );

	targets_per_frame = 4;
	targets_drawn = 0;
	delay = 0.05;

	while ( 1 )
	{
		foreach ( target in level.a10_targets )
		{
			if ( !IsDefined( target ) )
			{
				continue;
			}

			target draw_target( level.player );
			targets_drawn++;
			if ( targets_drawn >= targets_per_frame )
			{
				targets_drawn = 0;
				wait( delay );
			}
		}

		wait( 0.05 );
	}
}

draw_target( player )
{
	if ( IsDefined( self.has_target_shader ) && self.has_target_shader )
	{
		return;
	}

	self.has_target_shader = true;

	Target_Set( self, ( 0, 0, 32 ) );

	if ( IsAI( self ) || self.code_classname == "script_model")
	{
		assert(isdefined(self.team));
		if ( self.team == "axis" )
		{
			Target_SetShader( self, "remotemissile_infantry_target" );
		}
		else
		{
			Target_SetShader( self, "veh_hud_friendly" );
		}
	}
	else if ( IsPlayer( self ) ) // Make sure you add the player to the level.remote_missile_targets before use
	{
		Target_SetShader( self, "hud_fofbox_self_sp" );
	}
	else if ( self.code_classname == "script_vehicle" )
	{
		if( self.script_team == "axis" )
		{
			Target_SetShader( self, "veh_hud_target" );
		}
		else
		{
			Target_SetShader( self, "veh_hud_friendly" );
		}
	}
	else
	{
		Target_SetShader( self, "veh_hud_target" );
	}

	Target_ShowToPlayer( self, player );
}

a10_clear_targets()
{
	a10_stop_draw_targets();

	foreach ( target in level.a10_targets )
	{
		if ( !IsDefined( target ) )
		{
			continue;
		}

		target a10_remove_target();
	}

	level.a10_targets = [];
}