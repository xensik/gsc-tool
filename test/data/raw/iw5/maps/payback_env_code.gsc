#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_sandstorm;
#include maps\payback_util;
	
init_flags_environmental()
{
	flag_init( "start_pre_construction_anims" );
	flag_init( "stop_pre_construction_anims" );
	
	flag_init( "start_construction_anims" );
	flag_init( "stop_construction_anims" );
	
	flag_init( "start_sandstorm_anims" );
	flag_init( "stop_sandstorm_anims" );
	
	flag_init( "start_rescue_anims" );
	flag_init( "stop_rescue_anims" );
}

init_sandstorm_env_effects(startPoint)
{
	//maps\payback_sandstorm_code::init_sandstorm_logic();

	thread handle_sandstorm_env_effects();
	
	if ( !IsDefined(startPoint) )
	{
		startPoint = GetDVar("start");
	}

	switch ( startPoint )
	{
		case "s3_escape":
		case "s3_rescue":
			flag_set( "stop_sandstorm_anims" );
			flag_set( "start_rescue_anims" );
		
		case "s2_sandstorm":
		case "s2_rappel":
			flag_set( "stop_construction_anims" );
			flag_set( "start_sandstorm_anims" );
			
		case "s2_construction":
		 	flag_set( "stop_pre_construction_anims" );
		 	flag_set( "start_construction_anims" );
			
		case "s2_postambush":
		case "s2_city":
			flag_set( "start_pre_construction_anims" );

		default:
			break;
	};
}

handle_spawning_of_sandstorm_models()
{
	spawn_struct_array( "tree_med_need_in_intro", "script_noteworthy" );	// Intro trees - Intro/City area

	flag_wait( "start_pre_construction_anims" );
	if ( !flag("stop_pre_construction_anims") )
	{
		spawn_struct_array( "tree_low", "script_noteworthy" );			// Low trees - City/Ambush Area
		spawn_struct_array( "moving_grass_low", "targetname" );			// Low grass - Outside Compound Exit
		spawn_struct_array( "moving_grass_01_low", "targetname" );		// Low grass 01 - City/Ambush Area
		spawn_struct_array( "moving_grass_02_low", "targetname" );		// Low grass 02 - City/Ambush Area
		spawn_struct_array( "moving_grass_03_low", "targetname" );		// Low grass 03 - City/Ambush Area
		spawn_struct_array( "moving_bushes_low", "targetname" );		// Low bushes - City/Ambush area
		spawn_struct_array( "moving_bushes_med", "targetname" );		// Medium bushes - Construction area
	}
	if ( !flag("stop_construction_anims") )
	{
		spawn_struct_array( "tree_med", "script_noteworthy" );			// Medium trees - Construction Area
	}
	
	flag_wait( "start_construction_anims" );
	if ( !flag("stop_construction_anims") )
	{
		spawn_struct_array( "moving_grass_01_med", "targetname" );		// Medium grass 01 - Construction Area
		spawn_struct_array( "moving_grass_02_med", "targetname" );		// Medium grass 02 - Construction Area
		spawn_struct_array( "moving_grass_03_med", "targetname" );		// Medium grass 03 - Construction Area
		spawn_struct_array( "moving_flag_med", "targetname" );			// Flags - Construction Area
		spawn_struct_array( "moving_square_flag_med", "targetname" );	// Flags - Construction Area
		spawn_struct_array( "moving_tarp_03", "targetname" );			// Tarps - Construction Area
		spawn_struct_array( "moving_tarp_01", "targetname" );			// Tarp that gets ripped - Construction Area
	}
	if ( !flag("stop_sandstorm_anims") )
	{
		spawn_struct_array( "tree_heavy", "script_noteworthy" );		// Heavy trees - Sandstorm Area
	}
	
	flag_wait( "start_sandstorm_anims" );
	if ( !flag("stop_sandstorm_anims") )
	{
		spawn_struct_array( "moving_grass_01_high", "targetname" );		// High grass 01 - Sandstorm Area
		spawn_struct_array( "moving_grass_02_high", "targetname" );		// High grass 02 - Sandstorm Area
		spawn_struct_array( "moving_grass_03_high", "targetname" );		// High grass 03 - Sandstorm Area
		spawn_struct_array( "moving_bushes_high", "targetname" );		// High bushes - Sandstorm area
	}
	
	flag_wait( "start_rescue_anims" );
	spawn_struct_array( "tree_rescue", "script_noteworthy" );		// Rescue trees - Rescue area
	spawn_struct_array( "moving_grass_01_rescue", "targetname" );	// Rescue grass 01 - Rescue Area
	spawn_struct_array( "moving_grass_02_rescue", "targetname" );	// Rescue grass 02 - Rescue Area
	spawn_struct_array( "moving_grass_03_rescue", "targetname" );	// Rescue grass 03 - Rescue Area
	spawn_struct_array( "moving_bushes_rescue", "targetname" );		// Rescue bushes - Rescue area
	
	spawn_struct_array( "moving_grass_02_end", "targetname" );		// End grass 02 - End Area
	spawn_struct_array( "moving_bushes_end", "targetname" );		// End bushes - End area
}

spawn_struct_array(key,value)
{
	array = GetStructArray( key, value );
	
	foreach( thing in array )
	{
		spawn_model_from_struct(thing);
	}
}

