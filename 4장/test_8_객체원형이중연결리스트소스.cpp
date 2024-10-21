/*
 * �ܰ�8 : ���� ��ü ���� ���� ����Ʈ�� available list, getNode, retNode
 * head node�� ���� �ְ� ������ ������ available list�� �����Ѵ�.
 * CircularDoublyList�� ������� �� iterator�� �����Ѵ�.
 * Template ���� ���� 
 */

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string>
using namespace std;

// Forward declarations
template<class T> class DoublyListNode;
template<class T> class CircularDoublyList;
template<class T> class CircularDoublyListIterator;

// ------------- Employee Ŭ���� -------------
class Employee {
    template<class T> friend class DoublyListNode;
    template<class T> friend class CircularDoublyList;
    template<class T> friend class CircularDoublyListIterator;
private:
    string eno;    // ��� ��ȣ
    string ename;  // ��� �̸�
    int salary;    // �޿�
public:
    Employee() {}
    Employee(string sno, string sname, int salary) :eno(sno), ename(sname), salary(salary) {}

    // operator<< ����
    friend ostream& operator<<(ostream& os, const Employee& emp);

    // operator== ���� (eno ����)
    bool operator==(const Employee& emp) const;

    // operator< ���� (eno ����)
    bool operator<(const Employee& emp) const;

    // operator> ���� (eno ����)
    bool operator>(const Employee& emp) const;

    // compare �Լ� ����
    char compare(const Employee* emp) const;

    // getSalary �Լ�
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

// operator< ���� (eno ����)
bool Employee::operator<(const Employee& emp) const {
    return this->eno < emp.eno;
}

// operator> ���� (eno ����)
bool Employee::operator>(const Employee& emp) const {
    return this->eno > emp.eno;
}

// compare �Լ� ����
char Employee::compare(const Employee* emp) const {
    if (this->eno < emp->eno) return '<';
    if (this->eno > emp->eno) return '>';
    return '=';
}

// ------------- DoublyListNode Ŭ���� -------------
template<class T>
class DoublyListNode {
    friend class CircularDoublyList<T>;
    friend class CircularDoublyListIterator<T>;
public:
    DoublyListNode(T* p) {
        data = *p;
        llink = rlink = this;
    }
    DoublyListNode() {
        llink = rlink = this;
    }
private:
    T data;
    DoublyListNode<T>* llink, * rlink;
};

// ListNode operator<< ���� (���ʼ�, �ַ� ���� ���)
template <class T>
ostream& operator<<(ostream& os, const DoublyListNode<T>& ln) {
    os << ln.data;
    return os;
}

// ------------- CircularDoublyList Ŭ���� -------------
template<class T>
class CircularDoublyList {
    friend class CircularDoublyListIterator<T>;
public:
    CircularDoublyList() { 
        first = GetNode();    // ���� ��� ����
        first->rlink = first; // ���� ����� ������ ��ũ�� �ڱ� �ڽ�
        first->llink = first; // ���� ����� ���� ��ũ�� �ڱ� �ڽ�
        last = first;         // �ʱ⿡�� last�� ���� ��带 ����Ŵ
    }

    // ���� ������
    CircularDoublyList(const CircularDoublyList<T>& l) {
        if (l.first == l.last) { // �� ����Ʈ
            first = GetNode();
            first->rlink = first;
            first->llink = first;
            last = first;
            return;
        }
        // ������ ����Ʈ�� ������� ���� ���
        first = GetNode();    // ���ο� ���� ��� ����
        first->rlink = first;
        first->llink = first;
        last = first;
        DoublyListNode<T>* current = l.first->rlink; // ù ��° ���� ���
        while (current != l.first) {
            Add(&current->data);
            current = current->rlink;
        }
    }

    ~CircularDoublyList() {
        Erase();
        RetNode(first);
    }

