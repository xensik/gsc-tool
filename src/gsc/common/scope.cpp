// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/common/scope.hpp"

namespace xsk::gsc
{

scope::scope() : abort{ scope::abort_none }, create_count{ 0 }, public_count{ 0 }, is_last{ false }
{
}

auto scope::transfer_dec(scope::ptr const& child) -> void
{
    for (auto i = u32{ 0 }; i < vars.size(); i++)
    {
        child->vars.push_back(vars[i]);
    }

    child->public_count = static_cast<u32>(vars.size());
}

auto scope::transfer(scope::ptr const& child) -> void
{
    child->abort = scope::abort_none;
    child->loc_break = loc_break;
    child->loc_cont = loc_cont;

    for (auto i = u32{ 0 }; i < child->public_count || i < create_count; i++)
    {
        auto pos = child->find(i, vars[i].name);

        if (pos < 0)
        {
            child->public_count++;
            child->vars.insert(child->vars.begin() + i, vars[i]);
        }
        else
        {
            if (pos > static_cast<i32>(i))
                std::rotate(child->vars.rend() - pos - 1, child->vars.rend() - pos, child->vars.rend() - i);
            else
                std::rotate(child->vars.begin() + pos, child->vars.begin() + pos + 1, child->vars.begin() + i + 1);

            child->vars[i].init = vars[i].init;

            if (child->public_count <= i)
                child->public_count++;
        }
    }

    child->create_count = create_count;
}

auto scope::copy(scope::ptr const& child) -> void
{
    child->vars = vars;
    child->create_count = create_count;
    child->public_count = 0;
}

auto scope::append_dec(scope::ptr const& child) -> void
{
    for (auto i = vars.size(); i < child->public_count; i++)
    {
        vars.push_back(child->vars[i]);
    }
}

auto scope::append(std::vector<scope*> const& childs) -> void
{
    auto glob = true;

    if (childs.size() == 0) return;

    for (auto i = usize{ 0 }; i < childs[0]->vars.size(); i++)
    {
        glob = true;
        auto& var = childs[0]->vars[i];

        if (find(0, var.name) < 0)
        {
            for (auto j = usize{ 1 }; j < childs.size(); j++)
            {
                if (childs[j]->find(0, var.name) < 0)
                {
                    glob = false;
                }
            }

            if (glob)
            {
                vars.push_back(var);
            }
        }
    }
}

auto scope::merge(std::vector<scope*> const& childs) -> void
{
    if (childs.size() == 0) return;

    for (auto i = usize{ 0 }; i < childs.size(); i++)
    {
        auto child = childs[i];

        child->public_count = static_cast<u32>(vars.size());

        for (auto j = usize{ 0 }; j < vars.size(); j++)
        {
            auto pos = child->find(j, vars[j].name);

            if (pos < 0)
            {
                child->vars.insert(child->vars.begin() + j, vars[j]);
            }
            else if (pos > static_cast<i32>(j))
            {
                auto& v = child->vars;
                std::rotate(v.rend() - pos - 1, v.rend() - pos, v.rend() - j);
            }
        }
    }
}

auto scope::init(scope::ptr const& child) -> void
{
    create_count = child->create_count;

    for (auto i = u32{ 0 }; i < create_count; i++)
    {
        if (!vars[i].init)
            vars[i].init = true;
    }
}

auto scope::init(std::vector<scope*> const& childs) -> void
{
    if (childs.size() == 0) return;

    auto count = childs[0]->public_count;

    for (auto i = usize{ 1 }; i < childs.size(); i++)
    {
        if (childs[i]->public_count < count)
            count = childs[i]->public_count;
    }

    create_count = count;

    auto init = true;

    for (auto i = u32{ 0 }; i < count; i++)
    {
        init = true;
        if (!vars[i].init)
        {
            for (auto j = usize{ 0 }; j < childs.size(); j++)
            {
                if (!childs[j]->vars[i].init)
                    init = false;
            }

            if (init) vars[i].init = true;
        }
    }
}

auto scope::find(usize start, std::string const& name) -> i32
{
    for (auto i = start; i < vars.size(); i++)
    {
        if (vars[i].name == name)
            return static_cast<i32>(i);
    }

    return -1;
}

} // namespace xsk::gsc
