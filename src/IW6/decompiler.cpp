// Copyright 2020 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include "IW6.hpp"

namespace IW6
{

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

		this->decompile_function(func);

		script_->threads.push_back(std::move(func_));
	}
}

auto decompiler::output() -> std::string
{
	output_ = std::make_unique<utils::byte_buffer>(0x100000);

	output_->write_string("// IW6 PC GSC\n");
	output_->write_string("// Decompiled by https://github.com/xensik/gsc-tool\n");

	/*for (auto& func : functions_)
	{
		this->print_function(func);
	}*/

	std::string output;

	//output.resize(output_->pos());
	//memcpy(output.data(), output_->buffer().data(), output.size());

	return output;
}

void decompiler::decompile_function(const gsc::function_ptr& func)
{
	// return type
	//func->is_void = true;

	// parameter list
	//func->params = 0;

	// save last index for labels
	//func->end = (*(func->instructions.end() - 1))->index;
		
	// process instructions to generate statements
	this->decompile_statements(func);

	// generate blocks (for, foreach, while, if, if/else, infinite for, switch)
	//this->decompile_blocks(func);
}

void decompiler::decompile_statements(const gsc::function_ptr& func)
{
	for (auto& inst : func->instructions)
	{
		LOG_INFO("%s", resolver::opcode_name(opcode(inst->opcode)).data());

		//insert labels

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
		/*case opcode::OP_GetAnimation: // TODO !!! 
		{
			
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = "%_unsuported_get_animation_";

			func->stack.push(stmt);
		}
		break;*/
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
		
		

		case opcode::OP_GetBuiltinFunction:
		case opcode::OP_GetBuiltinMethod:
		{
			auto node = std::make_unique<gsc::node_identifier>(inst->data[0]);
			stack_.push(std::move(node));
		}
		break;

		case opcode::OP_waittillFrameEnd:
		{
			auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_waittillframeend>());
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
		case opcode::OP_EvalLocalVariableCached: // need revision for IW6!!!!!!!!!!!!!!!
		{
			auto node = std::make_unique<gsc::node_identifier>(local_vars_.at(std::stoul(inst->data[0])));
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_EvalLocalArrayCached:
		{
			/*auto key = gsc::expr_ptr(std::move(stack_.top()));
			stack_.pop();
			auto obj = gsc::expr_ptr(std::make_unique<gsc::node_identifier>(local_vars_.at(std::stoul(inst->data[0]))));
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));*/
		}
		break;
		case opcode::OP_EvalArray:
		{
			/*auto obj = std::move(stack_.top());
			stack_.pop();
			auto key = std::move(stack_.top());
			stack_.pop();
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));*/
		}
		break;
		case opcode::OP_EvalNewLocalArrayRefCached0: // IW6 have the index after instruction (array)
		{
			/*local_vars_.insert(local_vars_.begin(), "var_" + inst->data[0]);// need to check if this insert at variable_stack begin
			auto key = std::move(stack_.top());
			stack_.pop();
			auto obj = std::make_unique<gsc::node_identifier>(local_vars_.at(0));
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));*/
		}
		break;
		case opcode::OP_EvalLocalArrayRefCached0:
		{
			/*local_vars_.insert(local_vars_.begin(), "var_" + inst->data[0]);
			auto key = std::move(stack_.top());
			stack_.pop();
			auto obj = std::make_unique<gsc::node_identifier>(local_vars_.at(0));
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));*/	
		}
		break;
		case opcode::OP_EvalLocalArrayRefCached:
		{
			/*auto key = std::move(stack_.top());
			stack_.pop();
			auto obj = std::make_unique<gsc::node_identifier>(local_vars_.at(std::stoul(inst->data[0])));
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));*/
		}
		break;
		case opcode::OP_EvalArrayRef:
		{
			/*auto obj = std::move(stack_.top());
			stack_.pop();
			auto key = std::move(stack_.top());
			stack_.pop();
			auto node = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			stack_.push(std::move(node));*/
		}
		break;
		case opcode::OP_ClearArray:
		{
			/*auto obj = std::move(stack_.top());
			stack_.pop();
			auto key = std::move(stack_.top());
			stack_.pop();

			auto lvalue = std::make_unique<gsc::node_expr_array>(std::move(obj), std::move(key));
			auto rvalue = std::make_unique<gsc::node_undefined>();
			auto expr = std::make_unique<gsc::node_expr_assign_equal>(std::move(lvalue), std::move(rvalue));
			auto stmt = gsc::stmt_ptr(std::make_unique<gsc::node_stmt_assign>(std::move(expr)));
			func_->block->stmts.push_back(std::move(stmt));*/
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
		case opcode::OP_PreScriptCall:
		{
			auto node = std::make_unique<gsc::node_identifier>("pre_script_call");
			stack_.push(std::move(node));
		}
		break;
		case opcode::OP_ScriptLocalFunctionCall2:
		{
			/*auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0].substr(4));
			auto file = std::make_unique<gsc::node_filepath>("");
			auto func = std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args));
			auto obj = std::make_unique<gsc::node>();
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));*/
		}
		break;
		case opcode::OP_ScriptLocalFunctionCall:
		{
			/*auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0].substr(4));
			auto file = std::make_unique<gsc::node_filepath>("");

			auto var = std::move(stack_.top());
			stack_.pop();

			while(var->type != gsc::node_type::identifier && (*(gsc::identifier_ptr*)&var)->value != "pre_script_call")
			{
				args->list.push_back(std::move(var));
				var = std::move(stack_.top());
				stack_.pop();
			}

			auto func = std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args));
			auto obj = std::make_unique<gsc::node>();
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));*/
		}
		break;
		case opcode::OP_ScriptLocalMethodCall:
		{
			/*auto obj = std::move(stack_.top());
			stack_.pop();

			auto args = std::make_unique<gsc::node_expr_arguments>();
			auto name = std::make_unique<gsc::node_identifier>(inst->data[0].substr(4));
			auto file = std::make_unique<gsc::node_filepath>("");

			auto var = std::move(stack_.top());
			stack_.pop();

			while(var->type != gsc::node_type::identifier && (*(gsc::identifier_ptr*)&var)->value != "pre_script_call")
			{
				args->list.push_back(std::move(var));
				var = std::move(stack_.top());
				stack_.pop();
			}

			auto func = std::make_unique<gsc::node_expr_call_function>(std::move(file), std::move(name), std::move(args));
			auto expr = std::make_unique<gsc::node_expr_call>(false, std::move(obj) ,std::move(func));
			stack_.push(std::move(expr));*/
		}
		break;
		/*case opcode::OP_ScriptLocalThreadCall:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = "self thread " + inst->data[0].substr(4) + "(";

			auto argnum = std::stoul(inst->data[1]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto stmt2 = func->stack.top();
				func->stack.pop();
				stmt->index = stmt2->index;
				stmt->data += " " + stmt2->data;
				i != 1 ? stmt->data += "," : stmt->data += " ";
			}

			stmt->data += ")";
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_ScriptLocalChildThreadCall:
		{
			// TODO. take a look at all child things
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = "self thread " + inst->data[0].substr(4) + "(";

			auto argnum = std::stoul(inst->data[1]);

			for (size_t i = argnum; i > 0; i--)
			{
				auto stmt2 = func->stack.top();
				func->stack.pop();
				stmt->index = stmt2->index;
				stmt->data += " " + stmt2->data;
				i != 1 ? stmt->data += "," : stmt->data += " ";
			}

			stmt->data += ")";
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_ScriptLocalMethodThreadCall:
		{
			auto stmt = func->stack.top();
			auto data = stmt->data + " thread " + inst->data[0].substr(4) + "(";

			auto argnum = std::stoul(inst->data[1]);

			for (size_t i = argnum; i > 0; i--)
			{
				func->stack.pop();
				stmt = func->stack.top();
				data += " " + stmt->data;
				i != 1 ? data += "," : data += " ";
			}

			stmt->data = data + ")";
		}
		break;
		case opcode::OP_ScriptLocalMethodChildThreadCall:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_ScriptLocalMethodChildThreadCall'!");
		}
		break;
		case opcode::OP_ScriptFarFunctionCall2:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = utils::string::va("%s::%s()", inst->data[0].data(), inst->data[1].data());
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_ScriptFarFunctionCall:
		{
			std::string params = utils::string::va("%s::%s( ", inst->data[0].data(), inst->data[1].data());

			auto stmt = func->stack.top();

			while (stmt->data != "pre_script_call")
			{
				params += stmt->data + ", ";
				func->stack.pop();
				stmt = func->stack.top(); // swap pointers
			}

			params.erase(params.end() - 2, params.end()); // TODO: FIX THIS, SHOULD ONLY BE CALLED IF PARAMS > 0
			params.append(" )");
			stmt->data = params;
		}
		break;
		case opcode::OP_ScriptFarMethodCall:
		{
			auto stmt = func->stack.top();
			func->stack.pop();
			std::string params = stmt->data + " " + inst->data[0] + "::" + inst->data[1] + "(";

			stmt = func->stack.top();

			while (stmt->data != "pre_script_call")
			{
				params.append(" " + stmt->data);
				func->stack.pop();
				stmt = func->stack.top();
				stmt->data != "pre_script_call" ? params.append(",") : params.append(" ");
			}
			params.append(")");
			stmt->data = params;
		}
		break;
		case opcode::OP_ScriptFarThreadCall:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			std::string data = "thread " + inst->data[1] + "::" + inst->data[2] + "(";

			auto argnum = std::stoul(inst->data[0]);

			for (size_t i = argnum; i > 0; i--)
			{	
				stmt = func->stack.top();
				func->stack.pop();
				data += " " + stmt->data;
				i != 1 ? data += "," : data += " ";
			}

			data += ")";
			stmt->data = data;
			func->stack.push(stmt);
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
			auto stmt = func->stack.top(); // caller
			std::string data = stmt->data + " thread " + inst->data[1] + "::" + inst->data[2] + "(";

			auto argnum = std::stoul(inst->data[0]);

			for (size_t i = argnum; i > 0; i--)
			{
				func->stack.pop();
				stmt = func->stack.top();
				data += " " + stmt->data;
				i != 1 ? data += "," : data += " ";
			}

			data += ")";
			stmt->data = data;
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
			std::string params;
			auto stmt = func->stack.top();
			params = utils::string::va("[[ %s ]](", stmt->data.data());
			func->stack.pop();
			stmt = func->stack.top();

			auto count = 0;
			while (stmt->data != "pre_script_call")
			{
				params += stmt->data + ", ";
				func->stack.pop();
				stmt = func->stack.top(); // swap pointers
				count++;
			}
			if (count)
			{
				params.erase(params.end() - 2, params.end());
			}
			params.append(" )");
			stmt->data = params;
		}
		break;
		case opcode::OP_ScriptMethodCallPointer:
		{
			auto stmt = func->stack.top(); // pointer
			func->stack.pop();
			std::string data = "[[ " + stmt->data + " ]](";
				
			stmt = func->stack.top(); // caller
			func->stack.pop();
			data = stmt->data + " " + data;

			stmt = func->stack.top(); // params

			while (stmt->data != "pre_script_call")
			{
				data += " " + stmt->data;
				func->stack.pop();
				stmt = func->stack.top();
				stmt->data != "pre_script_call" ? data += "," : data += " ";
			}
	
			data += ")";
			stmt->data = data;
		}
		break;
		case opcode::OP_ScriptThreadCallPointer:
		{
			auto stmt = func->stack.top();
				
			std::string data = "thread [[ " + stmt->data + " ]](";

			auto argnum = std::stoul(inst->data[0]);

			for (size_t i = argnum; i > 0; i--)
			{
				func->stack.pop();
				stmt = func->stack.top();
				data += " " + stmt->data;
				i != 1 ? data += "," : data += " ";
			}

			data += ")";
			stmt->data = data;
		}
		break;
		case opcode::OP_ScriptMethodThreadCallPointer:
		{
			auto stmt = func->stack.top(); // pointer
			func->stack.pop();
			std::string data = "thread [[ " + stmt->data + " ]](";

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
			stmt->data = data;
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
			auto stmt = func->stack.top(); // pointer

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
			stmt->data = data;
		}
		break;
		case opcode::OP_CallBuiltinMethodPointer:
		{
			auto stmt = func->stack.top(); // pointer
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
			stmt->data = data;
		}
		break;
		

		case opcode::OP_inc:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = "++";
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_dec:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = "--";
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_bit_or:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s | %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_JumpOnFalseExpr:
		{
			// TODO
			auto stmt1 = func->stack.top();
			func->stack.pop();
			stmt1->data = utils::string::va("cond_false_expr ( %s ) #%s", stmt1->data.data(), inst->data[0].data());
			func->statements.push_back(stmt1);
		}
		break;
		case opcode::OP_bit_ex_or:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s ^ %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_bit_and:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s & %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_equality:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s == %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_inequality:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s != %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_less:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s < %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_greater:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s > %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_JumpOnTrueExpr:
		{
			// TODO
			auto stmt1 = func->stack.top();
			func->stack.pop();
			stmt1->data = utils::string::va("cond_true_expr ( %s ) #%s", stmt1->data.data(), inst->data[0].data());
			func->statements.push_back(stmt1);
		}
		break;
		case opcode::OP_less_equal:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s <= %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_jumpback:
		{
			// TODO
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = utils::string::va("cond_loop #%s", inst->data[0].data());
			func->statements.push_back(stmt);
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
			this->in_waittill_ = true;

			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();

			stmt1->data = utils::string::va("%s waittill( %s", stmt2->data.data(), stmt1->data.data());
		}
		break;
		case opcode::OP_notify:
		{
			auto stmt1 = func->stack.top();
			func->stack.pop();
			auto stmt = func->stack.top();
			func->stack.pop();
			auto data = stmt1->data + " notify(" + stmt->data;

			stmt = func->stack.top(); // params
			func->stack.pop();

			while (stmt->data != "voidcodepos")
			{
				data += ", " + stmt->data;
				stmt = func->stack.top();
				func->stack.pop();
			}

			data += " );";
			stmt->data = data;
			func->statements.push_back(stmt);
		}
		break;
		case opcode::OP_endon:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			func->stack.pop();
			stmt1->data = utils::string::va("%s endon(%s);", stmt2->data.data(), stmt1->data.data());
			func->statements.push_back(stmt1);
		}
		break;
		case opcode::OP_voidCodepos:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = "voidcodepos";
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_switch:
		{
			// TODO
			auto stmt = func->stack.top();
			func->stack.pop();
			stmt->data = utils::string::va("switch ( %s ) #%s", stmt->data.data(), inst->data[0].data());
			func->statements.push_back(stmt);
		}
		break;
		case opcode::OP_endswitch:
		{
			// TODO
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = resolver::opcode_name(opcode(inst->opcode));
			for (auto d : inst->data)
			{
				stmt->data.append(" " + d);
			}
			stmt->data.append(";");
			func->statements.push_back(stmt);
		}
		break;
		case opcode::OP_vector:
		{
			auto stmt3 = func->stack.top();
			func->stack.pop();
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = "( " + stmt3->data + ", " + stmt2->data + ", " + stmt1->data + " )";
		}
		break;
		case opcode::OP_JumpOnFalse:
		{
			auto stmt1 = func->stack.top();
			func->stack.pop();
			stmt1->data = utils::string::va("cond ( %s ) #%s", stmt1->data.data(), inst->data[0].data());
			func->statements.push_back(stmt1);

			// dirty shit
			if (func->labels.find(inst->index) != func->labels.end())
			{
				auto loc = func->labels.extract(inst->index);
				loc.key() = stmt1->index;
				func->labels.insert(std::move(loc));
			}
		}
		break;
		case opcode::OP_greater_equal:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s >= %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_shift_left:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_shift_left'!");
		}
		break;
		case opcode::OP_shift_right:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_shift_right'!");
		}
		break;
		case opcode::OP_plus:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s + %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_jump:
		{
			// TODO
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = utils::string::va("cond_no #%s;", inst->data[0].data());
			func->statements.push_back(stmt);
		}
		break;
		case opcode::OP_minus:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s - %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_multiply:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s * %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_divide:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = utils::string::va("%s / %s", stmt1->data.data(), stmt2->data.data());
		}
		break;
		case opcode::OP_mod:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			stmt1->data = stmt1->data + " % " + stmt2->data;
		}
		break;
		case opcode::OP_JumpOnTrue: // negate condition and replace with false: equals 'if (!epxr)'
		{
			auto stmt1 = func->stack.top();
			func->stack.pop();
			stmt1->data = utils::string::va("cond ( !%s ) #%s", stmt1->data.data(), inst->data[0].data());
			func->statements.push_back(stmt1);

			// dirty shit
			if (func->labels.find(inst->index) != func->labels.end())
			{
				auto loc = func->labels.extract(inst->index);
				loc.key() = stmt1->index;
				func->labels.insert(std::move(loc));
			}
		}
		break;
		case opcode::OP_size:
		{
			auto stmt = func->stack.top();
			stmt->data = utils::string::va("%s.size", stmt->data.data());
		}
		break;
		case opcode::OP_waittillmatch:
		{
			this->in_waittill_ = true;

			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			func->stack.pop();
			auto stmt = func->stack.top();
			stmt->data = stmt2->data + " waittillmatch( " + stmt1->data + ", " + stmt->data;
		}
		break;
		case opcode::OP_GetLocalFunction:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = utils::string::va("::%s", inst->data[0].substr(4).data());
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_GetFarFunction:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = utils::string::va("%s::%s", inst->data[0].data(), inst->data[1].data());
			func->stack.push(stmt);
		};
		break;
		
		case opcode::OP_EvalLevelFieldVariable:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = utils::string::va("level.%s", inst->data[0].data());
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_EvalAnimFieldVariable:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = utils::string::va("anim.%s", inst->data[0].data());
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_EvalSelfFieldVariable:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = utils::string::va("self.%s", inst->data[0].data());
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_EvalFieldVariable:
		{
			auto stmt = func->stack.top();
			stmt->data = utils::string::va("%s.%s", stmt->data.data(), inst->data[0].data());
		}
		break;
		case opcode::OP_EvalLevelFieldVariableRef:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = utils::string::va("level.%s", inst->data[0].data());
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_EvalAnimFieldVariableRef:
		{
			// TODO: check it!
			LOG_ERROR("missing handler 'OP_EvalAnimFieldVariableRef'!");
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = "anim." + inst->data[0];
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_EvalSelfFieldVariableRef:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = "self." + inst->data[0];
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_EvalFieldVariableRef:
		{
			auto stmt = func->stack.top();
			stmt->data = stmt->data + "." + inst->data[0];
		}
		break;
		case opcode::OP_ClearFieldVariable:
		{
			auto stmt = func->stack.top();
			func->stack.pop();
			stmt->data = utils::string::va("%s.%s = undefined;", stmt->data.data(), inst->data[0].data());
			func->statements.push_back(stmt);
		}
		break;
		case opcode::OP_SafeCreateVariableFieldCached:
		{
			func->params++;
			func->local_vars.push_back("var");
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
			auto stmt = func->stack.top();
			stmt->data += ", " + func->local_vars.at(std::stoul(inst->data[0]));
		}
		break;
		case opcode::OP_GetAnimTree:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_GetAnimTree'!");
		}
		break;
		case opcode::OP_clearparams:
		{
			if (this->in_waittill_)
			{
				this->in_waittill_ = false;
			}

			auto stmt1 = func->stack.top();
			func->stack.pop();

			stmt1->data = stmt1->data + " );";
			func->statements.push_back(stmt1);
		}
		break;
		case opcode::OP_checkclearparams:
		{
			for (size_t i = 0; i < func->params; i++)
			{
				func->local_vars.at(i).append(utils::string::va("%i", func->params - 1 - i));
			}
		}
		break;
		case opcode::OP_EvalLocalVariableRefCached0:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = func->local_vars.at(0).data();
			func->stack.push(stmt);
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
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = func->local_vars.at(std::stoul(inst->data[0])).data();
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_SetLevelFieldVariableField:
		{
			auto stmt1 = func->stack.top();
			func->stack.pop();
			stmt1->data = utils::string::va("level.%s = %s;", inst->data[0].data(), stmt1->data.data());
			func->statements.push_back(stmt1);
		}
		break;
		case opcode::OP_SetVariableField:
		{
			auto stmt2 = func->stack.top();
			func->stack.pop();
			auto stmt1 = func->stack.top();
			func->stack.pop();
			if (stmt2->data == "++" || stmt2->data == "--")
			{
				stmt1->data = utils::string::va("%s%s;", stmt1->data.data(), stmt2->data.data());
			}
			else
			{
				stmt1->data = utils::string::va("%s = %s;", stmt2->data.data(), stmt1->data.data());
			}
				
			func->statements.push_back(stmt1);
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
			// TODO
			LOG_ERROR("missing handler 'OP_SetAnimFieldVariableField'!");
		}
		break;
		case opcode::OP_SetSelfFieldVariableField:
		{
			auto stmt1 = func->stack.top();
			func->stack.pop();
			stmt1->data = utils::string::va("self.%s = %s;", inst->data[0].data(), stmt1->data.data());
			func->statements.push_back(stmt1);
		}
		break;
		case opcode::OP_SetLocalVariableFieldCached0:
		{
			auto stmt = func->stack.top();
			func->stack.pop();
			stmt->data = func->local_vars.at(0) + " = " + stmt->data + ";";
			func->statements.push_back(stmt);
		}
		break;
		case opcode::OP_SetNewLocalVariableFieldCached0:
		{
			func->local_vars.insert(func->local_vars.begin(), "var_" + inst->data[0]);

			auto stmt1 = func->stack.top();
			func->stack.pop();
			stmt1->data = utils::string::va("%s = %s;", func->local_vars.at(0).data(), stmt1->data.data());
			func->statements.push_back(stmt1);
		}
		break;
		case opcode::OP_SetLocalVariableFieldCached:
		{
			auto stmt = func->stack.top();
			func->stack.pop();
			stmt->data = func->local_vars.at(std::stoul(inst->data[0])) + " = " + stmt->data.data() + ";";
			func->statements.push_back(stmt);
		}
		break;
		case opcode::OP_ClearLocalVariableFieldCached:
		{
			// TODO
			// LOG_ERROR("missing handler 'OP_ClearLocalVariableFieldCached'!");

			// seems like no needed!
		}
		break;
		case opcode::OP_ClearLocalVariableFieldCached0:
		{
			// TODO
			// LOG_ERROR("missing handler 'OP_ClearLocalVariableFieldCached0'!");

			// seems like no needed!
		}
		break;
		case opcode::OP_CallBuiltin0:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = inst->data[0] + "()";
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_CallBuiltin1:
		{
			auto stmt = func->stack.top();
			stmt->data = inst->data[0] + "( " + stmt->data + " )";
		}
		break;
		case opcode::OP_CallBuiltin2:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = inst->data[0] + "(";

			for (size_t i = 2; i > 0; i--)
			{
				auto stmt2 = func->stack.top();
				func->stack.pop();
				stmt->index = stmt2->index;
				stmt->data += " " + stmt2->data;
				i != 1 ? stmt->data += "," : stmt->data += " ";
			}

			stmt->data += ")";
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_CallBuiltin3:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = inst->data[0] + "(";

			for (size_t i = 3; i > 0; i--)
			{
				auto stmt2 = func->stack.top();
				func->stack.pop();
				stmt->index = stmt2->index;
				stmt->data += " " + stmt2->data;
				i != 1 ? stmt->data += "," : stmt->data += " ";
			}

			stmt->data += ")";
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_CallBuiltin4:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = inst->data[0] + "(";

			for (size_t i = 4; i > 0; i--)
			{
				auto stmt2 = func->stack.top();
				func->stack.pop();
				stmt->index = stmt2->index;
				stmt->data += " " + stmt2->data;
				i != 1 ? stmt->data += "," : stmt->data += " ";
			}

			stmt->data += ")";
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_CallBuiltin5:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = inst->data[0] + "(";

			for (size_t i = 5; i > 0; i--)
			{
				auto stmt2 = func->stack.top();
				func->stack.pop();
				stmt->index = stmt2->index;
				stmt->data += " " + stmt2->data;
				i != 1 ? stmt->data += "," : stmt->data += " ";
			}

			stmt->data += ")";
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_CallBuiltin:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = inst->data[1] + "(";

			auto paracount = std::stoul(inst->data[0]);

			for (size_t i = paracount; i > 0; i--)
			{
				auto stmt2 = func->stack.top();
				func->stack.pop();
				stmt->index = stmt2->index;
				stmt->data += " " + stmt2->data;
				i != 1 ? stmt->data += "," : stmt->data += " ";
			}

			stmt->data += ")";
			func->stack.push(stmt);
		}
		break;
		case opcode::OP_CallBuiltinMethod0:
		{
			auto stmt = func->stack.top();
			stmt->data = utils::string::va("%s %s()", stmt->data.data(), inst->data[0].data());
		}
		break;
		case opcode::OP_CallBuiltinMethod1:
		{
			auto stmt = func->stack.top();
			func->stack.pop();
			auto stmt2 = func->stack.top();
			stmt2->data = utils::string::va("%s %s( %s )", stmt->data.data(), inst->data[0].data(), stmt2->data.data());
		}
		break;
		case opcode::OP_CallBuiltinMethod2:
		{
			auto stmt = func->stack.top();

			std::string params = utils::string::va("%s %s( ", stmt->data.data(), inst->data[0].data());

			for (size_t i = 0; i < 2; i++)
			{
				func->stack.pop();
				stmt = func->stack.top();
				params.append(stmt->data);
				if (i != 1)
				{
					params.append(", ");
				}
			}

			params.append(" )");
			stmt->data = params.data();
		}
		break;
		case opcode::OP_CallBuiltinMethod3:
		{
			auto stmt = func->stack.top();
	
			std::string params = utils::string::va("%s %s( ", stmt->data.data(), inst->data[0].data());
				
			for (size_t i = 0; i < 3; i++)
			{
				func->stack.pop();
				stmt = func->stack.top();
				params.append(stmt->data);
				if (i != 2)
				{
					params.append(", ");
				}
			}

			params.append(" )");
			stmt->data = params.data();
		}
		break;
		case opcode::OP_CallBuiltinMethod4:
		{
			auto stmt = func->stack.top();

			std::string params = utils::string::va("%s %s( ", stmt->data.data(), inst->data[0].data());

			for (size_t i = 0; i < 4; i++)
			{
				func->stack.pop();
				stmt = func->stack.top();
				params.append(stmt->data);
				if (i != 3)
				{
					params.append(", ");
				}
			}

			params.append(" )");
			stmt->data = params.data();
		}
		break;
		case opcode::OP_CallBuiltinMethod5:
		{
			auto stmt = func->stack.top();
			std::string data = stmt->data + " " + inst->data[0] + "(";

			for (size_t i = 0; i < 5; i++)
			{
				func->stack.pop();
				stmt = func->stack.top();
				data += " " + stmt->data;
				i != 4 ? data += "," : data += " ";
			}

			data += ")";
			stmt->data = data.data();
		}
		break;
		case opcode::OP_CallBuiltinMethod:
		{
			auto stmt = func->stack.top(); // method caller, level self or var
			func->stack.pop();

			stmt->data = utils::string::va("%s %s( ", stmt->data.data(), inst->data[1].data());

			auto paracount = std::stoul(inst->data[0]);
			for (size_t i = 0; i < paracount; i++)
			{
				auto stmt2 = func->stack.top();
				func->stack.pop();

				stmt->data.append(stmt2->data + ", ");

				if (i == paracount - 1)
				{
					stmt->index = stmt2->index;
					stmt->data.erase(stmt->data.end() - 2);
				}
			}
			stmt->data.append(" )");
			func->stack.push(stmt);
		}
		break;
		case  opcode::OP_wait:
		{
			auto stmt = func->stack.top();
			func->stack.pop();
			stmt->data = "wait " + stmt->data + ";";
			func->statements.push_back(stmt);
		}
		break;
		case opcode::OP_DecTop:
		{
			auto stmt = func->stack.top();
			func->stack.pop();
			stmt->data = stmt->data + ";";
			func->statements.push_back(stmt);
		}
		break;
		case opcode::OP_CastFieldObject:
		{
			continue;
		}
		break;
		case opcode::OP_EvalLocalVariableObjectCached:
		{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = func->local_vars.at(std::stoul(inst->data[0]));
			func->stack.push(stmt);
		}
		break;
		case  opcode::OP_CastBool:
		{
			continue;
		}
		break;
		case opcode::OP_BoolNot:
		{
			auto stmt = func->stack.top();
			stmt->data = "!" + stmt->data;
		}
		break;
		case opcode::OP_BoolComplement:
		{
			// TODO
			LOG_ERROR("missing handler 'OP_BoolComplement'!");
		}
		break;*/
		default:
		/*{
			auto stmt = std::make_shared<statement>();
			stmt->index = inst->index;
			stmt->data = resolver::opcode_name(opcode(inst->opcode));
			for (auto d : inst->data)
			{
				stmt->data.append(" " + d);
			}
			stmt->data.append(";");
			func->statements.push_back(stmt);
		}*/
		break;
		}
	}
}

void decompiler::decompile_blocks()
{
	// TODO

	// first parse and group conditions in a single statement

	// if ( x && y )    cond_false_expr + cond;
	// if ( x || y )	cond_true_expr + cond;

	// then parse easy blocks

	// for ( ;; )			loop
	// while (1)			loop
	// while ( x )			loop + condition
	// for ( x; y; z )		loop + pre assign + condition + post increment/decrement
	// foreach ( x in y )	loop + pre getfirstarraykey + conditionisdef + assign + post getnextarraykey

	// then parse if/ else if / else blocks

}

void decompiler::print_function()
{
}

void decompiler::print_statement()
{
}

void decompiler::print_label(const std::string& label)
{
}

} // namespace IW6
