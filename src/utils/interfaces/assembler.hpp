// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_ASSEMBLER_H_
#define _GSC_ASSEMBLER_H_

namespace gsc
{

class assembler
{
public:

	virtual void assemble(std::string& buffer) = 0;
	virtual void assemble(std::vector<std::shared_ptr<function>>& functions) = 0;
	virtual auto output_script() -> std::vector<std::uint8_t> = 0;
	virtual auto output_stack() -> std::vector<std::uint8_t> = 0;
};

} // namespace gsc

#endif // _GSC_ASSEMBLER_H_
