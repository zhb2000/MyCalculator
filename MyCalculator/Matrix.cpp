//矩阵计算器的实现
//by 马骁

#include "pch.h"
#include <iostream>
#include <string>
#include "Matrix.h"
using namespace std;
/*这一部分实现类的成员函数*/

/*实现构造函数 这里在构造函数内使用动态数组初始化了一个二维数组*/
Tableau::Tableau(int newa, int newb) {
	a = newa;
	b = newb;
	sz = new MElem*[a];
	for (int i = 0; i < newa; i++)//用new创造二维数组
	{
		sz[i] = new MElem[newb];
	}
}

//复制构造函数的实现
Tableau::Tableau(const Tableau &t)
{
	a = t.a;
	b = t.b;
	sz = new MElem*[a];
	for (int i = 0; i < a; i++)//用new创造二维数组
	{
		sz[i] = new MElem[b];
	}
	for (int r = 0; r < a; r++)
	{
		for (int c = 0; c < b; c++)
		{
			sz[r][c] = t.sz[r][c];
		}
	}
}

//实现析构函数，这里在析构函数中释放了数组sz的动态内存
Tableau::~Tableau() {
	for (int i = 0; i < a; i++)
	{
		delete[] sz[i];
	}
	delete[] sz;
}

//重载=运算符，实现深复制
Tableau & Tableau::operator=(const Tableau & t)
{
	a = t.a;
	b = t.b;
	delete[] sz;
	sz = new MElem*[a];
	for (int i = 0; i < a; i++)//用new创造二维数组
	{
		sz[i] = new MElem[b];
	}
	for (int r = 0; r < a; r++)
	{
		for (int c = 0; c < b; c++)
		{
			sz[r][c] = t.sz[r][c];
		}
	}
	return *this;
}

//这里定义初始化矩阵元素的函数 用输出语句提示用户输入数组
int Tableau::setTableau() {
	//利用嵌套的for结构来实现矩阵中元素的输入
	for (int p = 0; p < a; p++) {
		cout << "请输入第" << (p + 1) << "行的元素，并以空格将它们隔开" << endl;
		for (int q = 0; q < b; q++) {
			MElem element;
			cin >> element;
			sz[p][q] = element;
		}
	}
	cout << "矩阵输入完毕" << endl;
	return 0;
}

//打印矩阵
void Tableau::getTableau() const
{
	for (int x = 0; x < a; ++x)
	{
		cout << endl;
		for (int y = 0; y < b; ++y)
		{
			cout << sz[x][y] << " ";

		}
	}
	cout << endl;
}

//返回矩阵的行数
int Tableau::geta() const
{
	return a;
}

//返回矩阵的列数
int Tableau::getb() const
{
	return b;
}

//这里定义并实现了矩阵的加法
void add() {
	cout << "下面开始计算矩阵的加法" << endl;
	int r; int c; int i;
s1: cout << "请输入矩阵1的行数，并以回车结束" << endl;
	cin >> r;
	cout << "请输入矩阵1的列数，并以回车结束" << endl;
	cin >> c;
	Tableau t1(r, c);									//先构造两个矩阵实例并指导用户输入
	t1.setTableau();
	t1.getTableau();
	cout << "请检查矩阵1是否输入正确,若正确请输入1，若错误请输入2,并以回车结束" << endl;
	cin >> i;
	if (i == 2) goto s1;								/*这里用goto语句实现允许用户检查错误
													   并改正的功能*/
s2: cout << "请输入矩阵2的行数，并以回车结束" << endl;
	cin >> r;
	cout << "请输入矩阵2的列数，并以回车结束" << endl;
	cin >> c;
	Tableau t2(r, c);
	t2.setTableau();
	t2.getTableau();
	cout << "请检查矩阵2是否输入正确,若正确请输入1，若错误请输入2,并以回车结束" << endl;
	cin >> i;
	if (i == 2) goto s2;
	/*输入完毕后先判断两个矩阵是否为
	同型矩阵，如果是继续加法，如果不
	是那么提醒用户输入错误*/
	int a1 = t1.geta();
	int b1 = t1.getb();
	int a2 = t2.geta();
	int b2 = t2.getb();
	if (a1 == a2 && b1 == b2) {						/*构造一个实例t3来承载矩阵加法的和
													   并通过嵌套循环结构实现矩阵加法*/
		Tableau t3(a1, b1);
		for (int i1 = 0; i1 < a1; i1++) {
			for (int i2 = 0; i2 < b1; i2++) {
				t3.sz[i1][i2] = t1.sz[i1][i2] + t2.sz[i1][i2];
			}
		}
		cout << "矩阵加法计算完毕" << endl;
		t3.getTableau();
		return;
	}
	else {
		cout << "您所输入的矩阵并非同型矩阵，不能进行矩阵加法" << endl;
		return;
	}
}

