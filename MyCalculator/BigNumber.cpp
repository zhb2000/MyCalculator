#include "pch.h"
#include "BigNumber.h"

///----构造函数----

//无参数的构造函数
BigNumber::BigNumber()
{
	integer = { 0 };
	decimal = { 0 };
	int_len = 0;
	dec_len = 0;
	pos = '0';
}

//参数为int的构造函数
BigNumber::BigNumber(int num)
{
	//将num转换为字符串
	string str;
	stringstream ss;
	ss << num;
	ss >> str;
	BigNumber temp(str);//用字符串构造临时的大数变量
	integer = temp.integer;
	decimal = temp.decimal;
	int_len = temp.int_len;
	dec_len = temp.dec_len;
	pos = temp.pos;
}

//参数为double的构造函数
BigNumber::BigNumber(double num)
{
	if (num == 0)//规避0的问题
	{
		integer = { 0 };
		decimal = { 0 };
		int_len = 0;
		dec_len = 0;
		pos = '0';
	}
	else
	{
		//将num转换为字符串
		string str;
		stringstream ss;
		ss << setiosflags(ios::fixed);//设置为保留小数
		ss << setprecision(6) << num;//保留6位小数
		ss >> str;
		BigNumber temp(str);//用字符串构造临时的大数变量
		temp.clean_zero();//清除多余的0
		integer = temp.integer;
		decimal = temp.decimal;
		int_len = temp.int_len;
		dec_len = temp.dec_len;
		pos = temp.pos;
	}
}

//参数为string的构造函数
BigNumber::BigNumber(const string &num)
{
	//将int_len和dec_len初始化为0
	int_len = 0;
	dec_len = 0;
	int start;//从何处开始遍历字符串num
	//先确定符号
	if (num[0] == '-')//num是负数
	{
		pos = '-';
		start = 1;
	}
	else if (num == "0")//num是0
	{
		pos = '0';
		integer = { 0 };
		decimal = { 0 };
		int_len = 0;
		dec_len = 0;
		return;
	}
	else//num是正数
	{
		pos = '+';
		start = 0;
	}
	
	bool flag = false;//false则录入整数，true则录入小数
	//从start开始遍历字符串，录入每个数字
	for (unsigned int i = start; i < num.length(); i++)
	{
		if (num[i] == '.')
		{
			flag = true;//整数录入完成
			continue;
		}
		if (!flag)//录入整数
		{
			integer.insert(integer.begin(), num[i] - '0');
			int_len++;
		}
		else//录入小数
		{
			decimal.insert(decimal.end(), num[i] - '0');
			dec_len++;
		}
	}
	if (integer.size() == 1 && integer[0] == 0)
		int_len = 0;
	if (decimal.empty())
	{
		decimal.push_back(0);
	}
}

//参数为char *的构造函数
BigNumber::BigNumber(const char * num)
{
	string s(num);
	*this = BigNumber(s);
}

//----成员函数----

//清除多余的0，重新计算长度，顺便修正全0数的符号
void BigNumber::clean_zero()
{
	while (!integer.empty() && integer.back() == 0)
	{
		integer.pop_back();
		if (integer.empty())
			break;
	}
	while (!decimal.empty() && decimal.back() == 0)
	{
		decimal.pop_back();
		if (decimal.empty())
			break;
	}
	//重新计算整数部分的长度
	if (integer.empty())//表明整数部分为0
	{
		integer.push_back(0);
		int_len = 0;
	}
	else
		int_len = integer.size();
	//重新计算小数部分的长度
	if (decimal.empty())//表明小数部分为0
	{
		decimal.push_back(0);
		dec_len = 0;
	}
	else
		dec_len = decimal.size();
	//修正数0的符号
	if (!int_len && !dec_len)
		pos = '0';
}

//保留小数
void BigNumber::accuracy(int precision /*= PRECISION*/)
{
	if (precision >= dec_len)
		return;
	else
	{
		if (decimal[precision] >= 5)
		{
			if (precision != 0)
				decimal[precision - 1]++;
			else //precision == 0
				integer[0]++;
		}
		decimal.erase(decimal.begin() + precision, decimal.end());
		
		for (int i = decimal.size() - 1; i >= 0; i--)//处理小数部分
		{
			if (decimal[i] >= 10)
			{
				decimal[i] -= 10;
				if (i != 0)
					decimal[i - 1]++;
				else //i == 0
					integer[0]++;
			}
			else
				break;
		}//for
		
		for (int i = 0; i < int_len; i++)//处理整数，注意进位后整数可能多一位
		{
			if (integer[i] >= 10)
			{
				integer[i] -= 10;
				if (i != int_len - 1)
					integer[i + 1]++;
				else //i == int_len - 1
				{
					integer.push_back(1);
					int_len++;
				}
			}
			else
				break;
		}
		this->clean_zero();
	}//else
}

