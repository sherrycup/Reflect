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
	/*Reflect::Register<test>().setName("Test").addVariable<decltype(&test::a)>("a").addVariable<decltype(&test::test_float)>("test_float");
	Reflect::Register<test>().addFunction<decltype(&test::output_num)>("output_num").addFunction<decltype(&test::plus)>("plus");
	auto temp2 = Reflect::GetType("Test");
	std::cout << temp2->to_string() << std::endl;*/

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

	std::cout << Reflect::GetType("ref")->asNumeric()->getValue(test_any) << std::endl;

	LOG_INFO(tem);
	LOG_INFO("结束");

	Person person("nmsl", 30, 10);
	Reflect::Register<Person>().setName("person").addVariable("name", &Person::name).addVariable("age", &Person::age)
		.addVariable("id", &Person::id).addFunction("sum",&Person::sum);

	auto xxxxx = Reflect::GetType("person");
	auto var = xxxxx->asClass()->getVariable("age")->call({ Reflect::make_any_ref(person) });
	std::cout << var << std::endl;
	xxxxx->asClass()->getVariable("age")->call({ Reflect::make_any_ref(person), Reflect::make_any_copy(20)});
	std::cout << xxxxx->asClass()->getVariable("age")->call({ Reflect::make_any_ref(person) }) << std::endl;

	std::cout << xxxxx->asClass()->getFunction("sum")
		->call({ Reflect::make_any_ref(person), Reflect::make_any_copy(3), Reflect::make_any_copy(5) }) << std::endl;

	std::string str = "hahahha";
	Reflect::Register<std::string>().setName("str");
	auto abc = Reflect::GetType("str");
	std::cout << abc->asString()->getValue(Reflect::make_any_copy(str)) << std::endl;
	abc->asString()->setValue("这对吗？对的对的", Reflect::make_any_ref(str));
	std::cout << abc->asString()->getValue(Reflect::make_any_copy(str)) << std::endl;


	bool bool_test = true;
	Reflect::Register<bool>().setName("bool_test");
	auto b_test = Reflect::GetType("bool_test");
	std::cout << b_test->asBool()->getValue(Reflect::make_any_copy(bool_test)) << std::endl;
	b_test->asBool()->setValue(false, Reflect::make_any_ref(bool_test));
	std::cout << b_test->asBool()->getValue(Reflect::make_any_copy(bool_test)) << std::endl;
	return 0;
}