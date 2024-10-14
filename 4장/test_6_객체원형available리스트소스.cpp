/*
* 6단계- 원형 객체 연결 리스트의 available list, getNode, retNode
* head node를 갖고 있고 삭제된 노드들은 available list에 리턴한다.
* CircularList를 대상으로 한 iterator를 구현한다.
* 기존의 class와 함수들은 최대한 수정하지 않음
*/
#include <iostream>
#include <string>
using namespace std;

// Forward declaration of CircularList
class CircularList;

// Forward declaration of operator<<
ostream& operator<<(ostream& os, CircularList& l);

// Employee 클래스 구현
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

// 출력 연산자 오버로딩
ostream& operator<<(ostream& os, Employee& emp) {
    os << "[ENO: " << emp.eno << ", NAME: " << emp.ename << ", SALARY: " << emp.salary << "]";
    return os;
}

// 비교 연산자 오버로딩 (<)
bool Employee::operator<(Employee& emp) {
    return this->eno < emp.eno;
}

// 비교 연산자 오버로딩 (==)
bool Employee::operator==(Employee& emp) {
    return this->eno == emp.eno;
}

// compare 함수 구현
char Employee::compare(const Employee* emp) const {
    if (this->eno < emp->eno) return '<';
    if (this->eno > emp->eno) return '>';
    return '=';
}

// Node 클래스
class Node {
    friend class ListIterator;
    friend class CircularList;
    friend ostream& operator<<(ostream& os, CircularList& l); // operator<<를 친구로 선언
    Employee data;
    Node* link;
public:
    Node() { }
    Node(Employee element) {
        data = element;
        link = nullptr;
    }
};

// CircularList 클래스
class CircularList {
    friend class ListIterator;
    friend ostream& operator<<(ostream& os, CircularList& l); // operator<<를 친구로 선언
    Node* last; // 마지막 노드를 가리킴
    static Node* av; // available list
public:
    CircularList() {
        last = new Node(); 
        last->link = last; // 헤드 노드는 자기 자신을 가리킴
    }
    
    bool Delete(string);
    void Show();
    void Add(Employee*); // eno로 정렬되도록 구현
    bool Search(string);
    Node* GetNode();
    void RetNode(Node*);
    void Erase();
    CircularList& operator+(CircularList&);
    friend ostream& operator<<(ostream& os, CircularList& l);
};

// available list 초기화
Node* CircularList::av = NULL;

// GetNode 함수: available list에서 노드를 가져오거나 새로 생성
Node* CircularList::GetNode()
{ 
    if (av != NULL) { // available list에 노드가 있는 경우
        Node* temp = av;
        av = av->link;
        return temp;
    }
    else { // available list에 노드가 없는 경우 새로 생성
        return new Node();
    }
}

// RetNode 함수: 삭제된 노드를 available list에 반환
void CircularList::RetNode(Node* x)
{
    x->link = av;
    av = x;
}

// operator<< 오버로딩: 리스트 출력
ostream& operator<<(ostream& os, CircularList& l)
{
    if (l.last->link == l.last) { // 리스트가 비어있는 경우
        os << "Empty List";
        return os;
    }
    Node* p = l.last->link->link; // 첫 데이터 노드
    while (p != l.last->link) {
        os << p->data << " -> ";
        p = p->link;
    }
    os << "(Head)";
    return os;
}

// Show 함수: 리스트 출력
void CircularList::Show() { 
    cout << *this << endl;
}

// Add 함수: eno 기준으로 정렬된 위치에 삽입
void CircularList::Add(Employee* element) 
{
    Node* newNode = GetNode(); 
    newNode->data = *element;
    Node* first = last->link; // 헤드 노드
    Node* p = first->link; // 첫 데이터 노드
    Node* q = first; // 이전 노드
    
    // 삽입 위치를 찾음
    while (p != first && p->data < newNode->data) {
        q = p;
        p = p->link;
    }
    
    // 삽입
    q->link = newNode;
    newNode->link = p;
    
    // 마지막 노드 업데이트
    if (q == last) {
        last = newNode;
    }
}

// Search 함수: eno로 검색
bool CircularList::Search(string eno) { 
    Node* first = last->link; // 헤드 노드
    Node* p = first->link; // 첫 데이터 노드
    
    while (p != first) {
        if (p->data.eno == eno) return true;
        p = p->link;
    }
    return false;
}

// Delete 함수: eno로 삭제
bool CircularList::Delete(string eno) 
{
    Node* first = last->link; // 헤드 노드
    Node* p = first->link; // 첫 데이터 노드
    Node* q = first; // 이전 노드
    
    while (p != first && p->data.eno != eno) {
        q = p;
        p = p->link;
    }
    
    if (p == first) return false; // 찾지 못함
    
    q->link = p->link;
    
    // 마지막 노드가 삭제된 경우 업데이트
    if (p == last) {
        last = q;
    }
    
    RetNode(p);
    return true;
}

