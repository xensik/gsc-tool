// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _XSK_GSC_DECOMPILER_H_
#define _XSK_GSC_DECOMPILER_H_

#include <stack>

namespace gsc
{

struct statement
{
	std::uint32_t index;
	std::string data;

	statement() : index(0) { }
};

struct decompiler_function
{
	std::string name;
	std::size_t params = 0;
	std::size_t end = 0;
	bool is_void = true;
	std::vector<std::string> local_vars;
	std::stack<std::shared_ptr<statement>> stack;
	std::vector<std::shared_ptr<statement>> statements;

	std::unordered_map<std::uint32_t, std::string> labels;
	std::vector<std::shared_ptr<instruction>> instructions;
};

	
class decompiler
{
	std::unique_ptr<utils::byte_buffer> output_;
	std::vector<std::shared_ptr<decompiler_function>> functions_;
	bool in_waittill_;

public:
	decompiler();
	void decompile(std::vector<std::shared_ptr<function>>& functions);
	auto output() -> std::vector<std::uint8_t>;

private:
	void decompile_function(std::shared_ptr<decompiler_function> func);
	void decompile_statements(std::shared_ptr<decompiler_function> func);
	void decompile_blocks(std::shared_ptr<decompiler_function> func);

	void print_function(std::shared_ptr<decompiler_function> func);
	void print_statement(std::shared_ptr<statement> stmt);
	void print_label(const std::string& label);
};

} // namespace gsc

#endif // _XSK_GSC_DECOMPILER_H_
