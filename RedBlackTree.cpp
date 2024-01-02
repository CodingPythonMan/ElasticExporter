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
			// �ڽ� �Ѵ� ���� ���
			if (node->Left != _Nil && node->Right != _Nil)
			{
				// ������ �� ���������� �����ϰ�, �ش� node ���� �� ����.
				Node* thisNode = node;
				node = node->Left;
				while (node->Right != _Nil)
					node = node->Right;
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

			Node* ChildNode;
			NODE_COLOR nodeColor = node->Color;
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
				ChildNode = node->Left;
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
				ChildNode = node->Right;
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

	// �� Ʈ������ Ȯ��
	if (maxDepth == 0) {
		cout << "[Empty Tree]\n";
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

void RedBlackTree::DeleteDestructor(Node* node)
{
	if (node == _Nil)
		return;

	// �Ҹ��ڴ� ���� ����
	DeleteDestructor(node->Left);
	DeleteDestructor(node->Right);
	delete node;
}

void RedBlackTree::InsertBalance(Node* node)
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
					LeftDirectionRotate(node);
					node = node->Left;
				}
				
				RightDirectionRotate(node->Parent);
				// ���� ����
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
				// ���� ����
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
		// ��Ʈ���� �ö�Դٸ� Root �� ������ ����� ����
		if (node == _Root)
		{
			_Root->Color = NODE_COLOR::BLACK;
			return;
		}
			
		// 2.1 ����
		if (node->Color == NODE_COLOR::RED)
		{
			node->Color = NODE_COLOR::BLACK;
			return;
		}
			
		// �θ� ���� ����
		Node* Sibling;
		if (Parent->Left == node)
		{
			Sibling = Parent->Right;

			// ���� ����
			if (Sibling->Color == NODE_COLOR::RED)
			{
				// ���� ��
				Sibling->Color = NODE_COLOR::BLACK;
				// ��ȸ�� �ؾ� ��.
				LeftDirectionRotate(Sibling);
				Parent->Color = NODE_COLOR::RED;

				node = Parent->Left;
			}
			// ���� ��
			else
			{
				// ������ ���� �ڽ��� ��
				if (Sibling->Left->Color == NODE_COLOR::BLACK
					&& Sibling->Right->Color == NODE_COLOR::BLACK)
				{
					Sibling->Color = NODE_COLOR::RED;
					node = Parent;
					Parent = node->Parent;
				}
				// ���� �ڽ� ����, ���� �ڽ� ��
				else if(Sibling->Right->Color == NODE_COLOR::BLACK)
				{
					Sibling->Left->Color = NODE_COLOR::BLACK;
					Sibling->Color = NODE_COLOR::RED;

					RightDirectionRotate(Sibling->Left);
				}
				// ������ �ڽ� ����, ���� ����
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
		// �θ� ���� ������
		else
		{
			Sibling = Parent->Left;

			if (Sibling->Color == NODE_COLOR::RED)
			{
				// ���� ��
				Sibling->Color = NODE_COLOR::BLACK;
				// ��ȸ�� �ؾ� ��.
				RightDirectionRotate(Sibling);
				Parent->Color = NODE_COLOR::RED;
				
				node = Parent->Right;
				
			}
			// ���� ��
			else
			{
				// ������ ���� �ڽ��� ��
				if (Sibling->Left->Color == NODE_COLOR::BLACK
					&& Sibling->Right->Color == NODE_COLOR::BLACK)
				{
					Sibling->Color = NODE_COLOR::RED;
					node = Parent;
					Parent = node->Parent;
				}
				// ���� �ڽ� ����, ���� �ڽ� ��
				else if (Sibling->Left->Color == NODE_COLOR::BLACK)
				{
					Sibling->Right->Color = NODE_COLOR::BLACK;
					Sibling->Color = NODE_COLOR::RED;

					LeftDirectionRotate(Sibling->Right);
				}
				// ���� �ڽ� ����, ���� ����
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
	// �� �θ�� ���� �ڽ��� �θ� �ȴ�.
	node->Right->Parent = node->Parent;
	// �� ������ �ڽ��� �θ��� ������ �ȴ�.
	node->Parent->Left = node->Right;
	// �θ� ���� �ڽ��� �ȴ�.
	node->Right = node->Parent;

	LineToParent(node);

	// �� �������� �θ� �ȴ�.
	node->Right->Parent = node;
}

void RedBlackTree::LeftDirectionRotate(Node* node)
{
	// �� �θ�� ���� �ڽ��� �θ� �ȴ�.
	node->Left->Parent = node->Parent;
	// �������� �Ѿ �θ� ���� �ڽ����� �� ���� �ڽ��� ���´�.
	node->Parent->Right = node->Left;
	// �θ� ���� �ڽ��� �ȴ�.
	node->Left = node->Parent;

	// �θ��� �θ� ������ ������ ���� �� ����
	LineToParent(node);

	// �� ������ �θ� �ȴ�.
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
		cout << "[Test Result] : Reliable Test �̻� ����.\n";
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