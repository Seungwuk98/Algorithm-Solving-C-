#include <bits/stdc++.h>

using namespace std;
int n, m;
int mat[9][9];
unordered_map<int, int> dp[9][9];

struct state
{
    vector<int> s;
    state(int x = 0)
    {
        s.resize(m);
        for (int i = 0; i < m && x; ++i)
        {
            s[i] = x % 10;
            x /= 10;
        }
    }

    int val()
    {
        int ret = 0;
        for (int i = 0, c = 1; i < m; ++i, c *= 10)
            ret += s[i] * c;
        return ret;
    }

    int up()
    {
        return s.back();
    }

    int left()
    {
        return s[1];
    }

    void set_left(int x)
    {
        int t = left();
        if (t == 0)
            return;
        for (int i = 1; i < m && s[i] == t; ++i)
        {
            s[i] = x;
        }
    }

    void set_up(int x)
    {
        *(s.end() - 1) = x;
    }

    void norm()
    {
        int p = -1;
        for (int i = 0, t = 0; i < m; ++i)
        {
            if (s[i] == 0)
                continue;
            if (s[i] != p)
                t++, p = s[i];
            s[i] = t;
        }
    }

    state operator<<(int x)
    {
        state ret;
        for (int i = 1; i < m; ++i)
        {
            ret.s[i] = s[i - 1];
        }
        return ret;
    }

    state prop(int chk)
    {
        if (chk)
        {
            state ret;
            ret.s = s;
            int u = up();
            if (u)
                ret.set_left(u);
            int l = ret.left();
        }
        else
        {
            return operator<<(1);
        }
    }
};

int main()
{
    n = 2;
    m = 3;
    state s(30);
    cout << (s.prop(1)).val();
}