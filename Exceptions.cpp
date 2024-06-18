#include <iostream>

// exceptions

struct S {
    int x = 0;
    S() {
        std::cout << "S created\n";
    }
    S(const S&) {
        std::cout << "S copy\n";
    }
    ~S() {
        std::cout << "S destroyed\n";
    }
};

void f() {
    int x;
    std::cin >> x;
    if (x % 2) throw S();
}

struct Base {};
struct Derived: private Base {};

int main()
{
    std::cout << "Hello World!\n";

    try {
        Derived d;
        throw d;
    }
    catch (Base&) {
        std::cout << 1;
        return 0;
    }

    try {
        int* p = new int[1000000000];
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << &ex << '\n';
    }

    try {
        f();
    }
    catch (const S& s) {
        std::cout << "S catch\n";
    }
}