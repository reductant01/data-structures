/*
* backtracking �˰��� 
* 1. 8-Queen ������ 8x8 �迭�� 8���� Queen�� ����, ����, �밢������ collision�� �߻��ϰ� ��ġ
* 2. 1���� �ظ� ���ϴ� ��� ���� ���� > enum���� �޴� ���� 
* 3. 92���� �ظ� ��� ���ϴ� ��� ���� ���� > enum���� �޴� ���� 
* stack�� template���� ���� Ŭ������ �����Ͽ� throw, try {] catch(){} ����
* recursive �˰������� �����ϸ� �ȵǸ� stack�� ����� non-recursive �˰��� ����
* nextMove() �Լ��� ����Ͽ� ���� �ʼ� 
* �ļӽǽ� ���: knight�� 8x8�� collision ���� �ִ� ��ġ�� �� �ִ� ������ ���ϴ� ������ ����  
*/
#include <iostream>
#define ROW 8
#define COL 8

using namespace std;

class Point {
private:
    int ix;
    int iy;
public:
  
};


template <class T>
class Stack {
public:
    Stack(int stackCapacity = 10);
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& item);
    T& Pop();
private:
    T* stack;
    int top;
    int capacity;
};


bool checkRow(int d[][COL], int crow) {
   
}

bool checkCol(int d[][COL], int ccol) {
    
}

bool checkDiagSW(int d[][COL], int cx, int cy) { // x++, y-- or x--, y++
    
}

bool checkDiagSE(int d[][COL], int cx, int cy) { // x++, y++ or x--, y--
    
}

bool checkMove(int d[][COL], int x, int y) {
    return checkRow(d, x) && checkCol(d, y) && checkDiagSW(d, x, y) && checkDiagSE(d, x, y);
}

int nextMove(int d[][COL], int row, int col) {
    
     // (checkMove(d, row, nextCol))�� ����Ͽ� ����
          
}

void showQueens(int data[][COL]) {
    
}

int solveQueen(int d[][COL], bool findAll) {
    int count = 0;
    int ix = 0, iy = 0;
    Stack<Point> st(100);
    Point p(ix, iy);
    d[ix][iy] = 1;
    count++;
    st.Push(p);
   

    int solutions = 0;
    while (true) {
        if (ix == 8) {
            showQueens(d);
            solutions++;
            if (!findAll) break; // �ϳ��� �ظ� ã���� ����
           
            continue;
        }

        }

       
    }
    return solutions;
}

// �޴� �ɼ��� ���� enum
enum MenuOption { FIND_ONE_SOLUTION = 1, FIND_ALL_SOLUTIONS, EXIT };

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
            cout << "Finding one solution...\n";
            solveQueen(board, false);
            break;
        }
        case FIND_ALL_SOLUTIONS: {
            memset(board, 0, sizeof(board));
            cout << "Finding all solutions...\n";
            int totalSolutions = solveQueen(board, true);
            cout << "Total solutions: " << totalSolutions << endl;
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