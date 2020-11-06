// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_IW5_DECOMPILER_HPP_
#define _GSC_IW5_DECOMPILER_HPP_

namespace IW5
{

class decompiler : public gsc::decompiler
{
public:
	auto output() -> std::string;
	void decompile(std::vector<gsc::function_ptr>& functions);
};

} // namespace IW5

#endif // _GSC_IW5_DECOMPILER_HPP_
