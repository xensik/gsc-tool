#include common_scripts\utility;
#using_animtree( "destructibles" );

// Car alarm constants
MAX_SIMULTANEOUS_CAR_ALARMS = 2;
CAR_ALARM_ALIAS = "car_alarm";
CAR_ALARM_OFF_ALIAS = "car_alarm_off";
NO_CAR_ALARM_MAX_ELAPSED_TIME = 120;
CAR_ALARM_TIMEOUT = 25;
DESTROYED_ATTACHMENT_SUFFIX = "_destroy";

SP_DAMAGE_BIAS = 0.5;
SP_EXPLOSIVE_DAMAGE_BIAS = 9.0;

MP_DAMAGE_BIAS = 1.0;
MP_EXPLOSIVE_DAMAGE_BIAS = 13.0;

SP_SHOTGUN_BIAS = 8.0;
MP_SHOTGUN_BIAS = 4.0;

init()
{
	/#
	SetDevDvarIfUninitialized( "debug_destructibles", "0" );
	SetDevDvarIfUninitialized( "destructibles_enable_physics", "1" );
	SetDevDvarIfUninitialized( "destructibles_show_radiusdamage", "0" );
	#/

	level.destructibleSpawnedEntsLimit = 50;
	level.destructibleSpawnedEnts = [];
	level.currentCarAlarms = 0;
	level.commonStartTime = GetTime();
	
	if ( !IsDefined( level.fast_destructible_explode ) )
		level.fast_destructible_explode = false; // want to isolate resulting bugs to hamburg. - Nate

	/#
	level.created_destructibles = [];
	#/

	if ( !isdefined( level.func ) )
	{
		// this array will be filled with code commands that SP or MP may use but doesn't exist in the other.
		level.func = [];
	}

	destructibles_enabled = true;
	/#
	destructibles_enabled = ( GetDvarInt( "destructibles_enabled", 1 ) == 1 );
	#/

	if ( destructibles_enabled )
		find_destructibles();

	deletables = GetEntArray( "delete_on_load", "targetname" );
	foreach ( ent in deletables )
		ent Delete();

	/#
	SetDevDvarIfUninitialized( "scr_destructible_warning", "1" );
	if ( GetDvarInt( "scr_destructible_warning", 1 ) == 1 )
		thread warn_about_old_destructible();
	#/

	init_destroyed_count();
	init_destructible_frame_queue();
}

warn_about_old_destructible()
{
	wait 1;

	// Find all old prefabs and print warning/errors about them so they get updated
	destructibles = GetEntArray( "destructible", "targetname" );
	if ( destructibles.size != 0 )
	{
		PrintLn( "This map contains old destructible vehicle prefabs which no longer work properly. Please update them to use the new vehicle prefabs in map_source\\prefabs\\destructible\\. See console for a list of vehicles that you need to updated." );

		PrintLn( "^1###################################################^0" );
		PrintLn( "^1###################################################^0" );
		PrintLn( "^1###################################################^0" );

		foreach ( vehicle in destructibles )
			PrintLn( "^1Destructible vehicle at ( " + vehicle.origin + " ) uses an old prefab. Update it to use a prefab located in prefabs\destructible\^0" );

		PrintLn( "^1###################################################^0" );
		PrintLn( "^1###################################################^0" );
		PrintLn( "^1###################################################^0" );

		AssertMsg( "This map contains old destructible vehicle prefabs which no longer work properly. Please update them to use the new vehicle prefabs in map_source\\prefabs\\destructible\\. See console for a list of vehicles that you need to updated." );
	}
}

find_destructibles()
{
	//---------------------------------------------------------------------
	// Find all destructibles by their targetnames and run the setup
	//---------------------------------------------------------------------

//	array_thread( GetEntArray( "destructible_vehicle", "targetname" ), ::setup_destructibles );

	//////////////////////////////////////////////////////////////////////////
	// TU0: taking out some of these because they aren't in the playable area
	positions = [];
	switch( GetDvar( "mapname" ) )
	{
	case "mp_interchange":
		positions[ positions.size ] = ( 4172.8, -1887, 345.9 );
		positions[ positions.size ] = ( 4070.5, -2049.2, 349.2 );
		positions[ positions.size ] = ( 3333.3, -1743.4, 345.6 );
		positions[ positions.size ] = ( 3503.7, -1634.5, 345.6 );
		positions[ positions.size ] = ( 2852.6, -1220.7, 345.6 );
		positions[ positions.size ] = ( 2451.2, -1034.6, 345.6 );
		positions[ positions.size ] = ( 1719.8, -711, 328.5 );
		positions[ positions.size ] = ( 2920.1, -3423.3, 416.6 );
		positions[ positions.size ] = ( 2694.9, -3433, 414.4 );
		positions[ positions.size ] = ( 1497.2, -2220.9, 449.5 );
		positions[ positions.size ] = ( 1276.2, -1882.9, 403 );
		positions[ positions.size ] = ( 845.6, -1766.3, 400.6 );
		positions[ positions.size ] = ( -2038.3, 613, 378 );
		positions[ positions.size ] = ( -2966.6, 1288.5, 378 );
		positions[ positions.size ] = ( -1347.8, 2905.9, 445.9 );
		positions[ positions.size ] = ( -1030.6, 2989.5, 445.5 );
		positions[ positions.size ] = ( -29.3, 695.7, 349 );
		positions[ positions.size ] = ( 1418.6, 311.3, 602.1 );
		positions[ positions.size ] = ( 1662.3, 687.5, 599.9 );
		positions[ positions.size ] = ( 2061.6, 643.2, 597.7 );
		positions[ positions.size ] = ( 2096, 1042.5, 580.4 );
		positions[ positions.size ] = ( 3.4, -912.9, 646.9 );
		break;
	}
	//////////////////////////////////////////////////////////////////////////
	
	// Temporary store any dot refs in prefabs
	
	dots = [];
	
	foreach ( struct in level.struct )
		if ( IsDefined( struct.script_noteworthy ) &&
			struct.script_noteworthy == "destructible_dot" )
				dots[ dots.size ] = struct;	
	
	//assuring orders -nate
	vehicles = GetEntArray( "destructible_vehicle", "targetname" );
	foreach ( vehicle in vehicles )
	{
		//////////////////////////////////////////////////////////////////////////
		// TU0: taking out some of these because they aren't in the playable area
		switch( GetDvar( "mapname" ) )
		{
		case "mp_interchange":
			// first check the z so we don't loop all of the time
			if( vehicle.origin[2] > 150.0 )
			{
				skipDest = false;
				foreach( pos in positions )
				{
					if( int( vehicle.origin[0] ) == int( pos[0] ) && int( vehicle.origin[1] ) == int( pos[1] ) && int( vehicle.origin[2] ) == int( pos[2] ) )
					{
						skipDest = true;
						break;
					}
				}
				if( skipDest )
					continue;
			}
			break;
		}
		//////////////////////////////////////////////////////////////////////////

		vehicle setup_destructibles();
		vehicle setup_destructible_dots( dots );
	}

	destructible_toy = GetEntArray( "destructible_toy", "targetname" );
	foreach ( toy in destructible_toy )
	{
		toy setup_destructibles();
		toy setup_destructible_dots( dots );
	}

	/#
	total = 0;
	if ( GetDvarInt( "destructibles_locate" ) > 0 )
	{
		// Print out the destructibles we created and where they are all located
		PrintLn( "##################" );
		PrintLn( "DESTRUCTIBLE LIST:" );
		PrintLn( "##################" );
		PrintLn( "" );

		keys = GetArrayKeys( level.created_destructibles );
		foreach ( key in keys )
		{
			PrintLn( key + ": " + level.created_destructibles[ key ].size );
			total += level.created_destructibles[ key ].size;
		}
		PrintLn( "" );
		PrintLn( "Total: " + total );
		PrintLn( "" );
		PrintLn( "Locations:" );

		foreach ( key in keys )
		{
			foreach ( destructible in level.created_destructibles[ key ] )
			{
				PrintLn( key + ": " + destructible.origin );
				//destructible thread maps\_debug::drawOrgForever();
			}
		}

		PrintLn( "" );
		PrintLn( "##################" );
		PrintLn( "##################" );
		PrintLn( "##################" );

		level.created_destructibles = undefined;
	}
	#/

}

setup_destructible_dots( dots )
{
	destructibleInfo = self.destructibleInfo;
	
	AssertEx( IsDefined( destructibleInfo ), "Setup destructibles did not execute properly for this destructible" );
	
	foreach ( dot in dots )
	{
		if ( IsDefined( level.destructible_type[ destructibleInfo ].destructible_dots ) )
			return;
		
		if ( IsDefined( dot.script_parameters ) &&
			 IsSubStr( dot.script_parameters, "destructible_type" ) &&
			 IsSubStr( dot.script_parameters, self.destructible_type ) )
		{
			// This isnt the best solution. With how are prefabs system works I basically look for the dot reference closest to 
			// the destructible origin
			
			if ( DistanceSquared( self.origin, dot.origin ) < 1 )
			{
				triggers = GetEntArray( dot.target, "targetname" );
				level.destructible_type[ destructibleInfo ].destructible_dots = [];
				
				// Find out which triggers are associated with this destructible and "precache" the info
				
				foreach ( trigger in triggers )
				{
					script_index = trigger.script_index;
					
					AssertEx( IsDefined( script_index ), "Must specify a script_index for trigger being used as DOT in destructible prefab" );
					
					if ( !IsDefined( level.destructible_type[ destructibleInfo ].destructible_dots[ script_index ] ) )
						level.destructible_type[ destructibleInfo ].destructible_dots[ script_index ] = [];
					
					triggerIndex = level.destructible_type[ destructibleInfo ].destructible_dots[ script_index ].size;
					
					level.destructible_type[ destructibleInfo ].destructible_dots[ script_index ][ triggerIndex ][ "classname" ] 	= trigger.classname;
					level.destructible_type[ destructibleInfo ].destructible_dots[ script_index ][ triggerIndex ][ "origin" ]		= trigger.origin;
					spawnflags = ter_op( IsDefined( trigger.spawnflags ), trigger.spawnflags, 0 );
					level.destructible_type[ destructibleInfo ].destructible_dots[ script_index ][ triggerIndex ][ "spawnflags" ] = spawnflags;
					
					switch( trigger.classname )
					{
						case "trigger_radius":
							level.destructible_type[ destructibleInfo ].destructible_dots[ script_index ][ triggerIndex ][ "radius" ] = trigger.height;
							level.destructible_type[ destructibleInfo ].destructible_dots[ script_index ][ triggerIndex ][ "height" ] = trigger.height;
							break;
						default:
							AssertMsg( "This class is not supported for DOTs" );
					}
					trigger Delete();
				}
				break;
			}
		}	
	}
}

setup_destructibles( cached )
{
	if ( !isdefined( cached ) )
		cached = false;

	//---------------------------------------------------------------------
	// Figure out what destructible information this entity should use
	//---------------------------------------------------------------------
	destructibleInfo= undefined;
	AssertEx( IsDefined( self.destructible_type ), "Destructible object with targetname 'destructible' does not have a 'destructible_type' key / value" );

	self.modeldummyon = false;// - nate added for vehicle dummy stuff. This is so I can turn a destructible into a dummy and throw it around on jeepride.
	self add_damage_owner_recorder();	// Mackey added to track who is damaging the car

	self.destructibleInfo= common_scripts\_destructible_types::makeType( self.destructible_type );
	//println( "### DESTRUCTIBLE ### assigned infotype index: " + self.destructibleInfo);
	if ( self.destructibleInfo< 0 )
		return;

	/#
	// Store what destructibles we create and where they are located so we can get a list in the console
	if ( !isdefined(level.created_destructibles) )
		level.created_destructibles = [];
	if ( !isdefined( level.created_destructibles[ self.destructible_type ] ) )
		level.created_destructibles[ self.destructible_type ] = [];
	nextIndex = level.created_destructibles[ self.destructible_type ].size;
	level.created_destructibles[ self.destructible_type ][ nextIndex ] = self;
	#/

	if ( !cached )
		precache_destructibles();

	add_destructible_fx();

	//---------------------------------------------------------------------
	// Attach all parts to the entity
	//---------------------------------------------------------------------
	if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts ) )
	{
		self.destructible_parts = [];
		for ( i = 0; i < level.destructible_type[ self.destructibleInfo].parts.size; i++ )
		{
			// create the struct where the info for each entity will be held
			self.destructible_parts[ i ] = SpawnStruct();

			// set it's current state to 0 since it has never taken damage yet and will be on it's first state
			self.destructible_parts[ i ].v[ "currentState" ] = 0;

			// if it has a health value then store it's value
			if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "health" ] ) )
				self.destructible_parts[ i ].v[ "health" ] = level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "health" ];

			// find random attachements such as random advertisements on taxi cabs and attach them now
			if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "random_dynamic_attachment_1" ] ) )
			{
				randAttachmentIndex = RandomInt( level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "random_dynamic_attachment_1" ].size );
				attachTag = level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "random_dynamic_attachment_tag" ][ randAttachmentIndex ];
				attach_model_1 = level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "random_dynamic_attachment_1" ][ randAttachmentIndex ];
				attach_model_2 = level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "random_dynamic_attachment_2" ][ randAttachmentIndex ];
				clipToRemove = level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "clipToRemove" ][ randAttachmentIndex ];
				self thread do_random_dynamic_attachment( attachTag, attach_model_1, attach_model_2, clipToRemove );
			}

			// continue if it's the base model since its not an attached part
			if ( i == 0 )
				continue;

			// attach the part now
			modelName = level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "modelName" ];
			tagName = level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "tagName" ];

			stateIndex = 1;
			while ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ i ][ stateIndex ] ) )
			{
				stateTagName = level.destructible_type[ self.destructibleInfo].parts[ i ][ stateIndex ].v[ "tagName" ];
				stateModelName = level.destructible_type[ self.destructibleInfo].parts[ i ][ stateIndex ].v[ "modelName" ];
				if ( IsDefined( stateTagName ) && stateTagName != tagName )
				{
					self hideapart( stateTagName );
					if ( self.modeldummyon )
						self.modeldummy hideapart( stateTagName );
				}
				stateIndex++;
			}
		}
	}

	// some destructibles have collision that needs to change due to the large change in the destructible when it blows pu
	if ( IsDefined( self.target ) )
		thread destructible_handles_collision_brushes();

	//---------------------------------------------------------------------
	// Make this entity take damage and wait for events
	//---------------------------------------------------------------------
	if ( self.code_classname != "script_vehicle" )
		self SetCanDamage( true );
	if ( isSP() )
		self thread connectTraverses();
	self thread destructible_think();
}

destructible_create( type, tagName, health, validAttackers, validDamageZone, validDamageCause )
{
	//---------------------------------------------------------------------
	// Creates a new information structure for a destructible object
	//---------------------------------------------------------------------
	Assert( IsDefined( type ) );

	if ( !isdefined( level.destructible_type ) )
		level.destructible_type = [];

	destructibleIndex = level.destructible_type.size;


	destructibleIndex = level.destructible_type.size;
	level.destructible_type[ destructibleIndex ] = SpawnStruct();
	level.destructible_type[ destructibleIndex ].v[ "type" ] = type;

	level.destructible_type[ destructibleIndex ].parts = [];
	level.destructible_type[ destructibleIndex ].parts[ 0 ][ 0 ] = SpawnStruct();
	level.destructible_type[ destructibleIndex ].parts[ 0 ][ 0 ].v[ "modelName" ] = self.model;
	level.destructible_type[ destructibleIndex ].parts[ 0 ][ 0 ].v[ "tagName" ] = tagName;
	level.destructible_type[ destructibleIndex ].parts[ 0 ][ 0 ].v[ "health" ] = health;
	level.destructible_type[ destructibleIndex ].parts[ 0 ][ 0 ].v[ "validAttackers" ] = validAttackers;
	level.destructible_type[ destructibleIndex ].parts[ 0 ][ 0 ].v[ "validDamageZone" ] = validDamageZone;
	level.destructible_type[ destructibleIndex ].parts[ 0 ][ 0 ].v[ "validDamageCause" ] = validDamageCause;
	level.destructible_type[ destructibleIndex ].parts[ 0 ][ 0 ].v[ "godModeAllowed" ] = true;
	level.destructible_type[ destructibleIndex ].parts[ 0 ][ 0 ].v[ "rotateTo" ] = self.angles;
	level.destructible_type[ destructibleIndex ].parts[ 0 ][ 0 ].v[ "vehicle_exclude_anim" ] = false;
}

destructible_part( tagName, modelName, health, validAttackers, validDamageZone, validDamageCause, alsoDamageParent, physicsOnExplosion, grenadeImpactDeath, receiveDamageFromParent )
{
	//---------------------------------------------------------------------
	// Adds a part to the last created destructible information structure
	//---------------------------------------------------------------------
	destructibleIndex = ( level.destructible_type.size - 1 );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts.size ) );

	partIndex = level.destructible_type[ destructibleIndex ].parts.size;
	Assert( partIndex > 0 );

	stateIndex = 0;

	destructible_info( partIndex, stateIndex, tagName, modelName, health, validAttackers, validDamageZone, validDamageCause, alsoDamageParent, physicsOnExplosion, grenadeImpactDeath, undefined, receiveDamageFromParent );
}

destructible_state( tagName, modelName, health, validAttackers, validDamageZone, validDamageCause, grenadeImpactDeath, splashRotation )
{
	//---------------------------------------------------------------------
	// Adds a new part that is a state of the last created part
	// When the previous part reaches zero health this part will show up
	// and the previous part will be removed
	//---------------------------------------------------------------------

	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size );

	if ( !isdefined( tagName ) && partIndex == 0 )
		tagName = level.destructible_type[ destructibleIndex ].parts[ partIndex ][ 0 ].v[ "tagName" ];

	destructible_info( partIndex, stateIndex, tagName, modelName, health, validAttackers, validDamageZone, validDamageCause, undefined, undefined, grenadeImpactDeath, splashRotation );
}

