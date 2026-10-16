#include common_scripts\utility;
#include maps\_utility;
#include maps\_anim;
#include maps\_stealth_utility;

/************************************************************************************************************/
/*											SYSTEM UTILITIES												*/
/************************************************************************************************************/

//called by _stealth_accuracy_friendly
//called by _stealth_behavior_enemy
//called by _stealth_behavior_friendly
//called by _stealth_color_friendly
ai_message_handler_spotted( function, plugin_override  )
{
	self endon( "death" );
	
	assertex( isdefined( plugin_override ), "plugin_override required, modify plugin script -z" );
	plugin_override = plugin_override + "spotted";
	
	self notify( plugin_override );
	self endon( plugin_override );
	
	switch( self.team )
	{
		case "allies":
			while ( 1 )
			{
				self ent_flag_wait( "_stealth_enabled" );

				self flag_wait( "_stealth_spotted" );

				if ( !self ent_flag( "_stealth_enabled" ) )
					continue;

				self thread [[ function ]]();

				self flag_waitopen( "_stealth_spotted" );
			}
			break;

		case "axis":
		case "team3":
			while ( 1 )
			{
				self ent_flag_wait( "_stealth_enabled" );

				self stealth_group_spotted_flag_wait();

				if ( !self ent_flag( "_stealth_enabled" ) )
					continue;

				self thread [[ function ]]();

				self stealth_group_spotted_flag_waitopen();
			}
			break;
	}
}

//called by _stealth_accuracy_friendly
//called by _stealth_behavior_enemy
//called by _stealth_behavior_friendly
//called by _stealth_color_friendly
ai_message_handler_hidden( function, plugin_override )
{
	self endon( "death" );
		
	assertex( isdefined( plugin_override ), "plugin_override required, modify plugin script -z" );
	plugin_override = plugin_override + "hidden";
	
	self notify( plugin_override );
	self endon( plugin_override );

	switch( self.team )
	{
		case "allies":
			while ( 1 )
			{
				self ent_flag_wait( "_stealth_enabled" );

				self flag_waitopen( "_stealth_spotted" );

				if ( !self ent_flag( "_stealth_enabled" ) )
					continue;

				self thread [[ function ]]();

				self flag_wait( "_stealth_spotted" );
			}
			break;

		case "axis":
		case "team3":
			while ( 1 )
			{
				self ent_flag_wait( "_stealth_enabled" );

				self stealth_group_spotted_flag_waitopen();

				if ( !self ent_flag( "_stealth_enabled" ) )
					continue;

				self thread [[ function ]]();

				self stealth_group_spotted_flag_wait();
			}
			break;
	}
}

