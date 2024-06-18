#include <utility>
#include <map>
#include <iomanip>
#include <iostream>
#include <conio.h>
#include <windows.h>

// тип fsttype совпадает с типом параметра шаблона A1, а тип sectype – A2;
// таким образом, на практике A1 может соответствовать имени поля,
// а A2 – его значению
// 
// все члены типа pair являются открытыми - объявлены как struct, а не как class

/*template <class A1, class A2>
struct pair
{
	using fsttype = A1;
	using sectype = A2;
	fsttype first;                            // 1-ый элемент пары fst имеет тип A1
	sectype second;                           // 2-ой элемент пары sec – A2

    // конструктор по умолчанию - инициализирует 1-ый элемент пары как тип по умолчанию A1, а 2-ой элемент – как A2

    pair();

    // конструктор инициализирует 1-ый элемент пары как v1, а 2-ой элемент - как v2

    pair(const fsttype& v1, const sectype& v2);

};*/

template <class T1, class T2>
struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;
	T1 first;
	T2 second;
	constexpr pair();
	pair(const pair&) = default;
	pair(pair&&) = default;
	constexpr pair(
		const T1& Val1,
		const T2& Val2);

	template <class Other1, class Other2>
	constexpr pair(const pair<Other1, Other2>& Right);

	template <class Other1, class Other2>
	constexpr pair(Other1&& Val1, Other2&& Val2);

	pair& operator=(const pair& p);
	template<class U1, class U2> pair& operator=(const pair<U1, U2>& p);
	pair& operator=(pair&& p) noexcept(see below);
	template<class U1, class U2> pair& operator=(pair<U1, U2>&& p);

	void swap(pair& p) noexcept(see below);
};

int main()
{
	pair<int, double> p1(10, 0.011);		// через конструктор инициализируем пару
						  // p1, в которой 1-ый элемент имеет целый тип, а 2-ой – действительный двойной точности

	auto p2 = std::make_pair(10, 0.222);

	pair<int, double> p3(p1); // инициализация пары p3, как копии уже созданной p1

	std::cout.precision(3); // назначаем точность вывода действительных чисел

	// проверяем результаты работы выводом на устройство вывода по умолчанию

	std::cout << "Пара p1 состоит из элементов : ( " << p1.first << ", " << p1.second << " )" << std::endl;
	std::cout << "- p2 : ( " << p2.first << ", " << p2.second << " )" << std::endl;
	std::cout << "- p3 : ( " << p3.first << ", " << p3.second << " )" << std::endl;

	// пример более сложного применения pair, когда структура представляет собой
	// массив пар, оба элемента в которой целые числа (на примере карты памяти)

	std::map<int, int> mydb;			// это наша база данных, как карта памяти
	std::map<int, int> ::iterator mydbindex;

	using mypair = pair<int, int>;		// определяет тип пары mypair, в которой каждые 2 элемента – целые числа
	
	mydb.insert(std::make_pair(1, 10));		// одновременно, через конструкторn создаётся пара,
						  // её элементам присваиваются значения 1 и 10 и она вставляется в базу
						  // Внимание! Предполагается, что функция вставки insert() реализована в базе map
	mydb.insert(std::pair<int, int>(2, 20));
	mydb.insert(mypair(3, 30));		// после данной вставки в базе уже 3 пары элементов

	std::cout << "База mydb состоит из следующих элементов : ";

	// просматриваем всю базу через её индекс, получая 3 пары в формате «(число, число)»
	// Внимание! Предполагается, что функции begin() и end() в базе реализованы

	for (mydbindex = mydb.begin(); mydbindex != mydb.end(); mydbindex++)
		std::cout << "(" << mydbindex->first << ", " << mydbindex->second << ")";

	// Внимание! Обратите внимание на следующее объявление!
	// Создаются две пары res1 и res2, как результат вставки нового элемента в базу mydb
	// 1-ое поле каждой пары индексом на вставленную позицию в пару, а
	// 2-ое отвечает за результат вставки – успешна/неуспешна – тип логический

	pair<std::map <int, int> ::iterator, bool> res1, res2;

	res1 = mydb.insert(mypair(4, 40));	// помимо собственно вставки в базу пары 4 и 40 
						  // insert() выдаёт true или false в случае успеха или неуспеха операции
	res2 = mydb.insert(mypair(1, 10));

	if (res1.second == true)
	{
		std::cout << "Пара (4, 40) успешно вставлена в базу" << std::endl;
	}
	else {
		std::cout << "Пара с ключевым первым элементом " << " ( (res1.fst) -> fst ) = "
			<< (res1.first)->first
			<< " уже есть в базе, вставка невозможна" << std::endl;
	}

	if (res2.second == true)
	{
		std::cout << "Пара (1, 10) успешно вставлена в базу" << std::endl;
	}
	else {
		std::cout << "Пара с ключевым первым элементом " << " ( (res2.fst) -> fst ) = "
			<< (res2.first)->first
			<< " уже есть в базе, вставка невозможна" << std::endl;
	}
	getch();
}