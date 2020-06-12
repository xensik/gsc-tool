// Copyright 2020 xensik. All Rights Reserved.

#include "xsk_gsc.hpp"

namespace xsk
{

auto file::read(std::string file) -> std::string
{
	std::string buffer;

	std::ifstream stream(file, std::ios::binary);
	if (stream.good())
	{
		if (!stream.is_open()) return buffer;

		stream.seekg(0, std::ios::end);
		std::streamsize size = stream.tellg();
		stream.seekg(0, std::ios::beg);

		if (size > -1)
		{
			buffer.clear();
			buffer.resize(static_cast<uint32_t>(size));

			stream.read(const_cast<char*>(buffer.data()), size);
		}

		stream.close();
	}

	return buffer;
}

void file::save(std::string name, std::vector<std::uint8_t> data)
{
	FILE* fp = fopen(name.data(), "wb");
	fwrite(data.data(), 1, data.size(), fp);
	fclose(fp);
}

auto file::length(FILE* fp) -> long
{
	long i = ftell(fp);
	fseek(fp, 0, SEEK_END);
	long ret = ftell(fp);
	fseek(fp, i, SEEK_SET);
	return ret;
}

} // namespace utils