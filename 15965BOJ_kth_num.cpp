#include <iostream>
#include <vector>
#include <algorithm>
#define all(v) v.begin(), v.end()

using namespace std;
int main()
{
    int k; cin >> k;
    vector<bool> isprime(9000000,1);
    isprime[0] = isprime[1] = 0;
    for (int i=0; i<3000; ++i){
        if (isprime[i]) for (int j=i*i; j<9000000; j+=i) isprime[j] = 0;
    }
    vector<int> prime;
    for (int i=0; i<9000000; ++i) if (isprime[i]) prime.push_back(i);
    cout << prime[k-1];

} // namespace std;
