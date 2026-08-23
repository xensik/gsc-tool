#include common_scripts\utility;
#include maps\_utility;
#include maps\_audio;

main()
{
	prepare_dialogue();
}

prepare_dialogue()
{
	Price = "price";
	Nikolai = "nikolai";
	Doctor = "doctor";
	Soap = "soap";
	
	//Price: Get him inside!
	level.scr_sound[Price][ "intro_pri_inside" ]		= "intro_pri_inside";
	//Price: Out of the bloody way! Get a doctor!
	level.scr_sound[Price][ "intro_pri_getdoctor" ]		= "intro_pri_getdoctor";
	//Price: He needs help, now!
	level.scr_sound[Price][ "intro_pri_needshelp" ]		= "intro_pri_needshelp";
	//Nikolai: How many? Are you sure?
	level.scr_sound[Nikolai][ "intro_nik_howmany" ]		= "intro_nik_howmany";
	//Nikolai: Russian choppers approaching!
	level.scr_sound[Nikolai][ "intro_nik_choppers" ]		= "intro_nik_choppers";
	//Price: Makarov. He's tying up loose ends.
	level.scr_sound[Price][ "intro_pri_looseends" ]		= "intro_pri_looseends";
	//Nikolai: The safe house is up ahead!
	level.scr_sound[Nikolai][ "intro_opening_shot02_nikolai_face" ][0]		= "intro_nik_safehouse";
	//Price: Keep moving!
	level.scr_sound[Price][ "intro_opening_shot02_price_face" ][0]		= "intro_pri_keepmoving";
	//Nikolai: Keep pressure on that wound!
	level.scr_sound[Price][ "intro_opening_shot04_price_face" ][0]		= "intro_nik_keeppressure";
	//Nikolai: I'm trying!
	level.scr_sound[Nikolai][ "intro_opening_shot04_face" ][ 0 ]		= "intro_nik_imtrying";
	//Nikolai: Hang in there, my friend.
	level.scr_sound[Nikolai][ "intro_opening_shot04_face" ][ 1 ]		= "intro_nik_hanginthere";
	//Nikolai: Charging paddles!
	level.scr_sound[Nikolai][ "intro_nik_charging" ]		= "intro_nik_charging";
	//Nikolai: Three, two, one, CLEAR!
	level.scr_sound[Nikolai][ "intro_nik_threetwoone" ]		= "intro_nik_threetwoone";
	//Nikolai: We're losing him!  Charging - three, two, one.  Clear!
	level.scr_sound[Nikolai][ "intro_nik_321clear" ]		= "intro_nik_321clear";

	
	//---- START INDIA ----//


	//Loyalist 1: Russian attack choppers coming over the ridge!
	level.scr_radio[ "intro_loy1_attackchoppers" ]		= "intro_loy1_attackchoppers";
	//Loyalist 2: How many of them?
	level.scr_radio[ "intro_loy2_howmany" ]		= "intro_loy2_howmany";
	//Loyalist 1: 3 Havocs and 4, no, 5 MI-17s. Commandos fast roping down!
	level.scr_radio[ "intro_loy1_fastroping" ]		= "intro_loy1_fastroping";
	//Loyalist 2: Get a fire team on the roof!
	level.scr_radio[ "intro_loy2_fireteam" ]		= "intro_loy2_fireteam";
	//Nikolai: Yuri!
	level.scr_sound[Soap][ "intro_nik_yuri" ]		= "intro_nik_yuri";//playing this line on soap to stop collisions with the facial animation on nikolai
	//Price: We need to get Soap to the chopper!
	level.scr_sound[Price][ "intro_pri_getsoap" ]		= "intro_pri_getsoap";
	//Soap: *cough cough*
	level.scr_sound[Soap][ "" ]		= "";
	//Nikolai: Yuri, over here!
	level.scr_sound[Nikolai][ "intro_opening_shot07_face" ][ 0 ]		= "intro_nik_yurioverhere";
	//Nikolai: What's is that?!
	level.scr_sound[Nikolai][ "intro_opening_shot07_face" ][ 1 ]		= "intro_nik_whatisthat";
	//Price: Is everyone alright?
	level.scr_sound[Price][ "intro_pri_iseveryone" ]		= "intro_pri_iseveryone";
	//Nikolai: Da..
	level.scr_sound[Nikolai][ "intro_opening_shot08_face" ][ 0 ]		= "intro_nik_da";
	//Nikolai: Do whatever this man says.
	level.scr_sound[Nikolai][ "intro_opening_shot08_face" ][ 1 ]		= "intro_nik_thismansays";
	//Loyalist 1: I need shooters on the rooftops!
	level.scr_radio[ "intro_loy1_ineedshooters" ]		= "intro_loy1_ineedshooters";
	//Loyalist 2: More choppers coming from the west!
	level.scr_radio[ "intro_loy2_morechoppers" ]		= "intro_loy2_morechoppers";
	//Loyalist 1: We're running out of ammo!
	level.scr_radio[ "intro_loy1_runningout" ]		= "intro_loy1_runningout";
	//Loyalist 1: Get the civilians out of the streets!
	level.scr_radio[ "intro_loy1_getcivilians" ]		= "intro_loy1_getcivilians";
	//Price: Yuri, take a position on the balcony!
	level.scr_sound[Price][ "intro_pri_balcony" ]		= "intro_pri_balcony";
	//Price: We need to hold them off until we can move Soap!
	level.scr_sound[Price][ "intro_pri_holdthemoff" ]		= "intro_pri_holdthemoff";
	//Price: Keep your eyes on the courtyard.
	level.scr_sound[Price][ "intro_pri_eyesoncourtyard" ]		= "intro_pri_eyesoncourtyard";
	//Price: They've breached the courtyard! Take them down!
	level.scr_sound[Price][ "intro_pri_theybreached" ]		= "intro_pri_theybreached";
	//Nikolai: The doctor's down!
	level.scr_sound[Nikolai][ "intro_nik_doctorsdown" ]		= "intro_nik_doctorsdown";
	//Nikolai: Yuri, we need your help!
	level.scr_sound[Nikolai][ "intro_nik_needyourhelp" ]		= "intro_nik_needyourhelp";
	//Nikolai: Yuri, get over here!
	level.scr_sound[Nikolai][ "intro_nik_getoverhere" ]		= "intro_nik_getoverhere";
	//Nikolai: Give him the shot!
	level.scr_sound[Nikolai][ "intro_nik_theshot" ]		= "intro_nik_theshot";
	//Price: They're on the roof. We've got to get Soap to the chopper!
	level.scr_sound[Price][ "escort_help_soap_breach_price_face" ][0]		= "intro_pri_soaptochopper";
	//Nikolai: I've got him!
	level.scr_sound[Nikolai][ "intro_nik_ivegothim" ]		= "intro_nik_ivegothim";
	//Price: Yuri, you're with me!
	level.scr_sound[Price][ "escort_help_soap_breach_price_face" ][1]		= "intro_pri_yourewithme";
	//Price: Yuri, over here!
	level.scr_sound[Price][ "intro_pri_yurioverhere" ]		= "intro_pri_yurioverhere";
	//Price: Down the stairs, move!
	level.scr_sound[Price][ "intro_pri_downthestairs" ]		= "intro_pri_downthestairs";
	//Price: Yuri, on me!
	level.scr_sound[Price][ "intro_pri_yurionme" ]		= "intro_pri_yurionme";
	//Price: We've got to get through the courtyard!
	level.scr_sound[Price][ "intro_pri_throughcourtyard" ]		= "intro_pri_throughcourtyard";
	//Loyalist_1: We're pinned down in the street! We need reinforcements!
	level.scr_radio[ "intro_loy1_pinneddown" ]		= "intro_loy1_pinneddown";
	//Price: Nikolai, move up!
	//level.scr_sound[Price][ "price_to_nikolai_face" ][ 0 ]		= "intro_pri_moveup";
	//Price: Russian drone overhead!
	level.scr_sound[Price][ "price_to_nikolai_face" ][ 0 ] 		= "intro_pri_overhead";
	//Price: We're outnumbered and outgunned.  We need some heavier firepower.
	level.scr_sound[Price][ "price_to_nikolai_face" ][ 1 ]		= "intro_pri_firepower";
	//Nikolai: There's a weapon cache at the edge of town! We have a UGV stored there.
	level.scr_radio[ "intro_nik_weaponscache" ]		= "intro_nik_weaponscache";
	//Price: Then that's where we're heading. Let's move!
	level.scr_sound[Price][ "price_to_nikolai_face" ][ 2 ] 		= "intro_pri_letsmove";
	//Price: Hold fire! Civilians!
	level.scr_sound[Price][ "price_to_nikolai_face" ][ 3 ]		= "intro_pri_civilians";
	//Price: Nikolai, wait here with Soap! We'll clear a path!
	level.scr_sound[Price][ "intro_pri_clearapath" ]		= "intro_pri_clearapath";
	//Nikolai: Roger!
	level.scr_radio[ "intro_nik_roger" ]		= "intro_nik_roger";
	//Price: Watch the balconies!
	level.scr_sound[Price][ "intro_pri_watchbalconies" ]		= "intro_pri_watchbalconies";
	//Price: Doorway, right side!
	level.scr_sound[Price][ "intro_pri_doorwayright" ]		= "intro_pri_doorwayright";
	//Price: Nikolai, hang back! Protect Soap!
	level.scr_sound[Price][ "intro_pri_protectsoap" ]		= "intro_pri_protectsoap";
	//Loyalist 2: The courtyard's clear!
	level.scr_radio[ "intro_loy2_courtyardsclear" ]		= "intro_loy2_courtyardsclear";
	//Price: Keep moving down the street!
	level.scr_sound[Price][ "intro_pri_downthestreet" ]		= "intro_pri_downthestreet";
	//Price: We've got to get Soap out of here!!
	level.scr_sound[Price][ "intro_pri_getsoapout" ]		= "intro_pri_getsoapout";
	//Price: Machine gunner on the balcony! Take him out!
	level.scr_sound[Price][ "intro_pri_machinegunner" ]		= "intro_pri_machinegunner";
	//Price: Yuri, over here!
	level.scr_sound[Price][ "intro_pri_yurioverhere2" ]		= "intro_pri_yurioverhere2";
	//Price: The chopper's this way!
	level.scr_sound[Price][ "intro_pri_chopperthisway" ]		= "intro_pri_chopperthisway";
	//Price: Look out!
	level.scr_sound[Price][ "intro_pri_lookout" ]		= "intro_pri_lookout";
	//Price: The drone's doing another pass!
	level.scr_sound[Price][ "intro_pri_dronepass" ]		= "intro_pri_dronepass";
	//Nikolai: The weapons are in the building directly ahead!
	level.scr_sound[Nikolai][ "intro_nik_directlyahead" ]		= "intro_nik_directlyahead";
	//Price: There's too many of them between us and the chopper.
	level.scr_sound[Price][ "intro_pri_toomanyofthem" ]		= "intro_pri_toomanyofthem";
	//Price: Nikolai, we need that UGV now!
	level.scr_sound[Price][ "intro_pri_needthatugv" ]		= "intro_pri_needthatugv";
	//Nikolai: You're almost there! Go through the building!
	level.scr_sound[Nikolai][ "intro_nik_gothrough" ]		= "intro_nik_gothrough";
	//Price: Yuri, this way!
	level.scr_sound[Price][ "intro_pri_yurithisway" ]		= "intro_pri_yurithisway";
	//Loyalist 2: Breaching!
	level.scr_radio[ "intro_loy2_breaching" ]		= "intro_loy2_breaching";
	//Price: Yuri, the UGV is this way.	
	level.scr_sound[Price][ "intro_pri_ugvthisway" ]		= "intro_pri_ugvthisway";
	//Price: Yuri, over here!
	level.scr_sound[Price][ "intro_pri_overhere" ]		= "intro_pri_overhere";
	//Price: Hold up. This is it.
	level.scr_sound[Price][ "intro_pri_holdup" ]		= "intro_pri_holdup";
	//Price: Get inside!
	level.scr_sound[Price][ "intro_pri_getinside" ]		= "intro_pri_getinside";
	//Price: Hold up. Let them pass.
	level.scr_sound[Price][ "intro_pri_letthempass" ]		= "intro_pri_letthempass";
	//Nikolai: The UGV is in a shipping crate, directly below you.
	level.scr_sound[Nikolai][ "intro_nik_shippingcrate" ]		= "intro_nik_shippingcrate";
	//Price: I see it.
	level.scr_sound[Price][ "intro_pri_iseeit" ]		= "intro_pri_iseeit";
	//Price: Controls are going to be in Russian. You're up, Yuri.
	level.scr_sound[Price][ "intro_pri_controlsrussian" ]		= "intro_pri_controlsrussian";
	//Price: Nikolai, what's Soap's condition?
	level.scr_sound[Price][ "intro_pri_soapscondition" ]		= "intro_pri_soapscondition";
	//Nikolai: Ochen ploho...We've got to get him out of here!
	level.scr_sound[Nikolai][ "intro_nik_gethimout" ]		= "intro_nik_gethimout";
	//Price: Yuri, clear a path to the chopper. We'll be right behind you!
	level.scr_sound[Price][ "intro_pri_wellbebehind" ]		= "intro_pri_wellbebehind";
	//Price: Unmanned ground vehicle. 2 centimeter armor plating, mounted .50 cal and grenade launcher.
	level.scr_sound[Price][ "intro_weapon_cache_pullout_face" ][ 0 ]		= "intro_pri_ugv";
	//Price: Clear the path!
	level.scr_radio[ "intro_pri_clearthepath" ]		= "intro_pri_clearthepath";
	//Price: Keep firing!
	level.scr_radio[ "intro_pri_keepfiring" ]		= "intro_pri_keepfiring";
	//Price: Keep pushing to the chopper!
	level.scr_radio[ "intro_pri_keeppushing" ]		= "intro_pri_keeppushing";
	//Price: Yuri, grab the controls!
	level.scr_sound[Price][ "intro_pri_grabcontrols" ]		= "intro_pri_grabcontrols";
	//Price: We need to clear a path to the chopper. Target anything that moves.
	level.scr_radio[ "intro_pri_targetanything" ]		= "intro_pri_targetanything";
	//Price: They're using smoke! Yuri, switch to thermal!
	level.scr_radio[ "intro_pri_switchthermal" ]		= "intro_pri_switchthermal";
	//Price: Use your thermal!
	level.scr_radio[ "intro_pri_usethermal" ]		= "intro_pri_usethermal";
	//Price: That .50 cal will punch right through walls!
	level.scr_radio[ "intro_pri_punchwalls" ]		= "intro_pri_punchwalls";
	//Price: Use your grenade launcher!
	level.scr_radio[ "intro_pri_uselauncher" ]		= "intro_pri_uselauncher";
	//Price: Take out those choppers!
	level.scr_radio[ "intro_pri_takeoutchoppers" ]		= "intro_pri_takeoutchoppers";
	//Price: Yuri, we're moving up! Keep them pinned down!
	level.scr_radio[ "intro_pri_weremovingup" ]		= "intro_pri_weremovingup";
	//Price: We're at the chopper! Loading Soap in now!
	level.scr_radio[ "intro_pri_atthechopper" ]		= "intro_pri_atthechopper";
	//Nikolai: He's not looking good.
	level.scr_radio[ "intro_nik_notlookinggood" ]		= "intro_nik_notlookinggood";
	//Price: Drone inbound!
	level.scr_radio[ "intro_pri_droneinbound" ]		= "intro_pri_droneinbound";
	//Price: Yuri, run to the chopper! Move!
	level.scr_radio[ "intro_pri_runtochopper" ]		= "intro_pri_runtochopper";
	//Price: Go! Go!
	level.scr_radio[ "intro_pri_gogo" ]		= "intro_pri_gogo";
	//Price: Look out!
	level.scr_radio[ "intro_pri_lookout2" ]		= "intro_pri_lookout2";
	//Price: Hold on!
	level.scr_sound[Price][ "intro_pri_holdon" ]		= "intro_pri_holdon";
	//Price: We'll need him. We're going after Makarov.
	level.scr_sound[Price][ "intro_pri_aftermakarov" ]		= "intro_pri_aftermakarov";
	//Soap: Who the bloody hell's Yuri?
	level.scr_radio[ "intro_mct_whosyuri" ]		= "intro_mct_whosyuri";
	//Nikolai: There he is!
	level.scr_radio[ "intro_nik_thereheis" ]		= "intro_nik_thereheis";
	//Price: Good.  We'll need him. We're going after Makarov.
	level.scr_radio[ "intro_pri_aftermakarov" ]		= "intro_pri_aftermakarov";


}

