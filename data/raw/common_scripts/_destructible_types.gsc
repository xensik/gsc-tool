#include common_scripts\_destructible;
#using_animtree( "destructibles" );

makeType( destructibleType ) 
{
	//println( destructibleType );

	// if it's already been created dont create it again
	infoIndex = getInfoIndex( destructibleType );
	if ( infoIndex >= 0 )
		return infoIndex;

	switch( destructibleType )
	{
		case "rus_vx_gas_canister":
			rus_vx_gas_canister( destructibleType );
			break;
		case "prop_ac_prs_enm_barge_a_1":
			prop_ac_prs_enm_barge_a_1();
			break;
		case "prop_ac_prs_enm_barge_a_2":
			prop_ac_prs_enm_barge_a_2();
			break;
		case "prop_ac_prs_enm_con_digger_a":
			prop_ac_prs_enm_con_digger_a();
			break;
		case "prop_ac_prs_enm_con_dump_truck_a":
			prop_ac_prs_enm_con_dump_truck_a();
			break;
		case "prop_ac_prs_enm_fuel_tank_a":
			prop_ac_prs_enm_fuel_tank_a();
			break;
		case "vehicle_jeep":
			vehicle_jeep( destructibleType );
			break;
		case "vehicle_uaz_van_destructible":
			vehicle_uaz_van( destructibleType );
			break;
		case "prop_ac_prs_enm_hanger_a":
			prop_ac_prs_enm_hanger_a();
			break;
		case "prop_ac_prs_enm_maz_a":
			prop_ac_prs_enm_maz_a();
			break;
		case "prop_ac_prs_enm_mi26_halo_a":
			prop_ac_prs_enm_mi26_halo_a();
			break;
		case "prop_ac_prs_enm_mstas_a":
			prop_ac_prs_enm_mstas_a();
			break;
		case "prop_ac_prs_enm_radar_maz_a":
			prop_ac_prs_enm_radar_maz_a();
			break;
		case "prop_ac_prs_enm_s300v_a":
			prop_ac_prs_enm_s300v_a();
			break;
		case "prop_ac_prs_enm_storage_bld_a_1":
			prop_ac_prs_enm_storage_bld_a_1();
			break;
		case "prop_ac_prs_enm_storage_bld_a_2":
			prop_ac_prs_enm_storage_bld_a_2();
			break;
		case "prop_ac_prs_enm_storage_bld_b":
			prop_ac_prs_enm_storage_bld_b();
			break;
		case "vehicle_semi_truck":
			vehicle_semi_truck();
			break;
		case "prop_ac_prs_enm_tent_a":
			prop_ac_prs_enm_tent_a();
			break;
		case "prop_ac_prs_enm_tent_b":
			prop_ac_prs_enm_tent_b();
			break;
		case "prop_ac_prs_enm_tent_c":
			prop_ac_prs_enm_tent_c();
			break;
		case "prop_ac_prs_enm_truck_a":
			prop_ac_prs_enm_truck_a();
			break;
		case "prop_ac_prs_enm_cargo_crate_a_1":
            prop_ac_prs_enm_cargo_crate_a_1();
            break;
		case "prop_ac_prs_enm_cargo_crate_a_2":
            prop_ac_prs_enm_cargo_crate_a_2();
            break;
		case "prop_ac_prs_enm_crates_a_1":
            prop_ac_prs_enm_crates_a_1();
            break;
		case "prop_ac_prs_enm_crates_a_2":
            prop_ac_prs_enm_crates_a_2();
            break;
		case "prop_ac_prs_enm_crates_b_1":
            prop_ac_prs_enm_crates_b_1();
            break;
		case "prop_ac_prs_enm_crates_b_2":
            prop_ac_prs_enm_crates_b_2();
            break;
        case "prop_ac_prs_enm_mobile_crane_a":
	        prop_ac_prs_enm_mobile_crane_a();
	        break;
		case "prop_ac_prs_enm_landing_craft_a":
	        prop_ac_prs_enm_landing_craft_a();
	        break;
		case "prop_ac_prs_enm_speed_boat_a":
	        prop_ac_prs_enm_speed_boat_a();
	        break;
	    case "prop_ac_prs_prp_satellite_dish_a_dish":
	        prop_ac_prs_prp_satellite_dish_a_dish();
	        break;
	    case "prop_ac_prs_fps_hc_extc_balcony_a1":
	        prop_ac_prs_fps_hc_extc_balcony_a1();
	        break;
	    case "prop_ac_prs_fps_hc_extc_balcony_a2":
	        prop_ac_prs_fps_hc_extc_balcony_a2();
	        break;
	    case "prop_ac_prs_fps_hc_extc_balcony_a3":
	        prop_ac_prs_fps_hc_extc_balcony_a3();
	        break;
	    case "prop_ac_prs_fps_hc_extc_balcony_b1":
	        prop_ac_prs_fps_hc_extc_balcony_b1();
	        break;
	    case "prop_ac_prs_fps_hc_extc_balcony_b2":
	        prop_ac_prs_fps_hc_extc_balcony_b2();
	        break;
	    case "prop_ac_prs_fps_hc_extc_balcony_b3":
	        prop_ac_prs_fps_hc_extc_balcony_b3();
	        break;
	    case "prop_ac_prs_fps_hc_extc_balcony_c1":
	        prop_ac_prs_fps_hc_extc_balcony_c1();
	        break;
	    case "prop_ac_prs_fps_hc_extc_balcony_c2":
	        prop_ac_prs_fps_hc_extc_balcony_c2();
	        break;
	    case "prop_ac_prs_fps_hc_extc_column_b_a1":
	        prop_ac_prs_fps_hc_extc_column_b_a1();
	        break;
	    case "prop_ac_prs_fps_hc_extc_column_b_a2":
	        prop_ac_prs_fps_hc_extc_column_b_a2();
	        break;
	    case "prop_ac_prs_fps_hc_extc_column_b_a3":
	        prop_ac_prs_fps_hc_extc_column_b_a3();
	        break;
	    case "prop_ac_prs_fps_hc_extc_column_t_a1":
	        prop_ac_prs_fps_hc_extc_column_t_a1();
	        break;
	    case "prop_ac_prs_fps_hc_extc_column_t_a2":
	        prop_ac_prs_fps_hc_extc_column_t_a2();
	        break;
	    case "prop_ac_prs_fps_hc_extc_column_t_a3":
	        prop_ac_prs_fps_hc_extc_column_t_a3();
	        break;
	   	case "prop_ac_prs_enm_missile_boat_a":
	        prop_ac_prs_enm_missile_boat_a();
	        break;
		case "toy_glass120x110":
			toy_glass( "120x110" );
			break;
		case "vehicle_mini_destructible_blue":
			vehicle_mini( "blue" );
			break;
		case "vehicle_mini_destructible_gray":
			vehicle_mini( "gray" );
			break;
		case "vehicle_mini_destructible_white":
			vehicle_mini( "white" );
			break;
		case "vehicle_mini_destructible_red":
			vehicle_mini( "red" );
			break;
		case "toy_glass120x44":
			toy_glass( "120x44" );
			break;
		case "toy_glass56x59":
			toy_glass( "56x59" );
			break;
		case "toy_glass74x110":
			toy_glass( "74x110" );
			break;
		case "toy_glass74x44":
			toy_glass( "74x44" );
			break;
		case "toy_dt_mirror":
			toy_dt_mirror( "" );
			break;
		case "toy_dt_mirror_large":
			toy_dt_mirror( "_large" );
			break;
		case "toy_icbm_consolemonitor1":
			toy_icbm_consolemonitor( "1" );	
			break;
		case "toy_icbm_consolemonitor2":
			toy_icbm_consolemonitor( "2" );	
			break;
		case "toy_icbm_consolemonitor3":
			toy_icbm_consolemonitor( "3" );	
			break;
		case "toy_icbm_consolemonitor4":
			toy_icbm_consolemonitor( "4" );	
			break;
		case "toy_icbm_consolemonitor5":
			toy_icbm_consolemonitor( "5" );	
			break;
		case "toy_icbm_consolemonitor6":
			toy_icbm_consolemonitor( "6" );	
			break;
		case "toy_tubetv_tv1":
			toy_tubetv_( "tv1" );
			break;
		case "toy_tubetv_tv2":
			toy_tubetv_( "tv2" );
			break;
		case "toy_tv_flatscreen_01":
			toy_tvs_flatscreen( "01", "" );
			break;
		case "toy_tv_flatscreen_02":
			toy_tvs_flatscreen( "02", "" );
			break;
		case "toy_tv_flatscreen_wallmount_01":
			toy_tvs_flatscreen( "01", "wallmount_" );
			break;
		case "toy_tv_flatscreen_wallmount_01_sturdy":
			toy_tvs_flatscreen_sturdy( "01", "wallmount_" );
			break;
		case "toy_tv_flatscreen_wallmount_02":
			toy_tvs_flatscreen( "02", "wallmount_" );
			break;
		case "toy_transformer_ratnest01":
			toy_transformer_ratnest01( destructibleType );
			break;
		case "toy_transformer_small01":
			toy_transformer_small01( destructibleType );
			break;
		case "toy_generator":
			toy_generator( destructibleType );
			break;
		case "toy_generator_on":
			toy_generator_on( destructibleType );
			break;
		case "toy_oxygen_tank_01":
			toy_oxygen_tank( "01" );
			break;
		case "toy_oxygen_tank_02":
			toy_oxygen_tank( "02" );
			break;
		case "toy_electricbox2":
			toy_electricbox2( destructibleType );
			break;
		case "toy_electricbox4":
			toy_electricbox4( destructibleType );
			break;
		case "toy_airconditioner":
			toy_airconditioner( destructibleType );
			break;
		case "toy_ceiling_fan":
			toy_ceiling_fan( destructibleType );
			break;
		case "toy_wall_fan":
			toy_wall_fan( destructibleType );
			break;
		case "toy_propane_tank02":
			toy_propane_tank02( destructibleType );
			break;
		case "toy_propane_tank02_small":
			toy_propane_tank02_small( destructibleType );
			break;
		case "toy_copier":
			toy_copier( destructibleType );
			break;
		case "toy_firehydrant":
			toy_firehydrant( destructibleType );
			break;
		case "toy_parkingmeter":
			toy_parkingmeter( destructibleType );
			break;
		case "toy_mailbox":
			toy_mailbox( destructibleType );
			break;
		case "toy_mailbox2_black":
			toy_mailbox2( "black" );
			break;
		case "toy_mailbox2_green":
			toy_mailbox2( "green" );
			break;
		case "toy_mailbox2_yellow":
			toy_mailbox2( "yellow" );
			break;
		case "toy_newspaper_stand_red":
			toy_newspaper_stand_red( destructibleType );
			break;
		case "toy_newspaper_stand_blue":
			toy_newspaper_stand_blue( destructibleType );
			break;
		case "toy_filecabinet":
			toy_filecabinet( destructibleType );
			break;
		case "toy_trashbin_01":
			toy_trashbin_01( destructibleType );
			break;
		case "toy_trashbin_02":
			toy_trashbin_02( destructibleType );
			break;
		case "toy_trashbag1_white":
			toy_trashbag1( "white" );
			break;
		case "toy_trashbag1_black":
			toy_trashbag1( "black" );
			break;
		case "toy_trashbag1_green":
			toy_trashbag1( "green" );
			break;
		case "toy_recyclebin_01":
			toy_recyclebin_01( destructibleType );
			break;
		case "toy_trashcan_metal_closed":
			toy_trashcan_metal_closed( destructibleType );
			break;
		case "toy_water_collector":
			toy_water_collector( destructibleType );
			break;
		case "toy_foliage_tree_oak_1":
			toy_foliage_tree_oak_1( destructibleType );
			break;
		case "toy_paris_tree_plane_large":
			toy_paris_tree_plane_large( destructibleType );
			break;
		case "toy_usa_gas_station_trash_bin_01":
			toy_usa_gas_station_trash_bin_01( destructibleType );
			break;
		case "toy_usa_gas_station_trash_bin_02":
			toy_usa_gas_station_trash_bin_02( destructibleType );
			break;
		case "toy_light_ceiling_round":
			toy_light_ceiling_round( destructibleType );
			break;
		case "toy_light_ceiling_fluorescent":
			toy_light_ceiling_fluorescent( destructibleType );
			break;
		case "toy_light_ceiling_fluorescent_spotlight":
			toy_light_ceiling_fluorescent_spotlight( destructibleType );
			break;
		case "toy_light_ceiling_fluorescent_single":
			toy_light_ceiling_fluorescent_single( destructibleType );
			break;
		case "toy_light_ceiling_fluorescent_single_spotlight":
			toy_light_ceiling_fluorescent_single_spotlight( destructibleType );
			break;
		case "toy_bookstore_bookstand4_books":
			toy_bookstore_bookstand4_books( destructibleType );
			break;
		case "toy_locker_double":
			toy_locker_double( destructibleType );
			break;
		case "toy_chicken":
			toy_chicken( "" );
			break;
		case "toy_chicken_white":
			toy_chicken( "_white" );
			break;
		case "toy_chicken_black_white":
			toy_chicken( "_black_white" );
			break;
		case "toy_luggage_01":
			toy_hide_with_fx( "toy_luggage_01", "luggage1_lod0", "maps/hijack/luggage_1_des_hjk", 120 );
			break;
		case "toy_luggage_02":
			toy_hide_with_fx( "toy_luggage_02", "luggage2_lod0", "maps/hijack/luggage_2_des_hjk", 120 );
			break;
		case "toy_luggage_03":
			toy_hide_with_fx( "toy_luggage_03", "luggage3_lod0", "maps/hijack/luggage_3_des_hjk", 120 );
			break;
		case "toy_luggage_04":
			toy_hide_with_fx( "toy_luggage_04", "luggage4_lod0", "maps/hijack/luggage_4_des_hjk", 120 );
			break;
		case "toy_com_cardboardbox_dusty_05":
			toy_hide_with_fx( "toy_com_cardboardbox_dusty_05", "cardboardbox_5_lod0", "props/cardboardbox01_snacks_exp", 30 );
			break;
		case "toy_com_cardboardboxshortclosed_1":
			toy_hide_with_fx( "toy_com_cardboardboxshortclosed_1", "cardboardboxshortclosed_1_lod0", "props/cardboardboxshortclosed_snacks_exp", 30 );
			break;
		case "intro_gate_column_02_dest_01":
			toy_intro_concrete_chipaway("intro_gate_column_02_dest_01", 12);
			break;
		case "intro_concrete_junkyardwall_01":
			toy_intro_concrete_chipaway("intro_concrete_junkyardwall_01", 9);
			break;
		case "intro_concrete_kneehighwall_01":
			toy_intro_concrete_chipaway("intro_concrete_kneehighwall_01", 8);
			break;
		case "dub_lobby_fish_sculpture_left_orange":
			toy_dubai_fish_sculpture("dub_lobby_fish_sculpture_left_orange", "orange", 40);
			break;
		case "dub_lobby_fish_sculpture_right_orange":
			toy_dubai_fish_sculpture("dub_lobby_fish_sculpture_right_orange", "orange", 40);
			break;	
		case "dub_lobby_fish_sculpture_left_blue":
			toy_dubai_fish_sculpture("dub_lobby_fish_sculpture_left_blue", "blue", 45);
			break;
		case "dub_lobby_fish_sculpture_right_blue":
			toy_dubai_fish_sculpture("dub_lobby_fish_sculpture_right_blue", "blue", 45);
			break;	
		case "dub_lobby_fish_sculpture_left_purple":
			toy_dubai_fish_sculpture("dub_lobby_fish_sculpture_left_purple", "purple", 39);
			break;
		case "dub_lobby_fish_sculpture_right_purple":
			toy_dubai_fish_sculpture("dub_lobby_fish_sculpture_right_purple", "purple", 39);
			break;
		case "vehicle_ac130_80s_sedan1_yel":
			vehicle_ac130_80s_sedan1( "yel" );
			break;
		case "vehicle_bus_destructible":
			vehicle_bus_destructible( destructibleType );
			break;
		case "vehicle_80s_sedan1_green":
			vehicle_80s_sedan1( "green" );
			break;
		case "vehicle_80s_sedan1_red":
			vehicle_80s_sedan1( "red" );
			break;
		case "vehicle_80s_sedan1_silv":
			vehicle_80s_sedan1( "silv" );
			break;
		case "vehicle_80s_sedan1_tan":
			vehicle_80s_sedan1( "tan" );
			break;
		case "vehicle_80s_sedan1_yel":
			vehicle_80s_sedan1( "yel" );
			break;
		case "vehicle_80s_sedan1_brn":
			vehicle_80s_sedan1( "brn" );
			break;
		case "vehicle_80s_hatch1_green":
			vehicle_80s_hatch1( "green" );
			break;
		case "vehicle_80s_hatch1_red":
			vehicle_80s_hatch1( "red" );
			break;
		case "vehicle_80s_hatch1_silv":
			vehicle_80s_hatch1( "silv" );
			break;
		case "vehicle_80s_hatch1_tan":
			vehicle_80s_hatch1( "tan" );
			break;
		case "vehicle_80s_hatch1_yel":
			vehicle_80s_hatch1( "yel" );
			break;
		case "vehicle_80s_hatch1_brn":
			vehicle_80s_hatch1( "brn" );
			break;
		case "vehicle_80s_hatch2_green":
			vehicle_80s_hatch2( "green" );
			break;
		case "vehicle_80s_hatch2_red":
			vehicle_80s_hatch2( "red" );
			break;
		case "vehicle_80s_hatch2_silv":
			vehicle_80s_hatch2( "silv" );
			break;
		case "vehicle_80s_hatch2_tan":
			vehicle_80s_hatch2( "tan" );
			break;
		case "vehicle_80s_hatch2_yel":
			vehicle_80s_hatch2( "yel" );
			break;
		case "vehicle_80s_hatch2_brn":
			vehicle_80s_hatch2( "brn" );
			break;
		case "vehicle_80s_wagon1_green":
			vehicle_80s_wagon1( "green" );
			break;
		case "vehicle_80s_wagon1_red":
			vehicle_80s_wagon1( "red" );
			break;
		case "vehicle_80s_wagon1_silv":
			vehicle_80s_wagon1( "silv" );
			break;
		case "vehicle_80s_wagon1_tan":
			vehicle_80s_wagon1( "tan" );
			break;
		case "vehicle_80s_wagon1_yel":
			vehicle_80s_wagon1( "yel" );
			break;
		case "vehicle_80s_wagon1_brn":
			vehicle_80s_wagon1( "brn" );
			break;
		case "vehicle_civ_car_a_1":
			vehicle_civ_car_a( 1 );
			break;
		case "vehicle_civ_car_a_2":
			vehicle_civ_car_a( 2 );
			break;
		case "vehicle_civ_car_a_3":
			vehicle_civ_car_a( 3 );
			break;
		case "vehicle_civ_car_a_4":
			vehicle_civ_car_a( 4 );
			break;
		case "vehicle_civ_car_a_5":
			vehicle_civ_car_a( 5 );
			break;
		case "vehicle_civ_car_a_6":
			vehicle_civ_car_a( 6 );
			break;
		case "vehicle_civ_car_a_7":
			vehicle_civ_car_a( 7 );
			break;
		case "vehicle_civ_car_a_8":
			vehicle_civ_car_a( 8 );
			break;
		case "vehicle_civ_car_a_9":
			vehicle_civ_car_a( 9 );
			break;
		case "vehicle_civ_car_a_10":
			vehicle_civ_car_a( 10 );
			break;
		case "vehicle_civ_car_a_11":
			vehicle_civ_car_a( 11 );
			break;
		case "vehicle_civ_car_a_12":
			vehicle_civ_car_a( 12 );
			break;
		case "vehicle_civ_car_a_13":
			vehicle_civ_car_a( 13 );
			break;
		case "vehicle_small_hatch_blue":
			vehicle_small_hatch( "blue" );
			break;
		case "vehicle_london_cab_black":
			vehicle_london_cab_black();
			break;
		case "vehicle_small_hatch_green":
			vehicle_small_hatch( "green" );
			break;
		case "vehicle_small_hatch_turq":
			vehicle_small_hatch( "turq" );
			break;
		case "vehicle_small_hatch_white":
			vehicle_small_hatch( "white" );
			break;
		case "vehicle_pickup":
			vehicle_pickup( destructibleType );
			break;
		case "vehicle_hummer":
			vehicle_hummer( destructibleType );
			break;
		case "vehicle_t72":
			vehicle_t72( destructibleType );
			break;
		case "vehicle_btr":
			vehicle_btr( destructibleType );
			break;
		case "vehicle_gaz":
			vehicle_gaz( destructibleType );
			break;
		case "vehicle_gaz_harbor":
			vehicle_gaz_harbor( destructibleType );
			break;
		case "vehicle_moving_truck":
		case "vehicle_moving_truck_thai":
			vehicle_moving_truck( destructibleType );
			break;
		case "vehicle_subway_cart":
			vehicle_subway_cart( destructibleType );
			break;
		case "vehicle_subway_cart_windows":
			vehicle_subway_cart_windows( destructibleType );
			break;
		case "vehicle_subway_cart_windows_small":
			vehicle_subway_cart_windows_small( destructibleType );
			break;
		case "vehicle_bm21_mobile_bed":
			vehicle_bm21( destructibleType, "vehicle_bm21_mobile_bed_dstry" );
			break;
		case "vehicle_bm21_cover":
			vehicle_bm21( destructibleType, "vehicle_bm21_mobile_cover_dstry" );
			break;
		case "vehicle_luxurysedan_2008":
			vehicle_luxurysedan( "", false);
			break;
		case "vehicle_luxurysedan_2008_streamed":
			vehicle_luxurysedan( "", true);
			break;			
		case "vehicle_luxurysedan_2008_gray":
			vehicle_luxurysedan( "_gray", false);
			break;
		case "vehicle_luxurysedan_2008_white":
			vehicle_luxurysedan( "_white", false);
			break;
		case "vehicle_uk_truck":
			vehicle_uk_truck( destructibleType );
			break;
		case "vehicle_uk_police_estate":
			vehicle_uk_police_estate( destructibleType );
			break;
		case "vehicle_uaz_winter":
			vehicle_uaz_winter( destructibleType );
			break;
		case "vehicle_uaz_fabric":
			vehicle_uaz_fabric( destructibleType );
			break;
		case "vehicle_uaz_hardtop":
			vehicle_uaz_hardtop( destructibleType );
			break;
		case "vehicle_uaz_open":
			vehicle_uaz_open( destructibleType );
			break;
		case "vehicle_india_suv_w":
			vehicle_india_suv( "w" );
			break;
		case "vehicle_india_suv_b":
			vehicle_india_suv( "b" );
			break;
		//naming is bad but need to have new version without breaking old.
		case "vehicle_india_compact_destructible_gray":
			vehicle_india_compact_destructible( "gray" );
			break;
		case "vehicle_india_compact_destructible_red":
			vehicle_india_compact_destructible( "red" );
			break;
		case "vehicle_india_compact_destructible_brown":
			vehicle_india_compact_destructible( "brown" );
			break;
		case "vehicle_india_compact_destructible_blue":
			vehicle_india_compact_destructible( "blue" );
			break;
		case "vehicle_tuk_tuk":
			vehicle_tuk_tuk( destructibleType );
			break;
		case "vehicle_india_rickshaw":
			vehicle_india_rickshaw( destructibleType );
			break;
		case "vehicle_policecar":
			vehicle_policecar( destructibleType );
			break;
		case "vehicle_policecar_russia":
			vehicle_policecar_russia( destructibleType );
			break;
		case "vehicle_taxi":
			vehicle_taxi( destructibleType );
			break;
		case "vehicle_taxi_dubai":
			vehicle_taxi_dubai( destructibleType );
			break;
		case "vehicle_mig29_landed":
			vehicle_mig29_landed( destructibleType );
			break;
		case "vehicle_mack_truck_short_snow":
			vehicle_mack_truck_short( "snow" );
			break;
		case "vehicle_mack_truck_short_green":
			vehicle_mack_truck_short( "green" );
			break;
		case "vehicle_mack_truck_short_white":
			vehicle_mack_truck_short( "white" );
			break;
		case "vehicle_motorcycle_01":
			vehicle_motorcycle( "01" );
			break;
		case "vehicle_motorcycle_02":
			vehicle_motorcycle( "02" );
			break;
		case "vehicle_scooter_vespa":
			vehicle_scooter( "vehicle_scooter_vespa" );
			break;
		case "vehicle_subcompact_black":
			vehicle_subcompact( "black" );
			break;
		case "vehicle_subcompact_blue":
			vehicle_subcompact( "blue" );
			break;
		case "vehicle_subcompact_dark_gray":
			vehicle_subcompact( "dark_gray" );
			break;
		case "vehicle_subcompact_deep_blue":
			vehicle_subcompact( "deep_blue" );
			break;
		case "vehicle_subcompact_gold":
			vehicle_subcompact( "gold" );
			break;
		case "vehicle_subcompact_gray":
			vehicle_subcompact( "gray" );
			break;
		case "vehicle_subcompact_green":
			vehicle_subcompact( "green" );
			break;
		case "vehicle_subcompact_mica":
			vehicle_subcompact( "mica" );
			break;
		case "vehicle_subcompact_slate":
			vehicle_subcompact( "slate" );
			break;
		case "vehicle_subcompact_tan":
			vehicle_subcompact( "tan" );
			break;
		case "vehicle_subcompact_white":
			vehicle_subcompact( "white" );
			break;
		case "vehicle_coupe_black":
			vehicle_coupe( "black" );
			break;
		case "vehicle_coupe_blue":
			vehicle_coupe( "blue" );
			break;
		case "vehicle_coupe_dark_gray":
			vehicle_coupe( "dark_gray" );
			break;
		case "vehicle_coupe_deep_blue":
			vehicle_coupe( "deep_blue" );
			break;
		case "vehicle_coupe_gold":
			vehicle_coupe( "gold" );
			break;
		case "vehicle_coupe_gray":
			vehicle_coupe( "gray" );
			break;
		case "vehicle_coupe_green":
			vehicle_coupe( "green" );
			break;
		case "vehicle_coupe_mica":
			vehicle_coupe( "mica" );
			break;
		case "vehicle_coupe_slate":
			vehicle_coupe( "slate" );
			break;
		case "vehicle_coupe_tan":
			vehicle_coupe( "tan" );
			break;
		case "vehicle_coupe_white":
			vehicle_coupe( "white" );
			break;
		case "vehicle_van_black":
			vehicle_van( "black" );
			break;
		case "vehicle_van_blue":
			vehicle_van( "blue" );
			break;
		case "vehicle_van_dark_gray":
			vehicle_van( "dark_gray" );
			break;
		case "vehicle_van_deep_blue":
			vehicle_van( "deep_blue" );
			break;
		case "vehicle_van_gold":
			vehicle_van( "gold" );
			break;
		case "vehicle_van_gray":
			vehicle_van( "gray" );
			break;
		case "vehicle_van_green":
			vehicle_van( "green" );
			break;
		case "vehicle_van_mica":
			vehicle_van( "mica" );
			break;
		case "vehicle_van_slate":
			vehicle_van( "slate" );
			break;
		case "vehicle_van_tan":
			vehicle_van( "tan" );
			break;
		case "vehicle_van_white":
			vehicle_van( "white" );
			break;
		case "vehicle_suburban":
			vehicle_suburban( destructibleType, "" );
			break;
		case "vehicle_suburban_beige":
			vehicle_suburban( destructibleType, "_beige" );
			break;
		case "vehicle_suburban_dull":
			vehicle_suburban( destructibleType, "_dull" );
			break;
		case "vehicle_suburban_red":
			vehicle_suburban( destructibleType, "_red" );
			break;
		case "vehicle_snowmobile":
			vehicle_snowmobile( destructibleType );
			break;
		case "destructible_gaspump":
			destructible_gaspump( destructibleType );
			break;
		case "destructible_electrical_transformer_large":
			destructible_electrical_transformer_large( destructibleType );
			break;
		case "toy_new_dlc_destructible":
			toy_glass( "120x110" );
			break;
		case "toy_security_camera":
			toy_security_camera( destructibleType );
			break;
		case "toy_building_collapse_paris_ac130":
			toy_building_collapse_paris_ac130( destructibleType );
			break;
		case "toy_poison_gas_attack":
			toy_poison_gas_attack( destructibleType );
			break;
		case "toy_arcade_machine_1":
			toy_arcade_machine( "_1" );
			break;
		case "toy_arcade_machine_2":
			toy_arcade_machine( "_2" );
			break;
		case "toy_pinball_machine_1":
			toy_pinball_machine( "_1" );
			break;
		case "toy_pinball_machine_2":
			toy_pinball_machine( "_2" );
			break;
		case "toy_fortune_machine":
			toy_fortune_machine( destructibleType );
			break;
		// add new destructibles here, you can write new functions for them or call the old ones
		case "toy_trashcan_clown":
			toy_trashcan_clown( destructibleType );
			break;

		case "toy_afrShanty1":
			toy_afrShanty1( destructibleType );
			break;
		case "vehicle_slava_ny_harbor_zonea":
			vehicle_slava_ny_harbor_zonea( destructibleType );
			break;
		case "rooftop_skylight_destructible":
			rooftop_skylight_destructible( destructibleType );
			break;
		case "satellite_dish_big_destructible":
			satellite_dish_big_destructible( destructibleType );
			break;
		//*Raven
		case "berlin_hotel_lights_ceiling1":
			berlin_hotel_lights_ceiling1(destructibleType,"berlin_hotel_lights_ceiling1_destroyed");
			break;
		case "berlin_hotel_lights_ceiling1_off":
			berlin_hotel_lights_ceiling1(destructibleType,"berlin_hotel_lights_ceiling1_destroyed");
			break;
		case "berlin_hotel_lights_wall1":
			dest_onestate(destructibleType,"berlin_hotel_lights_wall1_destroyed","misc/light_blowout_wall2_runner");
			break;
		case "berlin_hotel_lights_wall1_off":
			dest_onestate(destructibleType,"berlin_hotel_lights_wall1_destroyed","misc/light_blowout_wall2_runner");
			break;
		case "berlin_hotel_lights_wall2":
			dest_onestate(destructibleType,"berlin_hotel_lights_wall2_destroyed","misc/light_blowout_wall_runner");
			break;
		case "berlin_hotel_lights_wall2_off":
			dest_onestate(destructibleType,"berlin_hotel_lights_wall2_destroyed","misc/light_blowout_wall_runner");
			break;
		case "pb_cubical_planter":
			dest_pb_planter(destructibleType,"pb_cubical_planter_dam","explosions/brick_chunk");
			break;
		case "vehicle_delivery_theme_park_truck_destructible":
			vehicle_delivery_theme_park_truck_destructible( destructibleType );
			break;
		case "vehicle_van_sas_dark_destructable":
			vehicle_van_iw5( "vehicle_van_sas_dark" );
			break;
		case "vehicle_uk_police_van_destructable":
			vehicle_van_iw5( "vehicle_uk_police_van" );
			break;
		case "vehicle_jeep_dusty":
			vehicle_jeep_dusty( destructibleType );
			break;
		//*EndRVN
			
		default: // Default means invalid type
			assertMsg( "Destructible object 'destructible_type' key/value of '" + destructibleType + "' is not valid" );
			break;
	}

	infoIndex = getInfoIndex( destructibleType );
	AssertEx( infoIndex >= 0, "invalid infoIndex: " + destructibleType );
	return infoIndex;
}

