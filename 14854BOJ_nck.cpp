#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>
#define fio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

using namespace std;
using lint = long long;

lint modpow(lint c, lint n, lint p){
    lint r = 1;
    while (n){
        if (n&1) r=r*c%p;
        c = c*c%p;
        n >>= 1;
    } return r;
}

vector<lint> precompute(int p, int e){
    lint pe = modpow(p,e,12341324L);
    vector<lint> val(pe,1);
    for (int i=2; i<pe; ++i)
        val[i] = i%p ? val[i-1]*i%pe : val[i-1];
    return val; 
}

pair<lint,lint> fact_n_pe(vector<lint> val, lint n, lint p, lint e, lint pe){
    if (n<p) return make_pair(0, val[n]);
    lint t = n/p;
    pair<lint,lint> next = fact_n_pe(val, t, p, e, pe);
    lint tp = t + next.first;
    lint kp = n/pe, rp = n%pe;
    lint m = next.second * modpow(val[pe-1], kp, pe) % pe * val[rp] %pe;
    return make_pair(tp, m);
}

lint comb(lint n, lint k, lint p){
    if (!n || n < k) return 0;
    lint r,s,t; r=s=t=1;
    for (int i=2; i<=n; ++i){
        r = r*i %p;
        if (i == k) s = modpow(r,p-2,p);
        if (i == n-k) t = modpow(r,p-2,p);
    }
    return r*s%p*t%p;
}

lint lucas(lint n, lint k, lint p){
    vector<lint> ni;
    vector<lint> ki;
    while (n){
        ni.push_back(n%p);
        n/=p;
    }
    while (k){
        ki.push_back(k%p);
        k/=p;
    }
    ki.resize(ni.size(),0);
    lint result = 1;
    for (int i=0; i<ni.size(); ++i){
        result = result * comb(ni[i], ki[i], p) %p;
    }
    return result;

}



lint comb(lint n, lint k, lint p, lint e){
    if (e == 1) return lucas(n,k,p);
    lint pe = modpow(p,e,12341234L);
    vector<lint> val = precompute(p,e);
    pair<lint, lint> p1 = fact_n_pe(val, n, p, e, pe);
    pair<lint, lint> p2 = fact_n_pe(val, k, p, e, pe);
    pair<lint, lint> p3 = fact_n_pe(val, n-k, p, e, pe);
    lint t = p1.first - p2.first - p3.first;
    if (t>=e) return 0;
    int i = 0;
    for (;i<pe;++i) if (p2.second*p3.second%pe*i%pe == 1) break;
    return modpow(p,t,pe) * p1.second %pe * i %pe;
}
lint D = 142857;

int main()
{   
    fio;
    int T; cin >> T;
    while (T--){
        lint n,r; cin >> n >> r;
        lint a,b,c,d;
        a = comb(n,r,3,3);
        b = comb(n,r,11,1);
        c = comb(n,r,13,1);
        d = comb(n,r,37,1);
        lint result = (a*137566LL % D + b*103896LL % D + c*109890LL % D + d*77220LL % D) % D;
        cout << result << endl;
    }

} // namespace std
