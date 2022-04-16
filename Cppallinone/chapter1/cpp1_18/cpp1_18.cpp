#include <iostream>

using namespace std;

int num = 10;
int main()
{
    int num = 0;
    cout << (num == 0 ? "num == 0" : "num!= 0") << endl;

    cout << sizeof num << endl;
    cout << sizeof(int) << endl;
    cout << ::num;

    unsigned int uintNum = 1;
    int intNum = 1u;
    float fNum = 1.1;

    uintNum = intNum;
    intNum = uintNum;
    fNum = intNum;

} // namespace std
