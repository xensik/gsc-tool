#include common_scripts\utility;
#include maps\_utility;

CONST_MIN_SQUAD_SPAWNERS		= 4;	// min required leader spawners in level, must be >=2
CONST_MAINTAIN_SQUAD_NUM 		= 4;	// number of squads to maintain
CONST_SQUAD_FILL_DELAY 			= 0.15;	// seconds delay of squad respawn to fill in
CONST_MAX_FOLLOW_DIST 			= 800;	// max units squad members are following leader
CONST_FOLLOW_DIST				= 600;	// units squad members following leader
CONST_MERGE_SQUAD_MEMBER_MAX 	= 3;	// when merging squads, the new squad can not have more than this number of AI
CONST_RIOTSHIELD_FOLLOW_DIST 	= 45;	// units squad member will follow behind riotshield leader, 45 or less is very close
CONST_RIOTSHIELD_FOLLOW_ANGLE	= 145;	// angle for squad member to position behind riotshield leader
CONST_RIOTSHIELD_FOLLOW_RADIUS	= 8;	// goal radius while squad members follow riotshield
CONST_SQUAD_LEADER_GOALRADIUS	= 2048;	// default goal radius of a squad leader vs player

squad_setup( struct_spawner )
{
	if ( !flag_exist( "squad_spawning" ) )
		flag_init( "squad_spawning" );
	
	level.new_squad_logic = true;
	level.merge_squad_member_max = CONST_MERGE_SQUAD_MEMBER_MAX;
	
	// squad leader spawner must have script_noteworthy = "leader", this spawner targets follower spawners
	level.leaders = [];
	if ( isdefined( struct_spawner ) && struct_spawner )
		all_spawn_locs = getstructarray( "leader", "script_noteworthy" );
	else
		all_spawn_locs = getentarray( "leader", "script_noteworthy" );

	// removing all scripted protector squad spawns, as protectors have their own behavior
	foreach ( spawner in all_spawn_locs )
	{
		if ( isdefined( spawner.targetname ) && isSubStr( spawner.targetname, "protector" ) )
			all_spawn_locs = array_remove( all_spawn_locs, spawner );
	}
	
	// using new custom follower logic
	level.squad_follower_func = ::setup_follower_advanced;
	// merge squads when only a few left in each
	thread merge_squad();
	// enlarges follower following radius when leaders at too close, avoid cluster
	thread squad_spread();
	// debug
	thread drawLeader();
	
	return all_spawn_locs;
}

squad_disband( delay, behavior_func, param1 )
{
	if ( isdefined( delay ) && delay > 0 )
		wait delay;
	
	if ( flag_exist( "squad_spawning" ) )
		flag_waitopen( "squad_spawning" );
	
	level notify( "squad_disband" );
	
	level.leaders = [];
	
	if ( isdefined( behavior_func ) )
	{
		bad_guys = getaiarray( "axis" );
		foreach ( guy in bad_guys )
		{
			// end manage ai thread if running on AI
			guy notify( "ai_behavior_change" );
			
			guy.leader = undefined;
			guy.squadmembers = undefined;
			
			if ( isdefined( guy.is_squad_enemy ) && guy.is_squad_enemy )
			{
				if ( isdefined( param1 ) )
					guy thread [[ behavior_func ]]( param1 );
				else
					guy thread [[ behavior_func ]]();
			}
			guy.is_squad_enemy = false;
		}
	}
}

// ============================================================================
//			Zones are for triggering squad spawns
// ============================================================================

// trig = trigger to spawn squads, trigger must be linked to multiple squads
// spawn_num = number of squads to be spawned, will be selected randomly from the linked squad spawners
// level.squad_zoning = true; // enables it

setup_zones( trig, spawn_num )
{
	level endon( "challenge_success" );
	level endon( "special_op_terminated" );
	
	if ( !flag_exist( "squad_spawning" ) )
		flag_init( "squad_spawning" );
		
	zone_spawn_names = trig get_links();
	
	zone_spawners = [];
	foreach ( spawn_name in zone_spawn_names )
		zone_spawners[ zone_spawners.size ] = getent( spawn_name, "script_linkname" );

	trig thread one_direction_trigger();
	trig waittill( "trigger" );

	if ( getAiarray( "axis" ).size > 1 )
	{
		level.cleaning_up = true;
		squad_clean_up();
		wait 2.02; // wait for clean up
	}
	else
	{
		level.cleaning_up = false;
	}
	
	if ( ( level.leaders.size + spawn_num ) > level.desired_squads )
		spawn_num = level.desired_squads - level.leaders.size;
	
	for ( i=0; i<spawn_num; i++ )
		spawn_far_squad( zone_spawners, undefined, undefined, undefined );
	
	wait ( 1 );
	
	level.cleaning_up = false;
	
	level notify( "clean_up_done" ); // cycle fillers wait for this
	level notify( "zone_spawn_complete" );	// fillers logic start waits for this
}

