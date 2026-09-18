#include animscripts\Utility;
#include common_scripts\Utility;

#using_animtree( "generic_human" );


////////////////////////////////////////////
// Initialize anim sets
//
// anim.initAnimSet is used as a temporary buffer, because variables, including arrays, can't be passed by reference
// Set it up in each init_animset_* function and then store it in anim.animset.*
// This allows using helpers such as "set_animarray_stance_change" for different sets
////////////////////////////////////////////

init_anim_sets()
{
	anim.animsets = spawnstruct();
	anim.animsets.move = [];
	
	// combat stand
	init_animset_default_stand();
	init_animset_cqb_stand();
	init_animset_pistol_stand();
	init_animset_rpg_stand();
	init_animset_shotgun_stand();
	init_animset_heat_stand();
	
	// combat crouch
	init_animset_default_crouch();
	init_animset_rpg_crouch();
	init_animset_shotgun_crouch();	
	
	// combat prone
	init_animset_default_prone();
	
	// move
	init_animset_run_move();
	init_animset_walk_move();
	init_animset_cqb_move();
	init_animset_heat_run_move();
	
	init_moving_turn_animations();
}


init_animset_run_move()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "sprint" ] = %sprint_loop_distant;
	anim.initAnimSet[ "sprint_short" ] = %sprint1_loop;
	anim.initAnimSet[ "prone" ] = %prone_crawl;

	anim.initAnimSet[ "straight" ] = %run_lowready_F;
	
	anim.initAnimSet[ "move_f" ] = %walk_forward;
	anim.initAnimSet[ "move_l" ] = %walk_left;
	anim.initAnimSet[ "move_r" ] = %walk_right;
	anim.initAnimSet[ "move_b" ] = %walk_backward; //this looks too fast to be natural
	
	anim.initAnimSet[ "crouch" ] = %crouch_fastwalk_F;
	anim.initAnimSet[ "crouch_l" ] = %crouch_fastwalk_L;
	anim.initAnimSet[ "crouch_r" ] = %crouch_fastwalk_R;
	anim.initAnimSet[ "crouch_b" ] = %crouch_fastwalk_B;
	
	anim.initAnimSet[ "stairs_up" ] = %traverse_stair_run_01;
	anim.initAnimSet[ "stairs_down" ] = %traverse_stair_run_down;
	
	assert( !isdefined( anim.animsets.move[ "run" ] ) );
	anim.animsets.move[ "run" ] = anim.initAnimSet;	
}


init_animset_heat_run_move()
{
	assert( isdefined( anim.animsets.move[ "run" ] ) );
	anim.initAnimSet = anim.animsets.move[ "run" ];

	anim.initAnimSet[ "straight" ] = %heat_run_loop;
	
	assert( !isdefined( anim.animsets.move[ "heat_run" ] ) );
	anim.animsets.move[ "heat_run" ] = anim.initAnimSet;	
}


init_animset_walk_move()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "sprint" ] = %sprint_loop_distant;
	anim.initAnimSet[ "sprint_short" ] = %sprint1_loop;
	anim.initAnimSet[ "prone" ] = %prone_crawl;

	anim.initAnimSet[ "straight" ] = %walk_CQB_F;
	
	anim.initAnimSet[ "move_f" ] = %walk_CQB_F;
	anim.initAnimSet[ "move_l" ] = %walk_left;
	anim.initAnimSet[ "move_r" ] = %walk_right;
	anim.initAnimSet[ "move_b" ] = %walk_backward;
	
	anim.initAnimSet[ "crouch" ] = %crouch_fastwalk_F;
	anim.initAnimSet[ "crouch_l" ] = %crouch_fastwalk_L;
	anim.initAnimSet[ "crouch_r" ] = %crouch_fastwalk_R;
	anim.initAnimSet[ "crouch_b" ] = %crouch_fastwalk_B;	
	
	anim.initAnimSet[ "stairs_up" ] = %traverse_stair_run;
	anim.initAnimSet[ "stairs_down" ] = %traverse_stair_run_down_01;

	assert( !isdefined( anim.animsets.move[ "walk" ] ) );
	anim.animsets.move[ "walk" ] = anim.initAnimSet;	
}


