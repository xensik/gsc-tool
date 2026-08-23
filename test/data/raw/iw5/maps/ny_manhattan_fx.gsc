#include common_scripts\utility;
#include maps\_utility;
#include maps\_audio;
#include maps\_shg_fx;
//#include maps\_art;
#include maps\_anim;
#include maps\_vehicle;

main()
{
	//LittleBird DeathFX override		
	//maps\_vehicle::build_deathfx_override( undefined, "littlebird", "vehicle_little_bird_armed", "explosions/helicopter_explosion_secondary_small", 	"tag_engine", 	"littlebird_helicopter_secondary_exp", 	undefined, 			undefined, 		undefined, 		0.0, 		true );
	//maps\_vehicle::build_deathfx_override( undefined, "littlebird", "vehicle_little_bird_armed", "fire/fire_smoke_trail_L", 							"tag_engine", 	"littlebird_helicopter_dying_loop", 	true, 				0.05, 			true, 			0.5, 		true );
	//maps\_vehicle::build_deathfx_override( undefined, "littlebird", "vehicle_little_bird_armed", "explosions/helicopter_explosion_secondary_small",	"tag_engine", 	"littlebird_helicopter_secondary_exp", 	undefined, 			undefined, 		undefined, 		2.5, 		true );
	//maps\_vehicle::build_deathfx_override( undefined, "littlebird", "vehicle_little_bird_armed", "explosions/mortarExp_water", 						undefined, 		"littlebird_helicopter_crash", 			undefined, 			undefined,		undefined, 		- 1, 		undefined, 	"stop_crash_loop_sound" );

	//fx_flaknode

	//exploder number codes:
	// 950s = window exploders for building hit moment
	// 961 & 962 = two explosions out of the manhole
	// 963 = building chunk on fire
	// 964-968 = extra chunks falling and hitting street
	// 970-977 = hummer intro fx
	// 980-986 = window explosions on broad
	// 969 = the carhit fx
	// 971 = the building prehit fx
	// 972 = giant smoke column
	// 850s = giant water splashes near ship
	// 600-610 = wave splashes near ship
	// 700 = land explosions in downtown
	// 799		= large flak in sky
	// 800-810 = gun muzzle flashes off the ships
	// 559 = the sparks in the building
	// 558 = tiffanys godrays during room fight
	// 557 = tiffanys sprinklers
	// 556 = the anti-air runners and the random giant water splashes
	// 650 = the water drips on the slava
	// 560 = activate the smoke occulders in the hind ride
	// 555 = activate the giant smoke columns in the harbor
	// 1000 = zone1 fx
	// 333 = manhole cover open
	// 101 = heli strafe light
	// 102 = manhole light102
	// 400 = ambient hind ride explosion
	// 401-407 = hind finale rotor window bursts
	// 13000 = missile launch vfx
	// 200-205 = street explosions
	// 206 = 15 broad hind crash explosion
	// 301-330 = signal tower sequence exploders
	// 33	= brush destructible in the signal tower sequence
	// 1507-1508 = hind finale secondary explosions
	// 1509 = explosion moment on nyse ladder climb
	// 1510-1511 = nyse roof heli landing fx
	// 1512-1513 = additional nyse heli street dust
	// 1514 = stairwell bombshake moment
	

	flag_init("msg_start_fx_tiffanys_godrays");
	flag_init("exp_playing");
	flag_init("enable_distant_bombShakes");
	flag_init("msg_stop_amb_exp_hind_1");
	flag_init("msg_stop_amb_exp_hind");
	flag_init("msg_stop_amb_exp_hind_2");//stopping the explosions during the hind ride
	flag_init("aud_hind_finale_rotor_hit");
	flag_init("msg_fx_hindfinale_oxytanks");
	flag_init("msg_fx_windowexplosionA");
	flag_init("msg_fx_windowexplosionB");
	flag_init("msg_fx_windowexplosionC");


	thread precacheFX();
	
	//Controlling rendering globals
	thread init_smVals();//Setting default shadow values
	thread init_scrEffects();
	thread hind_ride_shadow_vals();
	
	thread treadfx_override();
	maps\createfx\ny_manhattan_fx::main();

	thread gaz_tail_lights();
	
	//One off stryker vfx
	thread start_stryker_fx();

	//ambient street fx threads
	thread start_man_landexplosions();
	thread start_man_hindexplosions();
	thread start_man_superflak();
	thread start_distant_bombShakes();
	thread start_amb_window_exp();

	//Intro threads
	thread setup_exchange_des_anim();
	thread exchange_missile_hit();
	//thread manhole_falling_dust();
	thread temp_anim_fx();

	//downtown threads
	thread broad_hallway_exp_moment();
	thread stairwell_bombshake_moment();
	
	//signal tower fx sequence
	thread signal_tower_fx_sequence();
	
	//Misc old Tiffanys threads	
	thread init_fx_rooms();
	thread spawn_fx_sparks();
	thread spawn_fx_room_godrays();

	//Nyse room dust & ladder climb
	thread nyse_fx_rooms ();
	thread fx_stockexchange_roofdust();
	thread ladder_climb_moment();
	thread heli_dust_moment();
	//thread nyse_hinddeath_override();
	
	//Hind ride threads
	thread start_more_obscure_smoke();
	thread toggle_giant_smoke_column();
	thread entering_hind_dof();
	thread starthindDust();
	thread fireCollapseFX();
	thread kill_all_env_fx();
	thread hind_toggle_dlights();
	thread setup_water_sheeting_volumes();
	//thread fx_fire_oxygen_tanks();
	//thread heli_strafe_light();//old thread no longer used

	//Lighting threads
	thread trigger_surface_vision_set();
	array_thread( GetEntArray( "traffic_light_green_red_blinky", "targetname" ), ::traffic_light_green_red_blinky );
	//array_thread( GetEntArray( "light_15broad_exterior_blinky", "targetname" ), ::light_15broad_exterior_blinky );


	
	
	//thread fx_zone_watcher(1000,"msg_fx_zone1");//the sewer
	thread fx_zone_watcher(2000,"msg_fx_zone2","msg_fx_zone2alt");//exchange street
	thread fx_zone_watcher(2500,"msg_fx_zone2_5");//exchange street that can also be viewed from the apartments
	thread fx_zone_watcher(3000,"msg_fx_zone3","msg_fx_zone3_1");//broad street
	thread fx_zone_watcher(3500,"msg_fx_zone3_5");//broad street that can be viewed from the apartment
	thread fx_zone_watcher(3600,"msg_fx_zone3_6");//giant smoke fx that can be viewed from broad street and can be viewed from the apartment
	thread fx_zone_watcher(3700,"msg_fx_zone3_7","msg_fx_zone3_7_1");//giant smoke fx that can be viewed from the nyse rooftop
	thread fx_zone_watcher(4000,"msg_fx_zone4","msg_fx_zone4_1");//1st floor bread street interior
	thread fx_zone_watcher(5000,"msg_fx_zone5");//apartment interior
	thread fx_zone_watcher_waitopen(5500,"msg_fx_zone5");//aa gunfire
	thread fx_zone_watcher(6000,"msg_fx_zone6");//back alley
	thread fx_zone_watcher(7000,"msg_fx_zone7");//tiffanys
	thread fx_zone_watcher(7500,"msg_fx_zone7", "msg_fx_zone8");//stuff seen from both tiffanys and wall street
	thread fx_zone_watcher(8000,"msg_fx_zone8","msg_fx_zone8_2");//wall street
	thread fx_zone_watcher(9000,"msg_fx_zone9");//nyse entryway
	thread fx_zone_watcher(10000,"msg_fx_zone10");  //nyse interior: second floor and up before rooftop
	thread fx_zone_watcher(11000,"msg_fx_zone11","msg_fx_zone11_1");//Apartment interior back hallways
	thread fx_zone_watcher(11500,"msg_fx_zone11_1","msg_fx_zone3_5");//Apartment interior back hallways going into apartments
	thread fx_zone_watcher(12000,"msg_fx_zone12");//Stairwell between the back alley and the apartments
	//13000 is taken for missile
	thread fx_zone_watcher(14000,"msg_fx_zone14");//vfx triggered at the initial hind ride
	thread fx_zone_watcher(15000,"msg_fx_zone15");//vfx triggered at the end of hind ride where finale is
	thread fx_zone_watcher(16000,"msg_fx_zone16");//fog triggered in nyse
	thread fx_zone_watcher(17000,"msg_fx_zone17");//nyse rooftop

	
	level thread convertOneShot();

	//thread manhole_strafe_light();
	//level thread sendMsg1();

	//level thread showAngles1();
	//level thread showTrace();
	thread flareTest();
}


gaz_tail_lights()
{
	level waitframe();
	gaz_destruct_tail_lights = GetEnt( "gaz_destructable", "script_noteworthy" );
	playfxontag(getfx("gaz_running_tail_lights"), gaz_destruct_tail_lights, "TAG_BRAKELIGHT_LEFT" );
	gaz_destruct_tail_lights waittill("stop_taking_damage");
	stopfxontag(getfx("gaz_running_tail_lights"), gaz_destruct_tail_lights, "TAG_BRAKELIGHT_LEFT" );
}


init_smVals()
{
	//Set the initial shadow values
	setsaveddvar("sm_spotlimit",1);
	setsaveddvar("sm_sunshadowscale",.85);
	setsaveddvar("sm_sunsamplesizenear",.25);
	setsaveddvar("fx_alphathreshold",9);
}

hind_ride_shadow_vals()
{
	//Set shadow values during hind ride. Longer view but scaled down more for optimization.
	flag_wait("entering_hind");
	setsaveddvar("sm_sunsamplesizenear",.8);
	setsaveddvar("sm_sunshadowscale",.65);
	
	
	
	
}

start_stryker_fx()
{
	can_start = 0;
	playing = [0,0,0];
	all = 0;
	while(all<2)//wait for stykers to be initialized
	{
		
		stryker = level.intro_stryker;
		if(isdefined(stryker) && playing[0]==0) 
		{
			all++;
			playing[0]=1;
			level.intro_stryker thread stryker_exhaust_tread();
		}
		stryker = level.broad_stryker;
		if(isdefined(stryker) && playing[1]==0) 
		{
			all++;
			playing[1]=1;
			level.broad_stryker thread stryker_exhaust_tread();
		}
		stryker = level.broad_stryker02;
		if(isdefined(stryker) && playing[2]==0) 
		{
			all++;
			playing[2]=1;
			level.broad_stryker02 thread stryker_exhaust_tread();
		}
		level waitframe();
	}
	
}

stryker_exhaust_tread()
{
	self endon( "death" );
	playfxontag(getfx("ny_stryker_tread"),self,"tag_wheel_front_left");
	playfxontag(getfx("ny_stryker_tread"),self,"tag_wheel_front_right");
	playfxontag(getfx("ny_stryker_tread"),self,"tag_wheel_back_left");
	playfxontag(getfx("ny_stryker_tread"),self,"tag_wheel_back_right");
	for(;;)
	{
		playfxontag(getfx("stryker_exhaust"),self,"tag_engine_left");
		wait(.1);
	}
}


/*********************************

	SIGNAL TOWER FX SEQUENCE START

***********************************/

signal_tower_fx_sequence()
{
	//
	wait(.1);
	jammer_destroyed = getent ( "jamming_tower_destroyed", "targetname" );
	org = getent ( "org_tower_collapse", "targetname" );
	thread signal_debris_atplayer();



	flag_wait("thermite_detonated");
	
	//if( level.ps3 )	setsaveddvar("r_halfparticles",1);
	PhysicsExplosionSphere( (-2067,1417,1614), 400, 100, 2.0 );
	
	//do screen flash
	thread signal_tower_flash();
	jammer_destroyed thread signal_tower_line_dust();
	thread signal_tower_misc_explosions();

	wait(.5);
	//start the spreading fire
	PhysicsExplosionSphere( (-2067,1417,1614), 400, 100, 2.0 );
	exploder(301);//the spreading fire
	wait(.5);
	//start the inital tower fire
	exploder(302);
	exploder(303);
	wait(1.0);
	
	//Animation starts here
	//start climbing fires
	thread dish_sep();
	thread signal_tower_climbing_fire();
	thread signal_tower_climbing_elec();
	thread signal_tower_amb_dest_fx();
	thread signal_fence_rattle();//shake the fence when the tower falls
	thread signal_powerline_fire();//start the powerline fires
	
	
	//final explosion to send the tower over
	wait(7.0);//7.0
	exploder(308);
	wait(1.83);//8.83
	exploder(313);//the tower fall dust
	screenshake(.35,.5,.1,.1);
	//if( level.ps3 )	setsaveddvar("r_halfparticles",0);

}
//5.6

signal_debris_atplayer()
{
		//Toss some chickens
	dests = GetEntArray( "ny_roof_debris", "targetname" );
	init_orig = [];
	wait(.1);
	foreach (debris in dests)
	{
		debris hide();
	}
	flag_wait("thermite_detonated");
	//debris = [];
	player_comp_vect = vectornormalize(anglestoforward(level.player.angles));
	i = 0;
	foreach (debris in dests)
	{
		debris show();
		m_name = debris.model;
		launch_vect = vectornormalize(level.player.origin + (0,0,100) - debris.origin);
		random_vect = 85 * (randomfloatrange(-1,1),randomfloatrange(-1,1),0);
		launch_vect += player_comp_vect * 200 + random_vect + (0,0,300 + randomfloat(1) * 100) + launch_vect * (670 + 70 * randomfloat(.51));
		//debris launch(launch_vect);
		debris PhysicsLaunchClient(debris.origin+(0,0,5),launch_vect*3.5);
		//debris rotatevelocity((560*randomfloatrange(-1,1),361*randomfloatrange(-1,1),361*randomfloatrange(-1,1)),1);
	}
	wait(.75);
	//foreach (debris in dests)
	//{
	//	debris delete();
	//}	

}

signal_tower_flash()
{
	currVis = getdvar("vision_set_current");
	visionsetnaked("generic_flash",.08);
	wait(.17);
	visionsetnaked("ny_manhattan",.08);
}

signal_tower_misc_explosions()
{
	wait(3.0);
	exploder(306);//electronic exp 1
	wait(2.2);
	exploder(307);//electronic exp 2
	wait(2.5);
	exploder(303);//fuel exp 1
	wait(.9);//at 5.6
	exploder(309);//elec exp on tower before break
	wait(2.6);
	exploder(305);//another bg elec exp
	wait(1.7);
	exploder(304);
	
}

