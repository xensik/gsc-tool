// Copyright 2020 xensik. All Rights Reserved.

#ifndef XSK_UTILS_FILE_H_
#define XSK_UTILS_FILE_H_

namespace xsk
{

class file
{
public:
	static auto read(std::string file)->std::string;
	static void save(std::string file, std::vector<std::uint8_t> buffer);
	static auto length(FILE* fp) -> long;
};

} // namespace utils

#endif // XSK_UTILS_FILE_H_