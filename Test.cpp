#include "Test.h"
#include <iostream>
#include <algorithm>

Test::Test()
{
	QueryPerformanceFrequency(&_Freq);
}

Test::~Test()
{
}

void Test::CalculateTime()
{
	LARGE_INTEGER Start, End;
	double cal;

	RedBlackTree redBlackTree;
	BinaryTree binaryTree;
	MakeTestCase(INSERT_COUNT);

	std::cout << "[Binary Tree 삽입] " << INSERT_COUNT << " \n";
	// 비순차적인 데이터
	QueryPerformanceCounter(&Start);
	for (int i = 0; i < INSERT_COUNT; i++)
		binaryTree.Insert(_TestCase[i]);
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Binary Tree Insert : " << cal << "\n";

	cout << "[Binary Tree 삭제] " << DELETE_COUNT << " \n";
	// 비순차적인 데이터
	QueryPerformanceCounter(&Start);
	for (int i = 0; i < DELETE_COUNT; i++)
		binaryTree.Delete(_TestCase[i]);
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Binary Tree Delete : " << cal << "\n";

	cout << "[Red Black Tree 삽입] " << INSERT_COUNT << " \n";
	// 비순차적인 데이터
	QueryPerformanceCounter(&Start);
	for (int i = 0; i < INSERT_COUNT; i++)
		redBlackTree.Insert(_TestCase[i]);
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Red Black Tree Insert : " << cal << "\n";

	cout << "[Red Black Tree 삭제] " << DELETE_COUNT << " \n";
	// 비순차적인 데이터
	QueryPerformanceCounter(&Start);
	for (int i = 0; i < DELETE_COUNT; i++)
		redBlackTree.Delete(_TestCase[i]);
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Red Black Tree Delete : " << cal << "\n";
}

void Test::TestBinaryTree()
{
	set<int> _ReliableSet;
	for (int i = 0; i < _TestCase.size(); i++)
		_ReliableSet.insert(_TestCase[i]);

	// 해당 값을 트리에 삽입하고, 트리로 해당 Set를 넘겨 검증한다.
	for (int i = 0; i < _TestCase.size(); i++)
		_BinaryTree.Insert(_TestCase[i]);

	// 삽입 신뢰성 테스트
	_BinaryTree.ReliableTest(_ReliableSet);
	cout << "Depth : " << _BinaryTree.GetMaxDepth() << "\n";
}

void Test::TestRedBlackTree()
{
	set<int> _ReliableSet;
	for (int i = 0; i < _TestCase.size(); i++)
		_ReliableSet.insert(_TestCase[i]);

	// 해당 값을 트리에 삽입하고, 트리로 해당 Set을 넘겨 검증한다.
	for (int i = 0; i < _TestCase.size(); i++)
		_RedBlackTree.Insert(_TestCase[i]);

	// 삽입 신뢰성 테스트
	_RedBlackTree.ReliableTest(_ReliableSet);
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
			_ReliableSet.erase(randomNum);
		}
		cout << deleteCount - deleteIndex << "개 삭제\n";
		deleteIndex = deleteCount;

		int insertCount = deleteCount / 2;

		// 삽입
		for (int j = insertIndex; j < insertCount; j++)
		{
			randomNum = _TestCase[j];
			_RedBlackTree.Insert(randomNum);
			_ReliableSet.insert(randomNum);
		}
		cout << insertCount - insertIndex << "개 삽입\n";
		insertIndex = insertCount;

		// 조회
		_RedBlackTree.ReliableTest(_ReliableSet);
		cout << "Depth : " << _RedBlackTree.GetMaxDepth() << "\n";
	}

	// delete Index 만큼 부족한 것 Insert
	for (int i = insertIndex; i < deleteIndex; i++)
	{
		randomNum = _TestCase[i];
		_RedBlackTree.Insert(randomNum);
		_ReliableSet.insert(randomNum);
	}
	cout << deleteIndex - insertIndex << "개 삽입\n";
	cout << "Depth : " << _RedBlackTree.GetMaxDepth() << "\n";
	// 조회
	_RedBlackTree.ReliableTest(_ReliableSet);
}

void Test::TestTree001()
{
	BinaryTree binaryTree;

	for (auto iter = _TestCase.begin(); iter != _TestCase.end(); ++iter)
		binaryTree.Insert(*iter);

	binaryTree.Delete(40340);

	binaryTree.Insert(40340);
	binaryTree.Delete(40340);
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

void Test::MakeTestCase(int Count)
{
	_TestCase.clear();

	// 순차적인 값을 가진 리스트를 준비하고 셔플한다.
	for (int i = 0; i < Count; i++)
	{
		_TestCase.push_back(i);
	}

	for (int i = 0; i < Count; i++)
		Shuffle(_TestCase[i], _TestCase[MakeIntRand(Count)]);
}

void Test::Shuffle(int& num1, int& num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}