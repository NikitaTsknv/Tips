#include <iostream>
#include <any>

// std::any since c++17

// Type etasure idiom

class Any {
private:
    struct Base {
        virtual Base* get_copy();
        virtual ~Base() {}
    };

    template <typename T>
    struct Derived : public Base {

        T value;

        Derived(const T& value): value(value) {}

        Base* get_copy() override {
            return new Derived<T>(value);
        }
    };

    Base* storage =  nullptr;

public:
    template <typename U>
    Any(const U& value): Derived<U>(value) {}

    ~Any() {
        delete storage;
    }

    Any(const Any& a): storage(a.storage->get_copy()) {}

    template <typename U>
    Any& operator=(const U& value) {
        delete storage;
        storage = new Derived<U>(value);
    }
};

int main()
{
    std::cout << "Hello World!\n";

    std::any a = 5;
    std::cout << a.type().name() << " " << std::any_cast<int>(a);
}
