#include <iostream>

using namespace std;

class A
{
public:
    int num;
};
class B : public A
{
};

class Animal
{
public:
    int *p;
    virtual void eat() const
    {
        cout << "냠" << endl;
    }
};

class Cat : public Animal
{
public:
    virtual void eat() const override
    {
        cout << "냥" << endl;
    }
};

class Dog : public Animal
{
public:
    virtual void eat() const override
    {
        cout << "멍" << endl;
    }
};

A operator+(const A &x, const A &y)
{
    A a;
    a.num = x.num + y.num;
    return a;
}

B operator+(const B &x, const B &y)
{
    B b;
    b.num = x.num * y.num;
    return b;
}

void func(int x)
{
    cout << x << endl;
}

void func(int x, int y)
{
    cout << x << endl;
    cout << y << endl;
}

int main()
{

    Animal a;
    cout << &a << endl;
    cout << &(a.p) << endl;
} // namespace std;
