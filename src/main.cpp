#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

// 存储表达式所需的相关数据
class Container
{
public:
    //返回表达是具体是什么类型，或者说什么名称
    virtual const char *type() = 0;

    // 具体的forward的实现过程
    virtual float forward()=0;

    // 具体的backward的实现
    virtual void backward(float gradient)=0;  

};

// 表达式类
// 1. 所有的操作都可以认为是表达式
//    a. 标量x可以认为是常量表达式
//    b. 任意的算子， 比如加减乘除，都可抽象为表达式
class Expression
{
public:
    // 对表达式进行前向推理， 并得到推理后结果
    float forward()
    {
        return container_->forward();
    }

    // 对表达式反向推理，计算每一个节点对应的倒数
    void backward()
    {
        return container_->backward(1.0f);
    }

    // 为了存储表达式中的数据，所以需要引入二级指针，表示表达式所储存的具体实现
    // 具体实现在这里
    shared_ptr<Container> container_;
};

class ScalarContainer : public Container
{
public:
    ScalarContainer(float value)
    {
        value_ = value;
    }
    //返回表达是具体是什么类型，或者说什么名称
    virtual const char *type() override
    {
        return "Scalar";
    }

    // 具体的forward的实现过程
    virtual float forward() override
    {
        return value_;
    }

    // 具体的backward的实现
    virtual void backward(float gradient) override
    {
        gradient_ += gradient;
    }  

    float value_ = 0;
    float gradient_ = 0;
};


class Scalar : public Expression
{
    public:
        Scalar(float value)
        {
            container_.reset(new ScalarContainer(value));
        }

        float gradient() const 
        {
            return dynamic_pointer_cast<ScalarContainer>(container_)->gradient_;
            // return ((ScalarContainer*)container_.get())->gradient_;
        }
};

class MultiplyContainer : public Container
{
public:
    MultiplyContainer(const Expression& left, const Expression& right)
    {
        left_value_ = left.container_;
        right_value_ = right.container_;
    }
    //返回表达是具体是什么类型，或者说什么名称
    virtual const char *type() override
    {
        return "Multiply";
    }

    // 具体的forward的实现过程
    virtual float forward() override
    {
        return left_value_->forward() * right_value_->forward();
    }

    // 具体的backward的实现
    virtual void backward(float gradient) override
    {
        left_value_->backward(gradient * right_value_->forward());
        right_value_->backward(gradient * left_value_->forward());
    }  

    shared_ptr<Container> left_value_;
    shared_ptr<Container> right_value_;
};

class Multiply : public Expression 
{
    public:
        Multiply(const Expression& left, const Expression& right)
        {
            container_.reset(new MultiplyContainer(left, right));
        }
};


Expression operator* (float left, const Expression& right)
{
    return Multiply(Scalar(left), right);
};

Expression operator* (const Expression& left, float right)
{
    return Multiply(left, Scalar(right));
};


int main()
{
    // 1. 实现计算图的统计
    // 2. 实现过程，和四则运算类似，和普通表达式类似
    // 3. 实现forward前向计算，和backward反向求导
    // a 是一个通过调整得到的值，通过梯度方向调整，最终逼近sqrt(x)
    // x 是一个常量，需要求解的对象

    float x = 9;
    Scalar a(3.0f);
    // a uto loss = (a.power() - x).power();

    // cout << a.forward() <<endl;
    auto exp = 5.0f * a * 2.0;
    cout << exp.forward() <<endl;
    exp.backward();
    cout << a.gradient() << endl;
    // cout << a.gradient() << endl;


    return 0;
}