/*
=============
///ScriptDocBegin
"Name: ai_create_behavior_function( <name>, <key>, <function> )"
"Summary: sets up a behavior function that an AI using the stealth system will call in a specific situation, by putting an entry in the AI's ._stealth.behavior.ai_functions array."
"Module: Entity"
"MandatoryArg: <name>: the general category, for example, 'threat', 'animation', or 'event' (among others)."
"MandatoryArg: <key>: the specific subcategory, for example, 'heard_scream' or 'reset' (among others)."
"MandatoryArg: <function>: the function to run when the stealth script looks for this behavior function."
"Example: ai_create_behavior_function( "threat", "reset", ::cliffhanger_enemy_alert_level_reset );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
ai_create_behavior_function( name, key, function )
{
	self._stealth.behavior.ai_functions[ name ][ key ] = function;
}

// used internally by the stealth system
ai_get_behavior_function( name, key )
{
	return self._stealth.behavior.ai_functions[ name ][ key ];
}

/*
=============
///ScriptDocBegin
"Name: ai_set_goback_override_function( <function> )"
"Summary: sets up an "event" behavior function that an AI using the stealth system will call in a specific situation, by putting an entry in the AI's ._stealth.behavior.ai_functions[ "event" ] array.  This function will be called between the AI forgetting about the threat, and the AI heading back to where he was patrolling previously."
"Module: Entity"
"MandatoryArg: <function>: the function to run when the AI forgets about an event, before he heads back to his previous patrol spot."
"Example: ai_create_event_goback_override_function( ::cliffhanger_enemy_alert_level_reset );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
ai_set_goback_override_function( function )
{
	self._stealth.behavior.goback_startFunc = function;
}

stealth_event_validate( key )
{
	if ( key == "heard_scream" || key == "doFlashBanged" || key == "explode" )
	{
		return true;
	}
	
	ASSERTMSG( "valid values for stealth events are 'heard_scream', 'doFlashBanged', and 'explode'.  you tried: " + key );
	return false;
}


stealth_debug_print( msg )
{
	 /#
		if ( !flag( "_stealth_enabled" ) )
			return;

		type = undefined;
		name = undefined;

		if ( isdefined( self.script_noteworthy ) )
		{
			type = "Script_noteworthy";
			name = self.script_noteworthy;
		}
		else if ( isdefined( self.targetname ) )
		{
			type = "Targetname";
			name = self.targetname;
		}

		actor = "Actor -> ID: " + self.unique_id + " Export: " + self.export;

		if ( isdefined( type ) )
		{
			actor += " " + type + ": " + name;
		}
		txt = "STEALTH DEBUG PRINT: " + actor + "\n     " + msg;

		println( txt );

    	if ( getdvarint( "stealth_debug_prints" ) == 1 )
			self thread debug_message_ai( msg );
	#/
}

enemy_event_debug_print( type )
{
	setDvarIfUninitialized( "stealth_debug_prints", "0" );

    if ( !isdefined( getdvar( "stealth_debug_prints" ) ) )
	 	setdvar( "stealth_debug_prints", "0" );
	 
	if ( getdvarint( "stealth_debug_prints" ) != 1 )
		return;
	 
	 /#
		self endon( "death" );
		
		self waittill( type, subtype );
	
		if ( isdefined( subtype ) )
			self stealth_debug_print( "Received an event: " + type + " " + subtype );
		else
			self stealth_debug_print( "Received an event: " + type );
	#/
}

stealth_flag_debug_print( _flag )
{
	 /#
		while ( 1 )
		{
			flag_wait( _flag );
			{
				if ( getdvarint( "stealth_debug_prints" ) == 1 )
					iprintlnbold( _flag );
				else
					println( _flag );
			}

			flag_waitopen( _flag );
			{
				if ( getdvarint( "stealth_debug_prints" ) == 1 )
					iprintlnbold( "back to normal: " + _flag );
				else
					println( "back to normal: " + _flag );
			}
		}
	#/
}

group_flag_init( _flag )
{
	assertex( issentient( self ), "an AI must call this function" );

	if ( isdefined( self.script_stealthgroup ) )
		self.script_stealthgroup = string( self.script_stealthgroup );
	else
		self.script_stealthgroup = "default";

	name = self group_get_flagname( _flag );

	if ( !flag_exist( name ) )
	{
		flag_init( name );

		if ( !isdefined( level._stealth.group.flags[ _flag ] ) )
			level._stealth.group.flags[ _flag ] = [];

		size = level._stealth.group.flags[ _flag ].size;
		level._stealth.group.flags[ _flag ][ size ] = name;
	}
}

group_add_to_global_list()
{
	assertex( issentient( self ), "an AI must call this function" );

	if ( !isdefined( level._stealth.group.groups[ self.script_stealthgroup ] ) )
	{
		level._stealth.group.groups[ self.script_stealthgroup ] = [];
		level._stealth.group notify( self.script_stealthgroup );
	}
	size = level._stealth.group.groups[ self.script_stealthgroup ].size;
	level._stealth.group.groups[ self.script_stealthgroup ][ size ] = self;
}

group_get_flagname( _flag )
{
	assertex( issentient( self ), "an AI must call this function" );

	return group_get_flagname_from_group( _flag, self.script_stealthgroup );
}

group_get_flagname_from_group( _flag, group )
{
	name = _flag + "-Group:" + group;
	return name;
}

group_flag_set( _flag )
{	
	assertex( issentient( self ), "an AI must call this function" );

	name = self group_get_flagname( _flag );
	flag_set( name );
	flag_set( _flag );
}

group_return_groups_with_flag_set( _flag )
{
	return_value = [];
	
	array = level._stealth.group.groups;
	
	foreach ( key, value in array )
	{
		name = group_get_flagname_from_group( _flag, key );
		
		if ( flag( name ) )
			return_value[ return_value.size ] = key;
	}	
	
	return return_value;
}

group_return_ai_with_flag_set( _flag )
{
	return_value = [];	
	
	array = level._stealth.group.groups;
	
	foreach ( key, value in array )
	{
		name = group_get_flagname_from_group( _flag, key );
		
		if ( flag( name ) )
		{
			ai = group_get_ai_in_group( key );
			return_value = array_merge( return_value, ai ); 
		}
	}	
	
	return return_value;
}

group_flag_clear( _flag, group )
{
	name = group_get_flagname_from_group( _flag, group );
	flag_clear( name );

	array = level._stealth.group.flags[ _flag ];
	clear = true;

	foreach ( key, value in array )
	{
		if ( flag( value ) )
			return;
	}

	flag_clear( _flag );
}

group_get_ai_in_group( group_name )
{
	level._stealth.group.groups[ group_name ] = array_removeDead( level._stealth.group.groups[ group_name ] );
	return level._stealth.group.groups[ group_name ];
}

group_wait_group_spawned( group_name )
{
	if ( !isdefined( level._stealth.group.groups[ group_name ] ) )
		level._stealth.group waittill( group_name );
}

/************************************************************************************************************/
/*											BEHAVIOR UTILITIES												*/
/************************************************************************************************************/

