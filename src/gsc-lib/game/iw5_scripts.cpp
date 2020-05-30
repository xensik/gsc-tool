#include "stdinc.hpp"

namespace iw5
{
	struct scr_id_def
	{
		std::uint16_t id;
		std::unordered_map<std::string, std::uint16_t> funcs;
	};

	std::unordered_map<std::string, scr_id_def> script_ids
	{
		///////////////////////////////////////////////////////////
		// codescripts

		{ "codescripts/character",
			{
				324,
				{
					{ "setModelFromArray", 7765 },
					{ "precacheModelArray", 7766 },
					{ "attachHead", 7767 },
					{ "func_1E5B", 7771 },
					{ "new", 7773 },
					{ "save", 7776 },
					{ "load", 7778 },
					{ "get_random_character", 7779 },
					{ "get_least_used_index", 7782 },
					{ "initialize_character_group", 7783 },
					{ "get_random_weapon", 7784 },
					{ "random", 2363 },
				},
			},
		},

		{ "codescripts/delete",
			{
				1344,
				{
					{"main", 1650},
				},
			},
		},

		{ "codescripts/struct",
			{
				1345,
				{
					{"initstructs", 1661},
					{"createstruct", 1662},
				},
			},
		},

		///////////////////////////////////////////////////////////
		// common_scripts

		{ "common_scripts/_artcommon",
			{
				225,
				{
					{ "artStartVisionFileExport", 6858 },
					{ "artEndVisionFileExport", 6859 },
					{ "artStartFogFileExport", 6860 },
					{ "artEndFogFileExport", 6861 },
					{ "artCommonfxprintln", 6862 },
					{ "setfogsliders", 6863 },
					{ "translateFogSlidersToScript", 6864 },
					{ "limit", 6875 },
					{ "updateFogFromScript", 6876 },
					{ "artfxprintlnFog", 6877 },
				},
			},
		},

		{ "common_scripts/_createfx",
			{
				0,
				{

				},
			},
		},

		{ "common_scripts/_createfxmenu",
			{
				31,
				{

				},
			},
		},

		{ "common_scripts/_destructible",
			{
				70,
				{

				},
			},
		},

		{ "common_scripts/_destructible_types",
			{
				94,
				{

				},
			},
		},

		{ "common_scripts/_dynamic_world",
			{
				315,
				{

				},
			},
		},

		{ "common_scripts/_elevator",
			{
				273,
				{

				},
			},
		},

		{ "common_scripts/_fx",
			{
				32,
				{

				},
			},
		},

		{ "common_scripts/_pipes",
			{
				314,
				{

				},
			},
		},

		{ "common_scripts/utility",
			{
				30,
				{

				},
			},
		},

		///////////////////////////////////////////////////////////
		// maps

		///////////////////////////////////////////////////////////
		// maps/createart

		///////////////////////////////////////////////////////////
		// maps/createfx

		///////////////////////////////////////////////////////////
		// maps/mp

		{ "map/mp/_animatedmodels",
			{
				888,
				{

				},
			},
		},

		{ "map/mp/_areas",
			{
				937,
				{

				},
			},
		},

		{ "map/mp/_art",
			{
				885,
				{

				},
			},
		},

		{ "map/mp/_audio",
			{
				884,
				{

				},
			},
		},

		{ "map/mp/_awards",
			{
				936,
				{

				},
			},
		},

		{ "map/mp/_compass",
			{
				1218,
				{

				},
			},
		},

		{ "map/mp/_createfx",
			{
				886,
				{

				},
			},
		},

		{ "map/mp/_crib",
			{
				1220,
				{

				},
			},
		},

		{ "map/mp/_defcon",
			{
				938,
				{

				},
			},
		},

		{ "map/mp/_destructables",
			{
				883,
				{

				},
			},
		},

		{ "map/mp/_empgrenade",
			{
				840,
				{

				},
			},
		},

		{ "map/mp/_entityheadicons",
			{
				836,
				{

				},
			},
		},

		{ "map/mp/_events",
			{
				877,
				{

				},
			},
		},

		{ "map/mp/_flashgrenades",
			{
				839,
				{

				},
			},
		},

		{ "map/mp/_fx",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_global_fx",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_highlights",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_javelin",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_load",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_matchdata",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_matchevents",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_minefields",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_radiation",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_scoreboard",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_shutter",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_skill",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_stinger",
			{
				0,
				{

				},
			},
		},

		{ "map/mp/_utility",
			{
				0,
				{

				},
			},
		},

		///////////////////////////////////////////////////////////
		// maps/mp/animated_models


		///////////////////////////////////////////////////////////
		// maps/mp/gametypes

		{ "maps/mp/gametypes/_battlechatter_mp",
			{
				892,
				{
					{ "init", 1664 },
					{ "onPlayerConnect", 7448 },
					{ "onPlayerSpawned", 11281 },
					{ "grenadeProximityTracking", 12633 },
					{ "suppressingFireTracking", 12634 },
					{ "suppressWaiter", 12635 },
					{ "claymoreTracking", 12636 },
					{ "reloadTracking", 12637 },
					{ "grenadeTracking", 12638 },
					{ "sayLocalSoundDelayed", 12639 },
					{ "sayLocalSound", 12640 },
					{ "doSound", 12641 },
					{ "timeHack", 12642 },
					{ "isSpeakerInRange", 12643 },
					{ "addSpeaker", 12644 },
					{ "removeSpeaker", 12645 },
				},
			},
		},

		{ "maps/mp/gametypes/_callbacksetup",
			{
				943,
				{
					{ "CodeCallback_StartGameType", 1651 },
					{ "CodeCallback_PlayerConnect", 1652 },
					{ "CodeCallback_PlayerDisconnect", 1653 },
					{ "CodeCallback_PlayerDamage", 1654 },
					{ "CodeCallback_PlayerKilled", 1655 },
					{ "CodeCallback_VehicleDamage", 1656 },
					{ "CodeCallback_CodeEndGame", 1657 },
					{ "CodeCallback_PlayerLastStand", 1658 },
					{ "CodeCallback_PlayerMigrated", 1659 },
					{ "CodeCallback_HostMigration", 1660 },
					{ "SetupDamageFlags", 13320 },
					{ "SetupCallbacks", 13325 },
					{ "SetDefaultCallbacks", 13326 },
					{ "AbortLevel", 13327 },
					{ "callbackVoid", 13328 },
				}
			},
		},

		{ "maps/mp/gametypes/_class",
			{
				841,
				{
					{ "init", 1664 },
					{ "getClassChoice", 12179 },
					{ "getWeaponChoice", 12180 },
					{ "logClassChoice", 14202 },
					{ "cac_getCustomClassLoc", 442 },
					{ "cac_getWeapon", 11477 },
					{ "cac_getWeaponAttachment", 11622 },
					{ "cac_getWeaponAttachmentTwo", 11623 },
					{ "cac_getWeaponBuff", 11627 },
					{ "cac_getWeaponCamo", 14203 },
					{ "cac_getWeaponReticle", 14204 },
					{ "cac_getPerk", 11625 },
					{ "cac_getKillstreak", 11628 },
					{ "cac_getDeathstreak", 11626 },
					{ "cac_getOffhand", 11624 },
					{ "recipe_getKillstreak", 14205 },
					{ "table_getWeapon", 11630 },
					{ "table_getWeaponAttachment", 11631 },
					{ "table_getWeaponBuff", 11636 },
					{ "table_getWeaponCamo", 14206 },
					{ "table_getWeaponReticle", 14207 },
					{ "table_getEquipment", 11633 },
					{ "table_getPerk", 11634 },
					{ "table_getTeamPerk", 14208 },
					{ "table_getOffhand",11632 },
					{ "table_getKillstreak", 11637 },
					{ "table_getDeathstreak", 11635 },
					{ "getClassIndex", 11621 },
					{ "cloneLoadout", 12660 },
					{ "loadoutFakePerks", 14209 },
					{ "getLoadoutStreakTypeFromStreakType", 14210 },
					{ "giveLoadout", 12026 },
					{ "_detachAll", 14218 },
					{ "isPerkUpgraded", 14023 },
					{ "getPerkUpgrade", 11681 },
					{ "loadoutAllPerks", 14219 },
					{ "trackRiotShield", 11461 },
					{ "tryAttach", 14224 },
					{ "tryDetach", 14225 },
					{ "buildWeaponName", 14226 },
					{ "buildWeaponNameCamo", 14229 },
					{ "buildWeaponNameReticle", 14230 },
					{ "makeLettersToNumbers", 14231 },
					{ "setKillstreaks", 14232 },
					{ "replenishLoadout", 14233 },
					{ "onPlayerConnecting", 14235 },
					{ "fadeAway", 14236 },
					{ "setClass", 12182 },
					{ "getPerkForClass", 14237 },
					{ "classHasPerk", 14238 },
					{ "isValidPrimary", 14198 },
					{ "isValidSecondary", 14199 },
					{ "isValidAttachment", 14239 },
					{ "isAttachmentUnlocked", 14146 },
					{ "isValidWeaponBuff", 14240 },
					{ "isWeaponBuffUnlocked", 14241 },
					{ "isValidCamo", 14242 },
					{ "isValidReticle", 14243 },
					{ "isCamoUnlocked", 14244 },
					{ "isValidEquipment", 14245 },
					{ "isValidOffhand", 14246 },
					{ "isValidPerk1", 14247 },
					{ "isValidPerk2", 14248 },
					{ "isValidPerk3", 14249 },
					{ "isValidDeathStreak", 14250 },
					{ "isValidWeapon", 14251 },
					{ "isValidKillstreak", 14253 },
				}
			},
		},

		{ "maps/mp/gametypes/_damage",
			{
				896,
				{

				},
			},
		},

		{ "maps/mp/gametypes/_damagefeedback",
			{
				837,
				{
					{ "init", 1664 },
					{ "onPlayerConnect", 7448 },
					{ "updateDamageFeedback", 6702 },
				},
			},
		},

		{ "maps/mp/gametypes/_deathicons",
			{
				893,
				{
					{ "init", 1664 },
					{ "onPlayerConnect", 7448 },
					{ "updateDeathIconsEnabled", 12384 },
					{ "addDeathIcon", 12385 },
					{ "destroySlowly", 12387 },
				},
			},
		},

		{ "maps/mp/gametypes/_equipment",
			{
				842,
				{
					{ "watchTrophyUsage", 11312 },
					{ "trophyUseListener", 11321 },
					{ "trophyPlayerSpawnWaiter", 11325 },
					{ "trophyDisconnectWaiter", 11326 },
					{ "trophyActive", 11327 },
					{ "projectileExplode", 11333 },
					{ "trophyDamage", 11336 },
					{ "trophyBreak", 11341 },
				},
			},
		},

		{ "maps/mp/gametypes/_friendicons",
			{
				940,
				{
					{ "init", 0 },
					{ "onPlayerConnect", 0 },
					{ "onPlayerSpawned", 0 },
					{ "onPlayerKilled", 0 },
					{ "showFriendIcon", 0 },
					{ "updateFriendIconSettings", 0 },
					{ "updateFriendIcons", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_gamelogic",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_gameobjects",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_globalentities",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_globallogic",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_healthoverlay",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_hostmigration",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_hud",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_hud_message",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_hud_util",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_killcam",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_menus",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_missions",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_music_and_dialog",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_objpoints",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_persistence",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_playercards",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_playerlogic",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_portable_radar",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_quickmessages",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_rank",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},


		{ "maps/mp/gametypes/_scrambler",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_serversettings",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_shellshock",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_spawnlogic",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_spectating",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_teams",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_tweakables",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/_weapons",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/arena",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/conf",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/ctf",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/ctfpro",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/dd",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/dm",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/dom",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/grnd",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/gtnw",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/gun",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/infect",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/ioc",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/jugg",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/koth",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/oneflag",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/sab",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/sd",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/tdef",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/tjugg",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/vip",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/war",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		{ "maps/mp/gametypes/faceoff",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},

		///////////////////////////////////////////////////////////
		// maps/mp/killstreaks

		{ "maps/mp/killstreaks/_a10",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_aamissile",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_aastrike",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_ac130",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_airdrop",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_airstrike",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_autosentry",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_autoshotgun",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_deployablebox",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_emp",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_escortairdrop",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_harrier",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_helicopter",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_helicopter_flock",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_helicopter_guard",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_ims",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_juggernaut",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_killstreaks",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_mobilemortar",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_nuke",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_perkstreaks",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_remotemissile",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_remotemortar",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_remotetank",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_remoteturret",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_remoteuav",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_tank",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_teamammorefill",
			{
				0,
				{
				},
			},
		},

		{ "maps/mp/killstreaks/_uav",
			{
				0,
				{
				},
			},
		},

		///////////////////////////////////////////////////////////
		// maps/mp/perks

		{ "maps/mp/perks/_perkfunctions",
			{
				0,
				{
				},
			},
		},


		{ "maps/mp/perks/_perks",
			{
				0,
				{
					{ "init", 0 },
				},
			},
		},
	};

	auto GetFileId(std::string file) -> std::uint16_t
	{
		if (script_ids.find(file) != script_ids.end())
		{
			return script_ids[file].id;
		}

		LOG_ERROR("Couldn't resolve file id for \"%s\"!", file.c_str());
		return 0;
	}

	auto GetFunctionId(std::string file, std::string func) -> std::uint16_t
	{
		if (script_ids.find(file) != script_ids.end())
		{
			auto& fns = script_ids[file].funcs;

			if (fns.find(func) != fns.end())
			{
				return fns[func];
			}

			LOG_ERROR("Couldn't resolve func id for \"%s::%s\"!", file.c_str(), func.c_str());
			return 0;
		}

		LOG_ERROR("Couldn't resolve file id for \"%s::%s\"!", file.c_str(), func.c_str());
		return 0;
	}

	auto GetFileName(std::uint16_t id) -> std::string
	{
		for (auto& file : script_ids)
		{
			if (file.second.id == id)
			{
				return file.first;
			}
		}

		LOG_ERROR("Couldn't resolve file name 0x%X!", id);
		return "";
	}

	auto GetFunctionName(std::uint16_t file, std::uint16_t func) -> std::string
	{
		for (auto& s : script_ids)
		{
			if (s.second.id == file)
			{
				auto& fns = s.second.funcs;

				for (auto& f : fns)
				{
					if (f.second == func)
					{
						return f.first;
					}
				}

				LOG_ERROR("Couldn't resolve func name for 0x%X::0x%X!", file, func);
				return "";
			}
		}

		LOG_ERROR("Couldn't resolve file name for 0x%X::0x%X!", file, func);
		return "";
	}
}



std::unordered_map <std::uint16_t, std::string> filename_map =
{
	// missing files: aitype, animscripts, character, animated_models, mptype
	// _dev, _globalentities, _hostmigration (empty files?)
	{ 29, "maps/mp/gametypes/_tweakables" },
	{ 30, "common_scripts/utility" },
	{ 31, "common_scripts/_createfxmenu" },
	{ 32, "common_scripts/_fx" },
	// empty 33-69
	{ 70, "common_scripts/_destructible" },
	// empty 75-93
	{ 94, "common_scripts/_destructible_types" },
	// empty 95-224
	{ 225, "common_scripts/_artcommon" },
	// empty 226-272
	{ 273, "common_scripts/_elevator" },
	// empty 274-313
	{ 314, "common_scripts/_pipes" },
	{ 315, "common_scripts/_dynamic_world" },
	// empty 316-323
	{ 324, "codescripts/character" },
	// empty 325-365
	{ 366, "maps/mp/_utility" },
	{ 367, "maps/mp/gametypes/_rank" },
	{ 368, "maps/mp/gametypes/_persistence" },
	// empty 369-399
	{ 400, "maps/mp/gametypes/_gamelogic" },
	{ 401, "maps/mp/killstreaks/_killstreaks" },
	{ 402, "maps/mp/gametypes/_missions" },
	{ 403, "maps/mp/gametypes/_hud_message" },
	// characters
	{ 404, "mp_character_ally_ghillie_desert_sniper" },
	{ 405, "mp_character_opforce_ghillie_desert_sniper" },
	// 400s characters
	{ 491, "mp_character_sas_urban_assault" },
	{ 512, "unknown" },// 512 some utility shit
	// 532 characters
	// 533 characters
	// 600s, 700s 819-834 characters, animated_models, animscripts ...
	{ 835, "maps/mp/gametypes/_weapons" },
	{ 836, "maps/mp/_entityheadicons" },
	{ 837, "maps/mp/gametypes/_damagefeedback" },
	{ 838, "maps/mp/_stinger" },
	{ 839, "maps/mp/_flashgrenades" },
	{ 840, "maps/mp/_empgrenade" },
	{ 841, "maps/mp/gametypes/_class" },
	{ 842, "maps/mp/gametypes/_equipment" },
	{ 843, "maps/mp/_javelin" },
	{ 844, "maps/mp/gametypes/_shellshock" },
	{ 845, "maps/mp/_matchdata" },
	{ 846, "maps/mp/killstreaks/_perkstreaks" },
	{ 847, "maps/mp/perks/_perkfunctions" },
	{ 848, "maps/mp/gametypes/_scrambler" },
	{ 849, "maps/mp/gametypes/_portable_radar" },
	{ 850, "maps/mp/gametypes/_objpoints" },
	{ 851, "maps/mp/gametypes/_hud_util" },
	{ 852, "maps/mp/gametypes/_gameobjects" },
	// empty 953-972
	{ 873, "maps/mp/gametypes/_quickmessages" },
	{ 874, "maps/mp/gametypes/_playerlogic" },
	{ 875, "maps/mp/gametypes/_spectating" },
	{ 876, "maps/mp/gametypes/_spawnlogic" },
	{ 877, "maps/mp/_events" },
	{ 878, "maps/mp/gametypes/_gamescore" },
	{ 879, "maps/mp/gametypes/_menus" },
	{ 880, "maps/mp/_minefields" },
	{ 881, "maps/mp/_radiation" },
	{ 882, "maps/mp/_shutter" },
	{ 883, "maps/mp/_destructables" },
	{ 884, "maps/mp/_audio" },
	{ 885, "maps/mp/_art" }, // 4 empty functions (iw4 have 4 empty funcs too)
	{ 886, "maps/mp/_createfx" },
	{ 887, "maps/mp/_global_fx" },
	{ 888, "maps/mp/_animatedmodels" },
	{ 889, "maps/mp/killstreaks/_helicopter" },
	{ 890, "maps/mp/_skill" },
	{ 891, "maps/mp/killstreaks/_remoteuav" },
	{ 892, "maps/mp/gametypes/_battlechatter_mp" },
	{ 893, "maps/mp/gametypes/_deathicons" },
	{ 894, "maps/mp/gametypes/_killcam" },
	{ 895, "maps/mp/perks/_perks" },
	{ 896, "maps/mp/gametypes/_damage" },
	{ 897, "maps/mp/_highlights" },
	{ 898, "maps/mp/killstreaks/_escortairdrop" },
	{ 899, "maps/mp/killstreaks/_juggernaut" },
	{ 900, "maps/mp/killstreaks/_autosentry" },
	{ 901, "maps/mp/killstreaks/_airdrop" },
	{ 902, "maps/mp/gametypes/_hud" },
	{ 903, "maps/mp/_load" },
	{ 904, "maps/mp/gametypes/_serversettings" },
	// empty 905-933
	{ 906, "unknown" }, // mp_plaza2.ff
	{ 907, "unknown" }, // mp_plaza2.ff
	{ 908, "unknown" }, // mp_carbon.ff
	{ 909, "unknown" }, // mp_carbon.ff

	{ 912, "unknown" }, // mp_village.ff
	{ 913, "unknown" }, // mp_village.ff
	{ 914, "maps/mp/mp_seatown_precache" }, // mp_seatown.ff
	{ 915, "maps/mp/mp_seatown_fx" }, // mp_seatown.ff
	{ 916, "unknown" }, // mp_lambeth.ff
	{ 917, "unknown" }, // mp_lambeth.ff
	{ 918, "unknown" }, // mp_hardhat.ff
	{ 919, "unknown" }, // mp_hardhat.ff
	{ 920, "unknown" }, // mp_bootleg.ff
	{ 921, "unknown" }, // mp_bootleg.ff
	{ 922, "unknown" }, // mp_exchange.ff
	{ 923, "unknown" }, // mp_exchange.ff
	{ 924, "unknown" }, // mp_mogadishu.ff
	{ 925, "unknown" }, // mp_mogadishu.ff
	{ 926, "unknown" }, // mp_underground.ff
	{ 927, "unknown" }, // mp_underground.ff
	{ 928, "unknown" }, // mp_interchange.ff
	{ 929, "unknown" }, // mp_interchange.ff

	{ 934, "maps/mp/gametypes/_healthoverlay" },
	{ 935, "maps/mp/gametypes/_music_and_dialog" },
	{ 936, "maps/mp/_awards" },
	{ 937, "maps/mp/_areas" },
	{ 938, "maps/mp/_defcon" },
	{ 939, "maps/mp/_matchevents" },
	{ 940, "maps/mp/gametypes/_friendicons" },
	{ 941, "maps/mp/gametypes/_scoreboard" },
	{ 942, "maps/mp/killstreaks/_harrier" },
	{ 943, "maps/mp/gametypes/_callbacksetup" },
	{ 944, "maps/mp/killstreaks/_airstrike" },
	{ 945, "maps/mp/killstreaks/_emp" },
	{ 946, "maps/mp/killstreaks/_uav" },
	{ 947, "maps/mp/killstreaks/_ac130" },
	{ 948, "maps/mp/killstreaks/_remotemissile" },
	{ 949, "maps/mp/killstreaks/_helicopter_flock" },
	// empty 950-978
	{ 967, "maps/mp/mp_dome_precache" }, // mp_dome.ff
	{ 968, "maps/mp/mp_dome_fx" }, // mp_dome.ff

	{ 971, "unknown" }, // mp_radar.ff
	{ 972, "unknown" }, // mp_radar.ff
	{ 973, "unknown" }, // mp_paris.ff
	{ 974, "unknown" }, // mp_paris.ff
	{ 975, "unknown" }, // mp_bravo.ff
	{ 976, "unknown" }, // mp_bravo.ff
	{ 977, "unknown" }, // mp_alpha.ff
	{ 978, "unknown" }, // mp_alpha.ff
	{ 979, "maps/mp/killstreaks/_helicopter_guard" },
	{ 980, "maps/mp/killstreaks/_nuke" },
	{ 981, "maps/mp/killstreaks/_remotemortar" },
	{ 982, "maps/mp/killstreaks/_deployablebox" },
	{ 983, "maps/mp/killstreaks/_ims" },
	{ 984, "maps/mp/killstreaks/_remoteturret" },
	{ 985, "maps/mp/killstreaks/_remotetank" },
	{ 986, "maps/mp/gametypes/_playercards" },
	{ 987, "maps/mp/gametypes/_globallogic" },
	// empty 988-997
	{ 998, "maps/mp/gametypes/_teams" },
	// empty 999-1215
	{ 1216, "maps/mp/killstreaks/_pavelow" },
	{ 1217, "maps/mp/_fx" },
	{ 1218, "maps/mp/_compass" },
	{ 1219, "unknown" }, // 1 empty function
	{ 1220, "maps/mp/_crib" },
	{ 1221, "maps/mp/killstreaks/_autoshotgun" },
	{ 1222, "maps/mp/killstreaks/_tank" },
	{ 1223, "maps/mp/killstreaks/_mobilemortar" },
	{ 1224, "maps/mp/killstreaks/_a10" },
	{ 1225, "maps/mp/killstreaks/_teamammorefill" },
	{ 1226, "unknown" }, // empty file
	{ 1227, "unknown" }, // 11 empty functions
	{ 1228, "unknown" }, // empty file
	{ 1229, "unknown" }, // empty file
	{ 1230, "maps/mp/killstreaks/_aamissile" },
	{ 1231, "maps/mp/killstreaks/_aastrike" },
	{ 1232, "maps/mp/killstreaks/_reaper" },
	// empty 1233-1342
	{ 1343, "mp_character_gign_head" }, // unk
	{ 1344, "codescripts/delete" },
	{ 1345, "codescripts/struct" },

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
	{ 1459, "unknown" }, // mp_dome.ff fx, art
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
};


/*std::unordered_map <std::uint16_t, std::string> functions_map =
	{
		{ 1650, "main" },
		{ 1651, "CodeCallback_StartGameType" },
		{ 1652, "CodeCallback_PlayerConnect" },
		{ 1653, "CodeCallback_PlayerDisconnect" },
		{ 1654, "CodeCallback_PlayerDamage" },
		{ 1655, "CodeCallback_PlayerKilled" },
		{ 1656, "CodeCallback_VehicleDamage" },
		{ 1657, "CodeCallback_CodeEndGame" },
		{ 1658, "CodeCallback_PlayerLastStand" },
		{ 1659, "CodeCallback_PlayerMigrated" },
		{ 1660, "CodeCallback_HostMigration" },
		{ 1661, "initstructs" },
		{ 1662, "createstruct" },
		{ 1663, "" }, // unk
		{ 1664, "init" },
		{ 1665, "precache" },

		// codescripts/character
		{ 7765, "setModelFromArray" },
		{ 7766, "precacheModelArray" },
		{ 7767, "attachHead" },
		{ 7771, "func_1E5B" },
		{ 7773, "new" },
		{ 7776, "save" },
		{ 7778, "load" },
		{ 7779, "get_random_character" },
		{ 7782, "get_least_used_index" },
		{ 7783, "initialize_character_group" },
		{ 7784, "get_random_weapon" },
		{ 2363, "random" },

		// common_scripts/_artcommon
		{ 6858, "artStartVisionFileExport" },
		{ 6859, "artEndVisionFileExport" },
		{ 6860, "artStartFogFileExport" },
		{ 6861, "artEndFogFileExport" },
		{ 6862, "artCommonfxprintln" },
		{ 6863, "setfogsliders" },
		{ 6864, "translateFogSlidersToScript" },
		{ 6875, "limit" },
		{ 6876, "updateFogFromScript" },
		{ 6877, "artfxprintlnFog" },

		// common_scripts/_createfx
		{ 0, "" },

		// common_scripts/_createfxmenu
		{ 0, "" },

		// common_scripts/_destructible
		{ 0, "" },

		// common_scripts/_destructible_types
		{ 0, "" },

		// common_scripts/_dynamic_world
		{ 0, "" },

		// common_scripts/_elevator
		{ 0, "" },

		// common_scripts/_fx
		{ 0, "" },

		// common_scripts/_pipes
		{ 0, "" },

		// common_scripts/utility
		{ 0, "" },

		// maps/mp/gametypes/_battlechatter_mp
		{ 7448, "onPlayerConnect" },
		{ 11281, "onPlayerSpawned" },
		{ 12633, "grenadeProximityTracking" },
		{ 12634, "suppressingFireTracking" },
		{ 12635, "suppressWaiter" },
		{ 12636, "claymoreTracking" },
		{ 12637, "reloadTracking" },
		{ 12638, "grenadeTracking" },
		{ 12639, "sayLocalSoundDelayed" },
		{ 12640, "sayLocalSound" },
		{ 12641, "doSound" },
		{ 12642, "timeHack" },
		{ 12643, "isSpeakerInRange" },
		{ 12644, "addSpeaker" },
		{ 12645, "removeSpeaker" },

		// maps/mp/gametypes/_callbacksetup
		{ 13320, "SetupDamageFlags" },
		{ 13325, "SetupCallbacks" },
		{ 13326, "SetDefaultCallbacks" },
		{ 13327, "AbortLevel" },
		{ 13328, "callbackVoid" },

		// maps/mp/gametypes/_class
		{ 12179, "getClassChoice" },
		{ 12180, "getWeaponChoice" },
		{ 14202, "logClassChoice" },
		{ 442, "cac_getCustomClassLoc" },
		{ 11477, "cac_getWeapon" },
		{ 11622, "cac_getWeaponAttachment" },
		{ 11623, "cac_getWeaponAttachmentTwo" },
		{ 11627, "cac_getWeaponBuff" },
		{ 14203, "cac_getWeaponCamo" },
		{ 14204, "cac_getWeaponReticle" },
		{ 11625, "cac_getPerk" },
		{ 11628, "cac_getKillstreak" },
		{ 11626, "cac_getDeathstreak" },
		{ 11624, "cac_getOffhand" },
		{ 14205, "recipe_getKillstreak" },
		{ 11630, "table_getWeapon" },
		{ 11631, "table_getWeaponAttachment" },
		{ 11636, "table_getWeaponBuff" },
		{ 14206, "table_getWeaponCamo" },
		{ 14207, "table_getWeaponReticle" },
		{ 11633, "table_getEquipment" },
		{ 11634, "table_getPerk" },
		{ 14208, "table_getTeamPerk" },
		{ 11632, "table_getOffhand" },
		{ 11637, "table_getKillstreak" },
		{ 11635, "table_getDeathstreak" },
		{ 11621, "getClassIndex" },
		{ 12660, "cloneLoadout" },
		{ 14209, "loadoutFakePerks" },
		{ 14210, "getLoadoutStreakTypeFromStreakType" },
		{ 12026, "giveLoadout" },
		{ 14218, "_detachAll" },
		{ 14023, "isPerkUpgraded" },
		{ 11681, "getPerkUpgrade" },
		{ 14219, "loadoutAllPerks" },
		{ 11461, "trackRiotShield" },
		{ 14224, "tryAttach" },
		{ 14225, "tryDetach" },
		{ 14226, "buildWeaponName" },
		{ 14229, "buildWeaponNameCamo" },
		{ 14230, "buildWeaponNameReticle" },
		{ 14231, "makeLettersToNumbers" },
		{ 14232, "setKillstreaks" },
		{ 14233, "replenishLoadout" },
		{ 14235, "onPlayerConnecting" },
		{ 14236, "fadeAway" },
		{ 12182, "setClass" },
		{ 14237, "getPerkForClass" },
		{ 14238, "classHasPerk" },
		{ 14198, "isValidPrimary" },
		{ 14199, "isValidSecondary" },
		{ 14239, "isValidAttachment" },
		{ 14146, "isAttachmentUnlocked" },
		{ 14240, "isValidWeaponBuff" },
		{ 14241, "isWeaponBuffUnlocked" },
		{ 14242, "isValidCamo" },
		{ 14243, "isValidReticle" },
		{ 14244, "isCamoUnlocked" },
		{ 14245, "isValidEquipment" },
		{ 14246, "isValidOffhand" },
		{ 14247, "isValidPerk1" },
		{ 14248, "isValidPerk2" },
		{ 14249, "isValidPerk3" },
		{ 14250, "isValidDeathStreak" },
		{ 14251, "isValidWeapon" },
		{ 14253, "isValidKillstreak" },

		// maps/mp/gametypes/_damage
		{ 0, "" },

		// maps/mp/gametypes/_damagefeedback
		{ 7448, "onPlayerConnect" },
		{ 6702, "updateDamageFeedback" },

		// maps/mp/gametypes/_deathicons
		{ 7448, "onPlayerConnect" },
		{ 12384, "updateDeathIconsEnabled" },
		{ 12385, "addDeathIcon" },
		{ 12387, "destroySlowly" },

		// maps/mp/gametypes/_dev
		{ 0, "" },

		// maps/mp/gametypes/_equipment
		{ 11312, "watchTrophyUsage" },
		{ 11321, "trophyUseListener" },
		{ 11325, "trophyPlayerSpawnWaiter" },
		{ 11326, "trophyDisconnectWaiter" },
		{ 11327, "trophyActive" },
		{ 11333, "projectileExplode" },
		{ 11336, "trophyDamage" },
		{ 11341, "trophyBreak" },

		// maps/mp/gametypes/_friendicons
		{ 0, "onPlayerConnect" },
		{ 0, "onPlayerSpawned" },
		{ 0, "onPlayerKilled" },
		{ 0, "showFriendIcon" },
		{ 0, "updateFriendIconSettings" },
		{ 0, "updateFriendIcons" },

		// maps/mp/gametypes/_gamelogic
		{ 0, "" },

		// maps/mp/gametypes/_gameobjects
		{ 0, "" },
	};*/