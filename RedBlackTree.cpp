#include "RedBlackTree.h"
#include <iostream>

RedBlackTree::RedBlackTree()
{
	_Nil = new Node;
	_Nil->Color = NODE_COLOR::BLACK;
	_Nil->Parent = nullptr;
	_Nil->Left = nullptr;
	_Nil->Right = nullptr;
	_Root = nullptr;
}

RedBlackTree::~RedBlackTree()
{
	delete _Nil;

	// 트리 내 노드 모두 동적 해제 해줄 필요 있음.
	delete _Root;
}

bool RedBlackTree::Insert(int Data)
{
	if (_Root == nullptr)
	{
		_Root = new Node;
		// 루트 노드가 블랙인 이유
		// 1. 레드인 경우는 두번째 삽입에서 무조건 법칙 위반. (레드-블랙)
		// 2. 새로운 삽입이 레드인 이유는 블랙이면 무조건 법칙 위반.
		_Root->Color = NODE_COLOR::BLACK;
		_Root->Data = Data;
		_Root->Left = _Nil;
		_Root->Right = _Nil;

		return true;
	}

	Node* node = _Root;
	while (1)
	{
		if (Data < node->Data)
		{
			if (node->Left == _Nil)
			{
				Node* newNode = new Node;
				newNode->Parent = node;
				newNode->Data = Data;
				newNode->Left = _Nil;
				newNode->Right = _Nil;
				newNode->Color = NODE_COLOR::RED;
				node->Left = newNode;
				BalanceTree(newNode, true);
				break;
			}
			else
			{
				node = node->Left;
			}
		}
		else if (Data == node->Data)
		{
			return false;
		}
		else
		{
			if (node->Right == _Nil)
			{
				Node* newNode = new Node;
				newNode->Parent = node;
				newNode->Data = Data;
				newNode->Left = _Nil;
				newNode->Right = _Nil;
				newNode->Color = NODE_COLOR::RED;
				node->Right = newNode;
				BalanceTree(newNode, false);
				break;
			}
			else
			{
				node = node->Right;
			}
		}
	}

	return true;
}

bool RedBlackTree::Delete(int Data)
{
	// 하위 두개 있으면 오류날 확률 있음
	return Delete(_Root, nullptr, Data);
}

bool RedBlackTree::Find(int Data)
{
	return Find(_Root, Data);
}

void RedBlackTree::Print()
{
	const int maxDepth = GetMaxDepth();

	// 빈 트리임을 확인
	if (maxDepth == 0) {
		cout << " <empty tree>\n";
		return;
	}

	const RowList rowList = GetRowList(maxDepth);
	// 트리 Depth만큼 텍스트로 가공
	vector<string> formattedRows = FormatRow(rowList);
	// 왼쪽 Trim
	TrimRow(formattedRows);
	for (const auto& row : formattedRows)
	{
		cout << ' ' << row << '\n';
	}
}

bool RedBlackTree::Delete(Node* node, Node* Parent, int Data)
{
	return false;
}

bool RedBlackTree::Find(Node* node, int Data)
{
	if (node == nullptr)
		return false;

	bool leftResult, rightResult;

	leftResult = Find(node->Left, Data);
	if (node->Data == Data)
	{
		return true;
	}
	rightResult = Find(node->Right, Data);

	return leftResult || rightResult;
}

void RedBlackTree::BalanceTree(Node* node, bool Left)
{
	// 부모가 검정이면 밸런싱 종료
	if (node->Parent->Color == NODE_COLOR::BLACK)
		return;

	if (node->Parent == node->Parent->Parent->Left)
	{
		if (Left == false)
		{
			node->Parent = node->Parent->Parent;
			// 우선 부모를 내 왼쪽으로 가리킨다.
			node->Left = node->Parent->Left;
			node->Left->Parent = node;
			node->Parent->Left = node;

			node = node->Left;
			node->Left = _Nil;
			node->Right = _Nil;
		}

		if (node->Parent->Parent->Right->Color == NODE_COLOR::BLACK)
		{
			RightDirectionRotate(node);
			node = node->Parent;
			return;
		}

		node->Parent->Parent->Color = NODE_COLOR::RED;
		node->Parent->Color = NODE_COLOR::BLACK;
		node->Parent->Parent->Right->Color = NODE_COLOR::BLACK;

		node = node->Parent->Parent;

		// 밸런싱의 무한 반복을 이쪽에서 진행한다.
		BalanceProc(node);
	}
	else
	{
		if (Left == true)
		{
			node->Parent = node->Parent->Parent;
			// 우선 부모를 내 오른쪽으로 가리킨다.
			node->Right = node->Parent->Right;
			node->Right->Parent = node;
			node->Parent->Right = node;

			node = node->Right;
			node->Left = _Nil;
			node->Right = _Nil;
		}

		if (node->Parent->Parent->Left->Color == NODE_COLOR::BLACK)
		{
			LeftDirectionRotate(node);
			node = node->Parent;
			return;
		}

		node->Parent->Parent->Color = NODE_COLOR::RED;
		node->Parent->Color = NODE_COLOR::BLACK;
		node->Parent->Parent->Left->Color = NODE_COLOR::BLACK;

		node = node->Parent->Parent;

		// 밸런싱의 무한 반복을 이쪽에서 진행한다.
		BalanceProc(node);
	}
}

