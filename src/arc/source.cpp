// Copyright 2023 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/arc/source.hpp"
#include "xsk/arc/context.hpp"
#include "xsk/utils/string.hpp"

namespace xsk::arc
{

source::source(context* ctx) : ctx_{ ctx }, indent_{ 0 }
{
}

auto source::dump(assembly const& data) -> std::vector<u8>
{
    buf_ = std::vector<u8>{};
    buf_.reserve(0x10000);

    fmt::format_to(std::back_inserter(buf_), "// {} GSC ASSEMBLY\n", ctx_->engine_name());
    fmt::format_to(std::back_inserter(buf_), "// Dumped by https://github.com/xensik/gsc-tool\n");

    dump_assembly(data);

    return std::move(buf_);
}


auto source::dump(program const& data) -> std::vector<u8>
{
    buf_ = std::vector<u8>{};
    buf_.reserve(0x10000);

    fmt::format_to(std::back_inserter(buf_), "// {} GSC SOURCE\n", ctx_->engine_name());
    fmt::format_to(std::back_inserter(buf_), "// Dumped by https://github.com/xensik/gsc-tool\n");
    
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
            fmt::format_to(std::back_inserter(buf_), " \"{}\"", inst.data[0]);
            break;
        case opcode::OP_GetAnimation:
            fmt::format_to(std::back_inserter(buf_), " \"{}\" \"{}\"", inst.data[0], inst.data[1]);
            break;
        // case opcode::OP_GetLocalFunction:
        // case opcode::OP_ScriptLocalFunctionCall:
        // case opcode::OP_ScriptLocalFunctionCall2:
        // case opcode::OP_ScriptLocalMethodCall:
        //     fmt::format_to(std::back_inserter(buf_), " {}", inst.data[0]);
        //     break;
        // case opcode::OP_ScriptLocalThreadCall:
        // case opcode::OP_ScriptLocalChildThreadCall:
        // case opcode::OP_ScriptLocalMethodThreadCall:
        // case opcode::OP_ScriptLocalMethodChildThreadCall:
        //     fmt::format_to(std::back_inserter(buf_), " {} {}\n", inst.data[0], inst.data[1]);
        //     break;
        case opcode::OP_EndSwitch:
        {
            auto count = static_cast<u32>(std::stoul(inst.data[0]));
            auto type = static_cast<switch_type>(std::stoul(inst.data.back()));
            auto index = 1;

            fmt::format_to(std::back_inserter(buf_), " {}\n", count);

            for (auto i = 0u; i < count; i++)
            {
                if (inst.data[index] == "case")
                {
                    auto data = (type == switch_type::integer) ? fmt::format("{}", inst.data[index + 1]) : fmt::format("\"{}\"", inst.data[index + 1]);
                    fmt::format_to(std::back_inserter(buf_), "\t\t\t{} {} {}", inst.data[index], data, inst.data[index + 2]);
                    index += 3;
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
        dump_decl(dec);
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
            dump_decl_dev_begin(*dec.as_dev_begin);
            break;
        case node::decl_dev_end:
            dump_decl_dev_end(*dec.as_dev_end);
            break;
        case node::decl_namespace:
            dump_decl_namespace(*dec.as_namespace);
            break;
        case node::decl_usingtree:
            dump_decl_usingtree(*dec.as_usingtree);
            break;
        case node::decl_function:
            dump_decl_function(*dec.as_function);
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

auto source::dump_decl_namespace(decl_namespace const& dec) -> void
{
    fmt::format_to(std::back_inserter(buf_), "#namespace ");
    dump_expr_string(*dec.name);
    fmt::format_to(std::back_inserter(buf_), ";\n");
}

auto source::dump_decl_usingtree(decl_usingtree const& dec) -> void
{
    fmt::format_to(std::back_inserter(buf_), "#using_animtree(");
    dump_expr_string(*dec.name);
    fmt::format_to(std::back_inserter(buf_), ");\n");
}

auto source::dump_decl_function(decl_function const& dec) -> void
{
    indent_ = 0;

    if (ctx_->props() & props::version2)
        fmt::format_to(std::back_inserter(buf_), "function ");

    if (static_cast<std::uint8_t>(dec.flags) & static_cast<std::uint8_t>(export_flags::export_autoexec))
        fmt::format_to(std::back_inserter(buf_), "autoexec ");

    if (static_cast<std::uint8_t>(dec.flags) & static_cast<std::uint8_t>(export_flags::export_codecall))
        fmt::format_to(std::back_inserter(buf_), "codecall ");

    if (static_cast<std::uint8_t>(dec.flags) & static_cast<std::uint8_t>(export_flags::export_private2))
        fmt::format_to(std::back_inserter(buf_), "private ");

    if ((ctx_->props() & props::version2) && !dec.space->value.empty())
    {
        fmt::format_to(std::back_inserter(buf_), "{}::", dec.space->value);
    }

    dump_expr_identifier(*dec.name);
    fmt::format_to(std::back_inserter(buf_), "(");
    dump_expr_parameters(*dec.params);
    fmt::format_to(std::back_inserter(buf_), ")\n");
    dump_stmt_comp(*dec.body);
    fmt::format_to(std::back_inserter(buf_), "\n");
}

auto source::dump_stmt(stmt const& stm) -> void
{
    switch (stm.kind())
    {
        case node::stmt_list:
            dump_stmt_list(*stm.as_list);
            break;
        case node::stmt_comp:
            dump_stmt_comp(*stm.as_comp);
            break;
        case node::stmt_dev:
            dump_stmt_dev(*stm.as_dev);
            break;
        case node::stmt_expr:
            dump_stmt_expr(*stm.as_expr);
            break;
        case node::stmt_call:
            dump_stmt_call(*stm.as_call);
            break;
        case node::stmt_const:
            dump_stmt_const(*stm.as_const);
            break;
        case node::stmt_assign:
            dump_stmt_assign(*stm.as_assign);
            break;
        case node::stmt_endon:
            dump_stmt_endon(*stm.as_endon);
            break;
        case node::stmt_notify:
            dump_stmt_notify(*stm.as_notify);
            break;
        case node::stmt_realwait:
            dump_stmt_realwait(*stm.as_realwait);
            break;
        case node::stmt_wait:
            dump_stmt_wait(*stm.as_wait);
            break;
        case node::stmt_waittill:
            dump_stmt_waittill(*stm.as_waittill);
            break;
        case node::stmt_waittillmatch:
            dump_stmt_waittillmatch(*stm.as_waittillmatch);
            break;
        case node::stmt_waittillframeend:
            dump_stmt_waittillframeend(*stm.as_waittillframeend);
            break;
        case node::stmt_if:
            dump_stmt_if(*stm.as_if);
            break;
        case node::stmt_ifelse:
            dump_stmt_ifelse(*stm.as_ifelse);
            break;
        case node::stmt_while:
            dump_stmt_while(*stm.as_while);
            break;
        case node::stmt_dowhile:
            dump_stmt_dowhile(*stm.as_dowhile);
            break;
        case node::stmt_for:
            dump_stmt_for(*stm.as_for);
            break;
        case node::stmt_foreach:
            dump_stmt_foreach(*stm.as_foreach);
            break;
        case node::stmt_switch:
            dump_stmt_switch(*stm.as_switch);
            break;
        case node::stmt_case:
            dump_stmt_case(*stm.as_case);
            break;
        case node::stmt_default:
            dump_stmt_default(*stm.as_default);
            break;
        case node::stmt_break:
            dump_stmt_break(*stm.as_break);
            break;
        case node::stmt_continue:
            dump_stmt_continue(*stm.as_continue);
            break;
        case node::stmt_return:
            dump_stmt_return(*stm.as_return);
            break;
        case node::stmt_breakpoint:
            dump_stmt_breakpoint(*stm.as_breakpoint);
            break;
        case node::stmt_prof_begin:
            dump_stmt_prof_begin(*stm.as_prof_begin);
            break;
        case node::stmt_prof_end:
            dump_stmt_prof_end(*stm.as_prof_end);
            break;
        case node::asm_loc:
            dump_asm_loc(*stm.as_loc);
            break;
        case node::asm_jmp:
            dump_asm_jmp(*stm.as_jump);
            break;
        case node::asm_jmp_back:
            dump_asm_jmp_back(*stm.as_jump_back);
            break;
        case node::asm_jmp_cond:
            dump_asm_jmp_cond(*stm.as_cond);
            break;
        case node::asm_switch:
            dump_asm_switch(*stm.as_asm_switch);
            break;
        case node::asm_endswitch:
            dump_asm_endswitch(*stm.as_asm_endswitch);
            break;
        case node::asm_dev:
            dump_asm_dev(*stm.as_asm_dev);
            break;
        default:
            break;
    }
}

auto source::dump_stmt_list(stmt_list const& stm) -> void
{
    auto last_special = false;
    indent_ += 4;

    for (auto const& entry : stm.list)
    {
        if ((&entry != &stm.list.front() && entry.as_node->is_special_stmt()) || last_special)
            fmt::format_to(std::back_inserter(buf_), "\n");

        if (entry == node::stmt_dev)
        {
            dump_stmt(entry);
        }
        else
        {
            fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
            dump_stmt(entry);
        }

        if (&entry != &stm.list.back())
            fmt::format_to(std::back_inserter(buf_), "\n");

        if (entry.as_node->is_special_stmt())
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
    indent_ -= 4;
    fmt::format_to(std::back_inserter(buf_), "/#\n");
    dump_stmt_list(*stm.block);
    fmt::format_to(std::back_inserter(buf_), "\n#/");
    indent_ += 4;
}

auto source::dump_stmt_expr(stmt_expr const& stm) -> void
{
    dump_expr(stm.value);
}

auto source::dump_stmt_call(stmt_call const& stm) -> void
{
    dump_expr(stm.value);
    fmt::format_to(std::back_inserter(buf_), ";");
}

auto source::dump_stmt_const(stmt_const const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "const ");
    dump_expr_identifier(*stm.lvalue);
    fmt::format_to(std::back_inserter(buf_), " = ");
    dump_expr(stm.rvalue);
    fmt::format_to(std::back_inserter(buf_), ";");
}

auto source::dump_stmt_assign(stmt_assign const& stm) -> void
{
    dump_expr(stm.value);
    fmt::format_to(std::back_inserter(buf_), ";");
}

auto source::dump_stmt_endon(stmt_endon const& stm) -> void
{
    dump_expr(stm.obj);
    fmt::format_to(std::back_inserter(buf_), " endon( ");
    dump_expr(stm.event);
    fmt::format_to(std::back_inserter(buf_), " );");
}

auto source::dump_stmt_notify(stmt_notify const& stm) -> void
{
    dump_expr(stm.obj);
    fmt::format_to(std::back_inserter(buf_), " notify( ");
    dump_expr(stm.event);

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

auto source::dump_stmt_realwait(stmt_realwait const& stm) -> void
{
    if (stm.time == node::expr_float || stm.time == node::expr_integer)
    {
        fmt::format_to(std::back_inserter(buf_), "wait ");
        dump_expr(stm.time);
        fmt::format_to(std::back_inserter(buf_), ";");
    }
    else if (stm.time == node::expr_paren)
    {
        fmt::format_to(std::back_inserter(buf_), "wait");
        dump_expr(stm.time);
        fmt::format_to(std::back_inserter(buf_), ";");
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), "wait( ");
        dump_expr(stm.time);
        fmt::format_to(std::back_inserter(buf_), " );");
    }
}

auto source::dump_stmt_wait(stmt_wait const& stm) -> void
{
    if (stm.time == node::expr_float || stm.time == node::expr_integer)
    {
        fmt::format_to(std::back_inserter(buf_), "wait ");
        dump_expr(stm.time);
        fmt::format_to(std::back_inserter(buf_), ";");
    }
    else if (stm.time == node::expr_paren)
    {
        fmt::format_to(std::back_inserter(buf_), "wait");
        dump_expr(stm.time);
        fmt::format_to(std::back_inserter(buf_), ";");
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), "wait( ");
        dump_expr(stm.time);
        fmt::format_to(std::back_inserter(buf_), " );");
    }
}

auto source::dump_stmt_waittill(stmt_waittill const& stm) -> void
{
    dump_expr(stm.obj);
    fmt::format_to(std::back_inserter(buf_), " waittill( ");
    dump_expr(stm.event);

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
    dump_expr(stm.obj);
    fmt::format_to(std::back_inserter(buf_), " waittillmatch( ");
    dump_expr(stm.event);

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

auto source::dump_stmt_if(stmt_if const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "if ( ");
    dump_expr(stm.test);
    fmt::format_to(std::back_inserter(buf_), " )\n");

    if (stm.body == node::stmt_comp)
    {
        dump_stmt(stm.body);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(stm.body);
        indent_ -= 4;
    }
}

auto source::dump_stmt_ifelse(stmt_ifelse const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "if ( ");
    dump_expr(stm.test);
    fmt::format_to(std::back_inserter(buf_), " )\n");

    if (stm.stmt_if == node::stmt_comp)
    {
        dump_stmt(stm.stmt_if);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(stm.stmt_if);
        indent_ -= 4;
    }

    fmt::format_to(std::back_inserter(buf_), "\n{: >{}}else", "", indent_);

    if (stm.stmt_else == node::stmt_comp)
    {
        fmt::format_to(std::back_inserter(buf_), "\n");
        dump_stmt(stm.stmt_else);
    }
    else
    {
        if (stm.stmt_else == node::stmt_if || stm.stmt_else == node::stmt_ifelse)
        {
            fmt::format_to(std::back_inserter(buf_), " ");
            dump_stmt(stm.stmt_else);
        }
        else
        {
            indent_ += 4;
            fmt::format_to(std::back_inserter(buf_), "\n{: >{}}", "", indent_);
            dump_stmt(stm.stmt_else);
            indent_ -= 4;
        }
    }
}

auto source::dump_stmt_while(stmt_while const& stm) -> void
{
    if (stm.test == node::null)
    {
        fmt::format_to(std::back_inserter(buf_), "while ( true )\n");
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), "while ( ");
        dump_expr(stm.test);
        fmt::format_to(std::back_inserter(buf_), " )\n");
    }

    if (stm.body == node::stmt_comp)
    {
        dump_stmt(stm.body);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(stm.body);
        indent_ -= 4;
    }
}

