#include "stdinc.hpp"
#include "decompiler.hpp"

namespace gsc
{
	decompiler::decompiler()
	{
		output_ = std::make_unique<byte_buffer>(0x100000);
	}

	void decompiler::decompile(std::vector<std::shared_ptr<function>>& functions)
	{
		for (auto func : functions)
		{
			auto dfunc = std::make_shared<decompiler_function>();
			functions_.push_back(dfunc);

			dfunc->labels_ = func->m_labels;
			dfunc->instructions_ = func->m_instructions;
			dfunc->name_ = func->m_name != "" ? func->m_name : utils::string::va("sub_%i", func->m_id);

			this->decompile_function(dfunc);
		}
	}

	auto decompiler::output() -> std::vector<std::uint8_t>
	{
		output_->write_cpp_string("// IW5 PC GSC\n");
		output_->write_cpp_string("// Decompiled by https://github.com/xensik/gsc-tool\n");

		for (auto& func : functions_)
		{
			this->print_function(func);
		}

		std::vector<std::uint8_t> output;
		output.resize(output_->get_pos());
		memcpy(output.data(), output_->get_buffer().data(), output.size());

		return output;
	}

	void decompiler::decompile_function(std::shared_ptr<decompiler_function> func)
	{
		// return type
		func->is_void = true;

		// parameter list
		func->params_ = 0;

		// save last index for labels
		func->end_ = (*(func->instructions_.end() - 1))->m_index;
		
		// process instructions to generate statements
		this->decompile_statements(func);

		// generate blocks (for, foreach, while, if, if/else, infinite for, switch)
		this->decompile_blocks(func);
	}