// spawn squads from random far locations
spawn_enemy_squads( follower_size )
{
	level endon( "challenge_success" );
	level endon( "special_op_terminated" );
	
	all_spawn_locs = squad_setup();
	
	// level.desired_squads is number of active squads to be maintained
	if( !isdefined( level.desired_squads ) )
		level.desired_squads = CONST_MAINTAIN_SQUAD_NUM;
	else
	{
		msg = "Must have at least " + CONST_MIN_SQUAD_SPAWNERS + " squad leader spawners in level";
		assertex( level.desired_squads >= CONST_MIN_SQUAD_SPAWNERS, msg );
	}
	
	if ( isdefined( level.squad_zoning ) && level.squad_zoning )
	{
		zone_trigs = getentarray( "zone_trig", "targetname" );
		foreach ( trig in zone_trigs )
			thread setup_zones( trig, int( trig.script_noteworthy ) );
			
		// wait till any zone has completed spawning so we can continue to refill it
		level waittill( "zone_spawn_complete" );
	}
	
	// spawns and refills squads to level.desired_squads size
	while( 1 )
	{
		wait CONST_SQUAD_FILL_DELAY;
		
		// this is here cuz zoning does clean up
		if ( isdefined( level.cleaning_up ) && level.cleaning_up )
			level waittill( "clean_up_done" );
		
		if ( level.leaders.size < level.desired_squads )
			spawn_far_squad( all_spawn_locs, undefined, undefined, follower_size );
	}
}

spawn_far_squad( all_spawn_locs, leader_class, follower_class, follower_size )
{	
	// pick a spawn thats far from all enemies and players
	avoid_locs = [];
	avoid_locs[ avoid_locs.size ] = level.player;
	if( is_coop() ) 
	{ 
		avoid_locs[ avoid_locs.size ] = level.players[ 1 ]; 
	}
	foreach ( leader in level.leaders )
	{
		avoid_locs[ avoid_locs.size ] = leader;
	}

	spawn_loc = undefined;
	while( all_spawn_locs.size > ( 1 ) )
	{
		foreach ( avoid_loc in avoid_locs )
		{
			spawn_loc = getclosest( avoid_loc.origin, all_spawn_locs );
			//thread draw_debug_marker( spawn_loc.origin, ( 1, 0.5, 0.5 ) );
			all_spawn_locs = array_remove( all_spawn_locs, spawn_loc );
			if ( all_spawn_locs.size == 1 )
				break;
		}
	}
	
	spawn_loc = all_spawn_locs[ 0 ];
	thread draw_debug_marker( spawn_loc.origin, ( 1, 1, 1 ) );
	
	// spawn_loc is the leader spawner we picked
	assert( isdefined( spawn_loc ) );
	
	// support for struct spawner
	if ( isspawner( all_spawn_locs[ 0 ] ) )
		spawners = getentarray( spawn_loc.target, "targetname" );
	else
		spawners = getstructarray( spawn_loc.target, "targetname" );
	
	spawners[ spawners.size ] = spawn_loc;	// include leader as well

	foreach ( spawner in spawners )
	{
		if ( !isdefined( spawner.script_noteworthy ) )
			spawner.script_noteworthy = "follower";
	}
	
	flag_set( "squad_spawning" );
	group = [];
	group = spawn_enemy_group( spawners, leader_class, follower_class, follower_size );	
	flag_clear( "squad_spawning" );

	wait 0.05;
	
	return group;
}

squad_clean_up()
{
	// deletes enemies that arent insight and are far away, but not protectors
	ai_array = getaiarray( "axis" );

	foreach ( spawner in ai_array )
	{
		if ( isdefined( spawner.protector_obj_group ) )
			ai_array = array_remove( ai_array, spawner );
	}
	
	// delete enemies not insight, and are not objective protectors
	thread AI_delete_when_out_of_sight( ai_array, 1300 );
}

