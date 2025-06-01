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
	std::cout << temp->to_string() << std::endl;
	enum  s {
		aa = 1,
		bb = 2
	};

	test Test = test(1,"hahaha");
	// 注册类对象
	Reflect::Register<test>().setName("Test").addVariable<decltype(&test::a)>("a").addVariable<decltype(&test::test_float)>("test_float");
	Reflect::Register<test>().addFunction<decltype(&test::output_num)>("output_num").addFunction<decltype(&test::plus)>("plus");
	auto temp2 = Reflect::GetType("Test");
	std::cout << temp2->to_string() << std::endl;

	auto temp1 = Reflect::Register<s>().setName("s").getInfo();
	auto y = Reflect::GetType("s");
	std::cout << temp1->to_string() << std::endl;
	std::cout << y->to_string() << std::endl;
	auto tem = field_trait<decltype(&print)>::param_count();

	std::string text = "卓一刀";
	Reflect::Register<decltype(text)>().setName("text");
	auto temp3 = Reflect::GetType("text");
	std::cout << temp3->to_string() << std::endl;


	int ref = 123;
	Reflect::Register<int>().setName("ref");
	Reflect::any test_any = Reflect::make_any_ref<int>(ref);
	
	Reflect::GetType("ref")->asNumeric()->setValue(10, test_any);

	std::cout << ref << std::endl;

	Reflect::GetType("ref")->asNumeric()->setValue(50, test_any);

	std::cout << ref << std::endl;

	LOG_INFO(tem);
	LOG_INFO("结束");



	return 0;
}