#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> a, pw, b, c, ans;
int n, k;

const int mod = 786433;
const int root = 5;
const int root_pw = 1<<18;

void fft (vector<int> & a) {
    int n = (int) a.size();

    for (int i=1, j=0; i<n; ++i) {
        int bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }

    for (int len=2; len<=n; len<<=1) {
        int wlen = root;
        for (int i=len; i<root_pw; i<<=1)
            wlen = int (wlen * 1ll * wlen % mod);
        for (int i=0; i<n; i+=len) {
            int w = 1;
            for (int j=0; j<len/2; ++j) {
                int u = a[i+j],  v = int (a[i+j+len/2] * 1ll * w % mod);
                a[i+j] = u+v < mod ? u+v : u+v-mod;
                a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
                w = int (w * 1ll * wlen % mod);
            }
        }
    }
}

int pow (int a, int b) {
    if (b == 1) return a;
    int q = pow(a, b/2);
    q = q * 1LL * q % mod;
    if (b % 2) q = q * 1LL * a % mod;
    return q;
}

int main(int argc, const char * argv[]) {
    cin >> n;
    a.resize(1 << 18);
    b.resize(1 << 18);
    c.resize(1 << 18);
    ans.resize(mod);
    for(int i = 0; i < a.size(); i++) {
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
    }
    for(int i = 0; i < mod; i++) {
        ans[i] = 0;
    }
    for(int i = 0; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
        c[i] = a[i];
        if (i > 0) {
            b[i] = b[i] * 1LL * pow(10, i) % mod;
            c[i] = c[i] * 1LL * pow(100, i) % mod;
        }
    }
    ans[0] = a[0];
    fft(a);
    fft(b);
    fft(c);
	for (auto x : a) cout << x << ' ';
	cout << endl;
    pw.resize(1 << 18);
    pw[0] = 1;
    for(int i = 1; i < (1 << 18); i++)
        pw[i] = (pw[i - 1] * root) % mod;
    for(int i = 0; i < (1 << 18); i++) {
        ans[pw[i]] = a[i];
        ans[pw[i] * 10 % mod] = b[i];
        ans[pw[i] * 100 % mod] = c[i];
    }
    cin >> k;
    for(int i = 0; i < k; i++) {
        int x;
        cin >> x;
        cout << ans[x] << endl;
    }
    return 0;
}