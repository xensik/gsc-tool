#include maps\_utility;
#include common_scripts\utility;
#include maps\_vehicle;
#include maps\_anim;
#include maps\_hud_util;
#include maps\_shg_common;
#include maps\_audio;

#include maps\intro_vo;
#include maps\intro_utility;


////////////////////////
//---- Friendlies ----//
////////////////////////
setup_price()
{
	level.price = self;
	self.name = "Price";
	self.animname = "price";
	self setup_hero_generic();
	self.npcId = "pri";
	level.heroes[0] = level.price;	
}

setup_soap()
{
	level.soap = self;
	self.name = "Soap";
	self.animname = "soap";
	self setup_hero_generic();
	
	level.heroes[1] = level.soap;	
	
	//self gun_remove();
	self set_battlechatter( false );
}

setup_nikolai()
{
	level.nikolai = self;
	self.name = "Nikolai";
	self.animname = "nikolai";
	self setup_hero_generic();
	self.voice = "russian";
	self set_battlechatter( false );
	//self.countryid = "RU";
	level.heroes[2] = level.nikolai;	
}

setup_hero_generic()
{
	self thread magic_bullet_shield();
	//self thread uphill_run();
	self.awareness = 1;
	self.cqb_wide_poi_track = true;
	self lower_accuracy( .4 );
}

setup_friendly_spawner( name, func )
{
	ent_arr = getentarray( name, "script_noteworthy" );
	foreach(ent in ent_arr)
	{
		ent add_spawn_function( func );
	}
}

setup_friendlies( location )
{
	//level heroes
	level.heroes = [];
	
	setup_friendly_spawner( "price", ::setup_price );
	setup_friendly_spawner( "soap", ::setup_soap );
	setup_friendly_spawner( "nikolai", ::setup_nikolai );

	spawn_friendlies( location, "price" );
	//spawning soap differently because he is a drone
	soap_spawner = getent( "soap", "script_noteworthy" );
	soap_spawner spawn_ai( true );
	spawn_friendlies( location, "nikolai" );
}

///////////////////
//---- INTRO ----//
///////////////////

intro_shot_1()
{
	//scene setup
	SetUpPlayerForAnimations();
	level.player disableweapons();
	level.player disableoffhandweapons();
	
	intro_helicopter_landed_friendlies();
	
	wire1 = spawn_anim_model( "wire1", ( 0, 0, 0 ) );
	wire2 = spawn_anim_model( "wire2", ( 0, 0, 0 ) );
	
	
	anim_pos_wire1 = getstruct( "intro_shot01_wire1", "targetname" );
	anim_pos_wire2 = getstruct( "intro_shot01_wire2", "targetname" );
	
	static_wires = getent( "intro_shot01_wire1_static", "targetname" );
	static_wires hide();
	static_wires = getent( "intro_shot01_wire2_static", "targetname" );
	static_wires hide();
	
	
	anim_pos = getstruct( "intro_shot_1", "targetname" );
	heli = spawn_anim_model( "littlebird", ( 0, 0, 0 )  );
	heli.origin = anim_pos.origin;
	heli.angles = anim_pos.angles;
	heli.animname = "littlebird";
	heli setanimtree();
	heli hidepart("main_rotor_jnt");
	heli hidepart("tail_rotor_jnt");
	aud_send_msg("start_gurney_scene_heli", heli);
	
	level.player_rig = spawn_anim_model( "player_rig", ( 0, 0, 0 ) );
	level.player_rig.animname = "player_rig";
	level.player PlayerLinkToDelta( level.player_rig, "tag_player", 1, 25, 25, 10, 0 );
	  
	//set up gurney fx zones
	thread maps\intro_fx::enable_gurney_fxzones();
	//force on first fx zone
	exploder(7002);
	level.playerbody = spawn_anim_model( "player_body", ( 0, 0, 0 ) );
	level.playerbody.animname = "player_body";
	level.playerbody setanimtree();
	
	gurney = spawn_anim_model( "gurney", ( 0, 0, 0 ) );
	
	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.player_rig, 0 ];
	actors[3] = [ level.playerbody, 0 ];
	actors[4] = [ gurney, 0 ];

	thread maps\_introscreen::introscreen_generic_black_fade_in( 4.8, .01 );
	
	level.player thread soap_injured_audio();
	heli thread intro_helicopter_earthquake();
	
	wait 4.4;
	level.player shellshock( "intro_opening", 10 );//slow view during the fade up so we don't have to have the blood with it.
	thread maps\_introscreen::introscreen_generic_white_fade_in(0.5, 0.25, 0.5 );
	aud_send_msg("intro_white_fade_in");
	aud_send_msg("intro_shot_1_start");
	wait 0.6;
	
	//begin scene
	thread bloom_fadein();
	thread rotate_sun();
	thread intro_shot_1_dof();
	thread intro_sunflare();
	
	//time =  getanimlength( level.price getanim( "intro_opening_shot01" ) );
	time = 4.3;
	level.player delaythread(5, ::soap_injured_screenfx,(time), 1, .5, .3);

	flag_set( "intro_dialog_shot_1" );
	
	anim_pos_wire1 thread anim_single_solo( wire1, "intro_shot01_wires" );
	anim_pos_wire2 thread anim_single_solo( wire2, "intro_shot01_wires" );
	
	
	heli thread anim_single_solo( heli, "intro_opening_shot01" );
	blade_shadow = getent("blade_shadow", "targetname");
	playfxontag(getfx("intro_helicopter_blade_shadow"), heli, "main_rotor_jnt");
	heli anim_single_end_early( actors, "intro_opening_shot01", "tag_guy1" );
	level notify( "stop_player_injured_audio" );
	flag_set( "intro_stop_shake" );
	stopfxontag(getfx("intro_helicopter_blade_shadow"), heli, "main_rotor_jnt");
	heli delete();
	gurney delete();
	wire1 delete();
	wire2 delete();
}

intro_shot_2_prime()
{
	spawner = getent( "intro_shot_3_civ1", "targetname" );
	level.bystander1 = spawner spawn_ai( true );
	level.bystander1.animname = "bystander1";
	waittillframeend;
	spawner = getent( "intro_shot_3_civ2", "targetname" );
	level.bystander2 = spawner spawn_ai( true );
	level.bystander2.animname = "bystander2";
	waittillframeend;
	spawner = getent( "intro_shot_3_civ3", "targetname" );
	level.bystander3 = spawner spawn_ai( true );
	level.bystander3.animname = "bystander3";
	
	level.wire3 = spawn_anim_model( "wire3", ( 0, 0, 0 ) );
	
	anim_pos_wire3 = getstruct( "intro_shot02_wire3", "targetname" );
	anim_pos_wire3 thread anim_first_frame_solo( level.wire3, "intro_shot01_wires" );
	
	static_wires = getent( "intro_shot02_wire3_static", "targetname" );
	static_wires hide();
	
	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.player_rig, 0 ];
	actors[3] = [ level.playerbody, 0 ];
	
	bystanders = [];
	bystanders[0] = [ level.bystander1, 0 ];
	bystanders[1] = [ level.bystander2, 0 ];
	bystanders[2] = [ level.bystander3, 0 ];

	anim_pos = getstruct( "intro_shot_2", "targetname" );
	
	anim_pos thread intro_shot_anim_first_frame( actors, "intro_opening_shot02" );
	
	anim_pos_bystanders = getstruct( "intro_shot_2_bystanders", "targetname" );
	
	anim_pos_bystanders thread intro_shot_anim_first_frame( bystanders, "intro_opening_shot02" );
	
}

intro_shot_2()
{
	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.player_rig, 0 ];
	actors[3] = [ level.playerbody, 0 ];
	
	bystanders = [];
	bystanders[0] = [ level.bystander1, 0 ];
	bystanders[1] = [ level.bystander2, 0 ];
	bystanders[2] = [ level.bystander3, 0 ];

	anim_pos = getstruct( "intro_shot_2", "targetname" );
	
	flag_set( "intro_dialog_shot_2" );
	level.player thread soap_injured_audio();
	thread intro_fade_in_from_white();
	aud_send_msg("intro_shot_2_start");
	level.player shellshock( "intro_opening", 10 );
	pauseexploder(7002);
	
	time =  getanimlength( level.price getanim( "intro_opening_shot02" ) );
	level.player delaythread(0, ::soap_injured_screenfx,(time+.65), .5, .5, .7);	
	
	thread vision_set_fog_changes("intro_cinematics_2",0);
	thread intro_shot_2_dof();
	
	anim_pos_bystanders = getstruct( "intro_shot_2_bystanders", "targetname" );
	anim_pos_bystanders thread anim_single_end_early( bystanders, "intro_opening_shot02" );
	
	anim_pos_wire3 = getstruct( "intro_shot02_wire3", "targetname" );
	anim_pos_wire3 thread anim_single_solo( level.wire3, "intro_shot01_wires" );
	
	level.nikolai thread multiple_dialogue_queue( "intro_opening_shot02_nikolai_face" );
	level.price thread multiple_dialogue_queue( "intro_opening_shot02_price_face" );
	anim_pos anim_single_end_early( actors, "intro_opening_shot02" );
	level notify( "stop_player_injured_audio" );
	level.wire3 delete();
}


intro_shot_3_prime()
{
	spawner = getent( "intro_shot_3_civ1", "targetname" );
	spawner.count = 1;
	level.bystander4 = spawner spawn_ai( true );
	level.bystander4.animname = "bystander4";
	
	spawner = getent( "intro_shot_3_civ2", "targetname" );
	spawner.count = 1;
	level.bystander5 = spawner spawn_ai( true );
	level.bystander5.animname = "bystander5";

	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.player_rig, 0 ];
	actors[3] = [ level.bystander1, 0 ];
	actors[4] = [ level.bystander2, 0 ];
	actors[5] = [ level.bystander3, 0 ];
	actors[6] = [ level.bystander4, 0 ];
	actors[7] = [ level.bystander5, 0 ];
	actors[8] = [ level.playerbody, 0 ];

	anim_pos = getstruct( "anim_intro_shot_3", "targetname" );

	anim_pos intro_shot_anim_first_frame( actors, "intro_opening_shot03" );
}

intro_shot_3()
{
	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.player_rig, 0 ];
	actors[3] = [ level.bystander1, 0 ];
	actors[4] = [ level.bystander2, 0 ];
	actors[5] = [ level.bystander3, 0 ];
	actors[6] = [ level.bystander4, 0 ];
	actors[7] = [ level.bystander5, 0 ];
	actors[8] = [ level.playerbody, 0 ];

	anim_pos = getstruct( "anim_intro_shot_3", "targetname" );
	
	flag_set( "intro_dialog_shot_3" );
	level.player thread soap_injured_audio();
	thread intro_fade_in_from_white();
	aud_send_msg("intro_shot_3_start");
	level.player shellshock( "intro_opening", 10 );
	
	time =  getanimlength( level.price getanim( "intro_opening_shot03" ) );
	level.player delaythread(0, ::soap_injured_screenfx,(time+.65), .5, .5, 1);
	
	thread vision_set_fog_changes("Intro_cinematics_3",0);
	thread intro_shot_3_dof();

	anim_pos anim_single_end_early( actors, "intro_opening_shot03" );
	level notify( "stop_player_injured_audio" );
}

intro_shot_4_prime()
{	
	spawner = getent( "intro_shot_3_civ1", "targetname" );
	spawner.count = 1;
	level.bystander6 = spawner spawn_ai( true );
	level.bystander6.animname = "bystander6";
	
	spawner = getent( "intro_shot_3_civ2", "targetname" );
	spawner.count = 1;
	level.bystander7 = spawner spawn_ai( true );
	level.bystander7.animname = "bystander7";
	
	level.bystander2 delete();
	level.bystander3 delete();
	
	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.player_rig, 0 ];
	actors[3] = [ level.playerbody, 0 ];
	actors[4] = [ level.bystander1, 0 ];
	//actors[5] = [ level.bystander2, 0 ];
	//actors[6] = [ level.bystander3, 0 ];
	actors[5] = [ level.bystander4, 0 ];
	actors[6] = [ level.bystander5, 0 ];
	actors[7] = [ level.bystander6, 0 ];
	actors[8] = [ level.bystander7, 0 ];

	anim_pos = getstruct( "anim_intro_room", "targetname" );
	anim_pos intro_shot_anim_first_frame( actors, "intro_opening_shot04" );
}

intro_shot_4()
{
	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.player_rig, 0 ];
	actors[3] = [ level.playerbody, 0 ];
	actors[4] = [ level.bystander1, 0 ];
	//actors[5] = [ level.bystander2, 0 ];
	//actors[6] = [ level.bystander3, 0 ];
	actors[5] = [ level.bystander4, 0 ];
	actors[6] = [ level.bystander5, 0 ];
	actors[7] = [ level.bystander6, 0 ];
	actors[8] = [ level.bystander7, 0 ];

	anim_pos = getstruct( "anim_intro_room", "targetname" );

	flag_set( "intro_dialog_shot_4" );
	level.player thread soap_injured_audio();
	thread intro_fade_in_from_white();
	aud_send_msg("intro_shot_4_start");
	level.player shellshock( "intro_opening", 10 );
	
	time =  getanimlength( level.price getanim( "intro_opening_shot04" ) );
	level.player delaythread(0, ::soap_injured_screenfx,(time-.5), .5, .5, 1);
	level.player delaythread(0, ::play_fullscreen_blood_bottom,(time-.5), .5, .5, 1);
	
	thread vision_set_fog_changes("Intro_cinematics_4",0);
	thread intro_shot_4_dof();
	
	
	level.nikolai thread multiple_dialogue_queue( "intro_opening_shot04_face" );
	level.price thread multiple_dialogue_queue( "intro_opening_shot04_price_face" );
	anim_pos anim_single_end_early( actors, "intro_opening_shot04" );
	level notify( "stop_player_injured_audio" );
	
	level.bystander1 delete();
	
	level.bystander4 delete();
	level.bystander5 delete();
	level.bystander6 delete();
	level.bystander7 delete();
}

intro_shot_5_prime()
{
	doctor_spawn();

	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.player_rig, 0 ];
	actors[3] = [ level.doctor, 0 ];
	actors[4] = [ level.playerbody, 0 ];

	anim_pos = getstruct( "anim_intro_room_before", "targetname" );
	anim_pos intro_shot_anim_first_frame( actors, "intro_opening_shot05" );
}

intro_shot_5()
{
	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.player_rig, 0 ];
	actors[3] = [ level.doctor, 0 ];
	actors[4] = [ level.playerbody, 0 ];

	anim_pos = getstruct( "anim_intro_room_before", "targetname" );
	
	flag_set( "intro_dialog_shot_5" );
	level.player thread soap_injured_audio();
	thread intro_fade_in_from_white();
	aud_send_msg("intro_shot_5_start");
/*
	//Comment this out to show blood test
	time =  getanimlength( level.price getanim( "intro_opening_shot05" ) );
	level.player delaythread(0, ::soap_injured_screenfx,(time), 1, 1);	
*/
	
	thread vision_set_fog_changes("Intro_cinematics_5",0);
	thread intro_shot_5_dof();
	thread intro_shot_5_bloody_fadeout();
		
	//play full screen blood effect test with various blood types
	time =  getanimlength( level.price getanim( "intro_opening_shot05" ) );
	level.player delaythread(0, ::play_fullscreen_blood,(time), .5, .5, 1);
	level.player delaythread(0, ::play_fullscreen_blood_bottom,(time), .5, .5, 1);
	level.player delaythread(0, ::play_fullscreen_blood_splatter_alt,(time), .5, .5, 1);
		
	level.player shellshock( "intro_injured", time );
			
	//delaythread( 3.5, ::intro_fade_out_to_white, level.price );
	anim_pos anim_single_end_early( actors, "intro_opening_shot05" );
	level notify( "stop_player_injured_audio" );
	level.playerbody delete();
}

intro_shot_5_bloody_fadeout()
{
	wait(2);
	thread vision_set_fog_changes("Intro_cinematics_bloody",1);
	wait(2);
	setblur(10,2);
}

intro_shot_6()
{
	// move light 1
	spot_cinema = GetEnt( "spot_cinema", "targetname" );
	origin_cinema_light = GetStruct( "origin_cinema_light_01", "targetname" );
	spot_cinema.origin = origin_cinema_light.origin;
	
	light_target = GetStruct( spot_cinema.target, "targetname" );
	
	origin_to_target = light_target.origin - spot_cinema.origin;
	origin_to_target = VectorNormalize( origin_to_target );
	spot_cinema.angles = VectorToAngles( origin_to_target );
	
	yuri_spawner = getent( "yuri", "script_noteworthy" );
	yuri = yuri_spawner spawn_ai( true );
	yuri.animname = "yuri";
	
	level.mi28_crash = spawn_anim_model( "mi28", ( 0, 0, 0 ) );
	level.nikolai gun_recall();
	
	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.player_rig, 0 ];
	actors[3] = [ level.doctor, 0 ];
	actors[4] = [ level.mi28_crash, 0 ];
	actors[5] = [ yuri, 0 ];

	anim_pos = getstruct( "intro_shot_6", "targetname" );
	anim_pos intro_shot_anim_first_frame( actors, "intro_opening_shot06" );
	
	time =  getanimlength( level.price getanim( "intro_opening_shot06" ) );
	delaythread((time - 2.05),::soap_blink_screenfx);
	
	level.player thread soap_injured_audio();
	flag_set( "intro_dialog_shot_6" );
	thread intro_fade_in_from_white();
	thread intro_shot_6_ambient_battle();
	anim_pos anim_single_end_early( actors, "intro_opening_shot06" );
	level notify( "stop_player_injured_audio" );
	
	yuri delete();
}

intro_shot_6_ambient_battle()
{
	mi28_1 = attack_helicopter( "intro_mi28_1" );
	mi28_1 SetMaxPitchRoll( 30, 60 );
	wait 1;
	mi28_2 = attack_helicopter( "intro_mi28_2" );
	mi28_2 SetMaxPitchRoll( 30, 60 );
	wait 4;
	mi28_3 = attack_helicopter( "intro_mi28_3" );
	mi28_3 SetMaxPitchRoll( 30, 60 );
}

intro_shot_7()
{
	// move light 2
	spot_cinema = GetEnt( "spot_cinema", "targetname" );
	origin_cinema_light = GetStruct( "origin_cinema_light", "targetname" );
	spot_cinema.origin = origin_cinema_light.origin;
	
	light_target = GetStruct( spot_cinema.target, "targetname" );
	
	origin_to_target = light_target.origin - spot_cinema.origin;
	origin_to_target = VectorNormalize( origin_to_target );
	spot_cinema.angles = VectorToAngles( origin_to_target );
	
	level.gurney = spawn_anim_model( "gurney", ( 0, 0, 0 ) );
	level.cart = spawn_anim_model( "surgery_cart", ( 0, 0, 0 ) );
	level.mi28_crash = spawn_anim_model( "mi28", ( 0, 0, 0 ) );
	level.forceps = spawn_anim_model( "forceps", ( 0, 0, 0 ) );
	level.gauze = spawn_anim_model( "gauze", ( 0, 0, 0 ) );
	
	level.price gun_recall();
	level.nikolai gun_recall();
	
	soap_spawner = getent( "soap", "script_noteworthy" );
	soap_spawner spawn_ai( true );
	
	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.player_rig, 0 ];
	actors[3] = [ level.doctor, 0 ];
	actors[4] = [ level.mi28_crash, 0 ];
	actors[5] = [ level.gurney, 0 ];
	actors[6] = [ level.soap, 0 ];
	actors[7] = [ level.forceps, 0 ];
	actors[8] = [ level.gauze, 0 ];

	anim_pos = getstruct( "anim_intro_room_before", "targetname" );
	anim_pos anim_first_frame_solo( level.cart, "intro_opening_shot08" );
	
	//play soap blood fx
	thread maps\intro_fx::play_soap_blood_fx();
	anim_pos intro_shot_anim_first_frame( actors, "intro_opening_shot07" );
	exploder("intro_godray");
	
	flag_wait( "intro_transition_dialog_end" );
	black_overlay = get_black_overlay( true );
	black_overlay thread intro_fade_in_from_black( 3, 1 );
	aud_send_msg("intro_soap_temple_start");
	
	thread vision_set_fog_changes("Intro_cinematics_7",0);
	thread intro_shot_7_dof();
	
	flag_set( "intro_dialog_shot_7" );
	thread intro_shot_7_helicopter_flyin();
	aud_send_msg("intro_shot_7");
	level.player delaycall( 4.75, ::playrumbleonentity, "damage_heavy" );//rumble when soap grabs player.
	level.nikolai thread multiple_dialogue_queue( "intro_opening_shot07_face" );
	anim_pos anim_single_end_early( actors, "intro_opening_shot07" );

}

intro_shot_8()
{
	beam = spawn_anim_model( "intro_ceiling_woodbeam_01", ( 0, 0, 0 ) );
	ceiling = spawn_anim_model( "intro_ceiling_damage_med_01", ( 0, 0, 0 ) );
	playfxontag(getfx("fire_mi_28"), level.mi28_crash, "tag_fire");
	fireorg = spawn_tag_origin();
	fireorg linkto(beam, "tag_origin", (-20,0,-20), (0,0,0));
	playfxontag(getfx("fire_line_sm_cheap"), fireorg, "tag_origin");
	
	actors = [];
	actors[0] = [ level.price, 0 ];
	actors[1] = [ level.nikolai, 0 ];
	actors[2] = [ level.doctor, 0 ];
	actors[3] = [ level.mi28_crash, 0 ];
	actors[4] = [ level.gurney, 0 ];
	actors[5] = [ level.soap, 0 ];
	actors[6] = [ level.cart, 0 ];
	actors[7] = [ level.player_rig, 0 ];
	actors[8] = [ level.forceps, 0 ];
	actors[9] = [ level.gauze, 0 ];
	actors[10] = [ beam, 0 ];
	actors[11] = [ ceiling, 0 ];


	anim_pos = getstruct( "anim_intro_room", "targetname" );
	flag_set( "intro_dialog_shot_8" );
	anim_pos intro_shot_anim_first_frame( actors, "intro_opening_shot08" );
	
	flag_set( "intro_complete" );

	aud_send_msg("intro_shot_8");

	thread intro_shot_8_dof();
	thread intro_shot_8_blur();
	
	//anim_pos thread anim_single_end_early( [ level.player_rig, "intro_opening_shot08" );
	thread intro_setup_player_for_gameplay();
	thread intro_enable_playerhud();
	

	level.nikolai thread multiple_dialogue_queue( "intro_opening_shot08_face" );
	
	delaythread( 14, ::flag_set, "intro_dialog_shot_8_complete" );
	anim_pos anim_single_end_early( actors, "intro_opening_shot08" );
	
	thread intro_setup_idles();
	thread intro_setup_price();
	//thread intro_setup_player_for_gameplay();
	//thread intro_enable_playerhud();
	stopfxontag(getfx("fire_mi_28"), level.mi28_crash, "tag_fire");
	stopfxontag(getfx("fire_line_sm"), fireorg, "tag_origin");
	fireorg delete();
	level.mi28_crash delete();
}

intro_shot_7_helicopter_flyin()
{
	wait 6.5;
	spawn_vehicle_from_targetname_and_drive( "intro_shot7_mi28_1" );
	
}

intro_shot4_open_doors()
{
	door_left = getent( "intro_shot4_door_left", "targetname" );
	door_left.angles = door_left.angles + ( 0, 90, 0 );
	
	door_right = getent( "intro_shot4_door_right", "targetname" );
	door_right.angles = door_right.angles - ( 0, 90, 0 );
}

intro_helicopter_earthquake()
{
	playrumblelooponposition( "mig_rumble", self.origin );
	while( !flag( "intro_stop_shake" ) )
	{
		earthquake( .15, .05, self.origin, 1024 );
		wait .05;
	}
	stopallrumbles( );
}

intro_shot_anim_first_frame( array, animation, tag )
{
	actors = [];
	foreach( actor in array )
	{
		actors[ actors.size ] = actor[ 0 ];
	}
	self anim_first_frame( actors, animation, tag );
}

doctor_spawn()
{
	doc_spawn = getent( "intro_room_doctor", "targetname" );
	level.doctor = doc_spawn spawn_ai( true );
	level.doctor.ignoreall = true;
	//level.doctor gun_remove();
	level.doctor.animname = "doctor";
	level.doctor deletable_magic_bullet_shield();
}

soap_injured_screenfx(time, fadein, fadeout, max_alpha)
{
	//adjust timing
	time-=1;

	//self shellshock( "intro_opening", time );
	
	//self thread play_undulating_blur();
	
/*
	//had to comment out the dof as it was overriding the dof for the shot.	Setting custom dof on each shot.
	//set dof
	start = level.dofDefault;	

	dof_intro = [];
	dof_intro[ "nearStart" ] =9;
	dof_intro[ "nearEnd" ] = 23;
	dof_intro[ "nearBlur" ] = 4;
	dof_intro[ "farStart" ] = 128;
	dof_intro[ "farEnd" ] = 256;
	dof_intro[ "farBlur" ] = 1.8;	
	
	blend_dof( start, dof_intro, .2 );
*/
		
	self thread play_fullscreen_blood(time, fadein, fadeout, max_alpha);

	wait(time);
	level notify("msg_fx_screenfx_end");
/*
	setblur(0,0.1);
	blend_dof( dof_intro, start, .1 );
*/	
}

bloom_fadein()
{
		setblur(10,0);
		thread vision_set_fog_changes("Intro_cinematics_gurnee",0);
		wait(.5);
		setblur(0,2);
		thread vision_set_fog_changes("Intro_cinematics",2);
}

rotate_sun()
{
	setsaveddvar("sm_sunsamplesizenear",.1);
	target_sun_dir = anglestoforward((-23, 34, 0));
	setsundirection(target_sun_dir);
	
	setSunLight( 2.175, 1.575, 1.5 );	
	
	//setsaveddvar("r_specularcolorscale", .5);
	
	wait 12;
	
	//setsaveddvar("r_specularcolorscale", 2.5);
	
	resetsundirection();	
	resetSunLight();	
}

intro_sunflare()
{
	level waitframe();
	thread maps\_shg_fx::fx_spot_lens_flare_dir("lights_intro_sunflare",(-16, 78, 0),8000);
	wait(8.5);
	flag_set("fx_spot_flare_kill");
	flag_clear("fx_spot_flare_kill");
}

intro_shot_1_dof()
{
	start = level.dofDefault;
	
//fg blur values
	dof_intro_shot_1a = [];
	dof_intro_shot_1a[ "nearStart" ] = 10;
	dof_intro_shot_1a[ "nearEnd" ] = 500;
	dof_intro_shot_1a[ "nearBlur" ] = 5;
	dof_intro_shot_1a[ "farStart" ] = 1000;
	dof_intro_shot_1a[ "farEnd" ] = 4000;
	dof_intro_shot_1a[ "farBlur" ] = 4;
	
//bg blur values
	dof_intro_shot_1b = [];
	dof_intro_shot_1b[ "nearStart" ] = 1;
	dof_intro_shot_1b[ "nearEnd" ] = 10;
	dof_intro_shot_1b[ "nearBlur" ] = 4;
	dof_intro_shot_1b[ "farStart" ] = 180;
	dof_intro_shot_1b[ "farEnd" ] = 2000;
	dof_intro_shot_1b[ "farBlur" ] = 1.5;
	
	blend_dof( start, dof_intro_shot_1a, .1 );
  wait(3.5);
	blend_dof ( dof_intro_shot_1a, dof_intro_shot_1b, .7 );
	wait(5);
	blend_dof ( dof_intro_shot_1b, start, .5 );
}

intro_shot_2_dof()
{
	start = level.dofDefault;	

	dof_intro_shot_2 = [];
	dof_intro_shot_2[ "nearStart" ] = 5.0;
	dof_intro_shot_2[ "nearEnd" ] = 50;
	dof_intro_shot_2[ "nearBlur" ] = 6;
	dof_intro_shot_2[ "farStart" ] = 200;
	dof_intro_shot_2[ "farEnd" ] = 4500;
	dof_intro_shot_2[ "farBlur" ] = 6;
	
	blend_dof( start, dof_intro_shot_2, .1 );
  wait(5);
	blend_dof ( dof_intro_shot_2, start, .1 );
}

intro_shot_3_dof()
{
	start = level.dofDefault;	

	dof_intro_shot_3 = [];
	dof_intro_shot_3[ "nearStart" ] = 1.0;
	dof_intro_shot_3[ "nearEnd" ] = 120;
	dof_intro_shot_3[ "nearBlur" ] = 6;
	dof_intro_shot_3[ "farStart" ] = 180;
	dof_intro_shot_3[ "farEnd" ] = 1600;
	dof_intro_shot_3[ "farBlur" ] = 6;
	
	blend_dof( start, dof_intro_shot_3, .1 );
  wait(4);
	blend_dof ( dof_intro_shot_3, start, .1 );
}

intro_shot_4_dof()
{
	start = level.dofDefault;	

	dof_intro_shot_4a = [];
	dof_intro_shot_4a[ "nearStart" ] = 1.0;
	dof_intro_shot_4a[ "nearEnd" ] = 120;
	dof_intro_shot_4a[ "nearBlur" ] = 6;
	dof_intro_shot_4a[ "farStart" ] = 180;
	dof_intro_shot_4a[ "farEnd" ] = 1600;
	dof_intro_shot_4a[ "farBlur" ] = 6;
	
	dof_intro_shot_4b = [];
	dof_intro_shot_4b[ "nearStart" ] = 1.0;
	dof_intro_shot_4b[ "nearEnd" ] = 10;
	dof_intro_shot_4b[ "nearBlur" ] = 6;
	dof_intro_shot_4b[ "farStart" ] = 180;
	dof_intro_shot_4b[ "farEnd" ] = 800;
	dof_intro_shot_4b[ "farBlur" ] = 6;
	
	blend_dof( start, dof_intro_shot_4a, .1 );
	wait(5);
	blend_dof( dof_intro_shot_4a, dof_intro_shot_4b, .5 );
  wait(3);
	blend_dof ( dof_intro_shot_4b, start, .1 );
}

intro_shot_5_dof()
{
	start = level.dofDefault;	

	//near blur
	dof_intro_shot_5a = [];
	dof_intro_shot_5a[ "nearStart" ] = 1.0;
	dof_intro_shot_5a[ "nearEnd" ] = 120;
	dof_intro_shot_5a[ "nearBlur" ] = 6;
	dof_intro_shot_5a[ "farStart" ] = 180;
	dof_intro_shot_5a[ "farEnd" ] = 1600;
	dof_intro_shot_5a[ "farBlur" ] = 6;
	
	//far blur
	dof_intro_shot_5b = [];
	dof_intro_shot_5b[ "nearStart" ] = 0;
	dof_intro_shot_5b[ "nearEnd" ] = 8;
	dof_intro_shot_5b[ "nearBlur" ] = 4;
	dof_intro_shot_5b[ "farStart" ] = 10;
	dof_intro_shot_5b[ "farEnd" ] = 85;
	dof_intro_shot_5b[ "farBlur" ] = 4;
	
	blend_dof( start, dof_intro_shot_5a, .1 );
	wait(3);
	blend_dof( dof_intro_shot_5a, dof_intro_shot_5b, 1 );
  wait(5);
	blend_dof ( dof_intro_shot_5b, start, .1 );
}

intro_shot_7_dof()
{
	level.dofStart = level.dofDefault;
	start = level.dofDefault;	

	//initial dof
	dof_intro_shot_7a = [];
	dof_intro_shot_7a[ "nearStart" ] = 10;
	dof_intro_shot_7a[ "nearEnd" ] = 20;
	dof_intro_shot_7a[ "nearBlur" ] = 6;
	dof_intro_shot_7a[ "farStart" ] = 70;
	dof_intro_shot_7a[ "farEnd" ] = 800;
	dof_intro_shot_7a[ "farBlur" ] = 6;
	
	//focus on soap
	dof_intro_shot_7b = [];
	dof_intro_shot_7b[ "nearStart" ] = 1;
	dof_intro_shot_7b[ "nearEnd" ] = 9;
	dof_intro_shot_7b[ "nearBlur" ] = 6;
	dof_intro_shot_7b[ "farStart" ] = 10;
	dof_intro_shot_7b[ "farEnd" ] = 80;
	dof_intro_shot_7b[ "farBlur" ] = 6;
	
	//focus chopper crash
	dof_intro_shot_7c = [];
	dof_intro_shot_7c[ "nearStart" ] = 20;
	dof_intro_shot_7c[ "nearEnd" ] = 60;
	dof_intro_shot_7c[ "nearBlur" ] = 6;
	dof_intro_shot_7c[ "farStart" ] = 1500;
	dof_intro_shot_7c[ "farEnd" ] = 8000;
	dof_intro_shot_7c[ "farBlur" ] = 6;
	
	//start of shot
	blend_dof( start, dof_intro_shot_7a, .1 );
  wait(1.5);
  //focus on soap
  blend_dof( dof_intro_shot_7a, dof_intro_shot_7b, 3.0 );
  wait(6.0);
  //rack to wall, prepare for choopper crash
	blend_dof ( dof_intro_shot_7b, dof_intro_shot_7c, 1.0 );
}

