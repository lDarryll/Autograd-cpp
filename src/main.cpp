#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>

using namespace std;

// 1. 无论a被复制多少份，它的数据指针p永远都是同一个（数据引用），使得这个数据不至于有太多副本
// 2. 还能够正常释放内存
// 3. p指针释放问题，也就是释放的时机

class Data
{
public:
    Data()
    {
        this->p = new int[100];
    }
    virtual ~Data()
    {
        delete[] this->p;
    }
    int *p = nullptr;
    int nref = 1;
};

class A
{
public:
    A()
    {
        this->p = new Data();
    }

    // 深拷贝实现，对于实例对象的复制，复制一份p的副本
    // A(const A &other)
    // {
    //     this->a = other.a;
    //     this->b = other.b;
    //     this->p = new int[100];
    //     memcpy(this->p, other.p, sizeof(int) * 100);
    // }

    A(const A &other)
    {
        *this = other;
        this->p->nref++;
    }


    virtual ~A()
    {
        // 当最后一个应用实例释放时，删除p指针
        // 只要存在其它引用，释放都是不合适的
        // 问题在于，如何判断最后执行的析构函数是最后一个引用呢？
        // 引用计数， ref


        if (this->p->nref == 1)
        {   
            cout << "nref: " <<this->p->nref<< endl;
            delete this->p;
        }
        else
        {
            cout << "nref: " <<this->p->nref<< endl;
            this->p->nref--;
        }

        cout << "virtual ~A()" << endl;
    }

    int a = 124;
    int b = 234;
    Data *p = nullptr;
};

int main()
{

    A *a = new A();
    A b = *a;

    
    
    // delete a;

    cout << a->a << endl;
    cout << b.a << endl;

    return 0;
}