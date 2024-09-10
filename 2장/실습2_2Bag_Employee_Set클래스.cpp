//�ҽ� �ڵ�2.1: Bag Ŭ���� - Employee ���� �����ϱ� 
//Bag - Set Ŭ���� ��� ���� ����
#include <iostream>
#include <memory>
using namespace std;
#define MaxSize 100

template <class T>
class Bag {
public:
	Bag(int bagCapacity = 10);
	~Bag();
	bool IsFull();
	int Size() const; //HowMany( )�� �ش��
	bool IsEmpty() const;
	virtual T& Pop();
	virtual void Push(const T&);
	friend ostream& operator <<<T>(ostream&, Bag<T>&);
private:
	T* array;
	int capacity;
	int top;
};
template <class T>
class Set :public Bag{
public:
	Set(int setCapacity = 10);
	~Set();
	bool IsFull();
	int Size() const; //HowMany( )�� �ش��
	bool IsEmpty() const;
	virtual T Pop();
	virtual void Push(const T&);//�����ϱ� ���� �ߺ� üũ�ؾ� �ȴ�
	friend ostream& operator <<<T>(ostream&, Set<T>&);//template ���� ���� �ʿ� 
	//friend ostream& operator <<(ostream&, Set&);
private:
	T* data;
	int capacity;
	int top;
};


class Employee {
	string eno;
	string ename;
	int age;
public:
	Employee(string eno, string ename, int age) : eno(eno), ename(ename), age(age) {}

	string getEno() const { return eno; }
	string getEname() const { return ename; }
	int getAge() const { return age; }

	
	}
};

int main() {
	Set<Employee> b(4);
	int n;
	Employee emp[5] = { new Employee(),...}
	try {
		b.Push(emp[0]);
		b.Push(emp[0]);
		b.Push(emp[0]);
		b.Push(emp[0]);
		b.Push(emp[0]);
		if (b.IsFull()) {
			cout << "full" << endl;
		}
		else {
			cout << "not full" << endl;
		}
		cout << endl << b << endl;;
		while (!b.IsEmpty()) {
			n = b.Pop();
			cout << "b.Pop() = " << n << endl;
		}
	}
	catch (string s) {
		cout << "���ܹ߻�" << s;
	}
	system("pause");
	return 0;
}