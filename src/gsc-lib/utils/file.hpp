#pragma once

namespace utils::file
{
	auto read(std::string file) -> std::string;
	void save(std::string file, std::vector<std::uint8_t> buffer);
}
