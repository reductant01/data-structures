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
    float coef;  // 계수
    int exp;     // 지수
};

class Polynomial {
private:
    static Term* TermElement;  // 모든 다항식이 공유하는 정적 배열
    static int free;           // 배열에서 다음 사용할 위치
    int start, finish;         // 다항식이 사용하는 항들의 시작과 끝
    int terms;                 // 다항식에 포함된 항의 수

public:
    Polynomial(int terms) : terms(terms) {
        start = free;
        finish = start + terms;
        free += terms;  // 다음 항들을 위한 위치 이동
    }

    int get_data();                // 계수를 난수로 생성하고 지수를 순차적으로 할당
    int show_data(string msg);      // 다항식 데이터를 출력
    int sort_data();                // 계수를 기준으로 정렬 (필요 시 구현)
    Polynomial& addPolynomial(Polynomial&); // 두 다항식을 더하는 함수
};

// static 멤버 변수 초기화
int Polynomial::free = 0;
Term* Polynomial::TermElement = new Term[100];

// 다항식 데이터를 생성하는 함수
int Polynomial::get_data() {
    for (int i = start; i < finish; ++i) {
        TermElement[i].coef = rand() % 100 / 10.0f;  // 0 ~ 9.9 사이의 난수 계수
        TermElement[i].exp = i - start;              // 지수는 0부터 순차적으로 증가
    }
    return 0;
}

// 다항식 데이터를 출력하는 함수
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

// 두 다항식을 더하는 함수
Polynomial& Polynomial::addPolynomial(Polynomial& m) {
    // 결과 다항식의 항 수는 두 다항식의 항 수를 합한 값
    Polynomial* result = new Polynomial(terms + m.terms);

    int i = start, j = m.start, k = result->start;

    // 다항식의 항들을 더할 때, 지수가 같으면 계수를 더하고, 지수가 다르면 큰 쪽을 우선 삽입
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

    // 남은 항들을 복사
    while (i < finish) {
        result->TermElement[k] = TermElement[i];
        ++i; ++k;
    }

    while (j < m.finish) {
        result->TermElement[k] = m.TermElement[j];
        ++j; ++k;
    }

    // 새로 생성된 다항식 반환
    return *result;
}

int main(void) {
    Polynomial polynomialA(ATERMS);
    Polynomial polynomialB(BTERMS);
    Polynomial polynomialC(CTERMS);

    srand(time(NULL));
    polynomialA.get_data();
    polynomialA.show_data("다항식A: ");

    polynomialB.get_data();
    polynomialB.show_data("다항식B: ");

    polynomialC = polynomialA.addPolynomial(polynomialB);
    polynomialC.show_data("다항식C: ");

    system("pause");
    return 0;
}
