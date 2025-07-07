#pragma once
#include "TypeFactory.hpp"
#include "Traits/utils.hpp"

namespace Reflect
{

	template<typename T>
	class Factory final
	{
	public:
		static auto& GetFactory()
		{
			using RawT = typename remove_const_pointer<T>::type;
			if constexpr (std::is_same_v<T, bool>)
			{
				return BoolFactory::GetInstance();
			}
			else if constexpr (std::is_void_v<T>)
			{
				return VoidFactory::GetInstance();
			}
			else if constexpr (std::is_same_v<T, std::string>)
			{
				return StringFactory::GetInstance();
			}
			else if constexpr (std::is_fundamental_v<T>)	// 前两项已经排除bool与void
			{
				return NumericFactory<T>::GetInstance();
			}
			else if constexpr (std::is_enum_v<T>)
			{
				return EnumFactory::GetInstance();
			}
			else if constexpr (std::is_class_v<RawT>)
			{
				// 确定类型变体
				
				if constexpr (std::is_pointer_v<T>) {
					
				}
				else if constexpr (std::is_reference_v<T>) {
					
				}
				return ClassFactory<RawT>::GetInstace();
			}
			else
			{
				std::cout << "非法类型" << std::endl;
				return VoidFactory::GetInstance();
			}
		}
	};

	template<typename T>
	const Type* GetType()
	{
		return Factory<T>::GetFactory().getInfo();
	}


	// 输出流操作符重载实现
	std::ostream& operator<<(std::ostream& os, const any& elem) {
		const Type* type = elem.getTypeInfo();
		if (type) {
			switch (type->getKind())
			{
			case Type::Numeric:
				switch (type->asNumeric()->getKind())
				{
				case Numeric::Char:
					if (type->asNumeric()->getIsSigned())
					{
						os << *static_cast<char*>(elem.getPayload());
					}
					else
					{
						os << *static_cast<unsigned char*>(elem.getPayload());
					}
					break;
				case Numeric::Short:
					if (type->asNumeric()->getIsSigned())
					{
						os << *static_cast<short*>(elem.getPayload());
					}
					else
					{
						os << *static_cast<unsigned short*>(elem.getPayload());
					}
					break;
				case Numeric::Int:
					if (type->asNumeric()->getIsSigned())
					{
						os << *static_cast<int*>(elem.getPayload());
					}
					else
					{
						os << *static_cast<unsigned int*>(elem.getPayload());
					}
					break;
				case Numeric::Long:
					if (type->asNumeric()->getIsSigned())
					{
						os << *static_cast<long*>(elem.getPayload());
					}
					else
					{
						os << *static_cast<unsigned long*>(elem.getPayload());
					}
					break;
				case Numeric::LongLong:
					if (type->asNumeric()->getIsSigned())
					{
						os << *static_cast<long long*>(elem.getPayload());
					}
					else
					{
						os << *static_cast<unsigned long long*>(elem.getPayload());
					}
					break;
				case Numeric::Float:
					os << *static_cast<float*>(elem.getPayload());
					break;
				case Numeric::Double:
					os << *static_cast<double*>(elem.getPayload());
					break;
				default:
					assert(false);
				}
			case Type::Enum:

				break;
			case Type::Class:
				os << type->getName();
				break;
			case Type::GFunc:

				break;
			case Type::Bool:
				if (*static_cast<bool*>(elem.getPayload()))
				{
					os << "True";
				}
				else
				{
					os << "False";
				}
				
				break;
			case Type::Void:

				break;
			case Type::String:
				os << *static_cast<std::string*>(elem.getPayload());
				break;
			default:
				break;
			}
		}
		else {
			os << "<empty any>";
		}
		return os;
	}


}