class Person
{
private:
    float _weight;
    float _height;
    const std::string _name;

public:
    Person(float weight, float height, const std::string &name) : _weight(weight), _height(height), _name(name) {}
    void print()
    {
        std::cout << _name << std::endl;
    }
};

void foo();