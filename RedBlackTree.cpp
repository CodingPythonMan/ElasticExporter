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
}

RedBlackTree::~RedBlackTree()
{
	DeleteDestructor(_Root);
	// Nil �� ���� �������ش�.
	delete _Nil;
}

bool RedBlackTree::Insert(int Data)
{
	if (_Root == _Nil)
	{
		_Root = new Node;
		// ��Ʈ ��尡 ���� ����
		// 1. ������ ���� �ι�° ���Կ��� ������ ��Ģ ����. (����-��)
		// 2. ���ο� ������ ������ ������ ���̸� ������ ��Ģ ����.
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
	// ��ȸ �ڵ�
	return Delete(_Root, Data);
}

bool RedBlackTree::Find(int Data)
{
	return Find(_Root, Data);
}

void RedBlackTree::Print()
{
	const int maxDepth = GetMaxDepth();

	// �� Ʈ������ Ȯ��
	if (maxDepth == 0) {
		cout << " <empty tree>\n";
		return;
	}

	const RowList rowList = GetRowList(maxDepth);
	// Ʈ�� Depth��ŭ �ؽ�Ʈ�� ����
	vector<string> formattedRows = FormatRow(rowList);
	// ���� Trim
	TrimRow(formattedRows);
	for (const auto& row : formattedRows)
	{
		cout << ' ' << row << '\n';
	}
}

bool RedBlackTree::Delete(Node* node, int Data)
{
	if (node == _Nil)
		return false;

	bool leftResult, rightResult;
	leftResult = Delete(node->Left, Data);
	// �����Ϳ� ���� �� ó���� �� ���� �ִ��� Ȯ�� �ʿ�
	if (Data == node->Data)
	{
		// �ڽ� �Ѵ� ���� ���
		if (node->Left != _Nil && node->Right != _Nil)
		{
			// ������ �� ���������� �����ϰ�, �ش� node ���� �� ����.
			Node* thisNode = node;
			node = node->Left;
			while (node->Right != _Nil)
			{
				node = node->Right;
			}
			thisNode->Data = node->Data;
			// ���⼭ return ���� �ʴ� ������ node �� ������ �� �Ʒ� ���� ���.
		}

		// Root �� Parent ���� ������ �ʿ䰡 ����.
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

		// ���� �ڽ��� �ִ� ���
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
		}
		// ���� �ڽ��� �ִ� ���
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
		}
		// �ڽ��� ���� ���
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
		}
		delete node;
		return true;
	}
	rightResult = Delete(node->Right, Data);

	return leftResult || rightResult;
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

void RedBlackTree::DeleteDestructor(Node* node)
{
}

void RedBlackTree::InsertBalance(Node* node)
{
	// �θ� �����̸� �뷱�� ����
	if (node->Parent->Color == NODE_COLOR::BLACK)
		return;

	if (node->Parent == node->Parent->Parent->Left)
	{
		if (node->Parent->Parent->Right->Color == NODE_COLOR::BLACK)
		{
			if (node == node->Parent->Right)
			{
				node = RightToParent(node);
				node->Left = _Nil;
				node->Right = _Nil;
			}

			RightDirectionRotate(node);
			node = node->Parent;
			return;
		}

		node->Parent->Parent->Color = NODE_COLOR::RED;
		node->Parent->Color = NODE_COLOR::BLACK;
		node->Parent->Parent->Right->Color = NODE_COLOR::BLACK;

		node = node->Parent->Parent;

		// �뷱���� ���� �ݺ��� ���ʿ��� �����Ѵ�.
		BalanceProc(node);
	}
	else
	{
		if (node->Parent->Parent->Left->Color == NODE_COLOR::BLACK)
		{
			if (node == node->Parent->Left)
			{
				node = LeftToParent(node);
				node->Left = _Nil;
				node->Right = _Nil;
			}

			LeftDirectionRotate(node);
			node = node->Parent;
			return;
		}

		node->Parent->Parent->Color = NODE_COLOR::RED;
		node->Parent->Color = NODE_COLOR::BLACK;
		node->Parent->Parent->Left->Color = NODE_COLOR::BLACK;

		node = node->Parent->Parent;

		// �뷱���� ���� �ݺ��� ���ʿ��� �����Ѵ�.
		BalanceProc(node);
	}
}

void RedBlackTree::DeleteBalance(Node* node)
{
	if (node == _Nil)
		return;

	// �Ҹ��ڴ� ���� ����
	DeleteDestructor(node->Left);
	DeleteDestructor(node->Right);
	delete node;
}

