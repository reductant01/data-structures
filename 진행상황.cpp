#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <vector>
#include <exception>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()
#include <cctype>  // isalpha, isspace
#include <cmath>   // pow 함수 사용

using namespace std;

//--- 실행시 예외: 스택이 비어 있음 ---//
class EmptyStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "빈 Stack.";
    }
};

//--- 실행시 예외: 스택이 가득 참 ---//
class OverflowStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "full Stack.";
    }
};

// 템플릿 Stack 클래스
template <class T>
class Stack {
public:
    Stack(int stackCapacity = 4);
    ~Stack();
    bool IsFull() const;
    bool IsEmpty() const;
    T& Peek() const;
    void Push(const T& item);
    T Pop();
private:
    T* stack;
    int top;
    int capacity;
};

// Stack 클래스 메서드 구현
template <class T>
Stack<T>::Stack(int stackCapacity) : capacity(stackCapacity), top(-1) {
    stack = new T[capacity];
}

template <class T>
Stack<T>::~Stack() {
    delete[] stack;
}

template <class T>
bool Stack<T>::IsFull() const {
    return top >= capacity - 1;
}

template <class T>
bool Stack<T>::IsEmpty() const {
    return top == -1;
}

template <class T>
T& Stack<T>::Peek() const {
    if (IsEmpty())
        throw EmptyStackException();
    return stack[top];
}

template <class T>
void Stack<T>::Push(const T& item) {
    if (IsFull())
        throw OverflowStackException();
    stack[++top] = item;
}

template <class T>
T Stack<T>::Pop() {
    if (IsEmpty())
        throw EmptyStackException();
    return stack[top--];
}

typedef vector<string> Expr;
typedef string Token;

// 전역 변수
int index_pos = 0; // 'index'는 이미 C++에서 예약어로 사용되므로 'index_pos'로 변경
int inputData[26] = { 0 };

// 다음 토큰을 추출하는 함수 구현
string NextToken(const string& e) {
    if (index_pos >= e.size()) return "#";
    // 공백 무시
    while (index_pos < e.size() && isspace(e[index_pos])) index_pos++;
    if (index_pos >= e.size()) return "#";

    // 연산자 처리 (다중 문자 연산자 우선)
    string op;
    if (index_pos + 1 < e.size()) {
        string twoChar = e.substr(index_pos, 2);
        if (twoChar == "==" || twoChar == "!=" || twoChar == ">=" || twoChar == "<=" || twoChar == "&&" || twoChar == "||") {
            op = twoChar;
            index_pos += 2;
            return op;
        }
    }

    // 단일 문자 연산자
    char c = e[index_pos];
    if (c == '(' || c == ')' || c == '!' || c == '<' || c == '>' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
        op = string(1, c);
        index_pos += 1;
        return op;
    }

    // 피연산자 처리 (대문자 단일 문자)
    if (isalpha(c) && isupper(c)) {
        string operand = string(1, c);
        index_pos += 1;
        return operand;
    }

    // 알 수 없는 문자 처리
    index_pos += 1;
    return "";
}

// 피연산자인지 확인하는 함수
bool isOperand(const string& x) {
    return (x.size() == 1 && isalpha(x[0]) && isupper(x[0]));
}

// 연산자 우선순위 반환 (스택에서의 우선순위)
int isp(const string& a) {
    if (a == "#") return 8;
    if (a == "(") return 8;
    if (a == "!" || a == "-") return 1;
    if (a == "*" || a == "/" || a == "%") return 2;
    if (a == "+" || a == "-") return 3;
    if (a == "<" || a == ">" || a == "<=" || a == ">=") return 4;
    if (a == "==" || a == "!=") return 5;
    if (a == "&&") return 6;
    if (a == "||") return 7;
    return 9; // 알 수 없는 연산자
}

// 연산자 우선순위 반환 (입력되는 연산자의 우선순위)
int icp(const string& a) { // 스택에 있는 연산자의 우선순위를 반환
    if (a == "(") return 0;
    if (a == "!" || a == "-") return 1;
    if (a == "*" || a == "/" || a == "%") return 2;
    if (a == "+" || a == "-") return 3;
    if (a == "<" || a == ">" || a == "<=" || a == ">=") return 4;
    if (a == "==" || a == "!=") return 5;
    if (a == "&&") return 6;
    if (a == "||") return 7;
    return 9; // 알 수 없는 연산자
}

