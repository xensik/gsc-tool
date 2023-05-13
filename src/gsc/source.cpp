// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/gsc/source.hpp"
#include "xsk/gsc/context.hpp"
#include "xsk/gsc/preprocessor.hpp"
#include "xsk/gsc/parser.hpp"

namespace xsk::gsc
{

source::source(context* ctx) : ctx_{ ctx }, indent_{ 0 }
{
}

auto source::parse_assembly(buffer const& data) -> assembly::ptr
{
    return parse_assembly(data.data, data.size);
}

auto source::parse_assembly(std::vector<u8> const& data) -> assembly::ptr
{
    return parse_assembly(data.data(), data.size());
}

auto source::parse_assembly(u8 const* data, usize size) -> assembly::ptr
{
    auto buffer = std::vector<u8>{};
    buffer.resize(size);
    std::memcpy(buffer.data(), data, buffer.size());

    auto lines = utils::string::clean_buffer_lines(buffer);
    auto assembly = assembly::make();
    auto func = function::ptr{ nullptr };
    u32 index = 1;
    u16 switchnum = 0;

    for (auto& line : lines)
    {
        if (line == "" || line.substr(0, 2) == "//")
        {
            continue;
        }
        else if (line.substr(0, 4) == "sub:")
        {
            func = function::make();
            func->index = index;
            func->name = line.substr(4);
            func->id = ctx_->token_id(func->name);
        }
        else if (line.substr(0, 4) == "end:")
        {
            if (func != nullptr)
            {
                func->size = index - func->index;
                assembly->functions.push_back(std::move(func));
            }
        }
        else if (line.substr(0, 4) == "loc_")
        {
            func->labels[index] = line;
        }
        else
        {
            auto opdata = utils::string::parse_code(line);

            if (switchnum)
            {
                if (opdata[0] == "case" || opdata[0] == "default")
                {
                    for (auto& entry : opdata)
                    {
                        func->instructions.back()->data.push_back(entry);
                    }
                    switchnum--;
                    continue;
                }

                throw asm_error("invalid instruction inside endswitch \""s + line + "\"");
            }
            else
            {
                auto inst = instruction::make();
                inst->index = index;
                inst->opcode = ctx_->opcode_enum(opdata[0]);
                inst->size = ctx_->opcode_size(inst->opcode);
                opdata.erase(opdata.begin());
                inst->data = std::move(opdata);

                switch (inst->opcode)
                {
                    case opcode::OP_GetVector:
                    {
                        if (ctx_->endian() == endian::big)
                        {
                            auto base = inst->index + 1;
                            auto algn = (base + 3) & ~3;
                            inst->size += (algn - base);
                        }
                        break;
                    }
                    case opcode::OP_GetLocalFunction:
                    case opcode::OP_ScriptLocalFunctionCall:
                    case opcode::OP_ScriptLocalFunctionCall2:
                    case opcode::OP_ScriptLocalMethodCall:
                    case opcode::OP_ScriptLocalThreadCall:
                    case opcode::OP_ScriptLocalChildThreadCall:
                    case opcode::OP_ScriptLocalMethodThreadCall:
                    case opcode::OP_ScriptLocalMethodChildThreadCall:
                        inst->data[0] = inst->data[0].substr(4);
                        break;
                    case opcode::OP_endswitch:
                        switchnum = static_cast<std::uint16_t>(std::stoi(inst->data[0]));
                        inst->size += 7 * switchnum;
                        break;
                    default:
                        break;
                }

                index += inst->size;
                func->instructions.push_back(std::move(inst));
            }
        }
    }

    return assembly;
}

auto source::parse_program(std::string const& name, buffer const& data) -> program::ptr
{
    return parse_program(name, data.data, data.size);
}

auto source::parse_program(std::string const& name, std::vector<u8> const& data) -> program::ptr
{
    return parse_program(name, data.data(), data.size());
}

auto source::parse_program(std::string const& name, u8 const* data, usize size) -> program::ptr
{
    auto res = program::ptr{ nullptr };
    auto ppr = preprocessor{ ctx_, name, reinterpret_cast<char const*>(data), size };
    auto psr = parser{ ctx_, ppr, res, 0 };

    if (!psr.parse() && res != nullptr)
        return res;

    throw error{ fmt::format("an unknown error ocurred while parsing script {}", name) };   
}

auto source::dump(assembly const& data) -> std::vector<u8>
{
    buf_ = std::vector<u8>{};
    buf_.reserve(0x10000);

    fmt::format_to(std::back_inserter(buf_), "// {} GSC ASSEMBLY\n", ctx_->engine_name());
    fmt::format_to(std::back_inserter(buf_), "// Generated by https://github.com/xensik/gsc-tool\n");

    dump_assembly(data);

    return std::move(buf_);
}

auto source::dump(program const& data) -> std::vector<u8>
{
    buf_ = std::vector<u8>{};
    buf_.reserve(0x10000);

    fmt::format_to(std::back_inserter(buf_), "// {} GSC SOURCE\n", ctx_->engine_name());
    fmt::format_to(std::back_inserter(buf_), "// Generated by https://github.com/xensik/gsc-tool\n");
    
    dump_program(data);

    return std::move(buf_);
}

auto source::dump_assembly(assembly const& data) -> void
{
    for (auto const& func : data.functions)
    {
        dump_function(*func);
    }
}

auto source::dump_function(function const& func) -> void
{
    fmt::format_to(std::back_inserter(buf_), "\nsub:{}\n", func.name);

    for (auto const& inst : func.instructions)
    {
        auto const itr = func.labels.find(inst->index);

        if (itr != func.labels.end())
        {
            fmt::format_to(std::back_inserter(buf_), "\t{}\n", itr->second);
        }

        dump_instruction(*inst);
    }

    fmt::format_to(std::back_inserter(buf_), "end:{}\n", func.name);
}

auto source::dump_instruction(instruction const& inst) -> void
{
    fmt::format_to(std::back_inserter(buf_), "\t\t{}", ctx_->opcode_name(inst.opcode));

    switch (inst.opcode)
    {
        case opcode::OP_GetString:
        case opcode::OP_GetIString:
        case opcode::OP_GetAnimTree:
            fmt::format_to(std::back_inserter(buf_), " \"{}\"", inst.data[0]);
            break;
        case opcode::OP_GetAnimation:
            fmt::format_to(std::back_inserter(buf_), " \"{}\" \"{}\"", inst.data[0], inst.data[1]);
            break;
        case opcode::OP_GetLocalFunction:
        case opcode::OP_ScriptLocalFunctionCall:
        case opcode::OP_ScriptLocalFunctionCall2:
        case opcode::OP_ScriptLocalMethodCall:
            fmt::format_to(std::back_inserter(buf_), " {}", inst.data[0]);
            break;
        case opcode::OP_ScriptLocalThreadCall:
        case opcode::OP_ScriptLocalChildThreadCall:
        case opcode::OP_ScriptLocalMethodThreadCall:
        case opcode::OP_ScriptLocalMethodChildThreadCall:
            fmt::format_to(std::back_inserter(buf_), " {} {}\n", inst.data[0], inst.data[1]);
            break;
        case opcode::OP_endswitch:
        {
            auto count = static_cast<u32>(std::stoul(inst.data[0]));
            auto type = static_cast<switch_type>(std::stoul(inst.data.back()));
            auto index = 1;

            fmt::format_to(std::back_inserter(buf_), " {}\n", count);

            for (auto i = 0u; i < count; i++)
            {
                if (inst.data[index] == "case")
                {
                    if (ctx_->engine() == engine::iw9)
                    {
                        type = static_cast<switch_type>(std::stoul(inst.data[index + 1]));
                        auto data = (type == switch_type::integer) ? fmt::format("{}", inst.data[index + 2]) : fmt::format("\"{}\"", inst.data[index + 2]); 
                        fmt::format_to(std::back_inserter(buf_), "\t\t\t{} {} {}", inst.data[index], data, inst.data[index + 3]);
                        index += 4;
                    }
                    else
                    {
                        auto data = (type == switch_type::integer) ? fmt::format("{}", inst.data[index + 1]) : fmt::format("\"{}\"", inst.data[index + 1]);
                        fmt::format_to(std::back_inserter(buf_), "\t\t\t{} {} {}", inst.data[index], data, inst.data[index + 2]);
                        index += 3;
                    }     
                }
                else if (inst.data[index] == "default")
                {
                    fmt::format_to(std::back_inserter(buf_), "\t\t\t{} {}", inst.data[index], inst.data[index + 1]);
                    index += 2;
                }
                if (i != count - 1)
                {
                    fmt::format_to(std::back_inserter(buf_), "\n");
                }
            }
            break;
        }
        default:
            for (auto const& entry : inst.data)
            {
                fmt::format_to(std::back_inserter(buf_), " {}", entry);
            }
            break;
    }

    fmt::format_to(std::back_inserter(buf_), "\n");
}

auto source::dump_program(program const& data) -> void
{
    for (auto const& inc : data.includes)
    {
        dump_include(*inc);
    }

    for (auto const& dec : data.declarations)
    {
        fmt::format_to(std::back_inserter(buf_), "\n");
        dump_decl(*dec);
    }
}

auto source::dump_include(include const& inc) -> void
{
    fmt::format_to(std::back_inserter(buf_), "#include ");
    dump_expr_path(*inc.path);
    fmt::format_to(std::back_inserter(buf_), ";\n");
}

auto source::dump_decl(decl const& dec) -> void
{
    switch (dec.kind())
    {
        case node::decl_dev_begin:
            dump_decl_dev_begin(dec.as<decl_dev_begin>());
            break;
        case node::decl_dev_end:
            dump_decl_dev_end(dec.as<decl_dev_end>());
            break;
        case node::decl_usingtree:
            dump_decl_usingtree(dec.as<decl_usingtree>());
            break;
        case node::decl_constant:
            dump_decl_constant(dec.as<decl_constant>());
            break;
        case node::decl_function:
            dump_decl_function(dec.as<decl_function>());
            break;
        case node::decl_empty:
            dump_decl_empty(dec.as<decl_empty>());
            break;
        default:
            break;
    }
}

auto source::dump_decl_dev_begin(decl_dev_begin const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "/#");
}

