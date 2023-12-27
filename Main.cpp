#include "RedBlackTree.h"
#include "Test.h"
#include <iostream>
using namespace std;

Test test;

void TestCase001()
{
	RedBlackTree redblackTree;
	for(int i=0 ; i< 10; i++)
		redblackTree.Insert(i);


	for (int i = 0; i < 5; i++)
		redblackTree.Delete(i);

	redblackTree.Insert(10);
	redblackTree.Insert(3);
	redblackTree.Insert(11);
	redblackTree.Insert(0);
	redblackTree.Insert(15);
	redblackTree.Insert(4);
	redblackTree.Insert(17);

	for (int i = 6; i < 11; i++)
	{
		redblackTree.Delete(i);
		redblackTree.Print();
	}
}

void TestCase002()
{
	test.MakeTestCase();
	test.TestTree001();
}

void TestAutoTree()
{
	test.CalculateTime();
}

// �ǻ� ���� ����� �׽�Ʈ
void TestRandomNumberTree()
{
	test.MakeTestCase();
	test.TestRedBlackTree();
	test.TestBinaryTree();
}

void TestManualTree()
{
	RedBlackTree tree;
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
			if (true == tree.Insert(Data))
			{
				tree.Print();
			}
			else
			{
				cout << "�̹� �����Ͱ� �����մϴ�.\n";
			}
			break;
		case 2:
			cout << ">> ";
			cin >> Data;
			if (true == tree.Find(Data))
			{
				cout << "�����Ͱ� �����մϴ�.\n";
			}
			else
			{
				cout << "�����Ͱ� �������� �ʽ��ϴ�.\n";
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
	// Test �� Ȯ���� ��.
	TestManualTree();

	// ����, ���� �ŷڼ� �׽�Ʈ
	//TestRandomNumberTree();

	// ����, ���� �ð� �׽�Ʈ
	//TestAutoTree();

	// �׽�Ʈ ���̽�
	//TestCase001();
	//TestCase002();
}