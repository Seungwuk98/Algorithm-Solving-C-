#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int m = n;
    for (; n; n--)
    {
        for (int i = n - 1; i; i--)
            cout << ' ';
        for (int i = 2 * (m - n + 1) - 1; i; i--)
            cout << '*';
        cout << endl;
    }
} // namespace std;