ai_stealth_pause_handler()
{
	self endon( "death" );
	self endon( "pain_death" );
	
	while ( 1 )
	{
		self ent_flag_waitopen( "_stealth_enabled" );

		spotted_func = self._stealth.behavior.ai_functions[ "state" ][ "spotted" ];
		
		switch( self.team )
		{
			case "allies":
				self [[ spotted_func ]]();
				break;
			case "axis":
			case "team3":
				self [[ spotted_func ]]( true );
				break;
		}

		self ent_flag_wait( "_stealth_enabled" );
		
		hidden_func = self._stealth.behavior.ai_functions[ "state" ][ "hidden" ];
		self [[ hidden_func ]]();
	}
}

enemy_go_back()
{
	self notify( "going_back" );
	self endon( "death" );
	self notify( "stop_loop" );
	
	if( IsDefined( self._stealth.behavior.goback_startFunc ) )
	{
		self [[ self._stealth.behavior.goback_startFunc ]]();
	}

	spot = self._stealth.behavior.last_spot;
	
	if ( isdefined( spot ) && self.type != "dog" && !isdefined( self.customMoveTransition ) )
		self.customMoveTransition = maps\_patrol::patrol_resume_move_start_func;

	// stop before moving
	if ( isdefined( self.customMoveTransition ) && isdefined( self.pathGoalPos ) )
	{
		self setgoalpos( self.origin );
		wait 0.05;
	}

	if ( isdefined( self.script_patroller ) )
	{
		if ( isdefined( self.last_patrol_goal ) )
		{
			self.target = self.last_patrol_goal.targetname;
		}
		
		//these guys on the ridge in cliffhanger get alerted and jump down a one way traverse. this gives them a pathable patrol path to go back to.
		if ( isdefined( self.stealth_first_alert_new_patrol_path ) )
		{
			self.target = self.stealth_first_alert_new_patrol_path.targetname;
			self.stealth_first_alert_new_patrol_path = undefined;
		}

		self thread maps\_patrol::patrol();
	}
	else if ( isalive( self.patrol_master ) )
	{
		self thread maps\_patrol::pet_patrol();
		self set_dog_walk_anim();
		self.script_growl = undefined;
	}
	else if ( isdefined( spot ) ) 
	{
		if ( self.type != "dog" )
			self set_generic_run_anim( "_stealth_patrol_cqb", true );
		else
		{
			self set_dog_walk_anim();
			self.script_growl = undefined;
		}
		self.disablearrivals = true;
		self.disableexits = true;

		self setgoalpos( spot );
		self.goalradius = 40;
	}

	//make sure the AI has been given a new goal before clearing this flag
	waittillframeend;
	self ent_flag_clear( "_stealth_override_goalpos" );

	if ( isdefined( spot ) ) 
		self thread enemy_go_back_clear_lastspot( spot );
}

enemy_go_back_clear_lastspot( origin )
{
	self endon( "death" );
	self endon( "_stealth_enemy_alert_level_change" );

	self waittill_true_goal( origin );
	self._stealth.behavior.last_spot = undefined;
}

