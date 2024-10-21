/*
* 4�ܰ�- ���� ��ü ���� ����Ʈ�� iterator ����
* CircularList�� ������� �� iterator�� �����Ѵ�.
* template �������� ���� 
*/
#include <iostream>
#include <string>
using namespace std;

// ------------- Employee Ŭ���� -------------
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
    Employee(string sno, string sname, int salary) : eno(sno), ename(sname), salary(salary) {}
    friend ostream& operator<<(ostream& os, const Employee&);
    bool operator<(const Employee& emp) const;
    bool operator==(const Employee& emp) const;
    char compare(const Employee* emp) const;
    int getSalary() const {
        return salary;
    }
};

ostream& operator<<(ostream& os, const Employee& emp) {
    os << "�����ȣ: " << emp.eno << ", �̸�: " << emp.ename << ", �޿�: " << emp.salary;
    return os;
}

bool Employee::operator<(const Employee& emp) const {
    return this->eno < emp.eno;
}

bool Employee::operator==(const Employee& emp) const {
    return this->eno == emp.eno;
}

char Employee::compare(const Employee* emp) const {
    if (this->eno < emp->eno)
        return '<';
    else if (this->eno > emp->eno)
        return '>';
    else
        return '=';
}

// ------------- Node Ŭ���� -------------
class Node {
    friend class ListIterator;
    friend class CircularList;
    Employee data;
    Node* link;
public:
    Node() : link(nullptr) {}
    Node(const Employee& element) : data(element), link(nullptr) {}
};

// ------------- ListIterator Ŭ���� -------------
class CircularList; // Forward declaration

class ListIterator {
public:
    ListIterator(const CircularList& lst);
    ~ListIterator();
    bool NotNull() const;
    Employee* First();
    Employee* Next();
    Employee& operator*() const;
    Employee* operator->() const;
    ListIterator& operator++(); // ���� ���� ������
    ListIterator operator++(int); // ���� ���� ������
    bool operator!=(const ListIterator& right) const;
    bool operator==(const ListIterator& right) const;
    Employee* GetCurrent() const;
private:
    Node* current; // ���� ��带 ����Ű�� ������
    const CircularList& list; // ���� ����Ʈ�� ���� ����
};

// ------------- CircularList Ŭ���� -------------
class CircularList {
    friend class ListIterator;
    Node* first; // ���� ��带 ����Ű�� ������
public:
    CircularList() {
        first = new Node(); // ���� ��� ����
        first->link = first; // �ڱ� �ڽ��� ����Ŵ
    }
    ~CircularList();
    bool Delete(string);
    void Show() const;
    void Add(Employee*); // eno �������� �����Ͽ� ����
    bool Search(string) const;
    CircularList operator+(const CircularList& lb) const;
    friend ostream& operator<<(ostream& os, const CircularList& l);
};

// ------------- CircularList �޼��� ���� -------------
CircularList::~CircularList() {
    if (first == nullptr)
        return;
    Node* p = first->link;
    // ��尡 �ϳ����� ��� (����Ʈ�� ����ִ� ��� ���� ��常 ����)
    if (p == first) {
        delete first;
        first = nullptr;
        return;
    }
    // ��尡 ���� ���� ���
    while (p != first) {
        Node* temp = p;
        p = p->link;
        delete temp;
    }
    delete first;
    first = nullptr;
}

bool CircularList::Delete(string eno) {
    if (first->link == first) // ����Ʈ�� ����ִ� ���
        return false;

    Node* p = first->link; // ���� ���
    Node* q = first;       // ���� ���

    do {
        if (p->data.eno == eno) {
            q->link = p->link;
            delete p;
            return true;
        }
        q = p;
        p = p->link;
    } while (p != first);

    return false; // eno�� ���� ����� ����
}

void CircularList::Show() const { // ��ü ����Ʈ�� ������� ���
    if (first->link == first) {
        cout << "����Ʈ�� ��� �ֽ��ϴ�." << endl;
        return;
    }

    Node* p = first->link;
    do {
        cout << p->data << " -> ";
        p = p->link;
    } while (p != first);
    cout << "first" << endl;
}

void CircularList::Add(Employee* element) { // eno �������� �����Ͽ� ����
    Node* newNode = new Node(*element);
    Node* p = first->link; // ù ��° ���� ���
    Node* q = first;       // ���� ���

    // ����Ʈ�� ����ְų�, ù ��庸�� ���� eno�� ���� ���
    if (p == first || element->eno < p->data.eno) {
        newNode->link = p;
        q->link = newNode;
        return;
    }

    // ������ ��ġ�� ã��
    while (p != first && !(element->eno < p->data.eno)) {
        q = p;
        p = p->link;
    }

    // ��� ����
    newNode->link = p;
    q->link = newNode;
}

bool CircularList::Search(string eno) const { // eno�� ���� ���ڵ带 ã��
    if (first->link == first) // ����Ʈ�� ����ִ� ���
        return false;

    Node* p = first->link;
    do {
        if (p->data.eno == eno)
            return true;
        p = p->link;
    } while (p != first);

    return false; // eno�� ���� ����� ����
}

CircularList CircularList::operator+(const CircularList& lb) const {
    CircularList lc;
    ListIterator Aiter(*this);
    ListIterator Biter(lb);
    Employee* p = Aiter.First();
    Employee* q = Biter.First();

    while (p != nullptr && q != nullptr) {
        if (*p < *q) { // A�� eno�� B�� eno���� ���� ���
            lc.Add(new Employee(*p));
            p = Aiter.Next();
        }
        else { // B�� eno�� A�� eno���� �۰ų� ���� ���
            lc.Add(new Employee(*q));
            q = Biter.Next();
        }
    }

    // �����ִ� ��带 lc�� �߰�
    while (p != nullptr) {
        lc.Add(new Employee(*p));
        p = Aiter.Next();
    }

    while (q != nullptr) {
        lc.Add(new Employee(*q));
        q = Biter.Next();
    }

    return lc; // ���ο� ����Ʈ ��ȯ
}

