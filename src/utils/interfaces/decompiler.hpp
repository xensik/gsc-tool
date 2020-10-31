// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_DECOMPILER_H_
#define _GSC_DECOMPILER_H_

namespace gsc
{
	
class decompiler
{
public:
	virtual void decompile(std::vector<std::shared_ptr<function>>& functions) = 0;
	virtual auto output() -> std::string = 0;
};

} // namespace gsc

#endif // _GSC_DECOMPILER_H_