auto source::dump_stmt_dowhile(stmt_dowhile const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "do\n");

    if (stm.body == node::stmt_comp)
    {
        dump_stmt(stm.body);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(stm.body);
        indent_ -= 4;
    }

    if (stm.test == node::null)
    {
        fmt::format_to(std::back_inserter(buf_), "\n{: >{}}while ( true )", "", indent_);
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), "\n{: >{}}while (", "", indent_);
        dump_expr(stm.test);
        fmt::format_to(std::back_inserter(buf_), " );");
    }
}

auto source::dump_stmt_for(stmt_for const& stm) -> void
{
    if (stm.test == node::null)
    {
        fmt::format_to(std::back_inserter(buf_), "for (;;)\n");
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), "for ( ");
        dump_stmt(stm.init);
        fmt::format_to(std::back_inserter(buf_), "; ");
        dump_expr(stm.test);
        fmt::format_to(std::back_inserter(buf_), "; ");
        dump_stmt(stm.iter);
        fmt::format_to(std::back_inserter(buf_), " )\n");
    }

    if (stm.body == node::stmt_comp)
    {
        dump_stmt(stm.body);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(stm.body);
        indent_ -= 4;
    }
}

auto source::dump_stmt_foreach(stmt_foreach const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "foreach ( ");

    if (stm.use_key)
    {
        dump_expr(/*(ctx_->props() & props::foreach) ? stm.index :*/ stm.key);
        fmt::format_to(std::back_inserter(buf_), ", ");
    }

    dump_expr(stm.value);
    fmt::format_to(std::back_inserter(buf_), " in ");
    dump_expr(stm.container);
    fmt::format_to(std::back_inserter(buf_), " )\n");

    if (stm.body == node::stmt_comp)
    {
        dump_stmt(stm.body);
    }
    else
    {
        indent_ += 4;
        fmt::format_to(std::back_inserter(buf_), "{: >{}}", "", indent_);
        dump_stmt(stm.body);
        indent_ -= 4;
    }
}

