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

int main()
{
    string s1; cin >> s1;
    string s2; cin >> s2;
    int n = s1.size();
    string s = s1+s2;
    vector<int> sa = getsa(s);
    vector<int> lcp = getlcp(s, sa);


    int msz, midx;
    msz = midx =0;
    for (int i=1; i<lcp.size(); i++){
        int a1, a2;
        a1 = sa[i]; a2 = sa[i-1];
        if (a1 > a2) swap(a1, a2);
        if (a1 <n && a2 >= n && msz < lcp[i]){
            msz = lcp[i]; midx = a2;
        }
    }

    cout << msz << '\n';
    for (int i=midx-n;msz; ++i, msz--) cout << s2[i];
    cout << '\n';


} // namespace std;
