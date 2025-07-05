#pragma once
#include<string>
#include<tuple>

#include"function_traits.hpp"
#include"variable_traits.hpp"
#include"nlohmann/json.hpp"

namespace Reflect
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

	enum Access
	{
		Public,
		Private,
		Protected
	};

}

template<typename T>
struct traits_is_func
{
	static constexpr bool value = std::is_function_v<std::remove_pointer_t<T>> || std::is_member_function_pointer_v<T>;
};

template<typename T>
struct field_trait : public Reflect::baisc_field_trait<T, traits_is_func<T>::value>
{
	constexpr field_trait(T&& pointer, std::string_view name, Reflect::Access access)
		:pointer(pointer), name(name.substr(name.find_last_of(":") + 1)), access(access)
	{

	}

	T pointer;
	std::string_view name;
	Reflect::Access access;

};

template<typename T>
struct TypeInfo{};

// C++ 17 CTAD 自动推导类型T
// 宏定义全态化模板
#define Reflectable(X) friend TypeInfo<X>; using selfType = X;


#define Begin_Class(X) template<> struct TypeInfo<X> {	std::string_view name = #X;
	

#define functions(...)	\
	static constexpr auto functions = std::make_tuple(##__VA_ARGS__); \
	static constexpr size_t func_size = std::tuple_size_v<decltype(functions)>;

#define variables(...) \
	static constexpr auto variables = std::make_tuple(##__VA_ARGS__); \
	static constexpr size_t var_size = std::tuple_size_v<decltype(variables)>;

#define constructions(...)

#define func_public(F) \
	field_trait {F, #F, Reflect::Access::Public}
#define func_private(F) \
	field_trait {F, #F, Reflect::Access::Private}
#define func_protected(F) \
	field_trait {F, #F, Reflect::Access::Protected}

#define var_public(V) \
	field_trait {V, #V, Reflect::Access::Public}
#define var_private(V) \
	field_trait {V, #V, Reflect::Access::Private}
#define var_protected(V) \
	field_trait {V, #V, Reflect::Access::Protected}

#define ctor_public(V) \
	field_trait {V, #V, Reflect::Access::Public}
#define ctor_private(V) \
	field_trait {V, #V, Reflect::Access::Private}
#define ctor_protected(V) \
	field_trait {V, #V, Reflect::Access::Protected}

#define End_Class() }; 

