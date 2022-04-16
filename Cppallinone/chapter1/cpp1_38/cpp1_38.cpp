#include <iostream>

using namespace std;

void func(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }
}

int main(int argc, char *argv[])
{
    char strs[][5] = {"abcd", "efgh"};
}