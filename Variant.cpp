#include <iostream>
#include <variant>


// std::variant

template <size_t N, typename T, typename... Types>
struct get_index_by_type {
    static const size_t value = N;
};

template <size_t N, typename T, typename Head, typename... Tail>
struct get_index_by_type<N, T, Head, Tail...> {
    static const size_t value = std::is_same_v<T, Head> ? N
        : get_index_by_type<N+1, T, Tail...>::value;
};

template <typename... Types>
class Variant;

template <typename T, typename... Types>
struct VariantAlternative {


    // CRTP
    using Derived = Variant<Types...>;

    VariantAlternative(const T& value) {
        static_cast<Derived*>(this)->storage.put<sizeof...(Types)>(value);
    }

    VariantAlternative(T&& value) {
        static_cast<Derived*>(this)->storage.put<sizeof...(Types)>(std::move(value));
    }

    void destroy() {
        auto this_ptr = static_cast<Derived*>(this);
        if (get_index_by_type<0, T, Types...>::value == this_ptr->current) {
            // this_ptr->storage;
        }
    }
};

template <typename... Types>
class Variant: private VariantAlternative<Types, Types...>... {
private:

    template <typename... TTypes>
    union VariadicUnion {};

    template <typename Head, typename... Tail>
    union VariadicUnion<Head, Tail...> {
        Head head;
        VariadicUnion<Tail...> tail;

        template <size_t N, typename T>
        void put(const T& value) {
            if constexpr (N == 0) {
                new (&head) T(value);
            }
            else {
                tail.put<N - 1>(value);
            }
        }
    };

    VariadicUnion<Types...> storage;
    size_t current = 0;

public:

    // constructors
    //using VariantAlternative<Types, Types...>::VariadicAlternative...;

    ~Variant() {
        //(VariadicAlternative<Types, Types...>::destroy(), ...);
    }

    /*template <typename T>
    Variant(const T& value) {
        current = get_index_by_type<0, T, Types...>::value;
        storage.put<get_index_by_type<0, T, Types...>::value>(value);
    }*/

    size_t index() const {
        return current;
    }

    template <typename T>
    bool holds_alternative() const {
        return get_index_by_type<0, T, Types...>::value == current;
    }
};



struct S {
    const int x;
};

union U {
    S s;
    float f;
    U() {}
};

int main()
{
    std::cout << "Hello World!\n";

    /*std::variant<int, double, std::string> v = 1;
    v = "abc";
    std::cout << std::get<std::string>(v) << "\n";
    v = 5.0;
    std::cout << std::holds_alternative<int>(v) << "\n";
    std::cout << v.index() << "\n";*/


    U u;
    new(&u.s) S{ 1 };
    std::cout << u.s.x << "\n";
    new(&u.s) S{ 2 };
    std::cout << u.s.x << "\n"; // UB, maybe 1
    S* s = new S { 1 };
    new(s) S{ 2 };
    std::cout << std::undeclare_reachable(s)->x << "\n"; // UB, maybe 1

}