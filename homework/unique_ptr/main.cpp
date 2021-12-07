#include "my_unique_ptr.h"
#include <iostream>
#include <cassert>

struct test {
public:
    test(){
        std::cout << "test()\n";
    }
    test(int value): value(value) {
        std::cout << "test(" << value << ")\n";
    }
    ~test(){
        std::cout << "~test()\n";
    }

    auto getValue() {
        return value;
    }

    friend std::ostream& operator<<(std::ostream& os, const test& t);
private:
    int value = 0;
};

std::ostream& operator<<(std::ostream& os, const test& t) {
    os << "print " << t.value;
    return os;
}

int main(){
    std::cout << "create pointer\n";
    auto ptr = my_unique_ptr<test>(new test{10});
    std::cout << "get() =      " << ptr.get() << '\n';
    std::cout << "* =          " << *ptr << '\n';
    std::cout << "getValue() = " << ptr->getValue() << '\n';

    std::cout << "\nreset to new pointer\n";
    ptr.reset(new test{20});
    std::cout << "get() =      " << ptr.get() << '\n';
    std::cout << "* =          " << *ptr << '\n';
    std::cout << "getValue() = " << ptr->getValue() << '\n';

    std::cout << "\nmove to other smart pointer\n";
    auto ptr2 = std::move(ptr);
    assert(ptr.get() == nullptr);
    std::cout << "get() =      " << ptr2.get() << '\n';
    std::cout << "* =          " << *ptr2 << '\n';
    std::cout << "getValue() = " << ptr2->getValue() << '\n';

    {
        std::cout << "\nreset/release to other smart pointer\n";
        my_unique_ptr<test> ptr3;
        ptr3.reset(ptr2.release());
        std::cout << "get() =      " << ptr3.get() << '\n';
        std::cout << "* =          " << *ptr3 << '\n';
        std::cout << "getValue() = " << ptr3->getValue() << '\n';
    }

    std::cout << "\ncreate empty pointer\n";
    my_unique_ptr<test> ptr4;
    std::cout << "get() =      " << ptr4.get() << '\n';
    if (ptr4.get()) {
        std::cout << "* =          " << *ptr4 << '\n';
        std::cout << "getValue() = " << ptr4->getValue() << '\n';
    }
    
    return 0;
}
