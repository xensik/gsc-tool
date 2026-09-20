#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;

#include maps\_audio;
#include maps\paris_shared;

#include maps\_hud_util;

#include maps\_shg_common;

paris_intro_screen()
{
	duration = 11;
	thread intro_rumble();
	
	flag_set("flag_dialogue_opening");
	
	level.player FreezeControls( true );
	level.player player_control_off();
		
	thread maps\_introscreen::introscreen_generic_black_fade_in( duration, 4 );

	lines = [];
	
	// todo: add comments here once we're sure what strings we'll use
	lines[ lines.size ] = &"PARIS_INTROSCREEN_LINE1";
	lines[ lines.size ] = &"PARIS_INTROSCREEN_LINE2";
	lines[ lines.size ] = &"PARIS_INTROSCREEN_LINE3";
	lines[ lines.size ] = &"PARIS_INTROSCREEN_LINE4";
	lines[ lines.size ] = &"PARIS_INTROSCREEN_LINE5";

	maps\_introscreen::introscreen_feed_lines( lines );
	
	wait duration;
	
	level.player gasmask_on_player(false);
	
	flag_set( "intro_screen_complete" );
}

intro_rumble()
{
	level.rumble thread rumble_ramp_to ( .1, 11 );
	flag_wait( "flag_little_bird_landed" );
	level.player playrumbleonentity( "viewmodel_large" );
	level.rumble rumble_ramp_off ( 16 );
}	

little_bird_fly_away()
{
	guys = [level.hero_lone_star, level.hero_reno];
	
	bird = spawn_vehicle_from_targetname( "little_bird" );

	thread maps\_friendlyfire::friendly_fire_think(bird);
	bird MakeUnusable();
	pilot = getent_safe("pilot_little_bird", "targetname") spawn_ai(true);
	pilot gun_remove();
	pilot.animname = "pilot";
	bird SetHoverParams(0, 0, 0);

	//bird thread helicopter_wind();
	thread little_bird_camera_shake();
	
	//set half res particles for ps3
	if ( ( level.Console && level.ps3 ) || !level.Console )
	{
		SetHalfResParticles( true );
	}
	

	foreach(guy in guys)
	{
		guy disable_ai_color();
	}

	level.hero_lone_star LinkTo(bird, "tag_detach_left",  (0, 0, 0), (0, 0, 0));
	level.hero_reno      LinkTo(bird, "tag_detach_right", (0, 0, 0), (0, 0, 0));
	pilot     			 LinkTo(bird, "tag_driver", (0, 0, 0), (0, 0, 0));

	bird thread anim_loop_solo(level.hero_lone_star, "intro_heli_loop", "ender", "tag_detach_left" );
	bird thread anim_loop_solo(level.hero_reno,      "intro_heli_loop", "ender", "tag_detach_right");
	bird thread anim_loop_solo(pilot,      			 "intro_heli_loop", "nothing", "tag_driver");

	yaw_tweak = 35;   // positive = look left
	pitch_tweak = -15; // positive = look down
	tag_origin = spawn_tag_origin();
	tag_origin LinkTo(bird, "tag_guy2", (0, 0, 0), (0, 0, 0));
	
	level.player PlayerLinkTo(tag_origin, "tag_origin", .8, 0, 55, 5, 25, false);
	waitframe();  // necessary or you end up stuck at the limits of the view clamp
	level.player SetPlayerAngles(tag_origin.angles + (pitch_tweak, yaw_tweak, 0));
	
	flag_wait( "intro_screen_complete" );
	
	hud_off();
	
	bird gopath();

	bird waittill("unloading");
	
	flag_set( "flag_little_bird_landed" );
	
	Earthquake( 0.2, 1, level.player.origin, 850 );
	
	getent_safe("intro_heli_blocker", "script_noteworthy") delayCall(4, ::Delete);
	
	pilot delayCall(15, ::Delete);
	
	thread bird_fly_away_post_touchdown(bird);

	anim_ent = getstruct("heli_intro_struct", "script_noteworthy");
	
	// heli might not land in exactly the right spot, so we do the adjusted anim ent dance to avoid a pop
	adjusted_anim_ent = (level.hero_lone_star create_anim_ent_for_my_position("intro_heli_exit")) spawn_tag_origin();
	level.hero_lone_star LinkTo(adjusted_anim_ent);
	level.hero_reno LinkTo(adjusted_anim_ent);
	duration = 2;
	adjusted_anim_ent MoveTo(anim_ent.origin, duration, duration / 3, duration / 3);
	adjusted_anim_ent RotateTo(anim_ent.angles, duration, duration / 3, duration / 3);
	level.hero_lone_star delayCall(duration + .5, ::UnLink);
	level.hero_reno delayCall(duration + .5, ::UnLink);
	
	thread player_exits_little_bird(tag_origin);

	if ( ( level.Console && level.ps3 ) || !level.Console )
	{
		SetHalfResParticles( false );
	}
	
	bird notify("ender");
	
	// hmm, i think this takes much longer for reno vs. lonestar - seems to work though, except for some silly loops
	adjusted_anim_ent anim_single(guys, "intro_heli_exit");
	adjusted_anim_ent Delete();
	
	flag_set( "flag_obj_01_position_change_1" );

	delayThread(4, ::autosave_now);

	// have to thread these off because they're different lengths
	add_wait(::intro_roof_jumpdown_reno, anim_ent);
	add_wait(::intro_roof_jumpdown_lone_star, anim_ent);
	do_wait();	
}

little_bird_camera_shake()
{
	level endon("little_bird_camera_shake_stop");
	for(;;)
	{
		Earthquake( 0.08, .4, level.player.origin, 850 );
		wait RandomFloatRange(.05, .3);
	}
}

little_bird_camera_shake_stop()
{
	level notify("little_bird_camera_shake_stop");	
}

intro_roof_jumpdown_reno(anim_ent)
{
	scripted_sequence_recon("roof_jumpdown_reno", true, level.hero_reno, 4);
	anim_ent anim_single_solo_run(level.hero_reno, "intro_roof_jumpdown");
	level.hero_reno goto_node("node_reno_heli_intro_complete", false);
}

intro_roof_jumpdown_lone_star(anim_ent)
{
	scripted_sequence_recon("roof_jumpdown_sandman", true, level.hero_lone_star, 3);
	anim_ent anim_single_solo_run(level.hero_lone_star, "intro_roof_jumpdown");
	level.hero_lone_star goto_node("node_lonestar_heli_intro_complete", false);
}

bird_fly_away_post_touchdown(bird)
{

	// hack until we animate the bird
	bird Vehicle_SetSpeed(0, 10, 10);
	
	aud_send_msg("aud_paris_intro_heli_exit", bird);
	
	wait 2.75;
	bird SetAirResistance(10);
	bird SetJitterParams((300, 300, 200), .25, .5);  // not sure the jitter params are working
	bird SetHoverParams(100, 5, 5);
	bird SetMaxPitchRoll(30, 30);

	//heli hacks till we change the path / animate it
	bird Vehicle_SetSpeed(10, 10, 10);
}
	
player_exits_little_bird(tag_origin)
{
	level.player delayCall(1.5, ::EnableWeapons);
	wait 1.7;
	little_bird_camera_shake_stop();

	struct = getstruct("struct_intro_player_location", "script_noteworthy");
	assert(isdefined(struct));
	assert(isdefined(struct.origin));

	tag_origin Unlink();

	goal_angles = flat_angle(tag_origin.angles);
	
	duration = .4;
	level.player thread player_smooth_unclamp(duration, 0, 55, 5, 25);
	tag_origin MoveTo(struct.origin, duration, duration * .7, duration * .2);
	tag_origin RotateTo(goal_angles, duration, duration * .7, duration * .2);
	
	wait duration;
	
	level.player Unlink();
	
	tag_origin Delete();
	level.player player_control_on();
	hud_on();
}

helicopter_wind()
{
	self endon("death");
	for(;; waitframe())
	{
		PhysicsExplosionCylinder(self.origin, 200, 100, .05);
	}
}


rooftops_sequence_init()
{
	corpse = getent_safe( "corpse_check_vitals", "script_noteworthy" ) spawn_ai(true);
	corpse = maps\_vehicle_aianim::convert_guy_to_drone(corpse);
	corpse.animname = "corpse";
	anim_ent = GetStruct( "struct_delta_check_vitals", "script_noteworthy" );
	anim_ent anim_first_frame_solo( corpse, "delta_check_vitals" );
	
	level.check_vitals_corpse = corpse;

	anim_ent = getstruct("struct_move_debris", "script_noteworthy");
	level.move_debris_model = spawn_anim_model("debris");
	level.move_debris_model Hide();
	level.move_debris_model_model = spawn_anim_model("debris");
	level.move_debris_model_model LinkTo(level.move_debris_model, "slab", (0, 0, 0), (0, 0, 0));
	anim_ent anim_first_frame_solo(level.move_debris_model, "move_debris");
}



rooftops_sequence()
{
	// this combines what we previously called check_vitals, move_debris, and shimmy_moment
	
	level.hero_lone_star thread rooftops_sequence_lone_star();
	level.hero_reno thread rooftops_sequence_reno();
}
	
rooftops_sequence_lone_star()
{
	flag_wait( "flag_check_vitals" );
	
	disable_ai_color();
	anim_ent = getstruct("struct_delta_check_vitals", "script_noteworthy");
	anim_ent anim_reach_solo(self, "delta_check_vitals");
	
	// timing of the other guy starting depends on when we leave
	scripted_sequence_recon("check_vitals", true, self, 2);
	delayThread(4, ::flag_set, "flag_move_debris_guy2_begin");
	anim_ent anim_single_run([self, level.check_vitals_corpse], "delta_check_vitals");
	
	ally_keep_player_distance_stop();
	anim_ent = getstruct("struct_move_debris", "script_noteworthy");
	anim_ent anim_reach_solo(self, "move_debris");
	
	
	if(!flag("flag_move_debris_guy2_commited"))
	{
		scripted_sequence_recon("jank_rooftops_sequence_lonestar_waiting", true, self);
		/# debug_print("Lone Star waiting because Reno was slow, no pretty idle"); #/
	}
	else
	{
		scripted_sequence_recon("jank_rooftops_sequence_lonestar_waiting", false);
	}
			
	flag_wait("flag_move_debris_guy2_commited");
	
	// will be re-enabled when reno starts ledge walk
	// todo: make this not a global setting
	SetSavedDvar("ai_friendlyFireBlockDuration", 0);
	
	/#
	if(!player_can_see_ai(self, 0.05) && Distance(level.player.origin, self.origin) > 39*3)
	{
		debug_print("Look at Lone Star!");
	}
	#/
	
	while(!player_can_see_ai(self, 0.05))
		waitframe();
	
	// extra wait to sync the anims
	// duration is the start of paris_delta_move_debris_out_guy2 minus the start of paris_delta_move_debris_guy1
	// = frame 441 - frame 213 = 228 frames = 7.6 seconds
	scripted_sequence_recon("move_debris", true, self, 3);
	delayThread(7.6, ::flag_set, "flag_move_debris_guy2_stop_idle");	
	self disable_awareness();
	thread rooftops_sequence_debris(anim_ent);
	aud_send_msg("debris_push_animation");
	anim_ent anim_single_solo_run(self, "move_debris");
	
	anim_ent = getstruct("struct_delta_ledge_walk", "script_noteworthy");
	anim_ent anim_reach_solo(self, "delta_ledge_walk");
	self enable_awareness();
	
	scripted_sequence_recon("ledge_walk_guy1", true, self, 1);
	thread shimmy_moment_npc_slowdown(anim_ent);
	anim_ent anim_single_solo_run(self, "delta_ledge_walk");

	self notify("shimmy_moment_npc_slowdown_end");
	enable_ai_color();	
}
	
rooftops_sequence_reno()
{
	flag_wait("flag_check_vitals");
	
	disable_ai_color();
	goto_node("node_reno_check_vitals", true);
	
	/#
	if(flag("flag_move_debris_guy2_begin"))
		debug_print("timing may be off because reno was too slow getting to node_reno_check_vitals");
	#/
	flag_wait("flag_move_debris_guy2_begin");

	// the additive animation for crouch and cqb poses is broken, in the case that we send true for the second argument,
	// so just skip it in that case.
	handsignal_will_work = true;
	if ( self.a.pose == "crouch" )
		handsignal_will_work = false;
	else if ( self.script == "cover_right" )
		handsignal_will_work = true;
	else if ( self animscripts\utility::isCQBWalking() )
		handsignal_will_work = false;
	
	if(handsignal_will_work)
		handsignal("go", true);

	ally_keep_player_distance_stop();
	anim_ent = getstruct("struct_move_debris", "script_noteworthy");
	anim_ent anim_reach_solo(self, "move_debris_in");
	
	flag_set("flag_move_debris_guy2_commited");
	self disable_awareness();
	anim_ent anim_single_solo(self, "move_debris_in");

	anim_ent thread anim_loop_solo(self, "move_debris_idle", "reno_ender");
	/#
	if(flag("flag_move_debris_guy2_stop_idle"))
		debug_print("animation is out of sync because lone_star started too fast");
	#/
	flag_wait("flag_move_debris_guy2_stop_idle");

	getent("blocker_rooftops", "script_noteworthy") delayCall(5, ::Delete);	
	anim_ent notify("reno_ender");
	
	anim_ent anim_single_solo_run(self, "move_debris");

	anim_ent = getstruct("struct_delta_ledge_walk", "script_noteworthy");
	anim_ent anim_reach_solo(self, "delta_ledge_walk");
	
	anim_ent anim_first_frame_solo(self, "delta_ledge_walk");
	test_point = GetStartOrigin(anim_ent.origin, anim_ent.angles, self getanim("delta_ledge_walk")) + (0, -32, 60);
	
	for(;; waitframe())
	{
		if(flag("flag_dialogue_watch_your_step"))
			break;
		
		player_eye = level.player GetEye();
		
		if(SightTracePassed(player_eye, test_point, false, level.player, self))
			break;
		
		npc_trace_point = self.origin + RandomFloatRange(-16, 16) * AnglesToRight(self.angles) + RandomFloatRange(-16, 16) * AnglesToForward(self.angles) + RandomFloatRange(0, 64) * AnglesToUp(self.angles);
		
		if(SightTracePassed(player_eye, npc_trace_point, false, level.player, self))
			break;
	}
	
	
	self enable_awareness();
	SetSavedDvar( "ai_friendlyFireBlockDuration", 2000 );
	thread shimmy_moment_npc_slowdown(anim_ent);
	scripted_sequence_recon("ledge_walk_guy2", true, self, 2);
	anim_ent anim_single_solo_run(self, "delta_ledge_walk");

	self notify("shimmy_moment_npc_slowdown_end");
	enable_ai_color();	
}

