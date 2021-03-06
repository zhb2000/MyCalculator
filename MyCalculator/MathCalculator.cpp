//算术表达式求值
//by 李政民
#include"pch.h"
#include <iostream>
#include<queue>
#include<stack>
#include<string>
#include<math.h>
#include"MathCalculator.h"


using namespace std;


//进入算术表达式计算模式
void mathCalcuMode() {

	string str;
	//int a;

	queue<cell> que;	//构造一个队列存放表达式,队列里装的是cell
	string temp_num;	//构造一个字符串临时存放数字

	cout << "请输入需要计算的算术表达式并且确保表达式是合法的" << endl;
	cin >> str;

	/*	//发现想通过输出来检查有点困难而且没什么意义，所以舍弃
		//通过getline()函数输出一遍算术表达式来检查是否合法
		getline(cin, str);
		cout << "请检查式子是否正确" << endl;
		cout << str << endl;
		cout << "正确请按1，错误请按0" << endl;
		cin >> a;

		if (a == 0) {
			do {
				cout << "请重新输入需要计算的算术表达式" << endl;
				getline(cin, str);
				cout << "请检查式子是否正确" << endl;
				cout << str << endl;
				cout << "正确请按1，错误请按0" << endl;
				cin >> a;
			} while (a == 1);
		}
		*/

		//词法分析
	for (string::iterator iter = str.begin(); iter != str.end(); iter++)
	{
		if (type(*iter))		//是符号
		{
			if (!temp_num.empty())//临时字符串非空
			{
				cell c(trans_string_to_double(temp_num));//把临时字符串转换成double，
				temp_num.clear();                        //并清空临时字符串用转换出的double构造cell，cell入队列
				que.push(c);
			}

			if (*iter == '-')
			{
				if (iter == str.begin())////把这个放在前面,是为了防止后面的代码在“往前看”时出现访问越界
				{
					cell c('~');
					que.push(c);
				}
				else
				{
					if ((*(iter - 1) >= '0' && *(iter - 1) <= '9') || *(iter - 1) == ')' || *(iter - 1) == '!')		//这个地方//前一个字符是数字 or 前一个字符是右括号 or 前一个字符是阶乘
					{
						cell c('-');
						que.push(c);
					}
					else
					{
						cell c('~');
						que.push(c);
					}
				}
			}
			else
			{
				cell c(*iter);
				que.push(c);
			}
		}
		else		//是数字
		{
			temp_num.push_back(*iter);//把数字插到临时字符串的末尾
		}
	}

	if (!temp_num.empty())
	{
		cell c(trans_string_to_double(temp_num));
		temp_num.clear();
		que.push(c);
	}

	/*queue<cell> temp_q = que;
	output(temp_q);
	cout << endl;*/

	//语法分析
	stack<cell> operats;		//构造一个栈放操作符
	queue<cell> postfix_expression;	//构造一个队列放后缀表达式

	while (!que.empty())
	{
		if (!que.front().type)		//是操作数
		{
			postfix_expression.push(que.front());		//直接入队列
			que.pop();
		}
		else						//是运算符
		{
			if (que.front().ch == '~')	//是前置运算符
			{
				operats.push(que.front());	//直接入栈
				que.pop();
			}
			else if (que.front().ch == '!')//是后置运算符
			{
				postfix_expression.push(que.front());	//直接入队列
				que.pop();
			}
			else
			{
				if (que.front().ch == '(')	//是左括号
				{
					operats.push(que.front());	//直接进栈
					que.pop();
				}
				else if (que.front().ch == ')')
				{
					while (operats.top().ch != '(')
					{
						postfix_expression.push(operats.top());
						operats.pop();		//栈顶元素不停地依次出栈，加入到队列中
					}                       //知道碰见栈顶元素为左括号，停止出栈
					operats.pop();		//左括号出栈但不入队列，右括号自己并不入栈
					que.pop();
				}
				else //当前运算符是定义了优先级的中置运算符

				{
					if (operats.empty())	//栈为空
					{
						operats.push(que.front());	//直接进栈
						que.pop();
					}
					else if (operats.top().ch == '~')	//栈顶是前置运算符
					{
						postfix_expression.push(operats.top());
						operats.pop();		//前置运算符出栈入队列
						operats.push(que.front());
						que.pop();
					}
					else if (operats.top().ch == '(')	//栈顶是左括号
					{
						operats.push(que.front());	//直接进栈
						que.pop();
					}
					else if (getPriority(que.front().ch, operats.top().ch) == '>')
					{

						//postfix_expression.push(operats.top().ch);
						//operats.pop();
						operats.push(que.front().ch);
						que.pop();

					}
					else if (getPriority(que.front().ch, operats.top().ch) == '<' || getPriority(que.front().ch, operats.top().ch) == '=')
					{
						while (!operats.empty())
						{
							if (operats.top().ch == '(')
								break;
							postfix_expression.push(operats.top());
							operats.pop();		//栈顶元素不停地依次出栈，加入到队列中
						}
						operats.push(que.front());
						que.pop();
					}
				}
			}
		}

		//que.pop();		//前缀表达式队列不断出队列

	}

	while (!operats.empty())	//遍历结束后，若栈里还有运算符，依次弹出，加入队列
	{
		postfix_expression.push(operats.top());
		operats.pop();
	}

	/*queue<cell> temp_q2 = postfix_expression;
	output(temp_q2);
	cout << endl;*/

	/*后缀表达式求解*/
	stack<cell> nums;			//构造一个栈放操作数，栈里装的是cell
	while (!postfix_expression.empty())
	{
		if (!postfix_expression.front().type)	//是操作数
		{
			//cout << postfix_expression.front().num;
			nums.push(postfix_expression.front());
		}
		else		//是运算符 
		{
			//cout << postfix_expression.front().ch;
			if (postfix_expression.front().ch == '!')
			{
				double a = nums.top().num;
				nums.pop();
				nums.push(double(fac(int(a))));
			}
			else if (postfix_expression.front().ch == '~')
			{
				double a = -nums.top().num;
				nums.pop();
				nums.push(a);

			}
			else
			{
				double n1 = nums.top().num;
				//cout << n1 << endl;
				nums.pop();
				double n2 = nums.top().num;
				//cout << n2 << endl;
				nums.pop();

				switch (getIndex(postfix_expression.front().ch))
				{
				case 0:
					nums.push(n2 + n1);
					break;
				case 1:
					nums.push(n2 - n1);
					break;
				case 2:
					nums.push(n2 * n1);
					break;
				case 3:
					nums.push(n2 / n1);
					break;
				case 4:
					nums.push(pow(n2, n1));
					break;
				default:
					break;
				}
			}
		}
		postfix_expression.pop();		//后缀表达式队列不断地出队列
	}
	cout << "运算结果是: " << nums.top().num << endl;
}

