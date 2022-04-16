#include <iostream>
#include <typeinfo>
#include <cstring>

using namespace std;
int main()
{
    char str0[100] = "abcd";
    char *str1 = str0;

    const char *str2 = "hello";

    cout << strlen(str2) << endl;
    strcpy(str0, str2);

    cout << str0 << endl;

    cout << strcmp(str0, str2) << endl;

} // namespace std;
