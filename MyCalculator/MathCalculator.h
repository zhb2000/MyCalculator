//算术表达式求值
//by 李政民
#pragma once
#include<string>
#include <queue>
struct cell {
	cell(double d)		//参数为double的构造函数
	{
		num = d;
		type = false;
	}

	cell(char c)		//参数为char的构造函数
	{
		ch = c;
		type = true;
	}
	//数据成员
	bool type;			//标志cell里装的是运算符还是操作数，true表示是运算符
	char ch;
	double num;
};
//判断字符类型函数，返回true为符号，返回false为数字
bool type(char a);
//string转化为double
double trans_string_to_double(std::string s);
//string转化为double
double trans_string_to_double(const char *char_s);
//获取theta所对应的索引
int getIndex(char theta);
//判断theta1与theta2之间的优先级的函数
char getPriority(char theta1, char theta2);
//求阶乘
int fac(int x);
//输出这个表达式队列，测试用函数
void output(std::queue<cell> q);
//进入算术表达式计算模式
void mathCalcuMode();
