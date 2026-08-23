#include maps\_utility;
#include common_scripts\utility;
#include maps\_vehicle;
#include maps\hamburg_tank_sentry;

LEVEL_RESUMESPEED = 5;
TURRET_FIRE_TIMER = 4500;
TURRET_FIRE_TIMER_RANDOM_PLUS = 1000;
TROOP_CACHE_UPDATE_INTERVAL = 400;
TROOP_ATTENTION_SPAN_WHILE_TANKS = 2000;

init_tank_ai_globals()
{
	create_lock( "hamburg_tank_ai_troop_trace" );
	create_lock( "hamburg_tank_ai_getNearestVectorOutsideRange" );
	create_lock( "hamburg_tank_ai_vistarget" );
	create_lock( "hamburg_tank_ai_troop_cache" );
	PreCacheRumble( "hamburg_tank_fire" );
}

init_tank_ai( skip_turret_attack )
{
 	self.target_min_range = 0;
	self.turret_damage_range = 500;
	self.turret_damage_max = 1400;
	self.turret_damage_min = 710;
	self.dontunloadonend = true;

	if ( !IsDefined( skip_turret_attack ) )
	{
		self thread turret_attack_think_hamburg();
	}
}

turret_attack_think_hamburg()
{
	self notify ( "stop_turret_attack_think_hamburg" );
	self endon ( "stop_turret_attack_think_hamburg" );
	
	if ( !IsDefined( level.tank_thought_next ) )
		level.tank_thought_next = 0;

	if ( !IsDefined ( self.script_turret ) )
		self.script_turret = true;
		
	if ( !IsDefined( self.script_attackai ) )
		self.script_attackai = true;
		
	if ( !IsDefined( level.tanks ) )
		level.tanks = [];

	if ( !ent_flag_exist( "stunned_tank" ) )
		ent_flag_init( "stunned_tank" );
		
	level.tanks = array_merge( level.tanks, [ self ] );
	self childthread remove_tank_on_death();
		
	self.badshot = false;
	self.attackback = true;
	self.shotsatzerospeed = 0;
	self.tank_queue = [];
	
	self.troop_cache = [];
	self.troop_cache_update_next = gettime();
	
	if ( !IsDefined( self.script_attackai ) )
		self.script_attackai = true;
	
	self.offsetone = 30;
	self.offsetzero = 430;

	self.offsetrange = self.offsetone - self.offsetzero;

	if ( !IsDefined( self.script_accuracy ) )
		self.script_accuracy = 0.44;
		

	if( self.script_team == "allies" )
		tank_mgs_target_drones();
	
	self.script_accuracy = clamp( self.script_accuracy, 0, 0.9999 );	

	
	if ( !IsDefined( self.waitingforgate ) )
		self.waitingforgate = false;
		
	self.accuracy = self.offsetzero +( self.offsetrange * self.script_accuracy );

	self endon ( "death" );
	
	self.shotcount = 2;
	shotattempts = 0;
	self.turretfiretimer = GetTime(); // ready to fire
	self.turretaccmins = 0.35; // precentag of accuracy.  tank will never fire with accuracy less than this.   To get a tank to be more accurate simply addust the script_accuracy on the nodes.
	self.turretaccmaxs = 1 - self.turretaccmins;
	
	self.shotsatzerospeed = 0;
	self.badshotcount = 0;
	
	if( self.script_team == "allies" )
		foreach( rider in self.riders )
			if( IsDefined( rider ) )
				rider.minigun_ignoreme = false;

	
	for ( ;; )
	{
		while( is_dummy() )
			wait 0.05;
			
		target = undefined;
		
		for ( ;; )
		{
			if ( !tank_queue_check() )
				break;
			if ( !allowedShoot() )
				break;
			if( is_dummy() )
				break;

			target = self acquire_target();

			if ( !IsDefined( target ) )
			{
				break;
			}
				
			self childthread turret_on_vistarget( target, "vehicle" );
			
			while ( allowedShoot() && !self.turretonvistarg && !self.badshot && IsAlive( target ) && !self.turretonvistarg_failed )
				wait 0.2;
				
			if ( self.badshot )
				break;
				
			if( killed_target( target ) )
				break;
				
			if( self.turretonvistarg_failed )
				break;
				
				
			self notify ( "novistarget" );
			self.turretonvistarg = false;
			
			if ( !allowedShoot() )
				break;
				
			while ( GetTime() < self.turretfiretimer && allowedshoot() && IsAlive( target ) )
				wait 0.05;
				
			wait 0.1;
			
			if ( !allowedShoot() )
				break;
				
			if( killed_target( target ) )
				break;
				
				
			tracepassed = true;
			while ( true )
			{
				lock( "hamburg_tank_ai_troop_trace" );
				
				tracepassed = confirm_target( target );
				
				unlock_wait( "hamburg_tank_ai_troop_trace" );
				if ( !( GetTime() < self.turretfiretimer && IsAlive( target ) && tracepassed ) )
					break;
			}
			if( !tracepassed )
				break;
				
			if( gettime() < level.tank_thought_next )
			{
				wait ( level.tank_thought_next - GetTime() ) / 1000;
				break;
			}
				
			if( is_dummy() )
				break;
				
			self ClearTurretTarget();
			
			if( isdefined( level.protect_player_on_fire ) )
				thread [[level.protect_player_on_fire]]();
			else
				self FireWeapon();
				
			tank_queue_all_enemies();	

			if ( self Vehicle_GetSpeed() == 0 )
				self.shotsatzerospeed++;
				
			if ( self.shotsatzerospeed > 9 )
				self.shotsatzerospeed = 9;

			update_turret_fire_timer();			
			shotattempts++;
				
			timer = GetTime() + 1000;
			while ( GetTime() < timer && allowedShoot() )
				wait 0.05;

			if ( !allowedShoot() )
				break;

			if ( shotattempts > self.shotcount )
			{
				shotattempts = 0;
				break;
			}
		}
		
		
		if ( !self.script_turret )
		{
			wait 0.1;
			continue;
		}
		if ( self.badshot )
		{
			wait 0.05;
			self.badshot = false;
		}
		self.shotsatzerospeed = 0;
		
		shotattempts = 0;
		
		if ( self.tank_queue.size )
			tank_queue_remove( self.tank_queue[ 0 ] );

		attack_troops();

		if ( ! self.tank_queue.size )
			tank_queue_all_enemies();

		turret_idle();
		
		wait 0.3;
	}
}

