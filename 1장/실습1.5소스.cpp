#include <iostream>
#include <cstring> // strncpy�� ����ϱ� ���� �߰�
#include <string> // std::string�� ����ϱ� ���� �߰�

using namespace std;

#define N 10

class Employee {
	int eno;
	char ename[10];
	float salary;
	string dept;

public:
	Employee();
	Employee(int eno, const char* pname, float salary, string dept);
	Employee(const Employee& e);
	~Employee();
	Employee& operator=(const Employee& e);
	int operator++();
	friend ostream& operator<<(ostream& stream, Employee& e);
	const char* getName() const { return ename; }
	float getSalary() const { return salary; }
};

Employee::Employee() : eno(0), salary(0.0), dept("") {
	strcpy(ename, "");
}

Employee::Employee(int eno, const char* pname, float salary, string dept)
	: eno(eno), salary(salary), dept(dept) {
	strncpy(ename, pname, sizeof(ename) - 1);
	ename[sizeof(ename) - 1] = '\0'; // ������ �迭�� '\0'�� �ֱ� ���ؼ��̴�
}

Employee::Employee(const Employee& e)
	: eno(e.eno), salary(e.salary), dept(e.dept) {
	strncpy(ename, e.ename, sizeof(ename) - 1);
	ename[sizeof(ename) - 1] = '\0';
}

Employee::~Employee() {
	// Ư���� �� ���� ����
}

Employee& Employee::operator=(const Employee& e) {
	if (this != &e) {
		eno = e.eno;
		salary = e.salary;
		dept = e.dept;
		strncpy(ename, e.ename, sizeof(ename) - 1);
		ename[sizeof(ename) - 1] = '\0';
	}
	return *this;
}

int Employee::operator++() {
	return ++eno;
}

ostream& operator<<(ostream& stream, Employee& e) {
	stream << "Employee No: " << e.eno << ", Name: " << e.ename
		<< ", Salary: " << e.salary << ", Dept: " << e.dept;
	return stream;
}

class EmpTable {
	int top;
	Employee* data[N];
public:
	EmpTable() : top(0) { for (int i = 0; i < N; ++i) data[i] = nullptr; }
	~EmpTable() {
		for (int i = 0; i < N; ++i) delete data[i];
	}
	void initializeEmployee();
	void showEmployee();
	void maxEmployee();
	void minEmployee();
	void sortEmployee();
	void insert(Employee& e);
	bool deleteEmployee(const char* name); // delete�� ������ �Լ��� ����
	Employee* search(const char* name);
};

void EmpTable::initializeEmployee() {
	// ���Ƿ� �� ���� Employee ��ü�� �����Ͽ� �ʱ�ȭ
	insert(*(new Employee(1, "John", 3000.0f, "Sales")));
	insert(*(new Employee(2, "Anna", 4000.0f, "HR")));
	insert(*(new Employee(3, "Mark", 3500.0f, "IT")));
}

void EmpTable::showEmployee() {
	for (int i = 0; i < top; ++i) {
		if (data[i] != nullptr) {
			cout << *(data[i]) << endl;
		}
	}
}

void EmpTable::maxEmployee() {
	Employee* maxEmp = data[0];
	for (int i = 1; i < top; ++i) {
		if (data[i]->getSalary() > maxEmp->getSalary()) {
			maxEmp = data[i];
		}
	}
	cout << "Employee with highest salary: " << *maxEmp << endl;
}

void EmpTable::minEmployee() {
	Employee* minEmp = data[0];
	for (int i = 1; i < top; ++i) {
		if (data[i]->getSalary() < minEmp->getSalary()) {
			minEmp = data[i];
		}
	}
	cout << "Employee with lowest salary: " << *minEmp << endl;
}

void EmpTable::sortEmployee() {
	for (int i = 0; i < top - 1; ++i) {
		for (int j = i + 1; j < top; ++j) {
			if (data[i]->getSalary() > data[j]->getSalary()) {
				swap(data[i], data[j]);
			}
		}
	}
	cout << "Sorted employees by salary:" << endl;
	showEmployee();
}

void EmpTable::insert(Employee& e) {
	if (top < N) {
		data[top] = new Employee(e);
		++top;
	}
	else {
		cout << "Table is full!" << endl;
	}
}

bool EmpTable::deleteEmployee(const char* name) {
	for (int i = 0; i < top; ++i) {
		if (strcmp(data[i]->getName(), name) == 0) {
			delete data[i];
			for (int j = i; j < top - 1; ++j) {
				data[j] = data[j + 1];
			}
			data[--top] = nullptr;
			return true;
		}
	}
	return false;
}

Employee* EmpTable::search(const char* name) {
	for (int i = 0; i < top; ++i) {
		if (strcmp(data[i]->getName(), name) == 0) {
			return data[i];
		}
	}
	return nullptr;
}

int main() {
	EmpTable empt;
	empt.initializeEmployee();
	empt.showEmployee(); // ��ü ���ڵ� ���
	empt.maxEmployee();
	empt.minEmployee();
	empt.sortEmployee();

	const char* searchName = "Anna";
	Employee* emp = empt.search(searchName);
	if (emp) {
		cout << "Found employee: " << *emp << endl;
	}
	else {
		cout << "Employee " << searchName << " not found." << endl;
	}

	empt.deleteEmployee("Mark");
	empt.showEmployee(); // Mark ���� �� ���

	return 0;
}