signal_tower_line_dust()
{	
	//
	loc1 = self gettagorigin("cableC_endStick");
	loc2 = self gettagorigin("cableD_endStick");
	wait(2.0);
	//cableA_endStick -5.13
	wait(4.23);
	playfxontag(getfx("single_tower_cable_end"),self,"cableD_endStick");
	playfx(getfx("large_electric_exp"),loc2,(270,0,0));
	//cableB_endStick -5.3
	wait(1.5);
	playfxontag(getfx("single_tower_cable_end"),self,"cableC_endStick");
	playfx(getfx("large_electric_exp"),loc1,(270,0,0));
	
}

get_firefx(num, data)
{
	org = [];
	ang = [];
	ents = [];
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
			if ( int(ent.v[ "exploder" ]) == int(num) )
			{
				org[(org.size)]=ent.v["origin"];
				ang[(ang.size)]=ent.v["angles"];
				ents[(ents.size)]=ent;
			}
		}	
	data.v["origins"] =  org;
	data.v["angles"] = ang;
	data.v["ents"] = ents;
}


signal_tower_amb_dest_fx()
{
	wait(6.0);
	data = spawnStruct();
	data2 = spawnStruct();//second wave of amb destruction
	get_firefx("311",data);//misc destructible createfx ents
	get_firefx("314",data2);//misc destructible createfx ents
	ents = data.v["ents"];
	ents2 = data2.v["ents"];
	fire_playing = [];
	for(i=0;i<ents.size;i++)
	{
		fire_playing[i] = 0;
	}
	fire_playing2 = [];
	for(i=0;i<ents2.size;i++)
	{
		fire_playing2[i] = 0;
	}
	fire_steps = 20.0;
	fire_time = 24.0;
	for(h = 0;h < fire_steps ;h++)
	{	
		start_h = (-2087,1424,1614);//1500
		diff = 1500.00 * (h / fire_steps);
		for(i=0;i<ents.size;i++)
		{
			if(distance(ents[i].v["origin"],start_h)<diff && fire_playing[i] != 1)
			{
				ents[i] activate_individual_exploder();
				fire_playing[i] =1;
			}
		}
		wait(fire_time/fire_steps);
	}	

	//loop through the following for four of minutes
	for(j=0;j<5;j++)
	{
		for(i=0;i<ents2.size;i++)
		{
			fire_playing2[i] = 0;
		}
		fire_steps = 20.0;
		fire_time = 45.0;
		for(h = 0;h < fire_steps ;h++)
		{	
			start_h = (-2087,1424,1614);//1500
			diff = 1200.00 * (h / fire_steps);
			for(i=0;i<ents2.size;i++)
			{
				if(distance(ents2[i].v["origin"],start_h)<diff && fire_playing2[i] != 1)
				{
					ents2[i] activate_individual_exploder();
					fire_playing2[i] =1;
				}
			}
			wait(fire_time/fire_steps);
		}	
	}

}

dish_sep()
{
	jammer_destroyed = getent ( "jamming_tower_destroyed", "targetname" );
	//tower fire locations
	data = spawnStruct();
	get_firefx("317",data);
	fire_locs = data.v["origins"];
	fire_angs = data.v["angles"];
	ents = data.v["ents"];
	fire_playing = [];
	
	
	for(i=0;i<fire_locs.size;i++)
	{
		fire_playing[i] = 0;
	}
	//spawn the tag_origins
	fire_origins = [];
	for(i=0;i<fire_locs.size;i++)
	{
		fire_origins[i] = spawn_tag_origin();
		fire_origins[i].origin = fire_locs[i];
		fire_origins[i].angles = fire_angs[i];
		fire_origins[i] linkto(jammer_destroyed,"tower01");
	}
	
	wait(1.0);
	//do dish A
	for(i=0;i<ents.size;i++)
	{
		if(ents[i].v["ender"]=="dishA")
		{
			playfxontag(getfx("large_electric_exp"),fire_origins[i],"tag_origin");
			fire_playing[i] =1;
		}
	}
	wait(7.0);
	for(i=0;i<ents.size;i++)
	{
		if(ents[i].v["ender"]=="dishB")
		{
			playfxontag(getfx("large_electric_exp"),fire_origins[i],"tag_origin");
			fire_playing[i] =1;
		}
	}
	
	
}

signal_tower_climbing_elec()
{
	wait(2.0);
	jammer_destroyed = getent ( "jamming_tower_destroyed", "targetname" );
	//tower fire locations
	data = spawnStruct();
	get_firefx("312",data);
	fire_locs = data.v["origins"];
	fire_angs = data.v["angles"];
	ents = data.v["ents"];
	fire_playing = [];
	
	
	for(i=0;i<fire_locs.size;i++)
	{
		fire_playing[i] = 0;
	}
	//spawn the tag_origins
	fire_origins = [];
	for(i=0;i<fire_locs.size;i++)
	{
		fire_origins[i] = spawn_tag_origin();
		fire_origins[i].origin = fire_locs[i];
		fire_origins[i].angles = fire_angs[i];
		fire_origins[i] linkto(jammer_destroyed,"tower01");
	}
	
	
	fire_steps = 20.0;
	fire_time = 7.3;
	for(h = 0;h < fire_steps ;h++)
	{	
		start_h = 1708.00;
		end_h = 2200.00;
		diff = end_h - start_h;
		diff *= h / fire_steps;
		for(i=0;i<fire_locs.size;i++)
		{
			if(fire_origins[i].origin[2]<diff+start_h && fire_playing[i] != 1)
			{
				playfxontag(getfx("large_electric_exp"),fire_origins[i],"tag_origin");
				fire_playing[i] =1;
			}
		}
		wait(fire_time/fire_steps);
	}
	wait(14);
	//Cleanup
	for(i=0;i<fire_locs.size;i++)
	{
		stopfxontag(getfx("fire_line_sm"),fire_origins[i],"tag_origin");
		fire_origins[i] delete();
	}
		
}	
	
	
	
signal_tower_climbing_fire()
{
	//wait(.);
	jammer_destroyed = getent ( "jamming_tower_destroyed", "targetname" );
	//tower fire locations
	data = spawnStruct();
	get_firefx("310",data);
	fire_locs = data.v["origins"];
	fire_angs = data.v["angles"];
	fire_playing = [];
	
	
	for(i=0;i<fire_locs.size;i++)
	{
		fire_playing[i] = 0;
	}
	//spawn the tag_origins
	fire_origins = [];
	for(i=0;i<fire_locs.size;i++)
	{
		fire_origins[i] = spawn_tag_origin();
		fire_origins[i].origin = fire_locs[i];
		fire_origins[i].angles = fire_angs[i];
		fire_origins[i] linkto(jammer_destroyed,"tower01");
	}
	

	
	fire_steps = 20.0;
	fire_time = 2.0;
	for(h = 0;h < fire_steps ;h++)
	{	
		start_h = 1708.00;
		end_h = 1900.00;
		diff = end_h - start_h;
		diff *= h / fire_steps;
		for(i=0;i<fire_locs.size;i++)
		{
			if(fire_origins[i].origin[2]<diff+start_h && fire_playing[i] != 1)
			{
				playfxontag(getfx("fire_line_sm_cheap"),fire_origins[i],"tag_origin");
				fire_playing[i] =1;
			}
		}
		wait(fire_time/fire_steps);
	}
	wait(12);
	//Cleanup
	for(i=0;i<fire_locs.size;i++)
	{
		stopfxontag(getfx("fire_line_sm"),fire_origins[i],"tag_origin");
		fire_origins[i] delete();
	}
		
}	
	
	

signal_fence_rattle()
{
	wait(8.6);
	pivot = GetEnt( "nyse_fence_anim", "targetname" );

	animated_bridge_fences = GetEntArray( "nyse_fence_", "targetname" );


	foreach ( piece in animated_bridge_fences )
	{
		piece NotSolid();
		piece SetContents( 0 );
		piece LinkTo( pivot );
	}

	
	start_angles = pivot.angles;
	pivot RotateTo( start_angles,  .15, .071, .071 );
	start_val = 0;
	
	mis = spawn_tag_origin();
	
	amount = -20;
	for ( ;; )
	{
		time = abs( amount ) * 0.0475;
		if ( time < 0.5 )
			time = 0.25;
		pivot RotateTo( ( start_angles[0]+ amount, start_angles[1] , start_angles[2] ), time, time * 0.5, time * 0.5 );
		amount *= -0.7;
		wait( time );
		if ( abs( amount ) <= 2 )
			break;
	}
}


signal_powerline_fire()
{
	wait(.3);
	jammer_destroyed = getent ( "jamming_tower_destroyed", "targetname" );
	//tower fire locations
	data = spawnStruct();
	get_firefx("315",data);
	fire_locs = data.v["origins"];
	fire_angs = data.v["angles"];
	ents = data.v["ents"];
	fire_playing = [];
	//wait after the tower falls
	for(i=0;i<fire_locs.size;i++)
	{
		fire_playing[i] = 0;
	}
	//spawn the tag_origins
	fire_origins = [];
	for(i=0;i<fire_locs.size;i++)
	{
		fire_origins[i] = spawn_tag_origin();
		fire_origins[i].origin = fire_locs[i];
		fire_origins[i].angles = fire_angs[i];
	}
	

	
	fire_steps = 20.0;
	fire_time = 5.0;
	for(h = 0;h < fire_steps ;h++)
	{	
		start_h = (-2087,1424,1614);//1500
		diff = 900.00 * (h / fire_steps);
		for(i=0;i<ents.size;i++)
		{
			if(distance(ents[i].v["origin"],start_h)<diff && fire_playing[i] != 1)
			{
				ents[i] activate_individual_exploder();
				fire_playing[i] =1;
				if(isdefined(ents[i].v["ender"]))
				{
					if(ents[i].v["ender"] == "msg_fx_lineexp1") 
					{
						wait(1.0);
						level notify("msg_setoff_nyse_exp1");
						//signal_tower_flash();
					}
						
					if(ents[i].v["ender"] == "msg_fx_lineexp2") 
					{
						wait(1.0);
						level notify("msg_setoff_nyse_exp2");
						//signal_tower_flash();
					}
				}
			}
		}
		wait(fire_time/fire_steps);
	}	

	
}

init_scrEffects()
{
	//Use non-distortion fires on hummer deaths via overrides
	//( classname, type, model, effect, tag, sound, bEffectLooping, delay, bSoundlooping, waitDelay, stayontag, notifyString, delete_vehicle_delay )
	//hummer minigun
	//build_deathfx_override("script_vehicle_hummer_minigun","hummer_minigun","vehicle_hummer","fire/firelp_med_pm_atlas_nodist_cheap", "TAG_CAB_FIRE", "fire_metal_medium", undefined, undefined, true, 0 );
	//build_deathfx_override("script_vehicle_hummer_minigun","hummer_minigun","vehicle_hummer", "explosions/vehicle_explosion_hummer_minigun", "tag_deathfx", "car_explode", undefined, undefined, undefined, 0 );

	wait(.1);
	//if( level.ps3 )	setdvar("r_distortion",0);
}



flareTest()
{
	flag_wait("entering_hind");
	thread fx_spot_lens_flare_dir("lights_lf_test",(-29, -6, 0),10000);
}

