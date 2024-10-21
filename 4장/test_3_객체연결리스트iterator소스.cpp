/*
* 3단계-객체 연결 리스트의 iterator 버젼
* template 버전으로 구현
*/
#include <iostream>
#include <ctime> // <time.h> 대신 <ctime> 사용
using namespace std;

// Employee 클래스 정의
class Employee {
    friend class Node;
    friend class LinkedList;
    friend class ListIterator;
private:
    string eno;     // 사원번호
    string ename;   // 사원이름
    int salary;     // 사원 급여
public:
    Employee() {}
    Employee(string sno, string sname, int sal) : eno(sno), ename(sname), salary(sal) {}
    
    // operator<< 오버로딩: Employee 객체 출력
    friend ostream& operator<<(ostream& os, Employee& emp);
    
    // operator== 오버로딩: eno 기준 비교
    bool operator==(Employee& emp);
    
    // operator< 오버로딩: eno 기준 오름차순 정렬
    bool operator<(Employee& emp);
    
    // compare 함수: eno 기준 비교 결과 반환 ('<', '>', '=')
    char compare(const Employee*) const;
    
    // 급여 반환 함수
    int getSalary() const {
        return salary;
    }
};

// operator<< 구현
ostream& operator<<(ostream& os, Employee& emp) {
    os << "사원번호: " << emp.eno << ", 이름: " << emp.ename << ", 급여: " << emp.salary;
    return os;
}

// operator== 구현: eno가 동일한지 비교
bool Employee::operator==(Employee& emp) {
    return this->eno == emp.eno;
}

// operator< 구현: eno를 기준으로 오름차순 정렬
bool Employee::operator<(Employee& emp) {
    return this->eno < emp.eno;
}

// compare 함수 구현: eno 기준 비교
char Employee::compare(const Employee* emp) const {
    if (this->eno < emp->eno)
        return '<';
    else if (this->eno > emp->eno)
        return '>';
    else
        return '=';
}

// Node 클래스 정의
class Node {
    friend class ListIterator;
    friend class LinkedList;
    Employee data; // 노드가 저장하는 Employee 객체
    Node* link;    // 다음 노드를 가리키는 포인터
public:
    Node() : data(), link(nullptr) {}
    Node(Employee element) : data(element), link(nullptr) {}
};

// Forward 선언
class ListIterator;

// LinkedList 클래스 정의
class LinkedList {
    friend class ListIterator;
    Node* first; // 리스트의 첫 번째 노드를 가리키는 포인터
public:
    LinkedList() : first(nullptr) {}
    
    // 소멸자: 리스트의 모든 노드를 삭제하여 메모리 누수 방지
    ~LinkedList();
    
    bool Delete(string);           // 특정 eno를 가진 노드를 삭제하는 함수
    void Show();                   // 리스트의 모든 노드를 출력하는 함수
    void Add(Employee);            // eno로 정렬되도록 노드를 추가하는 함수
    bool Search(string);           // 특정 eno를 검색하는 함수
    LinkedList operator+(LinkedList&); // 두 리스트를 병합하는 연산자 오버로딩
};

// 소멸자 구현: 리스트의 모든 노드를 삭제
LinkedList::~LinkedList() {
    Node* current = first;
    while (current != nullptr) {
        Node* temp = current;
        current = current->link;
        delete temp;
    }
}

// Show 함수 구현: 리스트의 모든 노드를 순서대로 출력
void LinkedList::Show() {
    Node* p = first;
    while (p != nullptr) {
        cout << p->data << " -> ";
        p = p->link;
    }
    cout << "nullptr" << endl;
}

// Add 함수 구현: eno 기준 오름차순으로 정렬되도록 노드를 삽입
void LinkedList::Add(Employee element) {
    Node* newNode = new Node(element);
    
    // 리스트가 비어있거나 새로운 노드가 첫 노드보다 작은 경우
    if (first == nullptr || element < first->data) {
        newNode->link = first;
        first = newNode;
    }
    else {
        // 이전 노드와 현재 노드를 추적
        Node* prev = first;
        Node* current = first->link;
        
        // 적절한 위치를 찾기 위해 탐색
        while (current != nullptr && !(element < current->data)) {
            prev = current;
            current = current->link;
        }
        
        // 새로운 노드를 이전 노드 뒤에 삽입
        newNode->link = current;
        prev->link = newNode;
    }
}


// Search 함수 구현: 특정 eno를 가진 노드가 있는지 검색
bool LinkedList::Search(string eno) {
    Node* ptr = first;
    while (ptr != nullptr) {
        if (ptr->data.eno == eno)
            return true;
        ptr = ptr->link;
    }
    return false;
}

