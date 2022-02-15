// Copyright 2022 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"
#include "s2.hpp"
#include "parser.hpp"
#include "lexer.hpp"

xsk::gsc::s2::parser::symbol_type S2lex(xsk::gsc::s2::lexer& lexer)
{
    return lexer.lex();
}

namespace xsk::gsc::s2
{

const std::unordered_map<std::string_view, parser::token::token_kind_type> keyword_map
{{
    { "#define", parser::token::SH_DEFINE },
    { "#undef", parser::token::SH_UNDEF },
    { "#ifdef", parser::token::SH_IFDEF },
    { "#ifndef", parser::token::SH_IFNDEF },
    { "#if", parser::token::SH_IF },
    { "#elif", parser::token::SH_ELIF },
    { "#else", parser::token::SH_ELSE },
    { "#endif", parser::token::SH_ENDIF },
    { "#inline", parser::token::INLINE },
    { "#include", parser::token::INCLUDE },
    { "#using_animtree", parser::token::USINGTREE },
    { "#animtree", parser::token::ANIMTREE },
    { "endon", parser::token::ENDON },
    { "notify", parser::token::NOTIFY },
    { "wait", parser::token::WAIT },
    { "waittill", parser::token::WAITTILL },
    { "waittillmatch", parser::token::WAITTILLMATCH },
    { "waittillframeend", parser::token::WAITTILLFRAMEEND },
    { "waitframe", parser::token::WAITFRAME },
    { "if", parser::token::IF },
    { "else", parser::token::ELSE },
    { "do", parser::token::DO },
    { "while", parser::token::WHILE },
    { "for", parser::token::FOR },
    { "foreach", parser::token::FOREACH },
    { "in", parser::token::IN },
    { "switch", parser::token::SWITCH },
    { "case", parser::token::CASE },
    { "default", parser::token::DEFAULT },
    { "break", parser::token::BREAK },
    { "continue", parser::token::CONTINUE },
    { "return", parser::token::RETURN },
    { "breakpoint", parser::token::BREAKPOINT },
    { "prof_begin", parser::token::PROFBEGIN },
    { "prof_end", parser::token::PROFEND },
    { "thread", parser::token::THREAD },
    { "childthread", parser::token::CHILDTHREAD },
    { "thisthread", parser::token::THISTHREAD },
    { "call", parser::token::CALL },
    { "true", parser::token::TRUE },
    { "false", parser::token::FALSE },
    { "undefined", parser::token::UNDEFINED },
    { "game", parser::token::GAME },
    { "self", parser::token::SELF },
    { "anim", parser::token::ANIM },
    { "level", parser::token::LEVEL },
}};

buffer::buffer() : length(0)
{
    data = static_cast<char*>(std::malloc(max_buf_size));
}

buffer::~buffer()
{
    if (data) std::free(data);
}

bool buffer::push(char c)
{
    if (length >= max_buf_size)
        return false;

    data[length++] = c;
    return true;
}

reader::reader() : state(reader::end), buffer_pos(0), bytes_remaining(0),
    last_byte(0), current_byte(0) { }

void reader::init(const char* data, size_t size)
{
    if (data && size)
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

    if (bytes_remaining-- == 1)
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

lexer::lexer(const std::string& name, const char* data, size_t size) : indev_(false), clean_(true), loc_(location(&name)),
    mode_(build::dev), header_top_(0), locs_(std::stack<location>()), readers_(std::stack<reader>())
{
    reader_.init(data, size);
}

void lexer::push_header(const std::string& file)
{
    try
    {
        if (header_top_++ >= 10)
            throw comp_error(loc_, "maximum gsh depth exceeded '10'");

        auto data = resolver::file_data(file + ".gsh");

        readers_.push(reader_);
        locs_.push(loc_);
        loc_.initialize(std::get<0>(data));
        reader_.init(std::get<1>(data), std::get<2>(data));
        clean_ = true;
    }
    catch (const std::exception& e)
    {
        throw error("parsing header file '" + file + "': " + e.what());
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

void lexer::ban_header(const location& loc)
{
    if (header_top_ > 0)
    {
        throw comp_error(loc, "not allowed inside a gsh file");
    }
}

auto lexer::lex() -> parser::symbol_type
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
                return parser::make_S2EOF(loc_);
        }

        if (clean_ && last != 0 && last != ' ' && last != '\t' && last != '\n')
            clean_ = false;

        advance();

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
                clean_ = true;
                continue;
            case '\\':
                throw comp_error(loc_, "invalid token ('\\')");
            case '/':
                if (curr != '/' && curr != '*' && curr != '#' && curr != '=')
                    return parser::make_DIV(loc_);

                advance();

                if (last == '=')
                    return parser::make_ASSIGN_DIV(loc_);

                if (last == '#')
                {
                    if (indev_)
                        throw comp_error(loc_, "cannot recurse devblock ('/#')");

                    if (mode_ == build::dev)
                    {
                        indev_ = true;
                        return parser::make_DEVBEGIN(loc_);
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
                        if (state == reader::end)
                            break;

                        if (last == '\\' && (curr == '\r' || curr == '\n'))
                        {
                            reader_.advance();

                            if (state == reader::end)
                                break;

                            if (last == '\r')
                            {
                                if (curr != '\n')
                                    throw comp_error(loc_, "invalid token ('\')");

                                reader_.advance();
                            }

                            loc_.lines();
                            loc_.step();
                            continue;
                        }

                        if (curr == '\n')
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
                    advance();
                    return parser::make_DEVEND(loc_);
                }

                buffer_.push(last);
                advance();

                while (state == reader::ok)
                {
                    if (last != ' ' || last != '\t')
                        break;

                    advance();
                }

                if (state == reader::end || !((last > 64 && last < 91) || (last > 96 && last < 123)))
                    throw comp_error(loc_, "invalid preprocessor directive ('#')");

                state_ = state::preprocessor;
                goto lex_name;
            case '*':
                if (curr != '/' && curr != '=')
                    return parser::make_MUL(loc_);

                advance();

                if (last == '=')
                    return parser::make_ASSIGN_MUL(loc_);

                throw comp_error(loc_, "unmatched multiline comment end ('*/')");
            case '"':
                state_ = state::string;
                goto lex_string;
            case '.':
                advance();

                if (state == reader::end)
                    throw comp_error(loc_, "unterminated field ('.')");

                state_ = state::field;
                goto lex_name_or_number;
            case '(':
                return parser::make_LPAREN(loc_);
            case ')':
                return parser::make_RPAREN(loc_);
            case '{':
                return parser::make_LBRACE(loc_);
            case '}':
                return parser::make_RBRACE(loc_);
            case '[':
                return parser::make_LBRACKET(loc_);
            case ']':
                return parser::make_RBRACKET(loc_);
            case ',':
                return parser::make_COMMA(loc_);
            case ';':
                return parser::make_SEMICOLON(loc_);
            case ':':
                if (curr != ':')
                    return parser::make_COLON(loc_);

                advance();
                return parser::make_DOUBLECOLON(loc_);
            case '?':
                return parser::make_QMARK(loc_);
            case '=':
                if (curr != '=')
                    return parser::make_ASSIGN(loc_);

                advance();
                return parser::make_EQUALITY(loc_);
            case '+':
                if (curr != '+' && curr != '=')
                    return parser::make_ADD(loc_);

                advance();

                if (last == '+')
                    return parser::make_INCREMENT(loc_);

                return parser::make_ASSIGN_ADD(loc_);
            case '-':
                if (curr != '-' && curr != '=')
                    return parser::make_SUB(loc_);

                advance();

                if (last == '-')
                    return parser::make_DECREMENT(loc_);

                return parser::make_ASSIGN_SUB(loc_);
            case '%':
                if (curr != '=')
                    return parser::make_MOD(loc_);

                advance();

                return parser::make_ASSIGN_MOD(loc_);
            case '|':
                if (curr != '|' && curr != '=')
                    return parser::make_BITWISE_OR(loc_);

                advance();

                if (last == '|')
                    return parser::make_OR(loc_);

                return parser::make_ASSIGN_BW_OR(loc_);
            case '&':
                if (curr != '&' && curr != '=' && curr != '"')
                    return parser::make_BITWISE_AND(loc_);

                advance();

                if (last == '&')
                    return parser::make_AND(loc_);

                if (last == '=')
                    return parser::make_ASSIGN_BW_AND(loc_);

                state_ = state::localize;
                goto lex_string;
            case '^':
                if (curr != '=')
                    return parser::make_BITWISE_EXOR(loc_);

                advance();
                return parser::make_ASSIGN_BW_EXOR(loc_);
            case '!':
                if (curr != '=')
                    return parser::make_NOT(loc_);

                advance();
                return parser::make_INEQUALITY(loc_);
            case '~':
                return parser::make_COMPLEMENT(loc_);
            case '<':
                if (curr != '<' && curr != '=')
                    return parser::make_LESS(loc_);

                advance();
                if (last == '=')
                    return parser::make_LESS_EQUAL(loc_);

                if (curr != '=')
                    return parser::make_LSHIFT(loc_);

                advance();
                return parser::make_ASSIGN_LSHIFT(loc_);
            case '>':
                if (curr != '>' && curr != '=')
                    return parser::make_GREATER(loc_);

                advance();

                if (last == '=')
                    return parser::make_GREATER_EQUAL(loc_);

                if (curr != '=')
                    return parser::make_RSHIFT(loc_);

                advance();
                return parser::make_ASSIGN_RSHIFT(loc_);
            default:
lex_name_or_number:
                if (last >= '0' && last <= '9')
                    goto lex_number;
                else if (last == '_' || last >= 'A' && last <= 'Z' || last >= 'a' && last <= 'z')
                    goto lex_name;

                throw comp_error(loc_, utils::string::va("bad token: \'%c\'", last));
        }

lex_string:
        while (true)
        {
            if (state == reader::end)
                throw comp_error(loc_, "unmatched string start ('\"')");

            if (curr == '"')
            {
                advance();
                break;
            }

            if (curr == '\n')
                throw comp_error(loc_, "unterminated string literal");

            if (curr == '\\')
            {
                advance();

                if (state == reader::end)
                    throw comp_error(loc_, "invalid token ('\')");

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
            }
            else if (!buffer_.push(curr))
                throw comp_error(loc_, "max string size exceeded");

            advance();
        }

        if (state_ == state::localize)
            return parser::make_ISTRING(std::string(buffer_.data, buffer_.length), loc_);

        return parser::make_STRING(std::string(buffer_.data, buffer_.length), loc_);

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

            advance();
        }

        if (state_ == state::field)
        {
            if (path)
                throw comp_error(loc_, "invalid field token '\\'");

            if (std::string_view(buffer_.data, buffer_.length) == "size")
            {
                return parser::make_SIZE(loc_);
            }

            return parser::make_FIELD(std::string(buffer_.data, buffer_.length), loc_);
        }
        else if (state_ == state::preprocessor)
        {
            if (path)
                throw comp_error(loc_, "invalid preprocessor directive");

            auto token = parser::token::S2UNDEF;

            if (buffer_.length < 16)
            {
                const auto& itr = keyword_map.find(std::string_view(buffer_.data, buffer_.length));

                if (itr != keyword_map.end())
                {
                    if (itr->second > parser::token::SH_ENDIF)
                        return parser::symbol_type(itr->second, loc_);

                    token = itr->second;
                }
            }

            preprocessor(token);
            state_ = state::start;
            continue;
        }
        else
        {
            if (buffer_.length < 17)
            {
                const auto& itr = keyword_map.find(std::string_view(buffer_.data, buffer_.length));

                if (itr != keyword_map.end())
                    return parser::symbol_type(itr->second, loc_);
            }

            if (path)
            {
                if (buffer_.data[buffer_.length - 1] == '/')
                    throw comp_error(loc_, "invalid path end '\\'");

                return parser::make_PATH(resolver::make_token(std::string_view(buffer_.data, buffer_.length)), loc_);
            }

            return parser::make_IDENTIFIER(resolver::make_token(std::string_view(buffer_.data, buffer_.length)), loc_);
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
                    advance();
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

                advance();
            }

            if (last == '\'')
                throw comp_error(loc_, "invalid number literal");

            if (state_ == state::field && dot || dot > 1 || flt > 1 || flt && buffer_.data[buffer_.length - 1] != 'f')
                throw comp_error(loc_, "invalid number literal");

            if (state_ == state::field || dot || flt)
                return parser::make_FLOAT(std::string(buffer_.data, buffer_.length), loc_);

            return parser::make_INTEGER(std::string(buffer_.data, buffer_.length), loc_);
        }
        else if (curr == 'o')
        {
            advance();

            while (true)
            {
                if (state == reader::end)
                    break;

                if (curr == '\'' && (last == '\'' || last == 'o') || (curr == 'o' && last == '\''))
                    throw comp_error(loc_,  "invalid octal literal");

                if (curr == '\'')
                {
                    advance();
                    continue;
                }

                if (!(curr > 47 && curr < 56))
                    break;

                if (!buffer_.push(curr))
                    throw error("gsc lexer: out of memory!");

                advance();
            }

            if (last == '\'' || buffer_.length <= 0)
                throw comp_error(loc_, "invalid octal literal");

            return parser::make_INTEGER(xsk::utils::string::oct_to_dec(buffer_.data), loc_);
        }
        else if (curr == 'b')
        {
            buffer_.push(last);
            buffer_.push(curr);
            advance();

            while (true)
            {
                if (state == reader::end)
                    break;

                if (curr == '\'' && (last == '\'' || last == 'b') || (curr == 'b' && last == '\''))
                    throw comp_error(loc_, "invalid binary literal");

                if (curr == '\'')
                {
                    advance();
                    continue;
                }

                if (curr != '0' && curr != '1')
                    break;

                if (!buffer_.push(curr))
                    throw comp_error(loc_, "number literal size exceeded");

                advance();
            }

            if (last == '\'' || buffer_.length < 3)
                throw comp_error(loc_, "invalid binary literal");

            return parser::make_INTEGER(xsk::utils::string::bin_to_dec(buffer_.data), loc_);
        }
        else if (curr == 'x')
        {
            buffer_.push(last);
            buffer_.push(curr);
            advance();

            while (true)
            {
                if (state == reader::end)
                    break;

                if (curr == '\'' && (last == '\'' || last == 'x') || (curr == 'x' && last == '\''))
                    throw comp_error(loc_, "invalid hexadecimal literal");

                if (curr == '\'')
                {
                    advance();
                    continue;
                }

                if (!((curr > 47 && curr < 58) || (curr > 64 && curr < 71) || (curr > 96 && curr < 103)))
                    break;

                if (!buffer_.push(curr))
                    throw error("gsc lexer: out of memory!");

                advance();
            }

            if (last == '\'' || buffer_.length < 3)
                throw comp_error(loc_, "invalid hexadecimal literal");

            return parser::make_INTEGER(xsk::utils::string::hex_to_dec(buffer_.data), loc_);
        }
        // cant get here!
    }
}