auto source::dump_decl_dev_end(decl_dev_end const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "#/");
}

auto source::dump_decl_usingtree(decl_usingtree const& dec) -> void
{
    fmt::format_to(std::back_inserter(buf_), "#using_animtree(");
    dump_expr_string(*dec.name);
    fmt::format_to(std::back_inserter(buf_), ");\n");
}

auto source::dump_decl_constant(decl_constant const& dec) -> void
{
    dump_expr_identifier(*dec.name);
    fmt::format_to(std::back_inserter(buf_), " = ");
    dump_expr(*dec.value);
    fmt::format_to(std::back_inserter(buf_), ";\n");
}

auto source::dump_decl_function(decl_function const& dec) -> void
{
    indent_ = 0;
    dump_expr_identifier(*dec.name);
    fmt::format_to(std::back_inserter(buf_), "(");
    dump_expr_parameters(*dec.params);
    fmt::format_to(std::back_inserter(buf_), ")\n");
    dump_stmt_comp(*dec.body);
    fmt::format_to(std::back_inserter(buf_), "\n");
}

auto source::dump_decl_empty(decl_empty const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), ";");
}

auto source::dump_stmt(stmt const& stm) -> void
{
    switch (stm.kind())
    {
        case node::stmt_list:
            dump_stmt_list(stm.as<stmt_list>());
            break;
        case node::stmt_comp:
            dump_stmt_comp(stm.as<stmt_comp>());
            break;
        case node::stmt_dev:
            dump_stmt_dev(stm.as<stmt_dev>());
            break;
        case node::stmt_expr:
            dump_stmt_expr(stm.as<stmt_expr>());
            break;
        case node::stmt_endon:
            dump_stmt_endon(stm.as<stmt_endon>());
            break;
        case node::stmt_notify:
            dump_stmt_notify(stm.as<stmt_notify>());
            break;
        case node::stmt_wait:
            dump_stmt_wait(stm.as<stmt_wait>());
            break;
        case node::stmt_waittill:
            dump_stmt_waittill(stm.as<stmt_waittill>());
            break;
        case node::stmt_waittillmatch:
            dump_stmt_waittillmatch(stm.as<stmt_waittillmatch>());
            break;
        case node::stmt_waittillframeend:
            dump_stmt_waittillframeend(stm.as<stmt_waittillframeend>());
            break;
        case node::stmt_waitframe:
            dump_stmt_waitframe(stm.as<stmt_waitframe>());
            break;
        case node::stmt_if:
            dump_stmt_if(stm.as<stmt_if>());
            break;
        case node::stmt_ifelse:
            dump_stmt_ifelse(stm.as<stmt_ifelse>());
            break;
        case node::stmt_while:
            dump_stmt_while(stm.as<stmt_while>());
            break;
        case node::stmt_dowhile:
            dump_stmt_dowhile(stm.as<stmt_dowhile>());
            break;
        case node::stmt_for:
            dump_stmt_for(stm.as<stmt_for>());
            break;
        case node::stmt_foreach:
            dump_stmt_foreach(stm.as<stmt_foreach>());
            break;
        case node::stmt_switch:
            dump_stmt_switch(stm.as<stmt_switch>());
            break;
        case node::stmt_case:
            dump_stmt_case(stm.as<stmt_case>());
            break;
        case node::stmt_default:
            dump_stmt_default(stm.as<stmt_default>());
            break;
        case node::stmt_break:
            dump_stmt_break(stm.as<stmt_break>());
            break;
        case node::stmt_continue:
            dump_stmt_continue(stm.as<stmt_continue>());
            break;
        case node::stmt_return:
            dump_stmt_return(stm.as<stmt_return>());
            break;
        case node::stmt_breakpoint:
            dump_stmt_breakpoint(stm.as<stmt_breakpoint>());
            break;
        case node::stmt_prof_begin:
            dump_stmt_prof_begin(stm.as<stmt_prof_begin>());
            break;
        case node::stmt_prof_end:
            dump_stmt_prof_end(stm.as<stmt_prof_end>());
            break;
        case node::stmt_assert:
            dump_stmt_assert(stm.as<stmt_assert>());
            break;
        case node::stmt_assertex:
            dump_stmt_assertex(stm.as<stmt_assertex>());
            break;
        case node::stmt_assertmsg:
            dump_stmt_assertmsg(stm.as<stmt_assertmsg>());
            break;
        case node::stmt_create:
            dump_stmt_create(stm.as<stmt_create>());
            break;
        case node::stmt_remove:
            dump_stmt_remove(stm.as<stmt_remove>());
            break;
        case node::stmt_clear:
            dump_stmt_clear(stm.as<stmt_clear>());
            break;
        case node::stmt_jmp:
            dump_stmt_jmp(stm.as<stmt_jmp>());
            break;
        case node::stmt_jmp_back:
            dump_stmt_jmp_back(stm.as<stmt_jmp_back>());
            break;
        case node::stmt_jmp_cond:
            dump_stmt_jmp_cond(stm.as<stmt_jmp_cond>());
            break;
        case node::stmt_jmp_switch:
            dump_stmt_jmp_switch(stm.as<stmt_jmp_switch>());
            break;
        case node::stmt_jmp_endswitch:
            dump_stmt_jmp_endswitch(stm.as<stmt_jmp_endswitch>());
            break;
        default:
            break;
    }
}

