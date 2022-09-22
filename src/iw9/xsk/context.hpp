// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::iw9
{

class context : public gsc::context
{
    iw9::disassembler disassembler_;

public:
    void init(build mode, read_cb_type callback);
    void cleanup();

    auto assembler() -> gsc::assembler& { throw std::runtime_error("not impl"); }
    auto disassembler() -> gsc::disassembler& { return disassembler_; }
    auto compiler() -> gsc::compiler& { throw std::runtime_error("not impl"); }
    auto decompiler() -> gsc::decompiler& { throw std::runtime_error("not impl"); }
};

} // namespace xsk::gsc::iw9
