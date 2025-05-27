#pragma once
#include "head/type.hpp"

namespace Reflect
{
	class Bool : public Type
	{
	public:
		Bool(const std::string& name)
			:Type{ name, Type::Bool }
		{

		}

		std::string getName() const
		{
			return Type::name_;
		}

		void setName(const std::string& name)
		{
			Type::name_ = name;
		}

		static Bool Create()
		{
			return { "init Bool" };
		}
	protected:

	private:

	};
}