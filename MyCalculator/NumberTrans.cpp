//数制和编码转换的实现
//by 马骁

#include "pch.h"
#include <iostream>
#include<cstdio>
#include<bitset>
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include "NumberTrans.h"
using namespace std;
//这个函数用来将字符串中的小写字母转换为大写(16进制输出时会用到)
void mytoupper(string& s)
{
	int len = s.size();
	for (int i = 0; i < len; i++)
	{
		if (s[i] >= 'a'&&s[i] <= 'z')//如果s[i]是小写字母，那么将它的Ascii码-32转为小写字母
		{
			s[i] -= 32;//-32转换为大写
			//s[i]=s[i]-'a'+'A';
		}
	}
}

//数制转换
void trans1()
{
	cout << "下面进行进制转换。首先，请确定转换前的进制" << endl;
	cout << "1:十进制" << "2.二进制" << "3.八进制" << "4.十六进制" << endl;
	int n;
	cin >> n;
	switch (n)
	{
	case(1)://case(1)是将十进制的数转换为其他进制的数,将十进制的数分为整数部分和小数部分分别转换
	{
		double num;
		cout << "请输入要转换的数(如10.88)" << endl;
		cin >> num;//输入双精度浮点数a
		int z = (int)floor(num);//整数部分保存在整型z中
		double x = num - z;//小数部分保存在浮点数x中
		cout << "请选择要转换到的进制" << endl;
		cout << "请输入要选择的进制前的序号并以回车结束" << endl;
		cout << endl << "1.二进制" << "2.八进制" << "3.十六进制" << endl;
		int y;
		cin >> y;

		switch (y)
		{
		case(1)://十进制转换为二进制的情况
		{
			char  str1[50];//str1用来存放二进制的整数部分
			char str2[12] = ".          ";//str2用来存放二进制的小数部分
			string str;//str用来存放完整的二进制数
			_itoa_s(z, str1, 2);//得到str1
			for (int i = 1; i < 11; i++)//得到str2
			{
				double t = 2 * x;
				if (t >= 1)
				{
					x = t - 1;
					str2[i] = '1';
				}
				else
				{
					x = t;
					str2[i] = '0';
				}
			}
			str = str1;
			str = str + str2;
			cout << "转换后的二进制数为:" << str << endl;
			break;
		}
		case(2)://十进制转换为八进制的情况
		{
			char oct[9] = "01234567";//声明一个八进制的字母表
			char  str1[50];//str1用来存放八进制的整数部分
			char str2[12] = ".          ";//str2用来存放精度为十位的八进制的小数部分
			string str;//str用来存放完整的八进制数
			_itoa_s(z, str1, 8);//得到str1

			for (int i = 1; i < 11; i++)//得到str2
			{
				double t = 8 * x;
				if (t >= 1)
				{
					int p = (int)floor(t);//p为x乘8后得到的整数部分
					x = t - p;//x为x乘八后剩余的小数部分
					str2[i] = oct[p];
				}
				else
				{
					x = t;
					str2[i] = '0';
				}
			}


			str = str1;
			str = str + str2;
			cout << "转换后的八进制数为" << str;
			break;
		}
		case(3)://十进制转十六进制
		{
			char oct[17] = "0123456789abcdef";//声明一个十六进制的字母表
			char  str1[50];//str1用来存放十六进制的整数部分
			char str2[12] = ".          ";//str2用来存放精度为十位的十六进制的小数部分
			string str;//str用来存放完整的十六进制数
			_itoa_s(z, str1, 16);//得到str1

			for (int i = 1; i < 11; i++)//得到str2
			{
				double t = 16 * x;
				if (t >= 1)
				{
					int p = (int)floor(t);//p为x乘16后得到的整数部分
					x = t - p;//x为x乘八后剩余的小数部分
					str2[i] = oct[p];
				}
				else
				{
					x = t;
					str2[i] = '0';
				}
			}


			str = str1;
			str = str + str2;
			mytoupper(str);
			cout << "转换后的十六进制数为" << str << endl;
			break;
		}

		}
		break;

	}
	case(2)://case（2）是将二进制数转换为其他进制的数
	{
		cout << "请输入二进制数，并以回车结束（如：1011.01）" << endl;
		string str;//由于c++不支持直接输入二进制的数，我用字符串储存用户输入的二进制数再通过for循环将他转换为10进制的数
		cin >> str;//之后再将得到的10进制数转换为其他进制的数
		double sum = 0;//先将二进制数转换为10进制数
		int size = str.size();//获取字符串长度
		string str1;//str1用于保存二进制整数部分
		string str2;//str2用于保存二进制小数部分

		int point = 0;//point用于标记小数点的位置
		for (int i = 0; i < size; i++)//寻找小数点并将其位置赋给point
		{
			if (str[i] == '.')
			{
				point = i;
				break;
			}
			else if (i == (size - 1))str1 = str;
			else continue;
		}

		if (point > 0)
		{
			for (int q = 0; q < size; q++)//以point为分界点将str分为两部分
			{
				if (q < point) str1 += str[q];
				else if (q > point) str2 += str[q];
				else continue;
			}
		}
		else str1 = str;
		int size1 = str1.size();//size1用来保存str1的长度
		int size2 = str2.size();//size2用来保存str2的长度
		double sum1 = 0; double sum2 = 0;//sum1和sum2分别用来保存整数部分和小数部分的十进制的值
		for (int i = 0; i < size1; i++)//用for循环结构来计算整数部分的值
		{
			if (str[i] == '1')//判断字符串中的某一位是否为1，如果是则sum=sum+2^i
			{
				sum1 = sum1 + pow(2, (size1 - i - 1));


			}

		}
		for (int t = 0; t < size2; t++)
		{
			if (str2[t] == '1')
			{
				sum2 += pow(2, (-(t + 1)));
			}
		}

		sum = sum1 + sum2;
		int z = (int)sum;//z为整数部分
		double x = sum - z;//x为小数部分
		cout << "请选择要转换到的进制" << endl;
		cout << "1:十进制" << "2.八进制" << "3.十六进制" << endl;
		int u;
		cin >> u;
		switch (u)
		{

		case(1)://这是二进制转换为10进制的部分
		{
			cout << "转换后的十进制数为:" << sum << endl;//将二进制数转换为十进制数直接输出sum
			break;
		}

		case(2)://这是二进制转换为8进制的部分
		{

			char buffer[50];//缓冲字符串来接受double型的sum
			sprintf_s(buffer, "%f", sum);//将sum转换为字符串存在buffer中
			char oct[9] = "01234567";//声明一个八进制的字母表
			char  str1[50];//str1用来存放八进制的整数部分
			char str2[12] = ".          ";//str2用来存放精度为十位的八进制的小数部分
			_itoa_s((int)sum, str1, 8);//得到str1

			for (int i = 1; i < 11; i++)//得到str2
			{
				double t = 8 * x;
				if (t >= 1)
				{
					int p = (int)floor(t);//p为x乘8后得到的整数部分
					x = t - p;//x为x乘八后剩余的小数部分
					str2[i] = oct[p];
				}
				else
				{
					x = t;
					str2[i] = '0';
				}
			}
			str = str1;
			str = str + str2;
			cout << "转换后的八进制数为" << str << endl;
			break;
		}
		case(3)://这是二进制转换为16进制的部分
		{
			char oct[17] = "0123456789abcdef";//声明一个十六进制的字母表
			char  str1[50];//str1用来存放十六进制的整数部分
			char str2[12] = ".          ";//str2用来存放精度为十位的十六进制的小数部分
			string str;//str用来存放完整的十六进制数
			_itoa_s(z, str1, 16);//得到str1

			for (int i = 1; i < 11; i++)//得到str2
			{
				double t = 16 * x;
				if (t >= 1)
				{
					int p = (int)floor(t);//p为x乘16后得到的整数部分
					x = t - p;//x为x乘八后剩余的小数部分
					str2[i] = oct[p];
				}
				else
				{
					x = t;
					str2[i] = '0';
				}
			}
			str = str1;
			str = str + str2;
			mytoupper(str);
			cout << "转换后的十六进制数为" << str << endl;
			break;
		}

		}
		break;
	}
	case(3)://case(3)是将八进制的数转换为其他进制的数
	{
		cout << "请输入八进制数，并以回车结束（如：7.34）" << endl;
		string str;//用字符串储存用户输入的二进制数再通过for循环将他转换为10进制的数
		cin >> str;//之后再将得到的10进制数转换为其他进制的数
		double sum = 0;//先将二进制数转换为10进制数
		int size = str.size();//获取字符串长度
		string str1;//str1用于保存二进制整数部分
		string str2;//str2用于保存二进制小数部分
		char oct[9] = "01234567";//声明一个八进制的字母表
		int point = 0;//point用于标记小数点的位置
		for (int i = 0; i < size; i++)//寻找小数点并将其位置赋给point
		{
			if (str[i] == '.')
			{
				point = i;
				break;
			}
			else if (i == (size - 1))str1 = str;
			else continue;
		}
		if (point > 0)
		{
			for (int q = 0; q < size; q++)//以point为分界点将str分为两部分
			{
				if (q < point) str1 += str[q];
				else if (q > point) str2 += str[q];
				else continue;
			}
		}
		else str1 = str;
		int size1 = str1.size();//size1用来保存str1的长度
		int size2 = str2.size();//size2用来保存str2的长度
		double sum1 = 0; double sum2 = 0;//sum1和sum2分别用来保存整数部分和小数部分的十进制的值
		for (int i = 0; i < size1; i++)//用for循环结构来计算整数部分的值
		{
			for (int x = 0; x < 8; x++)//通过与字母表比较来匹配字符串中的某一位
			{
				if (str[i] == oct[x])
				{
					sum1 = sum1 + x * pow(8, (size1 - i - 1));
				}
			}

		}
		for (int t = 0; t < size2; t++)//计算小数部分的值
		{
			for (int x = 0; x < 8; x++)
			{

				if (str2[t] == oct[x])
				{
					sum2 += x * pow(8, (-(t + 1)));
				}
			}
		}
		sum = sum1 + sum2;
		int z = (int)sum;//z为整数部分
		double x = sum - z;//x为小数部分
		cout << "请选择要转换到的进制" << endl;
		cout << "1:十进制" << "2.二进制" << "3.十六进制" << endl;
		int u;
		cin >> u;
		switch (u)
		{

		case(1)://这是8进制转换为10进制的部分
		{
			cout << "转换后的十进制数为:" << sum << endl;//将二进制数转换为十进制数直接输出sum
			break;
		}

		case(2)://这是8进制转换为2进制的部分
		{

			char buffer[50];//缓冲字符串来接受double型的sum
			sprintf_s(buffer, "%f", sum);//将sum转换为字符串存在buffer中
			char  str1[50];//str1用来存放八进制的整数部分
			char str2[12] = ".          ";//str2用来存放精度为十位的八进制的小数部分
			_itoa_s((int)sum, str1, 2);//得到str1

			for (int i = 1; i < 11; i++)//得到str2
			{
				double t = 2 * x;
				if (t >= 1)
				{
					int p = (int)floor(t);//p为x乘2后得到的整数部分
					x = t - p;//x为x乘八后剩余的小数部分
					str2[i] = '1';
				}
				else
				{
					x = t;
					str2[i] = '0';
				}
			}
			str = str1;
			str = str + str2;
			cout << "转换后的二进制数为" << str << endl;
			break;
		}
		case(3)://这是8进制转换为16进制的部分
		{
			char oct[17] = "0123456789abcdef";//声明一个十六进制的字母表
			char  str1[50];//str1用来存放十六进制的整数部分
			char str2[12] = ".          ";//str2用来存放精度为十位的十六进制的小数部分
			string str;//str用来存放完整的十六进制数
			_itoa_s(z, str1, 16);//得到str1

			for (int i = 1; i < 11; i++)//得到str2
			{
				double t = 16 * x;
				if (t >= 1)
				{
					int p = (int)floor(t);//p为x乘16后得到的整数部分
					x = t - p;//x为x乘八后剩余的小数部分
					str2[i] = oct[p];
				}
				else
				{
					x = t;
					str2[i] = '0';
				}
			}
			str = str1;
			str = str + str2;
			mytoupper(str);
			cout << "转换后的十六进制数为" << str << endl;
			break;
		}

		}
		break;
	}
	case(4)://case(4)是将十六进制的数转换为其他进制的数
	{
		cout << "请输入十六进制数如（AB.2A3B），并以回车结束" << endl;
		string str;//用字符串储存用户输入的十六进制数再通过for循环将他转换为10进制的数
		cin >> str;//之后再将得到的10进制数转换为其他进制的数
		double sum = 0;//先将十六进制数转换为10进制数
		int size = str.size();//获取字符串长度
		string str1;//str1用于保存十六进制整数部分
		string str2;//str2用于保存十六进制小数部分
		char hex[17] = "0123456789ABCDEF";//声明一个十六进制的字母表
		int point = 0;//point用于标记小数点的位置
		for (int i = 0; i < size; i++)//寻找小数点并将其位置赋给point
		{
			if (str[i] == '.')
			{
				point = i;
				break;
			}
			else if (i == (size - 1))str1 = str;
			else continue;
		}

		if (point > 0)
		{
			for (int q = 0; q < size; q++)//以point为分界点将str分为两部分
			{
				if (q < point) str1 += str[q];
				else if (q > point) str2 += str[q];
				else continue;
			}
		}
		else str1 = str;
		int size1 = str1.size();//size1用来保存str1的长度
		int size2 = str2.size();//size2用来保存str2的长度
		double sum1 = 0; double sum2 = 0;//sum1和sum2分别用来保存整数部分和小数部分的十进制的值
		for (int i = 0; i < size1; i++)//用for循环结构来计算整数部分的值
		{
			for (int x = 0; x < 16; x++)//通过与字母表比较来匹配字符串中的某一位
			{
				if (str[i] == hex[x])
				{
					sum1 = sum1 + x * pow(16, (size1 - i - 1));

				}
			}

		}
		for (int t = 0; t < size2; t++)//计算小数部分的值
		{
			for (int x = 0; x < 16; x++)
			{

				if (str2[t] == hex[x])
				{
					sum2 += x * pow(16, (-(t + 1)));
				}
			}
		}

		sum = sum1 + sum2;
		int z = (int)sum;//z为整数部分
		double x = sum - z;//x为小数部
		cout << "请选择要转换到的进制" << endl;
		cout << "1:十进制" << "2.八进制" << "3.二进制" << endl;
		int u;
		cin >> u;
		switch (u)
		{

		case(1)://这是二进制转换为10进制的部分
		{
			cout << "转换后的十进制数为:" << sum << endl;//将二进制数转换为十进制数直接输出sum
			break;
		}

		case(2)://这是十六进制转换为8进制的部分
		{

			char buffer[50];//缓冲字符串来接受double型的sum
			sprintf_s(buffer, "%f", sum);//将sum转换为字符串存在buffer中
			char oct[9] = "01234567";//声明一个八进制的字母表
			char  str1[50];//str1用来存放八进制的整数部分
			char str2[12] = ".          ";//str2用来存放精度为十位的八进制的小数部分
			_itoa_s((int)sum, str1, 8);//得到str1

			for (int i = 1; i < 11; i++)//得到str2
			{
				double t = 8 * x;
				if (t >= 1)
				{
					int p = (int)floor(t);//p为x乘8后得到的整数部分
					x = t - p;//x为x乘八后剩余的小数部分
					str2[i] = oct[p];
				}
				else
				{
					x = t;
					str2[i] = '0';
				}
			}
			str = str1;
			str = str + str2;
			cout << "转换后的八进制数为" << str << endl;
			break;
		}
		case(3)://这是十六进制转换为2进制的部分
		{
			char  str1[50];//str1用来存放十六进制的整数部分
			char str2[12] = ".          ";//str2用来存放精度为十位的十六进制的小数部分
			string str;//str用来存放完整的十六进制数
			_itoa_s(z, str1, 2);//得到str1

			for (int i = 1; i < 11; i++)//得到str2
			{
				double t = 2 * x;
				if (t >= 1)
				{
					int p = (int)floor(t);//p为x乘16后得到的整数部分
					x = t - p;//x为x乘八后剩余的小数部分
					str2[i] = '1';
				}
				else
				{
					x = t;
					str2[i] = '0';
				}
			}
			str = str1;
			str = str + str2;
			mytoupper(str);
			cout << "转换后的二进制数为" << str << endl;
			break;
		}

		}
		break;
	}
	}
}