acquire_target()
{
	target = undefined;

	if ( self.target_min_range > 0 )
	{
		potential_targets = [];
		min_dist = self.target_min_range * self.target_min_range;
		foreach ( ent in self.tank_queue )
		{
			if ( DistanceSquared( self.origin, ent.origin ) < self.target_min_range )
			{
				potential_targets[ potential_targets.size ] = ent;
			}
		}

		if ( potential_targets.size > 0 )
		{
			potential_targets = SortByDistance( potential_targets, self.origin );
			target = potential_targets[ 0 ];
		}
	}
	else
	{
		target = self.tank_queue[ 0 ];
	}

	return target;
}

tank_mgs_target_drones()
{
	if ( !IsDefined( self.mgturret ) )
		return;
	turrets = array_removeundefined( self.mgturret );
	
	foreach( mg in turrets )
	{
		if ( IsDefined( mg.defaultonmode ) )
			mg.drones_targets_sets_to_default = true;
		mg.script_fireondrones = true;
		
		// consistent friendly tank mgturrets across difficulties.
		if( self.script_team == "axis" )
			assert();
			
		maps\_mgturret::mg42_setdifficulty( mg, "easy" );
		
		if( mg.model == "weapon_m1a1_minigun" )
			mg.secsOfFiringBeforeReloadDefault = 3;

		if( mg is_turret_type_ai_mounted() )
		{
			mg.prefers_drones = true;
			mg.anim_wait_func = animscripts\hummer_turret\common::custom_anim_wait;
			mg thread sentry_target_drones( self.script_team, -1 );
		}
		else
		{
			mg thread maps\_mgturret::mg42_target_drones( true, self.script_team, 0.88 );
		}
		
	}
}

is_turret_type_ai_mounted()
{
	switch( self.model )
	{
		case "weapon_m1a1_minigun":
		case "weapon_dshk_turret_t90":
			return true;
		default:
			return false;			
	}
	AssertMsg( "WTF!");
}

tank_mgs_stop_targeting_drones()
{
	foreach( mg in self.mgturret )
	{
		mg.script_fireondrones = false;
		mg notify ( "stop_mg42_target_drones");
	}
}

update_turret_fire_timer()
{
	self.turretfiretimer = GetTime() + TURRET_FIRE_TIMER + randomint( TURRET_FIRE_TIMER_RANDOM_PLUS );
}

