// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

class context
{
public:
    using ptr = std::unique_ptr<context>;

    virtual ~context() = default;
    virtual void init(build mode, read_cb_type callback) = 0;
    virtual void cleanup() = 0;

    virtual auto assembler() -> assembler& = 0;
    virtual auto disassembler() -> disassembler& = 0;
    virtual auto compiler() -> compiler& = 0;
    virtual auto decompiler() -> decompiler& = 0;
};

} // namespace xsk::arc
