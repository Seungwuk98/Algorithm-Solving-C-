#include <iostream>

using namespace std;

struct Weapon
{
    int price;
    int power;
};

void upgrade(Weapon &pWeapon)
{
    pWeapon.power += 10;
    pWeapon.price += 10;
}

int main()
{
    Weapon weapon{10, 20};
    upgrade(weapon);

    cout << weapon.power << endl;
    cout << weapon.price << endl;

    int num;
    cin >> num; // 레퍼런스로 넘겨줌

    int nums[] = {1,2,3,4};
    for (int num : nums){
        num = 0;
    }

    for (int num : nums){
        cout << num << endl;
    }

    const int& ref0 = 1;
    float f = 1.f;
    const int& ref1 = f;

    f = 10.1f;

    cout << f << endl;
    cout << ref1 << endl;



} // namespace std;
