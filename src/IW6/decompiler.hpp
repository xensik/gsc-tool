// Copyright 2021 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_IW6_DECOMPILER_HPP_
#define _GSC_IW6_DECOMPILER_HPP_

namespace IW6
{

class decompiler : public gsc::decompiler
{
    std::unique_ptr<utils::byte_buffer> output_;
    gsc::script_ptr script_;
    gsc::thread_ptr func_;
    std::uint32_t params_;
    std::unordered_map<std::uint32_t, std::string> labels_;
    std::vector<std::string> expr_labels_;
    std::vector<std::string> local_vars_;
    std::stack<gsc::node_ptr> stack_;
    std::vector<gsc::context> blocks_;

public:
    auto output() -> std::vector<std::uint8_t>;
    void decompile(std::vector<gsc::function_ptr>& functions);

private:
    void decompile_function(const gsc::function_ptr& func);
    void decompile_statements(const gsc::function_ptr& func);
    void decompile_expr();
    void decompile_block(const gsc::block_ptr& block);
    void decompile_nulls(const gsc::block_ptr& block);
    void decompile_search_infinite(const gsc::block_ptr& block);
    void decompile_search_loop(const gsc::block_ptr& block);
    void decompile_search_switch(const gsc::block_ptr& block);
    void decompile_search_ifelse(const gsc::block_ptr& block);
    void decompile_break_continue(const gsc::block_ptr& block);
    void decompile_if(const gsc::block_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_ifelse(const gsc::block_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_last_ifelse(const gsc::block_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_infinite(const gsc::block_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_loop(const gsc::block_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_while(const gsc::block_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_for(const gsc::block_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_foreach(const gsc::block_ptr& block, std::uint32_t start, std::uint32_t end);
    void decompile_switch(const gsc::block_ptr& block, std::uint32_t start);
    auto find_location_reference(const gsc::block_ptr& block, std::uint32_t start, std::uint32_t end, const std::string& location) -> bool;
    auto find_location_index(const gsc::block_ptr& block, const std::string& location) -> std::uint32_t;
    auto last_location_index(const gsc::block_ptr& block, std::uint32_t index) -> bool;
    auto unhandled_function(const std::string& function) -> bool;
};

} // namespace IW6

#endif // _GSC_IW6_DECOMPILER_HPP_
