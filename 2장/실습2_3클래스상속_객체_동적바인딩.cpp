#include <iostream>
#include <string>
using namespace std;

template <class E>
class Collection {
public:
    Collection(int capacity) {

    }
    virtual bool Add(E& e) {

    }
    virtual E& Search(string str) {
        
    }
    E& Delete(int index) {
        
    }
protected:
    E* data;
    int top;
};

template <class E>
class OrderedCollection : public Collection<E> {
public:
    OrderedCollection(int capacity) : Collection<E>(capacity) {}

    bool Add(E& e) override {
       
    }

    E& Search(string str) override {
       
    }
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
    // Employee 객체를 담는 Collection 초기화
    Collection<Employee>* collectSet = new Collection<Employee>(5);
    Employee e1("E001", "John", 30);
    Employee e2("E002", "Jane", 25);
    Employee e3("E003", "Mike", 28);
    Employee e4("E004", "Anna", 35);
    Employee e5("E005", "Tom", 40);

    collectSet->Add(e1);
    collectSet->Add(e2);
    collectSet->Add(e3);
    collectSet->Add(e4);
    collectSet->Add(e5);

    // OrderedCollection 객체 초기화
    OrderedCollection<Employee>* listSet = new OrderedCollection<Employee>(5);
    listSet->Add(e1);
    listSet->Add(e2);
    listSet->Add(e3);
    listSet->Add(e4);
    listSet->Add(e5);

    // Search 예시
    Employee& foundEmployee = collectSet->Search("John");
    cout << "Collection에서 찾은 직원: " << foundEmployee.getEname() << ", 나이: " << foundEmployee.getAge() << endl;

    Employee& foundOrderedEmployee = listSet->Search("Jane");
    cout << "OrderedCollection에서 찾은 직원: " << foundOrderedEmployee.getEname() << ", 나이: " << foundOrderedEmployee.getAge() << endl;

    return 0;
}