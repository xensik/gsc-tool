// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/string.hpp"
#include "xsk/gsc/lexer.hpp"
#include "xsk/gsc/context.hpp"

namespace xsk::gsc
{

lexer::lexer(context const* ctx, std::string const& name, char const* data, usize size) : ctx_{ ctx }, reader_{ data, size }, loc_{ &name }, buflen_{ 0 }, spacing_{ spacing::null }, indev_{ false }
{
}

auto lexer::lex() -> token
{
    buflen_ = 0;

    while (true)
    {
        auto& last = reader_.last_byte;
        auto& curr = reader_.curr_byte;
        auto path = false;
        auto localize = false;
        loc_.step();

        if (reader_.ended())
        {
            if (indev_)
                throw comp_error(loc_, "unmatched devblock start ('/#')");

            if (curr == 0 && last != '\n')
            {
                curr = -1;
                return token{ token::NEWLINE, spacing_, loc_ };
            }
            else
                return token{ token::EOS, spacing_, loc_ };
        }

        if (last == 0 || last == '\n')
            spacing_ = spacing::null;
        else if (last == ' ' || last == '\t')
            spacing_ = (spacing_ == spacing::null) ? spacing::empty : spacing::back;
        else
            spacing_ = spacing::none;

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
                return token{ token::NEWLINE, spacing_, loc_ };
            case '\\':
                throw comp_error(loc_, "invalid token ('\\')");
            case '/':
                if (curr != '=' && curr != '#' && curr != '@' && curr != '*' && curr != '/')
                    return token{ token::DIV, spacing_, loc_ };

                advance();

                if (last == '=')
                    return token{ token::DIVEQ, spacing_, loc_ };

                if (last == '#')
                {
                    if (indev_)
                        throw comp_error(loc_, "cannot recurse devblock ('/#')");

                    if ((ctx_->build() & build::dev_blocks) != build::prod)
                    {
                        indev_ = true;
                        return token{ token::DEVBEGIN, spacing_, loc_ };
                    }
                    else
                    {
                        auto first = true;

                        while (true)
                        {
                            if (reader_.ended())
                                throw comp_error(loc_, "unmatched devblock start ('/#')");

                            if (curr == '\n')
                            {
                                loc_.lines();
                                loc_.step();
                            }
                            else if (last == '#' && curr == '/' && !first)
                            {
                                advance();
                                break;
                            }

                            advance();
                            first = false;
                        }
                    }
                }
                else if (last == '@')
                {
                    auto first = true;

                    while (true)
                    {
                        if (reader_.ended())
                            throw comp_error(loc_, "unmatched script doc comment start ('/@')");

                        if (curr == '\n')
                        {
                            loc_.lines();
                            loc_.step();
                        }
                        else if (last == '@' && curr == '/' && !first)
                        {
                            advance();
                            break;
                        }

                        advance();
                        first = false;
                    }
                }
                else if (last == '*')
                {
                    auto first = true;

                    while (true)
                    {
                        if (reader_.ended())
                            throw comp_error(loc_, "unmatched multiline comment start ('/*')");

                        if (curr == '\n')
                        {
                            loc_.lines();
                            loc_.step();
                        }
                        else if (last  == '*' && curr == '/' && !first)
                        {
                            advance();
                            break;
                        }

                        advance();
                        first = false;
                    }
                }
                else if (last == '/')
                {
                    while (true)
                    {
                        if (reader_.ended())
                            break;

                        if (curr == '\n')
                            break;

                        advance();
                    }
                }
                continue;
            case '#':
                if (curr == '/')
                {
                    if (!indev_)
                        throw comp_error(loc_, "unmatched devblock end ('#/')");

                    advance();
                    indev_ = false;
                    return token{ token::DEVEND, spacing_, loc_ };
                }

                return token{ token::SHARP, spacing_, loc_ };
            case '*':
                if (curr != '=' && curr != '/')
                    return token{ token::STAR, spacing_, loc_ };

                advance();

                if (last == '=')
                    return token{ token::STAREQ, spacing_, loc_ };

                throw comp_error(loc_, "unmatched multiline comment end ('*/')");
            case '"':
                goto lex_string;
            case '.':
                if (curr == '.')
                {
                    advance();

                    if (curr != '.')
                        return token{ token::DOUBLEDOT, spacing_, loc_ };

                    advance();
                    return token{ token::ELLIPSIS, spacing_, loc_ };
                }

                if (curr < '0' || curr > '9')
                    return token{ token::DOT, spacing_, loc_ };
                goto lex_number;
            case '(':
                return token{ token::LPAREN, spacing_, loc_ };
            case ')':
                return token{ token::RPAREN, spacing_, loc_ };
            case '{':
                return token{ token::LBRACE, spacing_, loc_ };
            case '}':
                return token{ token::RBRACE, spacing_, loc_ };
            case '[':
                return token{ token::LBRACKET, spacing_, loc_ };
            case ']':
                return token{ token::RBRACKET, spacing_, loc_ };
            case ',':
                return token{ token::COMMA, spacing_, loc_ };
            case ';':
                return token{ token::SEMICOLON, spacing_, loc_ };
            case ':':
                if (curr != ':')
                    return token{ token::COLON, spacing_, loc_ };

                advance();
                return token{ token::DOUBLECOLON, spacing_, loc_ };
            case '?':
                return token{ token::QMARK, spacing_, loc_ };
            case '=':
                if (curr != '=')
                    return token{ token::ASSIGN, spacing_, loc_ };

                advance();
                return token{ token::EQ, spacing_, loc_ };
            case '+':
                if (curr != '+' && curr != '=')
                    return token{ token::PLUS, spacing_, loc_ };

                advance();

                if (last == '+')
                    return token{ token::INC, spacing_, loc_ };

                return token{ token::PLUSEQ, spacing_, loc_ };
            case '-':
                if (curr != '-' && curr != '=')
                    return token{ token::MINUS, spacing_, loc_ };

                advance();

                if (last == '-')
                    return token{ token::DEC, spacing_, loc_ };

                return token{ token::MINUSEQ, spacing_, loc_ };
            case '%':
                if (curr != '=')
                    return token{ token::MOD, spacing_, loc_ };

                advance();

                return token{ token::MODEQ, spacing_, loc_ };
            case '|':
                if (curr != '|' && curr != '=')
                    return token{ token::BITOR, spacing_, loc_ };

                advance();

                if (last == '|')
                    return token{ token::OR, spacing_, loc_ };

                return token{ token::BITOREQ, spacing_, loc_ };
            case '&':
                if (curr != '&' && curr != '=' && curr != '"')
                    return token{ token::BITAND, spacing_, loc_ };

                advance();

                if (last == '&')
                    return token{ token::AND, spacing_, loc_ };

                if (last == '=')
                    return token{ token::BITANDEQ, spacing_, loc_ };

                localize = true;
                goto lex_string;
            case '^':
                if (curr != '=')
                    return token{ token::BITEXOR, spacing_, loc_ };

                advance();
                return token{ token::BITEXOREQ, spacing_, loc_ };
            case '!':
                if (curr != '=')
                    return token{ token::BANG, spacing_, loc_ };

                advance();
                return token{ token::NE, spacing_, loc_ };
            case '~':
                return token{ token::TILDE, spacing_, loc_ };
            case '<':
                if (curr != '<' && curr != '=')
                    return token{ token::LT, spacing_, loc_ };

                advance();
                if (last == '=')
                    return token{ token::LE, spacing_, loc_ };

                if (curr != '=')
                    return token{ token::SHL, spacing_, loc_ };

                advance();
                return token{ token::SHLEQ, spacing_, loc_ };
            case '>':
                if (curr != '>' && curr != '=')
                    return token{ token::GT, spacing_, loc_ };

                advance();

                if (last == '=')
                    return token{ token::GE, spacing_, loc_ };

                if (curr != '=')
                    return token{ token::SHR, spacing_, loc_ };

                advance();
                return token{ token::SHREQ, spacing_, loc_ };
            default:
                if (last >= '0' && last <= '9')
                    goto lex_number;
                else if (last == '_' || (last >= 'A' && last <= 'Z') || (last >= 'a' && last <= 'z'))
                    goto lex_name;

                throw comp_error(loc_, std::format("bad token: '{}'", last));
        }

lex_string:
        while (true)
        {
            if (reader_.ended())
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

                if (reader_.ended())
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

                push(c);
            }
            else
                push(curr);

            advance();
        }

