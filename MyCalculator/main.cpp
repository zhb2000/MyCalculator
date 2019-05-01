// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
//#include <iostream>
#include "BigNumber.h"

using namespace std;

int main()
{
	getchar();
	BigNumber num2 = factorial_num(BigNumber("1000"));
	cout << num2;
	return 0;
}