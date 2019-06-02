//命题逻辑 
//by 朱华彬
#include "pch.h"
#include "LogicalExpression.h"
#include <iostream>
#include <stack>
#include <iterator>
#include <queue>
#include <cmath>
using namespace std;

//命题逻辑模式
void logical_expression_mode()
{
	while (true)
	{
		cout << "--------------------------------------------" << endl;
		cout << "[指令列表]输入start即可开始，输入quit退出命题逻辑模式，输入cls清屏" << endl;
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "start")
		{
			cout << endl;
			logical_expression_start();
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

//命题逻辑开始
void logical_expression_start()
{
	cout << "使用方法：\n'!'代表否定,'&'代表合取,'|'代表析取,'>'代表蕴含,'~'代表等值\n命题变元用英文字母表示\n\n";
	cout << "请输入命题逻辑表达式：" << endl;
	string infix;//中缀表达式
	cin >> infix;
	string rpolish;//后缀表达式
	//第一次合法性校验
	if (trans_to_rpolish(infix, rpolish) == 0)//转换成后缀表达式
	{
		cout << "[错误]非法的表达式!\n\n";
		return;
	}
	cout << endl;
	map<char, bool> assignment;//指派
	init_assignment(infix, assignment);//用表达式将assignment初始化
	//第二次合法性校验（尝试求值）
	bool result_no_use;//没用的结果
	if (calcu_rpolish(rpolish, assignment, result_no_use) == 0)
	{
		cout << "[错误]非法的表达式!!\n\n";
		return;
	}

	TruthTable table;//真值表
	table.create(assignment, rpolish);
	cout << "真值表：" << endl;
	table.print_table();//打印真值表
	cout << endl;
	cout << "主合取范式：" << endl;
	table.print_CCNF();//打印主合取范式
	cout << "主析取范式：" << endl;
	table.print_CDNF();//打主析取范式
	cout << endl << "[系统提示]本次求解结束" << endl;
}

//判断是否是操作符
bool is_opch(char ch)
{
	if (ch == '&' || ch == '|' || ch == '!' || ch == '>' || ch == '~')
		return true;
	else
		return false;
}

//判断是否是命题变元
bool is_var(char ch)
{
	if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z')
		return true;
	else
		return false;
}

//将指派初始化
void init_assignment(string str, map<char, bool> &assignment)
{
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (is_var(*it))
		{
			if (assignment.count(*it) == 0)//assignment中不存在key为当前字母的元素
				assignment[*it] = 0;
		}
	}
}

//中缀表达式转换为后缀表达式
//返回1表示成功，返回0表示失败
Status trans_to_rpolish(string infix, string &rpolish)
{
	stack<char> opchar;//运算符栈
	rpolish.clear();
	for (string::iterator it = infix.begin(); it != infix.end(); it++)
	{
		if (is_var(*it))//是命题变元
		{
			rpolish.push_back(*it);//直接加入表达式
		}
		else//是运算符
		{
			if (*it == '(')
				opchar.push(*it);//左括号直接入栈
			else if (*it == '!')
				opchar.push(*it);//前置运算符直接入栈
			else if (*it == ')')//右括号，不停地出栈
			{
				if (opchar.empty())
					return 0;//要出栈时栈为空，失败
				while (opchar.top() != '(')//直到遇到左括号才停止
				{
					rpolish.push_back(opchar.top());
					opchar.pop();
					if (opchar.empty())
						return 0;//之后还要出栈，可栈为空，失败
				}
				opchar.pop();//左括号出栈，丢弃
			}
			else//当前运算符是"可比较优先级"的运算符
			{
				if (opchar.empty())//若栈为空，就不比了，直接入栈
					opchar.push(*it);
				else if (opchar.top() == '(')//若栈顶是左括号，就不比了，直接入栈
					opchar.push(*it);
				else if (opchar.top() == '!')//栈顶是前置运算符
				{
					do
					{
						rpolish.push_back(opchar.top());
						opchar.pop();
						if (opchar.empty())
							break;
					} while (opchar.top() == '!');
					opchar.push(*it);
				}
				else if (logical_priority[(*it)] >= logical_priority[(opchar.top())])//当前优先级>=栈顶优先级
				{
					opchar.push(*it);
				}
				else//当前优先级<栈顶优先级，不停地出栈，然后自己入栈
				{
					if (opchar.empty())
						return 0;//要出栈时栈为空，失败
					//直到遇到左括号才停止，左括号留在栈中
					while ((!opchar.empty()) && opchar.top() != '(')//此处运用了短路运算的特点，防止与空栈的栈顶元素进行比较
					{
						rpolish.push_back(opchar.top());
						opchar.pop();
					}
					opchar.push(*it);
				}
			}
		}
	}//遍历中缀表达式结束
	while (!opchar.empty())//若栈里还有运算符，依次弹出，加入后缀表达式
	{
		if (opchar.top() == '(')//表明左括号未配对，失败
			return 0;
		rpolish.push_back(opchar.top());
		opchar.pop();
	}
	return 1;
}

//用指派和后缀表达式创建真值表
void TruthTable::create(map<char, bool>assignment, string rpolish)
{
	int n = assignment.size();
	int num = (int)pow(2, n);//警告：从“double”转换到“int”，可能丢失数据
	for (int i = 0; i < num; i++)
	{
		map<char, bool> temp_assignment = assignment;//临时变量，储存本次的具体指派
		assign_assignment(temp_assignment, i);
		bool result;
		calcu_rpolish(rpolish, temp_assignment, result);//临时变量，本次运算的值
		TruthTableRow row = { temp_assignment, result };//临时变量，一行
		rows.push_back(row);
		if (result)
			num_of_true++;
		else
			num_of_false++;
	}
}

//打印真值表
void TruthTable::print_table()
{
	//打印表头
	map<char, bool> row_assignment = rows[0].assignment;
	for (map<char, bool>::iterator it = row_assignment.begin(); it != row_assignment.end(); it++)
	{
		cout << it->first << " ";
	}
	cout << "func" << endl;
	//打印表的本体
	//一行一行地遍历真值表，vec_it指向TruthTableRow型的遍历
	for (vector<TruthTableRow>::iterator vec_it = rows.begin(); vec_it != rows.end(); vec_it++)
	{
		map<char, bool> this_assignment = vec_it->assignment;//当前行的指派
		//遍历当前行的指派
		for (map<char, bool>::iterator it = this_assignment.begin(); it != this_assignment.end(); it++)
		{
			cout << it->second << " ";
		}
		cout << vec_it->func_result;
		cout << endl;
	}
}

//把n转成二进制数给指派的每个变元赋值
void assign_assignment(map<char, bool> &assignment, int n)
{
	queue<int> q;//保存二进制每一位数（反向）
	do
	{
		q.push(n % 2);
		n /= 2;
	} while (n);
	//int q_size = q.size();
	//反向迭代
	for (map<char, bool>::reverse_iterator it = assignment.rbegin(); it != assignment.rend(); it++)
	{
		if (q.empty())//表明低位数字已用完，则高位赋值0
		{
			it->second = 0;
		}
		else
		{
			int temp = q.front();
			q.pop();
			it->second = temp;
		}
	}
}

//计算后缀表达式
//返回1表示成功，返回0表示失败
Status calcu_rpolish(string rpolish, map<char, bool> assignment, bool &result)
{
	stack<bool> var_stack;
	for (string::iterator it = rpolish.begin(); it != rpolish.end(); it++)
	{
		if (is_var(*it))//是命题变元
		{
			var_stack.push(assignment[(*it)]);
		}
		else//是运算符
		{
			if (*it == '!')//单目运算符
			{
				if (var_stack.empty())
					return 0;
				bool temp = var_stack.top();
				var_stack.pop();
				var_stack.push(!temp);
			}
			else//双目运算符
			{
				if (var_stack.empty())
					return 0;
				bool rtemp = var_stack.top();//右操作数
				var_stack.pop();
				if (var_stack.empty())
					return 0;
				bool ltemp = var_stack.top();//左操作数
				var_stack.pop();
				bool result = calcu_two(ltemp, rtemp, *it);
				var_stack.push(result);
			}
		}
	}
	if (var_stack.size() != 1)
		return 0;
	result = var_stack.top();
	return 1;
}

//双目运算符的计算
bool calcu_two(bool left, bool right, char ch)
{
	if (ch == '&')
		return (right&&left);
	else if (ch == '|')
		return (right || left);
	else if (ch == '>')
	{
		if (left == true && right == false)
			return false;
		else
			return true;
	}
	else//ch=='~'
	{
		if (left == right)
			return true;
		else
			return false;
	}
}

//打印主合取范式
void TruthTable::print_CCNF()
{
	if (num_of_false == 0)
	{
		cout << "主合取范式不存在" << endl;
		return;
	}
	int false_sum = 0;//记录当前是第几个成假指派
	//一行一行地遍历真值表
	for (vector<TruthTableRow>::iterator vec_it = rows.begin(); vec_it != rows.end(); vec_it++)
	{
		if (vec_it->func_result == false)
		{
			false_sum++;
			cout << "(";
			//遍历当前行的指派
			for (map<char, bool>::iterator it = vec_it->assignment.begin(); it != vec_it->assignment.end(); it++)
			{
				if (it->second == false)//0对应原变量
					cout << it->first;
				else//1对应反变量
					cout << "!" << it->first;
				map<char, bool>::iterator last = vec_it->assignment.end();
				last--;//让迭代器last指向assignment中最后一个元素
				if (it != last)
				{
					cout << "|";
				}
			}
			cout << ")";
			if (false_sum < num_of_false)
				cout << "&";
			else
				break;
		}
	}
	cout << endl;
}

//打印主析取范式
void TruthTable::print_CDNF()
{
	if (num_of_true == 0)
	{
		cout << "主析取范式不存在" << endl;
		return;
	}
	int true_sum = 0;//记录当前是第几个成真指派
	//一行一行地遍历真值表
	for (vector<TruthTableRow>::iterator vec_it = rows.begin(); vec_it != rows.end(); vec_it++)
	{
		if (vec_it->func_result == true)
		{
			true_sum++;
			cout << "(";
			//遍历当前行的指派
			for (map<char, bool>::iterator it = vec_it->assignment.begin(); it != vec_it->assignment.end(); it++)
			{
				if (it->second == true)//1对应原变量
					cout << it->first;
				else//0对应反变量
					cout << "!" << it->first;
				map<char, bool>::iterator last = vec_it->assignment.end();
				last--;//让迭代器last指向assignment中最后一个元素
				if (it != last)
				{
					cout << "&";
				}
			}
			cout << ")";
			if (true_sum < num_of_true)
				cout << "|";
			else
				break;
		}
	}
	cout << endl;
}