//分数类的实现 
//by 朱华彬
#include "pch.h"
#include "Fraction.h"
#include <iterator>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cmath>
using namespace std;

///----构造函数----

Fraction::Fraction()
{
	numerator = 0;
	denominator = 1;
}

Fraction::Fraction(int num)
{
	numerator = num;
	denominator = 1;
}

Fraction::Fraction(int a, int b)
{
	if (b == 0)
		throw "分母不能为0 ！";
	if (a * b == 0)
		*this = Fraction(0);
	else if (a * b > 0)
	{
		numerator = abs(a);
		denominator = abs(b);
	}
	else
	{
		numerator = -abs(a);
		denominator = abs(b);
	}
	this->simplify();//约分化简
}

Fraction::Fraction(string s)
{
	int string_type = 0;//0表示整数，1表示带小数点，2表示两数相除
	for (string::iterator it = s.begin(); it != s.end(); it++)
	{
		if (*it == '.')
		{
			string_type = 1;
			break;
		}
		if (*it == '/')
		{
			string_type = 2;
			break;
		}
	}
	if (string_type == 0)//整数形式
	{
		int num = 0;
		int start = 0;//从哪个下标开始遍历
		int pos = 1;//正数设为1，负数设为-1，到时候乘一下就行
		if (s[0] == '-')
		{
			start = 1;//遍历的时候跳过负号
			pos = -1;
		}
		for (size_t i = start; i < s.size(); i++)
		{
			num *= 10;
			num += s[i] - '0';
		}
		*this = Fraction(num * pos);
	}
	else if (string_type == 1)//小数点形式
	{
		int num = 0;//整数的数字
		int start = 0;//从哪个下标开始遍历
		int pos = 1;//正数设为1，负数设为-1，到时候乘一下就行
		if (s[0] == '-')
		{
			start = 1;//遍历的时候跳过负号
			pos = -1;
		}
		size_t i = start;//两个循环都要用到，要记住位置
		//太丑了，以后重写
		for (; i < s.size(); i++)//计算整数的数字
		{
			if (s[i] == '.')
				break;//break后i并不会自增
			num *= 10;//前面的数字*10
			num += s[i] - '0';//加上当前数字
		}
		i++;
		Fraction fract = 0;//小数的数字
		Fraction base(1, 10);
		for (; i < s.size(); i++)//计算小数的数字
		{
			fract += (s[i] - '0') * base;
			base /= 10;
		}
		*this = (Fraction(num) + fract) * pos;
	}
	else//两数相除形式
	{
		int num1 = 0;//分子的数字
		int start = 0;//从哪个下标开始遍历
		int pos = 1;//正数设为1，负数设为-1，到时候乘一下就行
		if (s[0] == '-')
		{
			start = 1;//遍历的时候跳过负号
			pos = -1;
		}
		size_t i = start;//两个循环都要用到，要记住位置
		//太丑了，以后重写
		for (; i < s.size(); i++)//计算分子的数字
		{
			if (s[i] == '/')
				break;//break后i并不会自增
			num1 *= 10;//前面的数字*10
			num1 += s[i] - '0';//加上当前数字
		}
		i++;
		int num2 = 0;//分母的数字
		for (; i < s.size(); i++)//计算分母的数字
		{
			num2 *= 10;
			num2 += s[i] - '0';
		}
		*this = Fraction(num1 * pos, num2);
	}
}

Fraction::Fraction(const char *char_s)
{
	string s(char_s);
	*this = Fraction(s);
}

Fraction::Fraction(double num)
{
	string str;//将num转换为字符串
	stringstream ss;
	ss << setiosflags(ios::fixed);//设置为保留小数
	ss << setprecision(6) << num;//保留6位小数
	ss >> str;
	*this = Fraction(str);
}

///----成员函数----

//约分化简
Fraction Fraction::simplify()
{
	if (numerator == 0)
		return *this;
	else
	{
		int gcd_num = gcd(abs(numerator), abs(denominator));
		numerator /= gcd_num;
		denominator /= gcd_num;
		return *this;
	}
}

///----友元函数----

