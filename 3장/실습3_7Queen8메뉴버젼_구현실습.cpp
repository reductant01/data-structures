#include <iostream>
#include <cstring> // For memset
#include <exception> // For exception handling

#define ROW 8
#define COL 8

using namespace std;

// Point 클래스 정의
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

// 예외 클래스 정의
class EmptyStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "빈 Stack입니다.";
    }
};

// --- 실행시 예외: 스택이 가득 참 --- //
class OverflowStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "가득 찬 Stack입니다.";
    }
};

// Stack 템플릿 클래스 구현
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

// Stack 클래스 메서드 구현
template <class T>
Stack<T>::Stack(int stackCapacity) : topIndex(-1), capacity(stackCapacity) {
    if (capacity <= 0)
        throw OverflowStackException(); // Capacity가 0 이하일 경우 예외 던지기
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

// 체크 함수들 구현
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

bool checkDiagSW(int d[][COL], int cx, int cy) { // 왼쪽 위 ↖, 오른쪽 아래 ↘
    // 왼쪽 위 방향 검사
    int x = cx - 1, y = cy - 1;
    while (x >= 0 && y >= 0) {
        if (d[x][y] == 1)
            return false;
        x--;
        y--;
    }
    // 오른쪽 아래 방향 검사
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

bool checkDiagSE(int d[][COL], int cx, int cy) { // 오른쪽 위 ↗, 왼쪽 아래 ↙
    // 오른쪽 위 방향 검사
    int x = cx - 1, y = cy + 1;
    while (x >= 0 && y < COL) {
        if (d[x][y] == 1)
            return false;
        x--;
        y++;
    }
    // 왼쪽 아래 방향 검사
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

// nextMove 함수 구현: 현재 행에서 가능한 다음 열을 찾음
int nextMove(int d[][COL], int row, int col) {
    for (int nextCol = col; nextCol < COL; nextCol++) {
        if (checkMove(d, row, nextCol)) {
            return nextCol;
        }
    }
    return -1; // 더 이상 가능한 이동이 없을 경우
}

// 퀸의 배치를 출력하는 함수 구현
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

// solveQueen 함수 구현: 스택을 사용한 비재귀적 백트래킹 알고리즘
int solveQueen(int d[][COL], bool findAll) { // 2차원 배열을 전달할 때에는 d[][COL]처럼 행은 생략가능하지만 열의 크기는 반드시 주어져야한다.
    int solutions = 0;
    // 현재 행과 열을 추적하기 위한 변수
    int row = 0;
    int col = 0;
    Stack<Point> st(ROW); // 최대 ROW개의 퀸을 스택에 저장

    try {
        while (row < ROW) {
            // 현재 행에서 가능한 다음 열을 찾음
            col = nextMove(d, row, col);
            if (col != -1) { // 가능한 열이 있는 경우
                // 퀸을 현재 행의 col 열에 배치
                d[row][col] = 1;
                st.Push(Point(row, col));
                row++;      // 다음 행으로 이동
                col = 0;    // 다음 행의 열 탐색을 처음부터 시작
            }
            else {
                // 현재 행에 퀸을 배치할 수 없으므로 backtrack
                if (st.IsEmpty()) {
                    // 모든 가능한 경우를 탐색한 후 종료
                    break;
                }
                // 스택에서 마지막으로 배치한 퀸의 위치를 제거
                Point last = st.Pop();
                d[last.getX()][last.getY()] = 0;
                row = last.getX();
                col = last.getY() + 1;
                // 다음 열부터 다시 시도, 만약 이렇게 하지 않으면 또 똑같은 좌표를 반환하여 계속 오류발생
            }

            // 모든 퀸을 배치한 경우
            if (row == ROW) {
                showQueens(d);
                solutions++;
                if (!findAll) {
                    // 하나의 해만 찾으면 종료
                    return solutions;
                }
                // 마지막 퀸을 제거하고 다음 해를 찾기 위해 backtrack
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

// 메뉴 옵션을 위한 enum
enum MenuOption { FIND_ONE_SOLUTION = 1, FIND_ALL_SOLUTIONS, EXIT };

// main 함수 구현
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
                // ptr: 메모리를 설정할 시작 주소를 가리키는 포인터입니다.
                // value : 설정할 값입니다.이 값은 unsigned char로 변환되어 메모리에 설정됩니다.
                // num : 설정할 바이트 수입니다.
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
