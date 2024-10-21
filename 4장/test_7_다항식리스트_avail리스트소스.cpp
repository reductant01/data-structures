/*
 * 단계7 : 다항식 연결리스트: Available Linked List
 * Circular list를 사용한 version, available list를 사용한 구현
 * Template 버전 구현 
 */

#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

// Forward declarations
template <class Type> class CircularList;
template <class Type> class CircularListIterator;

// ------------- Term 클래스 -------------
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

// operator<< 구현
template <class T>
ostream& operator<<(ostream& os, const Term<T>& e)
{
    if (e.coef == 0) return os; // 계수가 0이면 출력하지 않음
    if (e.exp == 0){
        os << e.coef;
    }
    else{
        os << e.coef << "X^" << e.exp;
    }
    return os;
}

// ------------- ListNode 클래스 -------------
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

// ListNode 생성자 구현
template <class Type>
ListNode<Type>::ListNode(Type Default)
{
    data = Default;
    link = nullptr;
}

template <class Type>
ListNode<Type>::ListNode()
{
    data = Type(); // 기본 생성자 호출
    link = nullptr;
}

// ListNode operator<< 구현
template <class Type>
ostream& operator<<(ostream& os, const ListNode<Type>& ln) {
    os << ln.data;
    return os;
}

// ------------- CircularList 클래스 -------------
template <class Type>
class CircularList {
    friend class CircularListIterator<Type>;
public:
    CircularList() { 
        first = GetNode();    // 더미 노드 생성
        first->link = first;  // 자기 자신을 가리키도록 설정
        last = first;         // 초기에는 last도 더미 노드를 가리킴
    }

    CircularList(const CircularList<Type>& l) {
        if (l.first == l.last) { // 빈 리스트
            first = GetNode();
            first->link = first;
            last = first;
            return;
        }
        // 복사할 리스트가 비어있지 않은 경우
        first = GetNode();    // 새로운 더미 노드 생성
        first->link = first;
        last = first;
        ListNode<Type>* current = l.first->link; // 첫 번째 실제 노드
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
        newnode->link = first->link; // 새 노드의 링크는 더미 노드 다음
        first->link = newnode;       // 더미 노드의 링크를 새 노드로 설정
        last = newnode;              // last를 새 노드로 업데이트
    }

    ListNode<Type>* GetNode() {
        if (av != nullptr) { // available list에 노드가 있으면
            ListNode<Type>* temp = av;
            av = av->link;
            return temp;
        }
        else { // 없으면 새 노드 생성
            return new ListNode<Type>();
        }
    }

    void RetNode(ListNode<Type>* x) { // 노드 반환
        x->link = av;
        av = x;
    }

    void Erase() { // 모든 노드 삭제 (available list로 반환)
        if (first == last) return; // 빈 리스트
        ListNode<Type>* current = first->link;
        while (current != first) {
            ListNode<Type>* temp = current;
            current = current->link;
            RetNode(temp);
        }
        first->link = first; // 리스트를 비우고 마지막 노드는 더미 노드를 가리키도록 설정
        last = first;        // last를 더미 노드로 재설정
    }

    // Friend operator<< 구현
    template <class T>
    friend ostream& operator<<(ostream& os, const CircularList<T>& cl);

private:
    ListNode<Type>* first;  // 더미 노드를 가리키는 포인터
    ListNode<Type>* last;   // 마지막 노드를 가리키는 포인터
    static ListNode<Type>* av; // available list (static)
};

// static 변수 초기화
template <class Type>
ListNode<Type>* CircularList<Type>::av = nullptr;

