/*
* 3�ܰ�-��ü ���� ����Ʈ�� iterator ����
* template �������� ����
*/
#include <iostream>
#include <ctime> // <time.h> ��� <ctime> ���
using namespace std;

// Employee Ŭ���� ����
class Employee {
    friend class Node;
    friend class LinkedList;
    friend class ListIterator;
private:
    string eno;     // �����ȣ
    string ename;   // ����̸�
    int salary;     // ��� �޿�
public:
    Employee() {}
    Employee(string sno, string sname, int sal) : eno(sno), ename(sname), salary(sal) {}
    
    // operator<< �����ε�: Employee ��ü ���
    friend ostream& operator<<(ostream& os, Employee& emp);
    
    // operator== �����ε�: eno ���� ��
    bool operator==(Employee& emp);
    
    // operator< �����ε�: eno ���� �������� ����
    bool operator<(Employee& emp);
    
    // compare �Լ�: eno ���� �� ��� ��ȯ ('<', '>', '=')
    char compare(const Employee*) const;
    
    // �޿� ��ȯ �Լ�
    int getSalary() const {
        return salary;
    }
};

// operator<< ����
ostream& operator<<(ostream& os, Employee& emp) {
    os << "�����ȣ: " << emp.eno << ", �̸�: " << emp.ename << ", �޿�: " << emp.salary;
    return os;
}

// operator== ����: eno�� �������� ��
bool Employee::operator==(Employee& emp) {
    return this->eno == emp.eno;
}

// operator< ����: eno�� �������� �������� ����
bool Employee::operator<(Employee& emp) {
    return this->eno < emp.eno;
}

// compare �Լ� ����: eno ���� ��
char Employee::compare(const Employee* emp) const {
    if (this->eno < emp->eno)
        return '<';
    else if (this->eno > emp->eno)
        return '>';
    else
        return '=';
}

// Node Ŭ���� ����
class Node {
    friend class ListIterator;
    friend class LinkedList;
    Employee data; // ��尡 �����ϴ� Employee ��ü
    Node* link;    // ���� ��带 ����Ű�� ������
public:
    Node() : data(), link(nullptr) {}
    Node(Employee element) : data(element), link(nullptr) {}
};

// Forward ����
class ListIterator;

// LinkedList Ŭ���� ����
class LinkedList {
    friend class ListIterator;
    Node* first; // ����Ʈ�� ù ��° ��带 ����Ű�� ������
public:
    LinkedList() : first(nullptr) {}
    
    // �Ҹ���: ����Ʈ�� ��� ��带 �����Ͽ� �޸� ���� ����
    ~LinkedList();
    
    bool Delete(string);           // Ư�� eno�� ���� ��带 �����ϴ� �Լ�
    void Show();                   // ����Ʈ�� ��� ��带 ����ϴ� �Լ�
    void Add(Employee);            // eno�� ���ĵǵ��� ��带 �߰��ϴ� �Լ�
    bool Search(string);           // Ư�� eno�� �˻��ϴ� �Լ�
    LinkedList operator+(LinkedList&); // �� ����Ʈ�� �����ϴ� ������ �����ε�
};

// �Ҹ��� ����: ����Ʈ�� ��� ��带 ����
LinkedList::~LinkedList() {
    Node* current = first;
    while (current != nullptr) {
        Node* temp = current;
        current = current->link;
        delete temp;
    }
}

// Show �Լ� ����: ����Ʈ�� ��� ��带 ������� ���
void LinkedList::Show() {
    Node* p = first;
    while (p != nullptr) {
        cout << p->data << " -> ";
        p = p->link;
    }
    cout << "nullptr" << endl;
}

// Add �Լ� ����: eno ���� ������������ ���ĵǵ��� ��带 ����
void LinkedList::Add(Employee element) {
    Node* newNode = new Node(element);
    
    // ����Ʈ�� ����ְų� ���ο� ��尡 ù ��庸�� ���� ���
    if (first == nullptr || element < first->data) {
        newNode->link = first;
        first = newNode;
    }
    else {
        // ���� ���� ���� ��带 ����
        Node* prev = first;
        Node* current = first->link;
        
        // ������ ��ġ�� ã�� ���� Ž��
        while (current != nullptr && !(element < current->data)) {
            prev = current;
            current = current->link;
        }
        
        // ���ο� ��带 ���� ��� �ڿ� ����
        newNode->link = current;
        prev->link = newNode;
    }
}


// Search �Լ� ����: Ư�� eno�� ���� ��尡 �ִ��� �˻�
bool LinkedList::Search(string eno) {
    Node* ptr = first;
    while (ptr != nullptr) {
        if (ptr->data.eno == eno)
            return true;
        ptr = ptr->link;
    }
    return false;
}

