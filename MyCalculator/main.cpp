// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "BigNumber.h"
#include "Fraction.h"
#include "Equation.h"

using namespace std;

int main()
{
	cout << "输入增广矩阵的行数,列数" << endl;
	int m, n;
	cin >> m >> n;
	Equation e = scan_matrix(m, n);
	cout << endl;
	e.solve();
	cout << endl;
	e.print_matrix();
	return 0;
}