/*
* 4단계- 원형 객체 연결 리스트의 iterator 버젼
* CircularList를 대상으로 한 iterator를 구현한다.
* template 버전으로 구현 
*/
#include <iostream>
#include <string>
using namespace std;

// ------------- Employee 클래스 -------------
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
    os << "사원번호: " << emp.eno << ", 이름: " << emp.ename << ", 급여: " << emp.salary;
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

// ------------- Node 클래스 -------------
class Node {
    friend class ListIterator;
    friend class CircularList;
    Employee data;
    Node* link;
public:
    Node() : link(nullptr) {}
    Node(const Employee& element) : data(element), link(nullptr) {}
};

// ------------- ListIterator 클래스 -------------
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
    ListIterator& operator++(); // 전위 증감 연산자
    ListIterator operator++(int); // 후위 증감 연산자
    bool operator!=(const ListIterator& right) const;
    bool operator==(const ListIterator& right) const;
    Employee* GetCurrent() const;
private:
    Node* current; // 현재 노드를 가리키는 포인터
    const CircularList& list; // 기존 리스트에 대한 참조
};

// ------------- CircularList 클래스 -------------
class CircularList {
    friend class ListIterator;
    Node* first; // 더미 노드를 가리키는 포인터
public:
    CircularList() {
        first = new Node(); // 더미 노드 생성
        first->link = first; // 자기 자신을 가리킴
    }
    ~CircularList();
    bool Delete(string);
    void Show() const;
    void Add(Employee*); // eno 기준으로 정렬하여 삽입
    bool Search(string) const;
    CircularList operator+(const CircularList& lb) const;
    friend ostream& operator<<(ostream& os, const CircularList& l);
};

// ------------- CircularList 메서드 구현 -------------
CircularList::~CircularList() {
    if (first == nullptr)
        return;
    Node* p = first->link;
    // 노드가 하나뿐인 경우 (리스트가 비어있는 경우 더미 노드만 존재)
    if (p == first) {
        delete first;
        first = nullptr;
        return;
    }
    // 노드가 여러 개인 경우
    while (p != first) {
        Node* temp = p;
        p = p->link;
        delete temp;
    }
    delete first;
    first = nullptr;
}

bool CircularList::Delete(string eno) {
    if (first->link == first) // 리스트가 비어있는 경우
        return false;

    Node* p = first->link; // 현재 노드
    Node* q = first;       // 이전 노드

    do {
        if (p->data.eno == eno) {
            q->link = p->link;
            delete p;
            return true;
        }
        q = p;
        p = p->link;
    } while (p != first);

    return false; // eno를 가진 사원이 없음
}

void CircularList::Show() const { // 전체 리스트를 순서대로 출력
    if (first->link == first) {
        cout << "리스트가 비어 있습니다." << endl;
        return;
    }

    Node* p = first->link;
    do {
        cout << p->data << " -> ";
        p = p->link;
    } while (p != first);
    cout << "first" << endl;
}

void CircularList::Add(Employee* element) { // eno 기준으로 정렬하여 삽입
    Node* newNode = new Node(*element);
    Node* p = first->link; // 첫 번째 실제 노드
    Node* q = first;       // 이전 노드

    // 리스트가 비어있거나, 첫 노드보다 작은 eno를 가진 경우
    if (p == first || element->eno < p->data.eno) {
        newNode->link = p;
        q->link = newNode;
        return;
    }

    // 적절한 위치를 찾기
    while (p != first && !(element->eno < p->data.eno)) {
        q = p;
        p = p->link;
    }

    // 노드 삽입
    newNode->link = p;
    q->link = newNode;
}

bool CircularList::Search(string eno) const { // eno를 갖는 레코드를 찾기
    if (first->link == first) // 리스트가 비어있는 경우
        return false;

    Node* p = first->link;
    do {
        if (p->data.eno == eno)
            return true;
        p = p->link;
    } while (p != first);

    return false; // eno를 가진 사원이 없음
}

