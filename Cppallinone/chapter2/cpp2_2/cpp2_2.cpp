#include <iostream>

using namespace std;

class Player
{
private:
    int _health;
    int _power;
    string _name;

public:
    Player(int health, int power, string name){
        _health = health;
        _power = power;
        _name = name;
    }
    void attack(Player &target)
    {
        cout << "Attack " << _name << "->" << target._name << endl;
        target.damaged(_power);
    }

    void damaged(int power){
        _health -= power;
        if (_health <= 0)
            cout << "Died." << _name << endl;
    }

}; // namespace std;

int main()
{
    Player david{200,100,"David"};
    
    
}