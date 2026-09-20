#include maps\_vehicle_aianim;
#include maps\_vehicle;
#using_animtree( "vehicles" );
main( model, type, classname )
{
	//SNDFILE=vehicle_80s_car
	build_template( "80s_hatch1", model, type, classname );
	build_localinit( ::init_local );

	build_destructible( "vehicle_80s_hatch1_brn_destructible_mp", "vehicle_80s_hatch1_brn" );
	build_destructible( "vehicle_80s_hatch1_green_destructible_mp", "vehicle_80s_hatch1_green" );
	build_destructible( "vehicle_80s_hatch1_red_destructible_mp", "vehicle_80s_hatch1_red" );
	build_destructible( "vehicle_80s_hatch1_silv_destructible_mp", "vehicle_80s_hatch1_silv" );
	build_destructible( "vehicle_80s_hatch1_tan_destructible_mp", "vehicle_80s_hatch1_tan" );
	build_destructible( "vehicle_80s_hatch1_yel_destructible_mp", "vehicle_80s_hatch1_yel" );

	build_drive( %technical_driving_idle_forward, %technical_driving_idle_backward, 10 );

//	build_treadfx();

	//life is now determined by destructible.  less _vehicle controled
	build_life( 999, 500, 1500 );

	build_team( "allies" );
	build_aianims( ::setanims, ::set_vehicle_anims );

}

init_local()
{

}

set_vehicle_anims( positions )
{
	return positions;
}


#using_animtree( "generic_human" );

setanims()
{
	positions = [];
	return positions;// no anims yet
/*
	for(i=0;i<4;i++)
		positions[i] = spawnstruct();

	positions[0].sittag = "body_animate_jnt";
	positions[1].sittag = "body_animate_jnt";
	positions[2].sittag = "tag_passenger";
	positions[3].sittag = "body_animate_jnt";

	positions[0].idle = %humvee_driver_climb_idle;
	positions[1].idle = %humvee_passenger_idle_L;
	positions[2].idle = %humvee_passenger_idle_R;
	positions[3].idle = %humvee_passenger_idle_R;

	positions[0].getout = %humvee_driver_climb_out;
	positions[1].getout = %humvee_passenger_out_L;
	positions[2].getout = %humvee_passenger_out_R;
	positions[3].getout = %humvee_passenger_out_R;

	positions[0].getin = %humvee_driver_climb_in;
	positions[1].getin = %humvee_passenger_in_L;
	positions[2].getin = %humvee_passenger_in_R;
	positions[3].getin = %humvee_passenger_in_R;

*/
	return positions;
}

/*QUAKED script_vehicle_80s_hatch1_brn_destructible_mp (1 0 0) (-16 -16 -24) (16 16 32) USABLE SPAWNER

This will be added to your precache script when compile with Repackage Zone/Script:

vehicle_scripts\_80s_hatch1::main( "vehicle_80s_hatch1_brn_destructible_mp", undefined, "script_vehicle_80s_hatch1_brn_destructible_mp" );

These will be added to your levels CSV when compile with Repackage Zone/Script:

include,vehicle_80s_hatch1_brn_destructible_mp_80s_hatch1
include,destructible_vehicle_80s_hatch1_brn_destructible_mp
sound,vehicle_car_exp,vehicle_standard,all_sp
sound,vehicle_80s_car,vehicle_standard,all_sp


defaultmdl="vehicle_80s_hatch1_brn_destructible_mp"
default:"vehicletype" "80s_hatch1"
default:"script_team" "allies"

*/

/*QUAKED script_vehicle_80s_hatch1_green_destructible_mp (1 0 0) (-16 -16 -24) (16 16 32) USABLE SPAWNER

This will be added to your precache script when compile with Repackage Zone/Script:

vehicle_scripts\_80s_hatch1::main( "vehicle_80s_hatch1_green_destructible_mp", undefined, "script_vehicle_80s_hatch1_green_destructible_mp" );

These will be added to your levels CSV when compile with Repackage Zone/Script:

include,vehicle_80s_hatch1_green_destructible_mp_80s_hatch1
include,destructible_vehicle_80s_hatch1_green_destructible_mp
sound,vehicle_car_exp,vehicle_standard,all_sp
sound,vehicle_80s_car,vehicle_standard,all_sp


defaultmdl="vehicle_80s_hatch1_green_destructible_mp"
default:"vehicletype" "80s_hatch1"
default:"script_team" "allies"
*/

