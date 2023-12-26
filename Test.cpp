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

	// �ش� ���� Ʈ���� �����ϰ�, Ʈ���� �ش� Vector�� �Ѱ� �����Ѵ�.
	for (auto iter = _ReliableList.begin(); iter != _ReliableList.end(); ++iter)
		_BinaryTree.Insert(*iter);

	_ReliableList.sort();

	// ���� �ŷڼ� �׽�Ʈ
	_BinaryTree.ReliableTest(_ReliableList);
	cout << "Depth : " << _BinaryTree.GetMaxDepth() << "\n";
}

void Test::TestRedBlackTree()
{
	list<int> _ReliableList;
	for (int i = 0; i < _TestCase.size(); i++)
		_ReliableList.push_back(_TestCase[i]);

	// �ش� ���� Ʈ���� �����ϰ�, Ʈ���� �ش� Vector�� �Ѱ� �����Ѵ�.
	for (auto iter = _ReliableList.begin(); iter != _ReliableList.end(); ++iter)
		_RedBlackTree.Insert(*iter);

	_ReliableList.sort();

	// ���� �ŷڼ� �׽�Ʈ
	_RedBlackTree.ReliableTest(_ReliableList);
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
			//_ReliableList.remove(randomNum);
		}
		cout << deleteCount - deleteIndex << "�� ����\n";
		deleteIndex = deleteCount;

		int insertCount = insertIndex + rand();

		if (insertCount >= deleteCount)
			insertCount = deleteCount / 2;

		// ����
		for (int j = insertIndex; j < insertCount; j++)
		{
			randomNum = _TestCase[j];
			_RedBlackTree.Insert(randomNum);
			//_ReliableList.push_back(randomNum);
		}
		cout << insertCount - insertIndex << "�� ����\n";
		insertIndex = insertCount;

		// ��ȸ
		//_ReliableList.sort();
		//_RedBlackTree.ReliableTest(_ReliableList);
		cout << "Depth : " << _RedBlackTree.GetMaxDepth() << "\n";
	}

	// delete Index ��ŭ ������ �� Insert
	for (int i = insertIndex; i < deleteIndex; i++)
	{
		randomNum = _TestCase[i];
		_RedBlackTree.Insert(randomNum);
		//_ReliableList.push_back(randomNum);
	}
	cout << deleteIndex - insertIndex << "�� ����\n";
	cout << "Depth : " << _RedBlackTree.GetMaxDepth() << "\n";
	// ��ȸ
	//_ReliableList.sort();
	_RedBlackTree.ReliableTest(_ReliableList);
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