// Delete �Լ� ����: Ư�� eno�� ���� ��� ����
bool LinkedList::Delete(string eno) {
    if (first == nullptr)
        return false; // ����Ʈ�� ��������� ������ ��尡 ����

    // ù ��尡 ������ eno�� ���� ���
    if (first->data.eno == eno) {
        Node* temp = first;
        first = first->link;
        delete temp;
        return true;
    }

    // ù ��尡 �ƴ� ��带 ������ ���
    Node* current = first->link; // �� ��° ������ ����
    Node* prev = first;
    while (current != nullptr && current->data.eno != eno) {
        prev = current;
        current = current->link;
    }

    if (current == nullptr)
        return false; // ������ �����͸� ���� ��带 ã�� ����

    prev->link = current->link;
    delete current;
    return true;
}

// operator+ ����: �� ����Ʈ�� �����Ͽ� ���ο� ����Ʈ ��ȯ
LinkedList LinkedList::operator+(LinkedList& lb) {
    LinkedList lc;
    ListIterator Aiter(*this);
    ListIterator Biter(lb);
    Employee* p = Aiter.First();
    Employee* q = Biter.First();

    while (p != nullptr && q != nullptr) {
        if (*p < *q) { // a�� eno�� b�� eno���� ���� ���
            lc.Add(*p);
            p = Aiter.Next();
        }
        else { // b�� eno�� a�� eno���� �۰ų� ���� ���
            lc.Add(*q);
            q = Biter.Next();
        }
    }

    // �����ִ� ��带 lc�� �߰�
    while (p != nullptr) {
        lc.Add(*p);
        p = Aiter.Next();
    }

    while (q != nullptr) {
        lc.Add(*q);
        q = Biter.Next();
    }

    return lc; // ���ο� ����Ʈ ��ȯ
}

// ListIterator Ŭ���� ����
class ListIterator {
public:
    // ������: ����Ʈ�� ù ��带 ���� ��ġ�� ����
    ListIterator(const LinkedList& lst);
    
    // �Ҹ���
    ~ListIterator();
    
    // ���� ��尡 nullptr�� �ƴ��� Ȯ��
    bool NotNull();
    
    // ���� ��尡 nullptr�� �ƴ��� Ȯ��
    bool NextNotNull();
    
    // ù ��° ����� �����͸� ��ȯ
    Employee* First();
    
    // ���� ����� �����͸� ��ȯ
    Employee* Next();
    
    // ���� ����� �����͸� ������
    Employee& operator*() const;
    
    // ���� ����� �����͸� �����ͷ� ��ȯ
    Employee* operator->() const;
    
    // ���� ���� ������: ���� ��带 ���� ���� �̵�
    ListIterator& operator++();
    
    // ���� ���� ������: ���� ��带 ���� ���� �̵�
    ListIterator operator++(int);
    
    // �� ���ͷ����Ͱ� �ٸ� ��带 ����Ű���� ��
    bool operator!=(const ListIterator right) const;
    
    // �� ���ͷ����Ͱ� ���� ��带 ����Ű���� ��
    bool operator==(const ListIterator right) const;
    
    // ���� ����� �����͸� ��ȯ
    Employee* GetCurrent();
private:
    Node* current;             // ���� ��带 ����Ű�� ������
    const LinkedList& list;    // ���� ����Ʈ�� ���� ����
};

// ListIterator ������ ����
ListIterator::ListIterator(const LinkedList& lst) : list(lst), current(lst.first) {
    cout << "List Iterator is constructed" << endl;
}

// ListIterator �Ҹ��� ����
ListIterator::~ListIterator() {}

// NotNull �Լ� ����
bool ListIterator::NotNull() {
    return current != nullptr;
}

// NextNotNull �Լ� ����
bool ListIterator::NextNotNull() {
    if (current != nullptr && current->link != nullptr)
        return true;
    return false;
}

// First �Լ� ����
Employee* ListIterator::First() {
    if (list.first != nullptr)
        return &list.first->data;
    return nullptr;
}

// Next �Լ� ����
Employee* ListIterator::Next() {
    if (current != nullptr) {
        current = current->link;
        if (current != nullptr) {  
            return &current->data;
        }
    }
    return nullptr;
}


// GetCurrent �Լ� ����
Employee* ListIterator::GetCurrent() {
    if (current != nullptr)
        return &current->data;
    return nullptr;
}

// operator* ����
Employee& ListIterator::operator*() const {
    return current->data;
}

// operator-> ����
Employee* ListIterator::operator->() const {
    return &current->data;
}

// ���� ���� ������ ����
ListIterator& ListIterator::operator++() { // ���� ��ȯ�Ҷ��� ListIterator, ������ �ִ� ���� �Ҷ��� ListIterator&
    if (current != nullptr)
        current = current->link;
    return *this;
}

// ���� ���� ������ ����
ListIterator ListIterator::operator++(int) {
    ListIterator old = *this;
    if (current != nullptr)
        current = current->link;
    return old;
}

// operator!= ����
bool ListIterator::operator!=(const ListIterator right) const {
    return current != right.current;
}

// operator== ����
bool ListIterator::operator==(const ListIterator right) const {
    return current == right.current;
}

// sum �Լ� ����: ����Ʈ�� ��� ��� �޿� �հ�
int sum(const LinkedList& l) {
    ListIterator li(l);
    int total = 0;
    while (li.NotNull()) {
        total += li.GetCurrent()->getSalary();
        li++;
    }
    return total;
}

