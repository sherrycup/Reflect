#pragma once

#include<type_traits>
#include<tuple>

namespace Reflect
{
	template<typename Ret, typename... Args>
	struct basic_function_trait;

	template<typename Ret, typename... Args>
	struct basic_function_trait <Ret(Args...)>
	{
		using ret_type = Ret;
		using args = std::tuple<Args...>;
	};
}

template<typename func>
struct function_trait;

template<typename Ret, typename... Args>
struct function_trait<Ret(*)(Args...)> : Reflect::basic_function_trait<Ret(Args...)>
{
	using type = Ret(Args...);
	using class_with_args = std::tuple<Args...>;
	using pointer_type = Ret(*)(Args...);
	static constexpr bool is_member = false;
	static constexpr bool is_const = false;
};

template<typename Ret,typename Clazz, typename... Args>
struct function_trait<Ret(Clazz::*)(Args...)> : Reflect::basic_function_trait<Ret(Args...)>
{
	using type = Ret(Clazz::*)(Args...);
	using class_with_args = std::tuple<Clazz*,Args...>;
	using pointer_type = Ret(Clazz::*)(Args...);
	static constexpr bool is_member = true;
	static constexpr bool is_const = false;
};

template<typename Ret, typename Clazz, typename... Args>
struct function_trait<Ret(Clazz::*)(Args...) const> : Reflect::basic_function_trait<Ret(Args...)>
{
	using type = Ret(Clazz::*)(Args...) const;
	using class_with_args = std::tuple<Clazz*, Args...>;
	using pointer_type = Ret(Clazz::*)(Args...)const;
	static constexpr bool is_member = true;
	static constexpr bool is_const = true;
};