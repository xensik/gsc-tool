// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW6.hpp"

namespace IW6
{

auto decompiler::output() -> std::string
{
	std::string output;

	output.reserve(0x1000000);
	output.append("// IW6 PC GSC\n");
	output.append("// Decompiled by https://github.com/xensik/gsc-tool\n\n");
	output.append(script_->print());

	return output;
}

void decompiler::decompile(std::vector<gsc::function_ptr>& functions)
{
	script_ = std::make_unique<gsc::node_script>();

	for (auto& func : functions)
	{
		auto name = std::make_unique<gsc::node_identifier>(func->name.substr(4));
		auto params = std::make_unique<gsc::node_parameters>();
		auto block = std::make_unique<gsc::node_block>();
		func_ = std::make_unique<gsc::node_thread>(std::move(name),std::move(params),std::move(block));

		labels_ = func->labels;
		params_ = 0;
		local_vars_.clear();
		expr_labels_.clear();
		stack_ = std::stack<gsc::node_ptr>();
		
		this->decompile_function(func);

		script_->threads.push_back(std::move(func_));
	}
}

void decompiler::decompile_function(const gsc::function_ptr& func)
{
	this->decompile_statements(func);

	auto& block = func_->block;
	this->decompile_block(block);
}

void decompiler::decompile_statements(const gsc::function_ptr& func)
{
	for (auto& inst : func->instructions)
	{
		const auto itr = func->labels.find(inst->index);

		if (itr != func->labels.end())
		{
			auto node = std::make_unique<gsc::node_asm_loc>(itr->second);
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(node)));

			for(auto& loc : expr_labels_)
			{
				if(loc == itr->second)
				{
					decompile_expr();
					// erase loc in expr_labels
					break;
				}
			}
		}