intro_shot_8_dof()
{ 
	start = level.dofDefault;	

	//initial dof
	dof_intro_shot_8a = [];
	dof_intro_shot_8a[ "nearStart" ] = 20;
	dof_intro_shot_8a[ "nearEnd" ] = 60;
	dof_intro_shot_8a[ "nearBlur" ] = 6;
	dof_intro_shot_8a[ "farStart" ] = 1500;
	dof_intro_shot_8a[ "farEnd" ] = 8000;
	dof_intro_shot_8a[ "farBlur" ] = 6;
	
	//fg in focus chopper out of focus
	dof_intro_shot_8b = [];
	dof_intro_shot_8b[ "nearStart" ] = 1.4;
	dof_intro_shot_8b[ "nearEnd" ] = 20;
	dof_intro_shot_8b[ "nearBlur" ] = 6;
	dof_intro_shot_8b[ "farStart" ] = 20;
	dof_intro_shot_8b[ "farEnd" ] = 300;
	dof_intro_shot_8b[ "farBlur" ] = 2.2;
	
	//hands out of focus
	blend_dof( start, dof_intro_shot_8a, 0.1 );
	wait(4);
	//chopper slightly out of focus
	blend_dof( dof_intro_shot_8a, dof_intro_shot_8b, 1.5 );
	wait(3.5);
	//blend back to no dof
	blend_dof( dof_intro_shot_8b, level.dofStart, 1.5 );
}

intro_shot_8_blur()
{
	//explosion blur
	setblur(8,0);
	wait(1);
	setblur(0,2);
}

//full screen blood left and right
play_fullscreen_blood(time, fadein, fadeout, max_alpha)
{
	/*sides = [];
	sides[ "bottom" ] = true;
	sides[ "left" ] = true;
	sides[ "right" ] = true;


	foreach ( type, _ in sides )
	{
		material = "fullscreen_bloodsplat_" + type;
		hud = self thread maps\_gameskill::display_screen_effect_nofade( "bloodsplat", type, material, undefined, RandomFloatRange( 0.45, 0.56 ), time );
	}*/
	
	overlay_left = NewClientHudElem( self );
	overlay_left.x = 0;
	overlay_left.y = 0;

	overlay_left SetShader( "fullscreen_bloodsplat_left", 640, 480 );
	
	overlay_left.splatter = true;
	overlay_left.alignX = "left";
	overlay_left.alignY = "top";
	overlay_left.sort = 1;
	overlay_left.foreground = 0;
	overlay_left.horzAlign = "fullscreen";
	overlay_left.vertAlign = "fullscreen";
	overlay_left.alpha = 0;
	
	overlay_right = NewClientHudElem( self );
	overlay_right.x = 0;
	overlay_right.y = 0;

	overlay_right SetShader( "fullscreen_bloodsplat_right", 640, 480 );
	
	overlay_right.splatter = true;
	overlay_right.alignX = "left";
	overlay_right.alignY = "top";
	overlay_right.sort = 1;
	overlay_right.foreground = 0;
	overlay_right.horzAlign = "fullscreen";
	overlay_right.vertAlign = "fullscreen";
	overlay_right.alpha = 0;
	
	if (!IsDefined(fadein))
		fadein = 1;
	if (!IsDefined(fadeout))
		fadeout = 1;
	if (!IsDefined(max_alpha))
		max_alpha = 1;
	
	//fade up
	step_time = 0.05;
	
	if ( fadein > 0 )
	{
		current_alpha = 0;
		increment_alpha = max_alpha / (fadein/step_time); 
		AssertEx( increment_alpha > 0, "alpha not increasing; infinite loop" );
		while ( current_alpha < max_alpha )
		{
			overlay_left.alpha = current_alpha;
			overlay_right.alpha = current_alpha;
			current_alpha = current_alpha + increment_alpha;
			wait step_time;
	}
	}
	
	overlay_left.alpha = max_alpha;
	overlay_right.alpha = max_alpha;
	
	wait(time - (fadein + fadeout));

	//fade down
	if ( fadeout > 0 )
	{
		current_alpha = max_alpha;
		decrement_alpha = max_alpha / (fadeout/step_time);
		AssertEx( decrement_alpha > 0, "alpha not decreasing; infinite loop" );
		while ( current_alpha > 0 )
		{
			overlay_left.alpha = current_alpha;
			overlay_right.alpha = current_alpha;
			current_alpha = current_alpha - decrement_alpha;
			wait step_time;
	}
	}
	
	overlay_left.alpha = 0;
	overlay_right.alpha = 0;
	
	overlay_left destroy();
	overlay_right destroy();
}

//full screen blood bottom
play_fullscreen_blood_bottom(time, fadein, fadeout, max_alpha)
{
	overlay = NewClientHudElem( self );
	overlay.x = 0;
	overlay.y = 0;

	overlay SetShader( "fullscreen_bloodsplat_bottom", 640, 480 );
	
	overlay.splatter = true;
	overlay.alignX = "left";
	overlay.alignY = "top";
	overlay.sort = 1;
	overlay.foreground = 0;
	overlay.horzAlign = "fullscreen";
	overlay.vertAlign = "fullscreen";
	overlay.alpha = 0;
	
	fade_counter = 0;
	if (!IsDefined(fadein))
		fadein = 1;
	if (!IsDefined(fadeout))
		fadeout = 1;
	if (!IsDefined(max_alpha))
		max_alpha = 1;
	
	//fade up
	step_time = 0.05;
	
	if ( fadein > 0 )
	{
		current_alpha = 0;
		increment_alpha = max_alpha / (fadein/step_time); 
		AssertEx( increment_alpha > 0, "alpha not increasing; infinite loop" );
		while ( current_alpha < max_alpha )
		{
			overlay.alpha = current_alpha;
			current_alpha = current_alpha + increment_alpha;
			wait step_time;
	}
	}
	
	overlay.alpha = max_alpha;
	
	wait(time - (fadein + fadeout));

	//fade down
	if ( fadeout > 0 )
	{
		current_alpha = max_alpha;
		decrement_alpha = max_alpha / (fadeout/step_time);
		AssertEx( decrement_alpha > 0, "alpha not decreasing; infinite loop" );
		while ( current_alpha > 0 )
		{
			overlay.alpha = current_alpha;
			current_alpha = current_alpha - decrement_alpha;
			wait step_time;
		}
	}
	
	overlay.alpha = 0;
	
	overlay destroy();
}

//full screen blood splatter_alt moderate damage
play_fullscreen_blood_splatter_alt(time, fadein, fadeout, max_alpha)
{
	overlay = NewClientHudElem( self );
	overlay.x = 0;
	overlay.y = 0;

	overlay SetShader( "splatter_alt_sp", 640, 480 );
	
	overlay.splatter = true;
	overlay.alignX = "left";
	overlay.alignY = "top";
	overlay.sort = 1;
	overlay.foreground = 0;
	overlay.horzAlign = "fullscreen";
	overlay.vertAlign = "fullscreen";
	overlay.alpha = 0;
	
	fade_counter = 0;
	if (!IsDefined(fadein))
		fadein = 1;
	if (!IsDefined(fadeout))
		fadeout = 1;
	if (!IsDefined(max_alpha))
		max_alpha = 1;
	
	//fade up
	step_time = 0.05;
	
	if ( fadein > 0 )
	{
		current_alpha = 0;
		increment_alpha = max_alpha / (fadein/step_time); 
		AssertEx( increment_alpha > 0, "alpha not increasing; infinite loop" );
		while ( current_alpha < max_alpha )
		{
			overlay.alpha = current_alpha;
			current_alpha = current_alpha + increment_alpha;
			wait step_time;
	}
	}
	
	overlay.alpha = max_alpha;
	
	wait(time - (fadein + fadeout));

	//fade down
	if ( fadeout > 0 )
	{
		current_alpha = max_alpha;
		decrement_alpha = max_alpha / (fadeout/step_time);
		AssertEx( decrement_alpha > 0, "alpha not decreasing; infinite loop" );
		while ( current_alpha > 0 )
		{
			overlay.alpha = current_alpha;
			current_alpha = current_alpha - decrement_alpha;
			wait step_time;
		}
	}
	
	overlay.alpha = 0;
	
	overlay destroy();
}

intro_shot_7_screen_dirt_hit(time, fadein, fadeout)
{
	overlay = NewClientHudElem( self );
	overlay.x = 0;
	overlay.y = 0;

	overlay SetShader( "fullscreen_dirt_right", 640, 480 );
	
	overlay.splatter = true;
	overlay.alignX = "left";
	overlay.alignY = "top";
	overlay.sort = 1;
	overlay.foreground = 0;
	overlay.horzAlign = "fullscreen";
	overlay.vertAlign = "fullscreen";
	overlay.alpha = 0;
	
	//fade up
	fade_counter = 0;
	if (!IsDefined(fadein))
		fadein = 1;
	if (!IsDefined(fadeout))
		fadeout = 1;
	
	while(fade_counter < fadein)
	{
		overlay.alpha += 0.05;	
		fade_counter += 0.05;
		wait 0.05;
	}
	overlay.alpha = 1;
	
	wait(time - (fadein + fadeout));

	//fade down
	fade_counter = 0;
	while(fade_counter < fadeout)
	{
		overlay.alpha -= 0.05;
		fade_counter += 0.05;
		wait 0.05;
	}
	overlay.alpha = 0;
	
	overlay destroy();
}

play_undulating_blur()
{
	while(true)
	{
		level endon("msg_fx_screenfx_end");
/*
		wait(randomFloat(2.5) + 2.5);
		time = randomFloat(0.4) + 0.35;
		blur = randomFloat(10) + 1.5;
		SetBlur(blur, time);
		time = randomFloat(1) + 0.35;
		wait(time);
		time = randomFloat(0.4) + 0.2;
		SetBlur(0, time);	
*/
		setblur((randomfloatrange (8, 10)), .2);
		wait(randomfloatrange (.2, .4));
		setblur(.5, .3);
		wait(randomfloatrange (1.8, 2.5));
	}
	setblur(0,.6);
}	

soap_blink_screenfx()
{
	introblack = NewHudElem();
	introblack.x = 0;
	introblack.y = 0;
	introblack.horzAlign = "fullscreen";
	introblack.vertAlign = "fullscreen";
	introblack.foreground = true;
	introblack SetShader( "black", 640, 480 );

//blink 1
	introblack.alpha = 0;
	introblack FadeOverTime( 0.4 );
	introblack.alpha = 0.75;
	wait( 0.225 );
	introblack FadeOverTime( 0.4 );
	introblack.alpha = 0;
	wait 0.6;
	
//blink 2
	introblack.alpha = 0;
	introblack FadeOverTime( 0.75 );
	introblack.alpha = 1.0;
	wait( 0.6 );
	introblack FadeOverTime( 1.1 );
	introblack.alpha = 0;
	
	introblack destroy();

}

soap_injured_audio()
{
	aud_send_msg("start_gurney_heartbeat");
	level waittill("stop_player_injured_audio");
	aud_send_msg("stop_gurney_heartbeat");
	
//	self thread player_heartbeat();
//	self thread player_breathing();
}

//player_heartbeat()
//{
//	level endon( "stop_player_injured_audio" );
//	while ( true )
//	{
//		self play_sound_on_entity( "breathing_heartbeat" );
//		wait .75;
//	}
//}
//
//player_breathing()
//{
//	level endon( "stop_player_injured_audio" );
//	while ( true )
//	{
//		wait RandomFloatRange( .5, 2 );
//		self play_sound_on_entity( "breathing_hurt_start" );
//	}
//}

intro_fade_out_to_black( guy )
{
	black_overlay = get_black_overlay();
	black_overlay thread exp_fade_overlay ( 1, .25 );
}

intro_fade_out_to_black_slow( guy )
{
	black_overlay = get_black_overlay( false );
	black_overlay thread exp_fade_overlay ( 1, 1 );
}

intro_fade_in_from_black( setFadeTime, waitonblack )
{
	if( isdefined( waitonblack ) ) 
		wait waitonblack;
		
	if( isdefined( setFadeTime ) )
	{
		fadetime = setFadeTime;
	}
	else
	{
		fadetime = .25;	
	}
	black_overlay = get_black_overlay();
	black_overlay thread exp_fade_overlay ( 0, fadetime );
}

intro_fade_out_to_white( guy )
{
	aud_send_msg("intro_fade_out_to_white");
	white_overlay = get_white_overlay();
	white_overlay thread exp_fade_overlay ( 1, .25 );
}

intro_fade_out_to_white_end( guy )
{
	white_overlay = get_white_overlay();
	white_overlay thread exp_fade_overlay ( 1, 3 );
}

intro_fade_in_from_white()
{
	aud_send_msg("intro_fade_in_from_white");
	white_overlay = get_white_overlay();
	white_overlay thread exp_fade_overlay ( 0, .25 );
}

intro_fade_in_from_white_as_yuri()
{
	thread introscreen_generic_fade_out( "white", 1, 2, 0 );
}

intro_flash_to_white_crash( guy )
{
	//thread introscreen_generic_fade_out( "white", 1, .1, .1 );
}

intro_room_heli_crash_as_soap( guy )
{
	thread start_slowmo_crash();
	org = getstruct( "courtyard_intro_room_heli_explode_as_soap", "targetname" );
	//dirt_on_screen_from_position( org.origin);
	playfx( getfx( "slamraam_explosion" ) , org.origin );
	earthquake(.8, 3, org.origin, 1024);
	level.player playrumbleonentity( "artillery_rumble" );
	wait .5;
	thread end_slowmo_crash();
}

intro_room_heli_crash_as_yuri( guy )
{
	//thread start_slowmo_crash();
	
 
	org = getstruct( "courtyard_intro_room_heli_explode_as_soap", "targetname" );
	//dirt_on_screen_from_position( org.origin);
	
	//play fx
	exploder(21);
	
	//swap fx zones
	thread maps\intro_fx::enable_gameplay_fxzones();
	level.player playrumbleonentity( "heavy_3s" );
	
	//turn off lightbeams and soap mouth blood
	pauseExploder("intro_godray");
	stopfxontag(getfx("blood_cough"), level.soap, "J_Jaw");
			
	//play wall explode animation
	wallshards = getent("helicrash_wallshards", "script_noteworthy");
	wallshards.animname = "helicrash_wallshards";
  wallshards SetAnimTree();
	wallshards thread anim_single_solo(wallshards, "wallshards");
	
	//vision set change bright to dark to normal
	thread vision_set_fog_changes("Intro_heli_breach", 0);
	thread vision_set_fog_changes("intro_dark", 1);
	wait 7.75;
	thread vision_set_fog_changes("intro_bright", 1.25);
	wait 3;
	wallshards hide();
	thread vision_set_fog_changes("intro", 2);
	
	earthquake(.8, 3, org.origin, 1024);
	level.player playrumbleonentity( "artillery_rumble" );

	//delete wallshards when you go downstairs
	flag_wait("msg_fx_zone7_5");
	wallshards delete();
}

hide_wonky_wallshards(wallshards)
{
	wonky_shards = ["joint_79", "joint_70"];
	foreach(shard in wonky_shards)
	{
		wallshards hidepart(shard);
	}
}

start_slowmo_crash( )
{
	slomoLerpTime_in = 0.5; //0.5;
	
	slowmo_start();
	
	slowmo_setspeed_slow( 0.75 );
	slowmo_setlerptime_in( slomoLerpTime_in );
	slowmo_lerp_in();
}

end_slowmo_crash( )
{
	slomoLerpTime_out = 0.5;
	
	slowmo_setlerptime_out( slomoLerpTime_out );
	slowmo_lerp_out();
	slowmo_end();
}


intro_setup_player_for_gameplay()
{
	level.player_rig waittill( "anim_ended" );
	flag_set( "intro_room_heli_crash_complete" );
	
	level.player unlink();
	level.player_rig delete();
	
	//unlink_target = getstruct( "intro_unlink_player", "targetname" );
	//level.player lerp_player_view_to_position( unlink_target.origin, unlink_target.angles, .5 );
	
	setupplayerforgameplay();
	level.player enableweapons();
	level.player enableoffhandweapons();
	waittillframeend;
	autosave_by_name( "intro_after_no_control" );
}

intro_setup_idles()
{
	anim_pos = getstruct( "anim_intro_room", "targetname" );
	
	anim_pos thread play_loop_stoppable( [level.doctor, level.gauze, level.forceps ], "intro_work_on_soap", "intro_room_doctor_stop_idle" );
	anim_pos thread play_loop_solo_stoppable( level.nikolai, "intro_work_on_soap", "intro_room_nikolai_stop_idle" );
	anim_pos thread play_loop_solo_stoppable( level.soap, "intro_work_on_soap", "stop_wounded_on_table" );
	anim_pos thread anim_loop_solo( level.gurney, "intro_work_on_soap" );
}

intro_setup_price()
{
	level.price.ignoreall = false;
	level.price enable_ai_color();
}

intro_room_setup()
{
	//doctor
	doc_spawn = getent( "intro_room_doctor", "targetname" );
	level.doctor = doc_spawn spawn_ai( true );
	waittillframeend;
	level.doctor.ignoreall = true;
	//level.doctor gun_remove();
	level.doctor.animname = "doctor";
	
	// soap
	soap_spawner = getent( "soap", "script_noteworthy" );
	soap_spawner spawn_ai( true );
	
	// gurney
	level.gurney = spawn_anim_model( "gurney", ( 0, 0, 0 ) );
	level.forceps = spawn_anim_model( "forceps", ( 0, 0, 0 ) );
	level.gauze = spawn_anim_model( "gauze", ( 0, 0, 0 ) );
	
	thread intro_setup_idles();
}

intro_helicopter_landed_friendlies()
{
	location = "intro_helicopter_landed_friends";
	price_spawner = getentarray( "price", "script_noteworthy" );
	foreach( ent in price_spawner) 
	{
		if( isSpawner( ent ) )
		{
			ent.count = 1;
		}
	}
	
	nikolai_spawner = getentarray( "nikolai", "script_noteworthy" );
	foreach( ent in nikolai_spawner) 
	{
		if( isSpawner( ent ) )
		{
			ent.count = 1;
		}
	}
	
	spawn_friendlies(location,"price");
	spawn_friendlies(location,"nikolai");
	level.price disable_ai_color();
	level.price.ignoreall = true;
	level.price gun_remove();
	
	level.nikolai disable_ai_color();
	level.nikolai.ignoreall = true;
	level.nikolai gun_remove();
}

intro_text()
{
	lines = [];
	// Mission Title
	lines[ lines.size ] = &"INTRO_INTROSCREEN_LINE1";
	// day/time
	lines[ "date" ]     = &"INTRO_INTROSCREEN_LINE2";
	//Name
	lines[ lines.size ] = &"INTRO_INTROSCREEN_LINE3";
	//Faction
	lines[ lines.size ] = &"INTRO_INTROSCREEN_LINE4";
	//Location
	lines[ lines.size ] = &"INTRO_INTROSCREEN_LINE5";

	wait 2;
	maps\_introscreen::introscreen_feed_lines( lines );
}

intro_enable_playerhud()
{
	level.player_rig waittill( "anim_ended" );
	
	setsavedDvar( "g_friendlyNameDist", 15000 );
	SetSavedDvar( "compass", "1" );
	SetSavedDvar( "ammoCounterHide", "0" );
	SetSavedDvar( "actionSlotsHide", "0" );
	
	//level.player showhud();
}

intro_disable_playerhud()
{
	setsavedDvar( "g_friendlyNameDist", 0 );
	SetSavedDvar( "compass", "0" );
	SetSavedDvar( "ammoCounterHide", "1" );
	SetSavedDvar( "actionSlotsHide", "1" );
	//level.player hidehud();
}


///////////////////////
//---- COURTYARD ----//
///////////////////////

courtyard_player_on_balcony()
{
	flag_wait( "courtyard_player_touching_balcony" );
	flag_set( "courtyard_player_on_balcony" );
}

courtyard_save()
{
	wait 1;
	wait_until_player_looking_at_courtyard();
	autosave_by_name( "intro_courtyard_save" );
}
	
courtyard_price()
{
	flag_wait( "obj_take_position_on_balcony" );
	
	//level.price.noreload = true;
	price_to_balcony = GetNode( "courtyard_price_to_balcony", "targetname" );
	level.price setGoalnode( price_to_balcony );
	waittillframeend;
	level.price.goalradius = 10;
}

courtyard_player_invulnerable()
{
	level.player enableinvulnerability();
	flag_wait( "courtyard_mi28_3_done_firing" );
	level.player disableinvulnerability();
}

courtyard_threat_groups()
{
	createthreatbiasgroup( "player_group" );
	createthreatbiasgroup( "courtyard_enemies" );
	
	level.player setthreatbiasgroup( "player_group" );
	level.price setthreatbiasgroup( "player_group" );
	level.nikolai setthreatbiasgroup( "player_group" );
	setignoremegroup( "player_group", "courtyard_enemies" );	
}

courtyard_combat()
{	
	spawners = getentarray( "courtyard_breach_spawn", "targetname" );
	array_spawn_function( spawners, ::enable_cqbwalk );
	array_spawn_function( spawners, ::remove_grenades );
	array_spawn_function( spawners, ::disable_long_death );
	
	flag_wait( "courtyard_start_scene" );
	
	wait( 5 );
	flag_set( "courtyard_start_breach");
	courtyard_animated_breach();
	
	spawners = getentarray( "courtyard_spawn_1", "targetname" );
	//array_spawn_function( spawners, ::enable_cqbwalk );
	array_spawn_function( spawners, ::remove_grenades );
	array_spawn_function( spawners, ::disable_long_death );

	spawners2 = getentarray( "courtyard_spawn_2", "targetname" );
	//array_spawn_function( spawners2, ::enable_cqbwalk );
	array_spawn_function( spawners2, ::remove_grenades );
	array_spawn_function( spawners2, ::disable_long_death );

	thread maps\_spawner::flood_spawner_scripted( spawners );
	thread courtyard_spawn_cleanup();
	thread courtyard_friendly_cleanup();
	
	wait( 4 );
	spawners = getentarray( "courtyard_friendly_spawn_2", "targetname" );
	friendlies = array_spawn( spawners );
	array_thread( friendlies, ::enable_cqbwalk );
	array_thread( friendlies, ::remove_grenades );
	
	wait( 2 );
	thread maps\_spawner::flood_spawner_scripted( spawners2 );
	
	wait( 7 );
	
	flag_set( "courtyard_combat_done" );
	
	maps\_spawner::killspawner(101);	

	thread courtyard_dialog_combat_done();
}

courtyard_animated_breach()
{
	anim_pos = getstruct( "courtyard_animated_breach_org", "targetname" );
	breachers = [];
	level.courtyard_breachers_dead = 0;
	spawners = getentarray( "courtyard_breach_spawn", "targetname" );
	i=1;
	foreach( spawner in spawners )
	{
		breacher = spawner spawn_ai( true );
		breacher.animname = "breacher"+i;
		breacher.allowdeath = true;
		breacher thread courtyard_breacher_monitor();
		breachers[ breachers.size ] = [ breacher, 0 ];
		i++;
	}

	anim_pos thread anim_single_end_early( breachers, "courtyard_breach" );
	while( level.courtyard_breachers_dead < 4 )
	{
		wait .1;
	}
}

courtyard_breacher_monitor()
{
	self waittill( "death" );
	level.courtyard_breachers_dead++;
}


courtyard_friendly_intro()
{
	array_spawn_function_targetname( "courtyard_friendly_spawn_1", ::courtyard_friendly_setup );
	
	flag_wait( "courtyard_start_scene" );
	
	wait( 1 );
	spawners = getentarray( "courtyard_friendly_spawn_1", "targetname" );
	thread maps\_spawner::flood_spawner_scripted( spawners );
}

courtyard_friendly_setup()
{
	self enable_cqbwalk();
	self thread remove_grenades();
}

courtyard_spawn_cleanup()
{
	flag_wait( "courtyard_spawn_cleanup" );
	maps\_spawner::killspawner(101);
	wait( .1 );
	enemies = get_living_ai_array( "courtyard_spawn_1", "script_noteworthy" );
	ai_delete_when_out_of_sight( enemies, 256 );
	enemies2 = get_living_ai_array( "courtyard_spawn_2", "script_noteworthy" );
	ai_delete_when_out_of_sight( enemies2, 256 );	
}

courtyard_friendly_cleanup()
{
	flag_wait( "regroup_dialog_intro_complete" );
	friends1 = get_living_ai_array( "courtyard_friendly_spawn_1", "script_noteworthy" );
	if( IsDefined( friends1 ) )
		ai_delete_when_out_of_sight( friends1, 256 );
	
	friends2 = get_living_ai_array( "courtyard_friendly_spawn_2", "script_noteworthy" );
	if( IsDefined( friends2 ) )
		ai_delete_when_out_of_sight( friends2, 256 );
	
	friends3 = get_living_ai_array( "escort_friendly_spawn_1", "script_noteworthy" );
	if( IsDefined( friends3 ) )
		ai_delete_when_out_of_sight( friends3, 256 );

	friends4 = get_living_ai_array( "courtyard_cover_pulldown1", "script_noteworthy" );
	ai_delete_when_out_of_sight( friends4, 256 );
	
	friends5 = get_living_ai_array( "courtyard_cover_pulldown2", "script_noteworthy" );
	ai_delete_when_out_of_sight( friends5, 256 );

}

wait_until_player_looking_at_courtyard()
{
	// wait until player is looking at courtyard
	breach_door_position = GetStruct( "breach_door_position", "targetname" );
	
	while ( !player_looking_at( breach_door_position.origin ) )
	{
		wait 0.1;
	}
}

//Enemy breach into courtyard
courtyard_breach()
{
	breach_fx = GetEntArray( "breach_fx", "targetname" );
	array_thread( breach_fx, ::breach_fx_setup, "courtyard" );
	
	thread breach_door( "courtyard_breach_door_left", "courtyard_breach_door_left_destroyed", "courtyard_left_breach_door_collision" );
	thread breach_door( "courtyard_breach_door_right", "courtyard_breach_door_right_destroyed", "courtyard_right_breach_door_collision" );

	
	flag_wait( "courtyard_start_breach" );
	exploder( "breach_courtyard" );
	aud_send_msg("courtyard_start_breach");
	
	flag_set( "courtyard_doors_breach" );
	thread courtyard_dialog_breached();
}

remove_grenades()
{
	self.grenadeammo = 0;
}

courtyard_helicopters()
{
	enemies = getentArray( "courtyard_helicopter_enemies", "script_noteworthy" );
	array_spawn_function( enemies, ::courtyard_helicopter_enemy_setup );
	
	thread courtyard_attack_helicopters();
	
	wait( 7 );
	spawner = GetEnt( "courtyard_mi17_1", "targetname" );
	mi17_1 = spawner spawn_vehicle_and_gopath();
	aud_send_msg("courtyard_heli_Mi17_01", mi17_1);
	mi17_1 SetMaxPitchRoll( 20, 30 );
	mi17_1 thread courtyard_helicopter_shoot_down();
	mi17_1 thread helicopter_dmg_hint();
	
	spawners = GetEntArray( "courtyard_mi17_drone1", "targetname" );
	array_thread( spawners, ::courtyard_mi17_drone );
	
	wait( 6 );
	spawners = GetEntArray( "courtyard_mi17_drone3", "targetname" );
	array_thread( spawners, ::courtyard_mi17_drone );
	
	//mi17 that rpg guys shoot down
	spawner = GetEnt( "courtyard_mi17_drone3_kill", "targetname" );
	mi17_drone3_kill = spawner spawn_vehicle_and_gopath();
	aud_send_msg("courtyard_mi17_drone3_kill", mi17_drone3_kill);
	mi17_drone3_kill SetMaxPitchRoll( 20, 30 );
	mi17_drone3_kill thread helicopter_dmg_hint();

	rpg_attackers = array_spawn_targetname( "courtyard_rpg_attacker" );
	array_thread(rpg_attackers, ::courtyard_rpg_attacker, mi17_drone3_kill);

}

courtyard_mi17_drone( )
{
	heli = self spawn_vehicle_and_gopath();
	heli SetMaxPitchRoll( 30, 60 );
	heli thread helicopter_dmg_hint();
}

courtyard_attack_helicopters()
{
	mi28_1 = attack_helicopter( "courtyard_mi28_1" );
	mi28_1 SetMaxPitchRoll( 20, 30 );
	mi28_1 thread helicopter_dmg_hint();
	aud_send_msg("attack_heli_mi28_1", mi28_1);
	
	mi28_5 = attack_helicopter( "courtyard_mi28_5" );
	mi28_5 SetMaxPitchRoll( 30, 60 );
	mi28_5 thread helicopter_dmg_hint();
	aud_send_msg("attack_heli_mi28_5", mi28_5);
	
	wait( 3 );
	
	mi28_6 = attack_helicopter( "courtyard_mi28_6" );
	mi28_6 SetMaxPitchRoll( 30, 60 );
	mi28_6 thread helicopter_dmg_hint();
	aud_send_msg("attack_heli_mi28_6", mi28_6);
	
	wait( 2 );

	mi28_2 = attack_helicopter( "courtyard_mi28_2" );
	mi28_2 thread courtyard_mi28_2_roll();
	mi28_2 thread helicopter_fire_turret( "courtyard_mi28_2_2", 25 );
	mi28_2 thread helicopter_dmg_hint();
	aud_send_msg("attack_heli_mi28_2", mi28_2);
	
	wait( 4 );
	thread maps\intro_fx::courtyard_heli_impacts();

	wait( 15 );
	
	mi28_3 = attack_helicopter( "courtyard_mi28_3" );
	mi28_3 SetMaxPitchRoll( 20, 50 );
	mi28_3 thread helicopter_fire_turret( "courtyard_mi28_3_2", 25 );
	mi28_3 thread helicopter_dmg_hint();
	aud_send_msg("attack_heli_mi28_3", mi28_3);
	
	wait( 1 );
	
	mi28_7 = attack_helicopter( "courtyard_mi28_7", true, 10 );
	mi28_7 SetMaxPitchRoll( 20, 60 );
	mi28_7 thread helicopter_fire_turret( "courtyard_mi28_7_2", 25 );
	mi28_7 thread helicopter_dmg_hint();
	aud_send_msg("attack_heli_mi28_7", mi28_7);
	
	mi28_8 = attack_helicopter( "courtyard_mi28_8", true, 10 );
	mi28_8 SetMaxPitchRoll( 20, 60 );
	mi28_8 thread helicopter_fire_turret( "courtyard_mi28_8_2", 25 );
	mi28_8 thread helicopter_dmg_hint();
	aud_send_msg("attack_heli_mi28_8", mi28_8);
		
	wait(20);
	
	thread courtyard_attack_helicopter_second_pass();
}

attack_helicopter( targetname, guns, shots )
{
	heli_spawn = getent( targetname, "targetname" );
	heli = heli_spawn spawn_vehicle_and_gopath();
	heli.enableRocketDeath = true;
	if( isDefined( guns ) )
	{
		heli thread helicopter_fire_turret( targetname, shots );
	}else
	{
		heli thread helicopter_fire_missiles( targetname );
	}
	
	return heli;
}

helicopter_fire_missiles( targetname )
{
	self endon( "death" );
	flag_wait( targetname + "_fire" );
	target = GetStruct( targetname + "_target", "targetname" );
	self heli_fire_missiles( target, 3, 0.25, "cobra_seeker" );
}

helicopter_fire_turret( targetname, shots )
{
	if( !isdefined( shots ) )
		shots = 75;
		
	self endon( "death" );
	flag_wait( targetname + "_fire" );
	target = GetStruct( targetname + "_target", "targetname" );
	self heli_fire_turret( target, shots, randomfloatrange( .05, .15 ) );
}

courtyard_rpg_attacker( rocket_target )
{
	self endon( "death" );
    self.old_weapon = self.weapon;
    self forceUseWeapon( "rpg" , "primary" );

    self waittill("goal");
    self set_ignoreSuppression( true );
    self setstablemissile( true );
    self setentitytarget( rocket_target );
    self.a.rockets = 1;
    self.maxSightDistSqrd = 8192 * 8192;
    self.noreload = true;
    
    while(isAlive(rocket_target))
    {
    	wait(0.1);
    	//waiting for the guy to fire
    	if( self.a.rockets < 1 )
    		break;
    }
    self ClearEntityTarget(); 
    self forceUseWeapon( self.old_weapon , "primary" );
    self.script_forcegoal =0;
}

