#include "RedBlackTree.h"
#include "Test.h"
#include <iostream>
using namespace std;

int main()
{
	RedBlackTree tree;
	srand(3);

	Test test;

	for (int i = 0; i < 30; i++)
	{
		int random = rand() % 100;
		test.PutReliableData(random);
		tree.Insert(random);
		tree.Print();
		test.Print();
	}
}