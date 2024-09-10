//�ҽ� �ڵ�1.9: ����� ǥ���ϴ� Ŭ����
//2���� �迭�� ������� �ʰ� pointer�� ����� data representation ���.

#include <iostream>

#include <stdlib.h>
using namespace std;

// implement the functions : add, sub, mult, transpose
class Matrix {
public:
	Matrix(int row, int col);
	Matrix(const Matrix&);
	~Matrix();//data member�� int * �̹Ƿ� �Ҹ��� ������ �� �ʿ��ϴ�
	int GetData();
	Matrix Transpose();
	int Display();
	Matrix Multiply(Matrix b);
	Matrix Add(Matrix b);
	Matrix Sub(Matrix b);
	Matrix Multiply2(Matrix b);
	int CompareRowCol(Matrix b);
	void operator=(const Matrix&);
private:
	int rows, cols;
	int* Term;
};

Matrix::Matrix(int row, int col) : rows(row), cols(col)
{

}
Matrix::Matrix(const Matrix& m) {

}
Matrix::~Matrix() {

}
void Matrix::operator=(const Matrix& m) {

}
int Matrix::GetData() {

}

Matrix Matrix::Transpose() {

}

Matrix Matrix::Multiply(Matrix b) {

}

Matrix Matrix::Add(Matrix b) {

}

Matrix Matrix::Sub(Matrix b) {

}

Matrix Matrix::Multiply2(Matrix b) {

}

int Matrix::CompareRowCol(Matrix b) {

}

int Matrix::Display() {


}

int main()
{
	Matrix a(12, 13); Matrix a1(12, 13); Matrix a2(12, 13);
	Matrix b(13, 14); Matrix b1(13, 14); Matrix b2(13, 14);
	Matrix c(12, 14);
	Matrix d(12, 14);
	Matrix t(14, 13);
	cout << "Enter first matrix: " << endl;
	a.GetData(); a1.GetData();
	a2 = a.Add(a1);

	cout << "Enter second matrix: " << endl;
	b.GetData(); b1.GetData();
	b2 = b.Sub(b1);
	cout << "Display first matrix: " << endl;
	a.Display();
	cout << "Display second matrix: " << endl;
	b.Display();
	t = b.Transpose();
	cout << "Transpose( ) of Matrix b" << endl;
	t.Display();

	/* If colum of first matrix in not equal to row of second matrix, asking user to enter the size of matrix again. */
	if (a.CompareRowCol(b))
	{
		cout << "Error! column of first matrix not equal to row of second.";
		cout << "Enter rows and columns for first matrix: ";
	}
	c = a.Multiply(b);//not using transpose( )
	cout << "Multiply of Matrix a,b" << endl;
	cout << c;
	d = c.Sub(d);
	cout << d;
	cout << "using transpose( )" << endl;
	t = b.transpose();
	c = a.Multiply2(t);//using transpose( )
	cout << c;
	system("pause");
	return 0;
}