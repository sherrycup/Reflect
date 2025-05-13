#include "head/any.hpp"
#include<Windows.h>
#include <iostream>

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	Log::Logger::Init();
	std::cout << "Hello World！" << std::endl;
	LOG_INFO("对的对的");

	int a = 2;
	Reflect::any num = Reflect::make_any_copy<int>(a);
	num.print();
	return 0;
}