courtyard_rpg_attacker_scripted( rocket_target )
{
	spawner = getent( "courtyard_rpg_attacker_scripted", "targetname" );
	attacker = spawner spawn_ai();
	attacker.animname = "generic";
	attacker thread magic_bullet_shield();
	attacker.awareness = 1;
	attacker disable_awareness();
	attacker place_weapon_on( "stinger_speedy", "back" );
	attacker disable_ai_color();
	
	anim_ent = getstruct( "courtyard_rpg_attacker_scripted_anim_pos", "targetname" );
	anim_ent anim_reach_solo( attacker, "fire_rocket" );
	attacker place_weapon_on( "stinger_speedy", "chest" );
	anim_ent thread anim_single_solo( attacker, "fire_rocket" );
	
	attacker waittillmatch( "single anim", "fire rocket" );
	org_hand = attacker gettagorigin( "TAG_INHAND" );
	rocket_target godoff();
	stinger = magicbullet( "stinger_speedy", org_hand, rocket_target.origin );
	aud_data = [org_hand, stinger];
	aud_send_msg("courtyard_magic_rpg_01", aud_data);
	stinger missile_setTargetEnt(rocket_target);
	attacker place_weapon_on( "stinger_speedy", "none" );
	attacker waittillmatch( "single anim", "end" );
	attacker thread enable_ai_color();
	attacker thread stop_magic_bullet_shield();
	attacker enable_awareness();
}

courtyard_mi28_2_roll()
{
	self SetMaxPitchRoll( 10, 60 );
	flag_wait( "courtyard_mi28_2_2_fire" );
	self SetMaxPitchRoll( 35, 60 );
}

courtyard_attack_helicopter3()
{
	target_ent3_spawner = getent("courtyard_mi28_3", "targetname");
	target_ent3 = target_ent3_spawner spawn_vehicle_and_gopath();
	target_ent3.enableRocketDeath = true;
		
	target_ent3 thread courtyard_helicopter3_fire_missiles();
}

courtyard_attack_helicopter_second_pass()
{
	flag_set( "courtyard_attack_helicopter_second_pass" );
	//flag_wait( "courtyard_price_back_inside" );
	target_ent4_spawner = getent("courtyard_mi28_4", "targetname");
	target_ent4 = target_ent4_spawner spawn_vehicle_and_gopath();
	target_ent4.enableRocketDeath = true;
	target_ent4 SetMaxPitchRoll( 20, 40 );
	target_ent4 thread courtyard_helicopter4_fire_missiles();
	target_ent4 thread courtyard_helicopter4_kill();
	target_ent4 thread helicopter_dmg_hint();
}

courtyard_helicopter_shoot_down()
{
	flag_wait( "courtyard_helicopter_1_takedown" );
	wait( 2 );
	thread courtyard_rpg_attacker_scripted( self );
	
	wait( 10 );
	flag_set( "courtyard_helicopter_enemies_delete" );
}

courtyard_helicopter4_kill()
{
	flag_wait( "courtyard_mi28_4_takedown" );
	src = GetStruct( "courtyard_mi28_4_take_down_missile_src_1", "targetname" );
	self godoff();
	self fire_fake_missile( src, undefined, "stinger_speedy" );
	aud_send_msg("courtyard_helicopter4_kill", self);
}

courtyard_helicopter_enemy_setup()
{
	self endon( "death" );
	self.ignoreall = true;
	
	flag_wait( "courtyard_helicopter_enemies_delete" );
	self delete();
}

courtyard_helicopter3_fire_missiles()
{
	self endon( "death" );
	flag_wait( "courtyard_mi28_3_fire" );
	target = GetStruct( "courtyard_helicopter_slamraam_target", "targetname" );
	self heli_fire_missiles( target, 3, 0.25, "cobra_seeker" );
	wait(1);
	target = GetStruct( "courtyard_helicopter_hotel_target", "targetname" );
	self heli_fire_missiles( target, 3, 0.25, "cobra_seeker" );
	flag_set( "courtyard_mi28_3_done_firing" );
}

courtyard_helicopter4_fire_missiles()
{
	self endon( "death" );
	flag_wait( "courtyard_mi28_4_fire" );
	target = GetStruct( "courtyard_helicopter_4_target_1", "targetname" );
	self heli_fire_missiles( target, 3, 0.25, "cobra_seeker" );
}

heli_fire_missiles( eTarget, iShots, delay, customMissiles )
{
	self endon( "death" );
	self endon( "heli_players_dead" );
	if ( IsDefined( self.defaultWeapon ) )
		defaultWeapon = self.defaultWeapon;
	else
		defaultWeapon = "turret_attackheli";
	weaponName = "missile_attackheli";
	if ( isdefined( customMissiles ) )
		weaponName = customMissiles;
	loseTargetDelay  = undefined;
	tags = [];
	self SetVehWeapon( defaultWeapon );
	if ( !isdefined( iShots ) )
		iShots = 1;
	if ( !isdefined( delay ) )
		delay = 1;
	
	created_ent = false;
	
	//if the target is a struct, need to spawn a dummy ent to fire at
	if ( !isdefined( eTarget.classname ) )
	{
		dummyTarget = Spawn( "script_origin", eTarget.origin );
		dummyTarget.ref_count = 0;
		level thread cleanup_target( self, dummyTarget );
		dummyTarget.targetname = eTarget.targetname;
		dummyTarget.origin = eTarget.origin;
		eTarget = dummyTarget;
		eTarget thread heli_target_monitor_missile_hit();
		created_ent = true;
	}

	loseTargetDelay  = 0.5;
	tags[ 0 ] = "tag_store_L_2_a";
	tags[ 1 ] = "tag_store_R_2_a";
	tags[ 2 ] = "tag_store_L_2_b";
	tags[ 3 ] = "tag_store_R_2_b";
	tags[ 4 ] = "tag_store_L_2_c";
	tags[ 5 ] = "tag_store_R_2_c";
	tags[ 6 ] = "tag_store_L_2_d";
	tags[ 7 ] = "tag_store_R_2_d";

	nextMissileTag = -1;

	for ( i = 0 ; i < iShots ; i++ )
	{
		nextMissileTag++;
		if ( nextMissileTag >= tags.size )
			nextMissileTag = 0;

		self SetVehWeapon( weaponName );
		self.firingMissiles = true;
		eMissile = self FireWeapon( tags[ nextMissileTag ], eTarget );
		aud_send_msg("heli_fire_missile", eMissile);
		if ( created_ent )
		{
			level thread manage_target_references( eTarget, eMissile );
		}
		eMissile thread heli_missile_explode_when_close( eTarget );
		eMissile thread vehicle_scripts\_attack_heli::missile_earthquake();
		if ( i < iShots - 1 )
			wait delay;
	}
	
	self.firingMissiles = false;
	self SetVehWeapon( defaultWeapon );
	
	self notify( "done_firing_weapons" );
}

cleanup_target( attacker, target_ent )
{
	// clean up spawned target ent after all references are done with it
	target_ent endon( "death" );
	
	attacker waittill_any( "death", "heli_players_dead", "done_firing_weapons" );
	wait 0.05;
	while ( IsDefined( target_ent.ref_count ) && target_ent.ref_count > 0 )
	{
		target_ent waittill( "ref_count_updated" );
	}
	
	target_ent Delete();
}

manage_target_references( target_ent, missile )
{
	target_ent.ref_count++;
	missile waittill( "death" );
	target_ent.ref_count--;
	target_ent notify( "ref_count_updated" );
}

heli_fire_turret( eTarget, iShots, delay )
{
	delay = 0.11;
	self endon( "death" );
	self endon( "heli_players_dead" );
	
	created_ent = false;
	
	if ( IsDefined( self.defaultWeapon ) )
		defaultWeapon = self.defaultWeapon;
	else
		defaultWeapon = "mi28_turret_intro";
	weaponName = "mi28_turret_intro";

	loseTargetDelay  = undefined;
	tags = [];
	self SetVehWeapon( defaultWeapon );
	if ( !isdefined( iShots ) )
		iShots = 1;
	if ( !isdefined( delay ) )
		delay = 1;
	
	entTarget = etarget;
	dist_increment = undefined;
	forward = undefined;
	
	//if the target is a struct, need to spawn a dummy ent to fire at
	if ( !isdefined( eTarget.classname ) )
	{
		dummyTarget = Spawn( "script_origin", eTarget.origin );
		level thread cleanup_target( self, dummyTarget );
		created_ent = true;
		dummyTarget.targetname = eTarget.targetname;
		dummyTarget.origin = eTarget.origin;
		entTarget = dummyTarget;
	}
	
	if( isdefined( etarget.target ) )
	{
		if( !IsDefined( eTarget.classname ) )
		{
			etarget2 = GetStruct( etarget.target, "targetname" );
			dist = distance( etarget.origin, etarget2.origin );
			angles = vectortoangles( etarget2.origin - etarget.origin );
			forward = anglestoforward( angles );
			dist_increment = dist/ishots;
		}
	}
	
	self setturrettargetent( entTarget );
	wait .5;// wait for the turret to get on target
	for( i = 0; i < iShots; i++ )
	{
		if ( !IsDefined( entTarget ) )
		{
			break;
		}
		
		self FireWeapon( "tag_flash", entTarget );//tag_barrel  // tag_turret
		
		wait( delay );
		if( isdefined( dist_increment ) && isdefined( forward ) )
		{
			enttarget.origin = entTarget.origin + forward * dist_increment;
		}
	}
	
	self SetVehWeapon( defaultWeapon );
	
	self notify( "done_firing_weapons" );
}

heli_missile_explode_when_close( target, notify_on_death )
{
	self endon( "death" );
	target endon( "death" );
	AssertEx( IsDefined( target ), "Heli missile target not defined." );
	
	explode_dist = 512;
	
	if ( IsDefined( notify_on_death ) && notify_on_death )
	{
		self thread notify_missile_hit_on_death( target );
	}
	
	while( 1 )
	{
		dist = distance( self.origin, target.origin );
		if( dist < explode_dist )
		{
			target notify( "missile_hit" );
			self notify( "missile_hit" );
		}
		wait( .05 );
	}
}

notify_missile_hit_on_death( target )
{
	target endon( "missile_hit" );
	self waittill( "death" );
	target notify( "missile_hit" );
}

heli_target_monitor_missile_hit()
{
	self waittill( "missile_hit" );
	
	if( isdefined( self.targetname ) )
	{
		switch( self.targetname )
		{
			case "courtyard_mi28_1_target":
				//playfx( getfx( "smoke_large" ) , self.origin );
				playfx( getfx( "slamraam_explosion" ) , self.origin );
				thread maps\intro_fx::courtyard_heli_smoke();
			break;
			case "courtyard_mi28_2_target":
				//playfx( getfx( "smoke_large" ) , self.origin );
			break;
			case "courtyard_mi28_3_target":
				thread courtyard_helicopter_slamraam_target_hit();
			break;
			case "courtyard_helicopter_4_target_1":
				//playfx( getfx( "smoke_large" ) , self.origin );
			break;
			case "courtyard_mi28_5_target":
				//playfx( getfx( "smoke_large" ) , self.origin );
			break;
			case "courtyard_mi28_6_target":
				//playfx( getfx( "smoke_large" ) , self.origin );
			break;
			case "regroup_gate_uav_target":
				thread regroup_uav_gate_fly_by_target_hit();
			break;
			case "javelin_end_point":
				//thread building_slide_building_hit();
			break;
			case "regroup_uav_street_target1":
				thread regroup_building_destruct_a_destroy();
			break;
			case "regroup_uav_street_target2":
				//thread regroup_building_destruct_b_destroy();
			break;
			case "regroup_uav_rural_target1":
				//thread regroup_building_destruct_c_destroy();
			break;
			case "regroup_uav_rural_target2":
				//thread regroup_building_destruct_d_destroy();
			break;
			case "building_slide_run_target2":
				thread building_slide_destroy_tree();
				earthquake( .2, .5, level.player.origin, 1280  );
				playrumbleonposition( "artillery_rumble", self.origin );
			break;
			case "building_slide_run_target4":
				thread building_slide_building_destruct();
				//playfx( getfx( "smoke_large" ) , self.origin );
				playfx( getfx( "intro_sliderun_buildingexp" ) , self.origin );
				thread maps\intro_fx::maars_do_hit_contrast();
				earthquake( .2, .5, level.player.origin, 1280  );
				playrumbleonposition( "artillery_rumble", self.origin );
			break;
			case "building_slide_run_target1":
			case "building_slide_run_target3":
			case "building_slide_run_target5":
			case "building_slide_run_target6":
			case "building_slide_run_target7":
			case "building_slide_run_target8":
				earthquake( .5, .5, level.player.origin, 2048  );
				playrumbleonposition( "artillery_rumble", self.origin );
			break;
			
			default:
			break;
		}
	}
}

courtyard_helicopter_slamraam_target_hit()
{
	//hint( "SLAMRAAM HIT", 3);
	//level.slamraam notify( "death");
	//playfx( getfx( "slamraam_explosion" ) , self.origin );
	earthquake(.8, 3, self.origin, 1024);
	level.player playrumbleonentity( "artillery_rumble" );
	
	thread maps\intro_fx::courtyard_heli_explode();
	//playfx( getfx( "smoke_large" ) , self.origin );
	
	wait( 2 );
	flag_set( "courtyard_mi28_3_done_firing" );
}

courtyard_heli_drone_kill()
{
	flag_wait( "courtyard_helicopter_drone_takedown" );
	
	wait( 5 );
	src = GetStruct( "courtyard_helicopter_takedown_missile_src", "targetname" );
	self fire_fake_missile( src, undefined, "stinger_speedy" );
}

courtyard_drones()
{
	array_spawn_function_targetname( "courtyard_drone", ::drone_runner_combat_think, "courtyard_kill_drones", true );
	
	flag_wait( "courtyard_start_breach" );
	level notify( "courtyard_kill_drones" );
}

courtyard_cover_pull_down()
{
	anim_pos = getstruct( "courtyard_cover_pull_down", "targetname" );
	object = spawn_anim_model( "cover_object", ( 0, 0, 0 ) );
	anim_pos anim_first_frame_solo( object, "cover_object_pull_down" );
	
	col = getent( "courtyard_cover_pulldown_col", "targetname" );
	//col connectpaths();
	col notsolid();
	
	flag_wait( "courtyard_player_touching_balcony" );
	
	spawner = getent( "courtyard_cover_pulldown1", "script_noteworthy" );
	guy1 = spawner spawn_ai( true );
	guy1.animname = "object_puller1";
	guy1 thread magic_bullet_shield();
	guy1 thread courtyard_cover_pull_down_guy1( object );
	
	wait 2;
	spawner = getent( "courtyard_cover_pulldown2", "script_noteworthy" );
	guy2 = spawner spawn_ai( true );
	guy2.animname = "object_puller2";
	guy2 thread magic_bullet_shield();

	guy2 thread courtyard_cover_pull_down_guy2();
	
	wait( 3 );
	//col disconnectpaths();
	col solid();
	
}

courtyard_cover_pull_down_guy1( object )
{
	self endon( "death" );
	
	anim_pos = getstruct( "courtyard_cover_pull_down", "targetname" );
	actors = make_array( self, object );
	anim_pos thread anim_single( actors, "cover_object_pull_down" );
	
	self.a.pose = "crouch";
	node1 = getnode( "courtyard_cover_pulldown1_node", "targetname" );
	self setgoalnode( node1 );
	self stop_magic_bullet_shield();
}

courtyard_cover_pull_down_guy2()
{
	self endon( "death" );
	anim_pos = getstruct( "courtyard_cover_pull_down", "targetname" );
	
	
	//anim_pos anim_reach_solo( self, "cover_object_pull_down" );
	anim_pos thread anim_single_solo( self, "cover_object_pull_down" );
	
	self.a.pose = "crouch";
	node2 = getnode( "courtyard_cover_pulldown2_node", "targetname" );
	self setgoalnode( node2 );
	self stop_magic_bullet_shield();
}


////////////////////
//---- ESCORT ----//
////////////////////

escort_doc_down_mi28()
{
	mi28 = thread attack_helicopter( "escort_doc_down_mi28", true, 5 );
	mi28 SetMaxPitchRoll( 30, 60 );
	mi28 thread helicopter_dmg_hint();
	aud_send_msg("escort_doc_down_mi28", mi28);
	flag_wait( "escort_doc_down_mi28_fire" );
	
	wait 3;
	
	target2 = getstruct( "escort_doc_down_mi28_2_target", "targetname" );
	
	aud_send_msg("mi28_doctor_killed_flyout", mi28);
	mi28 heli_fire_turret( target2, 75, .07  );	
}

escort_help_soap()
{
	//doctors dies
	
	thread escort_kill_doc();
	flag_wait( "escort_player_help_soap" );
	autosave_by_name( "intro_help_soap" );

	//player uses syringe
	use_trigger = getent( "escort_player_help_soap_use", "targetname" );
	use_trigger SetHintString( &"INTRO_HELP_SOAP" );
	//use_trigger UseTriggerRequireLookAt();
	use_trigger waittill( "trigger" );
	use_trigger delete();
	
	level.player enableinvulnerability();
	
	//use_trigger trigger_off();
	thread maps\intro_fx::street_fires_vfx();
	
	//set up player rig
	setup_player_rig();
	
	flag_set( "escort_player_helping_soap" );
	
	// help soap
	thread escort_treat_soap();
	flag_wait( "escort_help_soap_complete" );
	
	//Enemies breach door.
	thread escort_help_soap_breach();
	
	flag_set( "obj_exit_hotel" );
}

escort_price_throw_smoke()
{
	org = getstruct( "escort_price_throw_smoke", "targetname" );
	self disable_awareness();
	
	self.oldgrenade = self.grenadeWeapon;
	self.grenadeWeapon = "smoke_grenade_intro";
	
	anim_node = GetNode( "courtyard_price_to_balcony", "targetname" );
	if( !anim_node check_anim_reached( level.price, "exposed_grenadeThrowB", undefined, undefined, 16 ) )
		anim_node anim_reach_solo( level.price, "exposed_grenadeThrowB" );
	
	anim_node thread anim_single_solo( level.price, "exposed_grenadeThrowB" );
	
	self waittillmatch( "single anim", "grenade_throw" );
	src = getstruct( "escort_price_throw_smoke_src", "targetname" );
	self magicgrenade( src.origin , org.origin, 2 );
	//self magicgrenade( self gettagorigin( "tag_weapon_right" ), org.origin, 2 );
	
	self waittillmatch( "single anim", "end" );
	self enable_awareness();
	self.grenadeWeapon = self.oldgrenade;
	//self.noreload = undefined;
	flag_set( "escort_smoke_out" );
}

setup_player_rig()
{
	maps\_shg_common::SetUpPlayerForAnimations();
	level.player DisableWeapons();
	level.player DisableWeaponSwitch();
	
	level.player_rig = spawn_anim_model( "player_rig", ( 0, 0, 0 ) );
	level.player_rig.animname = "player_rig";
}

escort_pick_up_soap()
{
	flag_set( "escort_start_nikolai_color" );
	
	level.nikolai waittill( "anim_ended" );

	//flag_wait( "escort_help_soap_breachers_dead" );
	level.soap notify( "stop_loop" );
	
	maps\intro_carry::override_carry_anim( "wounded_idle", "soap_lie_down_idle" );
	maps\intro_carry::override_carry_anim( "pickup_wounded", "pickup_soap" );
	maps\intro_carry::override_carry_anim( "pickup_carrier", "pickup_soap" );
	maps\intro_carry::override_carry_anim( "putdown_wounded", "putdown_soap_init" );
	maps\intro_carry::override_carry_anim( "putdown_carrier", "putdown_soap_init" );
	
	wounded_node = GetStruct( "anim_intro_room", "targetname" );
	level.soap thread maps\intro_carry::setWounded( wounded_node );
	level.nikolai thread maps\intro_carry::move_wounded_to_node_monitor( level.soap, wounded_node );
	level.nikolai thread maps\intro_carry::move_wounded_to_node_by_color();
	//level.nikolai thread maps\intro_carry::move_wounded_to_node( level.soap, wounded_node );
	flag_set( "intro_room_soap_to_wounded_idle" );
}

escort_kill_doc()
{
	anim_pos = GetStruct( "anim_intro_room", "targetname" );
	
	level.doctor notify( "intro_room_doctor_stop_idle" );
	level.nikolai notify( "intro_room_nikolai_stop_idle" );
	level.soap notify( "stop_wounded_on_table" );
	
	guys = [];
	guys[ 0 ] = [ level.doctor, 0 ];
	guys[ 1 ] = [ level.nikolai, 0 ];
	guys[ 2 ] = [ level.soap, 0 ];
	guys[ 3 ] = [ level.forceps, 0 ];
	guys[ 4 ] = [ level.gauze, 0 ];
	
	level.doctor delaythread( .1, ::escort_kill_doctor_fx );
	
	anim_pos thread anim_single_end_early( guys, "escort_doctor_dies" );
	level.doctor thread kill_on_anim_end();
	anim_pos waittill( "escort_doctor_dies" );
	
	anim_pos thread play_loop_solo_stoppable( level.nikolai, "escort_wait_for_player_idle", "escort_wait_stop_idle" );
	anim_pos thread play_loop_solo_stoppable( level.soap, "escort_wait_for_player_idle", "escort_wait_stop_idle" );
	
	
	//anim_pos thread anim_reach_solo( level.price, "escort_help_soap" );
	
	flag_set( "escort_player_help_soap" );
	
	flag_wait( "escort_player_starting_courtyard" );
	level.forceps delete();
	level.gauze delete();
}

escort_kill_doctor_fx()
{
	num = RandomIntRange( 1, 3 );
	self bodyshot( "headshot" + num, "tag_eye" );
	//wait( .5 );
	self animscripts\death::play_blood_pool();
}



kill_on_anim_end()
{
	self endon( "death" );
	self waittill( "anim_ended" );
	
	// kill drone
	self.allowDeath = true;
	self.noragdoll = true;
	self.skipdeathanim = true;
	self thread set_battlechatter( false );
	self kill();
}

escrot_treat_soap_spawn_syringe()
{
	level.syringe = spawn_anim_model( "syringe", ( 0, 0, 0 ) );
	level.syringe dontcastshadows();
	anim_pos = GetStruct( "anim_intro_room", "targetname" );
	
	anim_pos anim_first_frame_solo( level.syringe, "escort_help_soap" );
	
}

escort_treat_soap()
{
	// make sure price is still where he should be??  or play his anim separately...??
	
	level.player_rig Hide();
	level.player_rig dontcastshadows();
	anim_pos = GetStruct( "anim_intro_room", "targetname" );
	
	anim_pos anim_first_frame_solo( level.player_rig, "escort_help_soap" );
	level.player PlayerLinkToBlend( level.player_rig, "tag_player", 0.5, 0.2, 0.2 );
	wait 0.5;
	level.player PlayerLinkToDelta( level.player_rig, "tag_player", 1, 12, 5, 15, 0, true  );
	level.player_rig Show();
	
	level.nikolai notify( "escort_wait_stop_idle" );
	level.soap notify( "escort_wait_stop_idle" );
	
	guys = [];
	guys[ 0 ] = level.price;
	guys[ 1 ] = level.nikolai;
	guys[ 2 ] = level.soap;
	guys[ 3 ] = level.player_rig;
	guys[ 4 ] = level.syringe;
	
	anim_pos anim_single( guys, "escort_help_soap" );
	
	// start breaching for the other guys, player rig continues on
	flag_set( "escort_help_soap_complete" );
	anim_pos thread play_loop_solo_stoppable( level.soap, "soap_lie_down_idle", "stop_loop" );
}

escort_help_soap_breach()
{
	thread maps\intro_fx::enemies_compound_door_breach();
	breacher1_spawn = getent( "escort_help_soap_breacher1", "targetname" );
	breacher1 = breacher1_spawn spawn_ai( true );
	breacher1.animname = "breacher1";
	
	/*
	breacher2_spawn = getent( "escort_help_soap_breacher2", "targetname" );
	breacher2 = breacher2_spawn spawn_ai( true );
	breacher2.animname = "breacher2";
	breacher2.allowdeath = true;
	*/
	anim_pos = GetStruct( "anim_intro_room", "targetname" );
	
	level.soap notify( "stop_loop" );
	
	guys = [];
	guys[ 0 ] = [ level.nikolai, 0 ];
	guys[ 1 ] = [ level.soap, 0 ];
	guys[ 2 ] = [ breacher1, 0 ];
	guys[ 3 ] = [ level.player_rig, 0 ];
	guys[ 4 ] = [ level.price, 0.15 ];
	guys[ 5 ] = [ level.syringe, 0 ];

	level.price thread multiple_dialogue_queue( "escort_help_soap_breach_price_face" );
	anim_pos thread anim_single_end_early( guys, "escort_help_soap_breach" );
	anim_pos thread play_loop_solo_stoppable( level.soap, "soap_lie_down_idle", "stop_loop" );

	thread cleanup_player_rig();
	
	thread escort_price_post_breach();

	thread escort_pick_up_soap();
}

cleanup_player_rig()
{
	level.player_rig waittill( "anim_ended" );
	level.player Unlink();
	level.player disableinvulnerability();
	level.player_rig Delete();
	level.syringe Delete();
	maps\_shg_common::SetUpPlayerForGamePlay();
	level.player EnableWeaponSwitch();
	//level.player switchtoweapon( "deserteagle" );
	level.player EnableWeapons();
}

escort_price_post_breach()
{
	if ( level.price.a.pose == "prone" )
	{
		level.price OrientMode( "face default" );
		level.price animscripts\utility::ExitProneWrapper( 1.0 );
		level.price.a.onback = undefined;
	}
	
	level.price.a.pose =  "stand";
	level.price.a.movement = "run";
	level.price enable_cqbwalk();
	level.price waittill( "anim_ended" );
	
	//price leads you out.
	
	level.price enable_ai_color_dontmove();
	trig_price_post_door = GetEnt( "trig_price_post_door", "targetname" );
	trig_price_post_door notify( "trigger" );
	
	// wait until after the animation blends so the pop isn't as bad
	wait 0.4;
	autosave_by_name( "intro_help_soap_complete" );
}

escort_combat()
{
	flag_wait( "escort_player_starting_courtyard" );
	wait( 1 );
	while( 1 )
	{
		enemies = get_living_ai_array( "escort_spawn_1", "script_noteworthy" );
		if( enemies.size < 5 || flag( "escort_player_halfway_through_courtyard" ) )
		{
			array_spawn_targetname( "escort_spawn_2" );
			break;
		}
		wait( .1 );
	}
	
	while( 1 )
	{
		enemies = get_living_ai_array( "escort_spawn_2", "script_noteworthy" );
		if( enemies.size < 2 || flag( "escort_player_halfway_through_courtyard" ) )
		{
			array_spawn_targetname( "escort_spawn_3" );
			break;
		}
		wait( .1 );
	}
	
	maps\intro_vo::escort_dialog_courtyard_clear();
}

escort_open_door2()
{
	self RotateTo( self.angles + ( 0, -110, 0 ), .5, .25, 0 );
	self ConnectPaths();
	self waittill( "rotatedone" );
}

escort_open_door()
{
	self RotateTo( self.angles + ( 0, 110, 0 ), .5, .25, 0 );
	self ConnectPaths();
	self waittill( "rotatedone" );
}

escort_carry_soap()
{
	flag_wait( "intro_room_soap_to_wounded_idle" );
	level.nikolai waittill( "carry_picked_up" );
	maps\intro_carry::override_carry_anim( "wounded_idle", "wounded_idle" );
	
	level.soap waittill( "stop_putdown" );
	maps\intro_carry::set_default_carry_anims();

	thread escort_player_exits_courtyard();
}

escort_vehicles()
{
	thread escort_mi28_1();
}

escort_mi28_1()
{
	flag_wait( "escort_mi28_1_start" );
	wait( 3 );
	spawner = getent( "escort_mi28_1", "targetname" );
	mi28_1 = spawner spawn_vehicle_and_gopath();	
	mi28_1 thread helicopter_dmg_hint();
	aud_send_msg("escort_mi28_1", mi28_1);
	
	flag_wait( "escort_mi28_1_fire" );
	target = GetStruct( "escort_mi28_1_fire_dest1", "targetname" );
	mi28_1 thread heli_fire_turret( target, 75, .05 );
}

escort_rappelers()
{
	array_spawn_function_targetname( "escort_rappeler1", ::remove_grenades );
	array_spawn_function_targetname( "escort_rappeler1", ::lower_accuracy, .01 );
	array_spawn_function_targetname( "escort_rappeler1", ::disable_long_death );
	array_spawn_function_targetname( "escort_rappeler2", ::remove_grenades );
	array_spawn_function_targetname( "escort_rappeler2", ::lower_accuracy, .01 );
	array_spawn_function_targetname( "escort_rappeler2", ::disable_long_death );
	array_spawn_function_targetname( "escort_rappeler3", ::remove_grenades );
	array_spawn_function_targetname( "escort_rappeler3", ::lower_accuracy, .01 );
	array_spawn_function_targetname( "escort_rappeler3", ::disable_long_death );
	
	
	flag_wait( "escort_start_rappelers" );
	
	spawner = getent( "escort_rappeler3", "targetname" );
	rappeler3 = spawner spawn_ai( true );
	
	spawner = getent( "escort_rappeler1", "targetname" );
	rappeler1 = spawner spawn_ai( true );
	rappeler1.allowdeath = true;
	rappeler1.animname = "generic";
	rappeler1_lattice = getEntArray("rappeler1_lattice", "targetname");
	delaythread(3.5, ::exploder, "rappeler1");
	delaythread(3.55, ::hide_lattice, rappeler1_lattice);
	
	rope1 = spawn_anim_model( "rope", ( 0, 0, 0 ) );
	
	
	anim_pos = getstruct( "escort_rappeler1_anim_pos", "targetname" );
	anim_pos thread anim_single( [ rappeler1, rope1 ], "escort_rappel" );
	
	wait( 1 );
	spawner = getent( "escort_rappeler2", "targetname" );
	rappeler2 = spawner spawn_ai( true );
	rappeler2.allowdeath = true;
	rappeler2.animname = "generic";
	rappeler2_lattice = getEntArray("rappeler2_lattice", "targetname");
	delaythread(3.4, ::exploder, "rappeler2");
	delaythread(3.45, ::hide_lattice, rappeler2_lattice);
	
	rope2 = spawn_anim_model( "rope", ( 0, 0, 0 ) );
	
	anim_pos2 = getstruct( "escort_rappeler2_anim_pos", "targetname" );
	anim_pos2 thread anim_single( [ rappeler2, rope2 ], "escort_rappel" );
	
	flag_wait( "escort_player_starting_courtyard" );
	rope1 delete();
	rope2 delete();
}

hide_lattice(pieces)
{
	foreach(piece in pieces)
	{
		piece delete();
	}
}

escort_price_open_door()
{
	flag_wait( "escort_rappelers_dead" );
	level.price disable_ai_color();
	level.price pushplayer( true );
	hallway_door = getent( "escort_hotel_door_hallway", "targetname" );
	hallway_door2 = getent( "escort_hotel_door_hallway2", "targetname" );
	anim_pos = getstruct( "escort_price_open_door_to_stairs", "targetname" );
	anim_pos anim_reach_solo( level.price, "door_kick_in" );
	hallway_door delaythread( .4, ::escort_open_door );
	thread maps\intro_fx::price_compound_door_breach();
	aud_send_msg("escort_doorkick", hallway_door2);
	hallway_door2 delaythread( .4, ::escort_open_door2 );
	anim_pos anim_single_solo( level.price, "door_kick_in" );
	
	level.price enable_ai_color();
	level.price pushplayer( false );
	trigger = getent( "escort_price_down_stairs", "targetname" );
	trigger notify( "trigger" );
	
	//price goes into cqb after doc down anim
	level.price delaythread( 2, ::disable_cqbwalk );
	
}

escort_wounded()
{
	array_thread( getentarray( "escort_wounded_spawner_trigger", "targetname" ), ::drones_wounded, "regroup_dialog_intro_complete" );
	array_spawn_function_noteworthy( "escort_drone_anim_then_idle", ::drone_anim_then_idle_think, "regroup_dialog_intro_complete" );
	array_spawn_function_noteworthy( "escort_drone_anim_then_die", ::drone_anim_then_die_think, "regroup_dialog_intro_complete" );
}

escort_advanced_nikolai_color()
{
	flag_wait( "escort_player_starting_courtyard" );
	//thread color_volume_advance( "escort_nikolai_color", 3, 1 );
}

