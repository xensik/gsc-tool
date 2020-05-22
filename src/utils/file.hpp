#pragma once

namespace utils::file
{
	std::string read(std::string file);
	void save(std::string file, std::vector<std::uint8_t> buffer);
}
