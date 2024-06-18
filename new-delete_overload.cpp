// new/delete overloading

#include <iostream>
#include <cstdlib>
#include <vector>

/*void* operator new(size_t n) {
    std::cout << "allocated " << n << " bytes\n";
    return malloc(n);
}

void operator delete(void* ptr, size_t n) {
    std::cout << "deallocated " << n << " bytes\n";
    free(ptr);
}

void* operator new[](size_t n) {
    std::cout << "allocated array " << n << " bytes\n";
    return malloc(n);
}

void operator delete[](void* ptr) {
    std::cout << "deallocated array\n";
    free(ptr);
}*/

struct S {
    int x = 0;
    double d = 0.0;

    S() {
        throw 1;
    }

    /*static void* operator new(size_t n) {
        std::cout << "allocated " << n << " bytes\n";
        return malloc(n);
    }
    void operator delete(void* ptr) {
        std::cout << "deallocated\n";
        free(ptr);
    }*/
};

// placement new
/*void* operator new(size_t, void* ptr) {
    return ptr;
}

void* operator new(size_t n, std::nothrow_t) {
    return malloc(n);
}*/

struct mynew_t {};
mynew_t mytag;

void* operator new(size_t n, mynew_t) {
    return malloc(n);
}
void operator delete(void* ptr, mynew_t) {
    std::cout << "I am here\n";
    free(ptr);
}
int main()
{
    std::cout << "Hello World!\n";

    //int* p = new int[5];
    //delete[] p;

    //double* pd = new double(3.14);
    //delete pd;

    std::vector<int> v(5);
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }

    //S* s = new S();
    //delete s;

    //int* ptr = new(std::nothrow) int(5);

    try {
        S* ptr = new(mytag) S();
    }
    catch (...) {
        std::cout << "Catch\n";
    }
}