escort_player_exits_courtyard()
{
	flag_wait("exiting_courtyard");
	srcEnt = getent( "courtyard", "targetname" );
	dstEnt = getent( "regroup", "targetname" );
	remapStage(srcEnt.origin,dstEnt.origin);
}

/////////////////////
//---- REGROUP ----//
/////////////////////

regroup_price_to_nikolai()
{
	anim_ent = GetStruct( "regroup_price_to_nikolai_anim_ent", "targetname" );
	gate = spawn_anim_model( "gate", anim_ent.origin );
	anim_ent anim_first_frame_solo( gate, "price_to_nikolai" ); 
	
	flag_wait( "regroup_dialog_intro_start" );
	
	vol = getent( "regroup_start_dialog_check_enemies", "targetname" );
	
	while( vol get_ai_touching_volume( "axis" ).size )
		wait .1;
	
	col = getent( "regroup_price_to_nikolai_col", "targetname" );
	
	uav = spawn_anim_model( "uav", ( 0, 0, 0 ) );

	level.price disable_ai_color();
	
	anim_ent anim_reach_solo( level.price, "price_to_nikolai_transition" );
	flag_set( "regroup_dialog_intro_start_all_clear" );
	anim_ent anim_single_solo( level.price, "price_to_nikolai_transition" );
	
	delaythread( 13, ::flag_set, "regroup_intro_start_sequence" );
	delaythread( 9, ::flag_set, "regroup_intro_enemies_start" );
	delaythread( 13, ::flag_set, "regroup_start_civilian_run" );
	uav delaythread( 3.75, ::regroup_gate_uav_fire_missiles );
	
	level.price thread multiple_dialogue_queue( "price_to_nikolai_face" );
	anim_ent thread anim_single( [ level.price, gate, uav ] , "price_to_nikolai" );
	aud_send_msg("regroup_uav_gate_fly_by", uav);
	wait( 15.5 );
	thread maps\intro_fx::regroup_price_gate_breach();
	col thread regroup_open_gate();
	aud_send_msg("mus_courtyard_gate_breach");
	aud_send_msg("aud_courtyard_gate_breach");
	
	
	//level.price enable_ai_color_dontmove();
	level.price enable_ai_color();
	trig_price_post_door = GetEnt( "escort_gate_open_price_move_up", "targetname" );
	trig_price_post_door notify( "trigger" );
	
	autosave_by_name( "regroup_start" );
}

regroup_gate_uav_fire_missiles()
{
	target = GetEnt( "regroup_gate_uav_target", "targetname" );
	target fire_fake_missile( self, "direct" );
}

regroup_price_break_and_rake()
{
	car_spawner = GetEnt( "regroup_break_and_rake_car", "targetname" );
	
	car = spawn_anim_model( "destructible_car", car_spawner.origin );
	car.angles = car_spawner.angles;
	//car = spawn_vehicle_from_targetname( "regroup_break_and_rake_car" );
	//car.animname = "destructible_car";
	//car SetCanDamage( false );
	
	car thread setup_custom_glass_destruction();
	
	anim_pos = GetStruct( "regroup_break_and_rake", "targetname" );
	anim_pos anim_first_frame_solo( car, "price_break_and_rake" );
	
	trigger_price_cover_slide = GetEnt( "trigger_price_cover_slide", "targetname" );
	trigger_price_cover_slide waittill( "trigger" );
	
	//get price to use cover after the anim is complete
	trigger_price_color_after_rake = GetEnt( "regroup_price_break_and_rake_complete_color", "targetname" );
	trigger_price_color_after_rake notify( "trigger" );
	
	level.price disable_awareness();
	level.price disable_ai_color();
	
	// play price slide to cover
	anim_pos anim_reach_solo( level.price, "price_break_and_rake" );
	anim_pos thread anim_single( [ level.price, car ], "price_break_and_rake" );
	
	delaythread( 2.65, maps\intro_anim::break_glass, car );
	level.price.a.pose = "crouch";
	level.price enable_ai_color();
	level.price enable_awareness();
}

regroup_open_gate()
{
	self ConnectPaths();
	self delete();
}

regroup_intro_friends()
{
	thread regroup_intro_friends_initial();
	thread regroup_intro_friends_cleanup();
}

regroup_intro_friends_initial()
{

	array_spawn_function_targetname( "regroup_intro_friendlies_init", ::regroup_intro_friends_setup );
	array_spawn_function_targetname( "regroup_intro_friendlies_init", ::regroup_friendly_shoot_chopper );
	
	flag_wait( "regroup_intro_friendlies_init_spawn" );
	
	array_spawn_noteworthy( "regroup_intro_friendlies_init" );
	array_spawn_noteworthy( "regroup_intro_friendlies_init_extra" );//extra guy gets deleted if he didn't already die later for the breachers
	
}

regroup_intro_friends_cleanup()
{
	flag_wait( "maars_control_player_controlling_maars" );
	level notify( "kill_color_replacements" );
	guys = get_living_ai_array( "regroup_intro_friendlies_init", "script_noteworthy"  );
	array_thread( guys, ::self_delete );

	guys = get_living_ai_array( "breachers", "script_noteworthy"  );
	array_thread( guys, ::self_delete );
}

regroup_intro_friends_setup()
{
	self thread replace_on_death();
	self endon( "death" );
}

regroup_intro_friends_move_up()
{
	self endon( "death" );
	
	self.animname = "generic";
	self thread magic_bullet_shield();
	
	self disable_ai_color();
	animation = "coverstand_hide_idle_wave01";
	node = getnode( "regroup_russian_friendly_wave_up", "targetname" );
	node anim_reach_and_approach_node_solo( self, animation );
	thread regroup_intro_friends_move_up_color();
	node anim_single_solo( self, animation );
	
	self stop_magic_bullet_shield();
	self enable_ai_color();

	//cleanup
	flag_wait( "maars_control_player_controlling_maars" );
	
	if ( IsDefined( self ) )
	{
		thread ai_delete_when_out_of_sight( [ self ], 256 );
	}
}

regroup_intro_friends_move_up_color()
{
	trigger = getent( "regroup_intro_friendlies_move_up_color", "targetname" );
	trigger notify( "trigger" );
}

regroup_intro_enemies()
{
	array_spawn_function_targetname( "mg_gunner", ::mg_guy_think );

	rpg_target = getent( "regroup_rpg_target", "targetname" );
	rpg_guy = getent( "regroup_rpg_rooftop_spawner", "script_noteworthy" );
	rpg_guy add_spawn_function( ::regroup_rpg_scripted, rpg_target );
}

regroup_rural_helicopter_threat_group_setup()
{
	createthreatbiasgroup( "player_group" );
	createthreatbiasgroup( "regroup_rural_helicopter_enemies" );
	
	level.player setthreatbiasgroup( "player_group" );
	level.price setthreatbiasgroup( "player_group" );
	level.nikolai setthreatbiasgroup( "player_group" );
	setignoremegroup( "player_group", "regroup_rural_helicopter_enemies" );	
}


regroup_rural_helicopter_threat_group()
{
	self endon( "death" );
	self.grenadeammo = 0;
	self setthreatbiasgroup( "regroup_rural_helicopter_enemies" );
	
	level waittill( "regroup_rural_helicopter_player_attacked" );

	self setthreatbiasgroup( );
}

regroup_rural_helicopter_monintor_player_attack()
{
	self endon( "death" );
	level endon( "regroup_rural_helicopter_player_attacked" );
	while( 1 )
	{	
		self waittill( "damage", damage_amount, attacker );
		if ( attacker == level.player )
			level notify( "regroup_rural_helicopter_player_attacked");
	}
}


regroup_intro_enemies_initial()
{
	array_spawn_function_targetname( "regroup_intro_enemy_initial_fighter", ::regroup_casual_killer_setup );
	
	flag_wait( "regroup_intro_enemies_start" );
	array_spawn_targetname( "regroup_intro_enemy_initial_fighter" );
	
	flag_wait( "regroup_casual_killers_dead" );
	
	flag_set( "regroup_car_start" );
	
	trigger = getent( "regroup_spawners0_trigger", "targetname" );
	if( isdefined( trigger ) )
	{
		trigger notify( "trigger" );
	}
	
	trigger = getent( "trigger_price_cover_slide", "targetname" );
	if( isdefined( trigger ) )
	{
		trigger notify( "trigger" );
}

}

regroup_casual_killer_setup()
{
	self endon( "death" );
	self maps\_casual_killer::enable_casual_killer();
	self.animplaybackrate = 1.5;
	self.script_forcegoal = 1;
	target = getent( "regroup_casual_killer_target", "targetname" );
	
	self setentitytarget( target );
	
	level add_wait( ::waittill_msg, "regroup_causal_killer_clear_target" );
	self add_wait( ::waittill_msg, "damage" );
	do_wait_any( );
	self.script_forcegoal = undefined;
	self.animplaybackrate = 1;
	self clearEntityTarget();
	self maps\_casual_killer::disable_casual_killer();
}

regroup_intro_enemies_initial_setup(num_to_retreat)
{
	self disable_long_death();
	self thread remove_grenades();
	self waittill( "death" );
	level.regroup_intro_enemies_initial_killed++;
	
	if( level.regroup_intro_enemies_initial_killed >= num_to_retreat )
	{
		flag_set( "regroup_intro_enemies_initial_retreat" );
	}
}

regroup_carry_soap()
{

}

regroup_civilians()
{
	//array_spawn_function_targetname( "regroup_dog", ::regroup_dog );
	
	array_spawn_function_noteworthy( "regroup_drone_anim_then_delete", ::drone_anim_think );
	array_spawn_function_targetname( "regroup_filler_drones", ::drone_respawn );
	array_spawn_function_targetname( "regroup_filler_drones2", ::drone_respawn );
	array_spawn_function_targetname( "regroup_filler_drones3", ::drone_respawn );
	array_spawn_function_noteworthy( "regroup_drone_anim_then_idle", ::drone_anim_then_idle_think, "regroup_wounded_spawner_cleanup2" );
	array_spawn_function_noteworthy( "regroup_drone_anim_then_die", ::drone_anim_then_die_think, "maars_control_player_controlling_maars" );
	array_thread( getentarray( "regroup_wounded_spawner_trigger", "targetname" ), ::drones_wounded, "regroup_wounded_spawner_cleanup" );
	
	array_thread( getentarray( "regroup_wounded_spawner_trigger2", "targetname" ), ::drones_wounded, "regroup_wounded_spawner_cleanup2" );
	
	
	thread regroup_looping_runners();
	thread regroup_civilians_run();
	thread regroup_civilian_door_peek();
}

regroup_looping_runners()
{
	flag_wait( "regroup_drone_looping_runners" );
	civ_ent_01 = array_spawn_targetname( "regroup_filler_drones" );
	aud_send_msg("start_civ_runners_wave1a", civ_ent_01);
	wait 5;
	civ_ent_02 = array_spawn_targetname( "regroup_filler_drones2" );
	aud_send_msg("start_civ_runners_wave1b", civ_ent_02);
	wait 5;
	civ_ent_03 = array_spawn_targetname( "regroup_filler_drones3" );
	aud_send_msg("start_civ_runners_wave1b", civ_ent_03);
}

regroup_civilian_door_peek()
{
	spawned = false;
	while( 1 )
	{
		count = 0;
		while( flag( "regroup_drone_door_peek_looking" ) )
		{
			if( count > 20 || flag( "regroup_start_civilian_run" ) )
			{
				array_spawn_targetname( "regroup_drone_door_peek", true );
				spawned = true;
				break;
			}
			count++;
			wait .1;
		}
		
		if( spawned == true )
			break;
			
		wait .05;
	}
}


regroup_dog()
{
	self endon( "death" );
	self.ignoreall = true;
	self.ignoreme = true;
	self waittill( "goal" );
	self delete();
}


regroup_civilians_run()
{
	array_spawn_function_targetname( "regroup_filler_drones_real", ::drone_runner_think, "regroup_delete_runners" );
	array_spawn_function_targetname( "regroup_drone_runner", ::drone_runner_think, "regroup_delete_runners" );
	array_spawn_function_targetname( "regroup_drone_runner2", ::drone_runner_think, "regroup_delete_runners" );
	
	flag_wait( "regroup_start_civilian_run" );
	thread regroup_drone_runners();
	thread regroup_drone_stop_loopers();
	wait 2;
	thread regroup_civ_magic_bullets();
	flag_set( "regroup_helicopters_start" );
}

regroup_drone_stop_loopers()
{
	//wait 2;
	flag_set( "regroup_drone_stop_loopers" );
}

regroup_civ_setup()
{
	self endon( "death" );
	
	self waittill( "goal" );
	self delete();
}

regroup_civ_magic_bullets()
{
	orgs = getStructarray( "regroup_civilian_magic_bullet_org", "targetname" );
	targets = getStructarray( "regroup_civilian_magic_bullet_target", "targetname" );
	volume = getent( "regroup_civilian_volume", "targetname" );
	timer = gettime() + 5000;


	while( gettime() < timer )
	{
		/*
		civs = volume get_ai_touching_volume( "neutral" );
		if( civs.size <= 0 )
			break; 
			*/
		foreach( org in orgs )
		{
			target = random( targets );
			for( i=0; i < 3; i++ )
			{
				magicbullet( "dshk_turret_sp", org.origin, target.origin );
			}
			wait( randomfloatrange( 0, .2 ) ); 
		}
		wait( randomfloatrange( .05, .5 ) );
	}
}

regroup_civilians2_run()
{
	array_spawn_function_targetname( "regroup_civilian2", ::regroup_civ2_setup );
	array_spawn_function_targetname( "regroup_civilian2", ::regroup_civ2_setup_death );
	flag_wait( "regroup_civilian2_start" );
	array_spawn_targetname( "regroup_civilian2" );
	
	flag_wait( "regroup_civilian2_stop" );
	
	level notify( "regroup_civ2_stop_respawn" );
}

regroup_civ2_setup_death()
{
	level endon( "regroup_civ2_stop_respawn" );
	self endon( "goal" );
	self waittill( "death" );
	
	thread regroup_civ2_respawn();
}

regroup_civ2_setup()
{	
	level endon( "regroup_civ2_stop_respawn" );
	self endon( "death" );
	self waittill( "goal" );
	
	thread regroup_civ2_respawn();
	
	if( isdefined( self) )
		self delete();
}

regroup_civ2_respawn()
{
	level endon( "regroup_civ2_stop_respawn" );
	spawners = GetEntArray( "regroup_civilian2", "targetname" );
	spawner = random( spawners );
	wait( randomfloatrange( .5, 10 ) );
	spawner.count = 1;
	spawner spawn_ai();
}

regroup_helicopters()
{
	flag_wait( "regroup_helicopters_start" );
	
	//regroup_mi28_1 = thread attack_helicopter( "regroup_mi28_1", true, 30 );
	//regroup_mi28_1 SetMaxPitchRoll( 40, 60 );
	
	flag_wait( "regroup_mi17_1_start" );
	heli_spawn = getent( "regroup_mi17_1", "targetname" );
	heli = heli_spawn spawn_vehicle_and_gopath();
	aud_send_msg("regroup_mi17_1", heli);
	
	heli godon();
	heli thread regroup_mi17_1_monitor_death();
	heli thread regroup_mi17_1_monitor_unload();
	heli thread regroup_mi17_1_delete_riders();
	heli thread helicopter_dmg_hint();
	thread maps\intro_fx::intro_heliswirl();
	
	//make sure the helicopter is dead or out of the way before bringing in the mi28
	flag_wait( "regroup_mi17_unloaded" );
}

regroup_ending()
{
	array_spawn_function_noteworthy( "regroup_ending_mg_turret", ::mg_guy_think, "regroup_ending_player_looking_past_gate", true );
	array_spawn_function_targetname( "regroup_spawners13", ::remove_grenades );
	
	thread regroup_ending_helicopter();
	thread regroup_ending_helicopter_last_street();
	thread regroup_ending_price();
	thread regroup_ending_breachers();
	thread regroup_ending_civs();
	
	flag_wait( "regroup_player_at_gate" );
	flag_set( "regroup_ending_shoot_at_player" );

}

regroup_ending_civs()
{
	array_thread( getentarray( "regroup_wounded_spawner_trigger3", "targetname" ), ::drones_wounded, "maars_control_player_controlling_maars" );
	//array_spawn_function_noteworthy( "regroup_ending_drone_anim_then_idle", ::drone_anim_then_idle_think, "maars_control_player_controlling_maars" );
	
	flag_wait( "regroup_ending_breaching" );
	wait .5;
	//array_spawn_targetname( "regroup_ending_anim_then_idle" );
	
	array_spawn_targetname( "regroup_ending_close_garage" );
}

regroup_ending_breachers()
{
	flag_wait( "regroup_ending_start" );

	//removing some of the friendlies if they aren't already dead
	//also stopping them from respawning	
	ents = getentarray( "regroup_intro_friendlies_init_extra", "script_noteworthy" );
	if( isdefined( ents ) )
	{
		foreach( ent in ents )
		{
			if( !isSpawner( ent ) )
			{
				ent notify( "_disable_reinforcement" );
				thread ai_delete_when_out_of_sight( [ ent ], 256 );
			}
		}
	}
	
	//Spawning two new guys with shotguns that we know exactly where they are and won't be waiting for them.
	breachers = array_spawn_noteworthy( "breachers" );
	array_thread( breachers, ::deletable_magic_bullet_shield );
	breachers[0].animname = "left_guy";
	breachers[0].awareness = 1;
	
	breachers[1].animname = "right_guy";
	breachers[1].awareness = 1;
	
	flag_wait( "regroup_ending_ugv_dialog_end" );
	
	breachers[0] disable_awareness();
	breachers[1] disable_awareness();
	
	thread regroup_ending_building_breach( breachers );
	thread regroup_ending_shotgun_breach( breachers );
	wait 2;

}

regroup_ending_price()
{
	flag_wait( "regroup_player_at_gate" );
	
	vol = getent( "regroup_ending_price_arrived", "targetname" );
	wait_for_price_count = 0;
	while( !level.price istouching( vol ) )
	{
		//if price doesn't make it within a certain time, just move on to stop progression blocker.
		if( wait_for_price_count > 50 )
			break;
		wait .1;
		wait_for_price_count ++;
	}
	
	flag_set( "regroup_ending_ugv_dialog_start" );
	flag_wait( "regroup_ending_ugv_dialog_end" );
	flag_set( "regroup_ending_follow_price" );
	
	level.price disable_awareness();

	trigger = getent( "regroup_friendly_color_heli_retreat", "targetname" );
	trigger notify( "trigger" );
	
	flag_wait( "regroup_ending_first_door_breached" );
	
	//trigger next color
	trigger = getent( "regroup_ending_building_price_after_door", "targetname" );
	trigger notify( "trigger");
	
	flag_wait( "regroup_ending_shotgun_breach_complete" );
	trigger = getent( "regroup_ending_price_after_shotgun_breach", "targetname" );
	trigger notify( "trigger");
	
	level.price enable_awareness();


}

regroup_ending_building_breach( guyArray )
{
	flag_wait( "regroup_player_at_gate" );
	
	anim_pos = getstruct( "regroup_ending_door_kick_breach", "targetname" );
	anim_pos anim_reach_and_idle_solo( guyArray[0], "breach_kick_stackL1_idle", "breach_kick_stackL1_idle", "end_idle" );

	flag_wait( "regroup_ending_ugv_dialog_end" );
	wait_for_player_to_look( guyArray );
	
	anim_pos anim_reach_solo( guyArray[1], "breach_kick" );
	flag_set( "regroup_ending_breaching" );
	
	thread maps\intro_fx::regroup_end_door_01_breachfx();
	
	anim_pos notify( "end_idle" );
	waittillframeend;
	delaythread( .5, ::regroup_ending_door_kick_breach_open_door, "regroup_ending_building_door" );
	aud_send_msg("mus_civilian_door_breach");
	aud_send_msg("aud_civilian_door_breach");
	anim_pos anim_single( guyArray, "breach_kick" );
	
	
	//guyArray[ 0 ] thread go_to_node_then_enable_color( "door_kick_breach_left_target" );
	//guyArray[ 1 ] thread go_to_node_then_enable_color( "door_kick_breach_right_target" );

	flag_set( "regroup_ending_first_door_breached" );
}

regroup_ending_door_kick_breach_open_door( targetname )
{
	thread background_hillside_visibility( true );
	
	setsaveddvar("sm_spotlimit",2);	
	
	door = getent( targetname, "targetname" );
	door rotateto( door.angles + ( 0, 110, 0 ), .5, 0, 0 );
	door connectPaths();
}

regroup_ending_shotgun_breach( guyArray )
{
	door_model = spawn_anim_model( "door" );
	door_anim_pos = getent( "shotgun_breach_door", "targetname" );
	door_anim_pos anim_first_frame_solo( door_model, "door_breach" ); 
	
	flag_wait( "regroup_ending_first_door_breached" );
		
	ent = getent( "shotgun_breach", "targetname" );

	ent anim_reach_and_idle( guyArray, "door_breach_setup", "door_breach_setup_idle", "stop_door_breach_idle" );

	ent notify( "stop_door_breach_idle" );
	ent anim_single( guyArray, "door_breach_setup" );
	ent thread anim_loop( guyArray, "door_breach_idle", "stop_loop" );

	wait_for_player_to_look( guyArray );

	ent notify( "stop_loop" );
	
	flag_set( "regroup_ending_shotgun_breach_dialog" );

	ent thread anim_single( guyArray, "door_breach" );

	thread maps\intro_fx::regroup_end_door_02_breachfx();

	//guyArray[1] waittillmatch( "single anim", "kick" );
	wait 1.8;
	door_anim_pos thread anim_single_solo( door_model, "door_breach" );
	door = getent( "shotgun_breach_door_col", "targetname" );
	door connectPaths();
	door delete();
	door_model playsound( "wood_door_kick" );

	delayThread( .5, ::flag_set, "regroup_ending_shotgun_breach_complete" );
	
	//guyArray[ 0 ] waittillmatch( "single anim", "end" );
	
	guyArray[ 0 ] thread go_to_node_then_enable_color( "shotgun_breach_guy_right_target" );
	guyArray[ 1 ] thread go_to_node_then_enable_color( "shotgun_breach_guy_left_target" );
	
	//trigger = getent( "shotgun_breach_complete_color", "targetname" );
	//trigger notify( "trigger" );
}

go_to_node_then_enable_color( node_targetname )
{
	target = getnode( node_targetname, "targetname" );
	self setgoalnode( target );
	waittillframeend;
	self.goalradius = 10;
	self waittill( "goal" );
	//self enable_ai_color();
}


regroup_ending_building_door_open_anim()
{

}

regroup_ending_building_door_open()
{
	door = getent( "regroup_ending_building_door", "targetname" );
	door RotateTo( door.angles + ( 0, 90, 0 ), .3, .1, 0 );
	door ConnectPaths();
}

regroup_ending_helicopter_last_street()
{
	flag_wait( "regroup_ending_helicopter_last_street" );
	mi28_6 = spawn_vehicle_from_targetname_and_drive( "regroup_mi28_6" );
	aud_send_msg("worlds_slowest_helicopter_by", mi28_6);
	
	mi28_6 SetMaxPitchRoll( 20, 15 );
	mi28_6 thread helicopter_dmg_hint();
}

regroup_ending_helicopter()
{
	flag_wait( "regroup_ending_start" );
	
	mi28_5_spawner = getent( "regroup_mi28_5", "targetname" );
	mi28_5 = mi28_5_spawner spawn_vehicle_and_gopath();
	mi28_5 SetMaxPitchRoll( 20, 15 );
	aud_send_msg("regroup_ending_start", mi28_5);
	mi28_5 godon();
	mi28_5 thread helicopter_dmg_hint();
	level notify( "regroup_mi28_5_spawned", mi28_5 );
	
	flag_wait( "regroup_mi28_5_inposition" );
	
	wait 1;
	
	thread regroup_ending_monitor_player_kill();
	
	//trigger = getent( "regroup_friendly_color_heli_retreat", "targetname" );
	//trigger notify( "trigger" );
	
	target = getstruct( "regroup_mi28_5_target", "targetname" );
	mi28_5 heli_fire_turret( target , 50, .05 );
	
	ai_vol = getent( "regroup_ending_target_vol", "targetname" );
	vol = getentarray( "regroup_ending_player_safe_vol", "targetname" );
	
	while( !flag( "maars_control_player_controlling_maars" ) )
	{
		
		
		targets = ai_vol get_ai_touching_volume( "allies" );
		
		
		if( !check_volumes( vol ) && flag( "regroup_ending_shoot_at_player" ) )
		{
			if( !isdefined( level.player_mg_target ) )
				mg_player_target();
			mi28_5 heli_fire_turret( level.player_mg_target, 5, .1 );	
		}
		else
		if( isdefined( targets ) && !check_volumes( vol ) )
		{
			guy = random( targets );
			
			if( isAlive( guy ) )
				mi28_5 heli_fire_turret( guy, 10, .1 );
		}
		wait randomIntrange( 2, 5 );
	}
	
	mi28_5 delete();
}


regroup_friendly_shoot_chopper()
{
	self endon( "death" );
	level waittill( "regroup_mi28_5_spawned", chopper );

	flag_wait( "regroup_mi28_5_insight" );

	self SetEntityTarget( chopper );
}

regroup_ending_monitor_player_kill()
{
	level endon( "maars_control_player_controlling_maars" );
	
	if( !check_volumes( GetEntArray( "regroup_ending_player_in_area", "targetname" ) ) )
	{
		building_slide_kill_player();
	}
	else
	{
		flag_wait( "regroup_ending_player_kill" );
		building_slide_kill_player();
	}
}

regroup_mi28_2_monitor_missile_hit()
{
	self endon( "death" );
	self waittill( "missile_hit" );
	self notify( "death" );
}

regroup_mi17_1_delete_riders()
{
	flag_wait( "regroup_mi17_delete_riders" );

	ents = getentarray( "regroup_mi17_enemy", "script_noteworthy" );
	foreach( ent in ents )
	{
		if( !isSpawner( ent ) )
		{
			ai_delete_when_out_of_sight( [ ent ], 512 );
		}
	}
}


regroup_mi17_1_monitor_unload()
{
	self endon( "death" );
	level endon( "regroup_mi17_delete_riders" );
	
	while( self.riders.size > 1 )
	{
		wait(.05);
	}
	flag_set( "regroup_mi17_unloaded" );
}

regroup_mi17_1_monitor_death()
{
	self waittill( "death" );
	flag_set( "regroup_mi17_unloaded" );
}

regroup_uav_gate_fly_by()
{
	flag_wait( "regroup_dialog_intro_start" );
	//wait( 10 );
	spawner = getent( "regroup_uav_gate_fly_by", "targetname" );
	uav_1 = spawner spawn_vehicle_and_gopath();	
	
	flag_wait( "regroup_uav_gate_fly_by_fire" );
	target = GetStruct( "regroup_uav_gate_fly_by_target", "targetname" );
	uav_1 thread uav_fire_missiles( target, 2, 2, "viper_tow_intro");
}

regroup_uav_gate_fly_by_target_hit()
{
	playfx( getfx( "slamraam_explosion" ) , self.origin );
	earthquake(.8, 3, self.origin, 1024);
	level.player playrumbleonentity( "artillery_rumble" );
	playfx( getfx( "smoke_large" ) , self.origin );
}


regroup_roll_up_door()
{
	door_trigger = getent( "regroup_trigger_garage_door", "targetname" );
	door_trigger thread trigger_garage_door();
}

trigger_garage_door()
{
	self waittill( "trigger" );

	doors = GetEntArray( self.target, "targetname" );
	foreach ( door in doors )
	{
		if ( IsSpawner( door ) )
		{
			continue;
		}

		door thread garage_door_open();
		flag_set( "regroup_roll_up_dialog" );
		thread maps\intro_fx::intro_regroup_doorfx();
	}
}

garage_door_open()
{
	if ( IsDefined( self.opened ) )
	{
		return;
	}

	self.opened = true;
	//self script_delay();

	dist = 104;
	z = self.origin[ 2 ] + dist;
	pieces = GetEntArray( self.target, "targetname" );

	spawners = [];

	clip = undefined;
	foreach ( piece in pieces )
	{
		if ( IsSpawner( piece ) )
		{
			spawners[ spawners.size ] = piece;
			continue;
		}

		piece LinkTo( self );
		piece thread garage_door_unlink( z );
	}

	if ( spawners.size > 0 )
	{
		//array_spawn( spawners );
		array_thread( spawners, ::spawn_ai );
	}

	min_dist = 48;
	time = 1.5;
	speed = dist / time;
	time = min_dist / speed;

	self thread play_sound_on_entity( "door_garage_metal_rolling_up" );
	self MoveZ( min_dist, time, time * 0.8 );
	wait( time - 0.05 );

	self ConnectPaths();

	dist -= min_dist;
	time = dist / speed;
	self MoveZ( dist, time );
}

garage_door_unlink( z )
{
	while ( self.origin[ 2 ] < z )
	{
		wait( 0.05 );
	}

	self Delete();
}

regroup_uav_street()
{
	
	//flag_wait( "regroup_uav_street_start" );
	
	lookat_target = getent( "regroup_street_uav_player_lookat", "targetname" );
	lookat_target add_wait( ::waittill_player_lookat_for_time, 0.5, .98 );

	lookat_target do_wait_any();
	
	flag_set( "regroup_uav_street_start" );
	
	uav_spawn = getent( "regroup_uav_street", "targetname" );
	uav = uav_spawn spawn_vehicle_and_gopath();
	aud_send_msg("UAV_street_bombing", uav);
	
	flag_wait( "regroup_uav_street_fire" );
	target1 = GetStruct( "regroup_uav_street_target1", "targetname");
	uav thread uav_fire_missiles( target1, 1, 0, "viper_tow_intro" );
	
	target1 = GetStruct( "regroup_uav_street_target2", "targetname");
	uav thread uav_fire_missiles( target1, 1, 0, "viper_tow_intro" );
}

regroup_building_destruct_a_destroy()
{
	//playfx( getfx( "slamraam_explosion" ) , self.origin );
	exploder(666);
	earthquake(.6, 1.5, self.origin, 1024);
	level.player playrumbleonentity( "artillery_rumble" );
	
	ents = getentarray( "regroup_building_destruct_a_damaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent hide_notsolid();
	}
	
	//wait 2;
	//playfx( getfx( "smoke_large" ) , self.origin );
	/*
	ents = getentarray( "regroup_building_destruct_a_damaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent show();
	}*/
}

regroup_building_destruct_b_destroy()
{
	playfx( getfx( "slamraam_explosion" ) , self.origin );
	earthquake(.8, 3, self.origin, 1024);
	level.player playrumbleonentity( "artillery_rumble" );
	
	ents = getentarray( "regroup_building_destruct_b_undamaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent hide_notsolid();
	}
	
	ents = getentarray( "market_building_11_removable", "targetname" );
	foreach( ent in ents )
	{
		ent hide_notsolid();
	}
	
	ents = getentarray( "regroup_building_destruct_b_damaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent show();
	}
	
	playfx( getfx( "smoke_large" ) , self.origin );
}

regroup_building_destruct_c_destroy()
{
	playfx( getfx( "slamraam_explosion" ) , self.origin );
	earthquake(.8, 3, self.origin, 1024);
	level.player playrumbleonentity( "artillery_rumble" );
	
	ents = getentarray( "regroup_building_destruct_c_undamaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent hide_notsolid();
	}
	
	ents = getentarray( "regroup_building_destruct_c_damaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent show();
	}
	
	playfx( getfx( "smoke_large" ) , self.origin );
}

regroup_building_destruct_d_destroy()
{
	playfx( getfx( "slamraam_explosion" ) , self.origin );
	earthquake(.8, 3, self.origin, 1024);
	level.player playrumbleonentity( "artillery_rumble" );
	
	ents = getentarray( "regroup_building_destruct_d_undamaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent hide_notsolid();
	}
	
	ents = getentarray( "market_transition_01_removable", "targetname" );
	foreach( ent in ents )
	{
		ent hide_notsolid();
	}
	
	ents = getentarray( "regroup_building_destruct_d_damaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent show();
	}
	
	playfx( getfx( "smoke_large" ) , self.origin );
}

regroup_building_destructs_setup()
{
	/*
	ents = getentarray( "regroup_building_destruct_a_damaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent hide_notsolid();
	}
	*/
	/*
	ents = getentarray( "regroup_building_destruct_b_damaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent hide_notsolid();
	}
	*/
	ents = getentarray( "regroup_building_destruct_a_damaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent hide_notsolid();
	}
	
	
	/*
	ents = getentarray( "regroup_building_destruct_c_damaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent hide_notsolid();
	}
	
	ents = getentarray( "regroup_building_destruct_d_damaged_state", "targetname" );
	foreach( ent in ents )
	{
		ent hide_notsolid();
	}
	*/
}

