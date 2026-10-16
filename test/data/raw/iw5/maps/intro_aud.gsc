#include maps\_utility;
#include common_scripts\utility;
#include maps\_audio;
#include maps\_audio_zone_manager;
#include maps\_audio_music;
#include maps\_audio_mix_manager;
#include maps\_audio_vehicles;
#include maps\_audio_dynamic_ambi;

/#
VIDCAP	= 0;
#/

main()
{
	if( getdvarint( "prologue_select" ) )
	{
		aud_set_level_fade_time(0);
	}
	else
	{
		aud_set_level_fade_time(3);
	}
	aud_init();
	aud_config_system();
	aud_init_flags();
	aud_init_globals();
	aud_launch_threads();
	aud_launch_loops();
	aud_create_level_envelop_arrays();
	aud_register_trigger_callbacks();
	aud_add_note_track_data();
	aud_precache_presets();
	aud_register_handlers();

	MM_add_submix("intro_level_global_mix", 1);
}

aud_config_system()
{
	set_stringtable_mapname("shg");
	aud_set_occlusion("med_occlusion");
	aud_set_timescale("shg_default", 20);
}

aud_init_flags()
{
	flag_init("aud_rear_strafe_stomp");
	flag_init("mi28_doctor_kill_flyout");
	flag_init("aud_mi28_gun_occlusion_off");
	flag_init("aud_maars_shed_heli_swap");
	flag_init("aud_mars_dead");
	flag_init("aud_stop_maars_impacts");
}

aud_init_globals()
{
	if (!IsDefined(level.aud))
	{
		level.aud = SpawnStruct();
	}

	if( getdvarint( "prologue_select" ) )
	{
		level.aud.next_flash_back_index = 0;
		level.aud.flashback_aliases = // [alias, white-start-offset]
			[	["prolog_flashback1", 3.90],
				["prolog_flashback2", 5.13],
				["prolog_flashback3", 5.20],
				["prolog_flashback4", 5.20]
			];
		level.aud.flashback_ent = undefined;
		level.aud.maars_dmg_intensity = 0.01;
	}

	level.aud.first_attack_heli_played = false;

	// Slow motion settings.
	thread aud_ignore_slowmo();
}

aud_launch_threads()
{
	thread aud_fireloops_start();
}

aud_launch_loops()
{
}

aud_create_level_envelop_arrays()
{
	level.aud.envs["maars_lo_dmg_scale"]	=	[
											[0.000,  0.000],
											[0.050,  0.100],
											[0.100,  0.150],
											[0.200,  0.500],
											[0.300,  0.600],
											[0.400,  0.700],
											[0.500,  0.500],
											[0.600,  0.400],
											[0.800,  0.200],
											[1.000,  0.000]
										];


	level.aud.envs["maars_hi_dmg_scale"]	=	[
											[0.000,  0.000],
											[0.050,  0.000],
											[0.100,  0.000],
											[0.200,  0.000],
											[0.300,  0.000],
											[0.400,  0.000],
											[0.500,  0.400],
											[0.600,  0.600],
											[0.800,  0.800],
											[1.000,  1.000]
										];


	level.aud.envs["maars_mix_dmg_blend"]	=	[
											[0.000,  0.000],
											[0.050,  0.200],
											[0.075,  0.300],
											[0.100,  0.400],
											[0.140,  0.500],
											[0.180,  0.600],
											[0.200,  0.800],
											[0.250,  1.000],
											[1.000,  1.000]
										];
}

aud_register_trigger_callbacks()
{
}

aud_add_note_track_data()
{
	//Slide River Sequence
	anim.notetracks[ "aud_intro_river_sequence" ] = ::aud_intro_river_sequence;
}

aud_precache_presets()
{
}

aud_register_handlers()
{
	aud_register_msg_handler(::audio_msg_handler);
	aud_register_msg_handler(::music_msg_handler);
}

