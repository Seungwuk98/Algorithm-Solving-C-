#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int m = n;
    for (; n; n--)
    {
        for (int i = m - n; i; i--)
            cout << ' ';
        for (int i = 2 * n - 1; i; i--)
            cout << '*';
        cout << endl;
    }
} // namespace std;
