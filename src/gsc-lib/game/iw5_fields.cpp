#include "stdinc.hpp"

namespace iw5
{
	std::unordered_map <std::uint16_t, std::string> fields_map =
	{
		// level
		// codescripts/struct
		{ 2291, "struct" },

		{7781, "character_index_cache" },

		// maps/mp/gametypes/_callbacksetup
		{ 7207, "callbackPlayerDamage" },
		{ 11338, "iDFLAGS_PENETRATION" },
		{ 13323, "iDFLAGS_NO_TEAM_PROTECTION" },
		{ 13324, "iDFLAGS_PASSTHRU" },
		{ 12327, "callbackStartGameType" },
		{ 12328, "callbackPlayerConnect" },
		{ 12329, "callbackPlayerDisconnect" },
		{ 12330, "callbackPlayerKilled" },
		{ 12331, "callbackCodeEndGame" },
		{ 12332, "callbackPlayerLastStand" },
		{ 12333, "callbackPlayerMigrated" },
		{ 12735, "iDFLAGS_STUN" },
		{ 12736, "iDFLAGS_SHIELD_EXPLOSIVE_IMPACT" },
		{ 12737, "iDFLAGS_SHIELD_EXPLOSIVE_IMPACT_HUGE" },
		{ 12738, "iDFLAGS_SHIELD_EXPLOSIVE_SPLASH" },
		{ 12742, "iDFLAGS_NO_KNOCKBACK" },
		{ 12744, "iDFLAGS_NO_PROTECTION" },
		{ 13317, "gametypestarted" },
		{ 13318, "damageCallback" },
		{ 13319, "callbackHostMigration" },
		{ 13321, "iDFLAGS_RADIUS" },

		{ 11629, "classTableName" },
		{ 14200, "classMap" },
		{ 14200, "defaultClass" },

		// self
		{ 3791, "headModel" },
		{ 11620, "curClass" },
		{ 12181, "lastClass" },

	};



	auto GetFieldName(std::uint16_t id) -> std::string
	{
		if (fields_map.find(id) != fields_map.end())
			return fields_map[id];

		LOG_ERROR("Couldn't resolve field 0x%X!", id);
		return "";
	}
}