    // Add �Լ�: eno ���� ������������ ����
    void Add(T* element) {
        DoublyListNode<T>* newNode = GetNode();
        newNode->data = *element;

        if (last->rlink == first) { // ����Ʈ�� ����ִ� ���
            // �� ��带 ����Ʈ�� ����
            newNode->rlink = first; // �� ����� ������ ��ũ�� ���� ���
            newNode->llink = last;   // �� ����� ���� ��ũ�� ���� ���
            first->rlink = newNode;  // ���� ����� ������ ��ũ�� �� ���
            first->llink = newNode;  // ���� ����� ���� ��ũ�� �� ���
            last = newNode;          // last�� �� ���� ������Ʈ
            return;
        }

        // eno ���� ������������ ���� ��ġ ã��
        DoublyListNode<T>* current = first->rlink; // ù ��° ���� ���
        while (current != first && current->data.eno < newNode->data.eno) {
            current = current->rlink;
        }

        if (current == first) { // ����Ʈ�� ���� ����
            newNode->rlink = first;
            newNode->llink = last;
            last->rlink = newNode;
            first->llink = newNode;
            last = newNode;
        }
        else { // �߰� �Ǵ� ���� ��ġ�� ����
            newNode->rlink = current;
            newNode->llink = current->llink;
            current->llink->rlink = newNode;
            current->llink = newNode;
        }
    }

    // Delete �Լ�: eno �������� ��� ����
    bool Delete(string eno) {
        if (last->rlink == first) return false; // �� ����Ʈ
        DoublyListNode<T>* current = first->rlink; // ù ��° ���� ���
        while (current != first) {
            if (current->data.eno == eno) {
                // ��ũ ����
                current->llink->rlink = current->rlink;
                current->rlink->llink = current->llink;
                if (current == last) { // ������ ��尡 ������ ����� ���
                    last = current->llink;
                }
                RetNode(current); // ��带 available list�� ��ȯ
                return true;
            }
            current = current->rlink;
        }
        return false; // eno�� ���� ����� ����
    }

    // Search �Լ�: eno �������� ��� �˻�
    bool Search(string eno) {
        if (last->rlink == first) return false; // �� ����Ʈ
        DoublyListNode<T>* current = first->rlink; // ù ��° ���� ���
        while (current != first) {
            if (current->data.eno == eno) return true;
            current = current->rlink;
        }
        return false;
    }

    // Show �Լ�: ����Ʈ�� ��� ��带 ���
    void Show() const {
        if (last->rlink == first) { // �� ����Ʈ
            cout << "����Ʈ�� ��� �ֽ��ϴ�." << endl;
            return;
        }
        DoublyListNode<T>* p = first->rlink; // ù ��° ���� ���
        while (p != first) {
            cout << p->data << " <-> ";
            p = p->rlink;
        }
        cout << "head" << endl;
    }

    // Erase �Լ�: ��� ��带 �����ϰ� available list�� ��ȯ
    void Erase() {
        if (last->rlink == first) return; // �� ����Ʈ
        DoublyListNode<T>* current = first->rlink; // ù ��° ���� ���
        while (current != first) {
            DoublyListNode<T>* temp = current;
            current = current->rlink;
            RetNode(temp);
        }
        first->rlink = first; // ���� ����� ��ũ�� �ڱ� �ڽ����� ����
        first->llink = first; // ���� ����� ���� ��ũ�� �ڱ� �ڽ����� ����
        last = first;         // last�� ���� ���� �缳��
    }

