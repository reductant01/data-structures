#include <iostream>
#include <cstdlib>
#include <ctime>

#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5

using namespace std;

class Matrix {
private:
    int rows, cols;
    static int* data;     // 모든 객체가 공유하는 static 배열
    static int free;      // data 배열에서 다음에 사용할 위치를 기록
    int start, finish;    // 이 행렬이 사용하는 data 배열의 범위를 기록
    int terms;            // 이 행렬에 저장된 데이터의 개수

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        terms = r * c;
        start = free;     // 이 행렬의 시작 인덱스는 현재 free가 가리키는 위치
        finish = start + terms; // finish는 시작 + 데이터 수
        free += terms;    // free 포인터를 데이터 개수만큼 증가
    }

    int get_data();
    int show_data(const string& msg);
    int sort_data();
    Matrix& addMatrix(Matrix&);
    Matrix& MultiplyMatrix(Matrix&);
};

// static 멤버 변수 초기화
int Matrix::free = 0;
int* Matrix::data = new int[100];  // 100개의 정수를 저장할 수 있는 메모리 할당

// 데이터를 랜덤으로 채우는 함수
int Matrix::get_data() {
    for (int i = start; i < finish; ++i) {
        data[i] = rand() % 100;  // 0 ~ 99 사이의 랜덤한 숫자를 채움
    }
    return 0;
}

// 행렬 데이터를 출력하는 함수
int Matrix::show_data(const string& msg) {
    cout << msg << " (" << rows << " x " << cols << "):" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << data[start + i * cols + j] << " ";
        }
        cout << endl;
    }
    return 0;
}

// 행렬 데이터를 오름차순으로 정렬하는 함수
int Matrix::sort_data() {
    for (int i = start; i < finish - 1; ++i) {
        for (int j = i + 1; j < finish; ++j) {
            if (data[i] > data[j]) {
                swap(data[i], data[j]);
            }
        }
    }
    return 0;
}

// 두 행렬을 더하는 함수 (A + B)
Matrix& Matrix::addMatrix(Matrix& m) {
    // 행렬 크기가 같을 때만 더할 수 있음
    if (this->rows != m.rows || this->cols != m.cols) {
        cerr << "행렬 크기가 일치하지 않아 더할 수 없습니다." << endl;
        exit(1);
    }

    // 새로운 행렬 생성 (더한 결과를 저장)
    Matrix* result = new Matrix(rows, cols);
    for (int i = 0; i < terms; ++i) {
        result->data[result->start + i] = this->data[this->start + i] + m.data[m.start + i];
    }

    return *result;
}

// 행렬 곱셈 함수 (A * B)
Matrix& Matrix::MultiplyMatrix(Matrix& m) {
    if (this->cols != m.rows) {
        cerr << "행렬 곱셈이 불가능합니다 (A의 열 수와 B의 행 수가 맞지 않음)." << endl;
        exit(1);
    }

    Matrix* result = new Matrix(this->rows, m.cols);

    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            result->data[result->start + i * m.cols + j] = 0;
            for (int k = 0; k < this->cols; ++k) {
                result->data[result->start + i * m.cols + j] += this->data[this->start + i * this->cols + k] * m.data[m.start + k * m.cols + j];
            }
        }
    }

    return *result;
}

int main(void) {
    Matrix matrixA(AROWS, ACOLS);
    Matrix matrixA1(AROWS, ACOLS);
    Matrix matrixA2(AROWS, ACOLS);
    Matrix matrixB(BROWS, BCOLS);
    Matrix matrixC(CROWS, CCOLS);

    srand(time(NULL));

    matrixA.get_data();
    matrixA.show_data("행렬A");

    matrixA1.get_data();
    matrixA1.show_data("행렬A1");

    matrixB.get_data();
    matrixB.show_data("행렬B");

    matrixA2 = matrixA.addMatrix(matrixA1);  // A2 = A + A1
    matrixA2.show_data("행렬A2");

    // matrixC = matrixA.MultiplyMatrix(matrixB); // 행렬 곱셈
    // matrixC.show_data("행렬C");

    system("pause");
    return 0;
}