auto source::dump_stmt_empty(stmt_empty const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), ";");
}

auto source::dump_stmt_list(stmt_list const& stm) -> void
{
    auto last_special = false;
    indent_ += 4;

    for (auto const& entry : stm.list)
    {
        if ((&entry != &stm.list.front() && entry->is_special_stmt()) || last_special)
            fmt::format_to(std::back_inserter(buf_), "\n");

        if (entry->is<stmt_dev>())
        {
            dump_stmt(*entry);
        }
        else
        {
            fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
            dump_stmt(*entry);
        }

        if (&entry != &stm.list.back())
            fmt::format_to(std::back_inserter(buf_), "\n");

        if (entry->is_special_stmt())
            last_special = true;
        else
            last_special = false;
    }

    indent_ -= 4;
}

auto source::dump_stmt_comp(stmt_comp const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "{: >{}}\n", "{", indent_ + 1);
    dump_stmt_list(*stm.block);
    fmt::format_to(std::back_inserter(buf_), "\n{: >{}}", "}", indent_ + 1);
}

auto source::dump_stmt_dev(stmt_dev const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "/#\n");
    dump_stmt_list(*stm.block);
    fmt::format_to(std::back_inserter(buf_), "\n#/");
}

auto source::dump_stmt_expr(stmt_expr const& stm) -> void
{
    switch (stm.value->kind())
    {
        case node::expr_increment:
            dump_expr_increment(stm.value->as<expr_increment>());
            break;
        case node::expr_decrement:
            dump_expr_decrement(stm.value->as<expr_decrement>());
            break;
        case node::expr_assign:
            dump_expr_assign(stm.value->as<expr_assign>());
            break;
        case node::expr_call:
            dump_expr_call(stm.value->as<expr_call>());
            break;
        case node::expr_method:
            dump_expr_method(stm.value->as<expr_method>());
            break;
        case node::expr_empty:
        default:
            break;
    }

    fmt::format_to(std::back_inserter(buf_), ";");
}

