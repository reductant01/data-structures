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
    static int* data;     // ��� ��ü�� �����ϴ� static �迭
    static int free;      // data �迭���� ������ ����� ��ġ�� ���
    int start, finish;    // �� ����� ����ϴ� data �迭�� ������ ���
    int terms;            // �� ��Ŀ� ����� �������� ����

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        terms = r * c;
        start = free;     // �� ����� ���� �ε����� ���� free�� ����Ű�� ��ġ
        finish = start + terms; // finish�� ���� + ������ ��
        free += terms;    // free �����͸� ������ ������ŭ ����
    }

    int get_data();
    int show_data(const string& msg);
    int sort_data();
    Matrix& addMatrix(Matrix&);
    Matrix& MultiplyMatrix(Matrix&);
};

// static ��� ���� �ʱ�ȭ
int Matrix::free = 0;
int* Matrix::data = new int[100];  // 100���� ������ ������ �� �ִ� �޸� �Ҵ�

// �����͸� �������� ä��� �Լ�
int Matrix::get_data() {
    for (int i = start; i < finish; ++i) {
        data[i] = rand() % 100;  // 0 ~ 99 ������ ������ ���ڸ� ä��
    }
    return 0;
}

// ��� �����͸� ����ϴ� �Լ�
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

// ��� �����͸� ������������ �����ϴ� �Լ�
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

// �� ����� ���ϴ� �Լ� (A + B)
Matrix& Matrix::addMatrix(Matrix& m) {
    // ��� ũ�Ⱑ ���� ���� ���� �� ����
    if (this->rows != m.rows || this->cols != m.cols) {
        cerr << "��� ũ�Ⱑ ��ġ���� �ʾ� ���� �� �����ϴ�." << endl;
        exit(1);
    }

    // ���ο� ��� ���� (���� ����� ����)
    Matrix* result = new Matrix(rows, cols);
    for (int i = 0; i < terms; ++i) {
        result->data[result->start + i] = this->data[this->start + i] + m.data[m.start + i];
    }

    return *result;
}

// ��� ���� �Լ� (A * B)
Matrix& Matrix::MultiplyMatrix(Matrix& m) {
    if (this->cols != m.rows) {
        cerr << "��� ������ �Ұ����մϴ� (A�� �� ���� B�� �� ���� ���� ����)." << endl;
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
    matrixA.show_data("���A");

    matrixA1.get_data();
    matrixA1.show_data("���A1");

    matrixB.get_data();
    matrixB.show_data("���B");

    matrixA2 = matrixA.addMatrix(matrixA1);  // A2 = A + A1
    matrixA2.show_data("���A2");

    // matrixC = matrixA.MultiplyMatrix(matrixB); // ��� ����
    // matrixC.show_data("���C");

    system("pause");
    return 0;
}