start_man_hindexplosions()
{
	
	wait(10.0);
	thread shg_spawn_tendrils(400,"smoke_geotrail_genericexplosion",5,500,2000,10,30,200,75,1200);
    expPos =     [(-4723.47, -3139.63, 2752.6)
        ,(-3731.84, -2029.16, 2799.87)
        ,(-3911.85, -1136.19, 2797.83)
        ,(-3871.81, -295.381, 3432.95)
        ,(-3996.06, 742.784, 2986.2)
        ,(-4948.13, -4699.07, 2252.31)
        ,(-3676.3, -4113.55, 1974.48)
        ,(-7745.4, -2947.22, 3413.39)
        ,(-7532.97, -3389.05, 3272.03)
        ,(-7993.39, -2583.71, 3281.43)
        ,(-7825.95, -2735.18, 4114.56)
        ,(-9837.14, -3326.57, 4584.54)
        ,(-10494.4, -3792.76, 4285.43)
        ,(-10421.3, -3647.76, 4619.95)
        ,(-10366.3, -3727.49, 3952.17)
        ,(-11799.4, -4781.56, 4117.62)
        ,(-12397.4, -5939.89, 4185.6)
        ,(-12046.1, -5291.72, 5020.61)
        ,(-12392.1, -5881.45, 4746.81)
        ,(-12629.3, -6285.67, 4452.1)
        ,(-10974.6, -8493.58, 3685.14)
        ,(-10484.9, -8525.86, 3330.77)
        ,(-10484.9, -8525.86, 3330.77)
        ,(-9992.39, -8818.68, 3719.72)
        ,(-9239.87, -9097.68, 3301.68)
        ,(-7978.5, -10026.6, 3788.68)
        ,(-7290.33, -9843.54, 3784.12)
        ,(-7633.41, -9674.08, 3291.68)
        ,(-8090.39, -10067.1, 2821.38)
        ,(-6973.91, -9944.56, 2915.12)
        ,(-7134.57, -9878.67, 2464.34)
        ,(-7043.57, -7480.28, 3256.53)
        ,(-6821.67, -7281.61, 3204.43)
        ,(-6672.38, -7241.97, 3617.14)
        ,(-7083.39, -7724.91, 3588.41)
        ,(-6945.34, -7226.35, 2764.36)
        ,(-6598.13, -4962.05, 3390.48)
        ,(-6700.62, -5037.11, 3012.84)
        ,(-6860.98, -4775.1, 3200.37)
        ,(-7067.37, -4470.25, 3038.22)
        ,(-12010.7, -5280.78, 2460.17)
        ,(-12496.2, -6058.87, 2462.49)
        ,(-10709.7, -3941.02, 2392.49)
        ,(-10709.7, -3941.02, 2392.49)
        ,(-12687.2, -2572.97, 2750.06)
        ,(-11743.8, -8123.64, 2624.81)
        ,(-12476.4, -7868.53, 2647.51)
        ,(-14925.6, -6756.64, 3298.52)
        ,(-14955.7, -7356.05, 3426.85)
        ,(-3807.92, -1962.47, 1717.8)
        ,(-4641.78, -2177.37, 1866.32)
        ,(-4631.36, -2719.82, 1542.89)
        ,(-4609.85, -3399.33, 1866.63)
        ,(-3703.84, -3427.87, 1835.05)
        ,(-4643.71, -2076.54, 868.674)
        ,(-3952.13, -1816.64, 919.216)
        ,(-4648.86, -1808.37, 886.547)
        ,(-9381.33, -3512.95, 2458.42)
        ,(-9839.28, -3746.29, 2226.69)
        ,(-9925.82, -3759.75, 2997.53)
        ,(-11080.9, -4091.61, 2454.12)
        ,(-7548.85, -3154.99, 2698.93)
        ,(-7147.64, -3205.07, 2961.14)
        ,(-7663.33, -3007.76, 2583.72)
        ,(-9743.96, -8922.13, 2796.55)
        ,(-10607.5, -8621.42, 3508.83)
        ,(-10706.6, -8584.48, 2502.18)
        ,(-12291.2, -5725.56, 2837.08)
        ,(-7185.32, -7508.32, 2376.36)
        ,(-6807.07, -7063.87, 2440.57)
        ,(-12494.9, -10857.7, 3844.31)
        ,(-13262.9, -10582.6, 3987.45)
        ,(-14374.3, -10620.4, 3848.83)
        ,(-15234.3, -10163.2, 3843.31)
        ,(-15345.9, -9509.54, 3165.93)
        ,(-12387.7, -8319.88, 2856.03)
        ,(-5587.13, -6339.12, 3191.43)
        ,(-5241.26, -5797.22, 3187.48)
        ,(-5687.7, -6079.25, 3896.24)
        ,(-5626.74, -6432.51, 2556.17)
        ,(-5542.88, -5845.09, 2580.03)
        ,(-7019.32, -7327.15, 2107.85)
        ,(-11871, -5042.7, 3207.29)
        ,(-12574.1, -6222.49, 3123.79)
        ,(-12305.9, -4272.42, 3133.6)
        ,(-11873.6, -4770.54, 3113.43)];
	flag_wait ( "level_started_fx" );
	for(;;)
	{
		//Wait a # of seconds
		randomInc = randomfloatrange(-.35,.35)+1;
		wait(randomInc);
		//flag_waitopen("exp_playing");
		flag_wait_either("msg_stop_amb_exp_hind_1","msg_stop_amb_exp_hind");
		flag_waitopen("msg_stop_amb_exp_hind_2");
		fxEnts = [];
		//Find the explosions the player is looking at
		playerAng = level.player getplayerangles();
		eye = vectornormalize(anglestoforward(playerAng));
		ent = get_exploder_ent(400);
		found_exp = -1;
		final_exp_pos = [];
		for ( i = 0;i < expPos.size;i++ )
		{
			if ( !isdefined( ent ) )
				continue;
			toFX = vectornormalize(expPos[i]-level.player.origin);
			if(vectordot(eye,toFX)>.45) 
			{
				found_exp = 1;
				final_exp_pos[final_exp_pos.size] = expPos[i];
			}
		}
		
		//to1.origin = self.player getorigin();
		if(found_exp >0)
		{
			curr_exp_num = randomInt((final_exp_pos.size+1));
			if(isdefined(curr_exp_num))
			{
				ent.v["origin"] = final_exp_pos[curr_exp_num];
				if(isdefined(ent.v["origin"]) && isdefined(ent)) exploder(400);
				aud_send_msg("msg_audio_fx_ambientExp", final_exp_pos[curr_exp_num]);
			}
			wait(1);
			//flag_clear("exp_playing");
		}
		
	}
}




heli_strafe_light()
{
	heli_origin = (-3766.11,661.521,477);
	heli_origin_end = (-3904.37,635.203,447);
	wait(1.0);
	flag_wait ( "obj_broad_complete" );
	level waitframe();
	if (isdefined(level.broad_hind_fly))
	{
		//level.broad_hind_fly vehicle_lights_on( "spot" );
	}	
	flag_wait ( "broad_hind_strafe_setup" );
	if (isdefined(level.broad_hind_fly))
	{
		//level.broad_hind_fly vehicle_lights_off( "spot" );
	}	
	flag_wait ( "broad_hind_strafe" );
	if (isdefined(level.broad_hind_fly))
	{
		//playfxontag(getfx("ny_manhattan_generic_spotlight_lit"),level.broad_hind_fly,"tag_flash");
		//level.broad_hind_fly waittill( "reached_dynamic_path_end" );
		//if(isdefined(level.broad_hind_fly)) stopfxontag(getfx("ny_manhattan_generic_spotlight_lit"),level.broad_hind_fly,"tag_flash");
	}
	
	
}




sendMsg1()
{
/#
	wait(2);
	//setDvarIfUninitialized( "curr_exp_num", 1 );
	
	while(1)
	{
		level waitframe();
		val = check_zkey_press();
		if(val)
		{
			orgn = [];
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
				if ( int(ent.v[ "exploder" ]) < 700 || int(ent.v[ "exploder" ]) > 789 )
					continue;
				orgn[(orgn.size)]=ent.v["origin"];
			
			}
			for(i=0;i<orgn.size;i++)
			{
				print(","+orgn[i]+"\n");
				//level waitframe();	
			}

			//level notify("intro_missile_1_hits");
		}
	}
#/		
}


enemy_hind_spotlight()
{
	//self vehicle_lights_on( "spot" );
}


enemy_hind_spot_finale()
{
	//playfxontag(getfx("hind_spot"),self,"tag_passenger");
	wait(7.2);
	//stopfxontag(getfx("hind_spot"),self,"tag_passenger");
}

/*
###################################################
Manhattan hind rotor hit sequence
###################################################
*/

hind_toggle_dlights()
{
	level waitframe();
	level waittill("spawn_hind06b");
	setsaveddvar("r_dlightlimit",0);
	//iprintlnbold("toggle_lights");
	level waittill("start_finale");
	wait(5);
	setsaveddvar("r_dlightlimit",4);
	//iprintlnbold("toggle_lights");
}


start_hind_secondary_explosions()
{
	thread shg_spawn_tendrils(1508,"ny_hind_smoketrail",10,200,1000,10,30,200,180,800);
	thread shg_spawn_tendrils(1507,"ny_hind_smoketrail",7,200,1000,10,30,200,180,800);

	wait(34.43);//1204
	exploder(1508);
	wait(5.6);//1377
	exploder(1507);
	exploder(1547);
	
}

exploder_wait_hind(num,msg)
{
	level waittill(msg);
	exploder(num);
}

//This manages the fx for when the helicopter scrapes the side of the building in the 
//	finale - it plays a scrape effect and blows up windows as the rotor hits them
hind_finale_rotor_hit()
{
	//Setting this flag to stop the ambient explosions
	flag_set("msg_stop_amb_exp_hind_2");
	//start at appropriate time - starts at frame 776 (947-171 anim start frame)
	
	thread start_hind_secondary_explosions();
	
	wait(5.0);
	if ( ( level.Console && level.ps3 ) || !level.Console )
	{
		SetHalfResParticles( true );
	}
	//the anim finishes at 975 - so it goes for 28 frames or .93 seconds or 19 server fames
	wait(20.86);
	//Setting up the window exploders here
	glassents = [];
	for(j = 401;j<408;j++)
	{
		glassents[(glassents.size)] = get_exploder_ent(j);
		thread exploder_wait_hind(j,("msg_fx_wait_"+string(j)));
	}
	//cast a ray from the rotor to the buidling
	rayVectorDir = vectornormalize( ( -11700, -8127, 2488 ) - ( -11659, -7857, 2452 ) );//anglestoright(self.angles));
	startForwardDir = vectornormalize(anglestoforward(self.angles));
	rayStartPoint = self gettagorigin("main_rotor_jnt");
	rayStartPoint += startForwardDir * 0;
	//cast our ray toward the building and play our anim
	trace = BulletTrace( rayStartPoint, rayStartPoint+rayVectorDir*1200, false, undefined);
	hitPos = trace["position"]+(0,0,50);
	fxforward = trace["normal"];
	mis = spawn_tag_origin();
	mis.origin = hitPos;
	mis.angles = vectortoangles(fxforward);	
	playfxontag(getfx("rotor_impact_concrete_sparks"),mis,"tag_origin");
	for(i=0;i<20;i++)
	{
		//cast a ray from the rotor to the buidling
		rayVectorDir = vectornormalize( ( -11700, -8127, 2488 ) - ( -11659, -7857, 2452 ) );//vectornormalize(anglestoright(self.angles));
		startForwardDir = vectornormalize(anglestoforward(self.angles));
		rayStartPoint = self gettagorigin("main_rotor_jnt");
		rayStartPoint += startForwardDir * 0;
		//cast our ray toward the building and play our anim
		trace = BulletTrace( rayStartPoint, rayStartPoint+rayVectorDir*1200, false, undefined);
		hitPos = trace["position"]+(0,0,50);
		fxforward = trace["normal"];
		mis.origin = hitPos;
		mis.angles = vectortoangles(fxforward);	
		//play the rotor scrape fx at the hit point with a slight offset from the surface of the building
		playfx(getfx("rotor_impact_concrete"),hitPos-rayVectorDir*4,mis.angles);
		aud_send_msg("aud_hind_finale_rotor_impact");
		flag_set("aud_hind_finale_rotor_hit");
		//each frame, look to see if our rotor is at the same level as the exploder, if so play it
		for(k=0;k<7;k++)
		{
			currorg = glassents[k].v["origin"];
			if(currorg[2]<hitPos[2]+80) 
			{
				level notify(("msg_fx_wait_"+string(k+401)));
			}
		}
		level waitframe();
	}
	stopfxontag(getfx("rotor_impact_concrete_sparks"),mis,"tag_origin");
	mis delete();
	//wait(1.0);
	//if ( ( level.Console && level.ps3 ) || !level.Console )
	//{
	//	SetHalfResParticles( false );
	//}
	
	
}




/*
###################################################
Manhattan Intro sequnce with building hit

Manhattan building hit sequence
###################################################
*/
//Anim starts at frame 331


anim_sun(current,target,time)
{
	sunlight = current;
	totalchange = target - sunlight;
	
	for(i=0;i<time*20;i++)
	{
		new_sunlight = sunlight +totalchange * (float(i+1)/float(time*20));

		setsunlight(new_sunlight[0],new_sunlight[1],new_sunlight[2]);
		level waitframe();
	}
		//adding the resetsunlight to fix pop when crossing stages with the same values.
		resetsunlight();
}

hummer_intro_vision()
{
	//Anim starts at 331
	wait(.2); //Adding this wait in order to better synchronize flash with audio.
	currVis = getdvar("vision_set_current");
	currSun = (1, 0.960784, 0.866667) * 1.55;
	//visionsetnaked("ny_manhattan_intro",0);
	thread anim_sun(currSun,(4.0,3.8,3.5),.1);
	wait(22.3);//21.8
	//visionsetnaked(currVis,2);
	thread anim_sun((4.0,3.8,3.5),currSun,2.0);
}

do_window_glass(ent,tag)
{
	wait(7.15);
	wait(2.25);
	playfxontag(getfx("ny_hummerglasswindow"),ent,tag);
	wait(12.7);
	playfxontag(getfx("ny_hummerglasswindowfall"),ent,tag);
	
	
}

launch_taxi_guy()
{
	wait(.65);
	player_comp_vect = vectornormalize(anglestoforward(level.player.angles));
	launch_vect = vectornormalize((-4348,-3588,36) + (0,0,750) - self.origin);
	launch_vect += launch_vect * (5470);
	self startragdollfromimpact("torso_upper",launch_vect);
	
}

hummer_intro()
{
	//Anim starts at 331 - 
	thread hummer_chunk_fall();
	thread hummer_intro_vision();	
	hummer_model = Getent( "intro_humvee", "targetname" );
	//thread do_window_glass(hummer_model,"tag_fx_14");
	wait(1.0);
	thread shg_spawn_tendrils(961,"smoke_geotrail_genericexplosion",7,500,2000,10,30,200,75,1200);
	thread shg_spawn_tendrils(962,"smoke_geotrail_genericexplosion",7,500,2000,10,30,200,75,1200);
	
	fog_tag = spawn_tag_origin();
	fog_tag linkto(hummer_model,"tag_fx_13",(0,40,0),(90,0,0));
	
	
	//Start hummer ambient fx
	exploder(970);
	
	//Start hummer fx spotlight
	exploder(973);	
	
	//hummer dust
	wait(5.5);
	playfxontag(getfx("ny_hummerfallingdust"),hummer_model,"tag_fx_22");
	
	
	//The first hit should happen at 829 (498) 16.6 sec
	wait(13);//14.4
	kill_exploder(970);
	wait(.1);
	exploder(971);
	wait(1.1);
	//The second should happen at 970	
	wait(2.1);
	exploder (962);
	//kill hummer fx spotlight
	wait(1.5);
	kill_exploder(973);
		
}

hummer_chunk_fall()
{
	wait(32.25);
	exploder(968);//chunk5
	aud_send_msg("building_chunk",[968,1.0]);
	wait(1.0);
	level thread screenshake(.25,.5,.15,.2);
	wait(2.5);
	exploder(965);//chunk2
	aud_send_msg("building_chunk",[965,1.0]);
	wait(.9);
	level thread screenshake(.35,.5,.15,.2);
	wait(0.25);
	exploder(964);//chunk
	aud_send_msg("building_chunk",[964,2.0]);
	wait(2.0);//
	//physicsexplosionsphere(( -4542.35, -2437.19, -112 ),1000,200,6);
	level thread screenshake(.3,.5,.15,.2);
	wait(1.5);
	exploder(966);
	aud_send_msg("building_chunk",[966,1.0]);
	wait(1.0);
	level thread screenshake(.2,.5,.15,.2);
	wait(1.5);
	exploder(967);
	aud_send_msg("building_chunk",[967,1.0]);
	wait(1.0);
	level thread screenshake(.2,.5,.15,.2);
	
}

temp_anim_fx()
{
	wait(.1);
	if(!level.createfx_enabled) return 0;
	
	org = getent ( "sewer_exit_scripted_node", "targetname" );
	humvee = Getent( "intro_humvee", "targetname" );
	humvee.animname = "intro_humvee";
	humvee assign_animtree();
	guys = [];
	guys [0] = humvee;
	
	
	
	org anim_first_frame( guys, "ny_intro" );
	

	
	//org anim_single_run ( guys, "ny_intro" );
}

