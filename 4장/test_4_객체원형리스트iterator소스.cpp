/*
* 4�ܰ�- ���� ��ü ���� ����Ʈ�� iterator ����
* CircularList�� ������� �� iterator�� �����Ѵ�.
* template �������� ���� 
*/
#include <iostream>
#include <time.h>
using namespace std;

class Employee {
	friend class Node;
	friend class CircularList;
	friend class ListIterator;
private:
	string eno;
	string ename;
	int salary;
public:
	Employee() {}
	Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
	char compare(const Employee* emp) const;
	int getSalary() const {
		return salary;
	}
};
ostream& operator<<(ostream& os, Employee& emp) {

}
bool Employee::operator==(Employee& emp) {

}
bool Employee::operator<(Employee& emp) {

}
char Employee::compare(const Employee* emp) const {


}
class Node {
	friend class ListIterator;
	friend class CircularList;
	Employee data;
	Node* link;
public:
	Node() {}
	Node(Employee element) {
		data = element;
		link = nullptr;
	}
};

class CircularList {
	friend class ListIterator;
	Node* first;//last ��带 ����Ű�� last ������ ����ϴ� �������� ���� �ǽ� 
	//static Node* av;
public:
	CircularList() {
		first = new Node(); first->link = first;
	}
	bool Delete(string);
	void Show();
	void Add(Employee*);//sno�� ���ĵǵ��� ����
	bool Search(string);
	CircularList& operator+(CircularList&);
	friend ostream& operator<<(ostream& os, CircularList& l);
};
class ListIterator {
	//���� ����Ʈ�� head node�� �����̹Ƿ� ����Ʈ ������ ��忡 ���޽� ������ �ʿ��ϴ� 
public:
	ListIterator(const CircularList& lst);
	~ListIterator();
	bool NotNull();
	bool NextNotNull();
	Employee* First();
	Employee* Next();
	Employee& operator*() const;
	Employee* operator->()const;
	ListIterator& operator++(); //Next()
	ListIterator operator ++(int);
	bool operator != (const ListIterator) const;
	bool operator == (const ListIterator) const;
	Employee* GetCurrent();
private:
	Node* current; //pointer to nodes
	const CircularList& list;//existing list
};

ostream& operator<<(ostream& os, CircularList& l)
{
	ListIterator li(l);

}
void CircularList::Show() { // ��ü ����Ʈ�� ������� ����Ѵ�.
	Node* p = first->link;

}
void CircularList::Add(Employee* element) // ���� ���� ������ �� ����Ʈ�� ������������ ������ �ǵ��� �Ѵ�
{
	Node* newNode = new Node(*element);
	Node* p = first->link, * q = first;
	if (p == nullptr) {
		first = newNode;
		newNode->link = newNode;
	}
	while (p->link != first) {
		if (element > p.data) {
			q = p;
			p = p->link
				if (p == first) {
					q->link = newNode;
			}
		}
		else { // �ΰ��� ���: 1) ��ó�� ���, 2) �߰��� ����
			if (q == nullptr) {
				// ��ó���� �ش�
			}
			else {

			}
		}
	}
}
bool CircularList::Search(string eno) { // sno�� ���� ���ڵ带 ã��
	Node* p = first->link;

}
bool CircularList::Delete(string eno) // delete the element
{
	Node* p = first->link;
	Node* q = first;

}
CircularList& CircularList::operator+(CircularList& lb) {
	Employee* p, * q;
	ListIterator Aiter(*this); ListIterator Biter(lb);
	CircularList lc;
	p = Aiter.First(); q = Biter.First();

}

ListIterator::ListIterator(const CircularList& lst) : list(lst), current(lst.first->link) {
	cout << "List Iterator is constructed" << endl;
}
bool ListIterator::NotNull() {

}
bool ListIterator::NextNotNull() {

}
Employee* ListIterator::First() {

}
Employee* ListIterator::Next() {

}

Employee* ListIterator::GetCurrent() {
	return &current->data;
}

ListIterator::~ListIterator() {
}

Employee& ListIterator::operator*() const {
	return current->data;
}

Employee* ListIterator::operator->()const {
	return &current->data;
}

ListIterator& ListIterator::operator++() {
	current = current->link;
	return *this;
}

ListIterator ListIterator::operator ++(int) {
	ListIterator old = *this;
	current = current->link;
	return old;
}

bool ListIterator::operator != (const ListIterator right) const {
	return current != right.current;
}

bool ListIterator::operator == (const ListIterator right) const {
	return current == right.current;
}
//int printAll(const List& l);//list iterator�� ����Ͽ� �ۼ��ϴ� ����
//int sumProductFifthElement(const List& l);//list iterator�� ����Ͽ� �ۼ��ϴ� ����
int sum(const CircularList& l)
{

}

double avg(const CircularList& l)
{

}

int min(const CircularList& l)
{

}

int max(const CircularList& l)
{
}

enum Enum {
	Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

//Node* CircularList::av = NULL;//static ������ �ʱ�ȭ ����� ����ؾ� �Ѵ�

void main() {
	Enum menu; // �޴�
	int selectMenu, num;
	string eno, ename;
	int pay;
	Employee* data;
	bool result = false;
	CircularList la, lb, lc;
	do {
		cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6. sum, 7.avg, 8.min, 9.max, 10.exit ����::";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case Add0:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			cout << "��� �޿�:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			la.Add(data);
			break;
		case Add1:
			cout << "�����ȣ �Է�:: ";
			cin >> eno;
			cout << "��� �̸� �Է�:: ";
			cin >> ename;
			cout << "��� �޿�:: ";
			cin >> pay;
			data = new Employee(eno, ename, pay);
			lb.Add(data);
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

		case SUM:  cout << "sum() = " << sum(la) << endl; break;
		case AVG:  cout << "avg() = " << avg(la) << endl; break;
		case MIN:  cout << "min() = " << min(la) << endl; break;
		case MAX:  cout << "max() = " << max(la) << endl; break;
		case Exit: // ���� ��� ����
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}
