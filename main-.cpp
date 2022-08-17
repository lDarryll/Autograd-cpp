#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <memory>

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
        cout << "构造Data" <<endl;
    }
    virtual ~Data()
    {
        delete[] this->p;
        cout << "析构Data" <<endl;
    }
    int *p = nullptr;
};

class A
{
public:
    A()
    {
        this->pdata.reset(new Data());
    }

    // 深拷贝实现，对于实例对象的复制，复制一份p的副本
    // A(const A &other)
    // {
    //     this->a = other.a;
    //     this->b = other.b;
    //     this->p = new int[100];
    //     memcpy(this->p, other.p, sizeof(int) * 100);
    // }


    int a = 124;
    int b = 234;

    shared_ptr<Data> pdata;

};

int main()
{

    A *a = new A();
    A b = *a;

    
    
    delete a;

    // cout << a->a << endl;
    cout << b.pdata.get() << endl;

    return 0;
}