spawn_model_from_struct(origin_struct)
{
	anim_model 						= Spawn( "script_model", origin_struct.origin );
	anim_model.angles 				= origin_struct.angles;
	anim_model 						SetModel( origin_struct.script_parameters );
	anim_model.targetname 			= origin_struct.targetname;
	anim_model.script_noteworthy	= origin_struct.script_noteworthy;
	
	return anim_model;
}

handle_sandstorm_env_effects()
{
	rolling_barrel_clip = GetEntArray( "rolling_barrel_clip", "targetname" );
	foreach(barrel_clip in rolling_barrel_clip)
	{
		barrel_clip NotSolid();
	}
	
	
	thread handle_trees();
	thread handle_pre_construction_effects();
	thread handle_construction_effects();
	thread handle_sandstorm_effects();
	thread handle_rescue_effects();
	thread handle_moving_objects();
	thread handle_impulse_objects();
}

handle_pre_construction_effects()
{
	flag_wait("start_pre_construction_anims");
	wait(1); // This is to allow time for any animated models that were deleted to spawn back in
	grass = thread grass_wind("low");
	bushes = thread bushes_wind("low");
	//flags = thread flags_wind("low");
	
	tarps = thread tarps_wind_low();
	wires = thread wires_wind_low();
	crates = thread crates_wind_low();
	laundry_items = thread laundry_wind_low();
	
	flag_wait("start_construction_anims");
	wait(1); // This is to allow time for any animated models that were deleted to spawn back in

	foreach(wire in wires)
	{
		wire notify("deleted_through_script");
		wire notify("stop_looping_anims");
	}
	wires = thread wires_wind_med(wires);	// kick up the wires to med wind
	
	wires = GetEntArray( "payback_wires_wind_light", "script_noteworthy" );
	
	flag_wait("stop_pre_construction_anims");
	objects = array_combine( tarps , array_combine( bushes , array_combine( grass, array_combine(crates, array_combine(laundry_items, wires )))));
	foreach( object in objects )
	{
		object notify("deleted_through_script");
		object delete();
	}
}

handle_construction_effects()
{
	flag_wait("start_construction_anims");
	wait(1); // This is to allow time for any animated models that were deleted to spawn back in
	grass = thread grass_wind("med");
	bushes = thread bushes_wind("med");
	flags = thread flags_wind("med");
	
	tarps = thread tarps_wind_med();
	wires = thread wires_wind_med();
	fences = thread fences_wind_med();
	roofs = thread roofs_wind_med();
	crates = thread crates_wind_med();
	thread gates_wind_high();
	//thread chain_wind();
	thread umbrella_wind();

	flag_wait("stop_construction_anims");
	objects = array_combine( flags , array_combine( tarps , array_combine( grass , array_combine( bushes , fences ))));
	objects = array_combine( objects , array_combine( wires , array_combine( roofs , crates )));
	foreach( object in objects )
	{
		object notify("deleted_through_script");
		object delete();
	}
}

handle_sandstorm_effects()
{
	flag_wait("start_sandstorm_anims");
	wait(1); // This is to allow time for any animated models that were deleted to spawn back in
	grass = thread grass_wind("high");
	bushes = thread bushes_wind("high");
	//flags = thread flags_wind("high");
	
	tarps = thread tarps_wind_high();
	wires = thread wires_wind_extreme();
	wires2 = thread wires_wind_high();
	signs = thread signs_wind_high();
	fences = thread fences_wind_high();
	wires = array_combine( wires, wires2 );
	crates = thread crates_wind_high();
	
	flag_wait("stop_sandstorm_anims");
	objects = array_combine( signs , array_combine( bushes , array_combine( grass , tarps )));
	objects = array_combine( objects , array_combine( fences , array_combine( wires , crates )));
	foreach( object in objects )
	{
		object notify("deleted_through_script");
		object delete();
	}
}

handle_rescue_effects()
{
	flag_wait("start_rescue_anims");
	wait(1); // This is to allow time for any animated models that were deleted to spawn back in
	grass = thread grass_wind("rescue");
	bushes = thread bushes_wind("rescue");
	//flags = thread flags_wind("rescue");
	
	//tarps = thread tarps_wind_rescue();
	wires = thread wires_wind_rescue();
	//signs = thread signs_wind_rescue();
	//fences = thread fences_wind_rescue();
	crates = thread crates_wind_rescue();
	
	grass2 = thread grass_wind("end");
	bushes2 = thread bushes_wind("end");
	
	flag_wait("stop_rescue_anims");
	objects = array_combine( bushes , array_combine( grass , array_combine( wires , crates )));
	
	foreach( object in objects )
	{
		object notify("deleted_through_script");
		object delete();
	}
}

