#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;
#include maps\_shg_common;
#include maps\_audio;
#include maps\_hud_util;

fake_death_over_time( type, min_wait, max_wait )
{
	self endon ( "death" );
	
	wait randomintrange ( min_wait, max_wait );
	if ( isdefined ( self ) && isai ( self ) && isalive ( self ) )
	{
		if ( type == "bullet" )
			self fake_death_bullet(); 
		else
			self fake_death_bullet(); // this will eventually get broken out into "bullet", "explosion" and maybe other types
	}
	
}

// fake death with bullet hit as cause
fake_death_bullet( delay )
{
	self endon( "death" );

	if( !IsSentient( self ) || !IsAlive( self ) )
	{
		return;
	}

	if( IsDefined( self.bloody_death ) && self.bloody_death )
	{
		return;
	}

	self.bloody_death = true;

	if( IsDefined( delay ) )
	{
		wait( RandomFloat( delay ) );
	}

	tags = [];
	tags[0] = "j_hip_le";
	tags[1] = "j_hip_ri";
	tags[2] = "j_head";
	tags[3] = "j_spine4";
	tags[4] = "j_elbow_le";
	tags[5] = "j_elbow_ri";
	tags[6] = "j_clavicle_le";
	tags[7] = "j_clavicle_ri";

	for( i = 0; i < 3 + RandomInt( 5 ); i++ )
	{
		random = RandomIntRange( 0, tags.size );
		//vec = self GetTagOrigin( tags[random] );
		self thread fake_death_bullet_fx( tags[random], undefined );
		wait( RandomFloat( 0.1 ) );
	}

	self DoDamage( self.health + 50, self.origin );
}

fake_death_bullet_fx( tag, fxName )
{
	if( !IsDefined( fxName ) )
	{
		fxName = level._effect["flesh_hit"];
	}

	PlayFxOnTag( fxName, self, tag );
}

array_setgoalvolume ( guys, volume )
{
	new_volume = getent ( volume, "targetname" );
	
	wait 0.05;
	
	foreach ( guy in guys )
	{
		if ( isdefined ( guy ) && isai ( guy ) )
		{
			guy cleargoalvolume();
			guy setgoalvolumeauto ( new_volume );
		}
	}
	
}

radio_dialogue_queue_single( line )
{
	conversation_start();
	radio_dialogue( line );
	conversation_stop();
}

dialogue_queue_single( line )
{
	conversation_start();
	self dialogue_queue( line );
	conversation_stop();
}

dialogue_random_line( line1, line2, line3, line4, line5, line6, line7, line8 )
{	
	
	lines = [];
	
	if ( isdefined ( line1 ) )
		lines [ lines.size ] = line1;
	if ( isdefined ( line2 ) )
		lines [ lines.size ] = line2;
	if ( isdefined ( line3 ) )
		lines [ lines.size ] = line3;
	if ( isdefined ( line4 ) )
		lines [ lines.size ] = line4;
	if ( isdefined ( line5 ) )
		lines [ lines.size ] = line5;
	if ( isdefined ( line6 ) )
		lines [ lines.size ] = line6;
	if ( isdefined ( line7 ) )
		lines [ lines.size ] = line7;
	if ( isdefined ( line8 ) )
		lines [ lines.size ] = line8;

	if ( !isdefined ( level.dialogue_random_last_line ) )
		level.dialogue_random_last_line = undefined;
	vo_line_good = false;
	
	while ( !vo_line_good )
	{
		line = random ( lines );
		
		if ( isdefined ( level.dialogue_random_last_line ) && level.dialogue_random_last_line == line )
			continue;
		else
		{
			if ( isdefined ( self ) && isai ( self ) )
				self dialogue_queue_single ( line );
			else
				radio_dialogue_queue_single ( line );
			level.dialogue_random_last_line = line;
			vo_line_good = true;
		}
		
		wait 0.05;
	}
	
	vo_line_good = false;
		
}
	
hint_neverbreak()
{
	return false;
}

setup_ignore_suppression_triggers()
{
	triggers = GetEntArray("trigger_ignore_suppression", "targetname");	
	foreach(trigger in triggers)
	{
		level thread ignore_suppression_trigger_think(trigger);	
	}
}


ignore_suppression_trigger_think(trigger)
{
	for(;;)
	{
		trigger waittill("trigger", other);
		if(IsDefined(other) &&  IsAI(other) && !other IsBadGuy())
		{
			other thread ignore_suppression_trigger_ai_think(trigger);	
		}		
	}	
}

ignore_suppression_trigger_ai_think(trigger)
{
	// self is the ai
	
	self notify("ignore_suppression_trigger_ai_think_stop");
	self endon("ignore_suppression_trigger_ai_think_stop");
	self endon("death");
	
	self set_ignoresuppression(true);
	
	while(self IsTouching(trigger))
	{
		wait .5;	
	}
	
	self set_ignoresuppression(false);
}

