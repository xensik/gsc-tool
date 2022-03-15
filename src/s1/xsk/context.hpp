// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::s1
{

class context : public gsc::context
{
    s1::assembler assembler_;
    s1::disassembler disassembler_;
    s1::compiler compiler_;
    s1::decompiler decompiler_;

public:
    void init(build mode, read_cb_type callback);
    void cleanup();

    auto assembler() -> gsc::assembler& { return assembler_; }
    auto disassembler() -> gsc::disassembler& { return disassembler_; }
    auto compiler() -> gsc::compiler& { return compiler_; }
    auto decompiler() -> gsc::decompiler& { return decompiler_; }
};

} // namespace xsk::gsc::s1
