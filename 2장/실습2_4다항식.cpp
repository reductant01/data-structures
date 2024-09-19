//소스 코드2.5: Polynomial 클래스
/*
* +, -, *, << , >> operator를 사용한 버젼으로 구현한다.
* template 버젼으로 구현: T coef;
* sub와 Mult(), Eval()를 구현한다
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath> // pow 함수를 사용하기 위해 추가

using namespace std;

class Polynomial;

class Term {
	friend Polynomial;
private:
	double coef;
	int exp;
public:

};

class Polynomial {
public:
	Polynomial();
	//construct the polynomial p(x) = 0;
	Polynomial& Add(Polynomial& b); // Add함수를 구현하여 아래의 operator를 구현하는데 사용하여라
	Polynomial& operator + (Polynomial&);
	Polynomial& operator - (Polynomial&);
	Polynomial& operator * (Polynomial&);
	//return the sum of the polynomials *this and b
	//Polynomial Mult(Polynomial b);
	//return the product of the polynomials *this and b
	//float Eval(float f);
	//evaluate the polynomial *this at f and return the result
	void NewTerm(const float theCoeff, const int theExp);
	int Display();
	int GetData();
	double Eval(int);
	friend ostream& operator <<(ostream&, Polynomial&);
	friend istream& operator >>(istream&, Polynomial&);
private:
	static Term* termArray;
	static int capacity;
	static int free;
	int start, finish;
	int terms;
};

int Polynomial::capacity = 100;
Term* Polynomial::termArray = new Term[100];
int Polynomial::free = 0;

Polynomial::Polynomial() : start(free), finish(free), terms(0) {}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity)
	{
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + free, temp); //tempArray=복사의 시작점, termArray + free=복사의 종료 지점 ????
		delete[] termArray;
		termArray = temp;
	}
	termArray[free].coef = theCoeff;
	termArray[free++].exp = theExp;
	finish++;
	terms++;
}

int Polynomial::GetData() {
	int degree;
	cout << "다항식의 degree 입력: ";
	cin >> degree;
	for (int i = degree; i >= 0; i--) {
		int coef;
		do {
			cout << "계수 입력 (지수 " << i << "): ";
			cin >> coef;
			if (coef == 0)
				cout << "계수가 0이면 다시 입력하세요." << endl;
		} while (coef == 0);
		NewTerm(coef, i);
	}
	return degree;
	//계수가 0이면 다시 
	//난수 생성하여 계수, 지수 입력
	//지수는 내림 차순으로 입력
	//계수 0은 없다
}

int Polynomial::Display() { // coef가 0이 아닌 term 만 있다고 가정한다 
	for (int i = start; i < finish; i++) {
		if (termArray[i].coef != 0) {
			if (i != start && termArray[i].coef > 0) cout << "+ ";
			cout << termArray[i].coef << "x^" << termArray[i].exp << " ";
		}
	}
	cout << endl;
	return 0;
}

Polynomial& Polynomial::Add(Polynomial& b)
{
	Polynomial* result = new Polynomial();

	int aPos = this->start;
	int bPos = b.start;

	while (aPos < this->finish && bPos < b.finish)
	{
		if (termArray[aPos].exp == termArray[bPos].exp)
		{
			double sum = termArray[aPos].coef + termArray[bPos].coef;
			if (sum != 0)
				result->NewTerm(sum, termArray[aPos].exp);
			aPos++;
			bPos++;
		}
		else if (termArray[aPos].exp > termArray[bPos].exp)
		{
			result->NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
		else
		{
			result->NewTerm(termArray[bPos].coef, termArray[bPos].exp);
			bPos++;
		}
	}

	// 남은 항들 추가
	while (aPos < this->finish)
	{
		result->NewTerm(termArray[aPos].coef, termArray[aPos].exp);
		aPos++;
	}

	while (bPos < b.finish)
	{
		result->NewTerm(termArray[bPos].coef, termArray[bPos].exp);
		bPos++;
	}

	return *result;
}

ostream& operator <<(ostream& stream, Polynomial& p) {
	p.Display();
	return stream;
}

Polynomial& Polynomial::operator + (Polynomial& b)
{
	return this->Add(b);
}

Polynomial& Polynomial::operator - (Polynomial& b)
{
	// 두 번째 다항식의 계수를 반대로 만든 새로운 다항식을 생성
	Polynomial* negB = new Polynomial();
	for (int i = b.start; i < b.finish; i++)
	{
		negB->NewTerm(-termArray[i].coef, termArray[i].exp);
	}
	// Add 함수를 사용하여 덧셈 수행
	Polynomial& result = this->Add(*negB);
	delete negB; // 메모리 해제
	return result;
}

Polynomial& Polynomial::operator * (Polynomial& b)
{
	Polynomial* result = new Polynomial();

	// 각 항을 곱한 결과를 누적합으로 추가
	for (int i = this->start; i < this->finish; i++)
	{
		Polynomial temp;
		for (int j = b.start; j < b.finish; j++)
		{
			double newCoef = termArray[i].coef * termArray[j].coef;
			int newExp = termArray[i].exp + termArray[j].exp;
			temp.NewTerm(newCoef, newExp);
		}
		*result = *result + temp; // Add 함수를 사용하여 누적합
	}

	return *result;
}

double Polynomial::Eval(int x)
{
	double result = 0.0;
	for (int i = start; i < finish; i++)
	{
		result += termArray[i].coef * pow(x, termArray[i].exp);
	}
	return result;
}

// enum 선언
enum MenuChoice { ADDITION = 1, SUBTRACTION, MULTIPLICATION, EVALUATION, EXIT };

int main(void) {
	srand(time(NULL));
	int choice;
	Polynomial P1, P2, P3;
	cout << "입력 예제: P(x)=5x^3+3x^1" << endl;
	cout << "<입력 다항식 P1>" << endl;
	P1.GetData();
	P1.Display();
	cout << "<입력 다항식 P2>" << endl;
	P2.GetData();
	P2.Display();
	cout << "****" << endl;
	while (1) {
		cout << "\n****** Menu Selection ******" << endl;
		cout << "1: Addition\n2: Subtraction\n3: Multiplication\n4: Evaluation\n5: Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		// switch 문에서 enum 사용
		switch (static_cast<MenuChoice>(choice)) { // static_cast ??
		case ADDITION:
			cout << "\n--------------- Addition ---------------\n";
			cout << "Polynomial1: ";
			cout << P1;
			cout << "Polynomial2: ";
			cout << P2;
			P3 = P1 + P2;
			cout << "덧셈 결과: ";
			cout << P3;
			cout << "----------------------------------------\n";
			break;

		case SUBTRACTION:
			cout << "\n------------- Subtraction -------------\n";
			cout << "Polynomial1: ";
			P1.Display();
			cout << "Polynomial2: ";
			P2.Display();
			P3 = P1 - P2;
			cout << "Resultant Polynomial: ";
			P3.Display();
			cout << "----------------------------------------\n";
			break;

		case MULTIPLICATION:
			cout << "\n----------- Multiplication -------------\n";
			cout << "Polynomial1: ";
			P1.Display();
			cout << "Polynomial2: ";
			P2.Display();
			P3 = P1 * P2;
			cout << "Resultant Polynomial: ";
			P3.Display();
			cout << "----------------------------------------\n";
			break;

		case EVALUATION: // 변수가 주어지면 값을 계산해서 출력
			cout << "\n------------- Evaluation -------------\n";
			int evalValue;
			cout << "Enter the value to evaluate Polynomial2: ";
			cin >> evalValue;
			cout << "P2(" << evalValue << ") = " << P2.Eval(evalValue) << endl;
			cout << "----------------------------------------\n";
			break;

		case EXIT:
			cout << "Good Bye...!!!" << endl;
			exit(0);

		default:
			cout << "Invalid choice! Please select again." << endl;
		}
	}

	system("pause");
	return 0;
}