manhole_falling_dust()
{
	/*
	wait(1.0);
	thread shg_spawn_tendrils(961,"smoke_geotrail_genericexplosion",7,500,2000,10,30,200,75,1200);
	thread shg_spawn_tendrils(962,"smoke_geotrail_genericexplosion",7,500,2000,10,30,200,75,1200);
	
	flag_wait("start_open_manhole_cinematic");
	manhole = getent ( "manhole", "targetname" );
	wait(3.6);//start of the guy pulling back the lid
	playfxontag(getfx("manhole_fallingdirt_ny"),manhole,"tag_root");
	wait(.5);
	playfxontag(getfx("manhole_fallingdirt_ny"),manhole,"tag_root");
	wait(1.5);
	//playfxontag(getfx("manhole_fallingdirt_ny"),manhole,"skel_manhole");
	wait(2.25);
	playfxontag(getfx("manhole_fallingdirt_ny2"),manhole,"skel_manhole");
	exploder(961);
	wait(.5);
	playfxontag(getfx("manhole_fallingdirt_ny2"),manhole,"skel_manhole");
	playfxontag(getfx("manhole_fallingdirt_ny2"),manhole,"skel_manhole");
	exploder (962);
	*/
}


setup_exchange_des_anim()
{
	if (!is_specialop() )
	{
		waitframe();
		des_anim = getent("ny_manhattan_building_exchange_01_facade_des","targetname");
		des_anim.animname = "building_des";
		des_anim  setAnimTree();
	}

	//des_animb = getent("ny_manhattan_building_exchange_01_facade_desb","targetname");
	//des_animb.animname = "building_des";
	//des_animb  setAnimTree();


}


do_hit_contrast()
{
	wait(6.06); //Adding this wait in order to better synchronize flash with audio.
	level thread screenshake(.4,.52,.13,.153);
	currVis = getdvar("vision_set_current");
	visionsetnaked("generic_flash",.2);
	wait(.1);
	visionsetnaked(currVis,.2);
}

chunk_blur()
{
	//curr_blur = level.dofDefault;
	start = level.dofDefault;
	curr_org = self gettagorigin("tag_fx14");
	curr_eye = level.player.origin;
	curr_dist = length(curr_org - curr_eye);
	dof_see_knife = [];
	last_dof = [];
	dof_see_knife[ "nearStart" ] = 60;
	dof_see_knife[ "nearEnd" ] = 1000;
	dof_see_knife[ "nearBlur" ] = 10;
	dof_see_knife[ "farStart" ] = curr_dist+1000;
	dof_see_knife[ "farEnd" ] = curr_dist+3500;
	dof_see_knife[ "farBlur" ] = 1;
	last_dof = dof_see_knife;
	dur = 20 * 5;
	blend_dof( start, dof_see_knife, .2 );
	wait(.15);
	for(i = 0; i < 25; i ++)
	{
		curr_org = self gettagorigin("tag_fx14");
		curr_eye = level.player.origin;
		curr_dist = length(curr_org - curr_eye);
		dof_see_knife[ "farStart" ] = curr_dist+1000;
		dof_see_knife[ "farEnd" ] = curr_dist+3500;
		blend_dof( last_dof, dof_see_knife, .2 );
		last_dof = dof_see_knife;
		wait(.2);
	}
	blend_dof(dof_see_knife, start, .5 );
	

	//level.player maps\_art::setDoFTarget( 1.0, 200, 500.0, 3000.0, 5000.0, 8.0, 1.0 );
}

fov_anim()
{
	//flag_wait( "start_open_manhole_cinematic" );
	wait(.25);
	lerp_fov_overtime(.20,25);
	wait(2.5);
	lerp_fov_overtime(4,65);
	
	
}

do_chunk_anim(anim_obj,chunks,tags)
{
	for(;;)
	{
		for(i=0;i<chunks.size;i++)
		{
			if(isdefined(chunks[i]))
			{
				tag_ang = anim_obj gettagangles(tags[i]);
				tag_org = anim_obj gettagorigin(tags[i]);
				chunks[i].origin = tag_org;
				chunks[i].angles = tag_ang;
			}
		}
		level waitframe();
	}
}

exchange_launch_tendrils()
{
	wait(.25);
	//959 second small explosoin
	exploder(959);
	wait(.5);
	//958 tendrils
	exploder(958);
	//wait(.75);
	exploder(960);//shockwave

}

exchnage_missile_prehit()
{
	flag_wait("msg_fx_missilehit");
	exploder(-951);
}


exchange_missile_hit()
{
	flag_init("msg_fx_zonefiretower");
	wait(1.0);
	
	//Assign the trail effect for the missile
	level._effect[ "contrail12" ]					= level._effect[ "smoke_geotrail_missile_shadow" ];
	level._effect[ "contrail" ]					= level._effect[ "smoke_geotrail_missile_shadow" ];
	

	//Assigning individual chunks to the animation for lighting
	chunks = [];//the chunk models are from 
	tags = [];
	chunks[0] = getent("chunk106","targetname");//tag_fx14 - tags are from the man_player_sewer_exit
	chunks[1] = getent("chunk100_dusty","targetname");//8
	chunks[2] = getent("chunk102_dusty","targetname");//10
	chunks[3] = getent("chunk105_dusty","targetname");//13
	chunks[4] = getent("chunk118_dusty","targetname");//26
	chunks[5] = getent("chunk119_dusty","targetname");//27
	chunks[6] = getent("chunk120_dusty","targetname");//28
	chunks[7] = getent("chunk121_dusty","targetname");//29
	chunks[8] = getent("chunk143_dusty","targetname");//51
	chunks[9] = getent("chunk151_dusty","targetname");//59
	tags[0] = "tag_fx14";
	tags[1] = "tag_fx8";
	tags[2] = "tag_fx10";
	tags[3] = "tag_fx13";
	tags[4] = "tag_fx26";
	tags[5] = "tag_fx27";
	tags[6] = "tag_fx28";
	tags[7] = "tag_fx29";
	tags[8] = "tag_fx51";
	tags[9] = "tag_fx59";

	//chunk_106 = getent("des_chunk106","targetname");
	des_anim = getent("ny_manhattan_building_exchange_01_facade_des","targetname");
	des_brush = getentarray("ny_manhattan_building_exchange_01_des_brush","targetname");
	des_anim hide();


	
	//Attach firefx to chunk 106 using a createfx
	data = spawnStruct();
	get_firefx("963",data);
	ents = data.v["ents"];
	fire_playing = [];
	for(i=0;i<ents.size;i++)
	{
		fire_playing[i] = 0;
	}
	//spawn the tag_origins
	fire_origins = [];
	for(i=0;i<ents.size;i++)
	{
		fire_origins[i] = spawn_tag_origin();
		fire_origins[i].origin = ents[i].v["origin"];
		fire_origins[i].angles = ents[i].v["angles"];
		fire_origins[i] linkto(chunks[0]);
	}	

	
	//start tendril thread on exploder 951
	thread shg_spawn_tendrils(958,"ny_buildingexplosion_trail",14,800,1700,10,45,20,70,800);
	thread shg_spawn_tendrils(951,"fire_smoke_trail_s",2,800,1200,60,105,20,55,400);

	
	thread exchnage_missile_prehit();//wait for missile to hit causing glass to blow

	
	//Begin main fx sequence
	level waittill("intro_missile_1_hits");

	
	foreach(currBrush in des_brush)
	{
		currBrush delete();
	}
	
	des_anim show();
	
	thread do_chunk_anim(des_anim,chunks,tags);
	des_anim thread anim_single_solo ( des_anim, "manhattan_sewer_exit" );

	


	
	
	exploder(955);//explosions
	exploder(950);//glass explodes & shockwave
	exploder(951);//mushroom cloud
	thread exchange_launch_tendrils();
	wait(.25);	
	exploder(969);//the carhit
	thread do_hit_contrast();//carhit blur & flash
	for(i=0;i<ents.size;i++)
	{
		playfxontag(getfx(ents[i].v["fxid"]),fire_origins[i],"tag_origin");
	}
	wait(.15);
	exploder(957);
	wait(.85);
	des_anim thread chunk_blur();
	level thread screenshake(.3,2,.3,.53);
	playfxontag(getfx("chunk_contrail_ny"),des_anim,"tag_fx14");
	wait(1.05);
	//thread fx_zone_watcher_late(13000,"msg_fx_zonefiretower");
	wait(2.8);
	exploder(954);//hits on building top
	level thread screenshake(.3,.52,.13,.153);
	
	//
	//Set off the final chunk hit
	wait(1.54);
	setblur(5,.125);
	stopfxontag(getfx("chunk_contrail_ny"),des_anim,"tag_fx14");
	exploder(953);//final dust hit
	//Kill all the chunks except 106
	for(k=1;k<10;k++)
	{
		chunks[k] delete();
	}
	wait(.125);
	dest_taxi = getent("intro_taxi","script_noteworthy");
	dest_taxi hide();
	setblur(0,.35);//set blur back to normal
	
	
	//Final glass and debris fall
	wait(1.5);
	exploder(956);//
	wait(16.0);
	kill_exploder(956);
	

	
	
	
		
}


start_man_superflak()
{
	wait(1.0);
	flaknodes = getentarray("fx_flaknode","targetname");
	//thread shg_spawn_tendrils(799,"smoke_geotrail_genericexplosion_c",8,500,700,15,30,50,75,2000);
	flakfxent = get_exploder_ent(799);
	missilefxent = get_exploder_ent(798);
	for(;;)
	{
		//Wait a # of seconds
		randomInc = randomfloatrange(-1,1)+2;
		wait(randomInc);
		flag_waitopen("exp_playing");
		playerAng = level.player getplayerangles();
		eye = vectornormalize(anglestoforward(playerAng));
		flakorigin = (0,0,0);
		smallestDot = -1.0;
		for(i=0;i<flaknodes.size;i++)
		{
			flako = flaknodes[i] getorigin() + (0,0,3000);
			toflaknode = vectornormalize(flako-level.player.origin);
			//print(flaknodes[i].origin);
			currDot = vectordot(eye,toflaknode);
			if(currDot>.65 && currDot>smallestDot) 
				{
					flakorigin = flako;
					smallestDot = currDot;
				}
		}
		neworigin = (0,0,0)+flakorigin+vectornormalize(randomvector(2))*2750;
		flakfxent.v["origin"]= neworigin;
		missilefxent.v["origin"]= neworigin;
		if(smallestDot>0) 
		{
			//flag_set("exp_playing");
			exploder(798);
			wait(.65);
			exploder(799);
			wait(1);
			//flag_clear("exp_playing");
		}
	}	
	
	
	
}


start_man_landexplosions()
{
	
	wait(10.0);
	expPos = [(-4187.7, -6955.04, 1965.78)
		,(-3033.99, -8245.14, 3389.71)
		,(-3575.84, -8408.69, 4263.41)
		,(811.9, 4777.98, 1729.21)
		,(1304.43, 6871.75, 2361.23)
		,(2167.09, 9577.33, 2361.58)
        ,(-2239.31, -8157.38, 3216.13)
        ,(-1767.18, -7948.25, 1893.35)
        ,(-1038.06, -8217.92, 4171.56)
        ,(-4681.31, 2736.97, 2090.5)
        ,(-3619.6, -9270.64, 3002.34)
        ,(-4037.59, -9934.14, 4787.15)
        ,(-3898.69, 4571.14, 1899.09)
        ,(-4717.15, 5422.82, 2262.04)
        ,(-4361.88, 6272.97, 3151.94)
        ,(-4606.62, 8595.08, 5823.76)
        ,(-4627.77, 7595.02, 5929.47)
        ,(1760.04, 7058.97, 2825)
        ,(1895.64, 8401.99, 4110.88)
        ,(2368.26, 9237.65, 4167.63)
        ,(1637.58, 9245.96, 6379.27)
        ,(1599.8, 9280.21, 5831.7)
        ,(3012.36, 9540.14, 6484.93)
        ,(3511.33, -808.979, 3015.82)
        ,(4992.68, -106.21, 4695.27)
        ,(5273.71, -1700.75, 5943.67)
        ,(5244.27, -2235.7, 8177.53)
        ,(2033.37, 999.022, 4260.44)
        ,(4827.54, 125.473, 3710.74)
        ,(3866.09, 548.33, 1266.61)
        ,(3862.02, 412.45, 2300.68)
        ,(4123.97, 353.335, 2060.32)
        ,(3616.9, -620.285, 1403.18)
        ,(3934.43, 563.696, 6214.36)
        ,(-2730.88, -8034.51, 1873.09)
        ,(-3469.97, -8078.36, 1886.72)
        ,(-4125.73, -8731.3, 2004.36)
        ,(-3732.74, -8142.53, 1118.17)
        ,(-4259.3, -6338.27, 1053.16)
        ,(-4531.53, -6101.44, 3117.44)
        ,(-2940.23, -8599.88, 5167.89)
        ,(-4700.34, 3499.22, 2659.31)
        ,(-3866.85, 6908.11, 3016.26)
        ,(-4540.91, 7185.43, 4532.95)
        ,(-4890.23, 6264.49, 3620.93)
        ,(-4198.43, 7192.49, 3621.29)
        ,(1859.05, 1296.63, 4863.39)
        ,(3713.3, 803.918, 6259.06)
        ,(3940.47, -1154.09, 5454.34)
        ,(2414.13, 8499.75, 2887.67)
        ,(2451.14, 8504.87, 3553.44)
        ,(2473.76, 9166.14, 4539.4)
        ,(1834.32, 7830.89, 2890.5)
        ,(1054.29, 2353.56, 1287.26)
        ,(738.125, 4247.55, 2890.5)
        ,(715.53, 5078.57, 2541.24)
        ,(-2449.77, -11697.9, 3232.45)
        ,(-2001.22, -13896.2, 3906.78)
        ,(-2331.26, -14562.9, 3274.91)
        ,(-3049.43, -18343.6, 3743.02)
        ,(-1537.31, -10542.8, 2032.75)
        ,(-8092.85, 1132.9, 3769.34)
        ,(-7914.71, 770.858, 4552.8)
        ,(-7747.38, 90.5198, 4527.27)
        ,(-7754.06, 675.826, 5790.95)
        ,(-8348.75, -134.581, 5964.13)
        ,(-5766.8, 1375.46, 3785.41)
        ,(-7466.81, 492.474, 3395.12)
        ,(-7926.47, -170.617, 1978.1)
        ,(-8006.18, -36.8266, 3203.16)
        ,(-4088.9, 2432.67, 2446.66)
        ,(-4646.15, 8323.33, 4891.13)
        ,(-4607.25, 8643.29, 5495.8)];
		thread shg_spawn_tendrils(700,"smoke_geotrail_genericexplosion",7,500,2000,10,30,200,75,1200);
	flag_wait ( "level_started_fx" );
	for(;;)
	{
		//Wait a # of seconds
		randomInc = randomfloatrange(-.5,.5)+1.5;
		wait(randomInc);
		//flag_waitopen("exp_playing");
		flag_waitopen("msg_fx_zone4");
		flag_waitopen("msg_fx_zone5");
		flag_waitopen("msg_fx_zone10");
		flag_waitopen("msg_stop_amb_exp_hind_1");
		flag_waitopen("msg_stop_amb_exp_hind");
		fxEnts = [];
		//Find the explosions the player is looking at
		playerAng = level.player getplayerangles();
		eye = vectornormalize(anglestoforward(playerAng));
		ent = get_exploder_ent(700);
		found_exp = -1;
		final_exp_pos = [];
		for ( i = 0;i < expPos.size;i++ )
		{
			if ( !isdefined( ent ) )
				continue;
			toFX = vectornormalize(expPos[i]-level.player.origin);
			if(vectordot(eye,toFX)>.45) 
			{
				found_exp = 1;
				final_exp_pos[final_exp_pos.size] = expPos[i];
			}
		}
		
		//to1.origin = self.player getorigin();
		if(found_exp >0)
		{
			curr_exp_num = randomInt((final_exp_pos.size+1));
			if(isdefined(curr_exp_num))
			{
				ent.v["origin"] = final_exp_pos[curr_exp_num];
				if(isdefined(ent.v["origin"]) && isdefined(ent)) exploder(700);
				aud_send_msg("msg_audio_fx_ambientExp", final_exp_pos[curr_exp_num]);
			}
			wait(1);
			//flag_clear("exp_playing");
		}
		
	}
}


