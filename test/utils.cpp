// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/reader.hpp"
#include "xsk/utils/writer.hpp"
#include "xsk/utils/zlib.hpp"
#include <catch_amalgamated.hpp>

namespace xsk::test
{

using namespace xsk::utils;

TEST_CASE("reader: default construction", "[utils][reader]")
{
    reader r;
    REQUIRE(r.pos() == 0);
    REQUIRE_FALSE(r.is_avail());
}

TEST_CASE("reader: read integers", "[utils][reader]")
{
    // little-endian: 0x04030201
    std::vector<u8> data = { 0x01, 0x02, 0x03, 0x04 };
    reader r(data);

    SECTION("read u8")
    {
        REQUIRE(r.read<u8>() == 0x01);
        REQUIRE(r.pos() == 1);
    }

    SECTION("read u16")
    {
        REQUIRE(r.read<u16>() == 0x0201);
        REQUIRE(r.pos() == 2);
    }

    SECTION("read u32")
    {
        REQUIRE(r.read<u32>() == 0x04030201);
        REQUIRE(r.pos() == 4);
    }
}

TEST_CASE("reader: byte swap (big-endian)", "[utils][reader]")
{
    std::vector<u8> data = { 0x01, 0x02, 0x03, 0x04 };
    reader r(data, true);

    SECTION("u16 swap")
    {
        REQUIRE(r.read<u16>() == 0x0102);
    }

    SECTION("u32 swap")
    {
        REQUIRE(r.read<u32>() == 0x01020304);
    }
}

TEST_CASE("reader: seek and position", "[utils][reader]")
{
    std::vector<u8> data = { 0xAA, 0xBB, 0xCC, 0xDD };
    reader r(data);

    r.seek(2);
    REQUIRE(r.pos() == 2);
    REQUIRE(r.read<u8>() == 0xCC);

    r.seek_neg(2);
    REQUIRE(r.pos() == 1);
    REQUIRE(r.read<u8>() == 0xBB);
}

TEST_CASE("reader: read c-string", "[utils][reader]")
{
    std::vector<u8> data = { 'h', 'e', 'l', 'l', 'o', '\0', 0xFF };
    reader r(data);

    auto str = r.read_cstr();
    REQUIRE(str == "hello");
    REQUIRE(r.pos() == 6);
}

TEST_CASE("reader: alignment", "[utils][reader]")
{
    std::vector<u8> data(16, 0);
    reader r(data);

    r.seek(3);
    auto padded = r.align(4);
    REQUIRE(r.pos() == 4);
    REQUIRE(padded == 1);
}

TEST_CASE("writer: default construction", "[utils][writer]")
{
    writer w;
    REQUIRE(w.pos() == 0);
}

TEST_CASE("writer: write and verify via reader", "[utils][writer]")
{
    writer w;
    w.write<u32>(0xDEADBEEF);
    w.write<u16>(0xCAFE);
    w.write<u8>(0x42);

    auto data = w.data();
    auto size = w.pos();

    reader r(data, size, false);
    REQUIRE(r.read<u32>() == 0xDEADBEEF);
    REQUIRE(r.read<u16>() == 0xCAFE);
    REQUIRE(r.read<u8>() == 0x42);
}

TEST_CASE("writer: byte swap (big-endian)", "[utils][writer]")
{
    writer w(true);
    w.write<u32>(0x01020304);

    reader r(w.data(), w.pos(), false);
    REQUIRE(r.read<u8>() == 0x01);
    REQUIRE(r.read<u8>() == 0x02);
    REQUIRE(r.read<u8>() == 0x03);
    REQUIRE(r.read<u8>() == 0x04);
}

TEST_CASE("writer: c-string", "[utils][writer]")
{
    writer w;
    w.write_cstr("test");

    reader r(w.data(), w.pos(), false);
    REQUIRE(r.read_cstr() == "test");
}

TEST_CASE("writer: alignment", "[utils][writer]")
{
    writer w;
    w.write<u8>(0xFF);
    w.write<u8>(0xFF);
    w.write<u8>(0xFF);
    auto padded = w.align(4);
    REQUIRE(w.pos() == 4);
    REQUIRE(padded == 1);
}

TEST_CASE("zlib: compress and decompress round-trip", "[utils][zlib]")
{
    std::vector<u8> original(1024);
    for (usize i = 0; i < original.size(); i++)
        original[i] = static_cast<u8>(i & 0xFF);

    auto compressed = zlib::compress(original);
    REQUIRE_FALSE(compressed.empty());
    REQUIRE(compressed.size() < original.size());

    auto decompressed = zlib::decompress(compressed, static_cast<u32>(original.size()));
    REQUIRE(decompressed == original);
}

TEST_CASE("zlib: empty data", "[utils][zlib]")
{
    std::vector<u8> empty;
    auto compressed = zlib::compress(empty);
    auto decompressed = zlib::decompress(compressed, 0);
    REQUIRE(decompressed.empty());
}

} // namespace xsk::test
