#pragma once
#include<string>
#include"Log/Log.h"
namespace Reflect
{
	// 声明子类
	class Numeric;
	class Class;
	class Enum;
	class Bool;
	class Void;
	class String;


	/*
		类型基类
	*/
	class Type
	{
	public:
		// 声明友元类
		template<typename T>
		friend class NumericFactory;

		friend class ClassFactory;

		friend class EnumFactory;

		friend class VoidFactory;

		friend class BoolFactory;

		friend class StringFactory;

		enum Kind
		{
			Numeric,
			Enum,
			Class,
			GFunc,
			Bool,
			Void,
			String
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

		Reflect::Class* asClass() const
		{
			if (kind_ == Kind::Class)
			{
				return (Reflect::Class*)(this);
			}
			else
			{
				return nullptr;
			}
		}

		Reflect::String* asString() const
		{
			if (kind_ == Kind::String)
			{
				return (Reflect::String*)(this);
			}
			else
			{
				return nullptr;
			}
		}

		Reflect::Bool* asBool() const
		{
			if (kind_ == Kind::Bool)
			{
				return (Reflect::Bool*)(this);
			}
			else
			{
				return nullptr;
			}
		}

		std::string getName() const { return name_; }

		Type::Kind getKind() const { return this->kind_; }
		//void setName(const std::string& name) { this->name_ = name; }
		
		virtual std::string to_string() const
		{
			return "Type " + name_;
		}

	protected:


		std::string name_;
	private:
		Kind kind_;
	};
}