//变成相反数
void BigNumber::set_opposite()
{
	if (pos == '+')
		pos = '-';
	else if (pos == '-')
		pos = '+';
}

//移动该数字的小数点
//direction 0为左，1为右，place表示移动几位
void BigNumber::move_dot(bool direction, unsigned int place)
{
	vector<int> temp_int;//临时的整数部分
	vector<int> temp_dec;//临时的小数部分
	//不用移
	if (place == 0)
		return;
	//左移
	if (direction == 0)
	{
		if (place < integer.size())//移动后整数部分不为0，小数部分无需补零
		{
			//构造整数部分
			temp_int.insert(temp_int.end(), integer.begin() + place, integer.end());
			//构造小数部分
			for (int i = place - 1; i >= 0; i--)
			{
				temp_dec.push_back(integer[i]);
			}
			temp_dec.insert(temp_dec.end(), decimal.begin(), decimal.end());
		}
		else//移动后整数部分为0，小数部分可能需要补0
		{
			//构造整数部分
			temp_int.push_back(0);
			//构造小数部分
			temp_dec.insert(temp_dec.end(), place - integer.size(), 0);
			temp_dec.insert(temp_dec.end(), integer.rbegin(), integer.rend());
			temp_dec.insert(temp_dec.end(), decimal.begin(), decimal.end());
		}
	}
	//右移
	else
	{
		if (place < decimal.size())//移动后小数部分不为0，整数部分无需补零
		{
			//构造小数部分
			temp_dec.insert(temp_dec.end(), decimal.begin() + place, decimal.end());
			//构造整数部分
			for (int i = place - 1; i >= 0; i--)
			{
				temp_int.push_back(decimal[i]);
			}
			temp_int.insert(temp_int.end(), integer.begin(), integer.end());
		}
		else//移动后小数部分为0，整数部分可能需要补0
		{
			//构造小数部分
			temp_dec.push_back(0);
			//构造整数部分
			temp_int.insert(temp_int.end(), place - decimal.size(), 0);
			temp_int.insert(temp_int.end(), decimal.rbegin(), decimal.rend());
			temp_int.insert(temp_int.end(), integer.begin(), integer.end());
		}
	}
	//赋值
	integer = temp_int;
	decimal = temp_dec;
	this->clean_zero();//清除0，重新计算长度
}

//返回转换成的整数
long long BigNumber::get_int() const
{
	if (int_len == 0)
		return 0;
	else
	{
		int result = 0;
		int base = 1;
		for (int i = 0; i < int_len; i++)
		{
			result += integer[i] * base;
			base *= 10;
		}
		if (pos == '-')
			result = -result;
		return result;
	}
}

//返回转换成的实数
long double BigNumber::get_real() const
{
	if (this->pos == '0')
		return 0;
	else
	{
		long double result = abs(this->get_int());
		long double base = 0.1;
		for (int i = 0; i < dec_len; i++)
		{
			result += decimal[i] * base;
			base /= 10;
		}
		if (pos == '-')
			result = -result;
		return result;
	}
}

///----友元函数----

//返回绝对值
BigNumber abs(const BigNumber & num)
{
	BigNumber result = num;
	if (result.pos == '-')
		result.pos = '+';
	return result;
}

