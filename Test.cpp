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

	vector<int> deleteItems;
	int randomNum;
	// ����, ���� �ŷڼ� �׽�Ʈ
	for (int i = 0; i < TEST_COUNT; i++)
	{
		// ���� �� ��ȸ
		for (int j = 0; j < rand(); j++)
		{
			randomNum = MakeIntRand(RANDOM_COUNT);
			_BinaryTree.Delete(randomNum);
			_ReliableList.remove(randomNum);
			deleteItems.push_back(randomNum);
		}

		// ���� �� ��ȸ

	}
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