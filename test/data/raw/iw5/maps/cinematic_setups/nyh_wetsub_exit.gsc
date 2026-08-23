#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;


main()
{
	setup_generic_human();
	setup_vehicle();
	setup_viewmodel();
}

#using_animtree( "generic_human" );
setup_generic_human()
{
	level.scr_animtree[ "submariner1" ] = #animtree;
	level.scr_animtree[ "submariner2" ] = #animtree;
	level.scr_animtree[ "submariner3" ] = #animtree;
	
	level.scr_anim[ "submariner1" ][ "nyh_wetsub_exit" ] = %ny_harbor_wetsub_exit_guy1;
	level.scr_anim[ "submariner2" ][ "nyh_wetsub_exit" ] = %ny_harbor_wetsub_exit_guy2;
	level.scr_anim[ "submariner3" ][ "nyh_wetsub_exit" ] = %ny_harbor_wetsub_exit_guy3;

	level.scr_anim[ "sandman" ][ "nyh_wetsub_ladder" ] = %ny_harbor_wetsub_ladder_guy2;

	level.scr_anim[ "essex" ][ "nyh_wetsub_board" ] = %ny_harbor_delta_guy2_board_slava;
	level.scr_anim[ "grinch" ][ "nyh_wetsub_board" ] = %ny_harbor_delta_guy2_board_slava;

	level.scr_anim[ "sandman" ][ "nyh_wetsub_double_paired_kill_covert" ] = %ny_harbor_delta_ai_double_paired_kill_covert_friendly;
	level.scr_anim[ "enemy1" ][ "nyh_wetsub_double_paired_kill_covert" ] = %ny_harbor_delta_ai_double_paired_kill_covert_enemy1;
	level.scr_anim[ "enemy1" ][ "nyh_wetsub_double_paired_kill_covert_idles" ][0] = %ny_harbor_delta_ai_double_paired_kill_covert_enemy1_idle;
	level.scr_anim[ "enemy2" ][ "nyh_wetsub_double_paired_kill_covert" ] = %ny_harbor_delta_ai_double_paired_kill_covert_enemy2;
	level.scr_anim[ "enemy2" ][ "nyh_wetsub_double_paired_kill_covert_idles" ][0] = %ny_harbor_delta_ai_double_paired_kill_covert_enemy2_idle;
}


#using_animtree( "vehicles" );
setup_vehicle()
{
	level.scr_animtree[ "sdv1" ] = #animtree;
	level.scr_animtree[ "sdv2" ] = #animtree;
	level.scr_animtree[ "sdv3" ] = #animtree;
	level.scr_animtree[ "player_sdv" ] = #animtree;
	level.scr_anim[ "sdv1" ][ "nyh_wetsub_exit" ] = %ny_harbor_wetsub_exit_vehicle1;
	level.scr_anim[ "sdv2" ][ "nyh_wetsub_exit" ] = %ny_harbor_wetsub_exit_vehicle2;
	level.scr_anim[ "sdv3" ][ "nyh_wetsub_exit" ] = %ny_harbor_wetsub_exit_vehicle3;
	level.scr_anim[ "player_sdv" ][ "nyh_wetsub_exit" ] = %ny_harbor_wetsub_player_exit_vehicle;
	level.scr_model[ "player_sdv" ] = "vehicle_blackshadow_730_viewmodel";
}

#using_animtree( "player" );
setup_viewmodel()
{
	level.scr_animtree[ "player_sdv_rig" ] = #animtree;
	level.scr_anim[ "player_sdv_rig" ][ "nyh_wetsub_exit" ]		 = %ny_harbor_wetsub_player_exit;
}
