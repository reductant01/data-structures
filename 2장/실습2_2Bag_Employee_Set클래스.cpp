//소스 코드2.1: Bag 클래스 - Employee 버젼 구현하기 
//Bag - Set 클래스 상속 버젼 구현
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
	int Size() const; //HowMany( )에 해당됨
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
	int Size() const; //HowMany( )에 해당됨
	bool IsEmpty() const;
	virtual T Pop();
	virtual void Push(const T&);//삽입하기 전에 중복 체크해야 된다
	friend ostream& operator <<<T>(ostream&, Set<T>&);//template 사용시 주의 필요 
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
		cout << "예외발생" << s;
	}
	system("pause");
	return 0;
}