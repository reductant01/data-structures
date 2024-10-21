#include <iostream>
#include <memory>
#include <exception>  // 예외 처리를 위한 헤더
#include <string>     // string 사용을 위해 추가

using namespace std;

//--- 실행시 예외: 스택이 비어 있음 ---//
class EmptyStackException : public std::exception {
public:
    EmptyStackException() {}
    const char* what() const noexcept override {
        return "빈 Stack입니다.";
    }
};

//--- 실행시 예외: 스택이 가득 참 ---//
class OverflowStackException : public std::exception {
public:
    OverflowStackException() {}
    const char* what() const noexcept override {
        return "Stack이 가득 찼습니다.";
    }
};

//--- Point 클래스 (현재는 사용되지 않음) ---//
class Point {
private:
    int ix;
    int iy;
public:
    Point() : ix(0), iy(0) {}
    Point(int x, int y) : ix(x), iy(y) {}
    friend ostream& operator<<(ostream& os, const Point& p);
};

// Point 클래스의 operator<< 구현
ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.ix << ", " << p.iy << ")";
    return os;
}

//--- Stack 템플릿 클래스 ---//
template <class T>
class Stack {
public:
    Stack(int stackCapacity = 4);
    ~Stack() { delete[] stack; }
    bool IsFull() const;
    bool IsEmpty() const;
    T& Peek() const; // 예외 - 빈 스택
    void Push(const T& item); // 예외 - full 스택
    T Pop(); // 예외 - 빈 스택
    void Dump() const; // 예외 - 빈 스택
private:
    T* stack;
    int top;
    int capacity;
};

// Stack 클래스의 생성자 구현
template <class T>
Stack<T>::Stack(int stackCapacity) {
    if (stackCapacity <= 0)
        throw OverflowStackException(); // 용량이 0 이하이면 예외
    capacity = stackCapacity;
    stack = new T[capacity];
    top = -1; // 빈 스택을 나타내기 위해 -1로 초기화
}

// IsFull() 메서드: 스택이 가득 찼는지 확인
template <class T>
bool Stack<T>::IsFull() const {
    return top >= capacity - 1;
}

// IsEmpty() 메서드: 스택이 비어있는지 확인
template <class T>
bool Stack<T>::IsEmpty() const {
    return top == -1;
}

// Peek() 메서드: 스택의 맨 위 요소를 반환
template <class T>
T& Stack<T>::Peek() const {
    if (IsEmpty())
        throw EmptyStackException();
    return const_cast<T&>(stack[top]); // const 메서드에서 참조 반환을 위해 const_cast 사용
}

// Push() 메서드: 스택에 요소 추가
template <class T>
void Stack<T>::Push(const T& item) {
    if (IsFull())
        throw OverflowStackException();
    stack[++top] = item;
}

// Pop() 메서드: 스택에서 요소 삭제 및 반환
template <class T>
T Stack<T>::Pop() {
    if (IsEmpty())
        throw EmptyStackException();
    return stack[top--];
}

// Dump() 메서드: 스택의 모든 요소를 출력
template <class T>
void Stack<T>::Dump() const {
    if (IsEmpty())
        throw EmptyStackException();
    cout << "Stack elements: ";
    for(int i = top; i >= 0; --i)
        cout << stack[i] << " ";
    cout << endl;
}

// Menu 열거형 정의
enum Menu { push, pop, peek, dump, Exit };

// 메뉴를 선택하는 함수
Menu SelectMenu() {
    int choice;
    cout << "0: Push, 1: Pop, 2: Peek, 3: Dump, 4: Exit\n";
    cout << "선택번호: ";
    cin >> choice;
    return static_cast<Menu>(choice);
}

int main() {
    Stack<int> stack(4);  // 용량이 4인 정수 스택 생성
    Menu menu;

    while (true) {
        try {
            menu = SelectMenu();
            switch (menu) {
                case push: {
                    int value;
                    cout << "Push할 값: ";
                    cin >> value;
                    stack.Push(value);
                    cout << value << "을(를) 스택에 추가했습니다.\n";
                    break;
                }
                case pop: {
                    int popped = stack.Pop();
                    cout << "Pop한 값 = " << popped << endl;
                    break;
                }
                case peek: {
                    cout << "Peek of stack: " << stack.Peek() << endl;
                    break;
                }
                case dump: {
                    stack.Dump();
                    break;
                }
                case Exit: {
                    cout << "프로그램을 종료합니다.\n";
                    return 0;
                }
                default: {
                    cout << "잘못된 선택입니다. 다시 시도해주세요.\n";
                    break;
                }
            }
        }
        catch (const EmptyStackException& e) {
            cout << "스택 empty 예외: " << e.what() << endl;
        }
        catch (const OverflowStackException& e) {
            cout << "스택 overflow 예외: " << e.what() << endl;
        }
        catch (const exception& e) { // 기타 예외 처리
            cout << "예외 발생: " << e.what() << endl;
        }
    }

    return 0;
}