init_animset_cqb_move()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "sprint" ] = %sprint_loop_distant;
	anim.initAnimSet[ "sprint_short" ] = %sprint1_loop;
	anim.initAnimSet[ "straight" ] = %run_CQB_F_search_v1;	// %run_CQB_F_search_v2
	
	anim.initAnimSet[ "move_f" ] = %walk_CQB_F;
	anim.initAnimSet[ "move_l" ] = %walk_left;
	anim.initAnimSet[ "move_r" ] = %walk_right;
	anim.initAnimSet[ "move_b" ] = %walk_backward;

	anim.initAnimSet[ "stairs_up" ] = %traverse_stair_run;
	anim.initAnimSet[ "stairs_down" ] = %traverse_stair_run_down_01;

	assert( !isdefined( anim.animsets.move[ "cqb" ] ) );
	anim.animsets.move[ "cqb" ] = anim.initAnimSet;	
}


init_animset_pistol_stand()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "add_aim_up" ] = %pistol_stand_aim_8_add;
	anim.initAnimSet[ "add_aim_down" ] = %pistol_stand_aim_2_add;
	anim.initAnimSet[ "add_aim_left" ] = %pistol_stand_aim_4_add;
	anim.initAnimSet[ "add_aim_right" ] = %pistol_stand_aim_6_add;
	anim.initAnimSet[ "straight_level" ] = %pistol_stand_aim_5;

	anim.initAnimSet[ "fire" ] = %pistol_stand_fire_A;
	anim.initAnimSet[ "single" ] = array( %pistol_stand_fire_A );

	anim.initAnimSet[ "reload" ] = array( %pistol_stand_reload_A );
	anim.initAnimSet[ "reload_crouchhide" ] = array();

	anim.initAnimSet[ "exposed_idle" ] = array( %exposed_idle_alert_v1, %exposed_idle_alert_v2, %exposed_idle_alert_v3 );

	set_animarray_standing_turns_pistol();

	anim.initAnimSet[ "add_turn_aim_up" ] = %pistol_stand_aim_8_alt;
	anim.initAnimSet[ "add_turn_aim_down" ] = %pistol_stand_aim_2_alt;
	anim.initAnimSet[ "add_turn_aim_left" ] = %pistol_stand_aim_4_alt;
	anim.initAnimSet[ "add_turn_aim_right" ] = %pistol_stand_aim_6_alt;
	
	assert( !isdefined( anim.animsets.pistolStand ) );
	anim.animsets.pistolStand = anim.initAnimSet;
}

init_animset_rpg_stand()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "add_aim_up" ] = %RPG_stand_aim_8;
	anim.initAnimSet[ "add_aim_down" ] = %RPG_stand_aim_2;
	anim.initAnimSet[ "add_aim_left" ] = %RPG_stand_aim_4;
	anim.initAnimSet[ "add_aim_right" ] = %RPG_stand_aim_6;
	anim.initAnimSet[ "straight_level" ] = %RPG_stand_aim_5;

	anim.initAnimSet[ "fire" ] = %RPG_stand_fire;
	anim.initAnimSet[ "single" ] = array( %exposed_shoot_semi1 );

	anim.initAnimSet[ "reload" ] = array( %RPG_stand_reload );
	anim.initAnimSet[ "reload_crouchhide" ] = array();

	anim.initAnimSet[ "exposed_idle" ] = array( %RPG_stand_idle );

	set_animarray_stance_change();
	set_animarray_standing_turns();
	set_animarray_add_turn_aims_stand();
	
	assert( !isdefined( anim.animsets.rpgStand ) );
	anim.animsets.rpgStand = anim.initAnimSet;
}

init_animset_shotgun_stand()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "add_aim_up" ] = %shotgun_aim_8;
	anim.initAnimSet[ "add_aim_down" ] = %shotgun_aim_2;
	anim.initAnimSet[ "add_aim_left" ] = %shotgun_aim_4;
	anim.initAnimSet[ "add_aim_right" ] = %shotgun_aim_6;
	anim.initAnimSet[ "straight_level" ] = %shotgun_aim_5;
	
	anim.initAnimSet[ "fire" ] = %exposed_shoot_auto_v3;
	anim.initAnimSet[ "single" ] = array( %shotgun_stand_fire_1A, %shotgun_stand_fire_1B );
	set_animarray_burst_and_semi_fire_stand();
	
	anim.initAnimSet[ "exposed_idle" ] = array( %exposed_idle_alert_v1, %exposed_idle_alert_v2, %exposed_idle_alert_v3 );

	anim.initAnimSet[ "reload" ] = array( %shotgun_stand_reload_A, %shotgun_stand_reload_B, %shotgun_stand_reload_C, %shotgun_stand_reload_C, %shotgun_stand_reload_C );// ( C is standing, want it more often )
	anim.initAnimSet[ "reload_crouchhide" ] = array( %shotgun_stand_reload_A, %shotgun_stand_reload_B );
	
	set_animarray_stance_change();
	set_animarray_standing_turns();
	set_animarray_add_turn_aims_stand();
	
	assert( !isdefined( anim.animsets.shotgunStand ) );
	anim.animsets.shotgunStand = anim.initAnimSet;
}

