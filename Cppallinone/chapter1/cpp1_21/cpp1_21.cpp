#include <iostream>
#include <cstring>

using namespace std;
int main()
{
    char str0[100] = "world";
    char str1[100] = "hello";
    int result = strcmp(str0, str1);
    cout << result << endl;

    strcat(str1, str0);
    cout << str1 << endl;
    int num = atoi(str0);
    

    cout << num << endl;

} // namespace std;

