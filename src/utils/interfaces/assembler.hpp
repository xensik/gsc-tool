// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_ASSEMBLER_HPP_
#define _GSC_ASSEMBLER_HPP_

namespace gsc
{

class assembler
{
public:
	virtual auto output_script() -> std::string = 0;
	virtual auto output_stack() -> std::string = 0;
	virtual void assemble(std::string& data) = 0;
	virtual void assemble(std::vector<gsc::function_ptr>& functions) = 0;
};

} // namespace gsc

#endif // _GSC_ASSEMBLER_HPP_