		switch (opcode(inst->opcode))
		{
		case opcode::OP_GetThisthread:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_GetThisthread'!");
		}
		break;
		case opcode::OP_GetLevel:
		case opcode::OP_GetLevelObject:
		{
			auto node = std::make_unique<gsc::node_level>();
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetAnim:
		case opcode::OP_GetAnimObject:
		{
			auto node = std::make_unique<gsc::node_anim>();
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetSelf:
		case opcode::OP_GetSelfObject:
		{
			auto node = std::make_unique<gsc::node_self>();
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetGame:
		case opcode::OP_GetGameRef:
		{
			auto node = std::make_unique<gsc::node_game>();
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetUndefined:
		{
			auto node = std::make_unique<gsc::node_undefined>();
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EmptyArray:
		{
			auto node = std::make_unique<gsc::node_empty_array>();
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetAnimation:
		{
			auto str_ = std::make_unique<gsc::node_string>(inst->data[0]);
			auto anim = std::make_unique<gsc::node_using_animtree>(std::move(str_));
			script_->animtrees.push_back(std::move(anim));
			auto node = std::make_unique<gsc::node_animref>(inst->data[1].substr(1,inst->data[1].size()-2));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetAnimTree:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_GetAnimTree'!");
		}
		break;
		case opcode::OP_GetString:
		{
			auto node = std::make_unique<gsc::node_string>(inst->data[0]);
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetIString:
		{
			auto node = std::make_unique<gsc::node_localized_string>(inst->data[0]);
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetZero:
		{
			auto node = std::make_unique<gsc::node_integer>("0");
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetByte:		
		case opcode::OP_GetUnsignedShort:
		case opcode::OP_GetInteger:
		{
			auto node = std::make_unique<gsc::node_integer>(inst->data[0]);
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetNegByte:
		case opcode::OP_GetNegUnsignedShort:
		{
			auto node = std::make_unique<gsc::node_integer>("-" + inst->data[0]);
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetFloat:
		{
			auto node = std::make_unique<gsc::node_float>(inst->data[0]);
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetVector:
		{
			auto node1 = std::make_unique<gsc::node_float>(inst->data[0]);
			auto node2 = std::make_unique<gsc::node_float>(inst->data[1]);
			auto node3 = std::make_unique<gsc::node_float>(inst->data[2]);
			auto node = std::make_unique<gsc::node_vector>(std::move(node1), std::move(node2), std::move(node3));
			stack_.push(std::move(node));
		}
		break;
// FUNC REF
		case opcode::OP_GetBuiltinFunction:
		case opcode::OP_GetBuiltinMethod:
		{
			// TODO: as func_ref!!!!
			LOG_ERROR("missing handler 'OP_GetBuiltin'!");
			//auto node = std::make_unique<gsc::node_identifier>(inst->data[0]);
			//stack_.push(std::move(node));
		}
		break;
		case opcode::OP_GetLocalFunction:
		{
			auto file = std::make_unique<gsc::node_filepath>("");
			auto func = std::make_unique<gsc::node_identifier>(inst->data[0].substr(4));
			auto stmt = std::make_unique<gsc::node_expr_function_ref>(std::move(file), std::move(func));
			stack_.push(std::move(stmt));
		}
		break;
		case opcode::OP_GetFarFunction:
		{
			auto file = std::make_unique<gsc::node_filepath>(inst->data[0]);
			auto func = std::make_unique<gsc::node_identifier>(inst->data[1]);
			auto stmt = std::make_unique<gsc::node_expr_function_ref>(std::move(file), std::move(func));
			stack_.push(std::move(stmt));
		};
		break;
//////
		case opcode::OP_End:
		{
			if (&inst != &func->instructions.back())
			{
				auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_return>(std::make_unique<gsc::node>()));
				func_->block->stmts.push_back(std::move(stmt));
			}
		}
		break;
		case opcode::OP_Return:
		{
			auto expr = std::move(stack_.top());
			stack_.pop();
			auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_return>(std::move(expr)));
			func_->block->stmts.push_back(std::move(stmt));
		}
		break;
		
		case opcode::OP_CreateLocalVariable:
		{
			local_vars_.insert(local_vars_.begin(), "var_" + inst->data[0]);
		}
		break;
		case opcode::OP_RemoveLocalVariables:
		{
			for(auto i = std::stoul(inst->data[0]); i > 0; i--)
				local_vars_.erase(local_vars_.begin());
		}
		break;
		case opcode::OP_EvalLocalVariableCached0:
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(0));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalLocalVariableCached1:
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(1));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalLocalVariableCached2:
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(2));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalLocalVariableCached3:
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(3));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalLocalVariableCached4:
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(4));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalLocalVariableCached5:
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(5));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalLocalVariableCached:
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(std::stoul(inst->data[0])));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalLocalArrayCached:
		{
			auto key = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_identifier>(local_vars_.at(std::stoul(inst->data[0]))));
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalArray:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto key = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalNewLocalArrayRefCached0: // creat a local array and initialize
		{
			local_vars_.insert(local_vars_.begin(), "var_" + inst->data[0]);
			auto key = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_identifier>(local_vars_.at(0)));
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalLocalArrayRefCached0: // get last created local array ref
		{
			auto key = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_identifier>(local_vars_.at(0)));
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));	
		}
		break;
		case opcode::OP_EvalLocalArrayRefCached: // get local array ref
		{
			auto key = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_identifier>(local_vars_.at(std::stoul(inst->data[0]))));
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalArrayRef:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto key = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_ClearArray:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto key = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key)));
			auto rvalue = gsc::expr_ptr(std::make_unique<gsc::node_undefined>());
			auto expr = std::make_unique<gsc::node_expr_assign_equal>(std::move(lvalue), std::move(rvalue));
			auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_assign>(std::move(expr)));
			func_->block->stmts.push_back(std::move(stmt));
		}
		break;
		case opcode::OP_AddArray:
		{
			auto var = std::move(stack_.top());
			stack_.pop();
			auto array = std::move(stack_.top());
			stack_.pop();
			
			if (array->type == gsc::node_type::empty_array)
			{
				auto args = std::make_unique<gsc::node_expr_arguments>();
				args->list.push_back(std::move(var));
				auto expr = std::make_unique<gsc::node_expr_add_array>(std::move(args));
				stack_.push(std::move(expr));
			}
			else if (array->type == gsc::node_type::expr_add_array)
			{
				(*(gsc::expr_add_array_ptr*)&array)->args->list.push_back(std::move(var));
				stack_.push(std::move(array));
			}
			else
			{
				LOG_ERROR("unknown add array type (could be an array variable name?)");
			}
		}
		break;
