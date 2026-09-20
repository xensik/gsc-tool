#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;
#include maps\_audio;

vo_wetsub_intro(delay)
{
	if (isdefined(delay))
	{
		wait delay;
	}
	
	flag_wait( "npcs_spawned" );
	
	//Grinch: In position.
	radio_dialogue( "nyharbor_rno_inposition" );
	//Sandman: SDV Team Four, this is Metal 0-1. Radio check in the blind, over.
	radio_dialogue( "nyharbor_lns_radiocheck" );
	//SEAL Leader: Roger 0-1, we have you five by five. Phase line Echo secure. We have execute authority.
	radio_dialogue( "nyharbor_sel_fivebyfive" );
	//Sandman: We're one minute out. Don't start the party without us, over.
	radio_dialogue( "nyharbor_lns_starttheparty" );
	//SEAL Leader: Copy that.
	radio_dialogue( "nyharbor_sel_copythat" );
	//Grinch: Just don't start the party without us.
	radio_dialogue( "nyharbor_rno_dontstart" );
	
	wait( 1 );
	
	//Sandman: Almost through.
	radio_dialogue( "nyharbor_lns_almostthrough" );
	
	flag_wait( "tunnel_linkup_dialogue" );
	
	//Grinch: Think anyone got out?
	radio_dialogue( "nyharbor_rno_gotout" );
	//Sandman: Nothing we can do for them now.
	radio_dialogue( "nyharbor_lns_forthem" );
	
	wait( 4 );
	
	//Sandman: Maintain 2,9,5 degrees. 300 meters to link up.
	radio_dialogue( "nyharbor_lns_linkup" );
	
	flag_wait( "tunnel_tracker_dialogue" );
	//SEAL Leader: Metal 0-1, got you on the tracker.
	radio_dialogue( "nyharbor_sel_ontracker" );
	//Sandman: Roger, approaching RV.
	radio_dialogue( "nyharbor_lns_approachingrv" );
	
	flag_wait( "up_ahead_vo" );
	//Sandman: Eyes open, SEAL team should be up ahead.
	radio_dialogue( "nyharbor_lns_upahead" );
	//Grinch: I see them.
	radio_dialogue( "nyharbor_rno_iseethem" );
	
	flag_wait( "leaving_tunnel" );
	wait( 2 );
	//SEAL leader: The sub's on the move. Intercept window is closing fast
	radio_dialogue( "nyharbor_sel_intercept" );
	//Sandman: Roger that, lead the way.
	radio_dialogue( "nyharbor_lns_leadtheway" );
	flag_set( "light_toggle_on_1" );
}

vo_sandman_grate( guy )
{
	//Sandman: Primary entry point is open, stay tight, easy to get separated down here.
	radio_dialogue( "nyharbor_lns_entrypoint" );
}

vo_mines( delay )
{
	level endon( "russian_sub_event" );
	
	if( isDefined( delay ) )
	{
		wait delay;
	}

	//SEAL leader: Watch your sonar. Russians are laying mines.
	radio_dialogue( "nyharbor_sel_watchsonar" );
	
	wait( 2 );
	//Sandman: Frost, eyes on your sonar.
	radio_dialogue( "nyharbor_lns_eyesonsonar" );
	
	flag_wait( "mine_2" );
	//Grinch: Mine!
	radio_dialogue( "nyharbor_rno_mine" );
	//Sandman: Keep it steady
	radio_dialogue( "nyharbor_lns_keepitsteady" );
	
	flag_wait( "mine_3" );
	//Sandman: Right, right!
	radio_dialogue( "nyharbor_lns_right" );
	
	flag_wait( "mine_5" );
	//Sandman: Got another mine!
	radio_dialogue( "nyharbor_lns_anothermine" );
	
	wait( 1 );
	//Sandman: Clear.
	radio_dialogue( "nyharbor_lns_clear" );
}
	