// when two leaders are too close, their followers will have larger following radius to move around farther; uncluttered.
// NOTE: this might not be effective enough, be nice to have control to spread leader AI apart in the same radius
squad_spread()
{
	level endon( "challenge_success" );
	level endon( "special_op_terminated" );
		
	while ( 1 )	
	{
		wait 1;
		
		// skip if squads not ready
		if ( !isdefined( level.leaders ) )
			continue;
		if ( level.leaders.size < 2 )
			continue;
		
		// TODO: probably can be scripted with less than n^3-n^2 complexity
		foreach ( leader in level.leaders )
		{
			if( !isdefined( leader.squadmembers ) || leader.squadmembers.size < 2 )
					continue;
					
			foreach ( other_leader in level.leaders )
			{	
				if ( other_leader == leader )
					continue;
					
				if( !isdefined( other_leader.squadmembers ) || other_leader.squadmembers.size < 2 )
					continue;

				if( distance( leader.origin, other_leader.origin ) < CONST_FOLLOW_DIST )
				{
					foreach( follower in other_leader.squadmembers )
					{
						if ( isdefined( follower.saw_player ) && follower.saw_player )
							follower.goalradius = CONST_MAX_FOLLOW_DIST;
					}
				}
				else
				{
					foreach( follower in other_leader.squadmembers )
					{
						if ( isdefined( follower.saw_player ) && follower.saw_player )
							follower.goalradius = CONST_FOLLOW_DIST;
					}					
				}
			}	
		}	
	}
}

// monitors all squads for mergable squads
merge_squad()
{
	level endon( "challenge_success" );
	level endon( "special_op_terminated" );

	while ( 1 )
	{
		wait 2; // merge cycle delay
		
		// skip if squads not ready
		if ( !isdefined( level.leaders ) )
			continue;
		if ( level.leaders.size < 2 )
			continue;
		
		// find the two smallest squads
		// find smallest
		smallest_leader = level.leaders[ 0 ];
		foreach ( leader in level.leaders )
		{
			if ( smallest_leader.squadmembers.size > leader.squadmembers.size )
				smallest_leader = leader;	
		}
		
		// find second smallest
		remaining = array_remove( level.leaders, smallest_leader );
		second_smallest_leader = remaining[ 0 ];
		foreach ( leader in remaining )
		{
			if ( second_smallest_leader.squadmembers.size > leader.squadmembers.size )
				second_smallest_leader = leader;	
		}	
		
		// smallest and second_smallest merged size must be <= max allowed squad size
		merge_size = smallest_leader.squadmembers.size + second_smallest_leader.squadmembers.size + 2; // +2 leaders
		if ( merge_size <= CONST_MERGE_SQUAD_MEMBER_MAX )
		{
			// merging!
			
			// remove smallest leader from leaders array and demote him
			level.leaders = array_remove( level.leaders, smallest_leader );
			smallest_leader notify( "demotion" );
			
			// build group with all AI in group for setup_leader(group)
			group = array_combine( smallest_leader.squadmembers, second_smallest_leader.squadmembers );
			group[ group.size ] = smallest_leader;
			group[ group.size ] = second_smallest_leader;
			
			// setup the new leader
			second_smallest_leader thread setup_leader( group );
			
			// setup all followers of new leader, including existing followers - to remove duplicates
			followers = array_remove( group, second_smallest_leader );
			foreach ( guy in followers )
			{
				if ( isalive( guy ) )
					guy thread setup_follower( second_smallest_leader );
			}
		}
	}
}

