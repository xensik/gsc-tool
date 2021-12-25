// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "stdafx.hpp"

namespace xsk::utils
{

auto file::read(const std::string& file) -> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> data;

    std::ifstream stream(file, std::ios::binary);

    if (!stream.good() && !stream.is_open())
    {
        throw std::runtime_error("Couldn't open file " + file);
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

void file::save(const std::string& file, const std::vector<std::uint8_t>& data)
{
    const auto pos = file.find_last_of("/\\");

    if (pos != std::string::npos)
    {
        std::filesystem::create_directories(file.substr(0, pos));
    }

    std::ofstream stream(file, std::ios::binary | std::ofstream::out);

    if (stream.is_open())
    {
        stream.write(reinterpret_cast<const char*>(data.data()), data.size());
        stream.close();
    }
}

auto file::length(const std::string& file) -> size_t
{
    auto stream = std::ifstream(file, std::ios::binary);

    if (stream.good())
    {
        stream.seekg(0, std::ios::end);
        return static_cast<size_t>(stream.tellg());
    }

    return 0;
}

auto file::exists(const std::string& file) -> bool
{
    return std::filesystem::exists(file);
}

} // namespace xsk::utils
