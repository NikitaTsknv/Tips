#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
    set<int> setA = { 1, 3, 4, 5, 7 };
    set<int> setB = { 0, 2, 3, 5, 4 };
    set<int> setC;

    set_intersection(setA.begin(), setA.end(),
        setB.begin(), setB.end(),
        inserter(setC, setC.begin()));
    for (auto& item : setC)
        cout << item << " ";
    cout << endl;
    setC.clear();

    set_union(setA.begin(), setA.end(),
        setB.begin(), setB.end(),
        inserter(setC, setC.begin()));
    for (auto& item : setC)
        cout << item << " ";
    cout << endl;
    setC.clear();

    set_difference(setA.begin(), setA.end(),
        setB.begin(), setB.end(),
        inserter(setC, setC.begin()));
    for (auto& item : setC)
        cout << item << " ";
    cout << endl;
    setC.clear();

    set_symmetric_difference(setA.begin(), setA.end(),
        setB.begin(), setB.end(),
        inserter(setC, setC.begin()));
    for (auto& item : setC)
        cout << item << " ";
    cout << endl;
    setC.clear();
}