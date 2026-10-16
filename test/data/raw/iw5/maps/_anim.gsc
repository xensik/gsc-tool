#include maps\_utility;
#include common_scripts\utility;
#include animscripts\shared;
#include animscripts\utility;
#include animscripts\face;

CONST_anim_end_time	 = 0.25;

init()
{
	if ( !isDefined( level.scr_notetrack ) )
		level.scr_notetrack = [];
	if ( !isDefined( level.scr_face ) )
		level.scr_face = [];
	if ( !isDefined( level.scr_look ) )
		level.scr_look = [];
	if ( !isDefined( level.scr_animSound ) )
		level.scr_animSound = [];
	if ( !isDefined( level.scr_sound ) )
		level.scr_sound = [];
	if ( !isDefined( level.scr_radio ) )
		level.scr_radio = [];
	if ( !isDefined( level.scr_text ) )
		level.scr_text = [];
	if ( !isDefined( level.scr_anim ) )
		level.scr_anim[ 0 ][ 0 ] = 0;
	if ( !isDefined( level.scr_radio ) )
		level.scr_radio = [];
}

endonRemoveAnimActive( endonString, guyPackets )
{
	self waittill( endonString );
	foreach ( guyPacket in guyPackets )
	{
		guy = guyPacket[ "guy" ];
		if ( !isdefined( guy ) )
			continue;

		guy._animActive--;
		guy._lastAnimTime = GetTime();
		Assert( guy._animactive >= 0 );
	}
}


 /* 
 ============= 
///ScriptDocBegin
"Name: anim_first_frame( <guys> , <scene> , <tag> )"
"Summary: Puts the animating models or AI or vehicles into the first frame of the animated scene. The animation is played relative to the entity that calls the scene"
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <array of things that animate> : An array of AI or vehicles or script_models, mixed or homogenous."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ animname ][ anime ]."
"OptionalArg: <optional tag to attach to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_first_frame( guys, "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
 ============= 
 */ 

anim_first_frame( guys, anime, tag )
{
	array = get_anim_position( tag );
	org = array[ "origin" ];
	angles = array[ "angles" ];
	array_levelthread( guys, ::anim_first_frame_on_guy, anime, org, angles );
}

/* 
============= 
///ScriptDocBegin
"Name: anim_generic_first_frame( <guy> , <scene> , <tag> )"
"Summary: Puts the animating model or AI or vehicle into the first frame of the animated scene. The animation is played relative to the entity that calls the scene"
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <thing that animates> : An AI or vehicle or script_model."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ animname ][ anime ]."
"OptionalArg: <optional tag to attach to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_generic_first_frame( guy, "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
============= 
*/ 

anim_generic_first_frame( guy, anime, tag )
{
	array = get_anim_position( tag );
	org = array[ "origin" ];
	angles = array[ "angles" ];

	thread anim_first_frame_on_guy( guy, anime, org, angles, "generic" );
}


/* 
============= 
///ScriptDocBegin
"Name: anim_generic( <guy>, <scene> , <optional tag to animate relative to> )"
"Summary: Makes an AI play a generic anim. The calling ent notifies itself the name of the animation scene when it completes."
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <thing that will animate> AI, model, or vehicle."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ generic ][ anime ]."
"OptionalArg: <optional tag to animate relative to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_generic( guy, "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
============= 
*/ 

anim_generic( guy, anime, tag )
{
	guys = [];
	guys[ 0 ] = guy;
	anim_single( guys, anime, tag, 0, "generic" );
}

/* 
============= 
///ScriptDocBegin
"Name: anim_generic_gravity( <guy>, <scene> , <optional tag to animate relative to> )"
"Summary: Makes an AI play a generic anim with gravity (so he'll self aline to any floor even if the animation doesnt). The calling ent notifies itself the name of the animation scene when it completes."
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <thing that will animate> AI, model, or vehicle."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ generic ][ anime ]."
"OptionalArg: <optional tag to animate relative to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_generic( guy, "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
============= 
*/ 
anim_generic_gravity( guy, anime, tag )
{
	pain = guy.allowPain;
	guy disable_pain();// anim_custom allows for pain - since 99% of the time this is unwanted behavior - we turn off pain before doing the anim.
	
	self anim_generic_custom_animmode( guy, "gravity", anime, tag );
	
	if( pain )
		guy enable_pain();
}

/* 
============= 
///ScriptDocBegin
"Name: anim_generic_run( <guy>, <scene> , <optional tag to animate relative to> )"
"Summary: Works like anim_generic but makes the anim blend out early so it can go into a run without pausing."
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <thing that will animate> AI, model, or vehicle."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ generic ][ anime ]."
"OptionalArg: <optional tag to animate relative to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_generic( guy, "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
============= 
*/ 

anim_generic_run( guy, anime, tag )
{
	guys = [];
	guys[ 0 ] = guy;
	anim_single( guys, anime, tag, CONST_anim_end_time, "generic" );
}

/* 
============= 
///ScriptDocBegin
"Name: anim_generic_reach( <guy>, <scene> , <optional tag to animate relative to> )"
"Summary: Makes an AI move to the position to start an animation. The calling ent notifies itself the name of the animation scene when it completes."
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <thing that will animate> AI that will move."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ generic ][ anime ]."
"OptionalArg: <optional tag to animate relative to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_reach( guy, "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
============= 
*/ 

anim_generic_reach( guy, anime, tag )
{
	guys = [];
	guys[ 0 ] = guy;
	anim_reach( guys, anime, tag, "generic" );
}

/* 
============= 
///ScriptDocBegin
"Name: anim_generic_reach_and_arrive( <guys>, <scene> , <optional tag to animate relative to> )"
"Summary: Makes an AI move to the position to start an animation, with arrivals. The calling ent notifies itself the name of the animation scene when it completes."
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <thing that will animate> AI that will move."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ generic ][ anime ]."
"OptionalArg: <optional tag to animate relative to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_reach_and_arrive( guy, "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
============= 
*/ 

anim_generic_reach_and_arrive( guy, anime, tag )
{
	guys = [];
	guys[ 0 ] = guy;
	anim_reach_with_funcs( guys, anime, tag, "generic", ::reach_with_arrivals_begin, ::reach_with_standard_adjustments_end );
}

/* 
============= 
///ScriptDocBegin
"Name: anim_reach_and_plant( <guys>, <scene> , <optional tag to animate relative to> )"
"Summary: Makes an AI move to the position to start an animation, with arrivals, and plants the point to the ground so you can do an animmode gravity after the reach. The calling ent notifies itself the name of the animation scene when it completes."
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <thing that will animate> AI that will move."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ generic ][ anime ]."
"OptionalArg: <optional tag to animate relative to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_reach_and_plant( guy, "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
============= 
*/ 

anim_reach_and_plant( guys, anime, tag )
{
	anim_reach_with_funcs( guys, anime, tag, undefined, ::reach_with_planting, ::reach_with_standard_adjustments_end );
}

/* 
============= 
///ScriptDocBegin
"Name: anim_reach_and_plant_and_arrive( <guys>, <scene> , <optional tag to animate relative to> )"
"Summary: Makes an AI move to the position to start an animation, with arrivals, and plants the point to the ground so you can do an animmode gravity after the reach. The calling ent notifies itself the name of the animation scene when it completes."
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <thing that will animate> AI that will move."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ generic ][ anime ]."
"OptionalArg: <optional tag to animate relative to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_reach_and_plant( guy, "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
============= 
*/ 

anim_reach_and_plant_and_arrive( guys, anime, tag )
{
	anim_reach_with_funcs( guys, anime, tag, undefined, ::reach_with_planting_and_arrivals, ::reach_with_standard_adjustments_end );
}

/* 
============= 
///ScriptDocBegin
"Name: anim_generic_loop( <guy>, <scene> , <optional ender notify> , <optional tag to animate relative to> )"
"Summary: Makes an AI play a generic looping anim. The calling ent notifies itself the name of the animation scene when it completes."
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <thing that will animate> AI, model, or vehicle."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ generic ][ anime ]."
"OptionalArg: <optional ender notify> : Ends the loop on notify."
"OptionalArg: <optional tag to animate relative to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_generic_loop( guy, "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
============= 
*/ 

anim_generic_loop( guy, anime, ender, tag )
{
	// package him off nicely for anim_loop_packet
	packet = [];
	packet[ "guy" ] = guy;
	packet[ "entity" ] = self;
	packet[ "tag" ] = tag;
	guyPackets[ 0 ] = packet;

	anim_loop_packet( guyPackets, anime, ender, "generic" );
}


/* 
============= 
///ScriptDocBegin
"Name: anim_custom_animmode( <guys>, <animmode> , <scene> , <tag> )"
"Summary: Makes an AI play an anim using a specific animmode."
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <array of things that animate> : An array of AI."
"MandatoryArg: <animmode> : The preferred animmode."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ animname ][ anime ]."
"OptionalArg: <optional tag to attach to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_custom_animmode( guys, "gravity", "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
============= 
*/ 

anim_custom_animmode( guys, custom_animmode, anime, tag )
{
	array = get_anim_position( tag );
	org = array[ "origin" ];
	angles = array[ "angles" ];

	aguy = undefined;
	foreach ( guy in guys )
	{
		aguy = guy;
		assertex( isdefined( guy.animname ), "Guy wants to do animmode custom but has no animname" );
		thread anim_custom_animmode_on_guy( guy, custom_animmode, anime, org, angles, guy.animname, false );
//             anim_custom_animmode_on_guy( guy, custom_animmode, anime, org, angles, animname_override, loop, thread_func )
		
	}

	AssertEx( IsDefined( aguy ), "anim_custom_animmode called without a guy in the array" );
	aguy wait_until_anim_finishes( anime );

	self notify( anime );
}


/* 
============= 
///ScriptDocBegin
"Name: anim_custom_animmode_loop( <guys>, <animmode> , <scene> , <tag> )"
"Summary: Makes an AI play an anim using a specific animmode."
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <array of things that animate> : An array of AI."
"MandatoryArg: <animmode> : The preferred animmode."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ animname ][ anime ]."
"OptionalArg: <optional tag to attach to> : A tag that the root entity has that the animating entities are attached to."
"Example: node anim_custom_animmode( guys, "gravity", "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
============= 
*/ 

anim_custom_animmode_loop( guys, custom_animmode, anime, tag )
{
	array = get_anim_position( tag );
	org = array[ "origin" ];
	angles = array[ "angles" ];

	foreach ( guy in guys )
	{
		thread anim_custom_animmode_on_guy( guy, custom_animmode, anime, org, angles, guy.animname, true );
	}

	AssertEx( IsDefined( guys[ 0 ] ), "anim_custom_animmode called without a guy in the array" );
	guys[ 0 ] wait_until_anim_finishes( anime );

	self notify( anime );
}

wait_until_anim_finishes( anime )
{
	self endon( "finished_custom_animmode" + anime );
	self waittill( "death" );
}

