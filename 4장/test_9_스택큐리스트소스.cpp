/*
* 9단계: Linked List를 사용한 스택과 큐의 구현
* template 버전으로 구현 
*/

//Stack node & Queue Node
#include <stdio.h>
#include <iostream>
using namespace std;
class Employee {
	friend class Node;
	friend class LinkedList;
	string eno;
	string ename;
public:
	Employee() {}
	Employee(string sno, string sname) :eno(sno), ename(sname) {}
	friend ostream& operator<<(ostream& os, Employee&);
	bool operator<(Employee&);
	bool operator==(Employee&);
};
ostream& operator<<(ostream& os, Employee& emp) {

}
bool Employee::operator==(Employee& emp) {

}
bool Employee::operator<(Employee& emp) {

}
template <class T> class Stack; //forward declaration
template <class T> class Queue;
template <class T>
class StackNode {
	friend class Stack<T>;
private:
	T* data;
	StackNode<T>* link;
public:
	StackNode<T>(T* d = 0) : data(d) { link = 0; }//constructor
};

template <class T>
class QueueNode {
	friend class Queue<T>;
private:
	T* data;
	QueueNode<T>* link;
public:
	QueueNode<T>(T* d = 0) : data(d) { link = 0; }//constructor
};

template <class T>
class Stack {
public:
	Stack<T>() { top = 0; }//constructor
	void Add(T*);
	T* Delete();
	void Show();
private:
	StackNode<T>* top;
	void StackEmpty();

};

template <class T>
class Queue {
public:
	Queue<T>() { front = rear = 0; }//constructor
	void Add(T*);
	T* Delete();
	void ShowQueue();
private:
	QueueNode<T>* front;
	QueueNode<T>* rear;
	void QueueEmpty();

};

template <class T>
void Stack<T>::Add(T* y) {

}

template <class T>
void Stack<T>::StackEmpty() {

}
template <class T>
void Stack<T>::Show() {

}
template <class T>
T* Stack<T>::Delete()
//delete the top node from stack and return a pointer to its data
{

}

template <class T>
void Queue<T>::Add(T* y) {

}

template <class T>
T* Queue<T>::Delete()
//delete the first node in queue and return a pointer to its data
{

}

template <class T>
void Queue<T>::QueueEmpty() {
	if (front == 0)
		cout << "Queue is empty" << endl;
	else
		cout << "Queue is non empty" << endl;
}
template <class T>
void Queue<T>::ShowQueue() {

}
enum Enum {
	PushStack, PopStack, ShowStack, AddQueue, DeleteQueue, ShowQueue, Exit
};

void main() {
	Enum menu; // 메뉴
	int selectMenu, num;
	string eno, ename;
	bool result = false;
	Stack<Employee> st;
	Queue<Employee> qu;
	Employee* data;
	do {
		cout << "0.PushSTack, 1.PopStack, 2.ShowStack, 3.AddQueue, 4.DeleteQueue, 5.ShowQueue, 6.Exit:: ";
		cin >> selectMenu;
		switch (static_cast<Enum>(selectMenu)) {
		case PushStack:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			st.Add(data);
			break;
		case PopStack:
			data = st.Delete();
			cout << *data;
			break;
		case ShowStack:
			st.Show();
			break;
		case AddQueue:
			cout << "사원번호 입력:: ";
			cin >> eno;
			cout << "사원 이름 입력:: ";
			cin >> ename;
			data = new Employee(eno, ename);
			qu.Add(data);
			break;
		case DeleteQueue:
			data = qu.Delete();
			cout << *data;
			break;
		case ShowQueue:
			qu.ShowQueue();
			break;

		case Exit: // 꼬리 노드 삭제
			break;
		}
	} while (static_cast<Enum>(selectMenu) != Exit);
	cin >> num;
}