/********************************************************************
	Level Audio Message Handler Function.
********************************************************************/
audio_msg_handler(msg, args)
{
	msg_handled = true;

	switch(msg)
	{
		/*******************************/
		/***** CHECKPOINT HANDLERS *****/
		/*******************************/

		case "start_intro": // intro scripted sequence audio (no audio zone)
		{
			/#
			if (VIDCAP)
			{
				iprintln("LEVEL START");
				ent = spawn("script_origin", (0,0,0));
				ent PlaySound("typewriter");
			}
			#/
			MM_add_submix("prolog_intro_mix", 0.1);
			wait(0.2);
			heartheli = aud_play_2d_sound("prolog_intro");
			heartheli scalevolume(0.25);
			wait(0.05);
			heartheli scalevolume(1, 6);
		}
		break;

		case "start_intro_transition":
		{
			AZM_start_zone("intro_courtyard_interior");
			aud_play_2d_sound("india_intro");
			//aud_play_2d_sound("india_intro_sitar");
			music_cue("mus_start_intro_transition");
		}
		break;

		case "start_courtyard": // after intro video, in balcony
		{
			AZM_start_zone("intro_courtyard");
		}
		break;

		case "start_escourt": // still inside the courtyard zone, this starts after the intro battle sequence
		{
			AZM_start_zone("intro_courtyard");
			music_cue("mus_eyes_on_courtyard");
		}
		break;

		case "start_regroup": // after the inner courtyard, and after the gate, right at beginning of intro_street
		{
			AZM_start_zone("intro_street");
			music_cue("mus_eyes_on_courtyard");
		}
		break;

		case "start_maars_shed": // Before the "civilian door breach."
		{
			AZM_start_zone("intro_street");
			music_cue("mus_courtyard_gate_breach");
		}
		break;

		case "start_maars_control": // right at end of street battle, right before entering the shack
		{
			AZM_start_zone("intro_street");
			music_cue("mus_start_point_only_maars_control");
		}
		break;

		case "start_slide":
		{
			AZM_start_zone("intro_shack_underground");
		}
		break;

		/***********************************/
		/***** AWESOME TRIGGER HANDLERS ****/
		/***********************************/

		//Blend Trigger: intro_courtyard intro_temple_hallway

		case "enter_intro_temple_hallway":
		{
			zone_from = args;
		}
		break;

		case "exit_intro_temple_hallway":
		{
			zone_to = args;
		}
		break;

		//Blend Trigger: intro_temple_hallway intro_temple_under

		case "enter_intro_temple_under":
		{
			zone_from = args;
		}
		break;

		case "exit_intro_temple_under":
		{
			zone_to = args;
		}
		break;

		//Blend Trigger: intro_temple_under intro_courtyard_ground

		case "enter_intro_courtyard_ground":
		{
			zone_from = args;
		}
		break;

		case "exit_intro_courtyard_ground":
		{
			zone_to = args;
		}
		break;

		//Blend Trigger: intro_courtyard_ground intro_street
		//Blend Trigger: intro_street_house intro_street
		//Blend Trigger: intro_shack_underground intro_street

		case "enter_intro_street":
		{
			zone_from = args;
		}
		break;

		case "exit_intro_street":
		{
			zone_to = args;
		}
		break;

		//Blend Trigger: intro_street intro_street_room

		case "enter_intro_street_room":
		{
			zone_from = args;
		}
		break;

		case "exit_intro_street_room":
		{
			zone_to = args;
		}
		break;

		//Blend Trigger: intro_street intro_street_house

		case "enter_intro_street_house":
		{
			zone_from = args;
		}
		break;

		case "exit_intro_street_house":
		{
			zone_to = args;
		}
		break;

		//Blend Trigger: intro_shack_street intro_shack

		case "enter_intro_shack":
		{
			zone_from = args;
		}
		break;

		case "exit_intro_shack":
		{
			zone_to = args;
		}
		break;

		//Blend Trigger: intro_shack intro_shack_underground

		case "enter_intro_shack_underground":
		{
			zone_from = args;
		}
		break;

		case "exit_intro_shack_underground":
		{
			zone_to = args;
		}
		break;

		//Blend Trigger: enter_intro_shack_underground intro_street_maars

		case "enter_intro_street_maars":
		{
			zone_from = args;
		}
		break;

		case "exit_intro_street_maars":
		{
			zone_to = args;
		}
		break;

		/**************************/
		/***** EVENT HANDLERS *****/
		/**************************/

//////////////////////////////////////////
//////**** INTRO/GURNEY/FLASHBACK ****///
////////////////////////////////////////

		case "intro_white_fade_in":	// Big white flash from black intro screen to initial gameplay.
		{
			// Set up new mix.
			MM_clear_submix("prolog_intro_mix", 2);
			MM_add_submix("prolog_gurney_mix", 2);

			// Play Flashback Transition Sound
			//aud_play_flashback_begin();
			wait(6);
			//aud_play_flashback_end();

			// Start ambience & music.
			AZM_start_zone("intro_courtyard", 3);
			music_cue("mus_gurney_scene", 3);
			wait(3);
			// Start the main heartbeat loop.
			aud_start_gurney_heartbeat_loop();
		}
		break;

		case "start_gurney_scene_heli":
		{
			heli = args;
			assert(IsDefined(heli));
			//heli PlayLoopSound("prolog_heli_loop");
		}
		break;

		case "cinematic_sequence_prep":
		{
			assert(!IsDefined(level.aud.flashback_ent));
			level.aud.flashback_ent = spawn("script_origin", level.player.origin);
			aud_prime_flashback();
		}
		break;

		case "cinematic_sequence_cleanup":
		{
			assert(IsDefined(level.aud.flashback_ent));
			level.aud.flashback_ent StopSounds();
			wait(0.1);
			level.aud.flashback_ent delete();
			level.aud.flashback_ent = undefined;
		}
		break;

		case "start_gurney_heartbeat":
		{
			aud_start_gurney_heartbeat_loop();
		}
		break;

		case "stop_gurney_heartbeat":
		{
			aud_stop_gurney_heartbeat_loop();
		}
		break;

		case "intro_fade_out_to_white":
		{
			//iprintlnbold("fade_out_to_white");
			aud_play_flashback_begin();
		}
		break;

		case "intro_fade_in_from_white":
		{
			//iprintlnbold("fade_in_from_white");
		}
		break;

		case "begin_cinematic":
		{
/#
			if (VIDCAP)
			{
				iprintln("begin_cinematic");
			}
#/
			// Change Mix to Flashback scene.
			MM_add_submix("prolog_flashback_mix", 0);

			// Play Primed Flashback Audio Stream (and release the prime on it).
			alias = aud_get_curr_flashback_alias();
			assert(IsString(alias));
			level.aud.flashback_ent PlaySound(alias);
			aud_release_primed_flashback();

			// Play special case timed audio events for flashbacks.
			if (alias == "prolog_flashback2")
			{
				//DelayThread(4.88, ::aud_play_2d_sound, "prolog_flashback2_gunshot");
				thread aud_play_flashback2_gunshot();
			}
			else if (alias == "prolog_flashback3")
			{
				//DelayThread(5.20, ::aud_play_2d_sound, "prolog_flashback3_splash");
				thread aud_play_flashback3_splash();
			}

			// Schedule the "Flash Out" transition sound to play when this video ends.
			white_offset = aud_get_curr_flashback_white_offset();
			white_offset = white_offset - 0.2; // So trans sound overlaps the transition boundry.
			DelayThread(white_offset, ::aud_play_flashback_end);
		}
		break;

		case "end_cinematic":
		{
/#
			if (VIDCAP)
			{
				iprintln("end_cinematic");
			}
#/
			// Reset Mix to normal gameplay mix.
			MM_clear_submix("prolog_flashback_mix", 0);

			// Prime next flashback auido stream.
			aud_inc_flashback_index();
			aud_prime_flashback();
		}
		break;

		case "intro_shot_1_start":
		{
			//iprintlnbold("shot_1");
			wait(6.3);
			aud_play_2d_sound("prolog_gurney_se_chopper");
		}
		break;

		case "intro_shot_2_start":
		{
			//iprintlnbold("shot_2");
			aud_play_2d_sound("prolog_gurney_se_01");
		}
		break;

		case "intro_shot_3_start":
		{
			//iprintlnbold("shot_3");
			aud_play_2d_sound("prolog_gurney_se_02");
		}
		break;

		case "intro_shot_4_start":
		{
			//iprintlnbold("shot_4");
			aud_play_2d_sound("prolog_gurney_se_03");
		}
		break;

		case "intro_shot_5_start":
		{
			//iprintlnbold("shot_5");
			aud_play_2d_sound("prolog_gurney_se_04");
		}
		break;

		case "intro_opening_movie_start":
		{
			MM_start_preset("mute_all", 1);
		}
		break;

		case "intro_soap_temple_start":
		{
			wait(1.2);
			aud_play_2d_sound("intro_soapcough_se");
		}
		break;

		case "intro_shot_7":
		{
			aud_crashing_helicopter_flyin();
		}
		break;

		case "intro_shot_8":
		{
			thread aud_crashing_helicopter_impact();
			wait(11.0);
			AZM_start_zone("intro_courtyard");
			mm_add_submix("intro_courtyard_skybattle");
			flag_set("aud_mi28_gun_occlusion_off");
		}
		break;

//////////////////////////////////////////
//////**** SAFEHOUSE SKYBATTLE ********//
////////////////////////////////////////

		case "courtyard_magic_rpg_01": //Magic Bullet that kills Courtyard_heli_Mi17_01
		{
			fire_tag = args[0];
			missile = args[1];

			thread play_sound_in_space("heli_missile_launch", fire_tag);
			aud_play_linked_sound("heli_death_missile_incoming", missile);
		}
		break;

		case "courtyard_heli_Mi17_01":   // Drops off troops: Needs Vehicle System attached to it.
		{
			if(!IsDefined(args))
				return;

			blade_lp = thread aud_play_linked_sound( "mi17_blades_loop", args, "loop", "kill_courtyard_heli_Mi17_01_loop");

			args thread aud_heli_death_watch( blade_lp ); //Handles deathspin and explosion.
		}
		break;

		case "courtyard_mi17_drone1": // Called multiple times.
		{
			if(!IsDefined(args[0]))
				return;

			//aud_heli_print_msg("heli_drone_by");
			//args[0] thread aud_print_3d_on_ent("courtyard_mi17_drone1", 5);
			//args thread aud_start_helicopter("courtyard_mi17_drone", true);
		}
		break;

		case "courtyard_mi17_drone3_kill": // 2nd flyby close mi17 after another mi17 crashes to the left (no idea why this is called "kill").
		{
			if(!Isdefined(args))
				return;


			wait(7);
			//aud_heli_print_msg("START_DRONE WHOOSH");
			//aud_play_linked_sound("heli_drone_by_02", args);

			//args thread aud_print_3d_on_ent("courtyard_mi17_drone3_kill", 5);
		}
		break;

		case "attack_heli_mi28_1": //First Heli By. Very close. Needs desinged heli by.
		{
			if(!IsDefined(args))
				return;
			//args thread aud_start_helicopter("attack_heli_mi28_1", true);
		}
		break;

		case "attack_heli_mi28_5": //Very distant, hidden behind buldings. May not need Audio.
		{
			if(!IsDefined(args))
				return;
			//args thread aud_start_helicopter("attack_heli_mi28_5", true);
		}
		break;

		case "attack_heli_mi28_6": //Med Dist By off to the left may not need audio.
		{
			if(!IsDefined(args))
				return;
			//args thread aud_start_helicopter("attack_heli_mi28_6", true);
		}
		break;

		case "attack_heli_mi28_2": //This is the first heli by, very close...needs cool whoosh.
		{
			if(!IsDefined(args))
				return;

			//aud_heli_print_msg("attack_heli_mi28_2");

			wait(3);
			blade_ent = aud_play_linked_sound("mi28_blades_loop", args, "loop", "aud_attack_heli_mi28_2_kill_loop");
			blade_ent scalevolume(0);
			wait(0.05);
			blade_ent scalevolume(1, 3);
			wait(2);

			//aud_heli_print_msg("PLAY_CHOPPER_BY");
			aud_play_linked_sound("mi28_1_flyby_quick_1", args);  //Oneshot triggered when the heli gets close
			thread aud_delay_play_2d_sound("heli_by_lfe_long", 2.3);
			thread aud_delay_play_2d_sound("heli_by_rattles_05", 2);
			wait(3);
			blade_ent scalevolume(0, 3);
			wait(3);
			//args thread aud_start_helicopter("attack_heli_mi28_2", true);
		}
		break;

		case "attack_heli_mi28_3": // Starts off Distant, flys towards window, breaks right. Close, needs a cool by.
		{
			if(!IsDefined(args))
				return;

			wait(6);
			aud_play_linked_sound("mi28_3_long_by", args);
			low_ent = aud_play_linked_sound("mi28_blades_loop", args, "loop", "aud_attack_heli_mi28_3_kill_loop");
			//aud_heli_print_msg("start_oneshot");   // @7 sec.

			thread aud_delay_play_2d_sound("heli_by_lfe_long", 5.6);
			thread aud_delay_play_2d_sound("heli_by_rattles_04", 5.5);

			wait(4);
			aud_play_linked_sound("mi28_2_flyby_quick_1", args);
			wait(3);
			low_ent scalevolume(0.0, 3);
			wait(3.05);
			level notify("aud_attack_heli_mi28_3_kill_loop");
		}
		break;

		case "attack_heli_mi28_8": // Lead strafe attack chopper, right side. Very close, needs cool oneshot. Circles back and comes at player again ~22 sec later.
		{
			// Helis fly far away and then return for a second strafe.

			if(!IsDefined(args))
				return;
			//args thread aud_print_3d_on_ent("HELI_08", 8);

			rear_flyby_01 = aud_play_linked_sound("mi28_8_long_by", args);

			wait(17.5);

			//aud_heli_print_msg("8_SECOND_PASS");

			second_flyby_01 = aud_play_linked_sound("mi28_8_second_pass", args);
			second_flyby_02 = aud_play_linked_sound("mi28_8_second_pass_close", args);

			wait(3.5);

			// Play Flyby LFE shake and building rattles. (Serves as shake for both Mi28 #7 and #8 because they come in so close together.
			thread aud_delay_play_2d_sound("heli_by_lfe_long", 3);
			thread aud_delay_play_2d_sound("heli_by_rattles_03", 3.2);

			second_flyby_03 = aud_play_linked_sound("intro_mi28_flyby_quick_3", args);
		}
		break;

		case "attack_heli_mi28_7": // Tail strafe attack chopper, right side. Very close, needs cool oneshot. Circles back and comes at player again about ~22 sec later.
		{
			if(!Isdefined(args))
				return;

			//args thread aud_print_3d_on_ent("HELI_07", 7);

			aud_play_linked_sound("mi28_8_long_by", args);

			wait(19.5);

			// Helis fly far away and then return for a second strafe.
			//aud_heli_print_msg("7_SECOND_PASS");
			second_flyby_01 = aud_play_linked_sound("mi28_7_second_pass", args);
			second_flyby_02 = aud_play_linked_sound("mi28_7_second_pass_close", args);
			wait(4);
			second_flyby_03 = aud_play_linked_sound("intro_mi28_flyby_quick_2", args);
		}
		break;

		case "courtyard_helicopter4_kill":  //Chopper Flys by, shoots missiles, then gets hit by a scripted missile attack and blows up mid air.
		{
			if(!IsDefined(args))
				return;

			blades_ent = aud_play_linked_sound("mi28_blades_loop", args, "loop", "aud_courtyard_helicopter4_kill_loop");
			args waittill("death");

			thread play_sound_in_space("courtyard_helicopter4_kill", blades_ent.origin);
			//aud_heli_print_msg("mi28_death");

		}
		break;

		case "escort_doc_down_mi28":  //Strafes in, hovers in courtyard firing at the player, killing the doctor working on Soap.
		{
			if(!IsDefined(args))
				return;

			wait(3);

			blades_ent = aud_play_linked_sound("mi28_blades_loop", args, "loop", "aud_attack_heli_mi28_2_kill_loop");
			blades_ent scalevolume(0);
			wait(0.05);
			blades_ent scalevolume(1, 5);
			wait(2);
			//aud_heli_print_msg("escort_doc_down_mi28");
			incoming_ent = aud_play_linked_sound("mi28_doctor_killer_fly_in", args);

			flag_wait("mi28_doctor_kill_flyout"); // Wait for doctor to die and heli to fly out.

			blades_ent scalevolume(0.75, 1);
			wait(3); //Hold Heli blade loop at 0.5 for 2 sec.
			blades_ent scalevolume(0, 5);
		}
		break;

		case "mi28_doctor_killed_flyout": // Flys over courtyard shooting once player goes down stairs.
		{
			if(!IsDefined(args))
				return;

			wait(3);

			thread aud_delay_play_2d_sound("heli_by_lfe_long", 2);
			thread aud_delay_play_2d_sound("heli_by_rattles_02", 2.5);

			flag_set("mi28_doctor_kill_flyout");
			//aud_heli_print_msg("mi28_doctor_killer_flyout");
			flyout = aud_play_linked_sound("mi28_doctor_killer_flyout", args);

			wait(5);

			mm_clear_submix("intro_courtyard_skybattle");
		}
		break;

		case "escort_doorkick":
		{
			door = args;
			wait(.6);
			door playsound("intro_preshack_house_doorkick");
		}
		break;

		case "aud_courtyard_gate_breach":
		{
			//iprintlnbold("gate_breach");
			wait(.15);
			play_sound_in_space("intro_courtyard_gatekick",(-1534, 1634, 260));
		}
		break;

		case "aud_civilian_door_breach":
		{
			//iprintlnbold("civ_door_breach");
			wait(.38);
			play_sound_in_space("intro_preshack_house_doorkick",(-5177, 3759, -292));
		}
		break;

		case "intro_civ_car_slide":
		{
			car = args;
			//iprintlnbold("start_skid");
			car playsound("intro_carslide_slide");
		}
		break;

		case "intro_civ_car_explode":
		{
			car_location = args;
			//iprintlnbold("civ_boom");
			play_sound_in_space("intro_carslide_explode", car_location);
		}
		break;

//////////////////////////////////////////////////
//////**** Courtyard and Streets ********////////
////////////////////////////////////////////////
	case "courtyard_start_breach":
	{
		static_gate_pos = (-1525, 1131, 371);
		thread play_sound_in_space("courtyard_breach_explode_main", static_gate_pos);
		thread play_sound_in_space("courtyard_breach_explode_wood", static_gate_pos);
		thread play_sound_in_space("courtyard_breach_explode_dist_verb", static_gate_pos);
		thread play_sound_in_space("courtyard_breach_debris_long", static_gate_pos);
	}
	break;

	case "start_civ_runners_wave1a":
	{
			civ_ent_01 = args;
			if (IsArray(civ_ent_01))
			{
			  if(IsDefined( civ_ent_01[0] ))
			  {
			  	//iprintlnbold("civ_loopers_01");
					civ_ent_01[0] play_loop_sound_on_entity("intro_civ_walla_male_01_firstwave");
			  }
			}
	}
	break;

	case "start_civ_runners_wave1b":
	{
			civ_ent_02 = args;
			if (IsArray(civ_ent_02))
			{
			  if(IsDefined( civ_ent_02[0] ))
			  {
			  	//iprintlnbold("civ_loopers_02");
					civ_ent_02[0] play_loop_sound_on_entity("intro_civ_walla_male_01");
			  }
			}
	}
	break;

	case "start_civ_runners_wave1c":
	{
			civ_ent_03 = args;
			if (IsArray(civ_ent_03))
			{
			  if(IsDefined( civ_ent_03[0] ))
			  {
			  	//iprintlnbold("civ_loopers_03");
					civ_ent_03[0] play_loop_sound_on_entity("intro_civ_walla_male_02");
			  }
			}
	}
	break;

	case "start_civ_runners_wave_2":
	{
		drones = args;
		if (IsArray(drones))
			{
			  if(IsDefined( drones[0] ))
			  {
			  	//iprintlnbold("civ_run");
					drones[0] play_loop_sound_on_entity("intro_civ_walla_male_01_loud");
					//iprintlnbold("civ_run_end");
			  }
			}
	}
	break;

	case "escort_mi28_1": // Flys over courtyard shooting once player goes down stairs.
	{
		if(!Isdefined(args))
			return;

		blades_ent = aud_play_linked_sound("mi28_blades_loop", args, "loop", "aud_escort_mi28_1_kill_loop");
		blades_ent scalevolume(0);
		wait(0.05);
		blades_ent scalevolume(1, 4);
		wait(2);
		aud_play_linked_sound("mi28_courtyard_fly_in", args);
		wait(5);
		aud_play_linked_sound("mi28_courtyard_fly_out", args);


		wait(4);

		flag_clear("aud_mi28_gun_occlusion_off");  // Last intro heli has passed, turn regular occlusion for heli guns back on.
	}
	break;


	case "courtyard_exit_flyby_01":  // Flyby as the player exits the courtyard, right to left.
	{
		if(!Isdefined(args))
			return;

		aud_play_linked_sound("mi28_blades_loop", args, "loop","aud_courtyard_heli_flyby_kill_lp");
		wait(8);
		aud_play_linked_sound("mi28_streets_flyover_main", args);
	}
	break;

	case "courtyard_exit_flyby_02":  // Flyby as the player exits the courtyard, right to left.
	{
		if(!Isdefined(args))
			return;

		aud_play_linked_sound("mi28_blades_loop", args, "loop","aud_courtyard_heli_flyby_kill_lp");
		wait(10);
		aud_play_linked_sound("mi28_streets_flyover_02", args);
	}
	break;


	case "regroup_mi17_1":     // Flys over the first street after the cortyard, drops troops.
	{
		if(!Isdefined(args))
			return;

		aud_play_linked_sound("mi17_streets_fly_in", args);
		blades_ent = aud_play_linked_sound("mi17_streets_blades_loop", args, "loop","aud_regroup_mi17_1_kill_lp");
		blades_ent scalevolume(0.0);
		wait(0.05);
		blades_ent scalevolume(1, 3);

		flag_wait( "regroup_mi17_unloaded" );

		if(isdefined(args))
		{
			wait(0.8);
			blades_ent scalevolume(0.5, 3);
			aud_play_linked_sound("mi17_streets_fly_out", args);
		}
	}
	break;

	case "regroup_ending_start":  // Attack helicopter behind a large gate, forces player to take route through houses to get to UGV.
	{
		if(!IsDefined(args))
			return;

		blade_ent = aud_play_linked_sound("mi28_gate_block_blades_loop", args, "loop", "kill_gate_heli_loop");

		wait(3);

		inbound = aud_play_linked_sound("mi28_big_gate_inbound", args);

		flag_wait("aud_maars_shed_heli_swap");
		if (IsDefined(blade_ent))
		{
			blade_ent scalevolume(0, 3);
			wait(3.05);
			level notify("kill_gate_heli_loop");
		}
	}
	break;

	case "regroup_uav_gate_fly_by":   //???????
	{
		if(!IsDefined(args))
			return;

		wait(0.5);
		aud_play_linked_sound("pred_by_courtyard_01", args);
	}
	break;


	case "UAV_street_bombing":  // UAV drops bombs on the street below as it flys by.
	{
		if(!IsDefined(args))
			return;

		aud_play_linked_sound("pred_by_streets_bomb_run", args);
	}
	break;

	case "uav_fire_missile":  // UAV missile shots.
	{
		if(!IsDefined(args))
			return;

		args waittill("missile_hit");

		thread play_sound_in_space("pred_missile_impact_main", args.origin);
	}
	break;

	case "worlds_slowest_helicopter_by":  // Helicopter slowly passes overhead in the back alley before the Maars shed.
	{
		if(!IsDefined(args))
			return;

		aud_play_linked_sound("mi28_by_slow", args, "loop", "aud_slow_flyby_kill_lp");
	}
	break;

//////////////////////////////////////////
//////******* MAARS SHED ********////////
////////////////////////////////////////

	case "intro_shed_bombshake_01":
	{
		//iprintlnbold("bomb_01");
		aud_play_2d_sound("intro_shed_bombshake");
	}
	break;

	case "intro_shed_bombshake_02":
	{
		//iprintlnbold("bomb_02");
		aud_play_2d_sound("intro_shed_bombshake");
	}
	break;

	case "maars_garage_door_opening":
	{
		wait(2.75);
		//iprintlnbold("door");
		aud_play_2d_sound("intro_shack_metaldoor_up");
	}
	break;

//////////////////////////////////////////
//////******* MAARS VEHICLE CONTROL*****/
////////////////////////////////////////

		case "maars_ugv_start":
		{
		}
		break;

		case "player_maars_interact_start":  //Second
		{
			mm_add_submix("intro_maars_control_mix", 2);
			wait(2.1);
			aud_play_2d_sound("maars_bootcomp");
			self thread aud_monitor_maars_impacts();
		}
		break;

		case "maars_computer_boot_up":  // First
		{
			aud_play_2d_sound("maars_comp_enter");
		}
		break;

		case "maars_control_door_open":
		{
			door = args;

			if(!IsDefined(door))
				return;
		}
		break;

		case "maars_player_control_start":
		{
			level.ugv_vehicle thread aud_maars_start_engine();
			level.ugv_vehicle thread aud_maars_damage_intensity();
		}
		break;

		case "maars_grenade_fired":
		{
			grenade = args;
			grenade thread maars_grenade_fired();
		}
		break;

		case "maars_damage_intensity":
		{
			dmg = args;
			level.aud.maars_dmg_intensity = clamp(dmg, 0, 1);
		}
		break;

		case "maars_takes_explosive_dmg":
		{

		}
		break;


		case "maars_takes_bullet_dmg":
		{
		}
		break;

		case "digital_distort_death":
		{

		}
		break;


//////////////////////////////////////////
//////******* MAARS SECTION*** ********//
////////////////////////////////////////

		case "maars_attack_chopper":
		{
			if(!IsDefined(args))
				return;

			//iprintlnbold("maars_attack_chopper");

			if(!level.aud.first_attack_heli_played)
			{
				flag_set("aud_maars_shed_heli_swap");
				blade_lp = aud_play_linked_sound( "mi28_blades_loop", args, "loop", "kill_maars_attack_chopper_loop");
				args thread aud_heli_death_watch( blade_lp );
				blade_lp scalevolume(0);
				wait(0.05);
				blade_lp scalevolume(0.3, 2);
				level.aud.first_attack_heli_played = true;
			}
			else
			{
				blade_lp = aud_play_linked_sound( "mi28_blades_loop", args, "loop", "kill_maars_attack_chopper_loop");
				args thread aud_heli_death_watch( blade_lp );
			}
		}
		break;

		case "maars_transport_chopper":
		{
			if(!IsDefined(args))
				return;

			blade_lp = thread aud_play_linked_sound( "mi17_blades_loop_no_oc", args, "loop", "kill_maars_attack_chopper_loop");

			args thread aud_heli_death_watch( blade_lp );
		}
		break;

		case "maars_control_drone_inbound":
		{
			UAV = args;
			wait(1.2);
			aud_play_2d_sound("maars_death_missile_incoming");

			aud_delay_play_2d_sound("maars_death_short_whoosh", 0.7, true);
			wait(0.8);
			MM_add_submix("intro_maars_death_mix", 0.1);
		}
		break;

		case "uav_kill_maars":
		{
			flag_set("aud_mars_dead");
			flag_set("aud_stop_maars_impacts");
			MM_clear_submix_blend("static_death_blend", 0.2);
			mm_clear_submix("intro_maars_control_mix", 2);
			//Stop Maars Dmg loops.
			level notify("kill_maars_dmg_ent_lo");
			level notify("kill_maars_dmg_ent_hi");

			UAV = args;

			thread VM_stop_preset_instance("ugv_motor_player");
			thread VM_stop_preset_instance("ugv_treads_player");
			thread VM_stop_preset_instance("ugv_idle_player");

			explo_pos = level.player.origin;

			aud_play_2d_sound("maars_death_drone_flyby");
			aud_delay_play_2d_sound("maars_death_tumble", 1.5, true);
			thread play_sound_in_space("finale_missile_impact_2d", explo_pos);
			thread play_sound_in_space("finale_missile_impact_3d", explo_pos);
			thread play_sound_in_space("finale_missile_impact_lyr", explo_pos);
			thread play_sound_in_space("finale_mortar_lfe", explo_pos);
			thread play_sound_in_space("finale_missile_debris", explo_pos);
			wait(0.25);
			thread play_sound_in_space("finale_missile_debris_long", explo_pos);

			thread aud_play_death_static();

			thread aud_start_final_fires();
		}
		break;

		case "heli_fire_missile":
		{
			missile = args;

			thread play_sound_in_space("heli_missile_launch", missile.origin);

			missile thread aud_missile_explode_watch();
		}
		break;

		case "aud_heli_missile_explode":
		{
			missile = args;
			//aud_heli_print_msg("aud_heli_missile_explode");
		}
		break;

//////////////////////////////////////////
//////******* INDIA FINALE ********//////
////////////////////////////////////////
		case "finale_missile_incoming":
		{
			missile = args;
			thread aud_play_linked_sound("finale_missile_incoming", missile);
		}
		break;

		case "finale_missile_impact":
		{
			explo_pos = args;
			thread play_sound_in_space("finale_missile_impact_3d", explo_pos);
			thread play_sound_in_space("finale_missile_impact_lyr", explo_pos);
			thread play_sound_in_space("finale_mortar_lfe", explo_pos);
			thread play_sound_in_space("finale_missile_debris", explo_pos);
			wait(0.25);
			thread play_sound_in_space("finale_missile_debris_long", explo_pos);
		}
		break;

/////////////////////////////////////////////////
//////******* INTRO SLIDE SEQUENCE ********/////
///////////////////////////////////////////////

		case "building_event_start":
		{
			aud_intro_slide_sequence();
		}
		break;

		default:
		{
			msg_handled = false;
		}
	}

	return msg_handled;
}

