#include <bits/stdc++.h>

using namespace std;

int main()
{
    int x[9] = {0,};
    int y[9] = {0,};
    for (int i=0; i<9; ++i) y[i] = i;
    memcpy(x, y, sizeof(y));
    for (int i=0; i<9; ++i) cout << x[i] << ' ';

} // namespace std;
