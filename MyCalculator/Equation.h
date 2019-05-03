#pragma once
//线性方程组
#include <vector>
#include "Fraction.h"
#include <algorithm>
#include <map>

typedef Fraction elem;//矩阵的元素
typedef int Status;//返回状态
typedef vector<vector<elem>> VectorGroup;//向量组
enum EquationType
{	homo, //齐次
	inhomo//非齐次
};//方程组的类型

struct Equation
{
	//构造函数,创建m行n列的二维vector
	Equation(int m, int n);
	
	///----成员函数----

	///----初等行变换----

	//把下标第i行加到下标第j行
	void add_i_to_j(int i, int j);
	//下标第i行变成k倍
	void row_i_multiple_k(int i, Fraction k);
	//把下标第i行乘k加到下标第j行
	void add_ki_to_j(int i, Fraction k, int j);
	//交换下标第i行和下标第j行
	void swap_i_j(int i, int j);

	//打印增广矩阵
	void print_matrix() const;
	//化为行简化阶梯阵
	void trans_to_stair();
	//将下标第i列的下标第k个元素化为1，其余化为0
	//返回0表示该列全0,返回1表示该列非全0
	Status col_i_k_th(int i, int k);
	//求秩
	void calculate_rank();

	//齐次方程组求解，用ans存解向量组
	//返回0表示只有0解，返回1表示有无穷多解
	Status solve_homo(VectorGroup &ans) const;
	//非齐次方程组求解，用ans存解向量组
	//返回-1表示无解，返回0表示有唯一解，返回1表示有无穷多解
	Status solve_inhomo(vector<elem> &ans_te, VectorGroup &ans_tong) const;
	void solve();
	///----数据成员----

	//增广矩阵,动态二维数组
	vector<vector<elem>> vec;
	int rows;//增广矩阵的行数
	int cols;//增广矩阵的列数
	EquationType type;//方程组的类型
	int xi_shu_rank;//系数矩阵的秩
	int zeng_guang_rank;//增广矩阵的秩
};

//读入增广矩阵
Equation scan_matrix(int m, int n);