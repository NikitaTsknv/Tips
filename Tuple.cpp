#include <vector>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <tuple>
#include <string>

using namespace std;

/*class Tuple {
    Tuple();
    explicit Tuple(P1, P2, ..., PN); // 0 < N
    Tuple(const Tuple&);
    template <class U1, class U2, ..., class UN>
    Tuple(const Tuple<U1, U2, ..., UN>&);
    template <class U1, class U2>
    Tuple(const pair<U1, U2>&); // N == 2

    void swap(Tuple& right);
    Tuple& operator=(const Tuple&);
    template <class U1, class U2, ..., class UN>
    Tuple& operator=(const tuple<U1, U2, ..., UN>&);
    template <class U1, class U2>
    Tuple& operator=(const pair<U1, U2>&); // N == 2
};*/

typedef tuple <int, double, string> ids;

void print_ids(const ids& i)
{
    cout << "( "
        << get<0>(i) << ", "
        << get<1>(i) << ", "
        << get<2>(i) << " )." << endl;
}

// для вывода элементов кортежа, но с С++17
template <typename TupleT, std::size_t... Is>
std::ostream& printTupleImp(std::ostream& os, const TupleT& tp, std::index_sequence<Is...>) {
    auto printElem = [&os](const auto& x, size_t id) {
        if (id > 0)
            os << ", ";
        os << id << ": " << x;
    };

    os << "(";
    (printElem(std::get<Is>(tp), Is), ...);
    os << ")";
    return os;
}

template <typename TupleT, std::size_t TupSize = std::tuple_size<TupleT>::value>
std::ostream& operator <<(std::ostream& os, const TupleT& tp) {
    return printTupleImp(os, tp, std::make_index_sequence<TupSize>{});
}

int main()
{
    // Using the constructor to declare and initialize a tuple
    ids p1(10, 1.1e-2, "one");

    // Compare using the helper function to declare and initialize a tuple
    ids p2;
    p2 = make_tuple(10, 2.22e-1, "two");

    // Making a copy of a tuple
    ids p3(p1);

    cout.precision(3);
    cout << "The tuple p1 is: ( ";
    print_ids(p1);
    cout << "The tuple p2 is: ( ";
    print_ids(p2);
    cout << "The tuple p3 is: ( ";
    print_ids(p3);

    vector<ids> v;

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(make_tuple(3, 3.3e-2, "three"));

    cout << "The tuples in the vector are" << endl;
    for (vector<ids>::const_iterator i = v.begin(); i != v.end(); ++i)
    {
        print_ids(*i);
    }

    std::cout << "( " << std::get<0>(p1)
        << ", " << std::get<1>(p1)
        << ", " << std::get<2>(p1)
        << " )\n";

}