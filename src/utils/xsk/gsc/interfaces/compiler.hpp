// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc
{

class compiler
{
public:
    using ptr = std::unique_ptr<compiler>;

    virtual ~compiler() = default;
    virtual auto output() -> std::vector<gsc::function::ptr> = 0;
    virtual void compile(const std::string& file, std::vector<std::uint8_t>& data) = 0;
};

} // namespace xsk::gsc
