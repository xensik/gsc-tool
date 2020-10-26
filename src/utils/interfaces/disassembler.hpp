// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_DISASSEMBLER_H_
#define _GSC_DISASSEMBLER_H_

namespace gsc
{

class disassembler
{
public:
	virtual void disassemble(std::shared_ptr<utils::byte_buffer> script, std::shared_ptr<utils::byte_buffer> stack) = 0;
	virtual auto output() -> std::vector<std::shared_ptr<function>> = 0;
	virtual auto output_buffer() -> std::vector<std::uint8_t> = 0;
};

} // namespace gsc

#endif // _GSC_DISASSEMBLER_H_
