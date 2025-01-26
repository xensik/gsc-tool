// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

struct directive
{
    enum kind : u8 { IF, IFDEF, IFNDEF, ELIF, ELIFDEF, ELIFNDEF, ELSE, ENDIF, DEFINE, UNDEF, PRAGMA, WARNING, ERROR, LINE, INCLUDE, INLINE, INSERT, USINGTREE };

    kind type;
    bool skip;
    bool exec;
};

} // namespace xsk::arc
