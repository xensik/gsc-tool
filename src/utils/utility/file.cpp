// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "utils.hpp"

namespace utils
{

auto file::read(const std::string& file) -> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> data;

    FILE* fp = fopen(file.data(), "rb");
    if (fp)
    {
        long len = utils::file::length(fp);
        data.resize(len);
        fread(data.data(), len, 1, fp);
        fclose(fp);
    }
    else
    {
        printf("Couldn't open file %s!\n", file.data());
        std::exit(-1);
    }

    return data;
}

auto file::read_text(const std::string& file) -> std::string
{
    std::string data;

    std::ifstream stream(file, std::ios::binary);
    if (stream.good())
    {
        if (!stream.is_open()) return data;

        stream.seekg(0, std::ios::end);
        std::streamsize size = stream.tellg();
        stream.seekg(0, std::ios::beg);

        if (size > -1)
        {
            data.clear();
            data.resize(static_cast<uint32_t>(size));

            stream.read(reinterpret_cast<char*>(data.data()), size);
        }

        stream.close();
    }
    return data;
}


void file::save(const std::string& file, const std::vector<std::uint8_t>& data)
{
    FILE* fp = fopen(file.data(), "wb");
    fwrite(data.data(), 1, data.size(), fp);
    fclose(fp);
}

auto file::length(FILE* fp) -> long
{
    long i = ftell(fp);
    fseek(fp, 0, SEEK_END);
    long ret = ftell(fp);
    fseek(fp, i, SEEK_SET);
    return ret;
}

} // namespace utils