init_animset_cqb_stand()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "add_aim_up" ] = %CQB_stand_aim8;
	anim.initAnimSet[ "add_aim_down" ] = %CQB_stand_aim2;
	anim.initAnimSet[ "add_aim_left" ] = %CQB_stand_aim4;
	anim.initAnimSet[ "add_aim_right" ] = %CQB_stand_aim6;

	anim.initAnimSet[ "straight_level" ] = %CQB_stand_aim5;

	anim.initAnimSet[ "fire" ] = %exposed_shoot_auto_v3;
	anim.initAnimSet[ "single" ] = array( %exposed_shoot_semi1 );
	set_animarray_burst_and_semi_fire_stand();

	anim.initAnimSet[ "exposed_idle" ] = array( %exposed_idle_alert_v1, %exposed_idle_alert_v2, %exposed_idle_alert_v3 );

	anim.initAnimSet[ "reload" ] = array( %CQB_stand_reload_steady );
	anim.initAnimSet[ "reload_crouchhide" ] = array( %CQB_stand_reload_knee );
	
	set_animarray_stance_change();
	set_animarray_standing_turns();
	set_animarray_add_turn_aims_stand();
	
	assert( !isdefined( anim.animsets.cqbStand ) );
	anim.animsets.cqbStand = anim.initAnimSet;
}

init_animset_heat_stand()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "add_aim_up" ] = %heat_stand_aim_8;
	anim.initAnimSet[ "add_aim_down" ] = %heat_stand_aim_2;
	anim.initAnimSet[ "add_aim_left" ] = %heat_stand_aim_4;
	anim.initAnimSet[ "add_aim_right" ] = %heat_stand_aim_6;

	anim.initAnimSet[ "straight_level" ] = %heat_stand_aim_5;

	anim.initAnimSet[ "fire" ] = %heat_stand_fire_auto;
	anim.initAnimSet[ "single" ] = array( %heat_stand_fire_single );
	set_animarray_custom_burst_and_semi_fire_stand( %heat_stand_fire_burst );

	anim.initAnimSet[ "exposed_idle" ] = array( %heat_stand_idle, /*%heat_stand_twitchA, %heat_stand_twitchB, %heat_stand_twitchC,*/ %heat_stand_scanA, %heat_stand_scanB );
	//heat_stand_scanA
	//heat_stand_scanB
	
	anim.initAnimSet[ "reload" ] = array( %heat_exposed_reload );
	anim.initAnimSet[ "reload_crouchhide" ] = array();
	
	set_animarray_stance_change();

	anim.initAnimSet[ "turn_left_45" ] = %heat_stand_turn_L;
	anim.initAnimSet[ "turn_left_90" ] = %heat_stand_turn_L;
	anim.initAnimSet[ "turn_left_135" ] = %heat_stand_turn_180;
	anim.initAnimSet[ "turn_left_180" ] = %heat_stand_turn_180;
	anim.initAnimSet[ "turn_right_45" ] = %heat_stand_turn_R;
	anim.initAnimSet[ "turn_right_90" ] = %heat_stand_turn_R;
	anim.initAnimSet[ "turn_right_135" ] = %heat_stand_turn_180;
	anim.initAnimSet[ "turn_right_180" ] = %heat_stand_turn_180;

	set_animarray_add_turn_aims_stand();
	
	assert( !isdefined( anim.animsets.heatStand ) );
	anim.animsets.heatStand = anim.initAnimSet;
}

