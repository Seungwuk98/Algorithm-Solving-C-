#include <iostream>
#include <string>

using namespace std;

int countDigit(int num)
{
    if (!num)
        return 1;
    int count = 0;
    while (num)
    {
        num /= 10;
        count++;
    }
    return count;
}

int countDigit(string num)
{
    return countDigit(stoi(num));
}



int main()
{
    cout << countDigit(0) << endl;
    cout << countDigit(12345) << endl;
    cout << countDigit("12345") << endl;

    cout << 'a' << endl;
    cout << (int)'a' << endl;
} // namespace std;
