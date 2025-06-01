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

		/*
		void setName(const std::string& name)
		{
			Type::name_ = name;
		}
		*/

		std::string to_string() const override
		{
			return "Bool " + this->getName();
		}

		static Bool Create()
		{
			return { "" };
		}
	protected:

	private:

	};
}