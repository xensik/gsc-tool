// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "s1.hpp"
#include "parser.hpp"
#include "lexer.hpp"

xsk::gsc::s1::parser::symbol_type S1lex(xsk::gsc::s1::lexer& lexer)
{
    return lexer.lex();
}

namespace xsk::gsc::s1
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
    KW_INVALID,
};

buffer::buffer() : length(0)
{
    data = static_cast<char*>(std::malloc(max_buf_size));
}

buffer::~buffer()
{
    if(data) std::free(data);
}

bool buffer::push(char c)
{
    if(length >= max_buf_size)
        return false;

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

lexer::lexer(const std::string& name, const char* data, size_t size) : indev_(false), loc_(xsk::gsc::location(&name)),
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

auto lexer::lex() -> xsk::gsc::s1::parser::symbol_type
{
    buffer_.length = 0;
    state_ = state::start;
    loc_.step();

    while (true)
    {
        const auto& state = reader_.state;
        auto& last = reader_.last_byte;
        auto& curr = reader_.current_byte;
        auto path = false;

        if (state == reader::end)
        {
            if (indev_)
                throw comp_error(loc_, "unmatched devblock start ('/#')");

            if (header_top_ > 0)
                pop_header();
            else
                return s1::parser::make_S1EOF(loc_);
        }

        reader_.advance();

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
                if (curr != '/' && curr != '*' && curr != '#' && curr != '=')
                    return s1::parser::make_DIV(loc_);

                reader_.advance();

                if (last == '=')
                    return s1::parser::make_ASSIGN_DIV(loc_);

                if (last == '#')
                {
                    if (indev_)
                        throw comp_error(loc_, "cannot recurse devblock ('/#')");

                    if (mode_ == xsk::gsc::build::dev)
                    {
                        indev_ = true;
                        return s1::parser::make_DEVBEGIN(loc_);
                    }
                    else
                    {
                        while (true)
                        {
                            if (state == reader::end)
                                throw comp_error(loc_, "unmatched devblock start ('/#')");

                            if (curr == '\n')
                            {
                                loc_.lines();
                                loc_.step();
                            }
                            else if (last == '#' && curr == '/')
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
                        if (state == reader::end)
                            throw comp_error(loc_, "unmatched multiline comment start ('/*')");

                        if (curr == '\n')
                        {
                            loc_.lines();
                            loc_.step();
                        }
                        else if (last  == '*' && curr == '/')
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
                        if (state == reader::end || curr == '\n')
                            break;

                        reader_.advance();
                    }
                }
                continue;
            case '#':
                if (curr == '/')
                {
                    if (!indev_)
                        throw comp_error(loc_, "unmatched devblock end ('#/')");

                    indev_ = false;
                    reader_.advance();
                    return s1::parser::make_DEVEND(loc_);
                }

                buffer_.push(last);
                reader_.advance();

                if (state == reader::end || !((last > 64 && last < 91) || (last > 96 && last < 123)))
                    throw comp_error(loc_, "unterminated preprocessor directive ('#')");

                state_ = state::preprocessor;
                goto lex_name;
            case '*':
                if (curr != '/' && curr != '=')
                    return s1::parser::make_MUL(loc_);

                reader_.advance();

                if (last == '=')
                    return s1::parser::make_ASSIGN_MUL(loc_);

                throw comp_error(loc_, "unmatched multiline comment end ('*/')");
            case '"':
                state_ = state::string;
                goto lex_string;
            case '.':
                reader_.advance();

                if(state == reader::end)
                    throw comp_error(loc_, "unterminated field ('.')");

                state_ = state::field;
                goto lex_name_or_number;
            case '(':
                return s1::parser::make_LPAREN(loc_);
            case ')':
                return s1::parser::make_RPAREN(loc_);
            case '{':
                return s1::parser::make_LBRACE(loc_);
            case '}':
                return s1::parser::make_RBRACE(loc_);
            case '[':
                return s1::parser::make_LBRACKET(loc_);
            case ']':
                return s1::parser::make_RBRACKET(loc_);
            case ',':
                return s1::parser::make_COMMA(loc_);
            case ';':
                return s1::parser::make_SEMICOLON(loc_);
            case ':':
                if (curr != ':')
                    return s1::parser::make_COLON(loc_);

                reader_.advance();
                return s1::parser::make_DOUBLECOLON(loc_);
            case '?':
                return s1::parser::make_QMARK(loc_);
            case '=':
                if (curr != '=')
                    return s1::parser::make_ASSIGN(loc_);

                reader_.advance();
                return s1::parser::make_EQUALITY(loc_);
            case '+':
                if (curr != '+' && curr != '=')
                    return s1::parser::make_ADD(loc_);

                reader_.advance();

                if (last == '+')
                    return s1::parser::make_INCREMENT(loc_);

                return s1::parser::make_ASSIGN_ADD(loc_);
            case '-':
                if (curr != '-' && curr != '=')
                    return s1::parser::make_SUB(loc_);

                reader_.advance();

                if (last == '-')
                    return s1::parser::make_DECREMENT(loc_);

                return s1::parser::make_ASSIGN_SUB(loc_);
            case '%':
                if (curr != '=')
                    return s1::parser::make_MOD(loc_);

                reader_.advance();

                return s1::parser::make_ASSIGN_MOD(loc_);
            case '|':
                if (curr != '|' && curr != '=')
                    return s1::parser::make_BITWISE_OR(loc_);

                reader_.advance();

                if (last == '|')
                    return s1::parser::make_OR(loc_);

                return s1::parser::make_ASSIGN_BW_OR(loc_);
            case '&':
                if (curr != '&' && curr != '=' && curr != '"' && curr != '\'')
                    return s1::parser::make_BITWISE_AND(loc_);

                reader_.advance();

                if (last == '&')
                    return s1::parser::make_AND(loc_);

                if (last == '=')
                    return s1::parser::make_ASSIGN_BW_AND(loc_);

                state_ = state::localize;
                goto lex_string;
            case '^':
                if (curr != '=')
                    return s1::parser::make_BITWISE_EXOR(loc_);

                reader_.advance();
                return s1::parser::make_ASSIGN_BW_EXOR(loc_);
            case '!':
                if (curr != '=')
                    return s1::parser::make_NOT(loc_);

                reader_.advance();
                return s1::parser::make_INEQUALITY(loc_);
            case '~':
                return s1::parser::make_COMPLEMENT(loc_);
            case '<':
                if (curr != '<' && curr != '=')
                    return s1::parser::make_LESS(loc_);

                reader_.advance();
                if (last == '=')
                    return s1::parser::make_LESS_EQUAL(loc_);

                if (curr != '=')
                    return s1::parser::make_LSHIFT(loc_);

                reader_.advance();
                return s1::parser::make_ASSIGN_LSHIFT(loc_);
            case '>':
                if (curr != '>' && curr != '=')
                    return s1::parser::make_GREATER(loc_);

                reader_.advance();

                if (last == '=')
                    return s1::parser::make_GREATER_EQUAL(loc_);

                if (curr != '=')
                    return s1::parser::make_RSHIFT(loc_);

                reader_.advance();
                return s1::parser::make_ASSIGN_RSHIFT(loc_);
            default:
lex_name_or_number:
                if (last >= '0' && last <= '9')
                    goto lex_number;
                else if (last == '_' || last >= 'A' && last <= 'Z' || last >= 'a' && last <= 'z')
                    goto lex_name;

                throw comp_error(loc_, utils::string::va("bad token: \'%c\'", last));
        }

lex_string:
        if (state == reader::end)
            throw comp_error(loc_, "unmatched string start ('\"')");

        reader_.advance();

        while (true)
        {
            if (last == '"')
                break;

            if (last == '\n')
                throw comp_error(loc_, "unterminated string literal");

            if (state == reader::end)
                throw comp_error(loc_, "unmatched string start ('\"')");

            if (last == '\\')
            {
                char c = curr;
                switch (curr)
                {
                    case 't': c = '\t'; break;
                    case 'r': c = '\r'; break;
                    case 'n': c = '\n'; break;
                    case '"': c = '\"'; break;
                    case '\\': c = '\\'; break;
                    default: break;
                }

                if (!buffer_.push(c))
                    throw comp_error(loc_, "max string size exceeded");

                reader_.advance();
            }
            else if (!buffer_.push(last))
                throw comp_error(loc_, "max string size exceeded");

            reader_.advance();
        }

        if (state_ == state::localize)
            return s1::parser::make_ISTRING(std::string(buffer_.data, buffer_.length), loc_);

        return s1::parser::make_STRING(std::string(buffer_.data, buffer_.length), loc_);

lex_name:
        buffer_.push(last);

        while (true)
        {
            if (state == reader::end)
                break;

            if (!(curr == '\\' || curr == '_' || (curr > 64 && curr < 91) || (curr > 96 && curr < 123) || (curr > 47 && curr < 58)))
                break;

            if (curr == '\\')
            {
                if (last == '\\')
                    throw comp_error(loc_, "invalid path '\\\\'");

                path = true;
                if (!buffer_.push('/'))
                    throw comp_error(loc_, "max string size exceeded");
            }
            else if (!buffer_.push(curr))
                throw comp_error(loc_, "max string size exceeded");

            reader_.advance();
        }

        if(state_ == state::field)
        {
            if (path)
                throw comp_error(loc_, "invalid field token '\\'");

            if (std::string_view(buffer_.data, buffer_.length) == "size")
            {
                return s1::parser::make_SIZE(loc_);
            }

            return s1::parser::make_FIELD(std::string(buffer_.data, buffer_.length), loc_);
        }
        else if (state_ == state::preprocessor)
        {
            if (path)
                throw comp_error(loc_, "invalid preprocessor directive");

            auto key = get_keyword(std::string_view(buffer_.data, buffer_.length));

            if (key != keyword::KW_INVALID)
                return keyword_token(key);

            // TODO: call preprocessor(key);
            throw comp_error(loc_, "unknown preprocessor directive");
            state_ = state::start;
            continue;
        }
        else
        {
            auto key = get_keyword(std::string_view(buffer_.data, buffer_.length));

            if (key != keyword::KW_INVALID)
                return keyword_token(key);

            if (path)
            {
                if (buffer_.data[buffer_.length - 1] == '/')
                    throw comp_error(loc_, "invalid path end '\\'");

                //return s1::parser::make_PATH(xsk::gsc::s1::resolver::make_token(std::string_view(buffer_.data, buffer_.length)), loc_);
                return s1::parser::make_PATH(std::string(buffer_.data, buffer_.length), loc_);
            }

            //return s1::parser::make_IDENTIFIER(xsk::gsc::s1::resolver::make_token(std::string_view(buffer_.data, buffer_.length)), loc_);
            return s1::parser::make_IDENTIFIER(std::string(buffer_.data, buffer_.length), loc_);
        }

lex_number:
        if (state_ == state::field)
            buffer_.push('.');

        if (state_ == state::field || last == '.' || last != '0' || (last == '0' && (curr != 'o' && curr != 'b' && curr != 'x')))
        {
            buffer_.push(last);

            auto dot = 0;
            auto flt = 0;

            while (true)
            {
                if (state == reader::end)
                    break;

                if (curr == '\'' && (last == '\'' || last == 'f' || last == '.'))
                    throw comp_error(loc_, "invalid number literal");

                if ((curr == '.' || curr == 'f') && last == '\'')
                    throw comp_error(loc_, "invalid number literal");

                if (curr == '\'')
                {
                    reader_.advance();
                    continue;
                }

                if (curr == 'f')
                    flt++;
                else if (curr == '.')
                    dot++;
                else if (!(curr > 47 && curr < 58))
                    break;

                if (!buffer_.push(curr))
                    throw comp_error(loc_, "number literal size exceeded");

                reader_.advance();
            }

            if (last == '\'')
                throw comp_error(loc_, "invalid number literal");

            if (state_ == state::field && dot || dot > 1 || flt > 1 || flt && buffer_.data[buffer_.length - 1] != 'f')
                throw comp_error(loc_, "invalid number literal");

            if (state_ == state::field || dot || flt)
                return s1::parser::make_FLOAT(std::string(buffer_.data, buffer_.length), loc_);

            return s1::parser::make_INTEGER(std::string(buffer_.data, buffer_.length), loc_);
        }
        else if (curr == 'o')
        {
            reader_.advance();

            while (true)
            {
                if (state == reader::end)
                    break;

                if (curr == '\'' && (last == '\'' || last == 'o') || (curr == 'o' && last == '\''))
                    throw comp_error(loc_,  "invalid octal literal");

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

            if (last == '\'' || buffer_.length <= 0)
                throw comp_error(loc_, "invalid octal literal");

            return s1::parser::make_INTEGER(xsk::utils::string::oct_to_dec(buffer_.data), loc_);
        }
        else if (curr == 'b')
        {
            buffer_.push(last);
            buffer_.push(curr);
            reader_.advance();

            while (true)
            {
                if (state == reader::end)
                    break;

                if (curr == '\'' && (last == '\'' || last == 'b') || (curr == 'b' && last == '\''))
                    throw comp_error(loc_, "invalid binary literal");

                if (curr == '\'')
                {
                    reader_.advance();
                    continue;
                }

                if (curr != '0' && curr != '1')
                    break;

                if (!buffer_.push(curr))
                    throw comp_error(loc_, "number literal size exceeded");

                reader_.advance();
            }

            if (last == '\'' || buffer_.length < 3)
                throw comp_error(loc_, "invalid binary literal");

            return s1::parser::make_INTEGER(xsk::utils::string::bin_to_dec(buffer_.data), loc_);
        }
        else if (curr == 'x')
        {
            buffer_.push(last);
            buffer_.push(curr);
            reader_.advance();

            while (true)
            {
                if (state == reader::end)
                    break;

                if (curr == '\'' && (last == '\'' || last == 'x') || (curr == 'x' && last == '\''))
                    throw comp_error(loc_, "invalid hexadecimal literal");

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

            if (last == '\'' || buffer_.length < 3)
                throw comp_error(loc_, "invalid hexadecimal literal");

            return s1::parser::make_INTEGER(xsk::utils::string::hex_to_dec(buffer_.data), loc_);
        }
        // cant get here!
    }
}

auto lexer::keyword_token(keyword k) -> xsk::gsc::s1::parser::symbol_type
{
    switch (k)
    {
        case keyword::KW_pre_inline:
            return s1::parser::make_INLINE(loc_);
        case keyword::KW_pre_include:
            return s1::parser::make_INCLUDE(loc_);
        case keyword::KW_pre_using_animtree:
            return s1::parser::make_USINGTREE(loc_);
        case keyword::KW_pre_animtree:
            return s1::parser::make_ANIMTREE(loc_);
        case keyword::KW_endon:
            return s1::parser::make_ENDON(loc_);
        case keyword::KW_notify:
            return s1::parser::make_NOTIFY(loc_);
        case keyword::KW_wait:
            return s1::parser::make_WAIT(loc_);
        case keyword::KW_waittill:
            return s1::parser::make_WAITTILL(loc_);
        case keyword::KW_waittillmatch:
            return s1::parser::make_WAITTILLMATCH(loc_);
        case keyword::KW_waittillframeend:
            return s1::parser::make_WAITTILLFRAMEEND(loc_);
        case keyword::KW_waitframe:
            return s1::parser::make_WAITFRAME(loc_);
        case keyword::KW_if:
            return s1::parser::make_IF(loc_);
        case keyword::KW_else:
            return s1::parser::make_ELSE(loc_);
        case keyword::KW_do:
            return s1::parser::make_DO(loc_);
        case keyword::KW_while:
            return s1::parser::make_WHILE(loc_);
        case keyword::KW_for:
            return s1::parser::make_FOR(loc_);
        case keyword::KW_foreach:
            return s1::parser::make_FOREACH(loc_);
        case keyword::KW_in:
            return s1::parser::make_IN(loc_);
        case keyword::KW_switch:
            return s1::parser::make_SWITCH(loc_);
        case keyword::KW_case:
            return s1::parser::make_CASE(loc_);
        case keyword::KW_default:
            return s1::parser::make_DEFAULT(loc_);
        case keyword::KW_break:
            return s1::parser::make_BREAK(loc_);
        case keyword::KW_continue:
            return s1::parser::make_CONTINUE(loc_);
        case keyword::KW_return:
            return s1::parser::make_RETURN(loc_);
        case keyword::KW_breakpoint:
            return s1::parser::make_BREAKPOINT(loc_);
        case keyword::KW_prof_begin:
            return s1::parser::make_PROFBEGIN(loc_);
        case keyword::KW_prof_end:
            return s1::parser::make_PROFEND(loc_);
        case keyword::KW_thread:
            return s1::parser::make_THREAD(loc_);
        case keyword::KW_childthread:
            return s1::parser::make_CHILDTHREAD(loc_);
        case keyword::KW_thisthread:
            return s1::parser::make_THISTHREAD(loc_);
        case keyword::KW_call:
            return s1::parser::make_CALL(loc_);
        case keyword::KW_true:
            return s1::parser::make_TRUE(loc_);
        case keyword::KW_false:
        return s1::parser::make_FALSE(loc_);
        case keyword::KW_undefined:
            return s1::parser::make_UNDEFINED(loc_);
        case keyword::KW_dotsize:
            return s1::parser::make_SIZE(loc_);
        case keyword::KW_game:
            return s1::parser::make_GAME(loc_);
        case keyword::KW_self:
            return s1::parser::make_SELF(loc_);
        case keyword::KW_anim:
            return s1::parser::make_ANIM(loc_);
        case keyword::KW_level:
            return s1::parser::make_LEVEL(loc_);
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
}};

} // namespace xsk::gsc::s1
