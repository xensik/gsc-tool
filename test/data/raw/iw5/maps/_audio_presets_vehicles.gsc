
/*
tilt, yaw, roll, speed, altitude
*/

// THIS IS QUASI DEPRECATED (Aaron is planning to convert this to stringtable format but has not done it yet)
AUDIO_PRESETS_VEHICLES(name, p)
{	
	switch(name)
	{
		case "nymn_player_hind":
			p["speed"] 		= [
												["hind_move", ["pitch", "player_hind_move_pitch"], ["volume", "player_hind_move_volume"]],
												["hind_hover", ["pitch", "player_hind_hover_pitch"], ["volume", "player_hind_hover_volume"]],
												["updaterate", 0.2],
												//["smoothness", 0.3], 
												["smooth_up", 0.3],    // can have (smoothness, smooth_down), (smoothness, smooth_up), or (smooth_up, smooth_down)
												["smooth_down", 0.03],
												["range", 1.0, 40.0] // sets bounds of the raw input values
											];		
		break;

		case "nymn_broad_hind":
			p["speed"] 		= [
												["broad_hind_move", ["pitch", "player_hind_move_pitch"], ["volume", "enemy_hind_move_volume"]],
												//["broad_hind_hover", ["pitch", "player_hind_hover_pitch"], ["volume", "player_hind_hover_volume"]],
												["updaterate", 0.2],
												//["smoothness", 0.3], 
												["smooth_up", 0.3],    // can have (smoothness, smooth_down), (smoothness, smooth_up), or (smooth_up, smooth_down)
												["smooth_down", 0.03],
												["range", 1.0, 30.0] // sets bounds of the raw input values
											];		
		break;

		case "paris_a_mi17":
			p["speed"] 		= [
												["mi17_engine_high", ["pitch", "mi17_move_pitch"], ["volume", "mi17_move_volume"]],
												["mi17_idle_high", ["pitch", "mi17_hover_pitch"], ["volume", "mi17_hover_volume"]],
												["updaterate", 0.2],
												//["smoothness", 0.3], 
												["smooth_up", 0.3],    // can have (smoothness, smooth_down), (smoothness, smooth_up), or (smooth_up, smooth_down)
												["smooth_down", 0.01],
												["range", 1.0, 30.0] // sets bounds of the raw input values
											];		
		break;
		
		
		
		case "dubai_littlebird":
			p["speed"] 		= [
												["dubai_littlebird_engine_high", ["pitch", "dubai_littlebird_move_pitch"], ["volume", "dubai_littlebird_move_volume"]],
												["dubai_littlebird_idle_high", ["pitch", "dubai_littlebird_hover_pitch"], ["volume", "dubai_littlebird_hover_volume"]],
												["updaterate", 0.2],
												//["smoothness", 0.3], 
												["smooth_up", 0.3],    // can have (smoothness, smooth_down), (smoothness, smooth_up), or (smooth_up, smooth_down)
												["smooth_down", 0.01],
												["range", 1.0, 30.0] // sets bounds of the raw input values
											];		
		break;

		case "paris_chase_hind":
			p["speed"] 		= [
												["chase_hind_move", ["pitch", "player_hind_move_pitch"], ["volume", "enemy_hind_move_volume"]],
												//["chase_hind_hover", ["pitch", "player_hind_hover_pitch"], ["volume", "player_hind_hover_volume"]],
												["updaterate", 0.2],
												//["smoothness", 0.3], 
												["smooth_up", 0.3],    // can have (smoothness, smooth_down), (smoothness, smooth_up), or (smooth_up, smooth_down)
												["smooth_down", 0.01],
												["range", 1.0, 30.0] // sets bounds of the raw input values
											];		
		break;
		
		case "escape_zodiac":
			p["speed"]		= [
												//["shg_zodiac_plr_idle", ["pitch", "zodiac_player_idle_pitch"], ["volume", "zodiac_player_idle_volume"]],
												//["shg_zodiac_plr_motor_botm", ["pitch", "zodiac_player_bottom_pitch"], ["volume", "zodiac_player_bottom_volume"]],
												["shg_zodiac_plr_motor_slow", ["pitch", "zodiac_player_slow_pitch"], ["volume", "zodiac_player_slow_volume"]],
												["shg_zodiac_plr_motor_med", ["pitch", "zodiac_player_medium_pitch"], ["volume", "zodiac_player_medium_volume"]],
												["shg_zodiac_plr_motor_fast", ["pitch", "zodiac_player_fast_pitch"], ["volume", "zodiac_player_fast_volume"]],
												["offset", -50], // position offset forward or rear (negative values) 
												["updaterate", 0.2],
												//["smoothness", 0.3],
												["multiply_by_throttle", true], 
												["smooth_up", 0.15],    // can have (smoothness, smooth_down), (smoothness, smooth_up), or (smooth_up, smooth_down)
												["smooth_down", 0.25],
												["oneshot_duck", 0.50],
												["oneshot_duck_time", 1.5],
												["range", 0.0, 45.0] // sets bounds of the raw input values
											];

			// based on throttle toggling
			// onshots
			p["start_stop"]	= [
												["start", "shg_zodiac_plr_rampup", ["pitch", "zodiac_player_rampup_pitch"], ["volume", "zodiac_player_rampup_volume"], true], // last argument says whether or not to cause ducking with other parameters on the same vehicle
												["stop", "shg_zodiac_plr_rampdown", ["pitch", "zodiac_player_rampdown_pitch"], ["volume", "zodiac_player_rampdown_volume"]],
												["updaterate", 0.1],
												["offset", -50],
												["throttle_input", "throttle"],
												["on_threshold", 0.3], // when to trigger the on_alias
												["off_threshold", -0.3], 
												["smooth_up", 0.5],
												["smooth_down", 0.5]
											];
		break;

		case "escape_zodiac_water":
			p["speed"] 		= [
												["shg_zodiac_plr_water_idle", ["pitch", "zodiac_plr_water_idle_pitch"], ["volume", "zodiac_plr_water_idle_volume"]],
												//["shg_zodiac_plr_water_botm", ["pitch", "zodiac_plr_water_botm_pitch"], ["volume", "zodiac_plr_water_botm_volume"]],
												["shg_zodiac_plr_water_slow", ["pitch", "zodiac_plr_water_slow_pitch"], ["volume", "zodiac_plr_water_slow_volume"]],
												["shg_zodiac_plr_water_med", ["pitch", "zodiac_plr_water_med_pitch"], ["volume", "zodiac_plr_water_med_volume"]],
												["shg_zodiac_plr_water_fast", ["pitch", "zodiac_plr_water_fast_pitch"], ["volume", "zodiac_plr_water_fast_volume"]],

												["updaterate", 0.2],
												//["smoothness", 0.3], 
												["smooth_up", 0.3],    // can have (smoothness, smooth_down), (smoothness, smooth_up), or (smooth_up, smooth_down)
												["smooth_down", 0.3],
												["range", 1.0, 30.0], // sets bounds of the raw input values
												["heightmax", 25] // if height of vehicle is above this, reduce volume of sounds to zero
											];
		break;

		case "sdv_motor_player":
			p["speed"] 		= [
												["shg_sdv_plr_motor_slow", ["pitch", "sdv_plr_motor_slow_pitch"], ["volume", "sdv_plr_motor_slow_volume"]],
												["shg_sdv_plr_motor_med", ["pitch", "sdv_plr_motor_med_pitch"], ["volume", "sdv_plr_motor_med_volume"]],
												["shg_sdv_plr_motor_fast", ["pitch", "sdv_plr_motor_fast_pitch"], ["volume", "sdv_plr_motor_fast_volume"]],
												["updaterate", 0.2],
												//["smoothness", 0.3], 
												["multiply_by_throttle", true], 
												["throttle_input", "throttle"],
												["smooth_up", 0.10],    // can have (smoothness, smooth_down), (smoothness, smooth_up), or (smooth_up, smooth_down)
												["smooth_down", 0.3],
												["range", 1.0, 12.0] // sets bounds of the raw input values
											];

			// based on throttle toggling
			// onshots
			p["start_stop"]	= [
												["start", "shg_sdv_plr_startup", ["pitch", "sdv_plr_rampup_pitch"], ["volume", "sdv_plr_rampup_volume"]], // last argument says whether or not to cause ducking with other parameters on the same vehicle
												["stop", "shg_sdv_plr_shutdown", ["pitch", "sdv_plr_rampdown_pitch"], ["volume", "sdv_plr_rampdown_volume"]],
												["updaterate", 0.1],
												//["offset", -50],
												["throttle_input", "throttle"],
												["on_threshold", 0.3], // when to trigger the on_alias
												["off_threshold", -0.3], 
												["smooth_up", 0.5],
												["smooth_down", 0.5]
											];
		break;

		case "ugv_motor_player":
			p["speed"] 		= [
												["ugv_plr_motor_slow", ["pitch", "sdv_plr_motor_slow_pitch"], ["volume", "sdv_plr_motor_slow_volume"]],
												["ugv_plr_motor_slow", ["pitch", "sdv_plr_motor_med_pitch"], ["volume", "sdv_plr_motor_med_volume"]],
												["ugv_plr_motor_fast", ["pitch", "sdv_plr_motor_fast_pitch"], ["volume", "sdv_plr_motor_fast_volume"]],
												["updaterate", 0.1],
												//["smoothness", 0.3], 
												["multiply_by_throttle", true], 
												["throttle_input", "leftstick_abs"], // "leftstick_abs" takes absolute value of left stick (i.e. can go backward)
												["smooth_up", 0.2],    // can have (smoothness, smooth_down), (smoothness, smooth_up), or (smooth_up, smooth_down)
												["smooth_down", 0.2],
												["range", 1, 8.0] // sets bounds of the raw input values (default 1, 12)
											];

			// based on throttle toggling
			// onshots
			p["start_stop"]	= [
												["start", "null", ["pitch", "sdv_plr_rampup_pitch"], ["volume", "sdv_plr_rampup_volume"]], // last argument says whether or not to cause ducking with other parameters on the same vehicle
												["stop", "null", ["pitch", "sdv_plr_rampdown_pitch"], ["volume", "sdv_plr_rampdown_volume"]],
												["updaterate", 0.3],
												//["offset", -50],
												["throttle_input", "leftstick_abs"],
												["on_threshold", 0.3], // when to trigger the on_alias
												["off_threshold", -0.3], 
												["smooth_up", 0.2],
												["smooth_down", 0.2]
											];
		break;
		
		case "ugv_treads_player":
			p["speed"] 		= [
												["ugv_plr_treads_slow", ["pitch", "sdv_plr_motor_slow_pitch"], ["volume", "sdv_plr_motor_slow_volume"]],
												["ugv_plr_treads_slow", ["pitch", "sdv_plr_motor_med_pitch"], ["volume", "sdv_plr_motor_med_volume"]],
												["ugv_plr_treads_fast", ["pitch", "sdv_plr_motor_fast_pitch"], ["volume", "sdv_plr_motor_fast_volume"]],
												["updaterate", 0.1],
												//["smoothness", 0.3], 
												["multiply_by_throttle", true], 
												["throttle_input", "leftstick_abs"], // "leftstick_abs" takes absolute value of left stick (i.e. can go backward)
												["smooth_up", 0.1],    // can have (smoothness, smooth_down), (smoothness, smooth_up), or (smooth_up, smooth_down)
												["smooth_down", 0.1],
												["range", 0.5, 8.0] // sets bounds of the raw input values (default 1, 12)
											];
		break;
		
		case "ugv_idle_player":
			p["speed"] =	[
											["ugv_plr_idle", ["pitch", "so_jeep_idle_pitch"], ["volume", "so_jeep_idle_volume"]],
											["updaterate", 0.1],
											["smooth_up", 0.2],
											["smooth_down", 0.2],
											["range", 0.0, 25.0]
										];
		break;		
		

		case "sdv_water_player":
			p["speed"] 		= [
												["shg_sdv_plr_water_slow", ["pitch", "sdv_plr_water_slow_pitch"], ["volume", "sdv_plr_water_slow_volume"]],
												["shg_sdv_plr_water_med", ["pitch", "sdv_plr_water_med_pitch"], ["volume", "sdv_plr_water_med_volume"]],
												["updaterate", 0.2],
												//["smoothness", 0.3], 
												["smooth_up", 0.3],    // can have (smoothness, smooth_down), (smoothness, smooth_up), or (smooth_up, smooth_down)
												["smooth_down", 0.1],
												["range", 1.0, 8.0] // sets bounds of the raw input values
											];
		break;
		
		case "so_paris_jeep":
			p["speed"] =	[
											["so_jeep_slow", ["pitch", "so_jeep_slow_pitch"], ["volume", "so_jeep_slow_volume"]],
											["so_jeep_fast", ["pitch", "so_jeep_medium_pitch"], ["volume", "so_jeep_medium_volume"]],
											["so_jeep_idle", ["pitch", "so_jeep_idle_pitch"], ["volume", "so_jeep_idle_volume"]],
											["updaterate", 0.1],
											["smooth_up", 0.3],
											["smooth_down", 0.1],
											["range", 0.0, 25.0]
										];
		break;

	}		
	return p;
}


