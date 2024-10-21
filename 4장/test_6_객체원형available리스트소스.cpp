/*
* 6�ܰ�- ���� ��ü ���� ����Ʈ�� available list, getNode, retNode
* head node�� ���� �ְ� ������ ������ available list�� �����Ѵ�.
* CircularList�� ������� �� iterator�� �����Ѵ�.
* template version���� ���� 
*/
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// ------------- Employee Ŭ���� -------------
class Employee {
    friend class Node;
    friend class CircularList;
    friend class ListIterator;
private:
    string eno;    // ��� ��ȣ
    string ename;  // ��� �̸�
    int salary;    // �޿�
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

// operator<< ����
ostream& operator<<(ostream& os, const Employee& emp) {
    os << "[eno: " << emp.eno << ", ename: " << emp.ename << ", salary: " << emp.salary << "]";
    return os;
}

// operator== ���� (eno ����)
bool Employee::operator==(const Employee& emp) const {
    return this->eno == emp.eno;
}

// operator< ���� (eno ����, ��������)
bool Employee::operator<(const Employee& emp) const {
    return this->eno < emp.eno;
}

// compare �Լ� ����
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
    friend ostream& operator<<(ostream& os, const CircularList& l); // ģ�� �Լ� ���� �߰�
private:
    Employee data;
    Node* link;
public:
    Node() : link(nullptr) {}
    Node(const Employee& element) : data(element), link(nullptr) {}
};

// ------------- CircularList Ŭ���� -------------
class CircularList {
    friend class ListIterator;
    Node* first;       // ���� ��带 ����Ű�� ������
    Node* last;        // ������ ��带 ����Ű�� ������
    static Node* av;    // available list (static)
public:
    CircularList() {
        first = new Node(); // ���� ��� ����
        first->link = first; // �ڱ� �ڽ��� ����Ŵ (�� ����Ʈ)
        last = first;        // �ʱ⿡�� last�� ���� ��带 ����Ŵ
    }

    ~CircularList() {
        // ��� ��带 available list�� ��ȯ
        if (first != nullptr) {
            Node* p = first->link;
            while (p != first) {
                Node* temp = p;
                p = p->link;
                RetNode(temp);
            }
            RetNode(first); // ���� ��嵵 ��ȯ
            first = nullptr;
            last = nullptr;
        }
    }

    bool Delete(string); // eno�� ����
    void Show() const;    // ��ü ����Ʈ ���
    void Add(Employee*);  // eno �������� �����Ͽ� ����
    bool Search(string) const; // eno �˻�
    Node* GetNode();      // available list���� ��� ��������
    void RetNode(Node*); // ��� available list�� ��ȯ
    void Erase();         // ��� ��� ���� (available list�� ��ȯ)
    CircularList operator+(const CircularList& lb) const; // ����Ʈ ����
    friend ostream& operator<<(ostream& os, const CircularList& l);
};

// static ���� �ʱ�ȭ
Node* CircularList::av = nullptr;

// GetNode ����
Node* CircularList::GetNode() {
    if (av != nullptr) { // available list�� ��尡 ������
        Node* temp = av;
        av = av->link;
        return temp;
    }
    else { // ������ �� ��� ����
        return new Node();
    }
}

// RetNode ����
void CircularList::RetNode(Node* x) {
    x->link = av;
    av = x;
}

// operator<< ����
ostream& operator<<(ostream& os, const CircularList& l) {
    if (l.first->link == l.first) { // �� ����Ʈ
        os << "����Ʈ�� ��� �ֽ��ϴ�." << endl;
        return os;
    }
    Node* p = l.first->link; // ù ��° ���� ���
    do {
        os << p->data << " -> ";
        p = p->link;
    } while (p != l.first->link);
    os << "head" << endl;
    return os;
}

// Show ����
void CircularList::Show() const {
    if (first->link == first) { // �� ����Ʈ
        cout << "����Ʈ�� ��� �ֽ��ϴ�." << endl;
        return;
    }
    Node* p = first->link; // ù ��° ���� ���
    do {
        cout << p->data << " -> ";
        p = p->link;
    } while (p != first->link);
    cout << "head" << endl;
}