// caches result of search
enemy_get_nearby_pathnodes( origin, radius, min_radius )
{
	if ( !isdefined( min_radius ) )
		min_radius = 0;

	if ( isdefined( level._stealth.node_search.nodes_array ) &&
		 distanceSquared( origin, level._stealth.node_search.origin ) < 64 * 64 &&
		 radius == level._stealth.node_search.radius && 
		 min_radius == level._stealth.node_search.min_radius )
		return level._stealth.node_search.nodes_array;

	level._stealth.node_search.origin = origin;
	level._stealth.node_search.radius = radius;
	level._stealth.node_search.min_radius = min_radius;
	
	level._stealth.node_search.nodes_array = getNodesInRadius( origin, radius, min_radius, 512, "Path" );
	
	return level._stealth.node_search.nodes_array;
}

// this is called by some functions like finding a corpse or
// hearing an explosion that go into alert - but dont want to put into alert
// state because alert state shares it's behavior with a guy simply
// thinkgin he saw something twice
enemy_reaction_state_alert()
{
	self.fovcosine = .01;// 90 degrees to either side...180 cone...default view cone
	self.ignoreall = false;
	self.dieQuietly 	 = false;
	self clear_run_anim();
	self.fixednode		 = false;
}

enemy_alert_level_forget( enemy, delay )
{
	self endon( "death" );
	enemy endon( "death" );
	
	if ( !isdefined( delay ) )
		delay = 60;		//after 60 seconds - forget about it
	
	wait delay;
					
	if ( isdefined( enemy._stealth.logic.spotted_list[ self.unique_id ] ) && enemy._stealth.logic.spotted_list[ self.unique_id ] > 0 )
		enemy._stealth.logic.spotted_list[ self.unique_id ] -- ;
}

enemy_stop_current_behavior()
{
	if ( !self ent_flag( "_stealth_behavior_reaction_anim" ) )
	{
		self anim_stopanimscripted();
		self notify( "stop_animmode" );
		self notify( "stop_loop" );
	}
	if ( isdefined( self.script_patroller ) )
	{
		if ( isdefined( self.last_patrol_goal ) )
			self.last_patrol_goal.patrol_claimed = undefined;

		self notify( "release_node" );
		self notify( "end_patrol" );
	}
	self notify( "stop_first_frame" );
	self clear_run_anim();
	self clear_generic_idle_anim();
}

enemy_find_original_goal()
{
	//if we already have an original goal - stick to it
	if ( isdefined( self._stealth.behavior.last_spot ) )
		return;

	if ( isdefined( self.last_set_goalnode ) )
		self._stealth.behavior.last_spot =  self.last_set_goalnode.origin;
	else if ( isdefined( self.last_set_goalent ) )
		self._stealth.behavior.last_spot =  self.last_set_goalent.origin;
	else if ( isdefined( self.last_set_goalpos ) )
		self._stealth.behavior.last_spot =  self.last_set_goalpos;
	else
		self._stealth.behavior.last_spot = self.origin;
}

enemy_set_original_goal( origin )
{
	self._stealth.behavior.last_spot = origin;
}

enemy_runto_and_lookaround( node, position )
{
	self notify( "enemy_runto_and_lookaround" );
	self endon( "enemy_runto_and_lookaround" );

	self endon( "death" );
	self endon( "_stealth_enemy_alert_level_change" );
	if ( self.type != "dog" )
		self endon( "_stealth_saw_corpse" );

	spotted_flag = self group_get_flagname( "_stealth_spotted" );
	level endon( spotted_flag );

	//this is for guys who are already DOING this, and need to do it again
	self notify( "stop_loop" );

	self ent_flag_set( "_stealth_override_goalpos" );
	
	if ( isdefined( node ) )
	{
		self setgoalnode( node );
	}
	else
	{
		assertex( isdefined( position ), "no node or position defined" );
		self setgoalpos( position );
	}
		
	self.goalradius = 64;

	self waittill( "goal" );

	if ( self.type != "dog" )
		self set_generic_idle_anim( "_stealth_look_around" );
}

enemy_find_free_pathnode_near( origin, radius, min_radius )
{
	array = enemy_get_nearby_pathnodes( origin, radius, min_radius );

	if ( !isdefined( array ) || array.size == 0 )
		return;

	node = array[ randomInt( array.size ) ];
	array = array_remove( array, node );
	
	while ( isdefined( node.owner ) )
	{
		if ( array.size == 0 )
			return;
			
		node = array[ randomInt( array.size ) ];
		array = array_remove( array, node );
	}
	
	level._stealth.node_search.nodes_array = array;
	
	return node;
}

