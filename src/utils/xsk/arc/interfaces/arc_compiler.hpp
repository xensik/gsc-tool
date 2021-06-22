// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::arc
{

class compiler
{
public:
    virtual auto output() -> std::vector<gsc::function_ptr> = 0;
    virtual void compile(const std::string& file, std::vector<std::uint8_t>& data) = 0;
    virtual void set_readf_callback(std::function<std::vector<std::uint8_t>(const std::string&)> func) = 0;
};

} // namespace xsk::gsc::arc
