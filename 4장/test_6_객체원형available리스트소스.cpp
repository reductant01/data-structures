/*
* 6�ܰ�- ���� ��ü ���� ����Ʈ�� available list, getNode, retNode
* head node�� ���� �ְ� ������ ������ available list�� �����Ѵ�.
* CircularList�� ������� �� iterator�� �����Ѵ�.
* ������ class�� �Լ����� �ִ��� �������� ����
*/
#include <iostream>
#include <string>
using namespace std;

// Forward declaration of CircularList
class CircularList;

// Forward declaration of operator<<
ostream& operator<<(ostream& os, CircularList& l);

// Employee Ŭ���� ����
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

// ��� ������ �����ε�
ostream& operator<<(ostream& os, Employee& emp) {
    os << "[ENO: " << emp.eno << ", NAME: " << emp.ename << ", SALARY: " << emp.salary << "]";
    return os;
}

// �� ������ �����ε� (<)
bool Employee::operator<(Employee& emp) {
    return this->eno < emp.eno;
}

// �� ������ �����ε� (==)
bool Employee::operator==(Employee& emp) {
    return this->eno == emp.eno;
}

// compare �Լ� ����
char Employee::compare(const Employee* emp) const {
    if (this->eno < emp->eno) return '<';
    if (this->eno > emp->eno) return '>';
    return '=';
}

// Node Ŭ����
class Node {
    friend class ListIterator;
    friend class CircularList;
    friend ostream& operator<<(ostream& os, CircularList& l); // operator<<�� ģ���� ����
    Employee data;
    Node* link;
public:
    Node() { }
    Node(Employee element) {
        data = element;
        link = nullptr;
    }
};

// CircularList Ŭ����
class CircularList {
    friend class ListIterator;
    friend ostream& operator<<(ostream& os, CircularList& l); // operator<<�� ģ���� ����
    Node* last; // ������ ��带 ����Ŵ
    static Node* av; // available list
public:
    CircularList() {
        last = new Node(); 
        last->link = last; // ��� ���� �ڱ� �ڽ��� ����Ŵ
    }
    
    bool Delete(string);
    void Show();
    void Add(Employee*); // eno�� ���ĵǵ��� ����
    bool Search(string);
    Node* GetNode();
    void RetNode(Node*);
    void Erase();
    CircularList& operator+(CircularList&);
    friend ostream& operator<<(ostream& os, CircularList& l);
};

// available list �ʱ�ȭ
Node* CircularList::av = NULL;

// GetNode �Լ�: available list���� ��带 �������ų� ���� ����
Node* CircularList::GetNode()
{ 
    if (av != NULL) { // available list�� ��尡 �ִ� ���
        Node* temp = av;
        av = av->link;
        return temp;
    }
    else { // available list�� ��尡 ���� ��� ���� ����
        return new Node();
    }
}

// RetNode �Լ�: ������ ��带 available list�� ��ȯ
void CircularList::RetNode(Node* x)
{
    x->link = av;
    av = x;
}

// operator<< �����ε�: ����Ʈ ���
ostream& operator<<(ostream& os, CircularList& l)
{
    if (l.last->link == l.last) { // ����Ʈ�� ����ִ� ���
        os << "Empty List";
        return os;
    }
    Node* p = l.last->link->link; // ù ������ ���
    while (p != l.last->link) {
        os << p->data << " -> ";
        p = p->link;
    }
    os << "(Head)";
    return os;
}

// Show �Լ�: ����Ʈ ���
void CircularList::Show() { 
    cout << *this << endl;
}

// Add �Լ�: eno �������� ���ĵ� ��ġ�� ����
void CircularList::Add(Employee* element) 
{
    Node* newNode = GetNode(); 
    newNode->data = *element;
    Node* first = last->link; // ��� ���
    Node* p = first->link; // ù ������ ���
    Node* q = first; // ���� ���
    
    // ���� ��ġ�� ã��
    while (p != first && p->data < newNode->data) {
        q = p;
        p = p->link;
    }
    
    // ����
    q->link = newNode;
    newNode->link = p;
    
    // ������ ��� ������Ʈ
    if (q == last) {
        last = newNode;
    }
}

// Search �Լ�: eno�� �˻�
bool CircularList::Search(string eno) { 
    Node* first = last->link; // ��� ���
    Node* p = first->link; // ù ������ ���
    
    while (p != first) {
        if (p->data.eno == eno) return true;
        p = p->link;
    }
    return false;
}

// Delete �Լ�: eno�� ����
bool CircularList::Delete(string eno) 
{
    Node* first = last->link; // ��� ���
    Node* p = first->link; // ù ������ ���
    Node* q = first; // ���� ���
    
    while (p != first && p->data.eno != eno) {
        q = p;
        p = p->link;
    }
    
    if (p == first) return false; // ã�� ����
    
    q->link = p->link;
    
    // ������ ��尡 ������ ��� ������Ʈ
    if (p == last) {
        last = q;
    }
    
    RetNode(p);
    return true;
}

// Erase �Լ�: ����Ʈ �ʱ�ȭ �� ��� ��ȯ
void CircularList::Erase() {
    Node* first = last->link; // ��� ���
    Node* p = first->link; // ù ������ ���
    
    while (p != first) {
        Node* temp = p;
        p = p->link;
        RetNode(temp);
    }
    last->link = last; // ��� ��常 ����
}