destructible_fx( tagName, fxName, useTagAngles, damageType, groupNum, fxCost )
{
	//assert( IsDefined( tagName ) );
	Assert( IsDefined( fxName ) );

	if ( !isdefined( useTagAngles ) )
		useTagAngles = true;

	if ( !isdefined( groupNum ) )
		groupNum = 0;

	if ( !isdefined( fxCost ) )
		fxCost = 0;

	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	fx_size = 0;
	if ( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "fx_filename" ] ) )
		if ( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "fx_filename" ][ groupNum ] ) )
			fx_size = level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "fx_filename" ][ groupNum ].size;

	if ( IsDefined( damageType ) )
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "fx_valid_damagetype" ][ groupNum ][ fx_size ] = damageType;

	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "fx_filename" ][ groupNum ][ fx_size ] = fxName;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "fx_tag" ][ groupNum ][ fx_size ] = tagName;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "fx_useTagAngles" ][ groupNum ][ fx_size ] = useTagAngles;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "fx_cost" ][ groupNum ][ fx_size ] = fxCost;
}

destructible_createDOT_predefined( index )
{
	AssertEx( IsDefined( index ), "Must specify an index >= 0" );
	
	destructibleIndex = ( level.destructible_type.size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	
	stateIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );
	
	if ( !IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ] ) )
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ] = [];
		
	dotIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ].size );
	dot 		= createDOT();
	dot.type	= "predefined";
	dot.index	= index;
	
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ][ dotIndex ] = dot;
}

destructible_createDOT_radius( tag, spawnflags, radius, height )
{
	AssertEx( IsDefined( tag ), "Must define tag where dot with be spawned for destructible" );
	
	destructibleIndex = ( level.destructible_type.size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	
	stateIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );
	
	if ( !IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ] ) )
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ] = [];
		
	dotIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ].size );
	dot		 = createDOT_radius( ( 0, 0, 0 ), spawnflags, radius, height );
	dot.tag  = tag;
	
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ][ dotIndex ] = dot;
}

destructible_setDOT_onTick( delay, interval, duration, minDamage, maxDamage, falloff, type, affected )
{
	destructibleIndex = ( level.destructible_type.size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	
	stateIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );
	
	dotIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ].size - 1 );
	dot			= level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ][ dotIndex ];
	
	Assert( IsDefined( dot ) );
	
	dot setDOT_onTick( delay, interval, duration, minDamage, maxDamage, falloff, type, affected );
	initDOT( type );
}

destructible_setDOT_onTickFunc( onEnterFunc, onExitFunc, onDeathFunc )
{
	destructibleIndex = ( level.destructible_type.size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	
	stateIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );
	
	dotIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ].size - 1 );
	dot			= level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ][ dotIndex ];
	
	Assert( IsDefined( dot ) );
	
	tickIndex  = dot.ticks.size;
	
	dot.ticks[ tickIndex ].onEnterFunc 	= onEnterFunc;
	dot.ticks[ tickIndex ].onExitFunc 	= onExitFunc;
	dot.ticks[ tickIndex ].onDeathFunc 	= onDeathFunc;
}

destructible_buildDOT_onTick( duration, affected )
{
	destructibleIndex = ( level.destructible_type.size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	
	stateIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );
	
	dotIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ].size - 1 );
	dot			= level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ][ dotIndex ];
	
	Assert( IsDefined( dot ) );
	
	dot buildDOT_onTick( duration, affected );
}

destructible_buildDOT_startLoop( count )
{
	destructibleIndex = ( level.destructible_type.size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	
	stateIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );
	
	dotIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ].size - 1 );
	dot			= level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ][ dotIndex ];
	
	Assert( IsDefined( dot ) );
	
	dot buildDOT_startLoop( count );
}

destructible_buildDOT_damage( minDamage, maxDamage, falloff, damageFlag, meansOfDeath, weapon )
{
	destructibleIndex = ( level.destructible_type.size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	
	stateIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );
	
	dotIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ].size - 1 );
	dot			= level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ][ dotIndex ];
	
	Assert( IsDefined( dot ) );
	
	dot buildDOT_damage( minDamage, maxDamage, falloff, damageFlag, meansOfDeath, weapon );
}

destructible_buildDOT_wait( time )
{
	destructibleIndex = ( level.destructible_type.size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	
	stateIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );
	
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );
	
	dotIndex 	= ( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ].size - 1 );
	dot			= level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "dot" ][ dotIndex ];
	
	Assert( IsDefined( dot ) );
	
	dot buildDOT_wait( time );
}

destructible_loopfx( tagName, fxName, loopRate, fxCost )
{
	Assert( IsDefined( tagName ) );
	Assert( IsDefined( fxName ) );
	Assert( IsDefined( loopRate ) );
	Assert( loopRate > 0 );

	if ( !isdefined( fxCost ) )
		fxCost = 0;

	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	fx_size = 0;
	if ( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopfx_filename" ] ) )
		fx_size = level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopfx_filename" ].size;

	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopfx_filename" ][ fx_size ] = fxName;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopfx_tag" ][ fx_size ] = tagName;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopfx_rate" ][ fx_size ] = loopRate;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopfx_cost" ][ fx_size ] = fxCost;
}

destructible_healthdrain( amount, interval, badplaceRadius, badplaceTeam )
{
	Assert( IsDefined( amount ) );

	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "healthdrain_amount" ] = amount;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "healthdrain_interval" ] = interval;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "badplace_radius" ] = badplaceRadius;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "badplace_team" ] = badplaceTeam;
}

destructible_sound( soundAlias, soundCause, groupNum )
{
	Assert( IsDefined( soundAlias ) );

	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );
	
	if ( !isdefined( groupNum ) )
		groupNum = 0;
	
	if ( !isdefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "sound" ] ) )
	{
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "sound" ] = [];
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "soundCause" ] = [];
	}
	
	if ( !isdefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "sound" ][ groupNum ] ) )
	{
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "sound" ][ groupNum ] = [];
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "soundCause" ][ groupNum ] = [];
	}
	
	index = level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "sound" ][ groupNum ].size;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "sound" ][ groupNum ][ index ] = soundAlias;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "soundCause" ][ groupNum ][ index ] = soundCause;

	if ( GetDvarInt( "precache_destructible", 1 ) )
	{
		PrecacheSound( soundAlias );

		soundTagName = level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "tagName" ];
		if ( isdefined( soundTagName ) )
			PrecacheTag( soundTagName );
	}
}


destructible_loopsound( soundAlias, loopsoundCause )
{
	Assert( IsDefined( soundAlias ) );

	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	if ( !isdefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopsound" ] ) )
	{
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopsound" ] = [];
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopsoundCause" ] = [];
	}

	index = level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopsound" ].size;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopsound" ][ index ] = soundAlias;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "loopsoundCause" ][ index ] = loopsoundCause;

	if ( GetDvarInt( "precache_destructible", 1 ) )
	{
		PrecacheSound( soundAlias );

		loopsoundTagName = level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "tagName" ];
		if ( isdefined( loopsoundTagName ) )
			PrecacheTag( loopsoundTagName );
	}
}

destructible_anim( animName, animTree, animType, vehicle_exclude, groupNum, mpAnim, maxStartDelay, animRateMin, animRateMax )
{
	if ( !isdefined( vehicle_exclude ) )
		vehicle_exclude = false;

	Assert( IsDefined( anim ) );
	Assert( IsDefined( animName ) );
	Assert( IsDefined( animtree ) );

	if ( !isdefined( groupNum ) )
		groupNum = 0;

	array = [];
	array[ "anim" ] = animName;
	array[ "animTree" ] = animtree;
	array[ "animType" ] = animType;
	array[ "vehicle_exclude_anim" ] = vehicle_exclude;
	array[ "groupNum" ] = groupNum;
	array[ "mpAnim" ] = mpAnim;
	array[ "maxStartDelay" ] = maxStartDelay;
	array[ "animRateMin" ] = animRateMin;
	array[ "animRateMax" ] = animRateMax;
	add_array_to_destructible( "animation", array );
}

destructible_spotlight( tag )
{
	AssertEx( IsDefined( tag ), "Tag wasn't defined for destructible_spotlight" );
	array = [];
	array[ "spotlight_tag" ] = tag;
	array[ "spotlight_fx" ] = "spotlight_fx";
	array[ "spotlight_brightness" ] = 0.85;
	array[ "randomly_flip" ] = true;

	dvars = [];
	dvars[ "r_spotlightendradius" ] = 1200;
	dvars[ "r_spotlightstartradius" ] = 50;
	array[ "dvars" ] = dvars;

	add_keypairs_to_destructible( array );
}

add_key_to_destructible( key, val )
{
	AssertEx( IsDefined( key ), "Key wasn't defined!" );
	AssertEx( IsDefined( val ), "Val wasn't defined!" );

	array = [];
	array[ key ] = val;
	add_keypairs_to_destructible( array );
}

