//切换主题的实现 by 朱华彬
#include "pch.h"
#include "Theme.h"
using namespace std;

void theme_mode()
{
	while (true)
	{
		cout << "[指令列表]输入相应的指令即可切换主题，输入quit退出主题切换模式\n\n";
		cout << "----------亮色主题----------\n\n";
		cout << "0 = 蓝色\t1 = 绿色\n";
		cout << "2 = 紫色\t3 = 黄色\n";
		cout << "4 = 红色\t5 = 黑色\n";
		cout << endl;
		cout << "----------暗色主题----------\n\n";
		cout << "a = 黑色\tb = 灰色\n";
		cout << "c = 灰白色\n";
		cout << endl << ">>>";
		string str;
		cin >> str;
		if (str == "0")
		{
			system("color f1");
			cout << "[系统提示]主题切换成功\n\n";
			return;
		}
		else if (str == "1")
		{
			system("color f2");
			cout << "[系统提示]主题切换成功\n\n";
			return;
		}
		else if (str == "2")
		{
			system("color f5");
			cout << "[系统提示]主题切换成功\n\n";
			return;
		}
		else if (str == "3")
		{
			system("color f6");
			cout << "[系统提示]主题切换成功\n\n";
			return;
		}
		else if (str == "4")
		{
			system("color f4");
			cout << "[系统提示]主题切换成功\n\n";
			return;
		}
		else if (str == "5")
		{
			system("color f0");
			cout << "[系统提示]主题切换成功\n\n";
			return;
		}
		else if (str == "a")
		{
			system("color 0f");
			cout << "[系统提示]主题切换成功\n\n";
			return;
		}
		else if (str == "b")
		{
			system("color 8f");
			cout << "[系统提示]主题切换成功\n\n";
			return;
		}
		else if (str == "c")
		{
			system("color 70");
			cout << "[系统提示]主题切换成功\n\n";
			return;
		}
		else if (str == "quit")
		{
			cout << "[系统提示]已退出主题切换模式\n\n";
			return;
		}
		else
		{
			cout << "[错误]无法识别的指令\n\n";
		}
	}
}