start_amb_window_exp()
{
	wait(.1);
	flag_wait("msg_fx_windowexplosionA");
	exploder(980);
	flag_wait("msg_fx_windowexplosionB");
	exploder(981);
	flag_wait("msg_fx_windowexplosionC");
	exploder(982);
	
}


start_distant_bombShakes()
{
	to1 = spawn_tag_origin();
	to1.origin = self.player getorigin();
	to1.angles = ( 270, 0, -45);
	if(!isdefined(level.bombshake_interval))
	{
		level.bombshake_interval = 15;//was at 20
		level.bombshake_interval_rand = 7;//was at 5
	}
	
	wait(15.0);//Make sure the fade in completes before it starts
	for(;;)
	{
		flag_waitopen("entering_hind");					// Wait (don't play) if player is in the hind.
		flag_wait("enable_distant_bombShakes");	// Wait until this system is enabled manually.
		flag_waitopen("msg_stop_fx_bombshakes"); //stop if under a scaffold		
		if (!flag("entering_hind") && flag("enable_distant_bombShakes")) // Still have to check. (e.g., entering_hind could be set while waiting on "enable_distant_bombShakes").
		{
			offsetDist = 1008;//look up 10 ft
			to1.origin = self.player getorigin();
			trace = BulletTrace( (self.player.origin+(0,0,12)), self.player.origin+(0,0,1200), false, undefined);
			hitDist = distance(to1.origin,trace["position"]);
			if(hitDist<200)
			{
				//Send the message to audio
				aud_send_msg("msg_audio_fx_bombshake");
				fx_bombShakes("falling_dirt_light","viewmodel_medium",.127,2,.3,.53);
				//Start a screen shake
				/*level.player playrumbleonentity("viewmodel_medium");
				level thread screenshake(.127,2,.3,.53);
				//Start casting rays and spawn dust falling
				for(i=0;i<6;i++)
				{
					wait(.1);
					tracedir = vectornormalize(anglestoforward(self.player getplayerangles())+(randomfloatrange(-1,1),randomfloatrange(-1,1),.5))*1000;
					trace1 = BulletTrace( (self.player.origin+(0,0,12)), self.player.origin+(0,0,12)+tracedir, false, undefined);
					hitdist1 = distance(self.player.origin,trace1["position"]);
					vdot = vectordot((0,0,-1),vectornormalize(trace["normal"]));
					//print(hitdist1);
					//print("\n");
					//print(trace["normal"]);
					//print("\n");
					if(hitdist1<450 && vdot>.75)
					{
						//line(trace1["position"]-(0,0,12),trace1["position"]+(0,0,12),(1.0,1.0,1.0),true,120);
						playfx(getfx("falling_dirt_light"),trace1["position"]);
					}
					
				}
				*/
			}
		}
		
		randomInc = randomfloatrange((level.bombshake_interval_rand * -1),level.bombshake_interval_rand)+level.bombshake_interval;
		wait(randomInc);
	}	
}




trigger_surface_vision_set()
{
	level waittill("msg_fx_set_surface_visionset");
	thread vision_set_fog_changes( "ny_harbor_surface", 3 );
}




check_key_press()
{
	if(level.player buttonPressed("space")==true) return true;
	else return false;
	//{
	//	 if(self.player buttonPressed("space")==true) print3d(( -42897, -8920, 277 ),"key presed",(1.0,0.0,0),1,3,1);
	//}
}


showTrace()
{
		to1 = spawn_tag_origin();
	
	for(;;)
	{
		wait(1.0);
		offsetDist = 30000;
		to1.origin = self.player getorigin();
		to1.origin += vectornormalize(anglestoforward(self.player getplayerangles()))*offsetDist;

		trace = BulletTrace( (self.player.origin+(0,0,24)), self.player.origin+(0,0,-2000), false, undefined);
		playfx(getfx(""),trace["position"]);
		
	}
}

spawn_fx_sparks()
{
	for(;;)
	{
	wait(5);
	exploder(559);
	}	
	
}

init_fx_room_damage()
{
	roomInfo = spawnStruct();
	if ( !isdefined( level.fx_room ) )
		level.fx_room = [];
	level.fx_room[ level.fx_room.size ] = roomInfo;
	roomInfo.v["health"] = 0;
	roomInfo.v["healrate"] = 15;
	roomInfo.v["numVFX"] = 0;
	roomInfo.v["vfxLife"] = 10;
	roomInfo.v["vfxOffset"]=(0,0,0);
	roomInfo.v["fxid"] = getfx( "room_dust_nyharbor" );
	roomInfo.v["roomTrigger"] = self;
	return roomInfo;
}

heal_fx_room(currRoom)
{
	trigObj = currRoom.v["roomTrigger"];
	for(;;)
	{
		wait(1.0);
		currRoom.v["health"] -= currRoom.v["healrate"];
		if (currRoom.v["health"]<0) currRoom.v["health"] = 0;
		//print3d(trigObj.origin+(currRoom.v["vfxoffset"]),(currRoom.v["health"]),(1.0,0.0,0),1,3,1);
	}	
}

spawn_fx_in_room(currRoom)
{
		
		playfx(currRoom.v["fxid"],(currRoom.v["roomTrigger"].origin+currRoom.v["vfxoffset"]),(0,0,1),(1,0,0));
		currRoom.v["numVFX"]+=1;
		wait(currRoom.v["vfxLife"]);
		currRoom.v["numVFX"]-=1;
}

spawn_fx_room_godrays()
{
	
	flag_wait("msg_start_fx_tiffanys_godrays");
	wait(5.0);
	thread fx_zone_watcher_late(558,"msg_fx_zone7");
	thread fx_zone_watcher_late(557,"msg_fx_zone7");
	
	
}



playdust_fx_room(currRoom)
{
	for(;;)
	{
		wait(7.0);
		if(currRoom.v["health"]>50 && currRoom.v["numVFX"]<6)	thread spawn_fx_in_room(currRoom);
		if(currRoom.v["health"]>150 && currRoom.v["numVFX"]<6)	thread spawn_fx_in_room(currRoom);
		if(currRoom.v["health"]>300 && currRoom.v["numVFX"]<6)	thread spawn_fx_in_room(currRoom);
	}
}

start_fx_room_damage(currRoom)
{
	trigObj = currRoom.v["roomTrigger"];
	thread heal_fx_room(currRoom);
	thread playdust_fx_room(currRoom);
	for(;;)
	{
		trigObj waittill("damage");
		currRoom.v["health"]++;
		flag_set("msg_start_fx_tiffanys_godrays");
	}
}

init_fx_rooms()
{
	//init tiffany's
	tifftrig = getent("tiffanys_fx_damage_trigger","targetname");
	tiffroom = tifftrig init_fx_room_damage();
	tiffroom.v["fxid"]=getfx( "room_dust_nyharbor" );
	tiffroom.v["vfxoffset"]=(0,0,-150);
	tiffroom.v["healrate"] = 10;
	thread start_fx_room_damage(tiffroom);
}

traffic_light_green_red_blinky()
{
	self endon( "death" );
	// Note from invasion .map might be a good idea.
	// use scrolling texture and save some resources here.
	while ( 1 )
	{
		self SetModel( "com_traffic_red_light" );
		wait .75;
		self SetModel( "com_traffic_green_light" );
		wait .75;
	}
}

light_15broad_exterior_blinky()
{
	self endon( "death" );
	while ( 1 )
	{
		self SetModel( "com_lightbox_on" );
		wait .2;
		self SetModel( "com_lightbox" );
		wait .75;
	}
}

