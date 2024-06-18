#include <iostream>


template <typename T>
std::remove_reference_t<T>&& move(T&& x) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(x);
}



template <typename T>
T&& forward(std::remove_reference_t<T> & x) {
    return static_cast<T&&>(x);
}


// references qualifiers

struct Data
{
    Data(const std::string& s): data(s) {}

    std::string getData()& {
        std::cout << "&\n";
        return data;
    }
    std::string getData()&& {
        std::cout << "&&\n";
        return std::move(data);
    }

private:
    std::string data;

};

void f(Data&& x) {
    std::string data = x.getData(); // for lvalue
    std::string data1 = std::move(x).getData(); // for rvalue
}



int main()
{
    std::cout << "Hello World!\n";

    int a = 1;
    int& b = a;
    //int& c = 2;

    //int&& d = a;
    int&& e = 5;

    int& g = e;
    //int&& h = e;

    const int&& i = 5;
    const int&& j = (const int&&)(a);



    Data d("abc");
    f(std::move(d));
}