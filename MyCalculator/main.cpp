// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
//#include <iostream>
#include "BigNumber.h"

using namespace std;

int main()
{
	cout << "Press any key to start.";
	getchar();
	BigNumber num1(2);
	cout << pow_int_index(num1, -2);
	return 0;
}