	void decompiler::decompile_statements(std::shared_ptr<decompiler_function> func)
	{
		for (auto inst : func->instructions_)
		{
			switch (inst->m_opcode)
			{
			case opcode::OP_End:
			{
				if (!func->is_void)
				{
					/*auto stmt = func->stack_.top();
					if (stmt->data_.find("return") != std::string::npos)
					{
						func->stack_.pop();
						func->statements_.push_back(stmt);
					}	*/			
				}
				else if (inst->m_index != func->end_)
				{
					auto stmt = std::make_shared<statement>();
					stmt->index_ = inst->m_index;
					stmt->data_ = utils::string::va("return;");
					func->statements_.push_back(stmt);
				}
			}
			break;
			case opcode::OP_Return:
			{
				func->is_void = false;
				auto stmt = func->stack_.top();
				func->stack_.pop();
				stmt->data_ = "return "+ stmt->data_ + ";";
				func->statements_.push_back(stmt);
			}
			break;
			case opcode::OP_GetByte:		
			case opcode::OP_GetUnsignedShort:
			case opcode::OP_GetInteger:
			case opcode::OP_GetBuiltinFunction:
			case opcode::OP_GetBuiltinMethod:
			case opcode::OP_GetFloat: // TODO: append .0 if integer / remove 0. if < 0
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = inst->m_data[0];
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_GetString:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = inst->m_data[0];

				for (size_t i = 0; i < stmt->data_.size(); i++)
				{
					if (stmt->data_.at(i) == '\\')
					{
						stmt->data_.insert(stmt->data_.begin() + i, '\\');
						i++;
					}
				}
				for (size_t i = 1; i < stmt->data_.size() - 1; i++)
				{
					if (stmt->data_.at(i) == '\"')
					{
						stmt->data_.insert(stmt->data_.begin() + i, '\\');
						i++;
					}
				}

				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_GetNegByte:
			case opcode::OP_GetNegUnsignedShort:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "-" + inst->m_data[0];
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_GetUndefined:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "undefined";

				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_GetZero:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "0";

				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_waittillFrameEnd:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "waittillframeend;";

				func->statements_.push_back(stmt);
			}
			break;
			case opcode::OP_CreateLocalVariable:
			{
				size_t index = std::stoul(inst->m_data[0]);
				func->local_vars_.insert(func->local_vars_.begin(), utils::string::va("var%i", index));
			}
			break;
			case opcode::OP_RemoveLocalVariables:
			{
				// TODO
				//LOG_ERROR("missing handler 'OP_RemoveLocalVariables'!");
				
				// no needed?
			}
			break;
			case opcode::OP_EvalLocalVariableCached0:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = func->local_vars_.at(0);
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalLocalVariableCached1:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = func->local_vars_.at(1);
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalLocalVariableCached2:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = func->local_vars_.at(2);
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalLocalVariableCached3:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = func->local_vars_.at(3);
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalLocalVariableCached4:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = func->local_vars_.at(4);
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalLocalVariableCached5:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = func->local_vars_.at(5);
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalLocalVariableCached:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = func->local_vars_.at(std::stoul(inst->m_data[0]));
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalLocalArrayCached:
			{
				auto stmt = func->stack_.top();
				stmt->data_ = utils::string::va("%s[%s]", func->local_vars_.at(std::stoul(inst->m_data[0])).data(), stmt->data_.data());
			}
			break;
			case opcode::OP_EvalArray:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s[%s]", stmt2->data_.data(), stmt1->data_.data());
			}
			break;
			case opcode::OP_EvalNewLocalArrayRefCached0:
			{
				auto stmt = func->stack_.top();
				stmt->data_ = utils::string::va("%s[%s]", func->local_vars_.at(0).data(), stmt->data_.data());
			}
			break;
			case opcode::OP_EvalLocalArrayRefCached0:
			{
				auto stmt = func->stack_.top();
				func->local_vars_.insert(func->local_vars_.begin(), utils::string::va("var%i", std::stoul(inst->m_data[0])));
				stmt->data_ = utils::string::va("%s[%s]", func->local_vars_.at(0).data(), stmt->data_.data());
			}
			break;
			case opcode::OP_EvalLocalArrayRefCached:
			{
				auto stmt = func->stack_.top();
				stmt->data_ = utils::string::va("%s[%s]", func->local_vars_.at(std::stoul(inst->m_data[0])).data(), stmt->data_.data());
			}
			break;
			case opcode::OP_EvalArrayRef:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s[%s]", stmt2->data_.data(), stmt1->data_.data());
			}
			break;
			case opcode::OP_ClearArray:
			{
				auto stmt = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				stmt1->data_ = utils::string::va("%s[%s] = undefined;", stmt->data_.data(), stmt1->data_.data());
				func->statements_.push_back(stmt1);
			}
			break;
			case opcode::OP_EmptyArray:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "[]";

				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_AddArray:
			{
				// TODO
				LOG_ERROR("missing handler 'OP_AddArray'!");
			}
			break;
			case opcode::OP_PreScriptCall:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "pre_script_call";

				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_ScriptLocalFunctionCall2:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = utils::string::va("%s()", inst->m_data[0].substr(4).data());
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_ScriptLocalFunctionCall:
			{
				std::string data = inst->m_data[0].substr(4) + "(";

				auto stmt = func->stack_.top();

				while (stmt->data_ != "pre_script_call")
				{
					data += " " + stmt->data_;
					func->stack_.pop();
					stmt = func->stack_.top();
					stmt->data_ != "pre_script_call" ? data += "," : data += " ";
				}
				data += ")";
				stmt->data_ = data;
			}
			break;
			case opcode::OP_ScriptLocalMethodCall:
			{
				auto stmt = func->stack_.top();
				func->stack_.pop();
				std::string data = stmt->data_ + " " + inst->m_data[0].substr(4) + "(";

				stmt = func->stack_.top();

				while (stmt->data_ != "pre_script_call")
				{
					data += " " + stmt->data_;
					func->stack_.pop();
					stmt = func->stack_.top();
					stmt->data_ != "pre_script_call" ? data += "," : data += " ";
				}
				data += ")";
				stmt->data_ = data;
			}
			break;
			case opcode::OP_ScriptLocalThreadCall:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "self thread " + inst->m_data[0].substr(4) + "(";

				auto argnum = std::stoul(inst->m_data[1]);

				for (size_t i = argnum; i > 0; i--)
				{
					auto stmt2 = func->stack_.top();
					func->stack_.pop();
					stmt->index_ = stmt2->index_;
					stmt->data_ += " " + stmt2->data_;
					i != 1 ? stmt->data_ += "," : stmt->data_ += " ";
				}

