/* ���׽� ����Ʈ: Polynomial Linked List
// ������ ���� 0<= ���� <= 5, ������ �����Ѵ�
// ����� double�� ���� �����Ѵ�.  -9.0 < ��� < 9.0
// ���� ���� �������� �����Ѵ�.
// c = a + b �����Ѵ�.
// singly linked list, circular linked list, circular linked list with head node
*/

#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

// ------------- Term Ŭ���� -------------
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

// operator<< �����ε�
template <typename valType>
inline ostream& operator<< (ostream& os, const Term<valType>& term) { // �Լ� ȣ�� ������ �����ϰ� ���� �Լ��� ������ ���
    if(term.coef == 0) return os; // ����� 0�̸� ������� ����
    if(term.exp == 0){
        os << term.coef;
    }
    else{
        os << term.coef << "x^" << term.exp;
    }
    return os;
}

// ------------- ChainNode Ŭ���� -------------
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

// ChainNode ������ ����
template <class T>
ChainNode<T>::ChainNode(const T& element) : data(element), link(NULL) {}

// ------------- Chain Ŭ���� -------------
template<class T>
class Chain; // forward declaration

template<class T>
class ChainIterator;

template<class T>
class Chain {
public:
    Chain() {
        first = new ChainNode<T>(Term<T>(0, -1)); // ���� ��� ���� (exp=-1�� ������ ��)
        first->link = first; // �ڱ� �ڽ��� ����Ŵ
    };
    ~Chain() {
        // ��� ��� ���� (���� ��嵵 ����)
        ChainNode<T>* current = first->link;
        while (current != first) {
            ChainNode<T>* temp = current;
            current = current->link;
            delete temp;
        }
        delete first; // ���� ��� ����
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
    ChainNode<T>* first; // ���� ��带 ����Ű�� ������
};

// Delete �Լ� ����
template <class T>
bool Chain<T>::Delete(int exp) // delete the node with given exponent
{
    if (first->link == first) // ����Ʈ�� ����ִ� ���
        return false;

    ChainNode<T>* current = first->link; // ���� ���
    ChainNode<T>* previous = first;       // ���� ���

    while (current != first) {
        if (current->data.exp == exp) { // ������ ���� �߰�
            previous->link = current->link;
            delete current;
            return true;
        }
        previous = current;
        current = current->link;
    }

    return false; // eno�� ���� ����� ����
}

// Length �Լ� ����
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

// Add �Լ� ����
template <class T>
void Chain<T>::Add(const T& element) // add a new node in descending exponent order
{
    ChainNode<T>* newNode = new ChainNode<T>(element);
    ChainNode<T>* current = first->link; // ù ��° ���� ���
    ChainNode<T>* previous = first;       // ���� ���

    // ����Ʈ�� ����ְų�, ù ��庸�� ū eno�� ���� ���
    if (current == first || element.exp > current->data.exp) {
        newNode->link = current;
        previous->link = newNode;
        return;
    }

    // ������ ��ġ�� ã��
    while (current != first && current->data.exp >= element.exp) {
        if (current->data.exp == element.exp) { // ������ ���� �߰�
            current->data.coef += element.coef;
            if (current->data.coef == 0) { // ����� 0�� �Ǹ� ����
                previous->link = current->link;
                delete current;
            }
            delete newNode; // ������ �ʿ� ����
            return;
        }
        previous = current;
        current = current->link;
    }

    // ���ο� ��带 ���� ��� �տ� ����
    newNode->link = current;
    previous->link = newNode;
}

// Invert �Լ� ����
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

// Concatenate �Լ� ����
template <class T>
void Chain<T>::Concatenate(Chain<T> b) {
    if (b.first->link == b.first) // b ����Ʈ�� ����ִ� ���
        return;

    ChainNode<T>* p = first;
    while (p->link != first) { // ������ ��� ã��
        p = p->link;
    }
    p->link = b.first->link; // b ����Ʈ�� ù ��° ���� ���� ����

    // b ����Ʈ�� ������ ��带 first�� �����Ͽ� ���� ����
    ChainNode<T>* q = b.first->link;
    while (q->link != b.first) {
        q = q->link;
    }
    q->link = first;
}

// InsertBack �Լ� ����
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

// displayAll �Լ� ����
template <class T>
void Chain<T>::displayAll() const {
    if (first->link == first) { // ����Ʈ�� ����ִ� ���
        cout << "����Ʈ�� ��� �ֽ��ϴ�." << endl;
        return;
    }
    ChainNode<T>* p = first->link;
    while (p != first) {
        cout << p->data << " -> ";
        p = p->link;
    }
    cout << "end" << endl;
}

// ------------- ChainIterator Ŭ���� -------------
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

// pre-increment ������ ����
template <class T>
ChainIterator<T>& ChainIterator<T>::operator++() //preincrement
{
    if (current && current->link != nullptr)
        current = current->link;
    else
        current = nullptr;
    return *this;
}

// post-increment ������ ����
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

// NotNull �Լ� ����
template <class T>
bool ChainIterator<T>::NotNull() const { //check the current element in list is non-null
    return current != NULL;
}

// NextNotNull �Լ� ����
template <class T>
bool ChainIterator<T>::NextNotNull() const { //check the next element in list is non-null
    if (current && current->link != NULL && current->link != nullptr)
        return true;
    return false;
}

// Next �Լ� ����
template <class T>
T* ChainIterator<T>::Next() {//return a pointer to the next element of list
    if (current && current->link != first && current->link != NULL) {
        current = current->link;
        return &(current->data);
    }
    return NULL;
}

// ------------- Polynomial Ŭ���� -------------
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
    T Evaluate(T&) const;//f(x)�� ���Ͽ� x�� ���� ���� ���Ѵ�
    Polynomial Multiply(Polynomial<T>&); //f(x) * g(x)
    Polynomial(const Polynomial& p); //copy constructor
    friend istream& operator>>(istream&, Polynomial&);//polynomial �Է�
    friend ostream& operator<<(ostream&, Polynomial&);//polynomial ���
    const Polynomial& operator=(const Polynomial&) const;
    ~Polynomial( );
    Polynomial operator-(const Polynomial&)const;
    */
private:
    Chain<Term<T> > poly;
};

