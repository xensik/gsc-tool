// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

#include "xsk/stdinc.hpp"

namespace xsk
{

// Size-class free list for the small nodes the parser and compiler churn
// through (AST nodes, instructions). Freed blocks go back on a list instead of
// to the allocator, so a whole compile reuses the same memory and per-node
// malloc/free leaves the hot path.
//
// Types opt in by declaring the sized operator delete, see XSK_POOLED below.
// Only the sized form is declared on purpose: any deletion path that cannot
// supply the size fails to compile instead of silently mismatching.
//
// ponytail: chunks are never handed back to the OS. Live memory is bounded by
// peak concurrent nodes (one file's AST), not by total churn, so there is
// nothing to reclaim between files. Revisit if a caller ever holds many
// programs alive at once.
struct pool
{
    static constexpr usize granule = 16;    // also the max_align_t on every target here
    static constexpr usize classes = 24;    // covers nodes up to 384 B
    static constexpr usize chunk = 128 * 1024;

    struct link { link* next; };

    // POD and zero-initialized: constant-init, so no constructor runs before main
    static inline thread_local link* lists[classes]{};
    static inline thread_local u8* bump{};
    static inline thread_local usize left{};

    static auto acquire(usize size) -> void*
    {
        auto const cls = (size ? size - 1 : 0) / granule;

        if (cls >= classes)
            return ::operator new(size);

        if (auto* head = lists[cls]; head != nullptr)
        {
            lists[cls] = head->next;
            return head;
        }

        auto const bytes = (cls + 1) * granule;

        if (left < bytes)
        {
            bump = static_cast<u8*>(::operator new(chunk));
            left = chunk;
        }

        auto* mem = bump;
        bump += bytes;
        left -= bytes;

        return mem;
    }

    static auto release(void* mem, usize size) -> void
    {
        auto const cls = (size ? size - 1 : 0) / granule;

        if (cls >= classes)
        {
            ::operator delete(mem);
            return;
        }

        auto* head = static_cast<link*>(mem);
        head->next = lists[cls];
        lists[cls] = head;
    }
};

} // namespace xsk

#define XSK_POOLED                                                             \
    static auto operator new(usize size) -> void* { return pool::acquire(size); } \
    static auto operator delete(void* mem, usize size) -> void { pool::release(mem, size); }
