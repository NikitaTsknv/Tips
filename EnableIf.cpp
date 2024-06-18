#include <iostream>

template <bool B, typename T = void>
struct enable_if {

};

template <typename T>
struct enable_if<true, T> {
    using type = T;
};

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <typename T, typename = std::enable_if<std::is_class_v<T>>>
void f(const T&) {
    std::cout << 1;
}

void f(...) {
    std::cout << 2;
}


int main()
{
    std::cout << "Hello World!\n";

    std::string s("abc");

    f(s);
    f(1);
}