// spawn new squad
spawn_enemy_group( spawners, leader_class, follower_class, follower_size )
{
	level endon( "challenge_success" );
	level endon( "special_op_terminated" );
		
	// either custom or not, no half way
	assertex( isdefined( leader_class ) == isdefined( follower_class ), "Squad leader and follower class overrides must be either both or none" );
	
	custom_spawner = false;
	if ( isdefined( leader_class ) )
		custom_spawner = true;
		
	if( !isdefined( level.leaders ) )
		level.leaders = [];
	
	AssertEx( ( spawners.size > 0 ), "The array passed to array_spawn function is empty" );

	// custom size of followers, <= than available follower spawners, usually 3
	if ( !isdefined( follower_size ) )
		follower_size = spawners.size - 1;
	else
		follower_size = int( min( spawners.size - 1, follower_size ) );

	msg = "Trying to spawn "+follower_size+" followers but only "+ (spawners.size-1) + " spawners are available!";
	AssertEx( follower_size < spawners.size, msg );
	
	// build custom spawners array
	// =============================
	if ( custom_spawner || !isspawner( spawners[ 0 ] ) )
	{
		leader_spawner 		= undefined;
		follower_spawner 	= undefined;
		all_spawners 		= getspawnerarray();
		
		foreach( ai_spawner in all_spawners )
		{
			if ( ai_spawner.classname == leader_class )
				leader_spawner = ai_spawner;
			if ( ai_spawner.classname == follower_class )
				follower_spawner = ai_spawner;
		}

		assertex( isdefined( leader_spawner ), "Trying to spawn: [" + leader_class + "] without spawner present in level" );
		assertex( isdefined( follower_spawner ), "Trying to spawn: [" + follower_class + "] without spawner present in level" );
	
		//spawn squad
		follower_count 	= 0;
		group 			= [];
		foreach( spawner in spawners )
		{
			wait 0.05; // spawn one per frame per spawner
			if( spawner.script_noteworthy == "leader" )
			{
				leader_spawner.script_noteworthy = "leader";
				leader_spawner.count = 1;
				leader_spawner.origin = spawner.origin;
				leader_spawner.angles = spawner.angles;
				guy = leader_spawner spawn_ai( true );
				group[ group.size ] = guy;
			}
			if( spawner.script_noteworthy == "follower" )
			{
				if ( follower_count >= follower_size )
					continue;
				follower_count++;
				
				follower_spawner.script_noteworthy = "follower";
				follower_spawner.count = 1;
				follower_spawner.origin = spawner.origin;
				follower_spawner.angles = spawner.angles;
				guy = follower_spawner spawn_ai( true );
				group[ group.size ] = guy;		
			}
		}
	}
	else
	{
		assertex( isspawner( spawners[ 0 ] ), "The spawners passed in for spawn arent spawner entities, is this custom spawning?" );
		
		follower_count 	= 0;
		group 			= [];
		foreach ( spawner in spawners )
		{
			if ( spawner.script_noteworthy == "follower" )
				follower_count++;

			if ( follower_count >= follower_size )
				continue;
				
			spawner.count = 1;
			guy = spawner spawn_ai( true );
			group[ group.size ] = guy;
		}
	}
	
	// all failed to spawn, maybe because was visible
	if ( !group.size )
		return undefined;
		
	// due to delay in spawning using same spawner, this guy might be dead before this point
	alive_group = [];
	foreach( guy in group )
	{
		guy.is_squad_enemy = true;
		if ( isalive( guy ) )
			alive_group[ alive_group.size ] = guy;
	}
	group = alive_group;
	
	// setup leader of the squad
	leader = undefined;
	foreach( guy in group )
	{
		if( guy.script_noteworthy == "leader" )
		{
			leader = guy;
			leader.back_occupied[ "left" ] = 0;
			leader.back_occupied[ "right" ] = 0;
				
			leader thread setup_leader( group );
		}
	}
	
	// the leader failed to spawn, maybe because was visible, but followers weren't, so pick new leader
	if ( group.size < spawners.size && !isdefined( leader ) )
	{
		leader = group[ randomint( group.size ) ];
		leader.script_noteworthy = "leader";
		leader thread setup_leader( group );
	}

	assert( isdefined( leader ) );
	
	// setup followers for leader
	foreach( guy in group )
	{
		if( isdefined( level.squad_drop_weapon_rate ) )
		{
			drop_chance = randomfloat( 1 );
			if( drop_chance > level.squad_drop_weapon_rate )
				guy.DropWeapon = false;
		}
			
		if( guy.script_noteworthy == "follower" )
			guy thread setup_follower( leader );
	}
	
	return group; // no use
}