//这里定义并实现矩阵的减法
void subtract() {
	cout << "下面开始计算矩阵的加法" << endl;
	int r; int c; int i;
s1: cout << "请输入减矩阵的行数，并以回车结束" << endl;
	cin >> r;
	cout << "请输入减矩阵的列数，并以回车结束" << endl;
	cin >> c;
	Tableau t1(r, c);
	t1.setTableau();
	t1.getTableau();
	cout << "请检查减矩阵是否输入正确,若正确请输入1，若错误请输入2,并以回车结束" << endl;
	cin >> i;
	if (i == 2) goto s1;
s2: cout << "请输入被减矩阵的行数，并以回车结束" << endl;
	cin >> r;
	cout << "请输入被减矩阵的列数，并以回车结束" << endl;
	cin >> c;
	Tableau t2(r, c);
	t2.setTableau();
	t2.getTableau();
	cout << "请检查被减矩阵是否输入正确,若正确请输入1，若错误请输入2,并以回车结束" << endl;
	cin >> i;
	if (i == 2) goto s2;
	int a1 = t1.geta();
	int a2 = t2.geta();
	int b1 = t1.getb();
	int b2 = t2.getb();
	if (a1 == a2 && b1 == b2) {								/*这里与加法一样先判断两个矩阵
															   是否为同型矩阵，若是继续计算
															   若不是提醒用户输入错误*/
		Tableau t3(a1, b1);
		for (int i1 = 0; i1 < a1; i1++) {
			for (int i2 = 0; i2 < b1; i2++) {
				t3.sz[i1][i2] = t1.sz[i1][i2] - t2.sz[i1][i2];
			}
		}
		cout << "矩阵减法计算完毕" << endl;
		t3.getTableau();
		return;
	}
	else {
		cout << "您所输入的矩阵并非同型矩阵，不能进行矩阵减法" << endl;
		return;
	}
}

//计算行列式并返回计算结果
MElem calculateDet(int n, MElem** d)
{
	MElem sum = 0;
	/*这里定义计算子行列式的递归函数函数*/
	if (n == 1)
	{
		return d[0][0];
	}//n=1和n=2时的递归出口
	else if (n == 2)
	{
		return  d[0][0] * d[1][1] - d[0][1] * d[1][0];
	}
	else //if (n > 2)
	{
		MElem***s = new MElem**[n];			//这里定义一个三维数组来存放行列式（二维数组）
		for (int j = 0; j < n; j++)
		{
			//每一次det都会被初始化为零
			 //这里将行列式从第一行展开用for循环创造n个（n-1）阶行列式
			MElem** d1 = new MElem*[n - 1];   //这里创造一个子数组d1暂时储存（n-1）阶数组
			for (int i = 0; i < (n - 1); i++)
			{
				d1[i] = new MElem[n - 1];
			}
			for (int y = 0; y < (n - 1); y++)
			{
				for (int z = 0; z < (n - 1); ++z)           //用j表示当前选择的展开位置a[0][j] 
				{
					if (z < j) d1[y][z] = d[y + 1][z];
					if (z >= j) d1[y][z] = d[y + 1][z + 1];

				}


			}
			s[j] = d1;
			//供测试用
			/*for (int x1 = 0; x1 < n - 1; x1++)
			{
				cout << endl;
				for (int x2 = 0; x2 < n - 1; x2++)
				{
					cout << d1[x1][x2] << " ";
				}
			}*/

			//供测试用
			//cout << "系数为" << d[0][j] << endl;		//这里遇到问题 4阶行列式的系数没有被计算导致错误

													//问题在于计算4阶行列式时将其展开为三阶行列式后第二个三阶行列式的二阶中的det的值为第一个三阶行列式的值
			int index;
			if (j % 2)//j是奇数
				index = -1;//-1的奇数次方是-1
			else
				index = 1;
			sum = sum + index*d[0][j] * calculateDet((n - 1), d1);

			//供测试用
			//cout << "sum " << sum << endl;

		}

		for (int i1 = 0; i1 < n; i1++)//删除动态数组s
		{
			for (int i2 = 0; i2 < n - 1; i2++)
			{
				delete[] s[i1][i2];
			}
			delete[] s[i1];
		}
		delete[] s;
		return sum;
	}

}

