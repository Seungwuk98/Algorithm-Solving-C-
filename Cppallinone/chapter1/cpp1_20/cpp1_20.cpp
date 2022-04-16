#include <iostream>
#include <array>
using namespace std;
int main()
{

    int num[3]{};
    for (int i = 0; i < 3; i++)
        cout << num[i] << endl;
    int num1[3];
    copy(num, num + 3, num1);
    for (int i = 0; i < 3; i++)
        cout << num1[i] << endl;
    cout << size(num1) << endl;
} // namespace std;
