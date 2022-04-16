#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define chk(nxt) nxt!=p && !vst[nxt]
#define sze(v) (int)(v).size()
#define all(v) v.begin(), v.end()
#define _USE_MATH_DEFINES

using namespace std;
using lint = long long;
vector<vector<int>> g;
vector<bool> isprime, vst;
vector<int> prime, sz;

int n, m;
int nums = 0;


typedef complex<double> base;
typedef long long lint;
void fft(vector<base> &a, bool inv)
{
    int n = a.size(), j = 0;
    vector<base> roots(n / 2);
    for (int i = 1; i < n; i++)
    {
        int bit = (n >> 1);
        while (j >= bit)
        {
            j -= bit;
            bit >>= 1;
        }
        j += bit; if (i < j) swap(a[i], a[j]);
    }
    double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
    for (int i = 0; i < n / 2; i++)
    {
        roots[i] = base(cos(ang * i), sin(ang * i));
    }
    
    for (int i = 2; i <= n; i <<= 1)
    {
        int step = n / i;
        for (int j = 0; j < n; j += i)
        {
            for (int k = 0; k < i /2;k++)
            {
                base u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
                a[j + k] = u + v;
                a[j + k + i / 2] = u - v;
            }
        }
    }
    if (inv)
        for (int i = 0;i < n; i++)
            a[i] /= n; 
}
vector<lint> multiply(vector<lint> &v, vector<lint> &w)
{
    vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
    int n = 2;
    while (n < v.size() + w.size()) n <<=1;
    fv.resize(n);
    fw.resize(n);
    fft(fv,0);
    fft(fw,0);
    for (int i =0;i < n; i++)fv[i] *= fw[i];
    fft(fv,1);
    vector<lint> ret(n);
    for (int i =0;i < n; i++)
        ret[i] = (lint)round(fv[i].real());
    return ret;
}


int get_size(int v, int p = -1){
    sz[v] = 1;
    for (int &nxt : g[v]) if (chk(nxt)) sz[v] += get_size(nxt, v);
    return sz[v];
}

int get_cent(int v, int p, int S){
    for (int &nxt : g[v]) if (chk(nxt) && sz[nxt]*2>S) return get_cent(nxt, v, S);
    return v;
}

void dfs(int v, int p, int dep, vector<lint> &B){
    if (B.size() <= dep) B.push_back(1);
    else B[dep]++;
    if (isprime[dep]) nums++;
    for (int &nxt : g[v]) if (nxt!=p && !vst[nxt]) dfs(nxt, v, dep+1, B);
}

void get_ans(int v){
    int cent = get_cent(v,-1,get_size(v));
    sort(all(g[cent]), [&](int a, int b){return sz[a]<sz[b];});
    vector<vector<lint>> A;
    for (int &nxt : g[cent]) if (!vst[nxt]){
        vector<lint> B(1); dfs(nxt,cent,1,B);
        A.push_back(B);
    }
    int k = A.size();
    for (int i=0; i<k-1; ++i) for (int j=i+1; j<k; ++j) {
        vector<lint> C = multiply(A[i], A[j]);
        for (int l=0; l<m && prime[l] < C.size(); ++l) nums += C[prime[l]];
    }
    vst[cent] = 1;
    for (int &nxt : g[cent]) if (!vst[nxt]) get_ans(nxt);
    
    
    vst[cent] = 1;
    for (int &nxt : g[cent]) if (!vst[nxt]) get_ans(nxt);
}


int main()
{
    scanf("%d",&n);
    g.resize(n+1); sz.resize(n+1); vst.resize(n+1);
    for (int i=n-1; i--;){
        int x,y; scanf("%d%d", &x,&y);
        g[x].push_back(y); g[y].push_back(x);
    }
    isprime.resize(n, 1);
    isprime[0] = isprime[1] = 0;
    int sn = sqrt(n)+1;
    for (int i=2; i<sn; ++i) if (isprime[i]) for (int j=i*i; j<n; j+=i) isprime[j] = 0;
    for (int i=2; i<n; ++i) if (isprime[i]) prime.push_back(i);
    m = prime.size();
    get_ans(1);
    double result = nums / ((double)n*(n-1)/2);
    printf("%.10f", result);

} // namespace std;
