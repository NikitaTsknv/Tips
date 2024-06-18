#include <iostream>
#include <vector>

// move-semantics

// std::move() - function

// rvalue- references, move-operations

class String {
private:
    char* arr;
    size_t sz;
    size_t cap;

public:
    String(const String& s);

    // move-constructor
    String(String&& s): arr(std::move(s.arr)), sz(std::move(s.sz)), cap(std::move(s.cap)) {
        s.arr = nullptr;
        s.sz = 0;
        s.cap = 0;
    }

    // move-operator=
    String& operator=(String&& s) {
        String news(std::move(s));
        swap(news);
        return *this;
    }

    void swap(String& s) {
        // ...
        //String temp = s;

    }
};

struct S {
    std::vector<int> v;
    std::string s;
};

// problems
template <typename T>
void swap(T& x, T& y) {
    T t = std::move(x);
    x = std::move(y);
    y = std::move(t);
}

std::string f() {
    // ...
    return std::string("abcd");
}


struct S1 {
    S1() {
        std::cout << "Created!\n";
    }
    S1(const S1&) {
        std::cout << "Copy!\n";
    }
    S1(S1&&) noexcept {
        std::cout << "Move!\n";
    }
    ~S1() {
        std::cout << "Destroyed!\n";
    }
};

// move_if_noexcept
template <typename T>
std::conditional_t<noexcept(T(std::move(T()))), T&&, const T&> move_if_noexcept(T& x) noexcept {
    return std::move(x);
}


int main()
{
    std::cout << "Hello World!\n";


    std::vector<std::vector<std::string>> v;
    //v.push_back(std::string("abcdefg"));
    v.emplace_back(3, "abc");

    std::vector<std::string> v1;
    v1.push_back(std::move(f())); // since c++11 this is already correct


    S x;
    S y = std::move(x);


    std::vector<S1> v2;
    for (int i = 0; i < 10; ++i) {
        v2.push_back(S1());
        std::cout << "\n";
    }

    S1 s1;
    S1&& r = std::move_if_noexcept(s1);
    
}