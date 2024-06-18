#include <iostream>
#define SIZE 5

class Queue {
private:
    int items[SIZE], front, rear, size;

public:
    Queue() {
        front = -1; // начало
        rear = -1;  // конец
        size = 0;
    }

    bool isFull() {
        if (front == 0 && rear == SIZE - 1) {
            return true;
        }
        return false;
    }

    bool isEmpty() {
        if (front == -1)
            return true;
        else
            return false;
    }

    // добавить в конец очереди
    void enQueue(int element) {
        if (isFull()) {
            std::cout << "Queue is full";
        }
        else {
            if (front == -1) front = 0;
            rear++;
            size++;
            items[rear] = element;
            std::cout << std::endl
                << "Element added " << std::endl
                << "Queue size " << size << std::endl;
        }
    }

    // удалить с конца очереди
    void deQueue() {
        int element;
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        else {
            element = items[front];
            if (front >= rear) {
                front = -1;
                rear = -1;
            } /* Внутри Q только один элемент, поэтому очередь сбрасывается
              в начальное состояние после удаления последнего элемента */
            else {
                front++;
                size--;
            }
            std::cout << std::endl
                << "Element removed " << element << std::endl
                << "Queue size " << size << std::endl;
        }
    }

    void display() {
        /* Функция выводит в консоль элементы очереди */
        int i;
        if (isEmpty()) {
            std::cout << std::endl
                << "Queue is empty" << std::endl;
        }
        else {
            std::cout << std::endl
                << "Index FRONT -> " << front;
            std::cout << std::endl
                << "Elements: ";
            for (i = front; i <= rear; i++)
                std::cout << items[i] << "  ";
            std::cout << std::endl
                << "Index REAR-> " << rear << std::endl
                << "Queue size " << size << std::endl;
        }
    }
};

int main() {
    Queue q;

    // функцию deQueue нельзя применять к пустой очереди
    q.deQueue();

    // Добавляем 5 элементов
    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3);
    q.enQueue(4);
    q.enQueue(5);

    // Шестой элемент добавить нельзя — очередь заполнена
    q.enQueue(6);

    q.display();

    // Функция deQueue удаляет первый элемент — 1
    q.deQueue();

    // Теперь внутри очереди 4 элемента
    q.display();

    return 0;
}