/*QUAKED script_vehicle_80s_hatch1_red_destructible_mp (1 0 0) (-16 -16 -24) (16 16 32) USABLE SPAWNER

This will be added to your precache script when compile with Repackage Zone/Script:

vehicle_scripts\_80s_hatch1::main( "vehicle_80s_hatch1_red_destructible_mp", undefined, "script_vehicle_80s_hatch1_red_destructible_mp" );

These will be added to your levels CSV when compile with Repackage Zone/Script:

include,vehicle_80s_hatch1_red_destructible_mp_80s_hatch1
include,destructible_vehicle_80s_hatch1_red_destructible_mp
sound,vehicle_car_exp,vehicle_standard,all_sp
sound,vehicle_80s_car,vehicle_standard,all_sp


defaultmdl="vehicle_80s_hatch1_red_destructible_mp"
default:"vehicletype" "80s_hatch1"
default:"script_team" "allies"
*/

/*QUAKED script_vehicle_80s_hatch1_silv_destructible_mp (1 0 0) (-16 -16 -24) (16 16 32) USABLE SPAWNER

This will be added to your precache script when compile with Repackage Zone/Script:

vehicle_scripts\_80s_hatch1::main( "vehicle_80s_hatch1_silv_destructible_mp", undefined, "script_vehicle_80s_hatch1_silv_destructible_mp" );

These will be added to your levels CSV when compile with Repackage Zone/Script:

include,vehicle_80s_hatch1_silv_destructible_mp_80s_hatch1
include,destructible_vehicle_80s_hatch1_silv_destructible_mp
sound,vehicle_car_exp,vehicle_standard,all_sp
sound,vehicle_80s_car,vehicle_standard,all_sp


defaultmdl="vehicle_80s_hatch1_silv_destructible_mp"
default:"vehicletype" "80s_hatch1"
default:"script_team" "allies"
*/

/*QUAKED script_vehicle_80s_hatch1_tan_destructible_mp (1 0 0) (-16 -16 -24) (16 16 32) USABLE SPAWNER

This will be added to your precache script when compile with Repackage Zone/Script:

vehicle_scripts\_80s_hatch1::main( "vehicle_80s_hatch1_tan_destructible_mp", undefined, "script_vehicle_80s_hatch1_tan_destructible_mp" );

These will be added to your levels CSV when compile with Repackage Zone/Script:

include,vehicle_80s_hatch1_tan_destructible_mp_80s_hatch1
include,destructible_vehicle_80s_hatch1_tan_destructible_mp
sound,vehicle_car_exp,vehicle_standard,all_sp
sound,vehicle_80s_car,vehicle_standard,all_sp


defaultmdl="vehicle_80s_hatch1_tan_destructible_mp"
default:"vehicletype" "80s_hatch1"
default:"script_team" "allies"
*/

/*QUAKED script_vehicle_80s_hatch1_yel_destructible_mp (1 0 0) (-16 -16 -24) (16 16 32) USABLE SPAWNER

This will be added to your precache script when compile with Repackage Zone/Script:

vehicle_scripts\_80s_hatch1::main( "vehicle_80s_hatch1_yel_destructible_mp", undefined, "script_vehicle_80s_hatch1_yel_destructible_mp" );

These will be added to your levels CSV when compile with Repackage Zone/Script:

include,vehicle_80s_hatch1_yel_destructible_mp_80s_hatch1
include,destructible_vehicle_80s_hatch1_yel_destructible_mp
sound,vehicle_car_exp,vehicle_standard,all_sp
sound,vehicle_80s_car,vehicle_standard,all_sp


defaultmdl="vehicle_80s_hatch1_yel_destructible_mp"
default:"vehicletype" "80s_hatch1"
default:"script_team" "allies"
*/
