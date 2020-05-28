#pragma once

namespace utils
{
	class file
	{
	public:
		static auto read(std::string file)->std::string;
		static void save(std::string file, std::vector<std::uint8_t> buffer);
	};
}