handle_trees()
{
	flag_wait("start_pre_construction_anims");
	wait(1);
	trees = thread trees_wind_low();
	antennas = thread antennas_wind();
	
	flag_wait("start_construction_anims");
	wait(2);
	foreach(tree in trees)
	{
		tree notify("deleted_through_script");
		tree notify("stop_looping_anims");
	}
	
	trees = thread trees_wind_med();
	
	flag_wait("stop_pre_construction_anims");
	trees_to_delete = GetEntArray( "tree_low", "script_noteworthy" );
	foreach (tree in trees_to_delete)
	{
		tree notify("deleted_through_script");
		tree delete();
	}
	
	flag_wait( "start_sandstorm_anims" );
	foreach ( tree in trees )
	{
		if (IsDefined(tree))
		{
			if ( tree.targetname == "jungle_tree" || tree.targetname == "pine_tree" )
			{
				tree notify("deleted_through_script");
				tree notify("stop_looping_anims");	
			}
		}	
	}
	
	trees = array_combine( trees , thread trees_wind_heavy() );	
	
	flag_wait("stop_construction_anims");
	trees_to_delete = GetEntArray( "tree_med", "script_noteworthy" );
	trees_to_delete = array_combine( trees_to_delete, GetEntArray( "tree_med_need_in_intro", "script_noteworthy" ));
	foreach (tree in trees_to_delete)
	{
		tree notify("deleted_through_script");
		tree delete();
	}
	
	flag_wait("start_rescue_anims");
	wait(1); // This is to allow time for any animated models that were deleted to spawn back in
	trees = thread trees_wind_med();
	//trees = thread trees_wind_heavy();
	trees = array_combine( trees , thread trees_wind_heavy() );	
	
	flag_wait("stop_sandstorm_anims");
	trees_to_delete = GetEntArray( "tree_heavy", "script_noteworthy" );
	foreach (tree in trees_to_delete)
	{
		tree notify("deleted_through_script");
		tree delete();
	}
	
	flag_wait("stop_rescue_anims");
	foreach(tree in trees)
	{
		if(IsDefined(tree))
		{
			tree notify("deleted_through_script");
			tree delete();
		}
	}
}

// self = model starting anim on
start_anim_on_object(animname,name_of_animation,delay)
{
	self endon("deleted_through_script");
	
	if ( isdefined(delay) )
	{
		wait(delay);
	}
	self.animname = animname;
	self useAnimTree( level.scr_animtree[ self.animname ] );
	//self thread anim_loop_solo(self, name_of_animation, "stop_looping_anims");
	self setAnimRestart( level.scr_anim[self.animname][name_of_animation][0], 1, 0, 1 );
}

grass_wind( type )
{
	// for grass just outside the compound, angles need to be 0 180 0
	grass = GetEntArray( "moving_grass_" + type , "targetname" );
	foreach(grass_piece in grass)
	{
		grass_piece thread start_anim_on_object("payback_sstorm_grass","light_sway",randomfloatrange(0.0,1.5));
	}

	// for grass_wind_1 animation, angles need to be 0 180 0
	grass01 = GetEntArray( "moving_grass_01_" + type , "targetname" );
	foreach(grass_piece in grass01)
	{
		grass_piece thread start_anim_on_object("payback_sstorm_grass","strong_sway_1",randomfloatrange(0.0,1.5));
	}
	
	// for grass_wind_2 animation, angles need to be 0 270 0
	grass02 = GetEntArray( "moving_grass_02_" + type , "targetname" );
	foreach(grass_piece in grass02)
	{
		grass_piece thread start_anim_on_object("payback_sstorm_grass","strong_sway_2",randomfloatrange(0.0,1.5));
	}
	
	// for grass_wind_3 animation, angles need to be 0 90 0
	grass03 = GetEntArray( "moving_grass_03_"+ type , "targetname" );
	foreach(grass_piece in grass03)
	{
		grass_piece thread start_anim_on_object("payback_sstorm_grass","strong_sway_3",randomfloatrange(0.0,1.5));
	}
	
	//return array_combine(array_combine(grass01,grass02),grass03);
	return array_combine( grass01, array_combine( grass02, array_combine( grass03, grass ) ) );
}

bushes_wind( type )
{
	bushes = GetEntArray( "moving_bushes_" + type , "targetname" );
	foreach ( bush in bushes )
	{
		if(IsDefined(bush.script_noteworthy) && (bush.script_noteworthy == "compound_exit") )
		{
			bush thread start_anim_on_object("payback_foliage_bush01","light_sway",randomfloatrange(0.0,1.5));
		}
		else
		{
			bush_anim_name =  "strong_sway_" + randomintrange(1,3); // randomly choose between the two anims
			bush thread start_anim_on_object("payback_foliage_bush01",bush_anim_name,randomfloatrange(0.0,1.5));
		}
	}
	return bushes;
}

flags_wind( type )
{
	flags = GetEntArray( "moving_flag_" + type , "targetname" );
	foreach(flag in flags)
	{
		flag thread start_anim_on_object("highrise_fencetarp_08","strong_sway",randomfloatrange(0.0,1.5));
	}
	
	square_flags = GetEntArray( "moving_square_flag_" + type , "targetname" );
	foreach(flag in square_flags)
	{
		flag thread start_anim_on_object("com_square_flag","strong_sway",randomfloatrange(0.0,1.5));
	}
	
	return array_combine(flags,square_flags);
}

umbrella_wind()
{
	construction_umbrella = GetEnt("construction_umbrella", "targetname" );
	construction_umbrella thread start_anim_on_object( "umbrella", "heli_wind_far", randomfloatrange(0.0,1.5) );
	
	flag_wait("stop_construction_anims");
	construction_umbrella notify("deleted_through_script");
	construction_umbrella delete();
	
	flag_wait( "start_rescue_anims" );
	nikolai_umbrella = GetEnt( "nikolai_umbrella", "targetname" );
	nikolai_umbrella thread start_anim_on_object( "umbrella", "heli_wind_far", randomfloatrange(0.0,1.5) );
}