killed_target( target )
{
	if ( !IsAlive( target ) )
	{
		tank_queue_remove_dead_and_undefined();
		return true;
	}
	return false;
}

should_attack_troops()
{
	if( !can_attack_troops() ) 
		return false;

	if ( self.tank_queue.size )	
		return false;
		
	return true;
}

can_attack_troops()
{
	if( !self.script_turret )
		return false;
	return self.script_attackai;
}

remove_tank_on_death()
{
	self waittill ( "death" );
	level.tanks = array_remove( level.tanks, self );
}

tank_queue_remove( target )
{
	if ( self.tank_queue.size == 0 )
		PrintLn( "self.tank_queue not defined in quermove before array remove" );
	self.tank_queue = array_remove( self.tank_queue, target );
}

tank_queue_remove_dead_and_undefined()
{
	self.tank_queue = array_removedead( self.tank_queue );
}

tank_queue_add( target )
{
	if ( !IsDefined( target ) )
		return;		
	if ( target.health > 0 )
		self.tank_queue = add_to_array_if_inot_inarray( self.tank_queue, target );
}

tank_queue_move_to_back( array, ent )
{
	newarray = [];
	count = 0;
	if ( array.size > 1 )
	{
		for ( i = 0;i < array.size;i++ )
		{
			if ( i!= 0 )
			{
				newarray[ count ] = array[ i ];
				count++;
			}
		}
		newarray[ count ] = array[ 0 ];
		return newarray;
	}
	else
	{
		return array;
	}
}

vismin = 1;
vismax = 4;

turret_on_vistarget( vistarget, type )
{
	self notify( "new_turret_on_vistarget" );
	self endon( "new_turret_on_vistarget" );
	self endon ( "death" );
	
	if ( !self.script_turret )
		return;
	
	self.turretonvistarg = false;	
	self.turretonvistarg_failed = false;	

	lock( "hamburg_tank_ai_vistarget" );
	
	if( !isdefined( vistarget ) )
	{
		unlock( "hamburg_tank_ai_vistarget" );
		return;
	}
	
	dist = Distance( self.origin, vistarget.origin );
	visibility = GetFXVisibility( self.origin, vistarget.origin );

	visrange = vismax - vismin;
	visibilitymod = vismin +( visrange - visibility * visrange );
	
	if ( self Vehicle_GetSpeed() < 1 && ( type == "troop" ) )
	{
		distacc = ( self.accuracy * ( 1 - 0.1 * self.shotsatzerospeed ) ) * visibilitymod * ( dist / 5000 );
	}
	else
	{
		self.shotsatzerospeed = 0;
		distacc = self.accuracy * visibilitymod * ( dist / 5000 );
	}

	randomacc = RandomFloat( distacc * self.turretaccmaxs ) +( distacc * self.turretaccmins );
	angletoenemy = flat_angle( VectorToAngles( vistarget.origin - self.origin ) );
	randrad = -20 + RandomInt( 220 );

	if ( type == "vehicle" )
		heightoffset = ( 0, 0, 78 );
	else
		heightoffset = ( 0, 0, 16 ); //try for splash damage
		
	randomthreesixtyangle = angletoenemy +( randrad, 90, 0 );

	offset = AnglesToForward( randomthreesixtyangle ) * randomacc;
	
	trace = BulletTrace( self GetTagOrigin( "tag_barrel" ), vistarget.origin + offset + heightoffset, type == "troop", self );
	offset = trace[ "position" ] -vistarget.origin;		

	/#
	if ( GetDvarInt( "debug_vehicleturretaccuracy" ) )
	{
		
		hangtime = 2;
		circleres = 32;
		hemires = circleres / 2;
		circleinc = 360 / circleres;
		circleres++;
		plotpoints = [];
		rad = 0;

		plotpoints = [];
		rad = 0.000;

		for ( i = 0;i < circleres;i++ )
		{
			plotpoints[ plotpoints.size ] = vistarget.origin + heightoffset + ( AnglesToForward( ( angletoenemy +( rad, 90, 0 ) ) ) * distacc );
			rad += circleinc;
		}
		plot_Points( plotpoints, 0, 1, 0, hangtime );

		plotpoints = [];
		
		rad = 0.000;
		for ( i = 0;i < circleres;i++ )
		{
			plotpoints[ plotpoints.size ] = vistarget.origin + heightoffset + ( AnglesToForward( ( angletoenemy +( rad, 90, 0 ) ) ) * distacc * self.turretaccmins );
			rad += circleinc;
		}
		plot_points( plotpoints, 1, 1, 0, hangtime );
		thread draw_line_for_time( self GetTagOrigin( "tag_barrel" ), vistarget.origin + offset, 1, 0, 0, hangtime );
	}
	#/		
	
	
	if ( Distance( trace[ "position" ], vistarget.origin + heightoffset ) / distacc > 1.5 &&
	 ( !IsDefined( trace[ "entity" ] ) || trace[ "entity" ] != vistarget ) && vistarget != level.player )
	{
		self.badshotcount++;
		if ( self.badshotcount > 5 )
		{
			if ( type == "vehicle" )
				self.tank_queue = tank_queue_move_to_back( self.tank_queue, vistarget );
			self.badshotcount = 0;
		}
		
		//thread draw_line_for_time( self GetTagOrigin( "tag_flash" ), vistarget.origin + offset + heightoffset, 0, 0, 1, 2 );
		unlock( "hamburg_tank_ai_vistarget" );
		wait 0.05;
		self.badshot = true;
		return;
	}
	else
		self.badshotcount = 0;
	
	// quick hack to keep aim from happening 
	if( ! extra_trace_from_commander_view( vistarget ) )
	{
		self.turretonvistarg_failed = true;	
		unlock( "hamburg_tank_ai_vistarget" );
		return;
	}
	
	//thread draw_line_for_time( self GetTagOrigin( "tag_flash" ), vistarget.origin + offset + heightoffset, 0, 0, 1, 2 );
	
	unlock( "hamburg_tank_ai_vistarget" );
	
	self SetTurretTargetEnt( vistarget, offset );
		
	self.turretonvistarg = false;	
	self endon ( "weapon_fired" );
	self endon ( "novistarget" );
	self waittill ( "turret_on_target" );
	self.turretonvistarg = true;
}

