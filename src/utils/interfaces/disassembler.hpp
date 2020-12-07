// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_DISASSEMBLER_HPP_
#define _GSC_DISASSEMBLER_HPP_

namespace gsc
{

class disassembler
{
public:
    virtual auto output() -> std::vector<gsc::function_ptr> = 0;
    virtual auto output_data() -> std::vector<std::uint8_t> = 0;
    virtual void disassemble(std::vector<std::uint8_t>& script, std::vector<std::uint8_t>& stack) = 0;
};

} // namespace gsc

#endif // _GSC_DISASSEMBLER_HPP_