//比较两个数的绝对值，num1大返回1，num2大返回-1，相等返回0
int cmp_abs(const BigNumber &num1, const BigNumber &num2)
{
	//比较整数位数长度
	if (num1.int_len > num2.int_len)
		return 1;
	else if (num1.int_len < num2.int_len)
		return -1;
	else
	{
		//从高位到低位比较整数部分
		for (int i = num1.int_len - 1; i >= 0; i--)
		{
			if (num1.integer[i] > num2.integer[i])
				return 1;
			if (num1.integer[i] < num2.integer[i])
				return -1;
		}
		
		//开始比较小数部分
		//小数位数长度可能不一样，要补0成一样长
		BigNumber num11 = num1;
		BigNumber num22 = num2;
		
		//通过补0把两个数变成一样长
		//考虑到0的情况，因此用size()来处理长度
		int max_dec_len = max(num11.decimal.size(), num22.decimal.size());//小数应当补到这么长
		num11.decimal.insert(num11.decimal.end(), max_dec_len - num11.decimal.size(), 0);
		num22.decimal.insert(num22.decimal.end(), max_dec_len - num22.decimal.size(), 0);
		//开始比较小数部分
		for (int i = 0; i < max_dec_len; i++)
		{
			if (num11.decimal[i] > num22.decimal[i])
				return 1;
			if (num11.decimal[i] < num22.decimal[i])
				return -1;
		}
		//相等，返回0
		return 0;
	}
}

//返回两数绝对值之和
BigNumber add_abs(const BigNumber &num1, const BigNumber &num2)
{
	BigNumber num11 = num1;//num11将作为返回值
	BigNumber num22 = num2;
	//通过补0把两个数变成一样长
	//考虑到0的情况，因此用size()来处理长度
	int max_int_len = max(num11.integer.size(), num22.integer.size());//整数应当补到这么长
	int max_dec_len = max(num11.decimal.size(), num22.decimal.size());//小数应当补到这么长
	//num11作为结果要多留出一位以防有进位
	num11.integer.insert(num11.integer.end(), max_int_len - num11.integer.size() + 1, 0);
	num11.decimal.insert(num11.decimal.end(), max_dec_len - num11.decimal.size(), 0);
	num22.integer.insert(num22.integer.end(), max_int_len - num22.integer.size(), 0);
	num22.decimal.insert(num22.decimal.end(), max_dec_len - num22.decimal.size(), 0);

	//小数部分相加
	for (int i = max_dec_len - 1; i >= 0; i--)
	{
		num11.decimal[i] += num22.decimal[i];
		if (num11.decimal[i] >= 10)//处理进位
		{
			num11.decimal[i] -= 10;
			if (i != 0)
				num11.decimal[i - 1]++;//进位给前一位小数
			else
				num11.integer[0]++;//进位给第一位整数
		}
	}
	//整数部分相加
	for (int i = 0; i < max_int_len; i++)
	{
		num11.integer[i] += num22.integer[i];
		if (num11.integer[i] >= 10)//处理进位
		{
			num11.integer[i] -= 10;
			num11.integer[i + 1]++;//进位给后一位整数
		}
	}
	num11.clean_zero();//清楚多余的0，并修正全0数的符号
	//修正符号
	if (num11 == BigNumber("0"))
		num11.pos = '0';
	else
		num11.pos = '+';
	return num11;
}

//返回两数绝对值之差（结果非负）
BigNumber minus_abs(const BigNumber & num1, const BigNumber & num2)
{
	BigNumber num11 = num1;//num11将作为返回值
	BigNumber num22 = num2;
	if (cmp_abs(num11, num22) == -1)
		swap(num11, num22);//保证（绝对值）num11-num22够减
	//通过补0把两个数变成一样长
	//考虑到0的情况，因此用size()来处理长度
	int max_int_len = max(num11.integer.size(), num22.integer.size());//整数应当补到这么长
	int max_dec_len = max(num11.decimal.size(), num22.decimal.size());//小数应当补到这么长
	
	num11.integer.insert(num11.integer.end(), max_int_len - num11.integer.size(), 0);
	num11.decimal.insert(num11.decimal.end(), max_dec_len - num11.decimal.size(), 0);
	num22.integer.insert(num22.integer.end(), max_int_len - num22.integer.size(), 0);
	num22.decimal.insert(num22.decimal.end(), max_dec_len - num22.decimal.size(), 0);

	for (int i = max_dec_len - 1; i >= 0; i--)
	{
		num11.decimal[i] -= num22.decimal[i];
		if (num11.decimal[i] < 0)//处理该位不够减的情况
		{
			num11.decimal[i] += 10;
			if (i != 0)
				num11.decimal[i - 1]--;//前一位小数退位
			else
				num11.integer[0]--;//第一位整数退位
		}
	}
	//整数部分相减
	for (int i = 0; i < max_int_len; i++)
	{
		num11.integer[i] -= num22.integer[i];
		if (num11.integer[i] < 0)//处理该位不够减的情况
		{
			num11.integer[i] += 10;
			num11.integer[i + 1]--;//前一位整数退位
		}
	}
	num11.clean_zero();//清楚多余的0，并修正全0数的符号
	//修正符号
	if (num11 == BigNumber("0"))
		num11.pos = '0';
	else
		num11.pos = '+';
	return num11;
}

