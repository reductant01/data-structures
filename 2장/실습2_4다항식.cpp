//�ҽ� �ڵ�2.5: Polynomial Ŭ����
/*
* +, -, *, << , >> operator�� ����� �������� �����Ѵ�.
* template �������� ����: T coef;
* sub�� Mult(), Eval()�� �����Ѵ�
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath> // pow �Լ��� ����ϱ� ���� �߰�

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
	Polynomial& Add(Polynomial& b); // Add�Լ��� �����Ͽ� �Ʒ��� operator�� �����ϴµ� ����Ͽ���
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
		copy(termArray, termArray + free, temp); //tempArray=������ ������, termArray + free=������ ���� ���� ????
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
	cout << "���׽��� degree �Է�: ";
	cin >> degree;
	for (int i = degree; i >= 0; i--) {
		int coef;
		do {
			cout << "��� �Է� (���� " << i << "): ";
			cin >> coef;
			if (coef == 0)
				cout << "����� 0�̸� �ٽ� �Է��ϼ���." << endl;
		} while (coef == 0);
		NewTerm(coef, i);
	}
	return degree;
	//����� 0�̸� �ٽ� 
	//���� �����Ͽ� ���, ���� �Է�
	//������ ���� �������� �Է�
	//��� 0�� ����
}

int Polynomial::Display() { // coef�� 0�� �ƴ� term �� �ִٰ� �����Ѵ� 
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

	// ���� �׵� �߰�
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
	// �� ��° ���׽��� ����� �ݴ�� ���� ���ο� ���׽��� ����
	Polynomial* negB = new Polynomial();
	for (int i = b.start; i < b.finish; i++)
	{
		negB->NewTerm(-termArray[i].coef, termArray[i].exp);
	}
	// Add �Լ��� ����Ͽ� ���� ����
	Polynomial& result = this->Add(*negB);
	delete negB; // �޸� ����
	return result;
}

Polynomial& Polynomial::operator * (Polynomial& b)
{
	Polynomial* result = new Polynomial();

	// �� ���� ���� ����� ���������� �߰�
	for (int i = this->start; i < this->finish; i++)
	{
		Polynomial temp;
		for (int j = b.start; j < b.finish; j++)
		{
			double newCoef = termArray[i].coef * termArray[j].coef;
			int newExp = termArray[i].exp + termArray[j].exp;
			temp.NewTerm(newCoef, newExp);
		}
		*result = *result + temp; // Add �Լ��� ����Ͽ� ������
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

// enum ����
enum MenuChoice { ADDITION = 1, SUBTRACTION, MULTIPLICATION, EVALUATION, EXIT };

int main(void) {
	srand(time(NULL));
	int choice;
	Polynomial P1, P2, P3;
	cout << "�Է� ����: P(x)=5x^3+3x^1" << endl;
	cout << "<�Է� ���׽� P1>" << endl;
	P1.GetData();
	P1.Display();
	cout << "<�Է� ���׽� P2>" << endl;
	P2.GetData();
	P2.Display();
	cout << "****" << endl;
	while (1) {
		cout << "\n****** Menu Selection ******" << endl;
		cout << "1: Addition\n2: Subtraction\n3: Multiplication\n4: Evaluation\n5: Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		// switch ������ enum ���
		switch (static_cast<MenuChoice>(choice)) { // static_cast ??
		case ADDITION:
			cout << "\n--------------- Addition ---------------\n";
			cout << "Polynomial1: ";
			cout << P1;
			cout << "Polynomial2: ";
			cout << P2;
			P3 = P1 + P2;
			cout << "���� ���: ";
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

		case EVALUATION: // ������ �־����� ���� ����ؼ� ���
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