// CALLS
		case opcode::OP_PreScriptCall:
		{
			auto node = std::make_unique<gsc::node_asm_prescriptcall>();
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_ScriptLocalFunctionCall2:
		{
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0].substr(4));
			auto file = std::make_unique<gsc::node_filepath>("");
			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptLocalFunctionCall:
		{
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0].substr(4));
			auto file = std::make_unique<gsc::node_filepath>("");

			auto var = std::move(stack_.top());
			stack_.pop();

			while(var->type != gsc::node_type::asm_prescriptcall)
			{
				args->list.push_back(std::move(var));
				var = std::move(stack_.top());
				stack_.pop();
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptLocalMethodCall:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0].substr(4));
			auto file = std::make_unique<gsc::node_filepath>("");

			auto var = std::move(stack_.top());
			stack_.pop();

			while(var->type != gsc::node_type::asm_prescriptcall)
			{
				args->list.push_back(std::move(var));
				var = std::move(stack_.top());
				stack_.pop();
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptLocalThreadCall:
		{
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0].substr(4));
			auto file = std::make_unique<gsc::node_filepath>("");

			auto argnum = std::stoul(inst->data[1]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto expr = std::make_unique<gsc::node_expr_call>(true, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptLocalChildThreadCall:
		{
			// TODO. take a look at all child things
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0].substr(4));
			auto file = std::make_unique<gsc::node_filepath>("");

			auto argnum = std::stoul(inst->data[1]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto expr = std::make_unique<gsc::node_expr_call>(true, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptLocalMethodThreadCall:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0].substr(4));
			auto file = std::make_unique<gsc::node_filepath>("");

			auto argnum = std::stoul(inst->data[1]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(true, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptLocalMethodChildThreadCall:
		{
			// TODO: child things...
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0].substr(4));
			auto file = std::make_unique<gsc::node_filepath>("");

			auto argnum = std::stoul(inst->data[1]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(true, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptFarFunctionCall2:
		{
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[1]);
			auto file = std::make_unique<gsc::node_filepath>(inst->data[0]);
			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptFarFunctionCall:
		{
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[1]);
			auto file = std::make_unique<gsc::node_filepath>(inst->data[0]);

			auto var = std::move(stack_.top());
			stack_.pop();

			while(var->type != gsc::node_type::asm_prescriptcall)
			{
				args->list.push_back(std::move(var));
				var = std::move(stack_.top());
				stack_.pop();
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptFarMethodCall:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[1]);
			auto file = std::make_unique<gsc::node_filepath>(inst->data[0]);

			auto var = std::move(stack_.top());
			stack_.pop();

			while(var->type != gsc::node_type::asm_prescriptcall)
			{
				args->list.push_back(std::move(var));
				var = std::move(stack_.top());
				stack_.pop();
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptFarThreadCall:
		{
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[2]);
			auto file = std::make_unique<gsc::node_filepath>(inst->data[1]);

			auto argnum = std::stoul(inst->data[0]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto expr = std::make_unique<gsc::node_expr_call>(true, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptFarChildThreadCall:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_ScriptFarChildThreadCall'!");
		}
		break;
		case opcode::OP_ScriptFarMethodThreadCall:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[2]);
			auto file = std::make_unique<gsc::node_filepath>(inst->data[1]);

			auto argnum = std::stoul(inst->data[0]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(true, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptFarMethodChildThreadCall:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_ScriptFarMethodChildThreadCall'!");
		}
		break;
		case opcode::OP_ScriptFunctionCallPointer:
		{
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto exprf = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto var = std::move(stack_.top());
			stack_.pop();

			while(var->type != gsc::node_type::asm_prescriptcall)
			{
				args->list.push_back(std::move(var));
				var = std::move(stack_.top());
				stack_.pop();
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(std::move(exprf), std::move(args)));
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptMethodCallPointer:
		{		
			auto exprf = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto var = std::move(stack_.top());
			stack_.pop();

			while(var->type != gsc::node_type::asm_prescriptcall)
			{
				args->list.push_back(std::move(var));
				var = std::move(stack_.top());
				stack_.pop();
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(std::move(exprf), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptThreadCallPointer:
		{
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto exprf = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto argnum = std::stoul(inst->data[0]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(std::move(exprf), std::move(args)));
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto expr = std::make_unique<gsc::node_expr_call>(true, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptMethodThreadCallPointer:
		{
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto exprf = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto argnum = std::stoul(inst->data[0]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_pointer>(std::move(exprf), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(true, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_ScriptMethodChildThreadCallPointer:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_ScriptMethodChildThreadCallPointer'!");
		}
		break;
		case opcode::OP_CallBuiltinPointer:
		{
			LOG_ERROR("missing handler 'OP_CallBuiltinPointer'!");
			/*auto stmt = func->stack.top(); // pointer

			std::string data = "call [[ " + stmt->data + " ]](";

			auto argnum = std::stoul(inst->data[0]);

			for (size_t i = argnum; i > 0; i--)
			{
				func->stack.pop();
				stmt = func->stack.top();
				data += " " + stmt->data;
				i != 1 ? data += "," : data += " ";
			}

			data += ")";
			stmt->data = data;*/
		}
		break;
		case opcode::OP_CallBuiltinMethodPointer:
		{
			LOG_ERROR("missing handler 'OP_CallBuiltinMethodPointer'!");
			/*auto stmt = func->stack.top(); // pointer
			func->stack.pop();
			std::string data = "call [[ " + stmt->data + " ]](";

			stmt = func->stack.top(); // caller
			data = stmt->data + " " + data;

			auto argnum = std::stoul(inst->data[0]);

			for (size_t i = argnum; i > 0; i--)
			{
				func->stack.pop();
				stmt = func->stack.top();
				data += " " + stmt->data;
				i != 1 ? data += "," : data += " ";
			}

			data += ")";
			stmt->data = data;*/
		}
		break;
		case opcode::OP_CallBuiltin0:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");
			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltin1:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");

			for (size_t i = 1; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}
			
			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltin2:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");

			for (size_t i = 2; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}
			
			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltin3:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");

			for (size_t i = 3; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}
			
			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltin4:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");

			for (size_t i = 4; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}
			
			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltin5:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");

			for (size_t i = 5; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}
			
			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltin:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node>());
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[1]);
			auto file = std::make_unique<gsc::node_filepath>("");

			auto argnum = std::stoul(inst->data[0]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltinMethod0:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltinMethod1:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");

			for (size_t i = 1; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltinMethod2:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");

			for (size_t i = 2; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltinMethod3:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");

			for (size_t i = 3; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltinMethod4:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");

			for (size_t i = 4; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltinMethod5:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto file = std::make_unique<gsc::node_filepath>("");

			for (size_t i = 5; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_CallBuiltinMethod:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[1]);
			auto file = std::make_unique<gsc::node_filepath>("");

			auto argnum = std::stoul(inst->data[0]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto var = std::move(stack_.top());
				stack_.pop();
				args->list.push_back(std::move(var));
			}

			auto func = gsc::expr_call_type_ptr(std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args)));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_DecTop:
		{
			auto expr = std::move(stack_.top());
			stack_.pop();
			auto stmt = std::make_unique<gsc::node_stmt_call>(std::move(*(gsc::expr_call_ptr*)&expr));
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
		}
		break;
// EXPR
		case opcode::OP_inc:
		{
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto expr = std::make_unique<gsc::node_expr_increment>(std::move(lvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_dec:
		{
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto expr = std::make_unique<gsc::node_expr_decrement>(std::move(lvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_bit_or:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_bitwise_or>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_bit_ex_or:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_bitwise_exor>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_bit_and:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_bitwise_and>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_equality:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_equality>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_inequality:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_inequality>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_less:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_less>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_greater:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_greater>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_less_equal:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_less_equal>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_greater_equal:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_greater_equal>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_shift_left:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_shift_left>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_shift_right:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_shift_right>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_plus:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_add>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_minus:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_sub>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_multiply:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_mult>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_divide:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_div>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_mod:
		{
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_mod>(std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(expr));
		}
		break;

// WAIT NOTIFY
		case opcode::OP_wait:
		{
			auto expr = std::move(stack_.top());
			stack_.pop();
			auto stmt = std::make_unique<gsc::node_stmt_wait>(std::move(expr));
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
		}
		break;
		case opcode::OP_waittillFrameEnd:
		{
			auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_waittillframeend>());
			func_->block->stmts.push_back(std::move(stmt));
		}
		break;
		case opcode::OP_waittillmatch2:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_waittillmatch2'!");
		}
		break;
		case opcode::OP_waittill:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto nstr = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto stmt = std::make_unique<gsc::node_stmt_waittill>(std::move(obj) , std::move(nstr), std::move(args));
			stack_.push(std::move(stmt));
		}
		break;
		case opcode::OP_waittillmatch:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto stmt = std::make_unique<gsc::node_stmt_waittillmatch>(std::move(obj), std::move(lvalue), std::move(rvalue));
			stack_.push(std::move(stmt));
		}
		break;
		case opcode::OP_clearparams:
		{
			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto var = std::move(stack_.top());
			stack_.pop();

			while(var->type != gsc::node_type::stmt_waittill && var->type != gsc::node_type::stmt_waittillmatch)
			{
				args->list.push_back(std::move(var));
				var = std::move(stack_.top());
				stack_.pop();
			}

			if(var->type == gsc::node_type::stmt_waittill)
			{
				(*(gsc::stmt_waittill_ptr*)&var)->args = std::move(args);
			}

			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(var)));
		}
		break;
		case opcode::OP_checkclearparams:
		{
			for (size_t i = 0; i < params_; i++)
			{
				local_vars_.at(i).append(utils::string::va("%i", params_ - 1 - i));
				func_->params->list.insert(func_->params->list.begin(), std::make_unique<gsc::node_identifier>(local_vars_.at(i)));
			}
		}
		break;
		case opcode::OP_notify:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto nstr = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			
			auto var = std::move(stack_.top());
			stack_.pop();

			while(var->type != gsc::node_type::asm_voidcodepos)
			{
				args->list.push_back(std::move(var));
				var = std::move(stack_.top());
				stack_.pop();
			}

			auto stmt = std::make_unique<gsc::node_stmt_notify>(std::move(obj) , std::move(nstr), std::move(args));
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
		}
		break;
		case opcode::OP_endon:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto nstr = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto stmt = std::make_unique<gsc::node_stmt_endon>(std::move(obj) , std::move(nstr));
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
		}
		break;
		case opcode::OP_voidCodepos:
		{
			auto node = std::make_unique<gsc::node_asm_voidcodepos>();
			stack_.push(std::move(node));
		}
		break;
/// 
		case opcode::OP_vector:
		{
			auto x = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto y = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto z = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto expr = std::make_unique<gsc::node_expr_vector>(std::move(x), std::move(y),  std::move(z));
			stack_.push(std::move(expr));
		}
		break;	
		case opcode::OP_size:
		{
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_size>(std::move(lvalue));
			stack_.push(std::move(expr));
		}
		break;		
		case opcode::OP_EvalLevelFieldVariable:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_level>());
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto stmt = std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field));
			stack_.push(std::move(stmt));
		}
		break;
		case opcode::OP_EvalAnimFieldVariable:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_anim>());
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto stmt = std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field));
			stack_.push(std::move(stmt));
		}
		break;
		case opcode::OP_EvalSelfFieldVariable:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_self>());
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto stmt = std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field));
			stack_.push(std::move(stmt));
		}
		break;
		case opcode::OP_EvalFieldVariable:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto stmt = std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field));
			stack_.push(std::move(stmt));
		}
		break;
		case opcode::OP_EvalLevelFieldVariableRef:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_level>());
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto stmt = std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field));
			stack_.push(std::move(stmt));
		}
		break;
		case opcode::OP_EvalAnimFieldVariableRef:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_anim>());
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto stmt = std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field));
			stack_.push(std::move(stmt));
		}
		break;
		case opcode::OP_EvalSelfFieldVariableRef:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_self>());
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto stmt = std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field));
			stack_.push(std::move(stmt));
		}
		break;
		case opcode::OP_EvalFieldVariableRef:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto stmt = std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field));
			stack_.push(std::move(stmt));
		}
		break;
		case opcode::OP_ClearFieldVariable:
		{
			auto obj = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto expr = gsc::expr_ptr(std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field)));
			auto undef = gsc::expr_ptr(std::make_unique<gsc::node_undefined>());
			auto e = std::make_unique<gsc::node_expr_assign_equal>(std::move(expr), std::move(undef));
			func_->block->stmts.push_back(gsc::stmt_ptr(std::make_unique<gsc::node_stmt_assign>(std::move(e))));
		}
		break;
		case opcode::OP_SafeCreateVariableFieldCached:
		{
			params_++;
			local_vars_.push_back("var");
		}
		break;
		case opcode::OP_SafeSetVariableFieldCached0:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_SafeSetVariableFieldCached0'!");
		}
		break;
		case opcode::OP_SafeSetVariableFieldCached:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_SafeSetVariableFieldCached'!");
		}
		break;
		case opcode::OP_SafeSetWaittillVariableFieldCached:
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(std::stoul(inst->data[0])));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalLocalVariableRefCached0:
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(0));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalNewLocalVariableRefCached0:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_EvalNewLocalVariableRefCached0'!");
		}
		break;
		case opcode::OP_EvalLocalVariableRefCached:
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(std::stoul(inst->data[0])));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_SetLevelFieldVariableField:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_level>());
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field)));
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto e = std::make_unique<gsc::node_expr_assign_equal>(std::move(lvalue), std::move(rvalue));
			auto stmt = std::make_unique<gsc::node_stmt_assign>(std::move(e));
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
		}
		break;
		case opcode::OP_SetVariableField:
		{
			// TODO: increment decrament need check!!!
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			

			if(lvalue.as_node->type == gsc::node_type::expr_increment)
			{
				auto stmt = std::make_unique<gsc::node_stmt_assign>(std::move(lvalue.as_increment));
				func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
			}
			else if(lvalue.as_node->type == gsc::node_type::expr_decrement)
			{
				auto stmt = std::make_unique<gsc::node_stmt_assign>(std::move(lvalue.as_decrement));
				func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
			}
			else
			{
				auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
				stack_.pop();
				auto e = std::make_unique<gsc::node_expr_assign_equal>(std::move(lvalue), std::move(rvalue));
				auto stmt = std::make_unique<gsc::node_stmt_assign>(std::move(e));
				func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
			}
		}
		break;
		case opcode::OP_ClearVariableField:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_ClearVariableField'!");
		}
		break;
		case opcode::OP_SetAnimFieldVariableField:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_anim>());
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field)));
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto e = std::make_unique<gsc::node_expr_assign_equal>(std::move(lvalue), std::move(rvalue));
			auto stmt = std::make_unique<gsc::node_stmt_assign>(std::move(e));
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
		}
		break;
		case opcode::OP_SetSelfFieldVariableField:
		{
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_self>());
			auto field = std::make_unique<gsc::node_identifier>(inst->data[0]);
			auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_expr_field>(std::move(obj), std::move(field)));
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto e = std::make_unique<gsc::node_expr_assign_equal>(std::move(lvalue), std::move(rvalue));
			auto stmt = std::make_unique<gsc::node_stmt_assign>(std::move(e));
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
		}
		break;
		case opcode::OP_SetLocalVariableFieldCached0:
		{
			auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_identifier>(local_vars_.at(0)));
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto e = std::make_unique<gsc::node_expr_assign_equal>(std::move(lvalue), std::move(rvalue));
			auto stmt = std::make_unique<gsc::node_stmt_assign>(std::move(e));
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
		}
		break;
		case opcode::OP_SetNewLocalVariableFieldCached0:
		{
			local_vars_.insert(local_vars_.begin(), "var_" + inst->data[0]);

			auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_identifier>(local_vars_.at(0)));
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto e = std::make_unique<gsc::node_expr_assign_equal>(std::move(lvalue), std::move(rvalue));
			auto stmt = std::make_unique<gsc::node_stmt_assign>(std::move(e));
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
		}
		break;
		case opcode::OP_SetLocalVariableFieldCached:
		{
			auto lvalue = gsc::expr_ptr(std::make_unique<gsc::node_identifier>(local_vars_.at(std::stoul(inst->data[0]))));
			auto rvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto e = std::make_unique<gsc::node_expr_assign_equal>(std::move(lvalue), std::move(rvalue));
			auto stmt = std::make_unique<gsc::node_stmt_assign>(std::move(e));
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(stmt)));
		}
		break;
		case opcode::OP_ClearLocalVariableFieldCached:
		{
			// TODO: used in for, foreach
			//LOG_ERROR("missing handler 'OP_ClearLocalVariableFieldCached'!");

			// seems like no needed!
		}
		break;
		case opcode::OP_ClearLocalVariableFieldCached0:
		{
			// TODO: used in for, foreach
			//LOG_ERROR("missing handler 'OP_ClearLocalVariableFieldCached0'!");

			// seems like no needed!
		}
		break;
		case opcode::OP_EvalLocalVariableObjectCached:
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(std::stoul(inst->data[0])));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_CastFieldObject:
		{
			//continue;
		}
		break;
		case  opcode::OP_CastBool:
		{
			//continue;
		}
		break;
		case opcode::OP_BoolNot:
		{
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_not>(std::move(lvalue));
			stack_.push(std::move(expr));
		}
		break;
		case opcode::OP_BoolComplement:
		{
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_expr_complement>(std::move(lvalue));
			stack_.push(std::move(expr));
		}
		break;