regroup_helicopters_gate()
{
	flag_wait( "regroup_dialog_intro_start" );
	mi28_3 = attack_helicopter( "regroup_mi28_3", true, 25 );
	mi28_3 SetMaxPitchRoll( 25, 25 );
	mi28_3 thread helicopter_dmg_hint();
	aud_send_msg("courtyard_exit_flyby_01", mi28_3);
	wait 2;
	mi28_4 = attack_helicopter( "regroup_mi28_4", true, 25 );
	mi28_4 SetMaxPitchRoll( 25, 25 );
	mi28_4 thread helicopter_dmg_hint();
	aud_send_msg("courtyard_exit_flyby_02", mi28_4);
}

regroup_drone_runners()
{
	array_spawn_targetname( "regroup_filler_drones_real" );
	drones = array_spawn_targetname( "regroup_drone_runner" );
	aud_send_msg("start_civ_runners_wave_2", drones);
	wait 3;
	//drones = array_spawn_targetname( "regroup_drone_runner2" );
}
	
regroup_civ_car()
{
	flag_wait( "regroup_car_start" );
	car = spawn_vehicle_from_targetname_and_drive( "regroup_civ_car" );
	car thread regroup_civ_car_monitor_death();
	aud_send_msg("intro_civ_car_slide", car);
	
	thread maps\intro_fx::regroup_car_skid(car);
	
	src = getstruct( "regroup_car_magic_bullet_src", "targetname" );
	while( !flag( "regroup_car_crashed" ) )
	{
		magicbullet( "dshk_turret_sp", src.origin, car.origin + ( randomIntrange( -32, 32 ), randomIntrange( -32, 32 ), randomIntrange( 32, 100 ) ) );
		wait randomfloatrange( .05, .1 );
	}
}

regroup_civ_car_monitor_death()
{
	self waittill( "death" );
	playfx( getfx( "vehicle_explosion" ) , self.origin );
	aud_send_msg("intro_civ_car_explode", self.origin);
	earthquake(.2, 3, self.origin, 256);
	self radiusdamage( self.origin, 128, 200, 100 );
}


regroup_price_down_alley()
{
	flag_wait( "regroup_player_moving_down_alleyway" );
	
	trigger = getent( "regroup_price_down_alley", "targetname" );
	
	if( isdefined( trigger ) )
		trigger notify( "trigger" );
}

regroup_car_cover()
{

	anim_pos = getstruct( "regroup_car_cover_car_anim_pos", "targetname" );
	car = getent( "regroup_car_cover_car", "targetname" );
	car.animname = "cover_car";
	car setanimtree();
	
	
	anim_pos anim_first_frame_solo( car, "car_door_cover" );
	
	door_col = getent( "regroup_car_door_cover_door_col", "targetname" );
	door_col notsolid();
		
	trigger = getent( "regroup_car_cover_trigger", "targetname" );
	trigger waittill( "trigger" );
	
	while( !flag( "regroup_car_door_cover_door_open" ) )
	{
		guy = regroup_car_cover_get_guy();
		regroup_car_cover_getto_door( guy );
		wait( randomintrange( 3, 5 ) );
	} 

}


regroup_car_cover_get_guy()
{
	vol = getent( "regroup_car_door_cover_vol", "targetname" );

	while( 1 )
	{ 
		guys = vol get_ai_touching_volume( "axis" );
		if( guys.size > 0 )
		{
			return guys[0];
		}
		wait( .05 );
	}
	
}

regroup_car_cover_getto_door( guy )
{
	guy endon( "death" );
	guy endon( "long_death" );
	
	guy.animname = "generic";
	
	anim_pos = getstruct( "regroup_car_cover_car_anim_pos", "targetname" );
	
	while( isAlive( guy ) && !guy doinglongdeath() )
	{ 
		anim_pos anim_reach_solo( guy, "car_door_cover" );
		if( anim_pos check_anim_reached( guy, "car_door_cover", undefined, undefined, 32 ) )
			break;
			
		wait( .05 );
	}
	
	if( isAlive( guy ) && !guy doinglongdeath() )
		thread regroup_car_cover_open_door( guy );
}

regroup_car_cover_open_door( guy )
{	
	guy.allowdeath = true;
	anim_pos = getstruct( "regroup_car_cover_car_anim_pos", "targetname" );
	
	car = getent( "regroup_car_cover_car", "targetname" );
	car.animname = "cover_car";
	car setanimtree();
	
	
	
	if( isAlive( guy ) && !guy doinglongdeath() ) {
		
		anim_pos thread anim_single( [ car, guy ], "car_door_cover" );
		guy thread regroup_car_cover_guy_opening_door( car );
		car thread regroup_car_cover_door_is_open( guy );
		
	}
}

regroup_car_cover_guy_opening_door( car )
{
	level endon( "regroup_car_door_cover_door_open" );
	self waittill( "death" );
	car notify( "anim_stopped" );
	car anim_stopanimscripted();
}

regroup_car_cover_door_is_open( guy )
{
	self endon( "anim_stopped" );
	wait( 1 );
	flag_set( "regroup_car_door_cover_door_open" );
	node_col = getent( "regroup_car_door_cover_node_col", "targetname" );
	node_col ConnectPaths();
	node_col delete();
	door_col = getent( "regroup_car_door_cover_door_col", "targetname" );
	door_col solid();
	if( isAlive( guy ) )
	{
		node = getnode( "regroup_car_door_cover_node", "targetname" );
		guy setgoalnode( node );
		guy.a.pose = "crouch";
	}
}

regroup_damage_cars()
{
	damage_locations = getStructarray( "regroup_damage_car", "targetname" );
	foreach( location in damage_locations )
	{
		radiusdamage( location.origin, 64, 250, 150 );
		wait( randomfloatrange( 0, 2 ) );
	}
}

regroup_rpg_scripted( rocket_target )
{
	self endon( "death" );
	self.awareness = 1;
	self disable_awareness();
	self thread deletable_magic_bullet_shield();
    self.old_weapon = self.weapon;
    self forceUseWeapon( "rpg" , "primary" );

    self waittill("goal");
    self set_ignoreSuppression( true );
    self setstablemissile( true );
    self setentitytarget( rocket_target );
    attractor = missile_createattractororigin( rocket_target.origin, 5000, 5000 );
    self.maxSightDistSqrd = 8192 * 8192;
    wait .1;    
	self shoot( 1, rocket_target.origin );
	self thread stop_magic_bullet_shield();
    wait 2;
    self enable_awareness();
    self ClearEntityTarget(); 
    self forceUseWeapon( self.old_weapon , "primary" );
    self.script_forcegoal =0;
}

wait_for_player_to_look( guys )
{
	for ( i = 0; i < guys.size; i++ )
	{
		guys[ i ] add_wait( ::waittill_player_lookat_for_time, 0.3 );
	}

	do_wait_any();
}


background_trees_visibility()
{
	ents = GetEntArray( "india_hillside_trees_hide", "targetname" );
	array_call( ents, ::hide );
	
	flag_wait( "india_hillside_trees_show" );
	array_call( ents, ::show );
}


background_hillside_visibility( show )
{
	ents = getentArray( "india_hillside_mountian_hide", "targetname" );
	
	if( isdefined( show ) )
		array_call( ents, ::show );
	else
		array_call( ents, ::hide );
}

////////////////////////
//---- UAV ATTACK ----//
////////////////////////
/*
uav_attack_fire_pass()
{
	flag_wait("uav_attack_intro_fire");
	uav_spawner = getent( "uav_attack_uav_attacker", "targetname" );
	uav = uav_spawner spawn_vehicle_and_gopath();
	
	flag_wait( "uav_attack_uav_fire" );
	target1 = getent( "uav_attack_uav_attacker_target1", "targetname" );
	target1 thread uav_attack_target1_monitor();
	uav thread uav_fire_missiles( target1, 1, .25, true);
	wait(.25);
	target2 = getent( "uav_attack_uav_attacker_target2", "targetname" );
	target2 thread uav_attack_target2_monitor();
	uav thread uav_fire_missiles( target2, 1, .25, true);
	wait(5);
	thread uav_attack_patrol();
}

uav_attack_target1_monitor()
{
	self waittill( "death" );
	//hint( "building HIT", 2 );
	playfx( getfx( "slamraam_explosion" ) , self.origin );
	earthquake(.8, 3, self.origin, 1024);
	level.player playrumbleonentity( "artillery_rumble" );
	
	building = GetEntArray( "junkyard_area_building_03_destruction", "targetname" );
	foreach( piece in building )
	{
		piece hide_notsolid();
	}
	
	supports = GetEntArray( "junkyard_area_building_03_destruction_supports", "targetname" );
	foreach( piece in supports )
	{
		piece hide_notsolid();
	}
}

uav_attack_target2_monitor()
{
	self waittill( "death" );
	//hint( "tree HIT", 2 );
	tree = getent( "uav_attack_tree_fall", "targetname" );
	thread object_fall_gravity(tree, 4);
	level.player playrumbleonentity( "artillery_rumble" );
}


uav_attack_patrol()
{
	volumes =  getEntArray( "uav_attack_patrol_player_vol", "targetname" );
	
	while( !flag( "uav_attack_second_run" ) )
	{
		uav_spawner = getent( "uav_attack_uav_patrol", "targetname" );
		if( uav_spawner.count <= 0 )
			uav_spawner.count = 1;
		uav = uav_spawner spawn_vehicle_and_gopath();
		flag_wait( "uav_attack_uav_patrol_fire" );
		if( check_volumes( volumes ) )
		{
			uav thread uav_fire_missiles( level.player, randomintrange( 1, 4 ), .25);
		}
		flag_wait( "uav_attack_uav_patrol_remove" );
		flag_clear( "uav_attack_uav_patrol_fire" );
		flag_clear( "uav_attack_uav_patrol_remove" );
		wait(randomint(5));
		
	}
}

uav_attack_second_run()
{
	flag_wait( "uav_attack_second_run" );
	volumes =  getEntArray( "uav_attack_second_run_player_vol", "targetname" );
	
	while( !flag( "maars_control_player_controlling_maars" ) )
	{
		uav_spawner = getent( "uav_attack_second_run", "targetname" );
		if( uav_spawner.count <= 0 )
			uav_spawner.count = 1;
		uav = uav_spawner spawn_vehicle_and_gopath();
		flag_wait( "uav_attack_second_run_fire" );
		if( check_volumes( volumes ) )
		{
			uav thread uav_fire_missiles( level.player, randomintrange( 1, 4 ), .25);
		}
		flag_wait( "uav_attack_second_run_remove" );
		flag_clear( "uav_attack_second_run_fire" );
		flag_clear( "uav_attack_second_run_remove" );
		wait(randomint(2));
	}
}

*/
///////////////////////////
//---- MAARS SHED ----//
///////////////////////////

maars_control_door()
{
	
	
	//anim_pos = getstruct( "maars_control_open_door", "targetname" );
	
	//anim_pos anim_reach_solo( level.price, "maars_control_open_door" );
	
	//anim_pos anim_single_solo( level.price, "maars_control_open_door" );
	
	maars_control_intro();
	//level.price enable_ai_color();
}

maars_control_door_open()
{
	self rotateto( self.angles + ( 0, 20, 0 ), .75, .5, 0 );
	wait .75;
	self rotateto( self.angles + ( 0, 70, 0 ), 1, 0, .75 );
	self ConnectPaths();
}

maars_control_door_close()
{
	flag_wait( "maars_control_player_controlling_maars" );
	self.angles -= ( 0, 90, 0 );
	self disconnectPaths();
}

maars_control_intro()
{
	door = getent( "maars_control_door", "targetname" );

	door thread maars_control_door_close();
	
	anim_pos = GetStruct( "maars_control_maars_intro", "targetname" );
	
	spawn_ugv_vehicle();
	
	//setup initial models
	trap_door = spawn_anim_model( "trap_door", ( 0, 0, 0 ) );
	crate_door = spawn_anim_model( "crate_door", ( 0, 0, 0 ) );
	rolling_door = spawn_anim_model( "rolling_door", ( 0, 0, 0 ) );
	
 
	anim_pos anim_first_frame_solo( trap_door, "intro_weapon_cache_start" );
	anim_pos anim_first_frame_solo( crate_door, "intro_weapon_cache_pullout" );
	
	anim_pos anim_first_frame_solo( rolling_door, "intro_weapon_cache_end" );
	
	trigger = getent( "maars_control_idle_door_trigger", "targetname" );
	trigger waittill( "trigger" );
	level.price disable_ai_color();
	level.price pushplayer( true );
	anim_pos anim_reach_solo( level.price, "intro_weapon_cache_upto_shed" );
	
	flag_set( "maars_shed_price_at_door" );
	
	anim_pos anim_single_solo( level.price, "intro_weapon_cache_upto_shed" );
	
	anim_pos thread anim_loop_solo( level.price, "intro_weapon_cache_upto_shed_idle", "end_idle" );
	
	flag_wait( "maars_control_open_door_trigger" );
	
	anim_pos notify( "end_idle" );
	
	flag_set( "maars_control_start_intro" );
	
	//anim_pos anim_reach_solo( level.price, "intro_weapon_cache_start" );
	
	flag_set( "maars_control_reinforcements" );

	//models in anim 
	level.flashlight = spawn_anim_model( "flashlight", ( 0, 0, 0 ) );
	crowbar = spawn_anim_model( "crowbar", ( 0, 0, 0 ) );
	
	actors = [];
	actors[ 0 ] = [ level.price, 0 ];
	actors[ 1 ] = [ level.flashlight, 0 ];
	actors[ 2 ] = [ trap_door, 0 ];

	//delaythread( 4, ::maars_control_trap_door_open );

	thread maars_control_player_clip_move();
	door delaythread( .5, ::maars_control_door_open );
	//tell player to get on ugv
	anim_pos anim_single_end_early( actors, "intro_weapon_cache_start" );
	
	actors_idle = make_array ( level.price, level.flashlight );
	anim_pos thread anim_loop( actors_idle, "intro_weapon_cache_stairs_idle", "end_idle" );
	
	flag_wait( "maars_control_player_down_stairs" );
	
	prep_cinematic( "ugv_startup" );
	
	anim_pos notify( "end_idle" );
	
	actors = [];
	actors[ 0 ] = [ level.price, 0 ];
	actors[ 1 ] = [ crowbar, 0 ];
	actors[ 2 ] = [ crate_door, 0 ];
	actors[ 3 ] = [ level.ugv_model, 0 ];
	actors[ 4 ] = [ level.flashlight, 0 ];
	
	delaythread( 12, ::flag_set, "maars_control_dialog_ugv_intro" );
	delaythread( 10, ::maars_control_move_ugv_clip );
	level.price thread  multiple_dialogue_queue( "intro_weapon_cache_pullout_face" );
	anim_pos anim_single_end_early( actors, "intro_weapon_cache_pullout" );
	
	
	flag_set( "player_to_maars_control" );
	
	actors_idle = make_array ( level.price, level.flashlight );
	anim_pos thread anim_loop( actors_idle, "intro_weapon_cache_idle", "end_idle" );
 	
	flag_wait( "maars_control_player_controlling_maars" );
	thread maars_control_regroup_enemy_cleanup();
	
	
	flag_wait( "maars_control_boot_up_fading" );
	//player is controlling ugv, open door
	anim_pos notify( "end_idle" );
	aud_send_msg("maars_garage_door_opening");
	delaythread( 4, ::maars_control_garage_door_open );
	actors_end = make_array ( level.price, level.flashlight, rolling_door  );
	anim_pos anim_single( actors_end, "intro_weapon_cache_end" );
	level.flashlight delete();
	crowbar delete();

	anim_pos thread anim_loop_solo( level.price, "intro_weapon_cache_end_idle", "end_idle" );
	
	flag_wait( "maars_control_player_out_of_weapons_cache" );
	anim_pos notify( "end_idle" );
	
	level.price enable_ai_color();
	level.price pushplayer( false );
	level.price disable_cqbwalk();
	level.price remove_grenades();
	trigger = getent( "maars_control_price_color", "targetname" );
	trigger notify( "trigger" );
}

maars_control_move_ugv_clip()
{
	movetime = 1;
	clip = getent( "maars_control_box_player_clip", "targetname" );
	move_loc = getstruct( "maars_control_maars_pullout_collision", "targetname" );
	clip moveto( move_loc.origin, movetime, 0, 0 );
}


maars_control_player_clip_move()
{
	wait 2;
	movetime = 4;
	clip = getent( "maars_control_trap_door_col", "targetname" );
	move_loc = getstruct( "maars_control_player_clip_moveto", "targetname" );
	clip moveto( move_loc.origin, movetime, 0, 0 );
	
	wait movetime + 7;
	
	clip delete();
	
}


spawn_ugv_vehicle()
{
	level.ugv_vehicle = spawn_vehicle_from_targetname( "player_ugv_robot" );
	// ugv vehicle init waits for a frame end
	waittillframeend;
	level.ugv_vehicle maps\intro_maars::hide_maars_vehicle();
	
	level.ugv_model = spawn_anim_model( "ugv_model", ( 0, 0, 0 ) );
	level.ugv_model.animname = "ugv_model";
	level.ugv_model.origin = level.ugv_vehicle.origin;
	level.ugv_model.angles = level.ugv_vehicle.angles;
}

///////////////////////////
//---- MAARS CONTROL ----//
///////////////////////////

maars_control_activate_maars()
{
	flag_wait( "player_to_maars_control" );
	flag_set( "obj_control_ugv" );
	flag_wait( "maars_control_player_controlling_maars" );
	aud_send_msg("player_maars_interact_start");
	flag_set( "obj_clear_helicopter_area" );
}

maars_control_maars_setup()
{
	laptop_position = getstruct( "maars_control_mount_zoom_to", "targetname" );
	
	flag_wait( "player_to_maars_control" );
	
	level.ugv_vehicle thread maars_control_maars_setup_cleanup( laptop_position );
	level.ugv_vehicle MakeUnusable();
	
	wait_for_trigger_use_maars();
	level.player enableinvulnerability();
	aud_send_msg("maars_computer_boot_up");
	thread background_hillside_visibility();
	
	setsaveddvar("sm_spotlightscoremodelscale", "1");
	
	setsaveddvar("cg_cinematicFullScreen", "0");
	cinematicingame( "ugv_startup" );
	
	flag_set( "maars_control_player_controlling_maars" );
	flag_set( "maars_fail_on_death" );
	
	box_col = getent( "maars_control_box_clip", "targetname" );
	box_col delete();
	
	clip = getent( "maars_control_box_player_clip", "targetname" );
	clip delete();
	thread vision_set_fog_changes("intro_maars_control",2);
	
	
	level.ugv_vehicle maps\intro_maars::mount_maars( level.ugv_model, laptop_position );
	level.player disableinvulnerability();
	//wait( 2 );
	autosave_by_name_silent( "maars_control" );
}

wait_for_trigger_use_maars()
{
	trigger_use_maars = GetEnt( "trigger_use_maars", "targetname" );
	trigger_use_maars SetHintString( &"INTRO_USE_UGV" );
	trigger_use_maars UseTriggerRequireLookAt();
	
	trigger_use_maars thread enable_trigger_on_flag( "enable_mount_maars_trigger" );
	trigger_use_maars waittill( "trigger" );
	trigger_use_maars trigger_off();
}

enable_trigger_on_flag( enable_flag )
{
	self endon( "trigger" );
	
	while ( true )
	{
		self trigger_off();
		flag_wait( enable_flag );
		self trigger_on();
		flag_waitopen( enable_flag );
	}
}

maars_control_setup_allied_targets()
{
	flag_wait( "maars_control_player_controlling_maars" );
}

maars_control_trap_door_open()
{
	maars_trap_door = GetEnt( "maars_control_trap_door_col", "targetname" );
	maars_trap_door Delete();
}

maars_control_garage_door_open()
{
	maars_garage_door = GetEnt( "maars_garage_door_col", "targetname" );
	aud_send_msg("maars_control_door_open", maars_garage_door );
	maars_garage_door ConnectPaths();
	maars_garage_door Delete();
	flag_set( "maars_control_door_open" );
}

maars_control_maars_setup_cleanup( laptop_position_struct )
{
	flag_wait( "maars_control_uav_complete" );
	
	self thread maps\intro_maars::dismount_maars( level.ugv_model, laptop_position_struct );
}

maars_control_combat()
{
	thread maars_control_threat_groups();
	thread maars_control_player_threat();
	level.maars_control_drones = [];
	level.maars_control_building_runner_dead = 0;
	
	level.maars_control_spawn1_dead = 0;
	level.maars_control_end_enemies_dead = 0;
	level.maars_control_end_enemies_to_kill = 15;
	
	//friendlies at the gate
	array_spawn_function_targetname( "maars_control_friendly_drone", ::maars_control_spawner_setup_allied_drone );
	array_spawn_function_targetname( "maars_control_friendly_target", ::maars_control_spawner_setup_allied );
	
	//recreate the gate scene
	array_spawn_function_targetname( "maars_control_initial_mg_turret", ::mg_guy_think_maars_control, "maars_control_player_attacked_runner", "maars_control_mg_gunner_initial_detach" );
	array_spawn_function_targetname( "maars_control_initial_mg_turret", ::maars_control_mg_guy  );
	
	
	array_spawn_function_noteworthy( "maars_control_initial_runner", ::maars_control_building_runner );
	
	
	//mg turrets for the end of the section
	array_spawn_function_targetname( "maars_control_mg_gunner", ::mg_guy_think_maars_control  );
	array_spawn_function_targetname( "maars_control_mg_gunner", ::maars_control_spawner_setup );
	array_spawn_function_targetname( "maars_control_mg_gunner2", ::mg_guy_think_maars_control);
	array_spawn_function_targetname( "maars_control_mg_gunner2", ::maars_control_spawner_setup );
	
	//spawners throughout the section
	array_spawn_function_targetname( "maars_control_spawn1", ::maars_control_spawner_setup );
	array_spawn_function_targetname( "maars_control_spawn1", ::maars_control_spawn1_monitor );
	array_spawn_function_targetname( "maars_control_spawn2_a", ::maars_control_spawner_setup );
	array_spawn_function_targetname( "maars_control_spawn2", ::maars_control_spawner_setup );
	array_spawn_function_targetname( "maars_control_spawn3", ::maars_control_spawner_setup );
	array_spawn_function_targetname( "maars_control_spawn4", ::maars_control_spawner_setup );
	array_spawn_function_targetname( "maars_control_spawn5", ::maars_control_spawner_setup );
	
	//Setup end enemies to stop spawning after so many kills so the player can thin out the area
	array_spawn_function_targetname( "maars_control_spawn5", ::maars_control_end_enemies );
	array_spawn_function_targetname( "maars_control_mg_gunner2", ::maars_control_end_enemies );
	thread maars_control_end_enemies_monitor();
	
	
	//Spawn initial gate figthers
	flag_wait( "maars_control_door_open" );
	
	array_spawn_targetname( "maars_control_friendly_target" );
	array_spawn_targetname( "maars_control_friendly_drone", true );
	array_spawn_targetname( "maars_control_initial_runner", true );
	array_spawn_targetname( "maars_control_initial_mg_turret", true );
	
	
	while( 1 ) 
	{
		if( level.maars_control_building_runner_dead > 5 )
		{
			break;
		}
		wait( .1 );
	}
	
	//spawn group1
	spawn_trigger = getent( "maars_control_spawn1_trigger", "targetname" );
	//might have already been triggered
	if( isdefined( spawn_trigger ) )
	{
		spawn_trigger notify( "trigger" );
	}
	
	while( 1 ) 
	{
		if( level.maars_control_spawn1_dead > 5 )
		{
			flag_set( "maars_control_spawn1_retreat" );
			break;
		}
		
		wait( .1 );
	}
	
	//spawning the second group of guys who are flood spawned.  Useing the trigger so we can either wait for the dead guys or the player to move up.
	spawn_trigger = getent( "maars_control_spawn2_trigger", "script_noteworthy" );
	//might have already been triggered
	if( isdefined( spawn_trigger ) )
	{
		spawn_trigger notify( "trigger" );
	}
}

//Basic setup for guys being killed by UGV
maars_control_spawner_setup()
{
	self endon( "death" );
	//self thread maps\intro_maars::maars_add_target();
	self thread disable_long_death();
	self.dontmelee = true;
	self.dropweapon = false;
	self.favoriteenemy = level.player;
	self setthreatbiasgroup( "maars_enemies" );
	self.deathFunction = ::maars_control_enemy_death_anim;
	self remove_grenades();
	if( !isDefined( level.player_ugv_target ) )
		maars_control_enemy_target();
	self SetEntityTarget( level.player_ugv_target );
}

maars_control_enemy_target()
{
	org = level.ugv_vehicle.mgturret[0] gettagorigin( "tag_barrel" );
	
	level.player_ugv_target = spawn( "script_origin", org + ( 0, 0, 10 ) );
	level.player_ugv_target linkTo( level.ugv_vehicle.mgturret[0] );
}

//Basic setup for Turret guys so they don't have there other settings clobbered
maars_control_mg_guy()
{
	thread maars_control_building_runner_monitor_damage();
	self setthreatbiasgroup( "maars_enemies" );
	self.dropweapon = false;
	self remove_grenades();
}

//Basic setup for initial gate fighters who should ignore the player at first but be firing at the gate
maars_control_building_runner()
{	
	self endon( "death" );

	thread maars_control_building_runner_monitor_damage();
	thread maars_control_building_runner_monitor_death();
	self thread disable_long_death();
	self.dontmelee = true;
	self.dropweapon = false;
	self.favoriteenemy = level.player;
	self setthreatbiasgroup( "maars_enemies" );
	self.deathFunction = ::maars_control_enemy_death_anim;
	
	if( !flag( "maars_control_player_attacked_runner" ) )
	{
		targets = GetEntArray( "maars_control_initial_spawn_target", "targetname" );
		self SetEntityTarget( random( targets ) );
	}
	
	flag_wait( "maars_control_player_attacked_runner" );
	self clearentitytarget();
	self SetEntityTarget( level.ugv_vehicle );
	
}

//Tells initial enemies to shoot at the player since the player has shoot someone
maars_control_building_runner_monitor_damage()
{
	self waittill( "damage", damage_amount, attacker );
	if ( attacker == level.player )
		flag_set( "maars_control_player_attacked_runner");
}

maars_control_building_runner_monitor_death()
{
	self waittill( "death" );
	level.maars_control_building_runner_dead ++;
}

//Allowing initial enemies to shoot at the player once they shoot or cross a threshold
maars_control_player_threat()
{
	flag_wait( "maars_control_player_attacked_runner" );
	level.player setthreatbiasgroup();
}

//one friendly at the gate so the enemies shoot at him and make it seem like the battle is still going...  Can probably do this a different way
maars_control_spawner_setup_allied()
{
	self.grenadeammo = 0;
	self thread magic_bullet_shield();
	//self thread maps\intro_maars::maars_add_target();	
	flag_wait( "maars_control_player_out_of_weapons_cache" );
	
	self stop_magic_bullet_shield();
}

//basically flood spawn drones at the gate
maars_control_spawner_setup_allied_drone()
{
	level endon( "maars_control_player_out_of_weapons_cache" );
	spawner = self.spawner;
	self set_ai_number();
	//self thread maps\intro_maars::maars_add_target();
	self waittill( "death" );
	spawner spawn_ai();
}

//Threat groups so the player and friends are not shot while they are in the maars control shed.
maars_control_threat_groups()
{
	createthreatbiasgroup( "friendly_group" );
	createthreatbiasgroup( "maars_enemies" );
	
	level.price setthreatbiasgroup( "friendly_group" );
	level.nikolai setthreatbiasgroup( "friendly_group" );
	level.player setthreatbiasgroup( "friendly_group" );
	setignoremegroup( "friendly_group", "maars_enemies" );	
}

//Tracking end enemy deaths
maars_control_end_enemies()
{
	self waittill( "death" );
	
	level.maars_control_end_enemies_dead++;
}

maars_control_end_enemies_monitor()
{
	while( level.maars_control_end_enemies_dead < level.maars_control_end_enemies_to_kill )
	{
		wait .1;
	}
	flag_set( "maars_control_end_enemies_dead" );
	wait 15;
	thread maps\_spawner::killspawner( 205 );
}

//Tracking first spawners so they know when to move back
maars_control_spawn1_monitor()
{
	spawner = self.spawner;
	self waittill( "death" );
	
	level.maars_control_spawn1_dead ++;
}

maars_control_enemy_death_anim()
{
	if ( IsDefined( self.attacker ) && self.attacker == level.player && self.damagetaken > 150 )
	{
		deathAnim = animscripts\death::getStrongBulletDamageDeathAnim();
		if ( IsDefined( deathAnim ) )
		{
			self.deathAnim = deathAnim;
		}
	}
	
	// continue thru normal animscript either way
	return false;
}


//Smoke sequence
maars_control_smoke()
{
	level endon( "maars_control_smoke_off" );
	Assert( !flag( "maars_control_smoke_off" ) );
	
	flag_wait( "maars_control_smoke_on" );
	
	magic_smoke_grenades = GetStructArray( "magic_smoke_grenade", "targetname" );
	
	foreach ( magic_smoke_grenade in magic_smoke_grenades )
	{
		smoke_pos = magic_smoke_grenade.origin;
		thread maps\intro_fx::maars_control_smk_grenade();
		thread play_sound_in_space( "smokegrenade_explode_default", smoke_pos );
	}
}


//MAARS CONTROL HELICOPTERS
maars_control_helicopters()
{
	thread maars_control_transport_helicopters();
	thread maars_control_attack_helicopters();
	
	little_bird = getent( "maars_control_littlebird", "targetname" );
	//little_bird = little_bird_spawner spawn_vehicle();
	little_bird hidepart("main_rotor_jnt");
	little_bird hidepart("tail_rotor_jnt");
	//little_bird thread maps\intro_maars::maars_add_target();
}

maars_control_transport_helicopters()
{
	array_spawn_function_noteworthy( "maars_control_helicopter_enemies", ::maars_control_spawner_setup );
	flag_wait( "maars_control_mi17_1" );
	heli_spawn = getEnt( "maars_control_mi17_1", "targetname" );
	heli = heli_spawn spawn_vehicle_and_gopath();
	heli thread maars_control_helicopter_achievement_watcher();
	aud_send_msg("maars_transport_chopper", heli);
	heli.script_bulletshield = 0;
	heli thread maps\intro_maars::maars_add_target( "vehicle_mi17_woodland_ugv_hitbox" );
	
	flag_wait( "maars_control_mi17_1" );
	heli_spawn2 = getEnt( "maars_control_mi17_2", "targetname" );
	heli2 = heli_spawn2 spawn_vehicle_and_gopath();
	heli2 thread maars_control_helicopter_achievement_watcher();
	aud_send_msg("maars_transport_chopper", heli2);
	heli2.script_bulletshield = 0;
	heli2 thread maps\intro_maars::maars_add_target( "vehicle_mi17_woodland_ugv_hitbox" );
}

maars_control_attack_helicopters()
{
	mi28_4_spawn = getEnt( "maars_control_mi28_4", "targetname" );
	mi28_4 = mi28_4_spawn spawn_vehicle_and_gopath();
	mi28_4 thread maars_control_helicopter_achievement_watcher();
	aud_send_msg("maars_attack_chopper", mi28_4);
	
	mi28_4 thread maps\intro_maars::maars_add_target( "vehicle_mi-28_ugv_hitbox" );
	mi28_4 thread maars_control_mi28_4();
	mi28_4 thread maars_control_mi28_4_monitor_death();
	mi28_4 thread maars_control_mi28_4_detour();
	mi28_4 SetMaxPitchRoll( 5, 20 );
	
	flag_wait( "maars_control_mi28_1" );
	heli_spawn = getEnt( "maars_control_mi28_1", "targetname" );
	heli_1 = heli_spawn spawn_vehicle_and_gopath();
	heli_1 thread maars_control_helicopter_achievement_watcher();
	aud_send_msg("maars_attack_chopper", heli_1);
	heli_1 thread maps\intro_maars::maars_add_target( "vehicle_mi-28_ugv_hitbox" );
	heli_1 thread maars_control_mi28_1_attack();
	heli_1 SetMaxPitchRoll( 15, 20 );

	flag_wait( "maars_control_mi28_3" );
	wait 5;
	heli_spawn = getEnt( "maars_control_mi28_3", "targetname" );
	heli_3 = heli_spawn spawn_vehicle_and_gopath();
	heli_3 thread maars_control_helicopter_achievement_watcher();
	aud_send_msg("maars_attack_chopper", heli_3);
	heli_3 thread maps\intro_maars::maars_add_target( "vehicle_mi-28_ugv_hitbox" );
	heli_3 thread maars_control_mi28_3_attack();
	heli_3 SetMaxPitchRoll( 15, 20 );
}

