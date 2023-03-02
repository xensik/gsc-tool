// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc::t6
{

class context : public arc::context
{
    t6::assembler assembler_;
    t6::disassembler disassembler_;
    t6::compiler compiler_;
    t6::decompiler decompiler_;

public:
    void init(build mode, read_cb_type callback);
    void cleanup();

    auto assembler() -> arc::assembler& { return assembler_; }
    auto disassembler() -> arc::disassembler& { return disassembler_; }
    auto compiler() -> arc::compiler& { return compiler_; }
    auto decompiler() -> arc::decompiler& { return decompiler_; }
};

} // namespace xsk::arc::t6