// operator+ ����
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
        else { // ������ ������ ���
            double sumCoef = ta.coef + tb.coef;
            if (sumCoef != 0) {
                c.add(sumCoef, ta.exp);
            }
            ++ai;
            ++bi;
        }
    }

    // �����ִ� �׵� �߰�
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

// add �Լ� ����
template<class T>
void Polynomial<T>::add(double coef, int exponent) {
    Term<T> newTerm;
    newTerm.coef = coef;
    newTerm.exp = exponent;
    this->poly.Add(newTerm);
}

// addAll �Լ� ����
template<class T>
void Polynomial<T>::addAll(Polynomial<T>* b) {
    ChainIterator<Term<T>> iterB = b->poly.begin();
    while (iterB.NotNull()) {
        Term<T> dataB = *iterB;
        add(dataB.coef, dataB.exp);
        iterB.Next();
    }
}

// display �Լ� ����
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

// ------------- main �Լ� ���� -------------
int main(void) {

    Polynomial<int> a, b, sum;

    char select;
    double c;
    int e;

    cout << endl << "��� ����: a: Add_a, b: Add_b, p: a + b, d: DisplayAll, q: exit" << endl;
    cin >> select;
    while (select != 'q')
    {
        switch (select)
        {
        case 'a':
            cout << "����Ʈ a�� �� �Է� : " << endl;
            cout << "double coef: ";
            cin >> c;
            cout << "int exp (��������): ";
            cin >> e;
            a.add(c, e); // ������ ������������ �����Ͽ� ����
            break;
        case 'b':
            cout << "����Ʈ b�� �� �Է�: " << endl;
            cout << "double coef: ";
            cin >> c;
            cout << "int exp (��������): ";
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