/*
=============
///ScriptDocBegin
"Name: anim_generic_custom_animmode( <guy> , <custom_animmode> , <anime> , <tag> , <thread_func> )"
"Summary: Runs a custom animmode on a level.scr_anim["generic"]  anim."
"Module: Anim"
"CallOn: An ai"
"MandatoryArg: <guy>: The guy that animates "
"MandatoryArg: <custom_animmode>: The animmode "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: An optional tag that the guy should already be linked to"
"OptionalArg: <thread_func>: An optional function to run in a thread when the custom animation starts"
"OptionalArg: <skip_start_pos>: An optional boolean that skips 'set_start_post()' from being called, which teleports the AI"
"Example: anim_generic_custom_animmode( guy, custom_animmode, anime, tag );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_generic_custom_animmode( guy, custom_animmode, anime, tag, thread_func, skip_start_pos )
{
	array = get_anim_position( tag );
	org = array[ "origin" ];
	angles = array[ "angles" ];

	thread anim_custom_animmode_on_guy( guy, custom_animmode, anime, org, angles, "generic", false, thread_func, skip_start_pos );
	guy wait_until_anim_finishes( anime );
	self notify( anime );
}

/*
=============
///ScriptDocBegin
"Name: anim_generic_custom_animmode_loop( <guy> , <custom_animmode> , <anime> , <tag> , <thread_func> )"
"Summary: Runs a custom animmode on a level.scr_anim["generic"]  anim."
"Module: Anim"
"CallOn: An ai"
"MandatoryArg: <guy>: The guy that animates "
"MandatoryArg: <custom_animmode>: The animmode "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: An optional tag that the guy should already be linked to"
"OptionalArg: <thread_func>: An optional function to run in a thread when the custom animation starts"
"OptionalArg: <skip_start_pos>: An optional boolean that skips 'set_start_post()' from being called, which teleports the AI
"Example: anim_generic_custom_animmode( guy, custom_animmode, anime, tag );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_generic_custom_animmode_loop( guy, custom_animmode, anime, tag, thread_func, skip_start_pos )
{
	array = get_anim_position( tag );
	org = array[ "origin" ];
	angles = array[ "angles" ];

	thread anim_custom_animmode_on_guy( guy, custom_animmode, anime, org, angles, "generic", true, thread_func, skip_start_pos );
	guy wait_until_anim_finishes( anime );
	self notify( anime );
}


/*
=============
///ScriptDocBegin
"Name: anim_custom_animmode_solo( <guy> , <custom_animmode> , <anime> , <tag> )"
"Summary:  Makes an AI play an anim using a specific animmode."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guy>: "
"MandatoryArg: <custom_animmode>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"MandatoryArg: <tag>: "
"Example: self anim_custom_animmode_solo( self, "gravity", "mole_wave_right" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_custom_animmode_solo( guy, custom_animmode, anime, tag )
{
	guys = [];
	guys[ 0 ] = guy;
	anim_custom_animmode( guys, custom_animmode, anime, tag );
}


 /* 
 ============= 
///ScriptDocBegin
"Name: anim_first_frame_solo( <guy> , <scene> , <tag> )"
"Summary: Puts the animating model or AI or vehicle into the first frame of the animated scene. The animation is played relative to the entity that calls the scene"
"Module: Anim"
"CallOn: The root entity that is the point of relativity for the scene, be it node, ai, vehicle, etc."
"MandatoryArg: <a single thing that animates> : An AI or vehicle or script_model that can animate."
"MandatoryArg: <name of animation scene> : The anime in level.scr_anim[ animname ][ anime ]."
"OptionalArg: <optional tag to attach to> : A tag that the root entity has that the animating entity is attached to."
"Example: node anim_first_frame_solo( guy, "rappel_sequence" );"
"SPMP: singleplayer"
///ScriptDocEnd
 ============= 
 */ 

anim_first_frame_solo( guy, anime, tag )
{
	guys = [];
	guys[ 0 ] = guy;
	anim_first_frame( guys, anime, tag );
}

anim_last_frame_solo( guy, anime, tag )
{

	guys = [];
	guys[ 0 ] = guy;
	anim_first_frame( guys, anime, tag );
	anim_set_time( guys, anime, 1.0 );
}

assert_existance_of_anim( anime, animname )
{
	if ( !isdefined( animname ) )
		animname = self.animname;

	AssertEx( IsDefined( animname ), "Animating character of type " + self.classname + " has no animname." );

	has_anim = false;
	if ( IsDefined( level.scr_anim[ animname ] ) )
	{
		has_anim = true;
		if ( IsDefined( level.scr_anim[ animname ][ anime ] ) )
		{
			return;
		}
	}

	has_sound = false;
	if ( IsDefined( level.scr_sound[ animname ] ) )
	{
		has_sound = true;
		if ( IsDefined( level.scr_sound[ animname ][ anime ] ) )
		{
			return;
		}
	}

	if ( has_anim || has_sound )
	{
		if ( has_anim )
		{
			array = GetArrayKeys( level.scr_anim[ animname ] );
			PrintLn( "Legal anime scenes for " + animname + ":" );
			foreach ( member in array )
			{
				PrintLn( member );
			}
		}
		if ( has_sound )
		{
			array = GetArrayKeys( level.scr_sound[ animname ] );
			PrintLn( "Legal scr_sound scenes for " + animname + ":" );
			foreach ( member in array )
			{
				PrintLn( member );
			}
		}
		PrintLn( "Guy with animname " + animname + " is trying to do scene " + anime + " there is no level.scr_anim or level.scr_sound for that animname" );
		AssertMsg( "That scene doesn't exist! See above in console log for details." );
		return;
	}

	keys = GetArrayKeys( level.scr_anim );
	keys = array_combine( keys, GetArrayKeys( level.scr_sound ) );
	foreach ( key in keys )
	{
		PrintLn( key );
	}
	AssertMsg( "Animname " + animname + " is not setup to do animations. See above for list of legal animnames." );
}

anim_first_frame_on_guy( guy, anime, org, angles, animname_override )
{

	guy.first_frame_time = GetTime();


	if ( IsDefined( animname_override ) )
		animname = animname_override;
	else
		animname = guy.animname;

	guy set_start_pos( anime, org, angles, animname );

	/#
	guy assert_existance_of_anim( anime, animname );
	#/

	if ( IsAI( guy ) )
	{
		// ai run a special animscript so they dont bust out
// 		guy Teleport( org, angles );
		guy._first_frame_anim = anime;
		guy._animname = animname;
		guy AnimCustom( animscripts\first_frame::main );
	}
	else
	{
// 		guy.origin = org;
// 		guy.angles = angles;
		guy StopAnimScripted();
		guy SetAnimKnob( level.scr_anim[ animname ][ anime ], 1, 0, 0 );
	}


// 	guy SetAnim( level.scr_anim[ guy.animname ][ anime ], 1, 0, 0 );
}


anim_custom_animmode_on_guy( guy, custom_animmode, anime, org, angles, animname_override, loop, thread_func, skip_start_pos )
{
	if ( IsAI( guy ) && guy doingLongDeath() )
		return;

	animname = undefined;
	if ( IsDefined( animname_override ) )
		animname = animname_override;
	else
		animname = guy.animname;

	/#
	guy assert_existance_of_anim( anime, animname );
	#/

	AssertEx( IsAI( guy ), "Tried to do custom_animmode on a non ai" );

	if ( !IsDefined( skip_start_pos ) || !skip_start_pos )
	{
		guy set_start_pos( anime, org, angles, animname_override, loop );
	}

	guy._animmode = custom_animmode;
	guy._custom_anim = anime;
	guy._tag_entity = self;
	guy._anime = anime;
	guy._animname = animname;
	guy._custom_anim_loop = loop;
	guy._custom_anim_thread = thread_func;
	guy AnimCustom( animscripts\animmode::main );
}

/*
=============
///ScriptDocBegin
"Name: anim_loop( <guys> , <anime> , <ender> , <tag> )"
"Summary: An array of actors or script_models do a looping animation in sync to an optional tag or model. "
"Module: Anim"
"CallOn: An entity or node that will be the root of the animation"
"MandatoryArg: <guys>: Array of entities that will animate "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <ender>: The loops will stop reoccurring if this is notified to the root entity."
"OptionalArg: <tag>: An optional tag that the scene is relative to"
"Example: node thread anim_loop( guys, "wounded_idle" );"
///ScriptDocEnd
=============
*/
anim_loop( guys, anime, ender, tag )
{
	guyPackets = [];
	foreach ( guy in guys )
	{
		packet = [];
		packet[ "guy" ] = guy;
		packet[ "entity" ] = self;
		packet[ "tag" ] = tag;
		guyPackets[ guyPackets.size ] = packet;
	}

	anim_loop_packet( guyPackets, anime, ender );
}

anim_loop_packet_solo( singleGuyPacket, anime, ender )
{
	loopPacket = [];
	loopPacket[ 0 ] = singleGuyPacket;
	anim_loop_packet( loopPacket, anime, ender );
}

anim_loop_packet( guyPackets, anime, ender, animname_override )
{
	// disable BCS if we're doing a scripted sequence.
	foreach ( guyPacket in guyPackets )
	{
		guy = guyPacket[ "guy" ];
		if ( !isdefined( guy ) )
			continue;

		if ( !isdefined( guy._animActive ) )
			guy._animActive = 0;// script models cant get their animactive set by init

		guy endon( "death" );
		guy._animActive++;
	}

	baseGuy = guyPackets[ 0 ][ "guy" ];
/#
	if ( !isdefined( baseGuy.loops ) )
	{
		baseGuy.loops = 0;
	}

	thread printloops( baseGuy, anime );
#/

	if ( !isdefined( ender ) )
		ender = "stop_loop";

	// kills notetracks on the guys doing looping anims
	thread endonRemoveAnimActive( ender, guyPackets );

	self endon( ender );
/#
	self thread looping_anim_ender( baseGuy, ender );
#/

	anim_string = "looping anim";

	base_animname = undefined;
	if ( IsDefined( animname_override ) )
		base_animname = animname_override;
	else
		base_animname = baseGuy.animname;


	idleanim = 0;
	lastIdleanim = 0;
	while ( 1 )
	{
		idleanim = anim_weight( base_animname, anime );
		while ( ( idleanim == lastIdleanim ) && ( idleanim != 0 ) )
			idleanim = anim_weight( base_animname, anime );
		lastIdleanim = idleanim;

		scriptedAnimationIndex = undefined;
		scriptedAnimationTime = 999999;

		scriptedSoundIndex = undefined;
		guy = undefined;
		foreach ( i, guyPacket in guyPackets )
		{
			entity = guyPacket[ "entity" ];
			guy = guyPacket[ "guy" ];
			pos = entity get_anim_position( guyPacket[ "tag" ] );
			org = pos[ "origin" ];
			angles = pos[ "angles" ];
			
			
			if ( isdefined( guy.remove_from_animloop ) )
			{
				guy.remove_from_animloop = undefined;
				guyPackets[ i ] = undefined;
				continue;
			}
			

			doFacialanim = false;
			doDialogue = false;
			doAnimation = false;
			doText = false;
			facialAnim = undefined;
			dialogue = undefined;
			animname = undefined;
			if ( IsDefined( animname_override ) )
				animname = animname_override;
			else
				animname = guy.animname;

			if ( ( IsDefined( level.scr_face[ animname ] ) ) &&
				( IsDefined( level.scr_face[ animname ][ anime ] ) ) &&
				( IsDefined( level.scr_face[ animname ][ anime ][ idleanim ] ) ) )
			{
				doFacialanim = true;
				facialAnim = level.scr_face[ animname ][ anime ][ idleanim ];
			}

			if ( ( IsDefined( level.scr_sound[ animname ] ) ) &&
				( IsDefined( level.scr_sound[ animname ][ anime ] ) ) &&
				( IsDefined( level.scr_sound[ animname ][ anime ][ idleanim ] ) ) )
			{
				doDialogue = true;
				dialogue = level.scr_sound[ animname ][ anime ][ idleanim ];
			}

			if ( IsDefined( level.scr_animSound[ animname ] ) &&
				 IsDefined( level.scr_animSound[ animname ][ idleanim + anime ] ) )
			{
				guy PlaySound( level.scr_animSound[ animname ][ idleanim + anime ] );
			}
			 /* 
			 /#
			if ( GetDebugDvar( "animsound" ) == "on" )
			{
				guy thread animsound_start_tracker( anime );
			}
			#/ 
			 */ 

			/#
			if ( GetDebugDvar( "animsound" ) == "on" )
			{
				guy thread animsound_start_tracker_loop( anime, idleanim, animname );
			}
// 			guy thread animsound_start_tracker( anime );
			#/

			if ( ( IsDefined( level.scr_anim[ animname ] ) ) &&
				( IsDefined( level.scr_anim[ animname ][ anime ] ) ) &&
				( !isAI( guy ) || !guy doingLongDeath() ) )
				doAnimation = true;

			/#
			if ( ( IsDefined( level.scr_text[ animname ] ) ) &&
				( IsDefined( level.scr_text[ animname ][ anime ] ) ) )
				doText = true;
			#/


			if ( doAnimation )
			{
				// ai and models use animscripted
				guy last_anim_time_check();
				guy AnimScripted( anim_string, org, angles, level.scr_anim[ animname ][ anime ][ idleanim ] );

				animtime = GetAnimLength( level.scr_anim[ animname ][ anime ][ idleanim ] );
				if ( animtime < scriptedAnimationTime )
				{
					scriptedAnimationTime = animtime;
					scriptedAnimationIndex = i;
				}

				thread start_notetrack_wait( guy, anim_string, anime, animname );

				thread animscriptDoNoteTracksThread( guy, anim_string, anime );
			}

			if ( ( doFacialanim ) || ( doDialogue ) )
			{
// 				PrintLn( "dofacialanim: ", dofacialanim, " and dodialogue: ", dodialogue );
// 				PrintLn( "^3 Animname: ", guy[ i ].animname, " doing animation ", anime, " facial: ", facialanim, " dialogue: ", dialogue );

				if ( IsAI( guy ) )
				{
					if ( doAnimation )
						guy SaySpecificDialogue( facialAnim, dialogue, 1.0 );
					else
						guy SaySpecificDialogue( facialAnim, dialogue, 1.0, anim_string );
				}
				else
				{
					guy play_sound_on_entity( dialogue );
				}

				scriptedSoundIndex = i;
			}

			/#
			if ( doText && !doDialogue )
				IPrintLnBold( level.scr_text[ animname ][ anime ] );

// 			add_animation( animname, anime );
			#/
		}
		
		if ( !isdefined( guy ) )
			break;

		if ( isdefined( scriptedAnimationIndex ) )
			guyPackets[ scriptedAnimationIndex ][ "guy" ] waittillmatch( anim_string, "end" );
		else
		if ( isdefined( scriptedSoundIndex ) )
			guyPackets[ scriptedSoundIndex ][ "guy" ] waittill( anim_string );
	}
}

