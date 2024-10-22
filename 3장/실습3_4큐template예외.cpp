#include <iostream>
#include <memory>
#include <exception>  // ���� ó���� ���� ���
#include <string>

using namespace std;

//--- ����� ����: ť�� ��� ���� ---//
class EmptyQueueException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Queue is empty.";
    }
};

//--- ����� ����: ť�� ���� �� ---//
class OverflowQueueException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Queue is full.";
    }
};

//--- Point Ŭ���� (����� ������ ����) ---//
class Point {
private:
    int ix;
    int iy;
public:
    Point() : ix(0), iy(0) {}
    Point(int x, int y) : ix(x), iy(y) {}
    friend ostream& operator<<(ostream& os, const Point& p);
};

// Point Ŭ������ operator<< ����
ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.ix << ", " << p.iy << ")";
    return os;
}

//--- Queue ���ø� Ŭ���� ---//
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

// Queue Ŭ������ ������ ����
template <class T>
Queue<T>::Queue(int queueCapacity)
{
    if (queueCapacity <= 0)
        throw OverflowQueueException();
    capacity = queueCapacity;
    queue = new T[capacity];
    front = rear = 0;
}

// Front() �޼���: ť�� ù ��° ��Ҹ� ��ȯ
template <class T>
T& Queue<T>::Front()
{
    if (IsEmpty())
        throw EmptyQueueException();
    return queue[(front + 1) % capacity];
}

// Rear() �޼���: ť�� ������ ��Ҹ� ��ȯ
template <class T>
T& Queue<T>::Rear()
{
    if (IsEmpty())
        throw EmptyQueueException();
    return queue[rear];
}

// Push() �޼���: ť�� ��� �߰�
template <class T>
void Queue<T>::Push(T const& x)
{
    if (IsFull())
        throw OverflowQueueException();
    rear = (rear + 1) % capacity;
    queue[rear] = x;
}

// Pop() �޼���: ť���� ��� ����
template <class T>
void Queue<T>::Pop()
{
    if (IsEmpty())
        throw EmptyQueueException();
    front = (front + 1) % capacity;
}

// IsFull() �޼���: ť�� ���� á���� Ȯ��
template <class T>
bool Queue<T>::IsFull() const
{
    return ((rear + 1) % capacity) == front;
}

// IsEmpty() �޼���: ť�� ����ִ��� Ȯ��
template <class T>
bool Queue<T>::IsEmpty() const
{
    return front == rear;
}

// Dump() �޼���: ť�� ��� ��Ҹ� ���
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

// �޴� ������ ����
enum Menu { push, pop, frontQ, peek, dump, Exit };

// �޴��� �����ϴ� �Լ�
Menu SelectMenu() {
    int m;
    cout << "0.Push, 1.Pop, 2.Front, 3.Peek, 4.Dump, 5.Exit ����: ";
    cin >> m;
    return static_cast<Menu>(m);
}

int main() {
    try {
        Queue<int> queue(5);  // �뷮�� 5�� ���� Queue ����
        Menu menu;

        while (true) {
            menu = SelectMenu();
            switch (menu) {
                case push: {
                    int x;
                    cout << "Push�� ���� �Է�: ";
                    cin >> x;
                    queue.Push(x);
                    cout << x << "��(��) ť�� �߰��߽��ϴ�." << endl;
                    break;
                }
                case pop: {
                    queue.Pop();
                    cout << "Pop �Ϸ�." << endl;
                    break;
                }
                case frontQ: {
                    cout << "Front: " << queue.Front() << endl;
                    break;
                }
                case peek: { // Rear ��� ���
                    cout << "Rear: " << queue.Rear() << endl;
                    break;
                }
                case dump: {
                    queue.Dump();
                    break;
                }
                case Exit:
                    cout << "���α׷��� �����մϴ�." << endl;
                    return 0;
                default:
                    cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���." << endl;
            }
        }
    }
    catch (EmptyQueueException& e) {
        cout << e.what() << endl;
    }
    catch (OverflowQueueException& e) {
        cout << e.what() << endl;
    }
    catch (exception& e) { // ��Ÿ ���� ó��
        cout << "���� �߻�: " << e.what() << endl;
    }

    return 0;
}