//判断字符类型函数，返回true为符号，返回false为数字
bool type(char a) {
	if (a == '+' || a == '-' || a == '*' || a == '/' || a == '^' || a == '!' || a == '(' || a == ')') //开始这里少了一个"!"啊!
		return true;
	else
		return false;
}

//string转化为double函数的定义 
double trans_string_to_double(string s)
{
	int string_type = 0;//0表示整数，1表示带小数点
	for (string::iterator it = s.begin(); it != s.end(); it++)
	{
		if (*it == '.')
		{
			string_type = 1;
			break;
		}
	}
	if (string_type == 0)//整数形式
	{
		double num = 0;
		for (size_t i = 0; i < s.size(); i++)
		{
			num *= 10;
			num += s[i] - '0';
		}
		return num;
	}
	else //string_type == 1 ,小数点形式
	{
		double num = 0;//整数部分 
		size_t i = 0;//两个循环都要用到，要记住位置

		for (; i < s.size(); i++)//计算整数的数字
		{
			if (s[i] == '.')
				break;//break后i并不会自增
			num *= 10;//前面的数字*10
			num += s[i] - '0';//加上当前数字
		}
		i++;
		double base = 0.1;
		for (; i < s.size(); i++)//计算小数的数字
		{
			num += (s[i] - '0') * base;
			base /= 10;
		}
		return num;
	}
}
//string转化为double
double trans_string_to_double(const char *char_s)
{
	string s(char_s);
	return trans_string_to_double(s);
}

//获取theta所对应的索引
int getIndex(char theta) {
	int index = 0;
	switch (theta) {
	case '+':
		index = 0;
		break;
	case '-':
		index = 1;
		break;
	case '*':
		index = 2;
		break;
	case '/':
		index = 3;
		break;
	case '^':
		index = 4;
		break;
	default:break;
	}
	return index;
}

//判断theta1与theta2之间的优先级的函数
char getPriority(char theta1, char theta2) {
	//运算符优先级关系表
	const char priority[5][5] = {
		{ '=','=','<','<','<'},
		{ '=','=','<','<','<'},
		{ '>','>','=','=','<'},
		{ '>','>','=','=','<'},
		{ '>','>','>','>','='},
	};
	int index1 = getIndex(theta1);
	int index2 = getIndex(theta2);
	return priority[index1][index2];
}


//求阶乘
int fac(int x)
{
	int i;
	int f = 1;
	for (i = 1; i <= x; i++)
	{
		f *= i;
	}
	return f;
}
//输出这个表达式队列，测试用函数
void output(std::queue<cell> q)
{
	while (!q.empty())
	{
		cell c = q.front();
		if (c.type)
			cout << c.ch;
		else
			cout << c.num;
		q.pop();
	}
}