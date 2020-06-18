// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _XSK_UTILS_FILE_H_
#define _XSK_UTILS_FILE_H_

namespace xsk
{

class file
{
public:
	static auto read(std::string file)->std::string;
	static void save(std::string file, std::vector<std::uint8_t> buffer);
	static auto length(FILE* fp) -> long;
};

} // namespace xsk

#endif // _XSK_UTILS_FILE_H_