// Add ���� (eno ���� ��������)
void CircularList::Add(Employee* element) {
    Node* newNode = GetNode();
    newNode->data = *element;

    Node* p = first->link; // ù ��° ���� ���
    Node* q = first;       // ���� ���

    // �� ����Ʈ�̰ų�, ù ��庸�� eno�� ���� ���
    if (p == first || newNode->data.eno < p->data.eno) {
        newNode->link = p;
        q->link = newNode;
        if (p == first) { // ����Ʈ�� ��� �־��� ���, last�� �� ���� ����
            last = newNode;
        }
        return;
    }

    // ������ ��ġ ã��
    while (p != first && newNode->data.eno > p->data.eno) {
        q = p;
        p = p->link;
    }

    // eno�� ������ ��� ������Ʈ �� ��ȯ
    if (p != first && newNode->data.eno == p->data.eno) {
        p->data = newNode->data; // ���� �����͸� ���ο� �����ͷ� ��ü
        RetNode(newNode);        // �� ��� ��ȯ
        return;
    }

    // ��� ����
    newNode->link = p;
    q->link = newNode;

    // ������ ��带 ������Ʈ
    if (p == first) { // ����Ʈ�� ���� ���Ե� ���
        last = newNode;
    }
}

// Search ����
bool CircularList::Search(string eno) const {
    if (first->link == first) // �� ����Ʈ
        return false;

    Node* p = first->link; // ù ��° ���� ���
    while (p != first) { // head node����
        if (p->data.eno == eno)
            return true;
        p = p->link;
    }
    return false;
}

// Delete ����
bool CircularList::Delete(string eno) {
    if (first->link == first) // �� ����Ʈ
        return false;

    Node* p = first->link; // ù ��° ���� ���
    Node* q = first;       // ���� ���

    while (p != first) { // head node����
        if (p->data.eno == eno) {
            q->link = p->link;
            // ������ ��尡 last�� ��� last�� ���� ���� ������Ʈ
            if (p == last) {
                last = q;
                // ���� ����Ʈ�� ��� �Ǹ� last�� ���� ���� ����
                if (last == first) {
                    // ����Ʈ�� ������� �̹� q->link = first�� ���������Ƿ� �߰� �۾� �ʿ� ����
                }
            }
            RetNode(p);
            return true;
        }
        q = p;
        p = p->link;
    }
    return false; // eno�� ���� ����� ����
}

// Erase ���� (��� ��� ����)
void CircularList::Erase() {
    if (first->link == first) // �� ����Ʈ
        return;

    Node* p = first->link; // ù ��° ���� ���
    while (p != first) {
        Node* temp = p;
        p = p->link;
        RetNode(temp);
    }
    first->link = first; // �ڱ� �ڽ��� ����Ű���� ����
    last = first;        // ����Ʈ�� ������Ƿ� last�� ���� ���� ����
}

// operator+ ���� (�� ����Ʈ ����)
CircularList CircularList::operator+(const CircularList& lb) const {
    CircularList lc;
    ListIterator Aiter(*this);
    ListIterator Biter(lb);
    Employee* p = Aiter.First();
    Employee* q = Biter.First();

    while (p != nullptr && q != nullptr) {
        if (p->eno < q->eno) {
            lc.Add(p);
            p = Aiter.Next();
        }
        else if (p->eno > q->eno) {
            lc.Add(q);
            q = Biter.Next();
        }
        else { // eno�� ���� ��� �ϳ��� �߰�
            lc.Add(p);
            p = Aiter.Next();
            q = Biter.Next();
        }
    }

    // �����ִ� ��� �߰�
    while (p != nullptr) {
        lc.Add(p);
        p = Aiter.Next();
    }
    while (q != nullptr) {
        lc.Add(q);
        q = Biter.Next();
    }

    return lc;
}

// ------------- ListIterator Ŭ���� -------------
class ListIterator {
public:
    ListIterator(const CircularList& lst);
    ~ListIterator();
    bool NotNull();
    bool NextNotNull();
    Employee* First();
    Employee* Next();
    Employee& operator*() const;
    Employee* operator->() const;
    ListIterator& operator++(); // Pre-increment
    ListIterator operator++(int); // Post-increment
    bool operator!=(const ListIterator) const;
    bool operator==(const ListIterator) const;
    Employee* GetCurrent();
private:
    Node* current; // pointer to nodes
    const CircularList& list; // existing list
};

