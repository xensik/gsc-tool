// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_UTILS_LOG_HPP_
#define _GSC_UTILS_LOG_HPP_

#ifdef DEBUG
#define GSC_LOG_DEBUG(__FMT__, ...) printf("[D]: " __FMT__ "\n", ## __VA_ARGS__);
#define GSC_LOG_INFO(__FMT__, ...)  printf("[I]: " __FMT__ "\n", ## __VA_ARGS__);
#define GSC_LOG_WARN(__FMT__, ...)  printf("[W]: " __FMT__ "\n", ## __VA_ARGS__);
#define GSC_LOG_ERROR(__FMT__, ...) printf("[E]: " __FMT__ "\n", ## __VA_ARGS__); exit(-1);
#else
#define GSC_LOG_DEBUG(__FMT__, ...)
#define GSC_LOG_INFO(__FMT__, ...)
#define GSC_LOG_WARN(__FMT__, ...)
#define GSC_LOG_ERROR(__FMT__, ...)  printf("[E]: " __FMT__ "\n", ## __VA_ARGS__); exit(-1);
#endif // DEBUG

#define GSC_ASM_ERROR(__FMT__, ...) printf("[ERROR] ASSEMBLER: " __FMT__ "\n", ## __VA_ARGS__); exit(-1);
#define GSC_DISASM_ERROR(__FMT__, ...) printf("[ERROR] DISASSEMBLER: " __FMT__ "\n", ## __VA_ARGS__); exit(-1);
#define GSC_COMP_ERROR(__FMT__, ...) printf("[ERROR] COMPILER: " __FMT__ "\n", ## __VA_ARGS__); exit(-1);
#define GSC_DECOMP_ERROR(__FMT__, ...) printf("[ERROR] DECOMPILER: " __FMT__ "\n", ## __VA_ARGS__); exit(-1);

namespace utils
{

class log
{
public:

};

} // namespace utils

#endif // _GSC_UTILS_LOG_HPP_
