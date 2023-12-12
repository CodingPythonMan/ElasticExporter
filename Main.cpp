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
	tree.Delete(35);
	tree.Delete(45);
	tree.Delete(40);

	Insert(120);
	Insert(130);

	tree.Delete(50);

	tree.Print();
	test.Print();
}

void TestAutoTree()
{
	test.CaculateInsertTime();
}

void TestManualTree()
{
	RedBlackTree tree;
	Test test;
	int Data;
	int Menu;

	cout << "[�޴�] 1. ���� 2. ã�� 3. ���� 4. ����\n";

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
				cout << "�����Ͱ� ������.\n";
			}
			else
			{
				cout << "�����Ͱ� �������� ����.\n";
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
				cout << "Ʈ�� �� �������� �ʴ� ������ �Դϴ�.\n";
			}
			break;
		case 4:
			return;
		default:
			cout << "�߸��� �޴��Դϴ�. \n";
			break;
		}
		
	}
}

int main()
{
	//TestManualTree();
	//TestAutoTree2();
	TestAutoTree();
}