extra_trace_from_commander_view( vistarget )
{
	start = self GetCentroid() + ( 0, 0, 100 );

	end = vistarget GetCentroid();
	
	targeting_an_ai = IsAI( vistarget );
	if ( targeting_an_ai )
		end = vistarget GetEye();
	else if( vistarget.code_classname == "script_vehicle" )
		end = vistarget GetTagOrigin( "tag_body" );
	
	trace = BulletTrace( start, end, targeting_an_ai, self );

	success = true;
	
	if( vistarget != level.player )
		if ( !IsDefined( trace[ "entity" ] ) )
			success = false;
		else if ( trace[ "entity" ] != vistarget )
			success = false;
		
	if ( !success && targeting_an_ai )
	{
		if ( DistanceSquared( trace[ "position" ], end ) < 90000 ) //300*300
			success = true;
	}

//	if( success )
//		thread draw_line_for_time( start, end, 0, 1, 1, 1 );
//	else
//		thread draw_line_for_time( start, end, 1, 0, 0, 1 );
		
	return success;
}

add_to_array_if_inot_inarray( array, ent )
{
	doadd = 1;
	for ( i = 0;i < array.size;i++ )
	{
		if ( ( IsDefined ( array[ i ] ) ) && ( array[ i ] == ent ) )
			doadd = 0;
	}
	if ( doadd == 1 )
		array = add_to_array ( array, ent );
	return array;
}

turret_idle()
{
	if( isdefined( self.script_turret ) )
		if ( !self.script_turret )
			return;
		
	if( tank_queue_check() )
		return;
		
	self ClearTurretTarget();

	vect = (0,0,0);
	if ( IsDefined( self.default_target_vec ) )
		vect = self.default_target_vec;
	else
		vect = ( 0, 0, 32 ) + self.origin + ( AnglesToForward( self.angles ) * 3000 );
		
	targetangles = VectorToAngles( vect - self.origin );	
	tag_angles = self GetTagAngles( "tag_turret" );
	diff = tag_angles[ 1 ] - targetangles[ 1 ];
	diff = abs( AngleClamp180( diff ) );

	if ( diff < 10 )
		return;
	
	self SetTurretTargetVec( vect );
}

turret_reset()
{
	vect = ( 0, 0, 32 ) + self.origin + ( AnglesToForward( self.angles ) * 3000 );
	self SetTurretTargetVec( vect );
	self waittill( "turret_on_target" );
	self ClearTurretTarget();
}

