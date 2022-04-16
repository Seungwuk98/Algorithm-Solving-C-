#include <iostream>
#include <cstring>

using namespace std;

class Person
{
private:
    float _weight;
    float _height;
    char *_name;

public:
    Person() {}
    Person(float weight, float height, const char *name)
        : _weight(weight), _height(height), _name(new char[strlen(name) + 1])
    {
        strcpy(_name, name);
    }
    ~Person()
    {
        cout << _name << endl;
        delete[] _name;
    }

    Person(const Person &person)
        : Person(person._weight, person._height, person._name) {
            cout << "copy" << endl;
        }
    void print() const
    {
        cout << _name << " " << _weight << " " << _height << endl;
    }

    Person &operator=(const Person &person)
    {
        _weight = person._weight;
        _height = person._height;
        delete[] _name;
        _name = new char[strlen(person._name) + 1];
        cout << "copy" << endl;
        strcpy(_name, person._name);
        return *this;
    }
};

int main()
{

    Person person0{45.f, 153.f, "Json asdfsd asdf "};
    Person person1 = person0;
    Person person2;
    person2 = person0 = person1;

    person0.print();
    person1.print();
    person2.print();



} // namespace std;