start_notetrack_wait( guy, anim_string, anime, animname )
{
	guy notify( "stop_sequencing_notetracks" );

	thread notetrack_wait( guy, anim_string, self, anime, animname );
}

anim_single_failsafeOnGuy( owner, anime )
{
	/#
	if ( GetDebugDvar( "debug_grenadehand" ) != "on" )
		return;

	owner endon( anime );
	owner endon( "death" );
	self endon( "death" );
	name = self.classname;
	num = self GetEntNum();
	wait( 60 );
	PrintLn( "Guy had classname " + name + " and entnum " + num );
	waittillframeend;
	AssertEx( 0, "Animation '" + anime + "' did not finish after 60 seconds. See note above" );
	#/

}

anim_single_failsafe( guys, anime )
{
// 	 /#
// 	self endon( anime );
// 	self endon( "death" );
	foreach ( guy in guys )
		guy thread anim_single_failsafeOnGuy( self, anime );
	 /* 
	guyName = [];
	guyNum = [];
	for ( i = 0;i < guy.size;i ++ )
	{
		guyName[ i ] = guy[ i ].classname;
		guyNum[ i ] = guy[ i ] GetEntNum();
	}
	
	wait( 60 );
	PrintLn( " ============ solo ran > 60 seconds from anim: ", anime );
	for ( i = 0;i < guy.size;i ++ )
	{
		PrintLn( "Guy with classname " + guyName[ i ] + " and entnum " + guyNum[ i ] );
	}
	AssertEx( 0, "Animation '" + anime + "' did not finish after 60 seconds. See note above" );
	#/ 
	 */ 
}


