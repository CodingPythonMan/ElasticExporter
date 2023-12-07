#include "Test.h"
#include <iostream>

Test::Test()
{
	make_heap(ReliableList.begin(), ReliableList.end());
}

Test::~Test()
{
}

bool Test::PutReliableData(int Data)
{
	ReliableList.push_back(Data);

	return true;
}

void Test::Print()
{
	cout << "List (";
	for (int elem : ReliableList)
	{
		cout << elem << ", ";
	}
	cout << ")" << "\n";
}