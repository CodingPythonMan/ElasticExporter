#include "RedBlackTree.h"
#include <iostream>

RedBlackTree::RedBlackTree()
{
	_Nil = new Node;
	_Nil->Color = NODE_COLOR::BLACK;
	_Nil->Parent = nullptr;
	_Nil->Left = nullptr;
	_Nil->Right = nullptr;
	_Root = _Nil;

#ifdef _DEBUG
	_Index = 0;
#endif
}

RedBlackTree::~RedBlackTree()
{
	DeleteDestructor(_Root);
	// Nil 은 따로 삭제해준다.
	delete _Nil;
}

bool RedBlackTree::Insert(int Data)
{
	if (_Root == _Nil)
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
				InsertBalance(newNode);
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
				InsertBalance(newNode);
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
	if (_Root == _Nil)
		return false;

	Node* node = _Root;
	while (1)
	{
		if (Data < node->Data)
		{
			if (node->Left == _Nil)
				break;
			else
				node = node->Left;
		}
		else if (Data == node->Data)
		{
			// 자식 둘다 있을 경우
			if (node->Left != _Nil && node->Right != _Nil)
			{
				// 왼쪽의 맨 오른쪽으로 접근하고, 해당 node 설정 후 삭제.
				Node* thisNode = node;
				node = node->Left;
				while (node->Right != _Nil)
					node = node->Right;
				thisNode->Data = node->Data;
				// 여기서 return 되지 않는 이유는 node 는 지워질 때 아래 사항 고려.
			}

			// Root 면 Parent 관련 설정할 필요가 없다.
			if (node == _Root)
			{
				if (node->Left != _Nil)
				{
					_Root = node->Left;
				}
				else if (node->Right != _Nil)
				{
					_Root = node->Right;
				}
				else
				{
					_Root = _Nil;
				}
				delete node;
				return true;
			}

			Node* ChildNode;
			NODE_COLOR nodeColor = node->Color;
			// 왼쪽 자식이 있는 경우
			if (node->Left != _Nil)
			{
				if (node->Parent->Left == node)
				{
					node->Parent->Left = node->Left;
				}
				else
				{
					node->Parent->Right = node->Left;
				}
				node->Left->Parent = node->Parent;
				ChildNode = node->Left;
			}
			// 오른 자식이 있는 경우
			else if (node->Right != _Nil)
			{
				if (node->Parent->Left == node)
				{
					node->Parent->Left = node->Right;
				}
				else
				{
					node->Parent->Right = node->Right;
				}
				node->Right->Parent = node->Parent;
				ChildNode = node->Right;
			}
			// 자식이 없는 경우
			else
			{
				if (node->Parent->Left == node)
				{
					node->Parent->Left = _Nil;
				}
				else
				{
					node->Parent->Right = _Nil;
				}
				ChildNode = _Nil;
				ChildNode->Parent = node->Parent;
			}
			delete node;
			if (nodeColor == NODE_COLOR::BLACK)
				DeleteBalance(ChildNode);

			return true;
		}
		else
		{
			if (node->Right == _Nil)
				break;
			else
				node = node->Right;
		}
	}

	return false;
}

bool RedBlackTree::Find(int Data)
{
	if (_Root == _Nil)
		return false;

	Node* node = _Root;
	while (1)
	{
		if (Data < node->Data)
		{
			if (node->Left == _Nil)
				break;
			else
				node = node->Left;
		}
		else if (Data == node->Data)
			return true;
		else
		{
			if (node->Right == _Nil)
				break;
			else
				node = node->Right;
		}
	}

	return false;
}

void RedBlackTree::Print()
{
	const int maxDepth = GetMaxDepth();

	// 빈 트리임을 확인
	if (maxDepth == 0) {
		cout << "[Empty Tree]\n";
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

void RedBlackTree::DeleteDestructor(Node* node)
{
	if (node == _Nil)
		return;

	// 소멸자는 후위 연산
	DeleteDestructor(node->Left);
	DeleteDestructor(node->Right);
	delete node;
}

void RedBlackTree::InsertBalance(Node* node)
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
				if (node == node->Parent->Right)
				{
					LeftDirectionRotate(node);
					node = node->Left;
				}
				
				RightDirectionRotate(node->Parent);
				// 색깔 설정
				node->Parent->Color = NODE_COLOR::BLACK;
				node->Parent->Right->Color = NODE_COLOR::RED;
				return;
			}
			else
			{
				node->Parent->Parent->Right->Color = NODE_COLOR::BLACK;
			}
		}
		else
		{
			if (node->Parent->Parent->Left->Color == NODE_COLOR::BLACK)
			{
				if (node == node->Parent->Left)
				{
					RightDirectionRotate(node);
					node = node->Right;
				}

				LeftDirectionRotate(node->Parent);
				// 색깔 설정
				node->Parent->Color = NODE_COLOR::BLACK;
				node->Parent->Left->Color = NODE_COLOR::RED;
				return;
			}
			else
			{
				node->Parent->Parent->Left->Color = NODE_COLOR::BLACK;
			}
		}

		node->Parent->Parent->Color = NODE_COLOR::RED;
		node->Parent->Color = NODE_COLOR::BLACK;
		node = node->Parent->Parent;
	}
}

