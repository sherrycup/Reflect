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
		void setValue(bool value, const any& elem)
		{
			assert(elem.getTypeInfo()->getKind() == Type::Bool);
			*static_cast<bool*>(elem.getPayload()) = value;
		}

		any getValue(const any& elem) const
		{
			auto value = *static_cast<bool*>(elem.getPayload());
			return make_any_copy(value);
		}

		std::string to_string() const override
		{
			if (this->getName().empty())
			{
				return "Bool";
			}
			else
			{
				return "Bool " + this->getName();
			}
						
			
		}

		static Bool Create()
		{
			return { "" };
		}
	protected:

	private:

	};
}