/************************************************************************************************************/
/*												ANNOUCEMENTS												*/
/************************************************************************************************************/
enemy_announce_wtf()
{
	if ( self.type == "dog" )
		return;
	if ( !( self enemy_announce_snd( "wtf" ) ) )
		return;

	alias = "stealth_" + self.npcID + "_anexplosion";
	self playsound( alias );
}

// Who's there?
enemy_announce_huh()
{
	if ( self.type == "dog" )
		return;
	if ( !( self enemy_announce_snd( "huh" ) ) )
		return;

	alias = "stealth_" + self.npcID + "_huh";
	self playsound( alias );
}

// Didn't find anything, going back to patrol
enemy_announce_hmph()
{
	if ( self.type == "dog" )
		return;
	if ( !( self enemy_announce_snd( "hmph" ) ) )
		return;

	alias = "stealth_" + self.npcID + "_hmph";
	self playsound( alias );
}


enemy_announce_attack()
{
	self endon( "death" );
	self endon( "pain_death" );// don't actually want to be able to still call out to buddies - it kinda sucks to take him down and still lose

	if ( self.type == "dog" )
		return;
		
	if ( !( self enemy_announce_snd( "spotted" ) ) )
		return;

	self playsound( "RU_" + self.npcID + "_stealth_alert" );
}

enemy_announce_spotted( pos )
{
	self endon( "death" );
	self endon( "pain_death" );// don't actually want to be able to still call out to buddies - it kinda sucks to take him down and still lose

	// this makes sure that if we're not spotted because we killed
	// this guy before he could set the flag - we dont' bring 
	// everyone over for no reason.
	self stealth_group_spotted_flag_wait();

	if ( self.type == "dog" )
		return;

	if ( self enemy_announce_snd( "spotted" ) )
	{
		self thread enemy_announce_spotted_bring_group( pos );

		alias = "RU_" + self.npcID + "_stealth_alert";
		self playsound( alias );
	}

	if ( self enemy_announce_snd( "acknowledge" ) )
		self thread enemy_announce_spotted_acknowledge( self.origin );
}

enemy_announce_spotted_acknowledge( spotterPos )
{
	wait 1.5;	

	if ( isdefined( self.npcID ) )
		num = self.npcID;
	else
		num = randomint( 3 );
		
	alias = "RU_" + num + "_stealth_alert_r";
	play_sound_in_space( alias, spotterPos );
}

enemy_announce_spotted_bring_group( pos )
{
	group = group_get_ai_in_group( self.script_stealthgroup );

	foreach ( key, ai in group )
	{
		if ( ai == self )
			continue;

		if ( isdefined( ai.enemy ) || isdefined( ai.favoriteenemy ) )
			continue;

		ai notify( "heard_scream", pos );
	}
}

enemy_announce_corpse()
{
	self endon( "death" );
	if ( isdefined( self.found_corpse_wait ) )
		wait( self.found_corpse_wait );

	if ( !( self enemy_announce_snd( "corpse" ) ) )
		return;

	if ( self.type == "dog" )
	{
		self ent_flag_waitopen( "_stealth_behavior_reaction_anim_in_progress" );
		self notify( "event_awareness", "howl" );
		return;
	}

	alias = "stealth_" + self.npcID + "_deadbody";
	self playsound( alias );
}

/************************************************************************************************************/
/*										ANNOUCEMENT UTILITIES												*/
/************************************************************************************************************/
enemy_announce_snd( type )
{
	if ( type == "spotted" )
	{
		if ( level._stealth.behavior.sound[ type ][ self.script_stealthgroup ] )
			return false;

		level._stealth.behavior.sound[ type ][ self.script_stealthgroup ] = true;
	}
	else
	{
		if ( level._stealth.behavior.sound[ type ] )
			return false;

		level._stealth.behavior.sound[ type ] = true;

		self thread	enemy_announce_snd_reset( type );
	}

	return true;
}

enemy_announce_snd_reset( type )
{
	wait level._stealth.behavior.sound_reset_time;
	level._stealth.behavior.sound[ type ] = false;
}