signs_wind_high()
{
	signs_metal_l = GetEntArray("moving_sign_metal_l_high","targetname");
	foreach(sign in signs_metal_l)
	{
		sign thread start_anim_on_object("payback_sstorm_sign_metal","strong_sway_l",randomfloatrange(0.0,1.5));
	}
	
	signs_metal_r = GetEntArray("moving_sign_metal_r_high","targetname");
	foreach(sign in signs_metal_r)
	{
		sign thread start_anim_on_object("payback_sstorm_sign_metal","strong_sway_r",randomfloatrange(0.0,1.5));
	}
	
	signs_chain_l = GetEntArray("moving_sign_chain_l_high","targetname");
	foreach(sign in signs_chain_l)
	{
		sign thread start_anim_on_object("payback_sstorm_sign_chain","strong_sway_l",randomfloatrange(0.0,1.5));
	}
	
	signs_chain_r = GetEntArray("moving_sign_chain_r_high","targetname");	
	foreach(sign in signs_chain_r)
	{
		sign thread start_anim_on_object("payback_sstorm_sign_chain","strong_sway_r",randomfloatrange(0.0,1.5));
	}
	
	return array_combine(array_combine(signs_metal_l,signs_metal_r),array_combine(signs_chain_l,signs_chain_r));
}

fences_wind_med()
{
	fences = GetEntArray("moving_fence","targetname");
	foreach(fence in fences)
	{
		fence_anim_name = "strong_sway_" + randomintrange(1,3); // randomly choose between the two anims
		fence thread start_anim_on_object("payback_sstorm_fence_chainlink",fence_anim_name,randomfloatrange(0.0,1.5));
	}
	
	return fences;
}

fences_wind_high()
{
	fences = GetEntArray("moving_fence_high","targetname");
	foreach(fence in fences)
	{
		fence_anim_name = "strong_sway_" + randomintrange(1,3); // randomly choose between the two anims
		fence thread start_anim_on_object("payback_sstorm_fence_chainlink",fence_anim_name,randomfloatrange(0.0,1.5));
	}
	
	return fences;
}

wires_wind_low()
{
	wires_light = GetEntArray( "payback_wires_wind_light", "script_noteworthy" );
	wires_medium = GetEntArray( "payback_wires_wind_medium", "script_noteworthy" );
	wires = array_combine( wires_light, wires_medium );
	return wires_wind_internal( wires, "light" );
}

wires_wind_med(wires)
{
	return wires_wind_internal( wires, "medium" );
}

wires_wind_high()
{
	return wires_wind_internal( undefined, "heavy" );
}

wires_wind_extreme()
{
	return wires_wind_internal( undefined, "extreme" );
}

wires_wind_rescue()
{
	return wires_wind_internal( undefined, "rescue" );
}

wires_wind_internal( wires_etc, wind_level )
{
	if (!IsDefined(wires_etc))
	{
		wires_etc = GetEntArray( "payback_wires_wind_" + wind_level , "script_noteworthy" );
	}
	wires = [];
	foreach ( object in wires_etc )
	{
		if ( IsDefined( object.targetname ))
		{
			if ( object.targetname == "moving_wires_single" )
			{
				object thread start_anim_on_object("payback_wires_single", "strong_sway", randomfloatrange(0.0,1.5));
				wires[wires.size] = object;
			}
			else if ( object.targetname == "moving_wires_double" )
			{
				object thread start_anim_on_object("payback_wires_double","strong_sway_" + wind_level, randomfloatrange(0.0,1.5));
				wires[wires.size] = object;
			}
			else if ( object.targetname == "moving_wires_short" )
			{
				anim_index = RandomIntRange( 1 , 3 );
				delay = 0.0;
				if ( IsDefined( object.script_delay ))
				{
					delay = object.script_delay;	
				}
				delay = RandomFloatRange( delay , delay + 0.25 );
				object thread start_anim_on_object("payback_wires_short", "wind_" + wind_level + "_" + anim_index , delay);
				wires[wires.size] = object;	
			}
			else if ( object.targetname == "moving_wires_long" )
			{
				anim_index = RandomIntRange( 1 , 3 );
				delay = 0.0;
				if ( IsDefined( object.script_delay ))
				{
					delay = object.script_delay;	
				}
				delay = RandomFloatRange( delay , delay + 0.25 );
				object thread start_anim_on_object("payback_wires_long", "wind_" + wind_level + "_" + anim_index , delay);
				wires[wires.size] = object;
			}
		}
	}
	return wires;
}

roofs_wind_med()
{
	roofs = GetEntArray("shack_moving_roof","targetname");	
	foreach(roof in roofs)
	{
		roof thread start_anim_on_object("payback_shack","strong_sway",randomfloatrange(0.0,1.5));
	}
	
	return roofs;
}

antennas_wind()
{
	antennas_low = GetEntArray("moving_antenna_low","targetname");
	foreach(antenna in antennas_low)
	{
		level thread antenna_anim(antenna, true);
	}
	
	antennas = GetEntArray("moving_antenna","targetname");
	foreach(antenna in antennas)
	{
		level thread antenna_anim(antenna, false);
	}
}

