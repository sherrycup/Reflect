#pragma once

#include"head/type.hpp"
#include"Type/TypenameList.hpp"
#include<variant>

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

		using retType = std::variant<char, unsigned char, short, unsigned short, int, unsigned int, long, unsigned long,
			long long, unsigned long long, float, double>;

		retType getRealValue(any& elem) const
		{
			switch (elem.getTypeInfo()->asNumeric()->getKind())
			{
			case Numeric::Char:
				if (elem.getTypeInfo()->asNumeric()->getIsSigned())
				{
					return *static_cast<char*>(elem.getPayload());
				}
				else
				{
					return *static_cast<unsigned char*>(elem.getPayload());
				}
				break;
			case Numeric::Short:
				if (elem.getTypeInfo()->asNumeric()->getIsSigned())
				{
					return *static_cast<short*>(elem.getPayload());
				}
				else
				{
					return *static_cast<unsigned short*>(elem.getPayload());
				}
				break;
			case Numeric::Int:
				if (elem.getTypeInfo()->asNumeric()->getIsSigned())
				{
					return *static_cast<int*>(elem.getPayload());
				}
				else
				{
					return *static_cast<unsigned int*>(elem.getPayload());
				}
				break;
			case Numeric::Long:
				if (elem.getTypeInfo()->asNumeric()->getIsSigned())
				{
					return *static_cast<long*>(elem.getPayload());
				}
				else
				{
					return *static_cast<unsigned long*>(elem.getPayload());
				}
				break;
			case Numeric::LongLong:
				if (elem.getTypeInfo()->asNumeric()->getIsSigned())
				{
					return *static_cast<long long*>(elem.getPayload());
				}
				else
				{
					return *static_cast<unsigned long long*>(elem.getPayload());
				}
				break;
			case Numeric::Float:
				return *static_cast<float*>(elem.getPayload());
				break;
			case Numeric::Double:
				return *static_cast<double*>(elem.getPayload());
			case Numeric::Unknown:
				LOG_ERROR("异常类型赋值");
			}
		}

		Numeric(const std::string& name, Numeric::Kind kind, bool is_signed)
			:Type{ name, Type::Kind::Numeric}, kind_(kind), is_signed_(is_signed)
		{

		}

		std::string getName() const
		{
			return Type::name_;
		}

		Numeric::Kind getKind() const
		{
			return kind_;
		}

		bool getIsSigned() const
		{
			return is_signed_;
		}
		/*
		void setName(const std::string& name)
		{
			Type::name_ = name;
		}
		*/

		std::string to_string() const override
		{
			return detectName(kind_) + " " + this->getName();
		}

		template<typename T>
		static Numeric Create()
		{
			return { "" ,getKind<T>() , std::is_unsigned_v<T>};
		}

		void setValue(double value, any& elem)
		{
			if (elem.getTypeInfo()->getKind() == Type::Numeric)
			{
				switch (elem.getTypeInfo()->asNumeric()->getKind())
				{
				case Numeric::Char:
					if (elem.getTypeInfo()->asNumeric()->getIsSigned())
					{
						*(char*)elem.getPayload() = value;
					}
					else
					{
						*(unsigned char*)elem.getPayload() = value;
					}
					break;
				case Numeric::Short:
					if (elem.getTypeInfo()->asNumeric()->getIsSigned())
					{
						*(short*)elem.getPayload() = value;
					}
					else
					{
						*(unsigned short*)elem.getPayload() = value;
					}
					break;
				case Numeric::Int:
					if (elem.getTypeInfo()->asNumeric()->getIsSigned())
					{
						*(int*)elem.getPayload() = value;
					}
					else
					{
						*(unsigned int*)elem.getPayload() = value;
					}
					break;
				case Numeric::Long:
					if (elem.getTypeInfo()->asNumeric()->getIsSigned())
					{
						*(long*)elem.getPayload() = value;
					}
					else
					{
						*(unsigned long*)elem.getPayload() = value;
					}
					break;
				case Numeric::LongLong:
					if (elem.getTypeInfo()->asNumeric()->getIsSigned())
					{
						*(long long*)elem.getPayload() = value;
					}
					else
					{
						*(unsigned long long*)elem.getPayload() = value;
					}
					break;
				case Numeric::Float:
					*(float*)elem.getPayload() = value;
					break;
				case Numeric::Double:
					*(double*)elem.getPayload() = value;
				case Numeric::Unknown:
					LOG_ERROR( "异常类型赋值");
				}
			}
			else
			{
				// 不属于Numeric类型
				assert(false);
			}
		}

		any getValue(any& elem) const
		{
			if (elem.getTypeInfo()->getKind() == Type::Numeric)
			{
				switch (elem.getTypeInfo()->asNumeric()->getKind())
				{
				case Numeric::Char:
					if (elem.getTypeInfo()->asNumeric()->getIsSigned())
					{
						return make_any_copy(*static_cast<char*>(elem.getPayload()));
					}
					else
					{
						return make_any_copy(*static_cast<unsigned char*>(elem.getPayload()));
					}
					break;
				case Numeric::Short:
					if (elem.getTypeInfo()->asNumeric()->getIsSigned())
					{
						return make_any_copy(*static_cast<short*>(elem.getPayload()));
					}
					else
					{
						return make_any_copy(*static_cast<unsigned short*>(elem.getPayload()));
					}
					break;
				case Numeric::Int:
					if (elem.getTypeInfo()->asNumeric()->getIsSigned())
					{
						return make_any_copy(*static_cast<int*>(elem.getPayload()));
					}
					else
					{
						return make_any_copy(*static_cast<unsigned int*>(elem.getPayload()));
					}
					break;
				case Numeric::Long:
					if (elem.getTypeInfo()->asNumeric()->getIsSigned())
					{
						return make_any_copy(*static_cast<long*>(elem.getPayload()));
					}
					else
					{
						return make_any_copy(*static_cast<unsigned long*>(elem.getPayload()));
					}
					break;
				case Numeric::LongLong:
					if (elem.getTypeInfo()->asNumeric()->getIsSigned())
					{
						return make_any_copy(*static_cast<long long*>(elem.getPayload()));
					}
					else
					{
						return make_any_copy(*static_cast<unsigned long long*>(elem.getPayload()));
					}
					break;
				case Numeric::Float:
					return make_any_copy(*static_cast<float*>(elem.getPayload()));
					break;
				case Numeric::Double:
					return make_any_copy(*static_cast<double*>(elem.getPayload()));
				case Numeric::Unknown:
					LOG_ERROR("异常类型赋值");
				}
			}
			else
			{
				// 不属于Numeric类型
				assert(false);
			}
		}
	protected:

	private:
		Kind kind_;
		bool is_signed_;


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