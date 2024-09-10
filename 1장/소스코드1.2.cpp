//소스 코드1.2: 행렬 연산
//다른 크기의 행렬을 get_data( ) 함수로 처리하는 문제를 해결하기 위한 class 사용
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5
/*
행렬이 여러 개일 때 하나의 function으로 처리하는 방법을 고안
*/

int get_data(int(*p)[ACOLS], int n)
{

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			p[i][j] = rand1() % (N * N);
	return 1;
}

void show_data(int(*p)[ACOLS], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
}

void multiply(int matrixA[][ACOLS], int ar, int matrixB[][BCOLS], int br, int matrixC[][CCOLS], int cr) {

}

int main(void)
{
	int matrixA[AROWS][ACOLS];
	int matrixB[BROWS][BCOLS];
	int matrixC[CROWS][CCOLS];

	srand(time(NULL));
	get_data(matrixA, AROWS);
	show_data(matrixA, AROWS);
	get_data(matrixB, BROWS);
	show_data(matrixB, BROWS);

	multiply(matrixA, AROWS, matrixB, BROWS, matrixC, CROWS);
	show_data(matrixC, AROWS);
	system("pause");
	return 0;
}