#include "RedBlackTree.h"
#include "Test.h"
#include <iostream>
using namespace std;

RedBlackTree tree;
Test test;

void Insert(int num)
{
	test.PutReliableData(num);
	tree.Insert(num);
}

void TestAutoTree2()
{
	Insert(100);

	Insert(50);
	Insert(150);

	Insert(30);
	Insert(70);
	Insert(20);
	Insert(40);

	Insert(60);
	Insert(80);
	Insert(10);
	Insert(25); 
	Insert(35);
	Insert(45);
	Insert(28);

	tree.Delete(150);
	tree.Delete(60);
	tree.Delete(70);
	tree.Delete(80);
	tree.Delete(100);

	tree.Print();
	test.Print();
}

void TestAutoTree()
{
	RedBlackTree tree;
	srand(3);

	Test test;

	for (int i = 0; i < 10; i++)
	{
		int random = rand() % 100;
		test.PutReliableData(random);
		tree.Insert(random);
		tree.Print();
		test.Print();
	}
}

void TestManualTree()
{
	RedBlackTree tree;
	Test test;
	int Data;
	int Menu;

	cout << "[메뉴] 1. 삽입 2. 찾기 3. 삭제 4. 종료\n";

	while (1)
	{
		cout << ">> ";
		cin >> Menu;

		switch (Menu)
		{
		case 1:
			cout << ">> ";
			cin >> Data;
			test.PutReliableData(Data);
			tree.Insert(Data);
			tree.Print();
			test.Print();
			break;
		case 2:
			cout << ">> ";
			cin >> Data;
			if (true == tree.Find(Data))
			{
				cout << "데이터가 존재함.\n";
			}
			else
			{
				cout << "데이터가 존재하지 않음.\n";
			}
			break;
		case 3:
			cout << ">> ";
			cin >> Data;
			if (true == tree.Delete(Data))
			{
				tree.Print();
			}
			else
			{
				cout << "트리 내 존재하지 않는 데이터 입니다.\n";
			}
			break;
		case 4:
			return;
		default:
			cout << "잘못된 메뉴입니다. \n";
			break;
		}
		
	}
}

int main()
{
	TestManualTree();
}