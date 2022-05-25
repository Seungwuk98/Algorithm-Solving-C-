#include <bits/stdc++.h>

using namespace std;

int main()
{
    int v = 8000;
    cout << v << '\n';
    for (int i = 1; i <= v; ++i)
    {
        cout << v - 1 << ' ';
        for (int j = 1; j <= v; ++j)
            if (i != j)
            {
                cout << j << ' ';
            }
        cout << '\n';
    }
} // namespace std;
