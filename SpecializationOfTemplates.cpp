#include <iostream>
#include <vector>

// specialization of templates

// non-type template parametrs

// basic compile-time computations

// dependent names

// basic type traits(характеристики)

// variadic templates (since c++11)

// fold expressions (выражения свертки) (since c++17)

struct St {
    template <typename T>
    St(T&);

    St(const St&);
};

template <typename T>
struct Vector {
    T* arr;
    size_t sz;
    size_t cap;
};

template <> // specialization
struct Vector<bool> {
    // ...
};

template <typename T, typename U>
void f(T, U) {
    std::cout << "1\n";
}

template <typename T>
void f(T, T) {
    std::cout << "2\n";
}

template <>
void f(int, int) {
    std::cout << "3\n";
}

template <int N>
void f(int x) {
    std::cout << x+N << "\n";
}

template <typename T, size_t N> // non-type template parametrs
class Array {
    T arr[N];
};

template <template <typename T, typename> class Container>
class Stack {
};

template <int N> // basic compile-time computations
struct Fibonacci {
    static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;

};

template <>
struct Fibonacci<0> {
    static const int value = 0;
};

template <>
struct Fibonacci<1> {
    static const int value = 1;
};


template <typename T> // dependent names
struct S {

    template <int N>
    using A = std::array<int, N>;
};

template <typename T>
struct S<T*> {
    static const int A = 0;
};

//int x = 0;

template <typename T>
void f() {
    /*typename S<T>::A * x;*/
    typename S<T>::template A <5> x;
};


template <typename T> // basic type traits(характеристики)
struct is_pointer {
    static const bool value = 0;
};

template <typename T>
struct is_pointer<T*> {
    static const bool value = 1;
};

template <typename T>
const bool is_pointer_v = is_pointer<T>::value;

template <typename T>
void f1() {
    if constexpr (is_pointer_v<T>) { // constexpr - для проверки в compile time
        T x = nullptr;
    }
};

// since c++11
template <typename T, typename U> // basic type traits(характеристики)
struct is_same {
    static const bool value = 0;
};

template <typename T>
struct is_same<T, T> {
    static const bool value = 1;
};

// since c++17
template <typename T, typename U>
const bool is_same_v = is_same<T, U>::value;


template <typename T>
struct remove_reference {
    using type = T;
};

template <typename T>
struct remove_reference<T&> {
    using type = T;
};

template <typename T>
void f2() {
    typename remove_reference<T>::type x = 3.14;
};


template <bool B, typename T, typename F>
struct conditional {
    using type = F;
};

template <typename T, typename F>
struct conditional<true, T, F> {
    using type = T;
};

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

/*template <typename T>
void f3() {
    typename conditional_t<is_const_v<T>, int, double>::type x = 0;
};*/ // в методе ошибка


/*template <typename ... Ts>
void print(Ts... args) {

}*/ // variadic templates

void print() {}

template <typename Head, typename ... Tail>
void print(const Head& head, const Tail& ... tail) {
    std::cout << head << ' ';
    print(tail...);
}

template <typename Head, typename... Tail> // variadic templates (since c++11)
void print1(const Head& head, const Tail&... tail) {
    std::cout << head << ' ' << sizeof...(tail) << ' ';
    /*if constexpr (sizeof...(tail) > 0) {
        print(tail...);
    }*/ // since c++17
}

template <typename T>
T sum(const T& x) {
    return x;
}

template <typename Head, typename... Tail>
auto sum(const Head& head, const Tail&... tail) {
    //std::cout << head << ' ';
    //static_assert(std::is_same_v<Head, int>); // since c++17
    return head + sum(tail...);
}


/*template <typename... Tail> // fold expressions (выражения свертки)
auto sum1(const Types&... types) {
    return (types + ...);
}*/ // since c++17

/*template <typename... Types> // fold expressions (выражения свертки)
auto print1(const Types&... types) {
    ((std::cout << types << ' '), ...);
    (std::cout << ... << types);
}*/ // since c++17

/*template <int... Numbers>
struct Check {
    static_assert((Numbers + ...) == 10);
};*/ // since c++17


int main()
{
    std::cout << "Hello World!\n";

    f<2>(1);

    Stack<std::vector> s;

    std::cout << Fibonacci<10>::value << "\n";

    //f<int*>();

    f1<std::string>();
    f1<double>();

    f2<double&>();


    print(1, 2, "abc", 3.0);


    print1(1, 2, "abc", 1.0);

    std::cout << sum(1, 2, 3, 4);


    //std::cout << sum1(1, 2, 3, 4);

    //Check<1, 2, 3, 4>();


}