#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << 'a' << endl;
    cout << (char)97 << 'b' << endl;
    cout.put('a');
    cout.put('\n');
    cout.write("hellor world", 5);
    cout.width(10);
    cout << endl;
    cout << 1 << endl;

    float num = 0.123456f;
    cout << num << endl;

    cout.precision(10);
    cout << num << endl;

    cout.setf(ios_base::showpos);
    cout << 1 << endl;
    cout.unsetf(ios_base::showpos);
    cout << 1 << endl;
    cout.setf(ios_base::boolalpha);
    cout << true << endl;
    cout << false << endl;

    cout.setf(ios_base::internal, ios_base::adjustfield);
    cout.width(10);
    cout << -10 << endl;

    cout << 32 << endl;

    cout << setw(10) << setfill('#') << setprecision(2) << showpos << 1.1f;

    freopen("output.txt", "w", stdout);
    cout << 11 << endl;
    return 0;
}
