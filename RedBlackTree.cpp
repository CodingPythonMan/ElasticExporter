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

	// Ʈ�� �� ��� ��� ���� ���� ���� �ʿ� ����.
	delete _Root;
}

bool RedBlackTree::Insert(int Data)
{
	if (_Root == nullptr)
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
	// ���� �ΰ� ������ ������ Ȯ�� ����
	return Delete(_Root, nullptr, Data);
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
	// �θ� �����̸� �뷱�� ����
	if (node->Parent->Color == NODE_COLOR::BLACK)
		return;

	if (node->Parent == node->Parent->Parent->Left)
	{
		if (Left == false)
		{
			node->Parent = node->Parent->Parent;
			// �켱 �θ� �� �������� ����Ų��.
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

		while (1)
		{
			node->Parent->Parent->Color = NODE_COLOR::RED;
			node->Parent->Color = NODE_COLOR::BLACK;
			node->Parent->Parent->Right->Color = NODE_COLOR::BLACK;

			node = node->Parent->Parent;

			// ��Ʈ�� return
			if (node == _Root)
				break;

			// ���� ����
			if (node->Parent->Color == NODE_COLOR::BLACK)
				break;

			// ������� �´ٸ� �θ� Root �ε� Red �� ���
			if (node->Parent == _Root)
			{
				_Root->Color = NODE_COLOR::BLACK;
				break;
			}

			// �θ� Root �ƴϹǷ� �ٽ� �ѹ� G�θ���� �� �� �ִ�
			if (node->Parent->Parent->Right->Color == NODE_COLOR::BLACK)
			{
				RightDirectionRotate(node);
				node = node->Parent;
				return;
			}
		}
	}
	else
	{
		if (Left == true)
		{
			node->Parent = node->Parent->Parent;
			// �켱 �θ� �� ���������� ����Ų��.
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

		while (1)
		{
			node->Parent->Parent->Color = NODE_COLOR::RED;
			node->Parent->Color = NODE_COLOR::BLACK;
			node->Parent->Parent->Left->Color = NODE_COLOR::BLACK;

			node = node->Parent->Parent;

			// ��Ʈ�� return
			if (node == _Root)
				break;

			// ���� ����
			if (node->Parent->Color == NODE_COLOR::BLACK)
				break;

			// ������� �´ٸ� �θ� Root �ε� Red �� ���
			if (node->Parent == _Root)
			{
				_Root->Color = NODE_COLOR::BLACK;
				break;
			}

			// �θ� Root �ƴϹǷ� �ٽ� �ѹ� G�θ���� �� �� �ִ�
			if (node->Parent->Parent->Left->Color == NODE_COLOR::BLACK)
			{
				LeftDirectionRotate(node);
				node = node->Parent;
				return;
			}
		}
	}
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
	size_t cell_width = 0;
	for (const auto& row_disp : rowList)
	{
		for (const auto& cd : row_disp)
		{
			if (cd.Present && cd.Value.length() > cell_width)
			{
				cell_width = cd.Value.length();
			}
		}
	}

	if (cell_width % 2 == 0)
		cell_width++;

	if (cell_width < 3) cell_width = 3;

	vector<string> formatted_rows;

	size_t row_count = rowList.size();

	int row_elem_count = 1i64 << (row_count - 1);

	size_t left_pad = 0;


	for (int r = 0; r < row_count; ++r) {
		const auto& cd_row = rowList[row_count - r - 1];

		size_t space = (1i64 << r) * (cell_width + 1) / 2 - 1;
		string row;

		for (int c = 0; c < row_elem_count; ++c) {
			row += string(c ? left_pad * 2 + 1 : left_pad, ' ');
			if (cd_row[c].Present) {
				const string& valstr = cd_row[c].Value;
				size_t long_padding = cell_width - valstr.length();
				size_t short_padding = long_padding / 2;
				long_padding -= short_padding;
				row += string(c % 2 ? short_padding : long_padding, ' ');
				row += valstr;
				row += string(c % 2 ? long_padding : short_padding, ' ');
			}
			else {
				// This position is empty, Nodeless...
				row += string(cell_width, ' ');
			}
		}
		formatted_rows.push_back(row);

		if (row_elem_count == 1) break;

		size_t left_space = space + 1;
		size_t right_space = space - 1;
		for (int sr = 0; sr < space; ++sr) {
			string row;
			for (int c = 0; c < row_elem_count; ++c) {
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
			formatted_rows.push_back(row);
			++left_space;
			--right_space;
		}
		left_pad += space + 1;
		row_elem_count /= 2;
	}

	reverse(formatted_rows.begin(), formatted_rows.end());

	return formatted_rows;
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