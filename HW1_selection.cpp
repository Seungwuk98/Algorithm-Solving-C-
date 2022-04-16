#include <bits/stdc++.h>
#include "HW1_checker_program.h"

using namespace std;
using ll = long long;
ll R = 2342305;
ll A = 2305953;
ll B = 59843860;
ll M = 1000000007;

ll rnd(){
    return R = (A*R%M + B)%M;
}

int partition(int *a, int s, int e){
    int i = s, pivot = a[e];
    for (int j=s; j<e; ++j) if (a[j] <= pivot) swap(a[i++], a[j]);
    swap(a[i], a[e]);
    return i;
}

bool isone(int *a, int s, int e){
    for (int i=s; i<e; ++i) if (a[i] != a[e]) return false;
    return true;
}

int selection(int *a, int s, int e, int i){
    if (s==e || isone(a, s, e)) return a[s];
    int p = rnd()%(e-s+1)+s;
    swap(a[e], a[p]);
    int q = partition(a, s, e);
    int diff = q-s+1;
    if (i < diff) return selection(a, s, q-1, i);
    else if (i==diff) return a[q];
    else return selection(a, q+1, e, i-diff);
}

using namespace chrono;
int a[100000000];
int main()
{
    int n,k;
    /*************file stream*************/
    ifstream cin;
    cin.open("testcase5.txt");
    ofstream cout;
    cout.open("random5.txt");
    cin.tie(0); ios_base::sync_with_stdio(0);
    /*************file stream*************/
    
    for (int i=0; i<5; ++i){
        system_clock::time_point start, end;
        start = system_clock::now();
        cin >> n;
        for (int i=0; i<n; ++i) cin >> a[i];
        cin >> k;
        int ans;
        cout << (ans = selection(a, 0, n-1, k)) << '\n';
        end = system_clock::now();
        microseconds micro = duration_cast<microseconds> (end - start);
        cout << micro.count() << "us" << '\n';
        cout << checker_ith_element(a, ans, n, k) << '\n';
    }

    /*************file close*************/
    cin.close();
    cout.close();
    /*************file close*************/
} // namespace std;
