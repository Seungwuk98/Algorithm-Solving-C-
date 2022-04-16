#include <iostream>
#include <string>

using namespace std;

int sum(int x, int y)
{
    return x + y;
}

int main(int argc, char *argv[])
{
    int total = 0;
    for (int i = 0; i < argc; i++)
    {
        string arg(argv[i]);
        int num = stoi(arg);
        total = sum(total, num);
    }
} // namespace std;
