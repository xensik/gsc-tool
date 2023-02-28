// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#ifdef _WINDOWS_
#undef ERROR
#undef IN
#undef TRUE
#undef FALSE
#undef far
#endif

#include "../src/stdinc.hpp"

#ifdef XSK_GSC_IW5_PC
#include "../src/iw5/iw5_pc.hpp"
#endif

#ifdef XSK_GSC_IW6_PC
#include "../src/iw6/iw6_pc.hpp"
#endif

#ifdef XSK_GSC_S1_PC
#include "../src/s1/s1_pc.hpp"
#endif

#ifdef XSK_GSC_T6_PC
#include "../src/t6/t6.hpp"
#endif