// Delete 함수 구현: 특정 eno를 가진 노드 삭제
bool LinkedList::Delete(string eno) {
    if (first == nullptr)
        return false; // 리스트가 비어있으면 삭제할 노드가 없음

    // 첫 노드가 삭제할 eno를 가진 경우
    if (first->data.eno == eno) {
        Node* temp = first;
        first = first->link;
        delete temp;
        return true;
    }

    // 첫 노드가 아닌 노드를 삭제할 경우
    Node* current = first->link; // 두 번째 노드부터 시작
    Node* prev = first;
    while (current != nullptr && current->data.eno != eno) {
        prev = current;
        current = current->link;
    }

    if (current == nullptr)
        return false; // 삭제할 데이터를 가진 노드를 찾지 못함

    prev->link = current->link;
    delete current;
    return true;
}

// operator+ 구현: 두 리스트를 병합하여 새로운 리스트 반환
LinkedList LinkedList::operator+(LinkedList& lb) {
    LinkedList lc;
    ListIterator Aiter(*this);
    ListIterator Biter(lb);
    Employee* p = Aiter.First();
    Employee* q = Biter.First();

    while (p != nullptr && q != nullptr) {
        if (*p < *q) { // a의 eno가 b의 eno보다 작은 경우
            lc.Add(*p);
            p = Aiter.Next();
        }
        else { // b의 eno가 a의 eno보다 작거나 같은 경우
            lc.Add(*q);
            q = Biter.Next();
        }
    }

    // 남아있는 노드를 lc에 추가
    while (p != nullptr) {
        lc.Add(*p);
        p = Aiter.Next();
    }

    while (q != nullptr) {
        lc.Add(*q);
        q = Biter.Next();
    }

    return lc; // 새로운 리스트 반환
}

// ListIterator 클래스 정의
class ListIterator {
public:
    // 생성자: 리스트의 첫 노드를 현재 위치로 설정
    ListIterator(const LinkedList& lst);
    
    // 소멸자
    ~ListIterator();
    
    // 현재 노드가 nullptr이 아닌지 확인
    bool NotNull();
    
    // 다음 노드가 nullptr이 아닌지 확인
    bool NextNotNull();
    
    // 첫 번째 노드의 데이터를 반환
    Employee* First();
    
    // 다음 노드의 데이터를 반환
    Employee* Next();
    
    // 현재 노드의 데이터를 역참조
    Employee& operator*() const;
    
    // 현재 노드의 데이터를 포인터로 반환
    Employee* operator->() const;
    
    // 전위 증감 연산자: 현재 노드를 다음 노드로 이동
    ListIterator& operator++();
    
    // 후위 증감 연산자: 현재 노드를 다음 노드로 이동
    ListIterator operator++(int);
    
    // 두 이터레이터가 다른 노드를 가리키는지 비교
    bool operator!=(const ListIterator right) const;
    
    // 두 이터레이터가 같은 노드를 가리키는지 비교
    bool operator==(const ListIterator right) const;
    
    // 현재 노드의 데이터를 반환
    Employee* GetCurrent();
private:
    Node* current;             // 현재 노드를 가리키는 포인터
    const LinkedList& list;    // 기존 리스트에 대한 참조
};

// ListIterator 생성자 구현
ListIterator::ListIterator(const LinkedList& lst) : list(lst), current(lst.first) {
    cout << "List Iterator is constructed" << endl;
}

// ListIterator 소멸자 구현
ListIterator::~ListIterator() {}

// NotNull 함수 구현
bool ListIterator::NotNull() {
    return current != nullptr;
}

// NextNotNull 함수 구현
bool ListIterator::NextNotNull() {
    if (current != nullptr && current->link != nullptr)
        return true;
    return false;
}

// First 함수 구현
Employee* ListIterator::First() {
    if (list.first != nullptr)
        return &list.first->data;
    return nullptr;
}

// Next 함수 구현
Employee* ListIterator::Next() {
    if (current != nullptr) {
        current = current->link;
        if (current != nullptr) {  
            return &current->data;
        }
    }
    return nullptr;
}


// GetCurrent 함수 구현
Employee* ListIterator::GetCurrent() {
    if (current != nullptr)
        return &current->data;
    return nullptr;
}

// operator* 구현
Employee& ListIterator::operator*() const {
    return current->data;
}

// operator-> 구현
Employee* ListIterator::operator->() const {
    return &current->data;
}

