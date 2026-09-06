// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/gsc/common/asset.hpp"
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

TEST_CASE("zlib: declared output length is validated without oversized allocation", "[utils][zlib]")
{
    auto const input = std::vector<u8>{ 't', 'e', 's', 't' };
    auto const compressed = zlib::compress(input);

    CHECK(zlib::decompress(compressed, static_cast<u32>(input.size())) == input);
    CHECK_THROWS_AS(zlib::decompress(compressed, static_cast<u32>(input.size() + 1)), std::runtime_error);
    CHECK_THROWS_AS(zlib::decompress(compressed, std::numeric_limits<u32>::max()), std::runtime_error);
}

TEST_CASE("reader: unaligned scalar reads are supported", "[utils][reader]")
{
    auto const data = std::vector<u8>{ 0xFF, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12 };
    auto value = reader{ data };

    value.seek(1);
    CHECK(value.read<u16>() == 0x1234);
    CHECK(value.read<u32>() == 0x12345678);
}

TEST_CASE("reader: i24 does not read beyond its three bytes", "[utils][reader]")
{
    auto const data = std::vector<u8>{ 0x56, 0x34, 0x12 };
    auto little = reader{ data };
    auto big = reader{ data, true };

    CHECK(little.read_i24() == 0x123456);
    CHECK(big.read_i24() == 0x563412);
    CHECK(little.pos() == 3);
}

TEST_CASE("reader: malformed ranges and strings are rejected", "[utils][reader]")
{
    auto const data = std::vector<u8>{ 'a', 'b', 'c' };
    auto value = reader{ data };

    CHECK_THROWS_AS(value.read_cstr(), std::runtime_error);
    CHECK(value.read_bytes(0, 0).empty());
    CHECK_THROWS_AS(value.read_bytes(2, 2), std::runtime_error);
    CHECK_THROWS_AS(value.align(0), std::runtime_error);
    CHECK_THROWS_AS(value.align(3), std::runtime_error);
}

TEST_CASE("writer: unaligned scalar writes round-trip through reader", "[utils][writer]")
{
    auto output = writer{ usize{ 7 } };
    output.write<u8>(0xFF);
    output.write<u16>(0x1234);
    output.write<u32>(0x12345678);

    auto input = reader{ output.data(), output.pos() };
    CHECK(input.read<u8>() == 0xFF);
    CHECK(input.read<u16>() == 0x1234);
    CHECK(input.read<u32>() == 0x12345678);
}

TEST_CASE("writer: i24 writes exactly three bytes", "[utils][writer]")
{
    auto output = writer{ usize{ 3 } };
    output.write_i24(0x123456);

    CHECK(output.pos() == 3);
    CHECK(output.data()[0] == 0x56);
    CHECK(output.data()[1] == 0x34);
    CHECK(output.data()[2] == 0x12);
}

TEST_CASE("writer: cstr terminates overwritten data and validates alignment", "[utils][writer]")
{
    auto output = writer{ usize{ 4 } };
    output.write_string("xxxx");
    output.pos(0);
    output.write_cstr("a");

    CHECK(output.data()[0] == 'a');
    CHECK(output.data()[1] == 0);
    CHECK_THROWS_AS(output.align(0), std::runtime_error);
    CHECK_THROWS_AS(output.align(3), std::runtime_error);
}

TEST_CASE("gsc asset: malformed input is rejected", "[gsc][asset]")
{
    auto value = gsc::asset{};

    CHECK_THROWS_AS(value.deserialize({}), std::runtime_error);
    CHECK_THROWS_AS(value.deserialize(std::vector<u8>(13, 1)), std::runtime_error);
    CHECK_THROWS_AS(value.deserialize({ 'a', 0 }), std::runtime_error);
}

TEST_CASE("gsc asset: empty payload is accepted", "[gsc][asset]")
{
    auto value = gsc::asset{};
    auto data = std::vector<u8>(13, 0);

    CHECK_NOTHROW(value.deserialize(data));
    CHECK(value.name.empty());
    CHECK(value.buffer.empty());
    CHECK(value.bytecode.empty());
}

TEST_CASE("gsc asset: serialization round-trip preserves metadata and payload", "[gsc][asset]")
{
    auto original = gsc::asset{};
    original.name = "test";
    original.buffer = { 1, 2, 3 };
    original.bytecode = { 4, 5 };
    original.compressed_length = static_cast<u32>(original.buffer.size());
    original.length = 7;
    original.bytecode_length = static_cast<u32>(original.bytecode.size());

    auto restored = gsc::asset{};
    restored.deserialize(original.serialize());

    CHECK(restored.name == original.name);
    CHECK(restored.compressed_length == original.compressed_length);
    CHECK(restored.length == original.length);
    CHECK(restored.bytecode_length == original.bytecode_length);
    CHECK(restored.buffer == original.buffer);
    CHECK(restored.bytecode == original.bytecode);
}

} // namespace xsk::test
