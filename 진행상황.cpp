#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <vector>
#include <exception>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()
#include <cctype>  // isalpha, isspace
#include <cmath>   // pow �Լ� ���

using namespace std;

//--- ����� ����: ������ ��� ���� ---//
class EmptyStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "�� Stack.";
    }
};

//--- ����� ����: ������ ���� �� ---//
class OverflowStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "full Stack.";
    }
};

// ���ø� Stack Ŭ����
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

// Stack Ŭ���� �޼��� ����
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

// ���� ����
int index_pos = 0; // 'index'�� �̹� C++���� ������ ���ǹǷ� 'index_pos'�� ����
int inputData[26] = { 0 };

// ���� ��ū�� �����ϴ� �Լ� ����
string NextToken(const string& e) {
    if (index_pos >= e.size()) return "#";
    // ���� ����
    while (index_pos < e.size() && isspace(e[index_pos])) index_pos++;
    if (index_pos >= e.size()) return "#";

    // ������ ó�� (���� ���� ������ �켱)
    string op;
    if (index_pos + 1 < e.size()) {
        string twoChar = e.substr(index_pos, 2);
        if (twoChar == "==" || twoChar == "!=" || twoChar == ">=" || twoChar == "<=" || twoChar == "&&" || twoChar == "||") {
            op = twoChar;
            index_pos += 2;
            return op;
        }
    }

    // ���� ���� ������
    char c = e[index_pos];
    if (c == '(' || c == ')' || c == '!' || c == '<' || c == '>' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
        op = string(1, c);
        index_pos += 1;
        return op;
    }

    // �ǿ����� ó�� (�빮�� ���� ����)
    if (isalpha(c) && isupper(c)) {
        string operand = string(1, c);
        index_pos += 1;
        return operand;
    }

    // �� �� ���� ���� ó��
    index_pos += 1;
    return "";
}

// �ǿ��������� Ȯ���ϴ� �Լ�
bool isOperand(const string& x) {
    return (x.size() == 1 && isalpha(x[0]) && isupper(x[0]));
}

// ������ �켱���� ��ȯ (���ÿ����� �켱����)
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
    return 9; // �� �� ���� ������
}

// ������ �켱���� ��ȯ (�ԷµǴ� �������� �켱����)
int icp(const string& a) { // ���ÿ� �ִ� �������� �켱������ ��ȯ
    if (a == "(") return 0;
    if (a == "!" || a == "-") return 1;
    if (a == "*" || a == "/" || a == "%") return 2;
    if (a == "+" || a == "-") return 3;
    if (a == "<" || a == ">" || a == "<=" || a == ">=") return 4;
    if (a == "==" || a == "!=") return 5;
    if (a == "&&") return 6;
    if (a == "||") return 7;
    return 9; // �� �� ���� ������
}

// ���� ǥ����� ���� ǥ������� ��ȯ�ϰ� ���ϴ� �Լ�
void toPostfix(const string& infixString) {
    cout << endl << "infix ǥ���� expression �Է�: " << infixString << endl;

    // ������ ���� �� �Ҵ� (0~99)
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < 26; i++) {
        inputData[i] = rand() % 100;
    }

    // ���� �� ���
    cout << "���� �� (A~Z):" << endl;
    for (int i = 0; i < 26; i++) {
        char var = 'A' + i;
        cout << var << " = " << inputData[i] << "  ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
    cout << endl;

    // ���� ǥ����� ���� ǥ������� ��ȯ
    Expr postfix;
    Postfix(infixString, postfix);

    // ���� ǥ����� �̹� Postfix �Լ����� ��µ�.

    // ���� ǥ����� ��
    Eval(postfix);
}

// ���� ǥ������� ��ȯ�ϴ� �Լ� (for �� ���)
void Postfix(const string& e, Expr& postfix) {
    Stack<string> stack(30);
    stack.Push("#");

    index_pos = 0;

    // �÷ο���Ʈ�� for �� ���·� ����
    for (Token x = NextToken(e); x != "#"; x = NextToken(e)) {
        if (isOperand(x)) {
            cout << x << " ";
            postfix.push_back(x);
        }
        else if (x == ")") {
            // '('�� ���� ������ ���ÿ��� �����ڸ� ���Ͽ� ���
            while (stack.Peek() != "(" && stack.Peek() != "#") {
                string op = stack.Pop();
                cout << op << " ";
                postfix.push_back(op);
            }
            if (stack.Peek() == "(")
                stack.Pop(); // '(' ����
            else
                throw std::runtime_error("Mismatched parentheses.");
        }
        else { // ������
            // ������ ������ �켱������ ���� �������� �켱�������� ���ų� ������ ���Ͽ� ���
            while (isp(stack.Peek()) <= icp(x) && stack.Peek() != "#") {
                string op = stack.Pop();
                cout << op << " ";
                postfix.push_back(op);
            }
            stack.Push(x); // ���� �����ڸ� ���ÿ� Ǫ��
        }
    }

    // ���ÿ� ���� �ִ� �����ڸ� ��� ���Ͽ� ���
    while (!stack.IsEmpty()) {
        string op = stack.Pop();
        if (op != "#") { // �ʱ� '#'�� ������� ����
            cout << op << " ";
            postfix.push_back(op);
        }
    }
    cout << endl;

    // ���� ǥ����� ���� ǥ�� (optional)
    // postfix.push_back("#");
}

// ���� ǥ����� ���ϴ� �Լ�
void Eval(const Expr& e) {
    Stack<int> stack(30);

    for (const auto& token : e) {
        if (isOperand(token)) {
            // ���� �� ��������
            char var = token[0];
            if (var >= 'A' && var <= 'Z') {
                stack.Push(inputData[var - 'A']);
            }
            else {
                throw std::runtime_error("Invalid variable.");
            }
        }
        else { // ������
            if (token == "!") {
                if (stack.IsEmpty()) throw EmptyStackException();
                int a = stack.Pop();
                stack.Push(!a);
            }
            else { // ���� ������
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

    // ��� ���
    if (stack.IsEmpty())
        throw EmptyStackException();
    int result = stack.Pop();
    cout << "�� ���: " << result << endl;
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
    while (true) { // ��ȿ�� �˻� �߰�
        cout << "1:E1,2:E2,3:E3,4:E4,5:E5,6:E6,7:E7,8:E8,9:E9,10:E10,11:E11,0:Exit\n";
        cout << "��ȣ: ";
        cin >> choice;
        if (choice >= 0 && choice <= 11) {
            return static_cast<Expressions>(choice);
        }
        else {
            cout << "�߸��� �����Դϴ�! �ٽ� �������ּ���." << endl;
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
                cout << "���α׷��� �����մϴ�." << endl;
                return 0;
            default:
                cout << "�߸��� �����Դϴ�! �ٽ� �������ּ���." << endl;
            }

        }
        catch (const EmptyStackException& e) {
            cout << "���� empty ���� : " << e.what() << endl;
        }
        catch (const OverflowStackException& e) {
            cout << "���� overflow ����: " << e.what() << endl;
        }
        catch (const std::runtime_error& e) {
            cout << "��Ÿ�� ����: " << e.what() << endl;
        }
        catch (...) {
            cout << "�� �� ���� ���ܰ� �߻��߽��ϴ�." << endl;
        }
    }
}