/************************************************************************************************************/
/*											ANIMATION SYSTEM												*/
/************************************************************************************************************/
enemy_animation_wrapper( type )
{
	self endon( "death" );
	self endon( "pain_death" );

	// ALWAYS RUN THIS UNLESS YOU'RE SURE YOU KNOW WHAT YOU"RE DOING
	if ( self enemy_animation_pre_anim( type ) )
		return;

	self enemy_animation_do_anim( type );

	// ALWAYS RUN THIS UNLESS YOU'RE SURE YOU KNOW WHAT YOU"RE DOING
	self enemy_animation_post_anim( type );
}

enemy_animation_do_anim( type )
{
	if ( isdefined( self._stealth.behavior.event.custom_animation ) )
	{
		self enemy_animation_custom( type );
		return;
	}

	// do default behavior	
	function = self._stealth.behavior.ai_functions[ "animation" ][ type ];

	self [[ function ]]( type );
}

enemy_animation_custom( type )
{
	node = self._stealth.behavior.event.custom_animation.node;
	anime = self._stealth.behavior.event.custom_animation.anime;
	tag = self._stealth.behavior.event.custom_animation.tag;
	ender = self._stealth.behavior.event.custom_animation.ender;

	self ent_flag_set( "_stealth_behavior_reaction_anim" );

	// wouldn't normally do this - but since this is specific to stealth script
	// i figured it would be ok to set allowdeath.
	self.allowdeath = true;

	// cut the loop
	node notify( ender );

	if ( isdefined( self.anim_props ) )
	{
		self.anim_props_animated = true;
		node thread anim_single( self.anim_props, anime );
	}
	if ( type != "doFlashBanged" )
	{
		// this is the reaction
		if ( isdefined( tag ) || isdefined( self.has_delta ) )
			node anim_generic( self, anime, tag );
		else
			node anim_generic_custom_animmode( self, "gravity", anime );
	}
	// once you the the reaction once - you dont wanna ever do it again...especially not off this node
	self ai_clear_custom_animation_reaction();
}

enemy_animation_pre_anim( type )
{
	self notify( "enemy_awareness_reaction", type );

	// this means that something really bad happened...a first reaction
	// to the player being spotted or something equally bad like a bullet
	// whizby
	if ( self ent_flag( "_stealth_behavior_first_reaction" ) || self ent_flag( "_stealth_behavior_reaction_anim_in_progress" ) )
		return true;

	// this function doesn't stop behavior if _stealth_behavior_reaction_anim
	// is set - because stoping behavior means ending current animations
	// and since reacting is an animation - we want to set the flag
	// AFTER we've stopped the current ones
	self enemy_stop_current_behavior();

	if ( issubstr( type, "warning" ) )
		type = "warning";

	switch( type )
	{
		case "explode":
		case "heard_corpse":
		case "saw_corpse":
		case "found_corpse":
			// all the cases above this dont break - so they all will do the same thing when they get to this line
			self ent_flag_set( "_stealth_behavior_reaction_anim" );
			break;
		case "reset":
		case "warning":
			// all the cases above this dont break - so they all will do the same thing when they get to this line
			// which is absolutely nothing
			break;
		default:
			if ( !self ent_flag_exist( "_stealth_behavior_asleep" ) || !self ent_flag( "_stealth_behavior_asleep" ) || self stealth_group_spotted_flag() )
			{
				self ent_flag_set( "_stealth_behavior_first_reaction" );
				self thread enemy_animation_pre_anim_dog_special_first_condition();
			}
			self ent_flag_set( "_stealth_behavior_reaction_anim" );
			break;
	}

	self ent_flag_set( "_stealth_behavior_reaction_anim_in_progress" );
	return false;
}

enemy_animation_pre_anim_dog_special_first_condition()
{
	spotted_flag = self group_get_flagname( "_stealth_spotted" );

	self endon( "death" );

	flag_wait_or_timeout( spotted_flag, 3 );
	if ( flag( spotted_flag ) )
		self ent_flag_set( "_stealth_behavior_first_reaction" );
}

enemy_animation_post_anim( type )
{
	switch( type )
	{
		default:
			self ent_flag_clear( "_stealth_behavior_reaction_anim" );
			break;
	}

	self ent_flag_clear( "_stealth_behavior_reaction_anim_in_progress" );
}

/************************************************************************************************************/
/*											ANIMATION UTILITIES												*/
/************************************************************************************************************/
ai_clear_custom_animation_reaction()
{
	self._stealth.behavior.event.custom_animation = undefined;
	
	self.newEnemyReactionDistSq = squared( 512 );
}