/*
=============
///ScriptDocBegin
"Name: add_keypairs_to_destructible( <array> )"
"Summary: Goes through the array and adds each key/val to .v."
"Module: Destructibles"
"MandatoryArg: <array>: Array of keypairs."
"Example: add_keypairs_to_destructible( array );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_keypairs_to_destructible( array )
{
	// add a single flat array to the destructible, overwriting any existing identical keys.
	destructibleIndex = level.destructible_type.size - 1;
	partIndex = level.destructible_type[ destructibleIndex ].parts.size - 1;
	stateIndex = level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1;

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	foreach ( key, val in array )
	{
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ key ] = val;
	}
}

/*
=============
///ScriptDocBegin
"Name: add_array_to_destructible( <array_name> , <array> )"
"Summary: Goes through the array and adds each key/val to .v."
"Module: Destructibles"
"MandatoryArg: <array_name>: Array of keypairs."
"MandatoryArg: <array>: Array of keypairs."
"Example: add_array_to_destructible( array );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
add_array_to_destructible( array_name, array )
{
	// add an array under a key name, so you can have multiple arrays under a given key name
	destructibleIndex = level.destructible_type.size - 1;
	partIndex = level.destructible_type[ destructibleIndex ].parts.size - 1;
	stateIndex = level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1;

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	v = level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v;

	if ( !isdefined( v[ array_name ] ) )
	{
		v[ array_name ] = [];
	}

	v[ array_name ][ v[ array_name ].size ] = array;

	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v = v;
}

destructible_car_alarm()
{
	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "triggerCarAlarm" ] = true;
}

destructible_lights_out( range )
{
	if ( !isdefined( range ) )
		range = 256;

	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "break_nearby_lights" ] = range;
}

random_dynamic_attachment( tagName, attachment_1, attachment_2, clipToRemove )
{
	// made so I can put random advertisements on the destructible taxi cabs without making lots of destructible types for each version
	
	Assert( IsDefined( tagName ) );
	Assert( IsDefined( attachment_1 ) );

	if ( !isdefined( attachment_2 ) )
		attachment_2 = "";

	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	//stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );
	stateIndex = 0;

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	if ( !isdefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "random_dynamic_attachment_1" ] ) )
	{
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "random_dynamic_attachment_1" ] = [];
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "random_dynamic_attachment_2" ] = [];
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "random_dynamic_attachment_tag" ] = [];
	}

	index = level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "random_dynamic_attachment_1" ].size;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "random_dynamic_attachment_1" ][ index ] = attachment_1;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "random_dynamic_attachment_2" ][ index ] = attachment_2;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "random_dynamic_attachment_tag" ][ index ] = tagName;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "clipToRemove" ][ index ] = clipToRemove;
}

destructible_physics( physTagName, physVelocity )
{
	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	if ( !isdefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "physics" ] ) )
	{
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "physics" ] = [];
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "physics_tagName" ] = [];
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "physics_velocity" ] = [];
	}

	index = level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "physics" ].size;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "physics" ][ index ] = true;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "physics_tagName" ][ index ] = physTagName;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "physics_velocity" ][ index ] = physVelocity;
}

destructible_splash_damage_scaler( damage_multiplier )
{
	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "splash_damage_scaler" ] = damage_multiplier;
}

destructible_explode( force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continueDamage, originOffset, earthQuakeScale, earthQuakeRadius, originOffset3d, delaytime )
{
	destructibleIndex = ( level.destructible_type.size - 1 );
	partIndex = ( level.destructible_type[ destructibleIndex ].parts.size - 1 );
	stateIndex = ( level.destructible_type[ destructibleIndex ].parts[ partIndex ].size - 1 );

	Assert( IsDefined( level.destructible_type ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ] ) );
	Assert( IsDefined( level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] ) );

	if ( isSP() )
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "explode_range" ] = rangeSP;
	else
		level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "explode_range" ] = rangeMP;

	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "explode" ] = true;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "explode_force_min" ] = force_min;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "explode_force_max" ] = force_max;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "explode_mindamage" ] = mindamage;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "explode_maxdamage" ] = maxdamage;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "continueDamage" ] = continueDamage;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "originOffset" ] = originOffset;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "earthQuakeScale" ] = earthQuakeScale;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "earthQuakeRadius" ] = earthQuakeRadius;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "originOffset3d" ] = originOffset3d;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "delaytime" ] = delaytime;
}

destructible_info( partIndex, stateIndex, tagName, modelName, health, validAttackers, validDamageZone, validDamageCause, alsoDamageParent, physicsOnExplosion, grenadeImpactDeath, splashRotation, receiveDamageFromParent )
{
	Assert( IsDefined( partIndex ) );
	Assert( IsDefined( stateIndex ) );
	Assert( IsDefined( level.destructible_type ) );
	Assert( level.destructible_type.size > 0 );

	if ( IsDefined( modelName ) )
		modelName = ToLower( modelName );

	destructibleIndex = ( level.destructible_type.size - 1 );

	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ] = SpawnStruct();
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "modelName" ] = modelName;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "tagName" ] = tagName;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "health" ] = health;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "validAttackers" ] = validAttackers;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "validDamageZone" ] = validDamageZone;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "validDamageCause" ] = validDamageCause;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "alsoDamageParent" ] = alsoDamageParent;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "physicsOnExplosion" ] = physicsOnExplosion;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "grenadeImpactDeath" ] = grenadeImpactDeath;
	// sanity check please. I set this here so that I don't have to do isdefined on every part evertime it gets hit
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "godModeAllowed" ] = false;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "splashRotation" ] = splashRotation;
	level.destructible_type[ destructibleIndex ].parts[ partIndex ][ stateIndex ].v[ "receiveDamageFromParent" ] = receiveDamageFromParent;
}

precache_destructibles()
{
	// I needed this to be seperate for vehicle scripts.
	//---------------------------------------------------------------------
	// Precache referenced models and load referenced effects
	//---------------------------------------------------------------------

	if ( !isdefined( level.destructible_type[ self.destructibleInfo].parts ) )
		return;
	
	//if ( !isdefined( level.precachedModels ) )
	//	level.precachedModels = [];
	
	for ( i = 0; i < level.destructible_type[ self.destructibleInfo].parts.size; i++ )
	{
		for ( j = 0; j < level.destructible_type[ self.destructibleInfo].parts[ i ].size; j++ )
		{
			if ( level.destructible_type[ self.destructibleInfo].parts[ i ].size <= j )
				continue;

			if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ i ][ j ].v[ "modelName" ] ) )
			{
				//model = level.destructible_type[ self.destructibleInfo].parts[ i ][ j ].v[ "modelName" ];
				//if ( !isdefined( level.precachedModels[ model ] ) )
				//{
				//	level.precachedModels[ model ] = true;
				//	println( "precachemodel( " + model + " )" );
				//}
				PreCacheModel( level.destructible_type[ self.destructibleInfo].parts[ i ][ j ].v[ "modelName" ] );
			}

			// in MP we have to precache animations that will be used
			if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ i ][ j ].v[ "animation" ] ) )
			{
				animGroups = level.destructible_type[ self.destructibleInfo].parts[ i ][ j ].v[ "animation" ];
				foreach ( group in animGroups )
				{
					if ( IsDefined( group[ "mpAnim" ] ) )
						noself_func( "precacheMpAnim", group[ "mpAnim" ] );
				}
			}

			// find random attachements such as random advertisements on taxi cabs and precache them now
			if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ i ][ j ].v[ "random_dynamic_attachment_1" ] ) )
			{
				foreach ( model in level.destructible_type[ self.destructibleInfo].parts[ i ][ j ].v[ "random_dynamic_attachment_1" ] )
				{
					if ( IsDefined( model ) && model != "" )
					{
						PreCacheModel( model );
						PreCacheModel( model + DESTROYED_ATTACHMENT_SUFFIX );
						
						//if ( !isdefined( level.precachedModels[ model ] ) )
						//{
						//	level.precachedModels[ model ] = true;
						//	println( "precachemodel( " + model + " )" );
						//}
						
						//if ( !isdefined( level.precachedModels[ model + DESTROYED_ATTACHMENT_SUFFIX ] ) )
						//{
						//	level.precachedModels[ model + DESTROYED_ATTACHMENT_SUFFIX ] = true;
						//	println( "precachemodel( " + model + DESTROYED_ATTACHMENT_SUFFIX + " )" );
						//}
					}
				}
				foreach ( model in level.destructible_type[ self.destructibleInfo].parts[ i ][ j ].v[ "random_dynamic_attachment_2" ] )
				{
					if ( IsDefined( model ) && model != "" )
					{
						PreCacheModel( model );
						PreCacheModel( model + DESTROYED_ATTACHMENT_SUFFIX );
						
						//if ( !isdefined( level.precachedModels[ model ] ) )
						//{
						//	level.precachedModels[ model ] = true;
						//	println( "precachemodel( " + model + " )" );
						//}
						
						//if ( !isdefined( level.precachedModels[ model + DESTROYED_ATTACHMENT_SUFFIX ] ) )
						//{
						//	level.precachedModels[ model + DESTROYED_ATTACHMENT_SUFFIX ] = true;
						//	println( "precachemodel( " + model + DESTROYED_ATTACHMENT_SUFFIX + " )" );
						//}
					}
				}
			}
		}
	}
}

add_destructible_fx()
{
	// I needed this to be seperate for vehicle scripts.
	//---------------------------------------------------------------------
	// Precache referenced models and load referenced effects
	//---------------------------------------------------------------------

	if ( !isdefined( level.destructible_type[ self.destructibleInfo].parts ) )
		return;
	
	//if ( !isdefined( level.precachedFX ) )
	//	level.precachedFX = [];
	
	for ( i = 0; i < level.destructible_type[ self.destructibleInfo].parts.size; i++ )
	{
		for ( j = 0; j < level.destructible_type[ self.destructibleInfo].parts[ i ].size; j++ )
		{
			if ( level.destructible_type[ self.destructibleInfo].parts[ i ].size <= j )
				continue;

			part = level.destructible_type[ self.destructibleInfo].parts[ i ][ j ];

			if ( IsDefined( part.v[ "fx_filename" ] ) )
			{
				for ( g = 0; g < part.v[ "fx_filename" ].size; g++ )
				{
					// for multiple checks on fx when doing conditional fx playing
					fx_filenames = part.v[ "fx_filename" ][ g ];
					if ( IsDefined( fx_filenames ) )
					{
						// has we already set this up?
						if ( IsDefined( part.v[ "fx" ] ) && IsDefined( part.v[ "fx" ][ g ] ) && part.v[ "fx" ][ g ].size == fx_filenames.size )
							continue;

						foreach ( idx, fx_filename in fx_filenames )
						{
							fx = _loadfx( fx_filename );
							part.v[ "fx" ][ g ][ idx ] = fx;

							if ( GetDvarInt( "precache_destructible", 1 ) )
							{
								fx_tag = part.v[ "fx_tag" ][ g ][ idx ];
								if ( isdefined( fx_tag ) )
									PrecacheFXOnTag( fx, fx_tag );
							}
							
							//if ( !isdefined( level.precachedFX[ fx_filename ] ) )
							//{
							//	level.precachedFX[ fx_filename ] = true;
							//	println( "loadfx( " + fx_filename + " )" );
							//}
						}
					}
				}
			}

			loopfx_filenames = part.v[ "loopfx_filename" ];
			if ( IsDefined( loopfx_filenames ) )
			{
				// has we already set this up?
				if ( IsDefined( part.v[ "loopfx" ] ) && part.v[ "loopfx" ].size == loopfx_filenames.size )
					continue;

				foreach ( idx, loopfx_filename in loopfx_filenames )
				{
					loopfx = _loadfx( loopfx_filename );
					part.v[ "loopfx" ][ idx ] = loopfx;

					if ( GetDvarInt( "precache_destructible", 1 ) )
					{
						loopfx_tag = part.v[ "loopfx_tag" ][ idx ];
						PrecacheFXOnTag( loopfx, loopfx_tag );
					}
					
					//if ( !isdefined( level.precachedFX[ loopfx_filename ] ) )
					//{
					//	level.precachedFX[ loopfx_filename ] = true;
					//	println( "loadfx( " + loopfx_filename + " )" );
					//}
				}
			}
		}
	}

}


canDamageDestructible( testDestructible )
{
	foreach ( destructible in self.destructibles )
	{
		if ( destructible == testDestructible )
			return true;
	}
	return false;
}

destructible_think()
{
	//---------------------------------------------------------------------
	// Force it to run update part one time first so we can have parts with
	// 0 health that will start on level load instead of waiting for damage
	//---------------------------------------------------------------------
	damage = 0;
	modelName = self.model;
	tagName = undefined;
	point = self.origin;
	direction_vec = undefined;
	attacker = undefined;
	damageType = undefined;
	self destructible_update_part( damage, modelName, tagName, point, direction_vec, attacker, damageType );

	//---------------------------------------------------------------------
	// Wait until this entity takes damage
	//---------------------------------------------------------------------
	self endon( "stop_taking_damage" );
	for ( ;; )
	{
		// set these to undefined to clear them for each loop to save variables
		damage = undefined;
		attacker = undefined;
		direction_vec = undefined;
		point = undefined;
		type = undefined;
		modelName = undefined;
		tagName = undefined;
		partName = undefined;
		dflags = undefined;
		
		self waittill( "damage", damage, attacker, direction_vec, point, type, modelName, tagName, partName, dflags );
		prof_begin( "_destructible" );

		if ( !isdefined( damage ) )
			continue;
		if ( IsDefined( attacker ) && IsDefined( attacker.type ) && attacker.type == "soft_landing" && !attacker canDamageDestructible( self ) )
			continue;

		if ( isSP() )
			damage *= SP_DAMAGE_BIAS;
		else
			damage *= MP_DAMAGE_BIAS;
		
		if ( damage <= 0 )
			continue;

		if ( isSP() )
		{
			if ( IsDefined( attacker ) && IsPlayer( attacker ) )
				self.damageOwner = attacker;
		}
		else
		{
			if ( IsDefined( attacker ) && IsPlayer( attacker ) )
				self.damageOwner = attacker;
			// osprey gunner could shoot a destructible, or anything with a player as the gunner
			else if( IsDefined( attacker ) && IsDefined( attacker.gunner ) && IsPlayer( attacker.gunner ) )
				self.damageOwner = attacker.gunner;
		}

		type = getDamageType( type );
		Assert( IsDefined( type ) );
		
		// shotguns only do one notify so we need to amp up the damage
		if ( is_shotgun_damage( attacker, type ) )
		{
			if ( isSP() )
				damage *= SP_SHOTGUN_BIAS;
			else
				damage *= MP_SHOTGUN_BIAS;
		}
		
		/#
		if ( GetDvarInt( "debug_destructibles" , 0 ) == 1 )
		{
			Print3d( point, ".", ( 1, 1, 1 ), 1.0, 0.5, 100 );
			if ( IsDefined( damage ) )
				IPrintLn( "damage amount: " + damage );
			if ( IsDefined( modelName ) )
				IPrintLn( "hit model: " + modelName );
			if ( IsDefined( tagName ) )
				IPrintLn( "hit model tag: " + tagName );
			else
				IPrintLn( "hit model tag: " );
		}
		#/

		// override for when base model is damaged. We dont want to pass in empty strings
		if ( !isdefined( modelName ) || ( modelName == "" ) )
		{
			Assert( IsDefined( self.model ) );
			modelName = self.model;
		}
		if ( IsDefined( tagName ) && tagName == "" )
		{
			if ( IsDefined( partName ) && partName != "" && partName != "tag_body" && partName != "body_animate_jnt" )
				tagName = partName;
			else
				tagName = undefined;

			baseModelTag = level.destructible_type[ self.destructibleInfo].parts[ 0 ][ 0 ].v[ "tagName" ];
			if ( IsDefined( baseModelTag ) && IsDefined( partName ) && ( baseModelTag == partName ) )
				tagName = undefined;
		}

		prof_end( "_destructible" );

		// special handling for splash and projectile damage
		if ( type == "splash" )
		{
			/#
			if ( GetDvarInt( "debug_destructibles" , 0 ) == 1 )
				IPrintLn( "type = splash" );
			#/

			if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ 0 ][ 0 ].v[ "splash_damage_scaler" ] ) )
				damage *= level.destructible_type[ self.destructibleInfo].parts[ 0 ][ 0 ].v[ "splash_damage_scaler" ];
			else
			{
				if ( isSP() )
					damage *= SP_EXPLOSIVE_DAMAGE_BIAS;
				else
					damage *= MP_EXPLOSIVE_DAMAGE_BIAS;
			}

			self destructible_splash_damage( Int( damage ), point, direction_vec, attacker, type );
			continue;
		}

		self thread destructible_update_part( Int( damage ), modelName, tagName, point, direction_vec, attacker, type );
	}
}

is_shotgun_damage( attacker, type )
{
	if ( type != "bullet" )
		return false;
	
	if ( !isdefined( attacker ) )
		return false;

	currentWeapon = undefined;
	if ( IsPlayer( attacker )  )
	{
		currentweapon = attacker getCurrentWeapon();
	}
    else if( isdefined( level.enable_ai_shotgun_destructible_damage ) && level.enable_ai_shotgun_destructible_damage )
    {
        if( isdefined( attacker.weapon ) )
            currentweapon = attacker.weapon;
    }

	if ( !isdefined( currentweapon ) )
		return false;
	
	class = weaponClass( currentweapon );
	if ( isdefined( class ) && class == "spread" )
		return true;
	
	return false;
}

getPartAndStateIndex( modelName, tagName )
{
	Assert( IsDefined( modelName ) );

	info = SpawnStruct();
	info.v = [];

	partIndex = -1;
	stateIndex = -1;
	Assert( IsDefined( self.model ) );
	if ( ( ToLower( modelName ) == ToLower( self.model ) ) && ( !isdefined( tagName ) ) )
	{
		modelName = self.model;
		tagName = undefined;
		partIndex = 0;
		stateIndex = 0;
	}

	for ( i = 0; i < level.destructible_type[ self.destructibleInfo].parts.size; i++ )
	{
		stateIndex = self.destructible_parts[ i ].v[ "currentState" ];

		if ( level.destructible_type[ self.destructibleInfo].parts[ i ].size <= stateIndex )
			continue;

		if ( !isdefined( tagName ) )
			continue;

		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ i ][ stateIndex ].v[ "tagName" ] ) )
		{
			partTagName = level.destructible_type[ self.destructibleInfo].parts[ i ][ stateIndex ].v[ "tagName" ];
			if ( tolower( partTagName ) == tolower( tagName ) )
			{
				partIndex = i;
				break;
			}
		}
	}
	Assert( stateIndex >= 0 );
	Assert( IsDefined( partIndex ) );

	info.v[ "stateIndex" ] = stateindex;
	info.v[ "partIndex" ] = partindex;

	return info;
}

destructible_update_part( damage, modelName, tagName, point, direction_vec, attacker, damageType, partInfo )
{
	//---------------------------------------------------------------------
	// Find what part this is, or is a child of. If the base model was
	// the entity that was damaged the part index will be -1
	//---------------------------------------------------------------------
	if ( !isdefined( self.destructible_parts ) )
		return;
	if ( self.destructible_parts.size == 0 )
		return;
		
	
	if( level.fast_destructible_explode )		
		self endon ( "destroyed" );

	prof_begin( "_destructible" );

	info = getPartAndStateIndex( modelName, tagName );
	stateIndex = info.v[ "stateIndex" ];
	partIndex = info.v[ "partIndex" ];

	prof_end( "_destructible" );

	if ( partIndex < 0 )
		return;

	//---------------------------------------------------------------------
	// Deduct the damage amount from the part's health
	// If the part runs out of health go to the next state
	//---------------------------------------------------------------------
	state_before = stateIndex;
	updateHealthValue = false;
	delayModelSwap = false;
	prof_begin( "_destructible" );
	for ( ;; )
	{
		stateIndex = self.destructible_parts[ partIndex ].v[ "currentState" ];

		// there isn't another state to go to when damaged
		if ( !isdefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ] ) )
			break;

		// see if the model is also supposed to damage the parent
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ 0 ].v[ "alsoDamageParent" ] ) )
		{
			if ( getDamageType( damageType ) != "splash" )
			{
				ratio = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ 0 ].v[ "alsoDamageParent" ];
				parentDamage = Int( damage * ratio );
				self thread notifyDamageAfterFrame( parentDamage, attacker, direction_vec, point, damageType, "", "" );
			}
		}

		// loop through all parts to see which ones also need to get this damage applied to them ( based on their "receiveDamageFromParent" value )
		if ( getDamageType( damageType ) != "splash" )
		{
			foreach ( part in level.destructible_type[ self.destructibleInfo].parts )
			{
				if ( !isdefined( part[ 0 ].v[ "receiveDamageFromParent" ] ) )
					continue;

				if ( !isdefined( part[ 0 ].v[ "tagName" ] ) )
					continue;

				ratio = part[ 0 ].v[ "receiveDamageFromParent" ];
				Assert( ratio > 0 );

				childDamage = Int( damage * ratio );
				childTagName = part[ 0 ].v[ "tagName" ];
				self thread notifyDamageAfterFrame( childDamage, attacker, direction_vec, point, damageType, "", childTagName );
			}
		}

		if ( !isdefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ].v[ "health" ] ) )
			break;
		if ( !isdefined( self.destructible_parts[ partIndex ].v[ "health" ] ) )
			break;

		if ( updateHealthValue )
			self.destructible_parts[ partIndex ].v[ "health" ] = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ].v[ "health" ];
		updateHealthValue = false;

		/#
		if ( GetDvarInt( "debug_destructibles" , 0 ) == 1 )
		{
			IPrintLn( "stateindex: " + stateIndex );
			IPrintLn( "damage: " + damage );
			IPrintLn( "health( before ): " + self.destructible_parts[ partIndex ].v[ "health" ] );
		}
		#/

		// Handle grenades hitting glass parts. Grenades should make the glass completely break instead of just doing 1 damage and shattering the glass
		if ( ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ].v[ "grenadeImpactDeath" ] ) ) && ( damageType == "impact" ) )
			damage = 100000000;

		// apply the damage to the part if the attacker was a valid attacker
		savedHealth = self.destructible_parts[ partIndex ].v[ "health" ];
		validAttacker = self isAttackerValid( partIndex, stateIndex, attacker );
		if ( validAttacker )
		{
			validDamageCause = self isValidDamageCause( partIndex, stateIndex, damageType );
			if ( validDamageCause )
			{
				if ( IsDefined( attacker ) )
				{
					if ( IsPlayer( attacker ) )
					{
						self.player_damage += damage;
					}
					else
					{
						if ( attacker != self )
							self.non_player_damage += damage;
					}
				}

				// Chad - ask Brent why we think melee is worth 100000 damage
				if ( IsDefined( damageType ) )
				{
					if ( damageType == "melee" || damageType == "impact" )
						damage = 100000;
				}

				self.destructible_parts[ partIndex ].v[ "health" ] -= damage;
			}
		}

		/#
		if ( GetDvarInt( "debug_destructibles" , 0 ) == 1 )
			IPrintLn( "health( after ): " + self.destructible_parts[ partIndex ].v[ "health" ] );
		#/

		// if the part still has health left then we're done
		if ( self.destructible_parts[ partIndex ].v[ "health" ] > 0 )
		{
			prof_end( "_destructible" );
			return;
		}

		// cap on the number of destructibles killed in a single frame
		if ( IsDefined( partInfo ) )
		{
			partInfo.v[ "fxcost" ] = get_part_FX_cost_for_action_state( partIndex, self.destructible_parts[ partIndex ].v[ "currentState" ] );

			add_destructible_to_frame_queue( self, partInfo, damage );
			
			if ( !IsDefined( self.waiting_for_queue ) )
				self.waiting_for_queue = 1;
			else
				self.waiting_for_queue++;
			
			self waittill( "queue_processed", success );
			
			self.waiting_for_queue--;			
			if ( self.waiting_for_queue == 0 )
				self.waiting_for_queue = undefined;
						
			if ( !success )// can we be destroyed this frame?
			{
				self.destructible_parts[ partIndex ].v[ "health" ] = savedHealth;
				return;
			}
		}

		// if the part ran out of health then carry over to the next part
		damage = Int( abs( self.destructible_parts[ partIndex ].v[ "health" ] ) );

		// Brent asks - why is this condition here?  It'll never trigger given that abs() does the following:
		// "fabs returns the absolute value of x.  Absolute value is a number's distance from zero on the number line. The absolute value of -4 is 4; the absolute value of 4 is 4."
		// It should probably be removed
		if ( damage < 0 )
		{
			prof_end( "_destructible" );
			return;
		}

		self.destructible_parts[ partIndex ].v[ "currentState" ]++;
		stateIndex = self.destructible_parts[ partIndex ].v[ "currentState" ];
		actionStateIndex = ( stateIndex - 1 );

		// use these rather than re-getting them all the time. This insures that we do
		// not overwrite their values too.
		action_v = undefined;
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ] ) )
			action_v = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v;

		state_v = undefined;
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ] ) )
			state_v = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ].v;

		if ( !isdefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ] ) )
		{
			prof_end( "_destructible" );
			return;
		}

		//---------------------------------------------------------------------
		// A state change is required so detach the old model or replace it if 
		// it's the base model that took the damage.
		// Then attach the model ( if specified ) used for the new state
		// Only do this if there is another state to go to, some parts might have
		// fx or anims, or sounds but no next model to go to
		//---------------------------------------------------------------------

		// if the part is meant to explode on this state set a flag. Actual explosion will be done down below
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "explode" ] ) )
			self.exploding = true;

		// stop all previously looped sounds
		if ( IsDefined( self.loopingSoundStopNotifies ) && IsDefined( self.loopingSoundStopNotifies[ toString( partIndex ) ] ) )
		{
			for ( i = 0; i < self.loopingSoundStopNotifies[ toString( partIndex ) ].size; i++ )
			{
				self notify( self.loopingSoundStopNotifies[ toString( partIndex ) ][ i ] );
				if ( isSP() && self.modeldummyon )
					self.modeldummy notify( self.loopingSoundStopNotifies[ toString( partIndex ) ][ i ] );
			}
			self.loopingSoundStopNotifies[ toString( partIndex ) ] = undefined;
		}

		// setup our destructible light if we want one and can find one
		if ( IsDefined( action_v[ "break_nearby_lights" ] ) )
		{
			self destructible_get_my_breakable_light( action_v[ "break_nearby_lights" ] );
		}

		// swap the model
		// this doesn't work when threaded off to another function
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ] ) )
		{
			if ( partIndex == 0 )	// base model damaged
			{
				newModel = state_v[ "modelName" ];
				if ( IsDefined( newModel ) && newModel != self.model )
				{
					self SetModel( newModel );
					if ( isSP() && self.modeldummyon )
						self.modeldummy SetModel( newModel );
					destructible_splash_rotatation( state_v );
				}
			}
			else	// part was damaged, not the base model
			{
				// handle a part getting damaged here - must be detached and reattached
				self hideapart( tagName );
				if ( isSP() && self.modeldummyon )
					self.modeldummy hideapart( tagName );

				tagName = state_v[ "tagName" ];
				if ( IsDefined( tagName ) )
				{
					self showapart( tagName );
					if ( isSP() && self.modeldummyon )
						self.modeldummy showapart( tagName );
				}
			}
		}

		eModel = get_dummy();

		// If its exploding clear all previous animations on the destructible. The only animation that will play after this is an explosion animation
		if ( IsDefined( self.exploding ) )
			self clear_anims( eModel );

		// if the part has an anim then play it now
		groupNumber = destructible_animation_think( action_v, eModel, damageType, partIndex );

		// if the part has fx then play it now
		groupNumber = destructible_fx_think( action_v, eModel, damageType, partIndex, groupNumber );
		
		// if the part has a soundalias then play it now
		groupNumber = destructible_sound_think( action_v, eModel, damageType, groupNumber );
		
		// if the part has a looping fx then play it now
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "loopfx" ] ) )
		{
			loopfx_size = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "loopfx_filename" ].size;

			if ( loopfx_size > 0 )
				self notify( "FX_State_Change" + partIndex );

			for ( idx = 0; idx < loopfx_size; idx++ )
			{
				Assert( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "loopfx_tag" ][ idx ] ) );
				loopfx = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "loopfx" ][ idx ];
				loopfx_tag = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "loopfx_tag" ][ idx ];
				loopRate = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "loopfx_rate" ][ idx ];
				self thread loopfx_onTag( loopfx, loopfx_tag, loopRate, partIndex );
			}
		}

		// if the part has a looping soundalias then start looping it now
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "loopsound" ] ) )
		{
			for ( i = 0; i < level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "loopsound" ].size; i++ )
			{
				validSoundCause = self isValidSoundCause( "loopsoundCause", action_v, i, damageType );
				if ( validSoundCause )
				{
					loopsoundAlias = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "loopsound" ][ i ];
					loopsoundTagName = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "tagName" ];
					self thread play_loop_sound_on_destructible( loopsoundAlias, loopsoundTagName );

					if ( !isdefined( self.loopingSoundStopNotifies ) )
						self.loopingSoundStopNotifies = [];
					if ( !isdefined( self.loopingSoundStopNotifies[ toString( partIndex ) ] ) )
						self.loopingSoundStopNotifies[ toString( partIndex ) ] = [];
					size = self.loopingSoundStopNotifies[ toString( partIndex ) ].size;
					self.loopingSoundStopNotifies[ toString( partIndex ) ][ size ] = "stop sound" + loopsoundAlias;
				}
			}
		}

		// if the part is supposed to trigger a car alarm
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "triggerCarAlarm" ] ) )
		{
			self thread do_car_alarm();
		}

		// if the part is supposed to trigger a car alarm
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "break_nearby_lights" ] ) )
		{
			self thread break_nearest_light();
		}

		// if the part should drain health then start the drain
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "healthdrain_amount" ] ) )
		{
			self notify( "Health_Drain_State_Change" + partIndex );
			healthdrain_amount 		 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "healthdrain_amount" ];
			healthdrain_interval 	 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "healthdrain_interval" ];
			healthdrain_modelName 	 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "modelName" ];
			healthdrain_tagName 	 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "tagName" ];
			badplaceRadius 			 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "badplace_radius" ];
			badplaceTeam 			 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "badplace_team" ];
			if ( healthdrain_amount > 0 )
			{
				Assert( ( IsDefined( healthdrain_interval ) ) && ( healthdrain_interval > 0 ) );
				self thread health_drain( healthdrain_amount, healthdrain_interval, partIndex, healthdrain_modelName, healthdrain_tagName, badplaceRadius, badplaceTeam );
			}
		}

		// DOT 
		//	- Usually this will happen the same time as explode.
		//  - This is setup so it can theoretically happen at any given state
		
		dots = level.destructible_type[ self.destructibleInfo ].parts[ partIndex ][ actionStateIndex ].v[ "dot" ];
		
		if ( IsDefined( dots ) )
		{
			foreach ( dot in dots )
			{
				dotIndex = dot.index;
				
				if ( dot.type == "predefined" && IsDefined( dotIndex ) )
				{
					dot_group = [];
					
					foreach ( triggerIndex in level.destructible_type[ self.destructibleInfo ].destructible_dots[ dotIndex ] )
					{
						classname 	= triggerIndex[ "classname" ];
						_dot 		= undefined;
						
						switch ( classname )
						{
							case "trigger_radius":
								origin 		= triggerIndex[ "origin" ];
								spawnflags 	= triggerIndex[ "spawnflags" ];
								radius 		= triggerIndex[ "radius" ];
								height 		= triggerindex[ "height" ];
								
								_dot 						= createDOT_radius( self.origin + origin, spawnflags, radius, height );
								_dot.ticks 					= dot.ticks;
								dot_group[ dot_group.size ] = _dot;
								break;
							default:
						}
					}
					level thread startDOT_group( dot_group );
				}
				else
				{
					if ( IsDefined( dot ) )
					{
						if ( IsDefined( dot.tag ) )
							dot setDOT_origin( self GetTagOrigin( dot.tag ) );
						level thread startDOT_group( [ dot ] );
					}
				}
			}
			dots = undefined;
		}
					
		// if the part is meant to explode on this state then do it now. Causes all attached models to become physics with the specified force
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "explode" ] ) )
		{
			delayModelSwap 		 = true;
			force_min 	 	 	 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "explode_force_min" ];
			force_max 	 	 	 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "explode_force_max" ];
			range 		 	 	 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "explode_range" ];
			mindamage 	 	 	 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "explode_mindamage" ];
			maxdamage 	 	 	 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "explode_maxdamage" ];
			continueDamage 		 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "continueDamage" ];
			originOffset 		 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "originOffset" ];
			earthQuakeScale		 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "earthQuakeScale" ];
			earthQuakeRadius	 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "earthQuakeRadius" ];
			originOffset3d 		 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "originOffset3d" ];
			delaytime 		 = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "delaytime" ];

			if ( IsDefined( attacker ) && attacker != self )
			{
				// Achievement Hook
				self.attacker = attacker;

				// Only add .damage_type to script_vehicles that happen to be destructibles (ie UAZ)
				// This hook provides info so the vehicle can do _player_stat::register_kill()
				if ( self.code_classname == "script_vehicle" )
				{
					self.damage_type = damageType;
				}
			}

			self thread explode( partIndex, force_min, force_max, range, mindamage, maxdamage, continueDamage, originOffset, earthQuakeScale, earthQuakeRadius, attacker, originOffset3d, delaytime );
		}

		// if the part should do physics here then initiate the physics and velocity
		physTagOrigin = undefined;
		if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "physics" ] ) )
		{
			for ( i = 0; i < level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "physics" ].size; i++ )
			{
				physTagOrigin = undefined;
				physTagName = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "physics_tagName" ][ i ];
				physVelocity = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v[ "physics_velocity" ][ i ];

				initial_velocity = undefined;
				if ( IsDefined( physVelocity ) )
				{
					physTagAngles = undefined;
					if ( IsDefined( physTagName ) )
						physTagAngles = self GetTagAngles( physTagName );
					else if ( IsDefined( tagName ) )
						physTagAngles = self GetTagAngles( tagName );
					Assert( IsDefined( physTagAngles ) );

					physTagOrigin = undefined;
					if ( IsDefined( physTagName ) )
						physTagOrigin = self GetTagOrigin( physTagName );
					else if ( IsDefined( tagName ) )
						physTagOrigin = self GetTagOrigin( tagName );
					Assert( IsDefined( physTagOrigin ) );

					phys_x = physVelocity[ 0 ] - 5 + RandomFloat( 10 );
					phys_y = physVelocity[ 1 ] - 5 + RandomFloat( 10 );
					phys_z = physVelocity[ 2 ] - 5 + RandomFloat( 10 );

					forward = AnglesToForward( physTagAngles ) * phys_x * RandomFloatRange( 80, 110 );
					right = AnglesToRight( physTagAngles ) * phys_y * RandomFloatRange( 80, 110 );
					up = AnglesToUp( physTagAngles ) * phys_z * RandomFloatRange( 80, 110 );

					initial_velocity = forward + right + up;

					/#
					if ( GetDvarInt( "debug_destructibles" , 0 ) == 1 )
					{
						thread draw_line_for_time( physTagOrigin, physTagOrigin + initial_velocity, 1, 1, 1, 5.0 );
					}
					#/
				}
				else
				{
					initial_velocity = point;
					impactDir = ( 0, 0, 0 );
					if ( IsDefined( attacker ) )
					{
						impactDir = attacker.origin;
						initial_velocity = VectorNormalize( point - impactDir );
						initial_velocity *= 200;
					}
				}
				Assert( IsDefined( initial_velocity ) );

				if ( IsDefined( physTagName ) )
				{
					// Do physics on another part, and continue this thread since the current part is still unaffected by the physics

					// get the partIndex that cooresponds to what the tagname is
					physPartIndex = undefined;
					for ( j = 0; j < level.destructible_type[ self.destructibleInfo].parts.size; j++ )
					{
						if ( !isdefined( level.destructible_type[ self.destructibleInfo].parts[ j ][ 0 ].v[ "tagName" ] ) )
							continue;

						if ( level.destructible_type[ self.destructibleInfo].parts[ j ][ 0 ].v[ "tagName" ] != physTagName )
							continue;

						physPartIndex = j;
						break;
					}

					if ( IsDefined( physTagOrigin ) )
						self thread physics_launch( physPartIndex, 0, physTagOrigin, initial_velocity );
					else
						self thread physics_launch( physPartIndex, 0, point, initial_velocity );
				}
				else
				{
					// Do physics on this part, therefore ending this thread

					if ( IsDefined( physTagOrigin ) )
						self thread physics_launch( partIndex, actionStateIndex, physTagOrigin, initial_velocity );
					else
						self thread physics_launch( partIndex, actionStateIndex, point, initial_velocity );

					prof_end( "_destructible" );
					return;
				}
			}
		}

		updateHealthValue = true;
	}
	prof_end( "_destructible" );
}

destructible_splash_rotatation( v )
{
	// rotate model due to splash damage direction, optional
	model_rotation = v[ "splashRotation" ];
	model_rotate_to = v[ "rotateTo" ];

	if ( !isdefined( model_rotate_to ) )
		return;
	if ( !isdefined( model_rotation ) )
		return;
	if ( !model_rotation )
		return;
	self.angles = ( self.angles[ 0 ], model_rotate_to[ 1 ], self.angles[ 2 ] );
}

// parameter damageType can be single damage or multiple damages separated by spaces
damage_not( damageType )
{
	toks = StrTok( damageType, " " );
	damages_tok = StrTok( "splash melee bullet splash impact unknown", " " );
	new_string = "";

	foreach ( idx, tok in toks )
		damages_tok = array_remove( damages_tok, tok );

	foreach ( damages in damages_tok )
		new_string += damages + " ";

	return new_string;
}

destructible_splash_damage( damage, point, direction_vec, attacker, damageType )
{
	if ( damage <= 0 )
		return;

	if ( IsDefined( self.exploded ) )
		return;

	//------------------------------------------------------------------------
	// Fill an array of all possible parts that might have been splash damaged
	//------------------------------------------------------------------------

	if ( !isdefined( level.destructible_type[ self.destructibleInfo].parts ) )
		return;

	damagedParts = self getAllActiveParts( direction_vec );

	if ( damagedParts.size <= 0 )
		return;

	damagedParts = self setDistanceOnParts( damagedParts, point );

	closestPartDist = getLowestPartDistance( damagedParts );
	Assert( IsDefined( closestPartDist ) );

	//--------------------------------------------------------------------------
	// Damage each part depending on how close it was to the splash damage point
	//--------------------------------------------------------------------------

	prof_begin( "_destructible" );

	foreach ( part in damagedParts )
	{
		distanceMod = ( part.v[ "distance" ] * 1.4 );
		damageAmount = ( damage - ( distanceMod - closestPartDist ) );

		if ( damageAmount <= 0 )
			continue;

		if ( IsDefined( self.exploded ) )
			continue;

		/#
		if ( GetDvarInt( "debug_destructibles" , 0 ) == 1 )
		{
			if ( IsDefined( part.v[ "tagName" ] ) )
				Print3d( self GetTagOrigin( part.v[ "tagName" ] ), damageAmount, ( 1, 1, 1 ), 1.0, 0.5, 200 );
		}
		#/

		self thread destructible_update_part( damageAmount, part.v[ "modelName" ], part.v[ "tagName" ], point, direction_vec, attacker, damageType, part );
	}

	prof_end( "_destructible" );
}

getAllActiveParts( direction_vec )
{
	activeParts = [];

	Assert( IsDefined( self.destructibleInfo) );
	if ( !isdefined( level.destructible_type[ self.destructibleInfo].parts ) )
		return activeParts;

	prof_begin( "_destructible" );

	for ( i = 0; i < level.destructible_type[ self.destructibleInfo].parts.size; i++ )
	{
		partIndex = i;
		currentState = self.destructible_parts[ partIndex ].v[ "currentState" ];

		// Splash damage rotation, rotation angle only calculated for state that has this option enabled
		for ( j = 0; j < level.destructible_type[ self.destructibleInfo].parts[ partIndex ].size; j++ )
		{
			splash_rotation = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ j ].v[ "splashRotation" ];
			if ( IsDefined( splash_rotation ) && splash_rotation )
			{
				rotate_to_angle = VectorToAngles( direction_vec );
				rotate_to_angle_y = rotate_to_angle[ 1 ] - 90;
				level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ j ].v[ "rotateTo" ] = ( 0, rotate_to_angle_y, 0 );
			}
		}

		if ( !isdefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ currentState ] ) )
			continue;

		tagName = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ currentState ].v[ "tagName" ];
		if ( !isdefined( tagName ) )
			tagName = "";

		if ( tagName == "" )
			continue;

		modelName = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ currentState ].v[ "modelName" ];
		if ( !isdefined( modelName ) )
			modelName = "";

		activePartIndex = activeParts.size;
		activeParts[ activePartIndex ] = SpawnStruct();
		activeParts[ activePartIndex ].v[ "modelName" ] = modelName;
		activeParts[ activePartIndex ].v[ "tagName" ] = tagName;
	}

	prof_end( "_destructible" );

	return activeParts;
}

setDistanceOnParts( partList, point )
{
	prof_begin( "_destructible" );

	for ( i = 0; i < partList.size; i++ )
	{
		d = Distance( point, self GetTagOrigin( partList[ i ].v[ "tagName" ] ) );
		partList[ i ].v[ "distance" ] = d;
	}

	prof_end( "_destructible" );

	return partList;
}

getLowestPartDistance( partList )
{
	closestDist = undefined;

	prof_begin( "_destructible" );

	foreach ( part in partList )
	{
		Assert( IsDefined( part.v[ "distance" ] ) );
		d = part.v[ "distance" ];

		if ( !isdefined( closestDist ) )
			closestDist = d;

		if ( d < closestDist )
			closestDist = d;
	}

	prof_end( "_destructible" );

	return closestDist;
}


isValidSoundCause( soundCauseVar, action_v, soundIndex, damageType, groupNum )
{
	if ( isdefined( groupNum ) )
		soundCause = action_v[ soundCauseVar ][ groupNum ][ soundIndex ];
	else
		soundCause = action_v[ soundCauseVar ][ soundIndex ];
	
	if ( !isdefined( soundCause ) )
		return true;

	if ( soundCause == damageType )
		return true;

	return false;
}

isAttackerValid( partIndex, stateIndex, attacker )
{
	// return true if the vehicle is being force exploded
	if ( IsDefined( self.forceExploding ) )
		return true;

	// return false if the vehicle is trying to explode but it's not allowed to
	if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ].v[ "explode" ] ) )
	{
		if ( IsDefined( self.dontAllowExplode ) )
			return false;
	}

	if ( !isdefined( attacker ) )
		return true;

	if ( attacker == self )
		return true;

	sType = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ].v[ "validAttackers" ];
	if ( !isdefined( sType ) )
		return true;

	if ( sType == "no_player" )
	{
		if ( !isplayer( attacker ) )
			return true;
		if ( !isdefined( attacker.damageIsFromPlayer ) )
			return true;
		if ( attacker.damageIsFromPlayer == false )
			return true;
	}
	else
	if ( sType == "player_only" )
	{
		if ( IsPlayer( attacker ) )
			return true;
		if ( IsDefined( attacker.damageIsFromPlayer ) && attacker.damageIsFromPlayer )
			return true;
	}
	else
	if ( sType == "no_ai" && IsDefined( level.isAIfunc ) )
	{
		if ( ![[ level.isAIfunc ]]( attacker ) )
			return true;
	}
	else
	if ( sType == "ai_only" && IsDefined( level.isAIfunc ) )
	{
		if ( [[ level.isAIfunc ]]( attacker ) )
			return true;
	}
	else
	{
		AssertMsg( "Invalid attacker rules on destructible vehicle. Valid types are: ai_only, no_ai, player_only, no_player" );
	}

	return false;
}

isValidDamageCause( partIndex, stateIndex, damageType )
{
	if ( !isdefined( damageType ) )
		return true;

	godModeAllowed = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ].v[ "godModeAllowed" ];
	if ( godModeAllowed && ( ( IsDefined( self.godmode ) && self.godmode ) || ( IsDefined( self.script_bulletshield ) && self.script_bulletshield ) && damageType == "bullet" ) )
		return false;

	validType = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ].v[ "validDamageCause" ];
	if ( !isdefined( validType ) )
		return true;

	if ( ( validType == "splash" ) && damageType != "splash" )
		return false;
		
	if ( ( validType == "no_splash" ) && damageType == "splash" )
		return false;

	if ( ( validType == "no_melee" ) && damageType == "melee" || damageType == "impact" )
		return false;

	return true;
}

getDamageType( type )
{
	//returns a simple damage type: melee, bullet, splash, or unknown

	if ( !isdefined( type ) )
		return "unknown";

	type = ToLower( type );
	switch( type )
	{
		case "mod_melee":
		case "mod_crush":
		case "melee":
			return "melee";
		case "mod_pistol_bullet":
		case "mod_rifle_bullet":
		case "bullet":
			return "bullet";
		case "mod_grenade":
		case "mod_grenade_splash":
		case "mod_projectile":
		case "mod_projectile_splash":
		case "mod_explosive":
		case "splash":
			return "splash";
		case "mod_impact":
			return "impact";
		case "unknown":
			return "unknown";
		default:
			return "unknown";
	}
}

damage_mirror( parent, modelName, tagName )
{
	self notify( "stop_damage_mirror" );
	self endon( "stop_damage_mirror" );
	parent endon( "stop_taking_damage" );

	self SetCanDamage( true );
	for ( ;; )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, type );
		parent notify( "damage", damage, attacker, direction_vec, point, type, modelName, tagName );
		damage = undefined;
		attacker = undefined;
		direction_vec = undefined;
		point = undefined;
		type = undefined;
	}
}

add_damage_owner_recorder()
{
	// Mackey added to track who is damaging the car
	self.player_damage = 0;
	self.non_player_damage = 0;

	self.car_damage_owner_recorder = true;
}

loopfx_onTag( loopfx, loopfx_tag, loopRate, partIndex )
{
	self endon( "FX_State_Change" + partIndex );
	self endon( "delete_destructible" );
	level endon( "putout_fires" );
	
	while( isdefined( self ) )
	{
		eModel = get_dummy();
		PlayFXOnTag( loopfx, eModel, loopfx_tag );
		wait loopRate;
	}
}

health_drain( amount, interval, partIndex, modelName, tagName, badplaceRadius, badplaceTeam )
{
	self endon( "Health_Drain_State_Change" + partIndex );
	level endon( "putout_fires" );
	self endon( "destroyed" );
	
	if( IsDefined( badplaceRadius ) && IsDefined( level.destructible_badplace_radius_multiplier ) )
	{
		badplaceRadius *= level.destructible_badplace_radius_multiplier;
	}
	
	if( IsDefined( amount ) &&IsDefined( level.destructible_health_drain_amount_multiplier ) )
	{
		amount *= level.destructible_health_drain_amount_multiplier;
	}
	
	wait interval;

	self.healthDrain = true;

	uniqueName = undefined;

	// disable the badplace radius call if level.disable_destructible_bad_places is true
	if ( IsDefined( level.disable_destructible_bad_places ) && level.disable_destructible_bad_places )
		badplaceRadius = undefined;

	if ( IsDefined( badplaceRadius ) && IsDefined( badplaceTeam ) && isSP() )
	{
		uniqueName = "" + GetTime();
		if ( !isdefined( self.disableBadPlace ) )
		{
			if ( IsDefined( self.script_radius ) )
			{
				// overwrite the badplace radius from the map
				badplaceRadius = self.script_radius;
			}
			Assert( IsDefined( level.badplace_cylinder_func ) );
			if ( badplaceTeam == "both" )
				call [[ level.badplace_cylinder_func ]]( uniqueName, 0, self.origin, badplaceRadius, 128, "allies", "bad_guys" );
			else
				call [[ level.badplace_cylinder_func ]]( uniqueName, 0, self.origin, badplaceRadius, 128, badplaceTeam );
			self thread badplace_remove( uniqueName );
		}
	}
	
	while ( isdefined( self ) && self.destructible_parts[ partIndex ].v[ "health" ] > 0 )
	{
		/#
		if ( GetDvarInt( "debug_destructibles" , 0 ) == 1 )
		{
			IPrintLn( "health before damage: " + self.destructible_parts[ partIndex ].v[ "health" ] );
			IPrintLn( "doing " + amount + " damage" );
		}
		#/
		self notify( "damage", amount, self, ( 0, 0, 0 ), ( 0, 0, 0 ), "MOD_UNKNOWN", modelName, tagName );
		wait interval;
	}
	
	self notify( "remove_badplace" );
}

badplace_remove( uniqueName )
{	
	self waittill_any( "destroyed", "remove_badplace" );
	
	Assert( IsDefined( uniqueName ) );
	Assert( IsDefined( level.badplace_delete_func ) );
	call [[ level.badplace_delete_func ]]( uniqueName );
}

physics_launch( partIndex, stateIndex, point, initial_velocity )
{
	modelName = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ].v[ "modelName" ];
	tagName = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ stateIndex ].v[ "tagName" ];

	self hideapart( tagName );

	/#
	if ( GetDvarInt( "destructibles_enable_physics", 1 ) == 0 )
		return;
	#/

	// If we've reached the max number of spawned physics models for destructible vehicles then delete one before creating another
	if ( level.destructibleSpawnedEnts.size >= level.destructibleSpawnedEntsLimit )
		physics_object_remove( level.destructibleSpawnedEnts[ 0 ] );

	// Spawn a model to use for physics using the modelname and position of the part
	physicsObject = Spawn( "script_model", self GetTagOrigin( tagName ) );
	physicsObject.angles = self GetTagAngles( tagName );
	physicsObject SetModel( modelName );

	// Keep track of the new part so it can be removed later if we reach the max
	level.destructibleSpawnedEnts[ level.destructibleSpawnedEnts.size ] = physicsObject;

	// Do physics on the model
	physicsObject PhysicsLaunchClient( point, initial_velocity );
}

physics_object_remove( ent )
{
	newArray = [];
	for ( i = 0; i < level.destructibleSpawnedEnts.size; i++ )
	{
		if ( level.destructibleSpawnedEnts[ i ] == ent )
			continue;
		newArray[ newArray.size ] = level.destructibleSpawnedEnts[ i ];
	}
	level.destructibleSpawnedEnts = newArray;
	
	if ( isdefined( ent ) )
		ent Delete();
}

explode( partIndex, force_min, force_max, range, mindamage, maxdamage, continueDamage, originOffset, earthQuakeScale, earthQuakeRadius, attacker, originOffset3d, delaytime )
{
	Assert( IsDefined( force_min ) );
	Assert( IsDefined( force_max ) );
	
	if( IsDefined( range ) && IsDefined( level.destructible_explosion_radius_multiplier ) )
	{
		range *= level.destructible_explosion_radius_multiplier;
	}

	if ( !isdefined( originOffset ) )
		originOffset = 80;
	if ( !isdefined( originOffset3d) )
		originOffset3d = (0,0,0);

	if ( !isdefined( continueDamage ) || ( IsDefined( continueDamage ) && !continueDamage ) )
	{
		if ( IsDefined( self.exploded ) )
			return;
		self.exploded = true;
	}
	
	if (!isdefined( delaytime) )
		delaytime = 0;

	self notify( "exploded", attacker );
	level notify( "destructible_exploded" );
	if ( self.code_classname == "script_vehicle" )
		self notify( "death", attacker, self.damage_type );

	// check if there is a disconnect paths brush to disconnect any traverses
	if ( isSP() )
		self thread disconnectTraverses();


	if( ! level.fast_destructible_explode )
		wait 0.05;
	
	// entity could be deleted during previous wait
	if ( !IsDefined( self ) )
		return;

	currentState = self.destructible_parts[ partIndex ].v[ "currentState" ];
	Assert( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ] ) );
	tagName = undefined;
	if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ currentState ] ) )
		tagName = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ currentState ].v[ "tagName" ];

	if ( IsDefined( tagName ) )
		explosionOrigin = self GetTagOrigin( tagName );
	else
		explosionOrigin = self.origin;

	self notify( "damage", maxdamage, self, ( 0, 0, 0 ), explosionOrigin, "MOD_EXPLOSIVE", "", "" );

	self notify( "stop_car_alarm" );

	waittillframeend;

	prof_begin( "_destructible" );

	if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts ) )
	{
		for ( i = ( level.destructible_type[ self.destructibleInfo].parts.size - 1 ); i >= 0; i-- )
		{
			if ( i == partIndex )
				continue;

			stateIndex = self.destructible_parts[ i ].v[ "currentState" ];
			if ( stateIndex >= level.destructible_type[ self.destructibleInfo].parts[ i ].size )
				stateIndex = level.destructible_type[ self.destructibleInfo].parts[ i ].size - 1;
			modelName = level.destructible_type[ self.destructibleInfo].parts[ i ][ stateIndex ].v[ "modelName" ];
			tagName = level.destructible_type[ self.destructibleInfo].parts[ i ][ stateIndex ].v[ "tagName" ];

			if ( !isdefined( modelName ) )
				continue;
			if ( !isdefined( tagName ) )
				continue;

			// dont do physics on parts that are supposed to be removed on explosion
			if ( IsDefined( level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "physicsOnExplosion" ] ) )
			{
				if ( level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "physicsOnExplosion" ] > 0 )
				{
					velocityScaler = level.destructible_type[ self.destructibleInfo].parts[ i ][ 0 ].v[ "physicsOnExplosion" ];

					point = self GetTagOrigin( tagName );
					initial_velocity = VectorNormalize( point - explosionOrigin );
					initial_velocity *= RandomFloatRange( force_min, force_max ) * velocityScaler;

					self thread physics_launch( i, stateIndex, point, initial_velocity );
					continue;
				}
			}
			//self.destructible_parts[ i ] Hide();
		}
	}

	prof_end( "_destructible" );
	
	stopTakingDamage = ( !isdefined( continueDamage ) || ( IsDefined( continueDamage ) && !continueDamage ) );
	if ( stopTakingDamage )
		self notify( "stop_taking_damage" );
	
	if( ! level.fast_destructible_explode )
		wait 0.05;
		
	// entity could be deleted during previous wait
	if ( !IsDefined( self ) )
		return;

	damageLocation = explosionOrigin + ( 0, 0, originOffset ) + originOffset3d;

	isVehicle = ( GetSubStr( level.destructible_type[ self.destructibleInfo].v[ "type" ], 0, 7 ) == "vehicle" );

	if ( isVehicle )
	{
		anim.lastCarExplosionTime = GetTime();
		anim.lastCarExplosionDamageLocation = damageLocation;
		anim.lastCarExplosionLocation = explosionOrigin;
		anim.lastCarExplosionRange = range;
	}

	// turn off friendly fire when they blow up so the player doesn't get accidental friendly fire mission failure
	level thread set_disable_friendlyfire_value_delayed( 1 );
	
	
	if ( delaytime > 0 )
		wait (delaytime);

	//using this in hamburg where player has no control and needs to be protected from cars blowing up nearby. It's not the players fault!!
	if( isdefined( level.destructible_protection_func ) )
		thread [[level.destructible_protection_func]]();		
		
	if ( isSP() )
	{
		if ( level.gameskill == 0 && !self player_touching_post_clip() )
			self RadiusDamage( damageLocation, range, maxdamage, mindamage, self, "MOD_RIFLE_BULLET" );
		else
			self RadiusDamage( damageLocation, range, maxdamage, mindamage, self );

		if ( IsDefined( self.damageOwner ) && isVehicle )
		{
			self.damageOwner notify( "destroyed_car" );
			level notify( "player_destroyed_car", self.damageOwner, damageLocation );
		}
	}
	else
	{
		weapon = "destructible_toy";
		if ( isVehicle )
			weapon = "destructible_car";

		if ( !isdefined( self.damageOwner ) )
		{
			self RadiusDamage( damageLocation, range, maxdamage, mindamage, self, "MOD_EXPLOSIVE", weapon );
		}
		else
		{
			self RadiusDamage( damageLocation, range, maxdamage, mindamage, self.damageOwner, "MOD_EXPLOSIVE", weapon );
			if ( isVehicle )
			{
				self.damageOwner notify( "destroyed_car" );
				level notify( "player_destroyed_car", self.damageOwner, damageLocation );
			}
		}
	}

	if ( IsDefined( earthQuakeScale ) && IsDefined( earthQuakeRadius ) )
		Earthquake( earthQuakeScale, 2.0, damageLocation, earthQuakeRadius );

	/#
	if ( GetDvarInt( "destructibles_show_radiusdamage" ) == 1 )
		thread debug_radiusdamage_circle( damageLocation, range, maxdamage, mindamage );
	#/

	// explosion damage done, resume friendly fire if it was enabled
	level thread set_disable_friendlyfire_value_delayed( 0, 0.05 );

	magnitudeScaler = 0.01;
	magnitude = range * magnitudeScaler;
	Assert( magnitude > 0 );
	range *= .99;
	PhysicsExplosionSphere( damageLocation, range, 0, magnitude );
	
	if ( stopTakingDamage )
	{
		self SetCanDamage( false );
		self thread cleanupVars();
	}
	
	self notify( "destroyed" );
}

cleanupVars()
{
	// wait so we can make sure they are no longer needed
	wait 0.05;
		
	while ( isdefined( self ) && isdefined( self.waiting_for_queue ) )
	{
		self waittill( "queue_processed" );
		wait 0.05;
	}
		
	if ( !isdefined( self ) )
		return;
	
	self.animsapplied = undefined;
	self.attacker = undefined;
	self.car_damage_owner_recorder = undefined;
	self.caralarm = undefined;
	self.damageowner = undefined;
	self.destructible_parts = undefined;
	self.destructible_type = undefined;
	self.destructibleInfo = undefined;
	self.healthdrain = undefined;
	self.non_player_damage = undefined;
	self.player_damage = undefined;
	
	if ( !IsDefined( level.destructible_cleans_up_more ) )
		return;
		
	self.script_noflip = undefined;
	self.exploding = undefined;
	self.loopingsoundstopnotifies = undefined;
	self.car_alarm_org = undefined;
}

set_disable_friendlyfire_value_delayed( value, delay )
{
	level notify( "set_disable_friendlyfire_value_delayed" );
	level endon( "set_disable_friendlyfire_value_delayed" );

	Assert( IsDefined( value ) );

	if ( IsDefined( delay ) )
		wait delay;

	level.friendlyFireDisabledForDestructible = value;
}

/*
arcadeMode_car_kill()
{
	if ( !isSP() )
		return false;
	
	if ( !arcadeMode() )
		return false;

	if ( level.script == "ac130" )
		return false;
		
	if ( IsDefined( level.allCarsDamagedByPlayer ) )
		return true;
		
	return self maps\_gameskill::player_did_most_damage();
}
*/
connectTraverses()
{
	clip = get_traverse_disconnect_brush();

	if ( !isdefined( clip ) )
		return;

	Assert( IsDefined( level.connectPathsFunction ) );
	clip call [[ level.connectPathsFunction ]]();
	clip.origin -= ( 0, 0, 10000 );
}

