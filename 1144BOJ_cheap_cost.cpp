#include <bits/stdc++.h>

using namespace std;

int n,m;
int mat[81];
unordered_map<int, int> dp[81];

struct state
{
    vector<int> s;
    state() {
        s.resize(m);
    }
    state(int x) {
        s.resize(m);
        for (int i=0; i<m && x; ++i) {
            s[i] = x%10;
            x/=10;
        }
    }

    int val() {
        int ret = 0;
        for (int i=0, c=1; i<m; ++i, c*=10) {
            ret += s[i] * c;
        }
        return ret;
    }

    void norm() {
        unordered_map<int, int> ck;
        for (int i=0, t=1; i<m; ++i) {
            if (s[i] == 0) continue;
            if (ck.find(s[i]) == ck.end()) ck[s[i]] = t++;
            s[i] = ck[s[i]];
        }
    }

    bool alone() {
        unordered_set<int> t;
        for (int x : s) if (x) t.insert(x);
        return t.size() == 1;
    }

    bool up_alone() {
        int x = s.back();
        for (int i=0; i<m-1; ++i) if (s[i] == x) return false;
        return true;
    }

    state prop(int j, bool chk) {
        state ret;
        for (int i=1; i<m; ++i) ret.s[i] = s[i-1];
        if (chk) {
            int u = s.back();
            int l = j? s[0] : 0;
            if (u) {
                ret.s[0] = u;
                if (l) for (int i=1; i<m; ++i) if (ret.s[i] == l) ret.s[i] = u;
            } else if (l) {
                ret.s[0] = l;
            } else {
                ret.s[0] = 1234;
            }
        } 
        ret.norm();
        return ret;
    }
};



int main()
{
    cin >> n >> m;
    for (int i=0; i<n*m; ++i) cin >> mat[i];
    dp[0][0] = 0;
    dp[0][1] = mat[0];
    int ans = min(0, mat[0]);
    for (int i=1; i<n*m; ++i) {
        for (auto [k, v] : dp[i-1]) {
            state st(k);
            int up = st.s.back();
            state prop = st.prop(i%m, 1);
            int val = prop.val();
            if (dp[i].find(val) == dp[i].end()) dp[i][val] = v + mat[i];
            else dp[i][val] = min(dp[i][val], v + mat[i]);
            if (prop.alone()) {
                ans = min(ans, dp[i][val]);
            } 
            if (!st.s[m-1] || !st.up_alone()) {
                prop = st.prop(i%m, 0);
                val = prop.val();
                if (dp[i].find(val) == dp[i].end()) dp[i][val] = v;
                else dp[i][val] = min(dp[i][val], v);
            }
        }
    }
    cout << ans;
} // namespace std;
