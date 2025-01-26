// Copyright 2025 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#pragma once

namespace xsk::utils
{

struct file
{
    using error = std::runtime_error;

    static auto read(std::filesystem::path const& file) -> std::vector<u8>;
    static auto save(std::filesystem::path const& file, std::vector<u8> const& data) -> void;
    static auto save(std::filesystem::path const& file, u8 const* data, usize size) -> void;
    static auto length(std::filesystem::path const& file) -> usize;
    static auto exists(std::filesystem::path const& file) -> bool;
};

} // namespace xsk::utils