//---- INTRO ----//
intro_dialog()
{
	flag_wait( "intro_dialog_shot_1" );
	wait 5;
	//on gurney
	level.price dialogue_queue( "intro_pri_inside" );
	//Start to roll down an alleyway...
	flag_wait( "intro_dialog_shot_2" );	
	//level.nikolai dialogue_queue( "intro_nik_safehouse" );
	
	//level.price dialogue_queue( "intro_pri_keepmoving" );

	
	//hallway
	//Fade up being rolled through a hallway, 
	flag_wait( "intro_dialog_shot_3" );
	level.price dialogue_queue( "intro_pri_getdoctor" );
	
	flag_wait( "intro_dialog_shot_4" );
	
	//level.price dialogue_queue( "intro_nik_keeppressure" );

	//level.nikolai dialogue_queue( "intro_nik_imtrying" );
	
	//level.nikolai dialogue_queue( "intro_nik_hanginthere" );

	flag_wait( "intro_dialog_shot_5" );
	//Room
	wait 2;
	level.price dialogue_queue( "intro_pri_needshelp" );
	
	wait 2;
	level.nikolai dialogue_queue( "intro_nik_321clear" );
	//wait 1;
	//level.nikolai dialogue_queue( "intro_nik_threetwoone" );
	flag_set( "intro_opening_movie_start" );

}

