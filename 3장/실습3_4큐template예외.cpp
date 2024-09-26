#include <iostream>
#include <memory>
#include <exception>  // ���� ó���� ���� ���

using namespace std;

//--- ����� ����: ������ ��� ���� ---//
class EmptyQueueException : public std::exception {

};

//--- ����� ����: ������ ���� �� ---//
class OverflowQueueException : public std::exception {

};

class Point {
private:
	int ix;
	int iy;
public:

};


template <class T>
class Queue
{
public:
	Queue(int queueCapacity = 10);
	T& Front();
	T& Rear();
	void Push(T const& x);
	void Pop();
	bool IsFull() const;
	bool IsEmpty() const;
	T& Peek() const;
	void Dump();
private:
	T* queue;
	int front;
	int rear;
	int capacity;
};


// Menu ������ ����
enum Menu { push, pop, front, peek, dump, Exit };

// �޴��� �����ϴ� �Լ�
Menu SelectMenu() {
	
}
int main() {
	Queue<int> queue(5);  // �뷮�� 5�� ���� Queue ����
	Menu menu;

	while (true) {
		try {
			menu = SelectMenu();
			switch (menu) {
			
		}
		catch () {
			
		}
		catch () {
			
		}
		catch () {
			
		}
	}


	return 0;
}