// For use from within the main audio msg handler.
music_cue(msg, args)
{
	thread music_msg_handler(msg, args);
}

music_msg_handler(msg, args)
{
	// Assume that this msg will be handled.
	msg_handled = true;

	// Only handle Music Messages (must start with "mus_"
	if (GetSubStr(msg, 0, 4) != "mus_")
		return false;

	// Kill any other instances of this thread that may be still active.
	level notify("kill_other_music");
	level endon("kill_other_music");

	// Handle Message.
	switch(msg)
	{
		/*** INTRO CUES ***/
		case "mus_gurney_scene":
		{
			MUS_play("intro_gurney_scene", 0);
		}
		break;


		/*** INDIA CUES ***/

		case "mus_start_intro_transition":
		{
			wait(2);
			MUS_play("india_intro_transition", 5);
		}
		break;

		case "mus_vo_nik_yurioverhere":
		{
			aud_set_music_submix(0.6, 10);
		}
		break;

		case "mus_eyes_on_courtyard":
		{
			aud_set_music_submix(1, 3);
			MUS_play("india_courtyard_combat", 3);
		}
		break;

		case "mus_halfway_through_courtyard":
		{
			//MUS_stop(30);
			MUS_play("india_courtyard_half_way", 8);
		}
		break;

		case "vo_price_moveup":
		{
			MUS_stop(20);
		}
		break;

		case "mus_courtyard_gate_breach":
		{
			aud_set_music_submix(100, 1);
			MUS_play("india_streets", 3);
		}
		break;

		case "mus_civilian_door_breach":
		{
			MUS_play("india_streets_end", 3);
			aud_set_music_submix(1, 5);
			//wait(5);
			//MUS_play("india_stealth", 5);
		}
		break;

		case "mus_start_point_only_maars_control":
		{
			//MUS_play("india_stealth", 5);
		}
		break;

		case "mus_ugv_start":
		{
			aud_set_music_submix(100, 5);
			MUS_play("india_ugv_control", 3);
		}
		break;

		case "mus_ugv_destroyed":
		{
			aud_set_music_submix(1, 5);
			MUS_play("india_ugv_destroyed", 3);
		}
		break;

		case "mus_run_to_heli":
		{
			aud_set_music_submix(100, 5);
			MUS_play("india_run_to_heli", 3);
		}
		break;

		case "mus_player_slide":
		{
			MUS_stop(1);
			aud_set_music_submix(1, 5);
		}
		break;

		case "mus_emerge_from_river":
		{
			MUS_play("india_ending1", 5);
			wait(8);
			MUS_play("india_ending2", 5);
		}
		break;

		default:
		{
			msg_handled = false;
		}
	}

	return msg_handled;
}

