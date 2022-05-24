#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;
using ll = long long;

const int P = 786433;

void fft(vector<int> &A, int x) {
    int n = A.size();
    if (n == 1) return;

    vector<int> even(n>>1), odd(n>>1);
    for (int i=0; i<(n>>1); ++i) {
        even[i] = A[i<<1];
        odd[i] = A[i<<1|1];
    }

    fft(even, x*x%P);
    fft(odd, x*x%P);

    int w = 1;
    for (int i=0; i<(n>>1); ++i) {
        A[i] = even[i] + 1LL * w * odd[i] % P;
        if (A[i] >= P) A[i] -= P;
        A[i+(n>>1)] = even[i] - 1LL * w * odd[i] % P;
        if (A[i+(n>>1)] < 0) A[i+(n>>1)] += P;
        w = w * x % P;
    }
}

int pow(int x, int y) {
    int ret = 1;
    while (y) {
        if (y&1) ret = 1LL * ret * x % P;
        x = 1LL * x * x % P;
        y >>= 1;
    }
    return ret;
}
int n;
int naive(vector<int> &A, int x) {
    int ret = 0;
    int w = 1;
    for (int i=0; i<=n; ++i) {
        ret = (ret + 1LL * A[i] * w % P) % P;
        w = 1LL * w * x % P;  
    }
    return ret;
}

int main()
{
    fastio
    cin >> n;
    vector<int> a(1<<18), b(1<<18), c(1<<18), ans(P), pw(1<<18);
    for(int i = 0; i <= n; i++) {
        cin >> a[i];
        b[i] = c[i] = a[i];
        if (i > 0) {
            b[i] = b[i] * 1LL * pow(10, i) % P;
            c[i] = c[i] * 1LL * pow(100, i) % P;
        }
    }
    ans[0] = a[0];
    fft(a, 5);
    fft(b, 5);
    fft(c, 5);
    pw[0] = 1;
    for(int i = 1; i < (1 << 18); i++)
        pw[i] = (pw[i - 1] * 5) % P;
    for(int i = 0; i < (1 << 18); i++) {
        ans[pw[i]] = a[i];
        ans[pw[i] * 10 % P] = b[i];
        ans[pw[i] * 100 % P] = c[i];
    }
    int k;
    cin >> k;
    for(int i = 0; i < k; i++) {
        int x;
        cin >> x;
        cout << ans[x] << endl;
    }
    return 0;
} // namespace std;
