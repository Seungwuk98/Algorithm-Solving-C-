#include <iostream>

using namespace std;
int main()
{
    int num0 = 10, num1(20);
    int num2 = 20, num3(30);
    if (num0 == num1 && num2 == num3)
        cout << "AND" << endl;

    if ((num0 == num1) || (num2 == num3))
        cout << "OR" << endl;

    if ((true || false) && false)
        cout << "OK" << endl;

    bool result = printf("1\n") || printf("ABC"); // || && 은 시퀀스 포인트
    cout << printf("AB") << endl;

    bool r = true;
    r = !r;
    cout << r << endl;

    cout.setf(ios_base::boolalpha);
    cout << !10 << endl;
} // namespace std;
