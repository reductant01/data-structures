#include <iostream>
#include <cstring> // For memset
#include <exception> // For exception handling

#define ROW 8
#define COL 8

using namespace std;

// Point Ŭ���� ����
class Point {
private:
    int ix;
    int iy;
public:
    Point(int x = 0, int y = 0) : ix(x), iy(y) {}
    int getX() const { return ix; }
    int getY() const { return iy; }
    void setX(int x) { ix = x; }
    void setY(int y) { iy = y; }
};

// ���� Ŭ���� ����
class EmptyStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "�� Stack�Դϴ�.";
    }
};

// --- ����� ����: ������ ���� �� --- //
class OverflowStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "���� �� Stack�Դϴ�.";
    }
};

// Stack ���ø� Ŭ���� ����
template <class T>
class Stack {
public:
    Stack(int stackCapacity = 10);
    ~Stack();
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& item);
    T& Pop();
private:
    T* stack;
    int topIndex;
    int capacity;
};

// Stack Ŭ���� �޼��� ����
template <class T>
Stack<T>::Stack(int stackCapacity) : topIndex(-1), capacity(stackCapacity) {
    if (capacity <= 0)
        throw OverflowStackException(); // Capacity�� 0 ������ ��� ���� ������
    stack = new T[capacity];
}

template <class T>
Stack<T>::~Stack() {
    delete[] stack;
}

template <class T>
bool Stack<T>::IsEmpty() const {
    return topIndex == -1;
}

template <class T>
T& Stack<T>::Top() const {
    if (IsEmpty())
        throw EmptyStackException();
    return stack[topIndex];
}

template <class T>
void Stack<T>::Push(const T& item) {
    if (topIndex + 1 >= capacity)
        throw OverflowStackException();
    stack[++topIndex] = item;
}

template <class T>
T& Stack<T>::Pop() {
    if (IsEmpty())
        throw EmptyStackException();
    return stack[topIndex--];
}

// üũ �Լ��� ����
bool checkRow(int d[][COL], int crow) {
    for (int y = 0; y < COL; y++) {
        if (d[crow][y] == 1)
            return false;
    }
    return true;
}

bool checkCol(int d[][COL], int ccol) {
    for (int x = 0; x < ROW; x++) {
        if (d[x][ccol] == 1)
            return false;
    }
    return true;
}

bool checkDiagSW(int d[][COL], int cx, int cy) { // ���� �� ��, ������ �Ʒ� ��
    // ���� �� ���� �˻�
    int x = cx - 1, y = cy - 1;
    while (x >= 0 && y >= 0) {
        if (d[x][y] == 1)
            return false;
        x--;
        y--;
    }
    // ������ �Ʒ� ���� �˻�
    x = cx + 1;
    y = cy + 1;
    while (x < ROW && y < COL) {
        if (d[x][y] == 1)
            return false;
        x++;
        y++;
    }
    return true;
}

bool checkDiagSE(int d[][COL], int cx, int cy) { // ������ �� ��, ���� �Ʒ� ��
    // ������ �� ���� �˻�
    int x = cx - 1, y = cy + 1;
    while (x >= 0 && y < COL) {
        if (d[x][y] == 1)
            return false;
        x--;
        y++;
    }
    // ���� �Ʒ� ���� �˻�
    x = cx + 1;
    y = cy - 1;
    while (x < ROW && y >= 0) {
        if (d[x][y] == 1)
            return false;
        x++;
        y--;
    }
    return true;
}

bool checkMove(int d[][COL], int x, int y) {
    return checkRow(d, x) && checkCol(d, y) && checkDiagSW(d, x, y) && checkDiagSE(d, x, y);
}

// nextMove �Լ� ����: ���� �࿡�� ������ ���� ���� ã��
int nextMove(int d[][COL], int row, int col) {
    for (int nextCol = col; nextCol < COL; nextCol++) {
        if (checkMove(d, row, nextCol)) {
            return nextCol;
        }
    }
    return -1; // �� �̻� ������ �̵��� ���� ���
}

// ���� ��ġ�� ����ϴ� �Լ� ����
void showQueens(int data[][COL]) {
    for (int x = 0; x < ROW; x++) {
        for (int y = 0; y < COL; y++) {
            if (data[x][y] == 1)
                cout << " Q ";
            else
                cout << " . ";
        }
        cout << endl;
    }
    cout << endl;
}

