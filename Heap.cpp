#include <iostream>
#include <vector>

struct heap {
    std::vector<int> tree;

    heap() {
        tree.push_back(0);  //Мы собираемся работать в 1-индексации, поэтому
                            //просто поместим в tree[0] произвольное значение.
    }

    void push(int x) {
        tree.push_back(x);
        sift_up(tree.size() - 1);
    }

    int max() {
        if (tree.size() > 1) {
            return tree[1];
        }
        else {
            //Ошибка: попытка найти максимум в пустой куче
        }
    }

    void pop() {
        if (tree.size() > 1) {
            tree[1] = tree.back();
            tree.pop_back();
            sift_down(1);
        }
        else {
            //Ошибка: попытка извлечь максимум из пустой кучи
        }
    }

    //Проталкивание вверх.
    void sift_up(int v) {
        if (v == 1) {
            return;     //Больше некуда подниматься.
        }

        if (tree[v / 2] < tree[v]) {
            std::swap(tree[v], tree[v / 2]);
            sift_up(v / 2);
        }
    }

    //Проталкивание вниз
    void sift_down(int v) {
        if (v * 2 >= tree.size()) {
            return;     //Больше некуда спускаться.
        }

        //Индекс большего дочернего элемента
        int max_idx;
        if (v * 2 + 1 == tree.size()) {     //Если можно спуститься только влево
            max_idx = v * 2;
        }
        else if (tree[v * 2] >= tree[v * 2 + 1]) {
            max_idx = v * 2;
        }
        else {
            max_idx = v * 2 + 1;
        }

        if (tree[v] < tree[max_idx]) {
            std::swap(tree[v], tree[max_idx]);
            sift_down(max_idx);
        }
    }

    bool empty() {
        return tree.size() == 1;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}