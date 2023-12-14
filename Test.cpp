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

bool Test::PutReliableData(int Data)
{
	_ReliableList.push_back(Data);
	_BinaryTree.Insert(Data);
	_RedBlackTree.Insert(Data);

	return true;
}

void Test::Print()
{
	cout << "List (";
	for (int elem : _ReliableList)
	{
		cout << elem << ", ";
	}
	cout << ")" << "\n";
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

	srand(3);
	for (int i = 0; i < RANDOM_COUNT; i++)
	{
		_ReliableList.push_back(rand());
	}
	RedBlackTree RandomRedBlackTree;
	BinaryTree RandomBinaryTree;

	cout << "[�������(����)] " << RANDOM_COUNT <<  " \n";
	// ��������� ������
	QueryPerformanceCounter(&Start);
	for (int i = 0; i < RANDOM_COUNT; i++)
	{
		RandomBinaryTree.Insert(_ReliableList[i]);
	}
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Binary Tree Insert : " << cal << "\n";

	QueryPerformanceCounter(&Start);
	for (int i = 0; i < RANDOM_COUNT; i++)
	{
		RandomRedBlackTree.Insert(_ReliableList[i]);
	}
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Red Black Tree Insert : " << cal << "\n";
}

void Test::TestBinaryTree()
{

}

void Test::TestRedBlackTree()
{
	_ReliableList.clear();

	// 1. �������� ���� ���� ����Ʈ�� �غ��ϰ� �����Ѵ�.
	for (int i = 0; i < RANDOM_COUNT; i++)
	{
		_ReliableList.push_back(i);
	}

	int a = MakeIntRand(RANDOM_COUNT);
	int b = MakeIntRand(RANDOM_COUNT);

	for (int i = 0; i < RANDOM_COUNT; i++)
		Shuffle(_ReliableList[a], _ReliableList[b]);

	Shuffle(_ReliableList[0], _ReliableList[1]);

	// 2. �ش� ���� Ʈ���� �����ϰ�, Ʈ���� �ش� Vector�� �Ѱ� �����Ѵ�.
	for (int i = 0; i < _ReliableList.size(); i++)
		_RedBlackTree.Insert(_ReliableList[i]);

	sort(_ReliableList.begin(), _ReliableList.end());

	_RedBlackTree.Test(_ReliableList);
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

void Test::Shuffle(int& num1, int& num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}