maars_control_helicopter_achievement_watcher()
{
	hit_by_non_grenade = self maars_control_helicopter_return_when_hit_by_non_grenade();
	
	if ( IsDefined( hit_by_non_grenade ) && hit_by_non_grenade )
	{
		return;
	}
	
	if(!IsDefined(level.maars_control_helicopter_death_count))
	{
		level.maars_control_helicopter_death_count = 0;
	}
	level.maars_control_helicopter_death_count++;
	
	if(level.maars_control_helicopter_death_count == 5)
	{
		level.player thread player_giveachievement_wrapper( "WHAT_GOES_UP" );
	}
}

maars_control_helicopter_return_when_hit_by_non_grenade()
{
	// self is the helicopter
	// if we get death message first, we will return undefined
	self endon ( "death" );
	
	while ( true )
	{
		self waittill("damage", amount, attacker, direction_vec, point, type, modelname, tagName, partName, dflags, weapon);
		if ( IsDefined( attacker ) && attacker == level.player )
		{
			if ( !IsDefined( weapon ) || !IsSubstr( weapon, "m203" ) )
			{
				return true;			
			}
		}
	}		
}

maars_control_mi28_4()
{
	self endon( "death" );
	
	target = getstruct( "maars_control_mi28_4_target", "targetname" );
	
	while( !flag( "maars_control_player_attacked_runner" ) )
	{
		self heli_fire_turret( target, 50, .05 );
		wait randomIntrange( 2, 5 );
	}
	
	wait 3;//giving the player a little more time to see the helicopter
	
	if( !isDefined( level.player_mg_target ) )
		mg_player_target();
	
	//self setlookatent ( level.player_mg_target );
	
	while( !flag( "maars_control_mi28_4_detour" ) )
	{
		self heli_fire_turret( level.player_mg_target, randomIntrange( 20, 50 ), .05 );
		
		wait randomIntrange( 2, 5 );
	}
	
	//self clearlookatent();
	flag_wait( "maars_control_mi28_4_clear_to_crash" );
	self.script_crashtypeoverride = "helicopter";
	
	flag_wait( "maars_control_mi28_4_detour_complete" );
	 
	//self setlookatent ( level.player_mg_target );
	while( 1 )
	{
		self heli_fire_turret( level.player_mg_target, randomIntrange( 50, 75 ), .05 );
		wait randomIntrange( 1, 2 );
	}
}

maars_control_mi28_4_monitor_death()
{
	self waittill( "death" );
	
	if( flag( "maars_control_mi28_4_clear_to_crash" ) ) 
		return;
		
	self.crashing = true;
	self notify( "newpath" );
	crashLoc = getstruct( "maars_control_mi28_4_death_go_to", "targetname" );
	crash_speed = 60;
	self Vehicle_SetSpeed( crash_speed, 15, 10 );
	self SetNearGoalNotifyDist( crashLoc.radius );
	self SetVehGoalPos( crashLoc.origin, 0 );
	self waittill_any( "goal", "near_goal" );
	
	crashLoc = getstruct( crashLoc.target, "targetname" );
	self SetNearGoalNotifyDist( crashLoc.radius );
	self SetVehGoalPos( crashLoc.origin, 0 );
	self waittill_any( "goal", "near_goal" );
	
	self notify( "deathspin" );
	self thread maps\_vehicle::helicopter_crash_rotate();
	
	crashLoc = getstruct( crashLoc.target, "targetname" );
	self SetNearGoalNotifyDist( crashLoc.radius );
	self SetVehGoalPos( crashLoc.origin, 0 );
	self waittill_any( "goal", "near_goal" );
	
	self notify( "crash_done" );
	self notify( "stop_crash_loop_sound" );
	
}

maars_control_mi28_4_detour()
{
	self endon( "death" );
	flag_wait( "maars_control_mi28_4_detour" );
	detour_start_from = getstruct( "maars_control_mi28_4_detour", "script_noteworthy" );
	
	detour_start_from.target = "maars_control_mi28_4_detour_go_to";
}

maars_control_mi28_1_attack()
{
	self endon( "death" );
	flag_wait( "maars_control_mi28_start_firing" );
	
	if( !isDefined( level.player_mg_target ) )
		mg_player_target();
		
	self setlookatent ( level.player_mg_target );
	
	while( 1 )
	{
		self heli_fire_turret( level.player_mg_target, 50, .05 );
		wait randomIntrange( 2, 5 );
	}
	
}

maars_control_mi28_3_attack()
{
	self endon( "death" );
	flag_wait( "maars_control_mi28_3_fire1" );
	
	wait 3;
	
	if( !isDefined( level.player_mg_target ) )
		mg_player_target();
	
	self setlookatent ( level.player_mg_target );
	
	while( 1 )
	{
		if( cointoss() )
		{
			self heli_fire_turret( level.player_mg_target, 25, .05 );
			wait randomIntrange( 3, 5 );
		}
		else
		{
			thread maps\intro_maars::maars_incoming_missile();
			wait .5;
			self heli_fire_missiles( level.ugv_vehicle, 2, .25, "viper_tow_intro" );
			wait randomIntrange( 3, 5 );
		}
	}
}

//Ending timing and sequencing when player is at the helicopter
maars_control_ending_sequence()
{
	flag_wait( "maars_control_player_at_helicopter" );
	flag_set( "maars_control_price_at_chopper" );
	
	flag_wait( "maars_control_soap_at_helicopter" );
	flag_clear( "maars_fail_on_death" );
	thread maps\_spawner::killspawner( 205 );
	flag_set( "maars_control_uav_start_dialog" );
	flag_wait( "maars_control_drone_inbound" );
	thread maps\intro_maars::maars_incoming_missile();
	aud_send_msg("maars_control_drone_inbound");
	flag_wait( "maars_control_uav_start" );
	maars_control_ending();
	flag_wait( "maars_control_uav_complete" );
	thread maars_control_enemy_cleanup();
	flag_set( "obj_clear_helicopter_area_complete" );
}

maars_control_ending()
{
	level.ugv_vehicle notify( "start_ugv_death" );
	thread vision_set_fog_changes("intro_shack_yard",1);
	uav = spawn_anim_model( "uav", ( 0, 0, 0 ) );
	uav.animname = "uav";
	uav setanimtree();
	aud_send_msg("uav_kill_maars", uav);
	aud_send_msg("mus_ugv_destroyed");

	setsaveddvar("sm_spotlightscoremodelscale", "0");

	missileHitOrg = playerFovGroundSpot();
	playFX( level._effect[ "mortar" ][ "dirt" ], missileHitOrg );
	
	thread play_sound_in_space( "clusterbomb_explode_default", missileHitOrg );
	level.player PlayRumbleOnEntity( "artillery_rumble" );

	// figure out where tag_player will be at the start of the anim
	level.ugv_vehicle maps\intro_maars::hide_maars_vehicle();
	
	// spawn separate ugv and turret, and don't link them!
	player_angles = level.player GetPlayerAngles();
	
	death_ugv = spawn_anim_model( "ugv" );
	death_ugv.origin = level.ugv_vehicle.origin;
	death_ugv.angles = level.ugv_vehicle.angles;
	death_ugv.angles = ( death_ugv.angles[0], player_angles[1], death_ugv.angles[2] );
	death_ugv anim_first_frame_solo( death_ugv, "ugv_death_pos" );
	
	death_ugv_turret = spawn_anim_model( "ugv_turret", (0,0,0) );
	death_ugv_turret.origin = death_ugv GetTagOrigin( "tag_gun" );
	death_ugv_turret.angles = death_ugv GetTagAngles( "tag_gun" );
	death_ugv_turret anim_first_frame_solo( death_ugv_turret, "ugv_death_pos" );
	
	death_ugv_grenade_launcher = spawn_anim_model( "ugv_grenade_launcher", (0,0,0) );
	
	// preserve grenade state from intro_maars
	for ( hide_ammo = 7; hide_ammo >= level.ugv_vehicle.m203_rounds_left; hide_ammo-- )
	{
		i = hide_ammo + 3;//hides the rounds so we can see all but the chambered round
		death_ugv_grenade_launcher hidepart( "ammo" + i );
	}
	
	start_org = death_ugv_turret GetTagOrigin( "tag_player" );
	start_angles = death_ugv_turret GetTagAngles( "tag_player" );
	
	death_anim_org = SpawnStruct();
	death_anim_org.origin = start_org;
	death_anim_org.angles = start_angles;

	level.player DisableWeapons();
	level.ugv_vehicle.mgturret[0] SetTurretDismountOrg( start_org );
	level.ugv_vehicle maps\intro_maars::detach_player_from_turret();
	level.player PlayerLinkToDelta( death_ugv_turret, "tag_player", 1, 0, 0, 0, 0, true );
	
	guys = [];
	guys[ 0 ] = uav;
	guys[ 1 ] = death_ugv;
	guys[ 2 ] = death_ugv_turret;
	guys[ 3 ] = death_ugv_grenade_launcher;

	guys thread maps\intro_fx::maars_ugv_damage_death();
	level.player notify( "maars_player_damage_disable" );
	level.player DigitalDistortSetParams( .76, 1.48 );
	level.player thread maps\intro_maars::maars_interface_disable_death_anim();
	death_anim_org anim_single( guys, "ugv_death" );

	flag_set( "maars_control_uav_complete" );
	uav delete();
	
	level waittill( "dismount_maars" );
	death_ugv delete();
	death_ugv_turret delete();
	death_ugv_grenade_launcher delete();
}
	
	
//Removing enemies from regroup section	
maars_control_regroup_enemy_cleanup()
{
	drones = GetEntArray( "regroup_spawners13_drones", "script_noteworthy" );
	if( isdefined( drones ) )
		array_thread( drones, ::self_delete );
		
	maps\_spawner::killspawner( 13 );
	enemies = getaiarray( "axis" );
	array_thread( enemies, ::self_delete );
}

//End cleanup before the run
maars_control_enemy_cleanup()
{
	enemies = getaiarray( "axis" );
	array_thread( enemies, ::self_delete );
}

maars_control_carry_soap()
{
	traversal_blocker = getent( "maars_control_traversal_blocker", "targetname" );
	traversal_blocker notsolid();
	traversal_blocker connectPaths();
	flag_wait( "maars_control_player_controlling_maars" );
	
	//teleporting soap and nikolai into basement because they can't path there.
	wounded_node = getnode( "regroup_soap_wounded_put_down7", "targetname" );
	maars_control_nikolai_teleport = getstruct( "maars_control_nikolai_teleport", "targetname" );
	level.nikolai maps\intro_carry::teleport_carrier_and_wounded( level.soap, wounded_node, maars_control_nikolai_teleport );
	level.carry_then_idle = true;
	
	flag_wait( "maars_control_soap_wounded_put_down5" );
	
	flag_wait( "maars_control_end_enemies_dead" );
	
	traversal_blocker solid();
	traversal_blocker disconnectPaths();
	
	
	level.carry_then_idle = undefined;
	level.nikolai notify( "stop_carry_by_color" );
	thread soap_wounded_nikolai_carry( "maars_control_soap_wounded_put_down5" ); 
	thread maars_control_load_helicopter_price();
	
}

//Retreat for guys throughout the sequence
maars_control_retreat()
{
	triggers = GetEntArray( "maars_control_retreat", "targetname" );
	array_thread( triggers, ::maars_control_retreat_monitor_trigger );
}

maars_control_retreat_monitor_trigger()
{
	self waittill( "trigger" );
	
	vol = getent( self.target, "targetname" );
	retreat_pos = getstruct( vol.target, "targetname" );
	
	guys = vol get_ai_touching_volume( "axis" );
	
	retreat_to_node( guys ,retreat_pos );
}



building_slide_remove_player_clip()
{
	col = getent( "building_slide_player_clip", "targetname" );
	col notsolid();
}

maars_control_load_helicopter_price()
{
	flag_wait( "maars_control_loading_helicopter" );
	anim_pos = getstruct( "maars_control_load_helicopter", "targetname" );
	
	anim_pos anim_reach_solo ( level.price, "intro_ugv_helicopter" );
	anim_pos anim_single_solo ( level.price, "intro_ugv_helicopter" );
	anim_pos anim_loop_solo ( level.price, "intro_ugv_helicopter_idle", "end_idles" );
	
}

maars_control_monitor_background_hillside_visibility()
{
	flag_wait( "maars_control_hillside_show" );
	thread background_hillside_visibility( true );
}

maars_control_crate_top_collision( solid )
{
	clip = getent( "maars_control_box_clip_top", "targetname" );
	
	if( isdefined( solid ) )
		clip solid();
	else
		clip notsolid();
	
}

////////////////////////////
//---- BUILDING SLIDE ----//
////////////////////////////


building_slide_player_setup()
{
	level.player DisableOffhandWeapons();
	setsaveddvar( "player_sprintUnlimited", 1 );
	thread building_slide_run_tutorial();
	wait 1;
	autosave_by_name( "maars_control_complete" );
	thread maps\intro_fx::slide_fires();
	thread maps\intro_fx::slide_window_fires_explosions();
	aud_send_msg("mus_run_to_heli");
}

building_slide_spawn_player_clip()
{
	col = getent( "building_slide_player_clip", "targetname" );
	col solid();
}

building_slide_run_tutorial()
{
	// action names are different for xb and pc/ps3
	action_name = undefined;
	if ( level.Xenon )
		action_name = "sprint";
	else
		action_name = "sprint_pc";
	
	// end this if you already did the action without the tutorial
	notify_string = notify_on_action( action_name );
	level.player endon( notify_string );
	wait(1);
	// hint if you haven't pressed the correct button yet
	thread hint_for_action( action_name, undefined, true, notify_string );
}

building_slide_run()
{
	flag_wait( "building_slide_player_starting_run" );
	//wait( 2 );

	uav = thread building_slide_run_uav();

	thread building_slide_run_missiles( uav );
	
	src =  uav;
	//src = getent( "building_slide_run_src1", "targetname" );
	
	trigger = getent( "building_slide_run_trigger1", "targetname" );
	trigger building_slide_run_kill( 8, src );
	flag_set( "building_slide_missile1" );
	flag_set( "building_slide_missile2" );
	trigger = getent( "building_slide_run_trigger2", "targetname" );
	trigger building_slide_run_kill( 4, src );
	flag_set( "building_slide_missile3" );
	trigger = getent( "building_slide_run_trigger3", "targetname" );
	trigger building_slide_run_kill( 4, src);
	flag_set( "building_slide_missile4" );
	
	//src = getent( "building_slide_run_src2", "targetname" );
	trigger = getent( "building_slide_run_trigger4", "targetname" );
	trigger building_slide_run_kill( 4, src );
	flag_set( "building_slide_missile5" );
	trigger = getent( "building_slide_run_trigger5", "targetname" );
	trigger building_slide_run_kill( 4, src );
	flag_set( "building_slide_missile6" );
	flag_set( "building_slide_missile7" );	
	trigger = getent( "building_slide_run_trigger6", "targetname" );
	trigger building_slide_run_kill( 4, src );
	flag_set( "building_slide_missile8" );
	trigger = getent( "building_slide_run_trigger7", "targetname" );
	trigger building_slide_run_kill( 4, src );
	
}

building_slide_run_missiles( uav )
{
	flag_wait( "building_slide_missile2" );
	//src = getent( "building_slide_run_src1", "targetname" );
	src = uav;
	src_offset = ( 0, 0, -300 );
	target = getent( "building_slide_run_target2", "targetname" );
	target thread fire_fake_missile( src, "direct", "stinger_speedy_intro", src_offset );
	wait 1;
	flag_wait( "building_slide_missile1" );
	target = getent( "building_slide_run_target1", "targetname" );
	target thread fire_fake_missile( src, "direct", "stinger_speedy_intro", src_offset  );
	thread maps\intro_fx::slide_window_explosions();

	flag_wait( "building_slide_missile3" );
	target = getent( "building_slide_run_target3", "targetname" );
	target thread fire_fake_missile( src, "direct", "stinger_speedy_intro", src_offset  );
	
	flag_wait( "building_slide_missile4" );
	//src = getent( "building_slide_run_src2", "targetname" );
	target = getent( "building_slide_run_target4", "targetname" );
	target thread fire_fake_missile( src, "direct", "stinger_speedy_intro", src_offset  );
	flag_wait( "building_slide_missile5" );
	target = getent( "building_slide_run_target5", "targetname" );
	target thread fire_fake_missile( src, "direct", "stinger_speedy_intro", src_offset  );
	flag_wait( "building_slide_missile6" );
	target = getent( "building_slide_run_target6", "targetname" );
	target thread fire_fake_missile( src, "direct", "stinger_speedy_intro", src_offset  );
	wait 1;
	flag_wait( "building_slide_missile7" );
	target = getent( "building_slide_run_target7", "targetname" );
	target thread fire_fake_missile( src, "direct", "stinger_speedy_intro", src_offset  );
	wait 1;
	flag_wait( "building_slide_missile8" );
	target = getent( "building_slide_run_target7", "targetname" );
	target thread fire_fake_missile( src, "direct", "stinger_speedy_intro", src_offset  );
	
	
	
}

building_slide_run_uav()
{
	uav_spawner = getent( "building_slide_run_uav", "targetname" );
	uav = uav_spawner spawn_vehicle_and_gopath();
	return uav;
}

building_slide_run_kill( override_time, src )
{
	self endon( "trigger" );
	if( IsDefined( override_time ) )
	{
		wait( override_time );
	}else{	
		wait( 3 );
	}
	//thread building_slide_kill_player();
	self building_slide_try_to_kill_player( src );

}

building_slide_try_to_kill_player( src )
{
	self endon( "trigger" );
	
	while( 1 )
	{
		missileHitOrg = level.player.origin + ( randomintrange( -128, 128 ), randomintrange( -128, 128 ), 0 ); 
		detorg = spawn( "script_origin", missileHitOrg );
		//src thread uav_fire_missiles( detorg, 1, 0, "stinger_speedy_intro" );
		new_missile = detorg thread fire_fake_missile( src, "direct", "stinger_speedy_intro", ( 0, 0, -300 )  );
		level thread cleanup_target( new_missile, detorg );
		wait randomfloatrange( 1.5, 4);
	}
}


building_slide_kill_player()
{
	missileHitOrg = playerFovGroundSpot();
	playFX( level._effect[ "mortar" ][ "dirt" ], missileHitOrg );
	thread play_sound_in_space( "clusterbomb_explode_default", missileHitOrg );
	level.player PlayRumbleOnEntity( "artillery_rumble" );
	wait( .2 );
	level.player disableinvulnerability();
	level.player kill();
}
/*
building_slide_uav()
{
	uav = spawn_vehicle_from_targetname_and_drive( "building_slide_uav" );
	uav thread building_slide_uav_fire();
}

building_slide_uav_fire()
{
	flag_wait( "building_slide_uav_fire" );
	
	jav_start = getent("javelin_start_point","targetname");
	jav_end = GetEnt( "javelin_end_point", "targetname" );
	self uav_fire_missiles( jav_end, 3, .1, "cobra_seeker", true );
}
*/

fire_fake_missile( fakeJavLauncher, flightMode, override_missile_type, src_offset )
{	
	if( isdefined( override_missile_type ) )
	{
		missile_type = override_missile_type;
	}else{
		missile_type = "stinger_speedy_intro";
	}
	
	if( isdefined( src_offset ) )
	{
		newMissile = MagicBullet( missile_type, fakeJavLauncher.origin + src_offset, self.origin  );
		aud_send_msg("finale_missile_incoming", newMissile);		
	}
		
	else	
	{
   		newMissile = MagicBullet( missile_type, fakeJavLauncher.origin, self.origin );
		aud_send_msg("finale_missile_incoming", newMissile);		
	}
   		
    newMissile thread fire_fake_missile_earthquake( self ); 	//quake on impact
    newMissile Missile_SetTargetEnt( self );
   
   	self thread heli_target_monitor_missile_hit();
   	newMissile thread heli_missile_explode_when_close( self );
   
    if( missile_type == "javelin_berlin" )
    {
	    if( isDefined( flightmode ) && flightMode == "direct" )
	    {
	   	 	newMissile Missile_SetFlightmodeDirect();
	  	}
	  	else
	  	{
	  		newMissile Missile_SetFlightmodeTop();    	//top down kill mode for javelin
	  	}
  	}
  	
  	return newMissile;
}

fire_fake_missile_lores()
{
	//lo-res particles on the ps3 for 3 seconds - while the explosion is in view
	if(!isdefined(level.halfresfxon)) level.halfresfxon = 0;
	new_target = self.origin + (0,0,48);//
	to_target = (new_target-level.player.origin);
	to_target_l = length(to_target);
	to_target_n = vectornormalize(to_target);
	eye = vectornormalize(anglestoforward(level.player.angles));
	ratio = vectordot(to_target_n,eye);
	if(ratio>.3 && to_target_l<700)
	{
		if ( ( level.Console && level.ps3 ) || !level.Console )
		{
			SetHalfResParticles( true );
			level.halfresfxon ++;
		}
		wait 3;
		if ( ( level.Console && level.ps3 ) || !level.Console )
		{
			if(level.halfresfxon<2) SetHalfResParticles( false );
			level.halfresfxon --;
		}
	}
}

fire_fake_missile_earthquake( targetObj )
{
    dummy = spawn( "script_origin", self.origin );
    dummy linkto( self );
    self waittill( "death" );
    aud_send_msg("finale_missile_impact", dummy.origin);
	dummy thread fire_fake_missile_lores();
    //flag_set( "building_slide_building_hit" );
    earthquake( .3, .5, dummy.origin, 512 );
    //radiusdamage( targetObj.origin, 64, 25000, 25000 );
    wait( 0.05 );
    dummy delete();
}

uav_fire_missiles( eTarget, iShots, delay, customMissiles, force_hit_on_death )
{
	self endon( "death" );
	self endon( "heli_players_dead" );
	if ( IsDefined( self.defaultWeapon ) )
		defaultWeapon = self.defaultWeapon;
	else
		defaultWeapon = "cobra_seeker";
	weaponName = "cobra_seeker";
	if ( isdefined( customMissiles ) )
		weaponName = customMissiles;
	loseTargetDelay  = undefined;
	tags = [];
	self SetVehWeapon( defaultWeapon );
	if ( !isdefined( iShots ) )
		iShots = 1;
	if ( !isdefined( delay ) )
		delay = 1;
		
	created_ent = false;
	
	//if the target is a struct, need to spawn a dummy ent to fire at
	if ( !isdefined( eTarget.classname ) )
	{
		dummyTarget = Spawn( "script_origin", eTarget.origin );
		dummyTarget.ref_count = 0;
		level thread cleanup_target( self, dummyTarget );
		dummyTarget.targetname = eTarget.targetname;
		dummyTarget.origin = eTarget.origin;
		eTarget = dummyTarget;
		created_ent = true;
	}
	
	eTarget thread heli_target_monitor_missile_hit();

	loseTargetDelay  = 0.5;
	tags[ 0 ] = "tag_missile_right";
	tags[ 1 ] = "tag_missile_left";

	nextMissileTag = -1;

	for ( i = 0 ; i < iShots ; i++ )
	{
		nextMissileTag++;
		if ( nextMissileTag >= tags.size )
			nextMissileTag = 0;

		self SetVehWeapon( weaponName );
		self.firingMissiles = true;
		eMissile = self FireWeapon( tags[ nextMissileTag ], eTarget );
		aud_send_msg("uav_fire_missile", eMissile);
		if ( created_ent )
		{
			level thread manage_target_references( eTarget, eMissile );
		}
		eMissile thread heli_missile_explode_when_close( eTarget, force_hit_on_death );
		eMissile thread vehicle_scripts\_attack_heli::missile_earthquake();
		if ( i < iShots - 1 )
			wait delay;
	}
	self.firingMissiles = false;
	self SetVehWeapon( defaultWeapon );
	
	self notify( "done_firing_weapons" );
}

building_slide_building_hit()
{
	flag_set( "building_slide_building_hit" );
	vol = getent( "building_slide_vol", "targetname" );
	if( !level.player istouching( vol ) ) 
	{
  		thread building_slide_kill_player();
	}
	else
	{
		level.player enableinvulnerability();
	}
}

playerFovGroundSpot( )
{
	angles = level.player getplayerangles();
	
	angles = ( 0, angles[ 1 ], 0 );	//only use yaw component
	
	forward = anglestoforward( angles );
	right = anglestoright( angles );
	left = right * ( -1 );
	
	mineOrg = level.player.origin + forward * 96; //96 units ahead of player
	
	mineOrg = drop_to_ground( mineOrg, 200, -200 );
	return( mineOrg );
}

building_slide_begins()
{
	thread building_slide_anim();
	aud_send_msg("mus_player_slide");
}


building_slide_anim()
{
	hide_me = getentarray("building_slide_hide", "targetname");
	roof_brushes = getentarray("building_slide_roof", "targetname");
	
	foreach(ent in hide_me)
	{
		ent hide_notsolid();
	}
	thread intro_disable_playerhud();
	thread building_slide_player_anim();
	thread maps\intro_fx::maars_buildingslide_moment(hide_me,roof_brushes);
	thread maps\intro_fx::slide_tree_rotates();
	thread maps\intro_fx::slide_fires_kill();
	thread slide_explosion_bright_blur();
	thread slide_sunflare();
	delaythread(8.5, ::slide_dof );
	delaythread(19.5, ::slide_water_splash_blur );
}
	
slide_explosion_bright_blur()
{
	setblur(10,0);
	delaythread(.2, ::vision_set_changes, "intro_slide_sun_bloom", 0);
	wait(.25);
	setblur(0,.25);
	//wait(.25);
	vision_set_changes("intro_slide", 1);
}
	
slide_sunflare()
{
	//set sun flare position and lensflare for slide
	SetSunFlarePosition(( -20, 110, 0 ));
	thread maps\_shg_fx::fx_spot_lens_flare_dir("lights_intro_sunflare",(-20, 110, 0),8000);
}

slide_dof()
{	
	start = level.dofDefault;
	
	dof_slide_1a = [];
	dof_slide_1a[ "nearStart" ] = 50;
	dof_slide_1a[ "nearEnd" ] = 220;
	dof_slide_1a[ "nearBlur" ] = 5;
	dof_slide_1a[ "farStart" ] = 1000;
	dof_slide_1a[ "farEnd" ] = 7000;
	dof_slide_1a[ "farBlur" ] = 1.75;

	blend_dof( start, dof_slide_1a, .5 );
	wait(7.5);
	blend_dof( dof_slide_1a, start, .5 );
}

slide_water_splash_blur()
{
	setblur(10,0);
	wait(.5);
	setblur(0,1);
}

building_slide_playfx( origin, forward, right, dist, fx_msg, time )
{
	ent = spawnstruct();
	ent endon( "stop" );
	ent delaythread( time, ::send_notify, "stop" );
	wait_time = 0.1;
	time_to_complete_line = time/wait_time;
	dist_inc = dist/time_to_complete_line;
	current_dist = 0;
	
	fx = getfx( fx_msg );
	
	rand = randomIntRange( -256, 256 );
	horiz = right * rand;

	for ( ;; )
	{
		
		rand = randomIntRange( -256, 256 );
		horiz = right * rand;
		org = origin + (forward * current_dist) + horiz;
		PlayFX( fx, org );
		wait( wait_time );
		
		current_dist += dist_inc;
	}
}

building_slide_player_anim()
{
	maps\_shg_common::SetUpPlayerForAnimations();
	level.player DisableWeapons();
	level.player DisableWeaponSwitch();

	
	level.player_rig = spawn_anim_model( "player_rig", ( 0, 0, 0 ) );
	level.player_rig.animname = "player_rig";
	level.player_rig Hide();
	
	level.player_legs = spawn_anim_model( "player_legs", ( 0, 0, 0 ) );
	level.player_legs.animname = "player_legs";
	level.player_legs Hide();
	
	uav = spawn_anim_model( "uav", ( 0, 0, 0 ) );
	uav.animname = "uav";
	uav setanimtree();
	level.uav_fx = uav;//used in the fx.gsc
	thread maps\intro_fx::maars_buildingslide_uavshadowsthread(level.uav_fx,68);
	
	water_heater = spawn_anim_model( "landslide_building_water_heater", ( 0, 0, 0 ) );
	water_heater.animname = "landslide_building_water_heater";
	level.fxwaterheater = water_heater;
	water_heater setanimtree();
	
	thread maps\intro_fx::slide_splashes(water_heater);
		
	complete_player_rig = [];
	complete_player_rig[ 0 ] = level.player_rig;
	complete_player_rig[ 1 ] = level.player_legs;
	complete_player_rig[ 2 ] = uav;
	complete_player_rig[ 3 ] = water_heater;
	
	anim_pos = GetStruct( "slide_roof_collapse", "targetname" );
	anim_pos anim_first_frame( complete_player_rig, "roof_collapse_slide" );
	level.player PlayerLinkToDelta( level.player_rig, "tag_player", 1, 10, 10, 10, 10  );
	
	level.player_rig Show();
	level.player_legs Show();
	
	rumble = "heavy_3s";
	

	
	level.player delaycall( 0, ::playrumbleonentity, rumble );
	
	level.player delaycall( 3, ::playrumblelooponentity, "subtle_tank_rumble" );
	
	level.player delaycall( 8.0, ::stoprumble, "subtle_tank_rumble"  );
	
	level.player delaycall( 8.5, ::playrumbleonentity, "artillery_rumble" );

	level.player delaycall( 9, ::playrumblelooponentity, "subtle_tank_rumble" );
	
	level.player delaycall( 15.5, ::stoprumble, "subtle_tank_rumble"  );
	
	level.player delaycall( 19.5, ::playrumbleonentity, "artillery_rumble" );
	
	
	delaythread( 5, ::autosave_by_name_silent, "building_slide" );
	
	//slide vars
	delaythread( 8, ::building_slide_control_hint );
	delaythread( 9, ::building_slide_player_slide );
	delaythread( 15.5, ::building_slide_player_slide_end );

	anim_pos anim_single( complete_player_rig, "roof_collapse_slide" );
	
	
	//level.player Unlink();
	//level.player_rig Delete();
	level.player_legs Delete();
	uav delete();
	
	building_slide_river_ride_anim();
	
	flag_set( "building_slide_player_anim_done" );
}

building_slide_player_slide()
{
	
	thread building_slide_earthquake();
	level.player disableinvulnerability();
	forward = anglestoforward( level.player.angles ) * 100;
	velocity =  forward + ( 0, 0, -10 );
	allowedAcceleration = 37;//25
	dampening = .1;//.035
	
	level.player unlink();
	level.player_rig hide();
	level.player_legs hide();

	array_thread( GetEntArray("trigger_hurt", "classname"), ::trigger_kill_player );

	waittillframeend;
	level.player building_slide_custom_slide( velocity, allowedAcceleration, dampening );
	
}

building_slide_earthquake()
{
	level.player endon( "stop_sliding" );
	counter = 0;
	scale = .2;
	while( 1 )
	{
		earthquake( scale, .05, level.player.origin, 512 );
		counter ++;
		wait .05;
	}
}

trigger_kill_player()
{
	self waittill( "trigger" );
	level.player dodamage( self.dmg, level.player.origin );
	earthquake( .5, 2, level.player.origin, 512 );
	level.player PlayRumbleOnEntity( "damage_heavy" );
	level.player freezecontrols( true );
	level.player notify( "stop_sliding" );
	level.player.slideModel stopmoveslide();
}

building_slide_player_slide_end()
{
	if( !isAlive( level.player ) )
		return;
		
	blendtime = .25;
	level.player notify( "stop_sliding" );

	//level.player.slideModel match_origin_to_tag( level.player_rig, "tag_player", true );
	level.player unlink();
	
	if ( IsDefined( level.player_rig_slide ) )
	{
		level.player_rig_slide Unlink();
		level.player_rig_slide Delete();
	}
	
	if ( IsDefined( level.player_legs_slide ) )
	{
		level.player_legs_slide Unlink();
		level.player_legs_slide Delete();
	}
	
	level.player PlayerLinkToBlend( level.player_rig, "tag_player", blendtime, 0, 0 );
	
	wait blendtime;
	level.player_rig show();
	level.player PlayerLinkToDelta( level.player_rig, "tag_player", 1, 10, 10, 10, 10 );
}


