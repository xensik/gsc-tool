#include common_scripts\utility;
#include maps\mp\_utility;

	// This script automaticly plays a users specified oneshot effect on all prefabs that have the 
	// specified "script_struct" and "targetname" It also excepts angles from the "script_struct" 
	// but will set a default angle of ( 0, 0, 0 ) if none is defined.
	//
	// example of the syntax: 
	// global_FX( "targetname", "fxIDname", "fxFile", "delay"
	
main()
{
	
	randomStartDelay = randomfloatrange( -20, -15 );

	// prefabs/misc_models/com_barrel_fire.map
	global_FX( "barrel_fireFX_origin", "global_barrel_fire", "fire/firelp_barrel_pm", randomStartDelay, "fire_barrel_small" );

	// prefabs/misc_models/ch_street_light_02_on.map
	// prefabs/misc_models/ch_street_wall_light_01_on.map
	global_FX( "ch_streetlight_02_FX_origin", "ch_streetlight_02_FX", "misc/lighthaze", randomStartDelay );

	// prefabs/misc_models/me_streetlight_on.map
	// prefabs/misc_models/me_streetlight_on_scaleddown80.map
	global_FX( "me_streetlight_01_FX_origin", "me_streetlight_01_FX", "misc/lighthaze_bog_a", randomStartDelay );

	// prefabs\village_assault\misc\lamp_post.map
	// prefabs\misc_models\ch_street_light_01_on.map
	global_FX( "ch_street_light_01_on", "lamp_glow_FX", "misc/light_glow_white", randomStartDelay );

	// prefabs\dcburning\lamp_post_globe_on.map
	global_FX( "lamp_post_globe_on", "lamp_glow_FX", "misc/light_glow_white", randomStartDelay );

	// prefabs\village_assault\misc\highway_lamp_post.map
	global_FX( "highway_lamp_post", "ch_streetlight_02_FX", "misc/lighthaze_villassault", randomStartDelay );

	// prefabs/misc_models/cs_cargoship_spotlight_on.map
	global_FX( "cs_cargoship_spotlight_on_FX_origin", "cs_cargoship_spotlight_on_FX", "misc/lighthaze", randomStartDelay );

	// prefabs/misc_models/me_dumpster_fire.map
	global_FX( "me_dumpster_fire_FX_origin", "me_dumpster_fire_FX", "fire/firelp_med_pm", randomStartDelay, "fire_dumpster_medium" );

	// prefabs/misc_models/com_tires01_burning.map
	global_FX( "com_tires_burning01_FX_origin", "com_tires_burning01_FX", "fire/tire_fire_med", randomStartDelay );

	// prefabs/icbm/icbm_powerlinetower02.map
	global_FX( "icbm_powerlinetower_FX_origin", "icbm_powerlinetower_FX", "misc/power_tower_light_red_blink", randomStartDelay );

	// prefabs/icbm/icbm_powerlinetower02.map
	global_FX( "icbm_mainframe_FX_origin", "icbm_mainframe_FX", "props/icbm_mainframe_lightblink", randomStartDelay );

	// prefabs/misc_model/cs_cargoship_wall_light_red_pulse.map
	global_FX( "light_pulse_red_FX_origin", "light_pulse_red_FX", "misc/light_glow_red_generic_pulse", -2 );

	// prefabs/misc_model/cs_cargoship_wall_light_red_pulse.map
	global_FX( "light_pulse_red_FX_origin", "light_pulse_red_FX", "misc/light_glow_red_generic_pulse", -2 );

	// prefabs/misc_model/cs_cargoship_wall_light_orange_pulse.map
	global_FX( "light_pulse_orange_FX_origin", "light_pulse_orange_FX", "misc/light_glow_orange_generic_pulse", -2 );

	// prefabs/oilrig/lights/light_corner_01.map
	// prefabs/oilrig/helipad/helipad_light.map
	global_FX( "light_red_blink_FX_origin", "light_red_blink", "misc/power_tower_light_red_blink", -2 );

	// prefabs/misc_models/ch_industrial_light_01_on.map
	global_FX( "lighthaze_oilrig_FX_origin", "lighthaze_oilrig", "misc/lighthaze_oilrig", randomStartDelay );

	// prefabs/misc_models/ch_industrial_light_01_on_white.map
	global_FX( "lighthaze_white_FX_origin", "lighthaze_white", "misc/lighthaze_white", randomStartDelay );

	// prefabs/misc_models/cs_cargoship_wall_light_on.map
	global_FX( "light_glow_walllight_white_FX_origin", "light_glow_walllight_white", "misc/light_glow_walllight_white", randomStartDelay );

	// prefabs/misc_models/me_lightfluohang_on.map
	global_FX( "fluorescent_glow_FX_origin", "fluorescent_glow", "misc/fluorescent_glow", randomStartDelay );

	// prefabs/misc_models/ch_industrial_light_02_on.map
	global_FX( "light_glow_industrial_FX_origin", "light_glow_industrial", "misc/light_glow_industrial", randomStartDelay );

	// prefabs/cliffhanger/red_light1.map
	// prefabs/misc_model/com_emergencylightcase_on.map
	global_FX( "light_red_steady_FX_origin", "light_red_steady", "misc/tower_light_red_steady", -2 );

	// prefabs/cliffhanger/blue_light1.map
	// prefabs/oilrig/helipad/helipad_light.map
	// prefabs/misc_model/com_emergencylightcase_blue_on.map
	global_FX( "light_blue_steady_FX_origin", "light_blue_steady", "misc/tower_light_blue_steady", -2 );

	// prefabs/misc_models/com_emergencylightcase_orange.map
	global_FX( "light_orange_steady_FX_origin", "light_orange_steady", "misc/tower_light_orange_steady", -2 );

	// prefabs/misc_models/mil_lightstick_pile_on.map
	global_FX( "glow_stick_pile_FX_origin", "glow_stick_pile", "misc/glow_stick_glow_pile", -2 );

	// prefabs/misc_models/mil_lightstick_pile_on_orange.map
	global_FX( "glow_stick_orange_pile_FX_origin", "glow_stick_pile_orange", "misc/glow_stick_glow_pile_orange", -2 );

	// prefabs/plaza/blinky_tower.map
	global_FX( "highrise_blinky_tower", "highrise_blinky_tower_FX", "misc/power_tower_light_red_blink_large", randomStartDelay );

	// prefabs/mil_emergency_flare.map
	global_FX( "flare_ambient_FX_origin", "flare_ambient_FX", "misc/flare_ambient", randomStartDelay, "emt_road_flare_burn" );

	// prefabs/misc_models/dt_light_on.map
	// prefabs/misc_models/com_utility_light_on.map
	// prefabs/misc_models/utility_lightbulb_bare_on.map
	global_FX( "light_glow_white_bulb_FX_origin", "light_glow_white_bulb_FX", "misc/light_glow_white_bulb", randomStartDelay);

	// prefabs/misc_models/com_restaurantceilinglamp_on.map
	global_FX( "light_glow_white_lamp_FX_origin", "light_glow_white_lamp_FX", "misc/light_glow_white_lamp", randomStartDelay);

}

global_FX( targetname, fxName, fxFile, delay, soundalias )
{
	// script_structs
	ents = getstructarray(targetname,"targetname");
	if ( !isdefined( ents ) )
		return;
	if ( ents.size <= 0 )
		return;
	
	for ( i = 0 ; i < ents.size ; i++ )
		ents[i] global_FX_create( fxName, fxFile, delay, soundalias );
}

global_FX_create( fxName, fxFile, delay, soundalias )
{
	if ( !isdefined( level._effect ) )
		level._effect = [];
	if ( !isdefined( level._effect[ fxName ] ) )
		level._effect[ fxName ]	= loadfx( fxFile );
	
	// default effect angles if they dont exist
	if ( !isdefined( self.angles ) )
		self.angles = ( 0, 0, 0 );
	
	ent = createOneshotEffect( fxName );
	ent.v[ "origin" ] = ( self.origin );
	ent.v[ "angles" ] = ( self.angles );
	ent.v[ "fxid" ] = fxName;
	ent.v[ "delay" ] = delay;
	if ( isdefined( soundalias ) )
	{
		ent.v[ "soundalias" ] = soundalias;
	}
}