// Erase 함수: 리스트 초기화 및 노드 반환
void CircularList::Erase() {
    Node* first = last->link; // 헤드 노드
    Node* p = first->link; // 첫 데이터 노드
    
    while (p != first) {
        Node* temp = p;
        p = p->link;
        RetNode(temp);
    }
    last->link = last; // 헤드 노드만 남김
}

// operator+ 함수: 두 리스트를 병합
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

// ListIterator 클래스
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
    Node* current; // 현재 노드
    const CircularList& list; // 리스트 참조
};

// ListIterator 생성자
ListIterator::ListIterator(const CircularList& lst) : list(lst), current(lst.last->link->link) {
}

// ListIterator 소멸자
ListIterator::~ListIterator() {
}

// NotNull 함수: 현재 노드가 헤드가 아닌지 확인
bool ListIterator::NotNull() {
    return current != list.last->link;
}

// NextNotNull 함수: 다음 노드가 헤드가 아닌지 확인
bool ListIterator::NextNotNull() {
    return current->link != list.last->link;
}

// First 함수: 첫 번째 데이터 노드 반환
Employee* ListIterator::First() {
    current = list.last->link->link;
    if (current == list.last->link) return nullptr;
    return &current->data;
}

// Next 함수: 다음 데이터 노드 반환
Employee* ListIterator::Next() {
    if (current->link == list.last->link) return nullptr;
    current = current->link;
    return &current->data;
}

// GetCurrent 함수: 현재 노드의 데이터 반환
Employee* ListIterator::GetCurrent() {
    return &current->data;
}

// 연산자* 오버로딩
Employee& ListIterator::operator*() const {
    return current->data;
}

// 연산자-> 오버로딩
Employee* ListIterator::operator->() const {
    return &current->data;
}

// 전위 증가 연산자
ListIterator& ListIterator::operator++() { 
    if (current->link != list.last->link)
        current = current->link;
    else
        current = list.last->link; // 순환
    return *this;
}

// 후위 증가 연산자
ListIterator ListIterator::operator++(int) { 
    ListIterator old = *this;
    if (current->link != list.last->link)
        current = current->link;
    else
        current = list.last->link;
    return old;
}

// 연산자!= 오버로딩
bool ListIterator::operator != (const ListIterator right) const {
    return current != right.current;
}

// 연산자== 오버로딩
bool ListIterator::operator == (const ListIterator right) const {
    return current == right.current;
}

// sum 함수: 리스트 내 급여 합계
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

// avg 함수: 리스트 내 급여 평균
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

// min 함수: 리스트 내 최소 급여
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

// max 함수: 리스트 내 최대 급여
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

// Enum 정의 (원래대로 Delete 사용)
enum Enum {
    Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

// main 함수 (void main)
void main() {
    Enum menu; // 메뉴
    int selectMenu, num;
    string eno, ename;
    int pay;
    Employee* data;
    bool result = false;
    CircularList la, lb, lc;
    Employee* s;
    do {
        cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6.sum, 7.avg, 8.min, 9.max, 10.exit 선택:: ";
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
        case Delete:
            cout << "사원번호 입력:: ";
            cin >> eno;
            result = la.Delete(eno);
            if (result)
                cout << "eno = " << eno << " 삭제 완료.";
            else
                cout << "eno = " << eno << " 삭제 실패.";
            break;
        case Show:
            cout << "리스트 la = ";
            la.Show();
            cout << "리스트 lb = ";
            lb.Show();
            break;
        case Search:
            cout << "사원번호 입력:: ";
            cin >> eno;
            result = la.Search(eno);
            if (!result)
                cout << "검색 값 = " << eno << " 데이터가 없습니다.";
            else
                cout << "검색 값 = " << eno << " 데이터가 존재합니다.";
            break;
        case Merge:
            lc = la + lb;
            cout << "리스트 lc = ";
            lc.Show();
            cout << "리스트 la를 삭제" << endl;
            la.Erase();
            cout << "리스트 lb를 삭제" << endl;
            lb.Erase();
            cout << "리스트 la = ";
            la.Show();
            cout << endl << "리스트 lb = ";
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
        case Exit: // 프로그램 종료
            break;
        default:
            cout << "잘못된 선택입니다.";
            break;
        }
    } while (static_cast<Enum>(selectMenu) != Exit);
    
    // 프로그램 종료 전에 입력을 대기 (선택 사항)
    cin >> num;
}
