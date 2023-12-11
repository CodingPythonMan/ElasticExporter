#include "RedBlackTree.h"
#include "Test.h"
#include <iostream>
using namespace std;

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
	TestManualTree();
	//TestAutoTree();
}