intro_dialog_transition()
{
	radio_dialogue( "intro_loy1_attackchoppers" );
	radio_dialogue( "intro_loy2_howmany" );
	radio_dialogue( "intro_loy1_fastroping" );
	radio_dialogue( "intro_loy2_fireteam" );
	
	flag_set( "intro_transition_dialog_end" );
	level.soap dialogue_queue( "intro_nik_yuri" );//playing this line on soap to stop collisions with the facial animation on nikolai

	//Gameplay
	flag_wait( "intro_dialog_shot_7" );
	aud_send_msg("mus_vo_nik_yurioverhere");
	wait 3;
	level.price dialogue_queue( "intro_pri_getsoap" );
	
	flag_wait( "intro_dialog_shot_8" );
	wait 3;
	level.price dialogue_queue( "intro_pri_iseveryone" );

	flag_wait( "intro_dialog_shot_8_complete" );
	flag_set( "courtyard_dialog_balcony_start" );
}



//---- COURTYARD ----//
courtyard_dialog_intro()
{
	flag_wait( "courtyard_dialog_balcony_start" );
	thread courtyard_take_position_on_balcony();
	flag_wait( "courtyard_dialog_intro_start" );
}

courtyard_take_position_on_balcony()
{
	level.price dialogue_queue( "intro_pri_balcony" );

	flag_set( "courtyard_dialog_intro_end" );
	flag_set( "obj_take_position_on_balcony" );
	
}