// ListIterator ������
ListIterator::ListIterator(const CircularList& lst) : list(lst), current(nullptr) {
    // �ʱ�ȭ �� ù ��° ���� ���� ����
    if (lst.first->link != lst.first) { // ����Ʈ�� ������� �ʴٸ�
        current = lst.first->link;
    }
}

// NotNull ����
bool ListIterator::NotNull() {
    return current != nullptr && current != list.first;
}

// NextNotNull ����
bool ListIterator::NextNotNull() {
    if (current && current->link != list.first)
        return true;
    return false;
}

// First ����
Employee* ListIterator::First() {
    if (list.first->link == list.first) { // �� ����Ʈ
        current = nullptr;
        return nullptr;
    }
    current = list.first->link; // ù ��° ���� ���
    return &current->data;
}

// Next ����
Employee* ListIterator::Next() {
    if (current && current->link != list.first) {
        current = current->link;
        return &current->data;
    }
    current = nullptr;
    return nullptr;
}

// GetCurrent ����
Employee* ListIterator::GetCurrent() {
    if (current != nullptr)
        return &current->data;
    return nullptr;
}

// Destructor
ListIterator::~ListIterator() {
    // Ư���� �޸� ���� �ʿ� ����
}

// Dereference operators
Employee& ListIterator::operator*() const {
    return current->data;
}

Employee* ListIterator::operator->() const {
    return &current->data;
}

// Pre-increment ������ ����
ListIterator& ListIterator::operator++() {
    if (current && current->link != list.first)
        current = current->link;
    else
        current = nullptr;
    return *this;
}

// Post-increment ������ ����
ListIterator ListIterator::operator++(int) {
    ListIterator temp = *this;
    if (current && current->link != list.first)
        current = current->link;
    else
        current = nullptr;
    return temp;
}

// operator!= ����
bool ListIterator::operator!=(const ListIterator right) const {
    return current != right.current;
}

// operator== ����
bool ListIterator::operator==(const ListIterator right) const {
    return current == right.current;
}

// ------------- sum, avg, min, max �Լ� ���� -------------
int sum(const CircularList& l)
{
    ListIterator li(l);
    int total = 0;
    Employee* p = li.First();
    while (p != nullptr) {
        total += p->getSalary();
        p = li.Next();
    }
    return total;
}

double avg(const CircularList& l)
{
    ListIterator li(l);
    int total = 0;
    int count = 0;
    Employee* p = li.First();
    while (p != nullptr) {
        total += p->getSalary();
        count++;
        p = li.Next();
    }
    if (count == 0)
        return 0.0;
    return static_cast<double>(total) / count;
}

int min(const CircularList& l)
{
    ListIterator li(l);
    Employee* p = li.First();
    if (p == nullptr)
        return 0; // �� ����Ʈ�� ���
    int minimum = p->getSalary();
    p = li.Next();
    while (p != nullptr) {
        if (p->getSalary() < minimum)
            minimum = p->getSalary();
        p = li.Next();
    }
    return minimum;
}

int max(const CircularList& l)
{
    ListIterator li(l);
    Employee* p = li.First();
    if (p == nullptr)
        return 0; // �� ����Ʈ�� ���
    int maximum = p->getSalary();
    p = li.Next();
    while (p != nullptr) {
        if (p->getSalary() > maximum)
            maximum = p->getSalary();
        p = li.Next();
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
    Employee* s;

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
                cout << "eno = " << eno << " ���� �Ϸ�." << endl;
            else
                cout << "eno = " << eno << " ���� ����: �ش� �����ȣ�� �����ϴ�." << endl;
            break;
        case ShowOp:
            cout << "����Ʈ la = " << la;
            cout << "����Ʈ lb = " << lb;
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
            cout << "����Ʈ lc = " << lc;
            cout << "����Ʈ la�� ����" << endl;
            la.Erase();
            cout << "����Ʈ lb�� ����" << endl;
            lb.Erase();
            cout << "����Ʈ la = " << la;
            cout << endl << "����Ʈ lb = " << lb;
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
