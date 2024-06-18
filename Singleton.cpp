#include <iostream>
#include <vector>
#include <set>
#include <string>

// Static fields and methods

// Functional objects and ()-overloading

// User-defined type conversions

// Singleton - pattern
class Singleton {
private:
    Singleton() {

    }
    Singleton(const Singleton&) = delete; // запрет конструктора копирования
    static Singleton* ptr;

    ~Singleton() {}

public:
    static Singleton& getInstance() {
        if (!ptr) ptr = new Singleton();
        return *ptr;
    }

};

Singleton* Singleton::ptr = nullptr;

struct S {
    static int count;

    S() {
        ++count;
    }

    ~S() {
        --count;
    }
};

int S::count = 0;

struct Less { // less -  меньше
    bool operator()(const std::string& a, const std::string& b) const {
        return a < b;
    }

};

struct C {
    int x;

    // explicit - запрет быть неявным
    explicit operator int() const {
        return x;
    }
};

int main()
{
    S s;
    std::cout << S::count << "\n";

    Singleton& si = Singleton::getInstance();

    Less less;
    std::cout << less("abcde", "abcd") << "\n";

    std::set<std::string, Less> set;

    C c;

    int x(c);
    static_cast<int>(c) + 5;

    std::cout << "Hello World!\n";
}