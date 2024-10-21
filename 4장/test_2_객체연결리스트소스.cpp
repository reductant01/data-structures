/*
* 2단계- 객체 연결 리스트: 단순한 linked list에서 insert는 올림차순으로 정렬되도록 처리, delete하는 알고리즘을 코딩
* template version으로 구현
*/
#include <iostream>
#include <ctime> // <time.h> 대신 <ctime> 사용
using namespace std;

// Employee 클래스 정의
class Employee {
    friend class Node;
    friend class LinkedList;
    string eno;    // 사원번호
    string ename;  // 사원이름
public:
    Employee() {}
    Employee(string sno, string sname) :eno(sno), ename(sname) {}
    
    // operator<< 오버로딩: Employee 객체 출력
    friend ostream& operator<<(ostream& os, Employee& emp);
    
    // operator== 오버로딩: eno 기준 비교
    bool operator==(Employee& emp);
    
    // operator< 오버로딩: eno 기준 오름차순 정렬
    bool operator<(Employee& emp);
};

// operator<< 구현
ostream& operator<<(ostream& os, Employee& emp) {
    os << "사원번호: " << emp.eno << ", 이름: " << emp.ename;
    return os;
}

// operator== 구현
bool Employee::operator==(Employee& emp) {
    return this->eno == emp.eno;
}

// operator< 구현
bool Employee::operator<(Employee& emp) {
    return this->eno < emp.eno;
}

// Node 클래스 정의
class Node {
    friend class LinkedList;
    Employee data;
    Node* link;
public:
    Node(Employee element) : data(element), link(nullptr) {}
};

// LinkedList 클래스 정의
class LinkedList {
    Node* first;
public:
    LinkedList() : first(nullptr) {}
    ~LinkedList();
    
    bool Delete(string);           // 특정 데이터를 가진 노드를 삭제하는 함수
    void Show();                   // 리스트의 모든 노드를 출력하는 함수
    void Add(Employee);            // 오름차순으로 노드를 추가하는 함수
    bool Search(string);           // 특정 데이터를 검색하는 함수
    LinkedList operator+(LinkedList&); // 두 리스트를 병합하는 연산자 오버로딩
};

// 소멸자 구현: 리스트의 모든 노드를 삭제하여 메모리 누수 방지
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

// Add 함수 구현: 오름차순으로 정렬되도록 노드 삽입
void LinkedList::Add(Employee element) // eno로 정렬되도록 구현
{
    Node* newNode = new Node(element);
    
    // 리스트가 비어있거나 첫 노드의 eno가 삽입할 eno보다 큰 경우
    if (first == nullptr || first->data < element) {
        newNode->link = first;
        first = newNode;
    }
    else {
        // 적절한 위치를 찾아 삽입
        Node* current = first;
        while (current->link != nullptr && !(current->link->data < element)) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}

// Search 함수 구현: 특정 eno를 가진 노드가 있는지 검색
bool LinkedList::Search(string eno) { // eno를 갖는 레코드를 찾기
    Node* ptr = first;
    while (ptr != nullptr) {
        if (ptr->data.eno == eno)
            return true;
        ptr = ptr->link;
    }
    return false;
}

// Delete 함수 구현: 특정 eno를 가진 노드 삭제
bool LinkedList::Delete(string eno) // delete the element
{
    if (first == nullptr)
        return false; // 리스트가 비어있으면 삭제할 노드가 없음

    // 첫 노드가 삭제할 데이터를 가진 경우
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
    Node* a = this->first;
    Node* b = lb.first;
    
    // 두 리스트를 순회하며 작은 eno를 가진 데이터를 lc에 추가
    while (a != nullptr && b != nullptr) {
        if (a->data < b->data) { // a의 eno가 b의 eno보다 작은 경우
            lc.Add(a->data);
            a = a->link;
        }
        else {
            lc.Add(b->data);
            b = b->link;
        }
    }
    
    // 남아있는 노드를 lc에 추가
    while (a != nullptr) {
        lc.Add(a->data);
        a = a->link;
    }
    
    while (b != nullptr) {
        lc.Add(b->data);
        b = b->link;
    }
    
    return lc; // 새로운 리스트 반환
}

// 열거형 정의: 메뉴 선택을 위한 상수
enum Enum {
    Add1, Add2, Delete, Show, Search, Merge, Exit
};

// main 함수: 프로그램의 진입점
int main() { // void main()을 int main()으로 변경
    int selectMenu, num;
    string eno, ename;
    bool result = false;
    LinkedList la, lb, lc; // 세 개의 연결 리스트 생성
    Employee* data = nullptr;
    
    do {
        // 메뉴 출력
        cout << "0.Add1, 1.Add2, 2.Delete, 3.Show, 4.Search, 5.Merge, 6.Exit 선택:: ";
        cin >> selectMenu;
        
        // 입력값 검증
        if (selectMenu < 0 || selectMenu > 6) {
            cout << "잘못된 선택입니다. 다시 시도해주세요." << endl;
            continue; // 루프의 다음 반복으로 이동
        }
        
        // 메뉴 선택에 따른 동작
        switch (static_cast<Enum>(selectMenu)) {
        case Add1:
            cout << "사원번호 입력:: ";
            cin >> eno;
            cout << "사원 이름 입력:: ";
            cin >> ename;
            data = new Employee(eno, ename);
            la.Add(*data);
            delete data; // 동적 할당 해제
            break;
        case Add2:
            cout << "사원번호 입력:: ";
            cin >> eno;
            cout << "사원 이름 입력:: ";
            cin >> ename;
            data = new Employee(eno, ename);
            lb.Add(*data);
            delete data; // 동적 할당 해제
            break;
        case Delete:
            cout << "사원번호 입력:: ";
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
        case Exit:
            cout << "프로그램을 종료합니다." << endl;
            break;
        default:
            cout << "잘못된 선택입니다. 다시 시도해주세요." << endl;
            break;
        }
    } while (static_cast<Enum>(selectMenu) != Exit);
    
    return 0; // 프로그램 정상 종료
}
