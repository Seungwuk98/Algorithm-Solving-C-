#include <iostream>

using namespace std;

struct Person
{
    float weight;
    float height;
    /* data */
};

int main()
{
    Person *persons[3] = {
        new Person{56.1f, 174.3f},
        new Person{74.2f, 184.2f}};

    for (Person *person : persons)
    {
        cout << person->weight << endl;
    }
} // namespace std;