void RedBlackTree::DeleteBalance(Node* node)
{
	Node* Parent = node->Parent;
	while (1)
	{
		// 루트까지 올라왔다면 Root 를 블랙으로 만들고 종료
		if (node == _Root)
		{
			_Root->Color = NODE_COLOR::BLACK;
			return;
		}
			
		// 2.1 조건
		if (node->Color == NODE_COLOR::RED)
		{
			node->Color = NODE_COLOR::BLACK;
			return;
		}
			
		// 부모 기준 왼쪽
		Node* Sibling;
		if (Parent->Left == node)
		{
			Sibling = Parent->Right;

			// 형제 레드
			if (Sibling->Color == NODE_COLOR::RED)
			{
				// 형제 블랙
				Sibling->Color = NODE_COLOR::BLACK;
				// 좌회전 해야 됨.
				LeftDirectionRotate(Sibling);
				Parent->Color = NODE_COLOR::RED;

				node = Parent->Left;
			}
			// 형제 블랙
			else
			{
				// 형제의 양쪽 자식이 블랙
				if (Sibling->Left->Color == NODE_COLOR::BLACK
					&& Sibling->Right->Color == NODE_COLOR::BLACK)
				{
					Sibling->Color = NODE_COLOR::RED;
					node = Parent;
					Parent = node->Parent;
				}
				// 왼쪽 자식 레드, 오른 자식 블랙
				else if(Sibling->Right->Color == NODE_COLOR::BLACK)
				{
					Sibling->Left->Color = NODE_COLOR::BLACK;
					Sibling->Color = NODE_COLOR::RED;

					RightDirectionRotate(Sibling->Left);
				}
				// 오른쪽 자식 레드, 양쪽 레드
				else
				{
					Sibling->Color = Parent->Color;
					Parent->Color = NODE_COLOR::BLACK;
					Sibling->Right->Color = NODE_COLOR::BLACK;

					LeftDirectionRotate(Sibling);
					return;
				}
			}
		}
		// 부모 기준 오른쪽
		else
		{
			Sibling = Parent->Left;

			if (Sibling->Color == NODE_COLOR::RED)
			{
				// 형제 블랙
				Sibling->Color = NODE_COLOR::BLACK;
				// 우회전 해야 됨.
				RightDirectionRotate(Sibling);
				Parent->Color = NODE_COLOR::RED;
				
				node = Parent->Right;
				
			}
			// 형제 블랙
			else
			{
				// 형제의 양쪽 자식이 블랙
				if (Sibling->Left->Color == NODE_COLOR::BLACK
					&& Sibling->Right->Color == NODE_COLOR::BLACK)
				{
					Sibling->Color = NODE_COLOR::RED;
					node = Parent;
					Parent = node->Parent;
				}
				// 오른 자식 레드, 왼쪽 자식 블랙
				else if (Sibling->Left->Color == NODE_COLOR::BLACK)
				{
					Sibling->Right->Color = NODE_COLOR::BLACK;
					Sibling->Color = NODE_COLOR::RED;

					LeftDirectionRotate(Sibling->Right);
				}
				// 왼쪽 자식 레드, 양쪽 레드
				else
				{
					Sibling->Color = Parent->Color;
					Parent->Color = NODE_COLOR::BLACK;
					Sibling->Left->Color = NODE_COLOR::BLACK;

					RightDirectionRotate(Sibling);
					return;
				}
			}
		}
	}
}

void RedBlackTree::LineToParent(Node* node)
{
	if (node->Parent == _Root)
	{
		_Root = node;
		_Root->Parent = nullptr;
	}
	else
	{
		if (node->Parent->Parent->Left == node->Parent)
		{
			node->Parent->Parent->Left = node;
		}
		else
		{
			node->Parent->Parent->Right = node;
		}
		node->Parent = node->Parent->Parent;
	}
}

void RedBlackTree::RightDirectionRotate(Node* node)
{
	// 내 부모는 오른 자식의 부모가 된다.
	node->Right->Parent = node->Parent;
	// 내 오른쪽 자식은 부모의 왼쪽이 된다.
	node->Parent->Left = node->Right;
	// 부모가 오른 자식이 된다.
	node->Right = node->Parent;

	LineToParent(node);

	// 내 오른쪽의 부모가 된다.
	node->Right->Parent = node;
}

void RedBlackTree::LeftDirectionRotate(Node* node)
{
	// 내 부모는 왼쪽 자식의 부모가 된다.
	node->Left->Parent = node->Parent;
	// 왼쪽으로 넘어갈 부모가 오른 자식으로 내 왼쪽 자식을 갖는다.
	node->Parent->Right = node->Left;
	// 부모가 왼쪽 자식이 된다.
	node->Left = node->Parent;

	// 부모의 부모 설정이 끝나야 다음 줄 가능
	LineToParent(node);

	// 내 왼쪽의 부모가 된다.
	node->Left->Parent = node;
}

int RedBlackTree::GetMaxDepth() const
{
	int maxLevel = 0;

	if (_Root == _Nil)
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

void RedBlackTree::ReliableTest(const set<int>& ReliableSet)
{
	_ReliableSet = ReliableSet;
	_Iter = _ReliableSet.begin();
	_Index = 0;
	cout << "[Red - Black Tree Test]\n";
	cout << "[Element Count] : " << _ReliableSet.size() << "\n";
	if (Test(_Root) == true)
	{
		cout << "[Test Result] : Error.\n";
	}
	else
	{
		cout << "[Test Result] : Reliable Test 이상 없음.\n";
	}
}

bool RedBlackTree::Test(Node* node)
{
	if (node == _Nil)
		return false;

	bool leftResult = Test(node->Left);
	if (node->Data == *_Iter)
	{
		++_Iter;
		_Index++;
	}
	else
	{
		cout << "Index : " << _Index << ", Error!!!\n";
		cout << "Data : " << node->Data << ", Error!!!\n";
		__debugbreak();
		return true;
	}
	bool rightResult = Test(node->Right);

	return leftResult || rightResult;
}