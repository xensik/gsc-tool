// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_SH1_COMPILER_H_
#define _GSC_SH1_COMPILER_H_

namespace SH1
{

class compiler : public gsc::compiler
{
public:
    compiler();

	void compile(std::string& buffer);
	auto output() -> std::vector<std::shared_ptr<function>>;
};

} // namespace SH1

#endif // _GSC_SH1_COMPILER_H_