/*
=============
///ScriptDocBegin
"Name: anim_single( <guys> , <anime> , <tag>, <anim_end_time> )"
"Summary: An array of actors or script_models do an animation in sync to an optional tag or model. Returns after the longest animation completes."
"Module: Anim"
"CallOn: An entity or node that will be the root of the animation"
"MandatoryArg: <guys>: Array of entities that will animate "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: An optional tag that the scene is relative to"
"OptionalArg: <anim_end_time>: The amount of time to end the animation early"
"OptionalArg: <animname_override>: Overrides the animname of the guys animating"
"Example: node thread anim_single( guys, "wounded_pickup" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_single( guys, anime, tag, anim_end_time, animname_override )
{
	if ( !isdefined( anim_end_time ) )
		anim_end_time = 0;
	anim_single_internal( guys, anime, tag, anim_end_time, animname_override );
}

/*
=============
///ScriptDocBegin
"Name: anim_single_run( <guys> , <anime> , <tag> )"
"Summary: Works like anim_single but the anim blends out early so it can blend into a run"
"Module: Anim"
"CallOn: An entity or node that will be the root of the animation"
"MandatoryArg: <guys>: Array of entities that will animate "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: An optional tag that the scene is relative to"
"Example: node thread anim_single( guys, "wounded_pickup" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_single_run( guys, anime, tag, animname_override )
{
	anim_single_internal( guys, anime, tag, CONST_anim_end_time, animname_override );
}

anim_single_internal( guys, anime, tag, anim_end_time, animname_override )
{
	entity = self;

	/#
	thread anim_single_failsafe( guys, anime );
	#/
	// disable BCS if we're doing a scripted sequence.
	foreach ( guy in guys )
	{
		if ( !isdefined( guy ) )
			continue;
		if ( !isdefined( guy._animActive ) )
			guy._animActive = 0;// script models cant get their animactive set by init
		guy._animActive++;
	}

	pos = get_anim_position( tag );
	org = pos[ "origin" ];
	angles = pos[ "angles" ];

	scriptedAnimationIndex = undefined;
	scriptedAnimationTime = 999999;

	scriptedSoundIndex = undefined;
	scriptedFaceIndex = undefined;
	scriptedFaceAnim = undefined;
	anim_string = "single anim";

	foreach ( i, guy in guys )
	{

		doFacialanim = false;
		doDialogue = false;
		doAnimation = false;
		doText = false;

		dialogue = undefined;
		facialAnim = undefined;

		animname = undefined;
		if ( IsDefined( animname_override ) )
			animname = animname_override;
		else
			animname = guy.animname;

		/#
		guy assert_existance_of_anim( anime, animname );
		#/

		if ( ( IsDefined( level.scr_face[ animname ] ) ) &&
			( IsDefined( level.scr_face[ animname ][ anime ] ) ) )
		{
			doFacialanim = true;
			facialAnim = level.scr_face[ animname ][ anime ];
			scriptedFaceAnim = facialAnim;
		}

		if ( ( IsDefined( level.scr_sound[ animname ] ) ) &&
			( IsDefined( level.scr_sound[ animname ][ anime ] ) ) )
		{
			doDialogue = true;
			dialogue = level.scr_sound[ animname ][ anime ];
		}

		if ( ( IsDefined( level.scr_anim[ animname ] ) ) &&
			( IsDefined( level.scr_anim[ animname ][ anime ] ) ) &&
			( !isAI( guy ) || !guy doingLongDeath() ) )
			doAnimation = true;

		if ( IsDefined( level.scr_animSound[ animname ] ) &&
			 IsDefined( level.scr_animSound[ animname ][ anime ] ) )
		{
			guy PlaySound( level.scr_animSound[ animname ][ anime ] );
		}

		/#
		if ( GetDebugDvar( "animsound" ) == "on" )
		{
			guy thread animsound_start_tracker( anime, animname );
		}
		#/


		/#
		if ( ( IsDefined( level.scr_text[ animname ] ) ) &&
			( IsDefined( level.scr_text[ animname ][ anime ] ) ) )
			doText = true;
		#/

		if ( doAnimation )
		{
			guy last_anim_time_check();
			if ( isPlayer( guy ) )
			{
//				guy ForceTeleport( org, angles );

				root_animation = level.scr_anim[ animname ][ "root" ];
				guy SetAnim( root_animation, 0, 0.2 );

				animation = level.scr_anim[ animname ][ anime ];
				guy SetFlaggedAnim( anim_string, animation, 1, 0.2 );
				
			}
			else
			if ( guy.code_classname == "misc_turret" )
			{
				animation = level.scr_anim[ animname ][ anime ];
				guy SetFlaggedAnim( anim_string, animation, 1, 0.2 );
			}
			else
			{
				// ai and models use animscripted
				guy AnimScripted( anim_string, org, angles, level.scr_anim[ animname ][ anime ] );
			}

			animtime = GetAnimLength( level.scr_anim[ animname ][ anime ] );
			if ( animtime < scriptedAnimationTime )
			{
				scriptedAnimationTime = animtime;
				scriptedAnimationIndex = i;
			}

			thread start_notetrack_wait( guy, anim_string, anime, animname );
			thread animscriptDoNoteTracksThread( guy, anim_string, anime );
		}


		if ( ( doFacialanim ) || ( doDialogue ) )
		{
			/#
			println("**dialog alias playing locally: " + dialogue );
			#/
			if ( doFacialAnim )
			{
				if ( doDialogue )
					guy thread delayedDialogue( anime, doFacialanim, dialogue, level.scr_face[ animname ][ anime ] );
				AssertEx( !doanimation, "Can't play a facial anim and fullbody anim at the same time. The facial anim should be in the full body anim. Occurred on animation " + anime );
				thread anim_facialAnim( guy, anime, level.scr_face[ animname ][ anime ] );
				scriptedFaceIndex = i;
			}
			else
			{
				if ( IsAI( guy ) )
				{
					if ( doAnimation )
						guy SaySpecificDialogue( facialAnim, dialogue, 1.0 );
					else
					{
						guy thread anim_facialFiller( "single dialogue" );
						guy SaySpecificDialogue( facialAnim, dialogue, 1.0, "single dialogue" );
					}
				}
				else
				{
					guy thread play_sound_on_entity( dialogue, "single dialogue" );
				}
			}

			scriptedSoundIndex = i;
		}
		AssertEx( doAnimation || doFacialanim || doDialogue || doText, "Tried to do anim scene " + anime + " on guy with animname " + animname + ", but he didn't have that anim scene." );

// 		add_animation( animname, anime );

		/#
		if ( doText && !doDialogue )
		{
			IPrintLnBold( level.scr_text[ animname ][ anime ] );
			wait 1.5;
		}
		#/
	}

	if ( isdefined( scriptedAnimationIndex ) )
	{
		ent = SpawnStruct();
		ent thread anim_deathNotify( guys[ scriptedAnimationIndex ], anime );
		ent thread anim_animationEndNotify( guys[ scriptedAnimationIndex ], anime, scriptedAnimationTime, anim_end_time );
		ent waittill( anime );
	}
	else
	if ( isdefined( scriptedFaceIndex ) )
	{
		ent = SpawnStruct();
		ent thread anim_deathNotify( guys[ scriptedFaceIndex ], anime );
		ent thread anim_facialEndNotify( guys[ scriptedFaceIndex ], anime, scriptedFaceAnim );
		ent waittill( anime );
	}
	else
	if ( isdefined( scriptedSoundIndex ) )
	{
		ent = SpawnStruct();
		ent thread anim_deathNotify( guys[ scriptedSoundIndex ], anime );
		ent thread anim_dialogueEndNotify( guys[ scriptedSoundIndex ], anime );
		ent waittill( anime );
	}

	foreach ( guy in guys )
	{
		if ( !isdefined( guy ) )
			continue;
		
		if ( isPlayer( guy ) )
		{	
			animname = undefined;
			if ( IsDefined( animname_override ) )
				animname = animname_override;
			else
				animname = guy.animname;

			// is there an animation?
			if ( isdefined( level.scr_anim[ animname ][ anime ] ) )
			{
				root_animation = level.scr_anim[ animname ][ "root" ];
				guy setanim( root_animation, 1, 0.2 );
	
				animation = level.scr_anim[ animname ][ anime ];
				guy ClearAnim( animation, 0.2 );
			}
		}
					
		guy._animActive--;
		guy._lastAnimTime = GetTime();
		Assert( guy._animactive >= 0 );
	}
	self notify( anime );
}

anim_deathNotify( guy, anime )
{
	self endon( anime );
	guy waittill( "death" );
	self notify( anime );
}


anim_facialEndNotify( guy, anime, scriptedFaceAnim )
{
	self endon( anime );
	time = getanimlength( scriptedFaceAnim );
	wait( time );
//	guy waittillmatch( "face_done_" + anime, "end" );
	self notify( anime );
}

anim_dialogueEndNotify( guy, anime )
{
	self endon( anime );
	guy waittill( "single dialogue" );
	self notify( anime );
}

anim_animationEndNotify( guy, anime, scriptedAnimationTime, anim_end_time )
{
	self endon( anime );
	guy endon( "death" );
	scriptedAnimationTime -= anim_end_time;
	if ( anim_end_time > 0 && scriptedAnimationTime > 0 )
	{
		guy waittill_match_or_timeout( "single anim", "end", scriptedAnimationTime );
		guy StopAnimScripted();
	}
	else
	{
		guy waittillmatch( "single anim", "end" );
	}
	self notify( anime );
}

animscriptDoNoteTracksThread( guy, animstring, anime )
{
	if ( IsDefined( guy.dontdonotetracks ) && guy.dontdonotetracks )
		return;
	guy endon( "stop_sequencing_notetracks" );
	guy endon( "death" );
	guy DoNoteTracks( animstring );
}

add_animsound( newSound )
{
	// find a vacant slot in the array
	for ( i = 0; i < level.animsound_hudlimit; i++ )
	{
		if ( IsDefined( self.animsounds[ i ] ) )
		{
			continue;
		}
		self.animSounds[ i ] = newSound;
		return;
	}

	// replace the oldest one
	keys = GetArrayKeys( self.animsounds );
	index = keys[ 0 ];
	timer = self.animsounds[ index ].end_time;
	for ( i = 1; i < keys.size; i++ )
	{
		key = keys[ i ];

		if ( self.animsounds[ key ].end_time < timer )
		{
			timer = self.animsounds[ key ].end_time;
			index = key;
		}
	}

	self.animSounds[ index ] = newSound;
}

animSound_exists( anime, notetrack )
{
	notetrack = ToLower( notetrack );// notetracks get converted to lowercase before they reach script

	keys = GetArrayKeys( self.animSounds );
	for ( i = 0; i < keys.size; i++ )
	{
		key = keys[ i ];
		if ( self.animSounds[ key ].anime != anime )
			continue;
		if ( self.animSounds[ key ].notetrack != notetrack )
			continue;
		// up its time since it was hit again
		self.animSounds[ key ].end_time = GetTime() + 60000;
		return true;
	}
	return false;
}


animsound_tracker( anime, notetrack, animname )
{
	notetrack = ToLower( notetrack );// notetracks get converted to lowercase before they reach script

	add_to_animsound();

	if ( notetrack == "end" )
		return;

	if ( animSound_exists( anime, notetrack ) )
		return;

	newTrack = SpawnStruct();
	newTrack.anime = anime;
	newTrack.notetrack = notetrack;
	newTrack.animname = animname;
	newTrack.end_time = GetTime() + 60000;

	add_animsound( newTrack );
}

animsound_start_tracker( anime, animname )
{
	// tracks the start of every animation or sound call
	// so sound can attach a sound at that time

	add_to_animsound();

	newSound = SpawnStruct();
	newSound.anime = anime;
	newSound.notetrack = "#" + anime;
	newSound.animname = animname;
	newSound.end_time = GetTime() + 60000;

	if ( animSound_exists( anime, newSound.notetrack ) )
		return;

	add_animsound( newSound );
}

animsound_start_tracker_loop( anime, loop, animname )
{
	// tracks the start of every animation or sound call
	// so sound can attach a sound at that time

	add_to_animsound();

	anime = loop + anime;
	newSound = SpawnStruct();
	newSound.anime = anime;
	newSound.notetrack = "#" + anime;
	newSound.animname = animname;
	newSound.end_time = GetTime() + 60000;

	if ( animSound_exists( anime, newSound.notetrack ) )
		return;

	add_animsound( newSound );
}

notetrack_wait( guy, msg, tag_entity, anime, animname_override )
{
	guy endon( "stop_sequencing_notetracks" );
	guy endon( "death" );

// 	self endon( ender );
	if ( IsDefined( tag_entity ) )
		tag_owner = tag_entity;
	else
		tag_owner = self;

	animname = undefined;
	if ( IsDefined( animname_override ) )
		animname = animname_override;
	else
		animname = guy.animname;

	// fill the dialogue array and then unfill it as the lines are called, so dialogue entered
	// in order will play in order
	// level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ][ "dialog" ] = soundalias;
	dialogue_array = SpawnStruct();
	dialogue_array.dialog = [];
	scripted_notetracks = [];

	if ( isdefined( animname ) && IsDefined( level.scr_notetrack[ animname ] ) )
	{
		if ( IsDefined( level.scr_notetrack[ animname ][ anime ] ) )
		{
			scripted_notetracks[ anime ] = level.scr_notetrack[ animname ][ anime ];
		}
		if ( IsDefined( level.scr_notetrack[ animname ][ "any" ] ) )
		{
			scripted_notetracks[ "any" ] = level.scr_notetrack[ animname ][ "any" ];
		}
	}

	foreach ( anime_key, _ in scripted_notetracks )
	{
		foreach ( notetrack_array in level.scr_notetrack[ animname ][ anime_key ] )
		{
			foreach ( scr_notetrack in notetrack_array )
			{
				if ( IsDefined( scr_notetrack[ "dialog" ] ) )
					dialogue_array.dialog[ scr_notetrack[ "dialog" ] ] = true;
			}
		}
	}

	while ( 1 )
	{
		dialogue_array.dialogueNotetrack = false;
		
		notetrack = undefined;
		guy waittill( msg, notetrack );

		/#
		if ( GetDebugDvar( "animsound" ) == "on" )
		{
			guy thread animsound_tracker( anime, notetrack, animname );
		}
		#/

		if ( notetrack == "end" )
			return;

		foreach ( anime_key, _ in scripted_notetracks )
		{
			if ( IsDefined( level.scr_notetrack[ animname ][ anime_key ][ notetrack ] ) )
			{
				foreach ( scr_notetrack in level.scr_notetrack[ animname ][ anime_key ][ notetrack ] )
				{
					anim_handle_notetrack( scr_notetrack, guy, dialogue_array, tag_owner );
				}
			}
		}

		prefix = GetSubStr( notetrack, 0, 3 );
		if ( prefix == "ps_" )
		{
			alias = GetSubStr( notetrack, 3 );
			if (alias == "dubai_elevse_yuri_remove_plr_armor")
			{
				breakpoint;
			}
			guy thread play_sound_on_tag( alias, undefined, true );
			continue;
		}
		
		// playsound message prefix using audio send message utility
		if ( prefix == "psm" )
		{
			message = GetSubStr( notetrack, 4 );
			maps\_audio::aud_send_msg(message, guy);
			continue;
		}

		prefix = GetSubStr( notetrack, 0, 4 );
		if ( prefix == "psr_" )
		{
			alias = GetSubStr( notetrack, 4 );
			radio_dialogue( alias );
			continue;
		}

		switch( notetrack )
		{
			case "ignoreall true":
				self.ignoreall = true;
				break;
			case "ignoreall false":
				self.ignoreall = false;
				break;
			case "ignoreme true":
				self.ignoreme = true;
				break;
			case "ignoreme false":
				self.ignoreme = false;
				break;
			case "allowdeath true":
				self.allowdeath = true;
				break;
			case "allowdeath false":
				self.allowdeath = false;
				break;
		}
	}
}

anim_handle_notetrack( scr_notetrack, guy, dialogue_array, tag_owner )
{
	if ( IsDefined( scr_notetrack[ "function" ] ) )
		self thread [[ scr_notetrack[ "function" ] ]]( guy );

	if ( IsDefined( scr_notetrack[ "flag" ] ) )
	{
		flag_set( scr_notetrack[ "flag" ] );
	}

	if ( IsDefined( scr_notetrack[ "flag_clear" ] ) )
	{
		flag_clear( scr_notetrack[ "flag_clear" ] );
	}

	if ( IsDefined( scr_notetrack[ "attach gun left" ] ) )
	{
		guy gun_pickup_left();
		return;
	}

	if ( IsDefined( scr_notetrack[ "attach gun right" ] ) )
	{
		guy gun_pickup_right();
		return;
	}

	if ( IsDefined( scr_notetrack[ "detach gun" ] ) )
	{
		guy gun_leave_behind( scr_notetrack );
		return;
	}

	if ( IsDefined( scr_notetrack[ "attach model" ] ) )
	{
		if ( IsDefined( scr_notetrack[ "selftag" ] ) )
			guy Attach( scr_notetrack[ "attach model" ], scr_notetrack[ "selftag" ] );
		else
			tag_owner Attach( scr_notetrack[ "attach model" ], scr_notetrack[ "tag" ] );

		return;
	}

	if ( IsDefined( scr_notetrack[ "detach model" ] ) )
	{
		waittillframeend;// because this should come after any attachs that happen on the same frame
		if ( IsDefined( scr_notetrack[ "selftag" ] ) )
			guy Detach( scr_notetrack[ "detach model" ], scr_notetrack[ "selftag" ] );
		else
			tag_owner Detach( scr_notetrack[ "detach model" ], scr_notetrack[ "tag" ] );
	}

	if ( IsDefined( scr_notetrack[ "sound" ] ) )
		guy thread play_sound_on_tag( scr_notetrack[ "sound" ], undefined, true );

	// dialogueNotetrack keeps it from playing more then one dialogue on a "dialog" notetrack at the same time.
	// it will play the next dialogue on the next "dialog" notetrack if there are more then one in the animation.
	if ( !dialogue_array.dialogueNotetrack )
	{
		if ( IsDefined( scr_notetrack[ "dialog" ] ) && IsDefined( dialogue_array.dialog[ scr_notetrack[ "dialog" ] ] ) )
		{
			guy SaySpecificDialogue( undefined, scr_notetrack[ "dialog" ], 1.0 );
			dialogue_array.dialog[ scr_notetrack[ "dialog" ] ] = undefined;
			dialogue_array.dialogueNotetrack = true;
		}
	}

	if ( IsDefined( scr_notetrack[ "create model" ] ) )
		anim_addModel( guy, scr_notetrack );
	else
	if ( IsDefined( scr_notetrack[ "delete model" ] ) )
		anim_removeModel( guy, scr_notetrack );

	if ( ( IsDefined( scr_notetrack[ "selftag" ] ) ) )
	{
    	if( IsDefined( scr_notetrack[ "effect" ] ) ) 
    	{
    		PlayFXOnTag( level._effect[ scr_notetrack[ "effect" ] ], guy, scr_notetrack[ "selftag" ] );
    	}
    	
    	if( isDefined( scr_notetrack[ "stop_effect" ] ) )
    	{
    		StopFXOnTag( level._effect[ scr_notetrack[ "stop_effect" ]  ], guy, scr_notetrack[ "selftag" ] );
    	}
	}

	if ( IsDefined( scr_notetrack[ "tag" ] ) && IsDefined( scr_notetrack[ "effect" ] ) )
	{
		PlayFXOnTag( level._effect[ scr_notetrack[ "effect" ] ], tag_owner, scr_notetrack[ "tag" ] );
	}

	if ( ( IsDefined( scr_notetrack[ "selftag" ] ) ) &&
	( IsDefined( scr_notetrack[ "effect_looped" ] ) ) )
	{
		PlayFXOnTag( level._effect[ scr_notetrack[ "effect_looped" ] ], guy, scr_notetrack[ "selftag" ] );
	}
    	
}


anim_addModel( guy, array )
{
	if ( !isdefined( guy.ScriptModel ) )
		guy.ScriptModel = [];

	index = guy.ScriptModel.size;
	guy.ScriptModel[ index ] = Spawn( "script_model", ( 0, 0, 0 ) );
	guy.ScriptModel[ index ] SetModel( array[ "create model" ] );
	guy.ScriptModel[ index ].origin = guy GetTagOrigin( array[ "selftag" ] );
	guy.ScriptModel[ index ].angles = guy GetTagAngles( array[ "selftag" ] );
}

anim_removeModel( guy, array )
{
/#
	if ( !isdefined( guy.ScriptModel ) )
		AssertMsg( "Tried to remove a model with delete model before it was create model'd on guy: " + guy.animname );
#/

	for ( i = 0; i < guy.ScriptModel.size; i++ )
	{
		if ( IsDefined( array[ "explosion" ] ) )
		{
			forward = AnglesToForward( guy.scriptModel[ i ].angles );
			forward *= ( 120 );
			forward += guy.scriptModel[ i ].origin;
			PlayFX( level._effect[ array[ "explosion" ] ], guy.scriptModel[ i ].origin );// , guy.scriptModel.origin, forward );
			RadiusDamage( guy.scriptModel[ i ].origin, 350, 700, 50 );
		}
		guy.scriptModel[ i ] Delete();
	}
}

gun_pickup_left()
{
	if ( !isdefined( self.gun_on_ground ) )
		return;

	self.gun_on_ground Delete();
	self.DropWeapon = true;
// 	PrintLn( "dropweapon is ", self.DropWeapon );

	self animscripts\shared::placeWeaponOn( self.weapon, "left" );
}

gun_pickup_right()
{
	if ( !isdefined( self.gun_on_ground ) )
		return;

	self.gun_on_ground Delete();
	self.DropWeapon = true;
// 	PrintLn( "dropweapon is ", self.DropWeapon );

	self animscripts\shared::placeWeaponOn( self.weapon, "right" );
}

gun_leave_behind( scr_notetrack )
{
	if ( IsDefined( self.gun_on_ground ) )
	{
		return;
	}

	origin = self GetTagOrigin( scr_notetrack[ "tag" ] );
	angles = self GetTagAngles( scr_notetrack[ "tag" ] );

	suspend = false;
	if ( IsDefined( scr_notetrack[ "suspend" ] ) )
	{
		suspend = scr_notetrack[ "suspend" ];
	}

	gun = Spawn( "weapon_" + self.weapon, origin, suspend );
	gun.angles = angles;

	self.gun_on_ground = gun;

	self animscripts\shared::placeWeaponOn( self.weapon, "none" );
	self.DropWeapon = false;
}

//delete_origin_on_gun_death( gun )
//{
//	gun waittill( "death" );
//	self Delete();
//}

anim_weight( animname, anime )
{
	AssertEx( IsDefined( level.scr_anim[ animname ][ anime ] ), "There is no animation scene \"" + anime + "\" for animname " + animname );
	AssertEx( IsArray( level.scr_anim[ animname ][ anime ] ), "the animation entry for level.scr_anim[ " + animname + " ][ " + anime + " ] needs to be an array of looping animations, not a single animation" );
	total_anims = level.scr_anim[ animname ][ anime ].size;
	idleanim = RandomInt( total_anims );
	if ( total_anims > 1 )
	{
		weights = 0;
		anim_weight = 0;

		for ( i = 0; i < total_anims; i++ )
		{
			if ( IsDefined( level.scr_anim[ animname ][ anime + "weight" ] ) )
			{
				if ( IsDefined( level.scr_anim[ animname ][ anime + "weight" ][ i ] ) )
				{
					weights++;
					anim_weight += level.scr_anim[ animname ][ anime + "weight" ][ i ];
				}
			}
		}

		if ( weights == total_anims )
		{
			anim_play = RandomFloat( anim_weight );
			anim_weight	 = 0;

			for ( i = 0; i < total_anims; i++ )
			{
				anim_weight += level.scr_anim[ animname ][ anime + "weight" ][ i ];
				if ( anim_play < anim_weight )
				{
					idleanim = i;
					break;
				}
			}
		}
	}

	return idleanim;
}

/*
=============
///ScriptDocBegin
"Name: anim_reach_and_idle( <guys> , <anime> , <anime_idle> , <ender> , <tag> )"
"Summary: Make AI run to an animation start and loop the anim."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guys>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"MandatoryArg: <anime_idle>: "
"MandatoryArg: <ender>: "
"MandatoryArg: <tag>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_reach_and_idle( guys, anime, anime_idle, ender, tag )
{
	thread anim_reach( guys, anime, tag );

	ent = SpawnStruct();
	ent.reachers = 0;
	foreach ( guy in guys )
	{
		ent.reachers++;
		thread idle_on_reach( guy, anime_idle, ender, tag, ent );
	}

	for ( ;; )
	{
		ent waittill( "reached_position" );
		if ( ent.reachers <= 0 )
			return;
	}
}

wait_for_guy_to_die_or_get_in_position()
{
	self endon( "death" );
	self waittill( "anim_reach_complete" );
}

idle_on_reach( guy, anime_idle, ender, tag, ent )
{
	guy wait_for_guy_to_die_or_get_in_position();
	ent.reachers--;
	ent notify( "reached_position" );

	if ( IsAlive( guy ) )
		anim_loop_solo( guy, anime_idle, ender, tag );
}

get_anim_position( tag )
{
	org = undefined;
	angles = undefined;
	if ( IsDefined( tag ) )
	{
		org = self GetTagOrigin( tag );
		angles = self GetTagAngles( tag );
	}
	else
	{
		org = self.origin;
		angles = self.angles;
	}

	array = [];
	array[ "angles" ] = angles;
	array[ "origin" ] = org;
	return array;
}

/*
=============
///ScriptDocBegin
"Name: anim_reach_together( <guys> , <anime> , <tag> , <animname_override> )"
"Summary: Makes AI reach their anim start points at the same time by adjusting moveplaybackrate"
"Module: Anim"
"CallOn: The scene root"
"MandatoryArg: <guys>: The ai"
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: Optional tag for the root scene"
"OptionalArg: <animname_override>: Optional animname override"
"Example: node anim_reach_together( guys, "scene" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_reach_together( guys, anime, tag, animname_override )
{
	thread modify_moveplaybackrate_together( guys );
	// include the standard begin and end reach functions
	anim_reach_with_funcs( guys, anime, tag, animname_override, ::reach_with_standard_adjustments_begin, ::reach_with_standard_adjustments_end );
}

modify_moveplaybackrate_together( ai )
{
	max_playback = 0.3;

	waittillframeend;// let the guys get their new goals from anim_reach
	for ( ;; )
	{
		ai = remove_dead_from_array( ai );

		dists = [];
		average_dist = 0;
		foreach ( index, guy in ai )
		{
			pos = guy.goalpos;
			if ( IsDefined( guy.reach_goal_pos ) )
			{
				pos = guy.reach_goal_pos;
			}

			//Line( guy.origin, pos, (0,0.3, 1) );

			dist = Distance( guy.origin, pos );
			dists[ guy.unique_id ] = dist;

			if ( dist <= 4 )
			{
				// remove guys that reach their goal
				ai[ index ] = undefined;
				continue;
			}

			average_dist += dist;
		}

		if ( ai.size <= 1 )
			break;

		average_dist /= ai.size;

		foreach ( guy in ai )
		{
			dif = dists[ guy.unique_id ] - average_dist;
			playback = dif * 0.003;
			if ( playback > max_playback )
				playback = max_playback;
			else
			if ( playback < max_playback * -1 )
				playback = max_playback * -1;
			guy.moveplaybackrate = 1 + playback;
		}
		wait( 0.05 );
	}

	foreach ( guy in ai )
	{
		if ( IsAlive( guy ) )
			guy.moveplaybackrate = 1;
	}
}

/*
=============
///ScriptDocBegin
"Name: anim_reach( <guys> , <anime> , <tag> , <animname_override> )"
"Summary:  Make a group of AI run to an animation start position."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guys>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"MandatoryArg: <tag>: "
"OptionalArg: <animname_override>: "
"Example: org anim_reach( guys, "soap_melee_kill" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_reach( guys, anime, tag, animname_override )
{
	// include the standard begin and end reach functions
	anim_reach_with_funcs( guys, anime, tag, animname_override, ::reach_with_standard_adjustments_begin, ::reach_with_standard_adjustments_end );
}

anim_reach_with_funcs( guys, anime, tag, animname_override, start_func, end_func, arrival_type )
{
// 	PrintLn( guy[ 0 ].animname, " doing animation ", anime );
	array = get_anim_position( tag );
	org = array[ "origin" ];
	angles = array[ "angles" ];

	if ( IsDefined( arrival_type ) )
	{
		AssertEx( !isdefined( self.type ), "type already defined" );
		self.type = arrival_type;
		self.arrivalStance = "stand";
	}

	ent = SpawnStruct();
	debugStartpos = false;
	/#
	debugStartpos = GetDebugDvar( "debug_animreach" ) ==  "on";
	#/
	threads = 0;
	foreach ( guy in guys )
	{
		// If there is an animation with this anime then reach the starting spot for that animation
		// otherwise run to the node

		if ( IsDefined( arrival_type ) )
			guy.scriptedarrivalent = self;

		if ( IsDefined( animname_override ) )
			animname = animname_override;
		else
			animname = guy.animname;

		if ( IsDefined( level.scr_anim[ animname ][ anime ] ) )
		{
			if ( IsArray( level.scr_anim[ animname ][ anime ] ) )
				startorg = GetStartOrigin( org, angles, level.scr_anim[ animname ][ anime ][ 0 ] );
			else
				startorg = GetStartOrigin( org, angles, level.scr_anim[ animname ][ anime ] );
		}
		else
		{
			startorg = org;
		}

		/#
		if ( debugStartpos )
			thread debug_message_clear( "x", startorg, 1000, "clearAnimDebug" );
		#/
		threads++;
		guy thread begin_anim_reach( ent, startOrg, start_func, end_func );
	}

	while ( threads )
	{
		ent waittill( "reach_notify" );
		threads--;
	}
	/#
	if ( debugStartpos )
		level notify( "x" + "clearAnimDebug" );
	#/

	foreach ( guy in guys )
	{
		if ( !isalive( guy ) )
			continue;

		guy.goalradius = guy.oldgoalradius;
		guy.scriptedarrivalent = undefined;
		guy.stopAnimDistSq = 0;
	}

	if ( IsDefined( arrival_type ) )
		self.type = undefined;
}

/*
=============
///ScriptDocBegin
"Name: anim_teleport( <guys> , <anime> , <tag> )"
"Summary: Teleport a group of guys to the associated animations start position."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guys>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: "
"Example: org anim_teleport( spawners, "icepick_fight" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_teleport( guys, anime, tag )
{
	pos = get_anim_position( tag );
	org = pos[ "origin" ];
	angles = pos[ "angles" ];

	foreach ( guy in guys )
	{
		startorg = GetStartOrigin( org, angles, level.scr_anim[ guy.animname ][ anime ] );
		startang = GetStartAngles( org, angles, level.scr_anim[ guy.animname ][ anime ] );
		if ( IsAI( guy ) )
			guy Teleport( startorg );
		else
		{
			guy.origin = startorg;
			guy.angles = startang;
		}
	}
}

anim_moveto( guys, anime, tag, time, acceleration_time, deceleration_time )
{
	pos = get_anim_position( tag );
	org = pos[ "origin" ];
	angles = pos[ "angles" ];

	foreach ( guy in guys )
	{
		startorg = GetStartOrigin( org, angles, level.scr_anim[ guy.animname ][ anime ] );
		startang = GetStartAngles( org, angles, level.scr_anim[ guy.animname ][ anime ] );
		if ( IsAI( guy ) )
			AssertMsg( "ai not supported by anim_moveto" );
		else
		{
		    guy MoveTo( startorg, time, acceleration_time, deceleration_time );
		    guy RotateTo( startang, time, acceleration_time, deceleration_time );
		}
	}
}

anim_generic_teleport( guy, anime, tag )
{
	pos = get_anim_position( tag );
	org = pos[ "origin" ];
	angles = pos[ "angles" ];

	startorg = GetStartOrigin( org, angles, level.scr_anim[ "generic" ][ anime ] );
	startang = GetStartAngles( org, angles, level.scr_anim[ "generic" ][ anime ] );
	if ( IsAI( guy ) )
	{
		guy Teleport( startorg );
	}
	else
	{
		guy.origin = startorg;
		guy.angles = startang;
	}
}

anim_spawn_generic_model( model, anime, tag )
{
	return anim_spawn_model( model, "generic", anime, tag );
}

anim_spawn_model( model, animname, anime, tag )
{
	pos = get_anim_position( tag );
	org = pos[ "origin" ];
	angles = pos[ "angles" ];
	startorg = GetStartOrigin( org, angles, level.scr_anim[ animname ][ anime ] );
	startangles = GetStartOrigin( org, angles, level.scr_anim[ animname ][ anime ] );

	spawned = Spawn( "script_model", startorg );
	spawned SetModel( model );
	spawned.angles = startangles;
	return spawned;
}

/*
=============
///ScriptDocBegin
"Name: anim_spawn_tag_model( <model> , <tag> )"
"Summary: Attaches a model to a tag, wraps Attach()"
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <model>: "
"MandatoryArg: <tag>: "
"Example: price anim_spawn_tag_model( "weapon_ice_picker", "tag_inhand" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_spawn_tag_model( model, tag )
{
	// org = self GetTagOrigin( tag );
	//spawned = Spawn( "script_model", org );
	//spawned SetModel( model );
	//spawned LinkTo( self, tag, (0,0,0), (0,0,0) );
	self Attach( model, tag );
//	return spawned;
}

/*
=============
///ScriptDocBegin
"Name: anim_link_tag_model( <model> , <tag> )"
"Summary: Create a new model entity and link it to the tag model."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <model>: "
"MandatoryArg: <tag>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_link_tag_model( model, tag )
{
	org = self GetTagOrigin( tag );
	spawned = Spawn( "script_model", org );
	spawned SetModel( model );
	spawned LinkTo( self, tag, ( 0, 0, 0 ), ( 0, 0, 0 ) );
	return spawned;
}

/*
=============
///ScriptDocBegin
"Name: anim_spawner_teleport( <guys> , <anime> , <tag> )"
"Summary: I don't know.."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guys>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"MandatoryArg: <tag>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_spawner_teleport( guys, anime, tag )
{
	pos = get_anim_position( tag );
	org = pos[ "origin" ];
	angles = pos[ "angles" ];

	ent = SpawnStruct();

	foreach ( guy in guys )
	{
		startorg = GetStartOrigin( org, angles, level.scr_anim[ guy.animname ][ anime ] );
		guy.origin = startorg;
	}
}

reach_death_notify( ent )
{
	self waittill_either( "death", "goal" );
	ent notify( "reach_notify" );
}

begin_anim_reach( ent, startOrg, start_func, end_func )
{
	self endon( "death" );
	self endon( "new_anim_reach" );
	thread reach_death_notify( ent );
	startorg = [[ start_func ]]( startorg );

	self set_goal_pos( startorg );// setgoalpos
	self.reach_goal_pos = startorg;
	self.goalradius = 0;
	self.stopAnimDistSq = squared( 64 );	// get a "stop_soon" notify when within this distance to goal, but don't slow down

	self waittill( "goal" );

	self notify( "anim_reach_complete" );

	[[ end_func ]]();

	self notify( "new_anim_reach" );
}

reach_with_standard_adjustments_begin( startorg )
{
	self.oldgoalradius = self.goalradius;
	self.oldpathenemyFightdist = self.pathenemyFightdist;
	self.oldpathenemyLookahead = self.pathenemyLookahead;
	self.pathenemyfightdist = 128;
	self.pathenemylookahead = 128;
	disable_ai_color();
	self anim_changes_pushplayer( true );
	self.nododgemove = true;
	self.fixedNodeWasOn = self.fixedNode;
	self.fixednode = false;
	
	if ( !isdefined( self.scriptedArrivalEnt ) )
	{
		self.old_disablearrivals = self.disablearrivals;
		self.disablearrivals = true;
	}
	self.reach_goal_pos = undefined;
	return startorg;
}

reach_with_standard_adjustments_end()
{
	self anim_changes_pushplayer( false );
		
	self.nododgemove = false;
	self.fixednode = self.fixedNodeWasOn;
	self.fixedNodeWasOn = undefined;

	self.pathenemyfightdist = self.oldpathenemyFightdist;
	self.pathenemylookahead = self.oldpathenemyLookahead;
	self.disablearrivals = self.old_disablearrivals;
}

anim_changes_pushplayer( value )
{
/*
=============
///ScriptFieldDocBegin
"Name: .dontchangepushplayer"
"Summary: dontchangepushplayer -> set to true to make sure animscripts dont turn off push player, set to undefined for default behavior"
"Module: Anim"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
	if( isdefined( self.dontchangepushplayer ) )
		assert( self.dontchangepushplayer == true );
	else
		self pushplayer( value );	
}

reach_with_arrivals_begin( startorg )
{
	startorg = reach_with_standard_adjustments_begin( startorg );
	self.disablearrivals = false;
	return startorg;
}


reach_with_planting( startorg )
{
	newOrigin = self GetDropToFloorPosition( startorg );
	Assert( IsDefined( newOrigin ) );
	startorg = newOrigin;

	startorg = reach_with_standard_adjustments_begin( startorg );
	self.disablearrivals = true;
	return startorg;
}

reach_with_planting_and_arrivals( startorg )
{
	newOrigin = self GetDropToFloorPosition( startorg );
	Assert( IsDefined( newOrigin ) );
	startorg = newOrigin;

	startorg = reach_with_standard_adjustments_begin( startorg );
	self.disablearrivals = false;
	return startorg;
}

/#
printloops( guy, anime )
{
// 	wait( 0.05 );
	if ( !isdefined( guy ) )
		return;

	guy endon( "death" );// could die during the frame
	waittillframeend;// delay a frame so if you end a loop with a notify then start a new loop, this guarentees that
	                 // the 2nd loop doesnt start before the loop decrementer receives the same notify that ended the first loop
	guy.loops++;
	if ( guy.loops > 1 )
		AssertMsg( "guy with name " + guy.animname + " has " + guy.loops + " looping animations played, anime: " + anime );
}

looping_anim_ender( guy, ender )
{
	guy endon( "death" );
	self waittill( ender );
	guy.loops--;
}
#/


/*
=============
///ScriptDocBegin
"Name: SetAnimTree()"
"Summary: Set the animtree associated with the callers animname."
"Module: Anim"
"CallOn: An entity"
"Example: fridge setAnimTree();"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
SetAnimTree()
{
	self UseAnimTree( level.scr_animtree[ self.animname ] );
}

/*
=============
///ScriptDocBegin
"Name: anim_single_solo( <guy> , <anime> , <tag>, <anim_end_time>, <animname_override> )"
"Summary: Do an anim on a guy from level.scr_anim[ animname ][ anime ]"
"Module: Anim"
"CallOn: The base for an animation scene, such as a node"
"MandatoryArg: <guy>: Guy that animates"
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: A tag to animate relative to"
"OptionalArg: <anim_end_time>: The amount of time to end the animation early"
"OptionalArg: <animname_override>: Overrides the animname of the guys animating"
"Example: level.price anim_single_solo( level.price, "whip_it_good" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_single_solo( guy, anime, tag, anim_end_time, animname_override )
{
	self endon( "death" );

	newguy[ 0 ] = guy;
	if ( !isdefined( anim_end_time ) )
		anim_end_time = 0;
	anim_single( newguy, anime, tag, anim_end_time, animname_override );
}

/*
=============
///ScriptDocBegin
"Name: anim_single_solo_run( <guy> , <anime> , <tag> )"
"Summary: Do an anim on a guy from level.scr_anim[ animname ][ anime ] and end the anim early so he goes into a run smoothly."
"Module: Anim"
"CallOn: The base for an animation scene, such as a node"
"MandatoryArg: <guy>: Guy that animates"
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: A tag to animate relative to"
"Example: level.price anim_single_solo_run( level.price, "whip_it_good" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_single_solo_run( guy, anime, tag )
{
	self endon( "death" );
	newguy[ 0 ] = guy;
	anim_single( newguy, anime, tag, CONST_anim_end_time );
}



/*
=============
///ScriptDocBegin
"Name: anim_single_run_solo( <guy> , <anime> , <tag> )"
"Summary: Like anim_single_solo except the anim blends out early so it can blend into a run."
"Module: Anim"
"CallOn: The base for an animation scene, such as a node"
"MandatoryArg: <guy>: Guy that animates"
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: A tag to animate relative to"
"Example: level.price anim_single_solo( level.price, "whip_it_good" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_single_run_solo( guy, anime, tag, anim_end_time )
{
	self endon( "death" );

	newguy[ 0 ] = guy;
	anim_single( newguy, anime, tag, CONST_anim_end_time );
}

/*
=============
///ScriptDocBegin
"Name: anim_reach_and_idle_solo( <guy> , <anime> , <anime_idle> , <ender> , <tag> )"
"Summary: Make a Single AI run to an animation start and loop the anim."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guy>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"MandatoryArg: <anime_idle>: "
"MandatoryArg: <ender>: "
"MandatoryArg: <tag>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_reach_and_idle_solo( guy, anime, anime_idle, ender, tag )
{
	self endon( "death" );

	newguy[ 0 ] = guy;
	anim_reach_and_idle( newguy, anime, anime_idle, ender, tag );
}

/*
=============
///ScriptDocBegin
"Name: anim_reach_solo( <guy> , <anime> , <tag> )"
"Summary: Make one AI run to an animation start."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guy>: ai to reach the node"
"OptionalArg: <anime>: name of the anim scene"
"Example: locker_brawl anim_reach_solo( level.price, "locker_brawl" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_reach_solo( guy, anime, tag )
{
	self endon( "death" );

	newguy[ 0 ] = guy;
	anim_reach( newguy, anime, tag );
}

/*
=============
///ScriptDocBegin
"Name: anim_reach_and_approach_solo( <guy> , <anime> , <tag> , <arrival_type> )"
"Summary: Make one AI run to an animation offset with an arrival"
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guy>: Guy that animates"
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: A tag to animate relative to"
"OptionalArg: <arrival_type>: If start of the scripted animation matches a cover node pose, set this to do an arrival. Possible values 'Cover Right', 'Cover Left', 'Cover Stand', 'Cover Crouch'"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_reach_and_approach_solo( guy, anime, tag, arrival_type )
{
	self endon( "death" );

	newguy[ 0 ] = guy;
	anim_reach_and_approach( newguy, anime, tag, arrival_type );
}

/*
=============
///ScriptDocBegin
"Name: anim_reach_and_approach_node_solo( <guy> , <anime> , <tag> )"
"Summary: anim_reach_and_approach_node_solo"
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guy>: Guy that animates"
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: A tag to animate relative to"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_reach_and_approach_node_solo( guy, anime, tag )
{
	self endon( "death" );

	newguy[ 0 ] = guy;

	arrivalEnt = Spawn( "script_origin", self.origin );
	arrivalEnt.type = self.type;
	arrivalEnt.angles = self.angles;
	arrivalEnt.arrivalStance = self GetHighestNodeStance();

	guy.scriptedarrivalent = arrivalEnt;
	anim_reach_and_approach( newguy, anime, tag );
	guy.scriptedarrivalent = undefined;

	arrivalEnt Delete();

	while ( guy.a.movement != "stop" )
		wait 0.05;
}

/*
=============
///ScriptDocBegin
"Name: anim_reach_and_approach( <guys> , <anime> , <tag> , <arrival_type> )"
"Summary: Make a group of AI run to an animation offset with an arrival"
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guy>: Guys that animate"
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: A tag to animate relative to"
"OptionalArg: <arrival_type>: If start of the scripted animation matches a cover node pose, set this to do an arrival. Possible values 'Cover Right', 'Cover Left', 'Cover Stand', 'Cover Crouch'"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_reach_and_approach( guys, anime, tag, arrival_type )
{
	self endon( "death" );

	anim_reach_with_funcs( guys, anime, tag, undefined, ::reach_with_arrivals_begin, ::reach_with_standard_adjustments_end, arrival_type );
}

/*
=============
///ScriptDocBegin
"Name: anim_loop_solo( <guy> , <anime> , <ender> , <tag> )"
"Summary: An actor or script_model does a looping animation in sync to an optional tag or model. "
"Module: Anim"
"CallOn: An entity or node that will be the root of the animation"
"MandatoryArg: <guy>: Entity that will animate "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <ender>: The loops will stop reoccurring if this is notified to the root entity."
"OptionalArg: <tag>: An optional tag that the scene is relative to"
"Example: node thread anim_loop_solo( guy, "wounded_idle" );"
///ScriptDocEnd
=============
*/

