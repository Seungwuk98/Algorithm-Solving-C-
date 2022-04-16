#include <iostream>

using namespace std;
int main()
{
    int E,S,M;
    cin >> E >> S >> M;
    int e,s,m;
    e = s = m = 1;

    int year = 1;
    while (e!=E || s!=S || m!=M){
        year++;
        e++; s++; m++;
        e=(e-1)%15+1; s=(s-1)%28+1; m=(m-1)%19+1;
    }

    cout << year;

    
} // namespace std;