precacheFX()
{
	level._effect[ "thick_dark_smoke_giant_nydowntown" ] 	= LoadFX( "smoke/thick_dark_smoke_giant_nydowntown" );//placed by fxman
	level._effect[ "gaz_running_tail_lights" ] 	= LoadFX( "misc/gaz_running_tail_lights" );
	level._effect[ "ny_ceiling_collapse_concrete" ] 	= LoadFX( "maps/ny_manhattan/ny_ceiling_collapse_concrete" );//placed by fxman
	level._effect[ "falling_dirt_light_1" ] 	= LoadFX( "dust/falling_dirt_light_1" );//placed by fxman
	level._effect[ "ny_ladderclimb_dustrungs" ] 	= LoadFX( "maps/ny_manhattan/ny_ladderclimb_dustrungs" );//placed by fxman
	level._effect[ "ny_ladderclimb_dust" ] 	= LoadFX( "maps/ny_manhattan/ny_ladderclimb_dust" );//placed by fxman
	level._effect[ "ny_hind_windowhit" ] 	= LoadFX( "maps/ny_manhattan/ny_hind_windowhit" );//placed by fxman
	level._effect[ "ny_heli_predatorexp" ] 	= LoadFX( "maps/ny_manhattan/ny_heli_predatorexp" );//placed by fxman
	level._effect[ "ny_heli_hinddeath" ] 	= LoadFX( "maps/ny_manhattan/ny_heli_hinddeath" );//placed by fxman
	level._effect[ "ny_towerambientexp" ] 	= LoadFX( "maps/ny_manhattan/ny_towerambientexp" );//placed by fxman
	level._effect[ "firelp_med_pm_cheap_nolight" ] 	= LoadFX( "fire/firelp_med_pm_cheap_nolight" );//placed by fxman
	level._effect[ "ny_heli_landing_smokedisturb" ] 	= LoadFX( "maps/ny_manhattan/ny_heli_landing_smokedisturb" );//placed by fxman
	level._effect[ "gas_pipe_spray" ] 	= LoadFX( "water/gas_pipe_spray" );//placed by fxman
	level._effect[ "ny_mortarexp_dud" ] 	= LoadFX( "maps/ny_manhattan/ny_mortarexp_dud" );//placed by fxman
	//level._effect[ "mortarExp_concrete_dud" ] 	= LoadFX( "explosions/mortarExp_concrete_dud" );//placed by fxman
	level._effect[ "ny_initmissilehit" ] 	= LoadFX( "maps/ny_manhattan/ny_initmissilehit" );//placed by fxman
	level._effect[ "amb_dust_light_med_graylit" ] 	= LoadFX( "dust/amb_dust_light_med_graylit" );//placed by fxman
	level._effect[ "powerline_runner_small2" ] 	= LoadFX( "explosions/powerline_runner_small2" );//placed by fxman
	level._effect[ "ny_hind_lastHit" ] 	= LoadFX( "maps/ny_manhattan/ny_hind_lastHit" );//placed by fxman
	level._effect[ "ny_papers_heli_landing" ] 	= LoadFX( "maps/ny_manhattan/ny_papers_heli_landing" );//placed by fxman
	level._effect[ "ny_nyse_laddermoment" ] 	= LoadFX( "maps/ny_manhattan/ny_nyse_laddermoment" );//placed by fxman
	level._effect[ "ny_hind_smoketrail" ] 	= LoadFX( "maps/ny_manhattan/ny_hind_smoketrail" );//placed by fxman
	level._effect[ "hind_finale_secondary_explosions" ] 	= LoadFX( "maps/ny_manhattan/hind_finale_secondary_explosions" );//placed by fxman
	level._effect[ "generic_explosion_nolight" ] 	= LoadFX( "explosions/generic_explosion_nolight" );//placed by fxman
	level._effect[ "oil_drip_small_continuous" ] 	= LoadFX( "misc/oil_drip_small_continuous" );//placed by fxman
	level._effect[ "battlefield_smk_directional_White_M_lit" ] 	= LoadFX( "smoke/battlefield_smk_directional_White_M_lit" );//placed by fxman
	level._effect[ "fire_ceiling_sm_slow" ] 	= LoadFX( "fire/fire_ceiling_sm_slow" );//placed by fxman
	level._effect[ "fire_line_verysmall_cheap" ] 	= LoadFX( "fire/fire_line_verysmall_cheap" );//placed by fxman
	level._effect[ "firelp_smokeonly_med" ] 	= LoadFX( "fire/firelp_smokeonly_med" );//placed by fxman
	level._effect[ "smoke_geotrail_missile_shadow" ] 	= LoadFX( "smoke/smoke_geotrail_missile_shadow" );//placed by fxman
	level._effect[ "window_explosion_glassy" ] 	= LoadFX( "explosions/window_explosion_glassy" );//placed by fxman
	level._effect[ "ny_stryker_tread" ] 	= LoadFX( "maps/ny_manhattan/ny_stryker_tread" );//placed by fxman
	level._effect[ "tread_road_stryker" ] 	= LoadFX( "treadfx/tread_road_stryker" );//placed by fxman
	level._effect[ "stryker_exhaust" ] 	= LoadFX( "misc/stryker_exhaust" );//placed by fxman
	level._effect[ "amb_smoke_black_small" ] 	= LoadFX( "smoke/amb_smoke_black_small" );//placed by fxman
	level._effect[ "ny_chunkBombs5" ] 	= LoadFX( "maps/ny_manhattan/ny_chunkBombs5" );//placed by fxman
	level._effect[ "ny_chunkBombs4" ] 	= LoadFX( "maps/ny_manhattan/ny_chunkBombs4" );//placed by fxman
	level._effect[ "ny_chunkBombs3" ] 	= LoadFX( "maps/ny_manhattan/ny_chunkBombs3" );//placed by fxman
	level._effect[ "ny_chunkBombs2" ] 	= LoadFX( "maps/ny_manhattan/ny_chunkBombs2" );//placed by fxman
	level._effect[ "ny_chunkBombs" ] 	= LoadFX( "maps/ny_manhattan/ny_chunkBombs" );//placed by fxman
	level._effect[ "ny_additionalchunks" ] 	= LoadFX( "maps/ny_manhattan/ny_additionalchunks" );//placed by fxman
	level._effect[ "ny_hummerglasswindowfall" ] 	= LoadFX( "maps/ny_manhattan/ny_hummerglasswindowfall" );//placed by fxman
	level._effect[ "generic_fallingdebris" ] 	= LoadFX( "misc/generic_fallingdebris" );//placed by fxman
	level._effect[ "ny_hummerglasswindow" ] 	= LoadFX( "maps/ny_manhattan/ny_hummerglasswindow" );//placed by fxman
	level._effect[ "fire_smoke_trail_s" ] 	= LoadFX( "fire/fire_smoke_trail_s" );//placed by fxman
	level._effect[ "ny_carhit" ] 	= LoadFX( "maps/ny_manhattan/ny_carhit" );//placed by fxman
	level._effect[ "light_hdr_fade" ] 	= LoadFX( "lights/light_hdr_fade" );//placed by fxman
	level._effect[ "light_hdr_looper" ] 	= LoadFX( "lights/light_hdr_looper" );//placed by fxman
	level._effect[ "fire_smoke_trail_M_ny" ] 	= LoadFX( "fire/fire_smoke_trail_M_ny" );//placed by fxman
	level._effect[ "powerline_runner_small" ] 	= LoadFX( "explosions/powerline_runner_small" );//placed by fxman
	level._effect[ "ny_hummerlightshaft" ] 	= LoadFX( "maps/ny_manhattan/ny_hummerlightshaft" );//placed by fxman
	level._effect[ "ny_hummerfallingdust" ] 	= LoadFX( "maps/ny_manhattan/ny_hummerfallingdust" );//placed by fxman
	level._effect[ "ceiling_dust_default" ] 	= LoadFX( "dust/ceiling_dust_default" );//placed by fxman
	level._effect[ "ceiling_falling_tile" ] 	= LoadFX( "dust/ceiling_falling_tile" );//placed by fxman
	level._effect[ "minigun_projectile" ] 	= LoadFX( "misc/minigun_projectile" );//placed by fxman
	level._effect[ "ny_shockwave" ] 	= LoadFX( "maps/ny_manhattan/ny_shockwave" );//placed by fxman
	level._effect[ "ny_buildingexplosion_trail" ] 	= LoadFX( "maps/ny_manhattan/ny_buildingexplosion_trail" );//placed by fxman
	level._effect[ "folding_table" ] 	= LoadFX( "props/folding_table" );//placed by fxman
	level._effect[ "ny_towerfirehit" ] 	= LoadFX( "maps/ny_manhattan/ny_towerfirehit" );//placed by fxman
	level._effect[ "ny_towerfall" ] 	= LoadFX( "maps/ny_manhattan/ny_towerfall" );//placed by fxman
	level._effect[ "fire_line_sm_cheap" ] 	= LoadFX( "fire/fire_line_sm_cheap" );//placed by fxman
	level._effect[ "ny_explosion_debris" ] 	= LoadFX( "maps/ny_manhattan/ny_explosion_debris" );//placed by fxman
	level._effect[ "generic_explosion_large" ] 	= LoadFX( "explosions/generic_explosion_large" );//placed by fxman
	level._effect[ "ny_explosion_large" ] 	= LoadFX( "maps/ny_manhattan/ny_explosion_large" );//placed by fxman

	level._effect["firelp_med_spreader_small"]													= loadfx ("fire/firelp_med_spreader_small");	
	level._effect[ "fire_line_sm" ]															= LoadFX( "fire/fire_line_sm" );
	level._effect[ "fire_ceiling_md_slow" ]													= LoadFX( "fire/fire_ceiling_md_slow" );
	level._effect[ "large_electric_exp" ]													= LoadFX( "props/large_electric_exp" );
	level._effect[ "single_tower_cable_end" ]													= LoadFX( "maps/ny_manhattan/single_tower_cable_end" );
	level._effect[ "lights_godray_beam" ]													= LoadFX( "lights/lights_godray_beam" );



	//sun flare fx
	level._effect["lights_lf_test"]													= loadfx ("lights/lights_lf_test");	
	level._effect["lights_lf_sewer"]													= loadfx ("lights/lights_lf_sewer");	

	//Procedural Bomb hits
	level._effect["falling_dirt_light"]													= loadfx ("dust/falling_dirt_light");	


	/*-----------------------
	SEWER FX / AMBIENT
	-------------------------*/	
	//level._effect[ "water_flow_sewage_catacomb" ]								= loadfx( "water/water_flow_sewage_catacomb2" );
	//level._effect[ "mist_drifting_catacomb" ]										= loadfx( "smoke/mist_drifting_catacomb" );
	level._effect[ "water_noise" ]															= loadfx( "weather/water_noise" );
	level._effect[ "waterfall_splash_falling_mist" ]						= loadfx( "water/waterfall_splash_falling_mist" );
	level._effect[ "water_pipe_spray" ]													= loadfx( "water/water_pipe_spray" );
	level._effect[ "water_faucet_spray" ]												= loadfx( "water/water_faucet_spray" );
	level._effect[ "fog_ground_200_heavy_lit" ]									= loadfx( "smoke/fog_ground_200_heavy_lit" );
	//level._effect[ "manhole_fallingdirt_ny" ]														= loadfx( "maps/ny_manhattan/manhole_fallingdirt_ny" );
	//level._effect[ "manhole_fallingdirt_ny2" ]														= loadfx( "maps/ny_manhattan/manhole_fallingdirt_ny2" );
	level._effect[ "pda_glow" ]														= loadfx( "props/pda_glow" );
	level._effect[ "smoke_red_lit_expensive" ]														= loadfx( "smoke/smoke_red_lit_expensive" );
	level._effect[ "light_red_pinlight" ]														= loadfx( "lights/light_red_pinlight" );



	/*-----------------------
	MANHATTAN BATTLE FX / AMBIENT
	-------------------------*/	
	level._effect["room_dust_nyharbor"]													= loadfx("dust/room_dust_100_blend_ny_harbor");
	level._effect["cloud_ash_nyHarborm"]												= loadfx ("weather/cloud_ash_nyHarbor");
	level._effect["cloud_ash_lite_nyHarbor"]										= loadfx ("weather/cloud_ash_lite_nyHarbor");
	level._effect["electrical_transformer_spark_runner"]				= loadfx ("explosions/electrical_transformer_spark_runner");	
 	level._effect[ "steam_manhole" ]														= loadfx( "smoke/steam_manhole" );
 	level._effect[ "bigcity_streetsmoke_obscure" ]							= loadfx( "smoke/bigcity_streetsmoke_obscure" );
 	level._effect[ "bigcity_streetsmoke_obscure_low" ]					= loadfx( "smoke/bigcity_streetsmoke_obscure_low" );
 	level._effect[ "bigcity_streetsmoke_obscure_onfire" ]				= loadfx( "smoke/bigcity_streetsmoke_obscure_onfire" );
	level._effect[ "firelp_med_pm_nolight" ]										= LoadFX( "fire/firelp_med_pm_nolight" );
	level._effect[ "firelp_med_pm_far" ] 												= LoadFX( "fire/firelp_med_pm_far" );//placed by fxman
	//level._effect[ "fire_med_pm_nolight_far_atlas" ] 								= LoadFX( "fire/fire_med_pm_nolight_far_atlas" );
	//level._effect[ "fire_med_pm_nolight_atlas" ] 								= LoadFX( "fire/fire_med_pm_nolight_atlas" );
	level._effect[ "building_collapse_nyharbor" ]								= loadfx( "dust/building_collapse_nyharbor" );
	level._effect[ "thick_dark_smoke_giant2" ]									= loadfx( "smoke/thick_dark_smoke_giant_nydowntown" );
	level._effect["antiair_runner_flak"]												= loadfx ("misc/antiair_runner_flak");	
	level._effect["fireball_lp_smk_l_swirl"]										= loadfx ("fire/fireball_lp_smk_l_swirl");	
	level._effect["fireball_lp_smk_l"]													= loadfx ("fire/fireball_lp_smk_l");	
	level._effect["fireball_lp_smkonly_l"]											= loadfx ("fire/fireball_lp_smkonly_l");	
	level._effect["fire_falling_runner_longlife"]								= loadfx ("fire/fire_falling_runner_longlife");	
	level._effect["fire_embers_directional"]										= loadfx ("fire/fire_embers_directional");	
	level._effect["fire_embers_directional_slow"]								= loadfx ("fire/fire_embers_directional_slow");	
	level._effect["fire_embers_directional_lowvel"]							= loadfx ("fire/fire_embers_directional_lowvel");	
	level._effect["generic_explosion"]													= loadfx ("explosions/generic_explosion");	
	level._effect["ambient_explosion"]													= loadfx ("maps/ny_manhattan/ambient_explosion");	
	level._effect["generic_explosion_distortion"]								= loadfx ("maps/ny_manhattan/ny_explosion_distortion");	
	level._effect["generic_explosion_debris"]										= loadfx ("explosions/generic_explosion_debris");	
	level._effect["window_explosion_glass_only"]								= loadfx ("explosions/window_explosion_glass_only");	
	level._effect["highrise_glass_mullions_74x44"]							= loadfx ("props/highrise_glass_mullions_74x44");	
	level._effect["abrams_muzzle_dust"]													= loadfx ("dust/abrams_muzzle_dust");	
	level._effect["smoke_geotrail_genericexplosion"]						= loadfx("smoke/smoke_geotrail_genericexplosion_b" );
	level._effect["smoke_geotrail_genericexplosion_c"]					= loadfx("smoke/smoke_geotrail_genericexplosion_c" );
	level._effect["chunk_contrail_ny"]													= loadfx ("maps/ny_manhattan/chunk_contrail_ny");	
	level._effect["car_glass_large"]														= loadfx ("props/car_glass_large");	
	level._effect["glass_falling_ny"]														= loadfx ("maps/ny_manhattan/building_debris_falling_ny");	
	level._effect["water_hydrant"]															= loadfx ("water/water_hydrant");	
	level._effect["aa_explosion_super"]													= loadfx ("explosions/aa_explosion_super_cloudOnly");
	level._effect["generic_incoming_aa_shell"]									= loadfx ("explosions/generic_incoming_aa_shell");	
	level._effect["ground_dust"]																= loadfx ("dust/ground_dust");
	level._effect["smoke_wall_l_warm_ny"]												= loadfx ("smoke/smoke_wall_l_warm_ny");
	level._effect["smk_shadow_l_ny"]														= loadfx ("smoke/smk_shadow_l_ny");
	level._effect["smoke_wall_m_warm_ny"]												= loadfx ("smoke/smoke_wall_m_warm_ny");
	level._effect["smk_shadow_m_ny"]														= loadfx ("smoke/smk_shadow_m_ny");
	level._effect["smoke_wall_s_warm_ny"]												= loadfx ("smoke/smoke_wall_s_warm_ny");
	level._effect["smk_shadow_s_ny"]														= loadfx ("smoke/smk_shadow_s_ny");
	level._effect["powerline_runner"]														= loadfx ("explosions/powerline_runner");	
	level._effect[ "firelp_small_pm" ]													= LoadFX( "fire/firelp_small_pm" );
	level._effect["dust_spiral_slow_runner"]										= loadfx ("dust/dust_spiral_slow_runner_optim");	
	level._effect[ "battlefield_smk_directional_yel_xs" ]				= loadfx( "smoke/battlefield_smk_directional_yel_xs" );
	level._effect[ "battlefield_smk_directional_White_S" ]			= loadfx( "smoke/battlefield_smk_directional_White_S" );
	level._effect[ "battlefield_smk_directional_White_M" ]			= loadfx( "smoke/battlefield_smk_directional_White_M" );
	level._effect[ "ash_spiral_runner" ]												= loadfx( "dust/ash_spiral_runner" );
	level._effect[ "dust_wind_slow_paper_narrow" ]							= loadfx( "dust/dust_wind_slow_paper_narrow" );
	level._effect["battlefield_smk_linger_l"]										= loadfx ("smoke/battlefield_smk_linger_l");	
	level._effect[ "pipe_steam" ]																= loadFX( "impacts/pipe_steam" );
	level._effect[ "pipe_steam_looping" ]												= loadFX( "impacts/pipe_steam_looping" );
	level._effect[ "car_steam_looping_sm" ]												= loadFX( "impacts/car_steam_looping_sm" );
	level._effect[ "trash_spiral_runner" ]											= loadfx( "misc/trash_spiral_runner" );
	level._effect[ "paper_falling_narrow" ]											= loadfx( "misc/paper_falling_narrow" );
	level._effect[ "smoke_white_room_linger_l" ]								= loadfx( "smoke/smoke_white_room_linger_l" );
	level._effect[ "gasoline_spray" ]														= loadfx( "distortion/gasoline_spray" );
	level._effect[ "car_damaged_heat" ]													= loadfx( "distortion/car_damaged_heat" );
	level._effect[ "car_damaged_heat_lite" ]										= loadfx( "distortion/car_damaged_heat_lite" );
	level._effect[ "water_drips_fat_fast_singlestream" ]				= loadfx( "water/water_drips_fat_fast_singlestream" );
	level._effect[ "drips_faucet_slow" ]												= loadfx( "water/drips_faucet_slow" );
	level._effect[ "oil_drip_small" ]														= loadfx( "misc/oil_drip_small" );
	level._effect[ "tread_smk_road_gaz_front" ]									= loadfx( "treadfx/tread_smk_road_gaz_front" );
	level._effect[ "tread_smk_road_gaz_back" ]									= loadfx( "treadfx/tread_smk_road_gaz_back" );
	level._effect[ "car_glass_xl" ]															= loadfx( "props/car_glass_xl" );
	level._effect[ "fireball_lp_smk_L_quickfalloff" ]						= loadfx( "fire/fireball_lp_smk_L_quickfalloff" );
	level._effect[ "building_smoke_simple" ]										= loadfx( "smoke/building_smoke_simple" );
	level._effect[ "light_red_steady_dim" ]											= loadfx( "misc/tower_light_red_steady_dim" );
			
	/*alleyway*/	
	level._effect[ "steam_large_vent_rooftop" ]									= loadfx( "smoke/steam_large_vent_rooftop" );
	level._effect[ "cloud_ash_nopaper_nyHarbor" ]								= loadfx( "weather/cloud_ash_nopaper_nyHarbor");
	level._effect[ "cloud_ash_nopaperdark_nyHarbor" ]						= loadfx( "weather/cloud_ash_nopaperdark_nyHarbor");
	level._effect[ "cloud_ash_nopaperdark_localized_nyHarbor" ]	= loadfx( "weather/cloud_ash_nopaperdark_localized_nyHarbor");
	level._effect[ "embers_burst_runner_longlife" ]							= loadfx( "fire/embers_burst_runner_longlife");
 	level._effect[ "steam_vent_small" ]													= loadfx( "smoke/steam_vent_small" );
 	level._effect[ "steam_jet_med_loop" ]												= loadfx( "smoke/steam_jet_med_loop" );
 	level._effect[ "steam_room_100" ]														= loadfx( "smoke/steam_room_100" );
 	level._effect[ "steam_hall_200" ]														= loadfx( "smoke/steam_hall_200" );
 	level._effect[ "insects_carcass_flies" ]										= loadfx( "misc/insects_carcass_flies" );
 	level._effect[ "insects_carcass_flies_dark" ]								= loadfx( "misc/insects_carcass_flies_dark" );
	

	//Apartments
	level._effect["falling_dirt_light_runner"]											= loadfx ("dust/falling_dirt_light_runner");	
//level._effect[ "stove_burner" ]			 											= loadfx( "misc/stove_burner" );
	level._effect["lights_conelight_smokey"]											= loadfx("lights/lights_conelight_smokey");
	level._effect["lights_godray_default"]												= loadfx("lights/lights_conelight_default");
	level._effect["lights_tvlight_smokey"]												= loadfx("lights/lights_tvlight_smokey");
	level._effect["tvlight_smokey_nolight"]												= loadfx("misc/tvlight_smokey_nolight");
	level._effect[ "waterfall_drainage_short_dcemp" ]									= loadfx( "water/waterfall_drainage_short_dcemp" );
	level._effect[ "waterfall_drainage_splash_dcemp" ]									= loadfx( "water/waterfall_drainage_splash_dcemp" );
	level._effect[ "drips_slow" ]														= loadfx( "misc/drips_slow" );
	level._effect[ "drips_fast" ]														= loadfx( "misc/drips_fast" );
	level._effect[ "falling_water_trickle" ]											= loadfx( "water/falling_water_trickle" );
	level._effect[ "ny_manhattan_generic_spotlight_lit" ]								= loadfx( "misc/ny_manhattan_generic_spotlight_lit" );
	level._effect[ "room_smoke_warm_flicker" ]									= loadfx( "smoke/room_smoke_warm_flicker" );
	level._effect[ "embers_spurt" ]															= loadfx( "fire/embers_spurt" );
	level._effect[ "lights_uplight_haze" ]										= loadfx( "lights/lights_uplight_haze" );
	level._effect[ "lights_uplight_haze_large" ]										= loadfx( "lights/lights_uplight_haze_large" );

	level._effect[ "door_kick_small" ]			 											= loadfx( "dust/door_kick_small" );

	//Tiffanys
	level._effect["tiffanys_ceiling_smoke"]												= loadfx ("smoke/tiffanys_ceiling_smoke");	
	level._effect["lights_headlight"]													= loadfx ("lights/lights_headlight");
	level._effect["lights_strobe_red"]													= loadfx ("lights/lights_strobe_red");
	level._effect["lights_strobe_blue"]													= loadfx ("lights/lights_strobe_blue");
	level._effect["lights_alarm_strobe"]												= loadfx ("lights/lights_alarm_strobe");
	level._effect["lights_uplight_haze"]												= loadfx ("lights/lights_uplight_haze");
	level._effect[ "firelp_med_pm_cheap" ]												= loadfx( "fire/firelp_med_pm_cheap" );
	level._effect[ "firelp_med_pm_cheap_tiffanies" ]									= loadfx( "fire/firelp_med_pm_cheap_tiffanies" );
	level._effect[ "firelp_med_pm_cheap_smoke_pair" ]									= loadfx( "fire/firelp_med_pm_cheap_smoke_pair" );
	level._effect[ "firelp_small_streak_pm1_h_nolight" ]												= loadfx( "fire/firelp_small_streak_pm1_h_nolight" );
	level._effect[ "heli_crashed_tail_smoke" ]												= loadfx( "smoke/heli_crashed_tail_smoke" );
	level._effect[ "lighthaze_skylight" ]												= loadfx( "misc/lighthaze_skylight" );
	level._effect[ "ground_smoke_breach_hole" ]											= loadfx( "smoke/ground_smoke_breach_hole" );
	level._effect[ "smoke_gush_breach" ]												= loadfx( "smoke/smoke_gush_breach" );
	level._effect[ "breach_fire_smoke" ]												= loadfx( "smoke/breach_fire_smoke" );
	level._effect["falling_dirt_light_runner_tiffanies"]								= loadfx ("dust/falling_dirt_light_runner_tiffanies");	
	level._effect["fire_falling_runner_point"]											= loadfx ("fire/fire_falling_runner_point");	
	level._effect["cloud_ash_tiffanies"]												= loadfx ("weather/cloud_ash_tiffanies");	

	//hind ride
	level._effect["smk_column_thin_shaded_ny"]									= loadfx ("maps/ny_manhattan/smk_column_thin_shaded_ny");	
	level._effect["smk_column_thin_sunned_ny"]									= loadfx ("maps/ny_manhattan/smk_column_thin_sunned_ny");	
	level._effect["smk_column_thick_sunned_ny"]									= loadfx ("maps/ny_manhattan/smk_column_thick_sunned_ny");	

	level._effect["fire_smoke_trail_l_emitter"]													= loadfx ("fire/fire_smoke_trail_l_emitter");	
	level._effect["smoke_trail_black_heli_emitter"]													= loadfx ("smoke/smoke_trail_black_heli_emitter");	
	level._effect["heli_engine_fire"]													= loadfx ("fire/heli_engine_fire");	
	
	//hind finale
	level._effect["hind_finale_enemy_tail_hit_ny"]							= loadfx ("maps/ny_manhattan/hind_finale_enemy_tail_hit_ny");	
	level._effect["hind_finale_enemy_building_hit_ny"]					= loadfx ("maps/ny_manhattan/hind_finale_enemy_building_hit_ny");	
	level._effect["hind_finale_enemy_tail_smk_trail_ny"]				= loadfx ("maps/ny_manhattan/hind_finale_enemy_tail_smk_trail_ny");	
	level._effect["hind_finale_building_hit_shkwv_ny"]					= loadfx ("maps/ny_manhattan/hind_finale_building_hit_shkwv_ny");	
	level._effect["hind_finale_building_fireball_out_ny"]				= loadfx ("maps/ny_manhattan/hind_finale_building_fireball_out_ny");	
	level._effect["hind_finale_building_fire_linger_ny"]				= loadfx ("maps/ny_manhattan/hind_finale_building_fire_linger_ny");	
	level._effect["hind_finale_player_smk_rotor_ny"]						= loadfx ("maps/ny_manhattan/hind_finale_player_smk_rotor_ny");			
	level._effect["hind_finale_player_beeper"]									= loadfx ("maps/ny_manhattan/hind_finale_player_beeper");
	level._effect[ "firelp_large_streak_v_nolight" ]						= loadfx( "fire/firelp_large_streak_v_nolight" );			
	level._effect[ "fuel_med_explosion" ]												= loadfx( "explosions/fuel_med_explosion" );	
	level._effect["hind_finale_player_damage_spark"]						= loadfx ("maps/ny_manhattan/hind_finale_player_damage_spark");
	level._effect["hind_finale_chunk_smk_trail_ny"]							= loadfx ("maps/ny_manhattan/hind_finale_chunk_smk_trail_ny");
	
	level._effect["rotor_impact_concrete"]											= loadfx ("impacts/rotor_impact_concrete");	
	level._effect["rotor_impact_concrete_sparks"]								= loadfx ("impacts/rotor_impact_concrete_sparks");	
	level._effect[ "minigun_shell_eject" ] 											= loadfx( "shellejects/20mm_mp" );
	level._effect[ "hind_spot" ] 																= loadfx( "misc/aircraft_light_hindspot");
	
	//end war fx
	level._effect[ "skybox_hind_flyby" ] 																= loadfx( "misc/skybox_hind_flyby");
	
	// for bloody_death
	level._effect[ "flesh_hit" ] = LoadFX( "impacts/flesh_hit_body_fatal_exit" );
	

	/*-----------------------
	old FX
	-------------------------*/	
 	//
	//level._effect["heli_takeoff_swirl"]												= loadfx ("dust/heli_takeoff_swirl");	http://twitter.com
	//level._effect[ "hallway_smoke_dark" ]						= loadfx( "smoke/hallway_smoke_dark" );
	//level._effect[ "ground_smoke_dcburning1200x1200" ]			= loadfx( "smoke/ground_smoke1200x1200_dcburning" );
	//level._effect[ "thin_black_smoke_L" ]						= loadfx( "smoke/thin_black_smoke_L" );
	//level._effect[ "firelp_med_pm" ]							= LoadFX( "fire/firelp_med_pm" );
	//level._effect[ "firelp_small_pm_a" ]						= LoadFX( "fire/firelp_small_pm_a" );
	//level._effect[ "firelp_large_pm" ]							= LoadFX( "fire/firelp_large_pm" );
	//level._effect[ "firelp_vhc_lrg_pm_farview" ]				= loadfx( "fire/firelp_vhc_lrg_pm_farview" );
	//level._effect[ "powerline_runner_cheap" ] 					= loadfx( "explosions/powerline_runner_cheap" );
	//level._effect[ "cgo_ship_puddle_small" ]	 				= loadfx( "distortion/cgo_ship_puddle_small" );
	//level._effect[ "rock_falling_small_runner" ]	 			= loadfx( "misc/rock_falling_small_runner" );
	//level._effect[ "firelp_small_pm_nolight" ]					= loadfx( "fire/firelp_small_pm_nolight" );
	//level._effect["fire_sprinkler"]														= loadfx ("water/fire_sprinkler");
	//level._effect[ "player_death_explosion" ]				 = loadfx( "explosions/player_death_explosion" );
	//level._effect[ "bird_seagull_flock_large" ]								= loadfx( "misc/bird_seagull_flock_large" );



	// "hunted light" required zfeather == 1 and r_zfeather is undefined on console.  So, test for != "0".
	if ( getdvarint( "sm_enable" ) && getdvar( "r_zfeather" ) != "0" )
		level._effect[ "spotlight" ]						 = loadfx( "misc/hunted_spotlight_model" );
	else
		level._effect[ "spotlight" ]						 = loadfx( "misc/spotlight_large" );

	level._effect[ "heli_dlight_blue" ]					 = loadfx( "misc/aircraft_light_cockpit_blue" );

	//level._effect[ "ship_explosion" ]						= loadfx( "explosions/tanker_explosion" );


	/*-----------------------
	LIGHT FX
	-------------------------*/	
	level._effect[ "light_glow_white_bulb" ]				= LoadFX( "misc/light_glow_white_bulb" );
	level._effect[ "fluorescent_glow" ]							= LoadFX( "misc/fluorescent_glow" );
	level._effect[ "whiteout" ]											= LoadFX( "maps/ny_manhattan/whiteout" );
	level._effect[ "spotlight_btr80_daytime" ]			= LoadFX( "misc/spotlight_btr80_daytime" );
	level._effect[ "car_taillight_btr80_eye" ]			= LoadFX( "misc/car_taillight_btr80_eye" );
	level._effect[ "traffic_light_red_blinking" ]		= LoadFX( "misc/traffic_light_red_blinking" );
	level._effect[ "traffic_light_green_blinking" ]	= LoadFX( "misc/traffic_light_green_blinking" );
	level._effect[ "aircraft_light_red_blink" ]			= LoadFX( "misc/aircraft_light_red_blink" );
	level._effect["lights_spotlight"]								= loadfx ("lights/lights_spotlight");
	
	
	// This is the temp effect used for the depth charges

	// Used for the ss_n_12
	level._effect[ "ship_explosion" ]						= loadfx( "impacts/ssn12_concrete_impact" );
	
	//Thermite reaction
	level._effect[ "thermite_reaction" ]					= loadfx( "smoke/thermite_reaction" );

}

