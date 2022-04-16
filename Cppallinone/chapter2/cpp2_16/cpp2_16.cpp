#include <iostream>
#include <cstring>
#include <algorithm>
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
    String(const char *s0, const char *s1)
    {
        cout << s0 << endl;
        cout << s1 << endl;
    }
    String(initializer_list<const char *> strs)
    {
        for (const char *str : strs)
        {
            cout << str << endl;
        }
    }

    explicit operator bool() const
    {
        return strlen(_chars) > 0;
    }
};

void func(const String &s)
{
}

int main()
{
    String s0 = "";
    String s1{"abc", "def"};
    String s2{"a", "b", "c", "d", "e"};

    bool result = (bool)s0;
    cout << result << endl;
    if (!s0)
    {
        cout << "!!" << endl;
    }

} // namespace td;