// SPECIAL SHIT
		case opcode::OP_switch:
		{
			auto expr = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto sw = std::make_unique<gsc::node_asm_switch>(std::move(expr), inst->data[0]);
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(sw)));
		}
		break;
		case opcode::OP_endswitch:
		{
			auto count = inst->data[0];
			inst->data.erase(inst->data.begin());
			auto data = inst->data;
			auto end = std::make_unique<gsc::node_asm_endswitch>(data, inst->data[0]);
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(end)));
		}
		break;
		case opcode::OP_jump:
		{
			auto expr = std::make_unique<gsc::node_asm_jump>(inst->data[0]);
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(expr)));

		}
		break;
		case opcode::OP_jumpback:
		{
			auto expr = std::make_unique<gsc::node_asm_jump_back>(inst->data[0]);
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(expr)));
		}
		break;
		case opcode::OP_JumpOnTrue:
		{
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto e_not = gsc::expr_ptr(std::make_unique<gsc::node_expr_not>(std::move(lvalue)));
			auto expr = std::make_unique<gsc::node_asm_jump_cond>(std::move(e_not), inst->data[0]);
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(expr)));
		}
		break;
		case opcode::OP_JumpOnFalse:
		{
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
	
			auto expr = std::make_unique<gsc::node_asm_jump_cond>(std::move(lvalue), inst->data[0]);
			func_->block->stmts.push_back(gsc::stmt_ptr(std::move(expr)));
		}
		break;
		case opcode::OP_JumpOnTrueExpr:
		{
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_asm_jump_true_expr>(std::move(lvalue), inst->data[0]);
			stack_.push(std::move(expr));
			expr_labels_.push_back(inst->data[0]);
		}
		break;
		case opcode::OP_JumpOnFalseExpr:
		{
			auto lvalue = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();

			auto expr = std::make_unique<gsc::node_asm_jump_false_expr>(std::move(lvalue), inst->data[0]);
			stack_.push(std::move(expr));
			expr_labels_.push_back(inst->data[0]);
		}
		break;
		default:
			LOG_ERROR("unhandled opcode '%s'!", resolver::opcode_name(opcode(inst->opcode)).data());
		break;
		}
	}
}

