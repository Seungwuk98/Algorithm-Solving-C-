#include <bits/stdc++.h>

using namespace std;

int main()
{
	bool isprime[1000001];
	fill(&isprime[0], &isprime[1000001], 1);
	isprime[0] = isprime[1] = 0;
	for (int i=2; i<=1000; ++i) if (isprime[i]) for (int j=i*i; j<=1000000; j+=i) isprime[j] = 0;
	for (int i=0; i<=1000000; ++i) {
		if (isprime[i]) cout << i << endl;
	}
} // namespace std;