// 중위 표기법을 후위 표기법으로 변환하고 평가하는 함수
void toPostfix(const string& infixString) {
    cout << endl << "infix 표기의 expression 입력: " << infixString << endl;

    // 변수에 난수 값 할당 (0~99)
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < 26; i++) {
        inputData[i] = rand() % 100;
    }

    // 변수 값 출력
    cout << "변수 값 (A~Z):" << endl;
    for (int i = 0; i < 26; i++) {
        char var = 'A' + i;
        cout << var << " = " << inputData[i] << "  ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
    cout << endl;

    // 중위 표기법을 후위 표기법으로 변환
    Expr postfix;
    Postfix(infixString, postfix);

    // 후위 표기법은 이미 Postfix 함수에서 출력됨.

    // 후위 표기법을 평가
    Eval(postfix);
}

// 후위 표기법으로 변환하는 함수 (for 문 사용)
void Postfix(const string& e, Expr& postfix) {
    Stack<string> stack(30);
    stack.Push("#");

    index_pos = 0;

    // 플로우차트의 for 문 형태로 변경
    for (Token x = NextToken(e); x != "#"; x = NextToken(e)) {
        if (isOperand(x)) {
            cout << x << " ";
            postfix.push_back(x);
        }
        else if (x == ")") {
            // '('를 만날 때까지 스택에서 연산자를 팝하여 출력
            while (stack.Peek() != "(" && stack.Peek() != "#") {
                string op = stack.Pop();
                cout << op << " ";
                postfix.push_back(op);
            }
            if (stack.Peek() == "(")
                stack.Pop(); // '(' 제거
            else
                throw std::runtime_error("Mismatched parentheses.");
        }
        else { // 연산자
            // 스택의 연산자 우선순위가 현재 연산자의 우선순위보다 낮거나 같으면 팝하여 출력
            while (isp(stack.Peek()) <= icp(x) && stack.Peek() != "#") {
                string op = stack.Pop();
                cout << op << " ";
                postfix.push_back(op);
            }
            stack.Push(x); // 현재 연산자를 스택에 푸시
        }
    }

    // 스택에 남아 있는 연산자를 모두 팝하여 출력
    while (!stack.IsEmpty()) {
        string op = stack.Pop();
        if (op != "#") { // 초기 '#'은 출력하지 않음
            cout << op << " ";
            postfix.push_back(op);
        }
    }
    cout << endl;

    // 후위 표기법의 끝을 표시 (optional)
    // postfix.push_back("#");
}

// 후위 표기법을 평가하는 함수
void Eval(const Expr& e) {
    Stack<int> stack(30);

    for (const auto& token : e) {
        if (isOperand(token)) {
            // 변수 값 가져오기
            char var = token[0];
            if (var >= 'A' && var <= 'Z') {
                stack.Push(inputData[var - 'A']);
            }
            else {
                throw std::runtime_error("Invalid variable.");
            }
        }
        else { // 연산자
            if (token == "!") {
                if (stack.IsEmpty()) throw EmptyStackException();
                int a = stack.Pop();
                stack.Push(!a);
            }
            else { // 이항 연산자
                if (stack.IsEmpty()) throw EmptyStackException();
                int b = stack.Pop();
                if (stack.IsEmpty()) throw EmptyStackException();
                int a = stack.Pop();
                if (token == "+") stack.Push(a + b);
                else if (token == "-") stack.Push(a - b);
                else if (token == "*") stack.Push(a * b);
                else if (token == "/") {
                    if (b == 0) throw std::runtime_error("Division by zero.");
                    stack.Push(a / b);
                }
                else if (token == "%") {
                    if (b == 0) throw std::runtime_error("Modulo by zero.");
                    stack.Push(a % b);
                }
                else if (token == "<") stack.Push(a < b);
                else if (token == ">") stack.Push(a > b);
                else if (token == "<=") stack.Push(a <= b);
                else if (token == ">=") stack.Push(a >= b);
                else if (token == "==") stack.Push(a == b);
                else if (token == "!=") stack.Push(a != b);
                else if (token == "&&") stack.Push(a && b);
                else if (token == "||") stack.Push(a || b);
                else throw std::runtime_error("Unknown operator.");
            }
        }
    }

    // 결과 출력
    if (stack.IsEmpty())
        throw EmptyStackException();
    int result = stack.Pop();
    cout << "평가 결과: " << result << endl;
}

