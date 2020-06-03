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
		// paramenter list
		func->params_ = 0;
		
		auto it = func->instructions_.begin();
		if ((*it)->m_opcode != opcode::OP_checkclearparams)
		{
			while ((*it)->m_opcode == opcode::OP_SafeCreateVariableFieldCached)
			{
				LOG_DEBUG("removing!");
				func->params_++;
				it = func->instructions_.erase(it);
			}
		}

		// remove checkclearparams
		func->instructions_.erase(func->instructions_.begin()); 

		for (size_t i = 0; i < func->params_; i++)
		{
			func->local_vars_.push_back(utils::string::va("arg%i", func->params_ - i));
		}

		// blocks

	}




	void decompiler::print_function(std::shared_ptr<decompiler_function> func)
	{
		output_->write_cpp_string(func->name_);

		output_->write_cpp_string("(");

		// param list
		std::vector<std::string> args = func->local_vars_;
		std::reverse(args.begin(), args.end());

		for (size_t i = 0; i < func->params_; i++)
		{
			output_->write_cpp_string(" ");
			output_->write_cpp_string(args.at(i));
			if (i != func->params_ - 1)
			{
				output_->write_cpp_string(",");
			}
			else
			{
				output_->write_cpp_string(" ");
			}
		}

		output_->write_cpp_string(")\n");

		output_->write_cpp_string("{\n");

		for (auto& inst : func->instructions_)
		{
			if (func->labels_.find(inst->m_index) != func->labels_.end())
			{
				this->print_label(func->labels_[inst->m_index]);
			}

			this->print_instruction(inst);
		}

		output_->write_cpp_string("}\n");

		output_->write_cpp_string("\n");
	}

	void decompiler::print_instruction(std::shared_ptr<instruction> inst)
	{
		switch (inst->m_opcode)
		{
		case opcode::OP_endswitch:
			output_->write_cpp_string("\t");
			output_->write_cpp_string(utils::string::va("%s", get_opcode_name(inst->m_opcode).data()));
			output_->write_cpp_string(utils::string::va(" %s\n", inst->m_data[0].data()));
			{
				std::uint32_t totalcase = std::stoul(inst->m_data[0]);
				auto index = 0;
				for (auto casenum = 0; casenum < totalcase; casenum++)
				{
					output_->write_cpp_string("\t");
					if (inst->m_data[1 + index] == "case")
					{
						output_->write_cpp_string(utils::string::va("%s %s %s", inst->m_data[1 + index].data(), inst->m_data[1 + index + 1].data(), inst->m_data[1 + index + 2].data()));
						index += 3;
					}
					else if (inst->m_data[1 + index] == "default")
					{
						output_->write_cpp_string(utils::string::va("%s %s", inst->m_data[1 + index].data(), inst->m_data[1 + index + 1].data()));
						index += 2;
					}
					if (casenum != totalcase - 1)
						output_->write_cpp_string("\n");
				}
			}
			break;
		default:
			output_->write_cpp_string("\t");
			output_->write_cpp_string(utils::string::va("%s", get_opcode_name(inst->m_opcode).data()));
			for (auto& d : inst->m_data)
			{
				output_->write_cpp_string(utils::string::va(" %s", d.data()));
			}
			break;
		}

		output_->write_cpp_string("\n");
	}

	void decompiler::print_label(const std::string& label)
	{
		output_->write_cpp_string(utils::string::va("\n\t%s\n", label.data()));
	}
}
