// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include <catch_amalgamated.hpp>

// MSVC does not pull main out of the catch2 static lib, so define it here.
int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
}