disconnectTraverses()
{
	clip = get_traverse_disconnect_brush();

	if ( !isdefined( clip ) )
		return;

	clip.origin += ( 0, 0, 10000 );
	Assert( IsDefined( level.disconnectPathsFunction ) );
	clip call [[ level.disconnectPathsFunction ]]();
	clip.origin -= ( 0, 0, 10000 );
}

get_traverse_disconnect_brush()
{
	if ( !isdefined( self.target ) )
		return undefined;

	targets = GetEntArray( self.target, "targetname" );
	foreach ( target in targets )
	{
		if ( IsSpawner( target ) )
			continue;
		if ( IsDefined( target.script_destruct_collision ) )
			continue;
		if ( target.code_classname == "light" )
			continue;
		if ( !target.spawnflags & 1 )
			continue;
		return target;
	}
}

hideapart( tagName )
{
	self HidePart( tagName );
}

showapart( tagName )
{
	self ShowPart( tagName );
}

disable_explosion()
{
	self.dontAllowExplode = true;
}

force_explosion()
{
	self.dontAllowExplode = undefined;
	self.forceExploding = true;
	self notify( "damage", 100000, self, self.origin, self.origin, "MOD_EXPLOSIVE", "", "" );
}

get_dummy()
{
	if ( !isSP() )
		return self;

	if ( self.modeldummyon )
		eModel = self.modeldummy;
	else
		eModel = self;
	return eModel;
}

