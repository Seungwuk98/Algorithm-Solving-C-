#include <iostream>


using namespace std;

class Person
{
private:
    float _weight;
    float _height;
    const string _name;

public:
    Person(float weight, float height, const string& name) : _weight(weight), _height(height), _name(name) {}

    void loseWeight(float weight)
    {
        this->_weight -= weight;
        if (this->_weight < 0)
            this->_weight = 0;
    }

    void skipMeals(int times)
    {
        this->loseWeight(times * 0.5f);
    }
    float getBMI()
    {
        return _weight / (_height * 100 * _height * 100);
    }

    Person &complete(Person &person)
    {
        if (this->getBMI() < person.getBMI())
            return *this;
        else
            return person;
    }

    void doceremony(){
        cout << _name << " win!!" << endl;
    }
};

int main()
{
    Person person0(67.3f, 172.3f, "david");
    Person person1(58.2f, 167.3f, "david");
    person0.complete(person1).doceremony();
} // namespace std;
