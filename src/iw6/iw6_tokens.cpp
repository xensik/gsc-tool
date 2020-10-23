// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"

namespace iw6
{

std::unordered_map <std::string, std::uint16_t> token_map =
{

};

auto get_token_id(const std::string& name) -> std::uint16_t
{
	const auto itr = token_map.find(name);

	if(itr != token_map.end())
	{
		return itr->second;
	}

	LOG_WARN("Couldn't resolve token id for name '%s'!", name.c_str());
	return 0;
}

auto get_token_name(std::uint16_t id) -> std::string
{
	for (auto& func : token_map)
	{
		if (func.second == id)
		{
			return func.first;
		}
	}

	LOG_WARN("Couldn't resolve token name for id '%i'!", id);
	return utils::string::va("id#%i", id);
}

} // namespace iw6
