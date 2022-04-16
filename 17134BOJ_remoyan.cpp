#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>
#include <vector>
#include <algorithm>
#include <vector>
#include <complex>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

typedef long long lint;
typedef complex<double> base;
void fft(vector<base> &a, bool invert)
{
    int n = sz(a);
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * M_PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            base w(1);
            for (int j = 0; j < len / 2; j++)
            {
                base u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v; a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
    {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

vector<lint> multiply(vector<lint> &v, vector<lint> &w)
{
    vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
    int n = 1;
    while (n < max(v.size(), w.size()))
        n <<= 1;
    n <<= 1;
    fv.resize(n);
    fw.resize(n);
    fft(fv, 0);
    fft(fw, 0);
    for (int i = 0; i < n; i++)
        fv[i] *= fw[i];
    fft(fv, 1);
    vector<lint> ret(n);
    for (int i = 0; i < n; i++)
        ret[i] = (lint)round(fv[i].real());
    return ret;
}
const int MAX = 1000000;
vector<lint> a(MAX+1,1), b(MAX+1);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    a[0]=a[1]=0;
    for (int i=2; i<=MAX/2; i++){
        if (a[i]) {
            b[2*i] =1;
            if (i <= 1000) for(int j=i*i; j<=MAX; j+=i) a[j] = 0;
        }
    }
    vector<lint> c = multiply(a,b);

    int T; cin >> T;
    while (T--){
        int n; cin >> n;
        cout << c[n] << '\n';
    }
}