rooftops_sequence_debris(anim_ent)
{
	anim_ent anim_single_solo_run(level.move_debris_model, "move_debris");
		
	level.move_debris_model_model Unlink();
	
	// PhysicsLaunchServer seems to preserve momentum but not angular momentum, so
	// give it a little kick also
	level.move_debris_model_model PhysicsLaunchServer(level.move_debris_model_model.origin + AnglesToUp(level.move_debris_model_model.angles) * 108, (0, 0, -1000));
	
	
	//level.move_debris_model_model PhysicsLaunchClient();
	//level.move_debris_model Launch((0, -5*12, -20 * 12));	
}


shimmy_moment_npc_slowdown(struct)
{
	outer_radius = 64;
	inner_radius = 40;
	min_rate = 0;

	self thread shimmy_moment_register_npc(struct);
}

shimmy_moment_register_npc(struct)
{
	if(!IsDefined(struct.shimmy_users))
		struct.shimmy_users = [];
	struct.shimmy_users[struct.shimmy_users.size] = self;
	
	self waittill("shimmy_moment_npc_slowdown_end");
	
	struct.shimmy_users = array_remove(struct.shimmy_users, self);
}

shimmy_moment_get_closest_npc(origin)
{
	struct = GetStruct("struct_delta_ledge_walk", "script_noteworthy");

	return getClosest(origin, struct.shimmy_users);
}

jets_flyby_01()
{
	flag_wait( "player_rooftop_jets_flyby_01" );
	jets_rooftops_01 = spawn_vehicles_from_targetname_and_drive( "jets_rooftops_01" );
	jets_rooftops_02 = spawn_vehicles_from_targetname_and_drive( "jets_rooftops_02" );
	aud_send_msg("jets_flyby_01", jets_rooftops_01);
}

jets_flyby_02()
{
	flag_wait( "player_rooftop_jets_flyby_02" );
	// Removed per Don, Brett, Kacper.
	//jets_rooftops_01 = spawn_vehicles_from_targetname_and_drive( "jets_rooftops_03" );
	//aud_send_msg("jets_flyby_02", jets_rooftops_01);
	autosave_by_name( "save_arch_building" );
}

stairwell_reaction()
{		
	flag_wait( "player_rooftop_jump_complete" );
	// now that player can't backtrack, disable this trigger so enemy cars can drive through
	disable_trigger_with_targetname( "trigger_hurt_player_rooftops" );
	aud_send_msg("mus_pre_first_contact");
	reduced_speed = .7;
	level.player thread lerp_move_speed_scale(1, reduced_speed, 2);
		
	level.hero_lone_star ent_flag_init("flag_stairwell_reaction_ready");
	level.hero_reno      ent_flag_init("flag_stairwell_reaction_ready");
		
	anim_ent = GetStruct( "struct_delta_stairwell_reaction", "script_noteworthy" );
	node_lone_star = GetNode("node_sandman_stairwell_moment", "targetname");
	node_reno = GetNode("node_reno_stairwell_moment", "targetname");
		
	level.hero_lone_star thread stairwell_reaction_path_to_node_npc(node_lone_star);
	level.hero_reno      thread stairwell_reaction_path_to_node_npc(node_reno     );

	flag_wait( "flag_bookstore_spray_moment" ); // this flag means the player has arrived
		
	level notify("stairwell_reaction_path_to_node_npc_cancel");  // if they're not there yet, they're not going to be
	flag_set( "flag_dialogue_in_the_game" );
	thread bookstore_spray_moment();
	
	scripted_sequence_recon("stairwell_reaction", level.hero_lone_star ent_flag("flag_stairwell_reaction_ready") || level.hero_reno ent_flag("flag_stairwell_reaction_ready"), node_lone_star.origin + (0, 0, 32));

	level.hero_lone_star thread stairwell_reaction_play_npc();
	level.hero_reno      thread stairwell_reaction_play_npc();
	
	level.hero_lone_star 	thread ally_keep_player_distance(39 * 8, .8, 1.2, .25);	
	level.hero_reno     	thread ally_keep_player_distance(39 * 6, .8, 1.2, .25);

	level.player thread lerp_move_speed_scale(reduced_speed, 1, 3);
}
	
stairwell_reaction_path_to_node_npc(node)
{
	level endon("stairwell_reaction_path_to_node_npc_cancel");

	self disable_ai_color();
	self disable_awareness();
	
	radius = 12;
	self goto_node(node, true, radius);

	if(Distance(self.origin, node.origin) < radius * 1.1)
	{
		ent_flag_set("flag_stairwell_reaction_ready");	
	}
	else
	{
		AssertMsg("Guy didn't arrive at node, skipping animation");
	}
	
}

stairwell_reaction_play_npc(anim_ent)
{
	if(ent_flag("flag_stairwell_reaction_ready"))
	{		
		// yes, they actually are playing it on themselves
		scripted_sequence_recon("stairwell_reaction_" + self.animname, true, self);
		self anim_single_solo_run(self, "delta_stairwell_reaction");
	}
	else
	{
		scripted_sequence_recon("stairwell_reaction_" + self.animname, false);
	}
	
	self enable_ai_color();
	self enable_awareness();
}

	
stop_cqb_after_fall()
{
	trigger = getent_safe("trigger_rooftops_cqb_off", "targetname");
	
	while(!self IsTouching(trigger))
	{
		waitframe();	
	}
	
	disable_cqbwalk();
	
	if(self.animname == "lonestar") thread ally_keep_player_distance(39 * 14, .8, 1.2, .25);	
	if(self.animname == "reno")     thread ally_keep_player_distance(39 * 12, .8, 1.2, .25);
}
	
initial_combat()
{
	flag_wait( "flag_bookstore_spray_moment" );
	
	aud_send_msg("bookstore_spray_moment");
	
	battlechatter_on( "allies" );
		
	aud_send_msg("mus_first_contact");
	
	spawners_1 = getentarray( "ai_bookstore_initial", "targetname" );
	spawners_2 = getentarray( "ai_bookstore_initial_top", "targetname" );
	
	spawners = array_combine( spawners_1, spawners_2 );

	foreach( spawner in spawners )
	{
		if(IsDefined(spawner))
			spawner spawn_ai(true);
	}
	
	spawn_metrics_waittill_deaths_reach(1, ["ai_bookstore_initial_top", "ai_encounter_initial_top", "ai_bookstore_initial", "ai_bookstore_spray_moment"], 1);
	
	flag_set ( "flag_ai_initial_top_retreat" );
	
}

process_ai_script_parameters()
{
	if ( !isdefined( self.script_parameters ) )
		return;
	
	parms = strtok( self.script_parameters, ":;, " );
	
	foreach( parm in parms )
	{
		parm = tolower( parm );
		
		if ( parm == "balcony" )
			self.specialDeathFunc = ::balcony_special_death_func;
	}
}

balcony_special_death_func()
{
	// always return false in this function because we want the death
	// animscript to continue after this function no matter what
	
	if ( !isdefined( self ) )
		return false;
	
	if ( self.a.pose == "prone" )	// allow crouch
		return false;
	
	if ( !isdefined( self.prevnode ) )
		return false;
	
	if ( !isdefined( self.prevnode.script_balcony ) )
		return false;
	
	angleAI = self.angles[ 1 ];
	angleNode = self.prevnode.angles[ 1 ];
	angleDiff = abs( AngleClamp180( angleAI - angleNode ) );
	if ( angleDiff > 45 )
		return false;
	
	d = distance( self.origin, self.prevnode.origin );
	if ( d > 16 )
		return false;
	
	if ( isdefined( level.last_balcony_death ) )
	{
		elapsedTime = getTime() - level.last_balcony_death;
	
		// if one just happened within 5 seconds dont do it
		if ( elapsedTime < 5 * 1000 )
			return false;
	}
	
	trigger_balcony = GetEntArray( "trigger_balcony", "targetname" );
	foreach ( trigger in trigger_balcony )
	{
		d = Distance( trigger.origin, self.origin );
		if ( d < 48 )
		{
			trigger notify( "trigger" );
		}
	}
	
	GlassRadiusDamage( self.origin, 48, 500, 500 );

	level.last_balcony_death = getTime();
	deathAnims = getGenericAnim( "balcony_death" );
	
	play_balcony_deathanim(deathAnims[ RandomInt( deathAnims.size ) ]);
	return true;
}

// to avoid floating ragdolls, I must not return from the death animscript thread, so the actor doesn't become
// an actor_corpse, who would be frozen in space in the event that the ragdoll failed the tunnel test.
#using_animtree("generic_human");
play_balcony_deathanim(deathAnim)
{
	self endon("play_balcony_deathanim_stop");
	// this is modeled after the important parts of animscripts\death::playDeathAnim()

	if ( !animHasNoteTrack( deathAnim, "dropgun" ) && !animHasNoteTrack( deathAnim, "fire_spray" ) )// && !animHasNotetrack( deathAnim, "gun keep" )
		self animscripts\shared::DropAllAIWeapons();

	self setFlaggedAnimKnobAllRestart( "deathanim", deathAnim, %body, 1, .1 );

	Assert(animHasNotetrack(deathanim, "start_ragdoll"));
	
	self animscripts\notetracks::DoNoteTracksIntercept("deathanim", ::balcony_death_notetrack_intercept);
	self animscripts\shared::DropAllAIWeapons();
}

balcony_death_notetrack_intercept(note)
{
	if(note == "start_ragdoll")
	{
		// this is the last notetrack we will handle
		// special ragdoll handling
		self StartRagdoll();
		
		// hopefully the ragdoll works, but if we were in a solid, we would just freeze in the last frame.
		// to avoid that, after the animation finishes we will move ourselves down through the floor.
		// ultimately we will need some combination of making the animation longer so it goes through the floor
		// on its own, and tweaking notetrack times and geo so we don't get the frozen ragdoll case anyway.
		
		start_time = GetTime() * .001;
		start_origin = self.origin;
		self waittillmatch("deathanim", "end");
		elapsed_time = GetTime() * .001 - start_time;
		velocity = (self.origin - start_origin) / elapsed_time;
		
		fall_time = 5;
		tag_origin = self spawn_tag_origin();
		self LinkTo(tag_origin);
		
		// grr, MoveGravity seems very jerky.  Gonna have to ask the animators to do this for me.
		tag_origin MoveGravity(velocity, fall_time);
		wait fall_time;
		
		self Unlink();
		tag_origin Delete();
		
		// this will ultimately make us return from the death animscript.
		self notify("play_balcony_deathanim_stop");
		// not reached
	}
	return false;
}


bookstore_spray_moment()
{	
	spawner = getent( "ai_bookstore_spray_moment", "script_noteworthy" );
	
	wait .15;
	
	node = GetStruct("bookstore_spray_node", "script_noteworthy");
	node_teleport = GetStruct( "bookstore_spray_node_teleport", "script_noteworthy" );
	target_start = GetStruct("bookstore_spray_target_start", "script_noteworthy");
	target_end   = GetStruct("bookstore_spray_target_end",   "script_noteworthy");
	
	guy = spawner spawn_ai (true);
	if(!IsAlive(guy)) return;
	guy endon("death");

	guy disable_awareness();
	guy goto_node( "bookstore_spray_node_teleport", false );
	guy teleport(node_teleport.origin, node_teleport.angles);

	guy bullet_spray(target_start.origin, target_end.origin);
		
	guy set_goal_radius (2048);
	guy enable_awareness();
		
//	node delete();
	
//	guy stop_magic_bullet_shield();
}

bookstore_combat_exterior()
{
	add_wait(::flag_wait, "flag_obj_01_position_change_5" );
	add_wait(::flag_wait, "flag_ai_initial_top_retreat" );
	do_wait_any();

	spawn_vehicle_from_targetname_and_drive( "uaz_01" );
//	spawn_vehicle_from_targetname_and_drive( "mi17_bookstore_1" );
	
	disable_trigger_with_targetname( "trigger_color_bookstore_force" );
	
	spawners_1 = getentarray( "ai_bookstore_exterior", "script_noteworthy" );
	spawners_2 = getentarray( "ai_bookstore_upper", "script_noteworthy" );
	
	spawners = array_combine( spawners_1, spawners_2 );

 	foreach( spawner in spawners )
	{
		spawner spawn_ai(true);
	}
	
}
	
bookstore_runners()
{
	flag_wait_any( "flag_obj_01_position_change_5", "flag_ai_exits_stairwell" );
		
	spawners = getentarray( "ai_bookstore_runners", "script_noteworthy" );
	array_thread( spawners, ::add_spawn_function, ::fire_while_moving );
	array_thread( spawners, ::add_spawn_function, ::lower_accuracy );

	foreach( spawner in spawners )
	{
		spawner spawn_ai();
	}
}
	
