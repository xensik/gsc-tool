#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;


main()
{
	setup_generic_human();
	setup_player();
	setup_vehicle();
	setup_script_models();
}

#using_animtree( "generic_human" );
setup_generic_human()
{
	level.scr_anim[ "lonestar" ][ "ny_manhattan_hind_finale" ] = %ny_manhatten_hind_finale_guy1;
	level.scr_anim[ "truck" ][ "ny_manhattan_hind_finale" ] = %ny_manhatten_hind_finale_guy2;
	level.scr_anim[ "reno" ][ "ny_manhattan_hind_finale" ] = %ny_manhatten_hind_finale_guy3;
	level.scr_anim[ "lonestar" ][ "ny_manhattan_hind_finale2" ] = %ny_manhatten_hind_finale_guy1_pt2;
	level.scr_anim[ "truck" ][ "ny_manhattan_hind_finale2" ] = %ny_manhatten_hind_finale_guy2_pt2;
	level.scr_anim[ "reno" ][ "ny_manhattan_hind_finale2" ] = %ny_manhatten_hind_finale_guy3_pt2;
}


#using_animtree( "player" );
setup_player()
{
	level.scr_anim[ "player_rig" ][ "ny_manhattan_hind_finale" ] = %ny_manhatten_hind_finale_player;
	level.scr_anim[ "player_rig" ][ "ny_manhattan_hind_finale2" ] = %ny_manhatten_hind_finale_player_pt2;
}

#using_animtree( "vehicles" );
setup_vehicle()
{
	level.scr_animtree["hind"] = #animtree;
	level.scr_anim[ "hind" ][ "ny_manhattan_hind_finale" ]	= %ny_manhatten_hind_finale_hind;
	level.scr_anim[ "hind" ][ "ny_manhattan_hind_finale2" ]	= %ny_manhatten_hind_finale_hind_pt2;
	addNotetrack_customFunction( "hind", "vfx_enemy_tail_hit", ::hind_finale_enemy_tail_hit_vfx_start, "ny_manhattan_hind_finale2" );
	addNotetrack_customFunction( "hind", "vfx_enemy_tail_hit", ::hind_finale_dof, "ny_manhattan_hind_finale2" );
	//addNotetrack_customFunction( "hind", "vfx_player_smk_trail_start", ::hind_finale_player_smk_trail_start, "ny_manhattan_hind_finale2" );
	level.scr_animtree["enemyhind"] = #animtree;
	level.scr_anim[ "enemyhind" ][ "ny_manhattan_hind_finale" ]	= %ny_manhatten_hind_finale_enemyhind;
	level.scr_anim[ "enemyhind" ][ "ny_manhattan_hind_finale2" ]	= %ny_manhatten_hind_finale_enemyhind_pt2;
	addNotetrack_customFunction( "enemyhind", "vfx_enemy_tail_smk_trail", ::hind_finale_enemy_smk_trail_start, "ny_manhattan_hind_finale2" );
	addNotetrack_customFunction( "enemyhind", "vfx_enemy_building_hit", ::hind_finale_enemy_building_hit_start, "ny_manhattan_hind_finale2" );
	level.scr_animtree["hindturret"] = #animtree;
	level.scr_anim[ "hindturret" ][ "ny_manhattan_hind_finale2" ]	= %ny_manhatten_hind_finale_turret_pt2;
}

#using_animtree( "script_model" );
setup_script_models()
{
	level.scr_model["chunks"] = "ny_building_chunks";
	level.scr_animtree["chunks"] = #animtree;
	level.scr_anim[ "chunks" ][ "ny_manhattan_hind_finale3" ]	= %ny_manhatten_hind_finale_exploding_parts;
	addNotetrack_customFunction( "chunks", "vfx_smktrail_start", ::hind_finale_chunk_smk_trail_start, "ny_manhattan_hind_finale3" );
	
}

//flash before the shell shock screen
hind_finale_enemy_tail_hit_vfx_start(guy)
{
    	PlayFXOnTag( getfx( "hind_finale_enemy_tail_hit_ny" ), guy, "tag_doorgun" );  
 		PlayFXOnTag( getfx( "hind_finale_player_beeper" ), guy, "tag_light_cargo01" );  
 		//interior sparks
 		PlayFXOnTag( getfx( "hind_finale_player_damage_spark" ), guy, "tag_light_cargo01" );  
 		wait (7.5);
 		PlayFXOnTag( getfx( "hind_finale_player_damage_spark" ), guy, "tag_light_cargo01" );   
} 