				stmt->data_ += ")";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_ScriptLocalChildThreadCall:
			{
				// TODO
				LOG_ERROR("missing handler 'OP_ScriptLocalChildThreadCall'!");
			}
			break;
			case opcode::OP_ScriptLocalMethodThreadCall:
			{
				auto stmt = func->stack_.top();
				auto data = stmt->data_ + " thread " + inst->m_data[0].substr(4) + "(";

				auto argnum = std::stoul(inst->m_data[1]);

				for (size_t i = argnum; i > 0; i--)
				{
					func->stack_.pop();
					stmt = func->stack_.top();
					data += " " + stmt->data_;
					i != 1 ? data += "," : data += " ";
				}

				stmt->data_ = data + ")";
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
				stmt->index_ = inst->m_index;
				stmt->data_ = utils::string::va("%s::%s()", inst->m_data[0].data(), inst->m_data[1].data());
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_ScriptFarFunctionCall:
			{
				std::string params = utils::string::va("%s::%s( ", inst->m_data[0].data(), inst->m_data[1].data());

				auto stmt = func->stack_.top();

				while (stmt->data_ != "pre_script_call")
				{
					params += stmt->data_ + ", ";
					func->stack_.pop();
					stmt = func->stack_.top(); // swap pointers
				}

				params.erase(params.end() - 2, params.end()); // TODO: FIX THIS, SHOULD ONLY BE CALLED IF PARAMS > 0
				params.append(" )");
				stmt->data_ = params;
			}
			break;
			case opcode::OP_ScriptFarMethodCall:
			{
				auto stmt = func->stack_.top();
				func->stack_.pop();
				std::string params = stmt->data_ + " " + inst->m_data[0] + "::" + inst->m_data[1] + "(";

				stmt = func->stack_.top();

				while (stmt->data_ != "pre_script_call")
				{
					params.append(" " + stmt->data_);
					func->stack_.pop();
					stmt = func->stack_.top();
					stmt->data_ != "pre_script_call" ? params.append(",") : params.append(" ");
				}
				params.append(")");
				stmt->data_ = params;
			}
			break;
			case opcode::OP_ScriptFarThreadCall:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				std::string data = "thread " + inst->m_data[1] + "::" + inst->m_data[2] + "(";

				auto argnum = std::stoul(inst->m_data[0]);

				for (size_t i = argnum; i > 0; i--)
				{	
					stmt = func->stack_.top();
					func->stack_.pop();
					data += " " + stmt->data_;
					i != 1 ? data += "," : data += " ";
				}

				data += ")";
				stmt->data_ = data;
				func->stack_.push(stmt);
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
				auto stmt = func->stack_.top(); // caller
				std::string data = stmt->data_ + " thread " + inst->m_data[1] + "::" + inst->m_data[2] + "(";

				auto argnum = std::stoul(inst->m_data[0]);

				for (size_t i = argnum; i > 0; i--)
				{
					func->stack_.pop();
					stmt = func->stack_.top();
					data += " " + stmt->data_;
					i != 1 ? data += "," : data += " ";
				}

				data += ")";
				stmt->data_ = data;
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
				auto stmt = func->stack_.top();
				params = utils::string::va("[[ %s ]](", stmt->data_.data());
				func->stack_.pop();
				stmt = func->stack_.top();

				auto count = 0;
				while (stmt->data_ != "pre_script_call")
				{
					params += stmt->data_ + ", ";
					func->stack_.pop();
					stmt = func->stack_.top(); // swap pointers
					count++;
				}
				if (count)
				{
					params.erase(params.end() - 2, params.end());
				}
				params.append(" )");
				stmt->data_ = params;
			}
			break;
			case opcode::OP_ScriptMethodCallPointer:
			{
				auto stmt = func->stack_.top(); // pointer
				func->stack_.pop();
				std::string data = "[[ " + stmt->data_ + " ]](";
				
				stmt = func->stack_.top(); // caller
				func->stack_.pop();
				data = stmt->data_ + " " + data;

				stmt = func->stack_.top(); // params

				while (stmt->data_ != "pre_script_call")
				{
					data += " " + stmt->data_;
					func->stack_.pop();
					stmt = func->stack_.top();
					stmt->data_ != "pre_script_call" ? data += "," : data += " ";
				}
	
				data += ")";
				stmt->data_ = data;
			}
			break;
			case opcode::OP_ScriptThreadCallPointer:
			{
				auto stmt = func->stack_.top();
				
				std::string data = "thread [[ " + stmt->data_ + " ]](";

				auto argnum = std::stoul(inst->m_data[0]);

				for (size_t i = argnum; i > 0; i--)
				{
					func->stack_.pop();
					stmt = func->stack_.top();
					data += " " + stmt->data_;
					i != 1 ? data += "," : data += " ";
				}

				data += ")";
				stmt->data_ = data;
			}
			break;
			case opcode::OP_ScriptMethodThreadCallPointer:
			{
				auto stmt = func->stack_.top(); // pointer
				func->stack_.pop();
				std::string data = "thread [[ " + stmt->data_ + " ]](";

				stmt = func->stack_.top(); // caller
				data = stmt->data_ + " " + data;

				auto argnum = std::stoul(inst->m_data[0]);

				for (size_t i = argnum; i > 0; i--)
				{
					func->stack_.pop();
					stmt = func->stack_.top();
					data += " " + stmt->data_;
					i != 1 ? data += "," : data += " ";
				}

				data += ")";
				stmt->data_ = data;
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
				auto stmt = func->stack_.top(); // pointer

				std::string data = "call [[ " + stmt->data_ + " ]](";

				auto argnum = std::stoul(inst->m_data[0]);

				for (size_t i = argnum; i > 0; i--)
				{
					func->stack_.pop();
					stmt = func->stack_.top();
					data += " " + stmt->data_;
					i != 1 ? data += "," : data += " ";
				}

				data += ")";
				stmt->data_ = data;
			}
			break;
			case opcode::OP_CallBuiltinMethodPointer:
			{
				auto stmt = func->stack_.top(); // pointer
				func->stack_.pop();
				std::string data = "call [[ " + stmt->data_ + " ]](";

				stmt = func->stack_.top(); // caller
				data = stmt->data_ + " " + data;

				auto argnum = std::stoul(inst->m_data[0]);

				for (size_t i = argnum; i > 0; i--)
				{
					func->stack_.pop();
					stmt = func->stack_.top();
					data += " " + stmt->data_;
					i != 1 ? data += "," : data += " ";
				}

				data += ")";
				stmt->data_ = data;
			}
			break;
			case opcode::OP_GetIString:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "&" + inst->m_data[0];
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_GetVector:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "( "+ inst->m_data[0] + ", " + inst->m_data[1] + ", " + inst->m_data[2] + " )";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_GetLevelObject:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "level";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_GetAnimObject:
			{
				// TODO
				LOG_ERROR("missing handler 'OP_GetAnimObject'!");
			}
			break;
			case opcode::OP_GetSelf:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "self";

				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_GetThisthread:
			{
				// TODO
				LOG_ERROR("missing handler 'OP_GetThisthread'!");
			}
			break;
			case opcode::OP_GetLevel:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "level";

				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_GetGame:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "game";

				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_GetAnim:
			{
				// TODO
				LOG_ERROR("missing handler 'OP_GetAnim'!");
			}
			break;
			case opcode::OP_GetAnimation:
			{
				// TODO
				LOG_ERROR("missing handler 'OP_GetAnimation'!");
			}
			break;
			case opcode::OP_GetGameRef:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "game";

				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_inc:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "++";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_dec:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "--";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_bit_or:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s | %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_JumpOnFalseExpr:
			{
				// TODO
				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				stmt1->data_ = utils::string::va("cond_false_expr ( %s ) #%s", stmt1->data_.data(), inst->m_data[0].data());
				func->statements_.push_back(stmt1);
			}
			break;
			case opcode::OP_bit_ex_or:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s ^ %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_bit_and:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s & %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_equality:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s == %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_inequality:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s != %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_less:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s < %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_greater:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s > %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_JumpOnTrueExpr:
			{
				// TODO
				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				stmt1->data_ = utils::string::va("cond_true_expr ( %s ) #%s", stmt1->data_.data(), inst->m_data[0].data());
				func->statements_.push_back(stmt1);
			}
			break;
			case opcode::OP_less_equal:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s <= %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_jumpback:
			{
				// TODO
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = utils::string::va("cond_loop #%s", inst->m_data[0].data());
				func->statements_.push_back(stmt);
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
				this->in_waittill = true;

				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();

				stmt1->data_ = utils::string::va("%s waittill( %s", stmt2->data_.data(), stmt1->data_.data());
			}
			break;
			case opcode::OP_notify:
			{
				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				auto stmt = func->stack_.top();
				func->stack_.pop();
				auto data = stmt1->data_ + " notify(" + stmt->data_;

				stmt = func->stack_.top(); // params
				func->stack_.pop();

				while (stmt->data_ != "voidcodepos")
				{
					data += ", " + stmt->data_;
					stmt = func->stack_.top();
					func->stack_.pop();
				}

				data += " );";
				stmt->data_ = data;
				func->statements_.push_back(stmt);
			}
			break;
			case opcode::OP_endon:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				stmt1->data_ = utils::string::va("%s endon(%s);", stmt2->data_.data(), stmt1->data_.data());
				func->statements_.push_back(stmt1);
			}
			break;
			case opcode::OP_voidCodepos:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "voidcodepos";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_switch:
			{
				// TODO
				auto stmt = func->stack_.top();
				func->stack_.pop();
				stmt->data_ = utils::string::va("switch ( %s ) #%s", stmt->data_.data(), inst->m_data[0].data());
				func->statements_.push_back(stmt);
			}
			break;
			case opcode::OP_endswitch:
			{
				// TODO
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = get_opcode_name(inst->m_opcode);
				for (auto d : inst->m_data)
				{
					stmt->data_.append(" " + d);
				}
				stmt->data_.append(";");
				func->statements_.push_back(stmt);
			}
			break;
			case opcode::OP_vector:
			{
				auto stmt3 = func->stack_.top();
				func->stack_.pop();
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = "( " + stmt3->data_ + ", " + stmt2->data_ + ", " + stmt1->data_ + " )";
			}
			break;
			case opcode::OP_JumpOnFalse:
			{
				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				stmt1->data_ = utils::string::va("cond ( %s ) #%s", stmt1->data_.data(), inst->m_data[0].data());
				func->statements_.push_back(stmt1);

				// dirty shit
				if (func->labels_.find(inst->m_index) != func->labels_.end())
				{
					auto loc = func->labels_.extract(inst->m_index);
					loc.key() = stmt1->index_;
					func->labels_.insert(std::move(loc));
				}
			}
			break;
			case opcode::OP_greater_equal:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s >= %s", stmt1->data_.data(), stmt2->data_.data());
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
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s + %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_jump:
			{
				// TODO
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = utils::string::va("cond_no #%s;", inst->m_data[0].data());
				func->statements_.push_back(stmt);
			}
			break;
			case opcode::OP_minus:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s - %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_multiply:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s * %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_divide:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = utils::string::va("%s / %s", stmt1->data_.data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_mod:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				stmt1->data_ = stmt1->data_ + " % " + stmt2->data_;
			}
			break;
			case opcode::OP_JumpOnTrue: // negate condition and replace with false: equals 'if (!epxr)'
			{
				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				stmt1->data_ = utils::string::va("cond ( !%s ) #%s", stmt1->data_.data(), inst->m_data[0].data());
				func->statements_.push_back(stmt1);

				// dirty shit
				if (func->labels_.find(inst->m_index) != func->labels_.end())
				{
					auto loc = func->labels_.extract(inst->m_index);
					loc.key() = stmt1->index_;
					func->labels_.insert(std::move(loc));
				}
			}
			break;
			case opcode::OP_size:
			{
				auto stmt = func->stack_.top();
				stmt->data_ = utils::string::va("%s.size", stmt->data_.data());
			}
			break;
			case opcode::OP_waittillmatch:
			{
				this->in_waittill = true;

				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				auto stmt = func->stack_.top();
				stmt->data_ = stmt2->data_ + " waittillmatch( " + stmt1->data_ + ", " + stmt->data_;
			}
			break;
			case opcode::OP_GetLocalFunction:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = utils::string::va("::%s", inst->m_data[0].substr(4).data());
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_GetFarFunction:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = utils::string::va("%s::%s", inst->m_data[0].data(), inst->m_data[1].data());
				func->stack_.push(stmt);
			};
			break;
			case opcode::OP_GetSelfObject:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "self";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalLevelFieldVariable:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = utils::string::va("level.%s", inst->m_data[0].data());
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalAnimFieldVariable:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = utils::string::va("anim.%s", inst->m_data[0].data());
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalSelfFieldVariable:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = utils::string::va("self.%s", inst->m_data[0].data());
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalFieldVariable:
			{
				auto stmt = func->stack_.top();
				stmt->data_ = utils::string::va("%s.%s", stmt->data_.data(), inst->m_data[0].data());
			}
			break;
			case opcode::OP_EvalLevelFieldVariableRef:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = utils::string::va("level.%s", inst->m_data[0].data());
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalAnimFieldVariableRef:
			{
				// TODO: check it!
				LOG_ERROR("missing handler 'OP_EvalAnimFieldVariableRef'!");
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "anim." + inst->m_data[0];
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalSelfFieldVariableRef:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = "self." + inst->m_data[0];
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_EvalFieldVariableRef:
			{
				auto stmt = func->stack_.top();
				stmt->data_ = stmt->data_ + "." + inst->m_data[0];
			}
			break;
			case opcode::OP_ClearFieldVariable:
			{
				auto stmt = func->stack_.top();
				func->stack_.pop();
				stmt->data_ = utils::string::va("%s.%s = undefined;", stmt->data_.data(), inst->m_data[0].data());
				func->statements_.push_back(stmt);
			}
			break;
			case opcode::OP_SafeCreateVariableFieldCached:
			{
				func->params_++;
				func->local_vars_.push_back("var");
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
				auto stmt = func->stack_.top();
				stmt->data_ += ", " + func->local_vars_.at(std::stoul(inst->m_data[0]));
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
				if (this->in_waittill)
				{
					this->in_waittill = false;
				}

				auto stmt1 = func->stack_.top();
				func->stack_.pop();

				stmt1->data_ = stmt1->data_ + " );";
				func->statements_.push_back(stmt1);
			}
			break;
			case opcode::OP_checkclearparams:
			{
				for (size_t i = 0; i < func->params_; i++)
				{
					func->local_vars_.at(i).append(utils::string::va("%i", func->params_ - 1 - i));
				}
			}
			break;
			case opcode::OP_EvalLocalVariableRefCached0:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = func->local_vars_.at(0).data();
				func->stack_.push(stmt);
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
				stmt->index_ = inst->m_index;
				stmt->data_ = func->local_vars_.at(std::stoul(inst->m_data[0])).data();
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_SetLevelFieldVariableField:
			{
				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				stmt1->data_ = utils::string::va("level.%s = %s;", inst->m_data[0].data(), stmt1->data_.data());
				func->statements_.push_back(stmt1);
			}
			break;
			case opcode::OP_SetVariableField:
			{
				auto stmt2 = func->stack_.top();
				func->stack_.pop();
				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				if (stmt2->data_ == "++" || stmt2->data_ == "--")
				{
					stmt1->data_ = utils::string::va("%s%s;", stmt1->data_.data(), stmt2->data_.data());
				}
				else
				{
					stmt1->data_ = utils::string::va("%s = %s;", stmt2->data_.data(), stmt1->data_.data());
				}
				
				func->statements_.push_back(stmt1);
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
				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				stmt1->data_ = utils::string::va("self.%s = %s;", inst->m_data[0].data(), stmt1->data_.data());
				func->statements_.push_back(stmt1);
			}
			break;
			case opcode::OP_SetLocalVariableFieldCached0:
			{
				auto stmt = func->stack_.top();
				func->stack_.pop();
				stmt->data_ = func->local_vars_.at(0) + " = " + stmt->data_ + ";";
				func->statements_.push_back(stmt);
			}
			break;
			case opcode::OP_SetNewLocalVariableFieldCached0:
			{
				std::string var = utils::string::va("var%i", std::stoul(inst->m_data[0]));
				func->local_vars_.insert(func->local_vars_.begin(), var);

				auto stmt1 = func->stack_.top();
				func->stack_.pop();
				stmt1->data_ = utils::string::va("%s = %s;", var.data(), stmt1->data_.data());
				func->statements_.push_back(stmt1);
			}
			break;
			case opcode::OP_SetLocalVariableFieldCached:
			{
				auto stmt = func->stack_.top();
				func->stack_.pop();
				stmt->data_ = func->local_vars_.at(std::stoul(inst->m_data[0])) + " = " + stmt->data_.data() + ";";
				func->statements_.push_back(stmt);
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
				stmt->index_ = inst->m_index;
				stmt->data_ = inst->m_data[0] + "()";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_CallBuiltin1:
			{
				auto stmt = func->stack_.top();
				stmt->data_ = inst->m_data[0] + "( " + stmt->data_ + " )";
			}
			break;
			case opcode::OP_CallBuiltin2:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = inst->m_data[0] + "(";

				for (size_t i = 2; i > 0; i--)
				{
					auto stmt2 = func->stack_.top();
					func->stack_.pop();
					stmt->index_ = stmt2->index_;
					stmt->data_ += " " + stmt2->data_;
					i != 1 ? stmt->data_ += "," : stmt->data_ += " ";
				}

				stmt->data_ += ")";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_CallBuiltin3:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = inst->m_data[0] + "(";

				for (size_t i = 3; i > 0; i--)
				{
					auto stmt2 = func->stack_.top();
					func->stack_.pop();
					stmt->index_ = stmt2->index_;
					stmt->data_ += " " + stmt2->data_;
					i != 1 ? stmt->data_ += "," : stmt->data_ += " ";
				}

				stmt->data_ += ")";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_CallBuiltin4:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = inst->m_data[0] + "(";

				for (size_t i = 4; i > 0; i--)
				{
					auto stmt2 = func->stack_.top();
					func->stack_.pop();
					stmt->index_ = stmt2->index_;
					stmt->data_ += " " + stmt2->data_;
					i != 1 ? stmt->data_ += "," : stmt->data_ += " ";
				}

				stmt->data_ += ")";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_CallBuiltin5:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = inst->m_data[0] + "(";

				for (size_t i = 5; i > 0; i--)
				{
					auto stmt2 = func->stack_.top();
					func->stack_.pop();
					stmt->index_ = stmt2->index_;
					stmt->data_ += " " + stmt2->data_;
					i != 1 ? stmt->data_ += "," : stmt->data_ += " ";
				}

				stmt->data_ += ")";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_CallBuiltin:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = inst->m_data[1] + "(";

				auto param_count = std::stoul(inst->m_data[0]);

				for (size_t i = param_count; i > 0; i--)
				{
					auto stmt2 = func->stack_.top();
					func->stack_.pop();
					stmt->index_ = stmt2->index_;
					stmt->data_ += " " + stmt2->data_;
					i != 1 ? stmt->data_ += "," : stmt->data_ += " ";
				}

				stmt->data_ += ")";
				func->stack_.push(stmt);
			}
			break;
			case opcode::OP_CallBuiltinMethod0:
			{
				auto stmt = func->stack_.top();
				stmt->data_ = utils::string::va("%s %s()", stmt->data_.data(), inst->m_data[0].data());
			}
			break;
			case opcode::OP_CallBuiltinMethod1:
			{
				auto stmt = func->stack_.top();
				func->stack_.pop();
				auto stmt2 = func->stack_.top();
				stmt2->data_ = utils::string::va("%s %s( %s )", stmt->data_.data(), inst->m_data[0].data(), stmt2->data_.data());
			}
			break;
			case opcode::OP_CallBuiltinMethod2:
			{
				auto stmt = func->stack_.top();

				std::string params = utils::string::va("%s %s( ", stmt->data_.data(), inst->m_data[0].data());

				for (size_t i = 0; i < 2; i++)
				{
					func->stack_.pop();
					stmt = func->stack_.top();
					params.append(stmt->data_);
					if (i != 1)
					{
						params.append(", ");
					}
				}

				params.append(" )");
				stmt->data_ = params.data();
			}
			break;
			case opcode::OP_CallBuiltinMethod3:
			{
				auto stmt = func->stack_.top();
	
				std::string params = utils::string::va("%s %s( ", stmt->data_.data(), inst->m_data[0].data());
				
				for (size_t i = 0; i < 3; i++)
				{
					func->stack_.pop();
					stmt = func->stack_.top();
					params.append(stmt->data_);
					if (i != 2)
					{
						params.append(", ");
					}
				}

				params.append(" )");
				stmt->data_ = params.data();
			}
			break;
			case opcode::OP_CallBuiltinMethod4:
			{
				auto stmt = func->stack_.top();

				std::string params = utils::string::va("%s %s( ", stmt->data_.data(), inst->m_data[0].data());

				for (size_t i = 0; i < 4; i++)
				{
					func->stack_.pop();
					stmt = func->stack_.top();
					params.append(stmt->data_);
					if (i != 3)
					{
						params.append(", ");
					}
				}

				params.append(" )");
				stmt->data_ = params.data();
			}
			break;
			case opcode::OP_CallBuiltinMethod5:
			{
				auto stmt = func->stack_.top();
				std::string data = stmt->data_ + " " + inst->m_data[0] + "(";

				for (size_t i = 0; i < 5; i++)
				{
					func->stack_.pop();
					stmt = func->stack_.top();
					data += " " + stmt->data_;
					i != 4 ? data += "," : data += " ";
				}

				data += ")";
				stmt->data_ = data.data();
			}
			break;
			case opcode::OP_CallBuiltinMethod:
			{
				auto stmt = func->stack_.top(); // method caller, level self or var
				func->stack_.pop();

				stmt->data_ = utils::string::va("%s %s( ", stmt->data_.data(), inst->m_data[1].data());

				auto param_count = std::stoul(inst->m_data[0]);
				for (size_t i = 0; i < param_count; i++)
				{
					auto stmt2 = func->stack_.top();
					func->stack_.pop();

					stmt->data_.append(stmt2->data_ + ", ");

					if (i == param_count - 1)
					{
						stmt->index_ = stmt2->index_;
						stmt->data_.erase(stmt->data_.end() - 2);
					}
				}
				stmt->data_.append(" )");
				func->stack_.push(stmt);
			}
			break;
			case  opcode::OP_wait:
			{
				auto stmt = func->stack_.top();
				func->stack_.pop();
				stmt->data_ = "wait " + stmt->data_ + ";";
				func->statements_.push_back(stmt);
			}
			break;
			case opcode::OP_DecTop:
			{
				auto stmt = func->stack_.top();
				func->stack_.pop();
				stmt->data_ = stmt->data_ + ";";
				func->statements_.push_back(stmt);
			}
			break;
			case opcode::OP_CastFieldObject:
			{
				// TODO
				//LOG_ERROR("missing handler 'OP_CastFieldObject'!");

				// no needed?
			}
			break;
			case opcode::OP_EvalLocalVariableObjectCached:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = func->local_vars_.at(std::stoul(inst->m_data[0]));
				func->stack_.push(stmt);
			}
			break;
			case  opcode::OP_CastBool:
			{
				continue;
			}
			break;
			case opcode::OP_BoolNot:
			{
				auto stmt = func->stack_.top();
				stmt->data_ = "!" + stmt->data_;
			}
			break;
			case opcode::OP_BoolComplement:
			{
				// TODO
				LOG_ERROR("missing handler 'OP_BoolComplement'!");
			}
			break;
			default:
			{
				auto stmt = std::make_shared<statement>();
				stmt->index_ = inst->m_index;
				stmt->data_ = get_opcode_name(inst->m_opcode);
				for (auto d : inst->m_data)
				{
					stmt->data_.append(" " + d);
				}
				stmt->data_.append(";");
				func->statements_.push_back(stmt);
			}
			break;
			}
		}
	}

	void decompiler::decompile_blocks(std::shared_ptr<decompiler_function> func)
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

	void decompiler::print_function(std::shared_ptr<decompiler_function> func)
	{
		// header
		output_->write_cpp_string("\n" + func->name_ + "(");

		// param list
		std::vector<std::string> args = func->local_vars_;
		std::reverse(args.begin(), args.end());

		for (size_t i = 0; i < func->params_; i++)
		{
			output_->write_cpp_string(" " + args.at(i));
			i != (func->params_ - 1) ? output_->write_cpp_string(",") : output_->write_cpp_string(" ");
		}

		output_->write_cpp_string(")\n{\n");

		// body
		for (auto& stmt : func->statements_)
		{
			if (func->labels_.find(stmt->index_) != func->labels_.end())
			{
				this->print_label(func->labels_[stmt->index_]);
			}

			this->print_statement(stmt);
		}

		if (func->labels_.find(func->end_) != func->labels_.end())
		{
			this->print_label(func->labels_[func->end_]);
		}

		// footer
		output_->write_cpp_string("}\n");
	}

	void decompiler::print_statement(std::shared_ptr<statement> stmt)
	{
		output_->write_cpp_string("\t");
		output_->write_cpp_string(stmt->data_);
		output_->write_cpp_string("\n");
	}

	void decompiler::print_label(const std::string& label)
	{
		output_->write_cpp_string(utils::string::va("#%s\n", label.data()));
	}
}
