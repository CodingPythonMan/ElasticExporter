#include "Test.h"
#include <iostream>
using namespace std;

bool Test::PutReliableData(int Data)
{
	ReliableQueue.push(Data);

	return false;
}

void Test::Print()
{
	cout << "q = ( ";
	while (!ReliableQueue.empty())
	{
		cout << ReliableQueue.top() << " ";
		ReliableQueue.pop();
	}
	cout << ")" << "\n";
}