void lexer::advance()
{
    reader_.advance();

    // dont wrap comment marks '/\/' '/\*' outside strings
    if (state_ == state::start && reader_.last_byte == '/')
        return;

    while (reader_.current_byte == '\\')
    {
        if (reader_.bytes_remaining == 1)
            throw comp_error(loc_, "invalid token ('\\')");

        if (reader_.buffer_pos[1] != '\r' && reader_.buffer_pos[1] != '\n')
            break;

        if (reader_.buffer_pos[1] == '\r')
        {
            if (reader_.bytes_remaining <= 3 || reader_.buffer_pos[2] != '\n')
                throw comp_error(loc_, "invalid token ('\\')");

            reader_.buffer_pos += 3;
            reader_.bytes_remaining -= 3;
        }

        if ((reader_.buffer_pos[1] == '\n'))
        {
            if (reader_.bytes_remaining == 2)
                throw comp_error(loc_, "invalid token ('\\')");

            reader_.buffer_pos += 2;
            reader_.bytes_remaining -= 2;
        }

        if (reader_.bytes_remaining == 0)
        {
            reader_.state = reader::end;
            reader_.current_byte = 0;
        }
        else
        {
            reader_.current_byte = *reader_.buffer_pos;
        }

        loc_.lines();
        loc_.step();
    }
}

void lexer::preprocessor(parser::token::token_kind_type token)
{
    if (!clean_)
        throw comp_error(loc_, "invalid token ('#')");

    switch (token)
    {
        case parser::token::SH_DEFINE:
            throw comp_error(loc_, "unimplemented preprocessor directive");
            break;
        case parser::token::SH_UNDEF:
            throw comp_error(loc_, "unimplemented preprocessor directive");
            break;
        case parser::token::SH_IFDEF:
            throw comp_error(loc_, "unimplemented preprocessor directive");
            break;
        case parser::token::SH_IFNDEF:
            throw comp_error(loc_, "unimplemented preprocessor directive");
            break;
        case parser::token::SH_IF:
            throw comp_error(loc_, "unimplemented preprocessor directive");
            break;
        case parser::token::SH_ELIF:
            throw comp_error(loc_, "unimplemented preprocessor directive");
            break;
        case parser::token::SH_ELSE:
            throw comp_error(loc_, "unimplemented preprocessor directive");
            break;
        case parser::token::SH_ENDIF:
            throw comp_error(loc_, "unimplemented preprocessor directive");
            break;
        default:
            throw comp_error(loc_, "unknown preprocessor directive");
    }
}

} // namespace xsk::gsc::s2