anim_loop_solo( guy, anime, ender, tag )
{
	self endon( "death" );
	guy endon( "death" );

	newguy[ 0 ] = guy;
	anim_loop( newguy, anime, ender, tag );
}

/*
=============
///ScriptDocBegin
"Name: anim_teleport_solo( <guy> , <anime> , <tag> )"
"Summary: Teleport a guy to the associated animations start position."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guy>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"MandatoryArg: <tag>: "
"Example: waveNode anim_teleport_solo( level.soap, "run_and_wave" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_teleport_solo( guy, anime, tag )
{
	self endon( "death" );

	newguy[ 0 ] = guy;
	anim_teleport( newguy, anime, tag );
}

/*
=============
///ScriptDocBegin
"Name: add_animation( <animname> , <anime> )"
"Summary: add_animation"
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <animname>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

add_animation( animname, anime )
{
	if ( !isdefined( level.completedAnims ) )
		level.completedAnims[ animname ][ 0 ] = anime;
	else
	{
		if ( !isdefined( level.completedAnims[ animname ] ) )
			level.completedAnims[ animname ][ 0 ] = anime;
		else
		{
			for ( i = 0; i < level.completedAnims[ animname ].size; i++ )
			{
				if ( level.completedAnims[ animname ][ i ] == anime )
					return;
			}

			level.completedAnims[ animname ][ level.completedAnims[ animname ].size ] = anime;
		}
	}
}


/*
=============
///ScriptDocBegin
"Name: anim_single_queue( <guy> , <anime> , <tag> , <anim_end_time> )"
"Summary: anim single, queued!"
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guy>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"MandatoryArg: <tag>: "
"MandatoryArg: <anim_end_time>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_single_queue( guy, anime, tag, anim_end_time )
{
	if ( !isdefined( anim_end_time ) )
		anim_end_time = 0;
	AssertEx( IsDefined( anime ), "Tried to do anim_single_queue without passing a scene name (anime)" );

	if ( IsDefined( guy.last_queue_time ) )
	{
		wait_for_buffer_time_to_pass( guy.last_queue_time, 0.5 );
	}

	function_stack( ::anim_single_solo, guy, anime, tag, anim_end_time );
	

	if ( IsAlive( guy ) )
		guy.last_queue_time = GetTime();
}

/*
=============
///ScriptDocBegin
"Name: anim_generic_queue( <guy> , <anime> , <tag> , <anim_end_time>, <timeout> )"
"Summary: queues anim_generic - Makes an AI play a generic anim. The calling ent notifies itself the name of the animation scene when it completes."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guy>: guy to animate"
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <tag>: An optional tag that the scene is relative to"
"OptionalArg: <anim_end_time>: The amount of time to end the animation early"
"OptionalArg: <timeout>: optional timeout to forget the radio dialogue if it's been in the queue for longer than this many seconds"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_generic_queue( guy, anime, tag, anim_end_time, timeout )
{
	guy endon( "death" );
	if ( !isdefined( anim_end_time ) )
		anim_end_time = 0;
	AssertEx( IsDefined( anime ), "Tried to do anim_single_queue without passing a scene name (anime)" );

	if ( IsDefined( guy.last_queue_time ) )
	{
		wait_for_buffer_time_to_pass( guy.last_queue_time, 0.5 );
	}
	
	if( isdefined( timeout ) )
		function_stack_timeout( timeout, ::anim_single_solo, guy, anime, tag, anim_end_time, "generic" );
	else
		function_stack( ::anim_single_solo, guy, anime, tag, anim_end_time, "generic" );

	if ( IsAlive( guy ) )
		guy.last_queue_time = GetTime();
}

/*
=============
///ScriptDocBegin
"Name: anim_dontPushPlayer( <guys> )"
"Summary: Makes the guys in an animation scene not push the player. "
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guys>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_dontPushPlayer( guys )
{
	foreach ( guy in guys )
	{
		guy PushPlayer( false );
	}
}

/*
=============
///ScriptDocBegin
"Name: anim_pushPlayer( <guys> )"
"Summary: Makes the guys in an animation scene push the player."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <guys>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_pushPlayer( guys )
{
	foreach ( guy in guys )
	{
		guy PushPlayer( true );
	}
}

/*
=============
///ScriptDocBegin
"Name: addNotetrack_dialogue( <animname> , <notetrack> , <scene> , <soundalias> )"
"Summary: Makes a dialogue sound play on a certain notetrack. If you put multiple dialogue notetracks in an anim, it will play them in the order you do addNotetrack."
"Module: Anim"
"MandatoryArg: <animname>: The animname of the character, or generic. "
"MandatoryArg: <notetrack>: The notetrack in the anim, usual dialog. "
"MandatoryArg: <scene>: The scene the sound plays in. "
"MandatoryArg: <soundalias>: The soundalias. "
"Example: addNotetrack_dialogue( "price", "dialog", "wounded_begins", "sniperescape_mcm_choppergetback" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
addNotetrack_dialogue( animname, notetrack, anime, soundalias )
{
	notetrack = ToLower( notetrack );
	/#
	assertex( AnimHasNotetrack( level.scr_anim[ animname ][ anime ], notetrack ), "Animation lacks notetrack " + notetrack );
	#/

	anime = get_generic_anime( anime );
	index = add_notetrack_and_get_index( animname, notetrack, anime );

	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ] = [];
	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ][ "dialog" ] = soundalias;
}

add_notetrack_and_get_index( animname, notetrack, anime )
{
	notetrack = ToLower( notetrack );// notetracks get converted to lowercase before they reach script
	add_notetrack_array( animname, notetrack, anime );
	return level.scr_notetrack[ animname ][ anime ][ notetrack ].size;
}

add_notetrack_array( animname, notetrack, anime )
{
	notetrack = ToLower( notetrack );

	if ( !isdefined( level.scr_notetrack ) )
		level.scr_notetrack = [];

	if ( !isdefined( level.scr_notetrack[ animname ] ) )
		level.scr_notetrack[ animname ] = [];

	if ( !isdefined( level.scr_notetrack[ animname ][ anime ] ) )
		level.scr_notetrack[ animname ][ anime ] = [];

	if ( !isdefined( level.scr_notetrack[ animname ][ anime ][ notetrack ] ) )
		level.scr_notetrack[ animname ][ anime ][ notetrack ] = [];
}


/*
=============
///ScriptDocBegin
"Name: addNotetrack_sound( <animname> , <notetrack> , <scene> , <soundalias> )"
"Summary: Makes a sound play on a certain notetrack. "
"Module: Anim"
"MandatoryArg: <animname>: The animname of the character, or generic. "
"MandatoryArg: <notetrack>: The notetrack in the anim, usual dialog. "
"MandatoryArg: <scene>: The scene the sound plays in. "
"MandatoryArg: <soundalias>: The soundalias. "
"Example: addNotetrack_sound( "price", "dialog", "wounded_begins", "sniperescape_mcm_choppergetback" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
addNotetrack_sound( animname, notetrack, anime, soundalias )
{
	notetrack = ToLower( notetrack );

	anime = get_generic_anime( anime );
	index = add_notetrack_and_get_index( animname, notetrack, anime );

	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ] = [];
	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ][ "sound" ] = soundalias;
}

get_generic_anime( anime )
{
	if ( !isdefined( anime ) )
		return "any";
	return anime;
}

addOnStart_animSound( animname, anime, soundalias )
{
	// only sounds generated by animSound should call this
	if ( !isdefined( level.scr_animSound[ animname ] ) )
		level.scr_animSound[ animname ] = [];

	level.scr_animSound[ animname ][ anime ] = soundalias;
}

/*
=============
///ScriptDocBegin
"Name: addNotetrack_animSound( <animname> , <anime> , <notetrack> , <soundalias> )"
"Summary: Associates a Sound with a notetrack on an animation scene"
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <animname>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"MandatoryArg: <notetrack>: "
"MandatoryArg: <soundalias>: "
"Example: addNotetrack_animSound( "price", "price_jump", "scn_cliffhanger_price_jump_dx", "scn_cliffhanger_price_jump_dx" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

addNotetrack_animSound( animname, anime, notetrack, soundalias )
{
	notetrack = ToLower( notetrack );

	anime = get_generic_anime( anime );
	index = add_notetrack_and_get_index( animname, notetrack, anime );

	array = [];
	array[ "sound" ] = soundalias;
	array[ "created_by_animSound" ] = true;

	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ] = array;
}


/*
=============
///ScriptDocBegin
"Name: addNotetrack_attach( <animname> , <notetrack> , <model> , <tag> , <anime> )"
"Summary: Associates a notetrack to attach a model on."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <animname>: "
"MandatoryArg: <notetrack>: "
"MandatoryArg: <model>: "
"MandatoryArg: <tag>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"Example: addNotetrack_attach( "generic", "attach knife right", "weapon_parabolic_knife", "TAG_INHAND" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
addNotetrack_attach( animname, notetrack, model, tag, anime )
{
	notetrack = ToLower( notetrack );

	anime = get_generic_anime( anime );
	index = add_notetrack_and_get_index( animname, notetrack, anime );

	array = [];
	array[ "attach model" ] = model;
	array[ "selftag" ] = tag;

	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ] = array;
}

/*
=============
///ScriptDocBegin
"Name: addNotetrack_detach( <animname> , <notetrack> , <model> , <tag> , <anime> )"
"Summary: Associates a notetrack to detach a model on."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <animname>: "
"MandatoryArg: <notetrack>: "
"MandatoryArg: <model>: "
"MandatoryArg: <tag>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"Example: addNotetrack_detach( "player_rig", "vision_effect" , "weapon_commando_knife", "TAG_WEAPON_LEFT", "turn_buckle" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

addNotetrack_detach( animname, notetrack, model, tag, anime )
{
	notetrack = ToLower( notetrack );

	anime = get_generic_anime( anime );
	index = add_notetrack_and_get_index( animname, notetrack, anime );

	array = [];
	array[ "detach model" ] = model;
	array[ "selftag" ] = tag;

	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ] = array;
}

/*
=============
///ScriptDocBegin
"Name: addNotetrack_detach_gun( <animname>, <notetrack>, <anime>, [suspend] )"
"Summary: Detaches the gun on the given notetrack"
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <animname>: "
"MandatoryArg: <notetrack>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"OptionalArg: <suspend>: Determine if the weapon that is spawned in the gun's position will suspend or not, default is false."
"Example: addNotetrack_detach_gun( "generic", "detach gun", "melee_scene" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
addNotetrack_detach_gun( animname, notetrack, anime, suspend )
{
	notetrack = ToLower( notetrack );

	anime = get_generic_anime( anime );
	index = add_notetrack_and_get_index( animname, notetrack, anime );

	array = [];
	array[ "detach gun" ] = true;
	array[ "tag" ] = "tag_weapon_right";

	if ( IsDefined( suspend ) )
	{
		array[ "suspend" ] = suspend;
	}

	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ] = array;
}

/*
=============
///ScriptDocBegin
"Name: addNotetrack_customFunction( <animname>, <notetrack> , <function> , <anime> )"
"Summary: Makes the function run when this notetrack is hit. The SELF of the function is the scene base, the PARM of the function is the guy that hit the notetrack."
"Module: Anim"
"MandatoryArg: <animname>: Animname of the scene "
"MandatoryArg: <notetrack>: Duh"
"MandatoryArg: <function>: Duh part 2 "
"OptionalArg: <anime>: The scene. If left blank, will occur on all scenes."
"Example: 	addNotetrack_customFunction( "zpu_gun", "fire_1", ::zpu_shoot1 ); "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
addNotetrack_customFunction( animname, notetrack, function, anime )
{
	notetrack = ToLower( notetrack );
	/#
	if ( isdefined( anime ) )
	{
		if ( isdefined( level.scr_anim[ animname ][ anime ] ) )
			assertex( IsArray( level.scr_anim[ animname ][ anime ] ) || AnimHasNotetrack( level.scr_anim[ animname ][ anime ], notetrack ), "Animation lacks notetrack " + notetrack );
	}
	#/
	anime = get_generic_anime( anime );
	index = add_notetrack_and_get_index( animname, notetrack, anime );

	array = [];
	array[ "function" ] = function;

	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ] = array;
}


/*
=============
///ScriptDocBegin
"Name: addNotetrack_startFXonTag( <animname> , <notetrack> , <anime> , <effect_name> , <tagname> )"
"Summary: "
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <animname>: Animname of the scene "
"MandatoryArg: <notetrack>: The notetrack in the anims. "
"MandatoryArg: <anime>: "
"MandatoryArg: <effect_name>: "
"MandatoryArg: <tagname>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

addNotetrack_startFXonTag( animname, notetrack, anime, effect_name, tagname )
{
    //for assertion
    getfx( effect_name );
   
	notetrack = ToLower( notetrack );
	/#
	if ( isdefined( anime ) )
	{
		if ( isdefined( level.scr_anim[ animname ][ anime ] ) )
			assertex( AnimHasNotetrack( level.scr_anim[ animname ][ anime ], notetrack ), "Animation lacks notetrack " + notetrack );
	}
	#/
	anime = get_generic_anime( anime );
	index = add_notetrack_and_get_index( animname, notetrack, anime );

	array = [];
	array[ "effect" ] = effect_name;
	array[ "selftag" ] = tagname;
	
	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ] = array;
}


/*
=============
///ScriptDocBegin
"Name: addNotetrack_stopFXonTag( <animname> , <notetrack> , <anime> , <effect_name> , <tagname> )"
"Summary: Associates a notetrack to start an effect on a tag on."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <animname>: Animname of the scene "
"MandatoryArg: <notetrack>: The notetrack in the anim. "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"MandatoryArg: <effect_name>: "
"MandatoryArg: <tagname>: "
"Example: addNotetrack_startFXonTag( "train_car1", "sparks_start", "train_crash", "sparks_subway_scrape_line", "TAG_BOTTOM_FX" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

addNotetrack_stopFXonTag( animname, notetrack, anime, effect_name, tagname )
{
    //for assertion
    getfx( effect_name );
   
	notetrack = ToLower( notetrack );
	/#
	if ( isdefined( anime ) )
	{
		if ( isdefined( level.scr_anim[ animname ][ anime ] ) )
			assertex( AnimHasNotetrack( level.scr_anim[ animname ][ anime ], notetrack ), "Animation lacks notetrack " + notetrack );
	}
	#/
	anime = get_generic_anime( anime );
	index = add_notetrack_and_get_index( animname, notetrack, anime );

	array = [];
	array[ "stop_effect" ] = effect_name;
	array[ "selftag" ] = tagname;
	
	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ] = array;
}


/*
=============
///ScriptDocBegin
"Name: addNotetrack_flag( <animname> , <notetrack> , <theFlag> , <anime> )"
"Summary: Associates a notetrack to set a level flag on."
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <animname>: "
"MandatoryArg: <notetrack>: "
"MandatoryArg: <theFlag>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"Example:  addNotetrack_flag( "van_mate" , "dialog" , "end_get_in_the_van" , "end_get_in" );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

addNotetrack_flag( animname, notetrack, theFlag, anime )
{
	notetrack = ToLower( notetrack );
	anime = get_generic_anime( anime );
	index = add_notetrack_and_get_index( animname, notetrack, anime );

	array = [];
	array[ "flag" ] = theFlag;

	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ] = array;

	if ( !isdefined( level.flag ) || !isdefined( level.flag[ theFlag ] ) )
	{
		flag_init( theFlag );
	}
}

/*
=============
///ScriptDocBegin
"Name: addNotetrack_flag_clear( <animname> , <notetrack> , <theFlag> , <anime> )"
"Summary: Associates a notetrack to clear a level flag on.""
"Module: Anim"
"CallOn: An entity"
"MandatoryArg: <animname>: "
"MandatoryArg: <notetrack>: "
"MandatoryArg: <theFlag>: "
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

addNotetrack_flag_clear( animname, notetrack, theFlag, anime )
{
	notetrack = ToLower( notetrack );
	anime = get_generic_anime( anime );
	index = add_notetrack_and_get_index( animname, notetrack, anime );

	array = [];
	array[ "flag_clear" ] = theFlag;

	level.scr_notetrack[ animname ][ anime ][ notetrack ][ index ] = array;

	if ( !isdefined( level.flag ) || !isdefined( level.flag[ theFlag ] ) )
	{
		flag_init( theFlag );
	}
}

#using_animtree( "generic_human" );

anim_facialAnim( guy, anime, faceanim )
{

	guy endon( "death" );
	self endon( anime );
	changeTime = 0.05;
	// must wait because animscripted starts the main animation and we have to wait until its started
// 	guy SetAnim( %scripted, 0.01, 0.3, 1 );

	guy notify( "newLookTarget" );

	waittillframeend;// in case another facial animation just ended, so its clear doesnt overwrite us

	guy SetAnim( %scripted_talking, 5, 0.2 );
	guy SetFlaggedAnimKnobRestart( "face_done_" + anime, faceanim, 1, 0, 1 );
	thread force_face_anim_to_play( guy, anime, faceanim );
	
	thread clearFaceAnimOnAnimdone( guy, "face_done_" + anime, anime );
}

force_face_anim_to_play( guy, anime, faceanim )
{
	guy endon( "death" );
	guy endon( "stop_loop" );
	self endon( anime );
	
	for ( ;; )
	{
		guy SetAnim( %scripted_talking, 5, 0.4 );
		guy SetFlaggedAnimKnobLimited( "face_done_" + anime, faceanim, 1, 0, 1 );
		wait( 0.05 );
	}
}

anim_facialFiller( msg, lookTarget )
{
	self endon( "death" );

	changeTime = 0.05;
	// must wait because animscripted starts the main animation and we have to wait until its started
// 	guy SetAnim( %scripted, 0.01, 0.3, 1 );

	self notify( "newLookTarget" );
	self endon( "newLookTarget" );

	waittillframeend;// in case another facial animation just ended, so its clear doesnt overwrite us

	 /* 
	quick = false;
	if ( !isdefined( looktarget ) )
	{
		guy[ 0 ] = self;
		lookTarget = get_closest_ai_exclude( self.origin, self.team, guy );
		if ( IsDefined( looktarget ) )
			quick = true;
	}
	 */ 
	if ( !isdefined( looktarget ) && IsDefined( self.looktarget ) )
		looktarget = self.looktarget;

	talkAnim = %generic_talker_allies;
	if ( self IsBadGuy() )
		talkAnim = %generic_talker_axis;

	Assert( IsAlive( self ) );// or else we shouldn't start talking!
	self SetAnimKnobLimitedRestart( talkAnim, 1, 0, 1 );
	self SetAnim( %scripted_talking, 5, 0.4 );

	self set_talker_until_msg( msg, talkanim );

	changeTime = 0.3;
	self ClearAnim( %scripted_talking, 0.2 );
}

