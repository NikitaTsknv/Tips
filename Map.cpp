#include <iostream>
#include <map>

int main()
{
    setlocale(LC_ALL, "ru");
    using namespace std;

    map<string, int> ar;

    ar["do"] = 1;
    ar["to"] = 2;
    ar["dog"] = 3;
    ar["dogs"] = 4;
    ar["dogs"] = 6;

    for (auto& item : ar)
    {
        cout << item.first << endl;
    }

    for (auto& item : ar)
    {
        cout << item.second << endl;
    }

    ar.insert(pair<string, int>("do", 1));
    ar.insert(make_pair("dos", 3));
    
    ar.emplace("tos", 4);

    auto it = ar.erase("dos");

    auto it1 = ar.find("dos");

    for (auto& item : ar)
    {
        cout << item.first << endl;
    }

    for (auto& item : ar)
    {
        cout << item.second << endl;
    }

    return 0;
}