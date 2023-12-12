#include "Test.h"
#include "RedBlackTree.h"
#include <iostream>

Test::Test()
{
	QueryPerformanceFrequency(&_Freq);

	make_heap(ReliableList.begin(), ReliableList.end());
}

Test::~Test()
{
}

bool Test::PutReliableData(int Data)
{
	ReliableList.push_back(Data);
	_BinaryTree.Insert(Data);
	_RedBlackTree.Insert(Data);

	return true;
}

void Test::Print()
{
	cout << "List (";
	for (int elem : ReliableList)
	{
		cout << elem << ", ";
	}
	cout << ")" << "\n";
}

void Test::CaculateInsertTime()
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
		ReliableList.push_back(rand());
	}
	RedBlackTree RandomRedBlackTree;
	BinaryTree RandomBinaryTree;

	cout << "[�������(����)] " << RANDOM_COUNT <<  " \n";
	// ��������� ������
	QueryPerformanceCounter(&Start);
	for (int i = 0; i < RANDOM_COUNT; i++)
	{
		RandomBinaryTree.Insert(ReliableList[i]);
	}
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Binary Tree Insert : " << cal << "\n";

	QueryPerformanceCounter(&Start);
	for (int i = 0; i < RANDOM_COUNT; i++)
	{
		RandomRedBlackTree.Insert(ReliableList[i]);
	}
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Red Black Tree Insert : " << cal << "\n";
}