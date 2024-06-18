#include <iostream>

class Node {
public:
    double data;
    Node* prev;
    Node* next;

public:
    Node(double data) {
        this->data = data;
        this->prev = this->next = nullptr;
    }
};

class LinkedList {
public:
    Node *head;
    Node *tail;

public:
    LinkedList() {
        this->head = this->tail = nullptr;
    }

    ~LinkedList() {
        while (head != nullptr)
            pop_front();
    }


    Node* operator [] (int index) {
        return getAt(index);
    }

    Node* push_front(double data);
    Node* push_back(double data);
    void pop_front();
    void pop_back();
    Node* insert(int index, double data);
    Node* getAt(int index);
    void erase(int index);
};

Node* LinkedList::push_front(double data) {
    Node* ptr = new Node(data);// новый элемент

    ptr->next = head;// Следующий - бывшая голова
    if (head != nullptr)// Если элементы есть?
        head->prev = ptr;
    if (tail == nullptr)
        tail = ptr;
    head = ptr;

    return ptr;
}

Node* LinkedList::push_back(double data) {
    Node* ptr = new Node(data);// Создаем новый элемент

    ptr->prev = tail;// Предыдущий - бывший хвост
    if (tail != nullptr)// Если элементы есть?
        tail->next = ptr;
    if (head == nullptr)
        head = ptr;
    tail = ptr;

    return ptr;
}
void LinkedList::pop_front() {
    if (head == NULL) return;

    Node* ptr = head->next;
    if (ptr != NULL)
        ptr->prev = NULL;
    else
        tail = NULL;

    delete head;
    head = ptr;
}

void LinkedList::pop_back() {
    if (tail == nullptr) return;

    Node* ptr = tail->prev;
    if (ptr != nullptr)
        ptr->next = nullptr;
    else
        head = nullptr;

    delete tail;
    tail = ptr;
}

Node* LinkedList::insert(int index, double data) {
    Node* right = getAt(index);
    if (right == nullptr)
        return push_back(data);

    Node* left = right->prev;
    if (left == nullptr)
        return push_front(data);

    Node* ptr = new Node(data);

    ptr->prev = left;
    ptr->next = right;
    left->next = ptr;
    right->prev = ptr;

    return ptr;
}

Node* LinkedList::getAt(int index) {
    Node* ptr = head;
    int n = 0;

    while (n != index) {
        if (ptr == nullptr)
            return ptr;
        ptr = ptr->next;
        n++;
    }

    return ptr;
}

void LinkedList::erase(int index) {
    Node* ptr = getAt(index);
    if (ptr == nullptr)
        return;

    if (ptr->prev == nullptr) {
        pop_front();
        return;
    }

    if (ptr->next == nullptr) {
        pop_back();
        return;
    }

    Node* left = ptr->prev;
    Node* right = ptr->next;
    left->next = right;
    right->prev = left;

    delete ptr;
}


int main()
{
    LinkedList lst;
    lst.push_back(1.0);
    lst.push_back(2.0);
    lst.push_back(3.0);
    lst.push_back(4.0);

    lst.insert(2, -5.0);
    lst.insert(20, -10.0);
    lst.erase(3);
    lst.erase(30);

    for (Node* ptr = lst.head; ptr != nullptr; ptr = ptr->next)
        std::cout << ptr->data << " ";
    std::cout << std::endl;

    for (Node* ptr = lst.tail; ptr != nullptr; ptr = ptr->prev)
        std::cout << ptr->data << " ";
    std::cout << std::endl;

    std::cout << lst[1]->data << std::endl;
    std::cout << lst[0]->data << std::endl;
    std::cout << lst[3]->data << std::endl;

    return 0;
}