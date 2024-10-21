/*
 * �ܰ�7 : ���׽� ���Ḯ��Ʈ: Available Linked List
 * Circular list�� ����� version, available list�� ����� ����
 * Template ���� ���� 
 */

#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

// Forward declarations
template <class Type> class CircularList;
template <class Type> class CircularListIterator;

// ------------- Term Ŭ���� -------------
template <class T>
class Term {
public:
    // All members of Term are public by default
    double coef; // coefficient
    int exp;     // exponent
    Term() : coef(0), exp(0) {}
    Term(double c, int e) : coef(c), exp(e) {}

    void NewTerm(double coef, int exp) {
        this->coef = coef;
        this->exp = exp;
    }

    // Friend function for operator<<
    template <class U>
    friend ostream& operator<<(ostream& os, const Term<U>& e);
};

// operator<< ����
template <class T>
ostream& operator<<(ostream& os, const Term<T>& e)
{
    if (e.coef == 0) return os; // ����� 0�̸� ������� ����
    if (e.exp == 0){
        os << e.coef;
    }
    else{
        os << e.coef << "X^" << e.exp;
    }
    return os;
}

// ------------- ListNode Ŭ���� -------------
template <class Type>
class ListNode {
    friend class CircularList<Type>;
    friend class CircularListIterator<Type>;
private:
    Type data;
    ListNode<Type>* link;
public:
    ListNode(Type);
    ListNode();
    template <class T>
    friend ostream& operator<<(ostream&, const ListNode<T>&);
};

// ListNode ������ ����
template <class Type>
ListNode<Type>::ListNode(Type Default)
{
    data = Default;
    link = nullptr;
}

template <class Type>
ListNode<Type>::ListNode()
{
    data = Type(); // �⺻ ������ ȣ��
    link = nullptr;
}

// ListNode operator<< ����
template <class Type>
ostream& operator<<(ostream& os, const ListNode<Type>& ln) {
    os << ln.data;
    return os;
}

// ------------- CircularList Ŭ���� -------------
template <class Type>
class CircularList {
    friend class CircularListIterator<Type>;
public:
    CircularList() { 
        first = GetNode();    // ���� ��� ����
        first->link = first;  // �ڱ� �ڽ��� ����Ű���� ����
        last = first;         // �ʱ⿡�� last�� ���� ��带 ����Ŵ
    }

    CircularList(const CircularList<Type>& l) {
        if (l.first == l.last) { // �� ����Ʈ
            first = GetNode();
            first->link = first;
            last = first;
            return;
        }
        // ������ ����Ʈ�� ������� ���� ���
        first = GetNode();    // ���ο� ���� ��� ����
        first->link = first;
        last = first;
        ListNode<Type>* current = l.first->link; // ù ��° ���� ���
        while (current != l.first) {
            Attach(current->data);
            current = current->link;
        }
    }

    ~CircularList() {
        Erase();
        RetNode(first);
    }

    void Attach(const Type& k) {
        ListNode<Type>* newnode = GetNode();
        newnode->data = k;
        newnode->link = first->link; // �� ����� ��ũ�� ���� ��� ����
        first->link = newnode;       // ���� ����� ��ũ�� �� ���� ����
        last = newnode;              // last�� �� ���� ������Ʈ
    }

    ListNode<Type>* GetNode() {
        if (av != nullptr) { // available list�� ��尡 ������
            ListNode<Type>* temp = av;
            av = av->link;
            return temp;
        }
        else { // ������ �� ��� ����
            return new ListNode<Type>();
        }
    }

    void RetNode(ListNode<Type>* x) { // ��� ��ȯ
        x->link = av;
        av = x;
    }

    void Erase() { // ��� ��� ���� (available list�� ��ȯ)
        if (first == last) return; // �� ����Ʈ
        ListNode<Type>* current = first->link;
        while (current != first) {
            ListNode<Type>* temp = current;
            current = current->link;
            RetNode(temp);
        }
        first->link = first; // ����Ʈ�� ���� ������ ���� ���� ��带 ����Ű���� ����
        last = first;        // last�� ���� ���� �缳��
    }

    // Friend operator<< ����
    template <class T>
    friend ostream& operator<<(ostream& os, const CircularList<T>& cl);

private:
    ListNode<Type>* first;  // ���� ��带 ����Ű�� ������
    ListNode<Type>* last;   // ������ ��带 ����Ű�� ������
    static ListNode<Type>* av; // available list (static)
};

// static ���� �ʱ�ȭ
template <class Type>
ListNode<Type>* CircularList<Type>::av = nullptr;

// operator<< ����
template <class Type>
ostream& operator<<(ostream& os, const CircularList<Type>& l)
{
    os << "���� ����Ʈ ���: ";
    CircularListIterator<Type> li(l);
    if (!li.NotNull()) { // �� ����Ʈ
        os << "����Ʈ�� ��� �ֽ��ϴ�.";
        return os;
    }
    Type* firstTerm = li.First();
    if (firstTerm != nullptr) {
        os << *firstTerm;
        Type* term;
        while ((term = li.Next()) != nullptr) {
            os << " + " << *term;
        }
    }
    os << endl;
    return os;
}

