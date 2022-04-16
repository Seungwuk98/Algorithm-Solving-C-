#define _USE_MATH_DEFINES
#include <iostream>
#include <bits/stdc++.h>
#include <complex>

using namespace std;
using lint = long long;
using base = complex<double>;

void FFT(vector<base> &a, bool inv)
{
    int n = a.size();
    vector<base> b(n);
    for (int i = 0; i < n; ++i)
    {
        int idx = 0;
        for (int j = i, k = n; k; k >>= 1, j >>= 1)
            if (j & 1)
                idx += k >> 1;
        b[idx] = a[i];
    }
    vector<base> c(2 * n);
    for (int i = 0; i < n; ++i)
        c[i + n] = b[i];
    for (int i = 0; i < n; ++i)
    {
        double x = inv ? -2 * M_PI / n * i : 2 * M_PI / n * i;
    }
    if (inv)
    {
        for (int i = 0; i < n; ++i)
            a[i] /= n;
    }
};

vector<lint> multiply(vector<lint> &a, vector<lint> &b)
{
    vector<base> A(a.begin(), a.end()), B(b.begin(), b.end());
    int n = 1;
    while (n < (A.size() + B.size()))
        n <<= 1;
    A.resize(n);
    B.resize(n);
    FFT(A, 0);
    FFT(B, 0);
    for (int i = 0; i < n; ++i)
        A[i] *= B[i];
    FFT(A, 1);
    vector<lint> ret(n);
    for (int i = 0; i < n; ++i)
    {
        ret[i] = lint(round(A[i].real()));
    }
    return ret;
}

int main()
{
    vector<lint> a{1, 1, 1};
    vector<lint> ret = multiply(a, a);
    for (auto x : ret)
        cout << x << ' ';

} // namespace std;
