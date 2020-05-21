main()
{	
	level._effect["godrays_qad"]								=loadfx("lights/godrays_qad");
	level._effect["sand_vortex_runner_qad"]						=loadfx("sand/sand_vortex_runner_qad");
	level._effect["sandstorm_wall_qadeem"]						=loadfx("sand/sandstorm_wall_qadeem");
	level._effect["paper_blowing_trash_fast_model_short"]		=loadfx("misc/paper_blowing_trash_fast_model_short");
	level._effect["water_wake_mp"]								=loadfx("water/water_wake_mp");
	level._effect["light_shaft_dust_qad"]						=loadfx("dust/light_shaft_dust_qad");
	level._effect["light_dust_motes_blowing_qadeem"]			=loadfx("dust/light_dust_motes_blowing_qadeem");
	level._effect["light_dust_motes_blowing_qadeem_interior"]	=loadfx("dust/light_dust_motes_blowing_qadeem_interior");
	level._effect["sand_blowing_lt_qadeem"]						=loadfx("sand/sand_blowing_lt_qadeem");
	level._effect["sand_blowing_mp_qadeem"]						=loadfx("sand/sand_blowing_mp_qadeem");
	level._effect["sand_blowing_rooftops"]						=loadfx("sand/sand_blowing_rooftops");
	level._effect["bulb_single_orange"]							=loadfx("lights/bulb_single_orange");
	level._effect["mist_light"]									=loadfx("water/mist_light");
	level._effect["foliage_dub_potted_spikey_plant"]			=loadfx("props/foliage_dub_potted_spikey_plant");
	level._effect["dub_vase_02"]								=loadfx("props/dub_vase_02");
	level._effect["sand_blowing_mp_qadeem_runner"]				=loadfx("sand/sand_blowing_mp_qadeem_runner");
	level._effect["sand_blowing_mp_qadeem_runner2"]				=loadfx("sand/sand_blowing_mp_qadeem_runner2");
	level._effect["fountain_splash_qadeem_circle"]				=loadfx("water/fountain_splash_qadeem_circle");
	level._effect["fountain_splash_qadeem_circle_sm"]			=loadfx("water/fountain_splash_qadeem_circle_sm");
	level._effect["fountain_splash_qadeem_sm"]					=loadfx("water/fountain_splash_qadeem_sm");
	level._effect["fountain_wake_qadeem"]						=loadfx("water/fountain_wake_qadeem");
	level._effect["water_sprinkler"]							=loadfx("water/water_sprinkler");
	level._effect["dust_spiral_qadeem"]							=loadfx("dust/dust_spiral_qadeem");
	level._effect["amb_dust_int"]								=loadfx("dust/amb_dust_int");
  	level._effect["body_splash" ]	                    		=loadfx("water/body_splash" );
  	level._effect["lionhead_fountain_qadeem" ]	                =loadfx("water/lionhead_fountain_qadeem" );
  	level._effect["water_bubbles_random_runner_qad" ]	        =loadfx("water/water_bubbles_random_runner_qad" );
  	
  	
	
/#
    if ( getdvar( "clientSideEffects" ) != "1" )
        maps\createfx\mp_qadeem_fx::main();
#/

}
