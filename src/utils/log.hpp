// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _XSK_UTILS_XSK_H_
#define _XSK_UTILS_XSK_H_

#ifdef DEBUG

#define LOG_DEBUG(__FMT__, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); \
								printf("[D][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__); \
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

#define LOG_ERROR(__FMT__, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); \
								printf("[E][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__); \
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

#define LOG_WARN(__FMT__, ...) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); \
								printf("[W][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__); \
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

#define LOG_INFO(__FMT__, ...) printf("[I][" __FUNCTION__ "]: " __FMT__ "\n", __VA_ARGS__);

#else

#define LOG_DEBUG(__FMT__, ...)

#define LOG_ERROR(__FMT__, ...) printf("[E]: " __FMT__ "\n", __VA_ARGS__);

#define LOG_WARN(__FMT__, ...)// printf("[W]: " __FMT__ "\n", __VA_ARGS__);

#define LOG_INFO(__FMT__, ...)// printf("[I]: " __FMT__ "\n", __VA_ARGS__);

#endif // DEBUG

namespace utils
{

class log
{
public:

};

} // namespace utils

#endif // _XSK_UTILS_STRING_H_