void RedBlackTree::RightDirectionRotate(Node* node)
{
	// 형제 부모 -> G부모
	node->Parent->Right->Parent = node->Parent->Parent;

	// G부모 왼쪽 -> 형제
	node->Parent->Parent->Left = node->Parent->Right;

	// 부모 R -> G부모
	node->Parent->Right = node->Parent->Parent;

	// G부모가 루트였다면 루트 바꿈 처리
	if (node->Parent->Parent == _Root)
	{
		_Root = node->Parent;
		_Root->Parent = nullptr;
	}
	// G부모가 루트가 아니면 부모가 더 있다고 생각할 수 있다.
	else
	{
		if (node->Parent->Parent->Parent->Left == node->Parent->Parent)
		{
			node->Parent->Parent->Parent->Left = node->Parent;
		}
		else
		{
			node->Parent->Parent->Parent->Right = node->Parent;
		}
		node->Parent->Parent = node->Parent->Parent->Parent;
	}

	// G부모의 부모 -> 부모
	node->Parent->Right->Parent = node->Parent;

	// 색깔 설정
	node->Parent->Color = NODE_COLOR::BLACK;
	node->Parent->Right->Color = NODE_COLOR::RED;
}

void RedBlackTree::LeftDirectionRotate(Node* node)
{
	// 형제 부모 -> G부모
	node->Parent->Left->Parent = node->Parent->Parent;

	// G부모 오른쪽 -> 형제
	node->Parent->Parent->Right = node->Parent->Left;

	// 부모 L -> G부모
	node->Parent->Left = node->Parent->Parent;

	// G부모가 루트였다면 루트 바꿈 처리
	if (node->Parent->Parent == _Root)
	{
		_Root = node->Parent;
		_Root->Parent = nullptr;
	}
	// G부모가 루트가 아니면 부모가 더 있다고 생각할 수 있다.
	else
	{
		if (node->Parent->Parent->Parent->Left == node->Parent->Parent)
		{
			node->Parent->Parent->Parent->Left = node->Parent;
		}
		else
		{
			node->Parent->Parent->Parent->Right = node->Parent;
		}
		node->Parent->Parent = node->Parent->Parent->Parent;
	}

	// G부모의 부모(이미 G부모는 부모의 L로 이동) -> 부모
	node->Parent->Left->Parent = node->Parent;

	// 색깔 설정
	node->Parent->Color = NODE_COLOR::BLACK;
	node->Parent->Left->Color = NODE_COLOR::RED;
}

void RedBlackTree::BalanceProc(Node* node)
{
	while (1)
	{
		// 루트면 return
		if (node == _Root)
			return;

		// 조건 만족
		if (node->Parent->Color == NODE_COLOR::BLACK)
			return;

		// 여기까지 온다면 부모가 Root 인데 Red 일 경우
		if (node->Parent == _Root)
		{
			_Root->Color = NODE_COLOR::BLACK;
			return;
		}

		// 부모가 Root 아니므로 다시 한번 G부모까지 볼 수 있다
		if (node->Parent == node->Parent->Parent->Left)
		{
			if (node->Parent->Parent->Right->Color == NODE_COLOR::BLACK)
			{
				RightDirectionRotate(node);
				node = node->Parent;
				return;
			}
			else
			{
				node->Parent->Parent->Color = NODE_COLOR::RED;
				node->Parent->Color = NODE_COLOR::BLACK;
				node->Parent->Parent->Right->Color = NODE_COLOR::BLACK;

				node = node->Parent->Parent;
			}
		}
		else
		{
			if (node->Parent->Parent->Left->Color == NODE_COLOR::BLACK)
			{
				LeftDirectionRotate(node);
				node = node->Parent;
				return;
			}
			else
			{
				node->Parent->Parent->Color = NODE_COLOR::RED;
				node->Parent->Color = NODE_COLOR::BLACK;
				node->Parent->Parent->Left->Color = NODE_COLOR::BLACK;

				node = node->Parent->Parent;
			}
		}
	}
}

