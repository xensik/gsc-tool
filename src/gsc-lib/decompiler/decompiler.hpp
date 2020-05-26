#pragma once

namespace gsc
{
	class decompiler
	{
	public:
		void decompile(std::vector<std::shared_ptr<function>>& functions);
		auto output() -> std::vector<std::uint8_t>;

	private:
		std::vector<std::shared_ptr<function>> m_functions;
	};
}
