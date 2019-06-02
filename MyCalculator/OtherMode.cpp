#include "pch.h"
#include "OtherMode.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "BigNumberCalcu.h"
#include "Equation.h"
#include "LogicalExpression.h"
#include "Theme.h"
#include "Matrix.h"
using namespace std;

//模式切换
void switch_mode()
{
	while (true)
	{
		cout << "--------------------------------------------" << endl;
		cout << "【多功能计算器】" << endl;
		cout << "[指令列表]输入指令进入相应功能\n\n";
		cout << "0-计算器 1-大数运算 2-解线性方程组\n\n3-命题逻辑演算 4-矩阵计算器 5-进制、编码转换\n\n6-切换主题配色 7-关于我们\n\ncls-清屏 quit-退出程序\n\n";
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "0")
			cout << "计算器未完成" << endl;
		else if (str == "1")
			BigNumCalcu_mode();
		else if (str == "2")
			equation_mode();
		else if (str == "3")
			logical_expression_mode();
		else if (str == "4")
			calcu_matrix();
		else if (str == "5")
			cout << "进制转换未完成" << endl;
		else if (str == "6")
			theme_mode();
		else if (str == "7")
			about_mode();
		else if (str == "cls")
			system("cls");
		else if (str == "quit")
			return;
		else
			cout << "[错误]无法识别的指令\n\n";
	}
}

void about_mode()
{
	cout << "--------------------------------------------" << endl;
	cout << "小组成员：\n朱华彬 马骁 李政民\n\n";
}