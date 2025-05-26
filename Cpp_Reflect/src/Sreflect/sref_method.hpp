#pragma once
#include <vector>
#include <tuple>
#include <string>
#include "traits/field_trait.h"

namespace Reflect
{

	/*
		获取所有公共方法 同java getMethod
	*/
	template< typename... Args, size_t... Idx>
	std::vector<std::string_view> getMethod(const std::tuple<Args...>& tuple, std::index_sequence<Idx...>)
	{
		using tuple_type = std::tuple<Args...>;
		std::vector<std::string_view> nameList;
		(([&] {
			auto elem = std::get<Idx>(tuple);
			if (elem.access == Reflect::Access::Public)
			{
				nameList.emplace_back(elem.name);
			}
		}()  // 立即调用lamda函数
		), ...);

		return nameList;
	}

	/*
		获取所有方法 同java getDeclearedMethod
	*/
	template< typename... Args, size_t... Idx>
	std::vector<std::string_view> getDeclearedMethod(const std::tuple<Args...>& tuple, std::index_sequence<Idx...>)
	{
		using tuple_type = std::tuple<Args...>;
		std::vector<std::string_view> nameList;
		(([&] {
			auto elem = std::get<Idx>(tuple);
			nameList.emplace_back(elem.name);
			}()  // 立即调用lamda函数
		), ...);

		return nameList;
	}

	/*
		获取所有公共字段 同java getField
	*/
	template< typename... Args, size_t... Idx>
	std::vector<std::string_view> getField(const std::tuple<Args...>& tuple, std::index_sequence<Idx...>)
	{
		using tuple_type = std::tuple<Args...>;
		std::vector<std::string_view> nameList;
		(([&] {
			auto elem = std::get<Idx>(tuple);
			if (elem.access == Reflect::Access::Public)
			{
				nameList.emplace_back(elem.name);
			}
			}()  // 立即调用lamda函数
		), ...);

		return nameList;
	}

	/*
	获取所有字段 同java getDeclearedField
*/
	template< typename... Args, size_t... Idx>
	std::vector<std::string_view> getDeclearedField(const std::tuple<Args...>& tuple, std::index_sequence<Idx...>)
	{
		using tuple_type = std::tuple<Args...>;
		std::vector<std::string_view> nameList;
		(([&] {
			auto elem = std::get<Idx>(tuple);
			nameList.emplace_back(elem.name);
			}()  // 立即调用lamda函数
				), ...);

		return nameList;
	}
}