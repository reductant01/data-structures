#include <iostream>
#include <memory>
#include <exception>  // 예외 처리를 위한 헤더
#include <string>

using namespace std;

//--- 실행시 예외: 큐가 비어 있음 ---//
class EmptyQueueException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Queue is empty.";
    }
};

//--- 실행시 예외: 큐가 가득 참 ---//
class OverflowQueueException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Queue is full.";
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

//--- Queue 템플릿 클래스 ---//
template <class T>
class Queue
{
public:
    Queue(int queueCapacity = 10);
    ~Queue() { delete[] queue; }
    T& Front();
    T& Rear();
    void Push(T const& x);
    void Pop();
    bool IsFull() const;
    bool IsEmpty() const;
    void Dump() const;
private:
    T* queue;
    int front;
    int rear;
    int capacity;
};

// Queue 클래스의 생성자 구현
template <class T>
Queue<T>::Queue(int queueCapacity)
{
    if (queueCapacity <= 0)
        throw OverflowQueueException();
    capacity = queueCapacity;
    queue = new T[capacity];
    front = rear = 0;
}

// Front() 메서드: 큐의 첫 번째 요소를 반환
template <class T>
T& Queue<T>::Front()
{
    if (IsEmpty())
        throw EmptyQueueException();
    return queue[(front + 1) % capacity];
}

// Rear() 메서드: 큐의 마지막 요소를 반환
template <class T>
T& Queue<T>::Rear()
{
    if (IsEmpty())
        throw EmptyQueueException();
    return queue[rear];
}

// Push() 메서드: 큐에 요소 추가
template <class T>
void Queue<T>::Push(T const& x)
{
    if (IsFull())
        throw OverflowQueueException();
    rear = (rear + 1) % capacity;
    queue[rear] = x;
}

// Pop() 메서드: 큐에서 요소 삭제
template <class T>
void Queue<T>::Pop()
{
    if (IsEmpty())
        throw EmptyQueueException();
    front = (front + 1) % capacity;
}

// IsFull() 메서드: 큐가 가득 찼는지 확인
template <class T>
bool Queue<T>::IsFull() const
{
    return ((rear + 1) % capacity) == front;
}

// IsEmpty() 메서드: 큐가 비어있는지 확인
template <class T>
bool Queue<T>::IsEmpty() const
{
    return front == rear;
}

// Dump() 메서드: 큐의 모든 요소를 출력
template <class T>
void Queue<T>::Dump() const
{
    if (IsEmpty()) {
        cout << "Queue is empty." << endl;
        return;
    }
    int i = (front + 1) % capacity;
    cout << "Queue elements: ";
    while (i != (rear + 1) % capacity) {
        cout << queue[i] << " ";
        i = (i + 1) % capacity;
    }
    cout << endl;
}

// 메뉴 열거형 정의
enum Menu { push, pop, frontQ, peek, dump, Exit };

// 메뉴를 선택하는 함수
Menu SelectMenu() {
    int m;
    cout << "0.Push, 1.Pop, 2.Front, 3.Peek, 4.Dump, 5.Exit 선택: ";
    cin >> m;
    return static_cast<Menu>(m);
}

int main() {
    try {
        Queue<int> queue(5);  // 용량이 5인 정수 Queue 생성
        Menu menu;

        while (true) {
            menu = SelectMenu();
            switch (menu) {
                case push: {
                    int x;
                    cout << "Push할 정수 입력: ";
                    cin >> x;
                    queue.Push(x);
                    cout << x << "을(를) 큐에 추가했습니다." << endl;
                    break;
                }
                case pop: {
                    queue.Pop();
                    cout << "Pop 완료." << endl;
                    break;
                }
                case frontQ: {
                    cout << "Front: " << queue.Front() << endl;
                    break;
                }
                case peek: { // Rear 요소 출력
                    cout << "Rear: " << queue.Rear() << endl;
                    break;
                }
                case dump: {
                    queue.Dump();
                    break;
                }
                case Exit:
                    cout << "프로그램을 종료합니다." << endl;
                    return 0;
                default:
                    cout << "잘못된 선택입니다. 다시 시도해주세요." << endl;
            }
        }
    }
    catch (EmptyQueueException& e) {
        cout << e.what() << endl;
    }
    catch (OverflowQueueException& e) {
        cout << e.what() << endl;
    }
    catch (exception& e) { // 기타 예외 처리
        cout << "예외 발생: " << e.what() << endl;
    }

    return 0;
}
