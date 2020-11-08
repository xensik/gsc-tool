// Copyright 2020 xensik. All rights reserved.
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
	gsc::script_ptr 								script_;
	gsc::thread_ptr									func_;
	std::unordered_map<std::uint32_t, std::string> 	labels_;
	std::uint32_t 									params_;
	std::vector<std::string> 						local_vars_;
	std::stack<gsc::node_ptr> 						stack_;
	std::vector<std::string> 						expr_labels_;

public:
	auto output() -> std::string;
	void decompile(std::vector<gsc::function_ptr>& functions);

private:
	void decompile_function(const gsc::function_ptr& func);
	void decompile_statements(const gsc::function_ptr& func);
	void decompile_blocks();
	void decompile_expr();
};

} // namespace IW6

#endif // _GSC_IW6_DECOMPILER_HPP_
