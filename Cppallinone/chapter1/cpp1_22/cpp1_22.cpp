#include <iostream>
#include <cstring>

using namespace std;
int main()
{
    struct alignas(16) Person
    {
        short grade;
        float height;
        float weight;
        char name[10];
    };

    cout << alignof(Person) << endl;

} // namespace std;
