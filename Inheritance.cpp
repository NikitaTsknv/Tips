#include <iostream>
#include <vector>
#include <string>

// Constructors and destructors in case of inheritance

// Empty based optimization (EBO)

// Virtual inheritance

struct Base {
    int x = 0;
    std::vector<int> v;
    void f(double) {
        std::cout << 1 << std::endl;

    }

    //Base() { std::cout << "C_B" << std::endl; }
    Base(int x): x(x) { std::cout << "C_B" << std::endl; }
    ~Base() { std::cout << "D_B" << std::endl; }
};

struct Derived: public Base {
    int x = 1;
    std::string str;
    double d = 3.14;
    using Base::Base;

    void f(int) {
        std::cout << 2 << std::endl;

    }

    //Derived() { std::cout << "C_D" << std::endl; }
    Derived(int x, double d): Base(x), d(d) { std::cout << "C_D" << std::endl; }
    ~Derived() { std::cout << "D_D" << std::endl; }
};

struct Empty{};

struct EmptyDerived: Empty{};

struct Granny {
    int g;
};

struct Mom: virtual public Granny {
    int m;
};

struct Dad: virtual public Granny {
    int d;
};

struct Son: Mom, Dad {
    int s;
};

int main()
{
    Derived d(1, 2.5);
    std::cout << d.x << "\n";
    d.f(3.14);

    std::cout << sizeof(Empty) << "\n";
    std::cout << sizeof(EmptyDerived) << "\n";

    Son ss;
    std::cout << sizeof(ss) << "\n";
    std::cout << &ss << " " << &ss.m << " " << &ss.d << " " << &ss.g << " " << &ss.s << "\n";

    Dad dd;
    static_cast<Son&>(dd);

    std::cout << (int*&)ss << "\n";
}