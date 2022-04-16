#include <iostream>

using namespace std;
int pow(int base, int exp)
{
    int result = 1;
    for (int i = 0; i < exp; ++i)
        result *= base;
    return result;
}

struct Person
{
    float weight;
    float height;
};

void foo(Person *p0 = nullptr)
{
    if (p0)
    {
        cout << p0->weight << endl;
        cout << p0->height << endl;
    }
    else
        cout << "invalid" << endl;
}

int main()
{
    foo();
    Person p{74.f, 183.1f};
    foo(&p);

} // namespace stdl
