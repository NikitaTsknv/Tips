#include <iostream>

class TreeElem
{
public:
    int m_data; // данные, которые хранятся в этой вершине
    TreeElem* m_left; // указатель на левого потомка данной вершины
    TreeElem* m_right; // указатель на правого потомка данной вершины
    TreeElem(int val)
    {
        m_left = nullptr;
        m_right = nullptr;
        m_data = val;
    }
};

class BinaryTree
{
private:
    TreeElem* m_root;
    int m_size;
    void print_tree(TreeElem*);
    void delete_tree(TreeElem*); // рекурсивно вызывает себя для удаления левого поддерева, правого поддерева, затем удаляет сам элемент

public:
    BinaryTree(int);
    ~BinaryTree();
    void print(); // рекурсивно обходит дерево и выводит его элементы в порядке возрастания
    bool find(int); // проверяет, содержится ли в дереве элемент со значением key
    void insert(int);
    void erase(int);
};

BinaryTree::BinaryTree(int key)
{
    m_root = new TreeElem(key);
    m_size = 1;
}

BinaryTree::~BinaryTree()
{
    delete_tree(m_root);
}

void BinaryTree::delete_tree(TreeElem* curr)
{
    if (curr)
    {
        delete_tree(curr->m_left);
        delete_tree(curr->m_right);
        delete curr;
    }
}

void BinaryTree::print()
{
    print_tree(m_root);
    std::cout << std::endl;
}

void BinaryTree::print_tree(TreeElem* curr)
{
    if (curr) // Проверка на ненулевой указатель
    {
        print_tree(curr->m_left);
        std::cout << curr->m_data << " \n";
        print_tree(curr->m_right);
    }
}

bool BinaryTree::find(int key)
{
    TreeElem* curr = m_root;
    while (curr && curr->m_data != key)
    {
        if (curr->m_data > key)
            curr = curr->m_left;
        else
            curr = curr->m_right;
    }
    return curr != NULL;
}

void BinaryTree::insert(int key)
{
    TreeElem* curr = m_root;
    while (curr && curr->m_data != key)
    {
        if (curr->m_data > key && curr->m_left == NULL)
        {
            curr->m_left = new TreeElem(key);
            ++m_size;
            return;
        }
        if (curr->m_data < key && curr->m_right == NULL)
        {
            curr->m_right = new TreeElem(key);
            ++m_size;
            return;
        }
        if (curr->m_data > key)
            curr = curr->m_left;
        else
            curr = curr->m_right;
    }
}

void BinaryTree::erase(int key)
{
    TreeElem* curr = m_root;
    TreeElem* parent = NULL;
    while (curr && curr->m_data != key)
    {
        parent = curr;
        if (curr->m_data > key)
        {
            curr = curr->m_left;
        }
        else
        {
            curr = curr->m_right;
        }
    }
    if (!curr)
        return;
    if (curr->m_left == NULL)
    {
        // Вместо curr подвешивается его правое поддерево
        if (parent && parent->m_left == curr)
            parent->m_left = curr->m_right;
        if (parent && parent->m_right == curr)
            parent->m_right = curr->m_right;
        --m_size;
        delete curr;
        return;
    }
    if (curr->m_right == NULL)
    {
        // Вместо curr подвешивается его левое поддерево
        if (parent && parent->m_left == curr)
            parent->m_left = curr->m_left;
        if (parent && parent->m_right == curr)
            parent->m_right = curr->m_left;
        --m_size;
        delete curr;
        return;
    }
    // У элемента есть два потомка, тогда на место элемента поставим
    // наименьший элемент из его правого поддерева
    TreeElem* replace = curr->m_right;
    while (replace->m_left)
        replace = replace->m_left;
    int replace_value = replace->m_data;
    erase(replace_value);
    curr->m_data = replace_value;
}

int main()
{
    std::cout << "Hello World!\n";
}