#include "Test.h"
#include "RedBlackTree.h"
#include <iostream>
#include <algorithm>

Test::Test()
{
	QueryPerformanceFrequency(&_Freq);
}

Test::~Test()
{
}

void Test::CalculateInsertTime()
{
	LARGE_INTEGER Start, End;
	double cal;

	cout << "[������(��������)] " << INC_COUNT << "\n";
	QueryPerformanceCounter(&Start);
	// �������� ������(��������)
	for (int i = 0; i < INC_COUNT; i++)
	{
		_BinaryTree.Insert(i);
	}
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Binary Tree Insert : " << cal << "\n";

	QueryPerformanceCounter(&Start);
	// �������� ������(��������)
	for (int i = 0; i < INC_COUNT; i++)
	{
		_RedBlackTree.Insert(i);
	}
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Red Black Tree Insert : " << cal << "\n\n";

	RedBlackTree RandomRedBlackTree;
	BinaryTree RandomBinaryTree;
	MakeTestCase();

	cout << "[�������(����)] " << RANDOM_COUNT <<  " \n";
	// ��������� ������
	QueryPerformanceCounter(&Start);
	for (int i = 0; i < RANDOM_COUNT; i++)
	{
		RandomBinaryTree.Insert(_TestCase[i]);
	}
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Binary Tree Insert : " << cal << "\n";

	QueryPerformanceCounter(&Start);
	for (int i = 0; i < RANDOM_COUNT; i++)
	{
		RandomRedBlackTree.Insert(_TestCase[i]);
	}
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Red Black Tree Insert : " << cal << "\n";
}

void Test::TestBinaryTree()
{
	vector<int> _ReliableList{ _TestCase };

	// �ش� ���� Ʈ���� �����ϰ�, Ʈ���� �ش� Vector�� �Ѱ� �����Ѵ�.
	for (int i = 0; i < _ReliableList.size(); i++)
		_BinaryTree.Insert(_ReliableList[i]);

	sort(_ReliableList.begin(), _ReliableList.end());

	// ���� �ŷڼ� �׽�Ʈ
	_BinaryTree.ReliableTest(_ReliableList);

	// ����, ���� �ŷڼ� �׽�Ʈ
	/*
	for (int i = 0; i < TEST_COUNT; i++)
	{
		int DeleteCount = _TestCase[i];

		for (int i = 0; i < DeleteCount; i++)
		{
			int DeleteNum = _ReliableList[_ReliableList.size() - 1];

			if (DeleteNum % 2 == 0)
			{
				_ReliableList.pop_back();
				_BinaryTree.Delete(i);
			}
			else
			{
				DeleteNum = _ReliableList[0];

			}
		}

	}*/
}

void Test::TestRedBlackTree()
{
	vector<int> _ReliableList{ _TestCase };

	// �ش� ���� Ʈ���� �����ϰ�, Ʈ���� �ش� Vector�� �Ѱ� �����Ѵ�.
	for (int i = 0; i < _ReliableList.size(); i++)
		_RedBlackTree.Insert(_ReliableList[i]);

	sort(_ReliableList.begin(), _ReliableList.end());

	// ���� �ŷڼ� �׽�Ʈ
	_RedBlackTree.ReliableTest(_ReliableList);

	// ���� �ŷڼ� �׽�Ʈ
	int DeleteCount = MakeIntRand(RANDOM_COUNT);
}

int Test::MakeIntRand(int maxNum)
{
	unsigned int num = rand();
	num <<= 15;
	num += rand();

	// ���ϱ� %�� �� �������� ���� �����ϱ⿡ �־���.
	num %= maxNum;

	return (int)num;
}

void Test::MakeTestCase()
{
	_TestCase.clear();

	// �������� ���� ���� ����Ʈ�� �غ��ϰ� �����Ѵ�.
	for (int i = 0; i < RANDOM_COUNT; i++)
	{
		_TestCase.push_back(i);
	}

	for (int i = 0; i < RANDOM_COUNT; i++)
		Shuffle(_TestCase[i], _TestCase[MakeIntRand(RANDOM_COUNT)]);
}

void Test::Shuffle(int& num1, int& num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}