setup_leader( group )
{
	level endon( "squad_disband" );
	
	self notify( "new_leader" );
	self endon( "new_leader" );
	self endon( "demotion" );
	
	// reset
	self.squadmembers = [];
	self.leader = undefined;	
	
	// clean up group
	foreach( guy in group )
		if( !isalive( guy ) )
			group array_remove( group, guy );
	
	// ===============================================
	// ==== legacy script: so the old levels work ====
	// ===============================================
	if ( !isdefined( level.new_squad_logic ) || level.new_squad_logic == false )
	{
		//check if im the last guy, follow someone else if we can
		if( group.size == 1 && level.leaders.size > 0 )
		{
			leader = level.leaders[0];
			if( level.leaders.size > 1 )
				leader = get_closest_living( self.origin, level.leaders );
			self setup_follower( leader );
			return;
		}
	}
	// ^=============================================^
	
	if ( !is_in_array( level.leaders, self ) )
		level.leaders[level.leaders.size] = self;
	
	if ( isdefined( level.squad_leader_behavior_func ) )
	{
		self thread [[ level.squad_leader_behavior_func ]]();
	}
	else
	{
		self.goalradius = CONST_SQUAD_LEADER_GOALRADIUS;
			
		//self.pathenemyfightdist = 1028;
		//self.pathenemylookahead = 1028;
		player = getclosest( self.origin, level.players );
		self.favoriteenemy = player;
		self setgoalentity( player );
		//self.moveplaybackrate = 1;
		self setengagementmindist( 300, 200 );
		self setengagementmaxdist( 512, 720 );
	}
	
	self thread wait_for_followers();
	self thread enlarge_follower_goalradius_upon_seeing_player();
	
	// ===============================================
	// ==== legacy script: so the old levels work ====
	// ===============================================
	if ( !isdefined( level.new_squad_logic ) || level.new_squad_logic == false )
	{
		self thread handle_all_followers_dying( group );
	}
	// ^=============================================^
	
	self waittill( "death" );
			
	// update leaders array
	new_leaders = [];
	foreach( leader in level.leaders )
	{
		if ( isdefined( leader ) && isalive( leader ) )
			new_leaders[ new_leaders.size ] = leader;
	}
	level.leaders = new_leaders;
	
	// find a follower and promote him to leader
	leader = undefined;
	foreach( guy in group )
	{
		if( isalive( guy ) )
		{
			if( !isdefined( leader ) )
			{
				leader = guy;
				guy notify( "promotion" );
				guy thread setup_leader( group );
			}
			else
			{
				guy thread setup_follower( leader );
			}
		}
	}	
}

enlarge_follower_goalradius_upon_seeing_player()
{
	level endon( "squad_disband" ); 
	
	self endon( "new_leader" );
	self endon( "demotion" );
	self endon( "death" );	
	
	self waittill( "enemy_visible" );
	
	if ( isdefined( self.squadmembers ) && self.squadmembers.size )
	{
		foreach( follower in self.squadmembers )
			follower notify( "leader_saw_player" );
	}
}


wait_for_followers()
{
	level endon( "squad_disband" );
	
	self endon( "new_leader" );
	self endon( "demotion" );
	self endon( "death" );
	
	old_rate = self.moveplaybackrate;
	while ( 1 )
	{
		wait 2;
		assertex( isdefined( self ), "Function called on dead or removed AI." );
		
		if ( isdefined( self.squadmembers ) && self.squadmembers.size )
		{
			guy = get_closest_living( self.origin, self.squadmembers );
			if ( isdefined( guy ) && distance( guy.origin, self.origin ) > 256 )
			{
				// If this function endon(s) this moveplaybackrate adjustment 
				// will be cleared. This happens when the AI is made a leader or a 
				// follower. In this tranistion the AI's behavior function is called 
				// which then calls the attributes function which then sets the AI
				// back to his default speed
				self.moveplaybackrate = 0.85 * old_rate;
			}
			else
			{
				self.moveplaybackrate = old_rate;
			}
		}
	}
}

// default setup_follower function
setup_follower( leader )
{
	level endon( "squad_disband" ); 
	
	// should only run one instance per follower
	self notify( "assigned_new_leader" );
	self endon( "assigned_new_leader" );
	self endon( "death" );
	self endon( "promotion" );
	
	// is not or no longer is leader
	self.squadmembers 	= undefined;
	self.leader 		= leader;
	
	self thread leader_follower_count( leader );
	
	assertex( isdefined( leader ), "setup follower to an undefined leader" );
	assertex( isalive( leader ), "setup follower to a dead leader" );
	
	// setup specops survival mode AI attributes
	if ( isdefined( level.attributes_func ) )
		self [[ level.attributes_func ]]();
	
	if ( isdefined( level.squad_follower_func ) )
		self [[level.squad_follower_func]]( leader );
	else
		self thread follow_leader_regular( leader );
}

// keeps track of the leader.squadmembers array
leader_follower_count( leader )
{
	level endon( "squad_disband" ); 
	
	self endon( "assigned_new_leader" );
	leader endon( "death" );
	
	leader.squadmembers[ leader.squadmembers.size ] = self;
	self waittill( "death" );
	
	if ( !isdefined( self.leader ) )
		return;
	
	// updated leader's squad member list
	if( isalive( self.leader ) && isdefined( self.leader.squadmembers ) && self.leader.squadmembers.size > 0 )
	{
		new_squadmembers = [];
		foreach( guy in leader.squadmembers )
		{
			if( isalive( guy ) )
				new_squadmembers[ new_squadmembers.size ] = guy;
		}
		leader.squadmembers = new_squadmembers;
	}
}

