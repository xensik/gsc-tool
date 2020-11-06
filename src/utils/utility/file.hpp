// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_UTILS_FILE_HPP_
#define _GSC_UTILS_FILE_HPP_

namespace utils
{

class file
{
public:
	static auto read(const std::string& name) -> std::string;
	static void save(const std::string& name, const std::string& data);
	static auto length(FILE* fp) -> long;
};

} // namespace utils

#endif // _GSC_UTILS_FILE_HPP_
