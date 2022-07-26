#include <iostream>
#include <queue>
using namespace std;

struct Node
{
	int key;
	Node* left;
	Node* right;
}; typedef Node* Tree;

void Init(Tree&);
Node* CreateNode(int);
void Insert(Tree&, int);
void Nhap(Tree&);
void PrintLNR(Tree);
void PrintLevel(Tree);
int FindX(Tree, int);
void FindSubs(Node*&, Tree&);
void RemoveX(Tree&, int);
int ktNguyenTo(int);
void RemoveSoNT(Tree&);
int countNodes(Tree);
int count2Sons(Tree);
int isLeaf(Node*);
int countLeaves(Tree);
int GetHeight(Tree);
void Draw(Tree);
int NodeToiX(Tree, int);
int TinhDuongDi(Tree, int, int);
int MucX(Tree, int);
int MucNhieuLa(Tree);
void InNutSoNutTraiBangSoNutPhai(Tree);
int keyBoX(Tree, int);

int main()
{
	Tree myTree;
	Init(myTree);
	Nhap(myTree);
	Draw(myTree);
	cout << "\nHeight: " << GetHeight(myTree);
	cout << "\nNode: " << countNodes(myTree);
	cout << "\nLeaf: " << countLeaves(myTree);
	cout << "\nNode with 2 sons: " << count2Sons(myTree) << endl;
	//int x, y, del;
	//cout << "\nDelete? ";
	//cin >> del;
	//RemoveX(myTree, del);
	//Draw(myTree);
	//cout << "\nNhap x: ";
	//cin >> x;// >> y;
	//cout << "Key cua bo x la: " << keyBoX(myTree, x);
	//cout << "Chieu dai duong di: " << TinhDuongDi(myTree, x, y) << endl;
	//InNutSoNutTraiBangSoNutPhai(myTree);
	RemoveSoNT(myTree);
	Draw(myTree);
	return 0;
}

void Init(Tree& tree)
{
	tree = NULL;
}
Node* CreateNode(int data)
{
	Node* p = new Node;
	p->key = data;
	p->left = NULL;
	p->right = NULL;
	return p;
}
void Insert(Tree& t, int x)
{
	if (t == NULL)
		t = CreateNode(x);
	else if (x <= t->key)
		Insert(t->left, x);
	else
		Insert(t->right, x);
}
void Nhap(Tree& tree)
{
	int soNode;
	cin >> soNode;
	srand(time(NULL));
	for (int i = 0; i < soNode; i++)
	{
		int randValue = (int)rand() % 100;
		Insert(tree, randValue);
	}
}
void PrintLNR(Tree t)
{
	if (t != NULL)
	{
		PrintLNR(t->left);
		cout << t->key << " ";
		PrintLNR(t->right);
	}
}

void PrintLevel(Tree t)
{
	if (t != NULL)
	{
		queue<Tree> q;
		q.push(t);
		while (!q.empty())
		{
			Tree current = q.front();
			cout << current->key << " ";
			if (current->left != NULL)
				q.push(current->left);
			if (current->right != NULL)
				q.push(current->right);
			q.pop();
		}
	}
}
int MucX(Tree t, int x)
{
	if (t == NULL || t->key == x)
		return 0;
	else if (t->key < x)
		return 1 + MucX(t->right, x);
	else
		return 1 + MucX(t->left, x);
}
int MucNhieuLa(Tree t)
{
	int maxLa = 0, demLa = 0;
	int level = 0, maxLevel = 0;
	if (t != NULL)
	{
		queue<Tree> q;
		q.push(t);
		while (!q.empty())
		{
			Tree current = q.front();
			if (isLeaf(current))
				demLa++;
			if (current->left != NULL)
				q.push(current->left);
			if (current->right != NULL)
				q.push(current->right);
			q.pop();
			if (q.empty()||MucX(t, q.front()->key) != MucX(t, current->key))
			{
				if (demLa > maxLa)
				{
					maxLevel = level;
					maxLa = demLa;
				}
				demLa = 0;
				level++;
			}
		}
	}
	return maxLevel;
}
int FindX(Tree t, int x)
{
	if (t == NULL)
		return 0;
	if (t->key == x)
		return 1;
	if (t->key > x)
		return FindX(t->left, x);
	return FindX(t->right, x);
}

