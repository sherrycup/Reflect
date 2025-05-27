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

		void setName(const std::string& name)
		{
			Type::name_ = name;
		}

		static Void Create()
		{
			return { "init Void" };
		}
	protected:

	private:

	};
}