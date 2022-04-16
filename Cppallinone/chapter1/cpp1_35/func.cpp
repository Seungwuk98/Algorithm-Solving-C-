#include <iostream>

using namespace std;
int sum(int x, int y)
{
    return x + y;
}

int abs(int x)
{
    return x >= 0 ? x : -x;
}
int abssum(int x, int y)
{
    return sum(abs(x), abs(y));
}

void print(int x, int y)
{
    cout << x << endl;
    if (y < 0)
        return;
    cout << y << endl;
    return;
}