init_animset_default_stand()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "add_aim_up" ] = %exposed_aim_8;
	anim.initAnimSet[ "add_aim_down" ] = %exposed_aim_2;
	anim.initAnimSet[ "add_aim_left" ] = %exposed_aim_4;
	anim.initAnimSet[ "add_aim_right" ] = %exposed_aim_6;

	anim.initAnimSet[ "straight_level" ] = %exposed_aim_5;

	anim.initAnimSet[ "fire" ] = %exposed_shoot_auto_v3;
	anim.initAnimSet[ "single" ] = array( %exposed_shoot_semi1 );
	set_animarray_burst_and_semi_fire_stand();

	anim.initAnimSet[ "exposed_idle" ] = array( %exposed_idle_alert_v1, %exposed_idle_alert_v2, %exposed_idle_alert_v3 );
	anim.initAnimSet[ "exposed_grenade" ] = array( %exposed_grenadeThrowB, %exposed_grenadeThrowC );

	anim.initAnimSet[ "reload" ] = array( %exposed_reload );// %exposed_reloadb, %exposed_reloadc
	anim.initAnimSet[ "reload_crouchhide" ] = array( %exposed_reloadb );
	
	set_animarray_stance_change();
	set_animarray_standing_turns();
	set_animarray_add_turn_aims_stand();
	
	assert( !isdefined( anim.animsets.defaultStand ) );
	anim.animsets.defaultStand = anim.initAnimSet;
}


init_animset_default_crouch()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "add_aim_up" ] = %exposed_crouch_aim_8;
	anim.initAnimSet[ "add_aim_down" ] = %exposed_crouch_aim_2;
	anim.initAnimSet[ "add_aim_left" ] = %exposed_crouch_aim_4;
	anim.initAnimSet[ "add_aim_right" ] = %exposed_crouch_aim_6;
	anim.initAnimSet[ "straight_level" ] = %exposed_crouch_aim_5;

	anim.initAnimSet[ "fire" ] = %exposed_crouch_shoot_auto_v2;
	anim.initAnimSet[ "single" ] = array( %exposed_crouch_shoot_semi1 );
	set_animarray_burst_and_semi_fire_crouch();

	anim.initAnimSet[ "reload" ] = array( %exposed_crouch_reload );

	anim.initAnimSet[ "exposed_idle" ] = array( %exposed_crouch_idle_alert_v1, %exposed_crouch_idle_alert_v2, %exposed_crouch_idle_alert_v3 );
	
	set_animarray_stance_change();
	set_animarray_crouching_turns();
	set_animarray_add_turn_aims_crouch();	
	
	assert( !isdefined( anim.animsets.defaultCrouch ) );
	anim.animsets.defaultCrouch = anim.initAnimSet;
}	

init_animset_rpg_crouch()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "add_aim_up" ] = %RPG_crouch_aim_8;
	anim.initAnimSet[ "add_aim_down" ] = %RPG_crouch_aim_2;
	anim.initAnimSet[ "add_aim_left" ] = %RPG_crouch_aim_4;
	anim.initAnimSet[ "add_aim_right" ] = %RPG_crouch_aim_6;
	anim.initAnimSet[ "straight_level" ] = %RPG_crouch_aim_5;

	anim.initAnimSet[ "fire" ] = %RPG_crouch_fire;
	anim.initAnimSet[ "single" ] = array( %RPG_crouch_fire );

	anim.initAnimSet[ "reload" ] = array( %RPG_crouch_reload );

	anim.initAnimSet[ "exposed_idle" ] = array( %RPG_crouch_idle );
	
	set_animarray_stance_change();
	set_animarray_crouching_turns();
	set_animarray_add_turn_aims_crouch();	
	
	assert( !isdefined( anim.animsets.rpgCrouch ) );
	anim.animsets.rpgCrouch = anim.initAnimSet;
}	


init_animset_shotgun_crouch()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "add_aim_up" ] = %exposed_crouch_aim_8;
	anim.initAnimSet[ "add_aim_down" ] = %exposed_crouch_aim_2;
	anim.initAnimSet[ "add_aim_left" ] = %exposed_crouch_aim_4;
	anim.initAnimSet[ "add_aim_right" ] = %exposed_crouch_aim_6;
	anim.initAnimSet[ "straight_level" ] = %exposed_crouch_aim_5;

	anim.initAnimSet[ "fire" ] = %exposed_crouch_shoot_auto_v2;
	anim.initAnimSet[ "single" ] = array( %shotgun_crouch_fire );
	set_animarray_burst_and_semi_fire_crouch();

	anim.initAnimSet[ "reload" ] = array( %shotgun_crouch_reload );
	anim.initAnimSet[ "exposed_idle" ] = array( %exposed_crouch_idle_alert_v1, %exposed_crouch_idle_alert_v2, %exposed_crouch_idle_alert_v3 );

	set_animarray_stance_change();
	set_animarray_crouching_turns();
	set_animarray_add_turn_aims_crouch();	
	
	assert( !isdefined( anim.animsets.shotgunCrouch ) );
	anim.animsets.shotgunCrouch = anim.initAnimSet;
}	


