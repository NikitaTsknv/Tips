#include <iostream>
#include <cstring>
#include <vector>

// Constructors and destructors

// Assigment operator and 'The rule of three'

// Operators overloading

struct S {
    int& x;
    const double d = 0.0;
    const std::string& s;

    S(int& y, double dd): x(y), d(dd), s("abc") {}
};

class Complex {
public:
    double re = 0.0;
    double im = 0.0;
public:
    Complex(){} // default constructor
    
    /*Complex(double re, double im) {
        this->re = re;
        this->im = im;
    }*/
    Complex(double re_, double im_): re(re_), im(im_) {}
};

class String {
    char* arr;
    size_t sz;
    size_t cap;

public:
    String(size_t n, char c): arr(new char[n]), sz(n), cap(n) {
        memset(arr, c, n);
    }

    //deep copy
    /*String(const String& s) : arr(new char[s.cap]), sz(s.sz), cap(s.cap) {
        memcpy(arr, s.arr, sz);
    }*/

    //delegating constructor (since c++11)
    String(const String& s) :String(s.sz, '\0') {
        memcpy(arr, s.arr, sz);
    }

    String(std::initializer_list<char> lst)
            : arr(new char[lst.size()])
            , sz(lst.size())
            , cap(lst.size())
    {
        std::copy(lst.begin(), lst.end(), arr);
    }
    
    /*String& operator=(const String& s) {
        if (this == &s) return *this;

        delete[] arr;

        arr = new char[s.cap];
        sz = s.sz;
        cap = s.cap;

        memcpy(arr, s.arr, sz);
        
        return *this;
    }*/

    String& operator=(String s) {
        swap(s);
        return *this;
    }

    ~String() {
        delete[] arr;
    }

    void swap(String& s) {
        std::swap(arr, s.arr);
        std::swap(sz, s.sz);
        std::swap(cap, s.cap);
    }
};

class BigInteger {
    std::vector<int> digits;

public:
    //Arithmetic operators
    /*BigInteger operator+(const BigInteger& another) {
        BigInteger sum = *this;
        sum += another;
        return sum;
    }*/

    /*BigInteger operator-() {
        return 0 - *this;
    }*/

    BigInteger& operator+=(const BigInteger& another) {
        // ...
        return *this;
    }

    /*BigInteger& operator++() { // prefix increment
        return *this += 1;
    }*/

    /*BigInteger& operator++(int) { // postfix increment
        BigInteger copy = *this;
        ++*this;
        return copy;
    }*/
};
BigInteger operator+(BigInteger first, const BigInteger& second) {
    first += second;
    return first;
}
BigInteger operator+(BigInteger first, const BigInteger& second) {
    first += second;
    return first;
}
bool operator<(const BigInteger& first, const BigInteger& second) {
    // ...
    return true;
}
bool operator>=(const BigInteger& first, const BigInteger& second) {
    return !(first < second);
}
bool operator>(const BigInteger& first, const BigInteger& second) {
    return first < second;
}
bool operator==(const BigInteger& first, const BigInteger& second) {
    return !(first < second || second < first);
}

int main()
{
    std::cout << "Hello World!\n";
}