//返回两数的整除
BigNumber divide_exactly(const BigNumber & num1, const BigNumber & num2)
{
	if (num1 == 0)
		return BigNumber(0);
	else if (num2 == 0)//非法表达式
		return BigNumber();
	else
	{
		BigNumber num11 = num1;
		BigNumber num22 = num2;
		if (num11 < 0)
			num11.set_opposite();//保证num11为正数
		if (num22 < 0)
			num22.set_opposite();//保证num22为正数
		BigNumber num22_init = num22;//记住原来的num22
		vector<BigNumber> times_array;//记录每个数减了多少次
		int i = 0;//计数变量
		//除法开始
		while (num11 >= num22)//够减
		{
			num11 = num11 - num22;
			num22.move_dot(1, 1);//乘10
			times_array.push_back(1);
			i++;
		}
		while (num11 >= num22_init)//若小于则表明除法结束
		{
			if (num11 >= num22)//够减
			{
				num11 = num11 - num22;
				times_array[i] = times_array[i] + 1;
			}
			else //不够减
			{
				num22.move_dot(0, 1);//左移
				i--;
			}
		}
		BigNumber result(0);//结果
		for (unsigned int i = 0; i < times_array.size(); i++)
		{
			BigNumber temp(1);//临时变量
			temp.move_dot(1, i);
			result = result + temp * times_array[i];
		}
		//确定符号
		if (result == 0)//整除出的结果是0
			result.pos = '0';
		else if (num1.pos == num2.pos)//两数同号
			result.pos = '+';
		else//两数异号
			result.pos = '-';
		return result;
	}
}

//返回两数的取余
BigNumber rem_num(const BigNumber & num1, const BigNumber & num2)
{
	return (num1 - multiply_num(divide_exactly(num1, num2), num2));
}

//返回两数之和
BigNumber add_num(const BigNumber & num1, const BigNumber & num2)
{
	//两数同号
	if (num1.pos == num2.pos)
	{
		if (num1.pos == '0')
			return BigNumber("0");
		else if (num1.pos == '+')
		{
			BigNumber result = add_abs(num1, num2);
			result.pos = '+';
			return result;
		}
		else//num1.pos == '-'
		{
			BigNumber result = add_abs(num1, num2);
			result.pos = '-';
			return result;
		}
	}
	//两数异号且其中一个是0
	else if (num1.pos == '0' && num2.pos != 0)
		return num2;
	else if (num1.pos != '0' && num2.pos == 0)
		return num1;
	//一正一负
	else
	{
		BigNumber result = minus_abs(num1, num2);
		//确定结果的符号
		if (result == BigNumber(0))
			result.pos = '0';
		else
			result.pos = (cmp_abs(num1, num2) == 1) ? num1.pos : num2.pos;
		return result;
	}
}

//返回两数之差
BigNumber minus_num(const BigNumber & num1, const BigNumber & num2)
{
	//两数同号
	if (num1.pos == num2.pos)
	{
		BigNumber result = minus_abs(num1, num2);
		if (num1 > num2)
			result.pos = '+';
		else if (num1 < num2)
			result.pos = '-';
		else
			result.pos = '0';
		return result;
	}
	//前数为0
	else if (num1.pos == '0')
	{
		BigNumber result = num2;
		result.set_opposite();
		return result;
	}
	//后数为0
	else if (num2.pos == '0')
	{
		return num1;
	}
	//一正一负
	else
	{
		BigNumber result = add_abs(num1, num2);
		result.pos = num1.pos;
		return result;
	}
}

