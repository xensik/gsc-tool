// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_COMPILER_HPP_
#define _GSC_COMPILER_HPP_

namespace gsc
{

class compiler
{
public:
	virtual auto output() -> std::vector<gsc::function_ptr> = 0;
	virtual void compile(std::vector<std::uint8_t>& data) = 0;
};

} // namespace gsc

#endif // _GSC_COMPILER_HPP_