antenna_anim(antenna, delete_at_construction)
{
	anim_model = Spawn( "script_model", antenna.origin );
	anim_model.angles = antenna.angles;
	anim_model SetModel("generic_prop_raven");
	anim_model.animname = "sstorm_antenna";
	anim_model SetAnimTree();

	// spawn and attach antenna
	anim_model attach( antenna.model, "J_prop_1" );
	
	anim_model thread start_anim_on_object("sstorm_antenna","light_sway",randomfloatrange(0.0,3.0));
	
	antenna delete();
	
	flag_wait("start_construction_anims");
	
	anim_model notify("deleted_through_script");
	anim_model notify("stop_looping_anims");

	if (delete_at_construction)
	{
		anim_model delete();
	} 
	else 
	{
		anim_model thread start_anim_on_object("sstorm_antenna","strong_sway",randomfloatrange(0.0,3.0));
	
		flag_wait("stop_rescue_anims");
		anim_model delete();
	}
}

trees_wind_low()
{
	tall_trees = GetEntArray("moving_tree","targetname");
	foreach(tree in tall_trees)
	{
		tree thread start_anim_on_object("foliage_tree_palm_med_1","light_sway",randomfloatrange(0.0,3.0));
	}
	
	bushy_trees = GetEntArray("moving_bushy_tree_extreme","targetname");
	foreach(tree in bushy_trees)
	{
		tree thread start_anim_on_object("foliage_tree_palm_bushy_3","med_sway",randomfloatrange(0.0,3.0));
	}
	
	jungle_trees = GetEntArray("jungle_tree","targetname");
	foreach ( tree in jungle_trees )
	{
		animation = "wind_med_" + RandomIntRange( 1 , 3 );
		tree thread start_anim_on_object("foliage_tree_jungle",animation,RandomFloatRange(0.0,3.0));
	}
	
	//There are currently no pine trees in Payback - payback_sstorm_tree_pine_sm
	pine_trees = GetEntArray("pine_tree","targetname");
	foreach( tree in pine_trees )
	{
		animation = "wind_light_" + RandomIntRange( 1 , 3 );
		tree thread start_anim_on_object("foliage_tree_pine",animation,randomfloatrange(0.0,3.0));
	}
	
	dwarf_palm_trees = GetEntArray("palm_tree", "targetname");
	foreach (tree in dwarf_palm_trees)
	{
		tree thread start_anim_on_object("dwarf_palm","wind_light",randomfloatrange(0.0,3.0));
	}
	
	return array_combine( tall_trees , array_combine( bushy_trees, array_combine( jungle_trees , array_combine( pine_trees, dwarf_palm_trees ))));
}

trees_wind_med()
{
	tall_trees = GetEntArray("moving_tree","targetname");
	foreach(tree in tall_trees)
	{
		tree thread wait_till_offscreen_then_start_anim("foliage_tree_palm_med_1","strong_sway",randomfloatrange(0.0,3.0));
	}
	
	bushy_trees = GetEntArray("moving_bushy_tree_extreme","targetname");
	foreach(tree in bushy_trees)
	{
		tree thread wait_till_offscreen_then_start_anim("foliage_tree_palm_bushy_3","strong_sway",randomfloatrange(0.0,3.0));
	}
	
	jungle_trees = GetEntArray("jungle_tree","targetname");
	foreach ( tree in jungle_trees )
	{
		animation = "wind_med_" + RandomIntRange( 1 , 3 );
		tree thread wait_till_offscreen_then_start_anim("foliage_tree_jungle",animation,RandomFloatRange(0.0,3.0));
	}
	
	//There are currently no pine trees in Payback - payback_sstorm_tree_pine_sm
	pine_trees = GetEntArray("pine_tree","targetname");
	foreach( tree in pine_trees )
	{
		animation = "wind_med_" + RandomIntRange( 1 , 3 );
		tree thread wait_till_offscreen_then_start_anim("foliage_tree_pine",animation,randomfloatrange(0.0,3.0));
	}
	
	dwarf_palm_trees = GetEntArray("palm_tree", "targetname");
	foreach (tree in dwarf_palm_trees)
	{
		tree thread wait_till_offscreen_then_start_anim("dwarf_palm","wind_med",randomfloatrange(0.0,3.0));
	}
	
	return array_combine(tall_trees, array_combine( bushy_trees , array_combine( jungle_trees , array_combine(pine_trees, dwarf_palm_trees ))));
}

wait_till_offscreen_then_start_anim(animname,name_of_animation,delay)
{
	self endon("deleted_through_script");
	wait(delay);

	tree_is_offscreen = false;
	while(!tree_is_offscreen)
	{
		if ( !within_fov_2d(level.player.origin,level.player.angles,self.origin,Cos(45)) )
		{
			tree_is_offscreen = true;
		}
		else
		{
			wait(0.1);
		}
	}

	self.animname = animname;
	self useAnimTree( level.scr_animtree[ self.animname ] );
	self setAnimRestart( level.scr_anim[self.animname][name_of_animation][0], 1, 0, 1 );
}

trees_wind_heavy()
{
	jungle_trees = GetEntArray("jungle_tree","targetname");
	foreach ( tree in jungle_trees )
	{
		animation = "wind_heavy_" + RandomIntRange( 1 , 3 );
		tree thread start_anim_on_object("foliage_tree_jungle",animation,RandomFloatRange(0.0,3.0));
	}
	
	//There are currently no pine trees in Payback - payback_sstorm_tree_pine_sm
	pine_trees = GetEntArray("pine_tree","targetname");
	foreach( tree in pine_trees )
	{
		animation = "wind_heavy_" + RandomIntRange( 1 , 3 );
		tree thread start_anim_on_object("foliage_tree_pine",animation,randomfloatrange(0.0,3.0));
	}
	
	return array_combine( jungle_trees , pine_trees );

}

