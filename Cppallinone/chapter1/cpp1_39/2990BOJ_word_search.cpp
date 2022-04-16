#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

struct Node
{
    char ch;
    int visit;
    bool child[27]{};

};

int main()
{
    bool child[27]{};
    for (bool x : child){
        cout << x << endl;
    }
} // namespace std;
