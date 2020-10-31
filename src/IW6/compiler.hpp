// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#ifndef _GSC_IW6_COMPILER_H_
#define _GSC_IW6_COMPILER_H_

namespace IW6
{

class compiler : public gsc::compiler
{
public:
    compiler();

	void compile(std::string& buffer);
	auto output() -> std::vector<std::shared_ptr<function>>;

private:
	std::vector<std::shared_ptr<function>> assembly_;
	std::vector<std::string> includes_;
	std::vector<std::string> animtrees_;
	std::shared_ptr<function> function_;

	void compile_tree(std::unique_ptr<node> tree);
	void emit_include(node_include* include);
	void emit_using_animtree(node_using_animtree* animtree);
	void emit_function(node_function* function);
	void emit_parameters(node_parameter_list* params);
};

} // namespace IW6

#endif // _GSC_IW6_COMPILER_H_