getInfoIndex( destructibleType )
{
	if ( !isdefined( level.destructible_type ) )
		return - 1;
	if ( level.destructible_type.size == 0 )
		return - 1;

	for ( i = 0 ; i < level.destructible_type.size ; i++ )
	{
		if ( destructibleType == level.destructible_type[ i ].v[ "type" ] )
			return i;
	}

	// didn't find it in the array, must not exist
	return - 1;
}

//---------------------------------------------------------------------
// Paris - AC130 Props - very low poly
//---------------------------------------------------------------------

prop_ac_prs_enm_barge_a_1()
{
	destructible_create( "prop_ac_prs_enm_barge_a_1", "tag_origin", 250, undefined, 32, "no_melee" );
			destructible_state( "tag_origin", "ac_prs_enm_barge_a_1_dam_animated", 250, undefined, 32, "no_melee" );
				destructible_anim( get_precached_anim( "paris_ac130_barge_sink" ), get_precached_animtree( "paris_ac130_barge_sink" ), "setanim" );
				destructible_fx( undefined, "impacts/105mm_water_impact_fast", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_barge_a_2()
{
	destructible_create( "prop_ac_prs_enm_barge_a_2", "tag_origin", 250, undefined, 32, "no_melee" );
			destructible_state( "tag_origin", "ac_prs_enm_barge_a_2_dam_animated", 250, undefined, 32, "no_melee" );
				destructible_anim( get_precached_anim( "paris_ac130_barge_sink" ), get_precached_animtree( "paris_ac130_barge_sink" ), "setanim" );
				destructible_fx( undefined, "impacts/105mm_water_impact_fast", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_con_digger_a()
{
	destructible_create( "prop_ac_prs_enm_con_digger_a", "ac_prs_enm_con_digger_a_lod_0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_con_digger_a_dam_lod0", "ac_prs_enm_con_digger_a_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_con_dump_truck_a()
{
	destructible_create( "prop_ac_prs_enm_con_dump_truck_a", "ac_prs_enm_con_dump_truck_a_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_con_dump_truck_a_destroyed_lod0", "ac_prs_enm_con_dump_truck_a_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_fuel_tank_a()
{
	destructible_create( "prop_ac_prs_enm_fuel_tank_a", "ac_prs_enm_fuel_tank_a_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_fuel_tank_a_dam_lod0", "ac_prs_enm_fuel_tank_a_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/fuel_storage", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_hanger_a()
{
	destructible_create( "prop_ac_prs_enm_hanger_a", "ac_prs_enm_hanger_a_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_hanger_a_dam_lod0", "ac_prs_enm_hanger_a_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_maz_a()
{
	destructible_create( "prop_ac_prs_enm_maz_a", "ac_prs_enm_maz_a", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_maz_a_dam3", "ac_prs_enm_maz_a_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );
				destructible_fx( undefined, "explosions/ac_prs_fx_flir_debris_explosion_a", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_mi26_halo_a()
{
	destructible_create( "prop_ac_prs_enm_mi26_halo_a", "ac_prs_enm_mi26_halo_a_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "polySurface80", "ac_prs_enm_mi26_halo_a_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/helicopter_explosion_mi26_halo", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_mstas_a()
{
	destructible_create( "prop_ac_prs_enm_mstas_a", "ac_prs_enm_mstas_a_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_mstas_a_dam_lod0", "ac_prs_enm_mstas_a_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_flir_debris_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fx_debris_explosion_fire_a", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_radar_maz_a()
{
	destructible_create( "prop_ac_prs_enm_radar_maz_a", "tag_origin", 250, undefined, 32, "no_melee" );
			destructible_state( "tag_origin", "ac_prs_enm_radar_maz_a", 250, undefined, 32, "no_melee" );
				destructible_anim( get_precached_anim( "ac130_radartower_crash" ), get_precached_animtree( "ac130_radartower_crash" ), "setanim" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_s300v_a()
{
	destructible_create( "prop_ac_prs_enm_s300v_a", "ac_prs_enm_s300v", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_s300v_dam", "ac_prs_enm_s300v_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/vehicle_explosion_sam", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_storage_bld_a_1()
{
	destructible_create( "prop_ac_prs_enm_storage_bld_a_1", "p_ac_prs_enm_storage_bld_a_1", 250, undefined, 32, "no_melee" );
			destructible_state( "p_ac_prs_enm_storage_bld_a_1_dam", "ac_prs_enm_storage_bld_a_1_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );	
				destructible_fx( undefined, "explosions/ac_prs_fx_flir_debris_explosion_a", false );			
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_storage_bld_a_2()
{
	destructible_create( "prop_ac_prs_enm_storage_bld_a_2", "p_ac_prs_enm_storage_bld_a_2", 250, undefined, 32, "no_melee" );
			destructible_state( "p_ac_prs_enm_storage_bld_a_2_dam", "ac_prs_enm_storage_bld_a_2_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );
				destructible_fx( undefined, "explosions/ac_prs_fx_flir_debris_explosion_a", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_storage_bld_b()
{
	destructible_create( "prop_ac_prs_enm_storage_bld_b", "p_ac_prs_enm_storage_bld_b", 250, undefined, 32, "no_melee" );
			destructible_state( "p_ac_prs_enm_storage_bld_b_dam", "ac_prs_enm_storage_bld_b_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );
				destructible_fx( undefined, "explosions/ac_prs_fx_flir_debris_explosion_max_a", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_tent_a()
{
	destructible_create( "prop_ac_prs_enm_tent_a", "ac_prs_enm_tent_a_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "polySurface1", "ac_prs_enm_tent_a_dam1", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/tent_collapse", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_tent_b()
{
	destructible_create( "prop_ac_prs_enm_tent_b", "ac_prs_enm_tent_b_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_tent_b_lod1", "ac_prs_enm_tent_b_dam1", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/tent_collapse", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_tent_c()
{
	destructible_create( "prop_ac_prs_enm_tent_c", "ac_prs_enm_tent_c_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_tent_c_lod1", "ac_prs_enm_tent_c_dam1", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/tent_collapse", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_truck_a()
{
	destructible_create( "prop_ac_prs_enm_truck_a", "ac_prs_enm_truck_a_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_truck_a_dam_lod0", "ac_prs_enm_truck_a_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );
				destructible_fx( undefined, "explosions/ac_prs_fx_flir_debris_explosion_a", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_cargo_crate_a_1()
{

	destructible_create( "prop_ac_prs_enm_cargo_crate_a_1", "ac_prs_enm_cargo_crate_a_1_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_cargo_crate_a_1_lod0", "ac_prs_enm_cargo_crate_a_1_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_cargo_crate_a_2()
{
	destructible_create( "prop_ac_prs_enm_cargo_crate_a_2", "ac_prs_enm_cargo_crate_a_2_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_cargo_crate_a_2_lod0", "ac_prs_enm_cargo_crate_a_2_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_crates_a_1()
{
	destructible_create( "prop_ac_prs_enm_crates_a_1", "ac_prs_enm_crates_a_1_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_crates_a_1_dam_lod0", "ac_prs_enm_crates_a_1_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_enm_crates_a_explosion_1", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_crates_a_2()
{
	destructible_create( "prop_ac_prs_enm_crates_a_2", "ac_prs_enm_crates_a_2_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_crates_a_2_dam_lod0", "ac_prs_enm_crates_a_2_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_enm_crates_a_explosion_1", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_crates_b_1()
{
	destructible_create( "prop_ac_prs_enm_crates_b_1", "ac_prs_enm_crates_b_1_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_crates_b_1_dam_lod0", "ac_prs_enm_crates_b_1_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_enm_crates_b_explosion_1", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_crates_b_2()
{
	destructible_create( "prop_ac_prs_enm_crates_b_2", "ac_prs_enm_crates_b_2_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_crates_b_2_dam_lod0", "ac_prs_enm_crates_b_2_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_enm_crates_b_explosion_1", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}
            
prop_ac_prs_enm_mobile_crane_a()
{
	destructible_create( "prop_ac_prs_enm_mobile_crane_a", "ac_prs_enm_mobile_crane_a_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_enm_mobile_crane_a_dam_lod0", "ac_prs_enm_mobile_crane_a_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_landing_craft_a()
{
	destructible_create( "prop_ac_prs_enm_landing_craft_a", "ac_prs_enm_landing_craft_a_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "tag_origin", "ac_prs_enm_landing_craft_a_dam", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_speed_boat_a()
{
	destructible_create( "prop_ac_prs_enm_speed_boat_a", "ac_prs_enm_speed_boat_a", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_prp_metal_debris_a_01_lod0", "ac_prs_prp_metal_debris_a_01", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/building_explosion_paris_ac130", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_prp_satellite_dish_a_dish()
{
	destructible_create( "prop_ac_prs_prp_satellite_dish_a_dish", "ac_prs_prp_satellite_dish_a_dish_lod0", 250, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_prp_metal_debris_a_01_lod0", "ac_prs_prp_metal_debris_a_01", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_fps_hc_extc_balcony_a1()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_balcony_a1", "ac_prs_fps_hc_extc_balcony_a_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_balcony_a_dam1_lod0", "ac_prs_fps_hc_extc_balcony_a_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_a_explosion_1", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_fps_hc_extc_balcony_a2()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_balcony_a2", "ac_prs_fps_hc_extc_balcony_a_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_balcony_a_dam2_lod0", "ac_prs_fps_hc_extc_balcony_a_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_a_explosion_1", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}
	
prop_ac_prs_fps_hc_extc_balcony_a3()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_balcony_a3", "ac_prs_fps_hc_extc_balcony_a_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_balcony_a_dam3_lod0", "ac_prs_fps_hc_extc_balcony_a_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_a_explosion_1", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_fps_hc_extc_balcony_b1()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_balcony_b1", "ac_prs_fps_hc_extc_balcony_b_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_balcony_b_dam1_lod0", "ac_prs_fps_hc_extc_balcony_b_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_b_explosion_1", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_fps_hc_extc_balcony_b2()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_balcony_b2", "ac_prs_fps_hc_extc_balcony_b_lod0", 80, undefined, 32, "no_melee" ); 
			destructible_state( "ac_prs_fps_hc_extc_balcony_b_dam2_lod0", "ac_prs_fps_hc_extc_balcony_b_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_b_explosion_1", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}
	
prop_ac_prs_fps_hc_extc_balcony_b3()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_balcony_b3", "ac_prs_fps_hc_extc_balcony_b_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_balcony_b_dam3_lod0", "ac_prs_fps_hc_extc_balcony_b_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_b_explosion_1", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_fps_hc_extc_balcony_c1()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_balcony_c1", "ac_prs_fps_hc_extc_balcony_c_lod0", 80, undefined, 32, "no_melee" ); 
			destructible_state( "ac_prs_fps_hc_extc_balcony_c_dam1_lod0", "ac_prs_fps_hc_extc_balcony_c_dam1", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_c_explosion_1", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}
	
prop_ac_prs_fps_hc_extc_balcony_c2()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_balcony_c2", "ac_prs_fps_hc_extc_balcony_c_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_balcony_c_dam2_lod0", "ac_prs_fps_hc_extc_balcony_c_dam2", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_c_explosion_2", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_fps_hc_extc_column_b_a1()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_column_b_a1", "ac_prs_fps_hc_extc_column_b_a_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_column_b_a_dam1_lod0", "ac_prs_fps_hc_extc_column_b_a_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_c_explosion_2", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_fps_hc_extc_column_b_a2()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_column_b_a2", "ac_prs_fps_hc_extc_column_b_a_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_column_b_a_dam2_lod0", "ac_prs_fps_hc_extc_column_b_a_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_c_explosion_2", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}



prop_ac_prs_fps_hc_extc_column_b_a3()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_column_b_a3", "ac_prs_fps_hc_extc_column_b_a_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_column_b_a_dam3_lod0", "ac_prs_fps_hc_extc_column_b_a_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_c_explosion_2", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_fps_hc_extc_column_t_a1()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_column_t_a1", "ac_prs_fps_hc_extc_column_t_a_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_column_t_a_dam1_lod0", "ac_prs_fps_hc_extc_column_t_a_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_c_explosion_2", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_fps_hc_extc_column_t_a2()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_column_t_a2", "ac_prs_fps_hc_extc_column_t_a_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_column_t_a_dam2_lod0", "ac_prs_fps_hc_extc_column_t_a_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_c_explosion_2", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_fps_hc_extc_column_t_a3()
{
	destructible_create( "prop_ac_prs_fps_hc_extc_column_t_a3", "ac_prs_fps_hc_extc_column_t_a_lod0", 80, undefined, 32, "no_melee" );
			destructible_state( "ac_prs_fps_hc_extc_column_t_a_dam3_lod0", "ac_prs_fps_hc_extc_column_t_a_dam3", 250, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/ac_prs_fx_dust_explosion_a", false );
				destructible_fx( undefined, "explosions/ac_prs_fps_extc_balcony_c_explosion_2", false );				
				//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

prop_ac_prs_enm_missile_boat_a()
{
	destructible_create( "prop_ac_prs_enm_missile_boat_a", "tag_origin", 250, undefined, 32, "no_melee" );
			destructible_state( "tag_origin", "ac_prs_enm_missile_boat_a", 250, undefined, 32, "no_melee" );
				destructible_anim( get_precached_anim( "paris_ac130_ship_sink" ), get_precached_animtree( "paris_ac130_ship_sink" ), "setanim" );
				destructible_fx( undefined, "impacts/105mm_water_impact_fast", false );				
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}
	                    
#using_animtree( "destructibles" );

toy_glass( size )
{
	//---------------------------------------------------------------------
	// glass break test 120x110inches
	//---------------------------------------------------------------------
	destructible_create( "toy_glass" + size, "tag_origin", 50 );
		destructible_splash_damage_scaler( 5 );
			destructible_sound( "building_glass_shatter" );
		// Glass
		tag = "tag_glass";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
				destructible_fx( tag, "props/highrise_glass_" + size );
				//destructible_fx( tag, "props/highrise_glass_120x110_fountain" );
				destructible_sound( "building_glass_blowout" );
			destructible_state( tag + "_des", undefined, 100, undefined, undefined, undefined, true );
				destructible_fx( tag, "props/highrise_glass_" + size + "_edge");
				destructible_sound( "building_glass_blowout" );
			destructible_state( undefined );
}

toy_dt_mirror( size )
{
	//---------------------------------------------------------------------
	// dt_mirror
	//---------------------------------------------------------------------
	destructible_create( "toy_dt_mirror" + size, "tag_origin", 150, undefined, 32 );
		destructible_splash_damage_scaler( 5 );
			destructible_fx( "tag_fx", "props/mirror_shatter" + size );
			destructible_sound( "mirror_shatter" );
		destructible_state( "tag_origin", "dt_mirror" + size + "_dam", 150, undefined );
			destructible_fx( "tag_fx", "props/mirror_dt_panel" + size + "_broken" );
			destructible_explode( 1000, 2000, 32, 32, 32, 48, undefined, 0 );   // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continue damage, originoffset
		destructible_state( "tag_origin", "dt_mirror" + size + "_des", 150, undefined );
}

toy_icbm_consolemonitor( version )
{
	//---------------------------------------------------------------------
	// ICBM TV SCREEN ONLY
	//---------------------------------------------------------------------
	destructible_create( "toy_icbm_consolemonitor" + version, "television2_lod04", 1, undefined, 32 );
		destructible_splash_damage_scaler( 1 );
			destructible_fx( "television2_lod04", "explosions/tv_explosion" );
			destructible_sound( "tv_shot_burst", "television2_lod04" );
			destructible_explode( 20, 2000, 9, 9, 3, 3, undefined, 12 );	// force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
		destructible_state( "television2_lod04", "hjk_icbm_consolemonitor7", undefined, undefined, "no_melee" );
}

toy_tubetv_( version )
{
	//---------------------------------------------------------------------
	// Tube TV
	//---------------------------------------------------------------------
	destructible_create( "toy_tubetv_" + version, "tag_origin", 1, undefined, 32 );
		destructible_splash_damage_scaler( 1 );
			destructible_fx( "tag_fx", "explosions/tv_explosion" );
			destructible_sound( "tv_shot_burst" );
			destructible_explode( 20, 2000, 9, 9, 3, 3, undefined, 12 );	// force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
		destructible_state( undefined, "com_" + version + "_d", undefined, undefined, "no_melee" );
}

toy_tvs_flatscreen( version, mounting )
{
	//---------------------------------------------------------------------
	// Flatscreen TVs
	//---------------------------------------------------------------------
	destructible_create( "toy_tv_flatscreen_" + mounting + version, "tag_origin", 1, undefined, 32 );
		destructible_splash_damage_scaler( 1 );
			destructible_fx( "tag_fx", "explosions/tv_flatscreen_explosion" );
			destructible_sound( "tv_shot_burst" );
			destructible_explode( 20, 2000, 10, 10, 3, 3, undefined, 15 );  // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
		destructible_state( undefined, "ma_flatscreen_tv_" + mounting + "broken_" + version, 200, undefined, "no_melee" );
}

toy_tvs_flatscreen_sturdy( version, mounting )
{
	//---------------------------------------------------------------------
	// Flatscreen TVs that can take more damage
	//---------------------------------------------------------------------
	destructible_create( "toy_tv_flatscreen_" + mounting + version + "_sturdy", "tag_origin", 1, undefined, 1280 );
		destructible_splash_damage_scaler( 0.5 );
			destructible_fx( "tag_fx", "explosions/tv_flatscreen_explosion_cheap" );
			destructible_sound( "tv_shot_burst" );
			destructible_explode( 20, 2000, 10, 10, 3, 3, undefined, 15 );  // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
		destructible_state( undefined, "ma_flatscreen_tv_" + mounting + "broken_" + version, 200, undefined, "no_melee" );
}

toy_transformer_ratnest01( destructibleType )
{
	//---------------------------------------------------------------------
	// Transformer w/ wires for Favela 
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 75, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );
				destructible_loopfx( "tag_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 75, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 150, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_sparks", "explosions/transformer_spark_runner", .5 );
				destructible_loopsound( "transformer_spark_loop" );
				destructible_healthdrain( 24, 0.2 );
			destructible_state( undefined, undefined, 250, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_sparks", "explosions/transformer_spark_runner", .5 );
				destructible_loopfx( "tag_fx", "fire/electrical_transformer_blacksmoke_fire", .4 );
				destructible_sound( "transformer01_flareup_med" );
				destructible_loopsound( "transformer_spark_loop" );
				destructible_healthdrain( 24, 0.2, 150, "allies" );
			destructible_state( undefined, undefined, 400, undefined, 5, "no_melee" );
				destructible_fx( "tag_fx", "explosions/transformer_explosion", false );
				destructible_fx( "tag_fx", "fire/firelp_small_pm" );
				destructible_sound( "transformer01_explode" );
				destructible_explode( 7000, 8000, 150, 256, 16, 100, undefined, 0 );	// force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
			destructible_state( undefined, "utility_transformer_ratnest01_dest", undefined, undefined, "no_melee" );
}

toy_transformer_small01( destructibleType )
{
	//---------------------------------------------------------------------
	// Small hanging Transformer box for Favela 
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 75, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );
				destructible_loopfx( "tag_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 75, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 150, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_fx", "explosions/transformer_spark_runner", .5 );
				destructible_loopsound( "transformer_spark_loop" );
				destructible_healthdrain( 24, 0.2 );
			destructible_state( undefined, undefined, 250, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_fx", "explosions/transformer_spark_runner", .5 );
				destructible_loopfx( "tag_fx", "fire/transformer_small_blacksmoke_fire", .4 );
				destructible_sound( "transformer01_flareup_med" );
				destructible_loopsound( "transformer_spark_loop" );
				destructible_healthdrain( 24, 0.2, 150, "allies" );
			destructible_state( undefined, undefined, 400, undefined, 5, "no_melee" );
				destructible_fx( "tag_fx", "explosions/transformer_explosion", false );
				destructible_fx( "tag_fx", "fire/firelp_small_pm" );
				destructible_sound( "transformer01_explode" );
				destructible_explode( 7000, 8000, 150, 256, 16, 100, undefined, 0 );	// force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
			destructible_state( undefined, "utility_transformer_small01_dest", undefined, undefined, "no_melee" );
}

toy_generator( destructibleType )
{
	//---------------------------------------------------------------------
	// Red Generator
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_bounce", 75, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );
				destructible_loopfx( "tag_fx2", "smoke/generator_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 75, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_fx2", "smoke/generator_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 250, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_fx2", "smoke/generator_damage_blacksmoke", 0.4 );
				destructible_loopfx( "tag_fx4", "explosions/generator_spark_runner", .9 );
				destructible_loopfx( "tag_fx3", "explosions/generator_spark_runner", .6123 );
				destructible_loopsound( "generator_spark_loop" );
				destructible_healthdrain( 24, 0.2, 64, "allies" );
			destructible_state( undefined, undefined, 400, undefined, 5, "no_melee" );
				destructible_fx( "tag_fx", "explosions/generator_explosion", true );
				destructible_fx( "tag_fx", "fire/generator_des_fire",true );
				destructible_sound( "generator01_explode" );
				destructible_explode( 7000, 8000, 128, 128, 16, 50, undefined, 0 );	 // force_min, force_max, range, mindamage, maxdamage
				destructible_anim( get_precached_anim( "generator_explode" ), #animtree, "setanimknob", undefined, undefined, "generator_explode" );
			destructible_state( undefined, "machinery_generator_des", undefined, undefined, "no_melee" );
}

toy_generator_on( destructibleType )
{
	//---------------------------------------------------------------------
	// Red Generator, on... with sound and vibration animation
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_bounce", 0, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );
			destructible_loopfx( "tag_fx2", "smoke/generator_exhaust", 0.4 );
			destructible_anim( get_precached_anim( "generator_vibration" ), #animtree, "setanimknob", undefined, undefined, "generator_vibration" );
			destructible_loopsound( "generator_running" );
		destructible_state( "tag_origin", "machinery_generator", 150 );
				destructible_loopfx( "tag_fx2", "smoke/generator_damage_whitesmoke", 0.4 );
				destructible_loopsound( "generator_running" );		  
			destructible_state( undefined, undefined, 75, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_fx2", "smoke/generator_damage_blacksmoke", 0.4 );
				destructible_loopsound( "generator_damage_loop" );
			destructible_state( undefined, undefined, 250, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_fx2", "smoke/generator_damage_blacksmoke", 0.4 );
				destructible_loopfx( "tag_fx4", "explosions/generator_spark_runner", .9 );
				destructible_loopfx( "tag_fx3", "explosions/generator_spark_runner", .6123 );
				destructible_loopsound( "generator_spark_loop" );
				destructible_loopsound( "generator_damage_loop" );
				destructible_healthdrain( 24, 0.2, 64, "allies" );
			destructible_state( undefined, undefined, 400, undefined, 5, "no_melee" );
				destructible_fx( "tag_fx", "explosions/generator_explosion", false );
				destructible_fx( "tag_fx", "fire/generator_des_fire" );
				destructible_sound( "generator01_explode" );
				destructible_explode( 7000, 8000, 128, 128, 16, 50, undefined, 0 );	 // force_min, force_max, range, mindamage, maxdamage
				destructible_anim( get_precached_anim( "generator_explode" ), #animtree, "setanimknob", undefined, 0, "generator_explode" );
				destructible_anim( get_precached_anim( "generator_explode_02" ), #animtree, "setanimknob", undefined, 0, "generator_explode_02" );
				destructible_anim( get_precached_anim( "generator_explode_03" ), #animtree, "setanimknob", undefined, 0, "generator_explode_03" );
			destructible_state( undefined, "machinery_generator_des", undefined, undefined, "no_melee" );
}

toy_oxygen_tank( version )
{
	//---------------------------------------------------------------------
	// Oxygen Tanks 01 and 02 
	//---------------------------------------------------------------------
	destructible_create( "toy_oxygen_tank_" + version, "tag_origin", 150, undefined, 32, "no_melee" );
				destructible_healthdrain( 12, 0.2, 64, "allies" );
				destructible_loopsound( "oxygen_tank_leak_loop" );
				destructible_fx( "tag_cap", "props/oxygen_tank" + version + "_cap" );
				destructible_loopfx( "tag_cap", "distortion/oxygen_tank_leak", 0.4 );
			destructible_state( undefined, "machinery_oxygen_tank" + version + "_dam", 300, undefined, 32, "no_melee" );
				destructible_fx( "tag_fx", "explosions/oxygen_tank" + version + "_explosion", false );
				destructible_sound( "oxygen_tank_explode" );
				destructible_explode( 7000, 8000, 150, 256, 16, 150, undefined, 32 );   
				destructible_state( undefined, "machinery_oxygen_tank" + version + "_des", undefined, undefined, "no_melee" );
}

toy_electricbox2( destructibleType )
{
	//---------------------------------------------------------------------
	// electric box large toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 150, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );
			destructible_fx( "tag_fx", "props/electricbox4_explode", undefined, undefined, undefined, 1 );
			destructible_sound( "exp_fusebox_sparks" );
			destructible_explode( 1000, 2000, 32, 32, 32, 48, undefined, 0 );   // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continue damage, originoffset
		destructible_state( undefined, "me_electricbox2_dest", undefined, undefined, "no_melee" );
		// door
		destructible_part( "tag_fx", "me_electricbox2_door", undefined, undefined, undefined, undefined, 1.0, 1.0 );

		// door upper
		destructible_part( "tag_door_upper", "me_electricbox2_door_upper", undefined, undefined, undefined, undefined, 1.0, 1.0 );

}

toy_electricbox4( destructibleType )
{
	//---------------------------------------------------------------------
	// electric box medium toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 150, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );
			destructible_fx( "tag_fx", "props/electricbox4_explode", undefined, undefined, undefined, 1 );
			destructible_sound( "exp_fusebox_sparks" );
			destructible_explode( 20, 2000, 32, 32, 32, 48, undefined, 0 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continue damage, originoffset
		destructible_state( undefined, "me_electricbox4_dest", undefined, undefined, "no_melee" );
		// door
		destructible_part( "tag_fx", "me_electricbox4_door", undefined, undefined, undefined, undefined, 1.0, 1.0 );
}

toy_airconditioner( destructibleType )
{
	//---------------------------------------------------------------------
	// Small Airconditioner hanging on wall
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 0, undefined, 32 );
			destructible_anim( get_precached_anim( "ex_airconditioner_fan" ), #animtree, "setanimknob", undefined, undefined, "ex_airconditioner_fan" );
			destructible_loopsound( "airconditioner_running_loop" );
		destructible_state( "tag_origin", "com_ex_airconditioner", 300 );
			destructible_fx( "tag_fx", "explosions/airconditioner_ex_explode", undefined, undefined, undefined, 1 );
			destructible_sound( "airconditioner_burst" );
			destructible_explode( 1000, 2000, 32, 32, 32, 48, undefined, 0 );   // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continue damage, originoffset
		destructible_state( undefined, "com_ex_airconditioner_dam", undefined, undefined, "no_melee" );
		// door
		destructible_part( "tag_fx", "com_ex_airconditioner_fan", undefined, undefined, undefined, undefined, 1.0, 1.0 );
}


toy_ceiling_fan( destructibleType )
{
	//---------------------------------------------------------------------
	// ceiling fan
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 0, undefined, 32 );
			destructible_anim( get_precached_anim( "me_fanceil1_spin" ), #animtree, "setanimknob", undefined, undefined, "me_fanceil1_spin" );
		destructible_state( "tag_origin", "me_fanceil1", 150 );
			destructible_anim( get_precached_anim( "me_fanceil1_spin_stop" ), #animtree, "setanimknob", undefined, undefined, "me_fanceil1_spin_stop" );
			destructible_fx( "tag_fx", "explosions/ceiling_fan_explosion" );
			destructible_sound( "ceiling_fan_sparks" );
			destructible_explode( 1000, 2000, 32, 32, 5, 32, undefined, 0 );	// force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continue damage, originoffset
		destructible_state( undefined, "me_fanceil1_des", undefined, undefined, "no_melee" );
			destructible_part( "tag_fx", undefined, 150, undefined, undefined, undefined, 1.0 );
}


toy_wall_fan( destructibleType )
{
	//---------------------------------------------------------------------
	// wall fan
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_swivel", 0, undefined, 32 );
			destructible_anim( get_precached_anim( "wall_fan_rotate" ), #animtree, "setanimknob", undefined, undefined, "wall_fan_rotate" );
			destructible_loopsound( "wall_fan_fanning" );
		destructible_state( "tag_wobble", "cs_wallfan1", 150 );
			destructible_anim( get_precached_anim( "wall_fan_stop" ), #animtree, "setanimknob", undefined, undefined, "wall_fan_wobble" );
			destructible_fx( "tag_fx", "explosions/wallfan_explosion_dmg" );
			destructible_sound( "wall_fan_sparks" );
		//  destructible_loopsound( "wall_fan_malfuntioning" );
		destructible_state( "tag_wobble", "cs_wallfan1", 150, undefined, "no_melee" );
		//  destructible_anim( get_precached_anim( "wall_fan_stop" ), #animtree, "setanimknob", undefined, undefined, "wall_fan_stop" );
			destructible_fx( "tag_fx", "explosions/wallfan_explosion_des" );
			destructible_sound( "wall_fan_break" );
		destructible_state( undefined, "cs_wallfan1_dmg", undefined, undefined, "no_melee" );
}

toy_propane_tank02( destructibleType )
{
	//---------------------------------------------------------------------
	// Large Propane tank goes KaBooM
	//---------------------------------------------------------------------

	destructible_create( destructibleType, "tag_origin", 50, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 5 );
			destructible_state( undefined, undefined, 350, undefined, 32, "no_melee" );
				destructible_loopsound( "propanetank02_gas_leak_loop" );
			destructible_state( undefined, undefined, 350, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_cap", "fire/propane_capfire_leak", 0.1 );
				destructible_sound( "propanetank02_flareup_med" );
				destructible_loopsound( "propanetank02_fire_med" );
				destructible_healthdrain( 12, 0.2, 300, "allies" );
			destructible_state( undefined, undefined, 150, undefined, 32, "no_melee" );
				destructible_physics( "tag_cap", ( 50, 0, 0 ) );
				destructible_loopfx( "tag_cap", "fire/propane_capfire", 0.6 );
				destructible_fx( "tag_valve", "fire/propane_valvefire_flareup" );
				destructible_physics( "tag_valve", ( 50, 0, 0 ) );
				destructible_fx( "tag_cap", "fire/propane_capfire_flareup" );
				destructible_loopfx( "tag_valve", "fire/propane_valvefire", 0.1 );
				destructible_sound( "propanetank02_flareup2_med" );
				destructible_loopsound( "propanetank02_fire_med" );
			destructible_state( undefined, undefined, 150, undefined, 5, "no_melee" );
				destructible_fx( "tag_fx", "fire/propane_small_fire" );
				//destructible_fx( "tag_fx", "explosions/propane_large_exp_fireball" );
				destructible_fx( "tag_fx", "explosions/propane_large_exp", false );
				destructible_sound( "propanetank02_explode" );
				destructible_loopsound( "propanetank02_fire_blown_med" );
				destructible_explode( 7000, 8000, 600, 600, 32, 300 );  // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
			destructible_state( undefined, "com_propane_tank02_DES", undefined, undefined, "no_melee" );
		// Lower Valve
		destructible_part( "tag_valve", "com_propane_tank02_valve" );
		// Top Cap
		destructible_part( "tag_cap", "com_propane_tank02_cap" );

}

toy_propane_tank02_small( destructibleType )
{
	//---------------------------------------------------------------------
	// Small Propane tank goes KaBooM
	//---------------------------------------------------------------------
	
	destructible_create( destructibleType, "tag_origin", 50, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 10 );
			destructible_state( undefined, undefined, 350, undefined, 32, "no_melee" );
				destructible_loopsound( "propanetank02_gas_leak_loop" );
			destructible_state( undefined, undefined, 350, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_cap", "fire/propane_capfire_leak", 0.1 );
				destructible_sound( "propanetank02_flareup_med" );
				destructible_loopsound( "propanetank02_fire_med" );
				destructible_healthdrain( 12, 0.2, 210, "allies" );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_physics( "tag_cap", ( 50, 0, 0 ) );
				destructible_loopfx( "tag_cap", "fire/propane_capfire", 0.6 );
				destructible_fx( "tag_valve", "fire/propane_valvefire_flareup" );
				destructible_physics( "tag_valve", ( 50, 0, 0 ) );
				destructible_fx( "tag_cap", "fire/propane_capfire_flareup" );
				destructible_loopfx( "tag_valve", "fire/propane_valvefire", 0.1 );
				destructible_sound( "propanetank02_flareup_med" );
				destructible_loopsound( "propanetank02_fire_med" );
			destructible_state( undefined, undefined, 200, undefined, 5, "no_melee" );
				destructible_fx( "tag_fx", "fire/propane_small_fire" );
				//destructible_fx( "tag_fx", "explosions/propane_large_exp_fireball" );
				destructible_fx( "tag_fx", "explosions/propane_large_exp", false );
				destructible_sound( "propanetank02_explode" );
				destructible_explode( 7000, 8000, 400, 400, 32, 100 );  // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
			destructible_state( undefined, "com_propane_tank02_small_DES", undefined, undefined, "no_melee" );
		// Lower Valve
		destructible_part( "tag_valve", "com_propane_tank02_small_valve" );
		// Top Cap
		destructible_part( "tag_cap", "com_propane_tank02_small_cap" );

}

toy_copier( destructibleType )
{
	//---------------------------------------------------------------------
	// copier toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );
				destructible_loopfx( "tag_left_feeder", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 250, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_left_feeder", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 500, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_fx", "props/photocopier_sparks", 3 );
				destructible_loopsound( "copier_spark_loop" );
				destructible_healthdrain( 12, 0.2 );
			destructible_state( undefined, undefined, 800, undefined, 5, "no_melee" );
				destructible_fx( "tag_fx", "props/photocopier_exp", false );
				destructible_fx( "tag_fx", "props/photocopier_fire" );
				destructible_sound( "copier_exp" );
				destructible_loopsound( "copier_fire_loop" );
				destructible_explode( 7000, 8000, 96, 96, 32, 48 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
			destructible_state( undefined, "prop_photocopier_destroyed", undefined, undefined, "no_melee" );


		// left feeder part
		destructible_part( "tag_left_feeder", "prop_photocopier_destroyed_left_feeder", 4, undefined, undefined, undefined, 1.0, 1.0 );
		// right shelf
		destructible_part( "tag_right_shelf", "prop_photocopier_destroyed_right_shelf", 4, undefined, undefined, undefined, 1.0, 1.0 );
		// top cover
		destructible_part( "tag_top", "prop_photocopier_destroyed_top", 4, undefined, undefined, undefined, 1.0, 1.0 );

}

toy_firehydrant( destructibleType )
{
	//---------------------------------------------------------------------
	// fire hydrant toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 250, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 11 );
			destructible_state( undefined, undefined, 500, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_cap", "props/firehydrant_leak", 0.1 );
				destructible_loopsound( "firehydrant_spray_loop" );
				destructible_healthdrain( 12, 0.2 );
			destructible_state( undefined, undefined, 800, undefined, 5, "no_melee" );
				destructible_fx( "tag_fx", "props/firehydrant_exp", false );
				destructible_fx( "tag_fx", "props/firehydrant_spray_10sec", false );
				destructible_sound( "firehydrant_burst" );
				destructible_explode( 17000, 18000, 96, 96, 32, 48 );   // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
			destructible_state( undefined, "com_firehydrant_dest", undefined, undefined, "no_melee" );

		// destroyed hydrant
		destructible_part( "tag_fx", "com_firehydrant_dam", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// side cap
		destructible_part( "tag_cap", "com_firehydrant_cap", undefined, undefined, undefined, undefined, 1.0, 1.0 );
}

toy_parkingmeter( destructibleType )
{
	//---------------------------------------------------------------------
	// parking meter toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_meter", 120 );
				destructible_fx( "tag_fx", "props/parking_meter_coins", true, damage_not( "splash" ) ); // coin drop
				destructible_fx( "tag_fx", "props/parking_meter_coins_exploded", true, "splash" );	  // coin drop
				destructible_sound( "exp_parking_meter_sweet" );										// coin drop sounds
				destructible_explode( 2800, 3000, 64, 64, 0, 0, true );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continue to take damage
			destructible_state( undefined, "com_parkingmeter_damaged", 20, undefined, undefined, "splash" );
			destructible_state( undefined, "com_parkingmeter_destroyed", undefined, undefined, undefined, undefined, undefined, true );

		// coin collector's cap
		destructible_part( "tag_cap", "com_parkingmeter_cap", undefined, undefined, undefined, undefined, 1.0, 1.0 );
}

toy_mailbox( destructibleType )
{
	//---------------------------------------------------------------------
	// mail box without pole
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 200 );
				destructible_fx( "tag_fx", "props/mail_box_explode", true );		// mail flying
				destructible_sound( "exp_mailbox_sweet" );						  // mail paper sounds
				destructible_explode( 100, 2000, 64, 64, 0, 0 );	// force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
			destructible_state( "tag_origin", "com_mailbox_dam" );
		destructible_part( "tag_door", "com_mailbox_door", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_flag", "com_mailbox_flag", undefined, undefined, undefined, undefined, 1.0, 1.0 );

}

toy_mailbox2( color )
{
	//---------------------------------------------------------------------
	// mailbox2 w/ pole toy
	//---------------------------------------------------------------------
	destructible_create( "toy_mailbox2_" + color, "tag_origin", 120 );
				destructible_fx( "tag_fx", "props/mail_box_explode", true, damage_not( "splash" ) );	// bullet damages
				destructible_fx( "tag_fx", "props/mail_box_explode", true, "splash" );				  // grenade damages
				destructible_sound( "exp_mailbox_sweet" );
				destructible_explode( 2800, 3000, 64, 64, 0, 0, true );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continue to take damage
			destructible_state( undefined, "mailbox_" + color + "_dam", 20, undefined, undefined, "splash" );
			destructible_state( undefined, "mailbox_black_dest", undefined, undefined, undefined, undefined, undefined, true );

		// mailbox door
		destructible_part( "tag_door", "mailbox_" + color + "_door", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_flag", "mailbox_black_flag", undefined, undefined, undefined, undefined, 1.0, 1.0 );
}


toy_newspaper_stand_red( destructibleType )
{
	//---------------------------------------------------------------------
	// newspaper stand toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 120 );
			destructible_fx( "tag_door", "props/news_stand_paper_spill", true, damage_not( "splash" ) );		// coin drop
			destructible_sound( "exp_newspaper_box" );												  // coin drop sounds
			destructible_explode( 2500, 2501, 64, 64, 0, 0, true );												 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continue to take damage
		destructible_state( undefined, "com_newspaperbox_red_dam", 20, undefined, undefined, "splash" );
			destructible_fx( "tag_fx", "props/news_stand_explosion", true, "splash" );						  // coin drop
		destructible_state( undefined, "com_newspaperbox_red_des", undefined, undefined, undefined, undefined, undefined, false );

		// front door
		destructible_part( "tag_door", "com_newspaperbox_red_door", undefined, undefined, undefined, undefined, 1.0, 1.0 );
}

toy_newspaper_stand_blue( destructibleType )
{
	//---------------------------------------------------------------------
	// newspaper stand toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 120 );
			destructible_fx( "tag_door", "props/news_stand_paper_spill_shatter", true, damage_not( "splash" ) );		// coin drop
			destructible_sound( "exp_newspaper_box" );												  // coin drop sounds
			destructible_explode( 800, 2001, 64, 64, 0, 0, true );											  // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continue to take damage
		destructible_state( undefined, "com_newspaperbox_blue_dam", 20, undefined, undefined, "splash" );
			destructible_fx( "tag_fx", "props/news_stand_explosion", true, "splash" );						  // coin drop
		destructible_state( undefined, "com_newspaperbox_blue_des", undefined, undefined, undefined, undefined, undefined, false );

		// front door
		destructible_part( "tag_door", "com_newspaperbox_blue_door", undefined, undefined, undefined, undefined, 1.0, 1.0 );

}

toy_filecabinet( destructibleType )
{
	//---------------------------------------------------------------------
	// filecabinet toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 120 );
				destructible_fx( "tag_drawer_lower", "props/filecabinet_dam", true, damage_not( "splash" ) );	   // coin drop
				destructible_sound( "exp_filecabinet" );
		destructible_state( undefined, "com_filecabinetblackclosed_dam", 20, undefined, undefined, "splash" );
				destructible_fx( "tag_drawer_upper", "props/filecabinet_des", true, "splash" );						 // coin drop
				destructible_sound( "exp_filecabinet" );											// coin drop sounds
				destructible_physics( "tag_drawer_upper", ( 50, -10, 5 ) );														 // coin drop sounds
		destructible_state( undefined, "com_filecabinetblackclosed_des", undefined, undefined, undefined, undefined, undefined, false );

		// front door
		destructible_part( "tag_drawer_upper", "com_filecabinetblackclosed_drawer", undefined, undefined, undefined, undefined, 1.0, 1.0 );

}

toy_trashbin_01( destructibleType )
{
	//---------------------------------------------------------------------
	// trashbin01 toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 120, undefined, 32, "no_melee" );
				destructible_fx( "tag_fx", "props/garbage_spew_des", true, "splash" );
				destructible_fx( "tag_fx", "props/garbage_spew", true, damage_not( "splash" ) );
				destructible_sound( "exp_trashcan_sweet" );															 
				destructible_explode( 1300, 1351, 1, 1, 10, 20 );   // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage

		destructible_state( undefined, "com_trashbin01_dmg", undefined, undefined, undefined, undefined, undefined, false );

		destructible_part( "tag_fx", "com_trashbin01_lid", undefined, undefined, undefined, undefined, 1.0, 1.0 );

}

toy_trashbin_02( destructibleType )
{
	//---------------------------------------------------------------------
	// trashbin02 toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 120, undefined, 32, "no_melee" );
				destructible_fx( "tag_fx", "props/garbage_spew_des", true, "splash" );
				destructible_fx( "tag_fx", "props/garbage_spew", true, damage_not( "splash" ) );
				destructible_sound( "exp_trashcan_sweet" );															 
				destructible_explode( 600, 800, 1, 1, 10, 20 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage

		destructible_state( undefined, "com_trashbin02_dmg", undefined, undefined, undefined, undefined, undefined, false );

		destructible_part( "tag_fx", "com_trashbin02_lid", undefined, undefined, undefined, undefined, 1.0, 1.0 );

}

toy_trashbag1( color )
{
	//---------------------------------------------------------------------
	// trashbag1 toy
	//---------------------------------------------------------------------
	destructible_create( "toy_trashbag1_" + color, "tag_origin", 120, undefined, 32, "no_melee" );
				destructible_fx( "tag_fx", "props/trashbag_" + color );
				//destructible_sound( "exp_trashcan_sweet" );															 

		destructible_state( undefined, "com_trashbag1_" + color + "_dsr", undefined, undefined, undefined, undefined, undefined, false );

}

toy_recyclebin_01( destructibleType )
{
	//---------------------------------------------------------------------
	// recyclebin toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 120, undefined, 32, "no_melee" );
				destructible_fx( "tag_fx", "props/garbage_spew_des", true, "splash" );
				destructible_fx( "tag_fx", "props/garbage_spew", true, damage_not( "splash" ) );
				destructible_sound( "exp_trashcan_sweet" );															 
				destructible_explode( 600, 651, 1, 1, 10, 20 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage

		destructible_state( undefined, "com_recyclebin01_dmg", undefined, undefined, undefined, undefined, undefined, false );


		destructible_part( "tag_fx", "com_recyclebin01_lid", undefined, undefined, undefined, undefined, 1.0, 1.0 );

}

toy_trashcan_metal_closed( destructibleType )
{
	//---------------------------------------------------------------------
	// trashcan_metal_closed
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 120, undefined, 32, "no_melee" );
			destructible_fx( "tag_fx", "props/garbage_spew_des", true, "splash" );
			destructible_fx( "tag_fx", "props/garbage_spew", true, damage_not( "splash" ) );
			destructible_sound( "exp_trashcan_sweet" );															 
			destructible_explode( 600, 651, 1, 1, 10, 20 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
		destructible_state( undefined, "com_trashcan_metal_with_trash", undefined, undefined, undefined, undefined, undefined, false );

		destructible_part( "tag_fx", "com_trashcan_metalLID", undefined, undefined, undefined, undefined, 1.0, 1.0 );
}

toy_water_collector( destructibleType )
{
	//---------------------------------------------------------------------
	// utility_water_collector - big blue odd shaped water barrels
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 220, undefined, 32, "no_melee" );
			destructible_fx( "tag_fx", "explosions/water_collector_explosion" );
			destructible_sound( "water_collector_splash" );															 
			destructible_explode( 500, 800, 32, 32, 1, 10, undefined, 32 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continue damage, originoffset
		destructible_state( undefined, "utility_water_collector_base_dest", undefined, undefined, "no_melee", undefined, undefined, false );

		destructible_part( "tag_lid", undefined, 220, undefined, undefined, "no_melee", 1.0 );
			destructible_state( undefined );
}

toy_foliage_tree_oak_1( destructibleType )
{
	//---------------------------------------------------------------------
	// foliage_tree_oak_1 destructible tree (splash damage only)
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 120, undefined, 32, "splash" );
				destructible_fx( "tag_fx", "explosions/tree_trunk_explosion_oak_1", true, "splash" );
				destructible_sound( "large_oak_tree_impact" );														  
				destructible_sound( "large_oak_tree_fall" );															
				//destructible_fx( "tag_fx", "explosions/tree_trunk_explosion_oak_1", true, damage_not( "splash" ) );
				destructible_explode( 600, 651, 1, 1, 10, 20 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage

		destructible_state( undefined, "foliage_tree_oak_1_destroyed_trunk", undefined, undefined, undefined, undefined, undefined, false );

}

toy_paris_tree_plane_large( destructibleType )
{
	//---------------------------------------------------------------------
	// paris_tree_plane destructible tree (splash damage only)
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 250, undefined, 32, "splash" );
				destructible_fx( "tag_origin", "props/paris_tree_plane_destruct" );
				//destructible_sound( "large_oak_tree_impact" );														  
				//destructible_sound( "large_oak_tree_fall" );															
				destructible_explode( 100, 351, 150, 350, 100, 200, undefined,undefined,undefined,undefined,(-400,0,80), 0.7 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continueDamage, originOffset, earthQuakeScale, earthQuakeRadius, originOffset3d, delaytime
				//destructible_explode( 300, 351, 250, 400, 100, 200, undefined,undefined,undefined,undefined,(-400,0,80), 0.7 );
		destructible_state( undefined, "foliage_paris_tree_plane_broken", undefined, undefined, undefined, undefined, undefined, false );

}


toy_usa_gas_station_trash_bin_01( destructibleType )
{
	//---------------------------------------------------------------------
	// usa_gas_station_trash_bin_01 toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 120, undefined, 32, "no_melee" );
				destructible_fx( "tag_fx", "props/garbage_spew_des", true, "splash" );
				destructible_fx( "tag_fx", "props/garbage_spew", true, damage_not( "splash" ) );
				destructible_explode( 600, 651, 1, 1, 10, 20 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage

		destructible_state( undefined, "usa_gas_station_trash_bin_01_base", undefined, undefined, undefined, undefined, undefined, false );

		destructible_part( "tag_fx", "usa_gas_station_trash_bin_01_lid", undefined, undefined, undefined, undefined, 1.0, 1.0 );

}

toy_usa_gas_station_trash_bin_02( destructibleType )
{
	//---------------------------------------------------------------------
	// usa_gas_station_trash_bin_02 toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 120, undefined, 32, "no_melee" );
				destructible_fx( "tag_fx_high", "props/garbage_spew_des", true, "splash" );
				destructible_fx( "tag_fx_high", "props/garbage_spew", true, damage_not( "splash" ) );
				destructible_explode( 600, 651, 1, 1, 10, 20 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage

		destructible_state( undefined, "usa_gas_station_trash_bin_02_base", undefined, undefined, undefined, undefined, undefined, false );


		destructible_part( "tag_fx_high", "usa_gas_station_trash_bin_02_lid", undefined, undefined, undefined, undefined, 1.0, 1.0 );

}


toy_light_ceiling_round( destructibleType )
{
	//---------------------------------------------------------------------
	// Ceiling round light
	//---------------------------------------------------------------------
	//println( "Ceiling light round being destroyed " );
	destructible_create( destructibleType, "tag_origin", 150, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );
			destructible_lights_out( 16 );
			destructible_fx( "tag_fx", "misc/light_blowout_runner" );
		destructible_state( undefined, "com_light_ceiling_round_off", undefined, undefined, "no_melee" );
}

toy_light_ceiling_fluorescent( destructibleType )
{
	//---------------------------------------------------------------------
	// Ceiling fluorescent light
	//---------------------------------------------------------------------
	println( "Ceiling light fluorescent being destroyed " );
	destructible_create( destructibleType, "tag_origin", 150, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );			
			destructible_fx( "tag_fx", "misc/light_fluorescent_blowout_runner" );
			destructible_fx( "tag_swing_fx", "misc/light_blowout_swinging_runner" );
			destructible_lights_out( 16 );
			destructible_explode( 20, 2000, 64, 64, 40, 80 );   // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
			destructible_anim( get_precached_anim( "light_fluorescent_swing" ), #animtree, "setanimknob", undefined, 0, "light_fluorescent_swing" );
				destructible_sound( "fluorescent_light_fall", undefined, 0 ); 
				destructible_sound( "fluorescent_light_bulb", undefined, 0  ); 
				//destructible_sound( "fluorescent_light_spark", undefined, 0  ); 
			destructible_anim( get_precached_anim( "light_fluorescent_swing_02" ), #animtree, "setanimknob", undefined, 1, "light_fluorescent_swing_02" );
				destructible_sound( "fluorescent_light_fall", undefined, 1  ); 
				destructible_sound( "fluorescent_light_bulb", undefined, 1  ); 
				//destructible_sound( "fluorescent_light_spark", undefined, 1  ); 
			destructible_anim( get_precached_anim( "light_fluorescent_null" ), #animtree, "setanimknob", undefined, 2, "light_fluorescent_null" );
		destructible_state( undefined, "me_lightfluohang_double_destroyed", undefined, undefined, "no_melee" );
		
		
}

toy_light_ceiling_fluorescent_spotlight( destructibleType )
{
	//---------------------------------------------------------------------
	// Ceiling fluorescent light
	//---------------------------------------------------------------------
	println( "Ceiling light fluorescent being destroyed " );
	destructible_create( destructibleType, "tag_origin", 150, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );
			destructible_sound( "fluorescent_light_bulb" ); 
			//destructible_sound( "fluorescent_light_spark" ); //played in effect   
			destructible_fx( "tag_fx", "misc/light_fluorescent_blowout_runner" );
			destructible_fx( "tag_swing_fx", "misc/light_blowout_swinging_runner" );
			destructible_lights_out( 16 );
			destructible_explode( 20, 2000, 64, 64, 40, 80 );   // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
			destructible_anim( get_precached_anim( "light_fluorescent_swing" ), #animtree, "setanimknob", undefined, 0, "light_fluorescent_swing" );
				destructible_sound( "fluorescent_light_fall", undefined, 0 ); 
				destructible_sound( "fluorescent_light_bulb", undefined, 0  ); 
				//destructible_sound( "fluorescent_light_spark", undefined, 0  ); 
			destructible_spotlight( "tag_swing_r_far" );
			destructible_sound( "fluorescent_light_fall" ); 
		destructible_state( undefined, "me_lightfluohang_double_destroyed", undefined, undefined, "no_melee" );
}

toy_light_ceiling_fluorescent_single( destructibleType )
{
	//---------------------------------------------------------------------
	// Ceiling fluorescent light
	//---------------------------------------------------------------------
	println( "Ceiling light fluorescent being destroyed " );
	destructible_create( destructibleType, "tag_origin", 150, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );	
			destructible_fx( "tag_fx", "misc/light_fluorescent_single_blowout_runner" );
			destructible_fx( "tag_swing_center_fx", "misc/light_blowout_swinging_runner" );
			destructible_fx( "tag_swing_center_fx_far", "misc/light_blowout_swinging_runner" );
			destructible_lights_out( 32 );
			destructible_explode( 20, 2000, 64, 64, 40, 80 );   // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
			destructible_anim( get_precached_anim( "light_fluorescent_single_swing" ), #animtree, "setanimknob", undefined, 0, "light_fluorescent_single_swing" );
				destructible_sound( "fluorescent_light_fall", undefined, 0 ); 
				destructible_sound( "fluorescent_light_bulb", undefined, 0  ); 
				//destructible_sound( "fluorescent_light_spark", undefined, 0  ); 
			destructible_anim( get_precached_anim( "light_fluorescent_single_swing_02" ), #animtree, "setanimknob", undefined, 1, "light_fluorescent_single_swing_02" );
				destructible_sound( "fluorescent_light_hinge", undefined, 1  ); 
				destructible_sound( "fluorescent_light_bulb", undefined, 1  ); 
				//destructible_sound( "fluorescent_light_spark", undefined, 1  ); 
			destructible_anim( get_precached_anim( "light_fluorescent_single_swing_03" ), #animtree, "setanimknob", undefined, 2, "light_fluorescent_single_swing_03" );
				destructible_sound( "fluorescent_light_fall", undefined, 2  ); 
				destructible_sound( "fluorescent_light_bulb", undefined, 2  ); 
				//destructible_sound( "fluorescent_light_spark", undefined, 2  ); 
			destructible_anim( get_precached_anim( "light_fluorescent_single_null" ), #animtree, "setanimknob", undefined, 3, "light_fluorescent_single_null" );
		destructible_state( undefined, "me_lightfluohang_single_destroyed", undefined, undefined, "no_melee" );
}

toy_light_ceiling_fluorescent_single_spotlight( destructibleType )
{
	//---------------------------------------------------------------------
	// Ceiling fluorescent light
	//---------------------------------------------------------------------
	println( "Ceiling light fluorescent single being destroyed " );
	destructible_create( destructibleType, "tag_origin", 150, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );
			destructible_lights_out( 16 );
			destructible_sound( "fluorescent_light_bulb" ); 
			//destructible_sound( "fluorescent_light_spark" ); //played in effect 
			destructible_fx( "tag_fx", "misc/light_fluorescent_single_blowout_runner" );
			destructible_fx( "tag_swing_center_fx", "misc/light_blowout_swinging_runner" );
			destructible_fx( "tag_swing_center_fx_far", "misc/light_blowout_swinging_runner" );
			destructible_explode( 20, 2000, 64, 64, 40, 80 );   // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
			destructible_anim( get_precached_anim( "light_fluorescent_single_swing_02" ), #animtree, "setanimknob", undefined, undefined, "light_fluorescent_single_swing_02" );
			destructible_sound( "fluorescent_light_fall" ); 
			destructible_spotlight( "tag_swing_center_fx_far" );
		destructible_state( undefined, "me_lightfluohang_single_destroyed", undefined, undefined, "no_melee" );
}

toy_bookstore_bookstand4_books( destructibleType )
{
	//---------------------------------------------------------------------
	// bookstore_bookstand4_books
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 200, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 7 );
			destructible_fx( "tag_fx", "props/bookshelf4_dmg", true, damage_not( "splash" ) );
			//destructible_sound( "copier_exp" );
		destructible_state( undefined, "bookstore_bookstand4", 100, undefined, undefined, "splash" );
			destructible_fx( "tag_fx", "props/bookshelf4_des", true, "splash" );
			destructible_explode( 2000, 3800, 32, 32, 1, 5, undefined, 0 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continueDamage, originOffset, earthQuakeScale, earthQuakeRadius 
		destructible_state( undefined, "bookstore_bookstand4_null", undefined, undefined, undefined, undefined, undefined, false );
}

toy_locker_double( destructibleType )
{
	//---------------------------------------------------------------------
	// Locker Double
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 150, undefined, 32, "no_melee" );
				
				destructible_anim( get_precached_anim( "locker_broken_both_doors_1" ), #animtree, "setanimknob", undefined, 0, "locker_broken_both_doors_1" );
				destructible_fx( "tag_fx", "props/locker_double_des_02_right", undefined, undefined, 0 );
				destructible_sound( "lockers_fast", undefined, 0 );
				
				destructible_anim( get_precached_anim( "locker_broken_both_doors_2" ), #animtree, "setanimknob", undefined, 1, "locker_broken_both_doors_2" );
				destructible_fx( "tag_fx", "props/locker_double_des_01_left", undefined, undefined, 1 );
				destructible_sound( "lockers_fast", undefined, 1 );
				
				destructible_anim( get_precached_anim( "locker_broken_both_doors_4" ), #animtree, "setanimknob", undefined, 2, "locker_broken_both_doors_4" );
				destructible_fx( "tag_fx", "props/locker_double_des_03_both", undefined, undefined, 2 );
				destructible_sound( "lockers_double", undefined, 2 );

				destructible_anim( get_precached_anim( "locker_broken_door1_fast" ), #animtree, "setanimknob", undefined, 3, "locker_broken_door1_fast" );
				destructible_fx( "tag_fx", "props/locker_double_des_01_left", undefined, undefined, 3 );
				destructible_sound( "lockers_fast", undefined, 3 );
				
				destructible_anim( get_precached_anim( "locker_broken_door2_fast" ), #animtree, "setanimknob", undefined, 4, "locker_broken_door2_fast" );
				destructible_fx( "tag_fx", "props/locker_double_des_02_right", undefined, undefined, 4 );
				destructible_sound( "lockers_fast", undefined, 4 );
				
				destructible_anim( get_precached_anim( "locker_broken_both_doors_3" ), #animtree, "setanimknob", undefined, 5, "locker_broken_both_doors_3" );
				destructible_fx( "tag_fx", "misc/no_effect", undefined, undefined, 5 );
				destructible_sound( "lockers_minor", undefined, 5 );
				
				destructible_anim( get_precached_anim( "locker_broken_door1_slow" ), #animtree, "setanimknob", undefined, 6, "locker_broken_door1_slow" );
				destructible_fx( "tag_fx", "misc/no_effect", undefined, undefined, 6 );
				destructible_sound( "lockers_minor", undefined, 6 );
				
				destructible_anim( get_precached_anim( "locker_broken_door2_slow" ), #animtree, "setanimknob", undefined, 7, "locker_broken_door2_slow" );
				destructible_fx( "tag_fx", "misc/no_effect", undefined, undefined, 7 );
				destructible_sound( "lockers_minor", undefined, 7 );
				
		destructible_state( undefined, "com_locker_double_destroyed", undefined, undefined, "no_melee" );
}

toy_dubai_fish_sculpture( destructibleType, color, numBones )
{
	//---------------------------------------------------------------------
	// dubai_fish_sculpture
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 200000000, undefined, 32, "no_melee" );
	destructible_splash_damage_scaler( 2 );
	for(i=1; i<=numBones; i++)
		{
			destructible_part( "tag_" + color + "_" + i, destructibleType, 10);
				destructible_fx("tag_" + color + "_" + i, "props/dub_fish_" + color + "_shatter");
				destructible_state( undefined );
		}
}

toy_intro_concrete_chipaway( destructibleType, numChunks )
{
	//---------------------------------------------------------------------
	// Intro walls with concrete chunks that can be chipped away
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 200000000, undefined, 32, "no_melee" );
	destructible_state( "tag_origin", destructibleType, undefined, undefined, "no_melee" );
	for(i=1; i<=numChunks; i++)
	{
		destructible_part( "tag_chunk_" + i, destructibleType, 200, undefined, undefined, "no_splash");
			destructible_splash_damage_scaler( 0.01 );
			destructible_fx("tag_chunk_" + i, "props/intro_wall_chunk_exp");
			destructible_state( undefined );
	}
}

toy_chicken( version )
{
	//---------------------------------------------------------------------
	// Chicken
	//---------------------------------------------------------------------
	destructible_create( "toy_chicken" + version, "tag_origin", 0, undefined, 32 );
			destructible_anim( get_precached_anim( "chicken_cage_loop_01" ), #animtree, "setanimknob", undefined, 0, "chicken_cage_loop_01", 1.6 );
			destructible_anim( get_precached_anim( "chicken_cage_loop_02" ), #animtree, "setanimknob", undefined, 1, "chicken_cage_loop_02", 1.6 );
			destructible_loopsound( "animal_chicken_idle_loop" );
		destructible_state( "tag_origin", "chicken" + version, 25 );
			destructible_fx( "tag_origin", "props/chicken_exp" + version );
			destructible_anim( get_precached_anim( "chicken_cage_death" ), #animtree, "setanimknob", undefined, 0, "chicken_cage_death" );
			destructible_anim( get_precached_anim( "chicken_cage_death_02" ), #animtree, "setanimknob", undefined, 1, "chicken_cage_death_02" );
			destructible_sound( "animal_chicken_death" );
		destructible_state( undefined, "chicken" + version, undefined, undefined, "no_melee" ); 
}


toy_hide_with_fx( destructibleType, part, efx, health )
{
	destructible_create( destructibleType, part, health );
			destructible_fx( "tag_origin", efx );
		destructible_state( "tag_origin", "generic_prop_raven" ); // generic_prop_raven is invisible
}


vehicle_ac130_80s_sedan1( color )
{
	//---------------------------------------------------------------------
	// 80's Sedan
	//---------------------------------------------------------------------
	destructible_create( "vehicle_ac130_80s_sedan1_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_80s_sedan1_" + color + "_destroyed", undefined, 32, "no_melee" );
		// Hood
		tag = "tag_hood";
		destructible_part( tag, "vehicle_80s_sedan1_" + color + "_hood", undefined, undefined, undefined, undefined, 1.0, 2.5 );
		//Trunk
		tag = "tag_trunk";
		destructible_part( tag, "vehicle_80s_sedan1_" + color + "_trunk", undefined, undefined, undefined, undefined, 1.0 );
		// Tires
		destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", "vehicle_80s_sedan1_" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", "vehicle_80s_sedan1_" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 2.3 );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		destructible_part( "tag_door_left_front", undefined, undefined, undefined, undefined, undefined, 1.0 );
		destructible_part( "tag_door_left_back", undefined, undefined, undefined, undefined, undefined, 1.0 );
		destructible_part( "tag_door_right_front", "vehicle_80s_sedan1_" + color + "_door_RF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_door_right_back", "vehicle_80s_sedan1_" + color + "_door_RB", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Left )
		tag = "tag_light_left_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Right )
		tag = "tag_light_right_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Bumpers
		destructible_part( "tag_bumper_front", "vehicle_80s_sedan1_" + color + "_bumper_F", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_bumper_back", "vehicle_80s_sedan1_" + color + "_bumper_B", undefined, undefined, undefined, undefined, undefined, 1.0 );
		// Side Mirrors
		destructible_part( "tag_mirror_left", "vehicle_80s_sedan1_" + color + "_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
		destructible_part( "tag_mirror_right", "vehicle_80s_sedan1_" + color + "_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
}

vehicle_bus_destructible( destructibleType )
{
	//---------------------------------------------------------------------
	// Bus
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		// Glass ( Front Left )
		/**WIItag = "tag_window_front_left";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Front Right )
		tag = "tag_window_front_right";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Driver Side )
		tag = "tag_window_driver";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Back of bus )
		tag = "tag_window_back";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Right Side )
		tag = "tag_window_side_1";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Right Side )
		tag = "tag_window_side_2";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Right Side )
		tag = "tag_window_side_3";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Right Side )
		tag = "tag_window_side_4";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Right Side )
		tag = "tag_window_side_5";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Left Side )
		tag = "tag_window_side_6";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Left Side )
		tag = "tag_window_side_7";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Left Side )
		tag = "tag_window_side_8";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Left Side )
		tag = "tag_window_side_9";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Left Side )
		tag = "tag_window_side_10";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );

		// Glass ( Left Side )
		tag = "tag_window_side_11";
		destructible_part( tag, undefined, 99, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 200, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );*/

}

vehicle_80s_sedan1( color )
{
	//---------------------------------------------------------------------
	// 80's Sedan
	//---------------------------------------------------------------------
	destructible_create( "vehicle_80s_sedan1_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 150, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_80s_sedan1_" + color + "_destroyed", undefined, 32, "no_melee" );
		// Hood
		tag = "tag_hood";
		destructible_part( tag, "vehicle_80s_sedan1_" + color + "_hood", undefined, undefined, undefined, undefined, 1.0, 2.5 );
		//Trunk
		tag = "tag_trunk";
		destructible_part( tag, "vehicle_80s_sedan1_" + color + "_trunk", undefined, undefined, undefined, undefined, 1.0 );
		// Tires
		destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", "vehicle_80s_sedan1_" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", "vehicle_80s_sedan1_" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 2.3 );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		destructible_part( "tag_door_left_front", undefined, undefined, undefined, undefined, undefined, 1.0 );
		destructible_part( "tag_door_left_back", undefined, undefined, undefined, undefined, undefined, 1.0 );
		destructible_part( "tag_door_right_front", "vehicle_80s_sedan1_" + color + "_door_RF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_door_right_back", "vehicle_80s_sedan1_" + color + "_door_RB", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Left )
		tag = "tag_light_left_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Right )
		tag = "tag_light_right_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Bumpers
		destructible_part( "tag_bumper_front", "vehicle_80s_sedan1_" + color + "_bumper_F", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_bumper_back", "vehicle_80s_sedan1_" + color + "_bumper_B", undefined, undefined, undefined, undefined, undefined, 1.0 );
		// Side Mirrors
		destructible_part( "tag_mirror_left", "vehicle_80s_sedan1_" + color + "_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
		destructible_part( "tag_mirror_right", "vehicle_80s_sedan1_" + color + "_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
}

vehicle_80s_hatch1( color )
{
	//---------------------------------------------------------------------
	// 80's hatchback
	//---------------------------------------------------------------------
	destructible_create( "vehicle_80s_hatch1_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 150, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_80s_hatch1_" + color + "_destroyed", undefined, 32, "no_melee" );
		// Hood
		//*tag = "tag_hood";
		//*destructible_part( tag, "vehicle_80s_hatch1_" + color + "_hood", 800, undefined, undefined, undefined, 1.0, 1.5 );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_80s_hatch1_" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", "vehicle_80s_hatch1_" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		//*destructible_part( "tag_door_left_front", undefined, undefined, undefined, undefined, undefined, 1.0 );
		//*destructible_part( "tag_door_right_front", "vehicle_80s_hatch1_" + color + "_door_RF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 10, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 10, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 10, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 10, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 10, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 10, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Left )
		tag = "tag_light_left_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Right )
		tag = "tag_light_right_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Bumpers
		destructible_part( "tag_bumper_front" );
		destructible_part( "tag_bumper_back" );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_80s_hatch1_" + color + "_mirror_L", 40 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_80s_hatch1_" + color + "_mirror_R", 40 );
			//*destructible_physics();
}

vehicle_80s_hatch2( color )
{
	//---------------------------------------------------------------------
	// 80's hatchback 2
	//---------------------------------------------------------------------
	destructible_create( "vehicle_80s_hatch2_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 150, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_80s_hatch2_" + color + "_destroyed", undefined, 32, "no_melee" );
		// Hood
		tag = "tag_hood";
		destructible_part( tag, "vehicle_80s_hatch2_" + color + "_hood", 800, undefined, undefined, undefined, 1.0, 1.5 );
		// Tires
		destructible_part( "left_wheel_01_jnt", "vehicle_80s_hatch2_" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", "vehicle_80s_hatch2_" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		destructible_part( "tag_door_left_front", undefined, undefined, undefined, undefined, undefined, 1.0 );
		destructible_part( "tag_door_right_front", "vehicle_80s_hatch2_" + color + "_door_RF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Left )
		tag = "tag_light_left_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Right )
		tag = "tag_light_right_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Bumpers
		destructible_part( "tag_bumper_front" );
		destructible_part( "tag_bumper_back" );
		// Side Mirrors
		destructible_part( "tag_mirror_left", "vehicle_80s_hatch2_" + color + "_mirror_L", 40 );
			destructible_physics();
		destructible_part( "tag_mirror_right", "vehicle_80s_hatch2_" + color + "_mirror_R", 40 );
			destructible_physics();
}

vehicle_80s_wagon1( color )
{
	//---------------------------------------------------------------------
	// 80's wagon
	//---------------------------------------------------------------------
	destructible_create( "vehicle_80s_wagon1_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 150, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_80s_wagon1_" + color + "_destroyed", undefined, 32, "no_melee" );
		// Hood
		//*tag = "tag_hood";
		//*destructible_part( tag, "vehicle_80s_wagon1_" + color + "_hood", 800, undefined, undefined, undefined, 1.0, 1.5 );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", "vehicle_80s_wagon1_" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", "vehicle_80s_wagon1_" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		//*destructible_part( "tag_door_left_front", undefined, undefined, undefined, undefined, undefined, 1.0 );
		//*destructible_part( "tag_door_left_back", undefined, undefined, undefined, undefined, undefined, 1.0 );
		//*destructible_part( "tag_door_right_front", undefined, undefined, undefined, undefined, undefined, 1.0 );
		//*destructible_part( "tag_door_right_back", "vehicle_80s_wagon1_" + color + "_door_RB", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back 2 )
		tag = "tag_glass_left_back2";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back2_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back 2 )
		tag = "tag_glass_right_back2";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back2_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Left )
		tag = "tag_light_left_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Right )
		tag = "tag_light_right_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Bumpers
		//*destructible_part( "tag_bumper_front", "vehicle_80s_wagon1_" + color + "_bumper_F", undefined, undefined, undefined, undefined, 1.0, 0.7 );
		//*destructible_part( "tag_bumper_back", undefined, undefined, undefined, undefined, undefined, undefined, 0.6 );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_80s_wagon1_" + color + "_mirror_L", 40 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_80s_wagon1_" + color + "_mirror_R", 40 );
			//*destructible_physics();
}
vehicle_civ_car_a( number )
{
	//---------------------------------------------------------------------
	// civilian car a - very low poly
	//---------------------------------------------------------------------
	
	useCV = false;
	
	if( number == 2 )
	{
		useCV = true;
	}
	
	if( number == 5 )
		destructible_create( "vehicle_civ_car_a_" + number, "ac_prs_veh_civ_car_a_" + 3 + "_lod0", 250, undefined, 32, "no_melee" );
	else
		destructible_create( "vehicle_civ_car_a_" + number, "ac_prs_veh_civ_car_a_" + number + "_lod0", 250, undefined, 32, "no_melee" );
	
	if( useCV )
	{
			destructible_state( "ac_prs_veh_civ_car_a_dam" + number + "_cv_lod0", "ac_prs_veh_civ_car_a_dam" + number + "_cv", 250, undefined, 32, "no_melee" );
	}
	else
	{
		if( number == 4 )
			destructible_state( "ac_prs_veh_civ_car_a_" + number + "_lod0", "ac_prs_veh_civ_car_a_dam" + number, 250, undefined, 32, "no_melee" );
		else if( number == 5 )
			destructible_state( "ac_prs_veh_civ_car_a_" + 3 + "_lod0", "ac_prs_veh_civ_car_a_dam" + number, 250, undefined, 32, "no_melee" );
		else
			destructible_state( "ac_prs_veh_civ_car_a_dam" + number + "_lod0", "ac_prs_veh_civ_car_a_dam" + number, 250, undefined, 32, "no_melee" );
	}
				destructible_fx( undefined, "explosions/small_vehicle_explosion_ac130", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

vehicle_small_hatch( color )
{
	//---------------------------------------------------------------------
	// small hatch
	//---------------------------------------------------------------------
	destructible_create( "vehicle_small_hatch_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 150, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_small_hatch_" + color + "_destroyed", undefined, 32, "no_melee" );
		// Hood
		//*tag = "tag_hood";
		//*destructible_part( tag, "vehicle_small_hatch_" + color + "_hood", 800, undefined, undefined, undefined, 1.0, 1.5 );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		//*destructible_part( "tag_door_left_front", "vehicle_small_hatch_" + color + "_door_LF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		//*destructible_part( "tag_door_right_front", "vehicle_small_hatch_" + color + "_door_RF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Left )
		tag = "tag_light_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Right )
		tag = "tag_light_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Bumpers
		//*destructible_part( "tag_bumper_front", undefined, undefined, undefined, undefined, undefined, 1.0 );
		//*destructible_part( "tag_bumper_back", undefined, undefined, undefined, undefined, undefined, 0.5 );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_small_hatch_" + color + "_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_small_hatch_" + color + "_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}

vehicle_london_cab_black()
{
	//---------------------------------------------------------------------
	// london cab "vehicle_london_cab_black_destructible"
	//---------------------------------------------------------------------
	/*
	origin_animate_jnt
	  TAG_BODY
	    body_animate_jnt
	      TAG_BUMPER_BACK
	      TAG_BUMPER_FRONT
	      TAG_CENTER_GLASS
	      TAG_CENTER_GLASS_D
	      TAG_CENTER_GLASS_FX
	      TAG_DEATH_FX
	      TAG_DOOR_LEFT_BACK
	        TAG_GLASS_LEFT_BACK
	        TAG_GLASS_LEFT_BACK_02
	        TAG_GLASS_LEFT_BACK_02_D
	        TAG_GLASS_LEFT_BACK_02_FX
	        TAG_GLASS_LEFT_BACK_D
	        TAG_GLASS_LEFT_BACK_FX
	      TAG_DOOR_LEFT_FRONT
	        TAG_GLASS_LEFT_FRONT
	        TAG_GLASS_LEFT_FRONT_D
	        TAG_GLASS_LEFT_FRONT_FX
	        TAG_MIRROR_LEFT
	      TAG_DOOR_RIGHT_BACK
	        TAG_GLASS_RIGHT_BACK
	        TAG_GLASS_RIGHT_BACK_02
	        TAG_GLASS_RIGHT_BACK_02_D
	        TAG_GLASS_RIGHT_BACK_02_FX
	        TAG_GLASS_RIGHT_BACK_D
	        TAG_GLASS_RIGHT_BACK_FX
	      TAG_DOOR_RIGHT_FRONT
	        TAG_GLASS_RIGHT_FRONT
	        TAG_GLASS_RIGHT_FRONT_D
	        TAG_GLASS_RIGHT_FRONT_FX
	        TAG_MIRROR_RIGHT
	      TAG_DRIVER
	      TAG_GLASS_BACK
	      TAG_GLASS_BACK_D
	      TAG_GLASS_BACK_FX
	      TAG_GLASS_FRONT
	      TAG_GLASS_FRONT_D
	      TAG_GLASS_FRONT_FX
	      TAG_HOOD
	      TAG_HOOD_FX
	      TAG_LIGHT_LEFT_FRONT
	      TAG_LIGHT_LEFT_FRONT_D
	      TAG_LIGHT_RIGHT_FRONT
	      TAG_LIGHT_RIGHT_FRONT_D
	  TAG_WHEEL_BACK_LEFT
	    left_wheel_02_jnt
	  TAG_WHEEL_BACK_RIGHT
	    right_wheel_02_jnt
	  TAG_WHEEL_FRONT_LEFT
	    left_wheel_front_animate_jnt
	      left_wheel_01_jnt
	  TAG_WHEEL_FRONT_RIGHT
	    right_wheel_front_animate_jnt
	      right_wheel_01_jnt
	
	*/
	destructible_create( "vehicle_london_cab_black" , undefined, 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 150, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( undefined, "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_london_cab_destroyed", undefined, 32, "no_melee" );
		// Hood
		tag = "tag_hood";
		//*destructible_part( tag, "vehicle_london_cab_hood", 800, undefined, undefined, undefined, 1.0, 1.5 );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_london_cab_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 1.0 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", "vehicle_london_cab_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 1.0 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", "vehicle_london_cab_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 1.0 );
		//*	destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		//*destructible_part( "tag_door_left_front", "vehicle_london_cab_door_lb", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		//*destructible_part( "tag_door_right_front", "vehicle_london_cab_door_lb", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Front )
		tag = "tag_center_glass";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back 2)
		tag = "tag_glass_left_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back 2 )
		tag = "tag_glass_right_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Bumpers
		//*destructible_part( "tag_bumper_front", undefined, undefined, undefined, undefined, undefined, 1.0 );
		//*destructible_part( "tag_bumper_back", undefined, undefined, undefined, undefined, undefined, 0.5 );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_london_cab_mirror_l", 40, undefined, undefined, undefined, undefined, 1.0 );
		//*	destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_london_cab_mirror_r", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}


vehicle_pickup( destructibleType )
{
	//---------------------------------------------------------------------
	// White Pickup Truck
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 300, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 210, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			if( issubstr( self.model, "_moga" ) )
				destructible_state( undefined, "vehicle_pickup_destroyed_moga", undefined, 32, "no_melee" );
			else
				destructible_state( undefined, "vehicle_pickup_destroyed", undefined, 32, "no_melee" );
		// Hood
		//*tag = "tag_hood";
		//*destructible_part( tag, "vehicle_pickup_hood", 800, undefined, undefined, undefined, 1.0, 2.5 );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		//*destructible_part( "tag_door_left_front", "vehicle_pickup_door_LF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		//*destructible_part( "tag_door_right_front", "vehicle_pickup_door_RF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Left )
		tag = "tag_light_left_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Right )
		tag = "tag_light_right_back";
		destructible_part( tag, undefined, 20 );
			destructible_fx( tag, "props/car_glass_brakelight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Bumpers
		destructible_part( "tag_bumper_front", undefined, undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_bumper_back", undefined, undefined, undefined, undefined, undefined, undefined, 1.0 );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_pickup_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_pickup_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}

vehicle_hummer( destructibleType )
{   
	//---------------------------------------------------------------------
	// Hummer
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 400, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_deathfx", "explosions/vehicle_explosion_hummer", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 210, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_hummer_destroyed", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
}


vehicle_t72( destructibleType )
{   
	//---------------------------------------------------------------------
	// T72
	//---------------------------------------------------------------------
	//PreCacheModel("vehicle_gaz_tigr_harbor_destroyed");
	destructible_create( destructibleType, "tag_body", 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_deathfx", "fire/firelp_med_pm" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_deathfx", "fire/firelp_med_pm" );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_deathfx", "fire/firelp_med_pm" );
				destructible_fx( "tag_deathfx", "explosions/vehicle_explosion_t72", false );
				destructible_sound( "exp_armor_vehicle" );
				destructible_explode( 4000, 5000, 210, 250, 50, 300, undefined, undefined, 0.3, 500 );
			destructible_state( undefined, "vehicle_t72_tank_d_body", undefined, 32, "no_melee" );
}


vehicle_btr( destructibleType )
{   
	//---------------------------------------------------------------------
	// BTR
	//---------------------------------------------------------------------
	//PreCacheModel("vehicle_gaz_tigr_harbor_destroyed");
	destructible_create( destructibleType, "tag_body", 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_cargofire", "fire/firelp_med_pm" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_cargofire", "fire/firelp_med_pm" );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_cargofire", "fire/firelp_med_pm" );
				destructible_fx( "tag_deathfx", "explosions/vehicle_explosion_btr80", false );
				destructible_sound( "exp_armor_vehicle" );
				destructible_explode( 4000, 5000, 210, 250, 50, 300, undefined, undefined, 0.3, 500 );
			destructible_state( undefined, "vehicle_btr80_d_pc", undefined, 32, "no_melee" );
}


vehicle_gaz( destructibleType )
{   
	//---------------------------------------------------------------------
	// Gaz
	//---------------------------------------------------------------------
	//PreCacheModel("vehicle_gaz_tigr_harbor_destroyed");
	destructible_create( destructibleType, "tag_body", 400, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				//tag_engine_right should be replace with tag_hood_fx
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire_gaz", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				//tag_origin should be replace with tag_deathfx
				destructible_fx( "tag_deathfx", "explosions/vehicle_explosion_gaz", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 210, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_gaz_tigr_harbor_destroyed", undefined, 32, "no_melee" );
		// Tires
		destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left mid )
		tag = "tag_glass_left_mid";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_mid_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right mid )
		tag = "tag_glass_right_mid";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_mid_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back Left )
		tag = "tag_glass_back_left";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_left_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back Right )
		tag = "tag_glass_back_right";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_right_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
}


vehicle_gaz_harbor( destructibleType )
{   
	//---------------------------------------------------------------------
	// Destructible Gaz Harbor
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke_moving", 0.1 );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire_gaz_moving", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 25, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 1000, undefined, 32, "no_melee" );
				//tag_origin should be replace with tag_deathfx
				destructible_fx( "tag_deathfx", "explosions/vehicle_explosion_gaz", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 210, 250, 50, 300, undefined, undefined, 0.3, 500 );
				//destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_gaz_tigr_paris_destroyed", undefined, undefined, 32, "no_melee" );
		// Tires
		/*
		destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
			*/
		// Bumper
		destructible_part( "tag_frontbumper", undefined, 50, undefined, undefined, undefined, 1.0 );
			destructible_fx( "tag_hood_fx", "props/vehicle_gaz_frontBumper", false );
			destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_moving", 0.1 );
			destructible_state( undefined );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 10, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large_moving" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med_moving" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med_moving" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left mid )
		tag = "tag_glass_left_mid";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_mid_fx", "props/car_glass_med_moving" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right mid )
		tag = "tag_glass_right_mid";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_mid_fx", "props/car_glass_med_moving" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med_moving" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med_moving" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back Left )
		tag = "tag_glass_back_left";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_left_fx", "props/car_glass_med_moving" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back Right )
		tag = "tag_glass_back_right";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_right_fx", "props/car_glass_med_moving" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
}


vehicle_bm21( destructibleType, destroyedModel )
{
	//---------------------------------------------------------------------
	// BM21
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 300, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_deathfx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 210, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, destroyedModel, undefined, 32, "no_melee" );
		// Tires
		destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
}

vehicle_moving_truck( destructibleType )
{
	//---------------------------------------------------------------------
	// White Moving Truck
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 300, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/vehicle_explosion_medium", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 210, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
				
			if( destructibleType == "vehicle_moving_truck" )
				destructible_state( undefined, "vehicle_moving_truck_dst", undefined, 32, "no_melee" );
			else
				destructible_state( undefined, "vehicle_moving_truck_thai_dst", undefined, 32, "no_melee" );
			
		// Tires
		destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Bumpers
		//destructible_part( "tag_bumper_front", undefined, undefined, undefined, undefined, undefined, 1.0, 1.0 );
		//destructible_part( "tag_bumper_back", undefined, undefined, undefined, undefined, undefined, undefined, 1.0 );
}

vehicle_subway_cart( destructibleType )
{
	//---------------------------------------------------------------------
	// Subway car "vehicle_subway_cart_destructible"
	//---------------------------------------------------------------------

/*
   Just the doors!
	
body_animate_jnt
  J_LE_Front_Door_01
	TAG_WINDOW_SMALL_02_LE
	TAG_WINDOW_SMALL_02_LE_D
  J_LE_Front_Door_02
	TAG_WINDOW_SMALL_03_LE
	TAG_WINDOW_SMALL_03_LE_D
  J_LE_Front_Door_03
	TAG_WINDOW_SMALL_04_LE
	TAG_WINDOW_SMALL_04_LE_D
  J_LE_Front_Door_04
	TAG_WINDOW_SMALL_05_LE
	TAG_WINDOW_SMALL_05_LE_D
  J_RI_Front_Door_01
	TAG_WINDOW_SMALL_02_RI
	TAG_WINDOW_SMALL_02_RI_D
  J_RI_Front_Door_02
	TAG_WINDOW_SMALL_03_RI
	TAG_WINDOW_SMALL_03_RI_D
  J_RI_Front_Door_03
	TAG_WINDOW_SMALL_04_RI
	TAG_WINDOW_SMALL_04_RI_D
  J_RI_Front_Door_04
	TAG_WINDOW_SMALL_05_RI
	TAG_WINDOW_SMALL_05_RI_D
=
*/
	destructible_create( destructibleType, "tag_origin", undefined, undefined, 32, "no_melee" );
	create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_02_RI", true,  "props/car_glass_subway_tall"  );
	create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_03_RI", true,  "props/car_glass_subway_tall"  );
	create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_04_RI", true,  "props/car_glass_subway_tall"  );
	create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_05_RI", true,  "props/car_glass_subway_tall"  );
	create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_02_LE", true,  "props/car_glass_subway_tall"  );
	create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_03_LE", true,  "props/car_glass_subway_tall"  );
	create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_04_LE", true,  "props/car_glass_subway_tall"  );
	create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_05_LE", true,  "props/car_glass_subway_tall"  );

}

create_vehicle_subway_cart_window_single( tag_center, has_destructible_mid_stage, fx )
{
	destructible_part( tag_center, undefined, 140, undefined, undefined, undefined, undefined, undefined, true );
	if( has_destructible_mid_stage ) 
		destructible_state( tag_center + "_D", undefined, 80, undefined, undefined, undefined, true );
	destructible_fx( tag_center, fx );
	destructible_sound( "veh_glass_break_large" );
	destructible_state( undefined );
}

vehicle_subway_cart_windows( destructibleType )
{
	//---------------------------------------------------------------------
	// Subway car windows only "vehicle_subway_window"
	//---------------------------------------------------------------------

	destructible_create( destructibleType, "tag_origin",  undefined, undefined, 32, "no_melee" );
		create_vehicle_subway_cart_window_single( "TAG_FRONT_WINDOW", true,  "props/car_glass_subway_tall"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_01_LE", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_03_LE", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_04_LE", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_07_LE", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_08_LE", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_011_LE", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_012_LE", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_014_LE", true,  "props/car_glass_subway_tall"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_01_RI", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_03_RI", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_04_RI", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_07_RI", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_08_RI", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_011_RI", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_012_RI", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_014_RI", true,  "props/car_glass_subway_tall"  );
}
vehicle_subway_cart_windows_small( destructibleType )
{
	//---------------------------------------------------------------------
	// Subway car windows only "vehicle_subway_window_small"
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", undefined, undefined, 32, "no_melee" );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_01_LE", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_06_LE", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_01_RI", true,  "props/car_glass_subway_large"  );
		create_vehicle_subway_cart_window_single( "TAG_WINDOW_SMALL_06_RI", true,  "props/car_glass_subway_large"  );
 }

vehicle_luxurysedan( color, streamed )
{
	//---------------------------------------------------------------------
	// Luxury Sedan
	//---------------------------------------------------------------------
	if( streamed )
		destructible_create( "vehicle_luxurysedan_2008" + color + "_streamed", "tag_body", 250, undefined, 32, "no_melee" );
	else
		destructible_create( "vehicle_luxurysedan_2008" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
				destructible_car_alarm();
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 210, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			if( color == "_gray" || color == "_white" )	
				destructible_state( undefined, "vehicle_luxurysedan_2008" + color + "_destroy", undefined, 32, "no_melee" );
			else
				destructible_state( undefined, "vehicle_luxurysedan_2008" + color + "_destroy_dusty", undefined, 32, "no_melee" );
		// Hood
		//*tag = "tag_hood";
		//*destructible_part( tag, "vehicle_luxurysedan_2008" + color + "_hood", 800, undefined, undefined, undefined, 1.0, 2.5 );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_luxurysedan_2008" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		//*destructible_part( "left_wheel_02_jnt", "vehicle_luxurysedan_2008" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		//*destructible_part( "right_wheel_01_jnt", "vehicle_luxurysedan_2008" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		//*destructible_part( "right_wheel_02_jnt", "vehicle_luxurysedan_2008" + color + "_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		// Doors
		//*destructible_part( "tag_door_left_front", "vehicle_luxurysedan_2008" + color + "_door_LF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		//*destructible_part( "tag_door_right_front", "vehicle_luxurysedan_2008" + color + "_door_RF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		//*destructible_part( "tag_door_left_back", "vehicle_luxurysedan_2008" + color + "_door_LB", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		//*destructible_part( "tag_door_right_back", "vehicle_luxurysedan_2008" + color + "_door_RB", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_luxurysedan_2008" + color + "_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_luxurysedan_2008" + color + "_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}


vehicle_mig29_landed( destructibleType )
{
	//---------------------------------------------------------------------
	// Mig 29 Landed Airplane
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "TAG_ORIGIN", 250, undefined, 32, "splash" );
		destructible_splash_damage_scaler( 11 );
				destructible_loopfx( "TAG_front_fire", "smoke/car_damage_whitesmoke", 0.4 );
				destructible_loopfx( "TAG_rear_fire", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "splash" );
				destructible_loopfx( "TAG_front_fire", "smoke/car_damage_blacksmoke", 0.4 );
				destructible_loopfx( "TAG_rear_fire", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "splash" );
				destructible_loopfx( "TAG_front_fire", "smoke/airplane_damage_blacksmoke_fire", 0.4 );
				destructible_loopfx( "TAG_rear_fire", "smoke/airplane_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 512, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "splash" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "splash" );
				destructible_fx( "TAG_FX", "explosions/vehicle_explosion_mig29", false );
				destructible_sound( "car_explode" );
				destructible_explode( 8000, 10000, 512, 512, 50, 300, undefined, undefined, 0.4, 1000 );
				destructible_anim( %vehicle_mig29_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_mig29_destroy" );
			destructible_state( undefined, "vehicle_mig29_v2_dest", undefined, 32, "splash" );

		destructible_part( "TAG_COCKPIT", "vehicle_mig29_dest_cockpit", 40, undefined, undefined, undefined, undefined, 1.0 );
}

vehicle_mack_truck_short( color )
{
	//---------------------------------------------------------------------
	// Mack Truck
	//---------------------------------------------------------------------
	destructible_create( "vehicle_mack_truck_short_" + color, "tag_body", 250, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/mack_truck_damage_blacksmoke_fire", 0.4 );
				destructible_loopfx( "tag_gastank", "smoke/motorcycle_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "mack_truck_flareup_med" );
				destructible_loopsound( "mack_truck_fire_med" );
				destructible_healthdrain( 15, 0.25, 300, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "mack_truck_fire_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_gastank", "smoke/motorcycle_damage_blacksmoke_fire", 0.4 );
				destructible_fx( "tag_cab_fire", "fire/firelp_med_pm" );
				destructible_fx( "tag_death_fx", "explosions/propane_large_exp", false );
				destructible_sound( "mack_truck_explode" );
				destructible_loopsound( "mack_truck_fire_med" );
				destructible_explode( 8000, 10000, 512, 512, 100, 400, undefined, undefined, 0.4, 1000 );
				//destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_mack_truck_short_" + color + "_destroy", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_mack_truck_short_" + color + "_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 8.0 );
		//*destructible_part( "left_wheel_02_jnt", "vehicle_mack_truck_short_" + color + "_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 81.0 );
		//*destructible_part( "left_wheel_03_jnt", "vehicle_mack_truck_short_" + color + "_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 8.0 );
		// Doors
		//*destructible_part( "tag_door_left_front", "vehicle_mack_truck_short_" + color + "_door_lf", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "mack_truck_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "mack_truck_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "mack_truck_glass_break_small" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "mack_truck_glass_break_small" );
			destructible_state( undefined );
}

vehicle_semi_truck()
{
	//---------------------------------------------------------------------
	// semui Truck
	//---------------------------------------------------------------------
	
	//"vehicle_semi_truck_destructible"
	//
	/*
	TAG_ORIGIN
	  TAG_BODY
	    TAG_CAB_FIRE
	    TAG_DEATH_FX
	    TAG_DOOR_LEFT_FRONT
	      TAG_GLASS_LEFT_BACK
	      TAG_GLASS_LEFT_BACK_D
	      TAG_GLASS_LEFT_BACK_FX
	      TAG_GLASS_LEFT_FRONT
	      TAG_GLASS_LEFT_FRONT_D
	      TAG_GLASS_LEFT_FRONT_FX
	    TAG_DOOR_RIGHT_FRONT
	      TAG_GLASS_RIGHT_BACK
	      TAG_GLASS_RIGHT_BACK_D
	      TAG_GLASS_RIGHT_BACK_FX
	      TAG_GLASS_RIGHT_FRONT
	      TAG_GLASS_RIGHT_FRONT_D
	      TAG_GLASS_RIGHT_FRONT_FX
	    TAG_GASTANK
	    TAG_GLASS_BACK
	    TAG_GLASS_BACK_D
	    TAG_GLASS_BACK_FX
	    TAG_GLASS_FRONT
	    TAG_GLASS_FRONT_D
	    TAG_GLASS_FRONT_FX
	    TAG_HOOD_FX
	  TAG_WHEEL_BACK_LEFT
	    left_wheel_02_jnt
	    left_wheel_03_jnt
	  TAG_WHEEL_BACK_RIGHT
	    right_wheel_02_jnt
	    right_wheel_03_jnt
	  TAG_WHEEL_FRONT_LEFT
	    left_wheel_01_jnt
	  TAG_WHEEL_FRONT_RIGHT
	    right_wheel_01_jnt



vehicle_semi_truck_destroyed
vehicle_semi_truck_destructible
vehicle_semi_truck_door_lf
vehicle_semi_truck_wheel_lf
	*/
	
	destructible_create( "vehicle_semi_truck", "tag_body", 250, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/mack_truck_damage_blacksmoke_fire", 0.4 );
				destructible_loopfx( "tag_gastank", "smoke/motorcycle_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "mack_truck_flareup_med" );
				destructible_loopsound( "mack_truck_fire_med" );
				destructible_healthdrain( 15, 0.25, 300, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "mack_truck_fire_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_gastank", "smoke/motorcycle_damage_blacksmoke_fire", 0.4 );
				destructible_fx( "tag_cab_fire", "fire/firelp_med_pm" );
				destructible_fx( "tag_death_fx", "explosions/propane_large_exp", false );
				destructible_sound( "mack_truck_explode" );
				destructible_loopsound( "mack_truck_fire_med" );
				destructible_explode( 8000, 10000, 512, 512, 100, 400, undefined, undefined, 0.4, 1000 );
				//destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_semi_truck_destroyed", undefined, 32, "no_melee" );
		// Tires
		destructible_part( "left_wheel_01_jnt", "vehicle_semi_truck_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 81.0 );
		destructible_part( "left_wheel_02_jnt", "vehicle_semi_truck_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 81.0 );
		destructible_part( "left_wheel_03_jnt", "vehicle_semi_truck_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 81.0 );
		// Doors
		destructible_part( "tag_door_left_front", "vehicle_semi_truck_door_lf", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( tag + "_fx", "props/car_glass_large" );
				destructible_sound( "mack_truck_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( tag + "_fx", "props/car_glass_large" );
				destructible_sound( "mack_truck_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( tag + "_fx", "props/car_glass_large" );
				destructible_sound( "mack_truck_glass_break_small" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "mack_truck_glass_break_small" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( tag + "_fx", "props/car_glass_large" );
				destructible_sound( "mack_truck_glass_break_small" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "mack_truck_glass_break_small" );
			destructible_state( undefined );
}

vehicle_motorcycle( number )
{
	explode_anim = undefined;
  explode_anim = get_precached_anim( "vehicle_motorcycle_destroy_" + number );

	//---------------------------------------------------------------------
	// Motorcycle
	//---------------------------------------------------------------------
	destructible_create( "vehicle_motorcycle_" + number, "body_animate_jnt", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_death_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_death_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_death_fx", "smoke/motorcycle_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 128, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 3000, 4000, 128, 150, 50, 300 );  // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
				destructible_anim( explode_anim, #animtree, "setanimknob", undefined, undefined, "vehicle_motorcycle_destroy_" + number );
			destructible_state( undefined, "vehicle_motorcycle_" + number + "_destroy", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "front_wheel", "vehicle_motorcycle_01_front_wheel_d", 20, undefined, undefined, "no_melee", undefined, 1.7 );
//		  destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
//		  destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "rear_wheel", "vehicle_motorcycle_01_rear_wheel_d", 20, undefined, undefined, "no_melee", undefined, 1.7 );
//		  destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
//		  destructible_sound( "veh_tire_deflate", "bullet" );
}

vehicle_scooter( destructibleType )
{
	//explode_anim = undefined;
  //explode_anim = get_precached_anim( "vehicle_motorcycle_destroy_" + 1 );

	//---------------------------------------------------------------------
	// Scooter
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 100, undefined, 32, "no_melee" );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_engine", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_engine", "smoke/scooter_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 128, "allies" );
			destructible_state( undefined, undefined, 150, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/vehicle_explosion_scooter", false );
				destructible_sound( "car_explode" );
				destructible_explode( 3000, 4000, 128, 150, 50, 300 );  // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage
				//destructible_anim( explode_anim, #animtree, "setanimknob", undefined, undefined, explode_anim );
			destructible_state( undefined, "vehicle_scooter_vespa_destroyed", undefined, 32, "no_melee" );
		// Tires
		//destructible_part( "front_wheel", "vehicle_motorcycle_01_front_wheel_d", 20, undefined, undefined, "no_melee", undefined, 1.7 );
//		  destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
//		  destructible_sound( "veh_tire_deflate", "bullet" );
		//destructible_part( "rear_wheel", "vehicle_motorcycle_01_rear_wheel_d", 20, undefined, undefined, "no_melee", undefined, 1.7 );
//		  destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
//		  destructible_sound( "veh_tire_deflate", "bullet" );
}

vehicle_subcompact( color )
{
	//---------------------------------------------------------------------
	// Modern Subcompact - shares textures with coupee and Van
	//---------------------------------------------------------------------
	destructible_create( "vehicle_subcompact_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 150, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, 0, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_subcompact_" + color + "_destroyed", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", "vehicle_subcompact_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", "vehicle_subcompact_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 2.3 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		//*destructible_part( "tag_door_left_back", "vehicle_subcompact_" + color + "_door_LB", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		//*destructible_part( "tag_door_right_back", "vehicle_subcompact_" + color + "_door_RB", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_subcompact_" + color + "_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_subcompact_" + color + "_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}

vehicle_van( color )
{
	//---------------------------------------------------------------------
	// Modern van - shares textures with Subcompact and Coupe
	//---------------------------------------------------------------------
	destructible_create( "vehicle_van_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_van_" + color + "_destroyed", undefined, 32, "no_melee" );
		// Hood
		//*tag = "tag_hood";
		//*destructible_part( tag, "vehicle_van_" + color + "_hood", undefined, undefined, undefined, undefined, 1.0, 2.5 );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_van_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 2.3 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", "vehicle_van_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 2.3 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt",  undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		//*destructible_part( "tag_door_right_back", "vehicle_van_" + color + "_door_RB", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back 2 )
		tag = "tag_glass_left_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back 2 )
		tag = "tag_glass_right_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_van_" + color + "_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_van_" + color + "_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}



vehicle_uaz_van( destructible_type )
{
	//---------------------------------------------------------------------
	// uaz_van 
	//---------------------------------------------------------------------
	/*
	"vehicle_uaz_van_destructible"
	TAG_ORIGIN
	  TAG_BODY
	    TAG_DEATH_FX
	    TAG_DOOR_LEFT_BACK
	      TAG_GLASS_LEFT_BACK
	      TAG_GLASS_LEFT_BACK_D
	      TAG_GLASS_LEFT_BACK_FX
	    TAG_DOOR_LEFT_FRONT
	      TAG_GLASS_LEFT_FRONT
	      TAG_GLASS_LEFT_FRONT_D
	      TAG_GLASS_LEFT_FRONT_FX
	      TAG_MIRROR_LEFT
	    TAG_DOOR_RIGHT_BACK
	      TAG_GLASS_RIGHT_BACK
	      TAG_GLASS_RIGHT_BACK_D
	      TAG_GLASS_RIGHT_BACK_FX
	    TAG_DOOR_RIGHT_FRONT
	      TAG_GLASS_RIGHT_FRONT
	      TAG_GLASS_RIGHT_FRONT_D
	      TAG_GLASS_RIGHT_FRONT_FX
	      TAG_MIRROR_RIGHT
	    TAG_GLASS_BACK
	    TAG_GLASS_BACK_D
	    TAG_GLASS_BACK_FX
	    TAG_GLASS_FRONT
	    TAG_GLASS_FRONT_D
	    TAG_GLASS_FRONT_FX
	    TAG_HOOD
	    TAG_HOOD_FX
	    TAG_LIGHT_LEFT_FRONT
	    TAG_LIGHT_LEFT_FRONT_D
	    TAG_LIGHT_RIGHT_FRONT
	    TAG_LIGHT_RIGHT_FRONT_D
	  TAG_WHEEL_BACK_LEFT
	    left_wheel_02_jnt
	  TAG_WHEEL_BACK_RIGHT
	    right_wheel_02_jnt
	  TAG_WHEEL_FRONT_LEFT
	    left_wheel_01_jnt
	  TAG_WHEEL_FRONT_RIGHT
	    right_wheel_01_jnt

	*/
	destructible_create( destructible_type , "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_uaz_van_destroyed", undefined, 32, "no_melee" );
		// Hood
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_van_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 2.3 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt",  "vehicle_van_wheel_lf" , 20, undefined, undefined, "no_melee", undefined, 1.6 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
}

vehicle_van_iw5( basemodel )
{
	//---------------------------------------------------------------------
	// Modern van - shares textures with Subcompact and Coupe
	//---------------------------------------------------------------------
	
	/*
	TAG_ORIGIN
  TAG_BODY
    TAG_DEATH_FX
    TAG_DOOR_LEFT_BACK
      TAG_GLASS_LEFT_BACK
      TAG_GLASS_LEFT_BACK_D
      TAG_GLASS_LEFT_BACK_FX
    TAG_DOOR_LEFT_FRONT
      TAG_GLASS_LEFT_FRONT
      TAG_GLASS_LEFT_FRONT_D
      TAG_GLASS_LEFT_FRONT_FX
      TAG_MIRROR_LEFT
    TAG_DOOR_RIGHT_BACK
      TAG_GLASS_RIGHT_BACK
      TAG_GLASS_RIGHT_BACK_D
      TAG_GLASS_RIGHT_BACK_FX
    TAG_DOOR_RIGHT_FRONT
      TAG_GLASS_RIGHT_FRONT
      TAG_GLASS_RIGHT_FRONT_D
      TAG_GLASS_RIGHT_FRONT_FX
      TAG_MIRROR_RIGHT
    TAG_GLASS_BACK
    TAG_GLASS_BACK_D
    TAG_GLASS_BACK_FX
    TAG_GLASS_FRONT
    TAG_GLASS_FRONT_D
    TAG_GLASS_FRONT_FX
    TAG_HOOD
    TAG_HOOD_FX
    TAG_LIGHT_LEFT_FRONT
    TAG_LIGHT_LEFT_FRONT_D
    TAG_LIGHT_RIGHT_FRONT
    TAG_LIGHT_RIGHT_FRONT_D
  TAG_WHEEL_BACK_LEFT
    left_wheel_02_jnt
  TAG_WHEEL_BACK_RIGHT
    right_wheel_02_jnt
  TAG_WHEEL_FRONT_LEFT
    left_wheel_01_jnt
  TAG_WHEEL_FRONT_RIGHT
    right_wheel_01_jnt

	*/
	
	destructible_create( basemodel + "_destructable", "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "TAG_DEATH_FX", "explosions/vehicle_explosion_medium", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, basemodel + "_destroyed", undefined, 32, "no_melee" );
			
		//*destructible_part( "left_wheel_01_jnt",  basemodel + "_wheel_lf", 20, undefined, undefined, "no_melee", 1.0, 1.0 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt",  basemodel + "_wheel_lf", 20, undefined, undefined, "no_melee", 1.0, 1.0 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt",  basemodel + "_wheel_lf", 20, undefined, undefined, "no_melee", 1.0, 1.0 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt",  basemodel + "_wheel_lf", 20, undefined, undefined, "no_melee", 1.0, 1.0 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );	
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Glass ( Left Front )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", basemodel + "_mirror_lf", 40, undefined, undefined, undefined, undefined, 1.0 );
		//*	destructible_physics();
		//*destructible_part( "tag_mirror_right", basemodel + "_mirror_rf", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}


vehicle_delivery_theme_park_truck_destructible( destructible_type )
{
	//---------------------------------------------------------------------
	// Modern van - shares textures with Subcompact and Coupe
	//---------------------------------------------------------------------
	
	/*
	
	"vehicle_delivery_theme_park_truck_destructible" 
	
	TAG_ORIGIN
	  origin_animate_jnt
	    origin_02_animate_jnt
	      TAG_BODY
	        body_animate_jnt
	          front_door_left_jnt
	          front_door_right_jnt
	          rear_door_left_jnt
	          rear_door_right_jnt
	          rear_hatch_jnt
	          TAG_DEATHFX
	          TAG_DRIVER
	          TAG_GLASS_FRONT1
	          TAG_GLASS_FRONT1_D
	          TAG_GLASS_FRONT1_FX
	          TAG_GLASS_FRONT2
	          TAG_GLASS_FRONT2_D
	          TAG_GLASS_FRONT2_FX
	          TAG_GLASS_LEFT_BACK
	          TAG_GLASS_LEFT_BACK_D
	          TAG_GLASS_LEFT_BACK_FX
	          TAG_GLASS_LEFT_FRONT
	          TAG_GLASS_LEFT_FRONT_D
	          TAG_GLASS_LEFT_FRONT_FX
	          TAG_GLASS_RIGH_BACK
	          TAG_GLASS_RIGH_BACK_D
	          TAG_GLASS_RIGH_BACK_FX
	          TAG_GLASS_RIGHT_FRONT
	          TAG_GLASS_RIGHT_FRONT_D
	          TAG_GLASS_RIGHT_FRONT_FX
	          TAG_GUY1
	          TAG_GUY2
	          TAG_GUY3
	          TAG_GUY4
	          TAG_HEADLIGHT_LEFT
	          TAG_HEADLIGHT_RIGHT
	          TAG_PASSENGER
	          TAG_TAIL_LIGHT_LEFT
	          TAG_TAIL_LIGHT_RIGHT
	      TAG_WHEEL_BACK_LEFT
	        wheel_back_left_animate_jnt
	          left_wheel_02_jnt
	      TAG_WHEEL_BACK_RIGHT
	        wheel_back_right_animate_jnt
	          right_wheel_02_jnt
	      TAG_WHEEL_FRONT_LEFT
	        wheel_front_left_animate_jnt
	          left_wheel_01_jnt
	      TAG_WHEEL_FRONT_RIGHT
	        wheel_front_right_animate_jnt
	          right_wheel_01_jnt


	*/
	
	destructible_create( destructible_type, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "TAG_HOOD_FX", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "TAG_HOOD_FX", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "TAG_HOOD_FX", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "TAG_DEATH_FX", "explosions/vehicle_explosion_medium", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_delivery_theme_park_truck_destroyed", undefined, 32, "no_melee" );
			
		destructible_part( "left_wheel_01_jnt",  "vehicle_van_sas_dark_wheel_lf", 20, undefined, undefined, "no_melee", 1.0, 2.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", undefined , 20, undefined, undefined, "no_melee", 1.0, 1.0 );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt",  undefined, 20, undefined, undefined, "no_melee", 1.0, 1.0 );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee", 1.0, 1.0 );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );	
			
		// Glass ( Front 1 )
		tag = "TAG_GLASS_FRONT1";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		tag = "TAG_GLASS_FRONT2";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "TAG_GLASS_LEFT_BACK";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "TAG_GLASS_LEFT_FRONT";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "TAG_GLASS_RIGHT_FRONT";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "TAG_GLASS_RIGHT_BACK";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
}



vehicle_suburban( destructibleType, color )
{
	//---------------------------------------------------------------------
	// Suburban
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
				destructible_car_alarm();
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 300, 300, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_suburban_destroyed" + color, undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt",  undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		//*destructible_part( "right_wheel_01_jnt", "vehicle_suburban_wheel_rf", 20, undefined, undefined, "no_melee", undefined, 2.3 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		//*destructible_part( "left_wheel_02_jnt", "vehicle_suburban_wheel_rf", 20, undefined, undefined, "no_melee", undefined, 2.3 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		//*destructible_part( "right_wheel_02_jnt",  undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		// Doors
		//*destructible_part( "tag_door_left_back", "vehicle_suburban_door_lb" + color, undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Center Divider )
		tag = "tag_center_glass";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag + "_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Left Back 2 )
		tag = "tag_glass_left_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Right Back 2 )
		tag = "tag_glass_right_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_car_alarm();
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_car_alarm();
			destructible_state( tag + "_d" );
}

vehicle_snowmobile( destructibleType )
{
	//---------------------------------------------------------------------
	// Snowmobile
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/snowmobile_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 150, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 150, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( get_precached_anim( "vehicle_snowmobile_destroy_01" ), #animtree, "setanimknob", undefined, undefined, "vehicle_snowmobile_destroy_01" );
			destructible_state( undefined, "vehicle_snowmobile_destroyed", undefined, 32, "no_melee" );
		// Front Ski
		tag = "right_wheel_01_jnt";
		destructible_part( tag, "vehicle_snowmobile_ski_right", 800, undefined, undefined, undefined, 1.0, 2.5 );
		// Bags
		destructible_part( "TAG_BAG_CENTER", "vehicle_snowmobile_bag_center", undefined, undefined, undefined, undefined, 1.0, 2.0 );
		destructible_part( "TAG_BAG_LEFT", "vehicle_snowmobile_bag_left", undefined, undefined, undefined, undefined, 1.0, 2.0 );
		destructible_part( "TAG_BAG_RIGHT", "vehicle_snowmobile_bag_right", undefined, undefined, undefined, undefined, 1.0, 2.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
}

#using_animtree( "destructibles" );
destructible_gaspump( destructibleType )
{
	//---------------------------------------------------------------------
	// Gas Pump 01
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 150, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 15 );
				destructible_loopfx( "tag_death_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 150, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_death_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 250, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_death_fx", "fire/gas_pump_fire_damage", .4 );
				destructible_sound( "gaspump01_flareup_med" );
				destructible_loopsound( "gaspump01_fire_med" );
				destructible_healthdrain( 12, 0.2, 210, "allies" );
			destructible_state( undefined, undefined, 300, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_death_fx", "fire/gas_pump_fire_damage", .4 );
				destructible_loopsound( "gaspump01_fire_med" );
				destructible_healthdrain( 12, 0.2, 210, "allies" );
				destructible_sound( "gaspump01_flareup_med" );
				destructible_loopfx( "tag_fx", "fire/gas_pump_fire_handle", 0.05 );
				destructible_anim( %gaspump01_hose, #animtree, "setanimknob", undefined, undefined, "gaspump01_hose" );
			destructible_state( undefined, undefined, 400, undefined, 5, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/gas_pump_exp", false );
				destructible_sound( "gaspump01_explode" );
				destructible_explode( 6000, 8000, 210, 300, 50, 300, undefined, undefined, 0.3, 500 );
			destructible_state( undefined, "furniture_gaspump01_destroyed", undefined, undefined, "no_melee" );

		// Large Front Bottom panel
		destructible_part( "tag_panel_front01", "furniture_gaspump01_panel01", 80, undefined, undefined, undefined, 1.0, 1.0, undefined, 1.0 );
			destructible_physics();
		// Medium Front Middle panel
		destructible_part( "tag_panel_front02", "furniture_gaspump01_panel02", 40, undefined, undefined, undefined, 1.0, 1.0 );
			destructible_physics();
		// Small Front Top Panel
		destructible_part( "tag_panel_front03", "furniture_gaspump01_panel03", 40, undefined, undefined, undefined, 1.0, 1.0 );
			destructible_sound( "exp_gaspump_sparks" );
			destructible_fx( "tag_panel_front03", "props/electricbox4_explode" );
			destructible_physics();

		// Large Back Bottom panel
		destructible_part( "tag_panel_back01", "furniture_gaspump01_panel01", 110, undefined, undefined, undefined, 1.0, 1.0, undefined, 1.0 );
			destructible_physics();
		// Medium Back Middle panel
		destructible_part( "tag_panel_back02", "furniture_gaspump01_panel02", 40, undefined, undefined, undefined, 1.0, 1.0 );
			destructible_physics();
		// Small Back Top Panel
		destructible_part( "tag_panel_back03", "furniture_gaspump01_panel03", 40, undefined, undefined, undefined, 1.0, 1.0 );
			destructible_sound( "exp_gaspump_sparks" );
			destructible_fx( "tag_panel_back03", "props/electricbox4_explode" );
			destructible_physics();

}

destructible_electrical_transformer_large( destructibleType )
{
	//---------------------------------------------------------------------
	// Electrical transformer 01
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 1500, undefined, 32, "no_melee" );
		destructible_splash_damage_scaler( 2 );
				destructible_loopsound( "electrical_transformer_sparks" );
				destructible_loopfx( "tag_fx", "explosions/electrical_transformer_spark_runner", 0.8 );
				destructible_healthdrain( 12, 0.2, 210, "allies" );
			destructible_state( undefined, undefined, 500, undefined, 32, "no_melee" );
				destructible_loopsound( "electrical_transformer_sparks" );
				destructible_fx( "tag_fx_junction", "explosions/generator_sparks_c", false );
				destructible_loopfx( "tag_fx_junction", "fire/electrical_transformer_blacksmoke_fire", 0.4 );
				destructible_loopfx( "tag_fx", "explosions/electrical_transformer_spark_runner", 0.8 );
				destructible_healthdrain( 12, 0.2, 210, "allies" );
			destructible_state( undefined, undefined, 300, undefined, 32, "no_melee" );
				destructible_loopsound( "electrical_transformer_sparks" );
				destructible_loopfx( "tag_fx_junction", "fire/electrical_transformer_blacksmoke_fire", 0.4 );
				destructible_loopfx( "tag_fx", "explosions/electrical_transformer_spark_runner", 0.8 );
				destructible_loopfx( "tag_fx_valve", "explosions/generator_spark_runner", 0.6 );
				destructible_healthdrain( 12, 0.2, 210, "allies" );
			destructible_state( undefined, undefined, 500, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/electrical_transformer_explosion", false );
				destructible_sound( "electrical_transformer01_explode" );
				destructible_explode( 6000, 8000, 210, 300, 20, 300, undefined, undefined, 0.3, 500 );
			destructible_state( undefined, "com_electrical_transformer_large_des", undefined, undefined, "no_melee" );

		// door 1
		destructible_part( "tag_door1", "com_electrical_transformer_large_dam_door1", 1500, undefined, undefined, undefined, 0, 1.0, undefined, 1  );
			destructible_sound( "electrical_transformer01_explode_detail" );
			destructible_fx( "tag_door1", "explosions/generator_explosion" );
			destructible_physics();
			
		// door 2
		destructible_part( "tag_door2", "com_electrical_transformer_large_dam_door2", 150, undefined, undefined, undefined, 0, 1.0, undefined, 1 );
			destructible_physics();

		// door 3
		destructible_part( "tag_door3", "com_electrical_transformer_large_dam_door3", 150, undefined, undefined, undefined, 0, 1.0, undefined, 1 );
			destructible_physics();

		// door 4
		destructible_part( "tag_door4", "com_electrical_transformer_large_dam_door4", 150, undefined, undefined, undefined, 0, 1.0, undefined, 1 );
			destructible_physics();

		// door 5
		destructible_part( "tag_door5", "com_electrical_transformer_large_dam_door5", 1500, undefined, undefined, undefined, 0, 1.0, undefined, 1 );
			destructible_sound( "electrical_transformer01_explode_detail" );
			destructible_fx( "tag_door5", "props/electricbox4_explode" );
			destructible_physics();

		// door 6
		destructible_part( "tag_door6", "com_electrical_transformer_large_dam_door6", 150, undefined, undefined, undefined, 0, 1.0, undefined, 1 );
			destructible_physics();

		// door 7
		destructible_part( "tag_door7", "com_electrical_transformer_large_dam_door7", 150, undefined, undefined, undefined, 0, 1.0, undefined, 1 );
			destructible_loopsound( "electrical_transformer_sparks" );
			destructible_fx( "tag_door7", "props/electricbox4_explode" );
			destructible_physics();

}

get_precached_anim( animname )
{
	println( animname );
	assertEX( isdefined( level._destructible_preanims ) && isdefined( level._destructible_preanims[ animname ] ),"Can't find destructible anim: "+animname+" check the Build Precache Scripts and Repackage Zone boxes In launcher when you compile your map. " );
	return level._destructible_preanims[ animname ];
}

get_precached_animtree( animname )
{
	println( animname );
	AssertEX( Isdefined( level._destructible_preanimtree ) && Isdefined( level._destructible_preanimtree[ animname ] ),"Can't find destructible anim tree: "+animname+" check the Build Precache Scripts and Repackage Zone boxes In launcher when you compile your map. " );
	return level._destructible_preanimtree[ animname ];
}

#using_animtree ( "vehicles" );


vehicle_coupe( color )
{
	//---------------------------------------------------------------------
	// Modern coupe - shares textures with Subcompact and Van
	//---------------------------------------------------------------------
	destructible_create( "vehicle_coupe_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 150, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_coupe_" + color + "_destroyed", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", "vehicle_coupe_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 2.3 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		//*destructible_part( "tag_door_left_front", "vehicle_coupe_" + color + "_door_LF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Spoiler (rear)
		//*destructible_part( "tag_spoiler", "vehicle_coupe_" + color + "_spoiler", undefined, undefined, undefined, undefined, 1.0, 2.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_coupe_" + color + "_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_coupe_" + color + "_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();

}


vehicle_mini( color )
{
	//---------------------------------------------------------------------
	// Modern mini - 
	//---------------------------------------------------------------------
	//"vehicle_mini_destructible_white"
	/*
	TAG_ORIGIN
  origin_animate_jnt
    TAG_BODY
      body_animate_jnt
        TAG_DEATH_FX
        TAG_DOOR_LEFT_BACK
          TAG_GLASS_LEFT_BACK
          TAG_GLASS_LEFT_BACK_02
          TAG_GLASS_LEFT_BACK_02_D
          TAG_GLASS_LEFT_BACK_02_FX
          TAG_GLASS_LEFT_BACK_D
          TAG_GLASS_LEFT_BACK_FX
        TAG_DOOR_LEFT_FRONT
          TAG_GLASS_LEFT_FRONT
          TAG_GLASS_LEFT_FRONT_D
          TAG_GLASS_LEFT_FRONT_FX
          TAG_MIRROR_LEFT
        TAG_DOOR_RIGHT_BACK
          TAG_GLASS_RIGHT_BACK
          TAG_GLASS_RIGHT_BACK_02
          TAG_GLASS_RIGHT_BACK_02_D
          TAG_GLASS_RIGHT_BACK_02_FX
          TAG_GLASS_RIGHT_BACK_D
          TAG_GLASS_RIGHT_BACK_FX
        TAG_DOOR_RIGHT_FRONT
          TAG_GLASS_RIGHT_FRONT
          TAG_GLASS_RIGHT_FRONT_D
          TAG_GLASS_RIGHT_FRONT_FX
          TAG_MIRROR_RIGHT
        TAG_DRIVER
        TAG_GLASS_BACK
        TAG_GLASS_BACK_D
        TAG_GLASS_BACK_FX
        TAG_GLASS_FRONT
        TAG_GLASS_FRONT_D
        TAG_GLASS_FRONT_FX
        TAG_HOOD
        TAG_HOOD_FX
        TAG_LIGHT_LEFT_FRONT
        TAG_LIGHT_LEFT_FRONT_D
        TAG_LIGHT_RIGHT_FRONT
        TAG_LIGHT_RIGHT_FRONT_D
        TAG_PASSENGER
        TAG_PLAYER
    TAG_WHEEL_BACK_LEFT
      left_wheel_02_jnt
    TAG_WHEEL_BACK_RIGHT
      right_wheel_02_jnt
    TAG_WHEEL_FRONT_LEFT
      left_wheel_front_animate_jnt
        left_wheel_01_jnt
    TAG_WHEEL_FRONT_RIGHT
      right_wheel_front_animate_jnt
        right_wheel_01_jnt

	*/
	destructible_create( "vehicle_mini_destructible_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 12, 0.2, 150, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_mini_destroyed_" + color, undefined, 32, "no_melee" );
		// Tires
		destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim", true );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim", true );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim", true );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee", undefined, 2.3 );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim", true );
			destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "TAG_GLASS_FRONT";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
			destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
			destructible_fx( tag, "props/car_glass_headlight" );
			destructible_sound( "veh_glass_break_small" );
		// Side Mirrors
		destructible_part( "tag_mirror_left", "vehicle_mini_mirror_lf", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
		destructible_part( "tag_mirror_right", "vehicle_mini_mirror_rf", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
}

vehicle_uk_truck( destructibleType )
{
	//"vehicle_uk_utility_truck_destructible"
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		tag = "TAG_GLASS_FRONT";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "TAG_GLASS_BACK";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "TAG_GLASS_LEFT_FRONT";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "TAG_GLASS_RIGHT_FRONT";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Tires
		destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );

}

vehicle_uk_police_estate( destructibleType )
{
	//"vehicle_uk_police_estate_destructible" -- "uk_police_estate_destructible"
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "uk_police_estate_destroyed", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "uk_police_estate_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 1.0 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", "uk_police_estate_wheel_lf", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", "uk_police_estate_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 10.0 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", "uk_police_estate_wheel_lf", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "TAG_GLASS_FRONT";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "TAG_GLASS_BACK";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "TAG_GLASS_LEFT_FRONT";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "TAG_GLASS_RIGHT_FRONT";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "TAG_GLASS_LEFT_BACK";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "TAG_GLASS_RIGHT_BACK";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back 2 )
		tag = "TAG_GLASS_LEFT_BACK_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back 2 )
		tag = "TAG_GLASS_RIGHT_BACK_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_D", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
}

vehicle_uaz_winter( destructibleType )
{
	//---------------------------------------------------------------------
	// UAZ - Winter Version
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_uaz_winter_destroy", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_uaz_wheel_LF_d", 20, undefined, undefined, "no_melee", undefined, 1.0 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", "vehicle_uaz_wheel_LF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", "vehicle_uaz_wheel_RF_d", 20, undefined, undefined, "no_melee", undefined, 10.0 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", "vehicle_uaz_wheel_RF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back 2 )
		tag = "tag_glass_left_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back 2 )
		tag = "tag_glass_right_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_uaz_winter_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_uaz_winter_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}

vehicle_uaz_fabric( destructibleType )
{
	//---------------------------------------------------------------------
	// UAZ - Winter Version
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_uaz_fabric_dsr", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_uaz_wheel_LF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", "vehicle_uaz_wheel_LF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", "vehicle_uaz_wheel_RF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", "vehicle_uaz_wheel_RF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_uaz_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_uaz_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}

vehicle_uaz_hardtop( destructibleType )
{
	//---------------------------------------------------------------------
	// UAZ - Winter Version
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_uaz_hardtop_dsr", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_uaz_wheel_LF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", "vehicle_uaz_wheel_LF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", "vehicle_uaz_wheel_RF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", "vehicle_uaz_wheel_RF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back 2 )
		tag = "tag_glass_left_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back 2 )
		tag = "tag_glass_right_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_uaz_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_uaz_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}


vehicle_jeep( destructibleType )
{
	//---------------------------------------------------------------------
	// vehicle jeep
	//---------------------------------------------------------------------
	
	/*
	"vehicle_jeep_destructible" 
	TAG_ORIGIN
	  TAG_BODY
	    TAG_DEATH_FX
	    TAG_DOOR_LEFT_BACK
	      TAG_GLASS_LEFT_BACK
	      TAG_GLASS_LEFT_BACK_D
	      TAG_GLASS_LEFT_BACK_FX
	    TAG_DOOR_LEFT_FRONT
	      TAG_GLASS_LEFT_FRONT
	      TAG_GLASS_LEFT_FRONT_D
	      TAG_GLASS_LEFT_FRONT_FX
	      TAG_MIRROR_LEFT
	    TAG_DOOR_RIGHT_BACK
	      TAG_GLASS_RIGHT_BACK
	      TAG_GLASS_RIGHT_BACK_D
	      TAG_GLASS_RIGHT_BACK_FX
	    TAG_DOOR_RIGHT_FRONT
	      TAG_GLASS_RIGHT_FRONT
	      TAG_GLASS_RIGHT_FRONT_D
	      TAG_GLASS_RIGHT_FRONT_FX
	      TAG_MIRROR_RIGHT
	    TAG_GLASS_BACK
	    TAG_GLASS_BACK_D
	    TAG_GLASS_BACK_FX
	    TAG_GLASS_FRONT
	    TAG_GLASS_FRONT_D
	    TAG_GLASS_FRONT_FX
	    TAG_HOOD
	    TAG_HOOD_FX
	    TAG_LIGHT_LEFT_FRONT
	    TAG_LIGHT_LEFT_FRONT_D
	    TAG_LIGHT_RIGHT_FRONT
	    TAG_LIGHT_RIGHT_FRONT_D
	  TAG_WHEEL_BACK_LEFT
	    left_wheel_02_jnt
	  TAG_WHEEL_BACK_RIGHT
	    right_wheel_02_jnt
	  TAG_WHEEL_FRONT_LEFT
	    left_wheel_01_jnt
	  TAG_WHEEL_FRONT_RIGHT
	    right_wheel_01_jnt

	*/
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_jeep_destroyed", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", undefined , 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", "vehicle_jeep_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 2.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", "vehicle_jeep_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 2.7  );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );	
		//*destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
}

vehicle_jeep_dusty( destructibleType )
{
	//---------------------------------------------------------------------
	// vehicle jeep dusty
	//---------------------------------------------------------------------
	
	
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_jeep_destroyed", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", undefined , 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", "vehicle_jeep_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 2.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", "vehicle_jeep_wheel_lf", 20, undefined, undefined, "no_melee", undefined, 2.7  );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );	
		//*destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
}


vehicle_uaz_open( destructibleType )
{
	//---------------------------------------------------------------------
	// UAZ - Open Version
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_uaz_open_dsr", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_uaz_wheel_LF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", "vehicle_uaz_wheel_LF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", "vehicle_uaz_wheel_LF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", "vehicle_uaz_wheel_LF_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back 2 )
		tag = "tag_glass_left_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back 2 )
		tag = "tag_glass_right_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_uaz_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_uaz_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}

vehicle_india_compact_destructible( color )
{
	//---------------------------------------------------------------------
	// India Compact
	//---------------------------------------------------------------------
	//"vehicle_india_compact_blue"
	
	/*
	
	tag_origin
		  tag_body
		    body_animate_jnt
		      front_door_left_jnt
		        tag_door_left_front
		          tag_glass_left_front
		          tag_glass_left_front_d
		          tag_glass_left_front_fx
		          tag_mirror_left
		      front_door_right_jnt
		        tag_door_right_front
		          tag_glass_right_front
		          tag_glass_right_front_d
		          tag_glass_right_front_fx
		          tag_mirror_right
		      rear_door_left_jnt
		        tag_door_left_back
		          tag_glass_left_back
		          tag_glass_left_back_d
		          tag_glass_left_back_fx
		      rear_door_right_jnt
		        tag_door_right_back
		          tag_glass_right_back
		          tag_glass_right_back_d
		          tag_glass_right_back_fx
		      steering_wheel_jnt
		      tag_bumper_back
		      tag_bumper_front
		      tag_deathfx
		      tag_detach
		      tag_driver
		      tag_engine_left
		      tag_engine_right
		      tag_glass_back
		      tag_glass_back_d
		      tag_glass_back_fx
		      tag_glass_front
		      tag_glass_front_d
		      tag_glass_front_fx
		      tag_glass_left_back_02
		      tag_glass_left_back_02_d
		      tag_glass_left_back_02_fx
		      tag_glass_right_back_02
		      tag_glass_right_back_02_d
		      tag_glass_right_back_02_fx
		      tag_guy0
		      tag_guy1
		      tag_guy2
		      tag_guy3
		      tag_headlight_left
		      tag_headlight_right
		      tag_hood
		      tag_hood_fx
		      tag_light_left_back
		      tag_light_left_back_d
		      tag_light_left_front
		      tag_light_left_front_d
		      tag_light_right_back
		      tag_light_right_back_d
		      tag_light_right_front
		      tag_light_right_front_d
		      tag_passenger
		  tag_wheel_back_left
		    left_wheel_02_jnt
		  tag_wheel_back_right
		    right_wheel_02_jnt
		  tag_wheel_front_left
		    left_wheel_01_jnt
		  tag_wheel_front_right
		    right_wheel_01_jnt

	*/
	destructible_create( "vehicle_india_compact_destructible_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/india_compact_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_india_compact_destroyed_" + color, undefined, 32, "no_melee" );
		// Tires
		destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim", true );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", "vehicle_india_compact_wheel_lf_d", 20, undefined, undefined, "no_melee", undefined, 1.2 );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim", true );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim", true );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim", true );
			destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back 2 )
		tag = "tag_glass_left_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back 2 )
		tag = "tag_glass_right_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		destructible_part( "tag_mirror_left", "vehicle_india_compact_mirror_l", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
		destructible_part( "tag_mirror_right", "vehicle_india_compact_mirror_r", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
}

vehicle_india_rickshaw( destructibleType )
{
	//---------------------------------------------------------------------
	// India Rickshaw
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/rickshaw_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_deathfx", "explosions/india_rickshaw_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "india_vehicle_rksw_d", undefined, 32, "no_melee" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 30, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Headlight
		destructible_part( "tag_headlight_left", "intro_vehicle_rksw_light_d", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
}


vehicle_tuk_tuk( destructibleType )
{
	//---------------------------------------------------------------------
	// tuk_tuk - ?
	//---------------------------------------------------------------------
	/*
	"vehicle_tuk_tuk_destructible"
	TAG_ORIGIN
	  TAG_BODY
	    TAG_DEATH_FX
	    TAG_DOOR_LEFT_BACK
	      TAG_GLASS_LEFT_BACK
	      TAG_GLASS_LEFT_BACK_D
	      TAG_GLASS_LEFT_BACK_FX
	    TAG_DOOR_LEFT_FRONT
	      TAG_GLASS_LEFT_FRONT
	      TAG_GLASS_LEFT_FRONT_D
	      TAG_GLASS_LEFT_FRONT_FX
	      TAG_MIRROR_LEFT
	    TAG_DOOR_RIGHT_BACK
	      TAG_GLASS_RIGHT_BACK
	      TAG_GLASS_RIGHT_BACK_D
	      TAG_GLASS_RIGHT_BACK_FX
	    TAG_DOOR_RIGHT_FRONT
	      TAG_GLASS_RIGHT_FRONT
	      TAG_GLASS_RIGHT_FRONT_D
	      TAG_GLASS_RIGHT_FRONT_FX
	      TAG_MIRROR_RIGHT
	    TAG_GLASS_BACK
	    TAG_GLASS_BACK_D
	    TAG_GLASS_BACK_FX
	    TAG_GLASS_FRONT
	    TAG_GLASS_FRONT_D
	    TAG_GLASS_FRONT_FX
	    TAG_HOOD
	    TAG_HOOD_FX
	    TAG_LIGHT_LEFT_FRONT
	    TAG_LIGHT_LEFT_FRONT_D
	    TAG_LIGHT_RIGHT_FRONT
	    TAG_LIGHT_RIGHT_FRONT_D
	  TAG_WHEEL_BACK_LEFT
	    left_wheel_02_jnt
	  TAG_WHEEL_BACK_RIGHT
	    right_wheel_02_jnt
	  TAG_WHEEL_FRONT_LEFT
	    left_wheel_01_jnt
	  TAG_WHEEL_FRONT_RIGHT
	    right_wheel_01_jnt

	*/
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/rickshaw_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/india_rickshaw_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_tuk_tuk_destroyed", undefined, 32, "no_melee" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 30, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 30, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( tag + "_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( tag + "_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		
		destructible_part( "tag_door_left_front", "vehicle_tuk_tuk_door_left", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_door_left_front", "vehicle_tuk_tuk_door_right", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_mirror_left", "vehicle_tuk_tuk_mirror", 10, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();

}

vehicle_india_suv( color )
{
	//---------------------------------------------------------------------
	// India SUV
	//---------------------------------------------------------------------
	destructible_create( "vehicle_india_suv_" + color, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_india_suv_" + color + "_dsr", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_india_suv_wheel_lf_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "left_wheel_02_jnt", "vehicle_india_suv_wheel_lf_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_01_jnt", "vehicle_india_suv_wheel_rf_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		//*destructible_part( "right_wheel_02_jnt", "vehicle_india_suv_wheel_rf_d", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim", true );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back 2 )
		tag = "tag_glass_left_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back 2 )
		tag = "tag_glass_right_back_02";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_02_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Left )
		tag = "tag_light_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_brakelight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Tail Light ( Right )
		tag = "tag_light_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_brakelight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_uaz_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_uaz_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}

vehicle_policecar( destructibleType )
{
	//---------------------------------------------------------------------
	// Police Car
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode_police" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_policecar_lapd_destroy", undefined, 32, "no_melee" );
		// Tires
		destructible_part( "left_wheel_01_jnt", "vehicle_policecar_lapd_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", "vehicle_policecar_lapd_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", "vehicle_policecar_lapd_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", "vehicle_policecar_lapd_wheel_LF", 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		destructible_part( "tag_door_left_front", "vehicle_policecar_lapd_door_LF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_door_right_front", "vehicle_policecar_lapd_door_RF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_door_left_back", "vehicle_policecar_lapd_door_LB", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Center Divider )
		tag = "tag_center_glass";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "TAG_CENTER_GLASS_FX", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		destructible_part( "tag_mirror_left", "vehicle_policecar_lapd_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
		destructible_part( "tag_mirror_right", "vehicle_policecar_lapd_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
}

vehicle_policecar_russia( destructibleType )
{
	//---------------------------------------------------------------------
	// Police Car
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode_police" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_policecar_russia_destroy", undefined, 32, "no_melee" );
		// Tires
		destructible_part( "left_wheel_01_jnt", "vehicle_policecar_russia_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "left_wheel_02_jnt", "vehicle_policecar_russia_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_01_jnt", "vehicle_policecar_russia_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		destructible_part( "right_wheel_02_jnt", "vehicle_policecar_russia_wheel_LF", 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
		// Doors
		destructible_part( "tag_door_left_front", "vehicle_policecar_russia_door_LF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_door_right_front", "vehicle_policecar_russia_door_RF", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		destructible_part( "tag_door_left_back", "vehicle_policecar_russia_door_LB", undefined, undefined, undefined, undefined, 1.0, 1.0 );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Center Divider )
		tag = "tag_center_glass";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "TAG_CENTER_GLASS_FX", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		destructible_part( "tag_mirror_left", "vehicle_policecar_russia_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
		destructible_part( "tag_mirror_right", "vehicle_policecar_russia_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
}

vehicle_taxi( destructibleType )
{
	//---------------------------------------------------------------------
	// Taxi with random roof ads
	//---------------------------------------------------------------------
	
	//"vehicle_taxi_yellow_destructible_dusty"
	/*
	TAG_ORIGIN
	  TAG_BODY
	    TAG_AD
	    TAG_CENTER_GLASS
	    TAG_CENTER_GLASS_D
	    TAG_CENTER_GLASS_FX
	    TAG_DEATH_FX
	    TAG_DOOR_LEFT_BACK
	      TAG_GLASS_LEFT_BACK
	      TAG_GLASS_LEFT_BACK_D
	      TAG_GLASS_LEFT_BACK_FX
	    TAG_DOOR_LEFT_FRONT
	      TAG_GLASS_LEFT_FRONT
	      TAG_GLASS_LEFT_FRONT_D
	      TAG_GLASS_LEFT_FRONT_FX
	      TAG_MIRROR_LEFT
	    TAG_DOOR_RIGHT_BACK
	      TAG_GLASS_RIGHT_BACK
	      TAG_GLASS_RIGHT_BACK_D
	      TAG_GLASS_RIGHT_BACK_FX
	    TAG_DOOR_RIGHT_FRONT
	      TAG_GLASS_RIGHT_FRONT
	      TAG_GLASS_RIGHT_FRONT_D
	      TAG_GLASS_RIGHT_FRONT_FX
	      TAG_MIRROR_RIGHT
	    TAG_GLASS_BACK
	    TAG_GLASS_BACK_D
	    TAG_GLASS_BACK_FX
	    TAG_GLASS_FRONT
	    TAG_GLASS_FRONT_D
	    TAG_GLASS_FRONT_FX
	    TAG_HOOD
	    TAG_HOOD_FX
	    TAG_LIGHT_LEFT_FRONT
	    TAG_LIGHT_LEFT_FRONT_D
	    TAG_LIGHT_RIGHT_FRONT
	    TAG_LIGHT_RIGHT_FRONT_D
	  TAG_WHEEL_BACK_LEFT
	    left_wheel_02_jnt
	  TAG_WHEEL_BACK_RIGHT
	    right_wheel_02_jnt
	  TAG_WHEEL_FRONT_LEFT
	    left_wheel_01_jnt
	  TAG_WHEEL_FRONT_RIGHT
	    right_wheel_01_jnt

	*/
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
					//*random_dynamic_attachment( "tag_ad", "vehicle_taxi_rooftop_ad_base", "vehicle_taxi_rooftop_ad_1" );
					//*random_dynamic_attachment( "tag_ad", "vehicle_taxi_rooftop_ad_base", "vehicle_taxi_rooftop_ad_2" );
					//*random_dynamic_attachment( "tag_ad", "vehicle_taxi_rooftop_ad_base", "vehicle_taxi_rooftop_ad_3" );
					//*random_dynamic_attachment( "tag_ad", "vehicle_taxi_rooftop_ad_base", "vehicle_taxi_rooftop_ad_4" );
					//*random_dynamic_attachment( "tag_ad", "vehicle_taxi_toplight", undefined, "taxi_ad_clip" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
				destructible_car_alarm();
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_taxi_yellow_destroy_dusty", undefined, 32, "no_melee" );
		// Tires
		//*destructible_part( "left_wheel_01_jnt", "vehicle_taxi_wheel_LF", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		//*destructible_part( "left_wheel_02_jnt", "vehicle_taxi_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		//*destructible_part( "right_wheel_01_jnt", "vehicle_taxi_wheel_LF", 20, undefined, undefined, "no_melee", undefined, 1.7 );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		//*destructible_part( "right_wheel_02_jnt", "vehicle_taxi_wheel_LF", 20, undefined, undefined, "no_melee" );
			//*destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			//*destructible_sound( "veh_tire_deflate", "bullet" );
			//*destructible_car_alarm();
		// Glass ( Front )
		tag = "TAG_CENTER_GLASS";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		//*destructible_part( "tag_mirror_left", "vehicle_taxi_mirror_L", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
		//*destructible_part( "tag_mirror_right", "vehicle_taxi_mirror_R", 40, undefined, undefined, undefined, undefined, 1.0 );
			//*destructible_physics();
}

vehicle_taxi_dubai( destructibleType )
{
	//---------------------------------------------------------------------
	// Taxi for dubai
	//---------------------------------------------------------------------
	
	destructible_create( destructibleType, "tag_body", 250, undefined, 32, "no_melee" );
		//destructible_splash_damage_scaler( 18 );
					//random_dynamic_attachment( "tag_ad", "vehicle_taxi_rooftop_ad_base", "vehicle_taxi_rooftop_ad_1" );
					//random_dynamic_attachment( "tag_ad", "vehicle_taxi_rooftop_ad_base", "vehicle_taxi_rooftop_ad_2" );
					//random_dynamic_attachment( "tag_ad", "vehicle_taxi_rooftop_ad_base", "vehicle_taxi_rooftop_ad_3" );
					//random_dynamic_attachment( "tag_ad", "vehicle_taxi_rooftop_ad_base", "vehicle_taxi_rooftop_ad_4" );
					random_dynamic_attachment( "tag_ad", "vehicle_taxi_toplight_dubai", undefined, "taxi_ad_clip" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_whitesmoke", 0.4 );
				destructible_car_alarm();
			destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_state( undefined, undefined, 100, undefined, 32, "no_melee" );
				destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke_fire", 0.4 );
				destructible_sound( "fire_vehicle_flareup_med" );
				destructible_loopsound( "fire_vehicle_med" );
				destructible_healthdrain( 15, 0.25, 210, "allies" );
			destructible_state( undefined, undefined, 300, "player_only", 32, "no_melee" );
				destructible_loopsound( "fire_vehicle_med" );
			destructible_state( undefined, undefined, 400, undefined, 32, "no_melee" );
				destructible_fx( "tag_death_fx", "explosions/small_vehicle_explosion", false );
				destructible_sound( "car_explode" );
				destructible_explode( 4000, 5000, 200, 250, 50, 300, undefined, undefined, 0.3, 500 );
				destructible_anim( %vehicle_80s_sedan1_destroy, #animtree, "setanimknob", undefined, undefined, "vehicle_80s_sedan1_destroy" );
			destructible_state( undefined, "vehicle_taxi_yellow_destroy_dubai", undefined, 32, "no_melee" );
		// Tires
		destructible_part( "left_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_LF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
			destructible_car_alarm();
		destructible_part( "left_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_LB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
			destructible_car_alarm();
		destructible_part( "right_wheel_01_jnt", undefined, 20, undefined, undefined, "no_melee", undefined, 1.7 );
			destructible_anim( %vehicle_80s_sedan1_flattire_RF, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
			destructible_car_alarm();
		destructible_part( "right_wheel_02_jnt", undefined, 20, undefined, undefined, "no_melee" );
			destructible_anim( %vehicle_80s_sedan1_flattire_RB, #animtree, "setanim" );
			destructible_sound( "veh_tire_deflate", "bullet" );
			destructible_car_alarm();
		// Glass ( Front )
		tag = "TAG_CENTER_GLASS";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Front )
		tag = "tag_glass_front";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_front_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Back )
		tag = "tag_glass_back";
		destructible_part( tag, undefined, 40, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_back_fx", "props/car_glass_large" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Left Front )
		tag = "tag_glass_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Right Front )
		tag = "tag_glass_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_front_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Left Back )
		tag = "tag_glass_left_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_left_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Glass ( Right Back )
		tag = "tag_glass_right_back";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, undefined, undefined, true );
			destructible_state( tag + "_d", undefined, 60, undefined, undefined, undefined, true );
				destructible_fx( "tag_glass_right_back_fx", "props/car_glass_med" );
				destructible_sound( "veh_glass_break_large" );
				destructible_car_alarm();
			destructible_state( undefined );
		// Head Light ( Left )
		tag = "tag_light_left_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Head Light ( Right )
		tag = "tag_light_right_front";
		destructible_part( tag, undefined, 20, undefined, undefined, undefined, 0.5 );
				destructible_fx( tag, "props/car_glass_headlight" );
				destructible_sound( "veh_glass_break_small" );
			destructible_state( tag + "_d" );
		// Side Mirrors
		destructible_part( "tag_mirror_left", "vehicle_taxi_mirror_l", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
		destructible_part( "tag_mirror_right", "vehicle_taxi_mirror_r", 40, undefined, undefined, undefined, undefined, 1.0 );
			destructible_physics();
}

//Destructibles from DLC
#using_animtree( "destructibles");

toy_security_camera( destructibleType )
{
	//---------------------------------------------------------------------
	// Rotating security camera
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_camera_tilt", 0, undefined, 32 );
			destructible_anim( get_precached_anim( "security_camera_idle" ), #animtree, "setanimknob", undefined, undefined, "security_camera_idle" );
		destructible_state( "tag_camera_tilt", "com_security_camera_tilt_animated", 75 );
			destructible_anim( get_precached_anim( "security_camera_destroy" ), #animtree, "setanimknob", undefined, undefined, "security_camera_destroy" );
			destructible_fx( "tag_fx", "props/security_camera_explosion_moving" );
			destructible_sound( "security_camera_sparks" );
		destructible_state( undefined, "com_security_camera_d_tilt_animated", undefined, undefined, "no_melee" );
}


//#using_animtree( "destructibles");
toy_building_collapse_paris_ac130( destructibleType )
{
	//---------------------------------------------------------------------
	// Collapsing building in AC130 Paris
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 100, undefined, 32 );
	   //	 destructible_anim( get_precached_anim( "security_camera_idle" ), #animtree, "setanimknob", undefined, undefined, "security_camera_idle" );
	  //  destructible_state( "tag_camera_tilt", "com_security_camera_tilt_animated", 75 );
			destructible_anim( get_precached_anim( "ac130_building_collapse" ), #animtree, "setanimknob", undefined, undefined, "ac130_building_collapse" );
			destructible_fx( "tag_fx", "misc/building_collapse_paris_ac130" );
			destructible_fx( "tag_fx_base", "misc/building_collapse_paris_ac130_ground" );
			destructible_fx( "tag_fx_crack", "misc/building_collapse_paris_ac130_cracks" );
	  //	  destructible_sound( "security_camera_sparks" );
		destructible_state( undefined, "building_collapse_paris_ac130_dest", undefined, undefined, "no_melee" );
 //			 destructible_anim( get_precached_anim( "ac130_building_collapse" ), #animtree, "setanimknob", undefined, undefined, "ac130_building_collapse" );

}

//#using_animtree( "destructibles");
toy_poison_gas_attack( destructibleType )
{
	//---------------------------------------------------------------------
	// test setup for animated gas stream
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 100, undefined, 32 );
	   //	 destructible_anim( get_precached_anim( "security_camera_idle" ), #animtree, "setanimknob", undefined, undefined, "security_camera_idle" );
	  //  destructible_state( "tag_camera_tilt", "com_security_camera_tilt_animated", 75 );
			destructible_anim( get_precached_anim( "london_gas_attack" ), #animtree, "setanimknob", undefined, undefined, "london_gas_attack" );
			destructible_fx( "tag_origin", "smoke/poison_gas_attack" );
	  //	  destructible_sound( "security_camera_sparks" );
		destructible_state( undefined, "fx_gas_attack", undefined, undefined, "no_melee" );
 //			 destructible_anim( get_precached_anim( "ac130_building_collapse" ), #animtree, "setanimknob", undefined, undefined, "ac130_building_collapse" );

}

toy_arcade_machine( version )
{
	//---------------------------------------------------------------------
	// Exploding Arcade Maching
	//---------------------------------------------------------------------
	destructible_create( "toy_arcade_machine" + version, "tag_origin", 0, undefined, 32 );
		destructible_state( "tag_origin", "arcade_machine" + version, 75 );
			destructible_fx( "tag_fx", "props/arcade_machine_exp" );
			destructible_fx( "tag_fx2", "props/arcade_machine_coins" );
			destructible_sound( "arcade_machine_destroy" );
		destructible_state( undefined, "arcade_machine" + version + "_des", undefined, undefined, "no_melee" );
}


toy_pinball_machine( version )
{
	//---------------------------------------------------------------------
	// Exploding Arcade Maching
	//---------------------------------------------------------------------
	destructible_create( "toy_pinball_machine" + version, "tag_origin", 0, undefined, 32 );
		destructible_state( "tag_origin", "pinball_machine" + version, 75 );
			destructible_fx( "tag_fx", "props/pinball_machine_exp", undefined, undefined, undefined, 1 );
			destructible_fx( "tag_fx2", "props/arcade_machine_coins" );
			destructible_fx( "tag_fx3", "props/pinball_machine_glass" );
			destructible_sound( "pinball_machine_destroy" );
		destructible_state( undefined, "pinball_machine" + version + "_des", undefined, undefined, "no_melee" );
}


toy_fortune_machine( destructibleType )
{
	//---------------------------------------------------------------------
	// Exploding Fortune Telling Maching
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 0, undefined, 32 );
			destructible_loopsound( "fortune_machine_idle" );
			destructible_loopfx( "J_Eye_RI", "props/fortune_machine_glow_eyes", 2.9 );
			destructible_loopfx( "J_Eye_LE", "props/fortune_machine_glow_eyes", 2.9 );
			destructible_loopfx( "tag_fx3", "props/fortune_machine_glow_ball", 4.0 );
			destructible_anim( get_precached_anim( "fortune_machine_anim" ), #animtree, "setanimknob", undefined, undefined, "fortune_machine_anim" );
		destructible_state( "tag_origin", "fortune_machine", 75 );
			destructible_fx( "tag_fx", "props/fortune_machine_exp", undefined, undefined, undefined, 1 );
			destructible_fx( "tag_fx2", "props/fortune_machine_tickets" );
			destructible_sound( "pinball_machine_destroy" );
			destructible_anim( get_precached_anim( "fortune_machine_des" ), #animtree, "setanimknob", undefined, undefined, "fortune_machine_des" );
			destructible_explode( 20, 2000, 20, 20, 40, 40, undefined, 64 );	// force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage, continueDamage, originOffset
		destructible_state( undefined, "fortune_machine_des", undefined, undefined, "no_melee" );
}

toy_trashcan_clown( destructibleType )
{
	//---------------------------------------------------------------------
	// Clown Trashcan toy
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 120, undefined, 32 );
				destructible_fx( "tag_fx", "props/garbage_spew_des", true, "splash" );
				destructible_fx( "tag_fx", "props/garbage_spew", true, damage_not( "splash" ) );
				destructible_sound( "exp_trashcan_sweet" );															 
				destructible_explode( 600, 651, 1, 1, 10, 20 );	 // force_min, force_max, rangeSP, rangeMP, mindamage, maxdamage

		destructible_state( "tag_origin", "trashcan_clown_base", undefined, undefined, undefined, undefined, undefined, false );


		destructible_part( "tag_fx", "trashcan_clown_lid", undefined, undefined, undefined, undefined, 1.0, 1.0 );

}


toy_afrShanty1( destructibleType )
{
	//---------------------------------------------------------------------
	// African shanty destructible
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 25, undefined, 32 );
		destructible_fx( "tag_origin", "dust/dust_shanty_explode" );
		destructible_anim( get_precached_anim( "afr_shanty01_explode" ), #animtree, "setanimknob", undefined, undefined, "afr_shanty01_explode" );
		destructible_state( undefined, "afr_shanty01", undefined, undefined, "no_melee" );
	
}

vehicle_slava_ny_harbor_zonea( destructibleType )
{
	
	//---------------------------------------------------------------------
	// Taxi with random roof ads
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 1, undefined, 32);//, undefined );
				//destructible_loopfx( "tag_origin", "smoke/car_damage_whitesmoke", 0.4 );
				//destructible_car_alarm();
			//destructible_state( undefined, undefined, 200, undefined, 32, "no_melee" );
			//  destructible_loopfx( "tag_hood_fx", "smoke/car_damage_blacksmoke", 0.4 );
			destructible_anim(  get_precached_anim( "ny_harbor_slava_r2a_des" ), #animtree, "setanim" );
			destructible_fx( "tag_explosionA", "maps/ny_harbor/ny_battleship_explosion" );
			destructible_fx( "tag_explosionB", "maps/ny_harbor/ny_battleship_explosion" );
			//destructible_state( undefined, "ny_harbor_slava_dest_zonea", undefined, 32, "no_melee" );
		// Tires
		//destructible_part( "tag_fx17", "ny_harbor_slava_cruiser_dest_zonea", 20, undefined, undefined, "no_melee" );
		//  ;

}

rooftop_skylight_destructible( destructibleType )
{
	//---------------------------------------------------------------------
	// skylight destructible
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 5, undefined, undefined );
		//destructible_fx( "tag_fx", "props/skylight_damaged_windowglass" );
		//destructible_fx( "tag_fx1", "props/skylight_damaged_windowglass" );
		//destructible_fx( "tag_fx4", "props/skylight_damaged_windowglass" );
		//destructible_fx( "tag_fx7", "props/skylight_damaged_windowglass" );
		//destructible_state( "tag_origin", "ny_rooftop_skylight_damaged", 100, undefined, undefined , "no_melee" );
		destructible_fx( "tag_fx1", "props/skylight_destroyed_windowglass" );
		destructible_fx( "tag_fx4", "props/skylight_destroyed_windowglass" );
		destructible_fx( "tag_fx7", "props/skylight_destroyed_windowglass" );
		destructible_fx( "tag_fx4", "props/skylight_destroyed_pit" );
		destructible_state( "tag_origin", "ny_rooftop_skylight_destroyed", undefined, undefined, "no_melee" );
	
}

satellite_dish_big_destructible( destructibleType )
{
	//---------------------------------------------------------------------
	// satellite dish big
	//---------------------------------------------------------------------
	destructible_create( destructibleType, "tag_origin", 150, undefined, 32 );
		destructible_fx( "tag_origin", "props/satellite_dish_big_des" );
		destructible_state( "tag_origin", "com_satellite_dish_big_destroyed", undefined, undefined, "no_melee" );
	
}
 

dest_onestate(destructibleType,dest,fx,sound)
{
	destructible_create(destructibleType,"tag_origin",150,undefined,32);
		destructible_fx( "tag_fx", fx);
		destructible_state( "tag_origin", dest, undefined, undefined, "no_meele" );
		if (isdefined( sound))
			destructible_sound( sound );
}


dest_pb_planter(destructibleType,dest,fx,sound)
{
	destructible_create(destructibleType,"tag_origin",1150,undefined,32);
		destructible_state( "tag_origin", dest, undefined, undefined, "no_meele" );
			destructible_fx( "tag_fx", fx);
			destructible_fx( "tag_fx", fx);
			//destructible_explode( 4000, 5000, 150, 250, 50, 300, undefined, undefined, 0.3, 500 );
}

berlin_hotel_lights_ceiling1(destructibleType,dest)
{
	destructible_create(destructibleType,"tag_origin",150,undefined,32);
		destructible_fx( "tag_fx", "misc/light_blowout_ceiling");
		destructible_fx( "tag_fx_wire", "misc/light_blowout_wire_spark");
		destructible_state( "tag_origin", dest, undefined, undefined, "no_meele" );
}

rus_vx_gas_canister( destructibleType )
{
	destructible_create( destructibleType, "tag_origin", 250, undefined, 32, "no_melee" );
		destructible_state( "tag_origin", "rus_vx_gas_canister_destroyed", 250, undefined, 32, "no_melee" );
			destructible_fx( undefined, "explosions/rus_vx_gas_canister", false );				
			destructible_explode( 4000, 5000, 150, 250, 50, 150, undefined, undefined, 0.3, 500 );
}
