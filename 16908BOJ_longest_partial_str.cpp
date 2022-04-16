#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <math.h>

using namespace std;

struct Comparator
{
    const vector<int> &group;
    int t;
    Comparator(const vector<int> &_group, int _t)
        : group(_group), t(_t) {}
    bool operator()(int a, int b)
    {
        if (group[a] != group[b])
            return group[a] < group[b];
        return group[a + t] < group[b + t];
    }
};

vector<int> getsa(const string &s)
{
    int n = s.size();
    int t = 1;
    vector<int> group(n + 1);
    for (int i = 0; i < n; ++i)
        group[i] = s[i];
    group[n] = -1;
    vector<int> sa(n);
    for (int i = 0; i < n; ++i)
        sa[i] = i;
    while (t < n)
    {
        Comparator comp(group, t);
        sort(sa.begin(), sa.end(), comp);
        t <<= 1;
        if (t >= n)
            break;
        vector<int> ngroup(n + 1);
        ngroup[n] = -1;
        ngroup[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
        {
            if (comp(sa[i - 1], sa[i]))
                ngroup[sa[i]] = ngroup[sa[i - 1]] + 1;
            else
                ngroup[sa[i]] = ngroup[sa[i - 1]];
        }
        group = ngroup;
    }

    return sa;
}

vector<int> getlcp(const string &s, const vector<int> &sa)
{
    int n = s.size();
    vector<int> lcp(n), isa(n);
    for (int i = 0; i < n; ++i)
        isa[sa[i]] = i;
    for (int k = 0, i = 0; i < n; ++i)
        if (isa[i])
        {
            for (int j = sa[isa[i] - 1]; s[i + k] == s[j + k]; ++k);
            lcp[isa[i]] = (k ? k-- : 0);
        }
    return lcp;
}

vector<int> e;
bool check(vector<int> &a){
    sort(a.begin(),a.end());
    for (auto x : a) cout << x << " " ;
    cout << endl;
    for (int i=0; i<a.size()-1; ++i){
        if (!(a[i] < e[i] && a[i+1] > e[i])) return false;
    }
    cout << "true" << endl;
    return true;
}

int main()
{
    int n; cin >> n; int T = n;
    string s; cin >> s;
    e.push_back(s.size());
    while (--T){
        char x = T+70;
        string t; cin >> t; s += x+t;
        e.push_back(e.back()+1+t.size());
    }
    vector<int> sa = getsa(s);
    vector<int> lcp = getlcp(s, sa);
    

    int msz; int midx;
    msz = midx = 0;
    for (int i=0; i<=sa.size()-n;++i){
        vector<int> a; int nsz = 1000000;
        for (int j=0; j<n; ++j){
            a.push_back(sa[i+j]);
            if (j) nsz = min(lcp[i+j], nsz);
        }
        if (nsz > msz && check(a)) {
            msz = nsz; midx = sa[i];
        }
    }
    cout << msz << '\n';
} // namespace std;
