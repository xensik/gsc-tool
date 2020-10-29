// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW6.hpp"

#include "parser.hpp"
#include "lexer.hpp"

namespace IW6
{

compiler::compiler()
{

}

void compiler::compile(std::string& buffer)
{
    // Add the two NUL terminators, required by flex.
    // Omit this for yy_scan_bytes(), which allocates, copies and
    // apends these for us.   
    buffer.append("\0", 1).append("\0", 1);
    // Our input file may contain NULs ('\0') so we MUST use
    // yy_scan_buffer() or yy_scan_bytes(). For a normal C (NUL-
    // terminated) string, we are better off using yy_scan_string() and
    // letting flex manage making a copy of it so the original may be a
    // const char (i.e., literal) string.
    yyscan_t scanner;
    if (yylex_init(&scanner)) exit(1);

    YY_BUFFER_STATE yybuffer = yy_scan_buffer(buffer.data(), buffer.size(), scanner);

    node* result = nullptr;

    int token;
    do { token = yyparse(scanner, &result); }
    while (token != 0);

    if(result != nullptr)
    {
        printf("%s\n", result->print().data());
    }
    
    yy_delete_buffer(yybuffer, scanner);
    yylex_destroy(scanner);

    // file parse complete, compile...
    
}

auto compiler::output() -> std::vector<std::shared_ptr<function>>
{
    return std::vector<std::shared_ptr<function>>();
}

} // namespace IW6
