//3.1�� STL
#include <iostream>
#include <list>
#include <memory> // std::allocator
template <typename T>
struct MyAllocator {
    using value_type = T;

    MyAllocator() = default;

    // �޸� �Ҵ�
    T* allocate(std::size_t n) {
        std::cout << "Allocating " << n << " elements" << std::endl;
        //:: scope resolution operator�̰� ���� ���� �������̴� 
        return static_cast<T*>(::operator new(n * sizeof(T)));//**static_cast<T*>**�� Ÿ�� ��ȯ ������. �Ҵ�� �޸𸮴� �Ϲ����� void* �����ͷ� ��ȯ�ǹǷ�, �̸� T* Ÿ������ ��ȯ
    }

    // �޸� ����
    void deallocate(T* p, std::size_t n) {
        std::cout << "Deallocating " << n << " elements" << std::endl;
        ::operator delete(p);
    }
};

int main() {
    // std::allocator<int>�� ����ϴ� std::list
    std::list<int, std::allocator<int>> my_list;

    // list�� �� �߰�
    my_list.push_back(10);
    my_list.push_back(20);

    // ����Ʈ ���
    for (const int& val : my_list) {
        std::cout << val << " ";
    }
    //
    // MyAllocator<int>�� ����ϴ� list
    std::list<int, MyAllocator<int>> my_list;

    my_list.push_back(1);
    my_list.push_back(2);

    for (const int& val : my_list) {
        std::cout << val << " ";
    }
    return 0;
}