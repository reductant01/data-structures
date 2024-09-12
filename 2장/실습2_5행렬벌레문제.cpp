
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
	bool CheckAllNonZero();
public:
	Matrix(int rows, int ccol):rows(rows) {
		Term = new int[rows * cols];
	}
	int GetData();
	void MoveRandom();
	int Display();

private:
	int rows, cols;
	//int Term[rows][cols];
	int* Term;//the add 2.6ress of a[i][j] = 0 + i * cols + j => Fig2.6
};
bool Matrix::CheckAllNonZero() {

}
int Matrix::GetData() {

}
void Matrix::MoveRandom() {
	const int N = 8;
	srand(time(NULL));

	moves[0].a = -1;	moves[0].b = 0;
	moves[1].a = -1;	moves[1].b = 1;
	moves[2].a = 0;		moves[2].b = 1;
	moves[3].a = 1;		moves[3].b = 1;
	moves[4].a = 1;		moves[4].b = 0;
	moves[5].a = 1;		moves[5].b = -1;
	moves[6].a = 0;		moves[6].b = -1;
	moves[7].a = -1;	moves[7].b = -1;
	int x = rand() % N;
	int y = rand() % N;

	Term[x * cols + j] = 1;
	// 난수 생성 0 ~ 7 => d라는 변수 저장
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