//调用计算行列式的函数
void getDet()
{
	cout << "下面开始计算矩阵的行列式" << endl;
	int i; int n;
s1: cout << "请输入矩阵的阶数，并以回车结束" << endl;
	cin >> n;
	Tableau t1(n, n);
	t1.setTableau();
	t1.getTableau();
	cout << "请检查矩阵是否输入正确,若正确请输入1，若错误请输入2,并以回车结束" << endl;
	cin >> i;
	if (i == 2) goto s1;
	MElem** ss = t1.sz;
	cout << "该矩阵的行列式的值为" << calculateDet(n, ss) << endl;
}

//原来的矩阵转置函数，有问题
/*
Tableau Transposition(int r ,int c,MElem** T)//这个函数以对象为参数计算并将其转置
{

	MElem** t = new MElem*[r];   //这里创造一个子数组t用来存储矩阵T的转置
	for (int i = 0; i < r; i++)
	{
		t[i] =  new MElem[c];
	}

	for (int r1 = 0; r1 < r; r1++)					   //先将矩阵按原顺序储存到临时数组中
	{
		for (int c1 = 0; c1 < c; c1++)
		{
			t[c1][r1] = T[r1][c1];
		}
	}
	for (int t1 = 0; t1 < r; t1++)
	{
		cout << endl;
		for (int t2 = 0; t2 < c; t2++)
		{
			cout << t[t1][t2]<<" ";
		}
	}
	Tableau t1(r,c);
	return t1;
}
*/

//返回t矩阵的转置矩阵
Tableau return_trans(const Tableau &t)
{
	Tableau matrix2(t.getb(), t.geta());
	for (int i = 0; i < t.geta(); i++)
	{
		for (int j = 0; j < t.getb(); j++)
			matrix2.sz[j][i] = t.sz[i][j];
	}
	return matrix2;
}

//这个函数用让用户输入矩阵并调用函数return_trans来进行矩阵的转置
void getTransposition()
{
	int r; int c; int cin1;
s1:cout << "请输入矩阵的行数" << endl;
	cin >> r;
	cout << "请输入矩阵的列数" << endl;
	cin >> c;
	Tableau t1(r, c);
	t1.setTableau();
	t1.getTableau();
	cout << "请检查矩阵是否正确，若正确请输入1，否则请输入2，并以回车结束" << endl;
	cin >> cin1;
	if (cin1 == 2)
	{
		goto s1;
	}
	else
	{
		//int a1 = t1.geta();
		//int b1 = t1.getb();
		//t1=Transposition(a1,b1,t1.sz);//将函数返回的转置后的矩阵对象赋给t1
		//Tableau matrix2(return_trans(t1));
		Tableau matrix2 = return_trans(t1);
		matrix2.getTableau();
	}
}

