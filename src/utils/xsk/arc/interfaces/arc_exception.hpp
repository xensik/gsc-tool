// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::gsc::arc
{

class error : public std::runtime_error
{
public:
    error(const std::string& what) : std::runtime_error("[gsc]: "s + what) { }
};

class asm_error : public std::runtime_error
{
public:
    asm_error(const std::string& what) : std::runtime_error("[gsc assembler]: "s + what) { }
};

class disasm_error : public std::runtime_error
{
public:
    disasm_error(const std::string& what) : std::runtime_error("[gsc disassembler]: "s + what) { }
};

class comp_error : public std::runtime_error
{
public:
    comp_error(gsc::location loc, const std::string& what)
        : std::runtime_error("[gsc compiler]:" + 
            *loc.begin.filename + ":" + 
            std::to_string(loc.begin.line) + ":" + 
            std::to_string(loc.begin.column) + ": " + what) { }
};

class decomp_error : public std::runtime_error
{
public:
    decomp_error(const std::string& what) : std::runtime_error("[gsc decompiler]: "s + what) { }
};

} // namespace xsk::gsc::arc
