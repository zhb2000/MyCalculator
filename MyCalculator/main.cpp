// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "BigNumber.h"
#include "Fraction.h"
#include "Equation.h"
#include "Theme.h"
#include "LogicalExpression.h"

using namespace std;

int main()
{
	//system("mode con cols=60 lines=20"); //cols为控制台的宽度，lines则代表控制台的高度。
	system("color f5");
	//theme_mode();
	//equation_mode();
	logical_expression_start();
	system("pause");
	return 0;
}