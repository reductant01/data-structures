/* 다항식 리스트: Polynomial Linked List
// 지수는 정수 0<= 지수 <= 5, 난수로 생성한다
// 계수는 double로 난수 생성한다.  -9.0 < 계수 < 9.0
// 지수 내림 차순으로 정렬한다.
// c = a + b 구현한다.
// singly linked list, circular linked list, circular linked list with head node
*/

#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

// ------------- Term 클래스 -------------
template<class T>
class Term {
public:
    // All members of Term are public by default
    double coef; // coefficient
    int exp; // exponent
    Term() { coef = 0; exp = 0; }
    Term(double c, int e) : coef(c), exp(e) { }
    Term Set(double c, int e) { coef = c; exp = e; return *this; };
};

// operator<< 오버로딩
template <typename valType>
inline ostream& operator<< (ostream& os, const Term<valType>& term) { // 함수 호출 과정을 생략하고 직접 함수의 내용을 사용
    if(term.coef == 0) return os; // 계수가 0이면 출력하지 않음
    if(term.exp == 0){
        os << term.coef;
    }
    else{
        os << term.coef << "x^" << term.exp;
    }
    return os;
}

// ------------- ChainNode 클래스 -------------
template<class T>
class ChainNode {
    friend class Chain<T>;
    friend class ChainIterator<T>;
public:
    ChainNode() {}
    ChainNode(const T&);
private:
    T data;
    ChainNode<T>* link;
};

// ChainNode 생성자 구현
template <class T>
ChainNode<T>::ChainNode(const T& element) : data(element), link(NULL) {}

// ------------- Chain 클래스 -------------
template<class T>
class Chain; // forward declaration

template<class T>
class ChainIterator;

template<class T>
class Chain {
public:
    Chain() {
        first = new ChainNode<T>(Term<T>(0, -1)); // 더미 노드 생성 (exp=-1은 임의의 값)
        first->link = first; // 자기 자신을 가리킴
    };
    ~Chain() {
        // 모든 노드 삭제 (더미 노드도 삭제)
        ChainNode<T>* current = first->link;
        while (current != first) {
            ChainNode<T>* temp = current;
            current = current->link;
            delete temp;
        }
        delete first; // 더미 노드 삭제
    }
    bool Delete(int exp); // delete the node with given exponent
    int Length();
    void Add(const T& element); // add a new node in descending exponent order
    void Invert();
    void Concatenate(Chain<T> b);
    void InsertBack(const T& element);
    void displayAll() const;

    ChainIterator<T> begin() const { return ChainIterator<T>(first->link); }
    ChainIterator<T> end() const { return ChainIterator<T>(first); }
private:
    ChainNode<T>* first; // 더미 노드를 가리키는 포인터
};

// Delete 함수 구현
template <class T>
bool Chain<T>::Delete(int exp) // delete the node with given exponent
{
    if (first->link == first) // 리스트가 비어있는 경우
        return false;

    ChainNode<T>* current = first->link; // 현재 노드
    ChainNode<T>* previous = first;       // 이전 노드

    while (current != first) {
        if (current->data.exp == exp) { // 동일한 지수 발견
            previous->link = current->link;
            delete current;
            return true;
        }
        previous = current;
        current = current->link;
    }

    return false; // eno를 가진 사원이 없음
}

// Length 함수 구현
template <class T>
int Chain<T>::Length() {
    int count = 0;
    ChainNode<T>* p = first->link;
    while (p != first) {
        count++;
        p = p->link;
    }
    return count;
}

// Add 함수 구현
template <class T>
void Chain<T>::Add(const T& element) // add a new node in descending exponent order
{
    ChainNode<T>* newNode = new ChainNode<T>(element);
    ChainNode<T>* current = first->link; // 첫 번째 실제 노드
    ChainNode<T>* previous = first;       // 이전 노드

    // 리스트가 비어있거나, 첫 노드보다 큰 eno를 가진 경우
    if (current == first || element.exp > current->data.exp) {
        newNode->link = current;
        previous->link = newNode;
        return;
    }

    // 적절한 위치를 찾기
    while (current != first && current->data.exp >= element.exp) {
        if (current->data.exp == element.exp) { // 동일한 지수 발견
            current->data.coef += element.coef;
            if (current->data.coef == 0) { // 계수가 0이 되면 삭제
                previous->link = current->link;
                delete current;
            }
            delete newNode; // 삽입할 필요 없음
            return;
        }
        previous = current;
        current = current->link;
    }

    // 새로운 노드를 현재 노드 앞에 삽입
    newNode->link = current;
    previous->link = newNode;
}

