//�ҽ� �ڵ�2.1: Bag Ŭ���� - Employee ���� �����ϱ� 
/*
	template ���� ����
*/
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
	bool IsEmpty() const; //function declaration - function signature
	virtual T& Pop();
	virtual void Push(const T&);
	friend ostream& operator <<<T>(ostream&, Bag<T>&);
private:
	T* array;
	int capacity;
	int top;
};

template <class T>
void ChangeSizeID(T*& a, const int oldSize, const int newSize)
{
	if (newSize < 0) throw "New length must be >= 0";
	T* temp = new T[newSize];
	int number = oldSize;
	if (oldSize > newSize) number = newSize;
	//copy(a, a + number, temp);
	memcpy(temp, a, sizeof(T) * number);
	delete[] a;
	a = temp;

}

template <class T>
void Bag<T>::Push(const T& x)
{
	if (top == capacity - 1)
		// ���� ������ ordering ���¿��� push�Ѵ�. non-ordering�ǰ� push�� �����ϰ� ����

}

template <class T>
T& Bag<T>::Pop()
{
	T retValue;
	if (IsEmpty()) throw "Bag is empty, cannot delete";
	int deletePos = top / 2;
	retValue = array[deletePos];
	// �ǽ� ����: no ordering���·� pop�ǰ� ����
	//copy(array + deletePos + 1, array + top + 1, array + deletePos);
	memcpy(array + deletePos, array + deletePos + 1, sizeof(int) * (top - deletePos));
	top--;
	return retValue;
}

class Employee {
	string eno;
	string ename;
	int age;
public:
	Employee(string eno, string ename, int age) : eno(eno), ename(ename), age(age) {}

	string getEno() const { return eno; }
	string getEname() const { return ename; }
	int getAge() const { return age; }

	
};

int main() {
	Bag<Employee> b(4);
	int n;
	Employee emp[5] = { new Employee(),... }
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