aud_play_flashback_begin()	// Wrapper for debugging.
{
	aud_play_2d_sound("intro_flashback_in");
}

aud_play_flashback_end()	// Wrapper for debugging.
{
	aud_play_2d_sound("intro_flashback_out");
}

aud_play_flashback2_gunshot()
{
	wait(5.2);
	aud_play_2d_sound("prolog_flashback2_gunshot");
}

aud_play_flashback3_splash()
{
	wait(5.1);
	aud_play_2d_sound("prolog_flashback3_splash");
}

aud_start_gurney_heartbeat_loop()
{
	if (!IsDefined(level.aud.gurney_heartbeat_ent))
	{
		level.aud.gurney_heartbeat_ent = spawn("script_origin", level.player.origin);
		level.aud.gurney_heartbeat_ent PlayLoopSound("prolog_hearbeat_loop");
	}
}

aud_stop_gurney_heartbeat_loop()
{
	if (IsDefined(level.aud.gurney_heartbeat_ent))
	{
		level.aud.gurney_heartbeat_ent ScaleVolume(0.0, 0.1);
		wait(0.1);
		level.aud.gurney_heartbeat_ent StopLoopSound();
		level.aud.gurney_heartbeat_ent delete();
		level.aud.gurney_heartbeat_ent = undefined;
	}
}

