/*
* 2�ܰ�- ��ü ���� ����Ʈ: �ܼ��� linked list���� insert�� �ø��������� ���ĵǵ��� ó��, delete�ϴ� �˰����� �ڵ�
* template version���� ����
*/
#include <iostream>
#include <ctime> // <time.h> ��� <ctime> ���
using namespace std;

// Employee Ŭ���� ����
class Employee {
    friend class Node;
    friend class LinkedList;
    string eno;    // �����ȣ
    string ename;  // ����̸�
public:
    Employee() {}
    Employee(string sno, string sname) :eno(sno), ename(sname) {}
    
    // operator<< �����ε�: Employee ��ü ���
    friend ostream& operator<<(ostream& os, Employee& emp);
    
    // operator== �����ε�: eno ���� ��
    bool operator==(Employee& emp);
    
    // operator< �����ε�: eno ���� �������� ����
    bool operator<(Employee& emp);
};

// operator<< ����
ostream& operator<<(ostream& os, Employee& emp) {
    os << "�����ȣ: " << emp.eno << ", �̸�: " << emp.ename;
    return os;
}

// operator== ����
bool Employee::operator==(Employee& emp) {
    return this->eno == emp.eno;
}

// operator< ����
bool Employee::operator<(Employee& emp) {
    return this->eno < emp.eno;
}

// Node Ŭ���� ����
class Node {
    friend class LinkedList;
    Employee data;
    Node* link;
public:
    Node(Employee element) : data(element), link(nullptr) {}
};

// LinkedList Ŭ���� ����
class LinkedList {
    Node* first;
public:
    LinkedList() : first(nullptr) {}
    ~LinkedList();
    
    bool Delete(string);           // Ư�� �����͸� ���� ��带 �����ϴ� �Լ�
    void Show();                   // ����Ʈ�� ��� ��带 ����ϴ� �Լ�
    void Add(Employee);            // ������������ ��带 �߰��ϴ� �Լ�
    bool Search(string);           // Ư�� �����͸� �˻��ϴ� �Լ�
    LinkedList operator+(LinkedList&); // �� ����Ʈ�� �����ϴ� ������ �����ε�
};

// �Ҹ��� ����: ����Ʈ�� ��� ��带 �����Ͽ� �޸� ���� ����
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

// Add �Լ� ����: ������������ ���ĵǵ��� ��� ����
void LinkedList::Add(Employee element) // eno�� ���ĵǵ��� ����
{
    Node* newNode = new Node(element);
    
    // ����Ʈ�� ����ְų� ù ����� eno�� ������ eno���� ū ���
    if (first == nullptr || first->data < element) {
        newNode->link = first;
        first = newNode;
    }
    else {
        // ������ ��ġ�� ã�� ����
        Node* current = first;
        while (current->link != nullptr && !(current->link->data < element)) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}

// Search �Լ� ����: Ư�� eno�� ���� ��尡 �ִ��� �˻�
bool LinkedList::Search(string eno) { // eno�� ���� ���ڵ带 ã��
    Node* ptr = first;
    while (ptr != nullptr) {
        if (ptr->data.eno == eno)
            return true;
        ptr = ptr->link;
    }
    return false;
}

// Delete �Լ� ����: Ư�� eno�� ���� ��� ����
bool LinkedList::Delete(string eno) // delete the element
{
    if (first == nullptr)
        return false; // ����Ʈ�� ��������� ������ ��尡 ����

    // ù ��尡 ������ �����͸� ���� ���
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
    Node* a = this->first;
    Node* b = lb.first;
    
    // �� ����Ʈ�� ��ȸ�ϸ� ���� eno�� ���� �����͸� lc�� �߰�
    while (a != nullptr && b != nullptr) {
        if (a->data < b->data) { // a�� eno�� b�� eno���� ���� ���
            lc.Add(a->data);
            a = a->link;
        }
        else {
            lc.Add(b->data);
            b = b->link;
        }
    }
    
    // �����ִ� ��带 lc�� �߰�
    while (a != nullptr) {
        lc.Add(a->data);
        a = a->link;
    }
    
    while (b != nullptr) {
        lc.Add(b->data);
        b = b->link;
    }
    
    return lc; // ���ο� ����Ʈ ��ȯ
}

// ������ ����: �޴� ������ ���� ���
enum Enum {
    Add1, Add2, Delete, Show, Search, Merge, Exit
};

// main �Լ�: ���α׷��� ������
int main() { // void main()�� int main()���� ����
    int selectMenu, num;
    string eno, ename;
    bool result = false;
    LinkedList la, lb, lc; // �� ���� ���� ����Ʈ ����
    Employee* data = nullptr;
    
    do {
        // �޴� ���
        cout << "0.Add1, 1.Add2, 2.Delete, 3.Show, 4.Search, 5.Merge, 6.Exit ����:: ";
        cin >> selectMenu;
        
        // �Է°� ����
        if (selectMenu < 0 || selectMenu > 6) {
            cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���." << endl;
            continue; // ������ ���� �ݺ����� �̵�
        }
        
        // �޴� ���ÿ� ���� ����
        switch (static_cast<Enum>(selectMenu)) {
        case Add1:
            cout << "�����ȣ �Է�:: ";
            cin >> eno;
            cout << "��� �̸� �Է�:: ";
            cin >> ename;
            data = new Employee(eno, ename);
            la.Add(*data);
            delete data; // ���� �Ҵ� ����
            break;
        case Add2:
            cout << "�����ȣ �Է�:: ";
            cin >> eno;
            cout << "��� �̸� �Է�:: ";
            cin >> ename;
            data = new Employee(eno, ename);
            lb.Add(*data);
            delete data; // ���� �Ҵ� ����
            break;
        case Delete:
            cout << "�����ȣ �Է�:: ";
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
        case Exit:
            cout << "���α׷��� �����մϴ�." << endl;
            break;
        default:
            cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���." << endl;
            break;
        }
    } while (static_cast<Enum>(selectMenu) != Exit);
    
    return 0; // ���α׷� ���� ����
}
