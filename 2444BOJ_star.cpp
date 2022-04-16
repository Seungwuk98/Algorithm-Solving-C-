#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int m, k;
    m = k = n;

    for (; n; n--)
    {
        for (int i = n - 1; i; i--)
            cout << ' ';
        for (int i = 2 * (m - n) + 1; i; i--)
            cout << '*';
        cout << endl;
    }
    k-=1;
    for (; k ; k--)
    {
        for (int i = m - k; i; i--)
            cout << ' ';
        for (int i = 2 * (k - 1) + 1; i; i--)
            cout << '*';
        cout << endl;
    }
} // namespace std;
