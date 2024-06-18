#include <iostream>
#include <vector>

// virtual issues

// templates

struct Base {
    virtual void f() = 0;
    virtual void g() {
        std::cout << "1" << std::endl;
    }
    void h() {
        f();
    }
};

struct Derived: Base {
    virtual void f() override {
        std::cout << "Ok" << std::endl;
    }
    virtual void g() override {
        std::cout << "2" << std::endl;
    }
    Derived() { h(); }
};


int maxx(int x, int y) {
    return x > y ? x : y;
}
std::string maxx(const std::string& x, const std::string& y) {
    return x > y ? x : y;
}
template <typename T, typename U>
U maxx(const T& x, const U& y) {
    return x > y ? x : y;
}

template <class T>
class Vector {
private:
    T* arr;
    size_t sz;
    size_t cap;

    template <class B>
    void f(B);
};

template <class A>
template <class B>
void Vector<A>::f(B) {
    std::cout << "1\n";
}

template <typename T>
using Iter = typename std::vector<T>::iterator;

//template <typename T>
//const double pi = f<T>();

template <typename T>
void f(T x) {
    std::cout << "11\n";
}

void f(double x) {
    std::cout << "22\n";
}

template <typename T, typename U>
void g(T x) {
    std::cout << "33\n";
}

int main()
{
    std::cout << "Hello World!\n";

    Derived d;
    d.f();

    std::cout << maxx(1, 2.05) << "\n";


    std::vector<int> v;
    Iter<int> it = v.begin();

    g<int, double>(1);
}