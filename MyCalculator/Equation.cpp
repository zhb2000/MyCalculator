//线性方程组 by 朱华彬
#include "pch.h"
#include "Fraction.h"
#include "Equation.h"
using namespace std;

//构造函数,创建m行n列的二维vector
Equation::Equation(int m, int n)
{
	rows = m;
	cols = n;
	vec.resize(m);
	for (int i = 0; i < m; i++)
		vec[i].resize(n);
}

///----成员函数----

///----初等行变换----

//把第i行加到第j行
void Equation::add_i_to_j(int i, int j)
{
	for (int a = 0; a < cols; a++)
	{
		vec[j][a] = vec[j][a] + vec[i][a];
	}
}
//第i行变成k倍
void Equation::row_i_multiple_k(int i, Fraction k)
{
	for (int a = 0; a < cols; a++)
	{
		vec[i][a] = vec[i][a] * k;
	}
}
//把第i行乘k加到第j行
void Equation::add_ki_to_j(int i, Fraction k, int j)
{
	for (int a = 0; a < cols; a++)
	{
		vec[j][a] = vec[j][a] + k * vec[i][a];
	}
}
//交换第i行和第j行
void Equation::swap_i_j(int i, int j)
{
	for (int a = 0; a < cols; a++)
	{
		swap(vec[i][a], vec[j][a]);
	}
}


//打印增广矩阵
void Equation::print_matrix() const
{
	int m = rows;
	int n = cols;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}

//将系数矩阵化为行简化阶梯阵
void Equation::trans_to_stair()
{
	//系数阵的每一列
	//now_col表示当前列下标
	int k = 0;
	for (int now_col = 0; now_col < cols - 1; now_col++)
	{
		if (k > rows - 1)
			break;
		if(this->col_i_k_th(now_col, k) != 0)
			k++;
	}
}
//将下标第i列的下标第k个元素化为1，其余化为0
//返回0表示该列全0,返回1表示该列非全0
Status Equation::col_i_k_th(int i, int k)
{
	if (vec[k][i] == 0)//若该位置为0,则做对换
	{
		bool flag = false;//是否有行对换
		for (int a = k+1; a < rows; a++)
		{
			if (vec[a][i] != 0)
			{
				this->swap_i_j(a, k);
				flag = true;
				break;
			}
		}
		if (!flag)
			return 0;
	}//if
	this->row_i_multiple_k(k, 1 / vec[k][i]);//化为1
	for (int a = 0; a < rows; a++)
	{
		if (a != k)
		{
			this->add_ki_to_j(k, -vec[a][i], a);
		}
	}
	return 1;
}

//求秩
void Equation::calculate_rank()
{
	//计算增广矩阵的秩
	zeng_guang_rank = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (vec[i][j] != 0)
			{
				zeng_guang_rank++;
				break;
			}
		}
	}
	//计算系数矩阵的秩
	xi_shu_rank = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols - 1; j++)
		{
			if (vec[i][j] != 0)
			{
				xi_shu_rank++;
				break;
			}
		}
	}
}