AUDIO_PRESETS_VEHICLE_MAPS(name, p)
{
	switch(name)
	{
//SPEC_OPS_JEEP

//SpecOps_Jeep_Idle
		case "so_jeep_idle_pitch":
		p = [
				[0.00,  0.50],
				[0.02,  0.65],
				[0.10,  0.75],
				[0.20,  0.85],
				[1.00,  1.00]
		];
		break;
		
		case "so_jeep_idle_volume":
		p = [
		    [0.00,  1.00],
		    [0.05,  0.90],
        [0.10,  0.85],
        [0.25,  0.45],
        [0.30,  0.15],
        [0.35,  0.00],
        [1.00,  0.00]
		];
		break;
		
		//SpecOps_Jeep_Slow
		case "so_jeep_slow_pitch":
		p = [
        [0.00,  0.38],
        [0.10,  0.40],
        [0.40,  0.45],
        [0.45,  0.50],
        [0.55,  0.55],
        [0.70,  0.60],
        [1.00,  0.80]
    ];
		break;
		
		case "so_jeep_slow_volume":
		p = [
        [0.00,  0.01],
        [0.10,  0.50],
        [0.35,	0.75],
        [0.55,  1.00],
        [0.70,  0.60],
        [0.80,  0.45],
        [1.00,  0.01]
    ]; 
		break;

//SpecOps_Jeep_Medium
		case "so_jeep_medium_pitch":
		p = [
        [0.00,  0.25],
        [0.50,  0.30],
        [0.65,  0.35],
        [0.75,  0.40],
				[0.85,  0.45],
        [1.00,  0.50]
    ];
		break;
		
		case "so_jeep_medium_volume":
		p = [
        [0.00,  0.00],
        [0.40,  0.20],
        [0.60,	0.60],
        [0.75,	0.90],
        [1.00,  1.00]
    ]; 
		break;
		
//Hind (Player)
	//Hind Move
		case "player_hind_move_volume":
		p = [
        [0.000,  0.000],
        [0.300,  0.000],
        [0.600,  0.350],
        [0.700,  0.900],
        [1.000,  1.000]
    ]; 
		break;
		
		case "player_hind_move_pitch":
		p = [
        [0.000,  0.400],
        [0.500,  0.400],
        [0.750,  0.500],
        [1.000,  0.700]
    ];  
		break;

	//Hind Hover		
		case "player_hind_hover_volume":
		p = [
        [0.000,  1.000],
        [1.000,  1.000]
    ];  
		break;
		
		case "player_hind_hover_pitch":
		p = [
        [0.000,  0.400],
        [0.500,  0.500],
        [1.000,  0.700]
    ];  
		break;

//Hind (Enemy)
	//Hind Move
		case "enemy_hind_move_volume":
		p = [
        [0.000,  1.000],
        [1.000,  1.000]
    ];  
		break;

//Mi17 (Enemy)
	//Mi17 Move
		case "mi17_move_volume":
		p = [
        [0.000,  0.750],
        [0.300,  0.850],
        [0.600,  0.950],
        [0.700,  0.990],
        [1.000,  1.000]
    ]; 
		break;
		
		case "mi17_move_pitch":
		p = [
        [0.000,  0.400],
        [0.500,  0.600],
        [1.000,  0.700]
    ];  
		break;

	//Mi17 Hover		
		case "mi17_hover_volume":
		p = [
        [0.000,  1.000],
        [1.000,  0.750]
    ];  
		break;
		
		case "mi17_hover_pitch":
		p = [
        [0.000,  0.400],
        [0.500,  0.600],
        [1.000,  0.700]
    ];  
		break;
		
		
// Dubai Littlebird (Resturant)
	//Littlebird Move
		case "dubai_littlebird_move_volume":
		p = [
        [0.000,  0.750],
        [0.300,  0.850],
        [0.600,  0.950],
        [0.700,  0.990],
        [1.000,  1.000]
    ]; 
		break;
		
		case "dubai_littlebird_move_pitch":
		p = [
        [0.000,  0.400],
        [0.500,  0.600],
        [1.000,  0.700]
    ];  
		break;

	//Mi17 Hover		
		case "dubai_littlebird_hover_volume":
		p = [
        [0.000,  1.000],
        [1.000,  0.750]
    ];  
		break;
		
		case "dubai_littlebird_hover_pitch":
		p = [
        [0.000,  0.400],
        [0.500,  0.600],
        [1.000,  0.700]
    ];  
		break;

//Zodiac (Player)
	//Zodiac Rampup
		case "zodiac_player_rampup_pitch":
		p = [
				[0.00,  0.45],
				[0.50,  0.50],
				[1.00,  1.00]
		];
		break;
		
		case "zodiac_player_rampup_volume":
		p = [
				[0.00,  0.00],
				[0.25,  0.50],
				[0.85,  1.00],
				[1.00,  1.00]
		];
		break;

	//Zodiac Rampdown
		case "zodiac_player_rampdown_pitch":
		p = [
				[0.00,  0.50],
				[0.25,  0.55],
				[1.00,  0.60]
		];
		break;
		
		case "zodiac_player_rampdown_volume":
		p = [
				[0.000,  1.000],
				[0.250,  0.850],
				[0.500,  0.500],
				[1.000,  0.250]
		];
		break;

	//Zodiac Idle		
		case "zodiac_player_idle_pitch":
		p = [
				[0.00,  0.50],
				[0.02,  0.65],
				[0.10,  0.75],
				[0.20,  0.85],
				[1.00,  1.00]
		];
		break;
		
		case "zodiac_player_idle_volume":
		p = [
		    [0.00,  0.75],
		    [0.05,  1.00],
        [0.10,  0.85],
        [0.25,  0.45],
        [0.30,  0.15],
        [0.35,  0.00],
        [1.00,  0.00]
		];
		break;

	//Zodiac Motor Bottom
		case "zodiac_player_bottom_pitch":
		p = [
        [0.00,  0.35],
        [0.10,  0.40],
        [0.30,  0.50],
        [0.35,  0.60],
        [0.45,  0.65],
        [0.60,  0.70],
        [1.00,  0.75]
    ];
		break;
		
		case "zodiac_player_bottom_volume":
		p = [
        [0.00,  0.75],
        [0.15,	0.75],
        [0.35,  1.00],
        [0.45,  0.35],
        [0.55,  0.25],
        [0.60,  0.20],
        [0.70,  0.15],
        [1.00,  0.00]
    ]; 
		break;

	//Zodiac Motor Slow
		case "zodiac_player_slow_pitch":
		p = [
        [0.00,  0.20],
        [0.40,  0.35],
        [0.45,  0.45],
        [0.55,  0.50],
        [0.70,  0.60],
        [1.00,  0.80]
    ];
		break;
		
		case "zodiac_player_slow_volume":
		p = [
        [0.00,  0.25],
        [0.10,  0.50],
        [0.35,	0.75],
        [0.55,  1.00],
        [0.70,  0.50],
        [0.80,  0.35],
        [1.00,  0.20]
    ]; 
		break;

	//Zodiac Motor Medium
		case "zodiac_player_medium_pitch":
		p = [
        [0.00,  0.35],
        [0.50,  0.45],
        [0.65,  0.50],
        [0.75,  0.60],
				[0.85,  0.70],
        [1.00,  0.70]
    ];
		break;
		
		case "zodiac_player_medium_volume":
		p = [
        [0.00,  0.00],
        [0.40,  0.20],
        [0.60,	0.50],
        [0.75,  1.00],
        [0.80,  0.50],
        [0.90,  0.25],
        [1.00,  0.10]
    ]; 
		break;

	//Zodiac Motor Fast
		case "zodiac_player_fast_pitch":
		p = [
        [0.00,  0.45],
        [0.70,  0.45],
        [0.85,  0.50],
        [0.95,  0.55],
        [1.00,  0.70]
    ];
		break;
		
		case "zodiac_player_fast_volume":
		p = [
        [0.00,  0.00],
        [0.60,  0.00],
        [0.70,	0.25],
        [0.85,  0.50],
        [0.95,  0.50],
        [1.00,  1.00]
    ]; 
		break;

	//Zodiac Water Idle		
		case "zodiac_plr_water_idle_pitch":
		p = [
				[0.00,  0.50],
				[1.00,  0.50]
		];
		break;
		
		case "zodiac_plr_water_idle_volume":
		p = [
		    [0.00,  1.00],
		    [0.10,  0.50],
        [0.15,  0.25],
        [0.20,  0.15],
        [0.35,  0.00],
        [1.00,  0.00]
		];
		break;

	//Zodiac Water Bottom
		case "zodiac_plr_water_botm_pitch":
		p = [
        [0.00,  0.45],
        [0.10,  0.50],
        [0.30,  0.50],
        [1.00,  0.50]
    ];
		break;
		
		case "zodiac_plr_water_botm_volume":
		p = [
        [0.00,  0.00],
        [0.15,	0.25],
        [0.35,  1.00],
        [0.45,  0.35],
        [0.55,  0.25],
        [0.60,  0.20],
        [0.70,  0.15],
        [1.00,  0.00]
    ];
		break;

	//Zodiac Water Slow
		case "zodiac_plr_water_slow_pitch":
		p = [
        [0.00,  0.45],
        [0.10,  0.50],
        [0.30,  0.50],
        [1.00,  0.50]
    ];
		break;
		
		case "zodiac_plr_water_slow_volume":
		p = [
        [0.00,  0.00],
        [0.10,  0.25],
        [0.35,	0.75],
        [0.55,  1.00],
        [0.70,  0.50],
        [0.80,  0.35],
        [1.00,  0.20]
    ]; 
		break;

	//Zodiac Water Medium
		case "zodiac_plr_water_med_pitch":
		p = [
        [0.00,  0.45],
        [0.10,  0.50],
        [0.30,  0.50],
        [1.00,  0.50]
    ];
		break;
		
		case "zodiac_plr_water_med_volume":
		p = [
        [0.00,  0.00],
        [0.40,  0.20],
        [0.60,	0.50],
        [0.75,  1.00],
        [0.80,  0.50],
        [0.90,  0.25],
        [1.00,  0.10]
    ]; 
		break;

	//Zodiac Water Fast
		case "zodiac_plr_water_fast_pitch":
		p = [
        [0.00,  0.45],
        [0.10,  0.50],
        [0.30,  0.50],
        [1.00,  0.50]
    ];
		break;
		
		case "zodiac_plr_water_fast_volume":
		p = [
        [0.00,  0.00],
        [0.60,  0.00],
        [0.70,	0.50],
        [0.85,  1.00],
        [1.00,  1.00]
    ]; 
		break;

//SDV (Player)
	//SDV Rampup
		case "sdv_plr_rampup_pitch":
		p = [
				[0.00,  0.50],
				[0.50,  0.50],
				[1.00,  0.50]
		];
		break;
		
		case "sdv_plr_rampup_volume":
		p = [
				[0.00,  1.00],
				[1.00,  1.00]
		];
		break;

	//SDV Rampdown
		case "sdv_plr_rampdown_pitch":
		p = [
				[0.00,  0.50],
				[0.50,  0.50],
				[1.00,  0.50]
		];
		break;
		
		case "sdv_plr_rampdown_volume":
		p = [
				[0.000,  1.00],
				[1.000,  1.00]
		];
		break;

	//SDV Motor Slow
		case "sdv_plr_motor_slow_pitch":
		p = [
        [0.00,  0.25],
        [0.15,  0.40],
        [0.30,  0.50],
        [0.60,  0.55],
        [0.75,  0.65],
        [1.00,  0.75]
    ];
		break;
		
		case "sdv_plr_motor_slow_volume":
		p = [
        [0.00,  0.00],
        [0.05,  0.50],
        [0.15,	0.75],
        [0.25,  1.00],
        [0.35,  0.50],
        [0.45,  0.25],
        [0.55,  0.20],
        [1.00,  0.00]
    ]; 
		break;

	//SDV Motor Medium
		case "sdv_plr_motor_med_pitch":
		p = [
        [0.00,  0.50],
        [0.60,  0.50],
        [0.75,  0.65],
        [1.00,  0.75]
    ];
		break;
		
		case "sdv_plr_motor_med_volume":
		p = [
        [0.00,  0.00],
        [0.25,  0.10],
        [0.35,	0.50],
        [0.45,  1.00],
        [0.65,  1.00],
        [0.75,  0.75],
        [0.95,  0.25],
        [1.00,  0.10]
    ]; 
		break;

	//SDV Motor Fast
		case "sdv_plr_motor_fast_pitch":
		p = [
        [0.00,  0.40],
        [0.60,  0.40],
        [0.70,  0.45],
        [0.85,  0.50],
        [1.00,  0.50]
    ];
		break;
		
		case "sdv_plr_motor_fast_volume":
		p = [
        [0.00,  0.00],
        [0.60,  0.35],
        [0.70,	0.55],
        [0.85,  0.85],
        [1.00,  1.00]
    ]; 
		break;

	//SDV Water Slow
		case "sdv_plr_water_slow_pitch":
		p = [
        [0.00,  0.45],
        [0.10,  0.50],
        [0.30,  0.50],
        [1.00,  0.50]
    ];
		break;
		
		case "sdv_plr_water_slow_volume":
		p = [
        [0.00,  0.00],
        [0.10,  0.25],
        [0.45,	0.75],
        [0.65,  1.00],
        [0.70,  0.50],
        [0.80,  0.35],
        [1.00,  0.20]
    ]; 
		break;

	//SDV Water Medium
		case "sdv_plr_water_med_pitch":
		p = [
        [0.00,  0.45],
        [0.10,  0.50],
        [0.30,  0.50],
        [0.80,  0.50],
        [1.00,  0.55]
    ];
		break;
		
		case "sdv_plr_water_med_volume":
		p = [
        [0.00,  0.00],
        [0.50,  0.00],
        [0.75,  0.00],
        [0.85,  0.25],
        [0.95,  0.50],
        [1.00,  1.00]
    ]; 
		break;

	}
	return p;
}