play_loop_sound_on_destructible( alias, tag )
{
	eModel = get_dummy();

	org = Spawn( "script_origin", ( 0, 0, 0 ) );
	if ( IsDefined( tag ) )
		org.origin = eModel GetTagOrigin( tag );
	else
		org.origin = eModel.origin;

	org PlayLoopSound( alias );

	eModel thread force_stop_sound( alias );

	eModel waittill( "stop sound" + alias );
	if ( !isdefined( org ) )
		return;

	org StopLoopSound( alias );
	org Delete();
}

force_stop_sound( alias )
{
	self endon( "stop sound" + alias );

	level waittill( "putout_fires" );
	self notify( "stop sound" + alias );
}

notifyDamageAfterFrame( damage, attacker, direction_vec, point, damageType, modelName, tagName )
{
	if ( IsDefined( level.notifyDamageAfterFrame ) )
		return;

	level.notifyDamageAfterFrame = true;
	waittillframeend;
	if ( IsDefined( self.exploded ) )
	{
		level.notifyDamageAfterFrame = undefined;
		return;
	}

	if ( isSP() )
		damage /= SP_DAMAGE_BIAS;
	else
		damage /= MP_DAMAGE_BIAS;

	self notify( "damage", damage, attacker, direction_vec, point, damageType, modelName, tagName );
	level.notifyDamageAfterFrame = undefined;
}

play_sound( alias, tag )
{
	if ( IsDefined( tag ) )
	{
		org = Spawn( "script_origin", self GetTagOrigin( tag ) );
		org Hide();
		org LinkTo( self, tag, ( 0, 0, 0 ), ( 0, 0, 0 ) );
	}
	else
	{
		org = Spawn( "script_origin", ( 0, 0, 0 ) );
		org Hide();
		org.origin = self.origin;
		org.angles = self.angles;
		org LinkTo( self );
	}

	org PlaySound( alias );
	wait( 5.0 );
	if ( IsDefined( org ) )
		org Delete();
}

toString( num )
{
	return( "" + num );
}

do_car_alarm()
{
	if ( IsDefined( self.carAlarm ) )
		return;
	self.carAlarm = true;

	if ( !should_do_car_alarm() )
		return;

	self.car_alarm_org = Spawn( "script_model", self.origin );
	self.car_alarm_org Hide();
	self.car_alarm_org PlayLoopSound( CAR_ALARM_ALIAS );

	level.currentCarAlarms++;
	Assert( level.currentCarAlarms <= MAX_SIMULTANEOUS_CAR_ALARMS );

	self thread car_alarm_timeout();

	self waittill( "stop_car_alarm" );

	level.lastCarAlarmTime = GetTime();
	level.currentCarAlarms--;

	self.car_alarm_org StopLoopSound( CAR_ALARM_ALIAS );
	self.car_alarm_org Delete();
}

car_alarm_timeout()
{
	self endon( "stop_car_alarm" );

	// Car alarm only lasts this long until it automatically shuts up
	wait CAR_ALARM_TIMEOUT;

	if ( !isdefined( self ) )
		return;

	self thread play_sound( CAR_ALARM_OFF_ALIAS );
	self notify( "stop_car_alarm" );
}

