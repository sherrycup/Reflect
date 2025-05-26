#include "head/any.hpp"
#include<Windows.h>
#include <iostream>
#include "head/test.h"


void print(int a,int b, char c, float d)
{

}
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	Log::Logger::Init();
	std::cout << "Hello World！" << std::endl;
	LOG_INFO("对的对的");


	auto tem = field_trait<decltype(&print)>::param_count();
	LOG_INFO(tem);
	LOG_INFO("结束");



	return 0;
}