// Invert 함수 구현
template <class T>
void Chain<T>::Invert() {
    ChainNode<T>* p = first->link;
    ChainNode<T>* q = first;
    ChainNode<T>* r = nullptr;

    while (p != first) {
        ChainNode<T>* temp = p->link;
        p->link = r;
        r = p;
        p = temp;
    }
    first->link = r;
}

// Concatenate 함수 구현
template <class T>
void Chain<T>::Concatenate(Chain<T> b) {
    if (b.first->link == b.first) // b 리스트가 비어있는 경우
        return;

    ChainNode<T>* p = first;
    while (p->link != first) { // 마지막 노드 찾기
        p = p->link;
    }
    p->link = b.first->link; // b 리스트의 첫 번째 실제 노드와 연결

    // b 리스트의 마지막 노드를 first로 연결하여 원형 유지
    ChainNode<T>* q = b.first->link;
    while (q->link != b.first) {
        q = q->link;
    }
    q->link = first;
}

// InsertBack 함수 구현
template <class T>
void Chain<T>::InsertBack(const T& element) {
    ChainNode<T>* newnode = new ChainNode<T>(element);
    ChainNode<T>* curr = first;
    while (curr->link != first) {
        curr = curr->link;
    }
    curr->link = newnode;
    newnode->link = first;
}

// displayAll 함수 구현
template <class T>
void Chain<T>::displayAll() const {
    if (first->link == first) { // 리스트가 비어있는 경우
        cout << "리스트가 비어 있습니다." << endl;
        return;
    }
    ChainNode<T>* p = first->link;
    while (p != first) {
        cout << p->data << " -> ";
        p = p->link;
    }
    cout << "end" << endl;
}

// ------------- ChainIterator 클래스 -------------
template<class T>
class ChainIterator {
private:
    ChainNode<T>* current; // points to a node in list
public:
    ChainIterator() { current = nullptr; }
    ChainIterator(ChainNode<T>* node) :current(node) { }
    // dereferencing operators
    T& operator *() const { return current->data; }
    T* operator->() const { return &current->data; }
    bool operator&&(ChainIterator<T> iter) const {
        return current != NULL && iter.current != NULL;
    }
    bool isEmpty() const { return current == NULL; }
    // increment
    ChainIterator& operator++(); //preincrement
    ChainIterator<T> operator++(int); //post increment
    bool NotNull() const; //check the current element in list is non-null
    bool NextNotNull() const; //check the next element in list is non-null
    T* Next(); //return a pointer to the next element of list
};

// pre-increment 연산자 구현
template <class T>
ChainIterator<T>& ChainIterator<T>::operator++() //preincrement
{
    if (current && current->link != nullptr)
        current = current->link;
    else
        current = nullptr;
    return *this;
}

// post-increment 연산자 구현
template <class T>
ChainIterator<T> ChainIterator<T>::operator++(int) //post increment
{
    ChainIterator<T> temp = *this;
    if (current && current->link != nullptr)
        current = current->link;
    else
        current = nullptr;
    return temp;
}

// NotNull 함수 구현
template <class T>
bool ChainIterator<T>::NotNull() const { //check the current element in list is non-null
    return current != NULL;
}

// NextNotNull 함수 구현
template <class T>
bool ChainIterator<T>::NextNotNull() const { //check the next element in list is non-null
    if (current && current->link != NULL && current->link != nullptr)
        return true;
    return false;
}

// Next 함수 구현
template <class T>
T* ChainIterator<T>::Next() {//return a pointer to the next element of list
    if (current && current->link != first && current->link != NULL) {
        current = current->link;
        return &(current->data);
    }
    return NULL;
}

