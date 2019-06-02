//命题逻辑头文件 
//by 朱华彬
#pragma once

#include <string>
#include <map>
#include <vector>

//函数返回状态代码
typedef int Status;
//运算符优先级
static std::map<char, int> logical_priority = { {'~', 1},{'>', 2},{'|',3},{'&',4},{'!',5} };

//真值表的一行
struct TruthTableRow
{
	std::map<char, bool> assignment;//对每个变元的具体指派
	bool func_result;//该行的结果
};
//真值表
struct TruthTable
{
	//构造函数，把num_of_true和num_of_false初始化为0
	TruthTable()
	{
		num_of_true = 0;
		num_of_false = 0;
	}

	//----成员函数----

	//用指派和后缀表达式创建真值表
	void create(std::map<char, bool>assignment, std::string rpolish);
	//打印真值表
	void print_table();
	//打印主合取范式
	void print_CCNF();
	//打印主析取范式
	void print_CDNF();

	//----数据成员----

	std::vector<TruthTableRow> rows;//一行
	int num_of_true;//结果为真的行数
	int num_of_false;//结果为假的行数
};

//命题逻辑模式
void logical_expression_mode();
//命题逻辑开始
void logical_expression_start();

//判断是否是操作符
bool is_opch(char ch);
//判断是否是命题变元
bool is_var(char ch);

//将指派初始化
void init_assignment(std::string str, std::map<char, bool> &assignment);
//中缀表达式转换为后缀表达式
//返回1表示成功，返回0表示失败
Status trans_to_rpolish(std::string infix, std::string &rpolish);
//把n转成二进制数给指派的每个变元赋值
void assign_assignment(std::map<char, bool> &assignment, int n);
//计算后缀表达式
//返回1表示成功，返回0表示失败
Status calcu_rpolish(std::string rpolish, std::map<char, bool> assignment, bool &result);
//双目运算符的计算
bool calcu_two(bool left, bool right, char ch);