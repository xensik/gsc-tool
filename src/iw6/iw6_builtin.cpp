// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"

namespace iw6
{

std::unordered_map<std::string, std::uint16_t> builtin_function_map
{

};

std::unordered_map<std::string, std::uint16_t> builtin_method_map
{

};

auto get_builtin_func_id(const std::string& name) -> std::uint16_t
{
	if (builtin_function_map.find(name) != builtin_function_map.end())
	{
		return builtin_function_map[name];
	}

	LOG_ERROR("Couldn't resolve builtin function id for name '%s'!", name.c_str());
	return 0xFFFF;
}

auto get_builtin_func_name(std::uint16_t id) -> std::string
{
	for (auto& field : builtin_function_map)
	{
		if (field.second == id)
		{
			return field.first;
		}
	}

	LOG_ERROR("Couldn't resolve builtin function name for id '%i'!", id);
	return "";
}

auto get_builtin_method_id(const std::string& name) -> std::uint16_t
{
	if (builtin_method_map.find(name) != builtin_method_map.end())
	{
		return builtin_method_map[name];
	}

	LOG_ERROR("Couldn't resolve builtin method id for name '%s'!", name.c_str());
	return 0xFFFF;
}

auto get_builtin_method_name(std::uint16_t id) -> std::string
{
	for (auto& field : builtin_method_map)
	{
		if (field.second == id)
		{
			return field.first;
		}
	}
	LOG_ERROR("Couldn't resolve builtin method name for id '%i'!", id);
	return "";
}

} // namespace iw6
