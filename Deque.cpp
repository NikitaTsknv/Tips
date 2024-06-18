#include <iostream>

#define MAX 10

class Deque {
    int arr[MAX];
    int front;
    int rear;
    int size;

public:
    Deque(int size) {
        front = -1;
        rear = 0;
        this->size = size;
    }

    void insertFront(int key);
    void insertRear(int key);
    void deleteFront();
    void deleteRear();
    bool isFull();
    bool isEmpty();
    int getFront();
    int getRear();
};

bool Deque::isFull() {
    return ((front == 0 && rear == size - 1) ||
        front == rear + 1);
}

bool Deque::isEmpty() {
    return (front == -1);
}

void Deque::insertFront(int key) {
    if (isFull()) {
        std::cout << "Overflow" << std::endl;
        return;
    }

    if (front == -1) {
        front = 0;
        rear = 0;
    }

    else if (front == 0)
        front = size - 1;

    else
        front = front - 1;

    arr[front] = key;
}

void Deque::insertRear(int key) {
    if (isFull()) {
        std::cout << "Overflow" << std::endl;
        return;
    }

    if (front == -1) {
        front = 0;
        rear = 0;
    }

    else if (rear == size - 1)
        rear = 0;

    else
        rear = rear + 1;

    arr[rear] = key;
}

void Deque::deleteFront() {
    if (isEmpty()) {
        std::cout << "Anti-overflow" << std::endl;
        return;
    }

    if (front == rear) {
        front = -1;
        rear = -1;
    }
    else if (front == size - 1)
        front = 0;

    else
        front = front + 1;
}

void Deque::deleteRear() {
    if (isEmpty()) {
        std::cout << "Anti-overflow" << std::endl;
        return;
    }

    if (front == rear) {
        front = -1;
        rear = -1;
    }
    else if (rear == 0)
        rear = size - 1;
    else
        rear = rear - 1;
}

int Deque::getFront() {
    if (isEmpty()) {
        std::cout << "Anti-overflow" << std::endl;
        return -1;
    }
    std::cout << "Front element " << arr[front] << std::endl;
    return arr[front];
}

int Deque::getRear() {
    if (isEmpty() || rear < 0) {
        std::cout << "Anti-overflow" << std::endl;
        return -1;
    }
    std::cout << "Rear element " << arr[rear] << std::endl;
    return arr[rear];
}

int main() {
    Deque dq(4);

    std::cout << "Insert rear element\n";
    dq.insertRear(5);
    dq.insertRear(11);
    dq.insertFront(1);

    dq.getFront();
    dq.getRear();

    dq.deleteRear();
    std::cout << "After removing the last element, the new last element is: " << dq.getRear() << std::endl;

    std::cout << "Insert front element\n";
    dq.insertFront(8);

    std::cout << "Front element: " << dq.getFront() << std::endl;
    dq.deleteFront();
    std::cout << "After removing the first element, the new first element: " << dq.getFront() << std::endl;

}