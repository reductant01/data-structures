#include <iostream>
#include <memory>
#include <exception>  // ���� ó���� ���� ���
#include <string>     // string ����� ���� �߰�

using namespace std;

//--- ����� ����: ������ ��� ���� ---//
class EmptyStackException : public std::exception {
public:
    EmptyStackException() {}
    const char* what() const noexcept override {
        return "�� Stack�Դϴ�.";
    }
};

//--- ����� ����: ������ ���� �� ---//
class OverflowStackException : public std::exception {
public:
    OverflowStackException() {}
    const char* what() const noexcept override {
        return "Stack�� ���� á���ϴ�.";
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

//--- Stack ���ø� Ŭ���� ---//
template <class T>
class Stack {
public:
    Stack(int stackCapacity = 4);
    ~Stack() { delete[] stack; }
    bool IsFull() const;
    bool IsEmpty() const;
    T& Peek() const; // ���� - �� ����
    void Push(const T& item); // ���� - full ����
    T Pop(); // ���� - �� ����
    void Dump() const; // ���� - �� ����
private:
    T* stack;
    int top;
    int capacity;
};

// Stack Ŭ������ ������ ����
template <class T>
Stack<T>::Stack(int stackCapacity) {
    if (stackCapacity <= 0)
        throw OverflowStackException(); // �뷮�� 0 �����̸� ����
    capacity = stackCapacity;
    stack = new T[capacity];
    top = -1; // �� ������ ��Ÿ���� ���� -1�� �ʱ�ȭ
}

// IsFull() �޼���: ������ ���� á���� Ȯ��
template <class T>
bool Stack<T>::IsFull() const {
    return top >= capacity - 1;
}

// IsEmpty() �޼���: ������ ����ִ��� Ȯ��
template <class T>
bool Stack<T>::IsEmpty() const {
    return top == -1;
}

// Peek() �޼���: ������ �� �� ��Ҹ� ��ȯ
template <class T>
T& Stack<T>::Peek() const {
    if (IsEmpty())
        throw EmptyStackException();
    return const_cast<T&>(stack[top]); // const �޼��忡�� ���� ��ȯ�� ���� const_cast ���
}

// Push() �޼���: ���ÿ� ��� �߰�
template <class T>
void Stack<T>::Push(const T& item) {
    if (IsFull())
        throw OverflowStackException();
    stack[++top] = item;
}

// Pop() �޼���: ���ÿ��� ��� ���� �� ��ȯ
template <class T>
T Stack<T>::Pop() {
    if (IsEmpty())
        throw EmptyStackException();
    return stack[top--];
}

// Dump() �޼���: ������ ��� ��Ҹ� ���
template <class T>
void Stack<T>::Dump() const {
    if (IsEmpty())
        throw EmptyStackException();
    cout << "Stack elements: ";
    for(int i = top; i >= 0; --i)
        cout << stack[i] << " ";
    cout << endl;
}

// Menu ������ ����
enum Menu { push, pop, peek, dump, Exit };

// �޴��� �����ϴ� �Լ�
Menu SelectMenu() {
    int choice;
    cout << "0: Push, 1: Pop, 2: Peek, 3: Dump, 4: Exit\n";
    cout << "���ù�ȣ: ";
    cin >> choice;
    return static_cast<Menu>(choice);
}

int main() {
    Stack<int> stack(4);  // �뷮�� 4�� ���� ���� ����
    Menu menu;

    while (true) {
        try {
            menu = SelectMenu();
            switch (menu) {
                case push: {
                    int value;
                    cout << "Push�� ��: ";
                    cin >> value;
                    stack.Push(value);
                    cout << value << "��(��) ���ÿ� �߰��߽��ϴ�.\n";
                    break;
                }
                case pop: {
                    int popped = stack.Pop();
                    cout << "Pop�� �� = " << popped << endl;
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
                    cout << "���α׷��� �����մϴ�.\n";
                    return 0;
                }
                default: {
                    cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n";
                    break;
                }
            }
        }
        catch (const EmptyStackException& e) {
            cout << "���� empty ����: " << e.what() << endl;
        }
        catch (const OverflowStackException& e) {
            cout << "���� overflow ����: " << e.what() << endl;
        }
        catch (const exception& e) { // ��Ÿ ���� ó��
            cout << "���� �߻�: " << e.what() << endl;
        }
    }

    return 0;
}
