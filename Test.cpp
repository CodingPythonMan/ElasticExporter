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

	std::cout << "[Binary Tree ����] " << INSERT_COUNT << " \n";
	// ��������� ������
	QueryPerformanceCounter(&Start);
	for (int i = 0; i < INSERT_COUNT; i++)
		binaryTree.Insert(_TestCase[i]);
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Binary Tree Insert : " << cal << "\n";

	cout << "[Binary Tree ����] " << DELETE_COUNT << " \n";
	// ��������� ������
	QueryPerformanceCounter(&Start);
	for (int i = 0; i < DELETE_COUNT; i++)
		binaryTree.Delete(_TestCase[i]);
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Binary Tree Delete : " << cal << "\n";

	cout << "[Red Black Tree ����] " << INSERT_COUNT << " \n";
	// ��������� ������
	QueryPerformanceCounter(&Start);
	for (int i = 0; i < INSERT_COUNT; i++)
		redBlackTree.Insert(_TestCase[i]);
	QueryPerformanceCounter(&End);

	cal = (End.QuadPart - Start.QuadPart) / (double)_Freq.QuadPart;
	cout << "Red Black Tree Insert : " << cal << "\n";

	cout << "[Red Black Tree ����] " << DELETE_COUNT << " \n";
	// ��������� ������
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

	// �ش� ���� Ʈ���� �����ϰ�, Ʈ���� �ش� Set�� �Ѱ� �����Ѵ�.
	for (int i = 0; i < _TestCase.size(); i++)
		_BinaryTree.Insert(_TestCase[i]);

	// ���� �ŷڼ� �׽�Ʈ
	_BinaryTree.ReliableTest(_ReliableSet);
	cout << "Depth : " << _BinaryTree.GetMaxDepth() << "\n";
}

void Test::TestRedBlackTree()
{
	set<int> _ReliableSet;
	for (int i = 0; i < _TestCase.size(); i++)
		_ReliableSet.insert(_TestCase[i]);

	// �ش� ���� Ʈ���� �����ϰ�, Ʈ���� �ش� Set�� �Ѱ� �����Ѵ�.
	for (int i = 0; i < _TestCase.size(); i++)
		_RedBlackTree.Insert(_TestCase[i]);

	// ���� �ŷڼ� �׽�Ʈ
	_RedBlackTree.ReliableTest(_ReliableSet);
	cout << "Depth : " << _RedBlackTree.GetMaxDepth() << "\n";

	// ����, ���� �ŷڼ� �׽�Ʈ
	int randomNum;
	int deleteIndex = 0;
	int insertIndex = 0;
	while (deleteIndex < RANDOM_COUNT)
	{
		int deleteCount = deleteIndex + rand();

		if (deleteCount >= RANDOM_COUNT)
			deleteCount = RANDOM_COUNT;

		// ����
		for (int j = deleteIndex; j < deleteCount; j++)
		{
			randomNum = _TestCase[j];
			_RedBlackTree.Delete(randomNum);
			_ReliableSet.erase(randomNum);
		}
		cout << deleteCount - deleteIndex << "�� ����\n";
		deleteIndex = deleteCount;

		int insertCount = deleteCount / 2;

		// ����
		for (int j = insertIndex; j < insertCount; j++)
		{
			randomNum = _TestCase[j];
			_RedBlackTree.Insert(randomNum);
			_ReliableSet.insert(randomNum);
		}
		cout << insertCount - insertIndex << "�� ����\n";
		insertIndex = insertCount;

		// ��ȸ
		_RedBlackTree.ReliableTest(_ReliableSet);
		cout << "Depth : " << _RedBlackTree.GetMaxDepth() << "\n";
	}

	// delete Index ��ŭ ������ �� Insert
	for (int i = insertIndex; i < deleteIndex; i++)
	{
		randomNum = _TestCase[i];
		_RedBlackTree.Insert(randomNum);
		_ReliableSet.insert(randomNum);
	}
	cout << deleteIndex - insertIndex << "�� ����\n";
	cout << "Depth : " << _RedBlackTree.GetMaxDepth() << "\n";
	// ��ȸ
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

	// ���ϱ� %�� �� �������� ���� �����ϱ⿡ �־���.
	num %= maxNum;

	return (int)num;
}

void Test::MakeTestCase(int Count)
{
	_TestCase.clear();

	// �������� ���� ���� ����Ʈ�� �غ��ϰ� �����Ѵ�.
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