#include <iostream>
#include <ctime> // <time.h> 대신 <ctime> 사용
using namespace std;

// Node 클래스 정의
class Node {
    friend class LinkedList; // LinkedList 클래스가 Node의 private 멤버에 접근할 수 있도록 허용
    int data;                // 노드가 저장하는 정수 데이터
    Node* link;              // 다음 노드를 가리키는 포인터
public:
    // 생성자: 데이터 초기화 및 링크를 nullptr로 설정
    Node(int element) {
        data = element;
        link = nullptr; // nullptr로 초기화
    }
};

// LinkedList 클래스 정의
class LinkedList {
    Node* first; // 리스트의 첫 번째 노드를 가리키는 포인터
public:
    // 생성자: 첫 번째 노드를 nullptr로 초기화
    LinkedList() {
        first = nullptr; // nullptr로 초기화
    }
    
    // 소멸자: 리스트의 모든 노드를 삭제하여 메모리 누수 방지
    ~LinkedList();
    
    bool Delete(int);           // 특정 데이터를 가진 노드를 삭제하는 함수
    void Show();                // 리스트의 모든 노드를 출력하는 함수
    void Add(int element);      // 오름차순으로 노드를 추가하는 함수
    bool Search(int data);      // 특정 데이터를 검색하는 함수
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
void LinkedList::Add(int element) {
    Node* newNode = new Node(element);
    
    // 리스트가 비어있거나 첫 노드의 데이터가 삽입할 데이터보다 크거나 같을 경우
    if (first == nullptr || first->data >= element) {
        newNode->link = first;
        first = newNode;
    }
    else {
        // 적절한 위치를 찾아 삽입
        Node* current = first;
        while (current->link != nullptr && current->link->data < element) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}

// Search 함수 구현: 특정 데이터를 가진 노드가 있는지 검색
bool LinkedList::Search(int element) {
    Node* current = first;
    while (current != nullptr) {
        if (current->data == element)
            return true;
        current = current->link;
    }
    return false;
}

// Delete 함수 구현: 특정 데이터를 가진 노드 삭제
bool LinkedList::Delete(int element) {
    if (first == nullptr)
        return false; // 리스트가 비어있으면 삭제할 노드가 없음

    // 첫 노드가 삭제할 데이터를 가진 경우
    if (first->data == element) {
        Node* temp = first;
        first = first->link;
        delete temp;
        return true;
    }
    
    // 첫 노드가 아닌 노드를 삭제할 경우
    Node* current = first;
    Node* prev = nullptr;
    while (current != nullptr && current->data != element) {
        prev = current;
        current = current->link;
    }
    
    if (current == nullptr)
        return false; // 삭제할 데이터를 가진 노드를 찾지 못함
    
    prev->link = current->link;
    delete current;
    return true;

    // Node* current = first;
    // Node* prev = nullptr;
    
    // while (current != nullptr) {
    //     if (current->data == element) {
    //         if (prev == nullptr) {
    //             // 첫 번째 노드를 삭제하는 경우
    //             first = current->link; // 'first' 포인터를 업데이트
    //         } 
    //         else {
    //             // 첫 번째 노드가 아닌 경우
    //             prev->link = current->link;
    //         }
    //         delete current; // 노드 삭제
    //         return true;    // 삭제 성공
    //     }
    //     prev = current;
    //     current = current->link;
    // }
    // return false; // 삭제할 노드를 찾지 못함
}

// 반환 타입을 상황에 맞게 선택: 새로운 객체를 생성하여 반환하는 경우 값 반환을, 기존 객체를 수정하고 반환하는 경우 참조 반환을 사용합니다.
// operator+ 구현: 두 리스트를 병합하여 새로운 리스트 반환 (새로운 리스트를 반환해야함으로 값 반환)
LinkedList LinkedList::operator+(LinkedList& lb) {
    LinkedList lc;
    Node* a = this->first;
    Node* b = lb.first;
    
    // 두 리스트를 순회하며 작은 값을 lc에 추가
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
    Enum menu;             // 메뉴 변수
    int selectMenu;        // 사용자 선택 메뉴 번호
    bool result = false;   // 함수 결과 저장 변수
    srand(static_cast<unsigned int>(time(nullptr))); // 랜덤 시드 초기화
    LinkedList la, lb, lc; // 세 개의 연결 리스트 생성
    int data = 0;          // 데이터 입력 변수
    
    do {
        // 메뉴 출력
        cout << "0.Add1, 1. Add2, 2.Delete, 3.Show, 4.Search, 5. Merge, 6. Exit 선택:: ";
        cin >> selectMenu;
        
        // 메뉴 선택에 따른 동작
        switch (static_cast<Enum>(selectMenu)) {
        case Add1:
            data = rand() % 49;
            cout << "la에 추가된 데이터: " << data << endl;
            la.Add(data);
            break;
        case Add2:
            data = rand() % 49;
            cout << "lb에 추가된 데이터: " << data << endl;
            lb.Add(data);
            break;
        case Delete:
            cout << "삭제할 데이터 입력: ";
            cin >> data;
            result = la.Delete(data);
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
            int n;
            cout << "검색할 데이터 입력: ";
            cin >> n;
            result = la.Search(n);
            if (!result)
                cout << "검색 값 = " << n << " 데이터가 없습니다." << endl;
            else
                cout << "검색 값 = " << n << " 데이터가 존재합니다." << endl;
            break;
        }
        case Merge:
            lc = la + lb;
            cout << "리스트 lc = ";
            lc.Show();
            break;
        case Exit:
            break;
        default:
            cout << "잘못된 선택입니다. 다시 시도해주세요." << endl;
            break;
        }
    } while (static_cast<Enum>(selectMenu) != Exit);
    
    return 0; // 프로그램 정상 종료
}