get_troops()
{
	if( gettime() < self.troop_cache_update_next )
		return self.troop_cache;
	
	if ( self.script_team == "axis" )
	{
		troops = get_troops_from_team( "allies" );
		troops = array_insert( troops, level.player, 0 );
	}
	else if ( self.script_team == "allies" )
	{
		troops = get_troops_from_team( "axis" );
	}
	else
	{
		troops = [];
	}
	self.troop_cache = troops;
	self.troop_cache_update_next = gettime() + TROOP_CACHE_UPDATE_INTERVAL;
	return troops;
}

get_troops_from_team( team )
{
	lock( "hamburg_tank_ai_troop_cache" );
	troops = array_reverse( SortByDistance( GetAIArray( team ), self.origin  ) );
	drones = SortByDistance( level.drones[ team ].array, self.origin );
	troops = array_combine( level.drones[ team ].array, troops  );
	troops = filter_troops_in_range( troops );
	unlock( "hamburg_tank_ai_troop_cache" );
	return troops;
}

filter_troops_in_range( troops )
{
	if ( IsDefined( self.target_min_range ) && self.target_min_range > 0 )
	{
		min_dist = self.target_min_range * self.target_min_range;
		new_troops = [];
		foreach ( troop in troops )
		{
			if ( DistanceSquared( self.origin, troop.origin ) > min_dist )
			{
				new_troops[ new_troops.size ] = troop;
			}
		}
		troops = new_troops;
	}
	return troops;
}

attack_troops()
{
	self endon ( "death" );
	self endon ( "attack" );
	self endon ( "attacking origins" );
	self.turretonvistarg = false;
	nearrange = 650;
	maxshots = 3;
	failedguy = [];
	failedcount = 0;
	
	troopattention_span = gettime() + TROOP_ATTENTION_SPAN_WHILE_TANKS;
	
	while ( should_attack_troops() )
	{
		
		if( gettime() > troopattention_span && getallenemies().size )
		{
			wait 0.05;
			return;
		}

		troops = undefined;
		troops = get_troops();

		if ( !IsDefined( troops ) )
			break;
			
		fullarray = troops;
		for ( i = 0;i < failedguy.size;i++ )
		{
			troops = array_remove( troops, failedguy[ i ] );
		}
		if ( !troops.size )
		{
			troops = fullarray;
			failedguy = []; //reset failed guy queue start over.  Everybody has failed at this point
			return;
		}
		
		forwardvec = AnglesToForward( self GetTagAngles( "tag_barrel" ) );
		target = getNearestVectorOutsideRange( self GetTagOrigin( "tag_flash" ), forwardvec, troops, nearrange );
		
		if ( !IsDefined( target ) )
		{
			wait 0.05;
			failedguy = [];
			tank_queue_all_enemies();
			continue;
		}
		
		if ( !self.script_turret || !self.script_attackai )
			return;
		shotsfired = 0;

		while ( IsAlive( target ) && Distance( self.origin, target.origin ) > nearrange && shotsfired < maxshots )
		{
			self notify ( "novistarget" );
			
			self childthread turret_on_vistarget( target, "troop" );
			while ( !self.turretonvistarg && !self.badshot && should_attack_troops() && IsAlive( target )  && !self.turretonvistarg_failed )
			{
				wait 0.05;
				if ( !should_attack_troops() )
					return;	
			}

			if ( !should_attack_troops() )
				return;	
			
			if ( self.badshot )
			{
				wait 0.05;
				self.badshot = false;
				break;
			}
			
			if( self.turretonvistarg_failed )
				break;
			
			
			tracepassed = true;
			while ( true )
			{
				lock( "hamburg_tank_ai_troop_trace" );
				
				tracepassed = confirm_target( target );
				
				unlock_wait( "hamburg_tank_ai_troop_trace" );
				if ( !( GetTime() < self.turretfiretimer && IsAlive( target ) && tracepassed ) )
					break;
			}
			if ( !( tracepassed ) || !IsAlive( target ) )
			{
				wait 0.05;
				break;
			}
			self ClearTurretTarget();
			
			if( isdefined( level.protect_player_on_fire ) )
				thread [[level.protect_player_on_fire]]();
			else
				self FireWeapon();
			level notify ( "swing", self );

			
			failedcount = 0;
			shotsfired++;
			update_turret_fire_timer();			
		}
		if ( failedcount > 2 )
		{
			wait 0.1;
			tank_queue_all_enemies();
			failedcount = 0;
		}
		
		shotsfired = 0;
		
		if ( !self.script_turret || !self.script_attackai )
			return;
			
		self notify ( "novistarget" );
	
		if ( IsAlive( target ) )
		{
			failedguy[ failedguy.size ] = target;
			failedcount++;			
		}
		
		wait 0.1;
	}
}

