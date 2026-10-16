#include maps\_utility;
#include common_scripts\utility;
#include maps\_hud_util;
#include maps\_remotemissile;

setup_remote_missile_target()
{
	if ( !isdefined( level.remote_missile_targets ) )
		level.remote_missile_targets = [];

	level.remote_missile_targets[ self.unique_id ] = self;

	if ( IsDefined( level.uav_struct.draw_red_boxes ) && !isdefined( level.uav_is_destroyed ) )
	{
		level endon( "draw_target_end" );
		while(isdefined(level.setup_remote_missile_target_last_add_time) && level.setup_remote_missile_target_last_add_time == GetTime())
		{
			wait(0.05);
		}
		
		level.setup_remote_missile_target_last_add_time = GetTime();
		
		if( isAlive( self ) )
			self draw_target();
	}

	self waittill( "death" );

	level.remote_missile_targets[ self.unique_id ] = undefined;

	if ( !isdefined( self ) )
		return;

	if ( IsDefined( self.has_target_shader ) )
	{
		self.has_target_shader = undefined;
		Target_Remove( self );
	}

}

player_uav_rig()
{
	AssertEx( IsPlayer( self ), "Only player entities can be Self of player_uav_rig" );

	if ( IsDefined( level.uavRig ) )
		return level.uavRig;

	
	AssertEx( IsDefined( self.uav_rigs ), "No player rig is defined." );
	
	rig = get_current_uav_rig();
	AssertEx( IsDefined( rig ), "No level.uav_player_rigs defined for player with unique_id " + self.unique_id );

	return rig;
}


create_uav_rigs( rig_function )
{
	assert( self.code_classname == "script_vehicle", "Tried to create a uav rig on a non vehicle." );
//	Assert( !isdefined( level.uavRig ), "Tried to create uav rigs but level.uavRig already exists. Pick one or the other." );
//	Assert( !isdefined( level.uav_player_rigs ), "Tried to create uav rigs but level.uav_player_rigs already exists." );

	foreach ( player in level.players )
	{
		rig = spawn_tag_origin();
		rig.origin = self.origin;
		rig.uav = self;
		rig thread run_rig_function_when_player_uses_UAV( rig_function, player );

		player add_player_rig( rig );
		player thread cycle_uav_rigs();
	}
}

add_player_rig( rig )
{
	assertex( isplayer( self ), "Not a player" );
	
	if ( !isdefined( self.uav_rigs ) )
	{
		self.uav_rigs = [];
	}
	
	self.uav_rigs[ self.uav_rigs.size ] = rig;
}


give_player_remote_missiles()
{
	assertex( isplayer( self ), "Can't give missiles to this entity." );
	
	self giveWeapon( "remote_missile_detonator" );
	self.remotemissile_actionslot = 4;
	self thread remotemissile_with_autoreloading();
	
	flag_clear( "predator_missile_launch_allowed" );
	self SetActionSlot( self.remotemissile_actionslot, "weapon", "remote_missile_detonator" );
}


remotemissile_reload()
{
	level endon( "stop_uav_reload" );
	level endon( "special_op_terminated" );

	// Wait for reload
	if ( flag( "uav_reloading" ) )
	{
		if ( IsDefined( level.uav_is_destroyed ) )
		{
			return;
		}

		remove_uav_weapon();

		if ( flag( "uav_collecting_stats" ) )
		{
			level waittill( "uav_collecting_stats" );
			play_kills_dialogue();
		}

		if ( IsDefined( level.uav_is_destroyed ) )
		{
			return;
		}

		// Make uav_user undefined so missile_kill_ai returns immediately.
		level.uav_user = undefined;

		//z: dont want to hear hellfire off line after each shot
		// Only do the dialogue if we have enough time between reloads.
		//if ( level.min_time_between_uav_launches > 5000 )
		//{
		//	thread remotemissile_offline( false );
		//}

		// Waiting for the flag_clear() notify
		if ( flag( "uav_reloading" ) )
		{
			level waittill( "uav_reloading" );
		}

		if ( IsDefined( level.uav_is_destroyed ) )
		{
			return;
		}

		if ( !flag( "uav_enabled" ) )
		{
			return;
		}

		if ( self GetWeaponAmmoClip( self.uav_weaponname ) < 1 )
		{
			disable_uav();
			return;
		}

		restore_uav_weapon();
		thread remotemissile_radio( "uav_online" );

		thread remotemissile_radio_reminder();
	}
}

remotemissile_with_autoreloading()
{
	remotemissile_player_input( ::remotemissile_reload );
}

remotemissile_no_autoreload()
{
	remotemissile_player_input();
}

remotemissile_move_player()
{
	return isdefined( level.remoteMissile_temp_move_player );
}