auto source::dump_stmt_endon(stmt_endon const& stm) -> void
{
    dump_expr(*stm.obj);
    fmt::format_to(std::back_inserter(buf_), " endon( ");
    dump_expr(*stm.event);
    fmt::format_to(std::back_inserter(buf_), " );");
}

auto source::dump_stmt_notify(stmt_notify const& stm) -> void
{
    dump_expr(*stm.obj);
    fmt::format_to(std::back_inserter(buf_), " notify( ");
    dump_expr(*stm.event);

    if (stm.args->list.size() > 0)
    {
        fmt::format_to(std::back_inserter(buf_), ",");
        dump_expr_arguments(*stm.args);
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), " ");
    }

    fmt::format_to(std::back_inserter(buf_), ");");
}

auto source::dump_stmt_wait(stmt_wait const& stm) -> void
{
    if (stm.time->is<expr_float>() || stm.time->is<expr_integer>())
    {
        fmt::format_to(std::back_inserter(buf_), "wait ");
        dump_expr(*stm.time);
        fmt::format_to(std::back_inserter(buf_), ";");
    }
    else if (stm.time->is<expr_paren>())
    {
        fmt::format_to(std::back_inserter(buf_), "wait");
        dump_expr(*stm.time);
        fmt::format_to(std::back_inserter(buf_), ";");
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), "wait( ");
        dump_expr(*stm.time);
        fmt::format_to(std::back_inserter(buf_), " );");
    }
}

auto source::dump_stmt_waittill(stmt_waittill const& stm) -> void
{
    dump_expr(*stm.obj);
    fmt::format_to(std::back_inserter(buf_), " waittill( ");
    dump_expr(*stm.event);

    if (stm.args->list.size() > 0)
    {
        fmt::format_to(std::back_inserter(buf_), ",");
        dump_expr_arguments(*stm.args);
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), " ");
    }

    fmt::format_to(std::back_inserter(buf_), ");");
}

auto source::dump_stmt_waittillmatch(stmt_waittillmatch const& stm) -> void
{
    dump_expr(*stm.obj);
    fmt::format_to(std::back_inserter(buf_), " waittillmatch( ");
    dump_expr(*stm.event);

    if (stm.args->list.size() > 0)
    {
        fmt::format_to(std::back_inserter(buf_), ",");
        dump_expr_arguments(*stm.args);
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), " ");
    }

    fmt::format_to(std::back_inserter(buf_), ");");
}

auto source::dump_stmt_waittillframeend(stmt_waittillframeend const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "waittillframeend;");
}

auto source::dump_stmt_waitframe(stmt_waitframe const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "waitframe();");
}

auto source::dump_stmt_if(stmt_if const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "if ( ");
    dump_expr(*stm.test);
    fmt::format_to(std::back_inserter(buf_), " )\n");

    if (stm.body->is<stmt_comp>())
    {
        dump_stmt(*stm.body);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(*stm.body);
        indent_ -= 4;
    }
}

auto source::dump_stmt_ifelse(stmt_ifelse const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "if ( ");
    dump_expr(*stm.test);
    fmt::format_to(std::back_inserter(buf_), " )\n");

    if (stm.stmt_if->is<stmt_comp>())
    {
        dump_stmt(*stm.stmt_if);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(*stm.stmt_if);
        indent_ -= 4;
    }

    fmt::format_to(std::back_inserter(buf_), "\n{: >{}}else", "", indent_);

    if (stm.stmt_else->is<stmt_comp>())
    {
        fmt::format_to(std::back_inserter(buf_), "\n");
        dump_stmt(*stm.stmt_else);
    }
    else
    {
        if (stm.stmt_else->is<stmt_if>() || stm.stmt_else ->is<stmt_ifelse>())
        {
            fmt::format_to(std::back_inserter(buf_), " ");
            dump_stmt(*stm.stmt_else);
        }
        else
        {
            indent_ += 4;
            fmt::format_to(std::back_inserter(buf_), "\n{: >{}}", "", indent_);
            dump_stmt(*stm.stmt_else);
            indent_ -= 4;
        }
    }
}

