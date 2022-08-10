#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        this->p = new int[100];
        this->p[0] = 555;
    }

    virtual ~A()
    {
        delete[] this->p;
    }

    int a = 124;
    int b = 234;
    int *p = nullptr;
};

int main()
{
    A a;
    A b = a;

    cout << *a.p << endl;
    cout << *b.p << endl;

    return 0;
}