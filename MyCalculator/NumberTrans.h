//数制和编码转换 头文件
//by 马骁
#pragma once
#include <string>

//这个函数用来将字符串中的小写字母转换为大写(16进制输出时会用到)
void mytoupper(std::string& s);
//数制转换
void trans1();
//十进制数转bcd码
void trans2();
//bcd码转十进制
void trans3();
//通过输入指令来调用各种转换的函数
void my_trans_func();