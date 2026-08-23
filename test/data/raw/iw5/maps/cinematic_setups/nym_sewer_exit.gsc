#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;


main()
{
	building_destruction();
}

#using_animtree( "script_model" );
building_destruction()
{
	level.scr_animtree["building_des"] = #animtree;
	level.scr_anim[ "building_des" ][ "manhattan_sewer_exit" ] = %ny_manhattan_intro_debris;
	
}
