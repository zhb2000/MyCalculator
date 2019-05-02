// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "BigNumber.h"
#include "Fraction.h"

using namespace std;

int main()
{
	Fraction a(1, -5);
	Fraction b(3, 6);
	cout << a + b;
	return 0;
}