vo_wetsub_russian_sub(delay)
{
	if (isdefined(delay))
		wait delay;	
	
	//Sandman: Power down, here we go.
	radio_dialogue( "nyharbor_lns_powerdown" );
	wait( 3 );
	//SEAL leader: Target approching. Oscar-2, eight o'clock.
	radio_dialogue( "nyharbor_sel_targetapproaching" );
	
	wait( 8 );
	//SEAL leader: Steady.
	radio_dialogue( "nyharbor_sel_steady" );
	
	wait( 8 );
	//Sandman: Wait til she passes.
	radio_dialogue( "nyharbor_lns_waittilpasses" );
	
	flag_wait( "sdvs_chase_sub" );
	//Sandman: Okay, go!
	radio_dialogue( "nyharbor_lns_okaygo" );
	thread mine_nag_lines();
	wait( 3 );
	//Sandman: Get in position.
	radio_dialogue( "nyharbor_lns_getinposition" );
	//SEAL Leader: Planting.
	radio_dialogue( "nyharbor_sel_planting" );
	wait( 1.5 );
	//Grinch: Planting.
	radio_dialogue( "nyharbor_rno_planting" );
	
	if( !flag( "vo_stop_mine_nag" ) )
	{
		//Sandman: Frost, plant the jaywick on the sub.
		radio_dialogue( "nyharbor_lns_plantjaywick" );
	}
	
	flag_wait( "submine_planted" );
	wait( 3 );
	//Sandman: Mines armed. Clear out.
	radio_dialogue( "nyharbor_lns_minesarmed" );
	//SEAL Leader: Good job. We'll prep the exfil.
	radio_dialogue( "nyharbor_sel_goodjob" );
	//Sandman: Going explosive. Hit it.
	radio_dialogue( "nyharbor_lns_goingexplosive" );
	
	wait( 1 );
	//Sandman: Overlord, this is Metal Zero One. Sub is surfacing. Commencing assault.
	radio_dialogue( "nyharbor_lns_commencingassault" );
	//Overlord: Roger, Zero-One, continue to Primary Objective. We need control of the sub's missiles.
	radio_dialogue( "nyharbor_hqr_primaryobjective" );
	wait( 2.5 );
	//Sandman: Hold position
	radio_dialogue( "nyharbor_lns_holdposition" );
}

sdv_follow_nag_lines()
{
	level endon("stop_sdv_follow_nag");
	lines = [];
	lines[ lines.size ] = "nyharbor_lns_hurryup";
	lines[ lines.size ] = "nyharbor_lns_frostmove";
	
	//assertex ( ( isdefined ( character ) ) && ( isai ( character ) ), "Character is not properly defined" );
	//assertex ( ( isdefined ( lines ) && isarray ( lines ) ), "Lines is undefined, or is not an array" );
	last_line = undefined;
	delay_min = 10;
	delay_max = 20;
		
	while ( true )
	{
		flag_wait("vo_sdv_follow_nag");
		rand_delay = RandomfloatRange( delay_min, delay_max );
		rand_line = random( lines );
		
		if ( isdefined( last_line ) && rand_line == last_line )
			continue;
		else
		{
			last_line = rand_line;
			radio_dialogue( rand_line );		
			
			wait rand_delay;
		}
		
	}
}

mine_nag_lines()
{
	lines = [];
	lines[ lines.size ] = "nyharbor_lns_plantyourmine";
	lines[ lines.size ] = "nyharbor_lns_frostgetinposition";
	lines[ lines.size ] = "nyharbor_lns_hurryup";
	lines[ lines.size ] = "nyharbor_lns_frostmove";
	
	//assertex ( ( isdefined ( character ) ) && ( isai ( character ) ), "Character is not properly defined" );
	//assertex ( ( isdefined ( lines ) && isarray ( lines ) ), "Lines is undefined, or is not an array" );
	last_line = undefined;
	delay_min = 10;
	delay_max = 20;
		
	while ( !flag( "vo_stop_mine_nag" ) )
	{
		rand_delay = RandomfloatRange( delay_min, delay_max );
		rand_line = random( lines );
		
		if ( isdefined( last_line ) && rand_line == last_line )
			continue;
		else
		{
			last_line = rand_line;
			wait rand_delay;
			
			if ( !flag( "vo_stop_mine_nag" ) )
				radio_dialogue( rand_line );		
			
		}
		
	}
}

