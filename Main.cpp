#include "RedBlackTree.h"
#include "Test.h"
#include <iostream>
using namespace std;

int main()
{
	RedBlackTree tree;
	tree.Insert(30);
	tree.Insert(10);
	tree.Insert(40);
	tree.Insert(20);
	tree.Insert(25);
	tree.Insert(28);

	tree.Print();
}