courtyard_dialog_watch_breach()
{
	//level.nikolai dialogue_queue( "intro_nik_menonturrets" );
	level.price dialogue_queue( "intro_pri_eyesoncourtyard" );
	aud_send_msg("mus_eyes_on_courtyard");
	flag_set( "obj_watch_courtyard" );
	//level.price dialogue_queue( "intro_pri_firedonebefore" );
}

courtyard_dialog_breached()
{
	wait( .5 );
	level.price dialogue_queue( "intro_pri_theybreached" );
	
	wait 3;
	level.price dialogue_queue( "intro_pri_holdthemoff" );
	
	//hint( "Price: We need to hold them off until we can move Soap!", 2 );
	
	wait 3;
	
	radio_dialogue( "intro_loy1_ineedshooters" );
	
	radio_dialogue( "intro_loy2_morechoppers" );
	
	/*
	hint( "Price: Nikolai, how's Soap?", 2 );
	hint( "Nikolai: He's a bloody mess, but he's stable!", 2 );
	*/
}

courtyard_dialog_combat_done()
{
	//hint( "Price: We gotta move!", 3 );
}

//---- ESCORT ----//

escort_dialog()
{
	thread escort_dialog_help_soap();
	thread escort_dialog_help_soap_give_shot();
	thread escort_dialog_exit_hotel();
	thread escort_dialog_at_stairs();
	thread escort_dialog_courtyard();
}