auto source::dump_stmt_while(stmt_while const& stm) -> void
{
    if (stm.test->is<expr_empty>())
    {
        fmt::format_to(std::back_inserter(buf_), "while ( true )\n");
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), "while ( ");
        dump_expr(*stm.test);
        fmt::format_to(std::back_inserter(buf_), " )\n");
    }

    if (stm.body->is<stmt_comp>())
    {
        dump_stmt(*stm.body);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(*stm.body);
        indent_ -= 4;
    }
}

auto source::dump_stmt_dowhile(stmt_dowhile const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "do\n");

    if (stm.body->is<stmt_comp>())
    {
        dump_stmt(*stm.body);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(*stm.body);
        indent_ -= 4;
    }

    if (stm.test->is<expr_empty>())
    {
        fmt::format_to(std::back_inserter(buf_), "\n{: >{}}while ( true )", "", indent_);
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), "\n{: >{}}while (", "", indent_);
        dump_expr(*stm.test);
        fmt::format_to(std::back_inserter(buf_), " );");
    }
}

auto source::dump_stmt_for(stmt_for const& stm) -> void
{
    if (stm.test->is<expr_empty>())
    {
        fmt::format_to(std::back_inserter(buf_), "for (;;)\n");
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), "for ( ");
        dump_stmt(*stm.init);
        buf_.pop_back();
        fmt::format_to(std::back_inserter(buf_), "; ");
        dump_expr(*stm.test);
        fmt::format_to(std::back_inserter(buf_), "; ");
        dump_stmt(*stm.iter);
        buf_.pop_back();
        fmt::format_to(std::back_inserter(buf_), " )\n");
    }

    if (stm.body->is<stmt_comp>())
    {
        dump_stmt(*stm.body);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(*stm.body);
        indent_ -= 4;
    }
}

auto source::dump_stmt_foreach(stmt_foreach const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "foreach ( ");

    if (stm.use_key)
    {
        dump_expr((ctx_->props() & props::foreach) ? *stm.index : *stm.key);
        fmt::format_to(std::back_inserter(buf_), ", ");
    }

    dump_expr(*stm.value);
    fmt::format_to(std::back_inserter(buf_), " in ");
    dump_expr(*stm.container);
    fmt::format_to(std::back_inserter(buf_), " )\n");

    if (stm.body->is<stmt_comp>())
    {
        dump_stmt(*stm.body);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(*stm.body);
        indent_ -= 4;
    }
}

auto source::dump_stmt_switch(stmt_switch const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "switch ( ");
    dump_expr(*stm.test);
    fmt::format_to(std::back_inserter(buf_), " )\n");
    dump_stmt_comp(*stm.body);
}

auto source::dump_stmt_case(stmt_case const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "case ");
    dump_expr(*stm.value);
    fmt::format_to(std::back_inserter(buf_), ":");

    if (stm.body != nullptr && stm.body->list.size() > 0)
    {
        fmt::format_to(std::back_inserter(buf_), "\n");
        dump_stmt_list(*stm.body);
    }
}

auto source::dump_stmt_default(stmt_default const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "default:");

    if (stm.body != nullptr && stm.body->list.size() > 0)
    {
        fmt::format_to(std::back_inserter(buf_), "\n");
        dump_stmt_list(*stm.body);
    }
}

auto source::dump_stmt_break(stmt_break const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "break;");
}

auto source::dump_stmt_continue(stmt_continue const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "continue;");
}

auto source::dump_stmt_return(stmt_return const& stm) -> void
{
    if (stm.value->is<expr_empty>())
    {
        fmt::format_to(std::back_inserter(buf_), "return;");
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), "return ");
        dump_expr(*stm.value);
        fmt::format_to(std::back_inserter(buf_), ";");
    }
}

auto source::dump_stmt_breakpoint(stmt_breakpoint const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "breakpoint;");
}

auto source::dump_stmt_prof_begin(stmt_prof_begin const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "prof_begin(");
    dump_expr_arguments(*stm.args);
    fmt::format_to(std::back_inserter(buf_), ");");
}

auto source::dump_stmt_prof_end(stmt_prof_end const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "prof_end(");
    dump_expr_arguments(*stm.args);
    fmt::format_to(std::back_inserter(buf_), ");");
}

auto source::dump_stmt_assert(stmt_assert const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "assert(");
    dump_expr_arguments(*stm.args);
    fmt::format_to(std::back_inserter(buf_), ");");
}

auto source::dump_stmt_assertex(stmt_assertex const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "assertex(");
    dump_expr_arguments(*stm.args);
    fmt::format_to(std::back_inserter(buf_), ");");
}

auto source::dump_stmt_assertmsg(stmt_assertmsg const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "assertmsg(");
    dump_expr_arguments(*stm.args);
    fmt::format_to(std::back_inserter(buf_), ");");
}

auto source::dump_stmt_create(stmt_create const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_var_create( {} )", stm.index);
}

auto source::dump_stmt_remove(stmt_remove const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_var_remove( {} )", stm.index);
}

auto source::dump_stmt_clear(stmt_clear const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_var_clear( {} )", stm.index);
}