void decompiler::decompile_expr()
{
	auto expr = std::move(stack_.top());
	stack_.pop();

	auto jump_expr = std::move(stack_.top());
	stack_.pop();

	if(jump_expr->type == gsc::node_type::asm_jump_true_expr)
	{
		auto lvalue = std::move((*(gsc::asm_jump_true_expr_ptr*)&jump_expr)->expr);
		auto rvalue = gsc::expr_ptr(std::move(expr));
		auto e = std::make_unique<gsc::node_expr_or>(std::move(lvalue), std::move(rvalue));
		stack_.push(std::move(e));
	}
	else if(jump_expr->type == gsc::node_type::asm_jump_false_expr)
	{
		auto lvalue = std::move((*(gsc::asm_jump_false_expr_ptr*)&jump_expr)->expr);
		auto rvalue = gsc::expr_ptr(std::move(expr));
		auto e = std::make_unique<gsc::node_expr_and>(std::move(lvalue), std::move(rvalue));
		stack_.push(std::move(e));
	}
	else
	{
		LOG_ERROR("invalid jump expr decompile.");
	}
	
}

void decompiler::decompile_block(const gsc::block_ptr& block)
{
	// check first for empty loops!

	auto index = 0;
	while(index < block->stmts.size())
	{
		auto& stmt = block->stmts.at(index);

		// switch should be first, then loop (jump_back)
		// preventing break, continue missing

		if(stmt.as_node->type == gsc::node_type::asm_jump_cond)
		{
			auto locidx = get_label_index(block, stmt.as_loc->value);

			if(block->stmts.at(locidx-1).as_node->type == gsc::node_type::asm_jump_back)
			{
				// loop (while, for, foreach)
			}
			else if(block->stmts.at(locidx-1).as_node->type == gsc::node_type::asm_jump)
			{
				decompile_ifelse(block, index, locidx);
			}
			else if(block->stmts.at(locidx-1).as_node->type == gsc::node_type::stmt_return
				&& block->stmts.at(locidx-1).as_return->expr.as_node->type == gsc::node_type::null)
			{
				decompile_last_ifelse(block, index, locidx);
			}
			else
			{
				decompile_if(block, index, locidx);
			}
		}

		index++;
	}
	// TODO

	// parse loop (jumpback)

	// for ( ;; )			loop
	// while (1)			loop
	// while ( x )			loop + condition
	// for ( x; y; z )		loop + pre assign + condition + post increment/decrement
	// foreach ( x in y )	loop + pre getfirstarraykey + conditionisdef + assign + post getnextarraykey

	// parse switch
}

