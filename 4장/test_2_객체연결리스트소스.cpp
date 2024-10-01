/*
* 2�ܰ�- ��ü ���� ����Ʈ: �ܼ��� linked list���� insert�� �ø��������� ���ĵǵ��� ó��, delete�ϴ� �˰����� �ڵ�
* template version���� ����
*/
#include <iostream>
#include <time.h>
using namespace std;
class Employee {
	friend class Node;
	friend class LinkedList;
	string eno;
	string ename;
public:
	Employee() {}
	Employee(string sno, string sname) :eno(sno), ename(sname) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
};
ostream& operator<<(ostream& os, Employee& emp) {

}
bool Employee::operator==(Employee& emp) {

}
bool Employee::operator<(Employee& emp) {

}
class Node {
	friend class LinkedList;
	Employee data;
	Node* link;
public:
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class LinkedList {
	Node* first;
public:
	LinkedList() {
		first = nullptr;
	}
	bool Delete(string);
	void Show();
	void Add(Employee);//sno�� ���ĵǵ��� ����
	bool Search(string);
	LinkedList& operator+(LinkedList&);
};
void LinkedList::Show() { // ��ü ����Ʈ�� ������� ����Ѵ�.
	Node* p = first;

}
void LinkedList::Add(Employee element) // ���� ���� ������ �� ����Ʈ�� ������������ ������ �ǵ��� �Ѵ�
{
	Node* newNode = new Node(element);

}
bool LinkedList::Search(string eno) { // sno�� ���� ���ڵ带 ã��
	Node* ptr = first;

}
bool LinkedList::Delete(string eno) // delete the element
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
	int selectMenu, num;
	string eno, ename;
	bool result = false;
	LinkedList la, lb, lc;
	Employee* data;
	do {
		cout << "0.ADD0, 1. Add1, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit ����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add1:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			la.Add(*data);
			break;
		case Add2:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			lb.Add(*data);
			break;
		case Delete:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = la.Delete(eno);
			if (result)
				cout << "���� �Ϸ�";
			break;
		case Show:
			cout << "����Ʈ la = ";
			la.Show();
			cout << "����Ʈ lb = ";
			lb.Show();
			break;
		case Search:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			result = la.Search(eno);
			if (!result)
				cout << "�˻� �� = " << eno << " �����Ͱ� �����ϴ�.";
			else
				cout << "�˻� �� = " << eno << " �����Ͱ� �����մϴ�.";
			break;
		case Merge:
			lc = la + lb;
			cout << "����Ʈ lc = ";
			lc.Show();
			break;

		case Exit: // ���� ��� ����
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}

