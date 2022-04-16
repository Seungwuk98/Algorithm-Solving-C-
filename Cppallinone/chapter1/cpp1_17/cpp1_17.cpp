#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    unsigned int att = 5u;
    if (att & (1 << 0))
        cout << "1st" << endl;

    if (att & (1 << 2))
        cout << "3rd" << endl;

    cout << (int)pow(2, 1) << endl;
}