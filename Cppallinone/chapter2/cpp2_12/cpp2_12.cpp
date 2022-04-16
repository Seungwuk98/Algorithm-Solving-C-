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

    bool operator!() const{
        return strlen(_chars) == 0;
    }

    bool operator&&(bool b) const{
        return strlen(_chars) > 0 && b;
    }
    bool operator||(bool b) const{
        return strlen(_chars) > 0 || b;
    }

};

bool func(){
    cout << "func" << endl;
    return true;
}

int main()
{
    String s("a");

    if (s || func()){
        cout << "!!" << endl;
    }

} // namespace std;