init_animset_default_prone()
{
	anim.initAnimSet = [];
	anim.initAnimSet[ "add_aim_up" ] = %prone_aim_8_add;
	anim.initAnimSet[ "add_aim_down" ] = %prone_aim_2_add;
	anim.initAnimSet[ "add_aim_left" ] = %prone_aim_4_add;
	anim.initAnimSet[ "add_aim_right" ] = %prone_aim_6_add;

	anim.initAnimSet[ "straight_level" ] = %prone_aim_5;
	anim.initAnimSet[ "fire" ] = %prone_fire_1;

	anim.initAnimSet[ "single" ] = array( %prone_fire_1 );
	anim.initAnimSet[ "reload" ] = array( %prone_reload );

	anim.initAnimSet[ "burst2" ] = %prone_fire_burst;
	anim.initAnimSet[ "burst3" ] = %prone_fire_burst;
	anim.initAnimSet[ "burst4" ] = %prone_fire_burst;
	anim.initAnimSet[ "burst5" ] = %prone_fire_burst;
	anim.initAnimSet[ "burst6" ] = %prone_fire_burst;

	anim.initAnimSet[ "semi2" ] = %prone_fire_burst;
	anim.initAnimSet[ "semi3" ] = %prone_fire_burst;
	anim.initAnimSet[ "semi4" ] = %prone_fire_burst;
	anim.initAnimSet[ "semi5" ] = %prone_fire_burst;

	anim.initAnimSet[ "exposed_idle" ] = array( %exposed_crouch_idle_alert_v1, %exposed_crouch_idle_alert_v2, %exposed_crouch_idle_alert_v3 );

	set_animarray_stance_change();

	assert( !isdefined( anim.animsets.defaultProne ) );
	anim.animsets.defaultProne = anim.initAnimSet;
}


init_animset_complete_custom_stand( completeSet )
{
	self.combatStandAnims = completeSet;
}

init_animset_custom_stand( fireAnim, aimStraight, idleAnim, reloadAnim )
{
	assert( isdefined( anim.animsets ) && isdefined( anim.animsets.defaultStand ) );
	
	anim.initAnimSet = anim.animsets.defaultStand;

	if ( isdefined( aimStraight ) )
		anim.initAnimSet[ "straight_level" ] = aimStraight;
	
	if ( isdefined( fireAnim ) )
	{
		anim.initAnimSet[ "fire" ] = fireAnim;
		anim.initAnimSet[ "single" ] = array( fireAnim );
		set_animarray_custom_burst_and_semi_fire_stand( fireAnim );
	}

	if ( isdefined( idleAnim ) )
		anim.initAnimSet[ "exposed_idle" ] = array( idleAnim );

	if ( isdefined( reloadAnim ) )
	{
		anim.initAnimSet[ "reload" ] = array( reloadAnim );
		anim.initAnimSet[ "reload_crouchhide" ] = array( reloadAnim );
	}

	self.combatStandAnims = anim.initAnimSet;
}


init_animset_complete_custom_crouch( completeSet )
{
	self.combatCrouchAnims = completeSet;
}

init_animset_custom_crouch( fireAnim, idleAnim, reloadAnim )
{
	assert( isdefined( anim.animsets ) && isdefined( anim.animsets.defaultCrouch ) );
	
	anim.initAnimSet = anim.animsets.defaultCrouch;

	if ( isdefined( fireAnim ) )
	{
		anim.initAnimSet[ "fire" ] = fireAnim;
		anim.initAnimSet[ "single" ] = array( fireAnim );
		set_animarray_custom_burst_and_semi_fire_crouch( fireAnim );
	}

	if ( isdefined( idleAnim ) )
		anim.initAnimSet[ "exposed_idle" ] = array( idleAnim );

	if ( isdefined( reloadAnim ) )
		anim.initAnimSet[ "reload" ] = array( reloadAnim );

	self.combatCrouchAnims = anim.initAnimSet;
}	