auto source::dump_stmt_jmp(stmt_jmp const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_jmp( {} )", stm.value);
}

auto source::dump_stmt_jmp_back(stmt_jmp_back const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_jmp_back( {} )", stm.value);
}

auto source::dump_stmt_jmp_cond(stmt_jmp_cond const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_jmp_cond( {} )", stm.value);
}

auto source::dump_stmt_jmp_true(stmt_jmp_true const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_jmp_expr_true( {} )", stm.value);
}

auto source::dump_stmt_jmp_false(stmt_jmp_false const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_jmp_expr_false( {} )", stm.value);
}

auto source::dump_stmt_jmp_switch(stmt_jmp_switch const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_switch( {} )", stm.value);
}

auto source::dump_stmt_jmp_endswitch(stmt_jmp_endswitch const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_endswitch()");
}

auto source::dump_expr(expr const& exp) -> void
{
    switch (exp.kind())
    {
        case node::expr_ternary:
            dump_expr_ternary(exp.as<expr_ternary>());
            break;
        case node::expr_binary:
            dump_expr_binary(exp.as<expr_binary>());
            break;
        case node::expr_complement:
            dump_expr_complement(exp.as<expr_complement>());
            break;
        case node::expr_negate:
            dump_expr_negate(exp.as<expr_negate>());
            break;
        case node::expr_not:
            dump_expr_not(exp.as<expr_not>());
            break;
        case node::expr_call:
            dump_expr_call(exp.as<expr_call>());
            break;
        case node::expr_method:
            dump_expr_method(exp.as<expr_method>());
            break;
        case node::expr_function:
            dump_expr_function(exp.as<expr_function>());
            break;
        case node::expr_pointer:
            dump_expr_pointer(exp.as<expr_pointer>());
            break;
        case node::expr_add_array:
            dump_expr_add_array(exp.as<expr_add_array>());
            break;
        case node::expr_parameters:
            dump_expr_parameters(exp.as<expr_parameters>());
            break;
        case node::expr_arguments:
            dump_expr_arguments(exp.as<expr_arguments>());
            break;
        case node::expr_isdefined:
            dump_expr_isdefined(exp.as<expr_isdefined>());
            break;
        case node::expr_istrue:
            dump_expr_istrue(exp.as<expr_istrue>());
            break;
        case node::expr_reference:
            dump_expr_reference(exp.as<expr_reference>());
            break;
        case node::expr_tuple:
            dump_expr_tuple(exp.as<expr_tuple>());
            break;
        case node::expr_array:
            dump_expr_array(exp.as<expr_array>());
            break;
        case node::expr_field:
            dump_expr_field(exp.as<expr_field>());
            break;
        case node::expr_size:
            dump_expr_size(exp.as<expr_size>());
            break;
        case node::expr_paren:
            dump_expr_paren(exp.as<expr_paren>());
            break;
        case node::expr_thisthread:
            dump_expr_thisthread(exp.as<expr_thisthread>());
            break;
        case node::expr_empty_array:
            dump_expr_empty_array(exp.as<expr_empty_array>());
            break;
        case node::expr_undefined:
            dump_expr_undefined(exp.as<expr_undefined>());
            break;
        case node::expr_game:
            dump_expr_game(exp.as<expr_game>());
            break;
        case node::expr_self:
            dump_expr_self(exp.as<expr_self>());
            break;
        case node::expr_anim:
            dump_expr_anim(exp.as<expr_anim>());
            break;
        case node::expr_level:
            dump_expr_level(exp.as<expr_level>());
            break;
        case node::expr_animation:
            dump_expr_animation(exp.as<expr_animation>());
            break;
        case node::expr_animtree:
            dump_expr_animtree(exp.as<expr_animtree>());
            break;
        case node::expr_identifier:
            dump_expr_identifier(exp.as<expr_identifier>());
            break;
        case node::expr_path:
            dump_expr_path(exp.as<expr_path>());
            break;
        case node::expr_istring:
            dump_expr_istring(exp.as<expr_istring>());
            break;
        case node::expr_string:
            dump_expr_string(exp.as<expr_string>());
            break;
        case node::expr_vector:
            dump_expr_vector(exp.as<expr_vector>());
            break;
        case node::expr_float:
            dump_expr_float(exp.as<expr_float>());
            break;
        case node::expr_integer:
            dump_expr_integer(exp.as<expr_integer>());
            break;
        case node::expr_false:
            dump_expr_false(exp.as<expr_false>());
            break;
        case node::expr_true:
            dump_expr_true(exp.as<expr_true>());
            break;
        case node::expr_var_create:
            dump_expr_var_create(exp.as<expr_var_create>());
            break;
        case node::expr_var_access:
            dump_expr_var_access(exp.as<expr_var_access>());
            break;
        default:
            break;
    }
}

auto source::dump_expr_increment(expr_increment const& exp) -> void
{
    if (exp.prefix)
    {
        fmt::format_to(std::back_inserter(buf_), "++");
        dump_expr(*exp.lvalue);
    }
    else
    {
        dump_expr(*exp.lvalue);
        fmt::format_to(std::back_inserter(buf_), "++");
    }
}

auto source::dump_expr_decrement(expr_decrement const& exp) -> void
{
    if (exp.prefix)
    {
        fmt::format_to(std::back_inserter(buf_), "--");
        dump_expr(*exp.lvalue);
    }
    else
    {
        dump_expr(*exp.lvalue);
        fmt::format_to(std::back_inserter(buf_), "--");
    }
}

