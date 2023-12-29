#pragma once
#include "RedBlackTree.h"
#include "BinaryTree.h"
#include <Windows.h>
#include <profileapi.h>

#define RANDOM_COUNT 1000000
#define INSERT_COUNT 300000
#define DELETE_COUNT 300000

class Test {
public:
	Test();
	virtual ~Test();

	void CalculateTime();

	void MakeTestCase(int Count = RANDOM_COUNT);
	void TestBinaryTree();
	void TestRedBlackTree();

	void TestTree001();

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