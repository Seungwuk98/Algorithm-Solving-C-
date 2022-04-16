#include <iostream>

using namespace std;

class Base
{
protected:
    int num;

public:
    virtual ~Base()
    {
        cout << "~Base" << endl;
    }
    void func0()
    {
    }
};

class Derived : public Base
{
public:
    ~Derived()
    {
        cout << "~Derived" << endl;
    }
    void func1()
    {
    }
};

class A
{
};

class B0 : public A
{
};
class B1 : public A
{
};
class C0 : public B0
{
};
class C1 : public B0
{
};
class C2 : public B1
{
};
class C3 : public B1
{
};


void func(Base& b){
    b.func0();
}

int main()
{
    Derived d;
    func(d);
} // namespace std;1