auto source::dump_expr_assign(expr_assign const& exp) -> void
{
    dump_expr(*exp.lvalue);

    switch (exp.oper)
    {
        case expr_assign::op::eq:
            fmt::format_to(std::back_inserter(buf_), " = ");
            break;
        case expr_assign::op::add:
            fmt::format_to(std::back_inserter(buf_), " += ");
            break;
        case expr_assign::op::sub:
            fmt::format_to(std::back_inserter(buf_), " -= ");
            break;
        case expr_assign::op::mul:
            fmt::format_to(std::back_inserter(buf_), " *= ");
            break;
        case expr_assign::op::div:
            fmt::format_to(std::back_inserter(buf_), " /= ");
            break;
        case expr_assign::op::mod:
            fmt::format_to(std::back_inserter(buf_), " %= ");
            break;
        case expr_assign::op::shl:
            fmt::format_to(std::back_inserter(buf_), " <<= ");
            break;
        case expr_assign::op::shr:
            fmt::format_to(std::back_inserter(buf_), " >>= ");
            break;
        case expr_assign::op::bwor:
            fmt::format_to(std::back_inserter(buf_), " |= ");
            break;
        case expr_assign::op::bwand:
            fmt::format_to(std::back_inserter(buf_), " &= ");
            break;
        case expr_assign::op::bwexor:
            fmt::format_to(std::back_inserter(buf_), " ^= ");
            break;
    }

    dump_expr(*exp.rvalue);
}

auto source::dump_expr_ternary(expr_ternary const& exp) -> void
{
    dump_expr(*exp.test);
    fmt::format_to(std::back_inserter(buf_), " ? ");
    dump_expr(*exp.true_expr);
    fmt::format_to(std::back_inserter(buf_), " : ");
    dump_expr(*exp.false_expr);
}

auto source::dump_expr_binary(expr_binary const& exp) -> void
{
    dump_expr(*exp.lvalue);

    switch (exp.oper)
    {
        case expr_binary::op::bool_or:
            fmt::format_to(std::back_inserter(buf_), " || ");
            break;
        case expr_binary::op::bool_and:
            fmt::format_to(std::back_inserter(buf_), " && ");
            break;
        case expr_binary::op::eq:
            fmt::format_to(std::back_inserter(buf_), " == ");
            break;
        case expr_binary::op::ne:
            fmt::format_to(std::back_inserter(buf_), " != ");
            break;
        case expr_binary::op::le:
            fmt::format_to(std::back_inserter(buf_), " <= ");
            break;
        case expr_binary::op::ge:
            fmt::format_to(std::back_inserter(buf_), " >= ");
            break;
        case expr_binary::op::lt:
            fmt::format_to(std::back_inserter(buf_), " < ");
            break;
        case expr_binary::op::gt:
            fmt::format_to(std::back_inserter(buf_), " > ");
            break;
        case expr_binary::op::add:
            fmt::format_to(std::back_inserter(buf_), " + ");
            break;
        case expr_binary::op::sub:
            fmt::format_to(std::back_inserter(buf_), " - ");
            break;
        case expr_binary::op::mul:
            fmt::format_to(std::back_inserter(buf_), " * ");
            break;
        case expr_binary::op::div:
            fmt::format_to(std::back_inserter(buf_), " / ");
            break;
        case expr_binary::op::mod:
            fmt::format_to(std::back_inserter(buf_), " % ");
            break;
        case expr_binary::op::shl:
            fmt::format_to(std::back_inserter(buf_), " << ");
            break;
        case expr_binary::op::shr:
            fmt::format_to(std::back_inserter(buf_), " >> ");
            break;
        case expr_binary::op::bwor:
            fmt::format_to(std::back_inserter(buf_), " | ");
            break;
        case expr_binary::op::bwand:
            fmt::format_to(std::back_inserter(buf_), " & ");
            break;
        case expr_binary::op::bwexor:
            fmt::format_to(std::back_inserter(buf_), " ^ ");
            break;
    }

    dump_expr(*exp.rvalue);
}

auto source::dump_expr_not(expr_not const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "!");
    dump_expr(*exp.rvalue);
}

auto source::dump_expr_negate(expr_negate const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "-");
    dump_expr(*exp.rvalue);
}

auto source::dump_expr_complement(expr_complement const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "~");
    dump_expr(*exp.rvalue);
}

auto source::dump_expr_call(expr_call const& exp) -> void
{
    dump_call(*exp.value);
}

auto source::dump_expr_method(expr_method const& exp) -> void
{
    dump_expr(*exp.obj);
    fmt::format_to(std::back_inserter(buf_), " ");
    dump_call(*exp.value);
}

auto source::dump_call(call const& exp) -> void
{
    switch (exp.kind())
    {
        case node::expr_function:
            dump_expr_function(exp.as<expr_function>());
            break;
        case node::expr_pointer:
            dump_expr_pointer(exp.as<expr_pointer>());
            break;
        default:
            break;
    }
}

auto source::dump_expr_function(expr_function const& exp) -> void
{
    if (exp.mode == call::mode::thread)
        fmt::format_to(std::back_inserter(buf_), "thread ");
    else if (exp.mode == call::mode::childthread)
        fmt::format_to(std::back_inserter(buf_), "childthread ");

    if (exp.path->value != "")
    {
        dump_expr_path(*exp.path);
        fmt::format_to(std::back_inserter(buf_), "::");
    }

    dump_expr_identifier(*exp.name);
    fmt::format_to(std::back_inserter(buf_), "(");
    dump_expr_arguments(*exp.args);
    fmt::format_to(std::back_inserter(buf_), ")");
}