clear_custom_animset()
{
	self.customMoveAnimSet = undefined;
	self.customIdleAnimSet = undefined;

	self.combatStandAnims = undefined;
	self.combatCrouchAnims = undefined;
}


////////////////////////////////////////////
// Helpers for the above init_*
////////////////////////////////////////////

set_animarray_standing_turns_pistol( animArray )
{
	anim.initAnimSet[ "turn_left_45" ] = %pistol_stand_turn45L;
	anim.initAnimSet[ "turn_left_90" ] = %pistol_stand_turn90L;
	anim.initAnimSet[ "turn_left_135" ] = %pistol_stand_turn90L;
	anim.initAnimSet[ "turn_left_180" ] = %pistol_stand_turn180L;
	anim.initAnimSet[ "turn_right_45" ] = %pistol_stand_turn45R;
	anim.initAnimSet[ "turn_right_90" ] = %pistol_stand_turn90R;
	anim.initAnimSet[ "turn_right_135" ] = %pistol_stand_turn90R;
	anim.initAnimSet[ "turn_right_180" ] = %pistol_stand_turn180L;
}

set_animarray_standing_turns()
{
	anim.initAnimSet[ "turn_left_45" ] = %exposed_tracking_turn45L;
	anim.initAnimSet[ "turn_left_90" ] = %exposed_tracking_turn90L;
	anim.initAnimSet[ "turn_left_135" ] = %exposed_tracking_turn135L;
	anim.initAnimSet[ "turn_left_180" ] = %exposed_tracking_turn180L;
	anim.initAnimSet[ "turn_right_45" ] = %exposed_tracking_turn45R;
	anim.initAnimSet[ "turn_right_90" ] = %exposed_tracking_turn90R;
	anim.initAnimSet[ "turn_right_135" ] = %exposed_tracking_turn135R;
	anim.initAnimSet[ "turn_right_180" ] = %exposed_tracking_turn180R;
}

set_animarray_crouching_turns()
{
	anim.initAnimSet[ "turn_left_45" ] = %exposed_crouch_turn_90_left;
	anim.initAnimSet[ "turn_left_90" ] = %exposed_crouch_turn_90_left;
	anim.initAnimSet[ "turn_left_135" ] = %exposed_crouch_turn_180_left;
	anim.initAnimSet[ "turn_left_180" ] = %exposed_crouch_turn_180_left;
	anim.initAnimSet[ "turn_right_45" ] = %exposed_crouch_turn_90_right;
	anim.initAnimSet[ "turn_right_90" ] = %exposed_crouch_turn_90_right;
	anim.initAnimSet[ "turn_right_135" ] = %exposed_crouch_turn_180_right;
	anim.initAnimSet[ "turn_right_180" ] = %exposed_crouch_turn_180_right;
}


set_animarray_stance_change()
{
	anim.initAnimSet[ "crouch_2_stand" ] = %exposed_crouch_2_stand;
	anim.initAnimSet[ "crouch_2_prone" ] = %crouch_2_prone;
	anim.initAnimSet[ "stand_2_crouch" ] = %exposed_stand_2_crouch;
	anim.initAnimSet[ "stand_2_prone" ] = %stand_2_prone;
	anim.initAnimSet[ "prone_2_crouch" ] = %prone_2_crouch;
	anim.initAnimSet[ "prone_2_stand" ] = %prone_2_stand;
}

set_animarray_burst_and_semi_fire_stand()
{
	anim.initAnimSet[ "burst2" ] = %exposed_shoot_burst3;// ( will be stopped after second bullet )
	anim.initAnimSet[ "burst3" ] = %exposed_shoot_burst3;
	anim.initAnimSet[ "burst4" ] = %exposed_shoot_burst4;
	anim.initAnimSet[ "burst5" ] = %exposed_shoot_burst5;
	anim.initAnimSet[ "burst6" ] = %exposed_shoot_burst6;

	anim.initAnimSet[ "semi2" ] = %exposed_shoot_semi2;
	anim.initAnimSet[ "semi3" ] = %exposed_shoot_semi3;
	anim.initAnimSet[ "semi4" ] = %exposed_shoot_semi4;
	anim.initAnimSet[ "semi5" ] = %exposed_shoot_semi5;
}


