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

using namespace std;
class Polynomial;

class Term
{
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
ostream& operator <<(ostream& stream, Polynomial& p) {
	stream << p.Add
		return 
}
double Polynomial::Eval(int num) {

}
Polynomial::Polynomial()
{

}

int Polynomial::Display() {//coef가 0이 아닌 term 만 있다고 가정한다 

}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity)
	{
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + free, temp);
		delete[] termArray;
		termArray = temp;
	}
	termArray[free].coef = theCoeff;
	termArray[free++].exp = theExp;
}

int Polynomial::GetData() {
	cout << "다항식의 degree 입력";
	cin >> degree;
	int exp = rand() % degree;
	int coef = rand() % degree;
	do {

	} while (); // 계수가 0이면 다시 
	//난수 생성하여 계수, 지수 입력
	//지수는 내림 차순으로 입력
	//계수 0은 없다
}
Polynomial& Polynomial::operator-(Polynomial& b) {
	Polynomial c;
	return c;
}
Polynomial& Polynomial::operator*(Polynomial& b) {
	Polynomial c;
	return c;
}
Polynomial& Polynomial::operator+(Polynomial& b)
{
	
}
// enum 선언
enum MenuChoice { ADDITION = 1, SUBTRACTION, MULTIPLICATION, EVALUATION, EXIT };

int Polynomial::capacity = 100;
Term* Polynomial::termArray = new Term[100];
int Polynomial::free = 0;

int main(void) {
	srand(time(NULL));
	int choice;
	Polynomial P1, P2, P3;
	cout << "입력 예제: \nP(x)=5x^3+3x^1";
	cout << "입력 다항식 P1:-" << endl;
	P1.GetData();
	P1.Display();
	cout << "입력 다항식 P2:-" << endl;
	P2.GetData();
	P2.Display();
	cout << "****" << P2;
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
			P2.Eval(evalValue);
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
