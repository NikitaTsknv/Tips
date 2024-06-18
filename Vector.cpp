#include <iostream>
#include <vector>

template <typename T, typename Alloc = std::allocator<T>>
class Vector {
private:
    T* arr;
    size_t sz;
    size_t cap;
    Alloc alloc;

    using AllocTraits = std::allocator_traits<Alloc>;

public:
    // size_t size() const;
    // size_t capacity() const;

    Vector(size_t count, const T& value, const Alloc& alloc = Alloc()) : alloc(alloc) {
        reserve(count);
        for (size_t i = 0; i < count; ++i) {
            AllocTraits::construct(alloc, arr + i, value);
        }
    }

    Vector(const Vector<T, Alloc>& v) : alloc(AllocTraits::select_on_container_copy_construction()) {
        // ...
    }

    Vector<T, Alloc>& operator=(const Vector<T, Alloc>& v) {
        for (size_t i = sz; i < sz; ++i) {
            AllocTraits::destroy(alloc, arr + i);
        }
        AllocTraits::deallocate(arr);

        if (AllocTraits::propagate_on_container_copy_assgnment::value && alloc != v.alloc) {
            alloc = v.alloc;
        }

        try {
            reserve(v.sz);
            for (size_t i = 0; i < v.sz; ++i) {
                AllocTraits::construct(alloc, arr + i, v[i]);
            }
        }
        catch (...) {

        }
    }

    void reserve(size_t n) {
        if (n <= cap) return;
        T* newarr = AllocTraits::allocate(alloc, n);
        //T* newarr = reinterpret_cast<T*>(new uint8_t[n * sizeof(T)]);
        //T* newarr = new T[n];
        size_t i = 0;
        try {
            for (i = 0; i < sz; ++i) {
                AllocTraits::construct(alloc, newarr + i, std::move(arr[i]));
            }
            //std::uninitialized_copy(arr, arr + sz, newarr);
        }
        catch (...) {
            for (size_t j = 0; j < i.sz; ++j) {
                AllocTraits::destroy(alloc, newarr + j);
            }
            AllocTraits::deallocate(alloc, newarr, n);
            //delete[] reinterpret_cast<uint8_t*>(arr);
            throw;
        }
        /*try {
            for (; i < sz; ++i) {
                new (newarr + i) T(arr[i]); // placement new
                //newarr[i] = arr[i];
            }
        }
        catch (...) {
            for (size_t j = 0; j < i; ++j) {
                (newarr + i)->~T();
            }
            delete[] reinterpret_cast<uint8_t*>(arr);
            throw;
        }*/
        for (size_t i = 0; i < sz; ++i) {
            alloc.destroy(arr + i);
            //(arr + i)->~T();
        }
        alloc.deallocate(arr);
        //delete[] reinterpret_cast<uint8_t*>(arr);
        arr = newarr;
        cap = n;
    }

    void resize(size_t n, const T& value = T()) {
        if (n > cap) reserve(n);
        for (size_t i = sz; i < n; ++i) {
            new (arr + i) T(value);
        }
        if (n < sz) {
            sz = n;
        }
    }

    void push_back(const T& value) {
        if (cap == sz) {
            reserve(2 * sz);
        }
        new (arr + sz) T(value);
        ++sz;
    }

    void pop_back() {
        --sz;
        (arr + sz)->~T();
    }

    T& operator [](size_t i) {
        return arr[i];
    }

    const T& operator [](size_t i) const {
        return arr[i];
    }

    T& at(size_t i) {
        if (i >= sz) {
            throw std::out_of_range("...");
        }
        return arr[i];
    }
};



// vector<bool>
template <>
class Vector<bool> {
    uint8_t* arr;
private:
    struct BitReference
    {
        uint8_t* bucket_ptr;
        uint8_t pos;

        BitReference& operator=(bool b) {
            if (b) {
                *bucket_ptr |= ((uint8_t)1 << pos);
            }
            else {
                *bucket_ptr &= ~((uint8_t)1 << pos);
            }
            return *this;
        }

        operator bool() const {
            return *bucket_ptr & ((uint8_t)1 << pos);
        }
    };
public:
    BitReference& operator[](size_t i) {
        uint8_t pos = i % 8;
        /*uint8_t* ptr = arr + i / 8;
        return BitReference(ptr, pos);*/
    }
};


int main()
{
    std::cout << "Hello World!\n";


}