// operator<< 구현
template <class Type>
ostream& operator<<(ostream& os, const CircularList<Type>& l)
{
    os << "원형 리스트 출력: ";
    CircularListIterator<Type> li(l);
    if (!li.NotNull()) { // 빈 리스트
        os << "리스트가 비어 있습니다.";
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

// ------------- CircularListIterator 클래스 -------------
template <class Type>
class CircularListIterator {
public:
    CircularListIterator(const CircularList<Type>& l) : list(l), current(l.first->link), started(false) {}

    Type* First() {
        if (list.first == list.last) { // 빈 리스트
            return nullptr;
        }
        current = list.first->link;
        started = true;
        return &current->data;
    }

    Type* Next() {
        if (!started) return nullptr;
        current = current->link;
        if (current == list.first) { // 원형 리스트의 끝
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

// ------------- Polynomial 클래스 -------------
template <class Type>
class Polynomial
{
private:
    CircularList<Term<Type>> poly;
public:
    Polynomial() { }

    Polynomial(const Polynomial<Type>& p) : poly(p.poly) { }

    // Polynomial 덧셈 연산자 오버로딩
    Polynomial<Type>* operator+(const Polynomial<Type>& b) const;

    void Add(const Term<Type>& e) {
        poly.Attach(e);
    }

    void Erase() {
        poly.Erase();
    }

    void GetData();

    // Friend operator<< 구현
    template <class T>
    friend ostream& operator<<(ostream&, const Polynomial<T>&);
};

// operator+ 구현
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
        else { // 지수가 동일한 경우
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

    // 남아있는 항들 추가
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

// operator<< 구현
template <class Type>
ostream& operator<<(ostream& os, const Polynomial<Type>& p)
{
    os << p.poly;
    return os;
}

// Polynomial::GetData 구현
template <class Type>
void Polynomial<Type>::GetData()
{
    // 다항식 항의 개수를 랜덤하게 생성 (1~6개)
    int numTerms = rand() % 6 + 1; // 1~6 terms
    for(int i=0; i<numTerms; ++i){
        double coef = ((double)(rand() % 1801) / 100.0) - 9.0; // -9.0 ~ +9.0
        int exp = rand() % 6; // 0~5
        Term<Type> m;
        m.NewTerm(coef, exp);
        poly.Attach(m);
    }
}

// ------------- main 함수 구현 -------------
int main()
{
    srand(time(NULL));

    Polynomial<float> p, q, r;
    Polynomial<float>* s = nullptr, * t = nullptr;
    char select;
    Term<float> e;
    cout << endl << "Select command: a: 다항식 입력, b: p+q, c: (p+q)+r, q: exit" << endl;
    cin >> select;
    while (select != 'q')
    {
        switch (select)
        {
        case 'a':
            p.GetData();
            q.GetData();
            r.GetData();
            cout << "다항식 p, q, r 입력 결과::" << endl;
            cout << "p(x) = " << p << endl;
            cout << "q(x) = " << q << endl;
            cout << "r(x) = " << r << endl;
            break;
        case 'b': // p + q
            s = p + q;
            cout << "a = p + q 실행결과::" << endl;
            cout << "p(x) = " << p << endl;
            cout << "q(x) = " << q << endl;
            cout << "s(x) = " << *s << endl;
            cout << "다항식 p, q를 삭제" << endl;
            p.Erase(); q.Erase();
            break;
        case 'c': // s + r
            if(s == nullptr){
                cout << "s가 아직 생성되지 않았습니다. 먼저 p + q를 수행하세요." << endl;
                break;
            }
            t = (*s) + r;
            cout << "t = s + r 실행결과::" << endl;
            cout << "s(x) = " << *s << endl;
            cout << "r(x) = " << r << endl;
            cout << "t(x) = " << *t << endl;
            cout << "다항식 s, r를 삭제" << endl;
            s->Erase(); 
            r.Erase();
            delete s; // 메모리 해제
            s = nullptr;
            break;
        default:
            cout << "WRONG INPUT  " << endl;
            cout << "Re-Enter" << endl;
        }
        cout << endl << "Select command: a: 다항식 입력, b: p+q, c: (p+q)+r, q: exit" << endl;
        cin >> select;
    }
    return 0;
}
