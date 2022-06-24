#include <bits/stdc++.h>

using namespace std;

int n, m;
char mat[102];
unordered_map<int, int> dp[102];

/*
    1      2       3     4     5       6
  ===      |       |     |   ===       ===
         ===       ===   |     |       |
*/

struct state
{
    vector<int> s;
    state(){s.resize(m+1);}
    state (int x) {
        s.resize(m+1);
        for (int i=0; i<=m && x; ++i, x/=7) s[i] = x%7;  
    }

    int val() {
        int ret = 0;
        for (int i=0, c=1; i<=m; ++i, c*=7) ret += s[i] * c;
        return ret;
    }

    void norm() {
        unordered_map<int, int> T;
        for (int i=0, t=1; i<=m; ++i) {
            if (s[i] == 0) continue;
            if (T.find(s[i]) == T.end()) T[s[i]] = t++;
            s[i] = T[s[i]];
        }
    }

    vector<state> prop(int j) {
        vector<state> ret;
        vector<int> tmp(m+1);
        for (int i=1; i<=m; ++i) tmp[i] = s[i-1];
        int u = s.back();
        int t = s[0];
        if (j == 0 && t) return ret;
        if (u && t) {
            if (u ^ t) { // _| 연결
                state a;
                a.s = tmp; a.s[0] = a.s[1] = 0;
                for (int i=2; i<=m; ++i) if (a.s[i] == t) a.s[i] = u;
                ret.push_back(a);
            }
        } else if (u) { // a : | 연결  b : |_ 연결
            state a, b;
            a.s = tmp; a.s[1] = u; a.s[0] = 0;
            b.s = tmp; b.s[1] = 0; b.s[0] = u;
            ret.push_back(a); ret.push_back(b);
        } else if (t) { // a : -- 연결  b : =| 연결
            state a, b;
            a.s = tmp; a.s[1] = 0; a.s[0] = t;
            b.s = tmp; b.s[1] = t; b.s[0] = 0;
            ret.push_back(a); ret.push_back(b);
        } else { // a : |= 연결  b : 노설치
            state a, b;
            a.s = tmp; a.s[1] = a.s[0] = 1234;
            b.s = tmp; b.s[1] = b.s[0] = 0;
            ret.push_back(a); ret.push_back(b);
        }
        for (auto &x : ret) x.norm();
        return ret;
    }

    vector<state> skip(int j) {
        vector<state> ret;
        int u = s.back();
        int t = s[0];
        if (u || t) return ret;
        state a;
        for (int i=2; i<=m; ++i) a.s[i] = s[i-1];
        a.norm();
        ret.push_back(a);
        return ret;
    }

    bool eff() {
        return val() == 7;
    }
};


int main() {
    cin >> n >> m;
    for (int i=0; i<n*m; ++i) dp[i].clear();
    for (int i=0; i<n*m; ++i) cin >> mat[i];
    if (mat[0] != '#') {
        dp[0][1] = 1;
        dp[0][7] = 1;
    }
    for (int i=1; i<n*m; ++i) {
        // cout << dp[i-1].size() << endl;
        for (auto [k, v] : dp[i-1]) {
            state st(k);
            vector<state> ret = mat[i] == '#' ? st.skip(i%m) : st.prop(i%m);
            for (state &x : ret) {
                int val = x.val();
                // cout << "from : "; st.print(); cout << "to : "; x.print(); cout << endl; 
                if (dp[i].find(val) == dp[i].end()) dp[i][val] = v;
                else {
                    // cout << "---" << i/m << ' ' << i%m << ' '; x.print(); cout << endl;
                    dp[i][val] = (dp[i][val] + v) % 10007;
                } 
            }
        }
    }
    int ans = 0;
    for (auto [k, v] : dp[n*m-1]) {
        state st(k);
        if (st.eff()) ans = (ans + v) % 10007;
    }

    cout << ans << '\n';
}