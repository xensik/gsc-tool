// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_INSTRUCTION_H_
#define _GSC_INSTRUCTION_H_

/*namespace gsc
{*/

struct instruction
{
	std::uint32_t index;
	std::uint32_t size;
	std::uint8_t opcode;
	std::vector<std::string> data;
	std::shared_ptr<function> parent;

	instruction() : index(0), opcode(0xFF), size(0) { }
};

/*} // namespace gsc*/

#endif // _GSC_INSTRUCTION_H_
