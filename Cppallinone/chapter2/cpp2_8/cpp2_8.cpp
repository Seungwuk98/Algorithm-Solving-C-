#include <iostream>
#include "Person.cpp"

using namespace std;

int main()
{
    Person p0;
    Person p1;

    p0.print();
    p1.print();

    Person::print();
} // namespace std;
