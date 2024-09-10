
#include <iostream>
using namespace std;
#include <stdlib.h>
#include "time.h"
struct Offsets {
	int a, b;
};
enum directions { N, NE, E, SE, S, SW, W, NW };
Offsets moves[8];
class Matrix {
private:
	bool CheckNonZero();
public:
	Matrix(int row, int col);
	int GetData();
	void MoveRandom();
	int Display();

private:
	int rows, cols;
	//int Term[rows][cols];
	int* Term;//the add 2.6ress of a[i][j] = 0 + i * cols + j => Fig2.6
};


void Matrix::MoveRandom() {
	srand(time(NULL));

	moves[N].a = -1;	moves[N].b = 0;
	moves[1].a = -1;	moves[1].b = 1;
	moves[2].a = 0;		moves[2].b = 1;
	moves[3].a = 1;		moves[3].b = 1;
	moves[4].a = 1;		moves[4].b = 0;
	moves[5].a = 1;		moves[5].b = -1;
	moves[6].a = 0;		moves[6].b = -1;
	moves[7].a = -1;	moves[7].b = -1;
	
}

int Matrix::Display() {
	
}

int main()
{
	Matrix table(8, 8);

	table.GetData();
	table.Display();
	table.MoveRandom();
	table.Display();
	system("pause");
	return 0;
}