starthindDust()
{
	self waittill("msg_fx_start_hindDust");
	//playfx(getfx("heli_takeoff_swirl"),(-671,598,16),anglestoforward((0,318,0)),(1,0,0));
}

entering_hind_dof()
{
	flag_wait( "entering_hind" );
	wait(1); //wait after jumping
	
	start = level.dofDefault;	

	ny_manhattan_dof_entering_hind = [];
	ny_manhattan_dof_entering_hind[ "nearStart" ] = 5;
	ny_manhattan_dof_entering_hind[ "nearEnd" ] = 10;
	ny_manhattan_dof_entering_hind[ "nearBlur" ] = 4;
	ny_manhattan_dof_entering_hind[ "farStart" ] = 300;
	ny_manhattan_dof_entering_hind[ "farEnd" ] = 3500;
	ny_manhattan_dof_entering_hind[ "farBlur" ] = 4;	
	
	blend_dof( start, ny_manhattan_dof_entering_hind, .3 );
	
	//wait(3.3);
	wait(4.3); //time with camera snap
	blend_dof ( ny_manhattan_dof_entering_hind, start, 1 );
}


treadfx_override()
{
	level.treadfx_maxheight = 3000;//
	tread_effects = "treadfx/tread_snow_slush";
	flying_tread_fx = "treadfx/heli_dust_large";
	flying_tread_fx_water = "treadfx/heli_water_big";


	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "brick", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "bark", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "carpet", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "cloth", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "concrete", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "dirt", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "flesh", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "foliage", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "glass", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "grass", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "gravel", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "ice", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "metal", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "mud", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "paper", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "plaster", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "rock", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "sand", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "snow", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "water", flying_tread_fx_water );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "wood", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "asphalt", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "ceramic", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "plastic", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "rubber", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "cushion", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "fruit", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "painted metal", flying_tread_fx );
 	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "default", flying_tread_fx );
	maps\_treadfx::setvehiclefx( "script_vehicle_ny_harbor_hind", "none", flying_tread_fx );
	
}