player_enters_bookstore()
{
	flag_wait( "flag_player_enters_bookstore" );
	
	thread enemy_balcony_think();
	thread spawn_corpses("dead_bodies_back_alley");
	
	thread bookstore_combat_interior();
	thread bookstore_combat_interior_top();
	thread bookstore_combat_interior_rear();
			
	aud_send_msg("mus_enter_book_store");
}
	
enemy_balcony_think()
{
	volume = GetEnt( "info_v_ai_bookstore_balcony", "targetname" );
	
	while(true)
	{
		anybody_touching_volume = false;
		foreach(guy in getaiarray( "axis" ))
		{
			if(guy IsTouching(volume))
			{
				anybody_touching_volume = true;
				break;	
			}
		}
	
		if(anybody_touching_volume)
			break;
	
		waitframe();	
	}
	
	flag_set( "flag_dialogue_bookstore_balcony" );
}	

enemy_top_floor_think()
{
	volume = GetEnt( "info_v_ai_bookstore_top_floor", "targetname" );
	
	while(true)
	{
		anybody_touching_volume = false;
		foreach(guy in getaiarray( "axis" ))
		{
			if(guy IsTouching(volume))
			{
				anybody_touching_volume = true;
				break;	
			}
		}	
		if(!anybody_touching_volume)
			break;
	
		waitframe();
	}
	if(level.player IsTouching(volume) )
	{
		if ( level.hero_lone_star IsTouching(volume))
		{
			flag_set( "flag_dialogue_bookstore_top_floor_clear_1" );
			
			triggers = GetEntArray( "trigger_color_bookstore", "targetname" );
			foreach( trigger in triggers )
			{
				trigger trigger_off();
			}
			thread bookstore_assist_grinch_below_1();
			path_squad_with_trigger( "trig_color_bookstore_sandman_lower_floor" );
		}
		else
		{
			thread bookstore_assist_grinch_below_2();
		}
	}
}

bookstore_assist_grinch_below_1()
{
	guys = getaiarray ( "axis" );
	if(guys.size > 3)
	{
		flag_set( "flag_dialogue_bookstore_heavy_fire_1" );
	}	
}

bookstore_assist_grinch_below_2()
{
	guys = getaiarray ( "axis" );
	if(guys.size > 3)
	{
		flag_set( "flag_dialogue_bookstore_heavy_fire_2" );
	}	
}

bookstore_combat_interior()
{
	spawners = getentarray( "ai_bookstore_01", "script_noteworthy" );

 	foreach( spawner in spawners )
	{
		spawner spawn_ai();
	}	
	
	noteworthies = ["ai_encounter_initial", "ai_encounter_initial_top", "ai_bookstore_runners", "ai_bookstore_top_rear", "ai_bookstore_01", "ai_bookstore_02", "ai_bookstore_heli_1", "ai_bookstore_spray_moment" ];
	spawn_metrics_waittill_count_reaches(6, noteworthies, true);
	level.hero_lone_star enable_cqbwalk();
	level.hero_reno enable_cqbwalk();
}

bookstore_combat_interior_top()
{
	flag_wait( "flag_bookstore_combat_top_rear" );
	
	volume_top = GetEnt( "info_v_ai_bookstore_top_rear", "targetname" );
	volume_bottom = GetEnt( "info_v_ai_bookstore_bottom_rear", "targetname" );
	guys = volume_top get_ai_touching_volume( "axis" );
	guys = array_trim(guys, 3);
	
	array_call(guys, ::SetGoalVolumeAuto, volume_bottom );
	
	spawners = getentarray( "ai_bookstore_top_rear", "script_noteworthy" );

 	foreach( spawner in spawners )
	{
		spawner spawn_ai();
	}	
	
	waitframe();
	thread enemy_top_floor_think();
}	
	
bookstore_combat_interior_rear()
{
	flag_wait( "flag_bookstore_combat_interior" );
	
	volume_bottom = GetEnt( "info_v_ai_bookstore_bottom_rear", "targetname" );
	guys = volume_bottom get_ai_touching_volume( "axis" );
	guys = array_trim(guys, 3);

	additional_guys_needed = 5 - guys.size;
	additional_guys_spawners = array_trim(getentarray( "ai_bookstore_02", "script_noteworthy" ), additional_guys_needed);
		
	foreach( spawner in additional_guys_spawners )
	{
		spawner spawn_ai();
	}
		
	noteworthies = ["ai_encounter_initial", "ai_encounter_initial_top", "ai_bookstore_runners", "ai_bookstore_top_rear", "ai_bookstore_01", "ai_bookstore_02", "ai_bookstore_heli_1", "ai_bookstore_spray_moment" ];
	
	spawn_metrics_waittill_count_reaches(3, noteworthies, true);
			
	flag_set( "flag_bookstore_straglers" );
	
	thread restaurant_meeting_random_shots();	
	thread bookstore_wait_till_clear();
	
	spawn_metrics_waittill_count_reaches(1, noteworthies, true);
	delete_spawners(noteworthies);
	array_thread(GetAIArray("axis"), ::kill_when_player_not_looking);
		
	triggers = GetEntArray( "trigger_color_bookstore_combat_complete", "targetname" );
	foreach( trigger in triggers )
	{
		trigger trigger_off();
	}
		
	flag_set("bookstore_combat_interior_rear_done");	
}

bookstore_wait_till_clear()
{
	enable_trigger_with_targetname( "trigger_color_bookstore_force" );
	
	level.hero_reno disable_ai_color();
	level.hero_lone_star disable_ai_color();
	
	goal_node_reno = GetNode("node_reno_clear_boorkstore", "targetname");
	goal_nodes_lone_star = GetNodeArray("node_sandman_clear_boorkstore", "targetname");

	closest_node = getClosest( level.hero_lone_star.origin, goal_nodes_lone_star );

	level.hero_reno goto_node(goal_node_reno, false);
	level.hero_lone_star goto_node(closest_node, false);
}	

bookstore_reno_check_door_init()
{
	level.bookstore_door = spawn_anim_model("bookstore_door");
	anim_ent = getstruct("struct_bookstore_exit", "script_noteworthy");
	anim_ent anim_first_frame_solo(level.bookstore_door, "bookstore_exit_exit");
	blocker = getent_safe("blocker_bookstore_exit", "script_noteworthy");
	
	// really we want to disconnect them, but not doing it yet because there's some NPCs that go through the door.
	blocker ConnectPaths();
}

bookstore_reno_check_door()
{
	flag_wait("bookstore_combat_interior_rear_done");
	
	battlechatter_off( "allies" );
	
	trigger = getent("trigger_color_bookstore_top", "targetname");
	if(IsDefined(trigger)) disable_trigger_with_targetname( "trigger_color_bookstore_top" );
	
	flag_set( "flag_dialogue_bookstore_clear" );
	aud_send_msg("mus_bookstore_clear");
	delayThread(1, ::flag_set, "flag_dialogue_check_door");
		
	anim_ent = getstruct("struct_bookstore_exit", "script_noteworthy");
	
	level.hero_reno      ent_flag_init("flag_bookstore_exit_ready");
	
	level.hero_lone_star ent_flag_init("flag_bookstore_exit_ready");
	
	level.hero_reno      thread bookstore_check_door_npc(anim_ent);
	level.hero_lone_star thread bookstore_check_door_npc(anim_ent);
	
	level.hero_reno      ent_flag_wait("flag_bookstore_exit_ready");
	level.hero_lone_star ent_flag_wait("flag_bookstore_exit_ready");
	
	autosave_by_name( "save_bookstore_breach" );
	
	flag_wait_all( "flag_bookstore_exit_player_nearby" , "flag_dialogue_check_door_complete" );
	
	thread bookstore_breach_axis_death("guy_bookstore_death_1", "struct_bookstore_alley_shooting_1", "bookstore_alley_shooting_1");
	thread bookstore_breach_axis_death("guy_bookstore_death_2", "struct_bookstore_alley_shooting_2", "bookstore_alley_shooting_2");
			
	thread alley_bullet_spray();
	thread gign_wave_restaurant();
	thread gign_meeting_runner();
	
	flag_set( "flag_obj_01_position_change_6" );
	flag_set( "flag_bookstore_exit_start" );
	
	SetSavedDvar( "ai_friendlyFireBlockDuration", 0 );
	
	anim_ent = getstruct("struct_bookstore_exit", "script_noteworthy");
	anim_ent thread anim_single_solo(level.bookstore_door, "bookstore_exit_exit");
	blocker = getent_safe("blocker_bookstore_exit", "script_noteworthy");
	blocker delayCall(2.5, ::Delete);
	
	flag_wait( "flag_ai_clean_up_initial" );
	
	disable_trigger_with_targetname( "trigger_color_bookstore_force" );
}
	
bookstore_check_door_npc(anim_ent)
{
	ender_string = self.animname + "_ender";
	
	self disable_awareness();
	
	anim_ent anim_reach_solo(self, "bookstore_exit_st");
	anim_ent anim_single_solo(self, "bookstore_exit_st");
	anim_ent thread anim_loop_solo(self, "bookstore_exit_idle", ender_string);
	self ent_flag_set("flag_bookstore_exit_ready");
	self disable_cqbwalk();
	
	flag_wait("flag_bookstore_exit_start");
		
	level.player SetMoveSpeedScale(.8);
	
	anim_ent notify(ender_string);
	scripted_sequence_recon("bookstore_check_door_" + self.animname, true, self, 2);
	anim_ent anim_single_solo_run(self, "bookstore_exit_exit");
	
	self enable_awareness();
	self enable_ai_color();
	self enable_sprint();
}

alley_gign()
{
	goal_node = GetNode( "node_gign_1_behind_kitchen", "targetname" );
	guy = getent( "gign_alley", "script_noteworthy" ) spawn_ai(true);
	guy endon("death");

	goal_node = GetNode( "node_gign_1_behind_kitchen_guard", "targetname" );
	guy goto_node(goal_node, false);
	
	flag_wait( "flag_courtyard_1_wave_4" );
	guy delete();
}	

alley_bullet_spray()
{	
	spawner = getent( "gign_alley_spray", "script_noteworthy" );
	
	wait 1;
	
	node = GetStruct("alley_spray_node", "script_noteworthy");
	node_teleport = GetStruct( "alley_spray_node_teleport", "script_noteworthy" );
	target_start = GetStruct("alley_spray_target_start", "script_noteworthy");
	target_end   = GetStruct("alley_spray_target_end",   "script_noteworthy");
	goal_node = GetNode( "node_gign_behind_kitchen", "targetname" );
	
	guy = spawner spawn_ai (true);
	
	guy deletable_magic_bullet_shield();
	if(!IsAlive(guy)) return;
	guy endon("death");

	guy goto_node( "alley_spray_node_teleport", false );
	guy teleport(node_teleport.origin, node_teleport.angles);

	guy bullet_spray(target_start.origin, target_end.origin);
	
	guy goto_node(goal_node, true);
	
	guy stop_magic_bullet_shield();
	guy delayThread(1, ::handsignal,"onme");
	
	flag_wait( "flag_courtyard_1_wave_4" );
	guy delete();
}
	
bookstore_breach_axis_death(spawner_targetname, anim_struct_targetname, generic_anime)
{
	guy = getent( spawner_targetname, "targetname" ) spawn_ai(true);
	guy.deathanim = getanim_generic(generic_anime);
	guy.deathFunction = ::ragdoll_death_noimpulse;
	
	guy endon( "death" );
	guy gun_remove();
	guy.ignoreme = true;
	guy.ignoreall = true;

	anim_ent = getstruct( anim_struct_targetname, "targetname" );
	anim_ent anim_generic_first_frame( guy, generic_anime );
	
	anim_ent anim_generic( guy, generic_anime );
	if( IsDefined(level.scr_anim[ "generic" ][ generic_anime + "_death" ] ) )
		anim_ent anim_generic_first_frame( guy, generic_anime + "_death" );
	
	waittillframeend;
	guy kill();
}

ragdoll_death_noimpulse()
{
    self StartRagdoll();
} 

gign_wave_restaurant()
{
	anim_ent = getstruct( "struct_gign_restaurant_wave" , "targetname" );
	guy = getent( "gign_alley_wave", "script_noteworthy" ) spawn_ai(true);
	guy endon( "death" );
	
	anim_ent thread anim_generic_loop( guy, "gign_wave", "end_wave" );
		
	flag_wait( "flag_gign_wave_complete" );
	
	wait 2;
	anim_ent notify("end_wave");
	guy stopanimscripted();
	
	goal_node = GetNode("node_gign_wave_kitchen", "targetname");
				
	guy set_ignoreall(true);
	guy goto_node(goal_node, true, 8);
	
	flag_wait( "flag_courtyard_1_wave_4" );
	guy delete();
}	

gign_meeting_runner()
{
	flag_wait( "flag_gign_meeting_runner" );
	
	level.player.participation = 0;
	
	thread alley_gign();
	
	anim_ent = getstruct( "struct_gign_meeting_runner" , "targetname" );
	goal_node = GetNode("node_gign_meeting_runner", "targetname");
	guy = getent( "gign_alley_runner", "script_noteworthy" ) spawn_ai(true);
	
	guy endon( "death" );
	guy enable_sprint();
	guy set_ignoreall(true);

	anim_ent anim_generic( guy, "gign_meeting_runner" );
	
	guy goto_node(goal_node, true);
	
	guy waittill("goal");	
	guy delete();	
}	

ai_clean_up_initial()
{
	flag_wait( "flag_ai_clean_up_initial" );
	cleanup_ai_with_script_noteworthy( "ai_encounter_initial", 128 );
}


ai_clean_up_restaurant_alley()
{
	flag_wait( "flag_ai_clean_up_restaurant_alley" );
	cleanup_ai_with_script_noteworthy( "ai_restaurant_alley", 128 );
	cleanup_ai_with_script_noteworthy( "enemy_kill_civ_street_alley_2", 128 );
}

