#include <iostream>

using namespace std;
class Person
{
private:
    const string _name;
    float _weight;
    float _height;

public:
    Person(const string &name, float weight, float height) : _name(name), _weight(weight), _height(height) {}

    float getWeight(/*const Person* this*/) const
    {
        return _weight;
    }
};

int main()
{
    Person person("David", 75.f, 181.f);
    cout << person.getWeight() << endl;
} // namespace std;
