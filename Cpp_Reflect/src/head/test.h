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
	std::string s;
	test(int a, std::string s)
		:a(a), s(s)
	{

	}

	int output_num()
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

