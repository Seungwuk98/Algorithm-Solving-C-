#include <iostream>
#include <string>
#include <cstring>

using namespace std;
int main()
{
    string s0 = "hello";
    string s1 = "world";
    s0.append(s1);
    cout << s0 << endl;

    char s2[100] = "hello";
    char s3[] = "world";

    strcat(s2, s3);
    cout << s2 << endl;
} // namespace std;