add_hint_background( double_line )
{
	if ( isdefined ( double_line ) )
		level.hintbackground = createIcon( "popmenu_bg", 650, 50 );
	else
		level.hintbackground = createIcon( "popmenu_bg", 650, 30 );
	level.hintbackground.hidewheninmenu = true;
	level.hintbackground setPoint( "TOP", undefined, 0, 110 );
	level.hintbackground.alpha = .5;
	level.hintbackground.sort = 0;
}

clear_hints()
{
	if ( isDefined( level.hintElem ) )
		level.hintElem destroyElem();
	if ( isDefined( level.iconElem ) )
		level.iconElem destroyElem();
	if ( isDefined( level.iconElem2 ) )
		level.iconElem2 destroyElem();
	if ( isDefined( level.iconElem3 ) )
		level.iconElem3 destroyElem();
	if ( isDefined( level.hintbackground ) )
		level.hintbackground destroyElem();
	level notify ( "clearing_hints" );
}


hint_with_background( text, timeOut, double_line )
{
	clear_hints();
	level endon ( "clearing_hints" );

	add_hint_background( double_line );
	level.hintElem = createFontString( "default", 2 );
	level.hintElem.hidewheninmenu = true;
	level.hintElem setPoint( "TOP", undefined, 0, 110 );
	level.hintElem.sort = 0.5;
	level.high_priority_hint = true;

	level.hintElem setText( text );
	//level.hintElem endon ( "death" );

	if ( isDefined( timeOut ) )
		wait ( timeOut );
	else
		return;

	level.high_priority_hint = undefined;
	level.hintElem fadeOverTime( 0.5 );
	level.hintElem.alpha = 0;
	wait ( 0.5 );

	clear_hints();
}


//===========================================
// 			dog_monitor_goal_ent
//===========================================
dog_monitor_goal_ent( goal_ent, exit_point )
{
	level 	endon( "special_op_terminated" );
	self 	endon( "death" );
	
	attackRangeBuffer = 30;
	meleeRange = self.meleeAttackDist + attackRangeBuffer;
	
	while( true )
	{
		wait( 0.05 );
		
		// player is in last stand
		if( self dog_enemy_laststand_check() )
		{
			continue;
		}
		
		// the dog has stopped moving but still has an enemy
		if( IsDefined( self.enemy ) && (self.movemode == "stop") )
		{
			// the dog is waiting on a timer to attack the player
			if( get_next_allow_melee_time( self ) > getTime() )
			{
				continue;
			}
			
			// the player is in a location where the dog can not reach
			self SetGoalEntity( exit_point );
			self set_ignoreall( true );
			
			continue;
		}
		
		// the dog has been told to retreat
		if( IsDefined( self.ignoreall ) && self.ignoreall )
		{
			nodes = GetNodesInRadiusSorted( self.favoriteenemy.origin, 16, 0, 64, "Path" );
		
			// attack the player when back on the path grid
			if( IsDefined( nodes ) && (nodes.size > 0) )
			{
				self SetGoalEntity( self.favoriteenemy );
				self set_ignoreall( false );
				continue;
			}
			
			// the dog is at the exit location
			if( is_coop() && Distance2D( self.origin, exit_point.origin ) < 125 )
			{
				coop_player = get_different_favoriteenemy();
				
				// the coop player can see the dog
				if( coop_player so_can_player_see_dog( self ) ) 
				{
					self dog_swap_enemy();
					self set_ignoreall( false );
				}
			}
		}	
	}
}


//===========================================
// 		   so_can_player_see_dog
//===========================================
so_can_player_see_dog( ai )
{
	playerEye = self GetEye();
	eyeOrigin = ai GetEye();
	
	if( SightTracePassed( playerEye, eyeOrigin, true, self, ai ) )
	{
		return true;
	}

	return false;
}


//===========================================
// 		   get_next_allow_melee_time
//===========================================
get_next_allow_melee_time( dog )
{
	time_since_last_melee = 0;
	
	if( isDefined( self.enemy.dogAttackAllowTime ) )
	{
		time_since_last_melee = self.enemy.dogAttackAllowTime + 2500;
	}
	
	return time_since_last_melee;
}


//===========================================
// 		   dog_enemy_laststand_check
//===========================================
dog_enemy_laststand_check()
{
	if( !is_coop() )
	{
		return false;
	}
	
	if( IsDefined( self.favoriteenemy.laststand ) && self.favoriteenemy.laststand )
	{
		self dog_swap_enemy();
		return true;
	}
	
	return false;
}


//===========================================
// 			   dog_swap_enemy
//===========================================
dog_swap_enemy()
{
	if( !is_coop() )
	{
		return;
	}

	new_enemy = self get_different_favoriteenemy();
	
	self SetGoalEntity( new_enemy );
	self set_favoriteenemy( new_enemy );
}


//===========================================
// 		 get_different_favoriteenemy
//===========================================
get_different_favoriteenemy()
{
	new_enemy_index = ( self.favoriteenemy != level.player2 );
	return level.players[ new_enemy_index ];
}