tanks_side_alley_bookstore()
{
	self endon("trigger_restaurant_meeting");

	flag_wait( "flag_obj_01_position_change_5" );

	for(i = 0; i < 20 ; i++)
	{
		tanks = spawn_vehicles_from_targetname_and_drive("tank_battalion_bookstore");
		aud_send_msg("tank_battalion_bookstore", tanks);
		wait 5;
	}
}

jet_flyby_back_alley()
{
	flag_wait( "flag_jet_flyby_back_alley" );
	jets_rooftops_01 = spawn_vehicles_from_targetname_and_drive( "jet_back_alley_01" );
	aud_send_msg("jet_flyby_back_alley", jets_rooftops_01);
}
	

sprint_to_restaurant()
{
	/*
	flag_wait( "flag_bookstore_exit_player_nearby" );
	
	level.hero_reno ally_keep_player_distance_stop();
	level.hero_lone_star ally_keep_player_distance_stop();
	
	level.hero_reno enable_sprint();
	level.hero_lone_star enable_sprint();
	*/
}
		
restaurant_meeting_init()
{
	flag_wait("restaurant_spawn_heroes");
	
	level.hero_frenchie = spawn_targetname("frenchie");
	level.hero_redshirt = spawn_targetname("redshirt");
	level.extras_gign = array_spawn_targetname("extras_gign");
	
	level.hero_frenchie disable_ai_color();
	level.hero_redshirt disable_ai_color();

	array_thread( level.extras_gign, ::disable_ai_color );

	level.hero_frenchie deletable_magic_bullet_shield();
	level.hero_redshirt deletable_magic_bullet_shield();
	
	foreach(dude in level.extras_gign)
	{
		if(IsAlive(dude))
			dude deletable_magic_bullet_shield();
	}
	
	anim_ent = GetStruct("struct_conversation_with_gign", "script_noteworthy");

	anim_ent thread anim_loop_solo(level.hero_frenchie, "conversation_with_gign_idle", "stop_loop");

	battlechatter_on( "allies" );

	thread spawn_corpses("dead_gign_restaurant");
	
	thread courtyard_1_wave_initial();
//	thread restaurant_meeting_random_shots();	
		
	thread conversation_blocker();
	
	disable_enemy_grenades();
}

restaurant_meeting()
{
	anim_ent = GetStruct("struct_conversation_with_gign", "script_noteworthy");
	
	level.hero_reno disable_sprint();

	level.hero_reno      thread ally_keep_player_distance(39 * 6, .8, 1.2, .25);
	level.hero_lone_star thread ally_keep_player_distance(39 * 8, .8, 1.2, .25);	
	
	level.extras_gign = array_removeDead(level.extras_gign);
	level.extras_gign = array_removeUndefined(level.extras_gign);
	array_thread(level.extras_gign, ::disable_ai_color);

	level.hero_lone_star ally_keep_player_distance_stop();
	level.hero_reno ally_keep_player_distance_stop();
	
	// todo: not sure if we really want this, leaving for consistency with what was there
	level.hero_reno disable_ai_color();
	
	anim_ent anim_reach_solo(level.hero_lone_star, "conversation_with_gign");
	
	// note: an idle would be nice here, but it's not bad without it.
	anim_ent anim_first_frame_solo(level.hero_lone_star, "conversation_with_gign");
	
	// wait for the player to get in the room or see the exchange
	for(time = 0; time < 5; time += 0.05)
	{
		if(flag("flag_player_in_restaurant"))
			break;
		
		player_eye = level.player GetEye();
		
		npc = level.hero_lone_star;
		npc_trace_point = npc.origin + RandomFloatRange(-16, 16) * AnglesToRight(npc.angles) + RandomFloatRange(-16, 16) * AnglesToForward(npc.angles) + RandomFloatRange(0, 64) * AnglesToUp(npc.angles);
		
		if(SightTracePassed(player_eye, npc_trace_point, false, level.player, npc))
			break;
		
		waitframe();
	}	
	
	flag_set( "flag_restaurant_meeting_start" );
	
	SetSavedDvar( "ai_friendlyFireBlockDuration", 2000 );
	
	level.hero_lone_star disable_sprint();
	
	level.hero_reno disable_ai_color();
	level.hero_reno set_ignoreall(true);
	level.hero_reno goto_node(GetNode("node_reno_kitchen", "targetname"), false);
		
	// todo: at some point this audio needs to be part of the anim scene
	flag_set("flag_dialogue_restaurant_meeting");
	delaythread(11.25, ::flag_set, "flag_conversation_blocker_leave");	
	
	anim_ent notify("stop_loop");
	scripted_sequence_recon("restaurant_meeting", true, level.hero_frenchie, 3);
	anim_ent anim_single_run([level.hero_lone_star, level.hero_frenchie], "conversation_with_gign");
	level.hero_lone_star thread anim_single_solo_run(level.hero_lone_star, "conversation_with_gign_end");
	
	activate_trigger_with_targetname( "trig_color_kitchen_force" );
	
	level.extras_gign = array_removeDead(level.extras_gign);
	level.extras_gign = array_removeUndefined(level.extras_gign);
	array_thread(level.extras_gign, ::disable_awareness);
	
	foreach(dude in level.extras_gign)
	{
		if(IsAlive(dude))
			dude stop_magic_bullet_shield();
	}
		
	flag_set("flag_restaurant_meeting_complete");
	
	thread spawn_corpses("dead_civ_courtyard_1");
	thread corpses_yoga_studio();
	
	level notify("restaurant_meeting_random_shots_stop");
		
	add_wait(::frenchie_exit_kitchen);
	add_wait(::sandman_exit_kitchen);
	add_wait(::reno_exit_kitchen);
	do_wait();
	
	level.extras_gign = array_removeDead(level.extras_gign);
	level.extras_gign = array_removeUndefined(level.extras_gign);
	array_thread(level.extras_gign, ::enable_ai_color);
	array_thread(level.extras_gign, ::enable_awareness);
	
	thread friendlies_keep_player_distance_on();
	
	level.player SetMoveSpeedScale(1);
}

corpses_yoga_studio()
{
	for(;;)
	{
    	flag_wait("flag_dead_civ_yoga_studio");  // a trigger_set_touching
                
        corpses = spawn_corpses("dead_civ_yoga_studio");

        flag_wait("flag_dead_civ_yoga_studio_delete");  // a trigger_set_touching

        foreach(corpse in corpses)
        {
        	if(IsDefined(corpse))
            	corpse delete();
        }
    }
}

conversation_blocker()
{	
	anim_ent = getstruct("struct_conversation_with_gign", "script_noteworthy");
	
	guard   = level.hero_redshirt;
	Assert(IsDefined(guard.magic_bullet_shield));
	wounded = getent_safe("conversation_blocker_wounded", "script_noteworthy") spawn_ai(true, true);
	scripted_sequence_recon("jank_conversation_blocker_spawn", true, wounded);	
	wounded.animname = "wounded";
	wounded.drawoncompass = false;
	wounded disable_awareness();
	wounded gun_remove();

	guard disable_ai_color(); 
		
	guys = [guard, wounded];
		
	anim_ent anim_first_frame(guys, "conversation_blocker");
			
	flag_wait_any("flag_restaurant_meeting_start", "flag_player_in_restaurant");
	scripted_sequence_recon("jank_conversation_blocker_start", true, wounded);	
	
	guard thread conversation_blocker_guard(anim_ent);
	wounded thread conversation_blocker_wounded(anim_ent);
}

conversation_blocker_guard(anim_ent)
{
	self disable_awareness();
		
	anim_ent anim_single_solo(self, "conversation_blocker");
		
	// idle isn't relative to the same node as the rest, so we do this...
	hack_ent = spawn_tag_origin();
	hack_ent.origin = self.origin;
	hack_ent.angles = self.angles;
	
	hack_ent thread anim_loop_solo(self, "conversation_blocker_idle_no_origin", "ender" );

	flag_wait("flag_conversation_blocker_leave");
		
	hack_ent notify("ender");
	
	hack_ent anim_single_solo(self, "conversation_blocker_exit", undefined, (52 - 33)/30);	
	self anim_single_solo_run(self, "conversation_blocker_exit_end");
	
	getent_safe("blocker_restaurant", "script_noteworthy") Delete();
	
	self goto_node("conversation_blocker_end_node", true);	
	self enable_awareness();
	self enable_ai_color_dontmove();
}


conversation_blocker_wounded(anim_ent)
{
	anim_ent anim_single_solo(self, "conversation_blocker");
	
	// idle isn't relative to the same node as the rest, so we do this...
	hack_ent = spawnstruct();
	hack_ent.origin = self.origin;
	hack_ent.angles = self.angles;
	hack_ent anim_loop_solo(self, "conversation_blocker_idle_no_origin");
}

frenchie_exit_kitchen()
{
	level.hero_frenchie disable_ai_color();
	level.hero_frenchie enable_cqbwalk();
	level.hero_frenchie disable_awareness();
			
	level.hero_frenchie  goto_node("node_sabre_exit_kitchen_1", true);
	level.hero_frenchie disable_cqbwalk();
	wait 1.5;
	level.hero_frenchie  goto_node("node_sabre_exit_kitchen_2", true);
	wait .5;	
	level.hero_frenchie enable_awareness();
	level.hero_frenchie enable_ai_color();
}	
	
sandman_exit_kitchen()
{
	goal_node = GetNode("node_sandman_exit_kitchen", "targetname");
		
	level.hero_lone_star disable_ai_color();
	level.hero_lone_star enable_cqbwalk();
	level.hero_lone_star disable_awareness();
	
	level.hero_lone_star goto_node(goal_node, true);
	
	level.hero_lone_star enable_awareness();
	level.hero_lone_star disable_cqbwalk();
	level.hero_lone_star enable_ai_color();
}
	
reno_exit_kitchen()
{
	level.hero_reno enable_ai_color();	
	level.hero_reno set_ignoreall(false);
}
		
restaurant_meeting_random_shots()
{
	// how long between bursts, seconds
	wait_min = .25;
	wait_max = 2.25;
	
	// how many shots
	burst_size_min = 3;
	burst_size_max = 10;
	
	// min/max fire rate, rounds per second
	fire_rate_min = 10;
	fire_rate_max = 20;
	
	// randomness on the aim
	noise_radius = 64;
	
	level endon("restaurant_meeting_random_shots_stop");
	
	origins = getstructarray("kitchen_spray_origin", "script_noteworthy");
	targets = getstructarray("kitchen_spray_target", "script_noteworthy");
	
	for(;;)
	{		
		burst_size = RandomIntRange(burst_size_min, burst_size_max);
		fire_delay = min(1.0 / RandomFloatRange(fire_rate_min, fire_rate_max), 0.05);
		origin = random(origins);
		target = random(targets);
		
		for(i = 0; i < burst_size; i++)
		{
			start = origin.origin;
			end = target.origin + randomvector(noise_radius);
			
			MagicBullet("scar_h_acog", start, end);
						
			// /# thread draw_line(start, end, 1, 0, 0); #/
			
			wait fire_delay;
		}		
		wait(RandomFloatRange(wait_min, wait_max));		
	}	
}

courtyard_1_wave_initial()
{
	spawners = getentarray( "enemy_courtyard_1_wave_1", "script_noteworthy" );

	if(spawners.size > 0)
 	{
		maps\_spawner::flood_spawner_scripted( spawners );
	}
	
	foreach(guy in GetEntArray("enemy_courtyard_1_wave_1", "script_noteworthy"))
	{
		if(IsAlive(guy))
		{
			guy deletable_magic_bullet_shield();	
		}	
	}
	
	flag_wait( "flag_courtyard_1_magic_shield_off" );
	
	enable_enemy_grenades();
	
	foreach(guy in GetEntArray("enemy_courtyard_1_wave_1", "script_noteworthy"))
	{
		if(IsAlive(guy))
		{
			guy stop_magic_bullet_shield();	
		}	
	}
	
	spawners_wave_1 = ["enemy_courtyard_1_wave_1"];
	
	flag_wait( "flag_courtyard_1_wave_2" );

	delete_spawners(spawners_wave_1);

	spawners = getentarray( "enemy_courtyard_1_wave_2", "script_noteworthy" );
	
	if(spawners.size > 0)
	{
		maps\_spawner::flood_spawner_scripted( spawners );
	}
	
	spawners = getentarray( "enemy_courtyard_1_rpg", "script_noteworthy" );

	if(spawners.size > 0)
 	{
		maps\_spawner::flood_spawner_scripted( spawners );
	}
		
	flag_wait( "flag_courtyard_1_wave_3" );

	spawners = getentarray( "enemy_courtyard_1_wave_3", "script_noteworthy" );

	if(spawners.size > 0)
 	{
		maps\_spawner::flood_spawner_scripted( spawners );
	}
	
	flag_wait( "flag_courtyard_1_wave_4" );

	thread courtyard_1_wave_4();
	
	flag_wait( "flag_courtyard_1_kill_spawners" );
	
	spawners_wave_3 = ["enemy_courtyard_1_wave_3"];
	delete_spawners(spawners_wave_3);
 
	flag_wait( "flag_courtyard_1_wave_5" );

	spawners = getentarray( "enemy_courtyard_1_wave_5", "script_noteworthy" );
	foreach( spawner in spawners )
	{
		spawner spawn_ai(true);
	}
}