int RedBlackTree::GetMaxDepth() const
{
	int maxLevel = 0;

	if (_Root == nullptr)
		return maxLevel;

	maxLevel = _Root->GetMaxDepth();

	return maxLevel;
}

RowList RedBlackTree::GetRowList(int maxDepth) const
{
	RowList rowList;

	vector<Node*> traversalStack;
	vector<vector<Node*>> rows;
	if (_Root == nullptr)
		return rowList;

	Node* node = _Root;
	rows.resize(maxDepth);
	int depth = 0;
	for (;;) {
		// 제일 깊은 노드는 null or 단말
		if (depth == maxDepth - 1) {
			rows[depth].push_back(node);
			if (depth == 0)
				break;
			--depth;
			continue;
		}

		// 처음 방문이라면 왼쪽 노드
		if (traversalStack.size() == depth) {
			rows[depth].push_back(node);
			traversalStack.push_back(node);
			if (node != nullptr)
				node = node->Left;
			++depth;
			continue;
		}

		// 하위가 하나라면 오른쪽 노드도 탐색
		if (rows[depth + 1].size() % 2) {
			node = traversalStack.back();
			if (node != nullptr)
				node = node->Right;
			++depth;
			continue;
		}

		// 루프 탈출
		if (depth == 0)
			break;

		traversalStack.pop_back();
		node = traversalStack.back();
		--depth;
	}

	// 각 행마다 텍스트로 가공되기 위해 준비
	for (const auto& row : rows) {
		rowList.emplace_back();
		for (Node* pn : row) {
			Cell cell;
			if (pn) {
				if (pn == _Nil)
				{
					cell.Value = "N";
				}
				else
				{
					cell.Value = to_string(pn->Data);
					if (pn->Color == NODE_COLOR::BLACK)
						cell.Value += " B";
					else
						cell.Value += " R";
				}
				cell.Present = true;
				rowList.back().push_back(cell);
			}
			else {
				rowList.back().push_back(cell);
			}
		}
	}

	return rowList;
}

vector<string> RedBlackTree::FormatRow(const RowList& rowList) const
{
	size_t cellWidth = 0;
	for (const auto& row : rowList)
	{
		for (const auto& cell : row)
		{
			if (cell.Present && cell.Value.length() > cellWidth)
			{
				cellWidth = cell.Value.length();
			}
		}
	}

	if (cellWidth % 2 == 0)
		cellWidth++;

	if (cellWidth < 3) 
		cellWidth = 3;

	vector<string> formattedRows;

	size_t rowCount = rowList.size();

	int rowElementCount = 1i64 << (rowCount - 1);

	size_t left_pad = 0;

	for (int r = 0; r < rowCount; ++r) {
		const auto& cd_row = rowList[rowCount - r - 1];

		size_t space = (1i64 << r) * (cellWidth + 1) / 2 - 1;
		string row;

		for (int c = 0; c < rowElementCount; ++c) {
			row += string(c ? left_pad * 2 + 1 : left_pad, ' ');
			if (cd_row[c].Present) 
			{
				const string& valstr = cd_row[c].Value;
				size_t long_padding = cellWidth - valstr.length();
				size_t short_padding = long_padding / 2;
				long_padding -= short_padding;
				row += string(c % 2 ? short_padding : long_padding, ' ');
				row += valstr;
				row += string(c % 2 ? long_padding : short_padding, ' ');
			}
			else 
			{
				row += string(cellWidth, ' ');
			}
		}
		formattedRows.push_back(row);

		if (rowElementCount == 1) 
			break;

		size_t left_space = space + 1;
		size_t right_space = space - 1;
		for (int sr = 0; sr < space; ++sr) {
			string row;
			for (int c = 0; c < rowElementCount; ++c) {
				if (c % 2 == 0) {
					row += string(c ? left_space * 2 + 1 : left_space, ' ');
					row += cd_row[c].Present ? '/' : ' ';
					row += string(right_space + 1, ' ');
				}
				else {
					row += string(right_space, ' ');
					row += cd_row[c].Present ? '\\' : ' ';
				}
			}
			formattedRows.push_back(row);
			++left_space;
			--right_space;
		}
		left_pad += space + 1;
		rowElementCount /= 2;
	}

	reverse(formattedRows.begin(), formattedRows.end());

	return formattedRows;
}

void RedBlackTree::TrimRow(vector<string>& rows)
{
	if (rows.size() == 0)
		return;

	auto min_space = rows.front().length();
	for (const auto& row : rows)
	{
		auto i = row.find_first_not_of(' ');
		if (i == string::npos)
			i = row.length();
		if (i == 0)
			return;
		if (i < min_space)
			min_space = i;
	}
	for (auto& row : rows)
	{
		row.erase(0, min_space);
	}
}