//十进制数转bcd码
void trans2()
{
	char Dec[11] = "0123456789";
	//声明一个十进制的字母表
	//声明一个字符串数组用来保存0-9的BCD码

	cout << "请输入十进制数如（10.88）" << endl;
	string str, str1, str2;
	/*
	 *str用来接收用户输入的二进制数
	 *str1用来保存整数部分
	 *str2用来保存小数部分
	 */
	cin >> str;
	//输入10进制数str
	int size = str.size();
	//获取字符长度
	int point = 0;//point用于标记小数点的位置
	for (int i = 0; i < size; i++)//寻找小数点并将其位置赋给point
	{
		if (str[i] == '.')
		{
			point = i;
			break;
		}
		else if (i == (size - 1))str1 = str;
		else continue;
	}

	if (point > 0)
	{
		for (int q = 0; q < size; q++)//以point为分界点将str分为两部分
		{
			if (q < point) str1 += str[q];
			else if (q > point) str2 += str[q];
			else continue;
		}
	}
	else str1 = str;
	int size1 = str1.size();//size1用来保存str1的长度
	int size2 = str2.size();//size2用来保存str2的长度
	cout << "请选择需要转换的BCD码" << endl;
	cout << "1.8421BCD码，2.5421BCD码，3.2421BCD码，4.余3码" << endl;
	int s;
	cin >> s;
	switch (s)
	{
	case(1):
	{
		string Decb[10] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001" };
		//声明一个字符串数组用来保存0-9的BCD码
		string out, out1, out2;
		for (int i = 0; i < size1; i++)
		{
			for (int y = 0; y < 10; y++)
				if (str1[i] == Dec[y])
				{
					out1 += Decb[y];//将对应的BCD码输入out1中
				}
		}
		for (int i = 0; i < size2; i++)
		{
			for (int y = 0; y < 10; y++)
				if (str2[i] == Dec[y])
				{
					out2 += Decb[y];//将对应的BCD码输入out1中
				}
		}
		out = out1 + '.' + out2;
		cout << "转换后的bcd码为：" << out << endl;
		break;
	}
	case(2)://5421BCD码
	{
		string Decb[10] = { "0000","0001","0010","0011","0100","0101","0110","0111","1011","1100" };
		//声明一个字符串数组用来保存0-9的BCD码
		string out, out1, out2;
		for (int i = 0; i < size1; i++)
		{
			for (int y = 0; y < 10; y++)
				if (str1[i] == Dec[y])
				{
					out1 += Decb[y];//将对应的BCD码输入out1中
				}
		}
		for (int i = 0; i < size2; i++)
		{
			for (int y = 0; y < 10; y++)
				if (str2[i] == Dec[y])
				{
					out2 += Decb[y];//将对应的BCD码输入out1中
				}
		}
		out = out1 + '.' + out2;
		cout << "转换后的bcd码为：" << out << endl;
		break;
	}
	case(3)://2421BCD码
	{
		string Decb[10] = { "0000","0001","0010","0011","0100","0101","0110","0111","1110","1111" };
		//声明一个字符串数组用来保存0-9的2421BCD码
		string out, out1, out2;
		for (int i = 0; i < size1; i++)
		{
			for (int y = 0; y < 10; y++)
				if (str1[i] == Dec[y])
				{
					out1 += Decb[y];//将对应的BCD码输入out1中
				}
		}
		for (int i = 0; i < size2; i++)
		{
			for (int y = 0; y < 10; y++)
				if (str2[i] == Dec[y])
				{
					out2 += Decb[y];//将对应的BCD码输入out1中
				}
		}
		out = out1 + '.' + out2;
		cout << "转换后的bcd码为：" << out << endl;
		break;
	}
	case(4):
	{
		string Decb[10] = { "0011","0100","0101","0110","0111","1000","1001","1010","1011","1100" };
		//声明一个字符串数组用来保存0-9的余3码
		string out, out1, out2;
		for (int i = 0; i < size1; i++)
		{
			for (int y = 0; y < 10; y++)
				if (str1[i] == Dec[y])
				{
					out1 += Decb[y];//将对应的BCD码输入out1中
				}
		}
		for (int i = 0; i < size2; i++)
		{
			for (int y = 0; y < 10; y++)
				if (str2[i] == Dec[y])
				{
					out2 += Decb[y];//将对应的BCD码输入out1中
				}
		}
		out = out1 + '.' + out2;
		cout << "转换后的bcd码为：" << out << endl;
		break;
	}
	}
}

