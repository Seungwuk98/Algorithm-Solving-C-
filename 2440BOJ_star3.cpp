#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    for (; n; n--)
    {
        for (int i = n; i; i--)
            cout << '*';
        cout << endl;
    }

} // namespace std;`
