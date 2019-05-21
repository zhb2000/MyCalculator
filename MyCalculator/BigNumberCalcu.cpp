//简单的大数运算 by 朱华彬
#include "pch.h"
#include "BigNumberCalcu.h"
using namespace std;

void BigNumCalcu_mode()
{
	while (true)
	{
		cout << "--------------------------------------------" << endl;
		cout << "[指令列表]输入对应的数字即可做相应的运算，输入quit退出大数运算模式，输入cls清屏\n";
		cout << "0-加法\t1-减法\t2-乘法\t3-除法" << endl;
		cout << "4-幂\t5-开方\t6-阶乘" << endl;
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "0")
			BigNum_add();
		else if (str == "1")
			BigNum_minus();
		else if (str == "2")
			BigNum_multiply();
		else if (str == "3")
			BigNum_divide();
		else if (str == "4")
			BigNum_pow();
		else if (str == "5")
			BigNum_root();
		else if (str == "6")
			BigNum_fact();
		else if (str == "cls")
			system("cls");
		else if (str == "quit")
			return;
		else
		{
			cout << "[错误]无法识别的指令\n\n";
		}
	}
}

void BigNum_add()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "输入第一个加数：" << endl;
	string num1;
	cin >> num1;
	cout << "输入第二个加数：" << endl;
	string num2;
	cin >> num2;
	cout << "计算中……" << endl;
	start_t = clock();//开始计时
	BigNumber result = BigNumber(num1) + BigNumber(num2);
	end_t = clock();//结束计时
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//转换成秒
	cout << "结果：" << endl << result << endl;
	cout << "用时：" << total_t << "秒" << endl << endl;
}

void BigNum_minus()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "输入被减数：" << endl;
	string num1;
	cin >> num1;
	cout << "输入减数：" << endl;
	string num2;
	cin >> num2;
	cout << "计算中……" << endl;
	start_t = clock();//开始计时
	BigNumber result = BigNumber(num1) - BigNumber(num2);
	end_t = clock();//结束计时
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//转换成秒
	cout << "结果：" << endl << result << endl;
	cout << "用时：" << total_t << "秒" << endl << endl;
}

void BigNum_multiply()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "输入第一个乘数：" << endl;
	string num1;
	cin >> num1;
	cout << "输入第二个乘数：" << endl;
	string num2;
	cin >> num2;
	cout << "计算中……" << endl;
	start_t = clock();//开始计时
	BigNumber result = multiply_num(BigNumber(num1), BigNumber(num2));
	end_t = clock();//结束计时
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//转换成秒
	cout << "结果：" << endl << result << endl;
	cout << "用时：" << total_t << "秒" << endl << endl;
}

void BigNum_divide()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "输入被除数：" << endl;
	string num1;
	cin >> num1;
	cout << "输入除数：" << endl;
	string num2;
	cin >> num2;
	cout << "计算中……" << endl;
	start_t = clock();//开始计时
	BigNumber result = divide_num(BigNumber(num1), BigNumber(num2));
	end_t = clock();//结束计时
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//转换成秒
	cout << "结果(保留10位小数)：" << endl << result << endl;
	cout << "用时：" << total_t << "秒" << endl << endl;
}

void BigNum_fact()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "输入要做阶乘运算的数：" << endl;
	string num;
	cin >> num;
	BigNumber bnum(num);
	if (bnum <= 0)
	{
		cout << "[错误]只有正整数才能做阶乘\n\n";
		return;
	}
	cout << "计算中……" << endl;
	start_t = clock();//开始计时
	BigNumber result = factorial_num(bnum);
	end_t = clock();//结束计时
	if (result == 0)
	{
		cout << "[错误]只有正整数才能做阶乘\n\n";
		return;
	}
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//转换成秒
	cout << "结果：" << endl << result << endl;
	cout << "用时：" << total_t << "秒" << endl << endl;
}

void BigNum_pow()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "输入底数：" << endl;
	string num1;
	cin >> num1;
	cout << "输入指数(只支持整数)：" << endl;
	string num2;
	cin >> num2;
	BigNumber bnum1(num1);
	BigNumber bnum2(num2);
	cout << "计算中……" << endl;
	start_t = clock();//开始计时
	BigNumber result = pow_int_index(bnum1, bnum2);
	end_t = clock();//结束计时
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//转换成秒
	cout << "结果(保留10位小数)：" << endl << result << endl;
	cout << "用时：" << total_t << "秒" << endl << endl;
}

void BigNum_root()
{
	clock_t start_t, end_t;
	double total_t;
	cout << "输入被开方数(只支持正数)：" << endl;
	string num1;
	cin >> num1;
	cout << "输入开方的次数(只支持正整数)：" << endl;
	string num2;
	cin >> num2;
	BigNumber bnum1(num1);
	BigNumber bnum2(num2);
	if (bnum1 <= 0 || bnum2 <= 0)
	{
		cout << "[错误]请重新输入\n\n";
		return;
	}
	cout << "计算中……" << endl;
	start_t = clock();//开始计时
	BigNumber result = nth_root_int(bnum1, bnum2);
	end_t = clock();//结束计时
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;//转换成秒
	cout << "结果(保留6位小数)：" << endl << result << endl;
	cout << "用时：" << total_t << "秒" << endl << endl;
}