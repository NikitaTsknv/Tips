#include <iostream>
#include <vector>
#include <scoped_allocator>

// allocators

template<typename T>
class MyAllocator: public std::allocator<T> {
public:
    MyAllocator() {}

    template<typename U>
    MyAllocator(const MyAllocator<U>&) {}

    T* allocate(size_t count) const {
        std::cout << "allocated\n";
        return ::operator new(count * sizeof(T));
    }

    void deallocate(T* ptr, size_t /*count*/) {
        std::cout << "deallocated\n";
        ::operator delete(ptr);
    }

    template <typename... Args>
    void construct(T* ptr, const Args&... args) {
        new(ptr) T(args...);
    }

    void destroy(T* ptr) {
        ptr->~T();
    }
};


// scoped allocators

template <typename OuterAlloc, typename... InnerAlloc>
struct scoped_allocator_adaptor: public OuterAlloc {
private:
    scoped_allocator_adaptor<InnerAlloc...> inner_alloc;
public:

    template<typename T, typename... Args>
    void construct(T* ptr, const Args&... args) {
        if (1/* elements of type T can be created with instance of InnerAlloc */) {
            new(ptr) T(args..., inner_alloc);
        }
        else {
            new(ptr) T(args...);
        }
    }
};


int main()
{
    std::cout << "Hello World!\n";

    /*using MyString = std::basic_string<char, std::char_traits<char>, MyAllocator<char>>;
    std::vector<MyString, MyAllocator<MyString>> v;
    v.push_back(MyString("abc"));*/

    using MyVector = std::vector<int, MyAllocator<int>>;

    MyAllocator<MyVector> outer_alloc;
    MyAllocator<int> inner_allocl(outer_alloc);

    std::vector<MyVector, std::scoped_allocator_adaptor<MyAllocator<MyVector>>> v(outer_alloc);
    //std::vector<MyVector, MyAllocator<MyVector>> v(outer_alloc);
    //std::vector<MyVector, MyAllocator<int>> v;
    
    v.push_back(MyVector(5));


}
