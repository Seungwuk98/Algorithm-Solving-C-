#include <iostream>
#include <string>

using namespace std;
int main()
{

    string str0 = to_string(1234);
    cout << str0 << endl;

    string str1 = to_string(123.23);
    cout << str1 << endl;

    int num = stoi("123");
    cout << num << endl;

    float num1 = stof("123.4");
    cout << num1 << endl;

    string x;
    getline(cin, x);
    cout << x << endl;
} // namespace std;