// different follower types and improved follower navigation logic
setup_follower_advanced( leader )
{
	// riotshield follow style
	if ( is_riotshield( leader ) )
	{
		leader.goalradius = 1300;
		position = undefined;

		if ( !leader.back_occupied[ "right" ] && !leader.back_occupied[ "left" ] )
		{
			if ( cointoss() )
				self follow_leader_riotshield( "left" );
			else
				self follow_leader_riotshield( "right" );
			return;
		}

		if ( leader.back_occupied[ "right" ] && leader.back_occupied[ "left" ] )
		{
			self follow_leader_regular();
			return;
		}

		if ( !leader.back_occupied[ "right" ] && leader.back_occupied[ "left" ] )
		{
			self follow_leader_riotshield( "right" );
			return;
		}

		if ( leader.back_occupied[ "right" ] && !leader.back_occupied[ "left" ] )
		{
			self follow_leader_riotshield( "left" );
			return;
		}
	}
	else
	{
		// regular leader follow style
		self follow_leader_regular();
	}
}

follow_leader_riotshield( position )
{
	level endon( "squad_disband" ); 
	
	self endon( "death" );
	self endon( "promotion" );
	
	// AI settings
	self.goalradius = 128;//64;
	self.pathenemyfightdist = 192;
	self.pathenemylookahead = 192;
	//self.moveplaybackrate = randomfloatrange( 1, 1.25 );
	self.favoriteenemy = undefined;
	self setengagementmindist( 300, 200 );
	self setengagementmaxdist( 512, 720 );
	
	self.leader.back_occupied[ position ] = 1;
	self.is_occupying = position;
	
	self thread setup_follower_goalradius_riotshield();
	
	while( 1 )
	{	
		follower_goal_pos = self.leader get_riotshield_back_pos( position, false );
		
		if ( !isdefined( follower_goal_pos ) )
		{
			// leader follow ////////////
			self follow_leader_regular();
			return;
		}

		old_org = self.leader.origin;
		wait 0.2;
		while ( isdefined( self.leader ) && isalive( self.leader ) && ( distance( self.leader.origin, old_org ) < 2 ) )
		{
			old_org = self.leader.origin;
			wait 0.2;
		}

		if( !isalive( self.leader ) || !isdefined( follower_goal_pos ) )
			self setgoalpos( self.origin );
		else
			self setgoalpos( follower_goal_pos );
	}		
}

follow_leader_regular()
{
	level endon( "squad_disband" ); 
	
	self endon( "death" );
	self endon( "promotion" );

	// AI settings
	self.goalradius = 128;//64;
	self.pathenemyfightdist = 192;
	self.pathenemylookahead = 192;
	//self.moveplaybackrate = randomfloatrange( 1, 1.25 );
	self.favoriteenemy = undefined;
	self setengagementmindist( 300, 200 );
	self setengagementmaxdist( 512, 720 );
	self thread setup_follower_goalradius();
	
	while( 1 )
	{
		wait .2;
		if( !isalive( self.leader ) )
			self setgoalpos( self.origin );
		else
			self setgoalpos( self.leader.origin );
	}

	/* // this might be too complicated for something not so different than natural AI behavior
	
	// AI settings
	self.goalradius = 128;//64;
	self.pathenemyfightdist = 192;
	self.pathenemylookahead = 192;
	self.moveplaybackrate = randomfloatrange( 1, 1.25 );
	self.favoriteenemy = undefined;
	self setengagementmindist( 300, 200 );
	self setengagementmaxdist( 512, 720 );
	
	self thread setup_follower_goalradius_big();
	
	while( 1 )
	{
		// follow_closely makes sure squad is in close formation before player sees it
		if ( isdefined( self.follow_closely ) && self.follow_closely )
		{
			wait .2;
			if( !isalive( self.leader ) )
				self setgoalpos( self.origin );
			else
				self setgoalpos( self.leader.origin );			
		}
		else
		{
			old_org = self.leader.origin;
			wait 2;
			
			// the distance check is to avoid followers updating position too often when leader is very active
			while ( isdefined( self.leader ) && isalive( self.leader ) && ( distance( self.leader.origin, old_org ) < 32 ) )
			{
				old_org = self.leader.origin;
				wait 2;
			}
			
			if( !isalive( self.leader ) )
			{
				self setgoalpos( self.origin );
			}
			else
			{
				aNodes = GetNodesInRadiusSorted( self.leader.origin, CONST_MAX_FOLLOW_DIST, 0, 80 );	
				//aNodes = get_array_of_closest( self.leader.origin, aNodes_unsorted, undefined, 16, CONST_MAX_FOLLOW_DIST, 64 );
				
				// if no nodes found (in case AI is climbing ladder), just follow leader
				if ( !isdefined( aNodes ) || aNodes.size < 1 )
				{
					self setgoalpos( self.leader.origin );
					continue;
				}
				
				lightest_node = aNodes[ 0 ];
				for( i=0; i<aNodes.size; i++ )
				{
					if ( !isdefined( aNodes[ i ].use_weight ) )
						aNodes[ i ].use_weight = 0;
						
					if ( lightest_node.use_weight > aNodes[ i ].use_weight )
						lightest_node = aNodes[ i ];
				}
				lightest_node.use_weight++;
				self setgoalnode( lightest_node );
			}
		}
	}
	*/
}


