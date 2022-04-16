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
    for (int i = 0; i < n; ++i)
    {
        double x = inv ? -2 * M_PI / n * i : 2 * M_PI / n * i;
        base w(cos(x), sin(x));
        a[i] = 0;
        base t(1, 0);
        for (int j = 0; j < n; ++j, t *= w)
        {
            int idx = 0;
            for (int k = j, l = n; l; k >>= 1, l >>= 1)
                if (k & 1)
                    idx += l >> 1;
            a[i] += b[idx] * t;
        }
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

char a[1000005], b[1000005];

int main()
{
    scanf("%s%s", &a, &b);
    reverse(a, a + strlen(a));
    reverse(b, b + strlen(b));
    vector<lint> A, B;
    for (int i = 0; a[i]; i++)
        A.push_back(a[i] - '0');
    for (int i = 0; b[i]; i++)
        B.push_back(b[i] - '0');
    vector<lint> C = multiply(A, B);
    for (int i = 0; i < C.size(); i++)
    {
        C[i + 1] += C[i] / 10;
        C[i] %= 10;
    }
    int i;
    bool check = false;
    for (i = C.size() - 1; i >= 0; i--)
    {
        if (C[i])
        {
            check = true;
            break;
        }
    }
    if (!check)
    {
        printf("0");
        return 0;
    }
    else
    {
        for (; i >= 0; i--)
            printf("%lld", C[i]);
    }
}