courtyard_1_wave_4()
{
	spawners_wave_2 = ["enemy_courtyard_1_wave_2"];
	delete_spawners(spawners_wave_2);
	
	spawners = getentarray( "enemy_courtyard_1_wave_4", "script_noteworthy" ); 
	foreach( spawner in spawners )
	{
		spawner spawn_ai(true);
	}
 	
 	waitframe();
 	
 	spawn_metrics_waittill_count_reaches(5, ["enemy_courtyard_1_wave_1", "enemy_courtyard_1_rpg", "enemy_courtyard_1_wave_2", "enemy_courtyard_1_wave_3", "enemy_courtyard_1_wave_4"], 1);
 
 	volume = GetEnt( "info_v_enemy_courtyard_01_stairs", "targetname" );

	foreach(guy in GetAIArray("axis"))
	{
		guy cleargoalvolume();
		guy SetGoalVolumeAuto( volume );
	}
 
 	waitframe();
 	
	spawn_metrics_waittill_count_reaches(3, ["enemy_courtyard_1_wave_1", "enemy_courtyard_1_rpg", "enemy_courtyard_1_wave_2", "enemy_courtyard_1_wave_3", "enemy_courtyard_1_wave_4"], 1);
	
	triggers = GetEntArray( "trig_color_courtyard_1", "targetname" );
	foreach(trigger in triggers)
	{
		if(IsDefined(trigger))
		{
			trigger trigger_off();
		}
	}
 
	volume = GetEnt( "info_v_enemy_courtyard_01_retreat", "targetname" );

	foreach(guy in GetAIArray("axis"))
	{
		guy cleargoalvolume();
		guy SetGoalVolumeAuto( volume );
	}
	
	wait 2;
	path_squad_with_trigger( "trig_color_courtyard_1_end" );
}

friendlies_keep_player_distance_on()
{
	flag_wait( "flag_tank_battalion_side_alley_01" );
	
	level.hero_lone_star	thread ally_keep_player_distance(39 * 6, .8, 1.2, .25);
	level.hero_reno			thread ally_keep_player_distance(39 * 6, .8, 1.2, .25);
	level.hero_frenchie		thread ally_keep_player_distance(39 * 6, .8, 1.2, .25);
	level.hero_redshirt		thread ally_keep_player_distance(39 * 6, .8, 1.2, .25);
}	

tanks_side_alley_01()
{
	self endon("flag_stop_tank_battalion_side_alley_01");

	flag_wait( "flag_tank_battalion_side_alley_01" );

	for(i = 0; i < 20 && !flag("flag_tanks_side_alley_aggro"); i++)
	{
		tanks = spawn_vehicles_from_targetname_and_drive("tank_battalion_side_alley_01");
		foreach(tank in tanks)
		{
			tank thread tank_side_alley_01_think();
			tank thread tank_side_alley_01_death_notify();
		}
		aud_send_msg("courtyard_tanks", tanks);
		wait 8;
	}
}

tank_side_alley_01_death_notify()
{
	self waittill("death");
	
	// this happens if tank is deleted because he reached the end of the path
	if(!IsDefined(self)) return;
	
	flag_set("flag_tanks_side_alley_aggro");
}

tank_side_alley_01_think()
{
	self endon("death");
	flag_wait("flag_tanks_side_alley_aggro");
	
	self Vehicle_SetSpeed(0, 15, 15);
	self vehicle_unload();
	
	// todo: something to make them fire at the player
}

player_enters_yoga_room()
{
	flag_wait( "flag_player_enters_yoga_room" );
	
	aud_send_msg("mus_courtyard1_crossed");
}
	
spawn_civ_corpses_ac_alley()
{
	flag_wait( "flag_spawn_corpses_ac_alley" );
	thread spawn_corpses("dead_civ_ac_alley");	
}
		
ac130_moment()
{
	array_spawn_function_noteworthy("enemy_ai_initial_ac_moment", ::ac_moment_enemy_think);
	array_spawn_function_noteworthy("enemy_ai_initial_ac_moment_gaz", ::ac_moment_enemy_think);
	
	thread ac_alley_hood_slide_block();
	thread ac_alley_ai_blocker();
	
	spawners = getentarray( "enemy_ai_initial_ac_moment", "script_noteworthy" );
	if(spawners.size > 0)
 	{
		maps\_spawner::flood_spawner_scripted( spawners );
	}
	
	thread ac130_moment_position_friendlies();
	
	spawn_vehicles_from_targetname_and_drive( "enemy_convoy_ac_moment_tanks" );

	flag_wait( "flag_ac130_moment_dialogue" );

	gazs = spawn_vehicles_from_targetname_and_drive( "enemy_ac_moment_uaz" );
	foreach(gaz in gazs)
	{
		if(IsDefined(gaz))
		{
			foreach(ai in GetAIArray("axis"))
			{
				if(ai animscripts\utility::AIHasWeapon("rpg"))
				{
					Missile_CreateRepulsorEnt( gaz, 5000, 1000, ai);
				}
			}
		}
	}
	
	wait 10.0;  // however long the previous dialog takes

	level.player maps\_air_support_strobe::enable_strobes_for_player();

	level.player thread show_air_support_hint();
	
	flag_set("flag_dialogue_ac130_player_has_strobe");

	add_wait(::wait_for_strobe_hit);
	add_wait(::flag_wait, "flag_ac130_moment_ran_past" );
	do_wait_any();
	
	// stop the kill line if any waiting to play, the dialogue
	//   has a wait in it so it can be endon
	level notify( "stop_air_support_strobe_kill_dialogue" );
	thread ac130_moment_complete_enable_color();

	// stop the spawners, say "nice shooting"
	// note: this flag will cause guys to move on to the next volume
	flag_set("flag_dialogue_ac130_player_killed_targets");

	foreach(spawner in spawners)
	{
		if(IsDefined(spawner))
		{
			spawner Delete();
		}
	}
}

ac_alley_ai_blocker()
{
	flag_wait( "flag_ac_alley_vehicle_movement_complete" );
	blockers = GetEntArray( "blocker_ac130_alley", "targetname" );
	foreach(blocker in blockers)
	{
		if(IsDefined(blocker))
		{
			blocker ConnectPaths();
			blocker Delete();
		}
	}
}

ac_alley_hood_slide_block()
{
	blocker = getent( "blocker_hood_slide_ac_alley", "targetname" );
	blocker ConnectPaths();
	
	flag_wait( "flag_ac_alley_hood_slide_block" );
	
	/#
	debug_print("hood_slide_began");
	#/
	
	blocker DisconnectPaths();
}
	
ac_moment_enemy_think()
{
	self endon("death");
	
	volume_retreat_test = getent( "info_v_enemy_ac130_moment_retreat", "targetname" );
	volume_retreat_target = getent( "info_v_enemy_ac130_moment_fall_back", "targetname" );
	volume_main = GetEnt( "info_v_enemy_courtyard_02_main", "targetname" );
	volume_front = GetEnt( "info_v_enemy_courtyard_02_front", "targetname" );
	volume_bar = GetEnt( "info_v_enemy_courtyard_02_zone_4", "targetname" );
	
	volume_front.guys_defending = 0;
	volume_main.guys_defending = 0;
	
	// this should make maps\_vehicle_aianims::guy_resets_goalpos() return false, thus stopping guy_unload() from clobbering our goalpos()
	self.script_delayed_playerseek = true;
	
	flag_wait("flag_dialogue_ac130_player_killed_targets");
	
	wait(RandomFloatRange(.5, 1.5));
	
	self notify( "stop_going_to_node" );
	
	if(self IsTouching(volume_retreat_test))
	{
		self SetGoalVolumeAuto(volume_retreat_target);
		self.target = volume_retreat_target.targetname;
		self thread kill_when_player_not_looking();
	}
	else
	{
		// various attempts to force these guys not to lollygag in cover
		// toning these down a bit since they're not really all necessary and make the NPCs look silly
		self set_ignoreSuppression(true);
		//self set_forcegoal();
		//self set_ignoreall(true);
		//self delaythread(2.0, ::set_ignoreall, false);
		
		if(volume_front.guys_defending < 3)
		{
			volume_front.guys_defending++;
			
			self SetGoalVolumeAuto(volume_front);
			self.target = volume_front.targetname;
			
			flag_wait("courtyard_2_wave_3");
			
			self SetGoalVolumeAuto(volume_main);
			self.target = volume_main.targetname;
		}
		else if(volume_main.guys_defending < 3)
		{
			volume_main.guys_defending++;
			
			self SetGoalVolumeAuto(volume_main);
			self.target = volume_main.targetname;
		}
		else
		{
			self SetGoalVolumeAuto(volume_bar);
			self.target = volume_bar.targetname;
		}
	}	
}

ac130_moment_position_friendlies()
{
	goal_node_reno = GetNode("node_reno_ac130_moment", "targetname");
	goal_node_lonestar = GetNode("node_lonestar_ac130_moment", "targetname");
	goal_node_frenchie = GetNode("node_frenchie_ac130_moment", "targetname");
	goal_node_redshirt = GetNode("node_redshirt_ac130_moment", "targetname");
			
	level.hero_reno.ignoreme = true;
	level.hero_lone_star.ignoreme = true;
	level.hero_frenchie.ignoreme = true;
	level.hero_redshirt.ignoreme = true;		
			
	level.hero_reno disable_ai_color();
	level.hero_lone_star disable_ai_color();
	level.hero_frenchie disable_ai_color();
	level.hero_redshirt disable_ai_color();

	level.hero_reno goto_node(goal_node_reno, false);
	level.hero_frenchie goto_node(goal_node_frenchie, false);
	level.hero_redshirt goto_node(goal_node_redshirt, false);
	level.hero_lone_star goto_node(goal_node_lonestar, true);
	
	flag_set("flag_ac130_moment_friendlies_in_position");
	
	level.hero_reno.ignoreme = false;
	level.hero_lone_star.ignoreme = false;
	level.hero_frenchie.ignoreme = false;
	level.hero_redshirt.ignoreme = false;
}	
		
ac130_moment_complete_enable_color()
{
	flag_set( "flag_ac130_moment_complete" );
	aud_send_msg("ac130_moment_complete");
	level.hero_redshirt enable_ai_color();
	wait 2;
	
	flag_set( "flag_dialogue_down_the_alley" );
	
	flag_wait("flag_ac130_moment_friendlies_in_position");
	level.hero_frenchie enable_ai_color();
	wait 1;
	level.hero_reno enable_ai_color();
	level.hero_lone_star enable_ai_color();
}		

wait_for_strobe_hit()
{
	
	total_killed = 0;
	while(total_killed < 3)
	{
		level waittill("air_support_strobe_killed", num_killed);
		total_killed += num_killed;
	}	
}

show_air_support_hint()
{
	if(!IsAlive(self)) return;
	self endon( "death" );
	self endon( "stop_air_support_hint" );
	wait 2.0;

	level.player ent_flag_wait( "flag_strobe_ready" );

	self.stop_air_support_hint = false;
	
	// make us always show the how to fire hint, even if we already have.
	level.displayed_strobe_fire_hint = false;
	
	if(!using_strobe())
	{
		timeout = 30;
		self thread stop_air_support_hint_on_notify( timeout );
		display_hint_timeout( "air_support_hint", timeout );
		
		thread air_support_strobe_fire_hint();
	}
}

stop_air_support_hint_on_notify( timeout )
{
	self endon( "death" );
	self endon( "stop_air_support_hint_timeout" );
	
	thread stop_air_support_hint_timeout( timeout );
	
	self waittill( "stop_air_support_hint" );
	self.stop_air_support_hint = true;
}

stop_air_support_hint_timeout( timeout )
{
	self endon( "death" );
	self endon( "stop_air_support_hint" );
	wait timeout;
	self notify( "stop_air_support_hint_timeout" );
}

using_strobe()
{
	return ( level.player.stop_air_support_hint || level.player GetCurrentWeapon() == "air_support_strobe" );
}


air_support_strobe_fire_hint()
{
	level.player endon("death");
		
	level notify("air_support_strobe_fire_hint");
	level endon("air_support_strobe_fire_hint");
	
	level.displayed_strobe_fire_hint = false;
	while(!level.displayed_strobe_fire_hint)
	{
		level.player ent_flag_wait("flag_strobe_ready");

		while(level.player GetCurrentWeapon() != "air_support_strobe")
		{
			waitframe();
		}

		wait 1;

		if(!level.player ent_flag("flag_strobe_ready") || level.player GetCurrentWeapon() != "air_support_strobe")
			continue;
			
		if( level.Console )
		{	
			display_hint_timeout("air_support_fire_hint", 30);
			level.displayed_strobe_fire_hint = true;
		}
		else
		{
			display_hint_timeout("air_support_fire_hint_pc", 30);
			level.displayed_strobe_fire_hint = true;
		}
	}
}

break_air_support_fire_hint()
{
	if(flag("btr_cortyard_killed"))
		return true;

	if(level.player GetCurrentWeapon() != "air_support_strobe")
		return true;

	return false;
}

ai_clean_up_ac130_moment()
{
	cleanup_ai_with_script_noteworthy( "enemy_ai_initial_ac_moment" );
}

