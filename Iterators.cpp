#include <iostream>
#include <set>
#include <vector>

template <typename Iterator, typename IterCategory>
void my_advance_helper(Iterator& iter, int n, IterCategory) {
    for (int i = 0; i < n; ++i) {
        ++iter;
    }
}

template <typename Iterator>
void my_advance_helper(Iterator& iter, int n, std::random_access_iterator_tag) {
    iter += n;
}

template <typename Iterator>
void my_advance(Iterator& iter, int n) { 


    /*if constexpr (std::is_same_v<typename std::iterator_traits<Iterator>::iterator_category,
        std::random_access_iterator_tag>) {
        iter += n;
    }
    else {
        for (int i = 0; i < n; ++i) {
            ++iter;
        }
    }*/

    my_advance_helper(iter, n, 
        typename std::iterator_traits<Iterator>::iterator_category());

}


// const-, reverse- iterators

template <bool B, typename U, typename V>
struct conditional {
    using type = V;
};

template <typename U, typename V>
struct conditional<true, U, V> {
    using type = U;
};

template <bool B, typename U, typename V>
using conditional_t = typename conditional<B, U, V>::type;

template <typename Iterator>
class ReverseIterator {
    Iterator iter;

public:
    ReverseIterator<Iterator>& operator++() {
        --iter;
        return *this;
    }

    ReverseIterator<Iterator>& operator+=(int n) {
        iter -= n;
        return *this;
    }

    Iterator base() const {
        return iter;
    }
};

template <typename T>
class Vector {
    int sz;
    T* str;

private:

    template <bool IsConst>
    struct common_iterator {
    private:
        using ConditionalPtr = std::conditional_t<IsConst, const T*, T*>;
        
        ConditionalPtr* ptr;
    public:
        std::conditional_t<IsConst, const T*, T*> operator*() const {
            return *ptr;
        }

        std::conditional_t<IsConst, const T*, T*> operator->() {
            return ptr;
        }

        template <typename U>
        std::conditional_t<IsConst, const T*, T*> operator->*(U T::* p) {
            return (*ptr).*p;
        }

        common_iterator<IsConst>& operator+=(int n) {
            ptr += n;
            return *this;
        }

        common_iterator<IsConst> operator+(int n) const {
            auto copy = *this;
            copy += n;
            return copy;
        }
    };

public:
    using iterator = common_iterator<false>;
    using const_iterator = common_iterator<true>;

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
};


// output iterators
template <typename Container>
struct BackInsertIterator {
private:
    Container& container;

public:
    BackInsertIterator(Container& container): container(container) {}
    BackInsertIterator<Container>& operator++() {
        return *this;
    }

    BackInsertIterator<Container>& operator*() {
        return *this;
    }

    BackInsertIterator<Container>& operator=(const typename Container::value_type& value) {
        container.push_back(value);
        return *this;
    }
};

template <typename Container>
struct InsertIterator {
private:
    Container& container;
    //Container::iterator iter;

public:
    //InsertIterator(Container& container, Container::iterator iter) 
    //    : container(container), iter(iter) {}

    InsertIterator<Container>& operator++() {
        return *this;
    }

    InsertIterator<Container>& operator*() {
        return *this;
    }

    //InsertIterator<Container>&& operator=(const typename Container::value_type& value) {
    //    container.insert(iter, value);
    //    return *this;
    //}
};


// iostream iterators
template <typename T>
struct IstreamIterator {
private:
    std::istream& stream;
    T value;
public:
    IstreamIterator(std::istream& stream): stream(stream) {}

    IstreamIterator<T>& operator++() {
        stream >> value;
        return *this;
    }

    T& operator*() {
        return value;
    }
};

template <typename T>
struct OstreamIterator {
private:
    std::ostream& stream;
public:
    OstreamIterator(std::ostream& stream) : stream(stream) {}

    OstreamIterator<T>& operator++() {
        return *this;
    }

    OstreamIterator<T>& operator*() {
        return *this;
    }

    OstreamIterator<T>& operator=(const T& value) {
        stream << value;
        return *this;
    }

};

int main()
{
    std::cout << "Hello World!\n";

    std::set<int> s;
    for (int i = 0; i < 100; ++i) {
        s.insert(i);
    }

    std::set<int>::iterator it = s.begin();
    auto it2 = it;
    std::advance(it2, 25);
    //my_advance(it, 25);
    //std::cout << *it;
    auto it3 = it2;
    std::advance(it3, -10);
    //my_advance(it, 25);
    //std::cout << *it;
    std::cout << std::distance(it3, it2);

    std::vector<int> v(10);
    for (auto it = v.rbegin(); it != v.rend(); ++it) {}

    std::vector<int> v1(10);
    for (int i = 0; i < 10; ++i) {
        v[i] = i;
    }
    std::vector<int> vv1;
    //std::copy(v1.begin(), v1.end(), vv1.begin());

}