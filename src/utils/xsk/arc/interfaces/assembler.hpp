// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

class assembler
{
public:
    using ptr = std::unique_ptr<assembler>;

    virtual ~assembler() = default;
    virtual auto output() -> std::vector<std::uint8_t> = 0;
    virtual void assemble(const std::string& file, std::vector<std::uint8_t>& data) = 0;
    virtual void assemble(const std::string& file, assembly::ptr& data) = 0;
};

} // namespace xsk::arc
