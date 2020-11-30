// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_CONTEXT_HPP_
#define _GSC_CONTEXT_HPP_

namespace gsc
{

struct context;
using context_ptr = std::unique_ptr<context>;

struct context
{
    bool is_last;
    bool is_loop;
    bool is_switch;
    std::string loc_end;
    std::string loc_break;
    std::string loc_continue;

    std::uint32_t local_vars_create_count;
    std::uint32_t local_vars_public_count;
    std::vector<bool> local_vars_init;
    std::vector<std::string> local_vars;
    
	context() : is_last(false), is_loop(false), is_switch(false), 
        local_vars_create_count(0), local_vars_public_count(0) { }

    auto transfer() -> std::unique_ptr<context>
    {
        auto child = std::make_unique<context>();

        this->transfer(child);

        return std::move(child);
    }

    void transfer(const context_ptr& child)
    {
        child->loc_break = this->loc_break;
        child->loc_continue = this->loc_continue;
        child->local_vars = this->local_vars;
        child->local_vars_init = this->local_vars_init;
        child->local_vars_create_count = this->local_vars_create_count;
        child->local_vars_public_count = this->local_vars_create_count;
    }
};

} // namespace gsc

#endif // _GSC_CONTEXT_HPP_
