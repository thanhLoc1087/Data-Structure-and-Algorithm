#include <iostream>
using namespace std;

struct Item
{
	int key;
	Item* next;
}; typedef Item* Node;
struct List
{
	Node head;
	Node tail;
};

void Init(List&);
Node CreateNode(int);
int isEmpty(List);
void AddTail(List&, Node);
void Nhap(List&);
void SortAsc(List&);
void RemoveAfterQ(List&, Node);
int FindX(List, int);
void Display(List);
void RemoveHead(List&);
void RemoveX(List&, int);
void RemoveDup(List&);
List MergeLists(List, List);

int main()
{
	List myList;
	List list1, list2;
	Init(list1);
	Init(list2);
	Nhap(list1);
	Nhap(list2);
	Init(myList);
	//Nhap(myList);
	//RemoveDup(myList);
	//cout << "Delete? ";
	//int del;
	//cin >> del;
	//RemoveX(myList, del);
	//Display(myList);
	//SortAsc(myList);
	cout << endl;
	Display(MergeLists(list1, list2));
	cout << endl;
	Display(list1);
	return 0;
}

void Init(List& list)
{
	list.head = NULL;
	list.tail = NULL;
}
Node CreateNode(int data)
{
	Node p = new Item;
	p->key = data;
	p->next = NULL;
	return p;
}
int isEmpty(List list)
{
	return list.head == NULL;
}
void Nhap(List& list)
{
	int soPhanTu, newData;
	cout << "Nhap so phan tu: ";
	cin >> soPhanTu;
	for (int i = 0; i < soPhanTu; i++)
	{
		cin >> newData;
		AddTail(list, CreateNode(newData));
	}
}
void AddTail(List& list, Node p)
{
	if (isEmpty(list))
	{
		list.head = list.tail = p;
	}
	else
	{
		list.tail->next = p;
		list.tail = p;
	}
}
void SortAsc(List& list)
{
	for (Node p = list.head; p->next != NULL; p = p->next)
		for (Node q = p->next; q != NULL; q = q->next)
			if (p->key > q->key)
				swap(p->key, q->key);
}
void RemoveAfterQ(List& list, Node q)
{
	if (isEmpty(list))
		return;
	if (q->next != NULL)
	{
		Node delNode = q->next;
		q->next = q->next->next;
		delete delNode;
		delNode = NULL;
		if (q->next == NULL)
			list.tail = q;
	}
}
int FindX(List list, int x)
{
	for (Node p = list.head; p != NULL; p = p->next)
		if (p->key == x)
			return 1;
	return 0;
}
void Display(List list)
{
	for (Node p = list.head; p != NULL; p = p->next)
		cout << p->key << " ";
}
void RemoveHead(List& list)
{
	Node delNode = list.head;
	list.head = list.head->next;
	delete delNode;
	delNode = NULL;
}
void RemoveX(List& list, int x)
{
	if (list.head->key == x)
		RemoveHead(list);
	else
	{
		for (Node k = list.head; k->next != NULL; k = k->next)
			if (k->next->key == x)
				RemoveAfterQ(list, k);
	}
}
void RemoveDup(List& list)
{
	if (isEmpty(list))
		return;
	Node node1, node2, delNode;
	node1 = list.head;
	while (node1 != NULL && node1->next != NULL)
	{
		node2 = node1->next;
		while (node2->next != NULL)
		{
			if (node2->next->key == node1->key)
			{
				delNode = node2->next;
				node2->next = delNode->next;
				delete delNode;
			}
			else
				node2 = node2->next;
		}
		node1 = node1->next;
	}
}
List MergeLists(List a, List b)
{
	List list;
	Init(list);
	SortAsc(a);
	SortAsc(b);
	Node ptr1 = a.head;
	Node ptr2 = b.head;
	do
	{
		if (ptr1 == NULL)
		{
			if (isEmpty(list))
				list = b;
			else
			{
			list.tail->next = ptr2;
			list.tail = b.tail;
			}
			break;
		}
		else if (ptr2 == NULL)
		{
			if (isEmpty(list))
				list = a;
			else
			{
				list.tail->next = ptr1;
				list.tail = a.tail;
			}
			break;
		}
		if (ptr1->key <= ptr2->key)
		{
			AddTail(list, CreateNode(ptr1->key));
			ptr1 = ptr1->next;
		}
		else if (ptr1->key > ptr2->key)
		{
			AddTail(list, CreateNode(ptr2->key));
			ptr2 = ptr2->next;
		}
	} while (true);

	return list;
}