//返回两数之积
BigNumber multiply_num(const BigNumber & num1, const BigNumber & num2)
{
	BigNumber num11 = num1;//用于运算的临时变量
	BigNumber num22 = num2;//用于运算的临时变量
	//小数点右移变成整数
	num11.move_dot(1, num11.dec_len);
	num22.move_dot(1, num22.dec_len);
	
	if (num11 == 0 || num22 == 0)//其中一个乘数为0
		return BigNumber(0);
	else //一般情况
	{
		BigNumber result(0);
		//让result预留足够的空间
		result.integer.insert(result.integer.end(), num11.int_len + num22.int_len - 1, 0);
		//开始竖式乘法
		//i对应num22，j对应num11，k对应result
		for (int i = 0; i < num22.int_len; i++)
		{
			int k = i;
			for (int j = 0; j < num11.int_len; j++)
			{
				result.integer[k] += num22.integer[i] * num11.integer[j];
				if (result.integer[k] >= 10)//处理进位
				{
					result.integer[k + 1] += result.integer[k] / 10;
					result.integer[k] %= 10;
				}
				k++;
			}
		}
		result.clean_zero();//清除0，计算长度
		result.move_dot(0, num1.dec_len + num2.dec_len);//小数点左移回去
		//确定符号
		if (num11.pos != num22.pos)
			result.pos = '-';
		else
			result.pos = '+';
		return result;
	}//else
}

//返回两数之商，precision是保留的小数位数
BigNumber divide_num(const BigNumber & num1, const BigNumber & num2, int precision)
{
	BigNumber num11 = num1;//用于运算的临时变量
	BigNumber num22 = num2;//用于运算的临时变量
	num22.move_dot(1, num2.dec_len);//把num22变成整数
	num11.move_dot(1, num2.dec_len + precision + 1);
	BigNumber result = divide_exactly(num11, num22);
	result.move_dot(0, precision + 1);//此时result的小数位数为precision + 1
	result.accuracy(precision);
	return result;
}

//返回数的阶乘
BigNumber factorial_num(const BigNumber &num)
{
	if (num == 0)
		return BigNumber(0);
	else if (num.dec_len != 0)//非法的参数
		return BigNumber();
	else
	{
		BigNumber result(1);//运算结果
		for (int i = 2; i <= num; i++)
		{
			result = result * i;
		}
		return result;
	}	
}

//返回数的整数次幂，base是底数，index是指数
//index必须为整数
BigNumber pow_int_index(const BigNumber &base, const BigNumber &index)
{
	if (base.pos == '0')
		return BigNumber(0);
	if (index.pos == '0')
		return BigNumber(1);
	else if (index.pos == '-')
	{
		BigNumber index2 = index;
		index2.pos = '+';
		return (1 / pow_int_index(base, index2));
	}
	else
	{
		BigNumber result("1");
		BigNumber base2 = base;
		long long index2 = index.get_int();
		while (index2 != 0)
		{
			if (index2 & 1)//index2为奇数
				result = result * base2;
			base2 = base2 * base2;
			index2 = index2 / 2;
		}
		return result;
	}
}

//返回数的整数次开根
//degree必须为整数,且degree会被转化成int
BigNumber nth_root_int(const BigNumber & radicand, const BigNumber & degree)
{
	BigNumber small(1);
	small.move_dot(0, 7);//设成10会变慢？2开1000次方
	BigNumber radicand2 = radicand;//用于运算的临时变量
	int degree2 = degree.get_int();//用于运算的临时变量
	BigNumber x0, x1;
	x0 = radicand2 / 2;//取radicand2 / 2作为radicand2的初值
	x1 = x0 - x0 * (1 - radicand2 * pow_int_index(x0, -degree2)) / degree2;
	do 
	{
		x0 = x1;
		x1 = x0 - x0 * (1 - radicand2 * pow_int_index(x0, -degree2)) / degree2;
	} while (abs(x0 - x1) >= small);
	x0.accuracy(6);
	return x0;
}

///----运算符重载----

//运算符重载：输出流
ostream & operator<<(ostream & out, const BigNumber & num)
{
	string s;//临时字符串s
	if (num.pos == '0')
	{
		s = "0";
		out << s;
		return out;
	}
	if (num.pos == '-')
		s.insert(s.end(), '-');
	//整数部分逆序
	for (int i = num.int_len - 1; i >= 0; i--)
	{
		s.insert(s.end(), num.integer[i] + '0');
	}
	//即使整数部分为0也要输出一个0
	if (num.int_len == 0)
		s.insert(s.end(), '0');
	//有小数部分
	if (num.dec_len > 0)
	{
		s.insert(s.end(), '.');//小数点
		//小数部分顺序
		for (int i = 0; i < num.dec_len; i++)
			s.insert(s.end(), num.decimal[i] + '0');
	}
	out << s;
	return out;
}