//齐次方程组求解，用ans存解向量组
//返回0表示只有0解，返回1表示有无穷多解
Status Equation::solve_homo(VectorGroup &ans) const
{
	//系数阵的秩等于系数阵的列数，只有0解
	if (xi_shu_rank == cols - 1)
	{
		ans.resize(1);//开辟一个解向量的空间
		ans[0].resize(cols - 1, 0);//解向量中有cols - 1个变元
		return 0;
	}
	//有无穷多解
	else
	{
		//自由变元的个数
		int free = cols - 1 - xi_shu_rank;
		//即基解组中解向量的个数
		ans.resize(free);
		for (int i = 0; i < free; i++)
			ans[i].resize(cols - 1);//解向量中有cols - 1个变元

		//记录谁是约束变元，谁是自由变元
		//0表示自由变元，1表示约束变元
		vector<bool> record;
		record.resize(cols - 1, 0);//分配空间并初始化为0
		//每行第一个非0元所在的列对应的是约束变元
		for (int i = 0; i < xi_shu_rank; i++)
		{
			for (int j = 0; j < cols - 1; j++)
			{
				if (vec[i][j] != 0)
				{
					record[j] = 1;
					break;
				}
			}
		}

		map<int, int> record2;//记录该自由变元是第几个自由变元（从0开始计数）
		int n = 0;//第几个自由变元
		for (int i = 0; i < cols - 1; i++)
		{
			if (record[i] == 0)
			{
				record2[i] = n;
				n++;
			}
		}


		//第a轮（从0开始），计算下标为a的解向量
		//第a轮求解就把第a个自由变元指派为1，其余自由变元指派为0
		for (int a = 0; a < free; a++)
		{
			//求下标第i个变元
			for (int i = 0; i < cols - 1; i++)
			{
				//下标第i的变元是自由变元
				if (record[i] == 0)
				{
					//给自由变元取1或取0
					if (record2[i] == a)
						ans[a][i] = 1;
					else
						ans[a][i] = 0;
				}
				else//下标第i的变元是约束变元
				{
					//寻找下标第i列非0元（值为1）所在的行号
					int at_row = 0;//所在行号
					for (int r = 0; r < rows; r++)
					{
						if (vec[r][i] != 0)
						{
							at_row = r;
							break;
						}
					}
					Fraction temp = vec[at_row][cols - 1];
					//下标at_row行的下标第j个变元
					for (int j = i; j < cols - 1; j++)
					{
						//该变元是自由变元，且在此轮求解中被指派为1
						if (record[j] == 0 && record2[j] == a)
							temp -= vec[at_row][j];
					}
					ans[a][i] = temp;
				}
			}
		}
		return 1;
	}
}

//非齐次方程组求解，用ans存解向量组
//返回-1表示无解，返回0表示有唯一解，返回1表示有无穷多解
Status Equation::solve_inhomo(vector<elem> &ans_te, VectorGroup &ans_tong) const
{
	//系数矩阵的秩与增广矩阵的秩不相等，无解
	if (xi_shu_rank != zeng_guang_rank)
		return -1;
	//系数阵的秩等于系数阵的列数，有唯一解
	if (xi_shu_rank == cols - 1)
	{
		//ans.resize(1);//开辟一个解向量的空间
		for (int i = 0; i < cols - 1; i++)////解向量中有cols - 1个变元
		{
			ans_te.push_back(vec[i][cols - 1]);
		}
		return 0;
	}
	//有无穷多解
	else
	{
		Equation dao_chu_zu = *this;//导出组
		for (int i = 0; i < rows; i++)
			dao_chu_zu.vec[i][rows] = 0;
		dao_chu_zu.solve_homo(ans_tong);

		//从齐次组求解移植而来

		//自由变元的个数
		int free = cols - 1 - xi_shu_rank;
		ans_te.resize(cols - 1);//解向量中有cols - 1个变元

		//记录谁是约束变元，谁是自由变元
		//0表示自由变元，1表示约束变元
		vector<bool> record;
		record.resize(cols - 1, 0);//分配空间并初始化为0
		//每行第一个非0元所在的列对应的是约束变元
		for (int i = 0; i < xi_shu_rank; i++)
		{
			for (int j = 0; j < cols - 1; j++)
			{
				if (vec[i][j] != 0)
				{
					record[j] = 1;
					break;
				}
			}
		}

		//求下标第i个变元
		for (int i = 0; i < cols - 1; i++)
		{
			//下标第i的变元是自由变元
			if (record[i] == 0)
			{
				ans_te[i] = 0;
			}
			else//下标第i的变元是约束变元
			{
				//寻找下标第i列非0元（值为1）所在的行号
				int at_row = 0;//所在行号
				for (int r = 0; r < rows; r++)
				{
					if (vec[r][i] != 0)
					{
						at_row = r;
						break;
					}
				}
				Fraction temp = vec[at_row][cols - 1];
				ans_te[i] = temp;
			}
		}
		return 1;
	}
}

