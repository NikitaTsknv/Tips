#include <iostream>
#include <cstddef>

// alignments

struct alignas(16) S
{
    int x;
    double y;
    int z;
};

int main()
{
    std::cout << "Hello World!\n";

    std::cout << sizeof(S) << "\n";

    // since c++11
    std::cout << alignof(S) << "\n";

    std::cout << alignof(std::max_align_t) << "\n";

}
