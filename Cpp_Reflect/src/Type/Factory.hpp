#pragma once
#include "TypeFactory.hpp"


namespace Reflect
{
	template<typename T>
	class Factory final
	{
	public:
		static auto& GetFactory()
		{
			if constexpr (std::is_same_v<T, bool>)
			{
				return BoolFactory::GetInstance();
			}
			else if constexpr (std::is_void_v<T>)
			{

			}
			else if constexpr (std::is_fundamental_v<T>)	// 前两项已经排除bool与void
			{
				return NumericFactory<T>::GetInstance();
			}
			else if constexpr (std::is_enum_v<T>)
			{
				return EnumFactory::GetInstance();
			}
		}
	};

	template<typename T>
	const Type* GetType()
	{
		return Factory<T>::GetFactory().getInfo();
	}


}