escort_dialog_help_soap()
{
	flag_wait( "escort_player_help_soap" );
	level.nikolai dialogue_queue( "intro_nik_doctorsdown" );

	wait .5;
	level.nikolai dialogue_queue( "intro_nik_needyourhelp" );

	thread escort_dialog_help_soap_nag();
}

escort_dialog_help_soap_nag()
{
	level endon( "escort_player_helping_soap" );
	
	while( !flag( "escort_player_helping_soap" ) )
	{
		level.nikolai dialogue_queue( "intro_nik_getoverhere" );
		wait( 5 );
	}
}

escort_dialog_help_soap_give_shot()
{
	flag_wait( "escort_player_helping_soap" );
	level.nikolai dialogue_queue( "intro_nik_theshot" );
}

escort_dialog_exit_hotel()
{
	flag_wait( "escort_help_soap_breachers_dead" );
	//level.price dialogue_queue( "intro_pri_soaptochopper" );
	wait 2;
	level.Nikolai dialogue_queue( "intro_nik_ivegothim" );
	//level.price dialogue_queue( "intro_pri_yourewithme" );
}

escort_dialog_at_stairs()
{
	flag_wait( "escort_player_exited_room" );
	level.price dialogue_queue( "intro_pri_yurioverhere" );
	flag_wait( "escort_rappelers_dead" );
	level.price dialogue_queue( "intro_pri_downthestairs" );
}

