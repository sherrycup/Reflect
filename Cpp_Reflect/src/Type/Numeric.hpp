#pragma once

#include"head/type.hpp"
#include"Type/TypenameList.hpp"

namespace Reflect
{
	class Numeric : public Type
	{
	public:
		enum Kind
		{
			Char,
			Short,
			Int,
			Long,
			LongLong,
			Float,
			Double,
			Unknown
		};

		Numeric(const std::string& name, Numeric::Kind kind, bool is_signed)
			:Type{ name, Type::Kind::Numeric}, kind_(kind), is_signed_(is_signed)
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

		template<typename T>
		static Numeric Create()
		{
			return { "init Numeric" ,getKind<T>() , std::is_unsigned_v<T>};
		}
	protected:

	private:
		Kind kind_;
		bool is_signed_;

		/*
		static std::string detectName(Kind kind)
		{
			switch (kind)
			{
			case Numeric::Char:
				return "char";
			case Numeric::Short:
				return "short";
			case Numeric::Int:
				return "int";
			case Numeric::Long:
				return "long";
			case Numeric::LongLong:
				return "longlong";
			case Numeric::Float:
				return "float";
			case Numeric::Double:
				return "double";
			default:
				return "Unknown";
			}
		}
		*/
		template<typename T>
		static Kind getKind()
		{
			if constexpr (std::is_same_v<T, char>)
			{
				return Kind::Char;
			}
			else if constexpr (std::is_same_v<T, short>)
			{
				return Kind::Short;
			}
			else if constexpr (std::is_same_v<T, int>)
			{
				return Kind::Int;
			}
			else if constexpr (std::is_same_v<T, long>)
			{
				return Kind::Long;
			}
			else if constexpr (std::is_same_v<T, long long>)
			{
				return Kind::LongLong;
			}
			else if constexpr (std::is_same_v<T, float>)
			{
				return Kind::Float;
			}
			else if constexpr (std::is_same_v<T, double>)
			{
				return Kind::Double;
			}
		}
	};
}