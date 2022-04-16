#include <iostream>

using namespace std;

class Character
{
protected:
    int _health;
    int _power;

public:
    Character(int health, int power) : _health(health), _power(power)
    {
    }

    virtual void damaged(int power) override
    {
        _health -= power;
    }

    void attack(Character &target) const
    {
        target.damaged(_power);
    }
};

class Player : public Character
{
    Player(int health, int power)
        : Character()
    {
    }
    void damaged(int power)
    {
        Character::damaged(power);
        cout << "으악" << endl;
    }
};

int main()
{
} // namespace std;
