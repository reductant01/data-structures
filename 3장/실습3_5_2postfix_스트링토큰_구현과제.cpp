/*
* ������ ���� ����/�빮��, �����ڴ� >, >= ��� ����

*/
#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <vector>
#include <exception>

using namespace std;

//--- ����� ����: ������ ��� ���� ---//
class EmptyStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return " �� Stack.";
    }
};

//--- ����� ����: ������ ���� �� ---//
class OverflowStackException : public std::exception {
public:
    const char* what() const noexcept override {
        return "full Stack.";
    }
};

template <class T>
class Stack {
public:
    Stack(int stackCapacity = 4);
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



typedef vector<string> Expr;
typedef string Token;

int index = 0;
int inputData[26] = { 0 };

string NextToken(const string& e) {
  /*
  * ������: ==, != �� ó��
  * ������ ó���� best of best!!!
  */
}

bool isOperand(const string& x) {
    return (x.size() == 1 && isalpha(x[0]));
}

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
    return 9; // Not an operator
}

int icp(const string& a) { // ���ÿ� �ִ� �������� �켱������ ��ȯ
    if (a == "(") return 0;
    if (a == "!" || a == "-") return 1;
    if (a == "*" || a == "/" || a == "%") return 2;
    if (a == "+" || a == "-") return 3;
    if (a == "<" || a == ">" || a == "<=" || a == ">=") return 4;
    if (a == "==" || a == "!=") return 5;
    if (a == "&&") return 6;
    if (a == "||") return 7;
    return 9; // Not an operator
}

void stringAdd(Expr& ex, const string& str) { // ���ÿ� ������ �������� �켱������ ��ȯ
    ex.push_back(str);
}

Expr Postfix(const string& e) {
    Stack<string> stack(30);
    stack.Push("#");
    /*
    * �ö��� �Խ��� �˰��� ����
    */

}

void Eval(const Expr e) {
    /*
postfix expression e�� evaluate�Ѵ�.
��ū�� operator, operand �Ǵ� #�̰� ������ ��ū�� #�̴�.
�Լ� NextToken()�� e �κ��� ���� ��ū�� �����´�.
���� ���� ������ ������ inputData[] �迭 ���� ����Ͽ� ���� �´�.
*/
    
}

enum class Expressions {
    Exit, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11
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
    cout << "1:E1,2:E2,3:E3,4:E4,5:E5,6:E6,7:E7,8:E8,9:E9,10:E10,11:E11,0:Exit\n";
    cout << "��ȣ: ";
    cin >> choice;
    return static_cast<Expressions>(choice);
}

void toPostfix(const string& infixString) {
    cout << endl << "infix ǥ���� expression �Է�: " << infixString;
    /*
    * Postfix(infixString);
    * Eval(postfix);
    */
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
                return 0;
            }

        }
        catch (const EmptyStackException& e) {
            cout << "���� empty ���� : " << e.what() << endl;
        }
        catch (const OverflowStackException& e) {
            cout << "���� overflow ����: " << e.what() << endl;
        }
        catch (...) {
            cout << "An unknown exception occurred." << endl;
        }
    }
}