// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"

namespace iw6
{

std::unordered_map<std::string, std::uint16_t> file_map =
{

};

auto get_file_id(const std::string& name) -> std::uint16_t
{
	const auto itr = file_map.find(name);

	if (itr != file_map.end())
	{
		return itr->second;
	}

	LOG_WARN("Couldn't resolve file id for name '%s'!", name.c_str());
	return 0;
}

auto get_file_name(std::uint16_t id) -> std::string
{
	for (auto& file : file_map)
	{
		if (file.second == id)
		{
			return file.first;
		}
	}

	LOG_WARN("Couldn't resolve file name for id '%i'!", id);
	return utils::string::va("id#%i", id);
}

} // namespace iw6

/*
		{ 1443, "unknown" }, // mp_dome.ff mp_bootleg.ff mp_carbon.ff  mp_hardhat.ff mp_interchange.ff mp_seatown.ff  mp_underground.ff mp_boardwalk.ff
		{ 1444, "unknown" }, // mp_dome.ff anim ?
		{ 1445, "unknown" }, // mp_dome.ff anim ?
		{ 1446, "unknown" }, // mp_dome.ff anim ?
		{ 1447, "unknown" }, // mp_dome.ff anim ?
		{ 1448, "unknown" }, // mp_dome.ff anim ?
		{ 1449, "unknown" }, // mp_dome.ff anim ?
		{ 1450, "unknown" }, // mp_dome.ff anim ?
		{ 1451, "unknown" }, // mp_dome.ff anim ?
		{ 1452, "unknown" }, // mp_dome.ff anim ?
		{ 1453, "unknown" }, // mp_dome.ff anim ?
		{ 1454, "unknown" }, // mp_dome.ff anim ?
		{ 1455, "unknown" }, // mp_dome.ff anim ?
		{ 1456, "unknown" }, // mp_dome.ff anim ?
		{ 1457, "unknown" }, // mp_dome.ff anim ?
		{ 1458, "unknown" }, // mp_dome.ff anim ?
		{ 1459, "maps\createart\mp_afghan_art" }, // mp_dome.ff fx, art
		{ 1460, "unknown" }, // mp_dome.ff fx, art mp_carbon.ff mp_hardhat.ff mp_interchange.ff mp_lambeth.ff  mp_radar.ff
		{ 1461, "unknown" }, // mp_dome.ff fx, art
		{ 1462, "unknown" }, // mp_dome.ff fx, art
		{ 1642, "unknown" }, // mp_carbon.ff
		{ 18649, "unknown" }, // mp_carbon.ff mp_hardhat.ff mp_radar.ff
		{ 18650, "unknown" }, // mp_carbon.ff mp_radar.ff  mp_underground.ff
		{ 18651, "unknown" }, // mp_radar.ff
		{ 18652, "unknown" }, // mp_radar.ff
		{ 18653, "unknown" }, // mp_radar.ff
		{ 18654, "unknown" }, // mp_radar.ff
		{ 18655, "unknown" }, // mp_radar.ff
		{ 18656, "unknown" }, // mp_radar.ff
		{ 18657, "unknown" }, // mp_radar.ff
		{ 18658, "unknown" }, // mp_radar.ff

		{ 18661, "unknown" }, // mp_bootleg.ff mp_seatown.ff mp_village.ff
		{ 18662, "unknown" }, // mp_bravo.ff mp_mogadishu.ff mp_seatown.ff mp_village.ff
		{ 18663, "unknown" }, // mp_village.ff
		{ 18664, "unknown" }, // mp_village.ff
		{ 18665, "unknown" }, // mp_village.ff
		{ 18666, "unknown" }, // mp_underground.ff
		{ 18667, "unknown" }, // mp_underground.ff

		{ 18670, "unknown" }, // mp_underground.ff
		{ 18671, "unknown" }, // mp_underground.ff
		{ 18672, "unknown" }, // mp_underground.ff
		{ 18673, "unknown" }, // mp_seatown.ff mp_boardwalk.ff
		{ 18674, "unknown" }, // mp_bravo.ff mp_seatown.ff
		{ 18675, "unknown" }, // mp_bravo.ff mp_seatown.ff
		{ 18676, "unknown" }, // mp_bravo.ff  mp_seatown.ff
		{ 18677, "unknown" }, // mp_seatown.ff
		{ 18678, "unknown" }, // mp_seatown.ff
		{ 18679, "unknown" }, // mp_seatown.ff
		{ 18680, "unknown" }, // mp_seatown.ff
		{ 18681, "unknown" }, // mp_seatown.ff
		{ 18682, "unknown" }, // mp_seatown.ff
		{ 18683, "unknown" }, // mp_seatown.ff
		{ 18684, "unknown" }, // mp_seatown.ff
		{ 18685, "unknown" }, // mp_seatown.ff


		{ 18686, "unknown" }, // mp_seatown.ff
		{ 18687, "unknown" }, // mp_seatown.ff
		{ 18688, "unknown" }, // mp_seatown.ff
		{ 18689, "unknown" }, // mp_bootleg.ff mp_bravo.ff mp_plaza2.ff mp_boardwalk.ff
		{ 18690, "unknown" }, // mp_plaza2.ff
		{ 18691, "unknown" }, // mp_plaza2.ff
		{ 18692, "unknown" }, // mp_plaza2.ff
		{ 18693, "unknown" }, // mp_plaza2.ff
		{ 18694, "unknown" }, // mp_paris.ff
		{ 18695, "unknown" }, // mp_paris.ff
		{ 18696, "unknown" }, // mp_paris.ff
		{ 18697, "unknown" }, // mp_paris.ff
		{ 18698, "unknown" }, // mp_mogadishu.ff
		{ 18699, "unknown" }, // mp_mogadishu.ff
		{ 18700, "unknown" }, // mp_mogadishu.ff
		{ 18701, "unknown" }, // mp_lambeth.ff
		{ 18702, "unknown" }, // mp_lambeth.ff
		{ 18703, "unknown" }, // mp_lambeth.ff
		{ 18704, "unknown" }, // mp_lambeth.ff
		{ 18705, "unknown" }, // mp_lambeth.ff
		{ 18706, "unknown" }, // mp_lambeth.ff
		{ 18707, "unknown" }, // mp_interchange.ff
		{ 18708, "unknown" }, // mp_interchange.ff
		{ 18709, "unknown" }, // mp_interchange.ff
		{ 18710, "unknown" }, // mp_hardhat.ff
		{ 18711, "unknown" }, // mp_hardhat.ff
		{ 18712, "unknown" }, // mp_hardhat.ff
		{ 18713, "unknown" }, // mp_hardhat.ff
		{ 18714, "unknown" }, // mp_hardhat.ff
		{ 18715, "unknown" }, // mp_hardhat.ff
		{ 18716, "unknown" }, // mp_hardhat.ff
		{ 18717, "unknown" }, // mp_hardhat.ff
		{ 18718, "unknown" }, // mp_hardhat.ff
		{ 18719, "unknown" }, // mp_hardhat.ff
		{ 18720, "unknown" }, // mp_hardhat.ff
		{ 18721, "unknown" }, // mp_hardhat.ff
		{ 18722, "unknown" }, // mp_hardhat.ff
		{ 18723, "unknown" }, // mp_hardhat.ff
		{ 18724, "unknown" }, // mp_hardhat.ff
		{ 18725, "unknown" }, // mp_hardhat.ff
		{ 18726, "unknown" }, // mp_hardhat.ff
		{ 18727, "unknown" }, // mp_hardhat.ff
		{ 18728, "unknown" }, // mp_hardhat.ff
		{ 18729, "unknown" }, // mp_hardhat.ff
		{ 18730, "unknown" }, // mp_hardhat.ff
		{ 18731, "unknown" }, // mp_hardhat.ff
		{ 18732, "unknown" }, // mp_hardhat.ff
		{ 18733, "unknown" }, // mp_exchange.ff
		{ 18734, "unknown" }, // mp_exchange.ff
		{ 18735, "unknown" }, // mp_exchange.ff
		{ 18736, "unknown" }, // mp_carbon.ff
		{ 18737, "unknown" }, // mp_carbon.ff
		{ 18738, "unknown" }, // mp_carbon.ff
		{ 18739, "unknown" }, // mp_carbon.ff
		{ 18740, "unknown" }, // mp_carbon.ff
		{ 18741, "unknown" }, // mp_carbon.ff
		{ 18742, "unknown" }, // mp_carbon.ff
		{ 18743, "unknown" }, // mp_carbon.ff
		{ 18744, "unknown" }, // mp_carbon.ff
		{ 18745, "unknown" }, // mp_carbon.ff
		{ 18746, "unknown" }, // mp_carbon.ff
		{ 18747, "unknown" }, // mp_carbon.ff
		{ 18748, "unknown" }, // mp_carbon.ff
		{ 18749, "unknown" }, // mp_carbon.ff
		{ 18750, "unknown" }, // mp_carbon.ff
		{ 18751, "unknown" }, // mp_carbon.ff
		{ 18752, "unknown" }, // mp_carbon.ff
		{ 18753, "unknown" }, // mp_carbon.ff
		{ 18754, "unknown" }, // mp_carbon.ff

		{ 18758, "unknown" }, // mp_carbon.ff
		{ 18759, "unknown" }, // mp_carbon.ff
		{ 18760, "unknown" }, // mp_bravo.ff
		{ 18761, "unknown" }, // mp_bravo.ff
		{ 18762, "unknown" }, // mp_bravo.ff
		{ 18763, "unknown" }, // mp_bravo.ff
		{ 18764, "unknown" }, // mp_bravo.ff
		{ 18765, "unknown" }, // mp_bravo.ff
		{ 18766, "unknown" }, // mp_bootleg.ff
		{ 18767, "unknown" }, // mp_bootleg.ff
		{ 18768, "unknown" }, // mp_bootleg.ff
		{ 18769, "unknown" }, // mp_bootleg.ff
		{ 18770, "unknown" }, // mp_alpha.ff
		{ 18771, "unknown" }, // mp_alpha.ff
		{ 18772, "unknown" }, // mp_alpha.ff
		{ 18773, "unknown" }, // mp_alpha.ff

		{ 33361, "maps/mp/mp_italy_precache" }, // mp_italy.ff
		{ 33362, "maps/createart/mp_italy_art" }, // mp_italy.ff
		{ 33363, "maps/mp/mp_italy_fx" }, // mp_italy.ff
		{ 33364, "maps/createfx/mp_italy_fx" }, // mp_italy.ff
		{ 33365, "maps/createart/mp_italy_fog" }, // mp_italy.ff

		{ 33366, "maps/mp/mp_park_precache" }, // mp_park.ff
		{ 33367, "maps/createart/mp_park_art" }, // mp_park.ff
		{ 33368, "maps/mp/mp_park_fx" }, // mp_park.ff
		{ 33369, "maps/createfx/mp_park_fx" }, // mp_park.ff
		{ 33370, "maps/createart/mp_park_fog" }, // mp_park.ff

		{ 33371, "maps/mp/mp_overwatch_precache" }, // mp_overwatch.ff
		{ 33372, "maps/createart/mp_overwatch_art" }, // mp_overwatch.ff
		{ 33373, "maps/mp/mp_overwatch_fx" }, // mp_overwatch.ff
		{ 33374, "maps/createfx/mp_overwatch_fx" }, // mp_overwatch.ff
		{ 33375, "maps/createart/mp_overwatch_fog" }, // mp_overwatch.ff

		{ 33376, "maps/mp/mp_morningwood_precache" }, // mp_morningwood.ff
		{ 33377, "maps/createart/mp_morningwood_art" }, // mp_morningwood.ff
		{ 33378, "maps/mp/mp_morningwood_fx" }, // mp_morningwood.ff
		{ 33379, "maps/createfx/mp_morningwood_fx" }, // mp_morningwood.ff
		{ 33380, "maps/createart/mp_morningwood_fog" }, // mp_morningwood.ff
		*/
