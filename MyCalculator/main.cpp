// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
//#include <iostream>
#include "BigNumber.h"

using namespace std;

int main()
{
	BigNumber num1("0.94532252");
	BigNumber num2("-0.12345");
	BigNumber num3 = divide_num(num1, num2);
	cout << num3;
	return 0;
}