void FindSubs(Node*& temp, Tree& t)
{
	if (t->left != NULL)
		FindSubs(temp, t->left);
	else
	{
		temp->key = t->key;
		temp = t;
		t = t->right;
	}
}
void RemoveX(Tree& t, int x)
{
	if (t == NULL)
		return;
	Node* temp = t;
	if (t->key == x)
	{
		if (t->left == NULL)
			t = t->right;
		else if (t->right == NULL)
			t = t->left;
		else
			FindSubs(temp, t->right);

		delete temp;
		temp = NULL;
	}
	else if (t->key < x)
		RemoveX(t->right, x);
	else
		RemoveX(t->left, x);
}
int ktNguyenTo(int x)
{
	int dem = 0;
	for (int i = 1; i <= x; i++)
		if (x % i == 0)
			dem++;
	return dem == 2;
}
void RemoveSoNT(Tree& t)
{
	if (t != NULL)
	{
		RemoveSoNT(t->left);
		RemoveSoNT(t->right);
		if (ktNguyenTo(t->key))
		{
			RemoveX(t, t->key);
		}
	}
}
int countNodes(Tree t)
{
	if (t == NULL)
		return 0;
	return 1 + countNodes(t->left) + countNodes(t->right);
}
int count2Sons(Tree t)
{
	if (t == NULL)
		return 0;
	if (t->left && t->right)
		return 1 + count2Sons(t->left) + count2Sons(t->right);
	return count2Sons(t->left) + count2Sons(t->right);
}
int isLeaf(Node* node)
{
	return node->left == NULL && node->right == NULL;
}
int countLeaves(Tree t)
{
	if (t == NULL)
		return 0;
	if (isLeaf(t))
		return 1;
	return countLeaves(t->left) + countLeaves(t->right);
}
int GetHeight(Tree t)
{
	if (t == NULL)
		return -1;
	return 1 + max(GetHeight(t->left), GetHeight(t->right));
}
void DrawTreeUtil(Tree t, int depth)
{
	if (t != NULL)
	{
		depth++;
		DrawTreeUtil(t->right, depth);
		for (int i = 1; i < depth; i++)
			cout << "\t";
		cout << t->key << endl;
		DrawTreeUtil(t->left, depth);
	}
}
void Draw(Tree t)
{
	if (t != NULL)
		DrawTreeUtil(t, 0);
}

int NodeToiX(Tree t, int x)
{
	if (t == NULL || t->key == x)
		return 0;
	else if (t->key < x)
		return 1 + NodeToiX(t->right, x);
	else
		return 1 + NodeToiX(t->left, x);
}
int TinhDuongDi(Tree t, int x, int y)
{
	if (t == NULL)
		return 0;
	if (x < t->key && y < t->key)
		return TinhDuongDi(t->left, x, y);
	if (x > t->key && y > t->key)
		return TinhDuongDi(t->right, x, y);
	return NodeToiX(t, x) + NodeToiX(t, y);
}

void InNutSoNutTraiBangSoNutPhai(Tree t)
{
	if (!isLeaf(t) && t)
	{
		if (countNodes(t->left) == countNodes(t->right))
			cout << t->key << " ";
		InNutSoNutTraiBangSoNutPhai(t->left);
		InNutSoNutTraiBangSoNutPhai(t->right);
	}
}

int keyBoX(Tree t, int x)
{
	if (t == NULL || t->key == x)
		return 0;
	else if (t->left->key == x || t->right->key == x)
		return t->key;
	else if (t->key < x)
		return keyBoX(t->right, x);
	else
		return keyBoX(t->left, x);
}