courtyard_2_combat()
{

	spawners = getentarray( "enemy_courtyard_2_wave_1", "script_noteworthy" );

 	foreach( spawner in spawners )
	{
		spawner spawn_ai(true);
	}

	flag_wait( "courtyard_2_wave_2" );
	
	thread mi17_courtyard_02();

	spawners = getentarray( "enemy_courtyard_2_wave_2", "script_noteworthy" );
 	foreach( spawner in spawners )
	{
		spawner spawn_ai(true);
	}

	flag_wait( "courtyard_2_wave_3" );
	
	thread spawn_enemy_courtyard_2_wave_3();
	
	flag_set("flag_dialogue_heli_courtyard");
	
	aud_send_msg("mus_cross_courtyard2");
	
	flag_wait( "flag_dialogue_btr_alley" );
	
	
	
	// should match the list in maps\paris_a_vo::air_support_strobe_dialogue()
	noteworthies = [
		  "enemy_courtyard_2_wave_1"
		, "enemy_courtyard_2_wave_2"
		, "enemy_courtyard_2_wave_3"
		, "enemy_courtyard_2_wave_4"
		, "enemy_courtyard_2_brt_crew"
		, "enemy_ai_initial_ac_moment"
		, "enemy_ai_initial_ac_moment_gaz"
		, "enemy_courtyard_2_heli_crew"
		];
	
	spawn_metrics_waittill_count_reaches(8, noteworthies, true);
	
	spawners = getentarray( "enemy_courtyard_2_wave_4", "script_noteworthy" );
	if(spawners.size > 0)
 	{
		maps\_spawner::flood_spawner_scripted( spawners );
	}
	
	spawn_metrics_waittill_count_reaches(4, noteworthies, true);
	delete_spawners(noteworthies);
	
	spawn_metrics_waittill_count_reaches(1, noteworthies, true);
	array_thread(GetAIArray("axis"), ::kill_when_player_not_looking);
	
	flag_wait( "flag_btr_approaching" );
	
	// also wait for the btr to die
	flag_wait("btr_cortyard_killed");

	// all guys are dead now
	flag_set("flag_dialogue_courtyard_2_clear");
	flag_set("flag_courtyard_2_combat_finished");
	aud_send_msg("courtyard_2_combat_finished");
	
	battlechatter_off( "allies" );
	
	level.player maps\_air_support_strobe::disable_strobes_for_player();
}

// todo: does anything like this exist?
kill_when_player_not_looking()
{
	self endon("death");
	for(;; wait 1)
	{
		if(!player_looking_at(self.origin))
		{
			self bloody_death();
			break;	
		}	
	}	
}

spawn_enemy_courtyard_2_wave_3()
{
//	flag_wait( "flag_btr_approaching" );
	
	spawners = getentarray( "enemy_courtyard_2_wave_3", "script_noteworthy" );
 	foreach( spawner in spawners )
	{
		spawner spawn_ai(true);
	}	
}

mi17_courtyard_02()
{
	mi17_ambient = spawn_vehicles_from_targetname_and_drive ("mi17_courtyard_ambient");
	mi17 = spawn_vehicle_from_targetname_and_drive ("mi17_courtyard_02");
	
	/#
	iprintln( "mi17_spawned" ); 
	#/
		
	aud_send_msg("mi17_courtyard_02_start", mi17);
	
	mi17 waittill("death", attacker, type, weapon);
	
	if(IsDefined(weapon) && weapon == level.air_support_weapon)
	{
		level.player thread player_giveachievement_wrapper("DANGER_CLOSE");
	}	
}

btr_courtyard()
{
	flag_wait_any( "flag_obj_btr_courtyard", "flag_dialogue_heli_unloading", "flag_mi17_courtyard_02_dead" );
	
	wait 2;
	
	thread gaz_crash_site_back_alley();
	
	level.btr_courtyard = spawn_vehicle_from_targetname_and_drive( "btr_courtyard" );
	level.btr_courtyard thread brt_god_until_safe_place();
	level.btr_courtyard ent_flag_init( "btr_unloading" );
	level.btr_courtyard.dontunloadonend = true;
	
	// set badplace on vehicle, kill if it is ever changed to be running,
	//   and start the thread
	level.btr_courtyard.script_badplace = true;
	level.btr_courtyard notify( "kill_badplace_forever" );
	level.btr_courtyard thread vehicle_badplace();
	level.btr_courtyard thread btr_monitor_damage();
	
	level.btr_courtyard thread btr_move_think();
	level.btr_courtyard thread btr_turret_think();
	//play extra death fx when btr is destroyed
	level.btr_courtyard thread maps\paris_a_fx::fx_btr_deathquake();
	
	aud_send_msg("aud_btr_courtyard_start", level.btr_courtyard);
	
	delaythread(3.0, ::flag_set, "flag_dialogue_btr_alley");
	
	level.player delaythread(9.0, ::show_air_support_hint);
	
	if( IsAlive( level.btr_courtyard ) )
		level.btr_courtyard waittill("death");
	
	maps\_spawner::kill_spawnerNum( 600 );

	flag_set( "btr_cortyard_killed" );
	
	level.player notify ( "stop_air_support_hint" );
	
	aud_send_msg("mus_btr_destroyed");
}

brt_god_until_safe_place()
{
	self godon();
	/#
	debug_print( "brt god on" );
	#/
	flag_wait( "flag_btr_godoff" );
	self godoff();
	
	blocker = getent("blocker_btr_alley", "targetname");
	if(IsDefined(blocker)) 
	{
		blocker ConnectPaths();
		blocker delete();
	}	
	
	/#
	debug_print( "brt god off" );
	#/
	level.btr_courtyard thread btr_unload_on_strobe();
}	

btr_monitor_damage()
{
	self waittill( "death", attacker, type, weapon );
	if(IsDefined(weapon) && IsSubStr(weapon, "rpg"))
	{
		flag_set( "flag_dialogue_destroyed_btr_with_rpg" );
	}
}
	
btr_move_think()
{
	self endon( "death" );
	self endon( "kill_btr_move_think" );
	
	self.path_map = [];
	self.path_map[ "forward" ][ "back" ] = "btr_path_forward_to_back";
	self.path_map[ "back" ][ "forward" ] = "btr_path_back_to_forward";
	self.path_map[ "back" ][ "left" ] = "btr_path_back_to_left";
	self.path_map[ "left" ][ "back" ] = "btr_path_left_to_back";
	self.path_map[ "left" ][ "right" ] = "btr_path_left_to_right";
	self.path_map[ "right" ][ "left" ] = "btr_path_right_to_left";
	
	current_location = "forward";
	
	// keep track of last path taken from this location to not ping-pong.
	//   artificially fill so first time it always goes back and then to the left 
	//   and then to the right
	self.last_path_map = [];
	self.last_path_map[ "back" ] = "forward";
	self.last_path_map[ "left" ] = "back";
	
	self.first_guys_unloaded = false;
	
	while ( true )
	{
		// wait until current path is done
		self waittill( "reached_dynamic_path_end" );
		self.script_badplace = false;
		
		if ( !self.first_guys_unloaded )
		{
			// first time it's stopped, unload 2 guys
			wait 1;
			self.first_guys_unloaded = true;
			self thread btr_unload_group( "two_riders" );
		}
		
		// think about what u want to do
		new_location = self btr_choose_new_location( current_location );
		if ( new_location == "none" )
		{
			return;
		}
		
		// start a new path
		self.script_badplace = true;
		wait 0.5;
		
		self.last_path_map[ current_location ] = new_location;
		new_path_node = self.path_map[ current_location ][ new_location ];
		new_path = GetVehicleNode( new_path_node, "targetname" );
		self StartPath( new_path );
		self thread vehicle_paths( new_path );
		current_location = new_location;
	}
}

btr_choose_new_location( current_location )
{
	min_wait_time = 2.5;
	max_wait_time = 8;
	current_wait_time = 0;
	
	wait min_wait_time;
	current_wait_time += min_wait_time;
	while ( true )
	{
		// check to see if u still have a clear shot at the player.
		//   should this check against the current target instead?
		wait_check_time = 0.5;
		wait wait_check_time;
		current_wait_time += wait_check_time;
		
		turret_fire_pos = self.mgturret[0] GetTagOrigin( "tag_flash" );
		player_target_pos = level.player GetEye();
		can_fire = SightTracePassed( turret_fire_pos, player_target_pos, false, self.mgturret[0] );
		
		// if you have a clear shot at the player and you have not exceeded the max wait time, stay in place
		if ( can_fire && current_wait_time < max_wait_time )
			continue;
		
		// figure out a new path to take
		last_path_taken = undefined;
		if ( IsDefined( self.last_path_map ) && IsDefined( self.last_path_map[ current_location ] ) )
		{
			// see if you have a last path from this location
			last_path_taken = self.last_path_map[ current_location ];
		}
		
		dest_location_array = self.path_map[ current_location ];
		dest_locations = GetArrayKeys( dest_location_array );
		if ( dest_locations.size == 1 )
		{
			// if only one possible destination, return it
			return dest_locations[0];
		}
		
		// pick a random destination, and then iterate until you find one
		//   that wasn't used last
		base_location_index = RandomIntRange( 0, dest_locations.size - 1 );
		for ( i = 0; i < dest_locations.size; i++ )
		{
			location_index = ( base_location_index + i ) % dest_locations.size;
			dest_location = dest_locations[ location_index ];
			
			if ( IsDefined( last_path_taken ) && dest_location == last_path_taken )
			{
				continue;
			}
			else
			{
				return dest_location;
			}
		}
		
		return "none";
	}
}

btr_turret_think()
{
	self endon("death");
	self endon( "kill_btr_turret_think" );
	
	self thread vehicle_turret_scan_on();
	
	while ( true )
	{
		wait RandomFloatRange(.3, .8);
		
		target = self btr_get_target();
		if(IsDefined(target))
		{
			self btr_fire_at_target( target );
			wait .3;
		}
	}
}

btr_fire_at_target( target )
{
	target endon("death");
	
	self SetTurretTargetEnt(target, (0, 0, 32));
	
	if ( CoinToss() )
	{
		// fire small turret
		if(IsDefined(self.mgturret))
		{
			foreach(turret in self.mgturret)
			{
				if(IsDefined(turret))
				{
					turret SetTurretTeam("axis");
					turret SetMode("manual");
					turret SetTargetEntity(target);
					turret StartFiring();
				}
			}
		}
		
		wait RandomFloatRange( 3, 5 );
		
		if(IsDefined(self.mgturret))
		{
			foreach(turret in self.mgturret)
			{
				if(IsDefined(turret))
				{
					turret ClearTargetEntity();
					turret StopFiring();
				}
			}
		}
	}
	else
	{
		// fire big gun
		for ( i = 0; i < RandomIntRange( 1, 3 ); i++ )
		{
			self burst_fire_weapon();
			wait 0.5;
		}
	}
}

burst_fire_weapon()
{
	for ( i = 0; i < RandomIntRange( 2,4 ); i++ )
	{
		self FireWeapon();
		wait 0.2;
	}
}

btr_get_target()
{
	player_extra_chance = 4;
	
	targets = GetAIArray("allies");
	for(i = 0; i < player_extra_chance; i++)
		targets[targets.size] = level.player;
		
	return random(targets);
}

btr_unload_on_strobe()
{
	self endon( "death" );
	
	while ( true )
	{
		level waittill( "air_support_strobe_popped", strobe );
		wait 1;
		
		if ( IsDefined( self.rollingdeath ) )
		{
			self waittill( "deathrolloff" );
		}
					
		if(IsDefined(strobe) && IsDefined(strobe.origin) && Distance(strobe.origin, self.origin) < 25 * 12)
		{
			// unload btr
			self notify( "kill_btr_move_think" );
			self notify( "kill_btr_turret_think" );
			self Vehicle_SetSpeed( 0, 20, 20 );
			
			if ( self.first_guys_unloaded )
			{
				self thread btr_unload_group( "driver_and_rider" );
			}
			else
			{
				self thread btr_unload_group();
			}
		}
	}
}

btr_unload_group( group_name )
{
	self endon( "death" );
	
	self ent_flag_waitopen( "btr_unloading" );
	if ( IsDefined( group_name ) )
	{
		self thread vehicle_unload( group_name );
	}
	else
	{
		self thread vehicle_unload();
	}
	
	self ent_flag_set( "btr_unloading" );
	// need to wait until the btr unload animation finishes (better way?)
	//   the "vehicle_anim_flag" doesn't work since the anim gets cleared before it notifies.
	wait 5.4;
	self ent_flag_clear( "btr_unloading" );
}

move_manhole()
{
	wait 3;
	// everybody waits in their defined locations	
	foreach(guy in [level.hero_frenchie, level.hero_redshirt, level.hero_lone_star, level.hero_reno])
	{
		guy disable_ai_color();
		// so they don't get stuck by any suppressing NPCs, in the unlikely event they're still alive
		guy set_ignoreall(true);
		guy set_ignoreSuppression(true);
	}
	level.hero_reno      goto_node("node_pre_move_manhole_reno", false);
	level.hero_redshirt  goto_node("node_pre_move_manhole_redshirt", false);
	level.hero_lone_star goto_node("node_pre_move_manhole_lonestar", false);
	thread frenchie_goto_manhole();
	
	thread frenchie_calls_when_near();
		
	guys = [ level.hero_frenchie, level.hero_lone_star ];
	guys_and_manhole = [ level.hero_frenchie, level.hero_lone_star, level.manhole ];	

	flag_wait_all("flag_move_manhole_start", "flag_frenchie_manhole_ready" );
	
	level.manhole_node anim_reach(guys, "delta_pull_movemanhole");
	
	// the _run version exits a bit early so the transitions can be better maybe
	scripted_sequence_recon("move_manhole", true, level.hero_lone_star, 3);
	level.manhole_node anim_single_run(guys_and_manhole, "delta_pull_movemanhole");
	level.hero_frenchie AnimCustom(::finish_descending_ladder);	
	
	level.manhole_node thread anim_loop_solo(level.hero_lone_star, "delta_pull_movemanhole_idle");

	// get lone_star going down the ladder
	// connect paths but don't delete, we still need the player not to fall through
	level.manhole_blocker ConnectPaths();
	//level.hero_reno goto_node("node_sewer_entrance_reno_goal", false);

	// don't let the player hit the trigger until lone_star's almost finished descending
	// hmm, if reno was late to the party this might get screwed up... though eventually we'll need
	// to animate him anyway.
	wait 1.5;

	//thread add_dialogue_line( "Sabre", "Get in here, Westbrook!" );

	trigger = getent_safe("flag_player_manhole", "script_noteworthy");
	// Press and hold ^3&&1^7 to climb onto the ladder.
	trigger SetHintString(&"PARIS_USE_MANHOLE");
	
	flag_set( "flag_player_manhole_ready" );
	
	// wait for the player to hit X
	flag_clear("flag_player_manhole");
	flag_wait("flag_player_manhole");
	trigger Delete();

	hud_off();
	
	player_rig = create_player_rig(level.manhole_node, undefined, "player_manhole");
	duration = .5;
	level.player player_control_off(true);
	level.player PlayerLinkToBlend(player_rig, "tag_player", duration, duration/3, duration/3);
	wait duration;
	player_rig Show();	
	level.manhole_node anim_single_solo(player_rig, "player_manhole");
	
	maps\_loadout::SavePlayerWeaponStatePersistent("paris", true);
	SetDvar("paris_transition_movie", "1");
	nextmission();
}

