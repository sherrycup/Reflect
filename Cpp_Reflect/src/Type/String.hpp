#pragma once

#include"head/type.hpp"

namespace Reflect
{
	class String : public Type
	{
	public:
		String(const std::string name)
			:Type {name, Type::String}
		{

		}

		std::string getName() const
		{
			return Type::name_;
		}

		std::string to_string() const override
		{
			return "String " + this->getName();
		}

		static String Create()
		{
			return { "" };
		}
	protected:

	private:

	};
}