vo_sub_exterior()
{
	flag_wait( "vo_hatch_open" );
	level.sandman dialogue_queue( "nyharbor_lns_hatchopening" ); //Sandman: Hatch opening
	level.sandman dialogue_queue ( "nyharbor_lns_comingout" );	//Sandman: Contact, coming out of the hatch!
	flag_wait("vo_frag_out");
	level.sandman dialogue_queue ( "nyharbor_lns_fragout" );	//Sandman: Frag out!	
	flag_wait("vo_frag_out_clear");
	level.sandman dialogue_queue ( "nyharbor_lns_clearheaddown" );	//Sandman: Clear. Head down.
	flag_set( "sandman_talking_on_deck" );
}

vo_sub_exterior_allies()
{
	level endon( "hatch_player_using_ladder" );
	flag_wait( "sub_exterior_guys_dead" ); //all guys up top are dead, from radiant
	flag_wait( "sandman_talking_on_deck" );
	wait( 1 );
	//Truck: Deck secured. We'll hold topside.
	level.sub_truck dialogue_queue( "nyharbor_trk_decksecured" );
	
	wait( 3.0 );
	
	if( !flag( "hatch_player_using_ladder" ) )
	{
		//Grinch: Deck secured!  Head down!
		level.sub_grinch dialogue_queue( "nyharbor_rno_headdown" );
	}
	
	wait( 5 );
	
	if( !flag( "hatch_player_using_ladder" ) )
	{
		//Truck: Get down the ladder!  We still got a job to do!
		level.sub_truck dialogue_queue( "nyharbor_trk_jobtodo" );
	}
	
	
	wait( 5 );
	
	if( !flag( "hatch_player_using_ladder" ) )
	{
		//Grinch: Sandman needs you down there, Frost!
		level.sub_grinch dialogue_queue( "nyharbor_rno_downthere" );
	}
	
	flag_wait( "sub_exterior_hind_1_fire" );
	//Truck: Incoming hind!!!  
	level.sub_truck dialogue_queue( "nyharbor_trk_incominghind" );
}

vo_sub_interior_engine_room()
{
	flag_wait( "vo_sub_interior_1" );
	level.sandman dialogue_queue ( "nyharbor_lns_unknowns" );  //Sandman: Alright Frost, sweep and clear. All unknowns are hostile.
	flag_wait("vo_go_downstairs");
	level.sandman dialogue_queue ( "nyharbor_lns_rvdownstairs" );	//Sandman: Rendezvous downstairs.	
}

sandman_exit_nag_vo()
{
	flag_wait( "barracks_exit_nag_vo" );
	
	lines = [];
	lines[0] = "nyharbor_snd_downstairs";
	lines[1] = "nyharbor_lns_rvdownstairs";
	
	counter = 0;
	while( !flag( "sandman_paired_kill" ) && !flag( "barracks_move_sandman" ) )
	{
		level.sandman dialogue_queue( lines[ counter ] );
		if( counter == 0 )
		{
			counter = 1;
		}
		else
		{
			counter = 0;
		}
		wait( 6 );
	}
}

vo_sub_interior_barracks( )
{
	flag_wait( "barracks_vo" );
  	//level.sandman dialogue_queue ( "nyharbor_lns_headingdownstairs" );	//Sandman: Heading downstairs.		
}

vo_sub_interior_reactor()
{
	flag_wait( "sandman_paired_kill_complete" );
	level.sandman dialogue_queue ( "nyharbor_lns_stairsclear" );
	level.sandman dialogue_queue ( "nyharbor_lns_takeleft" );
	
	flag_wait( "reactor_room_announcement" );
	thread sandman_translate_scuttle();
	radio_dialogue( "nyharbor_rpa_evacuate" );
}

