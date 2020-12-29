// Copyright 2021 xensik. All rights reserved.
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
    static auto read(const std::string& file) -> std::vector<std::uint8_t>;
    static auto read_text(const std::string& file) -> std::string;
    static void save(const std::string& file, const std::vector<std::uint8_t>& data);
    static auto length(FILE* fp) -> long;
};

} // namespace utils

#endif // _GSC_UTILS_FILE_HPP_