should_do_car_alarm()
{
	// If there is already car alarms going off then don't trigger another one
	if ( level.currentCarAlarms >= MAX_SIMULTANEOUS_CAR_ALARMS )
		return false;

	// If the player hasn't heard a car alarm yet during this level
	timeElapsed = undefined;
	if ( !isdefined( level.lastCarAlarmTime ) )
	{
		if ( cointoss() )
			return true;
		timeElapsed = GetTime() - level.commonStartTime;
	}
	else
	{
		timeElapsed = GetTime() - level.lastCarAlarmTime;
	}
	Assert( IsDefined( timeElapsed ) );

	// If the player hasn't heard a car alarm in a while then do one
	if ( level.currentCarAlarms == 0 && timeElapsed >= NO_CAR_ALARM_MAX_ELAPSED_TIME )
		return true;

	if ( RandomInt( 100 ) <= 33 )
		return true;

	return false;
}

do_random_dynamic_attachment( tagName, attach_model_1, attach_model_2, clipToRemove )
{
	Assert( IsDefined( tagName ) );
	Assert( IsDefined( attach_model_1 ) );
	
	spawnedModels = [];
	
	if ( isSP() )
	{
		self Attach( attach_model_1, tagName, false );
		if ( IsDefined( attach_model_2 ) && attach_model_2 != "" )
			self Attach( attach_model_2, tagName, false );
	}
	else
	{
		//attach doesn't work in MP so fake it
		spawnedModels[ 0 ] = Spawn( "script_model", self GetTagOrigin( tagName ) );
		spawnedModels[ 0 ].angles = self GetTagAngles( tagName );
		spawnedModels[ 0 ] SetModel( attach_model_1 );
		spawnedModels[ 0 ] LinkTo( self, tagName );

		if ( IsDefined( attach_model_2 ) && attach_model_2 != "" )
		{
			spawnedModels[ 1 ] = Spawn( "script_model", self GetTagOrigin( tagName ) );
			spawnedModels[ 1 ].angles = self GetTagAngles( tagName );
			spawnedModels[ 1 ] SetModel( attach_model_2 );
			spawnedModels[ 1 ] LinkTo( self, tagName );
		}
	}
	
	// remove collision that might not be used for this attachment
	if ( isdefined( clipToRemove ) )
	{
		tagOrg = self getTagOrigin( tagName );
		clip = get_closest_with_targetname( tagOrg, clipToRemove );
		if ( isdefined( clip ) )
			clip delete();
	}
	
	self waittill( "exploded" );

	if ( isSP() )
	{
		self Detach( attach_model_1, tagName );
		self Attach( attach_model_1 + DESTROYED_ATTACHMENT_SUFFIX, tagName, false );

		if ( IsDefined( attach_model_2 ) && attach_model_2 != "" )
		{
			self Detach( attach_model_2, tagName );
			self Attach( attach_model_2 + DESTROYED_ATTACHMENT_SUFFIX, tagName, false );
		}
	}
	else
	{
		spawnedModels[ 0 ] SetModel( attach_model_1 + DESTROYED_ATTACHMENT_SUFFIX );
		if ( IsDefined( attach_model_2 ) && attach_model_2 != "" )
			spawnedModels[ 1 ] SetModel( attach_model_2 + DESTROYED_ATTACHMENT_SUFFIX );
	}
}

get_closest_with_targetname( origin, targetname )
{
	closestDist = undefined;
	closestEnt = undefined;
	ents = getentarray( targetname, "targetname" );
	foreach ( ent in ents )
	{
		d = distanceSquared( origin, ent.origin );
		
		if ( !isdefined( closestDist ) || ( d < closestDist ) )
		{
			closestDist = d;
			closestEnt = ent;
		}
	}
	
	return closestEnt;
}

player_touching_post_clip()
{
	post_clip = undefined;

	if ( !IsDefined( self.target ) )
	{
		return false;
	}

	targets = GetEntArray( self.target, "targetname" );
	foreach ( target in targets )
	{
		if ( IsDefined( target.script_destruct_collision ) && target.script_destruct_collision == "post" )
		{
			post_clip = target;
			break;
		}
	}

	if ( !IsDefined( post_clip ) )
	{
		return false;
	}

	player = get_player_touching( post_clip );

	if ( IsDefined( player ) )
	{
		return true;
	}

	return false;
}

get_player_touching( ent )
{
	foreach ( player in level.players )
	{
		if ( !IsAlive( player ) )
		{
			continue;
		}

		if ( ent IsTouching( player ) )
		{
			return player;
		}
	}

	return undefined;
}

is_so()
{
	return GetDvar( "specialops" ) == "1";
}

destructible_handles_collision_brushes()
{
	targets = GetEntArray( self.target, "targetname" );
	collision_funcs = [];
	collision_funcs[ "pre" ] = ::collision_brush_pre_explosion;
	collision_funcs[ "post" ] = ::collision_brush_post_explosion;

	foreach ( target in targets )
	{
		if ( !isdefined( target.script_destruct_collision ) )
			continue;
		self thread [[ collision_funcs[ target.script_destruct_collision ] ]]( target );
	}
}
DYNAMICPATH = 1;

collision_brush_pre_explosion( clip )
{
	waittillframeend;// wait for same area post brushes to connect before we disconnect

	if ( isSP() && clip.spawnflags & DYNAMICPATH )
		clip call [[ level.disconnectPathsFunction ]]();

	self waittill( "exploded" );

	if ( isSP() && clip.spawnflags & DYNAMICPATH )
		clip call [[ level.connectPathsFunction ]]();

	clip Delete();
	
}

collision_brush_post_explosion( clip )
{
	clip NotSolid();

	if ( isSP() && clip.spawnflags & DYNAMICPATH )
		clip call [[ level.connectPathsFunction ]]();

	self waittill( "exploded" );
	waittillframeend;// wait for same area pre brushes to connect before we disconnect

	if ( isSP() )
	{
		if( clip.spawnflags & DYNAMICPATH )
			clip call [[ level.disconnectPathsFunction ]]();

		if ( is_so() )
		{
			player = get_player_touching( clip );
			if ( isdefined( player ) )
			{
				assertex( isdefined( level.func_destructible_crush_player ), "Special Ops requires level.func_destructible_crush_player to be defined." );
				self thread [[ level.func_destructible_crush_player ]]( player );
			}
		}
		else
		{
/#
			thread debug_player_in_post_clip( clip );
#/
		}
	}

	clip Solid();
}

debug_player_in_post_clip( clip )
{
/#
	wait( 0.1 );
	player = get_player_touching( clip );
	if ( IsDefined( player ) )
	{
		AssertEx( !IsAlive( player ), "Player is in a clip of a destructible, but is still alive. He's either in godmode or we're doing something wrong. Player will be stuck now." );
	}
#/
}


destructible_get_my_breakable_light( range )
{
	AssertEx( !isdefined( self.breakable_light ), "Tried to define my breakable light twice" );

	//	light = getClosest( self.origin, GetEntArray("light_destructible","targetname") );
	// beh getClosest is SP only.. to lazy to port right now.
	// find the nearest light with targetname light_destructible within range and turn it out. scripting stuff in prefabs is still hard.
	// 
	lights = GetEntArray( "light_destructible", "targetname" );
	if ( isSP() )// mp lacks noteworthy powers
	{
		lights2 = GetEntArray( "light_destructible", "script_noteworthy" );
		lights = array_combine( lights, lights2 );
	}
	if ( !lights.size )
		return;

	shortest_distance = range * range;
	the_light = undefined;
	foreach ( light in lights )
	{
		dist  = DistanceSquared( self.origin, light.origin );
		if ( dist < shortest_distance )
		{
			the_light = light;
			shortest_distance = dist;
		}
	}

	if ( !isdefined( the_light ) )
		return;

	self.breakable_light = the_light;
}

break_nearest_light( range )
{
	if ( !isdefined( self.breakable_light ) )
		return;

	self.breakable_light SetLightIntensity( 0 );
}


debug_radiusdamage_circle( center, radius, maxdamage, mindamage )
{
	circle_sides = 16;

	angleFrac = 360 / circle_sides;

	// Z circle
	circlepoints = [];
	for ( i = 0; i < circle_sides; i++ )
	{
		angle = ( angleFrac * i );
		xAdd = Cos( angle ) * radius;
		yAdd = Sin( angle ) * radius;
		x = center[ 0 ] + xAdd;
		y = center[ 1 ] + yAdd;
		z = center[ 2 ];
		circlepoints[ circlepoints.size ] = ( x, y, z );
	}
	thread debug_circle_drawlines( circlepoints, 5.0, ( 1, 0, 0 ), center );

	// X circle
	circlepoints = [];
	for ( i = 0; i < circle_sides; i++ )
	{
		angle = ( angleFrac * i );
		xAdd = Cos( angle ) * radius;
		yAdd = Sin( angle ) * radius;
		x = center[ 0 ];
		y = center[ 1 ] + xAdd;
		z = center[ 2 ] + yAdd;
		circlepoints[ circlepoints.size ] = ( x, y, z );
	}
	thread debug_circle_drawlines( circlepoints, 5.0, ( 1, 0, 0 ), center );

	// Y circle
	circlepoints = [];
	for ( i = 0; i < circle_sides; i++ )
	{
		angle = ( angleFrac * i );
		xAdd = Cos( angle ) * radius;
		yAdd = Sin( angle ) * radius;
		x = center[ 0 ] + yAdd;
		y = center[ 1 ];
		z = center[ 2 ] + xAdd;
		circlepoints[ circlepoints.size ] = ( x, y, z );
	}
	thread debug_circle_drawlines( circlepoints, 5.0, ( 1, 0, 0 ), center );

	// draw center and range with values
	Print3d( center, maxdamage, ( 1, 1, 1 ), 1, 1, 100 );
	Print3d( center + ( radius, 0, 0 ), mindamage, ( 1, 1, 1 ), 1, 1, 100 );
}

debug_circle_drawlines( circlepoints, duration, color, center )
{
	Assert( IsDefined( center ) );
	for ( i = 0; i < circlepoints.size; i++ )
	{
		start = circlepoints[ i ];
		if ( i + 1 >= circlepoints.size )
			end = circlepoints[ 0 ];
		else
			end = circlepoints[ i + 1 ];

		thread debug_line( start, end, duration, color );
		thread debug_line( center, start, duration, color );
	}
}

debug_line( start, end, duration, color )
{
	if ( !isdefined( color ) )
		color = ( 1, 1, 1 );

	for ( i = 0; i < ( duration * 20 ); i++ )
	{
		Line( start, end, color );
		wait 0.05;
	}
}

spotlight_tag_origin_cleanup( tag_origin )
{
	tag_origin endon( "death" );
	level waittill( "new_destructible_spotlight" );
	tag_origin Delete();
}

spotlight_fizzles_out( action_v, eModel, damageType, partIndex, tag_origin )
{
	level endon( "new_destructible_spotlight" );
	thread spotlight_tag_origin_cleanup( tag_origin );

	maxVal = action_v[ "spotlight_brightness" ];
	noself_func( "setsaveddvar", "r_spotlightbrightness", maxVal );

	wait( RandomFloatRange( 2, 5 ) );

	steps = RandomIntRange( 5, 11 );
	for ( i = 0; i < steps; i++ )
	{
		noself_func( "setsaveddvar", "r_spotlightbrightness", maxVal * 0.65 );
		wait( 0.05 );
		noself_func( "setsaveddvar", "r_spotlightbrightness", maxVal );
		wait( 0.05 );
	}

	destructible_fx_think( action_v, eModel, damageType, partIndex );
	level.destructible_spotlight Delete();
	tag_origin Delete();
}

destructible_spotlight_think( action_v, eModel, damageType, partIndex )
{
	// spotlights are MP only
	if ( !isSP() )
		return;

	if ( !isdefined( self.breakable_light ) )
		return;

	emodel self_func( "startignoringspotLight" );

	// set all the dvars for this light type
	foreach ( dvar, val in action_v[ "dvars" ] )
	{
		noself_func( "setsaveddvar", dvar, val );
	}

	if ( !isdefined( level.destructible_spotlight ) )
	{
		level.destructible_spotlight = spawn_tag_origin();
		fx = getfx( action_v[ "spotlight_fx" ] );
		PlayFXOnTag( fx, level.destructible_spotlight, "tag_origin" );
	}

	//self.breakable_light thread maps\_debug::drawForwardForever( 200, (1,0,0) );	
	//level.destructible_spotlight thread maps\_debug::drawForwardForever( 200, (1,1,0) );	

	level notify( "new_destructible_spotlight" );


	level.destructible_spotlight Unlink();


	tag_origin = spawn_tag_origin();
	tag_origin LinkTo( self, action_v[ "spotlight_tag" ], ( 0, 0, 0 ), ( 0, 0, 0 ) );

	//eModel thread maps\_debug::drawTagForever( action_v[ "spotlight_tag" ] );

	level.destructible_spotlight.origin = self.breakable_light.origin;
	level.destructible_spotlight.angles = self.breakable_light.angles;
	level.destructible_spotlight thread spotlight_fizzles_out( action_v, eModel, damageType, partIndex, tag_origin );

	wait( 0.05 );// Wait for the spawned tag_origin to get to the right place before linking
	if ( IsDefined( tag_origin ) )
	{
		// can be deleted during wait
		level.destructible_spotlight LinkTo( tag_origin );
	}

}

is_valid_damagetype( damageType, v, idx, groupNum )
{
	valid_damagetype = undefined;
	if ( IsDefined( v[ "fx_valid_damagetype" ] ) )
		valid_damagetype = v[ "fx_valid_damagetype" ][ groupNum ][ idx ];

	if ( !isdefined( valid_damagetype ) )
		return true;

	return IsSubStr( valid_damagetype, damageType );
}

destructible_sound_think( action_v, eModel, damageType, groupNum )
{
	if ( isdefined( self.exploded ) )
		return undefined;
	
	if ( !isDefined( action_v[ "sound" ] ) )
		return undefined;
	
	if ( !isdefined( groupNum ) )
		groupNum = 0;
	
	assert( isDefined( action_v[ "sound" ][ groupNum ] ) );
	
	for ( i = 0; i < action_v[ "sound" ][ groupNum ].size; i++ )
	{
		validSoundCause = self isValidSoundCause( "soundCause", action_v, i, damageType, groupNum );
		if ( !validSoundCause )
			continue;
		
		soundAlias = action_v[ "sound" ][ groupNum ][ i ];
		soundTagName = action_v[ "tagName" ];	//chad - dont think I need a groupnum index here, but now we probably can't support playing sounds on multiple tags within one group
		eModel thread play_sound( soundAlias, soundTagName );
	}
	
	return groupNum;
}

destructible_fx_think( action_v, eModel, damageType, partIndex, groupNum )
{
	if ( !isdefined( action_v[ "fx" ] ) )
		return undefined;

	if ( !isdefined( groupNum ) )
		groupNum = randomInt( action_v[ "fx_filename" ].size );
	
	if ( !isDefined( action_v[ "fx" ][ groupNum ] ) )
	{
		println( "^1destructible tried to use custom groupNum for FX but that group didn't exist" );
		groupNum = randomInt( action_v[ "fx_filename" ].size );
	}
	
	assert( isDefined( action_v[ "fx" ][ groupNum ] ) );

	fx_size = action_v[ "fx_filename" ][ groupNum ].size;

	for ( idx = 0; idx < fx_size; idx++ )
	{
		if ( !is_valid_damagetype( damageType, action_v, idx, groupNum ) )
			continue;

		fx = action_v[ "fx" ][ groupNum ][ idx ];

		if ( IsDefined( action_v[ "fx_tag" ][ groupNum ][ idx ] ) )
		{
			fx_tag = action_v[ "fx_tag" ][ groupNum ][ idx ];
			self notify( "FX_State_Change" + partIndex );

			if ( action_v[ "fx_useTagAngles" ][ groupNum ][ idx ] )
			{
				PlayFXOnTag( fx, eModel, fx_tag );
			}
			else
			{
				fxOrigin = eModel GetTagOrigin( fx_tag );
				forward = ( fxOrigin + ( 0, 0, 100 ) ) - fxOrigin;
				PlayFX( fx, fxOrigin, forward );
			}
		}
		else
		{
			fxOrigin = eModel.origin;
			forward = ( fxOrigin + ( 0, 0, 100 ) ) - fxOrigin;
			PlayFX( fx, fxOrigin, forward );
		}
	}

	return groupNum;
}

destructible_animation_think( action_v, eModel, damageType, partIndex )
{
	if ( IsDefined( self.exploded ) )
		return undefined;

	if ( !isdefined( action_v[ "animation" ] ) )
		return undefined;

	if ( IsDefined( self.no_destructible_animation ) )
		return undefined;

	if ( IsDefined( action_v[ "randomly_flip" ] ) && !isdefined( self.script_noflip ) )
	{
		if ( cointoss() )
		{
			// flip it around for randomness
			self.angles += ( 0, 180, 0 );
		}
	}

	// this stuff is SP only
	if ( IsDefined( action_v[ "spotlight_tag" ] ) )
	{
		thread destructible_spotlight_think( action_v, eModel, damageType, partIndex );
		wait( 0.05 );
	}

	array = random( action_v[ "animation" ] );

	animName = array[ "anim" ];
	animTree = array[ "animTree" ];
	groupNum = array[ "groupNum" ];
	mpAnim 	 = array[ "mpAnim" ];

	maxStartDelay = array[ "maxStartDelay" ];
	animRateMin = array[ "animRateMin" ];
	animRateMax = array[ "animRateMax" ];

	if ( !isdefined( animRateMin ) )
		animRateMin = 1.0;
	if ( !isdefined( animRateMax ) )
		animRateMax = 1.0;
	if ( animRateMin == animRateMax )
		animRate = animRateMin;
	else
		animRate = RandomFloatRange( animRateMin, animRateMax );

	vehicle_dodge_part_animation = array[ "vehicle_exclude_anim" ];

	if ( self.code_classname == "script_vehicle" && vehicle_dodge_part_animation )
		return undefined;

	eModel self_func( "useanimtree", animTree );

	animType = array[ "animType" ];

	if ( !isdefined( self.animsApplied ) )
		self.animsApplied = [];
	self.animsApplied[ self.animsApplied.size ] = animName;

	if ( IsDefined( self.exploding ) )
		self clear_anims( eModel );

	if ( IsDefined( maxStartDelay ) && maxStartDelay > 0 )
		wait RandomFloat( maxStartDelay );

	// Multiplayer animations work now
	if ( !isSP() )
	{
		if ( IsDefined( mpAnim ) )
			self self_func( "scriptModelPlayAnim", mpAnim );
		return groupNum;
	}

	if ( animType == "setanim" )
	{
		eModel self_func( "setanim", animName, 1.0, 1.0, animRate );
		return groupNum;
	}

	if ( animType == "setanimknob" )
	{
		eModel self_func( "setanimknob", animName, 1.0, 0, animRate );
		return groupNum;
	}

	AssertMsg( "Tried to play an animation on a destructible with an invalid animType: " + animType );
	return undefined;
}

