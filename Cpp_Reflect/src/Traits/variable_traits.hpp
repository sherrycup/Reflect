#pragma once
#include<type_traits>
namespace Reflect
{
	template<typename T>
	struct variable_trait_t
	{
		using type = T;
	};

	template<typename Clazz, typename T>
	struct variable_trait_t<T(Clazz::*)>
	{
		using type = T;
	};
	template<typename T>
	struct basic_variables_traits;


	template<typename T>
	struct basic_variables_traits
	{
		using type = typename variable_trait_t<T>::type;
		static constexpr bool is_member = std::is_member_pointer_v<T>;
	};

}

template<typename T>
struct variable_trait : Reflect::basic_variables_traits<T>
{

};

template<typename T>
struct variable_trait<T*> : Reflect::basic_variables_traits<T>
{
	using pointer_type = T*;
};

template<typename T, typename Clazz>
struct variable_trait <T(Clazz::*)> : Reflect::basic_variables_traits<T(Clazz::*)>
{
	using pointer_type = T(Clazz::*);
	using clazz_type = Clazz;
};
