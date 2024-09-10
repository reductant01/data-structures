//소스 코드1.4: 객체들의 배열과 일반 함수 구현 - step2
#include <iostream>
using namespace std;
#define N 10
//객체들의 배열을 main()에서 생성한다.
class Employee {
	int eno;
	string ename;
	float salary;
	string dept;
	static int count;//객체가 생성될 때마다 count++
public:
	Employee();
	Employee(int);
	Employee(const Employee&);
	~Employee();
	Employee& operator=(const Employee&);
	int operator++();//salary를 10% 증가
	static int Show();//count 값을 초기화
	friend ostream& operator << (ostream& stream, Employee&);
};

Employee::Employee() {  }
Employee::Employee(int n) { }
Employee::Employee(const Employee& e){}
void initializeEmployee(Employee* emp[], int);
void maxEmployee(Employee* emp[], int);//operator<<()을 사용하여 구현
void minEmployee(Employee* emp[], int);
void sortEmployee(Employee* emp[], int);
void ShowEmployee(Employee* emp[], int);
void main() {
	int num = N;
	Employee* emp[N];//객체들의 배열
	initializeEmployee(emp, num);
	Employee::Show();
	ShowEmployee(emp, num);
	maxEmployee(emp, num);
	minEmployee(emp, num);
	sortEmployee(emp, num);
	//min, max, sort()을 일반 함수로 구현 실습
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