// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW6.hpp"

#include "compiler_parser.hpp"
#include "compiler_lexer.hpp"

namespace IW6
{

compiler::compiler()
{

}

void compiler::compile(std::string& buffer)
{
    yyscan_t scanner;
    std::unique_ptr<node> result(nullptr);
    
    // Add the two NUL terminators, required by flex.   
    buffer.append("\0\0", 2);

    if (yylex_init(&scanner))
        exit(1);

    YY_BUFFER_STATE yybuffer = yy_scan_buffer(buffer.data(), buffer.size(), scanner);

    yy::parser parser(scanner, result);
    
    if(parser.parse())
    {
        LOG_ERROR("An error ocurred while parsing file.");
    }

    yy_delete_buffer(yybuffer, scanner);
    yylex_destroy(scanner);

    LOG_INFO("file parsing complete.");

    if(result != nullptr)
    {
        LOG_INFO("starting to compile...");
        compile_tree(std::move(result));
    }
}

auto compiler::output() -> std::vector<std::shared_ptr<function>>
{
    return std::vector<std::shared_ptr<function>>();
}

void compiler::compile_tree(std::unique_ptr<node> tree)
{
    if(tree->type == node_type::script)
    {
        auto script = static_cast<node_script*>(tree.get());

        for(auto& child : script->childs)
        {
            if(child->type == node_type::include)
            {
                emit_include(static_cast<node_include*>(child.get()));
            }
            else if(child->type == node_type::include)
            {
                emit_using_animtree(static_cast<node_using_animtree*>(child.get()));
            }
            else if(child->type == node_type::function)
            {
                emit_function(static_cast<node_function*>(child.get()));
            }
            else
            {
                LOG_ERROR("unexpected script child node.");
            }   
        }
    }
    else
    {
        LOG_ERROR("unexpected root tree node.");
    }
    
}

void compiler::emit_include(node_include* include)
{
    if(include->child->type == node_type::filepath)
    {
        includes_.push_back(static_cast<node_filepath*>(include->child.get())->value);
    }
    else if(include->child->type == node_type::identifier)
    {
        includes_.push_back(static_cast<node_identifier*>(include->child.get())->value);
    }
    else
    {
        LOG_ERROR("unexpected include file name.");
    }
}

void compiler::emit_using_animtree(node_using_animtree* animtree)
{
    if(animtree->child->type == node_type::string)
    {
        animtrees_.push_back(static_cast<node_string*>(animtree->child.get())->value);
    }
    else
    {
        LOG_ERROR("unexpected animtree name.");
    }
}

void compiler::emit_function(node_function* func)
{
    function_ = std::make_shared<function>(); // create a asm function


}

void compiler::emit_parameters(node_parameter_list* params)
{

}

} // namespace IW6