escort_dialog_courtyard()
{
	flag_wait( "escort_player_starting_courtyard" );
	level.price dialogue_queue( "intro_pri_yurionme" );
	level.price dialogue_queue( "intro_pri_throughcourtyard" );
	
	flag_wait( "escort_player_halfway_through_courtyard" );
	aud_send_msg("mus_halfway_through_courtyard");
	radio_dialogue( "intro_loy1_pinneddown" );
}

escort_dialog_courtyard_clear()
{
	vol = getent( "escort_courtyard_clear_dialog", "targetname" );
	
	while( vol get_ai_touching_volume( "axis" ).size > 0 )
		wait .1;
		
	radio_dialogue( "intro_loy2_courtyardsclear" );
}

//---- REGROUP ----//
regroup_dialog()
{
	thread regroup_dialog_before_street_battle();
	thread regroup_dialog_street_battle();
	thread regroup_dialog_weapons_ahead();
}

regroup_dialog_before_street_battle()
{
	flag_wait( "regroup_dialog_intro_start_all_clear" );
	aud_send_msg("vo_price_moveup");
	wait 3;
	//radio_dialogue( "intro_nik_roger" );
	wait 8;
	radio_dialogue( "intro_nik_weaponscache" );
	flag_set( "regroup_dialog_intro_complete" );
	
	//flag_wait( "regroup_start_civilian_run" );
	//level.price dialogue_queue( "intro_pri_civilians" );
	
}

