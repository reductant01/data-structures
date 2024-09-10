#include <iostream>
#include <cstdlib>
#include <ctime>

#define ATERMS 3
#define BTERMS 4
#define CTERMS 5

using namespace std;

class Polynomial;

class Term {
    friend Polynomial;
private:
    float coef;  // ���
    int exp;     // ����
};

class Polynomial {
private:
    static Term* TermElement;  // ��� ���׽��� �����ϴ� ���� �迭
    static int free;           // �迭���� ���� ����� ��ġ
    int start, finish;         // ���׽��� ����ϴ� �׵��� ���۰� ��
    int terms;                 // ���׽Ŀ� ���Ե� ���� ��

public:
    Polynomial(int terms) : terms(terms) {
        start = free;
        finish = start + terms;
        free += terms;  // ���� �׵��� ���� ��ġ �̵�
    }

    int get_data();                // ����� ������ �����ϰ� ������ ���������� �Ҵ�
    int show_data(string msg);      // ���׽� �����͸� ���
    int sort_data();                // ����� �������� ���� (�ʿ� �� ����)
    Polynomial& addPolynomial(Polynomial&); // �� ���׽��� ���ϴ� �Լ�
};

// static ��� ���� �ʱ�ȭ
int Polynomial::free = 0;
Term* Polynomial::TermElement = new Term[100];

// ���׽� �����͸� �����ϴ� �Լ�
int Polynomial::get_data() {
    for (int i = start; i < finish; ++i) {
        TermElement[i].coef = rand() % 100 / 10.0f;  // 0 ~ 9.9 ������ ���� ���
        TermElement[i].exp = i - start;              // ������ 0���� ���������� ����
    }
    return 0;
}

// ���׽� �����͸� ����ϴ� �Լ�
int Polynomial::show_data(string msg) {
    cout << msg;
    for (int i = start; i < finish; ++i) {
        cout << TermElement[i].coef << "x^" << TermElement[i].exp;
        if (i < finish - 1) {
            cout << " + ";
        }
    }
    cout << endl;
    return 0;
}

// �� ���׽��� ���ϴ� �Լ�
Polynomial& Polynomial::addPolynomial(Polynomial& m) {
    // ��� ���׽��� �� ���� �� ���׽��� �� ���� ���� ��
    Polynomial* result = new Polynomial(terms + m.terms);

    int i = start, j = m.start, k = result->start;

    // ���׽��� �׵��� ���� ��, ������ ������ ����� ���ϰ�, ������ �ٸ��� ū ���� �켱 ����
    while (i < finish && j < m.finish) {
        if (TermElement[i].exp == TermElement[j].exp) {
            result->TermElement[k].coef = TermElement[i].coef + m.TermElement[j].coef;
            result->TermElement[k].exp = TermElement[i].exp;
            ++i; ++j; ++k;
        }
        else if (TermElement[i].exp < m.TermElement[j].exp) {
            result->TermElement[k] = m.TermElement[j];
            ++j; ++k;
        }
        else {
            result->TermElement[k] = TermElement[i];
            ++i; ++k;
        }
    }

    // ���� �׵��� ����
    while (i < finish) {
        result->TermElement[k] = TermElement[i];
        ++i; ++k;
    }

    while (j < m.finish) {
        result->TermElement[k] = m.TermElement[j];
        ++j; ++k;
    }

    // ���� ������ ���׽� ��ȯ
    return *result;
}

int main(void) {
    Polynomial polynomialA(ATERMS);
    Polynomial polynomialB(BTERMS);
    Polynomial polynomialC(CTERMS);

    srand(time(NULL));
    polynomialA.get_data();
    polynomialA.show_data("���׽�A: ");

    polynomialB.get_data();
    polynomialB.show_data("���׽�B: ");

    polynomialC = polynomialA.addPolynomial(polynomialB);
    polynomialC.show_data("���׽�C: ");

    system("pause");
    return 0;
}
