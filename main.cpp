#include <iostream>
#include "SharedPtr.hpp"

int main() {
    int* intPtr = new int(4);
    Shared_Ptr<int> ptr(intPtr);
    std::cout << *ptr << std::endl;

    Shared_Ptr<int> ptr2(intPtr);
    ptr2 = ptr;
    std::cout << *ptr2 << std::endl;
    return 0;
}