        if (localize)
            return token{ token::ISTRING, spacing_, loc_, std::string{ &buffer_[0], buflen_ } };

        return token{ token::STRING, spacing_, loc_, std::string{ &buffer_[0], buflen_ } };

lex_name:
        push(last);

        while (true)
        {
            if (reader_.ended())
                break;

            if (!(curr == '\\' || curr == '_' || (curr > 64 && curr < 91) || (curr > 96 && curr < 123) || (curr > 47 && curr < 58)))
                break;

            if (curr == '\\')
            {
                if (last == '\\')
                    throw comp_error(loc_, "invalid path '\\\\'");

                path = true;
                push('/');
            }
            else
                push(curr);

            advance();
        }

        if (path)
        {
            if (buffer_[buflen_ - 1] == '/')
                throw comp_error(loc_, "invalid path end '\\'");

            return token{ token::PATH, spacing_, loc_, ctx_->make_token(std::string_view{ &buffer_[0], buflen_ }) };
        }

        return token{ token::NAME, spacing_, loc_, std::string{ &buffer_[0], buflen_ } };

lex_number:
        if (last == '.' || last != '0' || (last == '0' && (curr != 'o' && curr != 'b' && curr != 'x')))
        {
            push(last);

            auto dot = last == '.' ? 1 : 0;
            auto flt = 0;

            while (true)
            {
                if (reader_.ended())
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

                push(curr);
                advance();
            }

            if (last == '\'')
                throw comp_error(loc_, "invalid number literal");

            if (dot > 1 || flt > 1 || (flt && buffer_[buflen_ - 1] != 'f'))
                throw comp_error(loc_, "invalid number literal");

            if (dot || flt)
                return token{ token::FLT, spacing_, loc_, std::string{ &buffer_[0], buflen_ } };

            return token{ token::INT, spacing_, loc_, std::string{ &buffer_[0], buflen_ } };
        }
        else if (curr == 'o')
        {
            advance();

            while (true)
            {
                if (reader_.ended())
                    break;

                if ((curr == '\'' && (last == '\'' || last == 'o')) || (curr == 'o' && last == '\''))
                    throw comp_error(loc_, "invalid octal literal");

                if (curr == '\'')
                {
                    advance();
                    continue;
                }

                if (!(curr > 47 && curr < 56))
                    break;

                push(curr);
                advance();
            }

            if (last == '\'' || buflen_ <= 0)
                throw comp_error(loc_, "invalid octal literal");

            push('\0');

            return token{ token::INT, spacing_, loc_, utils::string::oct_to_dec(&buffer_[0]) };
        }
        else if (curr == 'b')
        {
            push(last);
            push(curr);
            advance();

            while (true)
            {
                if (reader_.ended())
                    break;

                if ((curr == '\'' && (last == '\'' || last == 'b')) || (curr == 'b' && last == '\''))
                    throw comp_error(loc_, "invalid binary literal");

                if (curr == '\'')
                {
                    advance();
                    continue;
                }

                if (curr != '0' && curr != '1')
                    break;

                push(curr);
                advance();
            }

            if (last == '\'' || buflen_ < 3)
                throw comp_error(loc_, "invalid binary literal");

            push('\0');

            return token{ token::INT, spacing_, loc_, utils::string::bin_to_dec(&buffer_[0]) };
        }
        else if (curr == 'x')
        {
            push(last);
            push(curr);
            advance();

            while (true)
            {
                if (reader_.ended())
                    break;

                if ((curr == '\'' && (last == '\'' || last == 'x')) || (curr == 'x' && last == '\''))
                    throw comp_error(loc_, "invalid hexadecimal literal");

                if (curr == '\'')
                {
                    advance();
                    continue;
                }

                if (!((curr > 47 && curr < 58) || (curr > 64 && curr < 71) || (curr > 96 && curr < 103)))
                    break;

                push(curr);
                advance();
            }

            if (last == '\'' || buflen_ < 3)
                throw comp_error(loc_, "invalid hexadecimal literal");

            push('\0');

            return token{ token::INT, spacing_, loc_, utils::string::hex_to_dec(&buffer_[0]) };
        }