// ------------- CircularListIterator Ŭ���� -------------
template <class Type>
class CircularListIterator {
public:
    CircularListIterator(const CircularList<Type>& l) : list(l), current(l.first->link), started(false) {}

    Type* First() {
        if (list.first == list.last) { // �� ����Ʈ
            return nullptr;
        }
        current = list.first->link;
        started = true;
        return &current->data;
    }

    Type* Next() {
        if (!started) return nullptr;
        current = current->link;
        if (current == list.first) { // ���� ����Ʈ�� ��
            return nullptr;
        }
        return &current->data;
    }

    bool NotNull() const {
        return list.first != list.last;
    }

    bool NextNotNull() const {
        return current->link != list.first;
    }

private:
    const CircularList<Type>& list;
    ListNode<Type>* current;
    bool started;
};

// ------------- Polynomial Ŭ���� -------------
template <class Type>
class Polynomial
{
private:
    CircularList<Term<Type>> poly;
public:
    Polynomial() { }

    Polynomial(const Polynomial<Type>& p) : poly(p.poly) { }

    // Polynomial ���� ������ �����ε�
    Polynomial<Type>* operator+(const Polynomial<Type>& b) const;

    void Add(const Term<Type>& e) {
        poly.Attach(e);
    }

    void Erase() {
        poly.Erase();
    }

    void GetData();

    // Friend operator<< ����
    template <class T>
    friend ostream& operator<<(ostream&, const Polynomial<T>&);
};

// operator+ ����
template <class Type>
Polynomial<Type>* Polynomial<Type>::operator+(const Polynomial<Type>& b) const
{
    Polynomial<Type>* c = new Polynomial<Type>();
    CircularListIterator<Term<Type>> Aiter(this->poly);
    CircularListIterator<Term<Type>> Biter(b.poly);

    Term<Type>* p = Aiter.First();
    Term<Type>* q = Biter.First();

    while (p != nullptr && q != nullptr) {
        if (p->exp > q->exp) {
            c->Add(*p);
            p = Aiter.Next();
        }
        else if (p->exp < q->exp) {
            c->Add(*q);
            q = Biter.Next();
        }
        else { // ������ ������ ���
            double sumCoef = p->coef + q->coef;
            if (sumCoef != 0) {
                Term<Type> temp;
                temp.NewTerm(sumCoef, p->exp);
                c->Add(temp);
            }
            p = Aiter.Next();
            q = Biter.Next();
        }
    }

    // �����ִ� �׵� �߰�
    while (p != nullptr) {
        c->Add(*p);
        p = Aiter.Next();
    }

    while (q != nullptr) {
        c->Add(*q);
        q = Biter.Next();
    }

    return c;
}

// operator<< ����
template <class Type>
ostream& operator<<(ostream& os, const Polynomial<Type>& p)
{
    os << p.poly;
    return os;
}

// Polynomial::GetData ����
template <class Type>
void Polynomial<Type>::GetData()
{
    // ���׽� ���� ������ �����ϰ� ���� (1~6��)
    int numTerms = rand() % 6 + 1; // 1~6 terms
    for(int i=0; i<numTerms; ++i){
        double coef = ((double)(rand() % 1801) / 100.0) - 9.0; // -9.0 ~ +9.0
        int exp = rand() % 6; // 0~5
        Term<Type> m;
        m.NewTerm(coef, exp);
        poly.Attach(m);
    }
}

// ------------- main �Լ� ���� -------------
int main()
{
    srand(time(NULL));

    Polynomial<float> p, q, r;
    Polynomial<float>* s = nullptr, * t = nullptr;
    char select;
    Term<float> e;
    cout << endl << "Select command: a: ���׽� �Է�, b: p+q, c: (p+q)+r, q: exit" << endl;
    cin >> select;
    while (select != 'q')
    {
        switch (select)
        {
        case 'a':
            p.GetData();
            q.GetData();
            r.GetData();
            cout << "���׽� p, q, r �Է� ���::" << endl;
            cout << "p(x) = " << p << endl;
            cout << "q(x) = " << q << endl;
            cout << "r(x) = " << r << endl;
            break;
        case 'b': // p + q
            s = p + q;
            cout << "a = p + q ������::" << endl;
            cout << "p(x) = " << p << endl;
            cout << "q(x) = " << q << endl;
            cout << "s(x) = " << *s << endl;
            cout << "���׽� p, q�� ����" << endl;
            p.Erase(); q.Erase();
            break;
        case 'c': // s + r
            if(s == nullptr){
                cout << "s�� ���� �������� �ʾҽ��ϴ�. ���� p + q�� �����ϼ���." << endl;
                break;
            }
            t = (*s) + r;
            cout << "t = s + r ������::" << endl;
            cout << "s(x) = " << *s << endl;
            cout << "r(x) = " << r << endl;
            cout << "t(x) = " << *t << endl;
            cout << "���׽� s, r�� ����" << endl;
            s->Erase(); 
            r.Erase();
            delete s; // �޸� ����
            s = nullptr;
            break;
        default:
            cout << "WRONG INPUT  " << endl;
            cout << "Re-Enter" << endl;
        }
        cout << endl << "Select command: a: ���׽� �Է�, b: p+q, c: (p+q)+r, q: exit" << endl;
        cin >> select;
    }
    return 0;
}
