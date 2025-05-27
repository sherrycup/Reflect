#pragma once

template<typename T>
struct remove_const
{
	using type = T;
};

template<typename T>
struct remove_const<const T>
{
	using type = T;
};

template<typename T>
struct remove_pointer
{
	using type = T;
};

template<typename T>
struct remove_pointer<T*>
{
	using type = T;
};

template<typename T>
struct remove_const_pointer
{
	using type =typename remove_pointer<typename remove_const<T>::type>::type;
};
