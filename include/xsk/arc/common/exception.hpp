// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

struct error : public std::runtime_error
{
public:
    explicit error(std::string const& what);
};

struct asm_error : public std::runtime_error
{
public:
    explicit asm_error(std::string const& what);
};

struct disasm_error : public std::runtime_error
{
public:
    explicit disasm_error(std::string const& what);
};

struct ppr_error : public std::runtime_error
{
public:
    ppr_error(location const& loc, std::string const& what);
};

struct comp_error : public std::runtime_error
{
public:
    comp_error(location const& loc, std::string const& what);
};

struct decomp_error : public std::runtime_error
{
public:
    explicit decomp_error(std::string const& what);
};

} // namespace xsk::arc