ai_clear_custom_animation_reaction_and_idle( waitanimend )
{
	// could have been cleared by something else
	if ( !isdefined( self._stealth.behavior.event.custom_animation ) )
		return;

	self._stealth.behavior.event.custom_animation.node notify( "stop_loop" );
	if ( !isdefined( waitanimend ) || waitanimend == false )
		self stopanimscripted();

	self ai_clear_custom_animation_reaction();
}

ai_set_custom_animation_reaction( node, anime, tag, ender )
{
	self._stealth.behavior.event.custom_animation = spawnstruct();

	self._stealth.behavior.event.custom_animation.node = node;
	self._stealth.behavior.event.custom_animation.anime = anime;
	self._stealth.behavior.event.custom_animation.tag = tag;
	self._stealth.behavior.event.custom_animation.ender = ender;
	self thread ai_animate_props_on_death( node, anime, tag, ender );
	
	self.newEnemyReactionDistSq = 0;
}

ai_animate_props_on_death( node, anime, tag, ender )
{
	wait .1;
	if ( !isdefined( self.anim_props ) )
		return;

	prop = self.anim_props;

	self waittill( "death" );

	if ( isdefined( self.anim_props_animated ) )
		return;

	node thread anim_single( prop, anime );
}

/************************************************************************************************************/
/*												EVENT AWARENESS												*/
/************************************************************************************************************/

event_awareness_main( dialogue_array, ender_array )
{
	level notify( "event_awareness_handler" );
	level endon( "event_awareness_handler" );
	level endon( "default_event_awareness_enders" );

	event_awareness_enders( ender_array );

	add_wait( ::waittill_msg, "event_awareness_handler" );
	add_wait( ::waittill_msg, "default_event_awareness_enders" );
	add_func( ::flag_clear, "_stealth_event" );
	thread do_wait_any();

	while ( 1 )
	{
		flag_wait( "_stealth_enabled" );

		flag_wait( "_stealth_event" );

		if ( !flag( "_stealth_enabled" ) )
			continue;

		wait 2;

		event_awareness_dialogue_wrapper( dialogue_array );

		flag_waitopen( "_stealth_event" );
	}
}

event_awareness_dialogue_wrapper( array )
{
	wait randomfloatrange( .5, 1 );

	if ( !isdefined( array ) )
		return;

	string = random( array );
	level thread function_stack( ::radio_dialogue, string );
}

event_awareness_enders( ender_array )
{
	level endon( "default_event_awareness_enders" );
	level endon( "event_awareness_handler" );

	if ( isdefined( ender_array ) )
	{
		foreach ( string in ender_array )
		{
			if ( flag_exist( string ) && flag( string ) )
				level notify( "default_event_awareness_enders" );
		}

		//don't want to put into the same loop as above because we dont
		//want to add_wait and then kill this function without every calling
		//do_wait...cause that would cause some nasty bugs
		foreach ( string in ender_array )
			add_wait( ::waittill_msg, string );
	}

	add_wait( ::flag_wait, "_stealth_spotted" );
	add_wait( ::waittill_msg, "end_event_awareness_handler" );
	add_wait( ::waittill_msg, "event_awareness_handler" );
	add_func( ::send_notify, "default_event_awareness_enders" );
	thread do_wait_any();
}

/************************************************************************************************************/
/*										GLOBAL SCRIPT CALL BACKS											*/
/************************************************************************************************************/

_autosave_stealthcheck()
{
	if( !stealth_is_everything_normal() )
		return false;
		
	if ( flag( "_stealth_player_nade" ) )
		return false;
	if ( flag_exist( "_radiation_poisoning" ) )
	{
		if ( flag( "_radiation_poisoning" ) )
			return false;
	}
	vehicles = getentarray( "destructible", "classname" );
	foreach ( vehicle in vehicles )
	{
		if ( isDefined( vehicle.healthDrain ) )
			return false;
	}
	
	return true;
}

_patrol_endon_spotted_flag()
{	
	flag1 = self stealth_get_group_spotted_flag();
	flag2 = self stealth_get_group_corpse_flag();
	
	add_wait( ::flag_wait, flag1 );
	add_wait( ::flag_wait, flag2 );
	self add_abort( ::waittill_msg, "death" );
	self add_func( ::send_notify, "end_patrol" );
	thread do_wait_any();
}

_spawner_stealth_default()
{
	self thread stealth_default();
}