// ------------- Polynomial 클래스 -------------
template<class T>
class Polynomial {
public:
    Polynomial() { }
    Polynomial(Chain<Term<T> >* terms) :poly(*terms) { }
    Polynomial<T> operator+(const Polynomial<T>& b) const;
    void add(double coef, int exponent);
    void addAll(Polynomial<T>* poly);
    void display() const;
    /*
    T Evaluate(T&) const;//f(x)에 대하여 x에 대한 값을 구한다
    Polynomial Multiply(Polynomial<T>&); //f(x) * g(x)
    Polynomial(const Polynomial& p); //copy constructor
    friend istream& operator>>(istream&, Polynomial&);//polynomial 입력
    friend ostream& operator<<(ostream&, Polynomial&);//polynomial 출력
    const Polynomial& operator=(const Polynomial&) const;
    ~Polynomial( );
    Polynomial operator-(const Polynomial&)const;
    */
private:
    Chain<Term<T> > poly;
};

// operator+ 구현
template<class T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& b) const {
    Polynomial<T> c;
    ChainIterator<Term<T>> ai = poly.begin();
    ChainIterator<Term<T>> bi = b.poly.begin();

    while (ai.NotNull() && bi.NotNull()) {
        Term<T> ta = *ai;
        Term<T> tb = *bi;
        if (ta.exp > tb.exp) {
            c.add(ta.coef, ta.exp);
            ++ai;
        }
        else if (ta.exp < tb.exp) {
            c.add(tb.coef, tb.exp);
            ++bi;
        }
        else { // 지수가 동일한 경우
            double sumCoef = ta.coef + tb.coef;
            if (sumCoef != 0) {
                c.add(sumCoef, ta.exp);
            }
            ++ai;
            ++bi;
        }
    }

    // 남아있는 항들 추가
    while (ai.NotNull()) {
        Term<T> ta = *ai;
        c.add(ta.coef, ta.exp);
        ++ai;
    }

    while (bi.NotNull()) {
        Term<T> tb = *bi;
        c.add(tb.coef, tb.exp);
        ++bi;
    }

    return c;
}

// add 함수 구현
template<class T>
void Polynomial<T>::add(double coef, int exponent) {
    Term<T> newTerm;
    newTerm.coef = coef;
    newTerm.exp = exponent;
    this->poly.Add(newTerm);
}

// addAll 함수 구현
template<class T>
void Polynomial<T>::addAll(Polynomial<T>* b) {
    ChainIterator<Term<T>> iterB = b->poly.begin();
    while (iterB.NotNull()) {
        Term<T> dataB = *iterB;
        add(dataB.coef, dataB.exp);
        iterB.Next();
    }
}

// display 함수 구현
template<class T>
void Polynomial<T>::display() const {
    if (poly.Length() == 0) {
        cout << "0" << endl;
        return;
    }
    ChainNode<Term<T>>* p = poly.first->link;
    while (p != poly.first) {
        cout << p->data;
        p = p->link;
        if (p != poly.first) {
            cout << " + ";
        }
    }
    cout << endl;
}

// ------------- main 함수 구현 -------------
int main(void) {

    Polynomial<int> a, b, sum;

    char select;
    double c;
    int e;

    cout << endl << "명령 선택: a: Add_a, b: Add_b, p: a + b, d: DisplayAll, q: exit" << endl;
    cin >> select;
    while (select != 'q')
    {
        switch (select)
        {
        case 'a':
            cout << "리스트 a의 항 입력 : " << endl;
            cout << "double coef: ";
            cin >> c;
            cout << "int exp (내림차순): ";
            cin >> e;
            a.add(c, e); // 지수를 내림차순으로 정렬하여 삽입
            break;
        case 'b':
            cout << "리스트 b의 항 입력: " << endl;
            cout << "double coef: ";
            cin >> c;
            cout << "int exp (내림차순): ";
            cin >> e;
            b.add(c, e);
            break;
        case 'p': // a + b
            cout << "a + b: ";
            sum = a + b;
            sum.display();
            break;
        case 'd':
            cout << "display all: " << endl;
            cout << "Polynomial a: ";
            a.display();
            cout << "Polynomial b: ";
            b.display();
            break;
        default:
            cout << "WRONG INPUT  " << endl;
            cout << "Re-Enter" << endl;
        }
        cout << endl << "Select command: a: Add_a, b: Add_b, p: Plus, d: DisplayAll, q: exit" << endl;
        cin >> select;
    }
    return 0;
}
