// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_S1_COMPILER_HPP_
#define _GSC_S1_COMPILER_HPP_

namespace S1
{

class compiler : public gsc::compiler
{
public:
	auto output() -> std::vector<gsc::function_ptr>;
	void compile(std::vector<std::uint8_t>& data);
};

} // namespace S1

#endif // _GSC_S1_COMPILER_HPP_