void decompiler::decompile_if(const gsc::block_ptr& block, std::uint32_t begin, std::uint32_t end)
{
	auto& stmt = block->stmts.at(begin);

	auto expr = std::move(stmt.as_cond->expr);
	block->stmts.erase(block->stmts.begin() + begin); // remove condition

	// create a block struct and add label as break.

	block->stmts.erase(block->stmts.begin() + end - 1); // remove the if label
	
	auto if_block = std::make_unique<gsc::node_block>();

	for(auto i = begin; i < end - 1; i++)
	{
		if_block->stmts.push_back(std::move(block->stmts[begin]));
		block->stmts.erase(block->stmts.begin() + begin);
	}

	// recursive...
	decompile_block(if_block);

	auto ifstmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_if>(std::move(expr), std::move(if_block)));
	block->stmts.insert(block->stmts.begin() + begin, std::move(ifstmt));
}

void decompiler::decompile_ifelse(const gsc::block_ptr& block, std::uint32_t begin, std::uint32_t end)
{
	auto& stmt = block->stmts.at(begin);

	auto expr = std::move(stmt.as_cond->expr);
	block->stmts.erase(block->stmts.begin() + begin); // remove condition

	// create a block struct and add label as break.

	block->stmts.erase(block->stmts.begin() + end - 1); // remove the if label
	
	auto if_block = std::make_unique<gsc::node_block>();

	for(auto i = begin; i < end - 2; i++) // skip the jump
	{
		if_block->stmts.push_back(std::move(block->stmts[begin]));
		block->stmts.erase(block->stmts.begin() + begin);
	}

	// recursive...
	decompile_block(if_block);

	auto else_label = block->stmts.at(begin).as_jump->value;
	block->stmts.erase(block->stmts.begin() + begin); // remove jump

	auto else_labelidx = get_label_index(block, else_label);
	block->stmts.erase(block->stmts.begin() + begin); // remove label

	auto else_block = std::make_unique<gsc::node_block>();

	for(auto i = begin; i <= else_labelidx; i++)
	{
		else_block->stmts.push_back(std::move(block->stmts[begin]));
		block->stmts.erase(block->stmts.begin() + begin);
	}

	// recursive...
	decompile_block(else_block);

	auto ifelsestmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_ifelse>(std::move(expr), std::move(if_block), std::move(else_block)));
	block->stmts.insert(block->stmts.begin() + begin, std::move(ifelsestmt));
}