enum class Expressions {
    Exit = 0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11
};

std::string expressionToString(Expressions expression) {
    switch (expression) {
    case Expressions::E1: return "A/B-C+D*E-A*C";
    case Expressions::E2: return "(((A/B)-C)+(D*E))-(A*C)";
    case Expressions::E3: return "A*B*C";
    case Expressions::E4: return "-A+B-C+D";
    case Expressions::E5: return "A*-B+C";
    case Expressions::E6: return "(A+B)*D+E/(F+A*D)+C";
    case Expressions::E7: return "A&&B||C||!(E>F)";
    case Expressions::E8: return "!(A&&!((B<C)||(C>D)))||(E<E)";
    case Expressions::E9: return "A*B/C";
    case Expressions::E10: return "A/B-C+D*E-A*C";
    case Expressions::E11: return "A*(B+C)/D-G";
    default: return "Unknown";
    }
}

Expressions SelectExpression() {
    int choice;
    while (true) { // 유효성 검사 추가
        cout << "1:E1,2:E2,3:E3,4:E4,5:E5,6:E6,7:E7,8:E8,9:E9,10:E10,11:E11,0:Exit\n";
        cout << "번호: ";
        cin >> choice;
        if (choice >= 0 && choice <= 11) {
            return static_cast<Expressions>(choice);
        }
        else {
            cout << "잘못된 선택입니다! 다시 선택해주세요." << endl;
        }
    }
}

int main() {

    Expressions menu;
    string infix;
    while (true) {
        try {
            menu = SelectExpression();
            switch (menu) {
            case Expressions::E1: {
                infix = expressionToString(Expressions::E1);
                toPostfix(infix);
                break;
            }
            case Expressions::E2: {
                infix = expressionToString(Expressions::E2);
                toPostfix(infix);
                break;
            }
            case Expressions::E3: {
                infix = expressionToString(Expressions::E3);
                toPostfix(infix);
                break;
            }
            case Expressions::E4: {
                infix = expressionToString(Expressions::E4);
                toPostfix(infix);
                break;
            }
            case Expressions::E5: {
                infix = expressionToString(Expressions::E5);
                toPostfix(infix);
                break;
            }
            case Expressions::E6: {
                infix = expressionToString(Expressions::E6);
                toPostfix(infix);
                break;
            }
            case Expressions::E7: {
                infix = expressionToString(Expressions::E7);
                toPostfix(infix);
                break;
            }
            case Expressions::E8: {
                infix = expressionToString(Expressions::E8);
                toPostfix(infix);
                break;
            }
            case Expressions::E9: {
                infix = expressionToString(Expressions::E9);
                toPostfix(infix);
                break;
            }
            case Expressions::E10: {
                infix = expressionToString(Expressions::E10);
                toPostfix(infix);
                break;
            }
            case Expressions::E11: {
                infix = expressionToString(Expressions::E11);
                toPostfix(infix);
                break;
            }
            case Expressions::Exit:
                cout << "프로그램을 종료합니다." << endl;
                return 0;
            default:
                cout << "잘못된 선택입니다! 다시 선택해주세요." << endl;
            }

        }
        catch (const EmptyStackException& e) {
            cout << "스택 empty 예외 : " << e.what() << endl;
        }
        catch (const OverflowStackException& e) {
            cout << "스택 overflow 예외: " << e.what() << endl;
        }
        catch (const std::runtime_error& e) {
            cout << "런타임 예외: " << e.what() << endl;
        }
        catch (...) {
            cout << "알 수 없는 예외가 발생했습니다." << endl;
        }
    }
}
