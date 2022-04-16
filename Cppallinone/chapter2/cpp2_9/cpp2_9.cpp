#include <iostream>
#include <functional>

using namespace std;

class Person
{
public:
    static void print(int i)
    {
        cout << i << endl;
    }
};

int main()
{
    void (*fn)(int) = &Person::print;
    fn(2);

} // namespace std;
