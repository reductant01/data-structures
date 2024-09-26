#include <iostream>
#include <stack>
#include <deque> // std::deque ���
#include <vector>
#include <queue>

int main() {
    // int Ÿ���� ������ ���� ���� - ADAPTER
    std::stack<int, std::deque<int>> int_stack;

    // ���ÿ� ���� �߰�
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);

    // ���ÿ��� ���� ���� �� ���
    std::cout << "Stack elements:" << std::endl;
    while (!int_stack.empty()) {
        std::cout << int_stack.top() << " "; // ������ ���� ���� �ִ� ���� ���
        int_stack.pop(); // ���ÿ��� ���� ����
    }
    std::cout << std::endl;

    // std::vector�� ����ϴ� ���� ����
    std::stack<std::string, std::vector<std::string>> string_stack;

    // ���ÿ� ���ڿ� �߰�
    string_stack.push("Hello");
    string_stack.push("World");

    // ���ÿ��� ���ڿ� ���� �� ���
    std::cout << "String stack elements:" << std::endl;
    while (!string_stack.empty()) {
        std::cout << string_stack.top() << " "; // ������ ���� ���� �ִ� ���� ���
        string_stack.pop(); // ���ÿ��� ���� ����
    }
    std::cout << std::endl;
    //
    // 1. �⺻������ �ִ� ���� ����ϴ� priority_queue
    std::priority_queue<int> max_heap;

    // ��� �߰� (push)
    max_heap.push(10);
    max_heap.push(20);
    max_heap.push(5);

    // �ִ� �������� ���: ū ������� ��� (20, 10, 5)
    std::cout << "Max Heap (Priority Queue):" << std::endl;
    while (!max_heap.empty()) {
        std::cout << max_heap.top() << " "; // ���� ū ���� ���
        max_heap.pop(); // ���� ū ���� ����
    }
    std::cout << std::endl;

    // 2. �ּ� ���� ����Ϸ��� std::greater<T>�� ���
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

    // ��� �߰� (push)
    min_heap.push(10);
    min_heap.push(20);
    min_heap.push(5);

    // �ּ� �������� ���: ���� ������� ��� (5, 10, 20)
    std::cout << "Min Heap (Priority Queue):" << std::endl;
    while (!min_heap.empty()) {
        std::cout << min_heap.top() << " "; // ���� ���� ���� ���
        min_heap.pop(); // ���� ���� ���� ����
    }
    std::cout << std::endl;

    return 0;
}