aud_prime_flashback()
{
	alias = aud_get_curr_flashback_alias();
	if (IsString(alias))
	{
		assert(IsString(alias));
		assert(IsDefined(level.aud.flashback_ent));
		level.aud.flashback_ent thread aud_prime_stream(alias, true); // prime streams using the constant re-prime method
	}
}

aud_release_primed_flashback()
{
	alias = aud_get_curr_flashback_alias();
	assert(IsString(alias));
	assert(IsDefined(level.aud.flashback_ent));
	level.aud.flashback_ent aud_release_stream(alias);
}

aud_get_curr_flashback_alias()
{
	alias = undefined;
	sub_array = level.aud.flashback_aliases[level.aud.next_flash_back_index];
	if (IsDefined(sub_array))
	{
		alias = sub_array[0];
	}
	return alias;
}

aud_get_curr_flashback_white_offset()
{
	offset = undefined;
	sub_array = level.aud.flashback_aliases[level.aud.next_flash_back_index];
	if (IsDefined(sub_array))
	{
		offset = sub_array[1];
	}
	return offset;
}

aud_inc_flashback_index()
{
	level.aud.next_flash_back_index++;
}

play_flashback_whoosh()
{
}

aud_start_helicopter( _name, _is_attack_heli, _alias, do_print)
{
	if (!IsDefined(self))
		return;

	// Setup_default_vars.
	is_attack_heli = true;
	name = "No_Name";

	if(Isdefined( _is_attack_heli ))
	{
		is_attack_heli = _is_attack_heli;
	}

	if(Isdefined( _name ))
	{
		name = _name;
	}

	//Debug Printing
	if(Isdefined( do_print ))
	{
		//self thread aud_print_3d_on_ent( name, 4 );
		//iprintlnbold( name );
	}

	if( is_attack_heli )
	 self thread aud_attack_heli( name , _alias );

	if(!is_attack_heli)
	 self thread aud_transport_heli( name, _alias );

}