//矩阵乘法
Tableau mul()
{
	cout << "下面开始计算矩阵的乘法" << endl;
	int r; int c; int i;
s1: cout << "请输入矩阵1的行数，并以回车结束" << endl;
	cin >> r;
	cout << "请输入矩阵1的列数，并以回车结束" << endl;
	cin >> c;
	Tableau t1(r, c);									//先构造两个矩阵实例并指导用户输入
	t1.setTableau();
	t1.getTableau();
	cout << "请检查矩阵1是否输入正确,若正确请输入1，若错误请输入2,并以回车结束" << endl;
	cin >> i;
	if (i == 2) goto s1;								/*这里用goto语句实现允许用户检查错误
													   并改正的功能*/
s2: cout << "请输入矩阵2的行数，并以回车结束" << endl;
	cin >> r;
	cout << "请输入矩阵2的列数，并以回车结束" << endl;
	cin >> c;
	Tableau t2(r, c);
	t2.setTableau();
	t2.getTableau();
	cout << "请检查矩阵2是否输入正确,若正确请输入1，若错误请输入2,并以回车结束" << endl;
	cin >> i;
	if (i == 2) goto s2;
	/*输入完毕后先判断两个矩阵是否能进行乘法，如果是继续乘法，如果不
	是那么提醒用户输入错误*/
	int a1 = t1.geta();
	int b1 = t1.getb();
	int a2 = t2.geta();
	int b2 = t2.getb();
	if (b1 == a2)
	{
		Tableau t3(a1, b2);
		MElem** t = new MElem*[a1];   //这里创造一个子数组t用来存储乘法的积
		for (int i = 0; i < a1; i++)
		{
			t[i] = new MElem[b2];
		}

		for (int i1 = 0; i1 < a1; i1++)
		{
			for (int i2 = 0; i2 < b2; i2++)
			{
				MElem sum = 0;
				for (int i3 = 0; i3 < b1; i3++)
				{

					sum += t1.sz[i1][i3] * t2.sz[i3][i2];
				}
				t[i1][i2] = sum;
			}
		}
		for (int xx = 0; xx < a1; xx++)
		{
			for (int yy = 0; yy < b2; yy++)
			{
				t3.sz[xx][yy] = t[xx][yy];
			}
		}
		for (int ii = 0; ii < a1; ii++)
		{
			delete[] t[ii];//删除数组t
		}
		delete[] t;
		t3.getTableau();
		return t3;
	}

	else {
		cout << "您所输入的矩阵不能进行矩阵乘法" << endl;
		Tableau t(0, 0);
		return t;
	}
}

//让用户输入矩阵，并计算逆阵
void getinverse()
{
	cout << "下面开始计算矩阵的逆阵" << endl;
	int i;
	int m; //方阵的阶数
s1: cout << "请输入矩阵的阶数，并以回车结束" << endl;
	cin >> m;
	Tableau t1(m, m);
	t1.setTableau();
	t1.getTableau();
	cout << "请检查矩阵是否输入正确,若正确请输入1，若错误请输入2,并以回车结束" << endl;
	cin >> i;
	if (i == 2) goto s1;
	MElem **d = t1.sz;
	MElem det = calculateDet(m, d);
	if (det == 0)
		cout << "此矩阵不是可逆阵，不能进行求逆运算" << endl;
	else
	{
		Tableau e = create_I(m);//构造一个同阶的单位阵e
		trans_to_I(t1, e);//用初等变换法求逆
		cout << "逆阵为" << endl;
		e.getTableau();
	}

	//原来的计算逆阵(伴随矩阵法)代码，有问题
	//Tableau t2(m, m);//此对象用于存放逆阵
	//for (int r1 = 0; r1 < m; r1++)//m n 表示当前计算的伴随矩阵A*中的元素A*[m][n]
	//{
	   // for (int c1 = 0; c1 < m; c1++)
	   // {
	   //	 MElem** d1 = new MElem*[m-1];   //这里创造一个子数组d1暂时储存（m-1）阶数组
	   //	 for (int i = 0; i < (m - 1); i++)
	   //	 {
	   //		 d1[i] = new MElem[m-1];
	   //	 }
	   //	 for (int r2 = 0; r2 < m-1; r2++)
	   //	 {
	   //		 for (int c2 = 0; c2 < m-1; c2++)
	   //		 {
	   //			 if (r2 < r1&&c2 < c1) d1[r2][c2] = d[r2][c2];
	   //			 if (r2 < r1&&c2 >= c1) d1[r2][c2] = d[r2][c2+1];
	   //			 if (r2 >= r1&&c2 < c1) d1[r2][c2] = d[r2+1][c2];
	   //			 if (r2 >= r1 && c2 >= c1) d1[r2][c2] = d[r2+1][c2+1];
	   //			 
	   //		 }
	   //	 }
	   //	 MElem Detd1 = calculateDet(m - 1, d1);//这里a[r1][c1]的余子式以及算好下面计算a*[r1][c1]
	   //	 t2.sz[c1][r1] = pow(-1, (r1 + c1))*d[r1][c1] * Detd1;
	   //	 for (int i = 0; i < m-1; i++)//删除数组d1
	   //		delete[] d1[i];
	   //	 delete[] d1;//此次循环结束时释放分配给d1的内存
	   // }
	//}
	//cout << "原矩阵行列式为" << det << endl;
	//cout << "伴随矩阵为" << endl;
	//t2.getTableau();//输出伴随矩阵
	//for (int r = 0; r < m; r++)//使伴随矩阵中每一个元素除以原矩阵的行列式值得到逆阵
	//{
	   // for (int c = 0; c < m; c++)
	   // {
	   //	 t2.sz[r][c] = t2.sz[r][c] / det;
	   // }
	//}
	//cout << "逆阵为" << endl;
	//t2.getTableau();
}

