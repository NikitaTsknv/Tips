#include <iostream>
#include <vector>

int main()
{
	int x = 1;
	std::cout << &x << '\n'; // адрес x

	int* p = &x;
	*p = 2;
	std::cout << *p << '\n'; // разыменование p

	int** pp = &p;
	std::cout << pp << ' ' << &pp << '\n'; // адрес p и адрес pp

	std::vector<int> v = { 1,2,3,4,5 };

	int* p1 = &v[0];
	int* p2 = &v[1];
	//p1 += 1;
	std::cout << *p1 << '\n';
	std::cout << (p1-p2) << '\n';

	/*Memory reuse*/
	int a = 10;
	int* pa = &a;
	{
		int b = 20;
		pa = &b;
	}
	std::cout << pa << '\n';
	std::cout << *pa << '\n'; // UB, bot most likely 2

	int c = 3, d = 4, e = 5, f = 6;
	std::cout << &c << ' ' << &d << ' ' << &e << ' ' << &f << '\n';

	++* pa; // still UB, and it's possible for one of c, d, e, f to be changed

	std::cout << c << ' ' << d << ' ' << e << ' ' << f << '\n'; // possibly something diferent from 3 4 5 6
	std::cout << *pa << '\n'; // possibly not 20 already

	int* p3 = new int(5);
	std::cout << *p3 << '\n';
	*p3 = 55;
	std::cout << *p3 << '\n';
	delete p3;
}