tarps_wind_low()
{
	tarp03_array = GetEntArray("moving_tarp_03_low","targetname");
	foreach(tarp in tarp03_array)
	{
		tarp thread start_anim_on_object("highrise_fencetarp_03","light_sway",randomfloatrange(0.0,2.0));
	}
	
	return tarp03_array;
}

tarps_wind_med()
{
	tarp01_array = GetEntArray("moving_tarp_01","targetname");
	foreach(tarp in tarp01_array)
	{
		tarp thread tarp01_rip();
	}
	
	tarp03_array = GetEntArray("moving_tarp_03","targetname");
	foreach(tarp in tarp03_array)
	{
		tarp_anim_name = "strong_sway_" + randomintrange(1,3); // randomly choose between the two anims
		tarp thread start_anim_on_object("highrise_fencetarp_03",tarp_anim_name,randomfloatrange(0.0,2.0));
	}
	
	return array_combine(tarp01_array,tarp03_array);
}

tarps_wind_high()
{
	tarp03_array = GetEntArray("moving_tarp_03_high","targetname");
	foreach(tarp in tarp03_array)
	{
		tarp_anim_name = "strong_sway_" + randomintrange(1,3); // randomly choose between the two anims
		tarp thread start_anim_on_object("highrise_fencetarp_03",tarp_anim_name,randomfloatrange(0.0,2.0));
	}
	
	return tarp03_array;
}

crates_wind_animate( targetname , animname )
{
	crates = GetEntArray( targetname , "targetname" );
	foreach( crate in crates )
	{
		crate thread start_anim_on_object( "tarp_crate" , animname , RandomFloatRange( 0 , 2 ));
		//crate Hide();
	}
	return crates;
}

crates_wind_low()
{
	return crates_wind_animate( "crate_with_tarp_low_wind" , "payback_tarp_crate_light_wind" );
}

crates_wind_med()
{
	return crates_wind_animate( "crate_with_tarp_med_wind" , "payback_tarp_crate_heavy_wind" );
}

crates_wind_high()
{
	return crates_wind_animate( "crate_with_tarp_high_wind" , "payback_tarp_crate_heavy_wind" );
}

crates_wind_rescue()
{
	return crates_wind_animate( "crate_with_tarp_rescue_wind" , "payback_tarp_crate_heavy_wind" );
}

laundry_wind_low()
{
	laundry_sheets = GetEntArray("laundry_sheet","targetname");
	foreach(laundry_sheet in laundry_sheets)
	{
		laundry_sheet thread start_anim_on_object("hanging_sheet","wind_medium",randomfloatrange(0.0,3.0));
	}
	
	laundry_short_sleeves = GetEntArray("laundry_short_sleeve","targetname");
	foreach(laundry_short_sleeve in laundry_short_sleeves)
	{
		laundry_short_sleeve thread start_anim_on_object("hanging_short_sleeve","wind_medium",randomfloatrange(0.0,3.0));
	}
	
	laundry_long_sleeves = GetEntArray("laundry_long_sleeve","targetname");
	foreach(laundry_long_sleeve in laundry_long_sleeves)
	{
		laundry_long_sleeve thread start_anim_on_object("hanging_long_sleeve","wind_medium",randomfloatrange(0.0,3.0));
	}
	
	laundry_aprons = GetEntArray("laundry_apron","targetname");
	foreach(laundry_apron in laundry_aprons)
	{
		laundry_apron thread start_anim_on_object("hanging_apron","wind_medium",randomfloatrange(0.0,3.0));
	}
	
	return array_combine( laundry_sheets, array_combine( laundry_short_sleeves, array_combine( laundry_long_sleeves, laundry_aprons )));
}



tarp01_rip()
{
	self thread start_anim_on_object("highrise_fencetarp_01","strong_sway_initial_loop",randomfloatrange(0.0,2.0));
	
	flag_wait("start_tarp_rip");
	
	self notify("stop_looping_anims");		// ends current looping anim playing
	self notify("deleted_through_script");	// stops self from starting a looping anim (if it hasn't started already)

	if ( IsDefined(self) )
	{
		self.animname = "highrise_fencetarp_01";
		self useAnimTree( level.scr_animtree[ self.animname ] );
		self anim_single_solo(self,"strong_sway_tear");
	
		self thread anim_loop_solo(self, "strong_sway_final_loop", "stop_looping_anims");
	}
}

gates_wind_high()
{
	anim_origin = getstruct("gate_origin","targetname");
	animation = "gate_loop_closed";
	start_animation = "gate_loop_closed_single";
	
	// delete editor models
	gate1 = getent( "wind_gate_left" , "targetname");
	gate2 = getent( "wind_gate_right" , "targetname");
	
	if ( IsDefined( gate1 ) && IsDefined( gate2 ) )
	{
		gate1 delete();
		gate2 delete();
		gate_rig = getent( "gate_rig", "targetname");
		thread gates_wind( anim_origin , start_animation , animation , gate_rig );
		thread chain_wind(gate_rig, anim_origin);
	}
	
	anim_origin = getstruct( "sandstorm_gates_2" , "targetname" );
	if ( IsDefined( anim_origin ))
	{
		animation = "gate_loop_2";
		start_animation = "gate_loop_2_single";
		gate_rig = getent( "gate_rig_2", "targetname");
		thread gates_wind( anim_origin , start_animation , animation , gate_rig );
		thread chain_wind(gate_rig, anim_origin);
	}
}

