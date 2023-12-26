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
	cout << "Depth : " << _BinaryTree.GetMaxDepth() << "\n";
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
	cout << "Depth : " << _RedBlackTree.GetMaxDepth() << "\n";

	// 삽입, 삭제 신뢰성 테스트
	int randomNum;
	int deleteIndex = 0;
	int insertIndex = 0;
	while (deleteIndex < RANDOM_COUNT)
	{
		int deleteCount = deleteIndex + rand();

		if (deleteCount >= RANDOM_COUNT)
			deleteCount = RANDOM_COUNT;

		// 삭제
		for (int j = deleteIndex; j < deleteCount; j++)
		{
			randomNum = _TestCase[j];
			_RedBlackTree.Delete(randomNum);
			//_ReliableList.remove(randomNum);
		}
		cout << deleteCount - deleteIndex << "개 삭제\n";
		deleteIndex = deleteCount;

		int insertCount = insertIndex + rand();

		if (insertCount >= deleteCount)
			insertCount = deleteCount / 2;

		// 삽입
		for (int j = insertIndex; j < insertCount; j++)
		{
			randomNum = _TestCase[j];
			_RedBlackTree.Insert(randomNum);
			//_ReliableList.push_back(randomNum);
		}
		cout << insertCount - insertIndex << "개 삽입\n";
		insertIndex = insertCount;

		// 조회
		//_ReliableList.sort();
		//_RedBlackTree.ReliableTest(_ReliableList);
		cout << "Depth : " << _RedBlackTree.GetMaxDepth() << "\n";
	}

	// delete Index 만큼 부족한 것 Insert
	for (int i = insertIndex; i < deleteIndex; i++)
	{
		randomNum = _TestCase[i];
		_RedBlackTree.Insert(randomNum);
		//_ReliableList.push_back(randomNum);
	}
	cout << deleteIndex - insertIndex << "개 삽입\n";
	cout << "Depth : " << _RedBlackTree.GetMaxDepth() << "\n";
	// 조회
	//_ReliableList.sort();
	_RedBlackTree.ReliableTest(_ReliableList);
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