get_origin_to_tag( target, tag, refmodel )
{	// self is the ent that we will match to tag
	org_origin = self.origin;
	org_angles = self.angles;
	
	tgt_tag_origin = target GetTagOrigin( tag );
	tgt_tag_angles = target GetTagAngles( tag );
	tgt_tag_up = AnglesToUp( tgt_tag_angles );
	tgt_tag_right = AnglesToRight( tgt_tag_angles );
	tgt_tag_forward = AnglesToForward( tgt_tag_angles );
	
	// get our bindpose
	our_tag_origin = undefined;
	our_tag_angles = undefined;
	if (!isdefined(refmodel))
	{
		self.origin = (0,0,0);
		self.angles = (0,0,0);
		
		// assume bindpose follows the standards
		our_tag_origin = self GetTagOrigin( tag );
		our_tag_angles = self GetTagAngles( tag );
		self.origin = org_origin;
		self.angles = org_angles;
	}
	else
	{
		refmodel.origin = (0,0,0);
		refmodel.angles = (0,0,0);
		
		// assume bindpose follows the standards
		our_tag_origin = refmodel GetTagOrigin( tag );
		our_tag_angles = refmodel GetTagAngles( tag );
	}
	
	// now determine where our origin should be to get our tag to match the target's tag
	our_origin = tgt_tag_origin - our_tag_origin[0]*tgt_tag_forward - our_tag_origin[1]*tgt_tag_right - our_tag_origin[2]*tgt_tag_up;
	our_angles = tgt_tag_angles;

	transform["origin"] = our_origin;
	transform["angles"] = our_angles;
	return transform;
}

match_origin_to_tag( target, tag, bLink, refmodel )
{	// self is the ent that we will match to tag
	transform = get_origin_to_tag( target, tag, refmodel );

	self.origin = transform["origin"];
	self.angles = transform["angles"];
	
	// and link
	if (bLink)
	{
		self linktoblendtotag( target, tag );
	}
}

building_slide_custom_slide( velocity, allowedAcceleration, dampening )
{
	player =  level.player;
	
	slideModel = spawn_tag_origin();
	slideModel.origin = player.origin;
	slideModel.angles = level.player_rig GetTagAngles( "tag_player" );
	player.slideModel = slideModel;

	override_link_method = IsDefined( level.custom_linkto_slide );
	
	if ( override_link_method )
	{
		player PlayerLinkToBlend( slideModel, undefined, 1 );
	}
	else
	{
		player PlayerLinkToDelta( slideModel, "tag_origin", 1, 10, 30, 20, 20 );
	}

/*
	// add another player rig to play animation when sliding
	level.player_rig_slide = spawn_anim_model( "player_rig", ( 0, 0, 0 ) );
	level.player_rig_slide.animname = "player_rig";
	level.player_legs_slide = spawn_anim_model( "player_legs", ( 0, 0, 0 ) );
	level.player_legs_slide.animname = "player_legs";
	
	thread move_rig_with_view( slideModel );
	
	player_rig_slide_anim = level.player_rig_slide getanim( "roof_collapse_slide_loop" );
	player_legs_slide_anim = level.player_legs_slide getanim( "roof_collapse_slide_loop" );
	level.player_rig_slide SetAnim( player_rig_slide_anim, 1, 0, 1 );
	level.player_legs_slide SetAnim( player_legs_slide_anim, 1, 0, 1 );
*/
	player.slideModel MoveSlide( ( 0, 0, 15 ), 15, velocity );

	player thread DoSlide( slideModel, allowedAcceleration, dampening );
}

move_rig_with_view( slideModel )
{
	level.player endon( "stop_sliding" );

	level.player_rig_slide LinkTo( slideModel, "tag_origin", (0,0,0), (0,0,0) );
	level.player_legs_slide LinkTo( slideModel, "tag_origin", (0,0,0), (0,0,0) );
		
	while ( true )
	{
		player_angles = level.player GetPlayerAngles();
		base_to_new_yaw = player_angles[1] - slideModel.angles[1];
		
		level.player_rig_slide LinkTo( slideModel, "tag_origin", (0,0,0), (0,base_to_new_yaw,0) );
		level.player_legs_slide LinkTo( slideModel, "tag_origin", (0,0,0), (0,base_to_new_yaw,0) );
		wait 0.05;
	}
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
	level.forwardAccel = 23; //.4;//.5
	childthread building_slide_adjust_player_forward_accel();
	while ( 1 )
	{
		movement = player GetNormalizedMovement();
		forward = AnglesToForward( player.angles );
		right = AnglesToRight( player.angles );
		
		movement = ( ( movement[ 1 ] * right[ 0 ] * allowedAcceleration ) + level.forwardAccel * forward[ 0 ], ( movement[ 1 ] * right[ 1 ] * allowedAcceleration ) + level.forwardAccel * forward[ 1 ], 0 );

		slideModel.slideVelocity += movement ;

		wait .05;
		slideModel.slideVelocity *= 1 - dampening;
	}
}


building_slide_adjust_player_forward_accel()
{
	
	forwardMax = 40;
	forwardMin = 23;
	base = getstruct( "slide_roof_collapse", "targetname" );
	lastdist = distance( level.player.origin, level.player_rig GetTagOrigin( "tag_player" ) ) + .01;
	
	wait 1;
	
	while( 1 )
	{
		dist_anim = distance( base.origin, level.player_rig GetTagOrigin( "tag_player" ) );
		dist_player = distance( base.origin, level.player.origin );
		dist = distance( level.player.origin, level.player_rig GetTagOrigin( "tag_player" ) );
		
		dist_ratio = dist/lastdist;
		
		if( dist_anim > dist_player && dist > 10 && level.forwardAccel < forwardMax ) 
		{
			level.forwardAccel += 4;// * dist_ratio;
		}
		else
		if( dist_anim < dist_player && dist > 10 && level.forwardAccel > forwardMin )
		{
			level.forwardAccel -= 4;// * dist_ratio;
		}
		
		lastdist = dist + .01;

		wait .05;
	}
	
}

building_slide_control_hint()
{
	hint_displayed = false;
	if ( level.Console )
	{
		config = GetSticksConfig();
		cur_flavor = "";
		if (issubstr(config,"southpaw"))
		{
			hint_displayed = true;
			display_hint( "control_slide_l", 3 );
		}
	}
	
	if ( !hint_displayed )
	{
		display_hint( "control_slide", 3 );
	}
	while (isdefined(level.current_hint))
	{
		cur_hint_string = "control_slide";
		config = GetSticksConfig();
		if (issubstr(config,"southpaw"))
			cur_hint_string = "control_slide_l";
		level.current_hint SetText(	level.trigger_hint_string[ cur_hint_string ] );

		wait 0.05;
	}
}


building_slide_river_ride_anim()
{
	water_heater = spawn_anim_model( "landslide_building_water_heater", ( 0, 0, 0 ) );
	water_heater.animname = "landslide_building_water_heater";
	water_heater setanimtree();
	
	building = getent("intro_landslide_small_01","targetname");
	building.animname = "landslide_building_small_01";
	building setanimtree();
	
	littlebird = spawn_anim_model( "littlebird", ( 0, 0, 0 ) );
	littlebird.animname = "littlebird";
	littlebird setanimtree();
	littlebird hidepart("static_rotor_jnt");
	littlebird hidepart("static_tail_rotor_jnt");
	
	level.soap.woundedNode notify( "stop_wounded_idle" ); 
	
	actorsfirstframe = [];

	actorsfirstframe[ 0 ] = water_heater;
	actorsfirstframe[ 1 ] = building;
	actorsfirstframe[ 2 ] = littlebird;
	anim_pos = GetStruct( "slide_roof_collapse", "targetname" );

	anim_pos anim_first_frame( actorsfirstframe, "river_ride" );
	
	actors = [];
	actors[ 0 ] = [ level.player_rig, 0 ];
	actors[ 1 ] = [ water_heater, 0 ];
	actors[ 2 ] = [ building, 0 ];
	actors[ 3 ] = [ littlebird, 0 ];
	
	
	level.player delaycall( 6, ::playrumbleonentity, "artillery_rumble" );
	
	level.player delaycall( 7, ::playrumblelooponentity, "subtle_tank_rumble" );
	
	level.player delaycall( 9, ::playrumbleonentity, "light_1s" );
	
	level.player delaycall( 13, ::playrumbleonentity, "heavy_3s" );
	level.player delaycall( 17.5, ::stoprumble, "subtle_tank_rumble" );
	
	littlebird delaycall( 13, ::hide );
	
	thread slide_bloom_to_white();
	thread slide_ending_sunflare();
	thread slide_ending_dof();

	//thread river_ride_pullout( "river_ride" );
	anim_pos anim_single_end_early( actors, "river_ride" );
	
	flag_set( "building_slide_complete" );
}

slide_bloom_to_white()
{
	//wait until exiting water
	wait(30);
	aud_send_msg("mus_emerge_from_river");
	thread vision_set_fog_changes("intro_slide_sun_bloom", 3);
	wait(.2);
	setblur(20,3);
	thread intro_fade_out_to_white_end();
//	wait(2);
//	thread intro_fade_out_to_black();
	
}

slide_ending_sunflare()
{
	SetSunFlarePosition(( -32, 65, 0 ));
	flag_set("fx_spot_flare_kill");
	flag_clear("fx_spot_flare_kill");
	wait(24); //have to wait here as the flare does some strange stuff if turned on earlier.
	thread maps\_shg_fx::fx_spot_lens_flare_dir("lights_intro_sunflare",(-32, 65, 0),8000);
}

slide_ending_dof()
{
	//wait until exiting water
	wait(24);
	
	start = level.dofDefault;
	
	dof_slide_ending_1a = [];
	dof_slide_ending_1a[ "nearStart" ] = 1.5;
	dof_slide_ending_1a[ "nearEnd" ] = 6.5;
	dof_slide_ending_1a[ "nearBlur" ] = 6;
	dof_slide_ending_1a[ "farStart" ] = 24;
	dof_slide_ending_1a[ "farEnd" ] = 90;
	dof_slide_ending_1a[ "farBlur" ] = 1.3;

	blend_dof( start, dof_slide_ending_1a, 1 );
}

building_slide_destroy_tree_setup()
{
	col = getent( "building_slide_tree_fall_col", "targetname" );
	col ConnectPaths();
	col notsolid();
}

building_slide_destroy_tree()
{
	static_tree = getent( "building_slide_destructible_tree", "targetname" );
	
	tree = spawn_anim_model( "animated_tree", ( 0, 0, 0 ) );
	tree.animname = "animated_tree";
	tree setanimtree();
	anim_pos = getstruct( "building_slide_tree_fall_anim_pos", "targetname" );
	
	wait(.4);
	//static_tree hide();
	playfx( getfx( "uav_attack_tree_missile_impact" ), self.origin );
	thread maps\intro_fx::run_tree_fall_fx(tree);
	wait(0.1);
	static_tree hide();
	anim_pos thread anim_single_solo( tree, "tree_fall" );
	//thread maps\intro_fx::run_tree_fall_fx();
	
	col = getent( "building_slide_tree_fall_col", "targetname" );
	col solid();
}


object_fall_gravity( faller, earthquake_time )
{
	// there are 39.3700787 inches in a meter
	// (dist in meters) = (0)t + (0.5)(9.8)t2
	// t = sqrt ((dist in meters) / (.5)(9.8))
	
	//trigger = getent(trigger_target_name, "targetname");
	//faller = getent(trigger.target, "targetname");
	target_ent = getStruct(faller.target, "targetname");
	dist_in = faller.origin[2] - target_ent.origin[2];
	assert( dist_in > 0 );
	time = sqrt ( (dist_in / 39.3700787) / (.5 * 9.8) );
	assert( time > 0 );
	shake_intensity = randomfloatrange( 0.2, 0.3 );

	wait( 0.3 );
	
	if(isdefined(earthquake_time))
	{
		earthquake(shake_intensity, earthquake_time, level.player.origin, 500);
	}
	
	wait( 0.3 );
	thread object_fall_vfx(target_ent);
	faller RotateTo(target_ent.angles, time, time, 0);
	faller MoveTo(target_ent.origin, time, time, 0);
	if(isdefined(target_ent.script_parameters))
	{
		wait(time);
		playfx(getfx(target_ent.script_parameters), target_ent.origin);
	}
}

object_fall_vfx(target_ent)
{
	//play vfx
	if(IsDefined(target_ent.target))
	{
		vfx_loc = GetStruct(target_ent.target, "targetname");
		if(IsDefined(vfx_loc.target))
		{
			thread object_fall_vfx(vfx_loc);
		}
		
		if(isDefined(vfx_loc.script_delay))
			wait(vfx_loc.script_delay);
		
		effect_name = "rock_falling";
		if(isdefined(vfx_loc.script_parameters))
			effect_name = vfx_loc.script_parameters;
		playfx(getfx(effect_name), vfx_loc.origin);
	}
}

building_slide_building_destruct_setup()
{
	damaged = getent( "landslide_area_building_01_damaged", "targetname" );
	damaged hide();
	damaged notsolid();
	
	collapser = getent( "landslide_area_building_01_damaged_collapse", "targetname" );
	collapser hide();
	collapser notsolid();
	
	collapser_windows = getentarray( "landslide_area_building_01_damaged_collapse_windows", "targetname" );
	
	foreach( window in collapser_windows )
	{
		window hide();
		window LinkTo( collapser );
	}
}


building_slide_building_destruct()
{
	fx1 = getstructarray( "building_slide_building_destruct_fx1", "targetname" );
	fx2 = getstructarray( "building_slide_building_destruct_fx2", "targetname" );
	fx3 = getstructarray( "building_slide_building_destruct_fx3", "targetname" );
	fx4 = getstructarray( "building_slide_building_destruct_fx4", "targetname" );
	
	//"debri_explosion" 								
	//"generic_explosion_debris" 						
	//"wall_explosion_1" 									
	//"wall_explosion_2" 									
	//"wood_explosion_1"
	
	foreach( fx in fx1 )
	{
		playfx( getfx( "intro_sliderun_debrisexp1" ), fx.origin );
	}
	
	/*
	models = getentarray( "landslide_area_building_01_undamaged_model", "targetname" );
	foreach( model in models )
	{
		model hide();
	}
	
	undamaged = getent( "landslide_area_building_01_undamaged", "targetname" );
	undamaged hide();
	undamaged notsolid();
	
	damaged = getent( "landslide_area_building_01_damaged", "targetname" );
	damaged show();
	
	collapser = getent( "landslide_area_building_01_damaged_collapse", "targetname" );
	collapser show();
	
	collapser_windows = getentarray( "landslide_area_building_01_damaged_collapse_windows", "targetname" );
	
	foreach( window in collapser_windows )
	{
		window show();
	}
	*/
	foreach( fx in fx2 )
	{
		playfx( getfx( "intro_sliderun_debrisexp2" ), fx.origin, ( 0, -1, 0), ( 0, 0, 1) );
	}
	/*
	pos1 = getstruct( collapser.target, "targetname" );
	collapser moveto( pos1.origin, .5, 0, 0 );
	*/
	wait( .5 );
	foreach( fx in fx3 )
	{
		playfx( getfx(  "intro_sliderun_wallexp1" ), fx.origin , ( 0, -1, 0), ( 0, 0, 1));
	}
	/*
	pos2 = getstruct( pos1.target, "targetname" );
	collapser moveto( pos2.origin, 3, 2, 0 );
	collapser rotateto( collapser.angles + ( 0, 0, 35 ), 3, 2, 0 );
	*/
	wait( 1.5 );
	foreach( fx in fx4 )
	{
		playfx( getfx(  "intro_sliderun_wallexp2" ), fx.origin, ( 0, -1, 0), ( 0, 0, 1) );
		wait( 1 );
	}
}



////////////////////////////////////
//---- RIVER RIDE BUTTON MASH ----//
////////////////////////////////////

river_ride_pullout( animation_name )
{
	autosave_by_name_silent( "river_ride" );
	wait 11;
	
	thread mash_hint_blinks();
	
	mash_struct = SpawnStruct();
	mash_struct.faded_out = false;
	mash_struct.pull_scale = 6;
	mash_struct.takes_pain = true;
	mash_struct.sin_scale = 0.75;
	mash_struct.rate = 0.065;
	mash_struct.range = 0.03;
	mash_struct.occumulator_base = 4;
	mash_struct.auto_occumulator_base = true;
	mash_struct.set_pull_weight = true;
	mash_struct.min_light = 70;
	mash_struct.min_heavy = 90;
	mash_struct.rumble_loop = "light_3s";
	

	mash_struct handle_mash( animation_name );
	
	//wait 10; //this should be when the anim is complete
	
}

handle_mash( animation_name )
{
	was_pressed = use_pressed();

	last_press = 0;
	rate = 0;
	
	animation = level.player_rig getanim( animation_name );
	
	occumulator = SpawnStruct();
	occumulator thread occumulate_player_use_presses( self );
	level.occumulator = occumulator;

	thread player_fails_if_does_not_occumulate( animation_name );
	
	next_pain = 0;

	max_time = 500;
	min_time = 0;
	time_range = abs( max_time - min_time );

	struct = SpawnStruct();

	damage_min = 2;
	damage_max = 5;

	//last_pain = 0;
	//last_held = 0;

	weaken_time = 0;



	old_percent = 0;
	anim_time = 0;
	playing_rumble = false;

	for ( ;; )
	{
		is_pressed = use_pressed();

		new_press = false;
		rate = 0;

		if ( is_pressed && !was_pressed )
		{
			if ( !playing_rumble )
			{
				playing_rumble = true;
				level.player PlayRumbleLoopOnEntity( self.rumble_loop );
			}
			
			if ( randomint( 100 ) > self.min_heavy )
			{
				level.player PlayRumbleOnEntity( "damage_heavy" );
			}
			else
			if ( randomint( 100 ) > self.min_light )
			{
				level.player PlayRumbleOnEntity( "damage_light" );
			}
			
			occumulator.presses[ occumulator.presses.size ] = GetTime();

			last_press = GetTime();


			rate = ( Sin( GetTime() * 0.2 ) + 1 ) * 0.5;
			rate *= self.range;
			rate += self.rate;

			new_press = true;
			
			if ( level.player_rig GetAnimTime( animation ) > 0.05 )
			{
				/*
				if ( self.takes_pain && GetTime() > next_pain )
				{
					next_pain = GetTime() + RandomIntRange( 450, 850 );
					amount = RandomFloatRange( damage_min, damage_max );
					amount = clamp( amount, 1, 50 );
					damage_min *= 1.15;
					damage_max *= 1.15;
					if ( IsDefined( self.override_damage ) )
						amount = self.override_damage;

					thread hurt_player( amount, anim_time );
				}
				*/
			}
			
		}
		
		if ( playing_rumble && gettime() > last_press + 300 )
		{
			playing_rumble = false;
			level.player StopRumble( self.rumble_loop );
		}

		was_pressed = is_pressed;

		anim_finished = false;
		anim_time = undefined;
		
		
		//animation = level.player_rig getanim( animation_name );
		anim_time = level.player_rig GetAnimTime( animation );
		if ( anim_time >= 0.45 )
			anim_finished = true;


		if ( IsDefined( self.auto_occumulator_base ) )
		{
			occumulator.occumulator_base = 1 - anim_time;
			occumulator.occumulator_base *= 7;
			occumulator.occumulator_base = clamp( occumulator.occumulator_base, 7, 1 );
		}

		percent_dif = abs( old_percent - anim_time );
		if ( percent_dif > 0.05 )
		{
			new_pull_earthquake( anim_time );
			old_percent = anim_time;
		}


		if ( anim_finished )
			break;
		
		wait( 0.05 );
	}
	
	occumulator notify( "stop" );
	level.player StopRumble( self.rumble_loop );
	thread fade_out_mash_hint( .25 );
	level.occumulator = undefined;
	fade_in( 1 );
}

use_pressed()
{
	return level.player UseButtonPressed();
}

occumulate_player_use_presses( struct )
{
	self endon( "stop" );

	press_time = 1500;
	self.presses = [];

	max_presses = 7;

	for ( ;; )
	{
		waittillframeend;// this always runs last

		for ( i = 0; i < self.presses.size; i++ )
		{
			press = self.presses[ i ];
			if ( press < GetTime() - press_time )
			{
//				PrintLn( "Removing press at time " + press );
				continue;
			}

			//i -= 1;	
			break;
		}

		newpresses = [];
		// i is set above
		for (; i < self.presses.size; i++ )
		{
			newpresses[ newpresses.size ] = self.presses[ i ];
		}

		self.presses = newpresses;

		scale = ( self.presses.size - struct.occumulator_base ) * 0.03;
		//scale *= scale;
		scale *= 10;
		scale = clamp( scale, 0, 1.0 );
		self.occumulator_scale = scale;

		wait 0.05;
	}

}


player_fails_if_does_not_occumulate( animation_name )
{
	level.occumulator endon( "stop" );

	wait( 3 );// some time to learn

	overlay = get_black_overlay();

	fail_count = 0;

	deathcount = -30;

	for ( ;; )
	{
		pressed_enough = level.occumulator.presses.size >= 2;
		if ( pressed_enough )
			fail_count += 2;
		else
			fail_count -= 1;

		if ( fail_count <= deathcount )
			break;

		fail_count = clamp( fail_count, deathcount, 20 );

		alpha = fail_count;
		alpha /= deathcount;
//		alpha *= -1;
		alpha = clamp( alpha, 0, 1 );

		overlay FadeOverTime( 0.2 );
		overlay.alpha = alpha;
		
		rate = fail_count/deathcount;
		rate = 1 - rate;
		rate = clamp( rate, 0, 1 );
		anim_set_rate_single( level.player_rig, animation_name, rate );
		
		wait( 0.05 );
	}

	overlay FadeOverTime( 0.2 );
	overlay.alpha = 1;
	wait( 0.2 );
	missionFailedWrapper();
}


fade_in_mash_hint( time )
{
	if ( !isdefined( time ) )
		time = 1.5;

	if ( !isdefined( level.mash_hint ) )
		draw_mash_hint();

	foreach ( elem in level.mash_hint )
	{
		elem FadeOverTime( time );
		elem.alpha = 0.95;
	}
}

draw_mash_hint()
{
	y_offset = 90;
	x_offset = 35;


	mash_text = level.player createClientFontString( "default", 3 );
	mash_text.horzAlign = "right";
	mash_text.alignX = "right";
	mash_text set_default_hud_stuff();
	// ^3[{+usereload}]^7
	mash_text SetText( &"INTRO_RIVER_RIDE_HINT" );

	elements = [];
	elements[ "text" ] = mash_text;

	level.mash_hint = elements;
}

mash_hint_blinks()
{
	level notify( "fade_out_mash_hint" );
	level endon( "fade_out_mash_hint" );

	if ( !isdefined( level.mash_hint ) )
		draw_mash_hint();

	fade_time = 0.10;
	hold_time = 0.20;

	foreach ( elem in level.mash_hint )
	{
		elem FadeOverTime( 0.1 );
		elem.alpha = 0.95;
	}

	wait 0.1;

	hud_button = level.mash_hint[ "text" ];

	for ( ;; )
	{
		hud_button FadeOverTime( 0.01 );
		hud_button.alpha = 0.95;
		hud_button ChangeFontScaleOverTime( 0.01 );
		hud_button.fontScale = 3;

		wait 0.05;

		hud_button FadeOverTime( fade_time );
		hud_button.alpha = 0.0;
		hud_button ChangeFontScaleOverTime( fade_time );
		hud_button.fontScale = 0.25;

		wait hold_time;

		hide_hint_presses = 6;

		while ( IsDefined( level.occumulator ) )
		{
			if ( level.occumulator.presses.size < hide_hint_presses )
				break;

			foreach ( elem in level.mash_hint )
			{
				elem.alpha = 0;
			}
			wait 0.05;
		}
	}
}

fade_out_mash_hint( time )
{
	level notify( "fade_out_mash_hint" );
	if ( !isdefined( time ) )
		time = 1.5;

	if ( !isdefined( level.mash_hint ) )
		draw_mash_hint();

	foreach ( elem in level.mash_hint )
	{
		elem FadeOverTime( time );
		elem.alpha = 0;
	}
}

set_default_hud_stuff()
{
	self.alignx = "center";
	self.aligny = "middle";
	self.horzAlign = "center";
	self.vertAlign = "middle";
	self.hidewhendead = true;
	self.hidewheninmenu = true;

	self.sort = 205;
	self.foreground = true;

	self.alpha = 0;
}
/*
get_black_overlay()
{
	if ( !isdefined( level.black_overlay ) )
		level.black_overlay = create_client_overlay( "black", 0, level.player );
	level.black_overlay.sort = -1;
	level.black_overlay.foreground = false;
	return level.black_overlay;
}
*/
fade_in( fade_time )
{
	if ( level.MissionFailed )
		return;
	level notify( "now_fade_in" );
		
	black_overlay = get_black_overlay();
	if ( fade_time )
		black_overlay FadeOverTime( fade_time );

	black_overlay.alpha = 0;

	//thread eq_changes( 0.0, fade_time );
}

notify_on_use()
{
	was_pressed = use_pressed();
	for ( ;; )
	{
		if ( !was_pressed && use_pressed() )
			break;
		was_pressed = use_pressed();
		wait 0.05;
	}
	level.player notify( "pressed_use" );
}

mash_hint_visible()
{
	if ( !isdefined( level.mash_hint ) )
		return false;

	foreach ( elem in level.mash_hint )
	{
		return elem.alpha > 0.8;
	}

	return false;
}

fade_out( fade_out_time )
{
	black_overlay = get_black_overlay();
	if ( fade_out_time )
		black_overlay FadeOverTime( fade_out_time );

	black_overlay.alpha = 1;
	//thread eq_changes( 0.5, fade_out_time );
}

new_pull_earthquake( anim_time )
{
	if ( IsDefined( self.override_anim_time ) )
		anim_time = self.override_anim_time;

	eq = anim_time + 0.37;
	eq *= 0.22;
	Earthquake( eq, 5, level.player.origin, 5000 );
}

hurt_player( num, anim_time )
{
	if ( !isdefined( anim_time ) )
		anim_time = 0.5;

	level notify( "new_hurt" );
	level endon( "new_hurt" );
	if ( IsDefined( self.override_anim_time ) )
		anim_time = self.override_anim_time;

	pos = level.player.origin + randomvector( 1000 );

	blur = num * 2.9;
	time = num * 0.25;
	SetBlur( blur, 0 );
	SetBlur( 0, time );

	quake_time = num * 0.05;
	quake_time = clamp( quake_time, 0, 0.4 );
	quake = num * 0.02;
	quake = clamp( quake, 0, 0.25 );

	duration = clamp( num, 0, 0.85 );

	min_time = 0.2;
	max_time = 0.75;//1.5
	time_range = abs( min_time - max_time );
	anim_range = 1 - anim_time;

	vision_blend_time = anim_range * time_range + min_time;
	halt_time = anim_time * 2;
	halt_time = clamp( halt_time, 0.5, 2.0 );
	recover_time = RandomFloatRange( 0.2, 0.6 );

	vision_set = "aftermath_hurt";
	if ( halt_time > 1.35 )
		vision_set = "aftermath_dying";
	set_vision_set( vision_set, vision_blend_time );

	if ( RandomInt( 100 ) > 70 )
	{
		// sometimes do quick recover
		wait( 0.15 );
		recover_time = RandomFloatRange( 0.16, 0.22 );
		set_vision_set( "aftermath_walking", recover_time );
	}
	wait halt_time;
	set_vision_set( "aftermath_walking", recover_time );
}



///////////////////
//---- UTILS ----//
///////////////////


breach_door( door, door_destroyed, door_col )
{
	door = getent( door, "targetname" );
	anim_ent = getent( door_destroyed, "targetname" );
	
	destroyedModel = spawn_anim_model( "breach_door_model", ( 0, 0, 0 ) );
	destroyedModel.animname = "breach_door_model";
	destroyedModel hide();
	
	anim_ent anim_first_frame_solo( destroyedModel, "breach" );
	
	flag_wait( "courtyard_start_breach" );
	
	//remove collision on door
	door_col = getent( door_col, "targetname" );
	door_col ConnectPaths();
	door_col delete();
	//animate exploded door
	anim_ent thread anim_single_solo( destroyedModel, "breach" );
	destroyedModel show();
	door Delete();
}

breach_fx_setup(breach_name)
{
	AssertEx( IsDefined( self.script_fxid ), "Breach_fx at " + self.origin + " has no script_fxid" );
	fxid = self.script_fxid;
	ent = createExploder( fxid );
 	ent.v[ "origin" ] = self.origin;
 	ent.v[ "angles" ] = self.angles;
 	ent.v[ "fxid" ] = fxid;
 	ent.v[ "delay" ] = 0;
 	ent.v[ "exploder" ] = "breach_"+ breach_name;
 	ent.v[ "soundalias" ] = "clusterbomb_explode_default";
 	ent.v[ "forward" ] = anglestoforward(self.angles);
 	ent.v[ "up" ] = anglestoup(self.angles);
}

drop_to_floor()
{
	trace = bullettrace( self.origin + ( 0, 0, 32 ), self.origin, false, undefined );
	self.origin = trace[ "position" ];
}

lower_accuracy(accuracy, endon_flag)
{
	self endon( "death" );
	old_accuracy = undefined;
	if( isDefined( self.accuracy ) )
	{
		old_accuracy = self.accuracy;
	}
	if( isDefined( accuracy ) )
	{
		self.accuracy = accuracy;
	}
	else
	{
		self.accuracy = .2;
	}
	if( isDefined( endon_flag ) )
	{
		flag_wait( endon_flag );
		if( isDefined( old_accuracy ) )
		{
			self.accuracy = old_accuracy;
		}
		else
		{
			self.accuracy = .8;
		}
	}
}


retreat_to_node(guy_array, retreat_node)
{
	//baddies_sorted = SortByDistance( guy_array, retreat_node.origin );
	baddies_sorted = guy_array;
	count = 0;
	for (i=baddies_sorted.size-1; i>=0; i--)
	{
		if ( isAlive(baddies_sorted[i]) && !isDefined(baddies_sorted[i].retreat) )
		{
			//baddies_sorted[i].retreat = true;
			if(isarray(retreat_node))
			{
				if(retreat_node.size > 1)
				{
					retreat_to_node = getclosest( baddies_sorted[i].origin, retreat_node );
					baddies_sorted[i] setGoalPos( retreat_to_node.origin );
				}
				else
				{
					assert(retreat_node.size > 0);
					baddies_sorted[i] setGoalPos( retreat_node[0].origin );
				}
			}else
			{
				baddies_sorted[i] setGoalPos( retreat_node.origin );
			}
			
			baddies_sorted[i] notify( "retreat" );
			baddies_sorted[i] thread monitor_retreater();
			
			count ++;
		}
		if (count > 3)
		{
			wait( 3 );
			count = 0;
		}
	}
}

monitor_retreater()
{
	self endon( "death" );
	self.goalradius = 256;
	self.ignoreall = true;
	//self.sprint = true;
	
	self waittill_either( "goal", "damage" );
	self.goalradius = 512;
	self.ignoreall = false;
	//self.sprint = false;
	//self.retreat = undefined;
}

check_volumes(volume_array)
{
	foreach(volume in volume_array)
	{
		if(level.player isTouching(volume))
			return true;
		wait(0.05);
	}
	return false;
}

exp_fade_overlay( target_alpha, fade_time )
{
	self notify( "exp_fade_overlay" );
	self endon( "exp_fade_overlay" );

	fade_steps = 4;
	step_angle = 90 / fade_steps;
	current_angle = 0;
	step_time = fade_time / fade_steps;

	current_alpha = self.alpha;
	alpha_dif = current_alpha - target_alpha;

	for ( i = 0; i < fade_steps; i++ )
	{
		current_angle += step_angle;

		self FadeOverTime( step_time );
		if ( target_alpha > current_alpha )
		{
			fraction = 1 - Cos( current_angle );
			self.alpha = current_alpha - alpha_dif * fraction;
		}
		else
		{
			fraction = Sin( current_angle );
			self.alpha = current_alpha - alpha_dif * fraction;
		}

		wait step_time;
	}
}

get_black_overlay( is_foreground )
{
	if ( !isdefined( level.black_overlay ) )
	{
		level.black_overlay = create_client_overlay( "black", 0, level.player );
	level.black_overlay.sort = -1;
	}
	
	if ( IsDefined( is_foreground ) )
	{
		level.black_overlay.foreground = is_foreground;
	}
	
	return level.black_overlay;
}

get_white_overlay()
{
	if ( !isdefined( level.white_overlay ) )
		level.white_overlay = create_client_overlay( "white", 0, level.player );
	level.white_overlay.sort = -1;
	level.white_overlay.foreground = false;
	return level.white_overlay;
}

blur_overlay( target, time )
{
	SetBlur( target, time );
}

