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
};

class Polynomial {
public:
	Polynomial();
	//construct the polynomial p(x) = 0;
	Polynomial& Add(Polynomial& b);
	Polynomial operator + (Polynomial&);
	Polynomial operator - (Polynomial&);
	Polynomial operator * (Polynomial&);
	//return the sum of the polynomials *this and b
	//Polynomial Mult(Polynomial b);
	//return the product of the polynomials *this and b
	//float Eval(float f);
	//evaluate the polynomial *this at f and return the result
	void NewTerm(const float theCoeff, const int theExp);
	int Display();
	int GetData();
	friend ostream& operator <<(ostream&, Polynomial&);
	friend istream& operator >>(istream&, Polynomial&);
private:
	static Term* termArray;
	static int capacity;
	static int free;
	int start, finish;
	int terms;
};



void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity)
	{
		
	}
	termArray[free].coef = theCoeff;
	termArray[free++].exp = theExp;
}

int Polynomial::GetData() {
	int i, degree;
	float coef;
	int expo;
	cout << "Enter Degree Of Polynomial:";
	cin >> degree;
	//
	finish = free - 1;
	terms = finish - start + 1;
	return 0;
}

Polynomial& Polynomial::Add(Polynomial& b)
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
	cout << "입력 예제: \nP(x)=5x^3+3x^1\nEnter the Polynomial like\nP(x)=5x^3+0x^2+3x^1+0x^0\n";
	cout << "Enter Polynomial1:-" << endl;
	P1.GetData();
	cout << "Enter Polynomial2:-" << endl;
	P2.GetData();

	while (1) {
		cout << "\n****** Menu Selection ******" << endl;
		cout << "1: Addition\n2: Subtraction\n3: Multiplication\n4: Evaluation\n0: Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		// switch 문에서 enum 사용
		switch (static_cast<MenuChoice>(choice)) {
		case ADDITION:
			cout << "\n--------------- Addition ---------------\n";
			cout << "Polynomial1: ";
			P1.Display();
			cout << "Polynomial2: ";
			P2.Display();
			P3 = P1.Add(P2);
			cout << "Resultant Polynomial: ";
			P3.Display();
			cout << "----------------------------------------\n";
			break;

		case SUBTRACTION:
			cout << "\n------------- Subtraction -------------\n";
			cout << "Polynomial1: ";
			P1.Display();
			cout << "Polynomial2: ";
			P2.Display();
			P3 = P1.Subtract(P2);
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
			P3 = P1.Multiply(P2);
			cout << "Resultant Polynomial: ";
			P3.Display();
			cout << "----------------------------------------\n";
			break;

		case EVALUATION:
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
