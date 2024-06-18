// Template metaprogramming, SFINAE idiom, compile-time computations

#include <iostream>
#include <vector>
#include <memory>


// SFINAE = subctitution failure is not an error

template <typename T>
auto f(const T& x) -> decltype(T().size()) {
    std::cout << 1 << "\n";
    return 1;

}

size_t f(...) {
    std::cout << 2 << "\n";
    return 2;
}


// check of method presence in a class

// decltype: value -> its type
// declval: type -> value of its type

// integral_constant, true_type and false_type

using std::declval;

template <typename T, T value_>
struct integral_constant {
    static const T value = value_;
};

struct true_type : public integral_constant<bool, true> {};
struct false_type : public integral_constant<bool, false> {};

template <typename T, typename... Args>
struct has_method_construct {
private:

    template <typename TT, typename... AArgs, typename = decltype(declval<TT>().construct(declval<AArgs>()...))>
    static true_type f(int);

    template <typename...>
    static false_type f(...);

public:
    //static const bool value = sizeof(f(0)) == sizeof(int);
    using type = decltype(f<T, Args...>(0));
};

template <typename T, typename... Args>
bool has_method_construct_v = std::is_same_v<typename has_method_construct<T, Args...>::type, true_type>;

template <typename T, typename... Args>
struct is_constructible {
private:

    template <typename TT, typename... AArgs,
        typename = decltype(TT(declval<AArgs>()...))>
        static true_type f(int);

    template <typename...>
    static false_type f(...);

public:
    static const bool value = decltype(f<T, Args...>(0))::value;
};

template <typename T, typename... Args>
bool is_constructible_v = is_constructible<T, Args...>::value;

template <typename T>
struct is_copy_constructible {
private:

    template <typename TT, 
                typename = decltype(TT(declval<const TT&>()))>
    static true_type f(int);

    template <typename...>
    static false_type f(...);

public:
    static const bool value = decltype(f<T>(0))::value;
};

template <typename T, typename... Args>
bool is_copy_constructible_v = is_copy_constructible<T, Args...>::value;

template <typename T>
struct is_nothrow_move_constructible {
private:

    template <typename TT,
        typename = enable_if_t<noexcept(TT(declval<TT>()))>>
        static true_type f(int);

    template <typename...>
    static false_type f(...);

public:
    static const bool value = decltype(f<T>(0))::value;
};

template <typename T, typename... Args>
bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T, Args...>
                        && noexcept(T(declval<T>()));


struct Test {

    void construct(int, int);
    void construct(double);
    void construct(const std::string&);

};


int main()
{
    std::cout << "Hello World!\n";

    std::vector<int> v{1, 2, 3};
    f(v);
    f(1);


    std::cout << has_method_construct_v<Test, int, int> << "\n";
    std::cout << has_method_construct_v<Test, int, int, int> << "\n";

    std::cout << is_constructible_v<std::string, int> << "\n";
    std::cout << is_constructible_v<std::string, int, char> << "\n";

    std::cout << is_copy_constructible_v<std::unique_ptr<int>> << "\n";

}