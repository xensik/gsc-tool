// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_BLOCK_HPP_
#define _GSC_BLOCK_HPP_

namespace gsc
{

struct block
{
    bool is_last;
    bool allow_break;
    bool allow_continue;
    bool allow_case;
    bool allow_default;
    std::uint32_t local_vars;
    std::string loc_end;
    std::string loc_break;
    std::string loc_continue;

	block() : is_last(false), allow_break(false), allow_continue(false), allow_case(false), allow_default(false) { }

    void set_loop() { allow_break = true; allow_continue = true; };
    void set_switch() { allow_break = true; allow_case = true; allow_default = true; };
};

} // namespace gsc

#endif // _GSC_BLOCK_HPP_
