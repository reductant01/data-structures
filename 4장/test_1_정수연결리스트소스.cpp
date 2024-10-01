/*
* 1�ܰ�-���� ���� ����Ʈ: �ܼ��� linked list���� add, delete�ϴ� �˰����� �ڵ�
* template �������� ����� 
*/
#include <iostream>
#include <time.h>
using namespace std;

class Node {
	friend class LinkedList;
	int data;
	Node* link;
public:
	Node(int element) {
		data = element;
		link = 0;
	}
};

class LinkedList {
	Node* first;
public:
	LinkedList() {
		first = 0;
	}
	bool Delete(int);
	void Show();
	void Add(int element);//���ĵǵ��� ����
	bool Search(int data);
	LinkedList& operator+(LinkedList&);
};
void LinkedList::Show() { // ��ü ����Ʈ�� ������� ����Ѵ�.
	Node* p = first;

}
void LinkedList::Add(int element) // ���� ���� ������ �� ����Ʈ�� ������������ ������ �ǵ��� �Ѵ�
{
	Node* newNode = new Node(element);

}
bool LinkedList::Search(int data) { // ��ü ����Ʈ�� ������� ����Ѵ�.
	Node* ptr = first;

}
bool LinkedList::Delete(int element) // delete the element
{
	Node* q, * current = first;
	q = current;

}
LinkedList& LinkedList::operator+(LinkedList& lb) {
	LinkedList lc;
	Node* a = first, * b = lb.first;

}
enum Enum {
	Add1, Add2, Delete, Show, Search, Merge, Exit
};
void main() {
	Enum menu; // �޴�
	int selectMenu;
	int num = 0; bool result = false;
	srand(time(NULL));
	LinkedList la, lb, lc;
	int data = 0;
	do {
		cout << "0.ADD0, 1. Add1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit ����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add1:
			data = rand() % 49;
			la.Add(data);
			break;
		case Add2:
			data = rand() % 49;
			lb.Add(data);
			break;
		case Delete:
			cin >> data;
			result = la.Delete(data);
			if (result)
				cout << "���� �Ϸ�";
			break;
		case Show:
			cout << "����Ʈ la = ";
			la.Show();
			cout << "����Ʈ lb = ";
			lb.Show();
			break;
		case Search: // ȸ�� ��ȣ �˻�
			int n; cin >> n;
			result = la.Search(n);
			if (!result)
				cout << "�˻� �� = " << n << " �����Ͱ� �����ϴ�.";
			else
				cout << "�˻� �� = " << n << " �����Ͱ� �����մϴ�.";
			break;
		case Merge:
			lc = la + lb;
			cout << "����Ʈ lc = ";
			lc.Show();
			break;
		case Exit:
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}

