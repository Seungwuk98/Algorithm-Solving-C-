#include <iostream>
#include <cfloat>
#include <string.h>

using namespace std;

int main()
{
    float num0 = 1.0f;

    unsigned int num1 = 0b01001011100000000000000000000000;
    float num2;
    memcpy(&num2, &num1, sizeof(num1));

    cout.precision(64);
    cout << num0 + num2 << endl;
    cout << num2 << endl;

    cout << FLT_MAX << endl;

    float num3;
    unsigned int num4 = 0b01111111011111111111111111111111;
    memcpy(&num3, &num4, sizeof(num4));
    cout << num3 << endl;

    unsigned int ifltMin;
}