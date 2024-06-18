#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

struct MyCompare {
    bool operator()(int x, int y) const {
        return std::abs(x - 5) < std::abs(y - 5);
    }
};

auto get_compare() {
    return [](int x, int y) { return x * x < y* y; };
}


void test()
{
    std::cout << "Hello World!\n";

    std::vector<int> v{ 4,6,3,2,7,1,9,8 };
    // closure expression
    auto f = [](int x, int y) -> bool {
        if (x == y)
            return x + y;
        else
            return std::abs(x - 5) < std::abs(y - 5); 
    };

    //std::map<int, int, decltype(f)> m;

    std::cout << get_compare()(1, 2) << "\n";

    std::sort(v.begin(), v.end(), get_compare());

    [](int x) {
        std::cout << x << "\n";
    }(5);

    for (const auto& x : v) {
        std::cout << x << " ";
    }

}

namespace N {
    int a = 5;
}


// lambdas as functions

template <typename T>
void g(const T&) = delete;

struct V {
    int& a;

    V(int& a): a(a) {}

    void f() const {
        ++a;
    }
};

struct T {
    T() { std::cout << "created\n"; }
    T(const T&) { std::cout << "copied\n"; }
    T(T&&) { std::cout << "moved\n"; }
    ~T() { std::cout << "deleted\n"; }
};


// lambda_this

struct S {
    int a = 5 ;

    auto get_finction() {
        auto f = [this](int x) {
            std::cout << x + a << "\n";
        };
        return f;
    }
};


// defaut-capture and capture with initialization

struct S1 {
    int a = 5;

    auto get_finction(int i) {

        std::string s = "abcde";

        // since C++14
        auto f = [i, s = std::move(s)]() {
            std::cout << s[i] << "\n";
        };
        return f;
    }
};



int main()
{
    int a = 1;
    int b = 2;

    // a - захваченная переменная, по умолчанию она const; mutable - чтобы a не была const
    [&a, b](int x) mutable { // захват а по ссылке - int &
        std::cout << x + a << "\n";
        ++a;
    }(5);

    T t;

    auto f = [t](int x, int y) {
        return x < y;
    };

    auto ff = f;

    //decltype(f) ff; // since C++20

    //std::coutr << typeid(f).name();
    std::cout << sizeof(f);


    auto f1 = S().get_finction();
    std::cout << sizeof(f1);
    //f(5); // UB



    auto f2 = S1().get_finction(1);
    //f2(5); //UB


    {
        std::string s = "abcde";

        auto h = [&s](int i) { return s[i]; };

    }

    f2();


    // обобщенные лямбды

    std::vector<std::string> v{ "abc", "abcde" };
    std::sort(v.begin(), v.end(), [](const auto& x, const auto& y) { return x[0] < y[0]; });

}