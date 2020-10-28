// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_FUNCTION_H_
#define _GSC_FUNCTION_H_

/*namespace gsc
{
*/
struct instruction;

struct function
{
	std::uint32_t index;
	std::uint32_t size;
	std::uint16_t id;
	std::string name;
	std::vector<std::shared_ptr<instruction>> instructions;
	std::unordered_map<std::uint32_t, std::string> labels;

	function() : index(0), name(""), size(0), id(0) { }
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

/*} // namespace gsc*/

#endif // _GSC_FUNCTION_H_
