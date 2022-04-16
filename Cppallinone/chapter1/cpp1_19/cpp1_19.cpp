#include <iostream>

using namespace std;
int main()
{
    int num;
    cin >> num;
    int total = 1;
multiply:
    total *= num;
    if (--num >= 1)
        goto multiply;

    cout << total << endl;

} // namespace std;