frenchie_goto_manhole()
{
	level.hero_frenchie  goto_node("struct_pre_move_manhole_frenchie", true);
	flag_set( "flag_frenchie_manhole_ready" );
	/#
	debug_print( "Sabre ready!" );
	#/
}	

frenchie_calls_when_near()
{
	origin = GetStruct("struct_pre_move_manhole_frenchie", "script_noteworthy").origin;
	
	while(Distance(origin, level.hero_frenchie.origin) > 120)
	{
		wait 1;
	}
	
	flag_set("flag_dialogue_manhole_prompt");
		
}

#using_animtree( "generic_human" );
finish_descending_ladder()
{
	self.allowpain = false;
	
	// this is all adapted from ladder_down.gsc
	
	self AnimMode( "none" );
	
	// the -64 is so we don't hit the dynamic blocker at the top of the manhole shaft.
	endPos = GetGroundPosition(self.origin, 8, 512, -64);
	    
	climbAnim = %paris_delta_down_ladder_loop;
	self setFlaggedAnimKnoballRestart( "climbanim", climbAnim, %body, 1, .2, 1 );

	cycleDelta = GetMoveDelta( climbAnim, 0, 1 );
	climbRate = cycleDelta[ 2 ] /  getanimlength( climbAnim );
	climbingTime = ( endPos[ 2 ] - self.origin[ 2 ] ) / climbRate;

	AssertEx(climbingTime > 0, "climbing time was negative, getgroundposition didn't work right");
	if(climbingTime < 0) climbingTime = 1.5;

	self thread animscripts\notetracks::DoNoteTracksForTime( climbingTime, "climbanim" );

	// would like to set noclip so we aren't interefered with by the manhole cover blocker, but
	// there's no way to do that outside of a traverse.  Instead, do this linky stuff.
		
	elevator = self spawn_tag_origin();
	self LinkTo(elevator, "tag_origin", (0, 0, 0), (0, 0, 0));
	elevator MoveTo(endPos, climbingTime);
	
	wait(climbingTime);
	
	self UnLink();
	elevator Delete();
	
	self AnimMode( "gravity" );

	self notify("finished_descending_ladder");
	
	self delete();
	//self goto_node("node_sewer_entrance_frenchie_goal", false);
}

gaz_crash_site_back_alley()
{
	flag_wait( "flag_gaz_back_alley" );
	spawn_vehicles_from_targetname( "gaz_crash_site_back_alley" );
}	

enemies_ignore_player_until_shot_or_hot()
{
	CreateThreatBiasGroup("rooftop_allies");
	level.player SetThreatBiasGroup("rooftop_allies");
	level.hero_lone_star 	SetThreatBiasGroup("rooftop_allies");
	level.hero_reno 		SetThreatBiasGroup("rooftop_allies");
	
	SetIgnoreMeGroup("rooftop_allies", "axis");
	SetIgnoreMeGroup("axis", "rooftop_allies");

	add_wait(::waittill_enemy_damaged_by_player);
	add_wait(::flag_wait, "flag_bookstore_spray_moment" );
	do_wait_any();
	
	level.player SetThreatBiasGroup("allies");
	level.hero_lone_star SetThreatBiasGroup("allies");
	level.hero_reno SetThreatBiasGroup("allies");		
}

waittill_enemy_damaged_by_player()
{
	foreach(guy in GetAIArray("axis"))
	{
		guy thread _notify_when_damaged_by_player();	
	}
	
	add_global_spawn_function("axis", ::_notify_when_damaged_by_player);
	
	level waittill("damaged_by_player");
	
	remove_global_spawn_function("axis", ::_notify_when_damaged_by_player);
}

_notify_when_damaged_by_player()
{
	level endon("damaged_by_player");
	
	for(;;)
	{
		self waittill("damage", amount, attacker);
		if(attacker == level.player)
			break;	
	}
	level notify("damaged_by_player");
}

player_shimmy()
{
	level endon("player_shimmy_stop");
	level.player endon( "death" );
	
	state = SpawnStruct();

	// tunable params

	base_speed = 45; // inches per second
	accel_time = .5;  // how long it takes to reach max speed
	time_to_fall = 0.5; // how long you must try to walk off the ledge before you fall off
	// extra space added to each end so we aren't right on the edge of coming off when we attach
	// could probably lerp thickness between points if necessary in the geo
	link_duration = 1;  // time to link at the start
	unlink_duration = 1; // time to unlink when walking off the end
	jump_duration = .5;  // time to unlink when falling off the left side
	thickness = 16;
	angle_smoothing = .7;
	
	speed_amplitude = 24;
	speed_angular_frequency = 360 / 1;  // degrees per second of phase (360 / footstep time)
	footstep_phase = 90; // degrees, where in the footstep we play effects
	
	// when you get on, advance this far past the first origin.  Shouldn't be farther than the distance to the second origin.
	start_distance = 48;
	
	// when you get off, we put you this far past the end of the last segment.
	end_distance = 24;
	
	// when you jum off, we move you this far out
	jump_distance = 24;
	
	// view constraints while you're linked
	right_arc = 40;
	left_arc = 40;
	top_arc = 20;
	bottom_arc = 5;
	
	// this is an engine constant, and what would be returned by level.player GetPlayerViewHeight(), assuming the player is standing.
	// we use a constant in case he's not standing when we start.
	player_view_height = 60;
	
	state.min_left = thickness * -0.5;
	state.max_left = thickness *  0.5;
	dt = 0.05;
	
	// arrays describing the path
	state.points = [];
	state.angles = [];
	state.to_next = [];
	state.dir_to_next = [];
	state.dist_to_next = [];
	state.left_dir = [];
	
	// read in all the points on the path
	struct = getstruct("struct_player_shimmy_start", "script_noteworthy");
	i = 0;
	while(IsDefined(struct))
	{
		Assert(IsDefined(struct.angles), "Shimmy structs all need angles");
		
		state.points[i] = struct.origin;
		state.angles[i] = struct.angles;		
				
		if(i > 0)
		{
			state.to_next[i - 1] = state.points[i] - state.points[i - 1];
			state.dir_to_next[i - 1] = VectorNormalize(state.to_next[i - 1]);
			state.dist_to_next[i - 1] = Length(state.to_next[i - 1]);
			state.left_dir[i - 1] = VectorNormalize(VectorCross((0, 0, 1), state.dir_to_next[i - 1]));
			Assert(state.dist_to_next[i - 1] != 0);
			Assert(state.left_dir[i - 1] != (0, 0, 0));
		}
		
		if(IsDefined(struct.script_angles))
		{
			if(i == 0)
				state.unlink_beginning_angles = struct.script_angles;
			else
				state.unlink_ending_angles = struct.script_angles;
		}
		
		if(IsDefined(struct.target))
		{
			struct = GetStruct(struct.target, "targetname");
			i++;
		}
		else
		{
			break;	
		}
	}
	Assert(state.points.size >= 2, "It takes two points to shimmy.");
	// we add some extra distance to the last segment to provide some hysteresis when getting on at the end.
	state.dist_to_next[state.dist_to_next.size - 1] += .125;
	
	while(true)
	{
		
		// wait for player to hit first or last point
		for(;; waitframe())
		{
			// I had hoped to avoid this for performance reasons, but crazy geo sometimes lets them skip the first segments,
			// so let's test every segment instead of just the first two to be safe.
			// Seems to cost <1ms of server time, and there's no fighting here, so it should be ok.
			/*
			if(player_shimmy_in_segment(state, 0) || player_shimmy_in_segment(state, state.points.size - 2))
				break;
			*/
			
			in_segment = false;
			for(i = 0; i < state.points.size - 1; i++)
			{
				if(player_shimmy_in_segment(state, i))
				{
					in_segment = true;
					break;					
				}
			}
			if(in_segment)
				break;
		}

		player_shimmy_origin_to_state(state, level.player.origin);
		Assert(IsDefined(state.segment_index));
		if(!IsDefined(state.segment_index))
			continue;
		
		level.player player_control_off(false);
		aud_send_msg("mus_ledge_walk");
		// NOTE: this flag is being used above for logic stuff, don't move it.
		flag_set("flag_dialogue_watch_your_step");
		
		// do the cheating to start you somewhat into the sequence
		
		if(state.segment_index == 0)
		{
			state.segment_forward += start_distance;
		}
		else
		{
			state.segment_forward -= start_distance;
		}
		state.segment_left = clamp(state.segment_left, state.min_left, state.max_left);
		
		struct = player_shimmy_state_to_point(state);
		
		// these are updated in the main loop
		logical_origin = struct.origin;  // needed because the real player_link_ent.origin needs to be tweaked based on pitch.
		smooth_angles = struct.angles;
		
		using_initial_player_angles = true;
		initial_player_angles = level.player.angles;
		
		player_link_ent = spawn_tag_origin();
		
		lerp_vector = (struct.origin + (0, 0, player_view_height)) - (level.player GetEye()); 
		
		lerp_params = compute_lerp_params(
			link_duration,
			VectorDot(level.player GetVelocity(), VectorNormalize(lerp_vector)),
			Length(lerp_vector));
		
		level.player lerp_player_camera(
			struct.origin + (0, 0, player_view_height), struct.angles,
			link_duration, lerp_params.accel_time, lerp_params.decel_time, link_duration * .4, link_duration * .4,
			player_link_ent,
			right_arc, left_arc, top_arc, bottom_arc);
		
		// main loop
		can_fall_yet = false;
		fall_duration = 0;
		moving_time = 0;
		next_footstep_time = footstep_phase / speed_angular_frequency;
		state.jumped = false;
		while(true)
		{			
			player_shimmy_origin_to_state(state, logical_origin);
			
			// if we fell off the end
			if(!IsDefined(state.segment_index))
				break;
			
			state.last_segment_index = state.segment_index;
			
			stick = level.player GetNormalizedMovement();
					
			// switch to right-handed coordinates
			stick = (stick[0], stick[1] * -1, 0);
			
			// forget the initial orientation when you get below .25 forward
			if(stick[0] < .25)
			{				
				using_initial_player_angles = false;
			}
			// don't let you fall until you stop moving
			if(Length(stick) < .1) 
			{				
				can_fall_yet = true;
			}
						
			if(using_initial_player_angles)
				player_to_global_angles = initial_player_angles;
			else
				player_to_global_angles = level.player.angles;
				
			stick_player_angles = VectorToAngles(stick);
			stick_global_angles = flat_angle(CombineAngles(player_to_global_angles, stick_player_angles));
			stick_global = AnglesToForward(stick_global_angles) * Length(stick);
			
			stick_local_forward = VectorDot(stick_global, state.dir_to_next[state.segment_index]);
			stick_local_left = VectorDot(stick_global, state.left_dir[state.segment_index]);
			
			// sine-wave speed to simulate footsteps
			if(abs(stick_local_forward) > .1)
			{
				moving_time += dt;
			}
			else
			{
				moving_time = 0;
				next_footstep_time = footstep_phase / speed_angular_frequency;
			}
			
			cur_speed = linear_map_clamp(moving_time, 0, accel_time, 0, base_speed) + speed_amplitude * Sin(moving_time * speed_angular_frequency);
			
			if(moving_time > next_footstep_time)
			{
				fx_origin = state.points[state.segment_index] + state.dir_to_next[state.segment_index] * state.segment_forward;
				player_shimmy_foostep_effect_placeholder(fx_origin, level.player.angles);
				level.player playrumbleonentity( "viewmodel_small" );
				
				next_footstep_time += 360.0 / speed_angular_frequency;
			}
				
			// don't clip through NPCs
			// note: only works for NPCs ahead of us.
			if(stick_local_forward > 0)
			{
				closest_npc = shimmy_moment_get_closest_npc(logical_origin);
				if(IsDefined(closest_npc))
				{
					to_npc = closest_npc.origin - logical_origin;
					if(VectorDot(to_npc, state.dir_to_next[state.segment_index]) > 0)
					{
						dist = Length(to_npc);
						stick_local_forward = linear_map_clamp(dist, 32, 64, 0, stick_local_forward);
					}
				}
			}				
				
			// advance our position
			state.segment_forward += stick_local_forward * cur_speed * dt;
			state.segment_left += stick_local_left * cur_speed * dt;
			
			// allow falling off on the left side of the path
			if(can_fall_yet && state.segment_left > state.max_left && stick[0] > .5)
			{
				fall_duration += dt;
			}
			else
			{
				fall_duration = 0;
			}
			
			if(fall_duration > time_to_fall)
			{
				state.jumped = true;
				break;	
			}				
						
			state.segment_left = clamp(state.segment_left, state.min_left, state.max_left);
	
			struct = player_shimmy_state_to_point(state);
			

			// time-based smoothing to cover discontinuties in our parametric position when the path goes around a bend
			// can't just use RotateTo because it uses quat slerp which can result in a roll angle.
			
			smooth_angles = euler_lerp(struct.angles, smooth_angles, angle_smoothing);
			
			player_link_ent.angles = smooth_angles;
			
			// want to do player_link_ent.origin = struct.origin, but then when we detach, we'd be facing down.
			// instead we need to set player_link_ent's position to the position such that, when we detach, the player
			// would end up at struct.origin
			
			logical_origin = struct.origin;
			player_link_ent.origin = logical_origin + (0, 0, player_view_height) - AnglesToUp(smooth_angles) * player_view_height;
			
			/#
			//thread draw_line_for_time(player_link_ent.origin + 60 * AnglesToUp(player_link_ent.angles), player_link_ent.origin + 60 * AnglesToUp(player_link_ent.angles) + AnglesToForward(struct.angles) * 32, 1, 0, 0, 10);
			//thread draw_line_for_time(logical_origin, state.points[state.segment_index] + state.dir_to_next[state.segment_index] * state.segment_forward, 0, 1, 0, 10);
			#/
			
			wait(dt);			
		}
		
		// we're done, lerp out smoothly.
		if(IsDefined(state.last_segment_index))
		{
			if(state.jumped)
			{
				state.segment_index = state.last_segment_index;
				state.segment_left += jump_distance;
				
				ending_origin = player_shimmy_state_to_point(state).origin;
				ending_forward = AnglesToForward(level.player GetPlayerAngles());
				
				level.player EnableWeapons();
			
				accel_time = jump_duration * .2;
				decel_time = jump_duration * .5;
				level.player LerpViewAngleClamp(jump_duration, accel_time, decel_time, 0, 0, 0, 0);
				player_link_ent RotateTo(VectorToAngles(ending_forward), jump_duration, accel_time, decel_time);
				player_link_ent MoveTo(ending_origin, jump_duration, accel_time, decel_time);
				wait(jump_duration);
			}
			else
			{
				// cheat ourselves forward so we move during the blend (note this involes out of bounds positions on the segment)				
				state.segment_index = state.last_segment_index;
				ending_angles = undefined;
				if(state.segment_index == 0)
				{
					state.segment_forward -= end_distance;
					ending_angles = state.unlink_beginning_angles;
				}
				else
				{
					state.segment_forward += end_distance;
					ending_angles = state.unlink_ending_angles;
				}
				ending_origin = player_shimmy_state_to_point(state).origin;
							
				if(!IsDefined(ending_angles))
				{
					if(state.last_segment_index == 0)
						ending_angles = VectorToAngles(state.dir_to_next[state.last_segment_index] * -1);
					else
						ending_angles = VectorToAngles(state.dir_to_next[state.last_segment_index]);
				}
				
				// tweak the ending angles so we still end up the right direction if we were looking left or right
				view_angles = level.player GetGunAngles();
				yaw_diff = AngleClamp180(view_angles[1] - VectorToAngles(state.left_dir[state.last_segment_index])[1]);
				ending_angles = (ending_angles[0], AngleClamp(ending_angles[1] - yaw_diff), ending_angles[2]);
								
				// cast down to account for irregularities in the ground
				ground_position = GetGroundPosition(ending_origin, 16, 24, 24);
				if(IsDefined(ground_position))
					ending_origin = ground_position;
			
				level.player EnableWeapons();
			
				accel_time = unlink_duration * .2;
				decel_time = unlink_duration * .5;
				level.player LerpViewAngleClamp(unlink_duration, accel_time, decel_time, 180, 180, 90, 90);
				player_link_ent RotateTo(ending_angles, unlink_duration, accel_time, decel_time);
				player_link_ent MoveTo(ending_origin, unlink_duration, accel_time, decel_time);
				wait(unlink_duration);
			}
		}
		
		
		level.player Unlink();
		level.player player_control_on();
		player_link_ent Delete();
		
		// must give the player a chance to move back to his logical_origin before re-evaluating whether to get back on
		waitframe();
		waitframe();
	}
}