start_more_obscure_smoke()
{
	//foo
	wait(1.0);
	flag_wait("thermite_detonated");
	wait(15.0);	
	exploder(1512);
	flag_wait("entering_hind");
	wait(15);
	kill_exploder(1512);
	exploder(1513);
	wait(5);
	kill_exploder(1513);
	
	
}




fireCollapseFX()
{
	//start collapsing building fx

		/*-----------------------
		WAIT FOR HIND RIDE VFX MSG
		-------------------------*/	
		self waittill("entering_hind");
		
		level waittill("msg_fx_spawn_hindride_fx" );
		//wait(.5);
		
		/*-----------------------
		KILL ALL THE EXISTING VFX
		-------------------------*/	
		//Killing all the ambient downtown fx and spawning the hind ride fx
		foreach ( fx in level.createFXent )
		{
			if ( fx.v[ "type" ] == "exploder" )
			{
				if ( isdefined(fx.v[ "exploder" ]) && ( fx.v[ "exploder" ]!="560" ))		fx pauseEffect();
			
			}
			else fx pauseEffect();
			
		}
		

		exploder(560);
		
		//playfx( getfx( "building_collapse_nyharbor" ),(-9970.91, -12762.6, 130.12 ),AnglesToForward((270, 0, 45)),AnglesToUp((270, 0, 45)) );
		
	
}

nyse_fx_rooms()
{
	//nyse
	nysetrig = getent("nyse_fx_damage_trigger","targetname");
	nyseroom = nysetrig nyse_fx_room_damage();
	nyseroom.v["fxid"]=getfx( "smoke_white_room_linger_l" );
	nyseroom.v["vfxoffset"]=(0,0,-150);
	nyseroom.v["healrate"] = 10;
	thread start_fx_nyse_room_damage(nyseroom);
}

nyse_fx_room_damage()
{
	roomInfo = spawnStruct();
	if ( !isdefined( level.fx_room ) )
		level.fx_room = [];
	level.fx_room[ level.fx_room.size ] = roomInfo;
	roomInfo.v["health"] = 0;
	roomInfo.v["healrate"] = 15;
	roomInfo.v["numVFX"] = 0;
	roomInfo.v["vfxLife"] = 10;
	roomInfo.v["vfxOffset"]=(0,0,0);
	roomInfo.v["fxid"] = getfx( "smoke_white_room_linger_l" );
	roomInfo.v["roomTrigger"] = self;
	return roomInfo;
}

update_nyse_fog(currRoom)
{
	wait(.25);
	flag_wait("fx_zone_16000_active");
	currRoom.v["roomTrigger"] waittill("damage");
	curr_half = getdvarfloat("scr_fog_exp_halfplane");
	curr_op = getdvarfloat("scr_fog_max_opacity");
	curr_start = getdvarfloat("scr_fog_nearplane");
	t_half = curr_half;
	t_op = curr_op;
	t_color = (.4,.35,.3);
	t_start = curr_start;
	half_target = 16000;
	start_target = 300;
	for(;;)
	{
		flag_wait("fx_zone_16000_active");
		while(flag("fx_zone_16000_active"))
		{
			lerpVal = min(1.0,max(0.0,float(currRoom.v["health"])/300.00));
			
			if(currRoom.v["health"]<50) lerpVal=0;
			t_half = curr_half * (1-lerpVal) + half_target * lerpVal;
			t_op = curr_op * (1-lerpVal) + .1 * lerpVal;
			t_start = 3000 * (1-lerpVal) + start_target * lerpVal;
			setexpfog(t_start,t_half,t_color[0],t_color[0],t_color[0],t_op,2.0);
			wait(2.1);
			half_target = max(1500,half_target-1100);
			start_target = max(300,start_target-100);
		}
		curr_half = getdvarfloat("scr_fog_exp_halfplane");
		curr_op = getdvarfloat("scr_fog_max_opacity");
		wait(.5);
	}
	
	
	
}

start_fx_nyse_room_damage(currRoom)
{
	trigObj = currRoom.v["roomTrigger"];
	thread heal_fx_room(currRoom);
	thread playdust_fx_room(currRoom);
	thread update_nyse_fog(currRoom);
	for(;;)
	{
		trigObj waittill("damage");
		currRoom.v["health"]++;
	}
}

//kill all env vfx using oneshot on hind ride
kill_all_env_fx ()
{	
	flag_wait("entering_hind" ); 
	foreach ( fx in level.createFXent )
	{
		if ( fx.v[ "type" ] == "oneshotfx" )  
		fx pauseEffect();
	}

}

fx_fire_oxygen_tanks()
{
	flag_wait("hind_finale_start");
	flag_wait("msg_fx_hindfinale_oxytanks");
	exploder(1507);
	//secondary war fx
	exploder(1547);
	wait 2.25;
	Earthquake( 0.2, 2.0, level.player.origin, 1600 );
}

fx_stockexchange_roofdust()
{
	wait 1;
	flag_wait("msg_fx_zone16");
	expPos = [(-1911, 2197, 1086)
        ,(-1623, 2462, 1047)
        ,(-2248, 2603, 1056)
        ,(-2442, 2072, 1059)
        ,(-1923, 1637, 1065)
        ,(-1349, 1347, 1054)
        ,(-1166, 1750, 1066)
        ,(-1446, 2470, 1046)
        ,(-1586, 2926, 1048)
        ,(-2256, 2728, 1061)
        ,(-1235, 1752, 1057)
        ,(-1802, 1649, 1053)
        ,(-1335, 2061, 1062)
        ,(-1879, 1752, 1060)
        ,(-1158, 2282, 1070)
        ,(-1836, 1909, 1084)
        ,(-1148, 1474, 1071)
        ,(-1024, 1747, 1067)
        ,(-1704, 2227, 1107)
        ,(-1346, 2698, 1067)
        ,(-1289, 1910, 1068)
        ,(-1867, 2233, 1095)
        ,(-2245, 2092, 1062)
        ,(-1442, 1848, 1069)];
	wait 3;
	for(;;)
	{
		flag_wait("msg_fx_zone16");
		//Wait a # of seconds
		randomInc = randomfloatrange(2,4.5);
		wait(randomInc);
		ent = get_exploder_ent(16001);
		randomPos = randomInt (expPos.size);
		ent.v["origin"] = expPos[randomPos];
		exploder(16001);	
	}
}

ladder_climb_moment()
{
	if ( !is_specialop() )
	{
		level waittill("fx_zone_16000_activating");
		level waittill("fx_zone_17000_activating");
		exploder(1509);
		level.rumble thread rumble_ramp_to ( 1, 0.1 );
		level.rumble delaythread ( 0.5, ::rumble_ramp_to, 0, 0.2 );
		aud_send_msg("ladder_climb_moment_explosion");
		screenshake(.65,.75,.21,.21);
		setblur(.5,0);
		wait(.25);
		setblur(0,.25);
		wait(.35);
		overlay = NewClientHudElem( level.player );
		overlay.x = 0;
		overlay.y = 0;
		overlay SetShader( "fullscreen_dirt_bottom", 640, 480 );	
		overlay.splatter = true;
		overlay.alignX = "left";
		overlay.alignY = "top";
		overlay.sort = 1;
		overlay.foreground = 0;
		overlay.horzAlign = "fullscreen";
		overlay.vertAlign = "fullscreen";
		overlay.alpha = .15;
		for(i=0;i<15;i++)
		{
			overlay.alpha = (1-(i/14.0))*.15;
			level waitframe();
		}	
		overlay destroy();
	}
}

broad_hallway_exp_moment()
{
	if (!flag_exist("fx_trigger_broad_hallexp")) flag_init("fx_trigger_broad_hallexp");
	level waitframe();
	flag_wait("fx_trigger_broad_hallexp");
	exploder(1515);
	level.rumble thread rumble_ramp_to ( 0.7, 0.1 );
	level.rumble delaythread ( 0.2, ::rumble_ramp_to, 0, 0.2 );
	aud_send_msg("broad_hallway_explosion");
	screenshake(.35,.75,.21,.1);
	//flag_exist
	
}


stairwell_bombshake_moment()
{
	if(!flag_exist("fx_trigger_stairway_bombshake")) flag_init("fx_trigger_stairway_bombshake");
	level waitframe();
	flag_wait("fx_trigger_stairway_bombshake");
	exploder(1514);
	level.rumble thread rumble_ramp_to ( 0.7, 0.1 );
	level.rumble delaythread ( 0.4, ::rumble_ramp_to, 0, 0.2 );
	aud_send_msg("stairwell_bombshake_explosion");
	screenshake(.55,.75,.21,.21);
	
}

heli_quake()
{
	exp = get_exploder_ent(1510);
	pos = exp.v["origin"];
	rampup = 0.01;
	i = 0;
	while(!flag("entering_hind"))
	{
	mag = distance2d(pos,level.player.origin);
	scale = .125 * clamp(1.0-(mag/3000.00),0.01,1.0) * (rampup/2.0);
	waittime = randomfloat(1.0) * 8.0+ 1.0;
	earthquake( scale, waittime * .5, pos, 3000 );
	rampup = clamp(rampup + (waittime /  20.0),0.01,2.0);
	wait(waittime / 20.00);
	}
}

heli_dust_moment()
{
	flag_wait("obj_capturehind_given");
	wait(5.0);//start smoke disturb fx
	exploder(1511);
	wait(3.3);//start fx at frame 100 - anim starts at frame -181
	exploder(1510);
	thread heli_quake();
	flag_wait("entering_hind");
	pauseexploder(1510);
	
}


nyse_hinddeath_swap()
{
		level endon("msg_fx_end_heliswap");
		while(maps\ny_manhattan_code_hind::isVehicleAlive(self))
		{
			level waitframe();
		}	
		if(!maps\ny_manhattan_code_hind::isVehicleAlive(self)) 
		{
			offset = vectornormalize(anglestoforward(self.angles))*-150;
			newhind = spawn( "script_model", self.origin  );
			newhind.angles = self.angles;
			newhind linkto(self,"tag_body",(-150,0,-25),(0,-90,0));
			newhind setmodel("vehicle_mi24p_hind_ny_destroy");
			level waitframe();
			newhind hidepart("rotor","vehicle_mi24p_hind_ny_destroy");
			wait(.7);
			self hide();
			wait(9);
			newhind delete();
		}
			
}

nyse_hinddeath_override()
{
	//replace the final crash effects
	original_deathfx1 = level.vehicle_death_fx["script_vehicle_hind_woodland"][5].effect;
	original_deathfx2 = level.vehicle_death_fx["script_vehicle_hind_woodland"][2].effect;
	original_tag2 = level.vehicle_death_fx["script_vehicle_hind_woodland"][2].tag;
	original_looping2 = level.vehicle_death_fx["script_vehicle_hind_woodland"][2].beffectlooping;

	level.vehicle_death_fx["script_vehicle_hind_woodland"][5].effect = getfx("ny_heli_hinddeath");

	weaponname = "";
	while(!flag("entering_hind"))
	{
		//self waittill("damage", damage, attacker, direction, point, method, modelName, tagName, partName, dFlags, weaponname );

		if ( !isdefined( level.player.is_controlling_UAV ) )
		{
			wait(2.0);
			
			//level waitframe();
			level.vehicle_death_fx["script_vehicle_hind_woodland"][2].effect = original_deathfx2;
			level.vehicle_death_fx["script_vehicle_hind_woodland"][2].tag = original_tag2;
			level.vehicle_death_fx["script_vehicle_hind_woodland"][2].beffectlooping = original_looping2;
			level notify("msg_fx_end_heliswap");
			level waitframe();
			
		}
		else
		{
			//replace the rotor on fire effects
			level.vehicle_death_fx["script_vehicle_hind_woodland"][2].effect = getfx("ny_heli_predatorexp");
			level.vehicle_death_fx["script_vehicle_hind_woodland"][2].tag = "tag_deathfx";
			level.vehicle_death_fx["script_vehicle_hind_woodland"][2].beffectlooping = 0;
			
			atk = undefined;
			level waitframe();
			self thread nyse_hinddeath_swap();
			while(isdefined(level.player.is_controlling_UAV))
			{
				level waitframe();
			}
			
		}

	}
	
	
	flag_wait("entering_hind");
	//reset everything back to normal
	level notify("msg_fx_end_heliswap");
	level.vehicle_death_fx["script_vehicle_hind_woodland"][5].effect = original_deathfx1;
	level.vehicle_death_fx["script_vehicle_hind_woodland"][2].effect = original_deathfx2;
	level.vehicle_death_fx["script_vehicle_hind_woodland"][2].tag = original_tag2;
	level.vehicle_death_fx["script_vehicle_hind_woodland"][2].beffectlooping = original_looping2;
	
}


alt_toggle_giant_smoke_column()
{
	flag_wait_either("obj_capturehind_given","entering_hind");
	kill_oneshot("thick_dark_smoke_giant2");
}

toggle_giant_smoke_column()
{
	thread alt_toggle_giant_smoke_column();
	level waittill("fx_zone_17000_activating");
	//kill the initial oneshot
	kill_oneshot("thick_dark_smoke_giant2");
	for(;;)
	{
	level waittill("fx_zone_16000_activating");
	exploder(972);
	level waittill("fx_zone_17000_activating");
	kill_exploder(972);
	}
	
}


vfx_door_kick()
{
	wait(.9);
	//iprintlnbold( "door_kick" );
	exploder(777);
}

setup_water_sheeting_volumes()
{
		water_sheeting_triggers = getentarray( "water_sheeting_vol", "targetname" );
		array_thread( water_sheeting_triggers, ::water_sheeting_trigger_think);
}

water_sheeting_trigger_think()
{
	self waittill( "trigger", other );
	level.player setwatersheeting( 1 );
	other water_sheeting_wait(self);
}

water_sheeting_wait( parentTrigger )
{
	self endon( "death" );

	for ( ;; )
	{
		if (self IsTouching(parentTrigger))
		{
			wait (0.15);
		}
		else
		{	
			level.player setwatersheeting( 1, 0.5 );
			parentTrigger thread water_sheeting_trigger_think();
			return;
		}
	}
}