/*
	scriptfile,maps/mp/gametypes/faceoff
	scriptfile,maps/mp/mp_aground_ss
	scriptfile,maps/mp/mp_aground_ss_precache
	scriptfile,maps/mp/mp_aground_ss_fx
	scriptfile,maps/createfx/mp_aground_ss_fx
	scriptfile,maps/createart/mp_aground_ss_art
	scriptfile,maps/createart/mp_aground_ss_fog
	scriptfile,maps/mp/mp_boardwalk
	scriptfile,maps/mp/mp_boardwalk_precache
	scriptfile,maps/mp/mp_boardwalk_fx
	scriptfile,maps/createfx/mp_boardwalk_fx
	scriptfile,maps/createart/mp_boardwalk_art
	scriptfile,maps/createart/mp_boardwalk_fog
	scriptfile,maps/mp/mp_boardwalk_scriptlights
	scriptfile,maps/animated_models/bw_dd_carscript_01_full_anim
	scriptfile,maps/createart/mp_burn_ss_fog
	scriptfile,maps/mp/mp_burn_ss
	scriptfile,maps/mp/mp_burn_ss_precache
	scriptfile,maps/mp/mp_burn_ss_fx
	scriptfile,maps/createfx/mp_burn_ss_fx
	scriptfile,maps/createart/mp_burn_ss_art
	scriptfile,maps/animated_models/vehicle_industrial_truck_anims
	scriptfile,maps/animated_models/foliage_tree_river_birch_med_a
	scriptfile,maps/animated_models/mp_cement_tarp3
	scriptfile,maps/animated_models/mp_cement_tarp4_a
	scriptfile,maps/animated_models/mp_cement_tarp4_b
	scriptfile,maps/animated_models/mp_cement_tarp4_d
	scriptfile,maps/animated_models/mp_cement_tarp4_e
	scriptfile,maps/animated_models/mp_cement_tarp4_f
	scriptfile,maps/animated_models/mp_cement_tarp4_g
	scriptfile,maps/animated_models/vehicle_industrial_truck_spin
	scriptfile,maps/mp/mp_cement
	scriptfile,maps/mp/mp_cement_precache
	scriptfile,maps/mp/mp_cement_fx
	scriptfile,maps/createfx/mp_cement_fx
	scriptfile,maps/createart/mp_cement_fog
	scriptfile,maps/createart/mp_cement_art
	scriptfile,common_scripts/_interactive
	scriptfile,maps/mp/mp_courtyard_ss
	scriptfile,maps/mp/mp_courtyard_ss_precache
	scriptfile,maps/mp/mp_courtyard_ss_fx
	scriptfile,maps/createfx/mp_courtyard_ss_fx
	scriptfile,maps/createart/mp_courtyard_ss_art
	scriptfile,maps/createart/mp_courtyard_ss_fog
	scriptfile,maps/mp/mp_crosswalk_ss
	scriptfile,maps/mp/mp_crosswalk_ss_precache
	scriptfile,maps/mp/mp_crosswalk_ss_fx
	scriptfile,maps/createfx/mp_crosswalk_ss_fx
	scriptfile,maps/createart/mp_crosswalk_ss_art
	scriptfile,maps/createart/mp_crosswalk_ss_fog
	scriptfile,maps/mp/mp_hillside_ss
	scriptfile,maps/mp/mp_hillside_ss_precache
	scriptfile,maps/mp/mp_hillside_ss_fx
	scriptfile,maps/createfx/mp_hillside_ss_fx
	scriptfile,maps/createart/mp_hillside_ss_art
	scriptfile,maps/createart/mp_hillside_ss_fog
	scriptfile,maps/animated_models/com_boat_fishing_buoy2_scale5
	scriptfile,maps/animated_models/hillside_awnings_animated
	scriptfile,maps/animated_models/hillside_drapes_animated
	scriptfile,maps/animated_models/yacht_modern_periph
	scriptfile,maps/mp/mp_meteora
	scriptfile,maps/mp/mp_meteora_precache
	scriptfile,maps/mp/mp_meteora_fx
	scriptfile,maps/createfx/mp_meteora_fx
	scriptfile,maps/createart/mp_meteora_art
	scriptfile,maps/createart/mp_meteora_fog
	scriptfile,maps/animated_models/lantern_iron_off_animated
	scriptfile,maps/animated_models/foliage_afr_tree_umbrel_01a_sway
	scriptfile,maps/animated_models/foliage_tree_birch_yellow_light_sway
	scriptfile,maps/mp/mp_moab
	scriptfile,maps/mp/mp_moab_precache
	scriptfile,maps/mp/mp_moab_fx
	scriptfile,maps/createfx/mp_moab_fx
	scriptfile,maps/createart/mp_moab_art
	scriptfile,maps/createart/mp_moab_fog
	scriptfile,maps/animated_models/moab_curtains_lace
	scriptfile,maps/animated_models/moab_tailing_wheel_full_anim
	scriptfile,maps/mp/mp_nola
	scriptfile,maps/mp/mp_nola_precache
	scriptfile,maps/mp/mp_nola_fx
	scriptfile,maps/createfx/mp_nola_fx
	scriptfile,maps/mp/mp_nola_scriptlights
	scriptfile,maps/createart/mp_nola_art
	scriptfile,maps/createart/mp_nola_fog
	scriptfile,maps/animated_models/ow_chute_corner_hang_idle
	scriptfile,maps/animated_models/ow_chute_side_hang_idle
	scriptfile,maps/animated_models/ow_crane_hook
	scriptfile,maps/animated_models/foliage_prk_tree_beech_fall_anim
	scriptfile,maps/animated_models/foliage_prk_tree_birch_animated
	scriptfile,maps/mp/mp_qadeem
	scriptfile,maps/mp/mp_qadeem_precache
	scriptfile,maps/mp/mp_qadeem_fx
	scriptfile,maps/createfx/mp_qadeem_fx
	scriptfile,maps/createart/mp_qadeem_art
	scriptfile,maps/createart/mp_qadeem_fog
	scriptfile,maps/animated_models/foliage_pacific_palms06_animated
	scriptfile,maps/animated_models/foliage_pacific_palms08_animated
	scriptfile,maps/animated_models/foliage_tree_palm_bushy_3
	scriptfile,maps/animated_models/qad_foliage_tree_palm_bushy_3
	scriptfile,maps/animated_models/qad_lamp_windy_animated
	scriptfile,maps/animated_models/qad_palmtree_bushy_animated
	scriptfile,maps/animated_models/qad_palmtree_tall_animated
	scriptfile,maps/mp/mp_restrepo_ss
	scriptfile,maps/mp/mp_restrepo_ss_precache
	scriptfile,maps/mp/mp_restrepo_ss_fx
	scriptfile,maps/createfx/mp_restrepo_ss_fx
	scriptfile,maps/createart/mp_restrepo_ss_art
	scriptfile,maps/createart/mp_restrepo_ss_fog
	scriptfile,maps/mp/mp_roughneck
	scriptfile,maps/mp/mp_roughneck_precache
	scriptfile,maps/mp/mp_roughneck_fx
	scriptfile,maps/createfx/mp_roughneck_fx
	scriptfile,maps/createart/mp_roughneck_art
	scriptfile,maps/createart/mp_roughneck_fog
	scriptfile,maps/mp/mp_shipbreaker
	scriptfile,maps/mp/mp_shipbreaker_precache
	scriptfile,maps/mp/mp_shipbreaker_fx
	scriptfile,maps/createfx/mp_shipbreaker_fx
	scriptfile,maps/mp/mp_shipbreaker_scriptlights
	scriptfile,maps/createart/mp_shipbreaker_art
	scriptfile,maps/createart/mp_shipbreaker_fog
	scriptfile,maps/animated_models/sb_metal_chunk_animated
	scriptfile,common_scripts/_destructible_types_anim_chicken_dlc
	scriptfile,maps/mp/gametypes/faceoff
	scriptfile,maps/mp/mp_six_ss
	scriptfile,maps/mp/mp_six_ss_precache
	scriptfile,maps/mp/mp_six_ss_fx
	scriptfile,maps/createfx/mp_six_ss_fx
	scriptfile,maps/createart/mp_six_ss_art
	scriptfile,maps/createart/mp_six_ss_fog
	scriptfile,maps/animated_models/barn_door_l
	scriptfile,maps/animated_models/barn_door_r
	scriptfile,maps/animated_models/corn_field_01_anim
	scriptfile,maps/animated_models/farmhouse_distant
	scriptfile,maps/animated_models/fence_flimsy_animated
	scriptfile,maps/animated_models/fence_sturdy_animated
	scriptfile,maps/animated_models/lamp_iron_hanging_nochain_animated
	scriptfile,maps/animated_models/me_corrugated_metal_anim
	scriptfile,maps/animated_models/paris_shutter_anim_violent_01
	scriptfile,maps/animated_models/paris_shutter_anim_violent_02
	scriptfile,maps/animated_models/paris_shutter_anim_violent_03
	scriptfile,maps/animated_models/prop_chain_hanging_combined
	scriptfile,maps/animated_models/prop_chain_hanging_loop
	scriptfile,maps/animated_models/prop_chain_hanging_long
	scriptfile,maps/animated_models/prop_chain_hanging_short
	scriptfile,maps/animated_models/river_birch_lg_a_animated
	scriptfile,maps/animated_models/stable_doors_anim
	scriptfile,maps/animated_models/ug_oak_tree_windy_anim
	scriptfile,maps/animated_models/wire_hanging_192long
	scriptfile,maps/animated_models/wire_hanging_512long
	scriptfile,maps/mp/mp_terminal_cls
	scriptfile,maps/mp/mp_terminal_cls_precache
	scriptfile,maps/mp/mp_terminal_cls_fx
	scriptfile,maps/createfx/mp_terminal_cls_fx
	scriptfile,maps/createart/mp_terminal_cls_art
	scriptfile,maps/createart/mp_terminal_cls_fog
	scriptfile,animscripts/traverse/traverse_window_terminal
	scriptfile,maps/animated_models/accessories_windsock_wind_medium
	scriptfile,maps/animated_models/foliage_pacific_fern01
	*/