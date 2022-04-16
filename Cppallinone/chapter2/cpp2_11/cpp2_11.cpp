#include <iostream>
#include <string>
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

    bool operator==(const String &s) const
    {
        return strcmp(_chars, s._chars) == 0;
    }
    bool operator!=(const String &s) const
    {
        return !(*this == s);
    }

    bool operator<(const String &s) const
    {
        return strcmp(_chars, s._chars) < 0;
    }
    bool operator>(const String &s) const
    {
        return strcmp(_chars, s._chars) > 0;
    }
    bool operator<=(const String &s) const
    {
        return !(*this > s);
    }
    bool operator>=(const String &s) const
    {
        return !(*this < s);
    }

    void print()
    {
        cout << _chars << endl;
    }
};

int main()
{
    String s0("abc");
    String s1("abd");

    if (s0 > s1)
        cout << "EQ" << endl;

} // namespace std;
