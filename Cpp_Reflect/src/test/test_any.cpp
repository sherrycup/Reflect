#include "head/any.hpp"
#include<Windows.h>
#include <iostream>
#include"Sreflect/static_register.hpp"
#include"Sreflect/sref_method.hpp"


void print(int a,int b, char c, float d)
{

}
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	Log::Logger::Init();
	std::cout << "Hello World！" << std::endl;
	LOG_INFO("对的对的");

	auto typeinfo = TypeInfo<test>();
	std::vector<std::string_view> names = Reflect::getDeclearedField(typeinfo.variables,std::make_index_sequence<typeinfo.func_size>());

	for (auto& str : names)
	{
		std::cout << str << std::endl;
	}


	auto tem = field_trait<decltype(&print)>::param_count();
	LOG_INFO(tem);
	LOG_INFO("结束");



	return 0;
}