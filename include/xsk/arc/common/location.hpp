// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::arc
{

struct position
{
public:
    typedef const std::string filename_type;
    typedef i32 counter_type;

    filename_type *filename;
    counter_type line;
    counter_type column;

    explicit position(filename_type *f = nullptr, counter_type l = 1, counter_type c = 1)
        : filename(f), line(l), column(c) {}

    void initialize(filename_type *fn = nullptr, counter_type l = 1, counter_type c = 1)
    {
        filename = fn;
        line = l;
        column = c;
    }

    void lines(counter_type count = 1)
    {
        if (count)
        {
            column = 1;
            line = add_(line, count, 1);
        }
    }

    void columns(counter_type count = 1)
    {
        column = add_(column, count, 1);
    }

private:
    static counter_type add_(counter_type lhs, counter_type rhs, counter_type min)
    {
        return lhs + rhs < min ? min : lhs + rhs;
    }
};

inline position& operator+=(position &res, position::counter_type width)
{
    res.columns(width);
    return res;
}

inline position operator+(position res, position::counter_type width)
{
    return res += width;
}

inline position& operator-=(position &res, position::counter_type width)
{
    return res += -width;
}

inline position operator-(position res, position::counter_type width)
{
    return res -= width;
}

template <typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T> &ostr, const position &pos)
{
    if (pos.filename)
        ostr << *pos.filename << ':';
    return ostr << pos.line << '.' << pos.column;
}

struct location
{
public:
    typedef position::filename_type filename_type;
    typedef position::counter_type counter_type;

    position begin;
    position end;

    location(const position &b, const position &e)
        : begin(b), end(e) {}

    explicit location(const position &p = position())
        : begin(p), end(p) {}

    explicit location(filename_type *f, counter_type l = 1, counter_type c = 1)
        : begin(f, l, c), end(f, l, c) {}

    void initialize(filename_type *f = nullptr, counter_type l = 1, counter_type c = 1)
    {
        begin.initialize(f, l, c);
        end = begin;
    }

    void step()
    {
        begin = end;
    }

    void columns(counter_type count = 1)
    {
        end += count;
    }

    void lines(counter_type count = 1)
    {
        end.lines(count);
    }

    auto print() const -> std::string
    {
        return std::format("{}:{}:{}", *begin.filename, begin.line, begin.column);
    }

    auto label() const -> std::string
    {
        return std::format("loc_{:X}", begin.line);
    }
};

inline location& operator+=(location &res, const location &end)
{
    res.end = end.end;
    return res;
}

inline location operator+(location res, const location &end)
{
    return res += end;
}

inline location& operator+=(location &res, location::counter_type width)
{
    res.columns(width);
    return res;
}

inline location operator+(location res, location::counter_type width)
{
    return res += width;
}

inline location& operator-=(location &res, location::counter_type width)
{
    return res += -width;
}

inline location operator-(location res, location::counter_type width)
{
    return res -= width;
}

template <typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T> &ostr, const location &loc)
{
    location::counter_type end_col = 0 < loc.end.column ? loc.end.column - 1 : 0;
    ostr << loc.begin;
    if (loc.end.filename && (!loc.begin.filename || *loc.begin.filename != *loc.end.filename))
        ostr << '-' << loc.end.filename << ':' << loc.end.line << '.' << end_col;
    else if (loc.begin.line < loc.end.line)
        ostr << '-' << loc.end.line << '.' << end_col;
    else if (loc.begin.column < end_col)
        ostr << '-' << end_col;
    return ostr;
}

} // namespace xsk::arc
