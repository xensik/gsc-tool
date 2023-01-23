// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdinc.hpp"
#include "types.hpp"

namespace xsk::gsc
{

auto engine_name(engine engine) -> std::string_view
{
    switch (engine)
    {
        case engine::iw5: return "IW5";
        case engine::iw6: return "IW6";
        case engine::iw7: return "IW7";
        case engine::iw8: return "IW8";
        case engine::iw9: return "IW9";
        case engine::s1: return "S1";
        case engine::s2: return "S2";
        case engine::s4: return "S4";
        case engine::h1: return "H1";
        case engine::h2: return "H2";
    }

    return "";
}

} // namespace xsk::gsc