introscreen_generic_fade_out( shader, pause_time, fade_in_time, fade_out_time )
{
	if ( !isdefined( fade_in_time ) )
		fade_in_time = 1.5;

	introblack = NewHudElem();
	introblack.x = 0;
	introblack.y = 0;
	introblack.horzAlign = "fullscreen";
	introblack.vertAlign = "fullscreen";
	introblack.foreground = true;
	introblack SetShader( shader, 640, 480 );

	if ( IsDefined( fade_out_time ) && fade_out_time > 0 )
	{
		introblack.alpha = 0;
		introblack FadeOverTime( fade_out_time );
		introblack.alpha = 1;
		wait( fade_out_time );
	}

	wait pause_time;

	
	
	// Fade out black
	if ( fade_in_time > 0 )
		introblack FadeOverTime( fade_in_time );

	introblack.alpha = 0;
	
	wait fade_in_time;
	
	introblack destroy();
	//SetSavedDvar( "com_cinematicEndInWhite", 0 );
	
}


disable_awareness()
{
	assert(self.awareness);
	self.awareness = 0;
	self.ignoreall = true;
	self.dontmelee = true;
	self.ignoreSuppression = true;
	assert(!isdefined(self.suppressionwait_old));
	self.suppressionwait_old = self.suppressionwait;
	self.suppressionwait = 0;
	self disable_surprise();
	self.IgnoreRandomBulletDamage = true;
  	self disable_bulletwhizbyreaction();
  	self disable_pain();
  	self disable_danger_react();
  	self.grenadeawareness = 0;
  	self.ignoreme = 1;
  	self enable_dontevershoot();
  	self.disableFriendlyFireReaction = true;
}

has_awareness()
{
	return self.awareness;
}

enable_awareness()
{
	assert(!self.awareness);
	self.awareness = 1;
	self.ignoreall = false;
	self.dontmelee = undefined;
	self.ignoreSuppression = false;
	assert(isdefined(self.suppressionwait_old));
	self.suppressionwait = self.suppressionwait_old;
	self.suppressionwait_old = undefined;
	self enable_surprise();
	self.IgnoreRandomBulletDamage = false;
	self enable_bulletwhizbyreaction();
 	self enable_pain();
	self.grenadeawareness = 1;
	self.ignoreme = 0;
	self disable_dontevershoot();
	self.disableFriendlyFireReaction = undefined;
}


///////////////////////////////////
//---- ADVANCED COLOR GROUPS ----//
///////////////////////////////////

color_volume_advance( baseName, numTotalFlags, startFlagNum, local_endon )
{
	if( isdefined( local_endon ) )
		color_endon = local_endon;
	else
		color_endon = "color_volume_advance_stop";
	
	
	thread color_volume_advance_cleanup( color_endon );
	level endon( color_endon );
	
	team = "allies";
	
	// maybe we want to start from the middle of the chain, like for a start point
	if( !IsDefined( startFlagNum ) )
	{
		startFlagNum = 1;
	}
	
	for ( i = startFlagNum; i <= numTotalFlags; i++ )
	{
		// final name looks like "[baseName]_1" or whatever
		name = baseName + "_" + i;
		trig = GetEnt( name, "targetname" );
		assert(isdefined(trig));
		assert((trig.spawnflags & 64) == 0); //these triggers should not delete after use
		vol = GetEnt( trig.target, "targetname" );
		assert(isdefined(vol));
		
		if(!isdefined(trig.trigger_off) || trig.trigger_off == true)
		{
			trig waittill("trigger");
			trig trigger_off_proc();
		}
		
		// get all the color codes from the script_color_allies
		array = vol maps\_colors::get_colorcodes( vol.script_color_allies, team );
		colorCodes = array[ "colorCodes" ];
		colorCodesByColorIndex = array[ "colorCodesByColorIndex" ];
		colors = array[ "colors" ];
		
		//we have the volume for this color group so set it up for each color specified
		infos = [];
		foreach( colorCode in colorCodes )
		{
			// can only support one volume per colorCode at the moment
			ASSERTEX( !color_volume_dupe_info( infos, colorCode ), "More than one volume found for colorCode " + colorCode + ", currently we only support one volume per colorCode." );
			
			info = spawnstruct();
			
			// set up arrays for us to manually pass to activate_color_trigger_internal
			info.colorCodes[ 0 ] = colorCode;
			color = GetSubStr( colorCode, 0, 1 );
			info.colors[ 0 ] = color;
			info.colorCodesByColorIndex[ color ] = colorCodesByColorIndex[ color ];
			info.name = name;
			info.volume = vol;
			
			infos[ infos.size ] = info;
		}
		
		array_thread( infos, ::color_volume_advance_queue_add, color_endon );
	}
}

color_volume_advance_cleanup( color_endon )
{
	level waittill( "color_endon" );
	
	level.color_volume_advance_queue = undefined;
}		

color_volume_advance_queue_manager( color, color_endon )
{
	level endon( color_endon );
	
	while( 1 )
	{
		// if we have any volumes of this color to wait for, do them in order
		if( level.color_volume_advance_queue[ color ].size )
		{
			// process the first volume in the stack, if the stack has any entries
			volume = level.color_volume_advance_queue[ color ][ 0 ];
			volume color_flag_volume_advance_wait( color_endon );
		}
		// otherwise, wait for an update and try again
		else
		{
			level waittill( "color_flag_advance_queue_updated" );
		}
	}
	
}

// self = the info spawnstruct to add
color_volume_advance_queue_add( color_endon )
{
	color = self.colors[ 0 ];
	
	if( !IsDefined( level.color_volume_advance_queue ) )
	{
		level.color_volume_advance_queue = [];
	}
	
	// see if we need to set up the key for this color
	keys = GetArrayKeys( level.color_volume_advance_queue );
	foundOne = false;
	foreach( key in keys )
	{
		if( key == color )
		{
			foundOne = true;
			break;
		}
	}
	
	// set it up if necessary
	if( !foundOne )
	{
		level.color_volume_advance_queue[ color ] = [];
		
		// kick off a queue manager for this color
		thread color_volume_advance_queue_manager( color, color_endon );
	}
	
	// add the volume to the end of the array
	level.color_volume_advance_queue[ color ][ level.color_volume_advance_queue[ color ].size ] = self;
	
	level notify( "color_flag_advance_queue_updated" );
}

// self = the info spawnstruct to remove
color_volume_advance_queue_remove()
{
	color = self.colors[ 0 ];
	
	ASSERTEX( self == level.color_volume_advance_queue[ color ][ 0 ], "Tried to remove a volume from the color_volume_advance queue for color " + color + ", but that volume wasn't at the top of the stack. This is unexpected." );
	
	level.color_volume_advance_queue[ color ] = array_remove( level.color_volume_advance_queue[ color ], self );
}

// self = the info spawnstruct
color_flag_volume_advance_wait( color_endon )
{
	level endon( color_endon );
	
	self.volume waittill_volume_dead_or_dying();
	
	thread maps\_colors::activate_color_code_internal( self.colorCodes, self.colors, "allies", self.colorCodesByColorIndex );
	
	//now that we have activated attempt to disable any triggers that have the same script noteworthy of our volume
	assert(isdefined(self.volume));
	if(isdefined(self.volume.script_noteworthy))
	{
		trigger_arr = GetEntArray( self.volume.script_noteworthy, "script_noteworthy" );
		
		foreach(obj in trigger_arr)
		{
			if(obj.classname == "trigger_multiple")
			{
				obj trigger_off();
			}
		}
	}
	
	self color_volume_advance_queue_remove();
}

color_volume_dupe_info( infos, colorCode )
{
	if( !infos.size )
	{
		return false;
	}
	
	foreach( info in infos )
	{
		if( info.colorCodes[ 0 ] == colorCode )
		{
			return true;
		}
	}
	
	return false;
}

// remove drone spawners from potential ally respawn spawners
remove_drone_spawners_from_respawners()
{
	spawners = getspawnerteamarray( "allies" );
	
	level._color_friendly_spawners = [];
	foreach ( spawner in spawners )
	{
		/*
		if ( !IsDefined( spawner.script_drone ) || !spawner.script_drone )
		{
			level._color_friendly_spawners[ spawner.classname ] = spawner;
		}*/
		//only want specific respawners because we delete these guys at the end and need to know they are the right ones.
		if( isDefined( spawner.script_noteworthy ) && spawner.script_noteworthy == "regroup_intro_friendlies_init" )
		{
			level._color_friendly_spawners[ spawner.classname ] = spawner;
		}
	}
}


//----- WOUNDED SOAP ----//
soap_wounded_start_position()
{
	switch( level.start_point )
	{
		case "courtyard":
			wounded_node = GetStruct( "anim_intro_room", "targetname" );
		break;
		case "escort":
			wounded_node = GetStruct( "anim_intro_room", "targetname" );
		break;
		case "regroup":
			wounded_node = GetNode( "regroup_soap_wounded_put_down1", "targetname" );
		break;
		case "maars shed":
			wounded_node = GetNode( "regroup_soap_wounded_put_down6", "targetname" );
		break;
		case "maars control":
			wounded_node = GetNode( "regroup_soap_wounded_put_down6", "targetname" );
		break;
		case "slide":
			wounded_node = GetNode( "maars_control_soap_wounded_put_down1", "targetname" );
		break;
		default:
			wounded_node = GetStruct( "anim_intro_room", "targetname" );
		break;
	}

	level.soap maps\intro_carry::setWounded( wounded_node );
	//level.carry_then_idle = true;
	level.nikolai thread maps\intro_carry::move_wounded_to_node_by_color();
	level.nikolai thread maps\intro_carry::move_wounded_to_node_monitor( level.soap, wounded_node );
}

soap_wounded_nikolai_carry( node_targetname )
{
	eNode = getNode( node_targetname, "targetname" );
	maps\intro_carry::carry_to_new_node( eNode );
	//level.nikolai maps\intro_carry::move_wounded_to_node( level.soap, eNode );
}

soap_wounded_nikolai_carry_struct( struct_targetname )
{
	eNode = getstruct( struct_targetname, "targetname" );
	maps\intro_carry::carry_to_new_node( eNode );
	//level.nikolai maps\intro_carry::move_wounded_to_node( level.soap, eNode );
}

prep_cinematic( cinematicName )
{
	setsaveddvar("cg_cinematicFullScreen", "0");	// don't draw while paused
	cinematicingame( cinematicName, 1 );	// start it paused
	level.current_cinematic = cinematicName;
}

play_cinematic( cinematicName, no_audio, no_pause )
{
	if( !isdefined( no_audio ) )
		aud_send_msg("begin_cinematic", cinematicName);
		
	if (isdefined(level.current_cinematic))
	{
		assert(level.current_cinematic == cinematicName);
		pauseCinematicInGame( 0 );
		setsaveddvar("cg_cinematicFullScreen", "1");	// start drawing
		level.current_cinematic = undefined;
	}
	else
	{
		cinematicingame( cinematicName );
	}
	if( !isdefined( no_pause ) || !no_pause )
		setsaveddvar("cg_cinematicCanPause", "1");	// allow pausing during movie
	wait 1;
	while( iscinematicplaying() )
	{
		wait .05;
	}
	if( !isdefined( no_pause ) || !no_pause )
		setsaveddvar("cg_cinematicCanPause", "0");	// back to the default
	
	if( !isdefined( no_audio ) )
		aud_send_msg("end_cinematic", cinematicName);
}

delete_enemies_in_volume()
{
	self waittill( "trigger" );
	
	volume = GetEnt( self.target, "targetname" );
	enemies = GetAIArray( "axis" );
	count = 0;
	/*
	foreach ( e in enemies )
	{
		if ( e IsTouching( volume ) )
		{
			count ++;
		}
	}
	
	if ( count > 3 )
	{
		return;
	}*/
	
	foreach ( e in enemies )
	{
		if ( e IsTouching( volume ) && ( Distance2D( e.origin, level.player.origin ) > 128 ) && ( !player_can_see_ai( e ) ) )
		{
			e notify( "killanimscript" );
			e Delete();
			count ++;
		}
	}
	print( "========================");
	print( "Deleted " + count + " enemies" );
	print( "========================");
	self Delete();
}

helicopter_dmg_hint()
{
	self endon ( "death" );
	
	while ( true )
	{
		self waittill( "damage", amount, attacker, direction_vec, point, type, modelName, tagName, partName, dFlags, weaponName );
		if ( attacker == level.player )
			display_hint ( "hint_heli_dmg" );	

	}
}

////////////////////////
//---- MG TURRETS ----//
////////////////////////

mg_player_target()
{
	level.player_mg_target = spawn_tag_origin();
	level.player_mg_target.origin = level.player.origin + ( 0, 0, 16 );
	level.player_mg_target linkTo( level.player );
	/*
	flag_wait( "mg_event_over" );
	
	level.player_mg_target delete(); 
	*/
}

mg_guy_think_maars_control( flag_to_wait_for_before_shooting_player, detach_flag )
{
	waittillframeend;
	
	self endon( "death" );
	
	if( !IsDefined( level.player_mg_target ) )
		thread mg_player_target();
	
	self AllowedStances( "stand" );
	self.ignoreme = true;
	self.fixednode = true;
	self.goalradius = 70;
	self.combatmode = "ambush";
	self disable_long_death();
	turret = self get_target_ent();
	
	self SetGoalPos( turret.origin );
	
	self waittill( "goal" );
	
	self UseTurret( turret );
	turret MakeUnusable();
	turret SetTurretTeam( "axis" );
	//turret SetTurretCanAIDetach( true );
	
	if( isDefined( turret.target ) && isDefined( detach_flag ) )
	{
		node = getnode( turret.target, "targetname" );
		self thread monitor_mg_turret_detach( node, detach_flag );
	}
	turret TurretFireEnable();
	self thread turret_track_ai( turret, flag_to_wait_for_before_shooting_player, true );
	self SetGoalPos( turret.origin );

	turret SetConvergenceTime( 7, "yaw" );
	turret SetConvergenceTime( 3, "pitch" );
	turret SetAISpread( 8 );
	
	self waittill( "damage" );
	self.ignoreme = false;
}

monitor_mg_turret_detach( node, detach_flag )
{
	self endon( "death" );
	
	flag_wait( detach_flag );
	self notify( "using_turret" );
	self setgoalnode( node );
	self.goalradius = 4;
	self waittill( "goal" );
	self.goalradius = 512;
}



mg_guy_think( flag_to_wait_for_before_shooting_player, only_shoot_at_player  )
{
	waittillframeend;
	
	self endon( "death" );
	
	if( !isdefined( level.player_mg_target ) )
		thread mg_player_target();
	
	self AllowedStances( "stand" );
	//self.favoriteenemy = level.player;
	self.ignoreme = true;
	self.fixednode = true;
	self.goalradius = 70;
	self.combatmode = "ambush";
	self disable_long_death();
	turret = self get_target_ent();
	turret hidepart( "tag_ground" );
	
	self SetGoalPos( turret.origin );
	
	self waittill( "goal" );
	
	self UseTurret( turret );
	turret MakeUnusable();
	turret SetTurretTeam( "axis" );
	turret SetTurretCanAIDetach( false );
	
	if( isdefined( only_shoot_at_player ) )
	{
		turret TurretFireDisable();
		thread turret_track_player_only( turret, flag_to_wait_for_before_shooting_player );
	}
	else
	{
		turret TurretFireEnable();
		self thread turret_track_ai( turret, flag_to_wait_for_before_shooting_player );
	}
	self SetGoalPos( turret.origin );

	trigger_wait_targetname( "mg_trigger" );
	wait( 0.05 );

	turret SetConvergenceTime( 7, "yaw" );
	turret SetConvergenceTime( 3, "pitch" );
	turret SetAISpread( 8 );

	self waittill( "damage" );	
	self.ignoreme = false;
}

turret_track_player_only( turret, flag_to_wait_for_before_shooting_player )
{
	self notify( "using_turret" );
	self endon( "death" );
	self endon( "using_turret" );
	
	flag_wait( flag_to_wait_for_before_shooting_player ); 
	turret TurretFireEnable();
	turret setmode( "manual_ai" );
	turret settargetentity( level.player_mg_target );

	wait( RandomFloatRange( 4, 8 ) );

	turret cleartargetentity();
	turret TurretFireDisable();
	self thread turret_track_player_only( turret, flag_to_wait_for_before_shooting_player );
}

turret_track_player( turret, flag_to_wait_for_before_shooting_player, always_shoot_player )
{
	self notify( "using_turret" );
	self endon( "death" );
	self endon( "using_turret" );
	
	turret setmode( "manual_ai" );
	turret settargetentity( level.player_mg_target );

	wait( RandomFloatRange( 4, 8 ) );
	
	if( isDefined( always_shoot_player ) )
		self thread turret_track_player( turret, flag_to_wait_for_before_shooting_player, always_shoot_player );
	else
		self thread turret_track_ai( turret, flag_to_wait_for_before_shooting_player, always_shoot_player );
}

turret_track_ai( turret, flag_to_wait_for_before_shooting_player, always_shoot_player )
{
	self notify( "using_turret" );
	self endon( "death" );
	self endon( "using_turret" );
	
	turret ClearTargetEntity();
	turret setmode( "auto_ai" );
	wait( RandomFloatRange( 1, 4 ) );
	
	if( !isdefined( flag_to_wait_for_before_shooting_player ) )
	{
		self thread turret_track_player( turret, undefined, always_shoot_player );
	}
	else
	{
		if( flag( flag_to_wait_for_before_shooting_player ) )
		{
			self thread turret_track_player( turret, flag_to_wait_for_before_shooting_player, always_shoot_player );
		}
		else
		{
			self thread turret_track_ai( turret, flag_to_wait_for_before_shooting_player, always_shoot_player );
		}
	}
}


////////////////////
//---- DRONES ----//
////////////////////


#using_animtree( "generic_human" );

drone_runner_think( notify_to_delete )
{
	self.moveplaybackrate = randomfloatrange( .8, 1.2 );
	
	if( !isAI( self ) )
	{
		self.runAnim = level.civ_runs[ RandomIntRange( 0, level.civ_runs.size ) ];
	
		if ( self.weapon != "none"  )
			self gun_remove();
	
		if ( isdefined( self.script_noteworthy ) )
		{
			if ( self.script_noteworthy == "idle_on_goal" )
			{
				//self solid();
				self.idleAnim = %civilain_crouch_hide_idle_loop;
				self drone_assign_unique_death( level.drone_deaths, true );
				self thread delete_on_notify ( notify_to_delete );
				self endon( "death" );
				self waittill( "goal" );
				self.skipdeathanim = 1;
				self.noragdoll = 1;
				self thread mission_fail_on_death();
				
			}
			else if ( self.script_noteworthy == "die_on_goal" )
			{
				self drone_assign_unique_death( level.drone_deaths_f );
			}
		}
	}
	else
	{
		self waittill( "goal" );
		self delete();
	}
}

drone_runner_combat_think( notify_to_kill, hold_fire, deatharray )
{
	self endon( "death" );
	if( isdefined( hold_fire ) )
	{
		self.ignoreall = true;
	}
	
	self drone_assign_unique_death( deatharray, true );
	
	level waittill( notify_to_kill );
	
	if( isdefined( hold_fire ) )
	{
		self.ignoreall = false;
	}
	
	wait( randomfloatrange( 0, .1 ) );
	//doing damage because drone_death_think is waiting for damage not death...
	self dodamage( self.health + 200, ( 0, 0, 0 ) );
}


drone_anim_think()
{
	self thread delete_on_notify();
	self.noragdoll = true;
	self endon( "death" );
	self thread mission_fail_on_death();
	if ( isdefined( self.script_bulletshield ) )
	{
		self thread deletable_magic_bullet_shield();
	}

	if ( isdefined( self.target ) )
		node = self get_target_ent();
	else
		node = self;
	
	self gunless_anim_check( node.animation );
	self drone_parameters( node );
	
	if ( IsAI( self ) && isdefined( self.moveoverride ) )
	{
		node anim_generic_reach( self, node.animation );
	}
	
	if ( IsSubStr( node.animation, "door" ) )
	{
		door = node get_target_ent();
		door assign_animtree( "door_peek" );
		door.animname = "door_peek";
		door thread anim_single_solo( door, node.animation + "_door" );
	}
	
	if ( IsSubStr( node.animation, "garage" ) )
	{
		door = node get_target_ent();
		nodeoffset = AnglesToForward( node.angles ) * - 32;//22
		node.origin = node.origin + nodeoffset;
		door.origin = door.origin + ( 0, 0, 51.013 );
		
		node anim_generic_first_frame( self, node.animation );
		
		if( isdefined( node.script_flag_wait ) )
		{
			flag_wait( node.script_flag_wait );
		}
		
		self thread drone_close_garage( door );
	}
	
	node anim_generic( self, node.animation );
	
	self delete();
}

drone_close_garage( door )
{
	wait 1;

	door linkto( self, "TAG_WEAPON_CHEST" );
	self waittillmatch( "single anim", "end" );
	door unlink();
}

drone_respawn()
{
	spawner = self.spawner;
	self.moveplaybackrate = randomfloatrange( .8, 1.2 );
	self.runAnim = level.civ_runs[ RandomIntRange( 0, level.civ_runs.size ) ];
	self drone_assign_unique_death( level.drone_deaths_f );
	self waittill( "death" );
	if( !flag( "regroup_drone_stop_loopers" ) )
		spawner spawn_ai();
}

drone_anim_then_idle_think( notify_to_delete )
{
	self thread delete_on_notify( notify_to_delete );
	self.noragdoll = true;
	self endon( "death" );
	self thread mission_fail_on_death();
	if ( isdefined( self.script_bulletshield ) )
	{
		self thread deletable_magic_bullet_shield();
	}
	
	if ( isdefined( self.target ) )
		node = self get_target_ent();
	else
		node = self;

	self drone_parameters( node );
	self gunless_anim_check( node.animation );
	
	
	
	node anim_generic( self, node.animation );
	
	if ( IsDefined( node.script_animation ) )
	{
		self.deathanim = getgenericanim( node.script_animation );
	}
	
	if ( isdefined( node.script_flag_set ) )
		flag_set( node.script_flag_set );
	
	if( isdefined( self.script_parameters ) && self.script_parameters == "idle_self" )
		self anim_generic_loop( self, node.animation + "_idle" );
	else
		node anim_generic_loop( self, node.animation + "_idle" );
}


drone_anim_then_die_think( notify_to_delete )
{
	self thread delete_on_notify( notify_to_delete );
	self.noragdoll = true;
	self endon( "death" );
	self thread mission_fail_on_death();
	if ( isdefined( self.target ) )
		node = self get_target_ent();
	else
		node = self;
		
	if ( isdefined( self.script_bulletshield ) )
	{
		self thread magic_bullet_shield();
	}
	
	self.deathanim = getgenericanim( node.animation + "_death" );
	
	self gunless_anim_check( node.animation );
	self drone_parameters( node );
	self thread drone_proper_death();
	
	if ( issubstr( node.animation, "crawl" ) )
	{
		self.a = spawnstruct();
		self.a.pose = "prone";
		self delaythread( 0.1, animscripts\pain::dyingCrawlBloodSmear );
	}
		
	node anim_generic( self, node.animation );
	
	if ( isdefined( self.script_bulletshield ) )
	{
		self stop_magic_bullet_shield();
	}
	self.noragdoll = true;
	self kill();
}

drones_wounded( notify_to_delete )
{
	self waittill( "trigger" );
	
	spawners = getentarray( self.target, "targetname" );
	
	foreach ( spawner in spawners )
	{
		spawnpoints = getstructarray( spawner.script_noteworthy, "targetname" );
		
		foreach ( p in spawnpoints )
		{
			spawner.origin = p.origin;
			spawner.angles = p.angles;
			if ( isdefined( p.target ) )
			{
				spawner.target = p.target;
			}
			drone = spawner spawn_ai( true );
			drone.script = "drone";
			drone_give_weaponsound( drone );
			
			drone.skipdeathanim = 1;
			drone.noragdoll = 1;
			drone thread mission_fail_on_death();

			if ( isdefined( p.script_bulletshield ) )
			{
				drone thread deletable_magic_bullet_shield();
			}
			
			drone thread delete_on_notify( notify_to_delete );
			drone thread drone_parameters( p );
			
			if ( IsDefined( p.script_animation ) )
			{
				drone.deathanim = getgenericanim( p.script_animation );
			}
			
			if ( IsDefined( p.script_noteworthy ) )
			{
				if ( p.script_noteworthy == "explosion_death" )
				{
					//drone thread assign_explosion_death();
				}
				else
				{
					drone thread maps\_drone::drone_fight( p.script_noteworthy, p );
					if ( IsSubStr( p.animation, "death" ) )
					{
						drone.deathanim = getgenericanim( p.animation );
						if ( issubstr( p.animation, "stagger" ) )
						{
							drone thread stagger_death();
						}
					}
				}
			}
			
			if ( IsDefined( p.animation ) )
			{
				if ( issubstr( p.animation, "prague_resistance_cover" ) )
				{
					drone thread drone_fighter( p );
				}
				else if ( !IsDefined( p.script_noteworthy ) || p.script_noteworthy == "explosion_death" )
				{
					drone gunless_anim_check( p.animation );
					if ( isdefined( p.script_delay ) && p.script_delay == 0 )
						p thread anim_generic_loop( drone, p.animation );
					else
						p delayThread( RandomFloatRange( 0, 1 ), ::anim_generic_loop, drone, p.animation );
				}
			}
			spawner.target = undefined;
		}
	}
}

drone_fighter( node )
{
	self endon( "death" );
	
	if ( issubstr( node.animation, "_l" ) && !issubstr( node.animation, "_l2r" ) )
		side = "_l";
	else
		side = "_r";
		
	anims = [
	"prague_resistance_cover_idle_once",
	"prague_resistance_cover_shoot" ];
	
	num = RandomIntRange( 0, anims.size );
	node thread anim_generic_loop( self, "prague_resistance_cover_idle" + side );
	if ( isdefined( node.script_flag_wait ) )
		flag_wait( node.script_flag_wait );
	node script_delay();
	node notify( "stop_loop" );
	while( 1 )
	{
		node anim_generic( self, anims[ num ] + side );
		num = num + 1;
		num = num % anims.size;
	}
}


dead_body_spawner_trigger()
{
	self waittill( "trigger" );
	t = self get_target_ent();
	structs = getstructarray( t.script_noteworthy, "script_noteworthy" );
	guys = [];
	foreach ( s in structs )
	{
		guy = t spawn_ai();
	//	guy thread deletable_magic_bullet_shield();
		guy.origin = s.origin;
		guy.angles = s.angles;
		guy SetCanDamage( false );
		
		anime = level.scr_anim[ "generic" ][ s.animation ];
		if ( IsArray( anime ) )
			anime = anime[ 0 ];
			
		guy gunless_anim_check( s.animation );
		guy AnimScripted( "endanim", s.origin, s.angles, anime );
		if ( isdefined( s.script_parameters ) )
		{
			if ( s.script_parameters == "notsolid" )
			{
				guy NotSolid();
			}
		}
		
		if ( issubstr( s.animation, "death" ) )
			guy delayCall( 0.05, ::setAnimTime, anime, 1.0 );
			
		guys[ guys.size ] = guy;	
	}
	
	cleanup_trigger = t get_target_ent();
	
	cleanup_trigger waittill( "trigger" );
	array_thread( guys, ::self_delete );
}


drone_assign_unique_death( deatharray, isSolid )
{
	if ( !IsDefined( deatharray ) )
		deatharray = level.drone_deaths;
	self.deathanim = deatharray[ RandomIntRange( 0, deatharray.size ) ];
	self.noragdoll = true;
	if( !isDefined( isSolid ) )
		self NotSolid();
	
	if ( !IsDefined( self.moveplaybackrate ) )
		self.moveplaybackrate = 1.0;
	
	movespeed = self.moveplaybackrate;
	self.moveplaybackrate = RandomFloatRange( movespeed * 0.8, movespeed );
	self thread drone_proper_death();
}


drone_proper_death()
{	
	self waittill_either( "death", "damage" );
	
	if ( !isdefined( self ) || isdefined(self.skipdeathfx) )
		return;
	
	//thread play_sound_in_space( "generic_death_falling_scream", self.origin );
	if ( cointoss() )
	{
		num = RandomIntRange( 1, 3 );
		self bodyshot( "bodyshot" + num, "J_SpineUpper" );
	}
	else
	{
		num = RandomIntRange( 1, 3 );
		self bodyshot( "headshot" + num, "tag_eye" );
	}
	wait( 2.0 );
	self animscripts\death::play_blood_pool();
}

bodyshot( fx, tag )
{
	origin = self GetTagOrigin( tag );

	PlayFX( getfx( fx ), origin );
}


gunless_anim_check( animation )
{
	if ( array_contains( level.gunless_anims, animation ) && self.weapon != "none" )
		self gun_remove();
	else if ( !isAI( self ) )
	{
		self.script = "drone";
		drone_give_weaponsound( self );
	}
}


drone_give_weaponsound( drone )
{
	drone.weaponsound = undefined;
	iRand = randomintrange( 1, 4 );
	
	//assign drone a random weapon for sound variety
	{
		if( iRand == 1 )
			drone.weaponsound = "drone_ak47_fire_npc";
		else if( iRand == 2 )
			drone.weaponsound = "drone_g36c_fire_npc";
		if( iRand == 3 )
			drone.weaponsound = "drone_fnp90_fire_npc";
	}
}

mission_fail_on_death()
{
	self waittill( "death", killer );
	
	if( self.type == "civilian" )
	{
		if ( isdefined( killer ) && killer == level.player )
		{
			//if the player killed himself and a civ don't fail for the civ.
			if( !isAlive( level.player ) )
				return;
				
			if ( IsDefined( level.MissionFailed ) && level.MissionFailed )
				return;
		
			SetSavedDvar( "hud_missionFailed", 1 );
		
			if ( IsDefined( level.player.failingMission ) )
				return;
		
			SetDvar( "ui_deadquote", &"SCRIPT_MISSIONFAIL_CIVILIAN_KILLED" );	// You shot a civilian. Watch your fire!
			SetBlur( 30, 2 );
			missionfailedwrapper();
		}
	}
}

delete_on_notify( message )
{
	if ( !IsDefined( message ) )
		message = "level_cleanup";
	self endon( "death" );
	level waittill( message );


	if ( IsDefined( self.magic_bullet_shield ) && self.magic_bullet_shield )
	{
		self stop_magic_bullet_shield();
	}
	
	self Delete();
}


drone_parameters( node )
{
	if ( !isdefined( node.script_parameters ) )
		return;
		
	if ( isSubstr( node.script_parameters, "notsolid" ) )
		self notsolid();
	//if ( isSubstr( node.script_parameters, "hero_head" ) )
		//self hero_head();
	if ( isSubstr( node.script_parameters, "cold_breath" ) )
	{
		self.a = SpawnStruct();
		self.a.movement = "stop";
		self thread animscripts\utility::PersonalColdBreath();
	}
}


/*
assign_explosion_death()
{
	self waittill( "death" );
	if ( !isdefined( self ) )
		return;
	node = get_target_ent( "explosion_death_node" );
	node.radius = 512;
	
	dir = undefined;
	{
		angles_to_damage = VectorToAngles( self.origin - node.origin );
		self.damageyaw = angles_to_damage[ 1 ] - self.angles[ 1 ];
		
		if ( self.damageyaw > 180 )
			self.damageyaw = self.damageyaw - 360;
		if ( ( self.damageyaw > 135 ) || ( self.damageyaw <= -135 ) )	// Front quadrant
		{
			dir = "b"; // b is causing clipping issues
		}
		else if ( ( self.damageyaw > 45 ) && ( self.damageyaw <= 135 ) )		// Right quadrant
		{
			dir = "l";
		}
		else if ( ( self.damageyaw > - 45 ) && ( self.damageyaw <= 45 ) )		// Back quadrant
		{
			dir = "f";
		}
		else
		{															// Left quadrant
			dir = "r";
		}
					
		if ( IsDefined( dir ) )
		{
			num = RandomIntRange( 0, level.explosion_deaths[ dir ].size );
			self.deathanim = level.explosion_deaths[ dir ][ num ];
			self.noragdoll = false;
		}
	}
}
*/


stagger_death()
{
	self waittill( "death" );
	
	if ( !isdefined( self ) )
		return;
	
	time = getAnimLength( self.deathanim ) * 0.3 ;
	self random_bloodspurt( time );
}


random_bloodspurt( time, tags )
{	
	if ( !isdefined( tags ) )
		tags = [ "j_spinelower", "j_spineupper", "j_shoulder_le", "j_shoulder_ri", "j_head" ];
	
	fxs = [ "bodyshot1", "bodyshot2", "headshot1", "headshot2" ];
	
	elapsed = 0;
	
	while( time > elapsed )
	{
		fxname = fxs[ RandomIntRange( 0,fxs.size ) ];
		PlayFXOnTag( getfx( fxname ), self, tags[ RandomIntRange(0,tags.size) ] );
		t = RandomFloatRange( 0.1, 0.2 );
		wait( t );
		elapsed = elapsed + t;
	}
}
