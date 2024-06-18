#include <iostream>


// Vocabulary types and type erase idiom

// pair, tuple, variant, any, optional

// unions

struct S {
    int i;
    double d;
    std::string s;
};

template <typename T> // inion может быть и шаблонным
union U {
    int i;
    double d;
    T s;

    U() {}
    ~U() {}
};

int main()
{
    std::cout << "Hello World!\n";

    std::cout << sizeof(S) << "\n";

    // active union member
    U<std::string> u;
    new (&u.s) std::string("abc");
}