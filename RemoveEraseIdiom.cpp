#include <iostream>
#include <vector>
#include <algorithm>


void print (const std::vector<int>& data)
{
    for(const auto& n: data)
    {
        std::cout << n << "\t";
    }
    std::cout << std::endl;
}

bool is_negative(int n){ return n < 0;}


int main()
{
    std::vector<int> numbers {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5}

    // применяем алгоритм remove_if() для удаления всех элементов, которые не соответствуют условию
    auto iter{ std::remove_if(begin(numbers), end(numbers), is_negative) };

    print(numbers);   // 0       1       2       3       4       5       1       2       3       4       5

    // удаляем все элементы, начиная с итератора first_to_erase
    numbers.erase(iter, end(numbers));

    print(numbers);   // 0       1       2       3       4       5
}
