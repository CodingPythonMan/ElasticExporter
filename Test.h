#pragma once
#include "RedBlackTree.h"
#include "BinaryTree.h"
#include <Windows.h>
#include <profileapi.h>

#define INC_COUNT 1000
#define RANDOM_COUNT 10000
#define TEST_COUNT 20

class Test {
public:
	Test();
	virtual ~Test();

	void CalculateInsertTime();

	void MakeTestCase();
	void TestBinaryTree();
	void TestRedBlackTree();

private:
	void Shuffle(int& num1, int& num2);
	int MakeIntRand(int maxNum);

private:
	vector<int> _TestCase;
	BinaryTree _BinaryTree;
	RedBlackTree _RedBlackTree;

	// 시간 관련 변수
	LARGE_INTEGER _Freq;

};