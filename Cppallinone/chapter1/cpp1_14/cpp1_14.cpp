#include <iostream>

using namespace std;
int main()
{
    cout << 40 - 32 / 2 << "==" << 24 << endl;
    cout << 4 - 6 + 2 + 8 / 2 / 2 * 2 << endl;

    int a, b, c;
    a = b = c = 10;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    int num = 0;
    cout << num++ << endl;
    cout << num << endl;

    num = 10;
    cout << num % 3 << endl;
    num += 5;
    cout << num << endl;
    a = num += 10;
    cout << a << endl;
    
    num = 10;
    cout << ++num + num++ << endl;
    cout << num << endl;

    printf("%d %d\n", ++num, ++num);
    printf("%d\n", num);

} // namespace std;
