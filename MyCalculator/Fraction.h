#pragma once
//分数类头文件 by 朱华彬
#include <iostream>
#include <cmath>
#include <string>
#include <iterator>
#include <iomanip>
#include <sstream>
using namespace std;

class Fraction
{
public:
	///----构造函数----

	Fraction();
	Fraction(int num);
	Fraction(int a, int b);
	Fraction(string s);
	Fraction(const char *char_s);
	Fraction(double num);

	///----成员函数----

	//约分化简
	Fraction simplify();

	///----友元函数----

	friend Fraction add_fract(Fraction fract1, Fraction fract2);
	friend Fraction minus_fract(Fraction fract1, Fraction fract2);
	friend Fraction multiply_fract(Fraction fract1, Fraction fract2);
	friend Fraction divide_fract(Fraction fract1, Fraction fract2);

	///----运算符重载----

	friend ostream& operator<< (ostream &out, const Fraction &num);
	friend istream& operator>> (istream &in, Fraction &num);
	friend Fraction operator+ (Fraction fract1, Fraction fract2);
	friend Fraction operator- (Fraction fract1, Fraction fract2);
	friend Fraction operator* (Fraction fract1, Fraction fract2);
	friend Fraction operator/ (Fraction fract1, Fraction fract2);
	Fraction operator- () const;
	Fraction& operator++ ();
	Fraction operator++ (int);
	Fraction& operator+= (const Fraction &fract);
	Fraction& operator-= (const Fraction &fract);
	Fraction& operator*= (const Fraction &fract);
	Fraction& operator/= (const Fraction &fract);
	friend bool operator== (const Fraction &fract1, const Fraction &fract2);
	friend bool operator!= (const Fraction &fract1, const Fraction &fract2);
	friend bool operator> (const Fraction &fract1, const Fraction &fract2);
	friend bool operator>= (const Fraction &fract1, const Fraction &fract2);
	friend bool operator< (const Fraction &fract1, const Fraction &fract2);
	friend bool operator<= (const Fraction &fract1, const Fraction &fract2);


private:
	int numerator;//分子
	int denominator;//分母
};

///----其他函数----

//返回最大公因数，要保证a、b都为非负
int gcd(int a, int b);
//返回最小公倍数，要保证 a、b都为正
int lcm(int a, int b);

Fraction add_fract(Fraction fract1, Fraction fract2);
Fraction minus_fract(Fraction fract1, Fraction fract2);
Fraction multiply_fract(Fraction fract1, Fraction fract2);
Fraction divide_fract(Fraction fract1, Fraction fract2);

ostream& operator<< (ostream &out, const Fraction &num);
istream& operator>> (istream &in, Fraction &num);
Fraction operator+ (Fraction fract1, Fraction fract2);
Fraction operator- (Fraction fract1, Fraction fract2);
Fraction operator* (Fraction fract1, Fraction fract2);
Fraction operator/ (Fraction fract1, Fraction fract2);

bool operator== (const Fraction &fract1, const Fraction &fract2);
bool operator!= (const Fraction &fract1, const Fraction &fract2);
bool operator> (const Fraction &fract1, const Fraction &fract2);
bool operator>= (const Fraction &fract1, const Fraction &fract2);
bool operator< (const Fraction &fract1, const Fraction &fract2);
bool operator<= (const Fraction &fract1, const Fraction &fract2);