confirm_target( target )
{
	if ( !IsAlive( target ) )
		return false;
		
	start = self GetTagOrigin( "tag_flash" );
	distance_to_target = Distance( start, target.origin );
	
	end = start + ( distance_to_target * ( VectorNormalize( AnglesToForward( self GetTagAngles( "tag_flash" ) ) ) ) );
	
	trace = BulletTrace( start, end , false, target );
	
	if( isdefined( trace[ "entity" ] ) )
	{
		trace_ent = trace[ "entity" ];
		if( isdefined( trace_ent.script_team ) && trace_ent.script_team == self.script_team )
			return false;		
	}
	
	if( DistanceSquared( trace[ "position" ], target.origin ) > 1000000 )
		return false; 
	
	// Putting this because sometimes the tanks don't kill the last tank because the troops get too close to it.
	// kind of hacky but it will ensure that all enemy tanks get blown up 
	// - Carlos
	if ( !flag( "player_ready_for_minigun_death" ) || flag( "player_in_tank" ) )
	{
		if( troops_to_close( trace[ "position" ] ) )
			return false;
	}
	
	return true;
}

troops_to_close( position )
{
	if( self.script_team == "axis" )
		return false; // enemies don't care, for performance of this.
		
	troops = GetAIArray( "allies" );
	
	foreach( troop in troops )
		if( DistanceSquared( troop.origin, position )  < 250000 )
			return true;
			
	return false;
}

getNearestVectorOutsideRange( org, forwardvec, array, range )
{
	theone = undefined;
	if ( array.size < 1 )
		return;
		rangeontheone = 0;
	ent = undefined;
	highestvectordot = -1;
	
	foreach( guy in array )
	{
		if ( !IsAlive( guy ) )
			continue; // lock creates window of death.

		lock( "hamburg_tank_ai_getNearestVectorOutsideRange" );

		if ( !IsAlive( guy ) )
		{
			unlock( "hamburg_tank_ai_getNearestVectorOutsideRange" );
			continue; // lock creates window of death.
		}

		trace = BulletTrace( org, guy.origin +( 0, 0, 48 ), true, self );
		unlock( "hamburg_tank_ai_getNearestVectorOutsideRange" );
		
		if ( trace[ "fraction" ]   < 0.7 )
			continue;
		newdist = Distance( guy.origin, org );
		if ( newdist < range )
			continue;
			
		targetvec = VectorNormalize( guy.origin - org );
		vectordotnumber = VectorDot( targetvec, forwardvec );
		if ( vectordotnumber > highestvectordot )
		{
			theone = guy;
			rangeontheone = newdist;
			highestvectordot = vectordotnumber;
		}
			
	}
	return theone;
}

tank_queue_all_enemies()
{
	tanks = array_randomize( getallenemies() );
	foreach ( tank in tanks )
		tank_queue_add( tank );
}

getallenemies()
{
	tanks = [];
	foreach ( tank in level.tanks )
	{
		if ( !IsDefined( tank ) )
			continue;
		if ( tank.script_team != self.script_team )
			tanks[ tanks.size ] = tank;
	}
	return tanks;
}

allowedShoot( target )
{
	if ( !self.script_turret )
		return false;
	ent_flag_waitopen( "stunned_tank" );		
	if ( !tank_queue_check() )
		return false;
	target = self.tank_queue[ 0 ];
	if ( !IsAlive( target ) )
		return false;
	if ( target.health <= 0 )
		return false;
	return true;
}

tank_queue_check()
{
	if ( self.tank_queue.size > 0 )
	{
		return true;
	}
	return false;
}

stop_turret_attack_think_hamburg()
{
	self notify ("stop_turret_attack_think_hamburg" );
	self ClearTurretTarget();
}

pause_all_tanks()
{
	level.paused_tanks = level.tanks;
	foreach( tank in level.tanks )
	{
		tank stop_turret_attack_think_hamburg();
	}
}

unpause_all_tanks()
{
	Assert( IsDefined( level.paused_tanks ) );
	foreach( tank in level.paused_tanks )
	{
		tank thread turret_attack_think_hamburg();
	}
	level.paused_tanks = undefined;
	
}
