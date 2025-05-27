#pragma once
#include<string>
namespace Reflect
{
	// 声明子类
	class Numeric;
	class Class;
	class Enum;
	class Bool;
	class Void;

	/*
		类型基类
	*/
	class Type
	{
	public:
		enum Kind
		{
			Numeric,
			Enum,
			Class,
			GFunc,
			Bool,
			Void,
			// TODO
		};
		virtual ~Type() = default;
		Type(const std::string& name, Type::Kind kind)
			:name_(name),kind_(kind)
		{

		}

		Reflect::Numeric* asNumeric() const
		{
			if (kind_ == Kind::Numeric)
			{
				return (Reflect::Numeric*)(this);
			}
			else {
				return nullptr;
			}
		}

		std::string getName() const { return name_; }
	protected:
		std::string name_;
	private:
		Kind kind_;
	};
}