sandman_translate_scuttle()
{
	wait( 2.5 );
	//Sandman: They're going to scuttle the sub! We gotta move, now!
	level.sandman dialogue_queue ( "nyharbor_lns_scuttle" );
	//Sandman: Frost, take point.
	level.sandman dialogue_queue( "nyharbor_lns_takepoint" );
}

vo_sub_interior_missile_room_1()
{
	flag_wait( "vo_to_bridge" );
	//Sandman: We have to get to the bridge!
	level.sandman dialogue_queue( "nyharbor_lns_tothebridge2" );
}

vo_sub_interior_missile_room_2( )
{
	flag_wait( "vo_wait_at_door" );
	wait(1); //adding wait because line was playing at the same time as a loud explosion/screen-shake and it was hard to hear. 
	if( !flag( "ready_for_breach" ) )
	{
		//Sandman: Hold position at the door.
		level.sandman dialogue_queue( "nyharbor_lns_atthedoor2" );
		wait 0.05;
	}
	flag_wait( "vo_breach" );
	level.sandman dialogue_queue ( "nyharbor_lns_kickercharge"  );	//Sandman: In position. Put a kicker charge on the door.	
	level.sandman SetLookAtEntity();
	flag_wait( "breach_guys_dead" );
	wait( 2 );
	//Sandman: Area secure.
	level.sandman dialogue_queue( "nyharbor_lns_areasecure" );
}

vo_sub_sandman_got_key( guy )
{
	//Sandman: Alright, I got the launch keys.
	level.sandman dialogue_queue( "nyharbor_lns_launchkeys" );
}

vo_sub_sandman_captain_flip_wface()
{
	level waittill("start_missilekey");
	level.sandman dialogue_queue ( "nyharbor_lns_missilekey" );					//Sandman: I have the missile key and I'm accessing the launch codes now.
	level notify("gridcoords");
	level.sandman dialogue_queue ( "nyharbor_lns_launchin30" );					//Sandman: Coordinates confirmed! Launch in 30 seconds!	+
	//Sandman: Frost, get on the console!
	level.sandman dialogue_queue( "nyharbor_lns_console" );
	flag_set( "sub_control_room_player_to_controls" );
	delaythread( 6, ::sub_interior_bridge_console_nag );
	
}

vo_sub_sandman_captain_flip(guy)
{
	thread vo_sub_sandman_captain_flip_wface();
	//flag_set( "sub_control_room_sandman_at_control_panel" );
	flag_set("vo_sandman_checkpointneptune");
	level.sandman dialogue_queue ( "nyharbor_lns_checkpointneptune" );	//Sandman: Overlord, this is Metal Zero-One. I send checkpoint "Neptune," over.		
	radio_dialogue( "nyharbor_hqr_copyneptune" );	
//	level.sandman dialogue_queue ( "nyharbor_lns_missilekey" );					//Sandman: I have the missile key and I'm accessing the launch codes now.	
	level waittill("gridcoords");
	radio_dialogue( "nyharbor_hqr_coordinates" );											//Overlord: Grid coordinates follow: Tango Whiskey Zero Five Six Six Two Eight.		
//	level.sandman dialogue_queue ( "nyharbor_lns_launchin30" );					//Sandman: Coordinates confirmed! Launch in 30 seconds!	+
	//Sandman: Frost, get on the console!
//	level.sandman dialogue_queue( "nyharbor_lns_console" );
//	flag_set( "sub_control_room_player_to_controls" );
//	delaythread( 6, ::sub_interior_bridge_console_nag );
}

vo_sandman_count_down(guy)
{
	level.sandman dialogue_queue ( "nyharbor_lns_321turn" );	//Sandman: 3, 2, 1, Turn!
	level.sandman dialogue_queue ( "nyharbor_lns_missiles" );	//Sandman: Overlord, missiles armed and launching!
	flag_set("vo_bridge_is_done");
	radio_dialogue( "nyharbor_hqr_teaminposition" );										//Overlord: Roger. SEAL team is in position for exfil.	
	level.sandman dialogue_queue ( "nyharbor_lns_gogo" );								//Sandman: Go! Go!	
	aud_send_msg("mus_to_the_zodiac");
}