regroup_dialog_street_battle()
{
	flag_wait( "regroup_player_starting_street_battle" );

	level.price dialogue_queue( "intro_pri_watchbalconies" );

	level.price dialogue_queue( "intro_pri_protectsoap" );

	level.price dialogue_queue( "intro_pri_doorwayright" );
	
	thread regroup_dialog_uav_street();
	
	wait 2; 
	
	level.price dialogue_queue( "intro_pri_downthestreet" );
	//hint( "Price: Keep moving down the street!", 2 );
	
	level.price dialogue_queue( "intro_pri_getsoapout" );
	//hint( "Price: We've got to Soap out of here!", 2 );
	
	flag_wait( "regroup_mg_dialog" );
	if( !flag( "regroup_mg_gunner_dead" ) )
	level.price dialogue_queue( "intro_pri_machinegunner" );
	//hint( "Price: Machine gunner on the balcony! Take him out!", 2 );
	
	//wait 2;
	//hint( "Price: Yuri, look for flanking routes!", 2 );
	
	flag_wait( "regroup_roll_up_dialog" );
	/*
	hint( "Price: More of them, coming out of the building!", 2 );
	wait 1; 
	hint( "Price: Nikolai, you still with us?!", 2 );
	wait .5;
	hint( "Nikolai: Da, moving up now!", 2 );
	*/
	
	flag_wait( "regroup_player_moving_down_alleyway" );
	level.price dialogue_queue( "intro_pri_chopperthisway" );
	
}

regroup_dialog_uav_street()
{
	flag_wait( "regroup_uav_street_start" );
	wait .5;
	level.price dialogue_queue( "intro_pri_dronepass" );
}

regroup_dialog_weapons_ahead()
{
	flag_wait( "regroup_player_approaching_maars_building" );
	level.Nikolai dialogue_queue( "intro_nik_directlyahead" );
	flag_wait( "regroup_ending_ugv_dialog_start" );
	level.Price dialogue_queue( "intro_pri_toomanyofthem" );
	//hint( "Price: There's too many of them between us and the chopper.", 3 );
	
	
	level.Price dialogue_queue( "intro_pri_needthatugv" );
	//hint( "Price: Nikolai, we need that UGV now!", 3 );
	
	
	level.Nikolai dialogue_queue( "intro_nik_gothrough" );
	
	
	flag_set( "regroup_ending_ugv_dialog_end" );
	level.Price dialogue_queue( "intro_pri_yurithisway" );
	//hint( "Price: Yuri, this way!", 3 );
	thread regroup_dialog_get_to_shed_nag();

	//level.price dialogue_queue( "intro_pri_yurioverhere2" );	
	
	flag_wait( "regroup_ending_shotgun_breach_dialog" );
	radio_dialogue( "intro_loy2_breaching" );
	
	flag_wait( "regroup_ending_dialog_get_inside" );
	//level.Price dialogue_queue( "intro_pri_holdup" );

}

regroup_dialog_get_to_shed_nag()
{
	count = 0;
	while( !flag( "regroup_ending_breaching" ) )
	{
		if( count % 2 )
		{
			level.Price dialogue_queue( "intro_pri_ugvthisway" );
			//hint( "Price: Yuri, the UGV is this way!", 3 );
		}
		else
		{
			level.Price dialogue_queue( "intro_pri_overhere" );
			//hint( "Price: Yuri, over here!", 3 );
		}
		count++;
		wait 5;
	}
}




//---- MAARS SHED ---//

maars_shed_dialog()
{
	thread maars_shed_dialog_start();
}

maars_shed_dialog_start()
{
	flag_wait( "maars_shed_price_at_door" );
	level.price dialogue_queue( "intro_pri_holdup" );
	
	flag_wait( "maars_control_reinforcements" );
	wait 2;
	
	flag_wait( "maars_control_start_intro" );
	level.price dialogue_queue( "intro_pri_getinside" );
	level.Nikolai dialogue_queue( "intro_nik_shippingcrate" );
	
	wait( 10 );
	level.price dialogue_queue( "intro_pri_iseeit" );
	
	flag_wait( "maars_control_dialog_ugv_intro" );
	//level.price dialogue_queue( "intro_pri_ugv" );
}

//---- MAARS CONTROL ----//

