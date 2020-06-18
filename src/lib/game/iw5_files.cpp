// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "gsc_tool.hpp"

namespace iw5
{

std::unordered_map<std::string, std::uint16_t> file_map =
{
	// missing files: aitype, animscripts, character, animated_models, mptype
	// _dev, _globalentities, _hostmigration (empty files?)
	{ "maps\\mp\\mp_aground_ss", 0 },
	{ "maps\\mp\\mp_alpha", 0 },
	{ "maps\\mp\\mp_boardwalk", 0 },
	{ "maps\\mp\\mp_bootleg", 0 },
	{ "maps\\mp\\mp_bravo", 0 },
	{ "maps\\mp\\mp_burn_ss", 0 },
	{ "maps\\mp\\mp_carbon", 0 },
	{ "maps\\mp\\mp_cement", 0 },
	{ "maps\\mp\\mp_courtyard_ss", 0 },
	{ "maps\\mp\\mp_crosswalk_ss", 0 },
	{ "maps\\mp\\mp_dome", 0 },
	{ "maps\\mp\\mp_exchange", 0 },
	{ "maps\\mp\\mp_hardhat", 0 },
	{ "maps\\mp\\mp_hillside_ss", 0 },
	{ "maps\\mp\\mp_interchange", 0 },
	{ "maps\\mp\\mp_italy", 0 },
	{ "maps\\mp\\mp_lambeth", 0 },
	{ "maps\\mp\\mp_meteora", 0 },
	{ "maps\\mp\\mp_moab", 0 },
	{ "maps\\mp\\mp_mogadishu", 0 },
	{ "maps\\mp\\mp_morningwood", 0 },
	{ "maps\\mp\\mp_nola", 0 },
	{ "maps\\mp\\mp_overwatch", 0 },
	{ "maps\\mp\\mp_paris", 0 },
	{ "maps\\mp\\mp_park", 0 },
	{ "maps\\mp\\mp_plaza2", 0 },
	{ "maps\\mp\\mp_qadeem", 0 },
	{ "maps\\mp\\mp_radar", 0 },
	{ "maps\\mp\\mp_restrepo_ss", 0 },
	{ "maps\\mp\\mp_roughneck", 0 },
	{ "maps\\mp\\mp_seatown", 0 },
	{ "maps\\mp\\mp_shipbreaker", 0 },
	{ "maps\\mp\\mp_six_ss", 0 },
	{ "maps\\mp\\mp_terminal_cls", 0 },
	{ "maps\\mp\\mp_underground", 0 },
	{ "maps\\mp\\mp_village", 0 },
	{ "maps\\mp\\gametypes\\arena", 0 },
	{ "maps\\mp\\gametypes\\conf", 0 },
	{ "maps\\mp\\gametypes\\ctf", 0 },
	{ "maps\\mp\\gametypes\\ctfpro", 0 },
	{ "maps\\mp\\gametypes\\dd", 0 },
	{ "maps\\mp\\gametypes\\dm", 0 },
	{ "maps\\mp\\gametypes\\dom", 0 },
	{ "maps\\mp\\gametypes\\grnd", 0 },
	{ "maps\\mp\\gametypes\\gtnw", 0 },
	{ "maps\\mp\\gametypes\\gun", 0 },
	{ "maps\\mp\\gametypes\\infect", 0 },
	{ "maps\\mp\\gametypes\\jugg", 0 },
	{ "maps\\mp\\gametypes\\koth", 0 },
	{ "maps\\mp\\gametypes\\oic", 0 },
	{ "maps\\mp\\gametypes\\oneflag", 0 },
	{ "maps\\mp\\gametypes\\sab", 0 },
	{ "maps\\mp\\gametypes\\sd", 0 },
	{ "maps\\mp\\gametypes\\tdef", 0 },
	{ "maps\\mp\\gametypes\\tjugg", 0 },
	{ "maps\\mp\\gametypes\\vip", 0 },
	{ "maps\\mp\\gametypes\\war", 0 },
	// 1-28
	{ "maps\\mp\\gametypes\\_tweakables", 29 },
	{ "common_scripts\\utility", 30 },
	{ "common_scripts\\_createfxmenu", 31 },
	{ "common_scripts\\_fx", 32 },
	// 33-69
	{ "common_scripts\\_destructible", 70 },
	// 75-93
	{ "common_scripts\\_destructible_types", 94 },
	// 95-224
	{ "common_scripts\\_artcommon", 225 },
	// 226-272
	{ "common_scripts\\_elevator", 273 },
	// 274-313
	{ "common_scripts\\_pipes", 314 },
	{ "common_scripts\\_dynamic_world", 315 },
	// 316-323
	{ "codescripts\\character", 324 },
	// 325-365
	{ "maps\\mp\\_utility", 366 },
	{ "maps\\mp\\gametypes\\_rank", 367 },
	{ "maps\\mp\\gametypes\\_persistence", 368 },
	// 369-399
	{ "maps\\mp\\gametypes\\_gamelogic", 400 },
	{ "maps\\mp\\killstreaks\\_killstreaks", 401 },
	{ "maps\\mp\\gametypes\\_missions", 402 },
	{ "maps\\mp\\gametypes\\_hud_message", 403 },
	{ "characters\\mp_character_ally_ghillie_desert_sniper?", 404 },
	{ "characters\\mp_character_opforce_ghillie_desert_sniper?", 405 },

	{ "common_scripts\\_createfx", 512 },
		
	// 400s 500s 600s, 700s characters, animated_models, animscripts ...
	{ "maps\\mp\\gametypes\\_hostmigration", 712 },
	{ "mptype\\mptype_ally_ghillie_desert", 713 },
	{ "mptype\\mptype_opforce_ghillie_desert", 714 },
	{ "mptype\\mptype_ally_ghillie_arctic", 715 },
	{ "mptype\\mptype_opforce_ghillie_arctic", 716 },
	{ "mptype\\mptype_ally_ghillie_urban", 717 },
	{ "mptype\\mptype_opforce_ghillie_urban", 718 },
	{ "mptype\\mptype_ally_ghillie_forest", 719 },
	{ "mptype\\mptype_opforce_ghillie_forest", 720 },
	{ "mptype\\mptype_opforce_ghillie_militia", 721 },
	{ "mptype\\mptype_delta_multicam_assault", 722 },
	{ "mptype\\mptype_delta_multicam_lmg", 723 },
	{ "mptype\\mptype_delta_multicam_smg", 724 },
	{ "mptype\\mptype_delta_multicam_shotgun", 725 },
	{ "mptype\\mptype_delta_multicam_riot", 726 },
	{ "mptype\\mptype_ally_juggernaut", 727 },
	{ "mptype\\mptype_sas_urban_assault", 728 },
	{ "mptype\\mptype_sas_urban_lmg", 729 },
	{ "mptype\\mptype_sas_urban_shotgun", 730 },
	{ "mptype\\mptype_sas_urban_smg", 731 },
	{ "mptype\\mptype_sas_urban_sniper", 732 },
	{ "mptype\\mptype_gign_paris_assault", 733 },
	{ "mptype\\mptype_gign_paris_lmg", 734 },
	{ "mptype\\mptype_gign_paris_shotgun", 735 },
	{ "mptype\\mptype_gign_paris_smg", 736 },
	// 737-766
	{ "mptype\\mptype_gign_paris_sniper", 767 },
	{ "mptype\\mptype_gign_paris_riot", 768 },
	{ "mptype\\mptype_pmc_africa_assault", 769 },
	{ "mptype\\mptype_pmc_africa_lmg", 770 },
	{ "mptype\\mptype_pmc_africa_smg", 771 },
	{ "mptype\\mptype_pmc_africa_shotgun", 772 },
	{ "mptype\\mptype_pmc_africa_sniper", 773 },
	{ "mptype\\mptype_pmc_africa_riot", 774 },
	{ "mptype\\mptype_opforce_air_assault", 775 },
	{ "mptype\\mptype_opforce_air_lmg", 776 },
	{ "mptype\\mptype_opforce_air_shotgun", 777 },
	{ "mptype\\mptype_opforce_air_smg", 778 },
	{ "mptype\\mptype_opforce_air_sniper", 779 },
	{ "mptype\\mptype_opforce_air_riot", 780 },
	{ "mptype\\mptype_opforce_juggernaut", 781 },
	{ "mptype\\mptype_opforce_snow_assault", 782 },
	{ "mptype\\mptype_opforce_snow_lmg", 783 },
	{ "mptype\\mptype_opforce_snow_shotgun", 784 },
	{ "mptype\\mptype_opforce_snow_smg", 785 },
	{ "mptype\\mptype_opforce_snow_sniper", 786 },
	{ "mptype\\mptype_opforce_snow_riot", 787 },
	{ "mptype\\mptype_opforce_urban_assault", 788 },
	{ "mptype\\mptype_opforce_urban_lmg", 789 },
	{ "mptype\\mptype_opforce_urban_shotgun", 790 },
	{ "mptype\\mptype_opforce_urban_smg", 791 },
	{ "mptype\\mptype_opforce_urban_sniper", 792 },
	{ "mptype\\mptype_opforce_urban_riot", 793 },
	{ "mptype\\mptype_opforce_woodland_assault", 794 },
	{ "mptype\\mptype_opforce_woodland_lmg", 795 },
	{ "mptype\\mptype_opforce_woodland_shotgun", 796 },
	// 797-818
	{ "mptype\\mptype_opforce_woodland_smg", 819 },
	{ "mptype\\mptype_opforce_woodland_sniper", 820 },
	{ "mptype\\mptype_opforce_woodland_riot", 821 },
	{ "mptype\\mptype_opforce_africa_assault", 822 },
	{ "mptype\\mptype_opforce_africa_lmg", 823 },
	{ "mptype\\mptype_opforce_africa_shotgun", 824 },
	{ "mptype\\mptype_opforce_africa_smg", 825 },
	{ "mptype\\mptype_opforce_africa_sniper", 826 },
	{ "mptype\\mptype_opforce_africa_riot", 827 },
	{ "mptype\\mptype_opforce_henchmen_assault", 828 },
	{ "mptype\\mptype_delta_multicam_sniper", 829 },
	{ "mptype\\mptype_opforce_henchmen_lmg", 830 },
	{ "mptype\\mptype_opforce_henchmen_shotgun", 831 },
	{ "mptype\\mptype_opforce_henchmen_smg", 832 },
	{ "mptype\\mptype_opforce_henchmen_sniper", 833 },
	{ "mptype\\mptype_opforce_henchmen_riot", 834 },
	{ "maps\\mp\\gametypes\\_weapons", 835 },
	{ "maps\\mp\\_entityheadicons", 836 },
	{ "maps\\mp\\gametypes\\_damagefeedback", 837 },
	{ "maps\\mp\\_stinger", 838 },
	{ "maps\\mp\\_flashgrenades", 839 },
	{ "maps\\mp\\_empgrenade", 840 },
	{ "maps\\mp\\gametypes\\_class", 841 },
	{ "maps\\mp\\_equipment", 842 },
	{ "maps\\mp\\_javelin", 843 },
	{ "maps\\mp\\gametypes\\_shellshock", 844 },
	{ "maps\\mp\\_matchdata", 845 },
	{ "maps\\mp\\killstreaks\\_perkstreaks", 846 },
	{ "maps\\mp\\perks\\_perkfunctions", 847 },
	{ "maps\\mp\\gametypes\\_scrambler", 848 },
	{ "maps\\mp\\gametypes\\_portable_radar", 849 },
	{ "maps\\mp\\gametypes\\_objpoints", 850 },
	{ "maps\\mp\\gametypes\\_hud_util", 851 },
	{ "maps\\mp\\gametypes\\_gameobjects", 852 },
	//853-872
	{"maps\\mp\\gametypes\\_quickmessages", 873 },
	{ "maps\\mp\\gametypes\\_playerlogic", 874 },
	{ "maps\\mp\\gametypes\\_spectating", 875 },
	{ "maps\\mp\\gametypes\\_spawnlogic", 876 },
	{ "maps\\mp\\_events", 877 },
	{ "maps\\mp\\gametypes\\_gamescore", 878 },
	{ "maps\\mp\\gametypes\\_menus", 879 },
	{ "maps\\mp\\_minefields", 880 },
	{ "maps\\mp\\_radiation", 881 },
	{ "maps\\mp\\_shutter", 882 },
	{ "maps\\mp\\_destructables", 883 },
	{ "maps\\mp\\_audio", 884 },
	{ "maps\\mp\\_art", 885 },
	{ "maps\\mp\\_createfx", 886 },
	{ "maps\\mp\\_global_fx", 887 },
	{ "maps\\mp\\_animatedmodels", 888 },
	{ "maps\\mp\\killstreaks\\_helicopter", 889 },
	{ "maps\\mp\\_skill", 890 },
	{ "maps\\mp\\killstreaks\\_remoteuav", 891 },
	{ "maps\\mp\\gametypes\\_battlechatter_mp", 892 },
	{ "maps\\mp\\gametypes\\_deathicons", 893 },
	{ "maps\\mp\\gametypes\\_killcam", 894 },
	{ "maps\\mp\\perks\\_perks", 895 },
	{ "maps\\mp\\gametypes\\_damage", 896 },
	{ "maps\\mp\\_highlights", 897 },
	{ "maps\\mp\\killstreaks\\_escortairdrop", 898 },
	{ "maps\\mp\\killstreaks\\_juggernaut", 899 },
	{ "maps\\mp\\killstreaks\\_autosentry", 900 },
	{ "maps\\mp\\killstreaks\\_airdrop", 901 },
	{ "maps\\mp\\gametypes\\_hud", 902 },
	{ "maps\\mp\\_load", 903 },
	{ "maps\\mp\\gametypes\\_serversettings", 904 },
	{ "905", 905 },
	{ "maps\\mp\\mp_plaza2_precache", 906 },
	{ "maps\\mp\\mp_plaza2_fx", 907 },
	{ "maps\\mp\\mp_carbon_precache", 908 },
	{ "maps\\mp\\mp_carbon_fx", 909 },
	{ "910", 910 },
	{ "911", 911 },
	{ "maps\\mp\\mp_village_precache", 912 },
	{ "maps\\mp\\mp_village_fx", 913 },
	{ "maps\\mp\\mp_seatown_precache", 914 },
	{ "maps\\mp\\mp_seatown_fx", 915 },
	{ "maps\\mp\\mp_lambeth_precache",916 },
	{ "maps\\mp\\mp_lambeth_fx", 917 },
	{ "maps\\mp\\mp_hardhat_precache",918 },
	{ "maps\\mp\\mp_hardhat_fx", 919 },
	{ "maps\\mp\\mp_bootleg_precache", 920 },
	{ "maps\\mp\\mp_bootleg_fx", 921 },
	{ "maps\\mp\\mp_exchange_precache", 922 },
	{ "maps\\mp\\mp_exchange_fx", 923 },
	{ "maps\\mp\\mp_mogadishu_precache", 924 },
	{ "maps\\mp\\mp_mogadishu_fx", 925 },
	{ "maps\\mp\\mp_underground_precache", 926 },
	{ "maps\\mp\\mp_underground_fx", 927 },
	{ "maps\\mp\\mp_interchange_precache", 928 },
	{ "maps\\mp\\mp_interchange_fx", 929 },
	{ "930", 930 },
	{ "931", 931 },
	{ "932", 932 },
	{ "933", 933 },
	{ "maps\\mp\\gametypes\\_healthoverlay", 934 },
	{ "maps\\mp\\gametypes\\_music_and_dialog", 935 },
	{ "maps\\mp\\_awards", 936 },
	{ "maps\\mp\\_areas", 937 },
	{ "maps\\mp\\_defcon", 938 },
	{ "maps\\mp\\_matchevents", 939 },
	{ "maps\\mp\\gametypes\\_friendicons", 940 },
	{ "maps\\mp\\gametypes\\_scoreboard", 941 },
	{ "maps\\mp\\killstreaks\\_harrier", 942 },
	{ "maps\\mp\\gametypes\\_callbacksetup", 943 },
	{ "maps\\mp\\killstreaks\\_airstrike", 944 },
	{ "maps\\mp\\killstreaks\\_emp", 945 },
	{ "maps\\mp\\killstreaks\\_uav", 946 },
	{ "maps\\mp\\killstreaks\\_ac130", 947 },
	{ "maps\\mp\\killstreaks\\_remotemissile", 948 },
	{ "maps\\mp\\killstreaks\\_helicopter_flock", 949 },
	// empty 950-967
	{ "maps\\mp\\mp_dome_precache", 967 },
	{ "maps\\mp\\mp_dome_fx", 968 },
	{ "969", 969 },
	{ "970", 970 },
	{ "maps\\mp\\mp_radar_precache", 971 },
	{ "maps\\mp\\mp_radar_fx", 972 },
	{ "maps\\mp\\mp_paris_precache", 973 },
	{ "maps\\mp\\mp_paris_fx", 974 },
	{ "maps\\mp\\mp_bravo_precache", 975 },
	{ "maps\\mp\\mp_bravo_fx", 976 },
	{ "maps\\mp\\mp_alpha_precache", 977 },
	{ "maps\\mp\\mp_alpha_fx", 978 },
	{ "maps\\mp\\killstreaks\\_helicopter_guard", 979 },
	{ "maps\\mp\\killstreaks\\_nuke", 980 },
	{ "maps\\mp\\killstreaks\\_remotemortar", 981 },
	{ "maps\\mp\\killstreaks\\_deployablebox", 982 },
	{ "maps\\mp\\killstreaks\\_ims", 983 },
	{ "maps\\mp\\killstreaks\\_remoteturret", 984 },
	{ "maps\\mp\\killstreaks\\_remotetank", 985 },
	{ "maps\\mp\\gametypes\\_playercards", 986 },
	{ "maps\\mp\\gametypes\\_globallogic", 987 },
	// 988-997
	{ "maps\\mp\\gametypes\\_teams", 998 },
	// 999-1215
	{ "maps\\mp\\killstreaks\\_pavelow", 1216 },
	{ "maps\\mp\\_fx", 1217 },
	{ "maps\\mp\\_compass", 1218 },
	{ "1219", 1219 }, // 1 empty function
	{ "maps\\mp\\_crib", 1220 },
	{ "maps\\mp\\killstreaks\\_autoshotgun", 1221 },
	{ "maps\\mp\\killstreaks\\_tank", 1222 },
	{ "maps\\mp\\killstreaks\\_mobilemortar", 1223 },
	{ "maps\\mp\\killstreaks\\_a10", 1224 },
	{ "maps\\mp\\killstreaks\\_teamammorefill", 1225 },
	{ "1226", 1226 }, // empty file
	{ "1227", 1227 }, // 11 empty functions
	{ "1228", 1228 }, // empty file
	{ "1229", 1229 }, // empty file
	{ "maps\\mp\\killstreaks\\_aamissile", 1230 },
	{ "maps\\mp\\killstreaks\\_aastrike", 1231 },
	{ "maps\\mp\\killstreaks\\_reaper", 1232 },
	// 1233-1342
	{ "mp_character_gign_head", 1343 }, // unk
	{ "codescripts\\delete", 1344 },
	{ "codescripts\\struct", 1345 },

	{ "maps\\createart\\mp_dome_art", 1459 },
	{ "maps\\mp\\_explosive_barrels", 1460 },
};

auto get_file_id(std::string name) -> std::uint16_t
{
	if (file_map.find(name) != file_map.end())
	{
		return file_map[name];
	}

	XSK_ERROR("Couldn't resolve file id for name '%s'!", name.c_str());
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

	XSK_ERROR("Couldn't resolve file name for id '%i'!", id);
	return "";
}

} // namespace iw5

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