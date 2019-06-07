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
#include "NumberTrans.h"
#include "MathCalculator.h"
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
			use_mathCalcuMode();
		else if (str == "1")
			BigNumCalcu_mode();
		else if (str == "2")
			equation_mode();
		else if (str == "3")
			logical_expression_mode();
		else if (str == "4")
			calcu_matrix();
		else if (str == "5")
			my_trans_func();
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
	cout << "小组组名：\\u4f18\\u79c0 \n";
	cout << "小组成员：\n组长：朱华彬 组员：马骁 李政民\n\n";
}

void use_mathCalcuMode()
{
	while (true)
	{
		cout << "--------------------------------------------" << endl;
		cout << "[指令列表]输入start即可开始，输入quit退出计算器模式，输入cls清屏" << endl;
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "start")
		{
			cout << endl;
			mathCalcuMode();
		}
		else if (str == "quit")
		{
			cout << "[系统提示]已退出命题逻辑模式" << endl << endl;
			return;
		}
		else if (str == "cls")
		{
			system("cls");
		}
		else
		{
			cout << "[错误]无法识别的指令" << endl;
		}
		cout << endl;
	}
}