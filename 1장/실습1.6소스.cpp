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
    int row, col;
    int* data;
public:
    Matrix(int r, int c) : row(r), col(c) {
        data = new int[row * col];
    }
    ~Matrix() {
        delete[] data;
    }
    int get_data();
    int show_data() const;
    int sort_data();
    Matrix& addMatrix(const Matrix&);
    int multiplyMatrix(const Matrix&, Matrix&);
};

int Matrix::get_data() {
    for (int i = 0; i < row * col; ++i) {
        data[i] = rand() % 100;  // 0 ~ 99 ������ ���� ����
    }
    return 0;
}

int Matrix::show_data() const {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << data[i * col + j] << " ";
        }
        cout << endl;
    }
    return 0;
}

int Matrix::sort_data() {
    // ������ ���� ������ ����Ͽ� �������� ����
    for (int i = 0; i < row * col - 1; ++i) {
        for (int j = 0; j < row * col - i - 1; ++j) {
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
            }
        }
    }
    return 0;
}

Matrix& Matrix::addMatrix(const Matrix& other) {
    if (this->row != other.row || this->col != other.col) {
        cerr << "����� ũ�Ⱑ ��ġ���� �ʽ��ϴ�." << endl;
        exit(1);  // ���� ����
    }

    for (int i = 0; i < row * col; ++i) {
        this->data[i] += other.data[i];
    }
    return *this;
}

int Matrix::multiplyMatrix(const Matrix& B, Matrix& C) {
    if (this->col != B.row || C.row != this->row || C.col != B.col) {
        cerr << "��� ������ �Ұ����մϴ�." << endl;
        return -1;
    }

    // ��� ����: C = A * B
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < B.col; ++j) {
            C.data[i * C.col + j] = 0;  // �ʱ�ȭ
            for (int k = 0; k < this->col; ++k) {
                C.data[i * C.col + j] += this->data[i * this->col + k] * B.data[k * B.col + j];
            }
        }
    }
    return 0;
}

int main(void)
{
    srand(time(NULL));

    Matrix matrixA(AROWS, ACOLS);
    Matrix matrixA1(AROWS, ACOLS);
    Matrix matrixA2(AROWS, ACOLS);
    Matrix matrixB(BROWS, BCOLS);
    Matrix matrixC(CROWS, CCOLS);

    cout << endl << "��� A: " << AROWS << " x " << ACOLS << endl;
    matrixA.get_data();
    matrixA.show_data();

    cout << endl << "��� B: " << BROWS << " x " << BCOLS << endl;
    matrixB.get_data();
    matrixB.show_data();

    cout << endl << "���ĵ� ��� A: " << endl;
    matrixA.sort_data();
    matrixA.show_data();

    cout << endl << "��� A1: " << endl;
    matrixA1.get_data();
    matrixA1.show_data();

    cout << endl << "��� A2 (A + A1): " << endl;
    matrixA2 = matrixA.addMatrix(matrixA1);
    matrixA2.show_data();

    system("pause");
    return 0;
}
