#include <iostream>

using namespace std;
int main()
{
    int a, s = 0;
    for (int i = 0; i < 5; i++)
    {
        cin >> a;
        s += a * a;
    }
    s %= 10;
    cout << s;

} // namespace std;
