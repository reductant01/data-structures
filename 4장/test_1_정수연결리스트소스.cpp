#include <iostream>
#include <ctime> // <time.h> ��� <ctime> ���
using namespace std;

// Node Ŭ���� ����
class Node {
    friend class LinkedList; // LinkedList Ŭ������ Node�� private ����� ������ �� �ֵ��� ���
    int data;                // ��尡 �����ϴ� ���� ������
    Node* link;              // ���� ��带 ����Ű�� ������
public:
    // ������: ������ �ʱ�ȭ �� ��ũ�� nullptr�� ����
    Node(int element) {
        data = element;
        link = nullptr; // nullptr�� �ʱ�ȭ
    }
};

// LinkedList Ŭ���� ����
class LinkedList {
    Node* first; // ����Ʈ�� ù ��° ��带 ����Ű�� ������
public:
    // ������: ù ��° ��带 nullptr�� �ʱ�ȭ
    LinkedList() {
        first = nullptr; // nullptr�� �ʱ�ȭ
    }
    
    // �Ҹ���: ����Ʈ�� ��� ��带 �����Ͽ� �޸� ���� ����
    ~LinkedList();
    
    bool Delete(int);           // Ư�� �����͸� ���� ��带 �����ϴ� �Լ�
    void Show();                // ����Ʈ�� ��� ��带 ����ϴ� �Լ�
    void Add(int element);      // ������������ ��带 �߰��ϴ� �Լ�
    bool Search(int data);      // Ư�� �����͸� �˻��ϴ� �Լ�
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
void LinkedList::Add(int element) {
    Node* newNode = new Node(element);
    
    // ����Ʈ�� ����ְų� ù ����� �����Ͱ� ������ �����ͺ��� ũ�ų� ���� ���
    if (first == nullptr || first->data >= element) {
        newNode->link = first;
        first = newNode;
    }
    else {
        // ������ ��ġ�� ã�� ����
        Node* current = first;
        while (current->link != nullptr && current->link->data < element) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}

// Search �Լ� ����: Ư�� �����͸� ���� ��尡 �ִ��� �˻�
bool LinkedList::Search(int element) {
    Node* current = first;
    while (current != nullptr) {
        if (current->data == element)
            return true;
        current = current->link;
    }
    return false;
}

// Delete �Լ� ����: Ư�� �����͸� ���� ��� ����
bool LinkedList::Delete(int element) {
    if (first == nullptr)
        return false; // ����Ʈ�� ��������� ������ ��尡 ����

    // ù ��尡 ������ �����͸� ���� ���
    if (first->data == element) {
        Node* temp = first;
        first = first->link;
        delete temp;
        return true;
    }
    
    // ù ��尡 �ƴ� ��带 ������ ���
    Node* current = first;
    Node* prev = nullptr;
    while (current != nullptr && current->data != element) {
        prev = current;
        current = current->link;
    }
    
    if (current == nullptr)
        return false; // ������ �����͸� ���� ��带 ã�� ����
    
    prev->link = current->link;
    delete current;
    return true;

    // Node* current = first;
    // Node* prev = nullptr;
    
    // while (current != nullptr) {
    //     if (current->data == element) {
    //         if (prev == nullptr) {
    //             // ù ��° ��带 �����ϴ� ���
    //             first = current->link; // 'first' �����͸� ������Ʈ
    //         } 
    //         else {
    //             // ù ��° ��尡 �ƴ� ���
    //             prev->link = current->link;
    //         }
    //         delete current; // ��� ����
    //         return true;    // ���� ����
    //     }
    //     prev = current;
    //     current = current->link;
    // }
    // return false; // ������ ��带 ã�� ����
}

// ��ȯ Ÿ���� ��Ȳ�� �°� ����: ���ο� ��ü�� �����Ͽ� ��ȯ�ϴ� ��� �� ��ȯ��, ���� ��ü�� �����ϰ� ��ȯ�ϴ� ��� ���� ��ȯ�� ����մϴ�.
// operator+ ����: �� ����Ʈ�� �����Ͽ� ���ο� ����Ʈ ��ȯ (���ο� ����Ʈ�� ��ȯ�ؾ������� �� ��ȯ)
LinkedList LinkedList::operator+(LinkedList& lb) {
    LinkedList lc;
    Node* a = this->first;
    Node* b = lb.first;
    
    // �� ����Ʈ�� ��ȸ�ϸ� ���� ���� lc�� �߰�
    while (a != nullptr && b != nullptr) {
        if (a->data < b->data) {
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
    Enum menu;             // �޴� ����
    int selectMenu;        // ����� ���� �޴� ��ȣ
    bool result = false;   // �Լ� ��� ���� ����
    srand(static_cast<unsigned int>(time(nullptr))); // ���� �õ� �ʱ�ȭ
    LinkedList la, lb, lc; // �� ���� ���� ����Ʈ ����
    int data = 0;          // ������ �Է� ����
    
    do {
        // �޴� ���
        cout << "0.Add1, 1. Add2, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit ����:: ";
        cin >> selectMenu;
        
        // �޴� ���ÿ� ���� ����
        switch (static_cast<Enum>(selectMenu)) {
        case Add1:
            data = rand() % 49;
            cout << "la�� �߰��� ������: " << data << endl;
            la.Add(data);
            break;
        case Add2:
            data = rand() % 49;
            cout << "lb�� �߰��� ������: " << data << endl;
            lb.Add(data);
            break;
        case Delete:
            cout << "������ ������ �Է�: ";
            cin >> data;
            result = la.Delete(data);
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
            int n;
            cout << "�˻��� ������ �Է�: ";
            cin >> n;
            result = la.Search(n);
            if (!result)
                cout << "�˻� �� = " << n << " �����Ͱ� �����ϴ�." << endl;
            else
                cout << "�˻� �� = " << n << " �����Ͱ� �����մϴ�." << endl;
            break;
        }
        case Merge:
            lc = la + lb;
            cout << "����Ʈ lc = ";
            lc.Show();
            break;
        case Exit:
            break;
        default:
            cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���." << endl;
            break;
        }
    } while (static_cast<Enum>(selectMenu) != Exit);
    
    return 0; // ���α׷� ���� ����
}
