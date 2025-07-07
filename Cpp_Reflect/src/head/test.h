#pragma once
#include<string>
#include"Traits/field_trait.hpp"
// 存放测试用头文件或代码

class test
{
public:
	// 静态反射许可
	Reflectable(test);
	int a;
	float test_float;
	std::string s;
	test(int a, std::string s)
		:a(a), s(s)
	{
		LOG_INFO("test实例化生成");
	}

	int output_num(float x)
	{
		return this->a + this->s.length();
	}

	int plus(int x, int y)
	{
		return x + y;
	}
private:
	float b;
	char c;

	void show() {}

	double what() { return 3.0; }

};

class Person
{
public:
	std::string name;
	int age;
	int id;

	Person(const std::string& name, int age, int id)
		:name(name), age(age), id(id)
	{

	}

	int sum(int a, int b)
	{
		return a + b;
	}

};