// (for an AI add_spawn_function) protector squad defends a place (script_struct) that it targets
// protector_obj_group = string name of the group
// obj_trig = when triggered the leader is freed from being binded in place

protector_leader_logic( protector_obj_group, obj_trig )
{
	level endon( "squad_disband" ); 
	
	self endon( "death" );
	
	self.back_occupied[ "left" ] = 0;
	self.back_occupied[ "right" ] = 0;
	self.protecting_obj = true;
	self.protector_obj_group = protector_obj_group;	

	goal_struct = getstruct( self.target, "targetname" );
	//bind in place, _squad_enemies.gsc fights this
	self bind_in_place( obj_trig, goal_struct.origin );
	
	obj_trig waittill( "trigger" );

	wait 5;
	
	self.protecting_obj = false;
	self.goalradius = 512;
	player = getclosest( self.origin, level.players );
	self.favoriteenemy = player;
	self setgoalentity( player );
}

// =================== follower following radius ==================

setup_follower_goalradius()
{
	self waittill_either( "enemy_visible", "leader_saw_player" );
	self.goalradius = CONST_FOLLOW_DIST;
	self.saw_player = true;
}


setup_follower_goalradius_riotshield()
{
	level endon( "squad_disband" ); 
	
	// self is follower
	self endon( "death" );
	self endon( "promotion" );
		
	self.goalradius = CONST_RIOTSHIELD_FOLLOW_RADIUS;
	self waittill( "goal" );

	trial_delay 	= 10;
	tries 			= 5;
	follow_duration = 120;
	
	while ( 1 )
	{
		cqb_walk( "on" );
		if ( isdefined( self.protecting_obj ) && self.protecting_obj )
		{
			wait 1;
			continue;
		}
		
		wait 30;
		self.goalradius = CONST_FOLLOW_DIST;
		cqb_walk( "off" );
		wait 20;
		self.goalradius = CONST_RIOTSHIELD_FOLLOW_RADIUS;
	}
	
	self.goalradius = CONST_FOLLOW_DIST;
	self.leader.back_occupied[ self.is_occupying ] = 0;
}

get_riotshield_back_pos( direction, facing_player )
{
	// self is riotshield guy
	if ( !isdefined( direction ) )
		return undefined;
		
	front_angle = undefined;

	if ( isdefined( facing_player ) && facing_player )
	{
		if ( isdefined( self.enemy ) && isplayer( self.enemy ) )
			front_angle = vectortoangles( self.enemy - self.origin );
		else
			return undefined;
	}
	else
	{
		front_angle = self.angles;
	}
	
	//thread draw_line_for_time( self.origin, self.origin + vector_multiply( vectornormalize( anglestoforward( front_angle ) ), CONST_RIOTSHIELD_FOLLOW_DIST ), 0, 1, 0, 0.2 );

	if ( direction == "left" )
		back_angle = ( front_angle[0], front_angle[1]-CONST_RIOTSHIELD_FOLLOW_ANGLE, front_angle[2] );
	else
		back_angle = ( front_angle[0], front_angle[1]+CONST_RIOTSHIELD_FOLLOW_ANGLE, front_angle[2] );

	pos_vector = ( VectorNormalize( AnglesToForward( back_angle ) ) * CONST_RIOTSHIELD_FOLLOW_DIST ); // its really 45.5

	//thread draw_line_for_time( self.origin, self.origin + pos_vector, 1, 0, 0, 0.2 );
	//thread draw_line_for_time( self.origin + pos_vector, self.origin + pos_vector + ( 0, 0, 10 ), 0, 1, 1, 0.2 );
	
	return self.origin + pos_vector;
}

