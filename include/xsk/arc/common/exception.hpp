// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

class error : public std::runtime_error
{
public:
    error(std::string const& what);
};

class asm_error : public std::runtime_error
{
public:
    asm_error(std::string const& what);
};

class disasm_error : public std::runtime_error
{
public:
    disasm_error(std::string const& what);
};

class ppr_error : public std::runtime_error
{
public:
    ppr_error(location const& loc, std::string const& what);
};

class comp_error : public std::runtime_error
{
public:
    comp_error(location const& loc, std::string const& what);
};

class decomp_error : public std::runtime_error
{
public:
    decomp_error(std::string const& what);
};

} // namespace xsk::arc