set_talker_until_msg( msg, talkanim )
{
	self endon( msg );
	for ( ;; )
	{
		wait( 0.2 );

		self SetAnimKnobLimited( talkAnim, 1, 0, 1 );
		self SetAnim( %scripted_talking, 5, 0.4 );
	}
}


talk_for_time( timer )
{
	self endon( "death" );
	talkAnim = %generic_talker_allies;
	if ( self IsBadGuy() )
		talkAnim = %generic_talker_axis;

	self SetAnimKnobLimitedRestart( talkAnim, 1, 0, 1 );
	self SetAnim( %scripted_talking, 5, 0.4 );

	wait( timer );
	changeTime = 0.3;
	self ClearAnim( %scripted_talking, 0.2 );
}

GetYawAngles( angles1, angles2 )
{
	yaw = angles1[ 1 ] - angles2[ 1 ];
	yaw = AngleClamp180( yaw );
	return yaw;
}

lookLine( org, msg )
{
	self notify( "lookline" );
	self endon( "lookline" );
	self endon( msg );
	self endon( "death" );
	for ( ;; )
	{
		Line( self GetEye(), org + ( 0, 0, 60 ), ( 1, 1, 0 ), 1 );
		wait( 0.05 );
	}
}

anim_reach_idle( guys, anime, idle )
{
	// Makes an array of guys go to the right spot relative to an animation
	// all but the last guy will idle there, so you do anim_reach_idle then anim_loop
	ent = SpawnStruct();
	ent.count = guys.size;
	foreach ( guy in guys )
		thread reachIdle( guy, anime, idle, ent );
	while ( ent.count )
		ent waittill( "reached_goal" );

	self notify( "stopReachIdle" );
}