maars_control_dialog()
{
	thread maars_control_dialog_start();
	thread maars_control_dialog_moving();
	thread maars_control_use_grenades();
	thread maars_control_shoot_helicopters();
	//thread maars_control_dialog_smoke();
}

maars_control_dialog_start()
{
	flag_wait( "player_to_maars_control" );
	level.price dialogue_queue( "intro_pri_controlsrussian" );
	//hint( "Controls are going to be in Russian. You're up, Yuri.", 3 );
	thread maars_control_start_controlling_nag();
	
	flag_wait( "maars_control_player_controlling_maars" );
	level.price dialogue_queue( "intro_pri_soapscondition" );
	//hint( "Price: Nikolai, what's Soap's condition?", 2);
	level.nikolai dialogue_queue( "intro_nik_gethimout" );
	//hint( "Nikolai: We've got to get him out of here!", 2);
	level.price dialogue_queue( "intro_pri_wellbebehind" );
	//hint( "Yuri, clear a path to the chopper. We'll be right behind you!", 2);
	
	//radio_dialogue( "intro_pri_targetanything" );
	
	wait 5;
	radio_dialogue( "intro_pri_punchwalls" );
}

maars_control_start_controlling_nag()
{
	wait( 6 );
	while( !flag( "maars_control_player_controlling_maars" ) )
	{
			level.price dialogue_queue( "intro_pri_grabcontrols" );
			wait( 6 );
	}
}

maars_control_use_grenades()
{
	flag_wait( "maars_control_spawn1_retreat" );
	radio_dialogue( "intro_pri_uselauncher" );
}

maars_control_shoot_helicopters()
{
	flag_wait( "maars_control_mi17_1" );
	radio_dialogue( "intro_pri_takeoutchoppers" );
}

maars_control_dialog_smoke()
{
	flag_wait( "maars_control_smoke_hint" );
	radio_dialogue( "intro_pri_switchthermal" );
	thread maars_control_dialog_thermal_nag();
}

maars_control_dialog_thermal_nag()
{
	wait( 2 );
	if( !flag( "maars_thermal_on" ) )
	{
		radio_dialogue( "intro_pri_usethermal" );
	}
}

maars_control_dialog_moving()
{
	flag_wait( "maars_control_dialog_clear_path" );
	//hint( "Price: Clear the path!", 3 );
	radio_dialogue( "intro_pri_clearthepath" );
	
	flag_wait( "maars_control_price_moving_up" );
	radio_dialogue( "intro_pri_weremovingup" );
	
	flag_wait( "maars_control_dialog_keep_pushing" );
//	hint( "Price: Keep pushing to the chopper!", 3 );
	radio_dialogue( "intro_pri_keeppushing" );
	
	
	flag_wait( "maars_control_uav_start_dialog" );
	wait 1;
	radio_dialogue( "intro_pri_atthechopper" );
	radio_dialogue( "intro_nik_notlookinggood" );
	flag_set( "maars_control_drone_inbound" );
	wait .5;
	radio_dialogue( "intro_pri_droneinbound" );
	flag_set( "maars_control_uav_start" );
}


//---- BUILDING SLIDE ----//

building_slide_dialog()
{
	radio_dialogue( "intro_pri_runtochopper" );
	
	wait( 2 );
	radio_dialogue( "intro_pri_gogo" );

	flag_wait( "building_event_start" );
	radio_dialogue( "intro_pri_lookout2" );
			
}

river_ride_dialog1( guy )
{
	radio_dialogue( "intro_nik_thereheis" );
	flag_set( "building_slide_pickup" );
	radio_dialogue( "intro_pri_aftermakarov" );
	radio_dialogue( "intro_mct_whosyuri" );
}

river_ride_dialog2( guy )
{
	//level.price dialogue_queue( "intro_pri_gunslinger" );
}

river_ride_dialog3( guy )
{
	//level.nikolai dialogue_queue( "intro_nik_mybest" );
}

river_ride_dialog4( guy )
{
	//level.price dialogue_queue( "intro_pri_aftermakarov" );
}

river_ride_dialog5( guy )
{
	//level.soap dialogue_queue( "intro_mct_whosyuri" );
}
