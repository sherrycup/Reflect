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

		void setValue(const std::string& value, const any& elem)
		{
			assert(elem.getTypeInfo()->getKind() == Type::String);
			*static_cast<std::string*>(elem.getPayload()) = value;
		}

		any getValue(const any& elem)
		{
			auto value = *static_cast<std::string*>(elem.getPayload());
			return make_any_copy(value);
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