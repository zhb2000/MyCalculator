#pragma once
#include <stack>
#include <map>
#include <vector>
using namespace std;



//真值表的一行
struct TruthTableRow
{
	map<char, bool> assignment;
	bool func_result;
};

typedef vector<TruthTableRow> TruthTable;