set_animarray_custom_burst_and_semi_fire_stand( fireAnim )
{
	anim.initAnimSet[ "burst2" ] = fireAnim;
	anim.initAnimSet[ "burst3" ] = fireAnim;
	anim.initAnimSet[ "burst4" ] = fireAnim;
	anim.initAnimSet[ "burst5" ] = fireAnim;
	anim.initAnimSet[ "burst6" ] = fireAnim;

	anim.initAnimSet[ "semi2" ] = fireAnim;
	anim.initAnimSet[ "semi3" ] = fireAnim;
	anim.initAnimSet[ "semi4" ] = fireAnim;
	anim.initAnimSet[ "semi5" ] = fireAnim;
}


set_animarray_burst_and_semi_fire_crouch()
{
	anim.initAnimSet[ "burst2" ] = %exposed_crouch_shoot_burst3;
	anim.initAnimSet[ "burst3" ] = %exposed_crouch_shoot_burst3;
	anim.initAnimSet[ "burst4" ] = %exposed_crouch_shoot_burst4;
	anim.initAnimSet[ "burst5" ] = %exposed_crouch_shoot_burst5;
	anim.initAnimSet[ "burst6" ] = %exposed_crouch_shoot_burst6;

	anim.initAnimSet[ "semi2" ] = %exposed_crouch_shoot_semi2;
	anim.initAnimSet[ "semi3" ] = %exposed_crouch_shoot_semi3;
	anim.initAnimSet[ "semi4" ] = %exposed_crouch_shoot_semi4;
	anim.initAnimSet[ "semi5" ] = %exposed_crouch_shoot_semi5;
}

set_animarray_custom_burst_and_semi_fire_crouch( fireAnim )
{
	anim.initAnimSet[ "burst2" ] = fireAnim;
	anim.initAnimSet[ "burst3" ] = fireAnim;
	anim.initAnimSet[ "burst4" ] = fireAnim;
	anim.initAnimSet[ "burst5" ] = fireAnim;
	anim.initAnimSet[ "burst6" ] = fireAnim;

	anim.initAnimSet[ "semi2" ] = fireAnim;
	anim.initAnimSet[ "semi3" ] = fireAnim;
	anim.initAnimSet[ "semi4" ] = fireAnim;
	anim.initAnimSet[ "semi5" ] = fireAnim;
}


set_animarray_add_turn_aims_stand()
{
	anim.initAnimSet[ "add_turn_aim_up" ] = %exposed_turn_aim_8;
	anim.initAnimSet[ "add_turn_aim_down" ] = %exposed_turn_aim_2;
	anim.initAnimSet[ "add_turn_aim_left" ] = %exposed_turn_aim_4;
	anim.initAnimSet[ "add_turn_aim_right" ] = %exposed_turn_aim_6;
}

set_animarray_add_turn_aims_crouch()
{
	anim.initAnimSet[ "add_turn_aim_up" ] = %exposed_crouch_turn_aim_8;
	anim.initAnimSet[ "add_turn_aim_down" ] = %exposed_crouch_turn_aim_2;
	anim.initAnimSet[ "add_turn_aim_left" ] = %exposed_crouch_turn_aim_4;
	anim.initAnimSet[ "add_turn_aim_right" ] = %exposed_crouch_turn_aim_6;
}


////////////////////////////////////////////
// Stand
////////////////////////////////////////////

set_animarray_standing()
{
	if ( usingSidearm() )
	{
		self.a.array = anim.animsets.pistolStand;
	}
	else if ( isdefined( self.combatStandAnims ) )
	{
		assert( isArray( self.combatStandAnims ) );
		self.a.array = self.combatStandAnims;
	}
	else if ( isdefined( self.heat ) )
	{
		self.a.array = anim.animsets.heatStand;
	}
	else if ( usingRocketLauncher() )
	{
		self.a.array = anim.animsets.rpgStand;
	}
	else if ( isdefined( self.weapon ) && weapon_pump_action_shotgun() )
	{
		self.a.array = anim.animsets.shotgunStand;
	}
	else if ( self isCQBWalking() )
	{
		self.a.array = anim.animsets.cqbStand;
	}
	else
	{
		self.a.array = anim.animsets.defaultStand;
	}
}