lerp_player_camera(target_eye_origin, target_eye_angles, time, linear_accel_time, linear_decel_time, camera_accel_time, camera_decel_time, target_link_ent, right, left, top, bottom)
{
	Assert(IsPlayer(self));
	test = level.player GetPlayerViewHeight();
	player_view_height = 60;  // using GetPlayerViewHeight wouldn't work if we're crouched, which we disallow anyway
	
	player_eye_ent = spawn_tag_origin();
	player_eye_ent.angles = self GetPlayerAngles();
	// not sure why we need to compensate for two frames of velocity, instead of just one, but it seems to work.
	// also, instead of calling GetEye() directly, we compute what it should be if we were standing
	//player_eye_ent.origin = self GetEye() + (self GetVelocity()) * .1;
	player_eye_ent.origin = self.origin + (0, 0, player_view_height) + (self GetVelocity()) * .1;
		
	player_link_ent = spawn_tag_origin();
	player_link_ent LinkTo(player_eye_ent, "tag_origin", (0, 0, -1 * player_view_height), (0, 0, 0));
	
	self PlayerLinkToDelta(player_link_ent, "tag_origin", 1, 0, 0, 0, 0, true);

	player_eye_ent MoveTo(target_eye_origin, time, linear_accel_time, linear_decel_time);
	player_eye_ent RotateTo(target_eye_angles, time, camera_accel_time, camera_decel_time);
		
	wait time;
		
	// we pass in the link ent so we can avoid ever unlinking the player, supressing Unlinked In Solid spam.
	target_link_ent.origin = target_eye_origin + (0, 0, player_view_height) - AnglesToUp(target_eye_angles) * player_view_height;
	target_link_ent.angles = target_eye_angles;	
	
	self PlayerLInkToDelta(target_link_ent, "tag_origin", 1, right, left, top, bottom, true);
	
	player_link_ent Delete();
	player_eye_ent Delete();
}

compute_lerp_params(duration, init_speed, distance)
{
	min_slope_time = duration * .25;
	
	ret = SpawnStruct();
	
	if(distance > 0 && init_speed > 0)
	{
		init_parametric_speed = init_speed / distance;
		
		// to compute maxspeed in the blend, the code does this:
		// maxSpeed = 2.0f / ( ( 2.0f * totalTime ) - totalAccelTime - totalDecelTime );
		// we consider totalAccelTime = 0 and solve for totalDecelTime
		
		totalDecelTime  = (2.0 * duration) - 2.0 / init_parametric_speed;
		
		if(totalDecelTime > min_slope_time)
		{
			if(totalDecelTime <= duration)
			{
				// the good case, where our speeds will match
				ret.accel_time = 0;
				ret.decel_time = totalDecelTime;
			}
			else
			{
				// going too fast, so we will decelerate as much as possible but there will be a discontinuity
				// in this case we could decrease the total duration, but that might make it even more abrupt.
				ret.accel_time = 0;
				ret.decel_time = duration;				
			}
		}
		else
		{
			// going too slow, our deceleration would need to be too steep (or impossible)
			// so we will have to speed up.  figure what our max speed would be with zero accel and min_slope_time decel
			// we could increase the transition time in this case, but it could be unboundedly long so that wouldn't totally solve the problem.
			max_parametric_speed = 2.0 / (( 2.0 * duration) - min_slope_time);
			
			if(init_parametric_speed > max_parametric_speed * 0.5)
			{
				// doing that is better than starting from a dead stop
				ret.accel_time = 0;
				ret.decel_time = min_slope_time;
			}
			else
			{
				// going so slow it's better to pop to stopped than pop to max speed
				ret.accel_time = min_slope_time;
				ret.decel_time = min_slope_time;
			}			
		}
	}
	else
	{
		// totally stopped or no distance to cover, use sensible defaults
		ret.accel_time = min_slope_time;
		ret.decel_time = min_slope_time;
	}
	
	return ret;
}

player_shimmy_in_segment(state, i)
{
	point_to_pos = level.player.origin - state.points[i];
	point_to_pos_parallel = VectorDot(point_to_pos, state.dir_to_next[i]);
	
	fudge = 2.5;
	
	// debug stuff
	/*
	left = VectorNormalize(VectorCross((0, 0, 1), state.dir_to_next[i]));
	corner1 = state.points[i] + left * state.min_left * fudge;
	corner2 = state.points[i] + left * state.max_left * fudge;
	corner3 = state.points[i] + left * state.max_left * fudge + state.dist_to_next[i] * state.dir_to_next[i];
	corner4 = state.points[i] + left * state.min_left * fudge + state.dist_to_next[i] * state.dir_to_next[i];
	Line(corner1, corner2, (1, 0, 0), 1);
	Line(corner2, corner3, (1, 0, 0), 1);
	Line(corner3, corner4, (1, 0, 0), 1);
	Line(corner4, corner1, (1, 0, 0), 1);
	*/
	
	if(point_to_pos_parallel > 0 && point_to_pos_parallel < state.dist_to_next[i])
	{
		left = VectorDot(point_to_pos, state.left_dir[i]);
		
		// make it easier to get on, since we need narrow widths to avoid getting off in geo.
		// only in the direction you can't fall in, so we don't get stuck in a falling loop.
		if(left > state.min_left * fudge && left < state.max_left * fudge)
		{
			return true;
		}
	}
	return false;
}

player_shimmy_origin_to_state(state, pos)
{
	state.segment_index = undefined;
	
	for(i = 0; i < state.points.size - 1; i++)
	{
		point_to_pos = pos - state.points[i];
		
		point_to_pos_parallel = VectorDot(point_to_pos, state.dir_to_next[i]);

		if(point_to_pos_parallel < state.dist_to_next[i])
		{
			state.segment_left = VectorDot(point_to_pos, state.left_dir[i]);
			state.segment_index = i;
			state.segment_forward = point_to_pos_parallel;
			break;
		}				
	}
	
	// -0.125 is to provide some hysterisis 
	if(IsDefined(state.segment_index) && state.segment_index == 0 && state.segment_forward < -0.125)
	{
		state.segment_index = undefined;	
	}
}

player_shimmy_state_to_point(state)
{
	struct = SpawnStruct();
	
	i = state.segment_index;
	struct.origin = state.points[i] + state.dir_to_next[i] * state.segment_forward + state.left_dir[i] * state.segment_left;
	
	// tweak logical_origin for smooth travel around corners
	corner = undefined;
	if(state.segment_forward > state.dist_to_next[state.segment_index] && state.segment_index + 1 < state.dist_to_next.size)
		corner = state.points[state.segment_index + 1];
	if(state.segment_forward < 0 && state.segment_index > 0)
		corner = state.points[state.segment_index];
	
	if(IsDefined(corner))
	{
		corner_to_origin = struct.origin - corner;
		corner_to_origin_dist = Length(corner_to_origin);
		
		clamp_radius = -1 * state.min_left;
		if(state.segment_left > 0)
			clamp_radius = state.max_left;
		
		if(corner_to_origin_dist > clamp_radius)
		{
			corner_to_origin *= (clamp_radius / corner_to_origin_dist);
			struct.origin = corner + corner_to_origin;
		}				
	}
	
	// cubic spline, interval already scaled to [0, 1]	
	t = clamp(state.segment_forward / state.dist_to_next[i], 0, 1);
	pk = angles_clamp_180(state.angles[i]);
	pkp1 = pk;
	pkm1 = pk;
	if(i + 1 < state.angles.size)
		pkp1 = angles_clamp_180(state.angles[i + 1]);
	if(i - 1 > 0)
		pkm1 = angles_clamp_180(state.angles[i - 1]);
	pkp2 = pkp1;
	if(i + 2 < state.angles.size)
		pkp2 = angles_clamp_180(state.angles[i + 2]);

	
	h00 = (1 + 2 * t) * Squared(1 - t);
	h10 = t * Squared(1 - t);
	h01 = Squared(t) * (3 - 2 * t);
	h11 = Squared(t) * (t - 1);
	
	mk = (pkp1 - pkm1) / 2;  // t difference between adjacent points is always 1
	mkp1 = (pkp2 - pk) / 2;
	
	struct.angles = angles_clamp(h00 * pk + h10 * mk + h01 * pkp1 + h11 * mkp1);
	
	// simple linear blending
	//struct.angles = euler_lerp(state.angles[i], state.angles[i + 1], t);
		
	return struct;
}

player_shimmy_foostep_effect_placeholder(fx_origin, fx_angles)
{
	playfx(getfx("ledge_footstep_dust"), fx_origin, AnglesToForward(fx_angles), AnglesToUp(fx_angles) );
	aud_send_msg("start_ledge_footstep");
}

angles_clamp_180(v)
{
	return (AngleClamp180(v[0]), AngleClamp180(v[1]), AngleClamp180(v[2]));
}

angles_clamp(v)
{
	return (AngleClamp(v[0]), AngleClamp(v[1]), AngleClamp(v[2]));
}

trigger_kill_player()
{
	for(;;)
	{
		self waittill("trigger", maybe_player);
		if(IsPlayer(maybe_player) && IsAlive(maybe_player))
		{
			maybe_player Kill();
		}
	}
}

bullet_spray(start_pos, end_pos)
{
	// self is an AI to do the shooting
	Assert(IsAI(self));
	
	if(!IsAlive(self))
		return;
	self endon("death");
	
	total_time = 1.5;
	rounds_per_min = 700;
	
	delay = 60 / rounds_per_min;
	shots = total_time / delay;
	
	noise_amplitude = 39;
	noise_smoothing = .3;
	
	noise = (0, 0, 0);
			
	entity_target = spawn_tag_origin();
	entity_target.origin = start_pos;
	self SetEntityTarget(entity_target);
		
	for(i = 0; i < shots; i++)
	{
		noise = noise * noise_smoothing + randomvector(noise_amplitude * (1 - noise_smoothing));
		
		pos = linear_interpolate(i / shots, start_pos, end_pos) + noise;
		entity_target.origin = pos;
		self SetEntityTarget(entity_target);
		
		MagicBullet(self.weapon, self GetTagOrigin("tag_flash"), pos);
		wait delay;
	}
	
	self ClearEntityTarget();
	entity_target Delete();
}

// returns a new array with the first count elements of the given array
array_trim(array, count)
{
	ret = [];
	for(i = 0; i < array.size && i < count; i++)
	{
		ret[ret.size] = array[i];
	}	
	return ret;
}
