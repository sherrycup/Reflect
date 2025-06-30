#pragma once
#include "head/type.hpp" 
namespace Reflect
{
	class Void : public Type
	{
	public:
		Void(const std::string& name)
			:Type{ name,Type::Void }
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
			if (this->getName().empty())
			{
				return "Void";
			}
			else
			{
				return "Void " + this->getName();
			}
			
		}

		static Void Create()
		{
			return { "" };
		}
	protected:

	private:

	};
}