//运算符重载：输入流
istream & operator>>(istream & in, BigNumber & num)
{
	string s;//临时字符串s
	if (!(in >> s))
		return in;
	num = BigNumber(s);
	return in;
}

//运算符重载：判等==
bool operator==(const BigNumber & num1, const BigNumber & num2)
{
	if (num1.pos == num2.pos && cmp_abs(num1, num2) == 0)
		return true;
	else
		return false;
}
//运算符重载：不等于!=
bool operator!=(const BigNumber & num1, const BigNumber & num2)
{
	if (num1 == num2)
		return false;
	else
		return true;
}
//运算符重载：大于>
bool operator>(const BigNumber & num1, const BigNumber & num2)
{
	//两数异号
	if (num1.pos == '+' && num2.pos == '0')
		return true;
	else if (num1.pos == '+' && num2.pos == '-')
		return true;
	else if (num1.pos == '0' && num2.pos == '-')
		return true;
	else if (num1.pos == '-' && num2.pos == '0')
		return false;
	else if (num1.pos == '-' && num2.pos == '+')
		return false;
	else if (num1.pos == '0' && num2.pos == '+')
		return false;
	//两数同号
	else
	{
		if (num1.pos == '+')
		{
			if (cmp_abs(num1, num2) == 1)
				return true;
			else
				return false;
		}
		else if (num1.pos == '-')
		{
			if (cmp_abs(num1, num2) == -1)
				return true;
			else
				return false;
		}
		else//都为0
			return false;
	}
}
//运算符重载：小于<
bool operator<(const BigNumber & num1, const BigNumber & num2)
{
	if (!(num1 >= num2))
		return true;
	else
		return false;
}
//运算符重载：大于等于>=
bool operator>=(const BigNumber & num1, const BigNumber & num2)
{
	if (num1 > num2 || num1 == num2)
		return true;
	else
		return false;
}
//运算符重载：小于等于<=
bool operator<=(const BigNumber & num1, const BigNumber & num2)
{
	if (!(num1 > num2))
		return true;
	else
		return false;
}

//运算符重载：相加+
BigNumber operator+(const BigNumber & num1, const BigNumber & num2)
{
	return add_num(num1, num2);
}

//运算符重载：相减-
BigNumber operator-(const BigNumber & num1, const BigNumber & num2)
{
	return minus_num(num1, num2);
}

//运算符重载：相乘*(保留PRECISION位小数)
BigNumber operator*(const BigNumber & num1, const BigNumber & num2)
{
	BigNumber result = multiply_num(num1, num2);
	result.accuracy(PRECISION);
	return result;
}

//运算符重载：相除/(保留PRECISION位小数)
BigNumber operator/(const BigNumber & num1, const BigNumber & num2)
{
	return divide_num(num1, num2, PRECISION);
}

//运算符重载：取余%
BigNumber operator%(const BigNumber & num1, const BigNumber & num2)
{
	return rem_num(num1, num2);
}

//运算符重载：取相反数-
BigNumber BigNumber::operator-() const
{
	BigNumber temp = *this;
	temp.set_opposite();
	return temp;
}

//运算符重载：前置++
BigNumber& BigNumber::operator++()
{
	*this = (*this) + 1;
	return *this;
}
//运算符重载：后置++
BigNumber BigNumber::operator++(int)
{
	BigNumber old = *this;
	++(*this);
	return old;
}

//运算符重载：+=
BigNumber & BigNumber::operator+=(const BigNumber & num)
{
	*this = *this + num;
	return *this;
}
//运算符重载：-=
BigNumber & BigNumber::operator-=(const BigNumber & num)
{
	*this = *this - num;
	return *this;
}
//运算符重载：*=
BigNumber & BigNumber::operator*=(const BigNumber & num)
{
	*this = *this * num;
	return *this;
}
//运算符重载：/= 做除法而不是整除
BigNumber & BigNumber::operator/=(const BigNumber & num)
{
	*this = *this / num;
	return *this;
}
//运算符重载：%=
BigNumber & BigNumber::operator%=(const BigNumber & num)
{
	*this = *this % num;
	return *this;
}