clear_anims( eModel )
{
	//clear all previously blended anims if the vehicle is exploding so the explosion doesn't have to blend with anything
	if ( IsDefined( self.animsApplied ) )
	{
		foreach ( animation in self.animsApplied )
		{
			if ( isSP() )
				eModel self_func( "clearanim", animation, 0 );
			else
				eModel self_func( "scriptModelClearAnim" );
		}
	}
}

init_destroyed_count()
{
	level.destroyedCount = 0;
	level.destroyedCountTimeout = 0.5;

	if ( isSP() )
		level.maxDestructions = 20;
	else
		level.maxDestructions = 2;

}

add_to_destroyed_count()
{
	level.destroyedCount++;

	wait( level.destroyedCountTimeout );

	level.destroyedCount--;

	Assert( level.destroyedCount >= 0 );
}

get_destroyed_count()
{
	return( level.destroyedCount );
}

get_max_destroyed_count()
{
	return( level.maxDestructions );
}


init_destructible_frame_queue()
{
	level.destructibleFrameQueue = [];
}

add_destructible_to_frame_queue( destructible, partInfo, damage )
{
	entNum = self GetEntityNumber();

	if ( !isDefined( level.destructibleFrameQueue[ entNum ] ) )
	{
		level.destructibleFrameQueue[ entNum ] = SpawnStruct();
		level.destructibleFrameQueue[ entNum ].entNum = entNum;
		level.destructibleFrameQueue[ entNum ].destructible = destructible;
		level.destructibleFrameQueue[ entNum ].totalDamage = 0;
		level.destructibleFrameQueue[ entNum ].nearDistance = 9999999;
		level.destructibleFrameQueue[ entNum ].fxCost = 0;
	}

	level.destructibleFrameQueue[ entNum ].fxCost += partInfo.v[ "fxcost" ];

	level.destructibleFrameQueue[ entNum ].totalDamage += damage;
	if ( partInfo.v[ "distance" ] < level.destructibleFrameQueue[ entNum ].nearDistance )
		level.destructibleFrameQueue[ entNum ].nearDistance = partInfo.v[ "distance" ];

	thread handle_destructible_frame_queue();
}


handle_destructible_frame_queue()
{
	level notify( "handle_destructible_frame_queue" );
	level endon( "handle_destructible_frame_queue" );

	wait( 0.05 );

	currentQueue = level.destructibleFrameQueue;
	level.destructibleFrameQueue = [];

	sortedQueue = sort_destructible_frame_queue( currentQueue );

	for ( i = 0; i < sortedQueue.size; i++ )
	{
		if ( get_destroyed_count() < get_max_destroyed_count() )
		{
			if ( sortedQueue[ i ].fxCost )
				thread add_to_destroyed_count();

			sortedQueue[ i ].destructible notify( "queue_processed", true );
		}
		else
		{
			sortedQueue[ i ].destructible notify( "queue_processed", false );
		}
	}
}


sort_destructible_frame_queue( unsortedQueue )
{
	sortedQueue = [];
	foreach ( destructibleInfo in unsortedQueue )
		sortedQueue[ sortedQueue.size ] = destructibleInfo;

	// insertion sort
	for ( i = 1; i < sortedQueue.size; i++ )
	{
		queueStruct = sortedQueue[ i ];

		for ( j = i - 1; j >= 0 && get_better_destructible( queueStruct, sortedQueue[ j ] ) == queueStruct; j-- )
			sortedQueue[ j + 1 ] = sortedQueue[ j ];

		sortedQueue[ j + 1 ] = queueStruct;
	}

	return sortedQueue;
}


get_better_destructible( destructibleInfo1, destructibleInfo2 )
{
	// this is very basic; we can also account for distance, fxcost, etc... if we need to
	if ( destructibleInfo1.totalDamage > destructibleInfo2.totalDamage )
		return destructibleInfo1;
	else
		return destructibleInfo2;
}


get_part_FX_cost_for_action_state( partIndex, actionStateIndex )
{
	fxCost = 0;

	if ( !isDefined( level.destructible_type[ self.destructibleInfo ].parts[ partIndex ][ actionStateIndex ] ) )
		return fxCost;

	action_v = level.destructible_type[ self.destructibleInfo].parts[ partIndex ][ actionStateIndex ].v;

	if ( IsDefined( action_v[ "fx" ] ) )
	{
		foreach ( fxCostObj in action_v[ "fx_cost" ] )
		{
			foreach ( fxCostVal in fxCostObj )
				fxCost += fxCostVal;
		}
	}

	return fxCost;
}

// *************************************
// DOT - **TODO for iw6 move into seperate .gsc 
// *************************************

initDOT( type )
{
	AssertEx( IsDefined( type ), "Must specify a type of 'poision'" );
	
	if ( !flag_exist( "FLAG_DOT_init" ) )
	{
		flag_init( "FLAG_DOT_init" );
		//level._dots = [];
		flag_set( "FLAG_DOT_init" );
	}
	
	type = ToLower( type );
	
	switch ( type )
	{
		case "poison":
			if ( !flag_exist( "FLAG_DOT_poison_init" ) )
			{
				flag_init( "FLAG_DOT_poison_init" );
				PreCacheShellShock( "mp_radiation_low" );
				PreCacheShellShock( "mp_radiation_med" );
				PreCacheShellShock( "mp_radiation_high" );
				flag_set( "FLAG_DOT_poison_init" );
			}
			break;
		default:
			AssertMsg( "Must specify a type of 'poison'" );
	}
}

// Not sure if we will ever get support for this
//createDOT_sphere(){}

createDOT()
{
	dot 		= SpawnStruct();
	dot.ticks 	= [];
	
	return dot;
}

createDOT_radius( origin, spawnflags, radius, height )
{
	AssertEx( IsDefined( origin ), "Must specify a origin for the DOT" );
	AssertEx( IsDefined( spawnflags ), "Must specify spawnflags for the DOT" );
	AssertEx( IsDefined( radius ), "Must specify a radius for the DOT" );
	AssertEx( IsDefined( height ), "Must specify a height for the DOT" );
	
	dot = SpawnStruct();
	
	dot.type		= "trigger_radius";
	dot.origin		= origin;
	dot.spawnflags	= spawnflags;
	dot.radius		= radius;
	dot.minRadius	= radius;
	dot.maxRadius 	= radius;
	dot.height 		= height;
	
	dot.ticks		= [];
	
	return dot;
}

// There is a code request for this ... so stubbing this in for now
/*
createDOT_rect( origin, spawnflags, length, width, height ){}
*/
/*
addDOT_radius( origin, spawnflags, radius, height )
{
	AssertEx( IsDefined( origin ), "Must specify a origin for the DOT" );
	AssertEx( IsDefined( spawnflags ), "Must specify spawnflags for the DOT" );
	AssertEx( IsDefined( radius ), "Must specify a radius for the DOT" );
	AssertEx( IsDefined( height ), "Must specify a height for the DOT" );
	
	dot = SpawnStruct();
	
	dot.origin		= origin;
	dot.spawnflags	= spawnflags;
	dot.radius		= radius;
	dot.minRadius	= radius;
	dot.maxRadius 	= radius;
	dot.height 		= height;
	
	dot.ticks		= [];
	
	self.dot		= dot;
	dot.parent		= self;
	
	return dot;
}
*/

setDOT_origin( origin )
{
	AssertEx( IsDefined( origin ), "Must specify a origin" );
	
	self.origin = origin;
}

setDOT_radius( minRadius, maxRadius )
{
	// Check if this is a valid call for self
	
	if ( IsDefined( self.classname ) && self.classname != "trigger_radius" )
		AssertMsg( "You can only use setDOT_radius on trigger_radius" );
	
	AssertEx( IsDefined( minRadius ), "Must define minRadius" );
	
	if ( !IsDefined( maxRadius ) )
		maxRadius = minRadius;
	
	AssertEx( maxRadius >= minRadius, "maxRadius must be greater than minRadius" );
	AssertEx( self.radius >= maxRadius, "radius on trigger must be greater than or equal to maxRadius" );
	
	self.minRadius = minRadius;
	self.maxRadius = maxRadius;
}

setDOT_height( minHeight, maxHeight )
{
	// Check if this is a valid call for self
	
	if ( IsDefined( self.classname ) && IsSubStr( self.classname, "trigger" ) )
		AssertMsg( "You can only use setDOT_height on triggers" );
}

setDOT_onTick( delay, interval, duration, minDamage, maxDamage, falloff, type, affected )
{
	if ( IsDefined( delay ) )
		AssertEx( delay >= 0, "Must specify a delay >= 0" );
	else
		delay = 0;
	AssertEx( IsDefined( interval ) && interval > 0 , "Must specify an interval > 0" );
	AssertEx( IsDefined( duration ) && duration > 0, "Must specify a duration > 0" );
	AssertEx( duration > interval, "duration must be > interval" );
	AssertEx( IsDefined( minDamage ) && minDamage >= 0, "Must specify a minDamage >= 0" );
	AssertEx( IsDefined( maxDamage ) && maxDamage > 0, "Must specify a maxDamage > 0" );
	AssertEx( IsDefined( falloff ), "Must specify a falloff of 0 or 1" );
	AssertEx( IsDefined( type ), "Must specify a type of 'normal' or 'poison'" );
	AssertEx( IsDefined( affected ), "Must specify a type of 'player'" );

	type 		= ToLower( type );
	affected 	= ToLower( affected );
		
	index 							= self.ticks.size;
	
	self.ticks[ index ] 			= SpawnStruct();
	self.ticks[ index ].enable		= 0;
	self.ticks[ index ].delay		= delay;
	self.ticks[ index ].interval 	= interval;
	self.ticks[ index ].duration 	= duration;
	self.ticks[ index ].minDamage	= minDamage;
	self.ticks[ index ].maxDamage	= maxDamage;
	
	switch ( falloff )
	{
		case 0:
		case 1:
			break;
		default:
			AssertMsg( "Must specify a falloff of 0 or 1" );
	}
	
	self.ticks[ index ].falloff		= falloff;
	self.ticks[ index ].startTime	= 0;
	
	switch ( type )
	{
		case "normal":
			break;
		case "poison":
			switch( affected )
			{
				case "player":
					self.ticks[ index ].type 		= type;
					self.ticks[ index ].affected 	= affected;
					self.ticks[ index ].onEnterFunc = ::onEnterDOT_poisonDamagePlayer;
					self.ticks[ index ].onExitFunc	= ::onExitDOT_poisonDamagePlayer;
					self.ticks[ index ].onDeathFunc	= ::onDeathDOT_poisonDamagePlayer;
				break;
				default:
					AssertMsg( "Must specify the affected. Valid types are 'player'" );
			}
			break;
		default:
			AssertMsg( "Must specify a type. Valid types are 'normal' or 'poision'" );
	}
}


/*
removeDOT_onTick( funcs ){}
*/

buildDOT_onTick( duration, affected )
{
	AssertEx( IsDefined( duration ), "Must specify a duration > 0" );
	AssertEx( IsDefined( affected ), "Must specify a type of 'player'" );
	
	affected 	= ToLower( affected );
	
	index							= self.ticks.size;
	
	self.ticks[ index ] 			= SpawnStruct();
	self.ticks[ index ].duration	= duration;
	self.ticks[ index ].delay		= 0;
	self.ticks[ index ].onEnterFunc	= ::onEnterDOT_buildFunc;
	self.ticks[ index ].onExitFunc	= ::onExitDOT_buildFunc;
	self.ticks[ index ].onDeathFunc	= ::onDeathDOT_buildFunc;
	
	switch( affected )
	{
		case "player":
			self.ticks[ index ].affected = affected;
		break;
		default:
			AssertMsg( "Must specify the affected. Valid types are 'player'" );
	}
}

buildDOT_startLoop( count )
{
	AssertEx( IsDefined( count ), "Must specify a count >= 0" );
	AssertEx( IsDefined( self.ticks ) && self.ticks.size >= 0, "Must call buildDOT_onTick first" );
	
	index = self.ticks.size - 1;
	
	if ( !IsDefined( self.ticks[ index ].statements ) )
		self.ticks[ index ].statements = [];
	
	statementIndex = self.ticks[ index ].statements.size;
	
	self.ticks[ index ].statements						= [];
	self.ticks[ index ].statements[ "vars" ] 			= [];
	self.ticks[ index ].statements[ "vars" ][ "count" ] = count;
}

buildDOT_damage( minDamage, maxDamage, falloff, damageFlag, meansOfDeath, weapon )
{
	AssertEx( IsDefined( minDamage ), "" );
	AssertEx( IsDefined( maxDamage ), "" );
	AssertEx( IsDefined( falloff ), "" );
	AssertEx( IsDefined( damageFlag ), "" );
	AssertEx( IsDefined( meansOfDeath ), "" );
	AssertEx( IsDefined( weapon ), "" );
	AssertEx( IsDefined( self.ticks ), "Must call buildDOT_startLoop first" );
	
	tickIndex = self.ticks.size - 1;
	
	AssertEx( IsDefined( self.ticks[ tickIndex ] ) &&
			  IsDefined( self.ticks[ tickIndex ].statements ), "Must call buildDOT_startLoop first" );
			  
	if ( !IsDefined( self.ticks[ tickIndex ].statements[ "actions" ] ) )
		self.ticks[ tickIndex ].statements[ "actions" ] = [];
		
	actionIndex = self.ticks[ tickIndex ].statements[ "actions" ].size;
	
	self.ticks[ tickIndex ].statements[ "actions" ][ actionIndex ] 				= [];
	self.ticks[ tickIndex ].statements[ "actions" ][ actionIndex ][ "vars" ] 	= [ minDamage, maxDamage, falloff, damageFlag, meansOfDeath, weapon ];
	self.ticks[ tickIndex ].statements[ "actions" ][ actionIndex ][ "func" ]	= ::doBuildDOT_damage;
}

buildDOT_wait( time )
{
	AssertEx( IsDefined( time ), "Must specify time >= 0" );
	AssertEx( IsDefined( self.ticks ), "Must call buildDOT_startLoop first" );
	
	tickIndex = self.ticks.size - 1;
	
	AssertEx( IsDefined( self.ticks[ tickIndex ] ) &&
			  IsDefined( self.ticks[ tickIndex ].statements ), "Must call buildDOT_startLoop first" );
			  
	if ( !IsDefined( self.ticks[ tickIndex ].statements[ "actions" ] ) )
		self.ticks[ tickIndex ].statements[ "actions" ] = [];
		
	actionIndex = self.ticks[ tickIndex ].statements[ "actions" ].size;
	
	self.ticks[ tickIndex ].statements[ "actions" ][ actionIndex ] 				= [];
	self.ticks[ tickIndex ].statements[ "actions" ][ actionIndex ][ "vars" ] 	= [ time ];
	self.ticks[ tickIndex ].statements[ "actions" ][ actionIndex ][ "func" ]	= ::doBuildDOT_wait;
}
		
onEnterDOT_buildFunc( idx, trigger )
{
	AssertEx( IsDefined( idx ), "Must specify an index for this function" );
	AssertEx( IsDefined( trigger ), "trying to run tick function on DOT that has been removed or is undefined" );
	
	entNum = trigger GetEntityNumber();
	
	trigger endon( "death" );
	trigger endon( "LISTEN_kill_tick_" + idx + "_" + entNum );
	
	self endon( "disconnect" );
	self endon( "game_ended" );
	self endon( "death" );
	self endon( "LISTEN_exit_dot_" + entNum );
	
	entNum 		= undefined;
	statements 	= trigger.ticks[ idx ].statements;
	
	if ( !IsDefined( statements ) || 
		 !IsDefined( statements[ "vars" ] ) || 
		 !IsDefined( statements[ "vars" ][ "count" ] ) ||
		 !IsDefined( statements[ "actions" ] ) )
		return;
		
	count 		= statements[ "vars" ][ "count" ];
	actions 	= statements[ "actions" ];
	statements 	= undefined; 
	
	// count = 0 runs loop forever
	// count >= 1 runs the loop count number of times
	
	for ( i = 1; i <= count || count == 0; i-- )
	{
		foreach ( action in actions )
		{
			vars = action[ "vars" ];
			func = action[ "func" ];
			
			self [[ func ]]( idx, trigger, vars );
		}
	}
}

onExitDOT_buildFunc( idx, trigger )
{
	entNum 		= trigger GetEntityNumber();
	playerNum 	= self GetEntityNumber();
	
	trigger notify( "LISTEN_kill_tick_" + idx + "_" + entNum + "_" + playerNum );
}

onDeathDOT_buildFunc( idx, trigger ){}

