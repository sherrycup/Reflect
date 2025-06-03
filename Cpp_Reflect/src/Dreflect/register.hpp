#pragma once
#include"Type/Factory.hpp"


namespace Reflect
{
	template<typename T>
	auto& Register()
	{
		return Factory<T>::GetFactory();
	}
}