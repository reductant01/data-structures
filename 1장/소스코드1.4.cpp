//�ҽ� �ڵ�1.4: ��ü���� �迭�� �Ϲ� �Լ� ���� - step2
#include <iostream>
using namespace std;
#define N 10
//��ü���� �迭�� main()���� �����Ѵ�.
class Employee {
	int eno;
	string ename;
	float salary;
	string dept;
	static int count;//��ü�� ������ ������ count++
public:
	Employee();
	Employee(int);
	Employee(const Employee&);
	~Employee();
	Employee& operator=(const Employee&);
	int operator++();//salary�� 10% ����
	static int Show();//count ���� �ʱ�ȭ
	friend ostream& operator << (ostream& stream, Employee&);
};

Employee::Employee() {  }
Employee::Employee(int n) { }
Employee::Employee(const Employee& e){}
void initializeEmployee(Employee* emp[], int);
void maxEmployee(Employee* emp[], int);//operator<<()�� ����Ͽ� ����
void minEmployee(Employee* emp[], int);
void sortEmployee(Employee* emp[], int);
void ShowEmployee(Employee* emp[], int);
void main() {
	int num = N;
	Employee* emp[N];//��ü���� �迭
	initializeEmployee(emp, num);
	Employee::Show();
	ShowEmployee(emp, num);
	maxEmployee(emp, num);
	minEmployee(emp, num);
	sortEmployee(emp, num);
	//min, max, sort()�� �Ϲ� �Լ��� ���� �ǽ�
	system("pause");
}

void initializeEmployee(Employee* emp[N], int n)
{
	int num;
	for (int i = 0; i < n; i++)
	{
		cin >> num;
			emp[i] = new Employee(num);
		    emp[i]++;
	}
}