//DOF
hind_finale_dof(guy)
{
	start = level.dofDefault;
	curr_org = self gettagorigin("tag_origin");
	curr_eye = level.player.origin;
	curr_dist = length(curr_org - curr_eye);
	dof_see_knife = [];
	last_dof = [];
	dof_see_knife[ "nearStart" ] = 60;
	dof_see_knife[ "nearEnd" ] = 500;
	dof_see_knife[ "nearBlur" ] = 10;
	dof_see_knife[ "farStart" ] = 5500;
	dof_see_knife[ "farEnd" ] = 8000;
	dof_see_knife[ "farBlur" ] = 1;
	last_dof = dof_see_knife;
	dur = 20 * 5;
	blend_dof( start, dof_see_knife, .2 );
	wait(.15);
	for(i = 0; i < 58; i ++)
	{
		curr_org = self gettagorigin("tag_origin");
		curr_eye = level.player.origin;
		curr_dist = length(curr_org - curr_eye);
		dof_see_knife[ "farStart" ] = 5500;
		dof_see_knife[ "farEnd" ] = 8000;
		blend_dof( last_dof, dof_see_knife, .2 );
		last_dof = dof_see_knife;
		wait(.2);
	}
	blend_dof(dof_see_knife, start, 1 );
	
	wait (3);
	
	start = level.dofDefault;
	curr_org = self gettagorigin("tag_origin");
	curr_eye = level.player.origin;
	curr_dist = length(curr_org - curr_eye);
	dof_see_knife = [];
	last_dof = [];
	dof_see_knife[ "nearStart" ] = 0;
	dof_see_knife[ "nearEnd" ] = 1;
	dof_see_knife[ "nearBlur" ] = 10;
	dof_see_knife[ "farStart" ] = 1500;
	dof_see_knife[ "farEnd" ] = 8000;
	dof_see_knife[ "farBlur" ] = 3.5;
	last_dof = dof_see_knife;
	dur = 20 * 5;
	blend_dof( start, dof_see_knife, .2 );
	wait(.15);
	for(i = 0; i < 40; i ++)
	{
		curr_org = self gettagorigin("tag_origin");
		curr_eye = level.player.origin;
		curr_dist = length(curr_org - curr_eye);
		dof_see_knife[ "farStart" ] = 1500;
		dof_see_knife[ "farEnd" ] = 8000;
		blend_dof( last_dof, dof_see_knife, .2 );
		last_dof = dof_see_knife;
		wait(.5);
	}
	
	wait(1);
		
	dof_outtro = [];
	dof_outtro[ "nearStart" ] = .1;
	dof_outtro[ "nearEnd" ] = .2;
	dof_outtro[ "nearBlur" ] = 4.0;
	dof_outtro[ "farStart" ] = 5200;
	dof_outtro[ "farEnd" ] = 13500;
	dof_outtro[ "farBlur" ] = 1.65;
	
	blend_dof(dof_see_knife, dof_outtro, .7 );
}

hind_finale_player_smk_trail_start(guy)
{
    //PlayFXOnTag( getfx( "hind_finale_player_smk_trail_ny" ), guy, "tag_wing_R" );
    PlayFXOnTag( getfx( "hind_finale_player_smk_rotor_ny" ), guy, "tag_origin" );
} 

hind_finale_enemy_smk_trail_start(guy)
{
    PlayFXOnTag( getfx( "hind_finale_enemy_tail_smk_trail_ny" ), guy, "tag_light_tail" );
   	level waittill ("enemyhind_hit_building_start");
   	StopFXOnTag( getfx( "hind_finale_enemy_tail_smk_trail_ny" ), guy, "tag_light_tail" );
} 

hind_finale_chunk_smk_trail_start(guy)
{
	   PlayFXOnTag( getfx( "hind_finale_chunk_smk_trail_ny" ), guy, "jnt_barrel" );
}	


hind_finale_enemy_building_hit_start(guy)
{
	exploder(17); //init building hit shkwv
	level notify ("enemyhind_hit_building_start");
	wait (0.15);
	exploder(18); // init buildling explosion
	
	wait (0.30);
	exploder(19);  //fireball shooting out from the other side with a bigger explosion
	
	wait (0.9);
	exploder(20);  //lingering fireball
	
	wait (19.0);
	exploder(21);  //more fire around the building structure
	
	//secondary explosion when hind flies by the buildling right before the ending
	wait (6.1);
	//exploder(22);  
	wait (3.0);
	exploder(23);
	//wait (1.2);
	//exploder(24);
}
 	