doBuildDOT_damage( idx, trigger, vars )
{
	AssertEx( IsDefined( idx ), "Must specify an index >= 0" );
	AssertEx( IsDefined( trigger ), "Must specify a trigger" );
	AssertEx( IsDefined( vars ), "Must specify vars" );
	
	minDamage 		= vars[ 0 ];
	maxDamage 		= vars[ 1 ];
	falloff 		= vars[ 2 ];
	damageFlag 		= vars[ 3 ];
	meansOfDeath 	= vars[ 4 ];
	weapon			= vars[ 5 ];
	
	self thread [[ level.callbackPlayerDamage ]](
		trigger,					// eInflictor The entity that causes the damage.( e.g. a turret )
		trigger,					// eAttacker The entity that is attacking.
		maxDamage,					// iDamage Integer specifying the amount of damage done
		damageFlag,					// iDFlags Integer specifying flags that are to be applied to the damage
		meansOfDeath,				// sMeansOfDeath Integer specifying the method of death
		weapon,						// sWeapon The weapon number of the weapon used to inflict the damage
		trigger.origin,				// vPoint The point the damage is from?
		( 0,0,0 ) - trigger.origin,// vDir The direction of the damage
		"none",						// sHitLoc The location of the hit
		0							// psOffsetTime The time offset for the damage
		);
}

doBuildDOT_wait( idx, trigger, vars )
{
	AssertEx( IsDefined( idx ), "Must specify an index >= 0" );
	AssertEx( IsDefined( trigger ), "Must specify a trigger" );
	AssertEx( IsDefined( vars ), "Must specify vars" );
	
	entNum 		= trigger GetEntityNumber();
	playerNum 	= self GetEntityNumber();
	
	trigger endon( "death" );
	trigger endon( "LISTEN_kill_tick_" + idx + "_" + entNum );
	trigger notify( "LISTEN_kill_tick_" + idx + "_" + entNum + "_" + playerNum );
	
	self endon( "disconnect" );
	self endon( "game_ended" );
	self endon( "death" );
	self endon( "LISTEN_exit_dot_" + entNum );
	
	entNum 		= undefined;
	playerNum 	= undefined;
	
	wait vars[ 0 ];
}

startDOT_group( dots )
{
	AssertEx( IsDefined( dots ), "Must specify an array of dots to start" );
	
	triggers = [];
	
	foreach ( dot in dots )
	{
		// Spawn the appropriate dot.type aka trigger
		
		trigger = undefined;
		
		switch ( dot.type )
		{
			case "trigger_radius":				
				trigger = Spawn( "trigger_radius", dot.origin, dot.spawnflags, dot.radius, dot.height );
				AssertEx( IsDefined( trigger ), "Could not spawn a trigger, too many entities" );
				
				trigger.minRadius 			= dot.minRadius;
				trigger.maxRadius 			= dot.maxRadius;
				trigger.ticks 				= dot.ticks;
				triggers[ triggers.size ] 	= trigger;
				break;
			default:
				AssertMsg( ".type for DOT is not supported" );
		}
		
		// Link to parent if it was defined
		
		if ( IsDefined( dot.parent ) )
		{
			trigger LinkTo( dot.parent );
			dot.parent.dot = trigger;
		}
		
		ticks = trigger.ticks;
			
		// Initialize ticks
		
		foreach ( tick in ticks )
			tick.startTime = GetTime();
		
		foreach ( tick in ticks )
			if ( !tick.delay )
				tick.enable = 1;
				
		// Check if there is a tick on player
		
		foreach ( tick in ticks )
		{
			if ( IsSubStr( tick.affected, "player" ) )
			{
				trigger.onPlayer = 1;
				break;
			}
		}
	}
	
	// Populate a group list for each trigger. Exclude self from list
	
	foreach ( trigger in triggers )
	{
		trigger.DOT_group = [];
		
		foreach ( _trigger in triggers )
		{
			if ( trigger == _trigger )
				continue;
			trigger.DOT_group[ trigger.DOT_group.size ] = _trigger;
		} 
	}
	
	// Start DOT on player
	
	foreach ( trigger in triggers )
		if ( trigger.onPlayer )
			trigger thread startDOT_player();
	
	// Monitor DOTs
	
	foreach ( trigger in triggers )
		trigger thread monitorDOT();
}

startDOT_player()
{
	self thread triggerTouchThink( ::onEnterDOT_player, ::onExitDOT_player );
}

// Check to see when we should delete a DOT

monitorDOT()
{
	startTime = GetTime();
	
	for ( ; IsDefined( self ); wait 0.05 )
	{
		foreach ( i, tick in self.ticks )
		{
			if ( IsDefined( tick ) && GetTime() - startTime >= tick.duration * 1000 )
			{
				entNum = self GetEntityNumber();
				self notify( "LISTEN_kill_tick_" + i + "_" + entNum );
				self.ticks[ i ] = undefined;
			}
		}
				
		if ( !self.ticks.size )
			break;
	}
	
	if ( IsDefined( self ) )
	{
		foreach ( tick in self.ticks )
			self [[ tick.onDeathFunc ]]();
		
		self notify( "death" );
		self Delete();
	}
}

onEnterDOT_player( trigger )
{
	Assert( IsDefined( trigger ) );
	
	entNum = trigger GetEntityNumber();

	self notify( "LISTEN_enter_dot_" + entNum );
	
	foreach ( i, tick in trigger.ticks )
		if ( !tick.enable )
			self thread doDOT_delayFunc( i, trigger, tick.delay, tick.onEnterFunc );
			
	foreach ( i, tick in trigger.ticks )
		if ( tick.enable && tick.affected == "player" )
			self thread [[ tick.onEnterFunc ]]( i, trigger );
}

onExitDOT_player( trigger )
{
	Assert( IsDefined( trigger ) );
	
	entNum = trigger GetEntityNumber();
	
	self notify( "LISTEN_exit_dot_" + entNum );
	
	foreach ( i, tick in trigger.ticks )
		if ( tick.enable && tick.affected == "player" )
			self thread [[ tick.onExitFunc ]]( i, trigger );
}

doDOT_delayFunc( idx, trigger, delay, func )
{
	Assert( IsDefined( trigger ) );
	
	entNum 		= trigger GetEntityNumber();
	playerNum 	= self GetEntityNumber();
	
	trigger endon( "LISTEN_kill_tick_" + idx + "_" + entNum + "_" + playerNum );
	
	self endon( "disconnect" );
	self endon( "game_ended" );
	self endon( "death" );
	
	self notify( "LISTEN_exit_dot_" + entNum );

	entNum 		= undefined;
	playerNum 	= undefined;
	
	wait delay;
	
	self thread [[ func ]]( idx, trigger );
}

/*
soundWatcher( entNum )
{
	Assert( IsDefined( entNum ) );
	
	self waittill_any( "death", "LISTEN_exit_dot_ + entNum  );
	
	self StopLoopSound();
}
*/

// This is a predefined DOT function
	
onEnterDOT_poisonDamagePlayer( idx, trigger )
{
	AssertEx( IsDefined( idx ), "Must specify an index for this function" );
	AssertEx( IsDefined( trigger ), "trying to run tick function on DOT that has been removed or is undefined" );
	
	entNum 		= trigger GetEntityNumber();
	playerNum 	= self GetEntityNumber();
	
	trigger endon( "death" );
	trigger endon( "LISTEN_kill_tick_" + idx + "_" + entNum );
	trigger endon( "LISTEN_kill_tick_" + idx + "_" + entNum + "_" + playerNum );
	
	self endon( "disconnect" );
	self endon( "game_ended" );
	self endon( "death" );
	self endon( "LISTEN_exit_dot_" + entNum );
	
	// Setup vars to keep track of number times player has been damaged by the trigger
	// For now this damage function is almost the same as the maps\mp\_radiatoin::radiationEffect
	
	if ( !IsDefined( self.onEnterDOT_poisonDamageCount ) )
		self.onEnterDOT_poisonDamageCount = [];
	if ( !IsDefined( self.onEnterDOT_poisonDamageCount[ idx ] ) )
		self.onEnterDOT_poisonDamageCount[ idx ] = [];
	self.onEnterDOT_poisonDamageCount[ idx ][ entNum ] = 0;
	
	//self thread soundWatcher( entNum );
	
	damageMultiplier = ter_op( isSP(), 1.5, 1 );
	
	for ( ; IsDefined( trigger ) && IsDefined( trigger.ticks[ idx ] ); wait trigger.ticks[ idx ].interval )
	{
		self.onEnterDOT_poisonDamageCount[ idx ][ entNum ]++;
		
		switch ( self.onEnterDOT_poisonDamageCount[ idx ][ entNum ] )
		{
			case 1:
				self ViewKick( 1, self.origin );
				break;
			case 3:				  
				self ShellShock( "mp_radiation_low", 4 );

				//self ViewKick( 3, self.origin );
				self doDOT_poisonDamage( trigger, damageMultiplier * 2 );
				break;
			case 4:
				self ShellShock( "mp_radiation_med", 5 );

				//self ViewKick( 15, self.origin );
				self thread doDOT_poisonBlackout( idx, trigger );
				self doDOT_poisonDamage( trigger, damageMultiplier * 2 );
				break;
			case 6:
				self ShellShock( "mp_radiation_high", 5 );

				//self ViewKick( 75, self.origin );
				self doDOT_poisonDamage( trigger, damageMultiplier * 2 );
				break;
			case 8:
				self ShellShock( "mp_radiation_high", 5 );

				//self ViewKick( 127, self.origin );
				self doDOT_poisonDamage( trigger, damageMultiplier * 500 );
				break;
		}
	}	
}

onExitDOT_poisonDamagePlayer( idx, trigger )
{
	AssertEx( IsDefined( idx ), "Must specify an index for this function" );
	AssertEx( IsDefined( trigger ), "trying to run tick function on DOT that has been removed or is undefined" );
	
	entNum 		= trigger GetEntityNumber();
	playerNum	= self GetEntityNumber();
	overlays 	= self.onEnterDOT_poisonDamageOverlay;
	
	if ( IsDefined( overlays ) )
	{
		foreach ( i, _ in overlays )
		{
			if ( IsDefined( overlays[ i ] ) &&
				 IsDefined( overlays[ i ][ entNum ] ) )
			{
				overlays[ i ][ entNum ] thread doDOT_fadeOutBlackOut( 0.1, 0 );
			}
		}
	}
	trigger notify( "LISTEN_kill_tick_" + idx + "_" + entNum + "_" + playerNum );
}

onDeathDOT_poisonDamagePlayer()
{
	entNum = self GetEntityNumber();
		
	foreach ( player in level.players )
	{
		overlays = player.onEnterDOT_poisonDamageOverlay;
		
		if ( IsDefined( overlays ) )
		{
			foreach ( i, _ in overlays )
			{
				if ( IsDefined( overlays[ i ] ) &&
					 IsDefined( overlays[ i ][ entNum ] ) )
				{
					overlays[ i ][ entNum ] thread doDOT_fadeOutBlackOutAndDestroy();
				}
			}
		}
	}
}

doDOT_poisonDamage( trigger, damage )
{
	if ( isSP() )
	{/*
		self doDamage(
		damage,					// iDamage Integer specifying the amount of damage done
		self.origin,			// vPoint The point the damage is from?
		self,					// eAttacker The entity that is attacking.
		self					// eInflictor The entity that causes the damage.( e.g. a turret )
		);*/
	}
	else
	{
		self thread [[ level.callbackPlayerDamage ]](
		trigger,					// eInflictor The entity that causes the damage.( e.g. a turret )
		trigger,					// eAttacker The entity that is attacking.
		damage,					// iDamage Integer specifying the amount of damage done
		0,						// iDFlags Integer specifying flags that are to be applied to the damage
		"MOD_SUICIDE",			// sMeansOfDeath Integer specifying the method of death
		"claymore_mp",			// sWeapon The weapon number of the weapon used to inflict the damage
		trigger.origin,			// vPoint The point the damage is from?
		( 0,0,0 ) - trigger.origin,// vDir The direction of the damage
		"none",					// sHitLoc The location of the hit
		0						// psOffsetTime The time offset for the damage
		);
	}
}

doDOT_poisonBlackout( idx, trigger )
{
	AssertEx( IsDefined( idx ), "Must specify an index for this function" );
	AssertEx( IsDefined( trigger ), "trying to run tick function on DOT that has been removed or is undefined" );
	
	entNum 		= trigger GetEntityNumber();
	playerNum 	= self GetEntityNumber();
	
	trigger endon( "death" );
	trigger endon( "LISTEN_kill_tick_" + idx + "_" + entNum );
	trigger endon( "LISTEN_kill_tick_" + idx + "_" + entNum + "_" + playerNum );
	
	self endon( "disconnect" );
	self endon( "game_ended" );
	self endon( "death" );
	self endon( "LISTEN_exit_dot_" + entNum );

	if ( !IsDefined( self.onEnterDOT_poisonDamageOverlay ) )
		self.onEnterDOT_poisonDamageOverlay = [];
	if ( !IsDefined( self.onEnterDOT_poisonDamageOverlay[ idx ] ) )
		self.onEnterDOT_poisonDamageOverlay[ idx ] = [];
		
	if ( !IsDefined( self.onEnterDOT_poisonDamageOverlay[ idx ][ entNum ] ) )
	{
		overlay 			= NewClientHudElem( self );
		overlay.x 			= 0;
		overlay.y 			= 0;
		overlay.alignX 		= "left";
		overlay.alignY 		= "top";
		overlay.horzAlign	= "fullscreen";
		overlay.vertAlign 	= "fullscreen";
		overlay.alpha 		= 0;
		overlay SetShader( "black", 640, 480 );
		
		self.onEnterDOT_poisonDamageOverlay[ idx ][ entNum ] = overlay;
	}

	overlay = self.onEnterDOT_poisonDamageOverlay[ idx ][ entNum ];
	
	min_length 	= 1;
	max_length 	= 2;
	min_alpha 	= .25;
	max_alpha 	= 1;

	min_percent = 5;
	max_percent = 100;

	fraction 	= 0;

	for ( ;; )
	{
		while ( self.onEnterDOT_poisonDamageCount[ idx ][ entNum ] > 1 )
		{
			percent_range = max_percent - min_percent;
			fraction = ( self.onEnterDOT_poisonDamageCount[ idx ][ entNum ] - min_percent ) / percent_range;

			if ( fraction < 0 )
				fraction = 0;
			else if ( fraction > 1 )
				fraction = 1;

			length_range = max_length - min_length;
			length = min_length + ( length_range * ( 1 - fraction ) );

			alpha_range = max_alpha - min_alpha;
			alpha = min_alpha + ( alpha_range * fraction );

			end_alpha = fraction * 0.5;

			if ( fraction == 1 )
				break;

			duration = length / 2;

			overlay doDOT_fadeInBlackOut( duration, alpha );
			overlay doDOT_fadeOutBlackOut( duration, end_alpha );

			wait( fraction * 0.5 );
		}

		if ( fraction == 1 )
			break;

		if ( overlay.alpha != 0 )
			overlay doDOT_fadeOutBlackOut( 1, 0 );

		wait 0.05;
	}
	overlay doDOT_fadeInBlackOut( 2, 0 );
}

doDOT_fadeInBlackOut( duration, alpha )
{
	self fadeOverTime( duration );
	self.alpha = alpha;
	alpha = undefined;
	wait duration;
}

doDOT_fadeOutBlackOut( duration, alpha )
{
	self fadeOverTime( duration );
	self.alpha = alpha;
	alpha = undefined;
	wait duration;
}

doDOT_fadeOutBlackOutAndDestroy( duration, alpha )
{
	self fadeOverTime( duration );
	self.alpha = alpha;
	alpha = undefined;
	wait duration;
	self Destroy();
}

triggerTouchThink( enterFunc, exitFunc )
{
	level endon( "game_ended" );
	self endon ( "death" );

	self.entNum = self GetEntityNumber();

	for ( ; ; )
	{
		self waittill( "trigger", player );

		if ( !isPlayer( player ) && !isDefined( player.finished_spawning ) )
			continue;

		if ( !isAlive( player ) )
			continue;

		if ( !isDefined( player.touchTriggers[ self.entNum ] ) )
			player thread playerTouchTriggerThink( self, enterFunc, exitFunc );
	}
}

// This is modified ver of _dynamic_world::playerTouchTriggerThink

playerTouchTriggerThink( trigger, enterFunc, exitFunc )
{
	trigger endon( "death" );
	
	if ( !isPlayer( self ) )
		self endon( "death" );

	if ( !isSP() )
		touchName = self.guid;	// generate GUID
	else
		touchName = "player" + gettime();		// generate GUID

	trigger.touchList[ touchName ] = self;
	if ( isDefined( trigger.moveTracker ) )
		self.moveTrackers++ ;

	trigger notify( "trigger_enter", self );
	self notify( "trigger_enter", trigger );

	// Check if player is already touching a trigger belonging to a DOT group
	
	doEnterExitFunc = true;
	
	foreach ( trig in trigger.DOT_group )
		foreach ( _trig in self.touchTriggers )
			if ( trig == _trig )
				doEnterExitFunc = false;
		
	if ( doEnterExitFunc && IsDefined( enterFunc ) )
		self thread [[ enterFunc ]]( trigger );

	self.touchTriggers[ trigger.entNum ] = trigger;

	// Do some extra checks to see if the player is touching any other trigger in the same group
	
	while ( IsAlive( self ) && ( isSP() || !level.gameEnded ) )
	{
		touchingTrigger = true;
		
		if ( self IsTouching( trigger ) )
			wait 0.05;
		else
		{
			if ( !trigger.DOT_group.size )
				touchingTrigger = false;
				
			foreach ( trig in trigger.DOT_group )
			{
				if ( self IsTouching( trig ) )
				{
					wait 0.05;
					break;
				}
				else
				{
					touchingTrigger = false;
				}
			}
		}
					
		if ( !touchingTrigger )
			break;
	}

	// disconnected player will skip this code
	if ( isDefined( self ) )
	{
		self.touchTriggers[ trigger.entNum ] = undefined;
		if ( isDefined( trigger.moveTracker ) )
			self.moveTrackers -- ;

		self notify( "trigger_leave", trigger );

		if ( doEnterExitFunc && IsDefined( exitFunc ) )
			self thread [[ exitFunc ]]( trigger );
	}

	if ( !isSP() && level.gameEnded )
		return;

	trigger.touchList[ touchName ] = undefined;
	trigger notify( "trigger_leave", self );

	if ( !anythingTouchingTrigger( trigger ) )
		trigger notify( "trigger_empty" );
}

anythingTouchingTrigger( trigger )
{
	return( trigger.touchList.size );
}