// avg �Լ� ����: ����Ʈ�� ��� ��� �޿� ���
double avg(const LinkedList& l) {
    ListIterator li(l);
    int total = 0;
    int count = 0;
    while (li.NotNull()) {
        total += li.GetCurrent()->getSalary();
        count++;
        li++;
    }
    if (count == 0)
        return 0.0;
    return static_cast<double>(total) / count;
}

// min �Լ� ����: ����Ʈ�� ��� ��� �޿� �� �ּҰ�
int min(const LinkedList& l) {
    ListIterator li(l);
    if (!li.NotNull())
        return 0; // �Ǵ� ������ ���� ó��
    int minimum = li.GetCurrent()->getSalary();
    li++;
    while (li.NotNull()) {
        int sal = li.GetCurrent()->getSalary();
        if (sal < minimum)
            minimum = sal;
        li++;
    }
    return minimum;
}

// max �Լ� ����: ����Ʈ�� ��� ��� �޿� �� �ִ밪
int max(const LinkedList& l) {
    ListIterator li(l);
    if (!li.NotNull())
        return 0; // �Ǵ� ������ ���� ó��
    int maximum = li.GetCurrent()->getSalary();
    li++;
    while (li.NotNull()) {
        int sal = li.GetCurrent()->getSalary();
        if (sal > maximum)
            maximum = sal;
        li++;
    }
    return maximum;
}

// ������ ����: �޴� ������ ���� ���
enum Enum {
    Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

// main �Լ�: ���α׷��� ������
int main() { // void main()�� int main()���� ����
    int selectMenu, num;
    string eno, ename;
    int pay;
    bool result = false;
    LinkedList la, lb, lc;
    Employee* data = nullptr;
    
    do {
        // �޴� ���
        cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6.Sum, 7.Avg, 8.Min, 9.Max, 10.Exit ����:: ";
        cin >> selectMenu;
        
        // �Է°� ����
        if (selectMenu < 0 || selectMenu > 10) {
            cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���." << endl;
            continue; // ������ ���� �ݺ����� �̵�
        }
        
        // �޴� ���ÿ� ���� ����
        switch (static_cast<Enum>(selectMenu)) {
        case Add0:
            cout << "�����ȣ �Է�:: ";
            cin >> eno;
            cout << "��� �̸� �Է�:: ";
            cin >> ename;
            cout << "��� �޿� �Է�:: ";
            cin >> pay;
            data = new Employee(eno, ename, pay);
            la.Add(*data);
            delete data; // �޸� ���� ������ ���� ���� �Ҵ� ����
            cout << "����� la ����Ʈ�� �߰��Ǿ����ϴ�." << endl;
            break;
        case Add1:
            cout << "�����ȣ �Է�:: ";
            cin >> eno;
            cout << "��� �̸� �Է�:: ";
            cin >> ename;
            cout << "��� �޿� �Է�:: ";
            cin >> pay;
            data = new Employee(eno, ename, pay);
            lb.Add(*data);
            delete data; // �޸� ���� ������ ���� ���� �Ҵ� ����
            cout << "����� lb ����Ʈ�� �߰��Ǿ����ϴ�." << endl;
            break;
        case Delete:
            cout << "������ �����ȣ �Է�:: ";
            cin >> eno;
            result = la.Delete(eno);
            if (result)
                cout << "���� �Ϸ�" << endl;
            else
                cout << "������ �����͸� ã�� �� �����ϴ�." << endl;
            break;
        case Show:
            cout << "����Ʈ la = ";
            la.Show();
            cout << "����Ʈ lb = ";
            lb.Show();
            cout << "����Ʈ lc = ";
            lc.Show();
            break;
        case Search: { // �߰�ȣ �߰��Ͽ� ���� ���� ���� ����
            cout << "�˻��� �����ȣ �Է�:: ";
            cin >> eno;
            result = la.Search(eno);
            if (!result)
                cout << "�˻� �� = " << eno << " �����Ͱ� �����ϴ�." << endl;
            else
                cout << "�˻� �� = " << eno << " �����Ͱ� �����մϴ�." << endl;
            break;
        }
        case Merge:
            lc = la + lb;
            cout << "����Ʈ lc = ";
            lc.Show();
            break;
        case SUM:
            cout << "Sum of salaries in la = " << sum(la) << endl;
            break;
        case AVG:
            cout << "Average salary in la = " << avg(la) << endl;
            break;
        case MIN:
            cout << "Minimum salary in la = " << min(la) << endl;
            break;
        case MAX:
            cout << "Maximum salary in la = " << max(la) << endl;
            break;
        case Exit:
            cout << "���α׷��� �����մϴ�." << endl;
            break;
        default:
            // �� ���� �̹� �Է°� ������ �����Ƿ� ������� ����
            break;
        }
    } while (static_cast<Enum>(selectMenu) != Exit);
    
    return 0; // ���α׷� ���� ����
}
