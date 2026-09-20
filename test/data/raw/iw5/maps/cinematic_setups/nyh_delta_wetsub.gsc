#include maps\_utility;
#include common_scripts\utility;
#include maps\_anim;
#include maps\_vehicle;


main()
{
	setup_generic_human();
	setup_vehicle();
}

#using_animtree( "generic_human" );
setup_generic_human()
{
	level.scr_anim[ "lonestar" ][ "pier_jump" ]		= %ny_harbor_delta_wetsub_guy1;
	level.scr_anim[ "grinch" ][ "pier_jump" ]			= %ny_harbor_delta_wetsub_guy2;
	level.scr_anim[ "truck" ][ "pier_jump" ]		= %ny_harbor_delta_wetsub_guy3;
}

#using_animtree( "vehicles" );
setup_vehicle()
{
	level.scr_animtree["blackshadow"] = #animtree;
	level.scr_anim[ "blackshadow" ][ "pier_jump" ]	= %ny_harbor_delta_wetsub_guy3_sdv;
}
