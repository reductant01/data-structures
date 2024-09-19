#include <iostream>
#include <memory>
#include <exception>  // ���� ó���� ���� ���

using namespace std;

//--- ����� ����: ������ ��� ���� ---//
class EmptyStackException : public std::exception {
public:
	EmptyStackException() {}
	//*
	const char* what() const noexcept override {
		return " �� Stack.";
	}
	//*/
};

//--- ����� ����: ������ ���� �� ---//
class OverflowStackException : public std::exception {
public:
	OverflowStackException() {}
	//*
	const char* what() const noexcept override {
		return "full Stack.";
	}
	//*/
};

class Point {
private:
	int ix;
	int iy;
public:

};


template <class T>
class Stack {
public:
	Stack(int stackCapacity = 4);
	bool IsFull() const;
	bool IsEmpty() const;
	T& Peek() const;//���� - �� ����
	void Push(const T& item);////���� - full ����
	T& Pop();//���� - �� ����
	void Dump();//���� - �� ����
private:
	T* stack;
	int top;
	int capacity;
};

template <class T>
void Stack::Push(const t& item) {
	if (isFull())
		throw OverflowStackException();
}

template <class T>
void Stack::Pop {
	if (isEmpty())
		throw EmptyStackException();
}

// Menu ������ ����
enum Menu { push, pop, peek, dump, Exit };

// �޴��� �����ϴ� �Լ�
Menu SelectMenu() {
	int choice;
	cout << "0: Push " << "1: Pop, " << "2: Peek, " << "3: Dump, " << "4: Exit\n";
	cout << "���ù�ȣ: ";
	cin >> choice;
	return static_cast<Menu>(choice);
}
int main() {
	Stack<int> stack(4);  // �뷮�� 5�� ���� ���� ����
	Menu menu;

	while (true) {
		try {
			menu = SelectMenu();
			switch (menu) {
			case push: {
				int value;
				cout << "push ��: ";
				cin >> value;
				stack.Push(value);
				break;
			}
			case pop: {
				cout << "pop �� = " << stack.Pop();
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
				cout << "Exiting program.\n";
				return 0;
			}
			default: {
				cout << "Invalid choice. Try again.\n";
				break;
			}
			}
		}
		catch (const EmptyStackException& e) {
			cout << "���� empty ���� : " << e.what() << endl;
		}
		catch (const OverflowStackException& e) {
			cout << "���� overflow ����: " << e.what() << endl;
		}
		catch (...) {
			cout << "An unknown exception occurred." << endl;
		}
	}


	return 0;
}