    // operator+ ����: �� ����Ʈ�� �����Ͽ� ���ο� ����Ʈ�� ��ȯ
    CircularDoublyList<T> operator+(const CircularDoublyList<T>& lb) const {
        CircularDoublyList<T> lc;
        CircularDoublyListIterator<T> Aiter(*this);
        CircularDoublyListIterator<T> Biter(lb);
        T* p = Aiter.First();
        T* q = Biter.First();

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
                lc.Add(p); // �Ǵ� �����͸� �����Ϸ��� �߰� ���� �ʿ�
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

    // GetNode �Լ�: available list���� ��带 �������ų� �� ��带 ����
    DoublyListNode<T>* GetNode() {
        if (av != nullptr) { // available list�� ��尡 ������
            DoublyListNode<T>* temp = av;
            av = av->rlink; // rlink�� ����Ͽ� available list�� ��ȸ
            temp->llink = temp->rlink = temp; // ��ũ �ʱ�ȭ
            return temp;
        }
        else { // ������ �� ��� ����
            return new DoublyListNode<T>();
        }
    }

    // RetNode �Լ�: ��带 available list�� ��ȯ
    void RetNode(DoublyListNode<T>* x) {
        x->rlink = av; // rlink�� ����Ͽ� available list�� �߰�
        av = x;
    }

    // Friend operator<< ����
    template <class T>
    friend ostream& operator<<(ostream&, const CircularDoublyList<T>&);

private:
    DoublyListNode<T>* first;    // ���� ��带 ����Ű�� ������
    DoublyListNode<T>* last;     // ������ ��带 ����Ű�� ������
    static DoublyListNode<T>* av; // available list (static)
};

// static ���� �ʱ�ȭ
template<class T>
DoublyListNode<T>* CircularDoublyList<T>::av = nullptr;

// operator<< ����
template<class T>
ostream& operator<<(ostream& os, const CircularDoublyList<T>& l)
{
    l.Show();
    return os;
}

// ------------- CircularDoublyListIterator Ŭ���� -------------
template<class T>
class CircularDoublyListIterator {
public:
    CircularDoublyListIterator(const CircularDoublyList<T>& l) : list(l), current(l.first->rlink) {}

    ~CircularDoublyListIterator() {}

    // ����Ʈ�� ����ִ��� Ȯ��
    bool NotNull() const {
        return list.first != list.last;
    }

    // ���� ��尡 �ִ��� Ȯ��
    bool NextNotNull() const {
        return current->rlink != list.first;
    }

    // ù ��° ���� �̵�
    T* First() {
        if (list.first == list.last) { // �� ����Ʈ
            return nullptr;
        }
        current = list.first->rlink;
        return &current->data;
    }

    // ���� ���� �̵�
    T* Next() {
        if (current->rlink == list.first) { // ���� ����Ʈ�� ��
            return nullptr;
        }
        current = current->rlink;
        return &current->data;
    }

    // ���� ��� ��ȯ
    T* GetCurrent() {
        if (current != list.first) {
            return &current->data;
        }
        return nullptr;
    }

private:
    const CircularDoublyList<T>& list;
    DoublyListNode<T>* current;
};

// ------------- ���� �Լ� ���� -------------
template<class T>
int sum(const CircularDoublyList<T>& l)
{
    int total = 0;
    CircularDoublyListIterator<T> iter(l);
    T* p = iter.First();
    while (p != nullptr) {
        total += p->getSalary();
        p = iter.Next();
    }
    return total;
}

template<class T>
double avg(const CircularDoublyList<T>& l)
{
    int total = 0;
    int count = 0;
    CircularDoublyListIterator<T> iter(l);
    T* p = iter.First();
    while (p != nullptr) {
        total += p->getSalary();
        count++;
        p = iter.Next();
    }
    if (count == 0) return 0.0;
    return static_cast<double>(total) / count;
}

template<class T>
int min(const CircularDoublyList<T>& l)
{
    if (l.first == l.last) return 0; // �� ����Ʈ
    CircularDoublyListIterator<T> iter(l);
    T* p = iter.First();
    if (p == nullptr) return 0;
    int minimum = p->getSalary();
    p = iter.Next();
    while (p != nullptr) {
        if (p->getSalary() < minimum)
            minimum = p->getSalary();
        p = iter.Next();
    }
    return minimum;
}

template<class T>
int max(const CircularDoublyList<T>& l)
{
    if (l.first == l.last) return 0; // �� ����Ʈ
    CircularDoublyListIterator<T> iter(l);
    T* p = iter.First();
    if (p == nullptr) return 0;
    int maximum = p->getSalary();
    p = iter.Next();
    while (p != nullptr) {
        if (p->getSalary() > maximum)
            maximum = p->getSalary();
        p = iter.Next();
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
    CircularDoublyList<Employee> la, lb, lc;
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
            cout << *data << endl;
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
            cout << *data << endl;
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
            cout << "����Ʈ la�� ����" << endl;
            la.Erase();
            cout << "����Ʈ lb�� ����" << endl;
            lb.Erase();
            cout << "����Ʈ la = ";
            la.Show();
            cout << "����Ʈ lb = ";
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