Node* RedBlackTree::RightToParent(Node* node)
{
	node->Parent = node->Parent->Parent;
	// �켱 �θ� �� �������� ����Ų��.
	node->Left = node->Parent->Left;
	node->Left->Parent = node;
	node->Parent->Left = node;
	
	return node->Left;
}

Node* RedBlackTree::LeftToParent(Node* node)
{
	node->Parent = node->Parent->Parent;
	// �켱 �θ� �� ���������� ����Ų��.
	node->Right = node->Parent->Right;
	node->Right->Parent = node;
	node->Parent->Right = node;

	return node->Right;
}

void RedBlackTree::RightDirectionRotate(Node* node)
{
	// ���� �θ� -> G�θ�
	node->Parent->Right->Parent = node->Parent->Parent;

	// G�θ� ���� -> ����
	node->Parent->Parent->Left = node->Parent->Right;

	// �θ� R -> G�θ�
	node->Parent->Right = node->Parent->Parent;

	// G�θ� ��Ʈ���ٸ� ��Ʈ �ٲ� ó��
	if (node->Parent->Parent == _Root)
	{
		_Root = node->Parent;
		_Root->Parent = nullptr;
	}
	// G�θ� ��Ʈ�� �ƴϸ� �θ� �� �ִٰ� ������ �� �ִ�.
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

	// G�θ��� �θ� -> �θ�
	node->Parent->Right->Parent = node->Parent;

	// ���� ����
	node->Parent->Color = NODE_COLOR::BLACK;
	node->Parent->Right->Color = NODE_COLOR::RED;
}

void RedBlackTree::LeftDirectionRotate(Node* node)
{
	// ���� �θ� -> G�θ�
	node->Parent->Left->Parent = node->Parent->Parent;

	// G�θ� ������ -> ����
	node->Parent->Parent->Right = node->Parent->Left;

	// �θ� L -> G�θ�
	node->Parent->Left = node->Parent->Parent;

	// G�θ� ��Ʈ���ٸ� ��Ʈ �ٲ� ó��
	if (node->Parent->Parent == _Root)
	{
		_Root = node->Parent;
		_Root->Parent = nullptr;
	}
	// G�θ� ��Ʈ�� �ƴϸ� �θ� �� �ִٰ� ������ �� �ִ�.
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

	// G�θ��� �θ�(�̹� G�θ�� �θ��� L�� �̵�) -> �θ�
	node->Parent->Left->Parent = node->Parent;

	// ���� ����
	node->Parent->Color = NODE_COLOR::BLACK;
	node->Parent->Left->Color = NODE_COLOR::RED;
}

void RedBlackTree::BalanceProc(Node* node)
{
	while (1)
	{
		// ��Ʈ�� return
		if (node == _Root)
			return;

		// ���� ����
		if (node->Parent->Color == NODE_COLOR::BLACK)
			return;

		// ������� �´ٸ� �θ� Root �ε� Red �� ���
		if (node->Parent == _Root)
		{
			_Root->Color = NODE_COLOR::BLACK;
			return;
		}

		// �θ� Root �ƴϹǷ� �ٽ� �ѹ� G�θ���� �� �� �ִ�
		if (node->Parent == node->Parent->Parent->Left)
		{
			if (node->Parent->Parent->Right->Color == NODE_COLOR::BLACK)
			{
				if (node == node->Parent->Right)
				{
					node = RightToParent(node);
					node->Left = _Nil;
					node->Right = _Nil;
				}

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
				if (node == node->Parent->Left)
				{
					node = LeftToParent(node);
					node->Left = _Nil;
					node->Right = _Nil;
				}

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
		// ���� ���� ���� null or �ܸ�
		if (depth == maxDepth - 1) {
			rows[depth].push_back(node);
			if (depth == 0)
				break;
			--depth;
			continue;
		}

		// ó�� �湮�̶�� ���� ���
		if (traversalStack.size() == depth) {
			rows[depth].push_back(node);
			traversalStack.push_back(node);
			if (node != nullptr)
				node = node->Left;
			++depth;
			continue;
		}

		// ������ �ϳ���� ������ ��嵵 Ž��
		if (rows[depth + 1].size() % 2) {
			node = traversalStack.back();
			if (node != nullptr)
				node = node->Right;
			++depth;
			continue;
		}

		// ���� Ż��
		if (depth == 0)
			break;

		traversalStack.pop_back();
		node = traversalStack.back();
		--depth;
	}

	// �� �ึ�� �ؽ�Ʈ�� �����Ǳ� ���� �غ�
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