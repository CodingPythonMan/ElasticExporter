#pragma once

#include "RedBlackTree.h"
#include "BinaryTree.h"
#include <queue>
#include <Windows.h>
#include <profileapi.h>

#define INC_COUNT 1000
#define RANDOM_COUNT 1000000

class Test {
public:
	Test();
	virtual ~Test();

	bool PutReliableData(int Data);
	
	void Print();

	void CalculateInsertTime();

	void TestBinaryTree();
	void TestRedBlackTree();

private:
	void Shuffle(int& num1, int& num2);

private:
	vector<int> _ReliableList;
	BinaryTree _BinaryTree;
	RedBlackTree _RedBlackTree;

	// 시간 관련 변수
	LARGE_INTEGER _Freq;

};