aud_attack_heli( name , alias )
{
	if(!Isdefined(self))
		return;

	if(!Isdefined( alias ))
		alias = "mi28_blades_loop";

	heli = aud_play_linked_sound( alias, self, "loop", "kill_" + name + "_loop");
	heli scalevolume(0.0);
	wait(0.05);
	heli scalevolume(1, 3);
}

aud_transport_heli( name, alias )
{
	if(!Isdefined(self))
		return;

	if(!Isdefined( alias ))
		alias = "mi17_blades_loop";

	heli = aud_play_linked_sound( alias, self, "loop", "kill_" + name + "_loop");
	heli scalevolume(0.0);
	wait(0.05);
	heli scalevolume(1, 3);
}


aud_missile_explode_watch()
{
	if(!IsDefined(self))
		return;

	loop_ent = aud_play_linked_sound("heli_missile_loop", self, "loop", "aud_stop_heli_missile_loop");

	missile_ent = spawn( "script_origin", self.origin );
	missile_ent linkto( self );

	self waittill("missile_hit");
	loop_ent delete();
	thread play_sound_in_space("finale_missile_impact_3d", missile_ent.origin);
	wait(1.5);
	missile_ent delete();
}

aud_heli_death_watch( blade_lp )
{
	if(!IsDefined(self))
		return;

	heli_track = spawn("script_origin", self.origin);
	heli_track linkto( self );

	self waittill("deathspin");

	ds1 = thread play_sound_in_space("intro_helicopter_crash_hit", heli_track.origin);
	ds2 = thread aud_play_linked_sound("intro_helicopter_crash_blades", heli_track);
	ds3 = thread aud_play_linked_sound("intro_helicopter_crash_engine", heli_track);
	ds4 = thread aud_play_linked_sound("intro_heli_deathspin_explo_whoosh_sweetner", heli_track);
	ds5 = thread aud_play_linked_sound("intro_heli_explo_streamer", heli_track);
	ds6 = thread aud_play_linked_sound("intro_heli_deathspin_secondary_explosion", heli_track);
	ds_array = [ds1, ds2, ds3, ds4, ds5, ds6];
	heli_track playloopsound("intro_heli_deathspin_engine_whine");

	self waittill("death");

	thread play_sound_in_space("intro_helicopter_crash_explo", heli_track.origin);

	foreach( ds in ds_array)
	{
		if(IsDefined(ds))
			ds stopsounds();
	}

	heli_track stopsounds();
	wait(0.05); // Making sure explosion is done before deleting the tracking ent.
	heli_track delete();
}

aud_heli_print_msg( msg )
{
	//iprintlnbold( msg );

//	if(IsDefined(self))
//		self thread aud_print_3d_on_ent( msg );
}

