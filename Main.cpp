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
		int random = rand() % 30;
		test.PutReliableData(random);

		if (i == 20)
			tree.Insert(random);

		tree.Insert(random);
		tree.Print();
	}

	test.Print();
}