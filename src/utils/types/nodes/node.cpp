// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "utils.hpp"

std::uint32_t node_statement_block::indent;

std::string indented(std::uint32_t indent)
{
    static char buff[100];
    snprintf(buff, sizeof(buff), "%*s", indent, "");
    return std::string(buff);
}