aud_maars_damage_intensity()
{
	flag_wait("maars_control_door_open");

	self thread maars_deathwatch();
	level endon("aud_mars_dead");

	maars_dmg_ent_lo = aud_play_linked_sound("maars_static_dmg_lo", self, "loop", "kill_maars_dmg_ent_lo");
	maars_dmg_ent_hi = aud_play_linked_sound("maars_static_dmg_hi", self, "loop", "kill_maars_dmg_ent_hi");

	max_dmg = 0.25;
	min_dmg = 0.1;

	prev_dmg = 0;

	submix_added = false;
	prev_maars_dmg_value = 0;
	update_rate = 0.1;

	while(1)
	{
		if(IsDefined(level.aud.maars_dmg_intensity))
		{
			current_dmg = level.aud.maars_dmg_intensity;

			maars_dmg = aud_smooth(prev_dmg, current_dmg, 0.001);
			prev_dmg = maars_dmg;

			maars_lo_dmg_vol = aud_map_range(current_dmg, min_dmg, max_dmg, level.aud.envs["maars_lo_dmg_scale"]);
			maars_hi_dmg_vol = aud_map_range(current_dmg, min_dmg, max_dmg, level.aud.envs["maars_hi_dmg_scale"]);

			maars_dmg_value = aud_map_range(current_dmg, min_dmg, max_dmg, level.aud.envs["maars_mix_dmg_blend"]);
			maars_dmg_value = clamp(maars_dmg_value, 0, 1);

			maars_dmg_ent_lo scalevolume(maars_lo_dmg_vol, 0.3);

			maars_dmg_ent_hi scalevolume(maars_hi_dmg_vol, 0.3);

			if (!submix_added)
			{
				submix_added = true;
				MM_add_submix_blend_to( "intro_maars_dying_mix", "static_death_blend", maars_dmg_value);
			}
			else if(maars_dmg_value != prev_maars_dmg_value)
			{
				prev_maars_dmg_value = maars_dmg_value ;
				MM_set_submix_blend_value("static_death_blend", maars_dmg_value, update_rate);
			}
		}

		wait(update_rate);
	}
}

maars_deathwatch()
{

}

aud_maars_start_engine()
{

	thread VM_start_preset("ugv_motor_player", "ugv_motor_player", self);
	thread VM_start_preset("ugv_treads_player", "ugv_treads_player", self);
	wait(1);
	thread VM_start_preset("ugv_idle_player", "ugv_idle_player", self, 4.0);
}

maars_grenade_fired()
{
	//aud_play_2d_sound("maars_grenade_launch");
	aud_play_2d_sound("maars_grenade_launcher_kick");
	self waittill("explode");

	if(Isdefined(self.origin))
	{
		thread play_sound_in_space("maars_grenade_explode", self.origin);
	}
}

aud_monitor_maars_impacts()
{
	level endon("aud_stop_maars_impacts");

	while(true)
	{
		level.player waittill( "damage", amount, attacker, direction, point, damage_type );
		//iprintlnbold("ARMOR_HIT");
		level.player playsound("maars_impact_dmg");
		wait(0.05);
	}
}

/////////////////////////////////////////////////
//////******* BIG MOMENT SEQUENCES ********/////
///////////////////////////////////////////////

aud_ignore_slowmo()
{
	SoundSetTimeScaleFactor( "announcer", 0 );
	SoundSetTimeScaleFactor( "mission", 0 );
	SoundSetTimeScaleFactor( "norestrict2d", 0 );
	SoundSetTimeScaleFactor( "grondo2d", 0 );
}

aud_crashing_helicopter_flyin()
{
	aud_delay_play_2d_sound("intro_helicrash_lfe", 3.0, true);

	aud_delay_play_2d_sound("intro_helicrash_rattle_front", 5.00, true);

	aud_delay_play_2d_sound("intro_helicrash_turbine_rear", 5.50, true);

	aud_delay_play_2d_sound("intro_helicrash_engine", 7.726, true);

	aud_delay_play_2d_sound("intro_helicrash_transient", 9.175, true);

	aud_delay_play_2d_sound("intro_helicrash_explo_front", 9.225, true);

	aud_delay_play_2d_sound("intro_helicrash_crack_front", 9.521, true);

	aud_delay_play_2d_sound("intro_helicrash_imp_front", 10.75, true);

}

aud_crashing_helicopter_impact()
{
	AZM_start_zone("intro_heli_crash", 0.05);
	mus_stop();

	aud_delay_play_2d_sound("intro_helicrash_fall_impact", 0.987, true);

	aud_delay_play_2d_sound("intro_helicrash_drop_crack", 1.717, true);

	aud_delay_play_2d_sound("intro_helicrash_debris_front", 2.864, true);

	aud_delay_play_2d_sound("intro_helicrash_tumble", 2.905, true);

	aud_delay_play_2d_sound("intro_helicrash_debris_rear", 4.141, true);

	aud_delay_play_2d_sound("intro_helicrash_demo_rear", 5.16, true);

	aud_delay_play_2d_sound("intro_helicrash_demo_front", 5.893, true);

	aud_delay_play_2d_sound("intro_helicrash_metal_groan", 8.571, true);

	aud_delay_play_2d_sound("intro_helicrash_heli_fall_front", 9.552, true);

	aud_delay_play_2d_sound("intro_helicrash_heli_slide_rear", 10.1, true);

	aud_delay_play_2d_sound("intro_helicrash_mtl_debris", 10.891, true);

	aud_delay_play_2d_sound("intro_helicrash_heli_fall_drop", 11.559, true);

	aud_delay_play_2d_sound("intro_helicrash_chunk_spin", 12.033, true);

	aud_delay_play_2d_sound("intro_helicrash_ground_impact", 12.935, true);

	aud_delay_play_2d_sound("intro_helicrash_tbone", 12.953, true);

	aud_delay_play_2d_sound("intro_helicrash_drop_imp_front", 13.026, true);
}

aud_intro_slide_sequence()
{
	MM_add_submix("intro_slide_sequence", 0.05);
	AZM_start_zone("intro_slide", 0.05);
	mus_stop();

	aud_delay_play_2d_sound("intro_slide_missile_impact", 0.05, true);

	aud_delay_play_2d_sound("intro_slide_initial_blast_01", 0.230, true);

	aud_delay_play_2d_sound("intro_slide_initial_crack_front", 0.346, true);

	aud_delay_play_2d_sound("intro_slide_initial_blast_03", 0.350, true);

	aud_delay_play_2d_sound("intro_slide_initial_blast_02", 0.350, true);

	aud_delay_play_2d_sound("intro_slide_drone_flyby", 1.383, true);

	aud_delay_play_2d_sound("intro_slide_drop_whoosh_short", 3.5, true);

	aud_delay_play_2d_sound("intro_slide_drop_imp_front", 3.763, true);

	aud_delay_play_2d_sound("intro_slide_drop_imp_blast", 3.883, true);

	aud_delay_play_2d_sound("intro_slide_drop_lfe", 3.9, true);

	aud_delay_play_2d_sound("intro_slide_drop_crack", 3.9, true);

	aud_delay_play_2d_sound("intro_slide_drop_slide_front", 5.201, true);

	aud_delay_play_2d_sound("intro_slide_drop_wind", 7.50, true);

	aud_delay_play_2d_sound("intro_slide_chunk_whoosh", 8.006, true);

	aud_delay_play_2d_sound("intro_slide_chunk_impact", 8.978, true);

	aud_delay_play_2d_sound("intro_slide_house_imp_01", 9.840, true);

	aud_delay_play_2d_sound("intro_slide_house_fall_front", 10.486, true);

	aud_delay_play_2d_sound("intro_slide_house_fall_impact", 11.465, true);

	aud_delay_play_2d_sound("intro_slide_house_fall_sweet", 12.101, true);

	aud_delay_play_2d_sound("intro_slide_tube_imp_02", 15.164, true);

	aud_delay_play_2d_sound("intro_slide_slab_imp", 15.630, true);

	aud_delay_play_2d_sound("intro_slide_slab_whoosh_rear", 17.565, true);

	aud_delay_play_2d_sound("intro_slide_slab_splash", 19.301, true);

	aud_delay_play_2d_sound("intro_slide_tube_splash", 19.564, true);
}

