#pragma once
#include"head/type.hpp"
#include"Type/TypenameList.hpp"
#include<vector>

namespace Reflect
{
	class Enum : public Type
	{
	public:
		struct Item
		{
			using value_type = long;
			Item(std::string& name, value_type value) :name_(name), value_(value){}
			std::string name_;
			value_type value_;
		};

		Enum(const std::string& name)
			:Type{ name, Type::Enum }
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

		static Enum Create()
		{
			return { "init Enum" };
		}
	protected:

	private:
		std::vector<Item> items_;
	};
}