reachIdle( guy, anime, idle, ent )
{
	anim_reach_solo( guy, anime );
	ent.count--;
	ent notify( "reached_goal" );
	if ( ent.count > 0 )
		anim_loop_solo( guy, idle, "stopReachIdle" );
}

delayedDialogue( anime, doAnimation, dialogue, animationName )
{
	if ( AnimHasNotetrack( animationName, "dialog" ) )
	{
		self waittillmatch( "face_done_" + anime, "dialog" );
	}
	
	if ( doAnimation )
		self SaySpecificDialogue( undefined, dialogue, 1.0 );
	else
		self SaySpecificDialogue( undefined, dialogue, 1.0, "single dialogue" );
}

clearFaceAnimOnAnimdone( guy, msg, anime )
{
	guy endon( "death" );
// 	self waittill( anime );
	guy waittillmatch( msg, "end" );
	changeTime = 0.3;
	guy ClearAnim( %scripted_talking, 0.2 );
}

anim_start_pos( guyArray, anime, tag )
{
	pos = get_anim_position( tag );
	org = pos[ "origin" ];
	angles = pos[ "angles" ];

	array_thread( guyArray, ::set_start_pos, anime, org, angles );
}

anim_start_pos_solo( guy, anime, tag )
{
	newguy[ 0 ] = guy;
	anim_start_pos( newguy, anime, tag );
}