//相加
Fraction add_fract(Fraction fract1, Fraction fract2)
{
	int lcm_num = lcm(fract1.denominator, fract2.denominator);//分母的最小公倍数，即新的分母
	int num1 = lcm_num / fract1.denominator;//fract1上下将同乘num1
	int num2 = lcm_num / fract2.denominator;
	int new_numerator = fract1.numerator * num1 + fract2.numerator * num2;
	return Fraction(new_numerator, lcm_num);
}
//相减
Fraction minus_fract(Fraction fract1, Fraction fract2)
{
	int lcm_num = lcm(fract1.denominator, fract2.denominator);//分母的最小公倍数，即新的分母
	int num1 = lcm_num / fract1.denominator;//fract1上下将同乘num1
	int num2 = lcm_num / fract2.denominator;
	int new_numerator = fract1.numerator * num1 - fract2.numerator * num2;
	return Fraction(new_numerator, lcm_num);
}
//相乘
Fraction multiply_fract(Fraction fract1, Fraction fract2)
{
	return Fraction(fract1.numerator * fract2.numerator, fract1.denominator * fract2.denominator);
}
//相除
Fraction divide_fract(Fraction fract1, Fraction fract2)
{
	return Fraction(fract1.numerator * fract2.denominator, fract1.denominator * fract2.numerator);
}

///----运算符重载----

//运算符重载：输出流
ostream& operator<< (ostream &out, const Fraction &num)
{
	if (num.denominator == 1)
		out << num.numerator;
	else if (num.numerator == 0)
		out << 0;
	else
		out << num.numerator << "/" << num.denominator;
	return out;
}
//运算符重载：输入流
istream& operator>> (istream &in, Fraction &fract)
{
	string str;
	if (!(in >> str))
		return in;
	fract = Fraction(str);
	return in;
}
//运算符重载：相加+
Fraction operator+(Fraction fract1, Fraction fract2)
{
	return add_fract(fract1, fract2);
}
//运算符重载：相减-
Fraction operator-(Fraction fract1, Fraction fract2)
{
	return minus_fract(fract1, fract2);
}
//运算符重载：相乘*
Fraction operator*(Fraction fract1, Fraction fract2)
{
	return multiply_fract(fract1, fract2);
}
//运算符重载：相除/
Fraction operator/(Fraction fract1, Fraction fract2)
{
	return divide_fract(fract1, fract2);
}
//运算符重载：取相反数-
Fraction Fraction::operator-() const
{
	Fraction temp = *this;
	temp.numerator = -temp.numerator;
	return temp;
}
//运算符重载：前置++
Fraction & Fraction::operator++()
{
	*this = (*this) + 1;
	return *this;
}
//运算符重载：后置++
Fraction Fraction::operator++(int)
{
	Fraction old = *this;
	++(*this);
	return old;
}
//运算符重载：+=
Fraction & Fraction::operator+=(const Fraction & fract)
{
	*this = *this + fract;
	return *this;
}
//运算符重载：-=
Fraction & Fraction::operator-=(const Fraction & fract)
{
	*this = *this - fract;
	return *this;
}
//运算符重载：*=
Fraction & Fraction::operator*=(const Fraction & fract)
{
	*this = (*this) * fract;
	return *this;
}
//运算符重载：/=
Fraction & Fraction::operator/=(const Fraction & fract)
{
	*this = *this / fract;
	return *this;
}

//运算符重载 ==
bool operator==(const Fraction & fract1, const Fraction & fract2)
{
	Fraction temp = fract1 - fract2;
	if (temp.numerator == 0)
		return true;
	else
		return false;
}
//运算符重载 !=
bool operator!=(const Fraction & fract1, const Fraction & fract2)
{
	if (!(fract1 == fract2))
		return true;
	else
		return false;
}
//运算符重载 >
bool operator>(const Fraction & fract1, const Fraction & fract2)
{
	Fraction temp = fract1 - fract2;
	if (temp.numerator > 0)
		return true;
	else
		return false;
}
//运算符重载 >=
bool operator>=(const Fraction & fract1, const Fraction & fract2)
{
	if (fract1 > fract2 || fract1 == fract2)
		return true;
	else
		return false;
}
//运算符重载 <
bool operator<(const Fraction & fract1, const Fraction & fract2)
{
	if (!(fract1 >= fract2))
		return true;
	else
		return false;
}
//运算符重载 <=
bool operator<=(const Fraction & fract1, const Fraction & fract2)
{
	if (!(fract1 > fract2))
		return true;
	else
		return false;
}


///----其他函数----

//返回最大公因数，，要保证a、b都为正
int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

//返回最小公倍数，要保证 a、b都为正
int lcm(int a, int b)
{
	return a * b / gcd(a, b);
}