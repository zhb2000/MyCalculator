//分数
#include "pch.h"
#include "Fraction.h"

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
	int num;
	if (!(in >> num))
		return in;
	fract = Fraction(num);
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