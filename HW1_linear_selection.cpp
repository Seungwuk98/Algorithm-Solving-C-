#include <bits/stdc++.h>
#include "HW1_checker_program.h"
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

bool isone(int *a, int s, int e){
    /**************************************
    배열 a의 [s, e] 범위의 모든 값이 같은 값인지 확인한다.
    만약 하나의 값이면 1, 아니면 0을 return한다.
    **************************************/
    for (int i=s; i<e; ++i) if (a[i] != a[e]) return false;
    return true;
}

int insertion_sort(int *a, int s, int e){
    /*************************************
    배열 a의 [s, e] 범위를 insertion sort한다.
    *************************************/
    for (int i=s+1; i<=e; ++i) 
        for (int j=i; j>s && a[j] < a[j-1]; --j)
            swap(a[j], a[j-1]);
}

int partition(int *a, int s, int e){
    /*************************************
    배열 a의 [s, e] 범위를 a[e]를 피벗으로 partition한다.
    **************************************/
    int i = s;
    for (int j=s; j<e; ++j) if (a[j] <= a[e]) swap(a[i++], a[j]);
    swap(a[e], a[i]);
    return i;
}

int selection(int *a, int s, int e, int i){
    /**************************************
    배열 a의 [s, e] 범위에서 i번째 원소를 select 한다.
    **************************************/
    if (isone(a, s, e)) return a[s];
    if (e-s+1 <= 5 ) {
        insertion_sort(a, s, e);
        // sort(a+s, a+e+1);
        return a[s+i-1];
    }
    int z=s;
    for (int x=s; x<=e; x+=5){
        int y = min(x+5, e);
        insertion_sort(a, x, y);
        // sort(a+x, a+y+1);
        swap(a[z++], a[x+y>>1]);
    }
    int mid = selection(a, s, z-1, z-s>>1);
    for (int x=s; x<=e; ++x) if (a[x] == mid) {
        mid = x; break;
    }
    swap(a[e], a[mid]);
    int q = partition(a, s, e);
    int diff = q-s+1;
    if (i == diff) return a[q];
    if (i < diff) return selection(a, s, q-1, i);
    return selection(a, q+1, e, i-diff);
}

using namespace chrono;

int a[100000000];

int main()
{
    /*************file stream*************/
    ifstream cin;
    cin.open("testcase5.txt");
    ofstream cout;
    cout.open("deter5.txt");
    cin.tie(0); ios_base::sync_with_stdio(0);
    /*************file stream*************/
    int n,k;
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
