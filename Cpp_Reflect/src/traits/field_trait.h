#pragma once
#include"function_traits.h"
#include"variable_traits.h"

namespace detail
{
	template<typename T,bool isFunc>
	struct baisc_field_trait;

	template<typename T>
	struct baisc_field_trait<T,true> : function_trait<T>
	{
		using trait = function_trait<T>;

		static constexpr size_t param_count()
		{
			return std::tuple_size_v<typename trait::args>;
		}
	};

	template<typename T>
	struct baisc_field_trait<T, false> : variable_trait<T>
	{
		using trait = variable_trait<T>;
	};

}

template<typename T>
struct traits_is_func
{
	static constexpr bool value = std::is_function_v<std::remove_pointer_t<T>> || std::is_member_function_pointer_v<T>;
};

template<typename T>
struct field_trait : detail::baisc_field_trait<T, traits_is_func<T>::value>
{
	field_trait(T&& pointer)
		:pointer(pointer)
	{

	}

	T pointer;
};