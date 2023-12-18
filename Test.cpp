#include "Test.h"
#include "RedBlackTree.h"
#include <iostream>
#include <algorithm>
#include <random>

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

	cout << "[순차적(오름차순)] " << INC_COUNT << "\n";
	QueryPerformanceCounter(&Start);
	// 순차적인 데이터(오름차순)
	for (int i = 0; i < INC_COUNT; i++)
	{
		_BinaryTree.Insert(i);
	}
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Binary Tree Insert : " << cal << "\n";

	QueryPerformanceCounter(&Start);
	// 순차적인 데이터(오름차순)
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

	cout << "[비순차적(랜덤)] " << RANDOM_COUNT <<  " \n";
	// 비순차적인 데이터
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

	// 1. 순차적인 값을 가진 리스트를 준비하고 셔플한다.
	for (int i = 0; i < RANDOM_COUNT; i++)
	{
		_ReliableList.push_back(i);
	}

	random_device rd;
	// Seed Value
	mt19937 gen(rd());
	uniform_int_distribution<int> random(0, RANDOM_COUNT-1);

	for (int i = 0; i < RANDOM_COUNT; i++)
		Shuffle(_ReliableList[i], _ReliableList[random(gen)]);

	// 2. 해당 값을 트리에 삽입하고, 트리로 해당 Vector를 넘겨 검증한다.
	for (int i = 0; i < _ReliableList.size(); i++)
		_RedBlackTree.Insert(_ReliableList[i]);

	sort(_ReliableList.begin(), _ReliableList.end());

	_RedBlackTree.Test(_ReliableList);
}

void Test::Shuffle(int& num1, int& num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}