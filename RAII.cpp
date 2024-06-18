#include <iostream>
#include <deque>

// RAII idiom, exceptions in conctructors and destructors

int g(int* p) {
    if (*p == 0)
        throw std::runtime_error("Boom!");
    return 3;
}

template <typename T>
struct SmartPtr {
    T* p;
    SmartPtr(T* p) : p(p) {}
    ~SmartPtr() { delete p; }
};

int f(int x) {
    //int* p = new int(x);
    SmartPtr<int> p(new int(x));
    
    int ans = g(p.p);
    return ans;
}


struct Exceptional {
    int* p;
    Exceptional(int x): p(new int (x)) {
        if (x == 0) throw std::runtime_error("Boom!");
    }

    ~Exceptional() {
        delete p;
    }
};

int f1(int x) {
    Exceptional ex(x);
    return x;
}


template <typename T>
class Vector {

    T* begin_;
    T* end_;
    T* buff_end_;

public:
    //T& operator[](size_t index) noexcept(noexcept(f<T>()));

    size_t size() const noexcept {
        return end_ - begin_;
    }

    size_t capacity() const noexcept {
        return buff_end_ - begin_;
    }

    Vector(size_t count, const T& value = T())
        : begin_(reinterpret_cast<T*>(new char[count * sizeof(T)]))
        , end_(begin_ + count)
        , buff_end_(begin_ + count) {

        T* it = begin_;
        try {
            for (T* it = begin_; it != end_; ++it) {
                //*it = value; // UB

                new (it) T(value);
            }
        }
        catch (...) {
            for (T* delit = begin_; delit != end_; ++delit) {
                delit->~T();
            }
            delete[] reinterpret_cast<T*>(begin_);
            throw;
        }
    }

    void reserve(size_t newcap) {
        if (capacity() >= newcap) return;

        T* newarr_ = reinterpret_cast<T*>(new char[newcap * sizeof(T)]);

        size_t i = 0;
        try {
            for (; i < size(); ++i) {
                new (newarr_ + i) T(begin_[i]);
            }
        }
        catch (...) {
            for (size_t j = 0; j < i; ++j) {
                (newarr_ + j)->~T();
            }
            delete[] reinterpret_cast<char*>(newarr_);
            throw;
        }

        for (T* delit = begin_; delit != end_; ++delit) {
            delit->~T();
        }
        delete[] reinterpret_cast<char*>(begin_);
    }

    void push_back(const T& value) {
        if (end_ == buff_end_) {
            reserve(std::max(1, 2 * capacity()));
        }

        new(end_) T(value);
        ++end_;
    }
};

template<>
class Vector<bool> {
    char* arr_;
    size_t sz;
    size_t cap;

private:
    struct BoolReference {
        char* chunk;
        uint8_t bit;

        BoolReference operator=(bool b) {
            if (b) {
                *chunk |= 1 << bit;
            }
            else {
                *chunk |= ~(1 << bit);
            }
            return *this;
        }

        operator bool() const {
            return *chunk & (1 << bit);
        }
    };

public:
    BoolReference operator[](size_t index) {
        return BoolReference{ arr_ + (index >> 3), index & 7 };
    }
};



int main()
{
    std::cout << "Hello World!\n";

    f(1);

    f1(0);

    /*Vector<bool> v(5);
    v[3] = true;

    std::deque<int> v(10);

    int& x = v[5];
    v.push_back(1);*/
}