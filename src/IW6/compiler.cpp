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
        printf("parse error\n");
    }

    yy_delete_buffer(yybuffer, scanner);
    yylex_destroy(scanner);

    // file parse complete, compile...
    
    if(result != nullptr)
    {
        printf("%s\n", result->print().data());
    }
}

auto compiler::output() -> std::vector<std::shared_ptr<function>>
{
    return std::vector<std::shared_ptr<function>>();
}

} // namespace IW6
