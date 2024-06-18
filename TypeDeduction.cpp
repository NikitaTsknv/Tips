#include <iostream>
#include <unordered_map>

/*Различие между decltype и auto сводится к типу возвращаемого значения: 
результат использования auto теряет квалификаторы типов const и &, 
а результат использования decltype сохраняет их для дальнейшей работы*/

// auto keyword

template <typename T, typename U>
auto&& f(const T& x, const U& y) {
    return x < y ? x : y;
}


// decltype (declared type объявленный)

template <typename Container>
decltype(auto) get_at(Container& container, size_t index) {
//auto get_at(Container& container, size_t index) -> decltype(container[index]) {
    // some additional work
    return container[index];
}


template <typename T>
class C {
    C() = delete;
};


struct S {
    int x = 0;
    std::string s = "abc";
};


// std::common_type implementation (общий тип)

// decltype: expression -> its type
// declval: type -> expression of this type

template <typename T>
std::add_lvalue_reference_t<T> declval() noexcept;

template <typename Head, typename... Tail>
struct common_type {
    using type = typename common_type<Head, typename common_type<Tail...>::type>::type;
};

template <typename T, typename U>
struct common_type<T, U> {
    using type = decltype(true ? T() : U());
};

template <typename... Types>
using common_type_t = typename common_type<Types...>::type;



int main()
{
    std::cout << "Hello World!\n";

    int y = 0;
    auto&& x = y;
    //const auto&& x = y;

    f('a', 5);


    int a = 5;
    int& r = a;
    decltype(r) b = a;


    decltype(a)* c = &a;

    // decltype(expr)
    // if expr is lvalue of type T, then decltype returns T&
    // if expr is prvalue of type T, then decltype returns T
    // if expr is xvalue of type T, then decltype returns T&&

    std::cout << a << " " << c << "\n";


    //C<decltype((x))>();

    std::cout << x << ' ' << y;
    
    // structured binding (since c++17)

    std::pair<int, std::string> p{ 2, "ab" };
    int mas[3] = { 1,2,3 };
    S s;
    //auto& [m, n] = s;



}