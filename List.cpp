#include <iostream>

class Node {
public:
    double data;
    Node* next;

public:
    Node(double data) {
        this->data = data;
        this->next = nullptr;
    }
};

class OneLinkedList {
public:
    Node* head, * tail;

public:
    OneLinkedList() {
        this->head = this->tail = nullptr;
    }

    ~OneLinkedList() {
        while (head != nullptr) pop_front();
    }

    void pop_front();
    void push_back(double data);
    void push_front(double data);
    void pop_back();
    Node* getAt(int k);
    void insert(int k, double data);
    void erase(int k);
};

void OneLinkedList::pop_front() {
    if (head == nullptr) return;

    if (head == tail) {
        delete tail;
        head = tail = nullptr;
        return;
    }

    Node* node = head;
    head = node->next;
    delete node;
}

void OneLinkedList::push_back(double data) {
    Node* node = new Node(data);
    if (head == nullptr) head = node;
    if (tail != nullptr) tail->next = node;
    tail = node;
}

void OneLinkedList::push_front(double data) {
    Node* node = new Node(data);
    node->next = head;
    head = node;
    if (tail == nullptr) tail = node;
}

void OneLinkedList::pop_back() {
    if (tail == nullptr) return;
    if (head == tail) {
        delete tail;
        head = tail = nullptr;
        return;
    }

    Node* node = head;
    for (; node->next != tail; node = node->next);

    node->next = nullptr;
    delete tail;
    tail = node;
}

Node* OneLinkedList::getAt(int k) {
    if (k < 0) return nullptr;

    Node* node = head;
    int n = 0;
    while (node && n != k && node->next) {
        node = node->next;
        n++;
    }

    return (n == k) ? node : nullptr;
}

void OneLinkedList::insert(int k, double data) {
    Node* left = getAt(k);
    if (left == nullptr) return;

    Node* right = left->next;
    Node* node = new Node(data);

    left->next = node;
    node->next = right;
    if (right == nullptr) tail = node;
}

void OneLinkedList::erase(int k) {
    if (k < 0) return;
    if (k == 0) {
        pop_front();
        return;
    }

    Node* left = getAt(k - 1);
    Node* node = left->next;
    if (node == nullptr) return;

    Node* right = node->next;
    left->next = right;
    if (node == tail) tail = left;
    delete node;
}

int main()
{
    OneLinkedList lst;
    lst.push_front(1);
    lst.push_back(2);
    lst.push_back(3);

    Node* n = lst.getAt(0);
    double d = (n != nullptr) ? n->data : 0;
    std::cout << d << std::endl;

    lst.erase(1);
    lst.insert(0, 5);
    lst.insert(0, 4);
    lst.pop_back();

    for (Node* node = lst.head; node != nullptr; node = node->next) {
        std::cout << node->data << " " << node << "\n";
    }

    return 0;
}