#include <stdlib.h>
#include <iostream>

#define MAX 10

// Создаем стек
struct stack {
    int items[MAX];
    int top;
    int size;
};

using st  = stack;

void createEmptyStack(st* s) {
    s->top = -1;
    s->size = 0;
}

// Проверяем, не заполнен ли стек
bool isFull(st* s) {
    if (s->top == MAX - 1)
        return true;
    else
        return false;
}

// Проверяем, не пуст ли стек
bool isEmpty(st* s) {
    if (s->top == -1)
        return true;
    else
        return false;
}

// Добавляем элемент в стек
void push(st* s, int new_item) {
    if (isFull(s)) {
        printf("Stack is full");
    }
    else {
        s->size++;
        s->top++;
        s->items[s->top] = new_item;
    }
}

// Удаляем элемент из стека
void pop(st* s) {
    if (isEmpty(s)) {
        printf("\nStack is empty\n");
    }
    else {
        printf("Element removed = %d", s->items[s->top]);
        s->size--;
        s->top--;
    }
}

// Выводим в консоль элементы стека
void printStack(st* s) {
    printf("Stack size: %i\n", s->size);
    printf("Stack: ");
    for (int i = 0; i < s->size; i++) {
        std::cout << s->items[i] << " ";
    }
    std::cout << std::endl;
}

// Функция main
int main() {
    int ch;
    st* s = (st*)malloc(sizeof(st));

    createEmptyStack(s);

    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);

    printStack(s);

    pop(s);

    std::cout << "\nAfter remove\n";
    printStack(s);
}