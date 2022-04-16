#include <iostream>
#include <string.h>
#include <cfloat>
#include <math.h>
using namespace std;

int main()
{
    float num0 = 0.1f;
    float num1 = 0.02f * 5.0f;

    cout.precision(64);
    cout << num0 << endl;
    cout << num1 << endl;

    if (fabsf(num0 - num1) <= FLT_EPSILON)
        cout << "Equal 1" << endl;
    if (num0 == 0.1f)
        cout << "Equal 2" << endl;
    if (num0 == 0.1)
        cout << "Equal 3" << endl;
    if (num0 == 0.1L)
        cout << "Equal 4" << endl;

    cout << 0.1f << endl;
    cout << 0.1 << endl;
    cout << 0.1L << endl;
}