// solveQueen �Լ� ����: ������ ����� ������� ��Ʈ��ŷ �˰���
int solveQueen(int d[][COL], bool findAll) { // 2���� �迭�� ������ ������ d[][COL]ó�� ���� �������������� ���� ũ��� �ݵ�� �־������Ѵ�.
    int solutions = 0;
    // ���� ��� ���� �����ϱ� ���� ����
    int row = 0;
    int col = 0;
    Stack<Point> st(ROW); // �ִ� ROW���� ���� ���ÿ� ����

    try {
        while (row < ROW) {
            // ���� �࿡�� ������ ���� ���� ã��
            col = nextMove(d, row, col);
            if (col != -1) { // ������ ���� �ִ� ���
                // ���� ���� ���� col ���� ��ġ
                d[row][col] = 1;
                st.Push(Point(row, col));
                row++;      // ���� ������ �̵�
                col = 0;    // ���� ���� �� Ž���� ó������ ����
            }
            else {
                // ���� �࿡ ���� ��ġ�� �� �����Ƿ� backtrack
                if (st.IsEmpty()) {
                    // ��� ������ ��츦 Ž���� �� ����
                    break;
                }
                // ���ÿ��� ���������� ��ġ�� ���� ��ġ�� ����
                Point last = st.Pop();
                d[last.getX()][last.getY()] = 0;
                row = last.getX();
                col = last.getY() + 1;
                // ���� ������ �ٽ� �õ�, ���� �̷��� ���� ������ �� �Ȱ��� ��ǥ�� ��ȯ�Ͽ� ��� �����߻�
            }

            // ��� ���� ��ġ�� ���
            if (row == ROW) {
                showQueens(d);
                solutions++;
                if (!findAll) {
                    // �ϳ��� �ظ� ã���� ����
                    return solutions;
                }
                // ������ ���� �����ϰ� ���� �ظ� ã�� ���� backtrack
                if (st.IsEmpty()) {
                    break;
                }
                Point last = st.Pop();
                d[last.getX()][last.getY()] = 0;
                row = last.getX();
                col = last.getY() + 1;
            }
        }
    }
    catch (const OverflowStackException& e) {
        cout << "Stack Error: " << e.what() << endl;
    }
    catch (const EmptyStackException& e) {
        cout << "Stack Error: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "Unexpected Error: " << e.what() << endl;
    }

    return solutions;
}

// �޴� �ɼ��� ���� enum
enum MenuOption { FIND_ONE_SOLUTION = 1, FIND_ALL_SOLUTIONS, EXIT };

// main �Լ� ����
int main() {
    int board[ROW][COL] = { 0 };
    MenuOption choice;
    int input;

    while (true) {
        cout << "1. Find One Solution\n2. Find All Solutions\n3. Exit\n";
        cout << "Choose an option: ";
        cin >> input;
        choice = static_cast<MenuOption>(input);

        switch (choice) {
        case FIND_ONE_SOLUTION: {
            memset(board, 0, sizeof(board));
            // void* memset(void* ptr, int value, size_t num);
                // ptr: �޸𸮸� ������ ���� �ּҸ� ����Ű�� �������Դϴ�.
                // value : ������ ���Դϴ�.�� ���� unsigned char�� ��ȯ�Ǿ� �޸𸮿� �����˴ϴ�.
                // num : ������ ����Ʈ ���Դϴ�.
            cout << "Finding one solution...\n";
            try {
                int solutions = solveQueen(board, false);
                if (solutions == 0) {
                    cout << "No solution found.\n";
                }
            }
            catch (const OverflowStackException& e) {
                cout << "Stack Error: " << e.what() << endl;
            }
            catch (const EmptyStackException& e) {
                cout << "Stack Error: " << e.what() << endl;
            }
            catch (const std::exception& e) {
                cout << "Unexpected Error: " << e.what() << endl;
            }
            break;
        }
        case FIND_ALL_SOLUTIONS: {
            memset(board, 0, sizeof(board));
            cout << "Finding all solutions...\n";
            try {
                int totalSolutions = solveQueen(board, true);
                cout << "Total solutions: " << totalSolutions << endl;
            }
            catch (const OverflowStackException& e) {
                cout << "Stack Error: " << e.what() << endl;
            }
            catch (const EmptyStackException& e) {
                cout << "Stack Error: " << e.what() << endl;
            }
            catch (const std::exception& e) {
                cout << "Unexpected Error: " << e.what() << endl;
            }
            break;
        }
        case EXIT:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
