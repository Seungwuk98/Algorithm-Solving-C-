#include <iostream>
using namespace std;

struct Weapon
{
    int price;
    int power;
};

void update(Weapon &weapon)
{
    weapon.power += 10;
    weapon.price += 10;
}

int main()
{
    Weapon weapon{10, 20};

    cout << "Price : " << weapon.power << endl;
    cout << "Power : " << weapon.price << endl;

    update(weapon);

    cout << "Price : " << weapon.power << endl;
    cout << "Power : " << weapon.price << endl;

} // namespace std;