auto source::dump_stmt_switch(stmt_switch const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "switch ( ");
    dump_expr(stm.test);
    fmt::format_to(std::back_inserter(buf_), " )\n");
    dump_stmt_comp(*stm.body);
}

auto source::dump_stmt_case(stmt_case const& stm) -> void
{
    fmt::format_to(std::back_inserter(buf_), "case ");
    dump_expr(stm.value);
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
    if (stm.value == node::null)
    {
        fmt::format_to(std::back_inserter(buf_), "return;");
    }
    else
    {
        fmt::format_to(std::back_inserter(buf_), "return ");
        dump_expr(stm.value);
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

auto source::dump_expr(expr const& exp) -> void
{
    switch (exp.as_node->kind())
    {
        case node::expr_increment:
            dump_expr_increment(*exp.as_increment);
            break;
        case node::expr_decrement:
            dump_expr_decrement(*exp.as_decrement);
            break;
        case node::expr_assign_equal:
            dump_expr_assign_equal(*exp.as_assign_equal);
            break;
        case node::expr_assign_add:
            dump_expr_assign_add(*exp.as_assign_add);
            break;
        case node::expr_assign_sub:
            dump_expr_assign_sub(*exp.as_assign_sub);
            break;
        case node::expr_assign_mul:
            dump_expr_assign_mul(*exp.as_assign_mul);
            break;
        case node::expr_assign_div:
            dump_expr_assign_div(*exp.as_assign_div);
            break;
        case node::expr_assign_mod:
            dump_expr_assign_mod(*exp.as_assign_mod);
            break;
        case node::expr_assign_shift_left:
            dump_expr_assign_shift_left(*exp.as_assign_shift_left);
            break;
        case node::expr_assign_shift_right:
            dump_expr_assign_shift_right(*exp.as_assign_shift_right);
            break;
        case node::expr_assign_bitwise_or:
            dump_expr_assign_bitwise_or(*exp.as_assign_bw_or);
            break;
        case node::expr_assign_bitwise_and:
            dump_expr_assign_bitwise_and(*exp.as_assign_bw_and);
            break;
        case node::expr_assign_bitwise_exor:
            dump_expr_assign_bitwise_exor(*exp.as_assign_bw_exor);
            break;
        case node::expr_ternary:
            dump_expr_ternary(*exp.as_ternary);
            break;
        case node::expr_and:
            dump_expr_and(*exp.as_and);
            break;
        case node::expr_or:
            dump_expr_or(*exp.as_or);
            break;
        case node::expr_super_equal:
            dump_expr_super_equal(*exp.as_super_equal);
            break;
        case node::expr_super_not_equal:
            dump_expr_super_not_equal(*exp.as_super_not_equal);
            break;
        case node::expr_equality:
            dump_expr_equality(*exp.as_equality);
            break;
        case node::expr_inequality:
            dump_expr_inequality(*exp.as_inequality);
            break;
        case node::expr_less_equal:
            dump_expr_less_equal(*exp.as_less_equal);
            break;
        case node::expr_greater_equal:
            dump_expr_greater_equal(*exp.as_greater_equal);
            break;
        case node::expr_less:
            dump_expr_less(*exp.as_less);
            break;
        case node::expr_greater:
            dump_expr_greater(*exp.as_greater);
            break;
        case node::expr_add:
            dump_expr_add(*exp.as_add);
            break;
        case node::expr_sub:
            dump_expr_sub(*exp.as_sub);
            break;
        case node::expr_mul:
            dump_expr_mul(*exp.as_mul);
            break;
        case node::expr_div:
            dump_expr_div(*exp.as_div);
            break;
        case node::expr_mod:
            dump_expr_mod(*exp.as_mod);
            break;
        case node::expr_shift_left:
            dump_expr_shift_left(*exp.as_shift_left);
            break;
        case node::expr_shift_right:
            dump_expr_shift_right(*exp.as_shift_right);
            break;
        case node::expr_bitwise_or:
            dump_expr_bitwise_or(*exp.as_bitwise_or);
            break;
        case node::expr_bitwise_and:
            dump_expr_bitwise_and(*exp.as_bitwise_and);
            break;
        case node::expr_bitwise_exor:
            dump_expr_bitwise_exor(*exp.as_bitwise_exor);
            break;
        case node::expr_complement:
            dump_expr_complement(*exp.as_complement);
            break;
        case node::expr_negate:
            dump_expr_negate(*exp.as_negate);
            break;
        case node::expr_not:
            dump_expr_not(*exp.as_not);
            break;
        case node::expr_new:
            dump_expr_new(*exp.as_new);
            break;
        case node::expr_call:
            dump_expr_call(*exp.as_call);
            break;
        case node::expr_method:
            dump_expr_method(*exp.as_method);
            break;
        case node::expr_function:
            dump_expr_function(*exp.as_function);
            break;
        case node::expr_pointer:
            dump_expr_pointer(*exp.as_pointer);
            break;
        case node::expr_parameters:
            dump_expr_parameters(*exp.as_parameters);
            break;
        case node::expr_arguments:
            dump_expr_arguments(*exp.as_arguments);
            break;
        case node::expr_isdefined:
            dump_expr_isdefined(*exp.as_isdefined);
            break;
        case node::expr_vectorscale:
            dump_expr_vectorscale(*exp.as_vectorscale);
            break;
        case node::expr_anglestoup:
            dump_expr_anglestoup(*exp.as_anglestoup);
            break;
        case node::expr_anglestoright:
            dump_expr_anglestoright(*exp.as_anglestoright);
            break;
        case node::expr_anglestoforward:
            dump_expr_anglestoforward(*exp.as_anglestoforward);
            break;
        case node::expr_angleclamp180:
            dump_expr_angleclamp180(*exp.as_angleclamp180);
            break;
        case node::expr_vectortoangles:
            dump_expr_vectortoangles(*exp.as_vectortoangles);
            break;
        case node::expr_abs:
            dump_expr_abs(*exp.as_abs);
            break;
        case node::expr_gettime:
            dump_expr_gettime(*exp.as_gettime);
            break;
        case node::expr_getdvar:
            dump_expr_getdvar(*exp.as_getdvar);
            break;
        case node::expr_getdvarint:
            dump_expr_getdvarint(*exp.as_getdvarint);
            break;
        case node::expr_getdvarfloat:
            dump_expr_getdvarfloat(*exp.as_getdvarfloat);
            break;
        case node::expr_getdvarvector:
            dump_expr_getdvarvector(*exp.as_getdvarvector);
            break;
        case node::expr_getdvarcolorred:
            dump_expr_getdvarcolorred(*exp.as_getdvarcolorred);
            break;
        case node::expr_getdvarcolorgreen:
            dump_expr_getdvarcolorgreen(*exp.as_getdvarcolorgreen);
            break;
        case node::expr_getdvarcolorblue:
            dump_expr_getdvarcolorblue(*exp.as_getdvarcolorblue);
            break;
        case node::expr_getdvarcoloralpha:
            dump_expr_getdvarcoloralpha(*exp.as_getdvarcoloralpha);
            break;
        case node::expr_getfirstarraykey:
            dump_expr_getfirstarraykey(*exp.as_getfirstarraykey);
            break;
        case node::expr_getnextarraykey:
            dump_expr_getnextarraykey(*exp.as_getnextarraykey);
            break;
        case node::expr_reference:
            dump_expr_reference(*exp.as_reference);
            break;
        case node::expr_array:
            dump_expr_array(*exp.as_array);
            break;
        case node::expr_field:
            dump_expr_field(*exp.as_field);
            break;
        case node::expr_size:
            dump_expr_size(*exp.as_size);
            break;
        case node::expr_paren:
            dump_expr_paren(*exp.as_paren);
            break;
        case node::expr_empty_array:
            dump_expr_empty_array(*exp.as_empty_array);
            break;
        case node::expr_undefined:
            dump_expr_undefined(*exp.as_undefined);
            break;
        case node::expr_game:
            dump_expr_game(*exp.as_game);
            break;
        case node::expr_self:
            dump_expr_self(*exp.as_self);
            break;
        case node::expr_anim:
            dump_expr_anim(*exp.as_anim);
            break;
        case node::expr_level:
            dump_expr_level(*exp.as_level);
            break;
        case node::expr_world:
            dump_expr_world(*exp.as_world);
            break;
        case node::expr_classes:
            dump_expr_classes(*exp.as_classes);
            break;
        case node::expr_animation:
            dump_expr_animation(*exp.as_animation);
            break;
        case node::expr_animtree:
            dump_expr_animtree(*exp.as_animtree);
            break;
        case node::expr_identifier:
            dump_expr_identifier(*exp.as_identifier);
            break;
        case node::expr_path:
            dump_expr_path(*exp.as_path);
            break;
        case node::expr_istring:
            dump_expr_istring(*exp.as_istring);
            break;
        case node::expr_string:
            dump_expr_string(*exp.as_string);
            break;
        case node::expr_hash:
            dump_expr_hash(*exp.as_hash);
            break;
        case node::expr_vector:
            dump_expr_vector(*exp.as_vector);
            break;
        case node::expr_float:
            dump_expr_float(*exp.as_float);
            break;
        case node::expr_integer:
            dump_expr_integer(*exp.as_integer);
            break;
        case node::expr_false:
            dump_expr_false(*exp.as_false);
            break;
        case node::expr_true:
            dump_expr_true(*exp.as_true);
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
        dump_expr(exp.lvalue);
    }
    else
    {
        dump_expr(exp.lvalue);
        fmt::format_to(std::back_inserter(buf_), "++");
    }
}

auto source::dump_expr_decrement(expr_decrement const& exp) -> void
{
    if (exp.prefix)
    {
        fmt::format_to(std::back_inserter(buf_), "--");
        dump_expr(exp.lvalue);
    }
    else
    {
        dump_expr(exp.lvalue);
        fmt::format_to(std::back_inserter(buf_), "--");
    }
}

auto source::dump_expr_assign_equal(expr_assign_equal const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " = ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_assign_add(expr_assign_add const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " += ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_assign_sub(expr_assign_sub const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " -= ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_assign_mul(expr_assign_mul const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " *= ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_assign_div(expr_assign_div const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " /= ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_assign_mod(expr_assign_mod const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " %= ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_assign_shift_left(expr_assign_shift_left const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " <<= ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_assign_shift_right(expr_assign_shift_right const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " >>= ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_assign_bitwise_or(expr_assign_bitwise_or const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " |= ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_assign_bitwise_and(expr_assign_bitwise_and const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " &= ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_assign_bitwise_exor(expr_assign_bitwise_exor const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " ^= ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_ternary(expr_ternary const& exp) -> void
{
    dump_expr(exp.test);
    fmt::format_to(std::back_inserter(buf_), " ? ");
    dump_expr(exp.true_expr);
    fmt::format_to(std::back_inserter(buf_), " : ");
    dump_expr(exp.false_expr);
}

auto source::dump_expr_or(expr_or const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " || ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_and(expr_and const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " && ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_super_equal(expr_super_equal const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " === ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_super_not_equal(expr_super_not_equal const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " !== ");
    dump_expr(exp.rvalue);
}
    
auto source::dump_expr_equality(expr_equality const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " == ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_inequality(expr_inequality const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " != ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_less_equal(expr_less_equal const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " <= ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_greater_equal(expr_greater_equal const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " >= ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_less(expr_less const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " < ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_greater(expr_greater const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " > ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_add(expr_add const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " + ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_sub(expr_sub const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " - ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_mul(expr_mul const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " * ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_div(expr_div const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " / ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_mod(expr_mod const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " % ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_shift_left(expr_shift_left const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " << ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_shift_right(expr_shift_right const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " >> ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_bitwise_or(expr_bitwise_or const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " | ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_bitwise_and(expr_bitwise_and const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " & ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_bitwise_exor(expr_bitwise_exor const& exp) -> void
{
    dump_expr(exp.lvalue);
    fmt::format_to(std::back_inserter(buf_), " ^ ");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_not(expr_not const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "!");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_negate(expr_negate const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "-");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_complement(expr_complement const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "~");
    dump_expr(exp.rvalue);
}

auto source::dump_expr_new(expr_new const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "new ");
    dump_expr_identifier(*exp.name);
    fmt::format_to(std::back_inserter(buf_), "()");
}

auto source::dump_expr_call(expr_call const& exp) -> void
{
    dump_call(exp.value);
}

auto source::dump_expr_method(expr_method const& exp) -> void
{
    dump_expr(exp.obj);
    fmt::format_to(std::back_inserter(buf_), " ");
    dump_call(exp.value);
}

auto source::dump_call(call const& exp) -> void
{
    switch (exp.as_node->kind())
    {
        case node::expr_function:
            dump_expr_function(*exp.as_function);
            break;
        case node::expr_pointer:
            dump_expr_pointer(*exp.as_pointer);
            break;
        case node::expr_member:
            dump_expr_member(*exp.as_member);
            break;
        default:
            break;
    }
}

auto source::dump_expr_function(expr_function const& exp) -> void
{
    if (exp.mode == call::mode::thread)
        fmt::format_to(std::back_inserter(buf_), "thread ");

    if (!exp.path->value.empty())
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
    if (exp.mode == call::mode::thread)
        fmt::format_to(std::back_inserter(buf_), "thread ");

    fmt::format_to(std::back_inserter(buf_), "[[ ");
    dump_expr(exp.func);
    fmt::format_to(std::back_inserter(buf_), " ]](");
    dump_expr_arguments(*exp.args);
    fmt::format_to(std::back_inserter(buf_), ")");
}

auto source::dump_expr_member(expr_member const& exp) -> void
{
    if (exp.mode == call::mode::thread)
        fmt::format_to(std::back_inserter(buf_), "thread ");

    fmt::format_to(std::back_inserter(buf_), "[[ ");
    dump_expr(exp.obj);
    fmt::format_to(std::back_inserter(buf_), " ]]->");
    dump_expr_identifier(*exp.name);
    fmt::format_to(std::back_inserter(buf_), "(");
    dump_expr_arguments(*exp.args);
    fmt::format_to(std::back_inserter(buf_), ")");
}

auto source::dump_expr_parameters(expr_parameters const& exp) -> void
{
    for (auto const& entry : exp.list)
    {
        fmt::format_to(std::back_inserter(buf_), " ");
        dump_expr(entry);

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
        dump_expr(entry);

        if (&entry != &exp.list.back())
            fmt::format_to(std::back_inserter(buf_), ",");
        else
            fmt::format_to(std::back_inserter(buf_), " ");
    }
}

auto source::dump_expr_isdefined(expr_isdefined const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "isdefined( ");
    dump_expr(exp.value);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_vectorscale(expr_vectorscale const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "vectorscale( ");
    dump_expr(exp.arg1);
    fmt::format_to(std::back_inserter(buf_), ", ");
    dump_expr(exp.arg2);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_anglestoup(expr_anglestoup const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "anglestoup( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_anglestoright(expr_anglestoright const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "anglestoright( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_anglestoforward(expr_anglestoforward const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "anglestoforward( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_angleclamp180(expr_angleclamp180 const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "angleclamp180( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_vectortoangles(expr_vectortoangles const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "vectorangles( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_abs(expr_abs const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "abs( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_gettime(expr_gettime const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "gettime()");
}

auto source::dump_expr_getdvar(expr_getdvar const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "getdvar( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_getdvarint(expr_getdvarint const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "getdvarint( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_getdvarfloat(expr_getdvarfloat const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "getdvarflaot( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_getdvarvector(expr_getdvarvector const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "getdvarvector( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_getdvarcolorred(expr_getdvarcolorred const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "getdvarcolorred( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_getdvarcolorgreen(expr_getdvarcolorgreen const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "getdvarcolorgreen( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_getdvarcolorblue(expr_getdvarcolorblue const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "getdvarcolorblue( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_getdvarcoloralpha(expr_getdvarcoloralpha const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "getdvarcoloralpha( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_getfirstarraykey(expr_getfirstarraykey const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "getfirstarraykey( ");
    dump_expr(exp.arg);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_getnextarraykey(expr_getnextarraykey const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "getnextarraykey( ");
    dump_expr(exp.arg1);
    fmt::format_to(std::back_inserter(buf_), ", ");
    dump_expr(exp.arg2);
    fmt::format_to(std::back_inserter(buf_), " )");
}

auto source::dump_expr_reference(expr_reference const& exp) -> void
{
    dump_expr_path(*exp.path);
    fmt::format_to(std::back_inserter(buf_), "::");
    dump_expr_identifier(*exp.name);
}

auto source::dump_expr_array(expr_array const& exp) -> void
{
    dump_expr(exp.obj);
    fmt::format_to(std::back_inserter(buf_), "[");
    dump_expr(exp.key);
    fmt::format_to(std::back_inserter(buf_), "]");
}

auto source::dump_expr_field(expr_field const& exp) -> void
{
    dump_expr(exp.obj);
    fmt::format_to(std::back_inserter(buf_), ".");
    dump_expr_identifier(*exp.field);
}

auto source::dump_expr_size(expr_size const& exp) -> void
{
    dump_expr(exp.obj);
    fmt::format_to(std::back_inserter(buf_), ".size");
}

auto source::dump_expr_paren(expr_paren const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "( ");
    dump_expr(exp.value);
    fmt::format_to(std::back_inserter(buf_), " )");
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

auto source::dump_expr_world(expr_world const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "world");
}

auto source::dump_expr_classes(expr_classes const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "classes");
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

auto source::dump_expr_hash(expr_hash const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "{}", utils::string::to_literal(exp.value));
}

auto source::dump_expr_vector(expr_vector const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "( ");
    dump_expr(exp.x);
    fmt::format_to(std::back_inserter(buf_), ", ");
    dump_expr(exp.y);
    fmt::format_to(std::back_inserter(buf_), ", ");
    dump_expr(exp.z);
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

auto source::dump_asm_loc(asm_loc const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_loc( {} )", exp.value);
}

auto source::dump_asm_jmp(asm_jmp const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_jmp( {} )", exp.value);
}

auto source::dump_asm_jmp_back(asm_jmp_back const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_jmp_back( {} )", exp.value);
}

auto source::dump_asm_jmp_cond(asm_jmp_cond const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_jmp_cond( {} )", exp.value);
}

auto source::dump_asm_jmp_true(asm_jmp_true const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_jmp_expr_true( {} )", exp.value);
}

auto source::dump_asm_jmp_false(asm_jmp_false const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_jmp_expr_false( {} )", exp.value);
}

auto source::dump_asm_switch(asm_switch const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_switch( {} )", exp.value);
}

auto source::dump_asm_endswitch(asm_endswitch const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_endswitch()");
}

auto source::dump_asm_prescriptcall(asm_prescriptcall const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_prescriptcall()");
}

auto source::dump_asm_voidcodepos(asm_voidcodepos const&) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_voidcodepos()");
}

auto source::dump_asm_dev(asm_dev const& exp) -> void
{
    fmt::format_to(std::back_inserter(buf_), "__asm_dev( {} )", exp.value);
}

} // namespace xsk::arc
