// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/compiler.hpp"
#include "xsk/arc/context.hpp"

namespace xsk::arc
{

compiler::compiler(context* ctx) : ctx_{ ctx }
{
}

auto compiler::compile(program const& data) -> assembly::ptr
{
    emit_program(data);
    return std::move(assembly_);
}

auto compiler::compile(std::string const& file, std::vector<u8>& data) -> assembly::ptr
{
    auto prog = ctx_->source().parse_program(file, data);
    return compile(*prog);
}

auto compiler::emit_program(program const& /*prog*/) -> void
{
    assembly_ = make_assembly();
}

} // namespace xsk::arc