gates_wind( anim_origin , start_animation , animation , gate_rig )
{
	gate_rig.animname = "sstorm_gate";
	gate_rig setanimtree();
		
	// attach gates to rig
	gate_rig attach( "pb_gate_wall_alt", "J_prop_1" );
	gate_rig attach( "pb_gate_wall_alt", "J_prop_2" );
	
	anim_origin thread anim_first_frame_solo( gate_rig , start_animation );

	flag_wait("start_sandstorm_anims");
		
	anim_origin thread anim_loop_solo( gate_rig , animation , "stop_gate_loop" );
		
	flag_wait("stop_sandstorm_anims");
			
	anim_origin notify("stop_gate_loop");
	waittillframeend;
	gate_rig delete();
}

chain_wind(gate_rig, anim_origin)
{
	chain_model = Spawn( "script_model", gate_rig.origin );
	chain_model SetModel("generic_prop_raven");
	chain_model.animname = "sstorm_gate_chain";
	chain_model SetAnimTree();
	chain_model attach( "pb_gate_chain", "J_prop_1" );
	
	if(gate_rig == getent( "gate_rig", "targetname"))
	{
		start_animation = "chain_windy_loop_closed_single";
		animation = "chain_windy_loop_closed";
		stop_anim_tag = "gate_1_stop";
		thread maps\payback_streets_const::gate_chain(chain_model, anim_origin);
	}
	else
	{
		start_animation = "chain_windy_2_single";
		animation = "chain_windy_2_loop";
		stop_anim_tag = "gate_2_stop";
	}
	
	anim_origin thread anim_first_frame_solo( chain_model, start_animation );

	flag_wait("start_sandstorm_anims");
		
	anim_origin thread anim_loop_solo( chain_model, animation, stop_anim_tag );
		
	flag_wait("stop_sandstorm_anims");
	chain_model delete();	
}

/*
chain_wind()
{
	chain_rig = getent( "chain_rig", "targetname");	
	chain_rig.animname = "sstorm_gate_chain";
	chain_rig setanimtree();
	
	anim_origin = getstruct("gate_origin","targetname");
	
	anim_origin thread anim_first_frame_solo( chain_rig , "chain_windy_loop_closed_single" );

	flag_wait("start_sandstorm_anims");
		
	anim_origin thread anim_loop_solo( chain_rig , "chain_windy_loop_closed" , "stop_gate_loop" );
		
	flag_wait("stop_sandstorm_anims");
	chain_rig delete();
}
*/
handle_moving_objects()
{
	barrel_triggers = GetEntArray("rolling_barrel_trigger","targetname");
	foreach(trigger in barrel_triggers)
	{
		trigger thread rolling_object_trigger("sstorm_barrel","com_barrel_green_dirt",false);
	}
	
	bucket_triggers = GetEntArray("rolling_bucket_trigger","targetname");
	foreach(trigger in bucket_triggers)
	{
		trigger thread rolling_object_trigger("sstorm_bucket","com_plastic_bucket_empty",true);
	}
	
	bush_triggers = GetEntArray("rolling_bush_trigger","targetname");
	foreach(trigger in bush_triggers)
	{
		trigger thread rolling_object_trigger("sstorm_bush","",true);
	}
	
	chicken_coop_triggers = GetEntArray("rolling_chicken_coop_trigger","targetname");
	foreach(trigger in chicken_coop_triggers)
	{
		trigger thread chicken_coop_trigger();
	}
}

handle_impulse_objects()
{
	level.south_dir = ( -1.0 * cos( GetNorthYaw() ), -1.0 * sin( GetNorthYaw() ), 0 );
	impulse_triggers = GetEntArray( "payback_impulse_trigger" , "targetname" );
	foreach( trigger in impulse_triggers )
	{
		trigger thread impulse_trigger();
	}
}

impulse_trigger()
{
	self waittill( "trigger" );
	
	impulse_targets = GetEntArray( self.target , "targetname" );
	foreach( target in impulse_targets )
	{
		force_amount = 50;
		if ( IsDefined( target.script_parameters ))
		{
			force_amount = Float(target.script_parameters);
		}
		force_dir = ( 1 , 0 , 0 );
		if ( IsDefined( target.angles ))
		{
			force_dir = AnglesToForward( target.angles );
		}
		else	
		{
			force_dir = level.south_dir;
		}
		force = force_dir * force_amount;	
		target PhysicsLaunchServer( target.origin , force );
	}
}

