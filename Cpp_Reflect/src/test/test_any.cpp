#include "head/any.hpp"
#include<Windows.h>
#include <iostream>
#include"Sreflect/static_register.hpp"
#include"Sreflect/sref_method.hpp"
#include"Dreflect/register.hpp"


void print(int a,int b, char c, float d)
{

}
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	Log::Logger::Init();
	std::cout << "Hello World！" << std::endl;
	LOG_INFO("对的对的");

	//auto typeinfo = TypeInfo<test>();
	//std::vector<std::string_view> names = Reflect::getDeclearedField(typeinfo.variables,std::make_index_sequence<typeinfo.func_size>());

	//for (auto& str : names)
	//{
	//	std::cout << str << std::endl;
	//}
	bool zyd;

	Reflect::Register<decltype(zyd)>().setName("zyd");

	auto temp = Reflect::GetType("zyd");
	std::cout << temp->getName() << std::endl;
	enum  s {
		aa = 1,
		bb = 2
	};

	auto temp1 = Reflect::Register<s>().setName("s").getInfo();
	auto y = Reflect::GetType("s");
	std::cout << temp1->getName() << std::endl;
	std::cout << y->getName() << std::endl;
	auto tem = field_trait<decltype(&print)>::param_count();
	LOG_INFO(tem);
	LOG_INFO("结束");



	return 0;
}