// 전위 증감 연산자 구현
ListIterator& ListIterator::operator++() { // 값을 반환할때는 ListIterator, 기존의 있던 값을 할때는 ListIterator&
    if (current != nullptr)
        current = current->link;
    return *this;
}

// 후위 증감 연산자 구현
ListIterator ListIterator::operator++(int) {
    ListIterator old = *this;
    if (current != nullptr)
        current = current->link;
    return old;
}

// operator!= 구현
bool ListIterator::operator!=(const ListIterator right) const {
    return current != right.current;
}

// operator== 구현
bool ListIterator::operator==(const ListIterator right) const {
    return current == right.current;
}

// sum 함수 구현: 리스트의 모든 사원 급여 합계
int sum(const LinkedList& l) {
    ListIterator li(l);
    int total = 0;
    while (li.NotNull()) {
        total += li.GetCurrent()->getSalary();
        li++;
    }
    return total;
}

// avg 함수 구현: 리스트의 모든 사원 급여 평균
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

// min 함수 구현: 리스트의 모든 사원 급여 중 최소값
int min(const LinkedList& l) {
    ListIterator li(l);
    if (!li.NotNull())
        return 0; // 또는 적절한 에러 처리
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

// max 함수 구현: 리스트의 모든 사원 급여 중 최대값
int max(const LinkedList& l) {
    ListIterator li(l);
    if (!li.NotNull())
        return 0; // 또는 적절한 에러 처리
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

// 열거형 정의: 메뉴 선택을 위한 상수
enum Enum {
    Add0, Add1, Delete, Show, Search, Merge, SUM, AVG, MIN, MAX, Exit
};

// main 함수: 프로그램의 진입점
int main() { // void main()을 int main()으로 변경
    int selectMenu, num;
    string eno, ename;
    int pay;
    bool result = false;
    LinkedList la, lb, lc;
    Employee* data = nullptr;
    
    do {
        // 메뉴 출력
        cout << endl << "0.Add0, 1.Add1, 2.Delete, 3.Show, 4.Search, 5.Merge, 6.Sum, 7.Avg, 8.Min, 9.Max, 10.Exit 선택:: ";
        cin >> selectMenu;
        
        // 입력값 검증
        if (selectMenu < 0 || selectMenu > 10) {
            cout << "잘못된 선택입니다. 다시 시도해주세요." << endl;
            continue; // 루프의 다음 반복으로 이동
        }
        
        // 메뉴 선택에 따른 동작
        switch (static_cast<Enum>(selectMenu)) {
        case Add0:
            cout << "사원번호 입력:: ";
            cin >> eno;
            cout << "사원 이름 입력:: ";
            cin >> ename;
            cout << "사원 급여 입력:: ";
            cin >> pay;
            data = new Employee(eno, ename, pay);
            la.Add(*data);
            delete data; // 메모리 누수 방지를 위해 동적 할당 해제
            cout << "사원이 la 리스트에 추가되었습니다." << endl;
            break;
        case Add1:
            cout << "사원번호 입력:: ";
            cin >> eno;
            cout << "사원 이름 입력:: ";
            cin >> ename;
            cout << "사원 급여 입력:: ";
            cin >> pay;
            data = new Employee(eno, ename, pay);
            lb.Add(*data);
            delete data; // 메모리 누수 방지를 위해 동적 할당 해제
            cout << "사원이 lb 리스트에 추가되었습니다." << endl;
            break;
        case Delete:
            cout << "삭제할 사원번호 입력:: ";
            cin >> eno;
            result = la.Delete(eno);
            if (result)
                cout << "삭제 완료" << endl;
            else
                cout << "삭제할 데이터를 찾을 수 없습니다." << endl;
            break;
        case Show:
            cout << "리스트 la = ";
            la.Show();
            cout << "리스트 lb = ";
            lb.Show();
            cout << "리스트 lc = ";
            lc.Show();
            break;
        case Search: { // 중괄호 추가하여 변수 선언 범위 제한
            cout << "검색할 사원번호 입력:: ";
            cin >> eno;
            result = la.Search(eno);
            if (!result)
                cout << "검색 값 = " << eno << " 데이터가 없습니다." << endl;
            else
                cout << "검색 값 = " << eno << " 데이터가 존재합니다." << endl;
            break;
        }
        case Merge:
            lc = la + lb;
            cout << "리스트 lc = ";
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
            cout << "프로그램을 종료합니다." << endl;
            break;
        default:
            // 이 경우는 이미 입력값 검증을 했으므로 실행되지 않음
            break;
        }
    } while (static_cast<Enum>(selectMenu) != Exit);
    
    return 0; // 프로그램 정상 종료
}