//求解并打印
void Equation::solve()
{
	this->trans_to_stair();
	this->calculate_rank();
	if (this->type == homo)//齐次
	{
		VectorGroup ans;
		if(this->solve_homo(ans) == 1)//有无穷多解
		{
			cout << "该齐次方程组有无穷多解" << endl;
			cout << "它的一个通解为：" << endl;
			cout << "X = ";
			int size = ans.size();//解向量的个数
			int num = ans[0].size();//一个解向量中元素的个数
			for (int i = 0; i < size; i++)
			{
				cout << "k" << i + 1 << "(";
				for (int j = 0; j < num; j++)
				{
					cout << ans[i][j];
					if (j < num - 1)
						cout << ", ";
				}
				cout << ")";
				if (i < size - 1)
					cout << " + ";
			}
			cout << endl;
		}
		else//只有零解
		{
			cout << "该齐次方程组只有零解" << endl;
			cout << "X = (";
			for (size_t i = 0; i < ans[0].size(); i++)
			{
				cout << "0";
				if (i < ans[0].size() - 1)
					cout << ", ";
			}
			cout << ")" << endl;
		}
	}
	else//非齐次
	{
		vector<elem> ans_te;
		VectorGroup ans_tong;
		int status = this->solve_inhomo(ans_te, ans_tong);
		if (status == -1)
			cout << "该非齐次方程组无解" << endl;
		else if (status == 0)
		{
			cout << "该非齐次方程组有唯一解" << endl;
			cout << "X = (";
			int num = ans_te.size();
			for (int i = 0; i < num; i++)
			{
				cout << ans_te[i];
				if (i < num - 1)
					cout << ", ";
			}
			cout << ")" << endl;
		}
		else
		{
			cout << "该非齐次方程组有无穷多解" << endl;
			cout << "它的一个通解为：" << endl;
			cout << "X = (";
			int num = ans_te.size();//特解的解向量元素个数
			for (int i = 0; i < num; i++)
			{
				cout << ans_te[i];
				if (i < num - 1)
					cout << ", ";
			}
			cout << ") + ";
			int size = ans_tong.size();//导出组基解组的解向量个数
			int num2 = ans_tong[0].size();//基解组解向量元素个数
			for (int i = 0; i < size; i++)
			{
				cout << "k" << i + 1 << "(";
				for (int j = 0; j < num2; j++)
				{
					cout << ans_tong[i][j];
					if (j < num2 - 1)
						cout << ", ";
				}
				cout << ")";
				if (i < size - 1)
					cout << " + ";
			}
			cout << endl;
		}
	}
}

///----其他函数----

//读入增广矩阵
Equation scan_matrix(int m, int n)
{
	Equation e(m, n);//构造矩阵
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> e.vec[i][j];
	}
	for(int i = 0; i < m; i++)
	{
		if (e.vec[i][n - 1] != 0)
		{
			e.type = inhomo;//非齐次
			return e;
		}
	}
	e.type = homo;//齐次
	return e;
}

//进入求解线性方程组模式
void equation_mode()
{
	while (true)
	{
		cout << "--------------------------------------------" << endl;
		cout << "[指令列表]输入start即可开始，输入quit退出求解线性方程组模式，输入cls清屏" << endl;
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "start")
		{
			cout << endl;
			equation_start();
		}
		else if (str == "quit")
		{
			cout << "[系统提示]已退出求解线性方程组模式" << endl << endl;
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

//开始求解线性方程组
void equation_start()
{
	int m, n;
	cout << "请输入方程组增广矩阵的行数、列数：" << endl;
	cin >> m >> n;
	cout << "请输入方程组的增广矩阵：" << endl;
	Equation e = scan_matrix(m, n);//读取并创建方程组e
	cout << endl;
	e.solve();//求解并打印结果
	cout << endl;
	while (true)//结束求解的相关操作
	{
		cout << "[指令列表]输入ok结束本次求解,输入printm打印变换出的行简化阶梯阵" << endl;
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "ok")
		{
			cout << "[系统提示]本次求解结束" << endl;
			return;
		}
		else if (str == "printm")
		{
			cout << "行简化阶梯阵：" << endl;
			e.print_matrix();
			cout << "[系统提示]本次求解结束" << endl;
			return;
		}
		else
		{
			cout << "[错误]无法识别的指令\n" << endl;
		}
	}
}