bind_in_place( obj_trig, org )
{
	level endon( "squad_disband" ); 
	
	obj_trig endon( "trigger" );
	self endon( "death" );
	
	while ( 1 )
	{
		self.goalradius = 8;
		self setgoalpos( org );
		wait 0.05;
	}	
}

one_direction_trigger()
{
	// self is trig
	self endon ( "trigger" );
	
	disable_trigger = getent( self.target, "targetname" );
	disable_trigger waittill( "trigger" );
	self trigger_off();
}

is_leader_riotshield( follower )
{
	return ( isdefined( follower.leader ) && follower.leader.classname == "actor_enemy_afghan_riotshield" );
}

is_riotshield( leader )
{
	if ( leader.classname == "actor_enemy_afghan_riotshield" )
		return true;

	//if ( leader.classname == "a new riotshield type" )
	//	return true;
		
	return false;
}


handle_all_followers_dying( group )
{
	level endon( "squad_disband" ); 
	self endon( "death" );
	
	while( 1 )
	{
		wait 1;
		
		survivors = 0;
		foreach( guy in group )
			if( isalive( guy ) )
				survivors++;
		if( ( survivors == 1 ) && ( level.leaders.size > 1 ) )
		{
			level.leaders = array_remove( level.leaders, self );
			leader = level.leaders[0];
			if( level.leaders.size > 1 )
				leader = get_closest_living( self.origin, level.leaders );
			self thread setup_follower( leader );
			self notify( "demotion" );
			return;
		}
	}
}

/*
handle_followers_dying( group )
{
	self endon( "death" );
	original_group_size = group.size;
	
	while( 1 )
	{
		wait 1;
		
		survivors = 0;
		foreach( guy in group )
			if( isalive( guy ) )
				survivors++;		
		
		if ( level.leaders.size < 2 )
			continue;

		if( survivors < original_group_size )
		{
			leaders = array_remove( level.leaders, self );
			smallest = leaders[ 0 ];
			foreach ( leader in leaders )
			{
				if ( smallest.squadmembers.size > leader.squadmembers.size )
					smallest = leader;	
			}
			
			merge_size = survivors + smallest.squadmembers.size;
			if ( merge_size =< CONST_MERGE_SQUAD_MEMBER_MAX )
			{
				// merge
				level.leaders = array_remove( level.leaders, self );
				foreach ( guy in group )
				{
					if ( isalive( guy ) )
					{
						guy thread setup_follower( smallest );
						
						if ( guy == self )
							guy notify( "demotion" );
					
					}
				}
				return;
			}
		}
	}
}
*/

drawLeader()
{
	if( getdvar( "squad_debug" ) == "" || getdvar( "squad_debug" ) == "0" )
		return;
	
	color = ( 1, 1, 1 );

	while ( 1 )
	{
		foreach( leader in level.leaders )
		{
			if( isalive( leader ) && isdefined( leader.squadmembers ) )
			{
				Print3d( leader.origin + (0,0,70), "leader["+(leader.squadmembers.size+1)+"]", color, 1, 2 );
				foreach( guy in leader.squadmembers )
				{
					if ( isdefined( guy ) && isalive( guy ) )
						line( leader.origin, guy.origin, ( 0.5, 0.5, 1 ), 1 );
				}
			}
		}
		wait( 0.05 );
	}
}

draw_debug_marker( loc, color )
{
	if( getdvar( "squad_debug" ) == "" || getdvar( "squad_debug" ) == "0" )
		return;
		
	counter = 0;
	while ( counter < 40 )
	{
		Print3d( loc + (0,0,70), "X", color, 1, 8 );
		wait ( 0.05 );
		counter++;
	}
}


drawFollowers()
{
	if( getdvar( "squad_debug" ) == "" || getdvar( "squad_debug" ) == "0" )
		return;

	while( 1 )
	{
		all_ai = getaiarray();
		foreach ( guy in all_ai )
		{
			if( isdefined( guy.leader ) )
				thread draw_line_for_time( guy.origin, guy.leader.origin, 0.5, 0.5, 1, 0.1 );
		}
		wait 0.1;
	}
}
