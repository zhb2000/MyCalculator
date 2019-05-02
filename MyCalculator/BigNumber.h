#pragma once
//大数
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
using namespace std;

static const int PRECISION = 10;//保留的小数位
//static const int BASE = 100000000;

//高精度实数类型
class BigNumber
{
public:
	///----构造函数----

	//无参数的构造函数
	BigNumber();
	//参数为int的构造函数
	BigNumber(int num);
	//参数为double的构造函数
	BigNumber(double num);
	//参数为string的构造函数
	BigNumber(const string &num);
	//参数为char *的构造函数
	BigNumber(const char *num);

	///----成员函数----

	//清除多余的0，重新计算长度，顺便修正全0数的符号
	void clean_zero();
	//保留小数
	void accuracy(int precision = PRECISION);
	//变成相反数
	void set_opposite();
	//移动该数字的小数点
	//direction 0为左，1为右，place表示移动几位
	void move_dot(bool direction, unsigned int place);
	//返回转换成的整数
	long long  get_int() const;
	//返回转换成的实数
	long double get_real() const;

	///----友元函数----

	//返回绝对值
	friend BigNumber abs(const BigNumber &num);
	//比较两个数的绝对值，num1大返回1，num2大返回-1，相等返回0
	friend int cmp_abs(const BigNumber &num1, const BigNumber &num2);
	//返回两数绝对值之和
	friend BigNumber add_abs(const BigNumber &num1, const BigNumber &num2);
	//返回两数绝对值之差（结果非负）
	friend BigNumber minus_abs(const BigNumber &num1, const BigNumber &num2);
	//返回两数的整除
	friend BigNumber divide_exactly(const BigNumber &num1, const BigNumber &num2);
	//返回两数的取余
	friend BigNumber rem_num(const BigNumber &num1, const BigNumber &num2);
	//返回两数之和
	friend BigNumber add_num(const BigNumber &num1, const BigNumber &num2);
	//返回两数之差
	friend BigNumber minus_num(const BigNumber &num1, const BigNumber &num2);
	//返回两数之积
	friend BigNumber multiply_num(const BigNumber &num1, const BigNumber &num2);
	//返回两数之商，precision是保留的小数位数
	friend BigNumber divide_num(const BigNumber &num1, const BigNumber &num2, int precision);
	//返回数的阶乘
	friend BigNumber factorial_num(const BigNumber &num);
	//返回数的整数次幂，base是底数，index是指数
	//index必须为整数,且index会被转化成long long
	friend BigNumber pow_int_index(const BigNumber &base, const BigNumber &index);
	//返回数的整数次开根
	//degree必须为整数,且degree会被转化成int
	friend BigNumber nth_root_int(const BigNumber &radicand, const BigNumber &degree);

	///----运算符重载----

	//运算符重载：输出流
	friend ostream& operator<< (ostream &out, const BigNumber &num);
	//运算符重载：输入流
	friend istream& operator>> (istream &in, BigNumber &num);
	//运算符重载：判等==
	friend bool operator== (const BigNumber &num1, const BigNumber &num2);
	//运算符重载：不等于!=
	friend bool operator!= (const BigNumber &num1, const BigNumber &num2);
	//运算符重载：大于>
	friend bool operator> (const BigNumber &num1, const BigNumber &num2);
	//运算符重载：小于<
	friend bool operator< (const BigNumber &num1, const BigNumber &num2);
	//运算符重载：大于等于>=
	friend bool operator>= (const BigNumber &num1, const BigNumber &num2);
	//运算符重载：小于等于<=
	friend bool operator<= (const BigNumber &num1, const BigNumber &num2);
	//运算符重载：相加+
	friend BigNumber operator+ (const BigNumber &num1, const BigNumber &num2);
	//运算符重载：相减-
	friend BigNumber operator- (const BigNumber &num1, const BigNumber &num2);
	//运算符重载：相乘*(保留PRECISION位小数)
	friend BigNumber operator* (const BigNumber &num1, const BigNumber &num2);
	//运算符重载：相除/(保留PRECISION位小数)
	friend BigNumber operator/ (const BigNumber &num1, const BigNumber &num2);
	//运算符重载：取余%
	friend BigNumber operator% (const BigNumber &num1, const BigNumber &num2);
	//运算符重载：取相反数-
	void operator- ();
	//运算符重载：前置++
	BigNumber& operator++ ();
	//运算符重载：后置++
	BigNumber operator++ (int);
	//运算符重载：+=
	BigNumber& operator+= (const BigNumber &num);
	//运算符重载：-=
	BigNumber& operator-= (const BigNumber &num);
	//运算符重载：*=
	BigNumber& operator*= (const BigNumber &num);
	//运算符重载：/= 做除法而不是整除
	BigNumber& operator/= (const BigNumber &num);
	//运算符重载：%=
	BigNumber& operator%= (const BigNumber &num);

private:
	vector<int> integer;//整数部分，逆序
	vector<int> decimal;//小数部分，顺序
	int int_len;//整数位数
	int dec_len;//小数位数
	char pos;//'+'表示整数，'-'表示负数，'0'表示0
};

BigNumber divide_num(const BigNumber &num1, const BigNumber &num2, int precision = PRECISION);