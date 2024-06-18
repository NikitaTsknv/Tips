#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
///////////////////////////////////////////////
#define SIZE_OF_BUFFER 10 // размер буфера
class RingBuffer
{
private:
    int* arr;  // массив-буфер
    int index;   // конец буфера
    int head;   // начало буфера

//---------------------------------------------
public:
    RingBuffer() // конструктор
    {
        head = index = 0;

        // создаём буфер заданного размера
        arr = new int[SIZE_OF_BUFFER];

        // заполняем буфер нулями*
        for (int i = 0; i < SIZE_OF_BUFFER; ++i)
            arr[i] = 0;
    }
    //---------------------------------------------
    ~RingBuffer() // деструктор
    {
        delete[] arr;
    }
    //---------------------------------------------
    void full() const // проверяем, полон ли буфер
    {
        if (index == SIZE_OF_BUFFER)
        {
            std::cout << "RingBuffer is full!\n";
            return;
        }
    }
    //---------------------------------------------
    void empty() const // проверяем, пуст ли буфер
    {
        if (index == 0)
        {
            std::cout << "RingBuffer is empty!\n";
            return;
        }
    }
    //---------------------------------------------
    void clean() // очищаем буфер
    {
        head = index = 0;
        for (int i = 0; i < SIZE_OF_BUFFER; ++i)
            arr[i] = 0;
        std::cout << "RingBuffer cleared!\n";
    }
    //---------------------------------------------
    void put(int value) // помещаем элемент в буфер
    {
        // проверяем, полон ли буфер
        this->full();
        // "зацикливаем" буфер
        if (index == SIZE_OF_BUFFER)
        {
            index = 0;
        }

        // помещаем значение в буфер
        arr[index] = value;
        // печатаем элемент
        std::cout << "Element is put = " << arr[index] << "\n";
        std::cout << "______________________________\n";
        std::cout << '\n';
        ++index;
    }
    //---------------------------------------------
    void get() // извлекаем элемент из буфера
    {
        // проверяем, пуст ли буфер
        this->empty();
        // "зацикливаем" буфер
        if (index == SIZE_OF_BUFFER)
        {
            index = 0;
        }

        // печатаем элемент
        std::cout << "Element is got = " << arr[index] << "\n";
        std::cout << "______________________________\n";
        std::cout << '\n';
        arr[index] = 0; // обнуляем элемент буфера*
        ++index;
    }
    //---------------------------------------------
    void printQueue() const // печатаем буфер
    {
        int i;

        // проверяем, пуст ли буфер
        this->empty();

        std::cout << "Queue is: ";

        // если элементы в буфере идут по порядку
        if (index > head)
        {
            for (i = head; i < index; ++i)
                std::cout << arr[i] << ' ';
        }

        // если буфер уже "зациклен"
        else
        {
            // выводим часть от головы
            for (i = head; i < SIZE_OF_BUFFER; ++i)
                std::cout << arr[i] << ' ';

            // выводим часть до хвоста
            for (i = 0; i < index; ++i)
                std::cout << arr[i] << ' ';
        }
        std::cout << '\n';

        // доп. информация
        //std::cout << "Count is: " << count << '\n';
        std::cout << "Head is: " << head << '\n';
        //std::cout << "Index is: " << index << '\n';
        std::cout << "______________________________\n";
        std::cout << '\n';

        // доп. информация
        //std::cout << "Length is: " << length << '\n';
        //std::cout << "Head is: " << head << '\n';
        //std::cout << "Tail is: " << tail << '\n';
    }
    //---------------------------------------------
    void printBuffer() const // печать всего массива*
    {
        // проверяем, пуст ли буфер
        this->empty();
        std::cout << "Index is: " << index << '\n';

        std::cout << "Buffer is: ";

        for (int i = 0; i < SIZE_OF_BUFFER; ++i)
        {
            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
        std::cout << "______________________________\n";
        std::cout << '\n';
    }
};
///////////////////////////////////////////////
int main()
{
    // создаём очередь, макс.длина = 10
    RingBuffer myRingBuffer;

    // Выводим первоначальный буфер
    myRingBuffer.printQueue();
    myRingBuffer.printBuffer();

    std::cout << "______________________________\n";

    srand(time(0)); // автоматическая рандомизация
    int r = 0;
    while (r != 1)
    {
        r = rand() % 100;
        myRingBuffer.put(r);
        myRingBuffer.printQueue();
        myRingBuffer.printBuffer();
    }
    myRingBuffer.get();
    myRingBuffer.printQueue();
    myRingBuffer.printBuffer();
    myRingBuffer.get();
    myRingBuffer.printQueue();
    myRingBuffer.printBuffer();
    myRingBuffer.get();
    myRingBuffer.printQueue();
    myRingBuffer.printBuffer();
    myRingBuffer.clean();

    return 0;
}