// self = trigger to wait on
rolling_object_trigger(animname,model_name,anim_at_end)
{
	self waittill("trigger");
	
	override_model = undefined;
	anim_model = undefined;
	start_struct = GetStruct(self.target,"targetname");
	if ( !isdefined(start_struct) )
	{
		override_model = GetEnt(self.target,"targetname");
		start_struct = GetStruct(override_model.target,"targetname");
	}
	end_struct = GetStruct(start_struct.target,"targetname");
	
	spawned_origin = spawn( "script_origin", start_struct.origin );
	
	// set up anim model
	if ( isdefined(override_model) )
	{
		override_model.animname = animname;
		override_model SetAnimTree();
		
		override_model.origin = start_struct.origin;
		if ( isdefined(start_struct.angles) )
		{
			override_model.angles = start_struct.angles;
		}
		
		anim_model = override_model;
	}
	else
	{
		anim_model = Spawn( "script_model", start_struct.origin );
		anim_model SetModel("generic_prop_raven");
		anim_model.animname = animname;
		anim_model SetAnimTree();
		if ( isdefined(start_struct.angles) )
		{
			anim_model.angles = start_struct.angles;
		}
		
		// attach model to anim_model
		anim_model attach( model_name, "J_prop_1" );
		if (anim_model.animname == "sstorm_barrel")
		{
			rolling_barrel_clip = GetEntArray( "rolling_barrel_clip", "targetname" );
			foreach(barrel_clip in rolling_barrel_clip)
			{
				distance_between = distance(barrel_clip.origin,start_struct.origin);
				if (distance_between <= 50)
				{
					barrel_clip Solid();
					barrel_clip LinkTo( anim_model );
				}
			}
		}
	}
	
	anim_model linkto( spawned_origin );
	anim_model thread anim_loop_solo(anim_model, "roll_loop");
	
	// AUDIO begin
	// hacking in a way to play sounds on our rolling objects
	// define the sound by comparing the animname string
	// otherwise print a debug error if we don't have a sound
	// so that we know we need one set up
	if (anim_model.animname == "sstorm_barrel")
	{
		anim_model.soundalias = "pybk_rolling_barrel";
		anim_model PlayLoopSound( anim_model.soundalias );
	}
	else if (anim_model.animname == "sstorm_bucket")
	{
		anim_model.soundalias = "pybk_rolling_bucket";
		anim_model PlayLoopSound( anim_model.soundalias );
	}
	else if (anim_model.animname == "sstorm_bush")
	{
		anim_model.soundalias = "pybk_rolling_bush";
		anim_model PlayLoopSound( anim_model.soundalias );
	}
	else
	{
		IPrintLnBold( "rolling_object_trigger() model '" + anim_model.animname + "' with no soundalias defined! please contact audio department with asset request!" );
	}
	// AUDIO end
	
	current_struct = start_struct;
	total_anim_time = 0;
	while(isdefined(current_struct.target))
	{
		next_struct = GetStruct(current_struct.target,"targetname");
		
		total_distance_inches = distance(current_struct.origin,next_struct.origin);
		total_distance_feet = total_distance_inches / 12;
		movement_time = total_distance_feet/current_struct.speed;
		
		spawned_origin MoveTo(next_struct.origin,movement_time);
		
		wait(movement_time);
		total_anim_time += movement_time;
		
		current_struct = next_struct;
	}
	
	anim_model StopAnimScripted();
	anim_model notify("stop_loop");
	
	if ( anim_at_end )
	{
		anim_model thread anim_loop_solo(anim_model, "roll_stop_loop");
	}
	else
	{	
		anim_length = GetAnimLength( level.scr_anim[ animname ][ "roll_loop" ][0] );
		
		num_of_anim_cycles = total_anim_time / anim_length;
		current_anim_time_percent = num_of_anim_cycles - INT(num_of_anim_cycles);
		
		anim_model SetAnimKnob( level.scr_anim[ animname ][ "roll_loop" ][0], 1, 0, 0 );
		anim_model SetAnimTime( level.scr_anim[ animname ][ "roll_loop" ][0], current_anim_time_percent );
	}
	
	anim_model StopLoopSound(); // AUDIO
	anim_model thread delete_when_player_far_away();
	spawned_origin delete();
	self delete();
}

// self = trigger to wait on
chicken_coop_trigger()
{
	self waittill("trigger");
	
	chicken_coop_start = GetStruct(self.target,"targetname");

	anim_model = Spawn( "script_model", chicken_coop_start.origin );
	anim_model SetModel("generic_prop_raven");
	anim_model.animname = "sstorm_chicken_coop";
	anim_model SetAnimTree();
	anim_model.angles = chicken_coop_start.angles;
	
	cage_model = Spawn( "script_model", anim_model GetTagOrigin("J_prop_1") );
	cage_model SetModel("me_wood_cage_large");
	cage_model.angles = anim_model GetTagAngles("J_prop_1");
	chicken_model = Spawn( "script_model", anim_model GetTagOrigin("J_prop_2") );
	chicken_model SetModel("chicken_black_white");
	chicken_model.angles = anim_model GetTagAngles("J_prop_2");
	chicken_model.animname = "sstorm_chicken";
	chicken_model SetAnimTree();
	
	cage_model LinkTo(anim_model,"J_prop_1");
	chicken_model LinkTo(anim_model,"J_prop_2");
	
	anim_model thread anim_single_solo(anim_model, "roll_loop");
	while(1)
	{
		chicken_model anim_single_solo(chicken_model,"chicken_loop_01");
		chicken_model anim_single_solo(chicken_model,"chicken_loop_02");
	}
}

delete_when_player_far_away()
{
	self endon("deleted");
	
	while(isdefined(self))
	{
		distance_to_player = distance(level.player.origin,self.origin);
		if ( distance_to_player > 2000 )
		{
			self delete();
			self notify("deleted");
		}
		wait(1.0);
	}
}