///----初等行变换----

//把下标第i行加到第j行
void Tableau::add_i_to_j(int i, int j)
{
	for (int x = 0; x < b; x++)
	{
		sz[j][x] = sz[j][x] + sz[i][x];
	}
}
//下标第i行变成k倍
void Tableau::row_i_multiple_k(int i, MElem k)
{
	for (int x = 0; x < b; x++)
	{
		sz[i][x] = sz[i][x] * k;
	}
}
//把下标第i行乘k加到第j行
void Tableau::add_ki_to_j(int i, MElem k, int j)
{
	for (int x = 0; x < b; x++)
	{
		sz[j][x] = sz[j][x] + k * sz[i][x];
	}
}
//交换下标第i行和第j行
void Tableau::swap_i_j(int i, int j)
{
	for (int x = 0; x < b; x++)
	{
		MElem temp = sz[i][x];
		sz[i][x] = sz[j][x];
		sz[j][x] = temp;
	}
}

//把t化为单位阵，单位阵e就变成了逆阵
//必须保证t是可逆阵
void trans_to_I(Tableau &t, Tableau &e)
{
	//矩阵的每一列
	//now_col表示当前列下标
	int k = 0;
	for (int now_col = 0; now_col < t.getb(); now_col++)
	{
		col_i_k_th(now_col, k, t, e);
		k++;
	}
}

//将t矩阵下标第i列的下标第k个元素化为1，其他元素化为0
//对e矩阵做同样的变换
//必须保证t是可逆阵
void col_i_k_th(int i, int k, Tableau &t, Tableau &e)
{
	int a = t.geta();
	int b = t.getb();

	if (t.sz[k][i] == 0)//若该位置为0,则做对换
	{
		for (int x = k + 1; x < a; x++)
		{
			if (t.sz[x][i] != 0)
			{
				t.swap_i_j(x, k);
				e.swap_i_j(x, k);
				break;
			}
		}
	}

	MElem ratio = 1 / t.sz[k][i];//做倍乘变换是要乘的因子
	t.row_i_multiple_k(k, ratio);//化为1
	e.row_i_multiple_k(k, ratio);

	for (int x = 0; x < a; x++)
	{
		if (x != k)
		{
			MElem factor = -t.sz[x][i];//做倍加行变换时要乘的因子
			t.add_ki_to_j(k, factor, x);
			e.add_ki_to_j(k, factor, x);
		}
	}
}

//构造并返回一个n阶单位阵
Tableau create_I(int n)
{
	Tableau e(n, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				e.sz[i][j] = 1;
			else
				e.sz[i][j] = 0;
		}
	}
	return e;
}

//调用矩阵运算的函数
void calcu_matrix()
{
	while (true)
	{
		cout << "--------------------------------------------" << endl;
		cout << "请通过输入指令选择要执行的操作" << endl;
		cout << "1.加法 2.减法 3.乘法 4.计算行列式 5.转置 6.求逆" << endl;
		cout << "cls - 清屏 quit - 退出矩阵运算模式" << endl;
		cout << ">>>";
		string str;
		cin >> str;
		if (str == "1")
			add();//调用加法函数
		else if (str == "2")
			subtract();//调用减法函数
		else if (str == "3")
			mul();//调用乘法函数
		else if (str == "4")
			getDet();//调用行列式计算函数
		else if (str == "5")
			getTransposition();//调用转置函数
		else if (str == "6")
			getinverse();//调用求逆函数
		else if (str == "cls")
			system("cls");
		else if (str == "quit")
			break;
		else
			cout << "[错误]无法识别的指令" << endl;
	}
}
