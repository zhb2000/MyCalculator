//矩阵计算器 头文件
//by 马骁
#pragma once

#include "Fraction.h"
typedef Fraction MElem;

//这里定义了类：数组 数组是类矩阵的子类
class Tableau {
public:
	Tableau(int newa, int newb);//声明构造函数
	~Tableau();					  //声明析构函数					  
	Tableau(const Tableau &t);//声明复制构造函数

	int setTableau();//声明初始化矩阵中的元素的函数
	void getTableau() const;//声明以矩阵形式输出矩阵的函数
	int geta() const;//返回矩阵的行数
	int getb() const;//返回矩阵的列数
	Tableau& operator= (const Tableau &t);//重载=运算符，实现深复制

	//把下标第i行加到第j行
	void add_i_to_j(int i, int j);
	//下标第i行变成k倍
	void row_i_multiple_k(int i, MElem k);
	//把下标第i行乘k加到第j行
	void add_ki_to_j(int i, MElem k, int j);
	//交换下标第i行和第j行
	void swap_i_j(int i, int j);

	///----数据成员----

	MElem **sz;//二维矩阵
private:
	int a;//行数
	int b;//列数

};

//矩阵的加法
void add();
//矩阵的减法
void subtract();
//计算行列式并返回计算结果
MElem calculateDet(int n, MElem** d);
//调用计算行列式的函数
void getDet();
//返回t矩阵的转置矩阵
Tableau return_trans(const Tableau &t);
//这个函数用让用户输入矩阵并调用函数return_trans来进行矩阵的转置
void getTransposition();
//矩阵乘法
Tableau mul();
//让用户输入矩阵，并计算逆阵
void getinverse();
//把t化为单位阵，单位阵e就变成了逆阵
//必须保证t是可逆阵
void trans_to_I(Tableau &t, Tableau &e);
//将t矩阵下标第i列的下标第k个元素化为1，其他元素化为0
 //对e矩阵做同样的变换
 //必须保证t是可逆阵
void col_i_k_th(int i, int k, Tableau &t, Tableau &e);
//构造并返回一个n阶单位阵
Tableau create_I(int n);
//调用矩阵运算的函数
void calcu_matrix();