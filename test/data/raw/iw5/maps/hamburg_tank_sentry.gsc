#include maps\_utility;
#include common_scripts\utility;
#include maps\_vehicle;

sentry_target_drones( team, dotrange )
{
	self endon( "death" );
	
	self notify ( "stop_sentry_target_drones" );
	self endon ( "stop_sentry_target_drones" );
	
	waittillframeend; // lazy waiting for this flag
	if( flag_exist( "pause_sentry_turrets" ) )
		flag_wait ( "pause_sentry_turrets" );
		
	if ( !IsDefined( self.idle_target_always ) )
	{
		self.idle_target_always = spawn_tag_origin();
//		thread draw_line_from_ent_to_ent_until_notify( self, self.idle_target_always, 1, 0, 0, self, "death" );
//		self childthread show_my_target();
	}	
	self ClearTargetEntity();
	
	if ( !IsDefined( self.script_fireondrones ) )
		self.script_fireondrones = false;

	if ( team == "allies" )
		targetteam = "axis";
	else
		targetteam = "allies";
		
	while ( 1 )
	{
		
		self set_manual_target( self.idle_target_always, 0 );
		while( !drone_check( targetteam ) )
		{
			wait 0.05;
		}
			
		if ( !IsDefined( self.oldconvergencetime ) )
			self.oldconvergencetime = self.convergencetime;
			
		self.convergencetime = 4.5;

		turretowner = self GetTurretOwner();

		if ( !IsAlive( turretowner ) || IsPlayer( turretowner ) )
		{
			wait 0.05;
			continue;
		}
		else
			team = turretowner.team;
			

		while ( drone_check( targetteam ) )
		{
			lock( "sentry_drones" );

			if( !drone_check( targetteam) )
			{
				unlock( "sentry_drones" );
				self set_manual_target( self.idle_target_always, 0 );
				break;
			}
			
			target = get_bestdrone_sentry( targetteam );
			unlock( "sentry_drones" );
			
			if ( !IsDefined( self.script_fireondrones ) || !self.script_fireondrones )
			{
				wait 0.05;
				break;
			}
			
			if ( !IsDefined( target ) )
			{
				wait 0.05;
				self ClearTargetEntity();
				break;
			}
			self.idle_target_always.origin = target GetCentroid();
			//self thread draw_line_from_ent_to_ent_until_notify( self, target, 1, 1, 1, self, "hehaw" );
			self set_manual_target( target, 3, 5 );
			//target waittill ( "death" );
			//self notify( "hehaw" );

			if ( !( IsDefined( self GetTurretOwner() ) && self GetTurretOwner() == turretowner ) )
				break;
				
		}
		self.convergencetime = self.oldconvergencetime;
		self.oldconvergencetime = undefined;
		
		if ( level.drones[ targetteam ].lastindex )
			waitfornewdrone = false;
		else
			waitfornewdrone = true;
	}
}

show_my_target()
{
	self endon ( "death" );
	while( true )
	{
		target = self GetTurretTarget( false );
			
			
		if ( IsDefined( target ) )
		{
//			if( IsAI( target ) && isdefined( self.idle_target_always ) )
//			 self settargetentity( self.idle_target_always );
			if( IsAI( target ) )
				Line( self.origin , target.origin, (0,1,0) );
			else
				Line( self.origin , target.origin, (1,1,1) );
		}
		wait 0.05;
	}
}

drone_check( targetteam )
{
	if ( !IsDefined( level.drones ) )
		return false;
	return level.drones[ targetteam ].lastindex;
}

get_bestdrone_sentry( team )
{
	if ( level.drones[ team ].lastindex < 1 )
		return;
	ent = undefined;
	dotforward = AnglesToForward( self.angles );
	
	for ( i = 0; i < level.drones[ team ].lastindex; i++ )
	{
		
		// I'm being stupid and defensive here. TODO.find out why I am I able to get and undefined guy from here?
		if ( !IsDefined( level.drones[ team ].array[ i ] ) )
			continue;
			
		angles = VectorToAngles( level.drones[ team ].array[ i ].origin - self.origin );
		forward = AnglesToForward( angles );
			
		ent = level.drones[ team ].array[ i ];
		if ( !BulletTracePassedGoodEnoughForDroneTarget( self GetTagOrigin( "tag_flash" ), ent GetCentroid(), false, ent ) )
		{
			ent = undefined;
			continue;
		}
		break;
	}
	
	aitarget = self GetTurretTarget( true );
	if( !isdefined( self.prefers_drones ) )
	{
		if ( IsDefined( ent ) && IsDefined( aitarget ) && DistanceSquared( self.origin, aitarget.origin ) < DistanceSquared( self.origin, ent.origin ) )
			ent = undefined; // shoot at ai if they are closer
	}
	return ent;
}

BulletTracePassedGoodEnoughForDroneTarget( start, end, hit_characters, ignore_entity )
{
	return DistanceSquared( BulletTrace( start, end, hit_characters, ignore_entity )[ "position" ], end ) < 250000 ; // 500 units
}

// manually designate a target for the turret
// - fireTime_min: minimum amount of time to fire once the turret has centered on the target
// - fireTime_max (optional): if set, function will pick a random time between min and max
// - fireTime_message (optional): will fire until the turret is notified the message. will ignore min and max time.
set_manual_target( target, fireTime_min, fireTime_max, fireTime_message )
{
	AssertEx( IsDefined( target ), "undefined target passed to set_manual_target()." );
	self endon( "turret_cleanup" );
	if ( !IsDefined( fireTime_min ) && !IsDefined( fireTime_max ) )
	{
		fireTime_min = 1.5;
		fireTime_max = 3;
	}

	self custom_anim_wait();
	self SetTargetEntity( target );
	target endon ( "death" );
	self waittill( "turret_on_target" );

	if ( IsDefined( fireTime_message ) )
	{
		self waittill( fireTime_message );
	}
	else if ( IsDefined( fireTime_max ) )
	{
		wait( RandomFloatRange( fireTime_min, fireTime_max ) );
	}
	else
	{
		wait( fireTime_min );
	}

	self custom_anim_wait();
	self ClearTargetEntity( target );

}

custom_anim_wait()
{
	self endon( "death" );
	if ( !IsDefined( self.isCustomAnimating ) )
		return;

	while ( self.isCustomAnimating )
		wait( 0.05 );
}