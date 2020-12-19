// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_S1_DECOMPILER_HPP_
#define _GSC_S1_DECOMPILER_HPP_

namespace S1
{

class decompiler : public gsc::decompiler
{
public:
	auto output() -> std::vector<std::uint8_t>;
	void decompile(std::vector<gsc::function_ptr>& functions);
};

} // namespace S1

#endif // _GSC_S1_DECOMPILER_HPP_