        throw error("UNEXPECTED LEXER INTERNAL ERROR");
    }
}

auto lexer::push(char c) -> void
{
    if (buflen_ >= 0x1000)
        throw error("lexer: max literal size exceeded");

    buffer_[buflen_++] = c;
}

auto lexer::advance() -> void
{
    reader_.advance();
    loc_.end.column++;

    if (reader_.curr_byte == '\\') [[unlikely]]
        linewrap();
}

auto lexer::linewrap() -> void
{
    while (reader_.curr_byte == '\\')
    {
        if (reader_.available == 1)
            throw comp_error(loc_, "invalid token ('\\')");

        if (reader_.buffer_pos[1] != '\r' && reader_.buffer_pos[1] != '\n')
            break;

        if (reader_.buffer_pos[1] == '\r')
        {
            if (reader_.available <= 3 || reader_.buffer_pos[2] != '\n')
                throw comp_error(loc_, "invalid token ('\\')");

            reader_.buffer_pos += 3;
            reader_.available -= 3;
        }

        if ((reader_.buffer_pos[1] == '\n'))
        {
            if (reader_.available == 2)
                throw comp_error(loc_, "invalid token ('\\')");

            reader_.buffer_pos += 2;
            reader_.available -= 2;
        }

        reader_.curr_byte = reader_.available ? *reader_.buffer_pos : 0;

        loc_.lines();
        loc_.step();
    }
}

} // namespace xsk::gsc