////////////////////////////////////////////
// Crouch
////////////////////////////////////////////

set_animarray_crouching()
{
	if ( usingSidearm() )
		animscripts\shared::placeWeaponOn( self.primaryweapon, "right" );
	
	if ( isdefined( self.combatCrouchAnims ) )
	{
		assert( isArray( self.combatCrouchAnims ) );
		self.a.array = self.combatCrouchAnims;
	}
	else if ( usingRocketLauncher() )
	{
		self.a.array = anim.animsets.rpgCrouch;
	}
	else if ( isdefined( self.weapon ) && weapon_pump_action_shotgun() )
	{
		self.a.array = anim.animsets.shotgunCrouch;
	}
	else
	{
		self.a.array = anim.animsets.defaultCrouch;
	}
}



////////////////////////////////////////////
// Prone
////////////////////////////////////////////

set_animarray_prone()
{
	if ( usingSidearm() )
		animscripts\shared::placeWeaponOn( self.primaryweapon, "right" );

	self.a.array = anim.animsets.defaultProne;
}


////////////////////////////////////////////
// Moving turn
////////////////////////////////////////////

init_moving_turn_animations()
{
	anim.runTurnAnims[ "L90" ] 	= %run_turn_L90;
	anim.runTurnAnims[ "R90" ] 	= %run_turn_R90;
	anim.runTurnAnims[ "L45" ] 	= %run_turn_L45;
	anim.runTurnAnims[ "R45" ] 	= %run_turn_R45;
	anim.runTurnAnims[ "L135" ] = %run_turn_L135;
	anim.runTurnAnims[ "R135" ] = %run_turn_R135;
	anim.runTurnAnims[ "180" ] 	= %run_turn_180;

	anim.cqbTurnAnims[ "L90" ] 	= %CQB_walk_turn_4;
	anim.cqbTurnAnims[ "R90" ] 	= %CQB_walk_turn_6;
	anim.cqbTurnAnims[ "L45" ] 	= %CQB_walk_turn_7;
	anim.cqbTurnAnims[ "R45" ] 	= %CQB_walk_turn_9;
	anim.cqbTurnAnims[ "L135" ] = %CQB_walk_turn_1;
	anim.cqbTurnAnims[ "R135" ] = %CQB_walk_turn_3;
	anim.cqbTurnAnims[ "180" ] 	= %CQB_walk_turn_2;
}


////////////////////////////////////////////
// Misc
////////////////////////////////////////////


MAX_RUN_N_GUN_ANGLE = 130;
RUN_N_GUN_TRANSITION_POINT = 60 / MAX_RUN_N_GUN_ANGLE;

set_animset_run_n_gun()
{
	self.maxRunNGunAngle = MAX_RUN_N_GUN_ANGLE;
	self.runNGunTransitionPoint = RUN_N_GUN_TRANSITION_POINT;
	self.runNGunIncrement = 0.3;
	
	self.runNGunAnims[ "F" ] = %run_n_gun_F;
	self.runNGunAnims[ "L" ] = %run_n_gun_L;
	self.runNGunAnims[ "R" ] = %run_n_gun_R;
	self.runNGunAnims[ "LB" ] = %run_n_gun_L_120;
	self.runNGunAnims[ "RB" ] = %run_n_gun_R_120;
}


set_ambush_sidestep_anims()
{
	assert( isdefined( self.a.moveAnimSet ) );

	self.a.moveAnimSet[ "move_l" ] = %combatwalk_L;
	self.a.moveAnimSet[ "move_r" ] = %combatwalk_R;
	self.a.moveAnimSet[ "move_b" ] = %combatwalk_B;
}

heat_reload_anim()
{
	if ( self.weapon != self.primaryweapon )
		return animArrayPickRandom( "reload" );
		
	if ( isdefined( self.node ) )
	{
		if ( self nearClaimNodeAndAngle() )
		{
			coverReloadAnim = undefined;
			if ( self.node.type == "Cover Left" )
				coverReloadAnim = %heat_cover_reload_R;
			else if ( self.node.type == "Cover Right" )
				coverReloadAnim = %heat_cover_reload_L;
				
			if ( isdefined( coverReloadAnim ) )
			{
				//self mayMoveToPoint( reloadAnimPos );
				return coverReloadAnim;
			}
		}
	}
	
	return %heat_exposed_reload;
}