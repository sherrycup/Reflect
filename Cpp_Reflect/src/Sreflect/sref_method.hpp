#pragma once
#include <vector>
#include <tuple>
#include <string>
#include "Traits/field_trait.hpp"
#include "head/type.hpp"
#include "Type/Factory.hpp"

namespace Reflect
{
	namespace detail
	{
		template<typename... Args>
		std::string getFunctionParam(const std::tuple<Args...>& tuple)
		{
			std::string str = "(";
			bool first = true;
			std::apply([&](auto... args) {
				([&](auto arg) {
					if (!first) str += ", ";
					first = false;
					str += GetType<decltype(arg)>()->to_string();
					}(args), ...);
				}, tuple);
			str += ")";
			return str;
		}

		template<bool isDeclear, bool isGetAccess = false, typename... Args, size_t... Idx>
		std::vector<std::string> Method(const std::tuple<Args...>& tuple, std::index_sequence<Idx...>, std::vector<Access>& access)
		{
			using tuple_type = std::tuple<Args...>;
			std::vector<std::string> nameList;
			(([&] {
				auto elem = std::get<Idx>(tuple);
				if (isDeclear || (!isDeclear && elem.access == Reflect::Access::Public))
				{
					using RetType = typename decltype(elem)::trait::ret_type;
					using param = typename decltype(elem)::trait::args;
					std::string ret_name = GetType<RetType>()->to_string();
					std::string param_name = getFunctionParam(param{});
					nameList.emplace_back(ret_name + " " + elem.name.data() + param_name);
					if (isGetAccess) access.emplace_back(elem.access);
				}
				}()  // 立即调用lamda函数
					), ...);

			return nameList;
		}

		template<bool isDeclear, bool isGetAccess = false, typename... Args, size_t... Idx>
		std::vector<std::string> Field(const std::tuple<Args...>& tuple, std::index_sequence<Idx...>, std::vector<Access>& access)
		{
			using tuple_type = std::tuple<Args...>;
			std::vector<std::string> nameList;
			(([&] {
				auto elem = std::get<Idx>(tuple);
				if (isDeclear || (!isDeclear && elem.access == Reflect::Access::Public))
				{
					using type = typename decltype(elem)::trait::type;
					std::string tname = GetType<type>()->to_string();
					nameList.emplace_back(tname + " " + elem.name.data());
					if (isGetAccess) access.emplace_back(elem.access);
				}
				}()  // 立即调用lamda函数
					), ...);

			return nameList;
		}
	}
	

	/*
		获取所有公共方法 同java getMethod
	*/
	template<typename T>
	std::vector<std::string> getMethod(const TypeInfo<T>& info)
	{
		std::vector<Access> dummy;
		return detail::Method<false>(info.functions, std::make_index_sequence<info.func_size>(),dummy);
	
	}

	template<typename T>
	std::vector<std::string> getMethod(const TypeInfo<T>& info, std::vector<Access>& access)
	{
		return detail::Method<false,true>(info.functions, std::make_index_sequence<info.func_size>(),access);
	}

	/*
		获取所有方法 同java getDeclearedMethod
	*/
	template<typename T>
	std::vector<std::string> getDeclearedMethod(const TypeInfo<T>& info)
	{
		std::vector<Access> dummy;
		return detail::Method<true>(info.functions, std::make_index_sequence<info.func_size>(), dummy);
	}

	template<typename T>
	std::vector<std::string> getDeclearedMethod(const TypeInfo<T>& info, std::vector<Access>& access)
	{
		return detail::Method<true,true>(info.functions, std::make_index_sequence<info.func_size>(), access);
	}

	/*
		获取所有公共字段 同java getField
	*/
	template<typename T>
	std::vector<std::string> getField(const TypeInfo<T>& info)
	{
		std::vector<Access> dummy;
		return detail::Field<false>(info.variables, std::make_index_sequence<info.var_size>(), dummy);
	}

	template<typename T>
	std::vector<std::string> getField(const TypeInfo<T>& info, std::vector<Access>& access)
	{
		return detail::Field<false,true>(info.variables, std::make_index_sequence<info.var_size>(),access);
	}

	/*
	获取所有字段 同java getDeclearedField
	希望显示变量名时，同时显示变量类型
	*/
	template<typename T>
	std::vector<std::string> getDeclearedField(const TypeInfo<T>& info)
	{
		std::vector<Access> dummy;
		return detail::Field<true>(info.variables, std::make_index_sequence<info.var_size>(), dummy);
	}

	template<typename T>
	std::vector<std::string> getDeclearedField(const TypeInfo<T>& info, std::vector<Access>& access)
	{
		return detail::Field<true, true>(info.variables, std::make_index_sequence<info.var_size>(), access);
	}


}