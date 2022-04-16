#include <iostream>
#include <string>
#include <array>

using namespace std;
int main()
{
    string a, b;
    cin >> a;
    cin >> b;
    array<int, 26> alist{};
    array<int, 26> blist{};
    for (int x : a)
        alist[x - 97] += 1;
    for (int x : b)
        blist[x - 97] += 1;
    int result = 0;
    for (int i = 0; i < 26; i++)
        result += min(alist[i], blist[i]) * 2;
    cout << a.size() + b.size() - result << endl;

} // namespace std;