set_start_pos( anime, org, angles, animname_override, anim_array )
{
	animname = undefined;
	if ( IsDefined( animname_override ) )
		animname = animname_override;
	else
		animname = self.animname;

	if ( IsDefined( anim_array ) && anim_array )
		animation = level.scr_anim[ animname ][ anime ][ 0 ];
	else
		animation = level.scr_anim[ animname ][ anime ];

	if ( IsAI( self ) )
	{
		neworg = GetStartOrigin( org, angles, animation );
		newangles = GetStartAngles( org, angles, animation );
		
		// if we're about to use animmode "gravity", not snapping to the groundpos can cause a vertical pop at the start of the anim
		if ( IsDefined( self.anim_start_at_groundpos ) )
		{
			neworg = groundpos( neworg );
		}
		
		self ForceTeleport( neworg, newangles );
	}
	else if ( self.code_classname == "script_vehicle" )
	{
		self Vehicle_Teleport( GetStartOrigin( org, angles, animation ), GetStartAngles( org, angles, animation ) );
	}
	else
	{
		self.origin = GetStartOrigin( org, angles, animation );
		self.angles = GetStartAngles( org, angles, animation );
	}
}


anim_at_self( entity, tag )
{
	packet = [];
	packet[ "guy" ] = self;
	packet[ "entity" ] = self;
	return packet;
}

anim_at_entity( entity, tag )
{
	packet = [];
	packet[ "guy" ] = self;
	packet[ "entity" ] = entity;
	packet[ "tag" ] = tag;
	return packet;
}

add_to_animsound()
{
	if ( !isdefined( self.animSounds ) )
	{
		self.animSounds = [];
	}

	isInArray = false;
	for ( i = 0; i < level.animSounds.size; i++ )
	{
		if ( self == level.animSounds[ i ] )
		{
			isInArray = true;
			break;
		}
	}
	if ( !isInArray )
	{
		level.animSounds[ level.animSounds.size ] = self;
	}
}

/*
=============
///ScriptDocBegin
"Name: anim_set_rate_single( <guy> , <anime> , <rate> )"
"Summary: Sets the rate that guy is playing an animation"
"Module: Anim"
"MandatoryArg: <guys>: Stuff that is doing anim_single, anim_generic, or anim_single_solo"
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"MandatoryArg: <rate>: The rate to change to"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

anim_set_rate_single( guy, anime, rate )
{
	guy thread anim_set_rate_internal( anime, rate );
}

/*
=============
///ScriptDocBegin
"Name: anim_set_rate( <guys> , <anime> , <rate> )"
"Summary: Sets the rate that guys are playing an animation"
"Module: Anim"
"MandatoryArg: <guys>: Stuff that is doing anim_single, anim_generic, or anim_single_solo"
"MandatoryArg: <anime>: The animation scene as defined in the map_anim.gsc file "
"MandatoryArg: <rate>: The rate to change to"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_set_rate( guys, anime, rate )
{
	array_thread( guys, ::anim_set_rate_internal, anime, rate );
}

anim_set_rate_internal( anime, rate, animname_override )
{
	animname = undefined;
	if ( IsDefined( animname_override ) )
		animname = animname_override;
	else
		animname = self.animname;

	self SetFlaggedAnim( "single anim", getanim_from_animname( anime, animname ), 1, 0, rate );
}

/*
=============
///ScriptDocBegin
"Name: anim_set_time( <guys> , <anime> , <time> )"
"Summary: Sets the current time of an anim, but should be done at least 0.05 seconds after the anim is calle"
"Module: Anim"
"CallOn: Array of guys animating"
"MandatoryArg: <guys>: Guys animating"
"MandatoryArg: <amime>: Scene name"
"MandatoryArg: <time>: Time to set to"
"Example: delayThread( 0.05, ::anim_set_time, guy_and_door, "fire_3", 1.0 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
anim_set_time( guys, anime, time )
{
	array_thread( guys, ::anim_self_set_time, anime, time );
}

anim_self_set_time( anime, time )
{
	animation = self getanim( anime );
	self SetAnimTime( animation, time );
}

last_anim_time_check()
{

	if ( !isdefined( self.last_anim_time ) )
	{
		self.last_anim_time = GetTime();
		return;
	}

	time = GetTime();
	//AssertEx( self.last_anim_time != time, "Tried to do animscripted twice in one frame. This is not supported." );
	if ( self.last_anim_time == time )
	{
		// can't call 2 animscripteds on one frame
		// check this in after e3 build
		self endon( "death" );
		wait( 0.05 );
	}
	self.last_anim_time = time;
}


/*
=============
///ScriptDocBegin
"Name: set_custom_move_start_transition( <guy> , <anime> )"
"Summary: Sets a custom move start transition. Resets after move starts"
"Module: Anim"
"CallOn: Guy that animates"
"MandatoryArg: <guy>: Guy that animates"
"MandatoryArg: <amime>: Scene name"
"Example: set_custom_move_start_transition( level.price, special_exit );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
set_custom_move_start_transition( guy, anime )
{
	/#
	guy assert_existance_of_anim( anime, guy.animname );
	#/

	guy.customMoveTransition = animscripts\cover_arrival::customMoveTransitionFunc;
	guy.startMoveTransitionAnim = level.scr_anim[ guy.animname ][ anime ];
}
