#include <iostream>
#include <limits>

using namespace std;

int main()
{
    char ch = 'a';
    char ch1 = 97;

    cout << "ch1 : " << ch1 << endl;
    cout << "ch0 : " << ch << endl;

    cout << "ch0 : " << (int)ch << endl;
    cout << "ch0 : " << int(ch) << endl;

    cout << (char)97 << endl;
    cout << sizeof(ch) << endl;

    cout << (int)numeric_limits<uint8_t>::max() << endl;

    cout << "Hello world\t";
    cout << "Hello World";
    cout << "\x61";
    cout << "Hello world" << endl;

    char x = 'ab';
    int y = 'ab';
    cout << x << endl;
    cout << y << endl;
}