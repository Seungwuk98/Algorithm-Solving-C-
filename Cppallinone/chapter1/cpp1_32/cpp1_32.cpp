#include <iostream>

using namespace std;
int main()
{

    int *p = (int*)malloc(sizeof(int) * 3);
    free(p);
    
} // namespace std;
