// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "iw8.hpp"
#include "parser.hpp"
#include "lexer.hpp"

xsk::gsc::iw8::parser::symbol_type IW8lex(xsk::gsc::iw8::lexer& lexer)
{
    return lexer.lex();
}

namespace xsk::gsc::iw8
{

enum class keyword
{
/*  KW_pre_define,
    KW_pre_undef,
    KW_pre_ifdef,
    KW_pre_ifndef,
    KW_pre_if,
    KW_pre_elif,
    KW_pre_else,
    KW_pre_endif,*/
    KW_pre_inline,
    KW_pre_include,
    KW_pre_using_animtree,
    KW_pre_animtree,
    KW_endon,
    KW_notify,
    KW_wait,
    KW_waittill,
    KW_waittillmatch,
    KW_waittillframeend,
    KW_waitframe,
    KW_if,
    KW_else,
    KW_do,
    KW_while,
    KW_for,
    KW_foreach,
    KW_in,
    KW_switch,
    KW_case,
    KW_default,
    KW_break,
    KW_continue,
    KW_return,
    KW_breakpoint,
    KW_prof_begin,
    KW_prof_end,
    KW_thread,
    KW_childthread,
    KW_thisthread,
    KW_call,
    KW_true,
    KW_false,
    KW_undefined,
    KW_dotsize,
    KW_game,
    KW_self,
    KW_anim,
    KW_level,
    KW_isdefined,
    KW_istrue,
    KW_INVALID,
};

buffer::buffer() : size(1024), length(0)
{
    data = static_cast<char*>(std::malloc(size));
}

buffer::~buffer()
{
    if(data) std::free(data);
}

bool buffer::push(char c)
{
    if(length >= size)
    {
        auto nsize = size * 2;
        auto ndata = reinterpret_cast<char*>(std::malloc(nsize));

        if(!ndata) return false;

        std::memmove(ndata, data, size);
        std::free(data);
        size = nsize;
        data = ndata;
    }
    data[length++] = c;
    return true;
}

reader::reader() : state(reader::end), buffer_pos(0), bytes_remaining(0), last_byte(0), current_byte(0)
{

}

void reader::init(const char* data, size_t size)
{
    if(data && size)
    {
        state = reader::ok;
        buffer_pos = data;
        bytes_remaining = size;
        last_byte = 0;
        current_byte = *data;
    }
    else
    {
        state = reader::end;
        buffer_pos = 0;
        bytes_remaining = 0;
        last_byte = 0;
        current_byte = 0;
    }
}

void reader::advance()
{
    ++buffer_pos;

    if(bytes_remaining-- == 1)
    {
        state = reader::end;
        bytes_remaining = 0;
        last_byte = current_byte;
        current_byte = 0;
    }
    else
    {
        last_byte = current_byte;
        current_byte = *buffer_pos;
    }
}

lexer::lexer(const std::string& name, const char* data, size_t size) : in_dev_state_(false), loc_(xsk::gsc::location(&name)),
    mode_(build::dev), header_top_(0), locs_(std::stack<location>()), readers_(std::stack<reader>())
{
    reader_.init(data, size);
}

void lexer::push_header(const std::string& file)
{
    try
    {
        if (header_top_++ >= 10)
            throw xsk::gsc::error("maximum gsh depth exceeded '10'");

        auto data = resolver::file_data(file + ".gsh");

        readers_.push(reader_);
        locs_.push(loc_);
        loc_.initialize(std::get<0>(data));
        reader_.init(std::get<1>(data), std::get<2>(data));
    }
    catch (const std::exception& e)
    {
        throw xsk::gsc::error("parsing header file '" + file + "': " + e.what());
    }
}

void lexer::pop_header()
{
    header_top_--;
    loc_ = locs_.top();
    locs_.pop();
    reader_ = readers_.top();
    readers_.pop();
}

void lexer::restrict_header(const xsk::gsc::location& loc)
{
    if (header_top_ > 0)
    {
        throw comp_error(loc, "not allowed inside a gsh file");
    }
}

auto lexer::lex() -> xsk::gsc::iw8::parser::symbol_type
{
    buffer_.length = 0;
    loc_.step();

    while (true)
    {
        if (reader_.state == reader::end)
        {
            if (in_dev_state_)
                throw iw8::parser::syntax_error(loc_, "unmatched devblock start ('/#')");

            if(header_top_ > 0)
                pop_header();
            else
                return iw8::parser::make_IW8EOF(loc_);
        }

        reader_.advance();
        auto& last = reader_.last_byte;
        auto& curr = reader_.current_byte;

        switch (last)
        {
            case ' ':
            case '\t':
            case '\r':
                loc_.step();
                continue;
            case '\n':
                loc_.lines();
                loc_.step();
                continue;
            case '/':
                if(reader_.state == reader::end || (curr != '/' && curr != '*' && curr != '#' && curr != '='))
                    return iw8::parser::make_DIV(loc_);

                reader_.advance();

                if (last == '=')
                    return iw8::parser::make_ASSIGN_DIV(loc_);

                if (last == '#')
                {
                    if (in_dev_state_)
                    {
                        throw iw8::parser::syntax_error(loc_, "cannot recurse devblock ('/#')");
                    }
                    else if (mode_ == xsk::gsc::build::dev)
                    {
                        in_dev_state_ = true;
                        return iw8::parser::make_DEVBEGIN(loc_);
                    }
                    else
                    {
                        while (true)
                        {
                            if (reader_.state == reader::end)
                            {
                                throw iw8::parser::syntax_error(loc_, "unmatched devblock start ('/#')");
                            }
                            else if (curr == '\n')
                            {
                                loc_.lines();
                                loc_.step();
                            }
                            else if (reader_.state == reader::ok && last == '#' && curr == '/')
                            {
                                reader_.advance();
                                break;
                            }

                            reader_.advance();
                        }
                    }
                }
                else if (last == '*')
                {
                    while (true)
                    {
                        if (reader_.state == reader::end)
                        {
                            throw iw8::parser::syntax_error(loc_, "unmatched multiline comment start ('/*')");
                        }
                        else if (curr == '\n')
                        {
                            loc_.lines();
                            loc_.step();
                        }
                        else if (reader_.state == reader::ok && last  == '*' && curr == '/')
                        {
                            reader_.advance();
                            break;
                        }

                        reader_.advance();
                    }
                }
                else if (last == '/')
                {
                    while (true)
                    {
                        if (reader_.state == reader::end || curr == '\n')
                            break;

                        reader_.advance();
                    }
                }
                continue;
            case '#':
                if (curr == '/')
                {
                    if (!in_dev_state_)
                        throw iw8::parser::syntax_error(loc_, "unmatched devblock end ('#/')");

                    in_dev_state_ = false;
                    reader_.advance();
                    return iw8::parser::make_DEVEND(loc_);
                }

                buffer_.push(last);
                while (reader_.state == reader::ok)
                {
                    if (!(curr == '_' || (curr > 64 && curr < 91) || (curr > 96 && curr < 123) || (curr > 47 && curr < 58)))
                        break;

                    if (!buffer_.push(curr))
                        throw error("gsc lexer: out of memory!");

                    reader_.advance();
                }

                {
                    if (auto len = buffer_.length; len == 4 || len == 7)
                    {
                        auto data = buffer_.data;
                        auto color = true;
                        for (auto i = 1; i < len; i++)
                        {
                            if ((data[i] < 48 || data[i] > 57) && (data[i] < 65 || data[i] > 70) && (data[i] < 97 || data[i] > 102))
                            {
                                color = false;
                                break;
                            }      
                        }

                        if (color) return iw8::parser::make_COLOR(std::string(++data, --len), loc_);
                    }

                    auto key = get_keyword(std::string_view(buffer_.data, buffer_.length));

                    if (key == keyword::KW_INVALID)
                        throw iw8::parser::syntax_error(loc_, utils::string::va("unknown preprocessor directive ('%s')", "#"));
            
                    if (keyword_is_token(key))
                        return keyword_token(key);

                    // call preprocessor(key);                
                }
                continue;
            case '*':
                if (reader_.state == reader::end || (curr != '/' && curr != '='))
                    return iw8::parser::make_MUL(loc_);
                
                reader_.advance();

                if (curr == '/')
                    throw iw8::parser::syntax_error(loc_, "unmatched multiline comment end ('*/')");

                return iw8::parser::make_ASSIGN_MUL(loc_);
            case '"':
            case '\'':
                return read_string(last, false);
            case '.':
                return read_dotsize();
            case '(':
                return iw8::parser::make_LPAREN(loc_);
            case ')':
                return iw8::parser::make_RPAREN(loc_);
            case '{':
                return iw8::parser::make_LBRACE(loc_);
            case '}':
                return iw8::parser::make_RBRACE(loc_);
            case '[':
                return iw8::parser::make_LBRACKET(loc_);
            case ']':
                return iw8::parser::make_RBRACKET(loc_);
            case ',':
                return iw8::parser::make_COMMA(loc_);
            case ';':
                return iw8::parser::make_SEMICOLON(loc_);
            case ':':
                if (curr != ':')
                    return iw8::parser::make_COLON(loc_);
                reader_.advance();
                return iw8::parser::make_DOUBLECOLON(loc_);
            case '?':
                return iw8::parser::make_QMARK(loc_);
            case '=':
                if (curr != '=')
                    return iw8::parser::make_ASSIGN(loc_);
                reader_.advance();
                return iw8::parser::make_EQUALITY(loc_);
            case '+':
                if (curr != '+' && curr != '=')
                    return iw8::parser::make_ADD(loc_);
                reader_.advance();
                return (last == '+') ? iw8::parser::make_INCREMENT(loc_) : iw8::parser::make_ASSIGN_ADD(loc_);
            case '-':
                if (curr != '-' && curr != '=')
                    return iw8::parser::make_SUB(loc_);
                reader_.advance();
                return (last == '-') ? iw8::parser::make_DECREMENT(loc_) : iw8::parser::make_ASSIGN_SUB(loc_);
            case '%':
                if (curr != '=')
                    return iw8::parser::make_MOD(loc_);
                reader_.advance();
                return iw8::parser::make_ASSIGN_MOD(loc_);                
            case '|':
                if (curr != '|' && curr != '=')
                    return iw8::parser::make_BITWISE_OR(loc_);
                reader_.advance();
                return (last == '|') ? iw8::parser::make_OR(loc_) : iw8::parser::make_ASSIGN_BW_OR(loc_); 
            case '&':
                if (curr != '&' && curr != '=' && curr != '"' && curr != '\'')
                    return iw8::parser::make_BITWISE_AND(loc_);
                reader_.advance();
                if (last == '"' || last == '\'')
                    return read_string(last, true);
                return (last == '&') ? iw8::parser::make_AND(loc_) : iw8::parser::make_ASSIGN_BW_AND(loc_); 
            case '^':
                if (curr != '=')
                    return iw8::parser::make_BITWISE_EXOR(loc_);
                reader_.advance();
                return iw8::parser::make_ASSIGN_BW_EXOR(loc_); 
            case '!':
                if (curr != '=')
                    return iw8::parser::make_NOT(loc_);
                reader_.advance();
                return iw8::parser::make_INEQUALITY(loc_);
            case '~':
                return iw8::parser::make_COMPLEMENT(loc_);
            case '<':
                if (curr != '<' && curr != '=')
                    return iw8::parser::make_LESS(loc_);
                reader_.advance();
                if (last == '<')
                {
                    reader_.advance();
                    return (last == '=') ? iw8::parser::make_ASSIGN_LSHIFT(loc_) : iw8::parser::make_LSHIFT(loc_);
                }
                return iw8::parser::make_LESS_EQUAL(loc_);
            case '>':
                if (curr != '>' && curr != '=')
                    return iw8::parser::make_GREATER(loc_);
                reader_.advance();
                if (last == '>')
                {
                    reader_.advance();
                    return (last == '=') ? iw8::parser::make_ASSIGN_RSHIFT(loc_) : iw8::parser::make_RSHIFT(loc_);
                }
                return iw8::parser::make_GREATER_EQUAL(loc_);
            default:
                if (last >= '0' && last <= '9')
                    return lexer::read_number(last);
                else if (last == '_' || last >= 'A' && last <= 'Z' || last >= 'a' && last <= 'z')
                    return lexer::read_word(last);

                throw iw8::parser::syntax_error(loc_, utils::string::va("bad token: \'%c\'", last));
        }
    }
}

auto lexer::read_string(char quote, bool localize) -> xsk::gsc::iw8::parser::symbol_type
{
    if (localize)
        reader_.advance();

    while (reader_.state == reader::ok)
    {
        auto last = reader_.last_byte;
        auto curr = reader_.current_byte;

        reader_.advance();

        if (last == '\n')
            throw iw8::parser::syntax_error(loc_, "unterminated string");

        if (last == '\\') // process scapes
        {
            // TODO:
        }

        if (last != '\\' && curr == quote)
            break;

        if (!buffer_.push(curr))
            throw error("gsc lexer: out of memory!");
    }

    if (reader_.state == reader::end)
    {
        throw iw8::parser::syntax_error(loc_, utils::string::va("unmatched string start ('%s')", (quote == '"') ? "\"" : "\\'"));
    }

    if (localize)
        return iw8::parser::make_ISTRING(std::string(buffer_.data, buffer_.length), loc_);

    return iw8::parser::make_STRING(std::string(buffer_.data, buffer_.length), loc_);
}

auto lexer::read_number(char first) -> xsk::gsc::iw8::parser::symbol_type
{
    if (first == '.')
    {
        buffer_.push(first);

        while (reader_.state == reader::ok)
        {
            auto last = reader_.last_byte;
            auto curr = reader_.current_byte;

            if (curr == '\'' && (last == '\'' || last == 'f' || last == '.'))
                throw iw8::parser::syntax_error(loc_, "invalid number '\''");

            if ((curr == '.' || curr == 'f') && last == '\'')
                throw iw8::parser::syntax_error(loc_, "invalid number '\''");

            if (curr == '\'')
            {
                reader_.advance();
                continue;
            }

            if (!(curr == 'f' || curr == '.' || (curr > 47 && curr < 58)))
                break;

            if (!buffer_.push(curr))
                throw error("gsc lexer: out of memory!");

            reader_.advance();
        }

        if (reader_.last_byte == '\'')
            throw iw8::parser::syntax_error(loc_, "invalid number '\''");

        auto data = buffer_.data;
        auto len = buffer_.length;
        auto dot = true;

        for (auto i = 1; i < len; i++)
        {
            if (data[i] == '.')
            {
                if (dot)
                    throw iw8::parser::syntax_error(loc_, "invalid number '.'");
            }
            if (data[i] == 'f' && i != len - 1)
                throw iw8::parser::syntax_error(loc_, "invalid number 'f'");
        }

        return iw8::parser::make_FLOAT(std::string(data, len), loc_);
    }
    else
    {
        auto curr = reader_.current_byte;

        if (first == '0' && curr == 'o')
        {
            buffer_.push(first);
            buffer_.push('o');
            reader_.advance();

            while (reader_.state == reader::ok)
            {
                auto last = reader_.last_byte;
                auto curr = reader_.current_byte;

                if (curr == '\'' && (last == '\'' || last == 'o'))
                    throw iw8::parser::syntax_error(loc_, "invalid number '\''");

                if (curr == 'o' && last == '\'')
                    throw iw8::parser::syntax_error(loc_, "invalid number '\''");

                if (curr == '\'')
                {
                    reader_.advance();
                    continue;
                }

                if (!(curr > 47 && curr < 56))
                    break;

                if (!buffer_.push(curr))
                    throw error("gsc lexer: out of memory!");

                reader_.advance();
            }

            if (reader_.last_byte == '\'')
                throw iw8::parser::syntax_error(loc_, "invalid number '\''");

            if (buffer_.length < 3)
                throw error("gsc lexer: invalid octal literal!");

            return iw8::parser::make_INTEGER(xsk::utils::string::oct_to_dec(buffer_.data + 2), loc_);
        }
        else if (first == '0' && curr == 'b')
        {
            buffer_.push(first);
            buffer_.push('b');
            reader_.advance();

            while (reader_.state == reader::ok)
            {
                auto last = reader_.last_byte;
                auto curr = reader_.current_byte;

                if (curr == '\'' && (last == '\'' || last == 'b'))
                    throw iw8::parser::syntax_error(loc_, "invalid number '\''");

                if (curr == 'b' && last == '\'')
                    throw iw8::parser::syntax_error(loc_, "invalid number '\''");

                if (curr == '\'')
                {
                    reader_.advance();
                    continue;
                }

                if (curr != '0' && curr != '1')
                    break;

                if (!buffer_.push(curr))
                    throw error("gsc lexer: out of memory!");

                reader_.advance();
            }

            if (reader_.last_byte == '\'')
                throw iw8::parser::syntax_error(loc_, "invalid number '\''");

            if (buffer_.length < 3)
                throw error("gsc lexer: invalid binary literal!");

            return iw8::parser::make_INTEGER(xsk::utils::string::bin_to_dec(buffer_.data), loc_);
        }
        else if (first == '0' && curr == 'x')
        {
            buffer_.push(first);
            buffer_.push('x');
            reader_.advance();

            while (reader_.state == reader::ok)
            {
                auto last = reader_.last_byte;
                auto curr = reader_.current_byte;

                if (curr == '\'' && (last == '\'' || last == 'x'))
                    throw iw8::parser::syntax_error(loc_, "invalid number '\''");

                if (curr == 'x' && last == '\'')
                    throw iw8::parser::syntax_error(loc_, "invalid number '\''");

                if (curr == '\'')
                {
                    reader_.advance();
                    continue;
                }

                if (!((curr > 47 && curr < 58) || (curr > 64 && curr < 71) || (curr > 96 && curr < 103)))
                    break;

                if (!buffer_.push(curr))
                    throw error("gsc lexer: out of memory!");

                reader_.advance();
            }

            if (reader_.last_byte == '\'')
                throw iw8::parser::syntax_error(loc_, "invalid number '\''");

            if (buffer_.length < 3)
                throw error("gsc lexer: invalid hexadecimal literal!");

            return iw8::parser::make_INTEGER(xsk::utils::string::hex_to_dec(buffer_.data), loc_);
        }
        else
        {
            buffer_.push(first);

            while (reader_.state == reader::ok)
            {
                auto last = reader_.last_byte;
                auto curr = reader_.current_byte;

                if (curr == '\'' && (last == '\'' || last == 'f' || last == '.'))
                    throw iw8::parser::syntax_error(loc_, "invalid number '\''");

                if ((curr == '.' || curr == 'f') && last == '\'')
                    throw iw8::parser::syntax_error(loc_, "invalid number '\''");

                if (curr == '\'')
                {
                    reader_.advance();
                    continue;
                }

                if (!(curr == 'f' || curr == '.' || (curr > 47 && curr < 58)))
                    break;

                if (!buffer_.push(curr))
                    throw error("gsc lexer: out of memory!");

                reader_.advance();
            }

            if (reader_.last_byte == '\'')
                throw iw8::parser::syntax_error(loc_, "invalid number '\''");

            auto data = buffer_.data;
            auto len = buffer_.length;
            auto dot = false;

            for (auto i = 1; i < len; i++)
            {
                if (data[i] == '.')
                {
                    if (dot)
                        throw iw8::parser::syntax_error(loc_, "invalid number '.'");

                    dot = true;
                }
                if (data[i] == 'f' && i != len - 1)
                    throw iw8::parser::syntax_error(loc_, "invalid number 'f'");
            }

            if (dot || data[len - 1] == 'f')
                return iw8::parser::make_FLOAT(std::string(data, len), loc_);

            return iw8::parser::make_INTEGER(std::string(data, len), loc_);
        }
    }
}

auto lexer::read_word(char first) -> xsk::gsc::iw8::parser::symbol_type
{
    auto path = false;

    buffer_.push(first);

    while (reader_.state == reader::ok)
    {
        auto curr = reader_.current_byte;

        if (!(curr == '\\' || curr == '_' || (curr > 64 && curr < 91) || (curr > 96 && curr < 123) || (curr > 47 && curr < 58)))
            break;

        if (curr == '\\')
        {
            if (reader_.last_byte == '\\')
                throw iw8::parser::syntax_error(loc_, "invalid path '\\\\'");

            path = true;
            curr = '/';
        }

        if (!buffer_.push(curr))
            throw error("gsc lexer: out of memory!");

        reader_.advance();
    }

    if(buffer_.data[0] != '_')
    {
        for(auto i = 0; i < buffer_.length; i++)
        {
            auto c = buffer_.data[i];

            if (c > 64 && c < 91)
                buffer_.data[i] = c + 32;
        }
    }

    auto key = get_keyword(std::string_view(buffer_.data, buffer_.length));

    if (key != keyword::KW_INVALID)
        return keyword_token(key);

    if (path)
    {
        if (buffer_.data[buffer_.length - 1] == '/')
            throw iw8::parser::syntax_error(loc_, "invalid path end '\\'");

        return iw8::parser::make_PATH(xsk::gsc::iw8::resolver::make_token(std::string_view(buffer_.data, buffer_.length)), loc_);
    }

    return iw8::parser::make_IDENTIFIER(xsk::gsc::iw8::resolver::make_token(std::string_view(buffer_.data, buffer_.length)), loc_);
}

auto lexer::read_dotsize() -> xsk::gsc::iw8::parser::symbol_type
{
    auto curr = reader_.current_byte;

    if (curr > 47 && curr < 58)
    {
        return lexer::read_number('.');
    }
    else if (curr == '_' || curr > 64 && curr < 91 || curr > 96 && curr < 123)
    {
        reader save;
        save.state = reader_.state;
        save.bytes_remaining = reader_.bytes_remaining;
        save.buffer_pos = reader_.buffer_pos;
        save.last_byte = reader_.last_byte;
        save.current_byte = reader_.current_byte;

        while (reader_.state == reader::ok)
        {
            curr = reader_.current_byte;

            if (!(curr == '_' || (curr > 64 && curr < 91) || (curr > 96 && curr < 123)))
                break;

            if (!buffer_.push(curr))
                throw error("gsc lexer: out of memory!");

            reader_.advance();
        }

        if (std::string_view(buffer_.data, buffer_.length) == "size")
        {
            return iw8::parser::make_SIZE(loc_);
        }

        reader_.state = save.state;
        reader_.bytes_remaining = save.bytes_remaining;
        reader_.buffer_pos = save.buffer_pos;
        reader_.last_byte = save.last_byte;
        reader_.current_byte = save.current_byte;

        return iw8::parser::make_DOT(loc_);

    }
    else return iw8::parser::make_DOT(loc_);
}

auto lexer::keyword_token(keyword k) -> xsk::gsc::iw8::parser::symbol_type
{
    switch (k)
    {
        case keyword::KW_pre_inline:
            return iw8::parser::make_INLINE(loc_);
        case keyword::KW_pre_include:
            return iw8::parser::make_INCLUDE(loc_);
        case keyword::KW_pre_using_animtree:
            return iw8::parser::make_USINGTREE(loc_);
        case keyword::KW_pre_animtree:
            return iw8::parser::make_ANIMTREE(loc_);
        case keyword::KW_endon:
            return iw8::parser::make_ENDON(loc_);
        case keyword::KW_notify:
            return iw8::parser::make_NOTIFY(loc_);
        case keyword::KW_wait:
            return iw8::parser::make_WAIT(loc_);
        case keyword::KW_waittill:
            return iw8::parser::make_WAITTILL(loc_);
        case keyword::KW_waittillmatch:
            return iw8::parser::make_WAITTILLMATCH(loc_);
        case keyword::KW_waittillframeend:
            return iw8::parser::make_WAITTILLFRAMEEND(loc_);
        case keyword::KW_waitframe:
            return iw8::parser::make_WAITFRAME(loc_);
        case keyword::KW_if:
            return iw8::parser::make_IF(loc_);
        case keyword::KW_else:
            return iw8::parser::make_ELSE(loc_);
        case keyword::KW_do:
            return iw8::parser::make_DO(loc_);
        case keyword::KW_while:
            return iw8::parser::make_WHILE(loc_);
        case keyword::KW_for:
            return iw8::parser::make_FOR(loc_);
        case keyword::KW_foreach:
            return iw8::parser::make_FOREACH(loc_);
        case keyword::KW_in:
            return iw8::parser::make_IN(loc_);
        case keyword::KW_switch:
            return iw8::parser::make_SWITCH(loc_);
        case keyword::KW_case:
            return iw8::parser::make_CASE(loc_);
        case keyword::KW_default:
            return iw8::parser::make_DEFAULT(loc_);
        case keyword::KW_break:
            return iw8::parser::make_BREAK(loc_);
        case keyword::KW_continue:
            return iw8::parser::make_CONTINUE(loc_);
        case keyword::KW_return:
            return iw8::parser::make_RETURN(loc_);
        case keyword::KW_breakpoint:
            return iw8::parser::make_BREAKPOINT(loc_);
        case keyword::KW_prof_begin:
            return iw8::parser::make_PROFBEGIN(loc_);
        case keyword::KW_prof_end:
            return iw8::parser::make_PROFEND(loc_);
        case keyword::KW_thread:
            return iw8::parser::make_THREAD(loc_);
        case keyword::KW_childthread:
            return iw8::parser::make_CHILDTHREAD(loc_);
        case keyword::KW_thisthread:
            return iw8::parser::make_THISTHREAD(loc_);
        case keyword::KW_call:
            return iw8::parser::make_CALL(loc_);
        case keyword::KW_true:
            return iw8::parser::make_TRUE(loc_);
        case keyword::KW_false:
        return iw8::parser::make_FALSE(loc_);
        case keyword::KW_undefined:
            return iw8::parser::make_UNDEFINED(loc_);
        case keyword::KW_dotsize:
            return iw8::parser::make_SIZE(loc_);
        case keyword::KW_game:
            return iw8::parser::make_GAME(loc_);
        case keyword::KW_self:
            return iw8::parser::make_SELF(loc_);
        case keyword::KW_anim:
            return iw8::parser::make_ANIM(loc_);
        case keyword::KW_level:
            return iw8::parser::make_LEVEL(loc_);
        case keyword::KW_isdefined:
            return iw8::parser::make_ISDEFINED(loc_);
        case keyword::KW_istrue:
            return iw8::parser::make_ISTRUE(loc_);
        default:
            throw error("gsc lexer: INVALID KEYWORD TOKEN!");
    }
}

auto lexer::keyword_is_token(keyword k) -> bool
{
    switch (k)
    {
/*      case keyword::KW_pre_define:
        case keyword::KW_pre_undef:
        case keyword::KW_pre_ifdef:
        case keyword::KW_pre_ifndef:
        case keyword::KW_pre_if:
        case keyword::KW_pre_elif:
        case keyword::KW_pre_else:
        case keyword::KW_pre_endif:*/
        case keyword::KW_INVALID:
            return false;
        default:
            return true;
    }
}

auto lexer::get_keyword(std::string_view str) -> keyword
{
    auto itr = keywords.find(str);

    if(itr != keywords.end())
    {
        return itr->second;
    }

    return keyword::KW_INVALID;
}

std::unordered_map<std::string_view, keyword> lexer::keywords
{{
/*  { "#define", keyword::KW_pre_define },
    { "#undef", keyword::KW_pre_undef },
    { "#ifdef", keyword::KW_pre_ifdef },
    { "#ifndef", keyword::KW_pre_ifndef },
    { "#if", keyword::KW_pre_if },
    { "#elif", keyword::KW_pre_elif },
    { "#else", keyword::KW_pre_else },
    { "#endif", keyword::KW_pre_endif },*/
    { "#inline", keyword::KW_pre_inline },
    { "#include", keyword::KW_pre_include },
    { "#using_animtree", keyword::KW_pre_using_animtree },
    { "#animtree", keyword::KW_pre_animtree },
    { "endon", keyword::KW_endon },
    { "notify", keyword::KW_notify },
    { "wait", keyword::KW_wait },
    { "waittill", keyword::KW_waittill },
    { "waittillmatch", keyword::KW_waittillmatch },
    { "waittillframeend", keyword::KW_waittillframeend },
    { "waitframe", keyword::KW_waitframe },
    { "if", keyword::KW_if },
    { "else", keyword::KW_else },
    { "do", keyword::KW_do },
    { "while", keyword::KW_while },
    { "for", keyword::KW_for },
    { "foreach", keyword::KW_foreach },
    { "in", keyword::KW_in },
    { "switch", keyword::KW_switch },
    { "case", keyword::KW_case },
    { "default", keyword::KW_default },
    { "break", keyword::KW_break },
    { "continue", keyword::KW_continue },
    { "return", keyword::KW_return },
    { "breakpoint", keyword::KW_breakpoint },
    { "prof_begin", keyword::KW_prof_begin },
    { "prof_end", keyword::KW_prof_end },
    { "thread", keyword::KW_thread },
    { "childthread", keyword::KW_childthread },
    { "thisthread", keyword::KW_thisthread },
    { "call", keyword::KW_call },
    { "true", keyword::KW_true },
    { "false", keyword::KW_false },
    { "undefined", keyword::KW_undefined },
    { ".size", keyword::KW_dotsize },
    { "game", keyword::KW_game },
    { "self", keyword::KW_self },
    { "anim", keyword::KW_anim },
    { "level", keyword::KW_level },
    { "isdefined", keyword::KW_isdefined },
    { "istrue", keyword::KW_istrue },
}};

} // namespace xsk::gsc::iw8
