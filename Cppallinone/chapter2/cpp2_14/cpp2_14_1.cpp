#include <iostream>
#include <cstring>

using namespace std;

class String
{
private:
    char *_chars;

public:
    String(const char *chars) : _chars(new char[strlen(chars) + 1])
    {
        strcpy(_chars, chars);
    }

    char operator[](int idx) const
    {
        return _chars[idx];
    }

    char &operator[](int idx)
    {
        return _chars[idx];
    }

    friend ostream &operator<<(ostream &os, const String &s)
    {
        os << s._chars;
        return os;
    }
};

int main()
{
    String s("abc");
    cout << s[0] << endl;
    cout << s << endl;
    s[0] = 'd';
    cout << s << endl;
} // namespace std;