auto source::dump_expr_pointer(expr_pointer const& exp) -> void
{
    if (exp.mode == call::mode::builtin)
        fmt::format_to(std::back_inserter(buf_), "call ");
    else if (exp.mode == call::mode::thread)
        fmt::format_to(std::back_inserter(buf_), "thread ");
    else if (exp.mode == call::mode::childthread)
        fmt::format_to(std::back_inserter(buf_), "childthread ");

    fmt::format_to(std::back_inserter(buf_), "[[ ");
    dump_expr(*exp.func);
    fmt::format_to(std::back_inserter(buf_), " ]](");
    dump_expr_arguments(*exp.args);
    fmt::format_to(std::back_inserter(buf_), ")");
}

auto source::dump_expr_add_array(expr_add_array const& exp) -> void
{  
    fmt::format_to(std::back_inserter(buf_), "[");
    dump_expr_arguments(*exp.args);
    fmt::format_to(std::back_inserter(buf_), "]");
}

auto source::dump_expr_parameters(expr_parameters const& exp) -> void
{
    for (auto const& entry : exp.list)
    {
        fmt::format_to(std::back_inserter(buf_), " ");
        dump_expr_identifier(*entry);

        if (&entry != &exp.list.back())
            fmt::format_to(std::back_inserter(buf_), ",");
        else
            fmt::format_to(std::back_inserter(buf_), " ");
    }
}

auto source::dump_expr_arguments(expr_arguments const& exp) -> void
{
    for (auto const& entry : exp.list)
    {
        fmt::format_to(std::back_inserter(buf_), " ");
        dump_expr(*entry);

        if (&entry != &exp.list.back())
            fmt::format_to(std::back_inserter(buf_), ",");
        else
            fmt::format_to(std::back_inserter(buf_), " ");
    }
}

auto source::dump_expr_isdefined(expr_isdefined const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "isdefined( ");
    dump_expr(*exp.value);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_istrue(expr_istrue const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "istrue( ");
    dump_expr(*exp.value);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_reference(expr_reference const& exp) -> void
{
    dump_expr_path(*exp.path);
    fmt::format_to(std::back_inserter(buf_), "::");
    dump_expr_identifier(*exp.name);
}

auto source::dump_expr_tuple(expr_tuple const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "[");

    for (auto const& entry : exp.list)
    {
        dump_expr(*entry);

        if (&entry != &exp.list.back())
            fmt::format_to(std::back_inserter(buf_), ", ");
    }

    fmt::format_to(std::back_inserter(buf_), "]");
}

auto source::dump_expr_array(expr_array const& exp) -> void
{
    dump_expr(*exp.obj);
    fmt::format_to(std::back_inserter(buf_), "[");
    dump_expr(*exp.key);
    fmt::format_to(std::back_inserter(buf_), "]");
}

auto source::dump_expr_field(expr_field const& exp) -> void
{
    dump_expr(*exp.obj);
    fmt::format_to(std::back_inserter(buf_), ".");
    dump_expr_identifier(*exp.field);
}

auto source::dump_expr_size(expr_size const& exp) -> void
{
    dump_expr(*exp.obj);
    fmt::format_to(std::back_inserter(buf_), ".size");
}

auto source::dump_expr_paren(expr_paren const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "( ");
    dump_expr(*exp.value);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_thisthread(expr_thisthread const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "thisthread");
}

auto source::dump_expr_empty_array(expr_empty_array const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "[]");
}

auto source::dump_expr_undefined(expr_undefined const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "undefined");
}

auto source::dump_expr_game(expr_game const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "game");
}

auto source::dump_expr_self(expr_self const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "self");
}

auto source::dump_expr_anim(expr_anim const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "anim");
}

auto source::dump_expr_level(expr_level const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "level");
}

auto source::dump_expr_animation(expr_animation const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "%{}", exp.value);
}

auto source::dump_expr_animtree(expr_animtree const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "#animtree");
}

auto source::dump_expr_identifier(expr_identifier const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "{}", exp.value);
}

auto source::dump_expr_path(expr_path const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "{}", utils::string::backslash(exp.value));
}

auto source::dump_expr_istring(expr_istring const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "&{}", utils::string::to_literal(exp.value));
}

auto source::dump_expr_string(expr_string const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "{}", utils::string::to_literal(exp.value));
}

auto source::dump_expr_vector(expr_vector const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "( ");
    dump_expr(*exp.x);
    fmt::format_to(std::back_inserter(buf_), ", ");
    dump_expr(*exp.y);
    fmt::format_to(std::back_inserter(buf_), ", ");
    dump_expr(*exp.z);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_float(expr_float const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "{}", exp.value);
}

auto source::dump_expr_integer(expr_integer const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "{}", exp.value);
}

auto source::dump_expr_false(expr_false const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "false");
}

auto source::dump_expr_true(expr_true const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "true");
}

auto source::dump_expr_var_create(expr_var_create const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_var_create( {} )", exp.index);
}

auto source::dump_expr_var_access(expr_var_access const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_var_access( {} )", exp.index);
}

} // namespace xsk::gsc