vo_sub_interior_bridge()
{
	flag_wait("vo_sub_interior_6");
													//Overlord: Roger Zero-One, copy "Neptune."
	
	//flag_wait( "sub_control_room_sandman_at_control_panel" );					
}



sub_interior_bridge_console_nag()
{
	wait( 1 );
	lines = [];
	//Sandman: Frost, get on the console!
	lines[ 0 ] = "nyharbor_lns_overhere"; 
	//Sandman: Frost, over here!
	lines[ 1 ] = "nyharbor_lns_console";
	
	counter = 0;
	while( !flag( "player_at_controls" ) )
	{
		level.sandman dialogue_queue( lines[ counter ] );
		if( counter == 0 )
		{
			counter = 1;
		}
		else
		{
			counter = 0;
		}
		wait( 6 );
	}
}

live_dialog_queue( msg )
{
	if (IsAlive(self))
		self dialogue_queue( msg );
	else
		wait 100;	// don't continue if he's dead
}
vo_zodiac_ride( delay )
{
	if( isDefined( delay ) )
	{
		wait delay;
	}
	
	flag_wait ( "sub_exit_player_going_out_hatch" );
	wait 3;
	
	level.sandman live_dialog_queue( "nyharbor_lns_letsroll" );
	radio_dialogue ( "nyharbor_rno_amentothat" );
	
	flag_wait( "player_on_boat" );
	
	//Sandman: Frost, punch it!
	level.sandman live_dialog_queue( "nyharbor_lns_punchit" );
	
	wait( 1 );
	
	//Sandman: Missile's launching!
	level.sandman live_dialog_queue( "nyharbor_lns_missileslaunching" );
	
	flag_wait( "zubrs" );
	//Sandman: Keep up with that zodiac!
	level.sandman live_dialog_queue( "nyharbor_lns_keepup" );
	
	flag_wait( "spawn_hind01" );
	//Sandman: Gun it!
	
	wait 4;
	
	level.sandman live_dialog_queue( "nyharbor_lns_gunit" );
	
	flag_wait( "vo_missiles_incoming" );
	//Sandman: Missile's coming in!
	level.sandman live_dialog_queue( "nyharbor_lns_missilescoming" );
	
	wait( 2 );
	
	//Sandman: Keep on going, Frost!
	level.sandman live_dialog_queue( "nyharbor_lns_keepongoing" );
	
	flag_wait( "start_boat_crash" );
	wait( 1 );
	//Sandman: Look out!
	level.sandman live_dialog_queue( "nyharbor_lns_lookout" );
	
	wait ( 0.5 );
	//Sandman: Shoot the mines!
	level.sandman live_dialog_queue( "nyharbor_lns_shootmines" );
	
	flag_wait( "spawn_chinook" );
	wait( 2 );
	//Sandman: There's our bird!
	level.sandman live_dialog_queue( "nyharbor_lns_theresourbird" );
	
	flag_wait( "switch_chinook" );
	
	wait 3;
	//Sandman: There she is! Go! Go!
	level.sandman live_dialog_queue( "nyharbor_lns_theresheis" );
	wait 0;
	//Chinook pilot: Metal 0-1, we are feet wet!
	radio_dialogue( "nyharbor_plt_feetwet" );
	
	flag_wait( "finale_dialogue" );
	wait 3;
	//Sandman: Overlord, mission complete. All Eagles accounted for.
	level.sandman live_dialog_queue( "nyharbor_lns_missioncomplete" );
	//Overlord: Roger Metal 0-1, missile strikes confirmed on multiple Russian hard targets in your AO. All primary threats neutralized. Good work, team, that's one for the books.
	radio_dialogue( "nyharbor_hqr_oneforbooks" );
	//Sandman: Easy day, Overlord. Sandman out.
	level.sandman live_dialog_queue( "nyharbor_lns_easyday" );
}
