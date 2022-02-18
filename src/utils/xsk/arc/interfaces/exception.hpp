// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

class error : public std::runtime_error
{
public:
    error(const std::string& what)
        : std::runtime_error("[ERROR]: "s + what) {}
};

class asm_error : public std::runtime_error
{
public:
    asm_error(const std::string& what)
        : std::runtime_error("[ERROR]:assembler: "s + what) {}
};

class disasm_error : public std::runtime_error
{
public:
    disasm_error(const std::string& what)
        : std::runtime_error("[ERROR]:disassembler: "s + what) {}
};

class comp_error : public std::runtime_error
{
public:
    comp_error(const location& loc, const std::string& what)
        : std::runtime_error("[ERROR]:compiler:" + loc.print() + ": " + what) {}
};

class decomp_error : public std::runtime_error
{
public:
    decomp_error(const std::string& what)
        : std::runtime_error("[ERROR]:decompiler: "s + what) {}
};

} // namespace xsk::arc
