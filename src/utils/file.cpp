// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "xsk/stdinc.hpp"
#include "xsk/utils/file.hpp"

namespace xsk::utils
{

auto file::read(std::filesystem::path const& file) -> std::vector<u8>
{
    auto data = std::vector<u8>{};

    auto stream = std::ifstream{ file, std::ios::binary };

    if (!stream.good() && !stream.is_open())
    {
        throw error(std::format("couldn't open file {}", file.string()));
    }

    stream.seekg(0, std::ios::end);
    std::streamsize size = stream.tellg();
    stream.seekg(0, std::ios::beg);

    if (size > -1)
    {
        data.resize(static_cast<uint32_t>(size));
        stream.read(reinterpret_cast<char*>(data.data()), size);
    }

    stream.close();

    return data;
}

auto file::save(std::filesystem::path const& file, std::vector<u8> const& data) -> void
{
    return save(file, data.data(), data.size());
}

auto file::save(std::filesystem::path const& file, u8 const* data, usize size) -> void
{
    std::filesystem::create_directories(file.parent_path());

    if (auto stream = std::ofstream{ file, std::ios::binary | std::ofstream::out }; stream)
    {
        stream.write(reinterpret_cast<char const*>(data), size);
    }
}

auto file::length(std::filesystem::path const& file) -> usize
{
    if (auto stream = std::ifstream{ file, std::ios::binary }; stream.good())
    {
        stream.seekg(0, std::ios::end);
        return static_cast<usize>(stream.tellg());
    }

    return 0;
}

auto file::exists(std::filesystem::path const& file) -> bool
{
    return std::filesystem::exists(file);
}

} // namespace xsk::utils
