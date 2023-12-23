#include "Test.h"
#include "RedBlackTree.h"
#include <iostream>

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

	RedBlackTree RandomRedBlackTree;
	BinaryTree RandomBinaryTree;
	MakeTestCase();

	cout << "[비순차적(랜덤)] " << RANDOM_COUNT <<  " \n";
	// 비순차적인 데이터
	QueryPerformanceCounter(&Start);
	for (auto iter = _TestCase.begin(); iter != _TestCase.end(); ++iter)
		RandomBinaryTree.Insert(*iter);
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Binary Tree Insert : " << cal << "\n";

	QueryPerformanceCounter(&Start);
	for (auto iter = _TestCase.begin(); iter != _TestCase.end(); ++iter)
		RandomRedBlackTree.Insert(*iter);
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Red Black Tree Insert : " << cal << "\n";
}

void Test::TestBinaryTree()
{
	list<int> _ReliableList;
	for (int i = 0; i < _TestCase.size(); i++)
		_ReliableList.push_back(_TestCase[i]);

	// 해당 값을 트리에 삽입하고, 트리로 해당 Vector를 넘겨 검증한다.
	for (auto iter = _ReliableList.begin(); iter != _ReliableList.end(); ++iter)
		_BinaryTree.Insert(*iter);

	_ReliableList.sort();

	// 삽입 신뢰성 테스트
	_BinaryTree.ReliableTest(_ReliableList);

	vector<int> deleteItems;
	int randomNum;
	// 삽입, 삭제 신뢰성 테스트
	for (int i = 0; i < TEST_COUNT; i++)
	{
		// 삭제 후 조회
		for (int j = 0; j < rand(); j++)
		{
			randomNum = MakeIntRand(RANDOM_COUNT);
			_BinaryTree.Delete(randomNum);
			_ReliableList.remove(randomNum);
			deleteItems.push_back(randomNum);
		}

		// 삽입 후 조회

	}
}

void Test::TestRedBlackTree()
{
	list<int> _ReliableList;
	for (int i = 0; i < _TestCase.size(); i++)
		_ReliableList.push_back(_TestCase[i]);

	// 해당 값을 트리에 삽입하고, 트리로 해당 Vector를 넘겨 검증한다.
	for (auto iter = _ReliableList.begin(); iter != _ReliableList.end(); ++iter)
		_RedBlackTree.Insert(*iter);

	_ReliableList.sort();

	// 삽입 신뢰성 테스트
	_RedBlackTree.ReliableTest(_ReliableList);

	// 삭제 신뢰성 테스트
	int DeleteCount = MakeIntRand(RANDOM_COUNT);
}

int Test::MakeIntRand(int maxNum)
{
	unsigned int num = rand();
	num <<= 15;
	num += rand();

	// 보니까 %가 들어간 시점에서 난수 측정하기에 멀었다.
	num %= maxNum;

	return (int)num;
}

void Test::MakeTestCase()
{
	_TestCase.clear();

	// 순차적인 값을 가진 리스트를 준비하고 셔플한다.
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