//bcd码转十进制
void trans3()
{

	cout << "请确认您输入的编码类型" << endl;
	cout << "1.8421BCD码，2.5421BCD码，3.2421BCD码，4.余3码" << endl;
	int s;
	cin >> s;
	char Dec[11] = "0123456789";
	//声明一个十进制的字母表
	//声明一个字符串数组用来保存0-9的BCD码

	cout << "请输入BCD码如（0100.00000100）" << endl;
	string str, str1, str2;
	/*
	 *str用来接收用户输入的二进制数
	 *str1用来保存整数部分
	 *str2用来保存小数部分
	 */
	cin >> str;
	//输入10进制数str
	int size = str.size();
	//获取字符长度
	int point = 0;//point用于标记小数点的位置
	for (int i = 0; i < size; i++)//寻找小数点并将其位置赋给point
	{
		if (str[i] == '.')
		{
			point = i;
			break;
		}
		else if (i == (size - 1))str1 = str;
		else continue;
	}

	if (point > 0)
	{
		for (int q = 0; q < size; q++)//以point为分界点将str分为两部分
		{
			if (q < point) str1 += str[q];
			else if (q > point) str2 += str[q];
			else continue;
		}
	}
	else str1 = str;
	int size1 = str1.size();//size1用来保存str1的长度
	int size2 = str2.size();//size2用来保存str2的长度
	switch (s)
	{
	case(1)://8421BCD
	{
		string Decb[10] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001" };
		//声明一个字符串数组用来保存0-9的BCD码
		double sum = 0, sum1 = 0, sum2 = 0;
		//整数部分
		for (int i = 0; i < size1; i = i + 4)
		{
			int n = size1 / 4;//转换后的十进制数的整数位数
			int q = i / 4;
			string b;//用于保存一位bcd码
			for (int y = i; y < i + 4; y++)
			{
				if (y == i)b = str1[y];
				else b = b + str1[y];
			}
			for (int y = 0; y < 10; y++)
			{
				if (b == Decb[y])
				{
					sum1 += y * pow(10, (n - 1 - q));
				}
			}
		}
		//下面是小数部分

		for (int i = 0; i < size2; i += 4)
		{
			int q = i / 4;
			string b1;//用来保存一位BCD
			for (int y = i; y < i + 4; y++)
			{
				if (y == i)b1 = str2[y];
				else b1 = b1 + str2[y];
			}
			for (int y = 0; y < 10; y++)
				if (b1 == Decb[y])
				{
					sum2 += y * pow(10, -(q + 1));//将对应的BCD码输入out1中
				}
		}
		sum = sum1 + sum2;
		cout << "转换后的十进制数为：" << sum << endl;
		break;
	}
	case(2)://5421BCD码
	{
		string Decb[10] = { "0000","0001","0010","0011","0100","0101","0110","0111","1011","1100" };
		//声明一个字符串数组用来保存0-9的BCD码
		double sum = 0, sum1 = 0, sum2 = 0;
		//整数部分
		for (int i = 0; i < size1; i = i + 4)
		{
			int n = size1 / 4;//转换后的十进制数的整数位数
			int q = i / 4;
			string b;//用于保存一位bcd码
			for (int y = i; y < i + 4; y++)
			{
				if (y == i)b = str1[y];
				else b = b + str1[y];
			}
			for (int y = 0; y < 10; y++)
			{
				if (b == Decb[y])
				{
					sum1 += y * pow(10, (n - 1 - q));
				}
			}
		}
		//下面是小数部分

		for (int i = 0; i < size2; i += 4)
		{
			int q = i / 4;
			string b1;//用来保存一位BCD
			for (int y = i; y < i + 4; y++)
			{
				if (y == i)b1 = str2[y];
				else b1 = b1 + str2[y];
			}
			for (int y = 0; y < 10; y++)
				if (b1 == Decb[y])
				{
					sum2 += y * pow(10, -(q + 1));//将对应的BCD码输入out1中
				}
		}
		sum = sum1 + sum2;
		cout << "转换后的十进制数为：" << sum << endl;
		break;
	}
	case(3)://2421BCD码
	{
		string Decb[10] = { "0000","0001","0010","0011","0100","0101","0110","0111","1110","1111" };
		//声明一个字符串数组用来保存0-9的BCD码
		double sum = 0, sum1 = 0, sum2 = 0;
		//整数部分
		for (int i = 0; i < size1; i = i + 4)
		{
			int n = size1 / 4;//转换后的十进制数的整数位数
			int q = i / 4;
			string b;//用于保存一位bcd码
			for (int y = i; y < i + 4; y++)
			{
				if (y == i)b = str1[y];
				else b = b + str1[y];

			}
			for (int y = 0; y < 10; y++)
			{
				if (b == Decb[y])
				{
					sum1 += y * pow(10, (n - 1 - q));
				}
			}
		}
		//下面是小数部分

		for (int i = 0; i < size2; i += 4)
		{
			int q = i / 4;
			string b1;//用来保存一位BCD
			for (int y = i; y < i + 4; y++)
			{
				if (y == i)b1 = str2[y];
				else b1 = b1 + str2[y];
			}
			for (int y = 0; y < 10; y++)
				if (b1 == Decb[y])
				{
					sum2 += y * pow(10, -(q + 1));//将对应的BCD码输入out1中
				}
		}
		sum = sum1 + sum2;
		cout << "转换后的十进制数为：" << sum << endl;
		break;
	}
	case(4)://余3码
	{
		string Decb[10] = { "0011","0100","0101","0110","0111","1000","1001","1010","1011","1100" };
		//声明一个字符串数组用来保存0-9的BCD码
		double sum = 0, sum1 = 0, sum2 = 0;
		//整数部分
		for (int i = 0; i < size1; i = i + 4)
		{
			int n = size1 / 4;//转换后的十进制数的整数位数
			int q = i / 4;
			string b;//用于保存一位bcd码
			for (int y = i; y < i + 4; y++)
			{
				if (y == i)b = str1[y];
				else b = b + str1[y];
			}
			for (int y = 0; y < 10; y++)
			{
				if (b == Decb[y])
				{
					sum1 += y * pow(10, (n - 1 - q));
				}
			}
		}
		//下面是小数部分

		for (int i = 0; i < size2; i += 4)
		{
			int q = i / 4;
			string b1;//用来保存一位BCD
			for (int y = i; y < i + 4; y++)
			{
				if (y == i)b1 = str2[y];
				else b1 = b1 + str2[y];
			}
			for (int y = 0; y < 10; y++)
				if (b1 == Decb[y])
				{
					sum2 += y * pow(10, -(q + 1));//将对应的BCD码输入out1中
				}
		}
		sum = sum1 + sum2;
		cout << "转换后的十进制数为：" << sum << endl;
		break;
	}
	}
}

//通过输入指令来调用各种转换的函数
void my_trans_func()
{
	while (true)
	{
		string s;
		cout << "请选择需要的功能" << endl;
		cout << "1.进制转换 " << "2.10进制数转BCD码 " << "3.BCD码转十进制数" << endl;
		cout << "cls - 清屏 quit - 退出进制和编码转换模式" << endl;
		cout << ">>>";
		cin >> s;
		if (s == "1")
			trans1();
		else if (s == "2")
			trans2();
		else if (s == "3")
			trans3();
		else if (s == "cls")
			system("cls");
		else if (s == "quit")
			break;
		else
			cout << "[错误]无法识别的指令\n\n";
	}
}