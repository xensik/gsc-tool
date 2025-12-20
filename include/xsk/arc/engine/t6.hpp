// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc::t6
{

	constexpr usize code_count = 125;

#ifdef XSK_NO_COMPILED_HASH
	constexpr usize hash_count = 0;
#else // !XSK_NO_COMPILED_HASH
	constexpr usize hash_count = 3809;
#endif // XSK_NO_COMPILED_HASH

} // namespace xsk::arc::t6
