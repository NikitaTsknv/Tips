#include <iostream>

struct S
{
    int x = 1;
    double y = 3.14;
    char c = 'a';

    struct SS
    {
        float s = 1.05;
        //float d = y;
    } ss; // ss - переменная ss в структуре S

    void f(int a){
        this->x = a;
        std::cout << this->x << ' ' << y << ' ' << c << "\n";
    }

    void f();
};

void S::f() {
    std::cout << "Ha!\n";
}

class S1
{
    friend void g();
    friend class SS1;

private:
    int x = 1; 
    void f(int a) {
        this->x = a;
        std::cout << this->x << "\n";
    }

public:
    double y = 3.14;
    void f(double d) {
        std::cout << x << "\n";
    }
};

void g() {
    S s;
    std::cout << s.x << "\n";
}

int main()
{
    S s{ 2, 2.72 }; // aggregate initialization

    std::cout << s.x << ' ' << s.y << ' ' << s.c << "\n";

    S* ps = new S{ 4, 4.72 }; // aggregate initialization

    std::cout << ps->x << ' ' << ps->y << ' ' << ps->c << "\n";

    s.f();

    ps->f(6);

    std::cout << ps->ss.s << "\n";

    struct Another {
        int a = 1;
        int b = 2;
    };

    Another a;

    std::cout << a.a << "\n";

    delete ps;

    S1 s1;
    //s1.f(0); - CE
    s1.f(0.);

    std::cout << *((double*)(&s1)+1) << "\n";
}