CircularList CircularList::operator+(const CircularList& lb) const {
    CircularList lc;
    ListIterator Aiter(*this);
    ListIterator Biter(lb);
    Employee* p = Aiter.First();
    Employee* q = Biter.First();

    while (p != nullptr && q != nullptr) {
        if (*p < *q) { // A의 eno가 B의 eno보다 작은 경우
            lc.Add(new Employee(*p));
            p = Aiter.Next();
        }
        else { // B의 eno가 A의 eno보다 작거나 같은 경우
            lc.Add(new Employee(*q));
            q = Biter.Next();
        }
    }

    // 남아있는 노드를 lc에 추가
    while (p != nullptr) {
        lc.Add(new Employee(*p));
        p = Aiter.Next();
    }

    while (q != nullptr) {
        lc.Add(new Employee(*q));
        q = Biter.Next();
    }

    return lc; // 새로운 리스트 반환
}

ostream& operator<<(ostream& os, const CircularList& l) {
    ListIterator li(l);
    if (!li.NotNull()) {
        os << "리스트가 비어 있습니다." << endl;
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

// ------------- ListIterator 메서드 구현 -------------
ListIterator::ListIterator(const CircularList& lst) : list(lst), current(lst.first->link) {
    if (current == lst.first) // 리스트가 비어있는 경우
        current = nullptr;
    cout << "List Iterator is constructed" << endl;
}

ListIterator::~ListIterator() {
    // 특별한 메모리 관리 필요 없음
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
    if (current == list.first) { // 다시 처음 노드에 도달했을 때
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

ListIterator& ListIterator::operator++() { // 전위 증감 연산자
    if (current != nullptr)
        current = current->link;
    if (current == list.first) // 다시 처음 노드에 도달했을 때
        current = nullptr;
    return *this;
}

ListIterator ListIterator::operator++(int) { // 후위 증감 연산자
    ListIterator old = *this;
    if (current != nullptr)
        current = current->link;
    if (current == list.first) // 다시 처음 노드에 도달했을 때
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

// ------------- sum, avg, min, max 함수 구현 -------------
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
        return 0; // 리스트가 비어있을 경우
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
        return 0; // 리스트가 비어있을 경우
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

// ------------- main 함수 구현 -------------
enum Enum {
    Add0, Add1, DeleteOp, ShowOp, SearchOp, MergeOp, SUM, AVG, MIN, MAX, ExitOp
};

int main() {
    Enum menu; // 메뉴
    int selectMenu;
    string eno, ename;
    int pay;
    Employee* data;
    bool result = false;
    CircularList la, lb, lc;
    do {
        cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6.sum, 7.avg, 8.min, 9.max, 10.exit 선택::";
        cin >> selectMenu;
        switch (static_cast<Enum>(selectMenu)) {
        case Add0:
            cout << "사원번호 입력:: ";
            cin >> eno;
            cout << "사원 이름 입력:: ";
            cin >> ename;
            cout << "사원 급여:: ";
            cin >> pay;
            data = new Employee(eno, ename, pay);
            la.Add(data);
            break;
        case Add1:
            cout << "사원번호 입력:: ";
            cin >> eno;
            cout << "사원 이름 입력:: ";
            cin >> ename;
            cout << "사원 급여:: ";
            cin >> pay;
            data = new Employee(eno, ename, pay);
            lb.Add(data);
            break;
        case DeleteOp:
            cout << "사원번호 입력:: ";
            cin >> eno;
            result = la.Delete(eno);
            if (result)
                cout << "삭제 완료" << endl;
            else
                cout << "삭제 실패: 해당 사원번호가 없습니다." << endl;
            break;
        case ShowOp:
            cout << "리스트 la = ";
            la.Show();
            cout << "리스트 lb = ";
            lb.Show();
            break;
        case SearchOp:
            cout << "사원번호 입력:: ";
            cin >> eno;
            result = la.Search(eno);
            if (!result)
                cout << "검색 값 = " << eno << " 데이터가 없습니다." << endl;
            else
                cout << "검색 값 = " << eno << " 데이터가 존재합니다." << endl;
            break;
        case MergeOp:
            lc = la + lb;
            cout << "리스트 lc = ";
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
            cout << "프로그램을 종료합니다." << endl;
            break;
        default:
            cout << "잘못된 선택입니다. 다시 시도해주세요." << endl;
            break;
        }
    } while (selectMenu != ExitOp);
    return 0;
}
