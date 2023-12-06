#pragma once
#include <vector>
#include <string>
using namespace std;

struct Cell {
	string Value;
	bool Present;

	Cell()
	{
		Present = false;
	}
};

using RowList = vector<vector<Cell>>;