void decompiler::decompile_last_ifelse(const gsc::block_ptr& block, std::uint32_t begin, std::uint32_t end)
{
	auto& stmt = block->stmts.at(begin);

	auto expr = std::move(stmt.as_cond->expr);
	block->stmts.erase(block->stmts.begin() + begin); // remove condition

	// create a block struct and add label as break.

	block->stmts.erase(block->stmts.begin() + end - 1); // remove the if label
	
	auto if_block = std::make_unique<gsc::node_block>();

	for(auto i = begin; i < end - 1; i++)
	{
		if_block->stmts.push_back(std::move(block->stmts[begin]));
		block->stmts.erase(block->stmts.begin() + begin);
	}

	// recursive...
	if_block->stmts.erase(if_block->stmts.begin() + if_block->stmts.size()-1); // remove retn;
	decompile_block(if_block);


	// check if there is an else block!!
	if(begin == block->stmts.size())
	{
		LOG_DEBUG("NO ELSE BLOCK");

		auto ifstmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_if>(std::move(expr), std::move(if_block)));
		block->stmts.insert(block->stmts.begin() + begin, std::move(ifstmt));
	}
	else
	{
		auto else_block = std::make_unique<gsc::node_block>();

		for(auto i = begin; i <= block->stmts.size(); i++)
		{
			else_block->stmts.push_back(std::move(block->stmts[begin]));
			block->stmts.erase(block->stmts.begin() + begin);
		}

		// recursive...
		else_block->stmts.erase(else_block->stmts.begin() + else_block->stmts.size()-1); // remove retn;
		decompile_block(else_block);

		auto ifelsestmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_ifelse>(std::move(expr), std::move(if_block), std::move(else_block)));
		block->stmts.insert(block->stmts.begin() + begin, std::move(ifelsestmt));
	}
}

auto decompiler::get_label_index(const gsc::block_ptr& block, const std::string& label) -> std::uint32_t
{
	auto index = 0;
	for(auto& stmt : block->stmts)
	{
		if(stmt.as_node->type == gsc::node_type::asm_loc)
		{
			if(stmt.as_loc->value == label)
			{
				return index;
			}
		}

		index++;
	}

	return 0;
}

} // namespace IW6