aud_intro_river_sequence( note, flagName )
{
	if (!IsDefined(level.aud.aud_intro_river_sequence))
	{
		level.aud.aud_intro_river_sequence = true;
		wait(0.05);
		aud_delay_play_2d_sound("intro_river_plyr_splash_punch", 0.05, true);

		aud_delay_play_2d_sound("intro_river_surface_01", 1.138, true);

		aud_delay_play_2d_sound("intro_river_rapids_01_front", 2.834, true);

		aud_delay_play_2d_sound("intro_river_heli_flyby", 2.962, true);

		aud_delay_play_2d_sound("intro_river_breath_01", 3.278, true);

		aud_delay_play_2d_sound("intro_river_hand_splash_01", 4.605, true);

		aud_delay_play_2d_sound("intro_river_hand_splash_02", 5.48, true);

		aud_delay_play_2d_sound("intro_river_hand_splash_03", 5.938, true);

		aud_delay_play_2d_sound("intro_river_uw_drown_front", 5.996, true);

		aud_delay_play_2d_sound("intro_river_uw_02_front", 6.228, true);

		aud_delay_play_2d_sound("intro_river_surface_02_front", 17.896, true);

		aud_delay_play_2d_sound("intro_river_breath_02", 17.998, true);

		aud_delay_play_2d_sound("intro_river_bank_rapids_rear", 18.29, true);

		aud_delay_play_2d_sound("intro_river_bank_hand_01", 19.365, true);

		aud_delay_play_2d_sound("intro_river_surface_02_tail_front", 19.453, true);

		aud_delay_play_2d_sound("intro_river_bank_hand_02", 19.940, true);

		aud_delay_play_2d_sound("intro_river_bank_slide_01", 22.124, true);

		aud_delay_play_2d_sound("intro_river_bank_hand_03", 22.749, true);

		aud_delay_play_2d_sound("intro_river_bank_slide_02", 24.04, true);

		aud_delay_play_2d_sound("intro_river_bank_hand_04", 25.168, true);

		thread aud_river_sequence_heli_fade_in();
	}
}

aud_river_sequence_heli_fade_in()
{
	wait(22);

	heli = aud_play_linked_sound("river_heli_pickup_2d", level.player, "loop", "aud_stop_exit_heli_lp");
	heli scalevolume(0);
	wait(0.05);
	heli scalevolume(0.9, 8);
	wait(11);
	heli scalevolume(0, 15);

	wait(18);
	level notify("aud_stop_exit_heli_lp");
}

aud_fireloops_start()
{
	//Temple
	DAMB_start_preset_at_point("fire_wood_med_tight", (-1484, -117, 695), "temple_01", 1000, 1.0);//right side of blownout wall
	DAMB_start_preset_at_point("fire_wood_med_tight", (-1564, -172, 701), "temple_02", 1000, 1.0);//middle of blownout wall
	DAMB_start_preset_at_point("fire_wood_med_tight", (-1666, -101, 699), "temple_03", 1000, 1.0);//left of blownout wall
	DAMB_start_preset_at_point("fire_wood_med_tight", (-1649, -80, 557), "temple_04", 1000, 1.0);//lower left of blownout wall

	//Courtyard
	DAMB_start_preset_at_point("fire_wood_med_tight", (-1539, -62, 501), "courtyard_01", 1000, 1.0);//broken wood support beam
	DAMB_start_preset_at_point("fire_wood_med", (-1691, 53, 453), "heli_01", 1000, 1.0);//heli cockpit
	thread play_loopsound_in_space("emt_fire_metal_med", (-1691, 53, 453));//heli cockpit metal
	DAMB_start_preset_at_point("fire_wood_med_tight", (-1597, 125, 466), "heli_02", 1000, 1.0);//heli blades
	thread play_loopsound_in_space("emt_fire_metal_med", (-1597, 125, 466));//heli blades metal
	DAMB_start_preset_at_point("fire_wood_med_tight", (-1605, 277, 404), "heli_03", 1000, 1.0);//heli rear woodbeams
	thread play_loopsound_in_space("emt_fire_metal_med", (-1491, 323, 328));//heli rear metal fin
	thread play_loopsound_in_space("emt_fire_metal_med", (-1672, 202, 367));//heli rear underbelly

	//Streets
	DAMB_start_preset_at_point("fire_wood_med_tight", (-749, 1985, 150), "woodtruck_01", 1000, 1.0);//wood truck front spill
	DAMB_start_preset_at_point("fire_wood_med", (-596, 2022, 198), "woodtruck_02", 1000, 1.0);//wood truck body

	DAMB_start_preset_at_point("fire_wood_med", (-2766, 2801, 201), "shoeshop_01", 1000, 1.0);//shoe shop second floor
	DAMB_start_preset_at_point("fire_wood_med_tight", (-2911, 2802, 36), "shoeshop_02", 1000, 1.0);//shoe shop first floor
	DAMB_start_preset_at_point("fire_wood_med", (-2935, 2797, 201), "tradeshop_01", 1000, 1.0);//trade shop second floor
	DAMB_start_preset_at_point("fire_wood_med_tight", (-2648, 2806, 42), "tradeshop_02", 1000, 1.0);//trade shop first floor left
	DAMB_start_preset_at_point("fire_wood_med_tight", (-2549, 2794, 19), "tradeshop_03", 1000, 1.0);//trade shop first floor right

	DAMB_start_preset_at_point("fire_wood_med_tight", (-3397, 2463, -22), "crates_01", 1000, 1.0);//wood crates mid street
	DAMB_start_preset_at_point("fire_wood_med", (-3498, 2380, 135), "crateshop_01", 1000, 1.0);//shop above crates

	//Lower street
	DAMB_start_preset_at_point("fire_wood_med_tight", (-4246, 3717, -154), "housewall_01", 1000, 1.0);//house rubble wall
	DAMB_start_preset_at_point("fire_wood_med", (-3858, 3591, 1), "apt_01", 1000, 1.0);//caved in apt
	DAMB_start_preset_at_point("fire_wood_med", (-4242, 3967, 93), "apt_02", 1000, 1.0);//upper left apt
	DAMB_start_preset_at_point("fire_wood_med", (-4033, 4479, -114), "apt_03", 1000, 1.0);//far apt
}

aud_start_final_fires()
{
	DAMB_start_preset_at_point("fire_wood_med", (-7493, 2992, -417), "finalhouse_01", 1000, 1.0);//final burning house on right
	DAMB_start_preset_at_point("fire_wood_med", (-7518, 2647, -587), "finalhouse_02", 1000, 1.0);//final burning house on left
}

aud_play_death_static()
{
	death_static = aud_play_linked_sound("maars_static_dmg_hi", level.player, "loop", "kill_dead_ugv_static_loop");
	wait(2);
	MM_clear_submix("intro_maars_death_mix", 4);
	wait(2);
	death_static scalevolume(0, 3);
	wait(3.05);
	level notify("kill_dead_ugv_static_loop");
}