ostream& operator<<(ostream& os, const CircularList& l) {
    ListIterator li(l);
    if (!li.NotNull()) {
        os << "����Ʈ�� ��� �ֽ��ϴ�." << endl;
        return os;
    }
    Employee* p = li.First();
    while (p != nullptr) {
        os << *p << " -> ";
        p = li.Next();
    }
    os << "first" << endl;
    return os;
}

// ------------- ListIterator �޼��� ���� -------------
ListIterator::ListIterator(const CircularList& lst) : list(lst), current(lst.first->link) {
    if (current == lst.first) // ����Ʈ�� ����ִ� ���
        current = nullptr;
    cout << "List Iterator is constructed" << endl;
}

ListIterator::~ListIterator() {
    // Ư���� �޸� ���� �ʿ� ����
}

bool ListIterator::NotNull() const {
    return current != nullptr;
}

Employee* ListIterator::First() {
    if (list.first->link != list.first) {
        current = list.first->link;
        return &current->data;
    }
    return nullptr;
}

Employee* ListIterator::Next() {
    if (current == nullptr)
        return nullptr;

    current = current->link;
    if (current == list.first) { // �ٽ� ó�� ��忡 �������� ��
        current = nullptr;
        return nullptr;
    }
    return &current->data;
}

Employee& ListIterator::operator*() const {
    return current->data;
}

Employee* ListIterator::operator->() const {
    return &current->data;
}

ListIterator& ListIterator::operator++() { // ���� ���� ������
    if (current != nullptr)
        current = current->link;
    if (current == list.first) // �ٽ� ó�� ��忡 �������� ��
        current = nullptr;
    return *this;
}

ListIterator ListIterator::operator++(int) { // ���� ���� ������
    ListIterator old = *this;
    if (current != nullptr)
        current = current->link;
    if (current == list.first) // �ٽ� ó�� ��忡 �������� ��
        current = nullptr;
    return old;
}

bool ListIterator::operator!=(const ListIterator& right) const {
    return current != right.current;
}

bool ListIterator::operator==(const ListIterator& right) const {
    return current == right.current;
}

Employee* ListIterator::GetCurrent() const {
    if (current != nullptr)
        return &current->data;
    return nullptr;
}

// ------------- sum, avg, min, max �Լ� ���� -------------
int sum(const CircularList& l)
{
    ListIterator li(l);
    int total = 0;
    while (li.NotNull()) {
        total += li->getSalary();
        li++;
    }
    return total;
}

double avg(const CircularList& l)
{
    ListIterator li(l);
    int total = 0;
    int count = 0;
    while (li.NotNull()) {
        total += li->getSalary();
        count++;
        li++;
    }
    if (count == 0)
        return 0.0;
    return static_cast<double>(total) / count;
}

int min(const CircularList& l)
{
    ListIterator li(l);
    if (!li.NotNull())
        return 0; // ����Ʈ�� ������� ���
    int minimum = li->getSalary();
    li++;
    while (li.NotNull()) {
        int sal = li->getSalary();
        if (sal < minimum)
            minimum = sal;
        li++;
    }
    return minimum;
}

int max(const CircularList& l)
{
    ListIterator li(l);
    if (!li.NotNull())
        return 0; // ����Ʈ�� ������� ���
    int maximum = li->getSalary();
    li++;
    while (li.NotNull()) {
        int sal = li->getSalary();
        if (sal > maximum)
            maximum = sal;
        li++;
    }
    return maximum;
}

// ------------- main �Լ� ���� -------------
enum Enum {
    Add0, Add1, DeleteOp, ShowOp, SearchOp, MergeOp, SUM, AVG, MIN, MAX, ExitOp
};

int main() {
    Enum menu; // �޴�
    int selectMenu;
    string eno, ename;
    int pay;
    Employee* data;
    bool result = false;
    CircularList la, lb, lc;
    do {
        cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6.sum, 7.avg, 8.min, 9.max, 10.exit ����::";
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
        case DeleteOp:
            cout << "�����ȣ �Է�:: ";
            cin >> eno;
            result = la.Delete(eno);
            if (result)
                cout << "���� �Ϸ�" << endl;
            else
                cout << "���� ����: �ش� �����ȣ�� �����ϴ�." << endl;
            break;
        case ShowOp:
            cout << "����Ʈ la = ";
            la.Show();
            cout << "����Ʈ lb = ";
            lb.Show();
            break;
        case SearchOp:
            cout << "�����ȣ �Է�:: ";
            cin >> eno;
            result = la.Search(eno);
            if (!result)
                cout << "�˻� �� = " << eno << " �����Ͱ� �����ϴ�." << endl;
            else
                cout << "�˻� �� = " << eno << " �����Ͱ� �����մϴ�." << endl;
            break;
        case MergeOp:
            lc = la + lb;
            cout << "����Ʈ lc = ";
            lc.Show();
            break;
        case SUM:
            cout << "sum() = " << sum(la) << endl;
            break;
        case AVG:
            cout << "avg() = " << avg(la) << endl;
            break;
        case MIN:
            cout << "min() = " << min(la) << endl;
            break;
        case MAX:
            cout << "max() = " << max(la) << endl;
            break;
        case ExitOp:
            cout << "���α׷��� �����մϴ�." << endl;
            break;
        default:
            cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���." << endl;
            break;
        }
    } while (selectMenu != ExitOp);
    return 0;
}