// operator+ �Լ�: �� ����Ʈ�� ����
CircularList& CircularList::operator+(CircularList& lb) {
    CircularList* lc = new CircularList();
    ListIterator iterA(*this);
    ListIterator iterB(lb);
    
    Employee* p = iterA.First();
    Employee* q = iterB.First();
    
    while (p != nullptr && q != nullptr) {
        if (*p < *q) {
            lc->Add(p);
            p = iterA.Next();
        }
        else {
            lc->Add(q);
            q = iterB.Next();
        }
    }
    while (p != nullptr) {
        lc->Add(p);
        p = iterA.Next();
    }
    while (q != nullptr) {
        lc->Add(q);
        q = iterB.Next();
    }
    return *lc;
}

// ListIterator Ŭ����
class ListIterator {
public:
    ListIterator(const CircularList& lst);
    ~ListIterator();
    bool NotNull();
    bool NextNotNull();
    Employee* First();
    Employee* Next();
    Employee& operator*() const;
    Employee* operator->()const;
    ListIterator& operator++(); // Next()
    ListIterator operator ++(int);
    bool operator != (const ListIterator) const;
    bool operator == (const ListIterator) const;
    Employee* GetCurrent();
private:
    Node* current; // ���� ���
    const CircularList& list; // ����Ʈ ����
};

// ListIterator ������
ListIterator::ListIterator(const CircularList& lst) : list(lst), current(lst.last->link->link) {
}

// ListIterator �Ҹ���
ListIterator::~ListIterator() {
}

// NotNull �Լ�: ���� ��尡 ��尡 �ƴ��� Ȯ��
bool ListIterator::NotNull() {
    return current != list.last->link;
}

// NextNotNull �Լ�: ���� ��尡 ��尡 �ƴ��� Ȯ��
bool ListIterator::NextNotNull() {
    return current->link != list.last->link;
}

// First �Լ�: ù ��° ������ ��� ��ȯ
Employee* ListIterator::First() {
    current = list.last->link->link;
    if (current == list.last->link) return nullptr;
    return &current->data;
}

// Next �Լ�: ���� ������ ��� ��ȯ
Employee* ListIterator::Next() {
    if (current->link == list.last->link) return nullptr;
    current = current->link;
    return &current->data;
}

// GetCurrent �Լ�: ���� ����� ������ ��ȯ
Employee* ListIterator::GetCurrent() {
    return &current->data;
}

// ������* �����ε�
Employee& ListIterator::operator*() const {
    return current->data;
}

// ������-> �����ε�
Employee* ListIterator::operator->() const {
    return &current->data;
}

// ���� ���� ������
ListIterator& ListIterator::operator++() { 
    if (current->link != list.last->link)
        current = current->link;
    else
        current = list.last->link; // ��ȯ
    return *this;
}

// ���� ���� ������
ListIterator ListIterator::operator++(int) { 
    ListIterator old = *this;
    if (current->link != list.last->link)
        current = current->link;
    else
        current = list.last->link;
    return old;
}

// ������!= �����ε�
bool ListIterator::operator != (const ListIterator right) const {
    return current != right.current;
}

// ������== �����ε�
bool ListIterator::operator == (const ListIterator right) const {
    return current == right.current;
}

// sum �Լ�: ����Ʈ �� �޿� �հ�
int sum(const CircularList& l)
{
    ListIterator li(l);
    int total = 0;
    Employee* emp = li.First();
    while (emp != nullptr) {
        total += emp->getSalary();
        emp = li.Next();
    }
    return total;
}

// avg �Լ�: ����Ʈ �� �޿� ���
double avg(const CircularList& l)
{
    ListIterator li(l);
    int total = 0, count = 0;
    Employee* emp = li.First();
    while (emp != nullptr) {
        total += emp->getSalary();
        count++;
        emp = li.Next();
    }
    return count == 0 ? 0 : static_cast<double>(total) / count;
}

// min �Լ�: ����Ʈ �� �ּ� �޿�
int min(const CircularList& l)
{
    ListIterator li(l);
    Employee* emp = li.First();
    if (emp == nullptr) return 0;
    int minSal = emp->getSalary();
    emp = li.Next();
    while (emp != nullptr) {
        if (emp->getSalary() < minSal)
            minSal = emp->getSalary();
        emp = li.Next();
    }
    return minSal;
}

// max �Լ�: ����Ʈ �� �ִ� �޿�
int max(const CircularList& l)
{
    ListIterator li(l);
    Employee* emp = li.First();
    if (emp == nullptr) return 0;
    int maxSal = emp->getSalary();
    emp = li.Next();
    while (emp != nullptr) {
        if (emp->getSalary() > maxSal)
            maxSal = emp->getSalary();
        emp = li.Next();
    }
    return maxSal;
}

// Enum ���� (������� Delete ���)
enum Enum {
    Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

// main �Լ� (void main)
void main() {
    Enum menu; // �޴�
    int selectMenu, num;
    string eno, ename;
    int pay;
    Employee* data;
    bool result = false;
    CircularList la, lb, lc;
    Employee* s;
    do {
        cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6.sum, 7.avg, 8.min, 9.max, 10.exit ����:: ";
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
                cout << "eno = " << eno << " ���� �Ϸ�.";
            else
                cout << "eno = " << eno << " ���� ����.";
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
            cout << "����Ʈ la�� ����" << endl;
            la.Erase();
            cout << "����Ʈ lb�� ����" << endl;
            lb.Erase();
            cout << "����Ʈ la = ";
            la.Show();
            cout << endl << "����Ʈ lb = ";
            lb.Show();
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
        case Exit: // ���α׷� ����
            break;
        default:
            cout << "�߸��� �����Դϴ�.";
            break;
        }
    } while (static_cast<Enum>(selectMenu) != Exit);
    
    // ���α׷� ���� ���� �Է��� ��� (���� ����)
    cin >> num;
}
