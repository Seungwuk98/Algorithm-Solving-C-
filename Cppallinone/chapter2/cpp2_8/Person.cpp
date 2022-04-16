#include "Person.h"
#include <iostream>

Person::Person()
{
    num++;
}

void Person::print()
{
    std::cout << num << std::endl;
}